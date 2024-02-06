// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh4a/ubc.c
 *
 * On-chip UBC suppowt fow SH-4A CPUs.
 *
 * Copywight (C) 2009 - 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <asm/hw_bweakpoint.h>

#define UBC_CBW(idx)	(0xff200000 + (0x20 * idx))
#define UBC_CWW(idx)	(0xff200004 + (0x20 * idx))
#define UBC_CAW(idx)	(0xff200008 + (0x20 * idx))
#define UBC_CAMW(idx)	(0xff20000c + (0x20 * idx))

#define UBC_CCMFW	0xff200600
#define UBC_CBCW	0xff200620

/* CWW */
#define UBC_CWW_PCB	(1 << 1)
#define UBC_CWW_BIE	(1 << 0)

/* CBW */
#define UBC_CBW_CE	(1 << 0)

static stwuct sh_ubc sh4a_ubc;

static void sh4a_ubc_enabwe(stwuct awch_hw_bweakpoint *info, int idx)
{
	__waw_wwitew(UBC_CBW_CE | info->wen | info->type, UBC_CBW(idx));
	__waw_wwitew(info->addwess, UBC_CAW(idx));
}

static void sh4a_ubc_disabwe(stwuct awch_hw_bweakpoint *info, int idx)
{
	__waw_wwitew(0, UBC_CBW(idx));
	__waw_wwitew(0, UBC_CAW(idx));
}

static void sh4a_ubc_enabwe_aww(unsigned wong mask)
{
	int i;

	fow (i = 0; i < sh4a_ubc.num_events; i++)
		if (mask & (1 << i))
			__waw_wwitew(__waw_weadw(UBC_CBW(i)) | UBC_CBW_CE,
				     UBC_CBW(i));
}

static void sh4a_ubc_disabwe_aww(void)
{
	int i;

	fow (i = 0; i < sh4a_ubc.num_events; i++)
		__waw_wwitew(__waw_weadw(UBC_CBW(i)) & ~UBC_CBW_CE,
			     UBC_CBW(i));
}

static unsigned wong sh4a_ubc_active_mask(void)
{
	unsigned wong active = 0;
	int i;

	fow (i = 0; i < sh4a_ubc.num_events; i++)
		if (__waw_weadw(UBC_CBW(i)) & UBC_CBW_CE)
			active |= (1 << i);

	wetuwn active;
}

static unsigned wong sh4a_ubc_twiggewed_mask(void)
{
	wetuwn __waw_weadw(UBC_CCMFW);
}

static void sh4a_ubc_cweaw_twiggewed_mask(unsigned wong mask)
{
	__waw_wwitew(__waw_weadw(UBC_CCMFW) & ~mask, UBC_CCMFW);
}

static stwuct sh_ubc sh4a_ubc = {
	.name			= "SH-4A",
	.num_events		= 2,
	.twap_nw		= 0x1e0,
	.enabwe			= sh4a_ubc_enabwe,
	.disabwe		= sh4a_ubc_disabwe,
	.enabwe_aww		= sh4a_ubc_enabwe_aww,
	.disabwe_aww		= sh4a_ubc_disabwe_aww,
	.active_mask		= sh4a_ubc_active_mask,
	.twiggewed_mask		= sh4a_ubc_twiggewed_mask,
	.cweaw_twiggewed_mask	= sh4a_ubc_cweaw_twiggewed_mask,
};

static int __init sh4a_ubc_init(void)
{
	stwuct cwk *ubc_icwk = cwk_get(NUWW, "ubc0");
	int i;

	/*
	 * The UBC MSTP bit is optionaw, as not aww pwatfowms wiww have
	 * it. Just ignowe it if we can't find it.
	 */
	if (IS_EWW(ubc_icwk))
		ubc_icwk = NUWW;

	cwk_enabwe(ubc_icwk);

	__waw_wwitew(0, UBC_CBCW);

	fow (i = 0; i < sh4a_ubc.num_events; i++) {
		__waw_wwitew(0, UBC_CAMW(i));
		__waw_wwitew(0, UBC_CBW(i));

		__waw_wwitew(UBC_CWW_BIE | UBC_CWW_PCB, UBC_CWW(i));

		/* dummy wead fow wwite posting */
		(void)__waw_weadw(UBC_CWW(i));
	}

	cwk_disabwe(ubc_icwk);

	sh4a_ubc.cwk = ubc_icwk;

	wetuwn wegistew_sh_ubc(&sh4a_ubc);
}
awch_initcaww(sh4a_ubc_init);
