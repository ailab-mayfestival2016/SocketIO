#pragma once
//送信データを生成するためのサンプル
#include <sio_client.h>
#include <Object.h>

//送信データを生成するサンプル関数一覧(おそらく大抵は配列か辞書型で送るはず)
sio::Boolean makeSampleBoolean();//真偽値の場合
sio::Integer makeSampleInteger();//整数の場合
sio::Float makeSampleFloat();//浮動小数の場合
sio::String makeSampleString();//文字列の場合
sio::Array makeSampleArray();//配列の場合
sio::Object makeSampleObject();//辞書型の場合


//真偽値型データの生成
sio::Boolean makeSampleBoolean(){
	//コンストラクタでセットしてそのまま返す
	return sio::Boolean(true);
}
//整数型データの生成
sio::Integer makeSampleInteger(){
	//コンストラクタでセットしてそのまま返す
	return sio::Integer(555);
}
//浮動小数型データの生成
sio::Float makeSampleFloat(){
	//コンストラクタでセットしてそのまま返す
	return sio::Float(1e8);
}
//文字列型データの生成
sio::String makeSampleString(){
	//コンストラクタでセットしてそのまま返す
	return sio::String("string data");
}

//配列型データの生成
sio::Array makeSampleArray(){
	sio::Array ret;//配列型の場合はsio::Array
	//Arrayへの追加はadd(value)で行う。
	ret.add((int64_t)1)
		.add("string")
		.add(false)
		.add(sio::Array().add(3.0).add(4.0).add(5.0));//ArrayやObjectの入れ子も可能
	return ret;
}
//辞書型データの生成
sio::Object makeSampleObject(){
	sio::Object ret;
	//Objectへの追加はadd("key",value)で行う。
	ret.add("Bool", true)
		.add("Int1", (int64_t)1)//整数型は明示的キャストが必要
		.addInt("Int2", 2)//キャストしたくなければaddIntを使う
		.add("Double", 1.0 / 3.0)
		.add("String", "C++")
		.add("Array", sio::Array()
		.addInt(1)
		.add((int64_t)2)
		.add("str"))//ArrayやObjectの入れ子も可能
		.add("Object", sio::Object()
		.add("Key", "Value");
	return ret;
}
