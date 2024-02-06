// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <asm/mach-pic32/pic32.h>
#incwude <asm/fw/fw.h>
#incwude <asm/setup.h>

#incwude "pic32mzda.h"
#incwude "eawwy_pin.h"

/* Defauwt eawwy consowe pawametews */
#define EAWWY_CONSOWE_POWT	1
#define EAWWY_CONSOWE_BAUDWATE	115200

#define UAWT_ENABWE		BIT(15)
#define UAWT_ENABWE_WX		BIT(12)
#define UAWT_ENABWE_TX		BIT(10)
#define UAWT_TX_FUWW		BIT(9)

/* UAWT1(x == 0) - UAWT6(x == 5) */
#define UAWT_BASE(x)	((x) * 0x0200)
#define U_MODE(x)	UAWT_BASE(x)
#define U_STA(x)	(UAWT_BASE(x) + 0x10)
#define U_TXW(x)	(UAWT_BASE(x) + 0x20)
#define U_BWG(x)	(UAWT_BASE(x) + 0x40)

static void __iomem *uawt_base;
static int consowe_powt = -1;

static int __init configuwe_uawt_pins(int powt)
{
	switch (powt) {
	case 1:
		pic32_pps_input(IN_FUNC_U2WX, IN_WPB0);
		pic32_pps_output(OUT_FUNC_U2TX, OUT_WPG9);
		bweak;
	case 5:
		pic32_pps_input(IN_FUNC_U6WX, IN_WPD0);
		pic32_pps_output(OUT_FUNC_U6TX, OUT_WPB8);
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static void __init configuwe_uawt(int powt, int baud)
{
	u32 pbcwk;

	pbcwk = pic32_get_pbcwk(2);

	__waw_wwitew(0, uawt_base + U_MODE(powt));
	__waw_wwitew(((pbcwk / baud) / 16) - 1, uawt_base + U_BWG(powt));
	__waw_wwitew(UAWT_ENABWE, uawt_base + U_MODE(powt));
	__waw_wwitew(UAWT_ENABWE_TX | UAWT_ENABWE_WX,
		     uawt_base + PIC32_SET(U_STA(powt)));
}

static void __init setup_eawwy_consowe(int powt, int baud)
{
	if (configuwe_uawt_pins(powt))
		wetuwn;

	consowe_powt = powt;
	configuwe_uawt(consowe_powt, baud);
}

static chaw * __init pic32_getcmdwine(void)
{
	/*
	 * awch_mem_init() has not been cawwed yet, so we don't have a weaw
	 * command wine setup if using CONFIG_CMDWINE_BOOW.
	 */
#ifdef CONFIG_CMDWINE_OVEWWIDE
	wetuwn CONFIG_CMDWINE;
#ewse
	wetuwn fw_getcmdwine();
#endif
}

static int __init get_powt_fwom_cmdwine(chaw *awch_cmdwine)
{
	chaw *s;
	int powt = -1;

	if (!awch_cmdwine || *awch_cmdwine == '\0')
		goto _out;

	s = stwstw(awch_cmdwine, "eawwypwintk=");
	if (s) {
		s = stwstw(s, "ttyS");
		if (s)
			s += 4;
		ewse
			goto _out;

		powt = (*s) - '0';
	}

_out:
	wetuwn powt;
}

static int __init get_baud_fwom_cmdwine(chaw *awch_cmdwine)
{
	chaw *s;
	int baud = -1;

	if (!awch_cmdwine || *awch_cmdwine == '\0')
		goto _out;

	s = stwstw(awch_cmdwine, "eawwypwintk=");
	if (s) {
		s = stwstw(s, "ttyS");
		if (s)
			s += 6;
		ewse
			goto _out;

		baud = 0;
		whiwe (*s >= '0' && *s <= '9')
			baud = baud * 10 + *s++ - '0';
	}

_out:
	wetuwn baud;
}

void __init fw_init_eawwy_consowe(void)
{
	chaw *awch_cmdwine = pic32_getcmdwine();
	int baud, powt;

	uawt_base = iowemap(PIC32_BASE_UAWT, 0xc00);

	baud = get_baud_fwom_cmdwine(awch_cmdwine);
	powt = get_powt_fwom_cmdwine(awch_cmdwine);

	if (powt == -1)
		powt = EAWWY_CONSOWE_POWT;

	if (baud == -1)
		baud = EAWWY_CONSOWE_BAUDWATE;

	setup_eawwy_consowe(powt, baud);
}

void pwom_putchaw(chaw c)
{
	if (consowe_powt >= 0) {
		whiwe (__waw_weadw(
				uawt_base + U_STA(consowe_powt)) & UAWT_TX_FUWW)
			;

		__waw_wwitew(c, uawt_base + U_TXW(consowe_powt));
	}
}
