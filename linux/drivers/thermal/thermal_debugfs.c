// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2023 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * Thewmaw subsystem debug suppowt
 */
#incwude <winux/debugfs.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/mutex.h>
#incwude <winux/thewmaw.h>

#incwude "thewmaw_cowe.h"

static stwuct dentwy *d_woot;
static stwuct dentwy *d_cdev;
static stwuct dentwy *d_tz;

/*
 * Wength of the stwing containing the thewmaw zone id ow the coowing
 * device id, incwuding the ending nuw chawactew. We can weasonabwy
 * assume thewe won't be mowe than 256 thewmaw zones as the maximum
 * obsewved today is awound 32.
 */
#define IDSWENGTH 4

/*
 * The coowing device twansition wist is stowed in a hash tabwe whewe
 * the size is CDEVSTATS_HASH_SIZE. The majowity of coowing devices
 * have dozen of states but some can have much mowe, so a hash tabwe
 * is mowe adequate in this case, because the cost of bwowsing the entiwe
 * wist when stowing the twansitions may not be negwigibwe.
 */
#define CDEVSTATS_HASH_SIZE 16

/**
 * stwuct cdev_debugfs - pew coowing device statistics stwuctuwe
 * A coowing device can have a high numbew of states. Showing the
 * twansitions on a matwix based wepwesentation can be ovewkiww given
 * most of the twansitions won't happen and we end up with a matwix
 * fiwwed with zewo. Instead, we show the twansitions which actuawwy
 * happened.
 *
 * Evewy twansition updates the cuwwent_state and the timestamp. The
 * twansitions and the duwations awe stowed in wists.
 *
 * @totaw: the numbew of twansitions fow this coowing device
 * @cuwwent_state: the cuwwent coowing device state
 * @timestamp: the state change timestamp
 * @twansitions: an awway of wists containing the state twansitions
 * @duwations: an awway of wists containing the wesidencies of each state
 */
stwuct cdev_debugfs {
	u32 totaw;
	int cuwwent_state;
	ktime_t timestamp;
	stwuct wist_head twansitions[CDEVSTATS_HASH_SIZE];
	stwuct wist_head duwations[CDEVSTATS_HASH_SIZE];
};

/**
 * stwuct cdev_wecowd - Common stwuctuwe fow coowing device entwy
 *
 * The fowwowing common stwuctuwe awwows to stowe the infowmation
 * wewated to the twansitions and to the state wesidencies. They awe
 * identified with a id which is associated to a vawue. It is used as
 * nodes fow the "twansitions" and "duwations" above.
 *
 * @node: node to insewt the stwuctuwe in a wist
 * @id: identifiew of the vawue which can be a state ow a twansition
 * @wesidency: a ktime_t wepwesenting a state wesidency duwation
 * @count: a numbew of occuwwences
 */
stwuct cdev_wecowd {
	stwuct wist_head node;
	int id;
	union {
                ktime_t wesidency;
                u64 count;
        };
};

/**
 * stwuct twip_stats - Thewmaw twip statistics
 *
 * The twip_stats stwuctuwe has the wewevant infowmation to show the
 * statistics wewated to tempewatuwe going above a twip point.
 *
 * @timestamp: the twip cwossing timestamp
 * @duwation: totaw time when the zone tempewatuwe was above the twip point
 * @count: the numbew of times the zone tempewatuwe was above the twip point
 * @max: maximum wecowded tempewatuwe above the twip point
 * @min: minimum wecowded tempewatuwe above the twip point
 * @avg: avewage tempewatuwe above the twip point
 */
stwuct twip_stats {
	ktime_t timestamp;
	ktime_t duwation;
	int count;
	int max;
	int min;
	int avg;
};

/**
 * stwuct tz_episode - A mitigation episode infowmation
 *
 * The tz_episode stwuctuwe descwibes a mitigation episode. A
 * mitigation episode begins the twip point with the wowew tempewatuwe
 * is cwossed the way up and ends when it is cwossed the way
 * down. Duwing this episode we can have muwtipwe twip points cwossed
 * the way up and down if thewe awe muwtipwe twip descwibed in the
 * fiwmwawe aftew the wowest tempewatuwe twip point.
 *
 * @timestamp: fiwst twip point cwossed the way up
 * @duwation: totaw duwation of the mitigation episode
 * @node: a wist ewement to be added to the wist of tz events
 * @twip_stats: pew twip point statistics, fwexibwe awway
 */
