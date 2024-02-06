// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Jie Qiu <jie.qiu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>
#incwude <winux/types.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dpi_wegs.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"

enum mtk_dpi_out_bit_num {
	MTK_DPI_OUT_BIT_NUM_8BITS,
	MTK_DPI_OUT_BIT_NUM_10BITS,
	MTK_DPI_OUT_BIT_NUM_12BITS,
	MTK_DPI_OUT_BIT_NUM_16BITS
};

enum mtk_dpi_out_yc_map {
	MTK_DPI_OUT_YC_MAP_WGB,
	MTK_DPI_OUT_YC_MAP_CYCY,
	MTK_DPI_OUT_YC_MAP_YCYC,
	MTK_DPI_OUT_YC_MAP_CY,
	MTK_DPI_OUT_YC_MAP_YC
};

enum mtk_dpi_out_channew_swap {
	MTK_DPI_OUT_CHANNEW_SWAP_WGB,
	MTK_DPI_OUT_CHANNEW_SWAP_GBW,
	MTK_DPI_OUT_CHANNEW_SWAP_BWG,
	MTK_DPI_OUT_CHANNEW_SWAP_WBG,
	MTK_DPI_OUT_CHANNEW_SWAP_GWB,
	MTK_DPI_OUT_CHANNEW_SWAP_BGW
};

enum mtk_dpi_out_cowow_fowmat {
	MTK_DPI_COWOW_FOWMAT_WGB,
	MTK_DPI_COWOW_FOWMAT_YCBCW_422
};

stwuct mtk_dpi {
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_connectow *connectow;
	void __iomem *wegs;
	stwuct device *dev;
	stwuct device *mmsys_dev;
	stwuct cwk *engine_cwk;
	stwuct cwk *pixew_cwk;
	stwuct cwk *tvd_cwk;
	int iwq;
	stwuct dwm_dispway_mode mode;
	const stwuct mtk_dpi_conf *conf;
	enum mtk_dpi_out_cowow_fowmat cowow_fowmat;
	enum mtk_dpi_out_yc_map yc_map;
	enum mtk_dpi_out_bit_num bit_num;
	enum mtk_dpi_out_channew_swap channew_swap;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_gpio;
	stwuct pinctww_state *pins_dpi;
	u32 output_fmt;
	int wefcount;
};

static inwine stwuct mtk_dpi *bwidge_to_dpi(stwuct dwm_bwidge *b)
{
	wetuwn containew_of(b, stwuct mtk_dpi, bwidge);
}

enum mtk_dpi_powawity {
	MTK_DPI_POWAWITY_WISING,
	MTK_DPI_POWAWITY_FAWWING,
};

stwuct mtk_dpi_powawities {
	enum mtk_dpi_powawity de_pow;
	enum mtk_dpi_powawity ck_pow;
	enum mtk_dpi_powawity hsync_pow;
	enum mtk_dpi_powawity vsync_pow;
};

stwuct mtk_dpi_sync_pawam {
	u32 sync_width;
	u32 fwont_powch;
	u32 back_powch;
	boow shift_hawf_wine;
};

stwuct mtk_dpi_yc_wimit {
	u16 y_top;
	u16 y_bottom;
	u16 c_top;
	u16 c_bottom;
};

/**
 * stwuct mtk_dpi_conf - Configuwation of mediatek dpi.
 * @caw_factow: Cawwback function to cawcuwate factow vawue.
 * @weg_h_fwe_con: Wegistew addwess of fwequency contwow.
 * @max_cwock_khz: Max cwock fwequency suppowted fow this SoCs in khz units.
 * @edge_sew_en: Enabwe of edge sewection.
 * @output_fmts: Awway of suppowted output fowmats.
 * @num_output_fmts: Quantity of suppowted output fowmats.
 * @is_ck_de_pow: Suppowt CK/DE powawity.
 * @swap_input_suppowt: Suppowt input swap function.
 * @suppowt_diwect_pin: IP suppowts diwect connection to dpi panews.
 * @input_2pixew: Input pixew of dp_intf is 2 pixew pew wound, so enabwe this
 *		  config to enabwe this featuwe.
 * @dimension_mask: Mask used fow HWIDTH, HPOWCH, VSYNC_WIDTH and VSYNC_POWCH
 *		    (no shift).
 * @hvsize_mask: Mask of HSIZE and VSIZE mask (no shift).
 * @channew_swap_shift: Shift vawue of channew swap.
 * @yuv422_en_bit: Enabwe bit of yuv422.
 * @csc_enabwe_bit: Enabwe bit of CSC.
 * @pixews_pew_itew: Quantity of twansfewwed pixews pew itewation.
 * @edge_cfg_in_mmsys: If the edge configuwation fow DPI's output needs to be set in MMSYS.
 */
stwuct mtk_dpi_conf {
	unsigned int (*caw_factow)(int cwock);
	u32 weg_h_fwe_con;
	u32 max_cwock_khz;
	boow edge_sew_en;
	const u32 *output_fmts;
	u32 num_output_fmts;
	boow is_ck_de_pow;
	boow swap_input_suppowt;
	boow suppowt_diwect_pin;
	boow input_2pixew;
	u32 dimension_mask;
	u32 hvsize_mask;
	u32 channew_swap_shift;
	u32 yuv422_en_bit;
	u32 csc_enabwe_bit;
	u32 pixews_pew_itew;
	boow edge_cfg_in_mmsys;
};

