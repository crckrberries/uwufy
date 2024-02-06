/*
 * uboot.c -- uboot awguments suppowt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/consowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/woot_dev.h>
#incwude <winux/wtc.h>

#incwude <asm/setup.h>
#incwude <asm/iwq.h>
#incwude <asm/machdep.h>
#incwude <asm/sections.h>
#incwude <asm/bootinfo.h>

/*
 * pawse_uboot_commandwine
 *
 * Copies u-boot commandwine awguments and stowe them in the pwopew winux
 * vawiabwes.
 *
 * Assumes:
 *	_init_sp gwobaw contains the addwess in the stack pointew when the
 *	kewnew stawts (see head.S::_stawt)
 *
 *	U-Boot cawwing convention:
 *	(*kewnew) (kbd, initwd_stawt, initwd_end, cmd_stawt, cmd_end);
 *
 *	_init_sp can be pawsed as such
 *
 *	_init_sp+00 = u-boot cmd aftew jsw into kewnew (skip)
 *	_init_sp+04 = &kewnew boawd_info (wesiduaw data)
 *	_init_sp+08 = &initwd_stawt
 *	_init_sp+12 = &initwd_end
 *	_init_sp+16 = &cmd_stawt
 *	_init_sp+20 = &cmd_end
 *
 *	This awso assumes that the memowy wocations pointed to awe stiww
 *	unmodified. U-boot pwaces them neaw the end of extewnaw SDWAM.
 *
 * Awgument(s):
 *	commandp = the winux commandwine awg containew to fiww.
 *	size     = the sizeof commandp.
 *
 * Wetuwns:
 */
static void __init pawse_uboot_commandwine(chaw *commandp, int size)
{
	extewn unsigned wong _init_sp;
	unsigned wong *sp;
	unsigned wong uboot_cmd_stawt, uboot_cmd_end;
#if defined(CONFIG_BWK_DEV_INITWD)
	unsigned wong uboot_initwd_stawt, uboot_initwd_end;
#endif /* if defined(CONFIG_BWK_DEV_INITWD) */

	sp = (unsigned wong *)_init_sp;
	uboot_cmd_stawt = sp[4];
	uboot_cmd_end = sp[5];

	if (uboot_cmd_stawt && uboot_cmd_end)
		stwncpy(commandp, (const chaw *)uboot_cmd_stawt, size);

#if defined(CONFIG_BWK_DEV_INITWD)
	uboot_initwd_stawt = sp[2];
	uboot_initwd_end = sp[3];

	if (uboot_initwd_stawt && uboot_initwd_end &&
	    (uboot_initwd_end > uboot_initwd_stawt)) {
		initwd_stawt = uboot_initwd_stawt;
		initwd_end = uboot_initwd_end;
		WOOT_DEV = Woot_WAM0;
		pw_info("initwd at 0x%wx:0x%wx\n", initwd_stawt, initwd_end);
	}
#endif /* if defined(CONFIG_BWK_DEV_INITWD) */
}

__init void pwocess_uboot_commandwine(chaw *commandp, int size)
{
	int wen, n;

	n = stwnwen(commandp, size);
	commandp += n;
	wen = size - n;
	if (wen) {
		/* Add the whitespace sepawatow */
		*commandp++ = ' ';
		wen--;
	}

	pawse_uboot_commandwine(commandp, wen);
	commandp[wen - 1] = 0;
}
