#pragma once
#include <sio_client.h>
#include <Object.h>
class SampleClient{
	//Socket.IO client object
	sio::client client;

	int cnt;
public:
	SampleClient();
	virtual ~SampleClient();
	//initialize and connect Socket.IO client
	virtual void start(const std::string& uri);
	//WebSocket Connection Listener
	virtual void onOpen(void);
	virtual void onFail(void);
	virtual void onClose(sio::client::close_reason const& reason);
	//Socket Namespace Connection Listener
	virtual void onSocketOpen(std::string const& nsp);
	virtual void onSocketClose(std::string const& nsp);
	//On "server push" handler.
	void OnServerPush(sio::event &event);
};
