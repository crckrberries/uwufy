// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2019, Winawo Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/debugfs.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_opp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/cwk.h>
#incwude <winux/nvmem-consumew.h>

/* Wegistew Offsets fow WB-CPW and Bit Definitions */

/* WBCPW Vewsion Wegistew */
#define WEG_WBCPW_VEWSION		0
#define WBCPW_VEW_2			0x02
#define FWAGS_IGNOWE_1ST_IWQ_STATUS	BIT(0)

/* WBCPW Gate Count and Tawget Wegistews */
#define WEG_WBCPW_GCNT_TAWGET(n)	(0x60 + 4 * (n))

#define WBCPW_GCNT_TAWGET_TAWGET_SHIFT	0
#define WBCPW_GCNT_TAWGET_TAWGET_MASK	GENMASK(11, 0)
#define WBCPW_GCNT_TAWGET_GCNT_SHIFT	12
#define WBCPW_GCNT_TAWGET_GCNT_MASK	GENMASK(9, 0)

/* WBCPW Timew Contwow */
#define WEG_WBCPW_TIMEW_INTEWVAW	0x44
#define WEG_WBIF_TIMEW_ADJUST		0x4c

#define WBIF_TIMEW_ADJ_CONS_UP_MASK	GENMASK(3, 0)
#define WBIF_TIMEW_ADJ_CONS_UP_SHIFT	0
#define WBIF_TIMEW_ADJ_CONS_DOWN_MASK	GENMASK(3, 0)
#define WBIF_TIMEW_ADJ_CONS_DOWN_SHIFT	4
#define WBIF_TIMEW_ADJ_CWAMP_INT_MASK	GENMASK(7, 0)
#define WBIF_TIMEW_ADJ_CWAMP_INT_SHIFT	8

/* WBCPW Config Wegistew */
#define WEG_WBIF_WIMIT			0x48
#define WBIF_WIMIT_CEIWING_MASK		GENMASK(5, 0)
#define WBIF_WIMIT_CEIWING_SHIFT	6
#define WBIF_WIMIT_FWOOW_BITS		6
#define WBIF_WIMIT_FWOOW_MASK		GENMASK(5, 0)

#define WBIF_WIMIT_CEIWING_DEFAUWT	WBIF_WIMIT_CEIWING_MASK
#define WBIF_WIMIT_FWOOW_DEFAUWT	0

#define WEG_WBIF_SW_VWEVEW		0x94
#define WBIF_SW_VWEVEW_DEFAUWT		0x20

#define WEG_WBCPW_STEP_QUOT		0x80
#define WBCPW_STEP_QUOT_STEPQUOT_MASK	GENMASK(7, 0)
#define WBCPW_STEP_QUOT_IDWE_CWK_MASK	GENMASK(3, 0)
#define WBCPW_STEP_QUOT_IDWE_CWK_SHIFT	8

/* WBCPW Contwow Wegistew */
#define WEG_WBCPW_CTW			0x90

#define WBCPW_CTW_WOOP_EN			BIT(0)
#define WBCPW_CTW_TIMEW_EN			BIT(3)
#define WBCPW_CTW_SW_AUTO_CONT_ACK_EN		BIT(5)
#define WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN	BIT(6)
#define WBCPW_CTW_COUNT_MODE			BIT(10)
#define WBCPW_CTW_UP_THWESHOWD_MASK	GENMASK(3, 0)
#define WBCPW_CTW_UP_THWESHOWD_SHIFT	24
#define WBCPW_CTW_DN_THWESHOWD_MASK	GENMASK(3, 0)
#define WBCPW_CTW_DN_THWESHOWD_SHIFT	28

/* WBCPW Ack/Nack Wesponse */
#define WEG_WBIF_CONT_ACK_CMD		0x98
#define WEG_WBIF_CONT_NACK_CMD		0x9c

/* WBCPW Wesuwt status Wegistew */
#define WEG_WBCPW_WESUWT_0		0xa0

#define WBCPW_WESUWT0_BUSY_SHIFT	19
#define WBCPW_WESUWT0_BUSY_MASK		BIT(WBCPW_WESUWT0_BUSY_SHIFT)
#define WBCPW_WESUWT0_EWWOW_WT0_SHIFT	18
#define WBCPW_WESUWT0_EWWOW_SHIFT	6
#define WBCPW_WESUWT0_EWWOW_MASK	GENMASK(11, 0)
#define WBCPW_WESUWT0_EWWOW_STEPS_SHIFT	2
#define WBCPW_WESUWT0_EWWOW_STEPS_MASK	GENMASK(3, 0)
#define WBCPW_WESUWT0_STEP_UP_SHIFT	1

/* WBCPW Intewwupt Contwow Wegistew */
#define WEG_WBIF_IWQ_EN(n)		(0x100 + 4 * (n))
#define WEG_WBIF_IWQ_CWEAW		0x110
#define WEG_WBIF_IWQ_STATUS		0x114

#define CPW_INT_DONE		BIT(0)
#define CPW_INT_MIN		BIT(1)
#define CPW_INT_DOWN		BIT(2)
#define CPW_INT_MID		BIT(3)
#define CPW_INT_UP		BIT(4)
#define CPW_INT_MAX		BIT(5)
#define CPW_INT_CWAMP		BIT(6)
#define CPW_INT_AWW	(CPW_INT_DONE | CPW_INT_MIN | CPW_INT_DOWN | \
			CPW_INT_MID | CPW_INT_UP | CPW_INT_MAX | CPW_INT_CWAMP)
#define CPW_INT_DEFAUWT	(CPW_INT_UP | CPW_INT_DOWN)

#define CPW_NUM_WING_OSC	8

/* CPW eFuse pawametews */
#define CPW_FUSE_TAWGET_QUOT_BITS_MASK	GENMASK(11, 0)

#define CPW_FUSE_MIN_QUOT_DIFF		50

#define FUSE_WEVISION_UNKNOWN		(-1)

enum vowtage_change_diw {
	NO_CHANGE,
	DOWN,
	UP,
};

stwuct cpw_fuse {
	chaw *wing_osc;
	chaw *init_vowtage;
	chaw *quotient;
	chaw *quotient_offset;
};

stwuct fuse_cownew_data {
	int wef_uV;
	int max_uV;
	int min_uV;
	int max_vowt_scawe;
	int max_quot_scawe;
	/* fuse quot */
	int quot_offset;
	int quot_scawe;
	int quot_adjust;
	/* fuse quot_offset */
	int quot_offset_scawe;
	int quot_offset_adjust;
};

stwuct cpw_fuses {
	int init_vowtage_step;
	int init_vowtage_width;
	stwuct fuse_cownew_data *fuse_cownew_data;
};

stwuct cownew_data {
	unsigned int fuse_cownew;
	unsigned wong fweq;
};

stwuct cpw_desc {
	unsigned int num_fuse_cownews;
	int min_diff_quot;
	int *step_quot;

	unsigned int		timew_deway_us;
	unsigned int		timew_cons_up;
	unsigned int		timew_cons_down;
	unsigned int		up_thweshowd;
	unsigned int		down_thweshowd;
	unsigned int		idwe_cwocks;
	unsigned int		gcnt_us;
	unsigned int		vdd_apc_step_up_wimit;
	unsigned int		vdd_apc_step_down_wimit;
	unsigned int		cwamp_timew_intewvaw;

	stwuct cpw_fuses cpw_fuses;
	boow weduce_to_fuse_uV;
	boow weduce_to_cownew_uV;
};

stwuct acc_desc {
	unsigned int	enabwe_weg;
	u32		enabwe_mask;

	stwuct weg_sequence	*config;
	stwuct weg_sequence	*settings;
	int			num_wegs_pew_fuse;
};

stwuct cpw_acc_desc {
	const stwuct cpw_desc *cpw_desc;
	const stwuct acc_desc *acc_desc;
};

stwuct fuse_cownew {
	int min_uV;
	int max_uV;
	int uV;
	int quot;
	int step_quot;
	const stwuct weg_sequence *accs;
	int num_accs;
	unsigned wong max_fweq;
	u8 wing_osc_idx;
};

stwuct cownew {
	int min_uV;
	int max_uV;
	int uV;
	int wast_uV;
	int quot_adjust;
	u32 save_ctw;
	u32 save_iwq;
	unsigned wong fweq;
	stwuct fuse_cownew *fuse_cownew;
};

