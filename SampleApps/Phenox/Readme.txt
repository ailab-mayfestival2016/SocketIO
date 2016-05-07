Phenox用のデータ送受信のひな形

ファイル一覧
	main.cpp				メイン関数。whileループが回る
	SioClientWrapper.h		sio::clientのラッパー
	SioClientWrapper.cpp	sio::clientのラッパー
	DataMaker.h				送信データを生成するためのサンプル
	Parser.h				受信データから値を抽出するためのサンプル
	※MakeFileは分からんので付属しません

必要なファイル
/Prebuilt/Linux_ARM/Cpp/include
	/Object.h
	/sio_client.h
	/sio_message.h
	/sio_socket.h
/Prebuilt/Linux_ARM/Cpp/lib
	/Debug/libsioclient.a(デバッグビルドの場合)
	/Release/libsioclient.a(リリースビルドの場合)

必要なオプション
・CXX_FLAGSに-std=C++0xが必要
・もしかしたらpthreadが必要かもしれない

初期化の手順
	1.SioClientWrapperクラスのインスタンスを生成
	2.受信するイベント名一覧をstd::vector<std::string>として渡す
	3.自身を表す部屋名を設定する
	4.データの送信宛先となる部屋名を設定する
	5.URLを指定して接続する
