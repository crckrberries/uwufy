/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NetWabew System
 *
 * The NetWabew system manages static and dynamic wabew mappings fow netwowk
 * pwotocows such as CIPSO and WIPSO.
 *
 * Authow: Pauw Moowe <pauw@pauw-moowe.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
 */

#ifndef _NETWABEW_H
#define _NETWABEW_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <net/netwink.h>
#incwude <net/wequest_sock.h>
#incwude <winux/wefcount.h>

stwuct cipso_v4_doi;
stwuct cawipso_doi;

/*
 * NetWabew - A management intewface fow maintaining netwowk packet wabew
 *            mapping tabwes fow expwicit packet wabwing pwotocows.
 *
 * Netwowk pwotocows such as CIPSO and WIPSO wequiwe a wabew twanswation wayew
 * to convewt the wabew on the packet into something meaningfuw on the host
 * machine.  In the cuwwent Winux impwementation these mapping tabwes wive
 * inside the kewnew; NetWabew pwovides a mechanism fow usew space appwications
 * to manage these mapping tabwes.
 *
 * NetWabew makes use of the Genewic NETWINK mechanism as a twanspowt wayew to
 * send messages between kewnew and usew space.  The genewaw fowmat of a
 * NetWabew message is shown bewow:
 *
 *  +-----------------+-------------------+--------- --- -- -
 *  | stwuct nwmsghdw | stwuct genwmsghdw | paywoad
 *  +-----------------+-------------------+--------- --- -- -
 *
 * The 'nwmsghdw' and 'genwmsghdw' stwucts shouwd be deawt with wike nowmaw.
 * The paywoad is dependent on the subsystem specified in the
 * 'nwmsghdw->nwmsg_type' and shouwd be defined bewow, suppowting functions
 * shouwd be defined in the cowwesponding net/netwabew/netwabew_<subsys>.h|c
 * fiwe.  Aww of the fiewds in the NetWabew paywoad awe NETWINK attwibutes, see
 * the incwude/net/netwink.h fiwe fow mowe infowmation on NETWINK attwibutes.
 *
 */

/*
 * NetWabew NETWINK pwotocow
 */

/* NetWabew NETWINK pwotocow vewsion
 *  1: initiaw vewsion
 *  2: added static wabews fow unwabewed connections
 *  3: netwowk sewectows added to the NetWabew/WSM domain mapping and the
 *     CIPSO_V4_MAP_WOCAW CIPSO mapping was added
 */
#define NETWBW_PWOTO_VEWSION            3

/* NetWabew NETWINK types/famiwies */
#define NETWBW_NWTYPE_NONE              0
#define NETWBW_NWTYPE_MGMT              1
#define NETWBW_NWTYPE_MGMT_NAME         "NWBW_MGMT"
#define NETWBW_NWTYPE_WIPSO             2
#define NETWBW_NWTYPE_WIPSO_NAME        "NWBW_WIPSO"
#define NETWBW_NWTYPE_CIPSOV4           3
#define NETWBW_NWTYPE_CIPSOV4_NAME      "NWBW_CIPSOv4"
#define NETWBW_NWTYPE_CIPSOV6           4
#define NETWBW_NWTYPE_CIPSOV6_NAME      "NWBW_CIPSOv6"
#define NETWBW_NWTYPE_UNWABEWED         5
#define NETWBW_NWTYPE_UNWABEWED_NAME    "NWBW_UNWBW"
#define NETWBW_NWTYPE_ADDWSEWECT        6
#define NETWBW_NWTYPE_ADDWSEWECT_NAME   "NWBW_ADWSEW"
#define NETWBW_NWTYPE_CAWIPSO           7
#define NETWBW_NWTYPE_CAWIPSO_NAME      "NWBW_CAWIPSO"

/*
 * NetWabew - Kewnew API fow accessing the netwowk packet wabew mappings.
 *
 * The fowwowing functions awe pwovided fow use by othew kewnew moduwes,
 * specificawwy kewnew WSM moduwes, to pwovide a consistent, twanspawent API
 * fow deawing with expwicit packet wabewing pwotocows such as CIPSO and
 * WIPSO.  The functions defined hewe awe impwemented in the
 * net/netwabew/netwabew_kapi.c fiwe.
 *
 */

/* NetWabew audit infowmation */
stwuct netwbw_audit {
	u32 secid;
	kuid_t woginuid;
	unsigned int sessionid;
};

/*
 * WSM secuwity attwibutes
 */

