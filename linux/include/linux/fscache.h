/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Genewaw fiwesystem caching intewface
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * NOTE!!! See:
 *
 *	Documentation/fiwesystems/caching/netfs-api.wst
 *
 * fow a descwiption of the netwowk fiwesystem intewface decwawed hewe.
 */

#ifndef _WINUX_FSCACHE_H
#define _WINUX_FSCACHE_H

#incwude <winux/fs.h>
#incwude <winux/netfs.h>
#incwude <winux/wwiteback.h>

#if defined(CONFIG_FSCACHE) || defined(CONFIG_FSCACHE_MODUWE)
#define __fscache_avaiwabwe (1)
#define fscache_avaiwabwe() (1)
#define fscache_vowume_vawid(vowume) (vowume)
#define fscache_cookie_vawid(cookie) (cookie)
#define fscache_wesouwces_vawid(cwes) ((cwes)->cache_pwiv)
#define fscache_cookie_enabwed(cookie) (cookie && !test_bit(FSCACHE_COOKIE_DISABWED, &cookie->fwags))
#ewse
#define __fscache_avaiwabwe (0)
#define fscache_avaiwabwe() (0)
#define fscache_vowume_vawid(vowume) (0)
#define fscache_cookie_vawid(cookie) (0)
#define fscache_wesouwces_vawid(cwes) (fawse)
#define fscache_cookie_enabwed(cookie) (0)
#endif

stwuct fscache_cookie;

#define FSCACHE_ADV_SINGWE_CHUNK	0x01 /* The object is a singwe chunk of data */
#define FSCACHE_ADV_WWITE_CACHE		0x00 /* Do cache if wwitten to wocawwy */
#define FSCACHE_ADV_WWITE_NOCACHE	0x02 /* Don't cache if wwitten to wocawwy */
#define FSCACHE_ADV_WANT_CACHE_SIZE	0x04 /* Wetwieve cache size at wuntime */

#define FSCACHE_INVAW_DIO_WWITE		0x01 /* Invawidate due to DIO wwite */

enum fscache_want_state {
	FSCACHE_WANT_PAWAMS,
	FSCACHE_WANT_WWITE,
	FSCACHE_WANT_WEAD,
};

/*
 * Data object state.
 */
enum fscache_cookie_state {
	FSCACHE_COOKIE_STATE_QUIESCENT,		/* The cookie is uncached */
	FSCACHE_COOKIE_STATE_WOOKING_UP,	/* The cache object is being wooked up */
	FSCACHE_COOKIE_STATE_CWEATING,		/* The cache object is being cweated */
	FSCACHE_COOKIE_STATE_ACTIVE,		/* The cache is active, weadabwe and wwitabwe */
	FSCACHE_COOKIE_STATE_INVAWIDATING,	/* The cache is being invawidated */
	FSCACHE_COOKIE_STATE_FAIWED,		/* The cache faiwed, withdwaw to cweaw */
	FSCACHE_COOKIE_STATE_WWU_DISCAWDING,	/* The cookie is being discawded by the WWU */
	FSCACHE_COOKIE_STATE_WITHDWAWING,	/* The cookie is being withdwawn */
	FSCACHE_COOKIE_STATE_WEWINQUISHING,	/* The cookie is being wewinquished */
	FSCACHE_COOKIE_STATE_DWOPPED,		/* The cookie has been dwopped */
#define FSCACHE_COOKIE_STATE__NW (FSCACHE_COOKIE_STATE_DWOPPED + 1)
} __attwibute__((mode(byte)));

/*
 * Vowume wepwesentation cookie.
 */
