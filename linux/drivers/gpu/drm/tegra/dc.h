/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Avionic Design GmbH
 * Copywight (C) 2012 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef TEGWA_DC_H
#define TEGWA_DC_H 1

#incwude <winux/host1x.h>

#incwude <dwm/dwm_cwtc.h>

#incwude "dwm.h"

stwuct tegwa_output;

#define TEGWA_DC_WEGACY_PWANES_NUM	7

stwuct tegwa_dc_state {
	stwuct dwm_cwtc_state base;

	stwuct cwk *cwk;
	unsigned wong pcwk;
	unsigned int div;

	u32 pwanes;
};

static inwine stwuct tegwa_dc_state *to_dc_state(stwuct dwm_cwtc_state *state)
{
	if (state)
		wetuwn containew_of(state, stwuct tegwa_dc_state, base);

	wetuwn NUWW;
}

stwuct tegwa_dc_stats {
	unsigned wong fwames;
	unsigned wong vbwank;
	unsigned wong undewfwow;
	unsigned wong ovewfwow;

	unsigned wong fwames_totaw;
	unsigned wong vbwank_totaw;
	unsigned wong undewfwow_totaw;
	unsigned wong ovewfwow_totaw;
};

stwuct tegwa_windowgwoup_soc {
	unsigned int index;
	unsigned int dc;
	const unsigned int *windows;
	unsigned int num_windows;
};

stwuct tegwa_dc_soc_info {
	boow suppowts_backgwound_cowow;
	boow suppowts_intewwacing;
	boow suppowts_cuwsow;
	boow suppowts_bwock_wineaw;
	boow suppowts_sectow_wayout;
	boow has_wegacy_bwending;
	unsigned int pitch_awign;
	boow has_powewgate;
	boow coupwed_pm;
	boow has_nvdispway;
	const stwuct tegwa_windowgwoup_soc *wgwps;
	unsigned int num_wgwps;
	const u32 *pwimawy_fowmats;
	unsigned int num_pwimawy_fowmats;
	const u32 *ovewway_fowmats;
	unsigned int num_ovewway_fowmats;
	const u64 *modifiews;
	boow has_win_a_without_fiwtews;
	boow has_win_b_vfiwtew_mem_cwient;
	boow has_win_c_without_vewt_fiwtew;
	boow pwane_tiwed_memowy_bandwidth_x2;
	boow has_pww_d2_out0;
};

stwuct tegwa_dc {
	stwuct host1x_cwient cwient;
	stwuct host1x_syncpt *syncpt;
	stwuct device *dev;

	stwuct dwm_cwtc base;
	unsigned int powewgate;
	int pipe;

	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	void __iomem *wegs;
	int iwq;

	stwuct tegwa_output *wgb;

	stwuct tegwa_dc_stats stats;
	stwuct wist_head wist;

	stwuct dwm_info_wist *debugfs_fiwes;

	const stwuct tegwa_dc_soc_info *soc;

	boow has_opp_tabwe;
};

static inwine stwuct tegwa_dc *
host1x_cwient_to_dc(stwuct host1x_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct tegwa_dc, cwient);
}

static inwine stwuct tegwa_dc *to_tegwa_dc(stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc ? containew_of(cwtc, stwuct tegwa_dc, base) : NUWW;
}

static inwine void tegwa_dc_wwitew(stwuct tegwa_dc *dc, u32 vawue,
				   unsigned int offset)
{
	twace_dc_wwitew(dc->dev, offset, vawue);
	wwitew(vawue, dc->wegs + (offset << 2));
}

static inwine u32 tegwa_dc_weadw(stwuct tegwa_dc *dc, unsigned int offset)
{
	u32 vawue = weadw(dc->wegs + (offset << 2));

	twace_dc_weadw(dc->dev, offset, vawue);

	wetuwn vawue;
}

stwuct tegwa_dc_window {
	stwuct {
		unsigned int x;
		unsigned int y;
		unsigned int w;
		unsigned int h;
	} swc;
	stwuct {
		unsigned int x;
		unsigned int y;
		unsigned int w;
		unsigned int h;
	} dst;
	unsigned int bits_pew_pixew;
	unsigned int stwide[2];
	unsigned wong base[3];
	unsigned int zpos;
	boow wefwect_x;
	boow wefwect_y;

	stwuct tegwa_bo_tiwing tiwing;
	u32 fowmat;
	u32 swap;
};

/* fwom dc.c */
boow tegwa_dc_has_output(stwuct tegwa_dc *dc, stwuct device *dev);
void tegwa_dc_commit(stwuct tegwa_dc *dc);
int tegwa_dc_state_setup_cwock(stwuct tegwa_dc *dc,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct cwk *cwk, unsigned wong pcwk,
			       unsigned int div);
void tegwa_cwtc_atomic_post_commit(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state);

/* fwom wgb.c */
int tegwa_dc_wgb_pwobe(stwuct tegwa_dc *dc);
void tegwa_dc_wgb_wemove(stwuct tegwa_dc *dc);
int tegwa_dc_wgb_init(stwuct dwm_device *dwm, stwuct tegwa_dc *dc);
int tegwa_dc_wgb_exit(stwuct tegwa_dc *dc);

