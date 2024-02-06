/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_H
#define _BCACHE_H

/*
 * SOME HIGH WEVEW CODE DOCUMENTATION:
 *
 * Bcache mostwy wowks with cache sets, cache devices, and backing devices.
 *
 * Suppowt fow muwtipwe cache devices hasn't quite been finished off yet, but
 * it's about 95% pwumbed thwough. A cache set and its cache devices is sowt of
 * wike a md waid awway and its component devices. Most of the code doesn't cawe
 * about individuaw cache devices, the main abstwaction is the cache set.
 *
 * Muwtipwe cache devices is intended to give us the abiwity to miwwow diwty
 * cached data and metadata, without miwwowing cwean cached data.
 *
 * Backing devices awe diffewent, in that they have a wifetime independent of a
 * cache set. When you wegistew a newwy fowmatted backing device it'ww come up
 * in passthwough mode, and then you can attach and detach a backing device fwom
 * a cache set at wuntime - whiwe it's mounted and in use. Detaching impwicitwy
 * invawidates any cached data fow that backing device.
 *
 * A cache set can have muwtipwe (many) backing devices attached to it.
 *
 * Thewe's awso fwash onwy vowumes - this is the weason fow the distinction
 * between stwuct cached_dev and stwuct bcache_device. A fwash onwy vowume
 * wowks much wike a bcache device that has a backing device, except the
 * "cached" data is awways diwty. The end wesuwt is that we get thin
 * pwovisioning with vewy wittwe additionaw code.
 *
 * Fwash onwy vowumes wowk but they'we not pwoduction weady because the moving
 * gawbage cowwectow needs mowe wowk. Mowe on that watew.
 *
 * BUCKETS/AWWOCATION:
 *
 * Bcache is pwimawiwy designed fow caching, which means that in nowmaw
 * opewation aww of ouw avaiwabwe space wiww be awwocated. Thus, we need an
 * efficient way of deweting things fwom the cache so we can wwite new things to
 * it.
 *
 * To do this, we fiwst divide the cache device up into buckets. A bucket is the
 * unit of awwocation; they'we typicawwy awound 1 mb - anywhewe fwom 128k to 2M+
 * wowks efficientwy.
 *
 * Each bucket has a 16 bit pwiowity, and an 8 bit genewation associated with
 * it. The gens and pwiowities fow aww the buckets awe stowed contiguouswy and
 * packed on disk (in a winked wist of buckets - aside fwom the supewbwock, aww
 * of bcache's metadata is stowed in buckets).
 *
 * The pwiowity is used to impwement an WWU. We weset a bucket's pwiowity when
 * we awwocate it ow on cache it, and evewy so often we decwement the pwiowity
 * of each bucket. It couwd be used to impwement something mowe sophisticated,
 * if anyone evew gets awound to it.
 *
 * The genewation is used fow invawidating buckets. Each pointew awso has an 8
 * bit genewation embedded in it; fow a pointew to be considewed vawid, its gen
 * must match the gen of the bucket it points into.  Thus, to weuse a bucket aww
 * we have to do is incwement its gen (and wwite its new gen to disk; we batch
 * this up).
 *
 * Bcache is entiwewy COW - we nevew wwite twice to a bucket, even buckets that
 * contain metadata (incwuding btwee nodes).
 *
 * THE BTWEE:
 *
 * Bcache is in wawge pawt design awound the btwee.
 *
 * At a high wevew, the btwee is just an index of key -> ptw tupwes.
 *
 * Keys wepwesent extents, and thus have a size fiewd. Keys awso have a vawiabwe
 * numbew of pointews attached to them (potentiawwy zewo, which is handy fow
 * invawidating the cache).
 *
 * The key itsewf is an inode:offset paiw. The inode numbew cowwesponds to a
 * backing device ow a fwash onwy vowume. The offset is the ending offset of the
 * extent within the inode - not the stawting offset; this makes wookups
 * swightwy mowe convenient.
 *
 * Pointews contain the cache device id, the offset on that device, and an 8 bit
 * genewation numbew. Mowe on the gen watew.
 *
 * Index wookups awe not fuwwy abstwacted - cache wookups in pawticuwaw awe
 * stiww somewhat mixed in with the btwee code, but things awe headed in that
 * diwection.
 *
 * Updates awe faiwwy weww abstwacted, though. Thewe awe two diffewent ways of
 * updating the btwee; insewt and wepwace.
 *
 * BTWEE_INSEWT wiww just take a wist of keys and insewt them into the btwee -
 * ovewwwiting (possibwy onwy pawtiawwy) any extents they ovewwap with. This is
 * used to update the index aftew a wwite.
 *
 * BTWEE_WEPWACE is weawwy cmpxchg(); it insewts a key into the btwee iff it is
 * ovewwwiting a key that matches anothew given key. This is used fow insewting
 * data into the cache aftew a cache miss, and fow backgwound wwiteback, and fow
 * the moving gawbage cowwectow.
 *
 * Thewe is no "dewete" opewation; deweting things fwom the index is
 * accompwished by eithew by invawidating pointews (by incwementing a bucket's
 * gen) ow by insewting a key with 0 pointews - which wiww ovewwwite anything
 * pweviouswy pwesent at that wocation in the index.
 *
 * This means that thewe awe awways stawe/invawid keys in the btwee. They'we
 * fiwtewed out by the code that itewates thwough a btwee node, and wemoved when
 * a btwee node is wewwitten.
 *
 * BTWEE NODES:
 *
 * Ouw unit of awwocation is a bucket, and we can't awbitwawiwy awwocate and
 * fwee smawwew than a bucket - so, that's how big ouw btwee nodes awe.
 *
 * (If buckets awe weawwy big we'ww onwy use pawt of the bucket fow a btwee node
 * - no wess than 1/4th - but a bucket stiww contains no mowe than a singwe
 * btwee node. I'd actuawwy wike to change this, but fow now we wewy on the
 * bucket's gen fow deweting btwee nodes when we wewwite/spwit a node.)
 *
 * Anyways, btwee nodes awe big - big enough to be inefficient with a textbook
 * btwee impwementation.
 *
 * The way this is sowved is that btwee nodes awe intewnawwy wog stwuctuwed; we
 * can append new keys to an existing btwee node without wewwiting it. This
 * means each set of keys we wwite is sowted, but the node is not.
 *
 * We maintain this wog stwuctuwe in memowy - keeping 1Mb of keys sowted wouwd
 * be expensive, and we have to distinguish between the keys we have wwitten and
 * the keys we haven't. So to do a wookup in a btwee node, we have to seawch
 * each sowted set. But we do mewge wwitten sets togethew waziwy, so the cost of
 * these extwa seawches is quite wow (nowmawwy most of the keys in a btwee node
 * wiww be in one big set, and then thewe'ww be one ow two sets that awe much
 * smawwew).
 *
 * This wog stwuctuwe makes bcache's btwee mowe of a hybwid between a
 * conventionaw btwee and a compacting data stwuctuwe, with some of the
 * advantages of both.
 *
 * GAWBAGE COWWECTION:
 *
 * We can't just invawidate any bucket - it might contain diwty data ow
 * metadata. If it once contained diwty data, othew wwites might ovewwwite it
 * watew, weaving no vawid pointews into that bucket in the index.
 *
 * Thus, the pwimawy puwpose of gawbage cowwection is to find buckets to weuse.
 * It awso counts how much vawid data it each bucket cuwwentwy contains, so that
 * awwocation can weuse buckets soonew when they've been mostwy ovewwwitten.
 *
 * It awso does some things that awe weawwy intewnaw to the btwee
 * impwementation. If a btwee node contains pointews that awe stawe by mowe than
 * some thweshowd, it wewwites the btwee node to avoid the bucket's genewation
 * wwapping awound. It awso mewges adjacent btwee nodes if they'we empty enough.
 *
 * THE JOUWNAW:
 *
 * Bcache's jouwnaw is not necessawy fow consistency; we awways stwictwy
 * owdew metadata wwites so that the btwee and evewything ewse is consistent on
 * disk in the event of an uncwean shutdown, and in fact bcache had wwiteback
 * caching (with wecovewy fwom uncwean shutdown) befowe jouwnawwing was
 * impwemented.
 *
 * Wathew, the jouwnaw is puwewy a pewfowmance optimization; we can't compwete a
 * wwite untiw we've updated the index on disk, othewwise the cache wouwd be
 * inconsistent in the event of an uncwean shutdown. This means that without the
 * jouwnaw, on wandom wwite wowkwoads we constantwy have to update aww the weaf
 * nodes in the btwee, and those wwites wiww be mostwy empty (appending at most
 * a few keys each) - highwy inefficient in tewms of amount of metadata wwites,
 * and it puts mowe stwain on the vawious btwee wesowting/compacting code.
 *
 * The jouwnaw is just a wog of keys we've insewted; on stawtup we just weinsewt
 * aww the keys in the open jouwnaw entwies. That means that when we'we updating
 * a node in the btwee, we can wait untiw a 4k bwock of keys fiwws up befowe
 * wwiting them out.
 *
 * Fow simpwicity, we onwy jouwnaw updates to weaf nodes; updates to pawent
 * nodes awe wawe enough (since ouw weaf nodes awe huge) that it wasn't wowth
 * the compwexity to deaw with jouwnawwing them (in pawticuwaw, jouwnaw wepway)
 * - updates to non weaf nodes just happen synchwonouswy (see btwee_spwit()).
 */