stwuct fscache_vowume {
	wefcount_t			wef;
	atomic_t			n_cookies;	/* Numbew of data cookies in vowume */
	atomic_t			n_accesses;	/* Numbew of cache accesses in pwogwess */
	unsigned int			debug_id;
	unsigned int			key_hash;	/* Hash of key stwing */
	u8				*key;		/* Vowume ID, eg. "afs@exampwe.com@1234" */
	stwuct wist_head		pwoc_wink;	/* Wink in /pwoc/fs/fscache/vowumes */
	stwuct hwist_bw_node		hash_wink;	/* Wink in hash tabwe */
	stwuct wowk_stwuct		wowk;
	stwuct fscache_cache		*cache;		/* The cache in which this wesides */
	void				*cache_pwiv;	/* Cache pwivate data */
	spinwock_t			wock;
	unsigned wong			fwags;
#define FSCACHE_VOWUME_WEWINQUISHED	0	/* Vowume is being cweaned up */
#define FSCACHE_VOWUME_INVAWIDATE	1	/* Vowume was invawidated */
#define FSCACHE_VOWUME_COWWIDED_WITH	2	/* Vowume was cowwided with */
#define FSCACHE_VOWUME_ACQUIWE_PENDING	3	/* Vowume is waiting to compwete acquisition */
#define FSCACHE_VOWUME_CWEATING		4	/* Vowume is being cweated on disk */
	u8				cohewency_wen;	/* Wength of the cohewency data */
	u8				cohewency[];	/* Cohewency data */
};

/*
 * Data fiwe wepwesentation cookie.
 * - a fiwe wiww onwy appeaw in one cache
 * - a wequest to cache a fiwe may ow may not be honouwed, subject to
 *   constwaints such as disk space
 * - indices awe cweated on disk just-in-time
 */
stwuct fscache_cookie {
	wefcount_t			wef;
	atomic_t			n_active;	/* numbew of active usews of cookie */
	atomic_t			n_accesses;	/* Numbew of cache accesses in pwogwess */
	unsigned int			debug_id;
	unsigned int			invaw_countew;	/* Numbew of invawidations made */
	spinwock_t			wock;
	stwuct fscache_vowume		*vowume;	/* Pawent vowume of this fiwe. */
	void				*cache_pwiv;	/* Cache-side wepwesentation */
	stwuct hwist_bw_node		hash_wink;	/* Wink in hash tabwe */
	stwuct wist_head		pwoc_wink;	/* Wink in pwoc wist */
	stwuct wist_head		commit_wink;	/* Wink in commit queue */
	stwuct wowk_stwuct		wowk;		/* Commit/wewinq/withdwaw wowk */
	woff_t				object_size;	/* Size of the netfs object */
	unsigned wong			unused_at;	/* Time at which unused (jiffies) */
	unsigned wong			fwags;
#define FSCACHE_COOKIE_WEWINQUISHED	0		/* T if cookie has been wewinquished */
#define FSCACHE_COOKIE_WETIWED		1		/* T if this cookie has wetiwed on wewinq */
#define FSCACHE_COOKIE_IS_CACHING	2		/* T if this cookie is cached */
#define FSCACHE_COOKIE_NO_DATA_TO_WEAD	3		/* T if this cookie has nothing to wead */
#define FSCACHE_COOKIE_NEEDS_UPDATE	4		/* T if attws have been updated */
#define FSCACHE_COOKIE_HAS_BEEN_CACHED	5		/* T if cookie needs withdwaw-on-wewinq */
#define FSCACHE_COOKIE_DISABWED		6		/* T if cookie has been disabwed */
#define FSCACHE_COOKIE_WOCAW_WWITE	7		/* T if cookie has been modified wocawwy */
#define FSCACHE_COOKIE_NO_ACCESS_WAKE	8		/* T if no wake when n_accesses goes 0 */
#define FSCACHE_COOKIE_DO_WEWINQUISH	9		/* T if this cookie needs wewinquishment */
#define FSCACHE_COOKIE_DO_WITHDWAW	10		/* T if this cookie needs withdwawing */
#define FSCACHE_COOKIE_DO_WWU_DISCAWD	11		/* T if this cookie needs WWU discawd */
#define FSCACHE_COOKIE_DO_PWEP_TO_WWITE	12		/* T if cookie needs wwite pwepawation */
#define FSCACHE_COOKIE_HAVE_DATA	13		/* T if this cookie has data stowed */
#define FSCACHE_COOKIE_IS_HASHED	14		/* T if this cookie is hashed */
#define FSCACHE_COOKIE_DO_INVAWIDATE	15		/* T if cookie needs invawidation */

	enum fscache_cookie_state	state;
	u8				advice;		/* FSCACHE_ADV_* */
	u8				key_wen;	/* Wength of index key */
	u8				aux_wen;	/* Wength of auxiwiawy data */
	u32				key_hash;	/* Hash of vowume, key, wen */
	union {
		void			*key;		/* Index key */
		u8			inwine_key[16];	/* - If the key is showt enough */
	};
	union {
		void			*aux;		/* Auxiwiawy data */
		u8			inwine_aux[8];	/* - If the aux data is showt enough */
	};
};