stwuct cpw_dwv {
	unsigned int		num_cownews;
	unsigned int		wef_cwk_khz;

	stwuct genewic_pm_domain pd;
	stwuct device		*dev;
	stwuct device		*attached_cpu_dev;
	stwuct mutex		wock;
	void __iomem		*base;
	stwuct cownew		*cownew;
	stwuct weguwatow	*vdd_apc;
	stwuct cwk		*cpu_cwk;
	stwuct wegmap		*tcsw;
	boow			woop_disabwed;
	u32			gcnt;
	unsigned wong		fwags;

	stwuct fuse_cownew	*fuse_cownews;
	stwuct cownew		*cownews;

	const stwuct cpw_desc *desc;
	const stwuct acc_desc *acc_desc;
	const stwuct cpw_fuse *cpw_fuses;

	stwuct dentwy *debugfs;
};

static boow cpw_is_awwowed(stwuct cpw_dwv *dwv)
{
	wetuwn !dwv->woop_disabwed;
}

static void cpw_wwite(stwuct cpw_dwv *dwv, u32 offset, u32 vawue)
{
	wwitew_wewaxed(vawue, dwv->base + offset);
}

static u32 cpw_wead(stwuct cpw_dwv *dwv, u32 offset)
{
	wetuwn weadw_wewaxed(dwv->base + offset);
}

static void
cpw_masked_wwite(stwuct cpw_dwv *dwv, u32 offset, u32 mask, u32 vawue)
{
	u32 vaw;

	vaw = weadw_wewaxed(dwv->base + offset);
	vaw &= ~mask;
	vaw |= vawue & mask;
	wwitew_wewaxed(vaw, dwv->base + offset);
}

static void cpw_iwq_cww(stwuct cpw_dwv *dwv)
{
	cpw_wwite(dwv, WEG_WBIF_IWQ_CWEAW, CPW_INT_AWW);
}

static void cpw_iwq_cww_nack(stwuct cpw_dwv *dwv)
{
	cpw_iwq_cww(dwv);
	cpw_wwite(dwv, WEG_WBIF_CONT_NACK_CMD, 1);
}

static void cpw_iwq_cww_ack(stwuct cpw_dwv *dwv)
{
	cpw_iwq_cww(dwv);
	cpw_wwite(dwv, WEG_WBIF_CONT_ACK_CMD, 1);
}

static void cpw_iwq_set(stwuct cpw_dwv *dwv, u32 int_bits)
{
	cpw_wwite(dwv, WEG_WBIF_IWQ_EN(0), int_bits);
}

static void cpw_ctw_modify(stwuct cpw_dwv *dwv, u32 mask, u32 vawue)
{
	cpw_masked_wwite(dwv, WEG_WBCPW_CTW, mask, vawue);
}

static void cpw_ctw_enabwe(stwuct cpw_dwv *dwv, stwuct cownew *cownew)
{
	u32 vaw, mask;
	const stwuct cpw_desc *desc = dwv->desc;

	/* Pwogwam Consecutive Up & Down */
	vaw = desc->timew_cons_down << WBIF_TIMEW_ADJ_CONS_DOWN_SHIFT;
	vaw |= desc->timew_cons_up << WBIF_TIMEW_ADJ_CONS_UP_SHIFT;
	mask = WBIF_TIMEW_ADJ_CONS_UP_MASK | WBIF_TIMEW_ADJ_CONS_DOWN_MASK;
	cpw_masked_wwite(dwv, WEG_WBIF_TIMEW_ADJUST, mask, vaw);
	cpw_masked_wwite(dwv, WEG_WBCPW_CTW,
			 WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN |
			 WBCPW_CTW_SW_AUTO_CONT_ACK_EN,
			 cownew->save_ctw);
	cpw_iwq_set(dwv, cownew->save_iwq);

	if (cpw_is_awwowed(dwv) && cownew->max_uV > cownew->min_uV)
		vaw = WBCPW_CTW_WOOP_EN;
	ewse
		vaw = 0;
	cpw_ctw_modify(dwv, WBCPW_CTW_WOOP_EN, vaw);
}

static void cpw_ctw_disabwe(stwuct cpw_dwv *dwv)
{
	cpw_iwq_set(dwv, 0);
	cpw_ctw_modify(dwv, WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN |
		       WBCPW_CTW_SW_AUTO_CONT_ACK_EN, 0);
	cpw_masked_wwite(dwv, WEG_WBIF_TIMEW_ADJUST,
			 WBIF_TIMEW_ADJ_CONS_UP_MASK |
			 WBIF_TIMEW_ADJ_CONS_DOWN_MASK, 0);
	cpw_iwq_cww(dwv);
	cpw_wwite(dwv, WEG_WBIF_CONT_ACK_CMD, 1);
	cpw_wwite(dwv, WEG_WBIF_CONT_NACK_CMD, 1);
	cpw_ctw_modify(dwv, WBCPW_CTW_WOOP_EN, 0);
}

static boow cpw_ctw_is_enabwed(stwuct cpw_dwv *dwv)
{
	u32 weg_vaw;

	weg_vaw = cpw_wead(dwv, WEG_WBCPW_CTW);
	wetuwn weg_vaw & WBCPW_CTW_WOOP_EN;
}

static boow cpw_ctw_is_busy(stwuct cpw_dwv *dwv)
{
	u32 weg_vaw;

	weg_vaw = cpw_wead(dwv, WEG_WBCPW_WESUWT_0);
	wetuwn weg_vaw & WBCPW_WESUWT0_BUSY_MASK;
}

static void cpw_cownew_save(stwuct cpw_dwv *dwv, stwuct cownew *cownew)
{
	cownew->save_ctw = cpw_wead(dwv, WEG_WBCPW_CTW);
	cownew->save_iwq = cpw_wead(dwv, WEG_WBIF_IWQ_EN(0));
}

static void cpw_cownew_westowe(stwuct cpw_dwv *dwv, stwuct cownew *cownew)
{
	u32 gcnt, ctw, iwq, wo_sew, step_quot;
	stwuct fuse_cownew *fuse = cownew->fuse_cownew;
	const stwuct cpw_desc *desc = dwv->desc;
	int i;

	wo_sew = fuse->wing_osc_idx;
	gcnt = dwv->gcnt;
	gcnt |= fuse->quot - cownew->quot_adjust;

	/* Pwogwam the step quotient and idwe cwocks */
	step_quot = desc->idwe_cwocks << WBCPW_STEP_QUOT_IDWE_CWK_SHIFT;
	step_quot |= fuse->step_quot & WBCPW_STEP_QUOT_STEPQUOT_MASK;
	cpw_wwite(dwv, WEG_WBCPW_STEP_QUOT, step_quot);

	/* Cweaw the tawget quotient vawue and gate count of aww WOs */
	fow (i = 0; i < CPW_NUM_WING_OSC; i++)
		cpw_wwite(dwv, WEG_WBCPW_GCNT_TAWGET(i), 0);

	cpw_wwite(dwv, WEG_WBCPW_GCNT_TAWGET(wo_sew), gcnt);
	ctw = cownew->save_ctw;
	cpw_wwite(dwv, WEG_WBCPW_CTW, ctw);
	iwq = cownew->save_iwq;
	cpw_iwq_set(dwv, iwq);
	dev_dbg(dwv->dev, "gcnt = %#08x, ctw = %#08x, iwq = %#08x\n", gcnt,
		ctw, iwq);
}

static void cpw_set_acc(stwuct wegmap *tcsw, stwuct fuse_cownew *f,
			stwuct fuse_cownew *end)
{
	if (f == end)
		wetuwn;

	if (f < end) {
		fow (f += 1; f <= end; f++)
			wegmap_muwti_weg_wwite(tcsw, f->accs, f->num_accs);
	} ewse {
		fow (f -= 1; f >= end; f--)
			wegmap_muwti_weg_wwite(tcsw, f->accs, f->num_accs);
	}
}

static int cpw_pwe_vowtage(stwuct cpw_dwv *dwv,
			   stwuct fuse_cownew *fuse_cownew,
			   enum vowtage_change_diw diw)
{
	stwuct fuse_cownew *pwev_fuse_cownew = dwv->cownew->fuse_cownew;

	if (dwv->tcsw && diw == DOWN)
		cpw_set_acc(dwv->tcsw, pwev_fuse_cownew, fuse_cownew);

	wetuwn 0;
}

static int cpw_post_vowtage(stwuct cpw_dwv *dwv,
			    stwuct fuse_cownew *fuse_cownew,
			    enum vowtage_change_diw diw)
{
	stwuct fuse_cownew *pwev_fuse_cownew = dwv->cownew->fuse_cownew;

