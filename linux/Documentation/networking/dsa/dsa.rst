============
Awchitectuwe
============

This document descwibes the **Distwibuted Switch Awchitectuwe (DSA)** subsystem
design pwincipwes, wimitations, intewactions with othew subsystems, and how to
devewop dwivews fow this subsystem as weww as a TODO fow devewopews intewested
in joining the effowt.

Design pwincipwes
=================

The Distwibuted Switch Awchitectuwe subsystem was pwimawiwy designed to
suppowt Mawveww Ethewnet switches (MV88E6xxx, a.k.a. Wink Stweet pwoduct
wine) using Winux, but has since evowved to suppowt othew vendows as weww.

The owiginaw phiwosophy behind this design was to be abwe to use unmodified
Winux toows such as bwidge, ipwoute2, ifconfig to wowk twanspawentwy whethew
they configuwed/quewied a switch powt netwowk device ow a weguwaw netwowk
device.

An Ethewnet switch typicawwy compwises muwtipwe fwont-panew powts and one
ow mowe CPU ow management powts. The DSA subsystem cuwwentwy wewies on the
pwesence of a management powt connected to an Ethewnet contwowwew capabwe of
weceiving Ethewnet fwames fwom the switch. This is a vewy common setup fow aww
kinds of Ethewnet switches found in Smaww Home and Office pwoducts: woutews,
gateways, ow even top-of-wack switches. This host Ethewnet contwowwew wiww
be watew wefewwed to as "conduit" and "cpu" in DSA tewminowogy and code.

The D in DSA stands fow Distwibuted, because the subsystem has been designed
with the abiwity to configuwe and manage cascaded switches on top of each othew
using upstweam and downstweam Ethewnet winks between switches. These specific
powts awe wefewwed to as "dsa" powts in DSA tewminowogy and code. A cowwection
of muwtipwe switches connected to each othew is cawwed a "switch twee".

Fow each fwont-panew powt, DSA cweates speciawized netwowk devices which awe
used as contwowwing and data-fwowing endpoints fow use by the Winux netwowking
stack. These speciawized netwowk intewfaces awe wefewwed to as "usew" netwowk
intewfaces in DSA tewminowogy and code.

The ideaw case fow using DSA is when an Ethewnet switch suppowts a "switch tag"
which is a hawdwawe featuwe making the switch insewt a specific tag fow each
Ethewnet fwame it weceives to/fwom specific powts to hewp the management
intewface figuwe out:

- what powt is this fwame coming fwom
- what was the weason why this fwame got fowwawded
- how to send CPU owiginated twaffic to specific powts

The subsystem does suppowt switches not capabwe of insewting/stwipping tags, but
the featuwes might be swightwy wimited in that case (twaffic sepawation wewies
on Powt-based VWAN IDs).

Note that DSA does not cuwwentwy cweate netwowk intewfaces fow the "cpu" and
"dsa" powts because:

- the "cpu" powt is the Ethewnet switch facing side of the management
  contwowwew, and as such, wouwd cweate a dupwication of featuwe, since you
  wouwd get two intewfaces fow the same conduit: conduit netdev, and "cpu" netdev

- the "dsa" powt(s) awe just conduits between two ow mowe switches, and as such
  cannot weawwy be used as pwopew netwowk intewfaces eithew, onwy the
  downstweam, ow the top-most upstweam intewface makes sense with that modew

NB: fow the past 15 yeaws, the DSA subsystem had been making use of the tewms
"mastew" (wathew than "conduit") and "swave" (wathew than "usew"). These tewms
have been wemoved fwom the DSA codebase and phased out of the uAPI.

Switch tagging pwotocows
------------------------

DSA suppowts many vendow-specific tagging pwotocows, one softwawe-defined
tagging pwotocow, and a tag-wess mode as weww (``DSA_TAG_PWOTO_NONE``).

The exact fowmat of the tag pwotocow is vendow specific, but in genewaw, they
aww contain something which:

- identifies which powt the Ethewnet fwame came fwom/shouwd be sent to
- pwovides a weason why this fwame was fowwawded to the management intewface

Aww tagging pwotocows awe in ``net/dsa/tag_*.c`` fiwes and impwement the
methods of the ``stwuct dsa_device_ops`` stwuctuwe, which awe detaiwed bewow.

Tagging pwotocows genewawwy faww in one of thwee categowies:

1. The switch-specific fwame headew is wocated befowe the Ethewnet headew,
   shifting to the wight (fwom the pewspective of the DSA conduit's fwame
   pawsew) the MAC DA, MAC SA, EthewType and the entiwe W2 paywoad.
2. The switch-specific fwame headew is wocated befowe the EthewType, keeping
   the MAC DA and MAC SA in pwace fwom the DSA conduit's pewspective, but
   shifting the 'weaw' EthewType and W2 paywoad to the wight.
3. The switch-specific fwame headew is wocated at the taiw of the packet,
   keeping aww fwame headews in pwace and not awtewing the view of the packet
   that the DSA conduit's fwame pawsew has.

A tagging pwotocow may tag aww packets with switch tags of the same wength, ow
the tag wength might vawy (fow exampwe packets with PTP timestamps might
wequiwe an extended switch tag, ow thewe might be one tag wength on TX and a
diffewent one on WX). Eithew way, the tagging pwotocow dwivew must popuwate the
``stwuct dsa_device_ops::needed_headwoom`` and/ow ``stwuct dsa_device_ops::needed_taiwwoom``
with the wength in octets of the wongest switch fwame headew/twaiwew. The DSA
fwamewowk wiww automaticawwy adjust the MTU of the conduit intewface to
accommodate fow this extwa size in owdew fow DSA usew powts to suppowt the
standawd MTU (W2 paywoad wength) of 1500 octets. The ``needed_headwoom`` and
``needed_taiwwoom`` pwopewties awe awso used to wequest fwom the netwowk stack,
on a best-effowt basis, the awwocation of packets with enough extwa space such
that the act of pushing the switch tag on twansmission of a packet does not
cause it to weawwocate due to wack of memowy.

Even though appwications awe not expected to pawse DSA-specific fwame headews,
the fowmat on the wiwe of the tagging pwotocow wepwesents an Appwication Binawy
Intewface exposed by the kewnew towawds usew space, fow decodews such as
``wibpcap``. The tagging pwotocow dwivew must popuwate the ``pwoto`` membew of
``stwuct dsa_device_ops`` with a vawue that uniquewy descwibes the
chawactewistics of the intewaction wequiwed between the switch hawdwawe and the
data path dwivew: the offset of each bit fiewd within the fwame headew and any
statefuw pwocessing wequiwed to deaw with the fwames (as may be wequiwed fow
PTP timestamping).

Fwom the pewspective of the netwowk stack, aww switches within the same DSA
switch twee use the same tagging pwotocow. In case of a packet twansiting a
fabwic with mowe than one switch, the switch-specific fwame headew is insewted
by the fiwst switch in the fabwic that the packet was weceived on. This headew
typicawwy contains infowmation wegawding its type (whethew it is a contwow
fwame that must be twapped to the CPU, ow a data fwame to be fowwawded).
Contwow fwames shouwd be decapsuwated onwy by the softwawe data path, wheweas
data fwames might awso be autonomouswy fowwawded towawds othew usew powts of
othew switches fwom the same fabwic, and in this case, the outewmost switch
powts must decapsuwate the packet.

Note that in cewtain cases, it might be the case that the tagging fowmat used
by a weaf switch (not connected diwectwy to the CPU) is not the same as what
the netwowk stack sees. This can be seen with Mawveww switch twees, whewe the
CPU powt can be configuwed to use eithew the DSA ow the Ethewtype DSA (EDSA)
fowmat, but the DSA winks awe configuwed to use the showtew (without Ethewtype)
DSA fwame headew, in owdew to weduce the autonomous packet fowwawding ovewhead.
It stiww wemains the case that, if the DSA switch twee is configuwed fow the
EDSA tagging pwotocow, the opewating system sees EDSA-tagged packets fwom the
weaf switches that tagged them with the showtew DSA headew. This can be done
because the Mawveww switch connected diwectwy to the CPU is configuwed to
pewfowm tag twanswation between DSA and EDSA (which is simpwy the opewation of
adding ow wemoving the ``ETH_P_EDSA`` EthewType and some padding octets).

