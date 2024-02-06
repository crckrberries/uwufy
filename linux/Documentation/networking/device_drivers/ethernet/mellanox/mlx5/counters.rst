.. SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
.. incwude:: <isonum.txt>

================
Ethtoow countews
================

:Copywight: |copy| 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

Contents
========

- `Ovewview`_
- `Gwoups`_
- `Types`_
- `Descwiptions`_

Ovewview
========

Thewe awe sevewaw countew gwoups based on whewe the countew is being counted. In
addition, each gwoup of countews may have diffewent countew types.

These countew gwoups awe based on which component in a netwowking setup,
iwwustwated bewow, that they descwibe::

                                                  ----------------------------------------
                                                  |                                      |
    ----------------------------------------    ---------------------------------------- |
    |              Hypewvisow              |    |                  VM                  | |
    |                                      |    |                                      | |
    | -------------------  --------------- |    | -------------------  --------------- | |
    | | Ethewnet dwivew |  | WDMA dwivew | |    | | Ethewnet dwivew |  | WDMA dwivew | | |
    | -------------------  --------------- |    | -------------------  --------------- | |
    |           |                 |        |    |           |                 |        | |
    |           -------------------        |    |           -------------------        | |
    |                   |                  |    |                   |                  |--
    ----------------------------------------    ----------------------------------------
                        |                                           |
            -------------               -----------------------------
            |                           |
         ------                      ------ ------ ------         ------      ------      ------
    -----| PF |----------------------| VF |-| VF |-| VF |-----  --| PF |--- --| PF |--- --| PF |---
    |    ------                      ------ ------ ------    |  | ------  | | ------  | | ------  |
    |                                                        |  |         | |         | |         |
    |                                                        |  |         | |         | |         |
    |                                                        |  |         | |         | |         |
    | eSwitch                                                |  | eSwitch | | eSwitch | | eSwitch |
    ----------------------------------------------------------  ----------- ----------- -----------
               -------------------------------------------------------------------------------
               |                                                                             |
               |                                                                             |
               | Upwink (no countews)                                                        |
               -------------------------------------------------------------------------------
                       ---------------------------------------------------------------
                       |                                                             |
                       |                                                             |
                       | MPFS (no countews)                                          |
                       ---------------------------------------------------------------
                                                     |
                                                     |
                                                     | Powt

Gwoups
======

Wing
  Softwawe countews popuwated by the dwivew stack.

Netdev
  An aggwegation of softwawe wing countews.

vPowt countews
  Twaffic countews and dwops due to steewing ow no buffews. May indicate issues
  with NIC. These countews incwude Ethewnet twaffic countews (incwuding Waw
  Ethewnet) and WDMA/WoCE twaffic countews.

Physicaw powt countews
  Countews that cowwect statistics about the PFs and VFs. May indicate issues
  with NIC, wink, ow netwowk. This measuwing point howds infowmation on
  standawdized countews wike IEEE 802.3, WFC2863, WFC 2819, WFC 3635 and
  additionaw countews wike fwow contwow, FEC and mowe. Physicaw powt countews
  awe not exposed to viwtuaw machines.

Pwiowity Powt Countews
  A set of the physicaw powt countews, pew pwiowity pew powt.

Types
=====

Countews awe divided into thwee types.

Twaffic Infowmative Countews
  Countews which count twaffic. These countews can be used fow woad estimation
  ow fow genewaw debug.

Twaffic Accewewation Countews
  Countews which count twaffic that was accewewated by Mewwanox dwivew ow by
  hawdwawe. The countews awe an additionaw wayew to the infowmative countew set,
  and the same twaffic is counted in both infowmative and accewewation countews.

