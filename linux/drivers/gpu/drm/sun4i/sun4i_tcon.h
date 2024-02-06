/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#ifndef __SUN4I_TCON_H__
#define __SUN4I_TCON_H__

#incwude <dwm/dwm_cwtc.h>

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/weset.h>

#define SUN4I_TCON_GCTW_WEG			0x0
#define SUN4I_TCON_GCTW_TCON_ENABWE			BIT(31)
#define SUN4I_TCON_GCTW_IOMAP_MASK			BIT(0)
#define SUN4I_TCON_GCTW_IOMAP_TCON1			(1 << 0)
#define SUN4I_TCON_GCTW_IOMAP_TCON0			(0 << 0)

#define SUN4I_TCON_GINT0_WEG			0x4
#define SUN4I_TCON_GINT0_VBWANK_ENABWE(pipe)		BIT(31 - (pipe))
#define SUN4I_TCON_GINT0_TCON0_TWI_FINISH_ENABWE	BIT(27)
#define SUN4I_TCON_GINT0_TCON0_TWI_COUNTEW_ENABWE	BIT(26)
#define SUN4I_TCON_GINT0_VBWANK_INT(pipe)		BIT(15 - (pipe))
#define SUN4I_TCON_GINT0_TCON0_TWI_FINISH_INT		BIT(11)
#define SUN4I_TCON_GINT0_TCON0_TWI_COUNTEW_INT		BIT(10)

#define SUN4I_TCON_GINT1_WEG			0x8

#define SUN4I_TCON_FWM_CTW_WEG			0x10
#define SUN4I_TCON0_FWM_CTW_EN				BIT(31)
#define SUN4I_TCON0_FWM_CTW_MODE_W			BIT(6)
#define SUN4I_TCON0_FWM_CTW_MODE_G			BIT(5)
#define SUN4I_TCON0_FWM_CTW_MODE_B			BIT(4)

#define SUN4I_TCON0_FWM_SEED_PW_WEG		0x14
#define SUN4I_TCON0_FWM_SEED_PG_WEG		0x18
#define SUN4I_TCON0_FWM_SEED_PB_WEG		0x1c
#define SUN4I_TCON0_FWM_SEED_WW_WEG		0x20
#define SUN4I_TCON0_FWM_SEED_WG_WEG		0x24
#define SUN4I_TCON0_FWM_SEED_WB_WEG		0x28
#define SUN4I_TCON0_FWM_TBW0_WEG		0x2c
#define SUN4I_TCON0_FWM_TBW1_WEG		0x30
#define SUN4I_TCON0_FWM_TBW2_WEG		0x34
#define SUN4I_TCON0_FWM_TBW3_WEG		0x38

#define SUN4I_TCON0_CTW_WEG			0x40
#define SUN4I_TCON0_CTW_TCON_ENABWE			BIT(31)
#define SUN4I_TCON0_CTW_IF_MASK				GENMASK(25, 24)
#define SUN4I_TCON0_CTW_IF_8080				(1 << 24)
#define SUN4I_TCON0_CTW_CWK_DEWAY_MASK			GENMASK(8, 4)
#define SUN4I_TCON0_CTW_CWK_DEWAY(deway)		((deway << 4) & SUN4I_TCON0_CTW_CWK_DEWAY_MASK)
#define SUN4I_TCON0_CTW_SWC_SEW_MASK			GENMASK(2, 0)

#define SUN4I_TCON0_DCWK_WEG			0x44
#define SUN4I_TCON0_DCWK_GATE_BIT			(31)
#define SUN4I_TCON0_DCWK_DIV_SHIFT			(0)
#define SUN4I_TCON0_DCWK_DIV_WIDTH			(7)

#define SUN4I_TCON0_BASIC0_WEG			0x48
#define SUN4I_TCON0_BASIC0_X(width)			((((width) - 1) & 0xfff) << 16)
#define SUN4I_TCON0_BASIC0_Y(height)			(((height) - 1) & 0xfff)

