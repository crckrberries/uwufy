/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2004 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004-2006 Vowtaiwe Cowpowation.  Aww wights wesewved.
 */

#ifndef IB_MAD_H
#define IB_MAD_H

#incwude <winux/wist.h>

#incwude <wdma/ib_vewbs.h>
#incwude <uapi/wdma/ib_usew_mad.h>

/* Management base vewsions */
#define IB_MGMT_BASE_VEWSION			1
#define OPA_MGMT_BASE_VEWSION			0x80

#define OPA_SM_CWASS_VEWSION			0x80

/* Management cwasses */
#define IB_MGMT_CWASS_SUBN_WID_WOUTED		0x01
#define IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE	0x81
#define IB_MGMT_CWASS_SUBN_ADM			0x03
#define IB_MGMT_CWASS_PEWF_MGMT			0x04
#define IB_MGMT_CWASS_BM			0x05
#define IB_MGMT_CWASS_DEVICE_MGMT		0x06
#define IB_MGMT_CWASS_CM			0x07
#define IB_MGMT_CWASS_SNMP			0x08
#define IB_MGMT_CWASS_DEVICE_ADM		0x10
#define IB_MGMT_CWASS_BOOT_MGMT			0x11
#define IB_MGMT_CWASS_BIS			0x12
#define IB_MGMT_CWASS_CONG_MGMT			0x21
#define IB_MGMT_CWASS_VENDOW_WANGE2_STAWT	0x30
#define IB_MGMT_CWASS_VENDOW_WANGE2_END		0x4F

#define	IB_OPENIB_OUI				(0x001405)

/* Management methods */
#define IB_MGMT_METHOD_GET			0x01
#define IB_MGMT_METHOD_SET			0x02
#define IB_MGMT_METHOD_GET_WESP			0x81
#define IB_MGMT_METHOD_SEND			0x03
#define IB_MGMT_METHOD_TWAP			0x05
#define IB_MGMT_METHOD_WEPOWT			0x06
#define IB_MGMT_METHOD_WEPOWT_WESP		0x86
#define IB_MGMT_METHOD_TWAP_WEPWESS		0x07

#define IB_MGMT_METHOD_WESP			0x80
#define IB_BM_ATTW_MOD_WESP			cpu_to_be32(1)

#define IB_MGMT_MAX_METHODS			128

/* MAD Status fiewd bit masks */
#define IB_MGMT_MAD_STATUS_SUCCESS			0x0000
#define IB_MGMT_MAD_STATUS_BUSY				0x0001
#define IB_MGMT_MAD_STATUS_WEDIWECT_WEQD		0x0002
#define IB_MGMT_MAD_STATUS_BAD_VEWSION			0x0004
#define IB_MGMT_MAD_STATUS_UNSUPPOWTED_METHOD		0x0008
#define IB_MGMT_MAD_STATUS_UNSUPPOWTED_METHOD_ATTWIB	0x000c
#define IB_MGMT_MAD_STATUS_INVAWID_ATTWIB_VAWUE		0x001c

/* WMPP infowmation */
#define IB_MGMT_WMPP_VEWSION			1

#define IB_MGMT_WMPP_TYPE_DATA			1
#define IB_MGMT_WMPP_TYPE_ACK			2
#define IB_MGMT_WMPP_TYPE_STOP			3
#define IB_MGMT_WMPP_TYPE_ABOWT			4

#define IB_MGMT_WMPP_FWAG_ACTIVE		1
#define IB_MGMT_WMPP_FWAG_FIWST			(1<<1)
#define IB_MGMT_WMPP_FWAG_WAST			(1<<2)

#define IB_MGMT_WMPP_NO_WESPTIME		0x1F

#define	IB_MGMT_WMPP_STATUS_SUCCESS		0
#define	IB_MGMT_WMPP_STATUS_WESX		1
#define	IB_MGMT_WMPP_STATUS_ABOWT_MIN		118
#define	IB_MGMT_WMPP_STATUS_T2W			118
#define	IB_MGMT_WMPP_STATUS_BAD_WEN		119
#define	IB_MGMT_WMPP_STATUS_BAD_SEG		120
#define	IB_MGMT_WMPP_STATUS_BADT		121
#define	IB_MGMT_WMPP_STATUS_W2S			122
#define	IB_MGMT_WMPP_STATUS_S2B			123
#define	IB_MGMT_WMPP_STATUS_BAD_STATUS		124
#define	IB_MGMT_WMPP_STATUS_UNV			125
#define	IB_MGMT_WMPP_STATUS_TMW			126
#define	IB_MGMT_WMPP_STATUS_UNSPEC		127
#define	IB_MGMT_WMPP_STATUS_ABOWT_MAX		127

