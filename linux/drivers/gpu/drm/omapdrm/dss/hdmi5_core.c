// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP5 HDMI COWE IP dwivew wibwawy
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authows:
 *	Yong Zhi
 *	Mythwi pk
 *	Awchit Taneja <awchit@ti.com>
 *	Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <dwm/dwm_edid.h>
#incwude <sound/asound.h>
#incwude <sound/asoundef.h>

#incwude "hdmi5_cowe.h"

void hdmi5_cowe_ddc_init(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;
	const unsigned wong wong icwk = 266000000;	/* DSS W3 ICWK */
	const unsigned int ss_scw_high = 4700;		/* ns */
	const unsigned int ss_scw_wow = 5500;		/* ns */
	const unsigned int fs_scw_high = 600;		/* ns */
	const unsigned int fs_scw_wow = 1300;		/* ns */
	const unsigned int sda_howd = 1000;		/* ns */
	const unsigned int sfw_div = 10;
	unsigned wong wong sfw;
	unsigned int v;

	sfw = icwk / sfw_div;	/* SFW_DIV */
	sfw /= 1000;		/* SFW cwock in kHz */

	/* Weset */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SOFTWSTZ, 0, 0, 0);
	if (hdmi_wait_fow_bit_change(base, HDMI_COWE_I2CM_SOFTWSTZ,
				0, 0, 1) != 1)
		DSSEWW("HDMI I2CM weset faiwed\n");

	/* Standawd (0) ow Fast (1) Mode */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_DIV, 0, 3, 3);

	/* Standawd Mode SCW High countew */
	v = DIV_WOUND_UP_UWW(ss_scw_high * sfw, 1000000);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SS_SCW_HCNT_1_ADDW,
			(v >> 8) & 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SS_SCW_HCNT_0_ADDW,
			v & 0xff, 7, 0);

	/* Standawd Mode SCW Wow countew */
	v = DIV_WOUND_UP_UWW(ss_scw_wow * sfw, 1000000);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SS_SCW_WCNT_1_ADDW,
			(v >> 8) & 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SS_SCW_WCNT_0_ADDW,
			v & 0xff, 7, 0);

	/* Fast Mode SCW High Countew */
	v = DIV_WOUND_UP_UWW(fs_scw_high * sfw, 1000000);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_FS_SCW_HCNT_1_ADDW,
			(v >> 8) & 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_FS_SCW_HCNT_0_ADDW,
			v & 0xff, 7, 0);

	/* Fast Mode SCW Wow Countew */
	v = DIV_WOUND_UP_UWW(fs_scw_wow * sfw, 1000000);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_FS_SCW_WCNT_1_ADDW,
			(v >> 8) & 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_FS_SCW_WCNT_0_ADDW,
			v & 0xff, 7, 0);

	/* SDA Howd Time */
	v = DIV_WOUND_UP_UWW(sda_howd * sfw, 1000000);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SDA_HOWD_ADDW, v & 0xff, 7, 0);

	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SWAVE, 0x50, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SEGADDW, 0x30, 6, 0);

	/* NACK_POW to high */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 7, 7);

	/* NACK_MASK to unmasked */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x0, 6, 6);

	/* AWBITWATION_POW to high */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 3, 3);

	/* AWBITWATION_MASK to unmasked */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x0, 2, 2);

	/* DONE_POW to high */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_INT, 0x1, 3, 3);

	/* DONE_MASK to unmasked */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_INT, 0x0, 2, 2);
}

void hdmi5_cowe_ddc_uninit(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;

	/* Mask I2C intewwupts */
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 6, 6);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 2, 2);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_INT, 0x1, 2, 2);
}

int hdmi5_cowe_ddc_wead(void *data, u8 *buf, unsigned int bwock, size_t wen)
{
	stwuct hdmi_cowe_data *cowe = data;
	void __iomem *base = cowe->base;
	u8 cuw_addw;
	const int wetwies = 1000;
	u8 seg_ptw = bwock / 2;
	u8 edidbase = ((bwock % 2) * EDID_WENGTH);

	WEG_FWD_MOD(base, HDMI_COWE_I2CM_SEGPTW, seg_ptw, 7, 0);

	/*
	 * TODO: We use powwing hewe, awthough we pwobabwy shouwd use pwopew
	 * intewwupts.
	 */
	fow (cuw_addw = 0; cuw_addw < wen; ++cuw_addw) {
		int i;

		/* cweaw EWWOW and DONE */
		WEG_FWD_MOD(base, HDMI_COWE_IH_I2CM_STAT0, 0x3, 1, 0);

		WEG_FWD_MOD(base, HDMI_COWE_I2CM_ADDWESS,
				edidbase + cuw_addw, 7, 0);

		if (seg_ptw)
			WEG_FWD_MOD(base, HDMI_COWE_I2CM_OPEWATION, 1, 1, 1);
		ewse
			WEG_FWD_MOD(base, HDMI_COWE_I2CM_OPEWATION, 1, 0, 0);

		fow (i = 0; i < wetwies; ++i) {
			u32 stat;

			stat = WEG_GET(base, HDMI_COWE_IH_I2CM_STAT0, 1, 0);

			/* I2CM_EWWOW */
			if (stat & 1) {
				DSSEWW("HDMI I2C Mastew Ewwow\n");
				wetuwn -EIO;
			}

			/* I2CM_DONE */
			if (stat & (1 << 1))
				bweak;

			usweep_wange(250, 1000);
		}

		if (i == wetwies) {
			DSSEWW("HDMI I2C timeout weading EDID\n");
			wetuwn -EIO;
		}

		buf[cuw_addw] = WEG_GET(base, HDMI_COWE_I2CM_DATAI, 7, 0);
	}

	wetuwn 0;

}

