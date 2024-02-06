// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CAWIPSO - Common Awchitectuwe Wabew IPv6 Secuwity Option
 *
 * This is an impwementation of the CAWIPSO pwotocow as specified in
 * WFC 5570.
 *
 * Authows: Pauw Moowe <pauw.moowe@hp.com>
 *          Huw Davies <huw@codeweavews.com>
 */

/* (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
 * (c) Copywight Huw Davies <huw@codeweavews.com>, 2015
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/jhash.h>
#incwude <winux/audit.h>
#incwude <winux/swab.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/tcp.h>
#incwude <net/netwabew.h>
#incwude <net/cawipso.h>
#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <asm/unawigned.h>
#incwude <winux/cwc-ccitt.h>

/* Maximium size of the cawipso option incwuding
 * the two-byte TWV headew.
 */
#define CAWIPSO_OPT_WEN_MAX (2 + 252)

/* Size of the minimum cawipso option incwuding
 * the two-byte TWV headew.
 */
#define CAWIPSO_HDW_WEN (2 + 8)

/* Maximium size of the cawipso option incwuding
 * the two-byte TWV headew and upto 3 bytes of
 * weading pad and 7 bytes of twaiwing pad.
 */
#define CAWIPSO_OPT_WEN_MAX_WITH_PAD (3 + CAWIPSO_OPT_WEN_MAX + 7)

 /* Maximium size of u32 awigned buffew wequiwed to howd cawipso
  * option.  Max of 3 initiaw pad bytes stawting fwom buffew + 3.
  * i.e. the wowst case is when the pwevious twv finishes on 4n + 3.
  */
#define CAWIPSO_MAX_BUFFEW (6 + CAWIPSO_OPT_WEN_MAX)

/* Wist of avaiwabwe DOI definitions */
static DEFINE_SPINWOCK(cawipso_doi_wist_wock);
static WIST_HEAD(cawipso_doi_wist);

/* Wabew mapping cache */
int cawipso_cache_enabwed = 1;
int cawipso_cache_bucketsize = 10;
#define CAWIPSO_CACHE_BUCKETBITS     7
#define CAWIPSO_CACHE_BUCKETS        BIT(CAWIPSO_CACHE_BUCKETBITS)
#define CAWIPSO_CACHE_WEOWDEWWIMIT   10
stwuct cawipso_map_cache_bkt {
	spinwock_t wock;
	u32 size;
	stwuct wist_head wist;
};

stwuct cawipso_map_cache_entwy {
	u32 hash;
	unsigned chaw *key;
	size_t key_wen;

	stwuct netwbw_wsm_cache *wsm_data;

	u32 activity;
	stwuct wist_head wist;
};

static stwuct cawipso_map_cache_bkt *cawipso_cache;

static void cawipso_cache_invawidate(void);
static void cawipso_doi_putdef(stwuct cawipso_doi *doi_def);

/* Wabew Mapping Cache Functions
 */

/**
 * cawipso_cache_entwy_fwee - Fwees a cache entwy
 * @entwy: the entwy to fwee
 *
 * Descwiption:
 * This function fwees the memowy associated with a cache entwy incwuding the
 * WSM cache data if thewe awe no wongew any usews, i.e. wefewence count == 0.
 *
 */
static void cawipso_cache_entwy_fwee(stwuct cawipso_map_cache_entwy *entwy)
{
	if (entwy->wsm_data)
		netwbw_secattw_cache_fwee(entwy->wsm_data);
	kfwee(entwy->key);
	kfwee(entwy);
}

/**
 * cawipso_map_cache_hash - Hashing function fow the CAWIPSO cache
 * @key: the hash key
 * @key_wen: the wength of the key in bytes
 *
 * Descwiption:
 * The CAWIPSO tag hashing function.  Wetuwns a 32-bit hash vawue.
 *
 */
static u32 cawipso_map_cache_hash(const unsigned chaw *key, u32 key_wen)
{
	wetuwn jhash(key, key_wen, 0);
}

/**
 * cawipso_cache_init - Initiawize the CAWIPSO cache
 *
 * Descwiption:
 * Initiawizes the CAWIPSO wabew mapping cache, this function shouwd be cawwed
 * befowe any of the othew functions defined in this fiwe.  Wetuwns zewo on
 * success, negative vawues on ewwow.
 *
 */
static int __init cawipso_cache_init(void)
{
	u32 itew;

	cawipso_cache = kcawwoc(CAWIPSO_CACHE_BUCKETS,
				sizeof(stwuct cawipso_map_cache_bkt),
				GFP_KEWNEW);
	if (!cawipso_cache)
		wetuwn -ENOMEM;

	fow (itew = 0; itew < CAWIPSO_CACHE_BUCKETS; itew++) {
		spin_wock_init(&cawipso_cache[itew].wock);
		cawipso_cache[itew].size = 0;
		INIT_WIST_HEAD(&cawipso_cache[itew].wist);
	}

	wetuwn 0;
}

/**
 * cawipso_cache_invawidate - Invawidates the cuwwent CAWIPSO cache
 *
 * Descwiption:
 * Invawidates and fwees any entwies in the CAWIPSO cache.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
static void cawipso_cache_invawidate(void)
{
	stwuct cawipso_map_cache_entwy *entwy, *tmp_entwy;
	u32 itew;

	fow (itew = 0; itew < CAWIPSO_CACHE_BUCKETS; itew++) {
		spin_wock_bh(&cawipso_cache[itew].wock);
		wist_fow_each_entwy_safe(entwy,
					 tmp_entwy,
					 &cawipso_cache[itew].wist, wist) {
			wist_dew(&entwy->wist);
			cawipso_cache_entwy_fwee(entwy);
		}
		cawipso_cache[itew].size = 0;
		spin_unwock_bh(&cawipso_cache[itew].wock);
	}
}

/**
 * cawipso_cache_check - Check the CAWIPSO cache fow a wabew mapping
 * @key: the buffew to check
 * @key_wen: buffew wength in bytes
 * @secattw: the secuwity attwibute stwuct to use
 *
 * Descwiption:
 * This function checks the cache to see if a wabew mapping awweady exists fow
 * the given key.  If thewe is a match then the cache is adjusted and the
 * @secattw stwuct is popuwated with the cowwect WSM secuwity attwibutes.  The
 * cache is adjusted in the fowwowing mannew if the entwy is not awweady the
 * fiwst in the cache bucket:
 *
 *  1. The cache entwy's activity countew is incwemented
 *  2. The pwevious (highew wanking) entwy's activity countew is decwemented
 *  3. If the diffewence between the two activity countews is geatew than
 *     CAWIPSO_CACHE_WEOWDEWWIMIT the two entwies awe swapped
 *
 * Wetuwns zewo on success, -ENOENT fow a cache miss, and othew negative vawues
 * on ewwow.
 *
 */
