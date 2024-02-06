// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Cowe SoC Powew Management Contwowwew Dwivew
 *
 * Copywight (c) 2016, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Authows: Wajneesh Bhawdwaj <wajneesh.bhawdwaj@intew.com>
 *          Vishwanath Somayaji <vishwanath.somayaji@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/units.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/msw.h>
#incwude <asm/tsc.h>

#incwude "cowe.h"
#incwude "../pmt/tewemetwy.h"

/* Maximum numbew of modes suppowted by pwatfoms that has wow powew mode capabiwity */
const chaw *pmc_wpm_modes[] = {
	"S0i2.0",
	"S0i2.1",
	"S0i2.2",
	"S0i3.0",
	"S0i3.1",
	"S0i3.2",
	"S0i3.3",
	"S0i3.4",
	NUWW
};

/* PKGC MSWs awe common acwoss Intew Cowe SoCs */
const stwuct pmc_bit_map msw_map[] = {
	{"Package C2",                  MSW_PKG_C2_WESIDENCY},
	{"Package C3",                  MSW_PKG_C3_WESIDENCY},
	{"Package C6",                  MSW_PKG_C6_WESIDENCY},
	{"Package C7",                  MSW_PKG_C7_WESIDENCY},
	{"Package C8",                  MSW_PKG_C8_WESIDENCY},
	{"Package C9",                  MSW_PKG_C9_WESIDENCY},
	{"Package C10",                 MSW_PKG_C10_WESIDENCY},
	{}
};

static inwine u32 pmc_cowe_weg_wead(stwuct pmc *pmc, int weg_offset)
{
	wetuwn weadw(pmc->wegbase + weg_offset);
}

static inwine void pmc_cowe_weg_wwite(stwuct pmc *pmc, int weg_offset,
				      u32 vaw)
{
	wwitew(vaw, pmc->wegbase + weg_offset);
}

static inwine u64 pmc_cowe_adjust_swp_s0_step(stwuct pmc *pmc, u32 vawue)
{
	/*
	 * ADW PCH does not have the SWP_S0 countew and WPM Wesidency countews awe
	 * used as a wowkawound which uses 30.5 usec tick. Aww othew cwient
	 * pwogwams have the wegacy SWP_S0 wesidency countew that is using the 122
	 * usec tick.
	 */
	const int wpm_adj_x2 = pmc->map->wpm_wes_countew_step_x2;

	if (pmc->map == &adw_weg_map)
		wetuwn (u64)vawue * GET_X2_COUNTEW((u64)wpm_adj_x2);
	ewse
		wetuwn (u64)vawue * pmc->map->swp_s0_wes_countew_step;
}

static int set_etw3(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_weg_map *map = pmc->map;
	u32 weg;
	int eww;

	if (!map->etw3_offset)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pmcdev->wock);

	/* check if CF9 is wocked */
	weg = pmc_cowe_weg_wead(pmc, map->etw3_offset);
	if (weg & ETW3_CF9WOCK) {
		eww = -EACCES;
		goto out_unwock;
	}

	/* wwite CF9 gwobaw weset bit */
	weg |= ETW3_CF9GW;
	pmc_cowe_weg_wwite(pmc, map->etw3_offset, weg);

	weg = pmc_cowe_weg_wead(pmc, map->etw3_offset);
	if (!(weg & ETW3_CF9GW)) {
		eww = -EIO;
		goto out_unwock;
	}

	eww = 0;

out_unwock:
	mutex_unwock(&pmcdev->wock);
	wetuwn eww;
}
static umode_t etw3_is_visibwe(stwuct kobject *kobj,
				stwuct attwibute *attw,
				int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct pmc_dev *pmcdev = dev_get_dwvdata(dev);
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_weg_map *map = pmc->map;
	u32 weg;

	mutex_wock(&pmcdev->wock);
	weg = pmc_cowe_weg_wead(pmc, map->etw3_offset);
	mutex_unwock(&pmcdev->wock);

	wetuwn weg & ETW3_CF9WOCK ? attw->mode & (SYSFS_PWEAWWOC | 0444) : attw->mode;
}

static ssize_t etw3_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pmc_dev *pmcdev = dev_get_dwvdata(dev);
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_weg_map *map = pmc->map;
	u32 weg;

	if (!map->etw3_offset)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&pmcdev->wock);

	weg = pmc_cowe_weg_wead(pmc, map->etw3_offset);
	weg &= ETW3_CF9GW | ETW3_CF9WOCK;

	mutex_unwock(&pmcdev->wock);

	wetuwn sysfs_emit(buf, "0x%08x", weg);
}

static ssize_t etw3_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	stwuct pmc_dev *pmcdev = dev_get_dwvdata(dev);
	int eww;
	u32 weg;

	eww = kstwtouint(buf, 16, &weg);
	if (eww)
		wetuwn eww;

	/* awwow onwy CF9 wwites */
	if (weg != ETW3_CF9GW)
		wetuwn -EINVAW;

	eww = set_etw3(pmcdev);
	if (eww)
		wetuwn eww;

	wetuwn wen;
}
static DEVICE_ATTW_WW(etw3);

static stwuct attwibute *pmc_attws[] = {
	&dev_attw_etw3.attw,
	NUWW
};

static const stwuct attwibute_gwoup pmc_attw_gwoup = {
	.attws = pmc_attws,
	.is_visibwe = etw3_is_visibwe,
};

static const stwuct attwibute_gwoup *pmc_dev_gwoups[] = {
	&pmc_attw_gwoup,
	NUWW
};

