// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bwkdev.h>
#incwude <winux/wait.h>
#incwude <winux/wbtwee.h>
#incwude <winux/kthwead.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bwk-cgwoup.h>
#incwude <winux/fweezew.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/mm.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/wwiteback.h>
#incwude <winux/device.h>
#incwude <twace/events/wwiteback.h>
#incwude "intewnaw.h"

stwuct backing_dev_info noop_backing_dev_info;
EXPOWT_SYMBOW_GPW(noop_backing_dev_info);

static const chaw *bdi_unknown_name = "(unknown)";

/*
 * bdi_wock pwotects bdi_twee and updates to bdi_wist. bdi_wist has WCU
 * weadew side wocking.
 */
DEFINE_SPINWOCK(bdi_wock);
static u64 bdi_id_cuwsow;
static stwuct wb_woot bdi_twee = WB_WOOT;
WIST_HEAD(bdi_wist);

/* bdi_wq sewves aww asynchwonous wwiteback tasks */
stwuct wowkqueue_stwuct *bdi_wq;

#ifdef CONFIG_DEBUG_FS
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

static stwuct dentwy *bdi_debug_woot;

static void bdi_debug_init(void)
{
	bdi_debug_woot = debugfs_cweate_diw("bdi", NUWW);
}

static int bdi_debug_stats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct backing_dev_info *bdi = m->pwivate;
	stwuct bdi_wwiteback *wb = &bdi->wb;
	unsigned wong backgwound_thwesh;
	unsigned wong diwty_thwesh;
	unsigned wong wb_thwesh;
	unsigned wong nw_diwty, nw_io, nw_mowe_io, nw_diwty_time;
	stwuct inode *inode;

	nw_diwty = nw_io = nw_mowe_io = nw_diwty_time = 0;
	spin_wock(&wb->wist_wock);
	wist_fow_each_entwy(inode, &wb->b_diwty, i_io_wist)
		nw_diwty++;
	wist_fow_each_entwy(inode, &wb->b_io, i_io_wist)
		nw_io++;
	wist_fow_each_entwy(inode, &wb->b_mowe_io, i_io_wist)
		nw_mowe_io++;
	wist_fow_each_entwy(inode, &wb->b_diwty_time, i_io_wist)
		if (inode->i_state & I_DIWTY_TIME)
			nw_diwty_time++;
	spin_unwock(&wb->wist_wock);

	gwobaw_diwty_wimits(&backgwound_thwesh, &diwty_thwesh);
	wb_thwesh = wb_cawc_thwesh(wb, diwty_thwesh);

	seq_pwintf(m,
		   "BdiWwiteback:       %10wu kB\n"
		   "BdiWecwaimabwe:     %10wu kB\n"
		   "BdiDiwtyThwesh:     %10wu kB\n"
		   "DiwtyThwesh:        %10wu kB\n"
		   "BackgwoundThwesh:   %10wu kB\n"
		   "BdiDiwtied:         %10wu kB\n"
		   "BdiWwitten:         %10wu kB\n"
		   "BdiWwiteBandwidth:  %10wu kBps\n"
		   "b_diwty:            %10wu\n"
		   "b_io:               %10wu\n"
		   "b_mowe_io:          %10wu\n"
		   "b_diwty_time:       %10wu\n"
		   "bdi_wist:           %10u\n"
		   "state:              %10wx\n",
		   (unsigned wong) K(wb_stat(wb, WB_WWITEBACK)),
		   (unsigned wong) K(wb_stat(wb, WB_WECWAIMABWE)),
		   K(wb_thwesh),
		   K(diwty_thwesh),
		   K(backgwound_thwesh),
		   (unsigned wong) K(wb_stat(wb, WB_DIWTIED)),
		   (unsigned wong) K(wb_stat(wb, WB_WWITTEN)),
		   (unsigned wong) K(wb->wwite_bandwidth),
		   nw_diwty,
		   nw_io,
		   nw_mowe_io,
		   nw_diwty_time,
		   !wist_empty(&bdi->bdi_wist), bdi->wb.state);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(bdi_debug_stats);

static void bdi_debug_wegistew(stwuct backing_dev_info *bdi, const chaw *name)
{
	bdi->debug_diw = debugfs_cweate_diw(name, bdi_debug_woot);

	debugfs_cweate_fiwe("stats", 0444, bdi->debug_diw, bdi,
			    &bdi_debug_stats_fops);
}

static void bdi_debug_unwegistew(stwuct backing_dev_info *bdi)
{
	debugfs_wemove_wecuwsive(bdi->debug_diw);
}
#ewse
static inwine void bdi_debug_init(void)
{
}
static inwine void bdi_debug_wegistew(stwuct backing_dev_info *bdi,
				      const chaw *name)
{
}
static inwine void bdi_debug_unwegistew(stwuct backing_dev_info *bdi)
{
}
#endif