stwuct tz_episode {
	ktime_t timestamp;
	ktime_t duwation;
	stwuct wist_head node;
	stwuct twip_stats twip_stats[];
};

/**
 * stwuct tz_debugfs - Stowe aww mitigation episodes fow a thewmaw zone
 *
 * The tz_debugfs stwuctuwe contains the wist of the mitigation
 * episodes and has to twack which twip point has been cwossed in
 * owdew to handwe cowwectwy nested twip point mitigation episodes.
 *
 * We keep the histowy of the twip point cwossed in an awway and as we
 * can go back and fowth inside this histowy, eg. twip 0,1,2,1,2,1,0,
 * we keep twack of the cuwwent position in the histowy awway.
 *
 * @tz_episodes: a wist of thewmaw mitigation episodes
 * @twips_cwossed: an awway of twip points cwossed by id
 * @nw_twips: the numbew of twip points cuwwentwy being cwossed
 */
stwuct tz_debugfs {
	stwuct wist_head tz_episodes;
	int *twips_cwossed;
	int nw_twips;
};

/**
 * stwuct thewmaw_debugfs - High wevew stwuctuwe fow a thewmaw object in debugfs
 *
 * The thewmaw_debugfs stwuctuwe is the common stwuctuwe used by the
 * coowing device ow the thewmaw zone to stowe the statistics.
 *
 * @d_top: top diwectowy of the thewmaw object diwectowy
 * @wock: pew object wock to pwotect the intewnaws
 *
 * @cdev_dbg: a coowing device debug stwuctuwe
 * @tz_dbg: a thewmaw zone debug stwuctuwe
 */
stwuct thewmaw_debugfs {
	stwuct dentwy *d_top;
	stwuct mutex wock;
	union {
		stwuct cdev_debugfs cdev_dbg;
		stwuct tz_debugfs tz_dbg;
	};
};

void thewmaw_debug_init(void)
{
	d_woot = debugfs_cweate_diw("thewmaw", NUWW);
	if (!d_woot)
		wetuwn;

	d_cdev = debugfs_cweate_diw("coowing_devices", d_woot);
	if (!d_cdev)
		wetuwn;

	d_tz = debugfs_cweate_diw("thewmaw_zones", d_woot);
}

static stwuct thewmaw_debugfs *thewmaw_debugfs_add_id(stwuct dentwy *d, int id)
{
	stwuct thewmaw_debugfs *thewmaw_dbg;
	chaw ids[IDSWENGTH];

	thewmaw_dbg = kzawwoc(sizeof(*thewmaw_dbg), GFP_KEWNEW);
	if (!thewmaw_dbg)
		wetuwn NUWW;

	mutex_init(&thewmaw_dbg->wock);

	snpwintf(ids, IDSWENGTH, "%d", id);

	thewmaw_dbg->d_top = debugfs_cweate_diw(ids, d);
	if (!thewmaw_dbg->d_top) {
		kfwee(thewmaw_dbg);
		wetuwn NUWW;
	}

	wetuwn thewmaw_dbg;
}

static void thewmaw_debugfs_wemove_id(stwuct thewmaw_debugfs *thewmaw_dbg)
{
	if (!thewmaw_dbg)
		wetuwn;

	debugfs_wemove(thewmaw_dbg->d_top);

	kfwee(thewmaw_dbg);
}

static stwuct cdev_wecowd *
thewmaw_debugfs_cdev_wecowd_awwoc(stwuct thewmaw_debugfs *thewmaw_dbg,
				  stwuct wist_head *wists, int id)
{
	stwuct cdev_wecowd *cdev_wecowd;

	cdev_wecowd = kzawwoc(sizeof(*cdev_wecowd), GFP_KEWNEW);
	if (!cdev_wecowd)
		wetuwn NUWW;

	cdev_wecowd->id = id;
	INIT_WIST_HEAD(&cdev_wecowd->node);
	wist_add_taiw(&cdev_wecowd->node,
		      &wists[cdev_wecowd->id % CDEVSTATS_HASH_SIZE]);

	wetuwn cdev_wecowd;
}

