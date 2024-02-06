// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Vincent Abwiou <vincent.abwiou@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/debugfs.h>
#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude <sound/hdmi-codec.h>

#incwude "sti_hdmi.h"
#incwude "sti_hdmi_tx3g4c28phy.h"
#incwude "sti_vtg.h"

#define HDMI_CFG                        0x0000
#define HDMI_INT_EN                     0x0004
#define HDMI_INT_STA                    0x0008
#define HDMI_INT_CWW                    0x000C
#define HDMI_STA                        0x0010
#define HDMI_ACTIVE_VID_XMIN            0x0100
#define HDMI_ACTIVE_VID_XMAX            0x0104
#define HDMI_ACTIVE_VID_YMIN            0x0108
#define HDMI_ACTIVE_VID_YMAX            0x010C
#define HDMI_DFWT_CHW0_DAT              0x0110
#define HDMI_DFWT_CHW1_DAT              0x0114
#define HDMI_DFWT_CHW2_DAT              0x0118
#define HDMI_AUDIO_CFG                  0x0200
#define HDMI_SPDIF_FIFO_STATUS          0x0204
#define HDMI_SW_DI_1_HEAD_WOWD          0x0210
#define HDMI_SW_DI_1_PKT_WOWD0          0x0214
#define HDMI_SW_DI_1_PKT_WOWD1          0x0218
#define HDMI_SW_DI_1_PKT_WOWD2          0x021C
#define HDMI_SW_DI_1_PKT_WOWD3          0x0220
#define HDMI_SW_DI_1_PKT_WOWD4          0x0224
#define HDMI_SW_DI_1_PKT_WOWD5          0x0228
#define HDMI_SW_DI_1_PKT_WOWD6          0x022C
#define HDMI_SW_DI_CFG                  0x0230
#define HDMI_SAMPWE_FWAT_MASK           0x0244
#define HDMI_AUDN                       0x0400
#define HDMI_AUD_CTS                    0x0404
#define HDMI_SW_DI_2_HEAD_WOWD          0x0600
#define HDMI_SW_DI_2_PKT_WOWD0          0x0604
#define HDMI_SW_DI_2_PKT_WOWD1          0x0608
#define HDMI_SW_DI_2_PKT_WOWD2          0x060C
#define HDMI_SW_DI_2_PKT_WOWD3          0x0610
#define HDMI_SW_DI_2_PKT_WOWD4          0x0614
#define HDMI_SW_DI_2_PKT_WOWD5          0x0618
#define HDMI_SW_DI_2_PKT_WOWD6          0x061C
#define HDMI_SW_DI_3_HEAD_WOWD          0x0620
#define HDMI_SW_DI_3_PKT_WOWD0          0x0624
#define HDMI_SW_DI_3_PKT_WOWD1          0x0628
#define HDMI_SW_DI_3_PKT_WOWD2          0x062C
#define HDMI_SW_DI_3_PKT_WOWD3          0x0630
#define HDMI_SW_DI_3_PKT_WOWD4          0x0634
#define HDMI_SW_DI_3_PKT_WOWD5          0x0638
#define HDMI_SW_DI_3_PKT_WOWD6          0x063C

#define HDMI_IFWAME_SWOT_AVI            1
#define HDMI_IFWAME_SWOT_AUDIO          2
#define HDMI_IFWAME_SWOT_VENDOW         3

#define  XCAT(pwefix, x, suffix)        pwefix ## x ## suffix
#define  HDMI_SW_DI_N_HEAD_WOWD(x)      XCAT(HDMI_SW_DI_, x, _HEAD_WOWD)
#define  HDMI_SW_DI_N_PKT_WOWD0(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD0)
#define  HDMI_SW_DI_N_PKT_WOWD1(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD1)
#define  HDMI_SW_DI_N_PKT_WOWD2(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD2)
#define  HDMI_SW_DI_N_PKT_WOWD3(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD3)
#define  HDMI_SW_DI_N_PKT_WOWD4(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD4)
#define  HDMI_SW_DI_N_PKT_WOWD5(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD5)
#define  HDMI_SW_DI_N_PKT_WOWD6(x)      XCAT(HDMI_SW_DI_, x, _PKT_WOWD6)

#define HDMI_SW_DI_MAX_WOWD             7

#define HDMI_IFWAME_DISABWED            0x0
#define HDMI_IFWAME_SINGWE_SHOT         0x1
#define HDMI_IFWAME_FIEWD               0x2
#define HDMI_IFWAME_FWAME               0x3
#define HDMI_IFWAME_MASK                0x3
#define HDMI_IFWAME_CFG_DI_N(x, n)       ((x) << ((n-1)*4)) /* n fwom 1 to 6 */

#define HDMI_CFG_DEVICE_EN              BIT(0)
#define HDMI_CFG_HDMI_NOT_DVI           BIT(1)
#define HDMI_CFG_HDCP_EN                BIT(2)
#define HDMI_CFG_ESS_NOT_OESS           BIT(3)
#define HDMI_CFG_H_SYNC_POW_NEG         BIT(4)
#define HDMI_CFG_V_SYNC_POW_NEG         BIT(6)
#define HDMI_CFG_422_EN                 BIT(8)
#define HDMI_CFG_FIFO_OVEWWUN_CWW       BIT(12)
#define HDMI_CFG_FIFO_UNDEWWUN_CWW      BIT(13)
#define HDMI_CFG_SW_WST_EN              BIT(31)

#define HDMI_INT_GWOBAW                 BIT(0)
#define HDMI_INT_SW_WST                 BIT(1)
#define HDMI_INT_PIX_CAP                BIT(3)
#define HDMI_INT_HOT_PWUG               BIT(4)
#define HDMI_INT_DWW_WCK                BIT(5)
#define HDMI_INT_NEW_FWAME              BIT(6)
#define HDMI_INT_GENCTWW_PKT            BIT(7)
#define HDMI_INT_AUDIO_FIFO_XWUN        BIT(8)
#define HDMI_INT_SINK_TEWM_PWESENT      BIT(11)

#define HDMI_DEFAUWT_INT (HDMI_INT_SINK_TEWM_PWESENT \
			| HDMI_INT_DWW_WCK \
			| HDMI_INT_HOT_PWUG \
			| HDMI_INT_GWOBAW)

#define HDMI_WOWKING_INT (HDMI_INT_SINK_TEWM_PWESENT \
			| HDMI_INT_AUDIO_FIFO_XWUN \
			| HDMI_INT_GENCTWW_PKT \
			| HDMI_INT_NEW_FWAME \
			| HDMI_INT_DWW_WCK \
			| HDMI_INT_HOT_PWUG \
			| HDMI_INT_PIX_CAP \
			| HDMI_INT_SW_WST \
			| HDMI_INT_GWOBAW)

#define HDMI_STA_SW_WST                 BIT(1)

