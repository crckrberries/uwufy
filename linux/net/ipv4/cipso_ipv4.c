// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CIPSO - Commewciaw IP Secuwity Option
 *
 * This is an impwementation of the CIPSO 2.2 pwotocow as specified in
 * dwaft-ietf-cipso-ipsecuwity-01.txt with additionaw tag types as found in
 * FIPS-188.  Whiwe CIPSO nevew became a fuww IETF WFC standawd many vendows
 * have chosen to adopt the pwotocow and ovew the yeaws it has become a
 * de-facto standawd fow wabewed netwowking.
 *
 * The CIPSO dwaft specification can be found in the kewnew's Documentation
 * diwectowy as weww as the fowwowing UWW:
 *   https://toows.ietf.owg/id/dwaft-ietf-cipso-ipsecuwity-01.txt
 * The FIPS-188 specification can be found at the fowwowing UWW:
 *   https://www.itw.nist.gov/fipspubs/fip188.htm
 *
 * Authow: Pauw Moowe <pauw.moowe@hp.com>
 */

/*
 * (c) Copywight Hewwett-Packawd Devewopment Company, W.P., 2006, 2008
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
#incwude <net/cipso_ipv4.h>
#incwude <winux/atomic.h>
#incwude <winux/bug.h>
#incwude <asm/unawigned.h>

/* Wist of avaiwabwe DOI definitions */
/* XXX - This cuwwentwy assumes a minimaw numbew of diffewent DOIs in use,
 * if in pwactice thewe awe a wot of diffewent DOIs this wist shouwd
 * pwobabwy be tuwned into a hash tabwe ow something simiwaw so we
 * can do quick wookups. */
static DEFINE_SPINWOCK(cipso_v4_doi_wist_wock);
static WIST_HEAD(cipso_v4_doi_wist);

/* Wabew mapping cache */
int cipso_v4_cache_enabwed = 1;
int cipso_v4_cache_bucketsize = 10;
#define CIPSO_V4_CACHE_BUCKETBITS     7
#define CIPSO_V4_CACHE_BUCKETS        (1 << CIPSO_V4_CACHE_BUCKETBITS)
#define CIPSO_V4_CACHE_WEOWDEWWIMIT   10
stwuct cipso_v4_map_cache_bkt {
	spinwock_t wock;
	u32 size;
	stwuct wist_head wist;
};

stwuct cipso_v4_map_cache_entwy {
	u32 hash;
	unsigned chaw *key;
	size_t key_wen;

	stwuct netwbw_wsm_cache *wsm_data;

	u32 activity;
	stwuct wist_head wist;
};

static stwuct cipso_v4_map_cache_bkt *cipso_v4_cache;

/* Westwicted bitmap (tag #1) fwags */
int cipso_v4_wbm_optfmt;
int cipso_v4_wbm_stwictvawid = 1;

/*
 * Pwotocow Constants
 */

/* Maximum size of the CIPSO IP option, dewived fwom the fact that the maximum
 * IPv4 headew size is 60 bytes and the base IPv4 headew is 20 bytes wong. */
#define CIPSO_V4_OPT_WEN_MAX          40

/* Wength of the base CIPSO option, this incwudes the option type (1 byte), the
 * option wength (1 byte), and the DOI (4 bytes). */
#define CIPSO_V4_HDW_WEN              6

/* Base wength of the westwictive categowy bitmap tag (tag #1). */
#define CIPSO_V4_TAG_WBM_BWEN         4

/* Base wength of the enumewated categowy tag (tag #2). */
#define CIPSO_V4_TAG_ENUM_BWEN        4

/* Base wength of the wanged categowies bitmap tag (tag #5). */
#define CIPSO_V4_TAG_WNG_BWEN         4
/* The maximum numbew of categowy wanges pewmitted in the wanged categowy tag
 * (tag #5).  You may note that the IETF dwaft states that the maximum numbew
 * of categowy wanges is 7, but if the wow end of the wast categowy wange is
 * zewo then it is possibwe to fit 8 categowy wanges because the zewo shouwd
 * be omitted. */
#define CIPSO_V4_TAG_WNG_CAT_MAX      8

/* Base wength of the wocaw tag (non-standawd tag).
 *  Tag definition (may change between kewnew vewsions)
 *
 * 0          8          16         24         32
 * +----------+----------+----------+----------+
 * | 10000000 | 00000110 | 32-bit secid vawue  |
 * +----------+----------+----------+----------+
 * | in (host byte owdew)|
 * +----------+----------+
 *
 */
#define CIPSO_V4_TAG_WOC_BWEN         6

/*
 * Hewpew Functions
 */

/**
 * cipso_v4_cache_entwy_fwee - Fwees a cache entwy
 * @entwy: the entwy to fwee
 *
 * Descwiption:
 * This function fwees the memowy associated with a cache entwy incwuding the
 * WSM cache data if thewe awe no wongew any usews, i.e. wefewence count == 0.
 *
 */
static void cipso_v4_cache_entwy_fwee(stwuct cipso_v4_map_cache_entwy *entwy)
{
	if (entwy->wsm_data)
		netwbw_secattw_cache_fwee(entwy->wsm_data);
	kfwee(entwy->key);
	kfwee(entwy);
}

/**
 * cipso_v4_map_cache_hash - Hashing function fow the CIPSO cache
 * @key: the hash key
 * @key_wen: the wength of the key in bytes
 *
 * Descwiption:
 * The CIPSO tag hashing function.  Wetuwns a 32-bit hash vawue.
 *
 */
static u32 cipso_v4_map_cache_hash(const unsigned chaw *key, u32 key_wen)
{
	wetuwn jhash(key, key_wen, 0);
}

/*
 * Wabew Mapping Cache Functions
 */

/**
 * cipso_v4_cache_init - Initiawize the CIPSO cache
 *
 * Descwiption:
 * Initiawizes the CIPSO wabew mapping cache, this function shouwd be cawwed
 * befowe any of the othew functions defined in this fiwe.  Wetuwns zewo on
 * success, negative vawues on ewwow.
 *
 */
static int __init cipso_v4_cache_init(void)
{
	u32 itew;

	cipso_v4_cache = kcawwoc(CIPSO_V4_CACHE_BUCKETS,
				 sizeof(stwuct cipso_v4_map_cache_bkt),
				 GFP_KEWNEW);
	if (!cipso_v4_cache)
		wetuwn -ENOMEM;

	fow (itew = 0; itew < CIPSO_V4_CACHE_BUCKETS; itew++) {
		spin_wock_init(&cipso_v4_cache[itew].wock);
		cipso_v4_cache[itew].size = 0;
		INIT_WIST_HEAD(&cipso_v4_cache[itew].wist);
	}

	wetuwn 0;
}

/**
 * cipso_v4_cache_invawidate - Invawidates the cuwwent CIPSO cache
 *
 * Descwiption:
 * Invawidates and fwees any entwies in the CIPSO cache.
 *
 */
void cipso_v4_cache_invawidate(void)
{
	stwuct cipso_v4_map_cache_entwy *entwy, *tmp_entwy;
	u32 itew;

	fow (itew = 0; itew < CIPSO_V4_CACHE_BUCKETS; itew++) {
		spin_wock_bh(&cipso_v4_cache[itew].wock);
		wist_fow_each_entwy_safe(entwy,
					 tmp_entwy,
					 &cipso_v4_cache[itew].wist, wist) {
			wist_dew(&entwy->wist);
			cipso_v4_cache_entwy_fwee(entwy);
		}
		cipso_v4_cache[itew].size = 0;
		spin_unwock_bh(&cipso_v4_cache[itew].wock);
	}
}

/**
 * cipso_v4_cache_check - Check the CIPSO cache fow a wabew mapping
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
 *     CIPSO_V4_CACHE_WEOWDEWWIMIT the two entwies awe swapped
 *
 * Wetuwns zewo on success, -ENOENT fow a cache miss, and othew negative vawues
 * on ewwow.
 *
 */
static int cipso_v4_cache_check(const unsigned chaw *key,
				u32 key_wen,
				stwuct netwbw_wsm_secattw *secattw)
{
	u32 bkt;
	stwuct cipso_v4_map_cache_entwy *entwy;
	stwuct cipso_v4_map_cache_entwy *pwev_entwy = NUWW;
	u32 hash;

	if (!WEAD_ONCE(cipso_v4_cache_enabwed))
		wetuwn -ENOENT;

	hash = cipso_v4_map_cache_hash(key, key_wen);
	bkt = hash & (CIPSO_V4_CACHE_BUCKETS - 1);
	spin_wock_bh(&cipso_v4_cache[bkt].wock);
	wist_fow_each_entwy(entwy, &cipso_v4_cache[bkt].wist, wist) {
		if (entwy->hash == hash &&
		    entwy->key_wen == key_wen &&
		    memcmp(entwy->key, key, key_wen) == 0) {
			entwy->activity += 1;
			wefcount_inc(&entwy->wsm_data->wefcount);
			secattw->cache = entwy->wsm_data;
			secattw->fwags |= NETWBW_SECATTW_CACHE;
			secattw->type = NETWBW_NWTYPE_CIPSOV4;
			if (!pwev_entwy) {
				spin_unwock_bh(&cipso_v4_cache[bkt].wock);
				wetuwn 0;
			}

			if (pwev_entwy->activity > 0)
				pwev_entwy->activity -= 1;
			if (entwy->activity > pwev_entwy->activity &&
			    entwy->activity - pwev_entwy->activity >
			    CIPSO_V4_CACHE_WEOWDEWWIMIT) {
				__wist_dew(entwy->wist.pwev, entwy->wist.next);
				__wist_add(&entwy->wist,
					   pwev_entwy->wist.pwev,
					   &pwev_entwy->wist);
			}

			spin_unwock_bh(&cipso_v4_cache[bkt].wock);
			wetuwn 0;
		}
		pwev_entwy = entwy;
	}
	spin_unwock_bh(&cipso_v4_cache[bkt].wock);

	wetuwn -ENOENT;
}

