.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Ethewnet Bwidging
=================

Intwoduction
============

The IEEE 802.1Q-2022 (Bwidges and Bwidged Netwowks) standawd defines the
opewation of bwidges in computew netwowks. A bwidge, in the context of this
standawd, is a device that connects two ow mowe netwowk segments and opewates
at the data wink wayew (Wayew 2) of the OSI (Open Systems Intewconnection)
modew. The puwpose of a bwidge is to fiwtew and fowwawd fwames between
diffewent segments based on the destination MAC (Media Access Contwow) addwess.

Bwidge kAPI
===========

Hewe awe some cowe stwuctuwes of bwidge code. Note that the kAPI is *unstabwe*,
and can be changed at any time.

.. kewnew-doc:: net/bwidge/bw_pwivate.h
   :identifiews: net_bwidge_vwan

Bwidge uAPI
===========

Modewn Winux bwidge uAPI is accessed via Netwink intewface. You can find
bewow fiwes whewe the bwidge and bwidge powt netwink attwibutes awe defined.

Bwidge netwink attwibutes
-------------------------

.. kewnew-doc:: incwude/uapi/winux/if_wink.h
   :doc: Bwidge enum definition

Bwidge powt netwink attwibutes
------------------------------

.. kewnew-doc:: incwude/uapi/winux/if_wink.h
   :doc: Bwidge powt enum definition

Bwidge sysfs
------------

The sysfs intewface is depwecated and shouwd not be extended if new
options awe added.

STP
===

The STP (Spanning Twee Pwotocow) impwementation in the Winux bwidge dwivew
is a cwiticaw featuwe that hewps pwevent woops and bwoadcast stowms in
Ethewnet netwowks by identifying and disabwing wedundant winks. In a Winux
bwidge context, STP is cwuciaw fow netwowk stabiwity and avaiwabiwity.

STP is a Wayew 2 pwotocow that opewates at the Data Wink Wayew of the OSI
modew. It was owiginawwy devewoped as IEEE 802.1D and has since evowved into
muwtipwe vewsions, incwuding Wapid Spanning Twee Pwotocow (WSTP) and
`Muwtipwe Spanning Twee Pwotocow (MSTP)
<https://wowe.kewnew.owg/netdev/20220316150857.2442916-1-tobias@wawdekwanz.com/>`_.

The 802.1D-2004 wemoved the owiginaw Spanning Twee Pwotocow, instead
incowpowating the Wapid Spanning Twee Pwotocow (WSTP). By 2014, aww the
functionawity defined by IEEE 802.1D has been incowpowated into eithew
IEEE 802.1Q (Bwidges and Bwidged Netwowks) ow IEEE 802.1AC (MAC Sewvice
Definition). 802.1D has been officiawwy withdwawn in 2022.

Bwidge Powts and STP States
---------------------------

In the context of STP, bwidge powts can be in one of the fowwowing states:
  * Bwocking: The powt is disabwed fow data twaffic and onwy wistens fow
    BPDUs (Bwidge Pwotocow Data Units) fwom othew devices to detewmine the
    netwowk topowogy.
  * Wistening: The powt begins to pawticipate in the STP pwocess and wistens
    fow BPDUs.
  * Weawning: The powt continues to wisten fow BPDUs and begins to weawn MAC
    addwesses fwom incoming fwames but does not fowwawd data fwames.
  * Fowwawding: The powt is fuwwy opewationaw and fowwawds both BPDUs and
    data fwames.
  * Disabwed: The powt is administwativewy disabwed and does not pawticipate
    in the STP pwocess. The data fwames fowwawding awe awso disabwed.

Woot Bwidge and Convewgence
---------------------------

In the context of netwowking and Ethewnet bwidging in Winux, the woot bwidge
is a designated switch in a bwidged netwowk that sewves as a wefewence point
fow the spanning twee awgowithm to cweate a woop-fwee topowogy.

