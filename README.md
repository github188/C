C code
=

##util
Utility function  
Most of the code is write by others(program genius), thanks for their work.

##iplocator  
A simple broadcast code, use for search devices in LAN

##netbios
Get mac address with NetBIOS protocol

##netdetect
Reference: 
+ [linux应用层监控网线插拔状态的实现](http://www.cnblogs.com/sunzl1987/archive/2012/05/24/2516635.html)
+ [bash script to detect physical connected state](http://stackoverflow.com/questions/808560/how-to-detect-the-physical-connected-state-of-a-network-cable-connector)

##proxy
1. source from [proxyd.c](https://github.com/webee/libscripts/blob/master/src/proxyd.c)  
2. technical detail explain visit : [Proxy源代碼分析--談談如何學習linux網絡編程](http://fanqiang.chinaunix.net/a4/b7/20010810/1200001101_b.html)  
3. other: [Improment to Carl Harris’ proxy](http://dev.poetpalace.org/?p=440)  

##w2tty
1. dowall.c is downloaded from [sysvinit-tools-2.88-9-i686.pkg.tar.xz](http://ftp.slackware.com/pub/archlinux/core/os/i686/sysvinit-tools-2.88-9-i686.pkg.tar.xz)
2. I modify the line length from 81 to 91.(File:dowell.c Line:159)
3. System command "wall" have the same function.
   example like this:  "wall testmessage" 

##arp
Example of using ARP protocol  
1. send_arp.c : a simple code of send arp packet to special computer.  
2. IPfinder.c : find alive hosts in lan with ARP protocol. (TO DO)  
Reference:  
+ [Linux发送arp请求与接收arp响应](http://blog.csdn.net/steve505/article/details/5111289)
+ [Linux原始套接字之ARP协议实现](http://blog.csdn.net/chenjin_zhong/article/details/7272156)

##threadpool
Reference:  
+ [threadpool](https://github.com/mbrossard/threadpool)
+ [C Thread Pool](https://github.com/Pithikos/C-Thread-Pool)
+ [c threadpool](http://bbs.chinaunix.net/thread-580210-1-1.html)
+ [一个Linux下C线程池的实现](http://blog.csdn.net/zouxinfox/article/details/3560891)

##cppscsi
c++ implement of jSCSI (a feature-complete iSCSI implementation in Java only)  
Reference:  
+ [jSCSI github project](https://github.com/disy/jSCSI.git)
+ [jSCSI office website](http://jscsi.org)
+ [bytebuffer-cpp An implementation of ByteBuffer in C++](http://code.google.com/p/bytebuffer-cpp/)
+ [Protocol Data Unit (PDU) data format, see RFC3720 page 114](http://www.ietf.org/rfc/rfc3720.txt)

##sg_ses  
use sg_ses control ISCSI expander LED light  
Reference:  
+ [use sg_ses](http://matrix207.github.com/2013/06/20/use-sg_ses/)

##sqlite
+ [sqlite_c_cpp](http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm)
+ [sqlite insert](http://www.csl.mtu.edu/cs1141/www/examples/sqlite/sqlite_insert.c)
+ [sqlite select](http://www.csl.mtu.edu/cs1141/www/examples/sqlite/sqlite_select.c)

##mystrace
+ [ptrace I](http://www.linuxjournal.com/article/6100)
+ [ptrace II](http://www.linuxjournal.com/article/6210)
+ [ptrace运行原理及使用详解](http://blog.csdn.net/edonlii/article/details/8717029)
+ [How to play with ptrace on x86-64](http://stackoverflow.com/questions/7418315/how-to-play-with-ptrace-on-x86-64)

##malloc
Implement malloc and free
+ [Computer Systems - A Programmer's Perspective Second Edition]()
+ [code](http://csapp.cs.cmu.edu/public/code.html)
+ [Malloc](https://github.com/ltganesan/Malloc)

##mmpool
Implement memory pool

##hexdump
Implement hexdump.  
Hexdump tools on linux includes : hexdump, vim  
If you want view file 1.dat in binary, you can use:  
1. `hexdump -C 1.dat`  
2. `vim -b 1.dat`, then `:%!xxd`, `:%!xxd -r`

##setprocesstitle
set farther process and child process title dynamically

reference from Nginx code "nginx-1.7.4/src/os/unix/ngx_setproctitle.c"

using `ps auxf |grep test`

Below is a sample running:

[dennis@localhost setprocesstitle]$ ./test &   
[1] 26496  
test: fork process 4  
test: fork process 3  
test: fork process 2  
test: fork process 1  
[dennis@localhost setprocesstitle]$ ps f |grep test |grep -v grep  
26496 pts/4    S      0:00  \_ test: master process  
26499 pts/4    S      0:00  |   \_ test: worker procee 1  
26500 pts/4    S      0:00  |   \_ test: worker procee 2  
26501 pts/4    S      0:00  |   \_ test: worker procee 3  
26502 pts/4    S      0:00  |   \_ test: worker procee 4  

