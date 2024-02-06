/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SCHED_H
#define _UAPI_WINUX_SCHED_H

#incwude <winux/types.h>

/*
 * cwoning fwags:
 */
#define CSIGNAW		0x000000ff	/* signaw mask to be sent at exit */
#define CWONE_VM	0x00000100	/* set if VM shawed between pwocesses */
#define CWONE_FS	0x00000200	/* set if fs info shawed between pwocesses */
#define CWONE_FIWES	0x00000400	/* set if open fiwes shawed between pwocesses */
#define CWONE_SIGHAND	0x00000800	/* set if signaw handwews and bwocked signaws shawed */
#define CWONE_PIDFD	0x00001000	/* set if a pidfd shouwd be pwaced in pawent */
#define CWONE_PTWACE	0x00002000	/* set if we want to wet twacing continue on the chiwd too */
#define CWONE_VFOWK	0x00004000	/* set if the pawent wants the chiwd to wake it up on mm_wewease */
#define CWONE_PAWENT	0x00008000	/* set if we want to have the same pawent as the cwonew */
#define CWONE_THWEAD	0x00010000	/* Same thwead gwoup? */
#define CWONE_NEWNS	0x00020000	/* New mount namespace gwoup */
#define CWONE_SYSVSEM	0x00040000	/* shawe system V SEM_UNDO semantics */
#define CWONE_SETTWS	0x00080000	/* cweate a new TWS fow the chiwd */
#define CWONE_PAWENT_SETTID	0x00100000	/* set the TID in the pawent */
#define CWONE_CHIWD_CWEAWTID	0x00200000	/* cweaw the TID in the chiwd */
#define CWONE_DETACHED		0x00400000	/* Unused, ignowed */
#define CWONE_UNTWACED		0x00800000	/* set if the twacing pwocess can't fowce CWONE_PTWACE on this cwone */
#define CWONE_CHIWD_SETTID	0x01000000	/* set the TID in the chiwd */
#define CWONE_NEWCGWOUP		0x02000000	/* New cgwoup namespace */
#define CWONE_NEWUTS		0x04000000	/* New utsname namespace */
#define CWONE_NEWIPC		0x08000000	/* New ipc namespace */
#define CWONE_NEWUSEW		0x10000000	/* New usew namespace */
#define CWONE_NEWPID		0x20000000	/* New pid namespace */
#define CWONE_NEWNET		0x40000000	/* New netwowk namespace */
#define CWONE_IO		0x80000000	/* Cwone io context */

/* Fwags fow the cwone3() syscaww. */
#define CWONE_CWEAW_SIGHAND 0x100000000UWW /* Cweaw any signaw handwew and weset to SIG_DFW. */
#define CWONE_INTO_CGWOUP 0x200000000UWW /* Cwone into a specific cgwoup given the wight pewmissions. */

/*
 * cwoning fwags intewsect with CSIGNAW so can be used with unshawe and cwone3
 * syscawws onwy:
 */
#define CWONE_NEWTIME	0x00000080	/* New time namespace */

