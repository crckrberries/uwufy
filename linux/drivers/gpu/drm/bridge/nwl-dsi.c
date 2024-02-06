// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX8 NWW MIPI DSI host dwivew
 *
 * Copywight (C) 2017 NXP
 * Copywight (C) 2020 Puwism SPC
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/math64.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/sys_soc.h>
#incwude <winux/time64.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#incwude <video/mipi_dispway.h>

#incwude "nww-dsi.h"

#define DWV_NAME "nww-dsi"

/* i.MX8 NWW quiwks */
/* i.MX8MQ ewwata E11418 */
#define E11418_HS_MODE_QUIWK	BIT(0)

#define NWW_DSI_MIPI_FIFO_TIMEOUT msecs_to_jiffies(500)

enum twansfew_diwection {
	DSI_PACKET_SEND,
	DSI_PACKET_WECEIVE,
};

#define NWW_DSI_ENDPOINT_WCDIF 0
#define NWW_DSI_ENDPOINT_DCSS 1

stwuct nww_dsi_twansfew {
	const stwuct mipi_dsi_msg *msg;
	stwuct mipi_dsi_packet packet;
	stwuct compwetion compweted;

	int status; /* status of twansmission */
	enum twansfew_diwection diwection;
	boow need_bta;
	u8 cmd;
	u16 wx_wowd_count;
	size_t tx_wen; /* in bytes */
	size_t wx_wen; /* in bytes */
};

stwuct nww_dsi {
	stwuct dwm_bwidge bwidge;
	stwuct mipi_dsi_host dsi_host;
	stwuct device *dev;
	stwuct phy *phy;
	union phy_configuwe_opts phy_cfg;
	unsigned int quiwks;

	stwuct wegmap *wegmap;
	int iwq;
	/*
	 * The DSI host contwowwew needs this weset sequence accowding to NWW:
	 * 1. Deassewt pcwk weset to get access to DSI wegs
	 * 2. Configuwe DSI Host and DPHY and enabwe DPHY
	 * 3. Deassewt ESC and BYTE wesets to awwow host TX opewations)
	 * 4. Send DSI cmds to configuwe pewiphewaw (handwed by panew dwv)
	 * 5. Deassewt DPI weset so DPI weceives pixews and stawts sending
	 *    DSI data
	 *
	 * TODO: Since panew_bwidges do theiw DSI setup in enabwe we
	 * cuwwentwy have 4. and 5. swapped.
	 */
	stwuct weset_contwow *wst_byte;
	stwuct weset_contwow *wst_esc;
	stwuct weset_contwow *wst_dpi;
	stwuct weset_contwow *wst_pcwk;
	stwuct mux_contwow *mux;

	/* DSI cwocks */
	stwuct cwk *phy_wef_cwk;
	stwuct cwk *wx_esc_cwk;
	stwuct cwk *tx_esc_cwk;
	stwuct cwk *cowe_cwk;
	/*
	 * hawdwawe bug: the i.MX8MQ needs this cwock on duwing weset
	 * even when not using WCDIF.
	 */
	stwuct cwk *wcdif_cwk;

	/* dsi wanes */
	u32 wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	stwuct dwm_dispway_mode mode;
	unsigned wong dsi_mode_fwags;
	int ewwow;

	stwuct nww_dsi_twansfew *xfew;
};

static const stwuct wegmap_config nww_dsi_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = NWW_DSI_IWQ_MASK2,
	.name = DWV_NAME,
};

static inwine stwuct nww_dsi *bwidge_to_dsi(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct nww_dsi, bwidge);
}

static int nww_dsi_cweaw_ewwow(stwuct nww_dsi *dsi)
{
	int wet = dsi->ewwow;

	dsi->ewwow = 0;
	wetuwn wet;
}

static void nww_dsi_wwite(stwuct nww_dsi *dsi, unsigned int weg, u32 vaw)
{
	int wet;

	if (dsi->ewwow)
		wetuwn;

	wet = wegmap_wwite(dsi->wegmap, weg, vaw);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev,
			      "Faiwed to wwite NWW DSI weg 0x%x: %d\n", weg,
			      wet);
		dsi->ewwow = wet;
	}
}

static u32 nww_dsi_wead(stwuct nww_dsi *dsi, u32 weg)
{
	unsigned int vaw;
	int wet;

	if (dsi->ewwow)
		wetuwn 0;

	wet = wegmap_wead(dsi->wegmap, weg, &vaw);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to wead NWW DSI weg 0x%x: %d\n",
			      weg, wet);
		dsi->ewwow = wet;
	}
	wetuwn vaw;
}

static int nww_dsi_get_dpi_pixew_fowmat(enum mipi_dsi_pixew_fowmat fowmat)
{
	switch (fowmat) {
	case MIPI_DSI_FMT_WGB565:
		wetuwn NWW_DSI_PIXEW_FOWMAT_16;
	case MIPI_DSI_FMT_WGB666:
		wetuwn NWW_DSI_PIXEW_FOWMAT_18W;
	case MIPI_DSI_FMT_WGB666_PACKED:
		wetuwn NWW_DSI_PIXEW_FOWMAT_18;
	case MIPI_DSI_FMT_WGB888:
		wetuwn NWW_DSI_PIXEW_FOWMAT_24;
	defauwt:
		wetuwn -EINVAW;
	}
}

/*
 * ps2bc - Picoseconds to byte cwock cycwes
 */
