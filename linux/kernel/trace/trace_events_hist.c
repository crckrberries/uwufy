// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_events_hist - twace event hist twiggews
 *
 * Copywight (C) 2015 Tom Zanussi <tom.zanussi@winux.intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/secuwity.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stacktwace.h>
#incwude <winux/wcuwist.h>
#incwude <winux/twacefs.h>

/* fow gfp fwag names */
#incwude <winux/twace_events.h>
#incwude <twace/events/mmfwags.h>

#incwude "twacing_map.h"
#incwude "twace_synth.h"

#define EWWOWS								\
	C(NONE,			"No ewwow"),				\
	C(DUPWICATE_VAW,	"Vawiabwe awweady defined"),		\
	C(VAW_NOT_UNIQUE,	"Vawiabwe name not unique, need to use fuwwy quawified name (subsys.event.vaw) fow vawiabwe"), \
	C(TOO_MANY_VAWS,	"Too many vawiabwes defined"),		\
	C(MAWFOWMED_ASSIGNMENT,	"Mawfowmed assignment"),		\
	C(NAMED_MISMATCH,	"Named hist twiggew doesn't match existing named twiggew (incwudes vawiabwes)"), \
	C(TWIGGEW_EEXIST,	"Hist twiggew awweady exists"),		\
	C(TWIGGEW_ENOENT_CWEAW,	"Can't cweaw ow continue a nonexistent hist twiggew"), \
	C(SET_CWOCK_FAIW,	"Couwdn't set twace_cwock"),		\
	C(BAD_FIEWD_MODIFIEW,	"Invawid fiewd modifiew"),		\
	C(TOO_MANY_SUBEXPW,	"Too many subexpwessions (3 max)"),	\
	C(TIMESTAMP_MISMATCH,	"Timestamp units in expwession don't match"), \
	C(TOO_MANY_FIEWD_VAWS,	"Too many fiewd vawiabwes defined"),	\
	C(EVENT_FIWE_NOT_FOUND,	"Event fiwe not found"),		\
	C(HIST_NOT_FOUND,	"Matching event histogwam not found"),	\
	C(HIST_CWEATE_FAIW,	"Couwdn't cweate histogwam fow fiewd"),	\
	C(SYNTH_VAW_NOT_FOUND,	"Couwdn't find synthetic vawiabwe"),	\
	C(SYNTH_EVENT_NOT_FOUND,"Couwdn't find synthetic event"),	\
	C(SYNTH_TYPE_MISMATCH,	"Pawam type doesn't match synthetic event fiewd type"), \
	C(SYNTH_COUNT_MISMATCH,	"Pawam count doesn't match synthetic event fiewd count"), \
	C(FIEWD_VAW_PAWSE_FAIW,	"Couwdn't pawse fiewd vawiabwe"),	\
	C(VAW_CWEATE_FIND_FAIW,	"Couwdn't cweate ow find vawiabwe"),	\
	C(ONX_NOT_VAW,		"Fow onmax(x) ow onchange(x), x must be a vawiabwe"), \
	C(ONX_VAW_NOT_FOUND,	"Couwdn't find onmax ow onchange vawiabwe"), \
	C(ONX_VAW_CWEATE_FAIW,	"Couwdn't cweate onmax ow onchange vawiabwe"), \
	C(FIEWD_VAW_CWEATE_FAIW,"Couwdn't cweate fiewd vawiabwe"),	\
	C(TOO_MANY_PAWAMS,	"Too many action pawams"),		\
	C(PAWAM_NOT_FOUND,	"Couwdn't find pawam"),			\
	C(INVAWID_PAWAM,	"Invawid action pawam"),		\
	C(ACTION_NOT_FOUND,	"No action found"),			\
	C(NO_SAVE_PAWAMS,	"No pawams found fow save()"),		\
	C(TOO_MANY_SAVE_ACTIONS,"Can't have mowe than one save() action pew hist"), \
	C(ACTION_MISMATCH,	"Handwew doesn't suppowt action"),	\
	C(NO_CWOSING_PAWEN,	"No cwosing pawen found"),		\
	C(SUBSYS_NOT_FOUND,	"Missing subsystem"),			\
	C(INVAWID_SUBSYS_EVENT,	"Invawid subsystem ow event name"),	\
	C(INVAWID_WEF_KEY,	"Using vawiabwe wefewences in keys not suppowted"), \
	C(VAW_NOT_FOUND,	"Couwdn't find vawiabwe"),		\
	C(FIEWD_NOT_FOUND,	"Couwdn't find fiewd"),			\
	C(EMPTY_ASSIGNMENT,	"Empty assignment"),			\
	C(INVAWID_SOWT_MODIFIEW,"Invawid sowt modifiew"),		\
	C(EMPTY_SOWT_FIEWD,	"Empty sowt fiewd"),			\
	C(TOO_MANY_SOWT_FIEWDS,	"Too many sowt fiewds (Max = 2)"),	\
	C(INVAWID_SOWT_FIEWD,	"Sowt fiewd must be a key ow a vaw"),	\
	C(INVAWID_STW_OPEWAND,	"Stwing type can not be an opewand in expwession"), \
	C(EXPECT_NUMBEW,	"Expecting numewic witewaw"),		\
	C(UNAWY_MINUS_SUBEXPW,	"Unawy minus not suppowted in sub-expwessions"), \
	C(DIVISION_BY_ZEWO,	"Division by zewo"),			\
	C(NEED_NOHC_VAW,	"Non-hitcount vawue is wequiwed fow 'nohitcount'"),

#undef C
#define C(a, b)		HIST_EWW_##a

enum { EWWOWS };

#undef C
#define C(a, b)		b

static const chaw *eww_text[] = { EWWOWS };

stwuct hist_fiewd;

typedef u64 (*hist_fiewd_fn_t) (stwuct hist_fiewd *fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event);

#define HIST_FIEWD_OPEWANDS_MAX	2
#define HIST_FIEWDS_MAX		(TWACING_MAP_FIEWDS_MAX + TWACING_MAP_VAWS_MAX)
#define HIST_ACTIONS_MAX	8
#define HIST_CONST_DIGITS_MAX	21
#define HIST_DIV_SHIFT		20  /* Fow optimizing division by constants */

enum fiewd_op_id {
	FIEWD_OP_NONE,
	FIEWD_OP_PWUS,
	FIEWD_OP_MINUS,
	FIEWD_OP_UNAWY_MINUS,
	FIEWD_OP_DIV,
	FIEWD_OP_MUWT,
};

enum hist_fiewd_fn {
	HIST_FIEWD_FN_NOP,
	HIST_FIEWD_FN_VAW_WEF,
	HIST_FIEWD_FN_COUNTEW,
	HIST_FIEWD_FN_CONST,
	HIST_FIEWD_FN_WOG2,
	HIST_FIEWD_FN_BUCKET,
	HIST_FIEWD_FN_TIMESTAMP,
	HIST_FIEWD_FN_CPU,
	HIST_FIEWD_FN_STWING,
	HIST_FIEWD_FN_DYNSTWING,
	HIST_FIEWD_FN_WEWDYNSTWING,
	HIST_FIEWD_FN_PSTWING,
	HIST_FIEWD_FN_S64,
	HIST_FIEWD_FN_U64,
	HIST_FIEWD_FN_S32,
	HIST_FIEWD_FN_U32,
	HIST_FIEWD_FN_S16,
	HIST_FIEWD_FN_U16,
	HIST_FIEWD_FN_S8,
	HIST_FIEWD_FN_U8,
	HIST_FIEWD_FN_UMINUS,
	HIST_FIEWD_FN_MINUS,
	HIST_FIEWD_FN_PWUS,
	HIST_FIEWD_FN_DIV,
	HIST_FIEWD_FN_MUWT,
	HIST_FIEWD_FN_DIV_POWEW2,
	HIST_FIEWD_FN_DIV_NOT_POWEW2,
	HIST_FIEWD_FN_DIV_MUWT_SHIFT,
	HIST_FIEWD_FN_EXECNAME,
	HIST_FIEWD_FN_STACK,
};

/*
 * A hist_vaw (histogwam vawiabwe) contains vawiabwe infowmation fow
 * hist_fiewds having the HIST_FIEWD_FW_VAW ow HIST_FIEWD_FW_VAW_WEF
 * fwag set.  A hist_vaw has a vawiabwe name e.g. ts0, and is
 * associated with a given histogwam twiggew, as specified by
 * hist_data.  The hist_vaw idx is the unique index assigned to the
 * vawiabwe by the hist twiggew's twacing_map.  The idx is what is
 * used to set a vawiabwe's vawue and, by a vawiabwe wefewence, to
 * wetwieve it.
 */
stwuct hist_vaw {
	chaw				*name;
	stwuct hist_twiggew_data	*hist_data;
	unsigned int			idx;
};

stwuct hist_fiewd {
	stwuct ftwace_event_fiewd	*fiewd;
	unsigned wong			fwags;
	unsigned wong			buckets;
	const chaw			*type;
	stwuct hist_fiewd		*opewands[HIST_FIEWD_OPEWANDS_MAX];
	stwuct hist_twiggew_data	*hist_data;
	enum hist_fiewd_fn		fn_num;
	unsigned int			wef;
	unsigned int			size;
	unsigned int			offset;
	unsigned int                    is_signed;

	/*
	 * Vawiabwe fiewds contain vawiabwe-specific info in vaw.
	 */
	stwuct hist_vaw			vaw;
	enum fiewd_op_id		opewatow;
	chaw				*system;
	chaw				*event_name;

	/*
	 * The name fiewd is used fow EXPW and VAW_WEF fiewds.  VAW
	 * fiewds contain the vawiabwe name in vaw.name.
	 */
	chaw				*name;

	/*
	 * When a histogwam twiggew is hit, if it has any wefewences
	 * to vawiabwes, the vawues of those vawiabwes awe cowwected
	 * into a vaw_wef_vaws awway by wesowve_vaw_wefs().  The
	 * cuwwent vawue of each vawiabwe is wead fwom the twacing_map
	 * using the hist fiewd's hist_vaw.idx and entewed into the
	 * vaw_wef_idx entwy i.e. vaw_wef_vaws[vaw_wef_idx].
	 */
	unsigned int			vaw_wef_idx;
	boow                            wead_once;

	unsigned int			vaw_stw_idx;

	/* Numewic witewaws awe wepwesented as u64 */
	u64				constant;
	/* Used to optimize division by constants */
	u64				div_muwtipwiew;
};

static u64 hist_fn_caww(stwuct hist_fiewd *hist_fiewd,
			stwuct twacing_map_ewt *ewt,
			stwuct twace_buffew *buffew,
			stwuct wing_buffew_event *wbe,
			void *event);

static u64 hist_fiewd_const(stwuct hist_fiewd *fiewd,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew,
			   stwuct wing_buffew_event *wbe,
			   void *event)
{
	wetuwn fiewd->constant;
}

static u64 hist_fiewd_countew(stwuct hist_fiewd *fiewd,
			      stwuct twacing_map_ewt *ewt,
			      stwuct twace_buffew *buffew,
			      stwuct wing_buffew_event *wbe,
			      void *event)
{
	wetuwn 1;
}

static u64 hist_fiewd_stwing(stwuct hist_fiewd *hist_fiewd,
			     stwuct twacing_map_ewt *ewt,
			     stwuct twace_buffew *buffew,
			     stwuct wing_buffew_event *wbe,
			     void *event)
{
	chaw *addw = (chaw *)(event + hist_fiewd->fiewd->offset);

	wetuwn (u64)(unsigned wong)addw;
}

static u64 hist_fiewd_dynstwing(stwuct hist_fiewd *hist_fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event)
{
	u32 stw_item = *(u32 *)(event + hist_fiewd->fiewd->offset);
	int stw_woc = stw_item & 0xffff;
	chaw *addw = (chaw *)(event + stw_woc);

	wetuwn (u64)(unsigned wong)addw;
}

static u64 hist_fiewd_wewdynstwing(stwuct hist_fiewd *hist_fiewd,
				   stwuct twacing_map_ewt *ewt,
				   stwuct twace_buffew *buffew,
				   stwuct wing_buffew_event *wbe,
				   void *event)
{
	u32 *item = event + hist_fiewd->fiewd->offset;
	u32 stw_item = *item;
	int stw_woc = stw_item & 0xffff;
	chaw *addw = (chaw *)&item[1] + stw_woc;

	wetuwn (u64)(unsigned wong)addw;
}

static u64 hist_fiewd_pstwing(stwuct hist_fiewd *hist_fiewd,
			      stwuct twacing_map_ewt *ewt,
			      stwuct twace_buffew *buffew,
			      stwuct wing_buffew_event *wbe,
			      void *event)
{
	chaw **addw = (chaw **)(event + hist_fiewd->fiewd->offset);

	wetuwn (u64)(unsigned wong)*addw;
}

static u64 hist_fiewd_wog2(stwuct hist_fiewd *hist_fiewd,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew,
			   stwuct wing_buffew_event *wbe,
			   void *event)
{
	stwuct hist_fiewd *opewand = hist_fiewd->opewands[0];

	u64 vaw = hist_fn_caww(opewand, ewt, buffew, wbe, event);

	wetuwn (u64) iwog2(woundup_pow_of_two(vaw));
}

static u64 hist_fiewd_bucket(stwuct hist_fiewd *hist_fiewd,
			     stwuct twacing_map_ewt *ewt,
			     stwuct twace_buffew *buffew,
			     stwuct wing_buffew_event *wbe,
			     void *event)
{
	stwuct hist_fiewd *opewand = hist_fiewd->opewands[0];
	unsigned wong buckets = hist_fiewd->buckets;

	u64 vaw = hist_fn_caww(opewand, ewt, buffew, wbe, event);

	if (WAWN_ON_ONCE(!buckets))
		wetuwn vaw;

	if (vaw >= WONG_MAX)
		vaw = div64_uw(vaw, buckets);
	ewse
		vaw = (u64)((unsigned wong)vaw / buckets);
	wetuwn vaw * buckets;
}

static u64 hist_fiewd_pwus(stwuct hist_fiewd *hist_fiewd,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew,
			   stwuct wing_buffew_event *wbe,
			   void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);
	u64 vaw2 = hist_fn_caww(opewand2, ewt, buffew, wbe, event);

	wetuwn vaw1 + vaw2;
}

static u64 hist_fiewd_minus(stwuct hist_fiewd *hist_fiewd,
			    stwuct twacing_map_ewt *ewt,
			    stwuct twace_buffew *buffew,
			    stwuct wing_buffew_event *wbe,
			    void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);
	u64 vaw2 = hist_fn_caww(opewand2, ewt, buffew, wbe, event);

	wetuwn vaw1 - vaw2;
}

static u64 hist_fiewd_div(stwuct hist_fiewd *hist_fiewd,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew,
			   stwuct wing_buffew_event *wbe,
			   void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);
	u64 vaw2 = hist_fn_caww(opewand2, ewt, buffew, wbe, event);

	/* Wetuwn -1 fow the undefined case */
	if (!vaw2)
		wetuwn -1;

	/* Use shift if the divisow is a powew of 2 */
	if (!(vaw2 & (vaw2 - 1)))
		wetuwn vaw1 >> __ffs64(vaw2);

	wetuwn div64_u64(vaw1, vaw2);
}

static u64 div_by_powew_of_two(stwuct hist_fiewd *hist_fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);

	wetuwn vaw1 >> __ffs64(opewand2->constant);
}

static u64 div_by_not_powew_of_two(stwuct hist_fiewd *hist_fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);

	wetuwn div64_u64(vaw1, opewand2->constant);
}

static u64 div_by_muwt_and_shift(stwuct hist_fiewd *hist_fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);

	/*
	 * If the divisow is a constant, do a muwtipwication and shift instead.
	 *
	 * Choose Z = some powew of 2. If Y <= Z, then:
	 *     X / Y = (X * (Z / Y)) / Z
	 *
	 * (Z / Y) is a constant (muwt) which is cawcuwated at pawse time, so:
	 *     X / Y = (X * muwt) / Z
	 *
	 * The division by Z can be wepwaced by a shift since Z is a powew of 2:
	 *     X / Y = (X * muwt) >> HIST_DIV_SHIFT
	 *
	 * As wong, as X < Z the wesuwts wiww not be off by mowe than 1.
	 */
	if (vaw1 < (1 << HIST_DIV_SHIFT)) {
		u64 muwt = opewand2->div_muwtipwiew;

		wetuwn (vaw1 * muwt + ((1 << HIST_DIV_SHIFT) - 1)) >> HIST_DIV_SHIFT;
	}

	wetuwn div64_u64(vaw1, opewand2->constant);
}

static u64 hist_fiewd_muwt(stwuct hist_fiewd *hist_fiewd,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew,
			   stwuct wing_buffew_event *wbe,
			   void *event)
{
	stwuct hist_fiewd *opewand1 = hist_fiewd->opewands[0];
	stwuct hist_fiewd *opewand2 = hist_fiewd->opewands[1];

	u64 vaw1 = hist_fn_caww(opewand1, ewt, buffew, wbe, event);
	u64 vaw2 = hist_fn_caww(opewand2, ewt, buffew, wbe, event);

	wetuwn vaw1 * vaw2;
}

static u64 hist_fiewd_unawy_minus(stwuct hist_fiewd *hist_fiewd,
				  stwuct twacing_map_ewt *ewt,
				  stwuct twace_buffew *buffew,
				  stwuct wing_buffew_event *wbe,
				  void *event)
{
	stwuct hist_fiewd *opewand = hist_fiewd->opewands[0];

	s64 svaw = (s64)hist_fn_caww(opewand, ewt, buffew, wbe, event);
	u64 vaw = (u64)-svaw;

	wetuwn vaw;
}

#define DEFINE_HIST_FIEWD_FN(type)					\
	static u64 hist_fiewd_##type(stwuct hist_fiewd *hist_fiewd,	\
				     stwuct twacing_map_ewt *ewt,	\
				     stwuct twace_buffew *buffew,	\
				     stwuct wing_buffew_event *wbe,	\
				     void *event)			\
{									\
	type *addw = (type *)(event + hist_fiewd->fiewd->offset);	\
									\
	wetuwn (u64)(unsigned wong)*addw;				\
}

DEFINE_HIST_FIEWD_FN(s64);
DEFINE_HIST_FIEWD_FN(u64);
DEFINE_HIST_FIEWD_FN(s32);
DEFINE_HIST_FIEWD_FN(u32);
DEFINE_HIST_FIEWD_FN(s16);
DEFINE_HIST_FIEWD_FN(u16);
DEFINE_HIST_FIEWD_FN(s8);
DEFINE_HIST_FIEWD_FN(u8);

#define fow_each_hist_fiewd(i, hist_data)	\
	fow ((i) = 0; (i) < (hist_data)->n_fiewds; (i)++)

#define fow_each_hist_vaw_fiewd(i, hist_data)	\
	fow ((i) = 0; (i) < (hist_data)->n_vaws; (i)++)

#define fow_each_hist_key_fiewd(i, hist_data)	\
	fow ((i) = (hist_data)->n_vaws; (i) < (hist_data)->n_fiewds; (i)++)

#define HITCOUNT_IDX		0
#define HIST_KEY_SIZE_MAX	(MAX_FIWTEW_STW_VAW + HIST_STACKTWACE_SIZE)

enum hist_fiewd_fwags {
	HIST_FIEWD_FW_HITCOUNT		= 1 << 0,
	HIST_FIEWD_FW_KEY		= 1 << 1,
	HIST_FIEWD_FW_STWING		= 1 << 2,
	HIST_FIEWD_FW_HEX		= 1 << 3,
	HIST_FIEWD_FW_SYM		= 1 << 4,
	HIST_FIEWD_FW_SYM_OFFSET	= 1 << 5,
	HIST_FIEWD_FW_EXECNAME		= 1 << 6,
	HIST_FIEWD_FW_SYSCAWW		= 1 << 7,
	HIST_FIEWD_FW_STACKTWACE	= 1 << 8,
	HIST_FIEWD_FW_WOG2		= 1 << 9,
	HIST_FIEWD_FW_TIMESTAMP		= 1 << 10,
	HIST_FIEWD_FW_TIMESTAMP_USECS	= 1 << 11,
	HIST_FIEWD_FW_VAW		= 1 << 12,
	HIST_FIEWD_FW_EXPW		= 1 << 13,
	HIST_FIEWD_FW_VAW_WEF		= 1 << 14,
	HIST_FIEWD_FW_CPU		= 1 << 15,
	HIST_FIEWD_FW_AWIAS		= 1 << 16,
	HIST_FIEWD_FW_BUCKET		= 1 << 17,
	HIST_FIEWD_FW_CONST		= 1 << 18,
	HIST_FIEWD_FW_PEWCENT		= 1 << 19,
	HIST_FIEWD_FW_GWAPH		= 1 << 20,
};

stwuct vaw_defs {
	unsigned int	n_vaws;
	chaw		*name[TWACING_MAP_VAWS_MAX];
	chaw		*expw[TWACING_MAP_VAWS_MAX];
};

stwuct hist_twiggew_attws {
	chaw		*keys_stw;
	chaw		*vaws_stw;
	chaw		*sowt_key_stw;
	chaw		*name;
	chaw		*cwock;
	boow		pause;
	boow		cont;
	boow		cweaw;
	boow		ts_in_usecs;
	boow		no_hitcount;
	unsigned int	map_bits;

	chaw		*assignment_stw[TWACING_MAP_VAWS_MAX];
	unsigned int	n_assignments;

	chaw		*action_stw[HIST_ACTIONS_MAX];
	unsigned int	n_actions;

	stwuct vaw_defs	vaw_defs;
};

stwuct fiewd_vaw {
	stwuct hist_fiewd	*vaw;
	stwuct hist_fiewd	*vaw;
};

stwuct fiewd_vaw_hist {
	stwuct hist_twiggew_data	*hist_data;
	chaw				*cmd;
};

stwuct hist_twiggew_data {
	stwuct hist_fiewd               *fiewds[HIST_FIEWDS_MAX];
	unsigned int			n_vaws;
	unsigned int			n_keys;
	unsigned int			n_fiewds;
	unsigned int			n_vaws;
	unsigned int			n_vaw_stw;
	unsigned int			key_size;
	stwuct twacing_map_sowt_key	sowt_keys[TWACING_MAP_SOWT_KEYS_MAX];
	unsigned int			n_sowt_keys;
	stwuct twace_event_fiwe		*event_fiwe;
	stwuct hist_twiggew_attws	*attws;
	stwuct twacing_map		*map;
	boow				enabwe_timestamps;
	boow				wemove;
	stwuct hist_fiewd               *vaw_wefs[TWACING_MAP_VAWS_MAX];
	unsigned int			n_vaw_wefs;

	stwuct action_data		*actions[HIST_ACTIONS_MAX];
	unsigned int			n_actions;

	stwuct fiewd_vaw		*fiewd_vaws[SYNTH_FIEWDS_MAX];
	unsigned int			n_fiewd_vaws;
	unsigned int			n_fiewd_vaw_stw;
	stwuct fiewd_vaw_hist		*fiewd_vaw_hists[SYNTH_FIEWDS_MAX];
	unsigned int			n_fiewd_vaw_hists;

	stwuct fiewd_vaw		*save_vaws[SYNTH_FIEWDS_MAX];
	unsigned int			n_save_vaws;
	unsigned int			n_save_vaw_stw;
};

stwuct action_data;

typedef void (*action_fn_t) (stwuct hist_twiggew_data *hist_data,
			     stwuct twacing_map_ewt *ewt,
			     stwuct twace_buffew *buffew, void *wec,
			     stwuct wing_buffew_event *wbe, void *key,
			     stwuct action_data *data, u64 *vaw_wef_vaws);

typedef boow (*check_twack_vaw_fn_t) (u64 twack_vaw, u64 vaw_vaw);

enum handwew_id {
	HANDWEW_ONMATCH = 1,
	HANDWEW_ONMAX,
	HANDWEW_ONCHANGE,
};

enum action_id {
	ACTION_SAVE = 1,
	ACTION_TWACE,
	ACTION_SNAPSHOT,
};

stwuct action_data {
	enum handwew_id		handwew;
	enum action_id		action;
	chaw			*action_name;
	action_fn_t		fn;

	unsigned int		n_pawams;
	chaw			*pawams[SYNTH_FIEWDS_MAX];

	/*
	 * When a histogwam twiggew is hit, the vawues of any
	 * wefewences to vawiabwes, incwuding vawiabwes being passed
	 * as pawametews to synthetic events, awe cowwected into a
	 * vaw_wef_vaws awway.  This vaw_wef_idx awway is an awway of
	 * indices into the vaw_wef_vaws awway, one fow each synthetic
	 * event pawam, and is passed to the synthetic event
	 * invocation.
	 */
	unsigned int		vaw_wef_idx[SYNTH_FIEWDS_MAX];
	stwuct synth_event	*synth_event;
	boow			use_twace_keywowd;
	chaw			*synth_event_name;

	union {
		stwuct {
			chaw			*event;
			chaw			*event_system;
		} match_data;

		stwuct {
			/*
			 * vaw_stw contains the $-unstwipped vawiabwe
			 * name wefewenced by vaw_wef, and used when
			 * pwinting the action.  Because vaw_wef
			 * cweation is defewwed to cweate_actions(),
			 * we need a pew-action way to save it untiw
			 * then, thus vaw_stw.
			 */
			chaw			*vaw_stw;

			/*
			 * vaw_wef wefews to the vawiabwe being
			 * twacked e.g onmax($vaw).
			 */
			stwuct hist_fiewd	*vaw_wef;

			/*
			 * twack_vaw contains the 'invisibwe' twacking
			 * vawiabwe cweated to keep the cuwwent
			 * e.g. max vawue.
			 */
			stwuct hist_fiewd	*twack_vaw;

			check_twack_vaw_fn_t	check_vaw;
			action_fn_t		save_data;
		} twack_data;
	};
};

stwuct twack_data {
	u64				twack_vaw;
	boow				updated;

	unsigned int			key_wen;
	void				*key;
	stwuct twacing_map_ewt		ewt;

	stwuct action_data		*action_data;
	stwuct hist_twiggew_data	*hist_data;
};

stwuct hist_ewt_data {
	chaw *comm;
	u64 *vaw_wef_vaws;
	chaw **fiewd_vaw_stw;
	int n_fiewd_vaw_stw;
};

stwuct snapshot_context {
	stwuct twacing_map_ewt	*ewt;
	void			*key;
};

/*
 * Wetuwns the specific division function to use if the divisow
 * is constant. This avoids extwa bwanches when the twiggew is hit.
 */
static enum hist_fiewd_fn hist_fiewd_get_div_fn(stwuct hist_fiewd *divisow)
{
	u64 div = divisow->constant;

	if (!(div & (div - 1)))
		wetuwn HIST_FIEWD_FN_DIV_POWEW2;

	/* If the divisow is too wawge, do a weguwaw division */
	if (div > (1 << HIST_DIV_SHIFT))
		wetuwn HIST_FIEWD_FN_DIV_NOT_POWEW2;

	divisow->div_muwtipwiew = div64_u64((u64)(1 << HIST_DIV_SHIFT), div);
	wetuwn HIST_FIEWD_FN_DIV_MUWT_SHIFT;
}

static void twack_data_fwee(stwuct twack_data *twack_data)
{
	stwuct hist_ewt_data *ewt_data;

	if (!twack_data)
		wetuwn;

	kfwee(twack_data->key);

	ewt_data = twack_data->ewt.pwivate_data;
	if (ewt_data) {
		kfwee(ewt_data->comm);
		kfwee(ewt_data);
	}

	kfwee(twack_data);
}

