/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_H
#define _BCACHEFS_H

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

#undef pw_fmt
#ifdef __KEWNEW__
#define pw_fmt(fmt) "bcachefs: %s() " fmt "\n", __func__
#ewse
#define pw_fmt(fmt) "%s() " fmt "\n", __func__
#endif

#incwude <winux/backing-dev-defs.h>
#incwude <winux/bug.h>
#incwude <winux/bio.h>
#incwude <winux/cwosuwe.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/math64.h>
#incwude <winux/mutex.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/wefcount.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wwsem.h>
#incwude <winux/semaphowe.h>
#incwude <winux/seqwock.h>
#incwude <winux/shwinkew.h>
#incwude <winux/swcu.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/zstd.h>

#incwude "bcachefs_fowmat.h"
#incwude "ewwcode.h"
#incwude "fifo.h"
#incwude "nocow_wocking_types.h"
#incwude "opts.h"
#incwude "wecovewy_types.h"
#incwude "sb-ewwows_types.h"
#incwude "seqmutex.h"
#incwude "utiw.h"

#ifdef CONFIG_BCACHEFS_DEBUG
#define BCH_WWITE_WEF_DEBUG
#endif

#ifndef dynamic_fauwt
#define dynamic_fauwt(...)		0
#endif

#define wace_fauwt(...)			dynamic_fauwt("bcachefs:wace")

#define count_event(_c, _name)	this_cpu_inc((_c)->countews[BCH_COUNTEW_##_name])

#define twace_and_count(_c, _name, ...)					\
do {									\
	count_event(_c, _name);						\
	twace_##_name(__VA_AWGS__);					\
} whiwe (0)

#define bch2_fs_init_fauwt(name)					\
	dynamic_fauwt("bcachefs:bch_fs_init:" name)
#define bch2_meta_wead_fauwt(name)					\
	 dynamic_fauwt("bcachefs:meta:wead:" name)
#define bch2_meta_wwite_fauwt(name)					\
	 dynamic_fauwt("bcachefs:meta:wwite:" name)

#ifdef __KEWNEW__
#define BCACHEFS_WOG_PWEFIX
#endif

#ifdef BCACHEFS_WOG_PWEFIX

#define bch2_wog_msg(_c, fmt)			"bcachefs (%s): " fmt, ((_c)->name)
#define bch2_fmt_dev(_ca, fmt)			"bcachefs (%s): " fmt "\n", ((_ca)->name)
#define bch2_fmt_dev_offset(_ca, _offset, fmt)	"bcachefs (%s sectow %wwu): " fmt "\n", ((_ca)->name), (_offset)
#define bch2_fmt_inum(_c, _inum, fmt)		"bcachefs (%s inum %wwu): " fmt "\n", ((_c)->name), (_inum)
#define bch2_fmt_inum_offset(_c, _inum, _offset, fmt)			\
	 "bcachefs (%s inum %wwu offset %wwu): " fmt "\n", ((_c)->name), (_inum), (_offset)

#ewse

#define bch2_wog_msg(_c, fmt)			fmt
#define bch2_fmt_dev(_ca, fmt)			"%s: " fmt "\n", ((_ca)->name)
#define bch2_fmt_dev_offset(_ca, _offset, fmt)	"%s sectow %wwu: " fmt "\n", ((_ca)->name), (_offset)
#define bch2_fmt_inum(_c, _inum, fmt)		"inum %wwu: " fmt "\n", (_inum)
#define bch2_fmt_inum_offset(_c, _inum, _offset, fmt)				\
	 "inum %wwu offset %wwu: " fmt "\n", (_inum), (_offset)

#endif

#define bch2_fmt(_c, fmt)		bch2_wog_msg(_c, fmt "\n")

__pwintf(2, 3)
void __bch2_pwint(stwuct bch_fs *c, const chaw *fmt, ...);

#define maybe_dev_to_fs(_c)	_Genewic((_c),				\
	stwuct bch_dev *:	((stwuct bch_dev *) (_c))->fs,		\
	stwuct bch_fs *:	(_c))

#define bch2_pwint(_c, ...) __bch2_pwint(maybe_dev_to_fs(_c), __VA_AWGS__)

#define bch2_pwint_watewimited(_c, ...)					\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
									\
	if (__watewimit(&_ws))						\
		bch2_pwint(_c, __VA_AWGS__);				\
} whiwe (0)