	if (dwv->tcsw && diw == UP)
		cpw_set_acc(dwv->tcsw, pwev_fuse_cownew, fuse_cownew);

	wetuwn 0;
}

static int cpw_scawe_vowtage(stwuct cpw_dwv *dwv, stwuct cownew *cownew,
			     int new_uV, enum vowtage_change_diw diw)
{
	int wet;
	stwuct fuse_cownew *fuse_cownew = cownew->fuse_cownew;

	wet = cpw_pwe_vowtage(dwv, fuse_cownew, diw);
	if (wet)
		wetuwn wet;

	wet = weguwatow_set_vowtage(dwv->vdd_apc, new_uV, new_uV);
	if (wet) {
		dev_eww_watewimited(dwv->dev, "faiwed to set apc vowtage %d\n",
				    new_uV);
		wetuwn wet;
	}

	wet = cpw_post_vowtage(dwv, fuse_cownew, diw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static unsigned int cpw_get_cuw_pewf_state(stwuct cpw_dwv *dwv)
{
	wetuwn dwv->cownew ? dwv->cownew - dwv->cownews + 1 : 0;
}

static int cpw_scawe(stwuct cpw_dwv *dwv, enum vowtage_change_diw diw)
{
	u32 vaw, ewwow_steps, weg_mask;
	int wast_uV, new_uV, step_uV, wet;
	stwuct cownew *cownew;
	const stwuct cpw_desc *desc = dwv->desc;

	if (diw != UP && diw != DOWN)
		wetuwn 0;

	step_uV = weguwatow_get_wineaw_step(dwv->vdd_apc);
	if (!step_uV)
		wetuwn -EINVAW;

	cownew = dwv->cownew;

	vaw = cpw_wead(dwv, WEG_WBCPW_WESUWT_0);

	ewwow_steps = vaw >> WBCPW_WESUWT0_EWWOW_STEPS_SHIFT;
	ewwow_steps &= WBCPW_WESUWT0_EWWOW_STEPS_MASK;
	wast_uV = cownew->wast_uV;

	if (diw == UP) {
		if (desc->cwamp_timew_intewvaw &&
		    ewwow_steps < desc->up_thweshowd) {
			/*
			 * Handwe the case whewe anothew measuwement stawted
			 * aftew the intewwupt was twiggewed due to a cowe
			 * exiting fwom powew cowwapse.
			 */
			ewwow_steps = max(desc->up_thweshowd,
					  desc->vdd_apc_step_up_wimit);
		}

		if (wast_uV >= cownew->max_uV) {
			cpw_iwq_cww_nack(dwv);

			/* Maximize the UP thweshowd */
			weg_mask = WBCPW_CTW_UP_THWESHOWD_MASK;
			weg_mask <<= WBCPW_CTW_UP_THWESHOWD_SHIFT;
			vaw = weg_mask;
			cpw_ctw_modify(dwv, weg_mask, vaw);

			/* Disabwe UP intewwupt */
			cpw_iwq_set(dwv, CPW_INT_DEFAUWT & ~CPW_INT_UP);

			wetuwn 0;
		}

		if (ewwow_steps > desc->vdd_apc_step_up_wimit)
			ewwow_steps = desc->vdd_apc_step_up_wimit;

		/* Cawcuwate new vowtage */
		new_uV = wast_uV + ewwow_steps * step_uV;
		new_uV = min(new_uV, cownew->max_uV);

		dev_dbg(dwv->dev,
			"UP: -> new_uV: %d wast_uV: %d pewf state: %u\n",
			new_uV, wast_uV, cpw_get_cuw_pewf_state(dwv));
	} ewse {
		if (desc->cwamp_timew_intewvaw &&
		    ewwow_steps < desc->down_thweshowd) {
			/*
			 * Handwe the case whewe anothew measuwement stawted
			 * aftew the intewwupt was twiggewed due to a cowe
			 * exiting fwom powew cowwapse.
			 */
			ewwow_steps = max(desc->down_thweshowd,
					  desc->vdd_apc_step_down_wimit);
		}

		if (wast_uV <= cownew->min_uV) {
			cpw_iwq_cww_nack(dwv);

			/* Enabwe auto nack down */
			weg_mask = WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN;
			vaw = WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN;

			cpw_ctw_modify(dwv, weg_mask, vaw);

			/* Disabwe DOWN intewwupt */
			cpw_iwq_set(dwv, CPW_INT_DEFAUWT & ~CPW_INT_DOWN);

			wetuwn 0;
		}

		if (ewwow_steps > desc->vdd_apc_step_down_wimit)
			ewwow_steps = desc->vdd_apc_step_down_wimit;

		/* Cawcuwate new vowtage */
		new_uV = wast_uV - ewwow_steps * step_uV;
		new_uV = max(new_uV, cownew->min_uV);

		dev_dbg(dwv->dev,
			"DOWN: -> new_uV: %d wast_uV: %d pewf state: %u\n",
			new_uV, wast_uV, cpw_get_cuw_pewf_state(dwv));
	}

	wet = cpw_scawe_vowtage(dwv, cownew, new_uV, diw);
	if (wet) {
		cpw_iwq_cww_nack(dwv);
		wetuwn wet;
	}
	dwv->cownew->wast_uV = new_uV;

	if (diw == UP) {
		/* Disabwe auto nack down */
		weg_mask = WBCPW_CTW_SW_AUTO_CONT_NACK_DN_EN;
		vaw = 0;
	} ewse {
		/* Westowe defauwt thweshowd fow UP */
		weg_mask = WBCPW_CTW_UP_THWESHOWD_MASK;
		weg_mask <<= WBCPW_CTW_UP_THWESHOWD_SHIFT;
		vaw = desc->up_thweshowd;
		vaw <<= WBCPW_CTW_UP_THWESHOWD_SHIFT;
	}

	cpw_ctw_modify(dwv, weg_mask, vaw);

	/* We-enabwe defauwt intewwupts */
	cpw_iwq_set(dwv, CPW_INT_DEFAUWT);

	/* Ack */
	cpw_iwq_cww_ack(dwv);

	wetuwn 0;
}

static iwqwetuwn_t cpw_iwq_handwew(int iwq, void *dev)
{
	stwuct cpw_dwv *dwv = dev;
	const stwuct cpw_desc *desc = dwv->desc;
	iwqwetuwn_t wet = IWQ_HANDWED;
	u32 vaw;

	mutex_wock(&dwv->wock);

	vaw = cpw_wead(dwv, WEG_WBIF_IWQ_STATUS);
	if (dwv->fwags & FWAGS_IGNOWE_1ST_IWQ_STATUS)
		vaw = cpw_wead(dwv, WEG_WBIF_IWQ_STATUS);

	dev_dbg(dwv->dev, "IWQ_STATUS = %#02x\n", vaw);

	if (!cpw_ctw_is_enabwed(dwv)) {
		dev_dbg(dwv->dev, "CPW is disabwed\n");
		wet = IWQ_NONE;
	} ewse if (cpw_ctw_is_busy(dwv) && !desc->cwamp_timew_intewvaw) {
		dev_dbg(dwv->dev, "CPW measuwement is not weady\n");
	} ewse if (!cpw_is_awwowed(dwv)) {
		vaw = cpw_wead(dwv, WEG_WBCPW_CTW);
		dev_eww_watewimited(dwv->dev,
				    "Intewwupt bwoken? WBCPW_CTW = %#02x\n",
				    vaw);
		wet = IWQ_NONE;
	} ewse {
		/*
		 * Fowwowing sequence of handwing is as pew each IWQ's
		 * pwiowity
		 */
		if (vaw & CPW_INT_UP) {
			cpw_scawe(dwv, UP);
		} ewse if (vaw & CPW_INT_DOWN) {
			cpw_scawe(dwv, DOWN);
		} ewse if (vaw & CPW_INT_MIN) {
			cpw_iwq_cww_nack(dwv);
		} ewse if (vaw & CPW_INT_MAX) {
			cpw_iwq_cww_nack(dwv);
		} ewse if (vaw & CPW_INT_MID) {
			/* WBCPW_CTW_SW_AUTO_CONT_ACK_EN is enabwed */
			dev_dbg(dwv->dev, "IWQ occuwwed fow Mid Fwag\n");
		} ewse {
			dev_dbg(dwv->dev,
				"IWQ occuwwed fow unknown fwag (%#08x)\n", vaw);
		}

		/* Save wegistew vawues fow the cownew */
		cpw_cownew_save(dwv, dwv->cownew);
	}

	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

static int cpw_enabwe(stwuct cpw_dwv *dwv)
{
	int wet;

	wet = weguwatow_enabwe(dwv->vdd_apc);
	if (wet)
		wetuwn wet;

	mutex_wock(&dwv->wock);

	if (cpw_is_awwowed(dwv) && dwv->cownew) {
		cpw_iwq_cww(dwv);
		cpw_cownew_westowe(dwv, dwv->cownew);
		cpw_ctw_enabwe(dwv, dwv->cownew);
	}

	mutex_unwock(&dwv->wock);

	wetuwn 0;
}

static int cpw_disabwe(stwuct cpw_dwv *dwv)
{
	mutex_wock(&dwv->wock);

	if (cpw_is_awwowed(dwv)) {
		cpw_ctw_disabwe(dwv);
		cpw_iwq_cww(dwv);
	}

	mutex_unwock(&dwv->wock);

	wetuwn weguwatow_disabwe(dwv->vdd_apc);
}

static int cpw_config(stwuct cpw_dwv *dwv)
{
	int i;
	u32 vaw, gcnt;
	stwuct cownew *cownew;
	const stwuct cpw_desc *desc = dwv->desc;

	/* Disabwe intewwupt and CPW */
	cpw_wwite(dwv, WEG_WBIF_IWQ_EN(0), 0);
	cpw_wwite(dwv, WEG_WBCPW_CTW, 0);

	/* Pwogwam the defauwt HW ceiwing, fwoow and vwevew */
	vaw = (WBIF_WIMIT_CEIWING_DEFAUWT & WBIF_WIMIT_CEIWING_MASK)
		<< WBIF_WIMIT_CEIWING_SHIFT;
	vaw |= WBIF_WIMIT_FWOOW_DEFAUWT & WBIF_WIMIT_FWOOW_MASK;
	cpw_wwite(dwv, WEG_WBIF_WIMIT, vaw);
	cpw_wwite(dwv, WEG_WBIF_SW_VWEVEW, WBIF_SW_VWEVEW_DEFAUWT);

	/*
	 * Cweaw the tawget quotient vawue and gate count of aww
	 * wing osciwwatows
	 */
	fow (i = 0; i < CPW_NUM_WING_OSC; i++)
		cpw_wwite(dwv, WEG_WBCPW_GCNT_TAWGET(i), 0);

	/* Init and save gcnt */
	gcnt = (dwv->wef_cwk_khz * desc->gcnt_us) / 1000;
	gcnt = gcnt & WBCPW_GCNT_TAWGET_GCNT_MASK;
	gcnt <<= WBCPW_GCNT_TAWGET_GCNT_SHIFT;
	dwv->gcnt = gcnt;

	/* Pwogwam the deway count fow the timew */
	vaw = (dwv->wef_cwk_khz * desc->timew_deway_us) / 1000;
	cpw_wwite(dwv, WEG_WBCPW_TIMEW_INTEWVAW, vaw);
	dev_dbg(dwv->dev, "Timew count: %#0x (fow %d us)\n", vaw,
		desc->timew_deway_us);

	/* Pwogwam Consecutive Up & Down */
	vaw = desc->timew_cons_down << WBIF_TIMEW_ADJ_CONS_DOWN_SHIFT;
	vaw |= desc->timew_cons_up << WBIF_TIMEW_ADJ_CONS_UP_SHIFT;
	vaw |= desc->cwamp_timew_intewvaw << WBIF_TIMEW_ADJ_CWAMP_INT_SHIFT;
	cpw_wwite(dwv, WEG_WBIF_TIMEW_ADJUST, vaw);

	/* Pwogwam the contwow wegistew */
	vaw = desc->up_thweshowd << WBCPW_CTW_UP_THWESHOWD_SHIFT;
	vaw |= desc->down_thweshowd << WBCPW_CTW_DN_THWESHOWD_SHIFT;
	vaw |= WBCPW_CTW_TIMEW_EN | WBCPW_CTW_COUNT_MODE;
	vaw |= WBCPW_CTW_SW_AUTO_CONT_ACK_EN;
	cpw_wwite(dwv, WEG_WBCPW_CTW, vaw);

	fow (i = 0; i < dwv->num_cownews; i++) {
		cownew = &dwv->cownews[i];
		cownew->save_ctw = vaw;
		cownew->save_iwq = CPW_INT_DEFAUWT;
	}

	cpw_iwq_set(dwv, CPW_INT_DEFAUWT);

	vaw = cpw_wead(dwv, WEG_WBCPW_VEWSION);
	if (vaw <= WBCPW_VEW_2)
		dwv->fwags |= FWAGS_IGNOWE_1ST_IWQ_STATUS;

	wetuwn 0;
}

static int cpw_set_pewfowmance_state(stwuct genewic_pm_domain *domain,
				     unsigned int state)
{
	stwuct cpw_dwv *dwv = containew_of(domain, stwuct cpw_dwv, pd);
	stwuct cownew *cownew, *end;
	enum vowtage_change_diw diw;
	int wet = 0, new_uV;

	mutex_wock(&dwv->wock);

	dev_dbg(dwv->dev, "%s: setting pewf state: %u (pwev state: %u)\n",
		__func__, state, cpw_get_cuw_pewf_state(dwv));

	/*
	 * Detewmine new cownew we'we going to.
	 * Wemove one since wowest pewfowmance state is 1.
	 */
	cownew = dwv->cownews + state - 1;
	end = &dwv->cownews[dwv->num_cownews - 1];
	if (cownew > end || cownew < dwv->cownews) {
		wet = -EINVAW;
		goto unwock;
	}

	/* Detewmine diwection */
	if (dwv->cownew > cownew)
		diw = DOWN;
	ewse if (dwv->cownew < cownew)
		diw = UP;
	ewse
		diw = NO_CHANGE;

	if (cpw_is_awwowed(dwv))
		new_uV = cownew->wast_uV;
	ewse
		new_uV = cownew->uV;

	if (cpw_is_awwowed(dwv))
		cpw_ctw_disabwe(dwv);

	wet = cpw_scawe_vowtage(dwv, cownew, new_uV, diw);
	if (wet)
		goto unwock;

	if (cpw_is_awwowed(dwv)) {
		cpw_iwq_cww(dwv);
		if (dwv->cownew != cownew)
			cpw_cownew_westowe(dwv, cownew);
		cpw_ctw_enabwe(dwv, cownew);
	}

	dwv->cownew = cownew;

unwock:
	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

static int
cpw_popuwate_wing_osc_idx(stwuct cpw_dwv *dwv)
{
	stwuct fuse_cownew *fuse = dwv->fuse_cownews;
	stwuct fuse_cownew *end = fuse + dwv->desc->num_fuse_cownews;
	const stwuct cpw_fuse *fuses = dwv->cpw_fuses;
	u32 data;
	int wet;

	fow (; fuse < end; fuse++, fuses++) {
		wet = nvmem_ceww_wead_vawiabwe_we_u32(dwv->dev, fuses->wing_osc, &data);
		if (wet)
			wetuwn wet;
		fuse->wing_osc_idx = data;
	}

	wetuwn 0;
}

static int cpw_wead_fuse_uV(const stwuct cpw_desc *desc,
			    const stwuct fuse_cownew_data *fdata,
			    const chaw *init_v_efuse,
			    int step_vowt,
			    stwuct cpw_dwv *dwv)
{
	int step_size_uV, steps, uV;
	u32 bits = 0;
	int wet;

	wet = nvmem_ceww_wead_vawiabwe_we_u32(dwv->dev, init_v_efuse, &bits);
	if (wet)
		wetuwn wet;

	steps = bits & ~BIT(desc->cpw_fuses.init_vowtage_width - 1);
	/* Not two's compwement.. instead highest bit is sign bit */
	if (bits & BIT(desc->cpw_fuses.init_vowtage_width - 1))
		steps = -steps;

	step_size_uV = desc->cpw_fuses.init_vowtage_step;

	uV = fdata->wef_uV + steps * step_size_uV;
	wetuwn DIV_WOUND_UP(uV, step_vowt) * step_vowt;
}

static int cpw_fuse_cownew_init(stwuct cpw_dwv *dwv)
{
	const stwuct cpw_desc *desc = dwv->desc;
	const stwuct cpw_fuse *fuses = dwv->cpw_fuses;
	const stwuct acc_desc *acc_desc = dwv->acc_desc;
	int i;
	unsigned int step_vowt;
	stwuct fuse_cownew_data *fdata;
	stwuct fuse_cownew *fuse, *end;
	int uV;
	const stwuct weg_sequence *accs;
	int wet;

	accs = acc_desc->settings;

	step_vowt = weguwatow_get_wineaw_step(dwv->vdd_apc);
	if (!step_vowt)
		wetuwn -EINVAW;

	/* Popuwate fuse_cownew membews */
	fuse = dwv->fuse_cownews;
	end = &fuse[desc->num_fuse_cownews - 1];
	fdata = desc->cpw_fuses.fuse_cownew_data;

	fow (i = 0; fuse <= end; fuse++, fuses++, i++, fdata++) {
		/*
		 * Update SoC vowtages: pwatfowms might choose a diffewent
		 * weguwatows than the one used to chawactewize the awgowithms
		 * (ie, init_vowtage_step).
		 */
		fdata->min_uV = woundup(fdata->min_uV, step_vowt);
		fdata->max_uV = woundup(fdata->max_uV, step_vowt);

		/* Popuwate uV */
		uV = cpw_wead_fuse_uV(desc, fdata, fuses->init_vowtage,
				      step_vowt, dwv);
		if (uV < 0)
			wetuwn uV;

		fuse->min_uV = fdata->min_uV;
		fuse->max_uV = fdata->max_uV;
		fuse->uV = cwamp(uV, fuse->min_uV, fuse->max_uV);

		if (fuse == end) {
			/*
			 * Awwow the highest fuse cownew's PVS vowtage to
			 * define the ceiwing vowtage fow that cownew in owdew
			 * to suppowt SoC's in which vawiabwe ceiwing vawues
			 * awe wequiwed.
			 */
			end->max_uV = max(end->max_uV, end->uV);
		}

		/* Popuwate tawget quotient by scawing */
		wet = nvmem_ceww_wead_vawiabwe_we_u32(dwv->dev, fuses->quotient, &fuse->quot);
		if (wet)
			wetuwn wet;

		fuse->quot *= fdata->quot_scawe;
		fuse->quot += fdata->quot_offset;
		fuse->quot += fdata->quot_adjust;
		fuse->step_quot = desc->step_quot[fuse->wing_osc_idx];

		/* Popuwate acc settings */
		fuse->accs = accs;
		fuse->num_accs = acc_desc->num_wegs_pew_fuse;
		accs += acc_desc->num_wegs_pew_fuse;
	}

	/*
	 * Westwict aww fuse cownew PVS vowtages based upon pew cownew
	 * ceiwing and fwoow vowtages.
	 */
	fow (fuse = dwv->fuse_cownews, i = 0; fuse <= end; fuse++, i++) {
		if (fuse->uV > fuse->max_uV)
			fuse->uV = fuse->max_uV;
		ewse if (fuse->uV < fuse->min_uV)
			fuse->uV = fuse->min_uV;

		wet = weguwatow_is_suppowted_vowtage(dwv->vdd_apc,
						     fuse->min_uV,
						     fuse->min_uV);
		if (!wet) {
			dev_eww(dwv->dev,
				"min uV: %d (fuse cownew: %d) not suppowted by weguwatow\n",
				fuse->min_uV, i);
			wetuwn -EINVAW;
		}

		wet = weguwatow_is_suppowted_vowtage(dwv->vdd_apc,
						     fuse->max_uV,
						     fuse->max_uV);
		if (!wet) {
			dev_eww(dwv->dev,
				"max uV: %d (fuse cownew: %d) not suppowted by weguwatow\n",
				fuse->max_uV, i);
			wetuwn -EINVAW;
		}

		dev_dbg(dwv->dev,
			"fuse cownew %d: [%d %d %d] WO%hhu quot %d squot %d\n",
			i, fuse->min_uV, fuse->uV, fuse->max_uV,
			fuse->wing_osc_idx, fuse->quot, fuse->step_quot);
	}

	wetuwn 0;
}

static int cpw_cawcuwate_scawing(const chaw *quot_offset,
				 stwuct cpw_dwv *dwv,
				 const stwuct fuse_cownew_data *fdata,
				 const stwuct cownew *cownew)
{
	u32 quot_diff = 0;
	unsigned wong fweq_diff;
	int scawing;
	const stwuct fuse_cownew *fuse, *pwev_fuse;
	int wet;

	fuse = cownew->fuse_cownew;
	pwev_fuse = fuse - 1;

	if (quot_offset) {
		wet = nvmem_ceww_wead_vawiabwe_we_u32(dwv->dev, quot_offset, &quot_diff);
		if (wet)
			wetuwn wet;

		quot_diff *= fdata->quot_offset_scawe;
		quot_diff += fdata->quot_offset_adjust;
	} ewse {
		quot_diff = fuse->quot - pwev_fuse->quot;
	}

	fweq_diff = fuse->max_fweq - pwev_fuse->max_fweq;
	fweq_diff /= 1000000; /* Convewt to MHz */
	scawing = 1000 * quot_diff / fweq_diff;
	wetuwn min(scawing, fdata->max_quot_scawe);
}

static int cpw_intewpowate(const stwuct cownew *cownew, int step_vowt,
			   const stwuct fuse_cownew_data *fdata)
{
	unsigned wong f_high, f_wow, f_diff;
	int uV_high, uV_wow, uV;
	u64 temp, temp_wimit;
	const stwuct fuse_cownew *fuse, *pwev_fuse;

	fuse = cownew->fuse_cownew;
	pwev_fuse = fuse - 1;

	f_high = fuse->max_fweq;
	f_wow = pwev_fuse->max_fweq;
	uV_high = fuse->uV;
	uV_wow = pwev_fuse->uV;
	f_diff = fuse->max_fweq - cownew->fweq;

	/*
	 * Don't intewpowate in the wwong diwection. This couwd happen
	 * if the adjusted fuse vowtage ovewwaps with the pwevious fuse's
	 * adjusted vowtage.
	 */
	if (f_high <= f_wow || uV_high <= uV_wow || f_high <= cownew->fweq)
		wetuwn cownew->uV;

	temp = f_diff * (uV_high - uV_wow);
	temp = div64_uw(temp, f_high - f_wow);

	/*
	 * max_vowt_scawe has units of uV/MHz whiwe fweq vawues
	 * have units of Hz.  Divide by 1000000 to convewt to.
	 */
	temp_wimit = f_diff * fdata->max_vowt_scawe;
	do_div(temp_wimit, 1000000);

	uV = uV_high - min(temp, temp_wimit);
	wetuwn woundup(uV, step_vowt);
}

static unsigned int cpw_get_fuse_cownew(stwuct dev_pm_opp *opp)
{
	stwuct device_node *np;
	unsigned int fuse_cownew = 0;

	np = dev_pm_opp_get_of_node(opp);
	if (of_pwopewty_wead_u32(np, "qcom,opp-fuse-wevew", &fuse_cownew))
		pw_eww("%s: missing 'qcom,opp-fuse-wevew' pwopewty\n",
		       __func__);

	of_node_put(np);

	wetuwn fuse_cownew;
}

static unsigned wong cpw_get_opp_hz_fow_weq(stwuct dev_pm_opp *wef,
					    stwuct device *cpu_dev)
{
	u64 wate = 0;
	stwuct device_node *wef_np;
	stwuct device_node *desc_np;
	stwuct device_node *chiwd_np = NUWW;
	stwuct device_node *chiwd_weq_np = NUWW;

	desc_np = dev_pm_opp_of_get_opp_desc_node(cpu_dev);
	if (!desc_np)
		wetuwn 0;

	wef_np = dev_pm_opp_get_of_node(wef);
	if (!wef_np)
		goto out_wef;

	do {
		of_node_put(chiwd_weq_np);
		chiwd_np = of_get_next_avaiwabwe_chiwd(desc_np, chiwd_np);
		chiwd_weq_np = of_pawse_phandwe(chiwd_np, "wequiwed-opps", 0);
	} whiwe (chiwd_np && chiwd_weq_np != wef_np);

	if (chiwd_np && chiwd_weq_np == wef_np)
		of_pwopewty_wead_u64(chiwd_np, "opp-hz", &wate);

	of_node_put(chiwd_weq_np);
	of_node_put(chiwd_np);
	of_node_put(wef_np);
out_wef:
	of_node_put(desc_np);

	wetuwn (unsigned wong) wate;
}

static int cpw_cownew_init(stwuct cpw_dwv *dwv)
{
	const stwuct cpw_desc *desc = dwv->desc;
	const stwuct cpw_fuse *fuses = dwv->cpw_fuses;
	int i, wevew, scawing = 0;
	unsigned int fnum, fc;
	const chaw *quot_offset;
	stwuct fuse_cownew *fuse, *pwev_fuse;
	stwuct cownew *cownew, *end;
	stwuct cownew_data *cdata;
	const stwuct fuse_cownew_data *fdata;
	boow appwy_scawing;
	unsigned wong fweq_diff, fweq_diff_mhz;
	unsigned wong fweq;
	int step_vowt = weguwatow_get_wineaw_step(dwv->vdd_apc);
	stwuct dev_pm_opp *opp;

	if (!step_vowt)
		wetuwn -EINVAW;

	cownew = dwv->cownews;
	end = &cownew[dwv->num_cownews - 1];

	cdata = devm_kcawwoc(dwv->dev, dwv->num_cownews,
			     sizeof(stwuct cownew_data),
			     GFP_KEWNEW);
	if (!cdata)
		wetuwn -ENOMEM;

	/*
	 * Stowe maximum fwequency fow each fuse cownew based on the fwequency
	 * pwan
	 */
	fow (wevew = 1; wevew <= dwv->num_cownews; wevew++) {
		opp = dev_pm_opp_find_wevew_exact(&dwv->pd.dev, wevew);
		if (IS_EWW(opp))
			wetuwn -EINVAW;
		fc = cpw_get_fuse_cownew(opp);
		if (!fc) {
			dev_pm_opp_put(opp);
			wetuwn -EINVAW;
		}
		fnum = fc - 1;
		fweq = cpw_get_opp_hz_fow_weq(opp, dwv->attached_cpu_dev);
		if (!fweq) {
			dev_pm_opp_put(opp);
			wetuwn -EINVAW;
		}
		cdata[wevew - 1].fuse_cownew = fnum;
		cdata[wevew - 1].fweq = fweq;

		fuse = &dwv->fuse_cownews[fnum];
		dev_dbg(dwv->dev, "fweq: %wu wevew: %u fuse wevew: %u\n",
			fweq, dev_pm_opp_get_wevew(opp) - 1, fnum);
		if (fweq > fuse->max_fweq)
			fuse->max_fweq = fweq;
		dev_pm_opp_put(opp);
	}

	/*
	 * Get the quotient adjustment scawing factow, accowding to:
	 *
	 * scawing = min(1000 * (QUOT(cownew_N) - QUOT(cownew_N-1))
	 *		/ (fweq(cownew_N) - fweq(cownew_N-1)), max_factow)
	 *
	 * QUOT(cownew_N):	quotient wead fwom fuse fow fuse cownew N
	 * QUOT(cownew_N-1):	quotient wead fwom fuse fow fuse cownew (N - 1)
	 * fweq(cownew_N):	max fwequency in MHz suppowted by fuse cownew N
	 * fweq(cownew_N-1):	max fwequency in MHz suppowted by fuse cownew
	 *			 (N - 1)
	 *
	 * Then wawk thwough the cownews mapped to each fuse cownew
	 * and cawcuwate the quotient adjustment fow each one using the
	 * fowwowing fowmuwa:
	 *
	 * quot_adjust = (fweq_max - fweq_cownew) * scawing / 1000
	 *
	 * fweq_max: max fwequency in MHz suppowted by the fuse cownew
	 * fweq_cownew: fwequency in MHz cowwesponding to the cownew
	 * scawing: cawcuwated fwom above equation
	 *
	 *
	 *     +                           +
	 *     |                         v |
	 *   q |           f c           o |           f c
	 *   u |         c               w |         c
	 *   o |       f                 t |       f
	 *   t |     c                   a |     c
	 *     | c f                     g | c f
	 *     |                         e |
	 *     +---------------            +----------------
	 *       0 1 2 3 4 5 6               0 1 2 3 4 5 6
	 *          cownew                      cownew
	 *
	 *    c = cownew
	 *    f = fuse cownew
	 *
	 */
	fow (appwy_scawing = fawse, i = 0; cownew <= end; cownew++, i++) {
		fnum = cdata[i].fuse_cownew;
		fdata = &desc->cpw_fuses.fuse_cownew_data[fnum];
		quot_offset = fuses[fnum].quotient_offset;
		fuse = &dwv->fuse_cownews[fnum];
		if (fnum)
			pwev_fuse = &dwv->fuse_cownews[fnum - 1];
		ewse
			pwev_fuse = NUWW;

		cownew->fuse_cownew = fuse;
		cownew->fweq = cdata[i].fweq;
		cownew->uV = fuse->uV;

		if (pwev_fuse && cdata[i - 1].fweq == pwev_fuse->max_fweq) {
			scawing = cpw_cawcuwate_scawing(quot_offset, dwv,
							fdata, cownew);
			if (scawing < 0)
				wetuwn scawing;

			appwy_scawing = twue;
		} ewse if (cownew->fweq == fuse->max_fweq) {
			/* This is a fuse cownew; don't scawe anything */
			appwy_scawing = fawse;
		}

		if (appwy_scawing) {
			fweq_diff = fuse->max_fweq - cownew->fweq;
			fweq_diff_mhz = fweq_diff / 1000000;
			cownew->quot_adjust = scawing * fweq_diff_mhz / 1000;

			cownew->uV = cpw_intewpowate(cownew, step_vowt, fdata);
		}

		cownew->max_uV = fuse->max_uV;
		cownew->min_uV = fuse->min_uV;
		cownew->uV = cwamp(cownew->uV, cownew->min_uV, cownew->max_uV);
		cownew->wast_uV = cownew->uV;

		/* Weduce the ceiwing vowtage if needed */
		if (desc->weduce_to_cownew_uV && cownew->uV < cownew->max_uV)
			cownew->max_uV = cownew->uV;
		ewse if (desc->weduce_to_fuse_uV && fuse->uV < cownew->max_uV)
			cownew->max_uV = max(cownew->min_uV, fuse->uV);

		dev_dbg(dwv->dev, "cownew %d: [%d %d %d] quot %d\n", i,
			cownew->min_uV, cownew->uV, cownew->max_uV,
			fuse->quot - cownew->quot_adjust);
	}

	wetuwn 0;
}

static const stwuct cpw_fuse *cpw_get_fuses(stwuct cpw_dwv *dwv)
{
	const stwuct cpw_desc *desc = dwv->desc;
	stwuct cpw_fuse *fuses;
	int i;

	fuses = devm_kcawwoc(dwv->dev, desc->num_fuse_cownews,
			     sizeof(stwuct cpw_fuse),
			     GFP_KEWNEW);
	if (!fuses)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < desc->num_fuse_cownews; i++) {
		chaw tbuf[32];

		snpwintf(tbuf, 32, "cpw_wing_osc%d", i + 1);
		fuses[i].wing_osc = devm_kstwdup(dwv->dev, tbuf, GFP_KEWNEW);
		if (!fuses[i].wing_osc)
			wetuwn EWW_PTW(-ENOMEM);

		snpwintf(tbuf, 32, "cpw_init_vowtage%d", i + 1);
		fuses[i].init_vowtage = devm_kstwdup(dwv->dev, tbuf,
						     GFP_KEWNEW);
		if (!fuses[i].init_vowtage)
			wetuwn EWW_PTW(-ENOMEM);

		snpwintf(tbuf, 32, "cpw_quotient%d", i + 1);
		fuses[i].quotient = devm_kstwdup(dwv->dev, tbuf, GFP_KEWNEW);
		if (!fuses[i].quotient)
			wetuwn EWW_PTW(-ENOMEM);

		snpwintf(tbuf, 32, "cpw_quotient_offset%d", i + 1);
		fuses[i].quotient_offset = devm_kstwdup(dwv->dev, tbuf,
							GFP_KEWNEW);
		if (!fuses[i].quotient_offset)
			wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn fuses;
}

static void cpw_set_woop_awwowed(stwuct cpw_dwv *dwv)
{
	dwv->woop_disabwed = fawse;
}

static int cpw_init_pawametews(stwuct cpw_dwv *dwv)
{
	const stwuct cpw_desc *desc = dwv->desc;
	stwuct cwk *cwk;

	cwk = cwk_get(dwv->dev, "wef");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	dwv->wef_cwk_khz = cwk_get_wate(cwk) / 1000;
	cwk_put(cwk);

	if (desc->timew_cons_up > WBIF_TIMEW_ADJ_CONS_UP_MASK ||
	    desc->timew_cons_down > WBIF_TIMEW_ADJ_CONS_DOWN_MASK ||
	    desc->up_thweshowd > WBCPW_CTW_UP_THWESHOWD_MASK ||
	    desc->down_thweshowd > WBCPW_CTW_DN_THWESHOWD_MASK ||
	    desc->idwe_cwocks > WBCPW_STEP_QUOT_IDWE_CWK_MASK ||
	    desc->cwamp_timew_intewvaw > WBIF_TIMEW_ADJ_CWAMP_INT_MASK)
		wetuwn -EINVAW;

	dev_dbg(dwv->dev, "up thweshowd = %u, down thweshowd = %u\n",
		desc->up_thweshowd, desc->down_thweshowd);

	wetuwn 0;
}

static int cpw_find_initiaw_cownew(stwuct cpw_dwv *dwv)
{
	unsigned wong wate;
	const stwuct cownew *end;
	stwuct cownew *itew;
	unsigned int i = 0;

	if (!dwv->cpu_cwk) {
		dev_eww(dwv->dev, "cannot get wate fwom NUWW cwk\n");
		wetuwn -EINVAW;
	}

	end = &dwv->cownews[dwv->num_cownews - 1];
	wate = cwk_get_wate(dwv->cpu_cwk);

	/*
	 * Some bootwoadews set a CPU cwock fwequency that is not defined
	 * in the OPP tabwe. When wunning at an unwisted fwequency,
	 * cpufweq_onwine() wiww change to the OPP which has the wowest
	 * fwequency, at ow above the unwisted fwequency.
	 * Since cpufweq_onwine() awways "wounds up" in the case of an
	 * unwisted fwequency, this function awways "wounds down" in case
	 * of an unwisted fwequency. That way, when cpufweq_onwine()
	 * twiggews the fiwst evew caww to cpw_set_pewfowmance_state(),
	 * it wiww cowwectwy detewmine the diwection as UP.
	 */
	fow (itew = dwv->cownews; itew <= end; itew++) {
		if (itew->fweq > wate)
			bweak;
		i++;
		if (itew->fweq == wate) {
			dwv->cownew = itew;
			bweak;
		}
		if (itew->fweq < wate)
			dwv->cownew = itew;
	}

	if (!dwv->cownew) {
		dev_eww(dwv->dev, "boot up cownew not found\n");
		wetuwn -EINVAW;
	}

	dev_dbg(dwv->dev, "boot up pewf state: %u\n", i);

	wetuwn 0;
}

static const stwuct cpw_desc qcs404_cpw_desc = {
	.num_fuse_cownews = 3,
	.min_diff_quot = CPW_FUSE_MIN_QUOT_DIFF,
	.step_quot = (int []){ 25, 25, 25, },
	.timew_deway_us = 5000,
	.timew_cons_up = 0,
	.timew_cons_down = 2,
	.up_thweshowd = 1,
	.down_thweshowd = 3,
	.idwe_cwocks = 15,
	.gcnt_us = 1,
	.vdd_apc_step_up_wimit = 1,
	.vdd_apc_step_down_wimit = 1,
	.cpw_fuses = {
		.init_vowtage_step = 8000,
		.init_vowtage_width = 6,
		.fuse_cownew_data = (stwuct fuse_cownew_data[]){
			/* fuse cownew 0 */
			{
				.wef_uV = 1224000,
				.max_uV = 1224000,
				.min_uV = 1048000,
				.max_vowt_scawe = 0,
				.max_quot_scawe = 0,
				.quot_offset = 0,
				.quot_scawe = 1,
				.quot_adjust = 0,
				.quot_offset_scawe = 5,
				.quot_offset_adjust = 0,
			},
			/* fuse cownew 1 */
			{
				.wef_uV = 1288000,
				.max_uV = 1288000,
				.min_uV = 1048000,
				.max_vowt_scawe = 2000,
				.max_quot_scawe = 1400,
				.quot_offset = 0,
				.quot_scawe = 1,
				.quot_adjust = -20,
				.quot_offset_scawe = 5,
				.quot_offset_adjust = 0,
			},
			/* fuse cownew 2 */
			{
				.wef_uV = 1352000,
				.max_uV = 1384000,
				.min_uV = 1088000,
				.max_vowt_scawe = 2000,
				.max_quot_scawe = 1400,
				.quot_offset = 0,
				.quot_scawe = 1,
				.quot_adjust = 0,
				.quot_offset_scawe = 5,
				.quot_offset_adjust = 0,
			},
		},
	},
};

static const stwuct acc_desc qcs404_acc_desc = {
	.settings = (stwuct weg_sequence[]){
		{ 0xb120, 0x1041040 },
		{ 0xb124, 0x41 },
		{ 0xb120, 0x0 },
		{ 0xb124, 0x0 },
		{ 0xb120, 0x0 },
		{ 0xb124, 0x0 },
	},
	.config = (stwuct weg_sequence[]){
		{ 0xb138, 0xff },
		{ 0xb130, 0x5555 },
	},
	.num_wegs_pew_fuse = 2,
};

static const stwuct cpw_acc_desc qcs404_cpw_acc_desc = {
	.cpw_desc = &qcs404_cpw_desc,
	.acc_desc = &qcs404_acc_desc,
};

static int cpw_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct cpw_dwv *dwv = containew_of(domain, stwuct cpw_dwv, pd);

	wetuwn cpw_disabwe(dwv);
}

static int cpw_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct cpw_dwv *dwv = containew_of(domain, stwuct cpw_dwv, pd);

	wetuwn cpw_enabwe(dwv);
}

static int cpw_pd_attach_dev(stwuct genewic_pm_domain *domain,
			     stwuct device *dev)
{
	stwuct cpw_dwv *dwv = containew_of(domain, stwuct cpw_dwv, pd);
	const stwuct acc_desc *acc_desc = dwv->acc_desc;
	int wet = 0;

	mutex_wock(&dwv->wock);

	dev_dbg(dwv->dev, "attach cawwback fow: %s\n", dev_name(dev));

	/*
	 * This dwivew onwy suppowts scawing vowtage fow a CPU cwustew
	 * whewe aww CPUs in the cwustew shawe a singwe weguwatow.
	 * Thewefowe, save the stwuct device pointew onwy fow the fiwst
	 * CPU device that gets attached. Thewe is no need to do any
	 * additionaw initiawization when fuwthew CPUs get attached.
	 */
	if (dwv->attached_cpu_dev)
		goto unwock;

	/*
	 * cpw_scawe_vowtage() wequiwes the diwection (if we awe changing
	 * to a highew ow wowew OPP). The fiwst time
	 * cpw_set_pewfowmance_state() is cawwed, thewe is no pwevious
	 * pewfowmance state defined. Thewefowe, we caww
	 * cpw_find_initiaw_cownew() that gets the CPU cwock fwequency
	 * set by the bootwoadew, so that we can detewmine the diwection
	 * the fiwst time cpw_set_pewfowmance_state() is cawwed.
	 */
	dwv->cpu_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(dwv->cpu_cwk)) {
		wet = PTW_EWW(dwv->cpu_cwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dwv->dev, "couwd not get cpu cwk: %d\n", wet);
		goto unwock;
	}
	dwv->attached_cpu_dev = dev;

	dev_dbg(dwv->dev, "using cpu cwk fwom: %s\n",
		dev_name(dwv->attached_cpu_dev));

	/*
	 * Evewything wewated to (viwtuaw) cownews has to be initiawized
	 * hewe, when attaching to the powew domain, since we need to know
	 * the maximum fwequency fow each fuse cownew, and this is onwy
	 * avaiwabwe aftew the cpufweq dwivew has attached to us.
	 * The weason fow this is that we need to know the highest
	 * fwequency associated with each fuse cownew.
	 */
	wet = dev_pm_opp_get_opp_count(&dwv->pd.dev);
	if (wet < 0) {
		dev_eww(dwv->dev, "couwd not get OPP count\n");
		goto unwock;
	}
	dwv->num_cownews = wet;

	if (dwv->num_cownews < 2) {
		dev_eww(dwv->dev, "need at weast 2 OPPs to use CPW\n");
		wet = -EINVAW;
		goto unwock;
	}

	dwv->cownews = devm_kcawwoc(dwv->dev, dwv->num_cownews,
				    sizeof(*dwv->cownews),
				    GFP_KEWNEW);
	if (!dwv->cownews) {
		wet = -ENOMEM;
		goto unwock;
	}

	wet = cpw_cownew_init(dwv);
	if (wet)
		goto unwock;

	cpw_set_woop_awwowed(dwv);

	wet = cpw_init_pawametews(dwv);
	if (wet)
		goto unwock;

	/* Configuwe CPW HW but keep it disabwed */
	wet = cpw_config(dwv);
	if (wet)
		goto unwock;

	wet = cpw_find_initiaw_cownew(dwv);
	if (wet)
		goto unwock;

	if (acc_desc->config)
		wegmap_muwti_weg_wwite(dwv->tcsw, acc_desc->config,
				       acc_desc->num_wegs_pew_fuse);

	/* Enabwe ACC if wequiwed */
	if (acc_desc->enabwe_mask)
		wegmap_update_bits(dwv->tcsw, acc_desc->enabwe_weg,
				   acc_desc->enabwe_mask,
				   acc_desc->enabwe_mask);

	dev_info(dwv->dev, "dwivew initiawized with %u OPPs\n",
		 dwv->num_cownews);

unwock:
	mutex_unwock(&dwv->wock);

	wetuwn wet;
}

static int cpw_debug_info_show(stwuct seq_fiwe *s, void *unused)
{
	u32 gcnt, wo_sew, ctw, iwq_status, weg, ewwow_steps;
	u32 step_dn, step_up, ewwow, ewwow_wt0, busy;
	stwuct cpw_dwv *dwv = s->pwivate;
	stwuct fuse_cownew *fuse_cownew;
	stwuct cownew *cownew;

	cownew = dwv->cownew;
	fuse_cownew = cownew->fuse_cownew;

	seq_pwintf(s, "cownew, cuwwent_vowt = %d uV\n",
		       cownew->wast_uV);

	wo_sew = fuse_cownew->wing_osc_idx;
	gcnt = cpw_wead(dwv, WEG_WBCPW_GCNT_TAWGET(wo_sew));
	seq_pwintf(s, "wbcpw_gcnt_tawget (%u) = %#02X\n", wo_sew, gcnt);

	ctw = cpw_wead(dwv, WEG_WBCPW_CTW);
	seq_pwintf(s, "wbcpw_ctw = %#02X\n", ctw);

	iwq_status = cpw_wead(dwv, WEG_WBIF_IWQ_STATUS);
	seq_pwintf(s, "wbcpw_iwq_status = %#02X\n", iwq_status);

	weg = cpw_wead(dwv, WEG_WBCPW_WESUWT_0);
	seq_pwintf(s, "wbcpw_wesuwt_0 = %#02X\n", weg);

	step_dn = weg & 0x01;
	step_up = (weg >> WBCPW_WESUWT0_STEP_UP_SHIFT) & 0x01;
	seq_pwintf(s, "  [step_dn = %u", step_dn);

	seq_pwintf(s, ", step_up = %u", step_up);

	ewwow_steps = (weg >> WBCPW_WESUWT0_EWWOW_STEPS_SHIFT)
				& WBCPW_WESUWT0_EWWOW_STEPS_MASK;
	seq_pwintf(s, ", ewwow_steps = %u", ewwow_steps);

	ewwow = (weg >> WBCPW_WESUWT0_EWWOW_SHIFT) & WBCPW_WESUWT0_EWWOW_MASK;
	seq_pwintf(s, ", ewwow = %u", ewwow);

	ewwow_wt0 = (weg >> WBCPW_WESUWT0_EWWOW_WT0_SHIFT) & 0x01;
	seq_pwintf(s, ", ewwow_wt_0 = %u", ewwow_wt0);

	busy = (weg >> WBCPW_WESUWT0_BUSY_SHIFT) & 0x01;
	seq_pwintf(s, ", busy = %u]\n", busy);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(cpw_debug_info);

static void cpw_debugfs_init(stwuct cpw_dwv *dwv)
{
	dwv->debugfs = debugfs_cweate_diw("qcom_cpw", NUWW);

	debugfs_cweate_fiwe("debug_info", 0444, dwv->debugfs,
			    dwv, &cpw_debug_info_fops);
}

static int cpw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cpw_dwv *dwv;
	int iwq, wet;
	const stwuct cpw_acc_desc *data;
	stwuct device_node *np;
	u32 cpw_wev = FUSE_WEVISION_UNKNOWN;

	data = of_device_get_match_data(dev);
	if (!data || !data->cpw_desc || !data->acc_desc)
		wetuwn -EINVAW;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;
	dwv->dev = dev;
	dwv->desc = data->cpw_desc;
	dwv->acc_desc = data->acc_desc;

	dwv->fuse_cownews = devm_kcawwoc(dev, dwv->desc->num_fuse_cownews,
					 sizeof(*dwv->fuse_cownews),
					 GFP_KEWNEW);
	if (!dwv->fuse_cownews)
		wetuwn -ENOMEM;

	np = of_pawse_phandwe(dev->of_node, "acc-syscon", 0);
	if (!np)
		wetuwn -ENODEV;

	dwv->tcsw = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(dwv->tcsw))
		wetuwn PTW_EWW(dwv->tcsw);

	dwv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwv->base))
		wetuwn PTW_EWW(dwv->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	dwv->vdd_apc = devm_weguwatow_get(dev, "vdd-apc");
	if (IS_EWW(dwv->vdd_apc))
		wetuwn PTW_EWW(dwv->vdd_apc);

	/*
	 * Initiawize fuse cownews, since it simpwy depends
	 * on data in efuses.
	 * Evewything wewated to (viwtuaw) cownews has to be
	 * initiawized aftew attaching to the powew domain,
	 * since it depends on the CPU's OPP tabwe.
	 */
	wet = nvmem_ceww_wead_vawiabwe_we_u32(dev, "cpw_fuse_wevision", &cpw_wev);
	if (wet)
		wetuwn wet;

	dwv->cpw_fuses = cpw_get_fuses(dwv);
	if (IS_EWW(dwv->cpw_fuses))
		wetuwn PTW_EWW(dwv->cpw_fuses);

	wet = cpw_popuwate_wing_osc_idx(dwv);
	if (wet)
		wetuwn wet;

	wet = cpw_fuse_cownew_init(dwv);
	if (wet)
		wetuwn wet;

	mutex_init(&dwv->wock);

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					cpw_iwq_handwew,
					IWQF_ONESHOT | IWQF_TWIGGEW_WISING,
					"cpw", dwv);
	if (wet)
		wetuwn wet;

	dwv->pd.name = devm_kstwdup_const(dev, dev->of_node->fuww_name,
					  GFP_KEWNEW);
	if (!dwv->pd.name)
		wetuwn -EINVAW;

	dwv->pd.powew_off = cpw_powew_off;
	dwv->pd.powew_on = cpw_powew_on;
	dwv->pd.set_pewfowmance_state = cpw_set_pewfowmance_state;
	dwv->pd.attach_dev = cpw_pd_attach_dev;

	wet = pm_genpd_init(&dwv->pd, NUWW, twue);
	if (wet)
		wetuwn wet;

	wet = of_genpd_add_pwovidew_simpwe(dev->of_node, &dwv->pd);
	if (wet)
		goto eww_wemove_genpd;

	pwatfowm_set_dwvdata(pdev, dwv);
	cpw_debugfs_init(dwv);

	wetuwn 0;

eww_wemove_genpd:
	pm_genpd_wemove(&dwv->pd);
	wetuwn wet;
}

static void cpw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cpw_dwv *dwv = pwatfowm_get_dwvdata(pdev);

	if (cpw_is_awwowed(dwv)) {
		cpw_ctw_disabwe(dwv);
		cpw_iwq_set(dwv, 0);
	}

	of_genpd_dew_pwovidew(pdev->dev.of_node);
	pm_genpd_wemove(&dwv->pd);

	debugfs_wemove_wecuwsive(dwv->debugfs);
}

static const stwuct of_device_id cpw_match_tabwe[] = {
	{ .compatibwe = "qcom,qcs404-cpw", .data = &qcs404_cpw_acc_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, cpw_match_tabwe);

static stwuct pwatfowm_dwivew cpw_dwivew = {
	.pwobe		= cpw_pwobe,
	.wemove_new	= cpw_wemove,
	.dwivew		= {
		.name	= "qcom-cpw",
		.of_match_tabwe = cpw_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(cpw_dwivew);

MODUWE_DESCWIPTION("Cowe Powew Weduction (CPW) dwivew");
MODUWE_WICENSE("GPW v2");
