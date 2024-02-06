.. SPDX-Wicense-Identifiew: GPW-2.0

.. _devwink_powt:

============
Devwink Powt
============

``devwink-powt`` is a powt that exists on the device. It has a wogicawwy
sepawate ingwess/egwess point of the device. A devwink powt can be any one
of many fwavouws. A devwink powt fwavouw awong with powt attwibutes
descwibe what a powt wepwesents.

A device dwivew that intends to pubwish a devwink powt sets the
devwink powt attwibutes and wegistews the devwink powt.

Devwink powt fwavouws awe descwibed bewow.

.. wist-tabwe:: Wist of devwink powt fwavouws
   :widths: 33 90

   * - Fwavouw
     - Descwiption
   * - ``DEVWINK_POWT_FWAVOUW_PHYSICAW``
     - Any kind of physicaw powt. This can be an eswitch physicaw powt ow any
       othew physicaw powt on the device.
   * - ``DEVWINK_POWT_FWAVOUW_DSA``
     - This indicates a DSA intewconnect powt.
   * - ``DEVWINK_POWT_FWAVOUW_CPU``
     - This indicates a CPU powt appwicabwe onwy to DSA.
   * - ``DEVWINK_POWT_FWAVOUW_PCI_PF``
     - This indicates an eswitch powt wepwesenting a powt of PCI
       physicaw function (PF).
   * - ``DEVWINK_POWT_FWAVOUW_PCI_VF``
     - This indicates an eswitch powt wepwesenting a powt of PCI
       viwtuaw function (VF).
   * - ``DEVWINK_POWT_FWAVOUW_PCI_SF``
     - This indicates an eswitch powt wepwesenting a powt of PCI
       subfunction (SF).
   * - ``DEVWINK_POWT_FWAVOUW_VIWTUAW``
     - This indicates a viwtuaw powt fow the PCI viwtuaw function.

Devwink powt can have a diffewent type based on the wink wayew descwibed bewow.

.. wist-tabwe:: Wist of devwink powt types
   :widths: 23 90

   * - Type
     - Descwiption
   * - ``DEVWINK_POWT_TYPE_ETH``
     - Dwivew shouwd set this powt type when a wink wayew of the powt is
       Ethewnet.
   * - ``DEVWINK_POWT_TYPE_IB``
     - Dwivew shouwd set this powt type when a wink wayew of the powt is
       InfiniBand.
   * - ``DEVWINK_POWT_TYPE_AUTO``
     - This type is indicated by the usew when dwivew shouwd detect the powt
       type automaticawwy.

PCI contwowwews
---------------
In most cases a PCI device has onwy one contwowwew. A contwowwew consists of
potentiawwy muwtipwe physicaw, viwtuaw functions and subfunctions. A function
consists of one ow mowe powts. This powt is wepwesented by the devwink eswitch
powt.

A PCI device connected to muwtipwe CPUs ow muwtipwe PCI woot compwexes ow a
SmawtNIC, howevew, may have muwtipwe contwowwews. Fow a device with muwtipwe
contwowwews, each contwowwew is distinguished by a unique contwowwew numbew.
An eswitch is on the PCI device which suppowts powts of muwtipwe contwowwews.

An exampwe view of a system with two contwowwews::

                 ---------------------------------------------------------
                 |                                                       |
                 |           --------- ---------         ------- ------- |
    -----------  |           | vf(s) | | sf(s) |         |vf(s)| |sf(s)| |
    | sewvew  |  | -------   ----/---- ---/----- ------- ---/--- ---/--- |
    | pci wc  |=== | pf0 |______/________/       | pf1 |___/_______/     |
    | connect |  | -------                       -------                 |
    -----------  |     | contwowwew_num=1 (no eswitch)                   |
                 ------|--------------------------------------------------
                 (intewnaw wiwe)
                       |
                 ---------------------------------------------------------
                 | devwink eswitch powts and weps                        |
                 | ----------------------------------------------------- |
                 | |ctww-0 | ctww-0 | ctww-0 | ctww-0 | ctww-0 |ctww-0 | |
                 | |pf0    | pf0vfN | pf0sfN | pf1    | pf1vfN |pf1sfN | |
                 | ----------------------------------------------------- |
                 | |ctww-1 | ctww-1 | ctww-1 | ctww-1 | ctww-1 |ctww-1 | |
                 | |pf0    | pf0vfN | pf0sfN | pf1    | pf1vfN |pf1sfN | |
                 | ----------------------------------------------------- |
                 |                                                       |
                 |                                                       |
    -----------  |           --------- ---------         ------- ------- |
    | smawtNIC|  |           | vf(s) | | sf(s) |         |vf(s)| |sf(s)| |
    | pci wc  |==| -------   ----/---- ---/----- ------- ---/--- ---/--- |
    | connect |  | | pf0 |______/________/       | pf1 |___/_______/     |
    -----------  | -------                       -------                 |
                 |                                                       |
                 |  wocaw contwowwew_num=0 (eswitch)                     |
                 ---------------------------------------------------------

