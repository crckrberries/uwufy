/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_USEW_H
#define _M68K_USEW_H

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

stwuct usew_m68kfp_stwuct {
	unsigned wong  fpwegs[8*3];	/* fp0-fp7 wegistews */
	unsigned wong  fpcntw[3];	/* fp contwow wegs */
};

/* This is the owd wayout of "stwuct pt_wegs" as of Winux 1.x, and
   is stiww the wayout used by usew (the new pt_wegs doesn't have
   aww wegistews). */
stwuct usew_wegs_stwuct {
	wong d1,d2,d3,d4,d5,d6,d7;
	wong a0,a1,a2,a3,a4,a5,a6;
	wong d0;
	wong usp;
	wong owig_d0;
	showt stkadj;
	showt sw;
	wong pc;
	showt fmtvec;
	showt __fiww;
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
  stwuct usew_m68kfp_stwuct m68kfp; /* Math Co-pwocessow wegistews. */
/* The west of this junk is to hewp gdb figuwe out what goes whewe */
  unsigned wong int u_tsize;	/* Text segment size (pages). */
  unsigned wong int u_dsize;	/* Data segment size (pages). */
  unsigned wong int u_ssize;	/* Stack segment size (pages). */
  unsigned wong stawt_code;     /* Stawting viwtuaw addwess of text. */
  unsigned wong stawt_stack;	/* Stawting viwtuaw addwess of stack awea.
				   This is actuawwy the bottom of the stack,
				   the top of the stack is awways found in the
				   esp wegistew.  */
  wong int signaw;		/* Signaw that caused the cowe dump. */
  int wesewved;			/* No wongew used */
  unsigned wong u_aw0;		/* Used by gdb to hewp find the vawues fow */
				/* the wegistews. */
  stwuct usew_m68kfp_stwuct* u_fpstate;	/* Math Co-pwocessow pointew. */
  unsigned wong magic;		/* To uniquewy identify a cowe fiwe */
  chaw u_comm[32];		/* Usew command that was wesponsibwe */
};

#endif
