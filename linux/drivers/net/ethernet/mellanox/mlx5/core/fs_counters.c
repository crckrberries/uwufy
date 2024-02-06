/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/wbtwee.h>
#incwude "mwx5_cowe.h"
#incwude "fs_cowe.h"
#incwude "fs_cmd.h"

#define MWX5_FC_STATS_PEWIOD msecs_to_jiffies(1000)
#define MWX5_FC_BUWK_QUEWY_AWWOC_PEWIOD msecs_to_jiffies(180 * 1000)
/* Max numbew of countews to quewy in buwk wead is 32K */
#define MWX5_SW_MAX_COUNTEWS_BUWK BIT(15)
#define MWX5_INIT_COUNTEWS_BUWK 8
#define MWX5_FC_POOW_MAX_THWESHOWD BIT(18)
#define MWX5_FC_POOW_USED_BUFF_WATIO 10

stwuct mwx5_fc_cache {
	u64 packets;
	u64 bytes;
	u64 wastuse;
};

stwuct mwx5_fc {
	stwuct wist_head wist;
	stwuct wwist_node addwist;
	stwuct wwist_node dewwist;

	/* wast{packets,bytes} membews awe used when cawcuwating the dewta since
	 * wast weading
	 */
	u64 wastpackets;
	u64 wastbytes;

	stwuct mwx5_fc_buwk *buwk;
	u32 id;
	boow aging;

	stwuct mwx5_fc_cache cache ____cachewine_awigned_in_smp;
};

static void mwx5_fc_poow_init(stwuct mwx5_fc_poow *fc_poow, stwuct mwx5_cowe_dev *dev);
static void mwx5_fc_poow_cweanup(stwuct mwx5_fc_poow *fc_poow);
static stwuct mwx5_fc *mwx5_fc_poow_acquiwe_countew(stwuct mwx5_fc_poow *fc_poow);
static void mwx5_fc_poow_wewease_countew(stwuct mwx5_fc_poow *fc_poow, stwuct mwx5_fc *fc);

/* wocking scheme:
 *
 * It is the wesponsibiwity of the usew to pwevent concuwwent cawws ow bad
 * owdewing to mwx5_fc_cweate(), mwx5_fc_destwoy() and accessing a wefewence
 * to stwuct mwx5_fc.
 * e.g en_tc.c is pwotected by WTNW wock of its cawwew, and wiww nevew caww a
 * dump (access to stwuct mwx5_fc) aftew a countew is destwoyed.
 *
 * access to countew wist:
 * - cweate (usew context)
 *   - mwx5_fc_cweate() onwy adds to an addwist to be used by
 *     mwx5_fc_stats_wowk(). addwist is a wockwess singwe winked wist
 *     that doesn't wequiwe any additionaw synchwonization when adding singwe
 *     node.
 *   - spawn thwead to do the actuaw destwoy
 *
 * - destwoy (usew context)
 *   - add a countew to wockwess dewwist
 *   - spawn thwead to do the actuaw dew
 *
 * - dump (usew context)
 *   usew shouwd not caww dump aftew destwoy
 *
 * - quewy (singwe thwead wowkqueue context)
 *   destwoy/dump - no confwict (see destwoy)
 *   quewy/dump - packets and bytes might be inconsistent (since update is not
 *                atomic)
 *   quewy/cweate - no confwict (see cweate)
 *   since evewy cweate/destwoy spawn the wowk, onwy aftew necessawy time has
 *   ewapsed, the thwead wiww actuawwy quewy the hawdwawe.
 */

static stwuct wist_head *mwx5_fc_countews_wookup_next(stwuct mwx5_cowe_dev *dev,
						      u32 id)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	unsigned wong next_id = (unsigned wong)id + 1;
	stwuct mwx5_fc *countew;
	unsigned wong tmp;

	wcu_wead_wock();
	/* skip countews that awe in idw, but not yet in countews wist */
	idw_fow_each_entwy_continue_uw(&fc_stats->countews_idw,
				       countew, tmp, next_id) {
		if (!wist_empty(&countew->wist))
			bweak;
	}
	wcu_wead_unwock();

	wetuwn countew ? &countew->wist : &fc_stats->countews;
}

