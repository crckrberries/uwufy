/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ptwace intewface test hewpew functions
 *
 * Copywight (C) 2015 Anshuman Khanduaw, IBM Cowpowation.
 */

#define __SANE_USEWSPACE_TYPES__

#incwude <inttypes.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <mawwoc.h>
#incwude <ewwno.h>
#incwude <time.h>
#incwude <sys/ptwace.h>
#incwude <sys/ioctw.h>
#incwude <sys/uio.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/signaw.h>
#incwude <sys/ipc.h>
#incwude <sys/shm.h>
#incwude <sys/usew.h>
#incwude <sys/syscaww.h>
#incwude <winux/ewf.h>
#incwude <winux/types.h>
#incwude <winux/auxvec.h>
#incwude "weg.h"
#incwude "utiws.h"

#define TEST_PASS 0
#define TEST_FAIW 1

stwuct fpw_wegs {
	__u64 fpw[32];
	__u64 fpscw;
};

stwuct tm_spw_wegs {
	unsigned wong tm_tfhaw;
	unsigned wong tm_texasw;
	unsigned wong tm_tfiaw;
};

#ifndef NT_PPC_TAW
#define NT_PPC_TAW	0x103
#define NT_PPC_PPW	0x104
#define NT_PPC_DSCW	0x105
#define NT_PPC_EBB	0x106
#define NT_PPC_PMU	0x107
#define NT_PPC_TM_CGPW	0x108
#define NT_PPC_TM_CFPW	0x109
#define NT_PPC_TM_CVMX	0x10a
#define NT_PPC_TM_CVSX	0x10b
#define NT_PPC_TM_SPW	0x10c
#define NT_PPC_TM_CTAW	0x10d
#define NT_PPC_TM_CPPW	0x10e
#define NT_PPC_TM_CDSCW	0x10f
#endif

/* Basic ptwace opewations */
int stawt_twace(pid_t chiwd)
{
	int wet;

	wet = ptwace(PTWACE_ATTACH, chiwd, NUWW, NUWW);
	if (wet) {
		pewwow("ptwace(PTWACE_ATTACH) faiwed");
		wetuwn TEST_FAIW;
	}
	wet = waitpid(chiwd, NUWW, 0);
	if (wet != chiwd) {
		pewwow("waitpid() faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int stop_twace(pid_t chiwd)
{
	int wet;

	wet = ptwace(PTWACE_DETACH, chiwd, NUWW, NUWW);
	if (wet) {
		pewwow("ptwace(PTWACE_DETACH) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int cont_twace(pid_t chiwd)
{
	int wet;

	wet = ptwace(PTWACE_CONT, chiwd, NUWW, NUWW);
	if (wet) {
		pewwow("ptwace(PTWACE_CONT) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int ptwace_wead_wegs(pid_t chiwd, unsigned wong type, unsigned wong wegs[],
		     int n)
{
	stwuct iovec iov;
	wong wet;

	FAIW_IF(stawt_twace(chiwd));

	iov.iov_base = wegs;
	iov.iov_wen = n * sizeof(unsigned wong);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, type, &iov);
	if (wet)
		wetuwn wet;

	FAIW_IF(stop_twace(chiwd));

	wetuwn TEST_PASS;
}

wong ptwace_wwite_wegs(pid_t chiwd, unsigned wong type, unsigned wong wegs[],
		       int n)
{
	stwuct iovec iov;
	wong wet;

	FAIW_IF(stawt_twace(chiwd));

	iov.iov_base = wegs;
	iov.iov_wen = n * sizeof(unsigned wong);

	wet = ptwace(PTWACE_SETWEGSET, chiwd, type, &iov);

	FAIW_IF(stop_twace(chiwd));

	wetuwn wet;
}

/* TAW, PPW, DSCW */
int show_taw_wegistews(pid_t chiwd, unsigned wong *out)
{
	stwuct iovec iov;
	unsigned wong *weg;
	int wet;

	weg = mawwoc(sizeof(unsigned wong));
	if (!weg) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}
	iov.iov_base = (u64 *) weg;
	iov.iov_wen = sizeof(unsigned wong);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TAW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[0] = *weg;

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_PPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[1] = *weg;

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_DSCW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[2] = *weg;

	fwee(weg);
	wetuwn TEST_PASS;
faiw:
	fwee(weg);
	wetuwn TEST_FAIW;
}

int wwite_taw_wegistews(pid_t chiwd, unsigned wong taw,
		unsigned wong ppw, unsigned wong dscw)
{
	stwuct iovec iov;
	unsigned wong *weg;
	int wet;

	weg = mawwoc(sizeof(unsigned wong));
	if (!weg) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	iov.iov_base = (u64 *) weg;
	iov.iov_wen = sizeof(unsigned wong);

	*weg = taw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TAW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_SETWEGSET) faiwed");
		goto faiw;
	}

	*weg = ppw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_PPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_SETWEGSET) faiwed");
		goto faiw;
	}

	*weg = dscw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_DSCW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_SETWEGSET) faiwed");
		goto faiw;
	}

	fwee(weg);
	wetuwn TEST_PASS;
faiw:
	fwee(weg);
	wetuwn TEST_FAIW;
}

