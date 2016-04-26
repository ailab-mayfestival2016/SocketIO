#-*-coding:utf-8-*-
#Import sioclient from somewhere.
import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import sioclient

import time
class Main:
	SioClient=sioclient.makeSioClient()
	def __init__(self,uri):
		self.uri=uri
		self.socket=Main.SioClient(uri,self)
		self.cnt=0
	def start(self):
		self.mainLoop()
	def mainLoop(self):
		self.socket.start()
		while(True):
			if(self.socket.isConnected()):
				self.socket.transfer('an event',{'hoge':'fuga','foo':[1,3.,True],'cnt':self.cnt},"Game")
			time.sleep(1./60.)
	@SioClient.on('connect')
	def onConnect(self):
		print "connected"
		self.socket.emit('enter_room',{'room':"Client"})
	@SioClient.on('server push')
	def onServerpush(self,event):
		data=event.get_messages()
		print "'server push'"+`data`
		self.cnt=data[1]['cnt']

if(__name__=='__main__'):
	main=Main('http://localhost:8000')
	main.start()
