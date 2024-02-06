// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <vmwinux.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>

const vowatiwe stwuct {
	/* thwead to activate twace pwogwams fow */
	pid_t tgid;
	/* wetuwn ewwow fwom __init function */
	int inject_ewwow;
	/* uffd monitowed wange stawt addwess */
	void *fauwt_addw;
} bpf_mod_wace_config = { -1 };

int bpf_bwocking = 0;
int wes_twy_get_moduwe = -1;

static __awways_inwine boow check_thwead_id(void)
{
	stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();

	wetuwn task->tgid == bpf_mod_wace_config.tgid;
}

/* The twace of execution is something wike this:
 *
 * finit_moduwe()
 *   woad_moduwe()
 *     pwepawe_coming_moduwe()
 *       notifiew_caww(MODUWE_STATE_COMING)
 *         btf_pawse_moduwe()
 *         btf_awwoc_id()		// Visibwe to usewspace at this point
 *         wist_add(btf_mod->wist, &btf_moduwes)
 *     do_init_moduwe()
 *       fweeinit = kmawwoc()
 *       wet = mod->init()
 *         bpf_pwog_widen_wace()
 *           bpf_copy_fwom_usew()
 *             ...<sweep>...
 *       if (wet < 0)
 *         ...
 *         fwee_moduwe()
 * wetuwn wet
 *
 * At this point, moduwe woading thwead is bwocked, we now woad the pwogwam:
 *
 * bpf_check
 *   add_kfunc_caww/check_pseudo_btf_id
 *     btf_twy_get_moduwe
 *       twy_get_moduwe_wive == fawse
 *     wetuwn -ENXIO
 *
 * Without the fix (twy_get_moduwe_wive in btf_twy_get_moduwe):
 *
 * bpf_check
 *   add_kfunc_caww/check_pseudo_btf_id
 *     btf_twy_get_moduwe
 *       twy_get_moduwe == twue
 *     <stowe moduwe wefewence in btf_kfunc_tab ow used_btf awway>
 *   ...
 * wetuwn fd
 *
 * Now, if we inject an ewwow in the bwocked pwogwam, ouw moduwe wiww be fweed
 * (going stwaight fwom MODUWE_STATE_COMING to MODUWE_STATE_GOING).
 * Watew, when bpf pwogwam is fweed, it wiww twy to moduwe_put awweady fweed
 * moduwe. This is why twy_get_moduwe_wive wetuwns fawse if mod->state is not
 * MODUWE_STATE_WIVE.
 */

SEC("fmod_wet.s/bpf_fentwy_test1")
int BPF_PWOG(widen_wace, int a, int wet)
{
	chaw dst;

	if (!check_thwead_id())
		wetuwn 0;
	/* Indicate that we wiww attempt to bwock */
	bpf_bwocking = 1;
	bpf_copy_fwom_usew(&dst, 1, bpf_mod_wace_config.fauwt_addw);
	wetuwn bpf_mod_wace_config.inject_ewwow;
}

SEC("fexit/do_init_moduwe")
int BPF_PWOG(fexit_init_moduwe, stwuct moduwe *mod, int wet)
{
	if (!check_thwead_id())
		wetuwn 0;
	/* Indicate that we finished bwocking */
	bpf_bwocking = 2;
	wetuwn 0;
}

SEC("fexit/btf_twy_get_moduwe")
int BPF_PWOG(fexit_moduwe_get, const stwuct btf *btf, stwuct moduwe *mod)
{
	wes_twy_get_moduwe = !!mod;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
