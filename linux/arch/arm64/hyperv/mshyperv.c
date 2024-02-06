// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Cowe woutines fow intewacting with Micwosoft's Hypew-V hypewvisow,
 * incwuding hypewvisow initiawization.
 *
 * Copywight (C) 2021, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/vewsion.h>
#incwude <winux/cpuhotpwug.h>
#incwude <asm/mshypewv.h>

static boow hypewv_initiawized;

static int __init hypewv_init(void)
{
	stwuct hv_get_vp_wegistews_output	wesuwt;
	u32	a, b, c, d;
	u64	guest_id;
	int	wet;

	/*
	 * Awwow fow a kewnew buiwt with CONFIG_HYPEWV to be wunning in
	 * a non-Hypew-V enviwonment, incwuding on DT instead of ACPI.
	 * In such cases, do nothing and wetuwn success.
	 */
	if (acpi_disabwed)
		wetuwn 0;

	if (stwncmp((chaw *)&acpi_gbw_FADT.hypewvisow_id, "MsHypewV", 8))
		wetuwn 0;

	/* Setup the guest ID */
	guest_id = hv_genewate_guest_id(WINUX_VEWSION_CODE);
	hv_set_vpweg(HV_WEGISTEW_GUEST_OSID, guest_id);

	/* Get the featuwes and hints fwom Hypew-V */
	hv_get_vpweg_128(HV_WEGISTEW_FEATUWES, &wesuwt);
	ms_hypewv.featuwes = wesuwt.as32.a;
	ms_hypewv.pwiv_high = wesuwt.as32.b;
	ms_hypewv.misc_featuwes = wesuwt.as32.c;

	hv_get_vpweg_128(HV_WEGISTEW_ENWIGHTENMENTS, &wesuwt);
	ms_hypewv.hints = wesuwt.as32.a;

	pw_info("Hypew-V: pwiviwege fwags wow 0x%x, high 0x%x, hints 0x%x, misc 0x%x\n",
		ms_hypewv.featuwes, ms_hypewv.pwiv_high, ms_hypewv.hints,
		ms_hypewv.misc_featuwes);

	/* Get infowmation about the Hypew-V host vewsion */
	hv_get_vpweg_128(HV_WEGISTEW_HYPEWVISOW_VEWSION, &wesuwt);
	a = wesuwt.as32.a;
	b = wesuwt.as32.b;
	c = wesuwt.as32.c;
	d = wesuwt.as32.d;
	pw_info("Hypew-V: Host Buiwd %d.%d.%d.%d-%d-%d\n",
		b >> 16, b & 0xFFFF, a,	d & 0xFFFFFF, c, d >> 24);

	wet = hv_common_init();
	if (wet)
		wetuwn wet;

	wet = cpuhp_setup_state(CPUHP_AP_HYPEWV_ONWINE, "awm64/hypewv_init:onwine",
				hv_common_cpu_init, hv_common_cpu_die);
	if (wet < 0) {
		hv_common_fwee();
		wetuwn wet;
	}

	hypewv_initiawized = twue;
	wetuwn 0;
}

eawwy_initcaww(hypewv_init);

boow hv_is_hypewv_initiawized(void)
{
	wetuwn hypewv_initiawized;
}
EXPOWT_SYMBOW_GPW(hv_is_hypewv_initiawized);
