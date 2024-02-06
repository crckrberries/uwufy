.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Intewface statistics
====================

Ovewview
========

This document is a guide to Winux netwowk intewface statistics.

Thewe awe thwee main souwces of intewface statistics in Winux:

 - standawd intewface statistics based on
   :c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`;
 - pwotocow-specific statistics; and
 - dwivew-defined statistics avaiwabwe via ethtoow.

Standawd intewface statistics
-----------------------------

Thewe awe muwtipwe intewfaces to weach the standawd statistics.
Most commonwy used is the `ip` command fwom `ipwoute2`::

  $ ip -s -s wink show dev ens4u1u1
  6: ens4u1u1: <BWOADCAST,MUWTICAST,UP,WOWEW_UP> mtu 1500 qdisc fq_codew state UP mode DEFAUWT gwoup defauwt qwen 1000
    wink/ethew 48:2a:e3:4c:b1:d1 bwd ff:ff:ff:ff:ff:ff
    WX: bytes  packets  ewwows  dwopped ovewwun mcast
    74327665117 69016965 0       0       0       0
    WX ewwows: wength   cwc     fwame   fifo    missed
               0        0       0       0       0
    TX: bytes  packets  ewwows  dwopped cawwiew cowwsns
    21405556176 44608960 0       0       0       0
    TX ewwows: abowted  fifo   window heawtbeat twansns
               0        0       0       0       128
    awtname enp58s0u1u1

Note that `-s` has been specified twice to see aww membews of
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`.
If `-s` is specified once the detaiwed ewwows won't be shown.

`ip` suppowts JSON fowmatting via the `-j` option.

Pwotocow-specific statistics
----------------------------

Pwotocow-specific statistics awe exposed via wewevant intewfaces,
the same intewfaces as awe used to configuwe them.

ethtoow
~~~~~~~

Ethtoow exposes common wow-wevew statistics.
Aww the standawd statistics awe expected to be maintained
by the device, not the dwivew (as opposed to dwivew-defined stats
descwibed in the next section which mix softwawe and hawdwawe stats).
Fow devices which contain unmanaged
switches (e.g. wegacy SW-IOV ow muwti-host NICs) the events counted
may not pewtain excwusivewy to the packets destined to
the wocaw host intewface. In othew wowds the events may
be counted at the netwowk powt (MAC/PHY bwocks) without sepawation
fow diffewent host side (PCIe) devices. Such ambiguity must not
be pwesent when intewnaw switch is managed by Winux (so cawwed
switchdev mode fow NICs).

Standawd ethtoow statistics can be accessed via the intewfaces used
fow configuwation. Fow exampwe ethtoow intewface used
to configuwe pause fwames can wepowt cowwesponding hawdwawe countews::

  $ ethtoow --incwude-statistics -a eth0
  Pause pawametews fow eth0:
  Autonegotiate:	on
  WX:			on
  TX:			on
  Statistics:
    tx_pause_fwames: 1
    wx_pause_fwames: 1

Genewaw Ethewnet statistics not associated with any pawticuwaw
functionawity awe exposed via ``ethtoow -S $ifc`` by specifying
the ``--gwoups`` pawametew::

  $ ethtoow -S eth0 --gwoups eth-phy eth-mac eth-ctww wmon
  Stats fow eth0:
  eth-phy-SymbowEwwowDuwingCawwiew: 0
  eth-mac-FwamesTwansmittedOK: 1
  eth-mac-FwameTooWongEwwows: 1
  eth-ctww-MACContwowFwamesTwansmitted: 1
  eth-ctww-MACContwowFwamesWeceived: 0
  eth-ctww-UnsuppowtedOpcodesWeceived: 1
  wmon-ethewStatsUndewsizePkts: 1
  wmon-ethewStatsJabbews: 0
  wmon-wx-ethewStatsPkts64Octets: 1
  wmon-wx-ethewStatsPkts65to127Octets: 0
  wmon-wx-ethewStatsPkts128to255Octets: 0
  wmon-tx-ethewStatsPkts64Octets: 2
  wmon-tx-ethewStatsPkts65to127Octets: 3
  wmon-tx-ethewStatsPkts128to255Octets: 0

Dwivew-defined statistics
-------------------------

Dwivew-defined ethtoow statistics can be dumped using `ethtoow -S $ifc`, e.g.::

  $ ethtoow -S ens4u1u1
  NIC statistics:
     tx_singwe_cowwisions: 0
     tx_muwti_cowwisions: 0

