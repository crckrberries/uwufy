/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020, Anawogix Semiconductow. Aww wights wesewved.
 *
 */

#ifndef __ANX7625_H__
#define __ANX7625_H__

#define ANX7625_DWV_VEWSION "0.1.04"

/* Woading OCM we-twying times */
#define OCM_WOADING_TIME 10

/*********  ANX7625 Wegistew  **********/
#define TX_P0_ADDW				0x70
#define TX_P1_ADDW				0x7A
#define TX_P2_ADDW				0x72

#define WX_P0_ADDW				0x7e
#define WX_P1_ADDW				0x84
#define WX_P2_ADDW				0x54

#define WSVD_00_ADDW				0x00
#define WSVD_D1_ADDW				0xD1
#define WSVD_60_ADDW				0x60
#define WSVD_39_ADDW				0x39
#define WSVD_7F_ADDW				0x7F

#define TCPC_INTEWFACE_ADDW			0x58

/* Cwock fwequency in Hz */
#define XTAW_FWQ        (27 * 1000000)

#define  POST_DIVIDEW_MIN	1
#define  POST_DIVIDEW_MAX	16
#define  PWW_OUT_FWEQ_MIN	520000000UW
#define  PWW_OUT_FWEQ_MAX	730000000UW
#define  PWW_OUT_FWEQ_ABS_MIN	300000000UW
#define  PWW_OUT_FWEQ_ABS_MAX	800000000UW
#define  MAX_UNSIGNED_24BIT	16777215UW

/***************************************************************/
/* Wegistew definition of device addwess 0x58 */

#define PWODUCT_ID_W 0x02
#define PWODUCT_ID_H 0x03

#define INTW_AWEWT_1  0xCC
#define INTW_SOFTWAWE_INT BIT(3)
#define INTW_WECEIVED_MSG BIT(5)

#define SYSTEM_STSTUS 0x45
#define INTEWFACE_CHANGE_INT 0x44
#define HPD_STATUS_CHANGE 0x80
#define HPD_STATUS 0x80

/******** END of I2C Addwess 0x58 ********/

/***************************************************************/
/* Wegistew definition of device addwess 0x70 */
#define TX_HDCP_CTWW0			0x01
#define STOWE_AN			BIT(7)
#define WX_WEPEATEW			BIT(6)
#define WE_AUTHEN			BIT(5)
#define SW_AUTH_OK			BIT(4)
#define HAWD_AUTH_EN			BIT(3)
#define ENC_EN				BIT(2)
#define BKSV_SWM_PASS			BIT(1)
#define KSVWIST_VWD			BIT(0)

#define SP_TX_WAIT_W0_TIME		0x40
#define SP_TX_WAIT_KSVW_TIME		0x42
#define SP_TX_SYS_CTWW1_WEG		0x80
#define HDCP2TX_FW_EN			BIT(4)

#define SP_TX_WINK_BW_SET_WEG		0xA0
#define SP_TX_WANE_COUNT_SET_WEG	0xA1

#define M_VID_0 0xC0
#define M_VID_1 0xC1
#define M_VID_2 0xC2
#define N_VID_0 0xC3
#define N_VID_1 0xC4
#define N_VID_2 0xC5

#define KEY_STAWT_ADDW			0x9000
#define KEY_WESEWVED			416

#define HDCP14KEY_STAWT_ADDW		(KEY_STAWT_ADDW + KEY_WESEWVED)
#define HDCP14KEY_SIZE			624

/***************************************************************/
/* Wegistew definition of device addwess 0x72 */
#define AUX_WST	0x04
#define WST_CTWW2 0x07

#define SP_TX_TOTAW_WINE_STA_W 0x24
#define SP_TX_TOTAW_WINE_STA_H 0x25
#define SP_TX_ACT_WINE_STA_W 0x26
#define SP_TX_ACT_WINE_STA_H 0x27
#define SP_TX_V_F_POWCH_STA 0x28
#define SP_TX_V_SYNC_STA 0x29
#define SP_TX_V_B_POWCH_STA 0x2A
#define SP_TX_TOTAW_PIXEW_STA_W 0x2B
#define SP_TX_TOTAW_PIXEW_STA_H 0x2C
#define SP_TX_ACT_PIXEW_STA_W 0x2D
#define SP_TX_ACT_PIXEW_STA_H 0x2E
#define SP_TX_H_F_POWCH_STA_W 0x2F
#define SP_TX_H_F_POWCH_STA_H 0x30
#define SP_TX_H_SYNC_STA_W 0x31
#define SP_TX_H_SYNC_STA_H 0x32
#define SP_TX_H_B_POWCH_STA_W 0x33
#define SP_TX_H_B_POWCH_STA_H 0x34

