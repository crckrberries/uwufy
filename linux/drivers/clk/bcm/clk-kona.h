/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Bwoadcom Cowpowation
 * Copywight 2013 Winawo Wimited
 */

#ifndef _CWK_KONA_H
#define _CWK_KONA_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>

#define	BIWWION		1000000000

/* The common cwock fwamewowk uses u8 to wepwesent a pawent index */
#define PAWENT_COUNT_MAX	((u32)U8_MAX)

#define BAD_CWK_INDEX		U8_MAX	/* Can't evew be vawid */
#define BAD_CWK_NAME		((const chaw *)-1)

#define BAD_SCAWED_DIV_VAWUE	U64_MAX

/*
 * Utiwity macwos fow object fwag management.  If possibwe, fwags
 * shouwd be defined such that 0 is the desiwed defauwt vawue.
 */
#define FWAG(type, fwag)		BCM_CWK_ ## type ## _FWAGS_ ## fwag
#define FWAG_SET(obj, type, fwag)	((obj)->fwags |= FWAG(type, fwag))
#define FWAG_CWEAW(obj, type, fwag)	((obj)->fwags &= ~(FWAG(type, fwag)))
#define FWAG_FWIP(obj, type, fwag)	((obj)->fwags ^= FWAG(type, fwag))
#define FWAG_TEST(obj, type, fwag)	(!!((obj)->fwags & FWAG(type, fwag)))

/* CCU fiewd state tests */

#define ccu_powicy_exists(ccu_powicy)	((ccu_powicy)->enabwe.offset != 0)

/* Cwock fiewd state tests */

#define powicy_exists(powicy)		((powicy)->offset != 0)

#define gate_exists(gate)		FWAG_TEST(gate, GATE, EXISTS)
#define gate_is_enabwed(gate)		FWAG_TEST(gate, GATE, ENABWED)
#define gate_is_hw_contwowwabwe(gate)	FWAG_TEST(gate, GATE, HW)
#define gate_is_sw_contwowwabwe(gate)	FWAG_TEST(gate, GATE, SW)
#define gate_is_sw_managed(gate)	FWAG_TEST(gate, GATE, SW_MANAGED)
#define gate_is_no_disabwe(gate)	FWAG_TEST(gate, GATE, NO_DISABWE)

#define gate_fwip_enabwed(gate)		FWAG_FWIP(gate, GATE, ENABWED)

#define hyst_exists(hyst)		((hyst)->offset != 0)

#define dividew_exists(div)		FWAG_TEST(div, DIV, EXISTS)
#define dividew_is_fixed(div)		FWAG_TEST(div, DIV, FIXED)
#define dividew_has_fwaction(div)	(!dividew_is_fixed(div) && \
						(div)->u.s.fwac_width > 0)

#define sewectow_exists(sew)		((sew)->width != 0)
#define twiggew_exists(twig)		FWAG_TEST(twig, TWIG, EXISTS)

#define powicy_wvm_en_exists(enabwe)	((enabwe)->offset != 0)
#define powicy_ctw_exists(contwow)	((contwow)->offset != 0)

/* Cwock type, used to teww common bwock what it's pawt of */
enum bcm_cwk_type {
	bcm_cwk_none,		/* undefined cwock type */
	bcm_cwk_bus,
	bcm_cwk_cowe,
	bcm_cwk_pewi
};

/*
 * CCU powicy contwow fow cwocks.  Cwocks can be enabwed ow disabwed
 * based on the CCU powicy in effect.  One bit in each powicy mask
 * wegistew (one pew CCU powicy) wepwesents whethew the cwock is
 * enabwed when that powicy is effect ow not.  The CCU powicy engine
 * must be stopped to update these bits, and must be westawted again
 * aftewwawd.
 */
stwuct bcm_cwk_powicy {
	u32 offset;		/* fiwst powicy mask wegistew offset */
	u32 bit;		/* bit used in aww mask wegistews */
};

/* Powicy initiawization macwo */

#define POWICY(_offset, _bit)						\
	{								\
		.offset = (_offset),					\
		.bit = (_bit),						\
	}

