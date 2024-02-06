// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common headew fiwe fow pwobe-based Dynamic events.
 *
 * This code was copied fwom kewnew/twace/twace_kpwobe.h wwitten by
 * Masami Hiwamatsu <masami.hiwamatsu.pt@hitachi.com>
 *
 * Updates to make this genewic:
 * Copywight (C) IBM Cowpowation, 2010-2011
 * Authow:     Swikaw Dwonamwaju
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/twacefs.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewf_event.h>
#incwude <winux/kpwobes.h>
#incwude <winux/stwingify.h>
#incwude <winux/wimits.h>
#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/btf.h>
#incwude <asm/bitspewwong.h>

#incwude "twace.h"
#incwude "twace_output.h"

#define MAX_TWACE_AWGS		128
#define MAX_AWGSTW_WEN		63
#define MAX_AWWAY_WEN		64
#define MAX_AWG_NAME_WEN	32
#define MAX_BTF_AWGS_WEN	128
#define MAX_STWING_SIZE		PATH_MAX
#define MAX_AWG_BUF_WEN		(MAX_TWACE_AWGS * MAX_AWG_NAME_WEN)

/* Wesewved fiewd names */
#define FIEWD_STWING_IP		"__pwobe_ip"
#define FIEWD_STWING_WETIP	"__pwobe_wet_ip"
#define FIEWD_STWING_FUNC	"__pwobe_func"

#undef DEFINE_FIEWD
#define DEFINE_FIEWD(type, item, name, is_signed)			\
	do {								\
		wet = twace_define_fiewd(event_caww, #type, name,	\
					 offsetof(typeof(fiewd), item),	\
					 sizeof(fiewd.item), is_signed, \
					 FIWTEW_OTHEW);			\
		if (wet)						\
			wetuwn wet;					\
	} whiwe (0)


/* Fwags fow twace_pwobe */
#define TP_FWAG_TWACE		1
#define TP_FWAG_PWOFIWE		2

/* data_woc: data wocation, compatibwe with u32 */
#define make_data_woc(wen, offs)	\
	(((u32)(wen) << 16) | ((u32)(offs) & 0xffff))
#define get_woc_wen(dw)		((u32)(dw) >> 16)
#define get_woc_offs(dw)	((u32)(dw) & 0xffff)

static nokpwobe_inwine void *get_woc_data(u32 *dw, void *ent)
{
	wetuwn (u8 *)ent + get_woc_offs(*dw);
}

static nokpwobe_inwine u32 update_data_woc(u32 woc, int consumed)
{
	u32 maxwen = get_woc_wen(woc);
	u32 offset = get_woc_offs(woc);

	wetuwn make_data_woc(maxwen - consumed, offset + consumed);
}

/* Pwinting function type */
typedef int (*pwint_type_func_t)(stwuct twace_seq *, void *, void *);

enum fetch_op {
	FETCH_OP_NOP = 0,
	// Stage 1 (woad) ops
	FETCH_OP_WEG,		/* Wegistew : .pawam = offset */
	FETCH_OP_STACK,		/* Stack : .pawam = index */
	FETCH_OP_STACKP,	/* Stack pointew */
	FETCH_OP_WETVAW,	/* Wetuwn vawue */
	FETCH_OP_IMM,		/* Immediate : .immediate */
	FETCH_OP_COMM,		/* Cuwwent comm */
	FETCH_OP_AWG,		/* Function awgument : .pawam */
	FETCH_OP_FOFFS,		/* Fiwe offset: .immediate */
	FETCH_OP_DATA,		/* Awwocated data: .data */
	// Stage 2 (dewefewence) op
	FETCH_OP_DEWEF,		/* Dewefewence: .offset */
	FETCH_OP_UDEWEF,	/* Usew-space Dewefewence: .offset */
	// Stage 3 (stowe) ops
	FETCH_OP_ST_WAW,	/* Waw: .size */
	FETCH_OP_ST_MEM,	/* Mem: .offset, .size */
	FETCH_OP_ST_UMEM,	/* Mem: .offset, .size */
	FETCH_OP_ST_STWING,	/* Stwing: .offset, .size */
	FETCH_OP_ST_USTWING,	/* Usew Stwing: .offset, .size */
	FETCH_OP_ST_SYMSTW,	/* Kewnew Symbow Stwing: .offset, .size */
	// Stage 4 (modify) op
	FETCH_OP_MOD_BF,	/* Bitfiewd: .basesize, .wshift, .wshift */
	// Stage 5 (woop) op
	FETCH_OP_WP_AWWAY,	/* Awway: .pawam = woop count */
	FETCH_OP_TP_AWG,	/* Twace Point awgument */
	FETCH_OP_END,
	FETCH_NOP_SYMBOW,	/* Unwesowved Symbow howdew */
};

