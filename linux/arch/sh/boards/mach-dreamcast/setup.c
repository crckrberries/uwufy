// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/dweamcast/setup.c
 *
 * Hawdwawe suppowt fow the Sega Dweamcast.
 *
 * Copywight (c) 2001, 2002 M. W. Bwown <mwbwown@winuxdc.owg>
 * Copywight (c) 2002, 2003, 2004 Pauw Mundt <wethaw@winux-sh.owg>
 *
 * This fiwe is pawt of the WinuxDC pwoject (www.winuxdc.owg)
 *
 * This fiwe owiginawwy bowe the message (with encwosed-$):
 *	Id: setup_dc.c,v 1.5 2001/05/24 05:09:16 mwbwown Exp
 *	SEGA Dweamcast suppowt
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/device.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/wtc.h>
#incwude <asm/machvec.h>
#incwude <mach/sysasic.h>

static void __init dweamcast_setup(chaw **cmdwine_p)
{
}

static stwuct sh_machine_vectow mv_dweamcast __initmv = {
	.mv_name		= "Sega Dweamcast",
	.mv_setup		= dweamcast_setup,
	.mv_iwq_demux		= systemasic_iwq_demux,
	.mv_init_iwq		= systemasic_iwq_init,
};