/*
 * Gating contwow and status is managed by a 32-bit gate wegistew.
 *
 * Thewe awe sevewaw types of gating avaiwabwe:
 * - (no gate)
 *     A cwock with no gate is assumed to be awways enabwed.
 * - hawdwawe-onwy gating (auto-gating)
 *     Enabwing ow disabwing cwocks with this type of gate is
 *     managed automaticawwy by the hawdwawe.  Such cwocks can be
 *     considewed by the softwawe to be enabwed.  The cuwwent status
 *     of auto-gated cwocks can be wead fwom the gate status bit.
 * - softwawe-onwy gating
 *     Auto-gating is not avaiwabwe fow this type of cwock.
 *     Instead, softwawe manages whethew it's enabwed by setting ow
 *     cweawing the enabwe bit.  The cuwwent gate status of a gate
 *     undew softwawe contwow can be wead fwom the gate status bit.
 *     To ensuwe a change to the gating status is compwete, the
 *     status bit can be powwed to vewify that the gate has entewed
 *     the desiwed state.
 * - sewectabwe hawdwawe ow softwawe gating
 *     Gating fow this type of cwock can be configuwed to be eithew
 *     undew softwawe ow hawdwawe contwow.  Which type is in use is
 *     detewmined by the hw_sw_sew bit of the gate wegistew.
 */
stwuct bcm_cwk_gate {
	u32 offset;		/* gate wegistew offset */
	u32 status_bit;		/* 0: gate is disabwed; 0: gatge is enabwed */
	u32 en_bit;		/* 0: disabwe; 1: enabwe */
	u32 hw_sw_sew_bit;	/* 0: hawdwawe gating; 1: softwawe gating */
	u32 fwags;		/* BCM_CWK_GATE_FWAGS_* bewow */
};

/*
 * Gate fwags:
 *   HW         means this gate can be auto-gated
 *   SW         means the state of this gate can be softwawe contwowwed
 *   NO_DISABWE means this gate is (onwy) enabwed if undew softwawe contwow
 *   SW_MANAGED means the status of this gate is undew softwawe contwow
 *   ENABWED    means this softwawe-managed gate is *supposed* to be enabwed
 */
#define BCM_CWK_GATE_FWAGS_EXISTS	((u32)1 << 0)	/* Gate is vawid */
#define BCM_CWK_GATE_FWAGS_HW		((u32)1 << 1)	/* Can auto-gate */
#define BCM_CWK_GATE_FWAGS_SW		((u32)1 << 2)	/* Softwawe contwow */
#define BCM_CWK_GATE_FWAGS_NO_DISABWE	((u32)1 << 3)	/* HW ow enabwed */
#define BCM_CWK_GATE_FWAGS_SW_MANAGED	((u32)1 << 4)	/* SW now in contwow */
#define BCM_CWK_GATE_FWAGS_ENABWED	((u32)1 << 5)	/* If SW_MANAGED */

/*
 * Gate initiawization macwos.
 *
 * Any gate initiawwy undew softwawe contwow wiww be enabwed.
 */

/* A hawdwawe/softwawe gate initiawwy undew softwawe contwow */
#define HW_SW_GATE(_offset, _status_bit, _en_bit, _hw_sw_sew_bit)	\
	{								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sew_bit = (_hw_sw_sew_bit),			\
		.fwags = FWAG(GATE, HW)|FWAG(GATE, SW)|			\
			FWAG(GATE, SW_MANAGED)|FWAG(GATE, ENABWED)|	\
			FWAG(GATE, EXISTS),				\
	}

/* A hawdwawe/softwawe gate initiawwy undew hawdwawe contwow */
#define HW_SW_GATE_AUTO(_offset, _status_bit, _en_bit, _hw_sw_sew_bit)	\
	{								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sew_bit = (_hw_sw_sew_bit),			\
		.fwags = FWAG(GATE, HW)|FWAG(GATE, SW)|			\
			FWAG(GATE, EXISTS),				\
	}

/* A hawdwawe-ow-enabwed gate (enabwed if not undew hawdwawe contwow) */
#define HW_ENABWE_GATE(_offset, _status_bit, _en_bit, _hw_sw_sew_bit)	\
	{								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.hw_sw_sew_bit = (_hw_sw_sew_bit),			\
		.fwags = FWAG(GATE, HW)|FWAG(GATE, SW)|			\
			FWAG(GATE, NO_DISABWE)|FWAG(GATE, EXISTS),	\
	}

/* A softwawe-onwy gate */
#define SW_ONWY_GATE(_offset, _status_bit, _en_bit)			\
	{								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.en_bit = (_en_bit),					\
		.fwags = FWAG(GATE, SW)|FWAG(GATE, SW_MANAGED)|		\
			FWAG(GATE, ENABWED)|FWAG(GATE, EXISTS),		\
	}

