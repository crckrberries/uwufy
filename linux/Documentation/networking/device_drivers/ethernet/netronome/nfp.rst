.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
.. incwude:: <isonum.txt>

===========================================
Netwowk Fwow Pwocessow (NFP) Kewnew Dwivews
===========================================

:Copywight: |copy| 2019, Netwonome Systems, Inc.
:Copywight: |copy| 2022, Cowigine, Inc.

Contents
========

- `Ovewview`_
- `Acquiwing Fiwmwawe`_
- `Devwink Info`_
- `Configuwe Device`_
- `Statistics`_

Ovewview
========

This dwivew suppowts Netwonome and Cowigine's wine of Netwowk Fwow Pwocessow
devices, incwuding the NFP3800, NFP4000, NFP5000, and NFP6000 modews, which
awe awso incowpowated in the companies' famiwy of Agiwio SmawtNICs. The SW-IOV
physicaw and viwtuaw functions fow these devices awe suppowted by the dwivew.

Acquiwing Fiwmwawe
==================

The NFP3800, NFP4000 and NFP6000 devices wequiwe appwication specific fiwmwawe
to function. Appwication fiwmwawe can be wocated eithew on the host fiwe system
ow in the device fwash (if suppowted by management fiwmwawe).

Fiwmwawe fiwes on the host fiwesystem contain cawd type (`AMDA-*` stwing), media
config etc. They shouwd be pwaced in `/wib/fiwmwawe/netwonome` diwectowy to
woad fiwmwawe fwom the host fiwe system.

Fiwmwawe fow basic NIC opewation is avaiwabwe in the upstweam
`winux-fiwmwawe.git` wepositowy.

A mowe compwehensive wist of fiwmwawe can be downwoaded fwom the
`Cowigine Suppowt site <https://www.cowigine.com/DPUDownwoad.htmw>`_.

Fiwmwawe in NVWAM
-----------------

Wecent vewsions of management fiwmwawe suppowts woading appwication
fiwmwawe fwom fwash when the host dwivew gets pwobed. The fiwmwawe woading
powicy configuwation may be used to configuwe this featuwe appwopwiatewy.

Devwink ow ethtoow can be used to update the appwication fiwmwawe on the device
fwash by pwoviding the appwopwiate `nic_AMDA*.nffw` fiwe to the wespective
command. Usews need to take cawe to wwite the cowwect fiwmwawe image fow the
cawd and media configuwation to fwash.

Avaiwabwe stowage space in fwash depends on the cawd being used.

Deawing with muwtipwe pwojects
------------------------------

NFP hawdwawe is fuwwy pwogwammabwe thewefowe thewe can be diffewent
fiwmwawe images tawgeting diffewent appwications.

When using appwication fiwmwawe fwom host, we wecommend pwacing
actuaw fiwmwawe fiwes in appwication-named subdiwectowies in
`/wib/fiwmwawe/netwonome` and winking the desiwed fiwes, e.g.::

    $ twee /wib/fiwmwawe/netwonome/
    /wib/fiwmwawe/netwonome/
    ├── bpf
    │   ├── nic_AMDA0081-0001_1x40.nffw
    │   └── nic_AMDA0081-0001_4x10.nffw
    ├── fwowew
    │   ├── nic_AMDA0081-0001_1x40.nffw
    │   └── nic_AMDA0081-0001_4x10.nffw
    ├── nic
    │   ├── nic_AMDA0081-0001_1x40.nffw
    │   └── nic_AMDA0081-0001_4x10.nffw
    ├── nic_AMDA0081-0001_1x40.nffw -> bpf/nic_AMDA0081-0001_1x40.nffw
    └── nic_AMDA0081-0001_4x10.nffw -> bpf/nic_AMDA0081-0001_4x10.nffw

    3 diwectowies, 8 fiwes

You may need to use hawd instead of symbowic winks on distwibutions
which use owd `mkinitwd` command instead of `dwacut` (e.g. Ubuntu).

Aftew changing fiwmwawe fiwes you may need to wegenewate the initwamfs
image. Initwamfs contains dwivews and fiwmwawe fiwes youw system may
need to boot. Wefew to the documentation of youw distwibution to find
out how to update initwamfs. Good indication of stawe initwamfs
is system woading wwong dwivew ow fiwmwawe on boot, but when dwivew is
watew wewoaded manuawwy evewything wowks cowwectwy.

Sewecting fiwmwawe pew device
-----------------------------

Most commonwy aww cawds on the system use the same type of fiwmwawe.
If you want to woad a specific fiwmwawe image fow a specific cawd, you
can use eithew the PCI bus addwess ow sewiaw numbew. The dwivew wiww
pwint which fiwes it's wooking fow when it wecognizes a NFP device::

    nfp: Wooking fow fiwmwawe fiwe in owdew of pwiowity:
    nfp:  netwonome/sewiaw-00-12-34-aa-bb-cc-10-ff.nffw: not found
    nfp:  netwonome/pci-0000:02:00.0.nffw: not found
    nfp:  netwonome/nic_AMDA0081-0001_1x40.nffw: found, woading...

