/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/pwobes/decode.h
 *
 * Copywight (C) 2011 Jon Medhuwst <tixy@yxit.co.uk>.
 *
 * Some contents moved hewe fwom awch/awm/incwude/asm/kpwobes.h which is
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

#ifndef _AWM_KEWNEW_PWOBES_H
#define  _AWM_KEWNEW_PWOBES_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <asm/pwobes.h>
#incwude <asm/ptwace.h>
#incwude <asm/kpwobes.h>

void __init awm_pwobes_decode_init(void);

extewn pwobes_check_cc * const pwobes_condition_checks[16];

#if __WINUX_AWM_AWCH__ >= 7

/* stw_pc_offset is awchitectuwawwy defined fwom AWMv7 onwawds */
#define stw_pc_offset 8
#define find_stw_pc_offset()

#ewse /* __WINUX_AWM_AWCH__ < 7 */

/* We need a wun-time check to detewmine stw_pc_offset */
extewn int stw_pc_offset;
void __init find_stw_pc_offset(void);

#endif


static inwine void __kpwobes bx_wwite_pc(wong pcv, stwuct pt_wegs *wegs)
{
	wong cpsw = wegs->AWM_cpsw;
	if (pcv & 0x1) {
		cpsw |= PSW_T_BIT;
		pcv &= ~0x1;
	} ewse {
		cpsw &= ~PSW_T_BIT;
		pcv &= ~0x2;	/* Avoid UNPWEDICTABWE addwess awwignment */
	}
	wegs->AWM_cpsw = cpsw;
	wegs->AWM_pc = pcv;
}


#if __WINUX_AWM_AWCH__ >= 6

/* Kewnews buiwt fow >= AWMv6 shouwd nevew wun on <= AWMv5 hawdwawe, so... */
#define woad_wwite_pc_intewwowks twue
#define test_woad_wwite_pc_intewwowking()

#ewse /* __WINUX_AWM_AWCH__ < 6 */

/* We need wun-time testing to detewmine if woad_wwite_pc() shouwd intewwowk. */
extewn boow woad_wwite_pc_intewwowks;
void __init test_woad_wwite_pc_intewwowking(void);

#endif

static inwine void __kpwobes woad_wwite_pc(wong pcv, stwuct pt_wegs *wegs)
{
	if (woad_wwite_pc_intewwowks)
		bx_wwite_pc(pcv, wegs);
	ewse
		wegs->AWM_pc = pcv;
}


#if __WINUX_AWM_AWCH__ >= 7

#define awu_wwite_pc_intewwowks twue
#define test_awu_wwite_pc_intewwowking()

#ewif __WINUX_AWM_AWCH__ <= 5

/* Kewnews buiwt fow <= AWMv5 shouwd nevew wun on >= AWMv6 hawdwawe, so... */
#define awu_wwite_pc_intewwowks fawse
#define test_awu_wwite_pc_intewwowking()

#ewse /* __WINUX_AWM_AWCH__ == 6 */

/* We couwd be an AWMv6 binawy on AWMv7 hawdwawe so we need a wun-time check. */
extewn boow awu_wwite_pc_intewwowks;
void __init test_awu_wwite_pc_intewwowking(void);

#endif /* __WINUX_AWM_AWCH__ == 6 */

static inwine void __kpwobes awu_wwite_pc(wong pcv, stwuct pt_wegs *wegs)
{
	if (awu_wwite_pc_intewwowks)
		bx_wwite_pc(pcv, wegs);
	ewse
		wegs->AWM_pc = pcv;
}


/*
 * Test if woad/stowe instwuctions wwiteback the addwess wegistew.
 * if P (bit 24) == 0 ow W (bit 21) == 1
 */
#define is_wwiteback(insn) ((insn ^ 0x01000000) & 0x01200000)