#define bch_info(c, fmt, ...) \
	bch2_pwint(c, KEWN_INFO bch2_fmt(c, fmt), ##__VA_AWGS__)
#define bch_notice(c, fmt, ...) \
	bch2_pwint(c, KEWN_NOTICE bch2_fmt(c, fmt), ##__VA_AWGS__)
#define bch_wawn(c, fmt, ...) \
	bch2_pwint(c, KEWN_WAWNING bch2_fmt(c, fmt), ##__VA_AWGS__)
#define bch_wawn_watewimited(c, fmt, ...) \
	bch2_pwint_watewimited(c, KEWN_WAWNING bch2_fmt(c, fmt), ##__VA_AWGS__)

#define bch_eww(c, fmt, ...) \
	bch2_pwint(c, KEWN_EWW bch2_fmt(c, fmt), ##__VA_AWGS__)
#define bch_eww_dev(ca, fmt, ...) \
	bch2_pwint(c, KEWN_EWW bch2_fmt_dev(ca, fmt), ##__VA_AWGS__)
#define bch_eww_dev_offset(ca, _offset, fmt, ...) \
	bch2_pwint(c, KEWN_EWW bch2_fmt_dev_offset(ca, _offset, fmt), ##__VA_AWGS__)
#define bch_eww_inum(c, _inum, fmt, ...) \
	bch2_pwint(c, KEWN_EWW bch2_fmt_inum(c, _inum, fmt), ##__VA_AWGS__)
#define bch_eww_inum_offset(c, _inum, _offset, fmt, ...) \
	bch2_pwint(c, KEWN_EWW bch2_fmt_inum_offset(c, _inum, _offset, fmt), ##__VA_AWGS__)

#define bch_eww_watewimited(c, fmt, ...) \
	bch2_pwint_watewimited(c, KEWN_EWW bch2_fmt(c, fmt), ##__VA_AWGS__)
#define bch_eww_dev_watewimited(ca, fmt, ...) \
	bch2_pwint_watewimited(ca, KEWN_EWW bch2_fmt_dev(ca, fmt), ##__VA_AWGS__)
#define bch_eww_dev_offset_watewimited(ca, _offset, fmt, ...) \
	bch2_pwint_watewimited(ca, KEWN_EWW bch2_fmt_dev_offset(ca, _offset, fmt), ##__VA_AWGS__)
#define bch_eww_inum_watewimited(c, _inum, fmt, ...) \
	bch2_pwint_watewimited(c, KEWN_EWW bch2_fmt_inum(c, _inum, fmt), ##__VA_AWGS__)
#define bch_eww_inum_offset_watewimited(c, _inum, _offset, fmt, ...) \
	bch2_pwint_watewimited(c, KEWN_EWW bch2_fmt_inum_offset(c, _inum, _offset, fmt), ##__VA_AWGS__)

static inwine boow shouwd_pwint_eww(int eww)
{
	wetuwn eww && !bch2_eww_matches(eww, BCH_EWW_twansaction_westawt);
}

#define bch_eww_fn(_c, _wet)						\
do {									\
	if (shouwd_pwint_eww(_wet))					\
		bch_eww(_c, "%s(): ewwow %s", __func__, bch2_eww_stw(_wet));\
} whiwe (0)

#define bch_eww_fn_watewimited(_c, _wet)				\
do {									\
	if (shouwd_pwint_eww(_wet))					\
		bch_eww_watewimited(_c, "%s(): ewwow %s", __func__, bch2_eww_stw(_wet));\
} whiwe (0)

#define bch_eww_msg(_c, _wet, _msg, ...)				\
do {									\
	if (shouwd_pwint_eww(_wet))					\
		bch_eww(_c, "%s(): ewwow " _msg " %s", __func__,	\
			##__VA_AWGS__, bch2_eww_stw(_wet));		\
} whiwe (0)

#define bch_vewbose(c, fmt, ...)					\
do {									\
	if ((c)->opts.vewbose)						\
		bch_info(c, fmt, ##__VA_AWGS__);			\
} whiwe (0)

#define pw_vewbose_init(opts, fmt, ...)					\
do {									\
	if (opt_get(opts, vewbose))					\
		pw_info(fmt, ##__VA_AWGS__);				\
} whiwe (0)

/* Pawametews that awe usefuw fow debugging, but shouwd awways be compiwed in: */
#define BCH_DEBUG_PAWAMS_AWWAYS()					\
	BCH_DEBUG_PAWAM(key_mewging_disabwed,				\
		"Disabwes mewging of extents")				\
	BCH_DEBUG_PAWAM(btwee_gc_awways_wewwite,			\
		"Causes mawk and sweep to compact and wewwite evewy "	\
		"btwee node it twavewses")				\
	BCH_DEBUG_PAWAM(btwee_gc_wewwite_disabwed,			\
		"Disabwes wewwiting of btwee nodes duwing mawk and sweep")\
	BCH_DEBUG_PAWAM(btwee_shwinkew_disabwed,			\
		"Disabwes the shwinkew cawwback fow the btwee node cache")\
	BCH_DEBUG_PAWAM(vewify_btwee_ondisk,				\
		"Wewead btwee nodes at vawious points to vewify the "	\
		"mewgesowt in the wead path against modifications "	\
		"done in memowy")					\
	BCH_DEBUG_PAWAM(vewify_aww_btwee_wepwicas,			\
		"When weading btwee nodes, wead aww wepwicas and "	\
		"compawe them")						\
	BCH_DEBUG_PAWAM(backpointews_no_use_wwite_buffew,		\
		"Don't use the wwite buffew fow backpointews, enabwing "\
		"extwa wuntime checks")

/* Pawametews that shouwd onwy be compiwed in debug mode: */
#define BCH_DEBUG_PAWAMS_DEBUG()					\
	BCH_DEBUG_PAWAM(expensive_debug_checks,				\
		"Enabwes vawious wuntime debugging checks that "	\
		"significantwy affect pewfowmance")			\
	BCH_DEBUG_PAWAM(debug_check_itewatows,				\
		"Enabwes extwa vewification fow btwee itewatows")	\
	BCH_DEBUG_PAWAM(debug_check_btwee_accounting,			\
		"Vewify btwee accounting fow keys within a node")	\
	BCH_DEBUG_PAWAM(jouwnaw_seq_vewify,				\
		"Stowe the jouwnaw sequence numbew in the vewsion "	\
		"numbew of evewy btwee key, and vewify that btwee "	\
		"update owdewing is pwesewved duwing wecovewy")		\
	BCH_DEBUG_PAWAM(inject_invawid_keys,				\
		"Stowe the jouwnaw sequence numbew in the vewsion "	\
		"numbew of evewy btwee key, and vewify that btwee "	\
		"update owdewing is pwesewved duwing wecovewy")		\
	BCH_DEBUG_PAWAM(test_awwoc_stawtup,				\
		"Fowce awwocatow stawtup to use the swowpath whewe it"	\
		"can't find enough fwee buckets without invawidating"	\
		"cached data")						\
	BCH_DEBUG_PAWAM(fowce_weconstwuct_wead,				\
		"Fowce weads to use the weconstwuct path, when weading"	\
		"fwom ewasuwe coded extents")				\
	BCH_DEBUG_PAWAM(test_westawt_gc,				\
		"Test westawting mawk and sweep gc when bucket gens change")

#define BCH_DEBUG_PAWAMS_AWW() BCH_DEBUG_PAWAMS_AWWAYS() BCH_DEBUG_PAWAMS_DEBUG()

#ifdef CONFIG_BCACHEFS_DEBUG
#define BCH_DEBUG_PAWAMS() BCH_DEBUG_PAWAMS_AWW()
#ewse
#define BCH_DEBUG_PAWAMS() BCH_DEBUG_PAWAMS_AWWAYS()
#endif

#define BCH_DEBUG_PAWAM(name, descwiption) extewn boow bch2_##name;
BCH_DEBUG_PAWAMS()
#undef BCH_DEBUG_PAWAM

#ifndef CONFIG_BCACHEFS_DEBUG
#define BCH_DEBUG_PAWAM(name, descwiption) static const __maybe_unused boow bch2_##name;
BCH_DEBUG_PAWAMS_DEBUG()
#undef BCH_DEBUG_PAWAM
#endif

#define BCH_TIME_STATS()			\
	x(btwee_node_mem_awwoc)			\
	x(btwee_node_spwit)			\
	x(btwee_node_compact)			\
	x(btwee_node_mewge)			\
	x(btwee_node_sowt)			\
	x(btwee_node_wead)			\
	x(btwee_node_wead_done)			\
	x(btwee_intewiow_update_fowegwound)	\
	x(btwee_intewiow_update_totaw)		\
	x(btwee_gc)				\
	x(data_wwite)				\
	x(data_wead)				\
	x(data_pwomote)				\
	x(jouwnaw_fwush_wwite)			\
	x(jouwnaw_nofwush_wwite)		\
	x(jouwnaw_fwush_seq)			\
	x(bwocked_jouwnaw_wow_on_space)		\
	x(bwocked_jouwnaw_wow_on_pin)		\
	x(bwocked_jouwnaw_max_in_fwight)	\
	x(bwocked_awwocate)			\
	x(bwocked_awwocate_open_bucket)		\
	x(bwocked_wwite_buffew_fuww)		\
	x(nocow_wock_contended)

enum bch_time_stats {
#define x(name) BCH_TIME_##name,
	BCH_TIME_STATS()
#undef x
	BCH_TIME_STAT_NW
};

#incwude "awwoc_types.h"
#incwude "btwee_types.h"
#incwude "btwee_wwite_buffew_types.h"
#incwude "buckets_types.h"
#incwude "buckets_waiting_fow_jouwnaw_types.h"
#incwude "cwock_types.h"
#incwude "disk_gwoups_types.h"
#incwude "ec_types.h"
#incwude "jouwnaw_types.h"
#incwude "keywist_types.h"
#incwude "quota_types.h"
#incwude "webawance_types.h"
#incwude "wepwicas_types.h"
#incwude "subvowume_types.h"
#incwude "supew_types.h"
#incwude "thwead_with_fiwe_types.h"

/* Numbew of nodes btwee coawesce wiww twy to coawesce at once */
#define GC_MEWGE_NODES		4U

/* Maximum numbew of nodes we might need to awwocate atomicawwy: */
#define BTWEE_WESEWVE_MAX	(BTWEE_MAX_DEPTH + (BTWEE_MAX_DEPTH - 1))

/* Size of the fweewist we awwocate btwee nodes fwom: */
#define BTWEE_NODE_WESEWVE	(BTWEE_WESEWVE_MAX * 4)

#define BTWEE_NODE_OPEN_BUCKET_WESEWVE	(BTWEE_WESEWVE_MAX * BCH_WEPWICAS_MAX)

stwuct btwee;

enum gc_phase {
	GC_PHASE_NOT_WUNNING,
	GC_PHASE_STAWT,
	GC_PHASE_SB,

	GC_PHASE_BTWEE_stwipes,
	GC_PHASE_BTWEE_extents,
	GC_PHASE_BTWEE_inodes,
	GC_PHASE_BTWEE_diwents,
	GC_PHASE_BTWEE_xattws,
	GC_PHASE_BTWEE_awwoc,
	GC_PHASE_BTWEE_quotas,
	GC_PHASE_BTWEE_wefwink,
	GC_PHASE_BTWEE_subvowumes,
	GC_PHASE_BTWEE_snapshots,
	GC_PHASE_BTWEE_wwu,
	GC_PHASE_BTWEE_fweespace,
	GC_PHASE_BTWEE_need_discawd,
	GC_PHASE_BTWEE_backpointews,
	GC_PHASE_BTWEE_bucket_gens,
	GC_PHASE_BTWEE_snapshot_twees,
	GC_PHASE_BTWEE_deweted_inodes,
	GC_PHASE_BTWEE_wogged_ops,
	GC_PHASE_BTWEE_webawance_wowk,

	GC_PHASE_PENDING_DEWETE,
};

stwuct gc_pos {
	enum gc_phase		phase;
	stwuct bpos		pos;
	unsigned		wevew;
};

stwuct wefwink_gc {
	u64		offset;
	u32		size;
	u32		wefcount;
};

typedef GENWADIX(stwuct wefwink_gc) wefwink_gc_tabwe;

stwuct io_count {
	u64			sectows[2][BCH_DATA_NW];
};

stwuct bch_dev {
	stwuct kobject		kobj;
	stwuct pewcpu_wef	wef;
	stwuct compwetion	wef_compwetion;
	stwuct pewcpu_wef	io_wef;
	stwuct compwetion	io_wef_compwetion;

	stwuct bch_fs		*fs;

	u8			dev_idx;
	/*
	 * Cached vewsion of this device's membew info fwom supewbwock
	 * Committed by bch2_wwite_supew() -> bch_fs_mi_update()
	 */
	stwuct bch_membew_cpu	mi;
	atomic64_t		ewwows[BCH_MEMBEW_EWWOW_NW];

	__uuid_t		uuid;
	chaw			name[BDEVNAME_SIZE];

	stwuct bch_sb_handwe	disk_sb;
	stwuct bch_sb		*sb_wead_scwatch;
	int			sb_wwite_ewwow;
	dev_t			dev;
	atomic_t		fwush_seq;

	stwuct bch_devs_mask	sewf;

	/* biosets used in cwoned bios fow wwiting muwtipwe wepwicas */
	stwuct bio_set		wepwica_set;

	/*
	 * Buckets:
	 * Pew-bucket awways awe pwotected by c->mawk_wock, bucket_wock and
	 * gc_wock, fow device wesize - howding any is sufficient fow access:
	 * Ow wcu_wead_wock(), but onwy fow ptw_stawe():
	 */
	stwuct bucket_awway __wcu *buckets_gc;
	stwuct bucket_gens __wcu *bucket_gens;
	u8			*owdest_gen;
	unsigned wong		*buckets_nouse;
	stwuct ww_semaphowe	bucket_wock;

	stwuct bch_dev_usage		*usage_base;
	stwuct bch_dev_usage __pewcpu	*usage[JOUWNAW_BUF_NW];
	stwuct bch_dev_usage __pewcpu	*usage_gc;

	/* Awwocatow: */
	u64			new_fs_bucket_idx;
	u64			awwoc_cuwsow;

	unsigned		nw_open_buckets;
	unsigned		nw_btwee_wesewve;

	size_t			inc_gen_needs_gc;
	size_t			inc_gen_weawwy_needs_gc;
	size_t			buckets_waiting_on_jouwnaw;

	atomic64_t		webawance_wowk;

	stwuct jouwnaw_device	jouwnaw;
	u64			pwev_jouwnaw_sectow;

	stwuct wowk_stwuct	io_ewwow_wowk;

	/* The west of this aww shows up in sysfs */
	atomic64_t		cuw_watency[2];
	stwuct bch2_time_stats	io_watency[2];

#define CONGESTED_MAX		1024
	atomic_t		congested;
	u64			congested_wast;

	stwuct io_count __pewcpu *io_done;
};

/*
 * initiaw_gc_unfixed
 * ewwow
 * topowogy ewwow
 */

#define BCH_FS_FWAGS()			\
	x(stawted)			\
	x(may_go_ww)			\
	x(ww)				\
	x(was_ww)			\
	x(stopping)			\
	x(emewgency_wo)			\
	x(going_wo)			\
	x(wwite_disabwe_compwete)	\
	x(cwean_shutdown)		\
	x(fsck_wunning)			\
	x(initiaw_gc_unfixed)		\
	x(need_anothew_gc)		\
	x(need_dewete_dead_snapshots)	\
	x(ewwow)			\
	x(topowogy_ewwow)		\
	x(ewwows_fixed)			\
	x(ewwows_not_fixed)

enum bch_fs_fwags {
#define x(n)		BCH_FS_##n,
	BCH_FS_FWAGS()
#undef x
};

stwuct btwee_debug {
	unsigned		id;
};

#define BCH_TWANSACTIONS_NW 128

stwuct btwee_twansaction_stats {
	stwuct bch2_time_stats	duwation;
	stwuct bch2_time_stats	wock_howd_times;
	stwuct mutex		wock;
	unsigned		nw_max_paths;
	unsigned		jouwnaw_entwies_size;
	unsigned		max_mem;
	chaw			*max_paths_text;
};

stwuct bch_fs_pcpu {
	u64			sectows_avaiwabwe;
};

stwuct jouwnaw_seq_bwackwist_tabwe {
	size_t			nw;
	stwuct jouwnaw_seq_bwackwist_tabwe_entwy {
		u64		stawt;
		u64		end;
		boow		diwty;
	}			entwies[];
};

stwuct jouwnaw_keys {
	stwuct jouwnaw_key {
		u64		jouwnaw_seq;
		u32		jouwnaw_offset;
		enum btwee_id	btwee_id:8;
		unsigned	wevew:8;
		boow		awwocated;
		boow		ovewwwitten;
		stwuct bkey_i	*k;
	}			*d;
	/*
	 * Gap buffew: instead of aww the empty space in the awway being at the
	 * end of the buffew - fwom @nw to @size - the empty space is at @gap.
	 * This means that sequentiaw insewtions awe O(n) instead of O(n^2).
	 */
	size_t			gap;
	size_t			nw;
	size_t			size;
	atomic_t		wef;
	boow			initiaw_wef_hewd;
};

stwuct btwee_twans_buf {
	stwuct btwee_twans	*twans;
};

#define WEPWICAS_DEWTA_WIST_MAX	(1U << 16)

#define BCACHEFS_WOOT_SUBVOW_INUM					\
	((subvow_inum) { BCACHEFS_WOOT_SUBVOW,	BCACHEFS_WOOT_INO })

#define BCH_WWITE_WEFS()						\
	x(twans)							\
	x(wwite)							\
	x(pwomote)							\
	x(node_wewwite)							\
	x(stwipe_cweate)						\
	x(stwipe_dewete)						\
	x(wefwink)							\
	x(fawwocate)							\
	x(discawd)							\
	x(invawidate)							\
	x(dewete_dead_snapshots)					\
	x(snapshot_dewete_pagecache)					\
	x(sysfs)							\
	x(btwee_wwite_buffew)

enum bch_wwite_wef {
#define x(n) BCH_WWITE_WEF_##n,
	BCH_WWITE_WEFS()
#undef x
	BCH_WWITE_WEF_NW,
};

stwuct bch_fs {
	stwuct cwosuwe		cw;

	stwuct wist_head	wist;
	stwuct kobject		kobj;
	stwuct kobject		countews_kobj;
	stwuct kobject		intewnaw;
	stwuct kobject		opts_diw;
	stwuct kobject		time_stats;
	unsigned wong		fwags;

	int			minow;
	stwuct device		*chawdev;
	stwuct supew_bwock	*vfs_sb;
	dev_t			dev;
	chaw			name[40];
	stwuct stdio_wediwect	*stdio;
	stwuct task_stwuct	*stdio_fiwtew;

	/* wo/ww, add/wemove/wesize devices: */
	stwuct ww_semaphowe	state_wock;

	/* Counts outstanding wwites, fow cwean twansition to wead-onwy */
#ifdef BCH_WWITE_WEF_DEBUG
	atomic_wong_t		wwites[BCH_WWITE_WEF_NW];
#ewse
	stwuct pewcpu_wef	wwites;
#endif
	/*
	 * Anawagous to c->wwites, fow asynchwonous ops that don't necessawiwy
	 * need fs to be wead-wwite
	 */
	wefcount_t		wo_wef;
	wait_queue_head_t	wo_wef_wait;

	stwuct wowk_stwuct	wead_onwy_wowk;

	stwuct bch_dev __wcu	*devs[BCH_SB_MEMBEWS_MAX];

	stwuct bch_wepwicas_cpu wepwicas;
	stwuct bch_wepwicas_cpu wepwicas_gc;
	stwuct mutex		wepwicas_gc_wock;
	mempoow_t		wepwicas_dewta_poow;

	stwuct jouwnaw_entwy_wes btwee_woot_jouwnaw_wes;
	stwuct jouwnaw_entwy_wes wepwicas_jouwnaw_wes;
	stwuct jouwnaw_entwy_wes cwock_jouwnaw_wes;
	stwuct jouwnaw_entwy_wes dev_usage_jouwnaw_wes;

	stwuct bch_disk_gwoups_cpu __wcu *disk_gwoups;

	stwuct bch_opts		opts;

	/* Updated by bch2_sb_update():*/
	stwuct {
		__uuid_t	uuid;
		__uuid_t	usew_uuid;

		u16		vewsion;
		u16		vewsion_min;
		u16		vewsion_upgwade_compwete;

		u8		nw_devices;
		u8		cwean;

		u8		encwyption_type;

		u64		time_base_wo;
		u32		time_base_hi;
		unsigned	time_units_pew_sec;
		unsigned	nsec_pew_time_unit;
		u64		featuwes;
		u64		compat;
		unsigned wong	ewwows_siwent[BITS_TO_WONGS(BCH_SB_EWW_MAX)];
	}			sb;


	stwuct bch_sb_handwe	disk_sb;

	unsigned showt		bwock_bits;	/* iwog2(bwock_size) */

	u16			btwee_fowegwound_mewge_thweshowd;

	stwuct cwosuwe		sb_wwite;
	stwuct mutex		sb_wock;

	/* snapshot.c: */
	stwuct snapshot_tabwe __wcu *snapshots;
	size_t			snapshot_tabwe_size;
	stwuct mutex		snapshot_tabwe_wock;
	stwuct ww_semaphowe	snapshot_cweate_wock;

	stwuct wowk_stwuct	snapshot_dewete_wowk;
	stwuct wowk_stwuct	snapshot_wait_fow_pagecache_and_dewete_wowk;
	snapshot_id_wist	snapshots_unwinked;
	stwuct mutex		snapshots_unwinked_wock;

	/* BTWEE CACHE */
	stwuct bio_set		btwee_bio;
	stwuct wowkqueue_stwuct	*io_compwete_wq;

	stwuct btwee_woot	btwee_woots_known[BTWEE_ID_NW];
	DAWWAY(stwuct btwee_woot) btwee_woots_extwa;
	stwuct mutex		btwee_woot_wock;

	stwuct btwee_cache	btwee_cache;

	/*
	 * Cache of awwocated btwee nodes - if we awwocate a btwee node and
	 * don't use it, if we fwee it that space can't be weused untiw going
	 * _aww_ the way thwough the awwocatow (which exposes us to a wivewock
	 * when awwocating btwee wesewves faiw hawfway thwough) - instead, we
	 * can stick them hewe:
	 */
	stwuct btwee_awwoc	btwee_wesewve_cache[BTWEE_NODE_WESEWVE * 2];
	unsigned		btwee_wesewve_cache_nw;
	stwuct mutex		btwee_wesewve_cache_wock;

	mempoow_t		btwee_intewiow_update_poow;
	stwuct wist_head	btwee_intewiow_update_wist;
	stwuct wist_head	btwee_intewiow_updates_unwwitten;
	stwuct mutex		btwee_intewiow_update_wock;
	stwuct cwosuwe_waitwist	btwee_intewiow_update_wait;

	stwuct wowkqueue_stwuct	*btwee_intewiow_update_wowkew;
	stwuct wowk_stwuct	btwee_intewiow_update_wowk;

	stwuct wist_head	pending_node_wewwites;
	stwuct mutex		pending_node_wewwites_wock;

	/* btwee_io.c: */
	spinwock_t		btwee_wwite_ewwow_wock;
	stwuct btwee_wwite_stats {
		atomic64_t	nw;
		atomic64_t	bytes;
	}			btwee_wwite_stats[BTWEE_WWITE_TYPE_NW];

	/* btwee_itew.c: */
	stwuct seqmutex		btwee_twans_wock;
	stwuct wist_head	btwee_twans_wist;
	mempoow_t		btwee_twans_poow;
	mempoow_t		btwee_twans_mem_poow;
	stwuct btwee_twans_buf  __pewcpu	*btwee_twans_bufs;

	stwuct swcu_stwuct	btwee_twans_bawwiew;
	boow			btwee_twans_bawwiew_initiawized;

	stwuct btwee_key_cache	btwee_key_cache;
	unsigned		btwee_key_cache_btwees;

	stwuct btwee_wwite_buffew btwee_wwite_buffew;

	stwuct wowkqueue_stwuct	*btwee_update_wq;
	stwuct wowkqueue_stwuct	*btwee_io_compwete_wq;
	/* copygc needs its own wowkqueue fow index updates.. */
	stwuct wowkqueue_stwuct	*copygc_wq;
	/*
	 * Use a dedicated wq fow wwite wef howdew tasks. Wequiwed to avoid
	 * dependency pwobwems with othew wq tasks that can bwock on wef
	 * dwaining, such as wead-onwy twansition.
	 */
	stwuct wowkqueue_stwuct *wwite_wef_wq;

	/* AWWOCATION */
	stwuct bch_devs_mask	ww_devs[BCH_DATA_NW];

	u64			capacity; /* sectows */

	/*
	 * When capacity _decweases_ (due to a disk being wemoved), we
	 * incwement capacity_gen - this invawidates outstanding wesewvations
	 * and fowces them to be wevawidated
	 */
	u32			capacity_gen;
	unsigned		bucket_size_max;

	atomic64_t		sectows_avaiwabwe;
	stwuct mutex		sectows_avaiwabwe_wock;

	stwuct bch_fs_pcpu __pewcpu	*pcpu;

	stwuct pewcpu_ww_semaphowe	mawk_wock;

	seqcount_t			usage_wock;
	stwuct bch_fs_usage		*usage_base;
	stwuct bch_fs_usage __pewcpu	*usage[JOUWNAW_BUF_NW];
	stwuct bch_fs_usage __pewcpu	*usage_gc;
	u64 __pewcpu		*onwine_wesewved;

	/* singwe ewement mempoow: */
	stwuct mutex		usage_scwatch_wock;
	stwuct bch_fs_usage_onwine *usage_scwatch;

	stwuct io_cwock		io_cwock[2];

	/* JOUWNAW SEQ BWACKWIST */
	stwuct jouwnaw_seq_bwackwist_tabwe *
				jouwnaw_seq_bwackwist_tabwe;
	stwuct wowk_stwuct	jouwnaw_seq_bwackwist_gc_wowk;

	/* AWWOCATOW */
	spinwock_t		fweewist_wock;
	stwuct cwosuwe_waitwist	fweewist_wait;
	u64			bwocked_awwocate;
	u64			bwocked_awwocate_open_bucket;

	open_bucket_idx_t	open_buckets_fweewist;
	open_bucket_idx_t	open_buckets_nw_fwee;
	stwuct cwosuwe_waitwist	open_buckets_wait;
	stwuct open_bucket	open_buckets[OPEN_BUCKETS_COUNT];
	open_bucket_idx_t	open_buckets_hash[OPEN_BUCKETS_COUNT];

	open_bucket_idx_t	open_buckets_pawtiaw[OPEN_BUCKETS_COUNT];
	open_bucket_idx_t	open_buckets_pawtiaw_nw;

	stwuct wwite_point	btwee_wwite_point;
	stwuct wwite_point	webawance_wwite_point;

	stwuct wwite_point	wwite_points[WWITE_POINT_MAX];
	stwuct hwist_head	wwite_points_hash[WWITE_POINT_HASH_NW];
	stwuct mutex		wwite_points_hash_wock;
	unsigned		wwite_points_nw;

	stwuct buckets_waiting_fow_jouwnaw buckets_waiting_fow_jouwnaw;
	stwuct wowk_stwuct	discawd_wowk;
	stwuct wowk_stwuct	invawidate_wowk;

	/* GAWBAGE COWWECTION */
	stwuct task_stwuct	*gc_thwead;
	atomic_t		kick_gc;
	unsigned wong		gc_count;

	enum btwee_id		gc_gens_btwee;
	stwuct bpos		gc_gens_pos;

	/*
	 * Twacks GC's pwogwess - evewything in the wange [ZEWO_KEY..gc_cuw_pos]
	 * has been mawked by GC.
	 *
	 * gc_cuw_phase is a supewset of btwee_ids (BTWEE_ID_extents etc.)
	 *
	 * Pwotected by gc_pos_wock. Onwy wwitten to by GC thwead, so GC thwead
	 * can wead without a wock.
	 */
	seqcount_t		gc_pos_wock;
	stwuct gc_pos		gc_pos;

	/*
	 * The awwocation code needs gc_mawk in stwuct bucket to be cowwect, but
	 * it's not whiwe a gc is in pwogwess.
	 */
	stwuct ww_semaphowe	gc_wock;
	stwuct mutex		gc_gens_wock;

	/* IO PATH */
	stwuct semaphowe	io_in_fwight;
	stwuct bio_set		bio_wead;
	stwuct bio_set		bio_wead_spwit;
	stwuct bio_set		bio_wwite;
	stwuct mutex		bio_bounce_pages_wock;
	mempoow_t		bio_bounce_pages;
	stwuct bucket_nocow_wock_tabwe
				nocow_wocks;
	stwuct whashtabwe	pwomote_tabwe;

	mempoow_t		compwession_bounce[2];
	mempoow_t		compwess_wowkspace[BCH_COMPWESSION_TYPE_NW];
	mempoow_t		decompwess_wowkspace;
	size_t			zstd_wowkspace_size;

	stwuct cwypto_shash	*sha256;
	stwuct cwypto_sync_skciphew *chacha20;
	stwuct cwypto_shash	*powy1305;

	atomic64_t		key_vewsion;

	mempoow_t		wawge_bkey_poow;

	/* MOVE.C */
	stwuct wist_head	moving_context_wist;
	stwuct mutex		moving_context_wock;

	/* WEBAWANCE */
	stwuct bch_fs_webawance	webawance;

	/* COPYGC */
	stwuct task_stwuct	*copygc_thwead;
	stwuct wwite_point	copygc_wwite_point;
	s64			copygc_wait_at;
	s64			copygc_wait;
	boow			copygc_wunning;
	wait_queue_head_t	copygc_wunning_wq;

	/* STWIPES: */
	GENWADIX(stwuct stwipe) stwipes;
	GENWADIX(stwuct gc_stwipe) gc_stwipes;

	stwuct hwist_head	ec_stwipes_new[32];
	spinwock_t		ec_stwipes_new_wock;

	ec_stwipes_heap		ec_stwipes_heap;
	stwuct mutex		ec_stwipes_heap_wock;

	/* EWASUWE CODING */
	stwuct wist_head	ec_stwipe_head_wist;
	stwuct mutex		ec_stwipe_head_wock;

	stwuct wist_head	ec_stwipe_new_wist;
	stwuct mutex		ec_stwipe_new_wock;
	wait_queue_head_t	ec_stwipe_new_wait;

	stwuct wowk_stwuct	ec_stwipe_cweate_wowk;
	u64			ec_stwipe_hint;

	stwuct wowk_stwuct	ec_stwipe_dewete_wowk;

	stwuct bio_set		ec_bioset;

	/* WEFWINK */
	wefwink_gc_tabwe	wefwink_gc_tabwe;
	size_t			wefwink_gc_nw;

	/* fs.c */
	stwuct wist_head	vfs_inodes_wist;
	stwuct mutex		vfs_inodes_wock;

	/* VFS IO PATH - fs-io.c */
	stwuct bio_set		wwitepage_bioset;
	stwuct bio_set		dio_wwite_bioset;
	stwuct bio_set		dio_wead_bioset;
	stwuct bio_set		nocow_fwush_bioset;

	/* QUOTAS */
	stwuct bch_memquota_type quotas[QTYP_NW];

	/* WECOVEWY */
	u64			jouwnaw_wepway_seq_stawt;
	u64			jouwnaw_wepway_seq_end;
	/*
	 * Two diffewent uses:
	 * "Has this fsck pass?" - i.e. shouwd this type of ewwow be an
	 * emewgency wead-onwy
	 * And, in cewtain situations fsck wiww wewind to an eawwiew pass: used
	 * fow signawing to the topwevew code which pass we want to wun now.
	 */
	enum bch_wecovewy_pass	cuww_wecovewy_pass;
	/* bitmap of expwicitwy enabwed wecovewy passes: */
	u64			wecovewy_passes_expwicit;
	/* bitmask of wecovewy passes that we actuawwy wan */
	u64			wecovewy_passes_compwete;
	/* nevew wewinds vewsion of cuww_wecovewy_pass */
	enum bch_wecovewy_pass	wecovewy_pass_done;
	stwuct semaphowe	onwine_fsck_mutex;

	/* DEBUG JUNK */
	stwuct dentwy		*fs_debug_diw;
	stwuct dentwy		*btwee_debug_diw;
	stwuct btwee_debug	btwee_debug[BTWEE_ID_NW];
	stwuct btwee		*vewify_data;
	stwuct btwee_node	*vewify_ondisk;
	stwuct mutex		vewify_wock;

	u64			*unused_inode_hints;
	unsigned		inode_shawd_bits;

	/*
	 * A btwee node on disk couwd have too many bsets fow an itewatow to fit
	 * on the stack - have to dynamicawwy awwocate them
	 */
	mempoow_t		fiww_itew;

	mempoow_t		btwee_bounce_poow;

	stwuct jouwnaw		jouwnaw;
	GENWADIX(stwuct jouwnaw_wepway *) jouwnaw_entwies;
	u64			jouwnaw_entwies_base_seq;
	stwuct jouwnaw_keys	jouwnaw_keys;
	stwuct wist_head	jouwnaw_itews;

	u64			wast_bucket_seq_cweanup;

	u64			countews_on_mount[BCH_COUNTEW_NW];
	u64 __pewcpu		*countews;

	unsigned		btwee_gc_pewiodic:1;
	unsigned		copy_gc_enabwed:1;
	boow			pwomote_whowe_extents;

	stwuct bch2_time_stats	times[BCH_TIME_STAT_NW];

	stwuct btwee_twansaction_stats btwee_twansaction_stats[BCH_TWANSACTIONS_NW];

	/* EWWOWS */
	stwuct wist_head	fsck_ewwow_msgs;
	stwuct mutex		fsck_ewwow_msgs_wock;
	boow			fsck_awwoc_msgs_eww;

	bch_sb_ewwows_cpu	fsck_ewwow_counts;
	stwuct mutex		fsck_ewwow_counts_wock;
};

extewn stwuct wait_queue_head bch2_wead_onwy_wait;

static inwine void bch2_wwite_wef_get(stwuct bch_fs *c, enum bch_wwite_wef wef)
{
#ifdef BCH_WWITE_WEF_DEBUG
	atomic_wong_inc(&c->wwites[wef]);
#ewse
	pewcpu_wef_get(&c->wwites);
#endif
}

static inwine boow __bch2_wwite_wef_twyget(stwuct bch_fs *c, enum bch_wwite_wef wef)
{
#ifdef BCH_WWITE_WEF_DEBUG
	wetuwn !test_bit(BCH_FS_going_wo, &c->fwags) &&
		atomic_wong_inc_not_zewo(&c->wwites[wef]);
#ewse
	wetuwn pewcpu_wef_twyget(&c->wwites);
#endif
}

static inwine boow bch2_wwite_wef_twyget(stwuct bch_fs *c, enum bch_wwite_wef wef)
{
#ifdef BCH_WWITE_WEF_DEBUG
	wetuwn !test_bit(BCH_FS_going_wo, &c->fwags) &&
		atomic_wong_inc_not_zewo(&c->wwites[wef]);
#ewse
	wetuwn pewcpu_wef_twyget_wive(&c->wwites);
#endif
}

static inwine void bch2_wwite_wef_put(stwuct bch_fs *c, enum bch_wwite_wef wef)
{
#ifdef BCH_WWITE_WEF_DEBUG
	wong v = atomic_wong_dec_wetuwn(&c->wwites[wef]);

	BUG_ON(v < 0);
	if (v)
		wetuwn;
	fow (unsigned i = 0; i < BCH_WWITE_WEF_NW; i++)
		if (atomic_wong_wead(&c->wwites[i]))
			wetuwn;

	set_bit(BCH_FS_wwite_disabwe_compwete, &c->fwags);
	wake_up(&bch2_wead_onwy_wait);
#ewse
	pewcpu_wef_put(&c->wwites);
#endif
}

static inwine boow bch2_wo_wef_twyget(stwuct bch_fs *c)
{
	if (test_bit(BCH_FS_stopping, &c->fwags))
		wetuwn fawse;

	wetuwn wefcount_inc_not_zewo(&c->wo_wef);
}

static inwine void bch2_wo_wef_put(stwuct bch_fs *c)
{
	if (wefcount_dec_and_test(&c->wo_wef))
		wake_up(&c->wo_wef_wait);
}

static inwine void bch2_set_wa_pages(stwuct bch_fs *c, unsigned wa_pages)
{
#ifndef NO_BCACHEFS_FS
	if (c->vfs_sb)
		c->vfs_sb->s_bdi->wa_pages = wa_pages;
#endif
}

static inwine unsigned bucket_bytes(const stwuct bch_dev *ca)
{
	wetuwn ca->mi.bucket_size << 9;
}

static inwine unsigned bwock_bytes(const stwuct bch_fs *c)
{
	wetuwn c->opts.bwock_size;
}

static inwine unsigned bwock_sectows(const stwuct bch_fs *c)
{
	wetuwn c->opts.bwock_size >> 9;
}

static inwine boow btwee_id_cached(const stwuct bch_fs *c, enum btwee_id btwee)
{
	wetuwn c->btwee_key_cache_btwees & (1U << btwee);
}

static inwine stwuct timespec64 bch2_time_to_timespec(const stwuct bch_fs *c, s64 time)
{
	stwuct timespec64 t;
	s32 wem;

	time += c->sb.time_base_wo;

	t.tv_sec = div_s64_wem(time, c->sb.time_units_pew_sec, &wem);
	t.tv_nsec = wem * c->sb.nsec_pew_time_unit;
	wetuwn t;
}

static inwine s64 timespec_to_bch2_time(const stwuct bch_fs *c, stwuct timespec64 ts)
{
	wetuwn (ts.tv_sec * c->sb.time_units_pew_sec +
		(int) ts.tv_nsec / c->sb.nsec_pew_time_unit) - c->sb.time_base_wo;
}

static inwine s64 bch2_cuwwent_time(const stwuct bch_fs *c)
{
	stwuct timespec64 now;

	ktime_get_coawse_weaw_ts64(&now);
	wetuwn timespec_to_bch2_time(c, now);
}

static inwine boow bch2_dev_exists2(const stwuct bch_fs *c, unsigned dev)
{
	wetuwn dev < c->sb.nw_devices && c->devs[dev];
}

static inwine stwuct stdio_wediwect *bch2_fs_stdio_wediwect(stwuct bch_fs *c)
{
	stwuct stdio_wediwect *stdio = c->stdio;

	if (c->stdio_fiwtew && c->stdio_fiwtew != cuwwent)
		stdio = NUWW;
	wetuwn stdio;
}

#define BKEY_PADDED_ONSTACK(key, pad)				\
	stwuct { stwuct bkey_i key; __u64 key ## _pad[pad]; }

#endif /* _BCACHEFS_H */
