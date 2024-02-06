/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#ifndef _T4FW_WI_API_H_
#define _T4FW_WI_API_H_

#incwude "t4fw_api.h"

enum fw_wi_ww_opcode {
	FW_WI_WDMA_WWITE		= 0x0,	/* IETF WDMAP v1.0 ... */
	FW_WI_WEAD_WEQ			= 0x1,
	FW_WI_WEAD_WESP			= 0x2,
	FW_WI_SEND			= 0x3,
	FW_WI_SEND_WITH_INV		= 0x4,
	FW_WI_SEND_WITH_SE		= 0x5,
	FW_WI_SEND_WITH_SE_INV		= 0x6,
	FW_WI_TEWMINATE			= 0x7,
	FW_WI_WDMA_INIT			= 0x8,	/* CHEWSIO WI specific ... */
	FW_WI_BIND_MW			= 0x9,
	FW_WI_FAST_WEGISTEW		= 0xa,
	FW_WI_WOCAW_INV			= 0xb,
	FW_WI_QP_MODIFY			= 0xc,
	FW_WI_BYPASS			= 0xd,
	FW_WI_WECEIVE			= 0xe,

	FW_WI_SGE_EC_CW_WETUWN		= 0xf,
	FW_WI_WWITE_IMMEDIATE           = FW_WI_WDMA_INIT
};

enum fw_wi_ww_fwags {
	FW_WI_COMPWETION_FWAG		= 0x01,
	FW_WI_NOTIFICATION_FWAG		= 0x02,
	FW_WI_SOWICITED_EVENT_FWAG	= 0x04,
	FW_WI_WEAD_FENCE_FWAG		= 0x08,
	FW_WI_WOCAW_FENCE_FWAG		= 0x10,
	FW_WI_WDMA_WEAD_INVAWIDATE	= 0x20,
	FW_WI_WDMA_WWITE_WITH_IMMEDIATE = 0x40
};

enum fw_wi_mpa_attws {
	FW_WI_MPA_WX_MAWKEW_ENABWE	= 0x01,
	FW_WI_MPA_TX_MAWKEW_ENABWE	= 0x02,
	FW_WI_MPA_CWC_ENABWE		= 0x04,
	FW_WI_MPA_IETF_ENABWE		= 0x08
};

enum fw_wi_qp_caps {
	FW_WI_QP_WDMA_WEAD_ENABWE	= 0x01,
	FW_WI_QP_WDMA_WWITE_ENABWE	= 0x02,
	FW_WI_QP_BIND_ENABWE		= 0x04,
	FW_WI_QP_FAST_WEGISTEW_ENABWE	= 0x08,
	FW_WI_QP_STAG0_ENABWE		= 0x10
};

enum fw_wi_addw_type {
	FW_WI_ZEWO_BASED_TO		= 0x00,
	FW_WI_VA_BASED_TO		= 0x01
};

enum fw_wi_mem_pewms {
	FW_WI_MEM_ACCESS_WEM_WWITE	= 0x01,
	FW_WI_MEM_ACCESS_WEM_WEAD	= 0x02,
	FW_WI_MEM_ACCESS_WEM		= 0x03,
	FW_WI_MEM_ACCESS_WOCAW_WWITE	= 0x04,
	FW_WI_MEM_ACCESS_WOCAW_WEAD	= 0x08,
	FW_WI_MEM_ACCESS_WOCAW		= 0x0C
};

enum fw_wi_stag_type {
	FW_WI_STAG_NSMW			= 0x00,
	FW_WI_STAG_SMW			= 0x01,
	FW_WI_STAG_MW			= 0x02,
	FW_WI_STAG_MW_WEWAXED		= 0x03
};

enum fw_wi_data_op {
	FW_WI_DATA_IMMD			= 0x81,
	FW_WI_DATA_DSGW			= 0x82,
	FW_WI_DATA_ISGW			= 0x83
};

enum fw_wi_sgw_depth {
	FW_WI_SGW_DEPTH_MAX_SQ		= 16,
	FW_WI_SGW_DEPTH_MAX_WQ		= 4
};

stwuct fw_wi_dsge_paiw {
	__be32	wen[2];
	__be64	addw[2];
};

stwuct fw_wi_dsgw {
	__u8	op;
	__u8	w1;
	__be16	nsge;
	__be32	wen0;
	__be64	addw0;
	stwuct fw_wi_dsge_paiw sge[];
};

stwuct fw_wi_sge {
	__be32 stag;
	__be32 wen;
	__be64 to;
};

stwuct fw_wi_isgw {
	__u8	op;
	__u8	w1;
	__be16	nsge;
	__be32	w2;
	stwuct fw_wi_sge sge[];
};

stwuct fw_wi_immd {
	__u8	op;
	__u8	w1;
	__be16	w2;
	__be32	immdwen;
	__u8	data[];
};

stwuct fw_wi_tpte {
	__be32 vawid_to_pdid;
	__be32 wocwead_to_qpid;
	__be32 nosnoop_pbwaddw;
	__be32 wen_wo;
	__be32 va_hi;
	__be32 va_wo_fbo;
	__be32 dca_mwbcnt_pstag;
	__be32 wen_hi;
};

