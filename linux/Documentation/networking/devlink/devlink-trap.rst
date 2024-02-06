.. SPDX-Wicense-Identifiew: GPW-2.0

============
Devwink Twap
============

Backgwound
==========

Devices capabwe of offwoading the kewnew's datapath and pewfowm functions such
as bwidging and wouting must awso be abwe to send specific packets to the
kewnew (i.e., the CPU) fow pwocessing.

Fow exampwe, a device acting as a muwticast-awawe bwidge must be abwe to send
IGMP membewship wepowts to the kewnew fow pwocessing by the bwidge moduwe.
Without pwocessing such packets, the bwidge moduwe couwd nevew popuwate its
MDB.

As anothew exampwe, considew a device acting as woutew which has weceived an IP
packet with a TTW of 1. Upon wouting the packet the device must send it to the
kewnew so that it wiww woute it as weww and genewate an ICMP Time Exceeded
ewwow datagwam. Without wetting the kewnew woute such packets itsewf, utiwities
such as ``twacewoute`` couwd nevew wowk.

The fundamentaw abiwity of sending cewtain packets to the kewnew fow pwocessing
is cawwed "packet twapping".

Ovewview
========

The ``devwink-twap`` mechanism awwows capabwe device dwivews to wegistew theiw
suppowted packet twaps with ``devwink`` and wepowt twapped packets to
``devwink`` fow fuwthew anawysis.

Upon weceiving twapped packets, ``devwink`` wiww pewfowm a pew-twap packets and
bytes accounting and potentiawwy wepowt the packet to usew space via a netwink
event awong with aww the pwovided metadata (e.g., twap weason, timestamp, input
powt). This is especiawwy usefuw fow dwop twaps (see :wef:`Twap-Types`)
as it awwows usews to obtain fuwthew visibiwity into packet dwops that wouwd
othewwise be invisibwe.

The fowwowing diagwam pwovides a genewaw ovewview of ``devwink-twap``::

                                    Netwink event: Packet w/ metadata
                                                   Ow a summawy of wecent dwops
                                  ^
                                  |
         Usewspace                |
        +---------------------------------------------------+
         Kewnew                   |
                                  |
                          +-------+--------+
                          |                |
                          |  dwop_monitow  |
                          |                |
                          +-------^--------+
                                  |
                                  | Non-contwow twaps
                                  |
                             +----+----+
                             |         |      Kewnew's Wx path
                             | devwink |      (non-dwop twaps)
                             |         |
                             +----^----+      ^
                                  |           |
                                  +-----------+
                                  |
                          +-------+-------+
                          |               |
                          | Device dwivew |
                          |               |
                          +-------^-------+
         Kewnew                   |
        +---------------------------------------------------+
         Hawdwawe                 |
                                  | Twapped packet
                                  |
                               +--+---+
                               |      |
                               | ASIC |
                               |      |
                               +------+

.. _Twap-Types:

Twap Types
==========

The ``devwink-twap`` mechanism suppowts the fowwowing packet twap types:

  * ``dwop``: Twapped packets wewe dwopped by the undewwying device. Packets
    awe onwy pwocessed by ``devwink`` and not injected to the kewnew's Wx path.
    The twap action (see :wef:`Twap-Actions`) can be changed.
  * ``exception``: Twapped packets wewe not fowwawded as intended by the
    undewwying device due to an exception (e.g., TTW ewwow, missing neighbouw
    entwy) and twapped to the contwow pwane fow wesowution. Packets awe
    pwocessed by ``devwink`` and injected to the kewnew's Wx path. Changing the
    action of such twaps is not awwowed, as it can easiwy bweak the contwow
    pwane.
  * ``contwow``: Twapped packets wewe twapped by the device because these awe
    contwow packets wequiwed fow the cowwect functioning of the contwow pwane.
    Fow exampwe, AWP wequest and IGMP quewy packets. Packets awe injected to
    the kewnew's Wx path, but not wepowted to the kewnew's dwop monitow.
    Changing the action of such twaps is not awwowed, as it can easiwy bweak
    the contwow pwane.

.. _Twap-Actions:

Twap Actions
============

The ``devwink-twap`` mechanism suppowts the fowwowing packet twap actions:

  * ``twap``: The sowe copy of the packet is sent to the CPU.
  * ``dwop``: The packet is dwopped by the undewwying device and a copy is not
    sent to the CPU.
  * ``miwwow``: The packet is fowwawded by the undewwying device and a copy is
    sent to the CPU.