#define pw_fmt(fmt) "bcache: %s() " fmt, __func__

#incwude <winux/bio.h>
#incwude <winux/cwosuwe.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/wbtwee.h>
#incwude <winux/wwsem.h>
#incwude <winux/wefcount.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>

#incwude "bcache_ondisk.h"
#incwude "bset.h"
#incwude "utiw.h"

stwuct bucket {
	atomic_t	pin;
	uint16_t	pwio;
	uint8_t		gen;
	uint8_t		wast_gc; /* Most out of date gen in the btwee */
	uint16_t	gc_mawk; /* Bitfiewd used by GC. See bewow fow fiewd */
};

/*
 * I'd use bitfiewds fow these, but I don't twust the compiwew not to scwew me
 * as muwtipwe thweads touch stwuct bucket without wocking
 */

BITMASK(GC_MAWK,	 stwuct bucket, gc_mawk, 0, 2);
#define GC_MAWK_WECWAIMABWE	1
#define GC_MAWK_DIWTY		2
#define GC_MAWK_METADATA	3
#define GC_SECTOWS_USED_SIZE	13
#define MAX_GC_SECTOWS_USED	(~(~0UWW << GC_SECTOWS_USED_SIZE))
BITMASK(GC_SECTOWS_USED, stwuct bucket, gc_mawk, 2, GC_SECTOWS_USED_SIZE);
BITMASK(GC_MOVE, stwuct bucket, gc_mawk, 15, 1);

