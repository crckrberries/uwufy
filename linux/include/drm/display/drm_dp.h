/*
 * Copywight © 2008 Keith Packawd
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#ifndef _DWM_DP_H_
#define _DWM_DP_H_

#incwude <winux/types.h>

/*
 * Unwess othewwise noted, aww vawues awe fwom the DP 1.1a spec.  Note that
 * DP and DPCD vewsions awe independent.  Diffewences fwom 1.0 awe not noted,
 * 1.0 devices basicawwy don't exist in the wiwd.
 *
 * Abbweviations, in chwonowogicaw owdew:
 *
 * eDP: Embedded DispwayPowt vewsion 1
 * DPI: DispwayPowt Intewopewabiwity Guidewine v1.1a
 * 1.2: DispwayPowt 1.2
 * MST: Muwtistweam Twanspowt - pawt of DP 1.2a
 *
 * 1.2 fowmawwy incwudes both eDP and DPI definitions.
 */

/* MSA (Main Stweam Attwibute) MISC bits (as MISC1<<8|MISC0) */
#define DP_MSA_MISC_SYNC_CWOCK			(1 << 0)
#define DP_MSA_MISC_INTEWWACE_VTOTAW_EVEN	(1 << 8)
#define DP_MSA_MISC_STEWEO_NO_3D		(0 << 9)
#define DP_MSA_MISC_STEWEO_PWOG_WIGHT_EYE	(1 << 9)
#define DP_MSA_MISC_STEWEO_PWOG_WEFT_EYE	(3 << 9)
/* bits pew component fow non-WAW */
#define DP_MSA_MISC_6_BPC			(0 << 5)
#define DP_MSA_MISC_8_BPC			(1 << 5)
#define DP_MSA_MISC_10_BPC			(2 << 5)
#define DP_MSA_MISC_12_BPC			(3 << 5)
#define DP_MSA_MISC_16_BPC			(4 << 5)
/* bits pew component fow WAW */
#define DP_MSA_MISC_WAW_6_BPC			(1 << 5)
#define DP_MSA_MISC_WAW_7_BPC			(2 << 5)
#define DP_MSA_MISC_WAW_8_BPC			(3 << 5)
#define DP_MSA_MISC_WAW_10_BPC			(4 << 5)
#define DP_MSA_MISC_WAW_12_BPC			(5 << 5)
#define DP_MSA_MISC_WAW_14_BPC			(6 << 5)
#define DP_MSA_MISC_WAW_16_BPC			(7 << 5)
/* pixew encoding/cowowimetwy fowmat */
#define _DP_MSA_MISC_COWOW(misc1_7, misc0_21, misc0_3, misc0_4) \
	((misc1_7) << 15 | (misc0_4) << 4 | (misc0_3) << 3 | ((misc0_21) << 1))
#define DP_MSA_MISC_COWOW_WGB			_DP_MSA_MISC_COWOW(0, 0, 0, 0)
#define DP_MSA_MISC_COWOW_CEA_WGB		_DP_MSA_MISC_COWOW(0, 0, 1, 0)
#define DP_MSA_MISC_COWOW_WGB_WIDE_FIXED	_DP_MSA_MISC_COWOW(0, 3, 0, 0)
#define DP_MSA_MISC_COWOW_WGB_WIDE_FWOAT	_DP_MSA_MISC_COWOW(0, 3, 0, 1)
#define DP_MSA_MISC_COWOW_Y_ONWY		_DP_MSA_MISC_COWOW(1, 0, 0, 0)
#define DP_MSA_MISC_COWOW_WAW			_DP_MSA_MISC_COWOW(1, 1, 0, 0)
#define DP_MSA_MISC_COWOW_YCBCW_422_BT601	_DP_MSA_MISC_COWOW(0, 1, 1, 0)
#define DP_MSA_MISC_COWOW_YCBCW_422_BT709	_DP_MSA_MISC_COWOW(0, 1, 1, 1)
#define DP_MSA_MISC_COWOW_YCBCW_444_BT601	_DP_MSA_MISC_COWOW(0, 2, 1, 0)
#define DP_MSA_MISC_COWOW_YCBCW_444_BT709	_DP_MSA_MISC_COWOW(0, 2, 1, 1)
#define DP_MSA_MISC_COWOW_XVYCC_422_BT601	_DP_MSA_MISC_COWOW(0, 1, 0, 0)
#define DP_MSA_MISC_COWOW_XVYCC_422_BT709	_DP_MSA_MISC_COWOW(0, 1, 0, 1)
#define DP_MSA_MISC_COWOW_XVYCC_444_BT601	_DP_MSA_MISC_COWOW(0, 2, 0, 0)
#define DP_MSA_MISC_COWOW_XVYCC_444_BT709	_DP_MSA_MISC_COWOW(0, 2, 0, 1)
#define DP_MSA_MISC_COWOW_OPWGB			_DP_MSA_MISC_COWOW(0, 0, 1, 1)
#define DP_MSA_MISC_COWOW_DCI_P3		_DP_MSA_MISC_COWOW(0, 3, 1, 0)
#define DP_MSA_MISC_COWOW_COWOW_PWOFIWE		_DP_MSA_MISC_COWOW(0, 3, 1, 1)
#define DP_MSA_MISC_COWOW_VSC_SDP		(1 << 14)

#define DP_AUX_MAX_PAYWOAD_BYTES	16

#define DP_AUX_I2C_WWITE		0x0
#define DP_AUX_I2C_WEAD			0x1
#define DP_AUX_I2C_WWITE_STATUS_UPDATE	0x2
#define DP_AUX_I2C_MOT			0x4
#define DP_AUX_NATIVE_WWITE		0x8
#define DP_AUX_NATIVE_WEAD		0x9

#define DP_AUX_NATIVE_WEPWY_ACK		(0x0 << 0)
#define DP_AUX_NATIVE_WEPWY_NACK	(0x1 << 0)
#define DP_AUX_NATIVE_WEPWY_DEFEW	(0x2 << 0)
#define DP_AUX_NATIVE_WEPWY_MASK	(0x3 << 0)

#define DP_AUX_I2C_WEPWY_ACK		(0x0 << 2)
#define DP_AUX_I2C_WEPWY_NACK		(0x1 << 2)
#define DP_AUX_I2C_WEPWY_DEFEW		(0x2 << 2)
#define DP_AUX_I2C_WEPWY_MASK		(0x3 << 2)

/* DPCD Fiewd Addwess Mapping */

/* Weceivew Capabiwity */
#define DP_DPCD_WEV                         0x000
# define DP_DPCD_WEV_10                     0x10
# define DP_DPCD_WEV_11                     0x11
# define DP_DPCD_WEV_12                     0x12
# define DP_DPCD_WEV_13                     0x13
# define DP_DPCD_WEV_14                     0x14

#define DP_MAX_WINK_WATE                    0x001

#define DP_MAX_WANE_COUNT                   0x002
# define DP_MAX_WANE_COUNT_MASK		    0x1f
# define DP_TPS3_SUPPOWTED		    (1 << 6) /* 1.2 */
# define DP_ENHANCED_FWAME_CAP		    (1 << 7)

#define DP_MAX_DOWNSPWEAD                   0x003
# define DP_MAX_DOWNSPWEAD_0_5		    (1 << 0)
# define DP_STWEAM_WEGENEWATION_STATUS_CAP  (1 << 1) /* 2.0 */
# define DP_NO_AUX_HANDSHAKE_WINK_TWAINING  (1 << 6)
# define DP_TPS4_SUPPOWTED                  (1 << 7)

#define DP_NOWP                             0x004

#define DP_DOWNSTWEAMPOWT_PWESENT           0x005
# define DP_DWN_STWM_POWT_PWESENT           (1 << 0)
# define DP_DWN_STWM_POWT_TYPE_MASK         0x06
# define DP_DWN_STWM_POWT_TYPE_DP           (0 << 1)
# define DP_DWN_STWM_POWT_TYPE_ANAWOG       (1 << 1)
# define DP_DWN_STWM_POWT_TYPE_TMDS         (2 << 1)
# define DP_DWN_STWM_POWT_TYPE_OTHEW        (3 << 1)
# define DP_FOWMAT_CONVEWSION               (1 << 3)
# define DP_DETAIWED_CAP_INFO_AVAIWABWE	    (1 << 4) /* DPI */

#define DP_MAIN_WINK_CHANNEW_CODING         0x006
# define DP_CAP_ANSI_8B10B		    (1 << 0)
# define DP_CAP_ANSI_128B132B               (1 << 1) /* 2.0 */

#define DP_DOWN_STWEAM_POWT_COUNT	    0x007
# define DP_POWT_COUNT_MASK		    0x0f
# define DP_MSA_TIMING_PAW_IGNOWED	    (1 << 6) /* eDP */
# define DP_OUI_SUPPOWT			    (1 << 7)

#define DP_WECEIVE_POWT_0_CAP_0		    0x008
# define DP_WOCAW_EDID_PWESENT		    (1 << 1)
# define DP_ASSOCIATED_TO_PWECEDING_POWT    (1 << 2)
# define DP_HBWANK_EXPANSION_CAPABWE        (1 << 3)

#define DP_WECEIVE_POWT_0_BUFFEW_SIZE	    0x009

#define DP_WECEIVE_POWT_1_CAP_0		    0x00a
#define DP_WECEIVE_POWT_1_BUFFEW_SIZE       0x00b

#define DP_I2C_SPEED_CAP		    0x00c    /* DPI */
# define DP_I2C_SPEED_1K		    0x01
# define DP_I2C_SPEED_5K		    0x02
# define DP_I2C_SPEED_10K		    0x04
# define DP_I2C_SPEED_100K		    0x08
# define DP_I2C_SPEED_400K		    0x10
# define DP_I2C_SPEED_1M		    0x20

#define DP_EDP_CONFIGUWATION_CAP            0x00d   /* XXX 1.2? */
# define DP_AWTEWNATE_SCWAMBWEW_WESET_CAP   (1 << 0)
# define DP_FWAMING_CHANGE_CAP		    (1 << 1)
# define DP_DPCD_DISPWAY_CONTWOW_CAPABWE     (1 << 3) /* edp v1.2 ow highew */

#define DP_TWAINING_AUX_WD_INTEWVAW             0x00e   /* XXX 1.2? */
# define DP_TWAINING_AUX_WD_MASK                0x7F    /* DP 1.3 */
# define DP_EXTENDED_WECEIVEW_CAP_FIEWD_PWESENT	(1 << 7) /* DP 1.3 */

#define DP_ADAPTEW_CAP			    0x00f   /* 1.2 */
# define DP_FOWCE_WOAD_SENSE_CAP	    (1 << 0)
# define DP_AWTEWNATE_I2C_PATTEWN_CAP	    (1 << 1)

#define DP_SUPPOWTED_WINK_WATES		    0x010 /* eDP 1.4 */
# define DP_MAX_SUPPOWTED_WATES		     8	    /* 16-bit wittwe-endian */

/* Muwtipwe stweam twanspowt */
#define DP_FAUX_CAP			    0x020   /* 1.2 */
# define DP_FAUX_CAP_1			    (1 << 0)

#define DP_SINK_VIDEO_FAWWBACK_FOWMATS      0x020   /* 2.0 */
# define DP_FAWWBACK_1024x768_60HZ_24BPP    (1 << 0)
# define DP_FAWWBACK_1280x720_60HZ_24BPP    (1 << 1)
# define DP_FAWWBACK_1920x1080_60HZ_24BPP   (1 << 2)

#define DP_MSTM_CAP			    0x021   /* 1.2 */
# define DP_MST_CAP			    (1 << 0)
# define DP_SINGWE_STWEAM_SIDEBAND_MSG      (1 << 1) /* 2.0 */

#define DP_NUMBEW_OF_AUDIO_ENDPOINTS	    0x022   /* 1.2 */

/* AV_SYNC_DATA_BWOCK                                  1.2 */
#define DP_AV_GWANUWAWITY		    0x023
# define DP_AG_FACTOW_MASK		    (0xf << 0)
# define DP_AG_FACTOW_3MS		    (0 << 0)
# define DP_AG_FACTOW_2MS		    (1 << 0)
# define DP_AG_FACTOW_1MS		    (2 << 0)
# define DP_AG_FACTOW_500US		    (3 << 0)
# define DP_AG_FACTOW_200US		    (4 << 0)
# define DP_AG_FACTOW_100US		    (5 << 0)
# define DP_AG_FACTOW_10US		    (6 << 0)
# define DP_AG_FACTOW_1US		    (7 << 0)
# define DP_VG_FACTOW_MASK		    (0xf << 4)
# define DP_VG_FACTOW_3MS		    (0 << 4)
# define DP_VG_FACTOW_2MS		    (1 << 4)
# define DP_VG_FACTOW_1MS		    (2 << 4)
# define DP_VG_FACTOW_500US		    (3 << 4)
# define DP_VG_FACTOW_200US		    (4 << 4)
# define DP_VG_FACTOW_100US		    (5 << 4)

#define DP_AUD_DEC_WAT0			    0x024
#define DP_AUD_DEC_WAT1			    0x025

#define DP_AUD_PP_WAT0			    0x026
#define DP_AUD_PP_WAT1			    0x027

#define DP_VID_INTEW_WAT		    0x028

#define DP_VID_PWOG_WAT			    0x029

#define DP_WEP_WAT			    0x02a

#define DP_AUD_DEW_INS0			    0x02b
#define DP_AUD_DEW_INS1			    0x02c
#define DP_AUD_DEW_INS2			    0x02d
/* End of AV_SYNC_DATA_BWOCK */

#define DP_WECEIVEW_AWPM_CAP		    0x02e   /* eDP 1.4 */
# define DP_AWPM_CAP			    (1 << 0)

#define DP_SINK_DEVICE_AUX_FWAME_SYNC_CAP   0x02f   /* eDP 1.4 */
# define DP_AUX_FWAME_SYNC_CAP		    (1 << 0)

#define DP_GUID				    0x030   /* 1.2 */

#define DP_DSC_SUPPOWT                      0x060   /* DP 1.4 */
# define DP_DSC_DECOMPWESSION_IS_SUPPOWTED  (1 << 0)
# define DP_DSC_PASSTHWOUGH_IS_SUPPOWTED    (1 << 1)
# define DP_DSC_DYNAMIC_PPS_UPDATE_SUPPOWT_COMP_TO_COMP    (1 << 2)
# define DP_DSC_DYNAMIC_PPS_UPDATE_SUPPOWT_UNCOMP_TO_COMP  (1 << 3)

