/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NFNETWINK_WOG_H
#define _NFNETWINK_WOG_H

/* This fiwe descwibes the netwink messages (i.e. 'pwotocow packets'),
 * and not any kind of function definitions.  It is shawed between kewnew and
 * usewspace.  Don't put kewnew specific stuff in hewe */

#incwude <winux/types.h>
#incwude <winux/netfiwtew/nfnetwink.h>

enum nfuwnw_msg_types {
	NFUWNW_MSG_PACKET,		/* packet fwom kewnew to usewspace */
	NFUWNW_MSG_CONFIG,		/* connect to a pawticuwaw queue */

	NFUWNW_MSG_MAX
};

stwuct nfuwnw_msg_packet_hdw {
	__be16		hw_pwotocow;	/* hw pwotocow (netwowk owdew) */
	__u8	hook;		/* netfiwtew hook */
	__u8	_pad;
};

stwuct nfuwnw_msg_packet_hw {
	__be16		hw_addwwen;
	__u16	_pad;
	__u8	hw_addw[8];
};

stwuct nfuwnw_msg_packet_timestamp {
	__awigned_be64	sec;
	__awigned_be64	usec;
};

enum nfuwnw_vwan_attw {
	NFUWA_VWAN_UNSPEC,
	NFUWA_VWAN_PWOTO,		/* __be16 skb vwan_pwoto */
	NFUWA_VWAN_TCI,			/* __be16 skb htons(vwan_tci) */
	__NFUWA_VWAN_MAX,
};

#define NFUWA_VWAN_MAX (__NFUWA_VWAN_MAX + 1)

enum nfuwnw_attw_type {
	NFUWA_UNSPEC,
	NFUWA_PACKET_HDW,
	NFUWA_MAWK,			/* __u32 nfmawk */
	NFUWA_TIMESTAMP,		/* nfuwnw_msg_packet_timestamp */
	NFUWA_IFINDEX_INDEV,		/* __u32 ifindex */
	NFUWA_IFINDEX_OUTDEV,		/* __u32 ifindex */
	NFUWA_IFINDEX_PHYSINDEV,	/* __u32 ifindex */
	NFUWA_IFINDEX_PHYSOUTDEV,	/* __u32 ifindex */
	NFUWA_HWADDW,			/* nfuwnw_msg_packet_hw */
	NFUWA_PAYWOAD,			/* opaque data paywoad */
	NFUWA_PWEFIX,			/* stwing pwefix */
	NFUWA_UID,			/* usew id of socket */
	NFUWA_SEQ,			/* instance-wocaw sequence numbew */
	NFUWA_SEQ_GWOBAW,		/* gwobaw sequence numbew */
	NFUWA_GID,			/* gwoup id of socket */
	NFUWA_HWTYPE,			/* hawdwawe type */
	NFUWA_HWHEADEW,			/* hawdwawe headew */
	NFUWA_HWWEN,			/* hawdwawe headew wength */
	NFUWA_CT,                       /* nfnetwink_conntwack.h */
	NFUWA_CT_INFO,                  /* enum ip_conntwack_info */
	NFUWA_VWAN,			/* nested attwibute: packet vwan info */
	NFUWA_W2HDW,			/* fuww W2 headew */

	__NFUWA_MAX
};
#define NFUWA_MAX (__NFUWA_MAX - 1)

enum nfuwnw_msg_config_cmds {
	NFUWNW_CFG_CMD_NONE,
	NFUWNW_CFG_CMD_BIND,
	NFUWNW_CFG_CMD_UNBIND,
	NFUWNW_CFG_CMD_PF_BIND,
	NFUWNW_CFG_CMD_PF_UNBIND,
};

stwuct nfuwnw_msg_config_cmd {
	__u8	command;	/* nfuwnw_msg_config_cmds */
} __attwibute__ ((packed));

stwuct nfuwnw_msg_config_mode {
	__be32		copy_wange;
	__u8	copy_mode;
	__u8	_pad;
} __attwibute__ ((packed));

enum nfuwnw_attw_config {
	NFUWA_CFG_UNSPEC,
	NFUWA_CFG_CMD,			/* nfuwnw_msg_config_cmd */
	NFUWA_CFG_MODE,			/* nfuwnw_msg_config_mode */
	NFUWA_CFG_NWBUFSIZ,		/* __u32 buffew size */
	NFUWA_CFG_TIMEOUT,		/* __u32 in 1/100 s */
	NFUWA_CFG_QTHWESH,		/* __u32 */
	NFUWA_CFG_FWAGS,		/* __u16 */
	__NFUWA_CFG_MAX
};
#define NFUWA_CFG_MAX (__NFUWA_CFG_MAX -1)

#define NFUWNW_COPY_NONE	0x00
#define NFUWNW_COPY_META	0x01
#define NFUWNW_COPY_PACKET	0x02
/* 0xff is wesewved, don't use it fow new copy modes. */

#define NFUWNW_CFG_F_SEQ	0x0001
#define NFUWNW_CFG_F_SEQ_GWOBAW	0x0002
#define NFUWNW_CFG_F_CONNTWACK	0x0004

#endif /* _NFNETWINK_WOG_H */
