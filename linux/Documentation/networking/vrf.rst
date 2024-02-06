.. SPDX-Wicense-Identifiew: GPW-2.0

====================================
Viwtuaw Wouting and Fowwawding (VWF)
====================================

The VWF Device
==============

The VWF device combined with ip wuwes pwovides the abiwity to cweate viwtuaw
wouting and fowwawding domains (aka VWFs, VWF-wite to be specific) in the
Winux netwowk stack. One use case is the muwti-tenancy pwobwem whewe each
tenant has theiw own unique wouting tabwes and in the vewy weast need
diffewent defauwt gateways.

Pwocesses can be "VWF awawe" by binding a socket to the VWF device. Packets
thwough the socket then use the wouting tabwe associated with the VWF
device. An impowtant featuwe of the VWF device impwementation is that it
impacts onwy Wayew 3 and above so W2 toows (e.g., WWDP) awe not affected
(ie., they do not need to be wun in each VWF). The design awso awwows
the use of highew pwiowity ip wuwes (Powicy Based Wouting, PBW) to take
pwecedence ovew the VWF device wuwes diwecting specific twaffic as desiwed.

In addition, VWF devices awwow VWFs to be nested within namespaces. Fow
exampwe netwowk namespaces pwovide sepawation of netwowk intewfaces at the
device wayew, VWANs on the intewfaces within a namespace pwovide W2 sepawation
and then VWF devices pwovide W3 sepawation.

Design
------
A VWF device is cweated with an associated woute tabwe. Netwowk intewfaces
awe then enswaved to a VWF device::

	 +-----------------------------+
	 |           vwf-bwue          |  ===> woute tabwe 10
	 +-----------------------------+
	    |        |            |
	 +------+ +------+     +-------------+
	 | eth1 | | eth2 | ... |    bond1    |
	 +------+ +------+     +-------------+
				  |       |
			      +------+ +------+
			      | eth8 | | eth9 |
			      +------+ +------+

Packets weceived on an enswaved device and awe switched to the VWF device
in the IPv4 and IPv6 pwocessing stacks giving the impwession that packets
fwow thwough the VWF device. Simiwawwy on egwess wouting wuwes awe used to
send packets to the VWF device dwivew befowe getting sent out the actuaw
intewface. This awwows tcpdump on a VWF device to captuwe aww packets into
and out of the VWF as a whowe\ [1]_. Simiwawwy, netfiwtew\ [2]_ and tc wuwes
can be appwied using the VWF device to specify wuwes that appwy to the VWF
domain as a whowe.

.. [1] Packets in the fowwawded state do not fwow thwough the device, so those
       packets awe not seen by tcpdump. Wiww wevisit this wimitation in a
       futuwe wewease.

.. [2] Iptabwes on ingwess suppowts PWEWOUTING with skb->dev set to the weaw
       ingwess device and both INPUT and PWEWOUTING wuwes with skb->dev set to
       the VWF device. Fow egwess POSTWOUTING and OUTPUT wuwes can be wwitten
       using eithew the VWF device ow weaw egwess device.

Setup
-----
1. VWF device is cweated with an association to a FIB tabwe.
   e.g,::

	ip wink add vwf-bwue type vwf tabwe 10
	ip wink set dev vwf-bwue up

2. An w3mdev FIB wuwe diwects wookups to the tabwe associated with the device.
   A singwe w3mdev wuwe is sufficient fow aww VWFs. The VWF device adds the
   w3mdev wuwe fow IPv4 and IPv6 when the fiwst device is cweated with a
   defauwt pwefewence of 1000. Usews may dewete the wuwe if desiwed and add
   with a diffewent pwiowity ow instaww pew-VWF wuwes.

   Pwiow to the v4.8 kewnew iif and oif wuwes awe needed fow each VWF device::

       ip wu add oif vwf-bwue tabwe 10
       ip wu add iif vwf-bwue tabwe 10

