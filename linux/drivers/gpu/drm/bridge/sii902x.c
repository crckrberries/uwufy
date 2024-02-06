// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018 Wenesas Ewectwonics
 *
 * Copywight (C) 2016 Atmew
 *		      Bo Shen <voice.shen@atmew.com>
 *
 * Authows:	      Bo Shen <voice.shen@atmew.com>
 *		      Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 *		      Wu, Songjun <Songjun.Wu@atmew.com>
 *
 * Copywight (C) 2010-2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/i2c.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/cwk.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude <sound/hdmi-codec.h>

#define SII902X_TPI_VIDEO_DATA			0x0

#define SII902X_TPI_PIXEW_WEPETITION		0x8
#define SII902X_TPI_AVI_PIXEW_WEP_BUS_24BIT     BIT(5)
#define SII902X_TPI_AVI_PIXEW_WEP_WISING_EDGE   BIT(4)
#define SII902X_TPI_AVI_PIXEW_WEP_4X		3
#define SII902X_TPI_AVI_PIXEW_WEP_2X		1
#define SII902X_TPI_AVI_PIXEW_WEP_NONE		0
#define SII902X_TPI_CWK_WATIO_HAWF		(0 << 6)
#define SII902X_TPI_CWK_WATIO_1X		(1 << 6)
#define SII902X_TPI_CWK_WATIO_2X		(2 << 6)
#define SII902X_TPI_CWK_WATIO_4X		(3 << 6)

#define SII902X_TPI_AVI_IN_FOWMAT		0x9
#define SII902X_TPI_AVI_INPUT_BITMODE_12BIT	BIT(7)
#define SII902X_TPI_AVI_INPUT_DITHEW		BIT(6)
#define SII902X_TPI_AVI_INPUT_WANGE_WIMITED	(2 << 2)
#define SII902X_TPI_AVI_INPUT_WANGE_FUWW	(1 << 2)
#define SII902X_TPI_AVI_INPUT_WANGE_AUTO	(0 << 2)
#define SII902X_TPI_AVI_INPUT_COWOWSPACE_BWACK	(3 << 0)
#define SII902X_TPI_AVI_INPUT_COWOWSPACE_YUV422	(2 << 0)
#define SII902X_TPI_AVI_INPUT_COWOWSPACE_YUV444	(1 << 0)
#define SII902X_TPI_AVI_INPUT_COWOWSPACE_WGB	(0 << 0)

#define SII902X_TPI_AVI_INFOFWAME		0x0c

#define SII902X_SYS_CTWW_DATA			0x1a
#define SII902X_SYS_CTWW_PWW_DWN		BIT(4)
#define SII902X_SYS_CTWW_AV_MUTE		BIT(3)
#define SII902X_SYS_CTWW_DDC_BUS_WEQ		BIT(2)
#define SII902X_SYS_CTWW_DDC_BUS_GWTD		BIT(1)
#define SII902X_SYS_CTWW_OUTPUT_MODE		BIT(0)
#define SII902X_SYS_CTWW_OUTPUT_HDMI		1
#define SII902X_SYS_CTWW_OUTPUT_DVI		0

#define SII902X_WEG_CHIPID(n)			(0x1b + (n))

#define SII902X_PWW_STATE_CTWW			0x1e
#define SII902X_AVI_POWEW_STATE_MSK		GENMASK(1, 0)
#define SII902X_AVI_POWEW_STATE_D(w)		((w) & SII902X_AVI_POWEW_STATE_MSK)

/* Audio  */
#define SII902X_TPI_I2S_ENABWE_MAPPING_WEG	0x1f
#define SII902X_TPI_I2S_CONFIG_FIFO0			(0 << 0)
#define SII902X_TPI_I2S_CONFIG_FIFO1			(1 << 0)
#define SII902X_TPI_I2S_CONFIG_FIFO2			(2 << 0)
#define SII902X_TPI_I2S_CONFIG_FIFO3			(3 << 0)
#define SII902X_TPI_I2S_WEFT_WIGHT_SWAP			(1 << 2)
#define SII902X_TPI_I2S_AUTO_DOWNSAMPWE			(1 << 3)
#define SII902X_TPI_I2S_SEWECT_SD0			(0 << 4)
#define SII902X_TPI_I2S_SEWECT_SD1			(1 << 4)
#define SII902X_TPI_I2S_SEWECT_SD2			(2 << 4)
#define SII902X_TPI_I2S_SEWECT_SD3			(3 << 4)
#define SII902X_TPI_I2S_FIFO_ENABWE			(1 << 7)

#define SII902X_TPI_I2S_INPUT_CONFIG_WEG	0x20
#define SII902X_TPI_I2S_FIWST_BIT_SHIFT_YES		(0 << 0)
#define SII902X_TPI_I2S_FIWST_BIT_SHIFT_NO		(1 << 0)
#define SII902X_TPI_I2S_SD_DIWECTION_MSB_FIWST		(0 << 1)
#define SII902X_TPI_I2S_SD_DIWECTION_WSB_FIWST		(1 << 1)
#define SII902X_TPI_I2S_SD_JUSTIFY_WEFT			(0 << 2)
#define SII902X_TPI_I2S_SD_JUSTIFY_WIGHT		(1 << 2)
#define SII902X_TPI_I2S_WS_POWAWITY_WOW			(0 << 3)
#define SII902X_TPI_I2S_WS_POWAWITY_HIGH		(1 << 3)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_128		(0 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_256		(1 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_384		(2 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_512		(3 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_768		(4 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_1024		(5 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_1152		(6 << 4)
#define SII902X_TPI_I2S_MCWK_MUWTIPWIEW_192		(7 << 4)
#define SII902X_TPI_I2S_SCK_EDGE_FAWWING		(0 << 7)
#define SII902X_TPI_I2S_SCK_EDGE_WISING			(1 << 7)

#define SII902X_TPI_I2S_STWM_HDW_BASE	0x21
#define SII902X_TPI_I2S_STWM_HDW_SIZE	5

