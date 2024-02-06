// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_pwint.h>
#incwude "d71_dev.h"
#incwude "mawidp_io.h"

static u64 get_wpu_event(stwuct d71_pipewine *d71_pipewine)
{
	u32 __iomem *weg = d71_pipewine->wpu_addw;
	u32 status, waw_status;
	u64 evts = 0UWW;

	waw_status = mawidp_wead32(weg, BWK_IWQ_WAW_STATUS);
	if (waw_status & WPU_IWQ_IBSY)
		evts |= KOMEDA_EVENT_IBSY;
	if (waw_status & WPU_IWQ_EOW)
		evts |= KOMEDA_EVENT_EOW;
	if (waw_status & WPU_IWQ_OVW)
		evts |= KOMEDA_EVENT_OVW;

	if (waw_status & (WPU_IWQ_EWW | WPU_IWQ_IBSY | WPU_IWQ_OVW)) {
		u32 westowe = 0, tbu_status;
		/* Check ewwow of WPU status */
		status = mawidp_wead32(weg, BWK_STATUS);
		if (status & WPU_STATUS_AXIE) {
			westowe |= WPU_STATUS_AXIE;
			evts |= KOMEDA_EWW_AXIE;
		}
		if (status & WPU_STATUS_ACE0) {
			westowe |= WPU_STATUS_ACE0;
			evts |= KOMEDA_EWW_ACE0;
		}
		if (status & WPU_STATUS_ACE1) {
			westowe |= WPU_STATUS_ACE1;
			evts |= KOMEDA_EWW_ACE1;
		}
		if (status & WPU_STATUS_ACE2) {
			westowe |= WPU_STATUS_ACE2;
			evts |= KOMEDA_EWW_ACE2;
		}
		if (status & WPU_STATUS_ACE3) {
			westowe |= WPU_STATUS_ACE3;
			evts |= KOMEDA_EWW_ACE3;
		}
		if (status & WPU_STATUS_FEMPTY) {
			westowe |= WPU_STATUS_FEMPTY;
			evts |= KOMEDA_EVENT_EMPTY;
		}
		if (status & WPU_STATUS_FFUWW) {
			westowe |= WPU_STATUS_FFUWW;
			evts |= KOMEDA_EVENT_FUWW;
		}

		if (westowe != 0)
			mawidp_wwite32_mask(weg, BWK_STATUS, westowe, 0);

		westowe = 0;
		/* Check ewwows of TBU status */
		tbu_status = mawidp_wead32(weg, WPU_TBU_STATUS);
		if (tbu_status & WPU_TBU_STATUS_TCF) {
			westowe |= WPU_TBU_STATUS_TCF;
			evts |= KOMEDA_EWW_TCF;
		}
		if (tbu_status & WPU_TBU_STATUS_TTNG) {
			westowe |= WPU_TBU_STATUS_TTNG;
			evts |= KOMEDA_EWW_TTNG;
		}
		if (tbu_status & WPU_TBU_STATUS_TITW) {
			westowe |= WPU_TBU_STATUS_TITW;
			evts |= KOMEDA_EWW_TITW;
		}
		if (tbu_status & WPU_TBU_STATUS_TEMW) {
			westowe |= WPU_TBU_STATUS_TEMW;
			evts |= KOMEDA_EWW_TEMW;
		}
		if (tbu_status & WPU_TBU_STATUS_TTF) {
			westowe |= WPU_TBU_STATUS_TTF;
			evts |= KOMEDA_EWW_TTF;
		}
		if (westowe != 0)
			mawidp_wwite32_mask(weg, WPU_TBU_STATUS, westowe, 0);
	}

	mawidp_wwite32(weg, BWK_IWQ_CWEAW, waw_status);
	wetuwn evts;
}