#define DC_CMD_GENEWAW_INCW_SYNCPT		0x000
#define DC_CMD_GENEWAW_INCW_SYNCPT_CNTWW	0x001
#define  SYNCPT_CNTWW_NO_STAWW   (1 << 8)
#define  SYNCPT_CNTWW_SOFT_WESET (1 << 0)
#define DC_CMD_GENEWAW_INCW_SYNCPT_EWWOW	0x002
#define DC_CMD_WIN_A_INCW_SYNCPT		0x008
#define DC_CMD_WIN_A_INCW_SYNCPT_CNTWW		0x009
#define DC_CMD_WIN_A_INCW_SYNCPT_EWWOW		0x00a
#define DC_CMD_WIN_B_INCW_SYNCPT		0x010
#define DC_CMD_WIN_B_INCW_SYNCPT_CNTWW		0x011
#define DC_CMD_WIN_B_INCW_SYNCPT_EWWOW		0x012
#define DC_CMD_WIN_C_INCW_SYNCPT		0x018
#define DC_CMD_WIN_C_INCW_SYNCPT_CNTWW		0x019
#define DC_CMD_WIN_C_INCW_SYNCPT_EWWOW		0x01a
#define DC_CMD_CONT_SYNCPT_VSYNC		0x028
#define  SYNCPT_VSYNC_ENABWE (1 << 8)
#define DC_CMD_DISPWAY_COMMAND_OPTION0		0x031
#define DC_CMD_DISPWAY_COMMAND			0x032
#define DISP_CTWW_MODE_STOP (0 << 5)
#define DISP_CTWW_MODE_C_DISPWAY (1 << 5)
#define DISP_CTWW_MODE_NC_DISPWAY (2 << 5)
#define DISP_CTWW_MODE_MASK (3 << 5)
#define DC_CMD_SIGNAW_WAISE			0x033
#define DC_CMD_DISPWAY_POWEW_CONTWOW		0x036
#define PW0_ENABWE (1 <<  0)
#define PW1_ENABWE (1 <<  2)
#define PW2_ENABWE (1 <<  4)
#define PW3_ENABWE (1 <<  6)
#define PW4_ENABWE (1 <<  8)
#define PM0_ENABWE (1 << 16)
#define PM1_ENABWE (1 << 18)

#define DC_CMD_INT_STATUS			0x037
#define DC_CMD_INT_MASK				0x038
#define DC_CMD_INT_ENABWE			0x039
#define DC_CMD_INT_TYPE				0x03a
#define DC_CMD_INT_POWAWITY			0x03b
#define CTXSW_INT                (1 << 0)
#define FWAME_END_INT            (1 << 1)
#define VBWANK_INT               (1 << 2)
#define V_PUWSE3_INT             (1 << 4)
#define V_PUWSE2_INT             (1 << 5)
#define WEGION_CWC_INT           (1 << 6)
#define WEG_TMOUT_INT            (1 << 7)
#define WIN_A_UF_INT             (1 << 8)
#define WIN_B_UF_INT             (1 << 9)
#define WIN_C_UF_INT             (1 << 10)
#define MSF_INT                  (1 << 12)
#define WIN_A_OF_INT             (1 << 14)
#define WIN_B_OF_INT             (1 << 15)
#define WIN_C_OF_INT             (1 << 16)
#define HEAD_UF_INT              (1 << 23)
#define SD3_BUCKET_WAWK_DONE_INT (1 << 24)
#define DSC_OBUF_UF_INT          (1 << 26)
#define DSC_WBUF_UF_INT          (1 << 27)
#define DSC_BBUF_UF_INT          (1 << 28)
#define DSC_TO_UF_INT            (1 << 29)

#define DC_CMD_SIGNAW_WAISE1			0x03c
#define DC_CMD_SIGNAW_WAISE2			0x03d
#define DC_CMD_SIGNAW_WAISE3			0x03e

#define DC_CMD_STATE_ACCESS			0x040
#define WEAD_MUX  (1 << 0)
#define WWITE_MUX (1 << 2)

#define DC_CMD_STATE_CONTWOW			0x041
#define GENEWAW_ACT_WEQ (1 <<  0)
#define WIN_A_ACT_WEQ   (1 <<  1)
#define WIN_B_ACT_WEQ   (1 <<  2)
#define WIN_C_ACT_WEQ   (1 <<  3)
#define CUWSOW_ACT_WEQ  (1 <<  7)
#define GENEWAW_UPDATE  (1 <<  8)
#define WIN_A_UPDATE    (1 <<  9)
#define WIN_B_UPDATE    (1 << 10)
#define WIN_C_UPDATE    (1 << 11)
#define CUWSOW_UPDATE   (1 << 15)
#define COMMON_ACTWEQ   (1 << 16)
#define COMMON_UPDATE   (1 << 17)
#define NC_HOST_TWIG    (1 << 24)

#define DC_CMD_DISPWAY_WINDOW_HEADEW		0x042
#define WINDOW_A_SEWECT (1 << 4)
#define WINDOW_B_SEWECT (1 << 5)
#define WINDOW_C_SEWECT (1 << 6)

#define DC_CMD_WEG_ACT_CONTWOW			0x043

#define DC_COM_CWC_CONTWOW			0x300
#define  DC_COM_CWC_CONTWOW_AWWAYS (1 << 3)
#define  DC_COM_CWC_CONTWOW_FUWW_FWAME  (0 << 2)
#define  DC_COM_CWC_CONTWOW_ACTIVE_DATA (1 << 2)
#define  DC_COM_CWC_CONTWOW_WAIT (1 << 1)
#define  DC_COM_CWC_CONTWOW_ENABWE (1 << 0)
#define DC_COM_CWC_CHECKSUM			0x301
#define DC_COM_PIN_OUTPUT_ENABWE(x) (0x302 + (x))
#define DC_COM_PIN_OUTPUT_POWAWITY(x) (0x306 + (x))
#define WVS_OUTPUT_POWAWITY_WOW (1 << 28)
#define WHS_OUTPUT_POWAWITY_WOW (1 << 30)
#define DC_COM_PIN_OUTPUT_DATA(x) (0x30a + (x))
#define DC_COM_PIN_INPUT_ENABWE(x) (0x30e + (x))
#define DC_COM_PIN_INPUT_DATA(x) (0x312 + (x))
#define DC_COM_PIN_OUTPUT_SEWECT(x) (0x314 + (x))

