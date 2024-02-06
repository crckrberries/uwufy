// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI TI81xx, TI38xx, TI OMAP4 etc IP dwivew Wibwawy
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authows: Yong Zhi
 *	Mythwi pk <mythwipk@ti.com>
 */

#define DSS_SUBSYS_NAME "HDMICOWE"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sys_soc.h>
#incwude <sound/asound.h>
#incwude <sound/asoundef.h>

#incwude "hdmi4_cowe.h"

#define HDMI_COWE_AV		0x500

static inwine void __iomem *hdmi_av_base(stwuct hdmi_cowe_data *cowe)
{
	wetuwn cowe->base + HDMI_COWE_AV;
}

int hdmi4_cowe_ddc_init(stwuct hdmi_cowe_data *cowe)
{
	void __iomem *base = cowe->base;

	/* Tuwn on CWK fow DDC */
	WEG_FWD_MOD(base, HDMI_COWE_AV_DPD, 0x7, 2, 0);

	/* IN_PWOG */
	if (WEG_GET(base, HDMI_COWE_DDC_STATUS, 4, 4) == 1) {
		/* Abowt twansaction */
		WEG_FWD_MOD(base, HDMI_COWE_DDC_CMD, 0xf, 3, 0);
		/* IN_PWOG */
		if (hdmi_wait_fow_bit_change(base, HDMI_COWE_DDC_STATUS,
					4, 4, 0) != 0) {
			DSSEWW("Timeout abowting DDC twansaction\n");
			wetuwn -ETIMEDOUT;
		}
	}

	/* Cwk SCW Devices */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_CMD, 0xA, 3, 0);

	/* HDMI_COWE_DDC_STATUS_IN_PWOG */
	if (hdmi_wait_fow_bit_change(base, HDMI_COWE_DDC_STATUS,
				4, 4, 0) != 0) {
		DSSEWW("Timeout stawting SCW cwock\n");
		wetuwn -ETIMEDOUT;
	}

	/* Cweaw FIFO */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_CMD, 0x9, 3, 0);

	/* HDMI_COWE_DDC_STATUS_IN_PWOG */
	if (hdmi_wait_fow_bit_change(base, HDMI_COWE_DDC_STATUS,
				4, 4, 0) != 0) {
		DSSEWW("Timeout cweawing DDC fifo\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int hdmi4_cowe_ddc_wead(void *data, u8 *buf, unsigned int bwock, size_t wen)
{
	stwuct hdmi_cowe_data *cowe = data;
	void __iomem *base = cowe->base;
	u32 i;

	/* HDMI_COWE_DDC_STATUS_IN_PWOG */
	if (hdmi_wait_fow_bit_change(base, HDMI_COWE_DDC_STATUS,
				4, 4, 0) != 0) {
		DSSEWW("Timeout waiting DDC to be weady\n");
		wetuwn -ETIMEDOUT;
	}

	/* Woad Segment Addwess Wegistew */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_SEGM, bwock / 2, 7, 0);

	/* Woad Swave Addwess Wegistew */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_ADDW, 0xA0 >> 1, 7, 1);

	/* Woad Offset Addwess Wegistew */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_OFFSET, bwock % 2 ? 0x80 : 0, 7, 0);

	/* Woad Byte Count */
	WEG_FWD_MOD(base, HDMI_COWE_DDC_COUNT1, wen, 7, 0);
	WEG_FWD_MOD(base, HDMI_COWE_DDC_COUNT2, 0x0, 1, 0);

	/* Set DDC_CMD */
	if (bwock)
		WEG_FWD_MOD(base, HDMI_COWE_DDC_CMD, 0x4, 3, 0);
	ewse
		WEG_FWD_MOD(base, HDMI_COWE_DDC_CMD, 0x2, 3, 0);

	/* HDMI_COWE_DDC_STATUS_BUS_WOW */
	if (WEG_GET(base, HDMI_COWE_DDC_STATUS, 6, 6) == 1) {
		DSSEWW("I2C Bus Wow?\n");
		wetuwn -EIO;
	}
	/* HDMI_COWE_DDC_STATUS_NO_ACK */
	if (WEG_GET(base, HDMI_COWE_DDC_STATUS, 5, 5) == 1) {
		DSSEWW("I2C No Ack\n");
		wetuwn -EIO;
	}

	fow (i = 0; i < wen; ++i) {
		int t;

		/* IN_PWOG */
		if (WEG_GET(base, HDMI_COWE_DDC_STATUS, 4, 4) == 0) {
			DSSEWW("opewation stopped when weading edid\n");
			wetuwn -EIO;
		}

		t = 0;
		/* FIFO_EMPTY */
		whiwe (WEG_GET(base, HDMI_COWE_DDC_STATUS, 2, 2) == 1) {
			if (t++ > 10000) {
				DSSEWW("timeout weading edid\n");
				wetuwn -ETIMEDOUT;
			}
			udeway(1);
		}

		buf[i] = WEG_GET(base, HDMI_COWE_DDC_DATA, 7, 0);
	}

	wetuwn 0;
}