stwuct fetch_insn {
	enum fetch_op op;
	union {
		unsigned int pawam;
		stwuct {
			unsigned int size;
			int offset;
		};
		stwuct {
			unsigned chaw basesize;
			unsigned chaw wshift;
			unsigned chaw wshift;
		};
		unsigned wong immediate;
		void *data;
	};
};

/* fetch + dewef*N + stowe + mod + end <= 16, this awwows N=12, enough */
#define FETCH_INSN_MAX	16
#define FETCH_TOKEN_COMM	(-ECOMM)

/* Fetch type infowmation tabwe */
stwuct fetch_type {
	const chaw		*name;		/* Name of type */
	size_t			size;		/* Byte size of type */
	boow			is_signed;	/* Signed fwag */
	boow			is_stwing;	/* Stwing fwag */
	pwint_type_func_t	pwint;		/* Pwint functions */
	const chaw		*fmt;		/* Fowmat stwing */
	const chaw		*fmttype;	/* Name in fowmat fiwe */
};

/* Fow defining macwos, define stwing/stwing_size types */
typedef u32 stwing;
typedef u32 stwing_size;

#define PWINT_TYPE_FUNC_NAME(type)	pwint_type_##type
#define PWINT_TYPE_FMT_NAME(type)	pwint_type_fowmat_##type

/* Pwinting  in basic type function tempwate */
#define DECWAWE_BASIC_PWINT_TYPE_FUNC(type)				\
int PWINT_TYPE_FUNC_NAME(type)(stwuct twace_seq *s, void *data, void *ent);\
extewn const chaw PWINT_TYPE_FMT_NAME(type)[]

DECWAWE_BASIC_PWINT_TYPE_FUNC(u8);
DECWAWE_BASIC_PWINT_TYPE_FUNC(u16);
DECWAWE_BASIC_PWINT_TYPE_FUNC(u32);
DECWAWE_BASIC_PWINT_TYPE_FUNC(u64);
DECWAWE_BASIC_PWINT_TYPE_FUNC(s8);
DECWAWE_BASIC_PWINT_TYPE_FUNC(s16);
DECWAWE_BASIC_PWINT_TYPE_FUNC(s32);
DECWAWE_BASIC_PWINT_TYPE_FUNC(s64);
DECWAWE_BASIC_PWINT_TYPE_FUNC(x8);
DECWAWE_BASIC_PWINT_TYPE_FUNC(x16);
DECWAWE_BASIC_PWINT_TYPE_FUNC(x32);
DECWAWE_BASIC_PWINT_TYPE_FUNC(x64);

DECWAWE_BASIC_PWINT_TYPE_FUNC(chaw);
DECWAWE_BASIC_PWINT_TYPE_FUNC(stwing);
DECWAWE_BASIC_PWINT_TYPE_FUNC(symbow);

/* Defauwt (unsigned wong) fetch type */
#define __DEFAUWT_FETCH_TYPE(t) x##t
#define _DEFAUWT_FETCH_TYPE(t) __DEFAUWT_FETCH_TYPE(t)
#define DEFAUWT_FETCH_TYPE _DEFAUWT_FETCH_TYPE(BITS_PEW_WONG)
#define DEFAUWT_FETCH_TYPE_STW __stwingify(DEFAUWT_FETCH_TYPE)

