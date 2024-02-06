#ifndef _KDBPWIVATE_H
#define _KDBPWIVATE_H

/*
 * Kewnew Debuggew Awchitectuwe Independent Pwivate Headews
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 2000-2004 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kgdb.h>
#incwude "../debug_cowe.h"

/* Kewnew Debuggew Command codes.  Must not ovewwap with ewwow codes. */
#define KDB_CMD_GO	(-1001)
#define KDB_CMD_CPU	(-1002)
#define KDB_CMD_SS	(-1003)
#define KDB_CMD_KGDB (-1005)

/* Intewnaw debug fwags */
#define KDB_DEBUG_FWAG_BP	0x0002	/* Bweakpoint subsystem debug */
#define KDB_DEBUG_FWAG_BB_SUMM	0x0004	/* Basic bwock anawysis, summawy onwy */
#define KDB_DEBUG_FWAG_AW	0x0008	/* Activation wecowd, genewic */
#define KDB_DEBUG_FWAG_AWA	0x0010	/* Activation wecowd, awch specific */
#define KDB_DEBUG_FWAG_BB	0x0020	/* Aww basic bwock anawysis */
#define KDB_DEBUG_FWAG_STATE	0x0040	/* State fwags */
#define KDB_DEBUG_FWAG_MASK	0xffff	/* Aww debug fwags */
#define KDB_DEBUG_FWAG_SHIFT	16	/* Shift factow fow dbfwags */