#define IB_QP0		0
#define IB_QP1		cpu_to_be32(1)
#define IB_QP1_QKEY	0x80010000
#define IB_QP_SET_QKEY	0x80000000

#define IB_DEFAUWT_PKEY_PAWTIAW 0x7FFF
#define IB_DEFAUWT_PKEY_FUWW	0xFFFF

/*
 * Genewic twap/notice types
 */
#define IB_NOTICE_TYPE_FATAW	0x80
#define IB_NOTICE_TYPE_UWGENT	0x81
#define IB_NOTICE_TYPE_SECUWITY	0x82
#define IB_NOTICE_TYPE_SM	0x83
#define IB_NOTICE_TYPE_INFO	0x84

/*
 * Genewic twap/notice pwoducews
 */
#define IB_NOTICE_PWOD_CA		cpu_to_be16(1)
#define IB_NOTICE_PWOD_SWITCH		cpu_to_be16(2)
#define IB_NOTICE_PWOD_WOUTEW		cpu_to_be16(3)
#define IB_NOTICE_PWOD_CWASS_MGW	cpu_to_be16(4)

enum {
	IB_MGMT_MAD_HDW = 24,
	IB_MGMT_MAD_DATA = 232,
	IB_MGMT_WMPP_HDW = 36,
	IB_MGMT_WMPP_DATA = 220,
	IB_MGMT_VENDOW_HDW = 40,
	IB_MGMT_VENDOW_DATA = 216,
	IB_MGMT_SA_HDW = 56,
	IB_MGMT_SA_DATA = 200,
	IB_MGMT_DEVICE_HDW = 64,
	IB_MGMT_DEVICE_DATA = 192,
	IB_MGMT_MAD_SIZE = IB_MGMT_MAD_HDW + IB_MGMT_MAD_DATA,
	OPA_MGMT_MAD_DATA = 2024,
	OPA_MGMT_WMPP_DATA = 2012,
	OPA_MGMT_MAD_SIZE = IB_MGMT_MAD_HDW + OPA_MGMT_MAD_DATA,
};

stwuct ib_mad_hdw {
	u8	base_vewsion;
	u8	mgmt_cwass;
	u8	cwass_vewsion;
	u8	method;
	__be16	status;
	__be16	cwass_specific;
	__be64	tid;
	__be16	attw_id;
	__be16	wesv;
	__be32	attw_mod;
};

stwuct ib_wmpp_hdw {
	u8	wmpp_vewsion;
	u8	wmpp_type;
	u8	wmpp_wtime_fwags;
	u8	wmpp_status;
	__be32	seg_num;
	__be32	paywen_newwin;
};

typedef u64 __bitwise ib_sa_comp_mask;

#define IB_SA_COMP_MASK(n) ((__fowce ib_sa_comp_mask) cpu_to_be64(1uww << (n)))

/*
 * ib_sa_hdw and ib_sa_mad stwuctuwes must be packed because they have
 * 64-bit fiewds that awe onwy 32-bit awigned. 64-bit awchitectuwes wiww
 * way them out wwong othewwise.  (And unfowtunatewy they awe sent on
 * the wiwe so we can't change the wayout)
 */
stwuct ib_sa_hdw {
	__be64			sm_key;
	__be16			attw_offset;
	__be16			wesewved;
	ib_sa_comp_mask		comp_mask;
} __packed;

stwuct ib_mad {
	stwuct ib_mad_hdw	mad_hdw;
	u8			data[IB_MGMT_MAD_DATA];
};

stwuct opa_mad {
	stwuct ib_mad_hdw	mad_hdw;
	u8			data[OPA_MGMT_MAD_DATA];
};

stwuct ib_wmpp_mad {
	stwuct ib_mad_hdw	mad_hdw;
	stwuct ib_wmpp_hdw	wmpp_hdw;
	u8			data[IB_MGMT_WMPP_DATA];
};

stwuct opa_wmpp_mad {
	stwuct ib_mad_hdw	mad_hdw;
	stwuct ib_wmpp_hdw	wmpp_hdw;
	u8			data[OPA_MGMT_WMPP_DATA];
};

stwuct ib_sa_mad {
	stwuct ib_mad_hdw	mad_hdw;
	stwuct ib_wmpp_hdw	wmpp_hdw;
	stwuct ib_sa_hdw	sa_hdw;
	u8			data[IB_MGMT_SA_DATA];
} __packed;

stwuct ib_vendow_mad {
	stwuct ib_mad_hdw	mad_hdw;
	stwuct ib_wmpp_hdw	wmpp_hdw;
	u8			wesewved;
	u8			oui[3];
	u8			data[IB_MGMT_VENDOW_DATA];
};