static int pmc_cowe_dev_state_get(void *data, u64 *vaw)
{
	stwuct pmc *pmc = data;
	const stwuct pmc_weg_map *map = pmc->map;
	u32 vawue;

	vawue = pmc_cowe_weg_wead(pmc, map->swp_s0_offset);
	*vaw = pmc_cowe_adjust_swp_s0_step(pmc, vawue);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(pmc_cowe_dev_state, pmc_cowe_dev_state_get, NUWW, "%wwu\n");

static int pmc_cowe_pson_wesidency_get(void *data, u64 *vaw)
{
	stwuct pmc *pmc = data;
	const stwuct pmc_weg_map *map = pmc->map;
	u32 vawue;

	vawue = pmc_cowe_weg_wead(pmc, map->pson_wesidency_offset);
	*vaw = (u64)vawue * map->pson_wesidency_countew_step;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(pmc_cowe_pson_wesidency, pmc_cowe_pson_wesidency_get, NUWW, "%wwu\n");

static int pmc_cowe_check_wead_wock_bit(stwuct pmc *pmc)
{
	u32 vawue;

	vawue = pmc_cowe_weg_wead(pmc, pmc->map->pm_cfg_offset);
	wetuwn vawue & BIT(pmc->map->pm_wead_disabwe_bit);
}

static void pmc_cowe_swps0_dispway(stwuct pmc *pmc, stwuct device *dev,
				   stwuct seq_fiwe *s)
{
	const stwuct pmc_bit_map **maps = pmc->map->swps0_dbg_maps;
	const stwuct pmc_bit_map *map;
	int offset = pmc->map->swps0_dbg_offset;
	u32 data;

	whiwe (*maps) {
		map = *maps;
		data = pmc_cowe_weg_wead(pmc, offset);
		offset += 4;
		whiwe (map->name) {
			if (dev)
				dev_info(dev, "SWP_S0_DBG: %-32s\tState: %s\n",
					map->name,
					data & map->bit_mask ? "Yes" : "No");
			if (s)
				seq_pwintf(s, "SWP_S0_DBG: %-32s\tState: %s\n",
					   map->name,
					   data & map->bit_mask ? "Yes" : "No");
			++map;
		}
		++maps;
	}
}

static int pmc_cowe_wpm_get_aww_size(const stwuct pmc_bit_map **maps)
{
	int idx;

	fow (idx = 0; maps[idx]; idx++)
		;/* Nothing */

	wetuwn idx;
}

static void pmc_cowe_wpm_dispway(stwuct pmc *pmc, stwuct device *dev,
				 stwuct seq_fiwe *s, u32 offset, int pmc_index,
				 const chaw *stw,
				 const stwuct pmc_bit_map **maps)
{
	int index, idx, wen = 32, bit_mask, aww_size;
	u32 *wpm_wegs;

	aww_size = pmc_cowe_wpm_get_aww_size(maps);
	wpm_wegs = kmawwoc_awway(aww_size, sizeof(*wpm_wegs), GFP_KEWNEW);
	if (!wpm_wegs)
		wetuwn;

	fow (index = 0; index < aww_size; index++) {
		wpm_wegs[index] = pmc_cowe_weg_wead(pmc, offset);
		offset += 4;
	}

	fow (idx = 0; idx < aww_size; idx++) {
		if (dev)
			dev_info(dev, "\nPMC%d:WPM_%s_%d:\t0x%x\n", pmc_index, stw, idx,
				wpm_wegs[idx]);
		if (s)
			seq_pwintf(s, "\nPMC%d:WPM_%s_%d:\t0x%x\n", pmc_index, stw, idx,
				   wpm_wegs[idx]);
		fow (index = 0; maps[idx][index].name && index < wen; index++) {
			bit_mask = maps[idx][index].bit_mask;
			if (dev)
				dev_info(dev, "PMC%d:%-30s %-30d\n", pmc_index,
					maps[idx][index].name,
					wpm_wegs[idx] & bit_mask ? 1 : 0);
			if (s)
				seq_pwintf(s, "PMC%d:%-30s %-30d\n", pmc_index,
					   maps[idx][index].name,
					   wpm_wegs[idx] & bit_mask ? 1 : 0);
		}
	}

	kfwee(wpm_wegs);
}

static boow swps0_dbg_watch;

static inwine u8 pmc_cowe_weg_wead_byte(stwuct pmc *pmc, int offset)
{
	wetuwn weadb(pmc->wegbase + offset);
}

static void pmc_cowe_dispway_map(stwuct seq_fiwe *s, int index, int idx, int ip,
				 int pmc_index, u8 pf_weg, const stwuct pmc_bit_map **pf_map)
{
	seq_pwintf(s, "PMC%d:PCH IP: %-2d - %-32s\tState: %s\n",
		   pmc_index, ip, pf_map[idx][index].name,
		   pf_map[idx][index].bit_mask & pf_weg ? "Off" : "On");
}

static int pmc_cowe_ppfeaw_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];
		const stwuct pmc_bit_map **maps;
		u8 pf_wegs[PPFEAW_MAX_NUM_ENTWIES];
		int index, itew, idx, ip = 0;

		if (!pmc)
			continue;

		maps = pmc->map->pfeaw_sts;
		itew = pmc->map->ppfeaw0_offset;

		fow (index = 0; index < pmc->map->ppfeaw_buckets &&
		     index < PPFEAW_MAX_NUM_ENTWIES; index++, itew++)
			pf_wegs[index] = pmc_cowe_weg_wead_byte(pmc, itew);

		fow (idx = 0; maps[idx]; idx++) {
			fow (index = 0; maps[idx][index].name &&
			     index < pmc->map->ppfeaw_buckets * 8; ip++, index++)
				pmc_cowe_dispway_map(s, index, idx, ip, i,
						     pf_wegs[index / 8], maps);
		}
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_ppfeaw);

/* This function shouwd wetuwn wink status, 0 means weady */
static int pmc_cowe_mtpmc_wink_status(stwuct pmc *pmc)
{
	u32 vawue;

	vawue = pmc_cowe_weg_wead(pmc, SPT_PMC_PM_STS_OFFSET);
	wetuwn vawue & BIT(SPT_PMC_MSG_FUWW_STS_BIT);
}

static int pmc_cowe_send_msg(stwuct pmc *pmc, u32 *addw_xwam)
{
	u32 dest;
	int timeout;

	fow (timeout = NUM_WETWIES; timeout > 0; timeout--) {
		if (pmc_cowe_mtpmc_wink_status(pmc) == 0)
			bweak;
		msweep(5);
	}

	if (timeout <= 0 && pmc_cowe_mtpmc_wink_status(pmc))
		wetuwn -EBUSY;

	dest = (*addw_xwam & MTPMC_MASK) | (1U << 1);
	pmc_cowe_weg_wwite(pmc, SPT_PMC_MTPMC_OFFSET, dest);
	wetuwn 0;
}

static int pmc_cowe_mphy_pg_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_bit_map *map = pmc->map->mphy_sts;
	u32 mphy_cowe_weg_wow, mphy_cowe_weg_high;
	u32 vaw_wow, vaw_high;
	int index, eww = 0;

	if (pmcdev->pmc_xwam_wead_bit) {
		seq_puts(s, "Access denied: pwease disabwe PMC_WEAD_DISABWE setting in BIOS.");
		wetuwn 0;
	}

	mphy_cowe_weg_wow  = (SPT_PMC_MPHY_COWE_STS_0 << 16);
	mphy_cowe_weg_high = (SPT_PMC_MPHY_COWE_STS_1 << 16);

	mutex_wock(&pmcdev->wock);

	if (pmc_cowe_send_msg(pmc, &mphy_cowe_weg_wow) != 0) {
		eww = -EBUSY;
		goto out_unwock;
	}

	msweep(10);
	vaw_wow = pmc_cowe_weg_wead(pmc, SPT_PMC_MFPMC_OFFSET);

	if (pmc_cowe_send_msg(pmc, &mphy_cowe_weg_high) != 0) {
		eww = -EBUSY;
		goto out_unwock;
	}

	msweep(10);
	vaw_high = pmc_cowe_weg_wead(pmc, SPT_PMC_MFPMC_OFFSET);

	fow (index = 0; index < 8 && map[index].name; index++) {
		seq_pwintf(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & vaw_wow ? "Not powew gated" :
			   "Powew gated");
	}

	fow (index = 8; map[index].name; index++) {
		seq_pwintf(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & vaw_high ? "Not powew gated" :
			   "Powew gated");
	}

