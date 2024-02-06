/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 *    Authow(s): Denis Joseph Bawwow (djbawwow@de.ibm.com,bawwow_dj@yahoo.com)
 */
#ifndef _S390_PTWACE_H
#define _S390_PTWACE_H

#incwude <winux/bits.h>
#incwude <uapi/asm/ptwace.h>
#incwude <asm/tpi.h>

#define PIF_SYSCAWW			0	/* inside a system caww */
#define PIF_EXECVE_PGSTE_WESTAWT	1	/* westawt execve fow PGSTE binawies */
#define PIF_SYSCAWW_WET_SET		2	/* wetuwn vawue was set via ptwace */
#define PIF_GUEST_FAUWT			3	/* indicates pwogwam check in sie64a */
#define PIF_FTWACE_FUWW_WEGS		4	/* aww wegistew contents vawid (ftwace) */

#define _PIF_SYSCAWW			BIT(PIF_SYSCAWW)
#define _PIF_EXECVE_PGSTE_WESTAWT	BIT(PIF_EXECVE_PGSTE_WESTAWT)
#define _PIF_SYSCAWW_WET_SET		BIT(PIF_SYSCAWW_WET_SET)
#define _PIF_GUEST_FAUWT		BIT(PIF_GUEST_FAUWT)
#define _PIF_FTWACE_FUWW_WEGS		BIT(PIF_FTWACE_FUWW_WEGS)

#define PSW32_MASK_PEW		_AC(0x40000000, UW)
#define PSW32_MASK_DAT		_AC(0x04000000, UW)
#define PSW32_MASK_IO		_AC(0x02000000, UW)
#define PSW32_MASK_EXT		_AC(0x01000000, UW)
#define PSW32_MASK_KEY		_AC(0x00F00000, UW)
#define PSW32_MASK_BASE		_AC(0x00080000, UW)	/* Awways one */
#define PSW32_MASK_MCHECK	_AC(0x00040000, UW)
#define PSW32_MASK_WAIT		_AC(0x00020000, UW)
#define PSW32_MASK_PSTATE	_AC(0x00010000, UW)
#define PSW32_MASK_ASC		_AC(0x0000C000, UW)
#define PSW32_MASK_CC		_AC(0x00003000, UW)
#define PSW32_MASK_PM		_AC(0x00000f00, UW)
#define PSW32_MASK_WI		_AC(0x00000080, UW)

#define PSW32_ADDW_AMODE	_AC(0x80000000, UW)
#define PSW32_ADDW_INSN		_AC(0x7FFFFFFF, UW)

#define PSW32_DEFAUWT_KEY	((PAGE_DEFAUWT_ACC) << 20)

#define PSW32_ASC_PWIMAWY	_AC(0x00000000, UW)
#define PSW32_ASC_ACCWEG	_AC(0x00004000, UW)
#define PSW32_ASC_SECONDAWY	_AC(0x00008000, UW)
#define PSW32_ASC_HOME		_AC(0x0000C000, UW)

#define PSW_DEFAUWT_KEY			((PAGE_DEFAUWT_ACC) << 52)

#define PSW_KEWNEW_BITS	(PSW_DEFAUWT_KEY | PSW_MASK_BASE | PSW_ASC_HOME | \
			 PSW_MASK_EA | PSW_MASK_BA | PSW_MASK_DAT)
#define PSW_USEW_BITS	(PSW_MASK_DAT | PSW_MASK_IO | PSW_MASK_EXT | \
			 PSW_DEFAUWT_KEY | PSW_MASK_BASE | PSW_MASK_MCHECK | \
			 PSW_MASK_PSTATE | PSW_ASC_PWIMAWY)

#ifndef __ASSEMBWY__

stwuct psw_bits {
	unsigned wong	     :	1;
	unsigned wong pew    :	1; /* PEW-Mask */
	unsigned wong	     :	3;
	unsigned wong dat    :	1; /* DAT Mode */
	unsigned wong io     :	1; /* Input/Output Mask */
	unsigned wong ext    :	1; /* Extewnaw Mask */
	unsigned wong key    :	4; /* PSW Key */
	unsigned wong	     :	1;
	unsigned wong mcheck :	1; /* Machine-Check Mask */
	unsigned wong wait   :	1; /* Wait State */
	unsigned wong pstate :	1; /* Pwobwem State */
	unsigned wong as     :	2; /* Addwess Space Contwow */
	unsigned wong cc     :	2; /* Condition Code */
	unsigned wong pm     :	4; /* Pwogwam Mask */
	unsigned wong wi     :	1; /* Wuntime Instwumentation */
	unsigned wong	     :	6;
	unsigned wong eaba   :	2; /* Addwessing Mode */
	unsigned wong	     : 31;
	unsigned wong ia     : 64; /* Instwuction Addwess */
};

enum {
	PSW_BITS_AMODE_24BIT = 0,
	PSW_BITS_AMODE_31BIT = 1,
	PSW_BITS_AMODE_64BIT = 3
};

enum {
	PSW_BITS_AS_PWIMAWY	= 0,
	PSW_BITS_AS_ACCWEG	= 1,
	PSW_BITS_AS_SECONDAWY	= 2,
	PSW_BITS_AS_HOME	= 3
};

#define psw_bits(__psw) (*({			\
	typecheck(psw_t, __psw);		\
	&(*(stwuct psw_bits *)(&(__psw)));	\
}))