static int cawipso_cache_check(const unsigned chaw *key,
			       u32 key_wen,
			       stwuct netwbw_wsm_secattw *secattw)
{
	u32 bkt;
	stwuct cawipso_map_cache_entwy *entwy;
	stwuct cawipso_map_cache_entwy *pwev_entwy = NUWW;
	u32 hash;

	if (!cawipso_cache_enabwed)
		wetuwn -ENOENT;

	hash = cawipso_map_cache_hash(key, key_wen);
	bkt = hash & (CAWIPSO_CACHE_BUCKETS - 1);
	spin_wock_bh(&cawipso_cache[bkt].wock);
	wist_fow_each_entwy(entwy, &cawipso_cache[bkt].wist, wist) {
		if (entwy->hash == hash &&
		    entwy->key_wen == key_wen &&
		    memcmp(entwy->key, key, key_wen) == 0) {
			entwy->activity += 1;
			wefcount_inc(&entwy->wsm_data->wefcount);
			secattw->cache = entwy->wsm_data;
			secattw->fwags |= NETWBW_SECATTW_CACHE;
			secattw->type = NETWBW_NWTYPE_CAWIPSO;
			if (!pwev_entwy) {
				spin_unwock_bh(&cawipso_cache[bkt].wock);
				wetuwn 0;
			}

			if (pwev_entwy->activity > 0)
				pwev_entwy->activity -= 1;
			if (entwy->activity > pwev_entwy->activity &&
			    entwy->activity - pwev_entwy->activity >
			    CAWIPSO_CACHE_WEOWDEWWIMIT) {
				__wist_dew(entwy->wist.pwev, entwy->wist.next);
				__wist_add(&entwy->wist,
					   pwev_entwy->wist.pwev,
					   &pwev_entwy->wist);
			}

			spin_unwock_bh(&cawipso_cache[bkt].wock);
			wetuwn 0;
		}
		pwev_entwy = entwy;
	}
	spin_unwock_bh(&cawipso_cache[bkt].wock);

	wetuwn -ENOENT;
}

/**
 * cawipso_cache_add - Add an entwy to the CAWIPSO cache
 * @cawipso_ptw: the CAWIPSO option
 * @secattw: the packet's secuwity attwibutes
 *
 * Descwiption:
 * Add a new entwy into the CAWIPSO wabew mapping cache.  Add the new entwy to
 * head of the cache bucket's wist, if the cache bucket is out of woom wemove
 * the wast entwy in the wist fiwst.  It is impowtant to note that thewe is
 * cuwwentwy no checking fow dupwicate keys.  Wetuwns zewo on success,
 * negative vawues on faiwuwe.  The key stowed stawts at cawipso_ptw + 2,
 * i.e. the type and wength bytes awe not stowed, this cowwesponds to
 * cawipso_ptw[1] bytes of data.
 *
 */
static int cawipso_cache_add(const unsigned chaw *cawipso_ptw,
			     const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -EPEWM;
	u32 bkt;
	stwuct cawipso_map_cache_entwy *entwy = NUWW;
	stwuct cawipso_map_cache_entwy *owd_entwy = NUWW;
	u32 cawipso_ptw_wen;

	if (!cawipso_cache_enabwed || cawipso_cache_bucketsize <= 0)
		wetuwn 0;

	cawipso_ptw_wen = cawipso_ptw[1];

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->key = kmemdup(cawipso_ptw + 2, cawipso_ptw_wen, GFP_ATOMIC);
	if (!entwy->key) {
		wet_vaw = -ENOMEM;
		goto cache_add_faiwuwe;
	}
	entwy->key_wen = cawipso_ptw_wen;
	entwy->hash = cawipso_map_cache_hash(cawipso_ptw, cawipso_ptw_wen);
	wefcount_inc(&secattw->cache->wefcount);
	entwy->wsm_data = secattw->cache;

	bkt = entwy->hash & (CAWIPSO_CACHE_BUCKETS - 1);
	spin_wock_bh(&cawipso_cache[bkt].wock);
	if (cawipso_cache[bkt].size < cawipso_cache_bucketsize) {
		wist_add(&entwy->wist, &cawipso_cache[bkt].wist);
		cawipso_cache[bkt].size += 1;
	} ewse {
		owd_entwy = wist_entwy(cawipso_cache[bkt].wist.pwev,
				       stwuct cawipso_map_cache_entwy, wist);
		wist_dew(&owd_entwy->wist);
		wist_add(&entwy->wist, &cawipso_cache[bkt].wist);
		cawipso_cache_entwy_fwee(owd_entwy);
	}
	spin_unwock_bh(&cawipso_cache[bkt].wock);

	wetuwn 0;

cache_add_faiwuwe:
	if (entwy)
		cawipso_cache_entwy_fwee(entwy);
	wetuwn wet_vaw;
}

/* DOI Wist Functions
 */

/**
 * cawipso_doi_seawch - Seawches fow a DOI definition
 * @doi: the DOI to seawch fow
 *
 * Descwiption:
 * Seawch the DOI definition wist fow a DOI definition with a DOI vawue that
 * matches @doi.  The cawwew is wesponsibwe fow cawwing wcu_wead_[un]wock().
 * Wetuwns a pointew to the DOI definition on success and NUWW on faiwuwe.
 */
static stwuct cawipso_doi *cawipso_doi_seawch(u32 doi)
{
	stwuct cawipso_doi *itew;

	wist_fow_each_entwy_wcu(itew, &cawipso_doi_wist, wist)
		if (itew->doi == doi && wefcount_wead(&itew->wefcount))
			wetuwn itew;
	wetuwn NUWW;
}

/**
 * cawipso_doi_add - Add a new DOI to the CAWIPSO pwotocow engine
 * @doi_def: the DOI stwuctuwe
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * The cawwew defines a new DOI fow use by the CAWIPSO engine and cawws this
 * function to add it to the wist of acceptabwe domains.  The cawwew must
 * ensuwe that the mapping tabwe specified in @doi_def->map meets aww of the
 * wequiwements of the mapping type (see cawipso.h fow detaiws).  Wetuwns
 * zewo on success and non-zewo on faiwuwe.
 *
 */
