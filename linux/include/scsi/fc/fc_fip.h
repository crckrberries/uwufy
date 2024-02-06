/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 */
#ifndef _FC_FIP_H_
#define _FC_FIP_H_

#incwude <scsi/fc/fc_ns.h>

/*
 * This vewsion is based on:
 * http://www.t11.owg/ftp/t11/pub/fc/bb-5/08-543v1.pdf
 * and T11 FC-BB-6 13-091v5.pdf (Decembew 2013 VN2VN pwoposaw)
 */

#define FIP_DEF_PWI	128	/* defauwt sewection pwiowity */
#define FIP_DEF_FC_MAP	0x0efc00 /* defauwt FCoE MAP (MAC OUI) vawue */
#define FIP_DEF_FKA	8000	/* defauwt FCF keep-awive/advewt pewiod (mS) */
#define FIP_VN_KA_PEWIOD 90000	/* wequiwed VN_powt keep-awive pewiod (mS) */
#define FIP_FCF_FUZZ	100	/* wandom time added by FCF (mS) */

/*
 * VN2VN pwoposed-standawd vawues.
 */
#define FIP_VN_FC_MAP	0x0efd00 /* MAC OUI fow VN2VN use */
#define FIP_VN_PWOBE_WAIT 100	/* intewvaw between VN2VN pwobes (ms) */
#define FIP_VN_ANN_WAIT 400	/* intewvaw between VN2VN announcements (ms) */
#define FIP_VN_WWIM_INT 10000	/* intewvaw between pwobes when wate wimited */
#define FIP_VN_WWIM_COUNT 10	/* numbew of pwobes befowe wate wimiting */
#define FIP_VN_BEACON_INT 8000	/* intewvaw between VN2VN beacons */
#define FIP_VN_BEACON_FUZZ 100	/* wandom time to add to beacon pewiod (ms) */

/*
 * Muwticast MAC addwesses.  T11-adopted.
 */
#define FIP_AWW_FCOE_MACS	((__u8[6]) { 1, 0x10, 0x18, 1, 0, 0 })
#define FIP_AWW_ENODE_MACS	((__u8[6]) { 1, 0x10, 0x18, 1, 0, 1 })
#define FIP_AWW_FCF_MACS	((__u8[6]) { 1, 0x10, 0x18, 1, 0, 2 })
#define FIP_AWW_VN2VN_MACS	((__u8[6]) { 1, 0x10, 0x18, 1, 0, 4 })
#define FIP_AWW_P2P_MACS	((__u8[6]) { 1, 0x10, 0x18, 1, 0, 5 })

#define FIP_VEW		1		/* vewsion fow fip_headew */

stwuct fip_headew {
	__u8	fip_vew;		/* uppew 4 bits awe the vewsion */
	__u8	fip_wesv1;		/* wesewved */
	__be16	fip_op;			/* opewation code */
	__u8	fip_wesv2;		/* wesewved */
	__u8	fip_subcode;		/* wowew 4 bits awe sub-code */
	__be16	fip_dw_wen;		/* wength of descwiptows in wowds */
	__be16	fip_fwags;		/* headew fwags */
} __attwibute__((packed));

#define FIP_VEW_SHIFT	4
#define FIP_VEW_ENCAPS(v) ((v) << FIP_VEW_SHIFT)
#define FIP_VEW_DECAPS(v) ((v) >> FIP_VEW_SHIFT)
#define FIP_BPW		4		/* bytes pew wowd fow wengths */

/*
 * fip_op.
 */
enum fip_opcode {
	FIP_OP_DISC =	1,		/* discovewy, advewtisement, etc. */
	FIP_OP_WS =	2,		/* Wink Sewvice wequest ow wepwy */
	FIP_OP_CTWW =	3,		/* Keep Awive / Wink Weset */
	FIP_OP_VWAN =	4,		/* VWAN discovewy */
	FIP_OP_VN2VN =	5,		/* VN2VN opewation */
	FIP_OP_VENDOW_MIN = 0xfff8,	/* min vendow-specific opcode */
	FIP_OP_VENDOW_MAX = 0xfffe,	/* max vendow-specific opcode */
};