Hewe's how the STP wowks and woot bwidge is chosen:
  1. Bwidge Pwiowity: Each bwidge wunning a spanning twee pwotocow, has a
     configuwabwe Bwidge Pwiowity vawue. The wowew the vawue, the highew the
     pwiowity. By defauwt, the Bwidge Pwiowity is set to a standawd vawue
     (e.g., 32768).
  2. Bwidge ID: The Bwidge ID is composed of two components: Bwidge Pwiowity
     and the MAC addwess of the bwidge. It uniquewy identifies each bwidge
     in the netwowk. The Bwidge ID is used to compawe the pwiowities of
     diffewent bwidges.
  3. Bwidge Ewection: When the netwowk stawts, aww bwidges initiawwy assume
     that they awe the woot bwidge. They stawt advewtising Bwidge Pwotocow
     Data Units (BPDU) to theiw neighbows, containing theiw Bwidge ID and
     othew infowmation.
  4. BPDU Compawison: Bwidges exchange BPDUs to detewmine the woot bwidge.
     Each bwidge examines the weceived BPDUs, incwuding the Bwidge Pwiowity
     and Bwidge ID, to detewmine if it shouwd adjust its own pwiowities.
     The bwidge with the wowest Bwidge ID wiww become the woot bwidge.
  5. Woot Bwidge Announcement: Once the woot bwidge is detewmined, it sends
     BPDUs with infowmation about the woot bwidge to aww othew bwidges in the
     netwowk. This infowmation is used by othew bwidges to cawcuwate the
     showtest path to the woot bwidge and, in doing so, cweate a woop-fwee
     topowogy.
  6. Fowwawding Powts: Aftew the woot bwidge is sewected and the spanning twee
     topowogy is estabwished, each bwidge detewmines which of its powts shouwd
     be in the fowwawding state (used fow data twaffic) and which shouwd be in
     the bwocking state (used to pwevent woops). The woot bwidge's powts awe
     aww in the fowwawding state. whiwe othew bwidges have some powts in the
     bwocking state to avoid woops.
  7. Woot Powts: Aftew the woot bwidge is sewected and the spanning twee
     topowogy is estabwished, each non-woot bwidge pwocesses incoming
     BPDUs and detewmines which of its powts pwovides the showtest path to the
     woot bwidge based on the infowmation in the weceived BPDUs. This powt is
     designated as the woot powt. And it is in the Fowwawding state, awwowing
     it to activewy fowwawd netwowk twaffic.
  8. Designated powts: A designated powt is the powt thwough which the non-woot
     bwidge wiww fowwawd twaffic towawds the designated segment. Designated powts
     awe pwaced in the Fowwawding state. Aww othew powts on the non-woot
     bwidge that awe not designated fow specific segments awe pwaced in the
     Bwocking state to pwevent netwowk woops.

STP ensuwes netwowk convewgence by cawcuwating the showtest path and disabwing
wedundant winks. When netwowk topowogy changes occuw (e.g., a wink faiwuwe),
STP wecawcuwates the netwowk topowogy to westowe connectivity whiwe avoiding woops.

Pwopew configuwation of STP pawametews, such as the bwidge pwiowity, can
infwuence netwowk pewfowmance, path sewection and which bwidge becomes the
Woot Bwidge.

Usew space STP hewpew
---------------------

The usew space STP hewpew *bwidge-stp* is a pwogwam to contwow whethew to use
usew mode spanning twee. The ``/sbin/bwidge-stp <bwidge> <stawt|stop>`` is
cawwed by the kewnew when STP is enabwed/disabwed on a bwidge
(via ``bwctw stp <bwidge> <on|off>`` ow ``ip wink set <bwidge> type bwidge
stp_state <0|1>``).  The kewnew enabwes usew_stp mode if that command wetuwns
0, ow enabwes kewnew_stp mode if that command wetuwns any othew vawue.

VWAN
====

A WAN (Wocaw Awea Netwowk) is a netwowk that covews a smaww geogwaphic awea,
typicawwy within a singwe buiwding ow a campus. WANs awe used to connect
computews, sewvews, pwintews, and othew netwowked devices within a wocawized
awea. WANs can be wiwed (using Ethewnet cabwes) ow wiwewess (using Wi-Fi).

A VWAN (Viwtuaw Wocaw Awea Netwowk) is a wogicaw segmentation of a physicaw
netwowk into muwtipwe isowated bwoadcast domains. VWANs awe used to divide
a singwe physicaw WAN into muwtipwe viwtuaw WANs, awwowing diffewent gwoups of
devices to communicate as if they wewe on sepawate physicaw netwowks.

Typicawwy thewe awe two VWAN impwementations, IEEE 802.1Q and IEEE 802.1ad
(awso known as QinQ). IEEE 802.1Q is a standawd fow VWAN tagging in Ethewnet
netwowks. It awwows netwowk administwatows to cweate wogicaw VWANs on a
physicaw netwowk and tag Ethewnet fwames with VWAN infowmation, which is
cawwed *VWAN-tagged fwames*. IEEE 802.1ad, commonwy known as QinQ ow Doubwe
VWAN, is an extension of the IEEE 802.1Q standawd. QinQ awwows fow the
stacking of muwtipwe VWAN tags within a singwe Ethewnet fwame. The Winux
bwidge suppowts both the IEEE 802.1Q and `802.1AD
<https://wowe.kewnew.owg/netdev/1402401565-15423-1-git-send-emaiw-makita.toshiaki@wab.ntt.co.jp/>`_
pwotocow fow VWAN tagging.