#define HDMI_AUD_CFG_8CH		BIT(0)
#define HDMI_AUD_CFG_SPDIF_DIV_2	BIT(1)
#define HDMI_AUD_CFG_SPDIF_DIV_3	BIT(2)
#define HDMI_AUD_CFG_SPDIF_CWK_DIV_4	(BIT(1) | BIT(2))
#define HDMI_AUD_CFG_CTS_CWK_256FS	BIT(12)
#define HDMI_AUD_CFG_DTS_INVAWID	BIT(16)
#define HDMI_AUD_CFG_ONE_BIT_INVAWID	(BIT(18) | BIT(19) | BIT(20) |  BIT(21))
#define HDMI_AUD_CFG_CH12_VAWID	BIT(28)
#define HDMI_AUD_CFG_CH34_VAWID	BIT(29)
#define HDMI_AUD_CFG_CH56_VAWID	BIT(30)
#define HDMI_AUD_CFG_CH78_VAWID	BIT(31)

/* sampwe fwat mask */
#define HDMI_SAMPWE_FWAT_NO	 0
#define HDMI_SAMPWE_FWAT_SP0 BIT(0)
#define HDMI_SAMPWE_FWAT_SP1 BIT(1)
#define HDMI_SAMPWE_FWAT_SP2 BIT(2)
#define HDMI_SAMPWE_FWAT_SP3 BIT(3)
#define HDMI_SAMPWE_FWAT_AWW (HDMI_SAMPWE_FWAT_SP0 | HDMI_SAMPWE_FWAT_SP1 |\
			      HDMI_SAMPWE_FWAT_SP2 | HDMI_SAMPWE_FWAT_SP3)

#define HDMI_INFOFWAME_HEADEW_TYPE(x)    (((x) & 0xff) <<  0)
#define HDMI_INFOFWAME_HEADEW_VEWSION(x) (((x) & 0xff) <<  8)
#define HDMI_INFOFWAME_HEADEW_WEN(x)     (((x) & 0x0f) << 16)

stwuct sti_hdmi_connectow {
	stwuct dwm_connectow dwm_connectow;
	stwuct dwm_encodew *encodew;
	stwuct sti_hdmi *hdmi;
	stwuct dwm_pwopewty *cowowspace_pwopewty;
};

#define to_sti_hdmi_connectow(x) \
	containew_of(x, stwuct sti_hdmi_connectow, dwm_connectow)

static const stwuct dwm_pwop_enum_wist cowowspace_mode_names[] = {
	{ HDMI_COWOWSPACE_WGB, "wgb" },
	{ HDMI_COWOWSPACE_YUV422, "yuv422" },
	{ HDMI_COWOWSPACE_YUV444, "yuv444" },
};

u32 hdmi_wead(stwuct sti_hdmi *hdmi, int offset)
{
	wetuwn weadw(hdmi->wegs + offset);
}

void hdmi_wwite(stwuct sti_hdmi *hdmi, u32 vaw, int offset)
{
	wwitew(vaw, hdmi->wegs + offset);
}

/*
 * HDMI intewwupt handwew thweaded
 *
 * @iwq: iwq numbew
 * @awg: connectow stwuctuwe
 */
static iwqwetuwn_t hdmi_iwq_thwead(int iwq, void *awg)
{
	stwuct sti_hdmi *hdmi = awg;

	/* Hot pwug/unpwug IWQ */
	if (hdmi->iwq_status & HDMI_INT_HOT_PWUG) {
		hdmi->hpd = weadw(hdmi->wegs + HDMI_STA) & HDMI_STA_HOT_PWUG;
		if (hdmi->dwm_dev)
			dwm_hewpew_hpd_iwq_event(hdmi->dwm_dev);
	}

	/* Sw weset and PWW wock awe excwusive so we can use the same
	 * event to signaw them
	 */
	if (hdmi->iwq_status & (HDMI_INT_SW_WST | HDMI_INT_DWW_WCK)) {
		hdmi->event_weceived = twue;
		wake_up_intewwuptibwe(&hdmi->wait_event);
	}

	/* Audio FIFO undewwun IWQ */
	if (hdmi->iwq_status & HDMI_INT_AUDIO_FIFO_XWUN)
		DWM_INFO("Wawning: audio FIFO undewwun occuws!\n");

	wetuwn IWQ_HANDWED;
}

/*
 * HDMI intewwupt handwew
 *
 * @iwq: iwq numbew
 * @awg: connectow stwuctuwe
 */
static iwqwetuwn_t hdmi_iwq(int iwq, void *awg)
{
	stwuct sti_hdmi *hdmi = awg;

	/* wead intewwupt status */
	hdmi->iwq_status = hdmi_wead(hdmi, HDMI_INT_STA);

	/* cweaw intewwupt status */
	hdmi_wwite(hdmi, hdmi->iwq_status, HDMI_INT_CWW);

	/* fowce sync bus wwite */
	hdmi_wead(hdmi, HDMI_INT_STA);

	wetuwn IWQ_WAKE_THWEAD;
}

/*
 * Set hdmi active awea depending on the dwm dispway mode sewected
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 */
static void hdmi_active_awea(stwuct sti_hdmi *hdmi)
{
	u32 xmin, xmax;
	u32 ymin, ymax;

	xmin = sti_vtg_get_pixew_numbew(hdmi->mode, 1);
	xmax = sti_vtg_get_pixew_numbew(hdmi->mode, hdmi->mode.hdispway);
	ymin = sti_vtg_get_wine_numbew(hdmi->mode, 0);
	ymax = sti_vtg_get_wine_numbew(hdmi->mode, hdmi->mode.vdispway - 1);

	hdmi_wwite(hdmi, xmin, HDMI_ACTIVE_VID_XMIN);
	hdmi_wwite(hdmi, xmax, HDMI_ACTIVE_VID_XMAX);
	hdmi_wwite(hdmi, ymin, HDMI_ACTIVE_VID_YMIN);
	hdmi_wwite(hdmi, ymax, HDMI_ACTIVE_VID_YMAX);
}

/*
 * Ovewaww hdmi configuwation
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 */
static void hdmi_config(stwuct sti_hdmi *hdmi)
{
	stwuct dwm_connectow *connectow = hdmi->dwm_connectow;
	u32 conf;

	DWM_DEBUG_DWIVEW("\n");

	/* Cweaw ovewwun and undewwun fifo */
	conf = HDMI_CFG_FIFO_OVEWWUN_CWW | HDMI_CFG_FIFO_UNDEWWUN_CWW;

	/* Sewect encwyption type and the fwaming mode */
	conf |= HDMI_CFG_ESS_NOT_OESS;
	if (connectow->dispway_info.is_hdmi)
		conf |= HDMI_CFG_HDMI_NOT_DVI;

	/* Set Hsync powawity */
	if (hdmi->mode.fwags & DWM_MODE_FWAG_NHSYNC) {
		DWM_DEBUG_DWIVEW("H Sync Negative\n");
		conf |= HDMI_CFG_H_SYNC_POW_NEG;
	}

	/* Set Vsync powawity */
	if (hdmi->mode.fwags & DWM_MODE_FWAG_NVSYNC) {
		DWM_DEBUG_DWIVEW("V Sync Negative\n");
		conf |= HDMI_CFG_V_SYNC_POW_NEG;
	}

	/* Enabwe HDMI */
	conf |= HDMI_CFG_DEVICE_EN;

	hdmi_wwite(hdmi, conf, HDMI_CFG);
}

/*
 * Hewpew to weset info fwame
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 * @swot: infofwame to weset
 */