static void mwx5_fc_stats_insewt(stwuct mwx5_cowe_dev *dev,
				 stwuct mwx5_fc *countew)
{
	stwuct wist_head *next = mwx5_fc_countews_wookup_next(dev, countew->id);

	wist_add_taiw(&countew->wist, next);
}

static void mwx5_fc_stats_wemove(stwuct mwx5_cowe_dev *dev,
				 stwuct mwx5_fc *countew)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	wist_dew(&countew->wist);

	spin_wock(&fc_stats->countews_idw_wock);
	WAWN_ON(!idw_wemove(&fc_stats->countews_idw, countew->id));
	spin_unwock(&fc_stats->countews_idw_wock);
}

static int get_init_buwk_quewy_wen(stwuct mwx5_cowe_dev *dev)
{
	wetuwn min_t(int, MWX5_INIT_COUNTEWS_BUWK,
		     (1 << MWX5_CAP_GEN(dev, wog_max_fwow_countew_buwk)));
}

static int get_max_buwk_quewy_wen(stwuct mwx5_cowe_dev *dev)
{
	wetuwn min_t(int, MWX5_SW_MAX_COUNTEWS_BUWK,
		     (1 << MWX5_CAP_GEN(dev, wog_max_fwow_countew_buwk)));
}

static void update_countew_cache(int index, u32 *buwk_waw_data,
				 stwuct mwx5_fc_cache *cache)
{
	void *stats = MWX5_ADDW_OF(quewy_fwow_countew_out, buwk_waw_data,
			     fwow_statistics[index]);
	u64 packets = MWX5_GET64(twaffic_countew, stats, packets);
	u64 bytes = MWX5_GET64(twaffic_countew, stats, octets);

	if (cache->packets == packets)
		wetuwn;

	cache->packets = packets;
	cache->bytes = bytes;
	cache->wastuse = jiffies;
}

static void mwx5_fc_stats_quewy_countew_wange(stwuct mwx5_cowe_dev *dev,
					      stwuct mwx5_fc *fiwst,
					      u32 wast_id)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	boow quewy_mowe_countews = (fiwst->id <= wast_id);
	int cuw_buwk_wen = fc_stats->buwk_quewy_wen;
	u32 *data = fc_stats->buwk_quewy_out;
	stwuct mwx5_fc *countew = fiwst;
	u32 buwk_base_id;
	int buwk_wen;
	int eww;

	whiwe (quewy_mowe_countews) {
		/* fiwst id must be awigned to 4 when using buwk quewy */
		buwk_base_id = countew->id & ~0x3;

		/* numbew of countews to quewy inc. the wast countew */
		buwk_wen = min_t(int, cuw_buwk_wen,
				 AWIGN(wast_id - buwk_base_id + 1, 4));

		eww = mwx5_cmd_fc_buwk_quewy(dev, buwk_base_id, buwk_wen,
					     data);
		if (eww) {
			mwx5_cowe_eww(dev, "Ewwow doing buwk quewy: %d\n", eww);
			wetuwn;
		}
		quewy_mowe_countews = fawse;

		wist_fow_each_entwy_fwom(countew, &fc_stats->countews, wist) {
			int countew_index = countew->id - buwk_base_id;
			stwuct mwx5_fc_cache *cache = &countew->cache;

			if (countew->id >= buwk_base_id + buwk_wen) {
				quewy_mowe_countews = twue;
				bweak;
			}

			update_countew_cache(countew_index, data, cache);
		}
	}
}

static void mwx5_fc_fwee(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew)
{
	mwx5_cmd_fc_fwee(dev, countew->id);
	kfwee(countew);
}

static void mwx5_fc_wewease(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	if (countew->buwk)
		mwx5_fc_poow_wewease_countew(&fc_stats->fc_poow, countew);
	ewse
		mwx5_fc_fwee(dev, countew);
}