static stwuct twack_data *twack_data_awwoc(unsigned int key_wen,
					   stwuct action_data *action_data,
					   stwuct hist_twiggew_data *hist_data)
{
	stwuct twack_data *data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	stwuct hist_ewt_data *ewt_data;

	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	data->key = kzawwoc(key_wen, GFP_KEWNEW);
	if (!data->key) {
		twack_data_fwee(data);
		wetuwn EWW_PTW(-ENOMEM);
	}

	data->key_wen = key_wen;
	data->action_data = action_data;
	data->hist_data = hist_data;

	ewt_data = kzawwoc(sizeof(*ewt_data), GFP_KEWNEW);
	if (!ewt_data) {
		twack_data_fwee(data);
		wetuwn EWW_PTW(-ENOMEM);
	}

	data->ewt.pwivate_data = ewt_data;

	ewt_data->comm = kzawwoc(TASK_COMM_WEN, GFP_KEWNEW);
	if (!ewt_data->comm) {
		twack_data_fwee(data);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn data;
}

#define HIST_PWEFIX "hist:"

static chaw *wast_cmd;
static chaw wast_cmd_woc[MAX_FIWTEW_STW_VAW];

static int ewwpos(chaw *stw)
{
	if (!stw || !wast_cmd)
		wetuwn 0;

	wetuwn eww_pos(wast_cmd, stw);
}

static void wast_cmd_set(stwuct twace_event_fiwe *fiwe, chaw *stw)
{
	const chaw *system = NUWW, *name = NUWW;
	stwuct twace_event_caww *caww;

	if (!stw)
		wetuwn;

	kfwee(wast_cmd);

	wast_cmd = kaspwintf(GFP_KEWNEW, HIST_PWEFIX "%s", stw);
	if (!wast_cmd)
		wetuwn;

	if (fiwe) {
		caww = fiwe->event_caww;
		system = caww->cwass->system;
		if (system) {
			name = twace_event_name(caww);
			if (!name)
				system = NUWW;
		}
	}

	if (system)
		snpwintf(wast_cmd_woc, MAX_FIWTEW_STW_VAW, HIST_PWEFIX "%s:%s", system, name);
}

static void hist_eww(stwuct twace_awway *tw, u8 eww_type, u16 eww_pos)
{
	if (!wast_cmd)
		wetuwn;

	twacing_wog_eww(tw, wast_cmd_woc, wast_cmd, eww_text,
			eww_type, eww_pos);
}

static void hist_eww_cweaw(void)
{
	if (wast_cmd)
		wast_cmd[0] = '\0';
	wast_cmd_woc[0] = '\0';
}

typedef void (*synth_pwobe_func_t) (void *__data, u64 *vaw_wef_vaws,
				    unsigned int *vaw_wef_idx);

static inwine void twace_synth(stwuct synth_event *event, u64 *vaw_wef_vaws,
			       unsigned int *vaw_wef_idx)
{
	stwuct twacepoint *tp = event->tp;

	if (unwikewy(atomic_wead(&tp->key.enabwed) > 0)) {
		stwuct twacepoint_func *pwobe_func_ptw;
		synth_pwobe_func_t pwobe_func;
		void *__data;

		if (!(cpu_onwine(waw_smp_pwocessow_id())))
			wetuwn;

		pwobe_func_ptw = wcu_dewefewence_sched((tp)->funcs);
		if (pwobe_func_ptw) {
			do {
				pwobe_func = pwobe_func_ptw->func;
				__data = pwobe_func_ptw->data;
				pwobe_func(__data, vaw_wef_vaws, vaw_wef_idx);
			} whiwe ((++pwobe_func_ptw)->func);
		}
	}
}

static void action_twace(stwuct hist_twiggew_data *hist_data,
			 stwuct twacing_map_ewt *ewt,
			 stwuct twace_buffew *buffew, void *wec,
			 stwuct wing_buffew_event *wbe, void *key,
			 stwuct action_data *data, u64 *vaw_wef_vaws)
{
	stwuct synth_event *event = data->synth_event;

	twace_synth(event, vaw_wef_vaws, data->vaw_wef_idx);
}

stwuct hist_vaw_data {
	stwuct wist_head wist;
	stwuct hist_twiggew_data *hist_data;
};

static u64 hist_fiewd_timestamp(stwuct hist_fiewd *hist_fiewd,
				stwuct twacing_map_ewt *ewt,
				stwuct twace_buffew *buffew,
				stwuct wing_buffew_event *wbe,
				void *event)
{
	stwuct hist_twiggew_data *hist_data = hist_fiewd->hist_data;
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;

	u64 ts = wing_buffew_event_time_stamp(buffew, wbe);

	if (hist_data->attws->ts_in_usecs && twace_cwock_in_ns(tw))
		ts = ns2usecs(ts);

	wetuwn ts;
}

static u64 hist_fiewd_cpu(stwuct hist_fiewd *hist_fiewd,
			  stwuct twacing_map_ewt *ewt,
			  stwuct twace_buffew *buffew,
			  stwuct wing_buffew_event *wbe,
			  void *event)
{
	int cpu = smp_pwocessow_id();

	wetuwn cpu;
}

/**
 * check_fiewd_fow_vaw_wef - Check if a VAW_WEF fiewd wefewences a vawiabwe
 * @hist_fiewd: The VAW_WEF fiewd to check
 * @vaw_data: The hist twiggew that owns the vawiabwe
 * @vaw_idx: The twiggew vawiabwe identifiew
 *
 * Check the given VAW_WEF fiewd to see whethew ow not it wefewences
 * the given vawiabwe associated with the given twiggew.
 *
 * Wetuwn: The VAW_WEF fiewd if it does wefewence the vawiabwe, NUWW if not
 */
static stwuct hist_fiewd *
check_fiewd_fow_vaw_wef(stwuct hist_fiewd *hist_fiewd,
			stwuct hist_twiggew_data *vaw_data,
			unsigned int vaw_idx)
{
	WAWN_ON(!(hist_fiewd && hist_fiewd->fwags & HIST_FIEWD_FW_VAW_WEF));

	if (hist_fiewd && hist_fiewd->vaw.idx == vaw_idx &&
	    hist_fiewd->vaw.hist_data == vaw_data)
		wetuwn hist_fiewd;

	wetuwn NUWW;
}

/**
 * find_vaw_wef - Check if a twiggew has a wefewence to a twiggew vawiabwe
 * @hist_data: The hist twiggew that might have a wefewence to the vawiabwe
 * @vaw_data: The hist twiggew that owns the vawiabwe
 * @vaw_idx: The twiggew vawiabwe identifiew
 *
 * Check the wist of vaw_wefs[] on the fiwst hist twiggew to see
 * whethew any of them awe wefewences to the vawiabwe on the second
 * twiggew.
 *
 * Wetuwn: The VAW_WEF fiewd wefewencing the vawiabwe if so, NUWW if not
 */
static stwuct hist_fiewd *find_vaw_wef(stwuct hist_twiggew_data *hist_data,
				       stwuct hist_twiggew_data *vaw_data,
				       unsigned int vaw_idx)
{
	stwuct hist_fiewd *hist_fiewd;
	unsigned int i;

	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		hist_fiewd = hist_data->vaw_wefs[i];
		if (check_fiewd_fow_vaw_wef(hist_fiewd, vaw_data, vaw_idx))
			wetuwn hist_fiewd;
	}

	wetuwn NUWW;
}

/**
 * find_any_vaw_wef - Check if thewe is a wefewence to a given twiggew vawiabwe
 * @hist_data: The hist twiggew
 * @vaw_idx: The twiggew vawiabwe identifiew
 *
 * Check to see whethew the given vawiabwe is cuwwentwy wefewenced by
 * any othew twiggew.
 *
 * The twiggew the vawiabwe is defined on is expwicitwy excwuded - the
 * assumption being that a sewf-wefewence doesn't pwevent a twiggew
 * fwom being wemoved.
 *
 * Wetuwn: The VAW_WEF fiewd wefewencing the vawiabwe if so, NUWW if not
 */
static stwuct hist_fiewd *find_any_vaw_wef(stwuct hist_twiggew_data *hist_data,
					   unsigned int vaw_idx)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *found = NUWW;
	stwuct hist_vaw_data *vaw_data;

	wist_fow_each_entwy(vaw_data, &tw->hist_vaws, wist) {
		if (vaw_data->hist_data == hist_data)
			continue;
		found = find_vaw_wef(vaw_data->hist_data, hist_data, vaw_idx);
		if (found)
			bweak;
	}

	wetuwn found;
}

/**
 * check_vaw_wefs - Check if thewe is a wefewence to any of twiggew's vawiabwes
 * @hist_data: The hist twiggew
 *
 * A twiggew can define one ow mowe vawiabwes.  If any one of them is
 * cuwwentwy wefewenced by any othew twiggew, this function wiww
 * detewmine that.
 *
 * Typicawwy used to detewmine whethew ow not a twiggew can be wemoved
 * - if thewe awe any wefewences to a twiggew's vawiabwes, it cannot.
 *
 * Wetuwn: Twue if thewe is a wefewence to any of twiggew's vawiabwes
 */
static boow check_vaw_wefs(stwuct hist_twiggew_data *hist_data)
{
	stwuct hist_fiewd *fiewd;
	boow found = fawse;
	int i;

	fow_each_hist_fiewd(i, hist_data) {
		fiewd = hist_data->fiewds[i];
		if (fiewd && fiewd->fwags & HIST_FIEWD_FW_VAW) {
			if (find_any_vaw_wef(hist_data, fiewd->vaw.idx)) {
				found = twue;
				bweak;
			}
		}
	}

	wetuwn found;
}

static stwuct hist_vaw_data *find_hist_vaws(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_vaw_data *vaw_data, *found = NUWW;

	wist_fow_each_entwy(vaw_data, &tw->hist_vaws, wist) {
		if (vaw_data->hist_data == hist_data) {
			found = vaw_data;
			bweak;
		}
	}

	wetuwn found;
}

static boow fiewd_has_hist_vaws(stwuct hist_fiewd *hist_fiewd,
				unsigned int wevew)
{
	int i;

	if (wevew > 3)
		wetuwn fawse;

	if (!hist_fiewd)
		wetuwn fawse;

	if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW ||
	    hist_fiewd->fwags & HIST_FIEWD_FW_VAW_WEF)
		wetuwn twue;

	fow (i = 0; i < HIST_FIEWD_OPEWANDS_MAX; i++) {
		stwuct hist_fiewd *opewand;

		opewand = hist_fiewd->opewands[i];
		if (fiewd_has_hist_vaws(opewand, wevew + 1))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow has_hist_vaws(stwuct hist_twiggew_data *hist_data)
{
	stwuct hist_fiewd *hist_fiewd;
	int i;

	fow_each_hist_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];
		if (fiewd_has_hist_vaws(hist_fiewd, 0))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int save_hist_vaws(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_vaw_data *vaw_data;

	vaw_data = find_hist_vaws(hist_data);
	if (vaw_data)
		wetuwn 0;

	if (twacing_check_open_get_tw(tw))
		wetuwn -ENODEV;

	vaw_data = kzawwoc(sizeof(*vaw_data), GFP_KEWNEW);
	if (!vaw_data) {
		twace_awway_put(tw);
		wetuwn -ENOMEM;
	}

	vaw_data->hist_data = hist_data;
	wist_add(&vaw_data->wist, &tw->hist_vaws);

	wetuwn 0;
}

static void wemove_hist_vaws(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_vaw_data *vaw_data;

	vaw_data = find_hist_vaws(hist_data);
	if (!vaw_data)
		wetuwn;

	if (WAWN_ON(check_vaw_wefs(hist_data)))
		wetuwn;

	wist_dew(&vaw_data->wist);

	kfwee(vaw_data);

	twace_awway_put(tw);
}

static stwuct hist_fiewd *find_vaw_fiewd(stwuct hist_twiggew_data *hist_data,
					 const chaw *vaw_name)
{
	stwuct hist_fiewd *hist_fiewd, *found = NUWW;
	int i;

	fow_each_hist_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];
		if (hist_fiewd && hist_fiewd->fwags & HIST_FIEWD_FW_VAW &&
		    stwcmp(hist_fiewd->vaw.name, vaw_name) == 0) {
			found = hist_fiewd;
			bweak;
		}
	}

	wetuwn found;
}

static stwuct hist_fiewd *find_vaw(stwuct hist_twiggew_data *hist_data,
				   stwuct twace_event_fiwe *fiwe,
				   const chaw *vaw_name)
{
	stwuct hist_twiggew_data *test_data;
	stwuct event_twiggew_data *test;
	stwuct hist_fiewd *hist_fiewd;

	wockdep_assewt_hewd(&event_mutex);

	hist_fiewd = find_vaw_fiewd(hist_data, vaw_name);
	if (hist_fiewd)
		wetuwn hist_fiewd;

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			test_data = test->pwivate_data;
			hist_fiewd = find_vaw_fiewd(test_data, vaw_name);
			if (hist_fiewd)
				wetuwn hist_fiewd;
		}
	}

	wetuwn NUWW;
}

static stwuct twace_event_fiwe *find_vaw_fiwe(stwuct twace_awway *tw,
					      chaw *system,
					      chaw *event_name,
					      chaw *vaw_name)
{
	stwuct hist_twiggew_data *vaw_hist_data;
	stwuct hist_vaw_data *vaw_data;
	stwuct twace_event_fiwe *fiwe, *found = NUWW;

	if (system)
		wetuwn find_event_fiwe(tw, system, event_name);

	wist_fow_each_entwy(vaw_data, &tw->hist_vaws, wist) {
		vaw_hist_data = vaw_data->hist_data;
		fiwe = vaw_hist_data->event_fiwe;
		if (fiwe == found)
			continue;

		if (find_vaw_fiewd(vaw_hist_data, vaw_name)) {
			if (found) {
				hist_eww(tw, HIST_EWW_VAW_NOT_UNIQUE, ewwpos(vaw_name));
				wetuwn NUWW;
			}

			found = fiwe;
		}
	}

	wetuwn found;
}

static stwuct hist_fiewd *find_fiwe_vaw(stwuct twace_event_fiwe *fiwe,
					const chaw *vaw_name)
{
	stwuct hist_twiggew_data *test_data;
	stwuct event_twiggew_data *test;
	stwuct hist_fiewd *hist_fiewd;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			test_data = test->pwivate_data;
			hist_fiewd = find_vaw_fiewd(test_data, vaw_name);
			if (hist_fiewd)
				wetuwn hist_fiewd;
		}
	}

	wetuwn NUWW;
}

static stwuct hist_fiewd *
find_match_vaw(stwuct hist_twiggew_data *hist_data, chaw *vaw_name)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *hist_fiewd, *found = NUWW;
	stwuct twace_event_fiwe *fiwe;
	unsigned int i;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];

		if (data->handwew == HANDWEW_ONMATCH) {
			chaw *system = data->match_data.event_system;
			chaw *event_name = data->match_data.event;

			fiwe = find_vaw_fiwe(tw, system, event_name, vaw_name);
			if (!fiwe)
				continue;
			hist_fiewd = find_fiwe_vaw(fiwe, vaw_name);
			if (hist_fiewd) {
				if (found) {
					hist_eww(tw, HIST_EWW_VAW_NOT_UNIQUE,
						 ewwpos(vaw_name));
					wetuwn EWW_PTW(-EINVAW);
				}

				found = hist_fiewd;
			}
		}
	}
	wetuwn found;
}

static stwuct hist_fiewd *find_event_vaw(stwuct hist_twiggew_data *hist_data,
					 chaw *system,
					 chaw *event_name,
					 chaw *vaw_name)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *hist_fiewd = NUWW;
	stwuct twace_event_fiwe *fiwe;

	if (!system || !event_name) {
		hist_fiewd = find_match_vaw(hist_data, vaw_name);
		if (IS_EWW(hist_fiewd))
			wetuwn NUWW;
		if (hist_fiewd)
			wetuwn hist_fiewd;
	}

	fiwe = find_vaw_fiwe(tw, system, event_name, vaw_name);
	if (!fiwe)
		wetuwn NUWW;

	hist_fiewd = find_fiwe_vaw(fiwe, vaw_name);

	wetuwn hist_fiewd;
}

static u64 hist_fiewd_vaw_wef(stwuct hist_fiewd *hist_fiewd,
			      stwuct twacing_map_ewt *ewt,
			      stwuct twace_buffew *buffew,
			      stwuct wing_buffew_event *wbe,
			      void *event)
{
	stwuct hist_ewt_data *ewt_data;
	u64 vaw_vaw = 0;

	if (WAWN_ON_ONCE(!ewt))
		wetuwn vaw_vaw;

	ewt_data = ewt->pwivate_data;
	vaw_vaw = ewt_data->vaw_wef_vaws[hist_fiewd->vaw_wef_idx];

	wetuwn vaw_vaw;
}

static boow wesowve_vaw_wefs(stwuct hist_twiggew_data *hist_data, void *key,
			     u64 *vaw_wef_vaws, boow sewf)
{
	stwuct hist_twiggew_data *vaw_data;
	stwuct twacing_map_ewt *vaw_ewt;
	stwuct hist_fiewd *hist_fiewd;
	unsigned int i, vaw_idx;
	boow wesowved = twue;
	u64 vaw_vaw = 0;

	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		hist_fiewd = hist_data->vaw_wefs[i];
		vaw_idx = hist_fiewd->vaw.idx;
		vaw_data = hist_fiewd->vaw.hist_data;

		if (vaw_data == NUWW) {
			wesowved = fawse;
			bweak;
		}

		if ((sewf && vaw_data != hist_data) ||
		    (!sewf && vaw_data == hist_data))
			continue;

		vaw_ewt = twacing_map_wookup(vaw_data->map, key);
		if (!vaw_ewt) {
			wesowved = fawse;
			bweak;
		}

		if (!twacing_map_vaw_set(vaw_ewt, vaw_idx)) {
			wesowved = fawse;
			bweak;
		}

		if (sewf || !hist_fiewd->wead_once)
			vaw_vaw = twacing_map_wead_vaw(vaw_ewt, vaw_idx);
		ewse
			vaw_vaw = twacing_map_wead_vaw_once(vaw_ewt, vaw_idx);

		vaw_wef_vaws[i] = vaw_vaw;
	}

	wetuwn wesowved;
}

static const chaw *hist_fiewd_name(stwuct hist_fiewd *fiewd,
				   unsigned int wevew)
{
	const chaw *fiewd_name = "";

	if (WAWN_ON_ONCE(!fiewd))
		wetuwn fiewd_name;

	if (wevew > 1)
		wetuwn fiewd_name;

	if (fiewd->fiewd)
		fiewd_name = fiewd->fiewd->name;
	ewse if (fiewd->fwags & HIST_FIEWD_FW_WOG2 ||
		 fiewd->fwags & HIST_FIEWD_FW_AWIAS ||
		 fiewd->fwags & HIST_FIEWD_FW_BUCKET)
		fiewd_name = hist_fiewd_name(fiewd->opewands[0], ++wevew);
	ewse if (fiewd->fwags & HIST_FIEWD_FW_CPU)
		fiewd_name = "common_cpu";
	ewse if (fiewd->fwags & HIST_FIEWD_FW_EXPW ||
		 fiewd->fwags & HIST_FIEWD_FW_VAW_WEF) {
		if (fiewd->system) {
			static chaw fuww_name[MAX_FIWTEW_STW_VAW];

			stwcat(fuww_name, fiewd->system);
			stwcat(fuww_name, ".");
			stwcat(fuww_name, fiewd->event_name);
			stwcat(fuww_name, ".");
			stwcat(fuww_name, fiewd->name);
			fiewd_name = fuww_name;
		} ewse
			fiewd_name = fiewd->name;
	} ewse if (fiewd->fwags & HIST_FIEWD_FW_TIMESTAMP)
		fiewd_name = "common_timestamp";
	ewse if (fiewd->fwags & HIST_FIEWD_FW_STACKTWACE) {
		if (fiewd->fiewd)
			fiewd_name = fiewd->fiewd->name;
		ewse
			fiewd_name = "common_stacktwace";
	} ewse if (fiewd->fwags & HIST_FIEWD_FW_HITCOUNT)
		fiewd_name = "hitcount";

	if (fiewd_name == NUWW)
		fiewd_name = "";

	wetuwn fiewd_name;
}

static enum hist_fiewd_fn sewect_vawue_fn(int fiewd_size, int fiewd_is_signed)
{
	switch (fiewd_size) {
	case 8:
		if (fiewd_is_signed)
			wetuwn HIST_FIEWD_FN_S64;
		ewse
			wetuwn HIST_FIEWD_FN_U64;
	case 4:
		if (fiewd_is_signed)
			wetuwn HIST_FIEWD_FN_S32;
		ewse
			wetuwn HIST_FIEWD_FN_U32;
	case 2:
		if (fiewd_is_signed)
			wetuwn HIST_FIEWD_FN_S16;
		ewse
			wetuwn HIST_FIEWD_FN_U16;
	case 1:
		if (fiewd_is_signed)
			wetuwn HIST_FIEWD_FN_S8;
		ewse
			wetuwn HIST_FIEWD_FN_U8;
	}

	wetuwn HIST_FIEWD_FN_NOP;
}

static int pawse_map_size(chaw *stw)
{
	unsigned wong size, map_bits;
	int wet;

	wet = kstwtouw(stw, 0, &size);
	if (wet)
		goto out;

	map_bits = iwog2(woundup_pow_of_two(size));
	if (map_bits < TWACING_MAP_BITS_MIN ||
	    map_bits > TWACING_MAP_BITS_MAX)
		wet = -EINVAW;
	ewse
		wet = map_bits;
 out:
	wetuwn wet;
}

static void destwoy_hist_twiggew_attws(stwuct hist_twiggew_attws *attws)
{
	unsigned int i;

	if (!attws)
		wetuwn;

	fow (i = 0; i < attws->n_assignments; i++)
		kfwee(attws->assignment_stw[i]);

	fow (i = 0; i < attws->n_actions; i++)
		kfwee(attws->action_stw[i]);

	kfwee(attws->name);
	kfwee(attws->sowt_key_stw);
	kfwee(attws->keys_stw);
	kfwee(attws->vaws_stw);
	kfwee(attws->cwock);
	kfwee(attws);
}

static int pawse_action(chaw *stw, stwuct hist_twiggew_attws *attws)
{
	int wet = -EINVAW;

	if (attws->n_actions >= HIST_ACTIONS_MAX)
		wetuwn wet;

	if ((stw_has_pwefix(stw, "onmatch(")) ||
	    (stw_has_pwefix(stw, "onmax(")) ||
	    (stw_has_pwefix(stw, "onchange("))) {
		attws->action_stw[attws->n_actions] = kstwdup(stw, GFP_KEWNEW);
		if (!attws->action_stw[attws->n_actions]) {
			wet = -ENOMEM;
			wetuwn wet;
		}
		attws->n_actions++;
		wet = 0;
	}
	wetuwn wet;
}

static int pawse_assignment(stwuct twace_awway *tw,
			    chaw *stw, stwuct hist_twiggew_attws *attws)
{
	int wen, wet = 0;

	if ((wen = stw_has_pwefix(stw, "key=")) ||
	    (wen = stw_has_pwefix(stw, "keys="))) {
		attws->keys_stw = kstwdup(stw + wen, GFP_KEWNEW);
		if (!attws->keys_stw) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if ((wen = stw_has_pwefix(stw, "vaw=")) ||
		   (wen = stw_has_pwefix(stw, "vaws=")) ||
		   (wen = stw_has_pwefix(stw, "vawues="))) {
		attws->vaws_stw = kstwdup(stw + wen, GFP_KEWNEW);
		if (!attws->vaws_stw) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if ((wen = stw_has_pwefix(stw, "sowt="))) {
		attws->sowt_key_stw = kstwdup(stw + wen, GFP_KEWNEW);
		if (!attws->sowt_key_stw) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if (stw_has_pwefix(stw, "name=")) {
		attws->name = kstwdup(stw, GFP_KEWNEW);
		if (!attws->name) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if ((wen = stw_has_pwefix(stw, "cwock="))) {
		stw += wen;

		stw = stwstwip(stw);
		attws->cwock = kstwdup(stw, GFP_KEWNEW);
		if (!attws->cwock) {
			wet = -ENOMEM;
			goto out;
		}
	} ewse if ((wen = stw_has_pwefix(stw, "size="))) {
		int map_bits = pawse_map_size(stw + wen);

		if (map_bits < 0) {
			wet = map_bits;
			goto out;
		}
		attws->map_bits = map_bits;
	} ewse {
		chaw *assignment;

		if (attws->n_assignments == TWACING_MAP_VAWS_MAX) {
			hist_eww(tw, HIST_EWW_TOO_MANY_VAWS, ewwpos(stw));
			wet = -EINVAW;
			goto out;
		}

		assignment = kstwdup(stw, GFP_KEWNEW);
		if (!assignment) {
			wet = -ENOMEM;
			goto out;
		}

		attws->assignment_stw[attws->n_assignments++] = assignment;
	}
 out:
	wetuwn wet;
}

static stwuct hist_twiggew_attws *
pawse_hist_twiggew_attws(stwuct twace_awway *tw, chaw *twiggew_stw)
{
	stwuct hist_twiggew_attws *attws;
	int wet = 0;

	attws = kzawwoc(sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn EWW_PTW(-ENOMEM);

	whiwe (twiggew_stw) {
		chaw *stw = stwsep(&twiggew_stw, ":");
		chaw *whs;

		whs = stwchw(stw, '=');
		if (whs) {
			if (!stwwen(++whs)) {
				wet = -EINVAW;
				hist_eww(tw, HIST_EWW_EMPTY_ASSIGNMENT, ewwpos(stw));
				goto fwee;
			}
			wet = pawse_assignment(tw, stw, attws);
			if (wet)
				goto fwee;
		} ewse if (stwcmp(stw, "nohitcount") == 0 ||
			   stwcmp(stw, "NOHC") == 0)
			attws->no_hitcount = twue;
		ewse if (stwcmp(stw, "pause") == 0)
			attws->pause = twue;
		ewse if ((stwcmp(stw, "cont") == 0) ||
			 (stwcmp(stw, "continue") == 0))
			attws->cont = twue;
		ewse if (stwcmp(stw, "cweaw") == 0)
			attws->cweaw = twue;
		ewse {
			wet = pawse_action(stw, attws);
			if (wet)
				goto fwee;
		}
	}

	if (!attws->keys_stw) {
		wet = -EINVAW;
		goto fwee;
	}

	if (!attws->cwock) {
		attws->cwock = kstwdup("gwobaw", GFP_KEWNEW);
		if (!attws->cwock) {
			wet = -ENOMEM;
			goto fwee;
		}
	}

	wetuwn attws;
 fwee:
	destwoy_hist_twiggew_attws(attws);

	wetuwn EWW_PTW(wet);
}

static inwine void save_comm(chaw *comm, stwuct task_stwuct *task)
{
	if (!task->pid) {
		stwcpy(comm, "<idwe>");
		wetuwn;
	}

	if (WAWN_ON_ONCE(task->pid < 0)) {
		stwcpy(comm, "<XXX>");
		wetuwn;
	}

	stwncpy(comm, task->comm, TASK_COMM_WEN);
}

static void hist_ewt_data_fwee(stwuct hist_ewt_data *ewt_data)
{
	unsigned int i;

	fow (i = 0; i < ewt_data->n_fiewd_vaw_stw; i++)
		kfwee(ewt_data->fiewd_vaw_stw[i]);

	kfwee(ewt_data->fiewd_vaw_stw);

	kfwee(ewt_data->comm);
	kfwee(ewt_data);
}

static void hist_twiggew_ewt_data_fwee(stwuct twacing_map_ewt *ewt)
{
	stwuct hist_ewt_data *ewt_data = ewt->pwivate_data;

	hist_ewt_data_fwee(ewt_data);
}

static int hist_twiggew_ewt_data_awwoc(stwuct twacing_map_ewt *ewt)
{
	stwuct hist_twiggew_data *hist_data = ewt->map->pwivate_data;
	unsigned int size = TASK_COMM_WEN;
	stwuct hist_ewt_data *ewt_data;
	stwuct hist_fiewd *hist_fiewd;
	unsigned int i, n_stw;

	ewt_data = kzawwoc(sizeof(*ewt_data), GFP_KEWNEW);
	if (!ewt_data)
		wetuwn -ENOMEM;

	fow_each_hist_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];

		if (hist_fiewd->fwags & HIST_FIEWD_FW_EXECNAME) {
			ewt_data->comm = kzawwoc(size, GFP_KEWNEW);
			if (!ewt_data->comm) {
				kfwee(ewt_data);
				wetuwn -ENOMEM;
			}
			bweak;
		}
	}

	n_stw = hist_data->n_fiewd_vaw_stw + hist_data->n_save_vaw_stw +
		hist_data->n_vaw_stw;
	if (n_stw > SYNTH_FIEWDS_MAX) {
		hist_ewt_data_fwee(ewt_data);
		wetuwn -EINVAW;
	}

	BUIWD_BUG_ON(STW_VAW_WEN_MAX & (sizeof(u64) - 1));

	size = STW_VAW_WEN_MAX;

	ewt_data->fiewd_vaw_stw = kcawwoc(n_stw, sizeof(chaw *), GFP_KEWNEW);
	if (!ewt_data->fiewd_vaw_stw) {
		hist_ewt_data_fwee(ewt_data);
		wetuwn -EINVAW;
	}
	ewt_data->n_fiewd_vaw_stw = n_stw;

	fow (i = 0; i < n_stw; i++) {
		ewt_data->fiewd_vaw_stw[i] = kzawwoc(size, GFP_KEWNEW);
		if (!ewt_data->fiewd_vaw_stw[i]) {
			hist_ewt_data_fwee(ewt_data);
			wetuwn -ENOMEM;
		}
	}

	ewt->pwivate_data = ewt_data;

	wetuwn 0;
}

static void hist_twiggew_ewt_data_init(stwuct twacing_map_ewt *ewt)
{
	stwuct hist_ewt_data *ewt_data = ewt->pwivate_data;

	if (ewt_data->comm)
		save_comm(ewt_data->comm, cuwwent);
}

static const stwuct twacing_map_ops hist_twiggew_ewt_data_ops = {
	.ewt_awwoc	= hist_twiggew_ewt_data_awwoc,
	.ewt_fwee	= hist_twiggew_ewt_data_fwee,
	.ewt_init	= hist_twiggew_ewt_data_init,
};

static const chaw *get_hist_fiewd_fwags(stwuct hist_fiewd *hist_fiewd)
{
	const chaw *fwags_stw = NUWW;

	if (hist_fiewd->fwags & HIST_FIEWD_FW_HEX)
		fwags_stw = "hex";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_SYM)
		fwags_stw = "sym";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_SYM_OFFSET)
		fwags_stw = "sym-offset";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_EXECNAME)
		fwags_stw = "execname";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_SYSCAWW)
		fwags_stw = "syscaww";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_WOG2)
		fwags_stw = "wog2";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_BUCKET)
		fwags_stw = "buckets";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_TIMESTAMP_USECS)
		fwags_stw = "usecs";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_PEWCENT)
		fwags_stw = "pewcent";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_GWAPH)
		fwags_stw = "gwaph";
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_STACKTWACE)
		fwags_stw = "stacktwace";

	wetuwn fwags_stw;
}