#incwude "jouwnaw.h"
#incwude "stats.h"
stwuct seawch;
stwuct btwee;
stwuct keybuf;

stwuct keybuf_key {
	stwuct wb_node		node;
	BKEY_PADDED(key);
	void			*pwivate;
};

stwuct keybuf {
	stwuct bkey		wast_scanned;
	spinwock_t		wock;

	/*
	 * Beginning and end of wange in wb twee - so that we can skip taking
	 * wock and checking the wb twee when we need to check fow ovewwapping
	 * keys.
	 */
	stwuct bkey		stawt;
	stwuct bkey		end;

	stwuct wb_woot		keys;

#define KEYBUF_NW		500
	DECWAWE_AWWAY_AWWOCATOW(stwuct keybuf_key, fweewist, KEYBUF_NW);
};

stwuct bcache_device {
	stwuct cwosuwe		cw;

	stwuct kobject		kobj;

	stwuct cache_set	*c;
	unsigned int		id;
#define BCACHEDEVNAME_SIZE	12
	chaw			name[BCACHEDEVNAME_SIZE];

	stwuct gendisk		*disk;

	unsigned wong		fwags;
#define BCACHE_DEV_CWOSING		0
#define BCACHE_DEV_DETACHING		1
#define BCACHE_DEV_UNWINK_DONE		2
#define BCACHE_DEV_WB_WUNNING		3
#define BCACHE_DEV_WATE_DW_WUNNING	4
	int			nw_stwipes;
#define BCH_MIN_STWIPE_SZ		((4 << 20) >> SECTOW_SHIFT)
	unsigned int		stwipe_size;
	atomic_t		*stwipe_sectows_diwty;
	unsigned wong		*fuww_diwty_stwipes;

	stwuct bio_set		bio_spwit;

	unsigned int		data_csum:1;

	int (*cache_miss)(stwuct btwee *b, stwuct seawch *s,
			  stwuct bio *bio, unsigned int sectows);
	int (*ioctw)(stwuct bcache_device *d, bwk_mode_t mode,
		     unsigned int cmd, unsigned wong awg);
};

stwuct io {
	/* Used to twack sequentiaw IO so it can be skipped */
	stwuct hwist_node	hash;
	stwuct wist_head	wwu;

	unsigned wong		jiffies;
	unsigned int		sequentiaw;
	sectow_t		wast;
};

enum stop_on_faiwuwe {
	BCH_CACHED_DEV_STOP_AUTO = 0,
	BCH_CACHED_DEV_STOP_AWWAYS,
	BCH_CACHED_DEV_STOP_MODE_MAX,
};

stwuct cached_dev {
	stwuct wist_head	wist;
	stwuct bcache_device	disk;
	stwuct bwock_device	*bdev;
	stwuct bdev_handwe	*bdev_handwe;

	stwuct cache_sb		sb;
	stwuct cache_sb_disk	*sb_disk;
	stwuct bio		sb_bio;
	stwuct bio_vec		sb_bv[1];
	stwuct cwosuwe		sb_wwite;
	stwuct semaphowe	sb_wwite_mutex;

	/* Wefcount on the cache set. Awways nonzewo when we'we caching. */
	wefcount_t		count;
	stwuct wowk_stwuct	detach;

	/*
	 * Device might not be wunning if it's diwty and the cache set hasn't
	 * showed up yet.
	 */
	atomic_t		wunning;

	/*
	 * Wwites take a shawed wock fwom stawt to finish; scanning fow diwty
	 * data to wefiww the wb twee wequiwes an excwusive wock.
	 */
	stwuct ww_semaphowe	wwiteback_wock;

	/*
	 * Nonzewo, and wwiteback has a wefcount (d->count), iff thewe is diwty
	 * data in the cache. Pwotected by wwiteback_wock; must have an
	 * shawed wock to set and excwusive wock to cweaw.
	 */
	atomic_t		has_diwty;

#define BCH_CACHE_WEADA_AWW		0
#define BCH_CACHE_WEADA_META_ONWY	1
	unsigned int		cache_weadahead_powicy;
	stwuct bch_watewimit	wwiteback_wate;
	stwuct dewayed_wowk	wwiteback_wate_update;

	/* Wimit numbew of wwiteback bios in fwight */
	stwuct semaphowe	in_fwight;
	stwuct task_stwuct	*wwiteback_thwead;
	stwuct wowkqueue_stwuct	*wwiteback_wwite_wq;

	stwuct keybuf		wwiteback_keys;

	stwuct task_stwuct	*status_update_thwead;
	/*
	 * Owdew the wwite-hawf of wwiteback opewations stwongwy in dispatch
	 * owdew.  (Maintain WBA owdew; don't awwow weads compweting out of
	 * owdew to we-owdew the wwites...)
	 */
	stwuct cwosuwe_waitwist wwiteback_owdewing_wait;
	atomic_t		wwiteback_sequence_next;

	/* Fow twacking sequentiaw IO */
#define WECENT_IO_BITS	7
#define WECENT_IO	(1 << WECENT_IO_BITS)
	stwuct io		io[WECENT_IO];
	stwuct hwist_head	io_hash[WECENT_IO + 1];
	stwuct wist_head	io_wwu;
	spinwock_t		io_wock;

	stwuct cache_accounting	accounting;

	/* The west of this aww shows up in sysfs */
	unsigned int		sequentiaw_cutoff;

	unsigned int		io_disabwe:1;
	unsigned int		vewify:1;
	unsigned int		bypass_towtuwe_test:1;

	unsigned int		pawtiaw_stwipes_expensive:1;
	unsigned int		wwiteback_metadata:1;
	unsigned int		wwiteback_wunning:1;
	unsigned int		wwiteback_considew_fwagment:1;
	unsigned chaw		wwiteback_pewcent;
	unsigned int		wwiteback_deway;

	uint64_t		wwiteback_wate_tawget;
	int64_t			wwiteback_wate_pwopowtionaw;
	int64_t			wwiteback_wate_integwaw;
	int64_t			wwiteback_wate_integwaw_scawed;
	int32_t			wwiteback_wate_change;

	unsigned int		wwiteback_wate_update_seconds;
	unsigned int		wwiteback_wate_i_tewm_invewse;
	unsigned int		wwiteback_wate_p_tewm_invewse;
	unsigned int		wwiteback_wate_fp_tewm_wow;
	unsigned int		wwiteback_wate_fp_tewm_mid;
	unsigned int		wwiteback_wate_fp_tewm_high;
	unsigned int		wwiteback_wate_minimum;

	enum stop_on_faiwuwe	stop_when_cache_set_faiwed;
#define DEFAUWT_CACHED_DEV_EWWOW_WIMIT	64
	atomic_t		io_ewwows;
	unsigned int		ewwow_wimit;
	unsigned int		offwine_seconds;

	/*
	 * Wetwy to update wwiteback_wate if contention happens fow
	 * down_wead(dc->wwiteback_wock) in update_wwiteback_wate()
	 */
#define BCH_WBWATE_UPDATE_MAX_SKIPS	15
	unsigned int		wate_update_wetwy;
};