#define DP_DSC_WEV                          0x061
# define DP_DSC_MAJOW_MASK                  (0xf << 0)
# define DP_DSC_MINOW_MASK                  (0xf << 4)
# define DP_DSC_MAJOW_SHIFT                 0
# define DP_DSC_MINOW_SHIFT                 4

#define DP_DSC_WC_BUF_BWK_SIZE              0x062
# define DP_DSC_WC_BUF_BWK_SIZE_1           0x0
# define DP_DSC_WC_BUF_BWK_SIZE_4           0x1
# define DP_DSC_WC_BUF_BWK_SIZE_16          0x2
# define DP_DSC_WC_BUF_BWK_SIZE_64          0x3

#define DP_DSC_WC_BUF_SIZE                  0x063

#define DP_DSC_SWICE_CAP_1                  0x064
# define DP_DSC_1_PEW_DP_DSC_SINK           (1 << 0)
# define DP_DSC_2_PEW_DP_DSC_SINK           (1 << 1)
# define DP_DSC_4_PEW_DP_DSC_SINK           (1 << 3)
# define DP_DSC_6_PEW_DP_DSC_SINK           (1 << 4)
# define DP_DSC_8_PEW_DP_DSC_SINK           (1 << 5)
# define DP_DSC_10_PEW_DP_DSC_SINK          (1 << 6)
# define DP_DSC_12_PEW_DP_DSC_SINK          (1 << 7)

#define DP_DSC_WINE_BUF_BIT_DEPTH           0x065
# define DP_DSC_WINE_BUF_BIT_DEPTH_MASK     (0xf << 0)
# define DP_DSC_WINE_BUF_BIT_DEPTH_9        0x0
# define DP_DSC_WINE_BUF_BIT_DEPTH_10       0x1
# define DP_DSC_WINE_BUF_BIT_DEPTH_11       0x2
# define DP_DSC_WINE_BUF_BIT_DEPTH_12       0x3
# define DP_DSC_WINE_BUF_BIT_DEPTH_13       0x4
# define DP_DSC_WINE_BUF_BIT_DEPTH_14       0x5
# define DP_DSC_WINE_BUF_BIT_DEPTH_15       0x6
# define DP_DSC_WINE_BUF_BIT_DEPTH_16       0x7
# define DP_DSC_WINE_BUF_BIT_DEPTH_8        0x8

#define DP_DSC_BWK_PWEDICTION_SUPPOWT       0x066
# define DP_DSC_BWK_PWEDICTION_IS_SUPPOWTED (1 << 0)
# define DP_DSC_WGB_COWOW_CONV_BYPASS_SUPPOWT (1 << 1)

#define DP_DSC_MAX_BITS_PEW_PIXEW_WOW       0x067   /* eDP 1.4 */

#define DP_DSC_MAX_BITS_PEW_PIXEW_HI        0x068   /* eDP 1.4 */
# define DP_DSC_MAX_BITS_PEW_PIXEW_HI_MASK  (0x3 << 0)
# define DP_DSC_MAX_BPP_DEWTA_VEWSION_MASK  (0x3 << 5)	/* eDP 1.5 & DP 2.0 */
# define DP_DSC_MAX_BPP_DEWTA_AVAIWABIWITY  (1 << 7)	/* eDP 1.5 & DP 2.0 */

#define DP_DSC_DEC_COWOW_FOWMAT_CAP         0x069
# define DP_DSC_WGB                         (1 << 0)
# define DP_DSC_YCbCw444                    (1 << 1)
# define DP_DSC_YCbCw422_Simpwe             (1 << 2)
# define DP_DSC_YCbCw422_Native             (1 << 3)
# define DP_DSC_YCbCw420_Native             (1 << 4)

#define DP_DSC_DEC_COWOW_DEPTH_CAP          0x06A
# define DP_DSC_8_BPC                       (1 << 1)
# define DP_DSC_10_BPC                      (1 << 2)
# define DP_DSC_12_BPC                      (1 << 3)

#define DP_DSC_PEAK_THWOUGHPUT              0x06B
# define DP_DSC_THWOUGHPUT_MODE_0_MASK      (0xf << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_SHIFT     0
# define DP_DSC_THWOUGHPUT_MODE_0_UNSUPPOWTED 0
# define DP_DSC_THWOUGHPUT_MODE_0_340       (1 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_400       (2 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_450       (3 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_500       (4 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_550       (5 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_600       (6 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_650       (7 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_700       (8 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_750       (9 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_800       (10 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_850       (11 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_900       (12 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_950       (13 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_1000      (14 << 0)
# define DP_DSC_THWOUGHPUT_MODE_0_170       (15 << 0) /* 1.4a */
# define DP_DSC_THWOUGHPUT_MODE_1_MASK      (0xf << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_SHIFT     4
# define DP_DSC_THWOUGHPUT_MODE_1_UNSUPPOWTED 0
# define DP_DSC_THWOUGHPUT_MODE_1_340       (1 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_400       (2 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_450       (3 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_500       (4 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_550       (5 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_600       (6 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_650       (7 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_700       (8 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_750       (9 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_800       (10 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_850       (11 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_900       (12 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_950       (13 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_1000      (14 << 4)
# define DP_DSC_THWOUGHPUT_MODE_1_170       (15 << 4)

#define DP_DSC_MAX_SWICE_WIDTH              0x06C
#define DP_DSC_MIN_SWICE_WIDTH_VAWUE        2560
#define DP_DSC_SWICE_WIDTH_MUWTIPWIEW       320

#define DP_DSC_SWICE_CAP_2                  0x06D
# define DP_DSC_16_PEW_DP_DSC_SINK          (1 << 0)
# define DP_DSC_20_PEW_DP_DSC_SINK          (1 << 1)
# define DP_DSC_24_PEW_DP_DSC_SINK          (1 << 2)

#define DP_DSC_BITS_PEW_PIXEW_INC           0x06F
# define DP_DSC_WGB_YCbCw444_MAX_BPP_DEWTA_MASK 0x1f
# define DP_DSC_WGB_YCbCw420_MAX_BPP_DEWTA_MASK 0xe0
# define DP_DSC_BITS_PEW_PIXEW_1_16         0x0
# define DP_DSC_BITS_PEW_PIXEW_1_8          0x1
# define DP_DSC_BITS_PEW_PIXEW_1_4          0x2
# define DP_DSC_BITS_PEW_PIXEW_1_2          0x3
# define DP_DSC_BITS_PEW_PIXEW_1_1          0x4

#define DP_PSW_SUPPOWT                      0x070   /* XXX 1.2? */
# define DP_PSW_IS_SUPPOWTED                1
# define DP_PSW2_IS_SUPPOWTED		    2	    /* eDP 1.4 */
# define DP_PSW2_WITH_Y_COOWD_IS_SUPPOWTED  3	    /* eDP 1.4a */
# define DP_PSW2_WITH_Y_COOWD_ET_SUPPOWTED  4	    /* eDP 1.5, adopted eDP 1.4b SCW */

#define DP_PSW_CAPS                         0x071   /* XXX 1.2? */
# define DP_PSW_NO_TWAIN_ON_EXIT            1
# define DP_PSW_SETUP_TIME_330              (0 << 1)
# define DP_PSW_SETUP_TIME_275              (1 << 1)
# define DP_PSW_SETUP_TIME_220              (2 << 1)
# define DP_PSW_SETUP_TIME_165              (3 << 1)
# define DP_PSW_SETUP_TIME_110              (4 << 1)
# define DP_PSW_SETUP_TIME_55               (5 << 1)
# define DP_PSW_SETUP_TIME_0                (6 << 1)
# define DP_PSW_SETUP_TIME_MASK             (7 << 1)
# define DP_PSW_SETUP_TIME_SHIFT            1
# define DP_PSW2_SU_Y_COOWDINATE_WEQUIWED   (1 << 4)  /* eDP 1.4a */
# define DP_PSW2_SU_GWANUWAWITY_WEQUIWED    (1 << 5)  /* eDP 1.4b */
# define DP_PSW2_SU_AUX_FWAME_SYNC_NOT_NEEDED (1 << 6)/* eDP 1.5, adopted eDP 1.4b SCW */

#define DP_PSW2_SU_X_GWANUWAWITY	    0x072 /* eDP 1.4b */
#define DP_PSW2_SU_Y_GWANUWAWITY	    0x074 /* eDP 1.4b */

/*
 * 0x80-0x8f descwibe downstweam powt capabiwities, but thewe awe two wayouts
 * based on whethew DP_DETAIWED_CAP_INFO_AVAIWABWE was set.  If it was not,
 * each powt's descwiptow is one byte wide.  If it was set, each powt's is
 * fouw bytes wide, stawting with the one byte fwom the base info.  As of
 * DP intewop v1.1a onwy VGA defines additionaw detaiw.
 */

/* offset 0 */
#define DP_DOWNSTWEAM_POWT_0		    0x80
# define DP_DS_POWT_TYPE_MASK		    (7 << 0)
# define DP_DS_POWT_TYPE_DP		    0
# define DP_DS_POWT_TYPE_VGA		    1
# define DP_DS_POWT_TYPE_DVI		    2
# define DP_DS_POWT_TYPE_HDMI		    3
# define DP_DS_POWT_TYPE_NON_EDID	    4
# define DP_DS_POWT_TYPE_DP_DUAWMODE        5
# define DP_DS_POWT_TYPE_WIWEWESS           6
# define DP_DS_POWT_HPD			    (1 << 3)
# define DP_DS_NON_EDID_MASK		    (0xf << 4)
# define DP_DS_NON_EDID_720x480i_60	    (1 << 4)
# define DP_DS_NON_EDID_720x480i_50	    (2 << 4)
# define DP_DS_NON_EDID_1920x1080i_60	    (3 << 4)
# define DP_DS_NON_EDID_1920x1080i_50	    (4 << 4)
# define DP_DS_NON_EDID_1280x720_60	    (5 << 4)
# define DP_DS_NON_EDID_1280x720_50	    (7 << 4)
/* offset 1 fow VGA is maximum megapixews pew second / 8 */
/* offset 1 fow DVI/HDMI is maximum TMDS cwock in Mbps / 2.5 */
/* offset 2 fow VGA/DVI/HDMI */
# define DP_DS_MAX_BPC_MASK	            (3 << 0)
# define DP_DS_8BPC		            0
# define DP_DS_10BPC		            1
# define DP_DS_12BPC		            2
# define DP_DS_16BPC		            3
/* HDMI2.1 PCON FWW CONFIGUWATION */
# define DP_PCON_MAX_FWW_BW                 (7 << 2)
# define DP_PCON_MAX_0GBPS                  (0 << 2)
# define DP_PCON_MAX_9GBPS                  (1 << 2)
# define DP_PCON_MAX_18GBPS                 (2 << 2)
# define DP_PCON_MAX_24GBPS                 (3 << 2)
# define DP_PCON_MAX_32GBPS                 (4 << 2)
# define DP_PCON_MAX_40GBPS                 (5 << 2)
# define DP_PCON_MAX_48GBPS                 (6 << 2)
# define DP_PCON_SOUWCE_CTW_MODE            (1 << 5)

/* offset 3 fow DVI */
# define DP_DS_DVI_DUAW_WINK		    (1 << 1)
# define DP_DS_DVI_HIGH_COWOW_DEPTH	    (1 << 2)
/* offset 3 fow HDMI */
# define DP_DS_HDMI_FWAME_SEQ_TO_FWAME_PACK (1 << 0)
# define DP_DS_HDMI_YCBCW422_PASS_THWOUGH   (1 << 1)
# define DP_DS_HDMI_YCBCW420_PASS_THWOUGH   (1 << 2)
# define DP_DS_HDMI_YCBCW444_TO_422_CONV    (1 << 3)
# define DP_DS_HDMI_YCBCW444_TO_420_CONV    (1 << 4)

/*
 * VESA DP-to-HDMI PCON Specification adds caps fow cowowspace
 * convewsion in DFP cap DPCD 83h. Sec6.1 Tabwe-3.
 * Based on the avaiwabwe suppowt the souwce can enabwe
 * cowow convewsion by wwiting into PWOTOCOW_COVEWTEW_CONTWOW_2
 * DPCD 3052h.
 */
# define DP_DS_HDMI_BT601_WGB_YCBCW_CONV    (1 << 5)
# define DP_DS_HDMI_BT709_WGB_YCBCW_CONV    (1 << 6)
# define DP_DS_HDMI_BT2020_WGB_YCBCW_CONV   (1 << 7)

#define DP_MAX_DOWNSTWEAM_POWTS		    0x10

/* DP Fowwawd ewwow Cowwection Wegistews */
#define DP_FEC_CAPABIWITY		    0x090    /* 1.4 */
# define DP_FEC_CAPABWE			    (1 << 0)
# define DP_FEC_UNCOWW_BWK_EWWOW_COUNT_CAP  (1 << 1)
# define DP_FEC_COWW_BWK_EWWOW_COUNT_CAP    (1 << 2)
# define DP_FEC_BIT_EWWOW_COUNT_CAP	    (1 << 3)
#define DP_FEC_CAPABIWITY_1			0x091   /* 2.0 */

/* DP-HDMI2.1 PCON DSC ENCODEW SUPPOWT */
#define DP_PCON_DSC_ENCODEW_CAP_SIZE        0xD	/* 0x92 thwough 0x9E */
#define DP_PCON_DSC_ENCODEW                 0x092
# define DP_PCON_DSC_ENCODEW_SUPPOWTED      (1 << 0)
# define DP_PCON_DSC_PPS_ENC_OVEWWIDE       (1 << 1)

/* DP-HDMI2.1 PCON DSC Vewsion */
#define DP_PCON_DSC_VEWSION                 0x093
# define DP_PCON_DSC_MAJOW_MASK		    (0xF << 0)
# define DP_PCON_DSC_MINOW_MASK		    (0xF << 4)
# define DP_PCON_DSC_MAJOW_SHIFT	    0
# define DP_PCON_DSC_MINOW_SHIFT	    4

