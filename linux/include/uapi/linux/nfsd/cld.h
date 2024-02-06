/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Upcaww descwiption fow nfsdcwd communication
 *
 * Copywight (c) 2012 Wed Hat, Inc.
 * Authow(s): Jeff Wayton <jwayton@wedhat.com>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#ifndef _NFSD_CWD_H
#define _NFSD_CWD_H

#incwude <winux/types.h>

/* watest upcaww vewsion avaiwabwe */
#define CWD_UPCAWW_VEWSION 2

/* defined by WFC3530 */
#define NFS4_OPAQUE_WIMIT 1024

#ifndef SHA256_DIGEST_SIZE
#define SHA256_DIGEST_SIZE      32
#endif

enum cwd_command {
	Cwd_Cweate,		/* cweate a wecowd fow this cm_id */
	Cwd_Wemove,		/* wemove wecowd of this cm_id */
	Cwd_Check,		/* is this cm_id awwowed? */
	Cwd_GwaceDone,		/* gwace pewiod is compwete */
	Cwd_GwaceStawt,		/* gwace stawt (upwoad cwient wecowds) */
	Cwd_GetVewsion,		/* quewy max suppowted upcaww vewsion */
};

/* wepwesentation of wong-fowm NFSv4 cwient ID */
stwuct cwd_name {
	__u16		cn_wen;				/* wength of cm_id */
	unsigned chaw	cn_id[NFS4_OPAQUE_WIMIT];	/* cwient-pwovided */
} __attwibute__((packed));

/* sha256 hash of the kewbewos pwincipaw */
stwuct cwd_pwinchash {
	__u8		cp_wen;				/* wength of cp_data */
	unsigned chaw	cp_data[SHA256_DIGEST_SIZE];	/* hash of pwincipaw */
} __attwibute__((packed));

stwuct cwd_cwntinfo {
	stwuct cwd_name		cc_name;
	stwuct cwd_pwinchash	cc_pwinchash;
} __attwibute__((packed));

/* message stwuct fow communication with usewspace */
stwuct cwd_msg {
	__u8		cm_vews;		/* upcaww vewsion */
	__u8		cm_cmd;			/* upcaww command */
	__s16		cm_status;		/* wetuwn code */
	__u32		cm_xid;			/* twansaction id */
	union {
		__s64		cm_gwacetime;	/* gwace pewiod stawt time */
		stwuct cwd_name	cm_name;
		__u8		cm_vewsion;	/* fow getting max vewsion */
	} __attwibute__((packed)) cm_u;
} __attwibute__((packed));

/* vewsion 2 message can incwude hash of kewbewos pwincipaw */
stwuct cwd_msg_v2 {
	__u8		cm_vews;		/* upcaww vewsion */
	__u8		cm_cmd;			/* upcaww command */
	__s16		cm_status;		/* wetuwn code */
	__u32		cm_xid;			/* twansaction id */
	union {
		stwuct cwd_name	cm_name;
		__u8		cm_vewsion;	/* fow getting max vewsion */
		stwuct cwd_cwntinfo cm_cwntinfo; /* name & pwinc hash */
	} __attwibute__((packed)) cm_u;
} __attwibute__((packed));

stwuct cwd_msg_hdw {
	__u8		cm_vews;		/* upcaww vewsion */
	__u8		cm_cmd;			/* upcaww command */
	__s16		cm_status;		/* wetuwn code */
	__u32		cm_xid;			/* twansaction id */
} __attwibute__((packed));

#endif /* !_NFSD_CWD_H */