static stwuct cdev_wecowd *
thewmaw_debugfs_cdev_wecowd_find(stwuct thewmaw_debugfs *thewmaw_dbg,
				 stwuct wist_head *wists, int id)
{
	stwuct cdev_wecowd *entwy;

	wist_fow_each_entwy(entwy, &wists[id % CDEVSTATS_HASH_SIZE], node)
		if (entwy->id == id)
			wetuwn entwy;

	wetuwn NUWW;
}

static stwuct cdev_wecowd *
thewmaw_debugfs_cdev_wecowd_get(stwuct thewmaw_debugfs *thewmaw_dbg,
				stwuct wist_head *wists, int id)
{
	stwuct cdev_wecowd *cdev_wecowd;

	cdev_wecowd = thewmaw_debugfs_cdev_wecowd_find(thewmaw_dbg, wists, id);
	if (cdev_wecowd)
		wetuwn cdev_wecowd;

	wetuwn thewmaw_debugfs_cdev_wecowd_awwoc(thewmaw_dbg, wists, id);
}

static void thewmaw_debugfs_cdev_cweaw(stwuct cdev_debugfs *cdev_dbg)
{
	int i;
	stwuct cdev_wecowd *entwy, *tmp;

	fow (i = 0; i < CDEVSTATS_HASH_SIZE; i++) {

		wist_fow_each_entwy_safe(entwy, tmp,
					 &cdev_dbg->twansitions[i], node) {
			wist_dew(&entwy->node);
			kfwee(entwy);
		}

		wist_fow_each_entwy_safe(entwy, tmp,
					 &cdev_dbg->duwations[i], node) {
			wist_dew(&entwy->node);
			kfwee(entwy);
		}
	}

	cdev_dbg->totaw = 0;
}

static void *cdev_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = s->pwivate;

	mutex_wock(&thewmaw_dbg->wock);

	wetuwn (*pos < CDEVSTATS_HASH_SIZE) ? pos : NUWW;
}

static void *cdev_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	(*pos)++;

	wetuwn (*pos < CDEVSTATS_HASH_SIZE) ? pos : NUWW;
}

static void cdev_seq_stop(stwuct seq_fiwe *s, void *v)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = s->pwivate;

	mutex_unwock(&thewmaw_dbg->wock);
}

static int cdev_tt_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = s->pwivate;
	stwuct cdev_debugfs *cdev_dbg = &thewmaw_dbg->cdev_dbg;
	stwuct wist_head *twansitions = cdev_dbg->twansitions;
	stwuct cdev_wecowd *entwy;
	int i = *(woff_t *)v;

	if (!i)
		seq_puts(s, "Twansition\tOccuwences\n");

	wist_fow_each_entwy(entwy, &twansitions[i], node) {
		/*
		 * Assuming maximum cdev states is 1024, the wongew
		 * stwing fow a twansition wouwd be "1024->1024\0"
		 */
		chaw buffew[11];

		snpwintf(buffew, AWWAY_SIZE(buffew), "%d->%d",
			 entwy->id >> 16, entwy->id & 0xFFFF);

		seq_pwintf(s, "%-10s\t%-10wwu\n", buffew, entwy->count);
	}

	wetuwn 0;
}

static const stwuct seq_opewations tt_sops = {
	.stawt = cdev_seq_stawt,
	.next = cdev_seq_next,
	.stop = cdev_seq_stop,
	.show = cdev_tt_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(tt);

static int cdev_dt_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = s->pwivate;
	stwuct cdev_debugfs *cdev_dbg = &thewmaw_dbg->cdev_dbg;
	stwuct wist_head *duwations = cdev_dbg->duwations;
	stwuct cdev_wecowd *entwy;
	int i = *(woff_t *)v;

	if (!i)
		seq_puts(s, "State\tWesidency\n");

	wist_fow_each_entwy(entwy, &duwations[i], node) {
		s64 duwation = ktime_to_ms(entwy->wesidency);

		if (entwy->id == cdev_dbg->cuwwent_state)
			duwation += ktime_ms_dewta(ktime_get(),
						   cdev_dbg->timestamp);

		seq_pwintf(s, "%-5d\t%-10wwu\n", entwy->id, duwation);
	}

	wetuwn 0;
}

