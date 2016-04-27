#-*-coding:utf-8-*-
from sioclientCpp import *
from threading import Thread
class SioClientBase(object):
	handlers={}
	@classmethod
	def on(cls,event,handler=None,nsp="/"):
		def set_handler(handler):
			def makeWrapper(self):
				if(self.user is None):
					def wrapper(*args,**kwargs):
						#Thread(target=handler,args=args,kwargs=kwargs).start()
						handler(*args,**kwargs)
					return wrapper
				else:
					def wrapper(*args,**kwargs):
						#Thread(target=handler,args=(self.user,)+args,kwargs=kwargs).start()
						handler(self.user,*args,**kwargs)
					return wrapper
			if(not nsp in cls.handlers):
				cls.handlers[nsp]={}
			cls.handlers[nsp][event]=makeWrapper
			return handler
		if handler is None:
			return set_handler
		set_handler(handler)
	def __init__(self,uri,user=None):
		super(SioClientBase,self).__init__()
		self.client=Client()
		self.uri=uri
		self.user=user
		import signal,sys
		def sigH(signal,handler):
			sys.exit()
		signal.signal(signal.SIGINT,sigH)
		signal.signal(signal.SIGTERM,sigH)
	def isConnected(self):
		if(self.client is None):
			return False
		return self.client.opened()
	def onSocketOpen(self,nsp):
		print "onSocketOpen(",nsp,")"
		for event in self.handlers[nsp]:
			#print "name=",event
			if(event=='disconnect'):
				pass
			else:
				self.client.socket(nsp).on(event,self.handlers[nsp][event](self))
		if('connect' in self.handlers[nsp]):
			self.handlers[nsp]['connect'](self)()
	def onSocketClose(self,nsp):
		print "onSocketClose(",nsp,")"
	def onClose(self,reason):
		print "onClose(",reason,")"
	def connect(self):
		self.client.set_socket_open_listener(lambda nsp: self.onSocketOpen(nsp))
		self.client.set_socket_close_listener(lambda nsp: self.onSocketClose(nsp))
		self.client.set_close_listener(lambda reason: self.onClose(reason))
		self.client.connect(self.uri)
	def emit(self,event,data,nsp="/"):
		self.client.socket(nsp).emit(event,data)
	def transfer(self,event,data,room=None,nsp="/"):
		if(room is None):
			self.client.socket(nsp).emit('transfer',{'event':event,'data':data})
		else:
			self.client.socket(nsp).emit('transfer',{'event':event,'room':room,'data':data})
	def start(self):
		self.connect()
def makeSioClient():
	return type('SioClient',(SioClientBase,),{'handlers':{}})

