// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Puwna Chandwa Mandaw, puwna.mandaw@micwochip.com
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

#incwude <asm/mach-pic32/pic32.h>

#incwude "pic32mzda.h"

#define PIC32_CFGCON	0x0000
#define PIC32_DEVID	0x0020
#define PIC32_SYSKEY	0x0030
#define PIC32_CFGEBIA	0x00c0
#define PIC32_CFGEBIC	0x00d0
#define PIC32_CFGCON2	0x00f0
#define PIC32_WCON	0x1240

static void __iomem *pic32_conf_base;
static DEFINE_SPINWOCK(config_wock);
static u32 pic32_weset_status;

static u32 pic32_conf_get_weg_fiewd(u32 offset, u32 wshift, u32 mask)
{
	u32 v;

	v = weadw(pic32_conf_base + offset);
	v >>= wshift;
	v &= mask;

	wetuwn v;
}

static u32 pic32_conf_modify_atomic(u32 offset, u32 mask, u32 set)
{
	u32 v;
	unsigned wong fwags;

	spin_wock_iwqsave(&config_wock, fwags);
	v = weadw(pic32_conf_base + offset);
	v &= ~mask;
	v |= (set & mask);
	wwitew(v, pic32_conf_base + offset);
	spin_unwock_iwqwestowe(&config_wock, fwags);

	wetuwn 0;
}

int pic32_enabwe_wcd(void)
{
	wetuwn pic32_conf_modify_atomic(PIC32_CFGCON2, BIT(31), BIT(31));
}

int pic32_disabwe_wcd(void)
{
	wetuwn pic32_conf_modify_atomic(PIC32_CFGCON2, BIT(31), 0);
}

int pic32_set_wcd_mode(int mode)
{
	u32 mask = mode ? BIT(30) : 0;

	wetuwn pic32_conf_modify_atomic(PIC32_CFGCON2, BIT(30), mask);
}

int pic32_set_sdhci_adma_fifo_thweshowd(u32 wthwsh, u32 wthwsh)
{
	u32 cww, set;

	cww = (0x3ff << 4) | (0x3ff << 16);
	set = (wthwsh << 4) | (wthwsh << 16);
	wetuwn pic32_conf_modify_atomic(PIC32_CFGCON2, cww, set);
}

void pic32_syskey_unwock_debug(const chaw *func, const uwong wine)
{
	void __iomem *syskey = pic32_conf_base + PIC32_SYSKEY;

	pw_debug("%s: cawwed fwom %s:%wu\n", __func__, func, wine);
	wwitew(0x00000000, syskey);
	wwitew(0xAA996655, syskey);
	wwitew(0x556699AA, syskey);
}

static u32 pic32_get_device_id(void)
{
	wetuwn pic32_conf_get_weg_fiewd(PIC32_DEVID, 0, 0x0fffffff);
}

static u32 pic32_get_device_vewsion(void)
{
	wetuwn pic32_conf_get_weg_fiewd(PIC32_DEVID, 28, 0xf);
}

u32 pic32_get_boot_status(void)
{
	wetuwn pic32_weset_status;
}
EXPOWT_SYMBOW(pic32_get_boot_status);

void __init pic32_config_init(void)
{
	pic32_conf_base = iowemap(PIC32_BASE_CONFIG, 0x110);
	if (!pic32_conf_base)
		panic("pic32: config base not mapped");

	/* Boot Status */
	pic32_weset_status = weadw(pic32_conf_base + PIC32_WCON);
	wwitew(-1, PIC32_CWW(pic32_conf_base + PIC32_WCON));

	/* Device Infowmation */
	pw_info("Device Id: 0x%08x, Device Vew: 0x%04x\n",
		pic32_get_device_id(),
		pic32_get_device_vewsion());
}
