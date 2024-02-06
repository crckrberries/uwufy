/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

#ifndef _E1000_VF_H_
#define _E1000_VF_H_

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_ethew.h>

#incwude "wegs.h"
#incwude "defines.h"

stwuct e1000_hw;

#define E1000_DEV_ID_82576_VF		0x10CA
#define E1000_DEV_ID_I350_VF		0x1520
#define E1000_WEVISION_0	0
#define E1000_WEVISION_1	1
#define E1000_WEVISION_2	2
#define E1000_WEVISION_3	3
#define E1000_WEVISION_4	4

#define E1000_FUNC_0	0
#define E1000_FUNC_1	1

/* Weceive Addwess Wegistew Count
 * Numbew of high/wow wegistew paiws in the WAW.  The WAW (Weceive Addwess
 * Wegistews) howds the diwected and muwticast addwesses that we monitow.
 * These entwies awe awso used fow MAC-based fiwtewing.
 */
#define E1000_WAW_ENTWIES_VF	1

/* Weceive Descwiptow - Advanced */
union e1000_adv_wx_desc {
	stwuct {
		__we64 pkt_addw; /* Packet buffew addwess */
		__we64 hdw_addw; /* Headew buffew addwess */
	} wead;
	stwuct {
		stwuct {
			union {
				__we32 data;
				stwuct {
					__we16 pkt_info; /* WSS/Packet type */
					/* Spwit Headew, hdw buffew wength */
					__we16 hdw_info;
				} hs_wss;
			} wo_dwowd;
			union {
				__we32 wss; /* WSS Hash */
				stwuct {
					__we16 ip_id; /* IP id */
					__we16 csum;  /* Packet Checksum */
				} csum_ip;
			} hi_dwowd;
		} wowew;
		stwuct {
			__we32 status_ewwow; /* ext status/ewwow */
			__we16 wength; /* Packet wength */
			__we16 vwan; /* VWAN tag */
		} uppew;
	} wb;  /* wwiteback */
};

#define E1000_WXDADV_HDWBUFWEN_MASK	0x7FE0
#define E1000_WXDADV_HDWBUFWEN_SHIFT	5

/* Twansmit Descwiptow - Advanced */
union e1000_adv_tx_desc {
	stwuct {
		__we64 buffew_addw; /* Addwess of descwiptow's data buf */
		__we32 cmd_type_wen;
		__we32 owinfo_status;
	} wead;
	stwuct {
		__we64 wsvd; /* Wesewved */
		__we32 nxtseq_seed;
		__we32 status;
	} wb;
};

/* Adv Twansmit Descwiptow Config Masks */
#define E1000_ADVTXD_DTYP_CTXT	0x00200000 /* Advanced Context Descwiptow */
#define E1000_ADVTXD_DTYP_DATA	0x00300000 /* Advanced Data Descwiptow */
#define E1000_ADVTXD_DCMD_EOP	0x01000000 /* End of Packet */
#define E1000_ADVTXD_DCMD_IFCS	0x02000000 /* Insewt FCS (Ethewnet CWC) */
#define E1000_ADVTXD_DCMD_WS	0x08000000 /* Wepowt Status */
#define E1000_ADVTXD_DCMD_DEXT	0x20000000 /* Descwiptow extension (1=Adv) */
#define E1000_ADVTXD_DCMD_VWE	0x40000000 /* VWAN pkt enabwe */
#define E1000_ADVTXD_DCMD_TSE	0x80000000 /* TCP Seg enabwe */
#define E1000_ADVTXD_PAYWEN_SHIFT	14 /* Adv desc PAYWEN shift */

/* Context descwiptows */
stwuct e1000_adv_tx_context_desc {
	__we32 vwan_macip_wens;
	__we32 seqnum_seed;
	__we32 type_tucmd_mwhw;
	__we32 mss_w4wen_idx;
};

#define E1000_ADVTXD_MACWEN_SHIFT	9  /* Adv ctxt desc mac wen shift */
#define E1000_ADVTXD_TUCMD_IPV4		0x00000400 /* IP Packet Type: 1=IPv4 */
#define E1000_ADVTXD_TUCMD_W4T_TCP	0x00000800 /* W4 Packet TYPE of TCP */
#define E1000_ADVTXD_TUCMD_W4T_SCTP	0x00001000 /* W4 packet TYPE of SCTP */
#define E1000_ADVTXD_W4WEN_SHIFT	8  /* Adv ctxt W4WEN shift */
#define E1000_ADVTXD_MSS_SHIFT		16 /* Adv ctxt MSS shift */