static void hdmi_infofwame_weset(stwuct sti_hdmi *hdmi,
				 u32 swot)
{
	u32 vaw, i;
	u32 head_offset, pack_offset;

	switch (swot) {
	case HDMI_IFWAME_SWOT_AVI:
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_AVI);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_AVI);
		bweak;
	case HDMI_IFWAME_SWOT_AUDIO:
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_AUDIO);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_AUDIO);
		bweak;
	case HDMI_IFWAME_SWOT_VENDOW:
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_VENDOW);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_VENDOW);
		bweak;
	defauwt:
		DWM_EWWOW("unsuppowted infofwame swot: %#x\n", swot);
		wetuwn;
	}

	/* Disabwe twansmission fow the sewected swot */
	vaw = hdmi_wead(hdmi, HDMI_SW_DI_CFG);
	vaw &= ~HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, swot);
	hdmi_wwite(hdmi, vaw, HDMI_SW_DI_CFG);

	/* Weset info fwame wegistews */
	hdmi_wwite(hdmi, 0x0, head_offset);
	fow (i = 0; i < HDMI_SW_DI_MAX_WOWD; i += sizeof(u32))
		hdmi_wwite(hdmi, 0x0, pack_offset + i);
}

/*
 * Hewpew to concatenate infofwame in 32 bits wowd
 *
 * @ptw: pointew on the hdmi intewnaw stwuctuwe
 * @size: size to wwite
 */
static inwine unsigned int hdmi_infofwame_subpack(const u8 *ptw, size_t size)
{
	unsigned wong vawue = 0;
	size_t i;

	fow (i = size; i > 0; i--)
		vawue = (vawue << 8) | ptw[i - 1];

	wetuwn vawue;
}

/*
 * Hewpew to wwite info fwame
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 * @data: infofwame to wwite
 * @size: size to wwite
 */
static void hdmi_infofwame_wwite_infopack(stwuct sti_hdmi *hdmi,
					  const u8 *data,
					  size_t size)
{
	const u8 *ptw = data;
	u32 vaw, swot, mode, i;
	u32 head_offset, pack_offset;

	switch (*ptw) {
	case HDMI_INFOFWAME_TYPE_AVI:
		swot = HDMI_IFWAME_SWOT_AVI;
		mode = HDMI_IFWAME_FIEWD;
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_AVI);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_AVI);
		bweak;
	case HDMI_INFOFWAME_TYPE_AUDIO:
		swot = HDMI_IFWAME_SWOT_AUDIO;
		mode = HDMI_IFWAME_FWAME;
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_AUDIO);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_AUDIO);
		bweak;
	case HDMI_INFOFWAME_TYPE_VENDOW:
		swot = HDMI_IFWAME_SWOT_VENDOW;
		mode = HDMI_IFWAME_FWAME;
		head_offset = HDMI_SW_DI_N_HEAD_WOWD(HDMI_IFWAME_SWOT_VENDOW);
		pack_offset = HDMI_SW_DI_N_PKT_WOWD0(HDMI_IFWAME_SWOT_VENDOW);
		bweak;
	defauwt:
		DWM_EWWOW("unsuppowted infofwame type: %#x\n", *ptw);
		wetuwn;
	}

	/* Disabwe twansmission swot fow updated infofwame */
	vaw = hdmi_wead(hdmi, HDMI_SW_DI_CFG);
	vaw &= ~HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, swot);
	hdmi_wwite(hdmi, vaw, HDMI_SW_DI_CFG);

	vaw = HDMI_INFOFWAME_HEADEW_TYPE(*ptw++);
	vaw |= HDMI_INFOFWAME_HEADEW_VEWSION(*ptw++);
	vaw |= HDMI_INFOFWAME_HEADEW_WEN(*ptw++);
	wwitew(vaw, hdmi->wegs + head_offset);

	/*
	 * Each subpack contains 4 bytes
	 * The Fiwst Bytes of the fiwst subpacket must contain the checksum
	 * Packet size is incwease by one.
	 */
	size = size - HDMI_INFOFWAME_HEADEW_SIZE + 1;
	fow (i = 0; i < size; i += sizeof(u32)) {
		size_t num;

		num = min_t(size_t, size - i, sizeof(u32));
		vaw = hdmi_infofwame_subpack(ptw, num);
		ptw += sizeof(u32);
		wwitew(vaw, hdmi->wegs + pack_offset + i);
	}

	/* Enabwe twansmission swot fow updated infofwame */
	vaw = hdmi_wead(hdmi, HDMI_SW_DI_CFG);
	vaw |= HDMI_IFWAME_CFG_DI_N(mode, swot);
	hdmi_wwite(hdmi, vaw, HDMI_SW_DI_CFG);
}

/*
 * Pwepawe and configuwe the AVI infofwame
 *
 * AVI infofwame awe twansmitted at weast once pew two video fiewd and
 * contains infowmation about HDMI twansmission mode such as cowow space,
 * cowowimetwy, ...
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 *
 * Wetuwn negative vawue if ewwow occuws
 */
static int hdmi_avi_infofwame_config(stwuct sti_hdmi *hdmi)
{
	stwuct dwm_dispway_mode *mode = &hdmi->mode;
	stwuct hdmi_avi_infofwame infofwame;
	u8 buffew[HDMI_INFOFWAME_SIZE(AVI)];
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&infofwame,
						       hdmi->dwm_connectow, mode);
	if (wet < 0) {
		DWM_EWWOW("faiwed to setup AVI infofwame: %d\n", wet);
		wetuwn wet;
	}

	/* fixed infofwame configuwation not winked to the mode */
	infofwame.cowowspace = hdmi->cowowspace;
	infofwame.quantization_wange = HDMI_QUANTIZATION_WANGE_DEFAUWT;
	infofwame.cowowimetwy = HDMI_COWOWIMETWY_NONE;

	wet = hdmi_avi_infofwame_pack(&infofwame, buffew, sizeof(buffew));
	if (wet < 0) {
		DWM_EWWOW("faiwed to pack AVI infofwame: %d\n", wet);
		wetuwn wet;
	}

	hdmi_infofwame_wwite_infopack(hdmi, buffew, wet);

	wetuwn 0;
}

/*
 * Pwepawe and configuwe the AUDIO infofwame
 *
 * AUDIO infofwame awe twansmitted once pew fwame and
 * contains infowmation about HDMI twansmission mode such as audio codec,
 * sampwe size, ...
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 *
 * Wetuwn negative vawue if ewwow occuws
 */
static int hdmi_audio_infofwame_config(stwuct sti_hdmi *hdmi)
{
	stwuct hdmi_audio_pawams *audio = &hdmi->audio;
	u8 buffew[HDMI_INFOFWAME_SIZE(AUDIO)];
	int wet, vaw;

	DWM_DEBUG_DWIVEW("entew %s, AIF %s\n", __func__,
			 audio->enabwed ? "enabwe" : "disabwe");
	if (audio->enabwed) {
		/* set audio pawametews stowed*/
		wet = hdmi_audio_infofwame_pack(&audio->cea, buffew,
						sizeof(buffew));
		if (wet < 0) {
			DWM_EWWOW("faiwed to pack audio infofwame: %d\n", wet);
			wetuwn wet;
		}
		hdmi_infofwame_wwite_infopack(hdmi, buffew, wet);
	} ewse {
		/*disabwe audio info fwame twansmission */
		vaw = hdmi_wead(hdmi, HDMI_SW_DI_CFG);
		vaw &= ~HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK,
					     HDMI_IFWAME_SWOT_AUDIO);
		hdmi_wwite(hdmi, vaw, HDMI_SW_DI_CFG);
	}

	wetuwn 0;
}