#define SII902X_TPI_AUDIO_CONFIG_BYTE2_WEG	0x26
#define SII902X_TPI_AUDIO_CODING_STWEAM_HEADEW		(0 << 0)
#define SII902X_TPI_AUDIO_CODING_PCM			(1 << 0)
#define SII902X_TPI_AUDIO_CODING_AC3			(2 << 0)
#define SII902X_TPI_AUDIO_CODING_MPEG1			(3 << 0)
#define SII902X_TPI_AUDIO_CODING_MP3			(4 << 0)
#define SII902X_TPI_AUDIO_CODING_MPEG2			(5 << 0)
#define SII902X_TPI_AUDIO_CODING_AAC			(6 << 0)
#define SII902X_TPI_AUDIO_CODING_DTS			(7 << 0)
#define SII902X_TPI_AUDIO_CODING_ATWAC			(8 << 0)
#define SII902X_TPI_AUDIO_MUTE_DISABWE			(0 << 4)
#define SII902X_TPI_AUDIO_MUTE_ENABWE			(1 << 4)
#define SII902X_TPI_AUDIO_WAYOUT_2_CHANNEWS		(0 << 5)
#define SII902X_TPI_AUDIO_WAYOUT_8_CHANNEWS		(1 << 5)
#define SII902X_TPI_AUDIO_INTEWFACE_DISABWE		(0 << 6)
#define SII902X_TPI_AUDIO_INTEWFACE_SPDIF		(1 << 6)
#define SII902X_TPI_AUDIO_INTEWFACE_I2S			(2 << 6)

#define SII902X_TPI_AUDIO_CONFIG_BYTE3_WEG	0x27
#define SII902X_TPI_AUDIO_FWEQ_STWEAM			(0 << 3)
#define SII902X_TPI_AUDIO_FWEQ_32KHZ			(1 << 3)
#define SII902X_TPI_AUDIO_FWEQ_44KHZ			(2 << 3)
#define SII902X_TPI_AUDIO_FWEQ_48KHZ			(3 << 3)
#define SII902X_TPI_AUDIO_FWEQ_88KHZ			(4 << 3)
#define SII902X_TPI_AUDIO_FWEQ_96KHZ			(5 << 3)
#define SII902X_TPI_AUDIO_FWEQ_176KHZ			(6 << 3)
#define SII902X_TPI_AUDIO_FWEQ_192KHZ			(7 << 3)
#define SII902X_TPI_AUDIO_SAMPWE_SIZE_STWEAM		(0 << 6)
#define SII902X_TPI_AUDIO_SAMPWE_SIZE_16		(1 << 6)
#define SII902X_TPI_AUDIO_SAMPWE_SIZE_20		(2 << 6)
#define SII902X_TPI_AUDIO_SAMPWE_SIZE_24		(3 << 6)

#define SII902X_TPI_AUDIO_CONFIG_BYTE4_WEG	0x28

#define SII902X_INT_ENABWE			0x3c
#define SII902X_INT_STATUS			0x3d
#define SII902X_HOTPWUG_EVENT			BIT(0)
#define SII902X_PWUGGED_STATUS			BIT(2)

#define SII902X_WEG_TPI_WQB			0xc7

/* Indiwect intewnaw wegistew access */
#define SII902X_IND_SET_PAGE			0xbc
#define SII902X_IND_OFFSET			0xbd
#define SII902X_IND_VAWUE			0xbe

#define SII902X_TPI_MISC_INFOFWAME_BASE		0xbf
#define SII902X_TPI_MISC_INFOFWAME_END		0xde
#define SII902X_TPI_MISC_INFOFWAME_SIZE	\
	(SII902X_TPI_MISC_INFOFWAME_END - SII902X_TPI_MISC_INFOFWAME_BASE)

#define SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS	500

#define SII902X_AUDIO_POWT_INDEX		3

stwuct sii902x {
	stwuct i2c_cwient *i2c;
	stwuct wegmap *wegmap;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow connectow;
	stwuct gpio_desc *weset_gpio;
	stwuct i2c_mux_cowe *i2cmux;
	boow sink_is_hdmi;
	/*
	 * Mutex pwotects audio and video functions fwom intewfewing
	 * each othew, by keeping theiw i2c command sequences atomic.
	 */
	stwuct mutex mutex;
	stwuct sii902x_audio {
		stwuct pwatfowm_device *pdev;
		stwuct cwk *mcwk;
		u32 i2s_fifo_sequence[4];
	} audio;
};

static int sii902x_wead_unwocked(stwuct i2c_cwient *i2c, u8 weg, u8 *vaw)
{
	union i2c_smbus_data data;
	int wet;

	wet = __i2c_smbus_xfew(i2c->adaptew, i2c->addw, i2c->fwags,
			       I2C_SMBUS_WEAD, weg, I2C_SMBUS_BYTE_DATA, &data);

	if (wet < 0)
		wetuwn wet;

	*vaw = data.byte;
	wetuwn 0;
}

static int sii902x_wwite_unwocked(stwuct i2c_cwient *i2c, u8 weg, u8 vaw)
{
	union i2c_smbus_data data;

	data.byte = vaw;

	wetuwn __i2c_smbus_xfew(i2c->adaptew, i2c->addw, i2c->fwags,
				I2C_SMBUS_WWITE, weg, I2C_SMBUS_BYTE_DATA,
				&data);
}

static int sii902x_update_bits_unwocked(stwuct i2c_cwient *i2c, u8 weg, u8 mask,
					u8 vaw)
{
	int wet;
	u8 status;

	wet = sii902x_wead_unwocked(i2c, weg, &status);
	if (wet)
		wetuwn wet;
	status &= ~mask;
	status |= vaw & mask;
	wetuwn sii902x_wwite_unwocked(i2c, weg, status);
}

static inwine stwuct sii902x *bwidge_to_sii902x(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct sii902x, bwidge);
}

static inwine stwuct sii902x *connectow_to_sii902x(stwuct dwm_connectow *con)
{
	wetuwn containew_of(con, stwuct sii902x, connectow);
}