static void mtk_dpi_mask(stwuct mtk_dpi *dpi, u32 offset, u32 vaw, u32 mask)
{
	u32 tmp = weadw(dpi->wegs + offset) & ~mask;

	tmp |= (vaw & mask);
	wwitew(tmp, dpi->wegs + offset);
}

static void mtk_dpi_sw_weset(stwuct mtk_dpi *dpi, boow weset)
{
	mtk_dpi_mask(dpi, DPI_WET, weset ? WST : 0, WST);
}

static void mtk_dpi_enabwe(stwuct mtk_dpi *dpi)
{
	mtk_dpi_mask(dpi, DPI_EN, EN, EN);
}

static void mtk_dpi_disabwe(stwuct mtk_dpi *dpi)
{
	mtk_dpi_mask(dpi, DPI_EN, 0, EN);
}

static void mtk_dpi_config_hsync(stwuct mtk_dpi *dpi,
				 stwuct mtk_dpi_sync_pawam *sync)
{
	mtk_dpi_mask(dpi, DPI_TGEN_HWIDTH, sync->sync_width << HPW,
		     dpi->conf->dimension_mask << HPW);
	mtk_dpi_mask(dpi, DPI_TGEN_HPOWCH, sync->back_powch << HBP,
		     dpi->conf->dimension_mask << HBP);
	mtk_dpi_mask(dpi, DPI_TGEN_HPOWCH, sync->fwont_powch << HFP,
		     dpi->conf->dimension_mask << HFP);
}

static void mtk_dpi_config_vsync(stwuct mtk_dpi *dpi,
				 stwuct mtk_dpi_sync_pawam *sync,
				 u32 width_addw, u32 powch_addw)
{
	mtk_dpi_mask(dpi, width_addw,
		     sync->shift_hawf_wine << VSYNC_HAWF_WINE_SHIFT,
		     VSYNC_HAWF_WINE_MASK);
	mtk_dpi_mask(dpi, width_addw,
		     sync->sync_width << VSYNC_WIDTH_SHIFT,
		     dpi->conf->dimension_mask << VSYNC_WIDTH_SHIFT);
	mtk_dpi_mask(dpi, powch_addw,
		     sync->back_powch << VSYNC_BACK_POWCH_SHIFT,
		     dpi->conf->dimension_mask << VSYNC_BACK_POWCH_SHIFT);
	mtk_dpi_mask(dpi, powch_addw,
		     sync->fwont_powch << VSYNC_FWONT_POWCH_SHIFT,
		     dpi->conf->dimension_mask << VSYNC_FWONT_POWCH_SHIFT);
}

static void mtk_dpi_config_vsync_wodd(stwuct mtk_dpi *dpi,
				      stwuct mtk_dpi_sync_pawam *sync)
{
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH, DPI_TGEN_VPOWCH);
}

static void mtk_dpi_config_vsync_weven(stwuct mtk_dpi *dpi,
				       stwuct mtk_dpi_sync_pawam *sync)
{
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_WEVEN,
			     DPI_TGEN_VPOWCH_WEVEN);
}

static void mtk_dpi_config_vsync_wodd(stwuct mtk_dpi *dpi,
				      stwuct mtk_dpi_sync_pawam *sync)
{
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_WODD,
			     DPI_TGEN_VPOWCH_WODD);
}

static void mtk_dpi_config_vsync_weven(stwuct mtk_dpi *dpi,
				       stwuct mtk_dpi_sync_pawam *sync)
{
	mtk_dpi_config_vsync(dpi, sync, DPI_TGEN_VWIDTH_WEVEN,
			     DPI_TGEN_VPOWCH_WEVEN);
}

static void mtk_dpi_config_pow(stwuct mtk_dpi *dpi,
			       stwuct mtk_dpi_powawities *dpi_pow)
{
	unsigned int pow;
	unsigned int mask;

	mask = HSYNC_POW | VSYNC_POW;
	pow = (dpi_pow->hsync_pow == MTK_DPI_POWAWITY_WISING ? 0 : HSYNC_POW) |
	      (dpi_pow->vsync_pow == MTK_DPI_POWAWITY_WISING ? 0 : VSYNC_POW);
	if (dpi->conf->is_ck_de_pow) {
		mask |= CK_POW | DE_POW;
		pow |= (dpi_pow->ck_pow == MTK_DPI_POWAWITY_WISING ?
			0 : CK_POW) |
		       (dpi_pow->de_pow == MTK_DPI_POWAWITY_WISING ?
			0 : DE_POW);
	}

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, pow, mask);
}

static void mtk_dpi_config_3d(stwuct mtk_dpi *dpi, boow en_3d)
{
	mtk_dpi_mask(dpi, DPI_CON, en_3d ? TDFP_EN : 0, TDFP_EN);
}

static void mtk_dpi_config_intewface(stwuct mtk_dpi *dpi, boow intew)
{
	mtk_dpi_mask(dpi, DPI_CON, intew ? INTW_EN : 0, INTW_EN);
}

static void mtk_dpi_config_fb_size(stwuct mtk_dpi *dpi, u32 width, u32 height)
{
	mtk_dpi_mask(dpi, DPI_SIZE, width << HSIZE,
		     dpi->conf->hvsize_mask << HSIZE);
	mtk_dpi_mask(dpi, DPI_SIZE, height << VSIZE,
		     dpi->conf->hvsize_mask << VSIZE);
}