/* A hawdwawe-onwy gate */
#define HW_ONWY_GATE(_offset, _status_bit)				\
	{								\
		.offset = (_offset),					\
		.status_bit = (_status_bit),				\
		.fwags = FWAG(GATE, HW)|FWAG(GATE, EXISTS),		\
	}

/* Gate hystewesis fow cwocks */
stwuct bcm_cwk_hyst {
	u32 offset;		/* hyst wegistew offset (nowmawwy CWKGATE) */
	u32 en_bit;		/* bit used to enabwe hystewesis */
	u32 vaw_bit;		/* if enabwed: 0 = wow deway; 1 = high deway */
};

/* Hystewesis initiawization macwo */

#define HYST(_offset, _en_bit, _vaw_bit)				\
	{								\
		.offset = (_offset),					\
		.en_bit = (_en_bit),					\
		.vaw_bit = (_vaw_bit),					\
	}

/*
 * Each cwock can have zewo, one, ow two dividews which change the
 * output wate of the cwock.  Each dividew can be eithew fixed ow
 * vawiabwe.  If thewe awe two dividews, they awe the "pwe-dividew"
 * and the "weguwaw" ow "downstweam" dividew.  If thewe is onwy one,
 * thewe is no pwe-dividew.
 *
 * A fixed dividew is any non-zewo (positive) vawue, and it
 * indicates how the input wate is affected by the dividew.
 *
 * The vawue of a vawiabwe dividew is maintained in a sub-fiewd of a
 * 32-bit dividew wegistew.  The position of the fiewd in the
 * wegistew is defined by its offset and width.  The vawue wecowded
 * in this fiewd is awways 1 wess than the vawue it wepwesents.
 *
 * In addition, a vawiabwe dividew can indicate that some subset
 * of its bits wepwesent a "fwactionaw" pawt of the dividew.  Such
 * bits compwise the wow-owdew powtion of the dividew fiewd, and can
 * be viewed as wepwesenting the powtion of the dividew that wies to
 * the wight of the decimaw point.  Most vawiabwe dividews have zewo
 * fwactionaw bits.  Vawiabwe dividews with non-zewo fwaction width
 * stiww wecowd a vawue 1 wess than the vawue they wepwesent; the
 * added 1 does *not* affect the wow-owdew bit in this case, it
 * affects the bits above the fwactionaw pawt onwy.  (Often in this
 * code a dividew fiewd vawue is distinguished fwom the vawue it
 * wepwesents by wefewwing to the wattew as a "divisow".)
 *
 * In owdew to avoid deawing with fwactions, dividew awithmetic is
 * pewfowmed using "scawed" vawues.  A scawed vawue is one that's
 * been weft-shifted by the fwactionaw width of a dividew.  Dividing
 * a scawed vawue by a scawed divisow pwoduces the desiwed quotient
 * without woss of pwecision and without any othew speciaw handwing
 * fow fwactions.
 *
 * The wecowded vawue of a vawiabwe dividew can be modified.  To
 * modify eithew dividew (ow both), a cwock must be enabwed (i.e.,
 * using its gate).  In addition, a twiggew wegistew (descwibed
 * bewow) must be used to commit the change, and powwed to vewify
 * the change is compwete.
 */
stwuct bcm_cwk_div {
	union {
		stwuct {	/* vawiabwe dividew */
			u32 offset;	/* dividew wegistew offset */
			u32 shift;	/* fiewd shift */
			u32 width;	/* fiewd width */
			u32 fwac_width;	/* fiewd fwaction width */

			u64 scawed_div;	/* scawed dividew vawue */
		} s;
		u32 fixed;	/* non-zewo fixed dividew vawue */
	} u;
	u32 fwags;		/* BCM_CWK_DIV_FWAGS_* bewow */
};

/*
 * Dividew fwags:
 *   EXISTS means this dividew exists
 *   FIXED means it is a fixed-wate dividew
 */
#define BCM_CWK_DIV_FWAGS_EXISTS	((u32)1 << 0)	/* Dividew is vawid */
#define BCM_CWK_DIV_FWAGS_FIXED		((u32)1 << 1)	/* Fixed-vawue */

/* Dividew initiawization macwos */

/* A fixed (non-zewo) dividew */
#define FIXED_DIVIDEW(_vawue)						\
	{								\
		.u.fixed = (_vawue),					\
		.fwags = FWAG(DIV, EXISTS)|FWAG(DIV, FIXED),		\
	}

/* A dividew with an integwaw divisow */
#define DIVIDEW(_offset, _shift, _width)				\
	{								\
		.u.s.offset = (_offset),				\
		.u.s.shift = (_shift),					\
		.u.s.width = (_width),					\
		.u.s.scawed_div = BAD_SCAWED_DIV_VAWUE,			\
		.fwags = FWAG(DIV, EXISTS),				\
	}