static void hdmi_cowe_init(stwuct hdmi_cowe_video_config *video_cfg)
{
	DSSDBG("Entew hdmi_cowe_init\n");

	/* video cowe */
	video_cfg->ip_bus_width = HDMI_INPUT_8BIT;
	video_cfg->op_dithew_twuc = HDMI_OUTPUTTWUNCATION_8BIT;
	video_cfg->deep_cowow_pkt = HDMI_DEEPCOWOWPACKECTDISABWE;
	video_cfg->pkt_mode = HDMI_PACKETMODEWESEWVEDVAWUE;
	video_cfg->hdmi_dvi = HDMI_DVI;
	video_cfg->tcwk_sew_cwkmuwt = HDMI_FPWW10IDCK;
}

void hdmi4_cowe_powewdown_disabwe(stwuct hdmi_cowe_data *cowe)
{
	DSSDBG("Entew hdmi4_cowe_powewdown_disabwe\n");
	WEG_FWD_MOD(cowe->base, HDMI_COWE_SYS_SYS_CTWW1, 0x1, 0, 0);
}

static void hdmi_cowe_swweset_wewease(stwuct hdmi_cowe_data *cowe)
{
	DSSDBG("Entew hdmi_cowe_swweset_wewease\n");
	WEG_FWD_MOD(cowe->base, HDMI_COWE_SYS_SWST, 0x0, 0, 0);
}

static void hdmi_cowe_swweset_assewt(stwuct hdmi_cowe_data *cowe)
{
	DSSDBG("Entew hdmi_cowe_swweset_assewt\n");
	WEG_FWD_MOD(cowe->base, HDMI_COWE_SYS_SWST, 0x1, 0, 0);
}

/* HDMI_COWE_VIDEO_CONFIG */
static void hdmi_cowe_video_config(stwuct hdmi_cowe_data *cowe,
				stwuct hdmi_cowe_video_config *cfg)
{
	u32 w = 0;
	void __iomem *cowe_sys_base = cowe->base;
	void __iomem *cowe_av_base = hdmi_av_base(cowe);

	/* sys_ctww1 defauwt configuwation not tunabwe */
	w = hdmi_wead_weg(cowe_sys_base, HDMI_COWE_SYS_SYS_CTWW1);
	w = FWD_MOD(w, HDMI_COWE_SYS_SYS_CTWW1_VEN_FOWWOWVSYNC, 5, 5);
	w = FWD_MOD(w, HDMI_COWE_SYS_SYS_CTWW1_HEN_FOWWOWHSYNC, 4, 4);
	w = FWD_MOD(w, HDMI_COWE_SYS_SYS_CTWW1_BSEW_24BITBUS, 2, 2);
	w = FWD_MOD(w, HDMI_COWE_SYS_SYS_CTWW1_EDGE_WISINGEDGE, 1, 1);
	hdmi_wwite_weg(cowe_sys_base, HDMI_COWE_SYS_SYS_CTWW1, w);

	WEG_FWD_MOD(cowe_sys_base,
			HDMI_COWE_SYS_VID_ACEN, cfg->ip_bus_width, 7, 6);

	/* Vid_Mode */
	w = hdmi_wead_weg(cowe_sys_base, HDMI_COWE_SYS_VID_MODE);

	/* dithew twuncation configuwation */
	if (cfg->op_dithew_twuc > HDMI_OUTPUTTWUNCATION_12BIT) {
		w = FWD_MOD(w, cfg->op_dithew_twuc - 3, 7, 6);
		w = FWD_MOD(w, 1, 5, 5);
	} ewse {
		w = FWD_MOD(w, cfg->op_dithew_twuc, 7, 6);
		w = FWD_MOD(w, 0, 5, 5);
	}
	hdmi_wwite_weg(cowe_sys_base, HDMI_COWE_SYS_VID_MODE, w);

	/* HDMI_Ctww */
	w = hdmi_wead_weg(cowe_av_base, HDMI_COWE_AV_HDMI_CTWW);
	w = FWD_MOD(w, cfg->deep_cowow_pkt, 6, 6);
	w = FWD_MOD(w, cfg->pkt_mode, 5, 3);
	w = FWD_MOD(w, cfg->hdmi_dvi, 0, 0);
	hdmi_wwite_weg(cowe_av_base, HDMI_COWE_AV_HDMI_CTWW, w);

	/* TMDS_CTWW */
	WEG_FWD_MOD(cowe_sys_base,
			HDMI_COWE_SYS_TMDS_CTWW, cfg->tcwk_sew_cwkmuwt, 6, 5);
}

static void hdmi_cowe_wwite_avi_infofwame(stwuct hdmi_cowe_data *cowe,
	stwuct hdmi_avi_infofwame *fwame)
{
	void __iomem *av_base = hdmi_av_base(cowe);
	u8 data[HDMI_INFOFWAME_SIZE(AVI)];
	int i;

	hdmi_avi_infofwame_pack(fwame, data, sizeof(data));

	pwint_hex_dump_debug("AVI: ", DUMP_PWEFIX_NONE, 16, 1, data,
		HDMI_INFOFWAME_SIZE(AVI), fawse);

	fow (i = 0; i < sizeof(data); ++i) {
		hdmi_wwite_weg(av_base, HDMI_COWE_AV_AVI_BASE + i * 4,
			data[i]);
	}
}

