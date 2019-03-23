# Thrift RPC Example

## 运行

请直接使用即可，无需拉取任何依赖包。

```
cd $GOPATH/src

git clone https://github.com/hunterhug/thrift_example.git

go build server.gp
go build client.go

./server
./client
```

`$GOPATH` 为环境变量，请替换为你的本地路径。

##  具体使用，详细介绍

gRPC是Google研究的RPC传输方案，thrift则是facebook, 大家都通过IDL（Interface Definition Language）接口定义语言来规范输入输出。

下载： [https://thrift.apache.org/download](https://thrift.apache.org/download)

### Ubuntu 系统安装

```
sudo apt-get install automake bison flex git libboost-all-dev libevent-dev libssl-dev libtool make pkg-config build-essential g++


tar xvf thrift-0.12.0.tar.gz 
./bootstrap.sh
./configure
make
sudo make install
sudo ldconfig
```

Windows系统请直接安装二进制。

### 建立 thrift 文件

新建 `timeRPC.thrift`:

```
service timeServe {
    i32 getCurrtentTime()
}
```

### C++ 服务端

您可以忽略 `C++` 部分，直接跳到 `Golang` 部分。

执行：

```
thrift --gen cpp timeRPC.thrift
```

在当前目录下生成一个叫做 "gen-cpp" 的文件夹，里面包含了需要的代码。

```
├── timeRPC_constants.cpp
├── timeRPC_constants.h
├── timeRPC_types.cpp
├── timeRPC_types.h
├── timeServe.cpp
├── timeServe.h
└── timeServe_server.skeleton.cpp

```

修改 `timeServe_server.skeleton.cpp`:

```
// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "timeServe.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class timeServeHandler : virtual public timeServeIf {
 public:
  timeServeHandler() {
    // Your initialization goes here
  }

  int32_t getCurrtentTime() {
        // Your implementation goes here
        auto t = time(nullptr);
        printf("getCurrtentTime: %ld\n", t);
        return t;
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<timeServeHandler> handler(new timeServeHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new timeServeProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
```

我们实现了 `getCurrtentTime`这个方法。

编译：

```
g++ -std=c++11 -o cpp-server timeRPC_constants.cpp timeRPC_types.cpp timeServe.cpp timeServe_server.skeleton.cpp -lthrift
```

查看：

```
ldd cpp-server 
        linux-vdso.so.1 =>  (0x00007ffee83b4000)
        libthrift-0.12.0.so => /usr/local/lib/libthrift-0.12.0.so (0x00007f0200e34000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f0200ab2000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f020089c000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f02004d2000)
        libssl.so.1.0.0 => /lib/x86_64-linux-gnu/libssl.so.1.0.0 (0x00007f0200269000)
        libcrypto.so.1.0.0 => /lib/x86_64-linux-gnu/libcrypto.so.1.0.0 (0x00007f01ffe24000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f01ffc07000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f01ff8fe000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f02010fe000)
        libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f01ff6fa000)

```

运行:

```
./cpp-server
```

### C++客户端

在 `gen-cpp` 上层新建 `client.cpp`:

```
// system
#include <iostream>

// lib
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using boost::shared_ptr;

// project
#include "gen-cpp/timeServe.h"


int main() {
  std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  timeServeClient client(protocol);

  // open connect
  transport->open();
  auto timeNow = client.getCurrtentTime();
  std::cout << timeNow << std::endl;
  transport->close();
  return 0;
}
```

对它进行编译：

```
g++ -std=c++11 -o cpp-client client.cpp gen-cpp/timeServe.cpp  -lthrift
```

运行:

```
./cpp-client 
1553223392
```

### Golang服务端

修改 `timeRPC.thrift`:

```
service timeServe {
    i32 getCurrtentTime()
}


service time2Serve {
    i32 getCurrtentTime()
}

```

查看:

```
go env

GOPATH="/opt/gocode"
```

其中 `$GOPATH` 为 `/opt/gocode` 。

准备必要库：

```
mkdir -p $GOPATH/src/github.com/apache
cd $GOPATH/src/github.com/apache
git clone https://github.com/apache/thrift.git
```

执行：

```
thrift --gen go timeRPC.thrift
```

在当前目录下生成一个叫做 "gen-go" 的文件夹，里面包含了需要的代码。

```
└── timerpc
    ├── GoUnusedProtection__.go
    ├── timeRPC-consts.go
    ├── timeRPC.go
    └── time_serve-remote
        └── time_serve-remote.go
```

在 `gen-go` 上层新建 `server.go`:

```
package main

import (
	"context"
	"fmt"
	"github.com/apache/thrift/lib/go/thrift"
	"net"
	"os"
	"thrift_example/gen-go/timerpc"
	"time"
)

type MyTime struct{}

func (s *MyTime) GetCurrtentTime(_ context.Context) (r int32, err error) {
	t := int32(time.Now().Unix())
	fmt.Printf("come on:%d\n", t)
	return t, nil
}

type MyTime2 struct{}

func (s *MyTime2) GetCurrtentTime(_ context.Context) (r int32, err error) {
	t := int32(time.Now().Unix())
	fmt.Printf("come on2:%d\n", t)
	return t, nil
}

func main() {
	// 创建服务器
	serverTransport, err := thrift.NewTServerSocket(net.JoinHostPort("127.0.0.1", "9090"))
	if err != nil {
		fmt.Println("Error!", err)
		os.Exit(1)
	}

	// 创建二进制协议
	protocolFactory := thrift.NewTBinaryProtocolFactoryDefault()
	transportFactory := thrift.NewTFramedTransportFactory(thrift.NewTTransportFactory())

	// 创建Processor，用一个端口处理多个服务
	multiProcessor := thrift.NewTMultiplexedProcessor()
	MyTimeProcessor := timerpc.NewTimeServeProcessor(new(MyTime))
	MyTime2Processor := timerpc.NewTimeServeProcessor(new(MyTime2))

	// 给每个service起一个名字
	multiProcessor.RegisterProcessor("mytime", MyTimeProcessor)
	multiProcessor.RegisterProcessor("mytime2", MyTime2Processor)

	server := thrift.NewTSimpleServer4(multiProcessor, serverTransport, transportFactory, protocolFactory)

	fmt.Println("start")
	if err := server.Serve(); err != nil {
		panic(err)
	}

	// 退出时停止服务器
	defer server.Stop()
}

```

编译并运行：

```
go build server.go
./server
```

### Golang客户端

在 `gen-go` 上层新建 `client.go`:

```
package main

import (
	"context"
	"fmt"
	"github.com/apache/thrift/lib/go/thrift"
	"net"
	"os"
	"thrift_example/gen-go/timerpc"
)

func main() {
	// 先建立和服务器的连接的socket，再通过socket建立Transport
	socket, err := thrift.NewTSocket(net.JoinHostPort("127.0.0.1", "9090"))
	if err != nil {
		fmt.Println("Error opening socket:", err)
		os.Exit(1)
	}
	transport := thrift.NewTFramedTransport(socket)

	// 创建二进制协议
	protocol := thrift.NewTBinaryProtocolTransport(transport)

	// 打开Transport，与服务器进行连接
	if err := transport.Open(); err != nil {
		fmt.Fprintln(os.Stderr, "Error opening socket to "+"localhost"+":"+"9090", err)
		os.Exit(1)
	}
	defer transport.Close()

	// 接口需要context，以便在长操作时用户可以取消RPC调用
	ctx := context.Background()

	// 使用Mytime服务
	MyTimeProtocol := thrift.NewTMultiplexedProtocol(protocol, "mytime")

	// 创建代理客户端，使用TMultiplexedProtocol访问对应的服务
	c := thrift.NewTStandardClient(MyTimeProtocol, MyTimeProtocol)

	client := timerpc.NewTimeServeClient(c)
	res, err := client.GetCurrtentTime(ctx)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(res)

	// 使用其他服务
	// 步骤与上面的相同
	// 使用Mytime服务
	MyTime2Protocol := thrift.NewTMultiplexedProtocol(protocol, "mytime2")
	c2 := thrift.NewTStandardClient(MyTime2Protocol, MyTime2Protocol)
	client2 := timerpc.NewTimeServeClient(c2)
	res, err = client2.GetCurrtentTime(ctx)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(res)
}

```

编译并运行：

```
go build client.go
./client
```
