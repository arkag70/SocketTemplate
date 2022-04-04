from http import client
import socket    
from struct import pack
BUFFER_SIZE = 1024

class Client:
	
	def __init__(self, ip = 'localhost', port = 8000):
		# Create a socket object
		self.sock = socket.socket()        
		 
		# Define the port on which you want to connect
		self.port = port
		self.ip = ip
		 
		# connect to the server on local computer
		self.sock.connect((self.ip, self.port))
		print("connection ok")
		 
	def send_data(self, data):

		print("Starting to send\n")
		size = len(data)
		buf = pack('<Q', size)
		print(size)
		self.sock.sendall(buf)
		self.sock.sendall(data)

		print(f"Data is sent. Size {len(data)}")

	def __del__(self):
		print("Closing socket...")
		self.sock.close()

if __name__ == "__main__":
	client = Client("192.168.9.11", 8000)
	content = ""
	with open("recv/sample_vid.mp4", 'rb') as fi:
		content = fi.read()
	client.send_data(content)