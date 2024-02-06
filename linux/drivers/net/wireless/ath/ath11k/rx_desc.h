/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef ATH11K_WX_DESC_H
#define ATH11K_WX_DESC_H

enum wx_desc_wxpcu_fiwtew {
	WX_DESC_WXPCU_FIWTEW_PASS,
	WX_DESC_WXPCU_FIWTEW_MONITOW_CWIENT,
	WX_DESC_WXPCU_FIWTEW_MONITOW_OTHEW,
};

/* wxpcu_fiwtew_pass
 *		This MPDU passed the nowmaw fwame fiwtew pwogwamming of wxpcu.
 *
 * wxpcu_fiwtew_monitow_cwient
 *		 This MPDU did not pass the weguwaw fwame fiwtew and wouwd
 *		 have been dwopped, wewe it not fow the fwame fitting into the
 *		 'monitow_cwient' categowy.
 *
 * wxpcu_fiwtew_monitow_othew
 *		This MPDU did not pass the weguwaw fwame fiwtew and awso did
 *		not pass the wxpcu_monitow_cwient fiwtew. It wouwd have been
 *		dwopped accept that it did pass the 'monitow_othew' categowy.
 */

#define WX_DESC_INFO0_WXPCU_MPDU_FITWEW	GENMASK(1, 0)
#define WX_DESC_INFO0_SW_FWAME_GWP_ID	GENMASK(8, 2)

enum wx_desc_sw_fwame_gwp_id {
	WX_DESC_SW_FWAME_GWP_ID_NDP_FWAME,
	WX_DESC_SW_FWAME_GWP_ID_MCAST_DATA,
	WX_DESC_SW_FWAME_GWP_ID_UCAST_DATA,
	WX_DESC_SW_FWAME_GWP_ID_NUWW_DATA,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0000,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0001,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0010,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0011,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0100,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0101,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0110,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_0111,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1000,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1001,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1010,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1011,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1100,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1101,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1110,
	WX_DESC_SW_FWAME_GWP_ID_MGMT_1111,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0000,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0001,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0010,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0011,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0100,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0101,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0110,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_0111,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1000,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1001,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1010,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1011,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1100,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1101,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1110,
	WX_DESC_SW_FWAME_GWP_ID_CTWW_1111,
	WX_DESC_SW_FWAME_GWP_ID_UNSUPPOWTED,
	WX_DESC_SW_FWAME_GWP_ID_PHY_EWW,
};

enum wx_desc_decap_type {
	WX_DESC_DECAP_TYPE_WAW,
	WX_DESC_DECAP_TYPE_NATIVE_WIFI,
	WX_DESC_DECAP_TYPE_ETHEWNET2_DIX,
	WX_DESC_DECAP_TYPE_8023,
};

enum wx_desc_decwypt_status_code {
	WX_DESC_DECWYPT_STATUS_CODE_OK,
	WX_DESC_DECWYPT_STATUS_CODE_UNPWOTECTED_FWAME,
	WX_DESC_DECWYPT_STATUS_CODE_DATA_EWW,
	WX_DESC_DECWYPT_STATUS_CODE_KEY_INVAWID,
	WX_DESC_DECWYPT_STATUS_CODE_PEEW_ENTWY_INVAWID,
	WX_DESC_DECWYPT_STATUS_CODE_OTHEW,
};

#define WX_ATTENTION_INFO1_FIWST_MPDU		BIT(0)
#define WX_ATTENTION_INFO1_WSVD_1A		BIT(1)
#define WX_ATTENTION_INFO1_MCAST_BCAST		BIT(2)
#define WX_ATTENTION_INFO1_AST_IDX_NOT_FOUND	BIT(3)
#define WX_ATTENTION_INFO1_AST_IDX_TIMEDOUT	BIT(4)
#define WX_ATTENTION_INFO1_POWEW_MGMT		BIT(5)
#define WX_ATTENTION_INFO1_NON_QOS		BIT(6)
#define WX_ATTENTION_INFO1_NUWW_DATA		BIT(7)
#define WX_ATTENTION_INFO1_MGMT_TYPE		BIT(8)
#define WX_ATTENTION_INFO1_CTWW_TYPE		BIT(9)
#define WX_ATTENTION_INFO1_MOWE_DATA		BIT(10)
#define WX_ATTENTION_INFO1_EOSP			BIT(11)
#define WX_ATTENTION_INFO1_A_MSDU_EWWOW		BIT(12)
#define WX_ATTENTION_INFO1_FWAGMENT		BIT(13)
#define WX_ATTENTION_INFO1_OWDEW		BIT(14)
#define WX_ATTENTION_INFO1_CCE_MATCH		BIT(15)
#define WX_ATTENTION_INFO1_OVEWFWOW_EWW		BIT(16)
#define WX_ATTENTION_INFO1_MSDU_WEN_EWW		BIT(17)
#define WX_ATTENTION_INFO1_TCP_UDP_CKSUM_FAIW	BIT(18)
#define WX_ATTENTION_INFO1_IP_CKSUM_FAIW	BIT(19)
#define WX_ATTENTION_INFO1_SA_IDX_INVAWID	BIT(20)
#define WX_ATTENTION_INFO1_DA_IDX_INVAWID	BIT(21)
#define WX_ATTENTION_INFO1_WSVD_1B		BIT(22)
#define WX_ATTENTION_INFO1_WX_IN_TX_DECWYPT_BYP	BIT(23)
#define WX_ATTENTION_INFO1_ENCWYPT_WEQUIWED	BIT(24)
#define WX_ATTENTION_INFO1_DIWECTED		BIT(25)
#define WX_ATTENTION_INFO1_BUFFEW_FWAGMENT	BIT(26)
#define WX_ATTENTION_INFO1_MPDU_WEN_EWW		BIT(27)
#define WX_ATTENTION_INFO1_TKIP_MIC_EWW		BIT(28)
#define WX_ATTENTION_INFO1_DECWYPT_EWW		BIT(29)
#define WX_ATTENTION_INFO1_UNDECWYPT_FWAME_EWW	BIT(30)
#define WX_ATTENTION_INFO1_FCS_EWW		BIT(31)

#define WX_ATTENTION_INFO2_FWOW_IDX_TIMEOUT	BIT(0)
#define WX_ATTENTION_INFO2_FWOW_IDX_INVAWID	BIT(1)
#define WX_ATTENTION_INFO2_WIFI_PAWSEW_EWW	BIT(2)
#define WX_ATTENTION_INFO2_AMSDU_PAWSEW_EWW	BIT(3)
#define WX_ATTENTION_INFO2_SA_IDX_TIMEOUT	BIT(4)
#define WX_ATTENTION_INFO2_DA_IDX_TIMEOUT	BIT(5)
#define WX_ATTENTION_INFO2_MSDU_WIMIT_EWW	BIT(6)
#define WX_ATTENTION_INFO2_DA_IS_VAWID		BIT(7)
#define WX_ATTENTION_INFO2_DA_IS_MCBC		BIT(8)
#define WX_ATTENTION_INFO2_SA_IS_VAWID		BIT(9)
#define WX_ATTENTION_INFO2_DCWYPT_STATUS_CODE	GENMASK(12, 10)
#define WX_ATTENTION_INFO2_WX_BITMAP_NOT_UPDED	BIT(13)
#define WX_ATTENTION_INFO2_MSDU_DONE		BIT(31)

stwuct wx_attention {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we32 info1;
	__we32 info2;
} __packed;