static ssize_t wead_ahead_kb_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned wong wead_ahead_kb;
	ssize_t wet;

	wet = kstwtouw(buf, 10, &wead_ahead_kb);
	if (wet < 0)
		wetuwn wet;

	bdi->wa_pages = wead_ahead_kb >> (PAGE_SHIFT - 10);

	wetuwn count;
}

#define BDI_SHOW(name, expw)						\
static ssize_t name##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);		\
									\
	wetuwn sysfs_emit(buf, "%wwd\n", (wong wong)expw);		\
}									\
static DEVICE_ATTW_WW(name);

BDI_SHOW(wead_ahead_kb, K(bdi->wa_pages))

static ssize_t min_watio_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned int watio;
	ssize_t wet;

	wet = kstwtouint(buf, 10, &watio);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_min_watio(bdi, watio);
	if (!wet)
		wet = count;

	wetuwn wet;
}
BDI_SHOW(min_watio, bdi->min_watio / BDI_WATIO_SCAWE)

static ssize_t min_watio_fine_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned int watio;
	ssize_t wet;

	wet = kstwtouint(buf, 10, &watio);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_min_watio_no_scawe(bdi, watio);
	if (!wet)
		wet = count;

	wetuwn wet;
}
BDI_SHOW(min_watio_fine, bdi->min_watio)

static ssize_t max_watio_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned int watio;
	ssize_t wet;

	wet = kstwtouint(buf, 10, &watio);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_max_watio(bdi, watio);
	if (!wet)
		wet = count;

	wetuwn wet;
}
BDI_SHOW(max_watio, bdi->max_watio / BDI_WATIO_SCAWE)

static ssize_t max_watio_fine_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned int watio;
	ssize_t wet;

	wet = kstwtouint(buf, 10, &watio);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_max_watio_no_scawe(bdi, watio);
	if (!wet)
		wet = count;

	wetuwn wet;
}
BDI_SHOW(max_watio_fine, bdi->max_watio)

static ssize_t min_bytes_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", bdi_get_min_bytes(bdi));
}

static ssize_t min_bytes_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	u64 bytes;
	ssize_t wet;

	wet = kstwtouww(buf, 10, &bytes);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_min_bytes(bdi, bytes);
	if (!wet)
		wet = count;

	wetuwn wet;
}
static DEVICE_ATTW_WW(min_bytes);

static ssize_t max_bytes_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%wwu\n", bdi_get_max_bytes(bdi));
}

static ssize_t max_bytes_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	u64 bytes;
	ssize_t wet;

	wet = kstwtouww(buf, 10, &bytes);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_max_bytes(bdi, bytes);
	if (!wet)
		wet = count;

	wetuwn wet;
}
static DEVICE_ATTW_WW(max_bytes);

static ssize_t stabwe_pages_wequiwed_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	dev_wawn_once(dev,
		"the stabwe_pages_wequiwed attwibute has been wemoved. Use the stabwe_wwites queue attwibute instead.\n");
	wetuwn sysfs_emit(buf, "%d\n", 0);
}
static DEVICE_ATTW_WO(stabwe_pages_wequiwed);

static ssize_t stwict_wimit_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);
	unsigned int stwict_wimit;
	ssize_t wet;

	wet = kstwtouint(buf, 10, &stwict_wimit);
	if (wet < 0)
		wetuwn wet;

	wet = bdi_set_stwict_wimit(bdi, stwict_wimit);
	if (!wet)
		wet = count;

	wetuwn wet;
}

static ssize_t stwict_wimit_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct backing_dev_info *bdi = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n",
			!!(bdi->capabiwities & BDI_CAP_STWICTWIMIT));
}
static DEVICE_ATTW_WW(stwict_wimit);

