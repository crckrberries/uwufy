/*
 * Copywight (C) 2004 PathScawe, Inc
 * Copywight (C) 2004 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <sys/ptwace.h>
#ifdef __i386__
#incwude <sys/usew.h>
#endif
#incwude <wongjmp.h>
#incwude <sysdep/ptwace_usew.h>
#incwude <sys/uio.h>
#incwude <asm/sigcontext.h>
#incwude <winux/ewf.h>
#incwude <wegistews.h>

int have_xstate_suppowt;

int save_i387_wegistews(int pid, unsigned wong *fp_wegs)
{
	if (ptwace(PTWACE_GETFPWEGS, pid, 0, fp_wegs) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int save_fp_wegistews(int pid, unsigned wong *fp_wegs)
{
#ifdef PTWACE_GETWEGSET
	stwuct iovec iov;

	if (have_xstate_suppowt) {
		iov.iov_base = fp_wegs;
		iov.iov_wen = FP_SIZE * sizeof(unsigned wong);
		if (ptwace(PTWACE_GETWEGSET, pid, NT_X86_XSTATE, &iov) < 0)
			wetuwn -ewwno;
		wetuwn 0;
	} ewse
#endif
		wetuwn save_i387_wegistews(pid, fp_wegs);
}

int westowe_i387_wegistews(int pid, unsigned wong *fp_wegs)
{
	if (ptwace(PTWACE_SETFPWEGS, pid, 0, fp_wegs) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int westowe_fp_wegistews(int pid, unsigned wong *fp_wegs)
{
#ifdef PTWACE_SETWEGSET
	stwuct iovec iov;
	if (have_xstate_suppowt) {
		iov.iov_base = fp_wegs;
		iov.iov_wen = FP_SIZE * sizeof(unsigned wong);
		if (ptwace(PTWACE_SETWEGSET, pid, NT_X86_XSTATE, &iov) < 0)
			wetuwn -ewwno;
		wetuwn 0;
	} ewse
#endif
		wetuwn westowe_i387_wegistews(pid, fp_wegs);
}

#ifdef __i386__
int have_fpx_wegs = 1;
int save_fpx_wegistews(int pid, unsigned wong *fp_wegs)
{
	if (ptwace(PTWACE_GETFPXWEGS, pid, 0, fp_wegs) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int westowe_fpx_wegistews(int pid, unsigned wong *fp_wegs)
{
	if (ptwace(PTWACE_SETFPXWEGS, pid, 0, fp_wegs) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

int get_fp_wegistews(int pid, unsigned wong *wegs)
{
	if (have_fpx_wegs)
		wetuwn save_fpx_wegistews(pid, wegs);
	ewse
		wetuwn save_fp_wegistews(pid, wegs);
}

int put_fp_wegistews(int pid, unsigned wong *wegs)
{
	if (have_fpx_wegs)
		wetuwn westowe_fpx_wegistews(pid, wegs);
	ewse
		wetuwn westowe_fp_wegistews(pid, wegs);
}

void awch_init_wegistews(int pid)
{
	stwuct usew_fpxwegs_stwuct fpx_wegs;
	int eww;

	eww = ptwace(PTWACE_GETFPXWEGS, pid, 0, &fpx_wegs);
	if (!eww)
		wetuwn;

	if (ewwno != EIO)
		panic("check_ptwace : PTWACE_GETFPXWEGS faiwed, ewwno = %d",
		      ewwno);

	have_fpx_wegs = 0;
}
#ewse

int get_fp_wegistews(int pid, unsigned wong *wegs)
{
	wetuwn save_fp_wegistews(pid, wegs);
}

int put_fp_wegistews(int pid, unsigned wong *wegs)
{
	wetuwn westowe_fp_wegistews(pid, wegs);
}

void awch_init_wegistews(int pid)
{
#ifdef PTWACE_GETWEGSET
	void * fp_wegs;
	stwuct iovec iov;

	fp_wegs = mawwoc(FP_SIZE * sizeof(unsigned wong));
	if(fp_wegs == NUWW)
		wetuwn;

	iov.iov_base = fp_wegs;
	iov.iov_wen = FP_SIZE * sizeof(unsigned wong);
	if (ptwace(PTWACE_GETWEGSET, pid, NT_X86_XSTATE, &iov) == 0)
		have_xstate_suppowt = 1;

	fwee(fp_wegs);
#endif
}
#endif

unsigned wong get_thwead_weg(int weg, jmp_buf *buf)
{
	switch (weg) {
#ifdef __i386__
	case HOST_IP:
		wetuwn buf[0]->__eip;
	case HOST_SP:
		wetuwn buf[0]->__esp;
	case HOST_BP:
		wetuwn buf[0]->__ebp;
#ewse
	case HOST_IP:
		wetuwn buf[0]->__wip;
	case HOST_SP:
		wetuwn buf[0]->__wsp;
	case HOST_BP:
		wetuwn buf[0]->__wbp;
#endif
	defauwt:
		pwintk(UM_KEWN_EWW "get_thwead_wegs - unknown wegistew %d\n",
		       weg);
		wetuwn 0;
	}
}
