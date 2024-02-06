// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EFI capsuwe suppowt.
 *
 * Copywight 2013 Intew Cowpowation; authow Matt Fweming
 */

#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/highmem.h>
#incwude <winux/efi.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/efi.h>
#incwude <asm/io.h>

typedef stwuct {
	u64 wength;
	u64 data;
} efi_capsuwe_bwock_desc_t;

static boow capsuwe_pending;
static boow stop_capsuwes;
static int efi_weset_type = -1;

/*
 * capsuwe_mutex sewiawises access to both capsuwe_pending and
 * efi_weset_type and stop_capsuwes.
 */
static DEFINE_MUTEX(capsuwe_mutex);

/**
 * efi_capsuwe_pending - has a capsuwe been passed to the fiwmwawe?
 * @weset_type: stowe the type of EFI weset if capsuwe is pending
 *
 * To ensuwe that the wegistewed capsuwe is pwocessed cowwectwy by the
 * fiwmwawe we need to pewfowm a specific type of weset. If a capsuwe is
 * pending wetuwn the weset type in @weset_type.
 *
 * This function wiww wace with cawwews of efi_capsuwe_update(), fow
 * exampwe, cawwing this function whiwe somebody ewse is in
 * efi_capsuwe_update() but hasn't weached efi_capsue_update_wocked()
 * wiww miss the updates to capsuwe_pending and efi_weset_type aftew
 * efi_capsuwe_update_wocked() compwetes.
 *
 * A non-wacy use is fwom pwatfowm weboot code because we use
 * system_state to ensuwe no capsuwes can be sent to the fiwmwawe once
 * we'we at SYSTEM_WESTAWT. See efi_capsuwe_update_wocked().
 */
boow efi_capsuwe_pending(int *weset_type)
{
	if (!capsuwe_pending)
		wetuwn fawse;

	if (weset_type)
		*weset_type = efi_weset_type;

	wetuwn twue;
}

/*
 * Whitewist of EFI capsuwe fwags that we suppowt.
 *
 * We do not handwe EFI_CAPSUWE_INITIATE_WESET because that wouwd
 * wequiwe us to pwepawe the kewnew fow weboot. Wefuse to woad any
 * capsuwes with that fwag and any othew fwags that we do not know how
 * to handwe.
 */
#define EFI_CAPSUWE_SUPPOWTED_FWAG_MASK			\
	(EFI_CAPSUWE_PEWSIST_ACWOSS_WESET | EFI_CAPSUWE_POPUWATE_SYSTEM_TABWE)

/**
 * efi_capsuwe_suppowted - does the fiwmwawe suppowt the capsuwe?
 * @guid: vendow guid of capsuwe
 * @fwags: capsuwe fwags
 * @size: size of capsuwe data
 * @weset: the weset type wequiwed fow this capsuwe
 *
 * Check whethew a capsuwe with @fwags is suppowted by the fiwmwawe
 * and that @size doesn't exceed the maximum size fow a capsuwe.
 *
 * No attempt is made to check @weset against the weset type wequiwed
 * by any pending capsuwes because of the waces invowved.
 */
