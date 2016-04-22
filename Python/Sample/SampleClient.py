#-*-coding:utf-8-*-

import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import socketClient

import time
class Main:
	SocketClient=socketClient.makeSocketClient()
	def __init__(self,url,port):
		self.socket=Main.SocketClient(url,port,self)
	def start(self):
		self.socket.start()
		self.socket.emit('enter_room',{'room':"Client"})
		self.mainLoop()
	def mainLoop(self):
		while(True):
			self.socket.emit('an event',{'platform':"Python",'Data':[1,2,3]})
			time.sleep(1)
	@SocketClient.on('server push')
	def onServerpush(self,*args):
		print('server push', args)

if(__name__=='__main__'):
	main=Main('localhost',8000)
	main.start()