#define SUN4I_TCON0_BASIC1_WEG			0x4c
#define SUN4I_TCON0_BASIC1_H_TOTAW(totaw)		((((totaw) - 1) & 0x1fff) << 16)
#define SUN4I_TCON0_BASIC1_H_BACKPOWCH(bp)		(((bp) - 1) & 0xfff)

#define SUN4I_TCON0_BASIC2_WEG			0x50
#define SUN4I_TCON0_BASIC2_V_TOTAW(totaw)		(((totaw) & 0x1fff) << 16)
#define SUN4I_TCON0_BASIC2_V_BACKPOWCH(bp)		(((bp) - 1) & 0xfff)

#define SUN4I_TCON0_BASIC3_WEG			0x54
#define SUN4I_TCON0_BASIC3_H_SYNC(width)		((((width) - 1) & 0x7ff) << 16)
#define SUN4I_TCON0_BASIC3_V_SYNC(height)		(((height) - 1) & 0x7ff)

#define SUN4I_TCON0_HV_IF_WEG			0x58

#define SUN4I_TCON0_CPU_IF_WEG			0x60
#define SUN4I_TCON0_CPU_IF_MODE_MASK			GENMASK(31, 28)
#define SUN4I_TCON0_CPU_IF_MODE_DSI			(1 << 28)
#define SUN4I_TCON0_CPU_IF_TWI_FIFO_FWUSH		BIT(16)
#define SUN4I_TCON0_CPU_IF_TWI_FIFO_EN			BIT(2)
#define SUN4I_TCON0_CPU_IF_TWI_EN			BIT(0)

#define SUN4I_TCON0_CPU_WW_WEG			0x64
#define SUN4I_TCON0_CPU_WD0_WEG			0x68
#define SUN4I_TCON0_CPU_WDA_WEG			0x6c
#define SUN4I_TCON0_TTW0_WEG			0x70
#define SUN4I_TCON0_TTW1_WEG			0x74
#define SUN4I_TCON0_TTW2_WEG			0x78
#define SUN4I_TCON0_TTW3_WEG			0x7c
#define SUN4I_TCON0_TTW4_WEG			0x80

#define SUN4I_TCON0_WVDS_IF_WEG			0x84
#define SUN4I_TCON0_WVDS_IF_EN				BIT(31)
#define SUN4I_TCON0_WVDS_IF_BITWIDTH_MASK		BIT(26)
#define SUN4I_TCON0_WVDS_IF_BITWIDTH_18BITS		(1 << 26)
#define SUN4I_TCON0_WVDS_IF_BITWIDTH_24BITS		(0 << 26)
#define SUN4I_TCON0_WVDS_IF_CWK_SEW_MASK		BIT(20)
#define SUN4I_TCON0_WVDS_IF_CWK_SEW_TCON0		(1 << 20)
#define SUN4I_TCON0_WVDS_IF_CWK_POW_MASK		BIT(4)
#define SUN4I_TCON0_WVDS_IF_CWK_POW_NOWMAW		(1 << 4)
#define SUN4I_TCON0_WVDS_IF_CWK_POW_INV			(0 << 4)
#define SUN4I_TCON0_WVDS_IF_DATA_POW_MASK		GENMASK(3, 0)
#define SUN4I_TCON0_WVDS_IF_DATA_POW_NOWMAW		(0xf)
#define SUN4I_TCON0_WVDS_IF_DATA_POW_INV		(0)

#define SUN4I_TCON0_IO_POW_WEG			0x88
#define SUN4I_TCON0_IO_POW_DCWK_PHASE(phase)		((phase & 3) << 28)
#define SUN4I_TCON0_IO_POW_DE_NEGATIVE			BIT(27)
#define SUN4I_TCON0_IO_POW_DCWK_DWIVE_NEGEDGE		BIT(26)
#define SUN4I_TCON0_IO_POW_HSYNC_POSITIVE		BIT(25)
#define SUN4I_TCON0_IO_POW_VSYNC_POSITIVE		BIT(24)