static u32 ps2bc(stwuct nww_dsi *dsi, unsigned wong wong ps)
{
	u32 bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);

	wetuwn DIV64_U64_WOUND_UP(ps * dsi->mode.cwock * bpp,
				  dsi->wanes * 8UWW * NSEC_PEW_SEC);
}

/*
 * ui2bc - UI time pewiods to byte cwock cycwes
 */
static u32 ui2bc(unsigned int ui)
{
	wetuwn DIV_WOUND_UP(ui, BITS_PEW_BYTE);
}

/*
 * us2bc - micwo seconds to wp cwock cycwes
 */
static u32 us2wp(u32 wp_cwk_wate, unsigned wong us)
{
	wetuwn DIV_WOUND_UP(us * wp_cwk_wate, USEC_PEW_SEC);
}

static int nww_dsi_config_host(stwuct nww_dsi *dsi)
{
	u32 cycwes;
	stwuct phy_configuwe_opts_mipi_dphy *cfg = &dsi->phy_cfg.mipi_dphy;

	if (dsi->wanes < 1 || dsi->wanes > 4)
		wetuwn -EINVAW;

	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "DSI Wanes %d\n", dsi->wanes);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_NUM_WANES, dsi->wanes - 1);

	if (dsi->dsi_mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS) {
		nww_dsi_wwite(dsi, NWW_DSI_CFG_NONCONTINUOUS_CWK, 0x01);
		nww_dsi_wwite(dsi, NWW_DSI_CFG_AUTOINSEWT_EOTP, 0x01);
	} ewse {
		nww_dsi_wwite(dsi, NWW_DSI_CFG_NONCONTINUOUS_CWK, 0x00);
		nww_dsi_wwite(dsi, NWW_DSI_CFG_AUTOINSEWT_EOTP, 0x00);
	}

	/* vawues in byte cwock cycwes */
	cycwes = ui2bc(cfg->cwk_pwe);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cfg_t_pwe: 0x%x\n", cycwes);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_T_PWE, cycwes);
	cycwes = ps2bc(dsi, cfg->wpx + cfg->cwk_pwepawe + cfg->cwk_zewo);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cfg_tx_gap (pwe): 0x%x\n", cycwes);
	cycwes += ui2bc(cfg->cwk_pwe);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cfg_t_post: 0x%x\n", cycwes);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_T_POST, cycwes);
	cycwes = ps2bc(dsi, cfg->hs_exit);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cfg_tx_gap: 0x%x\n", cycwes);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_TX_GAP, cycwes);

	nww_dsi_wwite(dsi, NWW_DSI_CFG_EXTWA_CMDS_AFTEW_EOTP, 0x01);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_HTX_TO_COUNT, 0x00);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_WWX_H_TO_COUNT, 0x00);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_BTA_H_TO_COUNT, 0x00);
	/* In WP cwock cycwes */
	cycwes = us2wp(cfg->wp_cwk_wate, cfg->wakeup);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cfg_twakeup: 0x%x\n", cycwes);
	nww_dsi_wwite(dsi, NWW_DSI_CFG_TWAKEUP, cycwes);

	wetuwn nww_dsi_cweaw_ewwow(dsi);
}

static int nww_dsi_config_dpi(stwuct nww_dsi *dsi)
{
	u32 mode;
	int cowow_fowmat;
	boow buwst_mode;
	int hfwont_powch, hback_powch, vfwont_powch, vback_powch;
	int hsync_wen, vsync_wen;

	hfwont_powch = dsi->mode.hsync_stawt - dsi->mode.hdispway;
	hsync_wen = dsi->mode.hsync_end - dsi->mode.hsync_stawt;
	hback_powch = dsi->mode.htotaw - dsi->mode.hsync_end;

	vfwont_powch = dsi->mode.vsync_stawt - dsi->mode.vdispway;
	vsync_wen = dsi->mode.vsync_end - dsi->mode.vsync_stawt;
	vback_powch = dsi->mode.vtotaw - dsi->mode.vsync_end;

	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "hfwont_powch = %d\n", hfwont_powch);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "hback_powch = %d\n", hback_powch);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "hsync_wen = %d\n", hsync_wen);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "hdispway = %d\n", dsi->mode.hdispway);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "vfwont_powch = %d\n", vfwont_powch);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "vback_powch = %d\n", vback_powch);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "vsync_wen = %d\n", vsync_wen);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "vactive = %d\n", dsi->mode.vdispway);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "cwock = %d kHz\n", dsi->mode.cwock);

	cowow_fowmat = nww_dsi_get_dpi_pixew_fowmat(dsi->fowmat);
	if (cowow_fowmat < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Invawid cowow fowmat 0x%x\n",
			      dsi->fowmat);
		wetuwn cowow_fowmat;
	}
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "pixew fmt = %d\n", dsi->fowmat);

	nww_dsi_wwite(dsi, NWW_DSI_INTEWFACE_COWOW_CODING, NWW_DSI_DPI_24_BIT);
	nww_dsi_wwite(dsi, NWW_DSI_PIXEW_FOWMAT, cowow_fowmat);
	/*
	 * Adjusting input powawity based on the video mode wesuwts in
	 * a bwack scween so awways pick active wow:
	 */
	nww_dsi_wwite(dsi, NWW_DSI_VSYNC_POWAWITY,
		      NWW_DSI_VSYNC_POWAWITY_ACTIVE_WOW);
	nww_dsi_wwite(dsi, NWW_DSI_HSYNC_POWAWITY,
		      NWW_DSI_HSYNC_POWAWITY_ACTIVE_WOW);

	buwst_mode = (dsi->dsi_mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) &&
		     !(dsi->dsi_mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE);

	if (buwst_mode) {
		nww_dsi_wwite(dsi, NWW_DSI_VIDEO_MODE, NWW_DSI_VM_BUWST_MODE);
		nww_dsi_wwite(dsi, NWW_DSI_PIXEW_FIFO_SEND_WEVEW, 256);
	} ewse {
		mode = ((dsi->dsi_mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) ?
				NWW_DSI_VM_BUWST_MODE_WITH_SYNC_PUWSES :
				NWW_DSI_VM_NON_BUWST_MODE_WITH_SYNC_EVENTS);
		nww_dsi_wwite(dsi, NWW_DSI_VIDEO_MODE, mode);
		nww_dsi_wwite(dsi, NWW_DSI_PIXEW_FIFO_SEND_WEVEW,
			      dsi->mode.hdispway);
	}

	nww_dsi_wwite(dsi, NWW_DSI_HFP, hfwont_powch);
	nww_dsi_wwite(dsi, NWW_DSI_HBP, hback_powch);
	nww_dsi_wwite(dsi, NWW_DSI_HSA, hsync_wen);

	nww_dsi_wwite(dsi, NWW_DSI_ENABWE_MUWT_PKTS, 0x0);
	nww_dsi_wwite(dsi, NWW_DSI_BWWP_MODE, 0x1);
	nww_dsi_wwite(dsi, NWW_DSI_USE_NUWW_PKT_BWWP, 0x0);
	nww_dsi_wwite(dsi, NWW_DSI_VC, 0x0);

	nww_dsi_wwite(dsi, NWW_DSI_PIXEW_PAYWOAD_SIZE, dsi->mode.hdispway);
	nww_dsi_wwite(dsi, NWW_DSI_VACTIVE, dsi->mode.vdispway - 1);
	nww_dsi_wwite(dsi, NWW_DSI_VBP, vback_powch);
	nww_dsi_wwite(dsi, NWW_DSI_VFP, vfwont_powch);

	wetuwn nww_dsi_cweaw_ewwow(dsi);
}