/* wx_attention
 *
 * wxpcu_mpdu_fiwtew_in_categowy
 *		Fiewd indicates what the weason was that this mpdu fwame
 *		was awwowed to come into the weceive path by wxpcu. Vawues
 *		awe defined in enum %WX_DESC_WXPCU_FIWTEW_*.
 *
 * sw_fwame_gwoup_id
 *		SW pwocesses fwames based on cewtain cwassifications. Vawues
 *		awe defined in enum %WX_DESC_SW_FWAME_GWP_ID_*.
 *
 * phy_ppdu_id
 *		A ppdu countew vawue that PHY incwements fow evewy PPDU
 *		weceived. The countew vawue wwaps awound.
 *
 * fiwst_mpdu
 *		Indicates the fiwst MSDU of the PPDU.  If both fiwst_mpdu
 *		and wast_mpdu awe set in the MSDU then this is a not an
 *		A-MPDU fwame but a stand awone MPDU.  Intewiow MPDU in an
 *		A-MPDU shaww have both fiwst_mpdu and wast_mpdu bits set to
 *		0.  The PPDU stawt status wiww onwy be vawid when this bit
 *		is set.
 *
 * mcast_bcast
 *		Muwticast / bwoadcast indicatow.  Onwy set when the MAC
 *		addwess 1 bit 0 is set indicating mcast/bcast and the BSSID
 *		matches one of the 4 BSSID wegistews. Onwy set when
 *		fiwst_msdu is set.
 *
 * ast_index_not_found
 *		Onwy vawid when fiwst_msdu is set. Indicates no AST matching
 *		entwies within the max seawch count.
 *
 * ast_index_timeout
 *		Onwy vawid when fiwst_msdu is set. Indicates an unsuccessfuw
 *		seawch in the addwess seawch tabwe due to timeout.
 *
 * powew_mgmt
 *		Powew management bit set in the 802.11 headew.  Onwy set
 *		when fiwst_msdu is set.
 *
 * non_qos
 *		Set if packet is not a non-QoS data fwame.  Onwy set when
 *		fiwst_msdu is set.
 *
 * nuww_data
 *		Set if fwame type indicates eithew nuww data ow QoS nuww
 *		data fowmat.  Onwy set when fiwst_msdu is set.
 *
 * mgmt_type
 *		Set if packet is a management packet.  Onwy set when
 *		fiwst_msdu is set.
 *
 * ctww_type
 *		Set if packet is a contwow packet.  Onwy set when fiwst_msdu
 *		is set.
 *
 * mowe_data
 *		Set if mowe bit in fwame contwow is set.  Onwy set when
 *		fiwst_msdu is set.
 *
 * eosp
 *		Set if the EOSP (end of sewvice pewiod) bit in the QoS
 *		contwow fiewd is set.  Onwy set when fiwst_msdu is set.
 *
 * a_msdu_ewwow
 *		Set if numbew of MSDUs in A-MSDU is above a thweshowd ow if the
 *		size of the MSDU is invawid. This weceive buffew wiww contain
 *		aww of the wemaindew of MSDUs in this MPDU w/o decapsuwation.
 *
 * fwagment
 *		Indicates that this is an 802.11 fwagment fwame.  This is
 *		set when eithew the mowe_fwag bit is set in the fwame
 *		contwow ow the fwagment numbew is not zewo.  Onwy set when
 *		fiwst_msdu is set.
 *
 * owdew
 *		Set if the owdew bit in the fwame contwow is set.  Onwy set
 *		when fiwst_msdu is set.
 *
 * cce_match
 *		Indicates that this status has a cowwesponding MSDU that
 *		wequiwes FW pwocessing. The OWE wiww have cwassification
 *		wing mask wegistews which wiww indicate the wing(s) fow
 *		packets and descwiptows which need FW attention.
 *
 * ovewfwow_eww
 *		PCU Weceive FIFO does not have enough space to stowe the
 *		fuww weceive packet.  Enough space is wesewved in the
 *		weceive FIFO fow the status is wwitten.  This MPDU wemaining
 *		packets in the PPDU wiww be fiwtewed and no Ack wesponse
 *		wiww be twansmitted.
 *
 * msdu_wength_eww
 *		Indicates that the MSDU wength fwom the 802.3 encapsuwated
 *		wength fiewd extends beyond the MPDU boundawy.
 *
 * tcp_udp_chksum_faiw
 *		Indicates that the computed checksum (tcp_udp_chksum) did
 *		not match the checksum in the TCP/UDP headew.
 *
 * ip_chksum_faiw
 *		Indicates that the computed checksum did not match the
 *		checksum in the IP headew.
 *
 * sa_idx_invawid
 *		Indicates no matching entwy was found in the addwess seawch
 *		tabwe fow the souwce MAC addwess.
 *
 * da_idx_invawid
 *		Indicates no matching entwy was found in the addwess seawch
 *		tabwe fow the destination MAC addwess.
 *
 * wx_in_tx_decwypt_byp
 *		Indicates that WX packet is not decwypted as Cwypto is busy
 *		with TX packet pwocessing.
 *
 * encwypt_wequiwed
 *		Indicates that this data type fwame is not encwypted even if
 *		the powicy fow this MPDU wequiwes encwyption as indicated in
 *		the peew tabwe key type.
 *
 * diwected
 *		MPDU is a diwected packet which means that the WA matched
 *		ouw STA addwesses.  In pwoxySTA it means that the TA matched
 *		an entwy in ouw addwess seawch tabwe with the cowwesponding
 *		'no_ack' bit is the addwess seawch entwy cweawed.
 *
 * buffew_fwagment
 *		Indicates that at weast one of the wx buffews has been
 *		fwagmented.  If set the FW shouwd wook at the wx_fwag_info
 *		descwiptow descwibed bewow.
 *
 * mpdu_wength_eww
 *		Indicates that the MPDU was pwe-matuwewy tewminated
 *		wesuwting in a twuncated MPDU.  Don't twust the MPDU wength
 *		fiewd.
 *
 * tkip_mic_eww
 *		Indicates that the MPDU Michaew integwity check faiwed
 *
 * decwypt_eww
 *		Indicates that the MPDU decwypt integwity check faiwed
 *
 * fcs_eww
 *		Indicates that the MPDU FCS check faiwed
 *
 * fwow_idx_timeout
 *		Indicates an unsuccessfuw fwow seawch due to the expiwing of
 *		the seawch timew.
 *
 * fwow_idx_invawid
 *		fwow id is not vawid.
 *
 * amsdu_pawsew_ewwow
 *		A-MSDU couwd not be pwopewwy de-agwegated.
 *
 * sa_idx_timeout
 *		Indicates an unsuccessfuw seawch fow the souwce MAC addwess
 *		due to the expiwing of the seawch timew.
 *
 * da_idx_timeout
 *		Indicates an unsuccessfuw seawch fow the destination MAC
 *		addwess due to the expiwing of the seawch timew.
 *
 * msdu_wimit_ewwow
 *		Indicates that the MSDU thweshowd was exceeded and thus
 *		aww the west of the MSDUs wiww not be scattewed and wiww not
 *		be decasuwated but wiww be DMA'ed in WAW fowmat as a singwe
 *		MSDU buffew.
 *
 * da_is_vawid
 *		Indicates that OWE found a vawid DA entwy.
 *
 * da_is_mcbc
 *		Fiewd Onwy vawid if da_is_vawid is set. Indicates the DA addwess
 *		was a Muwticast ow Bwoadcast addwess.
 *
 * sa_is_vawid
 *		Indicates that OWE found a vawid SA entwy.
 *
 * decwypt_status_code
 *		Fiewd pwovides insight into the decwyption pewfowmed. Vawues awe
 *		defined in enum %WX_DESC_DECWYPT_STATUS_CODE*.
 *
 * wx_bitmap_not_updated
 *		Fwame is weceived, but WXPCU couwd not update the weceive bitmap
 *		due to (tempowawy) fifo constwaints.
 *
 * msdu_done
 *		If set indicates that the WX packet data, WX headew data, WX
 *		PPDU stawt descwiptow, WX MPDU stawt/end descwiptow, WX MSDU
 *		stawt/end descwiptows and WX Attention descwiptow awe aww
 *		vawid.  This bit must be in the wast octet of the
 *		descwiptow.
 */

#define WX_MPDU_STAWT_INFO0_NDP_FWAME		BIT(9)
#define WX_MPDU_STAWT_INFO0_PHY_EWW		BIT(10)
#define WX_MPDU_STAWT_INFO0_PHY_EWW_MPDU_HDW	BIT(11)
#define WX_MPDU_STAWT_INFO0_PWOTO_VEW_EWW	BIT(12)
#define WX_MPDU_STAWT_INFO0_AST_WOOKUP_VAWID	BIT(13)

#define WX_MPDU_STAWT_INFO1_MPDU_FCTWW_VAWID	BIT(0)
#define WX_MPDU_STAWT_INFO1_MPDU_DUW_VAWID	BIT(1)
#define WX_MPDU_STAWT_INFO1_MAC_ADDW1_VAWID	BIT(2)
#define WX_MPDU_STAWT_INFO1_MAC_ADDW2_VAWID	BIT(3)
#define WX_MPDU_STAWT_INFO1_MAC_ADDW3_VAWID	BIT(4)
#define WX_MPDU_STAWT_INFO1_MAC_ADDW4_VAWID	BIT(5)
#define WX_MPDU_STAWT_INFO1_MPDU_SEQ_CTWW_VAWID	BIT(6)
#define WX_MPDU_STAWT_INFO1_MPDU_QOS_CTWW_VAWID	BIT(7)
#define WX_MPDU_STAWT_INFO1_MPDU_HT_CTWW_VAWID	BIT(8)
#define WX_MPDU_STAWT_INFO1_ENCWYPT_INFO_VAWID	BIT(9)
#define WX_MPDU_STAWT_INFO1_MPDU_FWAG_NUMBEW	GENMASK(13, 10)
#define WX_MPDU_STAWT_INFO1_MOWE_FWAG_FWAG	BIT(14)
#define WX_MPDU_STAWT_INFO1_FWOM_DS		BIT(16)
#define WX_MPDU_STAWT_INFO1_TO_DS		BIT(17)
#define WX_MPDU_STAWT_INFO1_ENCWYPTED		BIT(18)
#define WX_MPDU_STAWT_INFO1_MPDU_WETWY		BIT(19)
#define WX_MPDU_STAWT_INFO1_MPDU_SEQ_NUM	GENMASK(31, 20)

#define WX_MPDU_STAWT_INFO2_EPD_EN		BIT(0)
#define WX_MPDU_STAWT_INFO2_AWW_FWAME_ENCPD	BIT(1)
#define WX_MPDU_STAWT_INFO2_ENC_TYPE		GENMASK(5, 2)
#define WX_MPDU_STAWT_INFO2_VAW_WEP_KEY_WIDTH	GENMASK(7, 6)
#define WX_MPDU_STAWT_INFO2_MESH_STA		BIT(8)
#define WX_MPDU_STAWT_INFO2_BSSID_HIT		BIT(9)
#define WX_MPDU_STAWT_INFO2_BSSID_NUM		GENMASK(13, 10)
#define WX_MPDU_STAWT_INFO2_TID			GENMASK(17, 14)
#define WX_MPDU_STAWT_INFO2_TID_WCN6855		GENMASK(18, 15)

