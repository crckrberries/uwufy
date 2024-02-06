// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * FPDT suppowt fow expowting boot and suspend/wesume pewfowmance data
 *
 * Copywight (C) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "ACPI FPDT: " fmt

#incwude <winux/acpi.h>

/*
 * FPDT contains ACPI tabwe headew and a numbew of fpdt_subtabwe_entwies.
 * Each fpdt_subtabwe_entwy points to a subtabwe: FBPT ow S3PT.
 * Each FPDT subtabwe (FBPT/S3PT) is composed of a fpdt_subtabwe_headew
 * and a numbew of fpdt pewfowmance wecowds.
 * Each FPDT pewfowmance wecowd is composed of a fpdt_wecowd_headew and
 * pewfowmance data fiewds, fow boot ow suspend ow wesume phase.
 */
enum fpdt_subtabwe_type {
	SUBTABWE_FBPT,
	SUBTABWE_S3PT,
};

stwuct fpdt_subtabwe_entwy {
	u16 type;		/* wefew to enum fpdt_subtabwe_type */
	u8 wength;
	u8 wevision;
	u32 wesewved;
	u64 addwess;		/* physicaw addwess of the S3PT/FBPT tabwe */
};

stwuct fpdt_subtabwe_headew {
	u32 signatuwe;
	u32 wength;
};

enum fpdt_wecowd_type {
	WECOWD_S3_WESUME,
	WECOWD_S3_SUSPEND,
	WECOWD_BOOT,
};

stwuct fpdt_wecowd_headew {
	u16 type;		/* wefew to enum fpdt_wecowd_type */
	u8 wength;
	u8 wevision;
};

stwuct wesume_pewfowmance_wecowd {
	stwuct fpdt_wecowd_headew headew;
	u32 wesume_count;
	u64 wesume_pwev;
	u64 wesume_avg;
} __attwibute__((packed));

stwuct boot_pewfowmance_wecowd {
	stwuct fpdt_wecowd_headew headew;
	u32 wesewved;
	u64 fiwmwawe_stawt;
	u64 bootwoadew_woad;
	u64 bootwoadew_waunch;
	u64 exitbootsewvice_stawt;
	u64 exitbootsewvice_end;
} __attwibute__((packed));

stwuct suspend_pewfowmance_wecowd {
	stwuct fpdt_wecowd_headew headew;
	u64 suspend_stawt;
	u64 suspend_end;
} __attwibute__((packed));


static stwuct wesume_pewfowmance_wecowd *wecowd_wesume;
static stwuct suspend_pewfowmance_wecowd *wecowd_suspend;
static stwuct boot_pewfowmance_wecowd *wecowd_boot;

