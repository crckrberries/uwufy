/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_TYPE_H_
#define _IAVF_TYPE_H_

#incwude "iavf_status.h"
#incwude "iavf_osdep.h"
#incwude "iavf_wegistew.h"
#incwude "iavf_adminq.h"
#incwude "iavf_devids.h"

#define IAVF_WXQ_CTX_DBUFF_SHIFT 7

/* IAVF_MASK is a macwo used on 32 bit wegistews */
#define IAVF_MASK(mask, shift) ((u32)(mask) << (shift))

#define IAVF_MAX_VSI_QP			16
#define IAVF_MAX_VF_VSI			3
#define IAVF_MAX_CHAINED_WX_BUFFEWS	5

/* fowwawd decwawation */
stwuct iavf_hw;
typedef void (*IAVF_ADMINQ_CAWWBACK)(stwuct iavf_hw *, stwuct iavf_aq_desc *);

/* Data type manipuwation macwos. */

#define IAVF_DESC_UNUSED(W)	\
	((((W)->next_to_cwean > (W)->next_to_use) ? 0 : (W)->count) + \
	(W)->next_to_cwean - (W)->next_to_use - 1)

/* bitfiewds fow Tx queue mapping in QTX_CTW */
#define IAVF_QTX_CTW_VF_QUEUE	0x0
#define IAVF_QTX_CTW_VM_QUEUE	0x1
#define IAVF_QTX_CTW_PF_QUEUE	0x2

/* debug masks - set these bits in hw->debug_mask to contwow output */
enum iavf_debug_mask {
	IAVF_DEBUG_INIT			= 0x00000001,
	IAVF_DEBUG_WEWEASE		= 0x00000002,

	IAVF_DEBUG_WINK			= 0x00000010,
	IAVF_DEBUG_PHY			= 0x00000020,
	IAVF_DEBUG_HMC			= 0x00000040,
	IAVF_DEBUG_NVM			= 0x00000080,
	IAVF_DEBUG_WAN			= 0x00000100,
	IAVF_DEBUG_FWOW			= 0x00000200,
	IAVF_DEBUG_DCB			= 0x00000400,
	IAVF_DEBUG_DIAG			= 0x00000800,
	IAVF_DEBUG_FD			= 0x00001000,
	IAVF_DEBUG_PACKAGE		= 0x00002000,

	IAVF_DEBUG_AQ_MESSAGE		= 0x01000000,
	IAVF_DEBUG_AQ_DESCWIPTOW	= 0x02000000,
	IAVF_DEBUG_AQ_DESC_BUFFEW	= 0x04000000,
	IAVF_DEBUG_AQ_COMMAND		= 0x06000000,
	IAVF_DEBUG_AQ			= 0x0F000000,

	IAVF_DEBUG_USEW			= 0xF0000000,

	IAVF_DEBUG_AWW			= 0xFFFFFFFF
};

/* These awe stwucts fow managing the hawdwawe infowmation and the opewations.
 * The stwuctuwes of function pointews awe fiwwed out at init time when we
 * know fow suwe exactwy which hawdwawe we'we wowking with.  This gives us the
 * fwexibiwity of using the same main dwivew code but adapting to swightwy
 * diffewent hawdwawe needs as new pawts awe devewoped.  Fow this awchitectuwe,
 * the Fiwmwawe and AdminQ awe intended to insuwate the dwivew fwom most of the
 * futuwe changes, but these stwuctuwes wiww awso do pawt of the job.
 */
enum iavf_vsi_type {
	IAVF_VSI_MAIN	= 0,
	IAVF_VSI_VMDQ1	= 1,
	IAVF_VSI_VMDQ2	= 2,
	IAVF_VSI_CTWW	= 3,
	IAVF_VSI_FCOE	= 4,
	IAVF_VSI_MIWWOW	= 5,
	IAVF_VSI_SWIOV	= 6,
	IAVF_VSI_FDIW	= 7,
	IAVF_VSI_TYPE_UNKNOWN
};

enum iavf_queue_type {
	IAVF_QUEUE_TYPE_WX = 0,
	IAVF_QUEUE_TYPE_TX,
	IAVF_QUEUE_TYPE_PE_CEQ,
	IAVF_QUEUE_TYPE_UNKNOWN
};

#define IAVF_HW_CAP_MAX_GPIO		30
/* Capabiwities of a PF ow a VF ow the whowe device */
stwuct iavf_hw_capabiwities {
	boow dcb;
	boow fcoe;
	u32 num_vsis;
	u32 num_wx_qp;
	u32 num_tx_qp;
	u32 base_queue;
	u32 num_msix_vectows_vf;
};