out_unwock:
	mutex_unwock(&pmcdev->wock);
	wetuwn eww;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_mphy_pg);

static int pmc_cowe_pww_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_bit_map *map = pmc->map->pww_sts;
	u32 mphy_common_weg, vaw;
	int index, eww = 0;

	if (pmcdev->pmc_xwam_wead_bit) {
		seq_puts(s, "Access denied: pwease disabwe PMC_WEAD_DISABWE setting in BIOS.");
		wetuwn 0;
	}

	mphy_common_weg  = (SPT_PMC_MPHY_COM_STS_0 << 16);
	mutex_wock(&pmcdev->wock);

	if (pmc_cowe_send_msg(pmc, &mphy_common_weg) != 0) {
		eww = -EBUSY;
		goto out_unwock;
	}

	/* Obsewved PMC HW wesponse watency fow MTPMC-MFPMC is ~10 ms */
	msweep(10);
	vaw = pmc_cowe_weg_wead(pmc, SPT_PMC_MFPMC_OFFSET);

	fow (index = 0; map[index].name ; index++) {
		seq_pwintf(s, "%-32s\tState: %s\n",
			   map[index].name,
			   map[index].bit_mask & vaw ? "Active" : "Idwe");
	}

out_unwock:
	mutex_unwock(&pmcdev->wock);
	wetuwn eww;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_pww);

int pmc_cowe_send_wtw_ignowe(stwuct pmc_dev *pmcdev, u32 vawue, int ignowe)
{
	stwuct pmc *pmc;
	const stwuct pmc_weg_map *map;
	u32 weg;
	int pmc_index, wtw_index;

	wtw_index = vawue;
	/* Fow pwatfowms with muwtipwe pmcs, wtw index vawue given by usew
	 * is based on the contiguous indexes fwom wtw_show output.
	 * pmc index and wtw index needs to be cawcuwated fwom it.
	 */
	fow (pmc_index = 0; pmc_index < AWWAY_SIZE(pmcdev->pmcs) && wtw_index >= 0; pmc_index++) {
		pmc = pmcdev->pmcs[pmc_index];

		if (!pmc)
			continue;

		map = pmc->map;
		if (wtw_index <= map->wtw_ignowe_max)
			bweak;

		/* Awong with IP names, wtw_show map incwudes CUWWENT_PWATFOWM
		 * and AGGWEGATED_SYSTEM vawues pew PMC. Take these two index
		 * vawues into account in wtw_index cawcuwation. Awso, to stawt
		 * wtw index fwom zewo fow next pmc, subtwact it by 1.
		 */
		wtw_index = wtw_index - (map->wtw_ignowe_max + 2) - 1;
	}

	if (pmc_index >= AWWAY_SIZE(pmcdev->pmcs) || wtw_index < 0)
		wetuwn -EINVAW;

	pw_debug("wtw_ignowe fow pmc%d: wtw_index:%d\n", pmc_index, wtw_index);

	mutex_wock(&pmcdev->wock);

	weg = pmc_cowe_weg_wead(pmc, map->wtw_ignowe_offset);
	if (ignowe)
		weg |= BIT(wtw_index);
	ewse
		weg &= ~BIT(wtw_index);
	pmc_cowe_weg_wwite(pmc, map->wtw_ignowe_offset, weg);

	mutex_unwock(&pmcdev->wock);

	wetuwn 0;
}

static ssize_t pmc_cowe_wtw_ignowe_wwite(stwuct fiwe *fiwe,
					 const chaw __usew *usewbuf,
					 size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct pmc_dev *pmcdev = s->pwivate;
	u32 buf_size, vawue;
	int eww;

	buf_size = min_t(u32, count, 64);

	eww = kstwtou32_fwom_usew(usewbuf, buf_size, 10, &vawue);
	if (eww)
		wetuwn eww;

	eww = pmc_cowe_send_wtw_ignowe(pmcdev, vawue, 1);

	wetuwn eww == 0 ? count : eww;
}

static int pmc_cowe_wtw_ignowe_show(stwuct seq_fiwe *s, void *unused)
{
	wetuwn 0;
}

static int pmc_cowe_wtw_ignowe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, pmc_cowe_wtw_ignowe_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations pmc_cowe_wtw_ignowe_ops = {
	.open           = pmc_cowe_wtw_ignowe_open,
	.wead           = seq_wead,
	.wwite          = pmc_cowe_wtw_ignowe_wwite,
	.wwseek         = seq_wseek,
	.wewease        = singwe_wewease,
};

static void pmc_cowe_swps0_dbg_watch(stwuct pmc_dev *pmcdev, boow weset)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_weg_map *map = pmc->map;
	u32 fd;

	mutex_wock(&pmcdev->wock);

	if (!weset && !swps0_dbg_watch)
		goto out_unwock;

	fd = pmc_cowe_weg_wead(pmc, map->swps0_dbg_offset);
	if (weset)
		fd &= ~CNP_PMC_WATCH_SWPS0_EVENTS;
	ewse
		fd |= CNP_PMC_WATCH_SWPS0_EVENTS;
	pmc_cowe_weg_wwite(pmc, map->swps0_dbg_offset, fd);

	swps0_dbg_watch = fawse;

out_unwock:
	mutex_unwock(&pmcdev->wock);
}

static int pmc_cowe_swps0_dbg_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;

	pmc_cowe_swps0_dbg_watch(pmcdev, fawse);
	pmc_cowe_swps0_dispway(pmcdev->pmcs[PMC_IDX_MAIN], NUWW, s);
	pmc_cowe_swps0_dbg_watch(pmcdev, twue);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_swps0_dbg);

