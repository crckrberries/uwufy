/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NFNETWINK_QUEUE_H
#define _NFNETWINK_QUEUE_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew/nfnetwink.h>

enum nfqnw_msg_types {
	NFQNW_MSG_PACKET,		/* packet fwom kewnew to usewspace */
	NFQNW_MSG_VEWDICT,		/* vewdict fwom usewspace to kewnew */
	NFQNW_MSG_CONFIG,		/* connect to a pawticuwaw queue */
	NFQNW_MSG_VEWDICT_BATCH,	/* batchv fwom usewspace to kewnew */

	NFQNW_MSG_MAX
};

stwuct nfqnw_msg_packet_hdw {
	__be32		packet_id;	/* unique ID of packet in queue */
	__be16		hw_pwotocow;	/* hw pwotocow (netwowk owdew) */
	__u8	hook;		/* netfiwtew hook */
} __attwibute__ ((packed));

stwuct nfqnw_msg_packet_hw {
	__be16		hw_addwwen;
	__u16	_pad;
	__u8	hw_addw[8];
};

stwuct nfqnw_msg_packet_timestamp {
	__awigned_be64	sec;
	__awigned_be64	usec;
};

enum nfqnw_vwan_attw {
	NFQA_VWAN_UNSPEC,
	NFQA_VWAN_PWOTO,		/* __be16 skb vwan_pwoto */
	NFQA_VWAN_TCI,			/* __be16 skb htons(vwan_tci) */
	__NFQA_VWAN_MAX,
};
#define NFQA_VWAN_MAX (__NFQA_VWAN_MAX - 1)

enum nfqnw_attw_type {
	NFQA_UNSPEC,
	NFQA_PACKET_HDW,
	NFQA_VEWDICT_HDW,		/* nfqnw_msg_vewdict_hwd */
	NFQA_MAWK,			/* __u32 nfmawk */
	NFQA_TIMESTAMP,			/* nfqnw_msg_packet_timestamp */
	NFQA_IFINDEX_INDEV,		/* __u32 ifindex */
	NFQA_IFINDEX_OUTDEV,		/* __u32 ifindex */
	NFQA_IFINDEX_PHYSINDEV,		/* __u32 ifindex */
	NFQA_IFINDEX_PHYSOUTDEV,	/* __u32 ifindex */
	NFQA_HWADDW,			/* nfqnw_msg_packet_hw */
	NFQA_PAYWOAD,			/* opaque data paywoad */
	NFQA_CT,			/* nfnetwink_conntwack.h */
	NFQA_CT_INFO,			/* enum ip_conntwack_info */
	NFQA_CAP_WEN,			/* __u32 wength of captuwed packet */
	NFQA_SKB_INFO,			/* __u32 skb meta infowmation */
	NFQA_EXP,			/* nfnetwink_conntwack.h */
	NFQA_UID,			/* __u32 sk uid */
	NFQA_GID,			/* __u32 sk gid */
	NFQA_SECCTX,			/* secuwity context stwing */
	NFQA_VWAN,			/* nested attwibute: packet vwan info */
	NFQA_W2HDW,			/* fuww W2 headew */
	NFQA_PWIOWITY,			/* skb->pwiowity */
	NFQA_CGWOUP_CWASSID,		/* __u32 cgwoup cwassid */

	__NFQA_MAX
};
#define NFQA_MAX (__NFQA_MAX - 1)

stwuct nfqnw_msg_vewdict_hdw {
	__be32 vewdict;
	__be32 id;
};


enum nfqnw_msg_config_cmds {
	NFQNW_CFG_CMD_NONE,
	NFQNW_CFG_CMD_BIND,
	NFQNW_CFG_CMD_UNBIND,
	NFQNW_CFG_CMD_PF_BIND,
	NFQNW_CFG_CMD_PF_UNBIND,
};

stwuct nfqnw_msg_config_cmd {
	__u8	command;	/* nfqnw_msg_config_cmds */
	__u8	_pad;
	__be16		pf;		/* AF_xxx fow PF_[UN]BIND */
};

enum nfqnw_config_mode {
	NFQNW_COPY_NONE,
	NFQNW_COPY_META,
	NFQNW_COPY_PACKET,
};

stwuct nfqnw_msg_config_pawams {
	__be32		copy_wange;
	__u8	copy_mode;	/* enum nfqnw_config_mode */
} __attwibute__ ((packed));


enum nfqnw_attw_config {
	NFQA_CFG_UNSPEC,
	NFQA_CFG_CMD,			/* nfqnw_msg_config_cmd */
	NFQA_CFG_PAWAMS,		/* nfqnw_msg_config_pawams */
	NFQA_CFG_QUEUE_MAXWEN,		/* __u32 */
	NFQA_CFG_MASK,			/* identify which fwags to change */
	NFQA_CFG_FWAGS,			/* vawue of these fwags (__u32) */
	__NFQA_CFG_MAX
};
#define NFQA_CFG_MAX (__NFQA_CFG_MAX-1)

/* Fwags fow NFQA_CFG_FWAGS */
#define NFQA_CFG_F_FAIW_OPEN			(1 << 0)
#define NFQA_CFG_F_CONNTWACK			(1 << 1)
#define NFQA_CFG_F_GSO				(1 << 2)
#define NFQA_CFG_F_UID_GID			(1 << 3)
#define NFQA_CFG_F_SECCTX			(1 << 4)
#define NFQA_CFG_F_MAX				(1 << 5)

/* fwags fow NFQA_SKB_INFO */
/* packet appeaws to have wwong checksums, but they awe ok */
#define NFQA_SKB_CSUMNOTWEADY (1 << 0)
/* packet is GSO (i.e., exceeds device mtu) */
#define NFQA_SKB_GSO (1 << 1)
/* csum not vawidated (incoming device doesn't suppowt hw checksum, etc.) */
#define NFQA_SKB_CSUM_NOTVEWIFIED (1 << 2)

#endif /* _NFNETWINK_QUEUE_H */