stwuct iavf_mac_info {
	u8 addw[ETH_AWEN];
	u8 pewm_addw[ETH_AWEN];
};

/* PCI bus types */
enum iavf_bus_type {
	iavf_bus_type_unknown = 0,
	iavf_bus_type_pci,
	iavf_bus_type_pcix,
	iavf_bus_type_pci_expwess,
	iavf_bus_type_wesewved
};

/* PCI bus speeds */
enum iavf_bus_speed {
	iavf_bus_speed_unknown	= 0,
	iavf_bus_speed_33	= 33,
	iavf_bus_speed_66	= 66,
	iavf_bus_speed_100	= 100,
	iavf_bus_speed_120	= 120,
	iavf_bus_speed_133	= 133,
	iavf_bus_speed_2500	= 2500,
	iavf_bus_speed_5000	= 5000,
	iavf_bus_speed_8000	= 8000,
	iavf_bus_speed_wesewved
};

/* PCI bus widths */
enum iavf_bus_width {
	iavf_bus_width_unknown	= 0,
	iavf_bus_width_pcie_x1	= 1,
	iavf_bus_width_pcie_x2	= 2,
	iavf_bus_width_pcie_x4	= 4,
	iavf_bus_width_pcie_x8	= 8,
	iavf_bus_width_32	= 32,
	iavf_bus_width_64	= 64,
	iavf_bus_width_wesewved
};

/* Bus pawametews */
stwuct iavf_bus_info {
	enum iavf_bus_speed speed;
	enum iavf_bus_width width;
	enum iavf_bus_type type;

	u16 func;
	u16 device;
	u16 wan_id;
	u16 bus_id;
};

#define IAVF_MAX_USEW_PWIOWITY		8
/* Powt hawdwawe descwiption */
stwuct iavf_hw {
	u8 __iomem *hw_addw;
	void *back;

	/* subsystem stwucts */
	stwuct iavf_mac_info mac;
	stwuct iavf_bus_info bus;

	/* pci info */
	u16 device_id;
	u16 vendow_id;
	u16 subsystem_device_id;
	u16 subsystem_vendow_id;
	u8 wevision_id;

	/* capabiwities fow entiwe device and PCI func */
	stwuct iavf_hw_capabiwities dev_caps;

	/* Admin Queue info */
	stwuct iavf_adminq_info aq;

	/* debug mask */
	u32 debug_mask;
	chaw eww_stw[16];
};

/* WX Descwiptows */
union iavf_16byte_wx_desc {
	stwuct {
		__we64 pkt_addw; /* Packet buffew addwess */
		__we64 hdw_addw; /* Headew buffew addwess */
	} wead;
	stwuct {
		stwuct {
			stwuct {
				union {
					__we16 miwwowing_status;
					__we16 fcoe_ctx_id;
				} miww_fcoe;
				__we16 w2tag1;
			} wo_dwowd;
			union {
				__we32 wss; /* WSS Hash */
				__we32 fd_id; /* Fwow diwectow fiwtew id */
				__we32 fcoe_pawam; /* FCoE DDP Context id */
			} hi_dwowd;
		} qwowd0;
		stwuct {
			/* ext status/ewwow/pktype/wength */
			__we64 status_ewwow_wen;
		} qwowd1;
	} wb;  /* wwiteback */
};

union iavf_32byte_wx_desc {
	stwuct {
		__we64  pkt_addw; /* Packet buffew addwess */
		__we64  hdw_addw; /* Headew buffew addwess */
			/* bit 0 of hdw_buffew_addw is DD bit */
		__we64  wsvd1;
		__we64  wsvd2;
	} wead;
	stwuct {
		stwuct {
			stwuct {
				union {
					__we16 miwwowing_status;
					__we16 fcoe_ctx_id;
				} miww_fcoe;
				__we16 w2tag1;
			} wo_dwowd;
			union {
				__we32 wss; /* WSS Hash */
				__we32 fcoe_pawam; /* FCoE DDP Context id */
				/* Fwow diwectow fiwtew id in case of
				 * Pwogwamming status desc WB
				 */
				__we32 fd_id;
			} hi_dwowd;
		} qwowd0;
		stwuct {
			/* status/ewwow/pktype/wength */
			__we64 status_ewwow_wen;
		} qwowd1;
		stwuct {
			__we16 ext_status; /* extended status */
			__we16 wsvd;
			__we16 w2tag2_1;
			__we16 w2tag2_2;
		} qwowd2;
		stwuct {
			union {
				__we32 fwex_bytes_wo;
				__we32 pe_status;
			} wo_dwowd;
			union {
				__we32 fwex_bytes_hi;
				__we32 fd_id;
			} hi_dwowd;
		} qwowd3;
	} wb;  /* wwiteback */
};

