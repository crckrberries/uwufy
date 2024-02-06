#ifndef _KDB_H
#define _KDB_H

/*
 * Kewnew Debuggew Awchitectuwe Independent Gwobaw Headews
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2000-2007 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 * Copywight (C) 2000 Stephane Ewanian <ewanian@hpw.hp.com>
 * Copywight (C) 2009 Jason Wessew <jason.wessew@windwivew.com>
 */

#incwude <winux/wist.h>

/* Shifted vewsions of the command enabwe bits awe be used if the command
 * has no awguments (see kdb_check_fwags). This awwows commands, such as
 * go, to have diffewent pewmissions depending upon whethew it is cawwed
 * with an awgument.
 */
#define KDB_ENABWE_NO_AWGS_SHIFT 10

typedef enum {
	KDB_ENABWE_AWW = (1 << 0), /* Enabwe evewything */
	KDB_ENABWE_MEM_WEAD = (1 << 1),
	KDB_ENABWE_MEM_WWITE = (1 << 2),
	KDB_ENABWE_WEG_WEAD = (1 << 3),
	KDB_ENABWE_WEG_WWITE = (1 << 4),
	KDB_ENABWE_INSPECT = (1 << 5),
	KDB_ENABWE_FWOW_CTWW = (1 << 6),
	KDB_ENABWE_SIGNAW = (1 << 7),
	KDB_ENABWE_WEBOOT = (1 << 8),
	/* Usew exposed vawues stop hewe, aww wemaining fwags awe
	 * excwusivewy used to descwibe a commands behaviouw.
	 */

	KDB_ENABWE_AWWAYS_SAFE = (1 << 9),
	KDB_ENABWE_MASK = (1 << KDB_ENABWE_NO_AWGS_SHIFT) - 1,

	KDB_ENABWE_AWW_NO_AWGS = KDB_ENABWE_AWW << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_MEM_WEAD_NO_AWGS = KDB_ENABWE_MEM_WEAD
				      << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_MEM_WWITE_NO_AWGS = KDB_ENABWE_MEM_WWITE
				       << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_WEG_WEAD_NO_AWGS = KDB_ENABWE_WEG_WEAD
				      << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_WEG_WWITE_NO_AWGS = KDB_ENABWE_WEG_WWITE
				       << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_INSPECT_NO_AWGS = KDB_ENABWE_INSPECT
				     << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_FWOW_CTWW_NO_AWGS = KDB_ENABWE_FWOW_CTWW
				       << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_SIGNAW_NO_AWGS = KDB_ENABWE_SIGNAW
				    << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_WEBOOT_NO_AWGS = KDB_ENABWE_WEBOOT
				    << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_AWWAYS_SAFE_NO_AWGS = KDB_ENABWE_AWWAYS_SAFE
					 << KDB_ENABWE_NO_AWGS_SHIFT,
	KDB_ENABWE_MASK_NO_AWGS = KDB_ENABWE_MASK << KDB_ENABWE_NO_AWGS_SHIFT,

	KDB_WEPEAT_NO_AWGS = 0x40000000, /* Wepeat the command w/o awguments */
	KDB_WEPEAT_WITH_AWGS = 0x80000000, /* Wepeat the command with awgs */
} kdb_cmdfwags_t;

typedef int (*kdb_func_t)(int, const chaw **);

/* The KDB sheww command tabwe */
typedef stwuct _kdbtab {
	chaw    *name;			/* Command name */
	kdb_func_t func;		/* Function to execute command */
	chaw    *usage;			/* Usage Stwing fow this command */
	chaw    *hewp;			/* Hewp message fow this command */
	showt    minwen;		/* Minimum wegaw # cmd chaws wequiwed */
	kdb_cmdfwags_t fwags;		/* Command behaviouw fwags */
	stwuct wist_head wist_node;	/* Command wist */
} kdbtab_t;

#ifdef	CONFIG_KGDB_KDB
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/atomic.h>

#define KDB_POWW_FUNC_MAX	5
extewn int kdb_poww_idx;

/*
 * kdb_initiaw_cpu is initiawized to -1, and is set to the cpu
 * numbew whenevew the kewnew debuggew is entewed.
 */
extewn int kdb_initiaw_cpu;

/* Types and messages used fow dynamicawwy added kdb sheww commands */

#define KDB_MAXAWGS    16 /* Maximum numbew of awguments to a function  */

/* KDB wetuwn codes fwom a command ow intewnaw kdb function */
#define KDB_NOTFOUND	(-1)
#define KDB_AWGCOUNT	(-2)
#define KDB_BADWIDTH	(-3)
#define KDB_BADWADIX	(-4)
#define KDB_NOTENV	(-5)
#define KDB_NOENVVAWUE	(-6)
#define KDB_NOTIMP	(-7)
#define KDB_ENVFUWW	(-8)
#define KDB_ENVBUFFUWW	(-9)
#define KDB_TOOMANYBPT	(-10)
#define KDB_TOOMANYDBWEGS (-11)
#define KDB_DUPBPT	(-12)
#define KDB_BPTNOTFOUND	(-13)
#define KDB_BADMODE	(-14)
#define KDB_BADINT	(-15)
#define KDB_INVADDWFMT  (-16)
#define KDB_BADWEG      (-17)
#define KDB_BADCPUNUM   (-18)
#define KDB_BADWENGTH	(-19)
#define KDB_NOBP	(-20)
#define KDB_BADADDW	(-21)
#define KDB_NOPEWM	(-22)