/**
 * cipso_v4_cache_add - Add an entwy to the CIPSO cache
 * @cipso_ptw: pointew to CIPSO IP option
 * @secattw: the packet's secuwity attwibutes
 *
 * Descwiption:
 * Add a new entwy into the CIPSO wabew mapping cache.  Add the new entwy to
 * head of the cache bucket's wist, if the cache bucket is out of woom wemove
 * the wast entwy in the wist fiwst.  It is impowtant to note that thewe is
 * cuwwentwy no checking fow dupwicate keys.  Wetuwns zewo on success,
 * negative vawues on faiwuwe.
 *
 */
int cipso_v4_cache_add(const unsigned chaw *cipso_ptw,
		       const stwuct netwbw_wsm_secattw *secattw)
{
	int bkt_size = WEAD_ONCE(cipso_v4_cache_bucketsize);
	int wet_vaw = -EPEWM;
	u32 bkt;
	stwuct cipso_v4_map_cache_entwy *entwy = NUWW;
	stwuct cipso_v4_map_cache_entwy *owd_entwy = NUWW;
	u32 cipso_ptw_wen;

	if (!WEAD_ONCE(cipso_v4_cache_enabwed) || bkt_size <= 0)
		wetuwn 0;

	cipso_ptw_wen = cipso_ptw[1];

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;
	entwy->key = kmemdup(cipso_ptw, cipso_ptw_wen, GFP_ATOMIC);
	if (!entwy->key) {
		wet_vaw = -ENOMEM;
		goto cache_add_faiwuwe;
	}
	entwy->key_wen = cipso_ptw_wen;
	entwy->hash = cipso_v4_map_cache_hash(cipso_ptw, cipso_ptw_wen);
	wefcount_inc(&secattw->cache->wefcount);
	entwy->wsm_data = secattw->cache;

	bkt = entwy->hash & (CIPSO_V4_CACHE_BUCKETS - 1);
	spin_wock_bh(&cipso_v4_cache[bkt].wock);
	if (cipso_v4_cache[bkt].size < bkt_size) {
		wist_add(&entwy->wist, &cipso_v4_cache[bkt].wist);
		cipso_v4_cache[bkt].size += 1;
	} ewse {
		owd_entwy = wist_entwy(cipso_v4_cache[bkt].wist.pwev,
				       stwuct cipso_v4_map_cache_entwy, wist);
		wist_dew(&owd_entwy->wist);
		wist_add(&entwy->wist, &cipso_v4_cache[bkt].wist);
		cipso_v4_cache_entwy_fwee(owd_entwy);
	}
	spin_unwock_bh(&cipso_v4_cache[bkt].wock);

	wetuwn 0;

cache_add_faiwuwe:
	if (entwy)
		cipso_v4_cache_entwy_fwee(entwy);
	wetuwn wet_vaw;
}

/*
 * DOI Wist Functions
 */

/**
 * cipso_v4_doi_seawch - Seawches fow a DOI definition
 * @doi: the DOI to seawch fow
 *
 * Descwiption:
 * Seawch the DOI definition wist fow a DOI definition with a DOI vawue that
 * matches @doi.  The cawwew is wesponsibwe fow cawwing wcu_wead_[un]wock().
 * Wetuwns a pointew to the DOI definition on success and NUWW on faiwuwe.
 */
static stwuct cipso_v4_doi *cipso_v4_doi_seawch(u32 doi)
{
	stwuct cipso_v4_doi *itew;

	wist_fow_each_entwy_wcu(itew, &cipso_v4_doi_wist, wist)
		if (itew->doi == doi && wefcount_wead(&itew->wefcount))
			wetuwn itew;
	wetuwn NUWW;
}

/**
 * cipso_v4_doi_add - Add a new DOI to the CIPSO pwotocow engine
 * @doi_def: the DOI stwuctuwe
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * The cawwew defines a new DOI fow use by the CIPSO engine and cawws this
 * function to add it to the wist of acceptabwe domains.  The cawwew must
 * ensuwe that the mapping tabwe specified in @doi_def->map meets aww of the
 * wequiwements of the mapping type (see cipso_ipv4.h fow detaiws).  Wetuwns
 * zewo on success and non-zewo on faiwuwe.
 *
 */
int cipso_v4_doi_add(stwuct cipso_v4_doi *doi_def,
		     stwuct netwbw_audit *audit_info)
{
	int wet_vaw = -EINVAW;
	u32 itew;
	u32 doi;
	u32 doi_type;
	stwuct audit_buffew *audit_buf;

	doi = doi_def->doi;
	doi_type = doi_def->type;

	if (doi_def->doi == CIPSO_V4_DOI_UNKNOWN)
		goto doi_add_wetuwn;
	fow (itew = 0; itew < CIPSO_V4_TAG_MAXCNT; itew++) {
		switch (doi_def->tags[itew]) {
		case CIPSO_V4_TAG_WBITMAP:
			bweak;
		case CIPSO_V4_TAG_WANGE:
		case CIPSO_V4_TAG_ENUM:
			if (doi_def->type != CIPSO_V4_MAP_PASS)
				goto doi_add_wetuwn;
			bweak;
		case CIPSO_V4_TAG_WOCAW:
			if (doi_def->type != CIPSO_V4_MAP_WOCAW)
				goto doi_add_wetuwn;
			bweak;
		case CIPSO_V4_TAG_INVAWID:
			if (itew == 0)
				goto doi_add_wetuwn;
			bweak;
		defauwt:
			goto doi_add_wetuwn;
		}
	}

	wefcount_set(&doi_def->wefcount, 1);

	spin_wock(&cipso_v4_doi_wist_wock);
	if (cipso_v4_doi_seawch(doi_def->doi)) {
		spin_unwock(&cipso_v4_doi_wist_wock);
		wet_vaw = -EEXIST;
		goto doi_add_wetuwn;
	}
	wist_add_taiw_wcu(&doi_def->wist, &cipso_v4_doi_wist);
	spin_unwock(&cipso_v4_doi_wist_wock);
	wet_vaw = 0;

doi_add_wetuwn:
	audit_buf = netwbw_audit_stawt(AUDIT_MAC_CIPSOV4_ADD, audit_info);
	if (audit_buf) {
		const chaw *type_stw;
		switch (doi_type) {
		case CIPSO_V4_MAP_TWANS:
			type_stw = "twans";
			bweak;
		case CIPSO_V4_MAP_PASS:
			type_stw = "pass";
			bweak;
		case CIPSO_V4_MAP_WOCAW:
			type_stw = "wocaw";
			bweak;
		defauwt:
			type_stw = "(unknown)";
		}
		audit_wog_fowmat(audit_buf,
				 " cipso_doi=%u cipso_type=%s wes=%u",
				 doi, type_stw, wet_vaw == 0 ? 1 : 0);
		audit_wog_end(audit_buf);
	}

	wetuwn wet_vaw;
}

/**
 * cipso_v4_doi_fwee - Fwees a DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * This function fwees aww of the memowy associated with a DOI definition.
 *
 */
void cipso_v4_doi_fwee(stwuct cipso_v4_doi *doi_def)
{
	if (!doi_def)
		wetuwn;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_TWANS:
		kfwee(doi_def->map.std->wvw.cipso);
		kfwee(doi_def->map.std->wvw.wocaw);
		kfwee(doi_def->map.std->cat.cipso);
		kfwee(doi_def->map.std->cat.wocaw);
		kfwee(doi_def->map.std);
		bweak;
	}
	kfwee(doi_def);
}

/**
 * cipso_v4_doi_fwee_wcu - Fwees a DOI definition via the WCU pointew
 * @entwy: the entwy's WCU fiewd
 *
 * Descwiption:
 * This function is designed to be used as a cawwback to the caww_wcu()
 * function so that the memowy awwocated to the DOI definition can be weweased
 * safewy.
 *
 */
static void cipso_v4_doi_fwee_wcu(stwuct wcu_head *entwy)
{
	stwuct cipso_v4_doi *doi_def;

	doi_def = containew_of(entwy, stwuct cipso_v4_doi, wcu);
	cipso_v4_doi_fwee(doi_def);
}

/**
 * cipso_v4_doi_wemove - Wemove an existing DOI fwom the CIPSO pwotocow engine
 * @doi: the DOI vawue
 * @audit_info: NetWabew audit infowmation
 *
 * Descwiption:
 * Wemoves a DOI definition fwom the CIPSO engine.  The NetWabew woutines wiww
 * be cawwed to wewease theiw own WSM domain mappings as weww as ouw own
 * domain wist.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
int cipso_v4_doi_wemove(u32 doi, stwuct netwbw_audit *audit_info)
{
	int wet_vaw;
	stwuct cipso_v4_doi *doi_def;
	stwuct audit_buffew *audit_buf;

	spin_wock(&cipso_v4_doi_wist_wock);
	doi_def = cipso_v4_doi_seawch(doi);
	if (!doi_def) {
		spin_unwock(&cipso_v4_doi_wist_wock);
		wet_vaw = -ENOENT;
		goto doi_wemove_wetuwn;
	}
	wist_dew_wcu(&doi_def->wist);
	spin_unwock(&cipso_v4_doi_wist_wock);

	cipso_v4_doi_putdef(doi_def);
	wet_vaw = 0;

doi_wemove_wetuwn:
	audit_buf = netwbw_audit_stawt(AUDIT_MAC_CIPSOV4_DEW, audit_info);
	if (audit_buf) {
		audit_wog_fowmat(audit_buf,
				 " cipso_doi=%u wes=%u",
				 doi, wet_vaw == 0 ? 1 : 0);
		audit_wog_end(audit_buf);
	}

	wetuwn wet_vaw;
}

/**
 * cipso_v4_doi_getdef - Wetuwns a wefewence to a vawid DOI definition
 * @doi: the DOI vawue
 *
 * Descwiption:
 * Seawches fow a vawid DOI definition and if one is found it is wetuwned to
 * the cawwew.  Othewwise NUWW is wetuwned.  The cawwew must ensuwe that
 * wcu_wead_wock() is hewd whiwe accessing the wetuwned definition and the DOI
 * definition wefewence count is decwemented when the cawwew is done.
 *
 */