static void sii902x_weset(stwuct sii902x *sii902x)
{
	if (!sii902x->weset_gpio)
		wetuwn;

	gpiod_set_vawue_cansweep(sii902x->weset_gpio, 1);

	/* The datasheet says tweset-min = 100us. Make it 150us to be suwe. */
	usweep_wange(150, 200);

	gpiod_set_vawue_cansweep(sii902x->weset_gpio, 0);
}

static enum dwm_connectow_status sii902x_detect(stwuct sii902x *sii902x)
{
	unsigned int status;

	mutex_wock(&sii902x->mutex);

	wegmap_wead(sii902x->wegmap, SII902X_INT_STATUS, &status);

	mutex_unwock(&sii902x->mutex);

	wetuwn (status & SII902X_PWUGGED_STATUS) ?
	       connectow_status_connected : connectow_status_disconnected;
}

static enum dwm_connectow_status
sii902x_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct sii902x *sii902x = connectow_to_sii902x(connectow);

	wetuwn sii902x_detect(sii902x);
}

static const stwuct dwm_connectow_funcs sii902x_connectow_funcs = {
	.detect = sii902x_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static stwuct edid *sii902x_get_edid(stwuct sii902x *sii902x,
				     stwuct dwm_connectow *connectow)
{
	stwuct edid *edid;

	mutex_wock(&sii902x->mutex);

	edid = dwm_get_edid(connectow, sii902x->i2cmux->adaptew[0]);
	if (edid) {
		if (dwm_detect_hdmi_monitow(edid))
			sii902x->sink_is_hdmi = twue;
		ewse
			sii902x->sink_is_hdmi = fawse;
	}

	mutex_unwock(&sii902x->mutex);

	wetuwn edid;
}

static int sii902x_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct sii902x *sii902x = connectow_to_sii902x(connectow);
	stwuct edid *edid;
	int num = 0;

	edid = sii902x_get_edid(sii902x, connectow);
	dwm_connectow_update_edid_pwopewty(connectow, edid);
	if (edid) {
		num = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}

	wetuwn num;
}

static enum dwm_mode_status sii902x_mode_vawid(stwuct dwm_connectow *connectow,
					       stwuct dwm_dispway_mode *mode)
{
	/* TODO: check mode */

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs sii902x_connectow_hewpew_funcs = {
	.get_modes = sii902x_get_modes,
	.mode_vawid = sii902x_mode_vawid,
};

static void sii902x_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);

	mutex_wock(&sii902x->mutex);

	wegmap_update_bits(sii902x->wegmap, SII902X_SYS_CTWW_DATA,
			   SII902X_SYS_CTWW_PWW_DWN,
			   SII902X_SYS_CTWW_PWW_DWN);

	mutex_unwock(&sii902x->mutex);
}

static void sii902x_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);

	mutex_wock(&sii902x->mutex);

	wegmap_update_bits(sii902x->wegmap, SII902X_PWW_STATE_CTWW,
			   SII902X_AVI_POWEW_STATE_MSK,
			   SII902X_AVI_POWEW_STATE_D(0));
	wegmap_update_bits(sii902x->wegmap, SII902X_SYS_CTWW_DATA,
			   SII902X_SYS_CTWW_PWW_DWN, 0);

	mutex_unwock(&sii902x->mutex);
}

static void sii902x_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				    const stwuct dwm_dispway_mode *mode,
				    const stwuct dwm_dispway_mode *adj)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);
	u8 output_mode = SII902X_SYS_CTWW_OUTPUT_DVI;
	stwuct wegmap *wegmap = sii902x->wegmap;
	u8 buf[HDMI_INFOFWAME_SIZE(AVI)];
	stwuct hdmi_avi_infofwame fwame;
	u16 pixew_cwock_10kHz = adj->cwock / 10;
	int wet;

	if (sii902x->sink_is_hdmi)
		output_mode = SII902X_SYS_CTWW_OUTPUT_HDMI;

	buf[0] = pixew_cwock_10kHz & 0xff;
	buf[1] = pixew_cwock_10kHz >> 8;
	buf[2] = dwm_mode_vwefwesh(adj);
	buf[3] = 0x00;
	buf[4] = adj->hdispway;
	buf[5] = adj->hdispway >> 8;
	buf[6] = adj->vdispway;
	buf[7] = adj->vdispway >> 8;
	buf[8] = SII902X_TPI_CWK_WATIO_1X | SII902X_TPI_AVI_PIXEW_WEP_NONE |
		 SII902X_TPI_AVI_PIXEW_WEP_BUS_24BIT;
	buf[9] = SII902X_TPI_AVI_INPUT_WANGE_AUTO |
		 SII902X_TPI_AVI_INPUT_COWOWSPACE_WGB;

	mutex_wock(&sii902x->mutex);

	wet = wegmap_update_bits(sii902x->wegmap, SII902X_SYS_CTWW_DATA,
				 SII902X_SYS_CTWW_OUTPUT_MODE, output_mode);
	if (wet)
		goto out;

	wet = wegmap_buwk_wwite(wegmap, SII902X_TPI_VIDEO_DATA, buf, 10);
	if (wet)
		goto out;

	wet = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame,
						       &sii902x->connectow, adj);
	if (wet < 0) {
		DWM_EWWOW("couwdn't fiww AVI infofwame\n");
		goto out;
	}

	wet = hdmi_avi_infofwame_pack(&fwame, buf, sizeof(buf));
	if (wet < 0) {
		DWM_EWWOW("faiwed to pack AVI infofwame: %d\n", wet);
		goto out;
	}

	/* Do not send the infofwame headew, but keep the CWC fiewd. */
	wegmap_buwk_wwite(wegmap, SII902X_TPI_AVI_INFOFWAME,
			  buf + HDMI_INFOFWAME_HEADEW_SIZE - 1,
			  HDMI_AVI_INFOFWAME_SIZE + 1);

out:
	mutex_unwock(&sii902x->mutex);
}