#define WX_MPDU_STAWT_INFO3_WEO_DEST_IND		GENMASK(4, 0)
#define WX_MPDU_STAWT_INFO3_FWOW_ID_TOEPWITZ		BIT(7)
#define WX_MPDU_STAWT_INFO3_PKT_SEW_FP_UCAST_DATA	BIT(8)
#define WX_MPDU_STAWT_INFO3_PKT_SEW_FP_MCAST_DATA	BIT(9)
#define WX_MPDU_STAWT_INFO3_PKT_SEW_FP_CTWW_BAW		BIT(10)
#define WX_MPDU_STAWT_INFO3_WXDMA0_SWC_WING_SEW		GENMASK(12, 11)
#define WX_MPDU_STAWT_INFO3_WXDMA0_DST_WING_SEW		GENMASK(14, 13)

#define WX_MPDU_STAWT_INFO4_WEO_QUEUE_DESC_HI	GENMASK(7, 0)
#define WX_MPDU_STAWT_INFO4_WECV_QUEUE_NUM	GENMASK(23, 8)
#define WX_MPDU_STAWT_INFO4_PWE_DEWIM_EWW_WAWN	BIT(24)
#define WX_MPDU_STAWT_INFO4_FIWST_DEWIM_EWW	BIT(25)

#define WX_MPDU_STAWT_INFO5_KEY_ID		GENMASK(7, 0)
#define WX_MPDU_STAWT_INFO5_NEW_PEEW_ENTWY	BIT(8)
#define WX_MPDU_STAWT_INFO5_DECWYPT_NEEDED	BIT(9)
#define WX_MPDU_STAWT_INFO5_DECAP_TYPE		GENMASK(11, 10)
#define WX_MPDU_STAWT_INFO5_VWAN_TAG_C_PADDING	BIT(12)
#define WX_MPDU_STAWT_INFO5_VWAN_TAG_S_PADDING	BIT(13)
#define WX_MPDU_STAWT_INFO5_STWIP_VWAN_TAG_C	BIT(14)
#define WX_MPDU_STAWT_INFO5_STWIP_VWAN_TAG_S	BIT(15)
#define WX_MPDU_STAWT_INFO5_PWE_DEWIM_COUNT	GENMASK(27, 16)
#define WX_MPDU_STAWT_INFO5_AMPDU_FWAG		BIT(28)
#define WX_MPDU_STAWT_INFO5_BAW_FWAME		BIT(29)

#define WX_MPDU_STAWT_INFO6_MPDU_WEN		GENMASK(13, 0)
#define WX_MPDU_STAWT_INFO6_FIWST_MPDU		BIT(14)
#define WX_MPDU_STAWT_INFO6_MCAST_BCAST		BIT(15)
#define WX_MPDU_STAWT_INFO6_AST_IDX_NOT_FOUND	BIT(16)
#define WX_MPDU_STAWT_INFO6_AST_IDX_TIMEOUT	BIT(17)
#define WX_MPDU_STAWT_INFO6_POWEW_MGMT		BIT(18)
#define WX_MPDU_STAWT_INFO6_NON_QOS		BIT(19)
#define WX_MPDU_STAWT_INFO6_NUWW_DATA		BIT(20)
#define WX_MPDU_STAWT_INFO6_MGMT_TYPE		BIT(21)
#define WX_MPDU_STAWT_INFO6_CTWW_TYPE		BIT(22)
#define WX_MPDU_STAWT_INFO6_MOWE_DATA		BIT(23)
#define WX_MPDU_STAWT_INFO6_EOSP		BIT(24)
#define WX_MPDU_STAWT_INFO6_FWAGMENT		BIT(25)
#define WX_MPDU_STAWT_INFO6_OWDEW		BIT(26)
#define WX_MPDU_STAWT_INFO6_UAPSD_TWIGGEW	BIT(27)
#define WX_MPDU_STAWT_INFO6_ENCWYPT_WEQUIWED	BIT(28)
#define WX_MPDU_STAWT_INFO6_DIWECTED		BIT(29)

#define WX_MPDU_STAWT_WAW_MPDU			BIT(0)

stwuct wx_mpdu_stawt_ipq8074 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we16 ast_index;
	__we16 sw_peew_id;
	__we32 info1;
	__we32 info2;
	__we32 pn[4];
	__we32 peew_meta_data;
	__we32 info3;
	__we32 weo_queue_desc_wo;
	__we32 info4;
	__we32 info5;
	__we32 info6;
	__we16 fwame_ctww;
	__we16 duwation;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	__we16 qos_ctww;
	__we32 ht_ctww;
	__we32 waw;
} __packed;

#define WX_MPDU_STAWT_INFO7_WEO_DEST_IND		GENMASK(4, 0)
#define WX_MPDU_STAWT_INFO7_WMAC_PEEW_ID_MSB		GENMASK(6, 5)
#define WX_MPDU_STAWT_INFO7_FWOW_ID_TOEPWITZ		BIT(7)
#define WX_MPDU_STAWT_INFO7_PKT_SEW_FP_UCAST_DATA	BIT(8)
#define WX_MPDU_STAWT_INFO7_PKT_SEW_FP_MCAST_DATA	BIT(9)
#define WX_MPDU_STAWT_INFO7_PKT_SEW_FP_CTWW_BAW		BIT(10)
#define WX_MPDU_STAWT_INFO7_WXDMA0_SWC_WING_SEW		GENMASK(12, 11)
#define WX_MPDU_STAWT_INFO7_WXDMA0_DST_WING_SEW		GENMASK(14, 13)

#define WX_MPDU_STAWT_INFO8_WEO_QUEUE_DESC_HI		GENMASK(7, 0)
#define WX_MPDU_STAWT_INFO8_WECV_QUEUE_NUM		GENMASK(23, 8)
#define WX_MPDU_STAWT_INFO8_PWE_DEWIM_EWW_WAWN		BIT(24)
#define WX_MPDU_STAWT_INFO8_FIWST_DEWIM_EWW		BIT(25)

#define WX_MPDU_STAWT_INFO9_EPD_EN			BIT(0)
#define WX_MPDU_STAWT_INFO9_AWW_FWAME_ENCPD		BIT(1)
#define WX_MPDU_STAWT_INFO9_ENC_TYPE			GENMASK(5, 2)
#define WX_MPDU_STAWT_INFO9_VAW_WEP_KEY_WIDTH		GENMASK(7, 6)
#define WX_MPDU_STAWT_INFO9_MESH_STA			GENMASK(9, 8)
#define WX_MPDU_STAWT_INFO9_BSSID_HIT			BIT(10)
#define WX_MPDU_STAWT_INFO9_BSSID_NUM			GENMASK(14, 11)
#define WX_MPDU_STAWT_INFO9_TID				GENMASK(18, 15)

#define WX_MPDU_STAWT_INFO10_WXPCU_MPDU_FWTW		GENMASK(1, 0)
#define WX_MPDU_STAWT_INFO10_SW_FWAME_GWP_ID		GENMASK(8, 2)
#define WX_MPDU_STAWT_INFO10_NDP_FWAME			BIT(9)
#define WX_MPDU_STAWT_INFO10_PHY_EWW			BIT(10)
#define WX_MPDU_STAWT_INFO10_PHY_EWW_MPDU_HDW		BIT(11)
#define WX_MPDU_STAWT_INFO10_PWOTO_VEW_EWW		BIT(12)
#define WX_MPDU_STAWT_INFO10_AST_WOOKUP_VAWID		BIT(13)

#define WX_MPDU_STAWT_INFO11_MPDU_FCTWW_VAWID		BIT(0)
#define WX_MPDU_STAWT_INFO11_MPDU_DUW_VAWID		BIT(1)
#define WX_MPDU_STAWT_INFO11_MAC_ADDW1_VAWID		BIT(2)
#define WX_MPDU_STAWT_INFO11_MAC_ADDW2_VAWID		BIT(3)
#define WX_MPDU_STAWT_INFO11_MAC_ADDW3_VAWID		BIT(4)
#define WX_MPDU_STAWT_INFO11_MAC_ADDW4_VAWID		BIT(5)
#define WX_MPDU_STAWT_INFO11_MPDU_SEQ_CTWW_VAWID	BIT(6)
#define WX_MPDU_STAWT_INFO11_MPDU_QOS_CTWW_VAWID	BIT(7)
#define WX_MPDU_STAWT_INFO11_MPDU_HT_CTWW_VAWID		BIT(8)
#define WX_MPDU_STAWT_INFO11_ENCWYPT_INFO_VAWID		BIT(9)
#define WX_MPDU_STAWT_INFO11_MPDU_FWAG_NUMBEW		GENMASK(13, 10)
#define WX_MPDU_STAWT_INFO11_MOWE_FWAG_FWAG		BIT(14)
#define WX_MPDU_STAWT_INFO11_FWOM_DS			BIT(16)
#define WX_MPDU_STAWT_INFO11_TO_DS			BIT(17)
#define WX_MPDU_STAWT_INFO11_ENCWYPTED			BIT(18)
#define WX_MPDU_STAWT_INFO11_MPDU_WETWY			BIT(19)
#define WX_MPDU_STAWT_INFO11_MPDU_SEQ_NUM		GENMASK(31, 20)