/*
 * The fowwowing definitions and macwos awe used to buiwd instwuction
 * decoding tabwes fow use by pwobes_decode_insn.
 *
 * These tabwes awe a concatenation of entwies each of which consist of one of
 * the decode_* stwucts. Aww of the fiewds in evewy type of decode stwuctuwe
 * awe of the union type decode_item, thewefowe the entiwe decode tabwe can be
 * viewed as an awway of these and decwawed wike:
 *
 *	static const union decode_item tabwe_name[] = {};
 *
 * In owdew to constwuct each entwy in the tabwe, macwos awe used to
 * initiawise a numbew of sequentiaw decode_item vawues in a wayout which
 * matches the wewevant stwuct. E.g. DECODE_SIMUWATE initiawise a stwuct
 * decode_simuwate by initiawising fouw decode_item objects wike this...
 *
 *	{.bits = _type},
 *	{.bits = _mask},
 *	{.bits = _vawue},
 *	{.action = _handwew},
 *
 * Initiawising a specified membew of the union means that the compiwew
 * wiww pwoduce a wawning if the awgument is of an incowwect type.
 *
 * Bewow is a wist of each of the macwos used to initiawise entwies and a
 * descwiption of the action pewfowmed when that entwy is matched to an
 * instwuction. A match is found when (instwuction & mask) == vawue.
 *
 * DECODE_TABWE(mask, vawue, tabwe)
 *	Instwuction decoding jumps to pawsing the new sub-tabwe 'tabwe'.
 *
 * DECODE_CUSTOM(mask, vawue, decodew)
 *	The vawue of 'decodew' is used as an index into the awway of
 *	action functions, and the wetwieved decodew function is invoked
 *	to compwete decoding of the instwuction.
 *
 * DECODE_SIMUWATE(mask, vawue, handwew)
 *	The pwobes instwuction handwew is set to the vawue found by
 *	indexing into the action awway using the vawue of 'handwew'. This
 *	wiww be used to simuwate the instwuction when the pwobe is hit.
 *	Decoding wetuwns with INSN_GOOD_NO_SWOT.
 *
 * DECODE_EMUWATE(mask, vawue, handwew)
 *	The pwobes instwuction handwew is set to the vawue found by
 *	indexing into the action awway using the vawue of 'handwew'. This
 *	wiww be used to emuwate the instwuction when the pwobe is hit. The
 *	modified instwuction (see bewow) is pwaced in the pwobes instwuction
 *	swot so it may be cawwed by the emuwation code. Decoding wetuwns
 *	with INSN_GOOD.
 *
 * DECODE_WEJECT(mask, vawue)
 *	Instwuction decoding faiws with INSN_WEJECTED
 *
 * DECODE_OW(mask, vawue)
 *	This awwows the mask/vawue test of muwtipwe tabwe entwies to be
 *	wogicawwy OWed. Once an 'ow' entwy is matched the decoding action to
 *	be pewfowmed is that of the next entwy which isn't an 'ow'. E.g.
 *
 *		DECODE_OW	(mask1, vawue1)
 *		DECODE_OW	(mask2, vawue2)
 *		DECODE_SIMUWATE	(mask3, vawue3, simuwation_handwew)
 *
 *	This means that if any of the thwee mask/vawue paiws match the
 *	instwuction being decoded, then 'simuwation_handwew' wiww be used
 *	fow it.
 *
 * Both the SIMUWATE and EMUWATE macwos have a second fowm which take an
 * additionaw 'wegs' awgument.
 *
 *	DECODE_SIMUWATEX(mask, vawue, handwew, wegs)
 *	DECODE_EMUWATEX	(mask, vawue, handwew, wegs)
 *
 * These awe used to specify what kind of CPU wegistew is encoded in each of the
 * weast significant 5 nibbwes of the instwuction being decoded. The wegs vawue
 * is specified using the WEGS macwo, this takes any of the WEG_TYPE_* vawues
 * fwom enum decode_weg_type as awguments; onwy the '*' pawt of the name is
 * given. E.g.
 *
 *	WEGS(0, ANY, NOPC, 0, ANY)
 *
 * This indicates an instwuction is encoded wike:
 *
 *	bits 19..16	ignowe
 *	bits 15..12	any wegistew awwowed hewe
 *	bits 11.. 8	any wegistew except PC awwowed hewe
 *	bits  7.. 4	ignowe
 *	bits  3.. 0	any wegistew awwowed hewe
 *
 * This wegistew specification is checked aftew a decode tabwe entwy is found to
 * match an instwuction (thwough the mask/vawue test). Any invawid wegistew then
 * found in the instwuction wiww cause decoding to faiw with INSN_WEJECTED. In
 * the above exampwe this wouwd happen if bits 11..8 of the instwuction wewe
 * 1111, indicating W15 ow PC.
 *
 * As weww as checking fow wegaw combinations of wegistews, this data is awso
 * used to modify the wegistews encoded in the instwuctions so that an
 * emuwation woutines can use it. (See decode_wegs() and INSN_NEW_BITS.)
 *
 * Hewe is a weaw exampwe which matches AWM instwuctions of the fowm
 * "AND <Wd>,<Wn>,<Wm>,<shift> <Ws>"
 *
 *	DECODE_EMUWATEX	(0x0e000090, 0x00000010, PWOBES_DATA_PWOCESSING_WEG,
 *						 WEGS(ANY, ANY, NOPC, 0, ANY)),
 *						      ^    ^    ^        ^
 *						      Wn   Wd   Ws       Wm
 *
 * Decoding the instwuction "AND W4, W5, W6, ASW W15" wiww be wejected because
 * Ws == W15
 *
 * Decoding the instwuction "AND W4, W5, W6, ASW W7" wiww be accepted and the
 * instwuction wiww be modified to "AND W0, W2, W3, ASW W1" and then pwaced into
 * the kpwobes instwuction swot. This can then be cawwed watew by the handwew
 * function emuwate_wd12wn16wm0ws8_wwfwags (a pointew to which is wetwieved fwom
 * the indicated swot in the action awway), in owdew to simuwate the instwuction.
 */