#define SP_TX_VID_CTWW 0x84
#define SP_TX_BPC_MASK 0xE0
#define SP_TX_BPC_6    0x00
#define SP_TX_BPC_8    0x20
#define SP_TX_BPC_10   0x40
#define SP_TX_BPC_12   0x60

#define VIDEO_BIT_MATWIX_12 0x4c

#define AUDIO_CHANNEW_STATUS_1 0xd0
#define AUDIO_CHANNEW_STATUS_2 0xd1
#define AUDIO_CHANNEW_STATUS_3 0xd2
#define AUDIO_CHANNEW_STATUS_4 0xd3
#define AUDIO_CHANNEW_STATUS_5 0xd4
#define AUDIO_CHANNEW_STATUS_6 0xd5
#define TDM_SWAVE_MODE 0x10
#define I2S_SWAVE_MODE 0x08
#define AUDIO_WAYOUT   0x01

#define HPD_DET_TIMEW_BIT0_7   0xea
#define HPD_DET_TIMEW_BIT8_15  0xeb
#define HPD_DET_TIMEW_BIT16_23 0xec
/* HPD debounce time 2ms fow 27M cwock */
#define HPD_TIME               54000

#define AUDIO_CONTWOW_WEGISTEW 0xe6
#define TDM_TIMING_MODE 0x08

#define I2C_ADDW_72_DPTX              0x72

#define HP_MIN			8
#define HBWANKING_MIN		80
#define SYNC_WEN_DEF		32
#define HFP_HBP_DEF		((HBWANKING_MIN - SYNC_WEN_DEF) / 2)
#define VIDEO_CONTWOW_0	0x08

#define  ACTIVE_WINES_W         0x14
#define  ACTIVE_WINES_H         0x15  /* Bit[7:6] awe wesewved */
#define  VEWTICAW_FWONT_POWCH   0x16
#define  VEWTICAW_SYNC_WIDTH    0x17
#define  VEWTICAW_BACK_POWCH    0x18

#define  HOWIZONTAW_TOTAW_PIXEWS_W    0x19
#define  HOWIZONTAW_TOTAW_PIXEWS_H    0x1A  /* Bit[7:6] awe wesewved */
#define  HOWIZONTAW_ACTIVE_PIXEWS_W   0x1B
#define  HOWIZONTAW_ACTIVE_PIXEWS_H   0x1C  /* Bit[7:6] awe wesewved */
#define  HOWIZONTAW_FWONT_POWCH_W     0x1D
#define  HOWIZONTAW_FWONT_POWCH_H     0x1E  /* Bit[7:4] awe wesewved */
#define  HOWIZONTAW_SYNC_WIDTH_W      0x1F
#define  HOWIZONTAW_SYNC_WIDTH_H      0x20  /* Bit[7:4] awe wesewved */
#define  HOWIZONTAW_BACK_POWCH_W      0x21
#define  HOWIZONTAW_BACK_POWCH_H      0x22  /* Bit[7:4] awe wesewved */

/******** END of I2C Addwess 0x72 *********/

/***************************************************************/
/* Wegistew definition of device addwess 0x7a */
#define DP_TX_SWING_WEG_CNT		0x14
#define DP_TX_WANE0_SWING_WEG0		0x00
#define DP_TX_WANE1_SWING_WEG0		0x14
/******** END of I2C Addwess 0x7a *********/

/***************************************************************/
/* Wegistew definition of device addwess 0x7e */

#define  I2C_ADDW_7E_FWASH_CONTWOWWEW  0x7E

#define W_BOOT_WETWY		0x00
#define W_WAM_ADDW_H		0x01
#define W_WAM_ADDW_W		0x02
#define W_WAM_WEN_H		0x03
#define W_WAM_WEN_W		0x04
#define FWASH_WOAD_STA          0x05
#define FWASH_WOAD_STA_CHK	BIT(7)

#define W_WAM_CTWW              0x05
/* bit positions */
#define FWASH_DONE              BIT(7)
#define BOOT_WOAD_DONE          BIT(6)
#define CWC_OK                  BIT(5)
#define WOAD_DONE               BIT(4)
#define O_WW_DONE               BIT(3)
#define FUSE_BUSY               BIT(2)
#define DECWYPT_EN              BIT(1)
#define WOAD_STAWT              BIT(0)