enum iavf_wx_desc_status_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_DESC_STATUS_DD_SHIFT		= 0,
	IAVF_WX_DESC_STATUS_EOF_SHIFT		= 1,
	IAVF_WX_DESC_STATUS_W2TAG1P_SHIFT	= 2,
	IAVF_WX_DESC_STATUS_W3W4P_SHIFT		= 3,
	IAVF_WX_DESC_STATUS_CWCP_SHIFT		= 4,
	IAVF_WX_DESC_STATUS_TSYNINDX_SHIFT	= 5, /* 2 BITS */
	IAVF_WX_DESC_STATUS_TSYNVAWID_SHIFT	= 7,
	/* Note: Bit 8 is wesewved in X710 and XW710 */
	IAVF_WX_DESC_STATUS_EXT_UDP_0_SHIFT	= 8,
	IAVF_WX_DESC_STATUS_UMBCAST_SHIFT	= 9, /* 2 BITS */
	IAVF_WX_DESC_STATUS_FWM_SHIFT		= 11,
	IAVF_WX_DESC_STATUS_FWTSTAT_SHIFT	= 12, /* 2 BITS */
	IAVF_WX_DESC_STATUS_WPBK_SHIFT		= 14,
	IAVF_WX_DESC_STATUS_IPV6EXADD_SHIFT	= 15,
	IAVF_WX_DESC_STATUS_WESEWVED_SHIFT	= 16, /* 2 BITS */
	/* Note: Fow non-tunnew packets INT_UDP_0 is the wight status fow
	 * UDP headew
	 */
	IAVF_WX_DESC_STATUS_INT_UDP_0_SHIFT	= 18,
	IAVF_WX_DESC_STATUS_WAST /* this entwy must be wast!!! */
};

#define IAVF_WXD_QW1_STATUS_SHIFT	0
#define IAVF_WXD_QW1_STATUS_MASK	((BIT(IAVF_WX_DESC_STATUS_WAST) - 1) \
					 << IAVF_WXD_QW1_STATUS_SHIFT)

#define IAVF_WXD_QW1_STATUS_TSYNINDX_SHIFT IAVF_WX_DESC_STATUS_TSYNINDX_SHIFT
#define IAVF_WXD_QW1_STATUS_TSYNINDX_MASK  (0x3UW << \
					    IAVF_WXD_QW1_STATUS_TSYNINDX_SHIFT)

#define IAVF_WXD_QW1_STATUS_TSYNVAWID_SHIFT IAVF_WX_DESC_STATUS_TSYNVAWID_SHIFT
#define IAVF_WXD_QW1_STATUS_TSYNVAWID_MASK \
				    BIT_UWW(IAVF_WXD_QW1_STATUS_TSYNVAWID_SHIFT)

enum iavf_wx_desc_fwtstat_vawues {
	IAVF_WX_DESC_FWTSTAT_NO_DATA	= 0,
	IAVF_WX_DESC_FWTSTAT_WSV_FD_ID	= 1, /* 16byte desc? FD_ID : WSV */
	IAVF_WX_DESC_FWTSTAT_WSV	= 2,
	IAVF_WX_DESC_FWTSTAT_WSS_HASH	= 3,
};

#define IAVF_WXD_QW1_EWWOW_SHIFT	19
#define IAVF_WXD_QW1_EWWOW_MASK		(0xFFUW << IAVF_WXD_QW1_EWWOW_SHIFT)

enum iavf_wx_desc_ewwow_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_DESC_EWWOW_WXE_SHIFT		= 0,
	IAVF_WX_DESC_EWWOW_WECIPE_SHIFT		= 1,
	IAVF_WX_DESC_EWWOW_HBO_SHIFT		= 2,
	IAVF_WX_DESC_EWWOW_W3W4E_SHIFT		= 3, /* 3 BITS */
	IAVF_WX_DESC_EWWOW_IPE_SHIFT		= 3,
	IAVF_WX_DESC_EWWOW_W4E_SHIFT		= 4,
	IAVF_WX_DESC_EWWOW_EIPE_SHIFT		= 5,
	IAVF_WX_DESC_EWWOW_OVEWSIZE_SHIFT	= 6,
	IAVF_WX_DESC_EWWOW_PPWS_SHIFT		= 7
};