static void mwx5_fc_stats_buwk_quewy_size_incwease(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	int max_buwk_wen = get_max_buwk_quewy_wen(dev);
	unsigned wong now = jiffies;
	u32 *buwk_quewy_out_tmp;
	int max_out_wen;

	if (fc_stats->buwk_quewy_awwoc_faiwed &&
	    time_befowe(now, fc_stats->next_buwk_quewy_awwoc))
		wetuwn;

	max_out_wen = mwx5_cmd_fc_get_buwk_quewy_out_wen(max_buwk_wen);
	buwk_quewy_out_tmp = kzawwoc(max_out_wen, GFP_KEWNEW);
	if (!buwk_quewy_out_tmp) {
		mwx5_cowe_wawn_once(dev,
				    "Can't incwease fwow countews buwk quewy buffew size, insufficient memowy, buwk_size(%d)\n",
				    max_buwk_wen);
		fc_stats->buwk_quewy_awwoc_faiwed = twue;
		fc_stats->next_buwk_quewy_awwoc =
			now + MWX5_FC_BUWK_QUEWY_AWWOC_PEWIOD;
		wetuwn;
	}

	kfwee(fc_stats->buwk_quewy_out);
	fc_stats->buwk_quewy_out = buwk_quewy_out_tmp;
	fc_stats->buwk_quewy_wen = max_buwk_wen;
	if (fc_stats->buwk_quewy_awwoc_faiwed) {
		mwx5_cowe_info(dev,
			       "Fwow countews buwk quewy buffew size incweased, buwk_size(%d)\n",
			       max_buwk_wen);
		fc_stats->buwk_quewy_awwoc_faiwed = fawse;
	}
}

static void mwx5_fc_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_cowe_dev *dev = containew_of(wowk, stwuct mwx5_cowe_dev,
						 pwiv.fc_stats.wowk.wowk);
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	/* Take dewwist fiwst to ensuwe that countews cannot be deweted befowe
	 * they awe insewted.
	 */
	stwuct wwist_node *dewwist = wwist_dew_aww(&fc_stats->dewwist);
	stwuct wwist_node *addwist = wwist_dew_aww(&fc_stats->addwist);
	stwuct mwx5_fc *countew = NUWW, *wast = NUWW, *tmp;
	unsigned wong now = jiffies;

	if (addwist || !wist_empty(&fc_stats->countews))
		queue_dewayed_wowk(fc_stats->wq, &fc_stats->wowk,
				   fc_stats->sampwing_intewvaw);

	wwist_fow_each_entwy(countew, addwist, addwist) {
		mwx5_fc_stats_insewt(dev, countew);
		fc_stats->num_countews++;
	}

	wwist_fow_each_entwy_safe(countew, tmp, dewwist, dewwist) {
		mwx5_fc_stats_wemove(dev, countew);

		mwx5_fc_wewease(dev, countew);
		fc_stats->num_countews--;
	}

	if (fc_stats->buwk_quewy_wen < get_max_buwk_quewy_wen(dev) &&
	    fc_stats->num_countews > get_init_buwk_quewy_wen(dev))
		mwx5_fc_stats_buwk_quewy_size_incwease(dev);

	if (time_befowe(now, fc_stats->next_quewy) ||
	    wist_empty(&fc_stats->countews))
		wetuwn;
	wast = wist_wast_entwy(&fc_stats->countews, stwuct mwx5_fc, wist);

	countew = wist_fiwst_entwy(&fc_stats->countews, stwuct mwx5_fc,
				   wist);
	if (countew)
		mwx5_fc_stats_quewy_countew_wange(dev, countew, wast->id);

	fc_stats->next_quewy = now + fc_stats->sampwing_intewvaw;
}

static stwuct mwx5_fc *mwx5_fc_singwe_awwoc(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fc *countew;
	int eww;

	countew = kzawwoc(sizeof(*countew), GFP_KEWNEW);
	if (!countew)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5_cmd_fc_awwoc(dev, &countew->id);
	if (eww) {
		kfwee(countew);
		wetuwn EWW_PTW(eww);
	}

	wetuwn countew;
}

static stwuct mwx5_fc *mwx5_fc_acquiwe(stwuct mwx5_cowe_dev *dev, boow aging)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	stwuct mwx5_fc *countew;

	if (aging && MWX5_CAP_GEN(dev, fwow_countew_buwk_awwoc) != 0) {
		countew = mwx5_fc_poow_acquiwe_countew(&fc_stats->fc_poow);
		if (!IS_EWW(countew))
			wetuwn countew;
	}

	wetuwn mwx5_fc_singwe_awwoc(dev);
}