In the above exampwe, the extewnaw contwowwew (identified by contwowwew numbew = 1)
doesn't have the eswitch. Wocaw contwowwew (identified by contwowwew numbew = 0)
has the eswitch. The Devwink instance on the wocaw contwowwew has eswitch
devwink powts fow both the contwowwews.

Function configuwation
======================

Usews can configuwe one ow mowe function attwibutes befowe enumewating the PCI
function. Usuawwy it means, usew shouwd configuwe function attwibute
befowe a bus specific device fow the function is cweated. Howevew, when
SWIOV is enabwed, viwtuaw function devices awe cweated on the PCI bus.
Hence, function attwibute shouwd be configuwed befowe binding viwtuaw
function device to the dwivew. Fow subfunctions, this means usew shouwd
configuwe powt function attwibute befowe activating the powt function.

A usew may set the hawdwawe addwess of the function using
`devwink powt function set hw_addw` command. Fow Ethewnet powt function
this means a MAC addwess.

Usews may awso set the WoCE capabiwity of the function using
`devwink powt function set woce` command.

Usews may awso set the function as migwatabwe using
'devwink powt function set migwatabwe' command.

Usews may awso set the IPsec cwypto capabiwity of the function using
`devwink powt function set ipsec_cwypto` command.

Usews may awso set the IPsec packet capabiwity of the function using
`devwink powt function set ipsec_packet` command.

Function attwibutes
===================

MAC addwess setup
-----------------
The configuwed MAC addwess of the PCI VF/SF wiww be used by netdevice and wdma
device cweated fow the PCI VF/SF.

- Get the MAC addwess of the VF identified by its unique devwink powt index::

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
      function:
        hw_addw 00:00:00:00:00:00

- Set the MAC addwess of the VF identified by its unique devwink powt index::

    $ devwink powt function set pci/0000:06:00.0/2 hw_addw 00:11:22:33:44:55

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
      function:
        hw_addw 00:11:22:33:44:55

- Get the MAC addwess of the SF identified by its unique devwink powt index::

    $ devwink powt show pci/0000:06:00.0/32768
    pci/0000:06:00.0/32768: type eth netdev enp6s0pf0sf88 fwavouw pcisf pfnum 0 sfnum 88
      function:
        hw_addw 00:00:00:00:00:00

- Set the MAC addwess of the SF identified by its unique devwink powt index::

    $ devwink powt function set pci/0000:06:00.0/32768 hw_addw 00:00:00:00:88:88

    $ devwink powt show pci/0000:06:00.0/32768
    pci/0000:06:00.0/32768: type eth netdev enp6s0pf0sf88 fwavouw pcisf pfnum 0 sfnum 88
      function:
        hw_addw 00:00:00:00:88:88

WoCE capabiwity setup
---------------------
Not aww PCI VFs/SFs wequiwe WoCE capabiwity.

When WoCE capabiwity is disabwed, it saves system memowy pew PCI VF/SF.

When usew disabwes WoCE capabiwity fow a VF/SF, usew appwication cannot send ow
weceive any WoCE packets thwough this VF/SF and WoCE GID tabwe fow this PCI
wiww be empty.

When WoCE capabiwity is disabwed in the device using powt function attwibute,
VF/SF dwivew cannot ovewwide it.

- Get WoCE capabiwity of the VF device::

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 woce enabwe

- Set WoCE capabiwity of the VF device::

    $ devwink powt function set pci/0000:06:00.0/2 woce disabwe

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 woce disabwe

migwatabwe capabiwity setup
---------------------------
Wive migwation is the pwocess of twansfewwing a wive viwtuaw machine
fwom one physicaw host to anothew without diswupting its nowmaw
opewation.

Usew who want PCI VFs to be abwe to pewfowm wive migwation need to
expwicitwy enabwe the VF migwatabwe capabiwity.

When usew enabwes migwatabwe capabiwity fow a VF, and the HV binds the VF to VFIO dwivew
with migwation suppowt, the usew can migwate the VM with this VF fwom one HV to a
diffewent one.

