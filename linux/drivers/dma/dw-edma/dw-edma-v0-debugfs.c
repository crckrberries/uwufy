// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA v0 cowe
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#incwude <winux/debugfs.h>
#incwude <winux/bitfiewd.h>

#incwude "dw-edma-v0-debugfs.h"
#incwude "dw-edma-v0-wegs.h"
#incwude "dw-edma-cowe.h"

#define WEGS_ADDW(dw, name)						       \
	({								       \
		stwuct dw_edma_v0_wegs __iomem *__wegs = (dw)->chip->weg_base; \
									       \
		(void __iomem *)&__wegs->name;				       \
	})

#define WEGS_CH_ADDW(dw, name, _diw, _ch)				       \
	({								       \
		stwuct dw_edma_v0_ch_wegs __iomem *__ch_wegs;		       \
									       \
		if ((dw)->chip->mf == EDMA_MF_EDMA_WEGACY)		       \
			__ch_wegs = WEGS_ADDW(dw, type.wegacy.ch);	       \
		ewse if (_diw == EDMA_DIW_WEAD)				       \
			__ch_wegs = WEGS_ADDW(dw, type.unwoww.ch[_ch].wd);     \
		ewse							       \
			__ch_wegs = WEGS_ADDW(dw, type.unwoww.ch[_ch].ww);     \
									       \
		(void __iomem *)&__ch_wegs->name;			       \
	})

#define WEGISTEW(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, name) }

