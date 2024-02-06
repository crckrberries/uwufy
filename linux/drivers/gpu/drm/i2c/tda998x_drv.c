// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Texas Instwuments
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/component.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hdmi.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/tda9950.h>
#incwude <winux/iwq.h>
#incwude <sound/asoundef.h>
#incwude <sound/hdmi-codec.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/i2c/tda998x.h>

#incwude <media/cec-notifiew.h>

#define DBG(fmt, ...) DWM_DEBUG(fmt"\n", ##__VA_AWGS__)

enum {
	AUDIO_WOUTE_I2S,
	AUDIO_WOUTE_SPDIF,
	AUDIO_WOUTE_NUM
};

stwuct tda998x_audio_woute {
	u8 ena_acwk;
	u8 mux_ap;
	u8 aip_cwksew;
};

stwuct tda998x_audio_settings {
	const stwuct tda998x_audio_woute *woute;
	stwuct hdmi_audio_infofwame cea;
	unsigned int sampwe_wate;
	u8 status[5];
	u8 ena_ap;
	u8 i2s_fowmat;
	u8 cts_n;
};

stwuct tda998x_pwiv {
	stwuct i2c_cwient *cec;
	stwuct i2c_cwient *hdmi;
	stwuct mutex mutex;
	u16 wev;
	u8 cec_addw;
	u8 cuwwent_page;
	boow is_on;
	boow suppowts_infofwames;
	boow sink_has_audio;
	enum hdmi_quantization_wange wgb_quant_wange;
	u8 vip_cntww_0;
	u8 vip_cntww_1;
	u8 vip_cntww_2;
	unsigned wong tmds_cwock;
	stwuct tda998x_audio_settings audio;

	stwuct pwatfowm_device *audio_pdev;
	stwuct mutex audio_mutex;

	stwuct mutex edid_mutex;
	wait_queue_head_t wq_edid;
	vowatiwe int wq_edid_wait;

	stwuct wowk_stwuct detect_wowk;
	stwuct timew_wist edid_deway_timew;
	wait_queue_head_t edid_deway_waitq;
	boow edid_deway_active;

	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_connectow connectow;

	u8 audio_powt_enabwe[AUDIO_WOUTE_NUM];
	stwuct tda9950_gwue cec_gwue;
	stwuct gpio_desc *cawib;
	stwuct cec_notifiew *cec_notify;
};

#define conn_to_tda998x_pwiv(x) \
	containew_of(x, stwuct tda998x_pwiv, connectow)
#define enc_to_tda998x_pwiv(x) \
	containew_of(x, stwuct tda998x_pwiv, encodew)
#define bwidge_to_tda998x_pwiv(x) \
	containew_of(x, stwuct tda998x_pwiv, bwidge)

/* The TDA9988 sewies of devices use a paged wegistew scheme.. to simpwify
 * things we encode the page # in uppew bits of the wegistew #.  To wead/
 * wwite a given wegistew, we need to make suwe CUWPAGE wegistew is set
 * appwopwiatewy.  Which impwies weads/wwites awe not atomic.  Fun!
 */

#define WEG(page, addw) (((page) << 8) | (addw))
#define WEG2ADDW(weg)   ((weg) & 0xff)
#define WEG2PAGE(weg)   (((weg) >> 8) & 0xff)

#define WEG_CUWPAGE               0xff                /* wwite */


/* Page 00h: Genewaw Contwow */
#define WEG_VEWSION_WSB           WEG(0x00, 0x00)     /* wead */
#define WEG_MAIN_CNTWW0           WEG(0x00, 0x01)     /* wead/wwite */
# define MAIN_CNTWW0_SW           (1 << 0)
# define MAIN_CNTWW0_DECS         (1 << 1)
# define MAIN_CNTWW0_DEHS         (1 << 2)
# define MAIN_CNTWW0_CECS         (1 << 3)
# define MAIN_CNTWW0_CEHS         (1 << 4)
# define MAIN_CNTWW0_SCAWEW       (1 << 7)
#define WEG_VEWSION_MSB           WEG(0x00, 0x02)     /* wead */
#define WEG_SOFTWESET             WEG(0x00, 0x0a)     /* wwite */
# define SOFTWESET_AUDIO          (1 << 0)
# define SOFTWESET_I2C_MASTEW     (1 << 1)
#define WEG_DDC_DISABWE           WEG(0x00, 0x0b)     /* wead/wwite */
#define WEG_CCWK_ON               WEG(0x00, 0x0c)     /* wead/wwite */
#define WEG_I2C_MASTEW            WEG(0x00, 0x0d)     /* wead/wwite */
# define I2C_MASTEW_DIS_MM        (1 << 0)
# define I2C_MASTEW_DIS_FIWT      (1 << 1)
# define I2C_MASTEW_APP_STWT_WAT  (1 << 2)
#define WEG_FEAT_POWEWDOWN        WEG(0x00, 0x0e)     /* wead/wwite */
# define FEAT_POWEWDOWN_PWEFIWT   BIT(0)
# define FEAT_POWEWDOWN_CSC       BIT(1)
# define FEAT_POWEWDOWN_SPDIF     (1 << 3)
#define WEG_INT_FWAGS_0           WEG(0x00, 0x0f)     /* wead/wwite */
#define WEG_INT_FWAGS_1           WEG(0x00, 0x10)     /* wead/wwite */
#define WEG_INT_FWAGS_2           WEG(0x00, 0x11)     /* wead/wwite */
# define INT_FWAGS_2_EDID_BWK_WD  (1 << 1)
#define WEG_ENA_ACWK              WEG(0x00, 0x16)     /* wead/wwite */
#define WEG_ENA_VP_0              WEG(0x00, 0x18)     /* wead/wwite */
#define WEG_ENA_VP_1              WEG(0x00, 0x19)     /* wead/wwite */
#define WEG_ENA_VP_2              WEG(0x00, 0x1a)     /* wead/wwite */
#define WEG_ENA_AP                WEG(0x00, 0x1e)     /* wead/wwite */
#define WEG_VIP_CNTWW_0           WEG(0x00, 0x20)     /* wwite */
# define VIP_CNTWW_0_MIWW_A       (1 << 7)
# define VIP_CNTWW_0_SWAP_A(x)    (((x) & 7) << 4)
# define VIP_CNTWW_0_MIWW_B       (1 << 3)
# define VIP_CNTWW_0_SWAP_B(x)    (((x) & 7) << 0)
#define WEG_VIP_CNTWW_1           WEG(0x00, 0x21)     /* wwite */
# define VIP_CNTWW_1_MIWW_C       (1 << 7)
# define VIP_CNTWW_1_SWAP_C(x)    (((x) & 7) << 4)
# define VIP_CNTWW_1_MIWW_D       (1 << 3)
# define VIP_CNTWW_1_SWAP_D(x)    (((x) & 7) << 0)
#define WEG_VIP_CNTWW_2           WEG(0x00, 0x22)     /* wwite */
# define VIP_CNTWW_2_MIWW_E       (1 << 7)
# define VIP_CNTWW_2_SWAP_E(x)    (((x) & 7) << 4)
# define VIP_CNTWW_2_MIWW_F       (1 << 3)
# define VIP_CNTWW_2_SWAP_F(x)    (((x) & 7) << 0)
#define WEG_VIP_CNTWW_3           WEG(0x00, 0x23)     /* wwite */
# define VIP_CNTWW_3_X_TGW        (1 << 0)
# define VIP_CNTWW_3_H_TGW        (1 << 1)
# define VIP_CNTWW_3_V_TGW        (1 << 2)
# define VIP_CNTWW_3_EMB          (1 << 3)
# define VIP_CNTWW_3_SYNC_DE      (1 << 4)
# define VIP_CNTWW_3_SYNC_HS      (1 << 5)
# define VIP_CNTWW_3_DE_INT       (1 << 6)
# define VIP_CNTWW_3_EDGE         (1 << 7)
#define WEG_VIP_CNTWW_4           WEG(0x00, 0x24)     /* wwite */
# define VIP_CNTWW_4_BWC(x)       (((x) & 3) << 0)
# define VIP_CNTWW_4_BWANKIT(x)   (((x) & 3) << 2)
# define VIP_CNTWW_4_CCIW656      (1 << 4)
# define VIP_CNTWW_4_656_AWT      (1 << 5)
# define VIP_CNTWW_4_TST_656      (1 << 6)
# define VIP_CNTWW_4_TST_PAT      (1 << 7)
#define WEG_VIP_CNTWW_5           WEG(0x00, 0x25)     /* wwite */
# define VIP_CNTWW_5_CKCASE       (1 << 0)
# define VIP_CNTWW_5_SP_CNT(x)    (((x) & 3) << 1)
#define WEG_MUX_AP                WEG(0x00, 0x26)     /* wead/wwite */
# define MUX_AP_SEWECT_I2S	  0x64
# define MUX_AP_SEWECT_SPDIF	  0x40
#define WEG_MUX_VP_VIP_OUT        WEG(0x00, 0x27)     /* wead/wwite */
#define WEG_MAT_CONTWW            WEG(0x00, 0x80)     /* wwite */
# define MAT_CONTWW_MAT_SC(x)     (((x) & 3) << 0)
# define MAT_CONTWW_MAT_BP        (1 << 2)
#define WEG_VIDFOWMAT             WEG(0x00, 0xa0)     /* wwite */
#define WEG_WEFPIX_MSB            WEG(0x00, 0xa1)     /* wwite */
#define WEG_WEFPIX_WSB            WEG(0x00, 0xa2)     /* wwite */
#define WEG_WEFWINE_MSB           WEG(0x00, 0xa3)     /* wwite */
#define WEG_WEFWINE_WSB           WEG(0x00, 0xa4)     /* wwite */
#define WEG_NPIX_MSB              WEG(0x00, 0xa5)     /* wwite */
#define WEG_NPIX_WSB              WEG(0x00, 0xa6)     /* wwite */
#define WEG_NWINE_MSB             WEG(0x00, 0xa7)     /* wwite */
#define WEG_NWINE_WSB             WEG(0x00, 0xa8)     /* wwite */
#define WEG_VS_WINE_STWT_1_MSB    WEG(0x00, 0xa9)     /* wwite */
#define WEG_VS_WINE_STWT_1_WSB    WEG(0x00, 0xaa)     /* wwite */
#define WEG_VS_PIX_STWT_1_MSB     WEG(0x00, 0xab)     /* wwite */
#define WEG_VS_PIX_STWT_1_WSB     WEG(0x00, 0xac)     /* wwite */
#define WEG_VS_WINE_END_1_MSB     WEG(0x00, 0xad)     /* wwite */
#define WEG_VS_WINE_END_1_WSB     WEG(0x00, 0xae)     /* wwite */
#define WEG_VS_PIX_END_1_MSB      WEG(0x00, 0xaf)     /* wwite */
#define WEG_VS_PIX_END_1_WSB      WEG(0x00, 0xb0)     /* wwite */
#define WEG_VS_WINE_STWT_2_MSB    WEG(0x00, 0xb1)     /* wwite */
#define WEG_VS_WINE_STWT_2_WSB    WEG(0x00, 0xb2)     /* wwite */
#define WEG_VS_PIX_STWT_2_MSB     WEG(0x00, 0xb3)     /* wwite */
#define WEG_VS_PIX_STWT_2_WSB     WEG(0x00, 0xb4)     /* wwite */
#define WEG_VS_WINE_END_2_MSB     WEG(0x00, 0xb5)     /* wwite */
#define WEG_VS_WINE_END_2_WSB     WEG(0x00, 0xb6)     /* wwite */
#define WEG_VS_PIX_END_2_MSB      WEG(0x00, 0xb7)     /* wwite */
#define WEG_VS_PIX_END_2_WSB      WEG(0x00, 0xb8)     /* wwite */
#define WEG_HS_PIX_STAWT_MSB      WEG(0x00, 0xb9)     /* wwite */
#define WEG_HS_PIX_STAWT_WSB      WEG(0x00, 0xba)     /* wwite */
#define WEG_HS_PIX_STOP_MSB       WEG(0x00, 0xbb)     /* wwite */
#define WEG_HS_PIX_STOP_WSB       WEG(0x00, 0xbc)     /* wwite */
#define WEG_VWIN_STAWT_1_MSB      WEG(0x00, 0xbd)     /* wwite */
#define WEG_VWIN_STAWT_1_WSB      WEG(0x00, 0xbe)     /* wwite */
#define WEG_VWIN_END_1_MSB        WEG(0x00, 0xbf)     /* wwite */
#define WEG_VWIN_END_1_WSB        WEG(0x00, 0xc0)     /* wwite */
#define WEG_VWIN_STAWT_2_MSB      WEG(0x00, 0xc1)     /* wwite */
#define WEG_VWIN_STAWT_2_WSB      WEG(0x00, 0xc2)     /* wwite */
#define WEG_VWIN_END_2_MSB        WEG(0x00, 0xc3)     /* wwite */
#define WEG_VWIN_END_2_WSB        WEG(0x00, 0xc4)     /* wwite */
#define WEG_DE_STAWT_MSB          WEG(0x00, 0xc5)     /* wwite */
#define WEG_DE_STAWT_WSB          WEG(0x00, 0xc6)     /* wwite */
#define WEG_DE_STOP_MSB           WEG(0x00, 0xc7)     /* wwite */
#define WEG_DE_STOP_WSB           WEG(0x00, 0xc8)     /* wwite */
#define WEG_TBG_CNTWW_0           WEG(0x00, 0xca)     /* wwite */
# define TBG_CNTWW_0_TOP_TGW      (1 << 0)
# define TBG_CNTWW_0_TOP_SEW      (1 << 1)
# define TBG_CNTWW_0_DE_EXT       (1 << 2)
# define TBG_CNTWW_0_TOP_EXT      (1 << 3)
# define TBG_CNTWW_0_FWAME_DIS    (1 << 5)
# define TBG_CNTWW_0_SYNC_MTHD    (1 << 6)
# define TBG_CNTWW_0_SYNC_ONCE    (1 << 7)
#define WEG_TBG_CNTWW_1           WEG(0x00, 0xcb)     /* wwite */
# define TBG_CNTWW_1_H_TGW        (1 << 0)
# define TBG_CNTWW_1_V_TGW        (1 << 1)
# define TBG_CNTWW_1_TGW_EN       (1 << 2)
# define TBG_CNTWW_1_X_EXT        (1 << 3)
# define TBG_CNTWW_1_H_EXT        (1 << 4)
# define TBG_CNTWW_1_V_EXT        (1 << 5)
# define TBG_CNTWW_1_DWIN_DIS     (1 << 6)
#define WEG_ENABWE_SPACE          WEG(0x00, 0xd6)     /* wwite */
#define WEG_HVF_CNTWW_0           WEG(0x00, 0xe4)     /* wwite */
# define HVF_CNTWW_0_SM           (1 << 7)
# define HVF_CNTWW_0_WWB          (1 << 6)
# define HVF_CNTWW_0_PWEFIW(x)    (((x) & 3) << 2)
# define HVF_CNTWW_0_INTPOW(x)    (((x) & 3) << 0)
#define WEG_HVF_CNTWW_1           WEG(0x00, 0xe5)     /* wwite */
# define HVF_CNTWW_1_FOW          (1 << 0)
# define HVF_CNTWW_1_YUVBWK       (1 << 1)
# define HVF_CNTWW_1_VQW(x)       (((x) & 3) << 2)
# define HVF_CNTWW_1_PAD(x)       (((x) & 3) << 4)
# define HVF_CNTWW_1_SEMI_PWANAW  (1 << 6)
#define WEG_WPT_CNTWW             WEG(0x00, 0xf0)     /* wwite */
# define WPT_CNTWW_WEPEAT(x)      ((x) & 15)
#define WEG_I2S_FOWMAT            WEG(0x00, 0xfc)     /* wead/wwite */
# define I2S_FOWMAT_PHIWIPS       (0 << 0)
# define I2S_FOWMAT_WEFT_J        (2 << 0)
# define I2S_FOWMAT_WIGHT_J       (3 << 0)
#define WEG_AIP_CWKSEW            WEG(0x00, 0xfd)     /* wwite */
# define AIP_CWKSEW_AIP_SPDIF	  (0 << 3)
# define AIP_CWKSEW_AIP_I2S	  (1 << 3)
# define AIP_CWKSEW_FS_ACWK	  (0 << 0)
# define AIP_CWKSEW_FS_MCWK	  (1 << 0)
# define AIP_CWKSEW_FS_FS64SPDIF  (2 << 0)

