#pragma once
//���M�f�[�^�𐶐����邽�߂̃T���v��
#include <sio_client.h>
#include <Object.h>

//���M�f�[�^�𐶐�����T���v���֐��ꗗ(�����炭���͔z�񂩎����^�ő���͂�)
sio::Boolean makeSampleBoolean();//�^�U�l�̏ꍇ
sio::Integer makeSampleInteger();//�����̏ꍇ
sio::Float makeSampleFloat();//���������̏ꍇ
sio::String makeSampleString();//������̏ꍇ
sio::Array makeSampleArray();//�z��̏ꍇ
sio::Object makeSampleObject();//�����^�̏ꍇ


//�^�U�l�^�f�[�^�̐���
sio::Boolean makeSampleBoolean(){
	//�R���X�g���N�^�ŃZ�b�g���Ă��̂܂ܕԂ�
	return sio::Boolean(true);
}
//�����^�f�[�^�̐���
sio::Integer makeSampleInteger(){
	//�R���X�g���N�^�ŃZ�b�g���Ă��̂܂ܕԂ�
	return sio::Integer(555);
}
//���������^�f�[�^�̐���
sio::Float makeSampleFloat(){
	//�R���X�g���N�^�ŃZ�b�g���Ă��̂܂ܕԂ�
	return sio::Float(1e8);
}
//������^�f�[�^�̐���
sio::String makeSampleString(){
	//�R���X�g���N�^�ŃZ�b�g���Ă��̂܂ܕԂ�
	return sio::String("string data");
}

//�z��^�f�[�^�̐���
sio::Array makeSampleArray(){
	sio::Array ret;//�z��^�̏ꍇ��sio::Array
	//Array�ւ̒ǉ���add(value)�ōs���B
	ret.add((int64_t)1)
		.add("string")
		.add(false)
		.add(sio::Array().add(3.0).add(4.0).add(5.0));//Array��Object�̓���q���\
	return ret;
}
//�����^�f�[�^�̐���
sio::Object makeSampleObject(){
	sio::Object ret;
	//Object�ւ̒ǉ���add("key",value)�ōs���B
	ret.add("Bool", true)
		.add("Int1", (int64_t)1)//�����^�͖����I�L���X�g���K�v
		.addInt("Int2", 2)//�L���X�g�������Ȃ����addInt���g��
		.add("Double", 1.0 / 3.0)
		.add("String", "C++")
		.add("Array", sio::Array()
		.addInt(1)
		.add((int64_t)2)
		.add("str"))//Array��Object�̓���q���\
		.add("Object", sio::Object()
		.add("Key", "Value");
	return ret;
}
