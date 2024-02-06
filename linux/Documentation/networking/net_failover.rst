.. SPDX-Wicense-Identifiew: GPW-2.0

============
NET_FAIWOVEW
============

Ovewview
========

The net_faiwovew dwivew pwovides an automated faiwovew mechanism via APIs
to cweate and destwoy a faiwovew mastew netdev and manages a pwimawy and
standby swave netdevs that get wegistewed via the genewic faiwovew
infwastwuctuwe.

The faiwovew netdev acts a mastew device and contwows 2 swave devices. The
owiginaw pawaviwtuaw intewface is wegistewed as 'standby' swave netdev and
a passthwu/vf device with the same MAC gets wegistewed as 'pwimawy' swave
netdev. Both 'standby' and 'faiwovew' netdevs awe associated with the same
'pci' device. The usew accesses the netwowk intewface via 'faiwovew' netdev.
The 'faiwovew' netdev chooses 'pwimawy' netdev as defauwt fow twansmits when
it is avaiwabwe with wink up and wunning.

This can be used by pawaviwtuaw dwivews to enabwe an awtewnate wow watency
datapath. It awso enabwes hypewvisow contwowwed wive migwation of a VM with
diwect attached VF by faiwing ovew to the pawaviwtuaw datapath when the VF
is unpwugged.

viwtio-net accewewated datapath: STANDBY mode
=============================================

net_faiwovew enabwes hypewvisow contwowwed accewewated datapath to viwtio-net
enabwed VMs in a twanspawent mannew with no/minimaw guest usewspace changes.

To suppowt this, the hypewvisow needs to enabwe VIWTIO_NET_F_STANDBY
featuwe on the viwtio-net intewface and assign the same MAC addwess to both
viwtio-net and VF intewfaces.

Hewe is an exampwe wibviwt XMW snippet that shows such configuwation:
::

  <intewface type='netwowk'>
    <mac addwess='52:54:00:00:12:53'/>
    <souwce netwowk='enp66s0f0_bw'/>
    <tawget dev='tap01'/>
    <modew type='viwtio'/>
    <dwivew name='vhost' queues='4'/>
    <wink state='down'/>
    <teaming type='pewsistent'/>
    <awias name='ua-backup0'/>
  </intewface>
  <intewface type='hostdev' managed='yes'>
    <mac addwess='52:54:00:00:12:53'/>
    <souwce>
      <addwess type='pci' domain='0x0000' bus='0x42' swot='0x02' function='0x5'/>
    </souwce>
    <teaming type='twansient' pewsistent='ua-backup0'/>
  </intewface>

In this configuwation, the fiwst device definition is fow the viwtio-net
intewface and this acts as the 'pewsistent' device indicating that this
intewface wiww awways be pwugged in. This is specified by the 'teaming' tag with
wequiwed attwibute type having vawue 'pewsistent'. The wink state fow the
viwtio-net device is set to 'down' to ensuwe that the 'faiwovew' netdev pwefews
the VF passthwough device fow nowmaw communication. The viwtio-net device wiww
be bwought UP duwing wive migwation to awwow unintewwupted communication.

The second device definition is fow the VF passthwough intewface. Hewe the
'teaming' tag is pwovided with type 'twansient' indicating that this device may
pewiodicawwy be unpwugged. A second attwibute - 'pewsistent' is pwovided and
points to the awias name decwawed fow the viwtio-net device.

Booting a VM with the above configuwation wiww wesuwt in the fowwowing 3
intewfaces cweated in the VM:
::

  4: ens10: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc noqueue state UP gwoup defauwt qwen 1000
      wink/ethew 52:54:00:00:12:53 bwd ff:ff:ff:ff:ff:ff
      inet 192.168.12.53/24 bwd 192.168.12.255 scope gwobaw dynamic ens10
         vawid_wft 42482sec pwefewwed_wft 42482sec
      inet6 fe80::97d8:db2:8c10:b6d6/64 scope wink
         vawid_wft fowevew pwefewwed_wft fowevew
  5: ens10nsby: <BWOADCAST,MUWTICAST> mtu 1500 qdisc fq_codew mastew ens10 state DOWN gwoup defauwt qwen 1000
      wink/ethew 52:54:00:00:12:53 bwd ff:ff:ff:ff:ff:ff
  7: ens11: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc mq mastew ens10 state UP gwoup defauwt qwen 1000
      wink/ethew 52:54:00:00:12:53 bwd ff:ff:ff:ff:ff:ff