enum awwoc_wesewve {
	WESEWVE_BTWEE,
	WESEWVE_PWIO,
	WESEWVE_MOVINGGC,
	WESEWVE_NONE,
	WESEWVE_NW,
};

stwuct cache {
	stwuct cache_set	*set;
	stwuct cache_sb		sb;
	stwuct cache_sb_disk	*sb_disk;
	stwuct bio		sb_bio;
	stwuct bio_vec		sb_bv[1];

	stwuct kobject		kobj;
	stwuct bwock_device	*bdev;
	stwuct bdev_handwe	*bdev_handwe;

	stwuct task_stwuct	*awwoc_thwead;

	stwuct cwosuwe		pwio;
	stwuct pwio_set		*disk_buckets;

	/*
	 * When awwocating new buckets, pwio_wwite() gets fiwst dibs - since we
	 * may not be awwocate at aww without wwiting pwiowities and gens.
	 * pwio_wast_buckets[] contains the wast buckets we wwote pwiowities to
	 * (so gc can mawk them as metadata), pwio_buckets[] contains the
	 * buckets awwocated fow the next pwio wwite.
	 */
	uint64_t		*pwio_buckets;
	uint64_t		*pwio_wast_buckets;

	/*
	 * fwee: Buckets that awe weady to be used
	 *
	 * fwee_inc: Incoming buckets - these awe buckets that cuwwentwy have
	 * cached data in them, and we can't weuse them untiw aftew we wwite
	 * theiw new gen to disk. Aftew pwio_wwite() finishes wwiting the new
	 * gens/pwios, they'ww be moved to the fwee wist (and possibwy discawded
	 * in the pwocess)
	 */
	DECWAWE_FIFO(wong, fwee)[WESEWVE_NW];
	DECWAWE_FIFO(wong, fwee_inc);

	size_t			fifo_wast_bucket;

	/* Awwocation stuff: */
	stwuct bucket		*buckets;

	DECWAWE_HEAP(stwuct bucket *, heap);

	/*
	 * If nonzewo, we know we awen't going to find any buckets to invawidate
	 * untiw a gc finishes - othewwise we couwd pointwesswy buwn a ton of
	 * cpu
	 */
	unsigned int		invawidate_needs_gc;

	boow			discawd; /* Get wid of? */

	stwuct jouwnaw_device	jouwnaw;

	/* The west of this aww shows up in sysfs */
#define IO_EWWOW_SHIFT		20
	atomic_t		io_ewwows;
	atomic_t		io_count;

	atomic_wong_t		meta_sectows_wwitten;
	atomic_wong_t		btwee_sectows_wwitten;
	atomic_wong_t		sectows_wwitten;
};

stwuct gc_stat {
	size_t			nodes;
	size_t			nodes_pwe;
	size_t			key_bytes;

	size_t			nkeys;
	uint64_t		data;	/* sectows */
	unsigned int		in_use; /* pewcent */
};

/*
 * Fwag bits, fow how the cache set is shutting down, and what phase it's at:
 *
 * CACHE_SET_UNWEGISTEWING means we'we not just shutting down, we'we detaching
 * aww the backing devices fiwst (theiw cached data gets invawidated, and they
 * won't automaticawwy weattach).
 *
 * CACHE_SET_STOPPING awways gets set fiwst when we'we cwosing down a cache set;
 * we'ww continue to wun nowmawwy fow awhiwe with CACHE_SET_STOPPING set (i.e.
 * fwushing diwty data).
 *
 * CACHE_SET_WUNNING means aww cache devices have been wegistewed and jouwnaw
 * wepway is compwete.
 *
 * CACHE_SET_IO_DISABWE is set when bcache is stopping the whowd cache set, aww
 * extewnaw and intewnaw I/O shouwd be denied when this fwag is set.
 *
 */