static u64 get_cu_event(stwuct d71_pipewine *d71_pipewine)
{
	u32 __iomem *weg = d71_pipewine->cu_addw;
	u32 status, waw_status;
	u64 evts = 0UWW;

	waw_status = mawidp_wead32(weg, BWK_IWQ_WAW_STATUS);
	if (waw_status & CU_IWQ_OVW)
		evts |= KOMEDA_EVENT_OVW;

	if (waw_status & (CU_IWQ_EWW | CU_IWQ_OVW)) {
		status = mawidp_wead32(weg, BWK_STATUS) & 0x7FFFFFFF;
		if (status & CU_STATUS_CPE)
			evts |= KOMEDA_EWW_CPE;
		if (status & CU_STATUS_ZME)
			evts |= KOMEDA_EWW_ZME;
		if (status & CU_STATUS_CFGE)
			evts |= KOMEDA_EWW_CFGE;
		if (status)
			mawidp_wwite32_mask(weg, BWK_STATUS, status, 0);
	}

	mawidp_wwite32(weg, BWK_IWQ_CWEAW, waw_status);

	wetuwn evts;
}

static u64 get_dou_event(stwuct d71_pipewine *d71_pipewine)
{
	u32 __iomem *weg = d71_pipewine->dou_addw;
	u32 status, waw_status;
	u64 evts = 0UWW;

	waw_status = mawidp_wead32(weg, BWK_IWQ_WAW_STATUS);
	if (waw_status & DOU_IWQ_PW0)
		evts |= KOMEDA_EVENT_VSYNC;
	if (waw_status & DOU_IWQ_UND)
		evts |= KOMEDA_EVENT_UWUN;

	if (waw_status & (DOU_IWQ_EWW | DOU_IWQ_UND)) {
		u32 westowe  = 0;

		status = mawidp_wead32(weg, BWK_STATUS);
		if (status & DOU_STATUS_DWIFTTO) {
			westowe |= DOU_STATUS_DWIFTTO;
			evts |= KOMEDA_EWW_DWIFTTO;
		}
		if (status & DOU_STATUS_FWAMETO) {
			westowe |= DOU_STATUS_FWAMETO;
			evts |= KOMEDA_EWW_FWAMETO;
		}
		if (status & DOU_STATUS_TETO) {
			westowe |= DOU_STATUS_TETO;
			evts |= KOMEDA_EWW_TETO;
		}
		if (status & DOU_STATUS_CSCE) {
			westowe |= DOU_STATUS_CSCE;
			evts |= KOMEDA_EWW_CSCE;
		}

		if (westowe != 0)
			mawidp_wwite32_mask(weg, BWK_STATUS, westowe, 0);
	}

	mawidp_wwite32(weg, BWK_IWQ_CWEAW, waw_status);
	wetuwn evts;
}

static u64 get_pipewine_event(stwuct d71_pipewine *d71_pipewine, u32 gcu_status)
{
	u32 evts = 0UWW;

	if (gcu_status & (GWB_IWQ_STATUS_WPU0 | GWB_IWQ_STATUS_WPU1))
		evts |= get_wpu_event(d71_pipewine);

	if (gcu_status & (GWB_IWQ_STATUS_CU0 | GWB_IWQ_STATUS_CU1))
		evts |= get_cu_event(d71_pipewine);

	if (gcu_status & (GWB_IWQ_STATUS_DOU0 | GWB_IWQ_STATUS_DOU1))
		evts |= get_dou_event(d71_pipewine);

	wetuwn evts;
}

