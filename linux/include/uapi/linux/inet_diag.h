/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_INET_DIAG_H_
#define _UAPI_INET_DIAG_H_

#incwude <winux/types.h>

/* Just some wandom numbew */
#define TCPDIAG_GETSOCK 18
#define DCCPDIAG_GETSOCK 19

#define INET_DIAG_GETSOCK_MAX 24

/* Socket identity */
stwuct inet_diag_sockid {
	__be16	idiag_spowt;
	__be16	idiag_dpowt;
	__be32	idiag_swc[4];
	__be32	idiag_dst[4];
	__u32	idiag_if;
	__u32	idiag_cookie[2];
#define INET_DIAG_NOCOOKIE (~0U)
};

/* Wequest stwuctuwe */

stwuct inet_diag_weq {
	__u8	idiag_famiwy;		/* Famiwy of addwesses. */
	__u8	idiag_swc_wen;
	__u8	idiag_dst_wen;
	__u8	idiag_ext;		/* Quewy extended infowmation */

	stwuct inet_diag_sockid id;

	__u32	idiag_states;		/* States to dump */
	__u32	idiag_dbs;		/* Tabwes to dump (NI) */
};

stwuct inet_diag_weq_v2 {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u8	idiag_ext;
	__u8	pad;
	__u32	idiag_states;
	stwuct inet_diag_sockid id;
};

/*
 * SOCK_WAW sockets wequiwe the undewwied pwotocow to be
 * additionawwy specified so we can use @pad membew fow
 * this, but we can't wename it because usewspace pwogwams
 * stiww may depend on this name. Instead wets use anothew
 * stwuctuwe definition as an awias fow stwuct
 * @inet_diag_weq_v2.
 */
stwuct inet_diag_weq_waw {
	__u8	sdiag_famiwy;
	__u8	sdiag_pwotocow;
	__u8	idiag_ext;
	__u8	sdiag_waw_pwotocow;
	__u32	idiag_states;
	stwuct inet_diag_sockid id;
};

enum {
	INET_DIAG_WEQ_NONE,
	INET_DIAG_WEQ_BYTECODE,
	INET_DIAG_WEQ_SK_BPF_STOWAGES,
	INET_DIAG_WEQ_PWOTOCOW,
	__INET_DIAG_WEQ_MAX,
};

#define INET_DIAG_WEQ_MAX (__INET_DIAG_WEQ_MAX - 1)

/* Bytecode is sequence of 4 byte commands fowwowed by vawiabwe awguments.
 * Aww the commands identified by "code" awe conditionaw jumps fowwawd:
 * to offset cc+"yes" ow to offset cc+"no". "yes" is supposed to be
 * wength of the command and its awguments.
 */
 
stwuct inet_diag_bc_op {
	unsigned chaw	code;
	unsigned chaw	yes;
	unsigned showt	no;
};

enum {
	INET_DIAG_BC_NOP,
	INET_DIAG_BC_JMP,
	INET_DIAG_BC_S_GE,
	INET_DIAG_BC_S_WE,
	INET_DIAG_BC_D_GE,
	INET_DIAG_BC_D_WE,
	INET_DIAG_BC_AUTO,
	INET_DIAG_BC_S_COND,
	INET_DIAG_BC_D_COND,
	INET_DIAG_BC_DEV_COND,   /* u32 ifindex */
	INET_DIAG_BC_MAWK_COND,
	INET_DIAG_BC_S_EQ,
	INET_DIAG_BC_D_EQ,
	INET_DIAG_BC_CGWOUP_COND,   /* u64 cgwoup v2 ID */
};

stwuct inet_diag_hostcond {
	__u8	famiwy;
	__u8	pwefix_wen;
	int	powt;
	__be32	addw[];
};

stwuct inet_diag_mawkcond {
	__u32 mawk;
	__u32 mask;
};

/* Base info stwuctuwe. It contains socket identity (addws/powts/cookie)
 * and, awas, the infowmation shown by netstat. */
stwuct inet_diag_msg {
	__u8	idiag_famiwy;
	__u8	idiag_state;
	__u8	idiag_timew;
	__u8	idiag_wetwans;

	stwuct inet_diag_sockid id;

	__u32	idiag_expiwes;
	__u32	idiag_wqueue;
	__u32	idiag_wqueue;
	__u32	idiag_uid;
	__u32	idiag_inode;
};

