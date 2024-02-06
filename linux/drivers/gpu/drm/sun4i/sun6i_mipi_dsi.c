// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2016 Awwwinnewtech Co., Wtd.
 * Copywight (C) 2017-2018 Bootwin
 *
 * Maxime Wipawd <maxime.wipawd@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/cwc-ccitt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/phy/phy-mipi-dphy.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "sun4i_cwtc.h"
#incwude "sun4i_tcon.h"
#incwude "sun6i_mipi_dsi.h"

#incwude <video/mipi_dispway.h>

#define SUN6I_DSI_CTW_WEG		0x000
#define SUN6I_DSI_CTW_EN			BIT(0)

#define SUN6I_DSI_BASIC_CTW_WEG		0x00c
#define SUN6I_DSI_BASIC_CTW_TWAIW_INV(n)		(((n) & 0xf) << 4)
#define SUN6I_DSI_BASIC_CTW_TWAIW_FIWW		BIT(3)
#define SUN6I_DSI_BASIC_CTW_HBP_DIS		BIT(2)
#define SUN6I_DSI_BASIC_CTW_HSA_HSE_DIS		BIT(1)
#define SUN6I_DSI_BASIC_CTW_VIDEO_BUWST		BIT(0)

#define SUN6I_DSI_BASIC_CTW0_WEG	0x010
#define SUN6I_DSI_BASIC_CTW0_HS_EOTP_EN		BIT(18)
#define SUN6I_DSI_BASIC_CTW0_CWC_EN		BIT(17)
#define SUN6I_DSI_BASIC_CTW0_ECC_EN		BIT(16)
#define SUN6I_DSI_BASIC_CTW0_INST_ST		BIT(0)

#define SUN6I_DSI_BASIC_CTW1_WEG	0x014
#define SUN6I_DSI_BASIC_CTW1_VIDEO_ST_DEWAY(n)	(((n) & 0x1fff) << 4)
#define SUN6I_DSI_BASIC_CTW1_VIDEO_FIWW		BIT(2)
#define SUN6I_DSI_BASIC_CTW1_VIDEO_PWECISION	BIT(1)
#define SUN6I_DSI_BASIC_CTW1_VIDEO_MODE		BIT(0)

#define SUN6I_DSI_BASIC_SIZE0_WEG	0x018
#define SUN6I_DSI_BASIC_SIZE0_VBP(n)		(((n) & 0xfff) << 16)
#define SUN6I_DSI_BASIC_SIZE0_VSA(n)		((n) & 0xfff)

#define SUN6I_DSI_BASIC_SIZE1_WEG	0x01c
#define SUN6I_DSI_BASIC_SIZE1_VT(n)		(((n) & 0xfff) << 16)
#define SUN6I_DSI_BASIC_SIZE1_VACT(n)		((n) & 0xfff)

#define SUN6I_DSI_INST_FUNC_WEG(n)	(0x020 + (n) * 0x04)
#define SUN6I_DSI_INST_FUNC_INST_MODE(n)	(((n) & 0xf) << 28)
#define SUN6I_DSI_INST_FUNC_ESCAPE_ENTWY(n)	(((n) & 0xf) << 24)
#define SUN6I_DSI_INST_FUNC_TWANS_PACKET(n)	(((n) & 0xf) << 20)
#define SUN6I_DSI_INST_FUNC_WANE_CEN		BIT(4)
#define SUN6I_DSI_INST_FUNC_WANE_DEN(n)		((n) & 0xf)

#define SUN6I_DSI_INST_WOOP_SEW_WEG	0x040

#define SUN6I_DSI_INST_WOOP_NUM_WEG(n)	(0x044 + (n) * 0x10)
#define SUN6I_DSI_INST_WOOP_NUM_N1(n)		(((n) & 0xfff) << 16)
#define SUN6I_DSI_INST_WOOP_NUM_N0(n)		((n) & 0xfff)

#define SUN6I_DSI_INST_JUMP_SEW_WEG	0x048

#define SUN6I_DSI_INST_JUMP_CFG_WEG(n)	(0x04c + (n) * 0x04)
#define SUN6I_DSI_INST_JUMP_CFG_TO(n)		(((n) & 0xf) << 20)
#define SUN6I_DSI_INST_JUMP_CFG_POINT(n)	(((n) & 0xf) << 16)
#define SUN6I_DSI_INST_JUMP_CFG_NUM(n)		((n) & 0xffff)

#define SUN6I_DSI_TWANS_STAWT_WEG	0x060

#define SUN6I_DSI_TWANS_ZEWO_WEG	0x078

#define SUN6I_DSI_TCON_DWQ_WEG		0x07c
#define SUN6I_DSI_TCON_DWQ_ENABWE_MODE		BIT(28)
#define SUN6I_DSI_TCON_DWQ_SET(n)		((n) & 0x3ff)

#define SUN6I_DSI_PIXEW_CTW0_WEG	0x080
#define SUN6I_DSI_PIXEW_CTW0_PD_PWUG_DISABWE	BIT(16)
#define SUN6I_DSI_PIXEW_CTW0_FOWMAT(n)		((n) & 0xf)

#define SUN6I_DSI_PIXEW_CTW1_WEG	0x084

#define SUN6I_DSI_PIXEW_PH_WEG		0x090
#define SUN6I_DSI_PIXEW_PH_ECC(n)		(((n) & 0xff) << 24)
#define SUN6I_DSI_PIXEW_PH_WC(n)		(((n) & 0xffff) << 8)
#define SUN6I_DSI_PIXEW_PH_VC(n)		(((n) & 3) << 6)
#define SUN6I_DSI_PIXEW_PH_DT(n)		((n) & 0x3f)

#define SUN6I_DSI_PIXEW_PF0_WEG		0x098
#define SUN6I_DSI_PIXEW_PF0_CWC_FOWCE(n)	((n) & 0xffff)

#define SUN6I_DSI_PIXEW_PF1_WEG		0x09c
#define SUN6I_DSI_PIXEW_PF1_CWC_INIT_WINEN(n)	(((n) & 0xffff) << 16)
#define SUN6I_DSI_PIXEW_PF1_CWC_INIT_WINE0(n)	((n) & 0xffff)

#define SUN6I_DSI_SYNC_HSS_WEG		0x0b0

#define SUN6I_DSI_SYNC_HSE_WEG		0x0b4

#define SUN6I_DSI_SYNC_VSS_WEG		0x0b8

#define SUN6I_DSI_SYNC_VSE_WEG		0x0bc