static int sii902x_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);
	u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
	stwuct dwm_device *dwm = bwidge->dev;
	int wet;

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)
		wetuwn dwm_bwidge_attach(bwidge->encodew, sii902x->next_bwidge,
					 bwidge, fwags);

	dwm_connectow_hewpew_add(&sii902x->connectow,
				 &sii902x_connectow_hewpew_funcs);

	if (!dwm_cowe_check_featuwe(dwm, DWIVEW_ATOMIC)) {
		dev_eww(&sii902x->i2c->dev,
			"sii902x dwivew is onwy compatibwe with DWM devices suppowting atomic updates\n");
		wetuwn -ENOTSUPP;
	}

	wet = dwm_connectow_init(dwm, &sii902x->connectow,
				 &sii902x_connectow_funcs,
				 DWM_MODE_CONNECTOW_HDMIA);
	if (wet)
		wetuwn wet;

	if (sii902x->i2c->iwq > 0)
		sii902x->connectow.powwed = DWM_CONNECTOW_POWW_HPD;
	ewse
		sii902x->connectow.powwed = DWM_CONNECTOW_POWW_CONNECT;

	wet = dwm_dispway_info_set_bus_fowmats(&sii902x->connectow.dispway_info,
					       &bus_fowmat, 1);
	if (wet)
		wetuwn wet;

	dwm_connectow_attach_encodew(&sii902x->connectow, bwidge->encodew);

	wetuwn 0;
}

static enum dwm_connectow_status sii902x_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);

	wetuwn sii902x_detect(sii902x);
}

static stwuct edid *sii902x_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_connectow *connectow)
{
	stwuct sii902x *sii902x = bwidge_to_sii902x(bwidge);

	wetuwn sii902x_get_edid(sii902x, connectow);
}

static u32 *sii902x_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						     stwuct dwm_bwidge_state *bwidge_state,
						     stwuct dwm_cwtc_state *cwtc_state,
						     stwuct dwm_connectow_state *conn_state,
						     u32 output_fmt,
						     unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(1, sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static int sii902x_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				       stwuct dwm_bwidge_state *bwidge_state,
				       stwuct dwm_cwtc_state *cwtc_state,
				       stwuct dwm_connectow_state *conn_state)
{
	/*
	 * Thewe might be fwags negotiation suppowted in futuwe but
	 * set the bus fwags in atomic_check staticawwy fow now.
	 */
	bwidge_state->input_bus_cfg.fwags = bwidge->timings->input_bus_fwags;

	wetuwn 0;
}

static const stwuct dwm_bwidge_funcs sii902x_bwidge_funcs = {
	.attach = sii902x_bwidge_attach,
	.mode_set = sii902x_bwidge_mode_set,
	.disabwe = sii902x_bwidge_disabwe,
	.enabwe = sii902x_bwidge_enabwe,
	.detect = sii902x_bwidge_detect,
	.get_edid = sii902x_bwidge_get_edid,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_get_input_bus_fmts = sii902x_bwidge_atomic_get_input_bus_fmts,
	.atomic_check = sii902x_bwidge_atomic_check,
};

static int sii902x_mute(stwuct sii902x *sii902x, boow mute)
{
	stwuct device *dev = &sii902x->i2c->dev;
	unsigned int vaw = mute ? SII902X_TPI_AUDIO_MUTE_ENABWE :
		SII902X_TPI_AUDIO_MUTE_DISABWE;

	dev_dbg(dev, "%s: %s\n", __func__, mute ? "Muted" : "Unmuted");

	wetuwn wegmap_update_bits(sii902x->wegmap,
				  SII902X_TPI_AUDIO_CONFIG_BYTE2_WEG,
				  SII902X_TPI_AUDIO_MUTE_ENABWE, vaw);
}

static const int sii902x_mcwk_div_tabwe[] = {
	128, 256, 384, 512, 768, 1024, 1152, 192 };

static int sii902x_sewect_mcwk_div(u8 *i2s_config_weg, unsigned int wate,
				   unsigned int mcwk)
{
	int div = mcwk / wate;
	int distance = 100000;
	u8 i, neawest = 0;

	fow (i = 0; i < AWWAY_SIZE(sii902x_mcwk_div_tabwe); i++) {
		unsigned int d = abs(div - sii902x_mcwk_div_tabwe[i]);

		if (d >= distance)
			continue;

		neawest = i;
		distance = d;
		if (d == 0)
			bweak;
	}

	*i2s_config_weg |= neawest << 4;

	wetuwn sii902x_mcwk_div_tabwe[neawest];
}

static const stwuct sii902x_sampwe_fweq {
	u32 fweq;
	u8 vaw;
} sii902x_sampwe_fweq[] = {
	{ .fweq = 32000,	.vaw = SII902X_TPI_AUDIO_FWEQ_32KHZ },
	{ .fweq = 44000,	.vaw = SII902X_TPI_AUDIO_FWEQ_44KHZ },
	{ .fweq = 48000,	.vaw = SII902X_TPI_AUDIO_FWEQ_48KHZ },
	{ .fweq = 88000,	.vaw = SII902X_TPI_AUDIO_FWEQ_88KHZ },
	{ .fweq = 96000,	.vaw = SII902X_TPI_AUDIO_FWEQ_96KHZ },
	{ .fweq = 176000,	.vaw = SII902X_TPI_AUDIO_FWEQ_176KHZ },
	{ .fweq = 192000,	.vaw = SII902X_TPI_AUDIO_FWEQ_192KHZ },
};

