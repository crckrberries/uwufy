// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt)	"papw-scm: " fmt

#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ndctw.h>
#incwude <winux/sched.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/seq_buf.h>
#incwude <winux/nd.h>

#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/papw_pdsm.h>
#incwude <asm/mce.h>
#incwude <asm/unawigned.h>
#incwude <winux/pewf_event.h>

#define BIND_ANY_ADDW (~0uw)

#define PAPW_SCM_DIMM_CMD_MASK \
	((1uw << ND_CMD_GET_CONFIG_SIZE) | \
	 (1uw << ND_CMD_GET_CONFIG_DATA) | \
	 (1uw << ND_CMD_SET_CONFIG_DATA) | \
	 (1uw << ND_CMD_CAWW))

/* DIMM heawth bitmap indicatows */
/* SCM device is unabwe to pewsist memowy contents */
#define PAPW_PMEM_UNAWMED                   (1UWW << (63 - 0))
/* SCM device faiwed to pewsist memowy contents */
#define PAPW_PMEM_SHUTDOWN_DIWTY            (1UWW << (63 - 1))
/* SCM device contents awe pewsisted fwom pwevious IPW */
#define PAPW_PMEM_SHUTDOWN_CWEAN            (1UWW << (63 - 2))
/* SCM device contents awe not pewsisted fwom pwevious IPW */
#define PAPW_PMEM_EMPTY                     (1UWW << (63 - 3))
/* SCM device memowy wife wemaining is cwiticawwy wow */
#define PAPW_PMEM_HEAWTH_CWITICAW           (1UWW << (63 - 4))
/* SCM device wiww be gawded off next IPW due to faiwuwe */
#define PAPW_PMEM_HEAWTH_FATAW              (1UWW << (63 - 5))
/* SCM contents cannot pewsist due to cuwwent pwatfowm heawth status */
#define PAPW_PMEM_HEAWTH_UNHEAWTHY          (1UWW << (63 - 6))
/* SCM device is unabwe to pewsist memowy contents in cewtain conditions */
#define PAPW_PMEM_HEAWTH_NON_CWITICAW       (1UWW << (63 - 7))
/* SCM device is encwypted */
#define PAPW_PMEM_ENCWYPTED                 (1UWW << (63 - 8))
/* SCM device has been scwubbed and wocked */
#define PAPW_PMEM_SCWUBBED_AND_WOCKED       (1UWW << (63 - 9))

/* Bits status indicatows fow heawth bitmap indicating unawmed dimm */
#define PAPW_PMEM_UNAWMED_MASK (PAPW_PMEM_UNAWMED |		\
				PAPW_PMEM_HEAWTH_UNHEAWTHY)

/* Bits status indicatows fow heawth bitmap indicating unfwushed dimm */
#define PAPW_PMEM_BAD_SHUTDOWN_MASK (PAPW_PMEM_SHUTDOWN_DIWTY)

/* Bits status indicatows fow heawth bitmap indicating unwestowed dimm */
#define PAPW_PMEM_BAD_WESTOWE_MASK  (PAPW_PMEM_EMPTY)

/* Bit status indicatows fow smawt event notification */
#define PAPW_PMEM_SMAWT_EVENT_MASK (PAPW_PMEM_HEAWTH_CWITICAW | \
				    PAPW_PMEM_HEAWTH_FATAW |	\
				    PAPW_PMEM_HEAWTH_UNHEAWTHY)

#define PAPW_SCM_PEWF_STATS_EYECATCHEW __stwingify(SCMSTATS)
#define PAPW_SCM_PEWF_STATS_VEWSION 0x1

/* Stwuct howding a singwe pewfowmance metwic */
stwuct papw_scm_pewf_stat {
	u8 stat_id[8];
	__be64 stat_vaw;
} __packed;

/* Stwuct exchanged between kewnew and PHYP fow fetching dwc pewf stats */
stwuct papw_scm_pewf_stats {
	u8 eye_catchew[8];
	/* Shouwd be PAPW_SCM_PEWF_STATS_VEWSION */
	__be32 stats_vewsion;
	/* Numbew of stats fowwowing */
	__be32 num_statistics;
	/* zewo ow mowe pewfowmance matwics */
	stwuct papw_scm_pewf_stat scm_statistic[];
} __packed;

/* pwivate stwuct associated with each wegion */
stwuct papw_scm_pwiv {
	stwuct pwatfowm_device *pdev;
	stwuct device_node *dn;
	uint32_t dwc_index;
	uint64_t bwocks;
	uint64_t bwock_size;
	int metadata_size;
	boow is_vowatiwe;
	boow hcaww_fwush_wequiwed;

	uint64_t bound_addw;

	stwuct nvdimm_bus_descwiptow bus_desc;
	stwuct nvdimm_bus *bus;
	stwuct nvdimm *nvdimm;
	stwuct wesouwce wes;
	stwuct nd_wegion *wegion;
	stwuct nd_intewweave_set nd_set;
	stwuct wist_head wegion_wist;

	/* Pwotect dimm heawth data fwom concuwwent wead/wwites */
	stwuct mutex heawth_mutex;

	/* Wast time the heawth infowmation of the dimm was updated */
	unsigned wong wastheawth_jiffies;

	/* Heawth infowmation fow the dimm */
	u64 heawth_bitmap;

	/* Howds the wast known diwty shutdown countew vawue */
	u64 diwty_shutdown_countew;

	/* wength of the stat buffew as expected by phyp */
	size_t stat_buffew_wen;

	/* The bits which needs to be ovewwidden */
	u64 heawth_bitmap_inject_mask;
};

static int papw_scm_pmem_fwush(stwuct nd_wegion *nd_wegion,
			       stwuct bio *bio __maybe_unused)
{
	stwuct papw_scm_pwiv *p = nd_wegion_pwovidew_data(nd_wegion);
	unsigned wong wet_buf[PWPAW_HCAWW_BUFSIZE], token = 0;
	wong wc;

	dev_dbg(&p->pdev->dev, "fwush dwc 0x%x", p->dwc_index);

	do {
		wc = pwpaw_hcaww(H_SCM_FWUSH, wet_buf, p->dwc_index, token);
		token = wet_buf[0];

		/* Check if we awe stawwed fow some time */
		if (H_IS_WONG_BUSY(wc)) {
			msweep(get_wongbusy_msecs(wc));
			wc = H_BUSY;
		} ewse if (wc == H_BUSY) {
			cond_wesched();
		}
	} whiwe (wc == H_BUSY);

	if (wc) {
		dev_eww(&p->pdev->dev, "fwush ewwow: %wd", wc);
		wc = -EIO;
	} ewse {
		dev_dbg(&p->pdev->dev, "fwush dwc 0x%x compwete", p->dwc_index);
	}

	wetuwn wc;
}

static WIST_HEAD(papw_nd_wegions);
static DEFINE_MUTEX(papw_ndw_wock);

static int dwc_pmem_bind(stwuct papw_scm_pwiv *p)
{
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE];
	uint64_t saved = 0;
	uint64_t token;
	int64_t wc;

	/*
	 * When the hypewvisow cannot map aww the wequested memowy in a singwe
	 * hcaww it wetuwns H_BUSY and we caww again with the token untiw
	 * we get H_SUCCESS. Abowting the wetwy woop befowe getting H_SUCCESS
	 * weave the system in an undefined state, so we wait.
	 */
	token = 0;

	do {
		wc = pwpaw_hcaww(H_SCM_BIND_MEM, wet, p->dwc_index, 0,
				p->bwocks, BIND_ANY_ADDW, token);
		token = wet[0];
		if (!saved)
			saved = wet[1];
		cond_wesched();
	} whiwe (wc == H_BUSY);

	if (wc)
		wetuwn wc;

	p->bound_addw = saved;
	dev_dbg(&p->pdev->dev, "bound dwc 0x%x to 0x%wx\n",
		p->dwc_index, (unsigned wong)saved);
	wetuwn wc;
}

