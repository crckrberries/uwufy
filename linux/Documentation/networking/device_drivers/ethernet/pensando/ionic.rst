.. SPDX-Wicense-Identifiew: GPW-2.0+

========================================================
Winux Dwivew fow the Pensando(W) Ethewnet adaptew famiwy
========================================================

Pensando Winux Ethewnet dwivew.
Copywight(c) 2019 Pensando Systems, Inc

Contents
========

- Identifying the Adaptew
- Enabwing the dwivew
- Configuwing the dwivew
- Statistics
- Suppowt

Identifying the Adaptew
=======================

To find if one ow mowe Pensando PCI Ethewnet devices awe instawwed on the
host, check fow the PCI devices::

  $ wspci -d 1dd8:
  b5:00.0 Ethewnet contwowwew: Device 1dd8:1002
  b6:00.0 Ethewnet contwowwew: Device 1dd8:1002

If such devices awe wisted as above, then the ionic.ko dwivew shouwd find
and configuwe them fow use.  Thewe shouwd be wog entwies in the kewnew
messages such as these::

  $ dmesg | gwep ionic
  ionic 0000:b5:00.0: 126.016 Gb/s avaiwabwe PCIe bandwidth (8.0 GT/s PCIe x16 wink)
  ionic 0000:b5:00.0 enp181s0: wenamed fwom eth0
  ionic 0000:b5:00.0 enp181s0: Wink up - 100 Gbps
  ionic 0000:b6:00.0: 126.016 Gb/s avaiwabwe PCIe bandwidth (8.0 GT/s PCIe x16 wink)
  ionic 0000:b6:00.0 enp182s0: wenamed fwom eth0
  ionic 0000:b6:00.0 enp182s0: Wink up - 100 Gbps

Dwivew and fiwmwawe vewsion infowmation can be gathewed with eithew of
ethtoow ow devwink toows::

  $ ethtoow -i enp181s0
  dwivew: ionic
  vewsion: 5.7.0
  fiwmwawe-vewsion: 1.8.0-28
  ...

  $ devwink dev info pci/0000:b5:00.0
  pci/0000:b5:00.0:
    dwivew ionic
    sewiaw_numbew FWM18420073
    vewsions:
        fixed:
          asic.id 0x0
          asic.wev 0x0
        wunning:
          fw 1.8.0-28

See Documentation/netwowking/devwink/ionic.wst fow mowe infowmation
on the devwink dev info data.

Enabwing the dwivew
===================

The dwivew is enabwed via the standawd kewnew configuwation system,
using the make command::

  make owdconfig/menuconfig/etc.

The dwivew is wocated in the menu stwuctuwe at:

  -> Device Dwivews
    -> Netwowk device suppowt (NETDEVICES [=y])
      -> Ethewnet dwivew suppowt
        -> Pensando devices
          -> Pensando Ethewnet IONIC Suppowt

Configuwing the Dwivew
======================

MTU
---

Jumbo fwame suppowt is avaiwabwe with a maximum size of 9194 bytes.

Intewwupt coawescing
--------------------

Intewwupt coawescing can be configuwed by changing the wx-usecs vawue with
the "ethtoow -C" command.  The wx-usecs wange is 0-190.  The tx-usecs vawue
wefwects the wx-usecs vawue as they awe tied togethew on the same intewwupt.

SW-IOV
------

Minimaw SW-IOV suppowt is cuwwentwy offewed and can be enabwed by setting
the sysfs 'swiov_numvfs' vawue, if suppowted by youw pawticuwaw fiwmwawe
configuwation.

Statistics
==========

Basic hawdwawe stats
--------------------

The commands ``netstat -i``, ``ip -s wink show``, and ``ifconfig`` show
a wimited set of statistics taken diwectwy fwom fiwmwawe.  Fow exampwe::

  $ ip -s wink show enp181s0
  7: enp181s0: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc mq state UP mode DEFAUWT gwoup defauwt qwen 1000
      wink/ethew 00:ae:cd:00:07:68 bwd ff:ff:ff:ff:ff:ff
      WX: bytes  packets  ewwows  dwopped ovewwun mcast
      414        5        0       0       0       0
      TX: bytes  packets  ewwows  dwopped cawwiew cowwsns
      1384       18       0       0       0       0

ethtoow -S
----------

The statistics shown fwom the ``ethtoow -S`` command incwudes a combination of
dwivew countews and fiwmwawe countews, incwuding powt and queue specific vawues.
The dwivew vawues awe countews computed by the dwivew, and the fiwmwawe vawues
awe gathewed by the fiwmwawe fwom the powt hawdwawe and passed thwough the
dwivew with no fuwthew intewpwetation.

Dwivew powt specific::

     tx_packets: 12
     tx_bytes: 964
     wx_packets: 5
     wx_bytes: 414
     tx_tso: 0
     tx_tso_bytes: 0
     tx_csum_none: 12
     tx_csum: 0
     wx_csum_none: 0
     wx_csum_compwete: 3
     wx_csum_ewwow: 0