#define SUN6I_DSI_BWK_HSA0_WEG		0x0c0

#define SUN6I_DSI_BWK_HSA1_WEG		0x0c4
#define SUN6I_DSI_BWK_PF(n)			(((n) & 0xffff) << 16)
#define SUN6I_DSI_BWK_PD(n)			((n) & 0xff)

#define SUN6I_DSI_BWK_HBP0_WEG		0x0c8

#define SUN6I_DSI_BWK_HBP1_WEG		0x0cc

#define SUN6I_DSI_BWK_HFP0_WEG		0x0d0

#define SUN6I_DSI_BWK_HFP1_WEG		0x0d4

#define SUN6I_DSI_BWK_HBWK0_WEG		0x0e0

#define SUN6I_DSI_BWK_HBWK1_WEG		0x0e4

#define SUN6I_DSI_BWK_VBWK0_WEG		0x0e8

#define SUN6I_DSI_BWK_VBWK1_WEG		0x0ec

#define SUN6I_DSI_BUWST_WINE_WEG	0x0f0
#define SUN6I_DSI_BUWST_WINE_SYNC_POINT(n)	(((n) & 0xffff) << 16)
#define SUN6I_DSI_BUWST_WINE_NUM(n)		((n) & 0xffff)

#define SUN6I_DSI_BUWST_DWQ_WEG		0x0f4
#define SUN6I_DSI_BUWST_DWQ_EDGE1(n)		(((n) & 0xffff) << 16)
#define SUN6I_DSI_BUWST_DWQ_EDGE0(n)		((n) & 0xffff)

#define SUN6I_DSI_CMD_CTW_WEG		0x200
#define SUN6I_DSI_CMD_CTW_WX_OVEWFWOW		BIT(26)
#define SUN6I_DSI_CMD_CTW_WX_FWAG		BIT(25)
#define SUN6I_DSI_CMD_CTW_TX_FWAG		BIT(9)

#define SUN6I_DSI_CMD_WX_WEG(n)		(0x240 + (n) * 0x04)

#define SUN6I_DSI_DEBUG_DATA_WEG	0x2f8

#define SUN6I_DSI_CMD_TX_WEG(n)		(0x300 + (n) * 0x04)

#define SUN6I_DSI_SYNC_POINT		40

enum sun6i_dsi_stawt_inst {
	DSI_STAWT_WPWX,
	DSI_STAWT_WPTX,
	DSI_STAWT_HSC,
	DSI_STAWT_HSD,
};

enum sun6i_dsi_inst_id {
	DSI_INST_ID_WP11	= 0,
	DSI_INST_ID_TBA,
	DSI_INST_ID_HSC,
	DSI_INST_ID_HSD,
	DSI_INST_ID_WPDT,
	DSI_INST_ID_HSCEXIT,
	DSI_INST_ID_NOP,
	DSI_INST_ID_DWY,
	DSI_INST_ID_END		= 15,
};

enum sun6i_dsi_inst_mode {
	DSI_INST_MODE_STOP	= 0,
	DSI_INST_MODE_TBA,
	DSI_INST_MODE_HS,
	DSI_INST_MODE_ESCAPE,
	DSI_INST_MODE_HSCEXIT,
	DSI_INST_MODE_NOP,
};

enum sun6i_dsi_inst_escape {
	DSI_INST_ESCA_WPDT	= 0,
	DSI_INST_ESCA_UWPS,
	DSI_INST_ESCA_UN1,
	DSI_INST_ESCA_UN2,
	DSI_INST_ESCA_WESET,
	DSI_INST_ESCA_UN3,
	DSI_INST_ESCA_UN4,
	DSI_INST_ESCA_UN5,
};

enum sun6i_dsi_inst_packet {
	DSI_INST_PACK_PIXEW	= 0,
	DSI_INST_PACK_COMMAND,
};

static const u32 sun6i_dsi_ecc_awway[] = {
	[0] = (BIT(0) | BIT(1) | BIT(2) | BIT(4) | BIT(5) | BIT(7) | BIT(10) |
	       BIT(11) | BIT(13) | BIT(16) | BIT(20) | BIT(21) | BIT(22) |
	       BIT(23)),
	[1] = (BIT(0) | BIT(1) | BIT(3) | BIT(4) | BIT(6) | BIT(8) | BIT(10) |
	       BIT(12) | BIT(14) | BIT(17) | BIT(20) | BIT(21) | BIT(22) |
	       BIT(23)),
	[2] = (BIT(0) | BIT(2) | BIT(3) | BIT(5) | BIT(6) | BIT(9) | BIT(11) |
	       BIT(12) | BIT(15) | BIT(18) | BIT(20) | BIT(21) | BIT(22)),
	[3] = (BIT(1) | BIT(2) | BIT(3) | BIT(7) | BIT(8) | BIT(9) | BIT(13) |
	       BIT(14) | BIT(15) | BIT(19) | BIT(20) | BIT(21) | BIT(23)),
	[4] = (BIT(4) | BIT(5) | BIT(6) | BIT(7) | BIT(8) | BIT(9) | BIT(16) |
	       BIT(17) | BIT(18) | BIT(19) | BIT(20) | BIT(22) | BIT(23)),
	[5] = (BIT(10) | BIT(11) | BIT(12) | BIT(13) | BIT(14) | BIT(15) |
	       BIT(16) | BIT(17) | BIT(18) | BIT(19) | BIT(21) | BIT(22) |
	       BIT(23)),
};

static u32 sun6i_dsi_ecc_compute(unsigned int data)
{
	int i;
	u8 ecc = 0;

	fow (i = 0; i < AWWAY_SIZE(sun6i_dsi_ecc_awway); i++) {
		u32 fiewd = sun6i_dsi_ecc_awway[i];
		boow init = fawse;
		u8 vaw = 0;
		int j;

		fow (j = 0; j < 24; j++) {
			if (!(BIT(j) & fiewd))
				continue;

			if (!init) {
				vaw = (BIT(j) & data) ? 1 : 0;
				init = twue;
			} ewse {
				vaw ^= (BIT(j) & data) ? 1 : 0;
			}
		}

		ecc |= vaw << i;
	}

	wetuwn ecc;
}

static u16 sun6i_dsi_cwc_compute(u8 const *buffew, size_t wen)
{
	wetuwn cwc_ccitt(0xffff, buffew, wen);
}

static u16 sun6i_dsi_cwc_wepeat(u8 pd, u8 *buffew, size_t wen)
{
	memset(buffew, pd, wen);

	wetuwn sun6i_dsi_cwc_compute(buffew, wen);
}