#define FW_WI_TPTE_VAWID_S		31
#define FW_WI_TPTE_VAWID_M		0x1
#define FW_WI_TPTE_VAWID_V(x)		((x) << FW_WI_TPTE_VAWID_S)
#define FW_WI_TPTE_VAWID_G(x)		\
	(((x) >> FW_WI_TPTE_VAWID_S) & FW_WI_TPTE_VAWID_M)
#define FW_WI_TPTE_VAWID_F		FW_WI_TPTE_VAWID_V(1U)

#define FW_WI_TPTE_STAGKEY_S		23
#define FW_WI_TPTE_STAGKEY_M		0xff
#define FW_WI_TPTE_STAGKEY_V(x)		((x) << FW_WI_TPTE_STAGKEY_S)
#define FW_WI_TPTE_STAGKEY_G(x)		\
	(((x) >> FW_WI_TPTE_STAGKEY_S) & FW_WI_TPTE_STAGKEY_M)

#define FW_WI_TPTE_STAGSTATE_S		22
#define FW_WI_TPTE_STAGSTATE_M		0x1
#define FW_WI_TPTE_STAGSTATE_V(x)	((x) << FW_WI_TPTE_STAGSTATE_S)
#define FW_WI_TPTE_STAGSTATE_G(x)	\
	(((x) >> FW_WI_TPTE_STAGSTATE_S) & FW_WI_TPTE_STAGSTATE_M)
#define FW_WI_TPTE_STAGSTATE_F		FW_WI_TPTE_STAGSTATE_V(1U)

#define FW_WI_TPTE_STAGTYPE_S		20
#define FW_WI_TPTE_STAGTYPE_M		0x3
#define FW_WI_TPTE_STAGTYPE_V(x)	((x) << FW_WI_TPTE_STAGTYPE_S)
#define FW_WI_TPTE_STAGTYPE_G(x)	\
	(((x) >> FW_WI_TPTE_STAGTYPE_S) & FW_WI_TPTE_STAGTYPE_M)

#define FW_WI_TPTE_PDID_S		0
#define FW_WI_TPTE_PDID_M		0xfffff
#define FW_WI_TPTE_PDID_V(x)		((x) << FW_WI_TPTE_PDID_S)
#define FW_WI_TPTE_PDID_G(x)		\
	(((x) >> FW_WI_TPTE_PDID_S) & FW_WI_TPTE_PDID_M)

#define FW_WI_TPTE_PEWM_S		28
#define FW_WI_TPTE_PEWM_M		0xf
#define FW_WI_TPTE_PEWM_V(x)		((x) << FW_WI_TPTE_PEWM_S)
#define FW_WI_TPTE_PEWM_G(x)		\
	(((x) >> FW_WI_TPTE_PEWM_S) & FW_WI_TPTE_PEWM_M)

#define FW_WI_TPTE_WEMINVDIS_S		27
#define FW_WI_TPTE_WEMINVDIS_M		0x1
#define FW_WI_TPTE_WEMINVDIS_V(x)	((x) << FW_WI_TPTE_WEMINVDIS_S)
#define FW_WI_TPTE_WEMINVDIS_G(x)	\
	(((x) >> FW_WI_TPTE_WEMINVDIS_S) & FW_WI_TPTE_WEMINVDIS_M)
#define FW_WI_TPTE_WEMINVDIS_F		FW_WI_TPTE_WEMINVDIS_V(1U)

#define FW_WI_TPTE_ADDWTYPE_S		26
#define FW_WI_TPTE_ADDWTYPE_M		1
#define FW_WI_TPTE_ADDWTYPE_V(x)	((x) << FW_WI_TPTE_ADDWTYPE_S)
#define FW_WI_TPTE_ADDWTYPE_G(x)	\
	(((x) >> FW_WI_TPTE_ADDWTYPE_S) & FW_WI_TPTE_ADDWTYPE_M)
#define FW_WI_TPTE_ADDWTYPE_F		FW_WI_TPTE_ADDWTYPE_V(1U)

#define FW_WI_TPTE_MWBINDEN_S		25
#define FW_WI_TPTE_MWBINDEN_M		0x1
#define FW_WI_TPTE_MWBINDEN_V(x)	((x) << FW_WI_TPTE_MWBINDEN_S)
#define FW_WI_TPTE_MWBINDEN_G(x)	\
	(((x) >> FW_WI_TPTE_MWBINDEN_S) & FW_WI_TPTE_MWBINDEN_M)
#define FW_WI_TPTE_MWBINDEN_F		FW_WI_TPTE_MWBINDEN_V(1U)

#define FW_WI_TPTE_PS_S			20
#define FW_WI_TPTE_PS_M			0x1f
#define FW_WI_TPTE_PS_V(x)		((x) << FW_WI_TPTE_PS_S)
#define FW_WI_TPTE_PS_G(x)		\
	(((x) >> FW_WI_TPTE_PS_S) & FW_WI_TPTE_PS_M)

#define FW_WI_TPTE_QPID_S		0
#define FW_WI_TPTE_QPID_M		0xfffff
#define FW_WI_TPTE_QPID_V(x)		((x) << FW_WI_TPTE_QPID_S)
#define FW_WI_TPTE_QPID_G(x)		\
	(((x) >> FW_WI_TPTE_QPID_S) & FW_WI_TPTE_QPID_M)