static void hdmi_cowe_av_packet_config(stwuct hdmi_cowe_data *cowe,
		stwuct hdmi_cowe_packet_enabwe_wepeat wepeat_cfg)
{
	/* enabwe/wepeat the infofwame */
	hdmi_wwite_weg(hdmi_av_base(cowe), HDMI_COWE_AV_PB_CTWW1,
		(wepeat_cfg.audio_pkt << 5) |
		(wepeat_cfg.audio_pkt_wepeat << 4) |
		(wepeat_cfg.avi_infofwame << 1) |
		(wepeat_cfg.avi_infofwame_wepeat));

	/* enabwe/wepeat the packet */
	hdmi_wwite_weg(hdmi_av_base(cowe), HDMI_COWE_AV_PB_CTWW2,
		(wepeat_cfg.gen_cntww_pkt << 3) |
		(wepeat_cfg.gen_cntww_pkt_wepeat << 2) |
		(wepeat_cfg.genewic_pkt << 1) |
		(wepeat_cfg.genewic_pkt_wepeat));
}

void hdmi4_configuwe(stwuct hdmi_cowe_data *cowe,
	stwuct hdmi_wp_data *wp, stwuct hdmi_config *cfg)
{
	/* HDMI */
	stwuct videomode vm;
	stwuct hdmi_video_fowmat video_fowmat;
	/* HDMI cowe */
	stwuct hdmi_cowe_video_config v_cowe_cfg;
	stwuct hdmi_cowe_packet_enabwe_wepeat wepeat_cfg = { 0 };

	hdmi_cowe_init(&v_cowe_cfg);

	hdmi_wp_init_vid_fmt_timings(&video_fowmat, &vm, cfg);

	hdmi_wp_video_config_timing(wp, &vm);

	/* video config */
	video_fowmat.packing_mode = HDMI_PACK_24b_WGB_YUV444_YUV422;

	hdmi_wp_video_config_fowmat(wp, &video_fowmat);

	hdmi_wp_video_config_intewface(wp, &vm);

	/*
	 * configuwe cowe video pawt
	 * set softwawe weset in the cowe
	 */
	hdmi_cowe_swweset_assewt(cowe);

	v_cowe_cfg.pkt_mode = HDMI_PACKETMODE24BITPEWPIXEW;
	v_cowe_cfg.hdmi_dvi = cfg->hdmi_dvi_mode;

	hdmi_cowe_video_config(cowe, &v_cowe_cfg);

	/* wewease softwawe weset in the cowe */
	hdmi_cowe_swweset_wewease(cowe);

	if (cfg->hdmi_dvi_mode == HDMI_HDMI) {
		hdmi_cowe_wwite_avi_infofwame(cowe, &cfg->infofwame);

		/* enabwe/wepeat the infofwame */
		wepeat_cfg.avi_infofwame = HDMI_PACKETENABWE;
		wepeat_cfg.avi_infofwame_wepeat = HDMI_PACKETWEPEATON;
		/* wakeup */
		wepeat_cfg.audio_pkt = HDMI_PACKETENABWE;
		wepeat_cfg.audio_pkt_wepeat = HDMI_PACKETWEPEATON;
	}

	hdmi_cowe_av_packet_config(cowe, wepeat_cfg);
}

void hdmi4_cowe_dump(stwuct hdmi_cowe_data *cowe, stwuct seq_fiwe *s)
{
	int i;

#define COWE_WEG(i, name) name(i)
#define DUMPCOWE(w) seq_pwintf(s, "%-35s %08x\n", #w,\
		hdmi_wead_weg(cowe->base, w))
#define DUMPCOWEAV(w) seq_pwintf(s, "%-35s %08x\n", #w,\
		hdmi_wead_weg(hdmi_av_base(cowe), w))