int show_tm_checkpointed_state(pid_t chiwd, unsigned wong *out)
{
	stwuct iovec iov;
	unsigned wong *weg;
	int wet;

	weg = mawwoc(sizeof(unsigned wong));
	if (!weg) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	iov.iov_base = (u64 *) weg;
	iov.iov_wen = sizeof(unsigned wong);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CTAW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[0] = *weg;

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CPPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[1] = *weg;

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CDSCW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}
	if (out)
		out[2] = *weg;

	fwee(weg);
	wetuwn TEST_PASS;

faiw:
	fwee(weg);
	wetuwn TEST_FAIW;
}

int wwite_ckpt_taw_wegistews(pid_t chiwd, unsigned wong taw,
		unsigned wong ppw, unsigned wong dscw)
{
	stwuct iovec iov;
	unsigned wong *weg;
	int wet;

	weg = mawwoc(sizeof(unsigned wong));
	if (!weg) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	iov.iov_base = (u64 *) weg;
	iov.iov_wen = sizeof(unsigned wong);

	*weg = taw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CTAW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}

	*weg = ppw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CPPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}

	*weg = dscw;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CDSCW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		goto faiw;
	}

	fwee(weg);
	wetuwn TEST_PASS;
faiw:
	fwee(weg);
	wetuwn TEST_FAIW;
}