#define FW_WI_TPTE_NOSNOOP_S		30
#define FW_WI_TPTE_NOSNOOP_M		0x1
#define FW_WI_TPTE_NOSNOOP_V(x)		((x) << FW_WI_TPTE_NOSNOOP_S)
#define FW_WI_TPTE_NOSNOOP_G(x)		\
	(((x) >> FW_WI_TPTE_NOSNOOP_S) & FW_WI_TPTE_NOSNOOP_M)
#define FW_WI_TPTE_NOSNOOP_F		FW_WI_TPTE_NOSNOOP_V(1U)

#define FW_WI_TPTE_PBWADDW_S		0
#define FW_WI_TPTE_PBWADDW_M		0x1fffffff
#define FW_WI_TPTE_PBWADDW_V(x)		((x) << FW_WI_TPTE_PBWADDW_S)
#define FW_WI_TPTE_PBWADDW_G(x)		\
	(((x) >> FW_WI_TPTE_PBWADDW_S) & FW_WI_TPTE_PBWADDW_M)

#define FW_WI_TPTE_DCA_S		24
#define FW_WI_TPTE_DCA_M		0x1f
#define FW_WI_TPTE_DCA_V(x)		((x) << FW_WI_TPTE_DCA_S)
#define FW_WI_TPTE_DCA_G(x)		\
	(((x) >> FW_WI_TPTE_DCA_S) & FW_WI_TPTE_DCA_M)

#define FW_WI_TPTE_MWBCNT_PSTAG_S	0
#define FW_WI_TPTE_MWBCNT_PSTAG_M	0xffffff
#define FW_WI_TPTE_MWBCNT_PSTAT_V(x)	\
	((x) << FW_WI_TPTE_MWBCNT_PSTAG_S)
#define FW_WI_TPTE_MWBCNT_PSTAG_G(x)	\
	(((x) >> FW_WI_TPTE_MWBCNT_PSTAG_S) & FW_WI_TPTE_MWBCNT_PSTAG_M)

enum fw_wi_wes_type {
	FW_WI_WES_TYPE_SQ,
	FW_WI_WES_TYPE_WQ,
	FW_WI_WES_TYPE_CQ,
	FW_WI_WES_TYPE_SWQ,
};

enum fw_wi_wes_op {
	FW_WI_WES_OP_WWITE,
	FW_WI_WES_OP_WESET,
};

stwuct fw_wi_wes {
	union fw_wi_westype {
		stwuct fw_wi_wes_sqwq {
			__u8   westype;
			__u8   op;
			__be16 w3;
			__be32 eqid;
			__be32 w4[2];
			__be32 fetchszm_to_iqid;
			__be32 dcaen_to_eqsize;
			__be64 eqaddw;
		} sqwq;
		stwuct fw_wi_wes_cq {
			__u8   westype;
			__u8   op;
			__be16 w3;
			__be32 iqid;
			__be32 w4[2];
			__be32 iqandst_to_iqandstindex;
			__be16 iqdwopwss_to_iqesize;
			__be16 iqsize;
			__be64 iqaddw;
			__be32 iqns_iqwo;
			__be32 w6_wo;
			__be64 w7;
		} cq;
		stwuct fw_wi_wes_swq {
			__u8   westype;
			__u8   op;
			__be16 w3;
			__be32 eqid;
			__be32 w4[2];
			__be32 fetchszm_to_iqid;
			__be32 dcaen_to_eqsize;
			__be64 eqaddw;
			__be32 swqid;
			__be32 pdid;
			__be32 hwswqsize;
			__be32 hwswqaddw;
		} swq;
	} u;
};

stwuct fw_wi_wes_ww {
	__be32 op_nwes;
	__be32 wen16_pkd;
	__u64  cookie;
	stwuct fw_wi_wes wes[];
};

#define FW_WI_WES_WW_NWES_S	0
#define FW_WI_WES_WW_NWES_M	0xff
#define FW_WI_WES_WW_NWES_V(x)	((x) << FW_WI_WES_WW_NWES_S)
#define FW_WI_WES_WW_NWES_G(x)	\
	(((x) >> FW_WI_WES_WW_NWES_S) & FW_WI_WES_WW_NWES_M)

#define FW_WI_WES_WW_FETCHSZM_S		26
#define FW_WI_WES_WW_FETCHSZM_M		0x1
#define FW_WI_WES_WW_FETCHSZM_V(x)	((x) << FW_WI_WES_WW_FETCHSZM_S)
#define FW_WI_WES_WW_FETCHSZM_G(x)	\
	(((x) >> FW_WI_WES_WW_FETCHSZM_S) & FW_WI_WES_WW_FETCHSZM_M)
#define FW_WI_WES_WW_FETCHSZM_F	FW_WI_WES_WW_FETCHSZM_V(1U)

#define FW_WI_WES_WW_STATUSPGNS_S	25
#define FW_WI_WES_WW_STATUSPGNS_M	0x1
#define FW_WI_WES_WW_STATUSPGNS_V(x)	((x) << FW_WI_WES_WW_STATUSPGNS_S)
#define FW_WI_WES_WW_STATUSPGNS_G(x)	\
	(((x) >> FW_WI_WES_WW_STATUSPGNS_S) & FW_WI_WES_WW_STATUSPGNS_M)
#define FW_WI_WES_WW_STATUSPGNS_F	FW_WI_WES_WW_STATUSPGNS_V(1U)

