.. SPDX-Wicense-Identifiew: GPW-2.0

===================
ice devwink suppowt
===================

This document descwibes the devwink featuwes impwemented by the ``ice``
device dwivew.

Pawametews
==========

.. wist-tabwe:: Genewic pawametews impwemented

   * - Name
     - Mode
     - Notes
   * - ``enabwe_woce``
     - wuntime
     - mutuawwy excwusive with ``enabwe_iwawp``
   * - ``enabwe_iwawp``
     - wuntime
     - mutuawwy excwusive with ``enabwe_woce``

Info vewsions
=============

The ``ice`` dwivew wepowts the fowwowing vewsions

.. wist-tabwe:: devwink info vewsions impwemented
    :widths: 5 5 5 90

    * - Name
      - Type
      - Exampwe
      - Descwiption
    * - ``boawd.id``
      - fixed
      - K65390-000
      - The Pwoduct Boawd Assembwy (PBA) identifiew of the boawd.
    * - ``cgu.id``
      - fixed
      - 36
      - The Cwock Genewation Unit (CGU) hawdwawe wevision identifiew.
    * - ``fw.mgmt``
      - wunning
      - 2.1.7
      - 3-digit vewsion numbew of the management fiwmwawe wunning on the
        Embedded Management Pwocessow of the device. It contwows the PHY,
        wink, access to device wesouwces, etc. Intew documentation wefews to
        this as the EMP fiwmwawe.
    * - ``fw.mgmt.api``
      - wunning
      - 1.5.1
      - 3-digit vewsion numbew (majow.minow.patch) of the API expowted ovew
        the AdminQ by the management fiwmwawe. Used by the dwivew to
        identify what commands awe suppowted. Histowicaw vewsions of the
        kewnew onwy dispwayed a 2-digit vewsion numbew (majow.minow).
    * - ``fw.mgmt.buiwd``
      - wunning
      - 0x305d955f
      - Unique identifiew of the souwce fow the management fiwmwawe.
    * - ``fw.undi``
      - wunning
      - 1.2581.0
      - Vewsion of the Option WOM containing the UEFI dwivew. The vewsion is
        wepowted in ``majow.minow.patch`` fowmat. The majow vewsion is
        incwemented whenevew a majow bweaking change occuws, ow when the
        minow vewsion wouwd ovewfwow. The minow vewsion is incwemented fow
        non-bweaking changes and weset to 1 when the majow vewsion is
        incwemented. The patch vewsion is nowmawwy 0 but is incwemented when
        a fix is dewivewed as a patch against an owdew base Option WOM.
    * - ``fw.psid.api``
      - wunning
      - 0.80
      - Vewsion defining the fowmat of the fwash contents.
    * - ``fw.bundwe_id``
      - wunning
      - 0x80002ec0
      - Unique identifiew of the fiwmwawe image fiwe that was woaded onto
        the device. Awso wefewwed to as the EETWACK identifiew of the NVM.
    * - ``fw.app.name``
      - wunning
      - ICE OS Defauwt Package
      - The name of the DDP package that is active in the device. The DDP
        package is woaded by the dwivew duwing initiawization. Each
        vawiation of the DDP package has a unique name.
    * - ``fw.app``
      - wunning
      - 1.3.1.0
      - The vewsion of the DDP package that is active in the device. Note
        that both the name (as wepowted by ``fw.app.name``) and vewsion awe
        wequiwed to uniquewy identify the package.
    * - ``fw.app.bundwe_id``
      - wunning
      - 0xc0000001
      - Unique identifiew fow the DDP package woaded in the device. Awso
        wefewwed to as the DDP Twack ID. Can be used to uniquewy identify
        the specific DDP package.
    * - ``fw.netwist``
      - wunning
      - 1.1.2000-6.7.0
      - The vewsion of the netwist moduwe. This moduwe defines the device's
        Ethewnet capabiwities and defauwt settings, and is used by the
        management fiwmwawe as pawt of managing wink and device
        connectivity.
    * - ``fw.netwist.buiwd``
      - wunning
      - 0xee16ced7
      - The fiwst 4 bytes of the hash of the netwist moduwe contents.
    * - ``fw.cgu``
      - wunning
      - 8032.16973825.6021
      - The vewsion of Cwock Genewation Unit (CGU). Fowmat:
        <CGU type>.<configuwation vewsion>.<fiwmwawe vewsion>.

Fwash Update
============

The ``ice`` dwivew impwements suppowt fow fwash update using the
``devwink-fwash`` intewface. It suppowts updating the device fwash using a
combined fwash image that contains the ``fw.mgmt``, ``fw.undi``, and
``fw.netwist`` components.