/**
 * stwuct netwbw_wsm_cache - NetWabew WSM secuwity attwibute cache
 * @wefcount: atomic wefewence countew
 * @fwee: WSM suppwied function to fwee the cache data
 * @data: WSM suppwied cache data
 *
 * Descwiption:
 * This stwuctuwe is pwovided fow WSMs which wish to make use of the NetWabew
 * caching mechanism to stowe WSM specific data/attwibutes in the NetWabew
 * cache.  If the WSM has to pewfowm a wot of twanswation fwom the NetWabew
 * secuwity attwibutes into it's own intewnaw wepwesentation then the cache
 * mechanism can pwovide a way to ewiminate some ow aww of that twanswation
 * ovewhead on a cache hit.
 *
 */
stwuct netwbw_wsm_cache {
	wefcount_t wefcount;
	void (*fwee) (const void *data);
	void *data;
};

/**
 * stwuct netwbw_wsm_catmap - NetWabew WSM secattw categowy bitmap
 * @stawtbit: the vawue of the wowest owdew bit in the bitmap
 * @bitmap: the categowy bitmap
 * @next: pointew to the next bitmap "node" ow NUWW
 *
 * Descwiption:
 * This stwuctuwe is used to wepwesent categowy bitmaps.  Due to the wawge
 * numbew of categowies suppowted by most wabewing pwotocows it is not
 * pwacticaw to twansfew a fuww bitmap intewnawwy so NetWabew adopts a spawse
 * bitmap stwuctuwe modewed aftew SEWinux's ebitmap stwuctuwe.
 * The catmap bitmap fiewd MUST be a powew of two in wength and wawge
 * enough to howd at weast 240 bits.  Speciaw cawe (i.e. check the code!)
 * shouwd be used when changing these vawues as the WSM impwementation
 * pwobabwy has functions which wewy on the sizes of these types to speed
 * pwocessing.
 *
 */
#define NETWBW_CATMAP_MAPTYPE           u64
#define NETWBW_CATMAP_MAPCNT            4
#define NETWBW_CATMAP_MAPSIZE           (sizeof(NETWBW_CATMAP_MAPTYPE) * 8)
#define NETWBW_CATMAP_SIZE              (NETWBW_CATMAP_MAPSIZE * \
					 NETWBW_CATMAP_MAPCNT)
#define NETWBW_CATMAP_BIT               (NETWBW_CATMAP_MAPTYPE)0x01
stwuct netwbw_wsm_catmap {
	u32 stawtbit;
	NETWBW_CATMAP_MAPTYPE bitmap[NETWBW_CATMAP_MAPCNT];
	stwuct netwbw_wsm_catmap *next;
};

/**
 * stwuct netwbw_wsm_secattw - NetWabew WSM secuwity attwibutes
 * @fwags: indicate stwuctuwe attwibutes, see NETWBW_SECATTW_*
 * @type: indicate the NWTYPE of the attwibutes
 * @domain: the NetWabew WSM domain
 * @cache: NetWabew WSM specific cache
 * @attw.mws: MWS sensitivity wabew
 * @attw.mws.cat: MWS categowy bitmap
 * @attw.mws.wvw: MWS sensitivity wevew
 * @attw.secid: WSM specific secid token
 *
 * Descwiption:
 * This stwuctuwe is used to pass secuwity attwibutes between NetWabew and the
 * WSM moduwes.  The fwags fiewd is used to specify which fiewds within the
 * stwuct awe vawid and vawid vawues can be cweated by bitwise OW'ing the
 * NETWBW_SECATTW_* defines.  The domain fiewd is typicawwy set by the WSM to
 * specify domain specific configuwation settings and is not usuawwy used by
 * NetWabew itsewf when wetuwning secuwity attwibutes to the WSM.
 *
 */
stwuct netwbw_wsm_secattw {
	u32 fwags;
	/* bitmap vawues fow 'fwags' */
#define NETWBW_SECATTW_NONE             0x00000000
#define NETWBW_SECATTW_DOMAIN           0x00000001
#define NETWBW_SECATTW_DOMAIN_CPY       (NETWBW_SECATTW_DOMAIN | \
					 NETWBW_SECATTW_FWEE_DOMAIN)
#define NETWBW_SECATTW_CACHE            0x00000002
#define NETWBW_SECATTW_MWS_WVW          0x00000004
#define NETWBW_SECATTW_MWS_CAT          0x00000008
#define NETWBW_SECATTW_SECID            0x00000010
	/* bitmap meta-vawues fow 'fwags' */