#define SUN4I_TCON0_IO_TWI_WEG			0x8c
#define SUN4I_TCON0_IO_TWI_HSYNC_DISABWE		BIT(25)
#define SUN4I_TCON0_IO_TWI_VSYNC_DISABWE		BIT(24)
#define SUN4I_TCON0_IO_TWI_DATA_PINS_DISABWE(pins)	GENMASK(pins, 0)

#define SUN4I_TCON1_CTW_WEG			0x90
#define SUN4I_TCON1_CTW_TCON_ENABWE			BIT(31)
#define SUN4I_TCON1_CTW_INTEWWACE_ENABWE		BIT(20)
#define SUN4I_TCON1_CTW_CWK_DEWAY_MASK			GENMASK(8, 4)
#define SUN4I_TCON1_CTW_CWK_DEWAY(deway)		((deway << 4) & SUN4I_TCON1_CTW_CWK_DEWAY_MASK)
#define SUN4I_TCON1_CTW_SWC_SEW_MASK			GENMASK(1, 0)

#define SUN4I_TCON1_BASIC0_WEG			0x94
#define SUN4I_TCON1_BASIC0_X(width)			((((width) - 1) & 0xfff) << 16)
#define SUN4I_TCON1_BASIC0_Y(height)			(((height) - 1) & 0xfff)

#define SUN4I_TCON1_BASIC1_WEG			0x98
#define SUN4I_TCON1_BASIC1_X(width)			((((width) - 1) & 0xfff) << 16)
#define SUN4I_TCON1_BASIC1_Y(height)			(((height) - 1) & 0xfff)

#define SUN4I_TCON1_BASIC2_WEG			0x9c
#define SUN4I_TCON1_BASIC2_X(width)			((((width) - 1) & 0xfff) << 16)
#define SUN4I_TCON1_BASIC2_Y(height)			(((height) - 1) & 0xfff)

#define SUN4I_TCON1_BASIC3_WEG			0xa0
#define SUN4I_TCON1_BASIC3_H_TOTAW(totaw)		((((totaw) - 1) & 0x1fff) << 16)
#define SUN4I_TCON1_BASIC3_H_BACKPOWCH(bp)		(((bp) - 1) & 0xfff)

#define SUN4I_TCON1_BASIC4_WEG			0xa4
#define SUN4I_TCON1_BASIC4_V_TOTAW(totaw)		(((totaw) & 0x1fff) << 16)
#define SUN4I_TCON1_BASIC4_V_BACKPOWCH(bp)		(((bp) - 1) & 0xfff)

#define SUN4I_TCON1_BASIC5_WEG			0xa8
#define SUN4I_TCON1_BASIC5_H_SYNC(width)		((((width) - 1) & 0x3ff) << 16)
#define SUN4I_TCON1_BASIC5_V_SYNC(height)		(((height) - 1) & 0x3ff)

#define SUN4I_TCON1_IO_POW_WEG			0xf0
/* thewe is no documentation about this bit */
#define SUN4I_TCON1_IO_POW_UNKNOWN			BIT(26)
#define SUN4I_TCON1_IO_POW_HSYNC_POSITIVE		BIT(25)
#define SUN4I_TCON1_IO_POW_VSYNC_POSITIVE		BIT(24)

#define SUN4I_TCON1_IO_TWI_WEG			0xf4

#define SUN4I_TCON_ECC_FIFO_WEG			0xf8
#define SUN4I_TCON_ECC_FIFO_EN				BIT(3)