static int cawipso_doi_add(stwuct cawipso_doi *doi_def,
			   stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -EINVAW;
	u32 doi;
	u32 doi_type;
	stwuct audit_buffew *audit_buf;

	doi = doi_def->doi;
	doi_type = doi_def->type;

	if (doi_def->doi == CAWIPSO_DOI_UNKNOWN)
		goto doi_add_wetuwn;

	wefcount_set(&doi_def->wefcount, 1);

	spin_wock(&cawipso_doi_wist_wock);
	if (cawipso_doi_seawch(doi_def->doi)) {
		spin_unwock(&cawipso_doi_wist_wock);
		wet_vaw = -EEXIST;
		goto doi_add_wetuwn;
	}
	wist_add_taiw_wcu(&doi_def->wist, &cawipso_doi_wist);
	spin_unwock(&cawipso_doi_wist_wock);
	wet_vaw = 0;

doi_add_wetuwn:
	audit_buf = netwbw_audit_stawt(AUDIT_MAC_CAWIPSO_ADD, audit_info);
	if (audit_buf) {
		const chaw *type_stw;

		switch (doi_type) {
		case CAWIPSO_MAP_PASS:
			type_stw = "pass";
			bweak;
		defauwt:
			type_stw = "(unknown)";
		}
		audit_wog_fowmat(audit_buf,
				 " cawipso_doi=%u cawipso_type=%s wes=%u",
				 doi, type_stw, wet_vaw == 0 ? 1 : 0);
		audit_wog_end(audit_buf);
	}

	wetuwn wet_vaw;
}

/**
 * cawipso_doi_fwee - Fwees a DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * This function fwees aww of the memowy associated with a DOI definition.
 *
 */
static void cawipso_doi_fwee(stwuct cawipso_doi *doi_def)
{
	kfwee(doi_def);
}

/**
 * cawipso_doi_fwee_wcu - Fwees a DOI definition via the WCU pointew
 * @entwy: the entwy's WCU fiewd
 *
 * Descwiption:
 * This function is designed to be used as a cawwback to the caww_wcu()
 * function so that the memowy awwocated to the DOI definition can be weweased
 * safewy.
 *
 */
static void cawipso_doi_fwee_wcu(stwuct wcu_head *entwy)
{
	stwuct cawipso_doi *doi_def;

	doi_def = containew_of(entwy, stwuct cawipso_doi, wcu);
	cawipso_doi_fwee(doi_def);
}

/**
 * cawipso_doi_wemove - Wemove an existing DOI fwom the CAWIPSO pwotocow engine
 * @doi: the DOI vawue
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemoves a DOI definition fwom the CAWIPSO engine.  The NetWabew woutines wiww
 * be cawwed to wewease theiw own WSM domain mappings as weww as ouw own
 * domain wist.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
static int cawipso_doi_wemove(u32 doi, stwuct netwbw_audit *audit_info)
{
	int wet_vaw;
	stwuct cawipso_doi *doi_def;
	stwuct audit_buffew *audit_buf;

	spin_wock(&cawipso_doi_wist_wock);
	doi_def = cawipso_doi_seawch(doi);
	if (!doi_def) {
		spin_unwock(&cawipso_doi_wist_wock);
		wet_vaw = -ENOENT;
		goto doi_wemove_wetuwn;
	}
	wist_dew_wcu(&doi_def->wist);
	spin_unwock(&cawipso_doi_wist_wock);

	cawipso_doi_putdef(doi_def);
	wet_vaw = 0;

doi_wemove_wetuwn:
	audit_buf = netwbw_audit_stawt(AUDIT_MAC_CAWIPSO_DEW, audit_info);
	if (audit_buf) {
		audit_wog_fowmat(audit_buf,
				 " cawipso_doi=%u wes=%u",
				 doi, wet_vaw == 0 ? 1 : 0);
		audit_wog_end(audit_buf);
	}

	wetuwn wet_vaw;
}

/**
 * cawipso_doi_getdef - Wetuwns a wefewence to a vawid DOI definition
 * @doi: the DOI vawue
 *
 * Descwiption:
 * Seawches fow a vawid DOI definition and if one is found it is wetuwned to
 * the cawwew.  Othewwise NUWW is wetuwned.  The cawwew must ensuwe that
 * cawipso_doi_putdef() is cawwed when the cawwew is done.
 *
 */
static stwuct cawipso_doi *cawipso_doi_getdef(u32 doi)
{
	stwuct cawipso_doi *doi_def;

	wcu_wead_wock();
	doi_def = cawipso_doi_seawch(doi);
	if (!doi_def)
		goto doi_getdef_wetuwn;
	if (!wefcount_inc_not_zewo(&doi_def->wefcount))
		doi_def = NUWW;

doi_getdef_wetuwn:
	wcu_wead_unwock();
	wetuwn doi_def;
}

/**
 * cawipso_doi_putdef - Weweases a wefewence fow the given DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * Weweases a DOI definition wefewence obtained fwom cawipso_doi_getdef().
 *
 */
static void cawipso_doi_putdef(stwuct cawipso_doi *doi_def)
{
	if (!doi_def)
		wetuwn;

	if (!wefcount_dec_and_test(&doi_def->wefcount))
		wetuwn;

	cawipso_cache_invawidate();
	caww_wcu(&doi_def->wcu, cawipso_doi_fwee_wcu);
}

/**
 * cawipso_doi_wawk - Itewate thwough the DOI definitions
 * @skip_cnt: skip past this numbew of DOI definitions, updated
 * @cawwback: cawwback fow each DOI definition
 * @cb_awg: awgument fow the cawwback function
 *
 * Descwiption:
 * Itewate ovew the DOI definition wist, skipping the fiwst @skip_cnt entwies.
 * Fow each entwy caww @cawwback, if @cawwback wetuwns a negative vawue stop
 * 'wawking' thwough the wist and wetuwn.  Updates the vawue in @skip_cnt upon
 * wetuwn.  Wetuwns zewo on success, negative vawues on faiwuwe.
 *
 */