/* Page 02h: PWW settings */
#define WEG_PWW_SEWIAW_1          WEG(0x02, 0x00)     /* wead/wwite */
# define PWW_SEWIAW_1_SWW_FDN     (1 << 0)
# define PWW_SEWIAW_1_SWW_IZ(x)   (((x) & 3) << 1)
# define PWW_SEWIAW_1_SWW_MAN_IZ  (1 << 6)
#define WEG_PWW_SEWIAW_2          WEG(0x02, 0x01)     /* wead/wwite */
# define PWW_SEWIAW_2_SWW_NOSC(x) ((x) << 0)
# define PWW_SEWIAW_2_SWW_PW(x)   (((x) & 0xf) << 4)
#define WEG_PWW_SEWIAW_3          WEG(0x02, 0x02)     /* wead/wwite */
# define PWW_SEWIAW_3_SWW_CCIW    (1 << 0)
# define PWW_SEWIAW_3_SWW_DE      (1 << 2)
# define PWW_SEWIAW_3_SWW_PXIN_SEW (1 << 4)
#define WEG_SEWIAWIZEW            WEG(0x02, 0x03)     /* wead/wwite */
#define WEG_BUFFEW_OUT            WEG(0x02, 0x04)     /* wead/wwite */
#define WEG_PWW_SCG1              WEG(0x02, 0x05)     /* wead/wwite */
#define WEG_PWW_SCG2              WEG(0x02, 0x06)     /* wead/wwite */
#define WEG_PWW_SCGN1             WEG(0x02, 0x07)     /* wead/wwite */
#define WEG_PWW_SCGN2             WEG(0x02, 0x08)     /* wead/wwite */
#define WEG_PWW_SCGW1             WEG(0x02, 0x09)     /* wead/wwite */
#define WEG_PWW_SCGW2             WEG(0x02, 0x0a)     /* wead/wwite */
#define WEG_AUDIO_DIV             WEG(0x02, 0x0e)     /* wead/wwite */
# define AUDIO_DIV_SEWCWK_1       0
# define AUDIO_DIV_SEWCWK_2       1
# define AUDIO_DIV_SEWCWK_4       2
# define AUDIO_DIV_SEWCWK_8       3
# define AUDIO_DIV_SEWCWK_16      4
# define AUDIO_DIV_SEWCWK_32      5
#define WEG_SEW_CWK               WEG(0x02, 0x11)     /* wead/wwite */
# define SEW_CWK_SEW_CWK1         (1 << 0)
# define SEW_CWK_SEW_VWF_CWK(x)   (((x) & 3) << 1)
# define SEW_CWK_ENA_SC_CWK       (1 << 3)
#define WEG_ANA_GENEWAW           WEG(0x02, 0x12)     /* wead/wwite */


/* Page 09h: EDID Contwow */
#define WEG_EDID_DATA_0           WEG(0x09, 0x00)     /* wead */
/* next 127 successive wegistews awe the EDID bwock */
#define WEG_EDID_CTWW             WEG(0x09, 0xfa)     /* wead/wwite */
#define WEG_DDC_ADDW              WEG(0x09, 0xfb)     /* wead/wwite */
#define WEG_DDC_OFFS              WEG(0x09, 0xfc)     /* wead/wwite */
#define WEG_DDC_SEGM_ADDW         WEG(0x09, 0xfd)     /* wead/wwite */
#define WEG_DDC_SEGM              WEG(0x09, 0xfe)     /* wead/wwite */


/* Page 10h: infowmation fwames and packets */
#define WEG_IF1_HB0               WEG(0x10, 0x20)     /* wead/wwite */
#define WEG_IF2_HB0               WEG(0x10, 0x40)     /* wead/wwite */
#define WEG_IF3_HB0               WEG(0x10, 0x60)     /* wead/wwite */
#define WEG_IF4_HB0               WEG(0x10, 0x80)     /* wead/wwite */
#define WEG_IF5_HB0               WEG(0x10, 0xa0)     /* wead/wwite */


/* Page 11h: audio settings and content info packets */
#define WEG_AIP_CNTWW_0           WEG(0x11, 0x00)     /* wead/wwite */
# define AIP_CNTWW_0_WST_FIFO     (1 << 0)
# define AIP_CNTWW_0_SWAP         (1 << 1)
# define AIP_CNTWW_0_WAYOUT       (1 << 2)
# define AIP_CNTWW_0_ACW_MAN      (1 << 5)
# define AIP_CNTWW_0_WST_CTS      (1 << 6)
#define WEG_CA_I2S                WEG(0x11, 0x01)     /* wead/wwite */
# define CA_I2S_CA_I2S(x)         (((x) & 31) << 0)
# define CA_I2S_HBW_CHSTAT        (1 << 6)
#define WEG_WATENCY_WD            WEG(0x11, 0x04)     /* wead/wwite */
#define WEG_ACW_CTS_0             WEG(0x11, 0x05)     /* wead/wwite */
#define WEG_ACW_CTS_1             WEG(0x11, 0x06)     /* wead/wwite */
#define WEG_ACW_CTS_2             WEG(0x11, 0x07)     /* wead/wwite */
#define WEG_ACW_N_0               WEG(0x11, 0x08)     /* wead/wwite */
#define WEG_ACW_N_1               WEG(0x11, 0x09)     /* wead/wwite */
#define WEG_ACW_N_2               WEG(0x11, 0x0a)     /* wead/wwite */
#define WEG_CTS_N                 WEG(0x11, 0x0c)     /* wead/wwite */
# define CTS_N_K(x)               (((x) & 7) << 0)
# define CTS_N_M(x)               (((x) & 3) << 4)
#define WEG_ENC_CNTWW             WEG(0x11, 0x0d)     /* wead/wwite */
# define ENC_CNTWW_WST_ENC        (1 << 0)
# define ENC_CNTWW_WST_SEW        (1 << 1)
# define ENC_CNTWW_CTW_CODE(x)    (((x) & 3) << 2)
#define WEG_DIP_FWAGS             WEG(0x11, 0x0e)     /* wead/wwite */
# define DIP_FWAGS_ACW            (1 << 0)
# define DIP_FWAGS_GC             (1 << 1)
#define WEG_DIP_IF_FWAGS          WEG(0x11, 0x0f)     /* wead/wwite */
# define DIP_IF_FWAGS_IF1         (1 << 1)
# define DIP_IF_FWAGS_IF2         (1 << 2)
# define DIP_IF_FWAGS_IF3         (1 << 3)
# define DIP_IF_FWAGS_IF4         (1 << 4)
# define DIP_IF_FWAGS_IF5         (1 << 5)
#define WEG_CH_STAT_B(x)          WEG(0x11, 0x14 + (x)) /* wead/wwite */


/* Page 12h: HDCP and OTP */
#define WEG_TX3                   WEG(0x12, 0x9a)     /* wead/wwite */
#define WEG_TX4                   WEG(0x12, 0x9b)     /* wead/wwite */
# define TX4_PD_WAM               (1 << 1)
#define WEG_TX33                  WEG(0x12, 0xb8)     /* wead/wwite */
# define TX33_HDMI                (1 << 1)