void hdmi5_cowe_dump(stwuct hdmi_cowe_data *cowe, stwuct seq_fiwe *s)
{

#define DUMPCOWE(w) seq_pwintf(s, "%-35s %08x\n", #w,\
		hdmi_wead_weg(cowe->base, w))

	DUMPCOWE(HDMI_COWE_FC_INVIDCONF);
	DUMPCOWE(HDMI_COWE_FC_INHACTIV0);
	DUMPCOWE(HDMI_COWE_FC_INHACTIV1);
	DUMPCOWE(HDMI_COWE_FC_INHBWANK0);
	DUMPCOWE(HDMI_COWE_FC_INHBWANK1);
	DUMPCOWE(HDMI_COWE_FC_INVACTIV0);
	DUMPCOWE(HDMI_COWE_FC_INVACTIV1);
	DUMPCOWE(HDMI_COWE_FC_INVBWANK);
	DUMPCOWE(HDMI_COWE_FC_HSYNCINDEWAY0);
	DUMPCOWE(HDMI_COWE_FC_HSYNCINDEWAY1);
	DUMPCOWE(HDMI_COWE_FC_HSYNCINWIDTH0);
	DUMPCOWE(HDMI_COWE_FC_HSYNCINWIDTH1);
	DUMPCOWE(HDMI_COWE_FC_VSYNCINDEWAY);
	DUMPCOWE(HDMI_COWE_FC_VSYNCINWIDTH);
	DUMPCOWE(HDMI_COWE_FC_CTWWDUW);
	DUMPCOWE(HDMI_COWE_FC_EXCTWWDUW);
	DUMPCOWE(HDMI_COWE_FC_EXCTWWSPAC);
	DUMPCOWE(HDMI_COWE_FC_CH0PWEAM);
	DUMPCOWE(HDMI_COWE_FC_CH1PWEAM);
	DUMPCOWE(HDMI_COWE_FC_CH2PWEAM);
	DUMPCOWE(HDMI_COWE_FC_AVICONF0);
	DUMPCOWE(HDMI_COWE_FC_AVICONF1);
	DUMPCOWE(HDMI_COWE_FC_AVICONF2);
	DUMPCOWE(HDMI_COWE_FC_AVIVID);
	DUMPCOWE(HDMI_COWE_FC_PWCONF);

	DUMPCOWE(HDMI_COWE_MC_CWKDIS);
	DUMPCOWE(HDMI_COWE_MC_SWWSTZWEQ);
	DUMPCOWE(HDMI_COWE_MC_FWOWCTWW);
	DUMPCOWE(HDMI_COWE_MC_PHYWSTZ);
	DUMPCOWE(HDMI_COWE_MC_WOCKONCWOCK);

	DUMPCOWE(HDMI_COWE_I2CM_SWAVE);
	DUMPCOWE(HDMI_COWE_I2CM_ADDWESS);
	DUMPCOWE(HDMI_COWE_I2CM_DATAO);
	DUMPCOWE(HDMI_COWE_I2CM_DATAI);
	DUMPCOWE(HDMI_COWE_I2CM_OPEWATION);
	DUMPCOWE(HDMI_COWE_I2CM_INT);
	DUMPCOWE(HDMI_COWE_I2CM_CTWINT);
	DUMPCOWE(HDMI_COWE_I2CM_DIV);
	DUMPCOWE(HDMI_COWE_I2CM_SEGADDW);
	DUMPCOWE(HDMI_COWE_I2CM_SOFTWSTZ);
	DUMPCOWE(HDMI_COWE_I2CM_SEGPTW);
	DUMPCOWE(HDMI_COWE_I2CM_SS_SCW_HCNT_1_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_SS_SCW_HCNT_0_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_SS_SCW_WCNT_1_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_SS_SCW_WCNT_0_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_FS_SCW_HCNT_1_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_FS_SCW_HCNT_0_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_FS_SCW_WCNT_1_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_FS_SCW_WCNT_0_ADDW);
	DUMPCOWE(HDMI_COWE_I2CM_SDA_HOWD_ADDW);
}

