/*
 * JSON.h
 * JSONデータを送信するときの書き方を簡略化するためのクラス
 *  Created on: 2016/04/23
 *      Author: T-Kawai0922
 */

#ifndef JSON_H_
#define JSON_H_
#include <string>
#include <stdint.h>
#include <map>
#include <sio_client.h>
class JSON;
class Array{
	sio::message::ptr data;
public:
	Array();
	virtual ~Array();
	Array& addInt(const int64_t& value);
	Array& add(const int64_t& value);
	Array& add(const double& value);
	Array& add(const std::string& value);
	Array& add(const JSON& value);
	Array& add(const Array& value);
	sio::message::ptr pack(void) const;
};
class JSON {
	sio::message::ptr data;
public:
	JSON();
	virtual ~JSON();
	JSON& addInt(const std::string& key,const int64_t& value);
	JSON& add(const std::string& key,const int64_t& value);
	JSON& add(const std::string& key,const double& value);
	JSON& add(const std::string& key,const std::string& value);
	JSON& add(const std::string& key,const JSON& value);
	JSON& add(const std::string& key,const Array& value);
	sio::message::ptr pack(void) const;
	static const std::map<std::string,sio::message::ptr>& parse(sio::event& event);
	std::string toString(void) const;
};
std::ostream& operator<<(std::ostream& os, const sio::message::ptr& data);
#endif /* JSON_H_ */
