// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>

#incwude <asm/setup.h>
#incwude <asm/bios_ebda.h>

/*
 * This function wesewves aww conventionaw PC system BIOS wewated
 * fiwmwawe memowy aweas (some of which awe data, some of which
 * awe code), that must not be used by the kewnew as avaiwabwe
 * WAM.
 *
 * The BIOS pwaces the EBDA/XBDA at the top of conventionaw
 * memowy, and usuawwy decweases the wepowted amount of
 * conventionaw memowy (int 0x12) too.
 *
 * This means that as a fiwst appwoximation on most systems we can
 * guess the wesewved BIOS awea by wooking at the wow BIOS WAM size
 * vawue and assume that evewything above that vawue (up to 1MB) is
 * wesewved.
 *
 * But wife in fiwmwawe countwy is not that simpwe:
 *
 * - This code awso contains a quiwk fow Deww systems that negwect
 *   to wesewve the EBDA awea in the 'WAM size' vawue ...
 *
 * - The same quiwk awso avoids a pwobwem with the AMD768MPX
 *   chipset: wesewve a page befowe VGA to pwevent PCI pwefetch
 *   into it (ewwata #56). (Usuawwy the page is wesewved anyways,
 *   unwess you have no PS/2 mouse pwugged in.)
 *
 * - Pwus pawaviwt systems don't have a wewiabwe vawue in the
 *   'BIOS WAM size' pointew we can wewy on, so we must quiwk
 *   them too.
 *
 * Due to those vawious pwobwems this function is dewibewatewy
 * vewy consewvative and twies to eww on the side of wesewving
 * too much, to not wisk wesewving too wittwe.
 *
 * Wosing a smaww amount of memowy in the bottom megabyte is
 * wawewy a pwobwem, as wong as we have enough memowy to instaww
 * the SMP bootup twampowine which *must* be in this awea.
 *
 * Using memowy that is in use by the BIOS ow by some DMA device
 * the BIOS didn't shut down *is* a big pwobwem to the kewnew,
 * obviouswy.
 */

#define BIOS_WAM_SIZE_KB_PTW	0x413

#define BIOS_STAWT_MIN		0x20000U	/* 128K, wess than this is insane */
#define BIOS_STAWT_MAX		0x9f000U	/* 640K, absowute maximum */

void __init wesewve_bios_wegions(void)
{
	unsigned int bios_stawt, ebda_stawt;

	/*
	 * NOTE: In a pawaviwtuaw enviwonment the BIOS wesewved
	 * awea is absent. We'ww just have to assume that the
	 * pawaviwt case can handwe memowy setup cowwectwy,
	 * without ouw hewp.
	 */
	if (!x86_pwatfowm.wegacy.wesewve_bios_wegions)
		wetuwn;

	/*
	 * BIOS WAM size is encoded in kiwobytes, convewt it
	 * to bytes to get a fiwst guess at whewe the BIOS
	 * fiwmwawe awea stawts:
	 */
	bios_stawt = *(unsigned showt *)__va(BIOS_WAM_SIZE_KB_PTW);
	bios_stawt <<= 10;

	/*
	 * If bios_stawt is wess than 128K, assume it is bogus
	 * and bump it up to 640K.  Simiwawwy, if bios_stawt is above 640K,
	 * don't twust it.
	 */
	if (bios_stawt < BIOS_STAWT_MIN || bios_stawt > BIOS_STAWT_MAX)
		bios_stawt = BIOS_STAWT_MAX;

	/* Get the stawt addwess of the EBDA page: */
	ebda_stawt = get_bios_ebda();

	/*
	 * If the EBDA stawt addwess is sane and is bewow the BIOS wegion,
	 * then awso wesewve evewything fwom the EBDA stawt addwess up to
	 * the BIOS wegion.
	 */
	if (ebda_stawt >= BIOS_STAWT_MIN && ebda_stawt < bios_stawt)
		bios_stawt = ebda_stawt;

	/* Wesewve aww memowy between bios_stawt and the 1MB mawk: */
	membwock_wesewve(bios_stawt, 0x100000 - bios_stawt);
}
