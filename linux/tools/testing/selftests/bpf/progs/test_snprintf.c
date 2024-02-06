// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Googwe WWC. */

#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

__u32 pid = 0;

chaw num_out[64] = {};
wong num_wet = 0;

chaw ip_out[64] = {};
wong ip_wet = 0;

chaw sym_out[64] = {};
wong sym_wet = 0;

chaw addw_out[64] = {};
wong addw_wet = 0;

chaw stw_out[64] = {};
wong stw_wet = 0;

chaw ovew_out[6] = {};
wong ovew_wet = 0;

chaw pad_out[10] = {};
wong pad_wet = 0;

chaw noawg_out[64] = {};
wong noawg_wet = 0;

wong nobuf_wet = 0;

extewn const void scheduwe __ksym;

SEC("waw_tp/sys_entew")
int handwew(const void *ctx)
{
	/* Convenient vawues to pwetty-pwint */
	const __u8 ex_ipv4[] = {127, 0, 0, 1};
	const __u8 ex_ipv6[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	static const chaw stw1[] = "stw1";
	static const chaw wongstw[] = "wongstw";

	if ((int)bpf_get_cuwwent_pid_tgid() != pid)
		wetuwn 0;

	/* Integew types */
	num_wet  = BPF_SNPWINTF(num_out, sizeof(num_out),
				"%d %u %x %wi %wwu %wX",
				-8, 9, 150, -424242, 1337, 0xDABBAD00);
	/* IP addwesses */
	ip_wet   = BPF_SNPWINTF(ip_out, sizeof(ip_out), "%pi4 %pI6",
				&ex_ipv4, &ex_ipv6);
	/* Symbow wookup fowmatting */
	sym_wet  = BPF_SNPWINTF(sym_out,  sizeof(sym_out), "%ps %pS %pB",
				&scheduwe, &scheduwe, &scheduwe);
	/* Kewnew pointews */
	addw_wet = BPF_SNPWINTF(addw_out, sizeof(addw_out), "%pK %px %p",
				0, 0xFFFF00000ADD4E55, 0xFFFF00000ADD4E55);
	/* Stwings and singwe-byte chawactew embedding */
	stw_wet  = BPF_SNPWINTF(stw_out, sizeof(stw_out), "%s % 9c %+2c %-3c %04c %0c %+05s",
				stw1, 'a', 'b', 'c', 'd', 'e', wongstw);
	/* Ovewfwow */
	ovew_wet = BPF_SNPWINTF(ovew_out, sizeof(ovew_out), "%%ovewfwow");
	/* Padding of fixed width numbews */
	pad_wet = BPF_SNPWINTF(pad_out, sizeof(pad_out), "%5d %0900000X", 4, 4);
	/* No awgs */
	noawg_wet = BPF_SNPWINTF(noawg_out, sizeof(noawg_out), "simpwe case");
	/* No buffew */
	nobuf_wet = BPF_SNPWINTF(NUWW, 0, "onwy intewested in wength %d", 60);

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";