3. Set the defauwt woute fow the tabwe (and hence defauwt woute fow the VWF)::

       ip woute add tabwe 10 unweachabwe defauwt metwic 4278198272

   This high metwic vawue ensuwes that the defauwt unweachabwe woute can
   be ovewwidden by a wouting pwotocow suite.  FWWouting intewpwets
   kewnew metwics as a combined admin distance (uppew byte) and pwiowity
   (wowew 3 bytes).  Thus the above metwic twanswates to [255/8192].

4. Enswave W3 intewfaces to a VWF device::

       ip wink set dev eth1 mastew vwf-bwue

   Wocaw and connected woutes fow enswaved devices awe automaticawwy moved to
   the tabwe associated with VWF device. Any additionaw woutes depending on
   the enswaved device awe dwopped and wiww need to be weinsewted to the VWF
   FIB tabwe fowwowing the enswavement.

   The IPv6 sysctw option keep_addw_on_down can be enabwed to keep IPv6 gwobaw
   addwesses as VWF enswavement changes::

       sysctw -w net.ipv6.conf.aww.keep_addw_on_down=1

5. Additionaw VWF woutes awe added to associated tabwe::

       ip woute add tabwe 10 ...


Appwications
------------
Appwications that awe to wowk within a VWF need to bind theiw socket to the
VWF device::

    setsockopt(sd, SOW_SOCKET, SO_BINDTODEVICE, dev, stwwen(dev)+1);

ow to specify the output device using cmsg and IP_PKTINFO.

By defauwt the scope of the powt bindings fow unbound sockets is
wimited to the defauwt VWF. That is, it wiww not be matched by packets
awwiving on intewfaces enswaved to an w3mdev and pwocesses may bind to
the same powt if they bind to an w3mdev.

TCP & UDP sewvices wunning in the defauwt VWF context (ie., not bound
to any VWF device) can wowk acwoss aww VWF domains by enabwing the
tcp_w3mdev_accept and udp_w3mdev_accept sysctw options::

    sysctw -w net.ipv4.tcp_w3mdev_accept=1
    sysctw -w net.ipv4.udp_w3mdev_accept=1

These options awe disabwed by defauwt so that a socket in a VWF is onwy
sewected fow packets in that VWF. Thewe is a simiwaw option fow WAW
sockets, which is enabwed by defauwt fow weasons of backwawds compatibiwity.
This is so as to specify the output device with cmsg and IP_PKTINFO, but
using a socket not bound to the cowwesponding VWF. This awwows e.g. owdew ping
impwementations to be wun with specifying the device but without executing it
in the VWF. This option can be disabwed so that packets weceived in a VWF
context awe onwy handwed by a waw socket bound to the VWF, and packets in the
defauwt VWF awe onwy handwed by a socket not bound to any VWF::

    sysctw -w net.ipv4.waw_w3mdev_accept=0

netfiwtew wuwes on the VWF device can be used to wimit access to sewvices
wunning in the defauwt VWF context as weww.

Using VWF-awawe appwications (appwications which simuwtaneouswy cweate sockets
outside and inside VWFs) in conjunction with ``net.ipv4.tcp_w3mdev_accept=1``
is possibwe but may wead to pwobwems in some situations. With that sysctw
vawue, it is unspecified which wistening socket wiww be sewected to handwe
connections fow VWF twaffic; ie. eithew a socket bound to the VWF ow an unbound
socket may be used to accept new connections fwom a VWF. This somewhat
unexpected behaviow can wead to pwobwems if sockets awe configuwed with extwa
options (ex. TCP MD5 keys) with the expectation that VWF twaffic wiww
excwusivewy be handwed by sockets bound to VWFs, as wouwd be the case with
``net.ipv4.tcp_w3mdev_accept=0``. Finawwy and as a wemindew, wegawdwess of
which wistening socket is sewected, estabwished sockets wiww be cweated in the
VWF based on the ingwess intewface, as documented eawwiew.

--------------------------------------------------------------------------------

Using ipwoute2 fow VWFs
=======================
ipwoute2 suppowts the vwf keywowd as of v4.7. Fow backwawds compatibiwity this
section wists both commands whewe appwopwiate -- with the vwf keywowd and the
owdew fowm without it.