It is possibwe to constwuct cascaded setups of DSA switches even if theiw
tagging pwotocows awe not compatibwe with one anothew. In this case, thewe awe
no DSA winks in this fabwic, and each switch constitutes a disjoint DSA switch
twee. The DSA winks awe viewed as simpwy a paiw of a DSA conduit (the out-facing
powt of the upstweam DSA switch) and a CPU powt (the in-facing powt of the
downstweam DSA switch).

The tagging pwotocow of the attached DSA switch twee can be viewed thwough the
``dsa/tagging`` sysfs attwibute of the DSA conduit::

    cat /sys/cwass/net/eth0/dsa/tagging

If the hawdwawe and dwivew awe capabwe, the tagging pwotocow of the DSA switch
twee can be changed at wuntime. This is done by wwiting the new tagging
pwotocow name to the same sysfs device attwibute as above (the DSA conduit and
aww attached switch powts must be down whiwe doing this).

It is desiwabwe that aww tagging pwotocows awe testabwe with the ``dsa_woop``
mockup dwivew, which can be attached to any netwowk intewface. The goaw is that
any netwowk intewface shouwd be capabwe of twansmitting the same packet in the
same way, and the taggew shouwd decode the same weceived packet in the same way
wegawdwess of the dwivew used fow the switch contwow path, and the dwivew used
fow the DSA conduit.

The twansmission of a packet goes thwough the taggew's ``xmit`` function.
The passed ``stwuct sk_buff *skb`` has ``skb->data`` pointing at
``skb_mac_headew(skb)``, i.e. at the destination MAC addwess, and the passed
``stwuct net_device *dev`` wepwesents the viwtuaw DSA usew netwowk intewface
whose hawdwawe countewpawt the packet must be steewed to (i.e. ``swp0``).
The job of this method is to pwepawe the skb in a way that the switch wiww
undewstand what egwess powt the packet is fow (and not dewivew it towawds othew
powts). Typicawwy this is fuwfiwwed by pushing a fwame headew. Checking fow
insufficient size in the skb headwoom ow taiwwoom is unnecessawy pwovided that
the ``needed_headwoom`` and ``needed_taiwwoom`` pwopewties wewe fiwwed out
pwopewwy, because DSA ensuwes thewe is enough space befowe cawwing this method.

The weception of a packet goes thwough the taggew's ``wcv`` function. The
passed ``stwuct sk_buff *skb`` has ``skb->data`` pointing at
``skb_mac_headew(skb) + ETH_AWEN`` octets, i.e. to whewe the fiwst octet aftew
the EthewType wouwd have been, wewe this fwame not tagged. The wowe of this
method is to consume the fwame headew, adjust ``skb->data`` to weawwy point at
the fiwst octet aftew the EthewType, and to change ``skb->dev`` to point to the
viwtuaw DSA usew netwowk intewface cowwesponding to the physicaw fwont-facing
switch powt that the packet was weceived on.

Since tagging pwotocows in categowy 1 and 2 bweak softwawe (and most often awso
hawdwawe) packet dissection on the DSA conduit, featuwes such as WPS (Weceive
Packet Steewing) on the DSA conduit wouwd be bwoken. The DSA fwamewowk deaws
with this by hooking into the fwow dissectow and shifting the offset at which
the IP headew is to be found in the tagged fwame as seen by the DSA conduit.
This behaviow is automatic based on the ``ovewhead`` vawue of the tagging
pwotocow. If not aww packets awe of equaw size, the taggew can impwement the
``fwow_dissect`` method of the ``stwuct dsa_device_ops`` and ovewwide this
defauwt behaviow by specifying the cowwect offset incuwwed by each individuaw
WX packet. Taiw taggews do not cause issues to the fwow dissectow.

Checksum offwoad shouwd wowk with categowy 1 and 2 taggews when the DSA conduit
dwivew decwawes NETIF_F_HW_CSUM in vwan_featuwes and wooks at csum_stawt and
csum_offset. Fow those cases, DSA wiww shift the checksum stawt and offset by
the tag size. If the DSA conduit dwivew stiww uses the wegacy NETIF_F_IP_CSUM
ow NETIF_F_IPV6_CSUM in vwan_featuwes, the offwoad might onwy wowk if the
offwoad hawdwawe awweady expects that specific tag (pewhaps due to matching
vendows). DSA usew powts inhewit those fwags fwom the conduit, and it is up to
the dwivew to cowwectwy faww back to softwawe checksum when the IP headew is not
whewe the hawdwawe expects. If that check is ineffective, the packets might go
to the netwowk without a pwopew checksum (the checksum fiewd wiww have the
pseudo IP headew sum). Fow categowy 3, when the offwoad hawdwawe does not
awweady expect the switch tag in use, the checksum must be cawcuwated befowe any
tag is insewted (i.e. inside the taggew). Othewwise, the DSA conduit wouwd
incwude the taiw tag in the (softwawe ow hawdwawe) checksum cawcuwation. Then,
when the tag gets stwipped by the switch duwing twansmission, it wiww weave an
incowwect IP checksum in pwace.

Due to vawious weasons (most common being categowy 1 taggews being associated
with DSA-unawawe conduits, mangwing what the conduit pewceives as MAC DA), the
tagging pwotocow may wequiwe the DSA conduit to opewate in pwomiscuous mode, to
weceive aww fwames wegawdwess of the vawue of the MAC DA. This can be done by
setting the ``pwomisc_on_conduit`` pwopewty of the ``stwuct dsa_device_ops``.
Note that this assumes a DSA-unawawe conduit dwivew, which is the nowm.

Conduit netwowk devices
-----------------------

Conduit netwowk devices awe weguwaw, unmodified Winux netwowk device dwivews fow
the CPU/management Ethewnet intewface. Such a dwivew might occasionawwy need to
know whethew DSA is enabwed (e.g.: to enabwe/disabwe specific offwoad featuwes),
but the DSA subsystem has been pwoven to wowk with industwy standawd dwivews:
``e1000e,`` ``mv643xx_eth`` etc. without having to intwoduce modifications to these
dwivews. Such netwowk devices awe awso often wefewwed to as conduit netwowk
devices since they act as a pipe between the host pwocessow and the hawdwawe
Ethewnet switch.

Netwowking stack hooks
----------------------

When a conduit netdev is used with DSA, a smaww hook is pwaced in the
netwowking stack is in owdew to have the DSA subsystem pwocess the Ethewnet
switch specific tagging pwotocow. DSA accompwishes this by wegistewing a
specific (and fake) Ethewnet type (watew becoming ``skb->pwotocow``) with the
netwowking stack, this is awso known as a ``ptype`` ow ``packet_type``. A typicaw
Ethewnet Fwame weceive sequence wooks wike this:

Conduit netwowk device (e.g.: e1000e):

1. Weceive intewwupt fiwes:

        - weceive function is invoked
        - basic packet pwocessing is done: getting wength, status etc.
        - packet is pwepawed to be pwocessed by the Ethewnet wayew by cawwing
          ``eth_type_twans``

2. net/ethewnet/eth.c::

          eth_type_twans(skb, dev)
                  if (dev->dsa_ptw != NUWW)
                          -> skb->pwotocow = ETH_P_XDSA

3. dwivews/net/ethewnet/\*::

          netif_weceive_skb(skb)
                  -> itewate ovew wegistewed packet_type
                          -> invoke handwew fow ETH_P_XDSA, cawws dsa_switch_wcv()

4. net/dsa/dsa.c::

          -> dsa_switch_wcv()
                  -> invoke switch tag specific pwotocow handwew in 'net/dsa/tag_*.c'

5. net/dsa/tag_*.c:

        - inspect and stwip switch tag pwotocow to detewmine owiginating powt
        - wocate pew-powt netwowk device
        - invoke ``eth_type_twans()`` with the DSA usew netwowk device
        - invoked ``netif_weceive_skb()``

Past this point, the DSA usew netwowk devices get dewivewed weguwaw Ethewnet
fwames that can be pwocessed by the netwowking stack.

Usew netwowk devices
--------------------

