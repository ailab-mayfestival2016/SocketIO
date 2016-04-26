/*
 * JSON.cpp
 *
 *  Created on: 2016/04/23
 *      Author: T-Kawai0922
 */

#include "JSON.h"

Array::Array()
:data(sio::array_message::create()) {

}

Array::~Array() {

}
Array& Array::addInt(const int64_t& value){
	data->get_vector().push_back(sio::int_message::create(value));
	return *this;
}
Array& Array::add(const int64_t& value){
	data->get_vector().push_back(sio::int_message::create(value));
	return *this;
}
Array& Array::add(const double& value){
	data->get_vector().push_back(sio::double_message::create(value));
	return *this;
}
Array& Array::add(const std::string& value){
	data->get_vector().push_back(sio::string_message::create(value));
	return *this;
}
Array& Array::add(const JSON& value){
	data->get_vector().push_back(value.pack());
	return *this;
}
Array& Array::add(const Array& value){
	data->get_vector().push_back(value.data);
	return *this;
}
sio::message::ptr Array::pack(void) const{
	return data;
}

JSON::JSON()
:data(sio::object_message::create()) {

}

JSON::~JSON() {

}
JSON& JSON::addInt(const std::string& key,const int64_t& value){
	data->get_map()[key]=sio::int_message::create(value);
	return *this;
}
JSON& JSON::add(const std::string& key,const int64_t& value){
	data->get_map()[key]=sio::int_message::create(value);
	return *this;
}
JSON& JSON::add(const std::string& key,const double& value){
	data->get_map()[key]=sio::double_message::create(value);
	return *this;
}
JSON& JSON::add(const std::string& key,const std::string& value){
	data->get_map()[key]=sio::string_message::create(value);
	return *this;
}
JSON& JSON::add(const std::string& key,const JSON& value){
	data->get_map()[key]=value.data;
	return *this;
}
JSON& JSON::add(const std::string& key,const Array& value){
	data->get_map()[key]=value.pack();
	return *this;
}
sio::message::ptr JSON::pack(void) const{
	return data;
}
const std::map<std::string,sio::message::ptr>& JSON::parse(sio::event& event){
	return event.get_message()->get_map();
}
std::string print_value(sio::message::ptr data) {
	std::string ret;
	int cnt;
	 switch(data->get_flag()) {
	 case sio::message::flag_null:return "Null";break;
	 case sio::message::flag_boolean: return std::to_string(data->get_bool()); break;
	 case sio::message::flag_integer: return std::to_string(data->get_int()); break;
	 case sio::message::flag_double: return std::to_string(data->get_double()); break;
	 case sio::message::flag_string: return "\""+data->get_string()+"\""; break;
	 case sio::message::flag_binary: return "binary(string)"; break;
	 case sio::message::flag_array:
		 ret="[";
		 cnt=0;
		 for(auto e:data->get_vector()){
			 if(cnt>0){
			 	ret+=",";
			 }
			 ret+=print_value(e);
			 cnt++;
		 }
		 ret+="]";
		 return ret;
		 break;
	 case sio::message::flag_object:
		 ret="{";
		 cnt=0;
		 for(auto e:data->get_map()){
			 if(cnt>0){
				 ret+=",";
			 }
			 ret+="'"+e.first+"':"+print_value(e.second);
			 cnt++;
		 }
		 ret+="}";
		 return ret;
		 break;
	 }
	 return "";
}
std::ostream& operator<<(std::ostream& os, const sio::message::ptr& data)
{
    os << print_value(data);
    return os;
}
std::string JSON::toString(void) const{
	return print_value(data);
}