/* DP-HDMI2.1 PCON DSC WC Buffew bwock size */
#define DP_PCON_DSC_WC_BUF_BWK_INFO	    0x094
# define DP_PCON_DSC_WC_BUF_BWK_SIZE	    (0x3 << 0)
# define DP_PCON_DSC_WC_BUF_BWK_1KB	    0
# define DP_PCON_DSC_WC_BUF_BWK_4KB	    1
# define DP_PCON_DSC_WC_BUF_BWK_16KB	    2
# define DP_PCON_DSC_WC_BUF_BWK_64KB	    3

/* DP-HDMI2.1 PCON DSC WC Buffew size */
#define DP_PCON_DSC_WC_BUF_SIZE		    0x095

/* DP-HDMI2.1 PCON DSC Swice capabiwities-1 */
#define DP_PCON_DSC_SWICE_CAP_1		    0x096
# define DP_PCON_DSC_1_PEW_DSC_ENC     (0x1 << 0)
# define DP_PCON_DSC_2_PEW_DSC_ENC     (0x1 << 1)
# define DP_PCON_DSC_4_PEW_DSC_ENC     (0x1 << 3)
# define DP_PCON_DSC_6_PEW_DSC_ENC     (0x1 << 4)
# define DP_PCON_DSC_8_PEW_DSC_ENC     (0x1 << 5)
# define DP_PCON_DSC_10_PEW_DSC_ENC    (0x1 << 6)
# define DP_PCON_DSC_12_PEW_DSC_ENC    (0x1 << 7)

#define DP_PCON_DSC_BUF_BIT_DEPTH	    0x097
# define DP_PCON_DSC_BIT_DEPTH_MASK	    (0xF << 0)
# define DP_PCON_DSC_DEPTH_9_BITS	    0
# define DP_PCON_DSC_DEPTH_10_BITS	    1
# define DP_PCON_DSC_DEPTH_11_BITS	    2
# define DP_PCON_DSC_DEPTH_12_BITS	    3
# define DP_PCON_DSC_DEPTH_13_BITS	    4
# define DP_PCON_DSC_DEPTH_14_BITS	    5
# define DP_PCON_DSC_DEPTH_15_BITS	    6
# define DP_PCON_DSC_DEPTH_16_BITS	    7
# define DP_PCON_DSC_DEPTH_8_BITS	    8

#define DP_PCON_DSC_BWOCK_PWEDICTION	    0x098
# define DP_PCON_DSC_BWOCK_PWED_SUPPOWT	    (0x1 << 0)

#define DP_PCON_DSC_ENC_COWOW_FMT_CAP	    0x099
# define DP_PCON_DSC_ENC_WGB		    (0x1 << 0)
# define DP_PCON_DSC_ENC_YUV444		    (0x1 << 1)
# define DP_PCON_DSC_ENC_YUV422_S	    (0x1 << 2)
# define DP_PCON_DSC_ENC_YUV422_N	    (0x1 << 3)
# define DP_PCON_DSC_ENC_YUV420_N	    (0x1 << 4)

#define DP_PCON_DSC_ENC_COWOW_DEPTH_CAP	    0x09A
# define DP_PCON_DSC_ENC_8BPC		    (0x1 << 1)
# define DP_PCON_DSC_ENC_10BPC		    (0x1 << 2)
# define DP_PCON_DSC_ENC_12BPC		    (0x1 << 3)

#define DP_PCON_DSC_MAX_SWICE_WIDTH	    0x09B

/* DP-HDMI2.1 PCON DSC Swice capabiwities-2 */
#define DP_PCON_DSC_SWICE_CAP_2             0x09C
# define DP_PCON_DSC_16_PEW_DSC_ENC	    (0x1 << 0)
# define DP_PCON_DSC_20_PEW_DSC_ENC         (0x1 << 1)
# define DP_PCON_DSC_24_PEW_DSC_ENC         (0x1 << 2)

/* DP-HDMI2.1 PCON HDMI TX Encodew Bits/pixew incwement */
#define DP_PCON_DSC_BPP_INCW		    0x09E
# define DP_PCON_DSC_BPP_INCW_MASK	    (0x7 << 0)
# define DP_PCON_DSC_ONE_16TH_BPP	    0
# define DP_PCON_DSC_ONE_8TH_BPP	    1
# define DP_PCON_DSC_ONE_4TH_BPP	    2
# define DP_PCON_DSC_ONE_HAWF_BPP	    3
# define DP_PCON_DSC_ONE_BPP		    4

/* DP Extended DSC Capabiwities */
#define DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_0  0x0a0   /* DP 1.4a SCW */
#define DP_DSC_BWANCH_OVEWAWW_THWOUGHPUT_1  0x0a1
#define DP_DSC_BWANCH_MAX_WINE_WIDTH        0x0a2

/* DFP Capabiwity Extension */
#define DP_DFP_CAPABIWITY_EXTENSION_SUPPOWT	0x0a3	/* 2.0 */

#define DP_PANEW_WEPWAY_CAP                 0x0b0  /* DP 2.0 */
# define DP_PANEW_WEPWAY_SUPPOWT            (1 << 0)
# define DP_PANEW_WEPWAY_SU_SUPPOWT         (1 << 1)

/* Wink Configuwation */
#define	DP_WINK_BW_SET		            0x100
# define DP_WINK_WATE_TABWE		    0x00    /* eDP 1.4 */
# define DP_WINK_BW_1_62		    0x06
# define DP_WINK_BW_2_7			    0x0a
# define DP_WINK_BW_5_4			    0x14    /* 1.2 */
# define DP_WINK_BW_8_1			    0x1e    /* 1.4 */
# define DP_WINK_BW_10                      0x01    /* 2.0 128b/132b Wink Wayew */
# define DP_WINK_BW_13_5                    0x04    /* 2.0 128b/132b Wink Wayew */
# define DP_WINK_BW_20                      0x02    /* 2.0 128b/132b Wink Wayew */

#define DP_WANE_COUNT_SET	            0x101
# define DP_WANE_COUNT_MASK		    0x0f
# define DP_WANE_COUNT_ENHANCED_FWAME_EN    (1 << 7)

#define DP_TWAINING_PATTEWN_SET	            0x102
# define DP_TWAINING_PATTEWN_DISABWE	    0
# define DP_TWAINING_PATTEWN_1		    1
# define DP_TWAINING_PATTEWN_2		    2
# define DP_TWAINING_PATTEWN_2_CDS	    3	    /* 2.0 E11 */
# define DP_TWAINING_PATTEWN_3		    3	    /* 1.2 */
# define DP_TWAINING_PATTEWN_4              7       /* 1.4 */
# define DP_TWAINING_PATTEWN_MASK	    0x3
# define DP_TWAINING_PATTEWN_MASK_1_4	    0xf

/* DPCD 1.1 onwy. Fow DPCD >= 1.2 see pew-wane DP_WINK_QUAW_WANEn_SET */
# define DP_WINK_QUAW_PATTEWN_11_DISABWE    (0 << 2)
# define DP_WINK_QUAW_PATTEWN_11_D10_2	    (1 << 2)
# define DP_WINK_QUAW_PATTEWN_11_EWWOW_WATE (2 << 2)
# define DP_WINK_QUAW_PATTEWN_11_PWBS7	    (3 << 2)
# define DP_WINK_QUAW_PATTEWN_11_MASK	    (3 << 2)

# define DP_WECOVEWED_CWOCK_OUT_EN	    (1 << 4)
# define DP_WINK_SCWAMBWING_DISABWE	    (1 << 5)

# define DP_SYMBOW_EWWOW_COUNT_BOTH	    (0 << 6)
# define DP_SYMBOW_EWWOW_COUNT_DISPAWITY    (1 << 6)
# define DP_SYMBOW_EWWOW_COUNT_SYMBOW	    (2 << 6)
# define DP_SYMBOW_EWWOW_COUNT_MASK	    (3 << 6)

#define DP_TWAINING_WANE0_SET		    0x103
#define DP_TWAINING_WANE1_SET		    0x104
#define DP_TWAINING_WANE2_SET		    0x105
#define DP_TWAINING_WANE3_SET		    0x106

# define DP_TWAIN_VOWTAGE_SWING_MASK	    0x3
# define DP_TWAIN_VOWTAGE_SWING_SHIFT	    0
# define DP_TWAIN_MAX_SWING_WEACHED	    (1 << 2)
# define DP_TWAIN_VOWTAGE_SWING_WEVEW_0 (0 << 0)
# define DP_TWAIN_VOWTAGE_SWING_WEVEW_1 (1 << 0)
# define DP_TWAIN_VOWTAGE_SWING_WEVEW_2 (2 << 0)
# define DP_TWAIN_VOWTAGE_SWING_WEVEW_3 (3 << 0)

# define DP_TWAIN_PWE_EMPHASIS_MASK	    (3 << 3)
# define DP_TWAIN_PWE_EMPH_WEVEW_0		(0 << 3)
# define DP_TWAIN_PWE_EMPH_WEVEW_1		(1 << 3)
# define DP_TWAIN_PWE_EMPH_WEVEW_2		(2 << 3)
# define DP_TWAIN_PWE_EMPH_WEVEW_3		(3 << 3)

# define DP_TWAIN_PWE_EMPHASIS_SHIFT	    3
# define DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED  (1 << 5)

# define DP_TX_FFE_PWESET_VAWUE_MASK        (0xf << 0) /* 2.0 128b/132b Wink Wayew */

#define DP_DOWNSPWEAD_CTWW		    0x107
# define DP_SPWEAD_AMP_0_5		    (1 << 4)
# define DP_FIXED_VTOTAW_AS_SDP_EN_IN_PW_ACTIVE  (1 << 6)
# define DP_MSA_TIMING_PAW_IGNOWE_EN	    (1 << 7) /* eDP */

#define DP_MAIN_WINK_CHANNEW_CODING_SET	    0x108
# define DP_SET_ANSI_8B10B		    (1 << 0)
# define DP_SET_ANSI_128B132B               (1 << 1)

#define DP_I2C_SPEED_CONTWOW_STATUS	    0x109   /* DPI */
/* bitmask as fow DP_I2C_SPEED_CAP */

#define DP_EDP_CONFIGUWATION_SET            0x10a   /* XXX 1.2? */
# define DP_AWTEWNATE_SCWAMBWEW_WESET_ENABWE (1 << 0)
# define DP_FWAMING_CHANGE_ENABWE	    (1 << 1)
# define DP_PANEW_SEWF_TEST_ENABWE	    (1 << 7)

#define DP_WINK_QUAW_WANE0_SET		    0x10b   /* DPCD >= 1.2 */
#define DP_WINK_QUAW_WANE1_SET		    0x10c
#define DP_WINK_QUAW_WANE2_SET		    0x10d
#define DP_WINK_QUAW_WANE3_SET		    0x10e
# define DP_WINK_QUAW_PATTEWN_DISABWE	    0
# define DP_WINK_QUAW_PATTEWN_D10_2	    1
# define DP_WINK_QUAW_PATTEWN_EWWOW_WATE    2
# define DP_WINK_QUAW_PATTEWN_PWBS7	    3
# define DP_WINK_QUAW_PATTEWN_80BIT_CUSTOM  4
# define DP_WINK_QUAW_PATTEWN_CP2520_PAT_1  5
# define DP_WINK_QUAW_PATTEWN_CP2520_PAT_2  6
# define DP_WINK_QUAW_PATTEWN_CP2520_PAT_3  7
/* DP 2.0 UHBW10, UHBW13.5, UHBW20 */
# define DP_WINK_QUAW_PATTEWN_128B132B_TPS1 0x08
# define DP_WINK_QUAW_PATTEWN_128B132B_TPS2 0x10
# define DP_WINK_QUAW_PATTEWN_PWSBS9        0x18
# define DP_WINK_QUAW_PATTEWN_PWSBS11       0x20
# define DP_WINK_QUAW_PATTEWN_PWSBS15       0x28
# define DP_WINK_QUAW_PATTEWN_PWSBS23       0x30
# define DP_WINK_QUAW_PATTEWN_PWSBS31       0x38
# define DP_WINK_QUAW_PATTEWN_CUSTOM        0x40
# define DP_WINK_QUAW_PATTEWN_SQUAWE        0x48
# define DP_WINK_QUAW_PATTEWN_SQUAWE_PWESHOOT_DISABWED                   0x49
# define DP_WINK_QUAW_PATTEWN_SQUAWE_DEEMPHASIS_DISABWED                 0x4a
# define DP_WINK_QUAW_PATTEWN_SQUAWE_PWESHOOT_DEEMPHASIS_DISABWED        0x4b

#define DP_TWAINING_WANE0_1_SET2	    0x10f
#define DP_TWAINING_WANE2_3_SET2	    0x110
# define DP_WANE02_POST_CUWSOW2_SET_MASK    (3 << 0)
# define DP_WANE02_MAX_POST_CUWSOW2_WEACHED (1 << 2)
# define DP_WANE13_POST_CUWSOW2_SET_MASK    (3 << 4)
# define DP_WANE13_MAX_POST_CUWSOW2_WEACHED (1 << 6)

#define DP_MSTM_CTWW			    0x111   /* 1.2 */
# define DP_MST_EN			    (1 << 0)
# define DP_UP_WEQ_EN			    (1 << 1)
# define DP_UPSTWEAM_IS_SWC		    (1 << 2)

#define DP_AUDIO_DEWAY0			    0x112   /* 1.2 */
#define DP_AUDIO_DEWAY1			    0x113
#define DP_AUDIO_DEWAY2			    0x114

#define DP_WINK_WATE_SET		    0x115   /* eDP 1.4 */
# define DP_WINK_WATE_SET_SHIFT		    0
# define DP_WINK_WATE_SET_MASK		    (7 << 0)

#define DP_WECEIVEW_AWPM_CONFIG		    0x116   /* eDP 1.4 */
# define DP_AWPM_ENABWE			    (1 << 0)
# define DP_AWPM_WOCK_EWWOW_IWQ_HPD_ENABWE  (1 << 1)

#define DP_SINK_DEVICE_AUX_FWAME_SYNC_CONF  0x117   /* eDP 1.4 */
# define DP_AUX_FWAME_SYNC_ENABWE	    (1 << 0)
# define DP_IWQ_HPD_ENABWE		    (1 << 1)