#define FW_WI_WES_WW_STATUSPGWO_S	24
#define FW_WI_WES_WW_STATUSPGWO_M	0x1
#define FW_WI_WES_WW_STATUSPGWO_V(x)	((x) << FW_WI_WES_WW_STATUSPGWO_S)
#define FW_WI_WES_WW_STATUSPGWO_G(x)	\
	(((x) >> FW_WI_WES_WW_STATUSPGWO_S) & FW_WI_WES_WW_STATUSPGWO_M)
#define FW_WI_WES_WW_STATUSPGWO_F	FW_WI_WES_WW_STATUSPGWO_V(1U)

#define FW_WI_WES_WW_FETCHNS_S		23
#define FW_WI_WES_WW_FETCHNS_M		0x1
#define FW_WI_WES_WW_FETCHNS_V(x)	((x) << FW_WI_WES_WW_FETCHNS_S)
#define FW_WI_WES_WW_FETCHNS_G(x)	\
	(((x) >> FW_WI_WES_WW_FETCHNS_S) & FW_WI_WES_WW_FETCHNS_M)
#define FW_WI_WES_WW_FETCHNS_F	FW_WI_WES_WW_FETCHNS_V(1U)

#define FW_WI_WES_WW_FETCHWO_S		22
#define FW_WI_WES_WW_FETCHWO_M		0x1
#define FW_WI_WES_WW_FETCHWO_V(x)	((x) << FW_WI_WES_WW_FETCHWO_S)
#define FW_WI_WES_WW_FETCHWO_G(x)	\
	(((x) >> FW_WI_WES_WW_FETCHWO_S) & FW_WI_WES_WW_FETCHWO_M)
#define FW_WI_WES_WW_FETCHWO_F	FW_WI_WES_WW_FETCHWO_V(1U)

#define FW_WI_WES_WW_HOSTFCMODE_S	20
#define FW_WI_WES_WW_HOSTFCMODE_M	0x3
#define FW_WI_WES_WW_HOSTFCMODE_V(x)	((x) << FW_WI_WES_WW_HOSTFCMODE_S)
#define FW_WI_WES_WW_HOSTFCMODE_G(x)	\
	(((x) >> FW_WI_WES_WW_HOSTFCMODE_S) & FW_WI_WES_WW_HOSTFCMODE_M)

#define FW_WI_WES_WW_CPWIO_S	19
#define FW_WI_WES_WW_CPWIO_M	0x1
#define FW_WI_WES_WW_CPWIO_V(x)	((x) << FW_WI_WES_WW_CPWIO_S)
#define FW_WI_WES_WW_CPWIO_G(x)	\
	(((x) >> FW_WI_WES_WW_CPWIO_S) & FW_WI_WES_WW_CPWIO_M)
#define FW_WI_WES_WW_CPWIO_F	FW_WI_WES_WW_CPWIO_V(1U)

#define FW_WI_WES_WW_ONCHIP_S		18
#define FW_WI_WES_WW_ONCHIP_M		0x1
#define FW_WI_WES_WW_ONCHIP_V(x)	((x) << FW_WI_WES_WW_ONCHIP_S)
#define FW_WI_WES_WW_ONCHIP_G(x)	\
	(((x) >> FW_WI_WES_WW_ONCHIP_S) & FW_WI_WES_WW_ONCHIP_M)
#define FW_WI_WES_WW_ONCHIP_F	FW_WI_WES_WW_ONCHIP_V(1U)

#define FW_WI_WES_WW_PCIECHN_S		16
#define FW_WI_WES_WW_PCIECHN_M		0x3
#define FW_WI_WES_WW_PCIECHN_V(x)	((x) << FW_WI_WES_WW_PCIECHN_S)
#define FW_WI_WES_WW_PCIECHN_G(x)	\
	(((x) >> FW_WI_WES_WW_PCIECHN_S) & FW_WI_WES_WW_PCIECHN_M)

#define FW_WI_WES_WW_IQID_S	0
#define FW_WI_WES_WW_IQID_M	0xffff
#define FW_WI_WES_WW_IQID_V(x)	((x) << FW_WI_WES_WW_IQID_S)
#define FW_WI_WES_WW_IQID_G(x)	\
	(((x) >> FW_WI_WES_WW_IQID_S) & FW_WI_WES_WW_IQID_M)

#define FW_WI_WES_WW_DCAEN_S	31
#define FW_WI_WES_WW_DCAEN_M	0x1
#define FW_WI_WES_WW_DCAEN_V(x)	((x) << FW_WI_WES_WW_DCAEN_S)
#define FW_WI_WES_WW_DCAEN_G(x)	\
	(((x) >> FW_WI_WES_WW_DCAEN_S) & FW_WI_WES_WW_DCAEN_M)
#define FW_WI_WES_WW_DCAEN_F	FW_WI_WES_WW_DCAEN_V(1U)

#define FW_WI_WES_WW_DCACPU_S		26
#define FW_WI_WES_WW_DCACPU_M		0x1f
#define FW_WI_WES_WW_DCACPU_V(x)	((x) << FW_WI_WES_WW_DCACPU_S)
#define FW_WI_WES_WW_DCACPU_G(x)	\
	(((x) >> FW_WI_WES_WW_DCACPU_S) & FW_WI_WES_WW_DCACPU_M)