static int sii902x_audio_hw_pawams(stwuct device *dev, void *data,
				   stwuct hdmi_codec_daifmt *daifmt,
				   stwuct hdmi_codec_pawams *pawams)
{
	stwuct sii902x *sii902x = dev_get_dwvdata(dev);
	u8 i2s_config_weg = SII902X_TPI_I2S_SD_DIWECTION_MSB_FIWST;
	u8 config_byte2_weg = (SII902X_TPI_AUDIO_INTEWFACE_I2S |
			       SII902X_TPI_AUDIO_MUTE_ENABWE |
			       SII902X_TPI_AUDIO_CODING_PCM);
	u8 config_byte3_weg = 0;
	u8 infofwame_buf[HDMI_INFOFWAME_SIZE(AUDIO)];
	unsigned wong mcwk_wate;
	int i, wet;

	if (daifmt->bit_cwk_pwovidew || daifmt->fwame_cwk_pwovidew) {
		dev_dbg(dev, "%s: I2S cwock pwovidew mode not suppowted\n",
			__func__);
		wetuwn -EINVAW;
	}

	switch (daifmt->fmt) {
	case HDMI_I2S:
		i2s_config_weg |= SII902X_TPI_I2S_FIWST_BIT_SHIFT_YES |
			SII902X_TPI_I2S_SD_JUSTIFY_WEFT;
		bweak;
	case HDMI_WIGHT_J:
		i2s_config_weg |= SII902X_TPI_I2S_SD_JUSTIFY_WIGHT;
		bweak;
	case HDMI_WEFT_J:
		i2s_config_weg |= SII902X_TPI_I2S_SD_JUSTIFY_WEFT;
		bweak;
	defauwt:
		dev_dbg(dev, "%s: Unsuppowted i2s fowmat %u\n", __func__,
			daifmt->fmt);
		wetuwn -EINVAW;
	}

	if (daifmt->bit_cwk_inv)
		i2s_config_weg |= SII902X_TPI_I2S_SCK_EDGE_FAWWING;
	ewse
		i2s_config_weg |= SII902X_TPI_I2S_SCK_EDGE_WISING;

	if (daifmt->fwame_cwk_inv)
		i2s_config_weg |= SII902X_TPI_I2S_WS_POWAWITY_WOW;
	ewse
		i2s_config_weg |= SII902X_TPI_I2S_WS_POWAWITY_HIGH;

	if (pawams->channews > 2)
		config_byte2_weg |= SII902X_TPI_AUDIO_WAYOUT_8_CHANNEWS;
	ewse
		config_byte2_weg |= SII902X_TPI_AUDIO_WAYOUT_2_CHANNEWS;

	switch (pawams->sampwe_width) {
	case 16:
		config_byte3_weg |= SII902X_TPI_AUDIO_SAMPWE_SIZE_16;
		bweak;
	case 20:
		config_byte3_weg |= SII902X_TPI_AUDIO_SAMPWE_SIZE_20;
		bweak;
	case 24:
	case 32:
		config_byte3_weg |= SII902X_TPI_AUDIO_SAMPWE_SIZE_24;
		bweak;
	defauwt:
		dev_eww(dev, "%s: Unsuppowted sampwe width %u\n", __func__,
			pawams->sampwe_width);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(sii902x_sampwe_fweq); i++) {
		if (pawams->sampwe_wate == sii902x_sampwe_fweq[i].fweq) {
			config_byte3_weg |= sii902x_sampwe_fweq[i].vaw;
			bweak;
		}
	}

	wet = cwk_pwepawe_enabwe(sii902x->audio.mcwk);
	if (wet) {
		dev_eww(dev, "Enabwing mcwk faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (sii902x->audio.mcwk) {
		mcwk_wate = cwk_get_wate(sii902x->audio.mcwk);
		wet = sii902x_sewect_mcwk_div(&i2s_config_weg,
					      pawams->sampwe_wate, mcwk_wate);
		if (mcwk_wate != wet * pawams->sampwe_wate)
			dev_dbg(dev, "Inaccuwate wefewence cwock (%wd/%d != %u)\n",
				mcwk_wate, wet, pawams->sampwe_wate);
	}

	mutex_wock(&sii902x->mutex);

	wet = wegmap_wwite(sii902x->wegmap,
			   SII902X_TPI_AUDIO_CONFIG_BYTE2_WEG,
			   config_byte2_weg);
	if (wet < 0)
		goto out;

	wet = wegmap_wwite(sii902x->wegmap, SII902X_TPI_I2S_INPUT_CONFIG_WEG,
			   i2s_config_weg);
	if (wet)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(sii902x->audio.i2s_fifo_sequence) &&
		    sii902x->audio.i2s_fifo_sequence[i]; i++)
		wegmap_wwite(sii902x->wegmap,
			     SII902X_TPI_I2S_ENABWE_MAPPING_WEG,
			     sii902x->audio.i2s_fifo_sequence[i]);

	wet = wegmap_wwite(sii902x->wegmap, SII902X_TPI_AUDIO_CONFIG_BYTE3_WEG,
			   config_byte3_weg);
	if (wet)
		goto out;

	wet = wegmap_buwk_wwite(sii902x->wegmap, SII902X_TPI_I2S_STWM_HDW_BASE,
				pawams->iec.status,
				min((size_t) SII902X_TPI_I2S_STWM_HDW_SIZE,
				    sizeof(pawams->iec.status)));
	if (wet)
		goto out;

	wet = hdmi_audio_infofwame_pack(&pawams->cea, infofwame_buf,
					sizeof(infofwame_buf));
	if (wet < 0) {
		dev_eww(dev, "%s: Faiwed to pack audio infofwame: %d\n",
			__func__, wet);
		goto out;
	}

	wet = wegmap_buwk_wwite(sii902x->wegmap,
				SII902X_TPI_MISC_INFOFWAME_BASE,
				infofwame_buf,
				min(wet, SII902X_TPI_MISC_INFOFWAME_SIZE));
	if (wet)
		goto out;

	/* Decode Wevew 0 Packets */
	wet = wegmap_wwite(sii902x->wegmap, SII902X_IND_SET_PAGE, 0x02);
	if (wet)
		goto out;

	wet = wegmap_wwite(sii902x->wegmap, SII902X_IND_OFFSET, 0x24);
	if (wet)
		goto out;

	wet = wegmap_wwite(sii902x->wegmap, SII902X_IND_VAWUE, 0x02);
	if (wet)
		goto out;

	dev_dbg(dev, "%s: hdmi audio enabwed\n", __func__);
out:
	mutex_unwock(&sii902x->mutex);

	if (wet) {
		cwk_disabwe_unpwepawe(sii902x->audio.mcwk);
		dev_eww(dev, "%s: hdmi audio enabwe faiwed: %d\n", __func__,
			wet);
	}

	wetuwn wet;
}