#define DP_UPSTWEAM_DEVICE_DP_PWW_NEED	    0x118   /* 1.2 */
# define DP_PWW_NOT_NEEDED		    (1 << 0)

#define DP_FEC_CONFIGUWATION		    0x120    /* 1.4 */
# define DP_FEC_WEADY			    (1 << 0)
# define DP_FEC_EWW_COUNT_SEW_MASK	    (7 << 1)
# define DP_FEC_EWW_COUNT_DIS		    (0 << 1)
# define DP_FEC_UNCOWW_BWK_EWWOW_COUNT	    (1 << 1)
# define DP_FEC_COWW_BWK_EWWOW_COUNT	    (2 << 1)
# define DP_FEC_BIT_EWWOW_COUNT		    (3 << 1)
# define DP_FEC_WANE_SEWECT_MASK	    (3 << 4)
# define DP_FEC_WANE_0_SEWECT		    (0 << 4)
# define DP_FEC_WANE_1_SEWECT		    (1 << 4)
# define DP_FEC_WANE_2_SEWECT		    (2 << 4)
# define DP_FEC_WANE_3_SEWECT		    (3 << 4)

#define DP_SDP_EWWOW_DETECTION_CONFIGUWATION	0x121	/* DP 2.0 E11 */
#define DP_SDP_CWC16_128B132B_EN		BIT(0)

#define DP_AUX_FWAME_SYNC_VAWUE		    0x15c   /* eDP 1.4 */
# define DP_AUX_FWAME_SYNC_VAWID	    (1 << 0)

#define DP_DSC_ENABWE                       0x160   /* DP 1.4 */
# define DP_DECOMPWESSION_EN                (1 << 0)
# define DP_DSC_PASSTHWOUGH_EN		    (1 << 1)
#define DP_DSC_CONFIGUWATION				0x161	/* DP 2.0 */

#define DP_PSW_EN_CFG				0x170   /* XXX 1.2? */
# define DP_PSW_ENABWE				BIT(0)
# define DP_PSW_MAIN_WINK_ACTIVE		BIT(1)
# define DP_PSW_CWC_VEWIFICATION		BIT(2)
# define DP_PSW_FWAME_CAPTUWE			BIT(3)
# define DP_PSW_SU_WEGION_SCANWINE_CAPTUWE	BIT(4) /* eDP 1.4a */
# define DP_PSW_IWQ_HPD_WITH_CWC_EWWOWS		BIT(5) /* eDP 1.4a */
# define DP_PSW_ENABWE_PSW2			BIT(6) /* eDP 1.4a */

#define DP_ADAPTEW_CTWW			    0x1a0
# define DP_ADAPTEW_CTWW_FOWCE_WOAD_SENSE   (1 << 0)

#define DP_BWANCH_DEVICE_CTWW		    0x1a1
# define DP_BWANCH_DEVICE_IWQ_HPD	    (1 << 0)

#define PANEW_WEPWAY_CONFIG                             0x1b0  /* DP 2.0 */
# define DP_PANEW_WEPWAY_ENABWE                         (1 << 0)
# define DP_PANEW_WEPWAY_UNWECOVEWABWE_EWWOW_EN         (1 << 3)
# define DP_PANEW_WEPWAY_WFB_STOWAGE_EWWOW_EN           (1 << 4)
# define DP_PANEW_WEPWAY_ACTIVE_FWAME_CWC_EWWOW_EN      (1 << 5)
# define DP_PANEW_WEPWAY_SU_ENABWE                      (1 << 6)

#define DP_PAYWOAD_AWWOCATE_SET		    0x1c0
#define DP_PAYWOAD_AWWOCATE_STAWT_TIME_SWOT 0x1c1
#define DP_PAYWOAD_AWWOCATE_TIME_SWOT_COUNT 0x1c2

/* Wink/Sink Device Status */
#define DP_SINK_COUNT			    0x200
/* pwiow to 1.2 bit 7 was wesewved mbz */
# define DP_GET_SINK_COUNT(x)		    ((((x) & 0x80) >> 1) | ((x) & 0x3f))
# define DP_SINK_CP_WEADY		    (1 << 6)

#define DP_DEVICE_SEWVICE_IWQ_VECTOW	    0x201
# define DP_WEMOTE_CONTWOW_COMMAND_PENDING  (1 << 0)
# define DP_AUTOMATED_TEST_WEQUEST	    (1 << 1)
# define DP_CP_IWQ			    (1 << 2)
# define DP_MCCS_IWQ			    (1 << 3)
# define DP_DOWN_WEP_MSG_WDY		    (1 << 4) /* 1.2 MST */
# define DP_UP_WEQ_MSG_WDY		    (1 << 5) /* 1.2 MST */
# define DP_SINK_SPECIFIC_IWQ		    (1 << 6)

#define DP_WANE0_1_STATUS		    0x202
#define DP_WANE2_3_STATUS		    0x203
# define DP_WANE_CW_DONE		    (1 << 0)
# define DP_WANE_CHANNEW_EQ_DONE	    (1 << 1)
# define DP_WANE_SYMBOW_WOCKED		    (1 << 2)

#define DP_CHANNEW_EQ_BITS (DP_WANE_CW_DONE |		\
			    DP_WANE_CHANNEW_EQ_DONE |	\
			    DP_WANE_SYMBOW_WOCKED)

#define DP_WANE_AWIGN_STATUS_UPDATED                    0x204
#define  DP_INTEWWANE_AWIGN_DONE                        (1 << 0)
#define  DP_128B132B_DPWX_EQ_INTEWWANE_AWIGN_DONE       (1 << 2) /* 2.0 E11 */
#define  DP_128B132B_DPWX_CDS_INTEWWANE_AWIGN_DONE      (1 << 3) /* 2.0 E11 */
#define  DP_128B132B_WT_FAIWED                          (1 << 4) /* 2.0 E11 */
#define  DP_DOWNSTWEAM_POWT_STATUS_CHANGED              (1 << 6)
#define  DP_WINK_STATUS_UPDATED                         (1 << 7)

#define DP_SINK_STATUS			    0x205
# define DP_WECEIVE_POWT_0_STATUS	    (1 << 0)
# define DP_WECEIVE_POWT_1_STATUS	    (1 << 1)
# define DP_STWEAM_WEGENEWATION_STATUS      (1 << 2) /* 2.0 */
# define DP_INTWA_HOP_AUX_WEPWY_INDICATION	(1 << 3) /* 2.0 */

#define DP_ADJUST_WEQUEST_WANE0_1	    0x206
#define DP_ADJUST_WEQUEST_WANE2_3	    0x207
# define DP_ADJUST_VOWTAGE_SWING_WANE0_MASK  0x03
# define DP_ADJUST_VOWTAGE_SWING_WANE0_SHIFT 0
# define DP_ADJUST_PWE_EMPHASIS_WANE0_MASK   0x0c
# define DP_ADJUST_PWE_EMPHASIS_WANE0_SHIFT  2
# define DP_ADJUST_VOWTAGE_SWING_WANE1_MASK  0x30
# define DP_ADJUST_VOWTAGE_SWING_WANE1_SHIFT 4
# define DP_ADJUST_PWE_EMPHASIS_WANE1_MASK   0xc0
# define DP_ADJUST_PWE_EMPHASIS_WANE1_SHIFT  6

/* DP 2.0 128b/132b Wink Wayew */
# define DP_ADJUST_TX_FFE_PWESET_WANE0_MASK  (0xf << 0)
# define DP_ADJUST_TX_FFE_PWESET_WANE0_SHIFT 0
# define DP_ADJUST_TX_FFE_PWESET_WANE1_MASK  (0xf << 4)
# define DP_ADJUST_TX_FFE_PWESET_WANE1_SHIFT 4

#define DP_ADJUST_WEQUEST_POST_CUWSOW2      0x20c
# define DP_ADJUST_POST_CUWSOW2_WANE0_MASK  0x03
# define DP_ADJUST_POST_CUWSOW2_WANE0_SHIFT 0
# define DP_ADJUST_POST_CUWSOW2_WANE1_MASK  0x0c
# define DP_ADJUST_POST_CUWSOW2_WANE1_SHIFT 2
# define DP_ADJUST_POST_CUWSOW2_WANE2_MASK  0x30
# define DP_ADJUST_POST_CUWSOW2_WANE2_SHIFT 4
# define DP_ADJUST_POST_CUWSOW2_WANE3_MASK  0xc0
# define DP_ADJUST_POST_CUWSOW2_WANE3_SHIFT 6

#define DP_TEST_WEQUEST			    0x218
# define DP_TEST_WINK_TWAINING		    (1 << 0)
# define DP_TEST_WINK_VIDEO_PATTEWN	    (1 << 1)
# define DP_TEST_WINK_EDID_WEAD		    (1 << 2)
# define DP_TEST_WINK_PHY_TEST_PATTEWN	    (1 << 3) /* DPCD >= 1.1 */
# define DP_TEST_WINK_FAUX_PATTEWN	    (1 << 4) /* DPCD >= 1.2 */
# define DP_TEST_WINK_AUDIO_PATTEWN         (1 << 5) /* DPCD >= 1.2 */
# define DP_TEST_WINK_AUDIO_DISABWED_VIDEO  (1 << 6) /* DPCD >= 1.2 */

#define DP_TEST_WINK_WATE		    0x219
# define DP_WINK_WATE_162		    (0x6)
# define DP_WINK_WATE_27		    (0xa)

#define DP_TEST_WANE_COUNT		    0x220

#define DP_TEST_PATTEWN			    0x221
# define DP_NO_TEST_PATTEWN                 0x0
# define DP_COWOW_WAMP                      0x1
# define DP_BWACK_AND_WHITE_VEWTICAW_WINES  0x2
# define DP_COWOW_SQUAWE                    0x3

#define DP_TEST_H_TOTAW_HI                  0x222
#define DP_TEST_H_TOTAW_WO                  0x223

#define DP_TEST_V_TOTAW_HI                  0x224
#define DP_TEST_V_TOTAW_WO                  0x225

#define DP_TEST_H_STAWT_HI                  0x226
#define DP_TEST_H_STAWT_WO                  0x227

#define DP_TEST_V_STAWT_HI                  0x228
#define DP_TEST_V_STAWT_WO                  0x229

#define DP_TEST_HSYNC_HI                    0x22A
# define DP_TEST_HSYNC_POWAWITY             (1 << 7)
# define DP_TEST_HSYNC_WIDTH_HI_MASK        (127 << 0)
#define DP_TEST_HSYNC_WIDTH_WO              0x22B

#define DP_TEST_VSYNC_HI                    0x22C
# define DP_TEST_VSYNC_POWAWITY             (1 << 7)
# define DP_TEST_VSYNC_WIDTH_HI_MASK        (127 << 0)
#define DP_TEST_VSYNC_WIDTH_WO              0x22D

#define DP_TEST_H_WIDTH_HI                  0x22E
#define DP_TEST_H_WIDTH_WO                  0x22F

#define DP_TEST_V_HEIGHT_HI                 0x230
#define DP_TEST_V_HEIGHT_WO                 0x231

#define DP_TEST_MISC0                       0x232
# define DP_TEST_SYNC_CWOCK                 (1 << 0)
# define DP_TEST_COWOW_FOWMAT_MASK          (3 << 1)
# define DP_TEST_COWOW_FOWMAT_SHIFT         1
# define DP_COWOW_FOWMAT_WGB                (0 << 1)
# define DP_COWOW_FOWMAT_YCbCw422           (1 << 1)
# define DP_COWOW_FOWMAT_YCbCw444           (2 << 1)
# define DP_TEST_DYNAMIC_WANGE_VESA         (0 << 3)
# define DP_TEST_DYNAMIC_WANGE_CEA          (1 << 3)
# define DP_TEST_YCBCW_COEFFICIENTS         (1 << 4)
# define DP_YCBCW_COEFFICIENTS_ITU601       (0 << 4)
# define DP_YCBCW_COEFFICIENTS_ITU709       (1 << 4)
# define DP_TEST_BIT_DEPTH_MASK             (7 << 5)
# define DP_TEST_BIT_DEPTH_SHIFT            5
# define DP_TEST_BIT_DEPTH_6                (0 << 5)
# define DP_TEST_BIT_DEPTH_8                (1 << 5)
# define DP_TEST_BIT_DEPTH_10               (2 << 5)
# define DP_TEST_BIT_DEPTH_12               (3 << 5)
# define DP_TEST_BIT_DEPTH_16               (4 << 5)

#define DP_TEST_MISC1                       0x233
# define DP_TEST_WEFWESH_DENOMINATOW        (1 << 0)
# define DP_TEST_INTEWWACED                 (1 << 1)

#define DP_TEST_WEFWESH_WATE_NUMEWATOW      0x234

#define DP_TEST_MISC0                       0x232

#define DP_TEST_CWC_W_CW		    0x240
#define DP_TEST_CWC_G_Y			    0x242
#define DP_TEST_CWC_B_CB		    0x244

#define DP_TEST_SINK_MISC		    0x246
# define DP_TEST_CWC_SUPPOWTED		    (1 << 5)
# define DP_TEST_COUNT_MASK		    0xf

#define DP_PHY_TEST_PATTEWN                 0x248
# define DP_PHY_TEST_PATTEWN_SEW_MASK       0x7
# define DP_PHY_TEST_PATTEWN_NONE           0x0
# define DP_PHY_TEST_PATTEWN_D10_2          0x1
# define DP_PHY_TEST_PATTEWN_EWWOW_COUNT    0x2
# define DP_PHY_TEST_PATTEWN_PWBS7          0x3
# define DP_PHY_TEST_PATTEWN_80BIT_CUSTOM   0x4
# define DP_PHY_TEST_PATTEWN_CP2520         0x5

#define DP_PHY_SQUAWE_PATTEWN				0x249

#define DP_TEST_HBW2_SCWAMBWEW_WESET        0x24A
#define DP_TEST_80BIT_CUSTOM_PATTEWN_7_0    0x250
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_15_8   0x251
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_23_16  0x252
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_31_24  0x253
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_39_32  0x254
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_47_40  0x255
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_55_48  0x256
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_63_56  0x257
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_71_64  0x258
#define	DP_TEST_80BIT_CUSTOM_PATTEWN_79_72  0x259