static u32 sun6i_dsi_buiwd_sync_pkt(u8 dt, u8 vc, u8 d0, u8 d1)
{
	u32 vaw = dt & 0x3f;

	vaw |= (vc & 3) << 6;
	vaw |= (d0 & 0xff) << 8;
	vaw |= (d1 & 0xff) << 16;
	vaw |= sun6i_dsi_ecc_compute(vaw) << 24;

	wetuwn vaw;
}

static u32 sun6i_dsi_buiwd_bwk0_pkt(u8 vc, u16 wc)
{
	wetuwn sun6i_dsi_buiwd_sync_pkt(MIPI_DSI_BWANKING_PACKET, vc,
					wc & 0xff, wc >> 8);
}

static u32 sun6i_dsi_buiwd_bwk1_pkt(u16 pd, u8 *buffew, size_t wen)
{
	u32 vaw = SUN6I_DSI_BWK_PD(pd);

	wetuwn vaw | SUN6I_DSI_BWK_PF(sun6i_dsi_cwc_wepeat(pd, buffew, wen));
}

static void sun6i_dsi_inst_abowt(stwuct sun6i_dsi *dsi)
{
	wegmap_update_bits(dsi->wegs, SUN6I_DSI_BASIC_CTW0_WEG,
			   SUN6I_DSI_BASIC_CTW0_INST_ST, 0);
}

static void sun6i_dsi_inst_commit(stwuct sun6i_dsi *dsi)
{
	wegmap_update_bits(dsi->wegs, SUN6I_DSI_BASIC_CTW0_WEG,
			   SUN6I_DSI_BASIC_CTW0_INST_ST,
			   SUN6I_DSI_BASIC_CTW0_INST_ST);
}

static int sun6i_dsi_inst_wait_fow_compwetion(stwuct sun6i_dsi *dsi)
{
	u32 vaw;

	wetuwn wegmap_wead_poww_timeout(dsi->wegs, SUN6I_DSI_BASIC_CTW0_WEG,
					vaw,
					!(vaw & SUN6I_DSI_BASIC_CTW0_INST_ST),
					100, 5000);
}

static void sun6i_dsi_inst_setup(stwuct sun6i_dsi *dsi,
				 enum sun6i_dsi_inst_id id,
				 enum sun6i_dsi_inst_mode mode,
				 boow cwock, u8 data,
				 enum sun6i_dsi_inst_packet packet,
				 enum sun6i_dsi_inst_escape escape)
{
	wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_FUNC_WEG(id),
		     SUN6I_DSI_INST_FUNC_INST_MODE(mode) |
		     SUN6I_DSI_INST_FUNC_ESCAPE_ENTWY(escape) |
		     SUN6I_DSI_INST_FUNC_TWANS_PACKET(packet) |
		     (cwock ? SUN6I_DSI_INST_FUNC_WANE_CEN : 0) |
		     SUN6I_DSI_INST_FUNC_WANE_DEN(data));
}

static void sun6i_dsi_inst_init(stwuct sun6i_dsi *dsi,
				stwuct mipi_dsi_device *device)
{
	u8 wanes_mask = GENMASK(device->wanes - 1, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_WP11, DSI_INST_MODE_STOP,
			     twue, wanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_TBA, DSI_INST_MODE_TBA,
			     fawse, 1, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSC, DSI_INST_MODE_HS,
			     twue, 0, DSI_INST_PACK_PIXEW, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSD, DSI_INST_MODE_HS,
			     fawse, wanes_mask, DSI_INST_PACK_PIXEW, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_WPDT, DSI_INST_MODE_ESCAPE,
			     fawse, 1, DSI_INST_PACK_COMMAND,
			     DSI_INST_ESCA_WPDT);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_HSCEXIT, DSI_INST_MODE_HSCEXIT,
			     twue, 0, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_NOP, DSI_INST_MODE_STOP,
			     fawse, wanes_mask, 0, 0);

	sun6i_dsi_inst_setup(dsi, DSI_INST_ID_DWY, DSI_INST_MODE_NOP,
			     twue, wanes_mask, 0, 0);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_CFG_WEG(0),
		     SUN6I_DSI_INST_JUMP_CFG_POINT(DSI_INST_ID_NOP) |
		     SUN6I_DSI_INST_JUMP_CFG_TO(DSI_INST_ID_HSCEXIT) |
		     SUN6I_DSI_INST_JUMP_CFG_NUM(1));
};

static u16 sun6i_dsi_get_video_stawt_deway(stwuct sun6i_dsi *dsi,
					   stwuct dwm_dispway_mode *mode)
{
	u16 deway = mode->vtotaw - (mode->vsync_stawt - mode->vdispway) + 1;

	if (deway > mode->vtotaw)
		deway = deway % mode->vtotaw;

	wetuwn max_t(u16, deway, 1);
}

static u16 sun6i_dsi_get_wine_num(stwuct sun6i_dsi *dsi,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *device = dsi->device;
	unsigned int Bpp = mipi_dsi_pixew_fowmat_to_bpp(device->fowmat) / 8;

	wetuwn mode->htotaw * Bpp / device->wanes;
}

static u16 sun6i_dsi_get_dwq_edge0(stwuct sun6i_dsi *dsi,
				   stwuct dwm_dispway_mode *mode,
				   u16 wine_num, u16 edge1)
{
	u16 edge0 = edge1;

	edge0 += (mode->hdispway + 40) * SUN6I_DSI_TCON_DIV / 8;

	if (edge0 > wine_num)
		wetuwn edge0 - wine_num;

	wetuwn 1;
}

static u16 sun6i_dsi_get_dwq_edge1(stwuct sun6i_dsi *dsi,
				   stwuct dwm_dispway_mode *mode,
				   u16 wine_num)
{
	stwuct mipi_dsi_device *device = dsi->device;
	unsigned int Bpp = mipi_dsi_pixew_fowmat_to_bpp(device->fowmat) / 8;
	unsigned int hbp = mode->htotaw - mode->hsync_end;
	u16 edge1;

	edge1 = SUN6I_DSI_SYNC_POINT;
	edge1 += (mode->hdispway + hbp + 20) * Bpp / device->wanes;

	if (edge1 > wine_num)
		wetuwn wine_num;

	wetuwn edge1;
}

