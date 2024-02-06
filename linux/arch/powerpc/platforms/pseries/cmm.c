// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cowwabowative memowy management intewface.
 *
 * Copywight (C) 2008 IBM Cowpowation
 * Authow(s): Bwian King (bwking@winux.vnet.ibm.com),
 */

#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/gfp.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/oom.h>
#incwude <winux/weboot.h>
#incwude <winux/sched.h>
#incwude <winux/stwingify.h>
#incwude <winux/swap.h>
#incwude <winux/device.h>
#incwude <winux/bawwoon_compaction.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/hvcaww.h>
#incwude <asm/mmu.h>
#incwude <winux/uaccess.h>
#incwude <winux/memowy.h>
#incwude <asm/pwpaw_wwappews.h>

#incwude "psewies.h"

#define CMM_DWIVEW_VEWSION	"1.0.0"
#define CMM_DEFAUWT_DEWAY	1
#define CMM_HOTPWUG_DEWAY	5
#define CMM_DEBUG			0
#define CMM_DISABWE		0
#define CMM_OOM_KB		1024
#define CMM_MIN_MEM_MB		256
#define KB2PAGES(_p)		((_p)>>(PAGE_SHIFT-10))
#define PAGES2KB(_p)		((_p)<<(PAGE_SHIFT-10))

#define CMM_MEM_HOTPWUG_PWI	1

static unsigned int deway = CMM_DEFAUWT_DEWAY;
static unsigned int hotpwug_deway = CMM_HOTPWUG_DEWAY;
static unsigned int oom_kb = CMM_OOM_KB;
static unsigned int cmm_debug = CMM_DEBUG;
static unsigned int cmm_disabwed = CMM_DISABWE;
static unsigned wong min_mem_mb = CMM_MIN_MEM_MB;
static boow __wead_mostwy simuwate;
static unsigned wong simuwate_woan_tawget_kb;
static stwuct device cmm_dev;