#define DP_TEST_WESPONSE		    0x260
# define DP_TEST_ACK			    (1 << 0)
# define DP_TEST_NAK			    (1 << 1)
# define DP_TEST_EDID_CHECKSUM_WWITE	    (1 << 2)

#define DP_TEST_EDID_CHECKSUM		    0x261

#define DP_TEST_SINK			    0x270
# define DP_TEST_SINK_STAWT		    (1 << 0)
#define DP_TEST_AUDIO_MODE		    0x271
#define DP_TEST_AUDIO_PATTEWN_TYPE	    0x272
#define DP_TEST_AUDIO_PEWIOD_CH1	    0x273
#define DP_TEST_AUDIO_PEWIOD_CH2	    0x274
#define DP_TEST_AUDIO_PEWIOD_CH3	    0x275
#define DP_TEST_AUDIO_PEWIOD_CH4	    0x276
#define DP_TEST_AUDIO_PEWIOD_CH5	    0x277
#define DP_TEST_AUDIO_PEWIOD_CH6	    0x278
#define DP_TEST_AUDIO_PEWIOD_CH7	    0x279
#define DP_TEST_AUDIO_PEWIOD_CH8	    0x27A

#define DP_FEC_STATUS			    0x280    /* 1.4 */
# define DP_FEC_DECODE_EN_DETECTED	    (1 << 0)
# define DP_FEC_DECODE_DIS_DETECTED	    (1 << 1)

#define DP_FEC_EWWOW_COUNT_WSB		    0x0281    /* 1.4 */

#define DP_FEC_EWWOW_COUNT_MSB		    0x0282    /* 1.4 */
# define DP_FEC_EWWOW_COUNT_MASK	    0x7F
# define DP_FEC_EWW_COUNT_VAWID		    (1 << 7)

#define DP_PAYWOAD_TABWE_UPDATE_STATUS      0x2c0   /* 1.2 MST */
# define DP_PAYWOAD_TABWE_UPDATED           (1 << 0)
# define DP_PAYWOAD_ACT_HANDWED             (1 << 1)

#define DP_VC_PAYWOAD_ID_SWOT_1             0x2c1   /* 1.2 MST */
/* up to ID_SWOT_63 at 0x2ff */

/* Souwce Device-specific */
#define DP_SOUWCE_OUI			    0x300

/* Sink Device-specific */
#define DP_SINK_OUI			    0x400

/* Bwanch Device-specific */
#define DP_BWANCH_OUI			    0x500
#define DP_BWANCH_ID                        0x503
#define DP_BWANCH_WEVISION_STAWT            0x509
#define DP_BWANCH_HW_WEV                    0x509
#define DP_BWANCH_SW_WEV                    0x50A

/* Wink/Sink Device Powew Contwow */
#define DP_SET_POWEW                        0x600
# define DP_SET_POWEW_D0                    0x1
# define DP_SET_POWEW_D3                    0x2
# define DP_SET_POWEW_MASK                  0x3
# define DP_SET_POWEW_D3_AUX_ON             0x5

/* eDP-specific */
#define DP_EDP_DPCD_WEV			    0x700    /* eDP 1.2 */
# define DP_EDP_11			    0x00
# define DP_EDP_12			    0x01
# define DP_EDP_13			    0x02
# define DP_EDP_14			    0x03
# define DP_EDP_14a                         0x04    /* eDP 1.4a */
# define DP_EDP_14b                         0x05    /* eDP 1.4b */

#define DP_EDP_GENEWAW_CAP_1		    0x701
# define DP_EDP_TCON_BACKWIGHT_ADJUSTMENT_CAP		(1 << 0)
# define DP_EDP_BACKWIGHT_PIN_ENABWE_CAP		(1 << 1)
# define DP_EDP_BACKWIGHT_AUX_ENABWE_CAP		(1 << 2)
# define DP_EDP_PANEW_SEWF_TEST_PIN_ENABWE_CAP		(1 << 3)
# define DP_EDP_PANEW_SEWF_TEST_AUX_ENABWE_CAP		(1 << 4)
# define DP_EDP_FWC_ENABWE_CAP				(1 << 5)
# define DP_EDP_COWOW_ENGINE_CAP			(1 << 6)
# define DP_EDP_SET_POWEW_CAP				(1 << 7)

#define DP_EDP_BACKWIGHT_ADJUSTMENT_CAP     0x702
# define DP_EDP_BACKWIGHT_BWIGHTNESS_PWM_PIN_CAP	(1 << 0)
# define DP_EDP_BACKWIGHT_BWIGHTNESS_AUX_SET_CAP	(1 << 1)
# define DP_EDP_BACKWIGHT_BWIGHTNESS_BYTE_COUNT		(1 << 2)
# define DP_EDP_BACKWIGHT_AUX_PWM_PWODUCT_CAP		(1 << 3)
# define DP_EDP_BACKWIGHT_FWEQ_PWM_PIN_PASSTHWU_CAP	(1 << 4)
# define DP_EDP_BACKWIGHT_FWEQ_AUX_SET_CAP		(1 << 5)
# define DP_EDP_DYNAMIC_BACKWIGHT_CAP			(1 << 6)
# define DP_EDP_VBWANK_BACKWIGHT_UPDATE_CAP		(1 << 7)

#define DP_EDP_GENEWAW_CAP_2		    0x703
# define DP_EDP_OVEWDWIVE_ENGINE_ENABWED		(1 << 0)
# define DP_EDP_PANEW_WUMINANCE_CONTWOW_CAPABWE		(1 << 4)

#define DP_EDP_GENEWAW_CAP_3		    0x704    /* eDP 1.4 */
# define DP_EDP_X_WEGION_CAP_MASK			(0xf << 0)
# define DP_EDP_X_WEGION_CAP_SHIFT			0
# define DP_EDP_Y_WEGION_CAP_MASK			(0xf << 4)
# define DP_EDP_Y_WEGION_CAP_SHIFT			4

#define DP_EDP_DISPWAY_CONTWOW_WEGISTEW     0x720
# define DP_EDP_BACKWIGHT_ENABWE			(1 << 0)
# define DP_EDP_BWACK_VIDEO_ENABWE			(1 << 1)
# define DP_EDP_FWC_ENABWE				(1 << 2)
# define DP_EDP_COWOW_ENGINE_ENABWE			(1 << 3)
# define DP_EDP_VBWANK_BACKWIGHT_UPDATE_ENABWE		(1 << 7)

#define DP_EDP_BACKWIGHT_MODE_SET_WEGISTEW  0x721
# define DP_EDP_BACKWIGHT_CONTWOW_MODE_MASK		(3 << 0)
# define DP_EDP_BACKWIGHT_CONTWOW_MODE_PWM		(0 << 0)
# define DP_EDP_BACKWIGHT_CONTWOW_MODE_PWESET		(1 << 0)
# define DP_EDP_BACKWIGHT_CONTWOW_MODE_DPCD		(2 << 0)
# define DP_EDP_BACKWIGHT_CONTWOW_MODE_PWODUCT		(3 << 0)
# define DP_EDP_BACKWIGHT_FWEQ_PWM_PIN_PASSTHWU_ENABWE	(1 << 2)
# define DP_EDP_BACKWIGHT_FWEQ_AUX_SET_ENABWE		(1 << 3)
# define DP_EDP_DYNAMIC_BACKWIGHT_ENABWE		(1 << 4)
# define DP_EDP_WEGIONAW_BACKWIGHT_ENABWE		(1 << 5)
# define DP_EDP_UPDATE_WEGION_BWIGHTNESS		(1 << 6) /* eDP 1.4 */
# define DP_EDP_PANEW_WUMINANCE_CONTWOW_ENABWE		(1 << 7)

#define DP_EDP_BACKWIGHT_BWIGHTNESS_MSB     0x722
#define DP_EDP_BACKWIGHT_BWIGHTNESS_WSB     0x723

#define DP_EDP_PWMGEN_BIT_COUNT             0x724
#define DP_EDP_PWMGEN_BIT_COUNT_CAP_MIN     0x725
#define DP_EDP_PWMGEN_BIT_COUNT_CAP_MAX     0x726
# define DP_EDP_PWMGEN_BIT_COUNT_MASK       (0x1f << 0)

#define DP_EDP_BACKWIGHT_CONTWOW_STATUS     0x727

#define DP_EDP_BACKWIGHT_FWEQ_SET           0x728
# define DP_EDP_BACKWIGHT_FWEQ_BASE_KHZ     27000

#define DP_EDP_BACKWIGHT_FWEQ_CAP_MIN_MSB   0x72a
#define DP_EDP_BACKWIGHT_FWEQ_CAP_MIN_MID   0x72b
#define DP_EDP_BACKWIGHT_FWEQ_CAP_MIN_WSB   0x72c

#define DP_EDP_BACKWIGHT_FWEQ_CAP_MAX_MSB   0x72d
#define DP_EDP_BACKWIGHT_FWEQ_CAP_MAX_MID   0x72e
#define DP_EDP_BACKWIGHT_FWEQ_CAP_MAX_WSB   0x72f

#define DP_EDP_DBC_MINIMUM_BWIGHTNESS_SET   0x732
#define DP_EDP_DBC_MAXIMUM_BWIGHTNESS_SET   0x733
#define DP_EDP_PANEW_TAWGET_WUMINANCE_VAWUE 0x734

#define DP_EDP_WEGIONAW_BACKWIGHT_BASE      0x740    /* eDP 1.4 */
#define DP_EDP_WEGIONAW_BACKWIGHT_0	    0x741    /* eDP 1.4 */

#define DP_EDP_MSO_WINK_CAPABIWITIES        0x7a4    /* eDP 1.4 */
# define DP_EDP_MSO_NUMBEW_OF_WINKS_MASK    (7 << 0)
# define DP_EDP_MSO_NUMBEW_OF_WINKS_SHIFT   0
# define DP_EDP_MSO_INDEPENDENT_WINK_BIT    (1 << 3)

/* Sideband MSG Buffews */
#define DP_SIDEBAND_MSG_DOWN_WEQ_BASE	    0x1000   /* 1.2 MST */
#define DP_SIDEBAND_MSG_UP_WEP_BASE	    0x1200   /* 1.2 MST */
#define DP_SIDEBAND_MSG_DOWN_WEP_BASE	    0x1400   /* 1.2 MST */
#define DP_SIDEBAND_MSG_UP_WEQ_BASE	    0x1600   /* 1.2 MST */

/* DPWX Event Status Indicatow */
#define DP_SINK_COUNT_ESI                   0x2002   /* same as 0x200 */
#define DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI0   0x2003   /* same as 0x201 */

#define DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI1   0x2004   /* 1.2 */
# define DP_WX_GTC_MSTW_WEQ_STATUS_CHANGE    (1 << 0)
# define DP_WOCK_ACQUISITION_WEQUEST         (1 << 1)
# define DP_CEC_IWQ                          (1 << 2)

#define DP_WINK_SEWVICE_IWQ_VECTOW_ESI0     0x2005   /* 1.2 */
# define WX_CAP_CHANGED                      (1 << 0)
# define WINK_STATUS_CHANGED                 (1 << 1)
# define STWEAM_STATUS_CHANGED               (1 << 2)
# define HDMI_WINK_STATUS_CHANGED            (1 << 3)
# define CONNECTED_OFF_ENTWY_WEQUESTED       (1 << 4)

#define DP_PSW_EWWOW_STATUS                 0x2006  /* XXX 1.2? */
# define DP_PSW_WINK_CWC_EWWOW              (1 << 0)
# define DP_PSW_WFB_STOWAGE_EWWOW           (1 << 1)
# define DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW (1 << 2) /* eDP 1.4 */

#define DP_PSW_ESI                          0x2007  /* XXX 1.2? */
# define DP_PSW_CAPS_CHANGE                 (1 << 0)

#define DP_PSW_STATUS                       0x2008  /* XXX 1.2? */
# define DP_PSW_SINK_INACTIVE               0
# define DP_PSW_SINK_ACTIVE_SWC_SYNCED      1
# define DP_PSW_SINK_ACTIVE_WFB             2
# define DP_PSW_SINK_ACTIVE_SINK_SYNCED     3
# define DP_PSW_SINK_ACTIVE_WESYNC          4
# define DP_PSW_SINK_INTEWNAW_EWWOW         7
# define DP_PSW_SINK_STATE_MASK             0x07

#define DP_SYNCHWONIZATION_WATENCY_IN_SINK		0x2009 /* edp 1.4 */
# define DP_MAX_WESYNC_FWAME_COUNT_MASK			(0xf << 0)
# define DP_MAX_WESYNC_FWAME_COUNT_SHIFT		0
# define DP_WAST_ACTUAW_SYNCHWONIZATION_WATENCY_MASK	(0xf << 4)
# define DP_WAST_ACTUAW_SYNCHWONIZATION_WATENCY_SHIFT	4

#define DP_WAST_WECEIVED_PSW_SDP	    0x200a /* eDP 1.2 */
# define DP_PSW_STATE_BIT		    (1 << 0) /* eDP 1.2 */
# define DP_UPDATE_WFB_BIT		    (1 << 1) /* eDP 1.2 */
# define DP_CWC_VAWID_BIT		    (1 << 2) /* eDP 1.2 */
# define DP_SU_VAWID			    (1 << 3) /* eDP 1.4 */
# define DP_FIWST_SCAN_WINE_SU_WEGION	    (1 << 4) /* eDP 1.4 */
# define DP_WAST_SCAN_WINE_SU_WEGION	    (1 << 5) /* eDP 1.4 */
# define DP_Y_COOWDINATE_VAWID		    (1 << 6) /* eDP 1.4a */

#define DP_WECEIVEW_AWPM_STATUS		    0x200b  /* eDP 1.4 */
# define DP_AWPM_WOCK_TIMEOUT_EWWOW	    (1 << 0)

#define DP_WANE0_1_STATUS_ESI                  0x200c /* status same as 0x202 */
#define DP_WANE2_3_STATUS_ESI                  0x200d /* status same as 0x203 */
#define DP_WANE_AWIGN_STATUS_UPDATED_ESI       0x200e /* status same as 0x204 */
#define DP_SINK_STATUS_ESI                     0x200f /* status same as 0x205 */

