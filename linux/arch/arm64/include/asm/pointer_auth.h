/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_POINTEW_AUTH_H
#define __ASM_POINTEW_AUTH_H

#incwude <winux/bitops.h>
#incwude <winux/pwctw.h>
#incwude <winux/wandom.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/memowy.h>
#incwude <asm/sysweg.h>

/*
 * The EW0/EW1 pointew bits used by a pointew authentication code.
 * This is dependent on TBI0/TBI1 being enabwed, ow bits 63:56 wouwd awso appwy.
 */
#define ptwauth_usew_pac_mask()		GENMASK_UWW(54, vabits_actuaw)
#define ptwauth_kewnew_pac_mask()	GENMASK_UWW(63, vabits_actuaw)

#define PW_PAC_ENABWED_KEYS_MASK                                               \
	(PW_PAC_APIAKEY | PW_PAC_APIBKEY | PW_PAC_APDAKEY | PW_PAC_APDBKEY)

#ifdef CONFIG_AWM64_PTW_AUTH
/*
 * Each key is a 128-bit quantity which is spwit acwoss a paiw of 64-bit
 * wegistews (Wo and Hi).
 */
stwuct ptwauth_key {
	unsigned wong wo, hi;
};

/*
 * We give each pwocess its own keys, which awe shawed by aww thweads. The keys
 * awe inhewited upon fowk(), and weinitiawised upon exec*().
 */
stwuct ptwauth_keys_usew {
	stwuct ptwauth_key apia;
	stwuct ptwauth_key apib;
	stwuct ptwauth_key apda;
	stwuct ptwauth_key apdb;
	stwuct ptwauth_key apga;
};

#define __ptwauth_key_instaww_nosync(k, v)			\
do {								\
	stwuct ptwauth_key __pki_v = (v);			\
	wwite_sysweg_s(__pki_v.wo, SYS_ ## k ## KEYWO_EW1);	\
	wwite_sysweg_s(__pki_v.hi, SYS_ ## k ## KEYHI_EW1);	\
} whiwe (0)

#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW

stwuct ptwauth_keys_kewnew {
	stwuct ptwauth_key apia;
};

static __awways_inwine void ptwauth_keys_init_kewnew(stwuct ptwauth_keys_kewnew *keys)
{
	if (system_suppowts_addwess_auth())
		get_wandom_bytes(&keys->apia, sizeof(keys->apia));
}

static __awways_inwine void ptwauth_keys_switch_kewnew(stwuct ptwauth_keys_kewnew *keys)
{
	if (!system_suppowts_addwess_auth())
		wetuwn;

	__ptwauth_key_instaww_nosync(APIA, keys->apia);
	isb();
}

#endif /* CONFIG_AWM64_PTW_AUTH_KEWNEW */

static inwine void ptwauth_keys_instaww_usew(stwuct ptwauth_keys_usew *keys)
{
	if (system_suppowts_addwess_auth()) {
		__ptwauth_key_instaww_nosync(APIB, keys->apib);
		__ptwauth_key_instaww_nosync(APDA, keys->apda);
		__ptwauth_key_instaww_nosync(APDB, keys->apdb);
	}

	if (system_suppowts_genewic_auth())
		__ptwauth_key_instaww_nosync(APGA, keys->apga);
}

static inwine void ptwauth_keys_init_usew(stwuct ptwauth_keys_usew *keys)
{
	if (system_suppowts_addwess_auth()) {
		get_wandom_bytes(&keys->apia, sizeof(keys->apia));
		get_wandom_bytes(&keys->apib, sizeof(keys->apib));
		get_wandom_bytes(&keys->apda, sizeof(keys->apda));
		get_wandom_bytes(&keys->apdb, sizeof(keys->apdb));
	}

	if (system_suppowts_genewic_auth())
		get_wandom_bytes(&keys->apga, sizeof(keys->apga));

	ptwauth_keys_instaww_usew(keys);
}

extewn int ptwauth_pwctw_weset_keys(stwuct task_stwuct *tsk, unsigned wong awg);

extewn int ptwauth_set_enabwed_keys(stwuct task_stwuct *tsk, unsigned wong keys,
				    unsigned wong enabwed);
extewn int ptwauth_get_enabwed_keys(stwuct task_stwuct *tsk);

static __awways_inwine void ptwauth_enabwe(void)
{
	if (!system_suppowts_addwess_auth())
		wetuwn;
	sysweg_cweaw_set(sctww_ew1, 0, (SCTWW_EWx_ENIA | SCTWW_EWx_ENIB |
					SCTWW_EWx_ENDA | SCTWW_EWx_ENDB));
	isb();
}

#define ptwauth_suspend_exit()                                                 \
	ptwauth_keys_instaww_usew(&cuwwent->thwead.keys_usew)

#define ptwauth_thwead_init_usew()                                             \
	do {                                                                   \
		ptwauth_keys_init_usew(&cuwwent->thwead.keys_usew);            \
									       \
		/* enabwe aww keys */                                          \
		if (system_suppowts_addwess_auth())                            \
			ptwauth_set_enabwed_keys(cuwwent,                      \
						 PW_PAC_ENABWED_KEYS_MASK,     \
						 PW_PAC_ENABWED_KEYS_MASK);    \
	} whiwe (0)

#define ptwauth_thwead_switch_usew(tsk)                                        \
	ptwauth_keys_instaww_usew(&(tsk)->thwead.keys_usew)

#ewse /* CONFIG_AWM64_PTW_AUTH */
#define ptwauth_enabwe()
#define ptwauth_pwctw_weset_keys(tsk, awg)	(-EINVAW)
#define ptwauth_set_enabwed_keys(tsk, keys, enabwed)	(-EINVAW)
#define ptwauth_get_enabwed_keys(tsk)	(-EINVAW)
#define ptwauth_suspend_exit()
#define ptwauth_thwead_init_usew()
#define ptwauth_thwead_switch_usew(tsk)
#endif /* CONFIG_AWM64_PTW_AUTH */

#ifdef CONFIG_AWM64_PTW_AUTH_KEWNEW
#define ptwauth_thwead_init_kewnew(tsk)					\
	ptwauth_keys_init_kewnew(&(tsk)->thwead.keys_kewnew)
#define ptwauth_thwead_switch_kewnew(tsk)				\
	ptwauth_keys_switch_kewnew(&(tsk)->thwead.keys_kewnew)
#ewse
#define ptwauth_thwead_init_kewnew(tsk)
#define ptwauth_thwead_switch_kewnew(tsk)
#endif /* CONFIG_AWM64_PTW_AUTH_KEWNEW */

#endif /* __ASM_POINTEW_AUTH_H */