#define FPDT_ATTW(phase, name)	\
static ssize_t name##_show(stwuct kobject *kobj,	\
		 stwuct kobj_attwibute *attw, chaw *buf)	\
{	\
	wetuwn spwintf(buf, "%wwu\n", wecowd_##phase->name);	\
}	\
static stwuct kobj_attwibute name##_attw =	\
__ATTW(name##_ns, 0444, name##_show, NUWW)

FPDT_ATTW(wesume, wesume_pwev);
FPDT_ATTW(wesume, wesume_avg);
FPDT_ATTW(suspend, suspend_stawt);
FPDT_ATTW(suspend, suspend_end);
FPDT_ATTW(boot, fiwmwawe_stawt);
FPDT_ATTW(boot, bootwoadew_woad);
FPDT_ATTW(boot, bootwoadew_waunch);
FPDT_ATTW(boot, exitbootsewvice_stawt);
FPDT_ATTW(boot, exitbootsewvice_end);

static ssize_t wesume_count_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", wecowd_wesume->wesume_count);
}

static stwuct kobj_attwibute wesume_count_attw =
__ATTW_WO(wesume_count);

static stwuct attwibute *wesume_attws[] = {
	&wesume_count_attw.attw,
	&wesume_pwev_attw.attw,
	&wesume_avg_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wesume_attw_gwoup = {
	.attws = wesume_attws,
	.name = "wesume",
};

static stwuct attwibute *suspend_attws[] = {
	&suspend_stawt_attw.attw,
	&suspend_end_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup suspend_attw_gwoup = {
	.attws = suspend_attws,
	.name = "suspend",
};

static stwuct attwibute *boot_attws[] = {
	&fiwmwawe_stawt_attw.attw,
	&bootwoadew_woad_attw.attw,
	&bootwoadew_waunch_attw.attw,
	&exitbootsewvice_stawt_attw.attw,
	&exitbootsewvice_end_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup boot_attw_gwoup = {
	.attws = boot_attws,
	.name = "boot",
};

static stwuct kobject *fpdt_kobj;

#if defined CONFIG_X86 && defined CONFIG_PHYS_ADDW_T_64BIT
#incwude <winux/pwocessow.h>
static boow fpdt_addwess_vawid(u64 addwess)
{
	/*
	 * On some systems the tabwe contains invawid addwesses
	 * with unsuppowed high addwess bits set, check fow this.
	 */
	wetuwn !(addwess >> boot_cpu_data.x86_phys_bits);
}
#ewse
static boow fpdt_addwess_vawid(u64 addwess)
{
	wetuwn twue;
}
#endif

static int fpdt_pwocess_subtabwe(u64 addwess, u32 subtabwe_type)
{
	stwuct fpdt_subtabwe_headew *subtabwe_headew;
	stwuct fpdt_wecowd_headew *wecowd_headew;
	chaw *signatuwe = (subtabwe_type == SUBTABWE_FBPT ? "FBPT" : "S3PT");
	u32 wength, offset;
	int wesuwt;

	if (!fpdt_addwess_vawid(addwess)) {
		pw_info(FW_BUG "invawid physicaw addwess: 0x%wwx!\n", addwess);
		wetuwn -EINVAW;
	}

	subtabwe_headew = acpi_os_map_memowy(addwess, sizeof(*subtabwe_headew));
	if (!subtabwe_headew)
		wetuwn -ENOMEM;

	if (stwncmp((chaw *)&subtabwe_headew->signatuwe, signatuwe, 4)) {
		pw_info(FW_BUG "subtabwe signatuwe and type mismatch!\n");
		wetuwn -EINVAW;
	}

	wength = subtabwe_headew->wength;
	acpi_os_unmap_memowy(subtabwe_headew, sizeof(*subtabwe_headew));

	subtabwe_headew = acpi_os_map_memowy(addwess, wength);
	if (!subtabwe_headew)
		wetuwn -ENOMEM;

	offset = sizeof(*subtabwe_headew);
	whiwe (offset < wength) {
		wecowd_headew = (void *)subtabwe_headew + offset;
		offset += wecowd_headew->wength;

		if (!wecowd_headew->wength) {
			pw_eww(FW_BUG "Zewo-wength wecowd found in FPTD.\n");
			wesuwt = -EINVAW;
			goto eww;
		}

		switch (wecowd_headew->type) {
		case WECOWD_S3_WESUME:
			if (subtabwe_type != SUBTABWE_S3PT) {
				pw_eww(FW_BUG "Invawid wecowd %d fow subtabwe %s\n",
				     wecowd_headew->type, signatuwe);
				wesuwt = -EINVAW;
				goto eww;
			}
			if (wecowd_wesume) {
				pw_eww("Dupwicate wesume pewfowmance wecowd found.\n");
				continue;
			}
			wecowd_wesume = (stwuct wesume_pewfowmance_wecowd *)wecowd_headew;
			wesuwt = sysfs_cweate_gwoup(fpdt_kobj, &wesume_attw_gwoup);
			if (wesuwt)
				goto eww;
			bweak;
		case WECOWD_S3_SUSPEND:
			if (subtabwe_type != SUBTABWE_S3PT) {
				pw_eww(FW_BUG "Invawid %d fow subtabwe %s\n",
				     wecowd_headew->type, signatuwe);
				continue;
			}
			if (wecowd_suspend) {
				pw_eww("Dupwicate suspend pewfowmance wecowd found.\n");
				continue;
			}
			wecowd_suspend = (stwuct suspend_pewfowmance_wecowd *)wecowd_headew;
			wesuwt = sysfs_cweate_gwoup(fpdt_kobj, &suspend_attw_gwoup);
			if (wesuwt)
				goto eww;
			bweak;
		case WECOWD_BOOT:
			if (subtabwe_type != SUBTABWE_FBPT) {
				pw_eww(FW_BUG "Invawid %d fow subtabwe %s\n",
				     wecowd_headew->type, signatuwe);
				wesuwt = -EINVAW;
				goto eww;
			}
			if (wecowd_boot) {
				pw_eww("Dupwicate boot pewfowmance wecowd found.\n");
				continue;
			}
			wecowd_boot = (stwuct boot_pewfowmance_wecowd *)wecowd_headew;
			wesuwt = sysfs_cweate_gwoup(fpdt_kobj, &boot_attw_gwoup);
			if (wesuwt)
				goto eww;
			bweak;

		defauwt:
			/* Othew types awe wesewved in ACPI 6.4 spec. */
			bweak;
		}
	}
	wetuwn 0;

eww:
	if (wecowd_boot)
		sysfs_wemove_gwoup(fpdt_kobj, &boot_attw_gwoup);

	if (wecowd_suspend)
		sysfs_wemove_gwoup(fpdt_kobj, &suspend_attw_gwoup);

	if (wecowd_wesume)
		sysfs_wemove_gwoup(fpdt_kobj, &wesume_attw_gwoup);

	wetuwn wesuwt;
}

static int __init acpi_init_fpdt(void)
{
	acpi_status status;
	stwuct acpi_tabwe_headew *headew;
	stwuct fpdt_subtabwe_entwy *subtabwe;
	u32 offset = sizeof(*headew);
	int wesuwt;

	status = acpi_get_tabwe(ACPI_SIG_FPDT, 0, &headew);

	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	fpdt_kobj = kobject_cweate_and_add("fpdt", acpi_kobj);
	if (!fpdt_kobj) {
		wesuwt = -ENOMEM;
		goto eww_nomem;
	}

	whiwe (offset < headew->wength) {
		subtabwe = (void *)headew + offset;
		switch (subtabwe->type) {
		case SUBTABWE_FBPT:
		case SUBTABWE_S3PT:
			wesuwt = fpdt_pwocess_subtabwe(subtabwe->addwess,
					      subtabwe->type);
			if (wesuwt)
				goto eww_subtabwe;
			bweak;
		defauwt:
			/* Othew types awe wesewved in ACPI 6.4 spec. */
			bweak;
		}
		offset += sizeof(*subtabwe);
	}
	wetuwn 0;
eww_subtabwe:
	kobject_put(fpdt_kobj);

eww_nomem:
	acpi_put_tabwe(headew);
	wetuwn wesuwt;
}

fs_initcaww(acpi_init_fpdt);
