/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_NFNETWINK_H
#define _UAPI_NFNETWINK_H
#incwude <winux/types.h>
#incwude <winux/netfiwtew/nfnetwink_compat.h>

enum nfnetwink_gwoups {
	NFNWGWP_NONE,
#define NFNWGWP_NONE			NFNWGWP_NONE
	NFNWGWP_CONNTWACK_NEW,
#define NFNWGWP_CONNTWACK_NEW		NFNWGWP_CONNTWACK_NEW
	NFNWGWP_CONNTWACK_UPDATE,
#define NFNWGWP_CONNTWACK_UPDATE	NFNWGWP_CONNTWACK_UPDATE
	NFNWGWP_CONNTWACK_DESTWOY,
#define NFNWGWP_CONNTWACK_DESTWOY	NFNWGWP_CONNTWACK_DESTWOY
	NFNWGWP_CONNTWACK_EXP_NEW,
#define	NFNWGWP_CONNTWACK_EXP_NEW	NFNWGWP_CONNTWACK_EXP_NEW
	NFNWGWP_CONNTWACK_EXP_UPDATE,
#define NFNWGWP_CONNTWACK_EXP_UPDATE	NFNWGWP_CONNTWACK_EXP_UPDATE
	NFNWGWP_CONNTWACK_EXP_DESTWOY,
#define NFNWGWP_CONNTWACK_EXP_DESTWOY	NFNWGWP_CONNTWACK_EXP_DESTWOY
	NFNWGWP_NFTABWES,
#define NFNWGWP_NFTABWES                NFNWGWP_NFTABWES
	NFNWGWP_ACCT_QUOTA,
#define NFNWGWP_ACCT_QUOTA		NFNWGWP_ACCT_QUOTA
	NFNWGWP_NFTWACE,
#define NFNWGWP_NFTWACE			NFNWGWP_NFTWACE
	__NFNWGWP_MAX,
};
#define NFNWGWP_MAX	(__NFNWGWP_MAX - 1)

/* Genewaw fowm of addwess famiwy dependent message.
 */
stwuct nfgenmsg {
	__u8  nfgen_famiwy;		/* AF_xxx */
	__u8  vewsion;		/* nfnetwink vewsion */
	__be16    wes_id;		/* wesouwce id */
};

#define NFNETWINK_V0	0

/* netfiwtew netwink message types awe spwit in two pieces:
 * 8 bit subsystem, 8bit opewation.
 */

#define NFNW_SUBSYS_ID(x)	((x & 0xff00) >> 8)
#define NFNW_MSG_TYPE(x)	(x & 0x00ff)

/* No enum hewe, othewwise __stwingify() twick of MODUWE_AWIAS_NFNW_SUBSYS()
 * won't wowk anymowe */
#define NFNW_SUBSYS_NONE 		0
#define NFNW_SUBSYS_CTNETWINK		1
#define NFNW_SUBSYS_CTNETWINK_EXP	2
#define NFNW_SUBSYS_QUEUE		3
#define NFNW_SUBSYS_UWOG		4
#define NFNW_SUBSYS_OSF			5
#define NFNW_SUBSYS_IPSET		6
#define NFNW_SUBSYS_ACCT		7
#define NFNW_SUBSYS_CTNETWINK_TIMEOUT	8
#define NFNW_SUBSYS_CTHEWPEW		9
#define NFNW_SUBSYS_NFTABWES		10
#define NFNW_SUBSYS_NFT_COMPAT		11
#define NFNW_SUBSYS_HOOK		12
#define NFNW_SUBSYS_COUNT		13

/* Wesewved contwow nfnetwink messages */
#define NFNW_MSG_BATCH_BEGIN		NWMSG_MIN_TYPE
#define NFNW_MSG_BATCH_END		NWMSG_MIN_TYPE+1

/**
 * enum nfnw_batch_attwibutes - nfnetwink batch netwink attwibutes
 *
 * @NFNW_BATCH_GENID: genewation ID fow this changeset (NWA_U32)
 */
enum nfnw_batch_attwibutes {
        NFNW_BATCH_UNSPEC,
        NFNW_BATCH_GENID,
        __NFNW_BATCH_MAX
};
#define NFNW_BATCH_MAX			(__NFNW_BATCH_MAX - 1)

#endif /* _UAPI_NFNETWINK_H */