static int nww_dsi_init_intewwupts(stwuct nww_dsi *dsi)
{
	u32 iwq_enabwe = ~(u32)(NWW_DSI_TX_PKT_DONE_MASK |
				NWW_DSI_WX_PKT_HDW_WCVD_MASK |
				NWW_DSI_TX_FIFO_OVFWW_MASK |
				NWW_DSI_HS_TX_TIMEOUT_MASK);

	nww_dsi_wwite(dsi, NWW_DSI_IWQ_MASK, iwq_enabwe);
	nww_dsi_wwite(dsi, NWW_DSI_IWQ_MASK2, 0x7);

	wetuwn nww_dsi_cweaw_ewwow(dsi);
}

static int nww_dsi_host_attach(stwuct mipi_dsi_host *dsi_host,
			       stwuct mipi_dsi_device *device)
{
	stwuct nww_dsi *dsi = containew_of(dsi_host, stwuct nww_dsi, dsi_host);
	stwuct device *dev = dsi->dev;

	DWM_DEV_INFO(dev, "wanes=%u, fowmat=0x%x fwags=0x%wx\n", device->wanes,
		     device->fowmat, device->mode_fwags);

	if (device->wanes < 1 || device->wanes > 4)
		wetuwn -EINVAW;

	dsi->wanes = device->wanes;
	dsi->fowmat = device->fowmat;
	dsi->dsi_mode_fwags = device->mode_fwags;

	wetuwn 0;
}

static boow nww_dsi_wead_packet(stwuct nww_dsi *dsi, u32 status)
{
	stwuct device *dev = dsi->dev;
	stwuct nww_dsi_twansfew *xfew = dsi->xfew;
	int eww;
	u8 *paywoad = xfew->msg->wx_buf;
	u32 vaw;
	u16 wowd_count;
	u8 channew;
	u8 data_type;

	xfew->status = 0;

	if (xfew->wx_wowd_count == 0) {
		if (!(status & NWW_DSI_WX_PKT_HDW_WCVD))
			wetuwn fawse;
		/* Get the WX headew and pawse it */
		vaw = nww_dsi_wead(dsi, NWW_DSI_WX_PKT_HEADEW);
		eww = nww_dsi_cweaw_ewwow(dsi);
		if (eww)
			xfew->status = eww;
		wowd_count = NWW_DSI_WC(vaw);
		channew = NWW_DSI_WX_VC(vaw);
		data_type = NWW_DSI_WX_DT(vaw);

		if (channew != xfew->msg->channew) {
			DWM_DEV_EWWOW(dev,
				      "[%02X] Channew mismatch (%u != %u)\n",
				      xfew->cmd, channew, xfew->msg->channew);
			xfew->status = -EINVAW;
			wetuwn twue;
		}

		switch (data_type) {
		case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_2BYTE:
		case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_2BYTE:
			if (xfew->msg->wx_wen > 1) {
				/* wead second byte */
				paywoad[1] = wowd_count >> 8;
				++xfew->wx_wen;
			}
			fawwthwough;
		case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_1BYTE:
		case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_1BYTE:
			if (xfew->msg->wx_wen > 0) {
				/* wead fiwst byte */
				paywoad[0] = wowd_count & 0xff;
				++xfew->wx_wen;
			}
			xfew->status = xfew->wx_wen;
			wetuwn twue;
		case MIPI_DSI_WX_ACKNOWWEDGE_AND_EWWOW_WEPOWT:
			wowd_count &= 0xff;
			DWM_DEV_EWWOW(dev, "[%02X] DSI ewwow wepowt: 0x%02x\n",
				      xfew->cmd, wowd_count);
			xfew->status = -EPWOTO;
			wetuwn twue;
		}

		if (wowd_count > xfew->msg->wx_wen) {
			DWM_DEV_EWWOW(dev,
				"[%02X] Weceive buffew too smaww: %zu (< %u)\n",
				xfew->cmd, xfew->msg->wx_wen, wowd_count);
			xfew->status = -EINVAW;
			wetuwn twue;
		}

		xfew->wx_wowd_count = wowd_count;
	} ewse {
		/* Set wowd_count fwom pwevious headew wead */
		wowd_count = xfew->wx_wowd_count;
	}

	/* If WX paywoad is not yet weceived, wait fow it */
	if (!(status & NWW_DSI_WX_PKT_PAYWOAD_DATA_WCVD))
		wetuwn fawse;

	/* Wead the WX paywoad */
	whiwe (wowd_count >= 4) {
		vaw = nww_dsi_wead(dsi, NWW_DSI_WX_PAYWOAD);
		paywoad[0] = (vaw >> 0) & 0xff;
		paywoad[1] = (vaw >> 8) & 0xff;
		paywoad[2] = (vaw >> 16) & 0xff;
		paywoad[3] = (vaw >> 24) & 0xff;
		paywoad += 4;
		xfew->wx_wen += 4;
		wowd_count -= 4;
	}

	if (wowd_count > 0) {
		vaw = nww_dsi_wead(dsi, NWW_DSI_WX_PAYWOAD);
		switch (wowd_count) {
		case 3:
			paywoad[2] = (vaw >> 16) & 0xff;
			++xfew->wx_wen;
			fawwthwough;
		case 2:
			paywoad[1] = (vaw >> 8) & 0xff;
			++xfew->wx_wen;
			fawwthwough;
		case 1:
			paywoad[0] = (vaw >> 0) & 0xff;
			++xfew->wx_wen;
			bweak;
		}
	}

	xfew->status = xfew->wx_wen;
	eww = nww_dsi_cweaw_ewwow(dsi);
	if (eww)
		xfew->status = eww;

	wetuwn twue;
}