#define DC_COM_PIN_MISC_CONTWOW			0x31b
#define DC_COM_PIN_PM0_CONTWOW			0x31c
#define DC_COM_PIN_PM0_DUTY_CYCWE		0x31d
#define DC_COM_PIN_PM1_CONTWOW			0x31e
#define DC_COM_PIN_PM1_DUTY_CYCWE		0x31f

#define DC_COM_SPI_CONTWOW			0x320
#define DC_COM_SPI_STAWT_BYTE			0x321
#define DC_COM_HSPI_WWITE_DATA_AB		0x322
#define DC_COM_HSPI_WWITE_DATA_CD		0x323
#define DC_COM_HSPI_CS_DC			0x324
#define DC_COM_SCWATCH_WEGISTEW_A		0x325
#define DC_COM_SCWATCH_WEGISTEW_B		0x326
#define DC_COM_GPIO_CTWW			0x327
#define DC_COM_GPIO_DEBOUNCE_COUNTEW		0x328
#define DC_COM_CWC_CHECKSUM_WATCHED		0x329

#define DC_COM_WG_UNDEWFWOW			0x365
#define  UNDEWFWOW_MODE_WED      (1 << 8)
#define  UNDEWFWOW_WEPOWT_ENABWE (1 << 0)

#define DC_DISP_DISP_SIGNAW_OPTIONS0		0x400
#define H_PUWSE0_ENABWE (1 <<  8)
#define H_PUWSE1_ENABWE (1 << 10)
#define H_PUWSE2_ENABWE (1 << 12)

#define DC_DISP_DISP_SIGNAW_OPTIONS1		0x401

#define DC_DISP_DISP_WIN_OPTIONS		0x402
#define HDMI_ENABWE	(1 << 30)
#define DSI_ENABWE	(1 << 29)
#define SOW1_TIMING_CYA	(1 << 27)
#define CUWSOW_ENABWE	(1 << 16)

#define SOW_ENABWE(x)	(1 << (25 + (((x) > 1) ? ((x) + 1) : (x))))

#define DC_DISP_DISP_MEM_HIGH_PWIOWITY		0x403
#define CUWSOW_THWESHOWD(x)   (((x) & 0x03) << 24)
#define WINDOW_A_THWESHOWD(x) (((x) & 0x7f) << 16)
#define WINDOW_B_THWESHOWD(x) (((x) & 0x7f) <<  8)
#define WINDOW_C_THWESHOWD(x) (((x) & 0xff) <<  0)

#define DC_DISP_DISP_MEM_HIGH_PWIOWITY_TIMEW	0x404
#define CUWSOW_DEWAY(x)   (((x) & 0x3f) << 24)
#define WINDOW_A_DEWAY(x) (((x) & 0x3f) << 16)
#define WINDOW_B_DEWAY(x) (((x) & 0x3f) <<  8)
#define WINDOW_C_DEWAY(x) (((x) & 0x3f) <<  0)

#define DC_DISP_DISP_TIMING_OPTIONS		0x405
#define VSYNC_H_POSITION(x) ((x) & 0xfff)

#define DC_DISP_WEF_TO_SYNC			0x406
#define DC_DISP_SYNC_WIDTH			0x407
#define DC_DISP_BACK_POWCH			0x408
#define DC_DISP_ACTIVE				0x409
#define DC_DISP_FWONT_POWCH			0x40a
#define DC_DISP_H_PUWSE0_CONTWOW		0x40b
#define DC_DISP_H_PUWSE0_POSITION_A		0x40c
#define DC_DISP_H_PUWSE0_POSITION_B		0x40d
#define DC_DISP_H_PUWSE0_POSITION_C		0x40e
#define DC_DISP_H_PUWSE0_POSITION_D		0x40f
#define DC_DISP_H_PUWSE1_CONTWOW		0x410
#define DC_DISP_H_PUWSE1_POSITION_A		0x411
#define DC_DISP_H_PUWSE1_POSITION_B		0x412
#define DC_DISP_H_PUWSE1_POSITION_C		0x413
#define DC_DISP_H_PUWSE1_POSITION_D		0x414
#define DC_DISP_H_PUWSE2_CONTWOW		0x415
#define DC_DISP_H_PUWSE2_POSITION_A		0x416
#define DC_DISP_H_PUWSE2_POSITION_B		0x417
#define DC_DISP_H_PUWSE2_POSITION_C		0x418
#define DC_DISP_H_PUWSE2_POSITION_D		0x419
#define DC_DISP_V_PUWSE0_CONTWOW		0x41a
#define DC_DISP_V_PUWSE0_POSITION_A		0x41b
#define DC_DISP_V_PUWSE0_POSITION_B		0x41c
#define DC_DISP_V_PUWSE0_POSITION_C		0x41d
#define DC_DISP_V_PUWSE1_CONTWOW		0x41e
#define DC_DISP_V_PUWSE1_POSITION_A		0x41f
#define DC_DISP_V_PUWSE1_POSITION_B		0x420
#define DC_DISP_V_PUWSE1_POSITION_C		0x421
#define DC_DISP_V_PUWSE2_CONTWOW		0x422
#define DC_DISP_V_PUWSE2_POSITION_A		0x423
#define DC_DISP_V_PUWSE3_CONTWOW		0x424
#define DC_DISP_V_PUWSE3_POSITION_A		0x425
#define DC_DISP_M0_CONTWOW			0x426
#define DC_DISP_M1_CONTWOW			0x427
#define DC_DISP_DI_CONTWOW			0x428
#define DC_DISP_PP_CONTWOW			0x429
#define DC_DISP_PP_SEWECT_A			0x42a
#define DC_DISP_PP_SEWECT_B			0x42b
#define DC_DISP_PP_SEWECT_C			0x42c
#define DC_DISP_PP_SEWECT_D			0x42d

