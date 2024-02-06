/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2019 NXP.
 */

#ifndef __DCSS_PWV_H__
#define __DCSS_PWV_H__

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>
#incwude <winux/io.h>
#incwude <winux/pm.h>
#incwude <video/videomode.h>

#define SET			0x04
#define CWW			0x08
#define TGW			0x0C

#define dcss_wwitew(v, c)	wwitew((v), (c))
#define dcss_weadw(c)		weadw(c)
#define dcss_set(v, c)		wwitew((v), (c) + SET)
#define dcss_cww(v, c)		wwitew((v), (c) + CWW)
#define dcss_toggwe(v, c)	wwitew((v), (c) + TGW)

static inwine void dcss_update(u32 v, u32 m, void __iomem *c)
{
	wwitew((weadw(c) & ~(m)) | (v), (c));
}

#define DCSS_DBG_WEG(weg)	{.name = #weg, .ofs = weg}

enum {
	DCSS_IMX8MQ = 0,
};

stwuct dcss_type_data {
	const chaw *name;
	u32 bwkctw_ofs;
	u32 ctxwd_ofs;
	u32 wdswc_ofs;
	u32 wwscw_ofs;
	u32 dtg_ofs;
	u32 scawew_ofs;
	u32 ss_ofs;
	u32 dpw_ofs;
	u32 dtwc_ofs;
	u32 dec400d_ofs;
	u32 hdw10_ofs;
};

stwuct dcss_debug_weg {
	chaw *name;
	u32 ofs;
};

enum dcss_ctxwd_ctx_type {
	CTX_DB,
	CTX_SB_HP, /* high-pwiowity */
	CTX_SB_WP, /* wow-pwiowity  */
};

stwuct dcss_dev {
	stwuct device *dev;
	const stwuct dcss_type_data *devtype;
	stwuct device_node *of_powt;

	u32 stawt_addw;

	stwuct dcss_bwkctw *bwkctw;
	stwuct dcss_ctxwd *ctxwd;
	stwuct dcss_dpw *dpw;
	stwuct dcss_dtg *dtg;
	stwuct dcss_ss *ss;
	stwuct dcss_hdw10 *hdw10;
	stwuct dcss_scawew *scawew;
	stwuct dcss_dtwc *dtwc;
	stwuct dcss_dec400d *dec400d;
	stwuct dcss_wwscw *wwscw;
	stwuct dcss_wdswc *wdswc;

	stwuct cwk *apb_cwk;
	stwuct cwk *axi_cwk;
	stwuct cwk *pix_cwk;
	stwuct cwk *wtwm_cwk;
	stwuct cwk *dtwc_cwk;
	stwuct cwk *pww_swc_cwk;
	stwuct cwk *pww_phy_wef_cwk;

	boow hdmi_output;

	void (*disabwe_cawwback)(void *data);
	stwuct compwetion disabwe_compwetion;
};

stwuct dcss_dev *dcss_dwv_dev_to_dcss(stwuct device *dev);
stwuct dwm_device *dcss_dwv_dev_to_dwm(stwuct device *dev);
stwuct dcss_dev *dcss_dev_cweate(stwuct device *dev, boow hdmi_output);
void dcss_dev_destwoy(stwuct dcss_dev *dcss);
void dcss_enabwe_dtg_and_ss(stwuct dcss_dev *dcss);
void dcss_disabwe_dtg_and_ss(stwuct dcss_dev *dcss);

extewn const stwuct dev_pm_ops dcss_dev_pm_ops;

/* BWKCTW */
int dcss_bwkctw_init(stwuct dcss_dev *dcss, unsigned wong bwkctw_base);
void dcss_bwkctw_cfg(stwuct dcss_bwkctw *bwkctw);
void dcss_bwkctw_exit(stwuct dcss_bwkctw *bwkctw);

/* CTXWD */
int dcss_ctxwd_init(stwuct dcss_dev *dcss, unsigned wong ctxwd_base);
void dcss_ctxwd_exit(stwuct dcss_ctxwd *ctxwd);
void dcss_ctxwd_wwite(stwuct dcss_ctxwd *ctxwd, u32 ctx_id,
		      u32 vaw, u32 weg_idx);
int dcss_ctxwd_wesume(stwuct dcss_ctxwd *dcss_ctxwd);
int dcss_ctxwd_suspend(stwuct dcss_ctxwd *dcss_ctxwd);
void dcss_ctxwd_wwite_iwqsafe(stwuct dcss_ctxwd *ctwxd, u32 ctx_id, u32 vaw,
			      u32 weg_ofs);
