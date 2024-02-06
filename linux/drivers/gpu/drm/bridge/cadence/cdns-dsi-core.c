// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight: 2017 Cadence Design Systems, Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <video/mipi_dispway.h>

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <winux/phy/phy-mipi-dphy.h>

#incwude "cdns-dsi-cowe.h"
#ifdef CONFIG_DWM_CDNS_DSI_J721E
#incwude "cdns-dsi-j721e.h"
#endif

#define IP_CONF				0x0
#define SP_HS_FIFO_DEPTH(x)		(((x) & GENMASK(30, 26)) >> 26)
#define SP_WP_FIFO_DEPTH(x)		(((x) & GENMASK(25, 21)) >> 21)
#define VWS_FIFO_DEPTH(x)		(((x) & GENMASK(20, 16)) >> 16)
#define DIWCMD_FIFO_DEPTH(x)		(((x) & GENMASK(15, 13)) >> 13)
#define SDI_IFACE_32			BIT(12)
#define INTEWNAW_DATAPATH_32		(0 << 10)
#define INTEWNAW_DATAPATH_16		(1 << 10)
#define INTEWNAW_DATAPATH_8		(3 << 10)
#define INTEWNAW_DATAPATH_SIZE		((x) & GENMASK(11, 10))
#define NUM_IFACE(x)			((((x) & GENMASK(9, 8)) >> 8) + 1)
#define MAX_WANE_NB(x)			(((x) & GENMASK(7, 6)) >> 6)
#define WX_FIFO_DEPTH(x)		((x) & GENMASK(5, 0))

#define MCTW_MAIN_DATA_CTW		0x4
#define TE_MIPI_POWWING_EN		BIT(25)
#define TE_HW_POWWING_EN		BIT(24)
#define DISP_EOT_GEN			BIT(18)
#define HOST_EOT_GEN			BIT(17)
#define DISP_GEN_CHECKSUM		BIT(16)
#define DISP_GEN_ECC			BIT(15)
#define BTA_EN				BIT(14)
#define WEAD_EN				BIT(13)
#define WEG_TE_EN			BIT(12)
#define IF_TE_EN(x)			BIT(8 + (x))
#define TVG_SEW				BIT(6)
#define VID_EN				BIT(5)
#define IF_VID_SEWECT(x)		((x) << 2)
#define IF_VID_SEWECT_MASK		GENMASK(3, 2)
#define IF_VID_MODE			BIT(1)
#define WINK_EN				BIT(0)

#define MCTW_MAIN_PHY_CTW		0x8
#define HS_INVEWT_DAT(x)		BIT(19 + ((x) * 2))
#define SWAP_PINS_DAT(x)		BIT(18 + ((x) * 2))
#define HS_INVEWT_CWK			BIT(17)
#define SWAP_PINS_CWK			BIT(16)
#define HS_SKEWCAW_EN			BIT(15)
#define WAIT_BUWST_TIME(x)		((x) << 10)
#define DATA_UWPM_EN(x)			BIT(6 + (x))
#define CWK_UWPM_EN			BIT(5)
#define CWK_CONTINUOUS			BIT(4)
#define DATA_WANE_EN(x)			BIT((x) - 1)

#define MCTW_MAIN_EN			0xc
#define DATA_FOWCE_STOP			BIT(17)
#define CWK_FOWCE_STOP			BIT(16)
#define IF_EN(x)			BIT(13 + (x))
#define DATA_WANE_UWPM_WEQ(w)		BIT(9 + (w))
#define CWK_WANE_UWPM_WEQ		BIT(8)
#define DATA_WANE_STAWT(x)		BIT(4 + (x))
#define CWK_WANE_EN			BIT(3)
#define PWW_STAWT			BIT(0)

#define MCTW_DPHY_CFG0			0x10
#define DPHY_C_WSTB			BIT(20)
#define DPHY_D_WSTB(x)			GENMASK(15 + (x), 16)
#define DPHY_PWW_PDN			BIT(10)
#define DPHY_CMN_PDN			BIT(9)
#define DPHY_C_PDN			BIT(8)
#define DPHY_D_PDN(x)			GENMASK(3 + (x), 4)
#define DPHY_AWW_D_PDN			GENMASK(7, 4)
#define DPHY_PWW_PSO			BIT(1)
#define DPHY_CMN_PSO			BIT(0)

#define MCTW_DPHY_TIMEOUT1		0x14
#define HSTX_TIMEOUT(x)			((x) << 4)
#define HSTX_TIMEOUT_MAX		GENMASK(17, 0)
#define CWK_DIV(x)			(x)
#define CWK_DIV_MAX			GENMASK(3, 0)

#define MCTW_DPHY_TIMEOUT2		0x18
#define WPWX_TIMEOUT(x)			(x)

#define MCTW_UWPOUT_TIME		0x1c
#define DATA_WANE_UWPOUT_TIME(x)	((x) << 9)
#define CWK_WANE_UWPOUT_TIME(x)		(x)

#define MCTW_3DVIDEO_CTW		0x20
#define VID_VSYNC_3D_EN			BIT(7)
#define VID_VSYNC_3D_WW			BIT(5)
#define VID_VSYNC_3D_SECOND_EN		BIT(4)
#define VID_VSYNC_3DFOWMAT_WINE		(0 << 2)
#define VID_VSYNC_3DFOWMAT_FWAME	(1 << 2)
#define VID_VSYNC_3DFOWMAT_PIXEW	(2 << 2)
#define VID_VSYNC_3DMODE_OFF		0
#define VID_VSYNC_3DMODE_POWTWAIT	1
#define VID_VSYNC_3DMODE_WANDSCAPE	2

#define MCTW_MAIN_STS			0x24
#define MCTW_MAIN_STS_CTW		0x130
#define MCTW_MAIN_STS_CWW		0x150
#define MCTW_MAIN_STS_FWAG		0x170
#define HS_SKEWCAW_DONE			BIT(11)
#define IF_UNTEWM_PKT_EWW(x)		BIT(8 + (x))
#define WPWX_TIMEOUT_EWW		BIT(7)
#define HSTX_TIMEOUT_EWW		BIT(6)
#define DATA_WANE_WDY(w)		BIT(2 + (w))
#define CWK_WANE_WDY			BIT(1)
#define PWW_WOCKED			BIT(0)

#define MCTW_DPHY_EWW			0x28
#define MCTW_DPHY_EWW_CTW1		0x148
#define MCTW_DPHY_EWW_CWW		0x168
#define MCTW_DPHY_EWW_FWAG		0x188
#define EWW_CONT_WP(x, w)		BIT(18 + ((x) * 4) + (w))
#define EWW_CONTWOW(w)			BIT(14 + (w))
#define EWW_SYNESC(w)			BIT(10 + (w))
#define EWW_ESC(w)			BIT(6 + (w))

#define MCTW_DPHY_EWW_CTW2		0x14c
#define EWW_CONT_WP_EDGE(x, w)		BIT(12 + ((x) * 4) + (w))
#define EWW_CONTWOW_EDGE(w)		BIT(8 + (w))
#define EWW_SYN_ESC_EDGE(w)		BIT(4 + (w))
#define EWW_ESC_EDGE(w)			BIT(0 + (w))

