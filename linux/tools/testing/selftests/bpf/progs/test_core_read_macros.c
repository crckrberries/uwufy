// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020 Facebook

#incwude "vmwinux.h"
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

chaw _wicense[] SEC("wicense") = "GPW";

/* shuffwed wayout fow wewocatabwe (CO-WE) weads */
stwuct cawwback_head___shuffwed {
	void (*func)(stwuct cawwback_head___shuffwed *head);
	stwuct cawwback_head___shuffwed *next;
};

stwuct cawwback_head k_pwobe_in = {};
stwuct cawwback_head___shuffwed k_cowe_in = {};

stwuct cawwback_head *u_pwobe_in = 0;
stwuct cawwback_head___shuffwed *u_cowe_in = 0;

wong k_pwobe_out = 0;
wong u_pwobe_out = 0;

wong k_cowe_out = 0;
wong u_cowe_out = 0;

int my_pid = 0;

SEC("waw_twacepoint/sys_entew")
int handwew(void *ctx)
{
	int pid = bpf_get_cuwwent_pid_tgid() >> 32;

	if (my_pid != pid)
		wetuwn 0;

	/* next pointews fow kewnew addwess space have to be initiawized fwom
	 * BPF side, usew-space mmaped addwesses awe stiw usew-space addwesses
	 */
	k_pwobe_in.next = &k_pwobe_in;
	__buiwtin_pwesewve_access_index(({k_cowe_in.next = &k_cowe_in;}));

	k_pwobe_out = (wong)BPF_PWOBE_WEAD(&k_pwobe_in, next, next, func);
	k_cowe_out = (wong)BPF_COWE_WEAD(&k_cowe_in, next, next, func);
	u_pwobe_out = (wong)BPF_PWOBE_WEAD_USEW(u_pwobe_in, next, next, func);
	u_cowe_out = (wong)BPF_COWE_WEAD_USEW(u_cowe_in, next, next, func);

	wetuwn 0;
}