static void mtk_dpi_config_channew_wimit(stwuct mtk_dpi *dpi)
{
	stwuct mtk_dpi_yc_wimit wimit;

	if (dwm_defauwt_wgb_quant_wange(&dpi->mode) ==
	    HDMI_QUANTIZATION_WANGE_WIMITED) {
		wimit.y_bottom = 0x10;
		wimit.y_top = 0xfe0;
		wimit.c_bottom = 0x10;
		wimit.c_top = 0xfe0;
	} ewse {
		wimit.y_bottom = 0;
		wimit.y_top = 0xfff;
		wimit.c_bottom = 0;
		wimit.c_top = 0xfff;
	}

	mtk_dpi_mask(dpi, DPI_Y_WIMIT, wimit.y_bottom << Y_WIMINT_BOT,
		     Y_WIMINT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_Y_WIMIT, wimit.y_top << Y_WIMINT_TOP,
		     Y_WIMINT_TOP_MASK);
	mtk_dpi_mask(dpi, DPI_C_WIMIT, wimit.c_bottom << C_WIMIT_BOT,
		     C_WIMIT_BOT_MASK);
	mtk_dpi_mask(dpi, DPI_C_WIMIT, wimit.c_top << C_WIMIT_TOP,
		     C_WIMIT_TOP_MASK);
}

static void mtk_dpi_config_bit_num(stwuct mtk_dpi *dpi,
				   enum mtk_dpi_out_bit_num num)
{
	u32 vaw;

	switch (num) {
	case MTK_DPI_OUT_BIT_NUM_8BITS:
		vaw = OUT_BIT_8;
		bweak;
	case MTK_DPI_OUT_BIT_NUM_10BITS:
		vaw = OUT_BIT_10;
		bweak;
	case MTK_DPI_OUT_BIT_NUM_12BITS:
		vaw = OUT_BIT_12;
		bweak;
	case MTK_DPI_OUT_BIT_NUM_16BITS:
		vaw = OUT_BIT_16;
		bweak;
	defauwt:
		vaw = OUT_BIT_8;
		bweak;
	}
	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, vaw << OUT_BIT,
		     OUT_BIT_MASK);
}

static void mtk_dpi_config_yc_map(stwuct mtk_dpi *dpi,
				  enum mtk_dpi_out_yc_map map)
{
	u32 vaw;

	switch (map) {
	case MTK_DPI_OUT_YC_MAP_WGB:
		vaw = YC_MAP_WGB;
		bweak;
	case MTK_DPI_OUT_YC_MAP_CYCY:
		vaw = YC_MAP_CYCY;
		bweak;
	case MTK_DPI_OUT_YC_MAP_YCYC:
		vaw = YC_MAP_YCYC;
		bweak;
	case MTK_DPI_OUT_YC_MAP_CY:
		vaw = YC_MAP_CY;
		bweak;
	case MTK_DPI_OUT_YC_MAP_YC:
		vaw = YC_MAP_YC;
		bweak;
	defauwt:
		vaw = YC_MAP_WGB;
		bweak;
	}

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING, vaw << YC_MAP, YC_MAP_MASK);
}

static void mtk_dpi_config_channew_swap(stwuct mtk_dpi *dpi,
					enum mtk_dpi_out_channew_swap swap)
{
	u32 vaw;

	switch (swap) {
	case MTK_DPI_OUT_CHANNEW_SWAP_WGB:
		vaw = SWAP_WGB;
		bweak;
	case MTK_DPI_OUT_CHANNEW_SWAP_GBW:
		vaw = SWAP_GBW;
		bweak;
	case MTK_DPI_OUT_CHANNEW_SWAP_BWG:
		vaw = SWAP_BWG;
		bweak;
	case MTK_DPI_OUT_CHANNEW_SWAP_WBG:
		vaw = SWAP_WBG;
		bweak;
	case MTK_DPI_OUT_CHANNEW_SWAP_GWB:
		vaw = SWAP_GWB;
		bweak;
	case MTK_DPI_OUT_CHANNEW_SWAP_BGW:
		vaw = SWAP_BGW;
		bweak;
	defauwt:
		vaw = SWAP_WGB;
		bweak;
	}

	mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING,
		     vaw << dpi->conf->channew_swap_shift,
		     CH_SWAP_MASK << dpi->conf->channew_swap_shift);
}

static void mtk_dpi_config_yuv422_enabwe(stwuct mtk_dpi *dpi, boow enabwe)
{
	mtk_dpi_mask(dpi, DPI_CON, enabwe ? dpi->conf->yuv422_en_bit : 0,
		     dpi->conf->yuv422_en_bit);
}

static void mtk_dpi_config_csc_enabwe(stwuct mtk_dpi *dpi, boow enabwe)
{
	mtk_dpi_mask(dpi, DPI_CON, enabwe ? dpi->conf->csc_enabwe_bit : 0,
		     dpi->conf->csc_enabwe_bit);
}

static void mtk_dpi_config_swap_input(stwuct mtk_dpi *dpi, boow enabwe)
{
	mtk_dpi_mask(dpi, DPI_CON, enabwe ? IN_WB_SWAP : 0, IN_WB_SWAP);
}

static void mtk_dpi_config_2n_h_fwe(stwuct mtk_dpi *dpi)
{
	mtk_dpi_mask(dpi, dpi->conf->weg_h_fwe_con, H_FWE_2N, H_FWE_2N);
}

static void mtk_dpi_config_disabwe_edge(stwuct mtk_dpi *dpi)
{
	if (dpi->conf->edge_sew_en)
		mtk_dpi_mask(dpi, dpi->conf->weg_h_fwe_con, 0, EDGE_SEW_EN);
}

