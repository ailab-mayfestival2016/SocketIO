#include <iostream>
#include "SioClientWrapper.h"
#include "Parser.h"//��M�f�[�^��sio::message::ptr����l�𒊏o���邽�߂̃T���v��
#include "DataMaker.h"//���M�f�[�^�𐶐����邽�߂̃T���v��

int main()
{
	SioClientWrapper client;
	sio::message::ptr data;
	//��������C�x���g���ꗗ��std::vector<std::string>�Ƃ���client�ɓn��
	std::vector<std::string> eventList(0);
	eventList.push_back("Sample Event");
	eventList.push_back("vec3 sample");
	client.setEventList(eventList);
	//���g��\����������ݒ肷��(Phenox�Ȃ�Ⴆ��"Phenox"�ƌ��߂�)
	client.setMyRoom("Phenox");
	//�f�[�^�̑��M����ƂȂ镔������ݒ肷��(Game�T�[�o�Ȃ�Ⴆ��"Game")
	client.setDstRoom("Game");
	//URL���w�肵�Đڑ��J�n
	client.start("http://localhost:8000");
	while (true){
		//"Sample Event"�ɑΉ�����f�[�^�����Ă��邩�`�F�b�N
		if (client.isUpdated("Sample Event")){
			data = client.getData("Sample Event");//�f�[�^��sio::message::ptr�Ƃ��Ď擾
			parseSampleData(data);//�f�[�^���o�p�֐��ɓn��
			std::cout << "intVal=" << intVal << ",doubleVal=" << doubleVal << ",stringVal=" << stringVal << std::endl;
			std::cout << "vec3=[" << vec3[0] << "," << vec3[1] << "," << vec3[2] << "]" << std::endl;
			client.sendData("Phenox Data", makeSampleObject());//
		}
		//"vec3 sample"�ɑΉ�����f�[�^�����Ă��邩�`�F�b�N
		if (client.isUpdated("vec3 sample")){
			data = client.getData("vec3 sample");//�f�[�^��sio::message::ptr�Ƃ��Ď擾
			parseVec3(data);//�f�[�^���o�p�֐��ɓn��
			std::cout << "vec3=[" << vec3[0] << "," << vec3[1] << "," << vec3[2] << "]" << std::endl;
		}
		//sleep(100);
	}
	return 0;
}