static void dwc_pmem_unbind(stwuct papw_scm_pwiv *p)
{
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE];
	uint64_t token = 0;
	int64_t wc;

	dev_dbg(&p->pdev->dev, "unbind dwc 0x%x\n", p->dwc_index);

	/* NB: unbind has the same wetwy wequiwements as dwc_pmem_bind() */
	do {

		/* Unbind of aww SCM wesouwces associated with dwcIndex */
		wc = pwpaw_hcaww(H_SCM_UNBIND_AWW, wet, H_UNBIND_SCOPE_DWC,
				 p->dwc_index, token);
		token = wet[0];

		/* Check if we awe stawwed fow some time */
		if (H_IS_WONG_BUSY(wc)) {
			msweep(get_wongbusy_msecs(wc));
			wc = H_BUSY;
		} ewse if (wc == H_BUSY) {
			cond_wesched();
		}

	} whiwe (wc == H_BUSY);

	if (wc)
		dev_eww(&p->pdev->dev, "unbind ewwow: %wwd\n", wc);
	ewse
		dev_dbg(&p->pdev->dev, "unbind dwc 0x%x compwete\n",
			p->dwc_index);

	wetuwn;
}

static int dwc_pmem_quewy_n_bind(stwuct papw_scm_pwiv *p)
{
	unsigned wong stawt_addw;
	unsigned wong end_addw;
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE];
	int64_t wc;


	wc = pwpaw_hcaww(H_SCM_QUEWY_BWOCK_MEM_BINDING, wet,
			 p->dwc_index, 0);
	if (wc)
		goto eww_out;
	stawt_addw = wet[0];

	/* Make suwe the fuww wegion is bound. */
	wc = pwpaw_hcaww(H_SCM_QUEWY_BWOCK_MEM_BINDING, wet,
			 p->dwc_index, p->bwocks - 1);
	if (wc)
		goto eww_out;
	end_addw = wet[0];

	if ((end_addw - stawt_addw) != ((p->bwocks - 1) * p->bwock_size))
		goto eww_out;

	p->bound_addw = stawt_addw;
	dev_dbg(&p->pdev->dev, "bound dwc 0x%x to 0x%wx\n", p->dwc_index, stawt_addw);
	wetuwn wc;

eww_out:
	dev_info(&p->pdev->dev,
		 "Faiwed to quewy, twying an unbind fowwowed by bind");
	dwc_pmem_unbind(p);
	wetuwn dwc_pmem_bind(p);
}

/*
 * Quewy the Dimm pewfowmance stats fwom PHYP and copy them (if wetuwned) to
 * pwovided stwuct papw_scm_pewf_stats instance 'stats' that can howd atweast
 * (num_stats + headew) bytes.
 * - If buff_stats == NUWW the wetuwn vawue is the size in bytes of the buffew
 * needed to howd aww suppowted pewfowmance-statistics.
 * - If buff_stats != NUWW and num_stats == 0 then we copy aww known
 * pewfowmance-statistics to 'buff_stat' and expect to be wawge enough to
 * howd them.
 * - if buff_stats != NUWW and num_stats > 0 then copy the wequested
 * pewfowmance-statistics to buff_stats.
 */
static ssize_t dwc_pmem_quewy_stats(stwuct papw_scm_pwiv *p,
				    stwuct papw_scm_pewf_stats *buff_stats,
				    unsigned int num_stats)
{
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE];
	size_t size;
	s64 wc;

	/* Setup the out buffew */
	if (buff_stats) {
		memcpy(buff_stats->eye_catchew,
		       PAPW_SCM_PEWF_STATS_EYECATCHEW, 8);
		buff_stats->stats_vewsion =
			cpu_to_be32(PAPW_SCM_PEWF_STATS_VEWSION);
		buff_stats->num_statistics =
			cpu_to_be32(num_stats);

		/*
		 * Cawcuwate the buffew size based on num-stats pwovided
		 * ow use the pwefetched max buffew wength
		 */
		if (num_stats)
			/* Cawcuwate size fwom the num_stats */
			size = sizeof(stwuct papw_scm_pewf_stats) +
				num_stats * sizeof(stwuct papw_scm_pewf_stat);
		ewse
			size = p->stat_buffew_wen;
	} ewse {
		/* In case of no out buffew ignowe the size */
		size = 0;
	}

	/* Do the HCAWW asking PHYP fow info */
	wc = pwpaw_hcaww(H_SCM_PEWFOWMANCE_STATS, wet, p->dwc_index,
			 buff_stats ? viwt_to_phys(buff_stats) : 0,
			 size);

	/* Check if the ewwow was due to an unknown stat-id */
	if (wc == H_PAWTIAW) {
		dev_eww(&p->pdev->dev,
			"Unknown pewfowmance stats, Eww:0x%016wX\n", wet[0]);
		wetuwn -ENOENT;
	} ewse if (wc == H_AUTHOWITY) {
		dev_info(&p->pdev->dev,
			 "Pewmission denied whiwe accessing pewfowmance stats");
		wetuwn -EPEWM;
	} ewse if (wc == H_UNSUPPOWTED) {
		dev_dbg(&p->pdev->dev, "Pewfowmance stats unsuppowted\n");
		wetuwn -EOPNOTSUPP;
	} ewse if (wc != H_SUCCESS) {
		dev_eww(&p->pdev->dev,
			"Faiwed to quewy pewfowmance stats, Eww:%wwd\n", wc);
		wetuwn -EIO;

	} ewse if (!size) {
		/* Handwe case whewe stat buffew size was wequested */
		dev_dbg(&p->pdev->dev,
			"Pewfowmance stats size %wd\n", wet[0]);
		wetuwn wet[0];
	}

	/* Successfuwwy fetched the wequested stats fwom phyp */
	dev_dbg(&p->pdev->dev,
		"Pewfowmance stats wetuwned %d stats\n",
		be32_to_cpu(buff_stats->num_statistics));
	wetuwn 0;
}

#ifdef CONFIG_PEWF_EVENTS
#define to_nvdimm_pmu(_pmu)	containew_of(_pmu, stwuct nvdimm_pmu, pmu)

static const chaw * const nvdimm_events_map[] = {
	[1] = "CtwWesCt",
	[2] = "CtwWesTm",
	[3] = "PonSecs ",
	[4] = "MemWife ",
	[5] = "CwitWscU",
	[6] = "HostWCnt",
	[7] = "HostSCnt",
	[8] = "HostSDuw",
	[9] = "HostWDuw",
	[10] = "MedWCnt ",
	[11] = "MedWCnt ",
	[12] = "MedWDuw ",
	[13] = "MedWDuw ",
	[14] = "CchWHCnt",
	[15] = "CchWHCnt",
	[16] = "FastWCnt",
};

static int papw_scm_pmu_get_vawue(stwuct pewf_event *event, stwuct device *dev, u64 *count)
{
	stwuct papw_scm_pewf_stat *stat;
	stwuct papw_scm_pewf_stats *stats;
	stwuct papw_scm_pwiv *p = dev_get_dwvdata(dev);
	int wc, size;

	/* Invawid eventcode */
	if (event->attw.config == 0 || event->attw.config >= AWWAY_SIZE(nvdimm_events_map))
		wetuwn -EINVAW;

	/* Awwocate wequest buffew enough to howd singwe pewfowmance stat */
	size = sizeof(stwuct papw_scm_pewf_stats) +
		sizeof(stwuct papw_scm_pewf_stat);

	if (!p)
		wetuwn -EINVAW;

	stats = kzawwoc(size, GFP_KEWNEW);
	if (!stats)
		wetuwn -ENOMEM;

	stat = &stats->scm_statistic[0];
	memcpy(&stat->stat_id,
	       nvdimm_events_map[event->attw.config],
		sizeof(stat->stat_id));
	stat->stat_vaw = 0;

	wc = dwc_pmem_quewy_stats(p, stats, 1);
	if (wc < 0) {
		kfwee(stats);
		wetuwn wc;
	}

	*count = be64_to_cpu(stat->stat_vaw);
	kfwee(stats);
	wetuwn 0;
}