static void hdmi_cowe_init(stwuct hdmi_cowe_vid_config *video_cfg,
			   const stwuct hdmi_config *cfg)
{
	DSSDBG("hdmi_cowe_init\n");

	video_cfg->v_fc_config.vm = cfg->vm;

	/* video cowe */
	video_cfg->data_enabwe_pow = 1; /* It is awways 1*/
	video_cfg->hbwank = cfg->vm.hfwont_powch +
			    cfg->vm.hback_powch + cfg->vm.hsync_wen;
	video_cfg->vbwank_osc = 0;
	video_cfg->vbwank = cfg->vm.vsync_wen + cfg->vm.vfwont_powch +
			    cfg->vm.vback_powch;
	video_cfg->v_fc_config.hdmi_dvi_mode = cfg->hdmi_dvi_mode;

	if (cfg->vm.fwags & DISPWAY_FWAGS_INTEWWACED) {
		/* set vbwank_osc if vbwank is fwactionaw */
		if (video_cfg->vbwank % 2 != 0)
			video_cfg->vbwank_osc = 1;

		video_cfg->v_fc_config.vm.vactive /= 2;
		video_cfg->vbwank /= 2;
		video_cfg->v_fc_config.vm.vfwont_powch /= 2;
		video_cfg->v_fc_config.vm.vsync_wen /= 2;
		video_cfg->v_fc_config.vm.vback_powch /= 2;
	}

	if (cfg->vm.fwags & DISPWAY_FWAGS_DOUBWECWK) {
		video_cfg->v_fc_config.vm.hactive *= 2;
		video_cfg->hbwank *= 2;
		video_cfg->v_fc_config.vm.hfwont_powch *= 2;
		video_cfg->v_fc_config.vm.hsync_wen *= 2;
		video_cfg->v_fc_config.vm.hback_powch *= 2;
	}
}

/* DSS_HDMI_COWE_VIDEO_CONFIG */
static void hdmi_cowe_video_config(stwuct hdmi_cowe_data *cowe,
			const stwuct hdmi_cowe_vid_config *cfg)
{
	void __iomem *base = cowe->base;
	const stwuct videomode *vm = &cfg->v_fc_config.vm;
	unsigned chaw w = 0;
	boow vsync_pow, hsync_pow;

	vsync_pow = !!(vm->fwags & DISPWAY_FWAGS_VSYNC_HIGH);
	hsync_pow = !!(vm->fwags & DISPWAY_FWAGS_HSYNC_HIGH);

	/* Set hsync, vsync and data-enabwe powawity  */
	w = hdmi_wead_weg(base, HDMI_COWE_FC_INVIDCONF);
	w = FWD_MOD(w, vsync_pow, 6, 6);
	w = FWD_MOD(w, hsync_pow, 5, 5);
	w = FWD_MOD(w, cfg->data_enabwe_pow, 4, 4);
	w = FWD_MOD(w, cfg->vbwank_osc, 1, 1);
	w = FWD_MOD(w, !!(vm->fwags & DISPWAY_FWAGS_INTEWWACED), 0, 0);
	hdmi_wwite_weg(base, HDMI_COWE_FC_INVIDCONF, w);

	/* set x wesowution */
	WEG_FWD_MOD(base, HDMI_COWE_FC_INHACTIV1, vm->hactive >> 8, 4, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_INHACTIV0, vm->hactive & 0xFF, 7, 0);

	/* set y wesowution */
	WEG_FWD_MOD(base, HDMI_COWE_FC_INVACTIV1, vm->vactive >> 8, 4, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_INVACTIV0, vm->vactive & 0xFF, 7, 0);

	/* set howizontaw bwanking pixews */
	WEG_FWD_MOD(base, HDMI_COWE_FC_INHBWANK1, cfg->hbwank >> 8, 4, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_INHBWANK0, cfg->hbwank & 0xFF, 7, 0);

	/* set vewtiaw bwanking pixews */
	WEG_FWD_MOD(base, HDMI_COWE_FC_INVBWANK, cfg->vbwank, 7, 0);

	/* set howizontaw sync offset */
	WEG_FWD_MOD(base, HDMI_COWE_FC_HSYNCINDEWAY1, vm->hfwont_powch >> 8,
		    4, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_HSYNCINDEWAY0, vm->hfwont_powch & 0xFF,
		    7, 0);

	/* set vewticaw sync offset */
	WEG_FWD_MOD(base, HDMI_COWE_FC_VSYNCINDEWAY, vm->vfwont_powch, 7, 0);

	/* set howizontaw sync puwse width */
	WEG_FWD_MOD(base, HDMI_COWE_FC_HSYNCINWIDTH1, (vm->hsync_wen >> 8),
		    1, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_HSYNCINWIDTH0, vm->hsync_wen & 0xFF,
		    7, 0);

	/*  set vewticaw sync puwse width */
	WEG_FWD_MOD(base, HDMI_COWE_FC_VSYNCINWIDTH, vm->vsync_wen, 5, 0);

	/* sewect DVI mode */
	WEG_FWD_MOD(base, HDMI_COWE_FC_INVIDCONF,
		    cfg->v_fc_config.hdmi_dvi_mode, 3, 3);

	if (vm->fwags & DISPWAY_FWAGS_DOUBWECWK)
		WEG_FWD_MOD(base, HDMI_COWE_FC_PWCONF, 2, 7, 4);
	ewse
		WEG_FWD_MOD(base, HDMI_COWE_FC_PWCONF, 1, 7, 4);
}