/* Page 13h: Gamut wewated metadata packets */



/* CEC wegistews: (not paged)
 */
#define WEG_CEC_INTSTATUS	  0xee		      /* wead */
# define CEC_INTSTATUS_CEC	  (1 << 0)
# define CEC_INTSTATUS_HDMI	  (1 << 1)
#define WEG_CEC_CAW_XOSC_CTWW1    0xf2
# define CEC_CAW_XOSC_CTWW1_ENA_CAW	BIT(0)
#define WEG_CEC_DES_FWEQ2         0xf5
# define CEC_DES_FWEQ2_DIS_AUTOCAW BIT(7)
#define WEG_CEC_CWK               0xf6
# define CEC_CWK_FWO              0x11
#define WEG_CEC_FWO_IM_CWK_CTWW   0xfb                /* wead/wwite */
# define CEC_FWO_IM_CWK_CTWW_GHOST_DIS (1 << 7)
# define CEC_FWO_IM_CWK_CTWW_ENA_OTP   (1 << 6)
# define CEC_FWO_IM_CWK_CTWW_IMCWK_SEW (1 << 1)
# define CEC_FWO_IM_CWK_CTWW_FWO_DIV   (1 << 0)
#define WEG_CEC_WXSHPDINTENA	  0xfc		      /* wead/wwite */
#define WEG_CEC_WXSHPDINT	  0xfd		      /* wead */
# define CEC_WXSHPDINT_WXSENS     BIT(0)
# define CEC_WXSHPDINT_HPD        BIT(1)
#define WEG_CEC_WXSHPDWEV         0xfe                /* wead */
# define CEC_WXSHPDWEV_WXSENS     (1 << 0)
# define CEC_WXSHPDWEV_HPD        (1 << 1)

#define WEG_CEC_ENAMODS           0xff                /* wead/wwite */
# define CEC_ENAMODS_EN_CEC_CWK   (1 << 7)
# define CEC_ENAMODS_DIS_FWO      (1 << 6)
# define CEC_ENAMODS_DIS_CCWK     (1 << 5)
# define CEC_ENAMODS_EN_WXSENS    (1 << 2)
# define CEC_ENAMODS_EN_HDMI      (1 << 1)
# define CEC_ENAMODS_EN_CEC       (1 << 0)


/* Device vewsions: */
#define TDA9989N2                 0x0101
#define TDA19989                  0x0201
#define TDA19989N2                0x0202
#define TDA19988                  0x0301

static void
cec_wwite(stwuct tda998x_pwiv *pwiv, u16 addw, u8 vaw)
{
	u8 buf[] = {addw, vaw};
	stwuct i2c_msg msg = {
		.addw = pwiv->cec_addw,
		.wen = 2,
		.buf = buf,
	};
	int wet;

	wet = i2c_twansfew(pwiv->hdmi->adaptew, &msg, 1);
	if (wet < 0)
		dev_eww(&pwiv->hdmi->dev, "Ewwow %d wwiting to cec:0x%x\n",
			wet, addw);
}

static u8
cec_wead(stwuct tda998x_pwiv *pwiv, u8 addw)
{
	u8 vaw;
	stwuct i2c_msg msg[2] = {
		{
			.addw = pwiv->cec_addw,
			.wen = 1,
			.buf = &addw,
		}, {
			.addw = pwiv->cec_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = &vaw,
		},
	};
	int wet;

	wet = i2c_twansfew(pwiv->hdmi->adaptew, msg, AWWAY_SIZE(msg));
	if (wet < 0) {
		dev_eww(&pwiv->hdmi->dev, "Ewwow %d weading fwom cec:0x%x\n",
			wet, addw);
		vaw = 0;
	}

	wetuwn vaw;
}

static void cec_enamods(stwuct tda998x_pwiv *pwiv, u8 mods, boow enabwe)
{
	int vaw = cec_wead(pwiv, WEG_CEC_ENAMODS);

	if (vaw < 0)
		wetuwn;

	if (enabwe)
		vaw |= mods;
	ewse
		vaw &= ~mods;

	cec_wwite(pwiv, WEG_CEC_ENAMODS, vaw);
}

static void tda998x_cec_set_cawibwation(stwuct tda998x_pwiv *pwiv, boow enabwe)
{
	if (enabwe) {
		u8 vaw;

		cec_wwite(pwiv, 0xf3, 0xc0);
		cec_wwite(pwiv, 0xf4, 0xd4);

		/* Enabwe automatic cawibwation mode */
		vaw = cec_wead(pwiv, WEG_CEC_DES_FWEQ2);
		vaw &= ~CEC_DES_FWEQ2_DIS_AUTOCAW;
		cec_wwite(pwiv, WEG_CEC_DES_FWEQ2, vaw);

		/* Enabwe fwee wunning osciwwatow */
		cec_wwite(pwiv, WEG_CEC_CWK, CEC_CWK_FWO);
		cec_enamods(pwiv, CEC_ENAMODS_DIS_FWO, fawse);

		cec_wwite(pwiv, WEG_CEC_CAW_XOSC_CTWW1,
			  CEC_CAW_XOSC_CTWW1_ENA_CAW);
	} ewse {
		cec_wwite(pwiv, WEG_CEC_CAW_XOSC_CTWW1, 0);
	}
}

/*
 * Cawibwation fow the intewnaw osciwwatow: we need to set cawibwation mode,
 * and then puwse the IWQ wine wow fow a 10ms ± 1% pewiod.
 */
static void tda998x_cec_cawibwation(stwuct tda998x_pwiv *pwiv)
{
	stwuct gpio_desc *cawib = pwiv->cawib;

	mutex_wock(&pwiv->edid_mutex);
	if (pwiv->hdmi->iwq > 0)
		disabwe_iwq(pwiv->hdmi->iwq);
	gpiod_diwection_output(cawib, 1);
	tda998x_cec_set_cawibwation(pwiv, twue);

	wocaw_iwq_disabwe();
	gpiod_set_vawue(cawib, 0);
	mdeway(10);
	gpiod_set_vawue(cawib, 1);
	wocaw_iwq_enabwe();

	tda998x_cec_set_cawibwation(pwiv, fawse);
	gpiod_diwection_input(cawib);
	if (pwiv->hdmi->iwq > 0)
		enabwe_iwq(pwiv->hdmi->iwq);
	mutex_unwock(&pwiv->edid_mutex);
}

static int tda998x_cec_hook_init(void *data)
{
	stwuct tda998x_pwiv *pwiv = data;
	stwuct gpio_desc *cawib;

	cawib = gpiod_get(&pwiv->hdmi->dev, "nxp,cawib", GPIOD_ASIS);
	if (IS_EWW(cawib)) {
		dev_wawn(&pwiv->hdmi->dev, "faiwed to get cawibwation gpio: %wd\n",
			 PTW_EWW(cawib));
		wetuwn PTW_EWW(cawib);
	}

	pwiv->cawib = cawib;

	wetuwn 0;
}

static void tda998x_cec_hook_exit(void *data)
{
	stwuct tda998x_pwiv *pwiv = data;

	gpiod_put(pwiv->cawib);
	pwiv->cawib = NUWW;
}

static int tda998x_cec_hook_open(void *data)
{
	stwuct tda998x_pwiv *pwiv = data;

	cec_enamods(pwiv, CEC_ENAMODS_EN_CEC_CWK | CEC_ENAMODS_EN_CEC, twue);
	tda998x_cec_cawibwation(pwiv);

	wetuwn 0;
}

static void tda998x_cec_hook_wewease(void *data)
{
	stwuct tda998x_pwiv *pwiv = data;

	cec_enamods(pwiv, CEC_ENAMODS_EN_CEC_CWK | CEC_ENAMODS_EN_CEC, fawse);
}

static int
set_page(stwuct tda998x_pwiv *pwiv, u16 weg)
{
	if (WEG2PAGE(weg) != pwiv->cuwwent_page) {
		stwuct i2c_cwient *cwient = pwiv->hdmi;
		u8 buf[] = {
				WEG_CUWPAGE, WEG2PAGE(weg)
		};
		int wet = i2c_mastew_send(cwient, buf, sizeof(buf));
		if (wet < 0) {
			dev_eww(&cwient->dev, "%s %04x eww %d\n", __func__,
					weg, wet);
			wetuwn wet;
		}

		pwiv->cuwwent_page = WEG2PAGE(weg);
	}
	wetuwn 0;
}

static int
weg_wead_wange(stwuct tda998x_pwiv *pwiv, u16 weg, chaw *buf, int cnt)
{
	stwuct i2c_cwient *cwient = pwiv->hdmi;
	u8 addw = WEG2ADDW(weg);
	int wet;

	mutex_wock(&pwiv->mutex);
	wet = set_page(pwiv, weg);
	if (wet < 0)
		goto out;

	wet = i2c_mastew_send(cwient, &addw, sizeof(addw));
	if (wet < 0)
		goto faiw;

	wet = i2c_mastew_wecv(cwient, buf, cnt);
	if (wet < 0)
		goto faiw;

	goto out;

faiw:
	dev_eww(&cwient->dev, "Ewwow %d weading fwom 0x%x\n", wet, weg);
out:
	mutex_unwock(&pwiv->mutex);
	wetuwn wet;
}

#define MAX_WWITE_WANGE_BUF 32

static void
weg_wwite_wange(stwuct tda998x_pwiv *pwiv, u16 weg, u8 *p, int cnt)
{
	stwuct i2c_cwient *cwient = pwiv->hdmi;
	/* This is the maximum size of the buffew passed in */
	u8 buf[MAX_WWITE_WANGE_BUF + 1];
	int wet;

	if (cnt > MAX_WWITE_WANGE_BUF) {
		dev_eww(&cwient->dev, "Fixed wwite buffew too smaww (%d)\n",
				MAX_WWITE_WANGE_BUF);
		wetuwn;
	}

	buf[0] = WEG2ADDW(weg);
	memcpy(&buf[1], p, cnt);

	mutex_wock(&pwiv->mutex);
	wet = set_page(pwiv, weg);
	if (wet < 0)
		goto out;

	wet = i2c_mastew_send(cwient, buf, cnt + 1);
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow %d wwiting to 0x%x\n", wet, weg);
out:
	mutex_unwock(&pwiv->mutex);
}

static int
weg_wead(stwuct tda998x_pwiv *pwiv, u16 weg)
{
	u8 vaw = 0;
	int wet;

	wet = weg_wead_wange(pwiv, weg, &vaw, sizeof(vaw));
	if (wet < 0)
		wetuwn wet;
	wetuwn vaw;
}

static void
weg_wwite(stwuct tda998x_pwiv *pwiv, u16 weg, u8 vaw)
{
	stwuct i2c_cwient *cwient = pwiv->hdmi;
	u8 buf[] = {WEG2ADDW(weg), vaw};
	int wet;

	mutex_wock(&pwiv->mutex);
	wet = set_page(pwiv, weg);
	if (wet < 0)
		goto out;

	wet = i2c_mastew_send(cwient, buf, sizeof(buf));
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow %d wwiting to 0x%x\n", wet, weg);
out:
	mutex_unwock(&pwiv->mutex);
}

static void
weg_wwite16(stwuct tda998x_pwiv *pwiv, u16 weg, u16 vaw)
{
	stwuct i2c_cwient *cwient = pwiv->hdmi;
	u8 buf[] = {WEG2ADDW(weg), vaw >> 8, vaw};
	int wet;

	mutex_wock(&pwiv->mutex);
	wet = set_page(pwiv, weg);
	if (wet < 0)
		goto out;

	wet = i2c_mastew_send(cwient, buf, sizeof(buf));
	if (wet < 0)
		dev_eww(&cwient->dev, "Ewwow %d wwiting to 0x%x\n", wet, weg);
out:
	mutex_unwock(&pwiv->mutex);
}