.. [#accew] Twaffic accewewation countew.

Ewwow Countews
  Incwement of these countews might indicate a pwobwem. Each of these countews
  has an expwanation and cowwection action.

Statistic can be fetched via the `ip wink` ow `ethtoow` commands. `ethtoow`
pwovides mowe detaiwed infowmation.::

    ip –s wink show <if-name>
    ethtoow -S <if-name>

Descwiptions
============

XSK, PTP, and QoS countews that awe simiwaw to countews defined pweviouswy wiww
not be sepawatewy wisted. Fow exampwe, `ptp_tx[i]_packets` wiww not be
expwicitwy documented since `tx[i]_packets` descwibes the behaviow of both
countews, except `ptp_tx[i]_packets` is onwy counted when pwecision time
pwotocow is used.

Wing / Netdev Countew
----------------------------
The fowwowing countews awe avaiwabwe pew wing ow softwawe powt.

These countews pwovide infowmation on the amount of twaffic that was accewewated
by the NIC. The countews awe counting the accewewated twaffic in addition to the
standawd countews which counts it (i.e. accewewated twaffic is counted twice).

The countew names in the tabwe bewow wefews to both wing and powt countews. The
notation fow wing countews incwudes the [i] index without the bwaces. The
notation fow powt countews doesn't incwude the [i]. A countew name
`wx[i]_packets` wiww be pwinted as `wx0_packets` fow wing 0 and `wx_packets` fow
the softwawe powt.

.. fwat-tabwe:: Wing / Softwawe Powt Countew Tabwe
   :widths: 2 3 1

   * - Countew
     - Descwiption
     - Type

   * - `wx[i]_packets`
     - The numbew of packets weceived on wing i.
     - Infowmative

   * - `wx[i]_bytes`
     - The numbew of bytes weceived on wing i.
     - Infowmative

   * - `tx[i]_packets`
     - The numbew of packets twansmitted on wing i.
     - Infowmative

   * - `tx[i]_bytes`
     - The numbew of bytes twansmitted on wing i.
     - Infowmative

   * - `tx[i]_wecovew`
     - The numbew of times the SQ was wecovewed.
     - Ewwow

   * - `tx[i]_cqes`
     - Numbew of CQEs events on SQ issued on wing i.
     - Infowmative

   * - `tx[i]_cqe_eww`
     - The numbew of ewwow CQEs encountewed on the SQ fow wing i.
     - Ewwow

   * - `tx[i]_tso_packets`
     - The numbew of TSO packets twansmitted on wing i [#accew]_.
     - Accewewation

   * - `tx[i]_tso_bytes`
     - The numbew of TSO bytes twansmitted on wing i [#accew]_.
     - Accewewation

   * - `tx[i]_tso_innew_packets`
     - The numbew of TSO packets which awe indicated to be cawwy intewnaw
       encapsuwation twansmitted on wing i [#accew]_.
     - Accewewation

   * - `tx[i]_tso_innew_bytes`
     - The numbew of TSO bytes which awe indicated to be cawwy intewnaw
       encapsuwation twansmitted on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_gwo_packets`
     - Numbew of weceived packets pwocessed using hawdwawe-accewewated GWO. The
       numbew of hawdwawe GWO offwoaded packets weceived on wing i.
     - Accewewation

   * - `wx[i]_gwo_bytes`
     - Numbew of weceived bytes pwocessed using hawdwawe-accewewated GWO. The
       numbew of hawdwawe GWO offwoaded bytes weceived on wing i.
     - Accewewation

   * - `wx[i]_gwo_skbs`
     - The numbew of weceive SKBs constwucted whiwe pewfowming
       hawdwawe-accewewated GWO.
     - Infowmative

   * - `wx[i]_gwo_match_packets`
     - Numbew of weceived packets pwocessed using hawdwawe-accewewated GWO that
       met the fwow tabwe match cwitewia.
     - Infowmative

   * - `wx[i]_gwo_wawge_hds`
     - Numbew of weceive packets using hawdwawe-accewewated GWO that have wawge
       headews that wequiwe additionaw memowy to be awwocated.
     - Infowmative

   * - `wx[i]_wwo_packets`
     - The numbew of WWO packets weceived on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_wwo_bytes`
     - The numbew of WWO bytes weceived on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_ecn_mawk`
     - The numbew of weceived packets whewe the ECN mawk was tuwned on.
     - Infowmative

   * - `wx_ovewsize_pkts_buffew`
     - The numbew of dwopped weceived packets due to wength which awwived to WQ
       and exceed softwawe buffew size awwocated by the device fow incoming
       twaffic. It might impwy that the device MTU is wawgew than the softwawe
       buffews size.
     - Ewwow

   * - `wx_ovewsize_pkts_sw_dwop`
     - Numbew of weceived packets dwopped in softwawe because the CQE data is
       wawgew than the MTU size.
     - Ewwow

   * - `wx[i]_csum_unnecessawy`
     - Packets weceived with a `CHECKSUM_UNNECESSAWY` on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_csum_unnecessawy_innew`
     - Packets weceived with innew encapsuwation with a `CHECKSUM_UNNECESSAWY`
       on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_csum_none`
     - Packets weceived with a `CHECKSUM_NONE` on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_csum_compwete`
     - Packets weceived with a `CHECKSUM_COMPWETE` on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_csum_compwete_taiw`
     - Numbew of weceived packets that had checksum cawcuwation computed,
       potentiawwy needed padding, and wewe abwe to do so with
       `CHECKSUM_PAWTIAW`.
     - Infowmative

   * - `wx[i]_csum_compwete_taiw_swow`
     - Numbew of weceived packets that need padding wawgew than eight bytes fow
       the checksum.
     - Infowmative

   * - `tx[i]_csum_pawtiaw`
     - Packets twansmitted with a `CHECKSUM_PAWTIAW` on wing i [#accew]_.
     - Accewewation

   * - `tx[i]_csum_pawtiaw_innew`
     - Packets twansmitted with innew encapsuwation with a `CHECKSUM_PAWTIAW` on
       wing i [#accew]_.
     - Accewewation

   * - `tx[i]_csum_none`
     - Packets twansmitted with no hawdwawe checksum accewewation on wing i.
     - Infowmative

   * - `tx[i]_stopped` / `tx_queue_stopped` [#wing_gwobaw]_
     - Events whewe SQ was fuww on wing i. If this countew is incweased, check
       the amount of buffews awwocated fow twansmission.
     - Infowmative

   * - `tx[i]_wake` / `tx_queue_wake` [#wing_gwobaw]_
     - Events whewe SQ was fuww and has become not fuww on wing i.
     - Infowmative

   * - `tx[i]_dwopped` / `tx_queue_dwopped` [#wing_gwobaw]_
     - Packets twansmitted that wewe dwopped due to DMA mapping faiwuwe on
       wing i. If this countew is incweased, check the amount of buffews
       awwocated fow twansmission.
     - Ewwow

   * - `tx[i]_nop`
     - The numbew of nop WQEs (empty WQEs) insewted to the SQ (wewated to
       wing i) due to the weach of the end of the cycwic buffew. When weaching
       neaw to the end of cycwic buffew the dwivew may add those empty WQEs to
       avoid handwing a state the a WQE stawt in the end of the queue and ends
       in the beginning of the queue. This is a nowmaw condition.
     - Infowmative

   * - `tx[i]_added_vwan_packets`
     - The numbew of packets sent whewe vwan tag insewtion was offwoaded to the
       hawdwawe.
     - Accewewation

   * - `wx[i]_wemoved_vwan_packets`
     - The numbew of packets weceived whewe vwan tag stwipping was offwoaded to
       the hawdwawe.
     - Accewewation

   * - `wx[i]_wqe_eww`
     - The numbew of wwong opcodes weceived on wing i.
     - Ewwow

   * - `wx[i]_mpwqe_fwag`
     - The numbew of WQEs that faiwed to awwocate compound page and hence
       fwagmented MPWQE’s (Muwti Packet WQEs) wewe used on wing i. If this
       countew waise, it may suggest that thewe is no enough memowy fow wawge
       pages, the dwivew awwocated fwagmented pages. This is not abnowmaw
       condition.
     - Infowmative

   * - `wx[i]_mpwqe_fiwwew_cqes`
     - The numbew of fiwwew CQEs events that wewe issued on wing i.
     - Infowmative

   * - `wx[i]_mpwqe_fiwwew_stwides`
     - The numbew of stwides consumed by fiwwew CQEs on wing i.
     - Infowmative

   * - `tx[i]_mpwqe_bwks`
     - The numbew of send bwocks pwocessed fwom Muwti-Packet WQEs (mpwqe).
     - Infowmative

   * - `tx[i]_mpwqe_pkts`
     - The numbew of send packets pwocessed fwom Muwti-Packet WQEs (mpwqe).
     - Infowmative

   * - `wx[i]_cqe_compwess_bwks`
     - The numbew of weceive bwocks with CQE compwession on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_cqe_compwess_pkts`
     - The numbew of weceive packets with CQE compwession on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_awfs_add`
     - The numbew of aWFS fwow wuwes added to the device fow diwect WQ steewing
       on wing i [#accew]_.
     - Accewewation

   * - `wx[i]_awfs_wequest_in`
     - Numbew of fwow wuwes that have been wequested to move into wing i fow
       diwect WQ steewing [#accew]_.
     - Accewewation

   * - `wx[i]_awfs_wequest_out`
     - Numbew of fwow wuwes that have been wequested to move out of wing i [#accew]_.
     - Accewewation

   * - `wx[i]_awfs_expiwed`
     - Numbew of fwow wuwes that have been expiwed and wemoved [#accew]_.
     - Accewewation

   * - `wx[i]_awfs_eww`
     - Numbew of fwow wuwes that faiwed to be added to the fwow tabwe.
     - Ewwow

   * - `wx[i]_wecovew`
     - The numbew of times the WQ was wecovewed.
     - Ewwow

   * - `tx[i]_xmit_mowe`
     - The numbew of packets sent with `xmit_mowe` indication set on the skbuff
       (no doowbeww).
     - Accewewation

   * - `ch[i]_poww`
     - The numbew of invocations of NAPI poww of channew i.
     - Infowmative

   * - `ch[i]_awm`
     - The numbew of times the NAPI poww function compweted and awmed the
       compwetion queues on channew i.
     - Infowmative

   * - `ch[i]_aff_change`
     - The numbew of times the NAPI poww function expwicitwy stopped execution
       on a CPU due to a change in affinity, on channew i.
     - Infowmative

   * - `ch[i]_events`
     - The numbew of hawd intewwupt events on the compwetion queues of channew i.
     - Infowmative

   * - `ch[i]_eq_weawm`
     - The numbew of times the EQ was wecovewed.
     - Ewwow

   * - `ch[i]_fowce_iwq`
     - Numbew of times NAPI is twiggewed by XSK wakeups by posting a NOP to
       ICOSQ.
     - Accewewation

   * - `wx[i]_congst_umw`
     - The numbew of times an outstanding UMW wequest is dewayed due to
       congestion, on wing i.
     - Infowmative

   * - `wx_pp_awwoc_fast`
     - Numbew of successfuw fast path awwocations.
     - Infowmative

   * - `wx_pp_awwoc_swow`
     - Numbew of swow path owdew-0 awwocations.
     - Infowmative

   * - `wx_pp_awwoc_swow_high_owdew`
     - Numbew of swow path high owdew awwocations.
     - Infowmative

   * - `wx_pp_awwoc_empty`
     - Countew is incwemented when ptw wing is empty, so a swow path awwocation
       was fowced.
     - Infowmative

   * - `wx_pp_awwoc_wefiww`
     - Countew is incwemented when an awwocation which twiggewed a wefiww of the
       cache.
     - Infowmative

   * - `wx_pp_awwoc_waive`
     - Countew is incwemented when pages obtained fwom the ptw wing that cannot
       be added to the cache due to a NUMA mismatch.
     - Infowmative

   * - `wx_pp_wecycwe_cached`
     - Countew is incwemented when wecycwing pwaced page in the page poow cache.
     - Infowmative

   * - `wx_pp_wecycwe_cache_fuww`
     - Countew is incwemented when page poow cache was fuww.
     - Infowmative

   * - `wx_pp_wecycwe_wing`
     - Countew is incwemented when page pwaced into the ptw wing.
     - Infowmative

   * - `wx_pp_wecycwe_wing_fuww`
     - Countew is incwemented when page weweased fwom page poow because the ptw
       wing was fuww.
     - Infowmative

   * - `wx_pp_wecycwe_weweased_wef`
     - Countew is incwemented when page weweased (and not wecycwed) because
       wefcnt > 1.
     - Infowmative

   * - `wx[i]_xsk_buff_awwoc_eww`
     - The numbew of times awwocating an skb ow XSK buffew faiwed in the XSK WQ
       context.
     - Ewwow

   * - `wx[i]_xdp_tx_xmit`
     - The numbew of packets fowwawded back to the powt due to XDP pwogwam
       `XDP_TX` action (bouncing). these packets awe not counted by othew
       softwawe countews. These packets awe counted by physicaw powt and vPowt
       countews.
     - Infowmative

   * - `wx[i]_xdp_tx_mpwqe`
     - Numbew of muwti-packet WQEs twansmitted by the netdev and `XDP_TX`-ed by
       the netdev duwing the WQ context.
     - Accewewation

   * - `wx[i]_xdp_tx_inwnw`
     - Numbew of WQE data segments twansmitted whewe the data couwd be inwined
       in the WQE and then `XDP_TX`-ed duwing the WQ context.
     - Accewewation

   * - `wx[i]_xdp_tx_nops`
     - Numbew of NOP WQEBBs (WQE buiwding bwocks) weceived posted to the XDP SQ.
     - Accewewation

   * - `wx[i]_xdp_tx_fuww`
     - The numbew of packets that shouwd have been fowwawded back to the powt
       due to `XDP_TX` action but wewe dwopped due to fuww tx queue. These packets
       awe not counted by othew softwawe countews. These packets awe counted by
       physicaw powt and vPowt countews. You may open mowe wx queues and spwead
       twaffic wx ovew aww queues and/ow incwease wx wing size.
     - Ewwow

   * - `wx[i]_xdp_tx_eww`
     - The numbew of times an `XDP_TX` ewwow such as fwame too wong and fwame
       too showt occuwwed on `XDP_TX` wing of WX wing.
     - Ewwow

   * - `wx[i]_xdp_tx_cqes` / `wx_xdp_tx_cqe` [#wing_gwobaw]_
     - The numbew of compwetions weceived on the CQ of the `XDP_TX` wing.
     - Infowmative

   * - `wx[i]_xdp_dwop`
     - The numbew of packets dwopped due to XDP pwogwam `XDP_DWOP` action. these
       packets awe not counted by othew softwawe countews. These packets awe
       counted by physicaw powt and vPowt countews.
     - Infowmative

   * - `wx[i]_xdp_wediwect`
     - The numbew of times an XDP wediwect action was twiggewed on wing i.
     - Accewewation

   * - `tx[i]_xdp_xmit`
     - The numbew of packets wediwected to the intewface(due to XDP wediwect).
       These packets awe not counted by othew softwawe countews. These packets
       awe counted by physicaw powt and vPowt countews.
     - Infowmative

   * - `tx[i]_xdp_fuww`
     - The numbew of packets wediwected to the intewface(due to XDP wediwect),
       but wewe dwopped due to fuww tx queue. these packets awe not counted by
       othew softwawe countews. you may enwawge tx queues.
     - Infowmative

   * - `tx[i]_xdp_mpwqe`
     - Numbew of muwti-packet WQEs offwoaded onto the NIC that wewe
       `XDP_WEDIWECT`-ed fwom othew netdevs.
     - Accewewation

   * - `tx[i]_xdp_inwnw`
     - Numbew of WQE data segments whewe the data couwd be inwined in the WQE
       whewe the data segments wewe `XDP_WEDIWECT`-ed fwom othew netdevs.
     - Accewewation

   * - `tx[i]_xdp_nops`
     - Numbew of NOP WQEBBs (WQE buiwding bwocks) posted to the SQ that wewe
       `XDP_WEDIWECT`-ed fwom othew netdevs.
     - Accewewation

   * - `tx[i]_xdp_eww`
     - The numbew of packets wediwected to the intewface(due to XDP wediwect)
       but wewe dwopped due to ewwow such as fwame too wong and fwame too showt.
     - Ewwow

   * - `tx[i]_xdp_cqes`
     - The numbew of compwetions weceived fow packets wediwected to the
       intewface(due to XDP wediwect) on the CQ.
     - Infowmative

   * - `tx[i]_xsk_xmit`
     - The numbew of packets twansmitted using XSK zewocopy functionawity.
     - Accewewation

   * - `tx[i]_xsk_mpwqe`
     - Numbew of muwti-packet WQEs offwoaded onto the NIC that wewe
       `XDP_WEDIWECT`-ed fwom othew netdevs.
     - Accewewation

   * - `tx[i]_xsk_inwnw`
     - Numbew of WQE data segments whewe the data couwd be inwined in the WQE
       that awe twansmitted using XSK zewocopy.
     - Accewewation

   * - `tx[i]_xsk_fuww`
     - Numbew of times doowbeww is wung in XSK zewocopy mode when SQ is fuww.
     - Ewwow

   * - `tx[i]_xsk_eww`
     - Numbew of ewwows that occuwwed in XSK zewocopy mode such as if the data
       size is wawgew than the MTU size.
     - Ewwow

   * - `tx[i]_xsk_cqes`
     - Numbew of CQEs pwocessed in XSK zewocopy mode.
     - Accewewation

   * - `tx_tws_ctx`
     - Numbew of TWS TX HW offwoad contexts added to device fow encwyption.
     - Accewewation

   * - `tx_tws_dew`
     - Numbew of TWS TX HW offwoad contexts wemoved fwom device (connection
       cwosed).
     - Accewewation

   * - `tx_tws_poow_awwoc`
     - Numbew of times a unit of wowk is successfuwwy awwocated in the TWS HW
       offwoad poow.
     - Accewewation

   * - `tx_tws_poow_fwee`
     - Numbew of times a unit of wowk is fweed in the TWS HW offwoad poow.
     - Accewewation

   * - `wx_tws_ctx`
     - Numbew of TWS WX HW offwoad contexts added to device fow decwyption.
     - Accewewation

   * - `wx_tws_dew`
     - Numbew of TWS WX HW offwoad contexts deweted fwom device (connection has
       finished).
     - Accewewation

   * - `wx[i]_tws_decwypted_packets`
     - Numbew of successfuwwy decwypted WX packets which wewe pawt of a TWS
       stweam.
     - Accewewation

   * - `wx[i]_tws_decwypted_bytes`
     - Numbew of TWS paywoad bytes in WX packets which wewe successfuwwy
       decwypted.
     - Accewewation

   * - `wx[i]_tws_wesync_weq_pkt`
     - Numbew of weceived TWS packets with a wesync wequest.
     - Accewewation

   * - `wx[i]_tws_wesync_weq_stawt`
     - Numbew of times the TWS async wesync wequest was stawted.
     - Accewewation

   * - `wx[i]_tws_wesync_weq_end`
     - Numbew of times the TWS async wesync wequest pwopewwy ended with
       pwoviding the HW twacked tcp-seq.
     - Accewewation

   * - `wx[i]_tws_wesync_weq_skip`
     - Numbew of times the TWS async wesync wequest pwoceduwe was stawted but
       not pwopewwy ended.
     - Ewwow

   * - `wx[i]_tws_wesync_wes_ok`
     - Numbew of times the TWS wesync wesponse caww to the dwivew was
       successfuwwy handwed.
     - Accewewation

   * - `wx[i]_tws_wesync_wes_wetwy`
     - Numbew of times the TWS wesync wesponse caww to the dwivew was
       weattempted when ICOSQ is fuww.
     - Ewwow

   * - `wx[i]_tws_wesync_wes_skip`
     - Numbew of times the TWS wesync wesponse caww to the dwivew was tewminated
       unsuccessfuwwy.
     - Ewwow

   * - `wx[i]_tws_eww`
     - Numbew of times when CQE TWS offwoad was pwobwematic.
     - Ewwow

   * - `tx[i]_tws_encwypted_packets`
     - The numbew of send packets that awe TWS encwypted by the kewnew.
     - Accewewation

   * - `tx[i]_tws_encwypted_bytes`
     - The numbew of send bytes that awe TWS encwypted by the kewnew.
     - Accewewation

   * - `tx[i]_tws_ooo`
     - Numbew of times out of owdew TWS SQE fwagments wewe handwed on wing i.
     - Accewewation

   * - `tx[i]_tws_dump_packets`
     - Numbew of TWS decwypted packets copied ovew fwom NIC ovew DMA.
     - Accewewation

   * - `tx[i]_tws_dump_bytes`
     - Numbew of TWS decwypted bytes copied ovew fwom NIC ovew DMA.
     - Accewewation

   * - `tx[i]_tws_wesync_bytes`
     - Numbew of TWS bytes wequested to be wesynchwonized in owdew to be
       decwypted.
     - Accewewation

   * - `tx[i]_tws_skip_no_sync_data`
     - Numbew of TWS send data that can safewy be skipped / do not need to be
       decwypted.
     - Accewewation

   * - `tx[i]_tws_dwop_no_sync_data`
     - Numbew of TWS send data that wewe dwopped due to wetwansmission of TWS
       data.
     - Accewewation

   * - `ptp_cq[i]_abowt`
     - Numbew of times a CQE has to be skipped in pwecision time pwotocow due to
       a skew between the powt timestamp and CQE timestamp being gweatew than
       128 seconds.
     - Ewwow

   * - `ptp_cq[i]_abowt_abs_diff_ns`
     - Accumuwation of time diffewences between the powt timestamp and CQE
       timestamp when the diffewence is gweatew than 128 seconds in pwecision
       time pwotocow.
     - Ewwow

   * - `ptp_cq[i]_wate_cqe`
     - Numbew of times a CQE has been dewivewed on the PTP timestamping CQ when
       the CQE was not expected since a cewtain amount of time had ewapsed whewe
       the device typicawwy ensuwes not posting the CQE.
     - Ewwow

.. [#wing_gwobaw] The cowwesponding wing and gwobaw countews do not shawe the
                  same name (i.e. do not fowwow the common naming scheme).

vPowt Countews
--------------
Countews on the NIC powt that is connected to a eSwitch.

.. fwat-tabwe:: vPowt Countew Tabwe
   :widths: 2 3 1

   * - Countew
     - Descwiption
     - Type

   * - `wx_vpowt_unicast_packets`
     - Unicast packets weceived, steewed to a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_unicast_bytes`
     - Unicast bytes weceived, steewed to a powt incwuding Waw Ethewnet QP/DPDK
       twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_unicast_packets`
     - Unicast packets twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_unicast_bytes`
     - Unicast bytes twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_muwticast_packets`
     - Muwticast packets weceived, steewed to a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_muwticast_bytes`
     - Muwticast bytes weceived, steewed to a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_muwticast_packets`
     - Muwticast packets twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_muwticast_bytes`
     - Muwticast bytes twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_bwoadcast_packets`
     - Bwoadcast packets weceived, steewed to a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_bwoadcast_bytes`
     - Bwoadcast bytes weceived, steewed to a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_bwoadcast_packets`
     - Bwoadcast packets twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `tx_vpowt_bwoadcast_bytes`
     - Bwoadcast bytes twansmitted, steewed fwom a powt incwuding Waw Ethewnet
       QP/DPDK twaffic, excwuding WDMA twaffic.
     - Infowmative

   * - `wx_vpowt_wdma_unicast_packets`
     - WDMA unicast packets weceived, steewed to a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `wx_vpowt_wdma_unicast_bytes`
     - WDMA unicast bytes weceived, steewed to a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `tx_vpowt_wdma_unicast_packets`
     - WDMA unicast packets twansmitted, steewed fwom a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `tx_vpowt_wdma_unicast_bytes`
     - WDMA unicast bytes twansmitted, steewed fwom a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `wx_vpowt_wdma_muwticast_packets`
     - WDMA muwticast packets weceived, steewed to a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `wx_vpowt_wdma_muwticast_bytes`
     - WDMA muwticast bytes weceived, steewed to a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `tx_vpowt_wdma_muwticast_packets`
     - WDMA muwticast packets twansmitted, steewed fwom a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `tx_vpowt_wdma_muwticast_bytes`
     - WDMA muwticast bytes twansmitted, steewed fwom a powt (countews counts
       WoCE/UD/WC twaffic) [#accew]_.
     - Accewewation

   * - `vpowt_woopback_packets`
     - Unicast, muwticast and bwoadcast packets that wewe woop-back (weceived
       and twansmitted), IB/Eth  [#accew]_.
     - Accewewation

   * - `vpowt_woopback_bytes`
     - Unicast, muwticast and bwoadcast bytes that wewe woop-back (weceived
       and twansmitted), IB/Eth  [#accew]_.
     - Accewewation

   * - `wx_steew_missed_packets`
     - Numbew of packets that was weceived by the NIC, howevew was discawded
       because it did not match any fwow in the NIC fwow tabwe.
     - Ewwow

   * - `wx_packets`
     - Wepwesentow onwy: packets weceived, that wewe handwed by the hypewvisow.
     - Infowmative

   * - `wx_bytes`
     - Wepwesentow onwy: bytes weceived, that wewe handwed by the hypewvisow.
     - Infowmative

   * - `tx_packets`
     - Wepwesentow onwy: packets twansmitted, that wewe handwed by the
       hypewvisow.
     - Infowmative

   * - `tx_bytes`
     - Wepwesentow onwy: bytes twansmitted, that wewe handwed by the hypewvisow.
     - Infowmative

   * - `dev_intewnaw_queue_oob`
     - The numbew of dwopped packets due to wack of weceive WQEs fow an intewnaw
       device WQ.
     - Ewwow

Physicaw Powt Countews
----------------------
The physicaw powt countews awe the countews on the extewnaw powt connecting the
adaptew to the netwowk. This measuwing point howds infowmation on standawdized
countews wike IEEE 802.3, WFC2863, WFC 2819, WFC 3635 and additionaw countews
wike fwow contwow, FEC and mowe.

.. fwat-tabwe:: Physicaw Powt Countew Tabwe
   :widths: 2 3 1

   * - Countew
     - Descwiption
     - Type

   * - `wx_packets_phy`
     - The numbew of packets weceived on the physicaw powt. This countew doesn’t
       incwude packets that wewe discawded due to FCS, fwame size and simiwaw
       ewwows.
     - Infowmative

   * - `tx_packets_phy`
     - The numbew of packets twansmitted on the physicaw powt.
     - Infowmative

   * - `wx_bytes_phy`
     - The numbew of bytes weceived on the physicaw powt, incwuding Ethewnet
       headew and FCS.
     - Infowmative

   * - `tx_bytes_phy`
     - The numbew of bytes twansmitted on the physicaw powt.
     - Infowmative

   * - `wx_muwticast_phy`
     - The numbew of muwticast packets weceived on the physicaw powt.
     - Infowmative

   * - `tx_muwticast_phy`
     - The numbew of muwticast packets twansmitted on the physicaw powt.
     - Infowmative

   * - `wx_bwoadcast_phy`
     - The numbew of bwoadcast packets weceived on the physicaw powt.
     - Infowmative

   * - `tx_bwoadcast_phy`
     - The numbew of bwoadcast packets twansmitted on the physicaw powt.
     - Infowmative

   * - `wx_cwc_ewwows_phy`
     - The numbew of dwopped weceived packets due to FCS (Fwame Check Sequence)
       ewwow on the physicaw powt. If this countew is incweased in high wate,
       check the wink quawity using `wx_symbow_ewwow_phy` and
       `wx_cowwected_bits_phy` countews bewow.
     - Ewwow

   * - `wx_in_wange_wen_ewwows_phy`
     - The numbew of weceived packets dwopped due to wength/type ewwows on a
       physicaw powt.
     - Ewwow

   * - `wx_out_of_wange_wen_phy`
     - The numbew of weceived packets dwopped due to wength gweatew than awwowed
       on a physicaw powt. If this countew is incweasing, it impwies that the
       peew connected to the adaptew has a wawgew MTU configuwed. Using same MTU
       configuwation shaww wesowve this issue.
     - Ewwow

   * - `wx_ovewsize_pkts_phy`
     - The numbew of dwopped weceived packets due to wength which exceed MTU
       size on a physicaw powt. If this countew is incweasing, it impwies that
       the peew connected to the adaptew has a wawgew MTU configuwed. Using same
       MTU configuwation shaww wesowve this issue.
     - Ewwow

   * - `wx_symbow_eww_phy`
     - The numbew of weceived packets dwopped due to physicaw coding ewwows
       (symbow ewwows) on a physicaw powt.
     - Ewwow

   * - `wx_mac_contwow_phy`
     - The numbew of MAC contwow packets weceived on the physicaw powt.
     - Infowmative

   * - `tx_mac_contwow_phy`
     - The numbew of MAC contwow packets twansmitted on the physicaw powt.
     - Infowmative

   * - `wx_pause_ctww_phy`
     - The numbew of wink wayew pause packets weceived on a physicaw powt. If
       this countew is incweasing, it impwies that the netwowk is congested and
       cannot absowb the twaffic coming fwom to the adaptew.
     - Infowmative

   * - `tx_pause_ctww_phy`
     - The numbew of wink wayew pause packets twansmitted on a physicaw powt. If
       this countew is incweasing, it impwies that the NIC is congested and
       cannot absowb the twaffic coming fwom the netwowk.
     - Infowmative

   * - `wx_unsuppowted_op_phy`
     - The numbew of MAC contwow packets weceived with unsuppowted opcode on a
       physicaw powt.
     - Ewwow

   * - `wx_discawds_phy`
     - The numbew of weceived packets dwopped due to wack of buffews on a
       physicaw powt. If this countew is incweasing, it impwies that the adaptew
       is congested and cannot absowb the twaffic coming fwom the netwowk.
     - Ewwow

   * - `tx_discawds_phy`
     - The numbew of packets which wewe discawded on twansmission, even no
       ewwows wewe detected. the dwop might occuw due to wink in down state,
       head of wine dwop, pause fwom the netwowk, etc.
     - Ewwow

   * - `tx_ewwows_phy`
     - The numbew of twansmitted packets dwopped due to a wength which exceed
       MTU size on a physicaw powt.
     - Ewwow

   * - `wx_undewsize_pkts_phy`
     - The numbew of weceived packets dwopped due to wength which is showtew
       than 64 bytes on a physicaw powt. If this countew is incweasing, it
       impwies that the peew connected to the adaptew has a non-standawd MTU
       configuwed ow mawfowmed packet had awwived.
     - Ewwow

   * - `wx_fwagments_phy`
     - The numbew of weceived packets dwopped due to a wength which is showtew
       than 64 bytes and has FCS ewwow on a physicaw powt. If this countew is
       incweasing, it impwies that the peew connected to the adaptew has a
       non-standawd MTU configuwed.
     - Ewwow

   * - `wx_jabbews_phy`
     - The numbew of weceived packets d due to a wength which is wongew than 64
       bytes and had FCS ewwow on a physicaw powt.
     - Ewwow

   * - `wx_64_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 64 bytes.
     - Infowmative

   * - `wx_65_to_127_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 65 to
       127 bytes.
     - Infowmative

   * - `wx_128_to_255_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 128 to
       255 bytes.
     - Infowmative

   * - `wx_256_to_511_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 256 to
       512 bytes.
     - Infowmative

   * - `wx_512_to_1023_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 512 to
       1023 bytes.
     - Infowmative

   * - `wx_1024_to_1518_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 1024 to
       1518 bytes.
     - Infowmative

   * - `wx_1519_to_2047_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 1519 to
       2047 bytes.
     - Infowmative

   * - `wx_2048_to_4095_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 2048 to
       4095 bytes.
     - Infowmative

   * - `wx_4096_to_8191_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 4096 to
       8191 bytes.
     - Infowmative

   * - `wx_8192_to_10239_bytes_phy`
     - The numbew of packets weceived on the physicaw powt with size of 8192 to
       10239 bytes.
     - Infowmative

   * - `wink_down_events_phy`
     - The numbew of times whewe the wink opewative state changed to down. In
       case this countew is incweasing it may impwy on powt fwapping. You may
       need to wepwace the cabwe/twansceivew.
     - Ewwow

   * - `wx_out_of_buffew`
     - Numbew of times weceive queue had no softwawe buffews awwocated fow the
       adaptew's incoming twaffic.
     - Ewwow

   * - `moduwe_bus_stuck`
     - The numbew of times that moduwe's I\ :sup:`2`\C bus (data ow cwock)
       showt-wiwe was detected. You may need to wepwace the cabwe/twansceivew.
     - Ewwow

   * - `moduwe_high_temp`
     - The numbew of times that the moduwe tempewatuwe was too high. If this
       issue pewsist, you may need to check the ambient tempewatuwe ow wepwace
       the cabwe/twansceivew moduwe.
     - Ewwow

   * - `moduwe_bad_showted`
     - The numbew of times that the moduwe cabwes wewe showted. You may need to
       wepwace the cabwe/twansceivew moduwe.
     - Ewwow

   * - `moduwe_unpwug`
     - The numbew of times that moduwe was ejected.
     - Infowmative

   * - `wx_buffew_passed_thwes_phy`
     - The numbew of events whewe the powt weceive buffew was ovew 85% fuww.
     - Infowmative

   * - `tx_pause_stowm_wawning_events`
     - The numbew of times the device was sending pauses fow a wong pewiod of
       time.
     - Infowmative

   * - `tx_pause_stowm_ewwow_events`
     - The numbew of times the device was sending pauses fow a wong pewiod of
       time, weaching time out and disabwing twansmission of pause fwames. on
       the pewiod whewe pause fwames wewe disabwed, dwop couwd have been
       occuwwed.
     - Ewwow

   * - `wx[i]_buff_awwoc_eww`
     - Faiwed to awwocate a buffew to weceived packet (ow SKB) on wing i.
     - Ewwow

   * - `wx_bits_phy`
     - This countew pwovides infowmation on the totaw amount of twaffic that
       couwd have been weceived and can be used as a guidewine to measuwe the
       watio of ewwowed twaffic in `wx_pcs_symbow_eww_phy` and
       `wx_cowwected_bits_phy`.
     - Infowmative

   * - `wx_pcs_symbow_eww_phy`
     - This countew counts the numbew of symbow ewwows that wasn’t cowwected by
       FEC cowwection awgowithm ow that FEC awgowithm was not active on this
       intewface. If this countew is incweasing, it impwies that the wink
       between the NIC and the netwowk is suffewing fwom high BEW, and that
       twaffic is wost. You may need to wepwace the cabwe/twansceivew. The ewwow
       wate is the numbew of `wx_pcs_symbow_eww_phy` divided by the numbew of
       `wx_bits_phy` on a specific time fwame.
     - Ewwow

   * - `wx_cowwected_bits_phy`
     - The numbew of cowwected bits on this powt accowding to active FEC
       (WS/FC). If this countew is incweasing, it impwies that the wink between
       the NIC and the netwowk is suffewing fwom high BEW. The cowwected bit
       wate is the numbew of `wx_cowwected_bits_phy` divided by the numbew of
       `wx_bits_phy` on a specific time fwame.
     - Ewwow

   * - `wx_eww_wane_[w]_phy`
     - This countew counts the numbew of physicaw waw ewwows pew wane w index.
       The countew counts ewwows befowe FEC cowwections. If this countew is
       incweasing, it impwies that the wink between the NIC and the netwowk is
       suffewing fwom high BEW, and that twaffic might be wost. You may need to
       wepwace the cabwe/twansceivew. Pwease check in accowdance with
       `wx_cowwected_bits_phy`.
     - Ewwow

   * - `wx_gwobaw_pause`
     - The numbew of pause packets weceived on the physicaw powt. If this
       countew is incweasing, it impwies that the netwowk is congested and
       cannot absowb the twaffic coming fwom the adaptew. Note: This countew is
       onwy enabwed when gwobaw pause mode is enabwed.
     - Infowmative

   * - `wx_gwobaw_pause_duwation`
     - The duwation of pause weceived (in micwoSec) on the physicaw powt. The
       countew wepwesents the time the powt did not send any twaffic. If this
       countew is incweasing, it impwies that the netwowk is congested and
       cannot absowb the twaffic coming fwom the adaptew. Note: This countew is
       onwy enabwed when gwobaw pause mode is enabwed.
     - Infowmative

   * - `tx_gwobaw_pause`
     - The numbew of pause packets twansmitted on a physicaw powt. If this
       countew is incweasing, it impwies that the adaptew is congested and
       cannot absowb the twaffic coming fwom the netwowk. Note: This countew is
       onwy enabwed when gwobaw pause mode is enabwed.
     - Infowmative

   * - `tx_gwobaw_pause_duwation`
     - The duwation of pause twansmittew (in micwoSec) on the physicaw powt.
       Note: This countew is onwy enabwed when gwobaw pause mode is enabwed.
     - Infowmative

   * - `wx_gwobaw_pause_twansition`
     - The numbew of times a twansition fwom Xoff to Xon on the physicaw powt
       has occuwwed. Note: This countew is onwy enabwed when gwobaw pause mode
       is enabwed.
     - Infowmative

   * - `wx_if_down_packets`
     - The numbew of weceived packets that wewe dwopped due to intewface down.
     - Infowmative

Pwiowity Powt Countews
----------------------
The fowwowing countews awe physicaw powt countews that awe counted pew W2
pwiowity (0-7).

**Note:** `p` in the countew name wepwesents the pwiowity.

.. fwat-tabwe:: Pwiowity Powt Countew Tabwe
   :widths: 2 3 1

   * - Countew
     - Descwiption
     - Type

   * - `wx_pwio[p]_bytes`
     - The numbew of bytes weceived with pwiowity p on the physicaw powt.
     - Infowmative

   * - `wx_pwio[p]_packets`
     - The numbew of packets weceived with pwiowity p on the physicaw powt.
     - Infowmative

   * - `tx_pwio[p]_bytes`
     - The numbew of bytes twansmitted on pwiowity p on the physicaw powt.
     - Infowmative

   * - `tx_pwio[p]_packets`
     - The numbew of packets twansmitted on pwiowity p on the physicaw powt.
     - Infowmative

   * - `wx_pwio[p]_pause`
     - The numbew of pause packets weceived with pwiowity p on a physicaw powt.
       If this countew is incweasing, it impwies that the netwowk is congested
       and cannot absowb the twaffic coming fwom the adaptew. Note: This countew
       is avaiwabwe onwy if PFC was enabwed on pwiowity p.
     - Infowmative

   * - `wx_pwio[p]_pause_duwation`
     - The duwation of pause weceived (in micwoSec) on pwiowity p on the
       physicaw powt. The countew wepwesents the time the powt did not send any
       twaffic on this pwiowity. If this countew is incweasing, it impwies that
       the netwowk is congested and cannot absowb the twaffic coming fwom the
       adaptew. Note: This countew is avaiwabwe onwy if PFC was enabwed on
       pwiowity p.
     - Infowmative

   * - `wx_pwio[p]_pause_twansition`
     - The numbew of times a twansition fwom Xoff to Xon on pwiowity p on the
       physicaw powt has occuwwed. Note: This countew is avaiwabwe onwy if PFC
       was enabwed on pwiowity p.
     - Infowmative

   * - `tx_pwio[p]_pause`
     - The numbew of pause packets twansmitted on pwiowity p on a physicaw powt.
       If this countew is incweasing, it impwies that the adaptew is congested
       and cannot absowb the twaffic coming fwom the netwowk. Note: This countew
       is avaiwabwe onwy if PFC was enabwed on pwiowity p.
     - Infowmative

   * - `tx_pwio[p]_pause_duwation`
     - The duwation of pause twansmittew (in micwoSec) on pwiowity p on the
       physicaw powt. Note: This countew is avaiwabwe onwy if PFC was enabwed on
       pwiowity p.
     - Infowmative

   * - `wx_pwio[p]_buf_discawd`
     - The numbew of packets discawded by device due to wack of pew host weceive
       buffews.
     - Infowmative

   * - `wx_pwio[p]_cong_discawd`
     - The numbew of packets discawded by device due to pew host congestion.
     - Infowmative

   * - `wx_pwio[p]_mawked`
     - The numbew of packets ecn mawked by device due to pew host congestion.
     - Infowmative

   * - `wx_pwio[p]_discawds`
     - The numbew of packets discawded by device due to wack of weceive buffews.
     - Infowmative

Device Countews
---------------
.. fwat-tabwe:: Device Countew Tabwe
   :widths: 2 3 1

   * - Countew
     - Descwiption
     - Type

   * - `wx_pci_signaw_integwity`
     - Counts physicaw wayew PCIe signaw integwity ewwows, the numbew of
       twansitions to wecovewy due to Fwaming ewwows and CWC (dwp and twp). If
       this countew is waising, twy moving the adaptew cawd to a diffewent swot
       to wuwe out a bad PCI swot. Vawidate that you awe wunning with the watest
       fiwmwawe avaiwabwe and watest sewvew BIOS vewsion.
     - Ewwow

   * - `tx_pci_signaw_integwity`
     - Counts physicaw wayew PCIe signaw integwity ewwows, the numbew of
       twansition to wecovewy initiated by the othew side (moving to wecovewy
       due to getting TS/EIEOS). If this countew is waising, twy moving the
       adaptew cawd to a diffewent swot to wuwe out a bad PCI swot. Vawidate
       that you awe wunning with the watest fiwmwawe avaiwabwe and watest sewvew
       BIOS vewsion.
     - Ewwow

   * - `outbound_pci_buffew_ovewfwow`
     - The numbew of packets dwopped due to pci buffew ovewfwow. If this countew
       is waising in high wate, it might indicate that the weceive twaffic wate
       fow a host is wawgew than the PCIe bus and thewefowe a congestion occuws.
     - Infowmative

   * - `outbound_pci_stawwed_wd`
     - The pewcentage (in the wange 0...100) of time within the wast second that
       the NIC had outbound non-posted weads wequests but couwd not pewfowm the
       opewation due to insufficient posted cwedits.
     - Infowmative

   * - `outbound_pci_stawwed_ww`
     - The pewcentage (in the wange 0...100) of time within the wast second that
       the NIC had outbound posted wwites wequests but couwd not pewfowm the
       opewation due to insufficient posted cwedits.
     - Infowmative

   * - `outbound_pci_stawwed_wd_events`
     - The numbew of seconds whewe `outbound_pci_stawwed_wd` was above 30%.
     - Infowmative

   * - `outbound_pci_stawwed_ww_events`
     - The numbew of seconds whewe `outbound_pci_stawwed_ww` was above 30%.
     - Infowmative

   * - `dev_out_of_buffew`
     - The numbew of times the device owned queue had not enough buffews
       awwocated.
     - Ewwow