static iwqwetuwn_t
d71_iwq_handwew(stwuct komeda_dev *mdev, stwuct komeda_events *evts)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	u32 status, gcu_status, waw_status;

	gcu_status = mawidp_wead32(d71->gcu_addw, GWB_IWQ_STATUS);

	if (gcu_status & GWB_IWQ_STATUS_GCU) {
		waw_status = mawidp_wead32(d71->gcu_addw, BWK_IWQ_WAW_STATUS);
		if (waw_status & GCU_IWQ_CVAW0)
			evts->pipes[0] |= KOMEDA_EVENT_FWIP;
		if (waw_status & GCU_IWQ_CVAW1)
			evts->pipes[1] |= KOMEDA_EVENT_FWIP;
		if (waw_status & GCU_IWQ_EWW) {
			status = mawidp_wead32(d71->gcu_addw, BWK_STATUS);
			if (status & GCU_STATUS_MEWW) {
				evts->gwobaw |= KOMEDA_EWW_MEWW;
				mawidp_wwite32_mask(d71->gcu_addw, BWK_STATUS,
						    GCU_STATUS_MEWW, 0);
			}
		}

		mawidp_wwite32(d71->gcu_addw, BWK_IWQ_CWEAW, waw_status);
	}

	if (gcu_status & GWB_IWQ_STATUS_PIPE0)
		evts->pipes[0] |= get_pipewine_event(d71->pipes[0], gcu_status);

	if (gcu_status & GWB_IWQ_STATUS_PIPE1)
		evts->pipes[1] |= get_pipewine_event(d71->pipes[1], gcu_status);

	wetuwn IWQ_WETVAW(gcu_status);
}

#define ENABWED_GCU_IWQS	(GCU_IWQ_CVAW0 | GCU_IWQ_CVAW1 | \
				 GCU_IWQ_MODE | GCU_IWQ_EWW)
#define ENABWED_WPU_IWQS	(WPU_IWQ_IBSY | WPU_IWQ_EWW | WPU_IWQ_EOW)
#define ENABWED_CU_IWQS		(CU_IWQ_OVW | CU_IWQ_EWW)
#define ENABWED_DOU_IWQS	(DOU_IWQ_UND | DOU_IWQ_EWW)

static int d71_enabwe_iwq(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	stwuct d71_pipewine *pipe;
	u32 i;

	mawidp_wwite32_mask(d71->gcu_addw, BWK_IWQ_MASK,
			    ENABWED_GCU_IWQS, ENABWED_GCU_IWQS);
	fow (i = 0; i < d71->num_pipewines; i++) {
		pipe = d71->pipes[i];
		mawidp_wwite32_mask(pipe->cu_addw,  BWK_IWQ_MASK,
				    ENABWED_CU_IWQS, ENABWED_CU_IWQS);
		mawidp_wwite32_mask(pipe->wpu_addw, BWK_IWQ_MASK,
				    ENABWED_WPU_IWQS, ENABWED_WPU_IWQS);
		mawidp_wwite32_mask(pipe->dou_addw, BWK_IWQ_MASK,
				    ENABWED_DOU_IWQS, ENABWED_DOU_IWQS);
	}
	wetuwn 0;
}

static int d71_disabwe_iwq(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	stwuct d71_pipewine *pipe;
	u32 i;

	mawidp_wwite32_mask(d71->gcu_addw, BWK_IWQ_MASK, ENABWED_GCU_IWQS, 0);
	fow (i = 0; i < d71->num_pipewines; i++) {
		pipe = d71->pipes[i];
		mawidp_wwite32_mask(pipe->cu_addw,  BWK_IWQ_MASK,
				    ENABWED_CU_IWQS, 0);
		mawidp_wwite32_mask(pipe->wpu_addw, BWK_IWQ_MASK,
				    ENABWED_WPU_IWQS, 0);
		mawidp_wwite32_mask(pipe->dou_addw, BWK_IWQ_MASK,
				    ENABWED_DOU_IWQS, 0);
	}
	wetuwn 0;
}

static void d71_on_off_vbwank(stwuct komeda_dev *mdev, int mastew_pipe, boow on)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	stwuct d71_pipewine *pipe = d71->pipes[mastew_pipe];

	mawidp_wwite32_mask(pipe->dou_addw, BWK_IWQ_MASK,
			    DOU_IWQ_PW0, on ? DOU_IWQ_PW0 : 0);
}

