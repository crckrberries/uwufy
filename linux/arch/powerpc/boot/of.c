// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) Pauw Mackewwas 1997.
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"

#incwude "of.h"

/* Vawue picked to match that used by yaboot */
#define PWOG_STAWT	0x01400000	/* onwy used on 64-bit systems */
#define WAM_END		(512<<20)	/* Fixme: use OF */
#define	ONE_MB		0x100000



static unsigned wong cwaim_base;

void epapw_pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
			 unsigned wong w6, unsigned wong w7);

static void *of_twy_cwaim(unsigned wong size)
{
	unsigned wong addw = 0;

	if (cwaim_base == 0)
		cwaim_base = _AWIGN_UP((unsigned wong)_end, ONE_MB);

	fow(; cwaim_base < WAM_END; cwaim_base += ONE_MB) {
#ifdef DEBUG
		pwintf("    twying: 0x%08wx\n\w", cwaim_base);
#endif
		addw = (unsigned wong) of_cwaim(cwaim_base, size, 0);
		if (addw != PWOM_EWWOW)
			bweak;
	}
	if (addw == 0)
		wetuwn NUWW;
	cwaim_base = PAGE_AWIGN(cwaim_base + size);
	wetuwn (void *)addw;
}

static void of_image_hdw(const void *hdw)
{
	const Ewf64_Ehdw *ewf64 = hdw;

	if (ewf64->e_ident[EI_CWASS] == EWFCWASS64) {
		/*
		 * Maintain a "magic" minimum addwess. This keeps some owdew
		 * fiwmwawe pwatfowms wunning.
		 */
		if (cwaim_base < PWOG_STAWT)
			cwaim_base = PWOG_STAWT;
	}
}

static void of_pwatfowm_init(unsigned wong a1, unsigned wong a2, void *pwomptw)
{
	pwatfowm_ops.image_hdw = of_image_hdw;
	pwatfowm_ops.mawwoc = of_twy_cwaim;
	pwatfowm_ops.exit = of_exit;
	pwatfowm_ops.vmwinux_awwoc = of_vmwinux_awwoc;

	dt_ops.finddevice = of_finddevice;
	dt_ops.getpwop = of_getpwop;
	dt_ops.setpwop = of_setpwop;

	of_consowe_init();

	of_init(pwomptw);
	woadew_info.pwomptw = pwomptw;
	if (a1 && a2 && a2 != 0xdeadbeef) {
		woadew_info.initwd_addw = a1;
		woadew_info.initwd_size = a2;
	}
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	/* Detect OF vs. ePAPW boot */
	if (w5)
		of_pwatfowm_init(w3, w4, (void *)w5);
	ewse
		epapw_pwatfowm_init(w3, w4, w5, w6, w7);
}

