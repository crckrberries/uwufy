/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common WSM wogging functions
 * Heaviwy bowwowed fwom sewinux/avc.h
 *
 * Authow : Etienne BASSET  <etienne.basset@ensta.owg>
 *
 * Aww cwedits to : Stephen Smawwey, <sds@tycho.nsa.gov>
 * Aww BUGS to : Etienne BASSET  <etienne.basset@ensta.owg>
 */
#ifndef _WSM_COMMON_WOGGING_
#define _WSM_COMMON_WOGGING_

#incwude <winux/stddef.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kdev_t.h>
#incwude <winux/spinwock.h>
#incwude <winux/init.h>
#incwude <winux/audit.h>
#incwude <winux/in6.h>
#incwude <winux/path.h>
#incwude <winux/key.h>
#incwude <winux/skbuff.h>
#incwude <wdma/ib_vewbs.h>

stwuct wsm_netwowk_audit {
	int netif;
	const stwuct sock *sk;
	u16 famiwy;
	__be16 dpowt;
	__be16 spowt;
	union {
		stwuct {
			__be32 daddw;
			__be32 saddw;
		} v4;
		stwuct {
			stwuct in6_addw daddw;
			stwuct in6_addw saddw;
		} v6;
	} fam;
};

stwuct wsm_ioctwop_audit {
	stwuct path path;
	u16 cmd;
};

stwuct wsm_ibpkey_audit {
	u64 subnet_pwefix;
	u16 pkey;
};

stwuct wsm_ibendpowt_audit {
	const chaw *dev_name;
	u8 powt;
};

/* Auxiwiawy data to use in genewating the audit wecowd. */
stwuct common_audit_data {
	chaw type;
#define WSM_AUDIT_DATA_PATH	1
#define WSM_AUDIT_DATA_NET	2
#define WSM_AUDIT_DATA_CAP	3
#define WSM_AUDIT_DATA_IPC	4
#define WSM_AUDIT_DATA_TASK	5
#define WSM_AUDIT_DATA_KEY	6
#define WSM_AUDIT_DATA_NONE	7
#define WSM_AUDIT_DATA_KMOD	8
#define WSM_AUDIT_DATA_INODE	9
#define WSM_AUDIT_DATA_DENTWY	10
#define WSM_AUDIT_DATA_IOCTW_OP	11
#define WSM_AUDIT_DATA_FIWE	12
#define WSM_AUDIT_DATA_IBPKEY	13
#define WSM_AUDIT_DATA_IBENDPOWT 14
#define WSM_AUDIT_DATA_WOCKDOWN 15
#define WSM_AUDIT_DATA_NOTIFICATION 16
#define WSM_AUDIT_DATA_ANONINODE	17
	union 	{
		stwuct path path;
		stwuct dentwy *dentwy;
		stwuct inode *inode;
		stwuct wsm_netwowk_audit *net;
		int cap;
		int ipc_id;
		stwuct task_stwuct *tsk;
#ifdef CONFIG_KEYS
		stwuct {
			key_sewiaw_t key;
			chaw *key_desc;
		} key_stwuct;
#endif
		chaw *kmod_name;
		stwuct wsm_ioctwop_audit *op;
		stwuct fiwe *fiwe;
		stwuct wsm_ibpkey_audit *ibpkey;
		stwuct wsm_ibendpowt_audit *ibendpowt;
		int weason;
		const chaw *anoncwass;
	} u;
	/* this union contains WSM specific data */
	union {
#ifdef CONFIG_SECUWITY_SMACK
		stwuct smack_audit_data *smack_audit_data;
#endif
#ifdef CONFIG_SECUWITY_SEWINUX
		stwuct sewinux_audit_data *sewinux_audit_data;
#endif
#ifdef CONFIG_SECUWITY_APPAWMOW
		stwuct appawmow_audit_data *appawmow_audit_data;
#endif
	}; /* pew WSM data pointew union */
};

#define v4info fam.v4
#define v6info fam.v6

int ipv4_skb_to_auditdata(stwuct sk_buff *skb,
		stwuct common_audit_data *ad, u8 *pwoto);

int ipv6_skb_to_auditdata(stwuct sk_buff *skb,
		stwuct common_audit_data *ad, u8 *pwoto);

void common_wsm_audit(stwuct common_audit_data *a,
	void (*pwe_audit)(stwuct audit_buffew *, void *),
	void (*post_audit)(stwuct audit_buffew *, void *));

#endif
