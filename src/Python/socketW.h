/*
 * socketW.h
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#ifndef SOCKETW_H_
#define SOCKETW_H_
#include <sio_socket.h>
#include <boost/python.hpp>
namespace sio {

class eventW{
public:
	event& inner;
public:
	typedef std::shared_ptr<eventW> ptr;
	eventW(event& e);

	const std::string& get_nsp() const;

	const std::string& get_name() const;

	const boost::python::object get_message() const;
	//const message::ptr& get_message() const;

	const boost::python::object get_messages() const;
	//const message::list& get_messages() const;

	bool need_ack() const;

	void put_ack_message(boost::python::list const& ack_message);
	//void put_ack_message(message::list const& ack_message);

	boost::python::list const get_ack_message() const;
	//message::list const& get_ack_message() const;
};

class socketW{
	socket::ptr inner;
public:
	typedef std::shared_ptr<socketW> ptr;
	typedef std::function<void(const std::string& name,boost::python::object const& message,bool need_ack, boost::python::object& ack_message)> event_listener_auxW;
	//typedef std::function<void(const std::string& name,message::ptr const& message,bool need_ack, message::list& ack_message)> event_listener_aux;

	typedef std::function<void(eventW::ptr& event)> event_listenerW;
	//typedef std::function<void(event& event)> event_listener;

	typedef std::function<void(boost::python::object const& message)> error_listenerW;
	//typedef std::function<void(message::ptr const& message)> error_listener;
	socketW(socket::ptr ptr);
    ~socketW();

    void on(std::string const& event_name,const boost::python::object& func);

    //void on(std::string const& event_name,socketW::event_listener_auxW const& func);

    void off(std::string const& event_name);

    void off_all();

    void close();

    void on_error(socketW::error_listenerW const& l);

    void off_error();

    void emit(std::string const& name);
    void emit(std::string const& name, boost::python::object const& msglist);
    void emit(std::string const& name, boost::python::object const& msglist, const boost::python::object& ack);
    //void emit(std::string const& name, message::list const& msglist = nullptr, std::function<void (message::list const&)> const& ack = nullptr);

    std::string const& get_namespace() const;
};

} /* namespace sio */

#endif /* SOCKETW_H_ */