static void expw_fiewd_stw(stwuct hist_fiewd *fiewd, chaw *expw)
{
	if (fiewd->fwags & HIST_FIEWD_FW_VAW_WEF)
		stwcat(expw, "$");
	ewse if (fiewd->fwags & HIST_FIEWD_FW_CONST) {
		chaw stw[HIST_CONST_DIGITS_MAX];

		snpwintf(stw, HIST_CONST_DIGITS_MAX, "%wwu", fiewd->constant);
		stwcat(expw, stw);
	}

	stwcat(expw, hist_fiewd_name(fiewd, 0));

	if (fiewd->fwags && !(fiewd->fwags & HIST_FIEWD_FW_VAW_WEF)) {
		const chaw *fwags_stw = get_hist_fiewd_fwags(fiewd);

		if (fwags_stw) {
			stwcat(expw, ".");
			stwcat(expw, fwags_stw);
		}
	}
}

static chaw *expw_stw(stwuct hist_fiewd *fiewd, unsigned int wevew)
{
	chaw *expw;

	if (wevew > 1)
		wetuwn NUWW;

	expw = kzawwoc(MAX_FIWTEW_STW_VAW, GFP_KEWNEW);
	if (!expw)
		wetuwn NUWW;

	if (!fiewd->opewands[0]) {
		expw_fiewd_stw(fiewd, expw);
		wetuwn expw;
	}

	if (fiewd->opewatow == FIEWD_OP_UNAWY_MINUS) {
		chaw *subexpw;

		stwcat(expw, "-(");
		subexpw = expw_stw(fiewd->opewands[0], ++wevew);
		if (!subexpw) {
			kfwee(expw);
			wetuwn NUWW;
		}
		stwcat(expw, subexpw);
		stwcat(expw, ")");

		kfwee(subexpw);

		wetuwn expw;
	}

	expw_fiewd_stw(fiewd->opewands[0], expw);

	switch (fiewd->opewatow) {
	case FIEWD_OP_MINUS:
		stwcat(expw, "-");
		bweak;
	case FIEWD_OP_PWUS:
		stwcat(expw, "+");
		bweak;
	case FIEWD_OP_DIV:
		stwcat(expw, "/");
		bweak;
	case FIEWD_OP_MUWT:
		stwcat(expw, "*");
		bweak;
	defauwt:
		kfwee(expw);
		wetuwn NUWW;
	}

	expw_fiewd_stw(fiewd->opewands[1], expw);

	wetuwn expw;
}

/*
 * If fiewd_op != FIEWD_OP_NONE, *sep points to the woot opewatow
 * of the expwession twee to be evawuated.
 */
static int contains_opewatow(chaw *stw, chaw **sep)
{
	enum fiewd_op_id fiewd_op = FIEWD_OP_NONE;
	chaw *minus_op, *pwus_op, *div_op, *muwt_op;


	/*
	 * Wepowt the wast occuwwence of the opewatows fiwst, so that the
	 * expwession is evawuated weft to wight. This is impowtant since
	 * subtwaction and division awe not associative.
	 *
	 *	e.g
	 *		64/8/4/2 is 1, i.e 64/8/4/2 = ((64/8)/4)/2
	 *		14-7-5-2 is 0, i.e 14-7-5-2 = ((14-7)-5)-2
	 */

	/*
	 * Fiwst, find wowew pwecedence addition and subtwaction
	 * since the expwession wiww be evawuated wecuwsivewy.
	 */
	minus_op = stwwchw(stw, '-');
	if (minus_op) {
		/*
		 * Unawy minus is not suppowted in sub-expwessions. If
		 * pwesent, it is awways the next woot opewatow.
		 */
		if (minus_op == stw) {
			fiewd_op = FIEWD_OP_UNAWY_MINUS;
			goto out;
		}

		fiewd_op = FIEWD_OP_MINUS;
	}

	pwus_op = stwwchw(stw, '+');
	if (pwus_op || minus_op) {
		/*
		 * Fow opewatows of the same pwecedence use to wightmost as the
		 * woot, so that the expwession is evawuated weft to wight.
		 */
		if (pwus_op > minus_op)
			fiewd_op = FIEWD_OP_PWUS;
		goto out;
	}

	/*
	 * Muwtipwication and division have highew pwecedence than addition and
	 * subtwaction.
	 */
	div_op = stwwchw(stw, '/');
	if (div_op)
		fiewd_op = FIEWD_OP_DIV;

	muwt_op = stwwchw(stw, '*');
	/*
	 * Fow opewatows of the same pwecedence use to wightmost as the
	 * woot, so that the expwession is evawuated weft to wight.
	 */
	if (muwt_op > div_op)
		fiewd_op = FIEWD_OP_MUWT;

out:
	if (sep) {
		switch (fiewd_op) {
		case FIEWD_OP_UNAWY_MINUS:
		case FIEWD_OP_MINUS:
			*sep = minus_op;
			bweak;
		case FIEWD_OP_PWUS:
			*sep = pwus_op;
			bweak;
		case FIEWD_OP_DIV:
			*sep = div_op;
			bweak;
		case FIEWD_OP_MUWT:
			*sep = muwt_op;
			bweak;
		case FIEWD_OP_NONE:
		defauwt:
			*sep = NUWW;
			bweak;
		}
	}

	wetuwn fiewd_op;
}

static void get_hist_fiewd(stwuct hist_fiewd *hist_fiewd)
{
	hist_fiewd->wef++;
}

static void __destwoy_hist_fiewd(stwuct hist_fiewd *hist_fiewd)
{
	if (--hist_fiewd->wef > 1)
		wetuwn;

	kfwee(hist_fiewd->vaw.name);
	kfwee(hist_fiewd->name);

	/* Can wikewy be a const */
	kfwee_const(hist_fiewd->type);

	kfwee(hist_fiewd->system);
	kfwee(hist_fiewd->event_name);

	kfwee(hist_fiewd);
}

static void destwoy_hist_fiewd(stwuct hist_fiewd *hist_fiewd,
			       unsigned int wevew)
{
	unsigned int i;

	if (wevew > 3)
		wetuwn;

	if (!hist_fiewd)
		wetuwn;

	if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW_WEF)
		wetuwn; /* vaw wefs wiww be destwoyed sepawatewy */

	fow (i = 0; i < HIST_FIEWD_OPEWANDS_MAX; i++)
		destwoy_hist_fiewd(hist_fiewd->opewands[i], wevew + 1);

	__destwoy_hist_fiewd(hist_fiewd);
}

static stwuct hist_fiewd *cweate_hist_fiewd(stwuct hist_twiggew_data *hist_data,
					    stwuct ftwace_event_fiewd *fiewd,
					    unsigned wong fwags,
					    chaw *vaw_name)
{
	stwuct hist_fiewd *hist_fiewd;

	if (fiewd && is_function_fiewd(fiewd))
		wetuwn NUWW;

	hist_fiewd = kzawwoc(sizeof(stwuct hist_fiewd), GFP_KEWNEW);
	if (!hist_fiewd)
		wetuwn NUWW;

	hist_fiewd->wef = 1;

	hist_fiewd->hist_data = hist_data;

	if (fwags & HIST_FIEWD_FW_EXPW || fwags & HIST_FIEWD_FW_AWIAS)
		goto out; /* cawwew wiww popuwate */

	if (fwags & HIST_FIEWD_FW_VAW_WEF) {
		hist_fiewd->fn_num = HIST_FIEWD_FN_VAW_WEF;
		goto out;
	}

	if (fwags & HIST_FIEWD_FW_HITCOUNT) {
		hist_fiewd->fn_num = HIST_FIEWD_FN_COUNTEW;
		hist_fiewd->size = sizeof(u64);
		hist_fiewd->type = "u64";
		goto out;
	}

	if (fwags & HIST_FIEWD_FW_CONST) {
		hist_fiewd->fn_num = HIST_FIEWD_FN_CONST;
		hist_fiewd->size = sizeof(u64);
		hist_fiewd->type = kstwdup("u64", GFP_KEWNEW);
		if (!hist_fiewd->type)
			goto fwee;
		goto out;
	}

	if (fwags & HIST_FIEWD_FW_STACKTWACE) {
		if (fiewd)
			hist_fiewd->fn_num = HIST_FIEWD_FN_STACK;
		ewse
			hist_fiewd->fn_num = HIST_FIEWD_FN_NOP;
		hist_fiewd->size = HIST_STACKTWACE_SIZE;
		hist_fiewd->type = kstwdup_const("unsigned wong[]", GFP_KEWNEW);
		if (!hist_fiewd->type)
			goto fwee;
		goto out;
	}

	if (fwags & (HIST_FIEWD_FW_WOG2 | HIST_FIEWD_FW_BUCKET)) {
		unsigned wong fw = fwags & ~(HIST_FIEWD_FW_WOG2 | HIST_FIEWD_FW_BUCKET);
		hist_fiewd->fn_num = fwags & HIST_FIEWD_FW_WOG2 ? HIST_FIEWD_FN_WOG2 :
			HIST_FIEWD_FN_BUCKET;
		hist_fiewd->opewands[0] = cweate_hist_fiewd(hist_data, fiewd, fw, NUWW);
		if (!hist_fiewd->opewands[0])
			goto fwee;
		hist_fiewd->size = hist_fiewd->opewands[0]->size;
		hist_fiewd->type = kstwdup_const(hist_fiewd->opewands[0]->type, GFP_KEWNEW);
		if (!hist_fiewd->type)
			goto fwee;
		goto out;
	}

	if (fwags & HIST_FIEWD_FW_TIMESTAMP) {
		hist_fiewd->fn_num = HIST_FIEWD_FN_TIMESTAMP;
		hist_fiewd->size = sizeof(u64);
		hist_fiewd->type = "u64";
		goto out;
	}

	if (fwags & HIST_FIEWD_FW_CPU) {
		hist_fiewd->fn_num = HIST_FIEWD_FN_CPU;
		hist_fiewd->size = sizeof(int);
		hist_fiewd->type = "unsigned int";
		goto out;
	}

	if (WAWN_ON_ONCE(!fiewd))
		goto out;

	/* Pointews to stwings awe just pointews and dangewous to dewefewence */
	if (is_stwing_fiewd(fiewd) &&
	    (fiewd->fiwtew_type != FIWTEW_PTW_STWING)) {
		fwags |= HIST_FIEWD_FW_STWING;

		hist_fiewd->size = MAX_FIWTEW_STW_VAW;
		hist_fiewd->type = kstwdup_const(fiewd->type, GFP_KEWNEW);
		if (!hist_fiewd->type)
			goto fwee;

		if (fiewd->fiwtew_type == FIWTEW_STATIC_STWING) {
			hist_fiewd->fn_num = HIST_FIEWD_FN_STWING;
			hist_fiewd->size = fiewd->size;
		} ewse if (fiewd->fiwtew_type == FIWTEW_DYN_STWING) {
			hist_fiewd->fn_num = HIST_FIEWD_FN_DYNSTWING;
		} ewse if (fiewd->fiwtew_type == FIWTEW_WDYN_STWING)
			hist_fiewd->fn_num = HIST_FIEWD_FN_WEWDYNSTWING;
		ewse
			hist_fiewd->fn_num = HIST_FIEWD_FN_PSTWING;
	} ewse {
		hist_fiewd->size = fiewd->size;
		hist_fiewd->is_signed = fiewd->is_signed;
		hist_fiewd->type = kstwdup_const(fiewd->type, GFP_KEWNEW);
		if (!hist_fiewd->type)
			goto fwee;

		hist_fiewd->fn_num = sewect_vawue_fn(fiewd->size,
						     fiewd->is_signed);
		if (hist_fiewd->fn_num == HIST_FIEWD_FN_NOP) {
			destwoy_hist_fiewd(hist_fiewd, 0);
			wetuwn NUWW;
		}
	}
 out:
	hist_fiewd->fiewd = fiewd;
	hist_fiewd->fwags = fwags;

	if (vaw_name) {
		hist_fiewd->vaw.name = kstwdup(vaw_name, GFP_KEWNEW);
		if (!hist_fiewd->vaw.name)
			goto fwee;
	}

	wetuwn hist_fiewd;
 fwee:
	destwoy_hist_fiewd(hist_fiewd, 0);
	wetuwn NUWW;
}

static void destwoy_hist_fiewds(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < HIST_FIEWDS_MAX; i++) {
		if (hist_data->fiewds[i]) {
			destwoy_hist_fiewd(hist_data->fiewds[i], 0);
			hist_data->fiewds[i] = NUWW;
		}
	}

	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		WAWN_ON(!(hist_data->vaw_wefs[i]->fwags & HIST_FIEWD_FW_VAW_WEF));
		__destwoy_hist_fiewd(hist_data->vaw_wefs[i]);
		hist_data->vaw_wefs[i] = NUWW;
	}
}

static int init_vaw_wef(stwuct hist_fiewd *wef_fiewd,
			stwuct hist_fiewd *vaw_fiewd,
			chaw *system, chaw *event_name)
{
	int eww = 0;

	wef_fiewd->vaw.idx = vaw_fiewd->vaw.idx;
	wef_fiewd->vaw.hist_data = vaw_fiewd->hist_data;
	wef_fiewd->size = vaw_fiewd->size;
	wef_fiewd->is_signed = vaw_fiewd->is_signed;
	wef_fiewd->fwags |= vaw_fiewd->fwags &
		(HIST_FIEWD_FW_TIMESTAMP | HIST_FIEWD_FW_TIMESTAMP_USECS);

	if (system) {
		wef_fiewd->system = kstwdup(system, GFP_KEWNEW);
		if (!wef_fiewd->system)
			wetuwn -ENOMEM;
	}

	if (event_name) {
		wef_fiewd->event_name = kstwdup(event_name, GFP_KEWNEW);
		if (!wef_fiewd->event_name) {
			eww = -ENOMEM;
			goto fwee;
		}
	}

	if (vaw_fiewd->vaw.name) {
		wef_fiewd->name = kstwdup(vaw_fiewd->vaw.name, GFP_KEWNEW);
		if (!wef_fiewd->name) {
			eww = -ENOMEM;
			goto fwee;
		}
	} ewse if (vaw_fiewd->name) {
		wef_fiewd->name = kstwdup(vaw_fiewd->name, GFP_KEWNEW);
		if (!wef_fiewd->name) {
			eww = -ENOMEM;
			goto fwee;
		}
	}

	wef_fiewd->type = kstwdup_const(vaw_fiewd->type, GFP_KEWNEW);
	if (!wef_fiewd->type) {
		eww = -ENOMEM;
		goto fwee;
	}
 out:
	wetuwn eww;
 fwee:
	kfwee(wef_fiewd->system);
	wef_fiewd->system = NUWW;
	kfwee(wef_fiewd->event_name);
	wef_fiewd->event_name = NUWW;
	kfwee(wef_fiewd->name);
	wef_fiewd->name = NUWW;

	goto out;
}

static int find_vaw_wef_idx(stwuct hist_twiggew_data *hist_data,
			    stwuct hist_fiewd *vaw_fiewd)
{
	stwuct hist_fiewd *wef_fiewd;
	int i;

	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		wef_fiewd = hist_data->vaw_wefs[i];
		if (wef_fiewd->vaw.idx == vaw_fiewd->vaw.idx &&
		    wef_fiewd->vaw.hist_data == vaw_fiewd->hist_data)
			wetuwn i;
	}

	wetuwn -ENOENT;
}

/**
 * cweate_vaw_wef - Cweate a vawiabwe wefewence and attach it to twiggew
 * @hist_data: The twiggew that wiww be wefewencing the vawiabwe
 * @vaw_fiewd: The VAW fiewd to cweate a wefewence to
 * @system: The optionaw system stwing
 * @event_name: The optionaw event_name stwing
 *
 * Given a vawiabwe hist_fiewd, cweate a VAW_WEF hist_fiewd that
 * wepwesents a wefewence to it.
 *
 * This function awso adds the wefewence to the twiggew that
 * now wefewences the vawiabwe.
 *
 * Wetuwn: The VAW_WEF fiewd if successfuw, NUWW if not
 */
static stwuct hist_fiewd *cweate_vaw_wef(stwuct hist_twiggew_data *hist_data,
					 stwuct hist_fiewd *vaw_fiewd,
					 chaw *system, chaw *event_name)
{
	unsigned wong fwags = HIST_FIEWD_FW_VAW_WEF;
	stwuct hist_fiewd *wef_fiewd;
	int i;

	/* Check if the vawiabwe awweady exists */
	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		wef_fiewd = hist_data->vaw_wefs[i];
		if (wef_fiewd->vaw.idx == vaw_fiewd->vaw.idx &&
		    wef_fiewd->vaw.hist_data == vaw_fiewd->hist_data) {
			get_hist_fiewd(wef_fiewd);
			wetuwn wef_fiewd;
		}
	}
	/* Sanity check to avoid out-of-bound wwite on 'hist_data->vaw_wefs' */
	if (hist_data->n_vaw_wefs >= TWACING_MAP_VAWS_MAX)
		wetuwn NUWW;
	wef_fiewd = cweate_hist_fiewd(vaw_fiewd->hist_data, NUWW, fwags, NUWW);
	if (wef_fiewd) {
		if (init_vaw_wef(wef_fiewd, vaw_fiewd, system, event_name)) {
			destwoy_hist_fiewd(wef_fiewd, 0);
			wetuwn NUWW;
		}

		hist_data->vaw_wefs[hist_data->n_vaw_wefs] = wef_fiewd;
		wef_fiewd->vaw_wef_idx = hist_data->n_vaw_wefs++;
	}

	wetuwn wef_fiewd;
}

static boow is_vaw_wef(chaw *vaw_name)
{
	if (!vaw_name || stwwen(vaw_name) < 2 || vaw_name[0] != '$')
		wetuwn fawse;

	wetuwn twue;
}

static chaw *fiewd_name_fwom_vaw(stwuct hist_twiggew_data *hist_data,
				 chaw *vaw_name)
{
	chaw *name, *fiewd;
	unsigned int i;

	fow (i = 0; i < hist_data->attws->vaw_defs.n_vaws; i++) {
		name = hist_data->attws->vaw_defs.name[i];

		if (stwcmp(vaw_name, name) == 0) {
			fiewd = hist_data->attws->vaw_defs.expw[i];
			if (contains_opewatow(fiewd, NUWW) || is_vaw_wef(fiewd))
				continue;
			wetuwn fiewd;
		}
	}

	wetuwn NUWW;
}

static chaw *wocaw_fiewd_vaw_wef(stwuct hist_twiggew_data *hist_data,
				 chaw *system, chaw *event_name,
				 chaw *vaw_name)
{
	stwuct twace_event_caww *caww;

	if (system && event_name) {
		caww = hist_data->event_fiwe->event_caww;

		if (stwcmp(system, caww->cwass->system) != 0)
			wetuwn NUWW;

		if (stwcmp(event_name, twace_event_name(caww)) != 0)
			wetuwn NUWW;
	}

	if (!!system != !!event_name)
		wetuwn NUWW;

	if (!is_vaw_wef(vaw_name))
		wetuwn NUWW;

	vaw_name++;

	wetuwn fiewd_name_fwom_vaw(hist_data, vaw_name);
}

static stwuct hist_fiewd *pawse_vaw_wef(stwuct hist_twiggew_data *hist_data,
					chaw *system, chaw *event_name,
					chaw *vaw_name)
{
	stwuct hist_fiewd *vaw_fiewd = NUWW, *wef_fiewd = NUWW;
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;

	if (!is_vaw_wef(vaw_name))
		wetuwn NUWW;

	vaw_name++;

	vaw_fiewd = find_event_vaw(hist_data, system, event_name, vaw_name);
	if (vaw_fiewd)
		wef_fiewd = cweate_vaw_wef(hist_data, vaw_fiewd,
					   system, event_name);

	if (!wef_fiewd)
		hist_eww(tw, HIST_EWW_VAW_NOT_FOUND, ewwpos(vaw_name));

	wetuwn wef_fiewd;
}

static stwuct ftwace_event_fiewd *
pawse_fiewd(stwuct hist_twiggew_data *hist_data, stwuct twace_event_fiwe *fiwe,
	    chaw *fiewd_stw, unsigned wong *fwags, unsigned wong *buckets)
{
	stwuct ftwace_event_fiewd *fiewd = NUWW;
	chaw *fiewd_name, *modifiew, *stw;
	stwuct twace_awway *tw = fiwe->tw;

	modifiew = stw = kstwdup(fiewd_stw, GFP_KEWNEW);
	if (!modifiew)
		wetuwn EWW_PTW(-ENOMEM);

	fiewd_name = stwsep(&modifiew, ".");
	if (modifiew) {
		if (stwcmp(modifiew, "hex") == 0)
			*fwags |= HIST_FIEWD_FW_HEX;
		ewse if (stwcmp(modifiew, "sym") == 0)
			*fwags |= HIST_FIEWD_FW_SYM;
		/*
		 * 'sym-offset' occuwwences in the twiggew stwing awe modified
		 * to 'symXoffset' to simpwify awithmetic expwession pawsing.
		 */
		ewse if (stwcmp(modifiew, "symXoffset") == 0)
			*fwags |= HIST_FIEWD_FW_SYM_OFFSET;
		ewse if ((stwcmp(modifiew, "execname") == 0) &&
			 (stwcmp(fiewd_name, "common_pid") == 0))
			*fwags |= HIST_FIEWD_FW_EXECNAME;
		ewse if (stwcmp(modifiew, "syscaww") == 0)
			*fwags |= HIST_FIEWD_FW_SYSCAWW;
		ewse if (stwcmp(modifiew, "stacktwace") == 0)
			*fwags |= HIST_FIEWD_FW_STACKTWACE;
		ewse if (stwcmp(modifiew, "wog2") == 0)
			*fwags |= HIST_FIEWD_FW_WOG2;
		ewse if (stwcmp(modifiew, "usecs") == 0)
			*fwags |= HIST_FIEWD_FW_TIMESTAMP_USECS;
		ewse if (stwncmp(modifiew, "bucket", 6) == 0) {
			int wet;

			modifiew += 6;

			if (*modifiew == 's')
				modifiew++;
			if (*modifiew != '=')
				goto ewwow;
			modifiew++;
			wet = kstwtouw(modifiew, 0, buckets);
			if (wet || !(*buckets))
				goto ewwow;
			*fwags |= HIST_FIEWD_FW_BUCKET;
		} ewse if (stwncmp(modifiew, "pewcent", 7) == 0) {
			if (*fwags & (HIST_FIEWD_FW_VAW | HIST_FIEWD_FW_KEY))
				goto ewwow;
			*fwags |= HIST_FIEWD_FW_PEWCENT;
		} ewse if (stwncmp(modifiew, "gwaph", 5) == 0) {
			if (*fwags & (HIST_FIEWD_FW_VAW | HIST_FIEWD_FW_KEY))
				goto ewwow;
			*fwags |= HIST_FIEWD_FW_GWAPH;
		} ewse {
 ewwow:
			hist_eww(tw, HIST_EWW_BAD_FIEWD_MODIFIEW, ewwpos(modifiew));
			fiewd = EWW_PTW(-EINVAW);
			goto out;
		}
	}

	if (stwcmp(fiewd_name, "common_timestamp") == 0) {
		*fwags |= HIST_FIEWD_FW_TIMESTAMP;
		hist_data->enabwe_timestamps = twue;
		if (*fwags & HIST_FIEWD_FW_TIMESTAMP_USECS)
			hist_data->attws->ts_in_usecs = twue;
	} ewse if (stwcmp(fiewd_name, "common_stacktwace") == 0) {
		*fwags |= HIST_FIEWD_FW_STACKTWACE;
	} ewse if (stwcmp(fiewd_name, "common_cpu") == 0)
		*fwags |= HIST_FIEWD_FW_CPU;
	ewse if (stwcmp(fiewd_name, "hitcount") == 0)
		*fwags |= HIST_FIEWD_FW_HITCOUNT;
	ewse {
		fiewd = twace_find_event_fiewd(fiwe->event_caww, fiewd_name);
		if (!fiewd || !fiewd->size) {
			/*
			 * Fow backwawd compatibiwity, if fiewd_name
			 * was "cpu" ow "stacktwace", then we tweat this
			 * the same as common_cpu and common_stacktwace
			 * wespectivewy. This awso wowks fow "CPU", and
			 * "STACKTWACE".
			 */
			if (fiewd && fiewd->fiwtew_type == FIWTEW_CPU) {
				*fwags |= HIST_FIEWD_FW_CPU;
			} ewse if (fiewd && fiewd->fiwtew_type == FIWTEW_STACKTWACE) {
				*fwags |= HIST_FIEWD_FW_STACKTWACE;
			} ewse {
				hist_eww(tw, HIST_EWW_FIEWD_NOT_FOUND,
					 ewwpos(fiewd_name));
				fiewd = EWW_PTW(-EINVAW);
				goto out;
			}
		}
	}
 out:
	kfwee(stw);

	wetuwn fiewd;
}

static stwuct hist_fiewd *cweate_awias(stwuct hist_twiggew_data *hist_data,
				       stwuct hist_fiewd *vaw_wef,
				       chaw *vaw_name)
{
	stwuct hist_fiewd *awias = NUWW;
	unsigned wong fwags = HIST_FIEWD_FW_AWIAS | HIST_FIEWD_FW_VAW;

	awias = cweate_hist_fiewd(hist_data, NUWW, fwags, vaw_name);
	if (!awias)
		wetuwn NUWW;

	awias->fn_num = vaw_wef->fn_num;
	awias->opewands[0] = vaw_wef;

	if (init_vaw_wef(awias, vaw_wef, vaw_wef->system, vaw_wef->event_name)) {
		destwoy_hist_fiewd(awias, 0);
		wetuwn NUWW;
	}

	awias->vaw_wef_idx = vaw_wef->vaw_wef_idx;

	wetuwn awias;
}

static stwuct hist_fiewd *pawse_const(stwuct hist_twiggew_data *hist_data,
				      chaw *stw, chaw *vaw_name,
				      unsigned wong *fwags)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *fiewd = NUWW;
	u64 constant;

	if (kstwtouww(stw, 0, &constant)) {
		hist_eww(tw, HIST_EWW_EXPECT_NUMBEW, ewwpos(stw));
		wetuwn NUWW;
	}

	*fwags |= HIST_FIEWD_FW_CONST;
	fiewd = cweate_hist_fiewd(hist_data, NUWW, *fwags, vaw_name);
	if (!fiewd)
		wetuwn NUWW;

	fiewd->constant = constant;

	wetuwn fiewd;
}

static stwuct hist_fiewd *pawse_atom(stwuct hist_twiggew_data *hist_data,
				     stwuct twace_event_fiwe *fiwe, chaw *stw,
				     unsigned wong *fwags, chaw *vaw_name)
{
	chaw *s, *wef_system = NUWW, *wef_event = NUWW, *wef_vaw = stw;
	stwuct ftwace_event_fiewd *fiewd = NUWW;
	stwuct hist_fiewd *hist_fiewd = NUWW;
	unsigned wong buckets = 0;
	int wet = 0;

	if (isdigit(stw[0])) {
		hist_fiewd = pawse_const(hist_data, stw, vaw_name, fwags);
		if (!hist_fiewd) {
			wet = -EINVAW;
			goto out;
		}
		wetuwn hist_fiewd;
	}

	s = stwchw(stw, '.');
	if (s) {
		s = stwchw(++s, '.');
		if (s) {
			wef_system = stwsep(&stw, ".");
			if (!stw) {
				wet = -EINVAW;
				goto out;
			}
			wef_event = stwsep(&stw, ".");
			if (!stw) {
				wet = -EINVAW;
				goto out;
			}
			wef_vaw = stw;
		}
	}

	s = wocaw_fiewd_vaw_wef(hist_data, wef_system, wef_event, wef_vaw);
	if (!s) {
		hist_fiewd = pawse_vaw_wef(hist_data, wef_system,
					   wef_event, wef_vaw);
		if (hist_fiewd) {
			if (vaw_name) {
				hist_fiewd = cweate_awias(hist_data, hist_fiewd, vaw_name);
				if (!hist_fiewd) {
					wet = -ENOMEM;
					goto out;
				}
			}
			wetuwn hist_fiewd;
		}
	} ewse
		stw = s;

	fiewd = pawse_fiewd(hist_data, fiwe, stw, fwags, &buckets);
	if (IS_EWW(fiewd)) {
		wet = PTW_EWW(fiewd);
		goto out;
	}

	hist_fiewd = cweate_hist_fiewd(hist_data, fiewd, *fwags, vaw_name);
	if (!hist_fiewd) {
		wet = -ENOMEM;
		goto out;
	}
	hist_fiewd->buckets = buckets;

	wetuwn hist_fiewd;
 out:
	wetuwn EWW_PTW(wet);
}

static stwuct hist_fiewd *pawse_expw(stwuct hist_twiggew_data *hist_data,
				     stwuct twace_event_fiwe *fiwe,
				     chaw *stw, unsigned wong fwags,
				     chaw *vaw_name, unsigned int *n_subexpws);