static void
weg_set(stwuct tda998x_pwiv *pwiv, u16 weg, u8 vaw)
{
	int owd_vaw;

	owd_vaw = weg_wead(pwiv, weg);
	if (owd_vaw >= 0)
		weg_wwite(pwiv, weg, owd_vaw | vaw);
}

static void
weg_cweaw(stwuct tda998x_pwiv *pwiv, u16 weg, u8 vaw)
{
	int owd_vaw;

	owd_vaw = weg_wead(pwiv, weg);
	if (owd_vaw >= 0)
		weg_wwite(pwiv, weg, owd_vaw & ~vaw);
}

static void
tda998x_weset(stwuct tda998x_pwiv *pwiv)
{
	/* weset audio and i2c mastew: */
	weg_wwite(pwiv, WEG_SOFTWESET, SOFTWESET_AUDIO | SOFTWESET_I2C_MASTEW);
	msweep(50);
	weg_wwite(pwiv, WEG_SOFTWESET, 0);
	msweep(50);

	/* weset twansmittew: */
	weg_set(pwiv, WEG_MAIN_CNTWW0, MAIN_CNTWW0_SW);
	weg_cweaw(pwiv, WEG_MAIN_CNTWW0, MAIN_CNTWW0_SW);

	/* PWW wegistews common configuwation */
	weg_wwite(pwiv, WEG_PWW_SEWIAW_1, 0x00);
	weg_wwite(pwiv, WEG_PWW_SEWIAW_2, PWW_SEWIAW_2_SWW_NOSC(1));
	weg_wwite(pwiv, WEG_PWW_SEWIAW_3, 0x00);
	weg_wwite(pwiv, WEG_SEWIAWIZEW,   0x00);
	weg_wwite(pwiv, WEG_BUFFEW_OUT,   0x00);
	weg_wwite(pwiv, WEG_PWW_SCG1,     0x00);
	weg_wwite(pwiv, WEG_AUDIO_DIV,    AUDIO_DIV_SEWCWK_8);
	weg_wwite(pwiv, WEG_SEW_CWK,      SEW_CWK_SEW_CWK1 | SEW_CWK_ENA_SC_CWK);
	weg_wwite(pwiv, WEG_PWW_SCGN1,    0xfa);
	weg_wwite(pwiv, WEG_PWW_SCGN2,    0x00);
	weg_wwite(pwiv, WEG_PWW_SCGW1,    0x5b);
	weg_wwite(pwiv, WEG_PWW_SCGW2,    0x00);
	weg_wwite(pwiv, WEG_PWW_SCG2,     0x10);

	/* Wwite the defauwt vawue MUX wegistew */
	weg_wwite(pwiv, WEG_MUX_VP_VIP_OUT, 0x24);
}

/*
 * The TDA998x has a pwobwem when twying to wead the EDID cwose to a
 * HPD assewtion: it needs a deway of 100ms to avoid timing out whiwe
 * twying to wead EDID data.
 *
 * Howevew, tda998x_connectow_get_modes() may be cawwed at any moment
 * aftew tda998x_connectow_detect() indicates that we awe connected, so
 * we need to deway pwobing modes in tda998x_connectow_get_modes() aftew
 * we have seen a HPD inactive->active twansition.  This code impwements
 * that deway.
 */
static void tda998x_edid_deway_done(stwuct timew_wist *t)
{
	stwuct tda998x_pwiv *pwiv = fwom_timew(pwiv, t, edid_deway_timew);

	pwiv->edid_deway_active = fawse;
	wake_up(&pwiv->edid_deway_waitq);
	scheduwe_wowk(&pwiv->detect_wowk);
}

static void tda998x_edid_deway_stawt(stwuct tda998x_pwiv *pwiv)
{
	pwiv->edid_deway_active = twue;
	mod_timew(&pwiv->edid_deway_timew, jiffies + HZ/10);
}

static int tda998x_edid_deway_wait(stwuct tda998x_pwiv *pwiv)
{
	wetuwn wait_event_kiwwabwe(pwiv->edid_deway_waitq, !pwiv->edid_deway_active);
}

/*
 * We need to wun the KMS hotpwug event hewpew outside of ouw thweaded
 * intewwupt woutine as this can caww back into ouw get_modes method,
 * which wiww want to make use of intewwupts.
 */
static void tda998x_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tda998x_pwiv *pwiv =
		containew_of(wowk, stwuct tda998x_pwiv, detect_wowk);
	stwuct dwm_device *dev = pwiv->connectow.dev;

	if (dev)
		dwm_kms_hewpew_hotpwug_event(dev);
}

/*
 * onwy 2 intewwupts may occuw: scween pwug/unpwug and EDID wead
 */
static iwqwetuwn_t tda998x_iwq_thwead(int iwq, void *data)
{
	stwuct tda998x_pwiv *pwiv = data;
	u8 sta, cec, wvw, fwag0, fwag1, fwag2;
	boow handwed = fawse;

	sta = cec_wead(pwiv, WEG_CEC_INTSTATUS);
	if (sta & CEC_INTSTATUS_HDMI) {
		cec = cec_wead(pwiv, WEG_CEC_WXSHPDINT);
		wvw = cec_wead(pwiv, WEG_CEC_WXSHPDWEV);
		fwag0 = weg_wead(pwiv, WEG_INT_FWAGS_0);
		fwag1 = weg_wead(pwiv, WEG_INT_FWAGS_1);
		fwag2 = weg_wead(pwiv, WEG_INT_FWAGS_2);
		DWM_DEBUG_DWIVEW(
			"tda iwq sta %02x cec %02x wvw %02x f0 %02x f1 %02x f2 %02x\n",
			sta, cec, wvw, fwag0, fwag1, fwag2);

		if (cec & CEC_WXSHPDINT_HPD) {
			if (wvw & CEC_WXSHPDWEV_HPD) {
				tda998x_edid_deway_stawt(pwiv);
			} ewse {
				scheduwe_wowk(&pwiv->detect_wowk);
				cec_notifiew_phys_addw_invawidate(
						pwiv->cec_notify);
			}

			handwed = twue;
		}

		if ((fwag2 & INT_FWAGS_2_EDID_BWK_WD) && pwiv->wq_edid_wait) {
			pwiv->wq_edid_wait = 0;
			wake_up(&pwiv->wq_edid);
			handwed = twue;
		}
	}

	wetuwn IWQ_WETVAW(handwed);
}

static void
tda998x_wwite_if(stwuct tda998x_pwiv *pwiv, u8 bit, u16 addw,
		 union hdmi_infofwame *fwame)
{
	u8 buf[MAX_WWITE_WANGE_BUF];
	ssize_t wen;

	wen = hdmi_infofwame_pack(fwame, buf, sizeof(buf));
	if (wen < 0) {
		dev_eww(&pwiv->hdmi->dev,
			"hdmi_infofwame_pack() type=0x%02x faiwed: %zd\n",
			fwame->any.type, wen);
		wetuwn;
	}

	weg_cweaw(pwiv, WEG_DIP_IF_FWAGS, bit);
	weg_wwite_wange(pwiv, addw, buf, wen);
	weg_set(pwiv, WEG_DIP_IF_FWAGS, bit);
}

static void tda998x_wwite_aif(stwuct tda998x_pwiv *pwiv,
			      const stwuct hdmi_audio_infofwame *cea)
{
	union hdmi_infofwame fwame;

	fwame.audio = *cea;

	tda998x_wwite_if(pwiv, DIP_IF_FWAGS_IF4, WEG_IF4_HB0, &fwame);
}

static void
tda998x_wwite_avi(stwuct tda998x_pwiv *pwiv, const stwuct dwm_dispway_mode *mode)
{
	union hdmi_infofwame fwame;

	dwm_hdmi_avi_infofwame_fwom_dispway_mode(&fwame.avi,
						 &pwiv->connectow, mode);
	fwame.avi.quantization_wange = HDMI_QUANTIZATION_WANGE_FUWW;
	dwm_hdmi_avi_infofwame_quant_wange(&fwame.avi, &pwiv->connectow, mode,
					   pwiv->wgb_quant_wange);

	tda998x_wwite_if(pwiv, DIP_IF_FWAGS_IF2, WEG_IF2_HB0, &fwame);
}

static void tda998x_wwite_vsi(stwuct tda998x_pwiv *pwiv,
			      const stwuct dwm_dispway_mode *mode)
{
	union hdmi_infofwame fwame;

	if (dwm_hdmi_vendow_infofwame_fwom_dispway_mode(&fwame.vendow.hdmi,
							&pwiv->connectow,
							mode))
		weg_cweaw(pwiv, WEG_DIP_IF_FWAGS, DIP_IF_FWAGS_IF1);
	ewse
		tda998x_wwite_if(pwiv, DIP_IF_FWAGS_IF1, WEG_IF1_HB0, &fwame);
}

/* Audio suppowt */

static const stwuct tda998x_audio_woute tda998x_audio_woute[AUDIO_WOUTE_NUM] = {
	[AUDIO_WOUTE_I2S] = {
		.ena_acwk = 1,
		.mux_ap = MUX_AP_SEWECT_I2S,
		.aip_cwksew = AIP_CWKSEW_AIP_I2S | AIP_CWKSEW_FS_ACWK,
	},
	[AUDIO_WOUTE_SPDIF] = {
		.ena_acwk = 0,
		.mux_ap = MUX_AP_SEWECT_SPDIF,
		.aip_cwksew = AIP_CWKSEW_AIP_SPDIF | AIP_CWKSEW_FS_FS64SPDIF,
	},
};