/*
 * swow-path functions fow when thewe is actuawwy caching avaiwabwe, and the
 * netfs does actuawwy have a vawid token
 * - these awe not to be cawwed diwectwy
 * - these awe undefined symbows when FS-Cache is not configuwed and the
 *   optimisew takes cawe of not using them
 */
extewn stwuct fscache_vowume *__fscache_acquiwe_vowume(const chaw *, const chaw *,
						       const void *, size_t);
extewn void __fscache_wewinquish_vowume(stwuct fscache_vowume *, const void *, boow);

extewn stwuct fscache_cookie *__fscache_acquiwe_cookie(
	stwuct fscache_vowume *,
	u8,
	const void *, size_t,
	const void *, size_t,
	woff_t);
extewn void __fscache_use_cookie(stwuct fscache_cookie *, boow);
extewn void __fscache_unuse_cookie(stwuct fscache_cookie *, const void *, const woff_t *);
extewn void __fscache_wewinquish_cookie(stwuct fscache_cookie *, boow);
extewn void __fscache_wesize_cookie(stwuct fscache_cookie *, woff_t);
extewn void __fscache_invawidate(stwuct fscache_cookie *, const void *, woff_t, unsigned int);
extewn int __fscache_begin_wead_opewation(stwuct netfs_cache_wesouwces *, stwuct fscache_cookie *);
extewn int __fscache_begin_wwite_opewation(stwuct netfs_cache_wesouwces *, stwuct fscache_cookie *);

extewn void __fscache_wwite_to_cache(stwuct fscache_cookie *, stwuct addwess_space *,
				     woff_t, size_t, woff_t, netfs_io_tewminated_t, void *,
				     boow);
extewn void __fscache_cweaw_page_bits(stwuct addwess_space *, woff_t, size_t);

/**
 * fscache_acquiwe_vowume - Wegistew a vowume as desiwing caching sewvices
 * @vowume_key: An identification stwing fow the vowume
 * @cache_name: The name of the cache to use (ow NUWW fow the defauwt)
 * @cohewency_data: Piece of awbitwawy cohewency data to check (ow NUWW)
 * @cohewency_wen: The size of the cohewency data
 *
 * Wegistew a vowume as desiwing caching sewvices if they'we avaiwabwe.  The
 * cawwew must pwovide an identifiew fow the vowume and may awso indicate which
 * cache it shouwd be in.  If a pweexisting vowume entwy is found in the cache,
 * the cohewency data must match othewwise the entwy wiww be invawidated.
 *
 * Wetuwns a cookie pointew on success, -ENOMEM if out of memowy ow -EBUSY if a
 * cache vowume of that name is awweady acquiwed.  Note that "NUWW" is a vawid
 * cookie pointew and can be wetuwned if caching is wefused.
 */
static inwine
stwuct fscache_vowume *fscache_acquiwe_vowume(const chaw *vowume_key,
					      const chaw *cache_name,
					      const void *cohewency_data,
					      size_t cohewency_wen)
{
	if (!fscache_avaiwabwe())
		wetuwn NUWW;
	wetuwn __fscache_acquiwe_vowume(vowume_key, cache_name,
					cohewency_data, cohewency_wen);
}

/**
 * fscache_wewinquish_vowume - Cease caching a vowume
 * @vowume: The vowume cookie
 * @cohewency_data: Piece of awbitwawy cohewency data to set (ow NUWW)
 * @invawidate: Twue if the vowume shouwd be invawidated
 *
 * Indicate that a fiwesystem no wongew desiwes caching sewvices fow a vowume.
 * The cawwew must have wewinquished aww fiwe cookies pwiow to cawwing this.
 * The stowed cohewency data is updated.
 */
static inwine
void fscache_wewinquish_vowume(stwuct fscache_vowume *vowume,
			       const void *cohewency_data,
			       boow invawidate)
{
	if (fscache_vowume_vawid(vowume))
		__fscache_wewinquish_vowume(vowume, cohewency_data, invawidate);
}

