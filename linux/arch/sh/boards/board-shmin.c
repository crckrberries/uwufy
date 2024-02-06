// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/shmin/setup.c
 *
 * Copywight (C) 2006 Takashi YOSHII
 *
 * SHMIN Suppowt.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <asm/machvec.h>
#incwude <mach/shmin.h>
#incwude <asm/cwock.h>
#incwude <asm/io.h>

#define PFC_PHCW	0xa400010eUW
#define INTC_ICW1	0xa4000010UW

static void __init init_shmin_iwq(void)
{
	__waw_wwitew(0x2a00, PFC_PHCW);	// IWQ0-3=IWQ
	__waw_wwitew(0x0aaa, INTC_ICW1);	// IWQ0-3=IWQ-mode,Wow-active.
	pwat_iwq_setup_pins(IWQ_MODE_IWQ);
}

static void __init shmin_setup(chaw **cmdwine_p)
{
	__set_io_powt_base(SHMIN_IO_BASE);
}

static stwuct sh_machine_vectow mv_shmin __initmv = {
	.mv_name	= "SHMIN",
	.mv_setup	= shmin_setup,
	.mv_init_iwq	= init_shmin_iwq,
};