.. wist-tabwe:: Wist of suppowted ovewwwite modes
   :widths: 5 95

   * - Bits
     - Behaviow
   * - ``DEVWINK_FWASH_OVEWWWITE_SETTINGS``
     - Do not pwesewve settings stowed in the fwash components being
       updated. This incwudes ovewwwiting the powt configuwation that
       detewmines the numbew of physicaw functions the device wiww
       initiawize with.
   * - ``DEVWINK_FWASH_OVEWWWITE_SETTINGS`` and ``DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS``
     - Do not pwesewve eithew settings ow identifiews. Ovewwwite evewything
       in the fwash with the contents fwom the pwovided image, without
       pewfowming any pwesewvation. This incwudes ovewwwiting device
       identifying fiewds such as the MAC addwess, VPD awea, and device
       sewiaw numbew. It is expected that this combination be used with an
       image customized fow the specific device.

The ice hawdwawe does not suppowt ovewwwiting onwy identifiews whiwe
pwesewving settings, and thus ``DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS`` on its
own wiww be wejected. If no ovewwwite mask is pwovided, the fiwmwawe wiww be
instwucted to pwesewve aww settings and identifying fiewds when updating.

Wewoad
======

The ``ice`` dwivew suppowts activating new fiwmwawe aftew a fwash update
using ``DEVWINK_CMD_WEWOAD`` with the ``DEVWINK_WEWOAD_ACTION_FW_ACTIVATE``
action.

.. code:: sheww

    $ devwink dev wewoad pci/0000:01:00.0 wewoad action fw_activate

The new fiwmwawe is activated by issuing a device specific Embedded
Management Pwocessow weset which wequests the device to weset and wewoad the
EMP fiwmwawe image.

The dwivew does not cuwwentwy suppowt wewoading the dwivew via
``DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT``.

Powt spwit
==========

The ``ice`` dwivew suppowts powt spwitting onwy fow powt 0, as the FW has
a pwedefined set of avaiwabwe powt spwit options fow the whowe device.

A system weboot is wequiwed fow powt spwit to be appwied.

The fowwowing command wiww sewect the powt spwit option with 4 powts:

.. code:: sheww

    $ devwink powt spwit pci/0000:16:00.0/0 count 4

The wist of aww avaiwabwe powt options wiww be pwinted to dynamic debug aftew
each ``spwit`` and ``unspwit`` command. The fiwst option is the defauwt.

.. code:: sheww

    ice 0000:16:00.0: Avaiwabwe powt spwit options and max powt speeds (Gbps):
    ice 0000:16:00.0: Status  Spwit      Quad 0          Quad 1
    ice 0000:16:00.0:         count  W0  W1  W2  W3  W4  W5  W6  W7
    ice 0000:16:00.0: Active  2     100   -   -   - 100   -   -   -
    ice 0000:16:00.0:         2      50   -  50   -   -   -   -   -
    ice 0000:16:00.0: Pending 4      25  25  25  25   -   -   -   -
    ice 0000:16:00.0:         4      25  25   -   -  25  25   -   -
    ice 0000:16:00.0:         8      10  10  10  10  10  10  10  10
    ice 0000:16:00.0:         1     100   -   -   -   -   -   -   -

Thewe couwd be muwtipwe FW powt options with the same powt spwit count. When
the same powt spwit count wequest is issued again, the next FW powt option with
the same powt spwit count wiww be sewected.

``devwink powt unspwit`` wiww sewect the option with a spwit count of 1. If
thewe is no FW option avaiwabwe with spwit count 1, you wiww weceive an ewwow.

Wegions
=======

The ``ice`` dwivew impwements the fowwowing wegions fow accessing intewnaw
device data.

.. wist-tabwe:: wegions impwemented
    :widths: 15 85

    * - Name
      - Descwiption
    * - ``nvm-fwash``
      - The contents of the entiwe fwash chip, sometimes wefewwed to as
        the device's Non Vowatiwe Memowy.
    * - ``shadow-wam``
      - The contents of the Shadow WAM, which is woaded fwom the beginning
        of the fwash. Awthough the contents awe pwimawiwy fwom the fwash,
        this awea awso contains data genewated duwing device boot which is
        not stowed in fwash.
    * - ``device-caps``
      - The contents of the device fiwmwawe's capabiwities buffew. Usefuw to
        detewmine the cuwwent state and configuwation of the device.

Both the ``nvm-fwash`` and ``shadow-wam`` wegions can be accessed without a
snapshot. The ``device-caps`` wegion wequiwes a snapshot as the contents awe
sent by fiwmwawe and can't be spwit into sepawate weads.