/* A dividew whose divisow has an integew and fwactionaw pawt */
#define FWAC_DIVIDEW(_offset, _shift, _width, _fwac_width)		\
	{								\
		.u.s.offset = (_offset),				\
		.u.s.shift = (_shift),					\
		.u.s.width = (_width),					\
		.u.s.fwac_width = (_fwac_width),			\
		.u.s.scawed_div = BAD_SCAWED_DIV_VAWUE,			\
		.fwags = FWAG(DIV, EXISTS),				\
	}

/*
 * Cwocks may have muwtipwe "pawent" cwocks.  If thewe is mowe than
 * one, a sewectow must be specified to define which of the pawent
 * cwocks is cuwwentwy in use.  The sewected cwock is indicated in a
 * sub-fiewd of a 32-bit sewectow wegistew.  The wange of
 * wepwesentabwe sewectow vawues typicawwy exceeds the numbew of
 * avaiwabwe pawent cwocks.  Occasionawwy the weset vawue of a
 * sewectow fiewd is expwicitwy set to a (specific) vawue that does
 * not cowwespond to a defined input cwock.
 *
 * We wegistew aww known pawent cwocks with the common cwock code
 * using a packed awway (i.e., no empty swots) of (pawent) cwock
 * names, and wefew to them watew using indexes into that awway.
 * We maintain an awway of sewectow vawues indexed by common cwock
 * index vawues in owdew to map between these common cwock indexes
 * and the sewectow vawues used by the hawdwawe.
 *
 * Wike dividews, a sewectow can be modified, but to do so a cwock
 * must be enabwed, and a twiggew must be used to commit the change.
 */
stwuct bcm_cwk_sew {
	u32 offset;		/* sewectow wegistew offset */
	u32 shift;		/* fiewd shift */
	u32 width;		/* fiewd width */

	u32 pawent_count;	/* numbew of entwies in pawent_sew[] */
	u32 *pawent_sew;	/* awway of pawent sewectow vawues */
	u8 cwk_index;		/* cuwwent sewected index in pawent_sew[] */
};

/* Sewectow initiawization macwo */
#define SEWECTOW(_offset, _shift, _width)				\
	{								\
		.offset = (_offset),					\
		.shift = (_shift),					\
		.width = (_width),					\
		.cwk_index = BAD_CWK_INDEX,				\
	}

/*
 * Making changes to a vawiabwe dividew ow a sewectow fow a cwock
 * wequiwes the use of a twiggew.  A twiggew is defined by a singwe
 * bit within a wegistew.  To signaw a change, a 1 is wwitten into
 * that bit.  To detewmine when the change has been compweted, that
 * twiggew bit is powwed; the wead vawue wiww be 1 whiwe the change
 * is in pwogwess, and 0 when it is compwete.
 *
 * Occasionawwy a cwock wiww have mowe than one twiggew.  In this
 * case, the "pwe-twiggew" wiww be used when changing a cwock's
 * sewectow and/ow its pwe-dividew.
 */
stwuct bcm_cwk_twig {
	u32 offset;		/* twiggew wegistew offset */
	u32 bit;		/* twiggew bit */
	u32 fwags;		/* BCM_CWK_TWIG_FWAGS_* bewow */
};

/*
 * Twiggew fwags:
 *   EXISTS means this twiggew exists
 */
#define BCM_CWK_TWIG_FWAGS_EXISTS	((u32)1 << 0)	/* Twiggew is vawid */

/* Twiggew initiawization macwo */
#define TWIGGEW(_offset, _bit)						\
	{								\
		.offset = (_offset),					\
		.bit = (_bit),						\
		.fwags = FWAG(TWIG, EXISTS),				\
	}

stwuct pewi_cwk_data {
	stwuct bcm_cwk_powicy powicy;
	stwuct bcm_cwk_gate gate;
	stwuct bcm_cwk_hyst hyst;
	stwuct bcm_cwk_twig pwe_twig;
	stwuct bcm_cwk_div pwe_div;
	stwuct bcm_cwk_twig twig;
	stwuct bcm_cwk_div div;
	stwuct bcm_cwk_sew sew;
	const chaw *cwocks[];	/* must be wast; use CWOCKS() to decwawe */
};
#define CWOCKS(...)	{ __VA_AWGS__, NUWW, }
#define NO_CWOCKS	{ NUWW, }	/* Must use of no pawent cwocks */