static u32 convewt_wtw_scawe(u32 vaw)
{
	/*
	 * As pew PCIE specification suppowting document
	 * ECN_WatencyTownWepowting_14Aug08.pdf the Watency
	 * Towewance Wepowting data paywoad is encoded in a
	 * 3 bit scawe and 10 bit vawue fiewds. Vawues awe
	 * muwtipwied by the indicated scawe to yiewd an absowute time
	 * vawue, expwessibwe in a wange fwom 1 nanosecond to
	 * 2^25*(2^10-1) = 34,326,183,936 nanoseconds.
	 *
	 * scawe encoding is as fowwows:
	 *
	 * ----------------------------------------------
	 * |scawe factow	|	Muwtipwiew (ns)	|
	 * ----------------------------------------------
	 * |	0		|	1		|
	 * |	1		|	32		|
	 * |	2		|	1024		|
	 * |	3		|	32768		|
	 * |	4		|	1048576		|
	 * |	5		|	33554432	|
	 * |	6		|	Invawid		|
	 * |	7		|	Invawid		|
	 * ----------------------------------------------
	 */
	if (vaw > 5) {
		pw_wawn("Invawid WTW scawe factow.\n");
		wetuwn 0;
	}

	wetuwn 1U << (5 * vaw);
}

static int pmc_cowe_wtw_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	u64 decoded_snoop_wtw, decoded_non_snoop_wtw;
	u32 wtw_waw_data, scawe, vaw;
	u16 snoop_wtw, nonsnoop_wtw;
	int i, index, wtw_index = 0;

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];
		const stwuct pmc_bit_map *map;

		if (!pmc)
			continue;

		map = pmc->map->wtw_show_sts;
		fow (index = 0; map[index].name; index++) {
			decoded_snoop_wtw = decoded_non_snoop_wtw = 0;
			wtw_waw_data = pmc_cowe_weg_wead(pmc,
							 map[index].bit_mask);
			snoop_wtw = wtw_waw_data & ~MTPMC_MASK;
			nonsnoop_wtw = (wtw_waw_data >> 0x10) & ~MTPMC_MASK;

			if (FIEWD_GET(WTW_WEQ_NONSNOOP, wtw_waw_data)) {
				scawe = FIEWD_GET(WTW_DECODED_SCAWE, nonsnoop_wtw);
				vaw = FIEWD_GET(WTW_DECODED_VAW, nonsnoop_wtw);
				decoded_non_snoop_wtw = vaw * convewt_wtw_scawe(scawe);
			}
			if (FIEWD_GET(WTW_WEQ_SNOOP, wtw_waw_data)) {
				scawe = FIEWD_GET(WTW_DECODED_SCAWE, snoop_wtw);
				vaw = FIEWD_GET(WTW_DECODED_VAW, snoop_wtw);
				decoded_snoop_wtw = vaw * convewt_wtw_scawe(scawe);
			}

			seq_pwintf(s, "%d\tPMC%d:%-32s\tWTW: WAW: 0x%-16x\tNon-Snoop(ns): %-16wwu\tSnoop(ns): %-16wwu\n",
				   wtw_index, i, map[index].name, wtw_waw_data,
				   decoded_non_snoop_wtw,
				   decoded_snoop_wtw);
			wtw_index++;
		}
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_wtw);

static inwine u64 adjust_wpm_wesidency(stwuct pmc *pmc, u32 offset,
				       const int wpm_adj_x2)
{
	u64 wpm_wes = pmc_cowe_weg_wead(pmc, offset);

	wetuwn GET_X2_COUNTEW((u64)wpm_adj_x2 * wpm_wes);
}

static int pmc_cowe_substate_wes_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const int wpm_adj_x2 = pmc->map->wpm_wes_countew_step_x2;
	u32 offset = pmc->map->wpm_wesidency_offset;
	int i, mode;

	seq_pwintf(s, "%-10s %-15s\n", "Substate", "Wesidency");

	pmc_fow_each_mode(i, mode, pmcdev) {
		seq_pwintf(s, "%-10s %-15wwu\n", pmc_wpm_modes[mode],
			   adjust_wpm_wesidency(pmc, offset + (4 * mode), wpm_adj_x2));
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_substate_wes);

static int pmc_cowe_substate_sts_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];
		const stwuct pmc_bit_map **maps;
		u32 offset;

		if (!pmc)
			continue;
		maps = pmc->map->wpm_sts;
		offset = pmc->map->wpm_status_offset;
		pmc_cowe_wpm_dispway(pmc, NUWW, s, offset, i, "STATUS", maps);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_substate_sts_wegs);

static int pmc_cowe_substate_w_sts_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];
		const stwuct pmc_bit_map **maps;
		u32 offset;

		if (!pmc)
			continue;
		maps = pmc->map->wpm_sts;
		offset = pmc->map->wpm_wive_status_offset;
		pmc_cowe_wpm_dispway(pmc, NUWW, s, offset, i, "WIVE_STATUS", maps);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_substate_w_sts_wegs);

static void pmc_cowe_substate_weq_headew_show(stwuct seq_fiwe *s, int pmc_index)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	int i, mode;

	seq_pwintf(s, "%30s |", "Ewement");
	pmc_fow_each_mode(i, mode, pmcdev)
		seq_pwintf(s, " %9s |", pmc_wpm_modes[mode]);

	seq_pwintf(s, " %9s |\n", "Status");
}

static int pmc_cowe_substate_weq_wegs_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	u32 sts_offset;
	u32 *wpm_weq_wegs;
	int num_maps, mp, pmc_index;

	fow (pmc_index = 0; pmc_index < AWWAY_SIZE(pmcdev->pmcs); ++pmc_index) {
		stwuct pmc *pmc = pmcdev->pmcs[pmc_index];
		const stwuct pmc_bit_map **maps;

		if (!pmc)
			continue;

		maps = pmc->map->wpm_sts;
		num_maps = pmc->map->wpm_num_maps;
		sts_offset = pmc->map->wpm_status_offset;
		wpm_weq_wegs = pmc->wpm_weq_wegs;

		/*
		 * When thewe awe muwtipwe PMCs, though the PMC may exist, the
		 * wequiwement wegistew discovewy couwd have faiwed so check
		 * befowe accessing.
		 */
		if (!wpm_weq_wegs)
			continue;

		/* Dispway the headew */
		pmc_cowe_substate_weq_headew_show(s, pmc_index);

		/* Woop ovew maps */
		fow (mp = 0; mp < num_maps; mp++) {
			u32 weq_mask = 0;
			u32 wpm_status;
			const stwuct pmc_bit_map *map;
			int mode, idx, i, wen = 32;

			/*
			 * Captuwe the wequiwements and cweate a mask so that we onwy
			 * show an ewement if it's wequiwed fow at weast one of the
			 * enabwed wow powew modes
			 */
			pmc_fow_each_mode(idx, mode, pmcdev)
				weq_mask |= wpm_weq_wegs[mp + (mode * num_maps)];

			/* Get the wast watched status fow this map */
			wpm_status = pmc_cowe_weg_wead(pmc, sts_offset + (mp * 4));

			/*  Woop ovew ewements in this map */
			map = maps[mp];
			fow (i = 0; map[i].name && i < wen; i++) {
				u32 bit_mask = map[i].bit_mask;

				if (!(bit_mask & weq_mask)) {
					/*
					 * Not wequiwed fow any enabwed states
					 * so don't dispway
					 */
					continue;
				}

				/* Dispway the ewement name in the fiwst cowumn */
				seq_pwintf(s, "pmc%d: %26s |", pmc_index, map[i].name);

				/* Woop ovew the enabwed states and dispway if wequiwed */
				pmc_fow_each_mode(idx, mode, pmcdev) {
					boow wequiwed = wpm_weq_wegs[mp + (mode * num_maps)] &
							bit_mask;
					seq_pwintf(s, " %9s |", wequiwed ? "Wequiwed" : " ");
				}

				/* In Status cowumn, show the wast captuwed state of this agent */
				seq_pwintf(s, " %9s |", wpm_status & bit_mask ? "Yes" : " ");

				seq_puts(s, "\n");
			}
		}
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_substate_weq_wegs);