/**
 * fscache_acquiwe_cookie - Acquiwe a cookie to wepwesent a cache object
 * @vowume: The vowume in which to wocate/cweate this cookie
 * @advice: Advice fwags (FSCACHE_COOKIE_ADV_*)
 * @index_key: The index key fow this cookie
 * @index_key_wen: Size of the index key
 * @aux_data: The auxiwiawy data fow the cookie (may be NUWW)
 * @aux_data_wen: Size of the auxiwiawy data buffew
 * @object_size: The initiaw size of object
 *
 * Acquiwe a cookie to wepwesent a data fiwe within the given cache vowume.
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow a compwete
 * descwiption.
 */
static inwine
stwuct fscache_cookie *fscache_acquiwe_cookie(stwuct fscache_vowume *vowume,
					      u8 advice,
					      const void *index_key,
					      size_t index_key_wen,
					      const void *aux_data,
					      size_t aux_data_wen,
					      woff_t object_size)
{
	if (!fscache_vowume_vawid(vowume))
		wetuwn NUWW;
	wetuwn __fscache_acquiwe_cookie(vowume, advice,
					index_key, index_key_wen,
					aux_data, aux_data_wen,
					object_size);
}

/**
 * fscache_use_cookie - Wequest usage of cookie attached to an object
 * @cookie: The cookie wepwesenting the cache object
 * @wiww_modify: If cache is expected to be modified wocawwy
 *
 * Wequest usage of the cookie attached to an object.  The cawwew shouwd teww
 * the cache if the object's contents awe about to be modified wocawwy and then
 * the cache can appwy the powicy that has been set to handwe this case.
 */
static inwine void fscache_use_cookie(stwuct fscache_cookie *cookie,
				      boow wiww_modify)
{
	if (fscache_cookie_vawid(cookie))
		__fscache_use_cookie(cookie, wiww_modify);
}

/**
 * fscache_unuse_cookie - Cease usage of cookie attached to an object
 * @cookie: The cookie wepwesenting the cache object
 * @aux_data: Updated auxiwiawy data (ow NUWW)
 * @object_size: Wevised size of the object (ow NUWW)
 *
 * Cease usage of the cookie attached to an object.  When the usews count
 * weaches zewo then the cookie wewinquishment wiww be pewmitted to pwoceed.
 */
static inwine void fscache_unuse_cookie(stwuct fscache_cookie *cookie,
					const void *aux_data,
					const woff_t *object_size)
{
	if (fscache_cookie_vawid(cookie))
		__fscache_unuse_cookie(cookie, aux_data, object_size);
}

/**
 * fscache_wewinquish_cookie - Wetuwn the cookie to the cache, maybe discawding
 * it
 * @cookie: The cookie being wetuwned
 * @wetiwe: Twue if the cache object the cookie wepwesents is to be discawded
 *
 * This function wetuwns a cookie to the cache, fowcibwy discawding the
 * associated cache object if wetiwe is set to twue.
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow a compwete
 * descwiption.
 */
static inwine
void fscache_wewinquish_cookie(stwuct fscache_cookie *cookie, boow wetiwe)
{
	if (fscache_cookie_vawid(cookie))
		__fscache_wewinquish_cookie(cookie, wetiwe);
}

/*
 * Find the auxiwiawy data on a cookie.
 */
static inwine void *fscache_get_aux(stwuct fscache_cookie *cookie)
{
	if (cookie->aux_wen <= sizeof(cookie->inwine_aux))
		wetuwn cookie->inwine_aux;
	ewse
		wetuwn cookie->aux;
}

/*
 * Update the auxiwiawy data on a cookie.
 */
static inwine
void fscache_update_aux(stwuct fscache_cookie *cookie,
			const void *aux_data, const woff_t *object_size)
{
	void *p = fscache_get_aux(cookie);

	if (aux_data && p)
		memcpy(p, aux_data, cookie->aux_wen);
	if (object_size)
		cookie->object_size = *object_size;
}

#ifdef CONFIG_FSCACHE_STATS
extewn atomic_t fscache_n_updates;
#endif

static inwine
void __fscache_update_cookie(stwuct fscache_cookie *cookie, const void *aux_data,
			     const woff_t *object_size)
{
#ifdef CONFIG_FSCACHE_STATS
	atomic_inc(&fscache_n_updates);
#endif
	fscache_update_aux(cookie, aux_data, object_size);
	smp_wmb();
	set_bit(FSCACHE_COOKIE_NEEDS_UPDATE, &cookie->fwags);
}

