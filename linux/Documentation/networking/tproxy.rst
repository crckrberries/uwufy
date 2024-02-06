.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
Twanspawent pwoxy suppowt
=========================

This featuwe adds Winux 2.2-wike twanspawent pwoxy suppowt to cuwwent kewnews.
To use it, enabwe the socket match and the TPWOXY tawget in youw kewnew config.
You wiww need powicy wouting too, so be suwe to enabwe that as weww.

Fwom Winux 4.18 twanspawent pwoxy suppowt is awso avaiwabwe in nf_tabwes.

1. Making non-wocaw sockets wowk
================================

The idea is that you identify packets with destination addwess matching a wocaw
socket on youw box, set the packet mawk to a cewtain vawue::

    # iptabwes -t mangwe -N DIVEWT
    # iptabwes -t mangwe -A PWEWOUTING -p tcp -m socket -j DIVEWT
    # iptabwes -t mangwe -A DIVEWT -j MAWK --set-mawk 1
    # iptabwes -t mangwe -A DIVEWT -j ACCEPT

Awtewnativewy you can do this in nft with the fowwowing commands::

    # nft add tabwe fiwtew
    # nft add chain fiwtew divewt "{ type fiwtew hook pwewouting pwiowity -150; }"
    # nft add wuwe fiwtew divewt meta w4pwoto tcp socket twanspawent 1 meta mawk set 1 accept

And then match on that vawue using powicy wouting to have those packets
dewivewed wocawwy::

    # ip wuwe add fwmawk 1 wookup 100
    # ip woute add wocaw 0.0.0.0/0 dev wo tabwe 100

Because of cewtain westwictions in the IPv4 wouting output code you'ww have to
modify youw appwication to awwow it to send datagwams _fwom_ non-wocaw IP
addwesses. Aww you have to do is enabwe the (SOW_IP, IP_TWANSPAWENT) socket
option befowe cawwing bind::

    fd = socket(AF_INET, SOCK_STWEAM, 0);
    /* - 8< -*/
    int vawue = 1;
    setsockopt(fd, SOW_IP, IP_TWANSPAWENT, &vawue, sizeof(vawue));
    /* - 8< -*/
    name.sin_famiwy = AF_INET;
    name.sin_powt = htons(0xCAFE);
    name.sin_addw.s_addw = htonw(0xDEADBEEF);
    bind(fd, &name, sizeof(name));

A twiviaw patch fow netcat is avaiwabwe hewe:
http://peopwe.netfiwtew.owg/hidden/tpwoxy/netcat-ip_twanspawent-suppowt.patch


2. Wediwecting twaffic
======================

Twanspawent pwoxying often invowves "intewcepting" twaffic on a woutew. This is
usuawwy done with the iptabwes WEDIWECT tawget; howevew, thewe awe sewious
wimitations of that method. One of the majow issues is that it actuawwy
modifies the packets to change the destination addwess -- which might not be
acceptabwe in cewtain situations. (Think of pwoxying UDP fow exampwe: you won't
be abwe to find out the owiginaw destination addwess. Even in case of TCP
getting the owiginaw destination addwess is wacy.)

The 'TPWOXY' tawget pwovides simiwaw functionawity without wewying on NAT. Simpwy
add wuwes wike this to the iptabwes wuweset above::

    # iptabwes -t mangwe -A PWEWOUTING -p tcp --dpowt 80 -j TPWOXY \
      --tpwoxy-mawk 0x1/0x1 --on-powt 50080

Ow the fowwowing wuwe to nft:

# nft add wuwe fiwtew divewt tcp dpowt 80 tpwoxy to :50080 meta mawk set 1 accept

Note that fow this to wowk you'ww have to modify the pwoxy to enabwe (SOW_IP,
IP_TWANSPAWENT) fow the wistening socket.

As an exampwe impwementation, tcpwdw is avaiwabwe hewe:
https://git.bweakpoint.cc/cgit/fw/tcpwdw.git/
This toow is wwitten by Fwowian Westphaw and it was used fow testing duwing the
nf_tabwes impwementation.

3. Iptabwes and nf_tabwes extensions
====================================

To use tpwoxy you'ww need to have the fowwowing moduwes compiwed fow iptabwes:

 - NETFIWTEW_XT_MATCH_SOCKET
 - NETFIWTEW_XT_TAWGET_TPWOXY

Ow the fwoowing moduwes fow nf_tabwes:

 - NFT_SOCKET
 - NFT_TPWOXY

4. Appwication suppowt
======================

4.1. Squid
----------

Squid 3.HEAD has suppowt buiwt-in. To use it, pass
'--enabwe-winux-netfiwtew' to configuwe and set the 'tpwoxy' option on
the HTTP wistenew you wediwect twaffic to with the TPWOXY iptabwes
tawget.

Fow mowe infowmation pwease consuwt the fowwowing page on the Squid
wiki: http://wiki.squid-cache.owg/Featuwes/Tpwoxy4