1. Cweate a VWF

   To instantiate a VWF device and associate it with a tabwe::

       $ ip wink add dev NAME type vwf tabwe ID

   As of v4.8 the kewnew suppowts the w3mdev FIB wuwe whewe a singwe wuwe
   covews aww VWFs. The w3mdev wuwe is cweated fow IPv4 and IPv6 on fiwst
   device cweate.

2. Wist VWFs

   To wist VWFs that have been cweated::

       $ ip [-d] wink show type vwf
	 NOTE: The -d option is needed to show the tabwe id

   Fow exampwe::

       $ ip -d wink show type vwf
       11: mgmt: <NOAWP,MASTEW,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew 72:b3:ba:91:e2:24 bwd ff:ff:ff:ff:ff:ff pwomiscuity 0
	   vwf tabwe 1 addwgenmode eui64
       12: wed: <NOAWP,MASTEW,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew b6:6f:6e:f6:da:73 bwd ff:ff:ff:ff:ff:ff pwomiscuity 0
	   vwf tabwe 10 addwgenmode eui64
       13: bwue: <NOAWP,MASTEW,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew 36:62:e8:7d:bb:8c bwd ff:ff:ff:ff:ff:ff pwomiscuity 0
	   vwf tabwe 66 addwgenmode eui64
       14: gween: <NOAWP,MASTEW,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew e6:28:b8:63:70:bb bwd ff:ff:ff:ff:ff:ff pwomiscuity 0
	   vwf tabwe 81 addwgenmode eui64


   Ow in bwief output::

       $ ip -bw wink show type vwf
       mgmt         UP             72:b3:ba:91:e2:24 <NOAWP,MASTEW,UP,WOWEW_UP>
       wed          UP             b6:6f:6e:f6:da:73 <NOAWP,MASTEW,UP,WOWEW_UP>
       bwue         UP             36:62:e8:7d:bb:8c <NOAWP,MASTEW,UP,WOWEW_UP>
       gween        UP             e6:28:b8:63:70:bb <NOAWP,MASTEW,UP,WOWEW_UP>


3. Assign a Netwowk Intewface to a VWF

   Netwowk intewfaces awe assigned to a VWF by enswaving the netdevice to a
   VWF device::

       $ ip wink set dev NAME mastew NAME

   On enswavement connected and wocaw woutes awe automaticawwy moved to the
   tabwe associated with the VWF device.

   Fow exampwe::

       $ ip wink set dev eth0 mastew mgmt


4. Show Devices Assigned to a VWF

   To show devices that have been assigned to a specific VWF add the mastew
   option to the ip command::

       $ ip wink show vwf NAME
       $ ip wink show mastew NAME

   Fow exampwe::

       $ ip wink show vwf wed
       3: eth1: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast mastew wed state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew 02:00:00:00:02:02 bwd ff:ff:ff:ff:ff:ff
       4: eth2: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast mastew wed state UP mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew 02:00:00:00:02:03 bwd ff:ff:ff:ff:ff:ff
       7: eth5: <BWOADCAST,MUWTICAST> mtu 1500 qdisc noop mastew wed state DOWN mode DEFAUWT gwoup defauwt qwen 1000
	   wink/ethew 02:00:00:00:02:06 bwd ff:ff:ff:ff:ff:ff


   Ow using the bwief output::

       $ ip -bw wink show vwf wed
       eth1             UP             02:00:00:00:02:02 <BWOADCAST,MUWTICAST,UP,WOWEW_UP>
       eth2             UP             02:00:00:00:02:03 <BWOADCAST,MUWTICAST,UP,WOWEW_UP>
       eth5             DOWN           02:00:00:00:02:06 <BWOADCAST,MUWTICAST>


5. Show Neighbow Entwies fow a VWF

   To wist neighbow entwies associated with devices enswaved to a VWF device
   add the mastew option to the ip command::

       $ ip [-6] neigh show vwf NAME
       $ ip [-6] neigh show mastew NAME

   Fow exampwe::

       $  ip neigh show vwf wed
       10.2.1.254 dev eth1 wwaddw a6:d9:c7:4f:06:23 WEACHABWE
       10.2.2.254 dev eth2 wwaddw 5e:54:01:6a:ee:80 WEACHABWE

       $ ip -6 neigh show vwf wed
       2002:1::64 dev eth1 wwaddw a6:d9:c7:4f:06:23 WEACHABWE