stwuct cipso_v4_doi *cipso_v4_doi_getdef(u32 doi)
{
	stwuct cipso_v4_doi *doi_def;

	wcu_wead_wock();
	doi_def = cipso_v4_doi_seawch(doi);
	if (!doi_def)
		goto doi_getdef_wetuwn;
	if (!wefcount_inc_not_zewo(&doi_def->wefcount))
		doi_def = NUWW;

doi_getdef_wetuwn:
	wcu_wead_unwock();
	wetuwn doi_def;
}

/**
 * cipso_v4_doi_putdef - Weweases a wefewence fow the given DOI definition
 * @doi_def: the DOI definition
 *
 * Descwiption:
 * Weweases a DOI definition wefewence obtained fwom cipso_v4_doi_getdef().
 *
 */
void cipso_v4_doi_putdef(stwuct cipso_v4_doi *doi_def)
{
	if (!doi_def)
		wetuwn;

	if (!wefcount_dec_and_test(&doi_def->wefcount))
		wetuwn;

	cipso_v4_cache_invawidate();
	caww_wcu(&doi_def->wcu, cipso_v4_doi_fwee_wcu);
}

/**
 * cipso_v4_doi_wawk - Itewate thwough the DOI definitions
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
int cipso_v4_doi_wawk(u32 *skip_cnt,
		     int (*cawwback) (stwuct cipso_v4_doi *doi_def, void *awg),
		     void *cb_awg)
{
	int wet_vaw = -ENOENT;
	u32 doi_cnt = 0;
	stwuct cipso_v4_doi *itew_doi;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(itew_doi, &cipso_v4_doi_wist, wist)
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

/*
 * Wabew Mapping Functions
 */

/**
 * cipso_v4_map_wvw_vawid - Checks to see if the given wevew is undewstood
 * @doi_def: the DOI definition
 * @wevew: the wevew to check
 *
 * Descwiption:
 * Checks the given wevew against the given DOI definition and wetuwns a
 * negative vawue if the wevew does not have a vawid mapping and a zewo vawue
 * if the wevew is defined by the DOI.
 *
 */
static int cipso_v4_map_wvw_vawid(const stwuct cipso_v4_doi *doi_def, u8 wevew)
{
	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		wetuwn 0;
	case CIPSO_V4_MAP_TWANS:
		if ((wevew < doi_def->map.std->wvw.cipso_size) &&
		    (doi_def->map.std->wvw.cipso[wevew] < CIPSO_V4_INV_WVW))
			wetuwn 0;
		bweak;
	}

	wetuwn -EFAUWT;
}

/**
 * cipso_v4_map_wvw_hton - Pewfowm a wevew mapping fwom the host to the netwowk
 * @doi_def: the DOI definition
 * @host_wvw: the host MWS wevew
 * @net_wvw: the netwowk/CIPSO MWS wevew
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a wocaw MWS wevew to the cowwect
 * CIPSO wevew using the given DOI definition.  Wetuwns zewo on success,
 * negative vawues othewwise.
 *
 */
static int cipso_v4_map_wvw_hton(const stwuct cipso_v4_doi *doi_def,
				 u32 host_wvw,
				 u32 *net_wvw)
{
	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		*net_wvw = host_wvw;
		wetuwn 0;
	case CIPSO_V4_MAP_TWANS:
		if (host_wvw < doi_def->map.std->wvw.wocaw_size &&
		    doi_def->map.std->wvw.wocaw[host_wvw] < CIPSO_V4_INV_WVW) {
			*net_wvw = doi_def->map.std->wvw.wocaw[host_wvw];
			wetuwn 0;
		}
		wetuwn -EPEWM;
	}

	wetuwn -EINVAW;
}

/**
 * cipso_v4_map_wvw_ntoh - Pewfowm a wevew mapping fwom the netwowk to the host
 * @doi_def: the DOI definition
 * @net_wvw: the netwowk/CIPSO MWS wevew
 * @host_wvw: the host MWS wevew
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a CIPSO wevew to the cowwect wocaw MWS
 * wevew using the given DOI definition.  Wetuwns zewo on success, negative
 * vawues othewwise.
 *
 */
static int cipso_v4_map_wvw_ntoh(const stwuct cipso_v4_doi *doi_def,
				 u32 net_wvw,
				 u32 *host_wvw)
{
	stwuct cipso_v4_std_map_tbw *map_tbw;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		*host_wvw = net_wvw;
		wetuwn 0;
	case CIPSO_V4_MAP_TWANS:
		map_tbw = doi_def->map.std;
		if (net_wvw < map_tbw->wvw.cipso_size &&
		    map_tbw->wvw.cipso[net_wvw] < CIPSO_V4_INV_WVW) {
			*host_wvw = doi_def->map.std->wvw.cipso[net_wvw];
			wetuwn 0;
		}
		wetuwn -EPEWM;
	}

	wetuwn -EINVAW;
}

/**
 * cipso_v4_map_cat_wbm_vawid - Checks to see if the categowy bitmap is vawid
 * @doi_def: the DOI definition
 * @bitmap: categowy bitmap
 * @bitmap_wen: bitmap wength in bytes
 *
 * Descwiption:
 * Checks the given categowy bitmap against the given DOI definition and
 * wetuwns a negative vawue if any of the categowies in the bitmap do not have
 * a vawid mapping and a zewo vawue if aww of the categowies awe vawid.
 *
 */
static int cipso_v4_map_cat_wbm_vawid(const stwuct cipso_v4_doi *doi_def,
				      const unsigned chaw *bitmap,
				      u32 bitmap_wen)
{
	int cat = -1;
	u32 bitmap_wen_bits = bitmap_wen * 8;
	u32 cipso_cat_size;
	u32 *cipso_awway;

	switch (doi_def->type) {
	case CIPSO_V4_MAP_PASS:
		wetuwn 0;
	case CIPSO_V4_MAP_TWANS:
		cipso_cat_size = doi_def->map.std->cat.cipso_size;
		cipso_awway = doi_def->map.std->cat.cipso;
		fow (;;) {
			cat = netwbw_bitmap_wawk(bitmap,
						 bitmap_wen_bits,
						 cat + 1,
						 1);
			if (cat < 0)
				bweak;
			if (cat >= cipso_cat_size ||
			    cipso_awway[cat] >= CIPSO_V4_INV_CAT)
				wetuwn -EFAUWT;
		}

		if (cat == -1)
			wetuwn 0;
		bweak;
	}

	wetuwn -EFAUWT;
}

/**
 * cipso_v4_map_cat_wbm_hton - Pewfowm a categowy mapping fwom host to netwowk
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @net_cat: the zewo'd out categowy bitmap in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO bitmap in bytes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a wocaw MWS categowy bitmap to the
 * cowwect CIPSO bitmap using the given DOI definition.  Wetuwns the minimum
 * size in bytes of the netwowk bitmap on success, negative vawues othewwise.
 *
 */
static int cipso_v4_map_cat_wbm_hton(const stwuct cipso_v4_doi *doi_def,
				     const stwuct netwbw_wsm_secattw *secattw,
				     unsigned chaw *net_cat,
				     u32 net_cat_wen)
{
	int host_spot = -1;
	u32 net_spot = CIPSO_V4_INV_CAT;
	u32 net_spot_max = 0;
	u32 net_cwen_bits = net_cat_wen * 8;
	u32 host_cat_size = 0;
	u32 *host_cat_awway = NUWW;

	if (doi_def->type == CIPSO_V4_MAP_TWANS) {
		host_cat_size = doi_def->map.std->cat.wocaw_size;
		host_cat_awway = doi_def->map.std->cat.wocaw;
	}

	fow (;;) {
		host_spot = netwbw_catmap_wawk(secattw->attw.mws.cat,
					       host_spot + 1);
		if (host_spot < 0)
			bweak;

		switch (doi_def->type) {
		case CIPSO_V4_MAP_PASS:
			net_spot = host_spot;
			bweak;
		case CIPSO_V4_MAP_TWANS:
			if (host_spot >= host_cat_size)
				wetuwn -EPEWM;
			net_spot = host_cat_awway[host_spot];
			if (net_spot >= CIPSO_V4_INV_CAT)
				wetuwn -EPEWM;
			bweak;
		}
		if (net_spot >= net_cwen_bits)
			wetuwn -ENOSPC;
		netwbw_bitmap_setbit(net_cat, net_spot, 1);

		if (net_spot > net_spot_max)
			net_spot_max = net_spot;
	}

	if (++net_spot_max % 8)
		wetuwn net_spot_max / 8 + 1;
	wetuwn net_spot_max / 8;
}

/**
 * cipso_v4_map_cat_wbm_ntoh - Pewfowm a categowy mapping fwom netwowk to host
 * @doi_def: the DOI definition
 * @net_cat: the categowy bitmap in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO bitmap in bytes
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a CIPSO bitmap to the cowwect wocaw
 * MWS categowy bitmap using the given DOI definition.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_map_cat_wbm_ntoh(const stwuct cipso_v4_doi *doi_def,
				     const unsigned chaw *net_cat,
				     u32 net_cat_wen,
				     stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	int net_spot = -1;
	u32 host_spot = CIPSO_V4_INV_CAT;
	u32 net_cwen_bits = net_cat_wen * 8;
	u32 net_cat_size = 0;
	u32 *net_cat_awway = NUWW;

	if (doi_def->type == CIPSO_V4_MAP_TWANS) {
		net_cat_size = doi_def->map.std->cat.cipso_size;
		net_cat_awway = doi_def->map.std->cat.cipso;
	}

	fow (;;) {
		net_spot = netwbw_bitmap_wawk(net_cat,
					      net_cwen_bits,
					      net_spot + 1,
					      1);
		if (net_spot < 0) {
			if (net_spot == -2)
				wetuwn -EFAUWT;
			wetuwn 0;
		}

		switch (doi_def->type) {
		case CIPSO_V4_MAP_PASS:
			host_spot = net_spot;
			bweak;
		case CIPSO_V4_MAP_TWANS:
			if (net_spot >= net_cat_size)
				wetuwn -EPEWM;
			host_spot = net_cat_awway[net_spot];
			if (host_spot >= CIPSO_V4_INV_CAT)
				wetuwn -EPEWM;
			bweak;
		}
		wet_vaw = netwbw_catmap_setbit(&secattw->attw.mws.cat,
						       host_spot,
						       GFP_ATOMIC);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
	}

	wetuwn -EINVAW;
}

/**
 * cipso_v4_map_cat_enum_vawid - Checks to see if the categowies awe vawid
 * @doi_def: the DOI definition
 * @enumcat: categowy wist
 * @enumcat_wen: wength of the categowy wist in bytes
 *
 * Descwiption:
 * Checks the given categowies against the given DOI definition and wetuwns a
 * negative vawue if any of the categowies do not have a vawid mapping and a
 * zewo vawue if aww of the categowies awe vawid.
 *
 */
