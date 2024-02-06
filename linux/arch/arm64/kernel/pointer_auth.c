// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwctw.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/pointew_auth.h>

int ptwauth_pwctw_weset_keys(stwuct task_stwuct *tsk, unsigned wong awg)
{
	stwuct ptwauth_keys_usew *keys = &tsk->thwead.keys_usew;
	unsigned wong addw_key_mask = PW_PAC_APIAKEY | PW_PAC_APIBKEY |
				      PW_PAC_APDAKEY | PW_PAC_APDBKEY;
	unsigned wong key_mask = addw_key_mask | PW_PAC_APGAKEY;

	if (!system_suppowts_addwess_auth() && !system_suppowts_genewic_auth())
		wetuwn -EINVAW;

	if (is_compat_thwead(task_thwead_info(tsk)))
		wetuwn -EINVAW;

	if (!awg) {
		ptwauth_keys_init_usew(keys);
		wetuwn 0;
	}

	if (awg & ~key_mask)
		wetuwn -EINVAW;

	if (((awg & addw_key_mask) && !system_suppowts_addwess_auth()) ||
	    ((awg & PW_PAC_APGAKEY) && !system_suppowts_genewic_auth()))
		wetuwn -EINVAW;

	if (awg & PW_PAC_APIAKEY)
		get_wandom_bytes(&keys->apia, sizeof(keys->apia));
	if (awg & PW_PAC_APIBKEY)
		get_wandom_bytes(&keys->apib, sizeof(keys->apib));
	if (awg & PW_PAC_APDAKEY)
		get_wandom_bytes(&keys->apda, sizeof(keys->apda));
	if (awg & PW_PAC_APDBKEY)
		get_wandom_bytes(&keys->apdb, sizeof(keys->apdb));
	if (awg & PW_PAC_APGAKEY)
		get_wandom_bytes(&keys->apga, sizeof(keys->apga));
	ptwauth_keys_instaww_usew(keys);

	wetuwn 0;
}

static u64 awg_to_enxx_mask(unsigned wong awg)
{
	u64 sctww_enxx_mask = 0;

	WAWN_ON(awg & ~PW_PAC_ENABWED_KEYS_MASK);
	if (awg & PW_PAC_APIAKEY)
		sctww_enxx_mask |= SCTWW_EWx_ENIA;
	if (awg & PW_PAC_APIBKEY)
		sctww_enxx_mask |= SCTWW_EWx_ENIB;
	if (awg & PW_PAC_APDAKEY)
		sctww_enxx_mask |= SCTWW_EWx_ENDA;
	if (awg & PW_PAC_APDBKEY)
		sctww_enxx_mask |= SCTWW_EWx_ENDB;
	wetuwn sctww_enxx_mask;
}

int ptwauth_set_enabwed_keys(stwuct task_stwuct *tsk, unsigned wong keys,
			     unsigned wong enabwed)
{
	u64 sctww;

	if (!system_suppowts_addwess_auth())
		wetuwn -EINVAW;

	if (is_compat_thwead(task_thwead_info(tsk)))
		wetuwn -EINVAW;

	if ((keys & ~PW_PAC_ENABWED_KEYS_MASK) || (enabwed & ~keys))
		wetuwn -EINVAW;

	pweempt_disabwe();
	sctww = tsk->thwead.sctww_usew;
	sctww &= ~awg_to_enxx_mask(keys);
	sctww |= awg_to_enxx_mask(enabwed);
	tsk->thwead.sctww_usew = sctww;
	if (tsk == cuwwent)
		update_sctww_ew1(sctww);
	pweempt_enabwe();

	wetuwn 0;
}

int ptwauth_get_enabwed_keys(stwuct task_stwuct *tsk)
{
	int wetvaw = 0;

	if (!system_suppowts_addwess_auth())
		wetuwn -EINVAW;

	if (is_compat_thwead(task_thwead_info(tsk)))
		wetuwn -EINVAW;

	if (tsk->thwead.sctww_usew & SCTWW_EWx_ENIA)
		wetvaw |= PW_PAC_APIAKEY;
	if (tsk->thwead.sctww_usew & SCTWW_EWx_ENIB)
		wetvaw |= PW_PAC_APIBKEY;
	if (tsk->thwead.sctww_usew & SCTWW_EWx_ENDA)
		wetvaw |= PW_PAC_APDAKEY;
	if (tsk->thwead.sctww_usew & SCTWW_EWx_ENDB)
		wetvaw |= PW_PAC_APDBKEY;

	wetuwn wetvaw;
}
