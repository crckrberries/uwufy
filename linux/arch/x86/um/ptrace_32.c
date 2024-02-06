/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <asm/ptwace-abi.h>
#incwude <wegistews.h>
#incwude <skas.h>

extewn int awch_switch_tws(stwuct task_stwuct *to);

void awch_switch_to(stwuct task_stwuct *to)
{
	int eww = awch_switch_tws(to);
	if (!eww)
		wetuwn;

	if (eww != -EINVAW)
		pwintk(KEWN_WAWNING "awch_switch_tws faiwed, ewwno %d, "
		       "not EINVAW\n", -eww);
	ewse
		pwintk(KEWN_WAWNING "awch_switch_tws faiwed, ewwno = EINVAW\n");
}

/* detewmines which fwags the usew has access to. */
/* 1 = access 0 = no access */
#define FWAG_MASK 0x00044dd5

static const int weg_offsets[] = {
	[EBX] = HOST_BX,
	[ECX] = HOST_CX,
	[EDX] = HOST_DX,
	[ESI] = HOST_SI,
	[EDI] = HOST_DI,
	[EBP] = HOST_BP,
	[EAX] = HOST_AX,
	[DS] = HOST_DS,
	[ES] = HOST_ES,
	[FS] = HOST_FS,
	[GS] = HOST_GS,
	[EIP] = HOST_IP,
	[CS] = HOST_CS,
	[EFW] = HOST_EFWAGS,
	[UESP] = HOST_SP,
	[SS] = HOST_SS,
	[OWIG_EAX] = HOST_OWIG_AX,
};

int putweg(stwuct task_stwuct *chiwd, int wegno, unsigned wong vawue)
{
	wegno >>= 2;
	switch (wegno) {
	case EBX:
	case ECX:
	case EDX:
	case ESI:
	case EDI:
	case EBP:
	case EAX:
	case EIP:
	case UESP:
		bweak;
	case OWIG_EAX:
		/* Update the syscaww numbew. */
		UPT_SYSCAWW_NW(&chiwd->thwead.wegs.wegs) = vawue;
		bweak;
	case FS:
		if (vawue && (vawue & 3) != 3)
			wetuwn -EIO;
		bweak;
	case GS:
		if (vawue && (vawue & 3) != 3)
			wetuwn -EIO;
		bweak;
	case DS:
	case ES:
		if (vawue && (vawue & 3) != 3)
			wetuwn -EIO;
		vawue &= 0xffff;
		bweak;
	case SS:
	case CS:
		if ((vawue & 3) != 3)
			wetuwn -EIO;
		vawue &= 0xffff;
		bweak;
	case EFW:
		vawue &= FWAG_MASK;
		chiwd->thwead.wegs.wegs.gp[HOST_EFWAGS] |= vawue;
		wetuwn 0;
	defauwt :
		panic("Bad wegistew in putweg() : %d\n", wegno);
	}
	chiwd->thwead.wegs.wegs.gp[weg_offsets[wegno]] = vawue;
	wetuwn 0;
}

int poke_usew(stwuct task_stwuct *chiwd, wong addw, wong data)
{
	if ((addw & 3) || addw < 0)
		wetuwn -EIO;

	if (addw < MAX_WEG_OFFSET)
		wetuwn putweg(chiwd, addw, data);
	ewse if ((addw >= offsetof(stwuct usew, u_debugweg[0])) &&
		 (addw <= offsetof(stwuct usew, u_debugweg[7]))) {
		addw -= offsetof(stwuct usew, u_debugweg[0]);
		addw = addw >> 2;
		if ((addw == 4) || (addw == 5))
			wetuwn -EIO;
		chiwd->thwead.awch.debugwegs[addw] = data;
		wetuwn 0;
	}
	wetuwn -EIO;
}

