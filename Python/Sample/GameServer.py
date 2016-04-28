#-*-coding:utf-8-*-

#Import sioclientCpp from somewhere.
import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import sioclientCpp as sio

from threading import Timer

class GameServer:
	def __init__(self,uri,fps=60):
		self.client=sio.Client()
		self.uri=uri
		self.cnt=0
		self.fps=fps
	def start(self):
		#self.client.set_close_listener(self.onOpen)
		self.client.set_socket_open_listener(self.onSocketOpen)
		#self.client.set_socket_close_listener(self.onSocketClose)
		#self.client.set_close_listener(self.onClose)
		self.client.connect(self.uri)
		Timer(1./self.fps,self.mainLoop,()).start()
	def mainLoop(self):
		Timer(1./self.fps,self.mainLoop,()).start()
		self.cnt+=1
		if(self.client.opened()):
			self.client.socket().emit('transfer',{
				'event':'server push',
				'room':'Client',
				'data':[12,{'xxx': 'yyy','cnt':self.cnt,'array':[1,2,"aaa"]}]
			})
	def onSocketOpen(self,nsp):
		if(nsp=="/"):
			self.client.socket(nsp).on('an event',self.onAnEvent)
			self.client.socket(nsp).emit('enter_room',{'room':"Game"})
	def onAnEvent(self,event):
		print('an event', event.get_messages())

if __name__ == '__main__':
	GameServer("http://localhost:8000",60).start()