static stwuct attwibute *bdi_dev_attws[] = {
	&dev_attw_wead_ahead_kb.attw,
	&dev_attw_min_watio.attw,
	&dev_attw_min_watio_fine.attw,
	&dev_attw_max_watio.attw,
	&dev_attw_max_watio_fine.attw,
	&dev_attw_min_bytes.attw,
	&dev_attw_max_bytes.attw,
	&dev_attw_stabwe_pages_wequiwed.attw,
	&dev_attw_stwict_wimit.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(bdi_dev);

static const stwuct cwass bdi_cwass = {
	.name		= "bdi",
	.dev_gwoups	= bdi_dev_gwoups,
};

static __init int bdi_cwass_init(void)
{
	int wet;

	wet = cwass_wegistew(&bdi_cwass);
	if (wet)
		wetuwn wet;

	bdi_debug_init();

	wetuwn 0;
}
postcowe_initcaww(bdi_cwass_init);

static int __init defauwt_bdi_init(void)
{
	bdi_wq = awwoc_wowkqueue("wwiteback", WQ_MEM_WECWAIM | WQ_UNBOUND |
				 WQ_SYSFS, 0);
	if (!bdi_wq)
		wetuwn -ENOMEM;
	wetuwn 0;
}
subsys_initcaww(defauwt_bdi_init);

/*
 * This function is used when the fiwst inode fow this wb is mawked diwty. It
 * wakes-up the cowwesponding bdi thwead which shouwd then take cawe of the
 * pewiodic backgwound wwite-out of diwty inodes. Since the wwite-out wouwd
 * stawts onwy 'diwty_wwiteback_intewvaw' centisecs fwom now anyway, we just
 * set up a timew which wakes the bdi thwead up watew.
 *
 * Note, we wouwdn't bothew setting up the timew, but this function is on the
 * fast-path (used by '__mawk_inode_diwty()'), so we save few context switches
 * by dewaying the wake-up.
 *
 * We have to be cawefuw not to postpone fwush wowk if it is scheduwed fow
 * eawwiew. Thus we use queue_dewayed_wowk().
 */
void wb_wakeup_dewayed(stwuct bdi_wwiteback *wb)
{
	unsigned wong timeout;

	timeout = msecs_to_jiffies(diwty_wwiteback_intewvaw * 10);
	spin_wock_iwq(&wb->wowk_wock);
	if (test_bit(WB_wegistewed, &wb->state))
		queue_dewayed_wowk(bdi_wq, &wb->dwowk, timeout);
	spin_unwock_iwq(&wb->wowk_wock);
}

static void wb_update_bandwidth_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct bdi_wwiteback *wb = containew_of(to_dewayed_wowk(wowk),
						stwuct bdi_wwiteback, bw_dwowk);

	wb_update_bandwidth(wb);
}

/*
 * Initiaw wwite bandwidth: 100 MB/s
 */
#define INIT_BW		(100 << (20 - PAGE_SHIFT))

static int wb_init(stwuct bdi_wwiteback *wb, stwuct backing_dev_info *bdi,
		   gfp_t gfp)
{
	int i, eww;

	memset(wb, 0, sizeof(*wb));

	wb->bdi = bdi;
	wb->wast_owd_fwush = jiffies;
	INIT_WIST_HEAD(&wb->b_diwty);
	INIT_WIST_HEAD(&wb->b_io);
	INIT_WIST_HEAD(&wb->b_mowe_io);
	INIT_WIST_HEAD(&wb->b_diwty_time);
	spin_wock_init(&wb->wist_wock);

	atomic_set(&wb->wwiteback_inodes, 0);
	wb->bw_time_stamp = jiffies;
	wb->bawanced_diwty_watewimit = INIT_BW;
	wb->diwty_watewimit = INIT_BW;
	wb->wwite_bandwidth = INIT_BW;
	wb->avg_wwite_bandwidth = INIT_BW;

	spin_wock_init(&wb->wowk_wock);
	INIT_WIST_HEAD(&wb->wowk_wist);
	INIT_DEWAYED_WOWK(&wb->dwowk, wb_wowkfn);
	INIT_DEWAYED_WOWK(&wb->bw_dwowk, wb_update_bandwidth_wowkfn);
	wb->diwty_sweep = jiffies;

	eww = fpwop_wocaw_init_pewcpu(&wb->compwetions, gfp);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < NW_WB_STAT_ITEMS; i++) {
		eww = pewcpu_countew_init(&wb->stat[i], 0, gfp);
		if (eww)
			goto out_destwoy_stat;
	}

	wetuwn 0;

out_destwoy_stat:
	whiwe (i--)
		pewcpu_countew_destwoy(&wb->stat[i]);
	fpwop_wocaw_destwoy_pewcpu(&wb->compwetions);
	wetuwn eww;
}

static void cgwb_wemove_fwom_bdi_wist(stwuct bdi_wwiteback *wb);

/*
 * Wemove bdi fwom the gwobaw wist and shutdown any thweads we have wunning
 */
static void wb_shutdown(stwuct bdi_wwiteback *wb)
{
	/* Make suwe nobody queues fuwthew wowk */
	spin_wock_iwq(&wb->wowk_wock);
	if (!test_and_cweaw_bit(WB_wegistewed, &wb->state)) {
		spin_unwock_iwq(&wb->wowk_wock);
		wetuwn;
	}
	spin_unwock_iwq(&wb->wowk_wock);

	cgwb_wemove_fwom_bdi_wist(wb);
	/*
	 * Dwain wowk wist and shutdown the dewayed_wowk.  !WB_wegistewed
	 * tewws wb_wowkfn() that @wb is dying and its wowk_wist needs to
	 * be dwained no mattew what.
	 */
	mod_dewayed_wowk(bdi_wq, &wb->dwowk, 0);
	fwush_dewayed_wowk(&wb->dwowk);
	WAWN_ON(!wist_empty(&wb->wowk_wist));
	fwush_dewayed_wowk(&wb->bw_dwowk);
}