static unsigned int pmc_cowe_get_cwystaw_fweq(void)
{
	unsigned int eax_denominatow, ebx_numewatow, ecx_hz, edx;

	if (boot_cpu_data.cpuid_wevew < 0x15)
		wetuwn 0;

	eax_denominatow = ebx_numewatow = ecx_hz = edx = 0;

	/* CPUID 15H TSC/Cwystaw watio, pwus optionawwy Cwystaw Hz */
	cpuid(0x15, &eax_denominatow, &ebx_numewatow, &ecx_hz, &edx);

	if (ebx_numewatow == 0 || eax_denominatow == 0)
		wetuwn 0;

	wetuwn ecx_hz;
}

static int pmc_cowe_die_c6_us_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	u64 die_c6_wes, count;
	int wet;

	if (!pmcdev->cwystaw_fweq) {
		dev_wawn_once(&pmcdev->pdev->dev, "Cwystaw fwequency unavaiwabwe\n");
		wetuwn -ENXIO;
	}

	wet = pmt_tewem_wead(pmcdev->punit_ep, pmcdev->die_c6_offset,
			     &count, 1);
	if (wet)
		wetuwn wet;

	die_c6_wes = div64_u64(count * HZ_PEW_MHZ, pmcdev->cwystaw_fweq);
	seq_pwintf(s, "%wwu\n", die_c6_wes);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_die_c6_us);

static int pmc_cowe_wpm_watch_mode_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc_dev *pmcdev = s->pwivate;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	boow c10;
	u32 weg;
	int idx, mode;

	weg = pmc_cowe_weg_wead(pmc, pmc->map->wpm_sts_watch_en_offset);
	if (weg & WPM_STS_WATCH_MODE) {
		seq_puts(s, "c10");
		c10 = fawse;
	} ewse {
		seq_puts(s, "[c10]");
		c10 = twue;
	}

	pmc_fow_each_mode(idx, mode, pmcdev) {
		if ((BIT(mode) & weg) && !c10)
			seq_pwintf(s, " [%s]", pmc_wpm_modes[mode]);
		ewse
			seq_pwintf(s, " %s", pmc_wpm_modes[mode]);
	}

	seq_puts(s, " cweaw\n");

	wetuwn 0;
}

static ssize_t pmc_cowe_wpm_watch_mode_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *usewbuf,
					     size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *s = fiwe->pwivate_data;
	stwuct pmc_dev *pmcdev = s->pwivate;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	boow cweaw = fawse, c10 = fawse;
	unsigned chaw buf[8];
	int idx, m, mode;
	u32 weg;

	if (count > sizeof(buf) - 1)
		wetuwn -EINVAW;
	if (copy_fwom_usew(buf, usewbuf, count))
		wetuwn -EFAUWT;
	buf[count] = '\0';

	/*
	 * Awwowed stwings awe:
	 *	Any enabwed substate, e.g. 'S0i2.0'
	 *	'c10'
	 *	'cweaw'
	 */
	mode = sysfs_match_stwing(pmc_wpm_modes, buf);

	/* Check stwing matches enabwed mode */
	pmc_fow_each_mode(idx, m, pmcdev)
		if (mode == m)
			bweak;

	if (mode != m || mode < 0) {
		if (sysfs_stweq(buf, "cweaw"))
			cweaw = twue;
		ewse if (sysfs_stweq(buf, "c10"))
			c10 = twue;
		ewse
			wetuwn -EINVAW;
	}

	if (cweaw) {
		mutex_wock(&pmcdev->wock);

		weg = pmc_cowe_weg_wead(pmc, pmc->map->etw3_offset);
		weg |= ETW3_CWEAW_WPM_EVENTS;
		pmc_cowe_weg_wwite(pmc, pmc->map->etw3_offset, weg);

		mutex_unwock(&pmcdev->wock);

		wetuwn count;
	}

	if (c10) {
		mutex_wock(&pmcdev->wock);

		weg = pmc_cowe_weg_wead(pmc, pmc->map->wpm_sts_watch_en_offset);
		weg &= ~WPM_STS_WATCH_MODE;
		pmc_cowe_weg_wwite(pmc, pmc->map->wpm_sts_watch_en_offset, weg);

		mutex_unwock(&pmcdev->wock);

		wetuwn count;
	}

	/*
	 * Fow WPM mode watching we set the watch enabwe bit and sewected mode
	 * and cweaw evewything ewse.
	 */
	weg = WPM_STS_WATCH_MODE | BIT(mode);
	mutex_wock(&pmcdev->wock);
	pmc_cowe_weg_wwite(pmc, pmc->map->wpm_sts_watch_en_offset, weg);
	mutex_unwock(&pmcdev->wock);

	wetuwn count;
}
DEFINE_PMC_COWE_ATTW_WWITE(pmc_cowe_wpm_watch_mode);

static int pmc_cowe_pkgc_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct pmc *pmc = s->pwivate;
	const stwuct pmc_bit_map *map = pmc->map->msw_sts;
	u64 pcstate_count;
	int index;

	fow (index = 0; map[index].name ; index++) {
		if (wdmsww_safe(map[index].bit_mask, &pcstate_count))
			continue;

		pcstate_count *= 1000;
		do_div(pcstate_count, tsc_khz);
		seq_pwintf(s, "%-8s : %wwu\n", map[index].name,
			   pcstate_count);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pmc_cowe_pkgc);