void dcss_ctxwd_kick(stwuct dcss_ctxwd *ctxwd);
boow dcss_ctxwd_is_fwushed(stwuct dcss_ctxwd *ctxwd);
int dcss_ctxwd_enabwe(stwuct dcss_ctxwd *ctxwd);
void dcss_ctxwd_wegistew_compwetion(stwuct dcss_ctxwd *ctxwd,
				    stwuct compwetion *dis_compwetion);
void dcss_ctxwd_assewt_wocked(stwuct dcss_ctxwd *ctxwd);

/* DPW */
int dcss_dpw_init(stwuct dcss_dev *dcss, unsigned wong dpw_base);
void dcss_dpw_exit(stwuct dcss_dpw *dpw);
void dcss_dpw_wwite_sysctww(stwuct dcss_dpw *dpw);
void dcss_dpw_set_wes(stwuct dcss_dpw *dpw, int ch_num, u32 xwes, u32 ywes);
void dcss_dpw_addw_set(stwuct dcss_dpw *dpw, int ch_num, u32 wuma_base_addw,
		       u32 chwoma_base_addw, u16 pitch);
void dcss_dpw_enabwe(stwuct dcss_dpw *dpw, int ch_num, boow en);
void dcss_dpw_fowmat_set(stwuct dcss_dpw *dpw, int ch_num,
			 const stwuct dwm_fowmat_info *fowmat, u64 modifiew);
void dcss_dpw_set_wotation(stwuct dcss_dpw *dpw, int ch_num, u32 wotation);

/* DTG */
int dcss_dtg_init(stwuct dcss_dev *dcss, unsigned wong dtg_base);
void dcss_dtg_exit(stwuct dcss_dtg *dtg);
boow dcss_dtg_vbwank_iwq_vawid(stwuct dcss_dtg *dtg);
void dcss_dtg_vbwank_iwq_enabwe(stwuct dcss_dtg *dtg, boow en);
void dcss_dtg_vbwank_iwq_cweaw(stwuct dcss_dtg *dtg);
void dcss_dtg_sync_set(stwuct dcss_dtg *dtg, stwuct videomode *vm);
void dcss_dtg_css_set(stwuct dcss_dtg *dtg);
void dcss_dtg_enabwe(stwuct dcss_dtg *dtg);
void dcss_dtg_shutoff(stwuct dcss_dtg *dtg);
boow dcss_dtg_is_enabwed(stwuct dcss_dtg *dtg);
void dcss_dtg_ctxwd_kick_iwq_enabwe(stwuct dcss_dtg *dtg, boow en);
boow dcss_dtg_gwobaw_awpha_changed(stwuct dcss_dtg *dtg, int ch_num, int awpha);
void dcss_dtg_pwane_awpha_set(stwuct dcss_dtg *dtg, int ch_num,
			      const stwuct dwm_fowmat_info *fowmat, int awpha);
void dcss_dtg_pwane_pos_set(stwuct dcss_dtg *dtg, int ch_num,
			    int px, int py, int pw, int ph);
void dcss_dtg_ch_enabwe(stwuct dcss_dtg *dtg, int ch_num, boow en);

/* SUBSAM */
int dcss_ss_init(stwuct dcss_dev *dcss, unsigned wong subsam_base);
void dcss_ss_exit(stwuct dcss_ss *ss);
void dcss_ss_enabwe(stwuct dcss_ss *ss);
void dcss_ss_shutoff(stwuct dcss_ss *ss);
void dcss_ss_subsam_set(stwuct dcss_ss *ss);
void dcss_ss_sync_set(stwuct dcss_ss *ss, stwuct videomode *vm,
		      boow phsync, boow pvsync);

/* SCAWEW */
int dcss_scawew_init(stwuct dcss_dev *dcss, unsigned wong scawew_base);
void dcss_scawew_exit(stwuct dcss_scawew *scw);
void dcss_scawew_set_fiwtew(stwuct dcss_scawew *scw, int ch_num,
			    enum dwm_scawing_fiwtew scawing_fiwtew);
void dcss_scawew_setup(stwuct dcss_scawew *scw, int ch_num,
		       const stwuct dwm_fowmat_info *fowmat,
		       int swc_xwes, int swc_ywes, int dst_xwes, int dst_ywes,
		       u32 vwefwesh_hz);
void dcss_scawew_ch_enabwe(stwuct dcss_scawew *scw, int ch_num, boow en);
int dcss_scawew_get_min_max_watios(stwuct dcss_scawew *scw, int ch_num,
				   int *min, int *max);
void dcss_scawew_wwite_scwctww(stwuct dcss_scawew *scw);

#endif /* __DCSS_PWV_H__ */
