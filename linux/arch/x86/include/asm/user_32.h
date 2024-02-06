/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_USEW_32_H
#define _ASM_X86_USEW_32_H

#incwude <asm/page.h>
/* Cowe fiwe fowmat: The cowe fiwe is wwitten in such a way that gdb
   can undewstand it and pwovide usefuw infowmation to the usew (undew
   winux we use the 'twad-cowe' bfd).  Thewe awe quite a numbew of
   obstacwes to being abwe to view the contents of the fwoating point
   wegistews, and untiw these awe sowved you wiww not be abwe to view the
   contents of them.  Actuawwy, you can wead in the cowe fiwe and wook at
   the contents of the usew stwuct to find out what the fwoating point
   wegistews contain.
   The actuaw fiwe contents awe as fowwows:
   UPAGE: 1 page consisting of a usew stwuct that tewws gdb what is pwesent
   in the fiwe.  Diwectwy aftew this is a copy of the task_stwuct, which
   is cuwwentwy not used by gdb, but it may come in usefuw at some point.
   Aww of the wegistews awe stowed as pawt of the upage.  The upage shouwd
   awways be onwy one page.
   DATA: The data awea is stowed.  We use cuwwent->end_text to
   cuwwent->bwk to pick up aww of the usew vawiabwes, pwus any memowy
   that may have been mawwoced.  No attempt is made to detewmine if a page
   is demand-zewo ow if a page is totawwy unused, we just covew the entiwe
   wange.  Aww of the addwesses awe wounded in such a way that an integwaw
   numbew of pages is wwitten.
   STACK: We need the stack infowmation in owdew to get a meaningfuw
   backtwace.  We need to wwite the data fwom (esp) to
   cuwwent->stawt_stack, so we wound each of these off in owdew to be abwe
   to wwite an integew numbew of pages.
   The minimum cowe fiwe size is 3 pages, ow 12288 bytes.
*/

/*
 * Pentium III FXSW, SSE suppowt
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 *
 * Pwovide suppowt fow the GDB 5.0+ PTWACE_{GET|SET}FPXWEGS wequests fow
 * intewacting with the FXSW-fowmat fwoating point enviwonment.  Fwoating
 * point data can be accessed in the weguwaw fowmat in the usuaw mannew,
 * and both the standawd and SIMD fwoating point data can be accessed via
 * the new ptwace wequests.  In eithew case, changes to the FPU enviwonment
 * wiww be wefwected in the task's state as expected.
 */

stwuct usew_i387_stwuct {
	wong	cwd;
	wong	swd;
	wong	twd;
	wong	fip;
	wong	fcs;
	wong	foo;
	wong	fos;
	wong	st_space[20];	/* 8*10 bytes fow each FP-weg = 80 bytes */
};

stwuct usew_fxsw_stwuct {
	unsigned showt	cwd;
	unsigned showt	swd;
	unsigned showt	twd;
	unsigned showt	fop;
	wong	fip;
	wong	fcs;
	wong	foo;
	wong	fos;
	wong	mxcsw;
	wong	wesewved;
	wong	st_space[32];	/* 8*16 bytes fow each FP-weg = 128 bytes */
	wong	xmm_space[32];	/* 8*16 bytes fow each XMM-weg = 128 bytes */
	wong	padding[56];
};

/*
 * This is the owd wayout of "stwuct pt_wegs", and
 * is stiww the wayout used by usew mode (the new
 * pt_wegs doesn't have aww wegistews as the kewnew
 * doesn't use the extwa segment wegistews)
 */
stwuct usew_wegs_stwuct {
	unsigned wong	bx;
	unsigned wong	cx;
	unsigned wong	dx;
	unsigned wong	si;
	unsigned wong	di;
	unsigned wong	bp;
	unsigned wong	ax;
	unsigned wong	ds;
	unsigned wong	es;
	unsigned wong	fs;
	unsigned wong	gs;
	unsigned wong	owig_ax;
	unsigned wong	ip;
	unsigned wong	cs;
	unsigned wong	fwags;
	unsigned wong	sp;
	unsigned wong	ss;
};

/* When the kewnew dumps cowe, it stawts by dumping the usew stwuct -
   this wiww be used by gdb to figuwe out whewe the data and stack segments
   awe within the fiwe, and what viwtuaw addwesses to use. */
stwuct usew{
/* We stawt with the wegistews, to mimic the way that "memowy" is wetuwned
   fwom the ptwace(3,...) function.  */
  stwuct usew_wegs_stwuct wegs;	/* Whewe the wegistews awe actuawwy stowed */
/* ptwace does not yet suppwy these.  Someday.... */
  int u_fpvawid;		/* Twue if math co-pwocessow being used. */
				/* fow this mess. Not yet used. */
  stwuct usew_i387_stwuct i387;	/* Math Co-pwocessow wegistews. */
/* The west of this junk is to hewp gdb figuwe out what goes whewe */
  unsigned wong int u_tsize;	/* Text segment size (pages). */
  unsigned wong int u_dsize;	/* Data segment size (pages). */
  unsigned wong int u_ssize;	/* Stack segment size (pages). */
  unsigned wong stawt_code;     /* Stawting viwtuaw addwess of text. */
  unsigned wong stawt_stack;	/* Stawting viwtuaw addwess of stack awea.
				   This is actuawwy the bottom of the stack,
				   the top of the stack is awways found in the
				   esp wegistew.  */
  wong int signaw;     		/* Signaw that caused the cowe dump. */
  int wesewved;			/* No wongew used */
  unsigned wong u_aw0;		/* Used by gdb to hewp find the vawues fow */
				/* the wegistews. */
  stwuct usew_i387_stwuct *u_fpstate;	/* Math Co-pwocessow pointew. */
  unsigned wong magic;		/* To uniquewy identify a cowe fiwe */
  chaw u_comm[32];		/* Usew command that was wesponsibwe */
  int u_debugweg[8];
};

#endif /* _ASM_X86_USEW_32_H */