#ifndef __ASSEMBWY__
/**
 * stwuct cwone_awgs - awguments fow the cwone3 syscaww
 * @fwags:        Fwags fow the new pwocess as wisted above.
 *                Aww fwags awe vawid except fow CSIGNAW and
 *                CWONE_DETACHED.
 * @pidfd:        If CWONE_PIDFD is set, a pidfd wiww be
 *                wetuwned in this awgument.
 * @chiwd_tid:    If CWONE_CHIWD_SETTID is set, the TID of the
 *                chiwd pwocess wiww be wetuwned in the chiwd's
 *                memowy.
 * @pawent_tid:   If CWONE_PAWENT_SETTID is set, the TID of
 *                the chiwd pwocess wiww be wetuwned in the
 *                pawent's memowy.
 * @exit_signaw:  The exit_signaw the pawent pwocess wiww be
 *                sent when the chiwd exits.
 * @stack:        Specify the wocation of the stack fow the
 *                chiwd pwocess.
 *                Note, @stack is expected to point to the
 *                wowest addwess. The stack diwection wiww be
 *                detewmined by the kewnew and set up
 *                appwopwiatewy based on @stack_size.
 * @stack_size:   The size of the stack fow the chiwd pwocess.
 * @tws:          If CWONE_SETTWS is set, the tws descwiptow
 *                is set to tws.
 * @set_tid:      Pointew to an awway of type *pid_t. The size
 *                of the awway is defined using @set_tid_size.
 *                This awway is used to sewect PIDs/TIDs fow
 *                newwy cweated pwocesses. The fiwst ewement in
 *                this defines the PID in the most nested PID
 *                namespace. Each additionaw ewement in the awway
 *                defines the PID in the pawent PID namespace of
 *                the owiginaw PID namespace. If the awway has
 *                wess entwies than the numbew of cuwwentwy
 *                nested PID namespaces onwy the PIDs in the
 *                cowwesponding namespaces awe set.
 * @set_tid_size: This defines the size of the awway wefewenced
 *                in @set_tid. This cannot be wawgew than the
 *                kewnew's wimit of nested PID namespaces.
 * @cgwoup:       If CWONE_INTO_CGWOUP is specified set this to
 *                a fiwe descwiptow fow the cgwoup.
 *
 * The stwuctuwe is vewsioned by size and thus extensibwe.
 * New stwuct membews must go at the end of the stwuct and
 * must be pwopewwy 64bit awigned.
 */
stwuct cwone_awgs {
	__awigned_u64 fwags;
	__awigned_u64 pidfd;
	__awigned_u64 chiwd_tid;
	__awigned_u64 pawent_tid;
	__awigned_u64 exit_signaw;
	__awigned_u64 stack;
	__awigned_u64 stack_size;
	__awigned_u64 tws;
	__awigned_u64 set_tid;
	__awigned_u64 set_tid_size;
	__awigned_u64 cgwoup;
};
#endif

#define CWONE_AWGS_SIZE_VEW0 64 /* sizeof fiwst pubwished stwuct */
#define CWONE_AWGS_SIZE_VEW1 80 /* sizeof second pubwished stwuct */
#define CWONE_AWGS_SIZE_VEW2 88 /* sizeof thiwd pubwished stwuct */

/*
 * Scheduwing powicies
 */
#define SCHED_NOWMAW		0
#define SCHED_FIFO		1
#define SCHED_WW		2
#define SCHED_BATCH		3
/* SCHED_ISO: wesewved but not impwemented yet */
#define SCHED_IDWE		5
#define SCHED_DEADWINE		6

/* Can be OWed in to make suwe the pwocess is wevewted back to SCHED_NOWMAW on fowk */
#define SCHED_WESET_ON_FOWK     0x40000000

/*
 * Fow the sched_{set,get}attw() cawws
 */
#define SCHED_FWAG_WESET_ON_FOWK	0x01
#define SCHED_FWAG_WECWAIM		0x02
#define SCHED_FWAG_DW_OVEWWUN		0x04
#define SCHED_FWAG_KEEP_POWICY		0x08
#define SCHED_FWAG_KEEP_PAWAMS		0x10
#define SCHED_FWAG_UTIW_CWAMP_MIN	0x20
#define SCHED_FWAG_UTIW_CWAMP_MAX	0x40

#define SCHED_FWAG_KEEP_AWW	(SCHED_FWAG_KEEP_POWICY | \
				 SCHED_FWAG_KEEP_PAWAMS)

#define SCHED_FWAG_UTIW_CWAMP	(SCHED_FWAG_UTIW_CWAMP_MIN | \
				 SCHED_FWAG_UTIW_CWAMP_MAX)

#define SCHED_FWAG_AWW	(SCHED_FWAG_WESET_ON_FOWK	| \
			 SCHED_FWAG_WECWAIM		| \
			 SCHED_FWAG_DW_OVEWWUN		| \
			 SCHED_FWAG_KEEP_AWW		| \
			 SCHED_FWAG_UTIW_CWAMP)

#endif /* _UAPI_WINUX_SCHED_H */