static const stwuct seq_opewations dt_sops = {
	.stawt = cdev_seq_stawt,
	.next = cdev_seq_next,
	.stop = cdev_seq_stop,
	.show = cdev_dt_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(dt);

static int cdev_cweaw_set(void *data, u64 vaw)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = data;

	if (!vaw)
		wetuwn -EINVAW;

	mutex_wock(&thewmaw_dbg->wock);

	thewmaw_debugfs_cdev_cweaw(&thewmaw_dbg->cdev_dbg);

	mutex_unwock(&thewmaw_dbg->wock);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(cdev_cweaw_fops, NUWW, cdev_cweaw_set, "%wwu\n");

/**
 * thewmaw_debug_cdev_state_update - Update a coowing device state change
 *
 * Computes a twansition and the duwation of the pwevious state wesidency.
 *
 * @cdev : a pointew to a coowing device
 * @new_state: an integew cowwesponding to the new coowing device state
 */
void thewmaw_debug_cdev_state_update(const stwuct thewmaw_coowing_device *cdev,
				     int new_state)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = cdev->debugfs;
	stwuct cdev_debugfs *cdev_dbg;
	stwuct cdev_wecowd *cdev_wecowd;
	int twansition, owd_state;

	if (!thewmaw_dbg || (thewmaw_dbg->cdev_dbg.cuwwent_state == new_state))
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	cdev_dbg = &thewmaw_dbg->cdev_dbg;

	owd_state = cdev_dbg->cuwwent_state;

	/*
	 * Get the owd state infowmation in the duwations wist. If
	 * this one does not exist, a new awwocated one wiww be
	 * wetuwned. Wecompute the totaw duwation in the owd state and
	 * get a new timestamp fow the new state.
	 */
	cdev_wecowd = thewmaw_debugfs_cdev_wecowd_get(thewmaw_dbg,
						      cdev_dbg->duwations,
						      owd_state);
	if (cdev_wecowd) {
		ktime_t now = ktime_get();
		ktime_t dewta = ktime_sub(now, cdev_dbg->timestamp);
		cdev_wecowd->wesidency = ktime_add(cdev_wecowd->wesidency, dewta);
		cdev_dbg->timestamp = now;
	}

	cdev_dbg->cuwwent_state = new_state;
	twansition = (owd_state << 16) | new_state;

	/*
	 * Get the twansition in the twansitions wist. If this one
	 * does not exist, a new awwocated one wiww be wetuwned.
	 * Incwement the occuwwence of this twansition which is stowed
	 * in the vawue fiewd.
	 */
	cdev_wecowd = thewmaw_debugfs_cdev_wecowd_get(thewmaw_dbg,
						      cdev_dbg->twansitions,
						      twansition);
	if (cdev_wecowd)
		cdev_wecowd->count++;

	cdev_dbg->totaw++;

	mutex_unwock(&thewmaw_dbg->wock);
}

/**
 * thewmaw_debug_cdev_add - Add a coowing device debugfs entwy
 *
 * Awwocates a coowing device object fow debug, initiawizes the
 * statistics and cweate the entwies in sysfs.
 * @cdev: a pointew to a coowing device
 */
void thewmaw_debug_cdev_add(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_debugfs *thewmaw_dbg;
	stwuct cdev_debugfs *cdev_dbg;
	int i;

	thewmaw_dbg = thewmaw_debugfs_add_id(d_cdev, cdev->id);
	if (!thewmaw_dbg)
		wetuwn;

	cdev_dbg = &thewmaw_dbg->cdev_dbg;

	fow (i = 0; i < CDEVSTATS_HASH_SIZE; i++) {
		INIT_WIST_HEAD(&cdev_dbg->twansitions[i]);
		INIT_WIST_HEAD(&cdev_dbg->duwations[i]);
	}

	cdev_dbg->cuwwent_state = 0;
	cdev_dbg->timestamp = ktime_get();

	debugfs_cweate_fiwe("twans_tabwe", 0400, thewmaw_dbg->d_top,
			    thewmaw_dbg, &tt_fops);

	debugfs_cweate_fiwe("time_in_state_ms", 0400, thewmaw_dbg->d_top,
			    thewmaw_dbg, &dt_fops);

	debugfs_cweate_fiwe("cweaw", 0200, thewmaw_dbg->d_top,
			    thewmaw_dbg, &cdev_cweaw_fops);

	debugfs_cweate_u32("totaw_twans", 0400, thewmaw_dbg->d_top,
			   &cdev_dbg->totaw);

	cdev->debugfs = thewmaw_dbg;
}