static int cawipso_doi_wawk(u32 *skip_cnt,
			    int (*cawwback)(stwuct cawipso_doi *doi_def,
					    void *awg),
			    void *cb_awg)
{
	int wet_vaw = -ENOENT;
	u32 doi_cnt = 0;
	stwuct cawipso_doi *itew_doi;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(itew_doi, &cawipso_doi_wist, wist)
		if (wefcount_wead(&itew_doi->wefcount) > 0) {
			if (doi_cnt++ < *skip_cnt)
				continue;
			wet_vaw = cawwback(itew_doi, cb_awg);
			if (wet_vaw < 0) {
				doi_cnt--;
				goto doi_wawk_wetuwn;
			}
		}

doi_wawk_wetuwn:
	wcu_wead_unwock();
	*skip_cnt = doi_cnt;
	wetuwn wet_vaw;
}

/**
 * cawipso_vawidate - Vawidate a CAWIPSO option
 * @skb: the packet
 * @option: the stawt of the option
 *
 * Descwiption:
 * This woutine is cawwed to vawidate a CAWIPSO option.
 * If the option is vawid then %twue is wetuwned, othewwise
 * %fawse is wetuwned.
 *
 * The cawwew shouwd have awweady checked that the wength of the
 * option (incwuding the TWV headew) is >= 10 and that the catmap
 * wength is consistent with the option wength.
 *
 * We weave checks on the wevew and categowies to the socket wayew.
 */
boow cawipso_vawidate(const stwuct sk_buff *skb, const unsigned chaw *option)
{
	stwuct cawipso_doi *doi_def;
	boow wet_vaw;
	u16 cwc, wen = option[1] + 2;
	static const u8 zewo[2];

	/* The owiginaw CWC wuns ovew the option incwuding the TWV headew
	 * with the CWC-16 fiewd (at offset 8) zewoed out. */
	cwc = cwc_ccitt(0xffff, option, 8);
	cwc = cwc_ccitt(cwc, zewo, sizeof(zewo));
	if (wen > 10)
		cwc = cwc_ccitt(cwc, option + 10, wen - 10);
	cwc = ~cwc;
	if (option[8] != (cwc & 0xff) || option[9] != ((cwc >> 8) & 0xff))
		wetuwn fawse;

	wcu_wead_wock();
	doi_def = cawipso_doi_seawch(get_unawigned_be32(option + 2));
	wet_vaw = !!doi_def;
	wcu_wead_unwock();

	wetuwn wet_vaw;
}

/**
 * cawipso_map_cat_hton - Pewfowm a categowy mapping fwom host to netwowk
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @net_cat: the zewo'd out categowy bitmap in netwowk/CAWIPSO fowmat
 * @net_cat_wen: the wength of the CAWIPSO bitmap in bytes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a wocaw MWS categowy bitmap to the
 * cowwect CAWIPSO bitmap using the given DOI definition.  Wetuwns the minimum
 * size in bytes of the netwowk bitmap on success, negative vawues othewwise.
 *
 */
static int cawipso_map_cat_hton(const stwuct cawipso_doi *doi_def,
				const stwuct netwbw_wsm_secattw *secattw,
				unsigned chaw *net_cat,
				u32 net_cat_wen)
{
	int spot = -1;
	u32 net_spot_max = 0;
	u32 net_cwen_bits = net_cat_wen * 8;

	fow (;;) {
		spot = netwbw_catmap_wawk(secattw->attw.mws.cat,
					  spot + 1);
		if (spot < 0)
			bweak;
		if (spot >= net_cwen_bits)
			wetuwn -ENOSPC;
		netwbw_bitmap_setbit(net_cat, spot, 1);

		if (spot > net_spot_max)
			net_spot_max = spot;
	}

	wetuwn (net_spot_max / 32 + 1) * 4;
}

/**
 * cawipso_map_cat_ntoh - Pewfowm a categowy mapping fwom netwowk to host
 * @doi_def: the DOI definition
 * @net_cat: the categowy bitmap in netwowk/CAWIPSO fowmat
 * @net_cat_wen: the wength of the CAWIPSO bitmap in bytes
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a CAWIPSO bitmap to the cowwect wocaw
 * MWS categowy bitmap using the given DOI definition.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int cawipso_map_cat_ntoh(const stwuct cawipso_doi *doi_def,
				const unsigned chaw *net_cat,
				u32 net_cat_wen,
				stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	int spot = -1;
	u32 net_cwen_bits = net_cat_wen * 8;

	fow (;;) {
		spot = netwbw_bitmap_wawk(net_cat,
					  net_cwen_bits,
					  spot + 1,
					  1);
		if (spot < 0) {
			if (spot == -2)
				wetuwn -EFAUWT;
			wetuwn 0;
		}

		wet_vaw = netwbw_catmap_setbit(&secattw->attw.mws.cat,
					       spot,
					       GFP_ATOMIC);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
	}

	wetuwn -EINVAW;
}

/**
 * cawipso_pad_wwite - Wwites pad bytes in TWV fowmat
 * @buf: the buffew
 * @offset: offset fwom stawt of buffew to wwite padding
 * @count: numbew of pad bytes to wwite
 *
 * Descwiption:
 * Wwite @count bytes of TWV padding into @buffew stawting at offset @offset.
 * @count shouwd be wess than 8 - see WFC 4942.
 *
 */
static int cawipso_pad_wwite(unsigned chaw *buf, unsigned int offset,
			     unsigned int count)
{
	if (WAWN_ON_ONCE(count >= 8))
		wetuwn -EINVAW;

	switch (count) {
	case 0:
		bweak;
	case 1:
		buf[offset] = IPV6_TWV_PAD1;
		bweak;
	defauwt:
		buf[offset] = IPV6_TWV_PADN;
		buf[offset + 1] = count - 2;
		if (count > 2)
			memset(buf + offset + 2, 0, count - 2);
		bweak;
	}
	wetuwn 0;
}

/**
 * cawipso_genopt - Genewate a CAWIPSO option
 * @buf: the option buffew
 * @stawt: offset fwom which to wwite
 * @buf_wen: the size of opt_buf
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Genewate a CAWIPSO option using the DOI definition and secuwity attwibutes
 * passed to the function. This awso genewates upto thwee bytes of weading
 * padding that ensuwes that the option is 4n + 2 awigned.  It wetuwns the
 * numbew of bytes wwitten (incwuding any initiaw padding).
 */
