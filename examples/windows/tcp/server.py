import socket
import struct       
BUFFER_SIZE = 1024
KB = 1024
MB = 1024 * KB
GB = 1024 * MB
import time


class Server:

	def __init__(self, port=8000):

		self.server_fd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)        
		print ("Socket successfully created")
		self.port = port
		self.server_fd.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		# Next bind to the port
		# we have not typed any ip in the ip field
		# instead we have inputted an empty string
		# this makes the server listen to requests
		# coming from other computers on the network
		self.server_fd.bind(('', self.port))        
		print (f"socket bound to {self.port}")
 
		# put the socket into listening mode
		self.server_fd.listen(5)    
		print ("socket is listening")           
 
		# Establish connection with client.
		self.sock, self.client_addr = self.server_fd.accept()    
		print (f'Got connection from {self.client_addr}')

		# Close the connection with the client
		self.server_fd.close()

	def read_data(self):
		data = b""
		factor = 1
		prefix = ""
		chunk_size = 0
		transported = 0
		size = struct.unpack('<Q', self.sock.recv(8))[0]
		leftover = size
		print(f"Size : {size}")
		if size > MB:
			factor = MB
			prefix = "Mega-"
		elif size > KB:
			factor = KB
			prefix = "Kilo-"
		start = ""
		while leftover > 0:
			if leftover > BUFFER_SIZE:
				chunk_size = BUFFER_SIZE
			else:
				chunk_size = leftover
			
			print(f"Received : {round(transported/factor,2)} / {round(size/factor,2)} {prefix}bytes.")
			data += self.sock.recv(chunk_size)
			transported = len(data)
			leftover = size - transported
		return data

	def __del__(self):
		self.server_fd.close()