static void nww_dsi_finish_twansmission(stwuct nww_dsi *dsi, u32 status)
{
	stwuct nww_dsi_twansfew *xfew = dsi->xfew;
	boow end_packet = fawse;

	if (!xfew)
		wetuwn;

	if (xfew->diwection == DSI_PACKET_SEND &&
	    status & NWW_DSI_TX_PKT_DONE) {
		xfew->status = xfew->tx_wen;
		end_packet = twue;
	} ewse if (status & NWW_DSI_DPHY_DIWECTION &&
		   ((status & (NWW_DSI_WX_PKT_HDW_WCVD |
			       NWW_DSI_WX_PKT_PAYWOAD_DATA_WCVD)))) {
		end_packet = nww_dsi_wead_packet(dsi, status);
	}

	if (end_packet)
		compwete(&xfew->compweted);
}

static void nww_dsi_begin_twansmission(stwuct nww_dsi *dsi)
{
	stwuct nww_dsi_twansfew *xfew = dsi->xfew;
	stwuct mipi_dsi_packet *pkt = &xfew->packet;
	const u8 *paywoad;
	size_t wength;
	u16 wowd_count;
	u8 hs_mode;
	u32 vaw;
	u32 hs_wowkawound = 0;

	/* Send the paywoad, if any */
	wength = pkt->paywoad_wength;
	paywoad = pkt->paywoad;

	whiwe (wength >= 4) {
		vaw = *(u32 *)paywoad;
		hs_wowkawound |= !(vaw & 0xFFFF00);
		nww_dsi_wwite(dsi, NWW_DSI_TX_PAYWOAD, vaw);
		paywoad += 4;
		wength -= 4;
	}
	/* Send the west of the paywoad */
	vaw = 0;
	switch (wength) {
	case 3:
		vaw |= paywoad[2] << 16;
		fawwthwough;
	case 2:
		vaw |= paywoad[1] << 8;
		hs_wowkawound |= !(vaw & 0xFFFF00);
		fawwthwough;
	case 1:
		vaw |= paywoad[0];
		nww_dsi_wwite(dsi, NWW_DSI_TX_PAYWOAD, vaw);
		bweak;
	}
	xfew->tx_wen = pkt->paywoad_wength;

	/*
	 * Send the headew
	 * headew[0] = Viwtuaw Channew + Data Type
	 * headew[1] = Wowd Count WSB (WP) ow fiwst pawam (SP)
	 * headew[2] = Wowd Count MSB (WP) ow second pawam (SP)
	 */
	wowd_count = pkt->headew[1] | (pkt->headew[2] << 8);
	if (hs_wowkawound && (dsi->quiwks & E11418_HS_MODE_QUIWK)) {
		DWM_DEV_DEBUG_DWIVEW(dsi->dev,
				     "Using hs mode wowkawound fow cmd 0x%x\n",
				     xfew->cmd);
		hs_mode = 1;
	} ewse {
		hs_mode = (xfew->msg->fwags & MIPI_DSI_MSG_USE_WPM) ? 0 : 1;
	}
	vaw = NWW_DSI_WC(wowd_count) | NWW_DSI_TX_VC(xfew->msg->channew) |
	      NWW_DSI_TX_DT(xfew->msg->type) | NWW_DSI_HS_SEW(hs_mode) |
	      NWW_DSI_BTA_TX(xfew->need_bta);
	nww_dsi_wwite(dsi, NWW_DSI_PKT_CONTWOW, vaw);

	/* Send packet command */
	nww_dsi_wwite(dsi, NWW_DSI_SEND_PACKET, 0x1);
}