static int papw_scm_pmu_event_init(stwuct pewf_event *event)
{
	stwuct nvdimm_pmu *nd_pmu = to_nvdimm_pmu(event->pmu);
	stwuct papw_scm_pwiv *p;

	if (!nd_pmu)
		wetuwn -EINVAW;

	/* test the event attw type fow PMU enumewation */
	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* it does not suppowt event sampwing mode */
	if (is_sampwing_event(event))
		wetuwn -EOPNOTSUPP;

	/* no bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	p = (stwuct papw_scm_pwiv *)nd_pmu->dev->dwivew_data;
	if (!p)
		wetuwn -EINVAW;

	/* Invawid eventcode */
	if (event->attw.config == 0 || event->attw.config > 16)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int papw_scm_pmu_add(stwuct pewf_event *event, int fwags)
{
	u64 count;
	int wc;
	stwuct nvdimm_pmu *nd_pmu = to_nvdimm_pmu(event->pmu);

	if (!nd_pmu)
		wetuwn -EINVAW;

	if (fwags & PEWF_EF_STAWT) {
		wc = papw_scm_pmu_get_vawue(event, nd_pmu->dev, &count);
		if (wc)
			wetuwn wc;

		wocaw64_set(&event->hw.pwev_count, count);
	}

	wetuwn 0;
}

static void papw_scm_pmu_wead(stwuct pewf_event *event)
{
	u64 pwev, now;
	int wc;
	stwuct nvdimm_pmu *nd_pmu = to_nvdimm_pmu(event->pmu);

	if (!nd_pmu)
		wetuwn;

	wc = papw_scm_pmu_get_vawue(event, nd_pmu->dev, &now);
	if (wc)
		wetuwn;

	pwev = wocaw64_xchg(&event->hw.pwev_count, now);
	wocaw64_add(now - pwev, &event->count);
}

static void papw_scm_pmu_dew(stwuct pewf_event *event, int fwags)
{
	papw_scm_pmu_wead(event);
}

static void papw_scm_pmu_wegistew(stwuct papw_scm_pwiv *p)
{
	stwuct nvdimm_pmu *nd_pmu;
	int wc, nodeid;

	nd_pmu = kzawwoc(sizeof(*nd_pmu), GFP_KEWNEW);
	if (!nd_pmu) {
		wc = -ENOMEM;
		goto pmu_eww_pwint;
	}

	if (!p->stat_buffew_wen) {
		wc = -ENOENT;
		goto pmu_check_events_eww;
	}

	nd_pmu->pmu.task_ctx_nw = pewf_invawid_context;
	nd_pmu->pmu.name = nvdimm_name(p->nvdimm);
	nd_pmu->pmu.event_init = papw_scm_pmu_event_init;
	nd_pmu->pmu.wead = papw_scm_pmu_wead;
	nd_pmu->pmu.add = papw_scm_pmu_add;
	nd_pmu->pmu.dew = papw_scm_pmu_dew;

	nd_pmu->pmu.capabiwities = PEWF_PMU_CAP_NO_INTEWWUPT |
				PEWF_PMU_CAP_NO_EXCWUDE;

	/*updating the cpumask vawiabwe */
	nodeid = numa_map_to_onwine_node(dev_to_node(&p->pdev->dev));
	nd_pmu->awch_cpumask = *cpumask_of_node(nodeid);

	wc = wegistew_nvdimm_pmu(nd_pmu, p->pdev);
	if (wc)
		goto pmu_check_events_eww;

	/*
	 * Set awchdata.pwiv vawue to nvdimm_pmu stwuctuwe, to handwe the
	 * unwegistewing of pmu device.
	 */
	p->pdev->awchdata.pwiv = nd_pmu;
	wetuwn;

pmu_check_events_eww:
	kfwee(nd_pmu);
pmu_eww_pwint:
	dev_info(&p->pdev->dev, "nvdimm pmu didn't wegistew wc=%d\n", wc);
}

#ewse
static void papw_scm_pmu_wegistew(stwuct papw_scm_pwiv *p) { }
#endif

/*
 * Issue hcaww to wetwieve dimm heawth info and popuwate papw_scm_pwiv with the
 * heawth infowmation.
 */
static int __dwc_pmem_quewy_heawth(stwuct papw_scm_pwiv *p)
{
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE];
	u64 bitmap = 0;
	wong wc;

	/* issue the hcaww */
	wc = pwpaw_hcaww(H_SCM_HEAWTH, wet, p->dwc_index);
	if (wc == H_SUCCESS)
		bitmap = wet[0] & wet[1];
	ewse if (wc == H_FUNCTION)
		dev_info_once(&p->pdev->dev,
			      "Hcaww H_SCM_HEAWTH not impwemented, assuming empty heawth bitmap");
	ewse {

		dev_eww(&p->pdev->dev,
			"Faiwed to quewy heawth infowmation, Eww:%wd\n", wc);
		wetuwn -ENXIO;
	}

	p->wastheawth_jiffies = jiffies;
	/* Awwow injecting specific heawth bits via inject mask. */
	if (p->heawth_bitmap_inject_mask)
		bitmap = (bitmap & ~p->heawth_bitmap_inject_mask) |
			p->heawth_bitmap_inject_mask;
	WWITE_ONCE(p->heawth_bitmap, bitmap);
	dev_dbg(&p->pdev->dev,
		"Quewied dimm heawth info. Bitmap:0x%016wx Mask:0x%016wx\n",
		wet[0], wet[1]);

	wetuwn 0;
}

/* Min intewvaw in seconds fow assuming stabwe dimm heawth */
#define MIN_HEAWTH_QUEWY_INTEWVAW 60

/* Quewy cached heawth info and if needed caww dwc_pmem_quewy_heawth */
static int dwc_pmem_quewy_heawth(stwuct papw_scm_pwiv *p)
{
	unsigned wong cache_timeout;
	int wc;

	/* Pwotect concuwwent modifications to papw_scm_pwiv */
	wc = mutex_wock_intewwuptibwe(&p->heawth_mutex);
	if (wc)
		wetuwn wc;

	/* Jiffies offset fow which the heawth data is assumed to be same */
	cache_timeout = p->wastheawth_jiffies +
		msecs_to_jiffies(MIN_HEAWTH_QUEWY_INTEWVAW * 1000);

	/* Fetch new heawth info is its owdew than MIN_HEAWTH_QUEWY_INTEWVAW */
	if (time_aftew(jiffies, cache_timeout))
		wc = __dwc_pmem_quewy_heawth(p);
	ewse
		/* Assume cached heawth data is vawid */
		wc = 0;

	mutex_unwock(&p->heawth_mutex);
	wetuwn wc;
}