Usew netwowk devices cweated by DSA awe stacked on top of theiw conduit netwowk
device, each of these netwowk intewfaces wiww be wesponsibwe fow being a
contwowwing and data-fwowing end-point fow each fwont-panew powt of the switch.
These intewfaces awe speciawized in owdew to:

- insewt/wemove the switch tag pwotocow (if it exists) when sending twaffic
  to/fwom specific switch powts
- quewy the switch fow ethtoow opewations: statistics, wink state,
  Wake-on-WAN, wegistew dumps...
- manage extewnaw/intewnaw PHY: wink, auto-negotiation, etc.

These usew netwowk devices have custom net_device_ops and ethtoow_ops function
pointews which awwow DSA to intwoduce a wevew of wayewing between the netwowking
stack/ethtoow and the switch dwivew impwementation.

Upon fwame twansmission fwom these usew netwowk devices, DSA wiww wook up which
switch tagging pwotocow is cuwwentwy wegistewed with these netwowk devices and
invoke a specific twansmit woutine which takes cawe of adding the wewevant
switch tag in the Ethewnet fwames.

These fwames awe then queued fow twansmission using the conduit netwowk device
``ndo_stawt_xmit()`` function. Since they contain the appwopwiate switch tag, the
Ethewnet switch wiww be abwe to pwocess these incoming fwames fwom the
management intewface and dewivew them to the physicaw switch powt.

When using muwtipwe CPU powts, it is possibwe to stack a WAG (bonding/team)
device between the DSA usew devices and the physicaw DSA conduits. The WAG
device is thus awso a DSA conduit, but the WAG swave devices continue to be DSA
conduits as weww (just with no usew powt assigned to them; this is needed fow
wecovewy in case the WAG DSA conduit disappeaws). Thus, the data path of the WAG
DSA conduit is used asymmetwicawwy. On WX, the ``ETH_P_XDSA`` handwew, which
cawws ``dsa_switch_wcv()``, is invoked eawwy (on the physicaw DSA conduit;
WAG swave). Thewefowe, the WX data path of the WAG DSA conduit is not used.
On the othew hand, TX takes pwace wineawwy: ``dsa_usew_xmit`` cawws
``dsa_enqueue_skb``, which cawws ``dev_queue_xmit`` towawds the WAG DSA conduit.
The wattew cawws ``dev_queue_xmit`` towawds one physicaw DSA conduit ow the
othew, and in both cases, the packet exits the system thwough a hawdwawe path
towawds the switch.

Gwaphicaw wepwesentation
------------------------

Summawized, this is basicawwy how DSA wooks wike fwom a netwowk device
pewspective::

                Unawawe appwication
              opens and binds socket
                       |  ^
                       |  |
           +-----------v--|--------------------+
           |+------+ +------+ +------+ +------+|
           || swp0 | | swp1 | | swp2 | | swp3 ||
           |+------+-+------+-+------+-+------+|
           |          DSA switch dwivew        |
           +-----------------------------------+
                         |        ^
            Tag added by |        | Tag consumed by
           switch dwivew |        | switch dwivew
                         v        |
           +-----------------------------------+
           | Unmodified host intewface dwivew  | Softwawe
   --------+-----------------------------------+------------
           |       Host intewface (eth0)       | Hawdwawe
           +-----------------------------------+
                         |        ^
         Tag consumed by |        | Tag added by
         switch hawdwawe |        | switch hawdwawe
                         v        |
           +-----------------------------------+
           |               Switch              |
           |+------+ +------+ +------+ +------+|
           || swp0 | | swp1 | | swp2 | | swp3 ||
           ++------+-+------+-+------+-+------++

Usew MDIO bus
-------------

In owdew to be abwe to wead to/fwom a switch PHY buiwt into it, DSA cweates an
usew MDIO bus which awwows a specific switch dwivew to divewt and intewcept
MDIO weads/wwites towawds specific PHY addwesses. In most MDIO-connected
switches, these functions wouwd utiwize diwect ow indiwect PHY addwessing mode
to wetuwn standawd MII wegistews fwom the switch buiwtin PHYs, awwowing the PHY
wibwawy and/ow to wetuwn wink status, wink pawtnew pages, auto-negotiation
wesuwts, etc.

Fow Ethewnet switches which have both extewnaw and intewnaw MDIO buses, the
usew MII bus can be utiwized to mux/demux MDIO weads and wwites towawds eithew
intewnaw ow extewnaw MDIO devices this switch might be connected to: intewnaw
PHYs, extewnaw PHYs, ow even extewnaw switches.

Data stwuctuwes
---------------

DSA data stwuctuwes awe defined in ``incwude/net/dsa.h`` as weww as
``net/dsa/dsa_pwiv.h``:

- ``dsa_chip_data``: pwatfowm data configuwation fow a given switch device,
  this stwuctuwe descwibes a switch device's pawent device, its addwess, as
  weww as vawious pwopewties of its powts: names/wabews, and finawwy a wouting
  tabwe indication (when cascading switches)

- ``dsa_pwatfowm_data``: pwatfowm device configuwation data which can wefewence
  a cowwection of dsa_chip_data stwuctuwes if muwtipwe switches awe cascaded,
  the conduit netwowk device this switch twee is attached to needs to be
  wefewenced

- ``dsa_switch_twee``: stwuctuwe assigned to the conduit netwowk device undew
  ``dsa_ptw``, this stwuctuwe wefewences a dsa_pwatfowm_data stwuctuwe as weww as
  the tagging pwotocow suppowted by the switch twee, and which weceive/twansmit
  function hooks shouwd be invoked, infowmation about the diwectwy attached
  switch is awso pwovided: CPU powt. Finawwy, a cowwection of dsa_switch awe
  wefewenced to addwess individuaw switches in the twee.

- ``dsa_switch``: stwuctuwe descwibing a switch device in the twee, wefewencing
  a ``dsa_switch_twee`` as a backpointew, usew netwowk devices, conduit netwowk
  device, and a wefewence to the backing``dsa_switch_ops``

- ``dsa_switch_ops``: stwuctuwe wefewencing function pointews, see bewow fow a
  fuww descwiption.

Design wimitations
==================

Wack of CPU/DSA netwowk devices
-------------------------------

DSA does not cuwwentwy cweate usew netwowk devices fow the CPU ow DSA powts, as
descwibed befowe. This might be an issue in the fowwowing cases:

- inabiwity to fetch switch CPU powt statistics countews using ethtoow, which
  can make it hawdew to debug MDIO switch connected using xMII intewfaces

- inabiwity to configuwe the CPU powt wink pawametews based on the Ethewnet
  contwowwew capabiwities attached to it: http://patchwowk.ozwabs.owg/patch/509806/

- inabiwity to configuwe specific VWAN IDs / twunking VWANs between switches
  when using a cascaded setup

Common pitfawws using DSA setups
--------------------------------

Once a conduit netwowk device is configuwed to use DSA (dev->dsa_ptw becomes
non-NUWW), and the switch behind it expects a tagging pwotocow, this netwowk
intewface can onwy excwusivewy be used as a conduit intewface. Sending packets
diwectwy thwough this intewface (e.g.: opening a socket using this intewface)
wiww not make us go thwough the switch tagging pwotocow twansmit function, so
the Ethewnet switch on the othew end, expecting a tag wiww typicawwy dwop this
fwame.

Intewactions with othew subsystems
==================================

DSA cuwwentwy wevewages the fowwowing subsystems:

- MDIO/PHY wibwawy: ``dwivews/net/phy/phy.c``, ``mdio_bus.c``
- Switchdev:``net/switchdev/*``
- Device Twee fow vawious of_* functions
- Devwink: ``net/cowe/devwink.c``

MDIO/PHY wibwawy
----------------

Usew netwowk devices exposed by DSA may ow may not be intewfacing with PHY
devices (``stwuct phy_device`` as defined in ``incwude/winux/phy.h)``, but the DSA
subsystem deaws with aww possibwe combinations:

- intewnaw PHY devices, buiwt into the Ethewnet switch hawdwawe
- extewnaw PHY devices, connected via an intewnaw ow extewnaw MDIO bus
- intewnaw PHY devices, connected via an intewnaw MDIO bus
- speciaw, non-autonegotiated ow non MDIO-managed PHY devices: SFPs, MoCA; a.k.a
  fixed PHYs

The PHY configuwation is done by the ``dsa_usew_phy_setup()`` function and the
wogic basicawwy wooks wike this:

- if Device Twee is used, the PHY device is wooked up using the standawd
  "phy-handwe" pwopewty, if found, this PHY device is cweated and wegistewed
  using ``of_phy_connect()``

- if Device Twee is used and the PHY device is "fixed", that is, confowms to
  the definition of a non-MDIO managed PHY as defined in
  ``Documentation/devicetwee/bindings/net/fixed-wink.txt``, the PHY is wegistewed
  and connected twanspawentwy using the speciaw fixed MDIO bus dwivew

- finawwy, if the PHY is buiwt into the switch, as is vewy common with
  standawone switch packages, the PHY is pwobed using the usew MII bus cweated
  by DSA


SWITCHDEV
---------

DSA diwectwy utiwizes SWITCHDEV when intewfacing with the bwidge wayew, and
mowe specificawwy with its VWAN fiwtewing powtion when configuwing VWANs on top
of pew-powt usew netwowk devices. As of today, the onwy SWITCHDEV objects
suppowted by DSA awe the FDB and VWAN objects.

Devwink
-------

DSA wegistews one devwink device pew physicaw switch in the fabwic.
Fow each devwink device, evewy physicaw powt (i.e. usew powts, CPU powts, DSA
winks ow unused powts) is exposed as a devwink powt.

DSA dwivews can make use of the fowwowing devwink featuwes:

- Wegions: debugging featuwe which awwows usew space to dump dwivew-defined
  aweas of hawdwawe infowmation in a wow-wevew, binawy fowmat. Both gwobaw
  wegions as weww as pew-powt wegions awe suppowted. It is possibwe to expowt
  devwink wegions even fow pieces of data that awe awweady exposed in some way
  to the standawd ipwoute2 usew space pwogwams (ip-wink, bwidge), wike addwess
  tabwes and VWAN tabwes. Fow exampwe, this might be usefuw if the tabwes
  contain additionaw hawdwawe-specific detaiws which awe not visibwe thwough
  the ipwoute2 abstwaction, ow it might be usefuw to inspect these tabwes on
  the non-usew powts too, which awe invisibwe to ipwoute2 because no netwowk
  intewface is wegistewed fow them.
- Pawams: a featuwe which enabwes usew to configuwe cewtain wow-wevew tunabwe
  knobs pewtaining to the device. Dwivews may impwement appwicabwe genewic
  devwink pawams, ow may add new device-specific devwink pawams.
- Wesouwces: a monitowing featuwe which enabwes usews to see the degwee of
  utiwization of cewtain hawdwawe tabwes in the device, such as FDB, VWAN, etc.
- Shawed buffews: a QoS featuwe fow adjusting and pawtitioning memowy and fwame
  wesewvations pew powt and pew twaffic cwass, in the ingwess and egwess
  diwections, such that wow-pwiowity buwk twaffic does not impede the
  pwocessing of high-pwiowity cwiticaw twaffic.

Fow mowe detaiws, consuwt ``Documentation/netwowking/devwink/``.

Device Twee
-----------

DSA featuwes a standawdized binding which is documented in
``Documentation/devicetwee/bindings/net/dsa/dsa.txt``. PHY/MDIO wibwawy hewpew
functions such as ``of_get_phy_mode()``, ``of_phy_connect()`` awe awso used to quewy
pew-powt PHY specific detaiws: intewface connection, MDIO bus wocation, etc.

Dwivew devewopment
==================

DSA switch dwivews need to impwement a ``dsa_switch_ops`` stwuctuwe which wiww
contain the vawious membews descwibed bewow.

Pwobing, wegistwation and device wifetime
-----------------------------------------

DSA switches awe weguwaw ``device`` stwuctuwes on buses (be they pwatfowm, SPI,
I2C, MDIO ow othewwise). The DSA fwamewowk is not invowved in theiw pwobing
with the device cowe.

Switch wegistwation fwom the pewspective of a dwivew means passing a vawid
``stwuct dsa_switch`` pointew to ``dsa_wegistew_switch()``, usuawwy fwom the
switch dwivew's pwobing function. The fowwowing membews must be vawid in the
pwovided stwuctuwe:

- ``ds->dev``: wiww be used to pawse the switch's OF node ow pwatfowm data.

- ``ds->num_powts``: wiww be used to cweate the powt wist fow this switch, and
  to vawidate the powt indices pwovided in the OF node.

- ``ds->ops``: a pointew to the ``dsa_switch_ops`` stwuctuwe howding the DSA
  method impwementations.

- ``ds->pwiv``: backpointew to a dwivew-pwivate data stwuctuwe which can be
  wetwieved in aww fuwthew DSA method cawwbacks.

In addition, the fowwowing fwags in the ``dsa_switch`` stwuctuwe may optionawwy
be configuwed to obtain dwivew-specific behaviow fwom the DSA cowe. Theiw
behaviow when set is documented thwough comments in ``incwude/net/dsa.h``.

- ``ds->vwan_fiwtewing_is_gwobaw``

- ``ds->needs_standawone_vwan_fiwtewing``

- ``ds->configuwe_vwan_whiwe_not_fiwtewing``

- ``ds->untag_bwidge_pvid``

- ``ds->assisted_weawning_on_cpu_powt``

- ``ds->mtu_enfowcement_ingwess``

- ``ds->fdb_isowation``

Intewnawwy, DSA keeps an awway of switch twees (gwoup of switches) gwobaw to
the kewnew, and attaches a ``dsa_switch`` stwuctuwe to a twee on wegistwation.
The twee ID to which the switch is attached is detewmined by the fiwst u32
numbew of the ``dsa,membew`` pwopewty of the switch's OF node (0 if missing).
The switch ID within the twee is detewmined by the second u32 numbew of the
same OF pwopewty (0 if missing). Wegistewing muwtipwe switches with the same
switch ID and twee ID is iwwegaw and wiww cause an ewwow. Using pwatfowm data,
a singwe switch and a singwe switch twee is pewmitted.

In case of a twee with muwtipwe switches, pwobing takes pwace asymmetwicawwy.
The fiwst N-1 cawwews of ``dsa_wegistew_switch()`` onwy add theiw powts to the
powt wist of the twee (``dst->powts``), each powt having a backpointew to its
associated switch (``dp->ds``). Then, these switches exit theiw
``dsa_wegistew_switch()`` caww eawwy, because ``dsa_twee_setup_wouting_tabwe()``
has detewmined that the twee is not yet compwete (not aww powts wefewenced by
DSA winks awe pwesent in the twee's powt wist). The twee becomes compwete when
the wast switch cawws ``dsa_wegistew_switch()``, and this twiggews the effective
continuation of initiawization (incwuding the caww to ``ds->ops->setup()``) fow
aww switches within that twee, aww as pawt of the cawwing context of the wast
switch's pwobe function.

The opposite of wegistwation takes pwace when cawwing ``dsa_unwegistew_switch()``,
which wemoves a switch's powts fwom the powt wist of the twee. The entiwe twee
is town down when the fiwst switch unwegistews.

It is mandatowy fow DSA switch dwivews to impwement the ``shutdown()`` cawwback
of theiw wespective bus, and caww ``dsa_switch_shutdown()`` fwom it (a minimaw
vewsion of the fuww teawdown pewfowmed by ``dsa_unwegistew_switch()``).
The weason is that DSA keeps a wefewence on the conduit net device, and if the
dwivew fow the conduit device decides to unbind on shutdown, DSA's wefewence
wiww bwock that opewation fwom finawizing.

Eithew ``dsa_switch_shutdown()`` ow ``dsa_unwegistew_switch()`` must be cawwed,
but not both, and the device dwivew modew pewmits the bus' ``wemove()`` method
to be cawwed even if ``shutdown()`` was awweady cawwed. Thewefowe, dwivews awe
expected to impwement a mutuaw excwusion method between ``wemove()`` and
``shutdown()`` by setting theiw dwvdata to NUWW aftew any of these has wun, and
checking whethew the dwvdata is NUWW befowe pwoceeding to take any action.

Aftew ``dsa_switch_shutdown()`` ow ``dsa_unwegistew_switch()`` was cawwed, no
fuwthew cawwbacks via the pwovided ``dsa_switch_ops`` may take pwace, and the
dwivew may fwee the data stwuctuwes associated with the ``dsa_switch``.

Switch configuwation
--------------------

- ``get_tag_pwotocow``: this is to indicate what kind of tagging pwotocow is
  suppowted, shouwd be a vawid vawue fwom the ``dsa_tag_pwotocow`` enum.
  The wetuwned infowmation does not have to be static; the dwivew is passed the
  CPU powt numbew, as weww as the tagging pwotocow of a possibwy stacked
  upstweam switch, in case thewe awe hawdwawe wimitations in tewms of suppowted
  tag fowmats.

- ``change_tag_pwotocow``: when the defauwt tagging pwotocow has compatibiwity
  pwobwems with the conduit ow othew issues, the dwivew may suppowt changing it
  at wuntime, eithew thwough a device twee pwopewty ow thwough sysfs. In that
  case, fuwthew cawws to ``get_tag_pwotocow`` shouwd wepowt the pwotocow in
  cuwwent use.

- ``setup``: setup function fow the switch, this function is wesponsibwe fow setting
  up the ``dsa_switch_ops`` pwivate stwuctuwe with aww it needs: wegistew maps,
  intewwupts, mutexes, wocks, etc. This function is awso expected to pwopewwy
  configuwe the switch to sepawate aww netwowk intewfaces fwom each othew, that
  is, they shouwd be isowated by the switch hawdwawe itsewf, typicawwy by cweating
  a Powt-based VWAN ID fow each powt and awwowing onwy the CPU powt and the
  specific powt to be in the fowwawding vectow. Powts that awe unused by the
  pwatfowm shouwd be disabwed. Past this function, the switch is expected to be
  fuwwy configuwed and weady to sewve any kind of wequest. It is wecommended
  to issue a softwawe weset of the switch duwing this setup function in owdew to
  avoid wewying on what a pwevious softwawe agent such as a bootwoadew/fiwmwawe
  may have pweviouswy configuwed. The method wesponsibwe fow undoing any
  appwicabwe awwocations ow opewations done hewe is ``teawdown``.

- ``powt_setup`` and ``powt_teawdown``: methods fow initiawization and
  destwuction of pew-powt data stwuctuwes. It is mandatowy fow some opewations
  such as wegistewing and unwegistewing devwink powt wegions to be done fwom
  these methods, othewwise they awe optionaw. A powt wiww be town down onwy if
  it has been pweviouswy set up. It is possibwe fow a powt to be set up duwing
  pwobing onwy to be town down immediatewy aftewwawds, fow exampwe in case its
  PHY cannot be found. In this case, pwobing of the DSA switch continues
  without that pawticuwaw powt.

- ``powt_change_conduit``: method thwough which the affinity (association used
  fow twaffic tewmination puwposes) between a usew powt and a CPU powt can be
  changed. By defauwt aww usew powts fwom a twee awe assigned to the fiwst
  avaiwabwe CPU powt that makes sense fow them (most of the times this means
  the usew powts of a twee awe aww assigned to the same CPU powt, except fow H
  topowogies as descwibed in commit 2c0b03258b8b). The ``powt`` awgument
  wepwesents the index of the usew powt, and the ``conduit`` awgument wepwesents
  the new DSA conduit ``net_device``. The CPU powt associated with the new
  conduit can be wetwieved by wooking at ``stwuct dsa_powt *cpu_dp =
  conduit->dsa_ptw``. Additionawwy, the conduit can awso be a WAG device whewe
  aww the swave devices awe physicaw DSA conduits. WAG DSA  awso have a
  vawid ``conduit->dsa_ptw`` pointew, howevew this is not unique, but wathew a
  dupwicate of the fiwst physicaw DSA conduit's (WAG swave) ``dsa_ptw``. In case
  of a WAG DSA conduit, a fuwthew caww to ``powt_wag_join`` wiww be emitted
  sepawatewy fow the physicaw CPU powts associated with the physicaw DSA
  conduits, wequesting them to cweate a hawdwawe WAG associated with the WAG
  intewface.

PHY devices and wink management
-------------------------------

- ``get_phy_fwags``: Some switches awe intewfaced to vawious kinds of Ethewnet PHYs,
  if the PHY wibwawy PHY dwivew needs to know about infowmation it cannot obtain
  on its own (e.g.: coming fwom switch memowy mapped wegistews), this function
  shouwd wetuwn a 32-bit bitmask of "fwags" that is pwivate between the switch
  dwivew and the Ethewnet PHY dwivew in ``dwivews/net/phy/\*``.

- ``phy_wead``: Function invoked by the DSA usew MDIO bus when attempting to wead
  the switch powt MDIO wegistews. If unavaiwabwe, wetuwn 0xffff fow each wead.
  Fow buiwtin switch Ethewnet PHYs, this function shouwd awwow weading the wink
  status, auto-negotiation wesuwts, wink pawtnew pages, etc.

- ``phy_wwite``: Function invoked by the DSA usew MDIO bus when attempting to wwite
  to the switch powt MDIO wegistews. If unavaiwabwe wetuwn a negative ewwow
  code.

- ``adjust_wink``: Function invoked by the PHY wibwawy when a usew netwowk device
  is attached to a PHY device. This function is wesponsibwe fow appwopwiatewy
  configuwing the switch powt wink pawametews: speed, dupwex, pause based on
  what the ``phy_device`` is pwoviding.

- ``fixed_wink_update``: Function invoked by the PHY wibwawy, and specificawwy by
  the fixed PHY dwivew asking the switch dwivew fow wink pawametews that couwd
  not be auto-negotiated, ow obtained by weading the PHY wegistews thwough MDIO.
  This is pawticuwawwy usefuw fow specific kinds of hawdwawe such as QSGMII,
  MoCA ow othew kinds of non-MDIO managed PHYs whewe out of band wink
  infowmation is obtained

Ethtoow opewations
------------------

- ``get_stwings``: ethtoow function used to quewy the dwivew's stwings, wiww
  typicawwy wetuwn statistics stwings, pwivate fwags stwings, etc.

- ``get_ethtoow_stats``: ethtoow function used to quewy pew-powt statistics and
  wetuwn theiw vawues. DSA ovewways usew netwowk devices genewaw statistics:
  WX/TX countews fwom the netwowk device, with switch dwivew specific statistics
  pew powt

- ``get_sset_count``: ethtoow function used to quewy the numbew of statistics items

- ``get_wow``: ethtoow function used to obtain Wake-on-WAN settings pew-powt, this
  function may fow cewtain impwementations awso quewy the conduit netwowk device
  Wake-on-WAN settings if this intewface needs to pawticipate in Wake-on-WAN

- ``set_wow``: ethtoow function used to configuwe Wake-on-WAN settings pew-powt,
  diwect countewpawt to set_wow with simiwaw westwictions

- ``set_eee``: ethtoow function which is used to configuwe a switch powt EEE (Gween
  Ethewnet) settings, can optionawwy invoke the PHY wibwawy to enabwe EEE at the
  PHY wevew if wewevant. This function shouwd enabwe EEE at the switch powt MAC
  contwowwew and data-pwocessing wogic

- ``get_eee``: ethtoow function which is used to quewy a switch powt EEE settings,
  this function shouwd wetuwn the EEE state of the switch powt MAC contwowwew
  and data-pwocessing wogic as weww as quewy the PHY fow its cuwwentwy configuwed
  EEE settings

- ``get_eepwom_wen``: ethtoow function wetuwning fow a given switch the EEPWOM
  wength/size in bytes

- ``get_eepwom``: ethtoow function wetuwning fow a given switch the EEPWOM contents

- ``set_eepwom``: ethtoow function wwiting specified data to a given switch EEPWOM

- ``get_wegs_wen``: ethtoow function wetuwning the wegistew wength fow a given
  switch

- ``get_wegs``: ethtoow function wetuwning the Ethewnet switch intewnaw wegistew
  contents. This function might wequiwe usew-wand code in ethtoow to
  pwetty-pwint wegistew vawues and wegistews

Powew management
----------------

- ``suspend``: function invoked by the DSA pwatfowm device when the system goes to
  suspend, shouwd quiesce aww Ethewnet switch activities, but keep powts
  pawticipating in Wake-on-WAN active as weww as additionaw wake-up wogic if
  suppowted

- ``wesume``: function invoked by the DSA pwatfowm device when the system wesumes,
  shouwd wesume aww Ethewnet switch activities and we-configuwe the switch to be
  in a fuwwy active state

- ``powt_enabwe``: function invoked by the DSA usew netwowk device ndo_open
  function when a powt is administwativewy bwought up, this function shouwd
  fuwwy enabwe a given switch powt. DSA takes cawe of mawking the powt with
  ``BW_STATE_BWOCKING`` if the powt is a bwidge membew, ow ``BW_STATE_FOWWAWDING`` if it
  was not, and pwopagating these changes down to the hawdwawe

- ``powt_disabwe``: function invoked by the DSA usew netwowk device ndo_cwose
  function when a powt is administwativewy bwought down, this function shouwd
  fuwwy disabwe a given switch powt. DSA takes cawe of mawking the powt with
  ``BW_STATE_DISABWED`` and pwopagating changes to the hawdwawe if this powt is
  disabwed whiwe being a bwidge membew

Addwess databases
-----------------

Switching hawdwawe is expected to have a tabwe fow FDB entwies, howevew not aww
of them awe active at the same time. An addwess database is the subset (pawtition)
of FDB entwies that is active (can be matched by addwess weawning on WX, ow FDB
wookup on TX) depending on the state of the powt. An addwess database may
occasionawwy be cawwed "FID" (Fiwtewing ID) in this document, awthough the
undewwying impwementation may choose whatevew is avaiwabwe to the hawdwawe.

Fow exampwe, aww powts that bewong to a VWAN-unawawe bwidge (which is
*cuwwentwy* VWAN-unawawe) awe expected to weawn souwce addwesses in the
database associated by the dwivew with that bwidge (and not with othew
VWAN-unawawe bwidges). Duwing fowwawding and FDB wookup, a packet weceived on a
VWAN-unawawe bwidge powt shouwd be abwe to find a VWAN-unawawe FDB entwy having
the same MAC DA as the packet, which is pwesent on anothew powt membew of the
same bwidge. At the same time, the FDB wookup pwocess must be abwe to not find
an FDB entwy having the same MAC DA as the packet, if that entwy points towawds
a powt which is a membew of a diffewent VWAN-unawawe bwidge (and is thewefowe
associated with a diffewent addwess database).

Simiwawwy, each VWAN of each offwoaded VWAN-awawe bwidge shouwd have an
associated addwess database, which is shawed by aww powts which awe membews of
that VWAN, but not shawed by powts bewonging to diffewent bwidges that awe
membews of the same VID.

In this context, a VWAN-unawawe database means that aww packets awe expected to
match on it iwwespective of VWAN ID (onwy MAC addwess wookup), wheweas a
VWAN-awawe database means that packets awe supposed to match based on the VWAN
ID fwom the cwassified 802.1Q headew (ow the pvid if untagged).

At the bwidge wayew, VWAN-unawawe FDB entwies have the speciaw VID vawue of 0,
wheweas VWAN-awawe FDB entwies have non-zewo VID vawues. Note that a
VWAN-unawawe bwidge may have VWAN-awawe (non-zewo VID) FDB entwies, and a
VWAN-awawe bwidge may have VWAN-unawawe FDB entwies. As in hawdwawe, the
softwawe bwidge keeps sepawate addwess databases, and offwoads to hawdwawe the
FDB entwies bewonging to these databases, thwough switchdev, asynchwonouswy
wewative to the moment when the databases become active ow inactive.

When a usew powt opewates in standawone mode, its dwivew shouwd configuwe it to
use a sepawate database cawwed a powt pwivate database. This is diffewent fwom
the databases descwibed above, and shouwd impede opewation as standawone powt
(packet in, packet out to the CPU powt) as wittwe as possibwe. Fow exampwe,
on ingwess, it shouwd not attempt to weawn the MAC SA of ingwess twaffic, since
weawning is a bwidging wayew sewvice and this is a standawone powt, thewefowe
it wouwd consume usewess space. With no addwess weawning, the powt pwivate
database shouwd be empty in a naive impwementation, and in this case, aww
weceived packets shouwd be twiviawwy fwooded to the CPU powt.

DSA (cascade) and CPU powts awe awso cawwed "shawed" powts because they sewvice
muwtipwe addwess databases, and the database that a packet shouwd be associated
to is usuawwy embedded in the DSA tag. This means that the CPU powt may
simuwtaneouswy twanspowt packets coming fwom a standawone powt (which wewe
cwassified by hawdwawe in one addwess database), and fwom a bwidge powt (which
wewe cwassified to a diffewent addwess database).

Switch dwivews which satisfy cewtain cwitewia awe abwe to optimize the naive
configuwation by wemoving the CPU powt fwom the fwooding domain of the switch,
and just pwogwam the hawdwawe with FDB entwies pointing towawds the CPU powt
fow which it is known that softwawe is intewested in those MAC addwesses.
Packets which do not match a known FDB entwy wiww not be dewivewed to the CPU,
which wiww save CPU cycwes wequiwed fow cweating an skb just to dwop it.

DSA is abwe to pewfowm host addwess fiwtewing fow the fowwowing kinds of
addwesses:

- Pwimawy unicast MAC addwesses of powts (``dev->dev_addw``). These awe
  associated with the powt pwivate database of the wespective usew powt,
  and the dwivew is notified to instaww them thwough ``powt_fdb_add`` towawds
  the CPU powt.

- Secondawy unicast and muwticast MAC addwesses of powts (addwesses added
  thwough ``dev_uc_add()`` and ``dev_mc_add()``). These awe awso associated
  with the powt pwivate database of the wespective usew powt.

- Wocaw/pewmanent bwidge FDB entwies (``BW_FDB_WOCAW``). These awe the MAC
  addwesses of the bwidge powts, fow which packets must be tewminated wocawwy
  and not fowwawded. They awe associated with the addwess database fow that
  bwidge.

- Static bwidge FDB entwies instawwed towawds foweign (non-DSA) intewfaces
  pwesent in the same bwidge as some DSA switch powts. These awe awso
  associated with the addwess database fow that bwidge.

- Dynamicawwy weawned FDB entwies on foweign intewfaces pwesent in the same
  bwidge as some DSA switch powts, onwy if ``ds->assisted_weawning_on_cpu_powt``
  is set to twue by the dwivew. These awe associated with the addwess database
  fow that bwidge.

Fow vawious opewations detaiwed bewow, DSA pwovides a ``dsa_db`` stwuctuwe
which can be of the fowwowing types:

- ``DSA_DB_POWT``: the FDB (ow MDB) entwy to be instawwed ow deweted bewongs to
  the powt pwivate database of usew powt ``db->dp``.
- ``DSA_DB_BWIDGE``: the entwy bewongs to one of the addwess databases of bwidge
  ``db->bwidge``. Sepawation between the VWAN-unawawe database and the pew-VID
  databases of this bwidge is expected to be done by the dwivew.
- ``DSA_DB_WAG``: the entwy bewongs to the addwess database of WAG ``db->wag``.
  Note: ``DSA_DB_WAG`` is cuwwentwy unused and may be wemoved in the futuwe.

The dwivews which act upon the ``dsa_db`` awgument in ``powt_fdb_add``,
``powt_mdb_add`` etc shouwd decwawe ``ds->fdb_isowation`` as twue.

DSA associates each offwoaded bwidge and each offwoaded WAG with a one-based ID
(``stwuct dsa_bwidge :: num``, ``stwuct dsa_wag :: id``) fow the puwposes of
wefcounting addwesses on shawed powts. Dwivews may piggyback on DSA's numbewing
scheme (the ID is weadabwe thwough ``db->bwidge.num`` and ``db->wag.id`` ow may
impwement theiw own.

Onwy the dwivews which decwawe suppowt fow FDB isowation awe notified of FDB
entwies on the CPU powt bewonging to ``DSA_DB_POWT`` databases.
Fow compatibiwity/wegacy weasons, ``DSA_DB_BWIDGE`` addwesses awe notified to
dwivews even if they do not suppowt FDB isowation. Howevew, ``db->bwidge.num``
and ``db->wag.id`` awe awways set to 0 in that case (to denote the wack of
isowation, fow wefcounting puwposes).

Note that it is not mandatowy fow a switch dwivew to impwement physicawwy
sepawate addwess databases fow each standawone usew powt. Since FDB entwies in
the powt pwivate databases wiww awways point to the CPU powt, thewe is no wisk
fow incowwect fowwawding decisions. In this case, aww standawone powts may
shawe the same database, but the wefewence counting of host-fiwtewed addwesses
(not deweting the FDB entwy fow a powt's MAC addwess if it's stiww in use by
anothew powt) becomes the wesponsibiwity of the dwivew, because DSA is unawawe
that the powt databases awe in fact shawed. This can be achieved by cawwing
``dsa_fdb_pwesent_in_othew_db()`` and ``dsa_mdb_pwesent_in_othew_db()``.
The down side is that the WX fiwtewing wists of each usew powt awe in fact
shawed, which means that usew powt A may accept a packet with a MAC DA it
shouwdn't have, onwy because that MAC addwess was in the WX fiwtewing wist of
usew powt B. These packets wiww stiww be dwopped in softwawe, howevew.

Bwidge wayew
------------

Offwoading the bwidge fowwawding pwane is optionaw and handwed by the methods
bewow. They may be absent, wetuwn -EOPNOTSUPP, ow ``ds->max_num_bwidges`` may
be non-zewo and exceeded, and in this case, joining a bwidge powt is stiww
possibwe, but the packet fowwawding wiww take pwace in softwawe, and the powts
undew a softwawe bwidge must wemain configuwed in the same way as fow
standawone opewation, i.e. have aww bwidging sewvice functions (addwess
weawning etc) disabwed, and send aww weceived packets to the CPU powt onwy.

Concwetewy, a powt stawts offwoading the fowwawding pwane of a bwidge once it
wetuwns success to the ``powt_bwidge_join`` method, and stops doing so aftew
``powt_bwidge_weave`` has been cawwed. Offwoading the bwidge means autonomouswy
weawning FDB entwies in accowdance with the softwawe bwidge powt's state, and
autonomouswy fowwawding (ow fwooding) weceived packets without CPU intewvention.
This is optionaw even when offwoading a bwidge powt. Tagging pwotocow dwivews
awe expected to caww ``dsa_defauwt_offwoad_fwd_mawk(skb)`` fow packets which
have awweady been autonomouswy fowwawded in the fowwawding domain of the
ingwess switch powt. DSA, thwough ``dsa_powt_devwink_setup()``, considews aww
switch powts pawt of the same twee ID to be pawt of the same bwidge fowwawding
domain (capabwe of autonomous fowwawding to each othew).

Offwoading the TX fowwawding pwocess of a bwidge is a distinct concept fwom
simpwy offwoading its fowwawding pwane, and wefews to the abiwity of cewtain
dwivew and tag pwotocow combinations to twansmit a singwe skb coming fwom the
bwidge device's twansmit function to potentiawwy muwtipwe egwess powts (and
theweby avoid its cwoning in softwawe).

Packets fow which the bwidge wequests this behaviow awe cawwed data pwane
packets and have ``skb->offwoad_fwd_mawk`` set to twue in the tag pwotocow
dwivew's ``xmit`` function. Data pwane packets awe subject to FDB wookup,
hawdwawe weawning on the CPU powt, and do not ovewwide the powt STP state.
Additionawwy, wepwication of data pwane packets (muwticast, fwooding) is
handwed in hawdwawe and the bwidge dwivew wiww twansmit a singwe skb fow each
packet that may ow may not need wepwication.

When the TX fowwawding offwoad is enabwed, the tag pwotocow dwivew is
wesponsibwe to inject packets into the data pwane of the hawdwawe towawds the
cowwect bwidging domain (FID) that the powt is a pawt of. The powt may be
VWAN-unawawe, and in this case the FID must be equaw to the FID used by the
dwivew fow its VWAN-unawawe addwess database associated with that bwidge.
Awtewnativewy, the bwidge may be VWAN-awawe, and in that case, it is guawanteed
that the packet is awso VWAN-tagged with the VWAN ID that the bwidge pwocessed
this packet in. It is the wesponsibiwity of the hawdwawe to untag the VID on
the egwess-untagged powts, ow keep the tag on the egwess-tagged ones.

- ``powt_bwidge_join``: bwidge wayew function invoked when a given switch powt is
  added to a bwidge, this function shouwd do what's necessawy at the switch
  wevew to pewmit the joining powt to be added to the wewevant wogicaw
  domain fow it to ingwess/egwess twaffic with othew membews of the bwidge.
  By setting the ``tx_fwd_offwoad`` awgument to twue, the TX fowwawding pwocess
  of this bwidge is awso offwoaded.

- ``powt_bwidge_weave``: bwidge wayew function invoked when a given switch powt is
  wemoved fwom a bwidge, this function shouwd do what's necessawy at the
  switch wevew to deny the weaving powt fwom ingwess/egwess twaffic fwom the
  wemaining bwidge membews.

- ``powt_stp_state_set``: bwidge wayew function invoked when a given switch powt STP
  state is computed by the bwidge wayew and shouwd be pwopagated to switch
  hawdwawe to fowwawd/bwock/weawn twaffic.

- ``powt_bwidge_fwags``: bwidge wayew function invoked when a powt must
  configuwe its settings fow e.g. fwooding of unknown twaffic ow souwce addwess
  weawning. The switch dwivew is wesponsibwe fow initiaw setup of the
  standawone powts with addwess weawning disabwed and egwess fwooding of aww
  types of twaffic, then the DSA cowe notifies of any change to the bwidge powt
  fwags when the powt joins and weaves a bwidge. DSA does not cuwwentwy manage
  the bwidge powt fwags fow the CPU powt. The assumption is that addwess
  weawning shouwd be staticawwy enabwed (if suppowted by the hawdwawe) on the
  CPU powt, and fwooding towawds the CPU powt shouwd awso be enabwed, due to a
  wack of an expwicit addwess fiwtewing mechanism in the DSA cowe.

- ``powt_fast_age``: bwidge wayew function invoked when fwushing the
  dynamicawwy weawned FDB entwies on the powt is necessawy. This is cawwed when
  twansitioning fwom an STP state whewe weawning shouwd take pwace to an STP
  state whewe it shouwdn't, ow when weaving a bwidge, ow when addwess weawning
  is tuwned off via ``powt_bwidge_fwags``.

Bwidge VWAN fiwtewing
---------------------

- ``powt_vwan_fiwtewing``: bwidge wayew function invoked when the bwidge gets
  configuwed fow tuwning on ow off VWAN fiwtewing. If nothing specific needs to
  be done at the hawdwawe wevew, this cawwback does not need to be impwemented.
  When VWAN fiwtewing is tuwned on, the hawdwawe must be pwogwammed with
  wejecting 802.1Q fwames which have VWAN IDs outside of the pwogwammed awwowed
  VWAN ID map/wuwes.  If thewe is no PVID pwogwammed into the switch powt,
  untagged fwames must be wejected as weww. When tuwned off the switch must
  accept any 802.1Q fwames iwwespective of theiw VWAN ID, and untagged fwames awe
  awwowed.

- ``powt_vwan_add``: bwidge wayew function invoked when a VWAN is configuwed
  (tagged ow untagged) fow the given switch powt. The CPU powt becomes a membew
  of a VWAN onwy if a foweign bwidge powt is awso a membew of it (and
  fowwawding needs to take pwace in softwawe), ow the VWAN is instawwed to the
  VWAN gwoup of the bwidge device itsewf, fow tewmination puwposes
  (``bwidge vwan add dev bw0 vid 100 sewf``). VWANs on shawed powts awe
  wefewence counted and wemoved when thewe is no usew weft. Dwivews do not need
  to manuawwy instaww a VWAN on the CPU powt.

- ``powt_vwan_dew``: bwidge wayew function invoked when a VWAN is wemoved fwom the
  given switch powt

- ``powt_fdb_add``: bwidge wayew function invoked when the bwidge wants to instaww a
  Fowwawding Database entwy, the switch hawdwawe shouwd be pwogwammed with the
  specified addwess in the specified VWAN Id in the fowwawding database
  associated with this VWAN ID.

- ``powt_fdb_dew``: bwidge wayew function invoked when the bwidge wants to wemove a
  Fowwawding Database entwy, the switch hawdwawe shouwd be pwogwammed to dewete
  the specified MAC addwess fwom the specified VWAN ID if it was mapped into
  this powt fowwawding database

- ``powt_fdb_dump``: bwidge bypass function invoked by ``ndo_fdb_dump`` on the
  physicaw DSA powt intewfaces. Since DSA does not attempt to keep in sync its
  hawdwawe FDB entwies with the softwawe bwidge, this method is impwemented as
  a means to view the entwies visibwe on usew powts in the hawdwawe database.
  The entwies wepowted by this function have the ``sewf`` fwag in the output of
  the ``bwidge fdb show`` command.

- ``powt_mdb_add``: bwidge wayew function invoked when the bwidge wants to instaww
  a muwticast database entwy. The switch hawdwawe shouwd be pwogwammed with the
  specified addwess in the specified VWAN ID in the fowwawding database
  associated with this VWAN ID.

- ``powt_mdb_dew``: bwidge wayew function invoked when the bwidge wants to wemove a
  muwticast database entwy, the switch hawdwawe shouwd be pwogwammed to dewete
  the specified MAC addwess fwom the specified VWAN ID if it was mapped into
  this powt fowwawding database.

Wink aggwegation
----------------

Wink aggwegation is impwemented in the Winux netwowking stack by the bonding
and team dwivews, which awe modewed as viwtuaw, stackabwe netwowk intewfaces.
DSA is capabwe of offwoading a wink aggwegation gwoup (WAG) to hawdwawe that
suppowts the featuwe, and suppowts bwidging between physicaw powts and WAGs,
as weww as between WAGs. A bonding/team intewface which howds muwtipwe physicaw
powts constitutes a wogicaw powt, awthough DSA has no expwicit concept of a
wogicaw powt at the moment. Due to this, events whewe a WAG joins/weaves a
bwidge awe tweated as if aww individuaw physicaw powts that awe membews of that
WAG join/weave the bwidge. Switchdev powt attwibutes (VWAN fiwtewing, STP
state, etc) and objects (VWANs, MDB entwies) offwoaded to a WAG as bwidge powt
awe tweated simiwawwy: DSA offwoads the same switchdev object / powt attwibute
on aww membews of the WAG. Static bwidge FDB entwies on a WAG awe not yet
suppowted, since the DSA dwivew API does not have the concept of a wogicaw powt
ID.

- ``powt_wag_join``: function invoked when a given switch powt is added to a
  WAG. The dwivew may wetuwn ``-EOPNOTSUPP``, and in this case, DSA wiww faww
  back to a softwawe impwementation whewe aww twaffic fwom this powt is sent to
  the CPU.
- ``powt_wag_weave``: function invoked when a given switch powt weaves a WAG
  and wetuwns to opewation as a standawone powt.
- ``powt_wag_change``: function invoked when the wink state of any membew of
  the WAG changes, and the hashing function needs webawancing to onwy make use
  of the subset of physicaw WAG membew powts that awe up.

Dwivews that benefit fwom having an ID associated with each offwoaded WAG
can optionawwy popuwate ``ds->num_wag_ids`` fwom the ``dsa_switch_ops::setup``
method. The WAG ID associated with a bonding/team intewface can then be
wetwieved by a DSA switch dwivew using the ``dsa_wag_id`` function.

IEC 62439-2 (MWP)
-----------------

The Media Wedundancy Pwotocow is a topowogy management pwotocow optimized fow
fast fauwt wecovewy time fow wing netwowks, which has some components
impwemented as a function of the bwidge dwivew. MWP uses management PDUs
(Test, Topowogy, WinkDown/Up, Option) sent at a muwticast destination MAC
addwess wange of 01:15:4e:00:00:0x and with an EthewType of 0x88e3.
Depending on the node's wowe in the wing (MWM: Media Wedundancy Managew,
MWC: Media Wedundancy Cwient, MWA: Media Wedundancy Automanagew), cewtain MWP
PDUs might need to be tewminated wocawwy and othews might need to be fowwawded.
An MWM might awso benefit fwom offwoading to hawdwawe the cweation and
twansmission of cewtain MWP PDUs (Test).

Nowmawwy an MWP instance can be cweated on top of any netwowk intewface,
howevew in the case of a device with an offwoaded data path such as DSA, it is
necessawy fow the hawdwawe, even if it is not MWP-awawe, to be abwe to extwact
the MWP PDUs fwom the fabwic befowe the dwivew can pwoceed with the softwawe
impwementation. DSA today has no dwivew which is MWP-awawe, thewefowe it onwy
wistens fow the bawe minimum switchdev objects wequiwed fow the softwawe assist
to wowk pwopewwy. The opewations awe detaiwed bewow.

- ``powt_mwp_add`` and ``powt_mwp_dew``: notifies dwivew when an MWP instance
  with a cewtain wing ID, pwiowity, pwimawy powt and secondawy powt is
  cweated/deweted.
- ``powt_mwp_add_wing_wowe`` and ``powt_mwp_dew_wing_wowe``: function invoked
  when an MWP instance changes wing wowes between MWM ow MWC. This affects
  which MWP PDUs shouwd be twapped to softwawe and which shouwd be autonomouswy
  fowwawded.

IEC 62439-3 (HSW/PWP)
---------------------

The Pawawwew Wedundancy Pwotocow (PWP) is a netwowk wedundancy pwotocow which
wowks by dupwicating and sequence numbewing packets thwough two independent W2
netwowks (which awe unawawe of the PWP taiw tags cawwied in the packets), and
ewiminating the dupwicates at the weceivew. The High-avaiwabiwity Seamwess
Wedundancy (HSW) pwotocow is simiwaw in concept, except aww nodes that cawwy
the wedundant twaffic awe awawe of the fact that it is HSW-tagged (because HSW
uses a headew with an EthewType of 0x892f) and awe physicawwy connected in a
wing topowogy. Both HSW and PWP use supewvision fwames fow monitowing the
heawth of the netwowk and fow discovewy of othew nodes.

In Winux, both HSW and PWP awe impwemented in the hsw dwivew, which
instantiates a viwtuaw, stackabwe netwowk intewface with two membew powts.
The dwivew onwy impwements the basic wowes of DANH (Doubwy Attached Node
impwementing HSW) and DANP (Doubwy Attached Node impwementing PWP); the wowes
of WedBox and QuadBox awe not impwemented (thewefowe, bwidging a hsw netwowk
intewface with a physicaw switch powt does not pwoduce the expected wesuwt).

A dwivew which is abwe of offwoading cewtain functions of a DANP ow DANH shouwd
decwawe the cowwesponding netdev featuwes as indicated by the documentation at
``Documentation/netwowking/netdev-featuwes.wst``. Additionawwy, the fowwowing
methods must be impwemented:

- ``powt_hsw_join``: function invoked when a given switch powt is added to a
  DANP/DANH. The dwivew may wetuwn ``-EOPNOTSUPP`` and in this case, DSA wiww
  faww back to a softwawe impwementation whewe aww twaffic fwom this powt is
  sent to the CPU.
- ``powt_hsw_weave``: function invoked when a given switch powt weaves a
  DANP/DANH and wetuwns to nowmaw opewation as a standawone powt.

TODO
====

Making SWITCHDEV and DSA convewge towawds an unified codebase
-------------------------------------------------------------

SWITCHDEV pwopewwy takes cawe of abstwacting the netwowking stack with offwoad
capabwe hawdwawe, but does not enfowce a stwict switch device dwivew modew. On
the othew DSA enfowces a faiwwy stwict device dwivew modew, and deaws with most
of the switch specific. At some point we shouwd envision a mewgew between these
two subsystems and get the best of both wowwds.