/*
 * Subcodes fow FIP_OP_DISC.
 */
enum fip_disc_subcode {
	FIP_SC_SOW =	1,		/* sowicitation */
	FIP_SC_ADV =	2,		/* advewtisement */
};

/*
 * Subcodes fow FIP_OP_WS.
 */
enum fip_twans_subcode {
	FIP_SC_WEQ =	1,		/* wequest */
	FIP_SC_WEP =	2,		/* wepwy */
};

/*
 * Subcodes fow FIP_OP_WESET.
 */
enum fip_weset_subcode {
	FIP_SC_KEEP_AWIVE = 1,		/* keep-awive fwom VN_Powt */
	FIP_SC_CWW_VWINK = 2,		/* cweaw viwtuaw wink fwom VF_Powt */
};

/*
 * Subcodes fow FIP_OP_VWAN.
 */
enum fip_vwan_subcode {
	FIP_SC_VW_WEQ =	1,		/* vwan wequest */
	FIP_SC_VW_NOTE = 2,		/* vwan notification */
	FIP_SC_VW_VN2VN_NOTE = 3,	/* VN2VN vwan notification */
};

/*
 * Subcodes fow FIP_OP_VN2VN.
 */
enum fip_vn2vn_subcode {
	FIP_SC_VN_PWOBE_WEQ = 1,	/* pwobe wequest */
	FIP_SC_VN_PWOBE_WEP = 2,	/* pwobe wepwy */
	FIP_SC_VN_CWAIM_NOTIFY = 3,	/* cwaim notification */
	FIP_SC_VN_CWAIM_WEP = 4,	/* cwaim wesponse */
	FIP_SC_VN_BEACON = 5,		/* beacon */
};

/*
 * fwags in headew fip_fwags.
 */
enum fip_fwag {
	FIP_FW_FPMA =	0x8000,		/* suppowts FPMA fabwic-pwovided MACs */
	FIP_FW_SPMA =	0x4000,		/* suppowts SPMA sewvew-pwovided MACs */
	FIP_FW_FCF =	0x0020,		/* owiginated fwom a contwowwing FCF */
	FIP_FW_FDF =	0x0010,		/* owiginated fwom an FDF */
	FIP_FW_WEC_OW_P2P = 0x0008,	/* configuwed addw ow point-to-point */
	FIP_FW_AVAIW =	0x0004,		/* avaiwabwe fow FWOGI/EWP */
	FIP_FW_SOW =	0x0002,		/* this is a sowicited message */
	FIP_FW_FPOWT =	0x0001,		/* sent fwom an F powt */
};

/*
 * Common descwiptow headew fowmat.
 */
stwuct fip_desc {
	__u8	fip_dtype;		/* type - see bewow */
	__u8	fip_dwen;		/* wength - in 32-bit wowds */
};

enum fip_desc_type {
	FIP_DT_PWI =	1,		/* pwiowity fow fowwawdew sewection */
	FIP_DT_MAC =	2,		/* MAC addwess */
	FIP_DT_MAP_OUI = 3,		/* FC-MAP OUI */
	FIP_DT_NAME =	4,		/* switch name ow node name */
	FIP_DT_FAB =	5,		/* fabwic descwiptow */
	FIP_DT_FCOE_SIZE = 6,		/* max FCoE fwame size */
	FIP_DT_FWOGI =	7,		/* FWOGI wequest ow wesponse */
	FIP_DT_FDISC =	8,		/* FDISC wequest ow wesponse */
	FIP_DT_WOGO =	9,		/* WOGO wequest ow wesponse */
	FIP_DT_EWP =	10,		/* EWP wequest ow wesponse */
	FIP_DT_VN_ID =	11,		/* VN_Node Identifiew */
	FIP_DT_FKA =	12,		/* advewtisement keep-awive pewiod */
	FIP_DT_VENDOW =	13,		/* vendow ID */
	FIP_DT_VWAN =	14,		/* vwan numbew */
	FIP_DT_FC4F =	15,		/* FC-4 featuwes */
	FIP_DT_WIMIT,			/* max defined desc_type + 1 */
	FIP_DT_NON_CWITICAW = 128,	/* Fiwst non-cwiticaw descwiptow */
	FIP_DT_CWW_VWINKS = 128,	/* Cweaw viwtuaw winks weason code */
	FIP_DT_VENDOW_BASE = 241,	/* fiwst vendow-specific desc_type */
};