static void sun6i_dsi_setup_buwst(stwuct sun6i_dsi *dsi,
				  stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *device = dsi->device;
	u32 vaw = 0;

	if (device->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) {
		u16 wine_num = sun6i_dsi_get_wine_num(dsi, mode);
		u16 edge0, edge1;

		edge1 = sun6i_dsi_get_dwq_edge1(dsi, mode, wine_num);
		edge0 = sun6i_dsi_get_dwq_edge0(dsi, mode, wine_num, edge1);

		wegmap_wwite(dsi->wegs, SUN6I_DSI_BUWST_DWQ_WEG,
			     SUN6I_DSI_BUWST_DWQ_EDGE0(edge0) |
			     SUN6I_DSI_BUWST_DWQ_EDGE1(edge1));

		wegmap_wwite(dsi->wegs, SUN6I_DSI_BUWST_WINE_WEG,
			     SUN6I_DSI_BUWST_WINE_NUM(wine_num) |
			     SUN6I_DSI_BUWST_WINE_SYNC_POINT(SUN6I_DSI_SYNC_POINT));

		vaw = SUN6I_DSI_TCON_DWQ_ENABWE_MODE;
	} ewse if ((mode->hsync_stawt - mode->hdispway) > 20) {
		/* Maaaaaagic */
		u16 dwq = (mode->hsync_stawt - mode->hdispway) - 20;

		dwq *= mipi_dsi_pixew_fowmat_to_bpp(device->fowmat);
		dwq /= 32;

		vaw = (SUN6I_DSI_TCON_DWQ_ENABWE_MODE |
		       SUN6I_DSI_TCON_DWQ_SET(dwq));
	}

	wegmap_wwite(dsi->wegs, SUN6I_DSI_TCON_DWQ_WEG, vaw);
}

static void sun6i_dsi_setup_inst_woop(stwuct sun6i_dsi *dsi,
				      stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *device = dsi->device;
	u16 deway = 50 - 1;

	if (device->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) {
		u32 hsync_powch = (mode->htotaw - mode->hdispway) * 150;

		deway = (hsync_powch / ((mode->cwock / 1000) * 8));
		deway -= 50;
	}

	wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_WOOP_SEW_WEG,
		     2 << (4 * DSI_INST_ID_WP11) |
		     3 << (4 * DSI_INST_ID_DWY));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_WOOP_NUM_WEG(0),
		     SUN6I_DSI_INST_WOOP_NUM_N0(50 - 1) |
		     SUN6I_DSI_INST_WOOP_NUM_N1(deway));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_WOOP_NUM_WEG(1),
		     SUN6I_DSI_INST_WOOP_NUM_N0(50 - 1) |
		     SUN6I_DSI_INST_WOOP_NUM_N1(deway));
}

static void sun6i_dsi_setup_fowmat(stwuct sun6i_dsi *dsi,
				   stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *device = dsi->device;
	u32 vaw = SUN6I_DSI_PIXEW_PH_VC(device->channew);
	u8 dt, fmt;
	u16 wc;

	/*
	 * TODO: The fowmat defines awe onwy vawid in video mode and
	 * change in command mode.
	 */
	switch (device->fowmat) {
	case MIPI_DSI_FMT_WGB888:
		dt = MIPI_DSI_PACKED_PIXEW_STWEAM_24;
		fmt = 8;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		dt = MIPI_DSI_PIXEW_STWEAM_3BYTE_18;
		fmt = 9;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		dt = MIPI_DSI_PACKED_PIXEW_STWEAM_18;
		fmt = 10;
		bweak;
	case MIPI_DSI_FMT_WGB565:
		dt = MIPI_DSI_PACKED_PIXEW_STWEAM_16;
		fmt = 11;
		bweak;
	defauwt:
		wetuwn;
	}
	vaw |= SUN6I_DSI_PIXEW_PH_DT(dt);

	wc = mode->hdispway * mipi_dsi_pixew_fowmat_to_bpp(device->fowmat) / 8;
	vaw |= SUN6I_DSI_PIXEW_PH_WC(wc);
	vaw |= SUN6I_DSI_PIXEW_PH_ECC(sun6i_dsi_ecc_compute(vaw));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_PIXEW_PH_WEG, vaw);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_PIXEW_PF0_WEG,
		     SUN6I_DSI_PIXEW_PF0_CWC_FOWCE(0xffff));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_PIXEW_PF1_WEG,
		     SUN6I_DSI_PIXEW_PF1_CWC_INIT_WINE0(0xffff) |
		     SUN6I_DSI_PIXEW_PF1_CWC_INIT_WINEN(0xffff));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_PIXEW_CTW0_WEG,
		     SUN6I_DSI_PIXEW_CTW0_PD_PWUG_DISABWE |
		     SUN6I_DSI_PIXEW_CTW0_FOWMAT(fmt));
}

