#pragma once
//��M�f�[�^��sio::message::ptr����l�𒊏o���邽�߂̃T���v��
#include <sio_client.h>
#include <Object.h>


/*���o�T���v���ł̊i�[��̕ϐ�*/
int64_t intVal;
double doubleVal;
double vec3[3];
std::string stringVal;
/*���o�T���v���ł̊i�[��̕ϐ�*/
//�擾�����f�[�^��sio::message::ptr���璊�o����T���v��
void parseSampleData(sio::message::ptr data);
//3�����x�N�g�������M����Ă���ꍇ�̗�
void parseVec3(sio::message::ptr data);

void parseSampleData(sio::message::ptr data){
	sio::message::ptr ptr;
	//sio::message::ptr::get_XXX()��XXX�^�̒l�𓾂���̂ŁA
	//�e�^�ɍ��킹�Ĉȉ��̂悤�ɏ����l�𓾂Ă����B
	/*bool b = ptr->get_bool();
	int64_t i = ptr->get_int();
	double d = ptr->get_double();
	std::string s = ptr->get_string();
	std::vector<sio::message::ptr> vector = ptr->get_vector();
	std::map<std::string, sio::message::ptr> map = ptr->get_map();*/

	//�Ⴆ�΁A{"Int":1,"Double":3.0,"Array":[5,6,7,"end"]}�Ƃ���Object�������Ă���ꍇ�́A�ȉ��̂悤�ɒl�𒊏o���Ă����B
	//�l�̊i�[��͊e���Œ�`���Ă������ƁB
	std::map<std::string, sio::message::ptr> map = data->get_map();//�ŊO����Object����map�𒊏o
	intVal = map["Int"]->get_int();//�L�["Int"�̒l�𒊏o
	doubleVal = map["Double"]->get_double();//�L�["Double"�̒l�𒊏o
	std::vector<sio::message::ptr> vector = map["Array"]->get_vector();//�L�["Array"��Array����vector�𒊏o
	for (int i = 0; i < 3; ++i){
		vec3[i] = vector[i]->get_double();//vector�̐擪3��double�Ȃ̂�double�^�z��ɑ��
	}
	stringVal = vector[3]->get_string();//vector��4�߂�string�Ȃ̂�std::string�Ƃ��Ē��o
}

//3�����x�N�g�������M����Ă���ꍇ�̗�
void parseVec3(sio::message::ptr data){
	//[0.2,-2.1,3.4]�̂悤�ɗv�f��3�̎����z��Ƃ��Ă���ꍇ
	std::vector<sio::message::ptr> vector = data->get_vector();//�O����Array����vector�𒊏o
	for (int i = 0; i < 3; ++i){
		vec3[i] = vector[i]->get_double();//vector�̗v�f�����ɒ��o����double�^�z��ɑ��
	}
}