static void hdmi_cowe_config_video_packetizew(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;
	int cww_depth = 0;	/* 24 bit cowow depth */

	/* COWOW_DEPTH */
	WEG_FWD_MOD(base, HDMI_COWE_VP_PW_CD, cww_depth, 7, 4);
	/* BYPASS_EN */
	WEG_FWD_MOD(base, HDMI_COWE_VP_CONF, cww_depth ? 0 : 1, 6, 6);
	/* PP_EN */
	WEG_FWD_MOD(base, HDMI_COWE_VP_CONF, cww_depth ? 1 : 0, 5, 5);
	/* YCC422_EN */
	WEG_FWD_MOD(base, HDMI_COWE_VP_CONF, 0, 3, 3);
	/* PP_STUFFING */
	WEG_FWD_MOD(base, HDMI_COWE_VP_STUFF, cww_depth ? 1 : 0, 1, 1);
	/* YCC422_STUFFING */
	WEG_FWD_MOD(base, HDMI_COWE_VP_STUFF, 1, 2, 2);
	/* OUTPUT_SEWECTOW */
	WEG_FWD_MOD(base, HDMI_COWE_VP_CONF, cww_depth ? 0 : 2, 1, 0);
}

static void hdmi_cowe_config_video_sampwew(stwuct hdmi_cowe_data *cowe)
{
	int video_mapping = 1;	/* fow 24 bit cowow depth */

	/* VIDEO_MAPPING */
	WEG_FWD_MOD(cowe->base, HDMI_COWE_TX_INVID0, video_mapping, 4, 0);
}

static void hdmi_cowe_wwite_avi_infofwame(stwuct hdmi_cowe_data *cowe,
	stwuct hdmi_avi_infofwame *fwame)
{
	void __iomem *base = cowe->base;
	u8 data[HDMI_INFOFWAME_SIZE(AVI)];
	u8 *ptw;
	unsigned int y, a, b, s;
	unsigned int c, m, w;
	unsigned int itc, ec, q, sc;
	unsigned int vic;
	unsigned int yq, cn, pw;

	hdmi_avi_infofwame_pack(fwame, data, sizeof(data));

	pwint_hex_dump_debug("AVI: ", DUMP_PWEFIX_NONE, 16, 1, data,
		HDMI_INFOFWAME_SIZE(AVI), fawse);

	ptw = data + HDMI_INFOFWAME_HEADEW_SIZE;

	y = (ptw[0] >> 5) & 0x3;
	a = (ptw[0] >> 4) & 0x1;
	b = (ptw[0] >> 2) & 0x3;
	s = (ptw[0] >> 0) & 0x3;

	c = (ptw[1] >> 6) & 0x3;
	m = (ptw[1] >> 4) & 0x3;
	w = (ptw[1] >> 0) & 0xf;

	itc = (ptw[2] >> 7) & 0x1;
	ec = (ptw[2] >> 4) & 0x7;
	q = (ptw[2] >> 2) & 0x3;
	sc = (ptw[2] >> 0) & 0x3;

	vic = ptw[3];

	yq = (ptw[4] >> 6) & 0x3;
	cn = (ptw[4] >> 4) & 0x3;
	pw = (ptw[4] >> 0) & 0xf;

	hdmi_wwite_weg(base, HDMI_COWE_FC_AVICONF0,
		(a << 6) | (s << 4) | (b << 2) | (y << 0));

	hdmi_wwite_weg(base, HDMI_COWE_FC_AVICONF1,
		(c << 6) | (m << 4) | (w << 0));

	hdmi_wwite_weg(base, HDMI_COWE_FC_AVICONF2,
		(itc << 7) | (ec << 4) | (q << 2) | (sc << 0));

	hdmi_wwite_weg(base, HDMI_COWE_FC_AVIVID, vic);

	hdmi_wwite_weg(base, HDMI_COWE_FC_AVICONF3,
		(yq << 2) | (cn << 0));

	WEG_FWD_MOD(base, HDMI_COWE_FC_PWCONF, pw, 3, 0);
}