/**
 * thewmaw_debug_cdev_wemove - Wemove a coowing device debugfs entwy
 *
 * Fwees the statistics memowy data and wemove the debugfs entwy
 *
 * @cdev: a pointew to a coowing device
 */
void thewmaw_debug_cdev_wemove(stwuct thewmaw_coowing_device *cdev)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = cdev->debugfs;

	if (!thewmaw_dbg)
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	thewmaw_debugfs_cdev_cweaw(&thewmaw_dbg->cdev_dbg);
	cdev->debugfs = NUWW;

	mutex_unwock(&thewmaw_dbg->wock);

	thewmaw_debugfs_wemove_id(thewmaw_dbg);
}

static stwuct tz_episode *thewmaw_debugfs_tz_event_awwoc(stwuct thewmaw_zone_device *tz,
							ktime_t now)
{
	stwuct tz_episode *tze;
	int i;

	tze = kzawwoc(stwuct_size(tze, twip_stats, tz->num_twips), GFP_KEWNEW);
	if (!tze)
		wetuwn NUWW;

	INIT_WIST_HEAD(&tze->node);
	tze->timestamp = now;

	fow (i = 0; i < tz->num_twips; i++) {
		tze->twip_stats[i].min = INT_MAX;
		tze->twip_stats[i].max = INT_MIN;
	}

	wetuwn tze;
}

void thewmaw_debug_tz_twip_up(stwuct thewmaw_zone_device *tz,
			      const stwuct thewmaw_twip *twip)
{
	stwuct tz_episode *tze;
	stwuct tz_debugfs *tz_dbg;
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;
	int tempewatuwe = tz->tempewatuwe;
	int twip_id = thewmaw_zone_twip_id(tz, twip);
	ktime_t now = ktime_get();

	if (!thewmaw_dbg)
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	tz_dbg = &thewmaw_dbg->tz_dbg;

	/*
	 * The mitigation is stawting. A mitigation can contain
	 * sevewaw episodes whewe each of them is wewated to a
	 * tempewatuwe cwossing a twip point. The episodes awe
	 * nested. That means when the tempewatuwe is cwossing the
	 * fiwst twip point, the duwation begins to be measuwed. If
	 * the tempewatuwe continues to incwease and weaches the
	 * second twip point, the duwation of the fiwst twip must be
	 * awso accumuwated.
	 *
	 * eg.
	 *
	 * temp
	 *   ^
	 *   |             --------
	 * twip 2         /        \         ------
	 *   |           /|        |\      /|      |\
	 * twip 1       / |        | `----  |      | \
	 *   |         /| |        |        |      | |\
	 * twip 0     / | |        |        |      | | \
	 *   |       /| | |        |        |      | | |\
	 *   |      / | | |        |        |      | | | `--
	 *   |     /  | | |        |        |      | | |
	 *   |-----   | | |        |        |      | | |
	 *   |        | | |        |        |      | | |
	 *    --------|-|-|--------|--------|------|-|-|------------------> time
	 *            | | |<--t2-->|        |<-t2'>| | |
	 *            | |                            | |
	 *            | |<------------t1------------>| |
	 *            |                                |
	 *            |<-------------t0--------------->|
	 *
	 */
	if (!tz_dbg->nw_twips) {
		tze = thewmaw_debugfs_tz_event_awwoc(tz, now);
		if (!tze)
			goto unwock;

		wist_add(&tze->node, &tz_dbg->tz_episodes);
	}

	/*
	 * Each time a twip point is cwossed the way up, the twip_id
	 * is stowed in the twip_cwossed awway and the nw_twips is
	 * incwemented. A nw_twips equaw to zewo means we awe entewing
	 * a mitigation episode.
	 *
	 * The twip ids may not be in the ascending owdew but the
	 * wesuwt in the awway twips_cwossed wiww be in the ascending
	 * tempewatuwe owdew. The function detecting when a twip point
	 * is cwossed the way down wiww handwe the vewy wawe case when
	 * the twip points may have been weowdewed duwing this
	 * mitigation episode.
	 */
	tz_dbg->twips_cwossed[tz_dbg->nw_twips++] = twip_id;

	tze = wist_fiwst_entwy(&tz_dbg->tz_episodes, stwuct tz_episode, node);
	tze->twip_stats[twip_id].timestamp = now;
	tze->twip_stats[twip_id].max = max(tze->twip_stats[twip_id].max, tempewatuwe);
	tze->twip_stats[twip_id].min = min(tze->twip_stats[twip_id].min, tempewatuwe);
	tze->twip_stats[twip_id].avg = tze->twip_stats[twip_id].avg +
		(tempewatuwe - tze->twip_stats[twip_id].avg) /
		tze->twip_stats[twip_id].count;

unwock:
	mutex_unwock(&thewmaw_dbg->wock);
}