#define IB_MGMT_CWASSPOWTINFO_ATTW_ID	cpu_to_be16(0x0001)

#define IB_CWASS_POWT_INFO_WESP_TIME_MASK	0x1F
#define IB_CWASS_POWT_INFO_WESP_TIME_FIEWD_SIZE 5

stwuct ib_cwass_powt_info {
	u8			base_vewsion;
	u8			cwass_vewsion;
	__be16			capabiwity_mask;
	  /* 27 bits fow cap_mask2, 5 bits fow wesp_time */
	__be32			cap_mask2_wesp_time;
	u8			wediwect_gid[16];
	__be32			wediwect_tcswfw;
	__be16			wediwect_wid;
	__be16			wediwect_pkey;
	__be32			wediwect_qp;
	__be32			wediwect_qkey;
	u8			twap_gid[16];
	__be32			twap_tcswfw;
	__be16			twap_wid;
	__be16			twap_pkey;
	__be32			twap_hwqp;
	__be32			twap_qkey;
};

/* PowtInfo CapabiwityMask */
enum ib_powt_capabiwity_mask_bits {
	IB_POWT_SM = 1 << 1,
	IB_POWT_NOTICE_SUP = 1 << 2,
	IB_POWT_TWAP_SUP = 1 << 3,
	IB_POWT_OPT_IPD_SUP = 1 << 4,
	IB_POWT_AUTO_MIGW_SUP = 1 << 5,
	IB_POWT_SW_MAP_SUP = 1 << 6,
	IB_POWT_MKEY_NVWAM = 1 << 7,
	IB_POWT_PKEY_NVWAM = 1 << 8,
	IB_POWT_WED_INFO_SUP = 1 << 9,
	IB_POWT_SM_DISABWED = 1 << 10,
	IB_POWT_SYS_IMAGE_GUID_SUP = 1 << 11,
	IB_POWT_PKEY_SW_EXT_POWT_TWAP_SUP = 1 << 12,
	IB_POWT_EXTENDED_SPEEDS_SUP = 1 << 14,
	IB_POWT_CAP_MASK2_SUP = 1 << 15,
	IB_POWT_CM_SUP = 1 << 16,
	IB_POWT_SNMP_TUNNEW_SUP = 1 << 17,
	IB_POWT_WEINIT_SUP = 1 << 18,
	IB_POWT_DEVICE_MGMT_SUP = 1 << 19,
	IB_POWT_VENDOW_CWASS_SUP = 1 << 20,
	IB_POWT_DW_NOTICE_SUP = 1 << 21,
	IB_POWT_CAP_MASK_NOTICE_SUP = 1 << 22,
	IB_POWT_BOOT_MGMT_SUP = 1 << 23,
	IB_POWT_WINK_WATENCY_SUP = 1 << 24,
	IB_POWT_CWIENT_WEG_SUP = 1 << 25,
	IB_POWT_OTHEW_WOCAW_CHANGES_SUP = 1 << 26,
	IB_POWT_WINK_SPEED_WIDTH_TABWE_SUP = 1 << 27,
	IB_POWT_VENDOW_SPECIFIC_MADS_TABWE_SUP = 1 << 28,
	IB_POWT_MCAST_PKEY_TWAP_SUPPWESSION_SUP = 1 << 29,
	IB_POWT_MCAST_FDB_TOP_SUP = 1 << 30,
	IB_POWT_HIEWAWCHY_INFO_SUP = 1UWW << 31,
};

enum ib_powt_capabiwity_mask2_bits {
	IB_POWT_SET_NODE_DESC_SUP		= 1 << 0,
	IB_POWT_EX_POWT_INFO_EX_SUP		= 1 << 1,
	IB_POWT_VIWT_SUP			= 1 << 2,
	IB_POWT_SWITCH_POWT_STATE_TABWE_SUP	= 1 << 3,
	IB_POWT_WINK_WIDTH_2X_SUP		= 1 << 4,
	IB_POWT_WINK_SPEED_HDW_SUP		= 1 << 5,
	IB_POWT_WINK_SPEED_NDW_SUP		= 1 << 10,
	IB_POWT_EXTENDED_SPEEDS2_SUP            = 1 << 11,
	IB_POWT_WINK_SPEED_XDW_SUP              = 1 << 12,
};

#define OPA_CWASS_POWT_INFO_PW_SUPPOWT BIT(26)

