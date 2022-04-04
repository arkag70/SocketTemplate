from ast import arg
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
        
        if self.dir == "in":
            # linux will send, windows will receive
            # start server here 
            self.prepare_host_thread = Thread(target=self.prepare_host)

            # trigger sender on guest with these data - host_ip, port, guestfilepath (to copy from)
            self.prepare_guest_thread = Thread(target=self.prepare_guest, args=("in",))

            self.prepare_host_thread.start()
            sleep(5)
            self.prepare_guest_thread.start()
            

            self.prepare_host_thread.join()
            self.prepare_guest_thread.join()
        
        elif self.dir == "out":
            # windows will send, linux will receive
            # trigger receiver on guest with these data - guestfilepath (to paste into)
            self.prepare_guest_thread = Thread(target=self.prepare_guest, args=("out",))

            #trigger sender on host to send data to guest
            self.prepare_host_thread = Thread(target=self.prepare_host, args=("out",))

            self.prepare_guest_thread.start()
            sleep(5)
            self.prepare_host_thread.start()

            self.prepare_guest_thread.join()
            self.prepare_host_thread.join()

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

    def prepare_guest(self, dir="in"):
        
        cmd = ""
        if dir == "in":
            cmd = f"./{sender_app} {self.host_ip} {str(self.port)} {self.guestfilepath}"
        elif dir == "out":
            cmd = f"./{receiver_app} {self.guestfilepath}"
        
        self.scp_execute_func(cmd)
        

    def prepare_host(self, dir="in"):

        if dir == "in":
            server = Server(self.port)
            data = server.read_data()
            with open(self.hostfilepath, "wb") as fo:
                fo.write(data)
        elif dir == "out":
            client = Client(self.guest_ip, self.port)
            content = ""
            with open(self.hostfilepath, 'rb') as fi:
                content = fi.read()
            client.send_data(content)




if __name__ == "__main__":
    config = ConfigParser()
    config.read(CONFIG_FILE)
    host_ip = config['network']['host']
    guest_ip = config['network']['guest_clone']
    port = int(config['network']['port'])
    user = config['network']['user']
    passwd = config['network']['pass']
    sender_app = config['runnables']['sender_app']
    guest_file = path.join(config['path']['guest_path'], config['path']['guest_file'])
    host_file = path.join(config['path']['host_path'], config['path']['host_file'])

    t = Transport(host_ip, guest_ip, port, user, passwd, host_file, guest_file, "in")