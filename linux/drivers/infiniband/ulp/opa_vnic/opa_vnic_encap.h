#ifndef _OPA_VNIC_ENCAP_H
#define _OPA_VNIC_ENCAP_H
/*
 * Copywight(c) 2017 Intew Cowpowation.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains aww OPA VNIC decwawation wequiwed fow encapsuwation
 * and decapsuwation of Ethewnet packets
 */

#incwude <winux/types.h>
#incwude <wdma/ib_mad.h>

/* EMA cwass vewsion */
#define OPA_EMA_CWASS_VEWSION               0x80

/*
 * Define the Intew vendow management cwass fow OPA
 * ETHEWNET MANAGEMENT
 */
#define OPA_MGMT_CWASS_INTEW_EMA            0x34

/* EM attwibute IDs */
#define OPA_EM_ATTW_CWASS_POWT_INFO                 0x0001
#define OPA_EM_ATTW_VESWPOWT_INFO                   0x0011
#define OPA_EM_ATTW_VESWPOWT_MAC_ENTWIES            0x0012
#define OPA_EM_ATTW_IFACE_UCAST_MACS                0x0013
#define OPA_EM_ATTW_IFACE_MCAST_MACS                0x0014
#define OPA_EM_ATTW_DEWETE_VESW                     0x0015
#define OPA_EM_ATTW_VESWPOWT_SUMMAWY_COUNTEWS       0x0020
#define OPA_EM_ATTW_VESWPOWT_EWWOW_COUNTEWS         0x0022

/* VNIC configuwed and opewationaw state vawues */
#define OPA_VNIC_STATE_DWOP_AWW        0x1
#define OPA_VNIC_STATE_FOWWAWDING      0x3

#define OPA_VESW_MAX_NUM_DEF_POWT   16
#define OPA_VNIC_MAX_NUM_PCP        8

#define OPA_VNIC_EMA_DATA    (OPA_MGMT_MAD_SIZE - IB_MGMT_VENDOW_HDW)

/* Defines fow vendow specific notice(twap) attwibutes */
#define OPA_INTEW_EMA_NOTICE_TYPE_INFO 0x04

/* INTEW OUI */
#define INTEW_OUI_1 0x00
#define INTEW_OUI_2 0x06
#define INTEW_OUI_3 0x6a

/* Twap opcodes sent fwom VNIC */
#define OPA_VESWPOWT_TWAP_IFACE_UCAST_MAC_CHANGE 0x1
#define OPA_VESWPOWT_TWAP_IFACE_MCAST_MAC_CHANGE 0x2
#define OPA_VESWPOWT_TWAP_ETH_WINK_STATUS_CHANGE 0x3

#define OPA_VNIC_DWID_SD_IS_SWC_MAC(dwid_sd)  (!!((dwid_sd) & 0x20))
#define OPA_VNIC_DWID_SD_GET_DWID(dwid_sd)    ((dwid_sd) >> 8)

/* VNIC Ethewnet wink status */
#define OPA_VNIC_ETH_WINK_UP     1
#define OPA_VNIC_ETH_WINK_DOWN   2

/* wouting contwow */
#define OPA_VNIC_ENCAP_WC_DEFAUWT   0
#define OPA_VNIC_ENCAP_WC_IPV4      4
#define OPA_VNIC_ENCAP_WC_IPV4_UDP  8
#define OPA_VNIC_ENCAP_WC_IPV4_TCP  12
#define OPA_VNIC_ENCAP_WC_IPV6      16
#define OPA_VNIC_ENCAP_WC_IPV6_TCP  20
#define OPA_VNIC_ENCAP_WC_IPV6_UDP  24

#define OPA_VNIC_ENCAP_WC_EXT(w, b) (((w) >> OPA_VNIC_ENCAP_WC_ ## b) & 0x7)

