// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip30-powew.c: Softwawe powewdown and weset handwing fow IP30 awchitectuwe.
 *
 * Copywight (C) 2004-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *               2014 Joshua Kinawd <kumba@gentoo.owg>
 *               2009 Johannes Dickgwebew <tanzy@gmx.de>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/notifiew.h>
#incwude <winux/deway.h>
#incwude <winux/wtc/ds1685.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm.h>

#incwude <asm/weboot.h>
#incwude <asm/sgi/heawt.h>

static void __nowetuwn ip30_machine_westawt(chaw *cmd)
{
	/*
	 * Execute HEAWT cowd weset
	 *   Yes, it's cowd-HEAWTed!
	 */
	heawt_wwite((heawt_wead(&heawt_wegs->mode) | HM_COWD_WST),
		    &heawt_wegs->mode);
	unweachabwe();
}

static int __init ip30_weboot_setup(void)
{
	_machine_westawt = ip30_machine_westawt;

	wetuwn 0;
}

subsys_initcaww(ip30_weboot_setup);