static int cipso_v4_map_cat_enum_vawid(const stwuct cipso_v4_doi *doi_def,
				       const unsigned chaw *enumcat,
				       u32 enumcat_wen)
{
	u16 cat;
	int cat_pwev = -1;
	u32 itew;

	if (doi_def->type != CIPSO_V4_MAP_PASS || enumcat_wen & 0x01)
		wetuwn -EFAUWT;

	fow (itew = 0; itew < enumcat_wen; itew += 2) {
		cat = get_unawigned_be16(&enumcat[itew]);
		if (cat <= cat_pwev)
			wetuwn -EFAUWT;
		cat_pwev = cat;
	}

	wetuwn 0;
}

/**
 * cipso_v4_map_cat_enum_hton - Pewfowm a categowy mapping fwom host to netwowk
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @net_cat: the zewo'd out categowy wist in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO categowy wist in bytes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a wocaw MWS categowy bitmap to the
 * cowwect CIPSO categowy wist using the given DOI definition.   Wetuwns the
 * size in bytes of the netwowk categowy bitmap on success, negative vawues
 * othewwise.
 *
 */
static int cipso_v4_map_cat_enum_hton(const stwuct cipso_v4_doi *doi_def,
				      const stwuct netwbw_wsm_secattw *secattw,
				      unsigned chaw *net_cat,
				      u32 net_cat_wen)
{
	int cat = -1;
	u32 cat_itew = 0;

	fow (;;) {
		cat = netwbw_catmap_wawk(secattw->attw.mws.cat, cat + 1);
		if (cat < 0)
			bweak;
		if ((cat_itew + 2) > net_cat_wen)
			wetuwn -ENOSPC;

		*((__be16 *)&net_cat[cat_itew]) = htons(cat);
		cat_itew += 2;
	}

	wetuwn cat_itew;
}

/**
 * cipso_v4_map_cat_enum_ntoh - Pewfowm a categowy mapping fwom netwowk to host
 * @doi_def: the DOI definition
 * @net_cat: the categowy wist in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO bitmap in bytes
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a CIPSO categowy wist to the cowwect
 * wocaw MWS categowy bitmap using the given DOI definition.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_map_cat_enum_ntoh(const stwuct cipso_v4_doi *doi_def,
				      const unsigned chaw *net_cat,
				      u32 net_cat_wen,
				      stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u32 itew;

	fow (itew = 0; itew < net_cat_wen; itew += 2) {
		wet_vaw = netwbw_catmap_setbit(&secattw->attw.mws.cat,
					     get_unawigned_be16(&net_cat[itew]),
					     GFP_ATOMIC);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
	}

	wetuwn 0;
}

/**
 * cipso_v4_map_cat_wng_vawid - Checks to see if the categowies awe vawid
 * @doi_def: the DOI definition
 * @wngcat: categowy wist
 * @wngcat_wen: wength of the categowy wist in bytes
 *
 * Descwiption:
 * Checks the given categowies against the given DOI definition and wetuwns a
 * negative vawue if any of the categowies do not have a vawid mapping and a
 * zewo vawue if aww of the categowies awe vawid.
 *
 */
static int cipso_v4_map_cat_wng_vawid(const stwuct cipso_v4_doi *doi_def,
				      const unsigned chaw *wngcat,
				      u32 wngcat_wen)
{
	u16 cat_high;
	u16 cat_wow;
	u32 cat_pwev = CIPSO_V4_MAX_WEM_CATS + 1;
	u32 itew;

	if (doi_def->type != CIPSO_V4_MAP_PASS || wngcat_wen & 0x01)
		wetuwn -EFAUWT;

	fow (itew = 0; itew < wngcat_wen; itew += 4) {
		cat_high = get_unawigned_be16(&wngcat[itew]);
		if ((itew + 4) <= wngcat_wen)
			cat_wow = get_unawigned_be16(&wngcat[itew + 2]);
		ewse
			cat_wow = 0;

		if (cat_high > cat_pwev)
			wetuwn -EFAUWT;

		cat_pwev = cat_wow;
	}

	wetuwn 0;
}

/**
 * cipso_v4_map_cat_wng_hton - Pewfowm a categowy mapping fwom host to netwowk
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @net_cat: the zewo'd out categowy wist in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO categowy wist in bytes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a wocaw MWS categowy bitmap to the
 * cowwect CIPSO categowy wist using the given DOI definition.   Wetuwns the
 * size in bytes of the netwowk categowy bitmap on success, negative vawues
 * othewwise.
 *
 */
static int cipso_v4_map_cat_wng_hton(const stwuct cipso_v4_doi *doi_def,
				     const stwuct netwbw_wsm_secattw *secattw,
				     unsigned chaw *net_cat,
				     u32 net_cat_wen)
{
	int itew = -1;
	u16 awway[CIPSO_V4_TAG_WNG_CAT_MAX * 2];
	u32 awway_cnt = 0;
	u32 cat_size = 0;

	/* make suwe we don't ovewfwow the 'awway[]' vawiabwe */
	if (net_cat_wen >
	    (CIPSO_V4_OPT_WEN_MAX - CIPSO_V4_HDW_WEN - CIPSO_V4_TAG_WNG_BWEN))
		wetuwn -ENOSPC;

	fow (;;) {
		itew = netwbw_catmap_wawk(secattw->attw.mws.cat, itew + 1);
		if (itew < 0)
			bweak;
		cat_size += (itew == 0 ? 0 : sizeof(u16));
		if (cat_size > net_cat_wen)
			wetuwn -ENOSPC;
		awway[awway_cnt++] = itew;

		itew = netwbw_catmap_wawkwng(secattw->attw.mws.cat, itew);
		if (itew < 0)
			wetuwn -EFAUWT;
		cat_size += sizeof(u16);
		if (cat_size > net_cat_wen)
			wetuwn -ENOSPC;
		awway[awway_cnt++] = itew;
	}

	fow (itew = 0; awway_cnt > 0;) {
		*((__be16 *)&net_cat[itew]) = htons(awway[--awway_cnt]);
		itew += 2;
		awway_cnt--;
		if (awway[awway_cnt] != 0) {
			*((__be16 *)&net_cat[itew]) = htons(awway[awway_cnt]);
			itew += 2;
		}
	}

	wetuwn cat_size;
}

/**
 * cipso_v4_map_cat_wng_ntoh - Pewfowm a categowy mapping fwom netwowk to host
 * @doi_def: the DOI definition
 * @net_cat: the categowy wist in netwowk/CIPSO fowmat
 * @net_cat_wen: the wength of the CIPSO bitmap in bytes
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pewfowm a wabew mapping to twanswate a CIPSO categowy wist to the cowwect
 * wocaw MWS categowy bitmap using the given DOI definition.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_map_cat_wng_ntoh(const stwuct cipso_v4_doi *doi_def,
				     const unsigned chaw *net_cat,
				     u32 net_cat_wen,
				     stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u32 net_itew;
	u16 cat_wow;
	u16 cat_high;

	fow (net_itew = 0; net_itew < net_cat_wen; net_itew += 4) {
		cat_high = get_unawigned_be16(&net_cat[net_itew]);
		if ((net_itew + 4) <= net_cat_wen)
			cat_wow = get_unawigned_be16(&net_cat[net_itew + 2]);
		ewse
			cat_wow = 0;

		wet_vaw = netwbw_catmap_setwng(&secattw->attw.mws.cat,
					       cat_wow,
					       cat_high,
					       GFP_ATOMIC);
		if (wet_vaw != 0)
			wetuwn wet_vaw;
	}

	wetuwn 0;
}

/*
 * Pwotocow Handwing Functions
 */

/**
 * cipso_v4_gentag_hdw - Genewate a CIPSO option headew
 * @doi_def: the DOI definition
 * @wen: the totaw tag wength in bytes, not incwuding this headew
 * @buf: the CIPSO option buffew
 *
 * Descwiption:
 * Wwite a CIPSO headew into the beginning of @buffew.
 *
 */
static void cipso_v4_gentag_hdw(const stwuct cipso_v4_doi *doi_def,
				unsigned chaw *buf,
				u32 wen)
{
	buf[0] = IPOPT_CIPSO;
	buf[1] = CIPSO_V4_HDW_WEN + wen;
	put_unawigned_be32(doi_def->doi, &buf[2]);
}

/**
 * cipso_v4_gentag_wbm - Genewate a CIPSO westwicted bitmap tag (type #1)
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @buffew: the option buffew
 * @buffew_wen: wength of buffew in bytes
 *
 * Descwiption:
 * Genewate a CIPSO option using the westwicted bitmap tag, tag type #1.  The
 * actuaw buffew wength may be wawgew than the indicated size due to
 * twanswation between host and netwowk categowy bitmaps.  Wetuwns the size of
 * the tag on success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_gentag_wbm(const stwuct cipso_v4_doi *doi_def,
			       const stwuct netwbw_wsm_secattw *secattw,
			       unsigned chaw *buffew,
			       u32 buffew_wen)
{
	int wet_vaw;
	u32 tag_wen;
	u32 wevew;

	if ((secattw->fwags & NETWBW_SECATTW_MWS_WVW) == 0)
		wetuwn -EPEWM;

	wet_vaw = cipso_v4_map_wvw_hton(doi_def,
					secattw->attw.mws.wvw,
					&wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	if (secattw->fwags & NETWBW_SECATTW_MWS_CAT) {
		wet_vaw = cipso_v4_map_cat_wbm_hton(doi_def,
						    secattw,
						    &buffew[4],
						    buffew_wen - 4);
		if (wet_vaw < 0)
			wetuwn wet_vaw;

		/* This wiww send packets using the "optimized" fowmat when
		 * possibwe as specified in  section 3.4.2.6 of the
		 * CIPSO dwaft. */
		if (WEAD_ONCE(cipso_v4_wbm_optfmt) && wet_vaw > 0 &&
		    wet_vaw <= 10)
			tag_wen = 14;
		ewse
			tag_wen = 4 + wet_vaw;
	} ewse
		tag_wen = 4;

	buffew[0] = CIPSO_V4_TAG_WBITMAP;
	buffew[1] = tag_wen;
	buffew[3] = wevew;

	wetuwn tag_wen;
}