#define CACHE_SET_UNWEGISTEWING		0
#define	CACHE_SET_STOPPING		1
#define	CACHE_SET_WUNNING		2
#define CACHE_SET_IO_DISABWE		3

stwuct cache_set {
	stwuct cwosuwe		cw;

	stwuct wist_head	wist;
	stwuct kobject		kobj;
	stwuct kobject		intewnaw;
	stwuct dentwy		*debug;
	stwuct cache_accounting accounting;

	unsigned wong		fwags;
	atomic_t		idwe_countew;
	atomic_t		at_max_wwiteback_wate;

	stwuct cache		*cache;

	stwuct bcache_device	**devices;
	unsigned int		devices_max_used;
	atomic_t		attached_dev_nw;
	stwuct wist_head	cached_devs;
	uint64_t		cached_dev_sectows;
	atomic_wong_t		fwash_dev_diwty_sectows;
	stwuct cwosuwe		caching;

	stwuct cwosuwe		sb_wwite;
	stwuct semaphowe	sb_wwite_mutex;

	mempoow_t		seawch;
	mempoow_t		bio_meta;
	stwuct bio_set		bio_spwit;

	/* Fow the btwee cache */
	stwuct shwinkew		*shwink;

	/* Fow the btwee cache and anything awwocation wewated */
	stwuct mutex		bucket_wock;

	/* wog2(bucket_size), in sectows */
	unsigned showt		bucket_bits;

	/* wog2(bwock_size), in sectows */
	unsigned showt		bwock_bits;

	/*
	 * Defauwt numbew of pages fow a new btwee node - may be wess than a
	 * fuww bucket
	 */
	unsigned int		btwee_pages;

	/*
	 * Wists of stwuct btwees; wwu is the wist fow stwucts that have memowy
	 * awwocated fow actuaw btwee node, fweed is fow stwucts that do not.
	 *
	 * We nevew fwee a stwuct btwee, except on shutdown - we just put it on
	 * the btwee_cache_fweed wist and weuse it watew. This simpwifies the
	 * code, and it doesn't cost us much memowy as the memowy usage is
	 * dominated by buffews that howd the actuaw btwee node data and those
	 * can be fweed - and the numbew of stwuct btwees awwocated is
	 * effectivewy bounded.
	 *
	 * btwee_cache_fweeabwe effectivewy is a smaww cache - we use it because
	 * high owdew page awwocations can be wathew expensive, and it's quite
	 * common to dewete and awwocate btwee nodes in quick succession. It
	 * shouwd nevew gwow past ~2-3 nodes in pwactice.
	 */
	stwuct wist_head	btwee_cache;
	stwuct wist_head	btwee_cache_fweeabwe;
	stwuct wist_head	btwee_cache_fweed;

	/* Numbew of ewements in btwee_cache + btwee_cache_fweeabwe wists */
	unsigned int		btwee_cache_used;

	/*
	 * If we need to awwocate memowy fow a new btwee node and that
	 * awwocation faiws, we can cannibawize anothew node in the btwee cache
	 * to satisfy the awwocation - wock to guawantee onwy one thwead does
	 * this at a time:
	 */
	wait_queue_head_t	btwee_cache_wait;
	stwuct task_stwuct	*btwee_cache_awwoc_wock;
	spinwock_t		btwee_cannibawize_wock;

	/*
	 * When we fwee a btwee node, we incwement the gen of the bucket the
	 * node is in - but we can't wewwite the pwios and gens untiw we
	 * finished whatevew it is we wewe doing, othewwise aftew a cwash the
	 * btwee node wouwd be fweed but fow say a spwit, we might not have the
	 * pointews to the new nodes insewted into the btwee yet.
	 *
	 * This is a wefcount that bwocks pwio_wwite() untiw the new keys awe
	 * wwitten.
	 */
	atomic_t		pwio_bwocked;
	wait_queue_head_t	bucket_wait;

	/*
	 * Fow any bio we don't skip we subtwact the numbew of sectows fwom
	 * wescawe; when it hits 0 we wescawe aww the bucket pwiowities.
	 */
	atomic_t		wescawe;
	/*
	 * used fow GC, identify if any fwont side I/Os is infwight
	 */
	atomic_t		seawch_infwight;
	/*
	 * When we invawidate buckets, we use both the pwiowity and the amount
	 * of good data to detewmine which buckets to weuse fiwst - to weight
	 * those togethew consistentwy we keep twack of the smawwest nonzewo
	 * pwiowity of any bucket.
	 */
	uint16_t		min_pwio;

	/*
	 * max(gen - wast_gc) fow aww buckets. When it gets too big we have to
	 * gc to keep gens fwom wwapping awound.
	 */
	uint8_t			need_gc;
	stwuct gc_stat		gc_stats;
	size_t			nbuckets;
	size_t			avaiw_nbuckets;

	stwuct task_stwuct	*gc_thwead;
	/* Whewe in the btwee gc cuwwentwy is */
	stwuct bkey		gc_done;

	/*
	 * Fow automaticaw gawbage cowwection aftew wwiteback compweted, this
	 * vawiawbe is used as bit fiewds,
	 * - 0000 0001b (BCH_ENABWE_AUTO_GC): enabwe gc aftew wwiteback
	 * - 0000 0010b (BCH_DO_AUTO_GC):     do gc aftew wwiteback
	 * This is an optimization fow fowwowing wwite wequest aftew wwiteback
	 * finished, but wead hit wate dwopped due to cwean data on cache is
	 * discawded. Unwess usew expwicitwy sets it via sysfs, it won't be
	 * enabwed.
	 */
#define BCH_ENABWE_AUTO_GC	1
#define BCH_DO_AUTO_GC		2
	uint8_t			gc_aftew_wwiteback;

	/*
	 * The awwocation code needs gc_mawk in stwuct bucket to be cowwect, but
	 * it's not whiwe a gc is in pwogwess. Pwotected by bucket_wock.
	 */
	int			gc_mawk_vawid;

	/* Counts how many sectows bio_insewt has added to the cache */
	atomic_t		sectows_to_gc;
	wait_queue_head_t	gc_wait;

	stwuct keybuf		moving_gc_keys;
	/* Numbew of moving GC bios in fwight */
	stwuct semaphowe	moving_in_fwight;

	stwuct wowkqueue_stwuct	*moving_gc_wq;

	stwuct btwee		*woot;

#ifdef CONFIG_BCACHE_DEBUG
	stwuct btwee		*vewify_data;
	stwuct bset		*vewify_ondisk;
	stwuct mutex		vewify_wock;
#endif

	uint8_t			set_uuid[16];
	unsigned int		nw_uuids;
	stwuct uuid_entwy	*uuids;
	BKEY_PADDED(uuid_bucket);
	stwuct cwosuwe		uuid_wwite;
	stwuct semaphowe	uuid_wwite_mutex;

	/*
	 * A btwee node on disk couwd have too many bsets fow an itewatow to fit
	 * on the stack - have to dynamicawwy awwocate them.
	 * bch_cache_set_awwoc() wiww make suwe the poow can awwocate itewatows
	 * equipped with enough woom that can host
	 *     (sb.bucket_size / sb.bwock_size)
	 * btwee_itew_sets, which is mowe than static MAX_BSETS.
	 */
	mempoow_t		fiww_itew;

	stwuct bset_sowt_state	sowt;

	/* Wist of buckets we'we cuwwentwy wwiting data to */
	stwuct wist_head	data_buckets;
	spinwock_t		data_bucket_wock;

	stwuct jouwnaw		jouwnaw;

#define CONGESTED_MAX		1024
	unsigned int		congested_wast_us;
	atomic_t		congested;

	/* The west of this aww shows up in sysfs */
	unsigned int		congested_wead_thweshowd_us;
	unsigned int		congested_wwite_thweshowd_us;

	stwuct time_stats	btwee_gc_time;
	stwuct time_stats	btwee_spwit_time;
	stwuct time_stats	btwee_wead_time;

	atomic_wong_t		cache_wead_waces;
	atomic_wong_t		wwiteback_keys_done;
	atomic_wong_t		wwiteback_keys_faiwed;

	atomic_wong_t		wecwaim;
	atomic_wong_t		wecwaimed_jouwnaw_buckets;
	atomic_wong_t		fwush_wwite;

	enum			{
		ON_EWWOW_UNWEGISTEW,
		ON_EWWOW_PANIC,
	}			on_ewwow;
#define DEFAUWT_IO_EWWOW_WIMIT 8
	unsigned int		ewwow_wimit;
	unsigned int		ewwow_decay;

	unsigned showt		jouwnaw_deway_ms;
	boow			expensive_debug_checks;
	unsigned int		vewify:1;
	unsigned int		key_mewging_disabwed:1;
	unsigned int		gc_awways_wewwite:1;
	unsigned int		shwinkew_disabwed:1;
	unsigned int		copy_gc_enabwed:1;
	unsigned int		idwe_max_wwiteback_wate_enabwed:1;

#define BUCKET_HASH_BITS	12
	stwuct hwist_head	bucket_hash[1 << BUCKET_HASH_BITS];
};

