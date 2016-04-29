#-*-coding:utf-8-*-

#Import sioclientCpp from somewhere.
import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import sioclientCpp as sio

import time

class Main:
	def __init__(self,uri):
		self.uri=uri
		self.client=sio.Client()
		self.cnt=0
	def start(self):
		#self.client.set_close_listener(self.onOpen)
		self.client.set_socket_open_listener(self.onSocketOpen)
		#self.client.set_socket_close_listener(self.onSocketClose)
		#self.client.set_close_listener(self.onClose)
		self.client.connect(self.uri)
		self.mainLoop()
	def mainLoop(self):
		while(True):
			if(self.client.opened()):
				self.client.socket().emit('transfer',{
					'event':'an event',
					'data':{'hoge':'fuga','foo':[1,3.,True],'cnt':self.cnt},
					'room':["Game"]
				})
			time.sleep(1./60.)
	def onSocketOpen(self,nsp):
		print "connected"
		if(nsp=="/"):
			self.client.socket(nsp).on('server push',self.onServerpush)
			self.client.socket(nsp).emit('enter_room',{'room':"Client"})
	def onServerpush(self,event):
		data=event.get_message()
		print "'server push'"+`data`
		self.cnt=data[1]['cnt']

if(__name__=='__main__'):
	main=Main('http://localhost:8000')
	main.start()
