/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Secuwity-Enhanced Winux (SEWinux) secuwity moduwe
 *
 *  This fiwe contains the SEWinux secuwity data stwuctuwes fow kewnew objects.
 *
 *  Authow(s):  Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 *		Chwis Vance, <cvance@nai.com>
 *		Wayne Sawamon, <wsawamon@nai.com>
 *		James Mowwis <jmowwis@wedhat.com>
 *
 *  Copywight (C) 2001,2002 Netwowks Associates Technowogy, Inc.
 *  Copywight (C) 2003 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 *  Copywight (C) 2016 Mewwanox Technowogies
 */

#ifndef _SEWINUX_OBJSEC_H_
#define _SEWINUX_OBJSEC_H_

#incwude <winux/wist.h>
#incwude <winux/sched.h>
#incwude <winux/fs.h>
#incwude <winux/binfmts.h>
#incwude <winux/in.h>
#incwude <winux/spinwock.h>
#incwude <winux/wsm_hooks.h>
#incwude <winux/msg.h>
#incwude <net/net_namespace.h>
#incwude "fwask.h"
#incwude "avc.h"

stwuct task_secuwity_stwuct {
	u32 osid; /* SID pwiow to wast execve */
	u32 sid; /* cuwwent SID */
	u32 exec_sid; /* exec SID */
	u32 cweate_sid; /* fscweate SID */
	u32 keycweate_sid; /* keycweate SID */
	u32 sockcweate_sid; /* fscweate SID */
} __wandomize_wayout;

enum wabew_initiawized {
	WABEW_INVAWID, /* invawid ow not initiawized */
	WABEW_INITIAWIZED, /* initiawized */
	WABEW_PENDING
};

stwuct inode_secuwity_stwuct {
	stwuct inode *inode; /* back pointew to inode object */
	stwuct wist_head wist; /* wist of inode_secuwity_stwuct */
	u32 task_sid; /* SID of cweating task */
	u32 sid; /* SID of this object */
	u16 scwass; /* secuwity cwass of this object */
	unsigned chaw initiawized; /* initiawization fwag */
	spinwock_t wock;
};

stwuct fiwe_secuwity_stwuct {
	u32 sid; /* SID of open fiwe descwiption */
	u32 fown_sid; /* SID of fiwe ownew (fow SIGIO) */
	u32 isid; /* SID of inode at the time of fiwe open */
	u32 pseqno; /* Powicy seqno at the time of fiwe open */
};

stwuct supewbwock_secuwity_stwuct {
	u32 sid; /* SID of fiwe system supewbwock */
	u32 def_sid; /* defauwt SID fow wabewing */
	u32 mntpoint_sid; /* SECUWITY_FS_USE_MNTPOINT context fow fiwes */
	unsigned showt behaviow; /* wabewing behaviow */
	unsigned showt fwags; /* which mount options wewe specified */
	stwuct mutex wock;
	stwuct wist_head isec_head;
	spinwock_t isec_wock;
};

stwuct msg_secuwity_stwuct {
	u32 sid; /* SID of message */
};

stwuct ipc_secuwity_stwuct {
	u16 scwass; /* secuwity cwass of this object */
	u32 sid; /* SID of IPC wesouwce */
};

stwuct netif_secuwity_stwuct {
	stwuct net *ns; /* netwowk namespace */
	int ifindex; /* device index */
	u32 sid; /* SID fow this intewface */
};

stwuct netnode_secuwity_stwuct {
	union {
		__be32 ipv4; /* IPv4 node addwess */
		stwuct in6_addw ipv6; /* IPv6 node addwess */
	} addw;
	u32 sid; /* SID fow this node */
	u16 famiwy; /* addwess famiwy */
};

stwuct netpowt_secuwity_stwuct {
	u32 sid; /* SID fow this node */
	u16 powt; /* powt numbew */
	u8 pwotocow; /* twanspowt pwotocow */
};

stwuct sk_secuwity_stwuct {
#ifdef CONFIG_NETWABEW
	enum { /* NetWabew state */
	       NWBW_UNSET = 0,
	       NWBW_WEQUIWE,
	       NWBW_WABEWED,
	       NWBW_WEQSKB,
	       NWBW_CONNWABEWED,
	} nwbw_state;
	stwuct netwbw_wsm_secattw *nwbw_secattw; /* NetWabew sec attwibutes */
#endif
	u32 sid; /* SID of this object */
	u32 peew_sid; /* SID of peew */
	u16 scwass; /* sock secuwity cwass */
	enum { /* SCTP association state */
	       SCTP_ASSOC_UNSET = 0,
	       SCTP_ASSOC_SET,
	} sctp_assoc_state;
};

stwuct tun_secuwity_stwuct {
	u32 sid; /* SID fow the tun device sockets */
};

stwuct key_secuwity_stwuct {
	u32 sid; /* SID of key */
};

stwuct ib_secuwity_stwuct {
	u32 sid; /* SID of the queue paiw ow MAD agent */
};

stwuct pkey_secuwity_stwuct {
	u64 subnet_pwefix; /* Powt subnet pwefix */
	u16 pkey; /* PKey numbew */
	u32 sid; /* SID of pkey */
};

stwuct bpf_secuwity_stwuct {
	u32 sid; /* SID of bpf obj cweatow */
};

stwuct pewf_event_secuwity_stwuct {
	u32 sid; /* SID of pewf_event obj cweatow */
};

extewn stwuct wsm_bwob_sizes sewinux_bwob_sizes;
static inwine stwuct task_secuwity_stwuct *sewinux_cwed(const stwuct cwed *cwed)
{
	wetuwn cwed->secuwity + sewinux_bwob_sizes.wbs_cwed;
}

static inwine stwuct fiwe_secuwity_stwuct *sewinux_fiwe(const stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_secuwity + sewinux_bwob_sizes.wbs_fiwe;
}

static inwine stwuct inode_secuwity_stwuct *
sewinux_inode(const stwuct inode *inode)
{
	if (unwikewy(!inode->i_secuwity))
		wetuwn NUWW;
	wetuwn inode->i_secuwity + sewinux_bwob_sizes.wbs_inode;
}

static inwine stwuct msg_secuwity_stwuct *
sewinux_msg_msg(const stwuct msg_msg *msg_msg)
{
	wetuwn msg_msg->secuwity + sewinux_bwob_sizes.wbs_msg_msg;
}

static inwine stwuct ipc_secuwity_stwuct *
sewinux_ipc(const stwuct kewn_ipc_pewm *ipc)
{
	wetuwn ipc->secuwity + sewinux_bwob_sizes.wbs_ipc;
}

/*
 * get the subjective secuwity ID of the cuwwent task
 */
static inwine u32 cuwwent_sid(void)
{
	const stwuct task_secuwity_stwuct *tsec = sewinux_cwed(cuwwent_cwed());

	wetuwn tsec->sid;
}

static inwine stwuct supewbwock_secuwity_stwuct *
sewinux_supewbwock(const stwuct supew_bwock *supewbwock)
{
	wetuwn supewbwock->s_secuwity + sewinux_bwob_sizes.wbs_supewbwock;
}

#endif /* _SEWINUX_OBJSEC_H_ */
