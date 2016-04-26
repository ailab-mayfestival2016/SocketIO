/*
 * clientW.h
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#ifndef SRC_CLIENTW_H_
#define SRC_CLIENTW_H_
#include <sio_client.h>
#include "socketW.h"
#include <boost/python.hpp>
namespace sio {

class clientW
:public client{
public:
	clientW();
	virtual ~clientW();
	//set listeners and event bindings.
    void set_open_listener(const boost::python::object& object);

    void set_fail_listener(const boost::python::object& object);

    void set_reconnecting_listener(const boost::python::object& object);

    void set_reconnect_listener(const boost::python::object& object);

    void set_close_listener(const boost::python::object& object);

    void set_socket_open_listener(const boost::python::object& object);

    void set_socket_close_listener(const boost::python::object& object);

    //void clear_con_listeners();

    //void clear_socket_listeners();

	// Client Functions - such as send, etc.
	void connect(const std::string& uri);

	void connect(const std::string& uri, const boost::python::dict& query);

    //void set_reconnect_attempts(int attempts);

    //void set_reconnect_delay(unsigned millis);

    //void set_reconnect_delay_max(unsigned millis);

    const sio::socketW::ptr socket(void);
    const sio::socketW::ptr socket(const std::string& nsp);

    // Closes the connection
    //void close();

    //void sync_close();

    //bool opened() const;

    //std::string const& get_sessionid() const;
};

} /* namespace sio */

#endif /* SRC_CLIENTW_H_ */
