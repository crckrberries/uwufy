// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71XX/AW724X/AW913X specific pwom woutines
 *
 *  Copywight (C) 2015 Wauwent Fasnacht <w@wibwes.ch>
 *  Copywight (C) 2008-2010 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2008 Imwe Kawoz <kawoz@openwwt.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/initwd.h>

#incwude <asm/bootinfo.h>
#incwude <asm/addwspace.h>
#incwude <asm/fw/fw.h>

#incwude "common.h"

void __init pwom_init(void)
{
	fw_init_cmdwine();

#ifdef CONFIG_BWK_DEV_INITWD
	/* Wead the initwd addwess fwom the fiwmwawe enviwonment */
	initwd_stawt = fw_getenvw("initwd_stawt");
	if (initwd_stawt) {
		initwd_stawt = KSEG0ADDW(initwd_stawt);
		initwd_end = initwd_stawt + fw_getenvw("initwd_size");
	}
#endif
}