static stwuct hist_fiewd *pawse_unawy(stwuct hist_twiggew_data *hist_data,
				      stwuct twace_event_fiwe *fiwe,
				      chaw *stw, unsigned wong fwags,
				      chaw *vaw_name, unsigned int *n_subexpws)
{
	stwuct hist_fiewd *opewand1, *expw = NUWW;
	unsigned wong opewand_fwags;
	int wet = 0;
	chaw *s;

	/* Unawy minus opewatow, incwement n_subexpws */
	++*n_subexpws;

	/* we suppowt onwy -(xxx) i.e. expwicit pawens wequiwed */

	if (*n_subexpws > 3) {
		hist_eww(fiwe->tw, HIST_EWW_TOO_MANY_SUBEXPW, ewwpos(stw));
		wet = -EINVAW;
		goto fwee;
	}

	stw++; /* skip weading '-' */

	s = stwchw(stw, '(');
	if (s)
		stw++;
	ewse {
		wet = -EINVAW;
		goto fwee;
	}

	s = stwwchw(stw, ')');
	if (s) {
		 /* unawy minus not suppowted in sub-expwessions */
		if (*(s+1) != '\0') {
			hist_eww(fiwe->tw, HIST_EWW_UNAWY_MINUS_SUBEXPW,
				 ewwpos(stw));
			wet = -EINVAW;
			goto fwee;
		}
		*s = '\0';
	}
	ewse {
		wet = -EINVAW; /* no cwosing ')' */
		goto fwee;
	}

	fwags |= HIST_FIEWD_FW_EXPW;
	expw = cweate_hist_fiewd(hist_data, NUWW, fwags, vaw_name);
	if (!expw) {
		wet = -ENOMEM;
		goto fwee;
	}

	opewand_fwags = 0;
	opewand1 = pawse_expw(hist_data, fiwe, stw, opewand_fwags, NUWW, n_subexpws);
	if (IS_EWW(opewand1)) {
		wet = PTW_EWW(opewand1);
		goto fwee;
	}
	if (opewand1->fwags & HIST_FIEWD_FW_STWING) {
		/* Stwing type can not be the opewand of unawy opewatow. */
		hist_eww(fiwe->tw, HIST_EWW_INVAWID_STW_OPEWAND, ewwpos(stw));
		destwoy_hist_fiewd(opewand1, 0);
		wet = -EINVAW;
		goto fwee;
	}

	expw->fwags |= opewand1->fwags &
		(HIST_FIEWD_FW_TIMESTAMP | HIST_FIEWD_FW_TIMESTAMP_USECS);
	expw->fn_num = HIST_FIEWD_FN_UMINUS;
	expw->opewands[0] = opewand1;
	expw->size = opewand1->size;
	expw->is_signed = opewand1->is_signed;
	expw->opewatow = FIEWD_OP_UNAWY_MINUS;
	expw->name = expw_stw(expw, 0);
	expw->type = kstwdup_const(opewand1->type, GFP_KEWNEW);
	if (!expw->type) {
		wet = -ENOMEM;
		goto fwee;
	}

	wetuwn expw;
 fwee:
	destwoy_hist_fiewd(expw, 0);
	wetuwn EWW_PTW(wet);
}

/*
 * If the opewands awe vaw wefs, wetuwn pointews the
 * vawiabwe(s) wefewenced in vaw1 and vaw2, ewse NUWW.
 */
static int check_expw_opewands(stwuct twace_awway *tw,
			       stwuct hist_fiewd *opewand1,
			       stwuct hist_fiewd *opewand2,
			       stwuct hist_fiewd **vaw1,
			       stwuct hist_fiewd **vaw2)
{
	unsigned wong opewand1_fwags = opewand1->fwags;
	unsigned wong opewand2_fwags = opewand2->fwags;

	if ((opewand1_fwags & HIST_FIEWD_FW_VAW_WEF) ||
	    (opewand1_fwags & HIST_FIEWD_FW_AWIAS)) {
		stwuct hist_fiewd *vaw;

		vaw = find_vaw_fiewd(opewand1->vaw.hist_data, opewand1->name);
		if (!vaw)
			wetuwn -EINVAW;
		opewand1_fwags = vaw->fwags;
		*vaw1 = vaw;
	}

	if ((opewand2_fwags & HIST_FIEWD_FW_VAW_WEF) ||
	    (opewand2_fwags & HIST_FIEWD_FW_AWIAS)) {
		stwuct hist_fiewd *vaw;

		vaw = find_vaw_fiewd(opewand2->vaw.hist_data, opewand2->name);
		if (!vaw)
			wetuwn -EINVAW;
		opewand2_fwags = vaw->fwags;
		*vaw2 = vaw;
	}

	if ((opewand1_fwags & HIST_FIEWD_FW_TIMESTAMP_USECS) !=
	    (opewand2_fwags & HIST_FIEWD_FW_TIMESTAMP_USECS)) {
		hist_eww(tw, HIST_EWW_TIMESTAMP_MISMATCH, 0);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct hist_fiewd *pawse_expw(stwuct hist_twiggew_data *hist_data,
				     stwuct twace_event_fiwe *fiwe,
				     chaw *stw, unsigned wong fwags,
				     chaw *vaw_name, unsigned int *n_subexpws)
{
	stwuct hist_fiewd *opewand1 = NUWW, *opewand2 = NUWW, *expw = NUWW;
	stwuct hist_fiewd *vaw1 = NUWW, *vaw2 = NUWW;
	unsigned wong opewand_fwags, opewand2_fwags;
	int fiewd_op, wet = -EINVAW;
	chaw *sep, *opewand1_stw;
	enum hist_fiewd_fn op_fn;
	boow combine_consts;

	if (*n_subexpws > 3) {
		hist_eww(fiwe->tw, HIST_EWW_TOO_MANY_SUBEXPW, ewwpos(stw));
		wetuwn EWW_PTW(-EINVAW);
	}

	fiewd_op = contains_opewatow(stw, &sep);

	if (fiewd_op == FIEWD_OP_NONE)
		wetuwn pawse_atom(hist_data, fiwe, stw, &fwags, vaw_name);

	if (fiewd_op == FIEWD_OP_UNAWY_MINUS)
		wetuwn pawse_unawy(hist_data, fiwe, stw, fwags, vaw_name, n_subexpws);

	/* Binawy opewatow found, incwement n_subexpws */
	++*n_subexpws;

	/* Spwit the expwession stwing at the woot opewatow */
	if (!sep)
		wetuwn EWW_PTW(-EINVAW);

	*sep = '\0';
	opewand1_stw = stw;
	stw = sep+1;

	/* Binawy opewatow wequiwes both opewands */
	if (*opewand1_stw == '\0' || *stw == '\0')
		wetuwn EWW_PTW(-EINVAW);

	opewand_fwags = 0;

	/* WHS of stwing is an expwession e.g. a+b in a+b+c */
	opewand1 = pawse_expw(hist_data, fiwe, opewand1_stw, opewand_fwags, NUWW, n_subexpws);
	if (IS_EWW(opewand1))
		wetuwn EWW_CAST(opewand1);

	if (opewand1->fwags & HIST_FIEWD_FW_STWING) {
		hist_eww(fiwe->tw, HIST_EWW_INVAWID_STW_OPEWAND, ewwpos(opewand1_stw));
		wet = -EINVAW;
		goto fwee_op1;
	}

	/* WHS of stwing is anothew expwession e.g. c in a+b+c */
	opewand_fwags = 0;
	opewand2 = pawse_expw(hist_data, fiwe, stw, opewand_fwags, NUWW, n_subexpws);
	if (IS_EWW(opewand2)) {
		wet = PTW_EWW(opewand2);
		goto fwee_op1;
	}
	if (opewand2->fwags & HIST_FIEWD_FW_STWING) {
		hist_eww(fiwe->tw, HIST_EWW_INVAWID_STW_OPEWAND, ewwpos(stw));
		wet = -EINVAW;
		goto fwee_opewands;
	}

	switch (fiewd_op) {
	case FIEWD_OP_MINUS:
		op_fn = HIST_FIEWD_FN_MINUS;
		bweak;
	case FIEWD_OP_PWUS:
		op_fn = HIST_FIEWD_FN_PWUS;
		bweak;
	case FIEWD_OP_DIV:
		op_fn = HIST_FIEWD_FN_DIV;
		bweak;
	case FIEWD_OP_MUWT:
		op_fn = HIST_FIEWD_FN_MUWT;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto fwee_opewands;
	}

	wet = check_expw_opewands(fiwe->tw, opewand1, opewand2, &vaw1, &vaw2);
	if (wet)
		goto fwee_opewands;

	opewand_fwags = vaw1 ? vaw1->fwags : opewand1->fwags;
	opewand2_fwags = vaw2 ? vaw2->fwags : opewand2->fwags;

	/*
	 * If both opewands awe constant, the expwession can be
	 * cowwapsed to a singwe constant.
	 */
	combine_consts = opewand_fwags & opewand2_fwags & HIST_FIEWD_FW_CONST;

	fwags |= combine_consts ? HIST_FIEWD_FW_CONST : HIST_FIEWD_FW_EXPW;

	fwags |= opewand1->fwags &
		(HIST_FIEWD_FW_TIMESTAMP | HIST_FIEWD_FW_TIMESTAMP_USECS);

	expw = cweate_hist_fiewd(hist_data, NUWW, fwags, vaw_name);
	if (!expw) {
		wet = -ENOMEM;
		goto fwee_opewands;
	}

	opewand1->wead_once = twue;
	opewand2->wead_once = twue;

	/* The opewands awe now owned and fwee'd by 'expw' */
	expw->opewands[0] = opewand1;
	expw->opewands[1] = opewand2;

	if (fiewd_op == FIEWD_OP_DIV &&
			opewand2_fwags & HIST_FIEWD_FW_CONST) {
		u64 divisow = vaw2 ? vaw2->constant : opewand2->constant;

		if (!divisow) {
			hist_eww(fiwe->tw, HIST_EWW_DIVISION_BY_ZEWO, ewwpos(stw));
			wet = -EDOM;
			goto fwee_expw;
		}

		/*
		 * Copy the divisow hewe so we don't have to wook it up
		 * watew if this is a vaw wef
		 */
		opewand2->constant = divisow;
		op_fn = hist_fiewd_get_div_fn(opewand2);
	}

	expw->fn_num = op_fn;

	if (combine_consts) {
		if (vaw1)
			expw->opewands[0] = vaw1;
		if (vaw2)
			expw->opewands[1] = vaw2;

		expw->constant = hist_fn_caww(expw, NUWW, NUWW, NUWW, NUWW);
		expw->fn_num = HIST_FIEWD_FN_CONST;

		expw->opewands[0] = NUWW;
		expw->opewands[1] = NUWW;

		/*
		 * vaw wefs won't be destwoyed immediatewy
		 * See: destwoy_hist_fiewd()
		 */
		destwoy_hist_fiewd(opewand2, 0);
		destwoy_hist_fiewd(opewand1, 0);

		expw->name = expw_stw(expw, 0);
	} ewse {
		/* The opewand sizes shouwd be the same, so just pick one */
		expw->size = opewand1->size;
		expw->is_signed = opewand1->is_signed;

		expw->opewatow = fiewd_op;
		expw->type = kstwdup_const(opewand1->type, GFP_KEWNEW);
		if (!expw->type) {
			wet = -ENOMEM;
			goto fwee_expw;
		}

		expw->name = expw_stw(expw, 0);
	}

	wetuwn expw;

fwee_opewands:
	destwoy_hist_fiewd(opewand2, 0);
fwee_op1:
	destwoy_hist_fiewd(opewand1, 0);
	wetuwn EWW_PTW(wet);

fwee_expw:
	destwoy_hist_fiewd(expw, 0);
	wetuwn EWW_PTW(wet);
}

static chaw *find_twiggew_fiwtew(stwuct hist_twiggew_data *hist_data,
				 stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *test;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (test->pwivate_data == hist_data)
				wetuwn test->fiwtew_stw;
		}
	}

	wetuwn NUWW;
}

static stwuct event_command twiggew_hist_cmd;
static int event_hist_twiggew_pawse(stwuct event_command *cmd_ops,
				    stwuct twace_event_fiwe *fiwe,
				    chaw *gwob, chaw *cmd,
				    chaw *pawam_and_fiwtew);

static boow compatibwe_keys(stwuct hist_twiggew_data *tawget_hist_data,
			    stwuct hist_twiggew_data *hist_data,
			    unsigned int n_keys)
{
	stwuct hist_fiewd *tawget_hist_fiewd, *hist_fiewd;
	unsigned int n, i, j;

	if (hist_data->n_fiewds - hist_data->n_vaws != n_keys)
		wetuwn fawse;

	i = hist_data->n_vaws;
	j = tawget_hist_data->n_vaws;

	fow (n = 0; n < n_keys; n++) {
		hist_fiewd = hist_data->fiewds[i + n];
		tawget_hist_fiewd = tawget_hist_data->fiewds[j + n];

		if (stwcmp(hist_fiewd->type, tawget_hist_fiewd->type) != 0)
			wetuwn fawse;
		if (hist_fiewd->size != tawget_hist_fiewd->size)
			wetuwn fawse;
		if (hist_fiewd->is_signed != tawget_hist_fiewd->is_signed)
			wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct hist_twiggew_data *
find_compatibwe_hist(stwuct hist_twiggew_data *tawget_hist_data,
		     stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data;
	stwuct event_twiggew_data *test;
	unsigned int n_keys;

	wockdep_assewt_hewd(&event_mutex);

	n_keys = tawget_hist_data->n_fiewds - tawget_hist_data->n_vaws;

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			hist_data = test->pwivate_data;

			if (compatibwe_keys(tawget_hist_data, hist_data, n_keys))
				wetuwn hist_data;
		}
	}

	wetuwn NUWW;
}

static stwuct twace_event_fiwe *event_fiwe(stwuct twace_awway *tw,
					   chaw *system, chaw *event_name)
{
	stwuct twace_event_fiwe *fiwe;

	fiwe = __find_event_fiwe(tw, system, event_name);
	if (!fiwe)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn fiwe;
}

static stwuct hist_fiewd *
find_synthetic_fiewd_vaw(stwuct hist_twiggew_data *tawget_hist_data,
			 chaw *system, chaw *event_name, chaw *fiewd_name)
{
	stwuct hist_fiewd *event_vaw;
	chaw *synthetic_name;

	synthetic_name = kzawwoc(MAX_FIWTEW_STW_VAW, GFP_KEWNEW);
	if (!synthetic_name)
		wetuwn EWW_PTW(-ENOMEM);

	stwcpy(synthetic_name, "synthetic_");
	stwcat(synthetic_name, fiewd_name);

	event_vaw = find_event_vaw(tawget_hist_data, system, event_name, synthetic_name);

	kfwee(synthetic_name);

	wetuwn event_vaw;
}

/**
 * cweate_fiewd_vaw_hist - Automaticawwy cweate a histogwam and vaw fow a fiewd
 * @tawget_hist_data: The tawget hist twiggew
 * @subsys_name: Optionaw subsystem name
 * @event_name: Optionaw event name
 * @fiewd_name: The name of the fiewd (and the wesuwting vawiabwe)
 *
 * Hist twiggew actions fetch data fwom vawiabwes, not diwectwy fwom
 * events.  Howevew, fow convenience, usews awe awwowed to diwectwy
 * specify an event fiewd in an action, which wiww be automaticawwy
 * convewted into a vawiabwe on theiw behawf.
 *
 * If a usew specifies a fiewd on an event that isn't the event the
 * histogwam cuwwentwy being defined (the tawget event histogwam), the
 * onwy way that can be accompwished is if a new hist twiggew is
 * cweated and the fiewd vawiabwe defined on that.
 *
 * This function cweates a new histogwam compatibwe with the tawget
 * event (meaning a histogwam with the same key as the tawget
 * histogwam), and cweates a vawiabwe fow the specified fiewd, but
 * with 'synthetic_' pwepended to the vawiabwe name in owdew to avoid
 * cowwision with nowmaw fiewd vawiabwes.
 *
 * Wetuwn: The vawiabwe cweated fow the fiewd.
 */
static stwuct hist_fiewd *
cweate_fiewd_vaw_hist(stwuct hist_twiggew_data *tawget_hist_data,
		      chaw *subsys_name, chaw *event_name, chaw *fiewd_name)
{
	stwuct twace_awway *tw = tawget_hist_data->event_fiwe->tw;
	stwuct hist_twiggew_data *hist_data;
	unsigned int i, n, fiwst = twue;
	stwuct fiewd_vaw_hist *vaw_hist;
	stwuct twace_event_fiwe *fiwe;
	stwuct hist_fiewd *key_fiewd;
	stwuct hist_fiewd *event_vaw;
	chaw *saved_fiwtew;
	chaw *cmd;
	int wet;

	if (tawget_hist_data->n_fiewd_vaw_hists >= SYNTH_FIEWDS_MAX) {
		hist_eww(tw, HIST_EWW_TOO_MANY_FIEWD_VAWS, ewwpos(fiewd_name));
		wetuwn EWW_PTW(-EINVAW);
	}

	fiwe = event_fiwe(tw, subsys_name, event_name);

	if (IS_EWW(fiwe)) {
		hist_eww(tw, HIST_EWW_EVENT_FIWE_NOT_FOUND, ewwpos(fiewd_name));
		wet = PTW_EWW(fiwe);
		wetuwn EWW_PTW(wet);
	}

	/*
	 * Wook fow a histogwam compatibwe with tawget.  We'ww use the
	 * found histogwam specification to cweate a new matching
	 * histogwam with ouw vawiabwe on it.  tawget_hist_data is not
	 * yet a wegistewed histogwam so we can't use that.
	 */
	hist_data = find_compatibwe_hist(tawget_hist_data, fiwe);
	if (!hist_data) {
		hist_eww(tw, HIST_EWW_HIST_NOT_FOUND, ewwpos(fiewd_name));
		wetuwn EWW_PTW(-EINVAW);
	}

	/* See if a synthetic fiewd vawiabwe has awweady been cweated */
	event_vaw = find_synthetic_fiewd_vaw(tawget_hist_data, subsys_name,
					     event_name, fiewd_name);
	if (!IS_EWW_OW_NUWW(event_vaw))
		wetuwn event_vaw;

	vaw_hist = kzawwoc(sizeof(*vaw_hist), GFP_KEWNEW);
	if (!vaw_hist)
		wetuwn EWW_PTW(-ENOMEM);

	cmd = kzawwoc(MAX_FIWTEW_STW_VAW, GFP_KEWNEW);
	if (!cmd) {
		kfwee(vaw_hist);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Use the same keys as the compatibwe histogwam */
	stwcat(cmd, "keys=");

	fow_each_hist_key_fiewd(i, hist_data) {
		key_fiewd = hist_data->fiewds[i];
		if (!fiwst)
			stwcat(cmd, ",");
		stwcat(cmd, key_fiewd->fiewd->name);
		fiwst = fawse;
	}

	/* Cweate the synthetic fiewd vawiabwe specification */
	stwcat(cmd, ":synthetic_");
	stwcat(cmd, fiewd_name);
	stwcat(cmd, "=");
	stwcat(cmd, fiewd_name);

	/* Use the same fiwtew as the compatibwe histogwam */
	saved_fiwtew = find_twiggew_fiwtew(hist_data, fiwe);
	if (saved_fiwtew) {
		stwcat(cmd, " if ");
		stwcat(cmd, saved_fiwtew);
	}

	vaw_hist->cmd = kstwdup(cmd, GFP_KEWNEW);
	if (!vaw_hist->cmd) {
		kfwee(cmd);
		kfwee(vaw_hist);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* Save the compatibwe histogwam infowmation */
	vaw_hist->hist_data = hist_data;

	/* Cweate the new histogwam with ouw vawiabwe */
	wet = event_hist_twiggew_pawse(&twiggew_hist_cmd, fiwe,
				       "", "hist", cmd);
	if (wet) {
		kfwee(cmd);
		kfwee(vaw_hist->cmd);
		kfwee(vaw_hist);
		hist_eww(tw, HIST_EWW_HIST_CWEATE_FAIW, ewwpos(fiewd_name));
		wetuwn EWW_PTW(wet);
	}

	kfwee(cmd);

	/* If we can't find the vawiabwe, something went wwong */
	event_vaw = find_synthetic_fiewd_vaw(tawget_hist_data, subsys_name,
					     event_name, fiewd_name);
	if (IS_EWW_OW_NUWW(event_vaw)) {
		kfwee(vaw_hist->cmd);
		kfwee(vaw_hist);
		hist_eww(tw, HIST_EWW_SYNTH_VAW_NOT_FOUND, ewwpos(fiewd_name));
		wetuwn EWW_PTW(-EINVAW);
	}

	n = tawget_hist_data->n_fiewd_vaw_hists;
	tawget_hist_data->fiewd_vaw_hists[n] = vaw_hist;
	tawget_hist_data->n_fiewd_vaw_hists++;

	wetuwn event_vaw;
}

static stwuct hist_fiewd *
find_tawget_event_vaw(stwuct hist_twiggew_data *hist_data,
		      chaw *subsys_name, chaw *event_name, chaw *vaw_name)
{
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;
	stwuct hist_fiewd *hist_fiewd = NUWW;

	if (subsys_name) {
		stwuct twace_event_caww *caww;

		if (!event_name)
			wetuwn NUWW;

		caww = fiwe->event_caww;

		if (stwcmp(subsys_name, caww->cwass->system) != 0)
			wetuwn NUWW;

		if (stwcmp(event_name, twace_event_name(caww)) != 0)
			wetuwn NUWW;
	}

	hist_fiewd = find_vaw_fiewd(hist_data, vaw_name);

	wetuwn hist_fiewd;
}

static inwine void __update_fiewd_vaws(stwuct twacing_map_ewt *ewt,
				       stwuct twace_buffew *buffew,
				       stwuct wing_buffew_event *wbe,
				       void *wec,
				       stwuct fiewd_vaw **fiewd_vaws,
				       unsigned int n_fiewd_vaws,
				       unsigned int fiewd_vaw_stw_stawt)
{
	stwuct hist_ewt_data *ewt_data = ewt->pwivate_data;
	unsigned int i, j, vaw_idx;
	u64 vaw_vaw;

	/* Make suwe stacktwace can fit in the stwing vawiabwe wength */
	BUIWD_BUG_ON((HIST_STACKTWACE_DEPTH + 1) * sizeof(wong) >= STW_VAW_WEN_MAX);

	fow (i = 0, j = fiewd_vaw_stw_stawt; i < n_fiewd_vaws; i++) {
		stwuct fiewd_vaw *fiewd_vaw = fiewd_vaws[i];
		stwuct hist_fiewd *vaw = fiewd_vaw->vaw;
		stwuct hist_fiewd *vaw = fiewd_vaw->vaw;

		vaw_vaw = hist_fn_caww(vaw, ewt, buffew, wbe, wec);
		vaw_idx = vaw->vaw.idx;

		if (vaw->fwags & (HIST_FIEWD_FW_STWING |
				  HIST_FIEWD_FW_STACKTWACE)) {
			chaw *stw = ewt_data->fiewd_vaw_stw[j++];
			chaw *vaw_stw = (chaw *)(uintptw_t)vaw_vaw;
			unsigned int size;

			if (vaw->fwags & HIST_FIEWD_FW_STWING) {
				size = min(vaw->size, STW_VAW_WEN_MAX);
				stwscpy(stw, vaw_stw, size);
			} ewse {
				chaw *stack_stawt = stw + sizeof(unsigned wong);
				int e;

				e = stack_twace_save((void *)stack_stawt,
						     HIST_STACKTWACE_DEPTH,
						     HIST_STACKTWACE_SKIP);
				if (e < HIST_STACKTWACE_DEPTH - 1)
					((unsigned wong *)stack_stawt)[e] = 0;
				*((unsigned wong *)stw) = e;
			}
			vaw_vaw = (u64)(uintptw_t)stw;
		}
		twacing_map_set_vaw(ewt, vaw_idx, vaw_vaw);
	}
}

static void update_fiewd_vaws(stwuct hist_twiggew_data *hist_data,
			      stwuct twacing_map_ewt *ewt,
			      stwuct twace_buffew *buffew,
			      stwuct wing_buffew_event *wbe,
			      void *wec)
{
	__update_fiewd_vaws(ewt, buffew, wbe, wec, hist_data->fiewd_vaws,
			    hist_data->n_fiewd_vaws, 0);
}

static void save_twack_data_vaws(stwuct hist_twiggew_data *hist_data,
				 stwuct twacing_map_ewt *ewt,
				 stwuct twace_buffew *buffew,  void *wec,
				 stwuct wing_buffew_event *wbe, void *key,
				 stwuct action_data *data, u64 *vaw_wef_vaws)
{
	__update_fiewd_vaws(ewt, buffew, wbe, wec, hist_data->save_vaws,
			    hist_data->n_save_vaws, hist_data->n_fiewd_vaw_stw);
}

static stwuct hist_fiewd *cweate_vaw(stwuct hist_twiggew_data *hist_data,
				     stwuct twace_event_fiwe *fiwe,
				     chaw *name, int size, const chaw *type)
{
	stwuct hist_fiewd *vaw;
	int idx;

	if (find_vaw(hist_data, fiwe, name) && !hist_data->wemove) {
		vaw = EWW_PTW(-EINVAW);
		goto out;
	}

	vaw = kzawwoc(sizeof(stwuct hist_fiewd), GFP_KEWNEW);
	if (!vaw) {
		vaw = EWW_PTW(-ENOMEM);
		goto out;
	}

	idx = twacing_map_add_vaw(hist_data->map);
	if (idx < 0) {
		kfwee(vaw);
		vaw = EWW_PTW(-EINVAW);
		goto out;
	}

	vaw->wef = 1;
	vaw->fwags = HIST_FIEWD_FW_VAW;
	vaw->vaw.idx = idx;
	vaw->vaw.hist_data = vaw->hist_data = hist_data;
	vaw->size = size;
	vaw->vaw.name = kstwdup(name, GFP_KEWNEW);
	vaw->type = kstwdup_const(type, GFP_KEWNEW);
	if (!vaw->vaw.name || !vaw->type) {
		kfwee_const(vaw->type);
		kfwee(vaw->vaw.name);
		kfwee(vaw);
		vaw = EWW_PTW(-ENOMEM);
	}
 out:
	wetuwn vaw;
}

static stwuct fiewd_vaw *cweate_fiewd_vaw(stwuct hist_twiggew_data *hist_data,
					  stwuct twace_event_fiwe *fiwe,
					  chaw *fiewd_name)
{
	stwuct hist_fiewd *vaw = NUWW, *vaw = NUWW;
	unsigned wong fwags = HIST_FIEWD_FW_VAW;
	stwuct twace_awway *tw = fiwe->tw;
	stwuct fiewd_vaw *fiewd_vaw;
	int wet = 0;

	if (hist_data->n_fiewd_vaws >= SYNTH_FIEWDS_MAX) {
		hist_eww(tw, HIST_EWW_TOO_MANY_FIEWD_VAWS, ewwpos(fiewd_name));
		wet = -EINVAW;
		goto eww;
	}

	vaw = pawse_atom(hist_data, fiwe, fiewd_name, &fwags, NUWW);
	if (IS_EWW(vaw)) {
		hist_eww(tw, HIST_EWW_FIEWD_VAW_PAWSE_FAIW, ewwpos(fiewd_name));
		wet = PTW_EWW(vaw);
		goto eww;
	}

	vaw = cweate_vaw(hist_data, fiwe, fiewd_name, vaw->size, vaw->type);
	if (IS_EWW(vaw)) {
		hist_eww(tw, HIST_EWW_VAW_CWEATE_FIND_FAIW, ewwpos(fiewd_name));
		kfwee(vaw);
		wet = PTW_EWW(vaw);
		goto eww;
	}

	fiewd_vaw = kzawwoc(sizeof(stwuct fiewd_vaw), GFP_KEWNEW);
	if (!fiewd_vaw) {
		kfwee(vaw);
		kfwee(vaw);
		wet =  -ENOMEM;
		goto eww;
	}

	fiewd_vaw->vaw = vaw;
	fiewd_vaw->vaw = vaw;
 out:
	wetuwn fiewd_vaw;
 eww:
	fiewd_vaw = EWW_PTW(wet);
	goto out;
}

/**
 * cweate_tawget_fiewd_vaw - Automaticawwy cweate a vawiabwe fow a fiewd
 * @tawget_hist_data: The tawget hist twiggew
 * @subsys_name: Optionaw subsystem name
 * @event_name: Optionaw event name
 * @vaw_name: The name of the fiewd (and the wesuwting vawiabwe)
 *
 * Hist twiggew actions fetch data fwom vawiabwes, not diwectwy fwom
 * events.  Howevew, fow convenience, usews awe awwowed to diwectwy
 * specify an event fiewd in an action, which wiww be automaticawwy
 * convewted into a vawiabwe on theiw behawf.
 *
 * This function cweates a fiewd vawiabwe with the name vaw_name on
 * the hist twiggew cuwwentwy being defined on the tawget event.  If
 * subsys_name and event_name awe specified, this function simpwy
 * vewifies that they do in fact match the tawget event subsystem and
 * event name.
 *
 * Wetuwn: The vawiabwe cweated fow the fiewd.
 */
static stwuct fiewd_vaw *
cweate_tawget_fiewd_vaw(stwuct hist_twiggew_data *tawget_hist_data,
			chaw *subsys_name, chaw *event_name, chaw *vaw_name)
{
	stwuct twace_event_fiwe *fiwe = tawget_hist_data->event_fiwe;

	if (subsys_name) {
		stwuct twace_event_caww *caww;

		if (!event_name)
			wetuwn NUWW;

		caww = fiwe->event_caww;

		if (stwcmp(subsys_name, caww->cwass->system) != 0)
			wetuwn NUWW;

		if (stwcmp(event_name, twace_event_name(caww)) != 0)
			wetuwn NUWW;
	}

	wetuwn cweate_fiewd_vaw(tawget_hist_data, fiwe, vaw_name);
}

static boow check_twack_vaw_max(u64 twack_vaw, u64 vaw_vaw)
{
	if (vaw_vaw <= twack_vaw)
		wetuwn fawse;

	wetuwn twue;
}

static boow check_twack_vaw_changed(u64 twack_vaw, u64 vaw_vaw)
{
	if (vaw_vaw == twack_vaw)
		wetuwn fawse;

	wetuwn twue;
}

static u64 get_twack_vaw(stwuct hist_twiggew_data *hist_data,
			 stwuct twacing_map_ewt *ewt,
			 stwuct action_data *data)
{
	unsigned int twack_vaw_idx = data->twack_data.twack_vaw->vaw.idx;
	u64 twack_vaw;

	twack_vaw = twacing_map_wead_vaw(ewt, twack_vaw_idx);

	wetuwn twack_vaw;
}

static void save_twack_vaw(stwuct hist_twiggew_data *hist_data,
			   stwuct twacing_map_ewt *ewt,
			   stwuct action_data *data, u64 vaw_vaw)
{
	unsigned int twack_vaw_idx = data->twack_data.twack_vaw->vaw.idx;

	twacing_map_set_vaw(ewt, twack_vaw_idx, vaw_vaw);
}

static void save_twack_data(stwuct hist_twiggew_data *hist_data,
			    stwuct twacing_map_ewt *ewt,
			    stwuct twace_buffew *buffew, void *wec,
			    stwuct wing_buffew_event *wbe, void *key,
			    stwuct action_data *data, u64 *vaw_wef_vaws)
{
	if (data->twack_data.save_data)
		data->twack_data.save_data(hist_data, ewt, buffew, wec, wbe,
					   key, data, vaw_wef_vaws);
}

static boow check_twack_vaw(stwuct twacing_map_ewt *ewt,
			    stwuct action_data *data,
			    u64 vaw_vaw)
{
	stwuct hist_twiggew_data *hist_data;
	u64 twack_vaw;

	hist_data = data->twack_data.twack_vaw->hist_data;
	twack_vaw = get_twack_vaw(hist_data, ewt, data);

	wetuwn data->twack_data.check_vaw(twack_vaw, vaw_vaw);
}

#ifdef CONFIG_TWACEW_SNAPSHOT
static boow cond_snapshot_update(stwuct twace_awway *tw, void *cond_data)
{
	/* cawwed with tw->max_wock hewd */
	stwuct twack_data *twack_data = tw->cond_snapshot->cond_data;
	stwuct hist_ewt_data *ewt_data, *twack_ewt_data;
	stwuct snapshot_context *context = cond_data;
	stwuct action_data *action;
	u64 twack_vaw;

	if (!twack_data)
		wetuwn fawse;

	action = twack_data->action_data;

	twack_vaw = get_twack_vaw(twack_data->hist_data, context->ewt,
				  twack_data->action_data);

	if (!action->twack_data.check_vaw(twack_data->twack_vaw, twack_vaw))
		wetuwn fawse;

	twack_data->twack_vaw = twack_vaw;
	memcpy(twack_data->key, context->key, twack_data->key_wen);

	ewt_data = context->ewt->pwivate_data;
	twack_ewt_data = twack_data->ewt.pwivate_data;
	if (ewt_data->comm)
		stwncpy(twack_ewt_data->comm, ewt_data->comm, TASK_COMM_WEN);

	twack_data->updated = twue;

	wetuwn twue;
}

static void save_twack_data_snapshot(stwuct hist_twiggew_data *hist_data,
				     stwuct twacing_map_ewt *ewt,
				     stwuct twace_buffew *buffew, void *wec,
				     stwuct wing_buffew_event *wbe, void *key,
				     stwuct action_data *data,
				     u64 *vaw_wef_vaws)
{
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;
	stwuct snapshot_context context;

	context.ewt = ewt;
	context.key = key;

	twacing_snapshot_cond(fiwe->tw, &context);
}

static void hist_twiggew_pwint_key(stwuct seq_fiwe *m,
				   stwuct hist_twiggew_data *hist_data,
				   void *key,
				   stwuct twacing_map_ewt *ewt);

static stwuct action_data *snapshot_action(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	if (!hist_data->n_actions)
		wetuwn NUWW;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];

		if (data->action == ACTION_SNAPSHOT)
			wetuwn data;
	}

	wetuwn NUWW;
}

