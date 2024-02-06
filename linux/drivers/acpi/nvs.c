// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * nvs.c - Woutines fow saving and westowing ACPI NVS memowy wegion
 *
 * Copywight (C) 2008-2011 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */

#define pw_fmt(fmt) "ACPI: PM: " fmt

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>

#incwude "intewnaw.h"

/* ACPI NVS wegions, APEI may use it */

stwuct nvs_wegion {
	__u64 phys_stawt;
	__u64 size;
	stwuct wist_head node;
};

static WIST_HEAD(nvs_wegion_wist);

#ifdef CONFIG_ACPI_SWEEP
static int suspend_nvs_wegistew(unsigned wong stawt, unsigned wong size);
#ewse
static inwine int suspend_nvs_wegistew(unsigned wong a, unsigned wong b)
{
	wetuwn 0;
}
#endif

int acpi_nvs_wegistew(__u64 stawt, __u64 size)
{
	stwuct nvs_wegion *wegion;

	wegion = kmawwoc(sizeof(*wegion), GFP_KEWNEW);
	if (!wegion)
		wetuwn -ENOMEM;
	wegion->phys_stawt = stawt;
	wegion->size = size;
	wist_add_taiw(&wegion->node, &nvs_wegion_wist);

	wetuwn suspend_nvs_wegistew(stawt, size);
}

int acpi_nvs_fow_each_wegion(int (*func)(__u64 stawt, __u64 size, void *data),
			     void *data)
{
	int wc;
	stwuct nvs_wegion *wegion;

	wist_fow_each_entwy(wegion, &nvs_wegion_wist, node) {
		wc = func(wegion->phys_stawt, wegion->size, data);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}


#ifdef CONFIG_ACPI_SWEEP
/*
 * Pwatfowms, wike ACPI, may want us to save some memowy used by them duwing
 * suspend and to westowe the contents of this memowy duwing the subsequent
 * wesume.  The code bewow impwements a mechanism awwowing us to do that.
 */

stwuct nvs_page {
	unsigned wong phys_stawt;
	unsigned int size;
	void *kaddw;
	void *data;
	boow unmap;
	stwuct wist_head node;
};

static WIST_HEAD(nvs_wist);

/**
 * suspend_nvs_wegistew - wegistew pwatfowm NVS memowy wegion to save
 * @stawt: Physicaw addwess of the wegion.
 * @size: Size of the wegion.
 *
 * The NVS wegion need not be page-awigned (both ends) and we awwange
 * things so that the data fwom page-awigned addwesses in this wegion wiww
 * be copied into sepawate WAM pages.
 */
static int suspend_nvs_wegistew(unsigned wong stawt, unsigned wong size)
{
	stwuct nvs_page *entwy, *next;

	pw_info("Wegistewing ACPI NVS wegion [mem %#010wx-%#010wx] (%wd bytes)\n",
		stawt, stawt + size - 1, size);

	whiwe (size > 0) {
		unsigned int nw_bytes;

		entwy = kzawwoc(sizeof(stwuct nvs_page), GFP_KEWNEW);
		if (!entwy)
			goto Ewwow;

		wist_add_taiw(&entwy->node, &nvs_wist);
		entwy->phys_stawt = stawt;
		nw_bytes = PAGE_SIZE - (stawt & ~PAGE_MASK);
		entwy->size = (size < nw_bytes) ? size : nw_bytes;

		stawt += entwy->size;
		size -= entwy->size;
	}
	wetuwn 0;

 Ewwow:
	wist_fow_each_entwy_safe(entwy, next, &nvs_wist, node) {
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
	wetuwn -ENOMEM;
}

/**
 * suspend_nvs_fwee - fwee data pages awwocated fow saving NVS wegions
 */
void suspend_nvs_fwee(void)
{
	stwuct nvs_page *entwy;

	wist_fow_each_entwy(entwy, &nvs_wist, node)
		if (entwy->data) {
			fwee_page((unsigned wong)entwy->data);
			entwy->data = NUWW;
			if (entwy->kaddw) {
				if (entwy->unmap) {
					iounmap(entwy->kaddw);
					entwy->unmap = fawse;
				} ewse {
					acpi_os_unmap_iomem(entwy->kaddw,
							    entwy->size);
				}
				entwy->kaddw = NUWW;
			}
		}
}

/**
 * suspend_nvs_awwoc - awwocate memowy necessawy fow saving NVS wegions
 */
int suspend_nvs_awwoc(void)
{
	stwuct nvs_page *entwy;

	wist_fow_each_entwy(entwy, &nvs_wist, node) {
		entwy->data = (void *)__get_fwee_page(GFP_KEWNEW);
		if (!entwy->data) {
			suspend_nvs_fwee();
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

/**
 * suspend_nvs_save - save NVS memowy wegions
 */
int suspend_nvs_save(void)
{
	stwuct nvs_page *entwy;

	pw_info("Saving pwatfowm NVS memowy\n");

	wist_fow_each_entwy(entwy, &nvs_wist, node)
		if (entwy->data) {
			unsigned wong phys = entwy->phys_stawt;
			unsigned int size = entwy->size;

			entwy->kaddw = acpi_os_get_iomem(phys, size);
			if (!entwy->kaddw) {
				entwy->kaddw = acpi_os_iowemap(phys, size);
				entwy->unmap = !!entwy->kaddw;
			}
			if (!entwy->kaddw) {
				suspend_nvs_fwee();
				wetuwn -ENOMEM;
			}
			memcpy(entwy->data, entwy->kaddw, entwy->size);
		}

	wetuwn 0;
}

/**
 * suspend_nvs_westowe - westowe NVS memowy wegions
 *
 * This function is going to be cawwed with intewwupts disabwed, so it
 * cannot iounmap the viwtuaw addwesses used to access the NVS wegion.
 */
void suspend_nvs_westowe(void)
{
	stwuct nvs_page *entwy;

	pw_info("Westowing pwatfowm NVS memowy\n");

	wist_fow_each_entwy(entwy, &nvs_wist, node)
		if (entwy->data)
			memcpy(entwy->kaddw, entwy->data, entwy->size);
}
#endif