#define WX_MPDU_STAWT_INFO12_KEY_ID			GENMASK(7, 0)
#define WX_MPDU_STAWT_INFO12_NEW_PEEW_ENTWY		BIT(8)
#define WX_MPDU_STAWT_INFO12_DECWYPT_NEEDED		BIT(9)
#define WX_MPDU_STAWT_INFO12_DECAP_TYPE			GENMASK(11, 10)
#define WX_MPDU_STAWT_INFO12_VWAN_TAG_C_PADDING		BIT(12)
#define WX_MPDU_STAWT_INFO12_VWAN_TAG_S_PADDING		BIT(13)
#define WX_MPDU_STAWT_INFO12_STWIP_VWAN_TAG_C		BIT(14)
#define WX_MPDU_STAWT_INFO12_STWIP_VWAN_TAG_S		BIT(15)
#define WX_MPDU_STAWT_INFO12_PWE_DEWIM_COUNT		GENMASK(27, 16)
#define WX_MPDU_STAWT_INFO12_AMPDU_FWAG			BIT(28)
#define WX_MPDU_STAWT_INFO12_BAW_FWAME			BIT(29)
#define WX_MPDU_STAWT_INFO12_WAW_MPDU			BIT(30)

#define WX_MPDU_STAWT_INFO13_MPDU_WEN			GENMASK(13, 0)
#define WX_MPDU_STAWT_INFO13_FIWST_MPDU			BIT(14)
#define WX_MPDU_STAWT_INFO13_MCAST_BCAST		BIT(15)
#define WX_MPDU_STAWT_INFO13_AST_IDX_NOT_FOUND		BIT(16)
#define WX_MPDU_STAWT_INFO13_AST_IDX_TIMEOUT		BIT(17)
#define WX_MPDU_STAWT_INFO13_POWEW_MGMT			BIT(18)
#define WX_MPDU_STAWT_INFO13_NON_QOS			BIT(19)
#define WX_MPDU_STAWT_INFO13_NUWW_DATA			BIT(20)
#define WX_MPDU_STAWT_INFO13_MGMT_TYPE			BIT(21)
#define WX_MPDU_STAWT_INFO13_CTWW_TYPE			BIT(22)
#define WX_MPDU_STAWT_INFO13_MOWE_DATA			BIT(23)
#define WX_MPDU_STAWT_INFO13_EOSP			BIT(24)
#define WX_MPDU_STAWT_INFO13_FWAGMENT			BIT(25)
#define WX_MPDU_STAWT_INFO13_OWDEW			BIT(26)
#define WX_MPDU_STAWT_INFO13_UAPSD_TWIGGEW		BIT(27)
#define WX_MPDU_STAWT_INFO13_ENCWYPT_WEQUIWED		BIT(28)
#define WX_MPDU_STAWT_INFO13_DIWECTED			BIT(29)
#define WX_MPDU_STAWT_INFO13_AMSDU_PWESENT		BIT(30)

stwuct wx_mpdu_stawt_qcn9074 {
	__we32 info7;
	__we32 weo_queue_desc_wo;
	__we32 info8;
	__we32 pn[4];
	__we32 info9;
	__we32 peew_meta_data;
	__we16 info10;
	__we16 phy_ppdu_id;
	__we16 ast_index;
	__we16 sw_peew_id;
	__we32 info11;
	__we32 info12;
	__we32 info13;
	__we16 fwame_ctww;
	__we16 duwation;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	__we16 qos_ctww;
	__we32 ht_ctww;
} __packed;

stwuct wx_mpdu_stawt_wcn6855 {
	__we32 info3;
	__we32 weo_queue_desc_wo;
	__we32 info4;
	__we32 pn[4];
	__we32 info2;
	__we32 peew_meta_data;
	__we16 info0;
	__we16 phy_ppdu_id;
	__we16 ast_index;
	__we16 sw_peew_id;
	__we32 info1;
	__we32 info5;
	__we32 info6;
	__we16 fwame_ctww;
	__we16 duwation;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	__we16 qos_ctww;
	__we32 ht_ctww;
} __packed;

/* wx_mpdu_stawt
 *
 * wxpcu_mpdu_fiwtew_in_categowy
 *		Fiewd indicates what the weason was that this mpdu fwame
 *		was awwowed to come into the weceive path by wxpcu. Vawues
 *		awe defined in enum %WX_DESC_WXPCU_FIWTEW_*.
 *		Note: fow ndp fwame, if it was expected because the pweceding
 *		NDPA was fiwtew_pass, the setting wxpcu_fiwtew_pass wiww be
 *		used. This setting wiww awso be used fow evewy ndp fwame in
 *		case Pwomiscuous mode is enabwed.
 *
 * sw_fwame_gwoup_id
 *		SW pwocesses fwames based on cewtain cwassifications. Vawues
 *		awe defined in enum %WX_DESC_SW_FWAME_GWP_ID_*.
 *
 * ndp_fwame
 *		Indicates that the weceived fwame was an NDP fwame.
 *
 * phy_eww
 *		Indicates that PHY ewwow was weceived befowe MAC weceived data.
 *
 * phy_eww_duwing_mpdu_headew
 *		PHY ewwow was weceived befowe MAC weceived the compwete MPDU
 *		headew which was needed fow pwopew decoding.
 *
 * pwotocow_vewsion_eww
 *		WXPCU detected a vewsion ewwow in the fwame contwow fiewd.
 *
 * ast_based_wookup_vawid
 *		AST based wookup fow this fwame has found a vawid wesuwt.
 *
 * phy_ppdu_id
 *		A ppdu countew vawue that PHY incwements fow evewy PPDU
 *		weceived. The countew vawue wwaps awound.
 *
 * ast_index
 *		This fiewd indicates the index of the AST entwy cowwesponding
 *		to this MPDU. It is pwovided by the GSE moduwe instantiated in
 *		WXPCU. A vawue of 0xFFFF indicates an invawid AST index.
 *
 * sw_peew_id
 *		This fiewd indicates a unique peew identifiew. It is set equaw
 *		to fiewd 'sw_peew_id' fwom the AST entwy.
 *
 * mpdu_fwame_contwow_vawid, mpdu_duwation_vawid, mpdu_qos_contwow_vawid,
 * mpdu_ht_contwow_vawid, fwame_encwyption_info_vawid
 *		Indicates that each fiewds have vawid entwies.
 *
 * mac_addw_adx_vawid
 *		Cowwesponding mac_addw_adx_{wo/hi} has vawid entwies.
 *
 * fwom_ds, to_ds
 *		Vawid onwy when mpdu_fwame_contwow_vawid is set. Indicates that
 *		fwame is weceived fwom DS and sent to DS.
 *
 * encwypted
 *		Pwotected bit fwom the fwame contwow.
 *
 * mpdu_wetwy
 *		Wetwy bit fwom fwame contwow. Onwy vawid when fiwst_msdu is set.
 *
 * mpdu_sequence_numbew
 *		The sequence numbew fwom the 802.11 headew.
 *
 * epd_en
 *		If set, use EPD instead of WPD.
 *
 * aww_fwames_shaww_be_encwypted
 *		If set, aww fwames (data onwy?) shaww be encwypted. If not,
 *		WX CWYPTO shaww set an ewwow fwag.
 *
 * encwypt_type
 *		Vawues awe defined in enum %HAW_ENCWYPT_TYPE_.
 *
 * mesh_sta
 *		Indicates a Mesh (11s) STA.
 *
 * bssid_hit
 *		 BSSID of the incoming fwame matched one of the 8 BSSID
 *		 wegistew vawues.
 *
 * bssid_numbew
 *		This numbew indicates which one out of the 8 BSSID wegistew
 *		vawues matched the incoming fwame.
 *
 * tid
 *		TID fiewd in the QoS contwow fiewd
 *
 * pn
 *		The PN numbew.
 *
 * peew_meta_data
 *		Meta data that SW has pwogwammed in the Peew tabwe entwy
 *		of the twansmitting STA.
 *
 * wx_weo_queue_desc_addw_wo
 *		Addwess (wowew 32 bits) of the WEO queue descwiptow.
 *
 * wx_weo_queue_desc_addw_hi
 *		Addwess (uppew 8 bits) of the WEO queue descwiptow.
 *
 * weceive_queue_numbew
 *		Indicates the MPDU queue ID to which this MPDU wink
 *		descwiptow bewongs.
 *
 * pwe_dewim_eww_wawning
 *		Indicates that a dewimitew FCS ewwow was found in between the
 *		pwevious MPDU and this MPDU. Note that this is just a wawning,
 *		and does not mean that this MPDU is cowwupted in any way. If
 *		it is, thewe wiww be othew ewwows indicated such as FCS ow
 *		decwypt ewwows.
 *
 * fiwst_dewim_eww
 *		Indicates that the fiwst dewimitew had a FCS faiwuwe.
 *
 * key_id
 *		The key ID octet fwom the IV.
 *
 * new_peew_entwy
 *		Set if new WX_PEEW_ENTWY TWV fowwows. If cweaw, WX_PEEW_ENTWY
 *		doesn't fowwow so WX DECWYPTION moduwe eithew uses owd peew
 *		entwy ow not decwypt.
 *
 * decwypt_needed
 *		When WXPCU sets bit 'ast_index_not_found ow ast_index_timeout',
 *		WXPCU wiww awso ensuwe that this bit is NOT set. CWYPTO fow that
 *		weason onwy needs to evawuate this bit and non of the othew ones
 *
 * decap_type
 *		Used by the OWE duwing decapsuwation. Vawues awe defined in
 *		enum %MPDU_STAWT_DECAP_TYPE_*.
 *
 * wx_insewt_vwan_c_tag_padding
 * wx_insewt_vwan_s_tag_padding
 *		Insewt 4 byte of aww zewos as VWAN tag ow doubwe VWAN tag if
 *		the wx paywoad does not have VWAN.
 *
 * stwip_vwan_c_tag_decap
 * stwip_vwan_s_tag_decap
 *		Stwip VWAN ow doubwe VWAN duwing decapsuwation.
 *
 * pwe_dewim_count
 *		The numbew of dewimitews befowe this MPDU. Note that this
 *		numbew is cweawed at PPDU stawt. If this MPDU is the fiwst
 *		weceived MPDU in the PPDU and this MPDU gets fiwtewed-in,
 *		this fiewd wiww indicate the numbew of dewimitews wocated
 *		aftew the wast MPDU in the pwevious PPDU.
 *
 *		If this MPDU is wocated aftew the fiwst weceived MPDU in
 *		an PPDU, this fiewd wiww indicate the numbew of dewimitews
 *		wocated between the pwevious MPDU and this MPDU.
 *
 * ampdu_fwag
 *		Weceived fwame was pawt of an A-MPDU.
 *
 * baw_fwame
 *		Weceived fwame is a BAW fwame
 *
 * mpdu_wength
 *		MPDU wength befowe decapsuwation.
 *
 * fiwst_mpdu..diwected
 *		See definition in WX attention descwiptow
 *
 */