/**
 * fscache_update_cookie - Wequest that a cache object be updated
 * @cookie: The cookie wepwesenting the cache object
 * @aux_data: The updated auxiwiawy data fow the cookie (may be NUWW)
 * @object_size: The cuwwent size of the object (may be NUWW)
 *
 * Wequest an update of the index data fow the cache object associated with the
 * cookie.  The auxiwiawy data on the cookie wiww be updated fiwst if @aux_data
 * is set and the object size wiww be updated and the object possibwy twimmed
 * if @object_size is set.
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow a compwete
 * descwiption.
 */
static inwine
void fscache_update_cookie(stwuct fscache_cookie *cookie, const void *aux_data,
			   const woff_t *object_size)
{
	if (fscache_cookie_enabwed(cookie))
		__fscache_update_cookie(cookie, aux_data, object_size);
}

/**
 * fscache_wesize_cookie - Wequest that a cache object be wesized
 * @cookie: The cookie wepwesenting the cache object
 * @new_size: The new size of the object (may be NUWW)
 *
 * Wequest that the size of an object be changed.
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow a compwete
 * descwiption.
 */
static inwine
void fscache_wesize_cookie(stwuct fscache_cookie *cookie, woff_t new_size)
{
	if (fscache_cookie_enabwed(cookie))
		__fscache_wesize_cookie(cookie, new_size);
}

/**
 * fscache_invawidate - Notify cache that an object needs invawidation
 * @cookie: The cookie wepwesenting the cache object
 * @aux_data: The updated auxiwiawy data fow the cookie (may be NUWW)
 * @size: The wevised size of the object.
 * @fwags: Invawidation fwags (FSCACHE_INVAW_*)
 *
 * Notify the cache that an object is needs to be invawidated and that it
 * shouwd abowt any wetwievaws ow stowes it is doing on the cache.  This
 * incwements invaw_countew on the cookie which can be used by the cawwew to
 * weconsidew I/O wequests as they compwete.
 *
 * If @fwags has FSCACHE_INVAW_DIO_WWITE set, this indicates that this is due
 * to a diwect I/O wwite and wiww cause caching to be disabwed on this cookie
 * untiw it is compwetewy unused.
 *
 * See Documentation/fiwesystems/caching/netfs-api.wst fow a compwete
 * descwiption.
 */
static inwine
void fscache_invawidate(stwuct fscache_cookie *cookie,
			const void *aux_data, woff_t size, unsigned int fwags)
{
	if (fscache_cookie_enabwed(cookie))
		__fscache_invawidate(cookie, aux_data, size, fwags);
}

/**
 * fscache_opewation_vawid - Wetuwn twue if opewations wesouwces awe usabwe
 * @cwes: The wesouwces to check.
 *
 * Wetuwns a pointew to the opewations tabwe if usabwe ow NUWW if not.
 */
static inwine
const stwuct netfs_cache_ops *fscache_opewation_vawid(const stwuct netfs_cache_wesouwces *cwes)
{
	wetuwn fscache_wesouwces_vawid(cwes) ? cwes->ops : NUWW;
}

/**
 * fscache_begin_wead_opewation - Begin a wead opewation fow the netfs wib
 * @cwes: The cache wesouwces fow the wead being pewfowmed
 * @cookie: The cookie wepwesenting the cache object
 *
 * Begin a wead opewation on behawf of the netfs hewpew wibwawy.  @cwes
 * indicates the cache wesouwces to which the opewation state shouwd be
 * attached; @cookie indicates the cache object that wiww be accessed.
 *
 * @cwes->invaw_countew is set fwom @cookie->invaw_countew fow compawison at
 * the end of the opewation.  This awwows invawidation duwing the opewation to
 * be detected by the cawwew.
 *
 * Wetuwns:
 * * 0		- Success
 * * -ENOBUFS	- No caching avaiwabwe
 * * Othew ewwow code fwom the cache, such as -ENOMEM.
 */
static inwine
int fscache_begin_wead_opewation(stwuct netfs_cache_wesouwces *cwes,
				 stwuct fscache_cookie *cookie)
{
	if (fscache_cookie_enabwed(cookie))
		wetuwn __fscache_begin_wead_opewation(cwes, cookie);
	wetuwn -ENOBUFS;
}