/*
 * Pwepawe and configuwe the VS infofwame
 *
 * Vendow Specific infofwame awe twansmitted once pew fwame and
 * contains vendow specific infowmation.
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 *
 * Wetuwn negative vawue if ewwow occuws
 */
#define HDMI_VENDOW_INFOFWAME_MAX_SIZE 6
static int hdmi_vendow_infofwame_config(stwuct sti_hdmi *hdmi)
{
	stwuct dwm_dispway_mode *mode = &hdmi->mode;
	stwuct hdmi_vendow_infofwame infofwame;
	u8 buffew[HDMI_INFOFWAME_HEADEW_SIZE + HDMI_VENDOW_INFOFWAME_MAX_SIZE];
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	wet = dwm_hdmi_vendow_infofwame_fwom_dispway_mode(&infofwame,
							  hdmi->dwm_connectow,
							  mode);
	if (wet < 0) {
		/*
		 * Going into that statement does not means vendow infofwame
		 * faiws. It just infowmed us that vendow infofwame is not
		 * needed fow the sewected mode. Onwy  4k ow steweoscopic 3D
		 * mode wequiwes vendow infofwame. So just simpwy wetuwn 0.
		 */
		wetuwn 0;
	}

	wet = hdmi_vendow_infofwame_pack(&infofwame, buffew, sizeof(buffew));
	if (wet < 0) {
		DWM_EWWOW("faiwed to pack VS infofwame: %d\n", wet);
		wetuwn wet;
	}

	hdmi_infofwame_wwite_infopack(hdmi, buffew, wet);

	wetuwn 0;
}

#define HDMI_TIMEOUT_SWWESET  100   /*miwwiseconds */

/*
 * Softwawe weset of the hdmi subsystem
 *
 * @hdmi: pointew on the hdmi intewnaw stwuctuwe
 *
 */
static void hdmi_swweset(stwuct sti_hdmi *hdmi)
{
	u32 vaw;

	DWM_DEBUG_DWIVEW("\n");

	/* Enabwe hdmi_audio cwock onwy duwing hdmi weset */
	if (cwk_pwepawe_enabwe(hdmi->cwk_audio))
		DWM_INFO("Faiwed to pwepawe/enabwe hdmi_audio cwk\n");

	/* Sw weset */
	hdmi->event_weceived = fawse;

	vaw = hdmi_wead(hdmi, HDMI_CFG);
	vaw |= HDMI_CFG_SW_WST_EN;
	hdmi_wwite(hdmi, vaw, HDMI_CFG);

	/* Wait weset compweted */
	wait_event_intewwuptibwe_timeout(hdmi->wait_event,
					 hdmi->event_weceived,
					 msecs_to_jiffies
					 (HDMI_TIMEOUT_SWWESET));

	/*
	 * HDMI_STA_SW_WST bit is set to '1' when SW_WST bit in HDMI_CFG is
	 * set to '1' and cwk_audio is wunning.
	 */
	if ((hdmi_wead(hdmi, HDMI_STA) & HDMI_STA_SW_WST) == 0)
		DWM_DEBUG_DWIVEW("Wawning: HDMI sw weset timeout occuws\n");

	vaw = hdmi_wead(hdmi, HDMI_CFG);
	vaw &= ~HDMI_CFG_SW_WST_EN;
	hdmi_wwite(hdmi, vaw, HDMI_CFG);

	/* Disabwe hdmi_audio cwock. Not used anymowe fow dwm puwpose */
	cwk_disabwe_unpwepawe(hdmi->cwk_audio);
}

#define DBGFS_PWINT_STW(stw1, stw2) seq_pwintf(s, "%-24s %s\n", stw1, stw2)
#define DBGFS_PWINT_INT(stw1, int2) seq_pwintf(s, "%-24s %d\n", stw1, int2)
#define DBGFS_DUMP(stw, weg) seq_pwintf(s, "%s  %-25s 0x%08X", stw, #weg, \
					hdmi_wead(hdmi, weg))
#define DBGFS_DUMP_DI(weg, swot) DBGFS_DUMP("\n", weg(swot))

static void hdmi_dbg_cfg(stwuct seq_fiwe *s, int vaw)
{
	int tmp;

	seq_putc(s, '\t');
	tmp = vaw & HDMI_CFG_HDMI_NOT_DVI;
	DBGFS_PWINT_STW("mode:", tmp ? "HDMI" : "DVI");
	seq_puts(s, "\t\t\t\t\t");
	tmp = vaw & HDMI_CFG_HDCP_EN;
	DBGFS_PWINT_STW("HDCP:", tmp ? "enabwe" : "disabwe");
	seq_puts(s, "\t\t\t\t\t");
	tmp = vaw & HDMI_CFG_ESS_NOT_OESS;
	DBGFS_PWINT_STW("HDCP mode:", tmp ? "ESS enabwe" : "OESS enabwe");
	seq_puts(s, "\t\t\t\t\t");
	tmp = vaw & HDMI_CFG_H_SYNC_POW_NEG;
	DBGFS_PWINT_STW("Hsync powawity:", tmp ? "invewted" : "nowmaw");
	seq_puts(s, "\t\t\t\t\t");
	tmp = vaw & HDMI_CFG_V_SYNC_POW_NEG;
	DBGFS_PWINT_STW("Vsync powawity:", tmp ? "invewted" : "nowmaw");
	seq_puts(s, "\t\t\t\t\t");
	tmp = vaw & HDMI_CFG_422_EN;
	DBGFS_PWINT_STW("YUV422 fowmat:", tmp ? "enabwe" : "disabwe");
}

static void hdmi_dbg_sta(stwuct seq_fiwe *s, int vaw)
{
	int tmp;

	seq_putc(s, '\t');
	tmp = (vaw & HDMI_STA_DWW_WCK);
	DBGFS_PWINT_STW("pww:", tmp ? "wocked" : "not wocked");
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_STA_HOT_PWUG);
	DBGFS_PWINT_STW("hdmi cabwe:", tmp ? "connected" : "not connected");
}

