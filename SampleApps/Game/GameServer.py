#-*-coding:utf-8-*-

from sioclient import SioClient

if __name__ == '__main__':
	recvDataCon=[] #コントローラからのデータキュー
	recvDataOther=[] #他からのデータキュー
	#通信の初期化
	client=SioClient()
	#受信するイベント名一覧をリストとしてclientに渡す
	eventList=["Sample Event","Controller Data","Phenox Data"]
	client.setEventList(eventList)
	#自身を表す部屋名を設定する(Game Serverなら例えば"Game"と決める)
	client.setMyRoom("Game")
	#受信データを格納するキューを追加する
	client.setDataQueue(recvDataCon,["Controller Data"])#第二引数に与えたイベントの受信データのみが追加される
	client.setDataQueue(recvDataOther)#第二引数を与えなければ、対応キューを登録していないイベントの受信データ用のデフォルトキューとして働く
	#URLを指定して接続開始
	client.start("http://localhost:8000")
	cnt=0
	while True:
		import time
		if(len(recvDataCon)>0): #コントローラからのデータがあるとき
			eventName=recvDataCon[0][0]
			data=recvDataCon[0][1]
			print eventName,",",data
			del recvDataCon[0]
		if(len(recvDataOther)>0): #コントローラからのデータがあるとき
			eventName=recvDataOther[0][0]
			data=recvDataOther[0][1]
			print eventName,",",data
			del recvDataOther[0]
		client.sendData("Game Data",["Client"],[(1,2,3),(4,5,6),(7,8,9)])
		client.sendData("Sample Event",["Phenox"],{"Int":cnt,"Double":3.0,"Array":[5,6,7,"end"]})
		cnt+=1
		time.sleep(1./30.)