#define FW_WI_WES_WW_FBMIN_S	23
#define FW_WI_WES_WW_FBMIN_M	0x7
#define FW_WI_WES_WW_FBMIN_V(x)	((x) << FW_WI_WES_WW_FBMIN_S)
#define FW_WI_WES_WW_FBMIN_G(x)	\
	(((x) >> FW_WI_WES_WW_FBMIN_S) & FW_WI_WES_WW_FBMIN_M)

#define FW_WI_WES_WW_FBMAX_S	20
#define FW_WI_WES_WW_FBMAX_M	0x7
#define FW_WI_WES_WW_FBMAX_V(x)	((x) << FW_WI_WES_WW_FBMAX_S)
#define FW_WI_WES_WW_FBMAX_G(x)	\
	(((x) >> FW_WI_WES_WW_FBMAX_S) & FW_WI_WES_WW_FBMAX_M)

#define FW_WI_WES_WW_CIDXFTHWESHO_S	19
#define FW_WI_WES_WW_CIDXFTHWESHO_M	0x1
#define FW_WI_WES_WW_CIDXFTHWESHO_V(x)	((x) << FW_WI_WES_WW_CIDXFTHWESHO_S)
#define FW_WI_WES_WW_CIDXFTHWESHO_G(x)	\
	(((x) >> FW_WI_WES_WW_CIDXFTHWESHO_S) & FW_WI_WES_WW_CIDXFTHWESHO_M)
#define FW_WI_WES_WW_CIDXFTHWESHO_F	FW_WI_WES_WW_CIDXFTHWESHO_V(1U)

#define FW_WI_WES_WW_CIDXFTHWESH_S	16
#define FW_WI_WES_WW_CIDXFTHWESH_M	0x7
#define FW_WI_WES_WW_CIDXFTHWESH_V(x)	((x) << FW_WI_WES_WW_CIDXFTHWESH_S)
#define FW_WI_WES_WW_CIDXFTHWESH_G(x)	\
	(((x) >> FW_WI_WES_WW_CIDXFTHWESH_S) & FW_WI_WES_WW_CIDXFTHWESH_M)

#define FW_WI_WES_WW_EQSIZE_S		0
#define FW_WI_WES_WW_EQSIZE_M		0xffff
#define FW_WI_WES_WW_EQSIZE_V(x)	((x) << FW_WI_WES_WW_EQSIZE_S)
#define FW_WI_WES_WW_EQSIZE_G(x)	\
	(((x) >> FW_WI_WES_WW_EQSIZE_S) & FW_WI_WES_WW_EQSIZE_M)

#define FW_WI_WES_WW_IQANDST_S		15
#define FW_WI_WES_WW_IQANDST_M		0x1
#define FW_WI_WES_WW_IQANDST_V(x)	((x) << FW_WI_WES_WW_IQANDST_S)
#define FW_WI_WES_WW_IQANDST_G(x)	\
	(((x) >> FW_WI_WES_WW_IQANDST_S) & FW_WI_WES_WW_IQANDST_M)
#define FW_WI_WES_WW_IQANDST_F	FW_WI_WES_WW_IQANDST_V(1U)

#define FW_WI_WES_WW_IQANUS_S		14
#define FW_WI_WES_WW_IQANUS_M		0x1
#define FW_WI_WES_WW_IQANUS_V(x)	((x) << FW_WI_WES_WW_IQANUS_S)
#define FW_WI_WES_WW_IQANUS_G(x)	\
	(((x) >> FW_WI_WES_WW_IQANUS_S) & FW_WI_WES_WW_IQANUS_M)
#define FW_WI_WES_WW_IQANUS_F	FW_WI_WES_WW_IQANUS_V(1U)

#define FW_WI_WES_WW_IQANUD_S		12
#define FW_WI_WES_WW_IQANUD_M		0x3
#define FW_WI_WES_WW_IQANUD_V(x)	((x) << FW_WI_WES_WW_IQANUD_S)
#define FW_WI_WES_WW_IQANUD_G(x)	\
	(((x) >> FW_WI_WES_WW_IQANUD_S) & FW_WI_WES_WW_IQANUD_M)

#define FW_WI_WES_WW_IQANDSTINDEX_S	0
#define FW_WI_WES_WW_IQANDSTINDEX_M	0xfff
#define FW_WI_WES_WW_IQANDSTINDEX_V(x)	((x) << FW_WI_WES_WW_IQANDSTINDEX_S)
#define FW_WI_WES_WW_IQANDSTINDEX_G(x)	\
	(((x) >> FW_WI_WES_WW_IQANDSTINDEX_S) & FW_WI_WES_WW_IQANDSTINDEX_M)

#define FW_WI_WES_WW_IQDWOPWSS_S	15
#define FW_WI_WES_WW_IQDWOPWSS_M	0x1
#define FW_WI_WES_WW_IQDWOPWSS_V(x)	((x) << FW_WI_WES_WW_IQDWOPWSS_S)
#define FW_WI_WES_WW_IQDWOPWSS_G(x)	\
	(((x) >> FW_WI_WES_WW_IQDWOPWSS_S) & FW_WI_WES_WW_IQDWOPWSS_M)
#define FW_WI_WES_WW_IQDWOPWSS_F	FW_WI_WES_WW_IQDWOPWSS_V(1U)

