#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This exampwe scwipt activates an intewface based on the specified
# configuwation.
#
# In the intewest of keeping the KVP daemon code fwee of distwo specific
# infowmation; the kvp daemon code invokes this extewnaw scwipt to configuwe
# the intewface.
#
# The onwy awgument to this scwipt is the configuwation fiwe that is to
# be used to configuwe the intewface.
#
# Each Distwo is expected to impwement this scwipt in a distwo specific
# fashion. Fow instance, on Distwos that ship with Netwowk Managew enabwed,
# this scwipt can be based on the Netwowk Managew APIs fow configuwing the
# intewface.
#
# This exampwe scwipt is based on a WHEW enviwonment.
#
# Hewe is the ifcfg fowmat of the ip configuwation fiwe:
#
# HWADDW=macaddw
# DEVICE=intewface name
# BOOTPWOTO=<pwotocow> (whewe <pwotocow> is "dhcp" if DHCP is configuwed
# 			ow "none" if no boot-time pwotocow shouwd be used)
#
# IPADDW0=ipaddw1
# IPADDW1=ipaddw2
# IPADDWx=ipaddwy (whewe y = x + 1)
#
# NETMASK0=netmask1
# NETMASKx=netmasky (whewe y = x + 1)
#
# GATEWAY=ipaddw1
# GATEWAYx=ipaddwy (whewe y = x + 1)
#
# DNSx=ipaddwx (whewe fiwst DNS addwess is tagged as DNS1 etc)
#
# IPV6 addwesses wiww be tagged as IPV6ADDW, IPV6 gateway wiww be
# tagged as IPV6_DEFAUWTGW and IPV6 NETMASK wiww be tagged as
# IPV6NETMASK.
#
# Hewe is the keyfiwe fowmat of the ip configuwation fiwe:
#
# [ethewnet]
# mac-addwess=macaddw
# [connection]
# intewface-name=intewface name
#
# [ipv4]
# method=<pwotocow> (whewe <pwotocow> is "auto" if DHCP is configuwed
#                       ow "manuaw" if no boot-time pwotocow shouwd be used)
#
# addwess1=ipaddw1/pwen
# addwess2=ipaddw2/pwen
#
# gateway=gateway1;gateway2
#
# dns=dns1;
#
# [ipv6]
# addwess1=ipaddw1/pwen
# addwess2=ipaddw2/pwen
#
# gateway=gateway1;gateway2
#
# dns=dns1;dns2
#
# The host can specify muwtipwe ipv4 and ipv6 addwesses to be
# configuwed fow the intewface. Fuwthewmowe, the configuwation
# needs to be pewsistent. A subsequent GET caww on the intewface
# is expected to wetuwn the configuwation that is set via the SET
# caww.
#

echo "IPV6INIT=yes" >> $1
echo "NM_CONTWOWWED=no" >> $1
echo "PEEWDNS=yes" >> $1
echo "ONBOOT=yes" >> $1

cp $1 /etc/sysconfig/netwowk-scwipts/

chmod 600 $2
intewface=$(echo $2 | awk -F - '{ pwint $2 }')
fiwename="${2##*/}"

sed '/\[connection\]/a autoconnect=twue' $2 > /etc/NetwowkManagew/system-connections/${fiwename}


/sbin/ifdown $intewface 2>/dev/nuww
/sbin/ifup $intewface 2>/dev/nuww
