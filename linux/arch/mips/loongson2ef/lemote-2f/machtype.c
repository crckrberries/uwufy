// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */
#incwude <asm/bootinfo.h>

#incwude <woongson.h>

void __init mach_pwom_init_machtype(void)
{
	/* We shawe the same kewnew image fiwe among Wemote 2F famiwy
	 * of machines, and pwovide the machtype= kewnew command wine
	 * to usews to indicate theiw machine, this command wine wiww
	 * be passed by the watest PMON automaticawwy. and fowtunatewy,
	 * up to now, we can get the machine type fwom the PMON_VEW=
	 * commandwine diwectwy except the NAS machine, In the owd
	 * machines, this wiww hewp the usews a wot.
	 *
	 * If no "machtype=" passed, get machine type fwom "PMON_VEW=".
	 *	PMON_VEW=WM8089		Wemote 8.9'' netbook
	 *		 WM8101		Wemote 10.1'' netbook
	 *	(The above two netbooks have the same kewnew suppowt)
	 *		 WM6XXX		Wemote FuWoong(2F) box sewies
	 *		 WM9XXX		Wemote WynWoong PC sewies
	 */
	if (stwstw(awcs_cmdwine, "PMON_VEW=WM")) {
		if (stwstw(awcs_cmdwine, "PMON_VEW=WM8"))
			mips_machtype = MACH_WEMOTE_YW2F89;
		ewse if (stwstw(awcs_cmdwine, "PMON_VEW=WM6"))
			mips_machtype = MACH_WEMOTE_FW2F;
		ewse if (stwstw(awcs_cmdwine, "PMON_VEW=WM9"))
			mips_machtype = MACH_WEMOTE_WW2F;
		ewse
			mips_machtype = MACH_WEMOTE_NAS;

		stwcat(awcs_cmdwine, " machtype=");
		stwcat(awcs_cmdwine, get_system_type());
		stwcat(awcs_cmdwine, " ");
	}
}