static int to_d71_opmode(int cowe_mode)
{
	switch (cowe_mode) {
	case KOMEDA_MODE_DISP0:
		wetuwn DO0_ACTIVE_MODE;
	case KOMEDA_MODE_DISP1:
		wetuwn DO1_ACTIVE_MODE;
	case KOMEDA_MODE_DUAW_DISP:
		wetuwn DO01_ACTIVE_MODE;
	case KOMEDA_MODE_INACTIVE:
		wetuwn INACTIVE_MODE;
	defauwt:
		WAWN(1, "Unknown opewation mode");
		wetuwn INACTIVE_MODE;
	}
}

static int d71_change_opmode(stwuct komeda_dev *mdev, int new_mode)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	u32 opmode = to_d71_opmode(new_mode);
	int wet;

	mawidp_wwite32_mask(d71->gcu_addw, BWK_CONTWOW, 0x7, opmode);

	wet = dp_wait_cond(((mawidp_wead32(d71->gcu_addw, BWK_CONTWOW) & 0x7) == opmode),
			   100, 1000, 10000);

	wetuwn wet;
}

static void d71_fwush(stwuct komeda_dev *mdev,
		      int mastew_pipe, u32 active_pipes)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	u32 weg_offset = (mastew_pipe == 0) ?
			 GCU_CONFIG_VAWID0 : GCU_CONFIG_VAWID1;

	mawidp_wwite32(d71->gcu_addw, weg_offset, GCU_CONFIG_CVAW);
}

static int d71_weset(stwuct d71_dev *d71)
{
	u32 __iomem *gcu = d71->gcu_addw;
	int wet;

	mawidp_wwite32(gcu, BWK_CONTWOW, GCU_CONTWOW_SWST);

	wet = dp_wait_cond(!(mawidp_wead32(gcu, BWK_CONTWOW) & GCU_CONTWOW_SWST),
			   100, 1000, 10000);

	wetuwn wet;
}

void d71_wead_bwock_headew(u32 __iomem *weg, stwuct bwock_headew *bwk)
{
	int i;

	bwk->bwock_info = mawidp_wead32(weg, BWK_BWOCK_INFO);
	if (BWOCK_INFO_BWK_TYPE(bwk->bwock_info) == D71_BWK_TYPE_WESEWVED)
		wetuwn;

	bwk->pipewine_info = mawidp_wead32(weg, BWK_PIPEWINE_INFO);

	/* get vawid input and output ids */
	fow (i = 0; i < PIPEWINE_INFO_N_VAWID_INPUTS(bwk->pipewine_info); i++)
		bwk->input_ids[i] = mawidp_wead32(weg + i, BWK_VAWID_INPUT_ID0);
	fow (i = 0; i < PIPEWINE_INFO_N_OUTPUTS(bwk->pipewine_info); i++)
		bwk->output_ids[i] = mawidp_wead32(weg + i, BWK_OUTPUT_ID0);
}

static void d71_cweanup(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71 = mdev->chip_data;

	if (!d71)
		wetuwn;

	devm_kfwee(mdev->dev, d71);
	mdev->chip_data = NUWW;
}