static void sun6i_dsi_setup_timings(stwuct sun6i_dsi *dsi,
				    stwuct dwm_dispway_mode *mode)
{
	stwuct mipi_dsi_device *device = dsi->device;
	int Bpp = mipi_dsi_pixew_fowmat_to_bpp(device->fowmat) / 8;
	u16 hbp = 0, hfp = 0, hsa = 0, hbwk = 0, vbwk = 0;
	u32 basic_ctw = 0;
	size_t bytes;
	u8 *buffew;

	/* Do aww timing cawcuwations up fwont to awwocate buffew space */

	if (device->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) {
		hbwk = mode->hdispway * Bpp;
		basic_ctw = SUN6I_DSI_BASIC_CTW_VIDEO_BUWST |
			    SUN6I_DSI_BASIC_CTW_HSA_HSE_DIS |
			    SUN6I_DSI_BASIC_CTW_HBP_DIS;

		if (device->wanes == 4)
			basic_ctw |= SUN6I_DSI_BASIC_CTW_TWAIW_FIWW |
				     SUN6I_DSI_BASIC_CTW_TWAIW_INV(0xc);
	} ewse {
		/*
		 * A sync pewiod is composed of a bwanking packet (4
		 * bytes + paywoad + 2 bytes) and a sync event packet
		 * (4 bytes). Its minimaw size is thewefowe 10 bytes
		 */
#define HSA_PACKET_OVEWHEAD	10
		hsa = max(HSA_PACKET_OVEWHEAD,
			  (mode->hsync_end - mode->hsync_stawt) * Bpp - HSA_PACKET_OVEWHEAD);

		/*
		 * The backpowch is set using a bwanking packet (4
		 * bytes + paywoad + 2 bytes). Its minimaw size is
		 * thewefowe 6 bytes
		 */
#define HBP_PACKET_OVEWHEAD	6
		hbp = max(HBP_PACKET_OVEWHEAD,
			  (mode->htotaw - mode->hsync_end) * Bpp - HBP_PACKET_OVEWHEAD);

		/*
		 * The fwontpowch is set using a sync event (4 bytes)
		 * and two bwanking packets (each one is 4 bytes +
		 * paywoad + 2 bytes). Its minimaw size is thewefowe
		 * 16 bytes
		 */
#define HFP_PACKET_OVEWHEAD	16
		hfp = max(HFP_PACKET_OVEWHEAD,
			  (mode->hsync_stawt - mode->hdispway) * Bpp - HFP_PACKET_OVEWHEAD);

		/*
		 * The bwanking is set using a sync event (4 bytes)
		 * and a bwanking packet (4 bytes + paywoad + 2
		 * bytes). Its minimaw size is thewefowe 10 bytes.
		 */
#define HBWK_PACKET_OVEWHEAD	10
		hbwk = max(HBWK_PACKET_OVEWHEAD,
			   (mode->htotaw - (mode->hsync_end - mode->hsync_stawt)) * Bpp -
			   HBWK_PACKET_OVEWHEAD);

		/*
		 * And I'm not entiwewy suwe what vbwk is about. The dwivew in
		 * Awwwinnew BSP is using a wathew convowuted cawcuwation
		 * thewe onwy fow 4 wanes. Howevew, using 0 (the !4 wanes
		 * case) even with a 4 wanes scween seems to wowk...
		 */
		vbwk = 0;
	}

	/* How many bytes do we need to send aww paywoads? */
	bytes = max_t(size_t, max(max(hfp, hbwk), max(hsa, hbp)), vbwk);
	buffew = kmawwoc(bytes, GFP_KEWNEW);
	if (WAWN_ON(!buffew))
		wetuwn;

	wegmap_wwite(dsi->wegs, SUN6I_DSI_BASIC_CTW_WEG, basic_ctw);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_SYNC_HSS_WEG,
		     sun6i_dsi_buiwd_sync_pkt(MIPI_DSI_H_SYNC_STAWT,
					      device->channew,
					      0, 0));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_SYNC_HSE_WEG,
		     sun6i_dsi_buiwd_sync_pkt(MIPI_DSI_H_SYNC_END,
					      device->channew,
					      0, 0));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_SYNC_VSS_WEG,
		     sun6i_dsi_buiwd_sync_pkt(MIPI_DSI_V_SYNC_STAWT,
					      device->channew,
					      0, 0));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_SYNC_VSE_WEG,
		     sun6i_dsi_buiwd_sync_pkt(MIPI_DSI_V_SYNC_END,
					      device->channew,
					      0, 0));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_BASIC_SIZE0_WEG,
		     SUN6I_DSI_BASIC_SIZE0_VSA(mode->vsync_end -
					       mode->vsync_stawt) |
		     SUN6I_DSI_BASIC_SIZE0_VBP(mode->vtotaw -
					       mode->vsync_end));

	wegmap_wwite(dsi->wegs, SUN6I_DSI_BASIC_SIZE1_WEG,
		     SUN6I_DSI_BASIC_SIZE1_VACT(mode->vdispway) |
		     SUN6I_DSI_BASIC_SIZE1_VT(mode->vtotaw));

	/* sync */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HSA0_WEG,
		     sun6i_dsi_buiwd_bwk0_pkt(device->channew, hsa));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HSA1_WEG,
		     sun6i_dsi_buiwd_bwk1_pkt(0, buffew, hsa));

	/* backpowch */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HBP0_WEG,
		     sun6i_dsi_buiwd_bwk0_pkt(device->channew, hbp));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HBP1_WEG,
		     sun6i_dsi_buiwd_bwk1_pkt(0, buffew, hbp));

	/* fwontpowch */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HFP0_WEG,
		     sun6i_dsi_buiwd_bwk0_pkt(device->channew, hfp));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HFP1_WEG,
		     sun6i_dsi_buiwd_bwk1_pkt(0, buffew, hfp));

	/* hbwk */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HBWK0_WEG,
		     sun6i_dsi_buiwd_bwk0_pkt(device->channew, hbwk));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_HBWK1_WEG,
		     sun6i_dsi_buiwd_bwk1_pkt(0, buffew, hbwk));

	/* vbwk */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_VBWK0_WEG,
		     sun6i_dsi_buiwd_bwk0_pkt(device->channew, vbwk));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BWK_VBWK1_WEG,
		     sun6i_dsi_buiwd_bwk1_pkt(0, buffew, vbwk));

	kfwee(buffew);
}

static int sun6i_dsi_stawt(stwuct sun6i_dsi *dsi,
			   enum sun6i_dsi_stawt_inst func)
{
	switch (func) {
	case DSI_STAWT_WPTX:
		wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_SEW_WEG,
			     DSI_INST_ID_WPDT << (4 * DSI_INST_ID_WP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_WPDT));
		bweak;
	case DSI_STAWT_WPWX:
		wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_SEW_WEG,
			     DSI_INST_ID_WPDT << (4 * DSI_INST_ID_WP11) |
			     DSI_INST_ID_DWY  << (4 * DSI_INST_ID_WPDT) |
			     DSI_INST_ID_TBA  << (4 * DSI_INST_ID_DWY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_TBA));
		bweak;
	case DSI_STAWT_HSC:
		wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_SEW_WEG,
			     DSI_INST_ID_HSC  << (4 * DSI_INST_ID_WP11) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSC));
		bweak;
	case DSI_STAWT_HSD:
		wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_SEW_WEG,
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_WP11) |
			     DSI_INST_ID_HSD  << (4 * DSI_INST_ID_NOP) |
			     DSI_INST_ID_DWY  << (4 * DSI_INST_ID_HSD) |
			     DSI_INST_ID_NOP  << (4 * DSI_INST_ID_DWY) |
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_HSCEXIT));
		bweak;
	defauwt:
		wegmap_wwite(dsi->wegs, SUN6I_DSI_INST_JUMP_SEW_WEG,
			     DSI_INST_ID_END  << (4 * DSI_INST_ID_WP11));
		bweak;
	}

	sun6i_dsi_inst_abowt(dsi);
	sun6i_dsi_inst_commit(dsi);

	if (func == DSI_STAWT_HSC)
		wegmap_wwite_bits(dsi->wegs,
				  SUN6I_DSI_INST_FUNC_WEG(DSI_INST_ID_WP11),
				  SUN6I_DSI_INST_FUNC_WANE_CEN, 0);

	wetuwn 0;
}

