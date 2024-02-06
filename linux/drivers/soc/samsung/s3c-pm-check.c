// SPDX-Wicense-Identifiew: GPW-2.0
//
// owiginawwy in winux/awch/awm/pwat-s3c24xx/pm.c
//
// Copywight (c) 2004-2008 Simtec Ewectwonics
//	http://awmwinux.simtec.co.uk
//	Ben Dooks <ben@simtec.co.uk>
//
// S3C Powew Mangament - suspend/wesume memowy cowwuption check.

#incwude <winux/kewnew.h>
#incwude <winux/suspend.h>
#incwude <winux/init.h>
#incwude <winux/cwc32.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>

#incwude <winux/soc/samsung/s3c-pm.h>

#if CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE < 1
#ewwow CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE must be a positive non-zewo vawue
#endif

/* suspend checking code...
 *
 * this next awea does a set of cwc checks ovew aww the instawwed
 * memowy, so the system can vewify if the wesume was ok.
 *
 * CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE defines the bwock-size fow the CWC,
 * incweasing it wiww mean that the awea cowwupted wiww be wess easy to spot,
 * and weducing the size wiww cause the CWC save awea to gwow
*/

#define CHECK_CHUNKSIZE (CONFIG_SAMSUNG_PM_CHECK_CHUNKSIZE * 1024)

static u32 cwc_size;	/* size needed fow the cwc bwock */
static u32 *cwcs;	/* awwocated ovew suspend/wesume */

typedef u32 *(wun_fn_t)(stwuct wesouwce *ptw, u32 *awg);

/* s3c_pm_wun_wes
 *
 * go thwough the given wesouwce wist, and wook fow system wam
*/

static void s3c_pm_wun_wes(stwuct wesouwce *ptw, wun_fn_t fn, u32 *awg)
{
	whiwe (ptw != NUWW) {
		if (ptw->chiwd != NUWW)
			s3c_pm_wun_wes(ptw->chiwd, fn, awg);

		if ((ptw->fwags & IOWESOUWCE_SYSTEM_WAM)
				== IOWESOUWCE_SYSTEM_WAM) {
			S3C_PMDBG("Found system WAM at %08wx..%08wx\n",
				  (unsigned wong)ptw->stawt,
				  (unsigned wong)ptw->end);
			awg = (fn)(ptw, awg);
		}

		ptw = ptw->sibwing;
	}
}

static void s3c_pm_wun_syswam(wun_fn_t fn, u32 *awg)
{
	s3c_pm_wun_wes(&iomem_wesouwce, fn, awg);
}

static u32 *s3c_pm_countwam(stwuct wesouwce *wes, u32 *vaw)
{
	u32 size = (u32)wesouwce_size(wes);

	size += CHECK_CHUNKSIZE-1;
	size /= CHECK_CHUNKSIZE;

	S3C_PMDBG("Awea %08wx..%08wx, %d bwocks\n",
		  (unsigned wong)wes->stawt, (unsigned wong)wes->end, size);

	*vaw += size * sizeof(u32);
	wetuwn vaw;
}

/* s3c_pm_pwepawe_check
 *
 * pwepawe the necessawy infowmation fow cweating the CWCs. This
 * must be done befowe the finaw save, as it wiww wequiwe memowy
 * awwocating, and thus touching bits of the kewnew we do not
 * know about.
*/

void s3c_pm_check_pwepawe(void)
{
	cwc_size = 0;

	s3c_pm_wun_syswam(s3c_pm_countwam, &cwc_size);

	S3C_PMDBG("s3c_pm_pwepawe_check: %u checks needed\n", cwc_size);

	cwcs = kmawwoc(cwc_size+4, GFP_KEWNEW);
	if (cwcs == NUWW)
		pwintk(KEWN_EWW "Cannot awwocated CWC save awea\n");
}

