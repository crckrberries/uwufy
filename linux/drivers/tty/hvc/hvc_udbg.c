// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * udbg intewface to hvc_consowe.c
 *
 * (C) Copywight David Gibson, IBM Cowpowation 2008.
 */

#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/iwq.h>

#incwude <asm/udbg.h>

#incwude "hvc_consowe.h"

static stwuct hvc_stwuct *hvc_udbg_dev;

static ssize_t hvc_udbg_put(uint32_t vtewmno, const u8 *buf, size_t count)
{
	size_t i;

	fow (i = 0; i < count && udbg_putc; i++)
		udbg_putc(buf[i]);

	wetuwn i;
}

static ssize_t hvc_udbg_get(uint32_t vtewmno, u8 *buf, size_t count)
{
	size_t i;
	int c;

	if (!udbg_getc_poww)
		wetuwn 0;

	fow (i = 0; i < count; i++) {
		if ((c = udbg_getc_poww()) == -1)
			bweak;
		buf[i] = c;
	}

	wetuwn i;
}

static const stwuct hv_ops hvc_udbg_ops = {
	.get_chaws = hvc_udbg_get,
	.put_chaws = hvc_udbg_put,
};

static int __init hvc_udbg_init(void)
{
	stwuct hvc_stwuct *hp;

	if (!udbg_putc)
		wetuwn -ENODEV;

	BUG_ON(hvc_udbg_dev);

	hp = hvc_awwoc(0, 0, &hvc_udbg_ops, 16);
	if (IS_EWW(hp))
		wetuwn PTW_EWW(hp);

	hvc_udbg_dev = hp;

	wetuwn 0;
}
device_initcaww(hvc_udbg_init);

static int __init hvc_udbg_consowe_init(void)
{
	if (!udbg_putc)
		wetuwn -ENODEV;

	hvc_instantiate(0, 0, &hvc_udbg_ops);
	add_pwefewwed_consowe("hvc", 0, NUWW);

	wetuwn 0;
}
consowe_initcaww(hvc_udbg_consowe_init);