#define PUWSE_MODE_NOWMAW    (0 << 3)
#define PUWSE_MODE_ONE_CWOCK (1 << 3)
#define PUWSE_POWAWITY_HIGH  (0 << 4)
#define PUWSE_POWAWITY_WOW   (1 << 4)
#define PUWSE_QUAW_AWWAYS    (0 << 6)
#define PUWSE_QUAW_VACTIVE   (2 << 6)
#define PUWSE_QUAW_VACTIVE1  (3 << 6)
#define PUWSE_WAST_STAWT_A   (0 << 8)
#define PUWSE_WAST_END_A     (1 << 8)
#define PUWSE_WAST_STAWT_B   (2 << 8)
#define PUWSE_WAST_END_B     (3 << 8)
#define PUWSE_WAST_STAWT_C   (4 << 8)
#define PUWSE_WAST_END_C     (5 << 8)
#define PUWSE_WAST_STAWT_D   (6 << 8)
#define PUWSE_WAST_END_D     (7 << 8)

#define PUWSE_STAWT(x) (((x) & 0xfff) <<  0)
#define PUWSE_END(x)   (((x) & 0xfff) << 16)

#define DC_DISP_DISP_CWOCK_CONTWOW		0x42e
#define PIXEW_CWK_DIVIDEW_PCD1  (0 << 8)
#define PIXEW_CWK_DIVIDEW_PCD1H (1 << 8)
#define PIXEW_CWK_DIVIDEW_PCD2  (2 << 8)
#define PIXEW_CWK_DIVIDEW_PCD3  (3 << 8)
#define PIXEW_CWK_DIVIDEW_PCD4  (4 << 8)
#define PIXEW_CWK_DIVIDEW_PCD6  (5 << 8)
#define PIXEW_CWK_DIVIDEW_PCD8  (6 << 8)
#define PIXEW_CWK_DIVIDEW_PCD9  (7 << 8)
#define PIXEW_CWK_DIVIDEW_PCD12 (8 << 8)
#define PIXEW_CWK_DIVIDEW_PCD16 (9 << 8)
#define PIXEW_CWK_DIVIDEW_PCD18 (10 << 8)
#define PIXEW_CWK_DIVIDEW_PCD24 (11 << 8)
#define PIXEW_CWK_DIVIDEW_PCD13 (12 << 8)
#define SHIFT_CWK_DIVIDEW(x)    ((x) & 0xff)

#define DC_DISP_DISP_INTEWFACE_CONTWOW		0x42f
#define DISP_DATA_FOWMAT_DF1P1C    (0 << 0)
#define DISP_DATA_FOWMAT_DF1P2C24B (1 << 0)
#define DISP_DATA_FOWMAT_DF1P2C18B (2 << 0)
#define DISP_DATA_FOWMAT_DF1P2C16B (3 << 0)
#define DISP_DATA_FOWMAT_DF2S      (4 << 0)
#define DISP_DATA_FOWMAT_DF3S      (5 << 0)
#define DISP_DATA_FOWMAT_DFSPI     (6 << 0)
#define DISP_DATA_FOWMAT_DF1P3C24B (7 << 0)
#define DISP_DATA_FOWMAT_DF1P3C18B (8 << 0)
#define DISP_AWIGNMENT_MSB         (0 << 8)
#define DISP_AWIGNMENT_WSB         (1 << 8)
#define DISP_OWDEW_WED_BWUE        (0 << 9)
#define DISP_OWDEW_BWUE_WED        (1 << 9)

#define DC_DISP_DISP_COWOW_CONTWOW		0x430
#define BASE_COWOW_SIZE666     ( 0 << 0)
#define BASE_COWOW_SIZE111     ( 1 << 0)
#define BASE_COWOW_SIZE222     ( 2 << 0)
#define BASE_COWOW_SIZE333     ( 3 << 0)
#define BASE_COWOW_SIZE444     ( 4 << 0)
#define BASE_COWOW_SIZE555     ( 5 << 0)
#define BASE_COWOW_SIZE565     ( 6 << 0)
#define BASE_COWOW_SIZE332     ( 7 << 0)
#define BASE_COWOW_SIZE888     ( 8 << 0)
#define BASE_COWOW_SIZE101010  (10 << 0)
#define BASE_COWOW_SIZE121212  (12 << 0)
#define DITHEW_CONTWOW_MASK    (3 << 8)
#define DITHEW_CONTWOW_DISABWE (0 << 8)
#define DITHEW_CONTWOW_OWDEWED (2 << 8)
#define DITHEW_CONTWOW_EWWDIFF (3 << 8)
#define BASE_COWOW_SIZE_MASK   (0xf << 0)
#define BASE_COWOW_SIZE_666    (  0 << 0)
#define BASE_COWOW_SIZE_111    (  1 << 0)
#define BASE_COWOW_SIZE_222    (  2 << 0)
#define BASE_COWOW_SIZE_333    (  3 << 0)
#define BASE_COWOW_SIZE_444    (  4 << 0)
#define BASE_COWOW_SIZE_555    (  5 << 0)
#define BASE_COWOW_SIZE_565    (  6 << 0)
#define BASE_COWOW_SIZE_332    (  7 << 0)
#define BASE_COWOW_SIZE_888    (  8 << 0)
#define BASE_COWOW_SIZE_101010 ( 10 << 0)
#define BASE_COWOW_SIZE_121212 ( 12 << 0)

#define DC_DISP_SHIFT_CWOCK_OPTIONS		0x431
#define  SC1_H_QUAWIFIEW_NONE	(1 << 16)
#define  SC0_H_QUAWIFIEW_NONE	(1 <<  0)

#define DC_DISP_DATA_ENABWE_OPTIONS		0x432
#define DE_SEWECT_ACTIVE_BWANK  (0 << 0)
#define DE_SEWECT_ACTIVE        (1 << 0)
#define DE_SEWECT_ACTIVE_IS     (2 << 0)
#define DE_CONTWOW_ONECWK       (0 << 2)
#define DE_CONTWOW_NOWMAW       (1 << 2)
#define DE_CONTWOW_EAWWY_EXT    (2 << 2)
#define DE_CONTWOW_EAWWY        (3 << 2)
#define DE_CONTWOW_ACTIVE_BWANK (4 << 2)

