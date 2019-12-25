/*单例模式实现*/
/*version1:懒汉式*/
class Singleton
{
public:
	static Singleton* getInstance();
private:
	static Singleton* instance;
	Singleton() {};
};
//静态成员函数要在类外初始化
Singleton* Singleton::instance = nullptr;
Singleton* Singleton::getInstance() {
	if (instance == nullptr)
		instance = new Singleton();
	return instance;
}
/*version2:饿汉式*/
class EagerSingleton
{
public:
	static EagerSingleton* getInstance();
private:
	EagerSingleton() {};
	static EagerSingleton* instance;
};
EagerSingleton* EagerSingleton::instance = new EagerSingleton();
EagerSingleton* EagerSingleton::getInstance()
{
	return instance;
}
/*version3:懒汉式加双重锁保证线程安全*/
#include <pthread.h>
class MuteEagerSingleton
{
private:
	static MuteEagerSingleton* instance;
	MuteEagerSingleton();

public:
	static MuteEagerSingleton* getInstance();
	static pthread_mutex_t mutex;
};
MuteEagerSingleton::MuteEagerSingleton() {
	pthread_mutex_init(&mutex,NULL);
}
MuteEagerSingleton* MuteEagerSingleton::instance = nullptr;
MuteEagerSingleton* MuteEagerSingleton::getInstance()
{
	if (instance == nullptr)
	{
		pthread_mutex_lock(&mutex);
		if (instance == nullptr)
			instance = new MuteEagerSingleton();
		pthread_mutex_unlock(&mutex);
	}
	return instance;
}
/*version4:使用内部静态变量保证线程安全*/
class StaticEagerSingleton
{
private:
	StaticEagerSingleton();
	static class InstanceHolder
	{
	private:
		static StaticEagerSingleton* instance;
	public:
		static StaticEagerSingleton* getInstanceHolderInstance()
		{
			return instance;
		}
	};
	StaticEagerSingleton* InstanceHolder::instance = new StaticEagerSingleton();
public:
	static StaticEagerSingleton* getInstance()
	{
		return InstanceHolder::getInstanceHolderInstance();
	}
};