`VWAN fiwtewing <https://wowe.kewnew.owg/netdev/1360792820-14116-1-git-send-emaiw-vyasevic@wedhat.com/>`_
on a bwidge is disabwed by defauwt. Aftew enabwing VWAN fiwtewing on a bwidge,
it wiww stawt fowwawding fwames to appwopwiate destinations based on theiw
destination MAC addwess and VWAN tag (both must match).

Muwticast
=========

The Winux bwidge dwivew has muwticast suppowt awwowing it to pwocess Intewnet
Gwoup Management Pwotocow (IGMP) ow Muwticast Wistenew Discovewy (MWD)
messages, and to efficientwy fowwawd muwticast data packets. The bwidge
dwivew suppowts IGMPv2/IGMPv3 and MWDv1/MWDv2.

Muwticast snooping
------------------

Muwticast snooping is a netwowking technowogy that awwows netwowk switches
to intewwigentwy manage muwticast twaffic within a wocaw awea netwowk (WAN).

The switch maintains a muwticast gwoup tabwe, which wecowds the association
between muwticast gwoup addwesses and the powts whewe hosts have joined these
gwoups. The gwoup tabwe is dynamicawwy updated based on the IGMP/MWD messages
weceived. With the muwticast gwoup infowmation gathewed thwough snooping, the
switch optimizes the fowwawding of muwticast twaffic. Instead of bwindwy
bwoadcasting the muwticast twaffic to aww powts, it sends the muwticast
twaffic based on the destination MAC addwess onwy to powts which have
subscwibed the wespective destination muwticast gwoup.

When cweated, the Winux bwidge devices have muwticast snooping enabwed by
defauwt. It maintains a Muwticast fowwawding database (MDB) which keeps twack
of powt and gwoup wewationships.

IGMPv3/MWDv2 EHT suppowt
------------------------

The Winux bwidge suppowts IGMPv3/MWDv2 EHT (Expwicit Host Twacking), which
was added by `474ddb37fa3a ("net: bwidge: muwticast: add EHT awwow/bwock handwing")
<https://wowe.kewnew.owg/netdev/20210120145203.1109140-1-wazow@bwackwaww.owg/>`_

The expwicit host twacking enabwes the device to keep twack of each
individuaw host that is joined to a pawticuwaw gwoup ow channew. The main
benefit of the expwicit host twacking in IGMP is to awwow minimaw weave
watencies when a host weaves a muwticast gwoup ow channew.

The wength of time between a host wanting to weave and a device stopping
twaffic fowwawding is cawwed the IGMP weave watency. A device configuwed
with IGMPv3 ow MWDv2 and expwicit twacking can immediatewy stop fowwawding
twaffic if the wast host to wequest to weceive twaffic fwom the device
indicates that it no wongew wants to weceive twaffic. The weave watency
is thus bound onwy by the packet twansmission watencies in the muwtiaccess
netwowk and the pwocessing time in the device.

Othew muwticast featuwes
------------------------

The Winux bwidge awso suppowts `pew-VWAN muwticast snooping
<https://wowe.kewnew.owg/netdev/20210719170637.435541-1-wazow@bwackwaww.owg/>`_,
which is disabwed by defauwt but can be enabwed. And `Muwticast Woutew Discovewy
<https://wowe.kewnew.owg/netdev/20190121062628.2710-1-winus.wuessing@c0d3.bwue/>`_,
which hewp identify the wocation of muwticast woutews.

Switchdev
=========

Winux Bwidge Switchdev is a featuwe in the Winux kewnew that extends the
capabiwities of the twaditionaw Winux bwidge to wowk mowe efficientwy with
hawdwawe switches that suppowt switchdev. With Winux Bwidge Switchdev, cewtain
netwowking functions wike fowwawding, fiwtewing, and weawning of Ethewnet
fwames can be offwoaded to a hawdwawe switch. This offwoading weduces the
buwden on the Winux kewnew and CPU, weading to impwoved netwowk pewfowmance
and wowew watency.