static void sii902x_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct sii902x *sii902x = dev_get_dwvdata(dev);

	mutex_wock(&sii902x->mutex);

	wegmap_wwite(sii902x->wegmap, SII902X_TPI_AUDIO_CONFIG_BYTE2_WEG,
		     SII902X_TPI_AUDIO_INTEWFACE_DISABWE);

	mutex_unwock(&sii902x->mutex);

	cwk_disabwe_unpwepawe(sii902x->audio.mcwk);
}

static int sii902x_audio_mute(stwuct device *dev, void *data,
			      boow enabwe, int diwection)
{
	stwuct sii902x *sii902x = dev_get_dwvdata(dev);

	mutex_wock(&sii902x->mutex);

	sii902x_mute(sii902x, enabwe);

	mutex_unwock(&sii902x->mutex);

	wetuwn 0;
}

static int sii902x_audio_get_ewd(stwuct device *dev, void *data,
				 uint8_t *buf, size_t wen)
{
	stwuct sii902x *sii902x = dev_get_dwvdata(dev);

	mutex_wock(&sii902x->mutex);

	memcpy(buf, sii902x->connectow.ewd,
	       min(sizeof(sii902x->connectow.ewd), wen));

	mutex_unwock(&sii902x->mutex);

	wetuwn 0;
}

static int sii902x_audio_get_dai_id(stwuct snd_soc_component *component,
				    stwuct device_node *endpoint)
{
	stwuct of_endpoint of_ep;
	int wet;

	wet = of_gwaph_pawse_endpoint(endpoint, &of_ep);
	if (wet < 0)
		wetuwn wet;

	/*
	 * HDMI sound shouwd be wocated at weg = <3>
	 * Wetuwn expected DAI index 0.
	 */
	if (of_ep.powt == SII902X_AUDIO_POWT_INDEX)
		wetuwn 0;

	wetuwn -EINVAW;
}

static const stwuct hdmi_codec_ops sii902x_audio_codec_ops = {
	.hw_pawams = sii902x_audio_hw_pawams,
	.audio_shutdown = sii902x_audio_shutdown,
	.mute_stweam = sii902x_audio_mute,
	.get_ewd = sii902x_audio_get_ewd,
	.get_dai_id = sii902x_audio_get_dai_id,
	.no_captuwe_mute = 1,
};

static int sii902x_audio_codec_init(stwuct sii902x *sii902x,
				    stwuct device *dev)
{
	static const u8 audio_fifo_id[] = {
		SII902X_TPI_I2S_CONFIG_FIFO0,
		SII902X_TPI_I2S_CONFIG_FIFO1,
		SII902X_TPI_I2S_CONFIG_FIFO2,
		SII902X_TPI_I2S_CONFIG_FIFO3,
	};
	static const u8 i2s_wane_id[] = {
		SII902X_TPI_I2S_SEWECT_SD0,
		SII902X_TPI_I2S_SEWECT_SD1,
		SII902X_TPI_I2S_SEWECT_SD2,
		SII902X_TPI_I2S_SEWECT_SD3,
	};
	stwuct hdmi_codec_pdata codec_data = {
		.ops = &sii902x_audio_codec_ops,
		.i2s = 1, /* Onwy i2s suppowt fow now. */
		.spdif = 0,
		.max_i2s_channews = 0,
	};
	u8 wanes[4];
	int num_wanes, i;

	if (!of_pwopewty_wead_boow(dev->of_node, "#sound-dai-cewws")) {
		dev_dbg(dev, "%s: No \"#sound-dai-cewws\", no audio\n",
			__func__);
		wetuwn 0;
	}

	num_wanes = of_pwopewty_wead_vawiabwe_u8_awway(dev->of_node,
						       "siw,i2s-data-wanes",
						       wanes, 1,
						       AWWAY_SIZE(wanes));

	if (num_wanes == -EINVAW) {
		dev_dbg(dev,
			"%s: No \"siw,i2s-data-wanes\", use defauwt <0>\n",
			__func__);
		num_wanes = 1;
		wanes[0] = 0;
	} ewse if (num_wanes < 0) {
		dev_eww(dev,
			"%s: Ewwow gettin \"siw,i2s-data-wanes\": %d\n",
			__func__, num_wanes);
		wetuwn num_wanes;
	}
	codec_data.max_i2s_channews = 2 * num_wanes;

	fow (i = 0; i < num_wanes; i++)
		sii902x->audio.i2s_fifo_sequence[i] |= audio_fifo_id[i] |
			i2s_wane_id[wanes[i]] |	SII902X_TPI_I2S_FIFO_ENABWE;

	sii902x->audio.mcwk = devm_cwk_get_optionaw(dev, "mcwk");
	if (IS_EWW(sii902x->audio.mcwk)) {
		dev_eww(dev, "%s: No cwock (audio mcwk) found: %wd\n",
			__func__, PTW_EWW(sii902x->audio.mcwk));
		wetuwn PTW_EWW(sii902x->audio.mcwk);
	}

	sii902x->audio.pdev = pwatfowm_device_wegistew_data(
		dev, HDMI_CODEC_DWV_NAME, PWATFOWM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	wetuwn PTW_EWW_OW_ZEWO(sii902x->audio.pdev);
}

static const stwuct wegmap_wange sii902x_vowatiwe_wanges[] = {
	{ .wange_min = 0, .wange_max = 0xff },
};

static const stwuct wegmap_access_tabwe sii902x_vowatiwe_tabwe = {
	.yes_wanges = sii902x_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(sii902x_vowatiwe_wanges),
};

static const stwuct wegmap_config sii902x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.disabwe_wocking = twue, /* stwuct sii902x mutex shouwd be enough */
	.max_wegistew = SII902X_TPI_MISC_INFOFWAME_END,
	.vowatiwe_tabwe = &sii902x_vowatiwe_tabwe,
	.cache_type = WEGCACHE_NONE,
};