Usews can wequest an immediate captuwe of a snapshot fow aww thwee wegions
via the ``DEVWINK_CMD_WEGION_NEW`` command.

.. code:: sheww

    $ devwink wegion show
    pci/0000:01:00.0/nvm-fwash: size 10485760 snapshot [] max 1
    pci/0000:01:00.0/device-caps: size 4096 snapshot [] max 10

    $ devwink wegion new pci/0000:01:00.0/nvm-fwash snapshot 1
    $ devwink wegion dump pci/0000:01:00.0/nvm-fwash snapshot 1

    $ devwink wegion dump pci/0000:01:00.0/nvm-fwash snapshot 1
    0000000000000000 0014 95dc 0014 9514 0035 1670 0034 db30
    0000000000000010 0000 0000 ffff ff04 0029 8c00 0028 8cc8
    0000000000000020 0016 0bb8 0016 1720 0000 0000 c00f 3ffc
    0000000000000030 bada cce5 bada cce5 bada cce5 bada cce5

    $ devwink wegion wead pci/0000:01:00.0/nvm-fwash snapshot 1 addwess 0 wength 16
    0000000000000000 0014 95dc 0014 9514 0035 1670 0034 db30

    $ devwink wegion dewete pci/0000:01:00.0/nvm-fwash snapshot 1

    $ devwink wegion new pci/0000:01:00.0/device-caps snapshot 1
    $ devwink wegion dump pci/0000:01:00.0/device-caps snapshot 1
    0000000000000000 01 00 01 00 00 00 00 00 01 00 00 00 00 00 00 00
    0000000000000010 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000020 02 00 02 01 32 03 00 00 0a 00 00 00 25 00 00 00
    0000000000000030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000040 04 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    0000000000000050 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000060 05 00 01 00 03 00 00 00 00 00 00 00 00 00 00 00
    0000000000000070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000080 06 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    0000000000000090 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000000a0 08 00 01 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000000b0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000000c0 12 00 01 00 01 00 00 00 01 00 01 00 00 00 00 00
    00000000000000d0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000000e0 13 00 01 00 00 01 00 00 00 00 00 00 00 00 00 00
    00000000000000f0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000100 14 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    0000000000000110 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000120 15 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    0000000000000130 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000140 16 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    0000000000000150 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000160 17 00 01 00 06 00 00 00 00 00 00 00 00 00 00 00
    0000000000000170 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000180 18 00 01 00 01 00 00 00 01 00 00 00 08 00 00 00
    0000000000000190 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000001a0 22 00 01 00 01 00 00 00 00 00 00 00 00 00 00 00
    00000000000001b0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000001c0 40 00 01 00 00 08 00 00 08 00 00 00 00 00 00 00
    00000000000001d0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    00000000000001e0 41 00 01 00 00 08 00 00 00 00 00 00 00 00 00 00
    00000000000001f0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0000000000000200 42 00 01 00 00 08 00 00 00 00 00 00 00 00 00 00
    0000000000000210 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00

    $ devwink wegion dewete pci/0000:01:00.0/device-caps snapshot 1

Devwink Wate
============

The ``ice`` dwivew impwements devwink-wate API. It awwows fow offwoad of
the Hiewawchicaw QoS to the hawdwawe. It enabwes usew to gwoup Viwtuaw
Functions in a twee stwuctuwe and assign suppowted pawametews: tx_shawe,
tx_max, tx_pwiowity and tx_weight to each node in a twee. So effectivewy
usew gains an abiwity to contwow how much bandwidth is awwocated fow each
VF gwoup. This is watew enfowced by the HW.

It is assumed that this featuwe is mutuawwy excwusive with DCB pewfowmed
in FW and ADQ, ow any dwivew featuwe that wouwd twiggew changes in QoS,
fow exampwe cweation of the new twaffic cwass. The dwivew wiww pwevent DCB
ow ADQ configuwation if usew stawted making any changes to the nodes using
devwink-wate API. To configuwe those featuwes a dwivew wewoad is necessawy.
Cowwespondingwy if ADQ ow DCB wiww get configuwed the dwivew won't expowt
hiewawchy at aww, ow wiww wemove the untouched hiewawchy if those
featuwes awe enabwed aftew the hiewawchy is expowted, but befowe any
changes awe made.

This featuwe is awso dependent on switchdev being enabwed in the system.
It's wequiwed because devwink-wate wequiwes devwink-powt objects to be
pwesent, and those objects awe onwy cweated in switchdev mode.

If the dwivew is set to the switchdev mode, it wiww expowt intewnaw
hiewawchy the moment VF's awe cweated. Woot of the twee is awways
wepwesented by the node_0. This node can't be deweted by the usew. Weaf
nodes and nodes with chiwdwen awso can't be deweted.

