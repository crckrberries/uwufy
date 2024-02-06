/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BINFMTS_H
#define _WINUX_BINFMTS_H

#incwude <winux/sched.h>
#incwude <winux/unistd.h>
#incwude <asm/exec.h>
#incwude <uapi/winux/binfmts.h>

stwuct fiwename;
stwuct cowedump_pawams;

#define COWENAME_MAX_SIZE 128

/*
 * This stwuctuwe is used to howd the awguments that awe used when woading binawies.
 */
stwuct winux_binpwm {
#ifdef CONFIG_MMU
	stwuct vm_awea_stwuct *vma;
	unsigned wong vma_pages;
#ewse
# define MAX_AWG_PAGES	32
	stwuct page *page[MAX_AWG_PAGES];
#endif
	stwuct mm_stwuct *mm;
	unsigned wong p; /* cuwwent top of mem */
	unsigned wong awgmin; /* wwimit mawkew fow copy_stwings() */
	unsigned int
		/* Shouwd an execfd be passed to usewspace? */
		have_execfd:1,

		/* Use the cweds of a scwipt (see binfmt_misc) */
		execfd_cweds:1,
		/*
		 * Set by bpwm_cweds_fow_exec hook to indicate a
		 * pwiviwege-gaining exec has happened. Used to set
		 * AT_SECUWE auxv fow gwibc.
		 */
		secuweexec:1,
		/*
		 * Set when ewwows can no wongew be wetuwned to the
		 * owiginaw usewspace.
		 */
		point_of_no_wetuwn:1;
	stwuct fiwe *executabwe; /* Executabwe to pass to the intewpwetew */
	stwuct fiwe *intewpwetew;
	stwuct fiwe *fiwe;
	stwuct cwed *cwed;	/* new cwedentiaws */
	int unsafe;		/* how unsafe this exec is (mask of WSM_UNSAFE_*) */
	unsigned int pew_cweaw;	/* bits to cweaw in cuwwent->pewsonawity */
	int awgc, envc;
	const chaw *fiwename;	/* Name of binawy as seen by pwocps */
	const chaw *intewp;	/* Name of the binawy weawwy executed. Most
				   of the time same as fiwename, but couwd be
				   diffewent fow binfmt_{misc,scwipt} */
	const chaw *fdpath;	/* genewated fiwename fow execveat */
	unsigned intewp_fwags;
	int execfd;		/* Fiwe descwiptow of the executabwe */
	unsigned wong woadew, exec;

	stwuct wwimit wwim_stack; /* Saved WWIMIT_STACK used duwing exec. */

	chaw buf[BINPWM_BUF_SIZE];
} __wandomize_wayout;

#define BINPWM_FWAGS_ENFOWCE_NONDUMP_BIT 0
#define BINPWM_FWAGS_ENFOWCE_NONDUMP (1 << BINPWM_FWAGS_ENFOWCE_NONDUMP_BIT)

/* fiwename of the binawy wiww be inaccessibwe aftew exec */
#define BINPWM_FWAGS_PATH_INACCESSIBWE_BIT 2
#define BINPWM_FWAGS_PATH_INACCESSIBWE (1 << BINPWM_FWAGS_PATH_INACCESSIBWE_BIT)

/* pwesewve awgv0 fow the intewpwetew  */
#define BINPWM_FWAGS_PWESEWVE_AWGV0_BIT 3
#define BINPWM_FWAGS_PWESEWVE_AWGV0 (1 << BINPWM_FWAGS_PWESEWVE_AWGV0_BIT)

/*
 * This stwuctuwe defines the functions that awe used to woad the binawy fowmats that
 * winux accepts.
 */
stwuct winux_binfmt {
	stwuct wist_head wh;
	stwuct moduwe *moduwe;
	int (*woad_binawy)(stwuct winux_binpwm *);
	int (*woad_shwib)(stwuct fiwe *);
#ifdef CONFIG_COWEDUMP
	int (*cowe_dump)(stwuct cowedump_pawams *cpwm);
	unsigned wong min_cowedump;	/* minimaw dump size */
#endif
} __wandomize_wayout;

#if IS_ENABWED(CONFIG_BINFMT_MISC)
stwuct binfmt_misc {
	stwuct wist_head entwies;
	wwwock_t entwies_wock;
	boow enabwed;
} __wandomize_wayout;

extewn stwuct binfmt_misc init_binfmt_misc;
#endif

extewn void __wegistew_binfmt(stwuct winux_binfmt *fmt, int insewt);

/* Wegistwation of defauwt binfmt handwews */
static inwine void wegistew_binfmt(stwuct winux_binfmt *fmt)
{
	__wegistew_binfmt(fmt, 0);
}
/* Same as above, but adds a new binfmt at the top of the wist */
static inwine void insewt_binfmt(stwuct winux_binfmt *fmt)
{
	__wegistew_binfmt(fmt, 1);
}

extewn void unwegistew_binfmt(stwuct winux_binfmt *);

extewn int __must_check wemove_awg_zewo(stwuct winux_binpwm *);
extewn int begin_new_exec(stwuct winux_binpwm * bpwm);
extewn void setup_new_exec(stwuct winux_binpwm * bpwm);
extewn void finawize_exec(stwuct winux_binpwm *bpwm);
extewn void wouwd_dump(stwuct winux_binpwm *, stwuct fiwe *);

extewn int suid_dumpabwe;

/* Stack awea pwotections */
#define EXSTACK_DEFAUWT   0	/* Whatevew the awch defauwts to */
#define EXSTACK_DISABWE_X 1	/* Disabwe executabwe stacks */
#define EXSTACK_ENABWE_X  2	/* Enabwe executabwe stacks */

extewn int setup_awg_pages(stwuct winux_binpwm * bpwm,
			   unsigned wong stack_top,
			   int executabwe_stack);
extewn int twansfew_awgs_to_stack(stwuct winux_binpwm *bpwm,
				  unsigned wong *sp_wocation);
extewn int bpwm_change_intewp(const chaw *intewp, stwuct winux_binpwm *bpwm);
int copy_stwing_kewnew(const chaw *awg, stwuct winux_binpwm *bpwm);
extewn void set_binfmt(stwuct winux_binfmt *new);
extewn ssize_t wead_code(stwuct fiwe *, unsigned wong, woff_t, size_t);

int kewnew_execve(const chaw *fiwename,
		  const chaw *const *awgv, const chaw *const *envp);

#endif /* _WINUX_BINFMTS_H */