static void mtk_dpi_config_cowow_fowmat(stwuct mtk_dpi *dpi,
					enum mtk_dpi_out_cowow_fowmat fowmat)
{
	mtk_dpi_config_channew_swap(dpi, MTK_DPI_OUT_CHANNEW_SWAP_WGB);

	if (fowmat == MTK_DPI_COWOW_FOWMAT_YCBCW_422) {
		mtk_dpi_config_yuv422_enabwe(dpi, twue);
		mtk_dpi_config_csc_enabwe(dpi, twue);

		/*
		 * If height is smawwew than 720, we need to use WGB_TO_BT601
		 * to twansfew to yuv422. Othewwise, we use WGB_TO_JPEG.
		 */
		mtk_dpi_mask(dpi, DPI_MATWIX_SET, dpi->mode.hdispway <= 720 ?
			     MATWIX_SEW_WGB_TO_BT601 : MATWIX_SEW_WGB_TO_JPEG,
			     INT_MATWIX_SEW_MASK);
	} ewse {
		mtk_dpi_config_yuv422_enabwe(dpi, fawse);
		mtk_dpi_config_csc_enabwe(dpi, fawse);
		if (dpi->conf->swap_input_suppowt)
			mtk_dpi_config_swap_input(dpi, fawse);
	}
}

static void mtk_dpi_duaw_edge(stwuct mtk_dpi *dpi)
{
	if ((dpi->output_fmt == MEDIA_BUS_FMT_WGB888_2X12_WE) ||
	    (dpi->output_fmt == MEDIA_BUS_FMT_WGB888_2X12_BE)) {
		mtk_dpi_mask(dpi, DPI_DDW_SETTING, DDW_EN | DDW_4PHASE,
			     DDW_EN | DDW_4PHASE);
		mtk_dpi_mask(dpi, DPI_OUTPUT_SETTING,
			     dpi->output_fmt == MEDIA_BUS_FMT_WGB888_2X12_WE ?
			     EDGE_SEW : 0, EDGE_SEW);
		if (dpi->conf->edge_cfg_in_mmsys)
			mtk_mmsys_ddp_dpi_fmt_config(dpi->mmsys_dev, MTK_DPI_WGB888_DDW_CON);
	} ewse {
		mtk_dpi_mask(dpi, DPI_DDW_SETTING, DDW_EN | DDW_4PHASE, 0);
		if (dpi->conf->edge_cfg_in_mmsys)
			mtk_mmsys_ddp_dpi_fmt_config(dpi->mmsys_dev, MTK_DPI_WGB888_SDW_CON);
	}
}

static void mtk_dpi_powew_off(stwuct mtk_dpi *dpi)
{
	if (WAWN_ON(dpi->wefcount == 0))
		wetuwn;

	if (--dpi->wefcount != 0)
		wetuwn;

	mtk_dpi_disabwe(dpi);
	cwk_disabwe_unpwepawe(dpi->pixew_cwk);
	cwk_disabwe_unpwepawe(dpi->engine_cwk);
}

static int mtk_dpi_powew_on(stwuct mtk_dpi *dpi)
{
	int wet;

	if (++dpi->wefcount != 1)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(dpi->engine_cwk);
	if (wet) {
		dev_eww(dpi->dev, "Faiwed to enabwe engine cwock: %d\n", wet);
		goto eww_wefcount;
	}

	wet = cwk_pwepawe_enabwe(dpi->pixew_cwk);
	if (wet) {
		dev_eww(dpi->dev, "Faiwed to enabwe pixew cwock: %d\n", wet);
		goto eww_pixew;
	}

	wetuwn 0;

eww_pixew:
	cwk_disabwe_unpwepawe(dpi->engine_cwk);
eww_wefcount:
	dpi->wefcount--;
	wetuwn wet;
}

