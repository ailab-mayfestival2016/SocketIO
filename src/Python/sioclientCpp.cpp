/*
 * socketClient.cpp
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include "ScopedGILRelease.h"
#include "socketW.h"
#include "clientW.h"

void (sio::clientW::*connectS)(const std::string&)=&sio::clientW::connect;
void (sio::clientW::*connectSQ)(const std::string&,const boost::python::dict&)=&sio::clientW::connect;
sio::socketW::ptr const (sio::clientW::*socketV)(void)=&sio::clientW::socket;
sio::socketW::ptr const (sio::clientW::*socketS)(const std::string&)=&sio::clientW::socket;

void (sio::socketW::*emitN)(std::string const&)=&sio::socketW::emit;
void (sio::socketW::*emitNM)(std::string const&,const boost::python::object&)=&sio::socketW::emit;
void (sio::socketW::*emitNMA)(std::string const&,const boost::python::object&,const boost::python::object&)=&sio::socketW::emit;

#ifdef SIO_TLS
#define SIO_PYTHON_MODULE_NAME sioclientCpp_tls
#else
#define SIO_PYTHON_MODULE_NAME sioclientCpp
#endif
BOOST_PYTHON_MODULE(SIO_PYTHON_MODULE_NAME)
{
	using namespace boost::python;
	PyEval_InitThreads();
	scope module_level;

	scope scope_clientW=class_<sio::clientW,boost::noncopyable>("Client")
		.def("set_open_listener", &sio::clientW::set_open_listener)
		.def("set_fail_listener", &sio::clientW::set_fail_listener)
		.def("set_reconnecting_listener", &sio::clientW::set_reconnecting_listener)
		.def("set_reconnect_listener", &sio::clientW::set_reconnect_listener)
		.def("set_close_listener", &sio::clientW::set_close_listener)
		.def("set_socket_open_listener", &sio::clientW::set_socket_open_listener)
		.def("set_socket_close_listener",&sio::clientW::set_socket_close_listener)
		.def("clear_con_listeners",&sio::clientW::clear_con_listeners)
		.def("clear_socket_listeners",&sio::clientW::clear_socket_listeners)
		.def("connect",connectS)
		.def("connect",connectSQ)
		.def("set_reconnect_attempts",&sio::clientW::set_reconnect_attempts)
		.def("set_reconnect_delay",&sio::clientW::set_reconnect_delay)
		.def("set_reconnect_delay_max",&sio::clientW::set_reconnect_delay_max)
		.def("socket",socketV)
		.def("socket",socketS)
		.def("close",&sio::clientW::close)
		.def("sync_close",&sio::clientW::sync_close)
		.def("opened",&sio::clientW::opened)
		.def("get_sessionid",&sio::clientW::get_sessionid,return_value_policy<copy_const_reference>())
		;
	enum_<sio::clientW::close_reason>("close_reason")
		.value("close_reason_normal", sio::clientW::close_reason::close_reason_normal)
		.value("close_reason_drop", sio::clientW::close_reason::close_reason_drop)
		.export_values()
		;
	scope within(module_level);
	register_ptr_to_python<std::shared_ptr<sio::eventW>>();
	class_<sio::eventW,std::shared_ptr<sio::eventW>,boost::noncopyable>("Event",no_init)
		.def("get_nsp",&sio::eventW::get_nsp,return_value_policy<copy_const_reference>())
		.def("get_name",&sio::eventW::get_name,return_value_policy<copy_const_reference>())
		.def("get_message",&sio::eventW::get_message)
		.def("get_messages",&sio::eventW::get_messages)
		.def("need_ack",&sio::eventW::need_ack)
		.def("put_ack_message",&sio::eventW::put_ack_message)
		.def("get_ack_message",&sio::eventW::get_ack_message);
	register_ptr_to_python<std::shared_ptr<sio::socketW>>();
	class_<sio::socketW,std::shared_ptr<sio::socketW>,boost::noncopyable>("Socket",no_init)
		//.def("on",+[](sio::socketW::ptr& self,std::string const& event_name, const boost::python::object& object) {
		//	self->on(event_name,object);
		//})
		.def("on",&sio::socketW::on)
		//.def("on",onAux)
		.def("off",&sio::socketW::off)
		.def("off_all",&sio::socketW::off_all)
		.def("close",&sio::socketW::close)
		.def("on_error",&sio::socketW::on_error)
		.def("off_error",&sio::socketW::off_error)
		//.def("emit",&sio::socketW::emit)
		.def("emit",emitN)
		.def("emit",emitNM)
		.def("emit",emitNMA)
		/*.def("emit",+[](sio::socketW::ptr& self,std::string const& name) {
			self->emit(name);
		})
		.def("emit",+[](sio::socketW::ptr& self,std::string const& name, boost::python::object const& msglist) {
			self->emit(name,msglist);
		})
		.def("emit",+[](sio::socketW::ptr& self,std::string const& name, boost::python::object const& msglist, boost::python::object& object) {
			self->emit(name,msglist,object);
		})*/
		.def("get_namespace",&sio::socketW::get_namespace,return_value_policy<copy_const_reference>());
}