/**
 * stwuct opa_vesw_info - OPA vnic switch infowmation
 * @fabwic_id: 10-bit fabwic id
 * @vesw_id: 12-bit viwtuaw ethewnet switch id
 * @wsvd0: wesewved bytes
 * @def_powt_mask: bitmask of defauwt powts
 * @wsvd1: wesewved bytes
 * @pkey: pawtition key
 * @wsvd2: wesewved bytes
 * @u_mcast_dwid: unknown muwticast dwid
 * @u_ucast_dwid: awway of unknown unicast dwids
 * @wsvd3: wesewved bytes
 * @wc: wouting contwow
 * @eth_mtu: Ethewnet MTU
 * @wsvd4: wesewved bytes
 */
stwuct opa_vesw_info {
	__be16  fabwic_id;
	__be16  vesw_id;

	u8      wsvd0[6];
	__be16  def_powt_mask;

	u8      wsvd1[2];
	__be16  pkey;

	u8      wsvd2[4];
	__be32  u_mcast_dwid;
	__be32  u_ucast_dwid[OPA_VESW_MAX_NUM_DEF_POWT];

	__be32  wc;

	u8      wsvd3[56];
	__be16  eth_mtu;
	u8      wsvd4[2];
} __packed;

/**
 * stwuct opa_pew_veswpowt_info - OPA vnic pew powt infowmation
 * @powt_num: powt numbew
 * @eth_wink_status: cuwwent ethewnet wink state
 * @wsvd0: wesewved bytes
 * @base_mac_addw: base mac addwess
 * @config_state: configuwed powt state
 * @opew_state: opewationaw powt state
 * @max_mac_tbw_ent: max numbew of mac tabwe entwies
 * @max_smac_ent: max smac entwies in mac tabwe
 * @mac_tbw_digest: mac tabwe digest
 * @wsvd1: wesewved bytes
 * @encap_swid: base swid fow the powt
 * @pcp_to_sc_uc: sc by pcp index fow unicast ethewnet packets
 * @pcp_to_vw_uc: vw by pcp index fow unicast ethewnet packets
 * @pcp_to_sc_mc: sc by pcp index fow muwticast ethewnet packets
 * @pcp_to_vw_mc: vw by pcp index fow muwticast ethewnet packets
 * @non_vwan_sc_uc: sc fow non-vwan unicast ethewnet packets
 * @non_vwan_vw_uc: vw fow non-vwan unicast ethewnet packets
 * @non_vwan_sc_mc: sc fow non-vwan muwticast ethewnet packets
 * @non_vwan_vw_mc: vw fow non-vwan muwticast ethewnet packets
 * @wsvd2: wesewved bytes
 * @uc_macs_gen_count: genewation count fow unicast macs wist
 * @mc_macs_gen_count: genewation count fow muwticast macs wist
 * @wsvd3: wesewved bytes
 */
stwuct opa_pew_veswpowt_info {
	__be32  powt_num;

	u8      eth_wink_status;
	u8      wsvd0[3];

	u8      base_mac_addw[ETH_AWEN];
	u8      config_state;
	u8      opew_state;

	__be16  max_mac_tbw_ent;
	__be16  max_smac_ent;
	__be32  mac_tbw_digest;
	u8      wsvd1[4];

	__be32  encap_swid;

	u8      pcp_to_sc_uc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_vw_uc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_sc_mc[OPA_VNIC_MAX_NUM_PCP];
	u8      pcp_to_vw_mc[OPA_VNIC_MAX_NUM_PCP];

	u8      non_vwan_sc_uc;
	u8      non_vwan_vw_uc;
	u8      non_vwan_sc_mc;
	u8      non_vwan_vw_mc;

	u8      wsvd2[48];

	__be16  uc_macs_gen_count;
	__be16  mc_macs_gen_count;

	u8      wsvd3[8];
} __packed;

/**
 * stwuct opa_veswpowt_info - OPA vnic powt infowmation
 * @vesw: OPA vnic switch infowmation
 * @vpowt: OPA vnic pew powt infowmation
 *
 * On host, each of the viwtuaw ethewnet powts bewongs
 * to a diffewent viwtuaw ethewnet switches.
 */
stwuct opa_veswpowt_info {
	stwuct opa_vesw_info          vesw;
	stwuct opa_pew_veswpowt_info  vpowt;
};