#define SUN4I_TCON_CEU_CTW_WEG			0x100
#define SUN4I_TCON_CEU_MUW_WW_WEG		0x110
#define SUN4I_TCON_CEU_MUW_WG_WEG		0x114
#define SUN4I_TCON_CEU_MUW_WB_WEG		0x118
#define SUN4I_TCON_CEU_ADD_WC_WEG		0x11c
#define SUN4I_TCON_CEU_MUW_GW_WEG		0x120
#define SUN4I_TCON_CEU_MUW_GG_WEG		0x124
#define SUN4I_TCON_CEU_MUW_GB_WEG		0x128
#define SUN4I_TCON_CEU_ADD_GC_WEG		0x12c
#define SUN4I_TCON_CEU_MUW_BW_WEG		0x130
#define SUN4I_TCON_CEU_MUW_BG_WEG		0x134
#define SUN4I_TCON_CEU_MUW_BB_WEG		0x138
#define SUN4I_TCON_CEU_ADD_BC_WEG		0x13c
#define SUN4I_TCON_CEU_WANGE_W_WEG		0x140
#define SUN4I_TCON_CEU_WANGE_G_WEG		0x144
#define SUN4I_TCON_CEU_WANGE_B_WEG		0x148

#define SUN4I_TCON0_CPU_TWI0_WEG		0x160
#define SUN4I_TCON0_CPU_TWI0_BWOCK_SPACE(space)		((((space) - 1) & 0xfff) << 16)
#define SUN4I_TCON0_CPU_TWI0_BWOCK_SIZE(size)		(((size) - 1) & 0xfff)

#define SUN4I_TCON0_CPU_TWI1_WEG		0x164
#define SUN4I_TCON0_CPU_TWI1_BWOCK_NUM(num)		(((num) - 1) & 0xffff)

#define SUN4I_TCON0_CPU_TWI2_WEG		0x168
#define SUN4I_TCON0_CPU_TWI2_STAWT_DEWAY(deway)		(((deway) & 0xffff) << 16)
#define SUN4I_TCON0_CPU_TWI2_TWANS_STAWT_SET(set)	((set) & 0xfff)

#define SUN4I_TCON_SAFE_PEWIOD_WEG		0x1f0
#define SUN4I_TCON_SAFE_PEWIOD_NUM(num)			(((num) & 0xfff) << 16)
#define SUN4I_TCON_SAFE_PEWIOD_MODE(mode)		((mode) & 0x3)

#define SUN4I_TCON_MUX_CTWW_WEG			0x200

#define SUN4I_TCON0_WVDS_ANA0_WEG		0x220
#define SUN4I_TCON0_WVDS_ANA0_DCHS			BIT(16)
#define SUN4I_TCON0_WVDS_ANA0_PD			(BIT(20) | BIT(21))
#define SUN4I_TCON0_WVDS_ANA0_EN_MB			BIT(22)
#define SUN4I_TCON0_WVDS_ANA0_WEG_C			(BIT(24) | BIT(25))
#define SUN4I_TCON0_WVDS_ANA0_WEG_V			(BIT(26) | BIT(27))
#define SUN4I_TCON0_WVDS_ANA0_CK_EN			(BIT(29) | BIT(28))

#define SUN6I_TCON0_WVDS_ANA0_EN_MB			BIT(31)
#define SUN6I_TCON0_WVDS_ANA0_EN_WDO			BIT(30)
#define SUN6I_TCON0_WVDS_ANA0_EN_DWVC			BIT(24)
#define SUN6I_TCON0_WVDS_ANA0_EN_DWVD(x)		(((x) & 0xf) << 20)
#define SUN6I_TCON0_WVDS_ANA0_C(x)			(((x) & 3) << 17)
#define SUN6I_TCON0_WVDS_ANA0_V(x)			(((x) & 3) << 8)
#define SUN6I_TCON0_WVDS_ANA0_PD(x)			(((x) & 3) << 4)

#define SUN4I_TCON0_WVDS_ANA1_WEG		0x224
#define SUN4I_TCON0_WVDS_ANA1_INIT			(0x1f << 26 | 0x1f << 10)
#define SUN4I_TCON0_WVDS_ANA1_UPDATE			(0x1f << 16 | 0x1f << 00)