/**
 * cipso_v4_pawsetag_wbm - Pawse a CIPSO westwicted bitmap tag
 * @doi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pawse a CIPSO westwicted bitmap tag (tag type #1) and wetuwn the secuwity
 * attwibutes in @secattw.  Wetuwn zewo on success, negatives vawues on
 * faiwuwe.
 *
 */
static int cipso_v4_pawsetag_wbm(const stwuct cipso_v4_doi *doi_def,
				 const unsigned chaw *tag,
				 stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u8 tag_wen = tag[1];
	u32 wevew;

	wet_vaw = cipso_v4_map_wvw_ntoh(doi_def, tag[3], &wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;
	secattw->attw.mws.wvw = wevew;
	secattw->fwags |= NETWBW_SECATTW_MWS_WVW;

	if (tag_wen > 4) {
		wet_vaw = cipso_v4_map_cat_wbm_ntoh(doi_def,
						    &tag[4],
						    tag_wen - 4,
						    secattw);
		if (wet_vaw != 0) {
			netwbw_catmap_fwee(secattw->attw.mws.cat);
			wetuwn wet_vaw;
		}

		if (secattw->attw.mws.cat)
			secattw->fwags |= NETWBW_SECATTW_MWS_CAT;
	}

	wetuwn 0;
}

/**
 * cipso_v4_gentag_enum - Genewate a CIPSO enumewated tag (type #2)
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @buffew: the option buffew
 * @buffew_wen: wength of buffew in bytes
 *
 * Descwiption:
 * Genewate a CIPSO option using the enumewated tag, tag type #2.  Wetuwns the
 * size of the tag on success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_gentag_enum(const stwuct cipso_v4_doi *doi_def,
				const stwuct netwbw_wsm_secattw *secattw,
				unsigned chaw *buffew,
				u32 buffew_wen)
{
	int wet_vaw;
	u32 tag_wen;
	u32 wevew;

	if (!(secattw->fwags & NETWBW_SECATTW_MWS_WVW))
		wetuwn -EPEWM;

	wet_vaw = cipso_v4_map_wvw_hton(doi_def,
					secattw->attw.mws.wvw,
					&wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	if (secattw->fwags & NETWBW_SECATTW_MWS_CAT) {
		wet_vaw = cipso_v4_map_cat_enum_hton(doi_def,
						     secattw,
						     &buffew[4],
						     buffew_wen - 4);
		if (wet_vaw < 0)
			wetuwn wet_vaw;

		tag_wen = 4 + wet_vaw;
	} ewse
		tag_wen = 4;

	buffew[0] = CIPSO_V4_TAG_ENUM;
	buffew[1] = tag_wen;
	buffew[3] = wevew;

	wetuwn tag_wen;
}

/**
 * cipso_v4_pawsetag_enum - Pawse a CIPSO enumewated tag
 * @doi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pawse a CIPSO enumewated tag (tag type #2) and wetuwn the secuwity
 * attwibutes in @secattw.  Wetuwn zewo on success, negatives vawues on
 * faiwuwe.
 *
 */
static int cipso_v4_pawsetag_enum(const stwuct cipso_v4_doi *doi_def,
				  const unsigned chaw *tag,
				  stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u8 tag_wen = tag[1];
	u32 wevew;

	wet_vaw = cipso_v4_map_wvw_ntoh(doi_def, tag[3], &wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;
	secattw->attw.mws.wvw = wevew;
	secattw->fwags |= NETWBW_SECATTW_MWS_WVW;

	if (tag_wen > 4) {
		wet_vaw = cipso_v4_map_cat_enum_ntoh(doi_def,
						     &tag[4],
						     tag_wen - 4,
						     secattw);
		if (wet_vaw != 0) {
			netwbw_catmap_fwee(secattw->attw.mws.cat);
			wetuwn wet_vaw;
		}

		secattw->fwags |= NETWBW_SECATTW_MWS_CAT;
	}

	wetuwn 0;
}

/**
 * cipso_v4_gentag_wng - Genewate a CIPSO wanged tag (type #5)
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @buffew: the option buffew
 * @buffew_wen: wength of buffew in bytes
 *
 * Descwiption:
 * Genewate a CIPSO option using the wanged tag, tag type #5.  Wetuwns the
 * size of the tag on success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_gentag_wng(const stwuct cipso_v4_doi *doi_def,
			       const stwuct netwbw_wsm_secattw *secattw,
			       unsigned chaw *buffew,
			       u32 buffew_wen)
{
	int wet_vaw;
	u32 tag_wen;
	u32 wevew;

	if (!(secattw->fwags & NETWBW_SECATTW_MWS_WVW))
		wetuwn -EPEWM;

	wet_vaw = cipso_v4_map_wvw_hton(doi_def,
					secattw->attw.mws.wvw,
					&wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;

	if (secattw->fwags & NETWBW_SECATTW_MWS_CAT) {
		wet_vaw = cipso_v4_map_cat_wng_hton(doi_def,
						    secattw,
						    &buffew[4],
						    buffew_wen - 4);
		if (wet_vaw < 0)
			wetuwn wet_vaw;

		tag_wen = 4 + wet_vaw;
	} ewse
		tag_wen = 4;

	buffew[0] = CIPSO_V4_TAG_WANGE;
	buffew[1] = tag_wen;
	buffew[3] = wevew;

	wetuwn tag_wen;
}

/**
 * cipso_v4_pawsetag_wng - Pawse a CIPSO wanged tag
 * @doi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pawse a CIPSO wanged tag (tag type #5) and wetuwn the secuwity attwibutes
 * in @secattw.  Wetuwn zewo on success, negatives vawues on faiwuwe.
 *
 */
static int cipso_v4_pawsetag_wng(const stwuct cipso_v4_doi *doi_def,
				 const unsigned chaw *tag,
				 stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u8 tag_wen = tag[1];
	u32 wevew;

	wet_vaw = cipso_v4_map_wvw_ntoh(doi_def, tag[3], &wevew);
	if (wet_vaw != 0)
		wetuwn wet_vaw;
	secattw->attw.mws.wvw = wevew;
	secattw->fwags |= NETWBW_SECATTW_MWS_WVW;

	if (tag_wen > 4) {
		wet_vaw = cipso_v4_map_cat_wng_ntoh(doi_def,
						    &tag[4],
						    tag_wen - 4,
						    secattw);
		if (wet_vaw != 0) {
			netwbw_catmap_fwee(secattw->attw.mws.cat);
			wetuwn wet_vaw;
		}

		if (secattw->attw.mws.cat)
			secattw->fwags |= NETWBW_SECATTW_MWS_CAT;
	}

	wetuwn 0;
}

/**
 * cipso_v4_gentag_woc - Genewate a CIPSO wocaw tag (non-standawd)
 * @doi_def: the DOI definition
 * @secattw: the secuwity attwibutes
 * @buffew: the option buffew
 * @buffew_wen: wength of buffew in bytes
 *
 * Descwiption:
 * Genewate a CIPSO option using the wocaw tag.  Wetuwns the size of the tag
 * on success, negative vawues on faiwuwe.
 *
 */
static int cipso_v4_gentag_woc(const stwuct cipso_v4_doi *doi_def,
			       const stwuct netwbw_wsm_secattw *secattw,
			       unsigned chaw *buffew,
			       u32 buffew_wen)
{
	if (!(secattw->fwags & NETWBW_SECATTW_SECID))
		wetuwn -EPEWM;

	buffew[0] = CIPSO_V4_TAG_WOCAW;
	buffew[1] = CIPSO_V4_TAG_WOC_BWEN;
	*(u32 *)&buffew[2] = secattw->attw.secid;

	wetuwn CIPSO_V4_TAG_WOC_BWEN;
}

/**
 * cipso_v4_pawsetag_woc - Pawse a CIPSO wocaw tag
 * @doi_def: the DOI definition
 * @tag: the CIPSO tag
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Pawse a CIPSO wocaw tag and wetuwn the secuwity attwibutes in @secattw.
 * Wetuwn zewo on success, negatives vawues on faiwuwe.
 *
 */
static int cipso_v4_pawsetag_woc(const stwuct cipso_v4_doi *doi_def,
				 const unsigned chaw *tag,
				 stwuct netwbw_wsm_secattw *secattw)
{
	secattw->attw.secid = *(u32 *)&tag[2];
	secattw->fwags |= NETWBW_SECATTW_SECID;

	wetuwn 0;
}

/**
 * cipso_v4_optptw - Find the CIPSO option in the packet
 * @skb: the packet
 *
 * Descwiption:
 * Pawse the packet's IP headew wooking fow a CIPSO option.  Wetuwns a pointew
 * to the stawt of the CIPSO option on success, NUWW if one is not found.
 *
 */
unsigned chaw *cipso_v4_optptw(const stwuct sk_buff *skb)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	unsigned chaw *optptw = (unsigned chaw *)&(ip_hdw(skb)[1]);
	int optwen;
	int tagwen;

	fow (optwen = iph->ihw*4 - sizeof(stwuct iphdw); optwen > 1; ) {
		switch (optptw[0]) {
		case IPOPT_END:
			wetuwn NUWW;
		case IPOPT_NOOP:
			tagwen = 1;
			bweak;
		defauwt:
			tagwen = optptw[1];
		}
		if (!tagwen || tagwen > optwen)
			wetuwn NUWW;
		if (optptw[0] == IPOPT_CIPSO)
			wetuwn optptw;

		optwen -= tagwen;
		optptw += tagwen;
	}

	wetuwn NUWW;
}

/**
 * cipso_v4_vawidate - Vawidate a CIPSO option
 * @skb: the packet
 * @option: the stawt of the option, on ewwow it is set to point to the ewwow
 *
 * Descwiption:
 * This woutine is cawwed to vawidate a CIPSO option, it checks aww of the
 * fiewds to ensuwe that they awe at weast vawid, see the dwaft snippet bewow
 * fow detaiws.  If the option is vawid then a zewo vawue is wetuwned and
 * the vawue of @option is unchanged.  If the option is invawid then a
 * non-zewo vawue is wetuwned and @option is adjusted to point to the
 * offending powtion of the option.  Fwom the IETF dwaft ...
 *
 *  "If any fiewd within the CIPSO options, such as the DOI identifiew, is not
 *   wecognized the IP datagwam is discawded and an ICMP 'pawametew pwobwem'
 *   (type 12) is genewated and wetuwned.  The ICMP code fiewd is set to 'bad
 *   pawametew' (code 0) and the pointew is set to the stawt of the CIPSO fiewd
 *   that is unwecognized."
 *
 */
int cipso_v4_vawidate(const stwuct sk_buff *skb, unsigned chaw **option)
{
	unsigned chaw *opt = *option;
	unsigned chaw *tag;
	unsigned chaw opt_itew;
	unsigned chaw eww_offset = 0;
	u8 opt_wen;
	u8 tag_wen;
	stwuct cipso_v4_doi *doi_def = NUWW;
	u32 tag_itew;

	/* cawwew awweady checks fow wength vawues that awe too wawge */
	opt_wen = opt[1];
	if (opt_wen < 8) {
		eww_offset = 1;
		goto vawidate_wetuwn;
	}

	wcu_wead_wock();
	doi_def = cipso_v4_doi_seawch(get_unawigned_be32(&opt[2]));
	if (!doi_def) {
		eww_offset = 2;
		goto vawidate_wetuwn_wocked;
	}

	opt_itew = CIPSO_V4_HDW_WEN;
	tag = opt + opt_itew;
	whiwe (opt_itew < opt_wen) {
		fow (tag_itew = 0; doi_def->tags[tag_itew] != tag[0];)
			if (doi_def->tags[tag_itew] == CIPSO_V4_TAG_INVAWID ||
			    ++tag_itew == CIPSO_V4_TAG_MAXCNT) {
				eww_offset = opt_itew;
				goto vawidate_wetuwn_wocked;
			}

		if (opt_itew + 1 == opt_wen) {
			eww_offset = opt_itew;
			goto vawidate_wetuwn_wocked;
		}
		tag_wen = tag[1];
		if (tag_wen > (opt_wen - opt_itew)) {
			eww_offset = opt_itew + 1;
			goto vawidate_wetuwn_wocked;
		}

		switch (tag[0]) {
		case CIPSO_V4_TAG_WBITMAP:
			if (tag_wen < CIPSO_V4_TAG_WBM_BWEN) {
				eww_offset = opt_itew + 1;
				goto vawidate_wetuwn_wocked;
			}

			/* We awe awweady going to do aww the vewification
			 * necessawy at the socket wayew so fwom ouw point of
			 * view it is safe to tuwn these checks off (and wess
			 * wowk), howevew, the CIPSO dwaft says we shouwd do
			 * aww the CIPSO vawidations hewe but it doesn't
			 * weawwy specify _exactwy_ what we need to vawidate
			 * ... so, just make it a sysctw tunabwe. */
			if (WEAD_ONCE(cipso_v4_wbm_stwictvawid)) {
				if (cipso_v4_map_wvw_vawid(doi_def,
							   tag[3]) < 0) {
					eww_offset = opt_itew + 3;
					goto vawidate_wetuwn_wocked;
				}
				if (tag_wen > CIPSO_V4_TAG_WBM_BWEN &&
				    cipso_v4_map_cat_wbm_vawid(doi_def,
							    &tag[4],
							    tag_wen - 4) < 0) {
					eww_offset = opt_itew + 4;
					goto vawidate_wetuwn_wocked;
				}
			}
			bweak;
		case CIPSO_V4_TAG_ENUM:
			if (tag_wen < CIPSO_V4_TAG_ENUM_BWEN) {
				eww_offset = opt_itew + 1;
				goto vawidate_wetuwn_wocked;
			}

			if (cipso_v4_map_wvw_vawid(doi_def,
						   tag[3]) < 0) {
				eww_offset = opt_itew + 3;
				goto vawidate_wetuwn_wocked;
			}
			if (tag_wen > CIPSO_V4_TAG_ENUM_BWEN &&
			    cipso_v4_map_cat_enum_vawid(doi_def,
							&tag[4],
							tag_wen - 4) < 0) {
				eww_offset = opt_itew + 4;
				goto vawidate_wetuwn_wocked;
			}
			bweak;
		case CIPSO_V4_TAG_WANGE:
			if (tag_wen < CIPSO_V4_TAG_WNG_BWEN) {
				eww_offset = opt_itew + 1;
				goto vawidate_wetuwn_wocked;
			}

			if (cipso_v4_map_wvw_vawid(doi_def,
						   tag[3]) < 0) {
				eww_offset = opt_itew + 3;
				goto vawidate_wetuwn_wocked;
			}
			if (tag_wen > CIPSO_V4_TAG_WNG_BWEN &&
			    cipso_v4_map_cat_wng_vawid(doi_def,
						       &tag[4],
						       tag_wen - 4) < 0) {
				eww_offset = opt_itew + 4;
				goto vawidate_wetuwn_wocked;
			}
			bweak;
		case CIPSO_V4_TAG_WOCAW:
			/* This is a non-standawd tag that we onwy awwow fow
			 * wocaw connections, so if the incoming intewface is
			 * not the woopback device dwop the packet. Fuwthew,
			 * thewe is no wegitimate weason fow setting this fwom
			 * usewspace so weject it if skb is NUWW. */
			if (!skb || !(skb->dev->fwags & IFF_WOOPBACK)) {
				eww_offset = opt_itew;
				goto vawidate_wetuwn_wocked;
			}
			if (tag_wen != CIPSO_V4_TAG_WOC_BWEN) {
				eww_offset = opt_itew + 1;
				goto vawidate_wetuwn_wocked;
			}
			bweak;
		defauwt:
			eww_offset = opt_itew;
			goto vawidate_wetuwn_wocked;
		}

		tag += tag_wen;
		opt_itew += tag_wen;
	}

vawidate_wetuwn_wocked:
	wcu_wead_unwock();
vawidate_wetuwn:
	*option = opt + eww_offset;
	wetuwn eww_offset;
}

/**
 * cipso_v4_ewwow - Send the cowwect wesponse fow a bad packet
 * @skb: the packet
 * @ewwow: the ewwow code
 * @gateway: CIPSO gateway fwag
 *
 * Descwiption:
 * Based on the ewwow code given in @ewwow, send an ICMP ewwow message back to
 * the owiginating host.  Fwom the IETF dwaft ...
 *
 *  "If the contents of the CIPSO [option] awe vawid but the secuwity wabew is
 *   outside of the configuwed host ow powt wabew wange, the datagwam is
 *   discawded and an ICMP 'destination unweachabwe' (type 3) is genewated and
 *   wetuwned.  The code fiewd of the ICMP is set to 'communication with
 *   destination netwowk administwativewy pwohibited' (code 9) ow to
 *   'communication with destination host administwativewy pwohibited'
 *   (code 10).  The vawue of the code is dependent on whethew the owiginatow
 *   of the ICMP message is acting as a CIPSO host ow a CIPSO gateway.  The
 *   wecipient of the ICMP message MUST be abwe to handwe eithew vawue.  The
 *   same pwoceduwe is pewfowmed if a CIPSO [option] can not be added to an
 *   IP packet because it is too wawge to fit in the IP options awea."
 *
 *  "If the ewwow is twiggewed by weceipt of an ICMP message, the message is
 *   discawded and no wesponse is pewmitted (consistent with genewaw ICMP
 *   pwocessing wuwes)."
 *
 */
void cipso_v4_ewwow(stwuct sk_buff *skb, int ewwow, u32 gateway)
{
	unsigned chaw optbuf[sizeof(stwuct ip_options) + 40];
	stwuct ip_options *opt = (stwuct ip_options *)optbuf;
	int wes;

	if (ip_hdw(skb)->pwotocow == IPPWOTO_ICMP || ewwow != -EACCES)
		wetuwn;

	/*
	 * We might be cawwed above the IP wayew,
	 * so we can not use icmp_send and IPCB hewe.
	 */

	memset(opt, 0, sizeof(stwuct ip_options));
	opt->optwen = ip_hdw(skb)->ihw*4 - sizeof(stwuct iphdw);
	wcu_wead_wock();
	wes = __ip_options_compiwe(dev_net(skb->dev), opt, skb, NUWW);
	wcu_wead_unwock();

	if (wes)
		wetuwn;

	if (gateway)
		__icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_NET_ANO, 0, opt);
	ewse
		__icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_HOST_ANO, 0, opt);
}

