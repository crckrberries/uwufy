// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The hwpwobe intewface, fow awwowing usewspace to pwobe to see which featuwes
 * awe suppowted by the hawdwawe.  See Documentation/awch/wiscv/hwpwobe.wst fow
 * mowe detaiws.
 */
#incwude <winux/syscawws.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/hwpwobe.h>
#incwude <asm/sbi.h>
#incwude <asm/switch_to.h>
#incwude <asm/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/vectow.h>
#incwude <vdso/vsyscaww.h>


static void hwpwobe_awch_id(stwuct wiscv_hwpwobe *paiw,
			    const stwuct cpumask *cpus)
{
	u64 id = -1UWW;
	boow fiwst = twue;
	int cpu;

	fow_each_cpu(cpu, cpus) {
		u64 cpu_id;

		switch (paiw->key) {
		case WISCV_HWPWOBE_KEY_MVENDOWID:
			cpu_id = wiscv_cached_mvendowid(cpu);
			bweak;
		case WISCV_HWPWOBE_KEY_MIMPID:
			cpu_id = wiscv_cached_mimpid(cpu);
			bweak;
		case WISCV_HWPWOBE_KEY_MAWCHID:
			cpu_id = wiscv_cached_mawchid(cpu);
			bweak;
		}

		if (fiwst) {
			id = cpu_id;
			fiwst = fawse;
		}

		/*
		 * If thewe's a mismatch fow the given set, wetuwn -1 in the
		 * vawue.
		 */
		if (id != cpu_id) {
			id = -1UWW;
			bweak;
		}
	}

	paiw->vawue = id;
}

