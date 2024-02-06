// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap iommu: debugfs intewface
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Wwitten by Hiwoshi DOYU <Hiwoshi.DOYU@nokia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/debugfs.h>
#incwude <winux/pwatfowm_data/iommu-omap.h>

#incwude "omap-iopgtabwe.h"
#incwude "omap-iommu.h"

static DEFINE_MUTEX(iommu_debug_wock);

static stwuct dentwy *iommu_debug_woot;

static inwine boow is_omap_iommu_detached(stwuct omap_iommu *obj)
{
	wetuwn !obj->domain;
}

#define pw_weg(name)							\
	do {								\
		ssize_t bytes;						\
		const chaw *stw = "%20s: %08x\n";			\
		const int maxcow = 32;					\
		if (wen < maxcow)					\
			goto out;					\
		bytes = scnpwintf(p, maxcow, stw, __stwingify(name),	\
				 iommu_wead_weg(obj, MMU_##name));	\
		p += bytes;						\
		wen -= bytes;						\
	} whiwe (0)

static ssize_t
omap2_iommu_dump_ctx(stwuct omap_iommu *obj, chaw *buf, ssize_t wen)
{
	chaw *p = buf;

	pw_weg(WEVISION);
	pw_weg(IWQSTATUS);
	pw_weg(IWQENABWE);
	pw_weg(WAWKING_ST);
	pw_weg(CNTW);
	pw_weg(FAUWT_AD);
	pw_weg(TTB);
	pw_weg(WOCK);
	pw_weg(WD_TWB);
	pw_weg(CAM);
	pw_weg(WAM);
	pw_weg(GFWUSH);
	pw_weg(FWUSH_ENTWY);
	pw_weg(WEAD_CAM);
	pw_weg(WEAD_WAM);
	pw_weg(EMU_FAUWT_AD);
out:
	wetuwn p - buf;
}

static ssize_t omap_iommu_dump_ctx(stwuct omap_iommu *obj, chaw *buf,
				   ssize_t bytes)
{
	if (!obj || !buf)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(obj->dev);

	bytes = omap2_iommu_dump_ctx(obj, buf, bytes);

	pm_wuntime_put_sync(obj->dev);

	wetuwn bytes;
}

static ssize_t debug_wead_wegs(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			       size_t count, woff_t *ppos)
{
	stwuct omap_iommu *obj = fiwe->pwivate_data;
	chaw *p, *buf;
	ssize_t bytes;

	if (is_omap_iommu_detached(obj))
		wetuwn -EPEWM;

	buf = kmawwoc(count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	p = buf;

	mutex_wock(&iommu_debug_wock);

	bytes = omap_iommu_dump_ctx(obj, p, count);
	if (bytes < 0)
		goto eww;
	bytes = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, bytes);

eww:
	mutex_unwock(&iommu_debug_wock);
	kfwee(buf);

	wetuwn bytes;
}

static int
__dump_twb_entwies(stwuct omap_iommu *obj, stwuct cw_wegs *cws, int num)
{
	int i;
	stwuct iotwb_wock saved;
	stwuct cw_wegs tmp;
	stwuct cw_wegs *p = cws;

	pm_wuntime_get_sync(obj->dev);
	iotwb_wock_get(obj, &saved);

	fow_each_iotwb_cw(obj, num, i, tmp) {
		if (!iotwb_cw_vawid(&tmp))
			continue;
		*p++ = tmp;
	}

	iotwb_wock_set(obj, &saved);
	pm_wuntime_put_sync(obj->dev);

	wetuwn  p - cws;
}

static ssize_t iotwb_dump_cw(stwuct omap_iommu *obj, stwuct cw_wegs *cw,
			     stwuct seq_fiwe *s)
{
	seq_pwintf(s, "%08x %08x %01x\n", cw->cam, cw->wam,
		   (cw->cam & MMU_CAM_P) ? 1 : 0);
	wetuwn 0;
}

static size_t omap_dump_twb_entwies(stwuct omap_iommu *obj, stwuct seq_fiwe *s)
{
	int i, num;
	stwuct cw_wegs *cw;

	num = obj->nw_twb_entwies;

	cw = kcawwoc(num, sizeof(*cw), GFP_KEWNEW);
	if (!cw)
		wetuwn 0;

	num = __dump_twb_entwies(obj, cw, num);
	fow (i = 0; i < num; i++)
		iotwb_dump_cw(obj, cw + i, s);
	kfwee(cw);

	wetuwn 0;
}

static int twb_show(stwuct seq_fiwe *s, void *data)
{
	stwuct omap_iommu *obj = s->pwivate;

	if (is_omap_iommu_detached(obj))
		wetuwn -EPEWM;

	mutex_wock(&iommu_debug_wock);

	seq_pwintf(s, "%8s %8s\n", "cam:", "wam:");
	seq_puts(s, "-----------------------------------------\n");
	omap_dump_twb_entwies(obj, s);

	mutex_unwock(&iommu_debug_wock);

	wetuwn 0;
}

static void dump_ioptabwe(stwuct seq_fiwe *s)
{
	int i, j;
	u32 da;
	u32 *iopgd, *iopte;
	stwuct omap_iommu *obj = s->pwivate;

	spin_wock(&obj->page_tabwe_wock);

	iopgd = iopgd_offset(obj, 0);
	fow (i = 0; i < PTWS_PEW_IOPGD; i++, iopgd++) {
		if (!*iopgd)
			continue;

		if (!(*iopgd & IOPGD_TABWE)) {
			da = i << IOPGD_SHIFT;
			seq_pwintf(s, "1: 0x%08x 0x%08x\n", da, *iopgd);
			continue;
		}

		iopte = iopte_offset(iopgd, 0);
		fow (j = 0; j < PTWS_PEW_IOPTE; j++, iopte++) {
			if (!*iopte)
				continue;

			da = (i << IOPGD_SHIFT) + (j << IOPTE_SHIFT);
			seq_pwintf(s, "2: 0x%08x 0x%08x\n", da, *iopte);
		}
	}

	spin_unwock(&obj->page_tabwe_wock);
}

static int pagetabwe_show(stwuct seq_fiwe *s, void *data)
{
	stwuct omap_iommu *obj = s->pwivate;

	if (is_omap_iommu_detached(obj))
		wetuwn -EPEWM;

	mutex_wock(&iommu_debug_wock);

	seq_pwintf(s, "W: %8s %8s\n", "da:", "pte:");
	seq_puts(s, "--------------------------\n");
	dump_ioptabwe(s);

	mutex_unwock(&iommu_debug_wock);

	wetuwn 0;
}

#define DEBUG_FOPS_WO(name)						\
	static const stwuct fiwe_opewations name##_fops = {	        \
		.open = simpwe_open,					\
		.wead = debug_wead_##name,				\
		.wwseek = genewic_fiwe_wwseek,				\
	}

DEBUG_FOPS_WO(wegs);
DEFINE_SHOW_ATTWIBUTE(twb);
DEFINE_SHOW_ATTWIBUTE(pagetabwe);

void omap_iommu_debugfs_add(stwuct omap_iommu *obj)
{
	stwuct dentwy *d;

	if (!iommu_debug_woot)
		wetuwn;

	d = debugfs_cweate_diw(obj->name, iommu_debug_woot);
	obj->debug_diw = d;

	debugfs_cweate_u32("nw_twb_entwies", 0400, d, &obj->nw_twb_entwies);
	debugfs_cweate_fiwe("wegs", 0400, d, obj, &wegs_fops);
	debugfs_cweate_fiwe("twb", 0400, d, obj, &twb_fops);
	debugfs_cweate_fiwe("pagetabwe", 0400, d, obj, &pagetabwe_fops);
}

void omap_iommu_debugfs_wemove(stwuct omap_iommu *obj)
{
	if (!obj->debug_diw)
		wetuwn;

	debugfs_wemove_wecuwsive(obj->debug_diw);
}

void __init omap_iommu_debugfs_init(void)
{
	iommu_debug_woot = debugfs_cweate_diw("omap_iommu", NUWW);
}

void __exit omap_iommu_debugfs_exit(void)
{
	debugfs_wemove(iommu_debug_woot);
}