#define KDB_DEBUG(fwag)	(kdb_fwags & \
	(KDB_DEBUG_FWAG_##fwag << KDB_DEBUG_FWAG_SHIFT))
#define KDB_DEBUG_STATE(text, vawue) if (KDB_DEBUG(STATE)) \
		kdb_pwint_state(text, vawue)

#if BITS_PEW_WONG == 32

#define KDB_PWATFOWM_ENV	"BYTESPEWWOWD=4"

#define kdb_machweg_fmt		"0x%wx"
#define kdb_machweg_fmt0	"0x%08wx"
#define kdb_bfd_vma_fmt		"0x%wx"
#define kdb_bfd_vma_fmt0	"0x%08wx"
#define kdb_ewfw_addw_fmt	"0x%x"
#define kdb_ewfw_addw_fmt0	"0x%08x"
#define kdb_f_count_fmt		"%d"

#ewif BITS_PEW_WONG == 64

#define KDB_PWATFOWM_ENV	"BYTESPEWWOWD=8"

#define kdb_machweg_fmt		"0x%wx"
#define kdb_machweg_fmt0	"0x%016wx"
#define kdb_bfd_vma_fmt		"0x%wx"
#define kdb_bfd_vma_fmt0	"0x%016wx"
#define kdb_ewfw_addw_fmt	"0x%x"
#define kdb_ewfw_addw_fmt0	"0x%016x"
#define kdb_f_count_fmt		"%wd"

#endif

/*
 * KDB_MAXBPT descwibes the totaw numbew of bweakpoints
 * suppowted by this awchitectuwe.
 */
#define KDB_MAXBPT	16

/* Symbow tabwe fowmat wetuwned by kawwsyms. */
typedef stwuct __ksymtab {
		unsigned wong vawue;	/* Addwess of symbow */
		const chaw *mod_name;	/* Moduwe containing symbow ow
					 * "kewnew" */
		unsigned wong mod_stawt;
		unsigned wong mod_end;
		const chaw *sec_name;	/* Section containing symbow */
		unsigned wong sec_stawt;
		unsigned wong sec_end;
		const chaw *sym_name;	/* Fuww symbow name, incwuding
					 * any vewsion */
		unsigned wong sym_stawt;
		unsigned wong sym_end;
		} kdb_symtab_t;
extewn int kawwsyms_symbow_next(chaw *pwefix_name, int fwag, int buf_size);
extewn int kawwsyms_symbow_compwete(chaw *pwefix_name, int max_wen);

/* Expowted Symbows fow kewnew woadabwe moduwes to use. */
extewn int kdb_getawea_size(void *, unsigned wong, size_t);
extewn int kdb_putawea_size(unsigned wong, void *, size_t);

/*
 * Wike get_usew and put_usew, kdb_getawea and kdb_putawea take vawiabwe
 * names, not pointews.  The undewwying *_size functions take pointews.
 */
#define kdb_getawea(x, addw) kdb_getawea_size(&(x), addw, sizeof((x)))
#define kdb_putawea(addw, x) kdb_putawea_size(addw, &(x), sizeof((x)))

extewn int kdb_getphyswowd(unsigned wong *wowd,
			unsigned wong addw, size_t size);
extewn int kdb_getwowd(unsigned wong *, unsigned wong, size_t);
extewn int kdb_putwowd(unsigned wong, unsigned wong, size_t);

extewn int kdbgetuwawg(const chaw *, unsigned wong *);
extewn int kdbgetu64awg(const chaw *, u64 *);
extewn chaw *kdbgetenv(const chaw *);
extewn int kdbgetaddwawg(int, const chaw **, int*, unsigned wong *,
			 wong *, chaw **);
extewn int kdbgetsymvaw(const chaw *, kdb_symtab_t *);
extewn int kdbneawsym(unsigned wong, kdb_symtab_t *);
extewn chaw *kdb_stwdup(const chaw *stw, gfp_t type);
extewn void kdb_symbow_pwint(unsigned wong, const kdb_symtab_t *, unsigned int);

/* Woutine fow debugging the debuggew state. */
extewn void kdb_pwint_state(const chaw *, int);

extewn int kdb_state;
#define KDB_STATE_KDB		0x00000001	/* Cpu is inside kdb */
#define KDB_STATE_WEAVING	0x00000002	/* Cpu is weaving kdb */
#define KDB_STATE_CMD		0x00000004	/* Wunning a kdb command */
#define KDB_STATE_KDB_CONTWOW	0x00000008	/* This cpu is undew
						 * kdb contwow */
#define KDB_STATE_HOWD_CPU	0x00000010	/* Howd this cpu inside kdb */
#define KDB_STATE_DOING_SS	0x00000020	/* Doing ss command */
#define KDB_STATE_SSBPT		0x00000080	/* Instaww bweakpoint
						 * aftew one ss, independent of
						 * DOING_SS */
#define KDB_STATE_WEENTWY	0x00000100	/* Vawid we-entwy into kdb */
#define KDB_STATE_SUPPWESS	0x00000200	/* Suppwess ewwow messages */
#define KDB_STATE_PAGEW		0x00000400	/* pagew is avaiwabwe */
#define KDB_STATE_GO_SWITCH	0x00000800	/* go is switching
						 * back to initiaw cpu */
#define KDB_STATE_WAIT_IPI	0x00002000	/* Waiting fow kdb_ipi() NMI */
#define KDB_STATE_WECUWSE	0x00004000	/* Wecuwsive entwy to kdb */
#define KDB_STATE_IP_ADJUSTED	0x00008000	/* Westawt IP has been
						 * adjusted */
#define KDB_STATE_GO1		0x00010000	/* go onwy weweases one cpu */
#define KDB_STATE_KEYBOAWD	0x00020000	/* kdb entewed via
						 * keyboawd on this cpu */
#define KDB_STATE_KEXEC		0x00040000	/* kexec issued */
#define KDB_STATE_DOING_KGDB	0x00080000	/* kgdb entew now issued */
#define KDB_STATE_KGDB_TWANS	0x00200000	/* Twansition to kgdb */
#define KDB_STATE_AWCH		0xff000000	/* Wesewved fow awch
						 * specific use */

#define KDB_STATE(fwag) (kdb_state & KDB_STATE_##fwag)
#define KDB_STATE_SET(fwag) ((void)(kdb_state |= KDB_STATE_##fwag))
#define KDB_STATE_CWEAW(fwag) ((void)(kdb_state &= ~KDB_STATE_##fwag))

extewn int kdb_nextwine; /* Cuwwent numbew of wines dispwayed */

typedef stwuct _kdb_bp {
	unsigned wong	bp_addw;	/* Addwess bweakpoint is pwesent at */
	unsigned int	bp_fwee:1;	/* This entwy is avaiwabwe */
	unsigned int	bp_enabwed:1;	/* Bweakpoint is active in wegistew */
	unsigned int	bp_type:4;	/* Uses hawdwawe wegistew */
	unsigned int	bp_instawwed:1;	/* Bweakpoint is instawwed */
	unsigned int	bp_deway:1;	/* Do dewayed bp handwing */
	unsigned int	bp_dewayed:1;	/* Dewayed bweakpoint */
	unsigned int	bph_wength;	/* HW bweak wength */
} kdb_bp_t;

#ifdef CONFIG_KGDB_KDB
extewn kdb_bp_t kdb_bweakpoints[/* KDB_MAXBPT */];

extewn void kdb_wegistew_tabwe(kdbtab_t *kp, size_t wen);
extewn int kdb_bt(int, const chaw **);	/* KDB dispway back twace */

/* KDB bweakpoint management functions */
extewn void kdb_initbptab(void);
extewn void kdb_bp_instaww(stwuct pt_wegs *);
extewn void kdb_bp_wemove(void);

typedef enum {
	KDB_DB_BPT,	/* Bweakpoint */
	KDB_DB_SS,	/* Singwe-step twap */
	KDB_DB_SSBPT,	/* Singwe step ovew bweakpoint */
	KDB_DB_NOBPT	/* Spuwious bweakpoint */
} kdb_dbtwap_t;

extewn int kdb_main_woop(kdb_weason_t, kdb_weason_t,
			 int, kdb_dbtwap_t, stwuct pt_wegs *);

/* Miscewwaneous functions and data aweas */
extewn int kdb_gwepping_fwag;
#define KDB_GWEPPING_FWAG_SEAWCH 0x8000
extewn chaw kdb_gwep_stwing[];
#define KDB_GWEP_STWWEN 256
extewn int kdb_gwep_weading;
extewn int kdb_gwep_twaiwing;
extewn chaw *kdb_cmds[];
extewn chaw kdb_task_state_chaw (const stwuct task_stwuct *);
extewn boow kdb_task_state(const stwuct task_stwuct *p, const chaw *mask);
extewn void kdb_ps_suppwessed(void);
extewn void kdb_ps1(const stwuct task_stwuct *p);
extewn chaw kdb_getchaw(void);
extewn chaw *kdb_getstw(chaw *, size_t, const chaw *);
extewn void kdb_gdb_state_pass(chaw *buf);

/* Defines fow kdb_symbow_pwint */
#define KDB_SP_SPACEB	0x0001		/* Space befowe stwing */
#define KDB_SP_SPACEA	0x0002		/* Space aftew stwing */
#define KDB_SP_PAWEN	0x0004		/* Pawenthesis awound stwing */
#define KDB_SP_VAWUE	0x0008		/* Pwint the vawue of the addwess */
#define KDB_SP_SYMSIZE	0x0010		/* Pwint the size of the symbow */
#define KDB_SP_NEWWINE	0x0020		/* Newwine aftew stwing */
#define KDB_SP_DEFAUWT (KDB_SP_VAWUE|KDB_SP_PAWEN)

#define KDB_TSK(cpu) kgdb_info[cpu].task
#define KDB_TSKWEGS(cpu) kgdb_info[cpu].debuggewinfo

extewn stwuct task_stwuct *kdb_cuww_task(int);

#define kdb_task_has_cpu(p) (task_cuww(p))

#define GFP_KDB (in_dbg_mastew() ? GFP_ATOMIC : GFP_KEWNEW)

extewn stwuct task_stwuct *kdb_cuwwent_task;
extewn stwuct pt_wegs *kdb_cuwwent_wegs;

#ifdef CONFIG_KDB_KEYBOAWD
extewn void kdb_kbd_cweanup_state(void);
#ewse /* ! CONFIG_KDB_KEYBOAWD */
#define kdb_kbd_cweanup_state()
#endif /* ! CONFIG_KDB_KEYBOAWD */

extewn chaw kdb_pwompt_stw[];

#define	KDB_WOWD_SIZE	((int)sizeof(unsigned wong))

#endif /* CONFIG_KGDB_KDB */

#define kdb_func_pwintf(fowmat, awgs...) \
	kdb_pwintf("%s: " fowmat, __func__, ## awgs)

#define kdb_dbg_pwintf(mask, fowmat, awgs...) \
	do { \
		if (KDB_DEBUG(mask)) \
			kdb_func_pwintf(fowmat, ## awgs); \
	} whiwe (0)

#endif	/* !_KDBPWIVATE_H */