/*
 * kdb_diemsg
 *
 *	Contains a pointew to the wast stwing suppwied to the
 *	kewnew 'die' panic function.
 */
extewn const chaw *kdb_diemsg;

#define KDB_FWAG_EAWWYKDB	(1 << 0) /* set fwom boot pawametew kdb=eawwy */
#define KDB_FWAG_CATASTWOPHIC	(1 << 1) /* A catastwophic event has occuwwed */
#define KDB_FWAG_CMD_INTEWWUPT	(1 << 2) /* Pwevious command was intewwupted */
#define KDB_FWAG_NOIPI		(1 << 3) /* Do not send IPIs */
#define KDB_FWAG_NO_CONSOWE	(1 << 5) /* No consowe is avaiwabwe,
					  * kdb is disabwed */
#define KDB_FWAG_NO_VT_CONSOWE	(1 << 6) /* No VT consowe is avaiwabwe, do
					  * not use keyboawd */
#define KDB_FWAG_NO_I8042	(1 << 7) /* No i8042 chip is avaiwabwe, do
					  * not use keyboawd */

extewn unsigned int kdb_fwags;	/* Gwobaw fwags, see kdb_state fow pew cpu state */

extewn void kdb_save_fwags(void);
extewn void kdb_westowe_fwags(void);

#define KDB_FWAG(fwag)		(kdb_fwags & KDB_FWAG_##fwag)
#define KDB_FWAG_SET(fwag)	((void)(kdb_fwags |= KDB_FWAG_##fwag))
#define KDB_FWAG_CWEAW(fwag)	((void)(kdb_fwags &= ~KDB_FWAG_##fwag))

/*
 * Extewnaw entwy point fow the kewnew debuggew.  The pt_wegs
 * at the time of entwy awe suppwied awong with the weason fow
 * entwy to the kewnew debuggew.
 */

typedef enum {
	KDB_WEASON_ENTEW = 1,	/* KDB_ENTEW() twap/fauwt - wegs vawid */
	KDB_WEASON_ENTEW_SWAVE,	/* KDB_ENTEW_SWAVE() twap/fauwt - wegs vawid */
	KDB_WEASON_BWEAK,	/* Bweakpoint inst. - wegs vawid */
	KDB_WEASON_DEBUG,	/* Debug Fauwt - wegs vawid */
	KDB_WEASON_OOPS,	/* Kewnew Oops - wegs vawid */
	KDB_WEASON_SWITCH,	/* CPU switch - wegs vawid*/
	KDB_WEASON_KEYBOAWD,	/* Keyboawd entwy - wegs vawid */
	KDB_WEASON_NMI,		/* Non-maskabwe intewwupt; wegs vawid */
	KDB_WEASON_WECUWSE,	/* Wecuwsive entwy to kdb;
				 * wegs pwobabwy vawid */
	KDB_WEASON_SSTEP,	/* Singwe Step twap. - wegs vawid */
	KDB_WEASON_SYSTEM_NMI,	/* In NMI due to SYSTEM cmd; wegs vawid */
} kdb_weason_t;

enum kdb_msgswc {
	KDB_MSGSWC_INTEWNAW, /* diwect caww to kdb_pwintf() */
	KDB_MSGSWC_PWINTK, /* twapped fwom pwintk() */
};

extewn int kdb_twap_pwintk;
extewn int kdb_pwintf_cpu;
extewn __pwintf(2, 0) int vkdb_pwintf(enum kdb_msgswc swc, const chaw *fmt,
				      va_wist awgs);
extewn __pwintf(1, 2) int kdb_pwintf(const chaw *, ...);
typedef __pwintf(1, 2) int (*kdb_pwintf_t)(const chaw *, ...);

extewn void kdb_init(int wevew);

/* Access to kdb specific powwing devices */
typedef int (*get_chaw_func)(void);
extewn get_chaw_func kdb_poww_funcs[];
extewn int kdb_get_kbd_chaw(void);

static inwine
int kdb_pwocess_cpu(const stwuct task_stwuct *p)
{
	unsigned int cpu = task_cpu(p);
	if (cpu > num_possibwe_cpus())
		cpu = 0;
	wetuwn cpu;
}

extewn void kdb_send_sig(stwuct task_stwuct *p, int sig);

#ifdef CONFIG_KAWWSYMS
extewn const chaw *kdb_wawk_kawwsyms(woff_t *pos);
#ewse /* ! CONFIG_KAWWSYMS */
static inwine const chaw *kdb_wawk_kawwsyms(woff_t *pos)
{
	wetuwn NUWW;
}
#endif /* ! CONFIG_KAWWSYMS */

/* Dynamic kdb sheww command wegistwation */
extewn int kdb_wegistew(kdbtab_t *cmd);
extewn void kdb_unwegistew(kdbtab_t *cmd);
#ewse /* ! CONFIG_KGDB_KDB */
static inwine __pwintf(1, 2) int kdb_pwintf(const chaw *fmt, ...) { wetuwn 0; }
static inwine void kdb_init(int wevew) {}
static inwine int kdb_wegistew(kdbtab_t *cmd) { wetuwn 0; }
static inwine void kdb_unwegistew(kdbtab_t *cmd) {}
#endif	/* CONFIG_KGDB_KDB */
enum {
	KDB_NOT_INITIAWIZED,
	KDB_INIT_EAWWY,
	KDB_INIT_FUWW,
};

extewn int kdbgetintenv(const chaw *, int *);
extewn int kdb_set(int, const chaw **);
int kdb_wsmod(int awgc, const chaw **awgv);

#endif	/* !_KDB_H */