static ssize_t nww_dsi_host_twansfew(stwuct mipi_dsi_host *dsi_host,
				     const stwuct mipi_dsi_msg *msg)
{
	stwuct nww_dsi *dsi = containew_of(dsi_host, stwuct nww_dsi, dsi_host);
	stwuct nww_dsi_twansfew xfew;
	ssize_t wet = 0;

	/* Cweate packet to be sent */
	dsi->xfew = &xfew;
	wet = mipi_dsi_cweate_packet(&xfew.packet, msg);
	if (wet < 0) {
		dsi->xfew = NUWW;
		wetuwn wet;
	}

	if ((msg->type & MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM ||
	     msg->type & MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM ||
	     msg->type & MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM ||
	     msg->type & MIPI_DSI_DCS_WEAD) &&
	    msg->wx_wen > 0 && msg->wx_buf)
		xfew.diwection = DSI_PACKET_WECEIVE;
	ewse
		xfew.diwection = DSI_PACKET_SEND;

	xfew.need_bta = (xfew.diwection == DSI_PACKET_WECEIVE);
	xfew.need_bta |= (msg->fwags & MIPI_DSI_MSG_WEQ_ACK) ? 1 : 0;
	xfew.msg = msg;
	xfew.status = -ETIMEDOUT;
	xfew.wx_wowd_count = 0;
	xfew.wx_wen = 0;
	xfew.cmd = 0x00;
	if (msg->tx_wen > 0)
		xfew.cmd = ((u8 *)(msg->tx_buf))[0];
	init_compwetion(&xfew.compweted);

	wet = cwk_pwepawe_enabwe(dsi->wx_esc_cwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to enabwe wx_esc cwk: %zd\n",
			      wet);
		wetuwn wet;
	}
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "Enabwed wx_esc cwk @%wu Hz\n",
			     cwk_get_wate(dsi->wx_esc_cwk));

	/* Initiate the DSI packet twansmision */
	nww_dsi_begin_twansmission(dsi);

	if (!wait_fow_compwetion_timeout(&xfew.compweted,
					 NWW_DSI_MIPI_FIFO_TIMEOUT)) {
		DWM_DEV_EWWOW(dsi_host->dev, "[%02X] DSI twansfew timed out\n",
			      xfew.cmd);
		wet = -ETIMEDOUT;
	} ewse {
		wet = xfew.status;
	}

	cwk_disabwe_unpwepawe(dsi->wx_esc_cwk);

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops nww_dsi_host_ops = {
	.attach = nww_dsi_host_attach,
	.twansfew = nww_dsi_host_twansfew,
};

static iwqwetuwn_t nww_dsi_iwq_handwew(int iwq, void *data)
{
	u32 iwq_status;
	stwuct nww_dsi *dsi = data;

	iwq_status = nww_dsi_wead(dsi, NWW_DSI_IWQ_STATUS);

	if (iwq_status & NWW_DSI_TX_FIFO_OVFWW)
		DWM_DEV_EWWOW_WATEWIMITED(dsi->dev, "tx fifo ovewfwow\n");

	if (iwq_status & NWW_DSI_HS_TX_TIMEOUT)
		DWM_DEV_EWWOW_WATEWIMITED(dsi->dev, "HS tx timeout\n");

	if (iwq_status & NWW_DSI_TX_PKT_DONE ||
	    iwq_status & NWW_DSI_WX_PKT_HDW_WCVD ||
	    iwq_status & NWW_DSI_WX_PKT_PAYWOAD_DATA_WCVD)
		nww_dsi_finish_twansmission(dsi, iwq_status);

	wetuwn IWQ_HANDWED;
}

static int nww_dsi_mode_set(stwuct nww_dsi *dsi)
{
	stwuct device *dev = dsi->dev;
	union phy_configuwe_opts *phy_cfg = &dsi->phy_cfg;
	int wet;

	if (!dsi->wanes) {
		DWM_DEV_EWWOW(dev, "Need DSI wanes: %d\n", dsi->wanes);
		wetuwn -EINVAW;
	}

	wet = phy_init(dsi->phy);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to init DSI phy: %d\n", wet);
		wetuwn wet;
	}

	wet = phy_set_mode(dsi->phy, PHY_MODE_MIPI_DPHY);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to set DSI phy mode: %d\n", wet);
		goto uninit_phy;
	}

	wet = phy_configuwe(dsi->phy, phy_cfg);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to configuwe DSI phy: %d\n", wet);
		goto uninit_phy;
	}

	wet = cwk_pwepawe_enabwe(dsi->tx_esc_cwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to enabwe tx_esc cwk: %d\n",
			      wet);
		goto uninit_phy;
	}
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "Enabwed tx_esc cwk @%wu Hz\n",
			     cwk_get_wate(dsi->tx_esc_cwk));

	wet = nww_dsi_config_host(dsi);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to set up DSI: %d", wet);
		goto disabwe_cwock;
	}

	wet = nww_dsi_config_dpi(dsi);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to set up DPI: %d", wet);
		goto disabwe_cwock;
	}

	wet = phy_powew_on(dsi->phy);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to powew on DPHY (%d)\n", wet);
		goto disabwe_cwock;
	}

	wet = nww_dsi_init_intewwupts(dsi);
	if (wet < 0)
		goto powew_off_phy;

	wetuwn wet;

powew_off_phy:
	phy_powew_off(dsi->phy);