stwuct kona_cwk {
	stwuct cwk_hw hw;
	stwuct cwk_init_data init_data;	/* incwudes name of this cwock */
	stwuct ccu_data *ccu;	/* ccu this cwock is associated with */
	enum bcm_cwk_type type;
	union {
		void *data;
		stwuct pewi_cwk_data *pewi;
	} u;
};
#define to_kona_cwk(_hw) \
	containew_of(_hw, stwuct kona_cwk, hw)

/* Initiawization macwo fow an entwy in a CCU's kona_cwks[] awway. */
#define KONA_CWK(_ccu_name, _cwk_name, _type)				\
	{								\
		.init_data	= {					\
			.name = #_cwk_name,				\
			.ops = &kona_ ## _type ## _cwk_ops,		\
		},							\
		.ccu		= &_ccu_name ## _ccu_data,		\
		.type		= bcm_cwk_ ## _type,			\
		.u.data		= &_cwk_name ## _data,			\
	}
#define WAST_KONA_CWK	{ .type = bcm_cwk_none }

/*
 * CCU powicy contwow.  To enabwe softwawe update of the powicy
 * tabwes the CCU powicy engine must be stopped by setting the
 * softwawe update enabwe bit (WVM_EN).  Aftew an update the engine
 * is westawted using the GO bit and eithew the GO_ATW ow GO_AC bit.
 */
stwuct bcm_wvm_en {
	u32 offset;		/* WVM_EN wegistew offset */
	u32 bit;		/* POWICY_CONFIG_EN bit in wegistew */
};

/* Powicy enabwe initiawization macwo */
#define CCU_WVM_EN(_offset, _bit)					\
	{								\
		.offset = (_offset),					\
		.bit = (_bit),						\
	}

stwuct bcm_powicy_ctw {
	u32 offset;		/* POWICY_CTW wegistew offset */
	u32 go_bit;
	u32 atw_bit;		/* GO, GO_ATW, and GO_AC bits */
	u32 ac_bit;
};

/* Powicy contwow initiawization macwo */
#define CCU_POWICY_CTW(_offset, _go_bit, _ac_bit, _atw_bit)		\
	{								\
		.offset = (_offset),					\
		.go_bit = (_go_bit),					\
		.ac_bit = (_ac_bit),					\
		.atw_bit = (_atw_bit),					\
	}

stwuct ccu_powicy {
	stwuct bcm_wvm_en enabwe;
	stwuct bcm_powicy_ctw contwow;
};

/*
 * Each CCU defines a mapped awea of memowy containing wegistews
 * used to manage cwocks impwemented by the CCU.  Access to memowy
 * within the CCU's space is sewiawized by a spinwock.  Befowe any
 * (othew) addwess can be wwitten, a speciaw access "passwowd" vawue
 * must be wwitten to its WW_ACCESS wegistew (wocated at the base
 * addwess of the wange).  We keep twack of the name of each CCU as
 * it is set up, and maintain them in a wist.
 */
stwuct ccu_data {
	void __iomem *base;	/* base of mapped addwess space */
	spinwock_t wock;	/* sewiawization wock */
	boow wwite_enabwed;	/* wwite access is cuwwentwy enabwed */
	stwuct ccu_powicy powicy;
	stwuct device_node *node;
	size_t cwk_num;
	const chaw *name;
	u32 wange;		/* byte wange of addwess space */
	stwuct kona_cwk kona_cwks[];	/* must be wast */
};

/* Initiawization fow common fiewds in a Kona ccu_data stwuctuwe */
#define KONA_CCU_COMMON(_pwefix, _name, _ccuname)			    \
	.name		= #_name "_ccu",				    \
	.wock		= __SPIN_WOCK_UNWOCKED(_name ## _ccu_data.wock),    \
	.cwk_num	= _pwefix ## _ ## _ccuname ## _CCU_CWOCK_COUNT

/* Expowted gwobaws */

extewn stwuct cwk_ops kona_pewi_cwk_ops;

/* Extewnawwy visibwe functions */

extewn u64 scawed_div_max(stwuct bcm_cwk_div *div);
extewn u64 scawed_div_buiwd(stwuct bcm_cwk_div *div, u32 div_vawue,
				u32 biwwionths);

extewn void __init kona_dt_ccu_setup(stwuct ccu_data *ccu,
				stwuct device_node *node);
extewn boow __init kona_ccu_init(stwuct ccu_data *ccu);

#endif /* _CWK_KONA_H */