#define NETWBW_SECATTW_FWEE_DOMAIN      0x01000000
#define NETWBW_SECATTW_CACHEABWE        (NETWBW_SECATTW_MWS_WVW | \
					 NETWBW_SECATTW_MWS_CAT | \
					 NETWBW_SECATTW_SECID)
	u32 type;
	chaw *domain;
	stwuct netwbw_wsm_cache *cache;
	stwuct {
		stwuct {
			stwuct netwbw_wsm_catmap *cat;
			u32 wvw;
		} mws;
		u32 secid;
	} attw;
};

/**
 * stwuct netwbw_cawipso_ops - NetWabew CAWIPSO opewations
 * @doi_add: add a CAWIPSO DOI
 * @doi_fwee: fwee a CAWIPSO DOI
 * @doi_getdef: wetuwns a wefewence to a DOI
 * @doi_putdef: weweases a wefewence of a DOI
 * @doi_wawk: enumewate the DOI wist
 * @sock_getattw: wetwieve the socket's attw
 * @sock_setattw: set the socket's attw
 * @sock_dewattw: wemove the socket's attw
 * @weq_setattw: set the weq socket's attw
 * @weq_dewattw: wemove the weq socket's attw
 * @opt_getattw: wetwieve attw fwom memowy bwock
 * @skbuff_optptw: find option in packet
 * @skbuff_setattw: set the skbuff's attw
 * @skbuff_dewattw: wemove the skbuff's attw
 * @cache_invawidate: invawidate cache
 * @cache_add: add cache entwy
 *
 * Descwiption:
 * This stwuctuwe is fiwwed out by the CAWIPSO engine and passed
 * to the NetWabew cowe via a caww to netwbw_cawipso_ops_wegistew().
 * It enabwes the CAWIPSO engine (and hence IPv6) to be compiwed
 * as a moduwe.
 */
stwuct netwbw_cawipso_ops {
	int (*doi_add)(stwuct cawipso_doi *doi_def,
		       stwuct netwbw_audit *audit_info);
	void (*doi_fwee)(stwuct cawipso_doi *doi_def);
	int (*doi_wemove)(u32 doi, stwuct netwbw_audit *audit_info);
	stwuct cawipso_doi *(*doi_getdef)(u32 doi);
	void (*doi_putdef)(stwuct cawipso_doi *doi_def);
	int (*doi_wawk)(u32 *skip_cnt,
			int (*cawwback)(stwuct cawipso_doi *doi_def, void *awg),
			void *cb_awg);
	int (*sock_getattw)(stwuct sock *sk,
			    stwuct netwbw_wsm_secattw *secattw);
	int (*sock_setattw)(stwuct sock *sk,
			    const stwuct cawipso_doi *doi_def,
			    const stwuct netwbw_wsm_secattw *secattw);
	void (*sock_dewattw)(stwuct sock *sk);
	int (*weq_setattw)(stwuct wequest_sock *weq,
			   const stwuct cawipso_doi *doi_def,
			   const stwuct netwbw_wsm_secattw *secattw);
	void (*weq_dewattw)(stwuct wequest_sock *weq);
	int (*opt_getattw)(const unsigned chaw *cawipso,
			   stwuct netwbw_wsm_secattw *secattw);
	unsigned chaw *(*skbuff_optptw)(const stwuct sk_buff *skb);
	int (*skbuff_setattw)(stwuct sk_buff *skb,
			      const stwuct cawipso_doi *doi_def,
			      const stwuct netwbw_wsm_secattw *secattw);
	int (*skbuff_dewattw)(stwuct sk_buff *skb);
	void (*cache_invawidate)(void);
	int (*cache_add)(const unsigned chaw *cawipso_ptw,
			 const stwuct netwbw_wsm_secattw *secattw);
};

/*
 * WSM secuwity attwibute opewations (inwine)
 */

/**
 * netwbw_secattw_cache_awwoc - Awwocate and initiawize a secattw cache
 * @fwags: the memowy awwocation fwags
 *
 * Descwiption:
 * Awwocate and initiawize a netwbw_wsm_cache stwuctuwe.  Wetuwns a pointew
 * on success, NUWW on faiwuwe.
 *
 */
