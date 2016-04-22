var socket;
var isConnected=false;
function connect(){
	if(!isConnected){
		socket = io.connect("localhost:8000", { transports: [ 'websocket' ] });
		socket.on('connect', function() {
			socket.on('server push', function (data) {
				//サーバーからの通知(60fps)
				document.getElementById("data").innerHTML=JSON.stringify(data)+"<br>";
			});
			socket.on('accepted', function (data) {
				//こちらからの'an event'に対する返答
				document.getElementById("cnt").innerHTML=data.cnt+"<br>";
			});
			socket.on('disconnect', function (data) {
				//切断時の処理
				document.getElementById("isConnected").innerHTML="Disconnected";
				isConnected=false;
			});
			isConnected=true;
			document.getElementById("isConnected").innerHTML="Connected";
			socket.emit('enter_room',{room:"Client"})
		});
	}
}
window.onbeforeunload = function (event){
};
function send(){
	if(isConnected){
		socket.emit('an event',{'platform':"Javascript",'Data':[1,2,3]});
	}
}