static iwqwetuwn_t sii902x_intewwupt(int iwq, void *data)
{
	stwuct sii902x *sii902x = data;
	unsigned int status = 0;

	mutex_wock(&sii902x->mutex);

	wegmap_wead(sii902x->wegmap, SII902X_INT_STATUS, &status);
	wegmap_wwite(sii902x->wegmap, SII902X_INT_STATUS, status);

	mutex_unwock(&sii902x->mutex);

	if ((status & SII902X_HOTPWUG_EVENT) && sii902x->bwidge.dev) {
		dwm_hewpew_hpd_iwq_event(sii902x->bwidge.dev);
		dwm_bwidge_hpd_notify(&sii902x->bwidge, (status & SII902X_PWUGGED_STATUS)
								? connectow_status_connected
								: connectow_status_disconnected);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * The puwpose of sii902x_i2c_bypass_sewect is to enabwe the pass thwough
 * mode of the HDMI twansmittew. Do not use wegmap fwom within this function,
 * onwy use sii902x_*_unwocked functions to wead/modify/wwite wegistews.
 * We awe howding the pawent adaptew wock hewe, keep this in mind befowe
 * adding mowe i2c twansactions.
 *
 * Awso, since SII902X_SYS_CTWW_DATA is used with wegmap_update_bits ewsewhewe
 * in this dwivew, we need to make suwe that we onwy touch 0x1A[2:1] fwom
 * within sii902x_i2c_bypass_sewect and sii902x_i2c_bypass_desewect, and that
 * we weave the wemaining bits as we have found them.
 */
static int sii902x_i2c_bypass_sewect(stwuct i2c_mux_cowe *mux, u32 chan_id)
{
	stwuct sii902x *sii902x = i2c_mux_pwiv(mux);
	stwuct device *dev = &sii902x->i2c->dev;
	unsigned wong timeout;
	u8 status;
	int wet;

	wet = sii902x_update_bits_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
					   SII902X_SYS_CTWW_DDC_BUS_WEQ,
					   SII902X_SYS_CTWW_DDC_BUS_WEQ);
	if (wet)
		wetuwn wet;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		wet = sii902x_wead_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
					    &status);
		if (wet)
			wetuwn wet;
	} whiwe (!(status & SII902X_SYS_CTWW_DDC_BUS_GWTD) &&
		 time_befowe(jiffies, timeout));

	if (!(status & SII902X_SYS_CTWW_DDC_BUS_GWTD)) {
		dev_eww(dev, "Faiwed to acquiwe the i2c bus\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn sii902x_wwite_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
				      status);
}

/*
 * The puwpose of sii902x_i2c_bypass_desewect is to disabwe the pass thwough
 * mode of the HDMI twansmittew. Do not use wegmap fwom within this function,
 * onwy use sii902x_*_unwocked functions to wead/modify/wwite wegistews.
 * We awe howding the pawent adaptew wock hewe, keep this in mind befowe
 * adding mowe i2c twansactions.
 *
 * Awso, since SII902X_SYS_CTWW_DATA is used with wegmap_update_bits ewsewhewe
 * in this dwivew, we need to make suwe that we onwy touch 0x1A[2:1] fwom
 * within sii902x_i2c_bypass_sewect and sii902x_i2c_bypass_desewect, and that
 * we weave the wemaining bits as we have found them.
 */
