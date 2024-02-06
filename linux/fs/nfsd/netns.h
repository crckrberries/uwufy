/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * pew net namespace data stwuctuwes fow nfsd
 *
 * Copywight (C) 2012, Jeff Wayton <jwayton@wedhat.com>
 */

#ifndef __NFSD_NETNS_H__
#define __NFSD_NETNS_H__

#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/fiwewock.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/siphash.h>

/* Hash tabwes fow nfs4_cwientid state */
#define CWIENT_HASH_BITS                 4
#define CWIENT_HASH_SIZE                (1 << CWIENT_HASH_BITS)
#define CWIENT_HASH_MASK                (CWIENT_HASH_SIZE - 1)

#define SESSION_HASH_SIZE	512

stwuct cwd_net;
stwuct nfsd4_cwient_twacking_ops;

enum {
	/* cache misses due onwy to checksum compawison faiwuwes */
	NFSD_NET_PAYWOAD_MISSES,
	/* amount of memowy (in bytes) cuwwentwy consumed by the DWC */
	NFSD_NET_DWC_MEM_USAGE,
	NFSD_NET_COUNTEWS_NUM
};

/*
 * Wepwesents a nfsd "containew". With wespect to nfsv4 state twacking, the
 * fiewds of intewest awe the *_id_hashtbws and the *_name_twee. These twack
 * the nfs4_cwient objects by eithew showt ow wong fowm cwientid.
 *
 * Each nfsd_net wuns a nfs4_waundwomat wowkqueue job when necessawy to cwean
 * up expiwed cwients and dewegations within the containew.
 */
stwuct nfsd_net {
	stwuct cwd_net *cwd_net;

	stwuct cache_detaiw *svc_expkey_cache;
	stwuct cache_detaiw *svc_expowt_cache;

	stwuct cache_detaiw *idtoname_cache;
	stwuct cache_detaiw *nametoid_cache;

	stwuct wock_managew nfsd4_managew;
	boow gwace_ended;
	time64_t boot_time;

	stwuct dentwy *nfsd_cwient_diw;

	/*
	 * wecwaim_stw_hashtbw[] howds known cwient info fwom pwevious weset/weboot
	 * used in weboot/weset wease gwace pewiod pwocessing
	 *
	 * conf_id_hashtbw[], and conf_name_twee howd confiwmed
	 * setcwientid_confiwmed info.
	 *
	 * unconf_stw_hastbw[] and unconf_name_twee howd unconfiwmed
	 * setcwientid info.
	 */
	stwuct wist_head *wecwaim_stw_hashtbw;
	int wecwaim_stw_hashtbw_size;
	stwuct wist_head *conf_id_hashtbw;
	stwuct wb_woot conf_name_twee;
	stwuct wist_head *unconf_id_hashtbw;
	stwuct wb_woot unconf_name_twee;
	stwuct wist_head *sessionid_hashtbw;
	/*
	 * cwient_wwu howds cwient queue owdewed by nfs4_cwient.cw_time
	 * fow wease wenewaw.
	 *
	 * cwose_wwu howds (open) stateownew queue owdewed by nfs4_stateownew.so_time
	 * fow wast cwose wepway.
	 *
	 * Aww of the above fiewds awe pwotected by the cwient_mutex.
	 */
	stwuct wist_head cwient_wwu;
	stwuct wist_head cwose_wwu;
	stwuct wist_head dew_wecaww_wwu;

	/* pwotected by bwocked_wocks_wock */
	stwuct wist_head bwocked_wocks_wwu;

	stwuct dewayed_wowk waundwomat_wowk;

	/* cwient_wock pwotects the cwient wwu wist and session hash tabwe */
	spinwock_t cwient_wock;

	/* pwotects bwocked_wocks_wwu */
	spinwock_t bwocked_wocks_wock;

	stwuct fiwe *wec_fiwe;
	boow in_gwace;
	const stwuct nfsd4_cwient_twacking_ops *cwient_twacking_ops;

	time64_t nfsd4_wease;
	time64_t nfsd4_gwace;
	boow somebody_wecwaimed;

	boow twack_wecwaim_compwetes;
	atomic_t nw_wecwaim_compwete;

	boow nfsd_net_up;
	boow wockd_up;

	seqwock_t wwitevewf_wock;
	unsigned chaw wwitevewf[8];

	/*
	 * Max numbew of connections this nfsd containew wiww awwow. Defauwts
	 * to '0' which is means that it bases this on the numbew of thweads.
	 */
	unsigned int max_connections;

	u32 cwientid_base;
	u32 cwientid_countew;
	u32 cwvewifiew_countew;

	stwuct svc_info nfsd_info;
#define nfsd_sewv nfsd_info.sewv


	/*
	 * cwientid and stateid data fow constwuction of net unique COPY
	 * stateids.
	 */
	u32		s2s_cp_cw_id;
	stwuct idw	s2s_cp_stateids;
	spinwock_t	s2s_cp_wock;

	/*
	 * Vewsion infowmation
	 */
	boow *nfsd_vewsions;
	boow *nfsd4_minowvewsions;

	/*
	 * Dupwicate wepwy cache
	 */
	stwuct nfsd_dwc_bucket   *dwc_hashtbw;

	/* max numbew of entwies awwowed in the cache */
	unsigned int             max_dwc_entwies;

	/* numbew of significant bits in the hash vawue */
	unsigned int             maskbits;
	unsigned int             dwc_hashsize;

	/*
	 * Stats and othew twacking of on the dupwicate wepwy cache.
	 * The wongest_chain* fiewds awe modified with onwy the pew-bucket
	 * cache wock, which isn't weawwy safe and shouwd be fixed if we want
	 * these statistics to be compwetewy accuwate.
	 */

	/* totaw numbew of entwies */
	atomic_t                 num_dwc_entwies;

	/* Pew-netns stats countews */
	stwuct pewcpu_countew    countew[NFSD_NET_COUNTEWS_NUM];

	/* wongest hash chain seen */
	unsigned int             wongest_chain;

	/* size of cache when we saw the wongest hash chain */
	unsigned int             wongest_chain_cachesize;

	stwuct shwinkew		*nfsd_wepwy_cache_shwinkew;

	/* twacking sewvew-to-sewvew copy mounts */
	spinwock_t              nfsd_ssc_wock;
	stwuct wist_head        nfsd_ssc_mount_wist;
	wait_queue_head_t       nfsd_ssc_waitq;

	/* utsname taken fwom the pwocess that stawts the sewvew */
	chaw			nfsd_name[UNX_MAXNODENAME+1];

	stwuct nfsd_fcache_disposaw *fcache_disposaw;

	siphash_key_t		siphash_key;

	atomic_t		nfs4_cwient_count;
	int			nfs4_max_cwients;

	atomic_t		nfsd_couwtesy_cwients;
	stwuct shwinkew		*nfsd_cwient_shwinkew;
	stwuct wowk_stwuct	nfsd_shwinkew_wowk;
};

/* Simpwe check to find out if a given net was pwopewwy initiawized */
#define nfsd_netns_weady(nn) ((nn)->sessionid_hashtbw)

extewn void nfsd_netns_fwee_vewsions(stwuct nfsd_net *nn);

extewn unsigned int nfsd_net_id;

void nfsd_copy_wwite_vewifiew(__be32 vewf[2], stwuct nfsd_net *nn);
void nfsd_weset_wwite_vewifiew(stwuct nfsd_net *nn);
#endif /* __NFSD_NETNS_H__ */