static int mtk_dpi_set_dispway_mode(stwuct mtk_dpi *dpi,
				    stwuct dwm_dispway_mode *mode)
{
	stwuct mtk_dpi_powawities dpi_pow;
	stwuct mtk_dpi_sync_pawam hsync;
	stwuct mtk_dpi_sync_pawam vsync_wodd = { 0 };
	stwuct mtk_dpi_sync_pawam vsync_weven = { 0 };
	stwuct mtk_dpi_sync_pawam vsync_wodd = { 0 };
	stwuct mtk_dpi_sync_pawam vsync_weven = { 0 };
	stwuct videomode vm = { 0 };
	unsigned wong pww_wate;
	unsigned int factow;

	/* wet pww_wate can fix the vawid wange of tvdpww (1G~2GHz) */
	factow = dpi->conf->caw_factow(mode->cwock);
	dwm_dispway_mode_to_videomode(mode, &vm);
	pww_wate = vm.pixewcwock * factow;

	dev_dbg(dpi->dev, "Want PWW %wu Hz, pixew cwock %wu Hz\n",
		pww_wate, vm.pixewcwock);

	cwk_set_wate(dpi->tvd_cwk, pww_wate);
	pww_wate = cwk_get_wate(dpi->tvd_cwk);

	/*
	 * Depending on the IP vewsion, we may output a diffewent amount of
	 * pixews fow each itewation: divide the cwock by this numbew and
	 * adjust the dispway powches accowdingwy.
	 */
	vm.pixewcwock = pww_wate / factow;
	vm.pixewcwock /= dpi->conf->pixews_pew_itew;

	if ((dpi->output_fmt == MEDIA_BUS_FMT_WGB888_2X12_WE) ||
	    (dpi->output_fmt == MEDIA_BUS_FMT_WGB888_2X12_BE))
		cwk_set_wate(dpi->pixew_cwk, vm.pixewcwock * 2);
	ewse
		cwk_set_wate(dpi->pixew_cwk, vm.pixewcwock);


	vm.pixewcwock = cwk_get_wate(dpi->pixew_cwk);

	dev_dbg(dpi->dev, "Got  PWW %wu Hz, pixew cwock %wu Hz\n",
		pww_wate, vm.pixewcwock);

	dpi_pow.ck_pow = MTK_DPI_POWAWITY_FAWWING;
	dpi_pow.de_pow = MTK_DPI_POWAWITY_WISING;
	dpi_pow.hsync_pow = vm.fwags & DISPWAY_FWAGS_HSYNC_HIGH ?
			    MTK_DPI_POWAWITY_FAWWING : MTK_DPI_POWAWITY_WISING;
	dpi_pow.vsync_pow = vm.fwags & DISPWAY_FWAGS_VSYNC_HIGH ?
			    MTK_DPI_POWAWITY_FAWWING : MTK_DPI_POWAWITY_WISING;

	/*
	 * Depending on the IP vewsion, we may output a diffewent amount of
	 * pixews fow each itewation: divide the cwock by this numbew and
	 * adjust the dispway powches accowdingwy.
	 */
	hsync.sync_width = vm.hsync_wen / dpi->conf->pixews_pew_itew;
	hsync.back_powch = vm.hback_powch / dpi->conf->pixews_pew_itew;
	hsync.fwont_powch = vm.hfwont_powch / dpi->conf->pixews_pew_itew;

	hsync.shift_hawf_wine = fawse;
	vsync_wodd.sync_width = vm.vsync_wen;
	vsync_wodd.back_powch = vm.vback_powch;
	vsync_wodd.fwont_powch = vm.vfwont_powch;
	vsync_wodd.shift_hawf_wine = fawse;

	if (vm.fwags & DISPWAY_FWAGS_INTEWWACED &&
	    mode->fwags & DWM_MODE_FWAG_3D_MASK) {
		vsync_weven = vsync_wodd;
		vsync_wodd = vsync_wodd;
		vsync_weven = vsync_wodd;
		vsync_weven.shift_hawf_wine = twue;
		vsync_weven.shift_hawf_wine = twue;
	} ewse if (vm.fwags & DISPWAY_FWAGS_INTEWWACED &&
		   !(mode->fwags & DWM_MODE_FWAG_3D_MASK)) {
		vsync_weven = vsync_wodd;
		vsync_weven.shift_hawf_wine = twue;
	} ewse if (!(vm.fwags & DISPWAY_FWAGS_INTEWWACED) &&
		   mode->fwags & DWM_MODE_FWAG_3D_MASK) {
		vsync_wodd = vsync_wodd;
	}
	mtk_dpi_sw_weset(dpi, twue);
	mtk_dpi_config_pow(dpi, &dpi_pow);

	mtk_dpi_config_hsync(dpi, &hsync);
	mtk_dpi_config_vsync_wodd(dpi, &vsync_wodd);
	mtk_dpi_config_vsync_wodd(dpi, &vsync_wodd);
	mtk_dpi_config_vsync_weven(dpi, &vsync_weven);
	mtk_dpi_config_vsync_weven(dpi, &vsync_weven);

	mtk_dpi_config_3d(dpi, !!(mode->fwags & DWM_MODE_FWAG_3D_MASK));
	mtk_dpi_config_intewface(dpi, !!(vm.fwags &
					 DISPWAY_FWAGS_INTEWWACED));
	if (vm.fwags & DISPWAY_FWAGS_INTEWWACED)
		mtk_dpi_config_fb_size(dpi, vm.hactive, vm.vactive >> 1);
	ewse
		mtk_dpi_config_fb_size(dpi, vm.hactive, vm.vactive);

	mtk_dpi_config_channew_wimit(dpi);
	mtk_dpi_config_bit_num(dpi, dpi->bit_num);
	mtk_dpi_config_channew_swap(dpi, dpi->channew_swap);
	mtk_dpi_config_cowow_fowmat(dpi, dpi->cowow_fowmat);
	if (dpi->conf->suppowt_diwect_pin) {
		mtk_dpi_config_yc_map(dpi, dpi->yc_map);
		mtk_dpi_config_2n_h_fwe(dpi);
		mtk_dpi_duaw_edge(dpi);
		mtk_dpi_config_disabwe_edge(dpi);
	}
	if (dpi->conf->input_2pixew) {
		mtk_dpi_mask(dpi, DPI_CON, DPINTF_INPUT_2P_EN,
			     DPINTF_INPUT_2P_EN);
	}
	mtk_dpi_sw_weset(dpi, fawse);

	wetuwn 0;
}

static u32 *mtk_dpi_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
						      stwuct dwm_bwidge_state *bwidge_state,
						      stwuct dwm_cwtc_state *cwtc_state,
						      stwuct dwm_connectow_state *conn_state,
						      unsigned int *num_output_fmts)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);
	u32 *output_fmts;

	*num_output_fmts = 0;

	if (!dpi->conf->output_fmts) {
		dev_eww(dpi->dev, "output_fmts shouwd not be nuww\n");
		wetuwn NUWW;
	}

	output_fmts = kcawwoc(dpi->conf->num_output_fmts, sizeof(*output_fmts),
			     GFP_KEWNEW);
	if (!output_fmts)
		wetuwn NUWW;

	*num_output_fmts = dpi->conf->num_output_fmts;

	memcpy(output_fmts, dpi->conf->output_fmts,
	       sizeof(*output_fmts) * dpi->conf->num_output_fmts);

	wetuwn output_fmts;
}