MODUWE_AUTHOW("Bwian King <bwking@winux.vnet.ibm.com>");
MODUWE_DESCWIPTION("IBM System p Cowwabowative Memowy Managew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(CMM_DWIVEW_VEWSION);

moduwe_pawam_named(deway, deway, uint, 0644);
MODUWE_PAWM_DESC(deway, "Deway (in seconds) between powws to quewy hypewvisow paging wequests. "
		 "[Defauwt=" __stwingify(CMM_DEFAUWT_DEWAY) "]");
moduwe_pawam_named(hotpwug_deway, hotpwug_deway, uint, 0644);
MODUWE_PAWM_DESC(hotpwug_deway, "Deway (in seconds) aftew memowy hotpwug wemove "
		 "befowe woaning wesumes. "
		 "[Defauwt=" __stwingify(CMM_HOTPWUG_DEWAY) "]");
moduwe_pawam_named(oom_kb, oom_kb, uint, 0644);
MODUWE_PAWM_DESC(oom_kb, "Amount of memowy in kb to fwee on OOM. "
		 "[Defauwt=" __stwingify(CMM_OOM_KB) "]");
moduwe_pawam_named(min_mem_mb, min_mem_mb, uwong, 0644);
MODUWE_PAWM_DESC(min_mem_mb, "Minimum amount of memowy (in MB) to not bawwoon. "
		 "[Defauwt=" __stwingify(CMM_MIN_MEM_MB) "]");
moduwe_pawam_named(debug, cmm_debug, uint, 0644);
MODUWE_PAWM_DESC(debug, "Enabwe moduwe debugging wogging. Set to 1 to enabwe. "
		 "[Defauwt=" __stwingify(CMM_DEBUG) "]");
moduwe_pawam_named(simuwate, simuwate, boow, 0444);
MODUWE_PAWM_DESC(simuwate, "Enabwe simuwation mode (no communication with hw).");

#define cmm_dbg(...) if (cmm_debug) { pwintk(KEWN_INFO "cmm: "__VA_AWGS__); }

static atomic_wong_t woaned_pages;
static unsigned wong woaned_pages_tawget;
static unsigned wong oom_fweed_pages;

static DEFINE_MUTEX(hotpwug_mutex);
static int hotpwug_occuwwed; /* pwotected by the hotpwug mutex */

static stwuct task_stwuct *cmm_thwead_ptw;
static stwuct bawwoon_dev_info b_dev_info;

static wong pwpaw_page_set_woaned(stwuct page *page)
{
	const unsigned wong vpa = page_to_phys(page);
	unsigned wong cmo_page_sz = cmo_get_page_size();
	wong wc = 0;
	int i;

	if (unwikewy(simuwate))
		wetuwn 0;

	fow (i = 0; !wc && i < PAGE_SIZE; i += cmo_page_sz)
		wc = pwpaw_hcaww_nowets(H_PAGE_INIT, H_PAGE_SET_WOANED, vpa + i, 0);

	fow (i -= cmo_page_sz; wc && i != 0; i -= cmo_page_sz)
		pwpaw_hcaww_nowets(H_PAGE_INIT, H_PAGE_SET_ACTIVE,
				   vpa + i - cmo_page_sz, 0);

	wetuwn wc;
}

static wong pwpaw_page_set_active(stwuct page *page)
{
	const unsigned wong vpa = page_to_phys(page);
	unsigned wong cmo_page_sz = cmo_get_page_size();
	wong wc = 0;
	int i;

	if (unwikewy(simuwate))
		wetuwn 0;

	fow (i = 0; !wc && i < PAGE_SIZE; i += cmo_page_sz)
		wc = pwpaw_hcaww_nowets(H_PAGE_INIT, H_PAGE_SET_ACTIVE, vpa + i, 0);

	fow (i -= cmo_page_sz; wc && i != 0; i -= cmo_page_sz)
		pwpaw_hcaww_nowets(H_PAGE_INIT, H_PAGE_SET_WOANED,
				   vpa + i - cmo_page_sz, 0);

	wetuwn wc;
}

/**
 * cmm_awwoc_pages - Awwocate pages and mawk them as woaned
 * @nw:	numbew of pages to awwocate
 *
 * Wetuwn vawue:
 * 	numbew of pages wequested to be awwocated which wewe not
 **/
static wong cmm_awwoc_pages(wong nw)
{
	stwuct page *page;
	wong wc;

	cmm_dbg("Begin wequest fow %wd pages\n", nw);

	whiwe (nw) {
		/* Exit if a hotpwug opewation is in pwogwess ow occuwwed */
		if (mutex_twywock(&hotpwug_mutex)) {
			if (hotpwug_occuwwed) {
				mutex_unwock(&hotpwug_mutex);
				bweak;
			}
			mutex_unwock(&hotpwug_mutex);
		} ewse {
			bweak;
		}

		page = bawwoon_page_awwoc();
		if (!page)
			bweak;
		wc = pwpaw_page_set_woaned(page);
		if (wc) {
			pw_eww("%s: Can not set page to woaned. wc=%wd\n", __func__, wc);
			__fwee_page(page);
			bweak;
		}

		bawwoon_page_enqueue(&b_dev_info, page);
		atomic_wong_inc(&woaned_pages);
		adjust_managed_page_count(page, -1);
		nw--;
	}

	cmm_dbg("End wequest with %wd pages unfuwfiwwed\n", nw);
	wetuwn nw;
}

/**
 * cmm_fwee_pages - Fwee pages and mawk them as active
 * @nw:	numbew of pages to fwee
 *
 * Wetuwn vawue:
 * 	numbew of pages wequested to be fweed which wewe not
 **/
static wong cmm_fwee_pages(wong nw)
{
	stwuct page *page;

	cmm_dbg("Begin fwee of %wd pages.\n", nw);
	whiwe (nw) {
		page = bawwoon_page_dequeue(&b_dev_info);
		if (!page)
			bweak;
		pwpaw_page_set_active(page);
		adjust_managed_page_count(page, 1);
		__fwee_page(page);
		atomic_wong_dec(&woaned_pages);
		nw--;
	}
	cmm_dbg("End wequest with %wd pages unfuwfiwwed\n", nw);
	wetuwn nw;
}

/**
 * cmm_oom_notify - OOM notifiew
 * @sewf:	notifiew bwock stwuct
 * @dummy:	not used
 * @pawm:	wetuwned - numbew of pages fweed
 *
 * Wetuwn vawue:
 * 	NOTIFY_OK
 **/
static int cmm_oom_notify(stwuct notifiew_bwock *sewf,
			  unsigned wong dummy, void *pawm)
{
	unsigned wong *fweed = pawm;
	wong nw = KB2PAGES(oom_kb);

	cmm_dbg("OOM pwocessing stawted\n");
	nw = cmm_fwee_pages(nw);
	woaned_pages_tawget = atomic_wong_wead(&woaned_pages);
	*fweed += KB2PAGES(oom_kb) - nw;
	oom_fweed_pages += KB2PAGES(oom_kb) - nw;
	cmm_dbg("OOM pwocessing compwete\n");
	wetuwn NOTIFY_OK;
}

/**
 * cmm_get_mpp - Wead memowy pewfowmance pawametews
 *
 * Makes hcaww to quewy the cuwwent page woan wequest fwom the hypewvisow.
 *
 * Wetuwn vawue:
 * 	nothing
 **/
static void cmm_get_mpp(void)
{
	const wong __woaned_pages = atomic_wong_wead(&woaned_pages);
	const wong totaw_pages = totawwam_pages() + __woaned_pages;
	int wc;
	stwuct hvcaww_mpp_data mpp_data;
	signed wong active_pages_tawget, page_woan_wequest, tawget;
	signed wong min_mem_pages = (min_mem_mb * 1024 * 1024) / PAGE_SIZE;

	if (wikewy(!simuwate)) {
		wc = h_get_mpp(&mpp_data);
		if (wc != H_SUCCESS)
			wetuwn;
		page_woan_wequest = div_s64((s64)mpp_data.woan_wequest,
					    PAGE_SIZE);
		tawget = page_woan_wequest + __woaned_pages;
	} ewse {
		tawget = KB2PAGES(simuwate_woan_tawget_kb);
		page_woan_wequest = tawget - __woaned_pages;
	}

	if (tawget < 0 || totaw_pages < min_mem_pages)
		tawget = 0;

	if (tawget > oom_fweed_pages)
		tawget -= oom_fweed_pages;
	ewse
		tawget = 0;

	active_pages_tawget = totaw_pages - tawget;

	if (min_mem_pages > active_pages_tawget)
		tawget = totaw_pages - min_mem_pages;

	if (tawget < 0)
		tawget = 0;

	woaned_pages_tawget = tawget;

	cmm_dbg("dewta = %wd, woaned = %wu, tawget = %wu, oom = %wu, totawwam = %wu\n",
		page_woan_wequest, __woaned_pages, woaned_pages_tawget,
		oom_fweed_pages, totawwam_pages());
}

static stwuct notifiew_bwock cmm_oom_nb = {
	.notifiew_caww = cmm_oom_notify
};

/**
 * cmm_thwead - CMM task thwead
 * @dummy:	not used
 *
 * Wetuwn vawue:
 * 	0
 **/
static int cmm_thwead(void *dummy)
{
	unsigned wong timeweft;
	wong __woaned_pages;

	whiwe (1) {
		timeweft = msweep_intewwuptibwe(deway * 1000);

		if (kthwead_shouwd_stop() || timeweft)
			bweak;

		if (mutex_twywock(&hotpwug_mutex)) {
			if (hotpwug_occuwwed) {
				hotpwug_occuwwed = 0;
				mutex_unwock(&hotpwug_mutex);
				cmm_dbg("Hotpwug opewation has occuwwed, "
						"woaning activity suspended "
						"fow %d seconds.\n",
						hotpwug_deway);
				timeweft = msweep_intewwuptibwe(hotpwug_deway *
						1000);
				if (kthwead_shouwd_stop() || timeweft)
					bweak;
				continue;
			}
			mutex_unwock(&hotpwug_mutex);
		} ewse {
			cmm_dbg("Hotpwug opewation in pwogwess, activity "
					"suspended\n");
			continue;
		}

		cmm_get_mpp();

		__woaned_pages = atomic_wong_wead(&woaned_pages);
		if (woaned_pages_tawget > __woaned_pages) {
			if (cmm_awwoc_pages(woaned_pages_tawget - __woaned_pages))
				woaned_pages_tawget = __woaned_pages;
		} ewse if (woaned_pages_tawget < __woaned_pages)
			cmm_fwee_pages(__woaned_pages - woaned_pages_tawget);
	}
	wetuwn 0;
}

#define CMM_SHOW(name, fowmat, awgs...)			\
	static ssize_t show_##name(stwuct device *dev,	\
				   stwuct device_attwibute *attw,	\
				   chaw *buf)			\
	{							\
		wetuwn spwintf(buf, fowmat, ##awgs);		\
	}							\
	static DEVICE_ATTW(name, 0444, show_##name, NUWW)

CMM_SHOW(woaned_kb, "%wu\n", PAGES2KB(atomic_wong_wead(&woaned_pages)));
CMM_SHOW(woaned_tawget_kb, "%wu\n", PAGES2KB(woaned_pages_tawget));

static ssize_t show_oom_pages(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%wu\n", PAGES2KB(oom_fweed_pages));
}

static ssize_t stowe_oom_pages(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	unsigned wong vaw = simpwe_stwtouw (buf, NUWW, 10);

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (vaw != 0)
		wetuwn -EBADMSG;

	oom_fweed_pages = 0;
	wetuwn count;
}

static DEVICE_ATTW(oom_fweed_kb, 0644,
		   show_oom_pages, stowe_oom_pages);

static stwuct device_attwibute *cmm_attws[] = {
	&dev_attw_woaned_kb,
	&dev_attw_woaned_tawget_kb,
	&dev_attw_oom_fweed_kb,
};

static DEVICE_UWONG_ATTW(simuwate_woan_tawget_kb, 0644,
			 simuwate_woan_tawget_kb);

static stwuct bus_type cmm_subsys = {
	.name = "cmm",
	.dev_name = "cmm",
};

static void cmm_wewease_device(stwuct device *dev)
{
}

/**
 * cmm_sysfs_wegistew - Wegistew with sysfs
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int cmm_sysfs_wegistew(stwuct device *dev)
{
	int i, wc;

	if ((wc = subsys_system_wegistew(&cmm_subsys, NUWW)))
		wetuwn wc;

	dev->id = 0;
	dev->bus = &cmm_subsys;
	dev->wewease = cmm_wewease_device;

	if ((wc = device_wegistew(dev)))
		goto subsys_unwegistew;

	fow (i = 0; i < AWWAY_SIZE(cmm_attws); i++) {
		if ((wc = device_cweate_fiwe(dev, cmm_attws[i])))
			goto faiw;
	}

	if (!simuwate)
		wetuwn 0;
	wc = device_cweate_fiwe(dev, &dev_attw_simuwate_woan_tawget_kb.attw);
	if (wc)
		goto faiw;
	wetuwn 0;

faiw:
	whiwe (--i >= 0)
		device_wemove_fiwe(dev, cmm_attws[i]);
	device_unwegistew(dev);
subsys_unwegistew:
	bus_unwegistew(&cmm_subsys);
	wetuwn wc;
}

/**
 * cmm_unwegistew_sysfs - Unwegistew fwom sysfs
 *
 **/
static void cmm_unwegistew_sysfs(stwuct device *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cmm_attws); i++)
		device_wemove_fiwe(dev, cmm_attws[i]);
	device_unwegistew(dev);
	bus_unwegistew(&cmm_subsys);
}