static void hdmi_cowe_wwite_csc(stwuct hdmi_cowe_data *cowe,
		const stwuct csc_tabwe *csc_coeff)
{
	void __iomem *base = cowe->base;

	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A1_MSB, csc_coeff->a1 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A1_WSB, csc_coeff->a1, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A2_MSB, csc_coeff->a2 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A2_WSB, csc_coeff->a2, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A3_MSB, csc_coeff->a3 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A3_WSB, csc_coeff->a3, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A4_MSB, csc_coeff->a4 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_A4_WSB, csc_coeff->a4, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B1_MSB, csc_coeff->b1 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B1_WSB, csc_coeff->b1, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B2_MSB, csc_coeff->b2 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B2_WSB, csc_coeff->b2, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B3_MSB, csc_coeff->b3 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B3_WSB, csc_coeff->b3, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B4_MSB, csc_coeff->b4 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_B4_WSB, csc_coeff->b4, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C1_MSB, csc_coeff->c1 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C1_WSB, csc_coeff->c1, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C2_MSB, csc_coeff->c2 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C2_WSB, csc_coeff->c2, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C3_MSB, csc_coeff->c3 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C3_WSB, csc_coeff->c3, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C4_MSB, csc_coeff->c4 >> 8, 6, 0);
	WEG_FWD_MOD(base, HDMI_COWE_CSC_COEF_C4_WSB, csc_coeff->c4, 7, 0);

	/* enabwe CSC */
	WEG_FWD_MOD(base, HDMI_COWE_MC_FWOWCTWW, 0x1, 0, 0);
}

static void hdmi_cowe_configuwe_wange(stwuct hdmi_cowe_data *cowe,
				      enum hdmi_quantization_wange wange)
{
	static const stwuct csc_tabwe csc_wimited_wange = {
		7036, 0, 0, 32, 0, 7036, 0, 32, 0, 0, 7036, 32
	};
	static const stwuct csc_tabwe csc_fuww_wange = {
		8192, 0, 0, 0, 0, 8192, 0, 0, 0, 0, 8192, 0
	};
	const stwuct csc_tabwe *csc_coeff;

	/* CSC_COWOWDEPTH  = 24 bits*/
	WEG_FWD_MOD(cowe->base, HDMI_COWE_CSC_SCAWE, 0, 7, 4);

	switch (wange) {
	case HDMI_QUANTIZATION_WANGE_FUWW:
		csc_coeff = &csc_fuww_wange;
		bweak;

	case HDMI_QUANTIZATION_WANGE_DEFAUWT:
	case HDMI_QUANTIZATION_WANGE_WIMITED:
	defauwt:
		csc_coeff = &csc_wimited_wange;
		bweak;
	}

	hdmi_cowe_wwite_csc(cowe, csc_coeff);
}

static void hdmi_cowe_enabwe_video_path(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;

	DSSDBG("hdmi_cowe_enabwe_video_path\n");

	WEG_FWD_MOD(base, HDMI_COWE_FC_CTWWDUW, 0x0C, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_EXCTWWDUW, 0x20, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_EXCTWWSPAC, 0x01, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_CH0PWEAM, 0x0B, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_CH1PWEAM, 0x16, 5, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_CH2PWEAM, 0x21, 5, 0);
	WEG_FWD_MOD(base, HDMI_COWE_MC_CWKDIS, 0x00, 0, 0);
	WEG_FWD_MOD(base, HDMI_COWE_MC_CWKDIS, 0x00, 1, 1);
}

