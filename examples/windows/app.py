from examples.windows.tcp.server import Server
from examples.windows.tcp.client import Client
from threading import Thread
from configparser import ConfigParser
from os import path
from time import sleep
import paramiko

CONFIG_FILE = "examples\\windows\\config.ini"

sender_app = None
receiver_app = None

class Transport:

    def __init__(self, *args):
        self.host_ip, self.guest_ip, self.port, self.user, self.passwd, self.hostfilepath, self.guestfilepath, self.dir= args
        
        if(self.dir == "in"):
            # linux will send, windows will receive
            # start server here 
            self.prepare_host_thread = Thread(target=self.prepare_host)

            # trigger sender on guest with these data - host_ip, port, hostfilepath, guestfilepath
            self.inform_guest_thread = Thread(target=self.prepare_guest)

            self.prepare_host_thread.start()
            sleep(5)
            self.inform_guest_thread.start()
            

            self.prepare_host_thread.join()
            self.inform_guest_thread.join()

    def scp_execute_func(self, param): 

        scp_port = 22
        command = param
        print("Trying to connect to target...")
        try:
            sshclient = paramiko.SSHClient()
            try:
                sshclient.set_missing_host_key_policy(paramiko.AutoAddPolicy())
                try:
                    sshclient.connect(self.guest_ip, scp_port, self.user, self.passwd)
                    print("Connected to target!")
                except Exception as e:
                    print(f"Connection Error : {e}")
                    return -1
            except:
                print("Error in setting host key policies!")
                return -2
        except:
            print("Error in initializing SSHClient!")
            return -3
        
        try:
            (stdin, stdout, stderr) = sshclient.exec_command(command)
            print(f"stdout : {stdout.readlines()}")
            print(f"stderr : {stderr.readlines()}")
        except Exception as e:
            print(f"Error in starting guests : {e}")
            return -4

        sshclient.close()
        print('done')
        return 0

    def prepare_guest(self):
        print(f"sender_app : {sender_app}")
        print(f"{self.host_ip}:{self.port} - {self.guestfilepath}")
        cmd = f"./{sender_app} {self.host_ip} {str(self.port)} {self.guestfilepath}"
        self.scp_execute_func(cmd)
        

    def prepare_host(self):
        server = Server(self.port)
        data = server.read_data()
        with open(self.hostfilepath, "wb") as fo:
            fo.write(data)




if __name__ == "__main__":
    config = ConfigParser()
    config.read(CONFIG_FILE)
    host_ip = config['network']['host']
    guest_ip = config['network']['guest_clone']
    port = int(config['network']['port'])
    user = config['network']['user']
    passwd = config['network']['pass']
    sender_app = config['runnables']['sender_app']
    src_file = path.join(config['path']['guest_path'], config['path']['guest_file'])
    dest_file = path.join(config['path']['host_path'], config['path']['host_file'])

    t = Transport(host_ip, guest_ip, port, user, passwd, dest_file, src_file, "in")