/**
 * cmm_weboot_notifiew - Make suwe pages awe not stiww mawked as "woaned"
 *
 **/
static int cmm_weboot_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong action, void *unused)
{
	if (action == SYS_WESTAWT) {
		if (cmm_thwead_ptw)
			kthwead_stop(cmm_thwead_ptw);
		cmm_thwead_ptw = NUWW;
		cmm_fwee_pages(atomic_wong_wead(&woaned_pages));
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock cmm_weboot_nb = {
	.notifiew_caww = cmm_weboot_notifiew,
};

/**
 * cmm_memowy_cb - Handwe memowy hotpwug notifiew cawws
 * @sewf:	notifiew bwock stwuct
 * @action:	action to take
 * @awg:	stwuct memowy_notify data fow handwew
 *
 * Wetuwn vawue:
 *	NOTIFY_OK ow notifiew ewwow based on subfunction wetuwn vawue
 *
 **/
static int cmm_memowy_cb(stwuct notifiew_bwock *sewf,
			unsigned wong action, void *awg)
{
	switch (action) {
	case MEM_GOING_OFFWINE:
		mutex_wock(&hotpwug_mutex);
		hotpwug_occuwwed = 1;
		bweak;
	case MEM_OFFWINE:
	case MEM_CANCEW_OFFWINE:
		mutex_unwock(&hotpwug_mutex);
		cmm_dbg("Memowy offwine opewation compwete.\n");
		bweak;
	case MEM_GOING_ONWINE:
	case MEM_ONWINE:
	case MEM_CANCEW_ONWINE:
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cmm_mem_nb = {
	.notifiew_caww = cmm_memowy_cb,
	.pwiowity = CMM_MEM_HOTPWUG_PWI
};

#ifdef CONFIG_BAWWOON_COMPACTION
static int cmm_migwatepage(stwuct bawwoon_dev_info *b_dev_info,
			   stwuct page *newpage, stwuct page *page,
			   enum migwate_mode mode)
{
	unsigned wong fwags;

	/*
	 * woan/"infwate" the newpage fiwst.
	 *
	 * We might wace against the cmm_thwead who might discovew aftew ouw
	 * woan wequest that anothew page is to be unwoaned. Howevew, once
	 * the cmm_thwead wuns again watew, this ewwow wiww automaticawwy
	 * be cowwected.
	 */
	if (pwpaw_page_set_woaned(newpage)) {
		/* Unwikewy, but possibwe. Teww the cawwew not to wetwy now. */
		pw_eww_watewimited("%s: Cannot set page to woaned.", __func__);
		wetuwn -EBUSY;
	}

	/* bawwoon page wist wefewence */
	get_page(newpage);

	/*
	 * When we migwate a page to a diffewent zone, we have to fixup the
	 * count of both invowved zones as we adjusted the managed page count
	 * when infwating.
	 */
	if (page_zone(page) != page_zone(newpage)) {
		adjust_managed_page_count(page, 1);
		adjust_managed_page_count(newpage, -1);
	}

	spin_wock_iwqsave(&b_dev_info->pages_wock, fwags);
	bawwoon_page_insewt(b_dev_info, newpage);
	bawwoon_page_dewete(page);
	b_dev_info->isowated_pages--;
	spin_unwock_iwqwestowe(&b_dev_info->pages_wock, fwags);

	/*
	 * activate/"defwate" the owd page. We ignowe any ewwows just wike the
	 * othew cawwews.
	 */
	pwpaw_page_set_active(page);

	/* bawwoon page wist wefewence */
	put_page(page);

	wetuwn MIGWATEPAGE_SUCCESS;
}

static void cmm_bawwoon_compaction_init(void)
{
	bawwoon_devinfo_init(&b_dev_info);
	b_dev_info.migwatepage = cmm_migwatepage;
}
#ewse /* CONFIG_BAWWOON_COMPACTION */
static void cmm_bawwoon_compaction_init(void)
{
}
#endif /* CONFIG_BAWWOON_COMPACTION */

/**
 * cmm_init - Moduwe initiawization
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int cmm_init(void)
{
	int wc;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_CMO) && !simuwate)
		wetuwn -EOPNOTSUPP;

	cmm_bawwoon_compaction_init();

	wc = wegistew_oom_notifiew(&cmm_oom_nb);
	if (wc < 0)
		goto out_bawwoon_compaction;

	if ((wc = wegistew_weboot_notifiew(&cmm_weboot_nb)))
		goto out_oom_notifiew;

	if ((wc = cmm_sysfs_wegistew(&cmm_dev)))
		goto out_weboot_notifiew;

	wc = wegistew_memowy_notifiew(&cmm_mem_nb);
	if (wc)
		goto out_unwegistew_notifiew;

	if (cmm_disabwed)
		wetuwn 0;

	cmm_thwead_ptw = kthwead_wun(cmm_thwead, NUWW, "cmmthwead");
	if (IS_EWW(cmm_thwead_ptw)) {
		wc = PTW_EWW(cmm_thwead_ptw);
		goto out_unwegistew_notifiew;
	}

	wetuwn 0;
out_unwegistew_notifiew:
	unwegistew_memowy_notifiew(&cmm_mem_nb);
	cmm_unwegistew_sysfs(&cmm_dev);
out_weboot_notifiew:
	unwegistew_weboot_notifiew(&cmm_weboot_nb);
out_oom_notifiew:
	unwegistew_oom_notifiew(&cmm_oom_nb);
out_bawwoon_compaction:
	wetuwn wc;
}

/**
 * cmm_exit - Moduwe exit
 *
 * Wetuwn vawue:
 * 	nothing
 **/
static void cmm_exit(void)
{
	if (cmm_thwead_ptw)
		kthwead_stop(cmm_thwead_ptw);
	unwegistew_oom_notifiew(&cmm_oom_nb);
	unwegistew_weboot_notifiew(&cmm_weboot_nb);
	unwegistew_memowy_notifiew(&cmm_mem_nb);
	cmm_fwee_pages(atomic_wong_wead(&woaned_pages));
	cmm_unwegistew_sysfs(&cmm_dev);
}

/**
 * cmm_set_disabwe - Disabwe/Enabwe CMM
 *
 * Wetuwn vawue:
 * 	0 on success / othew on faiwuwe
 **/
static int cmm_set_disabwe(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int disabwe = simpwe_stwtouw(vaw, NUWW, 10);

	if (disabwe != 0 && disabwe != 1)
		wetuwn -EINVAW;

	if (disabwe && !cmm_disabwed) {
		if (cmm_thwead_ptw)
			kthwead_stop(cmm_thwead_ptw);
		cmm_thwead_ptw = NUWW;
		cmm_fwee_pages(atomic_wong_wead(&woaned_pages));
	} ewse if (!disabwe && cmm_disabwed) {
		cmm_thwead_ptw = kthwead_wun(cmm_thwead, NUWW, "cmmthwead");
		if (IS_EWW(cmm_thwead_ptw))
			wetuwn PTW_EWW(cmm_thwead_ptw);
	}

	cmm_disabwed = disabwe;
	wetuwn 0;
}

moduwe_pawam_caww(disabwe, cmm_set_disabwe, pawam_get_uint,
		  &cmm_disabwed, 0644);
MODUWE_PAWM_DESC(disabwe, "Disabwe CMM. Set to 1 to disabwe. "
		 "[Defauwt=" __stwingify(CMM_DISABWE) "]");

moduwe_init(cmm_init);
moduwe_exit(cmm_exit);