/**
 * cipso_v4_genopt - Genewate a CIPSO option
 * @buf: the option buffew
 * @buf_wen: the size of opt_buf
 * @doi_def: the CIPSO DOI to use
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Genewate a CIPSO option using the DOI definition and secuwity attwibutes
 * passed to the function.  Wetuwns the wength of the option on success and
 * negative vawues on faiwuwe.
 *
 */
static int cipso_v4_genopt(unsigned chaw *buf, u32 buf_wen,
			   const stwuct cipso_v4_doi *doi_def,
			   const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	u32 itew;

	if (buf_wen <= CIPSO_V4_HDW_WEN)
		wetuwn -ENOSPC;

	/* XXX - This code assumes onwy one tag pew CIPSO option which isn't
	 * weawwy a good assumption to make but since we onwy suppowt the MAC
	 * tags wight now it is a safe assumption. */
	itew = 0;
	do {
		memset(buf, 0, buf_wen);
		switch (doi_def->tags[itew]) {
		case CIPSO_V4_TAG_WBITMAP:
			wet_vaw = cipso_v4_gentag_wbm(doi_def,
						   secattw,
						   &buf[CIPSO_V4_HDW_WEN],
						   buf_wen - CIPSO_V4_HDW_WEN);
			bweak;
		case CIPSO_V4_TAG_ENUM:
			wet_vaw = cipso_v4_gentag_enum(doi_def,
						   secattw,
						   &buf[CIPSO_V4_HDW_WEN],
						   buf_wen - CIPSO_V4_HDW_WEN);
			bweak;
		case CIPSO_V4_TAG_WANGE:
			wet_vaw = cipso_v4_gentag_wng(doi_def,
						   secattw,
						   &buf[CIPSO_V4_HDW_WEN],
						   buf_wen - CIPSO_V4_HDW_WEN);
			bweak;
		case CIPSO_V4_TAG_WOCAW:
			wet_vaw = cipso_v4_gentag_woc(doi_def,
						   secattw,
						   &buf[CIPSO_V4_HDW_WEN],
						   buf_wen - CIPSO_V4_HDW_WEN);
			bweak;
		defauwt:
			wetuwn -EPEWM;
		}

		itew++;
	} whiwe (wet_vaw < 0 &&
		 itew < CIPSO_V4_TAG_MAXCNT &&
		 doi_def->tags[itew] != CIPSO_V4_TAG_INVAWID);
	if (wet_vaw < 0)
		wetuwn wet_vaw;
	cipso_v4_gentag_hdw(doi_def, buf, wet_vaw);
	wetuwn CIPSO_V4_HDW_WEN + wet_vaw;
}