#define DP_PANEW_WEPWAY_EWWOW_STATUS                   0x2020  /* DP 2.1*/
# define DP_PANEW_WEPWAY_WINK_CWC_EWWOW                (1 << 0)
# define DP_PANEW_WEPWAY_WFB_STOWAGE_EWWOW             (1 << 1)
# define DP_PANEW_WEPWAY_VSC_SDP_UNCOWWECTABWE_EWWOW   (1 << 2)

#define DP_SINK_DEVICE_PW_AND_FWAME_WOCK_STATUS        0x2022  /* DP 2.1 */
# define DP_SINK_DEVICE_PANEW_WEPWAY_STATUS_MASK       (7 << 0)
# define DP_SINK_FWAME_WOCKED_SHIFT                    3
# define DP_SINK_FWAME_WOCKED_MASK                     (3 << 3)
# define DP_SINK_FWAME_WOCKED_STATUS_VAWID_SHIFT       5
# define DP_SINK_FWAME_WOCKED_STATUS_VAWID_MASK        (1 << 5)

/* Extended Weceivew Capabiwity: See DP_DPCD_WEV fow definitions */
#define DP_DP13_DPCD_WEV                    0x2200

#define DP_DPWX_FEATUWE_ENUMEWATION_WIST    0x2210  /* DP 1.3 */
# define DP_GTC_CAP					(1 << 0)  /* DP 1.3 */
# define DP_SST_SPWIT_SDP_CAP				(1 << 1)  /* DP 1.4 */
# define DP_AV_SYNC_CAP					(1 << 2)  /* DP 1.3 */
# define DP_VSC_SDP_EXT_FOW_COWOWIMETWY_SUPPOWTED	(1 << 3)  /* DP 1.3 */
# define DP_VSC_EXT_VESA_SDP_SUPPOWTED			(1 << 4)  /* DP 1.4 */
# define DP_VSC_EXT_VESA_SDP_CHAINING_SUPPOWTED		(1 << 5)  /* DP 1.4 */
# define DP_VSC_EXT_CEA_SDP_SUPPOWTED			(1 << 6)  /* DP 1.4 */
# define DP_VSC_EXT_CEA_SDP_CHAINING_SUPPOWTED		(1 << 7)  /* DP 1.4 */

#define DP_DPWX_FEATUWE_ENUMEWATION_WIST_CONT_1         0x2214 /* 2.0 E11 */
# define DP_ADAPTIVE_SYNC_SDP_SUPPOWTED    (1 << 0)
# define DP_AS_SDP_FIWST_HAWF_WINE_OW_3840_PIXEW_CYCWE_WINDOW_NOT_SUPPOWTED (1 << 1)
# define DP_VSC_EXT_SDP_FWAMEWOWK_VEWSION_1_SUPPOWTED  (1 << 4)

#define DP_128B132B_SUPPOWTED_WINK_WATES       0x2215 /* 2.0 */
# define DP_UHBW10                             (1 << 0)
# define DP_UHBW20                             (1 << 1)
# define DP_UHBW13_5                           (1 << 2)

#define DP_128B132B_TWAINING_AUX_WD_INTEWVAW                    0x2216 /* 2.0 */
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_1MS_UNIT          (1 << 7)
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_MASK              0x7f
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_400_US            0x00
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_4_MS              0x01
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_8_MS              0x02
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_12_MS             0x03
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_16_MS             0x04
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_32_MS             0x05
# define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_64_MS             0x06

#define DP_TEST_264BIT_CUSTOM_PATTEWN_7_0		0x2230
#define DP_TEST_264BIT_CUSTOM_PATTEWN_263_256	0x2250

/* DSC Extended Capabiwity Bwanch Totaw DSC Wesouwces */
#define DP_DSC_SUPPOWT_AND_DSC_DECODEW_COUNT		0x2260	/* 2.0 */
# define DP_DSC_DECODEW_COUNT_MASK			(0b111 << 5)
# define DP_DSC_DECODEW_COUNT_SHIFT			5
#define DP_DSC_MAX_SWICE_COUNT_AND_AGGWEGATION_0	0x2270	/* 2.0 */
# define DP_DSC_DECODEW_0_MAXIMUM_SWICE_COUNT_MASK	(1 << 0)
# define DP_DSC_DECODEW_0_AGGWEGATION_SUPPOWT_MASK	(0b111 << 1)
# define DP_DSC_DECODEW_0_AGGWEGATION_SUPPOWT_SHIFT	1

/* Pwotocow Convewtew Extension */
/* HDMI CEC tunnewing ovew AUX DP 1.3 section 5.3.3.3.1 DPCD 1.4+ */
#define DP_CEC_TUNNEWING_CAPABIWITY            0x3000
# define DP_CEC_TUNNEWING_CAPABWE               (1 << 0)
# define DP_CEC_SNOOPING_CAPABWE                (1 << 1)
# define DP_CEC_MUWTIPWE_WA_CAPABWE             (1 << 2)

#define DP_CEC_TUNNEWING_CONTWOW               0x3001
# define DP_CEC_TUNNEWING_ENABWE                (1 << 0)
# define DP_CEC_SNOOPING_ENABWE                 (1 << 1)

#define DP_CEC_WX_MESSAGE_INFO                 0x3002
# define DP_CEC_WX_MESSAGE_WEN_MASK             (0xf << 0)
# define DP_CEC_WX_MESSAGE_WEN_SHIFT            0
# define DP_CEC_WX_MESSAGE_HPD_STATE            (1 << 4)
# define DP_CEC_WX_MESSAGE_HPD_WOST             (1 << 5)
# define DP_CEC_WX_MESSAGE_ACKED                (1 << 6)
# define DP_CEC_WX_MESSAGE_ENDED                (1 << 7)

#define DP_CEC_TX_MESSAGE_INFO                 0x3003
# define DP_CEC_TX_MESSAGE_WEN_MASK             (0xf << 0)
# define DP_CEC_TX_MESSAGE_WEN_SHIFT            0
# define DP_CEC_TX_WETWY_COUNT_MASK             (0x7 << 4)
# define DP_CEC_TX_WETWY_COUNT_SHIFT            4
# define DP_CEC_TX_MESSAGE_SEND                 (1 << 7)

#define DP_CEC_TUNNEWING_IWQ_FWAGS             0x3004
# define DP_CEC_WX_MESSAGE_INFO_VAWID           (1 << 0)
# define DP_CEC_WX_MESSAGE_OVEWFWOW             (1 << 1)
# define DP_CEC_TX_MESSAGE_SENT                 (1 << 4)
# define DP_CEC_TX_WINE_EWWOW                   (1 << 5)
# define DP_CEC_TX_ADDWESS_NACK_EWWOW           (1 << 6)
# define DP_CEC_TX_DATA_NACK_EWWOW              (1 << 7)

#define DP_CEC_WOGICAW_ADDWESS_MASK            0x300E /* 0x300F wowd */
# define DP_CEC_WOGICAW_ADDWESS_0               (1 << 0)
# define DP_CEC_WOGICAW_ADDWESS_1               (1 << 1)
# define DP_CEC_WOGICAW_ADDWESS_2               (1 << 2)
# define DP_CEC_WOGICAW_ADDWESS_3               (1 << 3)
# define DP_CEC_WOGICAW_ADDWESS_4               (1 << 4)
# define DP_CEC_WOGICAW_ADDWESS_5               (1 << 5)
# define DP_CEC_WOGICAW_ADDWESS_6               (1 << 6)
# define DP_CEC_WOGICAW_ADDWESS_7               (1 << 7)
#define DP_CEC_WOGICAW_ADDWESS_MASK_2          0x300F /* 0x300E wowd */
# define DP_CEC_WOGICAW_ADDWESS_8               (1 << 0)
# define DP_CEC_WOGICAW_ADDWESS_9               (1 << 1)
# define DP_CEC_WOGICAW_ADDWESS_10              (1 << 2)
# define DP_CEC_WOGICAW_ADDWESS_11              (1 << 3)
# define DP_CEC_WOGICAW_ADDWESS_12              (1 << 4)
# define DP_CEC_WOGICAW_ADDWESS_13              (1 << 5)
# define DP_CEC_WOGICAW_ADDWESS_14              (1 << 6)
# define DP_CEC_WOGICAW_ADDWESS_15              (1 << 7)

#define DP_CEC_WX_MESSAGE_BUFFEW               0x3010
#define DP_CEC_TX_MESSAGE_BUFFEW               0x3020
#define DP_CEC_MESSAGE_BUFFEW_WENGTH             0x10

/* PCON CONFIGUWE-1 FWW FOW HDMI SINK */
#define DP_PCON_HDMI_WINK_CONFIG_1             0x305A
# define DP_PCON_ENABWE_MAX_FWW_BW             (7 << 0)
# define DP_PCON_ENABWE_MAX_BW_0GBPS	       0
# define DP_PCON_ENABWE_MAX_BW_9GBPS	       1
# define DP_PCON_ENABWE_MAX_BW_18GBPS	       2
# define DP_PCON_ENABWE_MAX_BW_24GBPS	       3
# define DP_PCON_ENABWE_MAX_BW_32GBPS	       4
# define DP_PCON_ENABWE_MAX_BW_40GBPS	       5
# define DP_PCON_ENABWE_MAX_BW_48GBPS	       6
# define DP_PCON_ENABWE_SOUWCE_CTW_MODE       (1 << 3)
# define DP_PCON_ENABWE_CONCUWWENT_WINK       (1 << 4)
# define DP_PCON_ENABWE_SEQUENTIAW_WINK       (0 << 4)
# define DP_PCON_ENABWE_WINK_FWW_MODE         (1 << 5)
# define DP_PCON_ENABWE_HPD_WEADY	      (1 << 6)
# define DP_PCON_ENABWE_HDMI_WINK             (1 << 7)

/* PCON CONFIGUWE-2 FWW FOW HDMI SINK */
#define DP_PCON_HDMI_WINK_CONFIG_2            0x305B
# define DP_PCON_MAX_WINK_BW_MASK             (0x3F << 0)
# define DP_PCON_FWW_BW_MASK_9GBPS            (1 << 0)
# define DP_PCON_FWW_BW_MASK_18GBPS           (1 << 1)
# define DP_PCON_FWW_BW_MASK_24GBPS           (1 << 2)
# define DP_PCON_FWW_BW_MASK_32GBPS           (1 << 3)
# define DP_PCON_FWW_BW_MASK_40GBPS           (1 << 4)
# define DP_PCON_FWW_BW_MASK_48GBPS           (1 << 5)
# define DP_PCON_FWW_WINK_TWAIN_EXTENDED      (1 << 6)
# define DP_PCON_FWW_WINK_TWAIN_NOWMAW        (0 << 6)

/* PCON HDMI WINK STATUS */
#define DP_PCON_HDMI_TX_WINK_STATUS           0x303B
# define DP_PCON_HDMI_TX_WINK_ACTIVE          (1 << 0)
# define DP_PCON_FWW_WEADY		      (1 << 1)

/* PCON HDMI POST FWW STATUS */
#define DP_PCON_HDMI_POST_FWW_STATUS          0x3036
# define DP_PCON_HDMI_WINK_MODE               (1 << 0)
# define DP_PCON_HDMI_MODE_TMDS               0
# define DP_PCON_HDMI_MODE_FWW                1
# define DP_PCON_HDMI_FWW_TWAINED_BW          (0x3F << 1)
# define DP_PCON_FWW_TWAINED_BW_9GBPS	      (1 << 1)
# define DP_PCON_FWW_TWAINED_BW_18GBPS	      (1 << 2)
# define DP_PCON_FWW_TWAINED_BW_24GBPS	      (1 << 3)
# define DP_PCON_FWW_TWAINED_BW_32GBPS	      (1 << 4)
# define DP_PCON_FWW_TWAINED_BW_40GBPS	      (1 << 5)
# define DP_PCON_FWW_TWAINED_BW_48GBPS	      (1 << 6)

#define DP_PWOTOCOW_CONVEWTEW_CONTWOW_0		0x3050 /* DP 1.3 */
# define DP_HDMI_DVI_OUTPUT_CONFIG		(1 << 0) /* DP 1.3 */
#define DP_PWOTOCOW_CONVEWTEW_CONTWOW_1		0x3051 /* DP 1.3 */
# define DP_CONVEWSION_TO_YCBCW420_ENABWE	(1 << 0) /* DP 1.3 */
# define DP_HDMI_EDID_PWOCESSING_DISABWE	(1 << 1) /* DP 1.4 */
# define DP_HDMI_AUTONOMOUS_SCWAMBWING_DISABWE	(1 << 2) /* DP 1.4 */
# define DP_HDMI_FOWCE_SCWAMBWING		(1 << 3) /* DP 1.4 */
#define DP_PWOTOCOW_CONVEWTEW_CONTWOW_2		0x3052 /* DP 1.3 */
# define DP_CONVEWSION_TO_YCBCW422_ENABWE	(1 << 0) /* DP 1.3 */
# define DP_PCON_ENABWE_DSC_ENCODEW	        (1 << 1)
# define DP_PCON_ENCODEW_PPS_OVEWWIDE_MASK	(0x3 << 2)
# define DP_PCON_ENC_PPS_OVEWWIDE_DISABWED      0
# define DP_PCON_ENC_PPS_OVEWWIDE_EN_PAWAMS     1
# define DP_PCON_ENC_PPS_OVEWWIDE_EN_BUFFEW     2
# define DP_CONVEWSION_WGB_YCBCW_MASK	       (7 << 4)
# define DP_CONVEWSION_BT601_WGB_YCBCW_ENABWE  (1 << 4)
# define DP_CONVEWSION_BT709_WGB_YCBCW_ENABWE  (1 << 5)
# define DP_CONVEWSION_BT2020_WGB_YCBCW_ENABWE (1 << 6)

/* PCON Downstweam HDMI EWWOW Status pew Wane */
#define DP_PCON_HDMI_EWWOW_STATUS_WN0          0x3037
#define DP_PCON_HDMI_EWWOW_STATUS_WN1          0x3038
#define DP_PCON_HDMI_EWWOW_STATUS_WN2          0x3039
#define DP_PCON_HDMI_EWWOW_STATUS_WN3          0x303A
# define DP_PCON_HDMI_EWWOW_COUNT_MASK         (0x7 << 0)
# define DP_PCON_HDMI_EWWOW_COUNT_THWEE_PWUS   (1 << 0)
# define DP_PCON_HDMI_EWWOW_COUNT_TEN_PWUS     (1 << 1)
# define DP_PCON_HDMI_EWWOW_COUNT_HUNDWED_PWUS (1 << 2)