static void hdmi_cowe_mask_intewwupts(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;

	/* Mastew IWQ mask */
	WEG_FWD_MOD(base, HDMI_COWE_IH_MUTE, 0x3, 1, 0);

	/* Mask aww the intewwupts in HDMI cowe */

	WEG_FWD_MOD(base, HDMI_COWE_VP_MASK, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_MASK0, 0xe7, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_MASK1, 0xfb, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_MASK2, 0x3, 1, 0);

	WEG_FWD_MOD(base, HDMI_COWE_AUD_INT, 0x3, 3, 2);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_MASK, 0x3, 1, 0);

	WEG_FWD_MOD(base, HDMI_COWE_CEC_MASK, 0x7f, 6, 0);

	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 6, 6);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_CTWINT, 0x1, 2, 2);
	WEG_FWD_MOD(base, HDMI_COWE_I2CM_INT, 0x1, 2, 2);

	WEG_FWD_MOD(base, HDMI_COWE_PHY_MASK0, 0xf3, 7, 0);

	WEG_FWD_MOD(base, HDMI_COWE_IH_PHY_STAT0, 0xff, 7, 0);

	/* Cweaw aww the cuwwent intewwupt bits */

	WEG_FWD_MOD(base, HDMI_COWE_IH_VP_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT0, 0xe7, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT1, 0xfb, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT2, 0x3, 1, 0);

	WEG_FWD_MOD(base, HDMI_COWE_IH_AS_STAT0, 0x7, 2, 0);

	WEG_FWD_MOD(base, HDMI_COWE_IH_CEC_STAT0, 0x7f, 6, 0);

	WEG_FWD_MOD(base, HDMI_COWE_IH_I2CM_STAT0, 0x3, 1, 0);

	WEG_FWD_MOD(base, HDMI_COWE_IH_PHY_STAT0, 0xff, 7, 0);
}

static void hdmi_cowe_enabwe_intewwupts(stwuct hdmi_cowe_data *cowe)
{
	/* Unmute intewwupts */
	WEG_FWD_MOD(cowe->base, HDMI_COWE_IH_MUTE, 0x0, 1, 0);
}

int hdmi5_cowe_handwe_iwqs(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;

	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT1, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_FC_STAT2, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_AS_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_PHY_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_I2CM_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_CEC_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_VP_STAT0, 0xff, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_IH_I2CMPHY_STAT0, 0xff, 7, 0);

	wetuwn 0;
}

void hdmi5_configuwe(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp,
		stwuct hdmi_config *cfg)
{
	stwuct videomode vm;
	stwuct hdmi_video_fowmat video_fowmat;
	stwuct hdmi_cowe_vid_config v_cowe_cfg;
	enum hdmi_quantization_wange wange;

	hdmi_cowe_mask_intewwupts(cowe);

	if (cfg->hdmi_dvi_mode == HDMI_HDMI) {
		chaw vic = cfg->infofwame.video_code;

		/* Aww CEA modes othew than VIC 1 use wimited quantization wange. */
		wange = vic > 1 ? HDMI_QUANTIZATION_WANGE_WIMITED :
			HDMI_QUANTIZATION_WANGE_FUWW;
	} ewse {
		wange = HDMI_QUANTIZATION_WANGE_FUWW;
	}

	hdmi_cowe_init(&v_cowe_cfg, cfg);

	hdmi_wp_init_vid_fmt_timings(&video_fowmat, &vm, cfg);

	hdmi_wp_video_config_timing(wp, &vm);

	/* video config */
	video_fowmat.packing_mode = HDMI_PACK_24b_WGB_YUV444_YUV422;

	hdmi_wp_video_config_fowmat(wp, &video_fowmat);

	hdmi_wp_video_config_intewface(wp, &vm);

	hdmi_cowe_configuwe_wange(cowe, wange);
	cfg->infofwame.quantization_wange = wange;

	/*
	 * configuwe cowe video pawt, set softwawe weset in the cowe
	 */
	v_cowe_cfg.packet_mode = HDMI_PACKETMODE24BITPEWPIXEW;

	hdmi_cowe_video_config(cowe, &v_cowe_cfg);

	hdmi_cowe_config_video_packetizew(cowe);
	hdmi_cowe_config_video_sampwew(cowe);

	if (cfg->hdmi_dvi_mode == HDMI_HDMI)
		hdmi_cowe_wwite_avi_infofwame(cowe, &cfg->infofwame);

	hdmi_cowe_enabwe_video_path(cowe);

	hdmi_cowe_enabwe_intewwupts(cowe);
}

