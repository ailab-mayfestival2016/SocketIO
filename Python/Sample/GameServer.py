#-*-coding:utf-8-*-

#Import sioclient from somewhere.
import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import sioclient

import time
from threading import Timer,Thread
from flask import render_template
class GameServer:
	SioClient=sioclient.makeSioClient()
	def __init__(self,uri,fps=60):
		self.socket=GameServer.SioClient(uri,self)
		self.cnt=0
		self.fps=fps
	@SioClient.on('an event')
	def onAnEvent(self,sid,data):
		print "an event("+`self.cnt`+") data="+`data`
	def start(self):
		self.socket.start()
		Timer(1./self.fps,self.mainLoop,()).start()
	def mainLoop(self):
		Timer(1./self.fps,self.mainLoop,()).start()
		self.cnt+=1
		self.socket.transfer('server push',[12,{'xxx': 'yyy','cnt':self.cnt,'array':[1,2,"aaa"]}],'Client')
	@SioClient.on('connect')
	def onConnect(self):
		print('connected')
		self.socket.emit('enter_room',{'room':"Game"})
	@SioClient.on('an event')
	def onDisconnect(self,event):
		print('an event', event.get_messages())

if __name__ == '__main__':
	GameServer("http://localhost:8000",60).start()