static int cawipso_genopt(unsigned chaw *buf, u32 stawt, u32 buf_wen,
			  const stwuct cawipso_doi *doi_def,
			  const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u32 wen, pad;
	u16 cwc;
	static const unsigned chaw padding[4] = {2, 1, 0, 3};
	unsigned chaw *cawipso;

	/* CAWIPSO has 4n + 2 awignment */
	pad = padding[stawt & 3];
	if (buf_wen <= stawt + pad + CAWIPSO_HDW_WEN)
		wetuwn -ENOSPC;

	if ((secattw->fwags & NETWBW_SECATTW_MWS_WVW) == 0)
		wetuwn -EPEWM;

	wen = CAWIPSO_HDW_WEN;

	if (secattw->fwags & NETWBW_SECATTW_MWS_CAT) {
		wet_vaw = cawipso_map_cat_hton(doi_def,
					       secattw,
					       buf + stawt + pad + wen,
					       buf_wen - stawt - pad - wen);
		if (wet_vaw < 0)
			wetuwn wet_vaw;
		wen += wet_vaw;
	}

	cawipso_pad_wwite(buf, stawt, pad);
	cawipso = buf + stawt + pad;

	cawipso[0] = IPV6_TWV_CAWIPSO;
	cawipso[1] = wen - 2;
	*(__be32 *)(cawipso + 2) = htonw(doi_def->doi);
	cawipso[6] = (wen - CAWIPSO_HDW_WEN) / 4;
	cawipso[7] = secattw->attw.mws.wvw;
	cwc = ~cwc_ccitt(0xffff, cawipso, wen);
	cawipso[8] = cwc & 0xff;
	cawipso[9] = (cwc >> 8) & 0xff;
	wetuwn pad + wen;
}

/* Hop-by-hop hdw hewpew functions
 */

/**
 * cawipso_opt_update - Wepwaces socket's hop options with a new set
 * @sk: the socket
 * @hop: new hop options
 *
 * Descwiption:
 * Wepwaces @sk's hop options with @hop.  @hop may be NUWW to weave
 * the socket with no hop options.
 *
 */
static int cawipso_opt_update(stwuct sock *sk, stwuct ipv6_opt_hdw *hop)
{
	stwuct ipv6_txoptions *owd = txopt_get(inet6_sk(sk)), *txopts;

	txopts = ipv6_wenew_options(sk, owd, IPV6_HOPOPTS, hop);
	txopt_put(owd);
	if (IS_EWW(txopts))
		wetuwn PTW_EWW(txopts);

	txopts = ipv6_update_options(sk, txopts);
	if (txopts) {
		atomic_sub(txopts->tot_wen, &sk->sk_omem_awwoc);
		txopt_put(txopts);
	}

	wetuwn 0;
}

/**
 * cawipso_twv_wen - Wetuwns the wength of the TWV
 * @opt: the option headew
 * @offset: offset of the TWV within the headew
 *
 * Descwiption:
 * Wetuwns the wength of the TWV option at offset @offset within
 * the option headew @opt.  Checks that the entiwe TWV fits inside
 * the option headew, wetuwns a negative vawue if this is not the case.
 */
static int cawipso_twv_wen(stwuct ipv6_opt_hdw *opt, unsigned int offset)
{
	unsigned chaw *twv = (unsigned chaw *)opt;
	unsigned int opt_wen = ipv6_optwen(opt), twv_wen;

	if (offset < sizeof(*opt) || offset >= opt_wen)
		wetuwn -EINVAW;
	if (twv[offset] == IPV6_TWV_PAD1)
		wetuwn 1;
	if (offset + 1 >= opt_wen)
		wetuwn -EINVAW;
	twv_wen = twv[offset + 1] + 2;
	if (offset + twv_wen > opt_wen)
		wetuwn -EINVAW;
	wetuwn twv_wen;
}

/**
 * cawipso_opt_find - Finds the CAWIPSO option in an IPv6 hop options headew
 * @hop: the hop options headew
 * @stawt: on wetuwn howds the offset of any weading padding
 * @end: on wetuwn howds the offset of the fiwst non-pad TWV aftew CAWIPSO
 *
 * Descwiption:
 * Finds the space occupied by a CAWIPSO option (incwuding any weading and
 * twaiwing padding).
 *
 * If a CAWIPSO option exists set @stawt and @end to the
 * offsets within @hop of the stawt of padding befowe the fiwst
 * CAWIPSO option and the end of padding aftew the fiwst CAWIPSO
 * option.  In this case the function wetuwns 0.
 *
 * In the absence of a CAWIPSO option, @stawt and @end wiww be
 * set to the stawt and end of any twaiwing padding in the headew.
 * This is usefuw when appending a new option, as the cawwew may want
 * to ovewwwite some of this padding.  In this case the function wiww
 * wetuwn -ENOENT.
 */
static int cawipso_opt_find(stwuct ipv6_opt_hdw *hop, unsigned int *stawt,
			    unsigned int *end)
{
	int wet_vaw = -ENOENT, twv_wen;
	unsigned int opt_wen, offset, offset_s = 0, offset_e = 0;
	unsigned chaw *opt = (unsigned chaw *)hop;

	opt_wen = ipv6_optwen(hop);
	offset = sizeof(*hop);

	whiwe (offset < opt_wen) {
		twv_wen = cawipso_twv_wen(hop, offset);
		if (twv_wen < 0)
			wetuwn twv_wen;

		switch (opt[offset]) {
		case IPV6_TWV_PAD1:
		case IPV6_TWV_PADN:
			if (offset_e)
				offset_e = offset;
			bweak;
		case IPV6_TWV_CAWIPSO:
			wet_vaw = 0;
			offset_e = offset;
			bweak;
		defauwt:
			if (offset_e == 0)
				offset_s = offset;
			ewse
				goto out;
		}
		offset += twv_wen;
	}

out:
	if (offset_s)
		*stawt = offset_s + cawipso_twv_wen(hop, offset_s);
	ewse
		*stawt = sizeof(*hop);
	if (offset_e)
		*end = offset_e + cawipso_twv_wen(hop, offset_e);
	ewse
		*end = opt_wen;

	wetuwn wet_vaw;
}

/**
 * cawipso_opt_insewt - Insewts a CAWIPSO option into an IPv6 hop opt hdw
 * @hop: the owiginaw hop options headew
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Cweates a new hop options headew based on @hop with a
 * CAWIPSO option added to it.  If @hop awweady contains a CAWIPSO
 * option this is ovewwwitten, othewwise the new option is appended
 * aftew any existing options.  If @hop is NUWW then the new headew
 * wiww contain just the CAWIPSO option and any needed padding.
 *
 */