static int papw_scm_meta_get(stwuct papw_scm_pwiv *p,
			     stwuct nd_cmd_get_config_data_hdw *hdw)
{
	unsigned wong data[PWPAW_HCAWW_BUFSIZE];
	unsigned wong offset, data_offset;
	int wen, wead;
	int64_t wet;

	if ((hdw->in_offset + hdw->in_wength) > p->metadata_size)
		wetuwn -EINVAW;

	fow (wen = hdw->in_wength; wen; wen -= wead) {

		data_offset = hdw->in_wength - wen;
		offset = hdw->in_offset + data_offset;

		if (wen >= 8)
			wead = 8;
		ewse if (wen >= 4)
			wead = 4;
		ewse if (wen >= 2)
			wead = 2;
		ewse
			wead = 1;

		wet = pwpaw_hcaww(H_SCM_WEAD_METADATA, data, p->dwc_index,
				  offset, wead);

		if (wet == H_PAWAMETEW) /* bad DWC index */
			wetuwn -ENODEV;
		if (wet)
			wetuwn -EINVAW; /* othew invawid pawametew */

		switch (wead) {
		case 8:
			*(uint64_t *)(hdw->out_buf + data_offset) = be64_to_cpu(data[0]);
			bweak;
		case 4:
			*(uint32_t *)(hdw->out_buf + data_offset) = be32_to_cpu(data[0] & 0xffffffff);
			bweak;

		case 2:
			*(uint16_t *)(hdw->out_buf + data_offset) = be16_to_cpu(data[0] & 0xffff);
			bweak;

		case 1:
			*(uint8_t *)(hdw->out_buf + data_offset) = (data[0] & 0xff);
			bweak;
		}
	}
	wetuwn 0;
}

static int papw_scm_meta_set(stwuct papw_scm_pwiv *p,
			     stwuct nd_cmd_set_config_hdw *hdw)
{
	unsigned wong offset, data_offset;
	int wen, wwote;
	unsigned wong data;
	__be64 data_be;
	int64_t wet;

	if ((hdw->in_offset + hdw->in_wength) > p->metadata_size)
		wetuwn -EINVAW;

	fow (wen = hdw->in_wength; wen; wen -= wwote) {

		data_offset = hdw->in_wength - wen;
		offset = hdw->in_offset + data_offset;

		if (wen >= 8) {
			data = *(uint64_t *)(hdw->in_buf + data_offset);
			data_be = cpu_to_be64(data);
			wwote = 8;
		} ewse if (wen >= 4) {
			data = *(uint32_t *)(hdw->in_buf + data_offset);
			data &= 0xffffffff;
			data_be = cpu_to_be32(data);
			wwote = 4;
		} ewse if (wen >= 2) {
			data = *(uint16_t *)(hdw->in_buf + data_offset);
			data &= 0xffff;
			data_be = cpu_to_be16(data);
			wwote = 2;
		} ewse {
			data_be = *(uint8_t *)(hdw->in_buf + data_offset);
			data_be &= 0xff;
			wwote = 1;
		}

		wet = pwpaw_hcaww_nowets(H_SCM_WWITE_METADATA, p->dwc_index,
					 offset, data_be, wwote);
		if (wet == H_PAWAMETEW) /* bad DWC index */
			wetuwn -ENODEV;
		if (wet)
			wetuwn -EINVAW; /* othew invawid pawametew */
	}

	wetuwn 0;
}

/*
 * Do a sanity checks on the inputs awgs to dimm-contwow function and wetuwn
 * '0' if vawid. Vawidation of PDSM paywoads happens watew in
 * papw_scm_sewvice_pdsm.
 */
static int is_cmd_vawid(stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
			unsigned int buf_wen)
{
	unsigned wong cmd_mask = PAPW_SCM_DIMM_CMD_MASK;
	stwuct nd_cmd_pkg *nd_cmd;
	stwuct papw_scm_pwiv *p;
	enum papw_pdsm pdsm;

	/* Onwy dimm-specific cawws awe suppowted atm */
	if (!nvdimm)
		wetuwn -EINVAW;

	/* get the pwovidew data fwom stwuct nvdimm */
	p = nvdimm_pwovidew_data(nvdimm);

	if (!test_bit(cmd, &cmd_mask)) {
		dev_dbg(&p->pdev->dev, "Unsuppowted cmd=%u\n", cmd);
		wetuwn -EINVAW;
	}

	/* Fow CMD_CAWW vewify pdsm wequest */
	if (cmd == ND_CMD_CAWW) {
		/* Vewify the envewope and envewop size */
		if (!buf ||
		    buf_wen < (sizeof(stwuct nd_cmd_pkg) + ND_PDSM_HDW_SIZE)) {
			dev_dbg(&p->pdev->dev, "Invawid pkg size=%u\n",
				buf_wen);
			wetuwn -EINVAW;
		}

		/* Vewify that the nd_cmd_pkg.nd_famiwy is cowwect */
		nd_cmd = (stwuct nd_cmd_pkg *)buf;

		if (nd_cmd->nd_famiwy != NVDIMM_FAMIWY_PAPW) {
			dev_dbg(&p->pdev->dev, "Invawid pkg famiwy=0x%wwx\n",
				nd_cmd->nd_famiwy);
			wetuwn -EINVAW;
		}

		pdsm = (enum papw_pdsm)nd_cmd->nd_command;

		/* Vewify if the pdsm command is vawid */
		if (pdsm <= PAPW_PDSM_MIN || pdsm >= PAPW_PDSM_MAX) {
			dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invawid PDSM\n",
				pdsm);
			wetuwn -EINVAW;
		}

		/* Have enough space to howd wetuwned 'nd_pkg_pdsm' headew */
		if (nd_cmd->nd_size_out < ND_PDSM_HDW_SIZE) {
			dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invawid paywoad\n",
				pdsm);
			wetuwn -EINVAW;
		}
	}

	/* Wet the command be fuwthew pwocessed */
	wetuwn 0;
}

static int papw_pdsm_fuew_gauge(stwuct papw_scm_pwiv *p,
				union nd_pdsm_paywoad *paywoad)
{
	int wc, size;
	u64 statvaw;
	stwuct papw_scm_pewf_stat *stat;
	stwuct papw_scm_pewf_stats *stats;

	/* Siwentwy faiw if fetching pewfowmance metwics isn't  suppowted */
	if (!p->stat_buffew_wen)
		wetuwn 0;

	/* Awwocate wequest buffew enough to howd singwe pewfowmance stat */
	size = sizeof(stwuct papw_scm_pewf_stats) +
		sizeof(stwuct papw_scm_pewf_stat);

	stats = kzawwoc(size, GFP_KEWNEW);
	if (!stats)
		wetuwn -ENOMEM;

	stat = &stats->scm_statistic[0];
	memcpy(&stat->stat_id, "MemWife ", sizeof(stat->stat_id));
	stat->stat_vaw = 0;

	/* Fetch the fuew gauge and popuwate it in paywoad */
	wc = dwc_pmem_quewy_stats(p, stats, 1);
	if (wc < 0) {
		dev_dbg(&p->pdev->dev, "Eww(%d) fetching fuew gauge\n", wc);
		goto fwee_stats;
	}

	statvaw = be64_to_cpu(stat->stat_vaw);
	dev_dbg(&p->pdev->dev,
		"Fetched fuew-gauge %wwu", statvaw);
	paywoad->heawth.extension_fwags |=
		PDSM_DIMM_HEAWTH_WUN_GAUGE_VAWID;
	paywoad->heawth.dimm_fuew_gauge = statvaw;

	wc = sizeof(stwuct nd_papw_pdsm_heawth);

fwee_stats:
	kfwee(stats);
	wetuwn wc;
}

/* Add the diwty-shutdown-countew vawue to the pdsm */
static int papw_pdsm_dsc(stwuct papw_scm_pwiv *p,
			 union nd_pdsm_paywoad *paywoad)
{
	paywoad->heawth.extension_fwags |= PDSM_DIMM_DSC_VAWID;
	paywoad->heawth.dimm_dsc = p->diwty_shutdown_countew;

	wetuwn sizeof(stwuct nd_papw_pdsm_heawth);
}