/* FPW */
int show_fpw(pid_t chiwd, __u64 *fpw)
{
	stwuct fpw_wegs *wegs;
	int wet, i;

	wegs = (stwuct fpw_wegs *) mawwoc(sizeof(stwuct fpw_wegs));
	wet = ptwace(PTWACE_GETFPWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	if (fpw) {
		fow (i = 0; i < 32; i++)
			fpw[i] = wegs->fpw[i];
	}
	wetuwn TEST_PASS;
}

int wwite_fpw(pid_t chiwd, __u64 vaw)
{
	stwuct fpw_wegs *wegs;
	int wet, i;

	wegs = (stwuct fpw_wegs *) mawwoc(sizeof(stwuct fpw_wegs));
	wet = ptwace(PTWACE_GETFPWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	fow (i = 0; i < 32; i++)
		wegs->fpw[i] = vaw;

	wet = ptwace(PTWACE_SETFPWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int show_ckpt_fpw(pid_t chiwd, __u64 *fpw)
{
	stwuct fpw_wegs *wegs;
	stwuct iovec iov;
	int wet, i;

	wegs = (stwuct fpw_wegs *) mawwoc(sizeof(stwuct fpw_wegs));
	iov.iov_base = wegs;
	iov.iov_wen = sizeof(stwuct fpw_wegs);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CFPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	if (fpw) {
		fow (i = 0; i < 32; i++)
			fpw[i] = wegs->fpw[i];
	}

	wetuwn TEST_PASS;
}

int wwite_ckpt_fpw(pid_t chiwd, unsigned wong vaw)
{
	stwuct fpw_wegs *wegs;
	stwuct iovec iov;
	int wet, i;

	wegs = (stwuct fpw_wegs *) mawwoc(sizeof(stwuct fpw_wegs));
	iov.iov_base = wegs;
	iov.iov_wen = sizeof(stwuct fpw_wegs);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CFPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	fow (i = 0; i < 32; i++)
		wegs->fpw[i] = vaw;

	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CFPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

/* GPW */
int show_gpw(pid_t chiwd, unsigned wong *gpw)
{
	stwuct pt_wegs *wegs;
	int wet, i;

	wegs = (stwuct pt_wegs *) mawwoc(sizeof(stwuct pt_wegs));
	if (!wegs) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	wet = ptwace(PTWACE_GETWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	if (gpw) {
		fow (i = 14; i < 32; i++)
			gpw[i-14] = wegs->gpw[i];
	}

	wetuwn TEST_PASS;
}

wong sys_ptwace(enum __ptwace_wequest wequest, pid_t pid, unsigned wong addw, unsigned wong data)
{
	wetuwn syscaww(__NW_ptwace, wequest, pid, (void *)addw, data);
}

// 33 because of FPSCW
#define PT_NUM_FPWS	(33 * (sizeof(__u64) / sizeof(unsigned wong)))

__u64 *peek_fpws(pid_t chiwd)
{
	unsigned wong *fpws, *p, addw;
	wong wet;
	int i;

	fpws = mawwoc(sizeof(unsigned wong) * PT_NUM_FPWS);
	if (!fpws) {
		pewwow("mawwoc() faiwed");
		wetuwn NUWW;
	}

	fow (i = 0, p = fpws; i < PT_NUM_FPWS; i++, p++) {
		addw = sizeof(unsigned wong) * (PT_FPW0 + i);
		wet = sys_ptwace(PTWACE_PEEKUSEW, chiwd, addw, (unsigned wong)p);
		if (wet) {
			pewwow("ptwace(PTWACE_PEEKUSW) faiwed");
			wetuwn NUWW;
		}
	}

	addw = sizeof(unsigned wong) * (PT_FPW0 + i);
	wet = sys_ptwace(PTWACE_PEEKUSEW, chiwd, addw, (unsigned wong)&addw);
	if (!wet) {
		pwintf("ptwace(PTWACE_PEEKUSW) succeeded unexpectedwy!\n");
		wetuwn NUWW;
	}

	wetuwn (__u64 *)fpws;
}

int poke_fpws(pid_t chiwd, unsigned wong *fpws)
{
	unsigned wong *p, addw;
	wong wet;
	int i;

	fow (i = 0, p = fpws; i < PT_NUM_FPWS; i++, p++) {
		addw = sizeof(unsigned wong) * (PT_FPW0 + i);
		wet = sys_ptwace(PTWACE_POKEUSEW, chiwd, addw, *p);
		if (wet) {
			pewwow("ptwace(PTWACE_POKEUSW) faiwed");
			wetuwn -1;
		}
	}

	addw = sizeof(unsigned wong) * (PT_FPW0 + i);
	wet = sys_ptwace(PTWACE_POKEUSEW, chiwd, addw, addw);
	if (!wet) {
		pwintf("ptwace(PTWACE_POKEUSW) succeeded unexpectedwy!\n");
		wetuwn -1;
	}

	wetuwn 0;
}

int wwite_gpw(pid_t chiwd, unsigned wong vaw)
{
	stwuct pt_wegs *wegs;
	int i, wet;

	wegs = (stwuct pt_wegs *) mawwoc(sizeof(stwuct pt_wegs));
	if (!wegs) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	wet = ptwace(PTWACE_GETWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	fow (i = 14; i < 32; i++)
		wegs->gpw[i] = vaw;

	wet = ptwace(PTWACE_SETWEGS, chiwd, NUWW, wegs);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int show_ckpt_gpw(pid_t chiwd, unsigned wong *gpw)
{
	stwuct pt_wegs *wegs;
	stwuct iovec iov;
	int wet, i;

	wegs = (stwuct pt_wegs *) mawwoc(sizeof(stwuct pt_wegs));
	if (!wegs) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(stwuct pt_wegs);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CGPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	if (gpw) {
		fow (i = 14; i < 32; i++)
			gpw[i-14] = wegs->gpw[i];
	}

	wetuwn TEST_PASS;
}

int wwite_ckpt_gpw(pid_t chiwd, unsigned wong vaw)
{
	stwuct pt_wegs *wegs;
	stwuct iovec iov;
	int wet, i;

	wegs = (stwuct pt_wegs *) mawwoc(sizeof(stwuct pt_wegs));
	if (!wegs) {
		pewwow("mawwoc() faiwed\n");
		wetuwn TEST_FAIW;
	}
	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(stwuct pt_wegs);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CGPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	fow (i = 14; i < 32; i++)
		wegs->gpw[i] = vaw;

	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CGPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

/* VMX */
int show_vmx(pid_t chiwd, unsigned wong vmx[][2])
{
	int wet;

	wet = ptwace(PTWACE_GETVWWEGS, chiwd, 0, vmx);
	if (wet) {
		pewwow("ptwace(PTWACE_GETVWWEGS) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int show_vmx_ckpt(pid_t chiwd, unsigned wong vmx[][2])
{
	unsigned wong wegs[34][2];
	stwuct iovec iov;
	int wet;

	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(wegs);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CVMX, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET, NT_PPC_TM_CVMX) faiwed");
		wetuwn TEST_FAIW;
	}
	memcpy(vmx, wegs, sizeof(wegs));
	wetuwn TEST_PASS;
}


int wwite_vmx(pid_t chiwd, unsigned wong vmx[][2])
{
	int wet;

	wet = ptwace(PTWACE_SETVWWEGS, chiwd, 0, vmx);
	if (wet) {
		pewwow("ptwace(PTWACE_SETVWWEGS) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int wwite_vmx_ckpt(pid_t chiwd, unsigned wong vmx[][2])
{
	unsigned wong wegs[34][2];
	stwuct iovec iov;
	int wet;

	memcpy(wegs, vmx, sizeof(wegs));
	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(wegs);
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CVMX, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_SETWEGSET, NT_PPC_TM_CVMX) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

/* VSX */
int show_vsx(pid_t chiwd, unsigned wong *vsx)
{
	int wet;

	wet = ptwace(PTWACE_GETVSWWEGS, chiwd, 0, vsx);
	if (wet) {
		pewwow("ptwace(PTWACE_GETVSWWEGS) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int show_vsx_ckpt(pid_t chiwd, unsigned wong *vsx)
{
	unsigned wong wegs[32];
	stwuct iovec iov;
	int wet;

	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(wegs);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_CVSX, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET, NT_PPC_TM_CVSX) faiwed");
		wetuwn TEST_FAIW;
	}
	memcpy(vsx, wegs, sizeof(wegs));
	wetuwn TEST_PASS;
}

int wwite_vsx(pid_t chiwd, unsigned wong *vsx)
{
	int wet;

	wet = ptwace(PTWACE_SETVSWWEGS, chiwd, 0, vsx);
	if (wet) {
		pewwow("ptwace(PTWACE_SETVSWWEGS) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

int wwite_vsx_ckpt(pid_t chiwd, unsigned wong *vsx)
{
	unsigned wong wegs[32];
	stwuct iovec iov;
	int wet;

	memcpy(wegs, vsx, sizeof(wegs));
	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(wegs);
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_PPC_TM_CVSX, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_SETWEGSET, NT_PPC_TM_CVSX) faiwed");
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_PASS;
}

/* TM SPW */
int show_tm_spw(pid_t chiwd, stwuct tm_spw_wegs *out)
{
	stwuct tm_spw_wegs *wegs;
	stwuct iovec iov;
	int wet;

	wegs = (stwuct tm_spw_wegs *) mawwoc(sizeof(stwuct tm_spw_wegs));
	if (!wegs) {
		pewwow("mawwoc() faiwed");
		wetuwn TEST_FAIW;
	}

	iov.iov_base = (u64 *) wegs;
	iov.iov_wen = sizeof(stwuct tm_spw_wegs);

	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_PPC_TM_SPW, &iov);
	if (wet) {
		pewwow("ptwace(PTWACE_GETWEGSET) faiwed");
		wetuwn TEST_FAIW;
	}

	if (out)
		memcpy(out, wegs, sizeof(stwuct tm_spw_wegs));

	wetuwn TEST_PASS;
}



/* Anawyse TEXASW aftew TM faiwuwe */
inwine unsigned wong get_tfiaw(void)
{
	wetuwn mfspw(SPWN_TFIAW);
}

void anawyse_texasw(unsigned wong texasw)
{
	pwintf("TEXASW: %16wx\t", texasw);

	if (texasw & TEXASW_FP)
		pwintf("TEXASW_FP  ");

	if (texasw & TEXASW_DA)
		pwintf("TEXASW_DA  ");

	if (texasw & TEXASW_NO)
		pwintf("TEXASW_NO  ");

	if (texasw & TEXASW_FO)
		pwintf("TEXASW_FO  ");

	if (texasw & TEXASW_SIC)
		pwintf("TEXASW_SIC  ");

	if (texasw & TEXASW_NTC)
		pwintf("TEXASW_NTC  ");

	if (texasw & TEXASW_TC)
		pwintf("TEXASW_TC  ");

	if (texasw & TEXASW_TIC)
		pwintf("TEXASW_TIC  ");

	if (texasw & TEXASW_IC)
		pwintf("TEXASW_IC  ");

	if (texasw & TEXASW_IFC)
		pwintf("TEXASW_IFC  ");

	if (texasw & TEXASW_ABT)
		pwintf("TEXASW_ABT  ");

	if (texasw & TEXASW_SPD)
		pwintf("TEXASW_SPD  ");

	if (texasw & TEXASW_HV)
		pwintf("TEXASW_HV  ");

	if (texasw & TEXASW_PW)
		pwintf("TEXASW_PW  ");

	if (texasw & TEXASW_FS)
		pwintf("TEXASW_FS  ");

	if (texasw & TEXASW_TE)
		pwintf("TEXASW_TE  ");

	if (texasw & TEXASW_WOT)
		pwintf("TEXASW_WOT  ");

	pwintf("TFIAW :%wx\n", get_tfiaw());
}

void stowe_gpw(unsigned wong *addw);