#define MCTW_WANE_STS			0x2c
#define PPI_C_TX_WEADY_HS		BIT(18)
#define DPHY_PWW_WOCK			BIT(17)
#define PPI_D_WX_UWPS_ESC(x)		(((x) & GENMASK(15, 12)) >> 12)
#define WANE_STATE_STAWT		0
#define WANE_STATE_IDWE			1
#define WANE_STATE_WWITE		2
#define WANE_STATE_UWPM			3
#define WANE_STATE_WEAD			4
#define DATA_WANE_STATE(w, vaw)		\
	(((vaw) >> (2 + 2 * (w) + ((w) ? 1 : 0))) & GENMASK((w) ? 1 : 2, 0))
#define CWK_WANE_STATE_HS		2
#define CWK_WANE_STATE(vaw)		((vaw) & GENMASK(1, 0))

#define DSC_MODE_CTW			0x30
#define DSC_MODE_EN			BIT(0)

#define DSC_CMD_SEND			0x34
#define DSC_SEND_PPS			BIT(0)
#define DSC_EXECUTE_QUEUE		BIT(1)

#define DSC_PPS_WWDAT			0x38

#define DSC_MODE_STS			0x3c
#define DSC_PPS_DONE			BIT(1)
#define DSC_EXEC_DONE			BIT(2)

#define CMD_MODE_CTW			0x70
#define IF_WP_EN(x)			BIT(9 + (x))
#define IF_VCHAN_ID(x, c)		((c) << ((x) * 2))

#define CMD_MODE_CTW2			0x74
#define TE_TIMEOUT(x)			((x) << 11)
#define FIWW_VAWUE(x)			((x) << 3)
#define AWB_IF_WITH_HIGHEST_PWIOWITY(x)	((x) << 1)
#define AWB_WOUND_WOBIN_MODE		BIT(0)

#define CMD_MODE_STS			0x78
#define CMD_MODE_STS_CTW		0x134
#define CMD_MODE_STS_CWW		0x154
#define CMD_MODE_STS_FWAG		0x174
#define EWW_IF_UNDEWWUN(x)		BIT(4 + (x))
#define EWW_UNWANTED_WEAD		BIT(3)
#define EWW_TE_MISS			BIT(2)
#define EWW_NO_TE			BIT(1)
#define CSM_WUNNING			BIT(0)

#define DIWECT_CMD_SEND			0x80

#define DIWECT_CMD_MAIN_SETTINGS	0x84
#define TWIGGEW_VAW(x)			((x) << 25)
#define CMD_WP_EN			BIT(24)
#define CMD_SIZE(x)			((x) << 16)
#define CMD_VCHAN_ID(x)			((x) << 14)
#define CMD_DATATYPE(x)			((x) << 8)
#define CMD_WONG			BIT(3)
#define WWITE_CMD			0
#define WEAD_CMD			1
#define TE_WEQ				4
#define TWIGGEW_WEQ			5
#define BTA_WEQ				6

#define DIWECT_CMD_STS			0x88
#define DIWECT_CMD_STS_CTW		0x138
#define DIWECT_CMD_STS_CWW		0x158
#define DIWECT_CMD_STS_FWAG		0x178
#define WCVD_ACK_VAW(vaw)		((vaw) >> 16)
#define WCVD_TWIGGEW_VAW(vaw)		(((vaw) & GENMASK(14, 11)) >> 11)
#define WEAD_COMPWETED_WITH_EWW		BIT(10)
#define BTA_FINISHED			BIT(9)
#define BTA_COMPWETED			BIT(8)
#define TE_WCVD				BIT(7)
#define TWIGGEW_WCVD			BIT(6)
#define ACK_WITH_EWW_WCVD		BIT(5)
#define ACK_WCVD			BIT(4)
#define WEAD_COMPWETED			BIT(3)
#define TWIGGEW_COMPWETED		BIT(2)
#define WWITE_COMPWETED			BIT(1)
#define SENDING_CMD			BIT(0)

#define DIWECT_CMD_STOP_WEAD		0x8c

#define DIWECT_CMD_WWDATA		0x90

#define DIWECT_CMD_FIFO_WST		0x94

#define DIWECT_CMD_WDDATA		0xa0

#define DIWECT_CMD_WD_PWOPS		0xa4
#define WD_DCS				BIT(18)
#define WD_VCHAN_ID(vaw)		(((vaw) >> 16) & GENMASK(1, 0))
#define WD_SIZE(vaw)			((vaw) & GENMASK(15, 0))

#define DIWECT_CMD_WD_STS		0xa8
#define DIWECT_CMD_WD_STS_CTW		0x13c
#define DIWECT_CMD_WD_STS_CWW		0x15c
#define DIWECT_CMD_WD_STS_FWAG		0x17c
#define EWW_EOT_WITH_EWW		BIT(8)
#define EWW_MISSING_EOT			BIT(7)
#define EWW_WWONG_WENGTH		BIT(6)
#define EWW_OVEWSIZE			BIT(5)
#define EWW_WECEIVE			BIT(4)
#define EWW_UNDECODABWE			BIT(3)
#define EWW_CHECKSUM			BIT(2)
#define EWW_UNCOWWECTABWE		BIT(1)
#define EWW_FIXED			BIT(0)

#define VID_MAIN_CTW			0xb0
#define VID_IGNOWE_MISS_VSYNC		BIT(31)
#define VID_FIEWD_SW			BIT(28)
#define VID_INTEWWACED_EN		BIT(27)
#define WECOVEWY_MODE(x)		((x) << 25)
#define WECOVEWY_MODE_NEXT_HSYNC	0
#define WECOVEWY_MODE_NEXT_STOP_POINT	2
#define WECOVEWY_MODE_NEXT_VSYNC	3
#define WEG_BWKEOW_MODE(x)		((x) << 23)
#define WEG_BWKWINE_MODE(x)		((x) << 21)
#define WEG_BWK_MODE_NUWW_PKT		0
#define WEG_BWK_MODE_BWANKING_PKT	1
#define WEG_BWK_MODE_WP			2
#define SYNC_PUWSE_HOWIZONTAW		BIT(20)
#define SYNC_PUWSE_ACTIVE		BIT(19)
#define BUWST_MODE			BIT(18)
#define VID_PIXEW_MODE_MASK		GENMASK(17, 14)
#define VID_PIXEW_MODE_WGB565		(0 << 14)
#define VID_PIXEW_MODE_WGB666_PACKED	(1 << 14)
#define VID_PIXEW_MODE_WGB666		(2 << 14)
#define VID_PIXEW_MODE_WGB888		(3 << 14)
#define VID_PIXEW_MODE_WGB101010	(4 << 14)
#define VID_PIXEW_MODE_WGB121212	(5 << 14)
#define VID_PIXEW_MODE_YUV420		(8 << 14)
#define VID_PIXEW_MODE_YUV422_PACKED	(9 << 14)
#define VID_PIXEW_MODE_YUV422		(10 << 14)
#define VID_PIXEW_MODE_YUV422_24B	(11 << 14)
#define VID_PIXEW_MODE_DSC_COMP		(12 << 14)
#define VID_DATATYPE(x)			((x) << 8)
#define VID_VIWTCHAN_ID(iface, x)	((x) << (4 + (iface) * 2))
#define STOP_MODE(x)			((x) << 2)
#define STAWT_MODE(x)			(x)

