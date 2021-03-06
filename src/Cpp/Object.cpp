/*
 * Object.cpp
 *
 *  Created on: 2016/04/23
 *      Author: T-Kawai0922
 */

#include "Object.h"
namespace sio{
	//Null
	Null::Null()
	:data(sio::null_message::create()) {
	
	}
	Null::~Null(){}
	sio::message::ptr Null::pack(void) const{
		return data;
	}
	//Boolean
	Boolean::Boolean(const bool& value)
	:data(sio::bool_message::create(value)) {
	
	}
	Boolean::~Boolean(){}
	sio::message::ptr Boolean::pack(void) const{
		return data;
	}
	//Integer
	Integer::Integer(const int64_t& value)
	:data(sio::int_message::create(value)) {
	
	}
	Integer::~Integer(){}
	sio::message::ptr Integer::pack(void) const{
		return data;
	}
	//Float
	Float::Float(const double& value)
	:data(sio::double_message::create(value)) {
	
	}
	Float::~Float(){}
	sio::message::ptr Float::pack(void) const{
		return data;
	}
	//String
	String::String(const std::string& value)
	:data(sio::string_message::create(value)) {
	
	}
	String::~String(){}
	sio::message::ptr String::pack(void) const{
		return data;
	}
	
	
	
	Array::Array()
	:data(sio::array_message::create()) {
	
	}
	
	Array::~Array() {
	
	}
	Array& Array::add(const Null& value){
		data->get_vector().push_back(value.pack());
		return *this;
	}
	Array& Array::add(const bool& value){
		data->get_vector().push_back(sio::bool_message::create(value));
		return *this;
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
	Array& Array::add(const Object& value){
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
	
	Object::Object()
	:data(sio::object_message::create()) {
	
	}
	
	Object::~Object() {
	
	}
	Object& Object::add(const std::string& key,const Null& value){
		data->get_map()[key]=value.pack();
		return *this;
	}
	Object& Object::add(const std::string& key,const bool& value){
		data->get_map()[key]=sio::bool_message::create(value);
		return *this;
	}
	Object& Object::addInt(const std::string& key,const int64_t& value){
		data->get_map()[key]=sio::int_message::create(value);
		return *this;
	}
	Object& Object::add(const std::string& key,const int64_t& value){
		data->get_map()[key]=sio::int_message::create(value);
		return *this;
	}
	Object& Object::add(const std::string& key,const double& value){
		data->get_map()[key]=sio::double_message::create(value);
		return *this;
	}
	Object& Object::add(const std::string& key,const std::string& value){
		data->get_map()[key]=sio::string_message::create(value);
		return *this;
	}
	Object& Object::add(const std::string& key,const Object& value){
		data->get_map()[key]=value.data;
		return *this;
	}
	Object& Object::add(const std::string& key,const Array& value){
		data->get_map()[key]=value.pack();
		return *this;
	}
	sio::message::ptr Object::pack(void) const{
		return data;
	}
	const std::map<std::string,sio::message::ptr>& Object::parse(sio::event& event){
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
	std::string Object::toString(void) const{
		return print_value(data);
	}
};