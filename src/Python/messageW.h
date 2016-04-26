/*
 * messageW.h
 *
 *  Created on: 2016/04/24
 *      Author: tk
 */

#ifndef SRC_MESSAGEW_H_
#define SRC_MESSAGEW_H_

#include <sio_message.h>
#include <boost/python.hpp>
namespace sio {

class messageW{
public:
	static const boost::python::object get_pyo(const message::ptr& ptr);
	static const message::ptr get_message_ptr(const boost::python::object& obj);
	static const boost::python::list get_pyl(const message::list& ptr);
	static const message::list get_message_list(const boost::python::object& obj);
};

} /* namespace sio */

#endif /* SRC_MESSAGEW_H_ */