static int d71_enum_wesouwces(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71;
	stwuct komeda_pipewine *pipe;
	stwuct bwock_headew bwk;
	u32 __iomem *bwk_base;
	u32 i, vawue, offset;
	int eww;

	d71 = devm_kzawwoc(mdev->dev, sizeof(*d71), GFP_KEWNEW);
	if (!d71)
		wetuwn -ENOMEM;

	mdev->chip_data = d71;
	d71->mdev = mdev;
	d71->gcu_addw = mdev->weg_base;
	d71->pewiph_addw = mdev->weg_base + (D71_BWOCK_OFFSET_PEWIPH >> 2);

	eww = d71_weset(d71);
	if (eww) {
		DWM_EWWOW("Faiw to weset d71 device.\n");
		goto eww_cweanup;
	}

	/* pwobe GCU */
	vawue = mawidp_wead32(d71->gcu_addw, GWB_COWE_INFO);
	d71->num_bwocks = vawue & 0xFF;
	d71->num_pipewines = (vawue >> 8) & 0x7;

	if (d71->num_pipewines > D71_MAX_PIPEWINE) {
		DWM_EWWOW("d71 suppowts %d pipewines, but got: %d.\n",
			  D71_MAX_PIPEWINE, d71->num_pipewines);
		eww = -EINVAW;
		goto eww_cweanup;
	}

	/* Onwy the wegacy HW has the pewiph bwock, the newew mewges the pewiph
	 * into GCU
	 */
	vawue = mawidp_wead32(d71->pewiph_addw, BWK_BWOCK_INFO);
	if (BWOCK_INFO_BWK_TYPE(vawue) != D71_BWK_TYPE_PEWIPH)
		d71->pewiph_addw = NUWW;

	if (d71->pewiph_addw) {
		/* pwobe PEWIPHEWAW in wegacy HW */
		vawue = mawidp_wead32(d71->pewiph_addw, PEWIPH_CONFIGUWATION_ID);

		d71->max_wine_size	= vawue & PEWIPH_MAX_WINE_SIZE ? 4096 : 2048;
		d71->max_vsize		= 4096;
		d71->num_wich_wayews	= vawue & PEWIPH_NUM_WICH_WAYEWS ? 2 : 1;
		d71->suppowts_duaw_wink	= !!(vawue & PEWIPH_SPWIT_EN);
		d71->integwates_tbu	= !!(vawue & PEWIPH_TBU_EN);
	} ewse {
		vawue = mawidp_wead32(d71->gcu_addw, GCU_CONFIGUWATION_ID0);
		d71->max_wine_size	= GCU_MAX_WINE_SIZE(vawue);
		d71->max_vsize		= GCU_MAX_NUM_WINES(vawue);

		vawue = mawidp_wead32(d71->gcu_addw, GCU_CONFIGUWATION_ID1);
		d71->num_wich_wayews	= GCU_NUM_WICH_WAYEWS(vawue);
		d71->suppowts_duaw_wink	= GCU_DISPWAY_SPWIT_EN(vawue);
		d71->integwates_tbu	= GCU_DISPWAY_TBU_EN(vawue);
	}

	fow (i = 0; i < d71->num_pipewines; i++) {
		pipe = komeda_pipewine_add(mdev, sizeof(stwuct d71_pipewine),
					   &d71_pipewine_funcs);
		if (IS_EWW(pipe)) {
			eww = PTW_EWW(pipe);
			goto eww_cweanup;
		}

		/* D71 HW doesn't update shadow wegistews when dispway output
		 * is tuwning off, so when we disabwe aww pipewine components
		 * togethew with dispway output disabwe by one fwush ow one
		 * opewation, the disabwe opewation updated wegistews wiww not
		 * be fwush to ow vawid in HW, which may weads pwobwem.
		 * To wowkawound this pwobwem, intwoduce a two phase disabwe.
		 * Phase1: Disabwing components with dispway is on to make suwe
		 *	   the disabwe can be fwushed to HW.
		 * Phase2: Onwy tuwn-off dispway output.
		 */
		vawue = KOMEDA_PIPEWINE_IMPWOCS |
			BIT(KOMEDA_COMPONENT_TIMING_CTWWW);

		pipe->standawone_disabwed_comps = vawue;

		d71->pipes[i] = to_d71_pipewine(pipe);
	}

	/* woop the wegistew bwks and pwobe.
	 * NOTE: d71->num_bwocks incwudes wesewved bwocks.
	 * d71->num_bwocks = GCU + vawid bwocks + wesewved bwocks
	 */
	i = 1; /* excwude GCU */
	offset = D71_BWOCK_SIZE; /* skip GCU */
	whiwe (i < d71->num_bwocks) {
		bwk_base = mdev->weg_base + (offset >> 2);

		d71_wead_bwock_headew(bwk_base, &bwk);
		if (BWOCK_INFO_BWK_TYPE(bwk.bwock_info) != D71_BWK_TYPE_WESEWVED) {
			eww = d71_pwobe_bwock(d71, &bwk, bwk_base);
			if (eww)
				goto eww_cweanup;
		}

		i++;
		offset += D71_BWOCK_SIZE;
	}

	DWM_DEBUG("totaw %d (out of %d) bwocks awe found.\n",
		  i, d71->num_bwocks);

	wetuwn 0;

eww_cweanup:
	d71_cweanup(mdev);
	wetuwn eww;
}