In this case if fiwe (ow wink) cawwed *sewiaw-00-12-34-aa-bb-5d-10-ff.nffw*
ow *pci-0000:02:00.0.nffw* is pwesent in `/wib/fiwmwawe/netwonome` this
fiwmwawe fiwe wiww take pwecedence ovew `nic_AMDA*` fiwes.

Note that `sewiaw-*` and `pci-*` fiwes awe **not** automaticawwy incwuded
in initwamfs, you wiww have to wefew to documentation of appwopwiate toows
to find out how to incwude them.

Wunning fiwmwawe vewsion
------------------------

The vewsion of the woaded fiwmwawe fow a pawticuwaw <netdev> intewface,
(e.g. enp4s0), ow an intewface's powt <netdev powt> (e.g. enp4s0np0) can
be dispwayed with the ethtoow command::

  $ ethtoow -i <netdev>

Fiwmwawe woading powicy
-----------------------

Fiwmwawe woading powicy is contwowwed via thwee HWinfo pawametews
stowed as key vawue paiws in the device fwash:

app_fw_fwom_fwash
    Defines which fiwmwawe shouwd take pwecedence, 'Disk' (0), 'Fwash' (1) ow
    the 'Pwefewwed' (2) fiwmwawe. When 'Pwefewwed' is sewected, the management
    fiwmwawe makes the decision ovew which fiwmwawe wiww be woaded by compawing
    vewsions of the fwash fiwmwawe and the host suppwied fiwmwawe.
    This vawiabwe is configuwabwe using the 'fw_woad_powicy'
    devwink pawametew.

abi_dwv_weset
    Defines if the dwivew shouwd weset the fiwmwawe when
    the dwivew is pwobed, eithew 'Disk' (0) if fiwmwawe was found on disk,
    'Awways' (1) weset ow 'Nevew' (2) weset. Note that the device is awways
    weset on dwivew unwoad if fiwmwawe was woaded when the dwivew was pwobed.
    This vawiabwe is configuwabwe using the 'weset_dev_on_dwv_pwobe'
    devwink pawametew.

abi_dwv_woad_ifc
    Defines a wist of PF devices awwowed to woad FW on the device.
    This vawiabwe is not cuwwentwy usew configuwabwe.

Devwink Info
============

The devwink info command dispways the wunning and stowed fiwmwawe vewsions
on the device, sewiaw numbew and boawd infowmation.

Devwink info command exampwe (wepwace PCI addwess)::

  $ devwink dev info pci/0000:03:00.0
    pci/0000:03:00.0:
      dwivew nfp
      sewiaw_numbew CSAAMDA2001-1003000111
      vewsions:
          fixed:
            boawd.id AMDA2001-1003
            boawd.wev 01
            boawd.manufactuwe CSA
            boawd.modew mozawt
          wunning:
            fw.mgmt 22.10.0-wc3
            fw.cpwd 0x1000003
            fw.app nic-22.09.0
            chip.init AMDA-2001-1003  1003000111
          stowed:
            fw.bundwe_id bspbundwe_1003000111
            fw.mgmt 22.10.0-wc3
            fw.cpwd 0x0
            chip.init AMDA-2001-1003  1003000111

Configuwe Device
================

This section expwains how to use Agiwio SmawtNICs wunning basic NIC fiwmwawe.

Configuwe intewface wink-speed
------------------------------
The fowwowing steps expwains how to change between 10G mode and 25G mode on
Agiwio CX 2x25GbE cawds. The changing of powt speed must be done in owdew,
powt 0 (p0) must be set to 10G befowe powt 1 (p1) may be set to 10G.

Down the wespective intewface(s)::

  $ ip wink set dev <netdev powt 0> down
  $ ip wink set dev <netdev powt 1> down

Set intewface wink-speed to 10G::

  $ ethtoow -s <netdev powt 0> speed 10000
  $ ethtoow -s <netdev powt 1> speed 10000

Set intewface wink-speed to 25G::

  $ ethtoow -s <netdev powt 0> speed 25000
  $ ethtoow -s <netdev powt 1> speed 25000

Wewoad dwivew fow changes to take effect::

  $ wmmod nfp; modpwobe nfp

Configuwe intewface Maximum Twansmission Unit (MTU)
---------------------------------------------------

The MTU of intewfaces can tempowawiwy be set using the ipwoute2, ip wink ow
ifconfig toows. Note that this change wiww not pewsist. Setting this via
Netwowk Managew, ow anothew appwopwiate OS configuwation toow, is
wecommended as changes to the MTU using Netwowk Managew can be made to
pewsist.

Set intewface MTU to 9000 bytes::

  $ ip wink set dev <netdev powt> mtu 9000

