/*
 * socketW.cpp
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#include "socketW.h"
#include "messageW.h"
#include <exception>
#include "ScopedGILRelease.h"
namespace sio {

eventW::eventW(event& e):inner(e){
}
const std::string& eventW::get_nsp() const{
	return inner.get_nsp();
}

const std::string& eventW::get_name() const{
	return inner.get_name();
}
const boost::python::object eventW::get_message() const{
	//std::cout<<""<<std::endl;
	return messageW::get_pyo(inner.get_message());
}

const boost::python::object eventW::get_messages() const{
	message::list list=inner.get_messages();
	if(list.size()==1){
		return messageW::get_pyo(list[0]);
	}
	return messageW::get_pyl(list);
}
bool eventW::need_ack() const{
	return inner.need_ack();
}
void eventW::put_ack_message(boost::python::list const& ack_message){
	inner.put_ack_message(messageW::get_message_list(ack_message));
}

boost::python::list const eventW::get_ack_message() const{
	return messageW::get_pyl(inner.get_ack_message());
}

socketW::socketW(socket::ptr ptr){
	inner=ptr;
}

socketW::~socketW() {
}

void socketW::on(std::string const& event_name,const boost::python::object& func){
	//std::cout<<"onE func="<<&func<<std::endl;
	socket::event_listener li=std::bind(
			[&](const boost::python::object& f,event& e){
				eventW::ptr tmp=eventW::ptr(new eventW(e));
				ScopedGILRelease gil_lock;
				boost::python::call<void>(f.ptr(),tmp);
			},func,std::placeholders::_1);
	inner->on(event_name,li);
}

/*void socketW::on(std::string const& event_name,socketW::event_listener_auxW const& func){
	std::cout<<"onAux"<<std::endl;
	inner->on(event_name,
		[&](const std::string& name,message::ptr const& message,bool need_ack, message::list& ack_message){
			boost::python::object messageW=messageW::get_pyo(message);
			boost::python::object ack_messageW;
			func(name,messageW,need_ack,ack_messageW);
			ack_message=messageW::get_message_list(ack_messageW);
		});
}*/

void socketW::off(std::string const& event_name){
	inner->off(event_name);
}

void socketW::off_all(){
	inner->off_all();
}

void socketW::close(){
	inner->close();
}

void socketW::on_error(socketW::error_listenerW const& l){
	inner->on_error([&](message::ptr const& message){l(messageW::get_pyo(message));});
}

void socketW::off_error(){
	inner->off_error();
}
void socketW::emit(std::string const& name){
	inner->emit(name);
}
void socketW::emit(std::string const& name, boost::python::object const& msglist){
	inner->emit(name,messageW::get_message_list(msglist));
}
void socketW::emit(std::string const& name, boost::python::object const& msglist, const boost::python::object& ack){
	inner->emit(name,messageW::get_message_list(msglist),std::bind(
			[&](const boost::python::object& f,message::list const& ack_message){
				ScopedGILRelease gil_lock;
				boost::python::call<void>(f.ptr(),messageW::get_pyl(ack_message));
			},ack,std::placeholders::_1));
}

std::string const& socketW::get_namespace() const{
	return inner->get_namespace();
}

} /* namespace sio */