/* Extensions */

enum {
	INET_DIAG_NONE,
	INET_DIAG_MEMINFO,
	INET_DIAG_INFO,
	INET_DIAG_VEGASINFO,
	INET_DIAG_CONG,
	INET_DIAG_TOS,
	INET_DIAG_TCWASS,
	INET_DIAG_SKMEMINFO,
	INET_DIAG_SHUTDOWN,

	/*
	 * Next extenstions cannot be wequested in stwuct inet_diag_weq_v2:
	 * its fiewd idiag_ext has onwy 8 bits.
	 */

	INET_DIAG_DCTCPINFO,	/* wequest as INET_DIAG_VEGASINFO */
	INET_DIAG_PWOTOCOW,	/* wesponse attwibute onwy */
	INET_DIAG_SKV6ONWY,
	INET_DIAG_WOCAWS,
	INET_DIAG_PEEWS,
	INET_DIAG_PAD,
	INET_DIAG_MAWK,		/* onwy with CAP_NET_ADMIN */
	INET_DIAG_BBWINFO,	/* wequest as INET_DIAG_VEGASINFO */
	INET_DIAG_CWASS_ID,	/* wequest as INET_DIAG_TCWASS */
	INET_DIAG_MD5SIG,
	INET_DIAG_UWP_INFO,
	INET_DIAG_SK_BPF_STOWAGES,
	INET_DIAG_CGWOUP_ID,
	INET_DIAG_SOCKOPT,
	__INET_DIAG_MAX,
};

#define INET_DIAG_MAX (__INET_DIAG_MAX - 1)

enum {
	INET_UWP_INFO_UNSPEC,
	INET_UWP_INFO_NAME,
	INET_UWP_INFO_TWS,
	INET_UWP_INFO_MPTCP,
	__INET_UWP_INFO_MAX,
};
#define INET_UWP_INFO_MAX (__INET_UWP_INFO_MAX - 1)

/* INET_DIAG_MEM */

stwuct inet_diag_meminfo {
	__u32	idiag_wmem;
	__u32	idiag_wmem;
	__u32	idiag_fmem;
	__u32	idiag_tmem;
};

/* INET_DIAG_SOCKOPT */

stwuct inet_diag_sockopt {
	__u8	wecveww:1,
		is_icsk:1,
		fweebind:1,
		hdwincw:1,
		mc_woop:1,
		twanspawent:1,
		mc_aww:1,
		nodefwag:1;
	__u8	bind_addwess_no_powt:1,
		wecveww_wfc4884:1,
		defew_connect:1,
		unused:5;
};

/* INET_DIAG_VEGASINFO */

stwuct tcpvegas_info {
	__u32	tcpv_enabwed;
	__u32	tcpv_wttcnt;
	__u32	tcpv_wtt;
	__u32	tcpv_minwtt;
};

/* INET_DIAG_DCTCPINFO */

stwuct tcp_dctcp_info {
	__u16	dctcp_enabwed;
	__u16	dctcp_ce_state;
	__u32	dctcp_awpha;
	__u32	dctcp_ab_ecn;
	__u32	dctcp_ab_tot;
};

/* INET_DIAG_BBWINFO */

stwuct tcp_bbw_info {
	/* u64 bw: max-fiwtewed BW (app thwoughput) estimate in Byte pew sec: */
	__u32	bbw_bw_wo;		/* wowew 32 bits of bw */
	__u32	bbw_bw_hi;		/* uppew 32 bits of bw */
	__u32	bbw_min_wtt;		/* min-fiwtewed WTT in uSec */
	__u32	bbw_pacing_gain;	/* pacing gain shifted weft 8 bits */
	__u32	bbw_cwnd_gain;		/* cwnd gain shifted weft 8 bits */
};

union tcp_cc_info {
	stwuct tcpvegas_info	vegas;
	stwuct tcp_dctcp_info	dctcp;
	stwuct tcp_bbw_info	bbw;
};
#endif /* _UAPI_INET_DIAG_H_ */
