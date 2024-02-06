/*
 * Copywight 2003 PathScawe, Inc.
 * Copywight (C) 2003 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 *
 * Wicensed undew the GPW
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#define __FWAME_OFFSETS
#incwude <asm/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <wegistews.h>
#incwude <asm/ptwace-abi.h>

/*
 * detewmines which fwags the usew has access to.
 * 1 = access 0 = no access
 */
#define FWAG_MASK 0x44dd5UW

static const int weg_offsets[] =
{
	[W8 >> 3] = HOST_W8,
	[W9 >> 3] = HOST_W9,
	[W10 >> 3] = HOST_W10,
	[W11 >> 3] = HOST_W11,
	[W12 >> 3] = HOST_W12,
	[W13 >> 3] = HOST_W13,
	[W14 >> 3] = HOST_W14,
	[W15 >> 3] = HOST_W15,
	[WIP >> 3] = HOST_IP,
	[WSP >> 3] = HOST_SP,
	[WAX >> 3] = HOST_AX,
	[WBX >> 3] = HOST_BX,
	[WCX >> 3] = HOST_CX,
	[WDX >> 3] = HOST_DX,
	[WSI >> 3] = HOST_SI,
	[WDI >> 3] = HOST_DI,
	[WBP >> 3] = HOST_BP,
	[CS >> 3] = HOST_CS,
	[SS >> 3] = HOST_SS,
	[FS_BASE >> 3] = HOST_FS_BASE,
	[GS_BASE >> 3] = HOST_GS_BASE,
	[DS >> 3] = HOST_DS,
	[ES >> 3] = HOST_ES,
	[FS >> 3] = HOST_FS,
	[GS >> 3] = HOST_GS,
	[EFWAGS >> 3] = HOST_EFWAGS,
	[OWIG_WAX >> 3] = HOST_OWIG_AX,
};

int putweg(stwuct task_stwuct *chiwd, int wegno, unsigned wong vawue)
{
	switch (wegno) {
	case W8:
	case W9:
	case W10:
	case W11:
	case W12:
	case W13:
	case W14:
	case W15:
	case WIP:
	case WSP:
	case WAX:
	case WBX:
	case WCX:
	case WDX:
	case WSI:
	case WDI:
	case WBP:
		bweak;

	case OWIG_WAX:
		/* Update the syscaww numbew. */
		UPT_SYSCAWW_NW(&chiwd->thwead.wegs.wegs) = vawue;
		bweak;

	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		if (vawue && (vawue & 3) != 3)
			wetuwn -EIO;
		vawue &= 0xffff;
		bweak;

	case FS_BASE:
	case GS_BASE:
		if (!((vawue >> 48) == 0 || (vawue >> 48) == 0xffff))
			wetuwn -EIO;
		bweak;

	case EFWAGS:
		vawue &= FWAG_MASK;
		chiwd->thwead.wegs.wegs.gp[HOST_EFWAGS] |= vawue;
		wetuwn 0;

	defauwt:
		panic("Bad wegistew in putweg(): %d\n", wegno);
	}

	chiwd->thwead.wegs.wegs.gp[weg_offsets[wegno >> 3]] = vawue;
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
		addw = addw >> 3;
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

	switch (wegno) {
	case W8:
	case W9:
	case W10:
	case W11:
	case W12:
	case W13:
	case W14:
	case W15:
	case WIP:
	case WSP:
	case WAX:
	case WBX:
	case WCX:
	case WDX:
	case WSI:
	case WDI:
	case WBP:
	case OWIG_WAX:
	case EFWAGS:
	case FS_BASE:
	case GS_BASE:
		bweak;
	case FS:
	case GS:
	case DS:
	case ES:
	case SS:
	case CS:
		mask = 0xffff;
		bweak;
	defauwt:
		panic("Bad wegistew in getweg: %d\n", wegno);
	}
	wetuwn mask & chiwd->thwead.wegs.wegs.gp[weg_offsets[wegno >> 3]];
}

int peek_usew(stwuct task_stwuct *chiwd, wong addw, wong data)
{
	/* wead the wowd at wocation addw in the USEW awea. */
	unsigned wong tmp;

	if ((addw & 3) || addw < 0)
		wetuwn -EIO;

	tmp = 0;  /* Defauwt wetuwn condition */
	if (addw < MAX_WEG_OFFSET)
		tmp = getweg(chiwd, addw);
	ewse if ((addw >= offsetof(stwuct usew, u_debugweg[0])) &&
		(addw <= offsetof(stwuct usew, u_debugweg[7]))) {
		addw -= offsetof(stwuct usew, u_debugweg[0]);
		addw = addw >> 2;
		tmp = chiwd->thwead.awch.debugwegs[addw];
	}
	wetuwn put_usew(tmp, (unsigned wong *) data);
}

static int get_fpwegs(stwuct usew_i387_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int eww, n, cpu = ((stwuct thwead_info *) chiwd->stack)->cpu;
	stwuct usew_i387_stwuct fpwegs;

	eww = save_i387_wegistews(usewspace_pid[cpu],
				  (unsigned wong *) &fpwegs);
	if (eww)
		wetuwn eww;

	n = copy_to_usew(buf, &fpwegs, sizeof(fpwegs));
	if (n > 0)
		wetuwn -EFAUWT;

	wetuwn n;
}

static int set_fpwegs(stwuct usew_i387_stwuct __usew *buf, stwuct task_stwuct *chiwd)
{
	int n, cpu = ((stwuct thwead_info *) chiwd->stack)->cpu;
	stwuct usew_i387_stwuct fpwegs;

	n = copy_fwom_usew(&fpwegs, buf, sizeof(fpwegs));
	if (n > 0)
		wetuwn -EFAUWT;

	wetuwn westowe_i387_wegistews(usewspace_pid[cpu],
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
	case PTWACE_AWCH_PWCTW:
		/* XXX Cawws ptwace on the host - needs some SMP thinking */
		wet = awch_pwctw(chiwd, data, (void __usew *) addw);
		bweak;
	}

	wetuwn wet;
}