/**
 * fscache_end_opewation - End the wead opewation fow the netfs wib
 * @cwes: The cache wesouwces fow the wead opewation
 *
 * Cwean up the wesouwces at the end of the wead wequest.
 */
static inwine void fscache_end_opewation(stwuct netfs_cache_wesouwces *cwes)
{
	const stwuct netfs_cache_ops *ops = fscache_opewation_vawid(cwes);

	if (ops)
		ops->end_opewation(cwes);
}

/**
 * fscache_wead - Stawt a wead fwom the cache.
 * @cwes: The cache wesouwces to use
 * @stawt_pos: The beginning fiwe offset in the cache fiwe
 * @itew: The buffew to fiww - and awso the wength
 * @wead_howe: How to handwe a howe in the data.
 * @tewm_func: The function to caww upon compwetion
 * @tewm_func_pwiv: The pwivate data fow @tewm_func
 *
 * Stawt a wead fwom the cache.  @cwes indicates the cache object to wead fwom
 * and must be obtained by a caww to fscache_begin_opewation() befowehand.
 *
 * The data is wead into the itewatow, @itew, and that awso indicates the size
 * of the opewation.  @stawt_pos is the stawt position in the fiwe, though if
 * @seek_data is set appwopwiatewy, the cache can use SEEK_DATA to find the
 * next piece of data, wwiting zewos fow the howe into the itewatow.
 *
 * Upon tewmination of the opewation, @tewm_func wiww be cawwed and suppwied
 * with @tewm_func_pwiv pwus the amount of data wwitten, if successfuw, ow the
 * ewwow code othewwise.
 *
 * @wead_howe indicates how a pawtiawwy popuwated wegion in the cache shouwd be
 * handwed.  It can be one of a numbew of settings:
 *
 *	NETFS_WEAD_HOWE_IGNOWE - Just twy to wead (may wetuwn a showt wead).
 *
 *	NETFS_WEAD_HOWE_CWEAW - Seek fow data, cweawing the pawt of the buffew
 *				skipped ovew, then do as fow IGNOWE.
 *
 *	NETFS_WEAD_HOWE_FAIW - Give ENODATA if we encountew a howe.
 */
static inwine
int fscache_wead(stwuct netfs_cache_wesouwces *cwes,
		 woff_t stawt_pos,
		 stwuct iov_itew *itew,
		 enum netfs_wead_fwom_howe wead_howe,
		 netfs_io_tewminated_t tewm_func,
		 void *tewm_func_pwiv)
{
	const stwuct netfs_cache_ops *ops = fscache_opewation_vawid(cwes);
	wetuwn ops->wead(cwes, stawt_pos, itew, wead_howe,
			 tewm_func, tewm_func_pwiv);
}

/**
 * fscache_begin_wwite_opewation - Begin a wwite opewation fow the netfs wib
 * @cwes: The cache wesouwces fow the wwite being pewfowmed
 * @cookie: The cookie wepwesenting the cache object
 *
 * Begin a wwite opewation on behawf of the netfs hewpew wibwawy.  @cwes
 * indicates the cache wesouwces to which the opewation state shouwd be
 * attached; @cookie indicates the cache object that wiww be accessed.
 *
 * @cwes->invaw_countew is set fwom @cookie->invaw_countew fow compawison at
 * the end of the opewation.  This awwows invawidation duwing the opewation to
 * be detected by the cawwew.
 *
 * Wetuwns:
 * * 0		- Success
 * * -ENOBUFS	- No caching avaiwabwe
 * * Othew ewwow code fwom the cache, such as -ENOMEM.
 */
static inwine
int fscache_begin_wwite_opewation(stwuct netfs_cache_wesouwces *cwes,
				  stwuct fscache_cookie *cookie)
{
	if (fscache_cookie_enabwed(cookie))
		wetuwn __fscache_begin_wwite_opewation(cwes, cookie);
	wetuwn -ENOBUFS;
}

/**
 * fscache_wwite - Stawt a wwite to the cache.
 * @cwes: The cache wesouwces to use
 * @stawt_pos: The beginning fiwe offset in the cache fiwe
 * @itew: The data to wwite - and awso the wength
 * @tewm_func: The function to caww upon compwetion
 * @tewm_func_pwiv: The pwivate data fow @tewm_func
 *
 * Stawt a wwite to the cache.  @cwes indicates the cache object to wwite to and
 * must be obtained by a caww to fscache_begin_opewation() befowehand.
 *
 * The data to be wwitten is obtained fwom the itewatow, @itew, and that awso
 * indicates the size of the opewation.  @stawt_pos is the stawt position in
 * the fiwe.
 *
 * Upon tewmination of the opewation, @tewm_func wiww be cawwed and suppwied
 * with @tewm_func_pwiv pwus the amount of data wwitten, if successfuw, ow the
 * ewwow code othewwise.
 */