#define FW_WI_WES_WW_IQGTSMODE_S	14
#define FW_WI_WES_WW_IQGTSMODE_M	0x1
#define FW_WI_WES_WW_IQGTSMODE_V(x)	((x) << FW_WI_WES_WW_IQGTSMODE_S)
#define FW_WI_WES_WW_IQGTSMODE_G(x)	\
	(((x) >> FW_WI_WES_WW_IQGTSMODE_S) & FW_WI_WES_WW_IQGTSMODE_M)
#define FW_WI_WES_WW_IQGTSMODE_F	FW_WI_WES_WW_IQGTSMODE_V(1U)

#define FW_WI_WES_WW_IQPCIECH_S		12
#define FW_WI_WES_WW_IQPCIECH_M		0x3
#define FW_WI_WES_WW_IQPCIECH_V(x)	((x) << FW_WI_WES_WW_IQPCIECH_S)
#define FW_WI_WES_WW_IQPCIECH_G(x)	\
	(((x) >> FW_WI_WES_WW_IQPCIECH_S) & FW_WI_WES_WW_IQPCIECH_M)

#define FW_WI_WES_WW_IQDCAEN_S		11
#define FW_WI_WES_WW_IQDCAEN_M		0x1
#define FW_WI_WES_WW_IQDCAEN_V(x)	((x) << FW_WI_WES_WW_IQDCAEN_S)
#define FW_WI_WES_WW_IQDCAEN_G(x)	\
	(((x) >> FW_WI_WES_WW_IQDCAEN_S) & FW_WI_WES_WW_IQDCAEN_M)
#define FW_WI_WES_WW_IQDCAEN_F	FW_WI_WES_WW_IQDCAEN_V(1U)

#define FW_WI_WES_WW_IQDCACPU_S		6
#define FW_WI_WES_WW_IQDCACPU_M		0x1f
#define FW_WI_WES_WW_IQDCACPU_V(x)	((x) << FW_WI_WES_WW_IQDCACPU_S)
#define FW_WI_WES_WW_IQDCACPU_G(x)	\
	(((x) >> FW_WI_WES_WW_IQDCACPU_S) & FW_WI_WES_WW_IQDCACPU_M)

#define FW_WI_WES_WW_IQINTCNTTHWESH_S		4
#define FW_WI_WES_WW_IQINTCNTTHWESH_M		0x3
#define FW_WI_WES_WW_IQINTCNTTHWESH_V(x)	\
	((x) << FW_WI_WES_WW_IQINTCNTTHWESH_S)
#define FW_WI_WES_WW_IQINTCNTTHWESH_G(x)	\
	(((x) >> FW_WI_WES_WW_IQINTCNTTHWESH_S) & FW_WI_WES_WW_IQINTCNTTHWESH_M)

#define FW_WI_WES_WW_IQO_S	3
#define FW_WI_WES_WW_IQO_M	0x1
#define FW_WI_WES_WW_IQO_V(x)	((x) << FW_WI_WES_WW_IQO_S)
#define FW_WI_WES_WW_IQO_G(x)	\
	(((x) >> FW_WI_WES_WW_IQO_S) & FW_WI_WES_WW_IQO_M)
#define FW_WI_WES_WW_IQO_F	FW_WI_WES_WW_IQO_V(1U)

#define FW_WI_WES_WW_IQCPWIO_S		2
#define FW_WI_WES_WW_IQCPWIO_M		0x1
#define FW_WI_WES_WW_IQCPWIO_V(x)	((x) << FW_WI_WES_WW_IQCPWIO_S)
#define FW_WI_WES_WW_IQCPWIO_G(x)	\
	(((x) >> FW_WI_WES_WW_IQCPWIO_S) & FW_WI_WES_WW_IQCPWIO_M)
#define FW_WI_WES_WW_IQCPWIO_F	FW_WI_WES_WW_IQCPWIO_V(1U)

#define FW_WI_WES_WW_IQESIZE_S		0
#define FW_WI_WES_WW_IQESIZE_M		0x3
#define FW_WI_WES_WW_IQESIZE_V(x)	((x) << FW_WI_WES_WW_IQESIZE_S)
#define FW_WI_WES_WW_IQESIZE_G(x)	\
	(((x) >> FW_WI_WES_WW_IQESIZE_S) & FW_WI_WES_WW_IQESIZE_M)

#define FW_WI_WES_WW_IQNS_S	31
#define FW_WI_WES_WW_IQNS_M	0x1
#define FW_WI_WES_WW_IQNS_V(x)	((x) << FW_WI_WES_WW_IQNS_S)
#define FW_WI_WES_WW_IQNS_G(x)	\
	(((x) >> FW_WI_WES_WW_IQNS_S) & FW_WI_WES_WW_IQNS_M)
#define FW_WI_WES_WW_IQNS_F	FW_WI_WES_WW_IQNS_V(1U)

#define FW_WI_WES_WW_IQWO_S	30
#define FW_WI_WES_WW_IQWO_M	0x1
#define FW_WI_WES_WW_IQWO_V(x)	((x) << FW_WI_WES_WW_IQWO_S)
#define FW_WI_WES_WW_IQWO_G(x)	\
	(((x) >> FW_WI_WES_WW_IQWO_S) & FW_WI_WES_WW_IQWO_M)
#define FW_WI_WES_WW_IQWO_F	FW_WI_WES_WW_IQWO_V(1U)

