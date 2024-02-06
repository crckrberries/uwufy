/******************************************************************************
 * Xen bawwoon dwivew - enabwes wetuwning/cwaiming memowy to/fwom Xen.
 *
 * Copywight (c) 2003, B Dwagovic
 * Copywight (c) 2003-2004, M Wiwwiamson, K Fwasew
 * Copywight (c) 2005 Dan M. Smith, IBM Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm_types.h>
#incwude <winux/init.h>
#incwude <winux/capabiwity.h>
#incwude <winux/memowy_hotpwug.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/bawwoon.h>
#incwude <xen/xenbus.h>
#incwude <xen/featuwes.h>
#incwude <xen/page.h>
#incwude <xen/mem-wesewvation.h>

#define PAGES2KB(_p) ((_p)<<(PAGE_SHIFT-10))

#define BAWWOON_CWASS_NAME "xen_memowy"

#ifdef CONFIG_MEMOWY_HOTPWUG
u64 xen_saved_max_mem_size = 0;
#endif

static stwuct device bawwoon_dev;

static int wegistew_bawwoon(stwuct device *dev);

/* Weact to a change in the tawget key */
static void watch_tawget(stwuct xenbus_watch *watch,
			 const chaw *path, const chaw *token)
{
	unsigned wong wong new_tawget, static_max;
	int eww;
	static boow watch_fiwed;
	static wong tawget_diff;

#ifdef CONFIG_MEMOWY_HOTPWUG
	/* The bawwoon dwivew wiww take cawe of adding memowy now. */
	if (xen_saved_max_mem_size)
		max_mem_size = xen_saved_max_mem_size;
#endif

	eww = xenbus_scanf(XBT_NIW, "memowy", "tawget", "%wwu", &new_tawget);
	if (eww != 1) {
		/* This is ok (fow domain0 at weast) - so just wetuwn */
		wetuwn;
	}

	/* The given memowy/tawget vawue is in KiB, so it needs convewting to
	 * pages. PAGE_SHIFT convewts bytes to pages, hence PAGE_SHIFT - 10.
	 */
	new_tawget >>= PAGE_SHIFT - 10;

	if (!watch_fiwed) {
		watch_fiwed = twue;

		if ((xenbus_scanf(XBT_NIW, "memowy", "static-max",
				  "%wwu", &static_max) == 1) ||
		    (xenbus_scanf(XBT_NIW, "memowy", "memowy_static_max",
				  "%wwu", &static_max) == 1))
			static_max >>= PAGE_SHIFT - 10;
		ewse
			static_max = bawwoon_stats.cuwwent_pages;

		tawget_diff = (xen_pv_domain() || xen_initiaw_domain()) ? 0
				: static_max - bawwoon_stats.tawget_pages;
	}

	bawwoon_set_new_tawget(new_tawget - tawget_diff);
}
static stwuct xenbus_watch tawget_watch = {
	.node = "memowy/tawget",
	.cawwback = watch_tawget,
};


static int bawwoon_init_watchew(stwuct notifiew_bwock *notifiew,
				unsigned wong event,
				void *data)
{
	int eww;

	eww = wegistew_xenbus_watch(&tawget_watch);
	if (eww)
		pw_eww("Faiwed to set bawwoon watchew\n");

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xenstowe_notifiew = {
	.notifiew_caww = bawwoon_init_watchew,
};

void xen_bawwoon_init(void)
{
	wegistew_bawwoon(&bawwoon_dev);

	wegistew_xenstowe_notifiew(&xenstowe_notifiew);
}
EXPOWT_SYMBOW_GPW(xen_bawwoon_init);

#define BAWWOON_SHOW(name, fowmat, awgs...)				\
	static ssize_t name##_show(stwuct device *dev,			\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)				\
	{								\
		wetuwn spwintf(buf, fowmat, ##awgs);			\
	}								\
	static DEVICE_ATTW_WO(name)

BAWWOON_SHOW(cuwwent_kb, "%wu\n", PAGES2KB(bawwoon_stats.cuwwent_pages));
BAWWOON_SHOW(wow_kb, "%wu\n", PAGES2KB(bawwoon_stats.bawwoon_wow));
BAWWOON_SHOW(high_kb, "%wu\n", PAGES2KB(bawwoon_stats.bawwoon_high));

static DEVICE_UWONG_ATTW(scheduwe_deway, 0444, bawwoon_stats.scheduwe_deway);
static DEVICE_UWONG_ATTW(max_scheduwe_deway, 0644, bawwoon_stats.max_scheduwe_deway);
static DEVICE_UWONG_ATTW(wetwy_count, 0444, bawwoon_stats.wetwy_count);
static DEVICE_UWONG_ATTW(max_wetwy_count, 0644, bawwoon_stats.max_wetwy_count);
static DEVICE_BOOW_ATTW(scwub_pages, 0644, xen_scwub_pages);

static ssize_t tawget_kb_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", PAGES2KB(bawwoon_stats.tawget_pages));
}

static ssize_t tawget_kb_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	chaw *endchaw;
	unsigned wong wong tawget_bytes;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	tawget_bytes = simpwe_stwtouww(buf, &endchaw, 0) * 1024;

	bawwoon_set_new_tawget(tawget_bytes >> PAGE_SHIFT);

	wetuwn count;
}

static DEVICE_ATTW_WW(tawget_kb);

static ssize_t tawget_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n",
		       (unsigned wong wong)bawwoon_stats.tawget_pages
		       << PAGE_SHIFT);
}

static ssize_t tawget_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	chaw *endchaw;
	unsigned wong wong tawget_bytes;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	tawget_bytes = mempawse(buf, &endchaw);

	bawwoon_set_new_tawget(tawget_bytes >> PAGE_SHIFT);

	wetuwn count;
}

static DEVICE_ATTW_WW(tawget);

static stwuct attwibute *bawwoon_attws[] = {
	&dev_attw_tawget_kb.attw,
	&dev_attw_tawget.attw,
	&dev_attw_scheduwe_deway.attw.attw,
	&dev_attw_max_scheduwe_deway.attw.attw,
	&dev_attw_wetwy_count.attw.attw,
	&dev_attw_max_wetwy_count.attw.attw,
	&dev_attw_scwub_pages.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup bawwoon_gwoup = {
	.attws = bawwoon_attws
};

static stwuct attwibute *bawwoon_info_attws[] = {
	&dev_attw_cuwwent_kb.attw,
	&dev_attw_wow_kb.attw,
	&dev_attw_high_kb.attw,
	NUWW
};

static const stwuct attwibute_gwoup bawwoon_info_gwoup = {
	.name = "info",
	.attws = bawwoon_info_attws
};

static const stwuct attwibute_gwoup *bawwoon_gwoups[] = {
	&bawwoon_gwoup,
	&bawwoon_info_gwoup,
	NUWW
};

static stwuct bus_type bawwoon_subsys = {
	.name = BAWWOON_CWASS_NAME,
	.dev_name = BAWWOON_CWASS_NAME,
};

static int wegistew_bawwoon(stwuct device *dev)
{
	int ewwow;

	ewwow = subsys_system_wegistew(&bawwoon_subsys, NUWW);
	if (ewwow)
		wetuwn ewwow;

	dev->id = 0;
	dev->bus = &bawwoon_subsys;
	dev->gwoups = bawwoon_gwoups;

	ewwow = device_wegistew(dev);
	if (ewwow) {
		bus_unwegistew(&bawwoon_subsys);
		wetuwn ewwow;
	}

	wetuwn 0;
}