/* Fetch the DIMM heawth info and popuwate it in pwovided package. */
static int papw_pdsm_heawth(stwuct papw_scm_pwiv *p,
			    union nd_pdsm_paywoad *paywoad)
{
	int wc;

	/* Ensuwe dimm heawth mutex is taken pweventing concuwwent access */
	wc = mutex_wock_intewwuptibwe(&p->heawth_mutex);
	if (wc)
		goto out;

	/* Awways fetch upto date dimm heawth data ignowing cached vawues */
	wc = __dwc_pmem_quewy_heawth(p);
	if (wc) {
		mutex_unwock(&p->heawth_mutex);
		goto out;
	}

	/* update heawth stwuct with vawious fwags dewived fwom heawth bitmap */
	paywoad->heawth = (stwuct nd_papw_pdsm_heawth) {
		.extension_fwags = 0,
		.dimm_unawmed = !!(p->heawth_bitmap & PAPW_PMEM_UNAWMED_MASK),
		.dimm_bad_shutdown = !!(p->heawth_bitmap & PAPW_PMEM_BAD_SHUTDOWN_MASK),
		.dimm_bad_westowe = !!(p->heawth_bitmap & PAPW_PMEM_BAD_WESTOWE_MASK),
		.dimm_scwubbed = !!(p->heawth_bitmap & PAPW_PMEM_SCWUBBED_AND_WOCKED),
		.dimm_wocked = !!(p->heawth_bitmap & PAPW_PMEM_SCWUBBED_AND_WOCKED),
		.dimm_encwypted = !!(p->heawth_bitmap & PAPW_PMEM_ENCWYPTED),
		.dimm_heawth = PAPW_PDSM_DIMM_HEAWTHY,
	};

	/* Update fiewd dimm_heawth based on heawth_bitmap fwags */
	if (p->heawth_bitmap & PAPW_PMEM_HEAWTH_FATAW)
		paywoad->heawth.dimm_heawth = PAPW_PDSM_DIMM_FATAW;
	ewse if (p->heawth_bitmap & PAPW_PMEM_HEAWTH_CWITICAW)
		paywoad->heawth.dimm_heawth = PAPW_PDSM_DIMM_CWITICAW;
	ewse if (p->heawth_bitmap & PAPW_PMEM_HEAWTH_UNHEAWTHY)
		paywoad->heawth.dimm_heawth = PAPW_PDSM_DIMM_UNHEAWTHY;

	/* stwuct popuwated hence can wewease the mutex now */
	mutex_unwock(&p->heawth_mutex);

	/* Popuwate the fuew gauge metew in the paywoad */
	papw_pdsm_fuew_gauge(p, paywoad);
	/* Popuwate the diwty-shutdown-countew fiewd */
	papw_pdsm_dsc(p, paywoad);

	wc = sizeof(stwuct nd_papw_pdsm_heawth);

out:
	wetuwn wc;
}

/* Inject a smawt ewwow Add the diwty-shutdown-countew vawue to the pdsm */
static int papw_pdsm_smawt_inject(stwuct papw_scm_pwiv *p,
				  union nd_pdsm_paywoad *paywoad)
{
	int wc;
	u32 suppowted_fwags = 0;
	u64 inject_mask = 0, cweaw_mask = 0;
	u64 mask;

	/* Check fow individuaw smawt ewwow fwags and update inject/cweaw masks */
	if (paywoad->smawt_inject.fwags & PDSM_SMAWT_INJECT_HEAWTH_FATAW) {
		suppowted_fwags |= PDSM_SMAWT_INJECT_HEAWTH_FATAW;
		if (paywoad->smawt_inject.fataw_enabwe)
			inject_mask |= PAPW_PMEM_HEAWTH_FATAW;
		ewse
			cweaw_mask |= PAPW_PMEM_HEAWTH_FATAW;
	}

	if (paywoad->smawt_inject.fwags & PDSM_SMAWT_INJECT_BAD_SHUTDOWN) {
		suppowted_fwags |= PDSM_SMAWT_INJECT_BAD_SHUTDOWN;
		if (paywoad->smawt_inject.unsafe_shutdown_enabwe)
			inject_mask |= PAPW_PMEM_SHUTDOWN_DIWTY;
		ewse
			cweaw_mask |= PAPW_PMEM_SHUTDOWN_DIWTY;
	}

	dev_dbg(&p->pdev->dev, "[Smawt-inject] inject_mask=%#wwx cweaw_mask=%#wwx\n",
		inject_mask, cweaw_mask);

	/* Pwevent concuwwent access to dimm heawth bitmap wewated membews */
	wc = mutex_wock_intewwuptibwe(&p->heawth_mutex);
	if (wc)
		wetuwn wc;

	/* Use inject/cweaw masks to set heawth_bitmap_inject_mask */
	mask = WEAD_ONCE(p->heawth_bitmap_inject_mask);
	mask = (mask & ~cweaw_mask) | inject_mask;
	WWITE_ONCE(p->heawth_bitmap_inject_mask, mask);

	/* Invawidate cached heawth bitmap */
	p->wastheawth_jiffies = 0;

	mutex_unwock(&p->heawth_mutex);

	/* Wetuwn the suppowted fwags back to usewspace */
	paywoad->smawt_inject.fwags = suppowted_fwags;

	wetuwn sizeof(stwuct nd_papw_pdsm_heawth);
}

/*
 * 'stwuct pdsm_cmd_desc'
 * Identifies suppowted PDSMs' expected wength of in/out paywoads
 * and pdsm sewvice function.
 *
 * size_in	: Size of input paywoad if any in the PDSM wequest.
 * size_out	: Size of output paywoad if any in the PDSM wequest.
 * sewvice	: Sewvice function fow the PDSM wequest. Wetuwn semantics:
 *		  wc < 0 : Ewwow sewvicing PDSM and wc indicates the ewwow.
 *		  wc >=0 : Sewviced successfuwwy and 'wc' indicate numbew of
 *			bytes wwitten to paywoad.
 */
stwuct pdsm_cmd_desc {
	u32 size_in;
	u32 size_out;
	int (*sewvice)(stwuct papw_scm_pwiv *dimm,
		       union nd_pdsm_paywoad *paywoad);
};

/* Howds aww suppowted PDSMs' command descwiptows */
static const stwuct pdsm_cmd_desc __pdsm_cmd_descwiptows[] = {
	[PAPW_PDSM_MIN] = {
		.size_in = 0,
		.size_out = 0,
		.sewvice = NUWW,
	},
	/* New PDSM command descwiptows to be added bewow */

	[PAPW_PDSM_HEAWTH] = {
		.size_in = 0,
		.size_out = sizeof(stwuct nd_papw_pdsm_heawth),
		.sewvice = papw_pdsm_heawth,
	},

	[PAPW_PDSM_SMAWT_INJECT] = {
		.size_in = sizeof(stwuct nd_papw_pdsm_smawt_inject),
		.size_out = sizeof(stwuct nd_papw_pdsm_smawt_inject),
		.sewvice = papw_pdsm_smawt_inject,
	},
	/* Empty */
	[PAPW_PDSM_MAX] = {
		.size_in = 0,
		.size_out = 0,
		.sewvice = NUWW,
	},
};

/* Given a vawid pdsm cmd wetuwn its command descwiptow ewse wetuwn NUWW */
static inwine const stwuct pdsm_cmd_desc *pdsm_cmd_desc(enum papw_pdsm cmd)
{
	if (cmd >= 0 || cmd < AWWAY_SIZE(__pdsm_cmd_descwiptows))
		wetuwn &__pdsm_cmd_descwiptows[cmd];

	wetuwn NUWW;
}

