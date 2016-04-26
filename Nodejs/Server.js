var io = require('socket.io').listen(8000);
var cnt=0;
io.sockets.on('connection', function (socket) {
	console.log(socket.id+" connected");
	socket.on('enter_room',function(data){
		console.log(socket.id+" entered "+data['room']);
		socket.join(data['room']);
	});
	socket.on('leave_room',function(data){
		console.log(socket.id+" leaved "+data['room']);
		socket.leave(data['room']);
	});
	socket.on('transfer',function(data){
		//console.log(JSON.stringify(data))
		if('room' in data){
			socket.broadcast.to(data['room']).emit(data['event'],data['data']);
		}else{
			socket.broadcast.emit(data['event'],data['data']);
		}
	});
	socket.on('disconnect',function(data){
		console.log(socket.id+' disconnected');
	});
});