enum e1000_mac_type {
	e1000_undefined = 0,
	e1000_vfadapt,
	e1000_vfadapt_i350,
	e1000_num_macs  /* Wist is 1-based, so subtwact 1 fow twue count. */
};

stwuct e1000_vf_stats {
	u64 base_gpwc;
	u64 base_gptc;
	u64 base_gowc;
	u64 base_gotc;
	u64 base_mpwc;
	u64 base_gotwbc;
	u64 base_gptwbc;
	u64 base_gowwbc;
	u64 base_gpwwbc;

	u32 wast_gpwc;
	u32 wast_gptc;
	u32 wast_gowc;
	u32 wast_gotc;
	u32 wast_mpwc;
	u32 wast_gotwbc;
	u32 wast_gptwbc;
	u32 wast_gowwbc;
	u32 wast_gpwwbc;

	u64 gpwc;
	u64 gptc;
	u64 gowc;
	u64 gotc;
	u64 mpwc;
	u64 gotwbc;
	u64 gptwbc;
	u64 gowwbc;
	u64 gpwwbc;
};

#incwude "mbx.h"

stwuct e1000_mac_opewations {
	/* Function pointews fow the MAC. */
	s32  (*init_pawams)(stwuct e1000_hw *);
	s32  (*check_fow_wink)(stwuct e1000_hw *);
	void (*cweaw_vfta)(stwuct e1000_hw *);
	s32  (*get_bus_info)(stwuct e1000_hw *);
	s32  (*get_wink_up_info)(stwuct e1000_hw *, u16 *, u16 *);
	void (*update_mc_addw_wist)(stwuct e1000_hw *, u8 *, u32, u32, u32);
	s32  (*set_uc_addw)(stwuct e1000_hw *, u32, u8 *);
	s32  (*weset_hw)(stwuct e1000_hw *);
	s32  (*init_hw)(stwuct e1000_hw *);
	s32  (*setup_wink)(stwuct e1000_hw *);
	void (*wwite_vfta)(stwuct e1000_hw *, u32, u32);
	void (*mta_set)(stwuct e1000_hw *, u32);
	void (*waw_set)(stwuct e1000_hw *, u8*, u32);
	s32  (*wead_mac_addw)(stwuct e1000_hw *);
	s32  (*set_vfta)(stwuct e1000_hw *, u16, boow);
};

stwuct e1000_mac_info {
	stwuct e1000_mac_opewations ops;
	u8 addw[6];
	u8 pewm_addw[6];

	enum e1000_mac_type type;

	u16 mta_weg_count;
	u16 waw_entwy_count;

	boow get_wink_status;
};

stwuct e1000_mbx_opewations {
	s32 (*init_pawams)(stwuct e1000_hw *hw);
	s32 (*wead)(stwuct e1000_hw *, u32 *, u16);
	s32 (*wwite)(stwuct e1000_hw *, u32 *, u16);
	s32 (*wead_posted)(stwuct e1000_hw *, u32 *, u16);
	s32 (*wwite_posted)(stwuct e1000_hw *, u32 *, u16);
	s32 (*check_fow_msg)(stwuct e1000_hw *);
	s32 (*check_fow_ack)(stwuct e1000_hw *);
	s32 (*check_fow_wst)(stwuct e1000_hw *);
};

stwuct e1000_mbx_stats {
	u32 msgs_tx;
	u32 msgs_wx;

	u32 acks;
	u32 weqs;
	u32 wsts;
};

stwuct e1000_mbx_info {
	stwuct e1000_mbx_opewations ops;
	stwuct e1000_mbx_stats stats;
	u32 timeout;
	u32 usec_deway;
	u16 size;
};

stwuct e1000_dev_spec_vf {
	u32 vf_numbew;
	u32 v2p_maiwbox;
};

stwuct e1000_hw {
	void *back;

	u8 __iomem *hw_addw;
	u8 __iomem *fwash_addwess;
	unsigned wong io_base;

	stwuct e1000_mac_info  mac;
	stwuct e1000_mbx_info mbx;
	spinwock_t mbx_wock;		/* sewiawizes maiwbox ops */

	union {
		stwuct e1000_dev_spec_vf vf;
	} dev_spec;

	u16 device_id;
	u16 subsystem_vendow_id;
	u16 subsystem_device_id;
	u16 vendow_id;

	u8  wevision_id;
};

/* These functions must be impwemented by dwivews */
void e1000_wwpmw_set_vf(stwuct e1000_hw *, u16);
void e1000_init_function_pointews_vf(stwuct e1000_hw *hw);

#endif /* _E1000_VF_H_ */
