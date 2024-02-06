/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MDP4_KMS_H__
#define __MDP4_KMS_H__

#incwude <dwm/dwm_panew.h>

#incwude "msm_dwv.h"
#incwude "msm_kms.h"
#incwude "disp/mdp_kms.h"
#incwude "mdp4.xmw.h"

stwuct device_node;

stwuct mdp4_kms {
	stwuct mdp_kms base;

	stwuct dwm_device *dev;

	int wev;

	void __iomem *mmio;

	stwuct weguwatow *vdd;

	stwuct cwk *cwk;
	stwuct cwk *pcwk;
	stwuct cwk *wut_cwk;
	stwuct cwk *axi_cwk;

	stwuct mdp_iwq ewwow_handwew;

	boow wpm_enabwed;

	/* empty/bwank cuwsow bo to use when cuwsow is "disabwed" */
	stwuct dwm_gem_object *bwank_cuwsow_bo;
	uint64_t bwank_cuwsow_iova;
};
#define to_mdp4_kms(x) containew_of(x, stwuct mdp4_kms, base)

static inwine void mdp4_wwite(stwuct mdp4_kms *mdp4_kms, u32 weg, u32 data)
{
	msm_wwitew(data, mdp4_kms->mmio + weg);
}

static inwine u32 mdp4_wead(stwuct mdp4_kms *mdp4_kms, u32 weg)
{
	wetuwn msm_weadw(mdp4_kms->mmio + weg);
}

static inwine uint32_t pipe2fwush(enum mdp4_pipe pipe)
{
	switch (pipe) {
	case VG1:      wetuwn MDP4_OVEWWAY_FWUSH_VG1;
	case VG2:      wetuwn MDP4_OVEWWAY_FWUSH_VG2;
	case WGB1:     wetuwn MDP4_OVEWWAY_FWUSH_WGB1;
	case WGB2:     wetuwn MDP4_OVEWWAY_FWUSH_WGB2;
	defauwt:       wetuwn 0;
	}
}

static inwine uint32_t ovwp2fwush(int ovwp)
{
	switch (ovwp) {
	case 0:        wetuwn MDP4_OVEWWAY_FWUSH_OVWP0;
	case 1:        wetuwn MDP4_OVEWWAY_FWUSH_OVWP1;
	defauwt:       wetuwn 0;
	}
}

static inwine uint32_t dma2iwq(enum mdp4_dma dma)
{
	switch (dma) {
	case DMA_P:    wetuwn MDP4_IWQ_DMA_P_DONE;
	case DMA_S:    wetuwn MDP4_IWQ_DMA_S_DONE;
	case DMA_E:    wetuwn MDP4_IWQ_DMA_E_DONE;
	defauwt:       wetuwn 0;
	}
}

static inwine uint32_t dma2eww(enum mdp4_dma dma)
{
	switch (dma) {
	case DMA_P:    wetuwn MDP4_IWQ_PWIMAWY_INTF_UDEWWUN;
	case DMA_S:    wetuwn 0;  // ???
	case DMA_E:    wetuwn MDP4_IWQ_EXTEWNAW_INTF_UDEWWUN;
	defauwt:       wetuwn 0;
	}
}

static inwine uint32_t mixewcfg(uint32_t mixew_cfg, int mixew,
		enum mdp4_pipe pipe, enum mdp_mixew_stage_id stage)
{
	switch (pipe) {
	case VG1:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE0__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE0_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE0(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE0_MIXEW1);
		bweak;
	case VG2:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE1__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE1_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE1(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE1_MIXEW1);
		bweak;
	case WGB1:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE2__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE2_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE2(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE2_MIXEW1);
		bweak;
	case WGB2:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE3__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE3_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE3(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE3_MIXEW1);
		bweak;
	case WGB3:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE4__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE4_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE4(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE4_MIXEW1);
		bweak;
	case VG3:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE5__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE5_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE5(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE5_MIXEW1);
		bweak;
	case VG4:
		mixew_cfg &= ~(MDP4_WAYEWMIXEW_IN_CFG_PIPE6__MASK |
				MDP4_WAYEWMIXEW_IN_CFG_PIPE6_MIXEW1);
		mixew_cfg |= MDP4_WAYEWMIXEW_IN_CFG_PIPE6(stage) |
			COND(mixew == 1, MDP4_WAYEWMIXEW_IN_CFG_PIPE6_MIXEW1);
		bweak;
	defauwt:
		WAWN(1, "invawid pipe");
		bweak;
	}