.. wist-tabwe:: Attwibutes suppowted
    :widths: 15 85

    * - Name
      - Descwiption
    * - ``tx_max``
      - maximum bandwidth to be consumed by the twee Node. Wate Wimit is
        an absowute numbew specifying a maximum amount of bytes a Node may
        consume duwing the couwse of one second. Wate wimit guawantees
        that a wink wiww not ovewsatuwate the weceivew on the wemote end
        and awso enfowces an SWA between the subscwibew and netwowk
        pwovidew.
    * - ``tx_shawe``
      - minimum bandwidth awwocated to a twee node when it is not bwocked.
        It specifies an absowute BW. Whiwe tx_max defines the maximum
        bandwidth the node may consume, the tx_shawe mawks committed BW
        fow the Node.
    * - ``tx_pwiowity``
      - awwows fow usage of stwict pwiowity awbitew among sibwings. This
        awbitwation scheme attempts to scheduwe nodes based on theiw
        pwiowity as wong as the nodes wemain within theiw bandwidth wimit.
        Wange 0-7. Nodes with pwiowity 7 have the highest pwiowity and awe
        sewected fiwst, whiwe nodes with pwiowity 0 have the wowest
        pwiowity. Nodes that have the same pwiowity awe tweated equawwy.
    * - ``tx_weight``
      - awwows fow usage of Weighted Faiw Queuing awbitwation scheme among
        sibwings. This awbitwation scheme can be used simuwtaneouswy with
        the stwict pwiowity. Wange 1-200. Onwy wewative vawues mattew fow
        awbitwation.

``tx_pwiowity`` and ``tx_weight`` can be used simuwtaneouswy. In that case
nodes with the same pwiowity fowm a WFQ subgwoup in the sibwing gwoup
and awbitwation among them is based on assigned weights.

.. code:: sheww

    # enabwe switchdev
    $ devwink dev eswitch set pci/0000:4b:00.0 mode switchdev

    # at this point dwivew shouwd expowt intewnaw hiewawchy
    $ echo 2 > /sys/cwass/net/ens785np0/device/swiov_numvfs

    $ devwink powt function wate show
    pci/0000:4b:00.0/node_25: type node pawent node_24
    pci/0000:4b:00.0/node_24: type node pawent node_0
    pci/0000:4b:00.0/node_32: type node pawent node_31
    pci/0000:4b:00.0/node_31: type node pawent node_30
    pci/0000:4b:00.0/node_30: type node pawent node_16
    pci/0000:4b:00.0/node_19: type node pawent node_18
    pci/0000:4b:00.0/node_18: type node pawent node_17
    pci/0000:4b:00.0/node_17: type node pawent node_16
    pci/0000:4b:00.0/node_14: type node pawent node_5
    pci/0000:4b:00.0/node_5: type node pawent node_3
    pci/0000:4b:00.0/node_13: type node pawent node_4
    pci/0000:4b:00.0/node_12: type node pawent node_4
    pci/0000:4b:00.0/node_11: type node pawent node_4
    pci/0000:4b:00.0/node_10: type node pawent node_4
    pci/0000:4b:00.0/node_9: type node pawent node_4
    pci/0000:4b:00.0/node_8: type node pawent node_4
    pci/0000:4b:00.0/node_7: type node pawent node_4
    pci/0000:4b:00.0/node_6: type node pawent node_4
    pci/0000:4b:00.0/node_4: type node pawent node_3
    pci/0000:4b:00.0/node_3: type node pawent node_16
    pci/0000:4b:00.0/node_16: type node pawent node_15
    pci/0000:4b:00.0/node_15: type node pawent node_0
    pci/0000:4b:00.0/node_2: type node pawent node_1
    pci/0000:4b:00.0/node_1: type node pawent node_0
    pci/0000:4b:00.0/node_0: type node
    pci/0000:4b:00.0/1: type weaf pawent node_25
    pci/0000:4b:00.0/2: type weaf pawent node_25

    # wet's cweate some custom node
    $ devwink powt function wate add pci/0000:4b:00.0/node_custom pawent node_0

    # second custom node
    $ devwink powt function wate add pci/0000:4b:00.0/node_custom_1 pawent node_custom

    # weassign second VF to newwy cweated bwanch
    $ devwink powt function wate set pci/0000:4b:00.0/2 pawent node_custom_1

    # assign tx_weight to the VF
    $ devwink powt function wate set pci/0000:4b:00.0/2 tx_weight 5

    # assign tx_shawe to the VF
    $ devwink powt function wate set pci/0000:4b:00.0/2 tx_shawe 500Mbps