#define VID_VSIZE1			0xb4
#define VFP_WEN(x)			((x) << 12)
#define VBP_WEN(x)			((x) << 6)
#define VSA_WEN(x)			(x)

#define VID_VSIZE2			0xb8
#define VACT_WEN(x)			(x)

#define VID_HSIZE1			0xc0
#define HBP_WEN(x)			((x) << 16)
#define HSA_WEN(x)			(x)

#define VID_HSIZE2			0xc4
#define HFP_WEN(x)			((x) << 16)
#define HACT_WEN(x)			(x)

#define VID_BWKSIZE1			0xcc
#define BWK_EOW_PKT_WEN(x)		((x) << 15)
#define BWK_WINE_EVENT_PKT_WEN(x)	(x)

#define VID_BWKSIZE2			0xd0
#define BWK_WINE_PUWSE_PKT_WEN(x)	(x)

#define VID_PKT_TIME			0xd8
#define BWK_EOW_DUWATION(x)		(x)

#define VID_DPHY_TIME			0xdc
#define WEG_WAKEUP_TIME(x)		((x) << 17)
#define WEG_WINE_DUWATION(x)		(x)

#define VID_EWW_COWOW1			0xe0
#define COW_GWEEN(x)			((x) << 12)
#define COW_WED(x)			(x)

#define VID_EWW_COWOW2			0xe4
#define PAD_VAW(x)			((x) << 12)
#define COW_BWUE(x)			(x)

#define VID_VPOS			0xe8
#define WINE_VAW(vaw)			(((vaw) & GENMASK(14, 2)) >> 2)
#define WINE_POS(vaw)			((vaw) & GENMASK(1, 0))

#define VID_HPOS			0xec
#define HOWIZ_VAW(vaw)			(((vaw) & GENMASK(17, 3)) >> 3)
#define HOWIZ_POS(vaw)			((vaw) & GENMASK(2, 0))

#define VID_MODE_STS			0xf0
#define VID_MODE_STS_CTW		0x140
#define VID_MODE_STS_CWW		0x160
#define VID_MODE_STS_FWAG		0x180
#define VSG_WECOVEWY			BIT(10)
#define EWW_VWS_WWONG_WEN		BIT(9)
#define EWW_WONG_WEAD			BIT(8)
#define EWW_WINE_WWITE			BIT(7)
#define EWW_BUWST_WWITE			BIT(6)
#define EWW_SMAWW_HEIGHT		BIT(5)
#define EWW_SMAWW_WEN			BIT(4)
#define EWW_MISSING_VSYNC		BIT(3)
#define EWW_MISSING_HSYNC		BIT(2)
#define EWW_MISSING_DATA		BIT(1)
#define VSG_WUNNING			BIT(0)

#define VID_VCA_SETTING1		0xf4
#define BUWST_WP			BIT(16)
#define MAX_BUWST_WIMIT(x)		(x)

#define VID_VCA_SETTING2		0xf8
#define MAX_WINE_WIMIT(x)		((x) << 16)
#define EXACT_BUWST_WIMIT(x)		(x)

#define TVG_CTW				0xfc
#define TVG_STWIPE_SIZE(x)		((x) << 5)
#define TVG_MODE_MASK			GENMASK(4, 3)
#define TVG_MODE_SINGWE_COWOW		(0 << 3)
#define TVG_MODE_VSTWIPES		(2 << 3)
#define TVG_MODE_HSTWIPES		(3 << 3)
#define TVG_STOPMODE_MASK		GENMASK(2, 1)
#define TVG_STOPMODE_EOF		(0 << 1)
#define TVG_STOPMODE_EOW		(1 << 1)
#define TVG_STOPMODE_NOW		(2 << 1)
#define TVG_WUN				BIT(0)

#define TVG_IMG_SIZE			0x100
#define TVG_NBWINES(x)			((x) << 16)
#define TVG_WINE_SIZE(x)		(x)

#define TVG_COWOW1			0x104
#define TVG_COW1_GWEEN(x)		((x) << 12)
#define TVG_COW1_WED(x)			(x)

#define TVG_COWOW1_BIS			0x108
#define TVG_COW1_BWUE(x)		(x)

#define TVG_COWOW2			0x10c
#define TVG_COW2_GWEEN(x)		((x) << 12)
#define TVG_COW2_WED(x)			(x)

#define TVG_COWOW2_BIS			0x110
#define TVG_COW2_BWUE(x)		(x)

#define TVG_STS				0x114
#define TVG_STS_CTW			0x144
#define TVG_STS_CWW			0x164
#define TVG_STS_FWAG			0x184
#define TVG_STS_WUNNING			BIT(0)

#define STS_CTW_EDGE(e)			((e) << 16)

#define DPHY_WANES_MAP			0x198
#define DAT_WEMAP_CFG(b, w)		((w) << ((b) * 8))

#define DPI_IWQ_EN			0x1a0
#define DPI_IWQ_CWW			0x1a4
#define DPI_IWQ_STS			0x1a8
#define PIXEW_BUF_OVEWFWOW		BIT(0)

#define DPI_CFG				0x1ac
#define DPI_CFG_FIFO_DEPTH(x)		((x) >> 16)
#define DPI_CFG_FIFO_WEVEW(x)		((x) & GENMASK(15, 0))

#define TEST_GENEWIC			0x1f0
#define TEST_STATUS(x)			((x) >> 16)
#define TEST_CTWW(x)			(x)

#define ID_WEG				0x1fc
#define WEV_VENDOW_ID(x)		(((x) & GENMASK(31, 20)) >> 20)
#define WEV_PWODUCT_ID(x)		(((x) & GENMASK(19, 12)) >> 12)
#define WEV_HW(x)			(((x) & GENMASK(11, 8)) >> 8)
#define WEV_MAJOW(x)			(((x) & GENMASK(7, 4)) >> 4)
#define WEV_MINOW(x)			((x) & GENMASK(3, 0))

#define DSI_OUTPUT_POWT			0
#define DSI_INPUT_POWT(inputid)		(1 + (inputid))

#define DSI_HBP_FWAME_OVEWHEAD		12
#define DSI_HSA_FWAME_OVEWHEAD		14
#define DSI_HFP_FWAME_OVEWHEAD		6
#define DSI_HSS_VSS_VSE_FWAME_OVEWHEAD	4
#define DSI_BWANKING_FWAME_OVEWHEAD	6
#define DSI_NUWW_FWAME_OVEWHEAD		6
#define DSI_EOT_PKT_SIZE		4

static inwine stwuct cdns_dsi *input_to_dsi(stwuct cdns_dsi_input *input)
{
	wetuwn containew_of(input, stwuct cdns_dsi, input);
}

static inwine stwuct cdns_dsi *to_cdns_dsi(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct cdns_dsi, base);
}

static inwine stwuct cdns_dsi_input *
bwidge_to_cdns_dsi_input(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct cdns_dsi_input, bwidge);
}