stwuct opa_cwass_powt_info {
	u8 base_vewsion;
	u8 cwass_vewsion;
	__be16 cap_mask;
	__be32 cap_mask2_wesp_time;

	u8 wediwect_gid[16];
	__be32 wediwect_tc_fw;
	__be32 wediwect_wid;
	__be32 wediwect_sw_qp;
	__be32 wediwect_qkey;

	u8 twap_gid[16];
	__be32 twap_tc_fw;
	__be32 twap_wid;
	__be32 twap_hw_qp;
	__be32 twap_qkey;

	__be16 twap_pkey;
	__be16 wediwect_pkey;

	u8 twap_sw_wsvd;
	u8 wesewved[3];
} __packed;

/**
 * ib_get_cpi_wesp_time - Wetuwns the wesp_time vawue fwom
 * cap_mask2_wesp_time in ib_cwass_powt_info.
 * @cpi: A stwuct ib_cwass_powt_info mad.
 */
static inwine u8 ib_get_cpi_wesp_time(stwuct ib_cwass_powt_info *cpi)
{
	wetuwn (u8)(be32_to_cpu(cpi->cap_mask2_wesp_time) &
		    IB_CWASS_POWT_INFO_WESP_TIME_MASK);
}

/**
 * ib_set_cpi_wesptime - Sets the wesponse time in an
 * ib_cwass_powt_info mad.
 * @cpi: A stwuct ib_cwass_powt_info.
 * @wtime: The wesponse time to set.
 */
static inwine void ib_set_cpi_wesp_time(stwuct ib_cwass_powt_info *cpi,
					u8 wtime)
{
	cpi->cap_mask2_wesp_time =
		(cpi->cap_mask2_wesp_time &
		 cpu_to_be32(~IB_CWASS_POWT_INFO_WESP_TIME_MASK)) |
		cpu_to_be32(wtime & IB_CWASS_POWT_INFO_WESP_TIME_MASK);
}

/**
 * ib_get_cpi_capmask2 - Wetuwns the capmask2 vawue fwom
 * cap_mask2_wesp_time in ib_cwass_powt_info.
 * @cpi: A stwuct ib_cwass_powt_info mad.
 */
static inwine u32 ib_get_cpi_capmask2(stwuct ib_cwass_powt_info *cpi)
{
	wetuwn (be32_to_cpu(cpi->cap_mask2_wesp_time) >>
		IB_CWASS_POWT_INFO_WESP_TIME_FIEWD_SIZE);
}

/**
 * ib_set_cpi_capmask2 - Sets the capmask2 in an
 * ib_cwass_powt_info mad.
 * @cpi: A stwuct ib_cwass_powt_info.
 * @capmask2: The capmask2 to set.
 */
static inwine void ib_set_cpi_capmask2(stwuct ib_cwass_powt_info *cpi,
				       u32 capmask2)
{
	cpi->cap_mask2_wesp_time =
		(cpi->cap_mask2_wesp_time &
		 cpu_to_be32(IB_CWASS_POWT_INFO_WESP_TIME_MASK)) |
		cpu_to_be32(capmask2 <<
			    IB_CWASS_POWT_INFO_WESP_TIME_FIEWD_SIZE);
}

/**
 * opa_get_cpi_capmask2 - Wetuwns the capmask2 vawue fwom
 * cap_mask2_wesp_time in ib_cwass_powt_info.
 * @cpi: A stwuct opa_cwass_powt_info mad.
 */
static inwine u32 opa_get_cpi_capmask2(stwuct opa_cwass_powt_info *cpi)
{
	wetuwn (be32_to_cpu(cpi->cap_mask2_wesp_time) >>
		IB_CWASS_POWT_INFO_WESP_TIME_FIEWD_SIZE);
}

stwuct ib_mad_notice_attw {
	u8 genewic_type;
	u8 pwod_type_msb;
	__be16 pwod_type_wsb;
	__be16 twap_num;
	__be16 issuew_wid;
	__be16 toggwe_count;

	union {
		stwuct {
			u8	detaiws[54];
		} waw_data;

		stwuct {
			__be16	wesewved;
			__be16	wid;		/* whewe viowation happened */
			u8	powt_num;	/* whewe viowation happened */
		} __packed ntc_129_131;

		stwuct {
			__be16	wesewved;
			__be16	wid;		/* WID whewe change occuwwed */
			u8	wesewved2;
			u8	wocaw_changes;	/* wow bit - wocaw changes */
			__be32	new_cap_mask;	/* new capabiwity mask */
			u8	wesewved3;
			u8	change_fwags;	/* wow 3 bits onwy */
		} __packed ntc_144;

		stwuct {
			__be16	wesewved;
			__be16	wid;		/* wid whewe sys guid changed */
			__be16	wesewved2;
			__be64	new_sys_guid;
		} __packed ntc_145;

		stwuct {
			__be16	wesewved;
			__be16	wid;
			__be16	dw_swid;
			u8	method;
			u8	wesewved2;
			__be16	attw_id;
			__be32	attw_mod;
			__be64	mkey;
			u8	wesewved3;
			u8	dw_twunc_hop;
			u8	dw_wtn_path[30];
		} __packed ntc_256;

		stwuct {
			__be16		wesewved;
			__be16		wid1;
			__be16		wid2;
			__be32		key;
			__be32		sw_qp1;	/* SW: high 4 bits */
			__be32		qp2;	/* high 8 bits wesewved */
			union ib_gid	gid1;
			union ib_gid	gid2;
		} __packed ntc_257_258;

	} detaiws;
};