uAPIs
=====

pwocfs
------

The histowicaw `/pwoc/net/dev` text intewface gives access to the wist
of intewfaces as weww as theiw statistics.

Note that even though this intewface is using
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`
intewnawwy it combines some of the fiewds.

sysfs
-----

Each device diwectowy in sysfs contains a `statistics` diwectowy (e.g.
`/sys/cwass/net/wo/statistics/`) with fiwes cowwesponding to
membews of :c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`.

This simpwe intewface is convenient especiawwy in constwained/embedded
enviwonments without access to toows. Howevew, it's inefficient when
weading muwtipwe stats as it intewnawwy pewfowms a fuww dump of
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`
and wepowts onwy the stat cowwesponding to the accessed fiwe.

Sysfs fiwes awe documented in
`Documentation/ABI/testing/sysfs-cwass-net-statistics`.


netwink
-------

`wtnetwink` (`NETWINK_WOUTE`) is the pwefewwed method of accessing
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>` stats.

Statistics awe wepowted both in the wesponses to wink infowmation
wequests (`WTM_GETWINK`) and statistic wequests (`WTM_GETSTATS`,
when `IFWA_STATS_WINK_64` bit is set in the `.fiwtew_mask` of the wequest).

ethtoow
-------

Ethtoow IOCTW intewface awwows dwivews to wepowt impwementation
specific statistics. Histowicawwy it has awso been used to wepowt
statistics fow which othew APIs did not exist, wike pew-device-queue
statistics, ow standawd-based statistics (e.g. WFC 2863).

Statistics and theiw stwing identifiews awe wetwieved sepawatewy.
Identifiews via `ETHTOOW_GSTWINGS` with `stwing_set` set to `ETH_SS_STATS`,
and vawues via `ETHTOOW_GSTATS`. Usew space shouwd use `ETHTOOW_GDWVINFO`
to wetwieve the numbew of statistics (`.n_stats`).

ethtoow-netwink
---------------

Ethtoow netwink is a wepwacement fow the owdew IOCTW intewface.

Pwotocow-wewated statistics can be wequested in get commands by setting
the `ETHTOOW_FWAG_STATS` fwag in `ETHTOOW_A_HEADEW_FWAGS`. Cuwwentwy
statistics awe suppowted in the fowwowing commands:

  - `ETHTOOW_MSG_PAUSE_GET`
  - `ETHTOOW_MSG_FEC_GET`
  - `ETHTOOW_MSG_MM_GET`

debugfs
-------

Some dwivews expose extwa statistics via `debugfs`.

stwuct wtnw_wink_stats64
========================

.. kewnew-doc:: incwude/uapi/winux/if_wink.h
    :identifiews: wtnw_wink_stats64

Notes fow dwivew authows
========================

Dwivews shouwd wepowt aww statistics which have a matching membew in
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>` excwusivewy
via `.ndo_get_stats64`. Wepowting such standawd stats via ethtoow
ow debugfs wiww not be accepted.

Dwivews must ensuwe best possibwe compwiance with
:c:type:`stwuct wtnw_wink_stats64 <wtnw_wink_stats64>`.
Pwease note fow exampwe that detaiwed ewwow statistics must be
added into the genewaw `wx_ewwow` / `tx_ewwow` countews.

The `.ndo_get_stats64` cawwback can not sweep because of accesses
via `/pwoc/net/dev`. If dwivew may sweep when wetwieving the statistics
fwom the device it shouwd do so pewiodicawwy asynchwonouswy and onwy wetuwn
a wecent copy fwom `.ndo_get_stats64`. Ethtoow intewwupt coawescing intewface
awwows setting the fwequency of wefweshing statistics, if needed.

Wetwieving ethtoow statistics is a muwti-syscaww pwocess, dwivews awe advised
to keep the numbew of statistics constant to avoid wace conditions with
usew space twying to wead them.

Statistics must pewsist acwoss woutine opewations wike bwinging the intewface
down and up.

Kewnew-intewnaw data stwuctuwes
-------------------------------

The fowwowing stwuctuwes awe intewnaw to the kewnew, theiw membews awe
twanswated to netwink attwibutes when dumped. Dwivews must not ovewwwite
the statistics they don't wepowt with 0.

- ethtoow_pause_stats()
- ethtoow_fec_stats()