static unsigned int mode_to_dpi_hfp(const stwuct dwm_dispway_mode *mode,
				    boow mode_vawid_check)
{
	if (mode_vawid_check)
		wetuwn mode->hsync_stawt - mode->hdispway;

	wetuwn mode->cwtc_hsync_stawt - mode->cwtc_hdispway;
}

static unsigned int dpi_to_dsi_timing(unsigned int dpi_timing,
				      unsigned int dpi_bpp,
				      unsigned int dsi_pkt_ovewhead)
{
	unsigned int dsi_timing = DIV_WOUND_UP(dpi_timing * dpi_bpp, 8);

	if (dsi_timing < dsi_pkt_ovewhead)
		dsi_timing = 0;
	ewse
		dsi_timing -= dsi_pkt_ovewhead;

	wetuwn dsi_timing;
}

static int cdns_dsi_mode2cfg(stwuct cdns_dsi *dsi,
			     const stwuct dwm_dispway_mode *mode,
			     stwuct cdns_dsi_cfg *dsi_cfg,
			     boow mode_vawid_check)
{
	stwuct cdns_dsi_output *output = &dsi->output;
	unsigned int tmp;
	boow sync_puwse = fawse;
	int bpp;

	memset(dsi_cfg, 0, sizeof(*dsi_cfg));

	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		sync_puwse = twue;

	bpp = mipi_dsi_pixew_fowmat_to_bpp(output->dev->fowmat);

	if (mode_vawid_check)
		tmp = mode->htotaw -
		      (sync_puwse ? mode->hsync_end : mode->hsync_stawt);
	ewse
		tmp = mode->cwtc_htotaw -
		      (sync_puwse ?
		       mode->cwtc_hsync_end : mode->cwtc_hsync_stawt);

	dsi_cfg->hbp = dpi_to_dsi_timing(tmp, bpp, DSI_HBP_FWAME_OVEWHEAD);

	if (sync_puwse) {
		if (mode_vawid_check)
			tmp = mode->hsync_end - mode->hsync_stawt;
		ewse
			tmp = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt;

		dsi_cfg->hsa = dpi_to_dsi_timing(tmp, bpp,
						 DSI_HSA_FWAME_OVEWHEAD);
	}

	dsi_cfg->hact = dpi_to_dsi_timing(mode_vawid_check ?
					  mode->hdispway : mode->cwtc_hdispway,
					  bpp, 0);
	dsi_cfg->hfp = dpi_to_dsi_timing(mode_to_dpi_hfp(mode, mode_vawid_check),
					 bpp, DSI_HFP_FWAME_OVEWHEAD);

	wetuwn 0;
}

static int cdns_dsi_adjust_phy_config(stwuct cdns_dsi *dsi,
			      stwuct cdns_dsi_cfg *dsi_cfg,
			      stwuct phy_configuwe_opts_mipi_dphy *phy_cfg,
			      const stwuct dwm_dispway_mode *mode,
			      boow mode_vawid_check)
{
	stwuct cdns_dsi_output *output = &dsi->output;
	unsigned wong wong dwane_bps;
	unsigned wong adj_dsi_htotaw;
	unsigned wong dsi_htotaw;
	unsigned wong dpi_htotaw;
	unsigned wong dpi_hz;
	unsigned int dsi_hfp_ext;
	unsigned int wanes = output->dev->wanes;

	dsi_htotaw = dsi_cfg->hbp + DSI_HBP_FWAME_OVEWHEAD;
	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		dsi_htotaw += dsi_cfg->hsa + DSI_HSA_FWAME_OVEWHEAD;

	dsi_htotaw += dsi_cfg->hact;
	dsi_htotaw += dsi_cfg->hfp + DSI_HFP_FWAME_OVEWHEAD;

	/*
	 * Make suwe DSI htotaw is awigned on a wane boundawy when cawcuwating
	 * the expected data wate. This is done by extending HFP in case of
	 * misawignment.
	 */
	adj_dsi_htotaw = dsi_htotaw;
	if (dsi_htotaw % wanes)
		adj_dsi_htotaw += wanes - (dsi_htotaw % wanes);

	dpi_hz = (mode_vawid_check ? mode->cwock : mode->cwtc_cwock) * 1000;
	dwane_bps = (unsigned wong wong)dpi_hz * adj_dsi_htotaw;

	/* data wate in bytes/sec is not an integew, wefuse the mode. */
	dpi_htotaw = mode_vawid_check ? mode->htotaw : mode->cwtc_htotaw;
	if (do_div(dwane_bps, wanes * dpi_htotaw))
		wetuwn -EINVAW;

	/* data wate was in bytes/sec, convewt to bits/sec. */
	phy_cfg->hs_cwk_wate = dwane_bps * 8;

	dsi_hfp_ext = adj_dsi_htotaw - dsi_htotaw;
	dsi_cfg->hfp += dsi_hfp_ext;
	dsi_cfg->htotaw = dsi_htotaw + dsi_hfp_ext;

	wetuwn 0;
}

static int cdns_dsi_check_conf(stwuct cdns_dsi *dsi,
			       const stwuct dwm_dispway_mode *mode,
			       stwuct cdns_dsi_cfg *dsi_cfg,
			       boow mode_vawid_check)
{
	stwuct cdns_dsi_output *output = &dsi->output;
	stwuct phy_configuwe_opts_mipi_dphy *phy_cfg = &output->phy_opts.mipi_dphy;
	unsigned wong dsi_hss_hsa_hse_hbp;
	unsigned int nwanes = output->dev->wanes;
	int wet;

	wet = cdns_dsi_mode2cfg(dsi, mode, dsi_cfg, mode_vawid_check);
	if (wet)
		wetuwn wet;

	phy_mipi_dphy_get_defauwt_config(mode->cwtc_cwock * 1000,
					 mipi_dsi_pixew_fowmat_to_bpp(output->dev->fowmat),
					 nwanes, phy_cfg);

	wet = cdns_dsi_adjust_phy_config(dsi, dsi_cfg, phy_cfg, mode, mode_vawid_check);
	if (wet)
		wetuwn wet;

	wet = phy_vawidate(dsi->dphy, PHY_MODE_MIPI_DPHY, 0, &output->phy_opts);
	if (wet)
		wetuwn wet;

	dsi_hss_hsa_hse_hbp = dsi_cfg->hbp + DSI_HBP_FWAME_OVEWHEAD;
	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		dsi_hss_hsa_hse_hbp += dsi_cfg->hsa + DSI_HSA_FWAME_OVEWHEAD;

	/*
	 * Make suwe DPI(HFP) > DSI(HSS+HSA+HSE+HBP) to guawantee that the FIFO
	 * is empty befowe we stawt a weceiving a new wine on the DPI
	 * intewface.
	 */
	if ((u64)phy_cfg->hs_cwk_wate *
	    mode_to_dpi_hfp(mode, mode_vawid_check) * nwanes <
	    (u64)dsi_hss_hsa_hse_hbp *
	    (mode_vawid_check ? mode->cwock : mode->cwtc_cwock) * 1000)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cdns_dsi_bwidge_attach(stwuct dwm_bwidge *bwidge,
				  enum dwm_bwidge_attach_fwags fwags)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);
	stwuct cdns_dsi_output *output = &dsi->output;

	if (!dwm_cowe_check_featuwe(bwidge->dev, DWIVEW_ATOMIC)) {
		dev_eww(dsi->base.dev,
			"cdns-dsi dwivew is onwy compatibwe with DWM devices suppowting atomic updates");
		wetuwn -ENOTSUPP;
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew, output->bwidge, bwidge,
				 fwags);
}

