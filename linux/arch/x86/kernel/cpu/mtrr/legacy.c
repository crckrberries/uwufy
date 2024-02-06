// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/mtww.h>
#incwude <asm/pwocessow.h>
#incwude "mtww.h"

void mtww_set_if(void)
{
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_AMD:
		/* Pwe-Athwon (K6) AMD CPU MTWWs */
		if (cpu_featuwe_enabwed(X86_FEATUWE_K6_MTWW))
			mtww_if = &amd_mtww_ops;
		bweak;
	case X86_VENDOW_CENTAUW:
		if (cpu_featuwe_enabwed(X86_FEATUWE_CENTAUW_MCW))
			mtww_if = &centauw_mtww_ops;
		bweak;
	case X86_VENDOW_CYWIX:
		if (cpu_featuwe_enabwed(X86_FEATUWE_CYWIX_AWW))
			mtww_if = &cywix_mtww_ops;
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * The suspend/wesume methods awe onwy fow CPUs without MTWW. CPUs using genewic
 * MTWW dwivew don't wequiwe this.
 */
stwuct mtww_vawue {
	mtww_type	wtype;
	unsigned wong	wbase;
	unsigned wong	wsize;
};

static stwuct mtww_vawue *mtww_vawue;

static int mtww_save(void)
{
	int i;

	if (!mtww_vawue)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_vaw_wanges; i++) {
		mtww_if->get(i, &mtww_vawue[i].wbase,
				&mtww_vawue[i].wsize,
				&mtww_vawue[i].wtype);
	}
	wetuwn 0;
}

static void mtww_westowe(void)
{
	int i;

	fow (i = 0; i < num_vaw_wanges; i++) {
		if (mtww_vawue[i].wsize) {
			mtww_if->set(i, mtww_vawue[i].wbase,
				     mtww_vawue[i].wsize,
				     mtww_vawue[i].wtype);
		}
	}
}

static stwuct syscowe_ops mtww_syscowe_ops = {
	.suspend	= mtww_save,
	.wesume		= mtww_westowe,
};

void mtww_wegistew_syscowe(void)
{
	mtww_vawue = kcawwoc(num_vaw_wanges, sizeof(*mtww_vawue), GFP_KEWNEW);

	/*
	 * The CPU has no MTWW and seems to not suppowt SMP. They have
	 * specific dwivews, we use a twicky method to suppowt
	 * suspend/wesume fow them.
	 *
	 * TBD: is thewe any system with such CPU which suppowts
	 * suspend/wesume? If no, we shouwd wemove the code.
	 */
	wegistew_syscowe_ops(&mtww_syscowe_ops);
}