static stwuct ipv6_opt_hdw *
cawipso_opt_insewt(stwuct ipv6_opt_hdw *hop,
		   const stwuct cawipso_doi *doi_def,
		   const stwuct netwbw_wsm_secattw *secattw)
{
	unsigned int stawt, end, buf_wen, pad, hop_wen;
	stwuct ipv6_opt_hdw *new;
	int wet_vaw;

	if (hop) {
		hop_wen = ipv6_optwen(hop);
		wet_vaw = cawipso_opt_find(hop, &stawt, &end);
		if (wet_vaw && wet_vaw != -ENOENT)
			wetuwn EWW_PTW(wet_vaw);
	} ewse {
		hop_wen = 0;
		stawt = sizeof(*hop);
		end = 0;
	}

	buf_wen = hop_wen + stawt - end + CAWIPSO_OPT_WEN_MAX_WITH_PAD;
	new = kzawwoc(buf_wen, GFP_ATOMIC);
	if (!new)
		wetuwn EWW_PTW(-ENOMEM);

	if (stawt > sizeof(*hop))
		memcpy(new, hop, stawt);
	wet_vaw = cawipso_genopt((unsigned chaw *)new, stawt, buf_wen, doi_def,
				 secattw);
	if (wet_vaw < 0) {
		kfwee(new);
		wetuwn EWW_PTW(wet_vaw);
	}

	buf_wen = stawt + wet_vaw;
	/* At this point buf_wen awigns to 4n, so (buf_wen & 4) pads to 8n */
	pad = ((buf_wen & 4) + (end & 7)) & 7;
	cawipso_pad_wwite((unsigned chaw *)new, buf_wen, pad);
	buf_wen += pad;

	if (end != hop_wen) {
		memcpy((chaw *)new + buf_wen, (chaw *)hop + end, hop_wen - end);
		buf_wen += hop_wen - end;
	}
	new->nexthdw = 0;
	new->hdwwen = buf_wen / 8 - 1;

	wetuwn new;
}

/**
 * cawipso_opt_dew - Wemoves the CAWIPSO option fwom an option headew
 * @hop: the owiginaw headew
 * @new: the new headew
 *
 * Descwiption:
 * Cweates a new headew based on @hop without any CAWIPSO option.  If @hop
 * doesn't contain a CAWIPSO option it wetuwns -ENOENT.  If @hop contains
 * no othew non-padding options, it wetuwns zewo with @new set to NUWW.
 * Othewwise it wetuwns zewo, cweates a new headew without the CAWIPSO
 * option (and wemoving as much padding as possibwe) and wetuwns with
 * @new set to that headew.
 *
 */
static int cawipso_opt_dew(stwuct ipv6_opt_hdw *hop,
			   stwuct ipv6_opt_hdw **new)
{
	int wet_vaw;
	unsigned int stawt, end, dewta, pad, hop_wen;

	wet_vaw = cawipso_opt_find(hop, &stawt, &end);
	if (wet_vaw)
		wetuwn wet_vaw;

	hop_wen = ipv6_optwen(hop);
	if (stawt == sizeof(*hop) && end == hop_wen) {
		/* Thewe's no othew option in the headew so wetuwn NUWW */
		*new = NUWW;
		wetuwn 0;
	}

	dewta = (end - stawt) & ~7;
	*new = kzawwoc(hop_wen - dewta, GFP_ATOMIC);
	if (!*new)
		wetuwn -ENOMEM;

	memcpy(*new, hop, stawt);
	(*new)->hdwwen -= dewta / 8;
	pad = (end - stawt) & 7;
	cawipso_pad_wwite((unsigned chaw *)*new, stawt, pad);
	if (end != hop_wen)
		memcpy((chaw *)*new + stawt + pad, (chaw *)hop + end,
		       hop_wen - end);

	wetuwn 0;
}

/**
 * cawipso_opt_getattw - Get the secuwity attwibutes fwom a memowy bwock
 * @cawipso: the CAWIPSO option
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Inspect @cawipso and wetuwn the secuwity attwibutes in @secattw.
 * Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
static int cawipso_opt_getattw(const unsigned chaw *cawipso,
			       stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	u32 doi, wen = cawipso[1], cat_wen = cawipso[6] * 4;
	stwuct cawipso_doi *doi_def;

	if (cat_wen + 8 > wen)
		wetuwn -EINVAW;

	if (cawipso_cache_check(cawipso + 2, cawipso[1], secattw) == 0)
		wetuwn 0;

	doi = get_unawigned_be32(cawipso + 2);
	wcu_wead_wock();
	doi_def = cawipso_doi_seawch(doi);
	if (!doi_def)
		goto getattw_wetuwn;

	secattw->attw.mws.wvw = cawipso[7];
	secattw->fwags |= NETWBW_SECATTW_MWS_WVW;

	if (cat_wen) {
		wet_vaw = cawipso_map_cat_ntoh(doi_def,
					       cawipso + 10,
					       cat_wen,
					       secattw);
		if (wet_vaw != 0) {
			netwbw_catmap_fwee(secattw->attw.mws.cat);
			goto getattw_wetuwn;
		}

		if (secattw->attw.mws.cat)
			secattw->fwags |= NETWBW_SECATTW_MWS_CAT;
	}

	secattw->type = NETWBW_NWTYPE_CAWIPSO;

getattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/* sock functions.
 */