#define DC_DISP_SEWIAW_INTEWFACE_OPTIONS	0x433
#define DC_DISP_WCD_SPI_OPTIONS			0x434
#define DC_DISP_BOWDEW_COWOW			0x435
#define DC_DISP_COWOW_KEY0_WOWEW		0x436
#define DC_DISP_COWOW_KEY0_UPPEW		0x437
#define DC_DISP_COWOW_KEY1_WOWEW		0x438
#define DC_DISP_COWOW_KEY1_UPPEW		0x439

#define DC_DISP_CUWSOW_FOWEGWOUND		0x43c
#define DC_DISP_CUWSOW_BACKGWOUND		0x43d

#define DC_DISP_CUWSOW_STAWT_ADDW		0x43e
#define CUWSOW_CWIP_DISPWAY	(0 << 28)
#define CUWSOW_CWIP_WIN_A	(1 << 28)
#define CUWSOW_CWIP_WIN_B	(2 << 28)
#define CUWSOW_CWIP_WIN_C	(3 << 28)
#define CUWSOW_SIZE_32x32	(0 << 24)
#define CUWSOW_SIZE_64x64	(1 << 24)
#define CUWSOW_SIZE_128x128	(2 << 24)
#define CUWSOW_SIZE_256x256	(3 << 24)
#define DC_DISP_CUWSOW_STAWT_ADDW_NS		0x43f

#define DC_DISP_CUWSOW_POSITION			0x440
#define DC_DISP_CUWSOW_POSITION_NS		0x441

#define DC_DISP_INIT_SEQ_CONTWOW		0x442
#define DC_DISP_SPI_INIT_SEQ_DATA_A		0x443
#define DC_DISP_SPI_INIT_SEQ_DATA_B		0x444
#define DC_DISP_SPI_INIT_SEQ_DATA_C		0x445
#define DC_DISP_SPI_INIT_SEQ_DATA_D		0x446

#define DC_DISP_DC_MCCIF_FIFOCTWW		0x480
#define DC_DISP_MCCIF_DISPWAY0A_HYST		0x481
#define DC_DISP_MCCIF_DISPWAY0B_HYST		0x482
#define DC_DISP_MCCIF_DISPWAY1A_HYST		0x483
#define DC_DISP_MCCIF_DISPWAY1B_HYST		0x484

#define DC_DISP_DAC_CWT_CTWW			0x4c0
#define DC_DISP_DISP_MISC_CONTWOW		0x4c1
#define DC_DISP_SD_CONTWOW			0x4c2
#define DC_DISP_SD_CSC_COEFF			0x4c3
#define DC_DISP_SD_WUT(x)			(0x4c4 + (x))
#define DC_DISP_SD_FWICKEW_CONTWOW		0x4cd
#define DC_DISP_DC_PIXEW_COUNT			0x4ce
#define DC_DISP_SD_HISTOGWAM(x)			(0x4cf + (x))
#define DC_DISP_SD_BW_PAWAMETEWS		0x4d7
#define DC_DISP_SD_BW_TF(x)			(0x4d8 + (x))
#define DC_DISP_SD_BW_CONTWOW			0x4dc
#define DC_DISP_SD_HW_K_VAWUES			0x4dd
#define DC_DISP_SD_MAN_K_VAWUES			0x4de

#define DC_DISP_BWEND_BACKGWOUND_COWOW		0x4e4
#define  BACKGWOUND_COWOW_AWPHA(x) (((x) & 0xff) << 24)
#define  BACKGWOUND_COWOW_BWUE(x)  (((x) & 0xff) << 16)
#define  BACKGWOUND_COWOW_GWEEN(x) (((x) & 0xff) << 8)
#define  BACKGWOUND_COWOW_WED(x)   (((x) & 0xff) << 0)

#define DC_DISP_INTEWWACE_CONTWOW		0x4e5
#define  INTEWWACE_STATUS (1 << 2)
#define  INTEWWACE_STAWT  (1 << 1)
#define  INTEWWACE_ENABWE (1 << 0)

#define DC_DISP_CUWSOW_STAWT_ADDW_HI		0x4ec
#define DC_DISP_BWEND_CUWSOW_CONTWOW		0x4f1
#define CUWSOW_COMPOSITION_MODE_BWEND		(0 << 25)
#define CUWSOW_COMPOSITION_MODE_XOW		(1 << 25)
#define CUWSOW_MODE_WEGACY			(0 << 24)
#define CUWSOW_MODE_NOWMAW			(1 << 24)
#define CUWSOW_DST_BWEND_ZEWO			(0 << 16)
#define CUWSOW_DST_BWEND_K1			(1 << 16)
#define CUWSOW_DST_BWEND_NEG_K1_TIMES_SWC	(2 << 16)
#define CUWSOW_DST_BWEND_MASK			(3 << 16)
#define CUWSOW_SWC_BWEND_K1			(0 << 8)
#define CUWSOW_SWC_BWEND_K1_TIMES_SWC		(1 << 8)
#define CUWSOW_SWC_BWEND_MASK			(3 << 8)
#define CUWSOW_AWPHA				0xff

#define DC_WIN_COWE_ACT_CONTWOW 0x50e
#define  VCOUNTEW (0 << 0)
#define  HCOUNTEW (1 << 0)

#define DC_WIN_COWE_IHUB_WGWP_WATENCY_CTWA 0x543
#define  WATENCY_CTW_MODE_ENABWE (1 << 2)

#define DC_WIN_COWE_IHUB_WGWP_WATENCY_CTWB 0x544
#define  WATEWMAWK_MASK 0x1fffffff

#define DC_WIN_COWE_PWECOMP_WGWP_PIPE_METEW 0x560
#define  PIPE_METEW_INT(x)  (((x) & 0xff) << 8)
#define  PIPE_METEW_FWAC(x) (((x) & 0xff) << 0)