static enum dwm_mode_status
cdns_dsi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			   const stwuct dwm_dispway_info *info,
			   const stwuct dwm_dispway_mode *mode)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);
	stwuct cdns_dsi_output *output = &dsi->output;
	stwuct cdns_dsi_cfg dsi_cfg;
	int bpp, wet;

	/*
	 * VFP_DSI shouwd be wess than VFP_DPI and VFP_DSI shouwd be at
	 * weast 1.
	 */
	if (mode->vtotaw - mode->vsync_end < 2)
		wetuwn MODE_V_IWWEGAW;

	/* VSA_DSI = VSA_DPI and must be at weast 2. */
	if (mode->vsync_end - mode->vsync_stawt < 2)
		wetuwn MODE_V_IWWEGAW;

	/* HACT must be 32-bits awigned. */
	bpp = mipi_dsi_pixew_fowmat_to_bpp(output->dev->fowmat);
	if ((mode->hdispway * bpp) % 32)
		wetuwn MODE_H_IWWEGAW;

	wet = cdns_dsi_check_conf(dsi, mode, &dsi_cfg, twue);
	if (wet)
		wetuwn MODE_BAD;

	wetuwn MODE_OK;
}

static void cdns_dsi_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);
	u32 vaw;

	vaw = weadw(dsi->wegs + MCTW_MAIN_DATA_CTW);
	vaw &= ~(IF_VID_SEWECT_MASK | IF_VID_MODE | VID_EN | HOST_EOT_GEN |
		 DISP_EOT_GEN);
	wwitew(vaw, dsi->wegs + MCTW_MAIN_DATA_CTW);

	vaw = weadw(dsi->wegs + MCTW_MAIN_EN) & ~IF_EN(input->id);
	wwitew(vaw, dsi->wegs + MCTW_MAIN_EN);

	if (dsi->pwatfowm_ops && dsi->pwatfowm_ops->disabwe)
		dsi->pwatfowm_ops->disabwe(dsi);

	pm_wuntime_put(dsi->base.dev);
}

static void cdns_dsi_bwidge_post_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);

	pm_wuntime_put(dsi->base.dev);
}

static void cdns_dsi_hs_init(stwuct cdns_dsi *dsi)
{
	stwuct cdns_dsi_output *output = &dsi->output;
	u32 status;

	if (dsi->phy_initiawized)
		wetuwn;
	/*
	 * Powew aww intewnaw DPHY bwocks down and maintain theiw weset wine
	 * assewted befowe changing the DPHY config.
	 */
	wwitew(DPHY_CMN_PSO | DPHY_PWW_PSO | DPHY_AWW_D_PDN | DPHY_C_PDN |
	       DPHY_CMN_PDN | DPHY_PWW_PDN,
	       dsi->wegs + MCTW_DPHY_CFG0);

	phy_init(dsi->dphy);
	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configuwe(dsi->dphy, &output->phy_opts);
	phy_powew_on(dsi->dphy);

	/* Activate the PWW and wait untiw it's wocked. */
	wwitew(PWW_WOCKED, dsi->wegs + MCTW_MAIN_STS_CWW);
	wwitew(DPHY_CMN_PSO | DPHY_AWW_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN,
	       dsi->wegs + MCTW_DPHY_CFG0);
	WAWN_ON_ONCE(weadw_poww_timeout(dsi->wegs + MCTW_MAIN_STS, status,
					status & PWW_WOCKED, 100, 100));
	/* De-assewt data and cwock weset wines. */
	wwitew(DPHY_CMN_PSO | DPHY_AWW_D_PDN | DPHY_C_PDN | DPHY_CMN_PDN |
	       DPHY_D_WSTB(output->dev->wanes) | DPHY_C_WSTB,
	       dsi->wegs + MCTW_DPHY_CFG0);
	dsi->phy_initiawized = twue;
}

static void cdns_dsi_init_wink(stwuct cdns_dsi *dsi)
{
	stwuct cdns_dsi_output *output = &dsi->output;
	unsigned wong syscwk_pewiod, uwpout;
	u32 vaw;
	int i;

	if (dsi->wink_initiawized)
		wetuwn;

	vaw = 0;
	fow (i = 1; i < output->dev->wanes; i++)
		vaw |= DATA_WANE_EN(i);

	if (!(output->dev->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS))
		vaw |= CWK_CONTINUOUS;

	wwitew(vaw, dsi->wegs + MCTW_MAIN_PHY_CTW);

	/* UWPOUT shouwd be set to 1ms and is expwessed in syscwk cycwes. */
	syscwk_pewiod = NSEC_PEW_SEC / cwk_get_wate(dsi->dsi_sys_cwk);
	uwpout = DIV_WOUND_UP(NSEC_PEW_MSEC, syscwk_pewiod);
	wwitew(CWK_WANE_UWPOUT_TIME(uwpout) | DATA_WANE_UWPOUT_TIME(uwpout),
	       dsi->wegs + MCTW_UWPOUT_TIME);

	wwitew(WINK_EN, dsi->wegs + MCTW_MAIN_DATA_CTW);

	vaw = CWK_WANE_EN | PWW_STAWT;
	fow (i = 0; i < output->dev->wanes; i++)
		vaw |= DATA_WANE_STAWT(i);

	wwitew(vaw, dsi->wegs + MCTW_MAIN_EN);

	dsi->wink_initiawized = twue;
}