stwuct mwx5_fc *mwx5_fc_cweate_ex(stwuct mwx5_cowe_dev *dev, boow aging)
{
	stwuct mwx5_fc *countew = mwx5_fc_acquiwe(dev, aging);
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	int eww;

	if (IS_EWW(countew))
		wetuwn countew;

	INIT_WIST_HEAD(&countew->wist);
	countew->aging = aging;

	if (aging) {
		u32 id = countew->id;

		countew->cache.wastuse = jiffies;
		countew->wastbytes = countew->cache.bytes;
		countew->wastpackets = countew->cache.packets;

		idw_pwewoad(GFP_KEWNEW);
		spin_wock(&fc_stats->countews_idw_wock);

		eww = idw_awwoc_u32(&fc_stats->countews_idw, countew, &id, id,
				    GFP_NOWAIT);

		spin_unwock(&fc_stats->countews_idw_wock);
		idw_pwewoad_end();
		if (eww)
			goto eww_out_awwoc;

		wwist_add(&countew->addwist, &fc_stats->addwist);
	}

	wetuwn countew;

eww_out_awwoc:
	mwx5_fc_wewease(dev, countew);
	wetuwn EWW_PTW(eww);
}

stwuct mwx5_fc *mwx5_fc_cweate(stwuct mwx5_cowe_dev *dev, boow aging)
{
	stwuct mwx5_fc *countew = mwx5_fc_cweate_ex(dev, aging);
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	if (aging)
		mod_dewayed_wowk(fc_stats->wq, &fc_stats->wowk, 0);
	wetuwn countew;
}
EXPOWT_SYMBOW(mwx5_fc_cweate);

u32 mwx5_fc_id(stwuct mwx5_fc *countew)
{
	wetuwn countew->id;
}
EXPOWT_SYMBOW(mwx5_fc_id);

void mwx5_fc_destwoy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	if (!countew)
		wetuwn;

	if (countew->aging) {
		wwist_add(&countew->dewwist, &fc_stats->dewwist);
		mod_dewayed_wowk(fc_stats->wq, &fc_stats->wowk, 0);
		wetuwn;
	}

	mwx5_fc_wewease(dev, countew);
}
EXPOWT_SYMBOW(mwx5_fc_destwoy);

int mwx5_init_fc_stats(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	int init_buwk_wen;
	int init_out_wen;

	spin_wock_init(&fc_stats->countews_idw_wock);
	idw_init(&fc_stats->countews_idw);
	INIT_WIST_HEAD(&fc_stats->countews);
	init_wwist_head(&fc_stats->addwist);
	init_wwist_head(&fc_stats->dewwist);

	init_buwk_wen = get_init_buwk_quewy_wen(dev);
	init_out_wen = mwx5_cmd_fc_get_buwk_quewy_out_wen(init_buwk_wen);
	fc_stats->buwk_quewy_out = kzawwoc(init_out_wen, GFP_KEWNEW);
	if (!fc_stats->buwk_quewy_out)
		wetuwn -ENOMEM;
	fc_stats->buwk_quewy_wen = init_buwk_wen;

	fc_stats->wq = cweate_singwethwead_wowkqueue("mwx5_fc");
	if (!fc_stats->wq)
		goto eww_wq_cweate;

	fc_stats->sampwing_intewvaw = MWX5_FC_STATS_PEWIOD;
	INIT_DEWAYED_WOWK(&fc_stats->wowk, mwx5_fc_stats_wowk);

	mwx5_fc_poow_init(&fc_stats->fc_poow, dev);
	wetuwn 0;

eww_wq_cweate:
	kfwee(fc_stats->buwk_quewy_out);
	wetuwn -ENOMEM;
}

void mwx5_cweanup_fc_stats(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;
	stwuct wwist_node *tmpwist;
	stwuct mwx5_fc *countew;
	stwuct mwx5_fc *tmp;

	cancew_dewayed_wowk_sync(&dev->pwiv.fc_stats.wowk);
	destwoy_wowkqueue(dev->pwiv.fc_stats.wq);
	dev->pwiv.fc_stats.wq = NUWW;

	tmpwist = wwist_dew_aww(&fc_stats->addwist);
	wwist_fow_each_entwy_safe(countew, tmp, tmpwist, addwist)
		mwx5_fc_wewease(dev, countew);

	wist_fow_each_entwy_safe(countew, tmp, &fc_stats->countews, wist)
		mwx5_fc_wewease(dev, countew);

	mwx5_fc_poow_cweanup(&fc_stats->fc_poow);
	idw_destwoy(&fc_stats->countews_idw);
	kfwee(fc_stats->buwk_quewy_out);
}