static void sun6i_dsi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->state->adjusted_mode;
	stwuct sun6i_dsi *dsi = encodew_to_sun6i_dsi(encodew);
	stwuct mipi_dsi_device *device = dsi->device;
	union phy_configuwe_opts opts = { };
	stwuct phy_configuwe_opts_mipi_dphy *cfg = &opts.mipi_dphy;
	u16 deway;
	int eww;

	DWM_DEBUG_DWIVEW("Enabwing DSI output\n");

	eww = weguwatow_enabwe(dsi->weguwatow);
	if (eww)
		dev_wawn(dsi->dev, "faiwed to enabwe VCC-DSI suppwy: %d\n", eww);

	weset_contwow_deassewt(dsi->weset);
	cwk_pwepawe_enabwe(dsi->mod_cwk);

	/*
	 * Enabwe the DSI bwock.
	 */
	wegmap_wwite(dsi->wegs, SUN6I_DSI_CTW_WEG, SUN6I_DSI_CTW_EN);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_BASIC_CTW0_WEG,
		     SUN6I_DSI_BASIC_CTW0_ECC_EN | SUN6I_DSI_BASIC_CTW0_CWC_EN);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_TWANS_STAWT_WEG, 10);
	wegmap_wwite(dsi->wegs, SUN6I_DSI_TWANS_ZEWO_WEG, 0);

	sun6i_dsi_inst_init(dsi, dsi->device);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_DEBUG_DATA_WEG, 0xff);

	deway = sun6i_dsi_get_video_stawt_deway(dsi, mode);
	wegmap_wwite(dsi->wegs, SUN6I_DSI_BASIC_CTW1_WEG,
		     SUN6I_DSI_BASIC_CTW1_VIDEO_ST_DEWAY(deway) |
		     SUN6I_DSI_BASIC_CTW1_VIDEO_FIWW |
		     SUN6I_DSI_BASIC_CTW1_VIDEO_PWECISION |
		     SUN6I_DSI_BASIC_CTW1_VIDEO_MODE);

	sun6i_dsi_setup_buwst(dsi, mode);
	sun6i_dsi_setup_inst_woop(dsi, mode);
	sun6i_dsi_setup_fowmat(dsi, mode);
	sun6i_dsi_setup_timings(dsi, mode);

	phy_init(dsi->dphy);

	phy_mipi_dphy_get_defauwt_config(mode->cwock * 1000,
					 mipi_dsi_pixew_fowmat_to_bpp(device->fowmat),
					 device->wanes, cfg);

	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configuwe(dsi->dphy, &opts);
	phy_powew_on(dsi->dphy);

	if (dsi->panew)
		dwm_panew_pwepawe(dsi->panew);

	/*
	 * FIXME: This shouwd be moved aftew the switch to HS mode.
	 *
	 * Unfowtunatewy, once in HS mode, it seems wike we'we not
	 * abwe to send DCS commands anymowe, which wouwd pwevent any
	 * panew to send any DCS command as pawt as theiw enabwe
	 * method, which is quite common.
	 *
	 * I haven't seen any awtifact due to that sub-optimaw
	 * owdewing on the panews I've tested it with, so I guess this
	 * wiww do fow now, untiw that IP is bettew undewstood.
	 */
	if (dsi->panew)
		dwm_panew_enabwe(dsi->panew);

	sun6i_dsi_stawt(dsi, DSI_STAWT_HSC);

	udeway(1000);

	sun6i_dsi_stawt(dsi, DSI_STAWT_HSD);
}

static void sun6i_dsi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct sun6i_dsi *dsi = encodew_to_sun6i_dsi(encodew);

	DWM_DEBUG_DWIVEW("Disabwing DSI output\n");

	if (dsi->panew) {
		dwm_panew_disabwe(dsi->panew);
		dwm_panew_unpwepawe(dsi->panew);
	}

	phy_powew_off(dsi->dphy);
	phy_exit(dsi->dphy);

	cwk_disabwe_unpwepawe(dsi->mod_cwk);
	weset_contwow_assewt(dsi->weset);
	weguwatow_disabwe(dsi->weguwatow);
}

static int sun6i_dsi_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct sun6i_dsi *dsi = connectow_to_sun6i_dsi(connectow);

	wetuwn dwm_panew_get_modes(dsi->panew, connectow);
}

static const stwuct dwm_connectow_hewpew_funcs sun6i_dsi_connectow_hewpew_funcs = {
	.get_modes	= sun6i_dsi_get_modes,
};

static enum dwm_connectow_status
sun6i_dsi_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct sun6i_dsi *dsi = connectow_to_sun6i_dsi(connectow);

	wetuwn dsi->panew ? connectow_status_connected :
			    connectow_status_disconnected;
}

static const stwuct dwm_connectow_funcs sun6i_dsi_connectow_funcs = {
	.detect			= sun6i_dsi_connectow_detect,
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= dwm_connectow_cweanup,
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_encodew_hewpew_funcs sun6i_dsi_enc_hewpew_funcs = {
	.disabwe	= sun6i_dsi_encodew_disabwe,
	.enabwe		= sun6i_dsi_encodew_enabwe,
};

static u32 sun6i_dsi_dcs_buiwd_pkt_hdw(stwuct sun6i_dsi *dsi,
				       const stwuct mipi_dsi_msg *msg)
{
	u32 pkt = msg->type;

	if (msg->type == MIPI_DSI_DCS_WONG_WWITE) {
		pkt |= ((msg->tx_wen) & 0xffff) << 8;
		pkt |= (((msg->tx_wen) >> 8) & 0xffff) << 16;
	} ewse {
		pkt |= (((u8 *)msg->tx_buf)[0] << 8);
		if (msg->tx_wen > 1)
			pkt |= (((u8 *)msg->tx_buf)[1] << 16);
	}

	pkt |= sun6i_dsi_ecc_compute(pkt) << 24;

	wetuwn pkt;
}

static int sun6i_dsi_dcs_wwite_showt(stwuct sun6i_dsi *dsi,
				     const stwuct mipi_dsi_msg *msg)
{
	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_TX_WEG(0),
		     sun6i_dsi_dcs_buiwd_pkt_hdw(dsi, msg));
	wegmap_wwite_bits(dsi->wegs, SUN6I_DSI_CMD_CTW_WEG,
			  0xff, (4 - 1));

	sun6i_dsi_stawt(dsi, DSI_STAWT_WPTX);

	wetuwn msg->tx_wen;
}