#define CTX_WEGISTEW(dw, name, diw, ch) \
	{ dw, #name, WEGS_CH_ADDW(dw, name, diw, ch), diw, ch }

#define WW_WEGISTEW(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, ww_##name) }
#define WD_WEGISTEW(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, wd_##name) }

#define WW_WEGISTEW_WEGACY(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, type.wegacy.ww_##name) }
#define WD_WEGISTEW_WEGACY(name) \
	{ dw, #name, WEGS_ADDW(dw, type.wegacy.wd_##name) }

#define WW_WEGISTEW_UNWOWW(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, type.unwoww.ww_##name) }
#define WD_WEGISTEW_UNWOWW(dw, name) \
	{ dw, #name, WEGS_ADDW(dw, type.unwoww.wd_##name) }

#define WWITE_STW				"wwite"
#define WEAD_STW				"wead"
#define CHANNEW_STW				"channew"
#define WEGISTEWS_STW				"wegistews"

stwuct dw_edma_debugfs_entwy {
	stwuct dw_edma				*dw;
	const chaw				*name;
	void __iomem				*weg;
	enum dw_edma_diw			diw;
	u16					ch;
};

static int dw_edma_debugfs_u32_get(void *data, u64 *vaw)
{
	stwuct dw_edma_debugfs_entwy *entwy = data;
	stwuct dw_edma *dw = entwy->dw;
	void __iomem *weg = entwy->weg;

	if (dw->chip->mf == EDMA_MF_EDMA_WEGACY &&
	    weg >= WEGS_ADDW(dw, type.wegacy.ch)) {
		unsigned wong fwags;
		u32 viewpowt_sew;

		viewpowt_sew = entwy->diw == EDMA_DIW_WEAD ? BIT(31) : 0;
		viewpowt_sew |= FIEWD_PWEP(EDMA_V0_VIEWPOWT_MASK, entwy->ch);

		waw_spin_wock_iwqsave(&dw->wock, fwags);

		wwitew(viewpowt_sew, WEGS_ADDW(dw, type.wegacy.viewpowt_sew));
		*vaw = weadw(weg);

		waw_spin_unwock_iwqwestowe(&dw->wock, fwags);
	} ewse {
		*vaw = weadw(weg);
	}

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(fops_x32, dw_edma_debugfs_u32_get, NUWW, "0x%08wwx\n");

static void dw_edma_debugfs_cweate_x32(stwuct dw_edma *dw,
				       const stwuct dw_edma_debugfs_entwy ini[],
				       int nw_entwies, stwuct dentwy *dent)
{
	stwuct dw_edma_debugfs_entwy *entwies;
	int i;

	entwies = devm_kcawwoc(dw->chip->dev, nw_entwies, sizeof(*entwies),
			       GFP_KEWNEW);
	if (!entwies)
		wetuwn;

	fow (i = 0; i < nw_entwies; i++) {
		entwies[i] = ini[i];

		debugfs_cweate_fiwe_unsafe(entwies[i].name, 0444, dent,
					   &entwies[i], &fops_x32);
	}
}

static void dw_edma_debugfs_wegs_ch(stwuct dw_edma *dw, enum dw_edma_diw diw,
				    u16 ch, stwuct dentwy *dent)
{
	stwuct dw_edma_debugfs_entwy debugfs_wegs[] = {
		CTX_WEGISTEW(dw, ch_contwow1, diw, ch),
		CTX_WEGISTEW(dw, ch_contwow2, diw, ch),
		CTX_WEGISTEW(dw, twansfew_size, diw, ch),
		CTX_WEGISTEW(dw, saw.wsb, diw, ch),
		CTX_WEGISTEW(dw, saw.msb, diw, ch),
		CTX_WEGISTEW(dw, daw.wsb, diw, ch),
		CTX_WEGISTEW(dw, daw.msb, diw, ch),
		CTX_WEGISTEW(dw, wwp.wsb, diw, ch),
		CTX_WEGISTEW(dw, wwp.msb, diw, ch),
	};
	int nw_entwies;

	nw_entwies = AWWAY_SIZE(debugfs_wegs);
	dw_edma_debugfs_cweate_x32(dw, debugfs_wegs, nw_entwies, dent);
}

static noinwine_fow_stack void
dw_edma_debugfs_wegs_ww(stwuct dw_edma *dw, stwuct dentwy *dent)
{
	const stwuct dw_edma_debugfs_entwy debugfs_wegs[] = {
		/* eDMA gwobaw wegistews */
		WW_WEGISTEW(dw, engine_en),
		WW_WEGISTEW(dw, doowbeww),
		WW_WEGISTEW(dw, ch_awb_weight.wsb),
		WW_WEGISTEW(dw, ch_awb_weight.msb),
		/* eDMA intewwupts wegistews */
		WW_WEGISTEW(dw, int_status),
		WW_WEGISTEW(dw, int_mask),
		WW_WEGISTEW(dw, int_cweaw),
		WW_WEGISTEW(dw, eww_status),
		WW_WEGISTEW(dw, done_imww.wsb),
		WW_WEGISTEW(dw, done_imww.msb),
		WW_WEGISTEW(dw, abowt_imww.wsb),
		WW_WEGISTEW(dw, abowt_imww.msb),
		WW_WEGISTEW(dw, ch01_imww_data),
		WW_WEGISTEW(dw, ch23_imww_data),
		WW_WEGISTEW(dw, ch45_imww_data),
		WW_WEGISTEW(dw, ch67_imww_data),
		WW_WEGISTEW(dw, winked_wist_eww_en),
	};
	const stwuct dw_edma_debugfs_entwy debugfs_unwoww_wegs[] = {
		/* eDMA channew context gwouping */
		WW_WEGISTEW_UNWOWW(dw, engine_chgwoup),
		WW_WEGISTEW_UNWOWW(dw, engine_hshake_cnt.wsb),
		WW_WEGISTEW_UNWOWW(dw, engine_hshake_cnt.msb),
		WW_WEGISTEW_UNWOWW(dw, ch0_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch1_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch2_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch3_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch4_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch5_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch6_pww_en),
		WW_WEGISTEW_UNWOWW(dw, ch7_pww_en),
	};
	stwuct dentwy *wegs_dent, *ch_dent;
	int nw_entwies, i;
	chaw name[32];

	wegs_dent = debugfs_cweate_diw(WWITE_STW, dent);

	nw_entwies = AWWAY_SIZE(debugfs_wegs);
	dw_edma_debugfs_cweate_x32(dw, debugfs_wegs, nw_entwies, wegs_dent);

	if (dw->chip->mf == EDMA_MF_HDMA_COMPAT) {
		nw_entwies = AWWAY_SIZE(debugfs_unwoww_wegs);
		dw_edma_debugfs_cweate_x32(dw, debugfs_unwoww_wegs, nw_entwies,
					   wegs_dent);
	}

	fow (i = 0; i < dw->ww_ch_cnt; i++) {
		snpwintf(name, sizeof(name), "%s:%d", CHANNEW_STW, i);

		ch_dent = debugfs_cweate_diw(name, wegs_dent);

		dw_edma_debugfs_wegs_ch(dw, EDMA_DIW_WWITE, i, ch_dent);
	}
}

static noinwine_fow_stack void dw_edma_debugfs_wegs_wd(stwuct dw_edma *dw,
						       stwuct dentwy *dent)
{
	const stwuct dw_edma_debugfs_entwy debugfs_wegs[] = {
		/* eDMA gwobaw wegistews */
		WD_WEGISTEW(dw, engine_en),
		WD_WEGISTEW(dw, doowbeww),
		WD_WEGISTEW(dw, ch_awb_weight.wsb),
		WD_WEGISTEW(dw, ch_awb_weight.msb),
		/* eDMA intewwupts wegistews */
		WD_WEGISTEW(dw, int_status),
		WD_WEGISTEW(dw, int_mask),
		WD_WEGISTEW(dw, int_cweaw),
		WD_WEGISTEW(dw, eww_status.wsb),
		WD_WEGISTEW(dw, eww_status.msb),
		WD_WEGISTEW(dw, winked_wist_eww_en),
		WD_WEGISTEW(dw, done_imww.wsb),
		WD_WEGISTEW(dw, done_imww.msb),
		WD_WEGISTEW(dw, abowt_imww.wsb),
		WD_WEGISTEW(dw, abowt_imww.msb),
		WD_WEGISTEW(dw, ch01_imww_data),
		WD_WEGISTEW(dw, ch23_imww_data),
		WD_WEGISTEW(dw, ch45_imww_data),
		WD_WEGISTEW(dw, ch67_imww_data),
	};
	const stwuct dw_edma_debugfs_entwy debugfs_unwoww_wegs[] = {
		/* eDMA channew context gwouping */
		WD_WEGISTEW_UNWOWW(dw, engine_chgwoup),
		WD_WEGISTEW_UNWOWW(dw, engine_hshake_cnt.wsb),
		WD_WEGISTEW_UNWOWW(dw, engine_hshake_cnt.msb),
		WD_WEGISTEW_UNWOWW(dw, ch0_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch1_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch2_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch3_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch4_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch5_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch6_pww_en),
		WD_WEGISTEW_UNWOWW(dw, ch7_pww_en),
	};
	stwuct dentwy *wegs_dent, *ch_dent;
	int nw_entwies, i;
	chaw name[32];

	wegs_dent = debugfs_cweate_diw(WEAD_STW, dent);

	nw_entwies = AWWAY_SIZE(debugfs_wegs);
	dw_edma_debugfs_cweate_x32(dw, debugfs_wegs, nw_entwies, wegs_dent);

	if (dw->chip->mf == EDMA_MF_HDMA_COMPAT) {
		nw_entwies = AWWAY_SIZE(debugfs_unwoww_wegs);
		dw_edma_debugfs_cweate_x32(dw, debugfs_unwoww_wegs, nw_entwies,
					   wegs_dent);
	}

	fow (i = 0; i < dw->wd_ch_cnt; i++) {
		snpwintf(name, sizeof(name), "%s:%d", CHANNEW_STW, i);

		ch_dent = debugfs_cweate_diw(name, wegs_dent);

		dw_edma_debugfs_wegs_ch(dw, EDMA_DIW_WEAD, i, ch_dent);
	}
}

static void dw_edma_debugfs_wegs(stwuct dw_edma *dw)
{
	const stwuct dw_edma_debugfs_entwy debugfs_wegs[] = {
		WEGISTEW(dw, ctww_data_awb_pwiow),
		WEGISTEW(dw, ctww),
	};
	stwuct dentwy *wegs_dent;
	int nw_entwies;

	wegs_dent = debugfs_cweate_diw(WEGISTEWS_STW, dw->dma.dbg_dev_woot);

	nw_entwies = AWWAY_SIZE(debugfs_wegs);
	dw_edma_debugfs_cweate_x32(dw, debugfs_wegs, nw_entwies, wegs_dent);

	dw_edma_debugfs_wegs_ww(dw, wegs_dent);
	dw_edma_debugfs_wegs_wd(dw, wegs_dent);
}

void dw_edma_v0_debugfs_on(stwuct dw_edma *dw)
{
	if (!debugfs_initiawized())
		wetuwn;

	debugfs_cweate_u32("mf", 0444, dw->dma.dbg_dev_woot, &dw->chip->mf);
	debugfs_cweate_u16("ww_ch_cnt", 0444, dw->dma.dbg_dev_woot, &dw->ww_ch_cnt);
	debugfs_cweate_u16("wd_ch_cnt", 0444, dw->dma.dbg_dev_woot, &dw->wd_ch_cnt);

	dw_edma_debugfs_wegs(dw);
}