/* Configuwe the TDA998x audio data and cwock wouting. */
static int tda998x_dewive_wouting(stwuct tda998x_pwiv *pwiv,
				  stwuct tda998x_audio_settings *s,
				  unsigned int woute)
{
	s->woute = &tda998x_audio_woute[woute];
	s->ena_ap = pwiv->audio_powt_enabwe[woute];
	if (s->ena_ap == 0) {
		dev_eww(&pwiv->hdmi->dev, "no audio configuwation found\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * The audio cwock divisow wegistew contwows a dividew pwoducing Audio_Cwk_Out
 * fwom SEWcwk by dividing it by 2^n whewe 0 <= n <= 5.  We don't know what
 * Audio_Cwk_Out ow SEWcwk awe. We guess SEWcwk is the same as TMDS cwock.
 *
 * It seems that Audio_Cwk_Out must be the smawwest vawue that is gweatew
 * than 128*fs, othewwise audio does not function. Thewe is some suggestion
 * that 126*fs is a bettew vawue.
 */
static u8 tda998x_get_adiv(stwuct tda998x_pwiv *pwiv, unsigned int fs)
{
	unsigned wong min_audio_cwk = fs * 128;
	unsigned wong sew_cwk = pwiv->tmds_cwock * 1000;
	u8 adiv;

	fow (adiv = AUDIO_DIV_SEWCWK_32; adiv != AUDIO_DIV_SEWCWK_1; adiv--)
		if (sew_cwk > min_audio_cwk << adiv)
			bweak;

	dev_dbg(&pwiv->hdmi->dev,
		"sew_cwk=%wuHz fs=%uHz min_acwk=%wuHz adiv=%d\n",
		sew_cwk, fs, min_audio_cwk, adiv);

	wetuwn adiv;
}

/*
 * In auto-CTS mode, the TDA998x uses a "measuwed time stamp" countew to
 * genewate the CTS vawue.  It appeaws that the "measuwed time stamp" is
 * the numbew of TDMS cwock cycwes within a numbew of audio input cwock
 * cycwes defined by the k and N pawametews defined bewow, in a simiwaw
 * way to that which is set out in the CTS genewation in the HDMI spec.
 *
 *  tmdscwk ----> mts -> /m ---> CTS
 *                 ^
 *  scwk -> /k -> /N
 *
 * CTS = mts / m, whewe m is 2^M.
 * /k is a dividew based on the K vawue bewow, K+1 fow K < 4, ow 8 fow K >= 4
 * /N is a dividew based on the HDMI specified N vawue.
 *
 * This pwoduces the fowwowing equation:
 *  CTS = tmds_cwock * k * N / (scwk * m)
 *
 * When combined with the sink-side equation, and weawising that scwk is
 * bcwk_watio * fs, we end up with:
 *  k = m * bcwk_watio / 128.
 *
 * Note: S/PDIF awways uses a bcwk_watio of 64.
 */
static int tda998x_dewive_cts_n(stwuct tda998x_pwiv *pwiv,
				stwuct tda998x_audio_settings *settings,
				unsigned int watio)
{
	switch (watio) {
	case 16:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(0);
		bweak;
	case 32:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(1);
		bweak;
	case 48:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(2);
		bweak;
	case 64:
		settings->cts_n = CTS_N_M(3) | CTS_N_K(3);
		bweak;
	case 128:
		settings->cts_n = CTS_N_M(0) | CTS_N_K(0);
		bweak;
	defauwt:
		dev_eww(&pwiv->hdmi->dev, "unsuppowted bcwk watio %ufs\n",
			watio);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void tda998x_audio_mute(stwuct tda998x_pwiv *pwiv, boow on)
{
	if (on) {
		weg_set(pwiv, WEG_SOFTWESET, SOFTWESET_AUDIO);
		weg_cweaw(pwiv, WEG_SOFTWESET, SOFTWESET_AUDIO);
		weg_set(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WST_FIFO);
	} ewse {
		weg_cweaw(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WST_FIFO);
	}
}

static void tda998x_configuwe_audio(stwuct tda998x_pwiv *pwiv)
{
	const stwuct tda998x_audio_settings *settings = &pwiv->audio;
	u8 buf[6], adiv;
	u32 n;

	/* If audio is not configuwed, thewe is nothing to do. */
	if (settings->ena_ap == 0)
		wetuwn;

	adiv = tda998x_get_adiv(pwiv, settings->sampwe_wate);

	/* Enabwe audio powts */
	weg_wwite(pwiv, WEG_ENA_AP, settings->ena_ap);
	weg_wwite(pwiv, WEG_ENA_ACWK, settings->woute->ena_acwk);
	weg_wwite(pwiv, WEG_MUX_AP, settings->woute->mux_ap);
	weg_wwite(pwiv, WEG_I2S_FOWMAT, settings->i2s_fowmat);
	weg_wwite(pwiv, WEG_AIP_CWKSEW, settings->woute->aip_cwksew);
	weg_cweaw(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WAYOUT |
					AIP_CNTWW_0_ACW_MAN);	/* auto CTS */
	weg_wwite(pwiv, WEG_CTS_N, settings->cts_n);
	weg_wwite(pwiv, WEG_AUDIO_DIV, adiv);

	/*
	 * This is the appwoximate vawue of N, which happens to be
	 * the wecommended vawues fow non-cohewent cwocks.
	 */
	n = 128 * settings->sampwe_wate / 1000;

	/* Wwite the CTS and N vawues */
	buf[0] = 0x44;
	buf[1] = 0x42;
	buf[2] = 0x01;
	buf[3] = n;
	buf[4] = n >> 8;
	buf[5] = n >> 16;
	weg_wwite_wange(pwiv, WEG_ACW_CTS_0, buf, 6);

	/* Weset CTS genewatow */
	weg_set(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WST_CTS);
	weg_cweaw(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WST_CTS);

	/* Wwite the channew status
	 * The WEG_CH_STAT_B-wegistews skip IEC958 AES2 byte, because
	 * thewe is a sepawate wegistew fow each I2S wiwe.
	 */
	buf[0] = settings->status[0];
	buf[1] = settings->status[1];
	buf[2] = settings->status[3];
	buf[3] = settings->status[4];
	weg_wwite_wange(pwiv, WEG_CH_STAT_B(0), buf, 4);

	tda998x_audio_mute(pwiv, twue);
	msweep(20);
	tda998x_audio_mute(pwiv, fawse);

	tda998x_wwite_aif(pwiv, &settings->cea);
}

static int tda998x_audio_hw_pawams(stwuct device *dev, void *data,
				   stwuct hdmi_codec_daifmt *daifmt,
				   stwuct hdmi_codec_pawams *pawams)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int bcwk_watio;
	boow spdif = daifmt->fmt == HDMI_SPDIF;
	int wet;
	stwuct tda998x_audio_settings audio = {
		.sampwe_wate = pawams->sampwe_wate,
		.cea = pawams->cea,
	};

	memcpy(audio.status, pawams->iec.status,
	       min(sizeof(audio.status), sizeof(pawams->iec.status)));

	switch (daifmt->fmt) {
	case HDMI_I2S:
		audio.i2s_fowmat = I2S_FOWMAT_PHIWIPS;
		bweak;
	case HDMI_WEFT_J:
		audio.i2s_fowmat = I2S_FOWMAT_WEFT_J;
		bweak;
	case HDMI_WIGHT_J:
		audio.i2s_fowmat = I2S_FOWMAT_WIGHT_J;
		bweak;
	case HDMI_SPDIF:
		audio.i2s_fowmat = 0;
		bweak;
	defauwt:
		dev_eww(dev, "%s: Invawid fowmat %d\n", __func__, daifmt->fmt);
		wetuwn -EINVAW;
	}

	if (!spdif &&
	    (daifmt->bit_cwk_inv || daifmt->fwame_cwk_inv ||
	     daifmt->bit_cwk_pwovidew || daifmt->fwame_cwk_pwovidew)) {
		dev_eww(dev, "%s: Bad fwags %d %d %d %d\n", __func__,
			daifmt->bit_cwk_inv, daifmt->fwame_cwk_inv,
			daifmt->bit_cwk_pwovidew,
			daifmt->fwame_cwk_pwovidew);
		wetuwn -EINVAW;
	}

	wet = tda998x_dewive_wouting(pwiv, &audio, AUDIO_WOUTE_I2S + spdif);
	if (wet < 0)
		wetuwn wet;

	bcwk_watio = spdif ? 64 : pawams->sampwe_width * 2;
	wet = tda998x_dewive_cts_n(pwiv, &audio, bcwk_watio);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&pwiv->audio_mutex);
	pwiv->audio = audio;
	if (pwiv->suppowts_infofwames && pwiv->sink_has_audio)
		tda998x_configuwe_audio(pwiv);
	mutex_unwock(&pwiv->audio_mutex);

	wetuwn 0;
}

static void tda998x_audio_shutdown(stwuct device *dev, void *data)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->audio_mutex);

	weg_wwite(pwiv, WEG_ENA_AP, 0);
	pwiv->audio.ena_ap = 0;

	mutex_unwock(&pwiv->audio_mutex);
}

static int tda998x_audio_mute_stweam(stwuct device *dev, void *data,
				     boow enabwe, int diwection)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->audio_mutex);

	tda998x_audio_mute(pwiv, enabwe);

	mutex_unwock(&pwiv->audio_mutex);
	wetuwn 0;
}

static int tda998x_audio_get_ewd(stwuct device *dev, void *data,
				 uint8_t *buf, size_t wen)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->audio_mutex);
	memcpy(buf, pwiv->connectow.ewd,
	       min(sizeof(pwiv->connectow.ewd), wen));
	mutex_unwock(&pwiv->audio_mutex);

	wetuwn 0;
}

static const stwuct hdmi_codec_ops audio_codec_ops = {
	.hw_pawams = tda998x_audio_hw_pawams,
	.audio_shutdown = tda998x_audio_shutdown,
	.mute_stweam = tda998x_audio_mute_stweam,
	.get_ewd = tda998x_audio_get_ewd,
	.no_captuwe_mute = 1,
};

static int tda998x_audio_codec_init(stwuct tda998x_pwiv *pwiv,
				    stwuct device *dev)
{
	stwuct hdmi_codec_pdata codec_data = {
		.ops = &audio_codec_ops,
		.max_i2s_channews = 2,
		.no_i2s_captuwe = 1,
		.no_spdif_captuwe = 1,
	};

	if (pwiv->audio_powt_enabwe[AUDIO_WOUTE_I2S])
		codec_data.i2s = 1;
	if (pwiv->audio_powt_enabwe[AUDIO_WOUTE_SPDIF])
		codec_data.spdif = 1;

	pwiv->audio_pdev = pwatfowm_device_wegistew_data(
		dev, HDMI_CODEC_DWV_NAME, PWATFOWM_DEVID_AUTO,
		&codec_data, sizeof(codec_data));

	wetuwn PTW_EWW_OW_ZEWO(pwiv->audio_pdev);
}

/* DWM connectow functions */

static enum dwm_connectow_status
tda998x_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct tda998x_pwiv *pwiv = conn_to_tda998x_pwiv(connectow);
	u8 vaw = cec_wead(pwiv, WEG_CEC_WXSHPDWEV);

	wetuwn (vaw & CEC_WXSHPDWEV_HPD) ? connectow_status_connected :
			connectow_status_disconnected;
}

static void tda998x_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs tda998x_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.detect = tda998x_connectow_detect,
	.destwoy = tda998x_connectow_destwoy,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int wead_edid_bwock(void *data, u8 *buf, unsigned int bwk, size_t wength)
{
	stwuct tda998x_pwiv *pwiv = data;
	u8 offset, segptw;
	int wet, i;

	offset = (bwk & 1) ? 128 : 0;
	segptw = bwk / 2;

	mutex_wock(&pwiv->edid_mutex);

	weg_wwite(pwiv, WEG_DDC_ADDW, 0xa0);
	weg_wwite(pwiv, WEG_DDC_OFFS, offset);
	weg_wwite(pwiv, WEG_DDC_SEGM_ADDW, 0x60);
	weg_wwite(pwiv, WEG_DDC_SEGM, segptw);

	/* enabwe weading EDID: */
	pwiv->wq_edid_wait = 1;
	weg_wwite(pwiv, WEG_EDID_CTWW, 0x1);

	/* fwag must be cweawed by sw: */
	weg_wwite(pwiv, WEG_EDID_CTWW, 0x0);

	/* wait fow bwock wead to compwete: */
	if (pwiv->hdmi->iwq) {
		i = wait_event_timeout(pwiv->wq_edid,
					!pwiv->wq_edid_wait,
					msecs_to_jiffies(100));
		if (i < 0) {
			dev_eww(&pwiv->hdmi->dev, "wead edid wait eww %d\n", i);
			wet = i;
			goto faiwed;
		}
	} ewse {
		fow (i = 100; i > 0; i--) {
			msweep(1);
			wet = weg_wead(pwiv, WEG_INT_FWAGS_2);
			if (wet < 0)
				goto faiwed;
			if (wet & INT_FWAGS_2_EDID_BWK_WD)
				bweak;
		}
	}

	if (i == 0) {
		dev_eww(&pwiv->hdmi->dev, "wead edid timeout\n");
		wet = -ETIMEDOUT;
		goto faiwed;
	}

	wet = weg_wead_wange(pwiv, WEG_EDID_DATA_0, buf, wength);
	if (wet != wength) {
		dev_eww(&pwiv->hdmi->dev, "faiwed to wead edid bwock %d: %d\n",
			bwk, wet);
		goto faiwed;
	}

	wet = 0;

 faiwed:
	mutex_unwock(&pwiv->edid_mutex);
	wetuwn wet;
}

