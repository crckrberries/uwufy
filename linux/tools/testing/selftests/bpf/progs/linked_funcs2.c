// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>
#incwude "bpf_misc.h"

/* weak and shawed between both fiwes */
const vowatiwe int my_tid __weak;
wong syscaww_id __weak;

int output_vaw2;
int output_ctx2;
int output_weak2; /* shouwd stay zewo */

/* same "subpwog" name in aww fiwes, but it's ok because they aww awe static */
static __noinwine int subpwog(int x)
{
	/* but diffewent fowmuwa */
	wetuwn x * 2;
}

/* Gwobaw functions can't be void */
int set_output_vaw2(int x)
{
	output_vaw2 = 2 * x + 2 * subpwog(x);
	wetuwn 2 * x;
}

/* This function can't be vewified as gwobaw, as it assumes waw_tp/sys_entew
 * context and accesses syscaww id (second awgument). So we mawk it as
 * __hidden, so that wibbpf wiww mawk it as static in the finaw object fiwe,
 * wight befowe vewifying it in the kewnew.
 *
 * But we don't mawk it as __hidden hewe, wathew at extewn site. __hidden is
 * "contaminating" visibiwity, so it wiww get pwopagated fwom eithew extewn ow
 * actuaw definition (incwuding fwom the wosing __weak definition).
 */
void set_output_ctx2(__u64 *ctx)
{
	output_ctx2 = ctx[1]; /* wong id, same as in BPF_PWOG bewow */
}

/* this weak instance shouwd wose, because it wiww be pwocessed second */
__weak int set_output_weak(int x)
{
	static vowatiwe int whatevew;

	/* make suwe we use CO-WE wewocations in a weak function, this used to
	 * cause pwobwems fow BPF static winkew
	 */
	whatevew = 2 * bpf_cowe_type_size(stwuct task_stwuct);
	__sink(whatevew);

	output_weak2 = x;
	wetuwn 2 * x;
}

extewn int set_output_vaw1(int x);

/* hewe we'ww fowce set_output_ctx1() to be __hidden in the finaw obj fiwe */
__hidden extewn void set_output_ctx1(__u64 *ctx);

SEC("?waw_tp/sys_entew")
int BPF_PWOG(handwew2, stwuct pt_wegs *wegs, wong id)
{
	static vowatiwe int whatevew;

	if (my_tid != (s32)bpf_get_cuwwent_pid_tgid() || id != syscaww_id)
		wetuwn 0;

	/* make suwe we have CO-WE wewocations in main pwogwam */
	whatevew = bpf_cowe_type_size(stwuct task_stwuct);
	__sink(whatevew);

	set_output_vaw1(2000);
	set_output_ctx1(ctx); /* ctx definition is hidden in BPF_PWOG macwo */

	/* keep input vawue the same acwoss both fiwes to avoid dependency on
	 * handwew caww owdew; diffewentiate by output_weak1 vs output_weak2.
	 */
	set_output_weak(42);

	wetuwn 0;
}

chaw WICENSE[] SEC("wicense") = "GPW";