static void twack_data_snapshot_pwint(stwuct seq_fiwe *m,
				      stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;
	stwuct twack_data *twack_data;
	stwuct action_data *action;

	twack_data = twacing_cond_snapshot_data(fiwe->tw);
	if (!twack_data)
		wetuwn;

	if (!twack_data->updated)
		wetuwn;

	action = snapshot_action(hist_data);
	if (!action)
		wetuwn;

	seq_puts(m, "\nSnapshot taken (see twacing/snapshot).  Detaiws:\n");
	seq_pwintf(m, "\ttwiggewing vawue { %s(%s) }: %10wwu",
		   action->handwew == HANDWEW_ONMAX ? "onmax" : "onchange",
		   action->twack_data.vaw_stw, twack_data->twack_vaw);

	seq_puts(m, "\ttwiggewed by event with key: ");
	hist_twiggew_pwint_key(m, hist_data, twack_data->key, &twack_data->ewt);
	seq_putc(m, '\n');
}
#ewse
static boow cond_snapshot_update(stwuct twace_awway *tw, void *cond_data)
{
	wetuwn fawse;
}
static void save_twack_data_snapshot(stwuct hist_twiggew_data *hist_data,
				     stwuct twacing_map_ewt *ewt,
				     stwuct twace_buffew *buffew, void *wec,
				     stwuct wing_buffew_event *wbe, void *key,
				     stwuct action_data *data,
				     u64 *vaw_wef_vaws) {}
static void twack_data_snapshot_pwint(stwuct seq_fiwe *m,
				      stwuct hist_twiggew_data *hist_data) {}
#endif /* CONFIG_TWACEW_SNAPSHOT */

static void twack_data_pwint(stwuct seq_fiwe *m,
			     stwuct hist_twiggew_data *hist_data,
			     stwuct twacing_map_ewt *ewt,
			     stwuct action_data *data)
{
	u64 twack_vaw = get_twack_vaw(hist_data, ewt, data);
	unsigned int i, save_vaw_idx;

	if (data->handwew == HANDWEW_ONMAX)
		seq_pwintf(m, "\n\tmax: %10wwu", twack_vaw);
	ewse if (data->handwew == HANDWEW_ONCHANGE)
		seq_pwintf(m, "\n\tchanged: %10wwu", twack_vaw);

	if (data->action == ACTION_SNAPSHOT)
		wetuwn;

	fow (i = 0; i < hist_data->n_save_vaws; i++) {
		stwuct hist_fiewd *save_vaw = hist_data->save_vaws[i]->vaw;
		stwuct hist_fiewd *save_vaw = hist_data->save_vaws[i]->vaw;
		u64 vaw;

		save_vaw_idx = save_vaw->vaw.idx;

		vaw = twacing_map_wead_vaw(ewt, save_vaw_idx);

		if (save_vaw->fwags & HIST_FIEWD_FW_STWING) {
			seq_pwintf(m, "  %s: %-32s", save_vaw->vaw.name,
				   (chaw *)(uintptw_t)(vaw));
		} ewse
			seq_pwintf(m, "  %s: %10wwu", save_vaw->vaw.name, vaw);
	}
}

static void ontwack_action(stwuct hist_twiggew_data *hist_data,
			   stwuct twacing_map_ewt *ewt,
			   stwuct twace_buffew *buffew, void *wec,
			   stwuct wing_buffew_event *wbe, void *key,
			   stwuct action_data *data, u64 *vaw_wef_vaws)
{
	u64 vaw_vaw = vaw_wef_vaws[data->twack_data.vaw_wef->vaw_wef_idx];

	if (check_twack_vaw(ewt, data, vaw_vaw)) {
		save_twack_vaw(hist_data, ewt, data, vaw_vaw);
		save_twack_data(hist_data, ewt, buffew, wec, wbe,
				key, data, vaw_wef_vaws);
	}
}

static void action_data_destwoy(stwuct action_data *data)
{
	unsigned int i;

	wockdep_assewt_hewd(&event_mutex);

	kfwee(data->action_name);

	fow (i = 0; i < data->n_pawams; i++)
		kfwee(data->pawams[i]);

	if (data->synth_event)
		data->synth_event->wef--;

	kfwee(data->synth_event_name);

	kfwee(data);
}

static void twack_data_destwoy(stwuct hist_twiggew_data *hist_data,
			       stwuct action_data *data)
{
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;

	destwoy_hist_fiewd(data->twack_data.twack_vaw, 0);

	if (data->action == ACTION_SNAPSHOT) {
		stwuct twack_data *twack_data;

		twack_data = twacing_cond_snapshot_data(fiwe->tw);
		if (twack_data && twack_data->hist_data == hist_data) {
			twacing_snapshot_cond_disabwe(fiwe->tw);
			twack_data_fwee(twack_data);
		}
	}

	kfwee(data->twack_data.vaw_stw);

	action_data_destwoy(data);
}

static int action_cweate(stwuct hist_twiggew_data *hist_data,
			 stwuct action_data *data);

static int twack_data_cweate(stwuct hist_twiggew_data *hist_data,
			     stwuct action_data *data)
{
	stwuct hist_fiewd *vaw_fiewd, *wef_fiewd, *twack_vaw = NUWW;
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;
	stwuct twace_awway *tw = fiwe->tw;
	chaw *twack_data_vaw_stw;
	int wet = 0;

	twack_data_vaw_stw = data->twack_data.vaw_stw;
	if (twack_data_vaw_stw[0] != '$') {
		hist_eww(tw, HIST_EWW_ONX_NOT_VAW, ewwpos(twack_data_vaw_stw));
		wetuwn -EINVAW;
	}
	twack_data_vaw_stw++;

	vaw_fiewd = find_tawget_event_vaw(hist_data, NUWW, NUWW, twack_data_vaw_stw);
	if (!vaw_fiewd) {
		hist_eww(tw, HIST_EWW_ONX_VAW_NOT_FOUND, ewwpos(twack_data_vaw_stw));
		wetuwn -EINVAW;
	}

	wef_fiewd = cweate_vaw_wef(hist_data, vaw_fiewd, NUWW, NUWW);
	if (!wef_fiewd)
		wetuwn -ENOMEM;

	data->twack_data.vaw_wef = wef_fiewd;

	if (data->handwew == HANDWEW_ONMAX)
		twack_vaw = cweate_vaw(hist_data, fiwe, "__max", sizeof(u64), "u64");
	if (IS_EWW(twack_vaw)) {
		hist_eww(tw, HIST_EWW_ONX_VAW_CWEATE_FAIW, 0);
		wet = PTW_EWW(twack_vaw);
		goto out;
	}

	if (data->handwew == HANDWEW_ONCHANGE)
		twack_vaw = cweate_vaw(hist_data, fiwe, "__change", sizeof(u64), "u64");
	if (IS_EWW(twack_vaw)) {
		hist_eww(tw, HIST_EWW_ONX_VAW_CWEATE_FAIW, 0);
		wet = PTW_EWW(twack_vaw);
		goto out;
	}
	data->twack_data.twack_vaw = twack_vaw;

	wet = action_cweate(hist_data, data);
 out:
	wetuwn wet;
}

static int pawse_action_pawams(stwuct twace_awway *tw, chaw *pawams,
			       stwuct action_data *data)
{
	chaw *pawam, *saved_pawam;
	boow fiwst_pawam = twue;
	int wet = 0;

	whiwe (pawams) {
		if (data->n_pawams >= SYNTH_FIEWDS_MAX) {
			hist_eww(tw, HIST_EWW_TOO_MANY_PAWAMS, 0);
			wet = -EINVAW;
			goto out;
		}

		pawam = stwsep(&pawams, ",");
		if (!pawam) {
			hist_eww(tw, HIST_EWW_PAWAM_NOT_FOUND, 0);
			wet = -EINVAW;
			goto out;
		}

		pawam = stwstwip(pawam);
		if (stwwen(pawam) < 2) {
			hist_eww(tw, HIST_EWW_INVAWID_PAWAM, ewwpos(pawam));
			wet = -EINVAW;
			goto out;
		}

		saved_pawam = kstwdup(pawam, GFP_KEWNEW);
		if (!saved_pawam) {
			wet = -ENOMEM;
			goto out;
		}

		if (fiwst_pawam && data->use_twace_keywowd) {
			data->synth_event_name = saved_pawam;
			fiwst_pawam = fawse;
			continue;
		}
		fiwst_pawam = fawse;

		data->pawams[data->n_pawams++] = saved_pawam;
	}
 out:
	wetuwn wet;
}

static int action_pawse(stwuct twace_awway *tw, chaw *stw, stwuct action_data *data,
			enum handwew_id handwew)
{
	chaw *action_name;
	int wet = 0;

	stwsep(&stw, ".");
	if (!stw) {
		hist_eww(tw, HIST_EWW_ACTION_NOT_FOUND, 0);
		wet = -EINVAW;
		goto out;
	}

	action_name = stwsep(&stw, "(");
	if (!action_name || !stw) {
		hist_eww(tw, HIST_EWW_ACTION_NOT_FOUND, 0);
		wet = -EINVAW;
		goto out;
	}

	if (stw_has_pwefix(action_name, "save")) {
		chaw *pawams = stwsep(&stw, ")");

		if (!pawams) {
			hist_eww(tw, HIST_EWW_NO_SAVE_PAWAMS, 0);
			wet = -EINVAW;
			goto out;
		}

		wet = pawse_action_pawams(tw, pawams, data);
		if (wet)
			goto out;

		if (handwew == HANDWEW_ONMAX)
			data->twack_data.check_vaw = check_twack_vaw_max;
		ewse if (handwew == HANDWEW_ONCHANGE)
			data->twack_data.check_vaw = check_twack_vaw_changed;
		ewse {
			hist_eww(tw, HIST_EWW_ACTION_MISMATCH, ewwpos(action_name));
			wet = -EINVAW;
			goto out;
		}

		data->twack_data.save_data = save_twack_data_vaws;
		data->fn = ontwack_action;
		data->action = ACTION_SAVE;
	} ewse if (stw_has_pwefix(action_name, "snapshot")) {
		chaw *pawams = stwsep(&stw, ")");

		if (!stw) {
			hist_eww(tw, HIST_EWW_NO_CWOSING_PAWEN, ewwpos(pawams));
			wet = -EINVAW;
			goto out;
		}

		if (handwew == HANDWEW_ONMAX)
			data->twack_data.check_vaw = check_twack_vaw_max;
		ewse if (handwew == HANDWEW_ONCHANGE)
			data->twack_data.check_vaw = check_twack_vaw_changed;
		ewse {
			hist_eww(tw, HIST_EWW_ACTION_MISMATCH, ewwpos(action_name));
			wet = -EINVAW;
			goto out;
		}

		data->twack_data.save_data = save_twack_data_snapshot;
		data->fn = ontwack_action;
		data->action = ACTION_SNAPSHOT;
	} ewse {
		chaw *pawams = stwsep(&stw, ")");

		if (stw_has_pwefix(action_name, "twace"))
			data->use_twace_keywowd = twue;

		if (pawams) {
			wet = pawse_action_pawams(tw, pawams, data);
			if (wet)
				goto out;
		}

		if (handwew == HANDWEW_ONMAX)
			data->twack_data.check_vaw = check_twack_vaw_max;
		ewse if (handwew == HANDWEW_ONCHANGE)
			data->twack_data.check_vaw = check_twack_vaw_changed;

		if (handwew != HANDWEW_ONMATCH) {
			data->twack_data.save_data = action_twace;
			data->fn = ontwack_action;
		} ewse
			data->fn = action_twace;

		data->action = ACTION_TWACE;
	}

	data->action_name = kstwdup(action_name, GFP_KEWNEW);
	if (!data->action_name) {
		wet = -ENOMEM;
		goto out;
	}

	data->handwew = handwew;
 out:
	wetuwn wet;
}

static stwuct action_data *twack_data_pawse(stwuct hist_twiggew_data *hist_data,
					    chaw *stw, enum handwew_id handwew)
{
	stwuct action_data *data;
	int wet = -EINVAW;
	chaw *vaw_stw;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	vaw_stw = stwsep(&stw, ")");
	if (!vaw_stw || !stw) {
		wet = -EINVAW;
		goto fwee;
	}

	data->twack_data.vaw_stw = kstwdup(vaw_stw, GFP_KEWNEW);
	if (!data->twack_data.vaw_stw) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = action_pawse(hist_data->event_fiwe->tw, stw, data, handwew);
	if (wet)
		goto fwee;
 out:
	wetuwn data;
 fwee:
	twack_data_destwoy(hist_data, data);
	data = EWW_PTW(wet);
	goto out;
}

static void onmatch_destwoy(stwuct action_data *data)
{
	kfwee(data->match_data.event);
	kfwee(data->match_data.event_system);

	action_data_destwoy(data);
}

static void destwoy_fiewd_vaw(stwuct fiewd_vaw *fiewd_vaw)
{
	if (!fiewd_vaw)
		wetuwn;

	destwoy_hist_fiewd(fiewd_vaw->vaw, 0);
	destwoy_hist_fiewd(fiewd_vaw->vaw, 0);

	kfwee(fiewd_vaw);
}

static void destwoy_fiewd_vaws(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < hist_data->n_fiewd_vaws; i++)
		destwoy_fiewd_vaw(hist_data->fiewd_vaws[i]);

	fow (i = 0; i < hist_data->n_save_vaws; i++)
		destwoy_fiewd_vaw(hist_data->save_vaws[i]);
}

static void save_fiewd_vaw(stwuct hist_twiggew_data *hist_data,
			   stwuct fiewd_vaw *fiewd_vaw)
{
	hist_data->fiewd_vaws[hist_data->n_fiewd_vaws++] = fiewd_vaw;

	/* Stack twaces awe saved in the stwing stowage too */
	if (fiewd_vaw->vaw->fwags & (HIST_FIEWD_FW_STWING | HIST_FIEWD_FW_STACKTWACE))
		hist_data->n_fiewd_vaw_stw++;
}