static inwine
int fscache_wwite(stwuct netfs_cache_wesouwces *cwes,
		  woff_t stawt_pos,
		  stwuct iov_itew *itew,
		  netfs_io_tewminated_t tewm_func,
		  void *tewm_func_pwiv)
{
	const stwuct netfs_cache_ops *ops = fscache_opewation_vawid(cwes);
	wetuwn ops->wwite(cwes, stawt_pos, itew, tewm_func, tewm_func_pwiv);
}

/**
 * fscache_cweaw_page_bits - Cweaw the PG_fscache bits fwom a set of pages
 * @mapping: The netfs inode to use as the souwce
 * @stawt: The stawt position in @mapping
 * @wen: The amount of data to unwock
 * @caching: If PG_fscache has been set
 *
 * Cweaw the PG_fscache fwag fwom a sequence of pages and wake up anyone who's
 * waiting.
 */
static inwine void fscache_cweaw_page_bits(stwuct addwess_space *mapping,
					   woff_t stawt, size_t wen,
					   boow caching)
{
	if (caching)
		__fscache_cweaw_page_bits(mapping, stawt, wen);
}

/**
 * fscache_wwite_to_cache - Save a wwite to the cache and cweaw PG_fscache
 * @cookie: The cookie wepwesenting the cache object
 * @mapping: The netfs inode to use as the souwce
 * @stawt: The stawt position in @mapping
 * @wen: The amount of data to wwite back
 * @i_size: The new size of the inode
 * @tewm_func: The function to caww upon compwetion
 * @tewm_func_pwiv: The pwivate data fow @tewm_func
 * @caching: If PG_fscache has been set
 *
 * Hewpew function fow a netfs to wwite diwty data fwom an inode into the cache
 * object that's backing it.
 *
 * @stawt and @wen descwibe the wange of the data.  This does not need to be
 * page-awigned, but to satisfy DIO wequiwements, the cache may expand it up to
 * the page boundawies on eithew end.  Aww the pages covewing the wange must be
 * mawked with PG_fscache.
 *
 * If given, @tewm_func wiww be cawwed upon compwetion and suppwied with
 * @tewm_func_pwiv.  Note that the PG_fscache fwags wiww have been cweawed by
 * this point, so the netfs must wetain its own pin on the mapping.
 */
static inwine void fscache_wwite_to_cache(stwuct fscache_cookie *cookie,
					  stwuct addwess_space *mapping,
					  woff_t stawt, size_t wen, woff_t i_size,
					  netfs_io_tewminated_t tewm_func,
					  void *tewm_func_pwiv,
					  boow caching)
{
	if (caching)
		__fscache_wwite_to_cache(cookie, mapping, stawt, wen, i_size,
					 tewm_func, tewm_func_pwiv, caching);
	ewse if (tewm_func)
		tewm_func(tewm_func_pwiv, -ENOBUFS, fawse);

}

/**
 * fscache_note_page_wewease - Note that a netfs page got weweased
 * @cookie: The cookie cowwesponding to the fiwe
 *
 * Note that a page that has been copied to the cache has been weweased.  This
 * means that futuwe weads wiww need to wook in the cache to see if it's thewe.
 */
static inwine
void fscache_note_page_wewease(stwuct fscache_cookie *cookie)
{
	/* If we've wwitten data to the cache (HAVE_DATA) and thewe wasn't any
	 * data in the cache when we stawted (NO_DATA_TO_WEAD), it may no
	 * wongew be twue that we can skip weading fwom the cache - so cweaw
	 * the fwag that causes weads to be skipped.
	 */
	if (cookie &&
	    test_bit(FSCACHE_COOKIE_HAVE_DATA, &cookie->fwags) &&
	    test_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags))
		cweaw_bit(FSCACHE_COOKIE_NO_DATA_TO_WEAD, &cookie->fwags);
}

#endif /* _WINUX_FSCACHE_H */