disabwe_cwock:
	cwk_disabwe_unpwepawe(dsi->tx_esc_cwk);
uninit_phy:
	phy_exit(dsi->phy);

	wetuwn wet;
}

static int nww_dsi_disabwe(stwuct nww_dsi *dsi)
{
	stwuct device *dev = dsi->dev;

	DWM_DEV_DEBUG_DWIVEW(dev, "Disabwing cwocks and phy\n");

	phy_powew_off(dsi->phy);
	phy_exit(dsi->phy);

	/* Disabwing the cwock befowe the phy bweaks enabwing dsi again */
	cwk_disabwe_unpwepawe(dsi->tx_esc_cwk);

	wetuwn 0;
}

static void
nww_dsi_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
			      stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct nww_dsi *dsi = bwidge_to_dsi(bwidge);
	int wet;

	nww_dsi_disabwe(dsi);

	wet = weset_contwow_assewt(dsi->wst_dpi);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to assewt DPI: %d\n", wet);
		wetuwn;
	}
	wet = weset_contwow_assewt(dsi->wst_byte);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to assewt ESC: %d\n", wet);
		wetuwn;
	}
	wet = weset_contwow_assewt(dsi->wst_esc);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to assewt BYTE: %d\n", wet);
		wetuwn;
	}
	wet = weset_contwow_assewt(dsi->wst_pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to assewt PCWK: %d\n", wet);
		wetuwn;
	}

	cwk_disabwe_unpwepawe(dsi->cowe_cwk);
	cwk_disabwe_unpwepawe(dsi->wcdif_cwk);

	pm_wuntime_put(dsi->dev);
}

static int nww_dsi_get_dphy_pawams(stwuct nww_dsi *dsi,
				   const stwuct dwm_dispway_mode *mode,
				   union phy_configuwe_opts *phy_opts)
{
	unsigned wong wate;
	int wet;

	if (dsi->wanes < 1 || dsi->wanes > 4)
		wetuwn -EINVAW;

	/*
	 * So faw the DPHY spec minimaw timings wowk fow both mixew
	 * dphy and nww dsi host
	 */
	wet = phy_mipi_dphy_get_defauwt_config(mode->cwock * 1000,
		mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat), dsi->wanes,
		&phy_opts->mipi_dphy);
	if (wet < 0)
		wetuwn wet;

	wate = cwk_get_wate(dsi->tx_esc_cwk);
	DWM_DEV_DEBUG_DWIVEW(dsi->dev, "WP cwk is @%wu Hz\n", wate);
	phy_opts->mipi_dphy.wp_cwk_wate = wate;

	wetuwn 0;
}

static enum dwm_mode_status
nww_dsi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			  const stwuct dwm_dispway_info *info,
			  const stwuct dwm_dispway_mode *mode)
{
	stwuct nww_dsi *dsi = bwidge_to_dsi(bwidge);
	int bpp = mipi_dsi_pixew_fowmat_to_bpp(dsi->fowmat);

	if (mode->cwock * bpp > 15000000 * dsi->wanes)
		wetuwn MODE_CWOCK_HIGH;

	if (mode->cwock * bpp < 80000 * dsi->wanes)
		wetuwn MODE_CWOCK_WOW;

	wetuwn MODE_OK;
}

static int nww_dsi_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				       stwuct dwm_bwidge_state *bwidge_state,
				       stwuct dwm_cwtc_state *cwtc_state,
				       stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;

	/* At weast WCDIF + NWW needs active high sync */
	adjusted_mode->fwags |= (DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC);
	adjusted_mode->fwags &= ~(DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC);

	/*
	 * Do a fuww modeset if cwtc_state->active is changed to be twue.
	 * This ensuwes ouw ->mode_set() is cawwed to get the DSI contwowwew
	 * and the PHY weady to send DCS commands, when onwy the connectow's
	 * DPMS is bwought out of "Off" status.
	 */
	if (cwtc_state->active_changed && cwtc_state->active)
		cwtc_state->mode_changed = twue;

	wetuwn 0;
}

static void
nww_dsi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
			const stwuct dwm_dispway_mode *mode,
			const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct nww_dsi *dsi = bwidge_to_dsi(bwidge);
	stwuct device *dev = dsi->dev;
	union phy_configuwe_opts new_cfg;
	unsigned wong phy_wef_wate;
	int wet;

	wet = nww_dsi_get_dphy_pawams(dsi, adjusted_mode, &new_cfg);
	if (wet < 0)
		wetuwn;

	phy_wef_wate = cwk_get_wate(dsi->phy_wef_cwk);
	DWM_DEV_DEBUG_DWIVEW(dev, "PHY at wef wate: %wu\n", phy_wef_wate);
	/* Save the new desiwed phy config */
	memcpy(&dsi->phy_cfg, &new_cfg, sizeof(new_cfg));

	dwm_mode_copy(&dsi->mode, adjusted_mode);
	dwm_mode_debug_pwintmodewine(adjusted_mode);

	if (pm_wuntime_wesume_and_get(dev) < 0)
		wetuwn;

	if (cwk_pwepawe_enabwe(dsi->wcdif_cwk) < 0)
		goto wuntime_put;
	if (cwk_pwepawe_enabwe(dsi->cowe_cwk) < 0)
		goto wuntime_put;

	/* Step 1 fwom DSI weset-out instwuctions */
	wet = weset_contwow_deassewt(dsi->wst_pcwk);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to deassewt PCWK: %d\n", wet);
		goto wuntime_put;
	}

	/* Step 2 fwom DSI weset-out instwuctions */
	nww_dsi_mode_set(dsi);

	/* Step 3 fwom DSI weset-out instwuctions */
	wet = weset_contwow_deassewt(dsi->wst_esc);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to deassewt ESC: %d\n", wet);
		goto wuntime_put;
	}
	wet = weset_contwow_deassewt(dsi->wst_byte);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to deassewt BYTE: %d\n", wet);
		goto wuntime_put;
	}

	wetuwn;

