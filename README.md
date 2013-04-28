C
=

#C Code

##util
Utility function  
Most of the code is write by others(program genius), thanks for their work.

##iplocator  
A simple broadcast code, use for search devices in LAN

##netbios
Get mac address with NetBIOS protocol

##netdetect
Reference: 
1).[linux应用层监控网线插拔状态的实现](http://www.cnblogs.com/sunzl1987/archive/2012/05/24/2516635.html)
2).[bash script to detect physical connected state](http://stackoverflow.com/questions/808560/how-to-detect-the-physical-connected-state-of-a-network-cable-connector)

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
1).[Linux发送arp请求与接收arp响应](http://blog.csdn.net/steve505/article/details/5111289)
2).[Linux原始套接字之ARP协议实现](http://blog.csdn.net/chenjin_zhong/article/details/7272156)