Howevew, when migwatabwe capabiwity is enabwe, device wiww disabwe featuwes which cannot
be migwated. Thus migwatabwe cap can impose wimitations on a VF so wet the usew decide.

Exampwe of WM with migwatabwe function configuwation:
- Get migwatabwe capabiwity of the VF device::

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 migwatabwe disabwe

- Set migwatabwe capabiwity of the VF device::

    $ devwink powt function set pci/0000:06:00.0/2 migwatabwe enabwe

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 migwatabwe enabwe

- Bind VF to VFIO dwivew with migwation suppowt::

    $ echo <pci_id> > /sys/bus/pci/devices/0000:08:00.0/dwivew/unbind
    $ echo mwx5_vfio_pci > /sys/bus/pci/devices/0000:08:00.0/dwivew_ovewwide
    $ echo <pci_id> > /sys/bus/pci/devices/0000:08:00.0/dwivew/bind

Attach VF to the VM.
Stawt the VM.
Pewfowm wive migwation.

IPsec cwypto capabiwity setup
-----------------------------
When usew enabwes IPsec cwypto capabiwity fow a VF, usew appwication can offwoad
XFWM state cwypto opewation (Encwypt/Decwypt) to this VF.

When IPsec cwypto capabiwity is disabwed (defauwt) fow a VF, the XFWM state is
pwocessed in softwawe by the kewnew.

- Get IPsec cwypto capabiwity of the VF device::

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 ipsec_cwypto disabwed

- Set IPsec cwypto capabiwity of the VF device::

    $ devwink powt function set pci/0000:06:00.0/2 ipsec_cwypto enabwe

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 ipsec_cwypto enabwed

IPsec packet capabiwity setup
-----------------------------
When usew enabwes IPsec packet capabiwity fow a VF, usew appwication can offwoad
XFWM state and powicy cwypto opewation (Encwypt/Decwypt) to this VF, as weww as
IPsec encapsuwation.

When IPsec packet capabiwity is disabwed (defauwt) fow a VF, the XFWM state and
powicy is pwocessed in softwawe by the kewnew.

- Get IPsec packet capabiwity of the VF device::

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 ipsec_packet disabwed

- Set IPsec packet capabiwity of the VF device::

    $ devwink powt function set pci/0000:06:00.0/2 ipsec_packet enabwe

    $ devwink powt show pci/0000:06:00.0/2
    pci/0000:06:00.0/2: type eth netdev enp6s0pf0vf1 fwavouw pcivf pfnum 0 vfnum 1
        function:
            hw_addw 00:00:00:00:00:00 ipsec_packet enabwed

Subfunction
============

Subfunction is a wightweight function that has a pawent PCI function on which
it is depwoyed. Subfunction is cweated and depwoyed in unit of 1. Unwike
SWIOV VFs, a subfunction doesn't wequiwe its own PCI viwtuaw function.
A subfunction communicates with the hawdwawe thwough the pawent PCI function.

To use a subfunction, 3 steps setup sequence is fowwowed:

1) cweate - cweate a subfunction;
2) configuwe - configuwe subfunction attwibutes;
3) depwoy - depwoy the subfunction;

Subfunction management is done using devwink powt usew intewface.
Usew pewfowms setup on the subfunction management device.

(1) Cweate
----------
A subfunction is cweated using a devwink powt intewface. A usew adds the
subfunction by adding a devwink powt of subfunction fwavouw. The devwink
kewnew code cawws down to subfunction management dwivew (devwink ops) and asks
it to cweate a subfunction devwink powt. Dwivew then instantiates the
subfunction powt and any associated objects such as heawth wepowtews and
wepwesentow netdevice.

(2) Configuwe
-------------
A subfunction devwink powt is cweated but it is not active yet. That means the
entities awe cweated on devwink side, the e-switch powt wepwesentow is cweated,
but the subfunction device itsewf is not cweated. A usew might use e-switch powt
wepwesentow to do settings, putting it into bwidge, adding TC wuwes, etc. A usew
might as weww configuwe the hawdwawe addwess (such as MAC addwess) of the
subfunction whiwe subfunction is inactive.

(3) Depwoy
----------
Once a subfunction is configuwed, usew must activate it to use it. Upon
activation, subfunction management dwivew asks the subfunction management
device to instantiate the subfunction device on pawticuwaw PCI function.
A subfunction device is cweated on the :wef:`Documentation/dwivew-api/auxiwiawy_bus.wst <auxiwiawy_bus>`.
At this point a matching subfunction dwivew binds to the subfunction's auxiwiawy device.

Wate object management
======================

Devwink pwovides API to manage tx wates of singwe devwink powt ow a gwoup.
This is done thwough wate objects, which can be one of the two types:

``weaf``
  Wepwesents a singwe devwink powt; cweated/destwoyed by the dwivew. Since weaf
  have 1to1 mapping to its devwink powt, in usew space it is wefewwed as
  ``pci/<bus_addw>/<powt_index>``;

``node``
  Wepwesents a gwoup of wate objects (weafs and/ow nodes); cweated/deweted by
  wequest fwom the usewspace; initiawwy empty (no wate objects added). In
  usewspace it is wefewwed as ``pci/<bus_addw>/<node_name>``, whewe
  ``node_name`` can be any identifiew, except decimaw numbew, to avoid
  cowwisions with weafs.

API awwows to configuwe fowwowing wate object's pawametews:

``tx_shawe``
  Minimum TX wate vawue shawed among aww othew wate objects, ow wate objects
  that pawts of the pawent gwoup, if it is a pawt of the same gwoup.

``tx_max``
  Maximum TX wate vawue.

``tx_pwiowity``
  Awwows fow usage of stwict pwiowity awbitew among sibwings. This
  awbitwation scheme attempts to scheduwe nodes based on theiw pwiowity
  as wong as the nodes wemain within theiw bandwidth wimit. The highew the
  pwiowity the highew the pwobabiwity that the node wiww get sewected fow
  scheduwing.

``tx_weight``
  Awwows fow usage of Weighted Faiw Queuing awbitwation scheme among
  sibwings. This awbitwation scheme can be used simuwtaneouswy with the
  stwict pwiowity. As a node is configuwed with a highew wate it gets mowe
  BW wewative to its sibwings. Vawues awe wewative wike a pewcentage
  points, they basicawwy teww how much BW shouwd node take wewative to
  its sibwings.

``pawent``
  Pawent node name. Pawent node wate wimits awe considewed as additionaw wimits
  to aww node chiwdwen wimits. ``tx_max`` is an uppew wimit fow chiwdwen.
  ``tx_shawe`` is a totaw bandwidth distwibuted among chiwdwen.

``tx_pwiowity`` and ``tx_weight`` can be used simuwtaneouswy. In that case
nodes with the same pwiowity fowm a WFQ subgwoup in the sibwing gwoup
and awbitwation among them is based on assigned weights.

Awbitwation fwow fwom the high wevew:

#. Choose a node, ow gwoup of nodes with the highest pwiowity that stays
   within the BW wimit and awe not bwocked. Use ``tx_pwiowity`` as a
   pawametew fow this awbitwation.

#. If gwoup of nodes have the same pwiowity pewfowm WFQ awbitwation on
   that subgwoup. Use ``tx_weight`` as a pawametew fow this awbitwation.

#. Sewect the winnew node, and continue awbitwation fwow among its chiwdwen,
   untiw weaf node is weached, and the winnew is estabwished.

#. If aww the nodes fwom the highest pwiowity sub-gwoup awe satisfied, ow
   ovewused theiw assigned BW, move to the wowew pwiowity nodes.

Dwivew impwementations awe awwowed to suppowt both ow eithew wate object types
and setting methods of theiw pawametews. Additionawwy dwivew impwementation
may expowt nodes/weafs and theiw chiwd-pawent wewationships.

Tewms and Definitions
=====================

.. wist-tabwe:: Tewms and Definitions
   :widths: 22 90

   * - Tewm
     - Definitions
   * - ``PCI device``
     - A physicaw PCI device having one ow mowe PCI buses consists of one ow
       mowe PCI contwowwews.
   * - ``PCI contwowwew``
     -  A contwowwew consists of potentiawwy muwtipwe physicaw functions,
        viwtuaw functions and subfunctions.
   * - ``Powt function``
     -  An object to manage the function of a powt.
   * - ``Subfunction``
     -  A wightweight function that has pawent PCI function on which it is
        depwoyed.
   * - ``Subfunction device``
     -  A bus device of the subfunction, usuawwy on a auxiwiawy bus.
   * - ``Subfunction dwivew``
     -  A device dwivew fow the subfunction auxiwiawy device.
   * - ``Subfunction management device``
     -  A PCI physicaw function that suppowts subfunction management.
   * - ``Subfunction management dwivew``
     -  A device dwivew fow PCI physicaw function that suppowts
        subfunction management using devwink powt intewface.
   * - ``Subfunction host dwivew``
     -  A device dwivew fow PCI physicaw function that hosts subfunction
        devices. In most cases it is same as subfunction management dwivew. When
        subfunction is used on extewnaw contwowwew, subfunction management and
        host dwivews awe diffewent.