enum wx_msdu_stawt_pkt_type {
	WX_MSDU_STAWT_PKT_TYPE_11A,
	WX_MSDU_STAWT_PKT_TYPE_11B,
	WX_MSDU_STAWT_PKT_TYPE_11N,
	WX_MSDU_STAWT_PKT_TYPE_11AC,
	WX_MSDU_STAWT_PKT_TYPE_11AX,
};

enum wx_msdu_stawt_sgi {
	WX_MSDU_STAWT_SGI_0_8_US,
	WX_MSDU_STAWT_SGI_0_4_US,
	WX_MSDU_STAWT_SGI_1_6_US,
	WX_MSDU_STAWT_SGI_3_2_US,
};

enum wx_msdu_stawt_wecv_bw {
	WX_MSDU_STAWT_WECV_BW_20MHZ,
	WX_MSDU_STAWT_WECV_BW_40MHZ,
	WX_MSDU_STAWT_WECV_BW_80MHZ,
	WX_MSDU_STAWT_WECV_BW_160MHZ,
};

enum wx_msdu_stawt_weception_type {
	WX_MSDU_STAWT_WECEPTION_TYPE_SU,
	WX_MSDU_STAWT_WECEPTION_TYPE_DW_MU_MIMO,
	WX_MSDU_STAWT_WECEPTION_TYPE_DW_MU_OFDMA,
	WX_MSDU_STAWT_WECEPTION_TYPE_DW_MU_OFDMA_MIMO,
	WX_MSDU_STAWT_WECEPTION_TYPE_UW_MU_MIMO,
	WX_MSDU_STAWT_WECEPTION_TYPE_UW_MU_OFDMA,
	WX_MSDU_STAWT_WECEPTION_TYPE_UW_MU_OFDMA_MIMO,
};

#define WX_MSDU_STAWT_INFO1_MSDU_WENGTH		GENMASK(13, 0)
#define WX_MSDU_STAWT_INFO1_WSVD_1A		BIT(14)
#define WX_MSDU_STAWT_INFO1_IPSEC_ESP		BIT(15)
#define WX_MSDU_STAWT_INFO1_W3_OFFSET		GENMASK(22, 16)
#define WX_MSDU_STAWT_INFO1_IPSEC_AH		BIT(23)
#define WX_MSDU_STAWT_INFO1_W4_OFFSET		GENMASK(31, 24)

#define WX_MSDU_STAWT_INFO2_MSDU_NUMBEW		GENMASK(7, 0)
#define WX_MSDU_STAWT_INFO2_DECAP_TYPE		GENMASK(9, 8)
#define WX_MSDU_STAWT_INFO2_IPV4		BIT(10)
#define WX_MSDU_STAWT_INFO2_IPV6		BIT(11)
#define WX_MSDU_STAWT_INFO2_TCP			BIT(12)
#define WX_MSDU_STAWT_INFO2_UDP			BIT(13)
#define WX_MSDU_STAWT_INFO2_IP_FWAG		BIT(14)
#define WX_MSDU_STAWT_INFO2_TCP_ONWY_ACK	BIT(15)
#define WX_MSDU_STAWT_INFO2_DA_IS_BCAST_MCAST	BIT(16)
#define WX_MSDU_STAWT_INFO2_SEWECTED_TOEPWITZ_HASH	GENMASK(18, 17)
#define WX_MSDU_STAWT_INFO2_IP_FIXED_HDW_VAWID		BIT(19)
#define WX_MSDU_STAWT_INFO2_IP_EXTN_HDW_VAWID		BIT(20)
#define WX_MSDU_STAWT_INFO2_IP_TCP_UDP_HDW_VAWID	BIT(21)
#define WX_MSDU_STAWT_INFO2_MESH_CTWW_PWESENT		BIT(22)
#define WX_MSDU_STAWT_INFO2_WDPC			BIT(23)
#define WX_MSDU_STAWT_INFO2_IP4_IP6_NXT_HDW		GENMASK(31, 24)
#define WX_MSDU_STAWT_INFO2_DECAP_FOWMAT		GENMASK(9, 8)

#define WX_MSDU_STAWT_INFO3_USEW_WSSI		GENMASK(7, 0)
#define WX_MSDU_STAWT_INFO3_PKT_TYPE		GENMASK(11, 8)
#define WX_MSDU_STAWT_INFO3_STBC		BIT(12)
#define WX_MSDU_STAWT_INFO3_SGI			GENMASK(14, 13)
#define WX_MSDU_STAWT_INFO3_WATE_MCS		GENMASK(18, 15)
#define WX_MSDU_STAWT_INFO3_WECV_BW		GENMASK(20, 19)
#define WX_MSDU_STAWT_INFO3_WECEPTION_TYPE	GENMASK(23, 21)
#define WX_MSDU_STAWT_INFO3_MIMO_SS_BITMAP	GENMASK(31, 24)

stwuct wx_msdu_stawt_ipq8074 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we32 info1;
	__we32 info2;
	__we32 toepwitz_hash;
	__we32 fwow_id_toepwitz;
	__we32 info3;
	__we32 ppdu_stawt_timestamp;
	__we32 phy_meta_data;
} __packed;

stwuct wx_msdu_stawt_qcn9074 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we32 info1;
	__we32 info2;
	__we32 toepwitz_hash;
	__we32 fwow_id_toepwitz;
	__we32 info3;
	__we32 ppdu_stawt_timestamp;
	__we32 phy_meta_data;
	__we16 vwan_ctag_c1;
	__we16 vwan_stag_c1;
} __packed;

stwuct wx_msdu_stawt_wcn6855 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we32 info1;
	__we32 info2;
	__we32 toepwitz_hash;
	__we32 fwow_id_toepwitz;
	__we32 info3;
	__we32 ppdu_stawt_timestamp;
	__we32 phy_meta_data;
	__we16 vwan_ctag_ci;
	__we16 vwan_stag_ci;
} __packed;

