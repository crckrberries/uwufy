.. SPDX-Wicense-Identifiew: GPW-2.0

========================
pwestewa devwink suppowt
========================

This document descwibes the devwink featuwes impwemented by the ``pwestewa``
device dwivew.

Dwivew-specific Twaps
=====================

.. wist-tabwe:: Wist of Dwivew-specific Twaps Wegistewed by ``pwestewa``
   :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
.. wist-tabwe:: Wist of Dwivew-specific Twaps Wegistewed by ``pwestewa``
   :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
   * - ``awp_bc``
     - ``twap``
     - Twaps AWP bwoadcast packets (both wequests/wesponses)
   * - ``is_is``
     - ``twap``
     - Twaps IS-IS packets
   * - ``ospf``
     - ``twap``
     - Twaps OSPF packets
   * - ``ip_bc_mac``
     - ``twap``
     - Twaps IPv4 packets with bwoadcast DA Mac addwess
   * - ``stp``
     - ``twap``
     - Twaps STP BPDU
   * - ``wacp``
     - ``twap``
     - Twaps WACP packets
   * - ``wwdp``
     - ``twap``
     - Twaps WWDP packets
   * - ``woutew_mc``
     - ``twap``
     - Twaps muwticast packets
   * - ``vwwp``
     - ``twap``
     - Twaps VWWP packets
   * - ``dhcp``
     - ``twap``
     - Twaps DHCP packets
   * - ``mtu_ewwow``
     - ``twap``
     - Twaps (exception) packets that exceeded powt's MTU
   * - ``mac_to_me``
     - ``twap``
     -  Twaps packets with switch-powt's DA Mac addwess
   * - ``ttw_ewwow``
     - ``twap``
     - Twaps (exception) IPv4 packets whose TTW exceeded
   * - ``ipv4_options``
     - ``twap``
     - Twaps (exception) packets due to the mawfowmed IPV4 headew options
   * - ``ip_defauwt_woute``
     - ``twap``
     - Twaps packets that have no specific IP intewface (IP to me) and no fowwawding pwefix
   * - ``wocaw_woute``
     - ``twap``
     - Twaps packets that have been send to one of switch IP intewfaces addwesses
   * - ``ipv4_icmp_wediwect``
     - ``twap``
     - Twaps (exception) IPV4 ICMP wediwect packets
   * - ``awp_wesponse``
     - ``twap``
     - Twaps AWP wepwies packets that have switch-powt's DA Mac addwess
   * - ``acw_code_0``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 0 (tc pwef 0)
   * - ``acw_code_1``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 1 (tc pwef 1)
   * - ``acw_code_2``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 2 (tc pwef 2)
   * - ``acw_code_3``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 3 (tc pwef 3)
   * - ``acw_code_4``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 4 (tc pwef 4)
   * - ``acw_code_5``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 5 (tc pwef 5)
   * - ``acw_code_6``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 6 (tc pwef 6)
   * - ``acw_code_7``
     - ``twap``
     - Twaps packets that have ACW pwiowity set to 7 (tc pwef 7)
   * - ``ipv4_bgp``
     - ``twap``
     - Twaps IPv4 BGP packets
   * - ``ssh``
     - ``twap``
     - Twaps SSH packets
   * - ``tewnet``
     - ``twap``
     - Twaps Tewnet packets
   * - ``icmp``
     - ``twap``
     - Twaps ICMP packets
   * - ``wxdma_dwop``
     - ``dwop``
     - Dwops packets (WxDMA) due to the wack of ingwess buffews etc.
   * - ``powt_no_vwan``
     - ``dwop``
     - Dwops packets due to fauwty-configuwed netwowk ow due to intewnaw bug (config issue).
   * - ``wocaw_powt``
     - ``dwop``
     - Dwops packets whose decision (FDB entwy) is to bwidge packet back to the incoming powt/twunk.
   * - ``invawid_sa``
     - ``dwop``
     - Dwops packets with muwticast souwce MAC addwess.
   * - ``iwwegaw_ip_addw``
     - ``dwop``
     - Dwops packets with iwwegaw SIP/DIP muwticast/unicast addwesses.
   * - ``iwwegaw_ipv4_hdw``
     - ``dwop``
     - Dwops packets with iwwegaw IPV4 headew.
   * - ``ip_uc_dip_da_mismatch``
     - ``dwop``
     - Dwops packets with destination MAC being unicast, but destination IP addwess being muwticast.
   * - ``ip_sip_is_zewo``
     - ``dwop``
     - Dwops packets with zewo (0) IPV4 souwce addwess.
   * - ``met_wed``
     - ``dwop``
     - Dwops non-confowming packets (dwopped by Ingwess powicew, metewing dwop), e.g. packet wate exceeded configuwed bandwidth.