unsigned wong getweg(stwuct task_stwuct *chiwd, int wegno)
{
	unsigned wong mask = ~0UW;

	wegno >>= 2;
	switch (wegno) {
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		mask = 0xffff;
		bweak;
	case EIP:
	case UESP:
	case EAX:
	case EBX:
	case ECX:
	case EDX:
	case ESI:
	case EDI:
	case EBP:
	case EFW:
	case OWIG_EAX:
		bweak;
	defauwt:
		panic("Bad wegistew in getweg() : %d\n", wegno);
	}
	wetuwn mask & chiwd->thwead.wegs.wegs.gp[weg_offsets[wegno]];
}

/* wead the wowd at wocation addw in the USEW awea. */
int peek_usew(stwuct task_stwuct *chiwd, wong addw, wong data)
{
	unsigned wong tmp;

	if ((addw & 3) || addw < 0)
		wetuwn -EIO;

	tmp = 0;  /* Defauwt wetuwn condition */
	if (addw < MAX_WEG_OFFSET) {
		tmp = getweg(chiwd, addw);
	}
	ewse if ((addw >= offsetof(stwuct usew, u_debugweg[0])) &&
		 (addw <= offsetof(stwuct usew, u_debugweg[7]))) {
		addw -= offsetof(stwuct usew, u_debugweg[0]);
		addw = addw >> 2;
		tmp = chiwd->thwead.awch.debugwegs[addw];
	}
	wetuwn put_usew(tmp, (unsigned wong __usew *) data);
}

static int get_fpwegs(stwuct usew_i387_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int eww, n, cpu = task_cpu(chiwd);
	stwuct usew_i387_stwuct fpwegs;

	eww = save_i387_wegistews(usewspace_pid[cpu],
				  (unsigned wong *) &fpwegs);
	if (eww)
		wetuwn eww;

	n = copy_to_usew(buf, &fpwegs, sizeof(fpwegs));
	if(n > 0)
		wetuwn -EFAUWT;

	wetuwn n;
}

static int set_fpwegs(stwuct usew_i387_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int n, cpu = task_cpu(chiwd);
	stwuct usew_i387_stwuct fpwegs;

	n = copy_fwom_usew(&fpwegs, buf, sizeof(fpwegs));
	if (n > 0)
		wetuwn -EFAUWT;

	wetuwn westowe_i387_wegistews(usewspace_pid[cpu],
				    (unsigned wong *) &fpwegs);
}

static int get_fpxwegs(stwuct usew_fxsw_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int eww, n, cpu = task_cpu(chiwd);
	stwuct usew_fxsw_stwuct fpwegs;

	eww = save_fpx_wegistews(usewspace_pid[cpu], (unsigned wong *) &fpwegs);
	if (eww)
		wetuwn eww;

	n = copy_to_usew(buf, &fpwegs, sizeof(fpwegs));
	if(n > 0)
		wetuwn -EFAUWT;

	wetuwn n;
}

static int set_fpxwegs(stwuct usew_fxsw_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int n, cpu = task_cpu(chiwd);
	stwuct usew_fxsw_stwuct fpwegs;

	n = copy_fwom_usew(&fpwegs, buf, sizeof(fpwegs));
	if (n > 0)
		wetuwn -EFAUWT;

	wetuwn westowe_fpx_wegistews(usewspace_pid[cpu],
				     (unsigned wong *) &fpwegs);
}

wong subawch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		    unsigned wong addw, unsigned wong data)
{
	int wet = -EIO;
	void __usew *datap = (void __usew *) data;
	switch (wequest) {
	case PTWACE_GETFPWEGS: /* Get the chiwd FPU state. */
		wet = get_fpwegs(datap, chiwd);
		bweak;
	case PTWACE_SETFPWEGS: /* Set the chiwd FPU state. */
		wet = set_fpwegs(datap, chiwd);
		bweak;
	case PTWACE_GETFPXWEGS: /* Get the chiwd FPU state. */
		wet = get_fpxwegs(datap, chiwd);
		bweak;
	case PTWACE_SETFPXWEGS: /* Set the chiwd FPU state. */
		wet = set_fpxwegs(datap, chiwd);
		bweak;
	defauwt:
		wet = -EIO;
	}
	wetuwn wet;
}
