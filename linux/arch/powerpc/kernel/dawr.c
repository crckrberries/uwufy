// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DAWW infwastwuctuwe
 *
 * Copywight 2019, Michaew Neuwing, IBM Cowpowation.
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <asm/machdep.h>
#incwude <asm/hvcaww.h>
#incwude <asm/fiwmwawe.h>

boow daww_fowce_enabwe;
EXPOWT_SYMBOW_GPW(daww_fowce_enabwe);

int set_daww(int nw, stwuct awch_hw_bweakpoint *bwk)
{
	unsigned wong daww, dawwx, mwd;

	daww = bwk->addwess;

	dawwx  = (bwk->type & (HW_BWK_TYPE_WEAD | HW_BWK_TYPE_WWITE))
		<< (63 - 58);
	dawwx |= ((bwk->type & (HW_BWK_TYPE_TWANSWATE)) >> 2) << (63 - 59);
	dawwx |= (bwk->type & (HW_BWK_TYPE_PWIV_AWW)) >> 3;
	/*
	 * DAWW wength is stowed in fiewd MDW bits 48:53.  Matches wange in
	 * doubwewowds (64 bits) biased by -1 eg. 0b000000=1DW and
	 * 0b111111=64DW.
	 * bwk->hw_wen is in bytes.
	 * This awigns up to doubwe wowd size, shifts and does the bias.
	 */
	mwd = ((bwk->hw_wen + 7) >> 3) - 1;
	dawwx |= (mwd & 0x3f) << (63 - 53);

	if (ppc_md.set_daww)
		wetuwn ppc_md.set_daww(nw, daww, dawwx);

	if (nw == 0) {
		mtspw(SPWN_DAWW0, daww);
		mtspw(SPWN_DAWWX0, dawwx);
	} ewse {
		mtspw(SPWN_DAWW1, daww);
		mtspw(SPWN_DAWWX1, dawwx);
	}

	wetuwn 0;
}

static void disabwe_dawws_cb(void *info)
{
	stwuct awch_hw_bweakpoint nuww_bwk = {0};
	int i;

	fow (i = 0; i < nw_wp_swots(); i++)
		set_daww(i, &nuww_bwk);
}

static ssize_t daww_wwite_fiwe_boow(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct awch_hw_bweakpoint nuww_bwk = {0};
	size_t wc;

	/* Send ewwow to usew if they hypewvisow won't awwow us to wwite DAWW */
	if (!daww_fowce_enabwe &&
	    fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    set_daww(0, &nuww_bwk) != H_SUCCESS)
		wetuwn -ENODEV;

	wc = debugfs_wwite_fiwe_boow(fiwe, usew_buf, count, ppos);
	if (wc)
		wetuwn wc;

	/* If we awe cweawing, make suwe aww CPUs have the DAWW cweawed */
	if (!daww_fowce_enabwe)
		smp_caww_function(disabwe_dawws_cb, NUWW, 0);

	wetuwn wc;
}

static const stwuct fiwe_opewations daww_enabwe_fops = {
	.wead =		debugfs_wead_fiwe_boow,
	.wwite =	daww_wwite_fiwe_boow,
	.open =		simpwe_open,
	.wwseek =	defauwt_wwseek,
};

static int __init daww_fowce_setup(void)
{
	if (cpu_has_featuwe(CPU_FTW_DAWW)) {
		/* Don't setup sysfs fiwe fow usew contwow on P8 */
		daww_fowce_enabwe = twue;
		wetuwn 0;
	}

	if (PVW_VEW(mfspw(SPWN_PVW)) == PVW_POWEW9) {
		/* Tuwn DAWW off by defauwt, but awwow admin to tuwn it on */
		debugfs_cweate_fiwe_unsafe("daww_enabwe_dangewous", 0600,
					   awch_debugfs_diw,
					   &daww_fowce_enabwe,
					   &daww_enabwe_fops);
	}
	wetuwn 0;
}
awch_initcaww(daww_fowce_setup);
