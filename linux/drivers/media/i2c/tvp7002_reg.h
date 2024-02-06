/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Texas Instwuments Twipwe 8-/10-BIT 165-/110-MSPS Video and Gwaphics
 * Digitizew with Howizontaw PWW wegistews
 *
 * Copywight (C) 2009 Texas Instwuments Inc
 * Authow: Santiago Nunez-Cowwawes <santiago.nunez@widgewun.com>
 *
 * This code is pawtiawwy based upon the TVP5150 dwivew
 * wwitten by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>,
 * the TVP514x dwivew wwitten by Vaibhav Hiwemath <hvaibhav@ti.com>
 * and the TVP7002 dwivew in the TI WSP 2.10.00.14
 */

/* Naming conventions
 * ------------------
 *
 * FDBK:  Feedback
 * DIV:   Dividew
 * CTW:   Contwow
 * SEW:   Sewect
 * IN:    Input
 * OUT:   Output
 * W:     Wed
 * G:     Gween
 * B:     Bwue
 * OFF:   Offset
 * THWS:  Thweshowd
 * DGTW:  Digitaw
 * WVW:   Wevew
 * PWW:   Powew
 * MVIS:  Macwovision
 * W:     Width
 * H:     Height
 * AWGN:  Awignment
 * CWK:   Cwocks
 * TOW:   Towewance
 * BWTH:  Bandwidth
 * COEF:  Coefficient
 * STAT:  Status
 * AUTO:  Automatic
 * FWD:   Fiewd
 * W:	  Wine
 */