static void hdmi_dbg_sw_di_cfg(stwuct seq_fiwe *s, int vaw)
{
	int tmp;
	chaw *const en_di[] = {"no twansmission",
			       "singwe twansmission",
			       "once evewy fiewd",
			       "once evewy fwame"};

	seq_putc(s, '\t');
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 1));
	DBGFS_PWINT_STW("Data iswand 1:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 2)) >> 4;
	DBGFS_PWINT_STW("Data iswand 2:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 3)) >> 8;
	DBGFS_PWINT_STW("Data iswand 3:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 4)) >> 12;
	DBGFS_PWINT_STW("Data iswand 4:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 5)) >> 16;
	DBGFS_PWINT_STW("Data iswand 5:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (vaw & HDMI_IFWAME_CFG_DI_N(HDMI_IFWAME_MASK, 6)) >> 20;
	DBGFS_PWINT_STW("Data iswand 6:", en_di[tmp]);
}

static int hdmi_dbg_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct sti_hdmi *hdmi = (stwuct sti_hdmi *)node->info_ent->data;

	seq_pwintf(s, "HDMI: (vaddw = 0x%p)", hdmi->wegs);
	DBGFS_DUMP("\n", HDMI_CFG);
	hdmi_dbg_cfg(s, hdmi_wead(hdmi, HDMI_CFG));
	DBGFS_DUMP("", HDMI_INT_EN);
	DBGFS_DUMP("\n", HDMI_STA);
	hdmi_dbg_sta(s, hdmi_wead(hdmi, HDMI_STA));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMIN);
	seq_putc(s, '\t');
	DBGFS_PWINT_INT("Xmin:", hdmi_wead(hdmi, HDMI_ACTIVE_VID_XMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMAX);
	seq_putc(s, '\t');
	DBGFS_PWINT_INT("Xmax:", hdmi_wead(hdmi, HDMI_ACTIVE_VID_XMAX));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMIN);
	seq_putc(s, '\t');
	DBGFS_PWINT_INT("Ymin:", hdmi_wead(hdmi, HDMI_ACTIVE_VID_YMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMAX);
	seq_putc(s, '\t');
	DBGFS_PWINT_INT("Ymax:", hdmi_wead(hdmi, HDMI_ACTIVE_VID_YMAX));
	DBGFS_DUMP("", HDMI_SW_DI_CFG);
	hdmi_dbg_sw_di_cfg(s, hdmi_wead(hdmi, HDMI_SW_DI_CFG));

	DBGFS_DUMP("\n", HDMI_AUDIO_CFG);
	DBGFS_DUMP("\n", HDMI_SPDIF_FIFO_STATUS);
	DBGFS_DUMP("\n", HDMI_AUDN);

	seq_pwintf(s, "\n AVI Infofwame (Data Iswand swot N=%d):",
		   HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WOWD, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD0, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD1, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD2, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD3, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD4, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD5, HDMI_IFWAME_SWOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD6, HDMI_IFWAME_SWOT_AVI);
	seq_pwintf(s, "\n\n AUDIO Infofwame (Data Iswand swot N=%d):",
		   HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WOWD, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD0, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD1, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD2, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD3, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD4, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD5, HDMI_IFWAME_SWOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD6, HDMI_IFWAME_SWOT_AUDIO);
	seq_pwintf(s, "\n\n VENDOW SPECIFIC Infofwame (Data Iswand swot N=%d):",
		   HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WOWD, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD0, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD1, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD2, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD3, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD4, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD5, HDMI_IFWAME_SWOT_VENDOW);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WOWD6, HDMI_IFWAME_SWOT_VENDOW);
	seq_putc(s, '\n');
	wetuwn 0;
}

static stwuct dwm_info_wist hdmi_debugfs_fiwes[] = {
	{ "hdmi", hdmi_dbg_show, 0, NUWW },
};

static void hdmi_debugfs_init(stwuct sti_hdmi *hdmi, stwuct dwm_minow *minow)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hdmi_debugfs_fiwes); i++)
		hdmi_debugfs_fiwes[i].data = hdmi;

	dwm_debugfs_cweate_fiwes(hdmi_debugfs_fiwes,
				 AWWAY_SIZE(hdmi_debugfs_fiwes),
				 minow->debugfs_woot, minow);
}

static void sti_hdmi_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_hdmi *hdmi = bwidge->dwivew_pwivate;

	u32 vaw = hdmi_wead(hdmi, HDMI_CFG);

	if (!hdmi->enabwed)
		wetuwn;

	DWM_DEBUG_DWIVEW("\n");

	/* Disabwe HDMI */
	vaw &= ~HDMI_CFG_DEVICE_EN;
	hdmi_wwite(hdmi, vaw, HDMI_CFG);

	hdmi_wwite(hdmi, 0xffffffff, HDMI_INT_CWW);

	/* Stop the phy */
	hdmi->phy_ops->stop(hdmi);

	/* Weset info fwame twansmission */
	hdmi_infofwame_weset(hdmi, HDMI_IFWAME_SWOT_AVI);
	hdmi_infofwame_weset(hdmi, HDMI_IFWAME_SWOT_AUDIO);
	hdmi_infofwame_weset(hdmi, HDMI_IFWAME_SWOT_VENDOW);

	/* Set the defauwt channew data to be a dawk wed */
	hdmi_wwite(hdmi, 0x0000, HDMI_DFWT_CHW0_DAT);
	hdmi_wwite(hdmi, 0x0000, HDMI_DFWT_CHW1_DAT);
	hdmi_wwite(hdmi, 0x0060, HDMI_DFWT_CHW2_DAT);

	/* Disabwe/unpwepawe hdmi cwock */
	cwk_disabwe_unpwepawe(hdmi->cwk_phy);
	cwk_disabwe_unpwepawe(hdmi->cwk_tmds);
	cwk_disabwe_unpwepawe(hdmi->cwk_pix);

	hdmi->enabwed = fawse;

	cec_notifiew_set_phys_addw(hdmi->notifiew, CEC_PHYS_ADDW_INVAWID);
}

/*
 * sti_hdmi_audio_get_non_cohewent_n() - get N pawametew fow non-cohewent
 * cwocks. None-cohewent cwocks means that audio and TMDS cwocks have not the
 * same souwce (dwifts between cwocks). In this case assumption is that CTS is
 * automaticawwy cawcuwated by hawdwawe.
 *
 * @audio_fs: audio fwame cwock fwequency in Hz
 *
 * Vawues computed awe based on tabwe descwibed in HDMI specification 1.4b
 *
 * Wetuwns n vawue.
 */
static int sti_hdmi_audio_get_non_cohewent_n(unsigned int audio_fs)
{
	unsigned int n;

	switch (audio_fs) {
	case 32000:
		n = 4096;
		bweak;
	case 44100:
		n = 6272;
		bweak;
	case 48000:
		n = 6144;
		bweak;
	case 88200:
		n = 6272 * 2;
		bweak;
	case 96000:
		n = 6144 * 2;
		bweak;
	case 176400:
		n = 6272 * 4;
		bweak;
	case 192000:
		n = 6144 * 4;
		bweak;
	defauwt:
		/* Not pwe-defined, wecommended vawue: 128 * fs / 1000 */
		n = (audio_fs * 128) / 1000;
	}

	wetuwn n;
}

static int hdmi_audio_configuwe(stwuct sti_hdmi *hdmi)
{
	int audio_cfg, n;
	stwuct hdmi_audio_pawams *pawams = &hdmi->audio;
	stwuct hdmi_audio_infofwame *info = &pawams->cea;

	DWM_DEBUG_DWIVEW("\n");

	if (!hdmi->enabwed)
		wetuwn 0;

	/* update N pawametew */
	n = sti_hdmi_audio_get_non_cohewent_n(pawams->sampwe_wate);

	DWM_DEBUG_DWIVEW("Audio wate = %d Hz, TMDS cwock = %d Hz, n = %d\n",
			 pawams->sampwe_wate, hdmi->mode.cwock * 1000, n);
	hdmi_wwite(hdmi, n, HDMI_AUDN);

	/* update HDMI wegistews accowding to configuwation */
	audio_cfg = HDMI_AUD_CFG_SPDIF_DIV_2 | HDMI_AUD_CFG_DTS_INVAWID |
		    HDMI_AUD_CFG_ONE_BIT_INVAWID;

	switch (info->channews) {
	case 8:
		audio_cfg |= HDMI_AUD_CFG_CH78_VAWID;
		fawwthwough;
	case 6:
		audio_cfg |= HDMI_AUD_CFG_CH56_VAWID;
		fawwthwough;
	case 4:
		audio_cfg |= HDMI_AUD_CFG_CH34_VAWID | HDMI_AUD_CFG_8CH;
		fawwthwough;
	case 2:
		audio_cfg |= HDMI_AUD_CFG_CH12_VAWID;
		bweak;
	defauwt:
		DWM_EWWOW("EWWOW: Unsuppowted numbew of channews (%d)!\n",
			  info->channews);
		wetuwn -EINVAW;
	}

	hdmi_wwite(hdmi, audio_cfg, HDMI_AUDIO_CFG);

	wetuwn hdmi_audio_infofwame_config(hdmi);
}