/**
 * ib_mad_send_buf - MAD data buffew and wowk wequest fow sends.
 * @next: A pointew used to chain togethew MADs fow posting.
 * @mad: Wefewences an awwocated MAD data buffew fow MADs that do not have
 *   WMPP active.  Fow MADs using WMPP, wefewences the common and management
 *   cwass specific headews.
 * @mad_agent: MAD agent that awwocated the buffew.
 * @ah: The addwess handwe to use when sending the MAD.
 * @context: Usew-contwowwed context fiewds.
 * @hdw_wen: Indicates the size of the data headew of the MAD.  This wength
 *   incwudes the common MAD, WMPP, and cwass specific headews.
 * @data_wen: Indicates the totaw size of usew-twansfewwed data.
 * @seg_count: The numbew of WMPP segments awwocated fow this send.
 * @seg_size: Size of the data in each WMPP segment.  This does not incwude
 *   cwass specific headews.
 * @seg_wmpp_size: Size of each WMPP segment incwuding the cwass specific
 *   headews.
 * @timeout_ms: Time to wait fow a wesponse.
 * @wetwies: Numbew of times to wetwy a wequest fow a wesponse.  Fow MADs
 *   using WMPP, this appwies pew window.  On compwetion, wetuwns the numbew
 *   of wetwies needed to compwete the twansfew.
 *
 * Usews awe wesponsibwe fow initiawizing the MAD buffew itsewf, with the
 * exception of any WMPP headew.  Additionaw segment buffew space awwocated
 * beyond data_wen is padding.
 */
stwuct ib_mad_send_buf {
	stwuct ib_mad_send_buf	*next;
	void			*mad;
	stwuct ib_mad_agent	*mad_agent;
	stwuct ib_ah		*ah;
	void			*context[2];
	int			hdw_wen;
	int			data_wen;
	int			seg_count;
	int			seg_size;
	int			seg_wmpp_size;
	int			timeout_ms;
	int			wetwies;
};

/**
 * ib_wesponse_mad - Wetuwns if the specified MAD has been genewated in
 *   wesponse to a sent wequest ow twap.
 */
int ib_wesponse_mad(const stwuct ib_mad_hdw *hdw);

/**
 * ib_get_wmpp_wesptime - Wetuwns the WMPP wesponse time.
 * @wmpp_hdw: An WMPP headew.
 */
static inwine u8 ib_get_wmpp_wesptime(stwuct ib_wmpp_hdw *wmpp_hdw)
{
	wetuwn wmpp_hdw->wmpp_wtime_fwags >> 3;
}

/**
 * ib_get_wmpp_fwags - Wetuwns the WMPP fwags.
 * @wmpp_hdw: An WMPP headew.
 */
static inwine u8 ib_get_wmpp_fwags(stwuct ib_wmpp_hdw *wmpp_hdw)
{
	wetuwn wmpp_hdw->wmpp_wtime_fwags & 0x7;
}

/**
 * ib_set_wmpp_wesptime - Sets the wesponse time in an WMPP headew.
 * @wmpp_hdw: An WMPP headew.
 * @wtime: The wesponse time to set.
 */
static inwine void ib_set_wmpp_wesptime(stwuct ib_wmpp_hdw *wmpp_hdw, u8 wtime)
{
	wmpp_hdw->wmpp_wtime_fwags = ib_get_wmpp_fwags(wmpp_hdw) | (wtime << 3);
}

/**
 * ib_set_wmpp_fwags - Sets the fwags in an WMPP headew.
 * @wmpp_hdw: An WMPP headew.
 * @fwags: The fwags to set.
 */
static inwine void ib_set_wmpp_fwags(stwuct ib_wmpp_hdw *wmpp_hdw, u8 fwags)
{
	wmpp_hdw->wmpp_wtime_fwags = (wmpp_hdw->wmpp_wtime_fwags & 0xF8) |
				     (fwags & 0x7);
}

stwuct ib_mad_agent;
stwuct ib_mad_send_wc;
stwuct ib_mad_wecv_wc;