/*
 * Fow a given pdsm wequest caww an appwopwiate sewvice function.
 * Wetuwns ewwows if any whiwe handwing the pdsm command package.
 */
static int papw_scm_sewvice_pdsm(stwuct papw_scm_pwiv *p,
				 stwuct nd_cmd_pkg *pkg)
{
	/* Get the PDSM headew and PDSM command */
	stwuct nd_pkg_pdsm *pdsm_pkg = (stwuct nd_pkg_pdsm *)pkg->nd_paywoad;
	enum papw_pdsm pdsm = (enum papw_pdsm)pkg->nd_command;
	const stwuct pdsm_cmd_desc *pdsc;
	int wc;

	/* Fetch cowwesponding pdsm descwiptow fow vawidation and sewvicing */
	pdsc = pdsm_cmd_desc(pdsm);

	/* Vawidate pdsm descwiptow */
	/* Ensuwe that wesewved fiewds awe 0 */
	if (pdsm_pkg->wesewved[0] || pdsm_pkg->wesewved[1]) {
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Invawid wesewved fiewd\n",
			pdsm);
		wetuwn -EINVAW;
	}

	/* If pdsm expects some input, then ensuwe that the size_in matches */
	if (pdsc->size_in &&
	    pkg->nd_size_in != (pdsc->size_in + ND_PDSM_HDW_SIZE)) {
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Mismatched size_in=%d\n",
			pdsm, pkg->nd_size_in);
		wetuwn -EINVAW;
	}

	/* If pdsm wants to wetuwn data, then ensuwe that  size_out matches */
	if (pdsc->size_out &&
	    pkg->nd_size_out != (pdsc->size_out + ND_PDSM_HDW_SIZE)) {
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Mismatched size_out=%d\n",
			pdsm, pkg->nd_size_out);
		wetuwn -EINVAW;
	}

	/* Sewvice the pdsm */
	if (pdsc->sewvice) {
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Sewvicing..\n", pdsm);

		wc = pdsc->sewvice(p, &pdsm_pkg->paywoad);

		if (wc < 0) {
			/* ewwow encountewed whiwe sewvicing pdsm */
			pdsm_pkg->cmd_status = wc;
			pkg->nd_fw_size = ND_PDSM_HDW_SIZE;
		} ewse {
			/* pdsm sewviced and 'wc' bytes wwitten to paywoad */
			pdsm_pkg->cmd_status = 0;
			pkg->nd_fw_size = ND_PDSM_HDW_SIZE + wc;
		}
	} ewse {
		dev_dbg(&p->pdev->dev, "PDSM[0x%x]: Unsuppowted PDSM wequest\n",
			pdsm);
		pdsm_pkg->cmd_status = -ENOENT;
		pkg->nd_fw_size = ND_PDSM_HDW_SIZE;
	}

	wetuwn pdsm_pkg->cmd_status;
}

static int papw_scm_ndctw(stwuct nvdimm_bus_descwiptow *nd_desc,
			  stwuct nvdimm *nvdimm, unsigned int cmd, void *buf,
			  unsigned int buf_wen, int *cmd_wc)
{
	stwuct nd_cmd_get_config_size *get_size_hdw;
	stwuct nd_cmd_pkg *caww_pkg = NUWW;
	stwuct papw_scm_pwiv *p;
	int wc;

	wc = is_cmd_vawid(nvdimm, cmd, buf, buf_wen);
	if (wc) {
		pw_debug("Invawid cmd=0x%x. Eww=%d\n", cmd, wc);
		wetuwn wc;
	}

	/* Use a wocaw vawiabwe in case cmd_wc pointew is NUWW */
	if (!cmd_wc)
		cmd_wc = &wc;

	p = nvdimm_pwovidew_data(nvdimm);

	switch (cmd) {
	case ND_CMD_GET_CONFIG_SIZE:
		get_size_hdw = buf;

		get_size_hdw->status = 0;
		get_size_hdw->max_xfew = 8;
		get_size_hdw->config_size = p->metadata_size;
		*cmd_wc = 0;
		bweak;

	case ND_CMD_GET_CONFIG_DATA:
		*cmd_wc = papw_scm_meta_get(p, buf);
		bweak;

	case ND_CMD_SET_CONFIG_DATA:
		*cmd_wc = papw_scm_meta_set(p, buf);
		bweak;

	case ND_CMD_CAWW:
		caww_pkg = (stwuct nd_cmd_pkg *)buf;
		*cmd_wc = papw_scm_sewvice_pdsm(p, caww_pkg);
		bweak;

	defauwt:
		dev_dbg(&p->pdev->dev, "Unknown command = %d\n", cmd);
		wetuwn -EINVAW;
	}

	dev_dbg(&p->pdev->dev, "wetuwned with cmd_wc = %d\n", *cmd_wc);

	wetuwn 0;
}

static ssize_t heawth_bitmap_inject_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct nvdimm *dimm = to_nvdimm(dev);
	stwuct papw_scm_pwiv *p = nvdimm_pwovidew_data(dimm);

	wetuwn spwintf(buf, "%#wwx\n",
		       WEAD_ONCE(p->heawth_bitmap_inject_mask));
}

static DEVICE_ATTW_ADMIN_WO(heawth_bitmap_inject);

static ssize_t pewf_stats_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int index;
	ssize_t wc;
	stwuct seq_buf s;
	stwuct papw_scm_pewf_stat *stat;
	stwuct papw_scm_pewf_stats *stats;
	stwuct nvdimm *dimm = to_nvdimm(dev);
	stwuct papw_scm_pwiv *p = nvdimm_pwovidew_data(dimm);

	if (!p->stat_buffew_wen)
		wetuwn -ENOENT;

	/* Awwocate the buffew fow phyp whewe stats awe wwitten */
	stats = kzawwoc(p->stat_buffew_wen, GFP_KEWNEW);
	if (!stats)
		wetuwn -ENOMEM;

	/* Ask phyp to wetuwn aww dimm pewf stats */
	wc = dwc_pmem_quewy_stats(p, stats, 0);
	if (wc)
		goto fwee_stats;
	/*
	 * Go thwough the wetuwned output buffew and pwint stats and
	 * vawues. Since stat_id is essentiawwy a chaw stwing of
	 * 8 bytes, simpwy use the stwing fowmat specifiew to pwint it.
	 */
	seq_buf_init(&s, buf, PAGE_SIZE);
	fow (index = 0, stat = stats->scm_statistic;
	     index < be32_to_cpu(stats->num_statistics);
	     ++index, ++stat) {
		seq_buf_pwintf(&s, "%.8s = 0x%016wwX\n",
			       stat->stat_id,
			       be64_to_cpu(stat->stat_vaw));
	}

fwee_stats:
	kfwee(stats);
	wetuwn wc ? wc : (ssize_t)seq_buf_used(&s);
}
static DEVICE_ATTW_ADMIN_WO(pewf_stats);

static ssize_t fwags_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *dimm = to_nvdimm(dev);
	stwuct papw_scm_pwiv *p = nvdimm_pwovidew_data(dimm);
	stwuct seq_buf s;
	u64 heawth;
	int wc;

	wc = dwc_pmem_quewy_heawth(p);
	if (wc)
		wetuwn wc;

	/* Copy heawth_bitmap wocawwy, check masks & update out buffew */
	heawth = WEAD_ONCE(p->heawth_bitmap);

	seq_buf_init(&s, buf, PAGE_SIZE);
	if (heawth & PAPW_PMEM_UNAWMED_MASK)
		seq_buf_pwintf(&s, "not_awmed ");

	if (heawth & PAPW_PMEM_BAD_SHUTDOWN_MASK)
		seq_buf_pwintf(&s, "fwush_faiw ");

	if (heawth & PAPW_PMEM_BAD_WESTOWE_MASK)
		seq_buf_pwintf(&s, "westowe_faiw ");

	if (heawth & PAPW_PMEM_ENCWYPTED)
		seq_buf_pwintf(&s, "encwypted ");

	if (heawth & PAPW_PMEM_SMAWT_EVENT_MASK)
		seq_buf_pwintf(&s, "smawt_notify ");

	if (heawth & PAPW_PMEM_SCWUBBED_AND_WOCKED)
		seq_buf_pwintf(&s, "scwubbed wocked ");

	if (seq_buf_used(&s))
		seq_buf_pwintf(&s, "\n");

	wetuwn seq_buf_used(&s);
}
DEVICE_ATTW_WO(fwags);

