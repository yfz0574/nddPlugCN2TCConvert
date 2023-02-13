#pragma once
//template<typename T>
//using rcast = reinterpret_cast<const T*>;
//如果不喜欢用模板，也可以去掉这节，直接用reinterpret_cast<const char*>代替，但不建议直接用(const char*)强转。在C++20之前可以不加强转，20重新定义了u8，需要强转了。
template <typename To, typename From>
const To rcast(const From& obj) {
	return reinterpret_cast<const To>(obj);
}

//QString str = rcast<const char*>(u8"简繁体转换");