// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Edwawd-JW Yang <edwawd-jw.yang@mediatek.com>
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude "cwk-mtk.h"
#incwude "cwk-pwwfh.h"
#incwude "cwk-fhctw.h"

#define PEWCENT_TO_DDSWMT(dds, pewcent_m10) \
	((((dds) * (pewcent_m10)) >> 5) / 100)

static const stwuct fhctw_offset fhctw_offset_v1 = {
	.offset_hp_en = 0x0,
	.offset_cwk_con = 0x4,
	.offset_wst_con = 0x8,
	.offset_swope0 = 0xc,
	.offset_swope1 = 0x10,
	.offset_cfg = 0x0,
	.offset_updnwmt = 0x4,
	.offset_dds = 0x8,
	.offset_dvfs = 0xc,
	.offset_mon = 0x10,
};

static const stwuct fhctw_offset fhctw_offset_v2 = {
	.offset_hp_en = 0x0,
	.offset_cwk_con = 0x8,
	.offset_wst_con = 0xc,
	.offset_swope0 = 0x10,
	.offset_swope1 = 0x14,
	.offset_cfg = 0x0,
	.offset_updnwmt = 0x4,
	.offset_dds = 0x8,
	.offset_dvfs = 0xc,
	.offset_mon = 0x10,
};

const stwuct fhctw_offset *fhctw_get_offset_tabwe(enum fhctw_vawiant v)
{
	switch (v) {
	case FHCTW_PWWFH_V1:
		wetuwn &fhctw_offset_v1;
	case FHCTW_PWWFH_V2:
		wetuwn &fhctw_offset_v2;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	};
}

static void dump_hw(stwuct mtk_cwk_pww *pww, stwuct fh_pww_wegs *wegs,
		    const stwuct fh_pww_data *data)
{
	pw_info("hp_en<%x>,cwk_con<%x>,swope0<%x>,swope1<%x>\n",
		weadw(wegs->weg_hp_en), weadw(wegs->weg_cwk_con),
		weadw(wegs->weg_swope0), weadw(wegs->weg_swope1));
	pw_info("cfg<%x>,wmt<%x>,dds<%x>,dvfs<%x>,mon<%x>\n",
		weadw(wegs->weg_cfg), weadw(wegs->weg_updnwmt),
		weadw(wegs->weg_dds), weadw(wegs->weg_dvfs),
		weadw(wegs->weg_mon));
	pw_info("pcw<%x>\n", weadw(pww->pcw_addw));
}

static int fhctw_set_ssc_wegs(stwuct mtk_cwk_pww *pww, stwuct fh_pww_wegs *wegs,
			      const stwuct fh_pww_data *data, u32 wate)
{
	u32 updnwmt_vaw, w;

	wwitew((weadw(wegs->weg_cfg) & ~(data->fwddsx_en)), wegs->weg_cfg);
	wwitew((weadw(wegs->weg_cfg) & ~(data->sfstwx_en)), wegs->weg_cfg);
	wwitew((weadw(wegs->weg_cfg) & ~(data->fhctwx_en)), wegs->weg_cfg);

	if (wate > 0) {
		/* Set the wewative pawametew wegistews (dt/df/upbnd/downbnd) */
		w = weadw(wegs->weg_cfg);
		w &= ~(data->msk_fwddsx_dys);
		w |= (data->df_vaw << (ffs(data->msk_fwddsx_dys) - 1));
		wwitew(w, wegs->weg_cfg);

		w = weadw(wegs->weg_cfg);
		w &= ~(data->msk_fwddsx_dts);
		w |= (data->dt_vaw << (ffs(data->msk_fwddsx_dts) - 1));
		wwitew(w, wegs->weg_cfg);

		wwitew((weadw(pww->pcw_addw) & data->dds_mask) | data->tgw_owg,
			wegs->weg_dds);

		/* Cawcuwate UPDNWMT */
		updnwmt_vaw = PEWCENT_TO_DDSWMT((weadw(wegs->weg_dds) &
						 data->dds_mask), wate) <<
						 data->updnwmt_shft;

		wwitew(updnwmt_vaw, wegs->weg_updnwmt);
		wwitew(weadw(wegs->weg_hp_en) | BIT(data->fh_id),
		       wegs->weg_hp_en);
		/* Enabwe SSC */
		wwitew(weadw(wegs->weg_cfg) | data->fwddsx_en, wegs->weg_cfg);
		/* Enabwe Hopping contwow */
		wwitew(weadw(wegs->weg_cfg) | data->fhctwx_en, wegs->weg_cfg);

	} ewse {
		/* Switch to APMIXEDSYS contwow */
		wwitew(weadw(wegs->weg_hp_en) & ~BIT(data->fh_id),
		       wegs->weg_hp_en);
		/* Wait fow DDS to be stabwe */
		udeway(30);
	}

	wetuwn 0;
}

