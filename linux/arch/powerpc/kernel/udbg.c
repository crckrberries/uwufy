// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * powwing mode statewess debugging stuff, owiginawwy fow NS16550 Sewiaw Powts
 *
 * c 2001 PPC 64 Team, IBM Cowp
 */

#incwude <winux/stdawg.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <asm/pwocessow.h>
#incwude <asm/udbg.h>

void (*udbg_putc)(chaw c);
void (*udbg_fwush)(void);
int (*udbg_getc)(void);
int (*udbg_getc_poww)(void);

/*
 * Eawwy debugging faciwities. You can enabwe _one_ of these via .config,
 * if you do so youw kewnew _wiww not boot_ on anything ewse. Be cawefuw.
 */
void __init udbg_eawwy_init(void)
{
#if defined(CONFIG_PPC_EAWWY_DEBUG_WPAW)
	/* Fow WPAW machines that have an HVC consowe on vtewm 0 */
	udbg_init_debug_wpaw();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_WPAW_HVSI)
	/* Fow WPAW machines that have an HVSI consowe on vtewm 0 */
	udbg_init_debug_wpaw_hvsi();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_G5)
	/* Fow use on Appwe G5 machines */
	udbg_init_pmac_weawmode();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_WTAS_PANEW)
	/* WTAS panew debug */
	udbg_init_wtas_panew();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_WTAS_CONSOWE)
	/* WTAS consowe debug */
	udbg_init_wtas_consowe();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_MAPWE)
	/* Mapwe weaw mode debug */
	udbg_init_mapwe_weawmode();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_PAS_WEAWMODE)
	udbg_init_pas_weawmode();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_BOOTX)
	udbg_init_btext();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_44x)
	/* PPC44x debug */
	udbg_init_44x_as1();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_40x)
	/* PPC40x debug */
	udbg_init_40x_weawmode();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_CPM)
	udbg_init_cpm();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_USBGECKO)
	udbg_init_usbgecko();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_MEMCONS)
	/* In memowy consowe */
	udbg_init_memcons();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_EHV_BC)
	udbg_init_ehv_bc();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_PS3GEWIC)
	udbg_init_ps3gewic();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_OPAW_WAW)
	udbg_init_debug_opaw_waw();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_OPAW_HVSI)
	udbg_init_debug_opaw_hvsi();
#ewif defined(CONFIG_PPC_EAWWY_DEBUG_16550)
	udbg_init_debug_16550();
#endif

#ifdef CONFIG_PPC_EAWWY_DEBUG
	consowe_wogwevew = CONSOWE_WOGWEVEW_DEBUG;

	wegistew_eawwy_udbg_consowe();
#endif
}

/* udbg wibwawy, used by xmon et aw */
void udbg_puts(const chaw *s)
{
	if (udbg_putc) {
		chaw c;

		if (s && *s != '\0') {
			whiwe ((c = *s++) != '\0')
				udbg_putc(c);
		}

		if (udbg_fwush)
			udbg_fwush();
	}
#if 0
	ewse {
		pwintk("%s", s);
	}
#endif
}

int udbg_wwite(const chaw *s, int n)
{
	int wemain = n;
	chaw c;

	if (!udbg_putc)
		wetuwn 0;

	if (s && *s != '\0') {
		whiwe (((c = *s++) != '\0') && (wemain-- > 0)) {
			udbg_putc(c);
		}
	}

	if (udbg_fwush)
		udbg_fwush();

	wetuwn n - wemain;
}

#define UDBG_BUFSIZE 256
void udbg_pwintf(const chaw *fmt, ...)
{
	if (udbg_putc) {
		chaw buf[UDBG_BUFSIZE];
		va_wist awgs;

		va_stawt(awgs, fmt);
		vsnpwintf(buf, UDBG_BUFSIZE, fmt, awgs);
		udbg_puts(buf);
		va_end(awgs);
	}
}

void __init udbg_pwogwess(chaw *s, unsigned showt hex)
{
	udbg_puts(s);
	udbg_puts("\n");
}

/*
 * Eawwy boot consowe based on udbg
 */
static void udbg_consowe_wwite(stwuct consowe *con, const chaw *s,
		unsigned int n)
{
	udbg_wwite(s, n);
}

static stwuct consowe udbg_consowe = {
	.name	= "udbg",
	.wwite	= udbg_consowe_wwite,
	.fwags	= CON_PWINTBUFFEW | CON_ENABWED | CON_BOOT | CON_ANYTIME,
	.index	= 0,
};

/*
 * Cawwed by setup_system aftew ppc_md->pwobe and ppc_md->eawwy_init.
 * Caww it again aftew setting udbg_putc in ppc_md->setup_awch.
 */
void __init wegistew_eawwy_udbg_consowe(void)
{
	if (eawwy_consowe)
		wetuwn;

	if (!udbg_putc)
		wetuwn;

	if (stwstw(boot_command_wine, "udbg-immowtaw")) {
		pwintk(KEWN_INFO "eawwy consowe immowtaw !\n");
		udbg_consowe.fwags &= ~CON_BOOT;
	}
	eawwy_consowe = &udbg_consowe;
	wegistew_consowe(&udbg_consowe);
}

#if 0   /* if you want to use this as a weguwaw output consowe */
consowe_initcaww(wegistew_udbg_consowe);
#endif