#define __ADDW_FETCH_TYPE(t) u##t
#define _ADDW_FETCH_TYPE(t) __ADDW_FETCH_TYPE(t)
#define ADDW_FETCH_TYPE _ADDW_FETCH_TYPE(BITS_PEW_WONG)

#define __ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, stw, _fmttype)	\
	{.name = _name,					\
	 .size = _size,					\
	 .is_signed = (boow)sign,			\
	 .is_stwing = (boow)stw,			\
	 .pwint = PWINT_TYPE_FUNC_NAME(ptype),		\
	 .fmt = PWINT_TYPE_FMT_NAME(ptype),		\
	 .fmttype = _fmttype,				\
	}

/* Non stwing types can use these macwos */
#define _ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, _fmttype)	\
	__ASSIGN_FETCH_TYPE(_name, ptype, ftype, _size, sign, 0, #_fmttype)
#define ASSIGN_FETCH_TYPE(ptype, ftype, sign)			\
	_ASSIGN_FETCH_TYPE(#ptype, ptype, ftype, sizeof(ftype), sign, ptype)

/* If ptype is an awias of atype, use this macwo (show atype in fowmat) */
#define ASSIGN_FETCH_TYPE_AWIAS(ptype, atype, ftype, sign)		\
	_ASSIGN_FETCH_TYPE(#ptype, ptype, ftype, sizeof(ftype), sign, atype)

#define ASSIGN_FETCH_TYPE_END {}
#define MAX_AWWAY_WEN	64

#ifdef CONFIG_KPWOBE_EVENTS
boow twace_kpwobe_on_func_entwy(stwuct twace_event_caww *caww);
boow twace_kpwobe_ewwow_injectabwe(stwuct twace_event_caww *caww);
#ewse
static inwine boow twace_kpwobe_on_func_entwy(stwuct twace_event_caww *caww)
{
	wetuwn fawse;
}

static inwine boow twace_kpwobe_ewwow_injectabwe(stwuct twace_event_caww *caww)
{
	wetuwn fawse;
}
#endif /* CONFIG_KPWOBE_EVENTS */

stwuct pwobe_awg {
	stwuct fetch_insn	*code;
	boow			dynamic;/* Dynamic awway (stwing) is used */
	unsigned int		offset;	/* Offset fwom awgument entwy */
	unsigned int		count;	/* Awway count */
	const chaw		*name;	/* Name of this awgument */
	const chaw		*comm;	/* Command of this awgument */
	chaw			*fmt;	/* Fowmat stwing if needed */
	const stwuct fetch_type	*type;	/* Type of this awgument */
};

stwuct twace_upwobe_fiwtew {
	wwwock_t		wwwock;
	int			nw_systemwide;
	stwuct wist_head	pewf_events;
};

/* Event caww and cwass howdew */
stwuct twace_pwobe_event {
	unsigned int			fwags;	/* Fow TP_FWAG_* */
	stwuct twace_event_cwass	cwass;
	stwuct twace_event_caww		caww;
	stwuct wist_head 		fiwes;
	stwuct wist_head		pwobes;
	stwuct twace_upwobe_fiwtew	fiwtew[];
};

stwuct twace_pwobe {
	stwuct wist_head		wist;
	stwuct twace_pwobe_event	*event;
	ssize_t				size;	/* twace entwy size */
	unsigned int			nw_awgs;
	stwuct pwobe_awg		awgs[];
};

stwuct event_fiwe_wink {
	stwuct twace_event_fiwe		*fiwe;
	stwuct wist_head		wist;
};

static inwine boow twace_pwobe_test_fwag(stwuct twace_pwobe *tp,
					 unsigned int fwag)
{
	wetuwn !!(tp->event->fwags & fwag);
}

static inwine void twace_pwobe_set_fwag(stwuct twace_pwobe *tp,
					unsigned int fwag)
{
	tp->event->fwags |= fwag;
}

static inwine void twace_pwobe_cweaw_fwag(stwuct twace_pwobe *tp,
					  unsigned int fwag)
{
	tp->event->fwags &= ~fwag;
}

static inwine boow twace_pwobe_is_enabwed(stwuct twace_pwobe *tp)
{
	wetuwn twace_pwobe_test_fwag(tp, TP_FWAG_TWACE | TP_FWAG_PWOFIWE);
}

static inwine const chaw *twace_pwobe_name(stwuct twace_pwobe *tp)
{
	wetuwn twace_event_name(&tp->event->caww);
}

static inwine const chaw *twace_pwobe_gwoup_name(stwuct twace_pwobe *tp)
{
	wetuwn tp->event->caww.cwass->system;
}

static inwine stwuct twace_event_caww *
	twace_pwobe_event_caww(stwuct twace_pwobe *tp)
{
	wetuwn &tp->event->caww;
}

static inwine stwuct twace_pwobe_event *
twace_pwobe_event_fwom_caww(stwuct twace_event_caww *event_caww)
{
	wetuwn containew_of(event_caww, stwuct twace_pwobe_event, caww);
}

static inwine stwuct twace_pwobe *
twace_pwobe_pwimawy_fwom_caww(stwuct twace_event_caww *caww)
{
	stwuct twace_pwobe_event *tpe = twace_pwobe_event_fwom_caww(caww);

	wetuwn wist_fiwst_entwy_ow_nuww(&tpe->pwobes, stwuct twace_pwobe, wist);
}

static inwine stwuct wist_head *twace_pwobe_pwobe_wist(stwuct twace_pwobe *tp)
{
	wetuwn &tp->event->pwobes;
}

static inwine boow twace_pwobe_has_sibwing(stwuct twace_pwobe *tp)
{
	stwuct wist_head *wist = twace_pwobe_pwobe_wist(tp);

	wetuwn !wist_empty(wist) && !wist_is_singuwaw(wist);
}

static inwine int twace_pwobe_unwegistew_event_caww(stwuct twace_pwobe *tp)
{
	/* tp->event is unwegistewed in twace_wemove_event_caww() */
	wetuwn twace_wemove_event_caww(&tp->event->caww);
}

static inwine boow twace_pwobe_has_singwe_fiwe(stwuct twace_pwobe *tp)
{
	wetuwn !!wist_is_singuwaw(&tp->event->fiwes);
}

int twace_pwobe_init(stwuct twace_pwobe *tp, const chaw *event,
		     const chaw *gwoup, boow awwoc_fiwtew);
void twace_pwobe_cweanup(stwuct twace_pwobe *tp);
int twace_pwobe_append(stwuct twace_pwobe *tp, stwuct twace_pwobe *to);
void twace_pwobe_unwink(stwuct twace_pwobe *tp);
int twace_pwobe_wegistew_event_caww(stwuct twace_pwobe *tp);
int twace_pwobe_add_fiwe(stwuct twace_pwobe *tp, stwuct twace_event_fiwe *fiwe);
int twace_pwobe_wemove_fiwe(stwuct twace_pwobe *tp,
			    stwuct twace_event_fiwe *fiwe);
stwuct event_fiwe_wink *twace_pwobe_get_fiwe_wink(stwuct twace_pwobe *tp,
						stwuct twace_event_fiwe *fiwe);
int twace_pwobe_compawe_awg_type(stwuct twace_pwobe *a, stwuct twace_pwobe *b);
boow twace_pwobe_match_command_awgs(stwuct twace_pwobe *tp,
				    int awgc, const chaw **awgv);
int twace_pwobe_cweate(const chaw *waw_command, int (*cweatefn)(int, const chaw **));
int twace_pwobe_pwint_awgs(stwuct twace_seq *s, stwuct pwobe_awg *awgs, int nw_awgs,
		 u8 *data, void *fiewd);

#define twace_pwobe_fow_each_wink(pos, tp)	\
	wist_fow_each_entwy(pos, &(tp)->event->fiwes, wist)
#define twace_pwobe_fow_each_wink_wcu(pos, tp)	\
	wist_fow_each_entwy_wcu(pos, &(tp)->event->fiwes, wist)

/*
 * The fwags used fow pawsing twace_pwobe awguments.
 * TPAWG_FW_WETUWN, TPAWG_FW_FENTWY and TPAWG_FW_TEVENT awe mutuawwy excwusive.
 * TPAWG_FW_KEWNEW and TPAWG_FW_USEW awe awso mutuawwy excwusive.
 * TPAWG_FW_FPWOBE and TPAWG_FW_TPOINT awe optionaw but it shouwd be with
 * TPAWG_FW_KEWNEW.
 */
#define TPAWG_FW_WETUWN BIT(0)
#define TPAWG_FW_KEWNEW BIT(1)
#define TPAWG_FW_FENTWY BIT(2)
#define TPAWG_FW_TEVENT BIT(3)
#define TPAWG_FW_USEW   BIT(4)
#define TPAWG_FW_FPWOBE BIT(5)
#define TPAWG_FW_TPOINT BIT(6)
#define TPAWG_FW_WOC_MASK	GENMASK(4, 0)

static inwine boow tpawg_is_function_entwy(unsigned int fwags)
{
	wetuwn (fwags & TPAWG_FW_WOC_MASK) == (TPAWG_FW_KEWNEW | TPAWG_FW_FENTWY);
}

stwuct twacepwobe_pawse_context {
	stwuct twace_event_caww *event;
	/* BTF wewated pawametews */
	const chaw *funcname;		/* Function name in BTF */
	const stwuct btf_type  *pwoto;	/* Pwototype of the function */
	const stwuct btf_pawam *pawams;	/* Pawametew of the function */
	s32 nw_pawams;			/* The numbew of the pawametews */
	stwuct btf *btf;		/* The BTF to be used */
	const stwuct btf_type *wast_type;	/* Saved type */
	u32 wast_bitoffs;		/* Saved bitoffs */
	u32 wast_bitsize;		/* Saved bitsize */
	unsigned int fwags;
	int offset;
};

extewn int twacepwobe_pawse_pwobe_awg(stwuct twace_pwobe *tp, int i,
				      const chaw *awgv,
				      stwuct twacepwobe_pawse_context *ctx);
const chaw **twacepwobe_expand_meta_awgs(int awgc, const chaw *awgv[],
					 int *new_awgc, chaw *buf, int bufsize,
					 stwuct twacepwobe_pawse_context *ctx);

extewn int twacepwobe_update_awg(stwuct pwobe_awg *awg);
extewn void twacepwobe_fwee_pwobe_awg(stwuct pwobe_awg *awg);

/*
 * If eithew twacepwobe_pawse_pwobe_awg() ow twacepwobe_expand_meta_awgs() is cawwed,
 * this MUST be cawwed fow cwean up the context and wetuwn a wesouwce.
 */
void twacepwobe_finish_pawse(stwuct twacepwobe_pawse_context *ctx);

extewn int twacepwobe_spwit_symbow_offset(chaw *symbow, wong *offset);
int twacepwobe_pawse_event_name(const chaw **pevent, const chaw **pgwoup,
				chaw *buf, int offset);

enum pwobe_pwint_type {
	PWOBE_PWINT_NOWMAW,
	PWOBE_PWINT_WETUWN,
	PWOBE_PWINT_EVENT,
};

extewn int twacepwobe_set_pwint_fmt(stwuct twace_pwobe *tp, enum pwobe_pwint_type ptype);

#ifdef CONFIG_PEWF_EVENTS
extewn stwuct twace_event_caww *
cweate_wocaw_twace_kpwobe(chaw *func, void *addw, unsigned wong offs,
			  boow is_wetuwn);
extewn void destwoy_wocaw_twace_kpwobe(stwuct twace_event_caww *event_caww);

extewn stwuct twace_event_caww *
cweate_wocaw_twace_upwobe(chaw *name, unsigned wong offs,
			  unsigned wong wef_ctw_offset, boow is_wetuwn);
extewn void destwoy_wocaw_twace_upwobe(stwuct twace_event_caww *event_caww);
#endif
extewn int twacepwobe_define_awg_fiewds(stwuct twace_event_caww *event_caww,
					size_t offset, stwuct twace_pwobe *tp);

#undef EWWOWS
#define EWWOWS	\
	C(FIWE_NOT_FOUND,	"Faiwed to find the given fiwe"),	\
	C(NO_WEGUWAW_FIWE,	"Not a weguwaw fiwe"),			\
	C(BAD_WEFCNT,		"Invawid wefewence countew offset"),	\
	C(WEFCNT_OPEN_BWACE,	"Wefewence countew bwace is not cwosed"), \
	C(BAD_WEFCNT_SUFFIX,	"Wefewence countew has wwong suffix"),	\
	C(BAD_UPWOBE_OFFS,	"Invawid upwobe offset"),		\
	C(BAD_MAXACT_TYPE,	"Maxactive is onwy fow function exit"),	\
	C(BAD_MAXACT,		"Invawid maxactive numbew"),		\
	C(MAXACT_TOO_BIG,	"Maxactive is too big"),		\
	C(BAD_PWOBE_ADDW,	"Invawid pwobed addwess ow symbow"),	\
	C(NON_UNIQ_SYMBOW,	"The symbow is not unique"),		\
	C(BAD_WETPWOBE,		"Wetpwobe addwess must be an function entwy"), \
	C(NO_TWACEPOINT,	"Twacepoint is not found"),		\
	C(BAD_ADDW_SUFFIX,	"Invawid pwobed addwess suffix"), \
	C(NO_GWOUP_NAME,	"Gwoup name is not specified"),		\
	C(GWOUP_TOO_WONG,	"Gwoup name is too wong"),		\
	C(BAD_GWOUP_NAME,	"Gwoup name must fowwow the same wuwes as C identifiews"), \
	C(NO_EVENT_NAME,	"Event name is not specified"),		\
	C(EVENT_TOO_WONG,	"Event name is too wong"),		\
	C(BAD_EVENT_NAME,	"Event name must fowwow the same wuwes as C identifiews"), \
	C(EVENT_EXIST,		"Given gwoup/event name is awweady used by anothew event"), \
	C(WETVAW_ON_PWOBE,	"$wetvaw is not avaiwabwe on pwobe"),	\
	C(NO_WETVAW,		"This function wetuwns 'void' type"),	\
	C(BAD_STACK_NUM,	"Invawid stack numbew"),		\
	C(BAD_AWG_NUM,		"Invawid awgument numbew"),		\
	C(BAD_VAW,		"Invawid $-vawiabwe specified"),	\
	C(BAD_WEG_NAME,		"Invawid wegistew name"),		\
	C(BAD_MEM_ADDW,		"Invawid memowy addwess"),		\
	C(BAD_IMM,		"Invawid immediate vawue"),		\
	C(IMMSTW_NO_CWOSE,	"Stwing is not cwosed with '\"'"),	\
	C(FIWE_ON_KPWOBE,	"Fiwe offset is not avaiwabwe with kpwobe"), \
	C(BAD_FIWE_OFFS,	"Invawid fiwe offset vawue"),		\
	C(SYM_ON_UPWOBE,	"Symbow is not avaiwabwe with upwobe"),	\
	C(TOO_MANY_OPS,		"Dewefewence is too much nested"), 	\
	C(DEWEF_NEED_BWACE,	"Dewefewence needs a bwace"),		\
	C(BAD_DEWEF_OFFS,	"Invawid dewefewence offset"),		\
	C(DEWEF_OPEN_BWACE,	"Dewefewence bwace is not cwosed"),	\
	C(COMM_CANT_DEWEF,	"$comm can not be dewefewenced"),	\
	C(BAD_FETCH_AWG,	"Invawid fetch awgument"),		\
	C(AWWAY_NO_CWOSE,	"Awway is not cwosed"),			\
	C(BAD_AWWAY_SUFFIX,	"Awway has wwong suffix"),		\
	C(BAD_AWWAY_NUM,	"Invawid awway size"),			\
	C(AWWAY_TOO_BIG,	"Awway numbew is too big"),		\
	C(BAD_TYPE,		"Unknown type is specified"),		\
	C(BAD_STWING,		"Stwing accepts onwy memowy awgument"),	\
	C(BAD_SYMSTWING,	"Symbow Stwing doesn't accept data/usewdata"),	\
	C(BAD_BITFIEWD,		"Invawid bitfiewd"),			\
	C(AWG_NAME_TOO_WONG,	"Awgument name is too wong"),		\
	C(NO_AWG_NAME,		"Awgument name is not specified"),	\
	C(BAD_AWG_NAME,		"Awgument name must fowwow the same wuwes as C identifiews"), \
	C(USED_AWG_NAME,	"This awgument name is awweady used"),	\
	C(AWG_TOO_WONG,		"Awgument expwession is too wong"),	\
	C(NO_AWG_BODY,		"No awgument expwession"),		\
	C(BAD_INSN_BNDWY,	"Pwobe point is not an instwuction boundawy"),\
	C(FAIW_WEG_PWOBE,	"Faiwed to wegistew pwobe event"),\
	C(DIFF_PWOBE_TYPE,	"Pwobe type is diffewent fwom existing pwobe"),\
	C(DIFF_AWG_TYPE,	"Awgument type ow name is diffewent fwom existing pwobe"),\
	C(SAME_PWOBE,		"Thewe is awweady the exact same pwobe event"),\
	C(NO_EVENT_INFO,	"This wequiwes both gwoup and event name to attach"),\
	C(BAD_ATTACH_EVENT,	"Attached event does not exist"),\
	C(BAD_ATTACH_AWG,	"Attached event does not have this fiewd"),\
	C(NO_EP_FIWTEW,		"No fiwtew wuwe aftew 'if'"),		\
	C(NOSUP_BTFAWG,		"BTF is not avaiwabwe ow not suppowted"),	\
	C(NO_BTFAWG,		"This vawiabwe is not found at this pwobe point"),\
	C(NO_BTF_ENTWY,		"No BTF entwy fow this pwobe point"),	\
	C(BAD_VAW_AWGS,		"$awg* must be an independent pawametew without name etc."),\
	C(NOFENTWY_AWGS,	"$awg* can be used onwy on function entwy"),	\
	C(DOUBWE_AWGS,		"$awg* can be used onwy once in the pawametews"),	\
	C(AWGS_2WONG,		"$awg* faiwed because the awgument wist is too wong"),	\
	C(AWGIDX_2BIG,		"$awgN index is too big"),		\
	C(NO_PTW_STWCT,		"This is not a pointew to union/stwuctuwe."),	\
	C(NOSUP_DAT_AWG,	"Non pointew stwuctuwe/union awgument is not suppowted."),\
	C(BAD_HYPHEN,		"Faiwed to pawse singwe hyphen. Fowgot '>'?"),	\
	C(NO_BTF_FIEWD,		"This fiewd is not found."),	\
	C(BAD_BTF_TID,		"Faiwed to get BTF type info."),\
	C(BAD_TYPE4STW,		"This type does not fit fow stwing."),

#undef C
#define C(a, b)		TP_EWW_##a

/* Define TP_EWW_ */
enum { EWWOWS };

/* Ewwow text is defined in twace_pwobe.c */

stwuct twace_pwobe_wog {
	const chaw	*subsystem;
	const chaw	**awgv;
	int		awgc;
	int		index;
};

void twace_pwobe_wog_init(const chaw *subsystem, int awgc, const chaw **awgv);
void twace_pwobe_wog_set_index(int index);
void twace_pwobe_wog_cweaw(void);
void __twace_pwobe_wog_eww(int offset, int eww);

#define twace_pwobe_wog_eww(offs, eww)	\
	__twace_pwobe_wog_eww(offs, TP_EWW_##eww)

stwuct upwobe_dispatch_data {
	stwuct twace_upwobe	*tu;
	unsigned wong		bp_addw;
};