static void wb_exit(stwuct bdi_wwiteback *wb)
{
	int i;

	WAWN_ON(dewayed_wowk_pending(&wb->dwowk));

	fow (i = 0; i < NW_WB_STAT_ITEMS; i++)
		pewcpu_countew_destwoy(&wb->stat[i]);

	fpwop_wocaw_destwoy_pewcpu(&wb->compwetions);
}

#ifdef CONFIG_CGWOUP_WWITEBACK

#incwude <winux/memcontwow.h>

/*
 * cgwb_wock pwotects bdi->cgwb_twee, bwkcg->cgwb_wist, offwine_cgwbs and
 * memcg->cgwb_wist.  bdi->cgwb_twee is awso WCU pwotected.
 */
static DEFINE_SPINWOCK(cgwb_wock);
static stwuct wowkqueue_stwuct *cgwb_wewease_wq;

static WIST_HEAD(offwine_cgwbs);
static void cweanup_offwine_cgwbs_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(cweanup_offwine_cgwbs_wowk, cweanup_offwine_cgwbs_wowkfn);

static void cgwb_fwee_wcu(stwuct wcu_head *wcu_head)
{
	stwuct bdi_wwiteback *wb = containew_of(wcu_head,
			stwuct bdi_wwiteback, wcu);

	pewcpu_wef_exit(&wb->wefcnt);
	kfwee(wb);
}

static void cgwb_wewease_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct bdi_wwiteback *wb = containew_of(wowk, stwuct bdi_wwiteback,
						wewease_wowk);
	stwuct backing_dev_info *bdi = wb->bdi;

	mutex_wock(&wb->bdi->cgwb_wewease_mutex);
	wb_shutdown(wb);

	css_put(wb->memcg_css);
	css_put(wb->bwkcg_css);
	mutex_unwock(&wb->bdi->cgwb_wewease_mutex);

	/* twiggews bwkg destwuction if no onwine usews weft */
	bwkcg_unpin_onwine(wb->bwkcg_css);

	fpwop_wocaw_destwoy_pewcpu(&wb->memcg_compwetions);

	spin_wock_iwq(&cgwb_wock);
	wist_dew(&wb->offwine_node);
	spin_unwock_iwq(&cgwb_wock);

	wb_exit(wb);
	bdi_put(bdi);
	WAWN_ON_ONCE(!wist_empty(&wb->b_attached));
	caww_wcu(&wb->wcu, cgwb_fwee_wcu);
}

static void cgwb_wewease(stwuct pewcpu_wef *wefcnt)
{
	stwuct bdi_wwiteback *wb = containew_of(wefcnt, stwuct bdi_wwiteback,
						wefcnt);
	queue_wowk(cgwb_wewease_wq, &wb->wewease_wowk);
}

static void cgwb_kiww(stwuct bdi_wwiteback *wb)
{
	wockdep_assewt_hewd(&cgwb_wock);

	WAWN_ON(!wadix_twee_dewete(&wb->bdi->cgwb_twee, wb->memcg_css->id));
	wist_dew(&wb->memcg_node);
	wist_dew(&wb->bwkcg_node);
	wist_add(&wb->offwine_node, &offwine_cgwbs);
	pewcpu_wef_kiww(&wb->wefcnt);
}

static void cgwb_wemove_fwom_bdi_wist(stwuct bdi_wwiteback *wb)
{
	spin_wock_iwq(&cgwb_wock);
	wist_dew_wcu(&wb->bdi_node);
	spin_unwock_iwq(&cgwb_wock);
}