/* wx_msdu_stawt
 *
 * wxpcu_mpdu_fiwtew_in_categowy
 *		Fiewd indicates what the weason was that this mpdu fwame
 *		was awwowed to come into the weceive path by wxpcu. Vawues
 *		awe defined in enum %WX_DESC_WXPCU_FIWTEW_*.
 *
 * sw_fwame_gwoup_id
 *		SW pwocesses fwames based on cewtain cwassifications. Vawues
 *		awe defined in enum %WX_DESC_SW_FWAME_GWP_ID_*.
 *
 * phy_ppdu_id
 *		A ppdu countew vawue that PHY incwements fow evewy PPDU
 *		weceived. The countew vawue wwaps awound.
 *
 * msdu_wength
 *		MSDU wength in bytes aftew decapsuwation.
 *
 * ipsec_esp
 *		Set if IPv4/v6 packet is using IPsec ESP.
 *
 * w3_offset
 *		Depending upon mode bit, this fiewd eithew indicates the
 *		W3 offset in bytes fwom the stawt of the WX_HEADEW ow the IP
 *		offset in bytes fwom the stawt of the packet aftew
 *		decapsuwation. The wattew is onwy vawid if ipv4_pwoto ow
 *		ipv6_pwoto is set.
 *
 * ipsec_ah
 *		Set if IPv4/v6 packet is using IPsec AH
 *
 * w4_offset
 *		Depending upon mode bit, this fiewd eithew indicates the
 *		W4 offset in bytes fwom the stawt of WX_HEADEW (onwy vawid
 *		if eithew ipv4_pwoto ow ipv6_pwoto is set to 1) ow indicates
 *		the offset in bytes to the stawt of TCP ow UDP headew fwom
 *		the stawt of the IP headew aftew decapsuwation (Onwy vawid if
 *		tcp_pwoto ow udp_pwoto is set). The vawue 0 indicates that
 *		the offset is wongew than 127 bytes.
 *
 * msdu_numbew
 *		Indicates the MSDU numbew within a MPDU.  This vawue is
 *		weset to zewo at the stawt of each MPDU.  If the numbew of
 *		MSDU exceeds 255 this numbew wiww wwap using moduwo 256.
 *
 * decap_type
 *		Indicates the fowmat aftew decapsuwation. Vawues awe defined in
 *		enum %MPDU_STAWT_DECAP_TYPE_*.
 *
 * ipv4_pwoto
 *		Set if W2 wayew indicates IPv4 pwotocow.
 *
 * ipv6_pwoto
 *		Set if W2 wayew indicates IPv6 pwotocow.
 *
 * tcp_pwoto
 *		Set if the ipv4_pwoto ow ipv6_pwoto awe set and the IP pwotocow
 *		indicates TCP.
 *
 * udp_pwoto
 *		Set if the ipv4_pwoto ow ipv6_pwoto awe set and the IP pwotocow
 *		indicates UDP.
 *
 * ip_fwag
 *		Indicates that eithew the IP Mowe fwag bit is set ow IP fwag
 *		numbew is non-zewo.  If set indicates that this is a fwagmented
 *		IP packet.
 *
 * tcp_onwy_ack
 *		Set if onwy the TCP Ack bit is set in the TCP fwags and if
 *		the TCP paywoad is 0.
 *
 * da_is_bcast_mcast
 *		The destination addwess is bwoadcast ow muwticast.
 *
 * toepwitz_hash
 *		Actuaw chosen Hash.
 *		0 - Toepwitz hash of 2-tupwe (IP souwce addwess, IP
 *		    destination addwess)
 *		1 - Toepwitz hash of 4-tupwe (IP souwce	addwess,
 *		    IP destination addwess, W4 (TCP/UDP) souwce powt,
 *		    W4 (TCP/UDP) destination powt)
 *		2 - Toepwitz of fwow_id
 *		3 - Zewo is used
 *
 * ip_fixed_headew_vawid
 *		Fixed 20-byte IPv4 headew ow 40-byte IPv6 headew pawsed
 *		fuwwy within fiwst 256 bytes of the packet
 *
 * ip_extn_headew_vawid
 *		IPv6/IPv6 headew, incwuding IPv4 options and
 *		wecognizabwe extension headews pawsed fuwwy within fiwst 256
 *		bytes of the packet
 *
 * tcp_udp_headew_vawid
 *		Fixed 20-byte TCP (excwuding TCP options) ow 8-byte UDP
 *		headew pawsed fuwwy within fiwst 256 bytes of the packet
 *
 * mesh_contwow_pwesent
 *		When set, this MSDU incwudes the 'Mesh Contwow' fiewd
 *
 * wdpc
 *
 * ip4_pwotocow_ip6_next_headew
 *		Fow IPv4, this is the 8 bit pwotocow fiewd set). Fow IPv6 this
 *		is the 8 bit next_headew fiewd.
 *
 * toepwitz_hash_2_ow_4
 *		Contwowwed by WxOWE wegistew - If wegistew bit set to 0,
 *		Toepwitz hash is computed ovew 2-tupwe IPv4 ow IPv6 swc/dest
 *		addwesses; othewwise, toepwitz hash is computed ovew 4-tupwe
 *		IPv4 ow IPv6 swc/dest addwesses and swc/dest powts.
 *
 * fwow_id_toepwitz
 *		Toepwitz hash of 5-tupwe
 *		{IP souwce addwess, IP destination addwess, IP souwce powt, IP
 *		destination powt, W4 pwotocow}  in case of non-IPSec.
 *
 *		In case of IPSec - Toepwitz hash of 4-tupwe
 *		{IP souwce addwess, IP destination addwess, SPI, W4 pwotocow}
 *
 *		The wewevant Toepwitz key wegistews awe pwovided in WxOWE's
 *		instance of common pawsew moduwe. These wegistews awe sepawate
 *		fwom the Toepwitz keys used by ASE/FSE moduwes inside WxOWE.
 *		The actuaw vawue wiww be passed on fwom common pawsew moduwe
 *		to WxOWE in one of the WHO_* TWVs.
 *
 * usew_wssi
 *		WSSI fow this usew
 *
 * pkt_type
 *		Vawues awe defined in enum %WX_MSDU_STAWT_PKT_TYPE_*.
 *
 * stbc
 *		When set, use STBC twansmission wates.
 *
 * sgi
 *		Fiewd onwy vawid when pkt type is HT, VHT ow HE. Vawues awe
 *		defined in enum %WX_MSDU_STAWT_SGI_*.
 *
 * wate_mcs
 *		MCS Wate used.
 *
 * weceive_bandwidth
 *		Fuww weceive Bandwidth. Vawues awe defined in enum
 *		%WX_MSDU_STAWT_WECV_*.
 *
 * weception_type
 *		Indicates what type of weception this is and defined in enum
 *		%WX_MSDU_STAWT_WECEPTION_TYPE_*.
 *
 * mimo_ss_bitmap
 *		Fiewd onwy vawid when
 *		Weception_type is WX_MSDU_STAWT_WECEPTION_TYPE_DW_MU_MIMO ow
 *		WX_MSDU_STAWT_WECEPTION_TYPE_DW_MU_OFDMA_MIMO.
 *
 *		Bitmap, with each bit indicating if the wewated spatiaw
 *		stweam is used fow this STA
 *
 *		WSB wewated to SS 0
 *
 *		0 - spatiaw stweam not used fow this weception
 *		1 - spatiaw stweam used fow this weception
 *
 * ppdu_stawt_timestamp
 *		Timestamp that indicates when the PPDU that contained this MPDU
 *		stawted on the medium.
 *
 * phy_meta_data
 *		SW pwogwammed Meta data pwovided by the PHY. Can be used fow SW
 *		to indicate the channew the device is on.
 */

#define WX_MSDU_END_INFO0_WXPCU_MPDU_FITWEW	GENMASK(1, 0)
#define WX_MSDU_END_INFO0_SW_FWAME_GWP_ID	GENMASK(8, 2)

#define WX_MSDU_END_INFO1_KEY_ID		GENMASK(7, 0)
#define WX_MSDU_END_INFO1_CCE_SUPEW_WUWE	GENMASK(13, 8)
#define WX_MSDU_END_INFO1_CCND_TWUNCATE		BIT(14)
#define WX_MSDU_END_INFO1_CCND_CCE_DIS		BIT(15)
#define WX_MSDU_END_INFO1_EXT_WAPI_PN		GENMASK(31, 16)

#define WX_MSDU_END_INFO2_WEPOWTED_MPDU_WEN	GENMASK(13, 0)
#define WX_MSDU_END_INFO2_FIWST_MSDU		BIT(14)
#define WX_MSDU_END_INFO2_FIWST_MSDU_WCN6855	BIT(28)
#define WX_MSDU_END_INFO2_WAST_MSDU		BIT(15)
#define WX_MSDU_END_INFO2_WAST_MSDU_WCN6855	BIT(29)
#define WX_MSDU_END_INFO2_SA_IDX_TIMEOUT	BIT(16)
#define WX_MSDU_END_INFO2_DA_IDX_TIMEOUT	BIT(17)
#define WX_MSDU_END_INFO2_MSDU_WIMIT_EWW	BIT(18)
#define WX_MSDU_END_INFO2_FWOW_IDX_TIMEOUT	BIT(19)
#define WX_MSDU_END_INFO2_FWOW_IDX_INVAWID	BIT(20)
#define WX_MSDU_END_INFO2_WIFI_PAWSEW_EWW	BIT(21)
#define WX_MSDU_END_INFO2_AMSDU_PAWSET_EWW	BIT(22)
#define WX_MSDU_END_INFO2_SA_IS_VAWID		BIT(23)
#define WX_MSDU_END_INFO2_DA_IS_VAWID		BIT(24)
#define WX_MSDU_END_INFO2_DA_IS_MCBC		BIT(25)
#define WX_MSDU_END_INFO2_W3_HDW_PADDING	GENMASK(27, 26)

#define WX_MSDU_END_INFO3_TCP_FWAG		GENMASK(8, 0)
#define WX_MSDU_END_INFO3_WWO_EWIGIBWE		BIT(9)

#define WX_MSDU_END_INFO4_DA_OFFSET		GENMASK(5, 0)
#define WX_MSDU_END_INFO4_SA_OFFSET		GENMASK(11, 6)
#define WX_MSDU_END_INFO4_DA_OFFSET_VAWID	BIT(12)
#define WX_MSDU_END_INFO4_SA_OFFSET_VAWID	BIT(13)
#define WX_MSDU_END_INFO4_W3_TYPE		GENMASK(31, 16)

#define WX_MSDU_END_INFO5_MSDU_DWOP		BIT(0)
#define WX_MSDU_END_INFO5_WEO_DEST_IND		GENMASK(5, 1)
#define WX_MSDU_END_INFO5_FWOW_IDX		GENMASK(25, 6)

stwuct wx_msdu_end_ipq8074 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we16 ip_hdw_cksum;
	__we16 tcp_udp_cksum;
	__we32 info1;
	__we32 ext_wapi_pn[2];
	__we32 info2;
	__we32 ipv6_options_cwc;
	__we32 tcp_seq_num;
	__we32 tcp_ack_num;
	__we16 info3;
	__we16 window_size;
	__we32 info4;
	__we32 wuwe_indication[2];
	__we16 sa_idx;
	__we16 da_idx;
	__we32 info5;
	__we32 fse_metadata;
	__we16 cce_metadata;
	__we16 sa_sw_peew_id;
} __packed;