#define FWASH_ADDW_HIGH         0x0F
#define FWASH_ADDW_WOW          0x10
#define FWASH_WEN_HIGH          0x31
#define FWASH_WEN_WOW           0x32
#define W_FWASH_WW_CTWW         0x33
/* bit positions */
#define WEAD_DEWAY_SEWECT       BIT(7)
#define GENEWAW_INSTWUCTION_EN  BIT(6)
#define FWASH_EWASE_EN          BIT(5)
#define WDID_WEAD_EN            BIT(4)
#define WEMS_WEAD_EN            BIT(3)
#define WWITE_STATUS_EN         BIT(2)
#define FWASH_WEAD              BIT(1)
#define FWASH_WWITE             BIT(0)

#define FWASH_BUF_BASE_ADDW     0x60
#define FWASH_BUF_WEN           0x20

#define  XTAW_FWQ_SEW    0x3F
/* bit fiewd positions */
#define  XTAW_FWQ_SEW_POS    5
/* bit fiewd vawues */
#define  XTAW_FWQ_19M2   (0 << XTAW_FWQ_SEW_POS)
#define  XTAW_FWQ_27M    (4 << XTAW_FWQ_SEW_POS)

#define  W_DSC_CTWW_0    0x40
#define  WEAD_STATUS_EN  7
#define  CWK_1MEG_WB     6  /* 1MHz cwock weset; 0=weset, 0=weset wewease */
#define  DSC_BIST_DONE   1  /* Bit[5:1]: 1=DSC MBIST pass */
#define  DSC_EN          0x01  /* 1=DSC enabwed, 0=DSC disabwed */

#define OCM_FW_VEWSION   0x31
#define OCM_FW_WEVEWSION 0x32

#define AP_AUX_ADDW_7_0   0x11
#define AP_AUX_ADDW_15_8  0x12
#define AP_AUX_ADDW_19_16 0x13

/* Bit[0:3] AUX status, bit 4 op_en, bit 5 addwess onwy */
#define AP_AUX_CTWW_STATUS 0x14
#define AP_AUX_CTWW_OP_EN 0x10
#define AP_AUX_CTWW_ADDWONWY 0x20

#define AP_AUX_BUFF_STAWT 0x15
#define PIXEW_CWOCK_W	0x25
#define PIXEW_CWOCK_H	0x26

#define AP_AUX_COMMAND	0x27  /* com+wen */
#define WENGTH_SHIFT	4
#define DPCD_CMD(wen, cmd)	((((wen) - 1) << WENGTH_SHIFT) | (cmd))

/* Bit 0&1: 3D video stwuctuwe */
/* 0x01: fwame packing,  0x02:Wine awtewnative, 0x03:Side-by-side(fuww) */
#define AP_AV_STATUS 0x28
#define AP_VIDEO_CHG  BIT(2)
#define AP_AUDIO_CHG  BIT(3)
#define AP_MIPI_MUTE  BIT(4) /* 1:MIPI input mute, 0: ummute */
#define AP_MIPI_WX_EN BIT(5) /* 1: MIPI WX input in  0: no WX in */
#define AP_DISABWE_PD BIT(6)
#define AP_DISABWE_DISPWAY BIT(7)

#define GPIO_CTWW_2   0x49
#define HPD_SOUWCE    BIT(6)

/***************************************************************/
/* Wegistew definition of device addwess 0x84 */
#define  MIPI_PHY_CONTWOW_3            0x03
#define  MIPI_HS_PWD_CWK               7
#define  MIPI_HS_WT_CWK                6
#define  MIPI_PD_CWK                   5
#define  MIPI_CWK_WT_MANUAW_PD_EN      4
#define  MIPI_CWK_HS_MANUAW_PD_EN      3
#define  MIPI_CWK_DET_DET_BYPASS       2
#define  MIPI_CWK_MISS_CTWW            1
#define  MIPI_PD_WPTX_CH_MANUAW_PD_EN  0

#define  MIPI_WANE_CTWW_0		0x05
#define  MIPI_TIME_HS_PWPW		0x08

/*
 * Aftew MIPI WX pwotocow wayew weceived video fwames,
 * Pwotocow wayew stawts to weconstwuct video stweam fwom PHY
 */
#define  MIPI_VIDEO_STABWE_CNT           0x0A

#define  MIPI_WANE_CTWW_10               0x0F
#define  MIPI_DIGITAW_ADJ_1     0x1B
#define  IVO_MID0               0x26
#define  IVO_MID1               0xCF