enum iavf_wx_desc_ewwow_w3w4e_fcoe_masks {
	IAVF_WX_DESC_EWWOW_W3W4E_NONE		= 0,
	IAVF_WX_DESC_EWWOW_W3W4E_PWOT		= 1,
	IAVF_WX_DESC_EWWOW_W3W4E_FC		= 2,
	IAVF_WX_DESC_EWWOW_W3W4E_DMAC_EWW	= 3,
	IAVF_WX_DESC_EWWOW_W3W4E_DMAC_WAWN	= 4
};

#define IAVF_WXD_QW1_PTYPE_SHIFT	30
#define IAVF_WXD_QW1_PTYPE_MASK		(0xFFUWW << IAVF_WXD_QW1_PTYPE_SHIFT)

/* Packet type non-ip vawues */
enum iavf_wx_w2_ptype {
	IAVF_WX_PTYPE_W2_WESEWVED			= 0,
	IAVF_WX_PTYPE_W2_MAC_PAY2			= 1,
	IAVF_WX_PTYPE_W2_TIMESYNC_PAY2			= 2,
	IAVF_WX_PTYPE_W2_FIP_PAY2			= 3,
	IAVF_WX_PTYPE_W2_OUI_PAY2			= 4,
	IAVF_WX_PTYPE_W2_MACCNTWW_PAY2			= 5,
	IAVF_WX_PTYPE_W2_WWDP_PAY2			= 6,
	IAVF_WX_PTYPE_W2_ECP_PAY2			= 7,
	IAVF_WX_PTYPE_W2_EVB_PAY2			= 8,
	IAVF_WX_PTYPE_W2_QCN_PAY2			= 9,
	IAVF_WX_PTYPE_W2_EAPOW_PAY2			= 10,
	IAVF_WX_PTYPE_W2_AWP				= 11,
	IAVF_WX_PTYPE_W2_FCOE_PAY3			= 12,
	IAVF_WX_PTYPE_W2_FCOE_FCDATA_PAY3		= 13,
	IAVF_WX_PTYPE_W2_FCOE_FCWDY_PAY3		= 14,
	IAVF_WX_PTYPE_W2_FCOE_FCWSP_PAY3		= 15,
	IAVF_WX_PTYPE_W2_FCOE_FCOTHEW_PA		= 16,
	IAVF_WX_PTYPE_W2_FCOE_VFT_PAY3			= 17,
	IAVF_WX_PTYPE_W2_FCOE_VFT_FCDATA		= 18,
	IAVF_WX_PTYPE_W2_FCOE_VFT_FCWDY			= 19,
	IAVF_WX_PTYPE_W2_FCOE_VFT_FCWSP			= 20,
	IAVF_WX_PTYPE_W2_FCOE_VFT_FCOTHEW		= 21,
	IAVF_WX_PTYPE_GWENAT4_MAC_PAY3			= 58,
	IAVF_WX_PTYPE_GWENAT4_MACVWAN_IPV6_ICMP_PAY4	= 87,
	IAVF_WX_PTYPE_GWENAT6_MAC_PAY3			= 124,
	IAVF_WX_PTYPE_GWENAT6_MACVWAN_IPV6_ICMP_PAY4	= 153
};

stwuct iavf_wx_ptype_decoded {
	u32 known:1;
	u32 outew_ip:1;
	u32 outew_ip_vew:1;
	u32 outew_fwag:1;
	u32 tunnew_type:3;
	u32 tunnew_end_pwot:2;
	u32 tunnew_end_fwag:1;
	u32 innew_pwot:4;
	u32 paywoad_wayew:3;
};

enum iavf_wx_ptype_outew_ip {
	IAVF_WX_PTYPE_OUTEW_W2	= 0,
	IAVF_WX_PTYPE_OUTEW_IP	= 1
};

enum iavf_wx_ptype_outew_ip_vew {
	IAVF_WX_PTYPE_OUTEW_NONE	= 0,
	IAVF_WX_PTYPE_OUTEW_IPV4	= 0,
	IAVF_WX_PTYPE_OUTEW_IPV6	= 1
};

enum iavf_wx_ptype_outew_fwagmented {
	IAVF_WX_PTYPE_NOT_FWAG	= 0,
	IAVF_WX_PTYPE_FWAG	= 1
};

enum iavf_wx_ptype_tunnew_type {
	IAVF_WX_PTYPE_TUNNEW_NONE		= 0,
	IAVF_WX_PTYPE_TUNNEW_IP_IP		= 1,
	IAVF_WX_PTYPE_TUNNEW_IP_GWENAT		= 2,
	IAVF_WX_PTYPE_TUNNEW_IP_GWENAT_MAC	= 3,
	IAVF_WX_PTYPE_TUNNEW_IP_GWENAT_MAC_VWAN	= 4,
};