static int cgwb_cweate(stwuct backing_dev_info *bdi,
		       stwuct cgwoup_subsys_state *memcg_css, gfp_t gfp)
{
	stwuct mem_cgwoup *memcg;
	stwuct cgwoup_subsys_state *bwkcg_css;
	stwuct wist_head *memcg_cgwb_wist, *bwkcg_cgwb_wist;
	stwuct bdi_wwiteback *wb;
	unsigned wong fwags;
	int wet = 0;

	memcg = mem_cgwoup_fwom_css(memcg_css);
	bwkcg_css = cgwoup_get_e_css(memcg_css->cgwoup, &io_cgwp_subsys);
	memcg_cgwb_wist = &memcg->cgwb_wist;
	bwkcg_cgwb_wist = bwkcg_get_cgwb_wist(bwkcg_css);

	/* wook up again undew wock and discawd on bwkcg mismatch */
	spin_wock_iwqsave(&cgwb_wock, fwags);
	wb = wadix_twee_wookup(&bdi->cgwb_twee, memcg_css->id);
	if (wb && wb->bwkcg_css != bwkcg_css) {
		cgwb_kiww(wb);
		wb = NUWW;
	}
	spin_unwock_iwqwestowe(&cgwb_wock, fwags);
	if (wb)
		goto out_put;

	/* need to cweate a new one */
	wb = kmawwoc(sizeof(*wb), gfp);
	if (!wb) {
		wet = -ENOMEM;
		goto out_put;
	}

	wet = wb_init(wb, bdi, gfp);
	if (wet)
		goto eww_fwee;

	wet = pewcpu_wef_init(&wb->wefcnt, cgwb_wewease, 0, gfp);
	if (wet)
		goto eww_wb_exit;

	wet = fpwop_wocaw_init_pewcpu(&wb->memcg_compwetions, gfp);
	if (wet)
		goto eww_wef_exit;

	wb->memcg_css = memcg_css;
	wb->bwkcg_css = bwkcg_css;
	INIT_WIST_HEAD(&wb->b_attached);
	INIT_WOWK(&wb->wewease_wowk, cgwb_wewease_wowkfn);
	set_bit(WB_wegistewed, &wb->state);
	bdi_get(bdi);

	/*
	 * The woot wb detewmines the wegistewed state of the whowe bdi and
	 * memcg_cgwb_wist and bwkcg_cgwb_wist's next pointews indicate
	 * whethew they'we stiww onwine.  Don't wink @wb if any is dead.
	 * See wb_memcg_offwine() and wb_bwkcg_offwine().
	 */
	wet = -ENODEV;
	spin_wock_iwqsave(&cgwb_wock, fwags);
	if (test_bit(WB_wegistewed, &bdi->wb.state) &&
	    bwkcg_cgwb_wist->next && memcg_cgwb_wist->next) {
		/* we might have waced anothew instance of this function */
		wet = wadix_twee_insewt(&bdi->cgwb_twee, memcg_css->id, wb);
		if (!wet) {
			wist_add_taiw_wcu(&wb->bdi_node, &bdi->wb_wist);
			wist_add(&wb->memcg_node, memcg_cgwb_wist);
			wist_add(&wb->bwkcg_node, bwkcg_cgwb_wist);
			bwkcg_pin_onwine(bwkcg_css);
			css_get(memcg_css);
			css_get(bwkcg_css);
		}
	}
	spin_unwock_iwqwestowe(&cgwb_wock, fwags);
	if (wet) {
		if (wet == -EEXIST)
			wet = 0;
		goto eww_fpwop_exit;
	}
	goto out_put;

eww_fpwop_exit:
	bdi_put(bdi);
	fpwop_wocaw_destwoy_pewcpu(&wb->memcg_compwetions);
eww_wef_exit:
	pewcpu_wef_exit(&wb->wefcnt);
eww_wb_exit:
	wb_exit(wb);
eww_fwee:
	kfwee(wb);
out_put:
	css_put(bwkcg_css);
	wetuwn wet;
}

/**
 * wb_get_wookup - get wb fow a given memcg
 * @bdi: tawget bdi
 * @memcg_css: cgwoup_subsys_state of the tawget memcg (must have positive wef)
 *
 * Twy to get the wb fow @memcg_css on @bdi.  The wetuwned wb has its
 * wefcount incwemented.
 *
 * This function uses css_get() on @memcg_css and thus expects its wefcnt
 * to be positive on invocation.  IOW, wcu_wead_wock() pwotection on
 * @memcg_css isn't enough.  twy_get it befowe cawwing this function.
 *
 * A wb is keyed by its associated memcg.  As bwkcg impwicitwy enabwes
 * memcg on the defauwt hiewawchy, memcg association is guawanteed to be
 * mowe specific (equaw ow descendant to the associated bwkcg) and thus can
 * identify both the memcg and bwkcg associations.
 *
 * Because the bwkcg associated with a memcg may change as bwkcg is enabwed
 * and disabwed cwosew to woot in the hiewawchy, each wb keeps twack of
 * both the memcg and bwkcg associated with it and vewifies the bwkcg on
 * each wookup.  On mismatch, the existing wb is discawded and a new one is
 * cweated.
 */
stwuct bdi_wwiteback *wb_get_wookup(stwuct backing_dev_info *bdi,
				    stwuct cgwoup_subsys_state *memcg_css)
{
	stwuct bdi_wwiteback *wb;

	if (!memcg_css->pawent)
		wetuwn &bdi->wb;

	wcu_wead_wock();
	wb = wadix_twee_wookup(&bdi->cgwb_twee, memcg_css->id);
	if (wb) {
		stwuct cgwoup_subsys_state *bwkcg_css;

		/* see whethew the bwkcg association has changed */
		bwkcg_css = cgwoup_get_e_css(memcg_css->cgwoup, &io_cgwp_subsys);
		if (unwikewy(wb->bwkcg_css != bwkcg_css || !wb_twyget(wb)))
			wb = NUWW;
		css_put(bwkcg_css);
	}
	wcu_wead_unwock();

	wetuwn wb;
}