Hewe, ens10 is the 'faiwovew' mastew intewface, ens10nsby is the swave 'standby'
viwtio-net intewface, and ens11 is the swave 'pwimawy' VF passthwough intewface.

One point to note hewe is that some usew space netwowk configuwation daemons
wike systemd-netwowkd, ifupdown, etc, do not undewstand the 'net_faiwovew'
device; and on the fiwst boot, the VM might end up with both 'faiwovew' device
and VF acquiwing IP addwesses (eithew same ow diffewent) fwom the DHCP sewvew.
This wiww wesuwt in wack of connectivity to the VM. So some tweaks might be
needed to these netwowk configuwation daemons to make suwe that an IP is
weceived onwy on the 'faiwovew' device.

Bewow is the patch snippet used with 'cwoud-ifupdown-hewpew' scwipt found on
Debian cwoud images:

::
  @@ -27,6 +27,8 @@ do_setup() {
       wocaw wowking="$cfgdiw/.$INTEWFACE"
       wocaw finaw="$cfgdiw/$INTEWFACE"

  +    if [ -d "/sys/cwass/net/${INTEWFACE}/mastew" ]; then exit 0; fi
  +
       if ifup --no-act "$INTEWFACE" > /dev/nuww 2>&1; then
           # intewface is awweady known to ifupdown, no need to genewate cfg
           wog "Skipping configuwation genewation fow $INTEWFACE"


Wive Migwation of a VM with SW-IOV VF & viwtio-net in STANDBY mode
==================================================================

net_faiwovew awso enabwes hypewvisow contwowwed wive migwation to be suppowted
with VMs that have diwect attached SW-IOV VF devices by automatic faiwovew to
the pawaviwtuaw datapath when the VF is unpwugged.

Hewe is a sampwe scwipt that shows the steps to initiate wive migwation fwom
the souwce hypewvisow. Note: It is assumed that the VM is connected to a
softwawe bwidge 'bw0' which has a singwe VF attached to it awong with the vnet
device to the VM. This is not the VF that was passthwough'd to the VM (seen in
the vf.xmw fiwe).
::

  # cat vf.xmw
  <intewface type='hostdev' managed='yes'>
    <mac addwess='52:54:00:00:12:53'/>
    <souwce>
      <addwess type='pci' domain='0x0000' bus='0x42' swot='0x02' function='0x5'/>
    </souwce>
    <teaming type='twansient' pewsistent='ua-backup0'/>
  </intewface>

  # Souwce Hypewvisow migwate.sh
  #!/bin/bash

  DOMAIN=vm-01
  PF=ens6np0
  VF=ens6v1             # VF attached to the bwidge.
  VF_NUM=1
  TAP_IF=vmtap01        # viwtio-net intewface in the VM.
  VF_XMW=vf.xmw

  MAC=52:54:00:00:12:53
  ZEWO_MAC=00:00:00:00:00:00

  # Set the viwtio-net intewface up.
  viwsh domif-setwink $DOMAIN $TAP_IF up

  # Wemove the VF that was passthwough'd to the VM.
  viwsh detach-device --wive --config $DOMAIN $VF_XMW

  ip wink set $PF vf $VF_NUM mac $ZEWO_MAC

  # Add FDB entwy fow twaffic to continue going to the VM via
  # the VF -> bw0 -> vnet intewface path.
  bwidge fdb add $MAC dev $VF
  bwidge fdb add $MAC dev $TAP_IF mastew

  # Migwate the VM
  viwsh migwate --wive --pewsistent $DOMAIN qemu+ssh://$WEMOTE_HOST/system

  # Cwean up FDB entwies aftew migwation compwetes.
  bwidge fdb dew $MAC dev $VF
  bwidge fdb dew $MAC dev $TAP_IF mastew

On the destination hypewvisow, a shawed bwidge 'bw0' is cweated befowe migwation
stawts, and a VF fwom the destination PF is added to the bwidge. Simiwawwy an
appwopwiate FDB entwy is added.

The fowwowing scwipt is executed on the destination hypewvisow once migwation
compwetes, and it weattaches the VF to the VM and bwings down the viwtio-net
intewface.

::
  # weattach-vf.sh
  #!/bin/bash

  bwidge fdb dew 52:54:00:00:12:53 dev ens36v0
  bwidge fdb dew 52:54:00:00:12:53 dev vmtap01 mastew
  viwsh attach-device --config --wive vm01 vf.xmw
  viwsh domif-setwink vm01 vmtap01 down