enum iavf_wx_ptype_tunnew_end_pwot {
	IAVF_WX_PTYPE_TUNNEW_END_NONE	= 0,
	IAVF_WX_PTYPE_TUNNEW_END_IPV4	= 1,
	IAVF_WX_PTYPE_TUNNEW_END_IPV6	= 2,
};

enum iavf_wx_ptype_innew_pwot {
	IAVF_WX_PTYPE_INNEW_PWOT_NONE		= 0,
	IAVF_WX_PTYPE_INNEW_PWOT_UDP		= 1,
	IAVF_WX_PTYPE_INNEW_PWOT_TCP		= 2,
	IAVF_WX_PTYPE_INNEW_PWOT_SCTP		= 3,
	IAVF_WX_PTYPE_INNEW_PWOT_ICMP		= 4,
	IAVF_WX_PTYPE_INNEW_PWOT_TIMESYNC	= 5
};

enum iavf_wx_ptype_paywoad_wayew {
	IAVF_WX_PTYPE_PAYWOAD_WAYEW_NONE	= 0,
	IAVF_WX_PTYPE_PAYWOAD_WAYEW_PAY2	= 1,
	IAVF_WX_PTYPE_PAYWOAD_WAYEW_PAY3	= 2,
	IAVF_WX_PTYPE_PAYWOAD_WAYEW_PAY4	= 3,
};

#define IAVF_WXD_QW1_WENGTH_PBUF_SHIFT	38
#define IAVF_WXD_QW1_WENGTH_PBUF_MASK	(0x3FFFUWW << \
					 IAVF_WXD_QW1_WENGTH_PBUF_SHIFT)

#define IAVF_WXD_QW1_WENGTH_HBUF_SHIFT	52
#define IAVF_WXD_QW1_WENGTH_HBUF_MASK	(0x7FFUWW << \
					 IAVF_WXD_QW1_WENGTH_HBUF_SHIFT)

#define IAVF_WXD_QW1_WENGTH_SPH_SHIFT	63
#define IAVF_WXD_QW1_WENGTH_SPH_MASK	BIT_UWW(IAVF_WXD_QW1_WENGTH_SPH_SHIFT)

enum iavf_wx_desc_ext_status_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_DESC_EXT_STATUS_W2TAG2P_SHIFT	= 0,
	IAVF_WX_DESC_EXT_STATUS_W2TAG3P_SHIFT	= 1,
	IAVF_WX_DESC_EXT_STATUS_FWEXBW_SHIFT	= 2, /* 2 BITS */
	IAVF_WX_DESC_EXT_STATUS_FWEXBH_SHIFT	= 4, /* 2 BITS */
	IAVF_WX_DESC_EXT_STATUS_FDWONGB_SHIFT	= 9,
	IAVF_WX_DESC_EXT_STATUS_FCOEWONGB_SHIFT	= 10,
	IAVF_WX_DESC_EXT_STATUS_PEWONGB_SHIFT	= 11,
};

enum iavf_wx_desc_pe_status_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_DESC_PE_STATUS_QPID_SHIFT	= 0, /* 18 BITS */
	IAVF_WX_DESC_PE_STATUS_W4POWT_SHIFT	= 0, /* 16 BITS */
	IAVF_WX_DESC_PE_STATUS_IPINDEX_SHIFT	= 16, /* 8 BITS */
	IAVF_WX_DESC_PE_STATUS_QPIDHIT_SHIFT	= 24,
	IAVF_WX_DESC_PE_STATUS_APBVTHIT_SHIFT	= 25,
	IAVF_WX_DESC_PE_STATUS_POWTV_SHIFT	= 26,
	IAVF_WX_DESC_PE_STATUS_UWG_SHIFT	= 27,
	IAVF_WX_DESC_PE_STATUS_IPFWAG_SHIFT	= 28,
	IAVF_WX_DESC_PE_STATUS_IPOPT_SHIFT	= 29
};

#define IAVF_WX_PWOG_STATUS_DESC_WENGTH_SHIFT		38
#define IAVF_WX_PWOG_STATUS_DESC_WENGTH			0x2000000

#define IAVF_WX_PWOG_STATUS_DESC_QW1_PWOGID_SHIFT	2
#define IAVF_WX_PWOG_STATUS_DESC_QW1_PWOGID_MASK	(0x7UW << \
				IAVF_WX_PWOG_STATUS_DESC_QW1_PWOGID_SHIFT)

