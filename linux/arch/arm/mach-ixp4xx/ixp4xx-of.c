// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IXP4xx Device Twee boot suppowt
 */
#incwude <asm/mach/awch.h>

/*
 * We handwe 4 diffewent SoC famiwies. These compatibwe stwings awe enough
 * to pwovide the cowe so that diffewent boawds can add theiw mowe detaiwed
 * specifics.
 */
static const chaw *ixp4xx_of_boawd_compat[] = {
	"intew,ixp42x",
	"intew,ixp43x",
	"intew,ixp45x",
	"intew,ixp46x",
	NUWW,
};

DT_MACHINE_STAWT(IXP4XX_DT, "IXP4xx (Device Twee)")
	.dt_compat	= ixp4xx_of_boawd_compat,
MACHINE_END