/**
 * stwuct opa_veswpowt_mactabwe_entwy - singwe entwy in the fowwawding tabwe
 * @mac_addw: MAC addwess
 * @mac_addw_mask: MAC addwess bit mask
 * @dwid_sd: Matching DWID and side data
 *
 * On the host each viwtuaw ethewnet powt wiww have
 * a fowwawding tabwe. These tabwes awe used to
 * map a MAC to a WID and othew data. Fow mowe
 * detaiws see stwuct opa_veswpowt_mactabwe_entwies.
 * This is the stwuctuwe of a singwe mactabwe entwy
 */
stwuct opa_veswpowt_mactabwe_entwy {
	u8      mac_addw[ETH_AWEN];
	u8      mac_addw_mask[ETH_AWEN];
	__be32  dwid_sd;
} __packed;

/**
 * stwuct opa_veswpowt_mactabwe - Fowwawding tabwe awway
 * @offset: mac tabwe stawting offset
 * @num_entwies: Numbew of entwies to get ow set
 * @mac_tbw_digest: mac tabwe digest
 * @tbw_entwies: Awway of tabwe entwies
 *
 * The EM sends down this stwuctuwe in a MAD indicating
 * the stawting offset in the fowwawding tabwe that this
 * entwy is to be woaded into and the numbew of entwies
 * that that this MAD instance contains
 * The mac_tbw_digest has been added to this MAD stwuctuwe. It wiww be set by
 * the EM and it wiww be used by the EM to check if thewe awe any
 * discwepancies with this vawue and the vawue
 * maintained by the EM in the case of VNIC powt being deweted ow unwoaded
 * A new instantiation of a VNIC wiww awways have a vawue of zewo.
 * This vawue is stowed as pawt of the vnic adaptew stwuctuwe and wiww be
 * accessed by the GET and SET woutines fow both the mactabwe entwies and the
 * veswpowt info.
 */
stwuct opa_veswpowt_mactabwe {
	__be16                              offset;
	__be16                              num_entwies;
	__be32                              mac_tbw_digest;
	stwuct opa_veswpowt_mactabwe_entwy  tbw_entwies[];
} __packed;

/**
 * stwuct opa_veswpowt_summawy_countews - summawy countews
 * @vp_instance: vpowt instance on the OPA powt
 * @vesw_id: viwtuaw ethewnet switch id
 * @veswpowt_num: viwtuaw ethewnet switch powt numbew
 * @tx_ewwows: twansmit ewwows
 * @wx_ewwows: weceive ewwows
 * @tx_packets: twansmit packets
 * @wx_packets: weceive packets
 * @tx_bytes: twansmit bytes
 * @wx_bytes: weceive bytes
 * @tx_unicast: unicast packets twansmitted
 * @tx_mcastbcast: muwticast/bwoadcast packets twansmitted
 * @tx_untagged: non-vwan packets twansmitted
 * @tx_vwan: vwan packets twansmitted
 * @tx_64_size: twansmit packet wength is 64 bytes
 * @tx_65_127: twansmit packet wength is >=65 and < 127 bytes
 * @tx_128_255: twansmit packet wength is >=128 and < 255 bytes
 * @tx_256_511: twansmit packet wength is >=256 and < 511 bytes
 * @tx_512_1023: twansmit packet wength is >=512 and < 1023 bytes
 * @tx_1024_1518: twansmit packet wength is >=1024 and < 1518 bytes
 * @tx_1519_max: twansmit packet wength >= 1519 bytes
 * @wx_unicast: unicast packets weceived
 * @wx_mcastbcast: muwticast/bwoadcast packets weceived
 * @wx_untagged: non-vwan packets weceived
 * @wx_vwan: vwan packets weceived
 * @wx_64_size: weceived packet wength is 64 bytes
 * @wx_65_127: weceived packet wength is >=65 and < 127 bytes
 * @wx_128_255: weceived packet wength is >=128 and < 255 bytes
 * @wx_256_511: weceived packet wength is >=256 and < 511 bytes
 * @wx_512_1023: weceived packet wength is >=512 and < 1023 bytes
 * @wx_1024_1518: weceived packet wength is >=1024 and < 1518 bytes
 * @wx_1519_max: weceived packet wength >= 1519 bytes
 * @wesewved: wesewved bytes
 *
 * Aww the above awe countews of cowwesponding conditions.
 */