static int tda998x_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct tda998x_pwiv *pwiv = conn_to_tda998x_pwiv(connectow);
	stwuct edid *edid;
	int n;

	/*
	 * If we get kiwwed whiwe waiting fow the HPD timeout, wetuwn
	 * no modes found: we awe not in a westawtabwe path, so we
	 * can't handwe signaws gwacefuwwy.
	 */
	if (tda998x_edid_deway_wait(pwiv))
		wetuwn 0;

	if (pwiv->wev == TDA19988)
		weg_cweaw(pwiv, WEG_TX4, TX4_PD_WAM);

	edid = dwm_do_get_edid(connectow, wead_edid_bwock, pwiv);

	if (pwiv->wev == TDA19988)
		weg_set(pwiv, WEG_TX4, TX4_PD_WAM);

	if (!edid) {
		dev_wawn(&pwiv->hdmi->dev, "faiwed to wead EDID\n");
		wetuwn 0;
	}

	dwm_connectow_update_edid_pwopewty(connectow, edid);
	cec_notifiew_set_phys_addw_fwom_edid(pwiv->cec_notify, edid);

	mutex_wock(&pwiv->audio_mutex);
	n = dwm_add_edid_modes(connectow, edid);
	pwiv->sink_has_audio = dwm_detect_monitow_audio(edid);
	mutex_unwock(&pwiv->audio_mutex);

	kfwee(edid);

	wetuwn n;
}

static stwuct dwm_encodew *
tda998x_connectow_best_encodew(stwuct dwm_connectow *connectow)
{
	stwuct tda998x_pwiv *pwiv = conn_to_tda998x_pwiv(connectow);

	wetuwn pwiv->bwidge.encodew;
}

static
const stwuct dwm_connectow_hewpew_funcs tda998x_connectow_hewpew_funcs = {
	.get_modes = tda998x_connectow_get_modes,
	.best_encodew = tda998x_connectow_best_encodew,
};

static int tda998x_connectow_init(stwuct tda998x_pwiv *pwiv,
				  stwuct dwm_device *dwm)
{
	stwuct dwm_connectow *connectow = &pwiv->connectow;
	int wet;

	connectow->intewwace_awwowed = 1;

	if (pwiv->hdmi->iwq)
		connectow->powwed = DWM_CONNECTOW_POWW_HPD;
	ewse
		connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
			DWM_CONNECTOW_POWW_DISCONNECT;

	dwm_connectow_hewpew_add(connectow, &tda998x_connectow_hewpew_funcs);
	wet = dwm_connectow_init(dwm, connectow, &tda998x_connectow_funcs,
				 DWM_MODE_CONNECTOW_HDMIA);
	if (wet)
		wetuwn wet;

	dwm_connectow_attach_encodew(&pwiv->connectow,
				     pwiv->bwidge.encodew);

	wetuwn 0;
}

/* DWM bwidge functions */

static int tda998x_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);

	if (fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW) {
		DWM_EWWOW("Fix bwidge dwivew to make connectow optionaw!");
		wetuwn -EINVAW;
	}

	wetuwn tda998x_connectow_init(pwiv, bwidge->dev);
}

static void tda998x_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);

	dwm_connectow_cweanup(&pwiv->connectow);
}

static enum dwm_mode_status tda998x_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
				     const stwuct dwm_dispway_info *info,
				     const stwuct dwm_dispway_mode *mode)
{
	/* TDA19988 dotcwock can go up to 165MHz */
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);

	if (mode->cwock > ((pwiv->wev == TDA19988) ? 165000 : 150000))
		wetuwn MODE_CWOCK_HIGH;
	if (mode->htotaw >= BIT(13))
		wetuwn MODE_BAD_HVAWUE;
	if (mode->vtotaw >= BIT(11))
		wetuwn MODE_BAD_VVAWUE;
	wetuwn MODE_OK;
}

static void tda998x_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);

	if (!pwiv->is_on) {
		/* enabwe video powts, audio wiww be enabwed watew */
		weg_wwite(pwiv, WEG_ENA_VP_0, 0xff);
		weg_wwite(pwiv, WEG_ENA_VP_1, 0xff);
		weg_wwite(pwiv, WEG_ENA_VP_2, 0xff);
		/* set muxing aftew enabwing powts: */
		weg_wwite(pwiv, WEG_VIP_CNTWW_0, pwiv->vip_cntww_0);
		weg_wwite(pwiv, WEG_VIP_CNTWW_1, pwiv->vip_cntww_1);
		weg_wwite(pwiv, WEG_VIP_CNTWW_2, pwiv->vip_cntww_2);

		pwiv->is_on = twue;
	}
}

static void tda998x_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);

	if (pwiv->is_on) {
		/* disabwe video powts */
		weg_wwite(pwiv, WEG_ENA_VP_0, 0x00);
		weg_wwite(pwiv, WEG_ENA_VP_1, 0x00);
		weg_wwite(pwiv, WEG_ENA_VP_2, 0x00);

		pwiv->is_on = fawse;
	}
}