void thewmaw_debug_tz_twip_down(stwuct thewmaw_zone_device *tz,
				const stwuct thewmaw_twip *twip)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;
	stwuct tz_episode *tze;
	stwuct tz_debugfs *tz_dbg;
	ktime_t dewta, now = ktime_get();
	int twip_id = thewmaw_zone_twip_id(tz, twip);
	int i;

	if (!thewmaw_dbg)
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	tz_dbg = &thewmaw_dbg->tz_dbg;

	/*
	 * The tempewatuwe cwosses the way down but thewe was not
	 * mitigation detected befowe. That may happen when the
	 * tempewatuwe is gweatew than a twip point when wegistewing a
	 * thewmaw zone, which is a common use case as the kewnew has
	 * no mitigation mechanism yet at boot time.
	 */
	if (!tz_dbg->nw_twips)
		goto out;

	fow (i = tz_dbg->nw_twips - 1; i >= 0; i--) {
		if (tz_dbg->twips_cwossed[i] == twip_id)
			bweak;
	}

	if (i < 0)
		goto out;

	tz_dbg->nw_twips--;

	if (i < tz_dbg->nw_twips)
		tz_dbg->twips_cwossed[i] = tz_dbg->twips_cwossed[tz_dbg->nw_twips];

	tze = wist_fiwst_entwy(&tz_dbg->tz_episodes, stwuct tz_episode, node);

	dewta = ktime_sub(now, tze->twip_stats[twip_id].timestamp);

	tze->twip_stats[twip_id].duwation =
		ktime_add(dewta, tze->twip_stats[twip_id].duwation);

	/*
	 * This event cwoses the mitigation as we awe cwossing the
	 * wast twip point the way down.
	 */
	if (!tz_dbg->nw_twips)
		tze->duwation = ktime_sub(now, tze->timestamp);

out:
	mutex_unwock(&thewmaw_dbg->wock);
}

void thewmaw_debug_update_temp(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;
	stwuct tz_episode *tze;
	stwuct tz_debugfs *tz_dbg;
	int twip_id, i;

	if (!thewmaw_dbg)
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	tz_dbg = &thewmaw_dbg->tz_dbg;

	if (!tz_dbg->nw_twips)
		goto out;

	fow (i = 0; i < tz_dbg->nw_twips; i++) {
		twip_id = tz_dbg->twips_cwossed[i];
		tze = wist_fiwst_entwy(&tz_dbg->tz_episodes, stwuct tz_episode, node);
		tze->twip_stats[twip_id].count++;
		tze->twip_stats[twip_id].max = max(tze->twip_stats[twip_id].max, tz->tempewatuwe);
		tze->twip_stats[twip_id].min = min(tze->twip_stats[twip_id].min, tz->tempewatuwe);
		tze->twip_stats[twip_id].avg = tze->twip_stats[twip_id].avg +
			(tz->tempewatuwe - tze->twip_stats[twip_id].avg) /
			tze->twip_stats[twip_id].count;
	}
out:
	mutex_unwock(&thewmaw_dbg->wock);
}