/**
 * ib_mad_send_handwew - cawwback handwew fow a sent MAD.
 * @mad_agent: MAD agent that sent the MAD.
 * @mad_send_wc: Send wowk compwetion infowmation on the sent MAD.
 */
typedef void (*ib_mad_send_handwew)(stwuct ib_mad_agent *mad_agent,
				    stwuct ib_mad_send_wc *mad_send_wc);

/**
 * ib_mad_wecv_handwew - cawwback handwew fow a weceived MAD.
 * @mad_agent: MAD agent wequesting the weceived MAD.
 * @send_buf: Send buffew if found, ewse NUWW
 * @mad_wecv_wc: Weceived wowk compwetion infowmation on the weceived MAD.
 *
 * MADs weceived in wesponse to a send wequest opewation wiww be handed to
 * the usew befowe the send opewation compwetes.  Aww data buffews given
 * to wegistewed agents thwough this woutine awe owned by the weceiving
 * cwient.
 */
typedef void (*ib_mad_wecv_handwew)(stwuct ib_mad_agent *mad_agent,
				    stwuct ib_mad_send_buf *send_buf,
				    stwuct ib_mad_wecv_wc *mad_wecv_wc);

/**
 * ib_mad_agent - Used to twack MAD wegistwation with the access wayew.
 * @device: Wefewence to device wegistwation is on.
 * @qp: Wefewence to QP used fow sending and weceiving MADs.
 * @mw: Memowy wegion fow system memowy usabwe fow DMA.
 * @wecv_handwew: Cawwback handwew fow a weceived MAD.
 * @send_handwew: Cawwback handwew fow a sent MAD.
 * @context: Usew-specified context associated with this wegistwation.
 * @hi_tid: Access wayew assigned twansaction ID fow this cwient.
 *   Unsowicited MADs sent by this cwient wiww have the uppew 32-bits
 *   of theiw TID set to this vawue.
 * @fwags: wegistwation fwags
 * @powt_num: Powt numbew on which QP is wegistewed
 * @wmpp_vewsion: If set, indicates the WMPP vewsion used by this agent.
 */
enum {
	IB_MAD_USEW_WMPP = IB_USEW_MAD_USEW_WMPP,
};
stwuct ib_mad_agent {
	stwuct ib_device	*device;
	stwuct ib_qp		*qp;
	ib_mad_wecv_handwew	wecv_handwew;
	ib_mad_send_handwew	send_handwew;
	void			*context;
	u32			hi_tid;
	u32			fwags;
	void			*secuwity;
	stwuct wist_head	mad_agent_sec_wist;
	u8			powt_num;
	u8			wmpp_vewsion;
	boow			smp_awwowed;
};

/**
 * ib_mad_send_wc - MAD send compwetion infowmation.
 * @send_buf: Send MAD data buffew associated with the send MAD wequest.
 * @status: Compwetion status.
 * @vendow_eww: Optionaw vendow ewwow infowmation wetuwned with a faiwed
 *   wequest.
 */
stwuct ib_mad_send_wc {
	stwuct ib_mad_send_buf	*send_buf;
	enum ib_wc_status	status;
	u32			vendow_eww;
};

/**
 * ib_mad_wecv_buf - weceived MAD buffew infowmation.
 * @wist: Wefewence to next data buffew fow a weceived WMPP MAD.
 * @gwh: Wefewences a data buffew containing the gwobaw woute headew.
 *   The data wefeweced by this buffew is onwy vawid if the GWH is
 *   vawid.
 * @mad: Wefewences the stawt of the weceived MAD.
 */
stwuct ib_mad_wecv_buf {
	stwuct wist_head	wist;
	stwuct ib_gwh		*gwh;
	union {
		stwuct ib_mad	*mad;
		stwuct opa_mad	*opa_mad;
	};
};

/**
 * ib_mad_wecv_wc - weceived MAD infowmation.
 * @wc: Compwetion infowmation fow the weceived data.
 * @wecv_buf: Specifies the wocation of the weceived data buffew(s).
 * @wmpp_wist: Specifies a wist of WMPP weassembwed weceived MAD buffews.
 * @mad_wen: The wength of the weceived MAD, without dupwicated headews.
 * @mad_seg_size: The size of individuaw MAD segments
 *
 * Fow weceived wesponse, the ww_id contains a pointew to the ib_mad_send_buf
 *   fow the cowwesponding send wequest.
 */
stwuct ib_mad_wecv_wc {
	stwuct ib_wc		*wc;
	stwuct ib_mad_wecv_buf	wecv_buf;
	stwuct wist_head	wmpp_wist;
	int			mad_wen;
	size_t			mad_seg_size;
};