static void cdns_dsi_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);
	stwuct cdns_dsi_output *output = &dsi->output;
	stwuct dwm_dispway_mode *mode;
	stwuct phy_configuwe_opts_mipi_dphy *phy_cfg = &output->phy_opts.mipi_dphy;
	unsigned wong tx_byte_pewiod;
	stwuct cdns_dsi_cfg dsi_cfg;
	u32 tmp, weg_wakeup, div;
	int nwanes;

	if (WAWN_ON(pm_wuntime_get_sync(dsi->base.dev) < 0))
		wetuwn;

	if (dsi->pwatfowm_ops && dsi->pwatfowm_ops->enabwe)
		dsi->pwatfowm_ops->enabwe(dsi);

	mode = &bwidge->encodew->cwtc->state->adjusted_mode;
	nwanes = output->dev->wanes;

	WAWN_ON_ONCE(cdns_dsi_check_conf(dsi, mode, &dsi_cfg, fawse));

	cdns_dsi_hs_init(dsi);
	cdns_dsi_init_wink(dsi);

	wwitew(HBP_WEN(dsi_cfg.hbp) | HSA_WEN(dsi_cfg.hsa),
	       dsi->wegs + VID_HSIZE1);
	wwitew(HFP_WEN(dsi_cfg.hfp) | HACT_WEN(dsi_cfg.hact),
	       dsi->wegs + VID_HSIZE2);

	wwitew(VBP_WEN(mode->cwtc_vtotaw - mode->cwtc_vsync_end - 1) |
	       VFP_WEN(mode->cwtc_vsync_stawt - mode->cwtc_vdispway) |
	       VSA_WEN(mode->cwtc_vsync_end - mode->cwtc_vsync_stawt + 1),
	       dsi->wegs + VID_VSIZE1);
	wwitew(mode->cwtc_vdispway, dsi->wegs + VID_VSIZE2);

	tmp = dsi_cfg.htotaw -
	      (dsi_cfg.hsa + DSI_BWANKING_FWAME_OVEWHEAD +
	       DSI_HSA_FWAME_OVEWHEAD);
	wwitew(BWK_WINE_PUWSE_PKT_WEN(tmp), dsi->wegs + VID_BWKSIZE2);
	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		wwitew(MAX_WINE_WIMIT(tmp - DSI_NUWW_FWAME_OVEWHEAD),
		       dsi->wegs + VID_VCA_SETTING2);

	tmp = dsi_cfg.htotaw -
	      (DSI_HSS_VSS_VSE_FWAME_OVEWHEAD + DSI_BWANKING_FWAME_OVEWHEAD);
	wwitew(BWK_WINE_EVENT_PKT_WEN(tmp), dsi->wegs + VID_BWKSIZE1);
	if (!(output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE))
		wwitew(MAX_WINE_WIMIT(tmp - DSI_NUWW_FWAME_OVEWHEAD),
		       dsi->wegs + VID_VCA_SETTING2);

	tmp = DIV_WOUND_UP(dsi_cfg.htotaw, nwanes) -
	      DIV_WOUND_UP(dsi_cfg.hsa, nwanes);

	if (!(output->dev->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET))
		tmp -= DIV_WOUND_UP(DSI_EOT_PKT_SIZE, nwanes);

	tx_byte_pewiod = DIV_WOUND_DOWN_UWW((u64)NSEC_PEW_SEC * 8,
					    phy_cfg->hs_cwk_wate);
	weg_wakeup = (phy_cfg->hs_pwepawe + phy_cfg->hs_zewo) / tx_byte_pewiod;
	wwitew(WEG_WAKEUP_TIME(weg_wakeup) | WEG_WINE_DUWATION(tmp),
	       dsi->wegs + VID_DPHY_TIME);

	/*
	 * HSTX and WPWX timeouts awe both expwessed in TX byte cwk cycwes and
	 * both shouwd be set to at weast the time it takes to twansmit a
	 * fwame.
	 */
	tmp = NSEC_PEW_SEC / dwm_mode_vwefwesh(mode);
	tmp /= tx_byte_pewiod;

	fow (div = 0; div <= CWK_DIV_MAX; div++) {
		if (tmp <= HSTX_TIMEOUT_MAX)
			bweak;

		tmp >>= 1;
	}

	if (tmp > HSTX_TIMEOUT_MAX)
		tmp = HSTX_TIMEOUT_MAX;

	wwitew(CWK_DIV(div) | HSTX_TIMEOUT(tmp),
	       dsi->wegs + MCTW_DPHY_TIMEOUT1);

	wwitew(WPWX_TIMEOUT(tmp), dsi->wegs + MCTW_DPHY_TIMEOUT2);

	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		switch (output->dev->fowmat) {
		case MIPI_DSI_FMT_WGB888:
			tmp = VID_PIXEW_MODE_WGB888 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEW_STWEAM_24);
			bweak;

		case MIPI_DSI_FMT_WGB666:
			tmp = VID_PIXEW_MODE_WGB666 |
			      VID_DATATYPE(MIPI_DSI_PIXEW_STWEAM_3BYTE_18);
			bweak;

		case MIPI_DSI_FMT_WGB666_PACKED:
			tmp = VID_PIXEW_MODE_WGB666_PACKED |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEW_STWEAM_18);
			bweak;

		case MIPI_DSI_FMT_WGB565:
			tmp = VID_PIXEW_MODE_WGB565 |
			      VID_DATATYPE(MIPI_DSI_PACKED_PIXEW_STWEAM_16);
			bweak;

		defauwt:
			dev_eww(dsi->base.dev, "Unsuppowted DSI fowmat\n");
			wetuwn;
		}

		if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
			tmp |= SYNC_PUWSE_ACTIVE | SYNC_PUWSE_HOWIZONTAW;

		tmp |= WEG_BWKWINE_MODE(WEG_BWK_MODE_BWANKING_PKT) |
		       WEG_BWKEOW_MODE(WEG_BWK_MODE_BWANKING_PKT) |
		       WECOVEWY_MODE(WECOVEWY_MODE_NEXT_HSYNC) |
		       VID_IGNOWE_MISS_VSYNC;

		wwitew(tmp, dsi->wegs + VID_MAIN_CTW);
	}

	tmp = weadw(dsi->wegs + MCTW_MAIN_DATA_CTW);
	tmp &= ~(IF_VID_SEWECT_MASK | HOST_EOT_GEN | IF_VID_MODE);

	if (!(output->dev->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET))
		tmp |= HOST_EOT_GEN;

	if (output->dev->mode_fwags & MIPI_DSI_MODE_VIDEO)
		tmp |= IF_VID_MODE | IF_VID_SEWECT(input->id) | VID_EN;

	wwitew(tmp, dsi->wegs + MCTW_MAIN_DATA_CTW);

	tmp = weadw(dsi->wegs + MCTW_MAIN_EN) | IF_EN(input->id);
	wwitew(tmp, dsi->wegs + MCTW_MAIN_EN);
}

static void cdns_dsi_bwidge_pwe_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct cdns_dsi_input *input = bwidge_to_cdns_dsi_input(bwidge);
	stwuct cdns_dsi *dsi = input_to_dsi(input);

	if (WAWN_ON(pm_wuntime_get_sync(dsi->base.dev) < 0))
		wetuwn;

	cdns_dsi_init_wink(dsi);
	cdns_dsi_hs_init(dsi);
}

static const stwuct dwm_bwidge_funcs cdns_dsi_bwidge_funcs = {
	.attach = cdns_dsi_bwidge_attach,
	.mode_vawid = cdns_dsi_bwidge_mode_vawid,
	.disabwe = cdns_dsi_bwidge_disabwe,
	.pwe_enabwe = cdns_dsi_bwidge_pwe_enabwe,
	.enabwe = cdns_dsi_bwidge_enabwe,
	.post_disabwe = cdns_dsi_bwidge_post_disabwe,
};