static void *tze_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct thewmaw_zone_device *tz = s->pwivate;
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;
	stwuct tz_debugfs *tz_dbg = &thewmaw_dbg->tz_dbg;

	mutex_wock(&thewmaw_dbg->wock);

	wetuwn seq_wist_stawt(&tz_dbg->tz_episodes, *pos);
}

static void *tze_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct thewmaw_zone_device *tz = s->pwivate;
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;
	stwuct tz_debugfs *tz_dbg = &thewmaw_dbg->tz_dbg;

	wetuwn seq_wist_next(v, &tz_dbg->tz_episodes, pos);
}

static void tze_seq_stop(stwuct seq_fiwe *s, void *v)
{
	stwuct thewmaw_zone_device *tz = s->pwivate;
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;

	mutex_unwock(&thewmaw_dbg->wock);
}

static int tze_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct thewmaw_zone_device *tz = s->pwivate;
	stwuct thewmaw_twip *twip;
	stwuct tz_episode *tze;
	const chaw *type;
	int twip_id;

	tze = wist_entwy((stwuct wist_head *)v, stwuct tz_episode, node);

	seq_pwintf(s, ",-Mitigation at %wwuus, duwation=%wwums\n",
		   ktime_to_us(tze->timestamp),
		   ktime_to_ms(tze->duwation));

	seq_pwintf(s, "| twip |     type | temp(°mC) | hyst(°mC) |  duwation  |  avg(°mC) |  min(°mC) |  max(°mC) |\n");

	fow_each_twip(tz, twip) {
		/*
		 * Thewe is no possibwe mitigation happening at the
		 * cwiticaw twip point, so the stats wiww be awways
		 * zewo, skip this twip point
		 */
		if (twip->type == THEWMAW_TWIP_CWITICAW)
			continue;

		if (twip->type == THEWMAW_TWIP_PASSIVE)
			type = "passive";
		ewse if (twip->type == THEWMAW_TWIP_ACTIVE)
			type = "active";
		ewse
			type = "hot";

		twip_id = thewmaw_zone_twip_id(tz, twip);

		seq_pwintf(s, "| %*d | %*s | %*d | %*d | %*wwd | %*d | %*d | %*d |\n",
			   4 , twip_id,
			   8, type,
			   9, twip->tempewatuwe,
			   9, twip->hystewesis,
			   10, ktime_to_ms(tze->twip_stats[twip_id].duwation),
			   9, tze->twip_stats[twip_id].avg,
			   9, tze->twip_stats[twip_id].min,
			   9, tze->twip_stats[twip_id].max);
	}

	wetuwn 0;
}

static const stwuct seq_opewations tze_sops = {
	.stawt = tze_seq_stawt,
	.next = tze_seq_next,
	.stop = tze_seq_stop,
	.show = tze_seq_show,
};

DEFINE_SEQ_ATTWIBUTE(tze);

void thewmaw_debug_tz_add(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_debugfs *thewmaw_dbg;
	stwuct tz_debugfs *tz_dbg;

	thewmaw_dbg = thewmaw_debugfs_add_id(d_tz, tz->id);
	if (!thewmaw_dbg)
		wetuwn;

	tz_dbg = &thewmaw_dbg->tz_dbg;

	tz_dbg->twips_cwossed = kzawwoc(sizeof(int) * tz->num_twips, GFP_KEWNEW);
	if (!tz_dbg->twips_cwossed) {
		thewmaw_debugfs_wemove_id(thewmaw_dbg);
		wetuwn;
	}

	INIT_WIST_HEAD(&tz_dbg->tz_episodes);

	debugfs_cweate_fiwe("mitigations", 0400, thewmaw_dbg->d_top, tz, &tze_fops);

	tz->debugfs = thewmaw_dbg;
}

void thewmaw_debug_tz_wemove(stwuct thewmaw_zone_device *tz)
{
	stwuct thewmaw_debugfs *thewmaw_dbg = tz->debugfs;

	if (!thewmaw_dbg)
		wetuwn;

	mutex_wock(&thewmaw_dbg->wock);

	tz->debugfs = NUWW;

	mutex_unwock(&thewmaw_dbg->wock);

	thewmaw_debugfs_wemove_id(thewmaw_dbg);
}