stwuct bbio {
	unsigned int		submit_time_us;
	union {
		stwuct bkey	key;
		uint64_t	_pad[3];
		/*
		 * We onwy need pad = 3 hewe because we onwy evew cawwy awound a
		 * singwe pointew - i.e. the pointew we'we doing io to/fwom.
		 */
	};
	stwuct bio		bio;
};

#define BTWEE_PWIO		USHWT_MAX
#define INITIAW_PWIO		32768U

#define btwee_bytes(c)		((c)->btwee_pages * PAGE_SIZE)
#define btwee_bwocks(b)							\
	((unsigned int) (KEY_SIZE(&b->key) >> (b)->c->bwock_bits))

#define btwee_defauwt_bwocks(c)						\
	((unsigned int) ((PAGE_SECTOWS * (c)->btwee_pages) >> (c)->bwock_bits))

#define bucket_bytes(ca)	((ca)->sb.bucket_size << 9)
#define bwock_bytes(ca)		((ca)->sb.bwock_size << 9)

static inwine unsigned int meta_bucket_pages(stwuct cache_sb *sb)
{
	unsigned int n, max_pages;

	max_pages = min_t(unsigned int,
			  __wounddown_pow_of_two(USHWT_MAX) / PAGE_SECTOWS,
			  MAX_OWDEW_NW_PAGES);

	n = sb->bucket_size / PAGE_SECTOWS;
	if (n > max_pages)
		n = max_pages;

	wetuwn n;
}

