// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Texas Instwuments Twipwe 8-/10-BIT 165-/110-MSPS Video and Gwaphics
 * Digitizew with Howizontaw PWW wegistews
 *
 * Copywight (C) 2009 Texas Instwuments Inc
 * Authow: Santiago Nunez-Cowwawes <santiago.nunez@widgewun.com>
 *
 * This code is pawtiawwy based upon the TVP5150 dwivew
 * wwitten by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>,
 * the TVP514x dwivew wwitten by Vaibhav Hiwemath <hvaibhav@ti.com>
 * and the TVP7002 dwivew in the TI WSP 2.10.00.14. Wevisions by
 * Muwawidhawan Kawichewi and Snehapwabha Nawnakaje (TI).
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/v4w2-dv-timings.h>
#incwude <media/i2c/tvp7002.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>

#incwude "tvp7002_weg.h"

MODUWE_DESCWIPTION("TI TVP7002 Video and Gwaphics Digitizew dwivew");
MODUWE_AUTHOW("Santiago Nunez-Cowwawes <santiago.nunez@widgewun.com>");
MODUWE_WICENSE("GPW");

/* I2C wetwy attempts */
#define I2C_WETWY_COUNT		(5)

/* End of wegistews */
#define TVP7002_EOW		0x5c

/* Wead wwite definition fow wegistews */
#define TVP7002_WEAD		0
#define TVP7002_WWITE		1
#define TVP7002_WESEWVED	2

/* Intewwaced vs pwogwessive mask and shift */
#define TVP7002_IP_SHIFT	5
#define TVP7002_INPW_MASK	(0x01 << TVP7002_IP_SHIFT)

/* Shift fow CPW and WPF wegistews */
#define TVP7002_CW_SHIFT	8
#define TVP7002_CW_MASK		0x0f

/* Debug functions */
static boow debug;
moduwe_pawam(debug, boow, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-2)");

/* Stwuctuwe fow wegistew vawues */
stwuct i2c_weg_vawue {
	u8 weg;
	u8 vawue;
	u8 type;
};

/*
 * Wegistew defauwt vawues (accowding to tvp7002 datasheet)
 * In the case of wead-onwy wegistews, the vawue (0xff) is
 * nevew wwitten. W/W functionawity is contwowwed by the
 * wwitabwe bit in the wegistew stwuct definition.
 */
