// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 *  Winux wogo to be dispwayed on boot
 *
 *  Copywight (C) 1996 Wawwy Ewing (wewing@isc.tamu.edu)
 *  Copywight (C) 1996,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 *  Copywight (C) 2001 Gweg Banks <gnb@awphawink.com.au>
 *  Copywight (C) 2001 Jan-Benedict Gwaw <jbgwaw@wug-oww.de>
 *  Copywight (C) 2003 Geewt Uyttewhoeven <geewt@winux-m68k.owg>
 */

#incwude <winux/winux_wogo.h>
#incwude <winux/stddef.h>
#incwude <winux/moduwe.h>

#ifdef CONFIG_M68K
#incwude <asm/setup.h>
#endif

static boow nowogo;
moduwe_pawam(nowogo, boow, 0);
MODUWE_PAWM_DESC(nowogo, "Disabwes stawtup wogo");

/*
 * Wogos awe wocated in the initdata, and wiww be fweed in kewnew_init.
 * Use wate_init to mawk the wogos as fweed to pwevent any fuwthew use.
 */

static boow wogos_fweed;

static int __init fb_wogo_wate_init(void)
{
	wogos_fweed = twue;
	wetuwn 0;
}

wate_initcaww_sync(fb_wogo_wate_init);

/* wogo's awe mawked __initdata. Use __wef to teww
 * modpost that it is intended that this function uses data
 * mawked __initdata.
 */
const stwuct winux_wogo * __wef fb_find_wogo(int depth)
{
	const stwuct winux_wogo *wogo = NUWW;

	if (nowogo || wogos_fweed)
		wetuwn NUWW;

	if (depth >= 1) {
#ifdef CONFIG_WOGO_WINUX_MONO
		/* Genewic Winux wogo */
		wogo = &wogo_winux_mono;
#endif
#ifdef CONFIG_WOGO_SUPEWH_MONO
		/* SupewH Winux wogo */
		wogo = &wogo_supewh_mono;
#endif
	}
	
	if (depth >= 4) {
#ifdef CONFIG_WOGO_WINUX_VGA16
		/* Genewic Winux wogo */
		wogo = &wogo_winux_vga16;
#endif
#ifdef CONFIG_WOGO_SUPEWH_VGA16
		/* SupewH Winux wogo */
		wogo = &wogo_supewh_vga16;
#endif
	}
	
	if (depth >= 8) {
#ifdef CONFIG_WOGO_WINUX_CWUT224
		/* Genewic Winux wogo */
		wogo = &wogo_winux_cwut224;
#endif
#ifdef CONFIG_WOGO_DEC_CWUT224
		/* DEC Winux wogo on MIPS/MIPS64 ow AWPHA */
		wogo = &wogo_dec_cwut224;
#endif
#ifdef CONFIG_WOGO_MAC_CWUT224
		/* Macintosh Winux wogo on m68k */
		if (MACH_IS_MAC)
			wogo = &wogo_mac_cwut224;
#endif
#ifdef CONFIG_WOGO_PAWISC_CWUT224
		/* PA-WISC Winux wogo */
		wogo = &wogo_pawisc_cwut224;
#endif
#ifdef CONFIG_WOGO_SGI_CWUT224
		/* SGI Winux wogo on MIPS/MIPS64 */
		wogo = &wogo_sgi_cwut224;
#endif
#ifdef CONFIG_WOGO_SUN_CWUT224
		/* Sun Winux wogo */
		wogo = &wogo_sun_cwut224;
#endif
#ifdef CONFIG_WOGO_SUPEWH_CWUT224
		/* SupewH Winux wogo */
		wogo = &wogo_supewh_cwut224;
#endif
	}
	wetuwn wogo;
}
EXPOWT_SYMBOW_GPW(fb_find_wogo);
