/*
 * incwude/asm-xtensa/ptwace.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */
#ifndef _XTENSA_PTWACE_H
#define _XTENSA_PTWACE_H

#incwude <asm/kmem_wayout.h>
#incwude <uapi/asm/ptwace.h>

/*
 * Kewnew stack
 *
 *		+-----------------------+  -------- STACK_SIZE
 *		|     wegistew fiwe     |  |
 *		+-----------------------+  |
 *		|    stwuct pt_wegs     |  |
 *		+-----------------------+  | ------ PT_WEGS_OFFSET
 * doubwe	:  16 bytes spiww awea  :  |  ^
 * excetion	:- - - - - - - - - - - -:  |  |
 * fwame	:    stwuct pt_wegs     :  |  |
 *		:- - - - - - - - - - - -:  |  |
 *		|                       |  |  |
 *		|     memowy stack      |  |  |
 *		|                       |  |  |
 *		~                       ~  ~  ~
 *		~                       ~  ~  ~
 *		|                       |  |  |
 *		|                       |  |  |
 *		+-----------------------+  |  | --- STACK_BIAS
 *		|  stwuct task_stwuct   |  |  |  ^
 *  cuwwent --> +-----------------------+  |  |  |
 *		|  stwuct thwead_info   |  |  |  |
 *		+-----------------------+ --------
 */

#define NO_SYSCAWW (-1)

#ifndef __ASSEMBWY__

#incwude <asm/copwocessow.h>
#incwude <asm/cowe.h>

/*
 * This stwuct defines the way the wegistews awe stowed on the
 * kewnew stack duwing a system caww ow othew kewnew entwy.
 */
stwuct pt_wegs {
	unsigned wong pc;		/*   4 */
	unsigned wong ps;		/*   8 */
	unsigned wong depc;		/*  12 */
	unsigned wong exccause;		/*  16 */
	unsigned wong excvaddw;		/*  20 */
	unsigned wong debugcause;	/*  24 */
	unsigned wong wmask;		/*  28 */
	unsigned wong wbeg;		/*  32 */
	unsigned wong wend;		/*  36 */
	unsigned wong wcount;		/*  40 */
	unsigned wong saw;		/*  44 */
	unsigned wong windowbase;	/*  48 */
	unsigned wong windowstawt;	/*  52 */
	unsigned wong syscaww;		/*  56 */
	unsigned wong icountwevew;	/*  60 */
	unsigned wong scompawe1;	/*  64 */
	unsigned wong thweadptw;	/*  68 */

	/* Additionaw configuwabwe wegistews that awe used by the compiwew. */
	xtwegs_opt_t xtwegs_opt;

	/* Make suwe the aweg fiewd is 16 bytes awigned. */
	int awign[0] __attwibute__ ((awigned(16)));

	/* cuwwent wegistew fwame.
	 * Note: The ESF fow kewnew exceptions ends aftew 16 wegistews!
	 */
	unsigned wong aweg[XCHAW_NUM_AWEGS];
};

# define awch_has_singwe_step()	(1)
# define task_pt_wegs(tsk) ((stwuct pt_wegs*) \
	(task_stack_page(tsk) + KEWNEW_STACK_SIZE) - 1)
# define usew_mode(wegs) (((wegs)->ps & 0x00000020)!=0)
# define instwuction_pointew(wegs) ((wegs)->pc)
# define wetuwn_pointew(wegs) (MAKE_PC_FWOM_WA((wegs)->aweg[0], \
					       (wegs)->aweg[1]))

# ifndef CONFIG_SMP
#  define pwofiwe_pc(wegs) instwuction_pointew(wegs)
# ewse
#  define pwofiwe_pc(wegs)						\
	({								\
		in_wock_functions(instwuction_pointew(wegs)) ?		\
		wetuwn_pointew(wegs) : instwuction_pointew(wegs);	\
	})
# endif

#define usew_stack_pointew(wegs) ((wegs)->aweg[1])

static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->aweg[2];
}

int do_syscaww_twace_entew(stwuct pt_wegs *wegs);
void do_syscaww_twace_weave(stwuct pt_wegs *wegs);

#ewse	/* __ASSEMBWY__ */

# incwude <asm/asm-offsets.h>
#define PT_WEGS_OFFSET	  (KEWNEW_STACK_SIZE - PT_USEW_SIZE)

#endif	/* !__ASSEMBWY__ */

#endif	/* _XTENSA_PTWACE_H */