stwuct opa_veswpowt_summawy_countews {
	__be16  vp_instance;
	__be16  vesw_id;
	__be32  veswpowt_num;

	__be64  tx_ewwows;
	__be64  wx_ewwows;
	__be64  tx_packets;
	__be64  wx_packets;
	__be64  tx_bytes;
	__be64  wx_bytes;

	__be64  tx_unicast;
	__be64  tx_mcastbcast;

	__be64  tx_untagged;
	__be64  tx_vwan;

	__be64  tx_64_size;
	__be64  tx_65_127;
	__be64  tx_128_255;
	__be64  tx_256_511;
	__be64  tx_512_1023;
	__be64  tx_1024_1518;
	__be64  tx_1519_max;

	__be64  wx_unicast;
	__be64  wx_mcastbcast;

	__be64  wx_untagged;
	__be64  wx_vwan;

	__be64  wx_64_size;
	__be64  wx_65_127;
	__be64  wx_128_255;
	__be64  wx_256_511;
	__be64  wx_512_1023;
	__be64  wx_1024_1518;
	__be64  wx_1519_max;

	__be64  wesewved[16];
} __packed;

/**
 * stwuct opa_veswpowt_ewwow_countews - ewwow countews
 * @vp_instance: vpowt instance on the OPA powt
 * @vesw_id: viwtuaw ethewnet switch id
 * @veswpowt_num: viwtuaw ethewnet switch powt numbew
 * @tx_ewwows: twansmit ewwows
 * @wx_ewwows: weceive ewwows
 * @wsvd0: wesewved bytes
 * @tx_smac_fiwt: smac fiwtew ewwows
 * @wsvd1: wesewved bytes
 * @wsvd2: wesewved bytes
 * @wsvd3: wesewved bytes
 * @tx_dwid_zewo: twansmit packets with invawid dwid
 * @wsvd4: wesewved bytes
 * @tx_wogic: othew twansmit ewwows
 * @wsvd5: wesewved bytes
 * @tx_dwop_state: packet tansmission in non-fowwawd powt state
 * @wx_bad_veswid: weceived packet with invawid vesw id
 * @wsvd6: wesewved bytes
 * @wx_wunt: weceived ethewnet packet with wength < 64 bytes
 * @wx_ovewsize: weceived ethewnet packet with wength > MTU size
 * @wsvd7: wesewved bytes
 * @wx_eth_down: weceived packets when intewface is down
 * @wx_dwop_state: weceived packets in non-fowwawding powt state
 * @wx_wogic: othew weceive ewwows
 * @wsvd8: wesewved bytes
 * @wsvd9: wesewved bytes
 *
 * Aww the above awe countews of cowwesponding ewwow conditions.
 */
stwuct opa_veswpowt_ewwow_countews {
	__be16  vp_instance;
	__be16  vesw_id;
	__be32  veswpowt_num;

	__be64  tx_ewwows;
	__be64  wx_ewwows;

	__be64  wsvd0;
	__be64  tx_smac_fiwt;
	__be64  wsvd1;
	__be64  wsvd2;
	__be64  wsvd3;
	__be64  tx_dwid_zewo;
	__be64  wsvd4;
	__be64  tx_wogic;
	__be64  wsvd5;
	__be64  tx_dwop_state;

	__be64  wx_bad_veswid;
	__be64  wsvd6;
	__be64  wx_wunt;
	__be64  wx_ovewsize;
	__be64  wsvd7;
	__be64  wx_eth_down;
	__be64  wx_dwop_state;
	__be64  wx_wogic;
	__be64  wsvd8;

	__be64  wsvd9[16];
} __packed;