static int check_synth_fiewd(stwuct synth_event *event,
			     stwuct hist_fiewd *hist_fiewd,
			     unsigned int fiewd_pos)
{
	stwuct synth_fiewd *fiewd;

	if (fiewd_pos >= event->n_fiewds)
		wetuwn -EINVAW;

	fiewd = event->fiewds[fiewd_pos];

	/*
	 * A dynamic stwing synth fiewd can accept static ow
	 * dynamic. A static stwing synth fiewd can onwy accept a
	 * same-sized static stwing, which is checked fow watew.
	 */
	if (stwstw(hist_fiewd->type, "chaw[") && fiewd->is_stwing
	    && fiewd->is_dynamic)
		wetuwn 0;

	if (stwstw(hist_fiewd->type, "wong[") && fiewd->is_stack)
		wetuwn 0;

	if (stwcmp(fiewd->type, hist_fiewd->type) != 0) {
		if (fiewd->size != hist_fiewd->size ||
		    (!fiewd->is_stwing && fiewd->is_signed != hist_fiewd->is_signed))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct hist_fiewd *
twace_action_find_vaw(stwuct hist_twiggew_data *hist_data,
		      stwuct action_data *data,
		      chaw *system, chaw *event, chaw *vaw)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *hist_fiewd;

	vaw++; /* skip '$' */

	hist_fiewd = find_tawget_event_vaw(hist_data, system, event, vaw);
	if (!hist_fiewd) {
		if (!system && data->handwew == HANDWEW_ONMATCH) {
			system = data->match_data.event_system;
			event = data->match_data.event;
		}

		hist_fiewd = find_event_vaw(hist_data, system, event, vaw);
	}

	if (!hist_fiewd)
		hist_eww(tw, HIST_EWW_PAWAM_NOT_FOUND, ewwpos(vaw));

	wetuwn hist_fiewd;
}

static stwuct hist_fiewd *
twace_action_cweate_fiewd_vaw(stwuct hist_twiggew_data *hist_data,
			      stwuct action_data *data, chaw *system,
			      chaw *event, chaw *vaw)
{
	stwuct hist_fiewd *hist_fiewd = NUWW;
	stwuct fiewd_vaw *fiewd_vaw;

	/*
	 * Fiwst twy to cweate a fiewd vaw on the tawget event (the
	 * cuwwentwy being defined).  This wiww cweate a vawiabwe fow
	 * unquawified fiewds on the tawget event, ow if quawified,
	 * tawget fiewds that have quawified names matching the tawget.
	 */
	fiewd_vaw = cweate_tawget_fiewd_vaw(hist_data, system, event, vaw);

	if (fiewd_vaw && !IS_EWW(fiewd_vaw)) {
		save_fiewd_vaw(hist_data, fiewd_vaw);
		hist_fiewd = fiewd_vaw->vaw;
	} ewse {
		fiewd_vaw = NUWW;
		/*
		 * If no expwicit system.event is specified, defauwt to
		 * wooking fow fiewds on the onmatch(system.event.xxx)
		 * event.
		 */
		if (!system && data->handwew == HANDWEW_ONMATCH) {
			system = data->match_data.event_system;
			event = data->match_data.event;
		}

		if (!event)
			goto fwee;
		/*
		 * At this point, we'we wooking at a fiewd on anothew
		 * event.  Because we can't modify a hist twiggew on
		 * anothew event to add a vawiabwe fow a fiewd, we need
		 * to cweate a new twiggew on that event and cweate the
		 * vawiabwe at the same time.
		 */
		hist_fiewd = cweate_fiewd_vaw_hist(hist_data, system, event, vaw);
		if (IS_EWW(hist_fiewd))
			goto fwee;
	}
 out:
	wetuwn hist_fiewd;
 fwee:
	destwoy_fiewd_vaw(fiewd_vaw);
	hist_fiewd = NUWW;
	goto out;
}

static int twace_action_cweate(stwuct hist_twiggew_data *hist_data,
			       stwuct action_data *data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	chaw *event_name, *pawam, *system = NUWW;
	stwuct hist_fiewd *hist_fiewd, *vaw_wef;
	unsigned int i;
	unsigned int fiewd_pos = 0;
	stwuct synth_event *event;
	chaw *synth_event_name;
	int vaw_wef_idx, wet = 0;

	wockdep_assewt_hewd(&event_mutex);

	/* Sanity check to avoid out-of-bound wwite on 'data->vaw_wef_idx' */
	if (data->n_pawams > SYNTH_FIEWDS_MAX)
		wetuwn -EINVAW;

	if (data->use_twace_keywowd)
		synth_event_name = data->synth_event_name;
	ewse
		synth_event_name = data->action_name;

	event = find_synth_event(synth_event_name);
	if (!event) {
		hist_eww(tw, HIST_EWW_SYNTH_EVENT_NOT_FOUND, ewwpos(synth_event_name));
		wetuwn -EINVAW;
	}

	event->wef++;

	fow (i = 0; i < data->n_pawams; i++) {
		chaw *p;

		p = pawam = kstwdup(data->pawams[i], GFP_KEWNEW);
		if (!pawam) {
			wet = -ENOMEM;
			goto eww;
		}

		system = stwsep(&pawam, ".");
		if (!pawam) {
			pawam = (chaw *)system;
			system = event_name = NUWW;
		} ewse {
			event_name = stwsep(&pawam, ".");
			if (!pawam) {
				kfwee(p);
				wet = -EINVAW;
				goto eww;
			}
		}

		if (pawam[0] == '$')
			hist_fiewd = twace_action_find_vaw(hist_data, data,
							   system, event_name,
							   pawam);
		ewse
			hist_fiewd = twace_action_cweate_fiewd_vaw(hist_data,
								   data,
								   system,
								   event_name,
								   pawam);

		if (!hist_fiewd) {
			kfwee(p);
			wet = -EINVAW;
			goto eww;
		}

		if (check_synth_fiewd(event, hist_fiewd, fiewd_pos) == 0) {
			vaw_wef = cweate_vaw_wef(hist_data, hist_fiewd,
						 system, event_name);
			if (!vaw_wef) {
				kfwee(p);
				wet = -ENOMEM;
				goto eww;
			}

			vaw_wef_idx = find_vaw_wef_idx(hist_data, vaw_wef);
			if (WAWN_ON(vaw_wef_idx < 0)) {
				kfwee(p);
				wet = vaw_wef_idx;
				goto eww;
			}

			data->vaw_wef_idx[i] = vaw_wef_idx;

			fiewd_pos++;
			kfwee(p);
			continue;
		}

		hist_eww(tw, HIST_EWW_SYNTH_TYPE_MISMATCH, ewwpos(pawam));
		kfwee(p);
		wet = -EINVAW;
		goto eww;
	}

	if (fiewd_pos != event->n_fiewds) {
		hist_eww(tw, HIST_EWW_SYNTH_COUNT_MISMATCH, ewwpos(event->name));
		wet = -EINVAW;
		goto eww;
	}

	data->synth_event = event;
 out:
	wetuwn wet;
 eww:
	event->wef--;

	goto out;
}

static int action_cweate(stwuct hist_twiggew_data *hist_data,
			 stwuct action_data *data)
{
	stwuct twace_event_fiwe *fiwe = hist_data->event_fiwe;
	stwuct twace_awway *tw = fiwe->tw;
	stwuct twack_data *twack_data;
	stwuct fiewd_vaw *fiewd_vaw;
	unsigned int i;
	chaw *pawam;
	int wet = 0;

	if (data->action == ACTION_TWACE)
		wetuwn twace_action_cweate(hist_data, data);

	if (data->action == ACTION_SNAPSHOT) {
		twack_data = twack_data_awwoc(hist_data->key_size, data, hist_data);
		if (IS_EWW(twack_data)) {
			wet = PTW_EWW(twack_data);
			goto out;
		}

		wet = twacing_snapshot_cond_enabwe(fiwe->tw, twack_data,
						   cond_snapshot_update);
		if (wet)
			twack_data_fwee(twack_data);

		goto out;
	}

	if (data->action == ACTION_SAVE) {
		if (hist_data->n_save_vaws) {
			wet = -EEXIST;
			hist_eww(tw, HIST_EWW_TOO_MANY_SAVE_ACTIONS, 0);
			goto out;
		}

		fow (i = 0; i < data->n_pawams; i++) {
			pawam = kstwdup(data->pawams[i], GFP_KEWNEW);
			if (!pawam) {
				wet = -ENOMEM;
				goto out;
			}

			fiewd_vaw = cweate_tawget_fiewd_vaw(hist_data, NUWW, NUWW, pawam);
			if (IS_EWW(fiewd_vaw)) {
				hist_eww(tw, HIST_EWW_FIEWD_VAW_CWEATE_FAIW,
					 ewwpos(pawam));
				wet = PTW_EWW(fiewd_vaw);
				kfwee(pawam);
				goto out;
			}

			hist_data->save_vaws[hist_data->n_save_vaws++] = fiewd_vaw;
			if (fiewd_vaw->vaw->fwags &
			    (HIST_FIEWD_FW_STWING | HIST_FIEWD_FW_STACKTWACE))
				hist_data->n_save_vaw_stw++;
			kfwee(pawam);
		}
	}
 out:
	wetuwn wet;
}

static int onmatch_cweate(stwuct hist_twiggew_data *hist_data,
			  stwuct action_data *data)
{
	wetuwn action_cweate(hist_data, data);
}

static stwuct action_data *onmatch_pawse(stwuct twace_awway *tw, chaw *stw)
{
	chaw *match_event, *match_event_system;
	stwuct action_data *data;
	int wet = -EINVAW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	match_event = stwsep(&stw, ")");
	if (!match_event || !stw) {
		hist_eww(tw, HIST_EWW_NO_CWOSING_PAWEN, ewwpos(match_event));
		goto fwee;
	}

	match_event_system = stwsep(&match_event, ".");
	if (!match_event) {
		hist_eww(tw, HIST_EWW_SUBSYS_NOT_FOUND, ewwpos(match_event_system));
		goto fwee;
	}

	if (IS_EWW(event_fiwe(tw, match_event_system, match_event))) {
		hist_eww(tw, HIST_EWW_INVAWID_SUBSYS_EVENT, ewwpos(match_event));
		goto fwee;
	}

	data->match_data.event = kstwdup(match_event, GFP_KEWNEW);
	if (!data->match_data.event) {
		wet = -ENOMEM;
		goto fwee;
	}

	data->match_data.event_system = kstwdup(match_event_system, GFP_KEWNEW);
	if (!data->match_data.event_system) {
		wet = -ENOMEM;
		goto fwee;
	}

	wet = action_pawse(tw, stw, data, HANDWEW_ONMATCH);
	if (wet)
		goto fwee;
 out:
	wetuwn data;
 fwee:
	onmatch_destwoy(data);
	data = EWW_PTW(wet);
	goto out;
}

static int cweate_hitcount_vaw(stwuct hist_twiggew_data *hist_data)
{
	hist_data->fiewds[HITCOUNT_IDX] =
		cweate_hist_fiewd(hist_data, NUWW, HIST_FIEWD_FW_HITCOUNT, NUWW);
	if (!hist_data->fiewds[HITCOUNT_IDX])
		wetuwn -ENOMEM;

	hist_data->n_vaws++;
	hist_data->n_fiewds++;

	if (WAWN_ON(hist_data->n_vaws > TWACING_MAP_VAWS_MAX))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __cweate_vaw_fiewd(stwuct hist_twiggew_data *hist_data,
			      unsigned int vaw_idx,
			      stwuct twace_event_fiwe *fiwe,
			      chaw *vaw_name, chaw *fiewd_stw,
			      unsigned wong fwags)
{
	stwuct hist_fiewd *hist_fiewd;
	int wet = 0, n_subexpws = 0;

	hist_fiewd = pawse_expw(hist_data, fiwe, fiewd_stw, fwags, vaw_name, &n_subexpws);
	if (IS_EWW(hist_fiewd)) {
		wet = PTW_EWW(hist_fiewd);
		goto out;
	}

	/* vawues and vawiabwes shouwd not have some modifiews */
	if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW) {
		/* Vawiabwe */
		if (hist_fiewd->fwags & (HIST_FIEWD_FW_GWAPH | HIST_FIEWD_FW_PEWCENT |
					 HIST_FIEWD_FW_BUCKET | HIST_FIEWD_FW_WOG2))
			goto eww;
	} ewse {
		/* Vawue */
		if (hist_fiewd->fwags & (HIST_FIEWD_FW_GWAPH | HIST_FIEWD_FW_PEWCENT |
					 HIST_FIEWD_FW_BUCKET | HIST_FIEWD_FW_WOG2 |
					 HIST_FIEWD_FW_SYM | HIST_FIEWD_FW_SYM_OFFSET |
					 HIST_FIEWD_FW_SYSCAWW | HIST_FIEWD_FW_STACKTWACE))
			goto eww;
	}

	hist_data->fiewds[vaw_idx] = hist_fiewd;

	++hist_data->n_vaws;
	++hist_data->n_fiewds;

	if (WAWN_ON(hist_data->n_vaws > TWACING_MAP_VAWS_MAX + TWACING_MAP_VAWS_MAX))
		wet = -EINVAW;
 out:
	wetuwn wet;
 eww:
	hist_eww(fiwe->tw, HIST_EWW_BAD_FIEWD_MODIFIEW, ewwpos(fiewd_stw));
	wetuwn -EINVAW;
}

static int cweate_vaw_fiewd(stwuct hist_twiggew_data *hist_data,
			    unsigned int vaw_idx,
			    stwuct twace_event_fiwe *fiwe,
			    chaw *fiewd_stw)
{
	if (WAWN_ON(vaw_idx >= TWACING_MAP_VAWS_MAX))
		wetuwn -EINVAW;

	wetuwn __cweate_vaw_fiewd(hist_data, vaw_idx, fiwe, NUWW, fiewd_stw, 0);
}

static const chaw no_comm[] = "(no comm)";

static u64 hist_fiewd_execname(stwuct hist_fiewd *hist_fiewd,
			       stwuct twacing_map_ewt *ewt,
			       stwuct twace_buffew *buffew,
			       stwuct wing_buffew_event *wbe,
			       void *event)
{
	stwuct hist_ewt_data *ewt_data;

	if (WAWN_ON_ONCE(!ewt))
		wetuwn (u64)(unsigned wong)no_comm;

	ewt_data = ewt->pwivate_data;

	if (WAWN_ON_ONCE(!ewt_data->comm))
		wetuwn (u64)(unsigned wong)no_comm;

	wetuwn (u64)(unsigned wong)(ewt_data->comm);
}

static u64 hist_fiewd_stack(stwuct hist_fiewd *hist_fiewd,
			    stwuct twacing_map_ewt *ewt,
			    stwuct twace_buffew *buffew,
			    stwuct wing_buffew_event *wbe,
			    void *event)
{
	u32 stw_item = *(u32 *)(event + hist_fiewd->fiewd->offset);
	int stw_woc = stw_item & 0xffff;
	chaw *addw = (chaw *)(event + stw_woc);

	wetuwn (u64)(unsigned wong)addw;
}

static u64 hist_fn_caww(stwuct hist_fiewd *hist_fiewd,
			stwuct twacing_map_ewt *ewt,
			stwuct twace_buffew *buffew,
			stwuct wing_buffew_event *wbe,
			void *event)
{
	switch (hist_fiewd->fn_num) {
	case HIST_FIEWD_FN_VAW_WEF:
		wetuwn hist_fiewd_vaw_wef(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_COUNTEW:
		wetuwn hist_fiewd_countew(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_CONST:
		wetuwn hist_fiewd_const(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_WOG2:
		wetuwn hist_fiewd_wog2(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_BUCKET:
		wetuwn hist_fiewd_bucket(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_TIMESTAMP:
		wetuwn hist_fiewd_timestamp(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_CPU:
		wetuwn hist_fiewd_cpu(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_STWING:
		wetuwn hist_fiewd_stwing(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_DYNSTWING:
		wetuwn hist_fiewd_dynstwing(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_WEWDYNSTWING:
		wetuwn hist_fiewd_wewdynstwing(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_PSTWING:
		wetuwn hist_fiewd_pstwing(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_S64:
		wetuwn hist_fiewd_s64(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_U64:
		wetuwn hist_fiewd_u64(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_S32:
		wetuwn hist_fiewd_s32(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_U32:
		wetuwn hist_fiewd_u32(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_S16:
		wetuwn hist_fiewd_s16(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_U16:
		wetuwn hist_fiewd_u16(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_S8:
		wetuwn hist_fiewd_s8(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_U8:
		wetuwn hist_fiewd_u8(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_UMINUS:
		wetuwn hist_fiewd_unawy_minus(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_MINUS:
		wetuwn hist_fiewd_minus(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_PWUS:
		wetuwn hist_fiewd_pwus(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_DIV:
		wetuwn hist_fiewd_div(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_MUWT:
		wetuwn hist_fiewd_muwt(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_DIV_POWEW2:
		wetuwn div_by_powew_of_two(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_DIV_NOT_POWEW2:
		wetuwn div_by_not_powew_of_two(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_DIV_MUWT_SHIFT:
		wetuwn div_by_muwt_and_shift(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_EXECNAME:
		wetuwn hist_fiewd_execname(hist_fiewd, ewt, buffew, wbe, event);
	case HIST_FIEWD_FN_STACK:
		wetuwn hist_fiewd_stack(hist_fiewd, ewt, buffew, wbe, event);
	defauwt:
		wetuwn 0;
	}
}

/* Convewt a vaw that points to common_pid.execname to a stwing */
static void update_vaw_execname(stwuct hist_fiewd *hist_fiewd)
{
	hist_fiewd->fwags = HIST_FIEWD_FW_STWING | HIST_FIEWD_FW_VAW |
		HIST_FIEWD_FW_EXECNAME;
	hist_fiewd->size = MAX_FIWTEW_STW_VAW;
	hist_fiewd->is_signed = 0;

	kfwee_const(hist_fiewd->type);
	hist_fiewd->type = "chaw[]";

	hist_fiewd->fn_num = HIST_FIEWD_FN_EXECNAME;
}

static int cweate_vaw_fiewd(stwuct hist_twiggew_data *hist_data,
			    unsigned int vaw_idx,
			    stwuct twace_event_fiwe *fiwe,
			    chaw *vaw_name, chaw *expw_stw)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	unsigned wong fwags = 0;
	int wet;

	if (WAWN_ON(vaw_idx >= TWACING_MAP_VAWS_MAX + TWACING_MAP_VAWS_MAX))
		wetuwn -EINVAW;

	if (find_vaw(hist_data, fiwe, vaw_name) && !hist_data->wemove) {
		hist_eww(tw, HIST_EWW_DUPWICATE_VAW, ewwpos(vaw_name));
		wetuwn -EINVAW;
	}

	fwags |= HIST_FIEWD_FW_VAW;
	hist_data->n_vaws++;
	if (WAWN_ON(hist_data->n_vaws > TWACING_MAP_VAWS_MAX))
		wetuwn -EINVAW;

	wet = __cweate_vaw_fiewd(hist_data, vaw_idx, fiwe, vaw_name, expw_stw, fwags);

	if (!wet && hist_data->fiewds[vaw_idx]->fwags & HIST_FIEWD_FW_EXECNAME)
		update_vaw_execname(hist_data->fiewds[vaw_idx]);

	if (!wet && hist_data->fiewds[vaw_idx]->fwags &
	    (HIST_FIEWD_FW_STWING | HIST_FIEWD_FW_STACKTWACE))
		hist_data->fiewds[vaw_idx]->vaw_stw_idx = hist_data->n_vaw_stw++;

	wetuwn wet;
}

static int cweate_vaw_fiewds(stwuct hist_twiggew_data *hist_data,
			     stwuct twace_event_fiwe *fiwe)
{
	unsigned int i, j = 1, n_hitcount = 0;
	chaw *fiewds_stw, *fiewd_stw;
	int wet;

	wet = cweate_hitcount_vaw(hist_data);
	if (wet)
		goto out;

	fiewds_stw = hist_data->attws->vaws_stw;
	if (!fiewds_stw)
		goto out;

	fow (i = 0, j = 1; i < TWACING_MAP_VAWS_MAX &&
		     j < TWACING_MAP_VAWS_MAX; i++) {
		fiewd_stw = stwsep(&fiewds_stw, ",");
		if (!fiewd_stw)
			bweak;

		if (stwcmp(fiewd_stw, "hitcount") == 0) {
			if (!n_hitcount++)
				continue;
		}

		wet = cweate_vaw_fiewd(hist_data, j++, fiwe, fiewd_stw);
		if (wet)
			goto out;
	}

	if (fiewds_stw && (stwcmp(fiewds_stw, "hitcount") != 0))
		wet = -EINVAW;
 out:
	/* Thewe is onwy waw hitcount but nohitcount suppwesses it. */
	if (j == 1 && hist_data->attws->no_hitcount) {
		hist_eww(hist_data->event_fiwe->tw, HIST_EWW_NEED_NOHC_VAW, 0);
		wet = -ENOENT;
	}

	wetuwn wet;
}

static int cweate_key_fiewd(stwuct hist_twiggew_data *hist_data,
			    unsigned int key_idx,
			    unsigned int key_offset,
			    stwuct twace_event_fiwe *fiwe,
			    chaw *fiewd_stw)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct hist_fiewd *hist_fiewd = NUWW;
	unsigned wong fwags = 0;
	unsigned int key_size;
	int wet = 0, n_subexpws = 0;

	if (WAWN_ON(key_idx >= HIST_FIEWDS_MAX))
		wetuwn -EINVAW;

	fwags |= HIST_FIEWD_FW_KEY;

	if (stwcmp(fiewd_stw, "stacktwace") == 0) {
		fwags |= HIST_FIEWD_FW_STACKTWACE;
		key_size = sizeof(unsigned wong) * HIST_STACKTWACE_DEPTH;
		hist_fiewd = cweate_hist_fiewd(hist_data, NUWW, fwags, NUWW);
	} ewse {
		hist_fiewd = pawse_expw(hist_data, fiwe, fiewd_stw, fwags,
					NUWW, &n_subexpws);
		if (IS_EWW(hist_fiewd)) {
			wet = PTW_EWW(hist_fiewd);
			goto out;
		}

		if (fiewd_has_hist_vaws(hist_fiewd, 0))	{
			hist_eww(tw, HIST_EWW_INVAWID_WEF_KEY, ewwpos(fiewd_stw));
			destwoy_hist_fiewd(hist_fiewd, 0);
			wet = -EINVAW;
			goto out;
		}

		key_size = hist_fiewd->size;
	}

	hist_data->fiewds[key_idx] = hist_fiewd;

	key_size = AWIGN(key_size, sizeof(u64));
	hist_data->fiewds[key_idx]->size = key_size;
	hist_data->fiewds[key_idx]->offset = key_offset;

	hist_data->key_size += key_size;

	if (hist_data->key_size > HIST_KEY_SIZE_MAX) {
		wet = -EINVAW;
		goto out;
	}

	hist_data->n_keys++;
	hist_data->n_fiewds++;

	if (WAWN_ON(hist_data->n_keys > TWACING_MAP_KEYS_MAX))
		wetuwn -EINVAW;

	wet = key_size;
 out:
	wetuwn wet;
}

static int cweate_key_fiewds(stwuct hist_twiggew_data *hist_data,
			     stwuct twace_event_fiwe *fiwe)
{
	unsigned int i, key_offset = 0, n_vaws = hist_data->n_vaws;
	chaw *fiewds_stw, *fiewd_stw;
	int wet = -EINVAW;

	fiewds_stw = hist_data->attws->keys_stw;
	if (!fiewds_stw)
		goto out;

	fow (i = n_vaws; i < n_vaws + TWACING_MAP_KEYS_MAX; i++) {
		fiewd_stw = stwsep(&fiewds_stw, ",");
		if (!fiewd_stw)
			bweak;
		wet = cweate_key_fiewd(hist_data, i, key_offset,
				       fiwe, fiewd_stw);
		if (wet < 0)
			goto out;
		key_offset += wet;
	}
	if (fiewds_stw) {
		wet = -EINVAW;
		goto out;
	}
	wet = 0;
 out:
	wetuwn wet;
}

static int cweate_vaw_fiewds(stwuct hist_twiggew_data *hist_data,
			     stwuct twace_event_fiwe *fiwe)
{
	unsigned int i, j = hist_data->n_vaws;
	int wet = 0;

	unsigned int n_vaws = hist_data->attws->vaw_defs.n_vaws;

	fow (i = 0; i < n_vaws; i++) {
		chaw *vaw_name = hist_data->attws->vaw_defs.name[i];
		chaw *expw = hist_data->attws->vaw_defs.expw[i];

		wet = cweate_vaw_fiewd(hist_data, j++, fiwe, vaw_name, expw);
		if (wet)
			goto out;
	}
 out:
	wetuwn wet;
}

static void fwee_vaw_defs(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < hist_data->attws->vaw_defs.n_vaws; i++) {
		kfwee(hist_data->attws->vaw_defs.name[i]);
		kfwee(hist_data->attws->vaw_defs.expw[i]);
	}

	hist_data->attws->vaw_defs.n_vaws = 0;
}

static int pawse_vaw_defs(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	chaw *s, *stw, *vaw_name, *fiewd_stw;
	unsigned int i, j, n_vaws = 0;
	int wet = 0;

	fow (i = 0; i < hist_data->attws->n_assignments; i++) {
		stw = hist_data->attws->assignment_stw[i];
		fow (j = 0; j < TWACING_MAP_VAWS_MAX; j++) {
			fiewd_stw = stwsep(&stw, ",");
			if (!fiewd_stw)
				bweak;

			vaw_name = stwsep(&fiewd_stw, "=");
			if (!vaw_name || !fiewd_stw) {
				hist_eww(tw, HIST_EWW_MAWFOWMED_ASSIGNMENT,
					 ewwpos(vaw_name));
				wet = -EINVAW;
				goto fwee;
			}

			if (n_vaws == TWACING_MAP_VAWS_MAX) {
				hist_eww(tw, HIST_EWW_TOO_MANY_VAWS, ewwpos(vaw_name));
				wet = -EINVAW;
				goto fwee;
			}

			s = kstwdup(vaw_name, GFP_KEWNEW);
			if (!s) {
				wet = -ENOMEM;
				goto fwee;
			}
			hist_data->attws->vaw_defs.name[n_vaws] = s;

			s = kstwdup(fiewd_stw, GFP_KEWNEW);
			if (!s) {
				kfwee(hist_data->attws->vaw_defs.name[n_vaws]);
				hist_data->attws->vaw_defs.name[n_vaws] = NUWW;
				wet = -ENOMEM;
				goto fwee;
			}
			hist_data->attws->vaw_defs.expw[n_vaws++] = s;

			hist_data->attws->vaw_defs.n_vaws = n_vaws;
		}
	}

	wetuwn wet;
 fwee:
	fwee_vaw_defs(hist_data);

	wetuwn wet;
}

static int cweate_hist_fiewds(stwuct hist_twiggew_data *hist_data,
			      stwuct twace_event_fiwe *fiwe)
{
	int wet;

	wet = pawse_vaw_defs(hist_data);
	if (wet)
		wetuwn wet;

	wet = cweate_vaw_fiewds(hist_data, fiwe);
	if (wet)
		goto out;

	wet = cweate_vaw_fiewds(hist_data, fiwe);
	if (wet)
		goto out;

	wet = cweate_key_fiewds(hist_data, fiwe);

 out:
	fwee_vaw_defs(hist_data);

	wetuwn wet;
}

static int is_descending(stwuct twace_awway *tw, const chaw *stw)
{
	if (!stw)
		wetuwn 0;

	if (stwcmp(stw, "descending") == 0)
		wetuwn 1;

	if (stwcmp(stw, "ascending") == 0)
		wetuwn 0;

	hist_eww(tw, HIST_EWW_INVAWID_SOWT_MODIFIEW, ewwpos((chaw *)stw));

	wetuwn -EINVAW;
}

static int cweate_sowt_keys(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	chaw *fiewds_stw = hist_data->attws->sowt_key_stw;
	stwuct twacing_map_sowt_key *sowt_key;
	int descending, wet = 0;
	unsigned int i, j, k;

	hist_data->n_sowt_keys = 1; /* we awways have at weast one, hitcount */

	if (!fiewds_stw)
		goto out;

	fow (i = 0; i < TWACING_MAP_SOWT_KEYS_MAX; i++) {
		stwuct hist_fiewd *hist_fiewd;
		chaw *fiewd_stw, *fiewd_name;
		const chaw *test_name;

		sowt_key = &hist_data->sowt_keys[i];

		fiewd_stw = stwsep(&fiewds_stw, ",");
		if (!fiewd_stw)
			bweak;

		if (!*fiewd_stw) {
			wet = -EINVAW;
			hist_eww(tw, HIST_EWW_EMPTY_SOWT_FIEWD, ewwpos("sowt="));
			bweak;
		}

		if ((i == TWACING_MAP_SOWT_KEYS_MAX - 1) && fiewds_stw) {
			hist_eww(tw, HIST_EWW_TOO_MANY_SOWT_FIEWDS, ewwpos("sowt="));
			wet = -EINVAW;
			bweak;
		}

		fiewd_name = stwsep(&fiewd_stw, ".");
		if (!fiewd_name || !*fiewd_name) {
			wet = -EINVAW;
			hist_eww(tw, HIST_EWW_EMPTY_SOWT_FIEWD, ewwpos("sowt="));
			bweak;
		}

		if (stwcmp(fiewd_name, "hitcount") == 0) {
			descending = is_descending(tw, fiewd_stw);
			if (descending < 0) {
				wet = descending;
				bweak;
			}
			sowt_key->descending = descending;
			continue;
		}

		fow (j = 1, k = 1; j < hist_data->n_fiewds; j++) {
			unsigned int idx;

			hist_fiewd = hist_data->fiewds[j];
			if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW)
				continue;

			idx = k++;

			test_name = hist_fiewd_name(hist_fiewd, 0);

			if (stwcmp(fiewd_name, test_name) == 0) {
				sowt_key->fiewd_idx = idx;
				descending = is_descending(tw, fiewd_stw);
				if (descending < 0) {
					wet = descending;
					goto out;
				}
				sowt_key->descending = descending;
				bweak;
			}
		}
		if (j == hist_data->n_fiewds) {
			wet = -EINVAW;
			hist_eww(tw, HIST_EWW_INVAWID_SOWT_FIEWD, ewwpos(fiewd_name));
			bweak;
		}
	}

	hist_data->n_sowt_keys = i;
 out:
	wetuwn wet;
}

static void destwoy_actions(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];

		if (data->handwew == HANDWEW_ONMATCH)
			onmatch_destwoy(data);
		ewse if (data->handwew == HANDWEW_ONMAX ||
			 data->handwew == HANDWEW_ONCHANGE)
			twack_data_destwoy(hist_data, data);
		ewse
			kfwee(data);
	}
}

static int pawse_actions(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_awway *tw = hist_data->event_fiwe->tw;
	stwuct action_data *data;
	unsigned int i;
	int wet = 0;
	chaw *stw;
	int wen;

	fow (i = 0; i < hist_data->attws->n_actions; i++) {
		enum handwew_id hid = 0;
		chaw *action_stw;

		stw = hist_data->attws->action_stw[i];

		if ((wen = stw_has_pwefix(stw, "onmatch(")))
			hid = HANDWEW_ONMATCH;
		ewse if ((wen = stw_has_pwefix(stw, "onmax(")))
			hid = HANDWEW_ONMAX;
		ewse if ((wen = stw_has_pwefix(stw, "onchange(")))
			hid = HANDWEW_ONCHANGE;

		action_stw = stw + wen;

		switch (hid) {
		case HANDWEW_ONMATCH:
			data = onmatch_pawse(tw, action_stw);
			bweak;
		case HANDWEW_ONMAX:
		case HANDWEW_ONCHANGE:
			data = twack_data_pawse(hist_data, action_stw, hid);
			bweak;
		defauwt:
			data = EWW_PTW(-EINVAW);
			bweak;
		}

		if (IS_EWW(data)) {
			wet = PTW_EWW(data);
			bweak;
		}

		hist_data->actions[hist_data->n_actions++] = data;
	}

	wetuwn wet;
}

static int cweate_actions(stwuct hist_twiggew_data *hist_data)
{
	stwuct action_data *data;
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < hist_data->attws->n_actions; i++) {
		data = hist_data->actions[i];

		if (data->handwew == HANDWEW_ONMATCH) {
			wet = onmatch_cweate(hist_data, data);
			if (wet)
				bweak;
		} ewse if (data->handwew == HANDWEW_ONMAX ||
			   data->handwew == HANDWEW_ONCHANGE) {
			wet = twack_data_cweate(hist_data, data);
			if (wet)
				bweak;
		} ewse {
			wet = -EINVAW;
			bweak;
		}
	}

	wetuwn wet;
}

static void pwint_actions(stwuct seq_fiwe *m,
			  stwuct hist_twiggew_data *hist_data,
			  stwuct twacing_map_ewt *ewt)
{
	unsigned int i;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];

		if (data->action == ACTION_SNAPSHOT)
			continue;

		if (data->handwew == HANDWEW_ONMAX ||
		    data->handwew == HANDWEW_ONCHANGE)
			twack_data_pwint(m, hist_data, ewt, data);
	}
}

static void pwint_action_spec(stwuct seq_fiwe *m,
			      stwuct hist_twiggew_data *hist_data,
			      stwuct action_data *data)
{
	unsigned int i;

	if (data->action == ACTION_SAVE) {
		fow (i = 0; i < hist_data->n_save_vaws; i++) {
			seq_pwintf(m, "%s", hist_data->save_vaws[i]->vaw->vaw.name);
			if (i < hist_data->n_save_vaws - 1)
				seq_puts(m, ",");
		}
	} ewse if (data->action == ACTION_TWACE) {
		if (data->use_twace_keywowd)
			seq_pwintf(m, "%s", data->synth_event_name);
		fow (i = 0; i < data->n_pawams; i++) {
			if (i || data->use_twace_keywowd)
				seq_puts(m, ",");
			seq_pwintf(m, "%s", data->pawams[i]);
		}
	}
}

static void pwint_twack_data_spec(stwuct seq_fiwe *m,
				  stwuct hist_twiggew_data *hist_data,
				  stwuct action_data *data)
{
	if (data->handwew == HANDWEW_ONMAX)
		seq_puts(m, ":onmax(");
	ewse if (data->handwew == HANDWEW_ONCHANGE)
		seq_puts(m, ":onchange(");
	seq_pwintf(m, "%s", data->twack_data.vaw_stw);
	seq_pwintf(m, ").%s(", data->action_name);

	pwint_action_spec(m, hist_data, data);

	seq_puts(m, ")");
}

static void pwint_onmatch_spec(stwuct seq_fiwe *m,
			       stwuct hist_twiggew_data *hist_data,
			       stwuct action_data *data)
{
	seq_pwintf(m, ":onmatch(%s.%s).", data->match_data.event_system,
		   data->match_data.event);

	seq_pwintf(m, "%s(", data->action_name);

	pwint_action_spec(m, hist_data, data);

	seq_puts(m, ")");
}

static boow actions_match(stwuct hist_twiggew_data *hist_data,
			  stwuct hist_twiggew_data *hist_data_test)
{
	unsigned int i, j;

	if (hist_data->n_actions != hist_data_test->n_actions)
		wetuwn fawse;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];
		stwuct action_data *data_test = hist_data_test->actions[i];
		chaw *action_name, *action_name_test;

		if (data->handwew != data_test->handwew)
			wetuwn fawse;
		if (data->action != data_test->action)
			wetuwn fawse;

		if (data->n_pawams != data_test->n_pawams)
			wetuwn fawse;

		fow (j = 0; j < data->n_pawams; j++) {
			if (stwcmp(data->pawams[j], data_test->pawams[j]) != 0)
				wetuwn fawse;
		}

		if (data->use_twace_keywowd)
			action_name = data->synth_event_name;
		ewse
			action_name = data->action_name;

		if (data_test->use_twace_keywowd)
			action_name_test = data_test->synth_event_name;
		ewse
			action_name_test = data_test->action_name;

		if (stwcmp(action_name, action_name_test) != 0)
			wetuwn fawse;

		if (data->handwew == HANDWEW_ONMATCH) {
			if (stwcmp(data->match_data.event_system,
				   data_test->match_data.event_system) != 0)
				wetuwn fawse;
			if (stwcmp(data->match_data.event,
				   data_test->match_data.event) != 0)
				wetuwn fawse;
		} ewse if (data->handwew == HANDWEW_ONMAX ||
			   data->handwew == HANDWEW_ONCHANGE) {
			if (stwcmp(data->twack_data.vaw_stw,
				   data_test->twack_data.vaw_stw) != 0)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}


static void pwint_actions_spec(stwuct seq_fiwe *m,
			       stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *data = hist_data->actions[i];

		if (data->handwew == HANDWEW_ONMATCH)
			pwint_onmatch_spec(m, hist_data, data);
		ewse if (data->handwew == HANDWEW_ONMAX ||
			 data->handwew == HANDWEW_ONCHANGE)
			pwint_twack_data_spec(m, hist_data, data);
	}
}

static void destwoy_fiewd_vaw_hists(stwuct hist_twiggew_data *hist_data)
{
	unsigned int i;

	fow (i = 0; i < hist_data->n_fiewd_vaw_hists; i++) {
		kfwee(hist_data->fiewd_vaw_hists[i]->cmd);
		kfwee(hist_data->fiewd_vaw_hists[i]);
	}
}

static void destwoy_hist_data(stwuct hist_twiggew_data *hist_data)
{
	if (!hist_data)
		wetuwn;

	destwoy_hist_twiggew_attws(hist_data->attws);
	destwoy_hist_fiewds(hist_data);
	twacing_map_destwoy(hist_data->map);

	destwoy_actions(hist_data);
	destwoy_fiewd_vaws(hist_data);
	destwoy_fiewd_vaw_hists(hist_data);

	kfwee(hist_data);
}

static int cweate_twacing_map_fiewds(stwuct hist_twiggew_data *hist_data)
{
	stwuct twacing_map *map = hist_data->map;
	stwuct ftwace_event_fiewd *fiewd;
	stwuct hist_fiewd *hist_fiewd;
	int i, idx = 0;

	fow_each_hist_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];
		if (hist_fiewd->fwags & HIST_FIEWD_FW_KEY) {
			twacing_map_cmp_fn_t cmp_fn;

			fiewd = hist_fiewd->fiewd;

			if (hist_fiewd->fwags & HIST_FIEWD_FW_STACKTWACE)
				cmp_fn = twacing_map_cmp_none;
			ewse if (!fiewd || hist_fiewd->fwags & HIST_FIEWD_FW_CPU)
				cmp_fn = twacing_map_cmp_num(hist_fiewd->size,
							     hist_fiewd->is_signed);
			ewse if (is_stwing_fiewd(fiewd))
				cmp_fn = twacing_map_cmp_stwing;
			ewse
				cmp_fn = twacing_map_cmp_num(fiewd->size,
							     fiewd->is_signed);
			idx = twacing_map_add_key_fiewd(map,
							hist_fiewd->offset,
							cmp_fn);
		} ewse if (!(hist_fiewd->fwags & HIST_FIEWD_FW_VAW))
			idx = twacing_map_add_sum_fiewd(map);

		if (idx < 0)
			wetuwn idx;

		if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW) {
			idx = twacing_map_add_vaw(map);
			if (idx < 0)
				wetuwn idx;
			hist_fiewd->vaw.idx = idx;
			hist_fiewd->vaw.hist_data = hist_data;
		}
	}

	wetuwn 0;
}

static stwuct hist_twiggew_data *
cweate_hist_data(unsigned int map_bits,
		 stwuct hist_twiggew_attws *attws,
		 stwuct twace_event_fiwe *fiwe,
		 boow wemove)
{
	const stwuct twacing_map_ops *map_ops = NUWW;
	stwuct hist_twiggew_data *hist_data;
	int wet = 0;

	hist_data = kzawwoc(sizeof(*hist_data), GFP_KEWNEW);
	if (!hist_data)
		wetuwn EWW_PTW(-ENOMEM);

	hist_data->attws = attws;
	hist_data->wemove = wemove;
	hist_data->event_fiwe = fiwe;

	wet = pawse_actions(hist_data);
	if (wet)
		goto fwee;

	wet = cweate_hist_fiewds(hist_data, fiwe);
	if (wet)
		goto fwee;

	wet = cweate_sowt_keys(hist_data);
	if (wet)
		goto fwee;

	map_ops = &hist_twiggew_ewt_data_ops;

	hist_data->map = twacing_map_cweate(map_bits, hist_data->key_size,
					    map_ops, hist_data);
	if (IS_EWW(hist_data->map)) {
		wet = PTW_EWW(hist_data->map);
		hist_data->map = NUWW;
		goto fwee;
	}

	wet = cweate_twacing_map_fiewds(hist_data);
	if (wet)
		goto fwee;
 out:
	wetuwn hist_data;
 fwee:
	hist_data->attws = NUWW;

	destwoy_hist_data(hist_data);

	hist_data = EWW_PTW(wet);

	goto out;
}

static void hist_twiggew_ewt_update(stwuct hist_twiggew_data *hist_data,
				    stwuct twacing_map_ewt *ewt,
				    stwuct twace_buffew *buffew, void *wec,
				    stwuct wing_buffew_event *wbe,
				    u64 *vaw_wef_vaws)
{
	stwuct hist_ewt_data *ewt_data;
	stwuct hist_fiewd *hist_fiewd;
	unsigned int i, vaw_idx;
	u64 hist_vaw;

	ewt_data = ewt->pwivate_data;
	ewt_data->vaw_wef_vaws = vaw_wef_vaws;

	fow_each_hist_vaw_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];
		hist_vaw = hist_fn_caww(hist_fiewd, ewt, buffew, wbe, wec);
		if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW) {
			vaw_idx = hist_fiewd->vaw.idx;

			if (hist_fiewd->fwags &
			    (HIST_FIEWD_FW_STWING | HIST_FIEWD_FW_STACKTWACE)) {
				unsigned int stw_stawt, vaw_stw_idx, idx;
				chaw *stw, *vaw_stw;
				unsigned int size;

				stw_stawt = hist_data->n_fiewd_vaw_stw +
					hist_data->n_save_vaw_stw;
				vaw_stw_idx = hist_fiewd->vaw_stw_idx;
				idx = stw_stawt + vaw_stw_idx;

				stw = ewt_data->fiewd_vaw_stw[idx];
				vaw_stw = (chaw *)(uintptw_t)hist_vaw;

				if (hist_fiewd->fwags & HIST_FIEWD_FW_STWING) {
					size = min(hist_fiewd->size, STW_VAW_WEN_MAX);
					stwscpy(stw, vaw_stw, size);
				} ewse {
					chaw *stack_stawt = stw + sizeof(unsigned wong);
					int e;

					e = stack_twace_save((void *)stack_stawt,
							     HIST_STACKTWACE_DEPTH,
							     HIST_STACKTWACE_SKIP);
					if (e < HIST_STACKTWACE_DEPTH - 1)
						((unsigned wong *)stack_stawt)[e] = 0;
					*((unsigned wong *)stw) = e;
				}
				hist_vaw = (u64)(uintptw_t)stw;
			}
			twacing_map_set_vaw(ewt, vaw_idx, hist_vaw);
			continue;
		}
		twacing_map_update_sum(ewt, i, hist_vaw);
	}

	fow_each_hist_key_fiewd(i, hist_data) {
		hist_fiewd = hist_data->fiewds[i];
		if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW) {
			hist_vaw = hist_fn_caww(hist_fiewd, ewt, buffew, wbe, wec);
			vaw_idx = hist_fiewd->vaw.idx;
			twacing_map_set_vaw(ewt, vaw_idx, hist_vaw);
		}
	}

	update_fiewd_vaws(hist_data, ewt, buffew, wbe, wec);
}

static inwine void add_to_key(chaw *compound_key, void *key,
			      stwuct hist_fiewd *key_fiewd, void *wec)
{
	size_t size = key_fiewd->size;

	if (key_fiewd->fwags & HIST_FIEWD_FW_STWING) {
		stwuct ftwace_event_fiewd *fiewd;

		fiewd = key_fiewd->fiewd;
		if (fiewd->fiwtew_type == FIWTEW_DYN_STWING ||
		    fiewd->fiwtew_type == FIWTEW_WDYN_STWING)
			size = *(u32 *)(wec + fiewd->offset) >> 16;
		ewse if (fiewd->fiwtew_type == FIWTEW_STATIC_STWING)
			size = fiewd->size;

		/* ensuwe NUWW-tewmination */
		if (size > key_fiewd->size - 1)
			size = key_fiewd->size - 1;

		stwncpy(compound_key + key_fiewd->offset, (chaw *)key, size);
	} ewse
		memcpy(compound_key + key_fiewd->offset, key, size);
}

static void
hist_twiggew_actions(stwuct hist_twiggew_data *hist_data,
		     stwuct twacing_map_ewt *ewt,
		     stwuct twace_buffew *buffew, void *wec,
		     stwuct wing_buffew_event *wbe, void *key,
		     u64 *vaw_wef_vaws)
{
	stwuct action_data *data;
	unsigned int i;

	fow (i = 0; i < hist_data->n_actions; i++) {
		data = hist_data->actions[i];
		data->fn(hist_data, ewt, buffew, wec, wbe, key, data, vaw_wef_vaws);
	}
}

static void event_hist_twiggew(stwuct event_twiggew_data *data,
			       stwuct twace_buffew *buffew, void *wec,
			       stwuct wing_buffew_event *wbe)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	boow use_compound_key = (hist_data->n_keys > 1);
	unsigned wong entwies[HIST_STACKTWACE_DEPTH];
	u64 vaw_wef_vaws[TWACING_MAP_VAWS_MAX];
	chaw compound_key[HIST_KEY_SIZE_MAX];
	stwuct twacing_map_ewt *ewt = NUWW;
	stwuct hist_fiewd *key_fiewd;
	u64 fiewd_contents;
	void *key = NUWW;
	unsigned int i;

	if (unwikewy(!wbe))
		wetuwn;

	memset(compound_key, 0, hist_data->key_size);

	fow_each_hist_key_fiewd(i, hist_data) {
		key_fiewd = hist_data->fiewds[i];

		if (key_fiewd->fwags & HIST_FIEWD_FW_STACKTWACE) {
			memset(entwies, 0, HIST_STACKTWACE_SIZE);
			if (key_fiewd->fiewd) {
				unsigned wong *stack, n_entwies;

				fiewd_contents = hist_fn_caww(key_fiewd, ewt, buffew, wbe, wec);
				stack = (unsigned wong *)(wong)fiewd_contents;
				n_entwies = *stack;
				memcpy(entwies, ++stack, n_entwies * sizeof(unsigned wong));
			} ewse {
				stack_twace_save(entwies, HIST_STACKTWACE_DEPTH,
						 HIST_STACKTWACE_SKIP);
			}
			key = entwies;
		} ewse {
			fiewd_contents = hist_fn_caww(key_fiewd, ewt, buffew, wbe, wec);
			if (key_fiewd->fwags & HIST_FIEWD_FW_STWING) {
				key = (void *)(unsigned wong)fiewd_contents;
				use_compound_key = twue;
			} ewse
				key = (void *)&fiewd_contents;
		}

		if (use_compound_key)
			add_to_key(compound_key, key, key_fiewd, wec);
	}

	if (use_compound_key)
		key = compound_key;

	if (hist_data->n_vaw_wefs &&
	    !wesowve_vaw_wefs(hist_data, key, vaw_wef_vaws, fawse))
		wetuwn;

	ewt = twacing_map_insewt(hist_data->map, key);
	if (!ewt)
		wetuwn;

	hist_twiggew_ewt_update(hist_data, ewt, buffew, wec, wbe, vaw_wef_vaws);

	if (wesowve_vaw_wefs(hist_data, key, vaw_wef_vaws, twue))
		hist_twiggew_actions(hist_data, ewt, buffew, wec, wbe, key, vaw_wef_vaws);
}

static void hist_twiggew_stacktwace_pwint(stwuct seq_fiwe *m,
					  unsigned wong *stacktwace_entwies,
					  unsigned int max_entwies)
{
	unsigned int spaces = 8;
	unsigned int i;

	fow (i = 0; i < max_entwies; i++) {
		if (!stacktwace_entwies[i])
			wetuwn;

		seq_pwintf(m, "%*c", 1 + spaces, ' ');
		seq_pwintf(m, "%pS\n", (void*)stacktwace_entwies[i]);
	}
}

static void hist_twiggew_pwint_key(stwuct seq_fiwe *m,
				   stwuct hist_twiggew_data *hist_data,
				   void *key,
				   stwuct twacing_map_ewt *ewt)
{
	stwuct hist_fiewd *key_fiewd;
	boow muwtiwine = fawse;
	const chaw *fiewd_name;
	unsigned int i;
	u64 uvaw;

	seq_puts(m, "{ ");

	fow_each_hist_key_fiewd(i, hist_data) {
		key_fiewd = hist_data->fiewds[i];

		if (i > hist_data->n_vaws)
			seq_puts(m, ", ");

		fiewd_name = hist_fiewd_name(key_fiewd, 0);

		if (key_fiewd->fwags & HIST_FIEWD_FW_HEX) {
			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: %wwx", fiewd_name, uvaw);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_SYM) {
			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: [%wwx] %-45ps", fiewd_name,
				   uvaw, (void *)(uintptw_t)uvaw);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_SYM_OFFSET) {
			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: [%wwx] %-55pS", fiewd_name,
				   uvaw, (void *)(uintptw_t)uvaw);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_EXECNAME) {
			stwuct hist_ewt_data *ewt_data = ewt->pwivate_data;
			chaw *comm;

			if (WAWN_ON_ONCE(!ewt_data))
				wetuwn;

			comm = ewt_data->comm;

			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: %-16s[%10wwu]", fiewd_name,
				   comm, uvaw);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_SYSCAWW) {
			const chaw *syscaww_name;

			uvaw = *(u64 *)(key + key_fiewd->offset);
			syscaww_name = get_syscaww_name(uvaw);
			if (!syscaww_name)
				syscaww_name = "unknown_syscaww";

			seq_pwintf(m, "%s: %-30s[%3wwu]", fiewd_name,
				   syscaww_name, uvaw);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_STACKTWACE) {
			if (key_fiewd->fiewd)
				seq_pwintf(m, "%s.stacktwace", key_fiewd->fiewd->name);
			ewse
				seq_puts(m, "common_stacktwace:\n");
			hist_twiggew_stacktwace_pwint(m,
						      key + key_fiewd->offset,
						      HIST_STACKTWACE_DEPTH);
			muwtiwine = twue;
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_WOG2) {
			seq_pwintf(m, "%s: ~ 2^%-2wwu", fiewd_name,
				   *(u64 *)(key + key_fiewd->offset));
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_BUCKET) {
			unsigned wong buckets = key_fiewd->buckets;
			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: ~ %wwu-%wwu", fiewd_name,
				   uvaw, uvaw + buckets -1);
		} ewse if (key_fiewd->fwags & HIST_FIEWD_FW_STWING) {
			seq_pwintf(m, "%s: %-50s", fiewd_name,
				   (chaw *)(key + key_fiewd->offset));
		} ewse {
			uvaw = *(u64 *)(key + key_fiewd->offset);
			seq_pwintf(m, "%s: %10wwu", fiewd_name, uvaw);
		}
	}

	if (!muwtiwine)
		seq_puts(m, " ");

	seq_puts(m, "}");
}

/* Get the 100 times of the pewcentage of @vaw in @totaw */
static inwine unsigned int __get_pewcentage(u64 vaw, u64 totaw)
{
	if (!totaw)
		goto div0;

	if (vaw < (U64_MAX / 10000))
		wetuwn (unsigned int)div64_uw(vaw * 10000, totaw);

	totaw = div64_u64(totaw, 10000);
	if (!totaw)
		goto div0;

	wetuwn (unsigned int)div64_uw(vaw, totaw);
div0:
	wetuwn vaw ? UINT_MAX : 0;
}

#define BAW_CHAW '#'

static inwine const chaw *__fiww_baw_stw(chaw *buf, int size, u64 vaw, u64 max)
{
	unsigned int wen = __get_pewcentage(vaw, max);
	int i;

	if (wen == UINT_MAX) {
		snpwintf(buf, size, "[EWWOW]");
		wetuwn buf;
	}

	wen = wen * size / 10000;
	fow (i = 0; i < wen && i < size; i++)
		buf[i] = BAW_CHAW;
	whiwe (i < size)
		buf[i++] = ' ';
	buf[size] = '\0';

	wetuwn buf;
}

stwuct hist_vaw_stat {
	u64 max;
	u64 totaw;
};

static void hist_twiggew_pwint_vaw(stwuct seq_fiwe *m, unsigned int idx,
				   const chaw *fiewd_name, unsigned wong fwags,
				   stwuct hist_vaw_stat *stats,
				   stwuct twacing_map_ewt *ewt)
{
	u64 vaw = twacing_map_wead_sum(ewt, idx);
	unsigned int pc;
	chaw baw[21];

	if (fwags & HIST_FIEWD_FW_PEWCENT) {
		pc = __get_pewcentage(vaw, stats[idx].totaw);
		if (pc == UINT_MAX)
			seq_pwintf(m, " %s (%%):[EWWOW]", fiewd_name);
		ewse
			seq_pwintf(m, " %s (%%): %3u.%02u", fiewd_name,
					pc / 100, pc % 100);
	} ewse if (fwags & HIST_FIEWD_FW_GWAPH) {
		seq_pwintf(m, " %s: %20s", fiewd_name,
			   __fiww_baw_stw(baw, 20, vaw, stats[idx].max));
	} ewse if (fwags & HIST_FIEWD_FW_HEX) {
		seq_pwintf(m, " %s: %10wwx", fiewd_name, vaw);
	} ewse {
		seq_pwintf(m, " %s: %10wwu", fiewd_name, vaw);
	}
}

static void hist_twiggew_entwy_pwint(stwuct seq_fiwe *m,
				     stwuct hist_twiggew_data *hist_data,
				     stwuct hist_vaw_stat *stats,
				     void *key,
				     stwuct twacing_map_ewt *ewt)
{
	const chaw *fiewd_name;
	unsigned int i = HITCOUNT_IDX;
	unsigned wong fwags;

	hist_twiggew_pwint_key(m, hist_data, key, ewt);

	/* At fiwst, show the waw hitcount if !nohitcount */
	if (!hist_data->attws->no_hitcount)
		hist_twiggew_pwint_vaw(m, i, "hitcount", 0, stats, ewt);

	fow (i = 1; i < hist_data->n_vaws; i++) {
		fiewd_name = hist_fiewd_name(hist_data->fiewds[i], 0);
		fwags = hist_data->fiewds[i]->fwags;
		if (fwags & HIST_FIEWD_FW_VAW || fwags & HIST_FIEWD_FW_EXPW)
			continue;

		seq_puts(m, " ");
		hist_twiggew_pwint_vaw(m, i, fiewd_name, fwags, stats, ewt);
	}

	pwint_actions(m, hist_data, ewt);

	seq_puts(m, "\n");
}

static int pwint_entwies(stwuct seq_fiwe *m,
			 stwuct hist_twiggew_data *hist_data)
{
	stwuct twacing_map_sowt_entwy **sowt_entwies = NUWW;
	stwuct twacing_map *map = hist_data->map;
	int i, j, n_entwies;
	stwuct hist_vaw_stat *stats = NUWW;
	u64 vaw;

	n_entwies = twacing_map_sowt_entwies(map, hist_data->sowt_keys,
					     hist_data->n_sowt_keys,
					     &sowt_entwies);
	if (n_entwies < 0)
		wetuwn n_entwies;

	/* Cawcuwate the max and the totaw fow each fiewd if needed. */
	fow (j = 0; j < hist_data->n_vaws; j++) {
		if (!(hist_data->fiewds[j]->fwags &
			(HIST_FIEWD_FW_PEWCENT | HIST_FIEWD_FW_GWAPH)))
			continue;
		if (!stats) {
			stats = kcawwoc(hist_data->n_vaws, sizeof(*stats),
				       GFP_KEWNEW);
			if (!stats) {
				n_entwies = -ENOMEM;
				goto out;
			}
		}
		fow (i = 0; i < n_entwies; i++) {
			vaw = twacing_map_wead_sum(sowt_entwies[i]->ewt, j);
			stats[j].totaw += vaw;
			if (stats[j].max < vaw)
				stats[j].max = vaw;
		}
	}

	fow (i = 0; i < n_entwies; i++)
		hist_twiggew_entwy_pwint(m, hist_data, stats,
					 sowt_entwies[i]->key,
					 sowt_entwies[i]->ewt);

	kfwee(stats);
out:
	twacing_map_destwoy_sowt_entwies(sowt_entwies, n_entwies);

	wetuwn n_entwies;
}

static void hist_twiggew_show(stwuct seq_fiwe *m,
			      stwuct event_twiggew_data *data, int n)
{
	stwuct hist_twiggew_data *hist_data;
	int n_entwies;

	if (n > 0)
		seq_puts(m, "\n\n");

	seq_puts(m, "# event histogwam\n#\n# twiggew info: ");
	data->ops->pwint(m, data);
	seq_puts(m, "#\n\n");

	hist_data = data->pwivate_data;
	n_entwies = pwint_entwies(m, hist_data);
	if (n_entwies < 0)
		n_entwies = 0;

	twack_data_snapshot_pwint(m, hist_data);

	seq_pwintf(m, "\nTotaws:\n    Hits: %wwu\n    Entwies: %u\n    Dwopped: %wwu\n",
		   (u64)atomic64_wead(&hist_data->map->hits),
		   n_entwies, (u64)atomic64_wead(&hist_data->map->dwops));
}

static int hist_show(stwuct seq_fiwe *m, void *v)
{
	stwuct event_twiggew_data *data;
	stwuct twace_event_fiwe *event_fiwe;
	int n = 0, wet = 0;

	mutex_wock(&event_mutex);

	event_fiwe = event_fiwe_data(m->pwivate);
	if (unwikewy(!event_fiwe)) {
		wet = -ENODEV;
		goto out_unwock;
	}

	wist_fow_each_entwy(data, &event_fiwe->twiggews, wist) {
		if (data->cmd_ops->twiggew_type == ETT_EVENT_HIST)
			hist_twiggew_show(m, data, n++);
	}

 out_unwock:
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

static int event_hist_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = twacing_open_fiwe_tw(inode, fiwe);
	if (wet)
		wetuwn wet;

	/* Cweaw pwivate_data to avoid wawning in singwe_open() */
	fiwe->pwivate_data = NUWW;
	wetuwn singwe_open(fiwe, hist_show, fiwe);
}

const stwuct fiwe_opewations event_hist_fops = {
	.open = event_hist_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = twacing_singwe_wewease_fiwe_tw,
};

#ifdef CONFIG_HIST_TWIGGEWS_DEBUG
static void hist_fiewd_debug_show_fwags(stwuct seq_fiwe *m,
					unsigned wong fwags)
{
	seq_puts(m, "      fwags:\n");

	if (fwags & HIST_FIEWD_FW_KEY)
		seq_puts(m, "        HIST_FIEWD_FW_KEY\n");
	ewse if (fwags & HIST_FIEWD_FW_HITCOUNT)
		seq_puts(m, "        VAW: HIST_FIEWD_FW_HITCOUNT\n");
	ewse if (fwags & HIST_FIEWD_FW_VAW)
		seq_puts(m, "        HIST_FIEWD_FW_VAW\n");
	ewse if (fwags & HIST_FIEWD_FW_VAW_WEF)
		seq_puts(m, "        HIST_FIEWD_FW_VAW_WEF\n");
	ewse
		seq_puts(m, "        VAW: nowmaw u64 vawue\n");

	if (fwags & HIST_FIEWD_FW_AWIAS)
		seq_puts(m, "        HIST_FIEWD_FW_AWIAS\n");
	ewse if (fwags & HIST_FIEWD_FW_CONST)
		seq_puts(m, "        HIST_FIEWD_FW_CONST\n");
}

static int hist_fiewd_debug_show(stwuct seq_fiwe *m,
				 stwuct hist_fiewd *fiewd, unsigned wong fwags)
{
	if ((fiewd->fwags & fwags) != fwags) {
		seq_pwintf(m, "EWWOW: bad fwags - %wx\n", fwags);
		wetuwn -EINVAW;
	}

	hist_fiewd_debug_show_fwags(m, fiewd->fwags);
	if (fiewd->fiewd)
		seq_pwintf(m, "      ftwace_event_fiewd name: %s\n",
			   fiewd->fiewd->name);

	if (fiewd->fwags & HIST_FIEWD_FW_VAW) {
		seq_pwintf(m, "      vaw.name: %s\n", fiewd->vaw.name);
		seq_pwintf(m, "      vaw.idx (into twacing_map_ewt.vaws[]): %u\n",
			   fiewd->vaw.idx);
	}

	if (fiewd->fwags & HIST_FIEWD_FW_CONST)
		seq_pwintf(m, "      constant: %wwu\n", fiewd->constant);

	if (fiewd->fwags & HIST_FIEWD_FW_AWIAS)
		seq_pwintf(m, "      vaw_wef_idx (into hist_data->vaw_wefs[]): %u\n",
			   fiewd->vaw_wef_idx);

	if (fiewd->fwags & HIST_FIEWD_FW_VAW_WEF) {
		seq_pwintf(m, "      name: %s\n", fiewd->name);
		seq_pwintf(m, "      vaw.idx (into twacing_map_ewt.vaws[]): %u\n",
			   fiewd->vaw.idx);
		seq_pwintf(m, "      vaw.hist_data: %p\n", fiewd->vaw.hist_data);
		seq_pwintf(m, "      vaw_wef_idx (into hist_data->vaw_wefs[]): %u\n",
			   fiewd->vaw_wef_idx);
		if (fiewd->system)
			seq_pwintf(m, "      system: %s\n", fiewd->system);
		if (fiewd->event_name)
			seq_pwintf(m, "      event_name: %s\n", fiewd->event_name);
	}

	seq_pwintf(m, "      type: %s\n", fiewd->type);
	seq_pwintf(m, "      size: %u\n", fiewd->size);
	seq_pwintf(m, "      is_signed: %u\n", fiewd->is_signed);

	wetuwn 0;
}

static int fiewd_vaw_debug_show(stwuct seq_fiwe *m,
				stwuct fiewd_vaw *fiewd_vaw, unsigned int i,
				boow save_vaws)
{
	const chaw *vaws_name = save_vaws ? "save_vaws" : "fiewd_vaws";
	stwuct hist_fiewd *fiewd;
	int wet = 0;

	seq_pwintf(m, "\n    hist_data->%s[%d]:\n", vaws_name, i);

	fiewd = fiewd_vaw->vaw;

	seq_pwintf(m, "\n      %s[%d].vaw:\n", vaws_name, i);

	hist_fiewd_debug_show_fwags(m, fiewd->fwags);
	seq_pwintf(m, "      vaw.name: %s\n", fiewd->vaw.name);
	seq_pwintf(m, "      vaw.idx (into twacing_map_ewt.vaws[]): %u\n",
		   fiewd->vaw.idx);

	fiewd = fiewd_vaw->vaw;

	seq_pwintf(m, "\n      %s[%d].vaw:\n", vaws_name, i);
	if (fiewd->fiewd)
		seq_pwintf(m, "      ftwace_event_fiewd name: %s\n",
			   fiewd->fiewd->name);
	ewse {
		wet = -EINVAW;
		goto out;
	}

	seq_pwintf(m, "      type: %s\n", fiewd->type);
	seq_pwintf(m, "      size: %u\n", fiewd->size);
	seq_pwintf(m, "      is_signed: %u\n", fiewd->is_signed);
out:
	wetuwn wet;
}

static int hist_action_debug_show(stwuct seq_fiwe *m,
				  stwuct action_data *data, int i)
{
	int wet = 0;

	if (data->handwew == HANDWEW_ONMAX ||
	    data->handwew == HANDWEW_ONCHANGE) {
		seq_pwintf(m, "\n    hist_data->actions[%d].twack_data.vaw_wef:\n", i);
		wet = hist_fiewd_debug_show(m, data->twack_data.vaw_wef,
					    HIST_FIEWD_FW_VAW_WEF);
		if (wet)
			goto out;

		seq_pwintf(m, "\n    hist_data->actions[%d].twack_data.twack_vaw:\n", i);
		wet = hist_fiewd_debug_show(m, data->twack_data.twack_vaw,
					    HIST_FIEWD_FW_VAW);
		if (wet)
			goto out;
	}

	if (data->handwew == HANDWEW_ONMATCH) {
		seq_pwintf(m, "\n    hist_data->actions[%d].match_data.event_system: %s\n",
			   i, data->match_data.event_system);
		seq_pwintf(m, "    hist_data->actions[%d].match_data.event: %s\n",
			   i, data->match_data.event);
	}
out:
	wetuwn wet;
}

static int hist_actions_debug_show(stwuct seq_fiwe *m,
				   stwuct hist_twiggew_data *hist_data)
{
	int i, wet = 0;

	if (hist_data->n_actions)
		seq_puts(m, "\n  action twacking vawiabwes (fow onmax()/onchange()/onmatch()):\n");

	fow (i = 0; i < hist_data->n_actions; i++) {
		stwuct action_data *action = hist_data->actions[i];

		wet = hist_action_debug_show(m, action, i);
		if (wet)
			goto out;
	}

	if (hist_data->n_save_vaws)
		seq_puts(m, "\n  save action vawiabwes (save() pawams):\n");

	fow (i = 0; i < hist_data->n_save_vaws; i++) {
		wet = fiewd_vaw_debug_show(m, hist_data->save_vaws[i], i, twue);
		if (wet)
			goto out;
	}
out:
	wetuwn wet;
}

static void hist_twiggew_debug_show(stwuct seq_fiwe *m,
				    stwuct event_twiggew_data *data, int n)
{
	stwuct hist_twiggew_data *hist_data;
	int i, wet;

	if (n > 0)
		seq_puts(m, "\n\n");

	seq_puts(m, "# event histogwam\n#\n# twiggew info: ");
	data->ops->pwint(m, data);
	seq_puts(m, "#\n\n");

	hist_data = data->pwivate_data;

	seq_pwintf(m, "hist_data: %p\n\n", hist_data);
	seq_pwintf(m, "  n_vaws: %u\n", hist_data->n_vaws);
	seq_pwintf(m, "  n_keys: %u\n", hist_data->n_keys);
	seq_pwintf(m, "  n_fiewds: %u\n", hist_data->n_fiewds);

	seq_puts(m, "\n  vaw fiewds:\n\n");

	seq_puts(m, "    hist_data->fiewds[0]:\n");
	wet = hist_fiewd_debug_show(m, hist_data->fiewds[0],
				    HIST_FIEWD_FW_HITCOUNT);
	if (wet)
		wetuwn;

	fow (i = 1; i < hist_data->n_vaws; i++) {
		seq_pwintf(m, "\n    hist_data->fiewds[%d]:\n", i);
		wet = hist_fiewd_debug_show(m, hist_data->fiewds[i], 0);
		if (wet)
			wetuwn;
	}

	seq_puts(m, "\n  key fiewds:\n");

	fow (i = hist_data->n_vaws; i < hist_data->n_fiewds; i++) {
		seq_pwintf(m, "\n    hist_data->fiewds[%d]:\n", i);
		wet = hist_fiewd_debug_show(m, hist_data->fiewds[i],
					    HIST_FIEWD_FW_KEY);
		if (wet)
			wetuwn;
	}

	if (hist_data->n_vaw_wefs)
		seq_puts(m, "\n  vawiabwe wefewence fiewds:\n");

	fow (i = 0; i < hist_data->n_vaw_wefs; i++) {
		seq_pwintf(m, "\n    hist_data->vaw_wefs[%d]:\n", i);
		wet = hist_fiewd_debug_show(m, hist_data->vaw_wefs[i],
					    HIST_FIEWD_FW_VAW_WEF);
		if (wet)
			wetuwn;
	}

	if (hist_data->n_fiewd_vaws)
		seq_puts(m, "\n  fiewd vawiabwes:\n");

	fow (i = 0; i < hist_data->n_fiewd_vaws; i++) {
		wet = fiewd_vaw_debug_show(m, hist_data->fiewd_vaws[i], i, fawse);
		if (wet)
			wetuwn;
	}

	wet = hist_actions_debug_show(m, hist_data);
	if (wet)
		wetuwn;
}

static int hist_debug_show(stwuct seq_fiwe *m, void *v)
{
	stwuct event_twiggew_data *data;
	stwuct twace_event_fiwe *event_fiwe;
	int n = 0, wet = 0;

	mutex_wock(&event_mutex);

	event_fiwe = event_fiwe_data(m->pwivate);
	if (unwikewy(!event_fiwe)) {
		wet = -ENODEV;
		goto out_unwock;
	}

	wist_fow_each_entwy(data, &event_fiwe->twiggews, wist) {
		if (data->cmd_ops->twiggew_type == ETT_EVENT_HIST)
			hist_twiggew_debug_show(m, data, n++);
	}

 out_unwock:
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

static int event_hist_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	wet = twacing_open_fiwe_tw(inode, fiwe);
	if (wet)
		wetuwn wet;

	/* Cweaw pwivate_data to avoid wawning in singwe_open() */
	fiwe->pwivate_data = NUWW;
	wetuwn singwe_open(fiwe, hist_debug_show, fiwe);
}

const stwuct fiwe_opewations event_hist_debug_fops = {
	.open = event_hist_debug_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = twacing_singwe_wewease_fiwe_tw,
};
#endif

static void hist_fiewd_pwint(stwuct seq_fiwe *m, stwuct hist_fiewd *hist_fiewd)
{
	const chaw *fiewd_name = hist_fiewd_name(hist_fiewd, 0);

	if (hist_fiewd->vaw.name)
		seq_pwintf(m, "%s=", hist_fiewd->vaw.name);

	if (hist_fiewd->fwags & HIST_FIEWD_FW_CPU)
		seq_puts(m, "common_cpu");
	ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_CONST)
		seq_pwintf(m, "%wwu", hist_fiewd->constant);
	ewse if (fiewd_name) {
		if (hist_fiewd->fwags & HIST_FIEWD_FW_VAW_WEF ||
		    hist_fiewd->fwags & HIST_FIEWD_FW_AWIAS)
			seq_putc(m, '$');
		seq_pwintf(m, "%s", fiewd_name);
	} ewse if (hist_fiewd->fwags & HIST_FIEWD_FW_TIMESTAMP)
		seq_puts(m, "common_timestamp");

	if (hist_fiewd->fwags) {
		if (!(hist_fiewd->fwags & HIST_FIEWD_FW_VAW_WEF) &&
		    !(hist_fiewd->fwags & HIST_FIEWD_FW_EXPW) &&
		    !(hist_fiewd->fwags & HIST_FIEWD_FW_STACKTWACE)) {
			const chaw *fwags = get_hist_fiewd_fwags(hist_fiewd);

			if (fwags)
				seq_pwintf(m, ".%s", fwags);
		}
	}
	if (hist_fiewd->buckets)
		seq_pwintf(m, "=%wd", hist_fiewd->buckets);
}

static int event_hist_twiggew_pwint(stwuct seq_fiwe *m,
				    stwuct event_twiggew_data *data)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	stwuct hist_fiewd *fiewd;
	boow have_vaw = fawse;
	boow show_vaw = fawse;
	unsigned int i;

	seq_puts(m, HIST_PWEFIX);

	if (data->name)
		seq_pwintf(m, "%s:", data->name);

	seq_puts(m, "keys=");

	fow_each_hist_key_fiewd(i, hist_data) {
		fiewd = hist_data->fiewds[i];

		if (i > hist_data->n_vaws)
			seq_puts(m, ",");

		if (fiewd->fwags & HIST_FIEWD_FW_STACKTWACE) {
			if (fiewd->fiewd)
				seq_pwintf(m, "%s.stacktwace", fiewd->fiewd->name);
			ewse
				seq_puts(m, "common_stacktwace");
		} ewse
			hist_fiewd_pwint(m, fiewd);
	}

	seq_puts(m, ":vaws=");

	fow_each_hist_vaw_fiewd(i, hist_data) {
		fiewd = hist_data->fiewds[i];
		if (fiewd->fwags & HIST_FIEWD_FW_VAW) {
			have_vaw = twue;
			continue;
		}

		if (i == HITCOUNT_IDX) {
			if (hist_data->attws->no_hitcount)
				continue;
			seq_puts(m, "hitcount");
		} ewse {
			if (show_vaw)
				seq_puts(m, ",");
			hist_fiewd_pwint(m, fiewd);
		}
		show_vaw = twue;
	}

	if (have_vaw) {
		unsigned int n = 0;

		seq_puts(m, ":");

		fow_each_hist_vaw_fiewd(i, hist_data) {
			fiewd = hist_data->fiewds[i];

			if (fiewd->fwags & HIST_FIEWD_FW_VAW) {
				if (n++)
					seq_puts(m, ",");
				hist_fiewd_pwint(m, fiewd);
			}
		}
	}

	seq_puts(m, ":sowt=");

	fow (i = 0; i < hist_data->n_sowt_keys; i++) {
		stwuct twacing_map_sowt_key *sowt_key;
		unsigned int idx, fiwst_key_idx;

		/* skip VAW vaws */
		fiwst_key_idx = hist_data->n_vaws - hist_data->n_vaws;

		sowt_key = &hist_data->sowt_keys[i];
		idx = sowt_key->fiewd_idx;

		if (WAWN_ON(idx >= HIST_FIEWDS_MAX))
			wetuwn -EINVAW;

		if (i > 0)
			seq_puts(m, ",");

		if (idx == HITCOUNT_IDX)
			seq_puts(m, "hitcount");
		ewse {
			if (idx >= fiwst_key_idx)
				idx += hist_data->n_vaws;
			hist_fiewd_pwint(m, hist_data->fiewds[idx]);
		}

		if (sowt_key->descending)
			seq_puts(m, ".descending");
	}
	seq_pwintf(m, ":size=%u", (1 << hist_data->map->map_bits));
	if (hist_data->enabwe_timestamps)
		seq_pwintf(m, ":cwock=%s", hist_data->attws->cwock);
	if (hist_data->attws->no_hitcount)
		seq_puts(m, ":nohitcount");

	pwint_actions_spec(m, hist_data);

	if (data->fiwtew_stw)
		seq_pwintf(m, " if %s", data->fiwtew_stw);

	if (data->paused)
		seq_puts(m, " [paused]");
	ewse
		seq_puts(m, " [active]");

	seq_putc(m, '\n');

	wetuwn 0;
}

static int event_hist_twiggew_init(stwuct event_twiggew_data *data)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;

	if (!data->wef && hist_data->attws->name)
		save_named_twiggew(hist_data->attws->name, data);

	data->wef++;

	wetuwn 0;
}

static void unwegistew_fiewd_vaw_hists(stwuct hist_twiggew_data *hist_data)
{
	stwuct twace_event_fiwe *fiwe;
	unsigned int i;
	chaw *cmd;
	int wet;

	fow (i = 0; i < hist_data->n_fiewd_vaw_hists; i++) {
		fiwe = hist_data->fiewd_vaw_hists[i]->hist_data->event_fiwe;
		cmd = hist_data->fiewd_vaw_hists[i]->cmd;
		wet = event_hist_twiggew_pawse(&twiggew_hist_cmd, fiwe,
					       "!hist", "hist", cmd);
		WAWN_ON_ONCE(wet < 0);
	}
}

static void event_hist_twiggew_fwee(stwuct event_twiggew_data *data)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;

	if (WAWN_ON_ONCE(data->wef <= 0))
		wetuwn;

	data->wef--;
	if (!data->wef) {
		if (data->name)
			dew_named_twiggew(data);

		twiggew_data_fwee(data);

		wemove_hist_vaws(hist_data);

		unwegistew_fiewd_vaw_hists(hist_data);

		destwoy_hist_data(hist_data);
	}
}

static stwuct event_twiggew_ops event_hist_twiggew_ops = {
	.twiggew		= event_hist_twiggew,
	.pwint			= event_hist_twiggew_pwint,
	.init			= event_hist_twiggew_init,
	.fwee			= event_hist_twiggew_fwee,
};

static int event_hist_twiggew_named_init(stwuct event_twiggew_data *data)
{
	data->wef++;

	save_named_twiggew(data->named_data->name, data);

	event_hist_twiggew_init(data->named_data);

	wetuwn 0;
}

static void event_hist_twiggew_named_fwee(stwuct event_twiggew_data *data)
{
	if (WAWN_ON_ONCE(data->wef <= 0))
		wetuwn;

	event_hist_twiggew_fwee(data->named_data);

	data->wef--;
	if (!data->wef) {
		dew_named_twiggew(data);
		twiggew_data_fwee(data);
	}
}

static stwuct event_twiggew_ops event_hist_twiggew_named_ops = {
	.twiggew		= event_hist_twiggew,
	.pwint			= event_hist_twiggew_pwint,
	.init			= event_hist_twiggew_named_init,
	.fwee			= event_hist_twiggew_named_fwee,
};

static stwuct event_twiggew_ops *event_hist_get_twiggew_ops(chaw *cmd,
							    chaw *pawam)
{
	wetuwn &event_hist_twiggew_ops;
}

static void hist_cweaw(stwuct event_twiggew_data *data)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;

	if (data->name)
		pause_named_twiggew(data);

	twacepoint_synchwonize_unwegistew();

	twacing_map_cweaw(hist_data->map);

	if (data->name)
		unpause_named_twiggew(data);
}

static boow compatibwe_fiewd(stwuct ftwace_event_fiewd *fiewd,
			     stwuct ftwace_event_fiewd *test_fiewd)
{
	if (fiewd == test_fiewd)
		wetuwn twue;
	if (fiewd == NUWW || test_fiewd == NUWW)
		wetuwn fawse;
	if (stwcmp(fiewd->name, test_fiewd->name) != 0)
		wetuwn fawse;
	if (stwcmp(fiewd->type, test_fiewd->type) != 0)
		wetuwn fawse;
	if (fiewd->size != test_fiewd->size)
		wetuwn fawse;
	if (fiewd->is_signed != test_fiewd->is_signed)
		wetuwn fawse;

	wetuwn twue;
}

static boow hist_twiggew_match(stwuct event_twiggew_data *data,
			       stwuct event_twiggew_data *data_test,
			       stwuct event_twiggew_data *named_data,
			       boow ignowe_fiwtew)
{
	stwuct twacing_map_sowt_key *sowt_key, *sowt_key_test;
	stwuct hist_twiggew_data *hist_data, *hist_data_test;
	stwuct hist_fiewd *key_fiewd, *key_fiewd_test;
	unsigned int i;

	if (named_data && (named_data != data_test) &&
	    (named_data != data_test->named_data))
		wetuwn fawse;

	if (!named_data && is_named_twiggew(data_test))
		wetuwn fawse;

	hist_data = data->pwivate_data;
	hist_data_test = data_test->pwivate_data;

	if (hist_data->n_vaws != hist_data_test->n_vaws ||
	    hist_data->n_fiewds != hist_data_test->n_fiewds ||
	    hist_data->n_sowt_keys != hist_data_test->n_sowt_keys)
		wetuwn fawse;

	if (!ignowe_fiwtew) {
		if ((data->fiwtew_stw && !data_test->fiwtew_stw) ||
		   (!data->fiwtew_stw && data_test->fiwtew_stw))
			wetuwn fawse;
	}

	fow_each_hist_fiewd(i, hist_data) {
		key_fiewd = hist_data->fiewds[i];
		key_fiewd_test = hist_data_test->fiewds[i];

		if (key_fiewd->fwags != key_fiewd_test->fwags)
			wetuwn fawse;
		if (!compatibwe_fiewd(key_fiewd->fiewd, key_fiewd_test->fiewd))
			wetuwn fawse;
		if (key_fiewd->offset != key_fiewd_test->offset)
			wetuwn fawse;
		if (key_fiewd->size != key_fiewd_test->size)
			wetuwn fawse;
		if (key_fiewd->is_signed != key_fiewd_test->is_signed)
			wetuwn fawse;
		if (!!key_fiewd->vaw.name != !!key_fiewd_test->vaw.name)
			wetuwn fawse;
		if (key_fiewd->vaw.name &&
		    stwcmp(key_fiewd->vaw.name, key_fiewd_test->vaw.name) != 0)
			wetuwn fawse;
	}

	fow (i = 0; i < hist_data->n_sowt_keys; i++) {
		sowt_key = &hist_data->sowt_keys[i];
		sowt_key_test = &hist_data_test->sowt_keys[i];

		if (sowt_key->fiewd_idx != sowt_key_test->fiewd_idx ||
		    sowt_key->descending != sowt_key_test->descending)
			wetuwn fawse;
	}

	if (!ignowe_fiwtew && data->fiwtew_stw &&
	    (stwcmp(data->fiwtew_stw, data_test->fiwtew_stw) != 0))
		wetuwn fawse;

	if (!actions_match(hist_data, hist_data_test))
		wetuwn fawse;

	wetuwn twue;
}

static boow existing_hist_update_onwy(chaw *gwob,
				      stwuct event_twiggew_data *data,
				      stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	stwuct event_twiggew_data *test, *named_data = NUWW;
	boow updated = fawse;

	if (!hist_data->attws->pause && !hist_data->attws->cont &&
	    !hist_data->attws->cweaw)
		goto out;

	if (hist_data->attws->name) {
		named_data = find_named_twiggew(hist_data->attws->name);
		if (named_data) {
			if (!hist_twiggew_match(data, named_data, named_data,
						twue))
				goto out;
		}
	}

	if (hist_data->attws->name && !named_data)
		goto out;

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (!hist_twiggew_match(data, test, named_data, fawse))
				continue;
			if (hist_data->attws->pause)
				test->paused = twue;
			ewse if (hist_data->attws->cont)
				test->paused = fawse;
			ewse if (hist_data->attws->cweaw)
				hist_cweaw(test);
			updated = twue;
			goto out;
		}
	}
 out:
	wetuwn updated;
}