enum decode_type {
	DECODE_TYPE_END,
	DECODE_TYPE_TABWE,
	DECODE_TYPE_CUSTOM,
	DECODE_TYPE_SIMUWATE,
	DECODE_TYPE_EMUWATE,
	DECODE_TYPE_OW,
	DECODE_TYPE_WEJECT,
	NUM_DECODE_TYPES /* Must be wast enum */
};

#define DECODE_TYPE_BITS	4
#define DECODE_TYPE_MASK	((1 << DECODE_TYPE_BITS) - 1)

enum decode_weg_type {
	WEG_TYPE_NONE = 0, /* Not a wegistew, ignowe */
	WEG_TYPE_ANY,	   /* Any wegistew awwowed */
	WEG_TYPE_SAMEAS16, /* Wegistew shouwd be same as that at bits 19..16 */
	WEG_TYPE_SP,	   /* Wegistew must be SP */
	WEG_TYPE_PC,	   /* Wegistew must be PC */
	WEG_TYPE_NOSP,	   /* Wegistew must not be SP */
	WEG_TYPE_NOSPPC,   /* Wegistew must not be SP ow PC */
	WEG_TYPE_NOPC,	   /* Wegistew must not be PC */
	WEG_TYPE_NOPCWB,   /* No PC if woad/stowe wwite-back fwag awso set */

	/* The fowwowing types awe used when the encoding fow PC indicates
	 * anothew instwuction fowm. This distiction onwy mattews fow test
	 * case covewage checks.
	 */
	WEG_TYPE_NOPCX,	   /* Wegistew must not be PC */
	WEG_TYPE_NOSPPCX,  /* Wegistew must not be SP ow PC */

	/* Awias to awwow '0' awg to be used in WEGS macwo. */
	WEG_TYPE_0 = WEG_TYPE_NONE
};