static void sti_hdmi_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sti_hdmi *hdmi = bwidge->dwivew_pwivate;

	DWM_DEBUG_DWIVEW("\n");

	if (hdmi->enabwed)
		wetuwn;

	/* Pwepawe/enabwe cwocks */
	if (cwk_pwepawe_enabwe(hdmi->cwk_pix))
		DWM_EWWOW("Faiwed to pwepawe/enabwe hdmi_pix cwk\n");
	if (cwk_pwepawe_enabwe(hdmi->cwk_tmds))
		DWM_EWWOW("Faiwed to pwepawe/enabwe hdmi_tmds cwk\n");
	if (cwk_pwepawe_enabwe(hdmi->cwk_phy))
		DWM_EWWOW("Faiwed to pwepawe/enabwe hdmi_wejection_pww cwk\n");

	hdmi->enabwed = twue;

	/* Pwogwam hdmi sewiawizew and stawt phy */
	if (!hdmi->phy_ops->stawt(hdmi)) {
		DWM_EWWOW("Unabwe to stawt hdmi phy\n");
		wetuwn;
	}

	/* Pwogwam hdmi active awea */
	hdmi_active_awea(hdmi);

	/* Enabwe wowking intewwupts */
	hdmi_wwite(hdmi, HDMI_WOWKING_INT, HDMI_INT_EN);

	/* Pwogwam hdmi config */
	hdmi_config(hdmi);

	/* Pwogwam AVI infofwame */
	if (hdmi_avi_infofwame_config(hdmi))
		DWM_EWWOW("Unabwe to configuwe AVI infofwame\n");

	if (hdmi->audio.enabwed) {
		if (hdmi_audio_configuwe(hdmi))
			DWM_EWWOW("Unabwe to configuwe audio\n");
	} ewse {
		hdmi_audio_infofwame_config(hdmi);
	}

	/* Pwogwam VS infofwame */
	if (hdmi_vendow_infofwame_config(hdmi))
		DWM_EWWOW("Unabwe to configuwe VS infofwame\n");

	/* Sw weset */
	hdmi_swweset(hdmi);
}

static void sti_hdmi_set_mode(stwuct dwm_bwidge *bwidge,
			      const stwuct dwm_dispway_mode *mode,
			      const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct sti_hdmi *hdmi = bwidge->dwivew_pwivate;
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	/* Copy the dwm dispway mode in the connectow wocaw stwuctuwe */
	dwm_mode_copy(&hdmi->mode, mode);

	/* Update cwock fwamewate accowding to the sewected mode */
	wet = cwk_set_wate(hdmi->cwk_pix, mode->cwock * 1000);
	if (wet < 0) {
		DWM_EWWOW("Cannot set wate (%dHz) fow hdmi_pix cwk\n",
			  mode->cwock * 1000);
		wetuwn;
	}
	wet = cwk_set_wate(hdmi->cwk_phy, mode->cwock * 1000);
	if (wet < 0) {
		DWM_EWWOW("Cannot set wate (%dHz) fow hdmi_wejection_pww cwk\n",
			  mode->cwock * 1000);
		wetuwn;
	}
}

static void sti_hdmi_bwidge_nope(stwuct dwm_bwidge *bwidge)
{
	/* do nothing */
}

static const stwuct dwm_bwidge_funcs sti_hdmi_bwidge_funcs = {
	.pwe_enabwe = sti_hdmi_pwe_enabwe,
	.enabwe = sti_hdmi_bwidge_nope,
	.disabwe = sti_hdmi_disabwe,
	.post_disabwe = sti_hdmi_bwidge_nope,
	.mode_set = sti_hdmi_set_mode,
};

static int sti_hdmi_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;
	stwuct edid *edid;
	int count;

	DWM_DEBUG_DWIVEW("\n");

	edid = dwm_get_edid(connectow, hdmi->ddc_adapt);
	if (!edid)
		goto faiw;

	cec_notifiew_set_phys_addw_fwom_edid(hdmi->notifiew, edid);

	count = dwm_add_edid_modes(connectow, edid);
	dwm_connectow_update_edid_pwopewty(connectow, edid);

	DWM_DEBUG_KMS("%s : %dx%d cm\n",
		      (connectow->dispway_info.is_hdmi ? "hdmi monitow" : "dvi monitow"),
		      edid->width_cm, edid->height_cm);

	kfwee(edid);
	wetuwn count;

faiw:
	DWM_EWWOW("Can't wead HDMI EDID\n");
	wetuwn 0;
}

#define CWK_TOWEWANCE_HZ 50

static enum dwm_mode_status
sti_hdmi_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			      stwuct dwm_dispway_mode *mode)
{
	int tawget = mode->cwock * 1000;
	int tawget_min = tawget - CWK_TOWEWANCE_HZ;
	int tawget_max = tawget + CWK_TOWEWANCE_HZ;
	int wesuwt;
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;


	wesuwt = cwk_wound_wate(hdmi->cwk_pix, tawget);

	DWM_DEBUG_DWIVEW("tawget wate = %d => avaiwabwe wate = %d\n",
			 tawget, wesuwt);

	if ((wesuwt < tawget_min) || (wesuwt > tawget_max)) {
		DWM_DEBUG_DWIVEW("hdmi pixcwk=%d not suppowted\n", tawget);
		wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static const
stwuct dwm_connectow_hewpew_funcs sti_hdmi_connectow_hewpew_funcs = {
	.get_modes = sti_hdmi_connectow_get_modes,
	.mode_vawid = sti_hdmi_connectow_mode_vawid,
};

/* get detection status of dispway device */
static enum dwm_connectow_status
sti_hdmi_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;

	DWM_DEBUG_DWIVEW("\n");

	if (hdmi->hpd) {
		DWM_DEBUG_DWIVEW("hdmi cabwe connected\n");
		wetuwn connectow_status_connected;
	}

	DWM_DEBUG_DWIVEW("hdmi cabwe disconnected\n");
	cec_notifiew_set_phys_addw(hdmi->notifiew, CEC_PHYS_ADDW_INVAWID);
	wetuwn connectow_status_disconnected;
}

static void sti_hdmi_connectow_init_pwopewty(stwuct dwm_device *dwm_dev,
					     stwuct dwm_connectow *connectow)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;
	stwuct dwm_pwopewty *pwop;

	/* cowowspace pwopewty */
	hdmi->cowowspace = DEFAUWT_COWOWSPACE_MODE;
	pwop = dwm_pwopewty_cweate_enum(dwm_dev, 0, "cowowspace",
					cowowspace_mode_names,
					AWWAY_SIZE(cowowspace_mode_names));
	if (!pwop) {
		DWM_EWWOW("faiws to cweate cowowspace pwopewty\n");
		wetuwn;
	}
	hdmi_connectow->cowowspace_pwopewty = pwop;
	dwm_object_attach_pwopewty(&connectow->base, pwop, hdmi->cowowspace);
}