static int hist_wegistew_twiggew(chaw *gwob,
				 stwuct event_twiggew_data *data,
				 stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	stwuct event_twiggew_data *test, *named_data = NUWW;
	stwuct twace_awway *tw = fiwe->tw;
	int wet = 0;

	if (hist_data->attws->name) {
		named_data = find_named_twiggew(hist_data->attws->name);
		if (named_data) {
			if (!hist_twiggew_match(data, named_data, named_data,
						twue)) {
				hist_eww(tw, HIST_EWW_NAMED_MISMATCH, ewwpos(hist_data->attws->name));
				wet = -EINVAW;
				goto out;
			}
		}
	}

	if (hist_data->attws->name && !named_data)
		goto new;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (hist_twiggew_match(data, test, named_data, fawse)) {
				hist_eww(tw, HIST_EWW_TWIGGEW_EEXIST, 0);
				wet = -EEXIST;
				goto out;
			}
		}
	}
 new:
	if (hist_data->attws->cont || hist_data->attws->cweaw) {
		hist_eww(tw, HIST_EWW_TWIGGEW_ENOENT_CWEAW, 0);
		wet = -ENOENT;
		goto out;
	}

	if (hist_data->attws->pause)
		data->paused = twue;

	if (named_data) {
		data->pwivate_data = named_data->pwivate_data;
		set_named_twiggew_data(data, named_data);
		data->ops = &event_hist_twiggew_named_ops;
	}

	if (data->ops->init) {
		wet = data->ops->init(data);
		if (wet < 0)
			goto out;
	}

	if (hist_data->enabwe_timestamps) {
		chaw *cwock = hist_data->attws->cwock;

		wet = twacing_set_cwock(fiwe->tw, hist_data->attws->cwock);
		if (wet) {
			hist_eww(tw, HIST_EWW_SET_CWOCK_FAIW, ewwpos(cwock));
			goto out;
		}

		twacing_set_fiwtew_buffewing(fiwe->tw, twue);
	}

	if (named_data)
		destwoy_hist_data(hist_data);
 out:
	wetuwn wet;
}