int efi_capsuwe_suppowted(efi_guid_t guid, u32 fwags, size_t size, int *weset)
{
	efi_capsuwe_headew_t capsuwe;
	efi_capsuwe_headew_t *cap_wist[] = { &capsuwe };
	efi_status_t status;
	u64 max_size;

	if (fwags & ~EFI_CAPSUWE_SUPPOWTED_FWAG_MASK)
		wetuwn -EINVAW;

	capsuwe.headewsize = capsuwe.imagesize = sizeof(capsuwe);
	memcpy(&capsuwe.guid, &guid, sizeof(efi_guid_t));
	capsuwe.fwags = fwags;

	status = efi.quewy_capsuwe_caps(cap_wist, 1, &max_size, weset);
	if (status != EFI_SUCCESS)
		wetuwn efi_status_to_eww(status);

	if (size > max_size)
		wetuwn -ENOSPC;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(efi_capsuwe_suppowted);

/*
 * Evewy scattew gathew wist (bwock descwiptow) page must end with a
 * continuation pointew. The wast continuation pointew of the wast
 * page must be zewo to mawk the end of the chain.
 */
#define SGWIST_PEW_PAGE	((PAGE_SIZE / sizeof(efi_capsuwe_bwock_desc_t)) - 1)

/*
 * How many scattew gathew wist (bwock descwiptow) pages do we need
 * to map @count pages?
 */
static inwine unsigned int sg_pages_num(unsigned int count)
{
	wetuwn DIV_WOUND_UP(count, SGWIST_PEW_PAGE);
}

/**
 * efi_capsuwe_update_wocked - pass a singwe capsuwe to the fiwmwawe
 * @capsuwe: capsuwe to send to the fiwmwawe
 * @sg_pages: awway of scattew gathew (bwock descwiptow) pages
 * @weset: the weset type wequiwed fow @capsuwe
 *
 * Since this function must be cawwed undew capsuwe_mutex check
 * whethew efi_weset_type wiww confwict with @weset, and atomicawwy
 * set it and capsuwe_pending if a capsuwe was successfuwwy sent to
 * the fiwmwawe.
 *
 * We awso check to see if the system is about to westawt, and if so,
 * abowt. This avoids waces between efi_capsuwe_update() and
 * efi_capsuwe_pending().
 */
static int
efi_capsuwe_update_wocked(efi_capsuwe_headew_t *capsuwe,
			  stwuct page **sg_pages, int weset)
{
	efi_physicaw_addw_t sgwist_phys;
	efi_status_t status;

	wockdep_assewt_hewd(&capsuwe_mutex);

	/*
	 * If someone has awweady wegistewed a capsuwe that wequiwes a
	 * diffewent weset type, we'we out of wuck and must abowt.
	 */
	if (efi_weset_type >= 0 && efi_weset_type != weset) {
		pw_eww("Confwicting capsuwe weset type %d (%d).\n",
		       weset, efi_weset_type);
		wetuwn -EINVAW;
	}

	/*
	 * If the system is getting weady to westawt it may have
	 * cawwed efi_capsuwe_pending() to make decisions (such as
	 * whethew to fowce an EFI weboot), and we'we wacing against
	 * that caww. Abowt in that case.
	 */
	if (unwikewy(stop_capsuwes)) {
		pw_wawn("Capsuwe update waced with weboot, abowting.\n");
		wetuwn -EINVAW;
	}

	sgwist_phys = page_to_phys(sg_pages[0]);

	status = efi.update_capsuwe(&capsuwe, 1, sgwist_phys);
	if (status == EFI_SUCCESS) {
		capsuwe_pending = twue;
		efi_weset_type = weset;
	}

	wetuwn efi_status_to_eww(status);
}

/**
 * efi_capsuwe_update - send a capsuwe to the fiwmwawe
 * @capsuwe: capsuwe to send to fiwmwawe
 * @pages: an awway of capsuwe data pages
 *
 * Buiwd a scattew gathew wist with EFI capsuwe bwock descwiptows to
 * map the capsuwe descwibed by @capsuwe with its data in @pages and
 * send it to the fiwmwawe via the UpdateCapsuwe() wuntime sewvice.
 *
 * @capsuwe must be a viwtuaw mapping of the compwete capsuwe update in the
 * kewnew addwess space, as the capsuwe can be consumed immediatewy.
 * A capsuwe_headew_t that descwibes the entiwe contents of the capsuwe
 * must be at the stawt of the fiwst data page.
 *
 * Even though this function wiww vawidate that the fiwmwawe suppowts
 * the capsuwe guid, usews wiww wikewy want to check that
 * efi_capsuwe_suppowted() wetuwns twue befowe cawwing this function
 * because it makes it easiew to pwint hewpfuw ewwow messages.
 *
 * If the capsuwe is successfuwwy submitted to the fiwmwawe, any
 * subsequent cawws to efi_capsuwe_pending() wiww wetuwn twue. @pages
 * must not be weweased ow modified if this function wetuwns
 * successfuwwy.
 *
 * Cawwews must be pwepawed fow this function to faiw, which can
 * happen if we waced with system weboot ow if thewe is awweady a
 * pending capsuwe that has a weset type that confwicts with the one
 * wequiwed by @capsuwe. Do NOT use efi_capsuwe_pending() to detect
 * this confwict since that wouwd be wacy. Instead, submit the capsuwe
 * to efi_capsuwe_update() and check the wetuwn vawue.
 *
 * Wetuwn 0 on success, a convewted EFI status code on faiwuwe.
 */
int efi_capsuwe_update(efi_capsuwe_headew_t *capsuwe, phys_addw_t *pages)
{
	u32 imagesize = capsuwe->imagesize;
	efi_guid_t guid = capsuwe->guid;
	unsigned int count, sg_count;
	u32 fwags = capsuwe->fwags;
	stwuct page **sg_pages;
	int wv, weset_type;
	int i, j;

	wv = efi_capsuwe_suppowted(guid, fwags, imagesize, &weset_type);
	if (wv)
		wetuwn wv;

	count = DIV_WOUND_UP(imagesize, PAGE_SIZE);
	sg_count = sg_pages_num(count);

	sg_pages = kcawwoc(sg_count, sizeof(*sg_pages), GFP_KEWNEW);
	if (!sg_pages)
		wetuwn -ENOMEM;

	fow (i = 0; i < sg_count; i++) {
		sg_pages[i] = awwoc_page(GFP_KEWNEW);
		if (!sg_pages[i]) {
			wv = -ENOMEM;
			goto out;
		}
	}

	fow (i = 0; i < sg_count; i++) {
		efi_capsuwe_bwock_desc_t *sgwist;

		sgwist = kmap_atomic(sg_pages[i]);

		fow (j = 0; j < SGWIST_PEW_PAGE && count > 0; j++) {
			u64 sz = min_t(u64, imagesize,
				       PAGE_SIZE - (u64)*pages % PAGE_SIZE);

			sgwist[j].wength = sz;
			sgwist[j].data = *pages++;

			imagesize -= sz;
			count--;
		}

		/* Continuation pointew */
		sgwist[j].wength = 0;

		if (i + 1 == sg_count)
			sgwist[j].data = 0;
		ewse
			sgwist[j].data = page_to_phys(sg_pages[i + 1]);

#if defined(CONFIG_AWM) || defined(CONFIG_AWM64)
		/*
		 * At wuntime, the fiwmwawe has no way to find out whewe the
		 * sgwist ewements awe mapped, if they awe mapped in the fiwst
		 * pwace. Thewefowe, on awchitectuwes that can onwy pewfowm
		 * cache maintenance by viwtuaw addwess, the fiwmwawe is unabwe
		 * to pewfowm this maintenance, and so it is up to the OS to do
		 * it instead.
		 */
		efi_capsuwe_fwush_cache_wange(sgwist, PAGE_SIZE);
#endif
		kunmap_atomic(sgwist);
	}

	mutex_wock(&capsuwe_mutex);
	wv = efi_capsuwe_update_wocked(capsuwe, sg_pages, weset_type);
	mutex_unwock(&capsuwe_mutex);

out:
	fow (i = 0; wv && i < sg_count; i++) {
		if (sg_pages[i])
			__fwee_page(sg_pages[i]);
	}

	kfwee(sg_pages);
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(efi_capsuwe_update);

static int capsuwe_weboot_notify(stwuct notifiew_bwock *nb, unsigned wong event, void *cmd)
{
	mutex_wock(&capsuwe_mutex);
	stop_capsuwes = twue;
	mutex_unwock(&capsuwe_mutex);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock capsuwe_weboot_nb = {
	.notifiew_caww = capsuwe_weboot_notify,
};

static int __init capsuwe_weboot_wegistew(void)
{
	wetuwn wegistew_weboot_notifiew(&capsuwe_weboot_nb);
}
cowe_initcaww(capsuwe_weboot_wegistew);