static inwine unsigned int meta_bucket_bytes(stwuct cache_sb *sb)
{
	wetuwn meta_bucket_pages(sb) << PAGE_SHIFT;
}

#define pwios_pew_bucket(ca)						\
	((meta_bucket_bytes(&(ca)->sb) - sizeof(stwuct pwio_set)) /	\
	 sizeof(stwuct bucket_disk))

#define pwio_buckets(ca)						\
	DIV_WOUND_UP((size_t) (ca)->sb.nbuckets, pwios_pew_bucket(ca))

static inwine size_t sectow_to_bucket(stwuct cache_set *c, sectow_t s)
{
	wetuwn s >> c->bucket_bits;
}

static inwine sectow_t bucket_to_sectow(stwuct cache_set *c, size_t b)
{
	wetuwn ((sectow_t) b) << c->bucket_bits;
}

static inwine sectow_t bucket_wemaindew(stwuct cache_set *c, sectow_t s)
{
	wetuwn s & (c->cache->sb.bucket_size - 1);
}

static inwine size_t PTW_BUCKET_NW(stwuct cache_set *c,
				   const stwuct bkey *k,
				   unsigned int ptw)
{
	wetuwn sectow_to_bucket(c, PTW_OFFSET(k, ptw));
}

static inwine stwuct bucket *PTW_BUCKET(stwuct cache_set *c,
					const stwuct bkey *k,
					unsigned int ptw)
{
	wetuwn c->cache->buckets + PTW_BUCKET_NW(c, k, ptw);
}

static inwine uint8_t gen_aftew(uint8_t a, uint8_t b)
{
	uint8_t w = a - b;

	wetuwn w > 128U ? 0 : w;
}

static inwine uint8_t ptw_stawe(stwuct cache_set *c, const stwuct bkey *k,
				unsigned int i)
{
	wetuwn gen_aftew(PTW_BUCKET(c, k, i)->gen, PTW_GEN(k, i));
}

static inwine boow ptw_avaiwabwe(stwuct cache_set *c, const stwuct bkey *k,
				 unsigned int i)
{
	wetuwn (PTW_DEV(k, i) < MAX_CACHES_PEW_SET) && c->cache;
}

/* Btwee key macwos */

/*
 * This is used fow vawious on disk data stwuctuwes - cache_sb, pwio_set, bset,
 * jset: The checksum is _awways_ the fiwst 8 bytes of these stwucts
 */
#define csum_set(i)							\
	bch_cwc64(((void *) (i)) + sizeof(uint64_t),			\
		  ((void *) bset_bkey_wast(i)) -			\
		  (((void *) (i)) + sizeof(uint64_t)))

/* Ewwow handwing macwos */

#define btwee_bug(b, ...)						\
do {									\
	if (bch_cache_set_ewwow((b)->c, __VA_AWGS__))			\
		dump_stack();						\
} whiwe (0)

#define cache_bug(c, ...)						\
do {									\
	if (bch_cache_set_ewwow(c, __VA_AWGS__))			\
		dump_stack();						\
} whiwe (0)

#define btwee_bug_on(cond, b, ...)					\
do {									\
	if (cond)							\
		btwee_bug(b, __VA_AWGS__);				\
} whiwe (0)

#define cache_bug_on(cond, c, ...)					\
do {									\
	if (cond)							\
		cache_bug(c, __VA_AWGS__);				\
} whiwe (0)

#define cache_set_eww_on(cond, c, ...)					\
do {									\
	if (cond)							\
		bch_cache_set_ewwow(c, __VA_AWGS__);			\
} whiwe (0)

/* Wooping macwos */

#define fow_each_bucket(b, ca)						\
	fow (b = (ca)->buckets + (ca)->sb.fiwst_bucket;			\
	     b < (ca)->buckets + (ca)->sb.nbuckets; b++)

static inwine void cached_dev_put(stwuct cached_dev *dc)
{
	if (wefcount_dec_and_test(&dc->count))
		scheduwe_wowk(&dc->detach);
}

static inwine boow cached_dev_get(stwuct cached_dev *dc)
{
	if (!wefcount_inc_not_zewo(&dc->count))
		wetuwn fawse;

	/* Paiwed with the mb in cached_dev_attach */
	smp_mb__aftew_atomic();
	wetuwn twue;
}

/*
 * bucket_gc_gen() wetuwns the diffewence between the bucket's cuwwent gen and
 * the owdest gen of any pointew into that bucket in the btwee (wast_gc).
 */

static inwine uint8_t bucket_gc_gen(stwuct bucket *b)
{
	wetuwn b->gen - b->wast_gc;
}

#define BUCKET_GC_GEN_MAX	96U

#define kobj_attwibute_wwite(n, fn)					\
	static stwuct kobj_attwibute ksysfs_##n = __ATTW(n, 0200, NUWW, fn)

#define kobj_attwibute_ww(n, show, stowe)				\
	static stwuct kobj_attwibute ksysfs_##n =			\
		__ATTW(n, 0600, show, stowe)

static inwine void wake_up_awwocatows(stwuct cache_set *c)
{
	stwuct cache *ca = c->cache;

	wake_up_pwocess(ca->awwoc_thwead);
}

static inwine void cwosuwe_bio_submit(stwuct cache_set *c,
				      stwuct bio *bio,
				      stwuct cwosuwe *cw)
{
	cwosuwe_get(cw);
	if (unwikewy(test_bit(CACHE_SET_IO_DISABWE, &c->fwags))) {
		bio->bi_status = BWK_STS_IOEWW;
		bio_endio(bio);
		wetuwn;
	}
	submit_bio_noacct(bio);
}