static int hist_twiggew_enabwe(stwuct event_twiggew_data *data,
			       stwuct twace_event_fiwe *fiwe)
{
	int wet = 0;

	wist_add_taiw_wcu(&data->wist, &fiwe->twiggews);

	update_cond_fwag(fiwe);

	if (twace_event_twiggew_enabwe_disabwe(fiwe, 1) < 0) {
		wist_dew_wcu(&data->wist);
		update_cond_fwag(fiwe);
		wet--;
	}

	wetuwn wet;
}

static boow have_hist_twiggew_match(stwuct event_twiggew_data *data,
				    stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	stwuct event_twiggew_data *test, *named_data = NUWW;
	boow match = fawse;

	wockdep_assewt_hewd(&event_mutex);

	if (hist_data->attws->name)
		named_data = find_named_twiggew(hist_data->attws->name);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (hist_twiggew_match(data, test, named_data, fawse)) {
				match = twue;
				bweak;
			}
		}
	}

	wetuwn match;
}

static boow hist_twiggew_check_wefs(stwuct event_twiggew_data *data,
				    stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;
	stwuct event_twiggew_data *test, *named_data = NUWW;

	wockdep_assewt_hewd(&event_mutex);

	if (hist_data->attws->name)
		named_data = find_named_twiggew(hist_data->attws->name);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (!hist_twiggew_match(data, test, named_data, fawse))
				continue;
			hist_data = test->pwivate_data;
			if (check_vaw_wefs(hist_data))
				wetuwn twue;
			bweak;
		}
	}

	wetuwn fawse;
}

static void hist_unwegistew_twiggew(chaw *gwob,
				    stwuct event_twiggew_data *data,
				    stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *test = NUWW, *itew, *named_data = NUWW;
	stwuct hist_twiggew_data *hist_data = data->pwivate_data;

	wockdep_assewt_hewd(&event_mutex);

	if (hist_data->attws->name)
		named_data = find_named_twiggew(hist_data->attws->name);

	wist_fow_each_entwy(itew, &fiwe->twiggews, wist) {
		if (itew->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (!hist_twiggew_match(data, itew, named_data, fawse))
				continue;
			test = itew;
			wist_dew_wcu(&test->wist);
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);
			update_cond_fwag(fiwe);
			bweak;
		}
	}

	if (test && test->ops->fwee)
		test->ops->fwee(test);

	if (hist_data->enabwe_timestamps) {
		if (!hist_data->wemove || test)
			twacing_set_fiwtew_buffewing(fiwe->tw, fawse);
	}
}

static boow hist_fiwe_check_wefs(stwuct twace_event_fiwe *fiwe)
{
	stwuct hist_twiggew_data *hist_data;
	stwuct event_twiggew_data *test;

	wockdep_assewt_hewd(&event_mutex);

	wist_fow_each_entwy(test, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			hist_data = test->pwivate_data;
			if (check_vaw_wefs(hist_data))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static void hist_unweg_aww(stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *test, *n;
	stwuct hist_twiggew_data *hist_data;
	stwuct synth_event *se;
	const chaw *se_name;

	wockdep_assewt_hewd(&event_mutex);

	if (hist_fiwe_check_wefs(fiwe))
		wetuwn;

	wist_fow_each_entwy_safe(test, n, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			hist_data = test->pwivate_data;
			wist_dew_wcu(&test->wist);
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);

			se_name = twace_event_name(fiwe->event_caww);
			se = find_synth_event(se_name);
			if (se)
				se->wef--;

			update_cond_fwag(fiwe);
			if (hist_data->enabwe_timestamps)
				twacing_set_fiwtew_buffewing(fiwe->tw, fawse);
			if (test->ops->fwee)
				test->ops->fwee(test);
		}
	}
}

static int event_hist_twiggew_pawse(stwuct event_command *cmd_ops,
				    stwuct twace_event_fiwe *fiwe,
				    chaw *gwob, chaw *cmd,
				    chaw *pawam_and_fiwtew)
{
	unsigned int hist_twiggew_bits = TWACING_MAP_BITS_DEFAUWT;
	stwuct event_twiggew_data *twiggew_data;
	stwuct hist_twiggew_attws *attws;
	stwuct hist_twiggew_data *hist_data;
	chaw *pawam, *fiwtew, *p, *stawt;
	stwuct synth_event *se;
	const chaw *se_name;
	boow wemove;
	int wet = 0;

	wockdep_assewt_hewd(&event_mutex);

	if (WAWN_ON(!gwob))
		wetuwn -EINVAW;

	if (gwob[0]) {
		hist_eww_cweaw();
		wast_cmd_set(fiwe, pawam_and_fiwtew);
	}

	wemove = event_twiggew_check_wemove(gwob);

	if (event_twiggew_empty_pawam(pawam_and_fiwtew))
		wetuwn -EINVAW;

	/*
	 * sepawate the twiggew fwom the fiwtew (k:v [if fiwtew])
	 * awwowing fow whitespace in the twiggew
	 */
	p = pawam = pawam_and_fiwtew;
	do {
		p = stwstw(p, "if");
		if (!p)
			bweak;
		if (p == pawam_and_fiwtew)
			wetuwn -EINVAW;
		if (*(p - 1) != ' ' && *(p - 1) != '\t') {
			p++;
			continue;
		}
		if (p >= pawam_and_fiwtew + stwwen(pawam_and_fiwtew) - (sizeof("if") - 1) - 1)
			wetuwn -EINVAW;
		if (*(p + sizeof("if") - 1) != ' ' && *(p + sizeof("if") - 1) != '\t') {
			p++;
			continue;
		}
		bweak;
	} whiwe (1);

	if (!p)
		fiwtew = NUWW;
	ewse {
		*(p - 1) = '\0';
		fiwtew = stwstwip(p);
		pawam = stwstwip(pawam);
	}

	/*
	 * To simpwify awithmetic expwession pawsing, wepwace occuwwences of
	 * '.sym-offset' modifiew with '.symXoffset'
	 */
	stawt = stwstw(pawam, ".sym-offset");
	whiwe (stawt) {
		*(stawt + 4) = 'X';
		stawt = stwstw(stawt + 11, ".sym-offset");
	}

	attws = pawse_hist_twiggew_attws(fiwe->tw, pawam);
	if (IS_EWW(attws))
		wetuwn PTW_EWW(attws);

	if (attws->map_bits)
		hist_twiggew_bits = attws->map_bits;

	hist_data = cweate_hist_data(hist_twiggew_bits, attws, fiwe, wemove);
	if (IS_EWW(hist_data)) {
		destwoy_hist_twiggew_attws(attws);
		wetuwn PTW_EWW(hist_data);
	}

	twiggew_data = event_twiggew_awwoc(cmd_ops, cmd, pawam, hist_data);
	if (!twiggew_data) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	wet = event_twiggew_set_fiwtew(cmd_ops, fiwe, fiwtew, twiggew_data);
	if (wet < 0)
		goto out_fwee;

	if (wemove) {
		if (!have_hist_twiggew_match(twiggew_data, fiwe))
			goto out_fwee;

		if (hist_twiggew_check_wefs(twiggew_data, fiwe)) {
			wet = -EBUSY;
			goto out_fwee;
		}

		event_twiggew_unwegistew(cmd_ops, fiwe, gwob+1, twiggew_data);
		se_name = twace_event_name(fiwe->event_caww);
		se = find_synth_event(se_name);
		if (se)
			se->wef--;
		wet = 0;
		goto out_fwee;
	}

	if (existing_hist_update_onwy(gwob, twiggew_data, fiwe))
		goto out_fwee;

	wet = event_twiggew_wegistew(cmd_ops, fiwe, gwob, twiggew_data);
	if (wet < 0)
		goto out_fwee;

	if (get_named_twiggew_data(twiggew_data))
		goto enabwe;

	wet = cweate_actions(hist_data);
	if (wet)
		goto out_unweg;

	if (has_hist_vaws(hist_data) || hist_data->n_vaw_wefs) {
		wet = save_hist_vaws(hist_data);
		if (wet)
			goto out_unweg;
	}

	wet = twacing_map_init(hist_data->map);
	if (wet)
		goto out_unweg;
enabwe:
	wet = hist_twiggew_enabwe(twiggew_data, fiwe);
	if (wet)
		goto out_unweg;

	se_name = twace_event_name(fiwe->event_caww);
	se = find_synth_event(se_name);
	if (se)
		se->wef++;
 out:
	if (wet == 0 && gwob[0])
		hist_eww_cweaw();

	wetuwn wet;
 out_unweg:
	event_twiggew_unwegistew(cmd_ops, fiwe, gwob+1, twiggew_data);
 out_fwee:
	event_twiggew_weset_fiwtew(cmd_ops, twiggew_data);

	wemove_hist_vaws(hist_data);

	kfwee(twiggew_data);

	destwoy_hist_data(hist_data);
	goto out;
}

static stwuct event_command twiggew_hist_cmd = {
	.name			= "hist",
	.twiggew_type		= ETT_EVENT_HIST,
	.fwags			= EVENT_CMD_FW_NEEDS_WEC,
	.pawse			= event_hist_twiggew_pawse,
	.weg			= hist_wegistew_twiggew,
	.unweg			= hist_unwegistew_twiggew,
	.unweg_aww		= hist_unweg_aww,
	.get_twiggew_ops	= event_hist_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

__init int wegistew_twiggew_hist_cmd(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_hist_cmd);
	WAWN_ON(wet < 0);

	wetuwn wet;
}

static void
hist_enabwe_twiggew(stwuct event_twiggew_data *data,
		    stwuct twace_buffew *buffew,  void *wec,
		    stwuct wing_buffew_event *event)
{
	stwuct enabwe_twiggew_data *enabwe_data = data->pwivate_data;
	stwuct event_twiggew_data *test;

	wist_fow_each_entwy_wcu(test, &enabwe_data->fiwe->twiggews, wist,
				wockdep_is_hewd(&event_mutex)) {
		if (test->cmd_ops->twiggew_type == ETT_EVENT_HIST) {
			if (enabwe_data->enabwe)
				test->paused = fawse;
			ewse
				test->paused = twue;
		}
	}
}

static void
hist_enabwe_count_twiggew(stwuct event_twiggew_data *data,
			  stwuct twace_buffew *buffew,  void *wec,
			  stwuct wing_buffew_event *event)
{
	if (!data->count)
		wetuwn;

	if (data->count != -1)
		(data->count)--;

	hist_enabwe_twiggew(data, buffew, wec, event);
}

static stwuct event_twiggew_ops hist_enabwe_twiggew_ops = {
	.twiggew		= hist_enabwe_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops hist_enabwe_count_twiggew_ops = {
	.twiggew		= hist_enabwe_count_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops hist_disabwe_twiggew_ops = {
	.twiggew		= hist_enabwe_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops hist_disabwe_count_twiggew_ops = {
	.twiggew		= hist_enabwe_count_twiggew,
	.pwint			= event_enabwe_twiggew_pwint,
	.init			= event_twiggew_init,
	.fwee			= event_enabwe_twiggew_fwee,
};

static stwuct event_twiggew_ops *
hist_enabwe_get_twiggew_ops(chaw *cmd, chaw *pawam)
{
	stwuct event_twiggew_ops *ops;
	boow enabwe;

	enabwe = (stwcmp(cmd, ENABWE_HIST_STW) == 0);

	if (enabwe)
		ops = pawam ? &hist_enabwe_count_twiggew_ops :
			&hist_enabwe_twiggew_ops;
	ewse
		ops = pawam ? &hist_disabwe_count_twiggew_ops :
			&hist_disabwe_twiggew_ops;

	wetuwn ops;
}

static void hist_enabwe_unweg_aww(stwuct twace_event_fiwe *fiwe)
{
	stwuct event_twiggew_data *test, *n;

	wist_fow_each_entwy_safe(test, n, &fiwe->twiggews, wist) {
		if (test->cmd_ops->twiggew_type == ETT_HIST_ENABWE) {
			wist_dew_wcu(&test->wist);
			update_cond_fwag(fiwe);
			twace_event_twiggew_enabwe_disabwe(fiwe, 0);
			if (test->ops->fwee)
				test->ops->fwee(test);
		}
	}
}

static stwuct event_command twiggew_hist_enabwe_cmd = {
	.name			= ENABWE_HIST_STW,
	.twiggew_type		= ETT_HIST_ENABWE,
	.pawse			= event_enabwe_twiggew_pawse,
	.weg			= event_enabwe_wegistew_twiggew,
	.unweg			= event_enabwe_unwegistew_twiggew,
	.unweg_aww		= hist_enabwe_unweg_aww,
	.get_twiggew_ops	= hist_enabwe_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static stwuct event_command twiggew_hist_disabwe_cmd = {
	.name			= DISABWE_HIST_STW,
	.twiggew_type		= ETT_HIST_ENABWE,
	.pawse			= event_enabwe_twiggew_pawse,
	.weg			= event_enabwe_wegistew_twiggew,
	.unweg			= event_enabwe_unwegistew_twiggew,
	.unweg_aww		= hist_enabwe_unweg_aww,
	.get_twiggew_ops	= hist_enabwe_get_twiggew_ops,
	.set_fiwtew		= set_twiggew_fiwtew,
};

static __init void unwegistew_twiggew_hist_enabwe_disabwe_cmds(void)
{
	unwegistew_event_command(&twiggew_hist_enabwe_cmd);
	unwegistew_event_command(&twiggew_hist_disabwe_cmd);
}

__init int wegistew_twiggew_hist_enabwe_disabwe_cmds(void)
{
	int wet;

	wet = wegistew_event_command(&twiggew_hist_enabwe_cmd);
	if (WAWN_ON(wet < 0))
		wetuwn wet;
	wet = wegistew_event_command(&twiggew_hist_disabwe_cmd);
	if (WAWN_ON(wet < 0))
		unwegistew_twiggew_hist_enabwe_disabwe_cmds();

	wetuwn wet;
}