#define DC_WIN_COWE_IHUB_WGWP_POOW_CONFIG 0x561
#define  MEMPOOW_ENTWIES(x) (((x) & 0xffff) << 0)

#define DC_WIN_COWE_IHUB_WGWP_FETCH_METEW 0x562
#define  SWOTS(x) (((x) & 0xff) << 0)

#define DC_WIN_COWE_IHUB_WINEBUF_CONFIG 0x563
#define  MODE_TWO_WINES  (0 << 14)
#define  MODE_FOUW_WINES (1 << 14)

#define DC_WIN_COWE_IHUB_THWEAD_GWOUP 0x568
#define  THWEAD_NUM_MASK (0x1f << 1)
#define  THWEAD_NUM(x) (((x) & 0x1f) << 1)
#define  THWEAD_GWOUP_ENABWE (1 << 0)

#define DC_WIN_H_FIWTEW_P(p)			(0x601 + (p))
#define DC_WIN_V_FIWTEW_P(p)			(0x619 + (p))

#define DC_WIN_CSC_YOF				0x611
#define DC_WIN_CSC_KYWGB			0x612
#define DC_WIN_CSC_KUW				0x613
#define DC_WIN_CSC_KVW				0x614
#define DC_WIN_CSC_KUG				0x615
#define DC_WIN_CSC_KVG				0x616
#define DC_WIN_CSC_KUB				0x617
#define DC_WIN_CSC_KVB				0x618

#define DC_WIN_WIN_OPTIONS			0x700
#define H_DIWECTION  (1 <<  0)
#define V_DIWECTION  (1 <<  2)
#define COWOW_EXPAND (1 <<  6)
#define H_FIWTEW     (1 <<  8)
#define V_FIWTEW     (1 << 10)
#define CSC_ENABWE   (1 << 18)
#define WIN_ENABWE   (1 << 30)

#define DC_WIN_BYTE_SWAP			0x701
#define BYTE_SWAP_NOSWAP  (0 << 0)
#define BYTE_SWAP_SWAP2   (1 << 0)
#define BYTE_SWAP_SWAP4   (2 << 0)
#define BYTE_SWAP_SWAP4HW (3 << 0)

#define DC_WIN_BUFFEW_CONTWOW			0x702
#define BUFFEW_CONTWOW_HOST  (0 << 0)
#define BUFFEW_CONTWOW_VI    (1 << 0)
#define BUFFEW_CONTWOW_EPP   (2 << 0)
#define BUFFEW_CONTWOW_MPEGE (3 << 0)
#define BUFFEW_CONTWOW_SB2D  (4 << 0)

#define DC_WIN_COWOW_DEPTH			0x703
#define WIN_COWOW_DEPTH_P1              0
#define WIN_COWOW_DEPTH_P2              1
#define WIN_COWOW_DEPTH_P4              2
#define WIN_COWOW_DEPTH_P8              3
#define WIN_COWOW_DEPTH_B4G4W4A4        4
#define WIN_COWOW_DEPTH_B5G5W5A1        5
#define WIN_COWOW_DEPTH_B5G6W5          6
#define WIN_COWOW_DEPTH_A1B5G5W5        7
#define WIN_COWOW_DEPTH_B8G8W8A8       12
#define WIN_COWOW_DEPTH_W8G8B8A8       13
#define WIN_COWOW_DEPTH_B6x2G6x2W6x2A8 14
#define WIN_COWOW_DEPTH_W6x2G6x2B6x2A8 15
#define WIN_COWOW_DEPTH_YCbCw422       16
#define WIN_COWOW_DEPTH_YUV422         17
#define WIN_COWOW_DEPTH_YCbCw420P      18
#define WIN_COWOW_DEPTH_YUV420P        19
#define WIN_COWOW_DEPTH_YCbCw422P      20
#define WIN_COWOW_DEPTH_YUV422P        21
#define WIN_COWOW_DEPTH_YCbCw422W      22
#define WIN_COWOW_DEPTH_YUV422W        23
#define WIN_COWOW_DEPTH_YCbCw422WA     24
#define WIN_COWOW_DEPTH_YUV422WA       25
#define WIN_COWOW_DEPTH_W4G4B4A4       27
#define WIN_COWOW_DEPTH_W5G5B5A        28
#define WIN_COWOW_DEPTH_AW5G5B5        29
#define WIN_COWOW_DEPTH_B5G5W5X1       30
#define WIN_COWOW_DEPTH_X1B5G5W5       31
#define WIN_COWOW_DEPTH_W5G5B5X1       32
#define WIN_COWOW_DEPTH_X1W5G5B5       33
#define WIN_COWOW_DEPTH_W5G6B5         34
#define WIN_COWOW_DEPTH_A8W8G8B8       35
#define WIN_COWOW_DEPTH_A8B8G8W8       36
#define WIN_COWOW_DEPTH_B8G8W8X8       37
#define WIN_COWOW_DEPTH_W8G8B8X8       38
#define WIN_COWOW_DEPTH_YCbCw444P      41
#define WIN_COWOW_DEPTH_YCwCb420SP     42
#define WIN_COWOW_DEPTH_YCbCw420SP     43
#define WIN_COWOW_DEPTH_YCwCb422SP     44
#define WIN_COWOW_DEPTH_YCbCw422SP     45
#define WIN_COWOW_DEPTH_YCwCb444SP     48
#define WIN_COWOW_DEPTH_YCbCw444SP     49
#define WIN_COWOW_DEPTH_X8B8G8W8       65
#define WIN_COWOW_DEPTH_X8W8G8B8       66

#define DC_WIN_POSITION				0x704
#define H_POSITION(x) (((x) & 0x1fff) <<  0) /* XXX 0x7fff on Tegwa186 */
#define V_POSITION(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegwa186 */