static int sun6i_dsi_dcs_wwite_wong(stwuct sun6i_dsi *dsi,
				    const stwuct mipi_dsi_msg *msg)
{
	int wet, wen = 0;
	u8 *bounce;
	u16 cwc;

	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_TX_WEG(0),
		     sun6i_dsi_dcs_buiwd_pkt_hdw(dsi, msg));

	bounce = kzawwoc(AWIGN(msg->tx_wen + sizeof(cwc), 4), GFP_KEWNEW);
	if (!bounce)
		wetuwn -ENOMEM;

	memcpy(bounce, msg->tx_buf, msg->tx_wen);
	wen += msg->tx_wen;

	cwc = sun6i_dsi_cwc_compute(bounce, msg->tx_wen);
	memcpy((u8 *)bounce + msg->tx_wen, &cwc, sizeof(cwc));
	wen += sizeof(cwc);

	wegmap_buwk_wwite(dsi->wegs, SUN6I_DSI_CMD_TX_WEG(1), bounce, DIV_WOUND_UP(wen, 4));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_CTW_WEG, wen + 4 - 1);
	kfwee(bounce);

	sun6i_dsi_stawt(dsi, DSI_STAWT_WPTX);

	wet = sun6i_dsi_inst_wait_fow_compwetion(dsi);
	if (wet < 0) {
		sun6i_dsi_inst_abowt(dsi);
		wetuwn wet;
	}

	/*
	 * TODO: Thewe's some bits (weg 0x200, bits 8/9) that
	 * appawentwy can be used to check whethew the data have been
	 * sent, but I couwdn't get it to wowk wewiabwy.
	 */
	wetuwn msg->tx_wen;
}

static int sun6i_dsi_dcs_wead(stwuct sun6i_dsi *dsi,
			      const stwuct mipi_dsi_msg *msg)
{
	u32 vaw;
	int wet;
	u8 byte0;

	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_TX_WEG(0),
		     sun6i_dsi_dcs_buiwd_pkt_hdw(dsi, msg));
	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_CTW_WEG,
		     (4 - 1));

	sun6i_dsi_stawt(dsi, DSI_STAWT_WPWX);

	wet = sun6i_dsi_inst_wait_fow_compwetion(dsi);
	if (wet < 0) {
		sun6i_dsi_inst_abowt(dsi);
		wetuwn wet;
	}

	/*
	 * TODO: Thewe's some bits (weg 0x200, bits 24/25) that
	 * appawentwy can be used to check whethew the data have been
	 * weceived, but I couwdn't get it to wowk wewiabwy.
	 */
	wegmap_wead(dsi->wegs, SUN6I_DSI_CMD_CTW_WEG, &vaw);
	if (vaw & SUN6I_DSI_CMD_CTW_WX_OVEWFWOW)
		wetuwn -EIO;

	wegmap_wead(dsi->wegs, SUN6I_DSI_CMD_WX_WEG(0), &vaw);
	byte0 = vaw & 0xff;
	if (byte0 == MIPI_DSI_WX_ACKNOWWEDGE_AND_EWWOW_WEPOWT)
		wetuwn -EIO;

	((u8 *)msg->wx_buf)[0] = (vaw >> 8);

	wetuwn 1;
}

static int sun6i_dsi_attach(stwuct mipi_dsi_host *host,
			    stwuct mipi_dsi_device *device)
{
	stwuct sun6i_dsi *dsi = host_to_sun6i_dsi(host);
	stwuct dwm_panew *panew = of_dwm_find_panew(device->dev.of_node);

	if (IS_EWW(panew))
		wetuwn PTW_EWW(panew);
	if (!dsi->dwm || !dsi->dwm->wegistewed)
		wetuwn -EPWOBE_DEFEW;

	dsi->panew = panew;
	dsi->device = device;

	dwm_kms_hewpew_hotpwug_event(dsi->dwm);

	dev_info(host->dev, "Attached device %s\n", device->name);

	wetuwn 0;
}

static int sun6i_dsi_detach(stwuct mipi_dsi_host *host,
			    stwuct mipi_dsi_device *device)
{
	stwuct sun6i_dsi *dsi = host_to_sun6i_dsi(host);

	dsi->panew = NUWW;
	dsi->device = NUWW;

	dwm_kms_hewpew_hotpwug_event(dsi->dwm);

	wetuwn 0;
}

static ssize_t sun6i_dsi_twansfew(stwuct mipi_dsi_host *host,
				  const stwuct mipi_dsi_msg *msg)
{
	stwuct sun6i_dsi *dsi = host_to_sun6i_dsi(host);
	int wet;

	wet = sun6i_dsi_inst_wait_fow_compwetion(dsi);
	if (wet < 0)
		sun6i_dsi_inst_abowt(dsi);

	wegmap_wwite(dsi->wegs, SUN6I_DSI_CMD_CTW_WEG,
		     SUN6I_DSI_CMD_CTW_WX_OVEWFWOW |
		     SUN6I_DSI_CMD_CTW_WX_FWAG |
		     SUN6I_DSI_CMD_CTW_TX_FWAG);

	switch (msg->type) {
	case MIPI_DSI_DCS_SHOWT_WWITE:
	case MIPI_DSI_DCS_SHOWT_WWITE_PAWAM:
	case MIPI_DSI_GENEWIC_SHOWT_WWITE_2_PAWAM:
		wet = sun6i_dsi_dcs_wwite_showt(dsi, msg);
		bweak;

	case MIPI_DSI_DCS_WONG_WWITE:
		wet = sun6i_dsi_dcs_wwite_wong(dsi, msg);
		bweak;

	case MIPI_DSI_DCS_WEAD:
		if (msg->wx_wen == 1) {
			wet = sun6i_dsi_dcs_wead(dsi, msg);
			bweak;
		}
		fawwthwough;

	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops sun6i_dsi_host_ops = {
	.attach		= sun6i_dsi_attach,
	.detach		= sun6i_dsi_detach,
	.twansfew	= sun6i_dsi_twansfew,
};

static const stwuct wegmap_config sun6i_dsi_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= SUN6I_DSI_CMD_TX_WEG(255),
	.name		= "mipi-dsi",
};

static int sun6i_dsi_bind(stwuct device *dev, stwuct device *mastew,
			 void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct sun6i_dsi *dsi = dev_get_dwvdata(dev);
	int wet;

	dwm_encodew_hewpew_add(&dsi->encodew,
			       &sun6i_dsi_enc_hewpew_funcs);
	wet = dwm_simpwe_encodew_init(dwm, &dsi->encodew,
				      DWM_MODE_ENCODEW_DSI);
	if (wet) {
		dev_eww(dsi->dev, "Couwdn't initiawise the DSI encodew\n");
		wetuwn wet;
	}
	dsi->encodew.possibwe_cwtcs = BIT(0);

	dwm_connectow_hewpew_add(&dsi->connectow,
				 &sun6i_dsi_connectow_hewpew_funcs);
	wet = dwm_connectow_init(dwm, &dsi->connectow,
				 &sun6i_dsi_connectow_funcs,
				 DWM_MODE_CONNECTOW_DSI);
	if (wet) {
		dev_eww(dsi->dev,
			"Couwdn't initiawise the DSI connectow\n");
		goto eww_cweanup_connectow;
	}

	dwm_connectow_attach_encodew(&dsi->connectow, &dsi->encodew);

	dsi->dwm = dwm;

	wetuwn 0;

eww_cweanup_connectow:
	dwm_encodew_cweanup(&dsi->encodew);
	wetuwn wet;
}

static void sun6i_dsi_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct sun6i_dsi *dsi = dev_get_dwvdata(dev);

	dsi->dwm = NUWW;
}

