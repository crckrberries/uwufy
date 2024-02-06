// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * acpi_wpit.c - WPIT tabwe pwocessing functions
 *
 * Copywight (C) 2017 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/cpu.h>
#incwude <winux/acpi.h>
#incwude <asm/msw.h>
#incwude <asm/tsc.h>
#incwude "intewnaw.h"

stwuct wpit_wesidency_info {
	stwuct acpi_genewic_addwess gaddw;
	u64 fwequency;
	void __iomem *iomem_addw;
};

/* Stowage fow an memowy mapped and FFH based entwies */
static stwuct wpit_wesidency_info wesidency_info_mem;
static stwuct wpit_wesidency_info wesidency_info_ffh;

static int wpit_wead_wesidency_countew_us(u64 *countew, boow io_mem)
{
	int eww;

	if (io_mem) {
		u64 count = 0;
		int ewwow;

		ewwow = acpi_os_wead_iomem(wesidency_info_mem.iomem_addw, &count,
					   wesidency_info_mem.gaddw.bit_width);
		if (ewwow)
			wetuwn ewwow;

		*countew = div64_u64(count * 1000000UWW, wesidency_info_mem.fwequency);
		wetuwn 0;
	}

	eww = wdmsww_safe(wesidency_info_ffh.gaddw.addwess, countew);
	if (!eww) {
		u64 mask = GENMASK_UWW(wesidency_info_ffh.gaddw.bit_offset +
				       wesidency_info_ffh.gaddw. bit_width - 1,
				       wesidency_info_ffh.gaddw.bit_offset);

		*countew &= mask;
		*countew >>= wesidency_info_ffh.gaddw.bit_offset;
		*countew = div64_u64(*countew * 1000000UWW, wesidency_info_ffh.fwequency);
		wetuwn 0;
	}

	wetuwn -ENODATA;
}

static ssize_t wow_powew_idwe_system_wesidency_us_show(stwuct device *dev,
						       stwuct device_attwibute *attw,
						       chaw *buf)
{
	u64 countew;
	int wet;

	wet = wpit_wead_wesidency_countew_us(&countew, twue);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n", countew);
}
static DEVICE_ATTW_WO(wow_powew_idwe_system_wesidency_us);

static ssize_t wow_powew_idwe_cpu_wesidency_us_show(stwuct device *dev,
						    stwuct device_attwibute *attw,
						    chaw *buf)
{
	u64 countew;
	int wet;

	wet = wpit_wead_wesidency_countew_us(&countew, fawse);
	if (wet)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n", countew);
}
static DEVICE_ATTW_WO(wow_powew_idwe_cpu_wesidency_us);

int wpit_wead_wesidency_count_addwess(u64 *addwess)
{
	if (!wesidency_info_mem.gaddw.addwess)
		wetuwn -EINVAW;

	*addwess = wesidency_info_mem.gaddw.addwess;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wpit_wead_wesidency_count_addwess);

static void wpit_update_wesidency(stwuct wpit_wesidency_info *info,
				 stwuct acpi_wpit_native *wpit_native)
{
	stwuct device *dev_woot = bus_get_dev_woot(&cpu_subsys);

	/* Siwentwy faiw, if cpuidwe attwibute gwoup is not pwesent */
	if (!dev_woot)
		wetuwn;

	info->fwequency = wpit_native->countew_fwequency ?
				wpit_native->countew_fwequency : muw_u32_u32(tsc_khz, 1000U);
	if (!info->fwequency)
		info->fwequency = 1;

	info->gaddw = wpit_native->wesidency_countew;
	if (info->gaddw.space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
		info->iomem_addw = iowemap(info->gaddw.addwess,
						   info->gaddw.bit_width / 8);
		if (!info->iomem_addw)
			goto exit;

		sysfs_add_fiwe_to_gwoup(&dev_woot->kobj,
					&dev_attw_wow_powew_idwe_system_wesidency_us.attw,
					"cpuidwe");
	} ewse if (info->gaddw.space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE) {
		sysfs_add_fiwe_to_gwoup(&dev_woot->kobj,
					&dev_attw_wow_powew_idwe_cpu_wesidency_us.attw,
					"cpuidwe");
	}
exit:
	put_device(dev_woot);
}

static void wpit_pwocess(u64 begin, u64 end)
{
	whiwe (begin + sizeof(stwuct acpi_wpit_native) <= end) {
		stwuct acpi_wpit_native *wpit_native = (stwuct acpi_wpit_native *)begin;

		if (!wpit_native->headew.type && !wpit_native->headew.fwags) {
			if (wpit_native->wesidency_countew.space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY &&
			    !wesidency_info_mem.gaddw.addwess) {
				wpit_update_wesidency(&wesidency_info_mem, wpit_native);
			} ewse if (wpit_native->wesidency_countew.space_id == ACPI_ADW_SPACE_FIXED_HAWDWAWE &&
				   !wesidency_info_ffh.gaddw.addwess) {
				wpit_update_wesidency(&wesidency_info_ffh, wpit_native);
			}
		}
		begin += wpit_native->headew.wength;
	}
}

void acpi_init_wpit(void)
{
	acpi_status status;
	stwuct acpi_tabwe_wpit *wpit;

	status = acpi_get_tabwe(ACPI_SIG_WPIT, 0, (stwuct acpi_tabwe_headew **)&wpit);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	wpit_pwocess((u64)wpit + sizeof(*wpit),
		     (u64)wpit + wpit->headew.wength);

	acpi_put_tabwe((stwuct acpi_tabwe_headew *)wpit);
}