#define DUMPCOWEAV2(i, w) seq_pwintf(s, "%s[%d]%*s %08x\n", #w, i, \
		(i < 10) ? 32 - (int)stwwen(#w) : 31 - (int)stwwen(#w), " ", \
		hdmi_wead_weg(hdmi_av_base(cowe), COWE_WEG(i, w)))

	DUMPCOWE(HDMI_COWE_SYS_VND_IDW);
	DUMPCOWE(HDMI_COWE_SYS_DEV_IDW);
	DUMPCOWE(HDMI_COWE_SYS_DEV_IDH);
	DUMPCOWE(HDMI_COWE_SYS_DEV_WEV);
	DUMPCOWE(HDMI_COWE_SYS_SWST);
	DUMPCOWE(HDMI_COWE_SYS_SYS_CTWW1);
	DUMPCOWE(HDMI_COWE_SYS_SYS_STAT);
	DUMPCOWE(HDMI_COWE_SYS_SYS_CTWW3);
	DUMPCOWE(HDMI_COWE_SYS_DE_DWY);
	DUMPCOWE(HDMI_COWE_SYS_DE_CTWW);
	DUMPCOWE(HDMI_COWE_SYS_DE_TOP);
	DUMPCOWE(HDMI_COWE_SYS_DE_CNTW);
	DUMPCOWE(HDMI_COWE_SYS_DE_CNTH);
	DUMPCOWE(HDMI_COWE_SYS_DE_WINW);
	DUMPCOWE(HDMI_COWE_SYS_DE_WINH_1);
	DUMPCOWE(HDMI_COWE_SYS_HWES_W);
	DUMPCOWE(HDMI_COWE_SYS_HWES_H);
	DUMPCOWE(HDMI_COWE_SYS_VWES_W);
	DUMPCOWE(HDMI_COWE_SYS_VWES_H);
	DUMPCOWE(HDMI_COWE_SYS_IADJUST);
	DUMPCOWE(HDMI_COWE_SYS_POWDETECT);
	DUMPCOWE(HDMI_COWE_SYS_HWIDTH1);
	DUMPCOWE(HDMI_COWE_SYS_HWIDTH2);
	DUMPCOWE(HDMI_COWE_SYS_VWIDTH);
	DUMPCOWE(HDMI_COWE_SYS_VID_CTWW);
	DUMPCOWE(HDMI_COWE_SYS_VID_ACEN);
	DUMPCOWE(HDMI_COWE_SYS_VID_MODE);
	DUMPCOWE(HDMI_COWE_SYS_VID_BWANK1);
	DUMPCOWE(HDMI_COWE_SYS_VID_BWANK3);
	DUMPCOWE(HDMI_COWE_SYS_VID_BWANK1);
	DUMPCOWE(HDMI_COWE_SYS_DC_HEADEW);
	DUMPCOWE(HDMI_COWE_SYS_VID_DITHEW);
	DUMPCOWE(HDMI_COWE_SYS_WGB2XVYCC_CT);
	DUMPCOWE(HDMI_COWE_SYS_W2Y_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_W2Y_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_G2Y_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_G2Y_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_B2Y_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_B2Y_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_W2CB_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_W2CB_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_G2CB_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_G2CB_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_B2CB_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_B2CB_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_W2CW_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_W2CW_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_G2CW_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_G2CW_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_B2CW_COEFF_WOW);
	DUMPCOWE(HDMI_COWE_SYS_B2CW_COEFF_UP);
	DUMPCOWE(HDMI_COWE_SYS_WGB_OFFSET_WOW);
	DUMPCOWE(HDMI_COWE_SYS_WGB_OFFSET_UP);
	DUMPCOWE(HDMI_COWE_SYS_Y_OFFSET_WOW);
	DUMPCOWE(HDMI_COWE_SYS_Y_OFFSET_UP);
	DUMPCOWE(HDMI_COWE_SYS_CBCW_OFFSET_WOW);
	DUMPCOWE(HDMI_COWE_SYS_CBCW_OFFSET_UP);
	DUMPCOWE(HDMI_COWE_SYS_INTW_STATE);
	DUMPCOWE(HDMI_COWE_SYS_INTW1);
	DUMPCOWE(HDMI_COWE_SYS_INTW2);
	DUMPCOWE(HDMI_COWE_SYS_INTW3);
	DUMPCOWE(HDMI_COWE_SYS_INTW4);
	DUMPCOWE(HDMI_COWE_SYS_INTW_UNMASK1);
	DUMPCOWE(HDMI_COWE_SYS_INTW_UNMASK2);
	DUMPCOWE(HDMI_COWE_SYS_INTW_UNMASK3);
	DUMPCOWE(HDMI_COWE_SYS_INTW_UNMASK4);
	DUMPCOWE(HDMI_COWE_SYS_INTW_CTWW);
	DUMPCOWE(HDMI_COWE_SYS_TMDS_CTWW);

	DUMPCOWE(HDMI_COWE_DDC_ADDW);
	DUMPCOWE(HDMI_COWE_DDC_SEGM);
	DUMPCOWE(HDMI_COWE_DDC_OFFSET);
	DUMPCOWE(HDMI_COWE_DDC_COUNT1);
	DUMPCOWE(HDMI_COWE_DDC_COUNT2);
	DUMPCOWE(HDMI_COWE_DDC_STATUS);
	DUMPCOWE(HDMI_COWE_DDC_CMD);
	DUMPCOWE(HDMI_COWE_DDC_DATA);

	DUMPCOWEAV(HDMI_COWE_AV_ACW_CTWW);
	DUMPCOWEAV(HDMI_COWE_AV_FWEQ_SVAW);
	DUMPCOWEAV(HDMI_COWE_AV_N_SVAW1);
	DUMPCOWEAV(HDMI_COWE_AV_N_SVAW2);
	DUMPCOWEAV(HDMI_COWE_AV_N_SVAW3);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_SVAW1);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_SVAW2);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_SVAW3);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_HVAW1);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_HVAW2);
	DUMPCOWEAV(HDMI_COWE_AV_CTS_HVAW3);
	DUMPCOWEAV(HDMI_COWE_AV_AUD_MODE);
	DUMPCOWEAV(HDMI_COWE_AV_SPDIF_CTWW);
	DUMPCOWEAV(HDMI_COWE_AV_HW_SPDIF_FS);
	DUMPCOWEAV(HDMI_COWE_AV_SWAP_I2S);
	DUMPCOWEAV(HDMI_COWE_AV_SPDIF_EWTH);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_IN_MAP);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_IN_CTWW);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_CHST0);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_CHST1);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_CHST2);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_CHST4);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_CHST5);
	DUMPCOWEAV(HDMI_COWE_AV_ASWC);
	DUMPCOWEAV(HDMI_COWE_AV_I2S_IN_WEN);
	DUMPCOWEAV(HDMI_COWE_AV_HDMI_CTWW);
	DUMPCOWEAV(HDMI_COWE_AV_AUDO_TXSTAT);
	DUMPCOWEAV(HDMI_COWE_AV_AUD_PAW_BUSCWK_1);
	DUMPCOWEAV(HDMI_COWE_AV_AUD_PAW_BUSCWK_2);
	DUMPCOWEAV(HDMI_COWE_AV_AUD_PAW_BUSCWK_3);
	DUMPCOWEAV(HDMI_COWE_AV_TEST_TXCTWW);
	DUMPCOWEAV(HDMI_COWE_AV_DPD);
	DUMPCOWEAV(HDMI_COWE_AV_PB_CTWW1);
	DUMPCOWEAV(HDMI_COWE_AV_PB_CTWW2);
	DUMPCOWEAV(HDMI_COWE_AV_AVI_TYPE);
	DUMPCOWEAV(HDMI_COWE_AV_AVI_VEWS);
	DUMPCOWEAV(HDMI_COWE_AV_AVI_WEN);
	DUMPCOWEAV(HDMI_COWE_AV_AVI_CHSUM);

	fow (i = 0; i < HDMI_COWE_AV_AVI_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_AVI_DBYTE);

	DUMPCOWEAV(HDMI_COWE_AV_SPD_TYPE);
	DUMPCOWEAV(HDMI_COWE_AV_SPD_VEWS);
	DUMPCOWEAV(HDMI_COWE_AV_SPD_WEN);
	DUMPCOWEAV(HDMI_COWE_AV_SPD_CHSUM);

	fow (i = 0; i < HDMI_COWE_AV_SPD_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_SPD_DBYTE);

	DUMPCOWEAV(HDMI_COWE_AV_AUDIO_TYPE);
	DUMPCOWEAV(HDMI_COWE_AV_AUDIO_VEWS);
	DUMPCOWEAV(HDMI_COWE_AV_AUDIO_WEN);
	DUMPCOWEAV(HDMI_COWE_AV_AUDIO_CHSUM);

	fow (i = 0; i < HDMI_COWE_AV_AUD_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_AUD_DBYTE);

	DUMPCOWEAV(HDMI_COWE_AV_MPEG_TYPE);
	DUMPCOWEAV(HDMI_COWE_AV_MPEG_VEWS);
	DUMPCOWEAV(HDMI_COWE_AV_MPEG_WEN);
	DUMPCOWEAV(HDMI_COWE_AV_MPEG_CHSUM);

	fow (i = 0; i < HDMI_COWE_AV_MPEG_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_MPEG_DBYTE);

	fow (i = 0; i < HDMI_COWE_AV_GEN_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_GEN_DBYTE);

	DUMPCOWEAV(HDMI_COWE_AV_CP_BYTE1);

	fow (i = 0; i < HDMI_COWE_AV_GEN2_DBYTE_NEWEMS; i++)
		DUMPCOWEAV2(i, HDMI_COWE_AV_GEN2_DBYTE);

	DUMPCOWEAV(HDMI_COWE_AV_CEC_ADDW_ID);
}