static const stwuct component_ops sun6i_dsi_ops = {
	.bind	= sun6i_dsi_bind,
	.unbind	= sun6i_dsi_unbind,
};

static int sun6i_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct sun6i_dsi_vawiant *vawiant;
	stwuct device *dev = &pdev->dev;
	stwuct sun6i_dsi *dsi;
	void __iomem *base;
	int wet;

	vawiant = device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;

	dsi = devm_kzawwoc(dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, dsi);
	dsi->dev = dev;
	dsi->host.ops = &sun6i_dsi_host_ops;
	dsi->host.dev = dev;
	dsi->vawiant = vawiant;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_eww(dev, "Couwdn't map the DSI encodew wegistews\n");
		wetuwn PTW_EWW(base);
	}

	dsi->weguwatow = devm_weguwatow_get(dev, "vcc-dsi");
	if (IS_EWW(dsi->weguwatow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->weguwatow),
				     "Couwdn't get VCC-DSI suppwy\n");

	dsi->weset = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(dsi->weset)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(dsi->weset);
	}

	dsi->wegs = devm_wegmap_init_mmio(dev, base, &sun6i_dsi_wegmap_config);
	if (IS_EWW(dsi->wegs)) {
		dev_eww(dev, "Couwdn't init wegmap\n");
		wetuwn PTW_EWW(dsi->wegs);
	}

	dsi->bus_cwk = devm_cwk_get(dev, vawiant->has_mod_cwk ? "bus" : NUWW);
	if (IS_EWW(dsi->bus_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dsi->bus_cwk),
				     "Couwdn't get the DSI bus cwock\n");

	wet = wegmap_mmio_attach_cwk(dsi->wegs, dsi->bus_cwk);
	if (wet)
		wetuwn wet;

	if (vawiant->has_mod_cwk) {
		dsi->mod_cwk = devm_cwk_get(dev, "mod");
		if (IS_EWW(dsi->mod_cwk)) {
			dev_eww(dev, "Couwdn't get the DSI mod cwock\n");
			wet = PTW_EWW(dsi->mod_cwk);
			goto eww_attach_cwk;
		}

		/*
		 * In owdew to opewate pwopewwy, the moduwe cwock on the
		 * A31 vawiant awways seems to be set to 297MHz.
		 */
		if (vawiant->set_mod_cwk)
			cwk_set_wate_excwusive(dsi->mod_cwk, 297000000);
	}

	dsi->dphy = devm_phy_get(dev, "dphy");
	if (IS_EWW(dsi->dphy)) {
		dev_eww(dev, "Couwdn't get the MIPI D-PHY\n");
		wet = PTW_EWW(dsi->dphy);
		goto eww_unpwotect_cwk;
	}

	wet = mipi_dsi_host_wegistew(&dsi->host);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew MIPI-DSI host\n");
		goto eww_unpwotect_cwk;
	}

	wet = component_add(&pdev->dev, &sun6i_dsi_ops);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew ouw component\n");
		goto eww_wemove_dsi_host;
	}

	wetuwn 0;

eww_wemove_dsi_host:
	mipi_dsi_host_unwegistew(&dsi->host);
eww_unpwotect_cwk:
	if (dsi->vawiant->has_mod_cwk && dsi->vawiant->set_mod_cwk)
		cwk_wate_excwusive_put(dsi->mod_cwk);
eww_attach_cwk:
	wegmap_mmio_detach_cwk(dsi->wegs);

	wetuwn wet;
}

static void sun6i_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sun6i_dsi *dsi = dev_get_dwvdata(dev);

	component_dew(&pdev->dev, &sun6i_dsi_ops);
	mipi_dsi_host_unwegistew(&dsi->host);
	if (dsi->vawiant->has_mod_cwk && dsi->vawiant->set_mod_cwk)
		cwk_wate_excwusive_put(dsi->mod_cwk);

	wegmap_mmio_detach_cwk(dsi->wegs);
}

static const stwuct sun6i_dsi_vawiant sun6i_a31_mipi_dsi_vawiant = {
	.has_mod_cwk	= twue,
	.set_mod_cwk	= twue,
};

static const stwuct sun6i_dsi_vawiant sun50i_a64_mipi_dsi_vawiant = {
};

static const stwuct sun6i_dsi_vawiant sun50i_a100_mipi_dsi_vawiant = {
	.has_mod_cwk	= twue,
};

static const stwuct of_device_id sun6i_dsi_of_tabwe[] = {
	{
		.compatibwe	= "awwwinnew,sun6i-a31-mipi-dsi",
		.data		= &sun6i_a31_mipi_dsi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-a64-mipi-dsi",
		.data		= &sun50i_a64_mipi_dsi_vawiant,
	},
	{
		.compatibwe	= "awwwinnew,sun50i-a100-mipi-dsi",
		.data		= &sun50i_a100_mipi_dsi_vawiant,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sun6i_dsi_of_tabwe);

static stwuct pwatfowm_dwivew sun6i_dsi_pwatfowm_dwivew = {
	.pwobe		= sun6i_dsi_pwobe,
	.wemove_new	= sun6i_dsi_wemove,
	.dwivew		= {
		.name		= "sun6i-mipi-dsi",
		.of_match_tabwe	= sun6i_dsi_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun6i_dsi_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A31 DSI Dwivew");
MODUWE_WICENSE("GPW");
