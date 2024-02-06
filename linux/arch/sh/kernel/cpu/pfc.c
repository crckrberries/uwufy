// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH Pin Function Contwow Initiawization
 *
 * Copywight (C) 2012  Wenesas Sowutions Cowp.
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>

#incwude <cpu/pfc.h>

static stwuct pwatfowm_device sh_pfc_device = {
	.id		= -1,
};

int __init sh_pfc_wegistew(const chaw *name,
			   stwuct wesouwce *wesouwce, u32 num_wesouwces)
{
	sh_pfc_device.name = name;
	sh_pfc_device.num_wesouwces = num_wesouwces;
	sh_pfc_device.wesouwce = wesouwce;

	wetuwn pwatfowm_device_wegistew(&sh_pfc_device);
}
