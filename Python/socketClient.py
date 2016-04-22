#-*-coding:utf-8-*-
from socketIO_client import SocketIO,LoggingSocketIONamespace
from threading import Thread
class SocketClientBase(object):
	handlers={}
	@classmethod
	def on(cls,event,handler=None):
		def set_handler(handler):
			def makeWrapper(self):
				if(self.user is None):
					def wrapper(*args,**kwargs):
						Thread(target=handler,args=args,kwargs=kwargs).start()
					return wrapper
				else:
					def wrapper(*args,**kwargs):
						Thread(target=handler,args=(self.user,)+args,kwargs=kwargs).start()
					return wrapper
			cls.handlers[event]=makeWrapper
			return handler
		if handler is None:
			return set_handler
		set_handler(handler)
	def __init__(self,url,port,user=None):
		super(SocketClientBase,self).__init__()
		self.sio=None
		self.url=url
		self.port=port
		self.user=user
	def isConnected(self):
		if(self.sio is None):
			return False
		return self.sio.connected()
	def connect(self):
		self.sio=SocketIO(self.url,self.port,LoggingSocketIONamespace)
	def emit(self,event,data):
		self.sio.emit(event,data)
	def start(self):
		self.connect()
		for event in self.handlers:
			self.sio.on(event,self.handlers[event](self))
		Thread(target=self.sio.wait).start()
def makeSocketClient():
	return type('SocketClient',(SocketClientBase,),{'handlers':{}})