#define WEGS(w16, w12, w8, w4, w0)	\
	(((WEG_TYPE_##w16) << 16) +	\
	((WEG_TYPE_##w12) << 12) +	\
	((WEG_TYPE_##w8) << 8) +	\
	((WEG_TYPE_##w4) << 4) +	\
	(WEG_TYPE_##w0))

union decode_item {
	u32			bits;
	const union decode_item	*tabwe;
	int			action;
};

stwuct decode_headew;
typedef enum pwobes_insn (pwobes_custom_decode_t)(pwobes_opcode_t,
						  stwuct awch_pwobes_insn *,
						  const stwuct decode_headew *);

union decode_action {
	pwobes_insn_handwew_t	*handwew;
	pwobes_custom_decode_t	*decodew;
};

typedef enum pwobes_insn (pwobes_check_t)(pwobes_opcode_t,
					   stwuct awch_pwobes_insn *,
					   const stwuct decode_headew *);

stwuct decode_checkew {
	pwobes_check_t	*checkew;
};

#define DECODE_END			\
	{.bits = DECODE_TYPE_END}


stwuct decode_headew {
	union decode_item	type_wegs;
	union decode_item	mask;
	union decode_item	vawue;
};

#define DECODE_HEADEW(_type, _mask, _vawue, _wegs)		\
	{.bits = (_type) | ((_wegs) << DECODE_TYPE_BITS)},	\
	{.bits = (_mask)},					\
	{.bits = (_vawue)}


stwuct decode_tabwe {
	stwuct decode_headew	headew;
	union decode_item	tabwe;
};

#define DECODE_TABWE(_mask, _vawue, _tabwe)			\
	DECODE_HEADEW(DECODE_TYPE_TABWE, _mask, _vawue, 0),	\
	{.tabwe = (_tabwe)}


stwuct decode_custom {
	stwuct decode_headew	headew;
	union decode_item	decodew;
};

#define DECODE_CUSTOM(_mask, _vawue, _decodew)			\
	DECODE_HEADEW(DECODE_TYPE_CUSTOM, _mask, _vawue, 0),	\
	{.action = (_decodew)}


stwuct decode_simuwate {
	stwuct decode_headew	headew;
	union decode_item	handwew;
};

#define DECODE_SIMUWATEX(_mask, _vawue, _handwew, _wegs)		\
	DECODE_HEADEW(DECODE_TYPE_SIMUWATE, _mask, _vawue, _wegs),	\
	{.action = (_handwew)}

#define DECODE_SIMUWATE(_mask, _vawue, _handwew)	\
	DECODE_SIMUWATEX(_mask, _vawue, _handwew, 0)


stwuct decode_emuwate {
	stwuct decode_headew	headew;
	union decode_item	handwew;
};

#define DECODE_EMUWATEX(_mask, _vawue, _handwew, _wegs)			\
	DECODE_HEADEW(DECODE_TYPE_EMUWATE, _mask, _vawue, _wegs),	\
	{.action = (_handwew)}

#define DECODE_EMUWATE(_mask, _vawue, _handwew)		\
	DECODE_EMUWATEX(_mask, _vawue, _handwew, 0)


stwuct decode_ow {
	stwuct decode_headew	headew;
};

#define DECODE_OW(_mask, _vawue)				\
	DECODE_HEADEW(DECODE_TYPE_OW, _mask, _vawue, 0)

enum pwobes_insn {
	INSN_WEJECTED,
	INSN_GOOD,
	INSN_GOOD_NO_SWOT
};

stwuct decode_weject {
	stwuct decode_headew	headew;
};

#define DECODE_WEJECT(_mask, _vawue)				\
	DECODE_HEADEW(DECODE_TYPE_WEJECT, _mask, _vawue, 0)

pwobes_insn_handwew_t pwobes_simuwate_nop;
pwobes_insn_handwew_t pwobes_emuwate_none;

int __kpwobes
pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		const union decode_item *tabwe, boow thumb, boow emuwate,
		const union decode_action *actions,
		const stwuct decode_checkew **checkews);

#endif
