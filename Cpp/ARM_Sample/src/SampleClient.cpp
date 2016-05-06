#include "SampleClient.h"
#include <iostream>
#include <string>
SampleClient::SampleClient() {
	cnt=0;
}

SampleClient::~SampleClient() {
}
void SampleClient::start(const std::string& uri){
	//接続時のイベントハンドラなどは接続前に登録
	client.set_open_listener(std::bind(&SampleClient::onOpen,this));
	client.set_fail_listener(std::bind(&SampleClient::onFail,this));
	client.set_close_listener(std::bind(&SampleClient::onClose,this,std::placeholders::_1));
	client.set_socket_open_listener(std::bind(&SampleClient::onSocketOpen,this,std::placeholders::_1));
	client.set_socket_close_listener(std::bind(&SampleClient::onSocketClose,this,std::placeholders::_1));
	//接続する(デフォルトでnamespace"/"のsocketが開く)
	client.connect(uri);
}
void SampleClient::onOpen(void){
	//WebSocket通信が開通した時のハンドラ。
	//ここでは特に何かしなくともよいはず。
	std::cout<<"onOpen()"<<std::endl;
}
void SampleClient::onFail(void){
	//WebSocket通信の開通に失敗した時のハンドラ。
	//普通にしてればまず呼ばれないはず。
	std::cout<<"onFail()"<<std::endl;
}
void SampleClient::onClose(sio::client::close_reason const& reason){
	//WebSocket通信が終了した時のハンドラ。
	//サーバが強制終了などで落ちたら呼ばれないっぽい。
	std::cout<<"onClose("<<reason<<")"<<std::endl;
}
void SampleClient::onSocketOpen(std::string const& nsp){
	//データ送受信のイベントはclientではなくsocket単位のため、ここで登録する。
	std::cout<<"onSocketOpen("<<nsp<<")"<<std::endl;
	if(nsp=="/"){
		sio::socket::event_listener f;
		f = std::bind(&SampleClient::OnServerPush, this, std::placeholders::_1);
		client.socket(nsp)->on("server push",f);
		client.socket()->emit("enter_room",sio::Object().add("room","Client").pack());
	}
}
void SampleClient::onSocketClose(std::string const& nsp){
	//引数で与えられたnamespaceが閉じた時のハンドラ。
	//あえて対策しなくともよいのでは？
	std::cout<<"onSocketClose("<<nsp<<")"<<std::endl;
}
void SampleClient::OnServerPush(sio::event &event){
	//イベント名は一応event.get_name()で取得できる
	std::string name=event.get_name();
	//データはevent.get_message()で取得できる
	sio::message::ptr data=event.get_messages().to_array_message();
	//Object.hをincludeしていればデータもこの型のまま文字列として出力できる
	std::cout<<"'"<<name<<"',"<<data<<std::endl;

	//Objectならばmap=data->get_mapObject’ has()で子要素のmapを取得できる
	//ptr=map["key"]でキーkeyに対応する値(のポインタ)が得られるので、型に合わせてptr->get_int()のように実際の値を得る
	//一気に書くと以下のような感じ
	//cnt=data->get_map()["cnt"]->get_int();
	//Objectデータを送信する
	sio::Object sendData;
	sendData//.add("Integer with explicit cast",(int64_t)1)
		//.addInt("Integer with special method",2)
		//.add("Double",1.0/3.0)
		.add("String","C++")
		//.add("Array",sio::Array()
		//		.addInt(1)
		//		.add((int64_t)2)
		//		.add("string"))
		.add("Child Object",sio::Object()
				.add("Child","Object"));
	client.socket()->emit("transfer",sio::Object()
		.add("event","an event")
		.add("room","Game")
		.add("data",sendData).pack());
}