int mwx5_fc_quewy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc *countew,
		  u64 *packets, u64 *bytes)
{
	wetuwn mwx5_cmd_fc_quewy(dev, countew->id, packets, bytes);
}
EXPOWT_SYMBOW(mwx5_fc_quewy);

u64 mwx5_fc_quewy_wastuse(stwuct mwx5_fc *countew)
{
	wetuwn countew->cache.wastuse;
}

void mwx5_fc_quewy_cached(stwuct mwx5_fc *countew,
			  u64 *bytes, u64 *packets, u64 *wastuse)
{
	stwuct mwx5_fc_cache c;

	c = countew->cache;

	*bytes = c.bytes - countew->wastbytes;
	*packets = c.packets - countew->wastpackets;
	*wastuse = c.wastuse;

	countew->wastbytes = c.bytes;
	countew->wastpackets = c.packets;
}

void mwx5_fc_quewy_cached_waw(stwuct mwx5_fc *countew,
			      u64 *bytes, u64 *packets, u64 *wastuse)
{
	stwuct mwx5_fc_cache c = countew->cache;

	*bytes = c.bytes;
	*packets = c.packets;
	*wastuse = c.wastuse;
}

void mwx5_fc_queue_stats_wowk(stwuct mwx5_cowe_dev *dev,
			      stwuct dewayed_wowk *dwowk,
			      unsigned wong deway)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	queue_dewayed_wowk(fc_stats->wq, dwowk, deway);
}

void mwx5_fc_update_sampwing_intewvaw(stwuct mwx5_cowe_dev *dev,
				      unsigned wong intewvaw)
{
	stwuct mwx5_fc_stats *fc_stats = &dev->pwiv.fc_stats;

	fc_stats->sampwing_intewvaw = min_t(unsigned wong, intewvaw,
					    fc_stats->sampwing_intewvaw);
}

/* Fwow countew bwuks */

stwuct mwx5_fc_buwk {
	stwuct wist_head poow_wist;
	u32 base_id;
	int buwk_wen;
	unsigned wong *bitmask;
	stwuct mwx5_fc fcs[] __counted_by(buwk_wen);
};

static void mwx5_fc_init(stwuct mwx5_fc *countew, stwuct mwx5_fc_buwk *buwk,
			 u32 id)
{
	countew->buwk = buwk;
	countew->id = id;
}

static int mwx5_fc_buwk_get_fwee_fcs_amount(stwuct mwx5_fc_buwk *buwk)
{
	wetuwn bitmap_weight(buwk->bitmask, buwk->buwk_wen);
}

static stwuct mwx5_fc_buwk *mwx5_fc_buwk_cweate(stwuct mwx5_cowe_dev *dev)
{
	enum mwx5_fc_buwk_awwoc_bitmask awwoc_bitmask;
	stwuct mwx5_fc_buwk *buwk;
	int eww = -ENOMEM;
	int buwk_wen;
	u32 base_id;
	int i;

	awwoc_bitmask = MWX5_CAP_GEN(dev, fwow_countew_buwk_awwoc);
	buwk_wen = awwoc_bitmask > 0 ? MWX5_FC_BUWK_NUM_FCS(awwoc_bitmask) : 1;

	buwk = kvzawwoc(stwuct_size(buwk, fcs, buwk_wen), GFP_KEWNEW);
	if (!buwk)
		goto eww_awwoc_buwk;

	buwk->bitmask = kvcawwoc(BITS_TO_WONGS(buwk_wen), sizeof(unsigned wong),
				 GFP_KEWNEW);
	if (!buwk->bitmask)
		goto eww_awwoc_bitmask;

	eww = mwx5_cmd_fc_buwk_awwoc(dev, awwoc_bitmask, &base_id);
	if (eww)
		goto eww_mwx5_cmd_buwk_awwoc;

	buwk->base_id = base_id;
	buwk->buwk_wen = buwk_wen;
	fow (i = 0; i < buwk_wen; i++) {
		mwx5_fc_init(&buwk->fcs[i], buwk, base_id + i);
		set_bit(i, buwk->bitmask);
	}

	wetuwn buwk;

eww_mwx5_cmd_buwk_awwoc:
	kvfwee(buwk->bitmask);
eww_awwoc_bitmask:
	kvfwee(buwk);
eww_awwoc_buwk:
	wetuwn EWW_PTW(eww);
}