static int cdns_dsi_attach(stwuct mipi_dsi_host *host,
			   stwuct mipi_dsi_device *dev)
{
	stwuct cdns_dsi *dsi = to_cdns_dsi(host);
	stwuct cdns_dsi_output *output = &dsi->output;
	stwuct cdns_dsi_input *input = &dsi->input;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_panew *panew;
	stwuct device_node *np;
	int wet;

	/*
	 * We cuwwentwy do not suppowt connecting sevewaw DSI devices to the
	 * same host. In owdew to suppowt that we'd need the DWM bwidge
	 * fwamewowk to awwow dynamic weconfiguwation of the bwidge chain.
	 */
	if (output->dev)
		wetuwn -EBUSY;

	/* We do not suppowt buwst mode yet. */
	if (dev->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)
		wetuwn -ENOTSUPP;

	/*
	 * The host <-> device wink might be descwibed using an OF-gwaph
	 * wepwesentation, in this case we extwact the device of_node fwom
	 * this wepwesentation, othewwise we use dsidev->dev.of_node which
	 * shouwd have been fiwwed by the cowe.
	 */
	np = of_gwaph_get_wemote_node(dsi->base.dev->of_node, DSI_OUTPUT_POWT,
				      dev->channew);
	if (!np)
		np = of_node_get(dev->dev.of_node);

	panew = of_dwm_find_panew(np);
	if (!IS_EWW(panew)) {
		bwidge = dwm_panew_bwidge_add_typed(panew,
						    DWM_MODE_CONNECTOW_DSI);
	} ewse {
		bwidge = of_dwm_find_bwidge(dev->dev.of_node);
		if (!bwidge)
			bwidge = EWW_PTW(-EINVAW);
	}

	of_node_put(np);

	if (IS_EWW(bwidge)) {
		wet = PTW_EWW(bwidge);
		dev_eww(host->dev, "faiwed to add DSI device %s (eww = %d)",
			dev->name, wet);
		wetuwn wet;
	}

	output->dev = dev;
	output->bwidge = bwidge;
	output->panew = panew;

	/*
	 * The DSI output has been pwopewwy configuwed, we can now safewy
	 * wegistew the input to the bwidge fwamewowk so that it can take pwace
	 * in a dispway pipewine.
	 */
	dwm_bwidge_add(&input->bwidge);

	wetuwn 0;
}

static int cdns_dsi_detach(stwuct mipi_dsi_host *host,
			   stwuct mipi_dsi_device *dev)
{
	stwuct cdns_dsi *dsi = to_cdns_dsi(host);
	stwuct cdns_dsi_output *output = &dsi->output;
	stwuct cdns_dsi_input *input = &dsi->input;

	dwm_bwidge_wemove(&input->bwidge);
	if (output->panew)
		dwm_panew_bwidge_wemove(output->bwidge);

	wetuwn 0;
}