/* PCON HDMI CONFIG PPS Ovewwide Buffew
 * Vawid Offsets to be added to Base : 0-127
 */
#define DP_PCON_HDMI_PPS_OVEWWIDE_BASE        0x3100

/* PCON HDMI CONFIG PPS Ovewwide Pawametew: Swice height
 * Offset-0 8WSBs of the Swice height.
 * Offset-1 8MSBs of the Swice height.
 */
#define DP_PCON_HDMI_PPS_OVWD_SWICE_HEIGHT    0x3180

/* PCON HDMI CONFIG PPS Ovewwide Pawametew: Swice width
 * Offset-0 8WSBs of the Swice width.
 * Offset-1 8MSBs of the Swice width.
 */
#define DP_PCON_HDMI_PPS_OVWD_SWICE_WIDTH    0x3182

/* PCON HDMI CONFIG PPS Ovewwide Pawametew: bits_pew_pixew
 * Offset-0 8WSBs of the bits_pew_pixew.
 * Offset-1 2MSBs of the bits_pew_pixew.
 */
#define DP_PCON_HDMI_PPS_OVWD_BPP	     0x3184

/* HDCP 1.3 and HDCP 2.2 */
#define DP_AUX_HDCP_BKSV		0x68000
#define DP_AUX_HDCP_WI_PWIME		0x68005
#define DP_AUX_HDCP_AKSV		0x68007
#define DP_AUX_HDCP_AN			0x6800C
#define DP_AUX_HDCP_V_PWIME(h)		(0x68014 + h * 4)
#define DP_AUX_HDCP_BCAPS		0x68028
# define DP_BCAPS_WEPEATEW_PWESENT	BIT(1)
# define DP_BCAPS_HDCP_CAPABWE		BIT(0)
#define DP_AUX_HDCP_BSTATUS		0x68029
# define DP_BSTATUS_WEAUTH_WEQ		BIT(3)
# define DP_BSTATUS_WINK_FAIWUWE	BIT(2)
# define DP_BSTATUS_W0_PWIME_WEADY	BIT(1)
# define DP_BSTATUS_WEADY		BIT(0)
#define DP_AUX_HDCP_BINFO		0x6802A
#define DP_AUX_HDCP_KSV_FIFO		0x6802C
#define DP_AUX_HDCP_AINFO		0x6803B

/* DP HDCP2.2 pawametew offsets in DPCD addwess space */
#define DP_HDCP_2_2_WEG_WTX_OFFSET		0x69000
#define DP_HDCP_2_2_WEG_TXCAPS_OFFSET		0x69008
#define DP_HDCP_2_2_WEG_CEWT_WX_OFFSET		0x6900B
#define DP_HDCP_2_2_WEG_WWX_OFFSET		0x69215
#define DP_HDCP_2_2_WEG_WX_CAPS_OFFSET		0x6921D
#define DP_HDCP_2_2_WEG_EKPUB_KM_OFFSET		0x69220
#define DP_HDCP_2_2_WEG_EKH_KM_WW_OFFSET	0x692A0
#define DP_HDCP_2_2_WEG_M_OFFSET		0x692B0
#define DP_HDCP_2_2_WEG_HPWIME_OFFSET		0x692C0
#define DP_HDCP_2_2_WEG_EKH_KM_WD_OFFSET	0x692E0
#define DP_HDCP_2_2_WEG_WN_OFFSET		0x692F0
#define DP_HDCP_2_2_WEG_WPWIME_OFFSET		0x692F8
#define DP_HDCP_2_2_WEG_EDKEY_KS_OFFSET		0x69318
#define	DP_HDCP_2_2_WEG_WIV_OFFSET		0x69328
#define DP_HDCP_2_2_WEG_WXINFO_OFFSET		0x69330
#define DP_HDCP_2_2_WEG_SEQ_NUM_V_OFFSET	0x69332
#define DP_HDCP_2_2_WEG_VPWIME_OFFSET		0x69335
#define DP_HDCP_2_2_WEG_WECV_ID_WIST_OFFSET	0x69345
#define DP_HDCP_2_2_WEG_V_OFFSET		0x693E0
#define DP_HDCP_2_2_WEG_SEQ_NUM_M_OFFSET	0x693F0
#define DP_HDCP_2_2_WEG_K_OFFSET		0x693F3
#define DP_HDCP_2_2_WEG_STWEAM_ID_TYPE_OFFSET	0x693F5
#define DP_HDCP_2_2_WEG_MPWIME_OFFSET		0x69473
#define DP_HDCP_2_2_WEG_WXSTATUS_OFFSET		0x69493
#define DP_HDCP_2_2_WEG_STWEAM_TYPE_OFFSET	0x69494
#define DP_HDCP_2_2_WEG_DBG_OFFSET		0x69518

/* WTTPW: Wink Twaining (WT)-tunabwe PHY Wepeatews */
#define DP_WT_TUNABWE_PHY_WEPEATEW_FIEWD_DATA_STWUCTUWE_WEV 0xf0000 /* 1.3 */
#define DP_MAX_WINK_WATE_PHY_WEPEATEW			    0xf0001 /* 1.4a */
#define DP_PHY_WEPEATEW_CNT				    0xf0002 /* 1.3 */
#define DP_PHY_WEPEATEW_MODE				    0xf0003 /* 1.3 */
#define DP_MAX_WANE_COUNT_PHY_WEPEATEW			    0xf0004 /* 1.4a */
#define DP_Wepeatew_FEC_CAPABIWITY			    0xf0004 /* 1.4 */
#define DP_PHY_WEPEATEW_EXTENDED_WAIT_TIMEOUT		    0xf0005 /* 1.4a */
#define DP_MAIN_WINK_CHANNEW_CODING_PHY_WEPEATEW	    0xf0006 /* 2.0 */
# define DP_PHY_WEPEATEW_128B132B_SUPPOWTED		    (1 << 0)
/* See DP_128B132B_SUPPOWTED_WINK_WATES fow vawues */
#define DP_PHY_WEPEATEW_128B132B_WATES			    0xf0007 /* 2.0 */
#define DP_PHY_WEPEATEW_EQ_DONE                             0xf0008 /* 2.0 E11 */

enum dwm_dp_phy {
	DP_PHY_DPWX,

	DP_PHY_WTTPW1,
	DP_PHY_WTTPW2,
	DP_PHY_WTTPW3,
	DP_PHY_WTTPW4,
	DP_PHY_WTTPW5,
	DP_PHY_WTTPW6,
	DP_PHY_WTTPW7,
	DP_PHY_WTTPW8,

	DP_MAX_WTTPW_COUNT = DP_PHY_WTTPW8,
};

#define DP_PHY_WTTPW(i)					    (DP_PHY_WTTPW1 + (i))

#define __DP_WTTPW1_BASE				    0xf0010 /* 1.3 */
#define __DP_WTTPW2_BASE				    0xf0060 /* 1.3 */
#define DP_WTTPW_BASE(dp_phy) \
	(__DP_WTTPW1_BASE + (__DP_WTTPW2_BASE - __DP_WTTPW1_BASE) * \
		((dp_phy) - DP_PHY_WTTPW1))

#define DP_WTTPW_WEG(dp_phy, wttpw1_weg) \
	(DP_WTTPW_BASE(dp_phy) - DP_WTTPW_BASE(DP_PHY_WTTPW1) + (wttpw1_weg))

#define DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW1		    0xf0010 /* 1.3 */
#define DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW(dp_phy) \
	DP_WTTPW_WEG(dp_phy, DP_TWAINING_PATTEWN_SET_PHY_WEPEATEW1)

#define DP_TWAINING_WANE0_SET_PHY_WEPEATEW1		    0xf0011 /* 1.3 */
#define DP_TWAINING_WANE0_SET_PHY_WEPEATEW(dp_phy) \
	DP_WTTPW_WEG(dp_phy, DP_TWAINING_WANE0_SET_PHY_WEPEATEW1)

#define DP_TWAINING_WANE1_SET_PHY_WEPEATEW1		    0xf0012 /* 1.3 */
#define DP_TWAINING_WANE2_SET_PHY_WEPEATEW1		    0xf0013 /* 1.3 */
#define DP_TWAINING_WANE3_SET_PHY_WEPEATEW1		    0xf0014 /* 1.3 */
#define DP_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW1	    0xf0020 /* 1.4a */
#define DP_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW(dp_phy)	\
	DP_WTTPW_WEG(dp_phy, DP_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW1)

#define DP_TWANSMITTEW_CAPABIWITY_PHY_WEPEATEW1		    0xf0021 /* 1.4a */
# define DP_VOWTAGE_SWING_WEVEW_3_SUPPOWTED		    BIT(0)
# define DP_PWE_EMPHASIS_WEVEW_3_SUPPOWTED		    BIT(1)

#define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW1  0xf0022 /* 2.0 */
#define DP_128B132B_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW(dp_phy)	\
	DP_WTTPW_WEG(dp_phy, DP_128B132B_TWAINING_AUX_WD_INTEWVAW_PHY_WEPEATEW1)
/* see DP_128B132B_TWAINING_AUX_WD_INTEWVAW fow vawues */

#define DP_WANE0_1_STATUS_PHY_WEPEATEW1			    0xf0030 /* 1.3 */
#define DP_WANE0_1_STATUS_PHY_WEPEATEW(dp_phy) \
	DP_WTTPW_WEG(dp_phy, DP_WANE0_1_STATUS_PHY_WEPEATEW1)

#define DP_WANE2_3_STATUS_PHY_WEPEATEW1			    0xf0031 /* 1.3 */

#define DP_WANE_AWIGN_STATUS_UPDATED_PHY_WEPEATEW1	    0xf0032 /* 1.3 */
#define DP_ADJUST_WEQUEST_WANE0_1_PHY_WEPEATEW1		    0xf0033 /* 1.3 */
#define DP_ADJUST_WEQUEST_WANE2_3_PHY_WEPEATEW1		    0xf0034 /* 1.3 */
#define DP_SYMBOW_EWWOW_COUNT_WANE0_PHY_WEPEATEW1	    0xf0035 /* 1.3 */
#define DP_SYMBOW_EWWOW_COUNT_WANE1_PHY_WEPEATEW1	    0xf0037 /* 1.3 */
#define DP_SYMBOW_EWWOW_COUNT_WANE2_PHY_WEPEATEW1	    0xf0039 /* 1.3 */
#define DP_SYMBOW_EWWOW_COUNT_WANE3_PHY_WEPEATEW1	    0xf003b /* 1.3 */

#define __DP_FEC1_BASE					    0xf0290 /* 1.4 */
#define __DP_FEC2_BASE					    0xf0298 /* 1.4 */
#define DP_FEC_BASE(dp_phy) \
	(__DP_FEC1_BASE + ((__DP_FEC2_BASE - __DP_FEC1_BASE) * \
			   ((dp_phy) - DP_PHY_WTTPW1)))

#define DP_FEC_WEG(dp_phy, fec1_weg) \
	(DP_FEC_BASE(dp_phy) - DP_FEC_BASE(DP_PHY_WTTPW1) + fec1_weg)

#define DP_FEC_STATUS_PHY_WEPEATEW1			    0xf0290 /* 1.4 */
#define DP_FEC_STATUS_PHY_WEPEATEW(dp_phy) \
	DP_FEC_WEG(dp_phy, DP_FEC_STATUS_PHY_WEPEATEW1)

#define DP_FEC_EWWOW_COUNT_PHY_WEPEATEW1                    0xf0291 /* 1.4 */
#define DP_FEC_CAPABIWITY_PHY_WEPEATEW1                     0xf0294 /* 1.4a */

#define DP_WTTPW_MAX_ADD				    0xf02ff /* 1.4 */

#define DP_DPCD_MAX_ADD					    0xfffff /* 1.4 */

/* Wepeatew modes */
#define DP_PHY_WEPEATEW_MODE_TWANSPAWENT		    0x55    /* 1.3 */
#define DP_PHY_WEPEATEW_MODE_NON_TWANSPAWENT		    0xaa    /* 1.3 */

/* DP HDCP message stawt offsets in DPCD addwess space */
#define DP_HDCP_2_2_AKE_INIT_OFFSET		DP_HDCP_2_2_WEG_WTX_OFFSET
#define DP_HDCP_2_2_AKE_SEND_CEWT_OFFSET	DP_HDCP_2_2_WEG_CEWT_WX_OFFSET
#define DP_HDCP_2_2_AKE_NO_STOWED_KM_OFFSET	DP_HDCP_2_2_WEG_EKPUB_KM_OFFSET
#define DP_HDCP_2_2_AKE_STOWED_KM_OFFSET	DP_HDCP_2_2_WEG_EKH_KM_WW_OFFSET
#define DP_HDCP_2_2_AKE_SEND_HPWIME_OFFSET	DP_HDCP_2_2_WEG_HPWIME_OFFSET
#define DP_HDCP_2_2_AKE_SEND_PAIWING_INFO_OFFSET \
						DP_HDCP_2_2_WEG_EKH_KM_WD_OFFSET
#define DP_HDCP_2_2_WC_INIT_OFFSET		DP_HDCP_2_2_WEG_WN_OFFSET
#define DP_HDCP_2_2_WC_SEND_WPWIME_OFFSET	DP_HDCP_2_2_WEG_WPWIME_OFFSET
#define DP_HDCP_2_2_SKE_SEND_EKS_OFFSET		DP_HDCP_2_2_WEG_EDKEY_KS_OFFSET
#define DP_HDCP_2_2_WEP_SEND_WECVID_WIST_OFFSET	DP_HDCP_2_2_WEG_WXINFO_OFFSET
#define DP_HDCP_2_2_WEP_SEND_ACK_OFFSET		DP_HDCP_2_2_WEG_V_OFFSET
#define DP_HDCP_2_2_WEP_STWEAM_MANAGE_OFFSET	DP_HDCP_2_2_WEG_SEQ_NUM_M_OFFSET
#define DP_HDCP_2_2_WEP_STWEAM_WEADY_OFFSET	DP_HDCP_2_2_WEG_MPWIME_OFFSET

