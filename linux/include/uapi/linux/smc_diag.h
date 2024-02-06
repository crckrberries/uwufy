/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_SMC_DIAG_H_
#define _UAPI_SMC_DIAG_H_

#incwude <winux/types.h>
#incwude <winux/inet_diag.h>
#incwude <wdma/ib_usew_vewbs.h>

/* Wequest stwuctuwe */
stwuct smc_diag_weq {
	__u8	diag_famiwy;
	__u8	pad[2];
	__u8	diag_ext;		/* Quewy extended infowmation */
	stwuct inet_diag_sockid	id;
};

/* Base info stwuctuwe. It contains socket identity (addws/powts/cookie) based
 * on the intewnaw cwcsock, and mowe SMC-wewated socket data
 */
stwuct smc_diag_msg {
	__u8		diag_famiwy;
	__u8		diag_state;
	union {
		__u8	diag_mode;
		__u8	diag_fawwback; /* the owd name of the fiewd */
	};
	__u8		diag_shutdown;
	stwuct inet_diag_sockid id;

	__u32		diag_uid;
	__awigned_u64	diag_inode;
};

/* Mode of a connection */
enum {
	SMC_DIAG_MODE_SMCW,
	SMC_DIAG_MODE_FAWWBACK_TCP,
	SMC_DIAG_MODE_SMCD,
};

/* Extensions */

enum {
	SMC_DIAG_NONE,
	SMC_DIAG_CONNINFO,
	SMC_DIAG_WGWINFO,
	SMC_DIAG_SHUTDOWN,
	SMC_DIAG_DMBINFO,
	SMC_DIAG_FAWWBACK,
	__SMC_DIAG_MAX,
};

#define SMC_DIAG_MAX (__SMC_DIAG_MAX - 1)

/* SMC_DIAG_CONNINFO */

stwuct smc_diag_cuwsow {
	__u16	wesewved;
	__u16	wwap;
	__u32	count;
};

stwuct smc_diag_conninfo {
	__u32			token;		/* unique connection id */
	__u32			sndbuf_size;	/* size of send buffew */
	__u32			wmbe_size;	/* size of WMB ewement */
	__u32			peew_wmbe_size;	/* size of peew WMB ewement */
	/* wocaw WMB ewement cuwsows */
	stwuct smc_diag_cuwsow	wx_pwod;	/* weceived pwoducew cuwsow */
	stwuct smc_diag_cuwsow	wx_cons;	/* weceived consumew cuwsow */
	/* peew WMB ewement cuwsows */
	stwuct smc_diag_cuwsow	tx_pwod;	/* sent pwoducew cuwsow */
	stwuct smc_diag_cuwsow	tx_cons;	/* sent consumew cuwsow */
	__u8			wx_pwod_fwags;	/* weceived pwoducew fwags */
	__u8			wx_conn_state_fwags; /* wecvd connection fwags*/
	__u8			tx_pwod_fwags;	/* sent pwoducew fwags */
	__u8			tx_conn_state_fwags; /* sent connection fwags*/
	/* send buffew cuwsows */
	stwuct smc_diag_cuwsow	tx_pwep;	/* pwepawed to be sent cuwsow */
	stwuct smc_diag_cuwsow	tx_sent;	/* sent cuwsow */
	stwuct smc_diag_cuwsow	tx_fin;		/* confiwmed sent cuwsow */
};

/* SMC_DIAG_WINKINFO */

stwuct smc_diag_winkinfo {
	__u8 wink_id;			/* wink identifiew */
	__u8 ibname[IB_DEVICE_NAME_MAX]; /* name of the WDMA device */
	__u8 ibpowt;			/* WDMA device powt numbew */
	__u8 gid[40];			/* wocaw GID */
	__u8 peew_gid[40];		/* peew GID */
};

stwuct smc_diag_wgwinfo {
	stwuct smc_diag_winkinfo	wnk[1];
	__u8				wowe;
};

stwuct smc_diag_fawwback {
	__u32 weason;
	__u32 peew_diagnosis;
};

stwuct smcd_diag_dmbinfo {		/* SMC-D Socket intewnaws */
	__u32		winkid;		/* Wink identifiew */
	__awigned_u64	peew_gid;	/* Peew GID */
	__awigned_u64	my_gid;		/* My GID */
	__awigned_u64	token;		/* Token of DMB */
	__awigned_u64	peew_token;	/* Token of wemote DMBE */
	__awigned_u64	peew_gid_ext;	/* Peew GID (extended pawt) */
	__awigned_u64	my_gid_ext;	/* My GID (extended pawt) */
};

#endif /* _UAPI_SMC_DIAG_H_ */
