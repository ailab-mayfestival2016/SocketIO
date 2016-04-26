/*
 * clientW.cpp
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#include "clientW.h"
#include <iostream>
#include "ScopedGILRelease.h"
namespace sio {

clientW::clientW() {
	// TODO Auto-generated constructor stub

}

clientW::~clientW() {
	// TODO Auto-generated destructor stub
}

void clientW::set_open_listener(const boost::python::object& object){
	//std::cout<<"set_open "<<this<<std::endl;
	this->client::set_open_listener(std::bind([&](const boost::python::object& obj){
		//std::cout<<"ONOPEN"<<std::endl;
		ScopedGILRelease gil_lock;
		boost::python::call<void>(obj.ptr());
	},object));
	//std::cout<<"set_open done"<<std::endl;
}

void clientW::set_fail_listener(const boost::python::object& object){
	this->client::set_fail_listener(std::bind([&](const boost::python::object& obj){
		ScopedGILRelease gil_lock;
		boost::python::call<void>(obj.ptr());
	},object));
}

void clientW::set_reconnecting_listener(const boost::python::object& object){
	this->client::set_reconnecting_listener(std::bind([&](const boost::python::object& obj){
			ScopedGILRelease gil_lock;
			boost::python::call<void>(obj.ptr());
		},object));
}

void clientW::set_reconnect_listener(const boost::python::object& object){
	this->client::set_reconnect_listener(std::bind([&](const boost::python::object& obj,unsigned v1, unsigned v2){
				ScopedGILRelease gil_lock;
				boost::python::call<void>(obj.ptr(),v1,v2);
			},object,std::placeholders::_1,std::placeholders::_2));
}

void clientW::set_close_listener(const boost::python::object& object){
	this->client::set_close_listener(std::bind([&](const boost::python::object& obj,close_reason const& reason){
			ScopedGILRelease gil_lock;
			boost::python::call<void>(obj.ptr(),reason);
		},object,std::placeholders::_1));
}

void clientW::set_socket_open_listener(const boost::python::object& object){
	this->client::set_socket_open_listener(std::bind([&](const boost::python::object& obj,std::string const& nsp){
			//std::cout<<"ONSOCKETOPEN"<<std::endl;
			ScopedGILRelease gil_lock;
			boost::python::call<void>(obj.ptr(),nsp);
		},object,std::placeholders::_1));
}

void clientW::set_socket_close_listener(const boost::python::object& object){
	this->client::set_socket_close_listener(std::bind([&](const boost::python::object& obj,std::string const& nsp){
			//std::cout<<"ONSOCKETCLOSE"<<std::endl;
			ScopedGILRelease gil_lock;
			boost::python::call<void>(obj.ptr(),nsp);
		},object,std::placeholders::_1));
}

void clientW::connect(const std::string& uri){
	this->client::connect(uri);
}
void clientW::connect(const std::string& uri, const boost::python::dict& query){
	std::map<std::string, std::string> newmap;
	int len = boost::python::len(query);
	boost::python::list keys = query.keys();
	for(int i=0; i < len; i++) {
		std::string k = boost::python::extract<std::string>(keys[i]);
		newmap[k] = boost::python::extract<std::string>(query[k]);
	}
	this->client::connect(uri,newmap);
}
const sio::socketW::ptr clientW::socket(void){
	//std::cout<<"socket(void)"<<std::endl;
	return socketW::ptr(new socketW(this->client::socket()));
}
const sio::socketW::ptr clientW::socket(const std::string& nsp){
	//std::cout<<"socket("<<nsp<<")"<<std::endl;
	return socketW::ptr(new socketW(this->client::socket(nsp)));
}

} /* namespace sio */

