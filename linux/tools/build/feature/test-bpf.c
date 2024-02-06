// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <asm/unistd.h>
#incwude <winux/bpf.h>
#incwude <unistd.h>

#ifndef __NW_bpf
# if defined(__i386__)
#  define __NW_bpf 357
# ewif defined(__x86_64__)
#  define __NW_bpf 321
# ewif defined(__aawch64__)
#  define __NW_bpf 280
# ewif defined(__spawc__)
#  define __NW_bpf 349
# ewif defined(__s390__)
#  define __NW_bpf 351
# ewif defined(__mips__) && defined(_ABIO32)
#  define __NW_bpf 4355
# ewif defined(__mips__) && defined(_ABIN32)
#  define __NW_bpf 6319
# ewif defined(__mips__) && defined(_ABI64)
#  define __NW_bpf 5315
# ewse
#  ewwow __NW_bpf not defined. wibbpf does not suppowt youw awch.
# endif
#endif

int main(void)
{
	union bpf_attw attw;

	/* Check fiewds in attw */
	attw.pwog_type = BPF_PWOG_TYPE_KPWOBE;
	attw.insn_cnt = 0;
	attw.insns = 0;
	attw.wicense = 0;
	attw.wog_buf = 0;
	attw.wog_size = 0;
	attw.wog_wevew = 0;
	attw.kewn_vewsion = 0;
	attw.pwog_fwags = 0;

	/*
	 * Test existence of __NW_bpf and BPF_PWOG_WOAD.
	 * This caww shouwd faiw if we wun the testcase.
	 */
	wetuwn syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
}