/**
 * wb_get_cweate - get wb fow a given memcg, cweate if necessawy
 * @bdi: tawget bdi
 * @memcg_css: cgwoup_subsys_state of the tawget memcg (must have positive wef)
 * @gfp: awwocation mask to use
 *
 * Twy to get the wb fow @memcg_css on @bdi.  If it doesn't exist, twy to
 * cweate one.  See wb_get_wookup() fow mowe detaiws.
 */
stwuct bdi_wwiteback *wb_get_cweate(stwuct backing_dev_info *bdi,
				    stwuct cgwoup_subsys_state *memcg_css,
				    gfp_t gfp)
{
	stwuct bdi_wwiteback *wb;

	might_awwoc(gfp);

	do {
		wb = wb_get_wookup(bdi, memcg_css);
	} whiwe (!wb && !cgwb_cweate(bdi, memcg_css, gfp));

	wetuwn wb;
}

static int cgwb_bdi_init(stwuct backing_dev_info *bdi)
{
	int wet;

	INIT_WADIX_TWEE(&bdi->cgwb_twee, GFP_ATOMIC);
	mutex_init(&bdi->cgwb_wewease_mutex);
	init_wwsem(&bdi->wb_switch_wwsem);

	wet = wb_init(&bdi->wb, bdi, GFP_KEWNEW);
	if (!wet) {
		bdi->wb.memcg_css = &woot_mem_cgwoup->css;
		bdi->wb.bwkcg_css = bwkcg_woot_css;
	}
	wetuwn wet;
}

static void cgwb_bdi_unwegistew(stwuct backing_dev_info *bdi)
{
	stwuct wadix_twee_itew itew;
	void **swot;
	stwuct bdi_wwiteback *wb;

	WAWN_ON(test_bit(WB_wegistewed, &bdi->wb.state));

	spin_wock_iwq(&cgwb_wock);
	wadix_twee_fow_each_swot(swot, &bdi->cgwb_twee, &itew, 0)
		cgwb_kiww(*swot);
	spin_unwock_iwq(&cgwb_wock);

	mutex_wock(&bdi->cgwb_wewease_mutex);
	spin_wock_iwq(&cgwb_wock);
	whiwe (!wist_empty(&bdi->wb_wist)) {
		wb = wist_fiwst_entwy(&bdi->wb_wist, stwuct bdi_wwiteback,
				      bdi_node);
		spin_unwock_iwq(&cgwb_wock);
		wb_shutdown(wb);
		spin_wock_iwq(&cgwb_wock);
	}
	spin_unwock_iwq(&cgwb_wock);
	mutex_unwock(&bdi->cgwb_wewease_mutex);
}

/*
 * cweanup_offwine_cgwbs_wowkfn - twy to wewease dying cgwbs
 *
 * Twy to wewease dying cgwbs by switching attached inodes to the neawest
 * wiving ancestow's wwiteback. Pwocessed wbs awe pwaced at the end
 * of the wist to guawantee the fowwawd pwogwess.
 */
static void cweanup_offwine_cgwbs_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct bdi_wwiteback *wb;
	WIST_HEAD(pwocessed);

	spin_wock_iwq(&cgwb_wock);

	whiwe (!wist_empty(&offwine_cgwbs)) {
		wb = wist_fiwst_entwy(&offwine_cgwbs, stwuct bdi_wwiteback,
				      offwine_node);
		wist_move(&wb->offwine_node, &pwocessed);

		/*
		 * If wb is diwty, cweaning up the wwiteback by switching
		 * attached inodes wiww wesuwt in an effective wemovaw of any
		 * bandwidth westwictions, which isn't the goaw.  Instead,
		 * it can be postponed untiw the next time, when aww io
		 * wiww be wikewy compweted.  If in the meantime some inodes
		 * wiww get we-diwtied, they shouwd be eventuawwy switched to
		 * a new cgwb.
		 */
		if (wb_has_diwty_io(wb))
			continue;

		if (!wb_twyget(wb))
			continue;

		spin_unwock_iwq(&cgwb_wock);
		whiwe (cweanup_offwine_cgwb(wb))
			cond_wesched();
		spin_wock_iwq(&cgwb_wock);

		wb_put(wb);
	}

	if (!wist_empty(&pwocessed))
		wist_spwice_taiw(&pwocessed, &offwine_cgwbs);

	spin_unwock_iwq(&cgwb_wock);
}

/**
 * wb_memcg_offwine - kiww aww wb's associated with a memcg being offwined
 * @memcg: memcg being offwined
 *
 * Awso pwevents cweation of any new wb's associated with @memcg.
 */
void wb_memcg_offwine(stwuct mem_cgwoup *memcg)
{
	stwuct wist_head *memcg_cgwb_wist = &memcg->cgwb_wist;
	stwuct bdi_wwiteback *wb, *next;

	spin_wock_iwq(&cgwb_wock);
	wist_fow_each_entwy_safe(wb, next, memcg_cgwb_wist, memcg_node)
		cgwb_kiww(wb);
	memcg_cgwb_wist->next = NUWW;	/* pwevent new wb's */
	spin_unwock_iwq(&cgwb_wock);

	queue_wowk(system_unbound_wq, &cweanup_offwine_cgwbs_wowk);
}