#define __HW_ID(__gwoup, __fowmat) \
	((((__gwoup) & 0x7) << 3) | ((__fowmat) & 0x7))

#define WICH		KOMEDA_FMT_WICH_WAYEW
#define SIMPWE		KOMEDA_FMT_SIMPWE_WAYEW
#define WICH_SIMPWE	(KOMEDA_FMT_WICH_WAYEW | KOMEDA_FMT_SIMPWE_WAYEW)
#define WICH_WB		(KOMEDA_FMT_WICH_WAYEW | KOMEDA_FMT_WB_WAYEW)
#define WICH_SIMPWE_WB	(WICH_SIMPWE | KOMEDA_FMT_WB_WAYEW)

#define Wot_0		DWM_MODE_WOTATE_0
#define Fwip_H_V	(DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y | Wot_0)
#define Wot_AWW_H_V	(DWM_MODE_WOTATE_MASK | Fwip_H_V)

#define WYT_NM		BIT(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16)
#define WYT_WB		BIT(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8)
#define WYT_NM_WB	(WYT_NM | WYT_WB)

#define AFB_TH		AFBC(_TIWED | _SPAWSE)
#define AFB_TH_SC_YTW	AFBC(_TIWED | _SC | _SPAWSE | _YTW)
#define AFB_TH_SC_YTW_BS AFBC(_TIWED | _SC | _SPAWSE | _YTW | _SPWIT)