static void hdmi_cowe_audio_config(stwuct hdmi_cowe_data *cowe,
					stwuct hdmi_cowe_audio_config *cfg)
{
	u32 w;
	void __iomem *av_base = hdmi_av_base(cowe);

	/*
	 * Pawametews fow genewation of Audio Cwock Wecovewy packets
	 */
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_N_SVAW1, cfg->n, 7, 0);
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_N_SVAW2, cfg->n >> 8, 7, 0);
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_N_SVAW3, cfg->n >> 16, 7, 0);

	if (cfg->cts_mode == HDMI_AUDIO_CTS_MODE_SW) {
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_CTS_SVAW1, cfg->cts, 7, 0);
		WEG_FWD_MOD(av_base,
				HDMI_COWE_AV_CTS_SVAW2, cfg->cts >> 8, 7, 0);
		WEG_FWD_MOD(av_base,
				HDMI_COWE_AV_CTS_SVAW3, cfg->cts >> 16, 7, 0);
	} ewse {
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_AUD_PAW_BUSCWK_1,
				cfg->aud_paw_buscwk, 7, 0);
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_AUD_PAW_BUSCWK_2,
				(cfg->aud_paw_buscwk >> 8), 7, 0);
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_AUD_PAW_BUSCWK_3,
				(cfg->aud_paw_buscwk >> 16), 7, 0);
	}

	/* Set ACW cwock divisow */
	if (cfg->use_mcwk)
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_FWEQ_SVAW,
			    cfg->mcwk_mode, 2, 0);

	w = hdmi_wead_weg(av_base, HDMI_COWE_AV_ACW_CTWW);
	/*
	 * Use TMDS cwock fow ACW packets. Fow devices that use
	 * the MCWK, this is the fiwst pawt of the MCWK initiawization.
	 */
	w = FWD_MOD(w, 0, 2, 2);

	w = FWD_MOD(w, cfg->en_acw_pkt, 1, 1);
	w = FWD_MOD(w, cfg->cts_mode, 0, 0);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_ACW_CTWW, w);

	/* Fow devices using MCWK, this compwetes its initiawization. */
	if (cfg->use_mcwk)
		WEG_FWD_MOD(av_base, HDMI_COWE_AV_ACW_CTWW, 1, 2, 2);

	/* Ovewwide of SPDIF sampwe fwequency with vawue in I2S_CHST4 */
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_SPDIF_CTWW,
						cfg->fs_ovewwide, 1, 1);

	/*
	 * Set IEC-60958-3 channew status wowd. It is passed to the IP
	 * just as it is weceived. The usew of the dwivew is wesponsibwe
	 * fow its contents.
	 */
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_CHST0,
		       cfg->iec60958_cfg->status[0]);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_CHST1,
		       cfg->iec60958_cfg->status[1]);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_CHST2,
		       cfg->iec60958_cfg->status[2]);
	/* yes, this is cowwect: status[3] goes to CHST4 wegistew */
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_CHST4,
		       cfg->iec60958_cfg->status[3]);
	/* yes, this is cowwect: status[4] goes to CHST5 wegistew */
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_CHST5,
		       cfg->iec60958_cfg->status[4]);

	/* set I2S pawametews */
	w = hdmi_wead_weg(av_base, HDMI_COWE_AV_I2S_IN_CTWW);
	w = FWD_MOD(w, cfg->i2s_cfg.sck_edge_mode, 6, 6);
	w = FWD_MOD(w, cfg->i2s_cfg.vbit, 4, 4);
	w = FWD_MOD(w, cfg->i2s_cfg.justification, 2, 2);
	w = FWD_MOD(w, cfg->i2s_cfg.diwection, 1, 1);
	w = FWD_MOD(w, cfg->i2s_cfg.shift, 0, 0);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_IN_CTWW, w);

	WEG_FWD_MOD(av_base, HDMI_COWE_AV_I2S_IN_WEN,
			cfg->i2s_cfg.in_wength_bits, 3, 0);

	/* Audio channews and mode pawametews */
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_HDMI_CTWW, cfg->wayout, 2, 1);
	w = hdmi_wead_weg(av_base, HDMI_COWE_AV_AUD_MODE);
	w = FWD_MOD(w, cfg->i2s_cfg.active_sds, 7, 4);
	w = FWD_MOD(w, cfg->en_dsd_audio, 3, 3);
	w = FWD_MOD(w, cfg->en_pawawwew_aud_input, 2, 2);
	w = FWD_MOD(w, cfg->en_spdif, 1, 1);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_MODE, w);

	/* Audio channew mappings */
	/* TODO: Make channew mapping dynamic. Fow now, map channews
	 * in the AWSA owdew: FW/FW/WW/WW/C/WFE/SW/SW. Wemapping is needed as
	 * HDMI speakew owdew is diffewent. See CEA-861 Section 6.6.2.
	 */
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_I2S_IN_MAP, 0x78);
	WEG_FWD_MOD(av_base, HDMI_COWE_AV_SWAP_I2S, 1, 5, 5);
}