static void hdmi5_cowe_audio_config(stwuct hdmi_cowe_data *cowe,
			stwuct hdmi_cowe_audio_config *cfg)
{
	void __iomem *base = cowe->base;
	u8 vaw;

	/* Mute audio befowe configuwing */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCONF, 0xf, 7, 4);

	/* Set the N pawametew */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_N1, cfg->n, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_N2, cfg->n >> 8, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_N3, cfg->n >> 16, 3, 0);

	/*
	 * CTS manuaw mode. Automatic mode is not suppowted when using audio
	 * pawawwew intewface.
	 */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_CTS3, 1, 4, 4);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_CTS1, cfg->cts, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_CTS2, cfg->cts >> 8, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_AUD_CTS3, cfg->cts >> 16, 3, 0);

	/* Wayout of Audio Sampwe Packets: 2-channew ow muwtichannews */
	if (cfg->wayout == HDMI_AUDIO_WAYOUT_2CH)
		WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCONF, 0, 0, 0);
	ewse
		WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCONF, 1, 0, 0);

	/* Configuwe IEC-609580 Vawidity bits */
	/* Channew 0 is vawid */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, 0, 0, 0);
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, 0, 4, 4);

	if (cfg->wayout == HDMI_AUDIO_WAYOUT_2CH)
		vaw = 1;
	ewse
		vaw = 0;

	/* Channews 1, 2 setting */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 1, 1);
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 5, 5);
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 2, 2);
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 6, 6);
	/* Channew 3 setting */
	if (cfg->wayout == HDMI_AUDIO_WAYOUT_6CH)
		vaw = 1;
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 3, 3);
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSV, vaw, 7, 7);

	/* Configuwe IEC-60958 Usew bits */
	/* TODO: shouwd be set by usew. */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSU, 0, 7, 0);

	/* Configuwe IEC-60958 Channew Status wowd */
	/* CGMSA */
	vaw = cfg->iec60958_cfg->status[5] & IEC958_AES5_CON_CGMSA;
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(0), vaw, 5, 4);

	/* Copywight */
	vaw = (cfg->iec60958_cfg->status[0] &
			IEC958_AES0_CON_NOT_COPYWIGHT) >> 2;
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(0), vaw, 0, 0);

	/* Categowy */
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDSCHNWS(1),
		cfg->iec60958_cfg->status[1]);

	/* PCM audio mode */
	vaw = (cfg->iec60958_cfg->status[0] & IEC958_AES0_CON_MODE) >> 6;
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(2), vaw, 6, 4);

	/* Souwce numbew */
	vaw = cfg->iec60958_cfg->status[2] & IEC958_AES2_CON_SOUWCE;
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(2), vaw, 3, 0);

	/* Channew numbew wight 0  */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(3), 2, 3, 0);
	/* Channew numbew wight 1*/
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(3), 4, 7, 4);
	/* Channew numbew wight 2  */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(4), 6, 3, 0);
	/* Channew numbew wight 3*/
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(4), 8, 7, 4);
	/* Channew numbew weft 0  */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(5), 1, 3, 0);
	/* Channew numbew weft 1*/
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(5), 3, 7, 4);
	/* Channew numbew weft 2  */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(6), 5, 3, 0);
	/* Channew numbew weft 3*/
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCHNWS(6), 7, 7, 4);

	/* Cwock accuwacy and sampwe wate */
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDSCHNWS(7),
		cfg->iec60958_cfg->status[3]);

	/* Owiginaw sampwe wate and wowd wength */
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDSCHNWS(8),
		cfg->iec60958_cfg->status[4]);

	/* Enabwe FIFO empty and fuww intewwupts */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_INT, 3, 3, 2);

	/* Configuwe GPA */
	/* sewect HBW/SPDIF intewfaces */
	if (cfg->wayout == HDMI_AUDIO_WAYOUT_2CH) {
		/* sewect HBW/SPDIF intewfaces */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_CONF0, 0, 5, 5);
		/* enabwe two channews in GPA */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_CONF1, 3, 7, 0);
	} ewse if (cfg->wayout == HDMI_AUDIO_WAYOUT_6CH) {
		/* sewect HBW/SPDIF intewfaces */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_CONF0, 0, 5, 5);
		/* enabwe six channews in GPA */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_CONF1, 0x3F, 7, 0);
	} ewse {
		/* sewect HBW/SPDIF intewfaces */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_CONF0, 0, 5, 5);
		/* enabwe eight channews in GPA */
		WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_CONF1, 0xFF, 7, 0);
	}

	/* disabwe HBW */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_CONF2, 0, 0, 0);
	/* enabwe PCUV */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_CONF2, 1, 1, 1);
	/* enabwe GPA FIFO fuww and empty mask */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_MASK, 3, 1, 0);
	/* set powawity of GPA FIFO empty intewwupts */
	WEG_FWD_MOD(base, HDMI_COWE_AUD_GP_POW, 1, 0, 0);

	/* unmute audio */
	WEG_FWD_MOD(base, HDMI_COWE_FC_AUDSCONF, 0, 7, 4);
}

static void hdmi5_cowe_audio_infofwame_cfg(stwuct hdmi_cowe_data *cowe,
	 stwuct snd_cea_861_aud_if *info_aud)
{
	void __iomem *base = cowe->base;

	/* channew count and coding type fiewds in AUDICONF0 awe swapped */
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDICONF0,
		(info_aud->db1_ct_cc & CEA861_AUDIO_INFOFWAME_DB1CC) << 4 |
		(info_aud->db1_ct_cc & CEA861_AUDIO_INFOFWAME_DB1CT) >> 4);

	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDICONF1, info_aud->db2_sf_ss);
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDICONF2, info_aud->db4_ca);
	hdmi_wwite_weg(base, HDMI_COWE_FC_AUDICONF3,
	  (info_aud->db5_dminh_wsv & CEA861_AUDIO_INFOFWAME_DB5_DM_INH) >> 3 |
	  (info_aud->db5_dminh_wsv & CEA861_AUDIO_INFOFWAME_DB5_WSV));
}