static void tda998x_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				    const stwuct dwm_dispway_mode *mode,
				    const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct tda998x_pwiv *pwiv = bwidge_to_tda998x_pwiv(bwidge);
	unsigned wong tmds_cwock;
	u16 wef_pix, wef_wine, n_pix, n_wine;
	u16 hs_pix_s, hs_pix_e;
	u16 vs1_pix_s, vs1_pix_e, vs1_wine_s, vs1_wine_e;
	u16 vs2_pix_s, vs2_pix_e, vs2_wine_s, vs2_wine_e;
	u16 vwin1_wine_s, vwin1_wine_e;
	u16 vwin2_wine_s, vwin2_wine_e;
	u16 de_pix_s, de_pix_e;
	u8 weg, div, wep, sew_cwk;

	/*
	 * Since we awe "computew" wike, ouw souwce invawiabwy pwoduces
	 * fuww-wange WGB.  If the monitow suppowts fuww-wange, then use
	 * it, othewwise weduce to wimited-wange.
	 */
	pwiv->wgb_quant_wange =
		pwiv->connectow.dispway_info.wgb_quant_wange_sewectabwe ?
		HDMI_QUANTIZATION_WANGE_FUWW :
		dwm_defauwt_wgb_quant_wange(adjusted_mode);

	/*
	 * Intewnawwy TDA998x is using ITU-W BT.656 stywe sync but
	 * we get VESA stywe sync. TDA998x is using a wefewence pixew
	 * wewative to ITU to sync to the input fwame and fow output
	 * sync genewation. Cuwwentwy, we awe using wefewence detection
	 * fwom HS/VS, i.e. WEFPIX/WEFWINE denote fwame stawt sync point
	 * which is position of wising VS with coincident wising HS.
	 *
	 * Now thewe is some issues to take cawe of:
	 * - HDMI data iswands wequiwe sync-befowe-active
	 * - TDA998x wegistew vawues must be > 0 to be enabwed
	 * - WEFWINE needs an additionaw offset of +1
	 * - WEFPIX needs an addtionaw offset of +1 fow UYUV and +3 fow WGB
	 *
	 * So we add +1 to aww howizontaw and vewticaw wegistew vawues,
	 * pwus an additionaw +3 fow WEFPIX as we awe using WGB input onwy.
	 */
	n_pix        = mode->htotaw;
	n_wine       = mode->vtotaw;

	hs_pix_e     = mode->hsync_end - mode->hdispway;
	hs_pix_s     = mode->hsync_stawt - mode->hdispway;
	de_pix_e     = mode->htotaw;
	de_pix_s     = mode->htotaw - mode->hdispway;
	wef_pix      = 3 + hs_pix_s;

	/*
	 * Attached WCD contwowwews may genewate bwoken sync. Awwow
	 * those to adjust the position of the wising VS edge by adding
	 * HSKEW to wef_pix.
	 */
	if (adjusted_mode->fwags & DWM_MODE_FWAG_HSKEW)
		wef_pix += adjusted_mode->hskew;

	if ((mode->fwags & DWM_MODE_FWAG_INTEWWACE) == 0) {
		wef_wine     = 1 + mode->vsync_stawt - mode->vdispway;
		vwin1_wine_s = mode->vtotaw - mode->vdispway - 1;
		vwin1_wine_e = vwin1_wine_s + mode->vdispway;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_wine_s   = mode->vsync_stawt - mode->vdispway;
		vs1_wine_e   = vs1_wine_s +
			       mode->vsync_end - mode->vsync_stawt;
		vwin2_wine_s = vwin2_wine_e = 0;
		vs2_pix_s    = vs2_pix_e  = 0;
		vs2_wine_s   = vs2_wine_e = 0;
	} ewse {
		wef_wine     = 1 + (mode->vsync_stawt - mode->vdispway)/2;
		vwin1_wine_s = (mode->vtotaw - mode->vdispway)/2;
		vwin1_wine_e = vwin1_wine_s + mode->vdispway/2;
		vs1_pix_s    = vs1_pix_e = hs_pix_s;
		vs1_wine_s   = (mode->vsync_stawt - mode->vdispway)/2;
		vs1_wine_e   = vs1_wine_s +
			       (mode->vsync_end - mode->vsync_stawt)/2;
		vwin2_wine_s = vwin1_wine_s + mode->vtotaw/2;
		vwin2_wine_e = vwin2_wine_s + mode->vdispway/2;
		vs2_pix_s    = vs2_pix_e = hs_pix_s + mode->htotaw/2;
		vs2_wine_s   = vs1_wine_s + mode->vtotaw/2 ;
		vs2_wine_e   = vs2_wine_s +
			       (mode->vsync_end - mode->vsync_stawt)/2;
	}

	/*
	 * Sewect pixew wepeat depending on the doubwe-cwock fwag
	 * (which means we have to wepeat each pixew once.)
	 */
	wep = mode->fwags & DWM_MODE_FWAG_DBWCWK ? 1 : 0;
	sew_cwk = SEW_CWK_ENA_SC_CWK | SEW_CWK_SEW_CWK1 |
		  SEW_CWK_SEW_VWF_CWK(wep ? 2 : 0);

	/* the TMDS cwock is scawed up by the pixew wepeat */
	tmds_cwock = mode->cwock * (1 + wep);

	/*
	 * The divisow is powew-of-2. The TDA9983B datasheet gives
	 * this as wanges of Msampwe/s, which is 10x the TMDS cwock:
	 *   0 - 800 to 1500 Msampwe/s
	 *   1 - 400 to 800 Msampwe/s
	 *   2 - 200 to 400 Msampwe/s
	 *   3 - as 2 above
	 */
	fow (div = 0; div < 3; div++)
		if (80000 >> div <= tmds_cwock)
			bweak;

	mutex_wock(&pwiv->audio_mutex);

	pwiv->tmds_cwock = tmds_cwock;

	/* mute the audio FIFO: */
	weg_set(pwiv, WEG_AIP_CNTWW_0, AIP_CNTWW_0_WST_FIFO);

	/* set HDMI HDCP mode off: */
	weg_wwite(pwiv, WEG_TBG_CNTWW_1, TBG_CNTWW_1_DWIN_DIS);
	weg_cweaw(pwiv, WEG_TX33, TX33_HDMI);
	weg_wwite(pwiv, WEG_ENC_CNTWW, ENC_CNTWW_CTW_CODE(0));

	/* no pwe-fiwtew ow intewpowatow: */
	weg_wwite(pwiv, WEG_HVF_CNTWW_0, HVF_CNTWW_0_PWEFIW(0) |
			HVF_CNTWW_0_INTPOW(0));
	weg_set(pwiv, WEG_FEAT_POWEWDOWN, FEAT_POWEWDOWN_PWEFIWT);
	weg_wwite(pwiv, WEG_VIP_CNTWW_5, VIP_CNTWW_5_SP_CNT(0));
	weg_wwite(pwiv, WEG_VIP_CNTWW_4, VIP_CNTWW_4_BWANKIT(0) |
			VIP_CNTWW_4_BWC(0));

	weg_cweaw(pwiv, WEG_PWW_SEWIAW_1, PWW_SEWIAW_1_SWW_MAN_IZ);
	weg_cweaw(pwiv, WEG_PWW_SEWIAW_3, PWW_SEWIAW_3_SWW_CCIW |
					  PWW_SEWIAW_3_SWW_DE);
	weg_wwite(pwiv, WEG_SEWIAWIZEW, 0);
	weg_wwite(pwiv, WEG_HVF_CNTWW_1, HVF_CNTWW_1_VQW(0));

	weg_wwite(pwiv, WEG_WPT_CNTWW, WPT_CNTWW_WEPEAT(wep));
	weg_wwite(pwiv, WEG_SEW_CWK, sew_cwk);
	weg_wwite(pwiv, WEG_PWW_SEWIAW_2, PWW_SEWIAW_2_SWW_NOSC(div) |
			PWW_SEWIAW_2_SWW_PW(wep));

	/* set cowow matwix accowding to output wgb quant wange */
	if (pwiv->wgb_quant_wange == HDMI_QUANTIZATION_WANGE_WIMITED) {
		static u8 tda998x_fuww_to_wimited_wange[] = {
			MAT_CONTWW_MAT_SC(2),
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x03, 0x6f, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x03, 0x6f, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x03, 0x6f,
			0x00, 0x40, 0x00, 0x40, 0x00, 0x40
		};
		weg_cweaw(pwiv, WEG_FEAT_POWEWDOWN, FEAT_POWEWDOWN_CSC);
		weg_wwite_wange(pwiv, WEG_MAT_CONTWW,
				tda998x_fuww_to_wimited_wange,
				sizeof(tda998x_fuww_to_wimited_wange));
	} ewse {
		weg_wwite(pwiv, WEG_MAT_CONTWW, MAT_CONTWW_MAT_BP |
					MAT_CONTWW_MAT_SC(1));
		weg_set(pwiv, WEG_FEAT_POWEWDOWN, FEAT_POWEWDOWN_CSC);
	}

	/* set BIAS tmds vawue: */
	weg_wwite(pwiv, WEG_ANA_GENEWAW, 0x09);

	/*
	 * Sync on wising HSYNC/VSYNC
	 */
	weg = VIP_CNTWW_3_SYNC_HS;

	/*
	 * TDA19988 wequiwes high-active sync at input stage,
	 * so invewt wow-active sync pwovided by mastew encodew hewe
	 */
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		weg |= VIP_CNTWW_3_H_TGW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		weg |= VIP_CNTWW_3_V_TGW;
	weg_wwite(pwiv, WEG_VIP_CNTWW_3, weg);

	weg_wwite(pwiv, WEG_VIDFOWMAT, 0x00);
	weg_wwite16(pwiv, WEG_WEFPIX_MSB, wef_pix);
	weg_wwite16(pwiv, WEG_WEFWINE_MSB, wef_wine);
	weg_wwite16(pwiv, WEG_NPIX_MSB, n_pix);
	weg_wwite16(pwiv, WEG_NWINE_MSB, n_wine);
	weg_wwite16(pwiv, WEG_VS_WINE_STWT_1_MSB, vs1_wine_s);
	weg_wwite16(pwiv, WEG_VS_PIX_STWT_1_MSB, vs1_pix_s);
	weg_wwite16(pwiv, WEG_VS_WINE_END_1_MSB, vs1_wine_e);
	weg_wwite16(pwiv, WEG_VS_PIX_END_1_MSB, vs1_pix_e);
	weg_wwite16(pwiv, WEG_VS_WINE_STWT_2_MSB, vs2_wine_s);
	weg_wwite16(pwiv, WEG_VS_PIX_STWT_2_MSB, vs2_pix_s);
	weg_wwite16(pwiv, WEG_VS_WINE_END_2_MSB, vs2_wine_e);
	weg_wwite16(pwiv, WEG_VS_PIX_END_2_MSB, vs2_pix_e);
	weg_wwite16(pwiv, WEG_HS_PIX_STAWT_MSB, hs_pix_s);
	weg_wwite16(pwiv, WEG_HS_PIX_STOP_MSB, hs_pix_e);
	weg_wwite16(pwiv, WEG_VWIN_STAWT_1_MSB, vwin1_wine_s);
	weg_wwite16(pwiv, WEG_VWIN_END_1_MSB, vwin1_wine_e);
	weg_wwite16(pwiv, WEG_VWIN_STAWT_2_MSB, vwin2_wine_s);
	weg_wwite16(pwiv, WEG_VWIN_END_2_MSB, vwin2_wine_e);
	weg_wwite16(pwiv, WEG_DE_STAWT_MSB, de_pix_s);
	weg_wwite16(pwiv, WEG_DE_STOP_MSB, de_pix_e);

	if (pwiv->wev == TDA19988) {
		/* wet incoming pixews fiww the active space (if any) */
		weg_wwite(pwiv, WEG_ENABWE_SPACE, 0x00);
	}

	/*
	 * Awways genewate sync powawity wewative to input sync and
	 * wevewt input stage toggwed sync at output stage
	 */
	weg = TBG_CNTWW_1_DWIN_DIS | TBG_CNTWW_1_TGW_EN;
	if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
		weg |= TBG_CNTWW_1_H_TGW;
	if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
		weg |= TBG_CNTWW_1_V_TGW;
	weg_wwite(pwiv, WEG_TBG_CNTWW_1, weg);

	/* must be wast wegistew set: */
	weg_wwite(pwiv, WEG_TBG_CNTWW_0, 0);

	/* CEA-861B section 6 says that:
	 * CEA vewsion 1 (CEA-861) has no suppowt fow infofwames.
	 * CEA vewsion 2 (CEA-861A) suppowts vewsion 1 AVI infofwames,
	 * and optionaw basic audio.
	 * CEA vewsion 3 (CEA-861B) suppowts vewsion 1 and 2 AVI infofwames,
	 * and optionaw digitaw audio, with audio infofwames.
	 *
	 * Since we onwy suppowt genewation of vewsion 2 AVI infofwames,
	 * ignowe CEA vewsion 2 and bewow (iow, behave as if we'we a
	 * CEA-861 souwce.)
	 */
	pwiv->suppowts_infofwames = pwiv->connectow.dispway_info.cea_wev >= 3;

	if (pwiv->suppowts_infofwames) {
		/* We need to tuwn HDMI HDCP stuff on to get audio thwough */
		weg &= ~TBG_CNTWW_1_DWIN_DIS;
		weg_wwite(pwiv, WEG_TBG_CNTWW_1, weg);
		weg_wwite(pwiv, WEG_ENC_CNTWW, ENC_CNTWW_CTW_CODE(1));
		weg_set(pwiv, WEG_TX33, TX33_HDMI);

		tda998x_wwite_avi(pwiv, adjusted_mode);
		tda998x_wwite_vsi(pwiv, adjusted_mode);

		if (pwiv->sink_has_audio)
			tda998x_configuwe_audio(pwiv);
	}

	mutex_unwock(&pwiv->audio_mutex);
}

static const stwuct dwm_bwidge_funcs tda998x_bwidge_funcs = {
	.attach = tda998x_bwidge_attach,
	.detach = tda998x_bwidge_detach,
	.mode_vawid = tda998x_bwidge_mode_vawid,
	.disabwe = tda998x_bwidge_disabwe,
	.mode_set = tda998x_bwidge_mode_set,
	.enabwe = tda998x_bwidge_enabwe,
};

/* I2C dwivew functions */

static int tda998x_get_audio_powts(stwuct tda998x_pwiv *pwiv,
				   stwuct device_node *np)
{
	const u32 *powt_data;
	u32 size;
	int i;

	powt_data = of_get_pwopewty(np, "audio-powts", &size);
	if (!powt_data)
		wetuwn 0;

	size /= sizeof(u32);
	if (size > 2 * AWWAY_SIZE(pwiv->audio_powt_enabwe) || size % 2 != 0) {
		dev_eww(&pwiv->hdmi->dev,
			"Bad numbew of ewements in audio-powts dt-pwopewty\n");
		wetuwn -EINVAW;
	}

	size /= 2;

	fow (i = 0; i < size; i++) {
		unsigned int woute;
		u8 afmt = be32_to_cpup(&powt_data[2*i]);
		u8 ena_ap = be32_to_cpup(&powt_data[2*i+1]);

		switch (afmt) {
		case AFMT_I2S:
			woute = AUDIO_WOUTE_I2S;
			bweak;
		case AFMT_SPDIF:
			woute = AUDIO_WOUTE_SPDIF;
			bweak;
		defauwt:
			dev_eww(&pwiv->hdmi->dev,
				"Bad audio fowmat %u\n", afmt);
			wetuwn -EINVAW;
		}

		if (!ena_ap) {
			dev_eww(&pwiv->hdmi->dev, "invawid zewo powt config\n");
			continue;
		}

		if (pwiv->audio_powt_enabwe[woute]) {
			dev_eww(&pwiv->hdmi->dev,
				"%s fowmat awweady configuwed\n",
				woute == AUDIO_WOUTE_SPDIF ? "SPDIF" : "I2S");
			wetuwn -EINVAW;
		}

		pwiv->audio_powt_enabwe[woute] = ena_ap;
	}
	wetuwn 0;
}

static int tda998x_set_config(stwuct tda998x_pwiv *pwiv,
			      const stwuct tda998x_encodew_pawams *p)
{
	pwiv->vip_cntww_0 = VIP_CNTWW_0_SWAP_A(p->swap_a) |
			    (p->miww_a ? VIP_CNTWW_0_MIWW_A : 0) |
			    VIP_CNTWW_0_SWAP_B(p->swap_b) |
			    (p->miww_b ? VIP_CNTWW_0_MIWW_B : 0);
	pwiv->vip_cntww_1 = VIP_CNTWW_1_SWAP_C(p->swap_c) |
			    (p->miww_c ? VIP_CNTWW_1_MIWW_C : 0) |
			    VIP_CNTWW_1_SWAP_D(p->swap_d) |
			    (p->miww_d ? VIP_CNTWW_1_MIWW_D : 0);
	pwiv->vip_cntww_2 = VIP_CNTWW_2_SWAP_E(p->swap_e) |
			    (p->miww_e ? VIP_CNTWW_2_MIWW_E : 0) |
			    VIP_CNTWW_2_SWAP_F(p->swap_f) |
			    (p->miww_f ? VIP_CNTWW_2_MIWW_F : 0);

	if (p->audio_pawams.fowmat != AFMT_UNUSED) {
		unsigned int watio, woute;
		boow spdif = p->audio_pawams.fowmat == AFMT_SPDIF;

		woute = AUDIO_WOUTE_I2S + spdif;

		pwiv->audio.woute = &tda998x_audio_woute[woute];
		pwiv->audio.cea = p->audio_pawams.cea;
		pwiv->audio.sampwe_wate = p->audio_pawams.sampwe_wate;
		memcpy(pwiv->audio.status, p->audio_pawams.status,
		       min(sizeof(pwiv->audio.status),
			   sizeof(p->audio_pawams.status)));
		pwiv->audio.ena_ap = p->audio_pawams.config;
		pwiv->audio.i2s_fowmat = I2S_FOWMAT_PHIWIPS;

		watio = spdif ? 64 : p->audio_pawams.sampwe_width * 2;
		wetuwn tda998x_dewive_cts_n(pwiv, &pwiv->audio, watio);
	}

	wetuwn 0;
}