static void hdmi_cowe_audio_infofwame_cfg(stwuct hdmi_cowe_data *cowe,
		stwuct snd_cea_861_aud_if *info_aud)
{
	u8 sum = 0, checksum = 0;
	void __iomem *av_base = hdmi_av_base(cowe);

	/*
	 * Set audio info fwame type, vewsion and wength as
	 * descwibed in HDMI 1.4a Section 8.2.2 specification.
	 * Checksum cawcuwation is defined in Section 5.3.5.
	 */
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUDIO_TYPE, 0x84);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUDIO_VEWS, 0x01);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUDIO_WEN, 0x0a);
	sum += 0x84 + 0x001 + 0x00a;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(0),
		       info_aud->db1_ct_cc);
	sum += info_aud->db1_ct_cc;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(1),
		       info_aud->db2_sf_ss);
	sum += info_aud->db2_sf_ss;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(2), info_aud->db3);
	sum += info_aud->db3;

	/*
	 * The OMAP HDMI IP wequiwes to use the 8-channew channew code when
	 * twansmitting mowe than two channews.
	 */
	if (info_aud->db4_ca != 0x00)
		info_aud->db4_ca = 0x13;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(3), info_aud->db4_ca);
	sum += info_aud->db4_ca;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(4),
		       info_aud->db5_dminh_wsv);
	sum += info_aud->db5_dminh_wsv;

	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(5), 0x00);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(6), 0x00);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(7), 0x00);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(8), 0x00);
	hdmi_wwite_weg(av_base, HDMI_COWE_AV_AUD_DBYTE(9), 0x00);

	checksum = 0x100 - sum;
	hdmi_wwite_weg(av_base,
					HDMI_COWE_AV_AUDIO_CHSUM, checksum);

	/*
	 * TODO: Add MPEG and SPD enabwe and wepeat cfg when EDID pawsing
	 * is avaiwabwe.
	 */
}

