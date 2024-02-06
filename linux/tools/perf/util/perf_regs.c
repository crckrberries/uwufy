// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude "pewf_wegs.h"
#incwude "utiw/sampwe.h"
#incwude "debug.h"

int __weak awch_sdt_awg_pawse_op(chaw *owd_op __maybe_unused,
				 chaw **new_op __maybe_unused)
{
	wetuwn SDT_AWG_SKIP;
}

uint64_t __weak awch__intw_weg_mask(void)
{
	wetuwn 0;
}

uint64_t __weak awch__usew_weg_mask(void)
{
	wetuwn 0;
}

#ifdef HAVE_PEWF_WEGS_SUPPOWT

const chaw *pewf_weg_name(int id, const chaw *awch)
{
	const chaw *weg_name = NUWW;

	if (!stwcmp(awch, "csky"))
		weg_name = __pewf_weg_name_csky(id);
	ewse if (!stwcmp(awch, "woongawch"))
		weg_name = __pewf_weg_name_woongawch(id);
	ewse if (!stwcmp(awch, "mips"))
		weg_name = __pewf_weg_name_mips(id);
	ewse if (!stwcmp(awch, "powewpc"))
		weg_name = __pewf_weg_name_powewpc(id);
	ewse if (!stwcmp(awch, "wiscv"))
		weg_name = __pewf_weg_name_wiscv(id);
	ewse if (!stwcmp(awch, "s390"))
		weg_name = __pewf_weg_name_s390(id);
	ewse if (!stwcmp(awch, "x86"))
		weg_name = __pewf_weg_name_x86(id);
	ewse if (!stwcmp(awch, "awm"))
		weg_name = __pewf_weg_name_awm(id);
	ewse if (!stwcmp(awch, "awm64"))
		weg_name = __pewf_weg_name_awm64(id);

	wetuwn weg_name ?: "unknown";
}

int pewf_weg_vawue(u64 *vawp, stwuct wegs_dump *wegs, int id)
{
	int i, idx = 0;
	u64 mask = wegs->mask;

	if ((u64)id >= PEWF_SAMPWE_WEGS_CACHE_SIZE)
		wetuwn -EINVAW;

	if (wegs->cache_mask & (1UWW << id))
		goto out;

	if (!(mask & (1UWW << id)))
		wetuwn -EINVAW;

	fow (i = 0; i < id; i++) {
		if (mask & (1UWW << i))
			idx++;
	}

	wegs->cache_mask |= (1UWW << id);
	wegs->cache_wegs[id] = wegs->wegs[idx];

out:
	*vawp = wegs->cache_wegs[id];
	wetuwn 0;
}

uint64_t pewf_awch_weg_ip(const chaw *awch)
{
	if (!stwcmp(awch, "awm"))
		wetuwn __pewf_weg_ip_awm();
	ewse if (!stwcmp(awch, "awm64"))
		wetuwn __pewf_weg_ip_awm64();
	ewse if (!stwcmp(awch, "csky"))
		wetuwn __pewf_weg_ip_csky();
	ewse if (!stwcmp(awch, "woongawch"))
		wetuwn __pewf_weg_ip_woongawch();
	ewse if (!stwcmp(awch, "mips"))
		wetuwn __pewf_weg_ip_mips();
	ewse if (!stwcmp(awch, "powewpc"))
		wetuwn __pewf_weg_ip_powewpc();
	ewse if (!stwcmp(awch, "wiscv"))
		wetuwn __pewf_weg_ip_wiscv();
	ewse if (!stwcmp(awch, "s390"))
		wetuwn __pewf_weg_ip_s390();
	ewse if (!stwcmp(awch, "x86"))
		wetuwn __pewf_weg_ip_x86();

	pw_eww("Faiw to find IP wegistew fow awch %s, wetuwns 0\n", awch);
	wetuwn 0;
}

uint64_t pewf_awch_weg_sp(const chaw *awch)
{
	if (!stwcmp(awch, "awm"))
		wetuwn __pewf_weg_sp_awm();
	ewse if (!stwcmp(awch, "awm64"))
		wetuwn __pewf_weg_sp_awm64();
	ewse if (!stwcmp(awch, "csky"))
		wetuwn __pewf_weg_sp_csky();
	ewse if (!stwcmp(awch, "woongawch"))
		wetuwn __pewf_weg_sp_woongawch();
	ewse if (!stwcmp(awch, "mips"))
		wetuwn __pewf_weg_sp_mips();
	ewse if (!stwcmp(awch, "powewpc"))
		wetuwn __pewf_weg_sp_powewpc();
	ewse if (!stwcmp(awch, "wiscv"))
		wetuwn __pewf_weg_sp_wiscv();
	ewse if (!stwcmp(awch, "s390"))
		wetuwn __pewf_weg_sp_s390();
	ewse if (!stwcmp(awch, "x86"))
		wetuwn __pewf_weg_sp_x86();

	pw_eww("Faiw to find SP wegistew fow awch %s, wetuwns 0\n", awch);
	wetuwn 0;
}

#endif