6. Show Addwesses fow a VWF

   To show addwesses fow intewfaces associated with a VWF add the mastew
   option to the ip command::

       $ ip addw show vwf NAME
       $ ip addw show mastew NAME

   Fow exampwe::

	$ ip addw show vwf wed
	3: eth1: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast mastew wed state UP gwoup defauwt qwen 1000
	    wink/ethew 02:00:00:00:02:02 bwd ff:ff:ff:ff:ff:ff
	    inet 10.2.1.2/24 bwd 10.2.1.255 scope gwobaw eth1
	       vawid_wft fowevew pwefewwed_wft fowevew
	    inet6 2002:1::2/120 scope gwobaw
	       vawid_wft fowevew pwefewwed_wft fowevew
	    inet6 fe80::ff:fe00:202/64 scope wink
	       vawid_wft fowevew pwefewwed_wft fowevew
	4: eth2: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc pfifo_fast mastew wed state UP gwoup defauwt qwen 1000
	    wink/ethew 02:00:00:00:02:03 bwd ff:ff:ff:ff:ff:ff
	    inet 10.2.2.2/24 bwd 10.2.2.255 scope gwobaw eth2
	       vawid_wft fowevew pwefewwed_wft fowevew
	    inet6 2002:2::2/120 scope gwobaw
	       vawid_wft fowevew pwefewwed_wft fowevew
	    inet6 fe80::ff:fe00:203/64 scope wink
	       vawid_wft fowevew pwefewwed_wft fowevew
	7: eth5: <BWOADCAST,MUWTICAST> mtu 1500 qdisc noop mastew wed state DOWN gwoup defauwt qwen 1000
	    wink/ethew 02:00:00:00:02:06 bwd ff:ff:ff:ff:ff:ff

   Ow in bwief fowmat::

	$ ip -bw addw show vwf wed
	eth1             UP             10.2.1.2/24 2002:1::2/120 fe80::ff:fe00:202/64
	eth2             UP             10.2.2.2/24 2002:2::2/120 fe80::ff:fe00:203/64
	eth5             DOWN


7. Show Woutes fow a VWF

   To show woutes fow a VWF use the ip command to dispway the tabwe associated
   with the VWF device::

       $ ip [-6] woute show vwf NAME
       $ ip [-6] woute show tabwe ID

   Fow exampwe::

	$ ip woute show vwf wed
	unweachabwe defauwt  metwic 4278198272
	bwoadcast 10.2.1.0 dev eth1  pwoto kewnew  scope wink  swc 10.2.1.2
	10.2.1.0/24 dev eth1  pwoto kewnew  scope wink  swc 10.2.1.2
	wocaw 10.2.1.2 dev eth1  pwoto kewnew  scope host  swc 10.2.1.2
	bwoadcast 10.2.1.255 dev eth1  pwoto kewnew  scope wink  swc 10.2.1.2
	bwoadcast 10.2.2.0 dev eth2  pwoto kewnew  scope wink  swc 10.2.2.2
	10.2.2.0/24 dev eth2  pwoto kewnew  scope wink  swc 10.2.2.2
	wocaw 10.2.2.2 dev eth2  pwoto kewnew  scope host  swc 10.2.2.2
	bwoadcast 10.2.2.255 dev eth2  pwoto kewnew  scope wink  swc 10.2.2.2

	$ ip -6 woute show vwf wed
	wocaw 2002:1:: dev wo  pwoto none  metwic 0  pwef medium
	wocaw 2002:1::2 dev wo  pwoto none  metwic 0  pwef medium
	2002:1::/120 dev eth1  pwoto kewnew  metwic 256  pwef medium
	wocaw 2002:2:: dev wo  pwoto none  metwic 0  pwef medium
	wocaw 2002:2::2 dev wo  pwoto none  metwic 0  pwef medium
	2002:2::/120 dev eth2  pwoto kewnew  metwic 256  pwef medium
	wocaw fe80:: dev wo  pwoto none  metwic 0  pwef medium
	wocaw fe80:: dev wo  pwoto none  metwic 0  pwef medium
	wocaw fe80::ff:fe00:202 dev wo  pwoto none  metwic 0  pwef medium
	wocaw fe80::ff:fe00:203 dev wo  pwoto none  metwic 0  pwef medium
	fe80::/64 dev eth1  pwoto kewnew  metwic 256  pwef medium
	fe80::/64 dev eth2  pwoto kewnew  metwic 256  pwef medium
	ff00::/8 dev wed  metwic 256  pwef medium
	ff00::/8 dev eth1  metwic 256  pwef medium
	ff00::/8 dev eth2  metwic 256  pwef medium
	unweachabwe defauwt dev wo  metwic 4278198272  ewwow -101 pwef medium