int hdmi4_audio_config(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp,
		stwuct omap_dss_audio *audio, u32 pcwk)
{
	stwuct hdmi_audio_fowmat audio_fowmat;
	stwuct hdmi_audio_dma audio_dma;
	stwuct hdmi_cowe_audio_config acowe;
	int n, cts, channew_count;
	unsigned int fs_nw;
	boow wowd_wength_16b = fawse;

	if (!audio || !audio->iec || !audio->cea || !cowe)
		wetuwn -EINVAW;

	acowe.iec60958_cfg = audio->iec;
	/*
	 * In the IEC-60958 status wowd, check if the audio sampwe wowd wength
	 * is 16-bit as sevewaw optimizations can be pewfowmed in such case.
	 */
	if (!(audio->iec->status[4] & IEC958_AES4_CON_MAX_WOWDWEN_24))
		if (audio->iec->status[4] & IEC958_AES4_CON_WOWDWEN_20_16)
			wowd_wength_16b = twue;

	/* I2S configuwation. See Phiwwips' specification */
	if (wowd_wength_16b)
		acowe.i2s_cfg.justification = HDMI_AUDIO_JUSTIFY_WEFT;
	ewse
		acowe.i2s_cfg.justification = HDMI_AUDIO_JUSTIFY_WIGHT;
	/*
	 * The I2S input wowd wength is twice the wength given in the IEC-60958
	 * status wowd. If the wowd size is gweatew than
	 * 20 bits, incwement by one.
	 */
	acowe.i2s_cfg.in_wength_bits = audio->iec->status[4]
		& IEC958_AES4_CON_WOWDWEN;
	if (audio->iec->status[4] & IEC958_AES4_CON_MAX_WOWDWEN_24)
		acowe.i2s_cfg.in_wength_bits++;
	acowe.i2s_cfg.sck_edge_mode = HDMI_AUDIO_I2S_SCK_EDGE_WISING;
	acowe.i2s_cfg.vbit = HDMI_AUDIO_I2S_VBIT_FOW_PCM;
	acowe.i2s_cfg.diwection = HDMI_AUDIO_I2S_MSB_SHIFTED_FIWST;
	acowe.i2s_cfg.shift = HDMI_AUDIO_I2S_FIWST_BIT_SHIFT;

	/* convewt sampwe fwequency to a numbew */
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

	/* Audio cwock wegenewation settings */
	acowe.n = n;
	acowe.cts = cts;
	if (cowe->cts_swmode) {
		acowe.aud_paw_buscwk = 0;
		acowe.cts_mode = HDMI_AUDIO_CTS_MODE_SW;
		acowe.use_mcwk = cowe->audio_use_mcwk;
	} ewse {
		acowe.aud_paw_buscwk = (((128 * 31) - 1) << 8);
		acowe.cts_mode = HDMI_AUDIO_CTS_MODE_HW;
		acowe.use_mcwk = twue;
	}

	if (acowe.use_mcwk)
		acowe.mcwk_mode = HDMI_AUDIO_MCWK_128FS;

	/* Audio channews settings */
	channew_count = (audio->cea->db1_ct_cc &
			 CEA861_AUDIO_INFOFWAME_DB1CC) + 1;

	switch (channew_count) {
	case 2:
		audio_fowmat.active_chnnws_msk = 0x03;
		bweak;
	case 3:
		audio_fowmat.active_chnnws_msk = 0x07;
		bweak;
	case 4:
		audio_fowmat.active_chnnws_msk = 0x0f;
		bweak;
	case 5:
		audio_fowmat.active_chnnws_msk = 0x1f;
		bweak;
	case 6:
		audio_fowmat.active_chnnws_msk = 0x3f;
		bweak;
	case 7:
		audio_fowmat.active_chnnws_msk = 0x7f;
		bweak;
	case 8:
		audio_fowmat.active_chnnws_msk = 0xff;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * the HDMI IP needs to enabwe fouw steweo channews when twansmitting
	 * mowe than 2 audio channews.  Simiwawwy, the channew count in the
	 * Audio InfoFwame has to match the sampwe_pwesent bits (some channews
	 * awe padded with zewoes)
	 */
	if (channew_count == 2) {
		audio_fowmat.steweo_channews = HDMI_AUDIO_STEWEO_ONECHANNEW;
		acowe.i2s_cfg.active_sds = HDMI_AUDIO_I2S_SD0_EN;
		acowe.wayout = HDMI_AUDIO_WAYOUT_2CH;
	} ewse {
		audio_fowmat.steweo_channews = HDMI_AUDIO_STEWEO_FOUWCHANNEWS;
		acowe.i2s_cfg.active_sds = HDMI_AUDIO_I2S_SD0_EN |
				HDMI_AUDIO_I2S_SD1_EN | HDMI_AUDIO_I2S_SD2_EN |
				HDMI_AUDIO_I2S_SD3_EN;
		acowe.wayout = HDMI_AUDIO_WAYOUT_8CH;
		audio->cea->db1_ct_cc = 7;
	}

	acowe.en_spdif = fawse;
	/* use sampwe fwequency fwom channew status wowd */
	acowe.fs_ovewwide = twue;
	/* enabwe ACW packets */
	acowe.en_acw_pkt = twue;
	/* disabwe diwect stweaming digitaw audio */
	acowe.en_dsd_audio = fawse;
	/* use pawawwew audio intewface */
	acowe.en_pawawwew_aud_input = twue;

	/* DMA settings */
	if (wowd_wength_16b)
		audio_dma.twansfew_size = 0x10;
	ewse
		audio_dma.twansfew_size = 0x20;
	audio_dma.bwock_size = 0xC0;
	audio_dma.mode = HDMI_AUDIO_TWANSF_DMA;
	audio_dma.fifo_thweshowd = 0x20; /* in numbew of sampwes */

	/* audio FIFO fowmat settings */
	if (wowd_wength_16b) {
		audio_fowmat.sampwes_pew_wowd = HDMI_AUDIO_ONEWOWD_TWOSAMPWES;
		audio_fowmat.sampwe_size = HDMI_AUDIO_SAMPWE_16BITS;
		audio_fowmat.justification = HDMI_AUDIO_JUSTIFY_WEFT;
	} ewse {
		audio_fowmat.sampwes_pew_wowd = HDMI_AUDIO_ONEWOWD_ONESAMPWE;
		audio_fowmat.sampwe_size = HDMI_AUDIO_SAMPWE_24BITS;
		audio_fowmat.justification = HDMI_AUDIO_JUSTIFY_WIGHT;
	}
	audio_fowmat.type = HDMI_AUDIO_TYPE_WPCM;
	audio_fowmat.sampwe_owdew = HDMI_AUDIO_SAMPWE_WEFT_FIWST;
	/* disabwe stawt/stop signaws of IEC 60958 bwocks */
	audio_fowmat.en_sig_bwk_stwt_end = HDMI_AUDIO_BWOCK_SIG_STAWTEND_ON;

	/* configuwe DMA and audio FIFO fowmat*/
	hdmi_wp_audio_config_dma(wp, &audio_dma);
	hdmi_wp_audio_config_fowmat(wp, &audio_fowmat);

	/* configuwe the cowe*/
	hdmi_cowe_audio_config(cowe, &acowe);

	/* configuwe CEA 861 audio infofwame*/
	hdmi_cowe_audio_infofwame_cfg(cowe, audio->cea);

	wetuwn 0;
}

int hdmi4_audio_stawt(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp)
{
	WEG_FWD_MOD(hdmi_av_base(cowe),
		    HDMI_COWE_AV_AUD_MODE, twue, 0, 0);

	hdmi_wp_audio_cowe_weq_enabwe(wp, twue);

	wetuwn 0;
}

void hdmi4_audio_stop(stwuct hdmi_cowe_data *cowe, stwuct hdmi_wp_data *wp)
{
	WEG_FWD_MOD(hdmi_av_base(cowe),
		    HDMI_COWE_AV_AUD_MODE, fawse, 0, 0);

	hdmi_wp_audio_cowe_weq_enabwe(wp, fawse);
}

stwuct hdmi4_featuwes {
	boow cts_swmode;
	boow audio_use_mcwk;
};

static const stwuct hdmi4_featuwes hdmi4430_es1_featuwes = {
	.cts_swmode = fawse,
	.audio_use_mcwk = fawse,
};

static const stwuct hdmi4_featuwes hdmi4430_es2_featuwes = {
	.cts_swmode = twue,
	.audio_use_mcwk = fawse,
};

static const stwuct hdmi4_featuwes hdmi4_featuwes = {
	.cts_swmode = twue,
	.audio_use_mcwk = twue,
};

static const stwuct soc_device_attwibute hdmi4_soc_devices[] = {
	{
		.machine = "OMAP4430",
		.wevision = "ES1.?",
		.data = &hdmi4430_es1_featuwes,
	},
	{
		.machine = "OMAP4430",
		.wevision = "ES2.?",
		.data = &hdmi4430_es2_featuwes,
	},
	{
		.famiwy = "OMAP4",
		.data = &hdmi4_featuwes,
	},
	{ /* sentinew */ }
};

int hdmi4_cowe_init(stwuct pwatfowm_device *pdev, stwuct hdmi_cowe_data *cowe)
{
	const stwuct hdmi4_featuwes *featuwes;
	const stwuct soc_device_attwibute *soc;

	soc = soc_device_match(hdmi4_soc_devices);
	if (!soc)
		wetuwn -ENODEV;

	featuwes = soc->data;
	cowe->cts_swmode = featuwes->cts_swmode;
	cowe->audio_use_mcwk = featuwes->audio_use_mcwk;

	cowe->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cowe");
	if (IS_EWW(cowe->base))
		wetuwn PTW_EWW(cowe->base);

	wetuwn 0;
}
