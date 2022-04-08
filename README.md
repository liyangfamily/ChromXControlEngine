# LBusinessLib For LED Business Unit
## 介绍
作为 **LED C++ 业务引擎**， LBusinessLib 支持大部分LED**设备通信与控制**，包括PCON100、PCON500、PCON600、
2nd_Plus和衍生设备 。
这是一个**分层设计**的业务引擎，用户能够很方便的拆分、拓展或者移植这个业务引擎。

## 如何接入
* 库接入方式
  * 克隆源代码
    ~~~sh
    git clone https://gitlab.gz.cvte.cn/led-sw/led-windows/CHROMX_led_tools_group/maxconfig/lbusinesslib.git
    ~~~
  * 使用**Qt Creator**打开：
    ~~~sh
    LBusinessLib.pro
    ~~~
  * 在此文件中指定库文件输出目录：
    ~~~sh
    LBLCommon.pri

    $$PRO_BIN_PATH
    $$PRO_LIBRARY_PATH
    ~~~
  * 在**Qt Creator**中执行构建
  * 拷贝**include**文件夹与生成的**库文件**到所需要的工程目录下使用即可，使用者只需要依赖加载顶层 **LAPI_Control** 库即可。


* 源码接入方式
  
  我们推荐使用 **git submodule** 来管理 **LBusinessLib** 。当然你也可以 **git clone** 最新的源码，
  再拷贝到您的项目中使用，只不过您将无法方便的获得 **LBusinessLib** 的更新。
  本人不才，截止写本md为止，还不太会使用**cmake**进行配置搭建，遂继续使用**qmake**。

  * 将 **LBusinessLib** 下载到项目根目录 **3rdparty/LBusinessLib** 中
  * 需要根据 **LBusinessLib** 中 **LBLCommon.pri** 指示
    ~~~sh
    ...
    # For Parent Project Config
    # Parent Project Need Creat This Config In "3rdparty/LBusinessLib"(Actually,is 3rdparty, This project spelling error)
    # In this Config , Need to specify the variable: $$PRO_BIN_PATH $$PRO_LIBRARY_PATH
    exists(../../LBusinessLib_OutputPath.pri):include(../../LBusinessLib_OutputPath.pri)
    ...
    ~~~
    在 **项目根目录** 新建文件，并定义输出路径变量：
    ~~~sh
    LBusinessLib_OutputPath.pri

    $$PRO_BIN_PATH
    $$PRO_LIBRARY_PATH
    ~~~

    **我认为此方法比较丑陋，但我又想不到更好的实现办法来剥离子模块。**

  * 将 **LBusinessLib.pro** 加入到项目工程**pro**文件中，配置好**include路径**和**库依赖**即可。使用者只需要依赖加载顶层 **LAPI_Control** 库即可。

## 如何启动、停止与退出
~~~cpp
#include <LAPI_Control/LAPIControl>

//启动探卡服务
LAPI::StartDetectServer();

//停止探卡服务(仅停止探卡服务的定时器)
LAPI::StoptDetectServer();

//退出探卡服务(停止探卡服务定时器与断开对应通信连接)
LAPI::QuitDetectServer();

//退出库(必须调用，目前这种方式不够优雅)
LAPI::ReadyExit();
    int maxWait = 0;
    while (!LAPI::CanExit())
    {
        QCoreApplication::processEvents();
        QThread::currentThread()->msleep(200);
        maxWait++;
        if (maxWait >= 150)
        {
            if (QMessageBox::information(0, tr("Confire Exit"),
                                         tr("There are still some clients alive in the server. continue waiting?"),
                                         QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
                maxWait = 0;
            else
                break;
        }
    }
~~~

## 特性说明
* ### 统一API：

    对外使用的功能接口全部封装在
    ~~~
    include/LAPI_Control/LAPIControl.h
    ~~~
    头文件中。
    
    在用户上下文中，只需要使用API接口即可。目前**API**全部集中在一个文件中，后续可以考虑按照功能分成多个**API**接口文件。

    使用方法如下：
    ~~~cpp
    #include <LAPI_Control/LAPIControl>

    int main(){
        ...
        LAPI::ReadBrightness();
        ...
        return 0;
    }
    ~~~

* ### LBL_Core核心库：
    
    核心库为底层库，所有上层模块全都依赖于核心库。核心库主要定义了一些公共机制的**class**，包括：
    ~~~cpp
    /*信号等待器*/
    #include <LBL_Core/LBL_SignalWaiter>
    class LBLSignalWaiter;

    /*外部公用函数类*/
    #include <LBL_Core/LBLUIHelper>
    class LBLUIHelper;
    ~~~
    每个类具体使用方式，请查看对应**class**的**cpp**文件，其中有详细使用介绍。


* ### LBL_CommunicatEngine通信引擎
    通信库采用**通信读写分离**与**线程池任务处理**设计，设计有**通信数据传输引擎**与**任务处理引擎**。
    * 通信数据传输引擎
    
        目前UDP与COM各创建了 **2** 个线程来处理传输socket和串口的数据。外部主动通过 **通信数据传输引擎** 的连接函数来新建连接，在
        连接过程中，会主动简单判断线程客户端数量来进行负载均衡。
        
        1、发送数据：通过信号槽将需要发送的数据添加到对应客户端线程数据队列中

        2、接收数据：客户端数据线程收到数据后，通过信号槽将数据添加到**任务处理引擎**处理
    * 任务处理引擎

        目前数据传输引擎启动了 **4** 个线程来处理任务流，采用流水线的形式来处理任务。任务会被抽象为任务基类，用户可以根据自己的实际情况
        来实现任务基类中的虚函数
        ~~~cpp
        class LBL_TaskEngine_TaskBase{
            public:
            virtual int run() = 0;
        }
        ~~~
        当**通信数据传输引擎**收到数据后，会将数据**push**到对应的**Task**数据队列中，**任务处理引擎**线程池如果有空闲
        则会分配一个空闲线程去处理任务。当然，为了保证整个任务处理流水线高效运转，防止某个任务长时间占用线程处理，在任务基类中定义了
        任务每次处理的最大消息为 **8** 条数据。