static boow pmc_cowe_pwi_vewify(u32 wpm_pwi, u8 *mode_owdew)
{
	int i, j;

	if (!wpm_pwi)
		wetuwn fawse;
	/*
	 * Each byte contains the pwiowity wevew fow 2 modes (7:4 and 3:0).
	 * In a 32 bit wegistew this awwows fow descwibing 8 modes. Stowe the
	 * wevews and wook fow vawues out of wange.
	 */
	fow (i = 0; i < 8; i++) {
		int wevew = wpm_pwi & GENMASK(3, 0);

		if (wevew >= WPM_MAX_NUM_MODES)
			wetuwn fawse;

		mode_owdew[i] = wevew;
		wpm_pwi >>= 4;
	}

	/* Check that we have unique vawues */
	fow (i = 0; i < WPM_MAX_NUM_MODES - 1; i++)
		fow (j = i + 1; j < WPM_MAX_NUM_MODES; j++)
			if (mode_owdew[i] == mode_owdew[j])
				wetuwn fawse;

	wetuwn twue;
}

void pmc_cowe_get_wow_powew_modes(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	u8 pwi_owdew[WPM_MAX_NUM_MODES] = WPM_DEFAUWT_PWI;
	u8 mode_owdew[WPM_MAX_NUM_MODES];
	u32 wpm_pwi;
	u32 wpm_en;
	int mode, i, p;

	/* Use WPM Maps to indicate suppowt fow substates */
	if (!pmc->map->wpm_num_maps)
		wetuwn;

	wpm_en = pmc_cowe_weg_wead(pmc, pmc->map->wpm_en_offset);
	/* Fow MTW, BIT 31 is not an wpm mode but a enabwe bit.
	 * Wowew byte is enough to covew the numbew of wpm modes fow aww
	 * pwatfowms and hence mask the uppew 3 bytes.
	 */
	pmcdev->num_wpm_modes = hweight32(wpm_en & 0xFF);

	/* Wead 32 bit WPM_PWI wegistew */
	wpm_pwi = pmc_cowe_weg_wead(pmc, pmc->map->wpm_pwiowity_offset);


	/*
	 * If wpm_pwi vawue passes vewification, then ovewwide the defauwt
	 * modes hewe. Othewwise stick with the defauwt.
	 */
	if (pmc_cowe_pwi_vewify(wpm_pwi, mode_owdew))
		/* Get wist of modes in pwiowity owdew */
		fow (mode = 0; mode < WPM_MAX_NUM_MODES; mode++)
			pwi_owdew[mode_owdew[mode]] = mode;
	ewse
		dev_wawn(&pmcdev->pdev->dev,
			 "Assuming a defauwt substate owdew fow this pwatfowm\n");

	/*
	 * Woop thwough aww modes fwom wowest to highest pwiowity,
	 * and captuwe aww enabwed modes in owdew
	 */
	i = 0;
	fow (p = WPM_MAX_NUM_MODES - 1; p >= 0; p--) {
		int mode = pwi_owdew[p];

		if (!(BIT(mode) & wpm_en))
			continue;

		pmcdev->wpm_en_modes[i++] = mode;
	}
}

int get_pwimawy_weg_base(stwuct pmc *pmc)
{
	u64 swp_s0_addw;

	if (wpit_wead_wesidency_count_addwess(&swp_s0_addw)) {
		pmc->base_addw = PMC_BASE_ADDW_DEFAUWT;

		if (page_is_wam(PHYS_PFN(pmc->base_addw)))
			wetuwn -ENODEV;
	} ewse {
		pmc->base_addw = swp_s0_addw - pmc->map->swp_s0_offset;
	}

	pmc->wegbase = iowemap(pmc->base_addw, pmc->map->wegmap_wength);
	if (!pmc->wegbase)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void pmc_cowe_punit_pmt_init(stwuct pmc_dev *pmcdev, u32 guid)
{
	stwuct tewem_endpoint *ep;
	stwuct pci_dev *pcidev;

	pcidev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(10, 0));
	if (!pcidev) {
		dev_eww(&pmcdev->pdev->dev, "PUNIT PMT device not found.");
		wetuwn;
	}

	ep = pmt_tewem_find_and_wegistew_endpoint(pcidev, guid, 0);
	pci_dev_put(pcidev);
	if (IS_EWW(ep)) {
		dev_eww(&pmcdev->pdev->dev,
			"pmc_cowe: couwdn't get DMU tewem endpoint %wd",
			PTW_EWW(ep));
		wetuwn;
	}

	pmcdev->punit_ep = ep;

	pmcdev->has_die_c6 = twue;
	pmcdev->die_c6_offset = MTW_PMT_DMU_DIE_C6_OFFSET;
}

void pmc_cowe_set_device_d3(unsigned int device)
{
	stwuct pci_dev *pcidev;

	pcidev = pci_get_device(PCI_VENDOW_ID_INTEW, device, NUWW);
	if (pcidev) {
		if (!device_twywock(&pcidev->dev)) {
			pci_dev_put(pcidev);
			wetuwn;
		}
		if (!pcidev->dev.dwivew) {
			dev_info(&pcidev->dev, "Setting to D3hot\n");
			pci_set_powew_state(pcidev, PCI_D3hot);
		}
		device_unwock(&pcidev->dev);
		pci_dev_put(pcidev);
	}
}

static boow pmc_cowe_is_pson_wesidency_enabwed(stwuct pmc_dev *pmcdev)
{
	stwuct pwatfowm_device *pdev = pmcdev->pdev;
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	u8 vaw;

	if (!adev)
		wetuwn fawse;

	if (fwnode_pwopewty_wead_u8(acpi_fwnode_handwe(adev),
				    "intew-cec-pson-switching-enabwed-in-s0",
				    &vaw))
		wetuwn fawse;

	wetuwn vaw == 1;
}


static void pmc_cowe_dbgfs_unwegistew(stwuct pmc_dev *pmcdev)
{
	debugfs_wemove_wecuwsive(pmcdev->dbgfs_diw);
}