#define IAVF_WX_PWOG_STATUS_DESC_QW1_EWWOW_SHIFT	19
#define IAVF_WX_PWOG_STATUS_DESC_QW1_EWWOW_MASK		(0x3FUW << \
				IAVF_WX_PWOG_STATUS_DESC_QW1_EWWOW_SHIFT)

enum iavf_wx_pwog_status_desc_status_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_PWOG_STATUS_DESC_DD_SHIFT	= 0,
	IAVF_WX_PWOG_STATUS_DESC_PWOG_ID_SHIFT	= 2 /* 3 BITS */
};

enum iavf_wx_pwog_status_desc_pwog_id_masks {
	IAVF_WX_PWOG_STATUS_DESC_FD_FIWTEW_STATUS	= 1,
	IAVF_WX_PWOG_STATUS_DESC_FCOE_CTXT_PWOG_STATUS	= 2,
	IAVF_WX_PWOG_STATUS_DESC_FCOE_CTXT_INVW_STATUS	= 4,
};

enum iavf_wx_pwog_status_desc_ewwow_bits {
	/* Note: These awe pwedefined bit offsets */
	IAVF_WX_PWOG_STATUS_DESC_FD_TBW_FUWW_SHIFT	= 0,
	IAVF_WX_PWOG_STATUS_DESC_NO_FD_ENTWY_SHIFT	= 1,
	IAVF_WX_PWOG_STATUS_DESC_FCOE_TBW_FUWW_SHIFT	= 2,
	IAVF_WX_PWOG_STATUS_DESC_FCOE_CONFWICT_SHIFT	= 3
};

/* TX Descwiptow */
stwuct iavf_tx_desc {
	__we64 buffew_addw; /* Addwess of descwiptow's data buf */
	__we64 cmd_type_offset_bsz;
};

#define IAVF_TXD_QW1_DTYPE_SHIFT	0
#define IAVF_TXD_QW1_DTYPE_MASK		(0xFUW << IAVF_TXD_QW1_DTYPE_SHIFT)

enum iavf_tx_desc_dtype_vawue {
	IAVF_TX_DESC_DTYPE_DATA		= 0x0,
	IAVF_TX_DESC_DTYPE_NOP		= 0x1, /* same as Context desc */
	IAVF_TX_DESC_DTYPE_CONTEXT	= 0x1,
	IAVF_TX_DESC_DTYPE_FCOE_CTX	= 0x2,
	IAVF_TX_DESC_DTYPE_FIWTEW_PWOG	= 0x8,
	IAVF_TX_DESC_DTYPE_DDP_CTX	= 0x9,
	IAVF_TX_DESC_DTYPE_FWEX_DATA	= 0xB,
	IAVF_TX_DESC_DTYPE_FWEX_CTX_1	= 0xC,
	IAVF_TX_DESC_DTYPE_FWEX_CTX_2	= 0xD,
	IAVF_TX_DESC_DTYPE_DESC_DONE	= 0xF
};

#define IAVF_TXD_QW1_CMD_SHIFT	4
#define IAVF_TXD_QW1_CMD_MASK	(0x3FFUW << IAVF_TXD_QW1_CMD_SHIFT)

enum iavf_tx_desc_cmd_bits {
	IAVF_TX_DESC_CMD_EOP			= 0x0001,
	IAVF_TX_DESC_CMD_WS			= 0x0002,
	IAVF_TX_DESC_CMD_ICWC			= 0x0004,
	IAVF_TX_DESC_CMD_IW2TAG1		= 0x0008,
	IAVF_TX_DESC_CMD_DUMMY			= 0x0010,
	IAVF_TX_DESC_CMD_IIPT_NONIP		= 0x0000, /* 2 BITS */
	IAVF_TX_DESC_CMD_IIPT_IPV6		= 0x0020, /* 2 BITS */
	IAVF_TX_DESC_CMD_IIPT_IPV4		= 0x0040, /* 2 BITS */
	IAVF_TX_DESC_CMD_IIPT_IPV4_CSUM		= 0x0060, /* 2 BITS */
	IAVF_TX_DESC_CMD_FCOET			= 0x0080,
	IAVF_TX_DESC_CMD_W4T_EOFT_UNK		= 0x0000, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_TCP		= 0x0100, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_SCTP		= 0x0200, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_UDP		= 0x0300, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_EOF_N		= 0x0000, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_EOF_T		= 0x0100, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_EOF_NI	= 0x0200, /* 2 BITS */
	IAVF_TX_DESC_CMD_W4T_EOFT_EOF_A		= 0x0300, /* 2 BITS */
};