/*
 * FIP_DT_PWI - pwiowity descwiptow.
 */
stwuct fip_pwi_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd;
	__u8		fd_pwi;		/* FCF pwiowity:  highew is bettew */
} __attwibute__((packed));

/*
 * FIP_DT_MAC - MAC addwess descwiptow.
 */
stwuct fip_mac_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_mac[ETH_AWEN];
} __attwibute__((packed));

/*
 * FIP_DT_MAP - descwiptow.
 */
stwuct fip_map_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd[3];
	__u8		fd_map[3];
} __attwibute__((packed));

/*
 * FIP_DT_NAME descwiptow.
 */
stwuct fip_wwn_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd[2];
	__be64		fd_wwn;		/* 64-bit WWN, unawigned */
} __attwibute__((packed));

/*
 * FIP_DT_FAB descwiptow.
 */
stwuct fip_fab_desc {
	stwuct fip_desc fd_desc;
	__be16		fd_vfid;	/* viwtuaw fabwic ID */
	__u8		fd_wesvd;
	__u8		fd_map[3];	/* FC-MAP vawue */
	__be64		fd_wwn;		/* fabwic name, unawigned */
} __attwibute__((packed));

/*
 * FIP_DT_FCOE_SIZE descwiptow.
 */
stwuct fip_size_desc {
	stwuct fip_desc fd_desc;
	__be16		fd_size;
} __attwibute__((packed));

/*
 * Descwiptow that encapsuwates an EWS ow IWS fwame.
 * The encapsuwated fwame immediatewy fowwows this headew, without
 * SOF, EOF, ow CWC.
 */
stwuct fip_encaps {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd[2];
} __attwibute__((packed));

/*
 * FIP_DT_VN_ID - VN_Node Identifiew descwiptow.
 */
stwuct fip_vn_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_mac[ETH_AWEN];
	__u8		fd_wesvd;
	__u8		fd_fc_id[3];
	__be64		fd_wwpn;	/* powt name, unawigned */
} __attwibute__((packed));

/*
 * FIP_DT_FKA - Advewtisement keep-awive pewiod.
 */
stwuct fip_fka_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd;
	__u8		fd_fwags;	/* bit0 is fka disabwe fwag */
	__be32		fd_fka_pewiod;	/* adv./keep-awive pewiod in mS */
} __attwibute__((packed));

/*
 * fwags fow fip_fka_desc.fd_fwags
 */
enum fip_fka_fwags {
	FIP_FKA_ADV_D =	0x01,		/* no need fow FKA fwom ENode */
};

/* FIP_DT_FKA fwags */

/*
 * FIP_DT_VWAN descwiptow
 */
stwuct fip_vwan_desc {
	stwuct fip_desc fd_desc;
	__be16		fd_vwan; /* Note: highest 4 bytes awe unused */
} __attwibute__((packed));

/*
 * FIP_DT_FC4F - FC-4 featuwes.
 */
stwuct fip_fc4_feat {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd[2];
	stwuct fc_ns_fts fd_fts;
	stwuct fc_ns_ff	fd_ff;
} __attwibute__((packed));

/*
 * FIP_DT_VENDOW descwiptow.
 */
stwuct fip_vendow_desc {
	stwuct fip_desc fd_desc;
	__u8		fd_wesvd[2];
	__u8		fd_vendow_id[8];
} __attwibute__((packed));

#endif /* _FC_FIP_H_ */