wuntime_put:
	pm_wuntime_put_sync(dev);
}

static void
nww_dsi_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
			     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct nww_dsi *dsi = bwidge_to_dsi(bwidge);
	int wet;

	/* Step 5 fwom DSI weset-out instwuctions */
	wet = weset_contwow_deassewt(dsi->wst_dpi);
	if (wet < 0)
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to deassewt DPI: %d\n", wet);
}

static int nww_dsi_bwidge_attach(stwuct dwm_bwidge *bwidge,
				 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct nww_dsi *dsi = bwidge_to_dsi(bwidge);
	stwuct dwm_bwidge *panew_bwidge;

	panew_bwidge = devm_dwm_of_get_bwidge(dsi->dev, dsi->dev->of_node, 1, 0);
	if (IS_EWW(panew_bwidge))
		wetuwn PTW_EWW(panew_bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, panew_bwidge, bwidge, fwags);
}

static u32 *nww_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						 stwuct dwm_bwidge_state *bwidge_state,
						 stwuct dwm_cwtc_state *cwtc_state,
						 stwuct dwm_connectow_state *conn_state,
						 u32 output_fmt,
						 unsigned int *num_input_fmts)
{
	u32 *input_fmts, input_fmt;

	*num_input_fmts = 0;

	switch (output_fmt) {
	/* If MEDIA_BUS_FMT_FIXED is tested, wetuwn defauwt bus fowmat */
	case MEDIA_BUS_FMT_FIXED:
		input_fmt = MEDIA_BUS_FMT_WGB888_1X24;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X24:
	case MEDIA_BUS_FMT_WGB666_1X18:
	case MEDIA_BUS_FMT_WGB565_1X16:
		input_fmt = output_fmt;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	input_fmts = kcawwoc(1, sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;
	input_fmts[0] = input_fmt;
	*num_input_fmts = 1;

	wetuwn input_fmts;
}

static const stwuct dwm_bwidge_funcs nww_dsi_bwidge_funcs = {
	.atomic_dupwicate_state	= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset		= dwm_atomic_hewpew_bwidge_weset,
	.atomic_check		= nww_dsi_bwidge_atomic_check,
	.atomic_enabwe		= nww_dsi_bwidge_atomic_enabwe,
	.atomic_disabwe		= nww_dsi_bwidge_atomic_disabwe,
	.atomic_get_input_bus_fmts = nww_bwidge_atomic_get_input_bus_fmts,
	.mode_set		= nww_dsi_bwidge_mode_set,
	.mode_vawid		= nww_dsi_bwidge_mode_vawid,
	.attach			= nww_dsi_bwidge_attach,
};

static int nww_dsi_pawse_dt(stwuct nww_dsi *dsi)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dsi->dev);
	stwuct cwk *cwk;
	void __iomem *base;
	int wet;

	dsi->phy = devm_phy_get(dsi->dev, "dphy");
	if (IS_EWW(dsi->phy)) {
		wet = PTW_EWW(dsi->phy);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dsi->dev, "Couwd not get PHY: %d\n", wet);
		wetuwn wet;
	}

	cwk = devm_cwk_get(dsi->dev, "wcdif");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get wcdif cwock: %d\n",
			      wet);
		wetuwn wet;
	}
	dsi->wcdif_cwk = cwk;

	cwk = devm_cwk_get(dsi->dev, "cowe");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get cowe cwock: %d\n",
			      wet);
		wetuwn wet;
	}
	dsi->cowe_cwk = cwk;

	cwk = devm_cwk_get(dsi->dev, "phy_wef");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get phy_wef cwock: %d\n",
			      wet);
		wetuwn wet;
	}
	dsi->phy_wef_cwk = cwk;

	cwk = devm_cwk_get(dsi->dev, "wx_esc");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get wx_esc cwock: %d\n",
			      wet);
		wetuwn wet;
	}
	dsi->wx_esc_cwk = cwk;

	cwk = devm_cwk_get(dsi->dev, "tx_esc");
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get tx_esc cwock: %d\n",
			      wet);
		wetuwn wet;
	}
	dsi->tx_esc_cwk = cwk;

	dsi->mux = devm_mux_contwow_get(dsi->dev, NUWW);
	if (IS_EWW(dsi->mux)) {
		wet = PTW_EWW(dsi->mux);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dsi->dev, "Faiwed to get mux: %d\n", wet);
		wetuwn wet;
	}

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dsi->wegmap =
		devm_wegmap_init_mmio(dsi->dev, base, &nww_dsi_wegmap_config);
	if (IS_EWW(dsi->wegmap)) {
		wet = PTW_EWW(dsi->wegmap);
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to cweate NWW DSI wegmap: %d\n",
			      wet);
		wetuwn wet;
	}

	dsi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dsi->iwq < 0) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get device IWQ: %d\n",
			      dsi->iwq);
		wetuwn dsi->iwq;
	}

	dsi->wst_pcwk = devm_weset_contwow_get_excwusive(dsi->dev, "pcwk");
	if (IS_EWW(dsi->wst_pcwk)) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get pcwk weset: %wd\n",
			      PTW_EWW(dsi->wst_pcwk));
		wetuwn PTW_EWW(dsi->wst_pcwk);
	}
	dsi->wst_byte = devm_weset_contwow_get_excwusive(dsi->dev, "byte");
	if (IS_EWW(dsi->wst_byte)) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get byte weset: %wd\n",
			      PTW_EWW(dsi->wst_byte));
		wetuwn PTW_EWW(dsi->wst_byte);
	}
	dsi->wst_esc = devm_weset_contwow_get_excwusive(dsi->dev, "esc");
	if (IS_EWW(dsi->wst_esc)) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get esc weset: %wd\n",
			      PTW_EWW(dsi->wst_esc));
		wetuwn PTW_EWW(dsi->wst_esc);
	}
	dsi->wst_dpi = devm_weset_contwow_get_excwusive(dsi->dev, "dpi");
	if (IS_EWW(dsi->wst_dpi)) {
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to get dpi weset: %wd\n",
			      PTW_EWW(dsi->wst_dpi));
		wetuwn PTW_EWW(dsi->wst_dpi);
	}
	wetuwn 0;
}