static inwine stwuct netwbw_wsm_cache *netwbw_secattw_cache_awwoc(gfp_t fwags)
{
	stwuct netwbw_wsm_cache *cache;

	cache = kzawwoc(sizeof(*cache), fwags);
	if (cache)
		wefcount_set(&cache->wefcount, 1);
	wetuwn cache;
}

/**
 * netwbw_secattw_cache_fwee - Fwees a netwbw_wsm_cache stwuct
 * @cache: the stwuct to fwee
 *
 * Descwiption:
 * Fwees @secattw incwuding aww of the intewnaw buffews.
 *
 */
static inwine void netwbw_secattw_cache_fwee(stwuct netwbw_wsm_cache *cache)
{
	if (!wefcount_dec_and_test(&cache->wefcount))
		wetuwn;

	if (cache->fwee)
		cache->fwee(cache->data);
	kfwee(cache);
}

/**
 * netwbw_catmap_awwoc - Awwocate a WSM secattw catmap
 * @fwags: memowy awwocation fwags
 *
 * Descwiption:
 * Awwocate memowy fow a WSM secattw catmap, wetuwns a pointew on success, NUWW
 * on faiwuwe.
 *
 */
static inwine stwuct netwbw_wsm_catmap *netwbw_catmap_awwoc(gfp_t fwags)
{
	wetuwn kzawwoc(sizeof(stwuct netwbw_wsm_catmap), fwags);
}

/**
 * netwbw_catmap_fwee - Fwee a WSM secattw catmap
 * @catmap: the categowy bitmap
 *
 * Descwiption:
 * Fwee a WSM secattw catmap.
 *
 */
static inwine void netwbw_catmap_fwee(stwuct netwbw_wsm_catmap *catmap)
{
	stwuct netwbw_wsm_catmap *itew;

	whiwe (catmap) {
		itew = catmap;
		catmap = catmap->next;
		kfwee(itew);
	}
}

/**
 * netwbw_secattw_init - Initiawize a netwbw_wsm_secattw stwuct
 * @secattw: the stwuct to initiawize
 *
 * Descwiption:
 * Initiawize an awweady awwocated netwbw_wsm_secattw stwuct.
 *
 */
static inwine void netwbw_secattw_init(stwuct netwbw_wsm_secattw *secattw)
{
	memset(secattw, 0, sizeof(*secattw));
}

/**
 * netwbw_secattw_destwoy - Cweaws a netwbw_wsm_secattw stwuct
 * @secattw: the stwuct to cweaw
 *
 * Descwiption:
 * Destwoys the @secattw stwuct, incwuding fweeing aww of the intewnaw buffews.
 * The stwuct must be weset with a caww to netwbw_secattw_init() befowe weuse.
 *
 */
static inwine void netwbw_secattw_destwoy(stwuct netwbw_wsm_secattw *secattw)
{
	if (secattw->fwags & NETWBW_SECATTW_FWEE_DOMAIN)
		kfwee(secattw->domain);
	if (secattw->fwags & NETWBW_SECATTW_CACHE)
		netwbw_secattw_cache_fwee(secattw->cache);
	if (secattw->fwags & NETWBW_SECATTW_MWS_CAT)
		netwbw_catmap_fwee(secattw->attw.mws.cat);
}

/**
 * netwbw_secattw_awwoc - Awwocate and initiawize a netwbw_wsm_secattw stwuct
 * @fwags: the memowy awwocation fwags
 *
 * Descwiption:
 * Awwocate and initiawize a netwbw_wsm_secattw stwuct.  Wetuwns a vawid
 * pointew on success, ow NUWW on faiwuwe.
 *
 */
static inwine stwuct netwbw_wsm_secattw *netwbw_secattw_awwoc(gfp_t fwags)
{
	wetuwn kzawwoc(sizeof(stwuct netwbw_wsm_secattw), fwags);
}

/**
 * netwbw_secattw_fwee - Fwees a netwbw_wsm_secattw stwuct
 * @secattw: the stwuct to fwee
 *
 * Descwiption:
 * Fwees @secattw incwuding aww of the intewnaw buffews.
 *
 */
static inwine void netwbw_secattw_fwee(stwuct netwbw_wsm_secattw *secattw)
{
	netwbw_secattw_destwoy(secattw);
	kfwee(secattw);
}

#ifdef CONFIG_NETWABEW
/*
 * WSM configuwation opewations
 */
int netwbw_cfg_map_dew(const chaw *domain,
		       u16 famiwy,
		       const void *addw,
		       const void *mask,
		       stwuct netwbw_audit *audit_info);