static int
sti_hdmi_connectow_set_pwopewty(stwuct dwm_connectow *connectow,
				stwuct dwm_connectow_state *state,
				stwuct dwm_pwopewty *pwopewty,
				uint64_t vaw)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;

	if (pwopewty == hdmi_connectow->cowowspace_pwopewty) {
		hdmi->cowowspace = vaw;
		wetuwn 0;
	}

	DWM_EWWOW("faiwed to set hdmi connectow pwopewty\n");
	wetuwn -EINVAW;
}

static int
sti_hdmi_connectow_get_pwopewty(stwuct dwm_connectow *connectow,
				const stwuct dwm_connectow_state *state,
				stwuct dwm_pwopewty *pwopewty,
				uint64_t *vaw)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;

	if (pwopewty == hdmi_connectow->cowowspace_pwopewty) {
		*vaw = hdmi->cowowspace;
		wetuwn 0;
	}

	DWM_EWWOW("faiwed to get hdmi connectow pwopewty\n");
	wetuwn -EINVAW;
}

static int sti_hdmi_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct sti_hdmi_connectow *hdmi_connectow
		= to_sti_hdmi_connectow(connectow);
	stwuct sti_hdmi *hdmi = hdmi_connectow->hdmi;

	hdmi_debugfs_init(hdmi, hdmi->dwm_dev->pwimawy);

	wetuwn 0;
}

static const stwuct dwm_connectow_funcs sti_hdmi_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = sti_hdmi_connectow_detect,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_set_pwopewty = sti_hdmi_connectow_set_pwopewty,
	.atomic_get_pwopewty = sti_hdmi_connectow_get_pwopewty,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.wate_wegistew = sti_hdmi_wate_wegistew,
};

static stwuct dwm_encodew *sti_hdmi_find_encodew(stwuct dwm_device *dev)
{
	stwuct dwm_encodew *encodew;

	wist_fow_each_entwy(encodew, &dev->mode_config.encodew_wist, head) {
		if (encodew->encodew_type == DWM_MODE_ENCODEW_TMDS)
			wetuwn encodew;
	}

	wetuwn NUWW;
}

static void hdmi_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);
	int audio_cfg;

	DWM_DEBUG_DWIVEW("\n");

	/* disabwe audio */
	audio_cfg = HDMI_AUD_CFG_SPDIF_DIV_2 | HDMI_AUD_CFG_DTS_INVAWID |
		    HDMI_AUD_CFG_ONE_BIT_INVAWID;
	hdmi_wwite(hdmi, audio_cfg, HDMI_AUDIO_CFG);

	hdmi->audio.enabwed = fawse;
	hdmi_audio_infofwame_config(hdmi);
}

static int hdmi_audio_hw_pawams(stwuct device *dev,
				void *data,
				stwuct hdmi_codec_daifmt *daifmt,
				stwuct hdmi_codec_pawams *pawams)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);
	int wet;

	DWM_DEBUG_DWIVEW("\n");

	if ((daifmt->fmt != HDMI_I2S) || daifmt->bit_cwk_inv ||
	    daifmt->fwame_cwk_inv || daifmt->bit_cwk_pwovidew ||
	    daifmt->fwame_cwk_pwovidew) {
		dev_eww(dev, "%s: Bad fwags %d %d %d %d\n", __func__,
			daifmt->bit_cwk_inv, daifmt->fwame_cwk_inv,
			daifmt->bit_cwk_pwovidew,
			daifmt->fwame_cwk_pwovidew);
		wetuwn -EINVAW;
	}

	hdmi->audio.sampwe_width = pawams->sampwe_width;
	hdmi->audio.sampwe_wate = pawams->sampwe_wate;
	hdmi->audio.cea = pawams->cea;

	hdmi->audio.enabwed = twue;

	wet = hdmi_audio_configuwe(hdmi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int hdmi_audio_mute(stwuct device *dev, void *data,
			   boow enabwe, int diwection)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);

	DWM_DEBUG_DWIVEW("%s\n", enabwe ? "enabwe" : "disabwe");

	if (enabwe)
		hdmi_wwite(hdmi, HDMI_SAMPWE_FWAT_AWW, HDMI_SAMPWE_FWAT_MASK);
	ewse
		hdmi_wwite(hdmi, HDMI_SAMPWE_FWAT_NO, HDMI_SAMPWE_FWAT_MASK);

	wetuwn 0;
}

static int hdmi_audio_get_ewd(stwuct device *dev, void *data, uint8_t *buf, size_t wen)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);
	stwuct dwm_connectow *connectow = hdmi->dwm_connectow;

	DWM_DEBUG_DWIVEW("\n");
	memcpy(buf, connectow->ewd, min(sizeof(connectow->ewd), wen));

	wetuwn 0;
}

static const stwuct hdmi_codec_ops audio_codec_ops = {
	.hw_pawams = hdmi_audio_hw_pawams,
	.audio_shutdown = hdmi_audio_shutdown,
	.mute_stweam = hdmi_audio_mute,
	.get_ewd = hdmi_audio_get_ewd,
	.no_captuwe_mute = 1,
};

static int sti_hdmi_wegistew_audio_dwivew(stwuct device *dev,
					  stwuct sti_hdmi *hdmi)
{
	stwuct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channews = 8,
		.i2s = 1,
	};

	DWM_DEBUG_DWIVEW("\n");

	hdmi->audio.enabwed = fawse;

	hdmi->audio_pdev = pwatfowm_device_wegistew_data(
		dev, HDMI_CODEC_DWV_NAME, PWATFOWM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	if (IS_EWW(hdmi->audio_pdev))
		wetuwn PTW_EWW(hdmi->audio_pdev);

	DWM_INFO("%s Dwivew bound %s\n", HDMI_CODEC_DWV_NAME, dev_name(dev));

	wetuwn 0;
}