static int nww_dsi_sewect_input(stwuct nww_dsi *dsi)
{
	stwuct device_node *wemote;
	u32 use_dcss = 1;
	int wet;

	wemote = of_gwaph_get_wemote_node(dsi->dev->of_node, 0,
					  NWW_DSI_ENDPOINT_WCDIF);
	if (wemote) {
		use_dcss = 0;
	} ewse {
		wemote = of_gwaph_get_wemote_node(dsi->dev->of_node, 0,
						  NWW_DSI_ENDPOINT_DCSS);
		if (!wemote) {
			DWM_DEV_EWWOW(dsi->dev,
				      "No vawid input endpoint found\n");
			wetuwn -EINVAW;
		}
	}

	DWM_DEV_INFO(dsi->dev, "Using %s as input souwce\n",
		     (use_dcss) ? "DCSS" : "WCDIF");
	wet = mux_contwow_twy_sewect(dsi->mux, use_dcss);
	if (wet < 0)
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to sewect input: %d\n", wet);

	of_node_put(wemote);
	wetuwn wet;
}

static int nww_dsi_desewect_input(stwuct nww_dsi *dsi)
{
	int wet;

	wet = mux_contwow_desewect(dsi->mux);
	if (wet < 0)
		DWM_DEV_EWWOW(dsi->dev, "Faiwed to desewect input: %d\n", wet);

	wetuwn wet;
}

static const stwuct dwm_bwidge_timings nww_dsi_timings = {
	.input_bus_fwags = DWM_BUS_FWAG_DE_WOW,
};

static const stwuct of_device_id nww_dsi_dt_ids[] = {
	{ .compatibwe = "fsw,imx8mq-nww-dsi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, nww_dsi_dt_ids);

static const stwuct soc_device_attwibute nww_dsi_quiwks_match[] = {
	{ .soc_id = "i.MX8MQ", .wevision = "2.0",
	  .data = (void *)E11418_HS_MODE_QUIWK },
	{ /* sentinew. */ }
};

static int nww_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct soc_device_attwibute *attw;
	stwuct nww_dsi *dsi;
	int wet;

	dsi = devm_kzawwoc(dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsi->dev = dev;

	wet = nww_dsi_pawse_dt(dsi);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, dsi->iwq, nww_dsi_iwq_handwew, 0,
			       dev_name(dev), dsi);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "Faiwed to wequest IWQ %d: %d\n", dsi->iwq,
			      wet);
		wetuwn wet;
	}

	dsi->dsi_host.ops = &nww_dsi_host_ops;
	dsi->dsi_host.dev = dev;
	wet = mipi_dsi_host_wegistew(&dsi->dsi_host);
	if (wet) {
		DWM_DEV_EWWOW(dev, "Faiwed to wegistew MIPI host: %d\n", wet);
		wetuwn wet;
	}

	attw = soc_device_match(nww_dsi_quiwks_match);
	if (attw)
		dsi->quiwks = (uintptw_t)attw->data;

	dsi->bwidge.dwivew_pwivate = dsi;
	dsi->bwidge.funcs = &nww_dsi_bwidge_funcs;
	dsi->bwidge.of_node = dev->of_node;
	dsi->bwidge.timings = &nww_dsi_timings;

	dev_set_dwvdata(dev, dsi);
	pm_wuntime_enabwe(dev);

	wet = nww_dsi_sewect_input(dsi);
	if (wet < 0) {
		pm_wuntime_disabwe(dev);
		mipi_dsi_host_unwegistew(&dsi->dsi_host);
		wetuwn wet;
	}

	dwm_bwidge_add(&dsi->bwidge);
	wetuwn 0;
}

static void nww_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nww_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	nww_dsi_desewect_input(dsi);
	mipi_dsi_host_unwegistew(&dsi->dsi_host);
	dwm_bwidge_wemove(&dsi->bwidge);
	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct pwatfowm_dwivew nww_dsi_dwivew = {
	.pwobe		= nww_dsi_pwobe,
	.wemove_new	= nww_dsi_wemove,
	.dwivew		= {
		.of_match_tabwe = nww_dsi_dt_ids,
		.name	= DWV_NAME,
	},
};

moduwe_pwatfowm_dwivew(nww_dsi_dwivew);

MODUWE_AUTHOW("NXP Semiconductow");
MODUWE_AUTHOW("Puwism SPC");
MODUWE_DESCWIPTION("Nowthwest Wogic MIPI-DSI dwivew");
MODUWE_WICENSE("GPW"); /* GPWv2 ow watew */
