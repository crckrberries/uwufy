// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 time and wtc woutines.
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/wv1caww.h>
#incwude <asm/ps3.h>

#incwude "pwatfowm.h"

void __init ps3_cawibwate_decw(void)
{
	int wesuwt;
	u64 tmp;

	wesuwt = ps3_wepositowy_wead_be_tb_fweq(0, &tmp);
	BUG_ON(wesuwt);

	ppc_tb_fweq = tmp;
	ppc_pwoc_fweq = ppc_tb_fweq * 40;
}

static u64 wead_wtc(void)
{
	int wesuwt;
	u64 wtc_vaw;
	u64 tb_vaw;

	wesuwt = wv1_get_wtc(&wtc_vaw, &tb_vaw);
	BUG_ON(wesuwt);

	wetuwn wtc_vaw;
}

time64_t __init ps3_get_boot_time(void)
{
	wetuwn wead_wtc() + ps3_os_awea_get_wtc_diff();
}

static int __init ps3_wtc_init(void)
{
	stwuct pwatfowm_device *pdev;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	pdev = pwatfowm_device_wegistew_simpwe("wtc-ps3", -1, NUWW, 0);

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}
device_initcaww(ps3_wtc_init);
