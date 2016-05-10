#pragma once
#include <sio_client.h>
#include <Object.h>
class SioClientWrapper{
	//Socket.IO client object
	sio::client client;
	std::string myRoom, dstRoom;
	std::vector<std::string> eventList;
	std::map<std::string, sio::message::ptr> latestData;
	std::map<std::string, bool> updateFlag;

	//WebSocket Connection Listener
	void onOpen(void);
	void onFail(void);
	void onClose(sio::client::close_reason const& reason);
	//Socket Namespace Connection Listener
	void onSocketOpen(std::string const& nsp);
	void onSocketClose(std::string const& nsp);
	//On event
	void OnEvent(sio::event &event);
public:
	SioClientWrapper();
	~SioClientWrapper();
	//�擾�������C�x���g���̃��X�g��ݒ肷��
	void setEventList(const std::vector<std::string>& list);
	//������\�����於���w��
	void setMyRoom(const std::string& name);
	//����ƂȂ镔�������w�肷��
	void setDstRoom(const std::string& name);
	//���������āA�ڑ�����
	void start(const std::string& uri);
	//����C�x���g�̃f�[�^���X�V���ꂽ���ǂ���
	bool isUpdated(const std::string& name);
	//����C�x���g�̍ŐV�f�[�^�𓾂�
	sio::message::ptr getData(const std::string& name);
	//�f�[�^�𑗐M����
	template<typename T>
	void sendData(const std::string& eventName, const T& data){
		client.socket()->emit("transfer", sio::Object()
			.add("event", eventName)
			.add("room", sio::Array().add(dstRoom))
			.add("data", data).pack());
	}
	//��f�[�^(�C�x���g���̂�)�𑗐M����
	void sendData(const std::string& eventName);
};
