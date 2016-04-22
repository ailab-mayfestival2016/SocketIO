#-*-coding:utf-8-*-
from threading import Thread
import socketio
import eventlet
from flask import Flask
from jinja2 import FileSystemLoader
import os
eventlet.monkey_patch()
class SocketServerBase(Thread):
	handlers={}
	routes={}
	@classmethod
	def on(cls,event,handler=None):
		def set_handler(handler):
			def makeWrapper(self):
				if(self.user is None):
					def wrapper(*args,**kwargs):
						Thread(target=handler,args=args,kwargs=kwargs).start()
						#handler(*args,**kwargs)
					return wrapper
				else:
					def wrapper(*args,**kwargs):
						Thread(target=handler,args=(self.user,)+args,kwargs=kwargs).start()
						#handler(self.user,*args,**kwargs)
					return wrapper
			cls.handlers[event]=makeWrapper
			return handler
		if handler is None:
			return set_handler
		set_handler(handler)
	@classmethod
	def route(cls,rule,**options):
		def set_route(handler):
			def makeWrapper(self):
				if(self.user is None):
					def wrapper(*args,**kwargs):
						#Thread(target=handler,args=args,kwargs=kwargs).start()
						return handler(*args,**kwargs)
					return wrapper
				else:
					def wrapper(*args,**kwargs):
						#Thread(target=handler,args=(self.user,)+args,kwargs=kwargs).start()
						return handler(self.user,*args,**kwargs)
					return wrapper
			cls.routes[rule]={'options':options,'handler':makeWrapper}
			return handler
		return set_route
	def __init__(self,port,user):
		super(SocketServerBase,self).__init__()
		self.sio=socketio.Server()
		self.app=Flask(__name__)
		self.port=port
		self.user=user
		self.sio.on('enter_room',self.enter_room)
		self.sio.on('leave_room',self.leave_room)
	def run(self):
		self.app.static_folder=os.path.join(os.getcwd(),"static")
		self.app.jinja_loader = FileSystemLoader(os.path.join(os.getcwd(),"templates"))
		for event in self.handlers:
			handler=self.handlers[event](self)
			self.sio.on(event,handler)
		for rule in self.routes:
			options=self.routes[rule]['options']
			endpoint=options.pop('endpoint',None)
			handler=self.routes[rule]['handler'](self)
			self.app.add_url_rule(rule,endpoint,handler,**options)
		# wrap Flask application with socketio's middleware
		self.app = socketio.Middleware(self.sio, self.app)
		# deploy as an eventlet WSGI server
		eventlet.wsgi.server(eventlet.listen(('', self.port)), self.app)
	def enter_room(self,sid,data):
		self.sio.enter_room(sid,data['room'])
		print sid," entered into ",data['room']
	def leave_room(self,sid,data):
		self.sio.leave_room(sid,data['room'])
		print sid," leaved from ",data['room']
	def emit(self,*args,**kwargs):
		self.sio.emit(*args,**kwargs)
def makeSocketServer():
	return type('SocketServer',(SocketServerBase,),{'handlers':{},'routes':{}})