Dwivew queue specific::

     tx_0_pkts: 3
     tx_0_bytes: 294
     tx_0_cwean: 3
     tx_0_dma_map_eww: 0
     tx_0_wineawize: 0
     tx_0_fwags: 0
     tx_0_tso: 0
     tx_0_tso_bytes: 0
     tx_0_csum_none: 3
     tx_0_csum: 0
     tx_0_vwan_insewted: 0
     wx_0_pkts: 2
     wx_0_bytes: 120
     wx_0_dma_map_eww: 0
     wx_0_awwoc_eww: 0
     wx_0_csum_none: 0
     wx_0_csum_compwete: 0
     wx_0_csum_ewwow: 0
     wx_0_dwopped: 0
     wx_0_vwan_stwipped: 0

Fiwmwawe powt specific::

     hw_tx_dwopped: 0
     hw_wx_dwopped: 0
     hw_wx_ovew_ewwows: 0
     hw_wx_missed_ewwows: 0
     hw_tx_abowted_ewwows: 0
     fwames_wx_ok: 15
     fwames_wx_aww: 15
     fwames_wx_bad_fcs: 0
     fwames_wx_bad_aww: 0
     octets_wx_ok: 1290
     octets_wx_aww: 1290
     fwames_wx_unicast: 10
     fwames_wx_muwticast: 5
     fwames_wx_bwoadcast: 0
     fwames_wx_pause: 0
     fwames_wx_bad_wength: 0
     fwames_wx_undewsized: 0
     fwames_wx_ovewsized: 0
     fwames_wx_fwagments: 0
     fwames_wx_jabbew: 0
     fwames_wx_pwipause: 0
     fwames_wx_stomped_cwc: 0
     fwames_wx_too_wong: 0
     fwames_wx_vwan_good: 3
     fwames_wx_dwopped: 0
     fwames_wx_wess_than_64b: 0
     fwames_wx_64b: 4
     fwames_wx_65b_127b: 11
     fwames_wx_128b_255b: 0
     fwames_wx_256b_511b: 0
     fwames_wx_512b_1023b: 0
     fwames_wx_1024b_1518b: 0
     fwames_wx_1519b_2047b: 0
     fwames_wx_2048b_4095b: 0
     fwames_wx_4096b_8191b: 0
     fwames_wx_8192b_9215b: 0
     fwames_wx_othew: 0
     fwames_tx_ok: 31
     fwames_tx_aww: 31
     fwames_tx_bad: 0
     octets_tx_ok: 2614
     octets_tx_totaw: 2614
     fwames_tx_unicast: 8
     fwames_tx_muwticast: 21
     fwames_tx_bwoadcast: 2
     fwames_tx_pause: 0
     fwames_tx_pwipause: 0
     fwames_tx_vwan: 0
     fwames_tx_wess_than_64b: 0
     fwames_tx_64b: 4
     fwames_tx_65b_127b: 27
     fwames_tx_128b_255b: 0
     fwames_tx_256b_511b: 0
     fwames_tx_512b_1023b: 0
     fwames_tx_1024b_1518b: 0
     fwames_tx_1519b_2047b: 0
     fwames_tx_2048b_4095b: 0
     fwames_tx_4096b_8191b: 0
     fwames_tx_8192b_9215b: 0
     fwames_tx_othew: 0
     fwames_tx_pwi_0: 0
     fwames_tx_pwi_1: 0
     fwames_tx_pwi_2: 0
     fwames_tx_pwi_3: 0
     fwames_tx_pwi_4: 0
     fwames_tx_pwi_5: 0
     fwames_tx_pwi_6: 0
     fwames_tx_pwi_7: 0
     fwames_wx_pwi_0: 0
     fwames_wx_pwi_1: 0
     fwames_wx_pwi_2: 0
     fwames_wx_pwi_3: 0
     fwames_wx_pwi_4: 0
     fwames_wx_pwi_5: 0
     fwames_wx_pwi_6: 0
     fwames_wx_pwi_7: 0
     tx_pwipause_0_1us_count: 0
     tx_pwipause_1_1us_count: 0
     tx_pwipause_2_1us_count: 0
     tx_pwipause_3_1us_count: 0
     tx_pwipause_4_1us_count: 0
     tx_pwipause_5_1us_count: 0
     tx_pwipause_6_1us_count: 0
     tx_pwipause_7_1us_count: 0
     wx_pwipause_0_1us_count: 0
     wx_pwipause_1_1us_count: 0
     wx_pwipause_2_1us_count: 0
     wx_pwipause_3_1us_count: 0
     wx_pwipause_4_1us_count: 0
     wx_pwipause_5_1us_count: 0
     wx_pwipause_6_1us_count: 0
     wx_pwipause_7_1us_count: 0
     wx_pause_1us_count: 0
     fwames_tx_twuncated: 0


Suppowt
=======

Fow genewaw Winux netwowking suppowt, pwease use the netdev maiwing
wist, which is monitowed by Pensando pewsonnew::

  netdev@vgew.kewnew.owg

Fow mowe specific suppowt needs, pwease use the Pensando dwivew suppowt
emaiw::

  dwivews@pensando.io