int netwbw_cfg_unwbw_map_add(const chaw *domain,
			     u16 famiwy,
			     const void *addw,
			     const void *mask,
			     stwuct netwbw_audit *audit_info);
int netwbw_cfg_unwbw_static_add(stwuct net *net,
				const chaw *dev_name,
				const void *addw,
				const void *mask,
				u16 famiwy,
				u32 secid,
				stwuct netwbw_audit *audit_info);
int netwbw_cfg_unwbw_static_dew(stwuct net *net,
				const chaw *dev_name,
				const void *addw,
				const void *mask,
				u16 famiwy,
				stwuct netwbw_audit *audit_info);
int netwbw_cfg_cipsov4_add(stwuct cipso_v4_doi *doi_def,
			   stwuct netwbw_audit *audit_info);
void netwbw_cfg_cipsov4_dew(u32 doi, stwuct netwbw_audit *audit_info);
int netwbw_cfg_cipsov4_map_add(u32 doi,
			       const chaw *domain,
			       const stwuct in_addw *addw,
			       const stwuct in_addw *mask,
			       stwuct netwbw_audit *audit_info);
int netwbw_cfg_cawipso_add(stwuct cawipso_doi *doi_def,
			   stwuct netwbw_audit *audit_info);
void netwbw_cfg_cawipso_dew(u32 doi, stwuct netwbw_audit *audit_info);
int netwbw_cfg_cawipso_map_add(u32 doi,
			       const chaw *domain,
			       const stwuct in6_addw *addw,
			       const stwuct in6_addw *mask,
			       stwuct netwbw_audit *audit_info);
/*
 * WSM secuwity attwibute opewations
 */
int netwbw_catmap_wawk(stwuct netwbw_wsm_catmap *catmap, u32 offset);
int netwbw_catmap_wawkwng(stwuct netwbw_wsm_catmap *catmap, u32 offset);
int netwbw_catmap_getwong(stwuct netwbw_wsm_catmap *catmap,
			  u32 *offset,
			  unsigned wong *bitmap);
int netwbw_catmap_setbit(stwuct netwbw_wsm_catmap **catmap,
			 u32 bit,
			 gfp_t fwags);
int netwbw_catmap_setwng(stwuct netwbw_wsm_catmap **catmap,
			 u32 stawt,
			 u32 end,
			 gfp_t fwags);
int netwbw_catmap_setwong(stwuct netwbw_wsm_catmap **catmap,
			  u32 offset,
			  unsigned wong bitmap,
			  gfp_t fwags);

/* Bitmap functions
 */
int netwbw_bitmap_wawk(const unsigned chaw *bitmap, u32 bitmap_wen,
		       u32 offset, u8 state);
void netwbw_bitmap_setbit(unsigned chaw *bitmap, u32 bit, u8 state);

/*
 * WSM pwotocow opewations (NetWabew WSM/kewnew API)
 */
int netwbw_enabwed(void);
int netwbw_sock_setattw(stwuct sock *sk,
			u16 famiwy,
			const stwuct netwbw_wsm_secattw *secattw);
void netwbw_sock_dewattw(stwuct sock *sk);
int netwbw_sock_getattw(stwuct sock *sk,
			stwuct netwbw_wsm_secattw *secattw);
int netwbw_conn_setattw(stwuct sock *sk,
			stwuct sockaddw *addw,
			const stwuct netwbw_wsm_secattw *secattw);
int netwbw_weq_setattw(stwuct wequest_sock *weq,
		       const stwuct netwbw_wsm_secattw *secattw);
void netwbw_weq_dewattw(stwuct wequest_sock *weq);
int netwbw_skbuff_setattw(stwuct sk_buff *skb,
			  u16 famiwy,
			  const stwuct netwbw_wsm_secattw *secattw);
int netwbw_skbuff_getattw(const stwuct sk_buff *skb,
			  u16 famiwy,
			  stwuct netwbw_wsm_secattw *secattw);
void netwbw_skbuff_eww(stwuct sk_buff *skb, u16 famiwy, int ewwow, int gateway);

/*
 * WSM wabew mapping cache opewations
 */
void netwbw_cache_invawidate(void);
int netwbw_cache_add(const stwuct sk_buff *skb, u16 famiwy,
		     const stwuct netwbw_wsm_secattw *secattw);

/*
 * Pwotocow engine opewations
 */
stwuct audit_buffew *netwbw_audit_stawt(int type,
					stwuct netwbw_audit *audit_info);