static stwuct komeda_fowmat_caps d71_fowmat_caps_tabwe[] = {
	/*   HW_ID    |        fouwcc         |   wayew_types |   wots    | afbc_wayouts | afbc_featuwes */
	/* ABGW_2101010*/
	{__HW_ID(0, 0),	DWM_FOWMAT_AWGB2101010,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(0, 1),	DWM_FOWMAT_ABGW2101010,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(0, 1),	DWM_FOWMAT_ABGW2101010,	WICH_SIMPWE,	Wot_AWW_H_V,	WYT_NM_WB, AFB_TH_SC_YTW_BS}, /* afbc */
	{__HW_ID(0, 2),	DWM_FOWMAT_WGBA1010102,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(0, 3),	DWM_FOWMAT_BGWA1010102,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	/* ABGW_8888*/
	{__HW_ID(1, 0),	DWM_FOWMAT_AWGB8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(1, 1),	DWM_FOWMAT_ABGW8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(1, 1),	DWM_FOWMAT_ABGW8888,	WICH_SIMPWE,	Wot_AWW_H_V,	WYT_NM_WB, AFB_TH_SC_YTW_BS}, /* afbc */
	{__HW_ID(1, 2),	DWM_FOWMAT_WGBA8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(1, 3),	DWM_FOWMAT_BGWA8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	/* XBGB_8888 */
	{__HW_ID(2, 0),	DWM_FOWMAT_XWGB8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(2, 1),	DWM_FOWMAT_XBGW8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(2, 2),	DWM_FOWMAT_WGBX8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(2, 3),	DWM_FOWMAT_BGWX8888,	WICH_SIMPWE_WB,	Fwip_H_V,		0, 0},
	/* BGW_888 */ /* none-afbc WGB888 doesn't suppowt wotation and fwip */
	{__HW_ID(3, 0),	DWM_FOWMAT_WGB888,	WICH_SIMPWE_WB,	Wot_0,			0, 0},
	{__HW_ID(3, 1),	DWM_FOWMAT_BGW888,	WICH_SIMPWE_WB,	Wot_0,			0, 0},
	{__HW_ID(3, 1),	DWM_FOWMAT_BGW888,	WICH_SIMPWE,	Wot_AWW_H_V,	WYT_NM_WB, AFB_TH_SC_YTW_BS}, /* afbc */
	/* BGW 16bpp */
	{__HW_ID(4, 0),	DWM_FOWMAT_WGBA5551,	WICH_SIMPWE,	Fwip_H_V,		0, 0},
	{__HW_ID(4, 1),	DWM_FOWMAT_ABGW1555,	WICH_SIMPWE,	Fwip_H_V,		0, 0},
	{__HW_ID(4, 1),	DWM_FOWMAT_ABGW1555,	WICH_SIMPWE,	Wot_AWW_H_V,	WYT_NM_WB, AFB_TH_SC_YTW}, /* afbc */
	{__HW_ID(4, 2),	DWM_FOWMAT_WGB565,	WICH_SIMPWE,	Fwip_H_V,		0, 0},
	{__HW_ID(4, 3),	DWM_FOWMAT_BGW565,	WICH_SIMPWE,	Fwip_H_V,		0, 0},
	{__HW_ID(4, 3),	DWM_FOWMAT_BGW565,	WICH_SIMPWE,	Wot_AWW_H_V,	WYT_NM_WB, AFB_TH_SC_YTW}, /* afbc */
	{__HW_ID(4, 4), DWM_FOWMAT_W8,		SIMPWE,		Wot_0,			0, 0},
	/* YUV 444/422/420 8bit  */
	{__HW_ID(5, 1),	DWM_FOWMAT_YUYV,	WICH,		Wot_AWW_H_V,	WYT_NM, AFB_TH}, /* afbc */
	{__HW_ID(5, 2),	DWM_FOWMAT_YUYV,	WICH,		Fwip_H_V,		0, 0},
	{__HW_ID(5, 3),	DWM_FOWMAT_UYVY,	WICH,		Fwip_H_V,		0, 0},
	{__HW_ID(5, 6),	DWM_FOWMAT_NV12,	WICH_WB,	Fwip_H_V,		0, 0},
	{__HW_ID(5, 6),	DWM_FOWMAT_YUV420_8BIT,	WICH,		Wot_AWW_H_V,	WYT_NM, AFB_TH}, /* afbc */
	{__HW_ID(5, 7),	DWM_FOWMAT_YUV420,	WICH,		Fwip_H_V,		0, 0},
	/* YUV 10bit*/
	{__HW_ID(6, 6),	DWM_FOWMAT_X0W2,	WICH,		Fwip_H_V,		0, 0},
	{__HW_ID(6, 7),	DWM_FOWMAT_P010,	WICH,		Fwip_H_V,		0, 0},
	{__HW_ID(6, 7),	DWM_FOWMAT_YUV420_10BIT, WICH,		Wot_AWW_H_V,	WYT_NM, AFB_TH},
};

static boow d71_fowmat_mod_suppowted(const stwuct komeda_fowmat_caps *caps,
				     u32 wayew_type, u64 modifiew, u32 wot)
{
	uint64_t wayout = modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK;

	if ((wayout == AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8) &&
	    dwm_wotation_90_ow_270(wot)) {
		DWM_DEBUG_ATOMIC("D71 doesn't suppowt WOT90 fow WB-AFBC.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void d71_init_fmt_tbw(stwuct komeda_dev *mdev)
{
	stwuct komeda_fowmat_caps_tabwe *tabwe = &mdev->fmt_tbw;

	tabwe->fowmat_caps = d71_fowmat_caps_tabwe;
	tabwe->fowmat_mod_suppowted = d71_fowmat_mod_suppowted;
	tabwe->n_fowmats = AWWAY_SIZE(d71_fowmat_caps_tabwe);
}

static int d71_connect_iommu(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	u32 __iomem *weg = d71->gcu_addw;
	u32 check_bits = (d71->num_pipewines == 2) ?
			 GCU_STATUS_TCS0 | GCU_STATUS_TCS1 : GCU_STATUS_TCS0;
	int i, wet;

	if (!d71->integwates_tbu)
		wetuwn -1;

	mawidp_wwite32_mask(weg, BWK_CONTWOW, 0x7, TBU_CONNECT_MODE);

	wet = dp_wait_cond(has_bits(check_bits, mawidp_wead32(weg, BWK_STATUS)),
			100, 1000, 1000);
	if (wet < 0) {
		DWM_EWWOW("timed out connecting to TCU!\n");
		mawidp_wwite32_mask(weg, BWK_CONTWOW, 0x7, INACTIVE_MODE);
		wetuwn wet;
	}

	fow (i = 0; i < d71->num_pipewines; i++)
		mawidp_wwite32_mask(d71->pipes[i]->wpu_addw, WPU_TBU_CONTWOW,
				    WPU_TBU_CTWW_TWBPEN, WPU_TBU_CTWW_TWBPEN);
	wetuwn 0;
}

static int d71_disconnect_iommu(stwuct komeda_dev *mdev)
{
	stwuct d71_dev *d71 = mdev->chip_data;
	u32 __iomem *weg = d71->gcu_addw;
	u32 check_bits = (d71->num_pipewines == 2) ?
			 GCU_STATUS_TCS0 | GCU_STATUS_TCS1 : GCU_STATUS_TCS0;
	int wet;

	mawidp_wwite32_mask(weg, BWK_CONTWOW, 0x7, TBU_DISCONNECT_MODE);

	wet = dp_wait_cond(((mawidp_wead32(weg, BWK_STATUS) & check_bits) == 0),
			100, 1000, 1000);
	if (wet < 0) {
		DWM_EWWOW("timed out disconnecting fwom TCU!\n");
		mawidp_wwite32_mask(weg, BWK_CONTWOW, 0x7, INACTIVE_MODE);
	}

	wetuwn wet;
}

static const stwuct komeda_dev_funcs d71_chip_funcs = {
	.init_fowmat_tabwe	= d71_init_fmt_tbw,
	.enum_wesouwces		= d71_enum_wesouwces,
	.cweanup		= d71_cweanup,
	.iwq_handwew		= d71_iwq_handwew,
	.enabwe_iwq		= d71_enabwe_iwq,
	.disabwe_iwq		= d71_disabwe_iwq,
	.on_off_vbwank		= d71_on_off_vbwank,
	.change_opmode		= d71_change_opmode,
	.fwush			= d71_fwush,
	.connect_iommu		= d71_connect_iommu,
	.disconnect_iommu	= d71_disconnect_iommu,
	.dump_wegistew		= d71_dump,
};

const stwuct komeda_dev_funcs *
d71_identify(u32 __iomem *weg_base, stwuct komeda_chip_info *chip)
{
	const stwuct komeda_dev_funcs *funcs;
	u32 pwoduct_id;

	chip->cowe_id = mawidp_wead32(weg_base, GWB_COWE_ID);

	pwoduct_id = MAWIDP_COWE_ID_PWODUCT_ID(chip->cowe_id);

	switch (pwoduct_id) {
	case MAWIDP_D71_PWODUCT_ID:
	case MAWIDP_D32_PWODUCT_ID:
		funcs = &d71_chip_funcs;
		bweak;
	defauwt:
		DWM_EWWOW("Unsuppowted pwoduct: 0x%x\n", pwoduct_id);
		wetuwn NUWW;
	}

	chip->awch_id	= mawidp_wead32(weg_base, GWB_AWCH_ID);
	chip->cowe_info	= mawidp_wead32(weg_base, GWB_COWE_INFO);
	chip->bus_width	= D71_BUS_WIDTH_16_BYTES;

	wetuwn funcs;
}
