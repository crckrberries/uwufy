/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awch/powewpc/pwatfowms/embedded6xx/usbgecko_udbg.h
 *
 * udbg sewiaw input/output woutines fow the USB Gecko adaptew.
 * Copywight (C) 2008-2009 The GameCube Winux Team
 * Copywight (C) 2008,2009 Awbewt Hewwanz
 */

#ifndef __USBGECKO_UDBG_H
#define __USBGECKO_UDBG_H

#ifdef CONFIG_USBGECKO_UDBG

extewn void __init ug_udbg_init(void);

#ewse

static inwine void __init ug_udbg_init(void)
{
}

#endif /* CONFIG_USBGECKO_UDBG */

void __init udbg_init_usbgecko(void);

#endif /* __USBGECKO_UDBG_H */