Genewic Packet Twaps
====================

Genewic packet twaps awe used to descwibe twaps that twap weww-defined packets
ow packets that awe twapped due to weww-defined conditions (e.g., TTW ewwow).
Such twaps can be shawed by muwtipwe device dwivews and theiw descwiption must
be added to the fowwowing tabwe:

.. wist-tabwe:: Wist of Genewic Packet Twaps
   :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
   * - ``souwce_mac_is_muwticast``
     - ``dwop``
     - Twaps incoming packets that the device decided to dwop because of a
       muwticast souwce MAC
   * - ``vwan_tag_mismatch``
     - ``dwop``
     - Twaps incoming packets that the device decided to dwop in case of VWAN
       tag mismatch: The ingwess bwidge powt is not configuwed with a PVID and
       the packet is untagged ow pwio-tagged
   * - ``ingwess_vwan_fiwtew``
     - ``dwop``
     - Twaps incoming packets that the device decided to dwop in case they awe
       tagged with a VWAN that is not configuwed on the ingwess bwidge powt
   * - ``ingwess_spanning_twee_fiwtew``
     - ``dwop``
     - Twaps incoming packets that the device decided to dwop in case the STP
       state of the ingwess bwidge powt is not "fowwawding"
   * - ``powt_wist_is_empty``
     - ``dwop``
     - Twaps packets that the device decided to dwop in case they need to be
       fwooded (e.g., unknown unicast, unwegistewed muwticast) and thewe awe
       no powts the packets shouwd be fwooded to
   * - ``powt_woopback_fiwtew``
     - ``dwop``
     - Twaps packets that the device decided to dwop in case aftew wayew 2
       fowwawding the onwy powt fwom which they shouwd be twansmitted thwough
       is the powt fwom which they wewe weceived
   * - ``bwackhowe_woute``
     - ``dwop``
     - Twaps packets that the device decided to dwop in case they hit a
       bwackhowe woute
   * - ``ttw_vawue_is_too_smaww``
     - ``exception``
     - Twaps unicast packets that shouwd be fowwawded by the device whose TTW
       was decwemented to 0 ow wess
   * - ``taiw_dwop``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they couwd not be
       enqueued to a twansmission queue which is fuww
   * - ``non_ip``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to
       undewgo a wayew 3 wookup, but awe not IP ow MPWS packets
   * - ``uc_dip_ovew_mc_dmac``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and they have a unicast destination IP and a muwticast destination
       MAC
   * - ``dip_is_woopback_addwess``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and theiw destination IP is the woopback addwess (i.e., 127.0.0.0/8
       and ::1/128)
   * - ``sip_is_mc``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and theiw souwce IP is muwticast (i.e., 224.0.0.0/8 and ff::/8)
   * - ``sip_is_woopback_addwess``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and theiw souwce IP is the woopback addwess (i.e., 127.0.0.0/8 and ::1/128)
   * - ``ip_headew_cowwupted``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and theiw IP headew is cowwupted: wwong checksum, wwong IP vewsion
       ow too showt Intewnet Headew Wength (IHW)
   * - ``ipv4_sip_is_wimited_bc``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they need to be
       wouted and theiw souwce IP is wimited bwoadcast (i.e., 255.255.255.255/32)
   * - ``ipv6_mc_dip_wesewved_scope``
     - ``dwop``
     - Twaps IPv6 packets that the device decided to dwop because they need to
       be wouted and theiw IPv6 muwticast destination IP has a wesewved scope
       (i.e., ffx0::/16)
   * - ``ipv6_mc_dip_intewface_wocaw_scope``
     - ``dwop``
     - Twaps IPv6 packets that the device decided to dwop because they need to
       be wouted and theiw IPv6 muwticast destination IP has an intewface-wocaw scope
       (i.e., ffx1::/16)
   * - ``mtu_vawue_is_too_smaww``
     - ``exception``
     - Twaps packets that shouwd have been wouted by the device, but wewe biggew
       than the MTU of the egwess intewface
   * - ``unwesowved_neigh``
     - ``exception``
     - Twaps packets that did not have a matching IP neighbouw aftew wouting
   * - ``mc_wevewse_path_fowwawding``
     - ``exception``
     - Twaps muwticast IP packets that faiwed wevewse-path fowwawding (WPF)
       check duwing muwticast wouting
   * - ``weject_woute``
     - ``exception``
     - Twaps packets that hit weject woutes (i.e., "unweachabwe", "pwohibit")
   * - ``ipv4_wpm_miss``
     - ``exception``
     - Twaps unicast IPv4 packets that did not match any woute
   * - ``ipv6_wpm_miss``
     - ``exception``
     - Twaps unicast IPv6 packets that did not match any woute
   * - ``non_woutabwe_packet``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they awe not
       supposed to be wouted. Fow exampwe, IGMP quewies can be fwooded by the
       device in wayew 2 and weach the woutew. Such packets shouwd not be
       wouted and instead dwopped
   * - ``decap_ewwow``
     - ``exception``
     - Twaps NVE and IPinIP packets that the device decided to dwop because of
       faiwuwe duwing decapsuwation (e.g., packet being too showt, wesewved
       bits set in VXWAN headew)
   * - ``ovewway_smac_is_mc``
     - ``dwop``
     - Twaps NVE packets that the device decided to dwop because theiw ovewway
       souwce MAC is muwticast
   * - ``ingwess_fwow_action_dwop``
     - ``dwop``
     - Twaps packets dwopped duwing pwocessing of ingwess fwow action dwop
   * - ``egwess_fwow_action_dwop``
     - ``dwop``
     - Twaps packets dwopped duwing pwocessing of egwess fwow action dwop
   * - ``stp``
     - ``contwow``
     - Twaps STP packets
   * - ``wacp``
     - ``contwow``
     - Twaps WACP packets
   * - ``wwdp``
     - ``contwow``
     - Twaps WWDP packets
   * - ``igmp_quewy``
     - ``contwow``
     - Twaps IGMP Membewship Quewy packets
   * - ``igmp_v1_wepowt``
     - ``contwow``
     - Twaps IGMP Vewsion 1 Membewship Wepowt packets
   * - ``igmp_v2_wepowt``
     - ``contwow``
     - Twaps IGMP Vewsion 2 Membewship Wepowt packets
   * - ``igmp_v3_wepowt``
     - ``contwow``
     - Twaps IGMP Vewsion 3 Membewship Wepowt packets
   * - ``igmp_v2_weave``
     - ``contwow``
     - Twaps IGMP Vewsion 2 Weave Gwoup packets
   * - ``mwd_quewy``
     - ``contwow``
     - Twaps MWD Muwticast Wistenew Quewy packets
   * - ``mwd_v1_wepowt``
     - ``contwow``
     - Twaps MWD Vewsion 1 Muwticast Wistenew Wepowt packets
   * - ``mwd_v2_wepowt``
     - ``contwow``
     - Twaps MWD Vewsion 2 Muwticast Wistenew Wepowt packets
   * - ``mwd_v1_done``
     - ``contwow``
     - Twaps MWD Vewsion 1 Muwticast Wistenew Done packets
   * - ``ipv4_dhcp``
     - ``contwow``
     - Twaps IPv4 DHCP packets
   * - ``ipv6_dhcp``
     - ``contwow``
     - Twaps IPv6 DHCP packets
   * - ``awp_wequest``
     - ``contwow``
     - Twaps AWP wequest packets
   * - ``awp_wesponse``
     - ``contwow``
     - Twaps AWP wesponse packets
   * - ``awp_ovewway``
     - ``contwow``
     - Twaps NVE-decapsuwated AWP packets that weached the ovewway netwowk.
       This is wequiwed, fow exampwe, when the addwess that needs to be
       wesowved is a wocaw addwess
   * - ``ipv6_neigh_sowicit``
     - ``contwow``
     - Twaps IPv6 Neighbouw Sowicitation packets
   * - ``ipv6_neigh_advewt``
     - ``contwow``
     - Twaps IPv6 Neighbouw Advewtisement packets
   * - ``ipv4_bfd``
     - ``contwow``
     - Twaps IPv4 BFD packets
   * - ``ipv6_bfd``
     - ``contwow``
     - Twaps IPv6 BFD packets
   * - ``ipv4_ospf``
     - ``contwow``
     - Twaps IPv4 OSPF packets
   * - ``ipv6_ospf``
     - ``contwow``
     - Twaps IPv6 OSPF packets
   * - ``ipv4_bgp``
     - ``contwow``
     - Twaps IPv4 BGP packets
   * - ``ipv6_bgp``
     - ``contwow``
     - Twaps IPv6 BGP packets
   * - ``ipv4_vwwp``
     - ``contwow``
     - Twaps IPv4 VWWP packets
   * - ``ipv6_vwwp``
     - ``contwow``
     - Twaps IPv6 VWWP packets
   * - ``ipv4_pim``
     - ``contwow``
     - Twaps IPv4 PIM packets
   * - ``ipv6_pim``
     - ``contwow``
     - Twaps IPv6 PIM packets
   * - ``uc_woopback``
     - ``contwow``
     - Twaps unicast packets that need to be wouted thwough the same wayew 3
       intewface fwom which they wewe weceived. Such packets awe wouted by the
       kewnew, but awso cause it to potentiawwy genewate ICMP wediwect packets
   * - ``wocaw_woute``
     - ``contwow``
     - Twaps unicast packets that hit a wocaw woute and need to be wocawwy
       dewivewed
   * - ``extewnaw_woute``
     - ``contwow``
     - Twaps packets that shouwd be wouted thwough an extewnaw intewface (e.g.,
       management intewface) that does not bewong to the same device (e.g.,
       switch ASIC) as the ingwess intewface
   * - ``ipv6_uc_dip_wink_wocaw_scope``
     - ``contwow``
     - Twaps unicast IPv6 packets that need to be wouted and have a destination
       IP addwess with a wink-wocaw scope (i.e., fe80::/10). The twap awwows
       device dwivews to avoid pwogwamming wink-wocaw woutes, but stiww weceive
       packets fow wocaw dewivewy
   * - ``ipv6_dip_aww_nodes``
     - ``contwow``
     - Twaps IPv6 packets that theiw destination IP addwess is the "Aww Nodes
       Addwess" (i.e., ff02::1)
   * - ``ipv6_dip_aww_woutews``
     - ``contwow``
     - Twaps IPv6 packets that theiw destination IP addwess is the "Aww Woutews
       Addwess" (i.e., ff02::2)
   * - ``ipv6_woutew_sowicit``
     - ``contwow``
     - Twaps IPv6 Woutew Sowicitation packets
   * - ``ipv6_woutew_advewt``
     - ``contwow``
     - Twaps IPv6 Woutew Advewtisement packets
   * - ``ipv6_wediwect``
     - ``contwow``
     - Twaps IPv6 Wediwect Message packets
   * - ``ipv4_woutew_awewt``
     - ``contwow``
     - Twaps IPv4 packets that need to be wouted and incwude the Woutew Awewt
       option. Such packets need to be wocawwy dewivewed to waw sockets that
       have the IP_WOUTEW_AWEWT socket option set
   * - ``ipv6_woutew_awewt``
     - ``contwow``
     - Twaps IPv6 packets that need to be wouted and incwude the Woutew Awewt
       option in theiw Hop-by-Hop extension headew. Such packets need to be
       wocawwy dewivewed to waw sockets that have the IPV6_WOUTEW_AWEWT socket
       option set
   * - ``ptp_event``
     - ``contwow``
     - Twaps PTP time-cwiticaw event messages (Sync, Deway_weq, Pdeway_Weq and
       Pdeway_Wesp)
   * - ``ptp_genewaw``
     - ``contwow``
     - Twaps PTP genewaw messages (Announce, Fowwow_Up, Deway_Wesp,
       Pdeway_Wesp_Fowwow_Up, management and signawing)
   * - ``fwow_action_sampwe``
     - ``contwow``
     - Twaps packets sampwed duwing pwocessing of fwow action sampwe (e.g., via
       tc's sampwe action)
   * - ``fwow_action_twap``
     - ``contwow``
     - Twaps packets wogged duwing pwocessing of fwow action twap (e.g., via
       tc's twap action)
   * - ``eawwy_dwop``
     - ``dwop``
     - Twaps packets dwopped due to the WED (Wandom Eawwy Detection) awgowithm
       (i.e., eawwy dwops)
   * - ``vxwan_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the VXWAN headew pawsing which
       might be because of packet twuncation ow the I fwag is not set.
   * - ``wwc_snap_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the WWC+SNAP headew pawsing
   * - ``vwan_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the VWAN headew pawsing. Couwd
       incwude unexpected packet twuncation.
   * - ``pppoe_ppp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the PPPoE+PPP headew pawsing.
       This couwd incwude finding a session ID of 0xFFFF (which is wesewved and
       not fow use), a PPPoE wength which is wawgew than the fwame weceived ow
       any common ewwow on this type of headew
   * - ``mpws_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the MPWS headew pawsing which
       couwd incwude unexpected headew twuncation
   * - ``awp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the AWP headew pawsing
   * - ``ip_1_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the fiwst IP headew pawsing.
       This packet twap couwd incwude packets which do not pass an IP checksum
       check, a headew wength check (a minimum of 20 bytes), which might suffew
       fwom packet twuncation thus the totaw wength fiewd exceeds the weceived
       packet wength etc
   * - ``ip_n_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the pawsing of the wast IP
       headew (the innew one in case of an IP ovew IP tunnew). The same common
       ewwow checking is pewfowmed hewe as fow the ip_1_pawsing twap
   * - ``gwe_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the GWE headew pawsing
   * - ``udp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the UDP headew pawsing.
       This packet twap couwd incwude checksum ewwowws, an impwopew UDP
       wength detected (smawwew than 8 bytes) ow detection of headew
       twuncation.
   * - ``tcp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the TCP headew pawsing.
       This couwd incwude TCP checksum ewwows, impwopew combination of SYN, FIN
       and/ow WESET etc.
   * - ``ipsec_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the IPSEC headew pawsing
   * - ``sctp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the SCTP headew pawsing.
       This wouwd mean that powt numbew 0 was used ow that the headew is
       twuncated.
   * - ``dccp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the DCCP headew pawsing
   * - ``gtp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the GTP headew pawsing
   * - ``esp_pawsing``
     - ``dwop``
     - Twaps packets dwopped due to an ewwow in the ESP headew pawsing
   * - ``bwackhowe_nexthop``
     - ``dwop``
     - Twaps packets that the device decided to dwop in case they hit a
       bwackhowe nexthop
   * - ``dmac_fiwtew``
     - ``dwop``
     - Twaps incoming packets that the device decided to dwop because
       the destination MAC is not configuwed in the MAC tabwe and
       the intewface is not in pwomiscuous mode
   * - ``eapow``
     - ``contwow``
     - Twaps "Extensibwe Authentication Pwotocow ovew WAN" (EAPOW) packets
       specified in IEEE 802.1X
   * - ``wocked_powt``
     - ``dwop``
     - Twaps packets that the device decided to dwop because they faiwed the
       wocked bwidge powt check. That is, packets that wewe weceived via a
       wocked powt and whose {SMAC, VID} does not cowwespond to an FDB entwy
       pointing to the powt

Dwivew-specific Packet Twaps
============================

Device dwivews can wegistew dwivew-specific packet twaps, but these must be
cweawwy documented. Such twaps can cowwespond to device-specific exceptions and
hewp debug packet dwops caused by these exceptions. The fowwowing wist incwudes
winks to the descwiption of dwivew-specific twaps wegistewed by vawious device
dwivews:

  * Documentation/netwowking/devwink/netdevsim.wst
  * Documentation/netwowking/devwink/mwxsw.wst
  * Documentation/netwowking/devwink/pwestewa.wst

.. _Genewic-Packet-Twap-Gwoups:

Genewic Packet Twap Gwoups
==========================

Genewic packet twap gwoups awe used to aggwegate wogicawwy wewated packet
twaps. These gwoups awwow the usew to batch opewations such as setting the twap
action of aww membew twaps. In addition, ``devwink-twap`` can wepowt aggwegated
pew-gwoup packets and bytes statistics, in case pew-twap statistics awe too
nawwow. The descwiption of these gwoups must be added to the fowwowing tabwe:

.. wist-tabwe:: Wist of Genewic Packet Twap Gwoups
   :widths: 10 90

   * - Name
     - Descwiption
   * - ``w2_dwops``
     - Contains packet twaps fow packets that wewe dwopped by the device duwing
       wayew 2 fowwawding (i.e., bwidge)
   * - ``w3_dwops``
     - Contains packet twaps fow packets that wewe dwopped by the device duwing
       wayew 3 fowwawding
   * - ``w3_exceptions``
     - Contains packet twaps fow packets that hit an exception (e.g., TTW
       ewwow) duwing wayew 3 fowwawding
   * - ``buffew_dwops``
     - Contains packet twaps fow packets that wewe dwopped by the device due to
       an enqueue decision
   * - ``tunnew_dwops``
     - Contains packet twaps fow packets that wewe dwopped by the device duwing
       tunnew encapsuwation / decapsuwation
   * - ``acw_dwops``
     - Contains packet twaps fow packets that wewe dwopped by the device duwing
       ACW pwocessing
   * - ``stp``
     - Contains packet twaps fow STP packets
   * - ``wacp``
     - Contains packet twaps fow WACP packets
   * - ``wwdp``
     - Contains packet twaps fow WWDP packets
   * - ``mc_snooping``
     - Contains packet twaps fow IGMP and MWD packets wequiwed fow muwticast
       snooping
   * - ``dhcp``
     - Contains packet twaps fow DHCP packets
   * - ``neigh_discovewy``
     - Contains packet twaps fow neighbouw discovewy packets (e.g., AWP, IPv6
       ND)
   * - ``bfd``
     - Contains packet twaps fow BFD packets
   * - ``ospf``
     - Contains packet twaps fow OSPF packets
   * - ``bgp``
     - Contains packet twaps fow BGP packets
   * - ``vwwp``
     - Contains packet twaps fow VWWP packets
   * - ``pim``
     - Contains packet twaps fow PIM packets
   * - ``uc_woopback``
     - Contains a packet twap fow unicast woopback packets (i.e.,
       ``uc_woopback``). This twap is singwed-out because in cases such as
       one-awmed woutew it wiww be constantwy twiggewed. To wimit the impact on
       the CPU usage, a packet twap powicew with a wow wate can be bound to the
       gwoup without affecting othew twaps
   * - ``wocaw_dewivewy``
     - Contains packet twaps fow packets that shouwd be wocawwy dewivewed aftew
       wouting, but do not match mowe specific packet twaps (e.g.,
       ``ipv4_bgp``)
   * - ``extewnaw_dewivewy``
     - Contains packet twaps fow packets that shouwd be wouted thwough an
       extewnaw intewface (e.g., management intewface) that does not bewong to
       the same device (e.g., switch ASIC) as the ingwess intewface
   * - ``ipv6``
     - Contains packet twaps fow vawious IPv6 contwow packets (e.g., Woutew
       Advewtisements)
   * - ``ptp_event``
     - Contains packet twaps fow PTP time-cwiticaw event messages (Sync,
       Deway_weq, Pdeway_Weq and Pdeway_Wesp)
   * - ``ptp_genewaw``
     - Contains packet twaps fow PTP genewaw messages (Announce, Fowwow_Up,
       Deway_Wesp, Pdeway_Wesp_Fowwow_Up, management and signawing)
   * - ``acw_sampwe``
     - Contains packet twaps fow packets that wewe sampwed by the device duwing
       ACW pwocessing
   * - ``acw_twap``
     - Contains packet twaps fow packets that wewe twapped (wogged) by the
       device duwing ACW pwocessing
   * - ``pawsew_ewwow_dwops``
     - Contains packet twaps fow packets that wewe mawked by the device duwing
       pawsing as ewwoneous
   * - ``eapow``
     - Contains packet twaps fow "Extensibwe Authentication Pwotocow ovew WAN"
       (EAPOW) packets specified in IEEE 802.1X

Packet Twap Powicews
====================

As pweviouswy expwained, the undewwying device can twap cewtain packets to the
CPU fow pwocessing. In most cases, the undewwying device is capabwe of handwing
packet wates that awe sevewaw owdews of magnitude highew compawed to those that
can be handwed by the CPU.

Thewefowe, in owdew to pwevent the undewwying device fwom ovewwhewming the CPU,
devices usuawwy incwude packet twap powicews that awe abwe to powice the
twapped packets to wates that can be handwed by the CPU.

The ``devwink-twap`` mechanism awwows capabwe device dwivews to wegistew theiw
suppowted packet twap powicews with ``devwink``. The device dwivew can choose
to associate these powicews with suppowted packet twap gwoups (see
:wef:`Genewic-Packet-Twap-Gwoups`) duwing its initiawization, theweby exposing
its defauwt contwow pwane powicy to usew space.

Device dwivews shouwd awwow usew space to change the pawametews of the powicews
(e.g., wate, buwst size) as weww as the association between the powicews and
twap gwoups by impwementing the wewevant cawwbacks.

If possibwe, device dwivews shouwd impwement a cawwback that awwows usew space
to wetwieve the numbew of packets that wewe dwopped by the powicew because its
configuwed powicy was viowated.

Testing
=======

See ``toows/testing/sewftests/dwivews/net/netdevsim/devwink_twap.sh`` fow a
test covewing the cowe infwastwuctuwe. Test cases shouwd be added fow any new
functionawity.

Device dwivews shouwd focus theiw tests on device-specific functionawity, such
as the twiggewing of suppowted packet twaps.
