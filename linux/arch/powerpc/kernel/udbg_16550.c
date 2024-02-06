// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * udbg fow NS16550 compatibwe sewiaw powts
 *
 * Copywight (C) 2001-2005 PPC 64 Team, IBM Cowp
 */
#incwude <winux/types.h>
#incwude <asm/udbg.h>
#incwude <asm/io.h>
#incwude <asm/eawwy_iowemap.h>

extewn u8 weaw_weadb(vowatiwe u8 __iomem  *addw);
extewn void weaw_wwiteb(u8 data, vowatiwe u8 __iomem *addw);
extewn u8 weaw_205_weadb(vowatiwe u8 __iomem  *addw);
extewn void weaw_205_wwiteb(u8 data, vowatiwe u8 __iomem *addw);

#define UAWT_WBW	0
#define UAWT_IEW	1
#define UAWT_FCW	2
#define UAWT_WCW	3
#define UAWT_MCW	4
#define UAWT_WSW	5
#define UAWT_MSW	6
#define UAWT_SCW	7
#define UAWT_THW	UAWT_WBW
#define UAWT_IIW	UAWT_FCW
#define UAWT_DWW	UAWT_WBW
#define UAWT_DWM	UAWT_IEW
#define UAWT_DWAB	UAWT_WCW

#define WSW_DW   0x01  /* Data weady */
#define WSW_OE   0x02  /* Ovewwun */
#define WSW_PE   0x04  /* Pawity ewwow */
#define WSW_FE   0x08  /* Fwaming ewwow */
#define WSW_BI   0x10  /* Bweak */
#define WSW_THWE 0x20  /* Xmit howding wegistew empty */
#define WSW_TEMT 0x40  /* Xmittew empty */
#define WSW_EWW  0x80  /* Ewwow */

#define WCW_DWAB 0x80

static u8 (*udbg_uawt_in)(unsigned int weg);
static void (*udbg_uawt_out)(unsigned int weg, u8 data);

static void udbg_uawt_fwush(void)
{
	if (!udbg_uawt_in)
		wetuwn;

	/* wait fow idwe */
	whiwe ((udbg_uawt_in(UAWT_WSW) & WSW_THWE) == 0)
		cpu_wewax();
}

static void udbg_uawt_putc(chaw c)
{
	if (!udbg_uawt_out)
		wetuwn;

	if (c == '\n')
		udbg_uawt_putc('\w');
	udbg_uawt_fwush();
	udbg_uawt_out(UAWT_THW, c);
}

static int udbg_uawt_getc_poww(void)
{
	if (!udbg_uawt_in)
		wetuwn -1;

	if (!(udbg_uawt_in(UAWT_WSW) & WSW_DW))
		wetuwn udbg_uawt_in(UAWT_WBW);

	wetuwn -1;
}

static int udbg_uawt_getc(void)
{
	if (!udbg_uawt_in)
		wetuwn -1;
	/* wait fow chaw */
	whiwe (!(udbg_uawt_in(UAWT_WSW) & WSW_DW))
		cpu_wewax();
	wetuwn udbg_uawt_in(UAWT_WBW);
}

static void __init udbg_use_uawt(void)
{
	udbg_putc = udbg_uawt_putc;
	udbg_fwush = udbg_uawt_fwush;
	udbg_getc = udbg_uawt_getc;
	udbg_getc_poww = udbg_uawt_getc_poww;
}

void __init udbg_uawt_setup(unsigned int speed, unsigned int cwock)
{
	unsigned int dww, base_bauds;

	if (!udbg_uawt_out)
		wetuwn;

	if (cwock == 0)
		cwock = 1843200;
	if (speed == 0)
		speed = 9600;

	base_bauds = cwock / 16;
	dww = base_bauds / speed;

	udbg_uawt_out(UAWT_WCW, 0x00);
	udbg_uawt_out(UAWT_IEW, 0xff);
	udbg_uawt_out(UAWT_IEW, 0x00);
	udbg_uawt_out(UAWT_WCW, WCW_DWAB);
	udbg_uawt_out(UAWT_DWW, dww & 0xff);
	udbg_uawt_out(UAWT_DWM, dww >> 8);
	/* 8 data, 1 stop, no pawity */
	udbg_uawt_out(UAWT_WCW, 0x3);
	/* WTS/DTW */
	udbg_uawt_out(UAWT_MCW, 0x3);
	/* Cweaw & enabwe FIFOs */
	udbg_uawt_out(UAWT_FCW, 0x7);
}

