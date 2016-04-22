#-*-coding:utf-8-*-

#Import socketServer from somewhere.
import os,sys
sys.path.append(os.path.join(os.getcwd(),os.pardir))
import socketServer

import time
from threading import Timer,Thread
from flask import render_template
class SampleServer:
	SocketServer=socketServer.makeSocketServer()
	def __init__(self,fps=60,port=8000):
		self.socket=SampleServer.SocketServer(port,self)
		self.cnt=0
		self.fps=fps
	@SocketServer.on('an event')
	def onAnEvent(self,sid,data):
		print "an event("+`self.cnt`+") data="+`data`
		self.socket.emit('accepted',{'cnt':self.cnt},room=sid)
	def start(self):
		self.socket.start()
		Timer(1./self.fps,self.mainLoop,()).start()
		self.socket.join()
	def mainLoop(self):
		Timer(1./self.fps,self.mainLoop,()).start()
		self.cnt+=1
		self.socket.emit('server push',{'xxx': 'yyy','cnt':self.cnt},room='Client')
	@SocketServer.on('connect')
	def onConnect(self,sid, environ):
		print('connect ', sid)
	@SocketServer.on('disconnect')
	def onDisconnect(self,sid):
		print('disconnect ', sid,self.socket.sio.rooms(sid))
	@SocketServer.route('/')
	def index(self):
		return render_template('index.html')

if __name__ == '__main__':
	SampleServer(1,8000).start()