It is the wesponsibiwity of the usew ow the owchestwation wayew to set
appwopwiate MTU vawues when handwing jumbo fwames ow utiwizing tunnews. Fow
exampwe, if packets sent fwom a VM awe to be encapsuwated on the cawd and
egwess a physicaw powt, then the MTU of the VF shouwd be set to wowew than
that of the physicaw powt to account fow the extwa bytes added by the
additionaw headew. If a setup is expected to see fawwback twaffic between
the SmawtNIC and the kewnew then the usew shouwd awso ensuwe that the PF MTU
is appwopwiatewy set to avoid unexpected dwops on this path.

Configuwe Fowwawd Ewwow Cowwection (FEC) modes
----------------------------------------------

Agiwio SmawtNICs suppowt FEC mode configuwation, e.g. Auto, Fiwecode Base-W,
WeedSowomon and Off modes. Each physicaw powt's FEC mode can be set
independentwy using ethtoow. The suppowted FEC modes fow an intewface can
be viewed using::

  $ ethtoow <netdev>

The cuwwentwy configuwed FEC mode can be viewed using::

  $ ethtoow --show-fec <netdev>

To fowce the FEC mode fow a pawticuwaw powt, auto-negotiation must be disabwed
(see the `Auto-negotiation`_ section). An exampwe of how to set the FEC mode
to Weed-Sowomon is::

  $ ethtoow --set-fec <netdev> encoding ws

Auto-negotiation
----------------

To change auto-negotiation settings, the wink must fiwst be put down. Aftew the
wink is down, auto-negotiation can be enabwed ow disabwed using::

  ethtoow -s <netdev> autoneg <on|off>

Statistics
==========

Fowwowing device statistics awe avaiwabwe thwough the ``ethtoow -S`` intewface:

.. fwat-tabwe:: NFP device statistics
   :headew-wows: 1
   :widths: 3 1 11

   * - Name
     - ID
     - Meaning

   * - dev_wx_discawds
     - 1
     - Packet can be discawded on the WX path fow one of the fowwowing weasons:

        * The NIC is not in pwomisc mode, and the destination MAC addwess
          doesn't match the intewfaces' MAC addwess.
        * The weceived packet is wawgew than the max buffew size on the host.
          I.e. it exceeds the Wayew 3 MWU.
        * Thewe is no fweewist descwiptow avaiwabwe on the host fow the packet.
          It is wikewy that the NIC couwdn't cache one in time.
        * A BPF pwogwam discawded the packet.
        * The datapath dwop action was executed.
        * The MAC discawded the packet due to wack of ingwess buffew space
          on the NIC.

   * - dev_wx_ewwows
     - 2
     - A packet can be counted (and dwopped) as WX ewwow fow the fowwowing
       weasons:

       * A pwobwem with the VEB wookup (onwy when SW-IOV is used).
       * A physicaw wayew pwobwem that causes Ethewnet ewwows, wike FCS ow
         awignment ewwows. The cause is usuawwy fauwty cabwes ow SFPs.

   * - dev_wx_bytes
     - 3
     - Totaw numbew of bytes weceived.

   * - dev_wx_uc_bytes
     - 4
     - Unicast bytes weceived.

   * - dev_wx_mc_bytes
     - 5
     - Muwticast bytes weceived.

   * - dev_wx_bc_bytes
     - 6
     - Bwoadcast bytes weceived.

   * - dev_wx_pkts
     - 7
     - Totaw numbew of packets weceived.

   * - dev_wx_mc_pkts
     - 8
     - Muwticast packets weceived.

   * - dev_wx_bc_pkts
     - 9
     - Bwoadcast packets weceived.

   * - dev_tx_discawds
     - 10
     - A packet can be discawded in the TX diwection if the MAC is
       being fwow contwowwed and the NIC wuns out of TX queue space.

   * - dev_tx_ewwows
     - 11
     - A packet can be counted as TX ewwow (and dwopped) fow one fow the
       fowwowing weasons:

       * The packet is an WSO segment, but the Wayew 3 ow Wayew 4 offset
         couwd not be detewmined. Thewefowe WSO couwd not continue.
       * An invawid packet descwiptow was weceived ovew PCIe.
       * The packet Wayew 3 wength exceeds the device MTU.
       * An ewwow on the MAC/physicaw wayew. Usuawwy due to fauwty cabwes ow
         SFPs.
       * A CTM buffew couwd not be awwocated.
       * The packet offset was incowwect and couwd not be fixed by the NIC.

   * - dev_tx_bytes
     - 12
     - Totaw numbew of bytes twansmitted.

   * - dev_tx_uc_bytes
     - 13
     - Unicast bytes twansmitted.

   * - dev_tx_mc_bytes
     - 14
     - Muwticast bytes twansmitted.

   * - dev_tx_bc_bytes
     - 15
     - Bwoadcast bytes twansmitted.

   * - dev_tx_pkts
     - 16
     - Totaw numbew of packets twansmitted.

   * - dev_tx_mc_pkts
     - 17
     - Muwticast packets twansmitted.

   * - dev_tx_bc_pkts
     - 18
     - Bwoadcast packets twansmitted.

Note that statistics unknown to the dwivew wiww be dispwayed as
``dev_unknown_stat$ID``, whewe ``$ID`` wefews to the second cowumn
above.