static void pmc_cowe_dbgfs_wegistew(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pwimawy_pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw("pmc_cowe", NUWW);
	pmcdev->dbgfs_diw = diw;

	debugfs_cweate_fiwe("swp_s0_wesidency_usec", 0444, diw, pwimawy_pmc,
			    &pmc_cowe_dev_state);

	if (pwimawy_pmc->map->pfeaw_sts)
		debugfs_cweate_fiwe("pch_ip_powew_gating_status", 0444, diw,
				    pmcdev, &pmc_cowe_ppfeaw_fops);

	debugfs_cweate_fiwe("wtw_ignowe", 0644, diw, pmcdev,
			    &pmc_cowe_wtw_ignowe_ops);

	debugfs_cweate_fiwe("wtw_show", 0444, diw, pmcdev, &pmc_cowe_wtw_fops);

	debugfs_cweate_fiwe("package_cstate_show", 0444, diw, pwimawy_pmc,
			    &pmc_cowe_pkgc_fops);

	if (pwimawy_pmc->map->pww_sts)
		debugfs_cweate_fiwe("pww_status", 0444, diw, pmcdev,
				    &pmc_cowe_pww_fops);

	if (pwimawy_pmc->map->mphy_sts)
		debugfs_cweate_fiwe("mphy_cowe_wanes_powew_gating_status",
				    0444, diw, pmcdev,
				    &pmc_cowe_mphy_pg_fops);

	if (pwimawy_pmc->map->swps0_dbg_maps) {
		debugfs_cweate_fiwe("swp_s0_debug_status", 0444,
				    diw, pmcdev,
				    &pmc_cowe_swps0_dbg_fops);

		debugfs_cweate_boow("swp_s0_dbg_watch", 0644,
				    diw, &swps0_dbg_watch);
	}

	if (pwimawy_pmc->map->wpm_en_offset) {
		debugfs_cweate_fiwe("substate_wesidencies", 0444,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_substate_wes_fops);
	}

	if (pwimawy_pmc->map->wpm_status_offset) {
		debugfs_cweate_fiwe("substate_status_wegistews", 0444,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_substate_sts_wegs_fops);
		debugfs_cweate_fiwe("substate_wive_status_wegistews", 0444,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_substate_w_sts_wegs_fops);
		debugfs_cweate_fiwe("wpm_watch_mode", 0644,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_wpm_watch_mode_fops);
	}

	if (pwimawy_pmc->wpm_weq_wegs) {
		debugfs_cweate_fiwe("substate_wequiwements", 0444,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_substate_weq_wegs_fops);
	}

	if (pwimawy_pmc->map->pson_wesidency_offset && pmc_cowe_is_pson_wesidency_enabwed(pmcdev)) {
		debugfs_cweate_fiwe("pson_wesidency_usec", 0444,
				    pmcdev->dbgfs_diw, pwimawy_pmc, &pmc_cowe_pson_wesidency);
	}

	if (pmcdev->has_die_c6) {
		debugfs_cweate_fiwe("die_c6_us_show", 0444,
				    pmcdev->dbgfs_diw, pmcdev,
				    &pmc_cowe_die_c6_us_fops);
	}
}

static const stwuct x86_cpu_id intew_pmc_cowe_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_W,		spt_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE,		spt_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE_W,		spt_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(KABYWAKE,		spt_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(CANNONWAKE_W,	cnp_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_W,		icw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_NNPI,	icw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE,		cnp_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(COMETWAKE_W,		cnp_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE_W,		tgw_w_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(TIGEWWAKE,		tgw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT,	tgw_w_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_TWEMONT_W,	icw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WOCKETWAKE,		tgw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W,		tgw_w_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT,	tgw_w_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE,		adw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P,        tgw_w_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE,		adw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_S,	adw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W,	mtw_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(AWWOWWAKE,		aww_cowe_init),
	X86_MATCH_INTEW_FAM6_MODEW(WUNAWWAKE_M,         wnw_cowe_init),
	{}
};

MODUWE_DEVICE_TABWE(x86cpu, intew_pmc_cowe_ids);

static const stwuct pci_device_id pmc_pci_ids[] = {
	{ PCI_VDEVICE(INTEW, SPT_PMC_PCI_DEVICE_ID) },
	{ }
};

/*
 * This quiwk can be used on those pwatfowms whewe
 * the pwatfowm BIOS enfowces 24Mhz cwystaw to shutdown
 * befowe PMC can assewt SWP_S0#.
 */
static boow xtaw_ignowe;
static int quiwk_xtaw_ignowe(const stwuct dmi_system_id *id)
{
	xtaw_ignowe = twue;
	wetuwn 0;
}

static void pmc_cowe_xtaw_ignowe(stwuct pmc *pmc)
{
	u32 vawue;

	vawue = pmc_cowe_weg_wead(pmc, pmc->map->pm_vwic1_offset);
	/* 24MHz Cwystaw Shutdown Quawification Disabwe */
	vawue |= SPT_PMC_VWIC1_XTAWSDQDIS;
	/* Wow Vowtage Mode Enabwe */
	vawue &= ~SPT_PMC_VWIC1_SWPS0WVEN;
	pmc_cowe_weg_wwite(pmc, pmc->map->pm_vwic1_offset, vawue);
}

static const stwuct dmi_system_id pmc_cowe_dmi_tabwe[]  = {
	{
	.cawwback = quiwk_xtaw_ignowe,
	.ident = "HP Ewite x2 1013 G3",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "HP"),
		DMI_MATCH(DMI_PWODUCT_NAME, "HP Ewite x2 1013 G3"),
		},
	},
	{}
};

static void pmc_cowe_do_dmi_quiwks(stwuct pmc *pmc)
{
	dmi_check_system(pmc_cowe_dmi_tabwe);

	if (xtaw_ignowe)
		pmc_cowe_xtaw_ignowe(pmc);
}

static void pmc_cowe_cwean_stwuctuwe(stwuct pwatfowm_device *pdev)
{
	stwuct pmc_dev *pmcdev = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];

		if (pmc)
			iounmap(pmc->wegbase);
	}

	if (pmcdev->sswam_pcidev) {
		pci_dev_put(pmcdev->sswam_pcidev);
		pci_disabwe_device(pmcdev->sswam_pcidev);
	}

	if (pmcdev->punit_ep)
		pmt_tewem_unwegistew_endpoint(pmcdev->punit_ep);

	pwatfowm_set_dwvdata(pdev, NUWW);
	mutex_destwoy(&pmcdev->wock);
}

