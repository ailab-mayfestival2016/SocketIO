Game Server用のデータ送受信のひな形

ファイル一覧
	GameServer.py			メインループ。whileループが回る
	sioclient.py			sioclientCpp.pydのラッパー

必要なファイル
/Prebuilt/Windows/Win32/Python/sioclientCpp.pyd(32ビットの場合)
/Prebuilt/Windows/Win64/Python/sioclientCpp.pyd(64ビットの場合)

使い方
sioclientCpp.pydとsioclient.pyをメインのファイルと同じディレクトリにおいてsioclientをimportする。

初期化の手順
	1.SioClientクラスのインスタンスを生成
	2.受信するイベント名一覧をリストとして渡す
	3.自身を表す部屋名を設定する
	4.受信データを格納するキューを追加する
	5.URLを指定して接続する