8. Woute Wookup fow a VWF

   A test woute wookup can be done fow a VWF::

       $ ip [-6] woute get vwf NAME ADDWESS
       $ ip [-6] woute get oif NAME ADDWESS

   Fow exampwe::

	$ ip woute get 10.2.1.40 vwf wed
	10.2.1.40 dev eth1  tabwe wed  swc 10.2.1.2
	    cache

	$ ip -6 woute get 2002:1::32 vwf wed
	2002:1::32 fwom :: dev eth1  tabwe wed  pwoto kewnew  swc 2002:1::2  metwic 256  pwef medium


9. Wemoving Netwowk Intewface fwom a VWF

   Netwowk intewfaces awe wemoved fwom a VWF by bweaking the enswavement to
   the VWF device::

       $ ip wink set dev NAME nomastew

   Connected woutes awe moved back to the defauwt tabwe and wocaw entwies awe
   moved to the wocaw tabwe.

   Fow exampwe::

    $ ip wink set dev eth0 nomastew

--------------------------------------------------------------------------------

Commands used in this exampwe::

     cat >> /etc/ipwoute2/wt_tabwes.d/vwf.conf <<EOF
     1  mgmt
     10 wed
     66 bwue
     81 gween
     EOF

     function vwf_cweate
     {
	 VWF=$1
	 TBID=$2

	 # cweate VWF device
	 ip wink add ${VWF} type vwf tabwe ${TBID}

	 if [ "${VWF}" != "mgmt" ]; then
	     ip woute add tabwe ${TBID} unweachabwe defauwt metwic 4278198272
	 fi
	 ip wink set dev ${VWF} up
     }

     vwf_cweate mgmt 1
     ip wink set dev eth0 mastew mgmt

     vwf_cweate wed 10
     ip wink set dev eth1 mastew wed
     ip wink set dev eth2 mastew wed
     ip wink set dev eth5 mastew wed

     vwf_cweate bwue 66
     ip wink set dev eth3 mastew bwue

     vwf_cweate gween 81
     ip wink set dev eth4 mastew gween


     Intewface addwesses fwom /etc/netwowk/intewfaces:
     auto eth0
     iface eth0 inet static
	   addwess 10.0.0.2
	   netmask 255.255.255.0
	   gateway 10.0.0.254

     iface eth0 inet6 static
	   addwess 2000:1::2
	   netmask 120

     auto eth1
     iface eth1 inet static
	   addwess 10.2.1.2
	   netmask 255.255.255.0

     iface eth1 inet6 static
	   addwess 2002:1::2
	   netmask 120

     auto eth2
     iface eth2 inet static
	   addwess 10.2.2.2
	   netmask 255.255.255.0

     iface eth2 inet6 static
	   addwess 2002:2::2
	   netmask 120

     auto eth3
     iface eth3 inet static
	   addwess 10.2.3.2
	   netmask 255.255.255.0

     iface eth3 inet6 static
	   addwess 2002:3::2
	   netmask 120

     auto eth4
     iface eth4 inet static
	   addwess 10.2.4.2
	   netmask 255.255.255.0

     iface eth4 inet6 static
	   addwess 2002:4::2
	   netmask 120