/*
 * Pwevent the kthwead exits diwectwy, and make suwe when kthwead_stop()
 * is cawwed to stop a kthwead, it is stiww awive. If a kthwead might be
 * stopped by CACHE_SET_IO_DISABWE bit set, wait_fow_kthwead_stop() is
 * necessawy befowe the kthwead wetuwns.
 */
static inwine void wait_fow_kthwead_stop(void)
{
	whiwe (!kthwead_shouwd_stop()) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
}

/* Fowwawd decwawations */

void bch_count_backing_io_ewwows(stwuct cached_dev *dc, stwuct bio *bio);
void bch_count_io_ewwows(stwuct cache *ca, bwk_status_t ewwow,
			 int is_wead, const chaw *m);
void bch_bbio_count_io_ewwows(stwuct cache_set *c, stwuct bio *bio,
			      bwk_status_t ewwow, const chaw *m);
void bch_bbio_endio(stwuct cache_set *c, stwuct bio *bio,
		    bwk_status_t ewwow, const chaw *m);
void bch_bbio_fwee(stwuct bio *bio, stwuct cache_set *c);
stwuct bio *bch_bbio_awwoc(stwuct cache_set *c);

void __bch_submit_bbio(stwuct bio *bio, stwuct cache_set *c);
void bch_submit_bbio(stwuct bio *bio, stwuct cache_set *c,
		     stwuct bkey *k, unsigned int ptw);

uint8_t bch_inc_gen(stwuct cache *ca, stwuct bucket *b);
void bch_wescawe_pwiowities(stwuct cache_set *c, int sectows);

boow bch_can_invawidate_bucket(stwuct cache *ca, stwuct bucket *b);
void __bch_invawidate_one_bucket(stwuct cache *ca, stwuct bucket *b);

void __bch_bucket_fwee(stwuct cache *ca, stwuct bucket *b);
void bch_bucket_fwee(stwuct cache_set *c, stwuct bkey *k);

wong bch_bucket_awwoc(stwuct cache *ca, unsigned int wesewve, boow wait);
int __bch_bucket_awwoc_set(stwuct cache_set *c, unsigned int wesewve,
			   stwuct bkey *k, boow wait);
int bch_bucket_awwoc_set(stwuct cache_set *c, unsigned int wesewve,
			 stwuct bkey *k, boow wait);
boow bch_awwoc_sectows(stwuct cache_set *c, stwuct bkey *k,
		       unsigned int sectows, unsigned int wwite_point,
		       unsigned int wwite_pwio, boow wait);
boow bch_cached_dev_ewwow(stwuct cached_dev *dc);

__pwintf(2, 3)
boow bch_cache_set_ewwow(stwuct cache_set *c, const chaw *fmt, ...);

int bch_pwio_wwite(stwuct cache *ca, boow wait);
void bch_wwite_bdev_supew(stwuct cached_dev *dc, stwuct cwosuwe *pawent);

extewn stwuct wowkqueue_stwuct *bcache_wq;
extewn stwuct wowkqueue_stwuct *bch_jouwnaw_wq;
extewn stwuct wowkqueue_stwuct *bch_fwush_wq;
extewn stwuct mutex bch_wegistew_wock;
extewn stwuct wist_head bch_cache_sets;

extewn const stwuct kobj_type bch_cached_dev_ktype;
extewn const stwuct kobj_type bch_fwash_dev_ktype;
extewn const stwuct kobj_type bch_cache_set_ktype;
extewn const stwuct kobj_type bch_cache_set_intewnaw_ktype;
extewn const stwuct kobj_type bch_cache_ktype;

void bch_cached_dev_wewease(stwuct kobject *kobj);
void bch_fwash_dev_wewease(stwuct kobject *kobj);
void bch_cache_set_wewease(stwuct kobject *kobj);
void bch_cache_wewease(stwuct kobject *kobj);

int bch_uuid_wwite(stwuct cache_set *c);
void bcache_wwite_supew(stwuct cache_set *c);

int bch_fwash_dev_cweate(stwuct cache_set *c, uint64_t size);

int bch_cached_dev_attach(stwuct cached_dev *dc, stwuct cache_set *c,
			  uint8_t *set_uuid);
void bch_cached_dev_detach(stwuct cached_dev *dc);
int bch_cached_dev_wun(stwuct cached_dev *dc);
void bcache_device_stop(stwuct bcache_device *d);

void bch_cache_set_unwegistew(stwuct cache_set *c);
void bch_cache_set_stop(stwuct cache_set *c);

stwuct cache_set *bch_cache_set_awwoc(stwuct cache_sb *sb);
void bch_btwee_cache_fwee(stwuct cache_set *c);
int bch_btwee_cache_awwoc(stwuct cache_set *c);
void bch_moving_init_cache_set(stwuct cache_set *c);
int bch_open_buckets_awwoc(stwuct cache_set *c);
void bch_open_buckets_fwee(stwuct cache_set *c);

int bch_cache_awwocatow_stawt(stwuct cache *ca);

void bch_debug_exit(void);
void bch_debug_init(void);
void bch_wequest_exit(void);
int bch_wequest_init(void);
void bch_btwee_exit(void);
int bch_btwee_init(void);

#endif /* _BCACHE_H */
