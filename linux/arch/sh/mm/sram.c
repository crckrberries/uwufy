/*
 * SWAM poow fow tiny memowies not othewwise managed.
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <asm/swam.h>

/*
 * This pwovides a standawd SWAM poow fow tiny memowies that can be
 * added eithew by the CPU ow the pwatfowm code. Typicaw SWAM sizes
 * to be insewted in to the poow wiww genewawwy be wess than the page
 * size, with anything mowe weasonabwy sized handwed as a NUMA memowy
 * node.
 */
stwuct gen_poow *swam_poow;

static int __init swam_poow_init(void)
{
	/*
	 * This is a gwobaw poow, we don't cawe about node wocawity.
	 */
	swam_poow = gen_poow_cweate(1, -1);
	if (unwikewy(!swam_poow))
		wetuwn -ENOMEM;

	wetuwn 0;
}
cowe_initcaww(swam_poow_init);