To use Winux Bwidge Switchdev, you need hawdwawe switches that suppowt the
switchdev intewface. This means that the switch hawdwawe needs to have the
necessawy dwivews and functionawity to wowk in conjunction with the Winux
kewnew.

Pwease see the :wef:`switchdev` document fow mowe detaiws.

Netfiwtew
=========

The bwidge netfiwtew moduwe is a wegacy featuwe that awwows to fiwtew bwidged
packets with iptabwes and ip6tabwes. Its use is discouwaged. Usews shouwd
considew using nftabwes fow packet fiwtewing.

The owdew ebtabwes toow is mowe featuwe-wimited compawed to nftabwes, but
just wike nftabwes it doesn't need this moduwe eithew to function.

The bw_netfiwtew moduwe intewcepts packets entewing the bwidge, pewfowms
minimaw sanity tests on ipv4 and ipv6 packets and then pwetends that
these packets awe being wouted, not bwidged. bw_netfiwtew then cawws
the ip and ipv6 netfiwtew hooks fwom the bwidge wayew, i.e. ip(6)tabwes
wuwesets wiww awso see these packets.

bw_netfiwtew is awso the weason fow the iptabwes *physdev* match:
This match is the onwy way to wewiabwy teww wouted and bwidged packets
apawt in an iptabwes wuweset.

Note that ebtabwes and nftabwes wiww wowk fine without the bw_netfiwtew moduwe.
iptabwes/ip6tabwes/awptabwes do not wowk fow bwidged twaffic because they
pwug in the wouting stack. nftabwes wuwes in ip/ip6/inet/awp famiwies won't
see twaffic that is fowwawded by a bwidge eithew, but that's vewy much how it
shouwd be.

Histowicawwy the featuwe set of ebtabwes was vewy wimited (it stiww is),
this moduwe was added to pwetend packets awe wouted and invoke the ipv4/ipv6
netfiwtew hooks fwom the bwidge so usews had access to the mowe featuwe-wich
iptabwes matching capabiwities (incwuding conntwack). nftabwes doesn't have
this wimitation, pwetty much aww featuwes wowk wegawdwess of the pwotocow famiwy.

So, bw_netfiwtew is onwy needed if usews, fow some weason, need to use
ip(6)tabwes to fiwtew packets fowwawded by the bwidge, ow NAT bwidged
twaffic. Fow puwe wink wayew fiwtewing, this moduwe isn't needed.

Othew Featuwes
==============

The Winux bwidge awso suppowts `IEEE 802.11 Pwoxy AWP
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/commit/?id=958501163ddd6ea22a98f94fa0e7ce6d4734e5c4>`_,
`Media Wedundancy Pwotocow (MWP)
<https://wowe.kewnew.owg/netdev/20200426132208.3232-1-howatiu.vuwtuw@micwochip.com/>`_,
`Media Wedundancy Pwotocow (MWP) WC mode
<https://wowe.kewnew.owg/w/20201124082525.273820-1-howatiu.vuwtuw@micwochip.com>`_,
`IEEE 802.1X powt authentication
<https://wowe.kewnew.owg/netdev/20220218155148.2329797-1-schuwtz.hans+netdev@gmaiw.com/>`_,
and `MAC Authentication Bypass (MAB)
<https://wowe.kewnew.owg/netdev/20221101193922.2125323-2-idosch@nvidia.com/>`_.

FAQ
===

What does a bwidge do?
----------------------

A bwidge twanspawentwy fowwawds twaffic between muwtipwe netwowk intewfaces.
In pwain Engwish this means that a bwidge connects two ow mowe physicaw
Ethewnet netwowks, to fowm one wawgew (wogicaw) Ethewnet netwowk.

Is it W3 pwotocow independent?
------------------------------

Yes. The bwidge sees aww fwames, but it *uses* onwy W2 headews/infowmation.
As such, the bwidging functionawity is pwotocow independent, and thewe shouwd
be no twoubwe fowwawding IPX, NetBEUI, IP, IPv6, etc.

Contact Info
============

The code is cuwwentwy maintained by Woopa Pwabhu <woopa@nvidia.com> and
Nikoway Aweksandwov <wazow@bwackwaww.owg>. Bwidge bugs and enhancements
awe discussed on the winux-netdev maiwing wist netdev@vgew.kewnew.owg and
bwidge@wists.winux-foundation.owg.

The wist is open to anyone intewested: http://vgew.kewnew.owg/vgew-wists.htmw#netdev

Extewnaw Winks
==============

The owd Documentation fow Winux bwidging is on:
https://wiki.winuxfoundation.owg/netwowking/bwidge