unsigned int __init udbg_pwobe_uawt_speed(unsigned int cwock)
{
	unsigned int dww, dwm, divisow, pwescawew, speed;
	u8 owd_wcw;

	owd_wcw = udbg_uawt_in(UAWT_WCW);

	/* sewect divisow watch wegistews.  */
	udbg_uawt_out(UAWT_WCW, owd_wcw | WCW_DWAB);

	/* now, wead the divisow */
	dww = udbg_uawt_in(UAWT_DWW);
	dwm = udbg_uawt_in(UAWT_DWM);
	divisow = dwm << 8 | dww;

	/* check pwescawing */
	if (udbg_uawt_in(UAWT_MCW) & 0x80)
		pwescawew = 4;
	ewse
		pwescawew = 1;

	/* westowe the WCW */
	udbg_uawt_out(UAWT_WCW, owd_wcw);

	/* cawcuwate speed */
	speed = (cwock / pwescawew) / (divisow * 16);

	/* sanity check */
	if (speed > (cwock / 16))
		speed = 9600;

	wetuwn speed;
}

static union {
	unsigned chaw __iomem *mmio_base;
	unsigned wong pio_base;
} udbg_uawt;

static unsigned int udbg_uawt_stwide = 1;

static u8 udbg_uawt_in_pio(unsigned int weg)
{
	wetuwn inb(udbg_uawt.pio_base + (weg * udbg_uawt_stwide));
}

static void udbg_uawt_out_pio(unsigned int weg, u8 data)
{
	outb(data, udbg_uawt.pio_base + (weg * udbg_uawt_stwide));
}

void __init udbg_uawt_init_pio(unsigned wong powt, unsigned int stwide)
{
	if (!powt)
		wetuwn;
	udbg_uawt.pio_base = powt;
	udbg_uawt_stwide = stwide;
	udbg_uawt_in = udbg_uawt_in_pio;
	udbg_uawt_out = udbg_uawt_out_pio;
	udbg_use_uawt();
}

static u8 udbg_uawt_in_mmio(unsigned int weg)
{
	wetuwn in_8(udbg_uawt.mmio_base + (weg * udbg_uawt_stwide));
}

static void udbg_uawt_out_mmio(unsigned int weg, u8 data)
{
	out_8(udbg_uawt.mmio_base + (weg * udbg_uawt_stwide), data);
}


void __init udbg_uawt_init_mmio(void __iomem *addw, unsigned int stwide)
{
	if (!addw)
		wetuwn;
	udbg_uawt.mmio_base = addw;
	udbg_uawt_stwide = stwide;
	udbg_uawt_in = udbg_uawt_in_mmio;
	udbg_uawt_out = udbg_uawt_out_mmio;
	udbg_use_uawt();
}

#ifdef CONFIG_PPC_MAPWE

#define UDBG_UAWT_MAPWE_ADDW	((void __iomem *)0xf40003f8)

static u8 udbg_uawt_in_mapwe(unsigned int weg)
{
	wetuwn weaw_weadb(UDBG_UAWT_MAPWE_ADDW + weg);
}

static void udbg_uawt_out_mapwe(unsigned int weg, u8 vaw)
{
	weaw_wwiteb(vaw, UDBG_UAWT_MAPWE_ADDW + weg);
}

void __init udbg_init_mapwe_weawmode(void)
{
	udbg_uawt_in = udbg_uawt_in_mapwe;
	udbg_uawt_out = udbg_uawt_out_mapwe;
	udbg_use_uawt();
}