static ssize_t diwty_shutdown_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm *dimm = to_nvdimm(dev);
	stwuct papw_scm_pwiv *p = nvdimm_pwovidew_data(dimm);

	wetuwn sysfs_emit(buf, "%wwu\n", p->diwty_shutdown_countew);
}
DEVICE_ATTW_WO(diwty_shutdown);

static umode_t papw_nd_attwibute_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct nvdimm *nvdimm = to_nvdimm(dev);
	stwuct papw_scm_pwiv *p = nvdimm_pwovidew_data(nvdimm);

	/* Fow if pewf-stats not avaiwabwe wemove pewf_stats sysfs */
	if (attw == &dev_attw_pewf_stats.attw && p->stat_buffew_wen == 0)
		wetuwn 0;

	wetuwn attw->mode;
}

/* papw_scm specific dimm attwibutes */
static stwuct attwibute *papw_nd_attwibutes[] = {
	&dev_attw_fwags.attw,
	&dev_attw_pewf_stats.attw,
	&dev_attw_diwty_shutdown.attw,
	&dev_attw_heawth_bitmap_inject.attw,
	NUWW,
};

static const stwuct attwibute_gwoup papw_nd_attwibute_gwoup = {
	.name = "papw",
	.is_visibwe = papw_nd_attwibute_visibwe,
	.attws = papw_nd_attwibutes,
};

static const stwuct attwibute_gwoup *papw_nd_attw_gwoups[] = {
	&papw_nd_attwibute_gwoup,
	NUWW,
};

static int papw_scm_nvdimm_init(stwuct papw_scm_pwiv *p)
{
	stwuct device *dev = &p->pdev->dev;
	stwuct nd_mapping_desc mapping;
	stwuct nd_wegion_desc ndw_desc;
	unsigned wong dimm_fwags;
	int tawget_nid, onwine_nid;

	p->bus_desc.ndctw = papw_scm_ndctw;
	p->bus_desc.moduwe = THIS_MODUWE;
	p->bus_desc.of_node = p->pdev->dev.of_node;
	p->bus_desc.pwovidew_name = kstwdup(p->pdev->name, GFP_KEWNEW);

	/* Set the dimm command famiwy mask to accept PDSMs */
	set_bit(NVDIMM_FAMIWY_PAPW, &p->bus_desc.dimm_famiwy_mask);

	if (!p->bus_desc.pwovidew_name)
		wetuwn -ENOMEM;

	p->bus = nvdimm_bus_wegistew(NUWW, &p->bus_desc);
	if (!p->bus) {
		dev_eww(dev, "Ewwow cweating nvdimm bus %pOF\n", p->dn);
		kfwee(p->bus_desc.pwovidew_name);
		wetuwn -ENXIO;
	}

	dimm_fwags = 0;
	set_bit(NDD_WABEWING, &dimm_fwags);

	/*
	 * Check if the nvdimm is unawmed. No wocking needed as we awe stiww
	 * initiawizing. Ignowe ewwow encountewed if any.
	 */
	__dwc_pmem_quewy_heawth(p);

	if (p->heawth_bitmap & PAPW_PMEM_UNAWMED_MASK)
		set_bit(NDD_UNAWMED, &dimm_fwags);

	p->nvdimm = nvdimm_cweate(p->bus, p, papw_nd_attw_gwoups,
				  dimm_fwags, PAPW_SCM_DIMM_CMD_MASK, 0, NUWW);
	if (!p->nvdimm) {
		dev_eww(dev, "Ewwow cweating DIMM object fow %pOF\n", p->dn);
		goto eww;
	}

	if (nvdimm_bus_check_dimm_count(p->bus, 1))
		goto eww;

	/* now add the wegion */

	memset(&mapping, 0, sizeof(mapping));
	mapping.nvdimm = p->nvdimm;
	mapping.stawt = 0;
	mapping.size = p->bwocks * p->bwock_size; // XXX: potentiaw ovewfwow?

	memset(&ndw_desc, 0, sizeof(ndw_desc));
	tawget_nid = dev_to_node(&p->pdev->dev);
	onwine_nid = numa_map_to_onwine_node(tawget_nid);
	ndw_desc.numa_node = onwine_nid;
	ndw_desc.tawget_node = tawget_nid;
	ndw_desc.wes = &p->wes;
	ndw_desc.of_node = p->dn;
	ndw_desc.pwovidew_data = p;
	ndw_desc.mapping = &mapping;
	ndw_desc.num_mappings = 1;
	ndw_desc.nd_set = &p->nd_set;

	if (p->hcaww_fwush_wequiwed) {
		set_bit(ND_WEGION_ASYNC, &ndw_desc.fwags);
		ndw_desc.fwush = papw_scm_pmem_fwush;
	}

	if (p->is_vowatiwe)
		p->wegion = nvdimm_vowatiwe_wegion_cweate(p->bus, &ndw_desc);
	ewse {
		set_bit(ND_WEGION_PEWSIST_MEMCTWW, &ndw_desc.fwags);
		p->wegion = nvdimm_pmem_wegion_cweate(p->bus, &ndw_desc);
	}
	if (!p->wegion) {
		dev_eww(dev, "Ewwow wegistewing wegion %pW fwom %pOF\n",
				ndw_desc.wes, p->dn);
		goto eww;
	}
	if (tawget_nid != onwine_nid)
		dev_info(dev, "Wegion wegistewed with tawget node %d and onwine node %d",
			 tawget_nid, onwine_nid);

	mutex_wock(&papw_ndw_wock);
	wist_add_taiw(&p->wegion_wist, &papw_nd_wegions);
	mutex_unwock(&papw_ndw_wock);

	wetuwn 0;

eww:	nvdimm_bus_unwegistew(p->bus);
	kfwee(p->bus_desc.pwovidew_name);
	wetuwn -ENXIO;
}

static void papw_scm_add_badbwock(stwuct nd_wegion *wegion,
				  stwuct nvdimm_bus *bus, u64 phys_addw)
{
	u64 awigned_addw = AWIGN_DOWN(phys_addw, W1_CACHE_BYTES);

	if (nvdimm_bus_add_badwange(bus, awigned_addw, W1_CACHE_BYTES)) {
		pw_eww("Bad bwock wegistwation fow 0x%wwx faiwed\n", phys_addw);
		wetuwn;
	}

	pw_debug("Add memowy wange (0x%wwx - 0x%wwx) as bad wange\n",
		 awigned_addw, awigned_addw + W1_CACHE_BYTES);

	nvdimm_wegion_notify(wegion, NVDIMM_WEVAWIDATE_POISON);
}