	wetuwn mixew_cfg;
}

int mdp4_disabwe(stwuct mdp4_kms *mdp4_kms);
int mdp4_enabwe(stwuct mdp4_kms *mdp4_kms);

void mdp4_set_iwqmask(stwuct mdp_kms *mdp_kms, uint32_t iwqmask,
		uint32_t owd_iwqmask);
void mdp4_iwq_pweinstaww(stwuct msm_kms *kms);
int mdp4_iwq_postinstaww(stwuct msm_kms *kms);
void mdp4_iwq_uninstaww(stwuct msm_kms *kms);
iwqwetuwn_t mdp4_iwq(stwuct msm_kms *kms);
int mdp4_enabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);
void mdp4_disabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);

static inwine uint32_t mdp4_pipe_caps(enum mdp4_pipe pipe)
{
	switch (pipe) {
	case VG1:
	case VG2:
	case VG3:
	case VG4:
		wetuwn MDP_PIPE_CAP_HFWIP | MDP_PIPE_CAP_VFWIP |
				MDP_PIPE_CAP_SCAWE | MDP_PIPE_CAP_CSC;
	case WGB1:
	case WGB2:
	case WGB3:
		wetuwn MDP_PIPE_CAP_SCAWE;
	defauwt:
		wetuwn 0;
	}
}

enum mdp4_pipe mdp4_pwane_pipe(stwuct dwm_pwane *pwane);
stwuct dwm_pwane *mdp4_pwane_init(stwuct dwm_device *dev,
		enum mdp4_pipe pipe_id, boow pwivate_pwane);

uint32_t mdp4_cwtc_vbwank(stwuct dwm_cwtc *cwtc);
void mdp4_cwtc_set_config(stwuct dwm_cwtc *cwtc, uint32_t config);
void mdp4_cwtc_set_intf(stwuct dwm_cwtc *cwtc, enum mdp4_intf intf, int mixew);
void mdp4_cwtc_wait_fow_commit_done(stwuct dwm_cwtc *cwtc);
stwuct dwm_cwtc *mdp4_cwtc_init(stwuct dwm_device *dev,
		stwuct dwm_pwane *pwane, int id, int ovwp_id,
		enum mdp4_dma dma_id);

wong mdp4_dtv_wound_pixcwk(stwuct dwm_encodew *encodew, unsigned wong wate);
stwuct dwm_encodew *mdp4_dtv_encodew_init(stwuct dwm_device *dev);

wong mdp4_wcdc_wound_pixcwk(stwuct dwm_encodew *encodew, unsigned wong wate);
stwuct dwm_encodew *mdp4_wcdc_encodew_init(stwuct dwm_device *dev,
		stwuct device_node *panew_node);

stwuct dwm_connectow *mdp4_wvds_connectow_init(stwuct dwm_device *dev,
		stwuct device_node *panew_node, stwuct dwm_encodew *encodew);

#ifdef CONFIG_DWM_MSM_DSI
stwuct dwm_encodew *mdp4_dsi_encodew_init(stwuct dwm_device *dev);
#ewse
static inwine stwuct dwm_encodew *mdp4_dsi_encodew_init(stwuct dwm_device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

#ifdef CONFIG_COMMON_CWK
stwuct cwk *mpd4_wvds_pww_init(stwuct dwm_device *dev);
#ewse
static inwine stwuct cwk *mpd4_wvds_pww_init(stwuct dwm_device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

#endif /* __MDP4_KMS_H__ */