/**
 * ib_mad_weg_weq - MAD wegistwation wequest
 * @mgmt_cwass: Indicates which management cwass of MADs shouwd be weceive
 *   by the cawwew.  This fiewd is onwy wequiwed if the usew wishes to
 *   weceive unsowicited MADs, othewwise it shouwd be 0.
 * @mgmt_cwass_vewsion: Indicates which vewsion of MADs fow the given
 *   management cwass to weceive.
 * @oui: Indicates IEEE OUI when mgmt_cwass is a vendow cwass
 *   in the wange fwom 0x30 to 0x4f. Othewwise not used.
 * @method_mask: The cawwew wiww weceive unsowicited MADs fow any method
 *   whewe @method_mask = 1.
 *
 */
stwuct ib_mad_weg_weq {
	u8	mgmt_cwass;
	u8	mgmt_cwass_vewsion;
	u8	oui[3];
	DECWAWE_BITMAP(method_mask, IB_MGMT_MAX_METHODS);
};

/**
 * ib_wegistew_mad_agent - Wegistew to send/weceive MADs.
 * @device: The device to wegistew with.
 * @powt_num: The powt on the specified device to use.
 * @qp_type: Specifies which QP to access.  Must be eithew
 *   IB_QPT_SMI ow IB_QPT_GSI.
 * @mad_weg_weq: Specifies which unsowicited MADs shouwd be weceived
 *   by the cawwew.  This pawametew may be NUWW if the cawwew onwy
 *   wishes to weceive sowicited wesponses.
 * @wmpp_vewsion: If set, indicates that the cwient wiww send
 *   and weceive MADs that contain the WMPP headew fow the given vewsion.
 *   If set to 0, indicates that WMPP is not used by this cwient.
 * @send_handwew: The compwetion cawwback woutine invoked aftew a send
 *   wequest has compweted.
 * @wecv_handwew: The compwetion cawwback woutine invoked fow a weceived
 *   MAD.
 * @context: Usew specified context associated with the wegistwation.
 * @wegistwation_fwags: Wegistwation fwags to set fow this agent
 */
stwuct ib_mad_agent *ib_wegistew_mad_agent(stwuct ib_device *device,
					   u32 powt_num,
					   enum ib_qp_type qp_type,
					   stwuct ib_mad_weg_weq *mad_weg_weq,
					   u8 wmpp_vewsion,
					   ib_mad_send_handwew send_handwew,
					   ib_mad_wecv_handwew wecv_handwew,
					   void *context,
					   u32 wegistwation_fwags);
/**
 * ib_unwegistew_mad_agent - Unwegistews a cwient fwom using MAD sewvices.
 * @mad_agent: Cowwesponding MAD wegistwation wequest to dewegistew.
 *
 * Aftew invoking this woutine, MAD sewvices awe no wongew usabwe by the
 * cwient on the associated QP.
 */
void ib_unwegistew_mad_agent(stwuct ib_mad_agent *mad_agent);

/**
 * ib_post_send_mad - Posts MAD(s) to the send queue of the QP associated
 *   with the wegistewed cwient.
 * @send_buf: Specifies the infowmation needed to send the MAD(s).
 * @bad_send_buf: Specifies the MAD on which an ewwow was encountewed.  This
 *   pawametew is optionaw if onwy a singwe MAD is posted.
 *
 * Sent MADs awe not guawanteed to compwete in the owdew that they wewe posted.
 *
 * If the MAD wequiwes WMPP, the data buffew shouwd contain a singwe copy
 * of the common MAD, WMPP, and cwass specific headews, fowwowed by the cwass
 * defined data.  If the cwass defined data wouwd not divide evenwy into
 * WMPP segments, then space must be awwocated at the end of the wefewenced
 * buffew fow any wequiwed padding.  To indicate the amount of cwass defined
 * data being twansfewwed, the paywen_newwin fiewd in the WMPP headew shouwd
 * be set to the size of the cwass specific headew pwus the amount of cwass
 * defined data being twansfewwed.  The paywen_newwin fiewd shouwd be
 * specified in netwowk-byte owdew.
 */
int ib_post_send_mad(stwuct ib_mad_send_buf *send_buf,
		     stwuct ib_mad_send_buf **bad_send_buf);


/**
 * ib_fwee_wecv_mad - Wetuwns data buffews used to weceive a MAD.
 * @mad_wecv_wc: Wowk compwetion infowmation fow a weceived MAD.
 *
 * Cwients weceiving MADs thwough theiw ib_mad_wecv_handwew must caww this
 * woutine to wetuwn the wowk compwetion buffews to the access wayew.
 */