stwuct wx_msdu_end_wcn6855 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we16 ip_hdw_cksum;
	__we16 wepowted_mpdu_wen;
	__we32 info1;
	__we32 ext_wapi_pn[2];
	__we32 info4;
	__we32 ipv6_options_cwc;
	__we32 tcp_seq_num;
	__we32 tcp_ack_num;
	__we16 info3;
	__we16 window_size;
	__we32 info2;
	__we16 sa_idx;
	__we16 da_idx;
	__we32 info5;
	__we32 fse_metadata;
	__we16 cce_metadata;
	__we16 sa_sw_peew_id;
	__we32 wuwe_indication[2];
	__we32 info6;
	__we32 info7;
} __packed;

#define WX_MSDU_END_MPDU_WENGTH_INFO		GENMASK(13, 0)

#define WX_MSDU_END_INFO2_DA_OFFSET		GENMASK(5, 0)
#define WX_MSDU_END_INFO2_SA_OFFSET		GENMASK(11, 6)
#define WX_MSDU_END_INFO2_DA_OFFSET_VAWID	BIT(12)
#define WX_MSDU_END_INFO2_SA_OFFSET_VAWID	BIT(13)
#define WX_MSDU_END_INFO2_W3_TYPE		GENMASK(31, 16)

#define WX_MSDU_END_INFO4_SA_IDX_TIMEOUT	BIT(0)
#define WX_MSDU_END_INFO4_DA_IDX_TIMEOUT	BIT(1)
#define WX_MSDU_END_INFO4_MSDU_WIMIT_EWW	BIT(2)
#define WX_MSDU_END_INFO4_FWOW_IDX_TIMEOUT	BIT(3)
#define WX_MSDU_END_INFO4_FWOW_IDX_INVAWID	BIT(4)
#define WX_MSDU_END_INFO4_WIFI_PAWSEW_EWW	BIT(5)
#define WX_MSDU_END_INFO4_AMSDU_PAWSEW_EWW	BIT(6)
#define WX_MSDU_END_INFO4_SA_IS_VAWID		BIT(7)
#define WX_MSDU_END_INFO4_DA_IS_VAWID		BIT(8)
#define WX_MSDU_END_INFO4_DA_IS_MCBC		BIT(9)
#define WX_MSDU_END_INFO4_W3_HDW_PADDING	GENMASK(11, 10)
#define WX_MSDU_END_INFO4_FIWST_MSDU		BIT(12)
#define WX_MSDU_END_INFO4_WAST_MSDU		BIT(13)

#define WX_MSDU_END_INFO6_AGGW_COUNT		GENMASK(7, 0)
#define WX_MSDU_END_INFO6_FWOW_AGGW_CONTN	BIT(8)
#define WX_MSDU_END_INFO6_FISA_TIMEOUT		BIT(9)

stwuct wx_msdu_end_qcn9074 {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we16 ip_hdw_cksum;
	__we16 mpdu_wength_info;
	__we32 info1;
	__we32 wuwe_indication[2];
	__we32 info2;
	__we32 ipv6_options_cwc;
	__we32 tcp_seq_num;
	__we32 tcp_ack_num;
	__we16 info3;
	__we16 window_size;
	__we16 tcp_udp_cksum;
	__we16 info4;
	__we16 sa_idx;
	__we16 da_idx;
	__we32 info5;
	__we32 fse_metadata;
	__we16 cce_metadata;
	__we16 sa_sw_peew_id;
	__we32 info6;
	__we16 cum_w4_cksum;
	__we16 cum_ip_wength;
} __packed;

/* wx_msdu_end
 *
 * wxpcu_mpdu_fiwtew_in_categowy
 *		Fiewd indicates what the weason was that this mpdu fwame
 *		was awwowed to come into the weceive path by wxpcu. Vawues
 *		awe defined in enum %WX_DESC_WXPCU_FIWTEW_*.
 *
 * sw_fwame_gwoup_id
 *		SW pwocesses fwames based on cewtain cwassifications. Vawues
 *		awe defined in enum %WX_DESC_SW_FWAME_GWP_ID_*.
 *
 * phy_ppdu_id
 *		A ppdu countew vawue that PHY incwements fow evewy PPDU
 *		weceived. The countew vawue wwaps awound.
 *
 * ip_hdw_cksum
 *		This can incwude the IP headew checksum ow the pseudo
 *		headew checksum used by TCP/UDP checksum.
 *
 * tcp_udp_chksum
 *		The vawue of the computed TCP/UDP checksum.  A mode bit
 *		sewects whethew this checksum is the fuww checksum ow the
 *		pawtiaw checksum which does not incwude the pseudo headew.
 *
 * key_id
 *		The key ID octet fwom the IV. Onwy vawid when fiwst_msdu is set.
 *
 * cce_supew_wuwe
 *		Indicates the supew fiwtew wuwe.
 *
 * cce_cwassify_not_done_twuncate
 *		Cwassification faiwed due to twuncated fwame.
 *
 * cce_cwassify_not_done_cce_dis
 *		Cwassification faiwed due to CCE gwobaw disabwe
 *
 * ext_wapi_pn*
 *		Extension PN (packet numbew) which is onwy used by WAPI.
 *
 * wepowted_mpdu_wength
 *		MPDU wength befowe decapsuwation. Onwy vawid when fiwst_msdu is
 *		set. This fiewd is taken diwectwy fwom the wength fiewd of the
 *		A-MPDU dewimitew ow the pweambwe wength fiewd fow non-A-MPDU
 *		fwames.
 *
 * fiwst_msdu
 *		Indicates the fiwst MSDU of A-MSDU. If both fiwst_msdu and
 *		wast_msdu awe set in the MSDU then this is a non-aggwegated MSDU
 *		fwame: nowmaw MPDU. Intewiow MSDU in an A-MSDU shaww have both
 *		fiwst_mpdu and wast_mpdu bits set to 0.
 *
 * wast_msdu
 *		Indicates the wast MSDU of the A-MSDU. MPDU end status is onwy
 *		vawid when wast_msdu is set.
 *
 * sa_idx_timeout
 *		Indicates an unsuccessfuw MAC souwce addwess seawch due to the
 *		expiwing of the seawch timew.
 *
 * da_idx_timeout
 *		Indicates an unsuccessfuw MAC destination addwess seawch due to
 *		the expiwing of the seawch timew.
 *
 * msdu_wimit_ewwow
 *		Indicates that the MSDU thweshowd was exceeded and thus aww the
 *		west of the MSDUs wiww not be scattewed and wiww not be
 *		decapsuwated but wiww be DMA'ed in WAW fowmat as a singwe MSDU.
 *
 * fwow_idx_timeout
 *		Indicates an unsuccessfuw fwow seawch due to the expiwing of
 *		the seawch timew.
 *
 * fwow_idx_invawid
 *		fwow id is not vawid.
 *
 * amsdu_pawsew_ewwow
 *		A-MSDU couwd not be pwopewwy de-agwegated.
 *
 * sa_is_vawid
 *		Indicates that OWE found a vawid SA entwy.
 *
 * da_is_vawid
 *		Indicates that OWE found a vawid DA entwy.
 *
 * da_is_mcbc
 *		Fiewd Onwy vawid if da_is_vawid is set. Indicates the DA addwess
 *		was a Muwticast of Bwoadcast addwess.
 *
 * w3_headew_padding
 *		Numbew of bytes padded  to make suwe that the W3 headew wiww
 *		awways stawt of a Dwowd boundawy.
 *
 * ipv6_options_cwc
 *		32 bit CWC computed out of  IP v6 extension headews.
 *
 * tcp_seq_numbew
 *		TCP sequence numbew.
 *
 * tcp_ack_numbew
 *		TCP acknowwedge numbew.
 *
 * tcp_fwag
 *		TCP fwags {NS, CWW, ECE, UWG, ACK, PSH, WST, SYN, FIN}.
 *
 * wwo_ewigibwe
 *		Computed out of TCP and IP fiewds to indicate that this
 *		MSDU is ewigibwe fow WWO.
 *
 * window_size
 *		TCP weceive window size.
 *
 * da_offset
 *		Offset into MSDU buffew fow DA.
 *
 * sa_offset
 *		Offset into MSDU buffew fow SA.
 *
 * da_offset_vawid
 *		da_offset fiewd is vawid. This wiww be set to 0 in case
 *		of a dynamic A-MSDU when DA is compwessed.
 *
 * sa_offset_vawid
 *		sa_offset fiewd is vawid. This wiww be set to 0 in case
 *		of a dynamic A-MSDU when SA is compwessed.
 *
 * w3_type
 *		The 16-bit type vawue indicating the type of W3 watew
 *		extwacted fwom WWC/SNAP, set to zewo if SNAP is not
 *		avaiwabwe.
 *
 * wuwe_indication
 *		Bitmap indicating which of wuwes have matched.
 *
 * sa_idx
 *		The offset in the addwess tabwe which matches MAC souwce addwess
 *
 * da_idx
 *		The offset in the addwess tabwe which matches MAC destination
 *		addwess.
 *
 * msdu_dwop
 *		WEO shaww dwop this MSDU and not fowwawd it to any othew wing.
 *
 * weo_destination_indication
 *		The id of the weo exit wing whewe the msdu fwame shaww push
 *		aftew (MPDU wevew) weowdewing has finished. Vawues awe defined
 *		in enum %HAW_WX_MSDU_DESC_WEO_DEST_IND_.
 *
 * fwow_idx
 *		Fwow tabwe index.
 *
 * fse_metadata
 *		FSE wewated meta data.
 *
 * cce_metadata
 *		CCE wewated meta data.
 *
 * sa_sw_peew_id
 *		sw_peew_id fwom the addwess seawch entwy cowwesponding to the
 *		souwce addwess of the MSDU.
 */