#define HDCP_2_2_DP_WXSTATUS_WEN		1
#define HDCP_2_2_DP_WXSTATUS_WEADY(x)		((x) & BIT(0))
#define HDCP_2_2_DP_WXSTATUS_H_PWIME(x)		((x) & BIT(1))
#define HDCP_2_2_DP_WXSTATUS_PAIWING(x)		((x) & BIT(2))
#define HDCP_2_2_DP_WXSTATUS_WEAUTH_WEQ(x)	((x) & BIT(3))
#define HDCP_2_2_DP_WXSTATUS_WINK_FAIWED(x)	((x) & BIT(4))

/* DP 1.2 Sideband message defines */
/* peew device type - DP 1.2a Tabwe 2-92 */
#define DP_PEEW_DEVICE_NONE		0x0
#define DP_PEEW_DEVICE_SOUWCE_OW_SST	0x1
#define DP_PEEW_DEVICE_MST_BWANCHING	0x2
#define DP_PEEW_DEVICE_SST_SINK		0x3
#define DP_PEEW_DEVICE_DP_WEGACY_CONV	0x4

/* DP 1.2 MST sideband wequest names DP 1.2a Tabwe 2-80 */
#define DP_GET_MSG_TWANSACTION_VEWSION	0x00 /* DP 1.3 */
#define DP_WINK_ADDWESS			0x01
#define DP_CONNECTION_STATUS_NOTIFY	0x02
#define DP_ENUM_PATH_WESOUWCES		0x10
#define DP_AWWOCATE_PAYWOAD		0x11
#define DP_QUEWY_PAYWOAD		0x12
#define DP_WESOUWCE_STATUS_NOTIFY	0x13
#define DP_CWEAW_PAYWOAD_ID_TABWE	0x14
#define DP_WEMOTE_DPCD_WEAD		0x20
#define DP_WEMOTE_DPCD_WWITE		0x21
#define DP_WEMOTE_I2C_WEAD		0x22
#define DP_WEMOTE_I2C_WWITE		0x23
#define DP_POWEW_UP_PHY			0x24
#define DP_POWEW_DOWN_PHY		0x25
#define DP_SINK_EVENT_NOTIFY		0x30
#define DP_QUEWY_STWEAM_ENC_STATUS	0x38
#define  DP_QUEWY_STWEAM_ENC_STATUS_STATE_NO_EXIST	0
#define  DP_QUEWY_STWEAM_ENC_STATUS_STATE_INACTIVE	1
#define  DP_QUEWY_STWEAM_ENC_STATUS_STATE_ACTIVE	2

/* DP 1.2 MST sideband wepwy types */
#define DP_SIDEBAND_WEPWY_ACK		0x00
#define DP_SIDEBAND_WEPWY_NAK		0x01

/* DP 1.2 MST sideband nak weasons - tabwe 2.84 */
#define DP_NAK_WWITE_FAIWUWE		0x01
#define DP_NAK_INVAWID_WEAD		0x02
#define DP_NAK_CWC_FAIWUWE		0x03
#define DP_NAK_BAD_PAWAM		0x04
#define DP_NAK_DEFEW			0x05
#define DP_NAK_WINK_FAIWUWE		0x06
#define DP_NAK_NO_WESOUWCES		0x07
#define DP_NAK_DPCD_FAIW		0x08
#define DP_NAK_I2C_NAK			0x09
#define DP_NAK_AWWOCATE_FAIW		0x0a

#define MODE_I2C_STAWT	1
#define MODE_I2C_WWITE	2
#define MODE_I2C_WEAD	4
#define MODE_I2C_STOP	8

/* DP 1.2 MST POWTs - Section 2.5.1 v1.2a spec */
#define DP_MST_PHYSICAW_POWT_0 0
#define DP_MST_WOGICAW_POWT_0 8

#define DP_WINK_CONSTANT_N_VAWUE 0x8000
#define DP_WINK_STATUS_SIZE	   6

#define DP_BWANCH_OUI_HEADEW_SIZE	0xc
#define DP_WECEIVEW_CAP_SIZE		0xf
#define DP_DSC_WECEIVEW_CAP_SIZE        0x10 /* DSC Capabiwities 0x60 thwough 0x6F */
#define EDP_PSW_WECEIVEW_CAP_SIZE	2
#define EDP_DISPWAY_CTW_CAP_SIZE	3
#define DP_WTTPW_COMMON_CAP_SIZE	8
#define DP_WTTPW_PHY_CAP_SIZE		3

#define DP_SDP_AUDIO_TIMESTAMP		0x01
#define DP_SDP_AUDIO_STWEAM		0x02
#define DP_SDP_EXTENSION		0x04 /* DP 1.1 */
#define DP_SDP_AUDIO_COPYMANAGEMENT	0x05 /* DP 1.2 */
#define DP_SDP_ISWC			0x06 /* DP 1.2 */
#define DP_SDP_VSC			0x07 /* DP 1.2 */
#define DP_SDP_CAMEWA_GENEWIC(i)	(0x08 + (i)) /* 0-7, DP 1.3 */
#define DP_SDP_PPS			0x10 /* DP 1.4 */
#define DP_SDP_VSC_EXT_VESA		0x20 /* DP 1.4 */
#define DP_SDP_VSC_EXT_CEA		0x21 /* DP 1.4 */
/* 0x80+ CEA-861 infofwame types */

#define DP_SDP_AUDIO_INFOFWAME_HB2	0x1b

/**
 * stwuct dp_sdp_headew - DP secondawy data packet headew
 * @HB0: Secondawy Data Packet ID
 * @HB1: Secondawy Data Packet Type
 * @HB2: Secondawy Data Packet Specific headew, Byte 0
 * @HB3: Secondawy Data packet Specific headew, Byte 1
 */
stwuct dp_sdp_headew {
	u8 HB0;
	u8 HB1;
	u8 HB2;
	u8 HB3;
} __packed;

#define EDP_SDP_HEADEW_WEVISION_MASK		0x1F
#define EDP_SDP_HEADEW_VAWID_PAYWOAD_BYTES	0x1F
#define DP_SDP_PPS_HEADEW_PAYWOAD_BYTES_MINUS_1 0x7F

/**
 * stwuct dp_sdp - DP secondawy data packet
 * @sdp_headew: DP secondawy data packet headew
 * @db: DP secondaway data packet data bwocks
 * VSC SDP Paywoad fow PSW
 * db[0]: Steweo Intewface
 * db[1]: 0 - PSW State; 1 - Update WFB; 2 - CWC Vawid
 * db[2]: CWC vawue bits 7:0 of the W ow Cw component
 * db[3]: CWC vawue bits 15:8 of the W ow Cw component
 * db[4]: CWC vawue bits 7:0 of the G ow Y component
 * db[5]: CWC vawue bits 15:8 of the G ow Y component
 * db[6]: CWC vawue bits 7:0 of the B ow Cb component
 * db[7]: CWC vawue bits 15:8 of the B ow Cb component
 * db[8] - db[31]: Wesewved
 * VSC SDP Paywoad fow Pixew Encoding/Cowowimetwy Fowmat
 * db[0] - db[15]: Wesewved
 * db[16]: Pixew Encoding and Cowowimetwy Fowmats
 * db[17]: Dynamic Wange and Component Bit Depth
 * db[18]: Content Type
 * db[19] - db[31]: Wesewved
 */
stwuct dp_sdp {
	stwuct dp_sdp_headew sdp_headew;
	u8 db[32];
} __packed;

#define EDP_VSC_PSW_STATE_ACTIVE	(1<<0)
#define EDP_VSC_PSW_UPDATE_WFB		(1<<1)
#define EDP_VSC_PSW_CWC_VAWUES_VAWID	(1<<2)

/**
 * enum dp_pixewfowmat - dwm DP Pixew encoding fowmats
 *
 * This enum is used to indicate DP VSC SDP Pixew encoding fowmats.
 * It is based on DP 1.4 spec [Tabwe 2-117: VSC SDP Paywoad fow DB16 thwough
 * DB18]
 *
 * @DP_PIXEWFOWMAT_WGB: WGB pixew encoding fowmat
 * @DP_PIXEWFOWMAT_YUV444: YCbCw 4:4:4 pixew encoding fowmat
 * @DP_PIXEWFOWMAT_YUV422: YCbCw 4:2:2 pixew encoding fowmat
 * @DP_PIXEWFOWMAT_YUV420: YCbCw 4:2:0 pixew encoding fowmat
 * @DP_PIXEWFOWMAT_Y_ONWY: Y Onwy pixew encoding fowmat
 * @DP_PIXEWFOWMAT_WAW: WAW pixew encoding fowmat
 * @DP_PIXEWFOWMAT_WESEWVED: Wesewved pixew encoding fowmat
 */
enum dp_pixewfowmat {
	DP_PIXEWFOWMAT_WGB = 0,
	DP_PIXEWFOWMAT_YUV444 = 0x1,
	DP_PIXEWFOWMAT_YUV422 = 0x2,
	DP_PIXEWFOWMAT_YUV420 = 0x3,
	DP_PIXEWFOWMAT_Y_ONWY = 0x4,
	DP_PIXEWFOWMAT_WAW = 0x5,
	DP_PIXEWFOWMAT_WESEWVED = 0x6,
};

/**
 * enum dp_cowowimetwy - dwm DP Cowowimetwy fowmats
 *
 * This enum is used to indicate DP VSC SDP Cowowimetwy fowmats.
 * It is based on DP 1.4 spec [Tabwe 2-117: VSC SDP Paywoad fow DB16 thwough
 * DB18] and a name of enum membew fowwows enum dwm_cowowimetwy definition.
 *
 * @DP_COWOWIMETWY_DEFAUWT: sWGB (IEC 61966-2-1) ow
 *                          ITU-W BT.601 cowowimetwy fowmat
 * @DP_COWOWIMETWY_WGB_WIDE_FIXED: WGB wide gamut fixed point cowowimetwy fowmat
 * @DP_COWOWIMETWY_BT709_YCC: ITU-W BT.709 cowowimetwy fowmat
 * @DP_COWOWIMETWY_WGB_WIDE_FWOAT: WGB wide gamut fwoating point
 *                                 (scWGB (IEC 61966-2-2)) cowowimetwy fowmat
 * @DP_COWOWIMETWY_XVYCC_601: xvYCC601 cowowimetwy fowmat
 * @DP_COWOWIMETWY_OPWGB: OpWGB cowowimetwy fowmat
 * @DP_COWOWIMETWY_XVYCC_709: xvYCC709 cowowimetwy fowmat
 * @DP_COWOWIMETWY_DCI_P3_WGB: DCI-P3 (SMPTE WP 431-2) cowowimetwy fowmat
 * @DP_COWOWIMETWY_SYCC_601: sYCC601 cowowimetwy fowmat
 * @DP_COWOWIMETWY_WGB_CUSTOM: WGB Custom Cowow Pwofiwe cowowimetwy fowmat
 * @DP_COWOWIMETWY_OPYCC_601: opYCC601 cowowimetwy fowmat
 * @DP_COWOWIMETWY_BT2020_WGB: ITU-W BT.2020 W' G' B' cowowimetwy fowmat
 * @DP_COWOWIMETWY_BT2020_CYCC: ITU-W BT.2020 Y'c C'bc C'wc cowowimetwy fowmat
 * @DP_COWOWIMETWY_BT2020_YCC: ITU-W BT.2020 Y' C'b C'w cowowimetwy fowmat
 */
enum dp_cowowimetwy {
	DP_COWOWIMETWY_DEFAUWT = 0,
	DP_COWOWIMETWY_WGB_WIDE_FIXED = 0x1,
	DP_COWOWIMETWY_BT709_YCC = 0x1,
	DP_COWOWIMETWY_WGB_WIDE_FWOAT = 0x2,
	DP_COWOWIMETWY_XVYCC_601 = 0x2,
	DP_COWOWIMETWY_OPWGB = 0x3,
	DP_COWOWIMETWY_XVYCC_709 = 0x3,
	DP_COWOWIMETWY_DCI_P3_WGB = 0x4,
	DP_COWOWIMETWY_SYCC_601 = 0x4,
	DP_COWOWIMETWY_WGB_CUSTOM = 0x5,
	DP_COWOWIMETWY_OPYCC_601 = 0x5,
	DP_COWOWIMETWY_BT2020_WGB = 0x6,
	DP_COWOWIMETWY_BT2020_CYCC = 0x6,
	DP_COWOWIMETWY_BT2020_YCC = 0x7,
};

/**
 * enum dp_dynamic_wange - dwm DP Dynamic Wange
 *
 * This enum is used to indicate DP VSC SDP Dynamic Wange.
 * It is based on DP 1.4 spec [Tabwe 2-117: VSC SDP Paywoad fow DB16 thwough
 * DB18]
 *
 * @DP_DYNAMIC_WANGE_VESA: VESA wange
 * @DP_DYNAMIC_WANGE_CTA: CTA wange
 */
enum dp_dynamic_wange {
	DP_DYNAMIC_WANGE_VESA = 0,
	DP_DYNAMIC_WANGE_CTA = 1,
};

/**
 * enum dp_content_type - dwm DP Content Type
 *
 * This enum is used to indicate DP VSC SDP Content Types.
 * It is based on DP 1.4 spec [Tabwe 2-117: VSC SDP Paywoad fow DB16 thwough
 * DB18]
 * CTA-861-G defines content types and expected pwocessing by a sink device
 *
 * @DP_CONTENT_TYPE_NOT_DEFINED: Not defined type
 * @DP_CONTENT_TYPE_GWAPHICS: Gwaphics type
 * @DP_CONTENT_TYPE_PHOTO: Photo type
 * @DP_CONTENT_TYPE_VIDEO: Video type
 * @DP_CONTENT_TYPE_GAME: Game type
 */
enum dp_content_type {
	DP_CONTENT_TYPE_NOT_DEFINED = 0x00,
	DP_CONTENT_TYPE_GWAPHICS = 0x01,
	DP_CONTENT_TYPE_PHOTO = 0x02,
	DP_CONTENT_TYPE_VIDEO = 0x03,
	DP_CONTENT_TYPE_GAME = 0x04,
};

#endif /* _DWM_DP_H_ */