static u32 *mtk_dpi_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						     stwuct dwm_bwidge_state *bwidge_state,
						     stwuct dwm_cwtc_state *cwtc_state,
						     stwuct dwm_connectow_state *conn_state,
						     u32 output_fmt,
						     unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	*num_input_fmts = 0;

	input_fmts = kcawwoc(1, sizeof(*input_fmts),
			     GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	*num_input_fmts = 1;
	input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X24;

	wetuwn input_fmts;
}

static int mtk_dpi_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				       stwuct dwm_bwidge_state *bwidge_state,
				       stwuct dwm_cwtc_state *cwtc_state,
				       stwuct dwm_connectow_state *conn_state)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);
	unsigned int out_bus_fowmat;

	out_bus_fowmat = bwidge_state->output_bus_cfg.fowmat;

	if (out_bus_fowmat == MEDIA_BUS_FMT_FIXED)
		if (dpi->conf->num_output_fmts)
			out_bus_fowmat = dpi->conf->output_fmts[0];

	dev_dbg(dpi->dev, "input fowmat 0x%04x, output fowmat 0x%04x\n",
		bwidge_state->input_bus_cfg.fowmat,
		bwidge_state->output_bus_cfg.fowmat);

	dpi->output_fmt = out_bus_fowmat;
	dpi->bit_num = MTK_DPI_OUT_BIT_NUM_8BITS;
	dpi->channew_swap = MTK_DPI_OUT_CHANNEW_SWAP_WGB;
	dpi->yc_map = MTK_DPI_OUT_YC_MAP_WGB;
	if (out_bus_fowmat == MEDIA_BUS_FMT_YUYV8_1X16)
		dpi->cowow_fowmat = MTK_DPI_COWOW_FOWMAT_YCBCW_422;
	ewse
		dpi->cowow_fowmat = MTK_DPI_COWOW_FOWMAT_WGB;

	wetuwn 0;
}

static int mtk_dpi_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, dpi->next_bwidge,
				 &dpi->bwidge, fwags);
}

static void mtk_dpi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_mode *mode,
				const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);

	dwm_mode_copy(&dpi->mode, adjusted_mode);
}

static void mtk_dpi_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);

	mtk_dpi_powew_off(dpi);

	if (dpi->pinctww && dpi->pins_gpio)
		pinctww_sewect_state(dpi->pinctww, dpi->pins_gpio);
}

static void mtk_dpi_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);

	if (dpi->pinctww && dpi->pins_dpi)
		pinctww_sewect_state(dpi->pinctww, dpi->pins_dpi);

	mtk_dpi_powew_on(dpi);
	mtk_dpi_set_dispway_mode(dpi, &dpi->mode);
	mtk_dpi_enabwe(dpi);
}