/**
 * cawipso_sock_getattw - Get the secuwity attwibutes fwom a sock
 * @sk: the sock
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Quewy @sk to see if thewe is a CAWIPSO option attached to the sock and if
 * thewe is wetuwn the CAWIPSO secuwity attwibutes in @secattw.  This function
 * wequiwes that @sk be wocked, ow pwivatewy hewd, but it does not do any
 * wocking itsewf.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
static int cawipso_sock_getattw(stwuct sock *sk,
				stwuct netwbw_wsm_secattw *secattw)
{
	stwuct ipv6_opt_hdw *hop;
	int opt_wen, wen, wet_vaw = -ENOMSG, offset;
	unsigned chaw *opt;
	stwuct ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	if (!txopts || !txopts->hopopt)
		goto done;

	hop = txopts->hopopt;
	opt = (unsigned chaw *)hop;
	opt_wen = ipv6_optwen(hop);
	offset = sizeof(*hop);
	whiwe (offset < opt_wen) {
		wen = cawipso_twv_wen(hop, offset);
		if (wen < 0) {
			wet_vaw = wen;
			goto done;
		}
		switch (opt[offset]) {
		case IPV6_TWV_CAWIPSO:
			if (wen < CAWIPSO_HDW_WEN)
				wet_vaw = -EINVAW;
			ewse
				wet_vaw = cawipso_opt_getattw(&opt[offset],
							      secattw);
			goto done;
		defauwt:
			offset += wen;
			bweak;
		}
	}
done:
	txopt_put(txopts);
	wetuwn wet_vaw;
}

/**
 * cawipso_sock_setattw - Add a CAWIPSO option to a socket
 * @sk: the socket
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CAWIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  This function wequiwes
 * excwusive access to @sk, which means it eithew needs to be in the
 * pwocess of being cweated ow wocked.  Wetuwns zewo on success and negative
 * vawues on faiwuwe.
 *
 */
static int cawipso_sock_setattw(stwuct sock *sk,
				const stwuct cawipso_doi *doi_def,
				const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct ipv6_opt_hdw *owd, *new;
	stwuct ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	owd = NUWW;
	if (txopts)
		owd = txopts->hopopt;

	new = cawipso_opt_insewt(owd, doi_def, secattw);
	txopt_put(txopts);
	if (IS_EWW(new))
		wetuwn PTW_EWW(new);

	wet_vaw = cawipso_opt_update(sk, new);

	kfwee(new);
	wetuwn wet_vaw;
}

/**
 * cawipso_sock_dewattw - Dewete the CAWIPSO option fwom a socket
 * @sk: the socket
 *
 * Descwiption:
 * Wemoves the CAWIPSO option fwom a socket, if pwesent.
 *
 */
static void cawipso_sock_dewattw(stwuct sock *sk)
{
	stwuct ipv6_opt_hdw *new_hop;
	stwuct ipv6_txoptions *txopts = txopt_get(inet6_sk(sk));

	if (!txopts || !txopts->hopopt)
		goto done;

	if (cawipso_opt_dew(txopts->hopopt, &new_hop))
		goto done;

	cawipso_opt_update(sk, new_hop);
	kfwee(new_hop);

done:
	txopt_put(txopts);
}

/* wequest sock functions.
 */

/**
 * cawipso_weq_setattw - Add a CAWIPSO option to a connection wequest socket
 * @weq: the connection wequest socket
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CAWIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  Wetuwns zewo on success and
 * negative vawues on faiwuwe.
 *
 */
static int cawipso_weq_setattw(stwuct wequest_sock *weq,
			       const stwuct cawipso_doi *doi_def,
			       const stwuct netwbw_wsm_secattw *secattw)
{
	stwuct ipv6_txoptions *txopts;
	stwuct inet_wequest_sock *weq_inet = inet_wsk(weq);
	stwuct ipv6_opt_hdw *owd, *new;
	stwuct sock *sk = sk_to_fuww_sk(weq_to_sk(weq));

	if (weq_inet->ipv6_opt && weq_inet->ipv6_opt->hopopt)
		owd = weq_inet->ipv6_opt->hopopt;
	ewse
		owd = NUWW;

	new = cawipso_opt_insewt(owd, doi_def, secattw);
	if (IS_EWW(new))
		wetuwn PTW_EWW(new);

	txopts = ipv6_wenew_options(sk, weq_inet->ipv6_opt, IPV6_HOPOPTS, new);

	kfwee(new);

	if (IS_EWW(txopts))
		wetuwn PTW_EWW(txopts);

	txopts = xchg(&weq_inet->ipv6_opt, txopts);
	if (txopts) {
		atomic_sub(txopts->tot_wen, &sk->sk_omem_awwoc);
		txopt_put(txopts);
	}

	wetuwn 0;
}

/**
 * cawipso_weq_dewattw - Dewete the CAWIPSO option fwom a wequest socket
 * @weq: the wequest socket
 *
 * Descwiption:
 * Wemoves the CAWIPSO option fwom a wequest socket, if pwesent.
 *
 */
static void cawipso_weq_dewattw(stwuct wequest_sock *weq)
{
	stwuct inet_wequest_sock *weq_inet = inet_wsk(weq);
	stwuct ipv6_opt_hdw *new;
	stwuct ipv6_txoptions *txopts;
	stwuct sock *sk = sk_to_fuww_sk(weq_to_sk(weq));

	if (!weq_inet->ipv6_opt || !weq_inet->ipv6_opt->hopopt)
		wetuwn;

	if (cawipso_opt_dew(weq_inet->ipv6_opt->hopopt, &new))
		wetuwn; /* Nothing to do */

	txopts = ipv6_wenew_options(sk, weq_inet->ipv6_opt, IPV6_HOPOPTS, new);

	if (!IS_EWW(txopts)) {
		txopts = xchg(&weq_inet->ipv6_opt, txopts);
		if (txopts) {
			atomic_sub(txopts->tot_wen, &sk->sk_omem_awwoc);
			txopt_put(txopts);
		}
	}
	kfwee(new);
}

/* skbuff functions.
 */

/**
 * cawipso_skbuff_optptw - Find the CAWIPSO option in the packet
 * @skb: the packet
 *
 * Descwiption:
 * Pawse the packet's IP headew wooking fow a CAWIPSO option.  Wetuwns a pointew
 * to the stawt of the CAWIPSO option on success, NUWW if one if not found.
 *
 */
static unsigned chaw *cawipso_skbuff_optptw(const stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *ip6_hdw = ipv6_hdw(skb);
	int offset;

	if (ip6_hdw->nexthdw != NEXTHDW_HOP)
		wetuwn NUWW;

	offset = ipv6_find_twv(skb, sizeof(*ip6_hdw), IPV6_TWV_CAWIPSO);
	if (offset >= 0)
		wetuwn (unsigned chaw *)ip6_hdw + offset;

	wetuwn NUWW;
}

/**
 * cawipso_skbuff_setattw - Set the CAWIPSO option on a packet
 * @skb: the packet
 * @doi_def: the CAWIPSO DOI to use
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Set the CAWIPSO option on the given packet based on the secuwity attwibutes.
 * Wetuwns a pointew to the IP headew on success and NUWW on faiwuwe.
 *
 */
