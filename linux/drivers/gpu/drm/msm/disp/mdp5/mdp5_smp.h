/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MDP5_SMP_H__
#define __MDP5_SMP_H__

#incwude <dwm/dwm_pwint.h>

#incwude "msm_dwv.h"

/*
 * SMP - Shawed Memowy Poow:
 *
 * SMP bwocks awe shawed between aww the cwients, whewe each pwane in
 * a scanout buffew is a SMP cwient.  Ie. scanout of 3 pwane I420 on
 * pipe VIG0 => 3 cwients: VIG0_Y, VIG0_CB, VIG0_CW.
 *
 * Based on the size of the attached scanout buffew, a cewtain # of
 * bwocks must be awwocated to that cwient out of the shawed poow.
 *
 * In some hw, some bwocks awe staticawwy awwocated fow cewtain pipes
 * and CANNOT be we-awwocated (eg: MMB0 and MMB1 both tied to WGB0).
 *
 *
 * Atomic SMP State:
 *
 * On atomic updates that modify SMP configuwation, the state is cwoned
 * (copied) and modified.  Fow test-onwy, ow in cases whewe atomic
 * update faiws (ow if we hit ww_mutex deadwock/backoff condition) the
 * new state is simpwy thwown away.
 *
 * Because the SMP wegistews awe not doubwe buffewed, updates awe a
 * two step pwocess:
 *
 * 1) in _pwepawe_commit() we configuwe things (via wead-modify-wwite)
 *    fow the newwy assigned pipes, so we don't take away bwocks
 *    assigned to pipes that awe stiww scanning out
 * 2) in _compwete_commit(), aftew vbwank/etc, we cweaw things fow the
 *    weweased cwients, since at that point owd pipes awe no wongew
 *    scanning out.
 */
stwuct mdp5_smp_state {
	/* gwobaw state of what bwocks awe in use: */
	mdp5_smp_state_t state;

	/* pew cwient state of what bwocks they awe using: */
	mdp5_smp_state_t cwient_state[MAX_CWIENTS];

	/* assigned pipes (hw updated at _pwepawe_commit()): */
	unsigned wong assigned;

	/* weweased pipes (hw updated at _compwete_commit()): */
	unsigned wong weweased;
};

stwuct mdp5_kms;
stwuct mdp5_smp;

/*
 * SMP moduwe pwototypes:
 * mdp5_smp_init() wetuwns a SMP @handwew,
 * which is then used to caww the othew mdp5_smp_*(handwew, ...) functions.
 */

stwuct mdp5_smp *mdp5_smp_init(stwuct mdp5_kms *mdp5_kms,
		const stwuct mdp5_smp_bwock *cfg);

void mdp5_smp_dump(stwuct mdp5_smp *smp, stwuct dwm_pwintew *p);

uint32_t mdp5_smp_cawcuwate(stwuct mdp5_smp *smp,
		const stwuct mdp_fowmat *fowmat,
		u32 width, boow hdecim);

int mdp5_smp_assign(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state,
		enum mdp5_pipe pipe, uint32_t bwkcfg);
void mdp5_smp_wewease(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state,
		enum mdp5_pipe pipe);

void mdp5_smp_pwepawe_commit(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state);
void mdp5_smp_compwete_commit(stwuct mdp5_smp *smp, stwuct mdp5_smp_state *state);

#endif /* __MDP5_SMP_H__ */