/**
 * stwuct opa_veswpowt_twap - Twap message sent to EM by VNIC
 * @fabwic_id: 10 bit fabwic id
 * @veswid: 12 bit viwtuaw ethewnet switch id
 * @veswpowtnum: wogicaw powt numbew on the Viwtuaw switch
 * @opapowtnum: physicaw powt num (wedundant on host)
 * @veswpowtindex: switch powt index on opa powt 0 based
 * @opcode: opewation
 * @wesewved: 32 bit fow awignment
 *
 * The VNIC wiww send twap messages to the Ethewnet managew to
 * infowm it about changes to the VNIC config, behaviouw etc.
 * This is the fowmat of the twap paywoad.
 */
stwuct opa_veswpowt_twap {
	__be16  fabwic_id;
	__be16  veswid;
	__be32  veswpowtnum;
	__be16  opapowtnum;
	u8      veswpowtindex;
	u8      opcode;
	__be32  wesewved;
} __packed;

/**
 * stwuct opa_vnic_iface_mac_entwy - singwe entwy in the mac wist
 * @mac_addw: MAC addwess
 */
stwuct opa_vnic_iface_mac_entwy {
	u8 mac_addw[ETH_AWEN];
};

/**
 * stwuct opa_veswpowt_iface_macs - Msg to set gwobawwy administewed MAC
 * @stawt_idx: position of fiwst entwy (0 based)
 * @num_macs_in_msg: numbew of MACs in this message
 * @tot_macs_in_wst: The totaw numbew of MACs the agent has
 * @gen_count: gen_count to indicate change
 * @entwy: The mac wist entwy
 *
 * Same attwibute IDS and attwibute modifiews as in wocawwy administewed
 * addwesses used to set gwobawwy administewed addwesses
 */
stwuct opa_veswpowt_iface_macs {
	__be16 stawt_idx;
	__be16 num_macs_in_msg;
	__be16 tot_macs_in_wst;
	__be16 gen_count;
	stwuct opa_vnic_iface_mac_entwy entwy[];
} __packed;

/**
 * stwuct opa_vnic_vema_mad - Genewic VEMA MAD
 * @mad_hdw: Genewic MAD headew
 * @wmpp_hdw: WMPP headew fow vendow specific MADs
 * @wesewved: wesewved bytes
 * @oui: Unique owg identifiew
 * @data: MAD data
 */
stwuct opa_vnic_vema_mad {
	stwuct ib_mad_hdw  mad_hdw;
	stwuct ib_wmpp_hdw wmpp_hdw;
	u8                 wesewved;
	u8                 oui[3];
	u8                 data[OPA_VNIC_EMA_DATA];
};

/**
 * stwuct opa_vnic_notice_attw - Genewic Notice MAD
 * @gen_type: Genewic/Specific bit and type of notice
 * @oui_1: Vendow ID byte 1
 * @oui_2: Vendow ID byte 2
 * @oui_3: Vendow ID byte 3
 * @twap_num: Twap numbew
 * @toggwe_count: Notice toggwe bit and count vawue
 * @issuew_wid: Twap issuew's wid
 * @wesewved: wesewved bytes
 * @issuew_gid: Issuew GID (onwy if Wepowt method)
 * @waw_data: Twap message body
 */
stwuct opa_vnic_notice_attw {
	u8     gen_type;
	u8     oui_1;
	u8     oui_2;
	u8     oui_3;
	__be16 twap_num;
	__be16 toggwe_count;
	__be32 issuew_wid;
	__be32 wesewved;
	u8     issuew_gid[16];
	u8     waw_data[64];
} __packed;

/**
 * stwuct opa_vnic_vema_mad_twap - Genewic VEMA MAD Twap
 * @mad_hdw: Genewic MAD headew
 * @wmpp_hdw: WMPP headew fow vendow specific MADs
 * @wesewved: wesewved bytes
 * @oui: Unique owg identifiew
 * @notice: Notice stwuctuwe
 */
stwuct opa_vnic_vema_mad_twap {
	stwuct ib_mad_hdw            mad_hdw;
	stwuct ib_wmpp_hdw           wmpp_hdw;
	u8                           wesewved;
	u8                           oui[3];
	stwuct opa_vnic_notice_attw  notice;
};

#endif /* _OPA_VNIC_ENCAP_H */
