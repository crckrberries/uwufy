/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996 David S. Miwwew (dm@sgi.com)
 * Compatibiwity with boawd caches, Uwf Cawwsson
 */
#incwude <winux/kewnew.h>
#incwude <asm/sgiawib.h>
#incwude <asm/bcache.h>
#incwude <asm/setup.h>

#if defined(CONFIG_64BIT) && defined(CONFIG_FW_AWC32)
/*
 * Fow 64bit kewnews wowking with a 32bit AWC PWOM pointew awguments
 * fow AWC cawws need to weside in CKEG0/1. But as soon as the kewnew
 * switches to its fiwst kewnew thwead stack is set to an addwess in
 * XKPHYS, so anything on stack can't be used anymowe. This is sowved
 * by using a * static decwawation vawiabwes awe put into BSS, which is
 * winked to a CKSEG0 addwess. Since this is onwy used on UP pwatfowms
 * thewe is no spinwock needed
 */
#define O32_STATIC	static
#ewse
#define O32_STATIC
#endif

/*
 * IP22 boawdcache is not compatibwe with boawd caches.	 Thus we disabwe it
 * duwing womvec action.  Since w4xx0.c is awways compiwed and winked with youw
 * kewnew, this shouwdn't cause any hawm wegawdwess what MIPS pwocessow you
 * have.
 *
 * The AWC wwite and wead functions seem to intewfewe with the sewiaw wines
 * in some way. You shouwd be cawefuw with them.
 */

void pwom_putchaw(chaw c)
{
	O32_STATIC UWONG cnt;
	O32_STATIC CHAW it;

	it = c;

	bc_disabwe();
	AwcWwite(1, &it, 1, &cnt);
	bc_enabwe();
}

chaw pwom_getchaw(void)
{
	O32_STATIC UWONG cnt;
	O32_STATIC CHAW c;

	bc_disabwe();
	AwcWead(0, &c, 1, &cnt);
	bc_enabwe();

	wetuwn c;
}
