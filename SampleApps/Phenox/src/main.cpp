#include <iostream>
#include "SioClientWrapper.h"
#include "Parser.h"//受信データのsio::message::ptrから値を抽出するためのサンプル
#include "DataMaker.h"//送信データを生成するためのサンプル

int main()
{
	SioClientWrapper client;
	sio::message::ptr data;
	//発生するイベント名一覧をstd::vector<std::string>としてclientに渡す
	std::vector<std::string> eventList(0);
	eventList.push_back("Sample Event");
	eventList.push_back("vec3 sample");
	client.setEventList(eventList);
	//自身を表す部屋名を設定する(Phenoxなら例えば"Phenox"と決める)
	client.setMyRoom("Phenox");
	//データの送信宛先となる部屋名を設定する(Gameサーバなら例えば"Game")
	client.setDstRoom("Game");
	//URLを指定して接続開始
	client.start("http://localhost:8000");
	while (true){
		//"Sample Event"に対応するデータが来ているかチェック
		if (client.isUpdated("Sample Event")){
			data = client.getData("Sample Event");//データをsio::message::ptrとして取得
			parseSampleData(data);//データ抽出用関数に渡す
			std::cout << "intVal=" << intVal << ",doubleVal=" << doubleVal << ",stringVal=" << stringVal << std::endl;
			std::cout << "vec3=[" << vec3[0] << "," << vec3[1] << "," << vec3[2] << "]" << std::endl;
			client.sendData("Phenox Data", makeSampleObject());//
		}
		//"vec3 sample"に対応するデータが来ているかチェック
		if (client.isUpdated("vec3 sample")){
			data = client.getData("vec3 sample");//データをsio::message::ptrとして取得
			parseVec3(data);//データ抽出用関数に渡す
			std::cout << "vec3=[" << vec3[0] << "," << vec3[1] << "," << vec3[2] << "]" << std::endl;
		}
		//sleep(100);
	}
	return 0;
}