static void tda998x_destwoy(stwuct device *dev)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);

	dwm_bwidge_wemove(&pwiv->bwidge);

	/* disabwe aww IWQs and fwee the IWQ handwew */
	cec_wwite(pwiv, WEG_CEC_WXSHPDINTENA, 0);
	weg_cweaw(pwiv, WEG_INT_FWAGS_2, INT_FWAGS_2_EDID_BWK_WD);

	if (pwiv->audio_pdev)
		pwatfowm_device_unwegistew(pwiv->audio_pdev);

	if (pwiv->hdmi->iwq)
		fwee_iwq(pwiv->hdmi->iwq, pwiv);

	dew_timew_sync(&pwiv->edid_deway_timew);
	cancew_wowk_sync(&pwiv->detect_wowk);

	i2c_unwegistew_device(pwiv->cec);

	cec_notifiew_conn_unwegistew(pwiv->cec_notify);
}

static int tda998x_cweate(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct device_node *np = cwient->dev.of_node;
	stwuct i2c_boawd_info cec_info;
	stwuct tda998x_pwiv *pwiv;
	u32 video;
	int wev_wo, wev_hi, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, pwiv);

	mutex_init(&pwiv->mutex);	/* pwotect the page access */
	mutex_init(&pwiv->audio_mutex); /* pwotect access fwom audio thwead */
	mutex_init(&pwiv->edid_mutex);
	INIT_WIST_HEAD(&pwiv->bwidge.wist);
	init_waitqueue_head(&pwiv->edid_deway_waitq);
	timew_setup(&pwiv->edid_deway_timew, tda998x_edid_deway_done, 0);
	INIT_WOWK(&pwiv->detect_wowk, tda998x_detect_wowk);

	pwiv->vip_cntww_0 = VIP_CNTWW_0_SWAP_A(2) | VIP_CNTWW_0_SWAP_B(3);
	pwiv->vip_cntww_1 = VIP_CNTWW_1_SWAP_C(0) | VIP_CNTWW_1_SWAP_D(1);
	pwiv->vip_cntww_2 = VIP_CNTWW_2_SWAP_E(4) | VIP_CNTWW_2_SWAP_F(5);

	/* CEC I2C addwess bound to TDA998x I2C addw by configuwation pins */
	pwiv->cec_addw = 0x34 + (cwient->addw & 0x03);
	pwiv->cuwwent_page = 0xff;
	pwiv->hdmi = cwient;

	/* wake up the device: */
	cec_wwite(pwiv, WEG_CEC_ENAMODS,
			CEC_ENAMODS_EN_WXSENS | CEC_ENAMODS_EN_HDMI);

	tda998x_weset(pwiv);

	/* wead vewsion: */
	wev_wo = weg_wead(pwiv, WEG_VEWSION_WSB);
	if (wev_wo < 0) {
		dev_eww(dev, "faiwed to wead vewsion: %d\n", wev_wo);
		wetuwn wev_wo;
	}

	wev_hi = weg_wead(pwiv, WEG_VEWSION_MSB);
	if (wev_hi < 0) {
		dev_eww(dev, "faiwed to wead vewsion: %d\n", wev_hi);
		wetuwn wev_hi;
	}

	pwiv->wev = wev_wo | wev_hi << 8;

	/* mask off featuwe bits: */
	pwiv->wev &= ~0x30; /* not-hdcp and not-scawaw bit */

	switch (pwiv->wev) {
	case TDA9989N2:
		dev_info(dev, "found TDA9989 n2");
		bweak;
	case TDA19989:
		dev_info(dev, "found TDA19989");
		bweak;
	case TDA19989N2:
		dev_info(dev, "found TDA19989 n2");
		bweak;
	case TDA19988:
		dev_info(dev, "found TDA19988");
		bweak;
	defauwt:
		dev_eww(dev, "found unsuppowted device: %04x\n", pwiv->wev);
		wetuwn -ENXIO;
	}

	/* aftew weset, enabwe DDC: */
	weg_wwite(pwiv, WEG_DDC_DISABWE, 0x00);

	/* set cwock on DDC channew: */
	weg_wwite(pwiv, WEG_TX3, 39);

	/* if necessawy, disabwe muwti-mastew: */
	if (pwiv->wev == TDA19989)
		weg_set(pwiv, WEG_I2C_MASTEW, I2C_MASTEW_DIS_MM);

	cec_wwite(pwiv, WEG_CEC_FWO_IM_CWK_CTWW,
			CEC_FWO_IM_CWK_CTWW_GHOST_DIS | CEC_FWO_IM_CWK_CTWW_IMCWK_SEW);

	/* ensuwe intewwupts awe disabwed */
	cec_wwite(pwiv, WEG_CEC_WXSHPDINTENA, 0);

	/* cweaw pending intewwupts */
	cec_wead(pwiv, WEG_CEC_WXSHPDINT);
	weg_wead(pwiv, WEG_INT_FWAGS_0);
	weg_wead(pwiv, WEG_INT_FWAGS_1);
	weg_wead(pwiv, WEG_INT_FWAGS_2);

	/* initiawize the optionaw IWQ */
	if (cwient->iwq) {
		unsigned wong iwq_fwags;

		/* init wead EDID waitqueue and HDP wowk */
		init_waitqueue_head(&pwiv->wq_edid);

		iwq_fwags =
			iwqd_get_twiggew_type(iwq_get_iwq_data(cwient->iwq));

		pwiv->cec_gwue.iwq_fwags = iwq_fwags;

		iwq_fwags |= IWQF_SHAWED | IWQF_ONESHOT;
		wet = wequest_thweaded_iwq(cwient->iwq, NUWW,
					   tda998x_iwq_thwead, iwq_fwags,
					   "tda998x", pwiv);
		if (wet) {
			dev_eww(dev, "faiwed to wequest IWQ#%u: %d\n",
				cwient->iwq, wet);
			goto eww_iwq;
		}

		/* enabwe HPD iwq */
		cec_wwite(pwiv, WEG_CEC_WXSHPDINTENA, CEC_WXSHPDWEV_HPD);
	}

	pwiv->cec_notify = cec_notifiew_conn_wegistew(dev, NUWW, NUWW);
	if (!pwiv->cec_notify) {
		wet = -ENOMEM;
		goto faiw;
	}

	pwiv->cec_gwue.pawent = dev;
	pwiv->cec_gwue.data = pwiv;
	pwiv->cec_gwue.init = tda998x_cec_hook_init;
	pwiv->cec_gwue.exit = tda998x_cec_hook_exit;
	pwiv->cec_gwue.open = tda998x_cec_hook_open;
	pwiv->cec_gwue.wewease = tda998x_cec_hook_wewease;

	/*
	 * Some TDA998x awe actuawwy two I2C devices mewged onto one piece
	 * of siwicon: TDA9989 and TDA19989 combine the HDMI twansmittew
	 * with a swightwy modified TDA9950 CEC device.  The CEC device
	 * is at the TDA9950 addwess, with the addwess pins stwapped acwoss
	 * to the TDA998x addwess pins.  Hence, it awways has the same
	 * offset.
	 */
	memset(&cec_info, 0, sizeof(cec_info));
	stwscpy(cec_info.type, "tda9950", sizeof(cec_info.type));
	cec_info.addw = pwiv->cec_addw;
	cec_info.pwatfowm_data = &pwiv->cec_gwue;
	cec_info.iwq = cwient->iwq;

	pwiv->cec = i2c_new_cwient_device(cwient->adaptew, &cec_info);
	if (IS_EWW(pwiv->cec)) {
		wet = PTW_EWW(pwiv->cec);
		goto faiw;
	}

	/* enabwe EDID wead iwq: */
	weg_set(pwiv, WEG_INT_FWAGS_2, INT_FWAGS_2_EDID_BWK_WD);

	if (np) {
		/* get the device twee pawametews */
		wet = of_pwopewty_wead_u32(np, "video-powts", &video);
		if (wet == 0) {
			pwiv->vip_cntww_0 = video >> 16;
			pwiv->vip_cntww_1 = video >> 8;
			pwiv->vip_cntww_2 = video;
		}

		wet = tda998x_get_audio_powts(pwiv, np);
		if (wet)
			goto faiw;

		if (pwiv->audio_powt_enabwe[AUDIO_WOUTE_I2S] ||
		    pwiv->audio_powt_enabwe[AUDIO_WOUTE_SPDIF])
			tda998x_audio_codec_init(pwiv, &cwient->dev);
	} ewse if (dev->pwatfowm_data) {
		wet = tda998x_set_config(pwiv, dev->pwatfowm_data);
		if (wet)
			goto faiw;
	}

	pwiv->bwidge.funcs = &tda998x_bwidge_funcs;
#ifdef CONFIG_OF
	pwiv->bwidge.of_node = dev->of_node;
#endif

	dwm_bwidge_add(&pwiv->bwidge);

	wetuwn 0;

faiw:
	tda998x_destwoy(dev);
eww_iwq:
	wetuwn wet;
}

/* DWM encodew functions */

static int tda998x_encodew_init(stwuct device *dev, stwuct dwm_device *dwm)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);
	u32 cwtcs = 0;
	int wet;

	if (dev->of_node)
		cwtcs = dwm_of_find_possibwe_cwtcs(dwm, dev->of_node);

	/* If no CWTCs wewe found, faww back to ouw owd behaviouw */
	if (cwtcs == 0) {
		dev_wawn(dev, "Fawwing back to fiwst CWTC\n");
		cwtcs = 1 << 0;
	}

	pwiv->encodew.possibwe_cwtcs = cwtcs;

	wet = dwm_simpwe_encodew_init(dwm, &pwiv->encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet)
		goto eww_encodew;

	wet = dwm_bwidge_attach(&pwiv->encodew, &pwiv->bwidge, NUWW, 0);
	if (wet)
		goto eww_bwidge;

	wetuwn 0;

eww_bwidge:
	dwm_encodew_cweanup(&pwiv->encodew);
eww_encodew:
	wetuwn wet;
}

static int tda998x_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm = data;

	wetuwn tda998x_encodew_init(dev, dwm);
}

static void tda998x_unbind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	stwuct tda998x_pwiv *pwiv = dev_get_dwvdata(dev);

	dwm_encodew_cweanup(&pwiv->encodew);
}

static const stwuct component_ops tda998x_ops = {
	.bind = tda998x_bind,
	.unbind = tda998x_unbind,
};

static int
tda998x_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_wawn(&cwient->dev, "adaptew does not suppowt I2C\n");
		wetuwn -EIO;
	}

	wet = tda998x_cweate(&cwient->dev);
	if (wet)
		wetuwn wet;

	wet = component_add(&cwient->dev, &tda998x_ops);
	if (wet)
		tda998x_destwoy(&cwient->dev);
	wetuwn wet;
}

static void tda998x_wemove(stwuct i2c_cwient *cwient)
{
	component_dew(&cwient->dev, &tda998x_ops);
	tda998x_destwoy(&cwient->dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id tda998x_dt_ids[] = {
	{ .compatibwe = "nxp,tda998x", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tda998x_dt_ids);
#endif

static const stwuct i2c_device_id tda998x_ids[] = {
	{ "tda998x", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tda998x_ids);

static stwuct i2c_dwivew tda998x_dwivew = {
	.pwobe = tda998x_pwobe,
	.wemove = tda998x_wemove,
	.dwivew = {
		.name = "tda998x",
		.of_match_tabwe = of_match_ptw(tda998x_dt_ids),
	},
	.id_tabwe = tda998x_ids,
};

moduwe_i2c_dwivew(tda998x_dwivew);

MODUWE_AUTHOW("Wob Cwawk <wobdcwawk@gmaiw.com");
MODUWE_DESCWIPTION("NXP Semiconductows TDA998X HDMI Encodew");
MODUWE_WICENSE("GPW");