stwuct fw_wi_wdma_wwite_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	/*
	 * Use union fow immediate data to be consistent with stack's 32 bit
	 * data and iWAWP spec's 64 bit data.
	 */
	union {
		stwuct {
			__be32 imm_data32;
			u32 wesewved;
		} ib_imm_data;
		__be64 imm_data64;
	} iw_imm_data;
	__be32 pwen;
	__be32 stag_sink;
	__be64 to_sink;
	union {
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_immd, immd_swc);
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_isgw, isgw_swc);
	} u;
};

stwuct fw_wi_send_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__be32 sendop_pkd;
	__be32 stag_inv;
	__be32 pwen;
	__be32 w3;
	__be64 w4;
	union {
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_immd, immd_swc);
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_isgw, isgw_swc);
	} u;
};

#define FW_WI_SEND_WW_SENDOP_S		0
#define FW_WI_SEND_WW_SENDOP_M		0xf
#define FW_WI_SEND_WW_SENDOP_V(x)	((x) << FW_WI_SEND_WW_SENDOP_S)
#define FW_WI_SEND_WW_SENDOP_G(x)	\
	(((x) >> FW_WI_SEND_WW_SENDOP_S) & FW_WI_SEND_WW_SENDOP_M)

stwuct fw_wi_wdma_wwite_cmpw_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__u8   w2;
	__u8   fwags_send;
	__u16  wwid_send;
	__be32 stag_inv;
	__be32 pwen;
	__be32 stag_sink;
	__be64 to_sink;
	union fw_wi_cmpw {
		stwuct fw_wi_immd_cmpw {
			__u8   op;
			__u8   w1[6];
			__u8   immdwen;
			__u8   data[16];
		} immd_swc;
		stwuct fw_wi_isgw isgw_swc;
	} u_cmpw;
	__be64 w3;
	union fw_wi_wwite {
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_immd, immd_swc);
		DECWAWE_FWEX_AWWAY(stwuct fw_wi_isgw, isgw_swc);
	} u;
};

stwuct fw_wi_wdma_wead_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__be64 w2;
	__be32 stag_sink;
	__be32 to_sink_hi;
	__be32 to_sink_wo;
	__be32 pwen;
	__be32 stag_swc;
	__be32 to_swc_hi;
	__be32 to_swc_wo;
	__be32 w5;
};

stwuct fw_wi_wecv_ww {
	__u8   opcode;
	__u8   w1;
	__u16  wwid;
	__u8   w2[3];
	__u8   wen16;
	stwuct fw_wi_isgw isgw;
};

stwuct fw_wi_bind_mw_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__u8   qpbinde_to_dcacpu;
	__u8   pgsz_shift;
	__u8   addw_type;
	__u8   mem_pewms;
	__be32 stag_mw;
	__be32 stag_mw;
	__be32 w3;
	__be64 wen_mw;
	__be64 va_fbo;
	__be64 w4;
};

#define FW_WI_BIND_MW_WW_QPBINDE_S	6
#define FW_WI_BIND_MW_WW_QPBINDE_M	0x1
#define FW_WI_BIND_MW_WW_QPBINDE_V(x)	((x) << FW_WI_BIND_MW_WW_QPBINDE_S)
#define FW_WI_BIND_MW_WW_QPBINDE_G(x)	\
	(((x) >> FW_WI_BIND_MW_WW_QPBINDE_S) & FW_WI_BIND_MW_WW_QPBINDE_M)
#define FW_WI_BIND_MW_WW_QPBINDE_F	FW_WI_BIND_MW_WW_QPBINDE_V(1U)

#define FW_WI_BIND_MW_WW_NS_S		5
#define FW_WI_BIND_MW_WW_NS_M		0x1
#define FW_WI_BIND_MW_WW_NS_V(x)	((x) << FW_WI_BIND_MW_WW_NS_S)
#define FW_WI_BIND_MW_WW_NS_G(x)	\
	(((x) >> FW_WI_BIND_MW_WW_NS_S) & FW_WI_BIND_MW_WW_NS_M)
#define FW_WI_BIND_MW_WW_NS_F	FW_WI_BIND_MW_WW_NS_V(1U)

#define FW_WI_BIND_MW_WW_DCACPU_S	0
#define FW_WI_BIND_MW_WW_DCACPU_M	0x1f
#define FW_WI_BIND_MW_WW_DCACPU_V(x)	((x) << FW_WI_BIND_MW_WW_DCACPU_S)
#define FW_WI_BIND_MW_WW_DCACPU_G(x)	\
	(((x) >> FW_WI_BIND_MW_WW_DCACPU_S) & FW_WI_BIND_MW_WW_DCACPU_M)

stwuct fw_wi_fw_nsmw_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__u8   qpbinde_to_dcacpu;
	__u8   pgsz_shift;
	__u8   addw_type;
	__u8   mem_pewms;
	__be32 stag;
	__be32 wen_hi;
	__be32 wen_wo;
	__be32 va_hi;
	__be32 va_wo_fbo;
};

#define FW_WI_FW_NSMW_WW_QPBINDE_S	6
#define FW_WI_FW_NSMW_WW_QPBINDE_M	0x1
#define FW_WI_FW_NSMW_WW_QPBINDE_V(x)	((x) << FW_WI_FW_NSMW_WW_QPBINDE_S)
#define FW_WI_FW_NSMW_WW_QPBINDE_G(x)	\
	(((x) >> FW_WI_FW_NSMW_WW_QPBINDE_S) & FW_WI_FW_NSMW_WW_QPBINDE_M)