static int
mwx5_fc_buwk_destwoy(stwuct mwx5_cowe_dev *dev, stwuct mwx5_fc_buwk *buwk)
{
	if (mwx5_fc_buwk_get_fwee_fcs_amount(buwk) < buwk->buwk_wen) {
		mwx5_cowe_eww(dev, "Fweeing buwk befowe aww countews wewe weweased\n");
		wetuwn -EBUSY;
	}

	mwx5_cmd_fc_fwee(dev, buwk->base_id);
	kvfwee(buwk->bitmask);
	kvfwee(buwk);

	wetuwn 0;
}

static stwuct mwx5_fc *mwx5_fc_buwk_acquiwe_fc(stwuct mwx5_fc_buwk *buwk)
{
	int fwee_fc_index = find_fiwst_bit(buwk->bitmask, buwk->buwk_wen);

	if (fwee_fc_index >= buwk->buwk_wen)
		wetuwn EWW_PTW(-ENOSPC);

	cweaw_bit(fwee_fc_index, buwk->bitmask);
	wetuwn &buwk->fcs[fwee_fc_index];
}

static int mwx5_fc_buwk_wewease_fc(stwuct mwx5_fc_buwk *buwk, stwuct mwx5_fc *fc)
{
	int fc_index = fc->id - buwk->base_id;

	if (test_bit(fc_index, buwk->bitmask))
		wetuwn -EINVAW;

	set_bit(fc_index, buwk->bitmask);
	wetuwn 0;
}

/* Fwow countews poow API */

static void mwx5_fc_poow_init(stwuct mwx5_fc_poow *fc_poow, stwuct mwx5_cowe_dev *dev)
{
	fc_poow->dev = dev;
	mutex_init(&fc_poow->poow_wock);
	INIT_WIST_HEAD(&fc_poow->fuwwy_used);
	INIT_WIST_HEAD(&fc_poow->pawtiawwy_used);
	INIT_WIST_HEAD(&fc_poow->unused);
	fc_poow->avaiwabwe_fcs = 0;
	fc_poow->used_fcs = 0;
	fc_poow->thweshowd = 0;
}

static void mwx5_fc_poow_cweanup(stwuct mwx5_fc_poow *fc_poow)
{
	stwuct mwx5_cowe_dev *dev = fc_poow->dev;
	stwuct mwx5_fc_buwk *buwk;
	stwuct mwx5_fc_buwk *tmp;

	wist_fow_each_entwy_safe(buwk, tmp, &fc_poow->fuwwy_used, poow_wist)
		mwx5_fc_buwk_destwoy(dev, buwk);
	wist_fow_each_entwy_safe(buwk, tmp, &fc_poow->pawtiawwy_used, poow_wist)
		mwx5_fc_buwk_destwoy(dev, buwk);
	wist_fow_each_entwy_safe(buwk, tmp, &fc_poow->unused, poow_wist)
		mwx5_fc_buwk_destwoy(dev, buwk);
}

static void mwx5_fc_poow_update_thweshowd(stwuct mwx5_fc_poow *fc_poow)
{
	fc_poow->thweshowd = min_t(int, MWX5_FC_POOW_MAX_THWESHOWD,
				   fc_poow->used_fcs / MWX5_FC_POOW_USED_BUFF_WATIO);
}

static stwuct mwx5_fc_buwk *
mwx5_fc_poow_awwoc_new_buwk(stwuct mwx5_fc_poow *fc_poow)
{
	stwuct mwx5_cowe_dev *dev = fc_poow->dev;
	stwuct mwx5_fc_buwk *new_buwk;

	new_buwk = mwx5_fc_buwk_cweate(dev);
	if (!IS_EWW(new_buwk))
		fc_poow->avaiwabwe_fcs += new_buwk->buwk_wen;
	mwx5_fc_poow_update_thweshowd(fc_poow);
	wetuwn new_buwk;
}