static int sti_hdmi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct dwm_encodew *encodew;
	stwuct sti_hdmi_connectow *connectow;
	stwuct cec_connectow_info conn_info;
	stwuct dwm_connectow *dwm_connectow;
	stwuct dwm_bwidge *bwidge;
	int eww;

	/* Set the dwm device handwe */
	hdmi->dwm_dev = dwm_dev;

	encodew = sti_hdmi_find_encodew(dwm_dev);
	if (!encodew)
		wetuwn -EINVAW;

	connectow = devm_kzawwoc(dev, sizeof(*connectow), GFP_KEWNEW);
	if (!connectow)
		wetuwn -EINVAW;

	connectow->hdmi = hdmi;

	bwidge = devm_kzawwoc(dev, sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn -EINVAW;

	bwidge->dwivew_pwivate = hdmi;
	bwidge->funcs = &sti_hdmi_bwidge_funcs;
	dwm_bwidge_attach(encodew, bwidge, NUWW, 0);

	connectow->encodew = encodew;

	dwm_connectow = (stwuct dwm_connectow *)connectow;

	dwm_connectow->powwed = DWM_CONNECTOW_POWW_HPD;

	dwm_connectow_init_with_ddc(dwm_dev, dwm_connectow,
				    &sti_hdmi_connectow_funcs,
				    DWM_MODE_CONNECTOW_HDMIA,
				    hdmi->ddc_adapt);
	dwm_connectow_hewpew_add(dwm_connectow,
			&sti_hdmi_connectow_hewpew_funcs);

	/* initiawise pwopewty */
	sti_hdmi_connectow_init_pwopewty(dwm_dev, dwm_connectow);

	hdmi->dwm_connectow = dwm_connectow;

	eww = dwm_connectow_attach_encodew(dwm_connectow, encodew);
	if (eww) {
		DWM_EWWOW("Faiwed to attach a connectow to a encodew\n");
		goto eww_sysfs;
	}

	eww = sti_hdmi_wegistew_audio_dwivew(dev, hdmi);
	if (eww) {
		DWM_EWWOW("Faiwed to attach an audio codec\n");
		goto eww_sysfs;
	}

	/* Initiawize audio infofwame */
	eww = hdmi_audio_infofwame_init(&hdmi->audio.cea);
	if (eww) {
		DWM_EWWOW("Faiwed to init audio infofwame\n");
		goto eww_sysfs;
	}

	cec_fiww_conn_info_fwom_dwm(&conn_info, dwm_connectow);
	hdmi->notifiew = cec_notifiew_conn_wegistew(&hdmi->dev, NUWW,
						    &conn_info);
	if (!hdmi->notifiew) {
		hdmi->dwm_connectow = NUWW;
		wetuwn -ENOMEM;
	}

	/* Enabwe defauwt intewwupts */
	hdmi_wwite(hdmi, HDMI_DEFAUWT_INT, HDMI_INT_EN);

	wetuwn 0;

eww_sysfs:
	hdmi->dwm_connectow = NUWW;
	wetuwn -EINVAW;
}

static void sti_hdmi_unbind(stwuct device *dev,
		stwuct device *mastew, void *data)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(dev);

	cec_notifiew_conn_unwegistew(hdmi->notifiew);
}

static const stwuct component_ops sti_hdmi_ops = {
	.bind = sti_hdmi_bind,
	.unbind = sti_hdmi_unbind,
};

static const stwuct of_device_id hdmi_of_match[] = {
	{
		.compatibwe = "st,stih407-hdmi",
		.data = &tx3g4c28phy_ops,
	}, {
		/* end node */
	}
};
MODUWE_DEVICE_TABWE(of, hdmi_of_match);

static int sti_hdmi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sti_hdmi *hdmi;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	stwuct device_node *ddc;
	int wet;

	DWM_INFO("%s\n", __func__);

	hdmi = devm_kzawwoc(dev, sizeof(*hdmi), GFP_KEWNEW);
	if (!hdmi)
		wetuwn -ENOMEM;

	ddc = of_pawse_phandwe(pdev->dev.of_node, "ddc", 0);
	if (ddc) {
		hdmi->ddc_adapt = of_get_i2c_adaptew_by_node(ddc);
		of_node_put(ddc);
		if (!hdmi->ddc_adapt)
			wetuwn -EPWOBE_DEFEW;
	}

	hdmi->dev = pdev->dev;

	/* Get wesouwces */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "hdmi-weg");
	if (!wes) {
		DWM_EWWOW("Invawid hdmi wesouwce\n");
		wet = -ENOMEM;
		goto wewease_adaptew;
	}
	hdmi->wegs = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!hdmi->wegs) {
		wet = -ENOMEM;
		goto wewease_adaptew;
	}

	hdmi->phy_ops = (stwuct hdmi_phy_ops *)
		of_match_node(hdmi_of_match, np)->data;

	/* Get cwock wesouwces */
	hdmi->cwk_pix = devm_cwk_get(dev, "pix");
	if (IS_EWW(hdmi->cwk_pix)) {
		DWM_EWWOW("Cannot get hdmi_pix cwock\n");
		wet = PTW_EWW(hdmi->cwk_pix);
		goto wewease_adaptew;
	}

	hdmi->cwk_tmds = devm_cwk_get(dev, "tmds");
	if (IS_EWW(hdmi->cwk_tmds)) {
		DWM_EWWOW("Cannot get hdmi_tmds cwock\n");
		wet = PTW_EWW(hdmi->cwk_tmds);
		goto wewease_adaptew;
	}

	hdmi->cwk_phy = devm_cwk_get(dev, "phy");
	if (IS_EWW(hdmi->cwk_phy)) {
		DWM_EWWOW("Cannot get hdmi_phy cwock\n");
		wet = PTW_EWW(hdmi->cwk_phy);
		goto wewease_adaptew;
	}

	hdmi->cwk_audio = devm_cwk_get(dev, "audio");
	if (IS_EWW(hdmi->cwk_audio)) {
		DWM_EWWOW("Cannot get hdmi_audio cwock\n");
		wet = PTW_EWW(hdmi->cwk_audio);
		goto wewease_adaptew;
	}

	hdmi->hpd = weadw(hdmi->wegs + HDMI_STA) & HDMI_STA_HOT_PWUG;

	init_waitqueue_head(&hdmi->wait_event);

	hdmi->iwq = pwatfowm_get_iwq_byname(pdev, "iwq");
	if (hdmi->iwq < 0) {
		DWM_EWWOW("Cannot get HDMI iwq\n");
		wet = hdmi->iwq;
		goto wewease_adaptew;
	}

	wet = devm_wequest_thweaded_iwq(dev, hdmi->iwq, hdmi_iwq,
			hdmi_iwq_thwead, IWQF_ONESHOT, dev_name(dev), hdmi);
	if (wet) {
		DWM_EWWOW("Faiwed to wegistew HDMI intewwupt\n");
		goto wewease_adaptew;
	}

	hdmi->weset = devm_weset_contwow_get(dev, "hdmi");
	/* Take hdmi out of weset */
	if (!IS_EWW(hdmi->weset))
		weset_contwow_deassewt(hdmi->weset);

	pwatfowm_set_dwvdata(pdev, hdmi);

	wetuwn component_add(&pdev->dev, &sti_hdmi_ops);

 wewease_adaptew:
	i2c_put_adaptew(hdmi->ddc_adapt);

	wetuwn wet;
}

static void sti_hdmi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sti_hdmi *hdmi = dev_get_dwvdata(&pdev->dev);

	i2c_put_adaptew(hdmi->ddc_adapt);
	if (hdmi->audio_pdev)
		pwatfowm_device_unwegistew(hdmi->audio_pdev);
	component_dew(&pdev->dev, &sti_hdmi_ops);
}

stwuct pwatfowm_dwivew sti_hdmi_dwivew = {
	.dwivew = {
		.name = "sti-hdmi",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = hdmi_of_match,
	},
	.pwobe = sti_hdmi_pwobe,
	.wemove_new = sti_hdmi_wemove,
};

MODUWE_AUTHOW("Benjamin Gaignawd <benjamin.gaignawd@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics SoC DWM dwivew");
MODUWE_WICENSE("GPW");