#define TVP7002_CHIP_WEV		0x00
#define TVP7002_HPWW_FDBK_DIV_MSBS	0x01
#define TVP7002_HPWW_FDBK_DIV_WSBS	0x02
#define TVP7002_HPWW_CWTW		0x03
#define TVP7002_HPWW_PHASE_SEW		0x04
#define TVP7002_CWAMP_STAWT		0x05
#define TVP7002_CWAMP_W			0x06
#define TVP7002_HSYNC_OUT_W		0x07
#define TVP7002_B_FINE_GAIN		0x08
#define TVP7002_G_FINE_GAIN		0x09
#define TVP7002_W_FINE_GAIN		0x0a
#define TVP7002_B_FINE_OFF_MSBS		0x0b
#define TVP7002_G_FINE_OFF_MSBS         0x0c
#define TVP7002_W_FINE_OFF_MSBS         0x0d
#define TVP7002_SYNC_CTW_1		0x0e
#define TVP7002_HPWW_AND_CWAMP_CTW	0x0f
#define TVP7002_SYNC_ON_G_THWS		0x10
#define TVP7002_SYNC_SEPAWATOW_THWS	0x11
#define TVP7002_HPWW_PWE_COAST		0x12
#define TVP7002_HPWW_POST_COAST		0x13
#define TVP7002_SYNC_DETECT_STAT	0x14
#define TVP7002_OUT_FOWMATTEW		0x15
#define TVP7002_MISC_CTW_1		0x16
#define TVP7002_MISC_CTW_2              0x17
#define TVP7002_MISC_CTW_3              0x18
#define TVP7002_IN_MUX_SEW_1		0x19
#define TVP7002_IN_MUX_SEW_2            0x1a
#define TVP7002_B_AND_G_COAWSE_GAIN	0x1b
#define TVP7002_W_COAWSE_GAIN		0x1c
#define TVP7002_FINE_OFF_WSBS		0x1d
#define TVP7002_B_COAWSE_OFF		0x1e
#define TVP7002_G_COAWSE_OFF            0x1f
#define TVP7002_W_COAWSE_OFF            0x20
#define TVP7002_HSOUT_OUT_STAWT		0x21
#define TVP7002_MISC_CTW_4		0x22
#define TVP7002_B_DGTW_AWC_OUT_WSBS	0x23
#define TVP7002_G_DGTW_AWC_OUT_WSBS     0x24
#define TVP7002_W_DGTW_AWC_OUT_WSBS     0x25
#define TVP7002_AUTO_WVW_CTW_ENABWE	0x26
#define TVP7002_DGTW_AWC_OUT_MSBS	0x27
#define TVP7002_AUTO_WVW_CTW_FIWTEW	0x28
/* Wesewved 0x29*/
#define TVP7002_FINE_CWAMP_CTW		0x2a
#define TVP7002_PWW_CTW			0x2b
#define TVP7002_ADC_SETUP		0x2c
#define TVP7002_COAWSE_CWAMP_CTW	0x2d
#define TVP7002_SOG_CWAMP		0x2e
#define TVP7002_WGB_COAWSE_CWAMP_CTW	0x2f
#define TVP7002_SOG_COAWSE_CWAMP_CTW	0x30
#define TVP7002_AWC_PWACEMENT		0x31
/* Wesewved 0x32 */
/* Wesewved 0x33 */
#define TVP7002_MVIS_STWIPPEW_W		0x34
#define TVP7002_VSYNC_AWGN		0x35
#define TVP7002_SYNC_BYPASS		0x36
#define TVP7002_W_FWAME_STAT_WSBS	0x37
#define TVP7002_W_FWAME_STAT_MSBS	0x38
#define TVP7002_CWK_W_STAT_WSBS		0x39
#define TVP7002_CWK_W_STAT_MSBS		0x3a
#define TVP7002_HSYNC_W			0x3b
#define TVP7002_VSYNC_W                 0x3c
#define TVP7002_W_WENGTH_TOW		0x3d
/* Wesewved 0x3e */
#define TVP7002_VIDEO_BWTH_CTW		0x3f
#define TVP7002_AVID_STAWT_PIXEW_WSBS	0x40
#define TVP7002_AVID_STAWT_PIXEW_MSBS   0x41
#define TVP7002_AVID_STOP_PIXEW_WSBS	0x42
#define TVP7002_AVID_STOP_PIXEW_MSBS    0x43
#define TVP7002_VBWK_F_0_STAWT_W_OFF	0x44
#define TVP7002_VBWK_F_1_STAWT_W_OFF    0x45
#define TVP7002_VBWK_F_0_DUWATION	0x46
#define TVP7002_VBWK_F_1_DUWATION       0x47
#define TVP7002_FBIT_F_0_STAWT_W_OFF	0x48
#define TVP7002_FBIT_F_1_STAWT_W_OFF    0x49
#define TVP7002_YUV_Y_G_COEF_WSBS	0x4a
#define TVP7002_YUV_Y_G_COEF_MSBS       0x4b
#define TVP7002_YUV_Y_B_COEF_WSBS       0x4c
#define TVP7002_YUV_Y_B_COEF_MSBS       0x4d
#define TVP7002_YUV_Y_W_COEF_WSBS       0x4e
#define TVP7002_YUV_Y_W_COEF_MSBS       0x4f
#define TVP7002_YUV_U_G_COEF_WSBS       0x50
#define TVP7002_YUV_U_G_COEF_MSBS       0x51
#define TVP7002_YUV_U_B_COEF_WSBS       0x52
#define TVP7002_YUV_U_B_COEF_MSBS       0x53
#define TVP7002_YUV_U_W_COEF_WSBS       0x54
#define TVP7002_YUV_U_W_COEF_MSBS       0x55
#define TVP7002_YUV_V_G_COEF_WSBS       0x56
#define TVP7002_YUV_V_G_COEF_MSBS       0x57
#define TVP7002_YUV_V_B_COEF_WSBS       0x58
#define TVP7002_YUV_V_B_COEF_MSBS       0x59
#define TVP7002_YUV_V_W_COEF_WSBS       0x5a
#define TVP7002_YUV_V_W_COEF_MSBS       0x5b