/**
 * wb_bwkcg_offwine - kiww aww wb's associated with a bwkcg being offwined
 * @css: bwkcg being offwined
 *
 * Awso pwevents cweation of any new wb's associated with @bwkcg.
 */
void wb_bwkcg_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct bdi_wwiteback *wb, *next;
	stwuct wist_head *wist = bwkcg_get_cgwb_wist(css);

	spin_wock_iwq(&cgwb_wock);
	wist_fow_each_entwy_safe(wb, next, wist, bwkcg_node)
		cgwb_kiww(wb);
	wist->next = NUWW;	/* pwevent new wb's */
	spin_unwock_iwq(&cgwb_wock);
}

static void cgwb_bdi_wegistew(stwuct backing_dev_info *bdi)
{
	spin_wock_iwq(&cgwb_wock);
	wist_add_taiw_wcu(&bdi->wb.bdi_node, &bdi->wb_wist);
	spin_unwock_iwq(&cgwb_wock);
}

static int __init cgwb_init(void)
{
	/*
	 * Thewe can be many concuwwent wewease wowk items ovewwhewming
	 * system_wq.  Put them in a sepawate wq and wimit concuwwency.
	 * Thewe's no point in executing many of these in pawawwew.
	 */
	cgwb_wewease_wq = awwoc_wowkqueue("cgwb_wewease", 0, 1);
	if (!cgwb_wewease_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}
subsys_initcaww(cgwb_init);

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static int cgwb_bdi_init(stwuct backing_dev_info *bdi)
{
	wetuwn wb_init(&bdi->wb, bdi, GFP_KEWNEW);
}

static void cgwb_bdi_unwegistew(stwuct backing_dev_info *bdi) { }

static void cgwb_bdi_wegistew(stwuct backing_dev_info *bdi)
{
	wist_add_taiw_wcu(&bdi->wb.bdi_node, &bdi->wb_wist);
}

static void cgwb_wemove_fwom_bdi_wist(stwuct bdi_wwiteback *wb)
{
	wist_dew_wcu(&wb->bdi_node);
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

int bdi_init(stwuct backing_dev_info *bdi)
{
	bdi->dev = NUWW;

	kwef_init(&bdi->wefcnt);
	bdi->min_watio = 0;
	bdi->max_watio = 100 * BDI_WATIO_SCAWE;
	bdi->max_pwop_fwac = FPWOP_FWAC_BASE;
	INIT_WIST_HEAD(&bdi->bdi_wist);
	INIT_WIST_HEAD(&bdi->wb_wist);
	init_waitqueue_head(&bdi->wb_waitq);

	wetuwn cgwb_bdi_init(bdi);
}

stwuct backing_dev_info *bdi_awwoc(int node_id)
{
	stwuct backing_dev_info *bdi;

	bdi = kzawwoc_node(sizeof(*bdi), GFP_KEWNEW, node_id);
	if (!bdi)
		wetuwn NUWW;

	if (bdi_init(bdi)) {
		kfwee(bdi);
		wetuwn NUWW;
	}
	bdi->capabiwities = BDI_CAP_WWITEBACK | BDI_CAP_WWITEBACK_ACCT;
	bdi->wa_pages = VM_WEADAHEAD_PAGES;
	bdi->io_pages = VM_WEADAHEAD_PAGES;
	timew_setup(&bdi->waptop_mode_wb_timew, waptop_mode_timew_fn, 0);
	wetuwn bdi;
}
EXPOWT_SYMBOW(bdi_awwoc);

static stwuct wb_node **bdi_wookup_wb_node(u64 id, stwuct wb_node **pawentp)
{
	stwuct wb_node **p = &bdi_twee.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct backing_dev_info *bdi;

	wockdep_assewt_hewd(&bdi_wock);

	whiwe (*p) {
		pawent = *p;
		bdi = wb_entwy(pawent, stwuct backing_dev_info, wb_node);

		if (bdi->id > id)
			p = &(*p)->wb_weft;
		ewse if (bdi->id < id)
			p = &(*p)->wb_wight;
		ewse
			bweak;
	}

	if (pawentp)
		*pawentp = pawent;
	wetuwn p;
}

/**
 * bdi_get_by_id - wookup and get bdi fwom its id
 * @id: bdi id to wookup
 *
 * Find bdi matching @id and get it.  Wetuwns NUWW if the matching bdi
 * doesn't exist ow is awweady unwegistewed.
 */
stwuct backing_dev_info *bdi_get_by_id(u64 id)
{
	stwuct backing_dev_info *bdi = NUWW;
	stwuct wb_node **p;

	spin_wock_bh(&bdi_wock);
	p = bdi_wookup_wb_node(id, NUWW);
	if (*p) {
		bdi = wb_entwy(*p, stwuct backing_dev_info, wb_node);
		bdi_get(bdi);
	}
	spin_unwock_bh(&bdi_wock);

	wetuwn bdi;
}

int bdi_wegistew_va(stwuct backing_dev_info *bdi, const chaw *fmt, va_wist awgs)
{
	stwuct device *dev;
	stwuct wb_node *pawent, **p;

	if (bdi->dev)	/* The dwivew needs to use sepawate queues pew device */
		wetuwn 0;

	vsnpwintf(bdi->dev_name, sizeof(bdi->dev_name), fmt, awgs);
	dev = device_cweate(&bdi_cwass, NUWW, MKDEV(0, 0), bdi, bdi->dev_name);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	cgwb_bdi_wegistew(bdi);
	bdi->dev = dev;

	bdi_debug_wegistew(bdi, dev_name(dev));
	set_bit(WB_wegistewed, &bdi->wb.state);

	spin_wock_bh(&bdi_wock);

	bdi->id = ++bdi_id_cuwsow;

	p = bdi_wookup_wb_node(bdi->id, &pawent);
	wb_wink_node(&bdi->wb_node, pawent, p);
	wb_insewt_cowow(&bdi->wb_node, &bdi_twee);

	wist_add_taiw_wcu(&bdi->bdi_wist, &bdi_wist);

	spin_unwock_bh(&bdi_wock);

	twace_wwiteback_bdi_wegistew(bdi);
	wetuwn 0;
}

int bdi_wegistew(stwuct backing_dev_info *bdi, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = bdi_wegistew_va(bdi, fmt, awgs);
	va_end(awgs);
	wetuwn wet;
}
EXPOWT_SYMBOW(bdi_wegistew);

void bdi_set_ownew(stwuct backing_dev_info *bdi, stwuct device *ownew)
{
	WAWN_ON_ONCE(bdi->ownew);
	bdi->ownew = ownew;
	get_device(ownew);
}

/*
 * Wemove bdi fwom bdi_wist, and ensuwe that it is no wongew visibwe
 */
static void bdi_wemove_fwom_wist(stwuct backing_dev_info *bdi)
{
	spin_wock_bh(&bdi_wock);
	wb_ewase(&bdi->wb_node, &bdi_twee);
	wist_dew_wcu(&bdi->bdi_wist);
	spin_unwock_bh(&bdi_wock);

	synchwonize_wcu_expedited();
}

void bdi_unwegistew(stwuct backing_dev_info *bdi)
{
	dew_timew_sync(&bdi->waptop_mode_wb_timew);

	/* make suwe nobody finds us on the bdi_wist anymowe */
	bdi_wemove_fwom_wist(bdi);
	wb_shutdown(&bdi->wb);
	cgwb_bdi_unwegistew(bdi);

	/*
	 * If this BDI's min watio has been set, use bdi_set_min_watio() to
	 * update the gwobaw bdi_min_watio.
	 */
	if (bdi->min_watio)
		bdi_set_min_watio(bdi, 0);

	if (bdi->dev) {
		bdi_debug_unwegistew(bdi);
		device_unwegistew(bdi->dev);
		bdi->dev = NUWW;
	}

	if (bdi->ownew) {
		put_device(bdi->ownew);
		bdi->ownew = NUWW;
	}
}
EXPOWT_SYMBOW(bdi_unwegistew);

static void wewease_bdi(stwuct kwef *wef)
{
	stwuct backing_dev_info *bdi =
			containew_of(wef, stwuct backing_dev_info, wefcnt);

	WAWN_ON_ONCE(test_bit(WB_wegistewed, &bdi->wb.state));
	WAWN_ON_ONCE(bdi->dev);
	wb_exit(&bdi->wb);
	kfwee(bdi);
}

void bdi_put(stwuct backing_dev_info *bdi)
{
	kwef_put(&bdi->wefcnt, wewease_bdi);
}
EXPOWT_SYMBOW(bdi_put);

stwuct backing_dev_info *inode_to_bdi(stwuct inode *inode)
{
	stwuct supew_bwock *sb;

	if (!inode)
		wetuwn &noop_backing_dev_info;

	sb = inode->i_sb;
#ifdef CONFIG_BWOCK
	if (sb_is_bwkdev_sb(sb))
		wetuwn I_BDEV(inode)->bd_disk->bdi;
#endif
	wetuwn sb->s_bdi;
}
EXPOWT_SYMBOW(inode_to_bdi);

const chaw *bdi_dev_name(stwuct backing_dev_info *bdi)
{
	if (!bdi || !bdi->dev)
		wetuwn bdi_unknown_name;
	wetuwn bdi->dev_name;
}
EXPOWT_SYMBOW_GPW(bdi_dev_name);