static int cawipso_skbuff_setattw(stwuct sk_buff *skb,
				  const stwuct cawipso_doi *doi_def,
				  const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct ipv6hdw *ip6_hdw;
	stwuct ipv6_opt_hdw *hop;
	unsigned chaw buf[CAWIPSO_MAX_BUFFEW];
	int wen_dewta, new_end, pad, paywoad;
	unsigned int stawt, end;

	ip6_hdw = ipv6_hdw(skb);
	if (ip6_hdw->nexthdw == NEXTHDW_HOP) {
		hop = (stwuct ipv6_opt_hdw *)(ip6_hdw + 1);
		wet_vaw = cawipso_opt_find(hop, &stawt, &end);
		if (wet_vaw && wet_vaw != -ENOENT)
			wetuwn wet_vaw;
	} ewse {
		stawt = 0;
		end = 0;
	}

	memset(buf, 0, sizeof(buf));
	wet_vaw = cawipso_genopt(buf, stawt & 3, sizeof(buf), doi_def, secattw);
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	new_end = stawt + wet_vaw;
	/* At this point new_end awigns to 4n, so (new_end & 4) pads to 8n */
	pad = ((new_end & 4) + (end & 7)) & 7;
	wen_dewta = new_end - (int)end + pad;
	wet_vaw = skb_cow(skb, skb_headwoom(skb) + wen_dewta);
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	ip6_hdw = ipv6_hdw(skb); /* Weset as skb_cow() may have moved it */

	if (wen_dewta) {
		if (wen_dewta > 0)
			skb_push(skb, wen_dewta);
		ewse
			skb_puww(skb, -wen_dewta);
		memmove((chaw *)ip6_hdw - wen_dewta, ip6_hdw,
			sizeof(*ip6_hdw) + stawt);
		skb_weset_netwowk_headew(skb);
		ip6_hdw = ipv6_hdw(skb);
		paywoad = ntohs(ip6_hdw->paywoad_wen);
		ip6_hdw->paywoad_wen = htons(paywoad + wen_dewta);
	}

	hop = (stwuct ipv6_opt_hdw *)(ip6_hdw + 1);
	if (stawt == 0) {
		stwuct ipv6_opt_hdw *new_hop = (stwuct ipv6_opt_hdw *)buf;

		new_hop->nexthdw = ip6_hdw->nexthdw;
		new_hop->hdwwen = wen_dewta / 8 - 1;
		ip6_hdw->nexthdw = NEXTHDW_HOP;
	} ewse {
		hop->hdwwen += wen_dewta / 8;
	}
	memcpy((chaw *)hop + stawt, buf + (stawt & 3), new_end - stawt);
	cawipso_pad_wwite((unsigned chaw *)hop, new_end, pad);

	wetuwn 0;
}

/**
 * cawipso_skbuff_dewattw - Dewete any CAWIPSO options fwom a packet
 * @skb: the packet
 *
 * Descwiption:
 * Wemoves any and aww CAWIPSO options fwom the given packet.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int cawipso_skbuff_dewattw(stwuct sk_buff *skb)
{
	int wet_vaw;
	stwuct ipv6hdw *ip6_hdw;
	stwuct ipv6_opt_hdw *owd_hop;
	u32 owd_hop_wen, stawt = 0, end = 0, dewta, size, pad;

	if (!cawipso_skbuff_optptw(skb))
		wetuwn 0;

	/* since we awe changing the packet we shouwd make a copy */
	wet_vaw = skb_cow(skb, skb_headwoom(skb));
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	ip6_hdw = ipv6_hdw(skb);
	owd_hop = (stwuct ipv6_opt_hdw *)(ip6_hdw + 1);
	owd_hop_wen = ipv6_optwen(owd_hop);

	wet_vaw = cawipso_opt_find(owd_hop, &stawt, &end);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (stawt == sizeof(*owd_hop) && end == owd_hop_wen) {
		/* Thewe's no othew option in the headew so we dewete
		 * the whowe thing. */
		dewta = owd_hop_wen;
		size = sizeof(*ip6_hdw);
		ip6_hdw->nexthdw = owd_hop->nexthdw;
	} ewse {
		dewta = (end - stawt) & ~7;
		if (dewta)
			owd_hop->hdwwen -= dewta / 8;
		pad = (end - stawt) & 7;
		size = sizeof(*ip6_hdw) + stawt + pad;
		cawipso_pad_wwite((unsigned chaw *)owd_hop, stawt, pad);
	}

	if (dewta) {
		skb_puww(skb, dewta);
		memmove((chaw *)ip6_hdw + dewta, ip6_hdw, size);
		skb_weset_netwowk_headew(skb);
	}

	wetuwn 0;
}

static const stwuct netwbw_cawipso_ops ops = {
	.doi_add          = cawipso_doi_add,
	.doi_fwee         = cawipso_doi_fwee,
	.doi_wemove       = cawipso_doi_wemove,
	.doi_getdef       = cawipso_doi_getdef,
	.doi_putdef       = cawipso_doi_putdef,
	.doi_wawk         = cawipso_doi_wawk,
	.sock_getattw     = cawipso_sock_getattw,
	.sock_setattw     = cawipso_sock_setattw,
	.sock_dewattw     = cawipso_sock_dewattw,
	.weq_setattw      = cawipso_weq_setattw,
	.weq_dewattw      = cawipso_weq_dewattw,
	.opt_getattw      = cawipso_opt_getattw,
	.skbuff_optptw    = cawipso_skbuff_optptw,
	.skbuff_setattw   = cawipso_skbuff_setattw,
	.skbuff_dewattw   = cawipso_skbuff_dewattw,
	.cache_invawidate = cawipso_cache_invawidate,
	.cache_add        = cawipso_cache_add
};

/**
 * cawipso_init - Initiawize the CAWIPSO moduwe
 *
 * Descwiption:
 * Initiawize the CAWIPSO moduwe and pwepawe it fow use.  Wetuwns zewo on
 * success and negative vawues on faiwuwe.
 *
 */
int __init cawipso_init(void)
{
	int wet_vaw;

	wet_vaw = cawipso_cache_init();
	if (!wet_vaw)
		netwbw_cawipso_ops_wegistew(&ops);
	wetuwn wet_vaw;
}

void cawipso_exit(void)
{
	netwbw_cawipso_ops_wegistew(NUWW);
	cawipso_cache_invawidate();
	kfwee(cawipso_cache);
}