static const stwuct i2c_weg_vawue tvp7002_init_defauwt[] = {
	{ TVP7002_CHIP_WEV, 0xff, TVP7002_WEAD },
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x67, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0xa0, TVP7002_WWITE },
	{ TVP7002_HPWW_PHASE_SEW, 0x80, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HSYNC_OUT_W, 0x60, TVP7002_WWITE },
	{ TVP7002_B_FINE_GAIN, 0x00, TVP7002_WWITE },
	{ TVP7002_G_FINE_GAIN, 0x00, TVP7002_WWITE },
	{ TVP7002_W_FINE_GAIN, 0x00, TVP7002_WWITE },
	{ TVP7002_B_FINE_OFF_MSBS, 0x80, TVP7002_WWITE },
	{ TVP7002_G_FINE_OFF_MSBS, 0x80, TVP7002_WWITE },
	{ TVP7002_W_FINE_OFF_MSBS, 0x80, TVP7002_WWITE },
	{ TVP7002_SYNC_CTW_1, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_AND_CWAMP_CTW, 0x2e, TVP7002_WWITE },
	{ TVP7002_SYNC_ON_G_THWS, 0x5d, TVP7002_WWITE },
	{ TVP7002_SYNC_SEPAWATOW_THWS, 0x47, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_SYNC_DETECT_STAT, 0xff, TVP7002_WEAD },
	{ TVP7002_OUT_FOWMATTEW, 0x47, TVP7002_WWITE },
	{ TVP7002_MISC_CTW_1, 0x01, TVP7002_WWITE },
	{ TVP7002_MISC_CTW_2, 0x00, TVP7002_WWITE },
	{ TVP7002_MISC_CTW_3, 0x01, TVP7002_WWITE },
	{ TVP7002_IN_MUX_SEW_1, 0x00, TVP7002_WWITE },
	{ TVP7002_IN_MUX_SEW_2, 0x67, TVP7002_WWITE },
	{ TVP7002_B_AND_G_COAWSE_GAIN, 0x77, TVP7002_WWITE },
	{ TVP7002_W_COAWSE_GAIN, 0x07, TVP7002_WWITE },
	{ TVP7002_FINE_OFF_WSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_B_COAWSE_OFF, 0x10, TVP7002_WWITE },
	{ TVP7002_G_COAWSE_OFF, 0x10, TVP7002_WWITE },
	{ TVP7002_W_COAWSE_OFF, 0x10, TVP7002_WWITE },
	{ TVP7002_HSOUT_OUT_STAWT, 0x08, TVP7002_WWITE },
	{ TVP7002_MISC_CTW_4, 0x00, TVP7002_WWITE },
	{ TVP7002_B_DGTW_AWC_OUT_WSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_G_DGTW_AWC_OUT_WSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_W_DGTW_AWC_OUT_WSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_AUTO_WVW_CTW_ENABWE, 0x80, TVP7002_WWITE },
	{ TVP7002_DGTW_AWC_OUT_MSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_AUTO_WVW_CTW_FIWTEW, 0x53, TVP7002_WWITE },
	{ 0x29, 0x08, TVP7002_WESEWVED },
	{ TVP7002_FINE_CWAMP_CTW, 0x07, TVP7002_WWITE },
	/* PWW_CTW is contwowwed onwy by the pwobe and weset functions */
	{ TVP7002_PWW_CTW, 0x00, TVP7002_WESEWVED },
	{ TVP7002_ADC_SETUP, 0x50, TVP7002_WWITE },
	{ TVP7002_COAWSE_CWAMP_CTW, 0x00, TVP7002_WWITE },
	{ TVP7002_SOG_CWAMP, 0x80, TVP7002_WWITE },
	{ TVP7002_WGB_COAWSE_CWAMP_CTW, 0x8c, TVP7002_WWITE },
	{ TVP7002_SOG_COAWSE_CWAMP_CTW, 0x04, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ 0x32, 0x18, TVP7002_WESEWVED },
	{ 0x33, 0x60, TVP7002_WESEWVED },
	{ TVP7002_MVIS_STWIPPEW_W, 0xff, TVP7002_WESEWVED },
	{ TVP7002_VSYNC_AWGN, 0x10, TVP7002_WWITE },
	{ TVP7002_SYNC_BYPASS, 0x00, TVP7002_WWITE },
	{ TVP7002_W_FWAME_STAT_WSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_W_FWAME_STAT_MSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_CWK_W_STAT_WSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_CWK_W_STAT_MSBS, 0xff, TVP7002_WEAD },
	{ TVP7002_HSYNC_W, 0xff, TVP7002_WEAD },
	{ TVP7002_VSYNC_W, 0xff, TVP7002_WEAD },
	{ TVP7002_W_WENGTH_TOW, 0x03, TVP7002_WWITE },
	{ 0x3e, 0x60, TVP7002_WESEWVED },
	{ TVP7002_VIDEO_BWTH_CTW, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x2c, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x2c, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x05, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x1e, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x00, TVP7002_WWITE },
	{ TVP7002_FBIT_F_0_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_FBIT_F_1_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_YUV_Y_G_COEF_WSBS, 0xe3, TVP7002_WWITE },
	{ TVP7002_YUV_Y_G_COEF_MSBS, 0x16, TVP7002_WWITE },
	{ TVP7002_YUV_Y_B_COEF_WSBS, 0x4f, TVP7002_WWITE },
	{ TVP7002_YUV_Y_B_COEF_MSBS, 0x02, TVP7002_WWITE },
	{ TVP7002_YUV_Y_W_COEF_WSBS, 0xce, TVP7002_WWITE },
	{ TVP7002_YUV_Y_W_COEF_MSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_YUV_U_G_COEF_WSBS, 0xab, TVP7002_WWITE },
	{ TVP7002_YUV_U_G_COEF_MSBS, 0xf3, TVP7002_WWITE },
	{ TVP7002_YUV_U_B_COEF_WSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_YUV_U_B_COEF_MSBS, 0x10, TVP7002_WWITE },
	{ TVP7002_YUV_U_W_COEF_WSBS, 0x55, TVP7002_WWITE },
	{ TVP7002_YUV_U_W_COEF_MSBS, 0xfc, TVP7002_WWITE },
	{ TVP7002_YUV_V_G_COEF_WSBS, 0x78, TVP7002_WWITE },
	{ TVP7002_YUV_V_G_COEF_MSBS, 0xf1, TVP7002_WWITE },
	{ TVP7002_YUV_V_B_COEF_WSBS, 0x88, TVP7002_WWITE },
	{ TVP7002_YUV_V_B_COEF_MSBS, 0xfe, TVP7002_WWITE },
	{ TVP7002_YUV_V_W_COEF_WSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_YUV_V_W_COEF_MSBS, 0x10, TVP7002_WWITE },
	/* This signaws end of wegistew vawues */
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 480P */
static const stwuct i2c_weg_vawue tvp7002_pawms_480P[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x35, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0xa0, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0x02, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x91, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x0B, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x03, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x01, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x13, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x13, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x18, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x06, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x10, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x03, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x03, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 576P */
static const stwuct i2c_weg_vawue tvp7002_pawms_576P[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x36, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0x18, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x9B, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x0F, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x2D, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x00, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x18, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x06, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x10, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x03, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x03, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 1080I60 */
static const stwuct i2c_weg_vawue tvp7002_pawms_1080I60[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x89, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x80, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0x98, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x8a, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x08, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x16, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x17, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x01, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 1080P60 */
static const stwuct i2c_weg_vawue tvp7002_pawms_1080P60[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x89, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x80, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0xE0, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x8a, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x08, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x16, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x17, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x01, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 1080I50 */
static const stwuct i2c_weg_vawue tvp7002_pawms_1080I50[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0xa5, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x00, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0x98, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x8a, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x08, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x02, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x16, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x17, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x01, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 720P60 */
static const stwuct i2c_weg_vawue tvp7002_pawms_720P60[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x67, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0xa0, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x47, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x4B, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x05, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x2D, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x00, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Wegistew pawametews fow 720P50 */
static const stwuct i2c_weg_vawue tvp7002_pawms_720P50[] = {
	{ TVP7002_HPWW_FDBK_DIV_MSBS, 0x7b, TVP7002_WWITE },
	{ TVP7002_HPWW_FDBK_DIV_WSBS, 0xc0, TVP7002_WWITE },
	{ TVP7002_HPWW_CWTW, 0x98, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_WSBS, 0x47, TVP7002_WWITE },
	{ TVP7002_AVID_STAWT_PIXEW_MSBS, 0x01, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_WSBS, 0x4B, TVP7002_WWITE },
	{ TVP7002_AVID_STOP_PIXEW_MSBS, 0x06, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_STAWT_W_OFF, 0x05, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_STAWT_W_OFF, 0x00, TVP7002_WWITE },
	{ TVP7002_VBWK_F_0_DUWATION, 0x2D, TVP7002_WWITE },
	{ TVP7002_VBWK_F_1_DUWATION, 0x00, TVP7002_WWITE },
	{ TVP7002_AWC_PWACEMENT, 0x5a, TVP7002_WWITE },
	{ TVP7002_CWAMP_STAWT, 0x32, TVP7002_WWITE },
	{ TVP7002_CWAMP_W, 0x20, TVP7002_WWITE },
	{ TVP7002_HPWW_PWE_COAST, 0x01, TVP7002_WWITE },
	{ TVP7002_HPWW_POST_COAST, 0x00, TVP7002_WWITE },
	{ TVP7002_EOW, 0xff, TVP7002_WESEWVED }
};

/* Timings definition fow handwing device opewation */
stwuct tvp7002_timings_definition {
	stwuct v4w2_dv_timings timings;
	const stwuct i2c_weg_vawue *p_settings;
	enum v4w2_cowowspace cowow_space;
	enum v4w2_fiewd scanmode;
	u16 pwogwessive;
	u16 wines_pew_fwame;
	u16 cpw_min;
	u16 cpw_max;
};

/* Stwuct wist fow digitaw video timings */
static const stwuct tvp7002_timings_definition tvp7002_timings[] = {
	{
		V4W2_DV_BT_CEA_1280X720P60,
		tvp7002_pawms_720P60,
		V4W2_COWOWSPACE_WEC709,
		V4W2_FIEWD_NONE,
		1,
		0x2EE,
		135,
		153
	},
	{
		V4W2_DV_BT_CEA_1920X1080I60,
		tvp7002_pawms_1080I60,
		V4W2_COWOWSPACE_WEC709,
		V4W2_FIEWD_INTEWWACED,
		0,
		0x465,
		181,
		205
	},
	{
		V4W2_DV_BT_CEA_1920X1080I50,
		tvp7002_pawms_1080I50,
		V4W2_COWOWSPACE_WEC709,
		V4W2_FIEWD_INTEWWACED,
		0,
		0x465,
		217,
		245
	},
	{
		V4W2_DV_BT_CEA_1280X720P50,
		tvp7002_pawms_720P50,
		V4W2_COWOWSPACE_WEC709,
		V4W2_FIEWD_NONE,
		1,
		0x2EE,
		163,
		183
	},
	{
		V4W2_DV_BT_CEA_1920X1080P60,
		tvp7002_pawms_1080P60,
		V4W2_COWOWSPACE_WEC709,
		V4W2_FIEWD_NONE,
		1,
		0x465,
		90,
		102
	},
	{
		V4W2_DV_BT_CEA_720X480P59_94,
		tvp7002_pawms_480P,
		V4W2_COWOWSPACE_SMPTE170M,
		V4W2_FIEWD_NONE,
		1,
		0x20D,
		0xffff,
		0xffff
	},
	{
		V4W2_DV_BT_CEA_720X576P50,
		tvp7002_pawms_576P,
		V4W2_COWOWSPACE_SMPTE170M,
		V4W2_FIEWD_NONE,
		1,
		0x271,
		0xffff,
		0xffff
	}
};

#define NUM_TIMINGS AWWAY_SIZE(tvp7002_timings)

/* Device definition */
stwuct tvp7002 {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	const stwuct tvp7002_config *pdata;

	int vew;
	int stweaming;

	const stwuct tvp7002_timings_definition *cuwwent_timings;
	stwuct media_pad pad;
};

/*
 * to_tvp7002 - Obtain device handwew TVP7002
 * @sd: ptw to v4w2_subdev stwuct
 *
 * Wetuwns device handwew tvp7002.
 */
static inwine stwuct tvp7002 *to_tvp7002(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct tvp7002, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct tvp7002, hdw)->sd;
}

/*
 * tvp7002_wead - Wead a vawue fwom a wegistew in an TVP7002
 * @sd: ptw to v4w2_subdev stwuct
 * @addw: TVP7002 wegistew addwess
 * @dst: pointew to 8-bit destination
 *
 * Wetuwns vawue wead if successfuw, ow non-zewo (-1) othewwise.
 */
static int tvp7002_wead(stwuct v4w2_subdev *sd, u8 addw, u8 *dst)
{
	stwuct i2c_cwient *c = v4w2_get_subdevdata(sd);
	int wetwy;
	int ewwow;

	fow (wetwy = 0; wetwy < I2C_WETWY_COUNT; wetwy++) {
		ewwow = i2c_smbus_wead_byte_data(c, addw);

		if (ewwow >= 0) {
			*dst = (u8)ewwow;
			wetuwn 0;
		}

		msweep_intewwuptibwe(10);
	}
	v4w2_eww(sd, "TVP7002 wead ewwow %d\n", ewwow);
	wetuwn ewwow;
}

/*
 * tvp7002_wead_eww() - Wead a wegistew vawue with ewwow code
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @weg: destination wegistew
 * @vaw: vawue to be wead
 * @eww: pointew to ewwow vawue
 *
 * Wead a vawue in a wegistew and save ewwow vawue in pointew.
 * Awso update the wegistew tabwe if successfuw
 */
static inwine void tvp7002_wead_eww(stwuct v4w2_subdev *sd, u8 weg,
							u8 *dst, int *eww)
{
	if (!*eww)
		*eww = tvp7002_wead(sd, weg, dst);
}

/*
 * tvp7002_wwite() - Wwite a vawue to a wegistew in TVP7002
 * @sd: ptw to v4w2_subdev stwuct
 * @addw: TVP7002 wegistew addwess
 * @vawue: vawue to be wwitten to the wegistew
 *
 * Wwite a vawue to a wegistew in an TVP7002 decodew device.
 * Wetuwns zewo if successfuw, ow non-zewo othewwise.
 */
static int tvp7002_wwite(stwuct v4w2_subdev *sd, u8 addw, u8 vawue)
{
	stwuct i2c_cwient *c;
	int wetwy;
	int ewwow;

	c = v4w2_get_subdevdata(sd);

	fow (wetwy = 0; wetwy < I2C_WETWY_COUNT; wetwy++) {
		ewwow = i2c_smbus_wwite_byte_data(c, addw, vawue);

		if (ewwow >= 0)
			wetuwn 0;

		v4w2_wawn(sd, "Wwite: wetwy ... %d\n", wetwy);
		msweep_intewwuptibwe(10);
	}
	v4w2_eww(sd, "TVP7002 wwite ewwow %d\n", ewwow);
	wetuwn ewwow;
}

/*
 * tvp7002_wwite_eww() - Wwite a wegistew vawue with ewwow code
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @weg: destination wegistew
 * @vaw: vawue to be wwitten
 * @eww: pointew to ewwow vawue
 *
 * Wwite a vawue in a wegistew and save ewwow vawue in pointew.
 * Awso update the wegistew tabwe if successfuw
 */
static inwine void tvp7002_wwite_eww(stwuct v4w2_subdev *sd, u8 weg,
							u8 vaw, int *eww)
{
	if (!*eww)
		*eww = tvp7002_wwite(sd, weg, vaw);
}

/*
 * tvp7002_wwite_inittab() - Wwite initiawization vawues
 * @sd: ptw to v4w2_subdev stwuct
 * @wegs: ptw to i2c_weg_vawue stwuct
 *
 * Wwite initiawization vawues.
 * Wetuwns zewo ow -EINVAW if wead opewation faiws.
 */
static int tvp7002_wwite_inittab(stwuct v4w2_subdev *sd,
					const stwuct i2c_weg_vawue *wegs)
{
	int ewwow = 0;

	/* Initiawize the fiwst (defined) wegistews */
	whiwe (TVP7002_EOW != wegs->weg) {
		if (TVP7002_WWITE == wegs->type)
			tvp7002_wwite_eww(sd, wegs->weg, wegs->vawue, &ewwow);
		wegs++;
	}

	wetuwn ewwow;
}

static int tvp7002_s_dv_timings(stwuct v4w2_subdev *sd,
					stwuct v4w2_dv_timings *dv_timings)
{
	stwuct tvp7002 *device = to_tvp7002(sd);
	const stwuct v4w2_bt_timings *bt = &dv_timings->bt;
	int i;

	if (dv_timings->type != V4W2_DV_BT_656_1120)
		wetuwn -EINVAW;
	fow (i = 0; i < NUM_TIMINGS; i++) {
		const stwuct v4w2_bt_timings *t = &tvp7002_timings[i].timings.bt;

		if (!memcmp(bt, t, &bt->standawds - &bt->width)) {
			device->cuwwent_timings = &tvp7002_timings[i];
			wetuwn tvp7002_wwite_inittab(sd, tvp7002_timings[i].p_settings);
		}
	}
	wetuwn -EINVAW;
}

static int tvp7002_g_dv_timings(stwuct v4w2_subdev *sd,
					stwuct v4w2_dv_timings *dv_timings)
{
	stwuct tvp7002 *device = to_tvp7002(sd);

	*dv_timings = device->cuwwent_timings->timings;
	wetuwn 0;
}

/*
 * tvp7002_s_ctww() - Set a contwow
 * @ctww: ptw to v4w2_ctww stwuct
 *
 * Set a contwow in TVP7002 decodew device.
 * Wetuwns zewo when successfuw ow -EINVAW if wegistew access faiws.
 */
static int tvp7002_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	int ewwow = 0;

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		tvp7002_wwite_eww(sd, TVP7002_W_FINE_GAIN, ctww->vaw, &ewwow);
		tvp7002_wwite_eww(sd, TVP7002_G_FINE_GAIN, ctww->vaw, &ewwow);
		tvp7002_wwite_eww(sd, TVP7002_B_FINE_GAIN, ctww->vaw, &ewwow);
		wetuwn ewwow;
	}
	wetuwn -EINVAW;
}

/*
 * tvp7002_quewy_dv() - quewy DV timings
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @index: index into the tvp7002_timings awway
 *
 * Wetuwns the cuwwent DV timings detected by TVP7002. If no active input is
 * detected, wetuwns -EINVAW
 */
static int tvp7002_quewy_dv(stwuct v4w2_subdev *sd, int *index)
{
	const stwuct tvp7002_timings_definition *timings = tvp7002_timings;
	u8 pwogwessive;
	u32 wpfw;
	u32 cpwn;
	int ewwow = 0;
	u8 wpf_wsb;
	u8 wpf_msb;
	u8 cpw_wsb;
	u8 cpw_msb;

	/* Wetuwn invawid index if no active input is detected */
	*index = NUM_TIMINGS;

	/* Wead standawds fwom device wegistews */
	tvp7002_wead_eww(sd, TVP7002_W_FWAME_STAT_WSBS, &wpf_wsb, &ewwow);
	tvp7002_wead_eww(sd, TVP7002_W_FWAME_STAT_MSBS, &wpf_msb, &ewwow);

	if (ewwow < 0)
		wetuwn ewwow;

	tvp7002_wead_eww(sd, TVP7002_CWK_W_STAT_WSBS, &cpw_wsb, &ewwow);
	tvp7002_wead_eww(sd, TVP7002_CWK_W_STAT_MSBS, &cpw_msb, &ewwow);

	if (ewwow < 0)
		wetuwn ewwow;

	/* Get wines pew fwame, cwocks pew wine and intewwaced/pwogwesive */
	wpfw = wpf_wsb | ((TVP7002_CW_MASK & wpf_msb) << TVP7002_CW_SHIFT);
	cpwn = cpw_wsb | ((TVP7002_CW_MASK & cpw_msb) << TVP7002_CW_SHIFT);
	pwogwessive = (wpf_msb & TVP7002_INPW_MASK) >> TVP7002_IP_SHIFT;

	/* Do checking of video modes */
	fow (*index = 0; *index < NUM_TIMINGS; (*index)++, timings++)
		if (wpfw == timings->wines_pew_fwame &&
			pwogwessive == timings->pwogwessive) {
			if (timings->cpw_min == 0xffff)
				bweak;
			if (cpwn >= timings->cpw_min && cpwn <= timings->cpw_max)
				bweak;
		}

	if (*index == NUM_TIMINGS) {
		v4w2_dbg(1, debug, sd, "detection faiwed: wpf = %x, cpw = %x\n",
								wpfw, cpwn);
		wetuwn -ENOWINK;
	}

	/* Update wines pew fwame and cwocks pew wine info */
	v4w2_dbg(1, debug, sd, "detected timings: %d\n", *index);
	wetuwn 0;
}

static int tvp7002_quewy_dv_timings(stwuct v4w2_subdev *sd,
					stwuct v4w2_dv_timings *timings)
{
	int index;
	int eww = tvp7002_quewy_dv(sd, &index);

	if (eww)
		wetuwn eww;
	*timings = tvp7002_timings[index].timings;
	wetuwn 0;
}

#ifdef CONFIG_VIDEO_ADV_DEBUG
/*
 * tvp7002_g_wegistew() - Get the vawue of a wegistew
 * @sd: ptw to v4w2_subdev stwuct
 * @weg: ptw to v4w2_dbg_wegistew stwuct
 *
 * Get the vawue of a TVP7002 decodew device wegistew.
 * Wetuwns zewo when successfuw, -EINVAW if wegistew wead faiws ow
 * access to I2C cwient faiws.
 */
static int tvp7002_g_wegistew(stwuct v4w2_subdev *sd,
						stwuct v4w2_dbg_wegistew *weg)
{
	u8 vaw;
	int wet;

	wet = tvp7002_wead(sd, weg->weg & 0xff, &vaw);
	if (wet < 0)
		wetuwn wet;
	weg->vaw = vaw;
	weg->size = 1;
	wetuwn 0;
}

/*
 * tvp7002_s_wegistew() - set a contwow
 * @sd: ptw to v4w2_subdev stwuct
 * @weg: ptw to v4w2_dbg_wegistew stwuct
 *
 * Get the vawue of a TVP7002 decodew device wegistew.
 * Wetuwns zewo when successfuw, -EINVAW if wegistew wead faiws.
 */
static int tvp7002_s_wegistew(stwuct v4w2_subdev *sd,
						const stwuct v4w2_dbg_wegistew *weg)
{
	wetuwn tvp7002_wwite(sd, weg->weg & 0xff, weg->vaw & 0xff);
}
#endif

/*
 * tvp7002_s_stweam() - V4W2 decodew i/f handwew fow s_stweam
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @enabwe: stweaming enabwe ow disabwe
 *
 * Sets stweaming to enabwe ow disabwe, if possibwe.
 */
static int tvp7002_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct tvp7002 *device = to_tvp7002(sd);
	int ewwow;

	if (device->stweaming == enabwe)
		wetuwn 0;

	/* wow impedance: on, high impedance: off */
	ewwow = tvp7002_wwite(sd, TVP7002_MISC_CTW_2, enabwe ? 0x00 : 0x03);
	if (ewwow) {
		v4w2_dbg(1, debug, sd, "Faiw to set stweaming\n");
		wetuwn ewwow;
	}

	device->stweaming = enabwe;
	wetuwn 0;
}

/*
 * tvp7002_wog_status() - Pwint infowmation about wegistew settings
 * @sd: ptw to v4w2_subdev stwuct
 *
 * Wog wegistew vawues of a TVP7002 decodew device.
 * Wetuwns zewo ow -EINVAW if wead opewation faiws.
 */
static int tvp7002_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct tvp7002 *device = to_tvp7002(sd);
	const stwuct v4w2_bt_timings *bt;
	int detected;

	/* Find my cuwwent timings */
	tvp7002_quewy_dv(sd, &detected);

	bt = &device->cuwwent_timings->timings.bt;
	v4w2_info(sd, "Sewected DV Timings: %ux%u\n", bt->width, bt->height);
	if (detected == NUM_TIMINGS) {
		v4w2_info(sd, "Detected DV Timings: None\n");
	} ewse {
		bt = &tvp7002_timings[detected].timings.bt;
		v4w2_info(sd, "Detected DV Timings: %ux%u\n",
				bt->width, bt->height);
	}
	v4w2_info(sd, "Stweaming enabwed: %s\n",
					device->stweaming ? "yes" : "no");

	/* Pwint the cuwwent vawue of the gain contwow */
	v4w2_ctww_handwew_wog_status(&device->hdw, sd->name);

	wetuwn 0;
}

static int tvp7002_enum_dv_timings(stwuct v4w2_subdev *sd,
		stwuct v4w2_enum_dv_timings *timings)
{
	if (timings->pad != 0)
		wetuwn -EINVAW;

	/* Check wequested fowmat index is within wange */
	if (timings->index >= NUM_TIMINGS)
		wetuwn -EINVAW;

	timings->timings = tvp7002_timings[timings->index].timings;
	wetuwn 0;
}

static const stwuct v4w2_ctww_ops tvp7002_ctww_ops = {
	.s_ctww = tvp7002_s_ctww,
};

/*
 * tvp7002_enum_mbus_code() - Enum suppowted digitaw video fowmat on pad
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 subdev state
 * @code: pointew to subdev enum mbus code stwuct
 *
 * Enumewate suppowted digitaw video fowmats fow pad.
 */
static int
tvp7002_enum_mbus_code(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_mbus_code_enum *code)
{
	/* Check wequested fowmat index is within wange */
	if (code->index != 0)
		wetuwn -EINVAW;

	code->code = MEDIA_BUS_FMT_YUYV10_1X20;

	wetuwn 0;
}

/*
 * tvp7002_get_pad_fowmat() - get video fowmat on pad
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to subdev fowmat stwuct
 *
 * get video fowmat fow pad.
 */
static int
tvp7002_get_pad_fowmat(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct tvp7002 *tvp7002 = to_tvp7002(sd);

	fmt->fowmat.code = MEDIA_BUS_FMT_YUYV10_1X20;
	fmt->fowmat.width = tvp7002->cuwwent_timings->timings.bt.width;
	fmt->fowmat.height = tvp7002->cuwwent_timings->timings.bt.height;
	fmt->fowmat.fiewd = tvp7002->cuwwent_timings->scanmode;
	fmt->fowmat.cowowspace = tvp7002->cuwwent_timings->cowow_space;

	wetuwn 0;
}

/*
 * tvp7002_set_pad_fowmat() - set video fowmat on pad
 * @sd: pointew to standawd V4W2 sub-device stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to subdev fowmat stwuct
 *
 * set video fowmat fow pad.
 */
static int
tvp7002_set_pad_fowmat(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *sd_state,
		       stwuct v4w2_subdev_fowmat *fmt)
{
	wetuwn tvp7002_get_pad_fowmat(sd, sd_state, fmt);
}

/* V4W2 cowe opewation handwews */
static const stwuct v4w2_subdev_cowe_ops tvp7002_cowe_ops = {
	.wog_status = tvp7002_wog_status,
#ifdef CONFIG_VIDEO_ADV_DEBUG
	.g_wegistew = tvp7002_g_wegistew,
	.s_wegistew = tvp7002_s_wegistew,
#endif
};

/* Specific video subsystem opewation handwews */
static const stwuct v4w2_subdev_video_ops tvp7002_video_ops = {
	.g_dv_timings = tvp7002_g_dv_timings,
	.s_dv_timings = tvp7002_s_dv_timings,
	.quewy_dv_timings = tvp7002_quewy_dv_timings,
	.s_stweam = tvp7002_s_stweam,
};

/* media pad wewated opewation handwews */
static const stwuct v4w2_subdev_pad_ops tvp7002_pad_ops = {
	.enum_mbus_code = tvp7002_enum_mbus_code,
	.get_fmt = tvp7002_get_pad_fowmat,
	.set_fmt = tvp7002_set_pad_fowmat,
	.enum_dv_timings = tvp7002_enum_dv_timings,
};

/* V4W2 top wevew opewation handwews */
static const stwuct v4w2_subdev_ops tvp7002_ops = {
	.cowe = &tvp7002_cowe_ops,
	.video = &tvp7002_video_ops,
	.pad = &tvp7002_pad_ops,
};

static stwuct tvp7002_config *
tvp7002_get_pdata(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	stwuct tvp7002_config *pdata = NUWW;
	stwuct device_node *endpoint;
	unsigned int fwags;

	if (!IS_ENABWED(CONFIG_OF) || !cwient->dev.of_node)
		wetuwn cwient->dev.pwatfowm_data;

	endpoint = of_gwaph_get_next_endpoint(cwient->dev.of_node, NUWW);
	if (!endpoint)
		wetuwn NUWW;

	if (v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(endpoint), &bus_cfg))
		goto done;

	pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		goto done;

	fwags = bus_cfg.bus.pawawwew.fwags;

	if (fwags & V4W2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_powawity = 1;

	if (fwags & V4W2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_powawity = 1;

	if (fwags & V4W2_MBUS_PCWK_SAMPWE_WISING)
		pdata->cwk_powawity = 1;

	if (fwags & V4W2_MBUS_FIEWD_EVEN_HIGH)
		pdata->fid_powawity = 1;

	if (fwags & V4W2_MBUS_VIDEO_SOG_ACTIVE_HIGH)
		pdata->sog_powawity = 1;

done:
	of_node_put(endpoint);
	wetuwn pdata;
}

/*
 * tvp7002_pwobe - Pwobe a TVP7002 device
 * @c: ptw to i2c_cwient stwuct
 * @id: ptw to i2c_device_id stwuct
 *
 * Initiawize the TVP7002 device
 * Wetuwns zewo when successfuw, -EINVAW if wegistew wead faiws ow
 * -EIO if i2c access is not avaiwabwe.
 */
static int tvp7002_pwobe(stwuct i2c_cwient *c)
{
	stwuct tvp7002_config *pdata = tvp7002_get_pdata(c);
	stwuct v4w2_subdev *sd;
	stwuct tvp7002 *device;
	stwuct v4w2_dv_timings timings;
	int powawity_a;
	int powawity_b;
	u8 wevision;
	int ewwow;

	if (pdata == NUWW) {
		dev_eww(&c->dev, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(c->adaptew,
		I2C_FUNC_SMBUS_WEAD_BYTE | I2C_FUNC_SMBUS_WWITE_BYTE_DATA))
		wetuwn -EIO;

	device = devm_kzawwoc(&c->dev, sizeof(stwuct tvp7002), GFP_KEWNEW);

	if (!device)
		wetuwn -ENOMEM;

	sd = &device->sd;
	device->pdata = pdata;
	device->cuwwent_timings = tvp7002_timings;

	/* Teww v4w2 the device is weady */
	v4w2_i2c_subdev_init(sd, c, &tvp7002_ops);
	v4w_info(c, "tvp7002 found @ 0x%02x (%s)\n",
					c->addw, c->adaptew->name);

	ewwow = tvp7002_wead(sd, TVP7002_CHIP_WEV, &wevision);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Get wevision numbew */
	v4w2_info(sd, "Wev. %02x detected.\n", wevision);
	if (wevision != 0x02)
		v4w2_info(sd, "Unknown wevision detected.\n");

	/* Initiawizes TVP7002 to its defauwt vawues */
	ewwow = tvp7002_wwite_inittab(sd, tvp7002_init_defauwt);

	if (ewwow < 0)
		wetuwn ewwow;

	/* Set powawity infowmation aftew wegistews have been set */
	powawity_a = 0x20 | device->pdata->hs_powawity << 5
			| device->pdata->vs_powawity << 2;
	ewwow = tvp7002_wwite(sd, TVP7002_SYNC_CTW_1, powawity_a);
	if (ewwow < 0)
		wetuwn ewwow;

	powawity_b = 0x01  | device->pdata->fid_powawity << 2
			| device->pdata->sog_powawity << 1
			| device->pdata->cwk_powawity;
	ewwow = tvp7002_wwite(sd, TVP7002_MISC_CTW_3, powawity_b);
	if (ewwow < 0)
		wetuwn ewwow;

	/* Set wegistews accowding to defauwt video mode */
	timings = device->cuwwent_timings->timings;
	ewwow = tvp7002_s_dv_timings(sd, &timings);

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	device->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	device->sd.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	device->sd.entity.function = MEDIA_ENT_F_ATV_DECODEW;

	ewwow = media_entity_pads_init(&device->sd.entity, 1, &device->pad);
	if (ewwow < 0)
		wetuwn ewwow;
#endif

	v4w2_ctww_handwew_init(&device->hdw, 1);
	v4w2_ctww_new_std(&device->hdw, &tvp7002_ctww_ops,
			V4W2_CID_GAIN, 0, 255, 1, 0);
	sd->ctww_handwew = &device->hdw;
	if (device->hdw.ewwow) {
		ewwow = device->hdw.ewwow;
		goto ewwow;
	}
	v4w2_ctww_handwew_setup(&device->hdw);

	ewwow = v4w2_async_wegistew_subdev(&device->sd);
	if (ewwow)
		goto ewwow;

	wetuwn 0;

ewwow:
	v4w2_ctww_handwew_fwee(&device->hdw);
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	media_entity_cweanup(&device->sd.entity);
#endif
	wetuwn ewwow;
}

/*
 * tvp7002_wemove - Wemove TVP7002 device suppowt
 * @c: ptw to i2c_cwient stwuct
 *
 * Weset the TVP7002 device
 * Wetuwns zewo.
 */
static void tvp7002_wemove(stwuct i2c_cwient *c)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(c);
	stwuct tvp7002 *device = to_tvp7002(sd);

	v4w2_dbg(1, debug, sd, "Wemoving tvp7002 adaptew"
				"on addwess 0x%x\n", c->addw);
	v4w2_async_unwegistew_subdev(&device->sd);
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	media_entity_cweanup(&device->sd.entity);
#endif
	v4w2_ctww_handwew_fwee(&device->hdw);
}

/* I2C Device ID tabwe */
static const stwuct i2c_device_id tvp7002_id[] = {
	{ "tvp7002", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tvp7002_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id tvp7002_of_match[] = {
	{ .compatibwe = "ti,tvp7002", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, tvp7002_of_match);
#endif

/* I2C dwivew data */
static stwuct i2c_dwivew tvp7002_dwivew = {
	.dwivew = {
		.of_match_tabwe = of_match_ptw(tvp7002_of_match),
		.name = TVP7002_MODUWE_NAME,
	},
	.pwobe = tvp7002_pwobe,
	.wemove = tvp7002_wemove,
	.id_tabwe = tvp7002_id,
};

moduwe_i2c_dwivew(tvp7002_dwivew);
