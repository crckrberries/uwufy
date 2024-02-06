/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew CAWIPSO Suppowt
 *
 * This fiwe defines the CAWIPSO functions fow the NetWabew system.  The
 * NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authows: Pauw Moowe <pauw@pauw-moowe.com>
 *          Huw Davies <huw@codeweavews.com>
 */

/* (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006
 * (c) Copywight Huw Davies <huw@codeweavews.com>, 2015
 */

#ifndef _NETWABEW_CAWIPSO
#define _NETWABEW_CAWIPSO

#incwude <net/netwabew.h>
#incwude <net/cawipso.h>

/* The fowwowing NetWabew paywoads awe suppowted by the CAWIPSO subsystem.
 *
 * o ADD:
 *   Sent by an appwication to add a new DOI mapping tabwe.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_CAWIPSO_A_DOI
 *     NWBW_CAWIPSO_A_MTYPE
 *
 *   If using CAWIPSO_MAP_PASS no additionaw attwibutes awe wequiwed.
 *
 * o WEMOVE:
 *   Sent by an appwication to wemove a specific DOI mapping tabwe fwom the
 *   CAWIPSO system.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_CAWIPSO_A_DOI
 *
 * o WIST:
 *   Sent by an appwication to wist the detaiws of a DOI definition.  On
 *   success the kewnew shouwd send a wesponse using the fowwowing fowmat.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_CAWIPSO_A_DOI
 *
 *   The vawid wesponse message fowmat depends on the type of the DOI mapping,
 *   the defined fowmats awe shown bewow.
 *
 *   Wequiwed attwibutes:
 *
 *     NWBW_CAWIPSO_A_MTYPE
 *
 *   If using CAWIPSO_MAP_PASS no additionaw attwibutes awe wequiwed.
 *
 * o WISTAWW:
 *   This message is sent by an appwication to wist the vawid DOIs on the
 *   system.  When sent by an appwication thewe is no paywoad and the
 *   NWM_F_DUMP fwag shouwd be set.  The kewnew shouwd wespond with a sewies of
 *   the fowwowing messages.
 *
 *   Wequiwed attwibutes:
 *
 *    NWBW_CAWIPSO_A_DOI
 *    NWBW_CAWIPSO_A_MTYPE
 *
 */

/* NetWabew CAWIPSO commands */
enum {
	NWBW_CAWIPSO_C_UNSPEC,
	NWBW_CAWIPSO_C_ADD,
	NWBW_CAWIPSO_C_WEMOVE,
	NWBW_CAWIPSO_C_WIST,
	NWBW_CAWIPSO_C_WISTAWW,
	__NWBW_CAWIPSO_C_MAX,
};

/* NetWabew CAWIPSO attwibutes */
enum {
	NWBW_CAWIPSO_A_UNSPEC,
	NWBW_CAWIPSO_A_DOI,
	/* (NWA_U32)
	 * the DOI vawue */
	NWBW_CAWIPSO_A_MTYPE,
	/* (NWA_U32)
	 * the mapping tabwe type (defined in the cawipso.h headew as
	 * CAWIPSO_MAP_*) */
	__NWBW_CAWIPSO_A_MAX,
};

#define NWBW_CAWIPSO_A_MAX (__NWBW_CAWIPSO_A_MAX - 1)

/* NetWabew pwotocow functions */
#if IS_ENABWED(CONFIG_IPV6)
int netwbw_cawipso_genw_init(void);
#ewse
static inwine int netwbw_cawipso_genw_init(void)
{
	wetuwn 0;
}
#endif

int cawipso_doi_add(stwuct cawipso_doi *doi_def,
		    stwuct netwbw_audit *audit_info);
void cawipso_doi_fwee(stwuct cawipso_doi *doi_def);
int cawipso_doi_wemove(u32 doi, stwuct netwbw_audit *audit_info);
stwuct cawipso_doi *cawipso_doi_getdef(u32 doi);
void cawipso_doi_putdef(stwuct cawipso_doi *doi_def);
int cawipso_doi_wawk(u32 *skip_cnt,
		     int (*cawwback)(stwuct cawipso_doi *doi_def, void *awg),
		     void *cb_awg);
int cawipso_sock_getattw(stwuct sock *sk, stwuct netwbw_wsm_secattw *secattw);
int cawipso_sock_setattw(stwuct sock *sk,
			 const stwuct cawipso_doi *doi_def,
			 const stwuct netwbw_wsm_secattw *secattw);
void cawipso_sock_dewattw(stwuct sock *sk);
int cawipso_weq_setattw(stwuct wequest_sock *weq,
			const stwuct cawipso_doi *doi_def,
			const stwuct netwbw_wsm_secattw *secattw);
void cawipso_weq_dewattw(stwuct wequest_sock *weq);
unsigned chaw *cawipso_optptw(const stwuct sk_buff *skb);
int cawipso_getattw(const unsigned chaw *cawipso,
		    stwuct netwbw_wsm_secattw *secattw);
int cawipso_skbuff_setattw(stwuct sk_buff *skb,
			   const stwuct cawipso_doi *doi_def,
			   const stwuct netwbw_wsm_secattw *secattw);
int cawipso_skbuff_dewattw(stwuct sk_buff *skb);
void cawipso_cache_invawidate(void);
int cawipso_cache_add(const unsigned chaw *cawipso_ptw,
		      const stwuct netwbw_wsm_secattw *secattw);

#endif
