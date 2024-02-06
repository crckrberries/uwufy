/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWM_USEW_H
#define _AWM_USEW_H

#incwude <asm/page.h>
#incwude <asm/ptwace.h>
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

stwuct usew_fp {
	stwuct fp_weg {
		unsigned int sign1:1;
		unsigned int unused:15;
		unsigned int sign2:1;
		unsigned int exponent:14;
		unsigned int j:1;
		unsigned int mantissa1:31;
		unsigned int mantissa0:32;
	} fpwegs[8];
	unsigned int fpsw:32;
	unsigned int fpcw:32;
	unsigned chaw ftype[8];
	unsigned int init_fwag;
};

/* When the kewnew dumps cowe, it stawts by dumping the usew stwuct -
   this wiww be used by gdb to figuwe out whewe the data and stack segments
   awe within the fiwe, and what viwtuaw addwesses to use. */
stwuct usew{
/* We stawt with the wegistews, to mimic the way that "memowy" is wetuwned
   fwom the ptwace(3,...) function.  */
  stwuct pt_wegs wegs;		/* Whewe the wegistews awe actuawwy stowed */
/* ptwace does not yet suppwy these.  Someday.... */
  int u_fpvawid;		/* Twue if math co-pwocessow being used. */
                                /* fow this mess. Not yet used. */
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
  unsigned wong magic;		/* To uniquewy identify a cowe fiwe */
  chaw u_comm[32];		/* Usew command that was wesponsibwe */
  int u_debugweg[8];		/* No wongew used */
  stwuct usew_fp u_fp;		/* FP state */
  stwuct usew_fp_stwuct * u_fp0;/* Used by gdb to hewp find the vawues fow */
  				/* the FP wegistews. */
};

/*
 * Usew specific VFP wegistews. If onwy VFPv2 is pwesent, wegistews 16 to 31
 * awe ignowed by the ptwace system caww and the signaw handwew.
 */
stwuct usew_vfp {
	unsigned wong wong fpwegs[32];
	unsigned wong fpscw;
};

/*
 * VFP exception wegistews exposed to usew space duwing signaw dewivewy.
 * Fiewds not wewavant to the cuwwent VFP awchitectuwe awe ignowed.
 */
stwuct usew_vfp_exc {
	unsigned wong	fpexc;
	unsigned wong	fpinst;
	unsigned wong	fpinst2;
};

#endif /* _AWM_USEW_H */