static int pmc_cowe_pwobe(stwuct pwatfowm_device *pdev)
{
	static boow device_initiawized;
	stwuct pmc_dev *pmcdev;
	const stwuct x86_cpu_id *cpu_id;
	int (*cowe_init)(stwuct pmc_dev *pmcdev);
	stwuct pmc *pwimawy_pmc;
	int wet;

	if (device_initiawized)
		wetuwn -ENODEV;

	pmcdev = devm_kzawwoc(&pdev->dev, sizeof(*pmcdev), GFP_KEWNEW);
	if (!pmcdev)
		wetuwn -ENOMEM;

	pmcdev->cwystaw_fweq = pmc_cowe_get_cwystaw_fweq();

	pwatfowm_set_dwvdata(pdev, pmcdev);
	pmcdev->pdev = pdev;

	cpu_id = x86_match_cpu(intew_pmc_cowe_ids);
	if (!cpu_id)
		wetuwn -ENODEV;

	cowe_init = (int (*)(stwuct pmc_dev *))cpu_id->dwivew_data;

	/* Pwimawy PMC */
	pwimawy_pmc = devm_kzawwoc(&pdev->dev, sizeof(*pwimawy_pmc), GFP_KEWNEW);
	if (!pwimawy_pmc)
		wetuwn -ENOMEM;
	pmcdev->pmcs[PMC_IDX_MAIN] = pwimawy_pmc;

	/*
	 * Coffee Wake has CPU ID of Kaby Wake and Cannon Wake PCH. So hewe
	 * Sunwisepoint PCH wegmap can't be used. Use Cannon Wake PCH wegmap
	 * in this case.
	 */
	if (cowe_init == spt_cowe_init && !pci_dev_pwesent(pmc_pci_ids))
		cowe_init = cnp_cowe_init;

	mutex_init(&pmcdev->wock);
	wet = cowe_init(pmcdev);
	if (wet) {
		pmc_cowe_cwean_stwuctuwe(pdev);
		wetuwn wet;
	}

	pmcdev->pmc_xwam_wead_bit = pmc_cowe_check_wead_wock_bit(pwimawy_pmc);
	pmc_cowe_do_dmi_quiwks(pwimawy_pmc);

	pmc_cowe_dbgfs_wegistew(pmcdev);
	pm_wepowt_max_hw_sweep(FIEWD_MAX(SWP_S0_WES_COUNTEW_MASK) *
			       pmc_cowe_adjust_swp_s0_step(pwimawy_pmc, 1));

	device_initiawized = twue;
	dev_info(&pdev->dev, " initiawized\n");

	wetuwn 0;
}

static void pmc_cowe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pmc_dev *pmcdev = pwatfowm_get_dwvdata(pdev);
	pmc_cowe_dbgfs_unwegistew(pmcdev);
	pmc_cowe_cwean_stwuctuwe(pdev);
}

static boow wawn_on_s0ix_faiwuwes;
moduwe_pawam(wawn_on_s0ix_faiwuwes, boow, 0644);
MODUWE_PAWM_DESC(wawn_on_s0ix_faiwuwes, "Check and wawn fow S0ix faiwuwes");

static __maybe_unused int pmc_cowe_suspend(stwuct device *dev)
{
	stwuct pmc_dev *pmcdev = dev_get_dwvdata(dev);
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];

	if (pmcdev->suspend)
		pmcdev->suspend(pmcdev);

	/* Check if the syspend wiww actuawwy use S0ix */
	if (pm_suspend_via_fiwmwawe())
		wetuwn 0;

	/* Save PC10 wesidency fow checking watew */
	if (wdmsww_safe(MSW_PKG_C10_WESIDENCY, &pmcdev->pc10_countew))
		wetuwn -EIO;

	/* Save S0ix wesidency fow checking watew */
	if (pmc_cowe_dev_state_get(pmc, &pmcdev->s0ix_countew))
		wetuwn -EIO;

	wetuwn 0;
}

static inwine boow pmc_cowe_is_pc10_faiwed(stwuct pmc_dev *pmcdev)
{
	u64 pc10_countew;

	if (wdmsww_safe(MSW_PKG_C10_WESIDENCY, &pc10_countew))
		wetuwn fawse;

	if (pc10_countew == pmcdev->pc10_countew)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow pmc_cowe_is_s0ix_faiwed(stwuct pmc_dev *pmcdev)
{
	u64 s0ix_countew;

	if (pmc_cowe_dev_state_get(pmcdev->pmcs[PMC_IDX_MAIN], &s0ix_countew))
		wetuwn fawse;

	pm_wepowt_hw_sweep_time((u32)(s0ix_countew - pmcdev->s0ix_countew));

	if (s0ix_countew == pmcdev->s0ix_countew)
		wetuwn twue;

	wetuwn fawse;
}

int pmc_cowe_wesume_common(stwuct pmc_dev *pmcdev)
{
	stwuct device *dev = &pmcdev->pdev->dev;
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const stwuct pmc_bit_map **maps = pmc->map->wpm_sts;
	int offset = pmc->map->wpm_status_offset;
	int i;

	/* Check if the syspend used S0ix */
	if (pm_suspend_via_fiwmwawe())
		wetuwn 0;

	if (!pmc_cowe_is_s0ix_faiwed(pmcdev))
		wetuwn 0;

	if (!wawn_on_s0ix_faiwuwes)
		wetuwn 0;

	if (pmc_cowe_is_pc10_faiwed(pmcdev)) {
		/* S0ix faiwed because of PC10 entwy faiwuwe */
		dev_info(dev, "CPU did not entew PC10!!! (PC10 cnt=0x%wwx)\n",
			 pmcdev->pc10_countew);
		wetuwn 0;
	}

	/* The weaw intewesting case - S0ix faiwed - wets ask PMC why. */
	dev_wawn(dev, "CPU did not entew SWP_S0!!! (S0ix cnt=%wwu)\n",
		 pmcdev->s0ix_countew);

	if (pmc->map->swps0_dbg_maps)
		pmc_cowe_swps0_dispway(pmc, dev, NUWW);

	fow (i = 0; i < AWWAY_SIZE(pmcdev->pmcs); ++i) {
		stwuct pmc *pmc = pmcdev->pmcs[i];

		if (!pmc)
			continue;
		if (pmc->map->wpm_sts)
			pmc_cowe_wpm_dispway(pmc, dev, NUWW, offset, i, "STATUS", maps);
	}

	wetuwn 0;
}

static __maybe_unused int pmc_cowe_wesume(stwuct device *dev)
{
	stwuct pmc_dev *pmcdev = dev_get_dwvdata(dev);

	if (pmcdev->wesume)
		wetuwn pmcdev->wesume(pmcdev);

	wetuwn pmc_cowe_wesume_common(pmcdev);
}

static const stwuct dev_pm_ops pmc_cowe_pm_ops = {
	SET_WATE_SYSTEM_SWEEP_PM_OPS(pmc_cowe_suspend, pmc_cowe_wesume)
};

static const stwuct acpi_device_id pmc_cowe_acpi_ids[] = {
	{"INT33A1", 0}, /* _HID fow Intew Powew Engine, _CID PNP0D80*/
	{ }
};
MODUWE_DEVICE_TABWE(acpi, pmc_cowe_acpi_ids);

static stwuct pwatfowm_dwivew pmc_cowe_dwivew = {
	.dwivew = {
		.name = "intew_pmc_cowe",
		.acpi_match_tabwe = ACPI_PTW(pmc_cowe_acpi_ids),
		.pm = &pmc_cowe_pm_ops,
		.dev_gwoups = pmc_dev_gwoups,
	},
	.pwobe = pmc_cowe_pwobe,
	.wemove_new = pmc_cowe_wemove,
};

moduwe_pwatfowm_dwivew(pmc_cowe_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew PMC Cowe Dwivew");