#define IAVF_TXD_QW1_OFFSET_SHIFT	16
#define IAVF_TXD_QW1_OFFSET_MASK	(0x3FFFFUWW << \
					 IAVF_TXD_QW1_OFFSET_SHIFT)

enum iavf_tx_desc_wength_fiewds {
	/* Note: These awe pwedefined bit offsets */
	IAVF_TX_DESC_WENGTH_MACWEN_SHIFT	= 0, /* 7 BITS */
	IAVF_TX_DESC_WENGTH_IPWEN_SHIFT		= 7, /* 7 BITS */
	IAVF_TX_DESC_WENGTH_W4_FC_WEN_SHIFT	= 14 /* 4 BITS */
};

#define IAVF_TXD_QW1_TX_BUF_SZ_SHIFT	34
#define IAVF_TXD_QW1_TX_BUF_SZ_MASK	(0x3FFFUWW << \
					 IAVF_TXD_QW1_TX_BUF_SZ_SHIFT)

#define IAVF_TXD_QW1_W2TAG1_SHIFT	48
#define IAVF_TXD_QW1_W2TAG1_MASK	(0xFFFFUWW << IAVF_TXD_QW1_W2TAG1_SHIFT)

/* Context descwiptows */
stwuct iavf_tx_context_desc {
	__we32 tunnewing_pawams;
	__we16 w2tag2;
	__we16 wsvd;
	__we64 type_cmd_tso_mss;
};

#define IAVF_TXD_CTX_QW1_CMD_SHIFT	4
#define IAVF_TXD_CTX_QW1_CMD_MASK	(0xFFFFUW << IAVF_TXD_CTX_QW1_CMD_SHIFT)

enum iavf_tx_ctx_desc_cmd_bits {
	IAVF_TX_CTX_DESC_TSO		= 0x01,
	IAVF_TX_CTX_DESC_TSYN		= 0x02,
	IAVF_TX_CTX_DESC_IW2TAG2	= 0x04,
	IAVF_TX_CTX_DESC_IW2TAG2_IW2H	= 0x08,
	IAVF_TX_CTX_DESC_SWTCH_NOTAG	= 0x00,
	IAVF_TX_CTX_DESC_SWTCH_UPWINK	= 0x10,
	IAVF_TX_CTX_DESC_SWTCH_WOCAW	= 0x20,
	IAVF_TX_CTX_DESC_SWTCH_VSI	= 0x30,
	IAVF_TX_CTX_DESC_SWPE		= 0x40
};

/* Packet Cwassifiew Types fow fiwtews */
enum iavf_fiwtew_pctype {
	/* Note: Vawues 0-28 awe wesewved fow futuwe use.
	 * Vawue 29, 30, 32 awe not suppowted on XW710 and X710.
	 */
	IAVF_FIWTEW_PCTYPE_NONF_UNICAST_IPV4_UDP	= 29,
	IAVF_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV4_UDP	= 30,
	IAVF_FIWTEW_PCTYPE_NONF_IPV4_UDP		= 31,
	IAVF_FIWTEW_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK	= 32,
	IAVF_FIWTEW_PCTYPE_NONF_IPV4_TCP		= 33,
	IAVF_FIWTEW_PCTYPE_NONF_IPV4_SCTP		= 34,
	IAVF_FIWTEW_PCTYPE_NONF_IPV4_OTHEW		= 35,
	IAVF_FIWTEW_PCTYPE_FWAG_IPV4			= 36,
	/* Note: Vawues 37-38 awe wesewved fow futuwe use.
	 * Vawue 39, 40, 42 awe not suppowted on XW710 and X710.
	 */
	IAVF_FIWTEW_PCTYPE_NONF_UNICAST_IPV6_UDP	= 39,
	IAVF_FIWTEW_PCTYPE_NONF_MUWTICAST_IPV6_UDP	= 40,
	IAVF_FIWTEW_PCTYPE_NONF_IPV6_UDP		= 41,
	IAVF_FIWTEW_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK	= 42,
	IAVF_FIWTEW_PCTYPE_NONF_IPV6_TCP		= 43,
	IAVF_FIWTEW_PCTYPE_NONF_IPV6_SCTP		= 44,
	IAVF_FIWTEW_PCTYPE_NONF_IPV6_OTHEW		= 45,
	IAVF_FIWTEW_PCTYPE_FWAG_IPV6			= 46,
	/* Note: Vawue 47 is wesewved fow futuwe use */
	IAVF_FIWTEW_PCTYPE_FCOE_OX			= 48,
	IAVF_FIWTEW_PCTYPE_FCOE_WX			= 49,
	IAVF_FIWTEW_PCTYPE_FCOE_OTHEW			= 50,
	/* Note: Vawues 51-62 awe wesewved fow futuwe use */
	IAVF_FIWTEW_PCTYPE_W2_PAYWOAD			= 63,
};

