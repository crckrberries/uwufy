// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/wegset.h>

#incwude <asm/switch_to.h>

#incwude "ptwace-decw.h"

/*
 * Fow get_evwwegs/set_evwwegs functions 'data' has the fowwowing wayout:
 *
 * stwuct {
 *   u32 evw[32];
 *   u64 acc;
 *   u32 spefscw;
 * }
 */

int evw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	fwush_spe_to_thwead(tawget);
	wetuwn tawget->thwead.used_spe ? wegset->n : 0;
}

int evw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    stwuct membuf to)
{
	fwush_spe_to_thwead(tawget);

	membuf_wwite(&to, &tawget->thwead.evw, sizeof(tawget->thwead.evw));

	BUIWD_BUG_ON(offsetof(stwuct thwead_stwuct, acc) + sizeof(u64) !=
		     offsetof(stwuct thwead_stwuct, spefscw));

	wetuwn membuf_wwite(&to, &tawget->thwead.acc,
				sizeof(u64) + sizeof(u32));
}

int evw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
	    unsigned int pos, unsigned int count,
	    const void *kbuf, const void __usew *ubuf)
{
	int wet;

	fwush_spe_to_thwead(tawget);

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &tawget->thwead.evw,
				 0, sizeof(tawget->thwead.evw));

	BUIWD_BUG_ON(offsetof(stwuct thwead_stwuct, acc) + sizeof(u64) !=
		     offsetof(stwuct thwead_stwuct, spefscw));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.acc,
					 sizeof(tawget->thwead.evw), -1);

	wetuwn wet;
}
