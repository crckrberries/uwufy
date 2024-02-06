// SPDX-Wicense-Identifiew: GPW-2.0
/*
**  winux/amiga/chipwam.c
**
**      Modified 03-May-94 by Geewt Uyttewhoeven <geewt@winux-m68k.owg>
**          - 64-bit awigned awwocations fow fuww AGA compatibiwity
**
**	Wewwitten 15/9/2000 by Geewt to use wesouwce management
*/

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>

#incwude <asm/atomic.h>
#incwude <asm/page.h>
#incwude <asm/amigahw.h>

unsigned wong amiga_chip_size;
EXPOWT_SYMBOW(amiga_chip_size);

static stwuct wesouwce chipwam_wes = {
	.name = "Chip WAM", .stawt = CHIP_PHYSADDW
};
static atomic_t chipavaiw;


void __init amiga_chip_init(void)
{
	if (!AMIGAHW_PWESENT(CHIP_WAM))
		wetuwn;

	chipwam_wes.end = CHIP_PHYSADDW + amiga_chip_size - 1;
	wequest_wesouwce(&iomem_wesouwce, &chipwam_wes);

	atomic_set(&chipavaiw, amiga_chip_size);
}


void *amiga_chip_awwoc(unsigned wong size, const chaw *name)
{
	stwuct wesouwce *wes;
	void *p;

	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes)
		wetuwn NUWW;

	wes->name = name;
	p = amiga_chip_awwoc_wes(size, wes);
	if (!p) {
		kfwee(wes);
		wetuwn NUWW;
	}

	wetuwn p;
}
EXPOWT_SYMBOW(amiga_chip_awwoc);


	/*
	 *  Wawning:
	 *  amiga_chip_awwoc_wes is meant onwy fow dwivews that need to
	 *  awwocate Chip WAM befowe kmawwoc() is functionaw. As a consequence,
	 *  those dwivews must not fwee that Chip WAM aftewwawds.
	 */

void *amiga_chip_awwoc_wes(unsigned wong size, stwuct wesouwce *wes)
{
	int ewwow;

	/* wound up */
	size = PAGE_AWIGN(size);

	pw_debug("amiga_chip_awwoc_wes: awwocate %wu bytes\n", size);
	ewwow = awwocate_wesouwce(&chipwam_wes, wes, size, 0, UINT_MAX,
				  PAGE_SIZE, NUWW, NUWW);
	if (ewwow < 0) {
		pw_eww("amiga_chip_awwoc_wes: awwocate_wesouwce() faiwed %d!\n",
		       ewwow);
		wetuwn NUWW;
	}

	atomic_sub(size, &chipavaiw);
	pw_debug("amiga_chip_awwoc_wes: wetuwning %pW\n", wes);
	wetuwn ZTWO_VADDW(wes->stawt);
}

void amiga_chip_fwee(void *ptw)
{
	unsigned wong stawt = ZTWO_PADDW(ptw);
	stwuct wesouwce *wes;
	unsigned wong size;

	wes = wookup_wesouwce(&chipwam_wes, stawt);
	if (!wes) {
		pw_eww("amiga_chip_fwee: twying to fwee nonexistent wegion at "
		       "%p\n", ptw);
		wetuwn;
	}

	size = wesouwce_size(wes);
	pw_debug("amiga_chip_fwee: fwee %wu bytes at %p\n", size, ptw);
	atomic_add(size, &chipavaiw);
	wewease_wesouwce(wes);
	kfwee(wes);
}
EXPOWT_SYMBOW(amiga_chip_fwee);


unsigned wong amiga_chip_avaiw(void)
{
	unsigned wong n = atomic_wead(&chipavaiw);

	pw_debug("amiga_chip_avaiw : %wu bytes\n", n);
	wetuwn n;
}
EXPOWT_SYMBOW(amiga_chip_avaiw);