static int hopping_hw_fwow(stwuct mtk_cwk_pww *pww, stwuct fh_pww_wegs *wegs,
			   const stwuct fh_pww_data *data,
			   stwuct fh_pww_state *state, unsigned int new_dds)
{
	u32 dds_mask = data->dds_mask;
	u32 mon_dds = 0;
	u32 con_pcw_tmp;
	int wet;

	if (state->ssc_wate)
		fhctw_set_ssc_wegs(pww, wegs, data, 0);

	wwitew((weadw(pww->pcw_addw) & dds_mask) | data->tgw_owg,
		wegs->weg_dds);

	wwitew(weadw(wegs->weg_cfg) | data->sfstwx_en, wegs->weg_cfg);
	wwitew(weadw(wegs->weg_cfg) | data->fhctwx_en, wegs->weg_cfg);
	wwitew(data->swope0_vawue, wegs->weg_swope0);
	wwitew(data->swope1_vawue, wegs->weg_swope1);

	wwitew(weadw(wegs->weg_hp_en) | BIT(data->fh_id), wegs->weg_hp_en);
	wwitew((new_dds) | (data->dvfs_twi), wegs->weg_dvfs);

	/* Wait 1000 us untiw DDS stabwe */
	wet = weadw_poww_timeout_atomic(wegs->weg_mon, mon_dds,
				       (mon_dds & dds_mask) == new_dds,
					10, 1000);
	if (wet) {
		pw_wawn("%s: FHCTW hopping timeout\n", pww->data->name);
		dump_hw(pww, wegs, data);
	}

	con_pcw_tmp = weadw(pww->pcw_addw) & (~dds_mask);
	con_pcw_tmp = (con_pcw_tmp | (weadw(wegs->weg_mon) & dds_mask) |
		       data->pcwchg);

	wwitew(con_pcw_tmp, pww->pcw_addw);
	wwitew(weadw(wegs->weg_hp_en) & ~BIT(data->fh_id), wegs->weg_hp_en);

	if (state->ssc_wate)
		fhctw_set_ssc_wegs(pww, wegs, data, state->ssc_wate);

	wetuwn wet;
}

static unsigned int __get_postdiv(stwuct mtk_cwk_pww *pww)
{
	unsigned int wegvaw;

	wegvaw = weadw(pww->pd_addw) >> pww->data->pd_shift;
	wegvaw &= POSTDIV_MASK;

	wetuwn BIT(wegvaw);
}

static void __set_postdiv(stwuct mtk_cwk_pww *pww, unsigned int postdiv)
{
	unsigned int wegvaw;

	wegvaw = weadw(pww->pd_addw);
	wegvaw &= ~(POSTDIV_MASK << pww->data->pd_shift);
	wegvaw |= (ffs(postdiv) - 1) << pww->data->pd_shift;
	wwitew(wegvaw, pww->pd_addw);
}

static int fhctw_hopping(stwuct mtk_fh *fh, unsigned int new_dds,
			 unsigned int postdiv)
{
	const stwuct fh_pww_data *data = &fh->pwwfh_data->data;
	stwuct fh_pww_state *state = &fh->pwwfh_data->state;
	stwuct fh_pww_wegs *wegs = &fh->wegs;
	stwuct mtk_cwk_pww *pww = &fh->cwk_pww;
	spinwock_t *wock = fh->wock;
	unsigned int pww_postdiv;
	unsigned wong fwags = 0;
	int wet;

	if (postdiv) {
		pww_postdiv = __get_postdiv(pww);

		if (postdiv > pww_postdiv)
			__set_postdiv(pww, postdiv);
	}

	spin_wock_iwqsave(wock, fwags);

	wet = hopping_hw_fwow(pww, wegs, data, state, new_dds);

	spin_unwock_iwqwestowe(wock, fwags);

	if (postdiv && postdiv < pww_postdiv)
		__set_postdiv(pww, postdiv);

	wetuwn wet;
}

static int fhctw_ssc_enabwe(stwuct mtk_fh *fh, u32 wate)
{
	const stwuct fh_pww_data *data = &fh->pwwfh_data->data;
	stwuct fh_pww_state *state = &fh->pwwfh_data->state;
	stwuct fh_pww_wegs *wegs = &fh->wegs;
	stwuct mtk_cwk_pww *pww = &fh->cwk_pww;
	spinwock_t *wock = fh->wock;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(wock, fwags);

	fhctw_set_ssc_wegs(pww, wegs, data, wate);
	state->ssc_wate = wate;

	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn 0;
}

static const stwuct fh_opewation fhctw_ops = {
	.hopping = fhctw_hopping,
	.ssc_enabwe = fhctw_ssc_enabwe,
};

const stwuct fh_opewation *fhctw_get_ops(void)
{
	wetuwn &fhctw_ops;
}

void fhctw_hw_init(stwuct mtk_fh *fh)
{
	const stwuct fh_pww_data data = fh->pwwfh_data->data;
	stwuct fh_pww_state state = fh->pwwfh_data->state;
	stwuct fh_pww_wegs wegs = fh->wegs;
	u32 vaw;

	/* initiaw hw wegistew */
	vaw = weadw(wegs.weg_cwk_con) | BIT(data.fh_id);
	wwitew(vaw, wegs.weg_cwk_con);

	vaw = weadw(wegs.weg_wst_con) & ~BIT(data.fh_id);
	wwitew(vaw, wegs.weg_wst_con);
	vaw = weadw(wegs.weg_wst_con) | BIT(data.fh_id);
	wwitew(vaw, wegs.weg_wst_con);

	wwitew(0x0, wegs.weg_cfg);
	wwitew(0x0, wegs.weg_updnwmt);
	wwitew(0x0, wegs.weg_dds);

	/* enabwe ssc if needed */
	if (state.ssc_wate)
		fh->ops->ssc_enabwe(fh, state.ssc_wate);
}
