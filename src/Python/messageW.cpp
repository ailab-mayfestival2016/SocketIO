/*
 * messageW.cpp
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#include "messageW.h"

namespace sio {

const boost::python::object messageW::get_pyo(const message::ptr& ptr){
	boost::python::list list;
	boost::python::tuple tuple;
	boost::python::dict dict;
	switch(ptr->get_flag()) {
	case sio::message::flag_null:
		return boost::python::object();
		break;
	case sio::message::flag_boolean:
		return boost::python::object(ptr->get_bool());
		break;
	case sio::message::flag_integer:
		return boost::python::object(ptr->get_int());
		break;
	case sio::message::flag_double:
		return boost::python::object(ptr->get_double());
		break;
	case sio::message::flag_string:
		return boost::python::object(ptr->get_string());
		break;
	case sio::message::flag_binary:
		return boost::python::object("binary(string)");
		break;
	case sio::message::flag_array:
		for(auto&& e:ptr->get_vector()){
			list.append(get_pyo(e));
		}
		tuple=boost::python::tuple(list);
		return tuple;
		
		break;
	case sio::message::flag_object:
		for(auto&& e:ptr->get_map()){
			dict[e.first]=get_pyo(e.second);
		}
		return dict;
		break;
	}
	return boost::python::object();
}
const message::ptr messageW::get_message_ptr(const boost::python::object& obj){
	boost::python::extract<bool> b(obj);
	if(PyBool_Check(obj.ptr())){
	    return bool_message::create(b());
	}
	boost::python::extract<int64_t> i(obj);
	if (i.check()) {
	    return int_message::create(i());
	}
	boost::python::extract<double> d(obj);
	if (d.check()) {
	    return double_message::create(d());
	}
	boost::python::extract<std::string> s(obj);
	if (s.check()) {
	    return string_message::create(s());
	}
	boost::python::extract<boost::python::list> l(obj);
	if (l.check()) {
		boost::python::list list=l();
		message::ptr ret=array_message::create();
		int len = boost::python::len(list);
		for(int i=0; i<len; i++) {
			ret->get_vector().push_back(messageW::get_message_ptr(list[i]));
		}
	    return ret;
	}
	boost::python::extract<boost::python::tuple> t(obj);
	if (t.check()) {
		boost::python::tuple tuple=t();
		message::ptr ret=array_message::create();
		int len = boost::python::len(tuple);
		for(int i=0; i<len; i++) {
			ret->get_vector().push_back(messageW::get_message_ptr(tuple[i]));
		}
	    return ret;
	}
	boost::python::extract<boost::python::dict> m(obj);
	if (m.check()) {
		boost::python::dict dict=m();
		message::ptr ret=object_message::create();
		int len = boost::python::len(dict);
		boost::python::list keys = dict.keys();
		for(int i=0; i<len; i++) {
			std::string k = boost::python::extract<std::string>(keys[i]);
			ret->get_map()[k]=messageW::get_message_ptr(dict[k]);
		}
		return ret;
	}
	if (obj.ptr() == Py_None){
		return null_message::create();
	}
	PyErr_SetString(PyExc_TypeError,"Incompatible type of message.");
	//std::cout<<"No type hit."<<std::endl;
	boost::python::throw_error_already_set();
	return null_message::create();
}
const boost::python::list messageW::get_pyl(const message::list& list){
	return boost::python::extract<boost::python::list>(get_pyo(list.to_array_message()));
}
const message::list messageW::get_message_list(const boost::python::object& obj){
	message::list ret;
	boost::python::extract<boost::python::list> l(obj);
	if (l.check()) {
		//std::cout<<"given list"<<std::endl;
		boost::python::list list=l();
		int len = boost::python::len(list);
		for(int i=0; i<len; i++) {
			ret.push(get_message_ptr(list[i]));
		}
    }else{
    	//std::cout<<"given other"<<std::endl;
    	ret.push(get_message_ptr(obj));
    }
	return ret;
}

} /* namespace sio */
