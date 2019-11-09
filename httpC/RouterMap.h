#ifndef __RouterMap__
#define __RouterMap__
#include <string>
#include <map>
#include <iostream>
#include "Request.h"
#include "Response.h"


class RouterBaseClass
{
public:
	RouterBaseClass() {}
	virtual void doServer(Request& req, Response &reps) { std::cout << "I'm base!" << std::endl; }
	virtual ~RouterBaseClass() {}
};



// 使用模板，每个基类单独生成一个 ClassRegister
// 好处是需要反射的类不需要去继承 Object 对象
// ClassRegister 用来管理类名->类构造函数的映射，对外提供根据类名构造对象对函数
template<typename ClassName>
class ClassRegister {
public:
	typedef ClassName* (*Constructor)(void);
private:
	typedef std::map<std::string, Constructor> RouterMap;
	RouterMap constructor_map_;
public:
	// 添加新类的构造函数
	void AddConstructor(const std::string router, Constructor constructor) {
		typename RouterMap::iterator it = constructor_map_.find(router);
		if (it != constructor_map_.end()) {
			std::cout << "error!";
			return;
		}
		constructor_map_[router] = constructor;
	}
	// 根据类名构造对象
	ClassName* CreateObject(const std::string router) const {
		typename RouterMap::const_iterator it = constructor_map_.find(router);
		if (it == constructor_map_.end()) {
			return nullptr;
		}
		return (*(it->second))();
	}
};

// 用来保存每个基类的 ClassRegister static 对象，用于全局调用
template <typename ClassName>
ClassRegister<ClassName>& GetRegister() {
	static ClassRegister<ClassName> class_register;
	return class_register;
}

// 每个类的构造函数，返回对应的base指针
template <typename SubClassName>
RouterBaseClass* NewObject() {
	return new SubClassName();
}

// 为每个类反射提供一个 helper，构造时就完成反射函数对注册

class ClassRegisterHelper {
public:
	ClassRegisterHelper(
		const std::string router,
		typename ClassRegister<RouterBaseClass>::Constructor constructor) {
		GetRegister<RouterBaseClass>().AddConstructor(router, constructor);
	}
	~ClassRegisterHelper() {}
};

// 提供反射类的注册宏，使用时仅提供基类类名和派生类类名
#define RegisterRouter( router , subClass ) \
  static ClassRegisterHelper \
      subClass##_register_helper( \
          router, NewObject<subClass>);

// 创建对象的宏
#define ForRouter( router ) \
  GetRegister< RouterBaseClass >().CreateObject( router )


#endif