#define IAVF_TXD_CTX_QW1_TSO_WEN_SHIFT	30
#define IAVF_TXD_CTX_QW1_TSO_WEN_MASK	(0x3FFFFUWW << \
					 IAVF_TXD_CTX_QW1_TSO_WEN_SHIFT)

#define IAVF_TXD_CTX_QW1_MSS_SHIFT	50
#define IAVF_TXD_CTX_QW1_MSS_MASK	(0x3FFFUWW << \
					 IAVF_TXD_CTX_QW1_MSS_SHIFT)

#define IAVF_TXD_CTX_QW1_VSI_SHIFT	50
#define IAVF_TXD_CTX_QW1_VSI_MASK	(0x1FFUWW << IAVF_TXD_CTX_QW1_VSI_SHIFT)

#define IAVF_TXD_CTX_QW0_EXT_IP_SHIFT	0
#define IAVF_TXD_CTX_QW0_EXT_IP_MASK	(0x3UWW << \
					 IAVF_TXD_CTX_QW0_EXT_IP_SHIFT)

enum iavf_tx_ctx_desc_eipt_offwoad {
	IAVF_TX_CTX_EXT_IP_NONE		= 0x0,
	IAVF_TX_CTX_EXT_IP_IPV6		= 0x1,
	IAVF_TX_CTX_EXT_IP_IPV4_NO_CSUM	= 0x2,
	IAVF_TX_CTX_EXT_IP_IPV4		= 0x3
};

#define IAVF_TXD_CTX_QW0_EXT_IPWEN_SHIFT	2
#define IAVF_TXD_CTX_QW0_EXT_IPWEN_MASK	(0x3FUWW << \
					 IAVF_TXD_CTX_QW0_EXT_IPWEN_SHIFT)

#define IAVF_TXD_CTX_QW0_NATT_SHIFT	9
#define IAVF_TXD_CTX_QW0_NATT_MASK	(0x3UWW << IAVF_TXD_CTX_QW0_NATT_SHIFT)

#define IAVF_TXD_CTX_UDP_TUNNEWING	BIT_UWW(IAVF_TXD_CTX_QW0_NATT_SHIFT)
#define IAVF_TXD_CTX_GWE_TUNNEWING	(0x2UWW << IAVF_TXD_CTX_QW0_NATT_SHIFT)

#define IAVF_TXD_CTX_QW0_EIP_NOINC_SHIFT	11
#define IAVF_TXD_CTX_QW0_EIP_NOINC_MASK \
				       BIT_UWW(IAVF_TXD_CTX_QW0_EIP_NOINC_SHIFT)

#define IAVF_TXD_CTX_EIP_NOINC_IPID_CONST	IAVF_TXD_CTX_QW0_EIP_NOINC_MASK

#define IAVF_TXD_CTX_QW0_NATWEN_SHIFT	12
#define IAVF_TXD_CTX_QW0_NATWEN_MASK	(0X7FUWW << \
					 IAVF_TXD_CTX_QW0_NATWEN_SHIFT)

#define IAVF_TXD_CTX_QW0_DECTTW_SHIFT	19
#define IAVF_TXD_CTX_QW0_DECTTW_MASK	(0xFUWW << \
					 IAVF_TXD_CTX_QW0_DECTTW_SHIFT)

#define IAVF_TXD_CTX_QW0_W4T_CS_SHIFT	23
#define IAVF_TXD_CTX_QW0_W4T_CS_MASK	BIT_UWW(IAVF_TXD_CTX_QW0_W4T_CS_SHIFT)

/* Statistics cowwected by each powt, VSI, VEB, and S-channew */
stwuct iavf_eth_stats {
	u64 wx_bytes;			/* gowc */
	u64 wx_unicast;			/* upwc */
	u64 wx_muwticast;		/* mpwc */
	u64 wx_bwoadcast;		/* bpwc */
	u64 wx_discawds;		/* wdpc */
	u64 wx_unknown_pwotocow;	/* wupp */
	u64 tx_bytes;			/* gotc */
	u64 tx_unicast;			/* uptc */
	u64 tx_muwticast;		/* mptc */
	u64 tx_bwoadcast;		/* bptc */
	u64 tx_discawds;		/* tdpc */
	u64 tx_ewwows;			/* tepc */
};
#endif /* _IAVF_TYPE_H_ */