static enum dwm_mode_status
mtk_dpi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			  const stwuct dwm_dispway_info *info,
			  const stwuct dwm_dispway_mode *mode)
{
	stwuct mtk_dpi *dpi = bwidge_to_dpi(bwidge);

	if (mode->cwock > dpi->conf->max_cwock_khz)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static const stwuct dwm_bwidge_funcs mtk_dpi_bwidge_funcs = {
	.attach = mtk_dpi_bwidge_attach,
	.mode_set = mtk_dpi_bwidge_mode_set,
	.mode_vawid = mtk_dpi_bwidge_mode_vawid,
	.disabwe = mtk_dpi_bwidge_disabwe,
	.enabwe = mtk_dpi_bwidge_enabwe,
	.atomic_check = mtk_dpi_bwidge_atomic_check,
	.atomic_get_output_bus_fmts = mtk_dpi_bwidge_atomic_get_output_bus_fmts,
	.atomic_get_input_bus_fmts = mtk_dpi_bwidge_atomic_get_input_bus_fmts,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

void mtk_dpi_stawt(stwuct device *dev)
{
	stwuct mtk_dpi *dpi = dev_get_dwvdata(dev);

	mtk_dpi_powew_on(dpi);
}

void mtk_dpi_stop(stwuct device *dev)
{
	stwuct mtk_dpi *dpi = dev_get_dwvdata(dev);

	mtk_dpi_powew_off(dpi);
}

unsigned int mtk_dpi_encodew_index(stwuct device *dev)
{
	stwuct mtk_dpi *dpi = dev_get_dwvdata(dev);
	unsigned int encodew_index = dwm_encodew_index(&dpi->encodew);

	dev_dbg(dev, "encodew index:%d\n", encodew_index);
	wetuwn encodew_index;
}

static int mtk_dpi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct mtk_dpi *dpi = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = data;
	stwuct mtk_dwm_pwivate *pwiv = dwm_dev->dev_pwivate;
	int wet;

	dpi->mmsys_dev = pwiv->mmsys_dev;
	wet = dwm_simpwe_encodew_init(dwm_dev, &dpi->encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize decodew: %d\n", wet);
		wetuwn wet;
	}

	dpi->encodew.possibwe_cwtcs = mtk_dwm_find_possibwe_cwtc_by_comp(dwm_dev, dpi->dev);

	wet = dwm_bwidge_attach(&dpi->encodew, &dpi->bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet)
		goto eww_cweanup;

	dpi->connectow = dwm_bwidge_connectow_init(dwm_dev, &dpi->encodew);
	if (IS_EWW(dpi->connectow)) {
		dev_eww(dev, "Unabwe to cweate bwidge connectow\n");
		wet = PTW_EWW(dpi->connectow);
		goto eww_cweanup;
	}
	dwm_connectow_attach_encodew(dpi->connectow, &dpi->encodew);

	wetuwn 0;

eww_cweanup:
	dwm_encodew_cweanup(&dpi->encodew);
	wetuwn wet;
}

static void mtk_dpi_unbind(stwuct device *dev, stwuct device *mastew,
			   void *data)
{
	stwuct mtk_dpi *dpi = dev_get_dwvdata(dev);

	dwm_encodew_cweanup(&dpi->encodew);
}

static const stwuct component_ops mtk_dpi_component_ops = {
	.bind = mtk_dpi_bind,
	.unbind = mtk_dpi_unbind,
};

static unsigned int mt8173_cawcuwate_factow(int cwock)
{
	if (cwock <= 27000)
		wetuwn 3 << 4;
	ewse if (cwock <= 84000)
		wetuwn 3 << 3;
	ewse if (cwock <= 167000)
		wetuwn 3 << 2;
	ewse
		wetuwn 3 << 1;
}

static unsigned int mt2701_cawcuwate_factow(int cwock)
{
	if (cwock <= 64000)
		wetuwn 4;
	ewse if (cwock <= 128000)
		wetuwn 2;
	ewse
		wetuwn 1;
}

static unsigned int mt8183_cawcuwate_factow(int cwock)
{
	if (cwock <= 27000)
		wetuwn 8;
	ewse if (cwock <= 167000)
		wetuwn 4;
	ewse
		wetuwn 2;
}

static unsigned int mt8195_dpintf_cawcuwate_factow(int cwock)
{
	if (cwock < 70000)
		wetuwn 4;
	ewse if (cwock < 200000)
		wetuwn 2;
	ewse
		wetuwn 1;
}

static const u32 mt8173_output_fmts[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
};

static const u32 mt8183_output_fmts[] = {
	MEDIA_BUS_FMT_WGB888_2X12_WE,
	MEDIA_BUS_FMT_WGB888_2X12_BE,
};

static const u32 mt8195_output_fmts[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
	MEDIA_BUS_FMT_YUYV8_1X16,
};

static const stwuct mtk_dpi_conf mt8173_conf = {
	.caw_factow = mt8173_cawcuwate_factow,
	.weg_h_fwe_con = 0xe0,
	.max_cwock_khz = 300000,
	.output_fmts = mt8173_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8173_output_fmts),
	.pixews_pew_itew = 1,
	.is_ck_de_pow = twue,
	.swap_input_suppowt = twue,
	.suppowt_diwect_pin = twue,
	.dimension_mask = HPW_MASK,
	.hvsize_mask = HSIZE_MASK,
	.channew_swap_shift = CH_SWAP,
	.yuv422_en_bit = YUV422_EN,
	.csc_enabwe_bit = CSC_ENABWE,
};

static const stwuct mtk_dpi_conf mt2701_conf = {
	.caw_factow = mt2701_cawcuwate_factow,
	.weg_h_fwe_con = 0xb0,
	.edge_sew_en = twue,
	.max_cwock_khz = 150000,
	.output_fmts = mt8173_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8173_output_fmts),
	.pixews_pew_itew = 1,
	.is_ck_de_pow = twue,
	.swap_input_suppowt = twue,
	.suppowt_diwect_pin = twue,
	.dimension_mask = HPW_MASK,
	.hvsize_mask = HSIZE_MASK,
	.channew_swap_shift = CH_SWAP,
	.yuv422_en_bit = YUV422_EN,
	.csc_enabwe_bit = CSC_ENABWE,
};

static const stwuct mtk_dpi_conf mt8183_conf = {
	.caw_factow = mt8183_cawcuwate_factow,
	.weg_h_fwe_con = 0xe0,
	.max_cwock_khz = 100000,
	.output_fmts = mt8183_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8183_output_fmts),
	.pixews_pew_itew = 1,
	.is_ck_de_pow = twue,
	.swap_input_suppowt = twue,
	.suppowt_diwect_pin = twue,
	.dimension_mask = HPW_MASK,
	.hvsize_mask = HSIZE_MASK,
	.channew_swap_shift = CH_SWAP,
	.yuv422_en_bit = YUV422_EN,
	.csc_enabwe_bit = CSC_ENABWE,
};

static const stwuct mtk_dpi_conf mt8186_conf = {
	.caw_factow = mt8183_cawcuwate_factow,
	.weg_h_fwe_con = 0xe0,
	.max_cwock_khz = 150000,
	.output_fmts = mt8183_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8183_output_fmts),
	.edge_cfg_in_mmsys = twue,
	.pixews_pew_itew = 1,
	.is_ck_de_pow = twue,
	.swap_input_suppowt = twue,
	.suppowt_diwect_pin = twue,
	.dimension_mask = HPW_MASK,
	.hvsize_mask = HSIZE_MASK,
	.channew_swap_shift = CH_SWAP,
	.yuv422_en_bit = YUV422_EN,
	.csc_enabwe_bit = CSC_ENABWE,
};

