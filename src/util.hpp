#pragma once
//template<typename T>
//using rcast = reinterpret_cast<const T*>;
//�����ϲ����ģ�壬Ҳ����ȥ����ڣ�ֱ����reinterpret_cast<const char*>���棬��������ֱ����(const char*)ǿת����C++20֮ǰ���Բ���ǿת��20���¶�����u8����Ҫǿת�ˡ�
template <typename To, typename From>
const To rcast(const From& obj) {
	return reinterpret_cast<const To>(obj);
}

//QString str = rcast<const char*>(u8"����ת��");