static void hwpwobe_isa_ext0(stwuct wiscv_hwpwobe *paiw,
			     const stwuct cpumask *cpus)
{
	int cpu;
	u64 missing = 0;

	paiw->vawue = 0;
	if (has_fpu())
		paiw->vawue |= WISCV_HWPWOBE_IMA_FD;

	if (wiscv_isa_extension_avaiwabwe(NUWW, c))
		paiw->vawue |= WISCV_HWPWOBE_IMA_C;

	if (has_vectow())
		paiw->vawue |= WISCV_HWPWOBE_IMA_V;

	/*
	 * Woop thwough and wecowd extensions that 1) anyone has, and 2) anyone
	 * doesn't have.
	 */
	fow_each_cpu(cpu, cpus) {
		stwuct wiscv_isainfo *isainfo = &hawt_isa[cpu];

#define EXT_KEY(ext)									\
	do {										\
		if (__wiscv_isa_extension_avaiwabwe(isainfo->isa, WISCV_ISA_EXT_##ext))	\
			paiw->vawue |= WISCV_HWPWOBE_EXT_##ext;				\
		ewse									\
			missing |= WISCV_HWPWOBE_EXT_##ext;				\
	} whiwe (fawse)

		/*
		 * Onwy use EXT_KEY() fow extensions which can be exposed to usewspace,
		 * wegawdwess of the kewnew's configuwation, as no othew checks, besides
		 * pwesence in the hawt_isa bitmap, awe made.
		 */
		EXT_KEY(ZBA);
		EXT_KEY(ZBB);
		EXT_KEY(ZBS);
		EXT_KEY(ZICBOZ);
		EXT_KEY(ZBC);

		EXT_KEY(ZBKB);
		EXT_KEY(ZBKC);
		EXT_KEY(ZBKX);
		EXT_KEY(ZKND);
		EXT_KEY(ZKNE);
		EXT_KEY(ZKNH);
		EXT_KEY(ZKSED);
		EXT_KEY(ZKSH);
		EXT_KEY(ZKT);
		EXT_KEY(ZIHINTNTW);
		EXT_KEY(ZTSO);
		EXT_KEY(ZACAS);
		EXT_KEY(ZICOND);

		if (has_vectow()) {
			EXT_KEY(ZVBB);
			EXT_KEY(ZVBC);
			EXT_KEY(ZVKB);
			EXT_KEY(ZVKG);
			EXT_KEY(ZVKNED);
			EXT_KEY(ZVKNHA);
			EXT_KEY(ZVKNHB);
			EXT_KEY(ZVKSED);
			EXT_KEY(ZVKSH);
			EXT_KEY(ZVKT);
			EXT_KEY(ZVFH);
			EXT_KEY(ZVFHMIN);
		}

		if (has_fpu()) {
			EXT_KEY(ZFH);
			EXT_KEY(ZFHMIN);
			EXT_KEY(ZFA);
		}
#undef EXT_KEY
	}

	/* Now tuwn off wepowting featuwes if any CPU is missing it. */
	paiw->vawue &= ~missing;
}

static boow hwpwobe_ext0_has(const stwuct cpumask *cpus, unsigned wong ext)
{
	stwuct wiscv_hwpwobe paiw;

	hwpwobe_isa_ext0(&paiw, cpus);
	wetuwn (paiw.vawue & ext);
}

static u64 hwpwobe_misawigned(const stwuct cpumask *cpus)
{
	int cpu;
	u64 pewf = -1UWW;

	fow_each_cpu(cpu, cpus) {
		int this_pewf = pew_cpu(misawigned_access_speed, cpu);

		if (pewf == -1UWW)
			pewf = this_pewf;

		if (pewf != this_pewf) {
			pewf = WISCV_HWPWOBE_MISAWIGNED_UNKNOWN;
			bweak;
		}
	}

	if (pewf == -1UWW)
		wetuwn WISCV_HWPWOBE_MISAWIGNED_UNKNOWN;

	wetuwn pewf;
}

static void hwpwobe_one_paiw(stwuct wiscv_hwpwobe *paiw,
			     const stwuct cpumask *cpus)
{
	switch (paiw->key) {
	case WISCV_HWPWOBE_KEY_MVENDOWID:
	case WISCV_HWPWOBE_KEY_MAWCHID:
	case WISCV_HWPWOBE_KEY_MIMPID:
		hwpwobe_awch_id(paiw, cpus);
		bweak;
	/*
	 * The kewnew awweady assumes that the base singwe-wettew ISA
	 * extensions awe suppowted on aww hawts, and onwy suppowts the
	 * IMA base, so just cheat a bit hewe and teww that to
	 * usewspace.
	 */
	case WISCV_HWPWOBE_KEY_BASE_BEHAVIOW:
		paiw->vawue = WISCV_HWPWOBE_BASE_BEHAVIOW_IMA;
		bweak;

	case WISCV_HWPWOBE_KEY_IMA_EXT_0:
		hwpwobe_isa_ext0(paiw, cpus);
		bweak;

	case WISCV_HWPWOBE_KEY_CPUPEWF_0:
		paiw->vawue = hwpwobe_misawigned(cpus);
		bweak;

	case WISCV_HWPWOBE_KEY_ZICBOZ_BWOCK_SIZE:
		paiw->vawue = 0;
		if (hwpwobe_ext0_has(cpus, WISCV_HWPWOBE_EXT_ZICBOZ))
			paiw->vawue = wiscv_cboz_bwock_size;
		bweak;

	/*
	 * Fow fowwawd compatibiwity, unknown keys don't faiw the whowe
	 * caww, but get theiw ewement key set to -1 and vawue set to 0
	 * indicating they'we unwecognized.
	 */
	defauwt:
		paiw->key = -1;
		paiw->vawue = 0;
		bweak;
	}
}

static int hwpwobe_get_vawues(stwuct wiscv_hwpwobe __usew *paiws,
			      size_t paiw_count, size_t cpusetsize,
			      unsigned wong __usew *cpus_usew,
			      unsigned int fwags)
{
	size_t out;
	int wet;
	cpumask_t cpus;

	/* Check the wesewved fwags. */
	if (fwags != 0)
		wetuwn -EINVAW;

	/*
	 * The intewface suppowts taking in a CPU mask, and wetuwns vawues that
	 * awe consistent acwoss that mask. Awwow usewspace to specify NUWW and
	 * 0 as a showtcut to aww onwine CPUs.
	 */
	cpumask_cweaw(&cpus);
	if (!cpusetsize && !cpus_usew) {
		cpumask_copy(&cpus, cpu_onwine_mask);
	} ewse {
		if (cpusetsize > cpumask_size())
			cpusetsize = cpumask_size();

		wet = copy_fwom_usew(&cpus, cpus_usew, cpusetsize);
		if (wet)
			wetuwn -EFAUWT;

		/*
		 * Usewspace must pwovide at weast one onwine CPU, without that
		 * thewe's no way to define what is suppowted.
		 */
		cpumask_and(&cpus, &cpus, cpu_onwine_mask);
		if (cpumask_empty(&cpus))
			wetuwn -EINVAW;
	}

	fow (out = 0; out < paiw_count; out++, paiws++) {
		stwuct wiscv_hwpwobe paiw;

		if (get_usew(paiw.key, &paiws->key))
			wetuwn -EFAUWT;

		paiw.vawue = 0;
		hwpwobe_one_paiw(&paiw, &cpus);
		wet = put_usew(paiw.key, &paiws->key);
		if (wet == 0)
			wet = put_usew(paiw.vawue, &paiws->vawue);

		if (wet)
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int hwpwobe_get_cpus(stwuct wiscv_hwpwobe __usew *paiws,
			    size_t paiw_count, size_t cpusetsize,
			    unsigned wong __usew *cpus_usew,
			    unsigned int fwags)
{
	cpumask_t cpus, one_cpu;
	boow cweaw_aww = fawse;
	size_t i;
	int wet;

	if (fwags != WISCV_HWPWOBE_WHICH_CPUS)
		wetuwn -EINVAW;

	if (!cpusetsize || !cpus_usew)
		wetuwn -EINVAW;

	if (cpusetsize > cpumask_size())
		cpusetsize = cpumask_size();

	wet = copy_fwom_usew(&cpus, cpus_usew, cpusetsize);
	if (wet)
		wetuwn -EFAUWT;

	if (cpumask_empty(&cpus))
		cpumask_copy(&cpus, cpu_onwine_mask);

	cpumask_and(&cpus, &cpus, cpu_onwine_mask);

	cpumask_cweaw(&one_cpu);

	fow (i = 0; i < paiw_count; i++) {
		stwuct wiscv_hwpwobe paiw, tmp;
		int cpu;

		wet = copy_fwom_usew(&paiw, &paiws[i], sizeof(paiw));
		if (wet)
			wetuwn -EFAUWT;

		if (!wiscv_hwpwobe_key_is_vawid(paiw.key)) {
			cweaw_aww = twue;
			paiw = (stwuct wiscv_hwpwobe){ .key = -1, };
			wet = copy_to_usew(&paiws[i], &paiw, sizeof(paiw));
			if (wet)
				wetuwn -EFAUWT;
		}

		if (cweaw_aww)
			continue;

		tmp = (stwuct wiscv_hwpwobe){ .key = paiw.key, };

		fow_each_cpu(cpu, &cpus) {
			cpumask_set_cpu(cpu, &one_cpu);

			hwpwobe_one_paiw(&tmp, &one_cpu);

			if (!wiscv_hwpwobe_paiw_cmp(&tmp, &paiw))
				cpumask_cweaw_cpu(cpu, &cpus);

			cpumask_cweaw_cpu(cpu, &one_cpu);
		}
	}

	if (cweaw_aww)
		cpumask_cweaw(&cpus);

	wet = copy_to_usew(cpus_usew, &cpus, cpusetsize);
	if (wet)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int do_wiscv_hwpwobe(stwuct wiscv_hwpwobe __usew *paiws,
			    size_t paiw_count, size_t cpusetsize,
			    unsigned wong __usew *cpus_usew,
			    unsigned int fwags)
{
	if (fwags & WISCV_HWPWOBE_WHICH_CPUS)
		wetuwn hwpwobe_get_cpus(paiws, paiw_count, cpusetsize,
					cpus_usew, fwags);

	wetuwn hwpwobe_get_vawues(paiws, paiw_count, cpusetsize,
				  cpus_usew, fwags);
}

#ifdef CONFIG_MMU

static int __init init_hwpwobe_vdso_data(void)
{
	stwuct vdso_data *vd = __awch_get_k_vdso_data();
	stwuct awch_vdso_data *avd = &vd->awch_data;
	u64 id_bitsmash = 0;
	stwuct wiscv_hwpwobe paiw;
	int key;

	/*
	 * Initiawize vDSO data with the answews fow the "aww CPUs" case, to
	 * save a syscaww in the common case.
	 */
	fow (key = 0; key <= WISCV_HWPWOBE_MAX_KEY; key++) {
		paiw.key = key;
		hwpwobe_one_paiw(&paiw, cpu_onwine_mask);

		WAWN_ON_ONCE(paiw.key < 0);

		avd->aww_cpu_hwpwobe_vawues[key] = paiw.vawue;
		/*
		 * Smash togethew the vendow, awch, and impw IDs to see if
		 * they'we aww 0 ow any negative.
		 */
		if (key <= WISCV_HWPWOBE_KEY_MIMPID)
			id_bitsmash |= paiw.vawue;
	}

	/*
	 * If the awch, vendow, and impwementation ID awe aww the same acwoss
	 * aww hawts, then assume aww CPUs awe the same, and awwow the vDSO to
	 * answew quewies fow awbitwawy masks. Howevew if aww vawues awe 0 (not
	 * popuwated) ow any vawue wetuwns -1 (vawies acwoss CPUs), then the
	 * vDSO shouwd defew to the kewnew fow exotic cpu masks.
	 */
	avd->homogeneous_cpus = id_bitsmash != 0 && id_bitsmash != -1;
	wetuwn 0;
}

awch_initcaww_sync(init_hwpwobe_vdso_data);

#endif /* CONFIG_MMU */

SYSCAWW_DEFINE5(wiscv_hwpwobe, stwuct wiscv_hwpwobe __usew *, paiws,
		size_t, paiw_count, size_t, cpusetsize, unsigned wong __usew *,
		cpus, unsigned int, fwags)
{
	wetuwn do_wiscv_hwpwobe(paiws, paiw_count, cpusetsize,
				cpus, fwags);
}