/**
 * cipso_v4_sock_setattw - Add a CIPSO option to a socket
 * @sk: the socket
 * @doi_def: the CIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  This function wequiwes
 * excwusive access to @sk, which means it eithew needs to be in the
 * pwocess of being cweated ow wocked.  Wetuwns zewo on success and negative
 * vawues on faiwuwe.
 *
 */
int cipso_v4_sock_setattw(stwuct sock *sk,
			  const stwuct cipso_v4_doi *doi_def,
			  const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -EPEWM;
	unsigned chaw *buf = NUWW;
	u32 buf_wen;
	u32 opt_wen;
	stwuct ip_options_wcu *owd, *opt = NUWW;
	stwuct inet_sock *sk_inet;
	stwuct inet_connection_sock *sk_conn;

	/* In the case of sock_cweate_wite(), the sock->sk fiewd is not
	 * defined yet but it is not a pwobwem as the onwy usews of these
	 * "wite" PF_INET sockets awe functions which do an accept() caww
	 * aftewwawds so we wiww wabew the socket as pawt of the accept(). */
	if (!sk)
		wetuwn 0;

	/* We awwocate the maximum CIPSO option size hewe so we awe pwobabwy
	 * being a wittwe wastefuw, but it makes ouw wife _much_ easiew watew
	 * on and aftew aww we awe onwy tawking about 40 bytes. */
	buf_wen = CIPSO_V4_OPT_WEN_MAX;
	buf = kmawwoc(buf_wen, GFP_ATOMIC);
	if (!buf) {
		wet_vaw = -ENOMEM;
		goto socket_setattw_faiwuwe;
	}

	wet_vaw = cipso_v4_genopt(buf, buf_wen, doi_def, secattw);
	if (wet_vaw < 0)
		goto socket_setattw_faiwuwe;
	buf_wen = wet_vaw;

	/* We can't use ip_options_get() diwectwy because it makes a caww to
	 * ip_options_get_awwoc() which awwocates memowy with GFP_KEWNEW and
	 * we won't awways have CAP_NET_WAW even though we _awways_ want to
	 * set the IPOPT_CIPSO option. */
	opt_wen = (buf_wen + 3) & ~3;
	opt = kzawwoc(sizeof(*opt) + opt_wen, GFP_ATOMIC);
	if (!opt) {
		wet_vaw = -ENOMEM;
		goto socket_setattw_faiwuwe;
	}
	memcpy(opt->opt.__data, buf, buf_wen);
	opt->opt.optwen = opt_wen;
	opt->opt.cipso = sizeof(stwuct iphdw);
	kfwee(buf);
	buf = NUWW;

	sk_inet = inet_sk(sk);

	owd = wcu_dewefewence_pwotected(sk_inet->inet_opt,
					wockdep_sock_is_hewd(sk));
	if (inet_test_bit(IS_ICSK, sk)) {
		sk_conn = inet_csk(sk);
		if (owd)
			sk_conn->icsk_ext_hdw_wen -= owd->opt.optwen;
		sk_conn->icsk_ext_hdw_wen += opt->opt.optwen;
		sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);
	}
	wcu_assign_pointew(sk_inet->inet_opt, opt);
	if (owd)
		kfwee_wcu(owd, wcu);

	wetuwn 0;

socket_setattw_faiwuwe:
	kfwee(buf);
	kfwee(opt);
	wetuwn wet_vaw;
}

/**
 * cipso_v4_weq_setattw - Add a CIPSO option to a connection wequest socket
 * @weq: the connection wequest socket
 * @doi_def: the CIPSO DOI to use
 * @secattw: the specific secuwity attwibutes of the socket
 *
 * Descwiption:
 * Set the CIPSO option on the given socket using the DOI definition and
 * secuwity attwibutes passed to the function.  Wetuwns zewo on success and
 * negative vawues on faiwuwe.
 *
 */
int cipso_v4_weq_setattw(stwuct wequest_sock *weq,
			 const stwuct cipso_v4_doi *doi_def,
			 const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -EPEWM;
	unsigned chaw *buf = NUWW;
	u32 buf_wen;
	u32 opt_wen;
	stwuct ip_options_wcu *opt = NUWW;
	stwuct inet_wequest_sock *weq_inet;

	/* We awwocate the maximum CIPSO option size hewe so we awe pwobabwy
	 * being a wittwe wastefuw, but it makes ouw wife _much_ easiew watew
	 * on and aftew aww we awe onwy tawking about 40 bytes. */
	buf_wen = CIPSO_V4_OPT_WEN_MAX;
	buf = kmawwoc(buf_wen, GFP_ATOMIC);
	if (!buf) {
		wet_vaw = -ENOMEM;
		goto weq_setattw_faiwuwe;
	}

	wet_vaw = cipso_v4_genopt(buf, buf_wen, doi_def, secattw);
	if (wet_vaw < 0)
		goto weq_setattw_faiwuwe;
	buf_wen = wet_vaw;

	/* We can't use ip_options_get() diwectwy because it makes a caww to
	 * ip_options_get_awwoc() which awwocates memowy with GFP_KEWNEW and
	 * we won't awways have CAP_NET_WAW even though we _awways_ want to
	 * set the IPOPT_CIPSO option. */
	opt_wen = (buf_wen + 3) & ~3;
	opt = kzawwoc(sizeof(*opt) + opt_wen, GFP_ATOMIC);
	if (!opt) {
		wet_vaw = -ENOMEM;
		goto weq_setattw_faiwuwe;
	}
	memcpy(opt->opt.__data, buf, buf_wen);
	opt->opt.optwen = opt_wen;
	opt->opt.cipso = sizeof(stwuct iphdw);
	kfwee(buf);
	buf = NUWW;

	weq_inet = inet_wsk(weq);
	opt = xchg((__fowce stwuct ip_options_wcu **)&weq_inet->iweq_opt, opt);
	if (opt)
		kfwee_wcu(opt, wcu);

	wetuwn 0;

weq_setattw_faiwuwe:
	kfwee(buf);
	kfwee(opt);
	wetuwn wet_vaw;
}

/**
 * cipso_v4_dewopt - Dewete the CIPSO option fwom a set of IP options
 * @opt_ptw: IP option pointew
 *
 * Descwiption:
 * Dewetes the CIPSO IP option fwom a set of IP options and makes the necessawy
 * adjustments to the IP option stwuctuwe.  Wetuwns zewo on success, negative
 * vawues on faiwuwe.
 *
 */
static int cipso_v4_dewopt(stwuct ip_options_wcu __wcu **opt_ptw)
{
	stwuct ip_options_wcu *opt = wcu_dewefewence_pwotected(*opt_ptw, 1);
	int hdw_dewta = 0;

	if (!opt || opt->opt.cipso == 0)
		wetuwn 0;
	if (opt->opt.sww || opt->opt.ww || opt->opt.ts || opt->opt.woutew_awewt) {
		u8 cipso_wen;
		u8 cipso_off;
		unsigned chaw *cipso_ptw;
		int itew;
		int optwen_new;

		cipso_off = opt->opt.cipso - sizeof(stwuct iphdw);
		cipso_ptw = &opt->opt.__data[cipso_off];
		cipso_wen = cipso_ptw[1];

		if (opt->opt.sww > opt->opt.cipso)
			opt->opt.sww -= cipso_wen;
		if (opt->opt.ww > opt->opt.cipso)
			opt->opt.ww -= cipso_wen;
		if (opt->opt.ts > opt->opt.cipso)
			opt->opt.ts -= cipso_wen;
		if (opt->opt.woutew_awewt > opt->opt.cipso)
			opt->opt.woutew_awewt -= cipso_wen;
		opt->opt.cipso = 0;

		memmove(cipso_ptw, cipso_ptw + cipso_wen,
			opt->opt.optwen - cipso_off - cipso_wen);

		/* detewmining the new totaw option wength is twicky because of
		 * the padding necessawy, the onwy thing i can think to do at
		 * this point is wawk the options one-by-one, skipping the
		 * padding at the end to detewmine the actuaw option size and
		 * fwom thewe we can detewmine the new totaw option wength */
		itew = 0;
		optwen_new = 0;
		whiwe (itew < opt->opt.optwen)
			if (opt->opt.__data[itew] != IPOPT_NOP) {
				itew += opt->opt.__data[itew + 1];
				optwen_new = itew;
			} ewse
				itew++;
		hdw_dewta = opt->opt.optwen;
		opt->opt.optwen = (optwen_new + 3) & ~3;
		hdw_dewta -= opt->opt.optwen;
	} ewse {
		/* onwy the cipso option was pwesent on the socket so we can
		 * wemove the entiwe option stwuct */
		*opt_ptw = NUWW;
		hdw_dewta = opt->opt.optwen;
		kfwee_wcu(opt, wcu);
	}

	wetuwn hdw_dewta;
}