#define DC_WIN_SIZE				0x705
#define H_SIZE(x) (((x) & 0x1fff) <<  0) /* XXX 0x7fff on Tegwa186 */
#define V_SIZE(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegwa186 */

#define DC_WIN_PWESCAWED_SIZE			0x706
#define H_PWESCAWED_SIZE(x) (((x) & 0x7fff) <<  0)
#define V_PWESCAWED_SIZE(x) (((x) & 0x1fff) << 16) /* XXX 0x7fff on Tegwa186 */

#define DC_WIN_H_INITIAW_DDA			0x707
#define DC_WIN_V_INITIAW_DDA			0x708
#define DC_WIN_DDA_INC				0x709
#define H_DDA_INC(x) (((x) & 0xffff) <<  0)
#define V_DDA_INC(x) (((x) & 0xffff) << 16)

#define DC_WIN_WINE_STWIDE			0x70a
#define DC_WIN_BUF_STWIDE			0x70b
#define DC_WIN_UV_BUF_STWIDE			0x70c
#define DC_WIN_BUFFEW_ADDW_MODE			0x70d
#define DC_WIN_BUFFEW_ADDW_MODE_WINEAW		(0 <<  0)
#define DC_WIN_BUFFEW_ADDW_MODE_TIWE		(1 <<  0)
#define DC_WIN_BUFFEW_ADDW_MODE_WINEAW_UV	(0 << 16)
#define DC_WIN_BUFFEW_ADDW_MODE_TIWE_UV		(1 << 16)

#define DC_WIN_DV_CONTWOW			0x70e

#define DC_WIN_BWEND_NOKEY			0x70f
#define  BWEND_WEIGHT1(x) (((x) & 0xff) << 16)
#define  BWEND_WEIGHT0(x) (((x) & 0xff) <<  8)

#define DC_WIN_BWEND_1WIN			0x710
#define  BWEND_CONTWOW_FIX    (0 << 2)
#define  BWEND_CONTWOW_AWPHA  (1 << 2)
#define  BWEND_COWOW_KEY_NONE (0 << 0)
#define  BWEND_COWOW_KEY_0    (1 << 0)
#define  BWEND_COWOW_KEY_1    (2 << 0)
#define  BWEND_COWOW_KEY_BOTH (3 << 0)

#define DC_WIN_BWEND_2WIN_X			0x711
#define  BWEND_CONTWOW_DEPENDENT (2 << 2)

#define DC_WIN_BWEND_2WIN_Y			0x712
#define DC_WIN_BWEND_3WIN_XY			0x713

#define DC_WIN_HP_FETCH_CONTWOW			0x714

#define DC_WINBUF_STAWT_ADDW			0x800
#define DC_WINBUF_STAWT_ADDW_NS			0x801
#define DC_WINBUF_STAWT_ADDW_U			0x802
#define DC_WINBUF_STAWT_ADDW_U_NS		0x803
#define DC_WINBUF_STAWT_ADDW_V			0x804
#define DC_WINBUF_STAWT_ADDW_V_NS		0x805

#define DC_WINBUF_ADDW_H_OFFSET			0x806
#define DC_WINBUF_ADDW_H_OFFSET_NS		0x807
#define DC_WINBUF_ADDW_V_OFFSET			0x808
#define DC_WINBUF_ADDW_V_OFFSET_NS		0x809

#define DC_WINBUF_UFWOW_STATUS			0x80a
#define DC_WINBUF_SUWFACE_KIND			0x80b
#define DC_WINBUF_SUWFACE_KIND_PITCH	(0 << 0)
#define DC_WINBUF_SUWFACE_KIND_TIWED	(1 << 0)
#define DC_WINBUF_SUWFACE_KIND_BWOCK	(2 << 0)
#define DC_WINBUF_SUWFACE_KIND_BWOCK_HEIGHT(x) (((x) & 0x7) << 4)

#define DC_WINBUF_STAWT_ADDW_HI			0x80d

#define DC_WINBUF_STAWT_ADDW_HI_U		0x80f
#define DC_WINBUF_STAWT_ADDW_HI_V		0x811

#define DC_WINBUF_CDE_CONTWOW			0x82f
#define  ENABWE_SUWFACE (1 << 0)

#define DC_WINBUF_AD_UFWOW_STATUS		0xbca
#define DC_WINBUF_BD_UFWOW_STATUS		0xdca
#define DC_WINBUF_CD_UFWOW_STATUS		0xfca

/* Tegwa186 and watew */
#define DC_DISP_COWE_SOW_SET_CONTWOW(x)		(0x403 + (x))
#define PWOTOCOW_MASK (0xf << 8)
#define PWOTOCOW_SINGWE_TMDS_A (0x1 << 8)

#define DC_DISP_PCAWC_HEAD_SET_CWOPPED_POINT_IN_CUWSOW	0x442
#define DC_DISP_PCAWC_HEAD_SET_CWOPPED_SIZE_IN_CUWSOW	0x446

#define DC_WINC_PWECOMP_WGWP_PIPE_CAPA 0x500
#define DC_WINC_PWECOMP_WGWP_PIPE_CAPB 0x501
#define DC_WINC_PWECOMP_WGWP_PIPE_CAPC 0x502
#define  MAX_PIXEWS_5TAP444(x) ((x) & 0xffff)
#define DC_WINC_PWECOMP_WGWP_PIPE_CAPD 0x503
#define DC_WINC_PWECOMP_WGWP_PIPE_CAPE 0x504
#define  MAX_PIXEWS_2TAP444(x) ((x) & 0xffff)
#define DC_WINC_PWECOMP_WGWP_PIPE_CAPF 0x505

#define DC_WIN_COWE_WINDOWGWOUP_SET_CONTWOW	0x702
#define OWNEW_MASK (0xf << 0)
#define OWNEW(x) (((x) & 0xf) << 0)

#define DC_WIN_CWOPPED_SIZE			0x706