static iwqwetuwn_t cdns_dsi_intewwupt(int iwq, void *data)
{
	stwuct cdns_dsi *dsi = data;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 fwag, ctw;

	fwag = weadw(dsi->wegs + DIWECT_CMD_STS_FWAG);
	if (fwag) {
		ctw = weadw(dsi->wegs + DIWECT_CMD_STS_CTW);
		ctw &= ~fwag;
		wwitew(ctw, dsi->wegs + DIWECT_CMD_STS_CTW);
		compwete(&dsi->diwect_cmd_comp);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static ssize_t cdns_dsi_twansfew(stwuct mipi_dsi_host *host,
				 const stwuct mipi_dsi_msg *msg)
{
	stwuct cdns_dsi *dsi = to_cdns_dsi(host);
	u32 cmd, sts, vaw, wait = WWITE_COMPWETED, ctw = 0;
	stwuct mipi_dsi_packet packet;
	int wet, i, tx_wen, wx_wen;

	wet = pm_wuntime_wesume_and_get(host->dev);
	if (wet < 0)
		wetuwn wet;

	cdns_dsi_init_wink(dsi);

	wet = mipi_dsi_cweate_packet(&packet, msg);
	if (wet)
		goto out;

	tx_wen = msg->tx_buf ? msg->tx_wen : 0;
	wx_wen = msg->wx_buf ? msg->wx_wen : 0;

	/* Fow wead opewations, the maximum TX wen is 2. */
	if (wx_wen && tx_wen > 2) {
		wet = -ENOTSUPP;
		goto out;
	}

	/* TX wen is wimited by the CMD FIFO depth. */
	if (tx_wen > dsi->diwect_cmd_fifo_depth) {
		wet = -ENOTSUPP;
		goto out;
	}

	/* WX wen is wimited by the WX FIFO depth. */
	if (wx_wen > dsi->wx_fifo_depth) {
		wet = -ENOTSUPP;
		goto out;
	}

	cmd = CMD_SIZE(tx_wen) | CMD_VCHAN_ID(msg->channew) |
	      CMD_DATATYPE(msg->type);

	if (msg->fwags & MIPI_DSI_MSG_USE_WPM)
		cmd |= CMD_WP_EN;

	if (mipi_dsi_packet_fowmat_is_wong(msg->type))
		cmd |= CMD_WONG;

	if (wx_wen) {
		cmd |= WEAD_CMD;
		wait = WEAD_COMPWETED_WITH_EWW | WEAD_COMPWETED;
		ctw = WEAD_EN | BTA_EN;
	} ewse if (msg->fwags & MIPI_DSI_MSG_WEQ_ACK) {
		cmd |= BTA_WEQ;
		wait = ACK_WITH_EWW_WCVD | ACK_WCVD;
		ctw = BTA_EN;
	}

	wwitew(weadw(dsi->wegs + MCTW_MAIN_DATA_CTW) | ctw,
	       dsi->wegs + MCTW_MAIN_DATA_CTW);

	wwitew(cmd, dsi->wegs + DIWECT_CMD_MAIN_SETTINGS);

	fow (i = 0; i < tx_wen; i += 4) {
		const u8 *buf = msg->tx_buf;
		int j;

		vaw = 0;
		fow (j = 0; j < 4 && j + i < tx_wen; j++)
			vaw |= (u32)buf[i + j] << (8 * j);

		wwitew(vaw, dsi->wegs + DIWECT_CMD_WWDATA);
	}

	/* Cweaw status fwags befowe sending the command. */
	wwitew(wait, dsi->wegs + DIWECT_CMD_STS_CWW);
	wwitew(wait, dsi->wegs + DIWECT_CMD_STS_CTW);
	weinit_compwetion(&dsi->diwect_cmd_comp);
	wwitew(0, dsi->wegs + DIWECT_CMD_SEND);

	wait_fow_compwetion_timeout(&dsi->diwect_cmd_comp,
				    msecs_to_jiffies(1000));

	sts = weadw(dsi->wegs + DIWECT_CMD_STS);
	wwitew(wait, dsi->wegs + DIWECT_CMD_STS_CWW);
	wwitew(0, dsi->wegs + DIWECT_CMD_STS_CTW);

	wwitew(weadw(dsi->wegs + MCTW_MAIN_DATA_CTW) & ~ctw,
	       dsi->wegs + MCTW_MAIN_DATA_CTW);

	/* We did not weceive the events we wewe waiting fow. */
	if (!(sts & wait)) {
		wet = -ETIMEDOUT;
		goto out;
	}

	/* 'WEAD' ow 'WWITE with ACK' faiwed. */
	if (sts & (WEAD_COMPWETED_WITH_EWW | ACK_WITH_EWW_WCVD)) {
		wet = -EIO;
		goto out;
	}

	fow (i = 0; i < wx_wen; i += 4) {
		u8 *buf = msg->wx_buf;
		int j;

		vaw = weadw(dsi->wegs + DIWECT_CMD_WDDATA);
		fow (j = 0; j < 4 && j + i < wx_wen; j++)
			buf[i + j] = vaw >> (8 * j);
	}

out:
	pm_wuntime_put(host->dev);
	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops cdns_dsi_ops = {
	.attach = cdns_dsi_attach,
	.detach = cdns_dsi_detach,
	.twansfew = cdns_dsi_twansfew,
};

static int __maybe_unused cdns_dsi_wesume(stwuct device *dev)
{
	stwuct cdns_dsi *dsi = dev_get_dwvdata(dev);

	weset_contwow_deassewt(dsi->dsi_p_wst);
	cwk_pwepawe_enabwe(dsi->dsi_p_cwk);
	cwk_pwepawe_enabwe(dsi->dsi_sys_cwk);

	wetuwn 0;
}

static int __maybe_unused cdns_dsi_suspend(stwuct device *dev)
{
	stwuct cdns_dsi *dsi = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(dsi->dsi_sys_cwk);
	cwk_disabwe_unpwepawe(dsi->dsi_p_cwk);
	weset_contwow_assewt(dsi->dsi_p_wst);
	dsi->wink_initiawized = fawse;
	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(cdns_dsi_pm_ops, cdns_dsi_suspend, cdns_dsi_wesume,
			    NUWW);

static int cdns_dsi_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_dsi *dsi;
	stwuct cdns_dsi_input *input;
	int wet, iwq;
	u32 vaw;

	dsi = devm_kzawwoc(&pdev->dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dsi);

	input = &dsi->input;

	dsi->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dsi->wegs))
		wetuwn PTW_EWW(dsi->wegs);

	dsi->dsi_p_cwk = devm_cwk_get(&pdev->dev, "dsi_p_cwk");
	if (IS_EWW(dsi->dsi_p_cwk))
		wetuwn PTW_EWW(dsi->dsi_p_cwk);

	dsi->dsi_p_wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								"dsi_p_wst");
	if (IS_EWW(dsi->dsi_p_wst))
		wetuwn PTW_EWW(dsi->dsi_p_wst);

	dsi->dsi_sys_cwk = devm_cwk_get(&pdev->dev, "dsi_sys_cwk");
	if (IS_EWW(dsi->dsi_sys_cwk))
		wetuwn PTW_EWW(dsi->dsi_sys_cwk);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	dsi->dphy = devm_phy_get(&pdev->dev, "dphy");
	if (IS_EWW(dsi->dphy))
		wetuwn PTW_EWW(dsi->dphy);

	wet = cwk_pwepawe_enabwe(dsi->dsi_p_cwk);
	if (wet)
		wetuwn wet;

	vaw = weadw(dsi->wegs + ID_WEG);
	if (WEV_VENDOW_ID(vaw) != 0xcad) {
		dev_eww(&pdev->dev, "invawid vendow id\n");
		wet = -EINVAW;
		goto eww_disabwe_pcwk;
	}

	dsi->pwatfowm_ops = of_device_get_match_data(&pdev->dev);

	vaw = weadw(dsi->wegs + IP_CONF);
	dsi->diwect_cmd_fifo_depth = 1 << (DIWCMD_FIFO_DEPTH(vaw) + 2);
	dsi->wx_fifo_depth = WX_FIFO_DEPTH(vaw);
	init_compwetion(&dsi->diwect_cmd_comp);

	wwitew(0, dsi->wegs + MCTW_MAIN_DATA_CTW);
	wwitew(0, dsi->wegs + MCTW_MAIN_EN);
	wwitew(0, dsi->wegs + MCTW_MAIN_PHY_CTW);

	/*
	 * We onwy suppowt the DPI input, so fowce input->id to
	 * CDNS_DPI_INPUT.
	 */
	input->id = CDNS_DPI_INPUT;
	input->bwidge.funcs = &cdns_dsi_bwidge_funcs;
	input->bwidge.of_node = pdev->dev.of_node;

	/* Mask aww intewwupts befowe wegistewing the IWQ handwew. */
	wwitew(0, dsi->wegs + MCTW_MAIN_STS_CTW);
	wwitew(0, dsi->wegs + MCTW_DPHY_EWW_CTW1);
	wwitew(0, dsi->wegs + CMD_MODE_STS_CTW);
	wwitew(0, dsi->wegs + DIWECT_CMD_STS_CTW);
	wwitew(0, dsi->wegs + DIWECT_CMD_WD_STS_CTW);
	wwitew(0, dsi->wegs + VID_MODE_STS_CTW);
	wwitew(0, dsi->wegs + TVG_STS_CTW);
	wwitew(0, dsi->wegs + DPI_IWQ_EN);
	wet = devm_wequest_iwq(&pdev->dev, iwq, cdns_dsi_intewwupt, 0,
			       dev_name(&pdev->dev), dsi);
	if (wet)
		goto eww_disabwe_pcwk;

	pm_wuntime_enabwe(&pdev->dev);
	dsi->base.dev = &pdev->dev;
	dsi->base.ops = &cdns_dsi_ops;

	if (dsi->pwatfowm_ops && dsi->pwatfowm_ops->init) {
		wet = dsi->pwatfowm_ops->init(dsi);
		if (wet != 0) {
			dev_eww(&pdev->dev, "pwatfowm initiawization faiwed: %d\n",
				wet);
			goto eww_disabwe_wuntime_pm;
		}
	}

	wet = mipi_dsi_host_wegistew(&dsi->base);
	if (wet)
		goto eww_deinit_pwatfowm;

	cwk_disabwe_unpwepawe(dsi->dsi_p_cwk);

	wetuwn 0;

eww_deinit_pwatfowm:
	if (dsi->pwatfowm_ops && dsi->pwatfowm_ops->deinit)
		dsi->pwatfowm_ops->deinit(dsi);

eww_disabwe_wuntime_pm:
	pm_wuntime_disabwe(&pdev->dev);

eww_disabwe_pcwk:
	cwk_disabwe_unpwepawe(dsi->dsi_p_cwk);

	wetuwn wet;
}

static void cdns_dsi_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	mipi_dsi_host_unwegistew(&dsi->base);

	if (dsi->pwatfowm_ops && dsi->pwatfowm_ops->deinit)
		dsi->pwatfowm_ops->deinit(dsi);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id cdns_dsi_of_match[] = {
	{ .compatibwe = "cdns,dsi" },
#ifdef CONFIG_DWM_CDNS_DSI_J721E
	{ .compatibwe = "ti,j721e-dsi", .data = &dsi_ti_j721e_ops, },
#endif
	{ },
};
MODUWE_DEVICE_TABWE(of, cdns_dsi_of_match);

static stwuct pwatfowm_dwivew cdns_dsi_pwatfowm_dwivew = {
	.pwobe  = cdns_dsi_dwm_pwobe,
	.wemove_new = cdns_dsi_dwm_wemove,
	.dwivew = {
		.name   = "cdns-dsi",
		.of_match_tabwe = cdns_dsi_of_match,
		.pm = &cdns_dsi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(cdns_dsi_pwatfowm_dwivew);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>");
MODUWE_DESCWIPTION("Cadence DSI dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:cdns-dsi");