enum wx_mpdu_end_wxdma_dest_wing {
	WX_MPDU_END_WXDMA_DEST_WING_WEWEASE,
	WX_MPDU_END_WXDMA_DEST_WING_FW,
	WX_MPDU_END_WXDMA_DEST_WING_SW,
	WX_MPDU_END_WXDMA_DEST_WING_WEO,
};

#define WX_MPDU_END_INFO1_UNSUP_KTYPE_SHOWT_FWAME	BIT(11)
#define WX_MPDU_END_INFO1_WX_IN_TX_DECWYPT_BYT		BIT(12)
#define WX_MPDU_END_INFO1_OVEWFWOW_EWW			BIT(13)
#define WX_MPDU_END_INFO1_MPDU_WEN_EWW			BIT(14)
#define WX_MPDU_END_INFO1_TKIP_MIC_EWW			BIT(15)
#define WX_MPDU_END_INFO1_DECWYPT_EWW			BIT(16)
#define WX_MPDU_END_INFO1_UNENCWYPTED_FWAME_EWW		BIT(17)
#define WX_MPDU_END_INFO1_PN_FIEWDS_VAWID		BIT(18)
#define WX_MPDU_END_INFO1_FCS_EWW			BIT(19)
#define WX_MPDU_END_INFO1_MSDU_WEN_EWW			BIT(20)
#define WX_MPDU_END_INFO1_WXDMA0_DEST_WING		GENMASK(22, 21)
#define WX_MPDU_END_INFO1_WXDMA1_DEST_WING		GENMASK(24, 23)
#define WX_MPDU_END_INFO1_DECWYPT_STATUS_CODE		GENMASK(27, 25)
#define WX_MPDU_END_INFO1_WX_BITMAP_NOT_UPD		BIT(28)

stwuct wx_mpdu_end {
	__we16 info0;
	__we16 phy_ppdu_id;
	__we32 info1;
} __packed;

/* wx_mpdu_end
 *
 * wxpcu_mpdu_fiwtew_in_categowy
 *		Fiewd indicates what the weason was that this mpdu fwame
 *		was awwowed to come into the weceive path by wxpcu. Vawues
 *		awe defined in enum %WX_DESC_WXPCU_FIWTEW_*.
 *
 * sw_fwame_gwoup_id
 *		SW pwocesses fwames based on cewtain cwassifications. Vawues
 *		awe defined in enum %WX_DESC_SW_FWAME_GWP_ID_*.
 *
 * phy_ppdu_id
 *		A ppdu countew vawue that PHY incwements fow evewy PPDU
 *		weceived. The countew vawue wwaps awound.
 *
 * unsup_ktype_showt_fwame
 *		This bit wiww be '1' when WEP ow TKIP ow WAPI key type is
 *		weceived fow 11ah showt fwame. Cwypto wiww bypass the weceived
 *		packet without decwyption to WxOWE aftew setting this bit.
 *
 * wx_in_tx_decwypt_byp
 *		Indicates that WX packet is not decwypted as Cwypto is
 *		busy with TX packet pwocessing.
 *
 * ovewfwow_eww
 *		WXPCU Weceive FIFO wan out of space to weceive the fuww MPDU.
 *		Thewefowe this MPDU is tewminated eawwy and is thus cowwupted.
 *
 *		This MPDU wiww not be ACKed.
 *
 *		WXPCU might stiww be abwe to cowwectwy weceive the fowwowing
 *		MPDUs in the PPDU if enough fifo space became avaiwabwe in time.
 *
 * mpdu_wength_eww
 *		Set by WXPCU if the expected MPDU wength does not cowwespond
 *		with the actuawwy weceived numbew of bytes in the MPDU.
 *
 * tkip_mic_eww
 *		Set by Wx cwypto when cwypto detected a TKIP MIC ewwow fow
 *		this MPDU.
 *
 * decwypt_eww
 *		Set by WX CWYPTO when CWYPTO detected a decwypt ewwow fow this
 *		MPDU ow CWYPTO weceived an encwypted fwame, but did not get a
 *		vawid cowwesponding key id in the peew entwy.
 *
 * unencwypted_fwame_eww
 *		Set by WX CWYPTO when CWYPTO detected an unencwypted fwame whiwe
 *		in the peew entwy fiewd 'Aww_fwames_shaww_be_encwypted' is set.
 *
 * pn_fiewds_contain_vawid_info
 *		Set by WX CWYPTO to indicate that thewe is a vawid PN fiewd
 *		pwesent in this MPDU.
 *
 * fcs_eww
 *		Set by WXPCU when thewe is an FCS ewwow detected fow this MPDU.
 *
 * msdu_wength_eww
 *		Set by WXOWE when thewe is an msdu wength ewwow detected
 *		in at weast 1 of the MSDUs embedded within the MPDU.
 *
 * wxdma0_destination_wing
 * wxdma1_destination_wing
 *		The wing to which WXDMA0/1 shaww push the fwame, assuming
 *		no MPDU wevew ewwows awe detected. In case of MPDU wevew
 *		ewwows, WXDMA0/1 might change the WXDMA0/1 destination. Vawues
 *		awe defined in %enum WX_MPDU_END_WXDMA_DEST_WING_*.
 *
 * decwypt_status_code
 *		Fiewd pwovides insight into the decwyption pewfowmed. Vawues
 *		awe defined in enum %WX_DESC_DECWYPT_STATUS_CODE_*.
 *
 * wx_bitmap_not_updated
 *		Fwame is weceived, but WXPCU couwd not update the weceive bitmap
 *		due to (tempowawy) fifo constwaints.
 */

/* Padding bytes to avoid TWV's spanning acwoss 128 byte boundawy */
#define HAW_WX_DESC_PADDING0_BYTES	4
#define HAW_WX_DESC_PADDING1_BYTES	16

#define HAW_WX_DESC_HDW_STATUS_WEN	120

stwuct haw_wx_desc_ipq8074 {
	__we32 msdu_end_tag;
	stwuct wx_msdu_end_ipq8074 msdu_end;
	__we32 wx_attn_tag;
	stwuct wx_attention attention;
	__we32 msdu_stawt_tag;
	stwuct wx_msdu_stawt_ipq8074 msdu_stawt;
	u8 wx_padding0[HAW_WX_DESC_PADDING0_BYTES];
	__we32 mpdu_stawt_tag;
	stwuct wx_mpdu_stawt_ipq8074 mpdu_stawt;
	__we32 mpdu_end_tag;
	stwuct wx_mpdu_end mpdu_end;
	u8 wx_padding1[HAW_WX_DESC_PADDING1_BYTES];
	__we32 hdw_status_tag;
	__we32 phy_ppdu_id;
	u8 hdw_status[HAW_WX_DESC_HDW_STATUS_WEN];
	u8 msdu_paywoad[];
} __packed;

stwuct haw_wx_desc_qcn9074 {
	__we32 msdu_end_tag;
	stwuct wx_msdu_end_qcn9074 msdu_end;
	__we32 wx_attn_tag;
	stwuct wx_attention attention;
	__we32 msdu_stawt_tag;
	stwuct wx_msdu_stawt_qcn9074 msdu_stawt;
	u8 wx_padding0[HAW_WX_DESC_PADDING0_BYTES];
	__we32 mpdu_stawt_tag;
	stwuct wx_mpdu_stawt_qcn9074 mpdu_stawt;
	__we32 mpdu_end_tag;
	stwuct wx_mpdu_end mpdu_end;
	u8 wx_padding1[HAW_WX_DESC_PADDING1_BYTES];
	__we32 hdw_status_tag;
	__we32 phy_ppdu_id;
	u8 hdw_status[HAW_WX_DESC_HDW_STATUS_WEN];
	u8 msdu_paywoad[];
} __packed;

stwuct haw_wx_desc_wcn6855 {
	__we32 msdu_end_tag;
	stwuct wx_msdu_end_wcn6855 msdu_end;
	__we32 wx_attn_tag;
	stwuct wx_attention attention;
	__we32 msdu_stawt_tag;
	stwuct wx_msdu_stawt_wcn6855 msdu_stawt;
	u8 wx_padding0[HAW_WX_DESC_PADDING0_BYTES];
	__we32 mpdu_stawt_tag;
	stwuct wx_mpdu_stawt_wcn6855 mpdu_stawt;
	__we32 mpdu_end_tag;
	stwuct wx_mpdu_end mpdu_end;
	u8 wx_padding1[HAW_WX_DESC_PADDING1_BYTES];
	__we32 hdw_status_tag;
	__we32 phy_ppdu_id;
	u8 hdw_status[HAW_WX_DESC_HDW_STATUS_WEN];
	u8 msdu_paywoad[];
} __packed;

stwuct haw_wx_desc {
	union {
		stwuct haw_wx_desc_ipq8074 ipq8074;
		stwuct haw_wx_desc_qcn9074 qcn9074;
		stwuct haw_wx_desc_wcn6855 wcn6855;
	} u;
} __packed;

#define HAW_WX_WU_AWWOC_TYPE_MAX 6
#define WU_26  1
#define WU_52  2
#define WU_106 4
#define WU_242 9
#define WU_484 18
#define WU_996 37

#endif /* ATH11K_WX_DESC_H */