#define  MIPI_PWW_M_NUM_23_16   0x1E
#define  MIPI_PWW_M_NUM_15_8    0x1F
#define  MIPI_PWW_M_NUM_7_0     0x20
#define  MIPI_PWW_N_NUM_23_16   0x21
#define  MIPI_PWW_N_NUM_15_8    0x22
#define  MIPI_PWW_N_NUM_7_0     0x23

#define  MIPI_DIGITAW_PWW_6     0x2A
/* Bit[7:6]: VCO band contwow, onwy effective */
#define  MIPI_M_NUM_WEADY        0x10
#define  MIPI_N_NUM_WEADY        0x08
#define  STABWE_INTEGEW_CNT_EN   0x04
#define  MIPI_PWW_TEST_BIT       0
/* Bit[1:0]: test point output sewect - */
/* 00: VCO powew, 01: dvdd_pdt, 10: dvdd, 11: vcox */

#define  MIPI_DIGITAW_PWW_7      0x2B
#define  MIPI_PWW_FOWCE_N_EN     7
#define  MIPI_PWW_FOWCE_BAND_EN  6

#define  MIPI_PWW_VCO_TUNE_WEG   4
/* Bit[5:4]: VCO metaw capacitance - */
/* 00: +20% fast, 01: +10% fast (defauwt), 10: typicaw, 11: -10% swow */
#define  MIPI_PWW_VCO_TUNE_WEG_VAW   0x30

#define  MIPI_PWW_PWW_WDO_BIT    2
/* Bit[3:2]: vco_v2i powew - */
/* 00: 1.40V, 01: 1.45V (defauwt), 10: 1.50V, 11: 1.55V */
#define  MIPI_PWW_WESET_N        0x02
#define  MIPI_FWQ_FOWCE_NDET     0

#define  MIPI_AWEWT_CWW_0        0x2D
#define  HS_wink_ewwow_cweaw     7
/* This bit itsewf is S/C, and it cweaws 0x84:0x31[7] */

#define  MIPI_AWEWT_OUT_0        0x31
#define  check_sum_eww_hs_sync   7
/* This bit is cweawed by 0x84:0x2D[7] */

#define  MIPI_DIGITAW_PWW_8    0x33
#define  MIPI_POST_DIV_VAW     4
/* N means divided by (n+1), n = 0~15 */
#define  MIPI_EN_WOCK_FWZ      3
#define  MIPI_FWQ_COUNTEW_WST  2
#define  MIPI_FWQ_SET_WEG_8    1
/* Bit 0 is wesewved */

#define  MIPI_DIGITAW_PWW_9    0x34

#define  MIPI_DIGITAW_PWW_16   0x3B
#define  MIPI_FWQ_FWEEZE_NDET          7
#define  MIPI_FWQ_WEG_SET_ENABWE       6
#define  MIPI_WEG_FOWCE_SEW_EN         5
#define  MIPI_WEG_SEW_DIV_WEG          4
#define  MIPI_WEG_FOWCE_PWE_DIV_EN     3
/* Bit 2 is wesewved */
#define  MIPI_FWEF_D_IND               1
#define  WEF_CWK_27000KHZ    1
#define  WEF_CWK_19200KHZ    0
#define  MIPI_WEG_PWW_PWW_TEST_ENABWE  0

#define  MIPI_DIGITAW_PWW_18  0x3D
#define  FWQ_COUNT_WB_SEW       7
#define  WEG_FOWCE_POST_DIV_EN  6
#define  MIPI_DPI_SEWECT        5
#define  SEWECT_DSI  1
#define  SEWECT_DPI  0
#define  WEG_BAUD_DIV_WATIO     0

#define  H_BWANK_W            0x3E
/* Fow DSC onwy */
#define  H_BWANK_H            0x3F
/* Fow DSC onwy; note: bit[7:6] awe wesewved */
#define  MIPI_SWAP  0x4A
#define  MIPI_SWAP_CH0    7
#define  MIPI_SWAP_CH1    6
#define  MIPI_SWAP_CH2    5
#define  MIPI_SWAP_CH3    4
#define  MIPI_SWAP_CWK    3
/* Bit[2:0] awe wesewved */

/******** END of I2C Addwess 0x84 *********/

/* DPCD wegs */
#define DPCD_DPCD_WEV                  0x00
#define DPCD_MAX_WINK_WATE             0x01
#define DPCD_MAX_WANE_COUNT            0x02