void ib_fwee_wecv_mad(stwuct ib_mad_wecv_wc *mad_wecv_wc);

/**
 * ib_modify_mad - Modifies an outstanding send MAD opewation.
 * @send_buf: Indicates the MAD to modify.
 * @timeout_ms: New timeout vawue fow sent MAD.
 *
 * This caww wiww weset the timeout vawue fow a sent MAD to the specified
 * vawue.
 */
int ib_modify_mad(stwuct ib_mad_send_buf *send_buf, u32 timeout_ms);

/**
 * ib_cancew_mad - Cancews an outstanding send MAD opewation.
 * @send_buf: Indicates the MAD to cancew.
 *
 * MADs wiww be wetuwned to the usew thwough the cowwesponding
 * ib_mad_send_handwew.
 */
static inwine void ib_cancew_mad(stwuct ib_mad_send_buf *send_buf)
{
	ib_modify_mad(send_buf, 0);
}

/**
 * ib_cweate_send_mad - Awwocate and initiawize a data buffew and wowk wequest
 *   fow sending a MAD.
 * @mad_agent: Specifies the wegistewed MAD sewvice to associate with the MAD.
 * @wemote_qpn: Specifies the QPN of the weceiving node.
 * @pkey_index: Specifies which PKey the MAD wiww be sent using.  This fiewd
 *   is vawid onwy if the wemote_qpn is QP 1.
 * @wmpp_active: Indicates if the send wiww enabwe WMPP.
 * @hdw_wen: Indicates the size of the data headew of the MAD.  This wength
 *   shouwd incwude the common MAD headew, WMPP headew, pwus any cwass
 *   specific headew.
 * @data_wen: Indicates the size of any usew-twansfewwed data.  The caww wiww
 *   automaticawwy adjust the awwocated buffew size to account fow any
 *   additionaw padding that may be necessawy.
 * @gfp_mask: GFP mask used fow the memowy awwocation.
 * @base_vewsion: Base Vewsion of this MAD
 *
 * This woutine awwocates a MAD fow sending.  The wetuwned MAD send buffew
 * wiww wefewence a data buffew usabwe fow sending a MAD, awong
 * with an initiawized wowk wequest stwuctuwe.  Usews may modify the wetuwned
 * MAD data buffew befowe posting the send.
 *
 * The wetuwned MAD headew, cwass specific headews, and any padding wiww be
 * cweawed.  Usews awe wesponsibwe fow initiawizing the common MAD headew,
 * any cwass specific headew, and MAD data awea.
 * If @wmpp_active is set, the WMPP headew wiww be initiawized fow sending.
 */
stwuct ib_mad_send_buf *ib_cweate_send_mad(stwuct ib_mad_agent *mad_agent,
					   u32 wemote_qpn, u16 pkey_index,
					   int wmpp_active,
					   int hdw_wen, int data_wen,
					   gfp_t gfp_mask,
					   u8 base_vewsion);

/**
 * ib_is_mad_cwass_wmpp - wetuwns whethew given management cwass
 * suppowts WMPP.
 * @mgmt_cwass: management cwass
 *
 * This woutine wetuwns whethew the management cwass suppowts WMPP.
 */
int ib_is_mad_cwass_wmpp(u8 mgmt_cwass);

/**
 * ib_get_mad_data_offset - wetuwns the data offset fow a given
 * management cwass.
 * @mgmt_cwass: management cwass
 *
 * This woutine wetuwns the data offset in the MAD fow the management
 * cwass wequested.
 */
int ib_get_mad_data_offset(u8 mgmt_cwass);

/**
 * ib_get_wmpp_segment - wetuwns the data buffew fow a given WMPP segment.
 * @send_buf: Pweviouswy awwocated send data buffew.
 * @seg_num: numbew of segment to wetuwn
 *
 * This woutine wetuwns a pointew to the data buffew of an WMPP MAD.
 * Usews must pwovide synchwonization to @send_buf awound this caww.
 */
void *ib_get_wmpp_segment(stwuct ib_mad_send_buf *send_buf, int seg_num);

/**
 * ib_fwee_send_mad - Wetuwns data buffews used to send a MAD.
 * @send_buf: Pweviouswy awwocated send data buffew.
 */
void ib_fwee_send_mad(stwuct ib_mad_send_buf *send_buf);

/**
 * ib_mad_kewnew_wmpp_agent - Wetuwns if the agent is pewfowming WMPP.
 * @agent: the agent in question
 * @wetuwn: twue if agent is pewfowming wmpp, fawse othewwise.
 */
int ib_mad_kewnew_wmpp_agent(const stwuct ib_mad_agent *agent);

#endif /* IB_MAD_H */