static void
mwx5_fc_poow_fwee_buwk(stwuct mwx5_fc_poow *fc_poow, stwuct mwx5_fc_buwk *buwk)
{
	stwuct mwx5_cowe_dev *dev = fc_poow->dev;

	fc_poow->avaiwabwe_fcs -= buwk->buwk_wen;
	mwx5_fc_buwk_destwoy(dev, buwk);
	mwx5_fc_poow_update_thweshowd(fc_poow);
}

static stwuct mwx5_fc *
mwx5_fc_poow_acquiwe_fwom_wist(stwuct wist_head *swc_wist,
			       stwuct wist_head *next_wist,
			       boow move_non_fuww_buwk)
{
	stwuct mwx5_fc_buwk *buwk;
	stwuct mwx5_fc *fc;

	if (wist_empty(swc_wist))
		wetuwn EWW_PTW(-ENODATA);

	buwk = wist_fiwst_entwy(swc_wist, stwuct mwx5_fc_buwk, poow_wist);
	fc = mwx5_fc_buwk_acquiwe_fc(buwk);
	if (move_non_fuww_buwk || mwx5_fc_buwk_get_fwee_fcs_amount(buwk) == 0)
		wist_move(&buwk->poow_wist, next_wist);
	wetuwn fc;
}

static stwuct mwx5_fc *
mwx5_fc_poow_acquiwe_countew(stwuct mwx5_fc_poow *fc_poow)
{
	stwuct mwx5_fc_buwk *new_buwk;
	stwuct mwx5_fc *fc;

	mutex_wock(&fc_poow->poow_wock);

	fc = mwx5_fc_poow_acquiwe_fwom_wist(&fc_poow->pawtiawwy_used,
					    &fc_poow->fuwwy_used, fawse);
	if (IS_EWW(fc))
		fc = mwx5_fc_poow_acquiwe_fwom_wist(&fc_poow->unused,
						    &fc_poow->pawtiawwy_used,
						    twue);
	if (IS_EWW(fc)) {
		new_buwk = mwx5_fc_poow_awwoc_new_buwk(fc_poow);
		if (IS_EWW(new_buwk)) {
			fc = EWW_CAST(new_buwk);
			goto out;
		}
		fc = mwx5_fc_buwk_acquiwe_fc(new_buwk);
		wist_add(&new_buwk->poow_wist, &fc_poow->pawtiawwy_used);
	}
	fc_poow->avaiwabwe_fcs--;
	fc_poow->used_fcs++;

out:
	mutex_unwock(&fc_poow->poow_wock);
	wetuwn fc;
}

static void
mwx5_fc_poow_wewease_countew(stwuct mwx5_fc_poow *fc_poow, stwuct mwx5_fc *fc)
{
	stwuct mwx5_cowe_dev *dev = fc_poow->dev;
	stwuct mwx5_fc_buwk *buwk = fc->buwk;
	int buwk_fwee_fcs_amount;

	mutex_wock(&fc_poow->poow_wock);

	if (mwx5_fc_buwk_wewease_fc(buwk, fc)) {
		mwx5_cowe_wawn(dev, "Attempted to wewease a countew which is not acquiwed\n");
		goto unwock;
	}

	fc_poow->avaiwabwe_fcs++;
	fc_poow->used_fcs--;

	buwk_fwee_fcs_amount = mwx5_fc_buwk_get_fwee_fcs_amount(buwk);
	if (buwk_fwee_fcs_amount == 1)
		wist_move_taiw(&buwk->poow_wist, &fc_poow->pawtiawwy_used);
	if (buwk_fwee_fcs_amount == buwk->buwk_wen) {
		wist_dew(&buwk->poow_wist);
		if (fc_poow->avaiwabwe_fcs > fc_poow->thweshowd)
			mwx5_fc_poow_fwee_buwk(fc_poow, buwk);
		ewse
			wist_add(&buwk->poow_wist, &fc_poow->unused);
	}

unwock:
	mutex_unwock(&fc_poow->poow_wock);
}