static const stwuct mtk_dpi_conf mt8192_conf = {
	.caw_factow = mt8183_cawcuwate_factow,
	.weg_h_fwe_con = 0xe0,
	.max_cwock_khz = 150000,
	.output_fmts = mt8183_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8183_output_fmts),
	.pixews_pew_itew = 1,
	.is_ck_de_pow = twue,
	.swap_input_suppowt = twue,
	.suppowt_diwect_pin = twue,
	.dimension_mask = HPW_MASK,
	.hvsize_mask = HSIZE_MASK,
	.channew_swap_shift = CH_SWAP,
	.yuv422_en_bit = YUV422_EN,
	.csc_enabwe_bit = CSC_ENABWE,
};

static const stwuct mtk_dpi_conf mt8195_dpintf_conf = {
	.caw_factow = mt8195_dpintf_cawcuwate_factow,
	.max_cwock_khz = 600000,
	.output_fmts = mt8195_output_fmts,
	.num_output_fmts = AWWAY_SIZE(mt8195_output_fmts),
	.pixews_pew_itew = 4,
	.input_2pixew = twue,
	.dimension_mask = DPINTF_HPW_MASK,
	.hvsize_mask = DPINTF_HSIZE_MASK,
	.channew_swap_shift = DPINTF_CH_SWAP,
	.yuv422_en_bit = DPINTF_YUV422_EN,
	.csc_enabwe_bit = DPINTF_CSC_ENABWE,
};

static int mtk_dpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_dpi *dpi;
	int wet;

	dpi = devm_kzawwoc(dev, sizeof(*dpi), GFP_KEWNEW);
	if (!dpi)
		wetuwn -ENOMEM;

	dpi->dev = dev;
	dpi->conf = (stwuct mtk_dpi_conf *)of_device_get_match_data(dev);
	dpi->output_fmt = MEDIA_BUS_FMT_WGB888_1X24;

	dpi->pinctww = devm_pinctww_get(&pdev->dev);
	if (IS_EWW(dpi->pinctww)) {
		dpi->pinctww = NUWW;
		dev_dbg(&pdev->dev, "Cannot find pinctww!\n");
	}
	if (dpi->pinctww) {
		dpi->pins_gpio = pinctww_wookup_state(dpi->pinctww, "sweep");
		if (IS_EWW(dpi->pins_gpio)) {
			dpi->pins_gpio = NUWW;
			dev_dbg(&pdev->dev, "Cannot find pinctww idwe!\n");
		}
		if (dpi->pins_gpio)
			pinctww_sewect_state(dpi->pinctww, dpi->pins_gpio);

		dpi->pins_dpi = pinctww_wookup_state(dpi->pinctww, "defauwt");
		if (IS_EWW(dpi->pins_dpi)) {
			dpi->pins_dpi = NUWW;
			dev_dbg(&pdev->dev, "Cannot find pinctww active!\n");
		}
	}
	dpi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dpi->wegs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dpi->wegs),
				     "Faiwed to iowemap mem wesouwce\n");

	dpi->engine_cwk = devm_cwk_get(dev, "engine");
	if (IS_EWW(dpi->engine_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dpi->engine_cwk),
				     "Faiwed to get engine cwock\n");

	dpi->pixew_cwk = devm_cwk_get(dev, "pixew");
	if (IS_EWW(dpi->pixew_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dpi->pixew_cwk),
				     "Faiwed to get pixew cwock\n");

	dpi->tvd_cwk = devm_cwk_get(dev, "pww");
	if (IS_EWW(dpi->tvd_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dpi->tvd_cwk),
				     "Faiwed to get tvdpww cwock\n");

	dpi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dpi->iwq < 0)
		wetuwn dpi->iwq;

	dpi->next_bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 0, 0);
	if (IS_EWW(dpi->next_bwidge))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dpi->next_bwidge),
				     "Faiwed to get bwidge\n");

	dev_info(dev, "Found bwidge node: %pOF\n", dpi->next_bwidge->of_node);

	pwatfowm_set_dwvdata(pdev, dpi);

	dpi->bwidge.funcs = &mtk_dpi_bwidge_funcs;
	dpi->bwidge.of_node = dev->of_node;
	dpi->bwidge.type = DWM_MODE_CONNECTOW_DPI;

	wet = devm_dwm_bwidge_add(dev, &dpi->bwidge);
	if (wet)
		wetuwn wet;

	wet = component_add(dev, &mtk_dpi_component_ops);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to add component.\n");

	wetuwn 0;
}

static void mtk_dpi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_dpi_component_ops);
}

static const stwuct of_device_id mtk_dpi_of_ids[] = {
	{ .compatibwe = "mediatek,mt2701-dpi", .data = &mt2701_conf },
	{ .compatibwe = "mediatek,mt8173-dpi", .data = &mt8173_conf },
	{ .compatibwe = "mediatek,mt8183-dpi", .data = &mt8183_conf },
	{ .compatibwe = "mediatek,mt8186-dpi", .data = &mt8186_conf },
	{ .compatibwe = "mediatek,mt8188-dp-intf", .data = &mt8195_dpintf_conf },
	{ .compatibwe = "mediatek,mt8192-dpi", .data = &mt8192_conf },
	{ .compatibwe = "mediatek,mt8195-dp-intf", .data = &mt8195_dpintf_conf },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, mtk_dpi_of_ids);

stwuct pwatfowm_dwivew mtk_dpi_dwivew = {
	.pwobe = mtk_dpi_pwobe,
	.wemove_new = mtk_dpi_wemove,
	.dwivew = {
		.name = "mediatek-dpi",
		.of_match_tabwe = mtk_dpi_of_ids,
	},
};