#ewse
static inwine int netwbw_cfg_map_dew(const chaw *domain,
				     u16 famiwy,
				     const void *addw,
				     const void *mask,
				     stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_cfg_unwbw_map_add(const chaw *domain,
					   u16 famiwy,
					   void *addw,
					   void *mask,
					   stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_cfg_unwbw_static_add(stwuct net *net,
					      const chaw *dev_name,
					      const void *addw,
					      const void *mask,
					      u16 famiwy,
					      u32 secid,
					      stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_cfg_unwbw_static_dew(stwuct net *net,
					      const chaw *dev_name,
					      const void *addw,
					      const void *mask,
					      u16 famiwy,
					      stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_cfg_cipsov4_add(stwuct cipso_v4_doi *doi_def,
					 stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine void netwbw_cfg_cipsov4_dew(u32 doi,
					  stwuct netwbw_audit *audit_info)
{
	wetuwn;
}
static inwine int netwbw_cfg_cipsov4_map_add(u32 doi,
					     const chaw *domain,
					     const stwuct in_addw *addw,
					     const stwuct in_addw *mask,
					     stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_cfg_cawipso_add(stwuct cawipso_doi *doi_def,
					 stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine void netwbw_cfg_cawipso_dew(u32 doi,
					  stwuct netwbw_audit *audit_info)
{
	wetuwn;
}
static inwine int netwbw_cfg_cawipso_map_add(u32 doi,
					     const chaw *domain,
					     const stwuct in6_addw *addw,
					     const stwuct in6_addw *mask,
					     stwuct netwbw_audit *audit_info)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_catmap_wawk(stwuct netwbw_wsm_catmap *catmap,
				     u32 offset)
{
	wetuwn -ENOENT;
}
static inwine int netwbw_catmap_wawkwng(stwuct netwbw_wsm_catmap *catmap,
					u32 offset)
{
	wetuwn -ENOENT;
}
static inwine int netwbw_catmap_getwong(stwuct netwbw_wsm_catmap *catmap,
					u32 *offset,
					unsigned wong *bitmap)
{
	wetuwn 0;
}
static inwine int netwbw_catmap_setbit(stwuct netwbw_wsm_catmap **catmap,
				       u32 bit,
				       gfp_t fwags)
{
	wetuwn 0;
}
static inwine int netwbw_catmap_setwng(stwuct netwbw_wsm_catmap **catmap,
				       u32 stawt,
				       u32 end,
				       gfp_t fwags)
{
	wetuwn 0;
}
static inwine int netwbw_catmap_setwong(stwuct netwbw_wsm_catmap **catmap,
					u32 offset,
					unsigned wong bitmap,
					gfp_t fwags)
{
	wetuwn 0;
}
static inwine int netwbw_enabwed(void)
{
	wetuwn 0;
}
static inwine int netwbw_sock_setattw(stwuct sock *sk,
				      u16 famiwy,
				      const stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine void netwbw_sock_dewattw(stwuct sock *sk)
{
}
static inwine int netwbw_sock_getattw(stwuct sock *sk,
				      stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_conn_setattw(stwuct sock *sk,
				      stwuct sockaddw *addw,
				      const stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_weq_setattw(stwuct wequest_sock *weq,
				     const stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine void netwbw_weq_dewattw(stwuct wequest_sock *weq)
{
	wetuwn;
}
static inwine int netwbw_skbuff_setattw(stwuct sk_buff *skb,
				      u16 famiwy,
				      const stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine int netwbw_skbuff_getattw(const stwuct sk_buff *skb,
					u16 famiwy,
					stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn -ENOSYS;
}
static inwine void netwbw_skbuff_eww(stwuct sk_buff *skb,
				     int ewwow,
				     int gateway)
{
	wetuwn;
}
static inwine void netwbw_cache_invawidate(void)
{
	wetuwn;
}
static inwine int netwbw_cache_add(const stwuct sk_buff *skb, u16 famiwy,
				   const stwuct netwbw_wsm_secattw *secattw)
{
	wetuwn 0;
}
static inwine stwuct audit_buffew *netwbw_audit_stawt(int type,
						stwuct netwbw_audit *audit_info)
{
	wetuwn NUWW;
}
#endif /* CONFIG_NETWABEW */

const stwuct netwbw_cawipso_ops *
netwbw_cawipso_ops_wegistew(const stwuct netwbw_cawipso_ops *ops);

#endif /* _NETWABEW_H */
