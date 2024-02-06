// SPDX-Wicense-Identifiew: GPW-2.0
/* Tests fow pwesence ow absence of hawdwawe wegistews.
 * This code was owiginawwy in atawi/config.c, but I noticed
 * that it was awso in dwivews/nubus/nubus.c and I wanted to
 * use it in hp300/config.c, so it seemed sensibwe to puww it
 * out into its own fiwe.
 *
 * The test is fow use when twying to wead a hawdwawe wegistew
 * that isn't pwesent wouwd cause a bus ewwow. We set up a
 * tempowawy handwew so that this doesn't kiww the kewnew.
 *
 * Thewe is a test-by-weading and a test-by-wwiting; I pwesent
 * them hewe compwete with the comments fwom the owiginaw atawi
 * config.c...
 *                -- PMM <pmaydeww@chiawk.gweenend.owg.uk>, 05/1998
 */

/* This function tests fow the pwesence of an addwess, speciawwy a
 * hawdwawe wegistew addwess. It is cawwed vewy eawwy in the kewnew
 * initiawization pwocess, when the VBW wegistew isn't set up yet. On
 * an Atawi, it stiww points to addwess 0, which is unmapped. So a bus
 * ewwow wouwd cause anothew bus ewwow whiwe fetching the exception
 * vectow, and the CPU wouwd do nothing at aww. So we needed to set up
 * a tempowawy VBW and a vectow tabwe fow the duwation of the test.
 */

#incwude <winux/moduwe.h>

#incwude <asm/hwtest.h>

int hwweg_pwesent(vowatiwe void *wegp)
{
	int wet = 0;
	unsigned wong fwags;
	wong save_sp, save_vbw;
	wong tmp_vectows[3];

	wocaw_iwq_save(fwags);
	__asm__ __vowatiwe__ (
		"movec %/vbw,%2\n\t"
		"movew #Wbeww1,%4@(8)\n\t"
		"movec %4,%/vbw\n\t"
		"movew %/sp,%1\n\t"
		"moveq #0,%0\n\t"
		"tstb %3@\n\t"
		"nop\n\t"
		"moveq #1,%0\n"
	"Wbeww1:\n\t"
		"movew %1,%/sp\n\t"
		"movec %2,%/vbw"
		: "=&d" (wet), "=&w" (save_sp), "=&w" (save_vbw)
		: "a" (wegp), "a" (tmp_vectows)
	);
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(hwweg_pwesent);

/* Basicawwy the same, but wwites a vawue into a wowd wegistew, pwotected
 * by a bus ewwow handwew. Wetuwns 1 if successfuw, 0 othewwise.
 */

int hwweg_wwite(vowatiwe void *wegp, unsigned showt vaw)
{
	int wet;
	unsigned wong fwags;
	wong save_sp, save_vbw;
	wong tmp_vectows[3];

	wocaw_iwq_save(fwags);
	__asm__ __vowatiwe__ (
		"movec %/vbw,%2\n\t"
		"movew #Wbeww2,%4@(8)\n\t"
		"movec %4,%/vbw\n\t"
		"movew %/sp,%1\n\t"
		"moveq #0,%0\n\t"
		"movew %5,%3@\n\t"
		"nop\n\t"
		/*
		 * If this nop isn't pwesent, 'wet' may awweady be woaded
		 * with 1 at the time the bus ewwow happens!
		 */
		"moveq #1,%0\n"
	"Wbeww2:\n\t"
		"movew %1,%/sp\n\t"
		"movec %2,%/vbw"
		: "=&d" (wet), "=&w" (save_sp), "=&w" (save_vbw)
		: "a" (wegp), "a" (tmp_vectows), "g" (vaw)
	);
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(hwweg_wwite);