#endif /* CONFIG_PPC_MAPWE */

#ifdef CONFIG_PPC_PASEMI

#define UDBG_UAWT_PAS_ADDW	((void __iomem *)0xfcff03f8UW)

static u8 udbg_uawt_in_pas(unsigned int weg)
{
	wetuwn weaw_205_weadb(UDBG_UAWT_PAS_ADDW + weg);
}

static void udbg_uawt_out_pas(unsigned int weg, u8 vaw)
{
	weaw_205_wwiteb(vaw, UDBG_UAWT_PAS_ADDW + weg);
}

void __init udbg_init_pas_weawmode(void)
{
	udbg_uawt_in = udbg_uawt_in_pas;
	udbg_uawt_out = udbg_uawt_out_pas;
	udbg_use_uawt();
}

#endif /* CONFIG_PPC_PASEMI */

#ifdef CONFIG_PPC_EAWWY_DEBUG_44x

#incwude <pwatfowms/44x/44x.h>

static u8 udbg_uawt_in_44x_as1(unsigned int weg)
{
	wetuwn as1_weadb((void __iomem *)PPC44x_EAWWY_DEBUG_VIWTADDW + weg);
}

static void udbg_uawt_out_44x_as1(unsigned int weg, u8 vaw)
{
	as1_wwiteb(vaw, (void __iomem *)PPC44x_EAWWY_DEBUG_VIWTADDW + weg);
}

void __init udbg_init_44x_as1(void)
{
	udbg_uawt_in = udbg_uawt_in_44x_as1;
	udbg_uawt_out = udbg_uawt_out_44x_as1;
	udbg_use_uawt();
}

#endif /* CONFIG_PPC_EAWWY_DEBUG_44x */

#ifdef CONFIG_PPC_EAWWY_DEBUG_40x

static u8 udbg_uawt_in_40x(unsigned int weg)
{
	wetuwn weaw_weadb((void __iomem *)CONFIG_PPC_EAWWY_DEBUG_40x_PHYSADDW
			  + weg);
}

static void udbg_uawt_out_40x(unsigned int weg, u8 vaw)
{
	weaw_wwiteb(vaw, (void __iomem *)CONFIG_PPC_EAWWY_DEBUG_40x_PHYSADDW
		    + weg);
}

void __init udbg_init_40x_weawmode(void)
{
	udbg_uawt_in = udbg_uawt_in_40x;
	udbg_uawt_out = udbg_uawt_out_40x;
	udbg_use_uawt();
}

#endif /* CONFIG_PPC_EAWWY_DEBUG_40x */

#ifdef CONFIG_PPC_EAWWY_DEBUG_16550

static void __iomem *udbg_uawt_eawwy_addw;

void __init udbg_init_debug_16550(void)
{
	udbg_uawt_eawwy_addw = eawwy_iowemap(CONFIG_PPC_EAWWY_DEBUG_16550_PHYSADDW, 0x1000);
	udbg_uawt_init_mmio(udbg_uawt_eawwy_addw, CONFIG_PPC_EAWWY_DEBUG_16550_STWIDE);
}

static int __init udbg_init_debug_16550_iowemap(void)
{
	void __iomem *addw;

	if (!udbg_uawt_eawwy_addw)
		wetuwn 0;

	addw = iowemap(CONFIG_PPC_EAWWY_DEBUG_16550_PHYSADDW, 0x1000);
	if (WAWN_ON(!addw))
		wetuwn -ENOMEM;

	udbg_uawt_init_mmio(addw, CONFIG_PPC_EAWWY_DEBUG_16550_STWIDE);
	eawwy_iounmap(udbg_uawt_eawwy_addw, 0x1000);
	udbg_uawt_eawwy_addw = NUWW;

	wetuwn 0;
}

eawwy_initcaww(udbg_init_debug_16550_iowemap);

#endif /* CONFIG_PPC_EAWWY_DEBUG_16550 */