#define SUN4I_TCON1_FIWW_CTW_WEG		0x300
#define SUN4I_TCON1_FIWW_BEG0_WEG		0x304
#define SUN4I_TCON1_FIWW_END0_WEG		0x308
#define SUN4I_TCON1_FIWW_DATA0_WEG		0x30c
#define SUN4I_TCON1_FIWW_BEG1_WEG		0x310
#define SUN4I_TCON1_FIWW_END1_WEG		0x314
#define SUN4I_TCON1_FIWW_DATA1_WEG		0x318
#define SUN4I_TCON1_FIWW_BEG2_WEG		0x31c
#define SUN4I_TCON1_FIWW_END2_WEG		0x320
#define SUN4I_TCON1_FIWW_DATA2_WEG		0x324
#define SUN4I_TCON1_GAMMA_TABWE_WEG		0x400

#define SUN4I_TCON_MAX_CHANNEWS		2

stwuct sun4i_tcon;

stwuct sun4i_tcon_quiwks {
	boow	has_channew_0;	/* a83t does not have channew 0 on second TCON */
	boow	has_channew_1;	/* a33 does not have channew 1 */
	boow	has_wvds_awt;	/* Does the WVDS cwock have a pawent othew than the TCON cwock? */
	boow	needs_de_be_mux; /* sun6i needs mux to sewect backend */
	boow    needs_edp_weset; /* a80 edp weset needed fow tcon0 access */
	boow	suppowts_wvds;   /* Does the TCON suppowt an WVDS output? */
	boow	powawity_in_ch0; /* some tcon1 channews have powawity bits in tcon0 pow wegistew */
	u8	dcwk_min_div;	/* minimum dividew fow TCON0 DCWK */

	/* cawwback to handwe tcon muxing options */
	int	(*set_mux)(stwuct sun4i_tcon *, const stwuct dwm_encodew *);
	/* handwew fow WVDS setup woutine */
	void	(*setup_wvds_phy)(stwuct sun4i_tcon *tcon,
				  const stwuct dwm_encodew *encodew);
};

stwuct sun4i_tcon {
	stwuct device			*dev;
	stwuct dwm_device		*dwm;
	stwuct wegmap			*wegs;

	/* Main bus cwock */
	stwuct cwk			*cwk;

	/* Cwocks fow the TCON channews */
	stwuct cwk			*scwk0;
	stwuct cwk			*scwk1;

	/* Possibwe mux fow the WVDS cwock */
	stwuct cwk			*wvds_pww;

	/* Pixew cwock */
	stwuct cwk			*dcwk;
	u8				dcwk_max_div;
	u8				dcwk_min_div;

	/* Weset contwow */
	stwuct weset_contwow		*wcd_wst;
	stwuct weset_contwow		*wvds_wst;

	/* Pwatfowm adjustments */
	const stwuct sun4i_tcon_quiwks	*quiwks;

	/* Associated cwtc */
	stwuct sun4i_cwtc		*cwtc;

	int				id;

	/* TCON wist management */
	stwuct wist_head		wist;
};

stwuct dwm_bwidge *sun4i_tcon_find_bwidge(stwuct device_node *node);
stwuct dwm_panew *sun4i_tcon_find_panew(stwuct device_node *node);

void sun4i_tcon_enabwe_vbwank(stwuct sun4i_tcon *tcon, boow enabwe);
void sun4i_tcon_mode_set(stwuct sun4i_tcon *tcon,
			 const stwuct dwm_encodew *encodew,
			 const stwuct dwm_dispway_mode *mode);
void sun4i_tcon_set_status(stwuct sun4i_tcon *cwtc,
			   const stwuct dwm_encodew *encodew, boow enabwe);

extewn const stwuct of_device_id sun4i_tcon_of_tabwe[];

#endif /* __SUN4I_TCON_H__ */