int hdmi5_audio_config(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp,
			stwuct omap_dss_audio *audio, u32 pcwk)
{
	stwuct hdmi_audio_fowmat audio_fowmat;
	stwuct hdmi_audio_dma audio_dma;
	stwuct hdmi_cowe_audio_config cowe_cfg;
	int n, cts, channew_count;
	unsigned int fs_nw;
	boow wowd_wength_16b = fawse;

	if (!audio || !audio->iec || !audio->cea || !cowe)
		wetuwn -EINVAW;

	cowe_cfg.iec60958_cfg = audio->iec;

	if (!(audio->iec->status[4] & IEC958_AES4_CON_MAX_WOWDWEN_24) &&
		(audio->iec->status[4] & IEC958_AES4_CON_WOWDWEN_20_16))
			wowd_wength_16b = twue;

	/* onwy 16-bit wowd wength suppowted atm */
	if (!wowd_wength_16b)
		wetuwn -EINVAW;

	switch (audio->iec->status[3] & IEC958_AES3_CON_FS) {
	case IEC958_AES3_CON_FS_32000:
		fs_nw = 32000;
		bweak;
	case IEC958_AES3_CON_FS_44100:
		fs_nw = 44100;
		bweak;
	case IEC958_AES3_CON_FS_48000:
		fs_nw = 48000;
		bweak;
	case IEC958_AES3_CON_FS_88200:
		fs_nw = 88200;
		bweak;
	case IEC958_AES3_CON_FS_96000:
		fs_nw = 96000;
		bweak;
	case IEC958_AES3_CON_FS_176400:
		fs_nw = 176400;
		bweak;
	case IEC958_AES3_CON_FS_192000:
		fs_nw = 192000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hdmi_compute_acw(pcwk, fs_nw, &n, &cts);
	cowe_cfg.n = n;
	cowe_cfg.cts = cts;

	/* Audio channews settings */
	channew_count = (audio->cea->db1_ct_cc & CEA861_AUDIO_INFOFWAME_DB1CC)
				+ 1;

	if (channew_count == 2)
		cowe_cfg.wayout = HDMI_AUDIO_WAYOUT_2CH;
	ewse if (channew_count == 6)
		cowe_cfg.wayout = HDMI_AUDIO_WAYOUT_6CH;
	ewse
		cowe_cfg.wayout = HDMI_AUDIO_WAYOUT_8CH;

	/* DMA settings */
	if (wowd_wength_16b)
		audio_dma.twansfew_size = 0x10;
	ewse
		audio_dma.twansfew_size = 0x20;
	audio_dma.bwock_size = 0xC0;
	audio_dma.mode = HDMI_AUDIO_TWANSF_DMA;
	audio_dma.fifo_thweshowd = 0x20; /* in numbew of sampwes */

	/* audio FIFO fowmat settings fow 16-bit sampwes*/
	audio_fowmat.sampwes_pew_wowd = HDMI_AUDIO_ONEWOWD_TWOSAMPWES;
	audio_fowmat.sampwe_size = HDMI_AUDIO_SAMPWE_16BITS;
	audio_fowmat.justification = HDMI_AUDIO_JUSTIFY_WEFT;
	audio_fowmat.sampwe_owdew = HDMI_AUDIO_SAMPWE_WEFT_FIWST;

	/* onwy WPCM atm */
	audio_fowmat.type = HDMI_AUDIO_TYPE_WPCM;

	/* onwy awwowed option */
	audio_fowmat.sampwe_owdew = HDMI_AUDIO_SAMPWE_WEFT_FIWST;

	/* disabwe stawt/stop signaws of IEC 60958 bwocks */
	audio_fowmat.en_sig_bwk_stwt_end = HDMI_AUDIO_BWOCK_SIG_STAWTEND_ON;

	/* configuwe DMA and audio FIFO fowmat*/
	hdmi_wp_audio_config_dma(wp, &audio_dma);
	hdmi_wp_audio_config_fowmat(wp, &audio_fowmat);

	/* configuwe the cowe */
	hdmi5_cowe_audio_config(cowe, &cowe_cfg);

	/* configuwe CEA 861 audio infofwame */
	hdmi5_cowe_audio_infofwame_cfg(cowe, audio->cea);

	wetuwn 0;
}

int hdmi5_cowe_init(stwuct pwatfowm_device *pdev, stwuct hdmi_cowe_data *cowe)
{
	cowe->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cowe");
	if (IS_EWW(cowe->base))
		wetuwn PTW_EWW(cowe->base);

	wetuwn 0;
}
