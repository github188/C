C
=

#C Code

##iplocator  
A simple broadcast code, use for search devices in LAN

##netbios
Get mac address with NetBIOS protocol

##netdetect
Reference: 
[linux应用层监控网线插拔状态的实现](http://www.cnblogs.com/sunzl1987/archive/2012/05/24/2516635.html)

##proxy
1. source from [proxyd.c](https://github.com/webee/libscripts/blob/master/src/proxyd.c)  
2. technical detail explain visit : [Proxy源代碼分析--談談如何學習linux網絡編程](http://fanqiang.chinaunix.net/a4/b7/20010810/1200001101_b.html)  
3. other: [Improment to Carl Harris’ proxy](http://dev.poetpalace.org/?p=440)  

##w2tty
1. dowall.c is downloaded from [sysvinit-tools-2.88-9-i686.pkg.tar.xz](http://ftp.slackware.com/pub/archlinux/core/os/i686/sysvinit-tools-2.88-9-i686.pkg.tar.xz)
2. I modify the line length from 81 to 91.(File:dowell.c Line:159)
3. System command "wall" have the same function.
   example like this:  "wall testmessage" 