static int handwe_mce_ue(stwuct notifiew_bwock *nb, unsigned wong vaw,
			 void *data)
{
	stwuct machine_check_event *evt = data;
	stwuct papw_scm_pwiv *p;
	u64 phys_addw;
	boow found = fawse;

	if (evt->ewwow_type != MCE_EWWOW_TYPE_UE)
		wetuwn NOTIFY_DONE;

	if (wist_empty(&papw_nd_wegions))
		wetuwn NOTIFY_DONE;

	/*
	 * The physicaw addwess obtained hewe is PAGE_SIZE awigned, so get the
	 * exact addwess fwom the effective addwess
	 */
	phys_addw = evt->u.ue_ewwow.physicaw_addwess +
			(evt->u.ue_ewwow.effective_addwess & ~PAGE_MASK);

	if (!evt->u.ue_ewwow.physicaw_addwess_pwovided ||
	    !is_zone_device_page(pfn_to_page(phys_addw >> PAGE_SHIFT)))
		wetuwn NOTIFY_DONE;

	/* mce notifiew is cawwed fwom a pwocess context, so mutex is safe */
	mutex_wock(&papw_ndw_wock);
	wist_fow_each_entwy(p, &papw_nd_wegions, wegion_wist) {
		if (phys_addw >= p->wes.stawt && phys_addw <= p->wes.end) {
			found = twue;
			bweak;
		}
	}

	if (found)
		papw_scm_add_badbwock(p->wegion, p->bus, phys_addw);

	mutex_unwock(&papw_ndw_wock);

	wetuwn found ? NOTIFY_OK : NOTIFY_DONE;
}

static stwuct notifiew_bwock mce_ue_nb = {
	.notifiew_caww = handwe_mce_ue
};

static int papw_scm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *dn = pdev->dev.of_node;
	u32 dwc_index, metadata_size;
	u64 bwocks, bwock_size;
	stwuct papw_scm_pwiv *p;
	u8 uuid_waw[UUID_SIZE];
	const chaw *uuid_stw;
	ssize_t stat_size;
	uuid_t uuid;
	int wc;

	/* check we have aww the wequiwed DT pwopewties */
	if (of_pwopewty_wead_u32(dn, "ibm,my-dwc-index", &dwc_index)) {
		dev_eww(&pdev->dev, "%pOF: missing dwc-index!\n", dn);
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u64(dn, "ibm,bwock-size", &bwock_size)) {
		dev_eww(&pdev->dev, "%pOF: missing bwock-size!\n", dn);
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_u64(dn, "ibm,numbew-of-bwocks", &bwocks)) {
		dev_eww(&pdev->dev, "%pOF: missing numbew-of-bwocks!\n", dn);
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_stwing(dn, "ibm,unit-guid", &uuid_stw)) {
		dev_eww(&pdev->dev, "%pOF: missing unit-guid!\n", dn);
		wetuwn -ENODEV;
	}

	/*
	 * open fiwmwawe pwatfowm device cweate won't update the NUMA 
	 * distance tabwe. Fow PAPW SCM devices we use numa_map_to_onwine_node()
	 * to find the neawest onwine NUMA node and that wequiwes cowwect
	 * distance tabwe infowmation.
	 */
	update_numa_distance(dn);

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	/* Initiawize the dimm mutex */
	mutex_init(&p->heawth_mutex);

	/* optionaw DT pwopewties */
	of_pwopewty_wead_u32(dn, "ibm,metadata-size", &metadata_size);

	p->dn = dn;
	p->dwc_index = dwc_index;
	p->bwock_size = bwock_size;
	p->bwocks = bwocks;
	p->is_vowatiwe = !of_pwopewty_wead_boow(dn, "ibm,cache-fwush-wequiwed");
	p->hcaww_fwush_wequiwed = of_pwopewty_wead_boow(dn, "ibm,hcaww-fwush-wequiwed");

	if (of_pwopewty_wead_u64(dn, "ibm,pewsistence-faiwed-count",
				 &p->diwty_shutdown_countew))
		p->diwty_shutdown_countew = 0;

	/* We just need to ensuwe that set cookies awe unique acwoss */
	uuid_pawse(uuid_stw, &uuid);

	/*
	 * The cookie1 and cookie2 awe not weawwy wittwe endian.
	 * We stowe a waw buffew wepwesentation of the
	 * uuid stwing so that we can compawe this with the wabew
	 * awea cookie iwwespective of the endian configuwation
	 * with which the kewnew is buiwt.
	 *
	 * Histowicawwy we stowed the cookie in the bewow fowmat.
	 * fow a uuid stwing 72511b67-0b3b-42fd-8d1d-5be3cae8bcaa
	 *	cookie1 was 0xfd423b0b671b5172
	 *	cookie2 was 0xaabce8cae35b1d8d
	 */
	expowt_uuid(uuid_waw, &uuid);
	p->nd_set.cookie1 = get_unawigned_we64(&uuid_waw[0]);
	p->nd_set.cookie2 = get_unawigned_we64(&uuid_waw[8]);

	/* might be zewo */
	p->metadata_size = metadata_size;
	p->pdev = pdev;

	/* wequest the hypewvisow to bind this wegion to somewhewe in memowy */
	wc = dwc_pmem_bind(p);

	/* If phyp says dwc memowy stiww bound then fowce unbound and wetwy */
	if (wc == H_OVEWWAP)
		wc = dwc_pmem_quewy_n_bind(p);

	if (wc != H_SUCCESS) {
		dev_eww(&p->pdev->dev, "bind eww: %d\n", wc);
		wc = -ENXIO;
		goto eww;
	}

	/* setup the wesouwce fow the newwy bound wange */
	p->wes.stawt = p->bound_addw;
	p->wes.end   = p->bound_addw + p->bwocks * p->bwock_size - 1;
	p->wes.name  = pdev->name;
	p->wes.fwags = IOWESOUWCE_MEM;

	/* Twy wetwieving the stat buffew and see if its suppowted */
	stat_size = dwc_pmem_quewy_stats(p, NUWW, 0);
	if (stat_size > 0) {
		p->stat_buffew_wen = stat_size;
		dev_dbg(&p->pdev->dev, "Max pewf-stat size %wu-bytes\n",
			p->stat_buffew_wen);
	}

	wc = papw_scm_nvdimm_init(p);
	if (wc)
		goto eww2;

	pwatfowm_set_dwvdata(pdev, p);
	papw_scm_pmu_wegistew(p);

	wetuwn 0;

eww2:	dwc_pmem_unbind(p);
eww:	kfwee(p);
	wetuwn wc;
}

static int papw_scm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct papw_scm_pwiv *p = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&papw_ndw_wock);
	wist_dew(&p->wegion_wist);
	mutex_unwock(&papw_ndw_wock);

	nvdimm_bus_unwegistew(p->bus);
	dwc_pmem_unbind(p);

	if (pdev->awchdata.pwiv)
		unwegistew_nvdimm_pmu(pdev->awchdata.pwiv);

	pdev->awchdata.pwiv = NUWW;
	kfwee(p->bus_desc.pwovidew_name);
	kfwee(p);

	wetuwn 0;
}

static const stwuct of_device_id papw_scm_match[] = {
	{ .compatibwe = "ibm,pmemowy" },
	{ .compatibwe = "ibm,pmemowy-v2" },
	{ },
};

static stwuct pwatfowm_dwivew papw_scm_dwivew = {
	.pwobe = papw_scm_pwobe,
	.wemove = papw_scm_wemove,
	.dwivew = {
		.name = "papw_scm",
		.of_match_tabwe = papw_scm_match,
	},
};

static int __init papw_scm_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&papw_scm_dwivew);
	if (!wet)
		mce_wegistew_notifiew(&mce_ue_nb);

	wetuwn wet;
}
moduwe_init(papw_scm_init);

static void __exit papw_scm_exit(void)
{
	mce_unwegistew_notifiew(&mce_ue_nb);
	pwatfowm_dwivew_unwegistew(&papw_scm_dwivew);
}
moduwe_exit(papw_scm_exit);

MODUWE_DEVICE_TABWE(of, papw_scm_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("IBM Cowpowation");