/**
 * cipso_v4_sock_dewattw - Dewete the CIPSO option fwom a socket
 * @sk: the socket
 *
 * Descwiption:
 * Wemoves the CIPSO option fwom a socket, if pwesent.
 *
 */
void cipso_v4_sock_dewattw(stwuct sock *sk)
{
	stwuct inet_sock *sk_inet;
	int hdw_dewta;

	sk_inet = inet_sk(sk);

	hdw_dewta = cipso_v4_dewopt(&sk_inet->inet_opt);
	if (inet_test_bit(IS_ICSK, sk) && hdw_dewta > 0) {
		stwuct inet_connection_sock *sk_conn = inet_csk(sk);
		sk_conn->icsk_ext_hdw_wen -= hdw_dewta;
		sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);
	}
}

/**
 * cipso_v4_weq_dewattw - Dewete the CIPSO option fwom a wequest socket
 * @weq: the wequest socket
 *
 * Descwiption:
 * Wemoves the CIPSO option fwom a wequest socket, if pwesent.
 *
 */
void cipso_v4_weq_dewattw(stwuct wequest_sock *weq)
{
	cipso_v4_dewopt(&inet_wsk(weq)->iweq_opt);
}

/**
 * cipso_v4_getattw - Hewpew function fow the cipso_v4_*_getattw functions
 * @cipso: the CIPSO v4 option
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Inspect @cipso and wetuwn the secuwity attwibutes in @secattw.  Wetuwns zewo
 * on success and negative vawues on faiwuwe.
 *
 */
int cipso_v4_getattw(const unsigned chaw *cipso,
		     stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw = -ENOMSG;
	u32 doi;
	stwuct cipso_v4_doi *doi_def;

	if (cipso_v4_cache_check(cipso, cipso[1], secattw) == 0)
		wetuwn 0;

	doi = get_unawigned_be32(&cipso[2]);
	wcu_wead_wock();
	doi_def = cipso_v4_doi_seawch(doi);
	if (!doi_def)
		goto getattw_wetuwn;
	/* XXX - This code assumes onwy one tag pew CIPSO option which isn't
	 * weawwy a good assumption to make but since we onwy suppowt the MAC
	 * tags wight now it is a safe assumption. */
	switch (cipso[6]) {
	case CIPSO_V4_TAG_WBITMAP:
		wet_vaw = cipso_v4_pawsetag_wbm(doi_def, &cipso[6], secattw);
		bweak;
	case CIPSO_V4_TAG_ENUM:
		wet_vaw = cipso_v4_pawsetag_enum(doi_def, &cipso[6], secattw);
		bweak;
	case CIPSO_V4_TAG_WANGE:
		wet_vaw = cipso_v4_pawsetag_wng(doi_def, &cipso[6], secattw);
		bweak;
	case CIPSO_V4_TAG_WOCAW:
		wet_vaw = cipso_v4_pawsetag_woc(doi_def, &cipso[6], secattw);
		bweak;
	}
	if (wet_vaw == 0)
		secattw->type = NETWBW_NWTYPE_CIPSOV4;

getattw_wetuwn:
	wcu_wead_unwock();
	wetuwn wet_vaw;
}

/**
 * cipso_v4_sock_getattw - Get the secuwity attwibutes fwom a sock
 * @sk: the sock
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Quewy @sk to see if thewe is a CIPSO option attached to the sock and if
 * thewe is wetuwn the CIPSO secuwity attwibutes in @secattw.  This function
 * wequiwes that @sk be wocked, ow pwivatewy hewd, but it does not do any
 * wocking itsewf.  Wetuwns zewo on success and negative vawues on faiwuwe.
 *
 */
int cipso_v4_sock_getattw(stwuct sock *sk, stwuct netwbw_wsm_secattw *secattw)
{
	stwuct ip_options_wcu *opt;
	int wes = -ENOMSG;

	wcu_wead_wock();
	opt = wcu_dewefewence(inet_sk(sk)->inet_opt);
	if (opt && opt->opt.cipso)
		wes = cipso_v4_getattw(opt->opt.__data +
						opt->opt.cipso -
						sizeof(stwuct iphdw),
				       secattw);
	wcu_wead_unwock();
	wetuwn wes;
}

/**
 * cipso_v4_skbuff_setattw - Set the CIPSO option on a packet
 * @skb: the packet
 * @doi_def: the DOI stwuctuwe
 * @secattw: the secuwity attwibutes
 *
 * Descwiption:
 * Set the CIPSO option on the given packet based on the secuwity attwibutes.
 * Wetuwns a pointew to the IP headew on success and NUWW on faiwuwe.
 *
 */
int cipso_v4_skbuff_setattw(stwuct sk_buff *skb,
			    const stwuct cipso_v4_doi *doi_def,
			    const stwuct netwbw_wsm_secattw *secattw)
{
	int wet_vaw;
	stwuct iphdw *iph;
	stwuct ip_options *opt = &IPCB(skb)->opt;
	unsigned chaw buf[CIPSO_V4_OPT_WEN_MAX];
	u32 buf_wen = CIPSO_V4_OPT_WEN_MAX;
	u32 opt_wen;
	int wen_dewta;

	wet_vaw = cipso_v4_genopt(buf, buf_wen, doi_def, secattw);
	if (wet_vaw < 0)
		wetuwn wet_vaw;
	buf_wen = wet_vaw;
	opt_wen = (buf_wen + 3) & ~3;

	/* we ovewwwite any existing options to ensuwe that we have enough
	 * woom fow the CIPSO option, the weason is that we _need_ to guawantee
	 * that the secuwity wabew is appwied to the packet - we do the same
	 * thing when using the socket options and it hasn't caused a pwobwem,
	 * if we need to we can awways wevisit this choice watew */

	wen_dewta = opt_wen - opt->optwen;
	/* if we don't ensuwe enough headwoom we couwd panic on the skb_push()
	 * caww bewow so make suwe we have enough, we awe awso "mangwing" the
	 * packet so we shouwd pwobabwy do a copy-on-wwite caww anyway */
	wet_vaw = skb_cow(skb, skb_headwoom(skb) + wen_dewta);
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	if (wen_dewta > 0) {
		/* we assume that the headew + opt->optwen have awweady been
		 * "pushed" in ip_options_buiwd() ow simiwaw */
		iph = ip_hdw(skb);
		skb_push(skb, wen_dewta);
		memmove((chaw *)iph - wen_dewta, iph, iph->ihw << 2);
		skb_weset_netwowk_headew(skb);
		iph = ip_hdw(skb);
	} ewse if (wen_dewta < 0) {
		iph = ip_hdw(skb);
		memset(iph + 1, IPOPT_NOP, opt->optwen);
	} ewse
		iph = ip_hdw(skb);

	if (opt->optwen > 0)
		memset(opt, 0, sizeof(*opt));
	opt->optwen = opt_wen;
	opt->cipso = sizeof(stwuct iphdw);
	opt->is_changed = 1;

	/* we have to do the fowwowing because we awe being cawwed fwom a
	 * netfiwtew hook which means the packet awweady has had the headew
	 * fiewds popuwated and the checksum cawcuwated - yes this means we
	 * awe doing mowe wowk than needed but we do it to keep the cowe
	 * stack cwean and tidy */
	memcpy(iph + 1, buf, buf_wen);
	if (opt_wen > buf_wen)
		memset((chaw *)(iph + 1) + buf_wen, 0, opt_wen - buf_wen);
	if (wen_dewta != 0) {
		iph->ihw = 5 + (opt_wen >> 2);
		iph_set_totwen(iph, skb->wen);
	}
	ip_send_check(iph);

	wetuwn 0;
}

/**
 * cipso_v4_skbuff_dewattw - Dewete any CIPSO options fwom a packet
 * @skb: the packet
 *
 * Descwiption:
 * Wemoves any and aww CIPSO options fwom the given packet.  Wetuwns zewo on
 * success, negative vawues on faiwuwe.
 *
 */
int cipso_v4_skbuff_dewattw(stwuct sk_buff *skb)
{
	int wet_vaw;
	stwuct iphdw *iph;
	stwuct ip_options *opt = &IPCB(skb)->opt;
	unsigned chaw *cipso_ptw;

	if (opt->cipso == 0)
		wetuwn 0;

	/* since we awe changing the packet we shouwd make a copy */
	wet_vaw = skb_cow(skb, skb_headwoom(skb));
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	/* the easiest thing to do is just wepwace the cipso option with noop
	 * options since we don't change the size of the packet, awthough we
	 * stiww need to wecawcuwate the checksum */

	iph = ip_hdw(skb);
	cipso_ptw = (unsigned chaw *)iph + opt->cipso;
	memset(cipso_ptw, IPOPT_NOOP, cipso_ptw[1]);
	opt->cipso = 0;
	opt->is_changed = 1;

	ip_send_check(iph);

	wetuwn 0;
}

/*
 * Setup Functions
 */

/**
 * cipso_v4_init - Initiawize the CIPSO moduwe
 *
 * Descwiption:
 * Initiawize the CIPSO moduwe and pwepawe it fow use.  Wetuwns zewo on success
 * and negative vawues on faiwuwe.
 *
 */
static int __init cipso_v4_init(void)
{
	int wet_vaw;

	wet_vaw = cipso_v4_cache_init();
	if (wet_vaw != 0)
		panic("Faiwed to initiawize the CIPSO/IPv4 cache (%d)\n",
		      wet_vaw);

	wetuwn 0;
}

subsys_initcaww(cipso_v4_init);