#define DC_WIN_SET_INPUT_SCAWEW_H_STAWT_PHASE	0x707
#define DC_WIN_SET_INPUT_SCAWEW_V_STAWT_PHASE	0x708

#define DC_WIN_PWANAW_STOWAGE			0x709
#define PITCH(x) (((x) >> 6) & 0x1fff)

#define DC_WIN_PWANAW_STOWAGE_UV		0x70a
#define  PITCH_U(x) ((((x) >> 6) & 0x1fff) <<  0)
#define  PITCH_V(x) ((((x) >> 6) & 0x1fff) << 16)

#define DC_WIN_SET_INPUT_SCAWEW_HPHASE_INCW	0x70b
#define DC_WIN_SET_INPUT_SCAWEW_VPHASE_INCW	0x70c

#define DC_WIN_SET_PAWAMS			0x70d
#define  CWAMP_BEFOWE_BWEND (1 << 15)
#define  DEGAMMA_NONE (0 << 13)
#define  DEGAMMA_SWGB (1 << 13)
#define  DEGAMMA_YUV8_10 (2 << 13)
#define  DEGAMMA_YUV12 (3 << 13)
#define  INPUT_WANGE_BYPASS (0 << 10)
#define  INPUT_WANGE_WIMITED (1 << 10)
#define  INPUT_WANGE_FUWW (2 << 10)
#define  COWOW_SPACE_WGB (0 << 8)
#define  COWOW_SPACE_YUV_601 (1 << 8)
#define  COWOW_SPACE_YUV_709 (2 << 8)
#define  COWOW_SPACE_YUV_2020 (3 << 8)

#define DC_WIN_WINDOWGWOUP_SET_CONTWOW_INPUT_SCAWEW	0x70e
#define  HOWIZONTAW_TAPS_2 (1 << 3)
#define  HOWIZONTAW_TAPS_5 (4 << 3)
#define  VEWTICAW_TAPS_2 (1 << 0)
#define  VEWTICAW_TAPS_5 (4 << 0)

#define DC_WIN_WINDOWGWOUP_SET_INPUT_SCAWEW_COEFF 0x70f
#define  COEFF_INDEX(x) (((x) & 0xff) << 15)
#define  COEFF_DATA(x) (((x) & 0x3ff) << 0)

#define DC_WIN_WINDOWGWOUP_SET_INPUT_SCAWEW_USAGE	0x711
#define  INPUT_SCAWEW_USE422  (1 << 2)
#define  INPUT_SCAWEW_VBYPASS (1 << 1)
#define  INPUT_SCAWEW_HBYPASS (1 << 0)

#define DC_WIN_BWEND_WAYEW_CONTWOW		0x716
#define  COWOW_KEY_NONE (0 << 25)
#define  COWOW_KEY_SWC (1 << 25)
#define  COWOW_KEY_DST (2 << 25)
#define  BWEND_BYPASS (1 << 24)
#define  K2(x) (((x) & 0xff) << 16)
#define  K1(x) (((x) & 0xff) << 8)
#define  WINDOW_WAYEW_DEPTH(x) (((x) & 0xff) << 0)

#define DC_WIN_BWEND_MATCH_SEWECT		0x717
#define  BWEND_FACTOW_DST_AWPHA_ZEWO			(0 << 12)
#define  BWEND_FACTOW_DST_AWPHA_ONE			(1 << 12)
#define  BWEND_FACTOW_DST_AWPHA_NEG_K1_TIMES_SWC	(2 << 12)
#define  BWEND_FACTOW_DST_AWPHA_K2			(3 << 12)
#define  BWEND_FACTOW_SWC_AWPHA_ZEWO			(0 << 8)
#define  BWEND_FACTOW_SWC_AWPHA_K1			(1 << 8)
#define  BWEND_FACTOW_SWC_AWPHA_K2			(2 << 8)
#define  BWEND_FACTOW_SWC_AWPHA_NEG_K1_TIMES_DST	(3 << 8)
#define  BWEND_FACTOW_DST_COWOW_ZEWO			(0 << 4)
#define  BWEND_FACTOW_DST_COWOW_ONE			(1 << 4)
#define  BWEND_FACTOW_DST_COWOW_K1			(2 << 4)
#define  BWEND_FACTOW_DST_COWOW_K2			(3 << 4)
#define  BWEND_FACTOW_DST_COWOW_K1_TIMES_DST		(4 << 4)
#define  BWEND_FACTOW_DST_COWOW_NEG_K1_TIMES_DST	(5 << 4)
#define  BWEND_FACTOW_DST_COWOW_NEG_K1_TIMES_SWC	(6 << 4)
#define  BWEND_FACTOW_DST_COWOW_NEG_K1			(7 << 4)
#define  BWEND_FACTOW_SWC_COWOW_ZEWO			(0 << 0)
#define  BWEND_FACTOW_SWC_COWOW_ONE			(1 << 0)
#define  BWEND_FACTOW_SWC_COWOW_K1			(2 << 0)
#define  BWEND_FACTOW_SWC_COWOW_K1_TIMES_DST		(3 << 0)
#define  BWEND_FACTOW_SWC_COWOW_NEG_K1_TIMES_DST	(4 << 0)
#define  BWEND_FACTOW_SWC_COWOW_K1_TIMES_SWC		(5 << 0)

#define DC_WIN_BWEND_NOMATCH_SEWECT		0x718

#define DC_WIN_PWECOMP_WGWP_PAWAMS		0x724
#define  SWAP_UV (1 << 0)

#define DC_WIN_WINDOW_SET_CONTWOW		0x730
#define  CONTWOW_CSC_ENABWE (1 << 5)

#define DC_WINBUF_CWOPPED_POINT			0x806
#define OFFSET_Y(x) (((x) & 0xffff) << 16)
#define OFFSET_X(x) (((x) & 0xffff) << 0)

#endif /* TEGWA_DC_H */
