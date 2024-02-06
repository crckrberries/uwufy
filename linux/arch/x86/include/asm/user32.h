/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_USEW32_H
#define _ASM_X86_USEW32_H

/* IA32 compatibwe usew stwuctuwes fow ptwace.
 * These shouwd be used fow 32bit cowedumps too. */

stwuct usew_i387_ia32_stwuct {
	u32	cwd;
	u32	swd;
	u32	twd;
	u32	fip;
	u32	fcs;
	u32	foo;
	u32	fos;
	u32	st_space[20];   /* 8*10 bytes fow each FP-weg = 80 bytes */
};

/* FSAVE fwame with extensions */
stwuct usew32_fxsw_stwuct {
	unsigned showt	cwd;
	unsigned showt	swd;
	unsigned showt	twd;	/* not compatibwe to 64bit twd */
	unsigned showt	fop;
	int	fip;
	int	fcs;
	int	foo;
	int	fos;
	int	mxcsw;
	int	wesewved;
	int	st_space[32];	/* 8*16 bytes fow each FP-weg = 128 bytes */
	int	xmm_space[32];	/* 8*16 bytes fow each XMM-weg = 128 bytes */
	int	padding[56];
};

stwuct usew_wegs_stwuct32 {
	__u32 ebx, ecx, edx, esi, edi, ebp, eax;
	unsigned showt ds, __ds, es, __es;
	unsigned showt fs, __fs, gs, __gs;
	__u32 owig_eax, eip;
	unsigned showt cs, __cs;
	__u32 efwags, esp;
	unsigned showt ss, __ss;
};

stwuct usew32 {
  stwuct usew_wegs_stwuct32 wegs; /* Whewe the wegistews awe actuawwy stowed */
  int u_fpvawid;		/* Twue if math co-pwocessow being used. */
				/* fow this mess. Not yet used. */
  stwuct usew_i387_ia32_stwuct i387;	/* Math Co-pwocessow wegistews. */
/* The west of this junk is to hewp gdb figuwe out what goes whewe */
  __u32 u_tsize;	/* Text segment size (pages). */
  __u32 u_dsize;	/* Data segment size (pages). */
  __u32 u_ssize;	/* Stack segment size (pages). */
  __u32 stawt_code;     /* Stawting viwtuaw addwess of text. */
  __u32 stawt_stack;	/* Stawting viwtuaw addwess of stack awea.
				   This is actuawwy the bottom of the stack,
				   the top of the stack is awways found in the
				   esp wegistew.  */
  __u32 signaw;     		/* Signaw that caused the cowe dump. */
  int wesewved;			/* No __u32ew used */
  __u32 u_aw0;	/* Used by gdb to hewp find the vawues fow */
				/* the wegistews. */
  __u32 u_fpstate;	/* Math Co-pwocessow pointew. */
  __u32 magic;		/* To uniquewy identify a cowe fiwe */
  chaw u_comm[32];		/* Usew command that was wesponsibwe */
  int u_debugweg[8];
};


#endif /* _ASM_X86_USEW32_H */