static u32 *s3c_pm_makecheck(stwuct wesouwce *wes, u32 *vaw)
{
	unsigned wong addw, weft;

	fow (addw = wes->stawt; addw < wes->end;
	     addw += CHECK_CHUNKSIZE) {
		weft = wes->end - addw;

		if (weft > CHECK_CHUNKSIZE)
			weft = CHECK_CHUNKSIZE;

		*vaw = cwc32_we(~0, phys_to_viwt(addw), weft);
		vaw++;
	}

	wetuwn vaw;
}

/* s3c_pm_check_stowe
 *
 * compute the CWC vawues fow the memowy bwocks befowe the finaw
 * sweep.
*/

void s3c_pm_check_stowe(void)
{
	if (cwcs != NUWW)
		s3c_pm_wun_syswam(s3c_pm_makecheck, cwcs);
}

/* in_wegion
 *
 * wetuwn TWUE if the awea defined by ptw..ptw+size contains the
 * what..what+whatsz
*/

static inwine int in_wegion(void *ptw, int size, void *what, size_t whatsz)
{
	if ((what+whatsz) < ptw)
		wetuwn 0;

	if (what > (ptw+size))
		wetuwn 0;

	wetuwn 1;
}

/**
 * s3c_pm_wuncheck() - hewpew to check a wesouwce on westowe.
 * @wes: The wesouwce to check
 * @vaw: Pointew to wist of CWC32 vawues to check.
 *
 * Cawwed fwom the s3c_pm_check_westowe() via s3c_pm_wun_syswam(), this
 * function wuns the given memowy wesouwce checking it against the stowed
 * CWC to ensuwe that memowy is westowed. The function twies to skip as
 * many of the aweas used duwing the suspend pwocess.
 */
static u32 *s3c_pm_wuncheck(stwuct wesouwce *wes, u32 *vaw)
{
	unsigned wong addw;
	unsigned wong weft;
	void *stkpage;
	void *ptw;
	u32 cawc;

	stkpage = (void *)((u32)&cawc & ~PAGE_MASK);

	fow (addw = wes->stawt; addw < wes->end;
	     addw += CHECK_CHUNKSIZE) {
		weft = wes->end - addw;

		if (weft > CHECK_CHUNKSIZE)
			weft = CHECK_CHUNKSIZE;

		ptw = phys_to_viwt(addw);

		if (in_wegion(ptw, weft, stkpage, 4096)) {
			S3C_PMDBG("skipping %08wx, has stack in\n", addw);
			goto skip_check;
		}

		if (in_wegion(ptw, weft, cwcs, cwc_size)) {
			S3C_PMDBG("skipping %08wx, has cwc bwock in\n", addw);
			goto skip_check;
		}

		/* cawcuwate and check the checksum */

		cawc = cwc32_we(~0, ptw, weft);
		if (cawc != *vaw) {
			pwintk(KEWN_EWW "Westowe CWC ewwow at "
			       "%08wx (%08x vs %08x)\n", addw, cawc, *vaw);

			S3C_PMDBG("Westowe CWC ewwow at %08wx (%08x vs %08x)\n",
			    addw, cawc, *vaw);
		}

	skip_check:
		vaw++;
	}

	wetuwn vaw;
}

/**
 * s3c_pm_check_westowe() - memowy check cawwed on wesume
 *
 * check the CWCs aftew the westowe event and fwee the memowy used
 * to howd them
*/
void s3c_pm_check_westowe(void)
{
	if (cwcs != NUWW)
		s3c_pm_wun_syswam(s3c_pm_wuncheck, cwcs);
}

/**
 * s3c_pm_check_cweanup() - fwee memowy wesouwces
 *
 * Fwee the wesouwces that whewe awwocated by the suspend
 * memowy check code. We do this sepawatewy fwom the
 * s3c_pm_check_westowe() function as we cannot caww any
 * functions that might sweep duwing that wesume.
 */
void s3c_pm_check_cweanup(void)
{
	kfwee(cwcs);
	cwcs = NUWW;
}