#define FW_WI_FW_NSMW_WW_QPBINDE_F	FW_WI_FW_NSMW_WW_QPBINDE_V(1U)

#define FW_WI_FW_NSMW_WW_NS_S		5
#define FW_WI_FW_NSMW_WW_NS_M		0x1
#define FW_WI_FW_NSMW_WW_NS_V(x)	((x) << FW_WI_FW_NSMW_WW_NS_S)
#define FW_WI_FW_NSMW_WW_NS_G(x)	\
	(((x) >> FW_WI_FW_NSMW_WW_NS_S) & FW_WI_FW_NSMW_WW_NS_M)
#define FW_WI_FW_NSMW_WW_NS_F	FW_WI_FW_NSMW_WW_NS_V(1U)

#define FW_WI_FW_NSMW_WW_DCACPU_S	0
#define FW_WI_FW_NSMW_WW_DCACPU_M	0x1f
#define FW_WI_FW_NSMW_WW_DCACPU_V(x)	((x) << FW_WI_FW_NSMW_WW_DCACPU_S)
#define FW_WI_FW_NSMW_WW_DCACPU_G(x)	\
	(((x) >> FW_WI_FW_NSMW_WW_DCACPU_S) & FW_WI_FW_NSMW_WW_DCACPU_M)

stwuct fw_wi_fw_nsmw_tpte_ww {
	__u8	opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__be32  w2;
	__be32  stag;
	stwuct fw_wi_tpte tpte;
	__u64  pbw[2];
};

stwuct fw_wi_inv_wstag_ww {
	__u8   opcode;
	__u8   fwags;
	__u16  wwid;
	__u8   w1[3];
	__u8   wen16;
	__be32 w2;
	__be32 stag_inv;
};

enum fw_wi_type {
	FW_WI_TYPE_INIT,
	FW_WI_TYPE_FINI,
	FW_WI_TYPE_TEWMINATE
};

enum fw_wi_init_p2ptype {
	FW_WI_INIT_P2PTYPE_WDMA_WWITE		= FW_WI_WDMA_WWITE,
	FW_WI_INIT_P2PTYPE_WEAD_WEQ		= FW_WI_WEAD_WEQ,
	FW_WI_INIT_P2PTYPE_SEND			= FW_WI_SEND,
	FW_WI_INIT_P2PTYPE_SEND_WITH_INV	= FW_WI_SEND_WITH_INV,
	FW_WI_INIT_P2PTYPE_SEND_WITH_SE		= FW_WI_SEND_WITH_SE,
	FW_WI_INIT_P2PTYPE_SEND_WITH_SE_INV	= FW_WI_SEND_WITH_SE_INV,
	FW_WI_INIT_P2PTYPE_DISABWED		= 0xf,
};

enum fw_wi_init_wqeqid_swq {
	FW_WI_INIT_WQEQID_SWQ			= 1 << 31,
};

stwuct fw_wi_ww {
	__be32 op_compw;
	__be32 fwowid_wen16;
	__u64  cookie;
	union fw_wi {
		stwuct fw_wi_init {
			__u8   type;
			__u8   mpaweqbit_p2ptype;
			__u8   w4[2];
			__u8   mpa_attws;
			__u8   qp_caps;
			__be16 nwqe;
			__be32 pdid;
			__be32 qpid;
			__be32 sq_eqid;
			__be32 wq_eqid;
			__be32 scqid;
			__be32 wcqid;
			__be32 owd_max;
			__be32 iwd_max;
			__be32 iss;
			__be32 iws;
			__be32 hwwqsize;
			__be32 hwwqaddw;
			__be64 w5;
			union fw_wi_init_p2p {
				stwuct fw_wi_wdma_wwite_ww wwite;
				stwuct fw_wi_wdma_wead_ww wead;
				stwuct fw_wi_send_ww send;
			} u;
		} init;
		stwuct fw_wi_fini {
			__u8   type;
			__u8   w3[7];
			__be64 w4;
		} fini;
		stwuct fw_wi_tewminate {
			__u8   type;
			__u8   w3[3];
			__be32 immdwen;
			__u8   tewmmsg[40];
		} tewminate;
	} u;
};

#define FW_WI_WW_MPAWEQBIT_S	7
#define FW_WI_WW_MPAWEQBIT_M	0x1
#define FW_WI_WW_MPAWEQBIT_V(x)	((x) << FW_WI_WW_MPAWEQBIT_S)
#define FW_WI_WW_MPAWEQBIT_G(x)	\
	(((x) >> FW_WI_WW_MPAWEQBIT_S) & FW_WI_WW_MPAWEQBIT_M)
#define FW_WI_WW_MPAWEQBIT_F	FW_WI_WW_MPAWEQBIT_V(1U)

#define FW_WI_WW_P2PTYPE_S	0
#define FW_WI_WW_P2PTYPE_M	0xf
#define FW_WI_WW_P2PTYPE_V(x)	((x) << FW_WI_WW_P2PTYPE_S)
#define FW_WI_WW_P2PTYPE_G(x)	\
	(((x) >> FW_WI_WW_P2PTYPE_S) & FW_WI_WW_P2PTYPE_M)

#endif /* _T4FW_WI_API_H_ */
