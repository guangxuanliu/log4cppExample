//============================================================================
// Name        : test.cpp
// Author      : lgx
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/CategoryStream.hh>
#include <log4cpp/PropertyConfigurator.hh>

using namespace std;

void manualWrite() {
	// 1实例化一个layout 对象
	log4cpp::Layout *layout = new log4cpp::BasicLayout();
	// 2. 初始化一个appender 对象
	log4cpp::Appender *appender = new log4cpp::FileAppender("FileAppender",
			"./test_log4cpp1.log");
	// 3. 把layout对象附着在appender对象上
	appender->setLayout(layout);
	// 4. 实例化一个category对象
	log4cpp::Category &warn_log = log4cpp::Category::getInstance("mywarn");
	// 5. 设置additivity为false，替换已有的appender
	warn_log.setAdditivity(false);
	// 5. 把appender对象附到category上
	warn_log.setAppender(appender);
	// 6. 设置category的优先级，低于此优先级的日志不被记录
	warn_log.setPriority(log4cpp::Priority::WARN);
	// 记录一些日志
	warn_log.info("Program info which cannot be wirten");
	warn_log.debug("This debug message will fail to write");
	warn_log.alert("Alert info");
	// 其他记录日志方式
	warn_log.log(log4cpp::Priority::WARN, "This will be a logged warning");
	log4cpp::Priority::PriorityLevel priority;
	bool this_is_critical = true;
	if (this_is_critical)
		priority = log4cpp::Priority::CRIT;
	else
		priority = log4cpp::Priority::DEBUG;
	warn_log.log(priority, "Importance depends on context");

	// api changed
	//	warn_log.critStream() << "This will show up << as " << 1
	//			<< " critical message"
	//			<< log4cpp::CategoryStream::ENDLINE;
	// clean up and flush all appenders
	log4cpp::Category::shutdown();
}

void configWrite() {
	// 1 读取解析配置文件
	// 读取出错, 完全可以忽略，可以定义一个缺省策略或者使用系统缺省策略
	// BasicLayout输出所有优先级日志到ConsoleAppender
	try {
		log4cpp::PropertyConfigurator::configure("./log4cpp.conf");
	} catch (log4cpp::ConfigureFailure &f) {
		std::cout << "Configure Problem " << f.what() << std::endl;
		return;
	}

	// 2 实例化category对象
	// 这些对象即使配置文件没有定义也可以使用，不过其属性继承其父category
	// 通常使用引用可能不太方便，可以使用指针，以后做指针使用
	// log4cpp::Category* root = &log4cpp::Category::getRoot();

	log4cpp::Category &sub1 = log4cpp::Category::getInstance(
			std::string("sub1"));

	// 3 正常使用这些category对象进行日志处理。
	// sub1 has appender A1.

	for(int i = 0;i < 5000;i ++)
	{
		sub1.info(to_string(i) + " This is some info");
	}

	cout << "done!" << endl;
}

int main() {

	// test 1
//	manualWrite();

	// test2
	configWrite();

	return 0;
}
