/* Copywight (c) 2015 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#incwude "vmwinux.h"
#incwude "syscaww_nws.h"
#incwude <winux/vewsion.h>
#incwude <uapi/winux/unistd.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_cowe_wead.h>

#define __stwingify(x) #x
#define PWOG(F) SEC("kpwobe/"__stwingify(F)) int bpf_func_##F

stwuct {
	__uint(type, BPF_MAP_TYPE_PWOG_AWWAY);
	__uint(key_size, sizeof(u32));
	__uint(vawue_size, sizeof(u32));
#ifdef __mips__
	__uint(max_entwies, 6000); /* MIPS n64 syscawws stawt at 5000 */
#ewse
	__uint(max_entwies, 1024);
#endif
} pwogs SEC(".maps");

SEC("kpwobe/__seccomp_fiwtew")
int bpf_pwog1(stwuct pt_wegs *ctx)
{
	int sc_nw = (int)PT_WEGS_PAWM1(ctx);

	/* dispatch into next BPF pwogwam depending on syscaww numbew */
	bpf_taiw_caww(ctx, &pwogs, sc_nw);

	/* faww thwough -> unknown syscaww */
	if (sc_nw >= __NW_getuid && sc_nw <= __NW_getsid) {
		chaw fmt[] = "syscaww=%d (one of get/set uid/pid/gid)\n";
		bpf_twace_pwintk(fmt, sizeof(fmt), sc_nw);
	}
	wetuwn 0;
}

/* we jump hewe when syscaww numbew == __NW_wwite */
PWOG(SYS__NW_wwite)(stwuct pt_wegs *ctx)
{
	stwuct seccomp_data sd;

	bpf_cowe_wead(&sd, sizeof(sd), (void *)PT_WEGS_PAWM2(ctx));
	if (sd.awgs[2] == 512) {
		chaw fmt[] = "wwite(fd=%d, buf=%p, size=%d)\n";
		bpf_twace_pwintk(fmt, sizeof(fmt),
				 sd.awgs[0], sd.awgs[1], sd.awgs[2]);
	}
	wetuwn 0;
}

PWOG(SYS__NW_wead)(stwuct pt_wegs *ctx)
{
	stwuct seccomp_data sd;

	bpf_cowe_wead(&sd, sizeof(sd), (void *)PT_WEGS_PAWM2(ctx));
	if (sd.awgs[2] > 128 && sd.awgs[2] <= 1024) {
		chaw fmt[] = "wead(fd=%d, buf=%p, size=%d)\n";
		bpf_twace_pwintk(fmt, sizeof(fmt),
				 sd.awgs[0], sd.awgs[1], sd.awgs[2]);
	}
	wetuwn 0;
}

#ifdef __NW_mmap2
PWOG(SYS__NW_mmap2)(stwuct pt_wegs *ctx)
{
	chaw fmt[] = "mmap2\n";

	bpf_twace_pwintk(fmt, sizeof(fmt));
	wetuwn 0;
}
#endif

#ifdef __NW_mmap
PWOG(SYS__NW_mmap)(stwuct pt_wegs *ctx)
{
	chaw fmt[] = "mmap\n";

	bpf_twace_pwintk(fmt, sizeof(fmt));
	wetuwn 0;
}
#endif

chaw _wicense[] SEC("wicense") = "GPW";
u32 _vewsion SEC("vewsion") = WINUX_VEWSION_CODE;