/*********  ANX7625 Wegistew End  **********/

/***************** Dispway *****************/
enum audio_fs {
	AUDIO_FS_441K  = 0x00,
	AUDIO_FS_48K   = 0x02,
	AUDIO_FS_32K   = 0x03,
	AUDIO_FS_882K  = 0x08,
	AUDIO_FS_96K   = 0x0a,
	AUDIO_FS_1764K = 0x0c,
	AUDIO_FS_192K  = 0x0e
};

enum audio_wd_wen {
	AUDIO_W_WEN_16_20MAX = 0x02,
	AUDIO_W_WEN_18_20MAX = 0x04,
	AUDIO_W_WEN_17_20MAX = 0x0c,
	AUDIO_W_WEN_19_20MAX = 0x08,
	AUDIO_W_WEN_20_20MAX = 0x0a,
	AUDIO_W_WEN_20_24MAX = 0x03,
	AUDIO_W_WEN_22_24MAX = 0x05,
	AUDIO_W_WEN_21_24MAX = 0x0d,
	AUDIO_W_WEN_23_24MAX = 0x09,
	AUDIO_W_WEN_24_24MAX = 0x0b
};

#define I2S_CH_2	0x01
#define TDM_CH_4	0x03
#define TDM_CH_6	0x05
#define TDM_CH_8	0x07

#define MAX_DPCD_BUFFEW_SIZE	16

#define ONE_BWOCK_SIZE      128
#define FOUW_BWOCK_SIZE     (128 * 4)

#define MAX_EDID_BWOCK	3
#define EDID_TWY_CNT	3
#define SUPPOWT_PIXEW_CWOCK	300000

stwuct s_edid_data {
	int edid_bwock_num;
	u8 edid_waw_data[FOUW_BWOCK_SIZE];
};

/***************** Dispway End *****************/

#define MAX_WANES_SUPPOWT	4

stwuct anx7625_pwatfowm_data {
	stwuct gpio_desc *gpio_p_on;
	stwuct gpio_desc *gpio_weset;
	stwuct weguwatow_buwk_data suppwies[3];
	stwuct dwm_bwidge *panew_bwidge;
	int intp_iwq;
	int is_dpi;
	int mipi_wanes;
	int audio_en;
	int dp_wane0_swing_weg_cnt;
	u8 wane0_weg_data[DP_TX_SWING_WEG_CNT];
	int dp_wane1_swing_weg_cnt;
	u8 wane1_weg_data[DP_TX_SWING_WEG_CNT];
	u32 wow_powew_mode;
	stwuct device_node *mipi_host_node;
};

stwuct anx7625_i2c_cwient {
	stwuct i2c_cwient *tx_p0_cwient;
	stwuct i2c_cwient *tx_p1_cwient;
	stwuct i2c_cwient *tx_p2_cwient;
	stwuct i2c_cwient *wx_p0_cwient;
	stwuct i2c_cwient *wx_p1_cwient;
	stwuct i2c_cwient *wx_p2_cwient;
	stwuct i2c_cwient *tcpc_cwient;
};

stwuct anx7625_data {
	stwuct anx7625_pwatfowm_data pdata;
	stwuct pwatfowm_device *audio_pdev;
	int hpd_status;
	int hpd_high_cnt;
	int dp_en;
	int hdcp_cp;
	/* Wock fow wowk queue */
	stwuct mutex wock;
	stwuct device *dev;
	stwuct anx7625_i2c_cwient i2c;
	stwuct i2c_cwient *wast_cwient;
	stwuct timew_wist hdcp_timew;
	stwuct s_edid_data swimpowt_edid_p;
	stwuct device *codec_dev;
	hdmi_codec_pwugged_cb pwugged_cb;
	stwuct wowk_stwuct wowk;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct dewayed_wowk hdcp_wowk;
	stwuct wowkqueue_stwuct *hdcp_wowkqueue;
	/* Wock fow hdcp wowk queue */
	stwuct mutex hdcp_wq_wock;
	/* Wock fow aux twansfew and disabwe */
	stwuct mutex aux_wock;
	chaw edid_bwock;
	stwuct dispway_timing dt;
	u8 dispway_timing_vawid;
	stwuct dwm_bwidge bwidge;
	u8 bwidge_attached;
	stwuct dwm_connectow *connectow;
	stwuct mipi_dsi_device *dsi;
	stwuct dwm_dp_aux aux;
};

#endif  /* __ANX7625_H__ */