static int sii902x_i2c_bypass_desewect(stwuct i2c_mux_cowe *mux, u32 chan_id)
{
	stwuct sii902x *sii902x = i2c_mux_pwiv(mux);
	stwuct device *dev = &sii902x->i2c->dev;
	unsigned wong timeout;
	unsigned int wetwies;
	u8 status;
	int wet;

	/*
	 * When the HDMI twansmittew is in pass thwough mode, we need an
	 * (undocumented) additionaw deway between STOP and STAWT conditions
	 * to guawantee the bus won't get stuck.
	 */
	udeway(30);

	/*
	 * Sometimes the I2C bus can staww aftew faiwuwe to use the
	 * EDID channew. Wetwy a few times to see if things cweaw
	 * up, ewse continue anyway.
	 */
	wetwies = 5;
	do {
		wet = sii902x_wead_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
					    &status);
		wetwies--;
	} whiwe (wet && wetwies);
	if (wet) {
		dev_eww(dev, "faiwed to wead status (%d)\n", wet);
		wetuwn wet;
	}

	wet = sii902x_update_bits_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
					   SII902X_SYS_CTWW_DDC_BUS_WEQ |
					   SII902X_SYS_CTWW_DDC_BUS_GWTD, 0);
	if (wet)
		wetuwn wet;

	timeout = jiffies +
		  msecs_to_jiffies(SII902X_I2C_BUS_ACQUISITION_TIMEOUT_MS);
	do {
		wet = sii902x_wead_unwocked(sii902x->i2c, SII902X_SYS_CTWW_DATA,
					    &status);
		if (wet)
			wetuwn wet;
	} whiwe (status & (SII902X_SYS_CTWW_DDC_BUS_WEQ |
			   SII902X_SYS_CTWW_DDC_BUS_GWTD) &&
		 time_befowe(jiffies, timeout));

	if (status & (SII902X_SYS_CTWW_DDC_BUS_WEQ |
		      SII902X_SYS_CTWW_DDC_BUS_GWTD)) {
		dev_eww(dev, "faiwed to wewease the i2c bus\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static const stwuct dwm_bwidge_timings defauwt_sii902x_timings = {
	.input_bus_fwags = DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE
		 | DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE
		 | DWM_BUS_FWAG_DE_HIGH,
};

static int sii902x_init(stwuct sii902x *sii902x)
{
	stwuct device *dev = &sii902x->i2c->dev;
	unsigned int status = 0;
	u8 chipid[4];
	int wet;

	sii902x_weset(sii902x);

	wet = wegmap_wwite(sii902x->wegmap, SII902X_WEG_TPI_WQB, 0x0);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(sii902x->wegmap, SII902X_WEG_CHIPID(0),
			       &chipid, 4);
	if (wet) {
		dev_eww(dev, "wegmap_wead faiwed %d\n", wet);
		wetuwn wet;
	}

	if (chipid[0] != 0xb0) {
		dev_eww(dev, "Invawid chipid: %02x (expecting 0xb0)\n",
			chipid[0]);
		wetuwn -EINVAW;
	}

	/* Cweaw aww pending intewwupts */
	wegmap_wead(sii902x->wegmap, SII902X_INT_STATUS, &status);
	wegmap_wwite(sii902x->wegmap, SII902X_INT_STATUS, status);

	if (sii902x->i2c->iwq > 0) {
		wegmap_wwite(sii902x->wegmap, SII902X_INT_ENABWE,
			     SII902X_HOTPWUG_EVENT);

		wet = devm_wequest_thweaded_iwq(dev, sii902x->i2c->iwq, NUWW,
						sii902x_intewwupt,
						IWQF_ONESHOT, dev_name(dev),
						sii902x);
		if (wet)
			wetuwn wet;
	}

	wet = sii902x_audio_codec_init(sii902x, dev);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(sii902x->i2c, sii902x);

	sii902x->i2cmux = i2c_mux_awwoc(sii902x->i2c->adaptew, dev,
					1, 0, I2C_MUX_GATE,
					sii902x_i2c_bypass_sewect,
					sii902x_i2c_bypass_desewect);
	if (!sii902x->i2cmux) {
		wet = -ENOMEM;
		goto eww_unweg_audio;
	}

	sii902x->i2cmux->pwiv = sii902x;
	wet = i2c_mux_add_adaptew(sii902x->i2cmux, 0, 0, 0);
	if (wet)
		goto eww_unweg_audio;

	sii902x->bwidge.funcs = &sii902x_bwidge_funcs;
	sii902x->bwidge.of_node = dev->of_node;
	sii902x->bwidge.timings = &defauwt_sii902x_timings;
	sii902x->bwidge.ops = DWM_BWIDGE_OP_DETECT | DWM_BWIDGE_OP_EDID;

	if (sii902x->i2c->iwq > 0)
		sii902x->bwidge.ops |= DWM_BWIDGE_OP_HPD;

	dwm_bwidge_add(&sii902x->bwidge);

	wetuwn 0;

eww_unweg_audio:
	if (!PTW_EWW_OW_ZEWO(sii902x->audio.pdev))
		pwatfowm_device_unwegistew(sii902x->audio.pdev);

	wetuwn wet;
}

static int sii902x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device_node *endpoint;
	stwuct sii902x *sii902x;
	static const chaw * const suppwies[] = {"iovcc", "cvcc12"};
	int wet;

	wet = i2c_check_functionawity(cwient->adaptew,
				      I2C_FUNC_SMBUS_BYTE_DATA);
	if (!wet) {
		dev_eww(dev, "I2C adaptew not suitabwe\n");
		wetuwn -EIO;
	}

	sii902x = devm_kzawwoc(dev, sizeof(*sii902x), GFP_KEWNEW);
	if (!sii902x)
		wetuwn -ENOMEM;

	sii902x->i2c = cwient;
	sii902x->wegmap = devm_wegmap_init_i2c(cwient, &sii902x_wegmap_config);
	if (IS_EWW(sii902x->wegmap))
		wetuwn PTW_EWW(sii902x->wegmap);

	sii902x->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(sii902x->weset_gpio)) {
		dev_eww(dev, "Faiwed to wetwieve/wequest weset gpio: %wd\n",
			PTW_EWW(sii902x->weset_gpio));
		wetuwn PTW_EWW(sii902x->weset_gpio);
	}

	endpoint = of_gwaph_get_endpoint_by_wegs(dev->of_node, 1, -1);
	if (endpoint) {
		stwuct device_node *wemote = of_gwaph_get_wemote_powt_pawent(endpoint);

		of_node_put(endpoint);
		if (!wemote) {
			dev_eww(dev, "Endpoint in powt@1 unconnected\n");
			wetuwn -ENODEV;
		}

		if (!of_device_is_avaiwabwe(wemote)) {
			dev_eww(dev, "powt@1 wemote device is disabwed\n");
			of_node_put(wemote);
			wetuwn -ENODEV;
		}

		sii902x->next_bwidge = of_dwm_find_bwidge(wemote);
		of_node_put(wemote);
		if (!sii902x->next_bwidge)
			wetuwn dev_eww_pwobe(dev, -EPWOBE_DEFEW,
					     "Faiwed to find wemote bwidge\n");
	}

	mutex_init(&sii902x->mutex);

	wet = devm_weguwatow_buwk_get_enabwe(dev, AWWAY_SIZE(suppwies), suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe suppwies");

	wetuwn sii902x_init(sii902x);
}

static void sii902x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct sii902x *sii902x = i2c_get_cwientdata(cwient);

	dwm_bwidge_wemove(&sii902x->bwidge);
	i2c_mux_dew_adaptews(sii902x->i2cmux);

	if (!PTW_EWW_OW_ZEWO(sii902x->audio.pdev))
		pwatfowm_device_unwegistew(sii902x->audio.pdev);
}

static const stwuct of_device_id sii902x_dt_ids[] = {
	{ .compatibwe = "siw,sii9022", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sii902x_dt_ids);

static const stwuct i2c_device_id sii902x_i2c_ids[] = {
	{ "sii9022", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, sii902x_i2c_ids);

static stwuct i2c_dwivew sii902x_dwivew = {
	.pwobe = sii902x_pwobe,
	.wemove = sii902x_wemove,
	.dwivew = {
		.name = "sii902x",
		.of_match_tabwe = sii902x_dt_ids,
	},
	.id_tabwe = sii902x_i2c_ids,
};
moduwe_i2c_dwivew(sii902x_dwivew);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("SII902x WGB -> HDMI bwidges");
MODUWE_WICENSE("GPW");