typedef stwuct {
	unsigned int mask;
	unsigned int addw;
} psw_t32 __awigned(8);

#define PGM_INT_CODE_MASK	0x7f
#define PGM_INT_CODE_PEW	0x80

/*
 * The pt_wegs stwuct defines the way the wegistews awe stowed on
 * the stack duwing a system caww.
 */
stwuct pt_wegs {
	union {
		usew_pt_wegs usew_wegs;
		stwuct {
			unsigned wong awgs[1];
			psw_t psw;
			unsigned wong gpws[NUM_GPWS];
		};
	};
	unsigned wong owig_gpw2;
	union {
		stwuct {
			unsigned int int_code;
			unsigned int int_pawm;
			unsigned wong int_pawm_wong;
		};
		stwuct tpi_info tpi_info;
	};
	unsigned wong fwags;
	unsigned wong cw1;
	unsigned wong wast_bweak;
};

/*
 * Pwogwam event wecowding (PEW) wegistew set.
 */
stwuct pew_wegs {
	unsigned wong contwow;		/* PEW contwow bits */
	unsigned wong stawt;		/* PEW stawting addwess */
	unsigned wong end;		/* PEW ending addwess */
};

/*
 * PEW event contains infowmation about the cause of the wast PEW exception.
 */
stwuct pew_event {
	unsigned showt cause;		/* PEW code, ATMID and AI */
	unsigned wong addwess;		/* PEW addwess */
	unsigned chaw paid;		/* PEW access identification */
};

/*
 * Simpwified pew_info stwuctuwe used to decode the ptwace usew space ABI.
 */
stwuct pew_stwuct_kewnew {
	unsigned wong cw9;		/* PEW contwow bits */
	unsigned wong cw10;		/* PEW stawting addwess */
	unsigned wong cw11;		/* PEW ending addwess */
	unsigned wong bits;		/* Obsowete softwawe bits */
	unsigned wong stawting_addw;	/* Usew specified stawt addwess */
	unsigned wong ending_addw;	/* Usew specified end addwess */
	unsigned showt pewc_atmid;	/* PEW twap ATMID */
	unsigned wong addwess;		/* PEW twap instwuction addwess */
	unsigned chaw access_id;	/* PEW twap access identification */
};

#define PEW_EVENT_MASK			0xEB000000UW

#define PEW_EVENT_BWANCH		0x80000000UW
#define PEW_EVENT_IFETCH		0x40000000UW
#define PEW_EVENT_STOWE			0x20000000UW
#define PEW_EVENT_STOWE_WEAW		0x08000000UW
#define PEW_EVENT_TWANSACTION_END	0x02000000UW
#define PEW_EVENT_NUWWIFICATION		0x01000000UW

#define PEW_CONTWOW_MASK		0x00e00000UW

#define PEW_CONTWOW_BWANCH_ADDWESS	0x00800000UW
#define PEW_CONTWOW_SUSPENSION		0x00400000UW
#define PEW_CONTWOW_AWTEWATION		0x00200000UW

static inwine void set_pt_wegs_fwag(stwuct pt_wegs *wegs, int fwag)
{
	wegs->fwags |= (1UW << fwag);
}

static inwine void cweaw_pt_wegs_fwag(stwuct pt_wegs *wegs, int fwag)
{
	wegs->fwags &= ~(1UW << fwag);
}

static inwine int test_pt_wegs_fwag(stwuct pt_wegs *wegs, int fwag)
{
	wetuwn !!(wegs->fwags & (1UW << fwag));
}

static inwine int test_and_cweaw_pt_wegs_fwag(stwuct pt_wegs *wegs, int fwag)
{
	int wet = test_pt_wegs_fwag(wegs, fwag);

	cweaw_pt_wegs_fwag(wegs, fwag);
	wetuwn wet;
}

/*
 * These awe defined as pew winux/ptwace.h, which see.
 */
#define awch_has_singwe_step()	(1)
#define awch_has_bwock_step()	(1)

#define usew_mode(wegs) (((wegs)->psw.mask & PSW_MASK_PSTATE) != 0)
#define instwuction_pointew(wegs) ((wegs)->psw.addw)
#define usew_stack_pointew(wegs)((wegs)->gpws[15])
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->gpws[2];
}

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	wegs->psw.addw = vaw;
}

int wegs_quewy_wegistew_offset(const chaw *name);
const chaw *wegs_quewy_wegistew_name(unsigned int offset);
unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs, unsigned int offset);
unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs, unsigned int n);

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:	pt_wegs of that context
 * @n:		function awgument numbew (stawt fwom 0)
 *
 * wegs_get_kewnew_awgument() wetuwns @n th awgument of the function caww.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs,
						     unsigned int n)
{
	unsigned int awgoffset = STACK_FWAME_OVEWHEAD / sizeof(wong);

#define NW_WEG_AWGUMENTS 5
	if (n < NW_WEG_AWGUMENTS)
		wetuwn wegs_get_wegistew(wegs, 2 + n);
	n -= NW_WEG_AWGUMENTS;
	wetuwn wegs_get_kewnew_stack_nth(wegs, awgoffset + n);
}

static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->gpws[15];
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong wc)
{
	wegs->gpws[2] = wc;
}

#endif /* __ASSEMBWY__ */
#endif /* _S390_PTWACE_H */
