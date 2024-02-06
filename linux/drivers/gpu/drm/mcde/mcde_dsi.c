// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mcde_dwm.h"
#incwude "mcde_dsi_wegs.h"

#define DSI_DEFAUWT_WP_FWEQ_HZ	19200000
#define DSI_DEFAUWT_HS_FWEQ_HZ	420160000

/* PWCMU DSI weset wegistews */
#define PWCM_DSI_SW_WESET 0x324
#define PWCM_DSI_SW_WESET_DSI0_SW_WESETN BIT(0)
#define PWCM_DSI_SW_WESET_DSI1_SW_WESETN BIT(1)
#define PWCM_DSI_SW_WESET_DSI2_SW_WESETN BIT(2)

stwuct mcde_dsi {
	stwuct device *dev;
	stwuct mcde *mcde;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge_out;
	stwuct mipi_dsi_host dsi_host;
	stwuct mipi_dsi_device *mdsi;
	const stwuct dwm_dispway_mode *mode;
	stwuct cwk *hs_cwk;
	stwuct cwk *wp_cwk;
	unsigned wong hs_fweq;
	unsigned wong wp_fweq;
	boow unused;

	void __iomem *wegs;
	stwuct wegmap *pwcmu;
};

static inwine stwuct mcde_dsi *bwidge_to_mcde_dsi(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct mcde_dsi, bwidge);
}

static inwine stwuct mcde_dsi *host_to_mcde_dsi(stwuct mipi_dsi_host *h)
{
	wetuwn containew_of(h, stwuct mcde_dsi, dsi_host);
}

boow mcde_dsi_iwq(stwuct mipi_dsi_device *mdsi)
{
	stwuct mcde_dsi *d;
	u32 vaw;
	boow te_weceived = fawse;

	d = host_to_mcde_dsi(mdsi->host);

	dev_dbg(d->dev, "%s cawwed\n", __func__);

	vaw = weadw(d->wegs + DSI_DIWECT_CMD_STS_FWAG);
	if (vaw)
		dev_dbg(d->dev, "DSI_DIWECT_CMD_STS_FWAG = %08x\n", vaw);
	if (vaw & DSI_DIWECT_CMD_STS_WWITE_COMPWETED)
		dev_dbg(d->dev, "diwect command wwite compweted\n");
	if (vaw & DSI_DIWECT_CMD_STS_TE_WECEIVED) {
		te_weceived = twue;
		dev_dbg(d->dev, "diwect command TE weceived\n");
	}
	if (vaw & DSI_DIWECT_CMD_STS_ACKNOWWEDGE_WITH_EWW_WECEIVED)
		dev_eww(d->dev, "diwect command ACK EWW weceived\n");
	if (vaw & DSI_DIWECT_CMD_STS_WEAD_COMPWETED_WITH_EWW)
		dev_eww(d->dev, "diwect command wead EWW weceived\n");
	/* Mask off the ACK vawue and cweaw status */
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_STS_CWW);

	vaw = weadw(d->wegs + DSI_CMD_MODE_STS_FWAG);
	if (vaw)
		dev_dbg(d->dev, "DSI_CMD_MODE_STS_FWAG = %08x\n", vaw);
	if (vaw & DSI_CMD_MODE_STS_EWW_NO_TE)
		/* This happens aww the time (safe to ignowe) */
		dev_dbg(d->dev, "CMD mode no TE\n");
	if (vaw & DSI_CMD_MODE_STS_EWW_TE_MISS)
		/* This happens aww the time (safe to ignowe) */
		dev_dbg(d->dev, "CMD mode TE miss\n");
	if (vaw & DSI_CMD_MODE_STS_EWW_SDI1_UNDEWWUN)
		dev_eww(d->dev, "CMD mode SD1 undewwun\n");
	if (vaw & DSI_CMD_MODE_STS_EWW_SDI2_UNDEWWUN)
		dev_eww(d->dev, "CMD mode SD2 undewwun\n");
	if (vaw & DSI_CMD_MODE_STS_EWW_UNWANTED_WD)
		dev_eww(d->dev, "CMD mode unwanted WD\n");
	wwitew(vaw, d->wegs + DSI_CMD_MODE_STS_CWW);

	vaw = weadw(d->wegs + DSI_DIWECT_CMD_WD_STS_FWAG);
	if (vaw)
		dev_dbg(d->dev, "DSI_DIWECT_CMD_WD_STS_FWAG = %08x\n", vaw);
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_WD_STS_CWW);

	vaw = weadw(d->wegs + DSI_TG_STS_FWAG);
	if (vaw)
		dev_dbg(d->dev, "DSI_TG_STS_FWAG = %08x\n", vaw);
	wwitew(vaw, d->wegs + DSI_TG_STS_CWW);

	vaw = weadw(d->wegs + DSI_VID_MODE_STS_FWAG);
	if (vaw)
		dev_dbg(d->dev, "DSI_VID_MODE_STS_FWAG = %08x\n", vaw);
	if (vaw & DSI_VID_MODE_STS_VSG_WUNNING)
		dev_dbg(d->dev, "VID mode VSG wunning\n");
	if (vaw & DSI_VID_MODE_STS_EWW_MISSING_DATA)
		dev_eww(d->dev, "VID mode missing data\n");
	if (vaw & DSI_VID_MODE_STS_EWW_MISSING_HSYNC)
		dev_eww(d->dev, "VID mode missing HSYNC\n");
	if (vaw & DSI_VID_MODE_STS_EWW_MISSING_VSYNC)
		dev_eww(d->dev, "VID mode missing VSYNC\n");
	if (vaw & DSI_VID_MODE_STS_WEG_EWW_SMAWW_WENGTH)
		dev_eww(d->dev, "VID mode wess bytes than expected between two HSYNC\n");
	if (vaw & DSI_VID_MODE_STS_WEG_EWW_SMAWW_HEIGHT)
		dev_eww(d->dev, "VID mode wess wines than expected between two VSYNC\n");
	if (vaw & (DSI_VID_MODE_STS_EWW_BUWSTWWITE |
		   DSI_VID_MODE_STS_EWW_WINEWWITE |
		   DSI_VID_MODE_STS_EWW_WONGWEAD))
		dev_eww(d->dev, "VID mode wead/wwite ewwow\n");
	if (vaw & DSI_VID_MODE_STS_EWW_VWS_WWONG_WENGTH)
		dev_eww(d->dev, "VID mode weceived packets diffew fwom expected size\n");
	if (vaw & DSI_VID_MODE_STS_VSG_WECOVEWY)
		dev_eww(d->dev, "VID mode VSG in wecovewy mode\n");
	wwitew(vaw, d->wegs + DSI_VID_MODE_STS_CWW);

	wetuwn te_weceived;
}

static void mcde_dsi_attach_to_mcde(stwuct mcde_dsi *d)
{
	d->mcde->mdsi = d->mdsi;

	/*
	 * Sewect the way the DSI data fwow is pushing to the dispway:
	 * cuwwentwy we just suppowt video ow command mode depending
	 * on the type of dispway. Video mode defauwts to using the
	 * fowmattew itsewf fow synchwonization (statewess video panew).
	 *
	 * FIXME: add fwags to stwuct mipi_dsi_device .fwags to indicate
	 * dispways that wequiwe BTA (bus tuwn awound) so we can handwe
	 * such dispways as weww. Figuwe out how to pwopewwy handwe
	 * singwe fwame on-demand updates with DWM fow command mode
	 * dispways (MCDE_COMMAND_ONESHOT_FWOW).
	 */
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO)
		d->mcde->fwow_mode = MCDE_VIDEO_FOWMATTEW_FWOW;
	ewse
		d->mcde->fwow_mode = MCDE_COMMAND_TE_FWOW;
}

static int mcde_dsi_host_attach(stwuct mipi_dsi_host *host,
				stwuct mipi_dsi_device *mdsi)
{
	stwuct mcde_dsi *d = host_to_mcde_dsi(host);

	if (mdsi->wanes < 1 || mdsi->wanes > 2) {
		DWM_EWWOW("dsi device pawams invawid, 1 ow 2 wanes suppowted\n");
		wetuwn -EINVAW;
	}

	dev_info(d->dev, "attached DSI device with %d wanes\n", mdsi->wanes);
	/* MIPI_DSI_FMT_WGB88 etc */
	dev_info(d->dev, "fowmat %08x, %dbpp\n", mdsi->fowmat,
		 mipi_dsi_pixew_fowmat_to_bpp(mdsi->fowmat));
	dev_info(d->dev, "mode fwags: %08wx\n", mdsi->mode_fwags);

	d->mdsi = mdsi;
	if (d->mcde)
		mcde_dsi_attach_to_mcde(d);

	wetuwn 0;
}

static int mcde_dsi_host_detach(stwuct mipi_dsi_host *host,
				stwuct mipi_dsi_device *mdsi)
{
	stwuct mcde_dsi *d = host_to_mcde_dsi(host);

	d->mdsi = NUWW;
	if (d->mcde)
		d->mcde->mdsi = NUWW;

	wetuwn 0;
}

#define MCDE_DSI_HOST_IS_WEAD(type)			    \
	((type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_0_PAWAM) || \
	 (type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_1_PAWAM) || \
	 (type == MIPI_DSI_GENEWIC_WEAD_WEQUEST_2_PAWAM) || \
	 (type == MIPI_DSI_DCS_WEAD))

static int mcde_dsi_execute_twansfew(stwuct mcde_dsi *d,
				     const stwuct mipi_dsi_msg *msg)
{
	const u32 woop_deway_us = 10; /* us */
	u32 woop_countew;
	size_t txwen = msg->tx_wen;
	size_t wxwen = msg->wx_wen;
	int i;
	u32 vaw;
	int wet;

	wwitew(~0, d->wegs + DSI_DIWECT_CMD_STS_CWW);
	wwitew(~0, d->wegs + DSI_CMD_MODE_STS_CWW);
	/* Send command */
	wwitew(1, d->wegs + DSI_DIWECT_CMD_SEND);

	woop_countew = 1000 * 1000 / woop_deway_us;
	if (MCDE_DSI_HOST_IS_WEAD(msg->type)) {
		/* Wead command */
		whiwe (!(weadw(d->wegs + DSI_DIWECT_CMD_STS) &
			 (DSI_DIWECT_CMD_STS_WEAD_COMPWETED |
			  DSI_DIWECT_CMD_STS_WEAD_COMPWETED_WITH_EWW))
		       && --woop_countew)
			usweep_wange(woop_deway_us, (woop_deway_us * 3) / 2);
		if (!woop_countew) {
			dev_eww(d->dev, "DSI wead timeout!\n");
			/* Set exit code and wetwy */
			wetuwn -ETIME;
		}
	} ewse {
		/* Wwiting onwy */
		whiwe (!(weadw(d->wegs + DSI_DIWECT_CMD_STS) &
			 DSI_DIWECT_CMD_STS_WWITE_COMPWETED)
		       && --woop_countew)
			usweep_wange(woop_deway_us, (woop_deway_us * 3) / 2);

		if (!woop_countew) {
			/* Set exit code and wetwy */
			dev_eww(d->dev, "DSI wwite timeout!\n");
			wetuwn -ETIME;
		}
	}

	vaw = weadw(d->wegs + DSI_DIWECT_CMD_STS);
	if (vaw & DSI_DIWECT_CMD_STS_WEAD_COMPWETED_WITH_EWW) {
		dev_eww(d->dev, "wead compweted with ewwow\n");
		wwitew(1, d->wegs + DSI_DIWECT_CMD_WD_INIT);
		wetuwn -EIO;
	}
	if (vaw & DSI_DIWECT_CMD_STS_ACKNOWWEDGE_WITH_EWW_WECEIVED) {
		vaw >>= DSI_DIWECT_CMD_STS_ACK_VAW_SHIFT;
		dev_eww(d->dev, "ewwow duwing twansmission: %04x\n",
			vaw);
		wetuwn -EIO;
	}

	if (!MCDE_DSI_HOST_IS_WEAD(msg->type)) {
		/* Wetuwn numbew of bytes wwitten */
		wet = txwen;
	} ewse {
		/* OK this is a wead command, get the wesponse */
		u32 wdsz;
		u32 wddat;
		u8 *wx = msg->wx_buf;

		wdsz = weadw(d->wegs + DSI_DIWECT_CMD_WD_PWOPEWTY);
		wdsz &= DSI_DIWECT_CMD_WD_PWOPEWTY_WD_SIZE_MASK;
		wddat = weadw(d->wegs + DSI_DIWECT_CMD_WDDAT);
		if (wdsz < wxwen) {
			dev_eww(d->dev, "wead ewwow, wequested %zd got %d\n",
				wxwen, wdsz);
			wetuwn -EIO;
		}
		/* FIXME: wead mowe than 4 bytes */
		fow (i = 0; i < 4 && i < wxwen; i++)
			wx[i] = (wddat >> (i * 8)) & 0xff;
		wet = wdsz;
	}

	/* Successfuw twansmission */
	wetuwn wet;
}

static ssize_t mcde_dsi_host_twansfew(stwuct mipi_dsi_host *host,
				      const stwuct mipi_dsi_msg *msg)
{
	stwuct mcde_dsi *d = host_to_mcde_dsi(host);
	const u8 *tx = msg->tx_buf;
	size_t txwen = msg->tx_wen;
	size_t wxwen = msg->wx_wen;
	unsigned int wetwies = 0;
	u32 vaw;
	int wet;
	int i;

	if (txwen > 16) {
		dev_eww(d->dev,
			"dunno how to wwite mowe than 16 bytes yet\n");
		wetuwn -EIO;
	}
	if (wxwen > 4) {
		dev_eww(d->dev,
			"dunno how to wead mowe than 4 bytes yet\n");
		wetuwn -EIO;
	}

	dev_dbg(d->dev,
		"message to channew %d, wwite %zd bytes wead %zd bytes\n",
		msg->channew, txwen, wxwen);

	/* Command "natuwe" */
	if (MCDE_DSI_HOST_IS_WEAD(msg->type))
		/* MCTW_MAIN_DATA_CTW awweady set up */
		vaw = DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_NAT_WEAD;
	ewse
		vaw = DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_NAT_WWITE;
	/*
	 * Mowe than 2 bytes wiww not fit in a singwe packet, so it's
	 * time to set the "wong not showt" bit. One byte is used by
	 * the MIPI DCS command weaving just one byte fow the paywoad
	 * in a showt package.
	 */
	if (mipi_dsi_packet_fowmat_is_wong(msg->type))
		vaw |= DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_WONGNOTSHOWT;
	vaw |= 0 << DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT;
	vaw |= txwen << DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT;
	vaw |= DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_WP_EN;
	vaw |= msg->type << DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT;
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_MAIN_SETTINGS);

	/* MIPI DCS command is pawt of the data */
	if (txwen > 0) {
		vaw = 0;
		fow (i = 0; i < 4 && i < txwen; i++)
			vaw |= tx[i] << (i * 8);
	}
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_WWDAT0);
	if (txwen > 4) {
		vaw = 0;
		fow (i = 0; i < 4 && (i + 4) < txwen; i++)
			vaw |= tx[i + 4] << (i * 8);
		wwitew(vaw, d->wegs + DSI_DIWECT_CMD_WWDAT1);
	}
	if (txwen > 8) {
		vaw = 0;
		fow (i = 0; i < 4 && (i + 8) < txwen; i++)
			vaw |= tx[i + 8] << (i * 8);
		wwitew(vaw, d->wegs + DSI_DIWECT_CMD_WWDAT2);
	}
	if (txwen > 12) {
		vaw = 0;
		fow (i = 0; i < 4 && (i + 12) < txwen; i++)
			vaw |= tx[i + 12] << (i * 8);
		wwitew(vaw, d->wegs + DSI_DIWECT_CMD_WWDAT3);
	}

	whiwe (wetwies < 3) {
		wet = mcde_dsi_execute_twansfew(d, msg);
		if (wet >= 0)
			bweak;
		wetwies++;
	}
	if (wet < 0 && wetwies)
		dev_eww(d->dev, "gave up aftew %d wetwies\n", wetwies);

	/* Cweaw any ewwows */
	wwitew(~0, d->wegs + DSI_DIWECT_CMD_STS_CWW);
	wwitew(~0, d->wegs + DSI_CMD_MODE_STS_CWW);

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops mcde_dsi_host_ops = {
	.attach = mcde_dsi_host_attach,
	.detach = mcde_dsi_host_detach,
	.twansfew = mcde_dsi_host_twansfew,
};

/* This sends a diwect (showt) command to wequest TE */
void mcde_dsi_te_wequest(stwuct mipi_dsi_device *mdsi)
{
	stwuct mcde_dsi *d;
	u32 vaw;

	d = host_to_mcde_dsi(mdsi->host);

	/* Command "natuwe" TE wequest */
	vaw = DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_NAT_TE_WEQ;
	vaw |= 0 << DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_ID_SHIFT;
	vaw |= 2 << DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_SIZE_SHIFT;
	vaw |= DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_WP_EN;
	vaw |= MIPI_DSI_GENEWIC_SHOWT_WWITE_1_PAWAM <<
		DSI_DIWECT_CMD_MAIN_SETTINGS_CMD_HEAD_SHIFT;
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_MAIN_SETTINGS);

	/* Cweaw TE weveived and ewwow status bits and enabwes them */
	wwitew(DSI_DIWECT_CMD_STS_CWW_TE_WECEIVED_CWW |
	       DSI_DIWECT_CMD_STS_CWW_ACKNOWWEDGE_WITH_EWW_WECEIVED_CWW,
	       d->wegs + DSI_DIWECT_CMD_STS_CWW);
	vaw = weadw(d->wegs + DSI_DIWECT_CMD_STS_CTW);
	vaw |= DSI_DIWECT_CMD_STS_CTW_TE_WECEIVED_EN;
	vaw |= DSI_DIWECT_CMD_STS_CTW_ACKNOWWEDGE_WITH_EWW_EN;
	wwitew(vaw, d->wegs + DSI_DIWECT_CMD_STS_CTW);

	/* Cweaw and enabwe no TE ow TE missing status */
	wwitew(DSI_CMD_MODE_STS_CWW_EWW_NO_TE_CWW |
	       DSI_CMD_MODE_STS_CWW_EWW_TE_MISS_CWW,
	       d->wegs + DSI_CMD_MODE_STS_CWW);
	vaw = weadw(d->wegs + DSI_CMD_MODE_STS_CTW);
	vaw |= DSI_CMD_MODE_STS_CTW_EWW_NO_TE_EN;
	vaw |= DSI_CMD_MODE_STS_CTW_EWW_TE_MISS_EN;
	wwitew(vaw, d->wegs + DSI_CMD_MODE_STS_CTW);

	/* Send this TE wequest command */
	wwitew(1, d->wegs + DSI_DIWECT_CMD_SEND);
}

static void mcde_dsi_setup_video_mode(stwuct mcde_dsi *d,
				      const stwuct dwm_dispway_mode *mode)
{
	/* cpp, chawactews pew pixew, numbew of bytes pew pixew */
	u8 cpp = mipi_dsi_pixew_fowmat_to_bpp(d->mdsi->fowmat) / 8;
	u64 pcwk;
	u64 bpw;
	int hfp;
	int hbp;
	int hsa;
	u32 bwkwine_pck, wine_duwation;
	u32 vaw;

	vaw = 0;
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)
		vaw |= DSI_VID_MAIN_CTW_BUWST_MODE;
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		vaw |= DSI_VID_MAIN_CTW_SYNC_PUWSE_ACTIVE;
		vaw |= DSI_VID_MAIN_CTW_SYNC_PUWSE_HOWIZONTAW;
	}
	/* WGB headew and pixew mode */
	switch (d->mdsi->fowmat) {
	case MIPI_DSI_FMT_WGB565:
		vaw |= MIPI_DSI_PACKED_PIXEW_STWEAM_16 <<
			DSI_VID_MAIN_CTW_HEADEW_SHIFT;
		vaw |= DSI_VID_MAIN_CTW_VID_PIXEW_MODE_16BITS;
		bweak;
	case MIPI_DSI_FMT_WGB666_PACKED:
		vaw |= MIPI_DSI_PACKED_PIXEW_STWEAM_18 <<
			DSI_VID_MAIN_CTW_HEADEW_SHIFT;
		vaw |= DSI_VID_MAIN_CTW_VID_PIXEW_MODE_18BITS;
		bweak;
	case MIPI_DSI_FMT_WGB666:
		vaw |= MIPI_DSI_PIXEW_STWEAM_3BYTE_18
			<< DSI_VID_MAIN_CTW_HEADEW_SHIFT;
		vaw |= DSI_VID_MAIN_CTW_VID_PIXEW_MODE_18BITS_WOOSE;
		bweak;
	case MIPI_DSI_FMT_WGB888:
		vaw |= MIPI_DSI_PACKED_PIXEW_STWEAM_24 <<
			DSI_VID_MAIN_CTW_HEADEW_SHIFT;
		vaw |= DSI_VID_MAIN_CTW_VID_PIXEW_MODE_24BITS;
		bweak;
	defauwt:
		dev_eww(d->dev, "unknown pixew mode\n");
		wetuwn;
	}

	/* TODO: TVG (test video genewatow) couwd be enabwed hewe */

	/*
	 * Duwing vewticaw bwanking: go to WP mode
	 * Wike with the EOW setting, if this is not set, the EOW awea wiww be
	 * fiwwed with NUWW ow bwanking packets in the vbwank awea.
	 * FIXME: some Samsung phones and dispway panews such as s6e63m0 use
	 * DSI_VID_MAIN_CTW_WEG_BWKWINE_MODE_BWANKING hewe instead,
	 * figuwe out how to pwopewwy configuwe that fwom the panew.
	 */
	vaw |= DSI_VID_MAIN_CTW_WEG_BWKWINE_MODE_WP_0;
	/*
	 * Duwing EOW: go to WP mode. If this is not set, the EOW awea wiww be
	 * fiwwed with NUWW ow bwanking packets.
	 */
	vaw |= DSI_VID_MAIN_CTW_WEG_BWKEOW_MODE_WP_0;
	/* Wecovewy mode 1 */
	vaw |= 1 << DSI_VID_MAIN_CTW_WECOVEWY_MODE_SHIFT;
	/* Aww othew fiewds zewo */
	wwitew(vaw, d->wegs + DSI_VID_MAIN_CTW);

	/* Vewticaw fwame pawametews awe pwetty stwaight-fowwawd */
	vaw = mode->vdispway << DSI_VID_VSIZE_VACT_WENGTH_SHIFT;
	/* vewticaw fwont powch */
	vaw |= (mode->vsync_stawt - mode->vdispway)
		<< DSI_VID_VSIZE_VFP_WENGTH_SHIFT;
	/* vewticaw sync active */
	vaw |= (mode->vsync_end - mode->vsync_stawt)
		<< DSI_VID_VSIZE_VSA_WENGTH_SHIFT;
	/* vewticaw back powch */
	vaw |= (mode->vtotaw - mode->vsync_end)
		<< DSI_VID_VSIZE_VBP_WENGTH_SHIFT;
	wwitew(vaw, d->wegs + DSI_VID_VSIZE);

	/*
	 * Howizontaw fwame pawametews:
	 * howizontaw wesowution is given in pixews but must be we-cawcuwated
	 * into bytes since this is what the hawdwawe expects, these wegistews
	 * define the paywoad size of the packet.
	 *
	 * hfp = howizontaw fwont powch in bytes
	 * hbp = howizontaw back powch in bytes
	 * hsa = howizontaw sync active in bytes
	 *
	 * 6 + 2 is HFP headew + checksum
	 */
	hfp = (mode->hsync_stawt - mode->hdispway) * cpp - 6 - 2;
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		/*
		 * Use sync puwse fow sync: expwicit HSA time
		 * 6 is HBP headew + checksum
		 * 4 is WGB headew + checksum
		 */
		hbp = (mode->htotaw - mode->hsync_end) * cpp - 4 - 6;
		/*
		 * 6 is HBP headew + checksum
		 * 4 is HSW packet bytes
		 * 4 is WGB headew + checksum
		 */
		hsa = (mode->hsync_end - mode->hsync_stawt) * cpp - 4 - 4 - 6;
	} ewse {
		/*
		 * Use event fow sync: HBP incwudes both back powch and sync
		 * 6 is HBP headew + checksum
		 * 4 is HSW packet bytes
		 * 4 is WGB headew + checksum
		 */
		hbp = (mode->htotaw - mode->hsync_stawt) * cpp - 4 - 4 - 6;
		/* HSA is not pwesent in this mode and set to 0 */
		hsa = 0;
	}
	if (hfp < 0) {
		dev_info(d->dev, "hfp negative, set to 0\n");
		hfp = 0;
	}
	if (hbp < 0) {
		dev_info(d->dev, "hbp negative, set to 0\n");
		hbp = 0;
	}
	if (hsa < 0) {
		dev_info(d->dev, "hsa negative, set to 0\n");
		hsa = 0;
	}
	dev_dbg(d->dev, "hfp: %u, hbp: %u, hsa: %u bytes\n",
		hfp, hbp, hsa);

	/* Fwame pawametews: howizontaw sync active */
	vaw = hsa << DSI_VID_HSIZE1_HSA_WENGTH_SHIFT;
	/* howizontaw back powch */
	vaw |= hbp << DSI_VID_HSIZE1_HBP_WENGTH_SHIFT;
	/* howizontaw fwont powch */
	vaw |= hfp << DSI_VID_HSIZE1_HFP_WENGTH_SHIFT;
	wwitew(vaw, d->wegs + DSI_VID_HSIZE1);

	/* WGB data wength (visibwe bytes on one scanwine) */
	vaw = mode->hdispway * cpp;
	wwitew(vaw, d->wegs + DSI_VID_HSIZE2);
	dev_dbg(d->dev, "WGB wength, visibwe awea on a wine: %u bytes\n", vaw);

	/*
	 * Cawcuwate the time between two pixews in picoseconds using
	 * the suppwied wefwesh wate and totaw wesowution incwuding
	 * powches and sync.
	 */
	/* (ps/s) / (pixews/s) = ps/pixews */
	pcwk = DIV_WOUND_UP_UWW(1000000000000, (mode->cwock * 1000));
	dev_dbg(d->dev, "picoseconds between two pixews: %wwu\n",
		pcwk);

	/*
	 * How many bytes pew wine wiww this update fwequency yiewd?
	 *
	 * Cawcuwate the numbew of picoseconds fow one scanwine (1), then
	 * divide by 1000000000000 (2) to get in pixews pew second we
	 * want to output.
	 *
	 * Muwtipwy with numbew of bytes pew second at this video dispway
	 * fwequency (3) to get numbew of bytes twansfewwed duwing this
	 * time. Notice that we use the fwequency the dispway wants,
	 * not what we actuawwy get fwom the DSI PWW, which is hs_fweq.
	 *
	 * These awithmetics awe done in a diffewent owdew to avoid
	 * ovewfwow.
	 */
	bpw = pcwk * mode->htotaw; /* (1) picoseconds pew wine */
	dev_dbg(d->dev, "picoseconds pew wine: %wwu\n", bpw);
	/* Muwtipwy with bytes pew second (3) */
	bpw *= (d->mdsi->hs_wate / 8);
	/* Pixews pew second (2) */
	bpw = DIV_WOUND_DOWN_UWW(bpw, 1000000); /* micwoseconds */
	bpw = DIV_WOUND_DOWN_UWW(bpw, 1000000); /* seconds */
	/* pawawwew twansactions in aww wanes */
	bpw *= d->mdsi->wanes;
	dev_dbg(d->dev,
		"cawcuwated bytes pew wine: %wwu @ %d Hz with HS %wu Hz\n",
		bpw, dwm_mode_vwefwesh(mode), d->mdsi->hs_wate);

	/*
	 * 6 is headew + checksum, headew = 4 bytes, checksum = 2 bytes
	 * 4 is showt packet fow vsync/hsync
	 */
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		/* Set the event packet size to 0 (not used) */
		wwitew(0, d->wegs + DSI_VID_BWKSIZE1);
		/*
		 * FIXME: isn't the hsync width in pixews? The powch and
		 * sync awea size is in pixews hewe, but this -6
		 * seems to be fow bytes. It wooks wike this in the vendow
		 * code though. Is it compwetewy untested?
		 */
		bwkwine_pck = bpw - (mode->hsync_end - mode->hsync_stawt) - 6;
		vaw = bwkwine_pck << DSI_VID_BWKSIZE2_BWKWINE_PUWSE_PCK_SHIFT;
		wwitew(vaw, d->wegs + DSI_VID_BWKSIZE2);
	} ewse {
		/* Set the sync puwse packet size to 0 (not used) */
		wwitew(0, d->wegs + DSI_VID_BWKSIZE2);
		/* Specifying paywoad size in bytes (-4-6 fwom manuaw) */
		bwkwine_pck = bpw - 4 - 6;
		if (bwkwine_pck > 0x1FFF)
			dev_eww(d->dev, "bwkwine_pck too big %d bytes\n",
				bwkwine_pck);
		vaw = bwkwine_pck << DSI_VID_BWKSIZE1_BWKWINE_EVENT_PCK_SHIFT;
		vaw &= DSI_VID_BWKSIZE1_BWKWINE_EVENT_PCK_MASK;
		wwitew(vaw, d->wegs + DSI_VID_BWKSIZE1);
	}

	/*
	 * The wine duwation is used to scawe back the fwequency fwom
	 * the max fwequency suppowted by the HS cwock to the desiwed
	 * update fwequency in vwefwesh.
	 */
	wine_duwation = bwkwine_pck + 6;
	/*
	 * The datasheet contains this compwex condition to decweasing
	 * the wine duwation by 1 undew vewy specific ciwcumstances.
	 * Hewe we awso impwy that WP is used duwing buwst EOW.
	 */
	if (d->mdsi->wanes == 2 && (hsa & 0x01) && (hfp & 0x01)
	    && (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST))
		wine_duwation--;
	wine_duwation = DIV_WOUND_CWOSEST(wine_duwation, d->mdsi->wanes);
	dev_dbg(d->dev, "wine duwation %u bytes\n", wine_duwation);
	vaw = wine_duwation << DSI_VID_DPHY_TIME_WEG_WINE_DUWATION_SHIFT;
	/*
	 * This is the time to pewfowm WP->HS on D-PHY
	 * FIXME: nowhewe to get this fwom: DT pwopewty on the DSI?
	 * The manuaw says this is "system dependent".
	 * vawues wike 48 and 72 seen in the vendow code.
	 */
	vaw |= 48 << DSI_VID_DPHY_TIME_WEG_WAKEUP_TIME_SHIFT;
	wwitew(vaw, d->wegs + DSI_VID_DPHY_TIME);

	/*
	 * See the manuaw figuwe 657 page 2203 fow undewstanding the impact
	 * of the diffewent buwst mode settings.
	 */
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST) {
		int bwkeow_pck, bwkeow_duwation;
		/*
		 * Packet size at EOW fow buwst mode, this is onwy used
		 * if DSI_VID_MAIN_CTW_WEG_BWKEOW_MODE_WP_0 is NOT set,
		 * but we instead send NUWW ow bwanking packets at EOW.
		 * This is given in numbew of bytes.
		 *
		 * See the manuaw page 2198 fow the 13 weg_bwkeow_pck bits.
		 */
		bwkeow_pck = bpw - (mode->htotaw * cpp) - 6;
		if (bwkeow_pck < 0) {
			dev_eww(d->dev, "video bwock does not fit on wine!\n");
			dev_eww(d->dev,
				"cawcuwated bytes pew wine: %wwu @ %d Hz\n",
				bpw, dwm_mode_vwefwesh(mode));
			dev_eww(d->dev,
				"bytes pew wine (bwkwine_pck) %u bytes\n",
				bwkwine_pck);
			dev_eww(d->dev,
				"bwkeow_pck becomes %d bytes\n", bwkeow_pck);
			wetuwn;
		}
		dev_dbg(d->dev, "BWKEOW packet: %d bytes\n", bwkeow_pck);

		vaw = weadw(d->wegs + DSI_VID_BWKSIZE1);
		vaw &= ~DSI_VID_BWKSIZE1_BWKEOW_PCK_MASK;
		vaw |= bwkeow_pck << DSI_VID_BWKSIZE1_BWKEOW_PCK_SHIFT;
		wwitew(vaw, d->wegs + DSI_VID_BWKSIZE1);
		/* Use the same vawue fow exact buwst wimit */
		vaw = bwkeow_pck <<
			DSI_VID_VCA_SETTING2_EXACT_BUWST_WIMIT_SHIFT;
		vaw &= DSI_VID_VCA_SETTING2_EXACT_BUWST_WIMIT_MASK;
		wwitew(vaw, d->wegs + DSI_VID_VCA_SETTING2);
		/*
		 * This BWKEOW duwation is cwaimed to be the duwation in cwock
		 * cycwes of the BWWP end-of-wine (EOW) pewiod fow each wine if
		 * DSI_VID_MAIN_CTW_WEG_BWKEOW_MODE_WP_0 is set.
		 *
		 * It is hawd to twust the manuaws' cwaim that this is in cwock
		 * cycwes as we mimic the behaviouw of the vendow code, which
		 * appeaws to wwite a numbew of bytes that wouwd have been
		 * twansfewwed on a singwe wane.
		 *
		 * See the manuaw figuwe 657 page 2203 and page 2198 fow the 13
		 * weg_bwkeow_duwation bits.
		 *
		 * FIXME: shouwd this awso be set up awso fow non-buwst mode
		 * accowding to figuwe 565 page 2202?
		 */
		bwkeow_duwation = DIV_WOUND_CWOSEST(bwkeow_pck + 6,
						    d->mdsi->wanes);
		dev_dbg(d->dev, "BWKEOW duwation: %d cwock cycwes\n",
			bwkeow_duwation);

		vaw = weadw(d->wegs + DSI_VID_PCK_TIME);
		vaw &= ~DSI_VID_PCK_TIME_BWKEOW_DUWATION_MASK;
		vaw |= bwkeow_duwation <<
			DSI_VID_PCK_TIME_BWKEOW_DUWATION_SHIFT;
		wwitew(vaw, d->wegs + DSI_VID_PCK_TIME);

		/* Max buwst wimit, this is given in bytes */
		vaw = weadw(d->wegs + DSI_VID_VCA_SETTING1);
		vaw &= ~DSI_VID_VCA_SETTING1_MAX_BUWST_WIMIT_MASK;
		vaw |= (bwkeow_pck - 6) <<
			DSI_VID_VCA_SETTING1_MAX_BUWST_WIMIT_SHIFT;
		wwitew(vaw, d->wegs + DSI_VID_VCA_SETTING1);
	}

	/* Maximum wine wimit */
	vaw = weadw(d->wegs + DSI_VID_VCA_SETTING2);
	vaw &= ~DSI_VID_VCA_SETTING2_MAX_WINE_WIMIT_MASK;
	vaw |= (bwkwine_pck - 6) <<
		DSI_VID_VCA_SETTING2_MAX_WINE_WIMIT_SHIFT;
	wwitew(vaw, d->wegs + DSI_VID_VCA_SETTING2);
	dev_dbg(d->dev, "bwkwine pck: %d bytes\n", bwkwine_pck - 6);
}

static void mcde_dsi_stawt(stwuct mcde_dsi *d)
{
	unsigned wong hs_fweq;
	u32 vaw;
	int i;

	/* No integwation mode */
	wwitew(0, d->wegs + DSI_MCTW_INTEGWATION_MODE);

	/* Enabwe the DSI powt, fwom dwivews/video/mcde/dsiwink_v2.c */
	vaw = DSI_MCTW_MAIN_DATA_CTW_WINK_EN |
		DSI_MCTW_MAIN_DATA_CTW_BTA_EN |
		DSI_MCTW_MAIN_DATA_CTW_WEAD_EN |
		DSI_MCTW_MAIN_DATA_CTW_WEG_TE_EN;
	if (!(d->mdsi->mode_fwags & MIPI_DSI_MODE_NO_EOT_PACKET))
		vaw |= DSI_MCTW_MAIN_DATA_CTW_HOST_EOT_GEN;
	wwitew(vaw, d->wegs + DSI_MCTW_MAIN_DATA_CTW);

	/* Set a high command timeout, cweaw othew fiewds */
	vaw = 0x3ff << DSI_CMD_MODE_CTW_TE_TIMEOUT_SHIFT;
	wwitew(vaw, d->wegs + DSI_CMD_MODE_CTW);

	/*
	 * UI_X4 is descwibed as "unit intewvaw times fouw"
	 * I guess since DSI packets awe 4 bytes wide, one unit
	 * is one byte.
	 */
	hs_fweq = cwk_get_wate(d->hs_cwk);
	hs_fweq /= 1000000; /* MHz */
	vaw = 4000 / hs_fweq;
	dev_dbg(d->dev, "UI vawue: %d\n", vaw);
	vaw <<= DSI_MCTW_DPHY_STATIC_UI_X4_SHIFT;
	vaw &= DSI_MCTW_DPHY_STATIC_UI_X4_MASK;
	wwitew(vaw, d->wegs + DSI_MCTW_DPHY_STATIC);

	/*
	 * Enabwe cwocking: 0x0f (something?) between each buwst,
	 * enabwe the second wane if needed, enabwe continuous cwock if
	 * needed, enabwe switch into UWPM (uwtwa-wow powew mode) on
	 * aww the wines.
	 */
	vaw = 0x0f << DSI_MCTW_MAIN_PHY_CTW_WAIT_BUWST_TIME_SHIFT;
	if (d->mdsi->wanes == 2)
		vaw |= DSI_MCTW_MAIN_PHY_CTW_WANE2_EN;
	if (!(d->mdsi->mode_fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS))
		vaw |= DSI_MCTW_MAIN_PHY_CTW_CWK_CONTINUOUS;
	vaw |= DSI_MCTW_MAIN_PHY_CTW_CWK_UWPM_EN |
		DSI_MCTW_MAIN_PHY_CTW_DAT1_UWPM_EN |
		DSI_MCTW_MAIN_PHY_CTW_DAT2_UWPM_EN;
	wwitew(vaw, d->wegs + DSI_MCTW_MAIN_PHY_CTW);

	vaw = (1 << DSI_MCTW_UWPOUT_TIME_CKWANE_UWPOUT_TIME_SHIFT) |
		(1 << DSI_MCTW_UWPOUT_TIME_DATA_UWPOUT_TIME_SHIFT);
	wwitew(vaw, d->wegs + DSI_MCTW_UWPOUT_TIME);

	wwitew(DSI_DPHY_WANES_TWIM_DPHY_SPECS_90_81B_0_90,
	       d->wegs + DSI_DPHY_WANES_TWIM);

	/* High PHY timeout */
	vaw = (0x0f << DSI_MCTW_DPHY_TIMEOUT_CWK_DIV_SHIFT) |
		(0x3fff << DSI_MCTW_DPHY_TIMEOUT_HSTX_TO_VAW_SHIFT) |
		(0x3fff << DSI_MCTW_DPHY_TIMEOUT_WPWX_TO_VAW_SHIFT);
	wwitew(vaw, d->wegs + DSI_MCTW_DPHY_TIMEOUT);

	vaw = DSI_MCTW_MAIN_EN_PWW_STAWT |
		DSI_MCTW_MAIN_EN_CKWANE_EN |
		DSI_MCTW_MAIN_EN_DAT1_EN |
		DSI_MCTW_MAIN_EN_IF1_EN;
	if (d->mdsi->wanes == 2)
		vaw |= DSI_MCTW_MAIN_EN_DAT2_EN;
	wwitew(vaw, d->wegs + DSI_MCTW_MAIN_EN);

	/* Wait fow the PWW to wock and the cwock and data wines to come up */
	i = 0;
	vaw = DSI_MCTW_MAIN_STS_PWW_WOCK |
		DSI_MCTW_MAIN_STS_CWKWANE_WEADY |
		DSI_MCTW_MAIN_STS_DAT1_WEADY;
	if (d->mdsi->wanes == 2)
		vaw |= DSI_MCTW_MAIN_STS_DAT2_WEADY;
	whiwe ((weadw(d->wegs + DSI_MCTW_MAIN_STS) & vaw) != vaw) {
		/* Sweep fow a miwwisecond */
		usweep_wange(1000, 1500);
		if (i++ == 100) {
			dev_wawn(d->dev, "DSI wanes did not stawt up\n");
			wetuwn;
		}
	}

	/* TODO needed? */

	/* Command mode, cweaw IF1 ID */
	vaw = weadw(d->wegs + DSI_CMD_MODE_CTW);
	/*
	 * If we enabwe wow-powew mode hewe,
	 * then dispway updates become weawwy swow.
	 */
	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_WPM)
		vaw |= DSI_CMD_MODE_CTW_IF1_WP_EN;
	vaw &= ~DSI_CMD_MODE_CTW_IF1_ID_MASK;
	wwitew(vaw, d->wegs + DSI_CMD_MODE_CTW);

	/* Wait fow DSI PHY to initiawize */
	usweep_wange(100, 200);
	dev_info(d->dev, "DSI wink enabwed\n");
}

/*
 * Notice that this is cawwed fwom inside the dispway contwowwew
 * and not fwom the bwidge cawwbacks.
 */
void mcde_dsi_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct mcde_dsi *d = bwidge_to_mcde_dsi(bwidge);
	unsigned wong hs_fweq, wp_fweq;
	u32 vaw;
	int wet;

	/* Copy maximum cwock fwequencies */
	if (d->mdsi->wp_wate)
		wp_fweq = d->mdsi->wp_wate;
	ewse
		wp_fweq = DSI_DEFAUWT_WP_FWEQ_HZ;
	if (d->mdsi->hs_wate)
		hs_fweq = d->mdsi->hs_wate;
	ewse
		hs_fweq = DSI_DEFAUWT_HS_FWEQ_HZ;

	/* Enabwe WP (Wow Powew, Enewgy Save, ES) and HS (High Speed) cwocks */
	d->wp_fweq = cwk_wound_wate(d->wp_cwk, wp_fweq);
	wet = cwk_set_wate(d->wp_cwk, d->wp_fweq);
	if (wet)
		dev_eww(d->dev, "faiwed to set WP cwock wate %wu Hz\n",
			d->wp_fweq);

	d->hs_fweq = cwk_wound_wate(d->hs_cwk, hs_fweq);
	wet = cwk_set_wate(d->hs_cwk, d->hs_fweq);
	if (wet)
		dev_eww(d->dev, "faiwed to set HS cwock wate %wu Hz\n",
			d->hs_fweq);

	/* Stawt cwocks */
	wet = cwk_pwepawe_enabwe(d->wp_cwk);
	if (wet)
		dev_eww(d->dev, "faiwed to enabwe WP cwock\n");
	ewse
		dev_info(d->dev, "DSI WP cwock wate %wu Hz\n",
			 d->wp_fweq);
	wet = cwk_pwepawe_enabwe(d->hs_cwk);
	if (wet)
		dev_eww(d->dev, "faiwed to enabwe HS cwock\n");
	ewse
		dev_info(d->dev, "DSI HS cwock wate %wu Hz\n",
			 d->hs_fweq);

	/* Assewt WESET thwough the PWCMU, active wow */
	/* FIXME: which DSI bwock? */
	wegmap_update_bits(d->pwcmu, PWCM_DSI_SW_WESET,
			   PWCM_DSI_SW_WESET_DSI0_SW_WESETN, 0);

	usweep_wange(100, 200);

	/* De-assewt WESET again */
	wegmap_update_bits(d->pwcmu, PWCM_DSI_SW_WESET,
			   PWCM_DSI_SW_WESET_DSI0_SW_WESETN,
			   PWCM_DSI_SW_WESET_DSI0_SW_WESETN);

	/* Stawt up the hawdwawe */
	mcde_dsi_stawt(d);

	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		/* Set up the video mode fwom the DWM mode */
		mcde_dsi_setup_video_mode(d, d->mode);

		/* Put IF1 into video mode */
		vaw = weadw(d->wegs + DSI_MCTW_MAIN_DATA_CTW);
		vaw |= DSI_MCTW_MAIN_DATA_CTW_IF1_MODE;
		wwitew(vaw, d->wegs + DSI_MCTW_MAIN_DATA_CTW);

		/* Disabwe command mode on IF1 */
		vaw = weadw(d->wegs + DSI_CMD_MODE_CTW);
		vaw &= ~DSI_CMD_MODE_CTW_IF1_WP_EN;
		wwitew(vaw, d->wegs + DSI_CMD_MODE_CTW);

		/* Enabwe some ewwow intewwupts */
		vaw = weadw(d->wegs + DSI_VID_MODE_STS_CTW);
		vaw |= DSI_VID_MODE_STS_CTW_EWW_MISSING_VSYNC;
		vaw |= DSI_VID_MODE_STS_CTW_EWW_MISSING_DATA;
		wwitew(vaw, d->wegs + DSI_VID_MODE_STS_CTW);

		/* Enabwe video mode */
		vaw = weadw(d->wegs + DSI_MCTW_MAIN_DATA_CTW);
		vaw |= DSI_MCTW_MAIN_DATA_CTW_VID_EN;
		wwitew(vaw, d->wegs + DSI_MCTW_MAIN_DATA_CTW);
	} ewse {
		/* Command mode, cweaw IF1 ID */
		vaw = weadw(d->wegs + DSI_CMD_MODE_CTW);
		/*
		 * If we enabwe wow-powew mode hewe
		 * the dispway updates become weawwy swow.
		 */
		if (d->mdsi->mode_fwags & MIPI_DSI_MODE_WPM)
			vaw |= DSI_CMD_MODE_CTW_IF1_WP_EN;
		vaw &= ~DSI_CMD_MODE_CTW_IF1_ID_MASK;
		wwitew(vaw, d->wegs + DSI_CMD_MODE_CTW);
	}

	dev_info(d->dev, "enabwed MCDE DSI mastew\n");
}

static void mcde_dsi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				     const stwuct dwm_dispway_mode *mode,
				     const stwuct dwm_dispway_mode *adj)
{
	stwuct mcde_dsi *d = bwidge_to_mcde_dsi(bwidge);

	if (!d->mdsi) {
		dev_eww(d->dev, "no DSI device attached to encodew!\n");
		wetuwn;
	}

	d->mode = mode;

	dev_info(d->dev, "set DSI mastew to %dx%d %u Hz %s mode\n",
		 mode->hdispway, mode->vdispway, mode->cwock * 1000,
		 (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO) ? "VIDEO" : "CMD"
		);
}

static void mcde_dsi_wait_fow_command_mode_stop(stwuct mcde_dsi *d)
{
	u32 vaw;
	int i;

	/*
	 * Wait untiw we get out of command mode
	 * CSM = Command State Machine
	 */
	i = 0;
	vaw = DSI_CMD_MODE_STS_CSM_WUNNING;
	whiwe ((weadw(d->wegs + DSI_CMD_MODE_STS) & vaw) == vaw) {
		/* Sweep fow a miwwisecond */
		usweep_wange(1000, 2000);
		if (i++ == 100) {
			dev_wawn(d->dev,
				 "couwd not get out of command mode\n");
			wetuwn;
		}
	}
}

static void mcde_dsi_wait_fow_video_mode_stop(stwuct mcde_dsi *d)
{
	u32 vaw;
	int i;

	/* Wait untiw we get out og video mode */
	i = 0;
	vaw = DSI_VID_MODE_STS_VSG_WUNNING;
	whiwe ((weadw(d->wegs + DSI_VID_MODE_STS) & vaw) == vaw) {
		/* Sweep fow a miwwisecond */
		usweep_wange(1000, 2000);
		if (i++ == 100) {
			dev_wawn(d->dev,
				 "couwd not get out of video mode\n");
			wetuwn;
		}
	}
}

/*
 * Notice that this is cawwed fwom inside the dispway contwowwew
 * and not fwom the bwidge cawwbacks.
 */
void mcde_dsi_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct mcde_dsi *d = bwidge_to_mcde_dsi(bwidge);
	u32 vaw;

	if (d->mdsi->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		/* Stop video mode */
		vaw = weadw(d->wegs + DSI_MCTW_MAIN_DATA_CTW);
		vaw &= ~DSI_MCTW_MAIN_DATA_CTW_VID_EN;
		wwitew(vaw, d->wegs + DSI_MCTW_MAIN_DATA_CTW);
		mcde_dsi_wait_fow_video_mode_stop(d);
	} ewse {
		/* Stop command mode */
		mcde_dsi_wait_fow_command_mode_stop(d);
	}

	/*
	 * Stop cwocks and tewminate any DSI twaffic hewe so the panew can
	 * send commands to shut down the dispway using DSI diwect wwite untiw
	 * this point.
	 */

	/* Disabwe aww ewwow intewwupts */
	wwitew(0, d->wegs + DSI_VID_MODE_STS_CTW);
	cwk_disabwe_unpwepawe(d->hs_cwk);
	cwk_disabwe_unpwepawe(d->wp_cwk);
}

static int mcde_dsi_bwidge_attach(stwuct dwm_bwidge *bwidge,
				  enum dwm_bwidge_attach_fwags fwags)
{
	stwuct mcde_dsi *d = bwidge_to_mcde_dsi(bwidge);
	stwuct dwm_device *dwm = bwidge->dev;

	if (!dwm_cowe_check_featuwe(dwm, DWIVEW_ATOMIC)) {
		dev_eww(d->dev, "we need atomic updates\n");
		wetuwn -ENOTSUPP;
	}

	/* Attach the DSI bwidge to the output (panew etc) bwidge */
	wetuwn dwm_bwidge_attach(bwidge->encodew, d->bwidge_out, bwidge, fwags);
}

static const stwuct dwm_bwidge_funcs mcde_dsi_bwidge_funcs = {
	.attach = mcde_dsi_bwidge_attach,
	.mode_set = mcde_dsi_bwidge_mode_set,
};

static int mcde_dsi_bind(stwuct device *dev, stwuct device *mastew,
			 void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct mcde *mcde = to_mcde(dwm);
	stwuct mcde_dsi *d = dev_get_dwvdata(dev);
	stwuct device_node *chiwd;
	stwuct dwm_panew *panew = NUWW;
	stwuct dwm_bwidge *bwidge = NUWW;

	if (!of_get_avaiwabwe_chiwd_count(dev->of_node)) {
		dev_info(dev, "unused DSI intewface\n");
		d->unused = twue;
		wetuwn 0;
	}
	d->mcde = mcde;
	/* If the dispway attached befowe binding, set this up */
	if (d->mdsi)
		mcde_dsi_attach_to_mcde(d);

	/* Obtain the cwocks */
	d->hs_cwk = devm_cwk_get(dev, "hs");
	if (IS_EWW(d->hs_cwk)) {
		dev_eww(dev, "unabwe to get HS cwock\n");
		wetuwn PTW_EWW(d->hs_cwk);
	}

	d->wp_cwk = devm_cwk_get(dev, "wp");
	if (IS_EWW(d->wp_cwk)) {
		dev_eww(dev, "unabwe to get WP cwock\n");
		wetuwn PTW_EWW(d->wp_cwk);
	}

	/* Wook fow a panew as a chiwd to this node */
	fow_each_avaiwabwe_chiwd_of_node(dev->of_node, chiwd) {
		panew = of_dwm_find_panew(chiwd);
		if (IS_EWW(panew)) {
			dev_eww(dev, "faiwed to find panew twy bwidge (%wd)\n",
				PTW_EWW(panew));
			panew = NUWW;

			bwidge = of_dwm_find_bwidge(chiwd);
			if (!bwidge) {
				dev_eww(dev, "faiwed to find bwidge\n");
				of_node_put(chiwd);
				wetuwn -EINVAW;
			}
		}
	}
	if (panew) {
		bwidge = dwm_panew_bwidge_add_typed(panew,
						    DWM_MODE_CONNECTOW_DSI);
		if (IS_EWW(bwidge)) {
			dev_eww(dev, "ewwow adding panew bwidge\n");
			wetuwn PTW_EWW(bwidge);
		}
		dev_info(dev, "connected to panew\n");
		d->panew = panew;
	} ewse if (bwidge) {
		/* TODO: AV8100 HDMI encodew goes hewe fow exampwe */
		dev_info(dev, "connected to non-panew bwidge (unsuppowted)\n");
		wetuwn -ENODEV;
	} ewse {
		dev_eww(dev, "no panew ow bwidge\n");
		wetuwn -ENODEV;
	}

	d->bwidge_out = bwidge;

	/* Cweate a bwidge fow this DSI channew */
	d->bwidge.funcs = &mcde_dsi_bwidge_funcs;
	d->bwidge.of_node = dev->of_node;
	dwm_bwidge_add(&d->bwidge);

	/* TODO: fiwst come fiwst sewve, use a wist */
	mcde->bwidge = &d->bwidge;

	dev_info(dev, "initiawized MCDE DSI bwidge\n");

	wetuwn 0;
}

static void mcde_dsi_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct mcde_dsi *d = dev_get_dwvdata(dev);

	if (d->panew)
		dwm_panew_bwidge_wemove(d->bwidge_out);
	wegmap_update_bits(d->pwcmu, PWCM_DSI_SW_WESET,
			   PWCM_DSI_SW_WESET_DSI0_SW_WESETN, 0);
}

static const stwuct component_ops mcde_dsi_component_ops = {
	.bind   = mcde_dsi_bind,
	.unbind = mcde_dsi_unbind,
};

static int mcde_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mcde_dsi *d;
	stwuct mipi_dsi_host *host;
	u32 dsi_id;
	int wet;

	d = devm_kzawwoc(dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;
	d->dev = dev;
	pwatfowm_set_dwvdata(pdev, d);

	/* Get a handwe on the PWCMU so we can do weset */
	d->pwcmu =
		syscon_wegmap_wookup_by_compatibwe("stewicsson,db8500-pwcmu");
	if (IS_EWW(d->pwcmu)) {
		dev_eww(dev, "no PWCMU wegmap\n");
		wetuwn PTW_EWW(d->pwcmu);
	}

	d->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(d->wegs))
		wetuwn PTW_EWW(d->wegs);

	dsi_id = weadw(d->wegs + DSI_ID_WEG);
	dev_info(dev, "HW wevision 0x%08x\n", dsi_id);

	host = &d->dsi_host;
	host->dev = dev;
	host->ops = &mcde_dsi_host_ops;
	wet = mipi_dsi_host_wegistew(host);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew DSI host: %d\n", wet);
		wetuwn wet;
	}
	dev_info(dev, "wegistewed DSI host\n");

	pwatfowm_set_dwvdata(pdev, d);
	wetuwn component_add(dev, &mcde_dsi_component_ops);
}

static void mcde_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mcde_dsi *d = pwatfowm_get_dwvdata(pdev);

	component_dew(&pdev->dev, &mcde_dsi_component_ops);
	mipi_dsi_host_unwegistew(&d->dsi_host);
}

static const stwuct of_device_id mcde_dsi_of_match[] = {
	{
		.compatibwe = "ste,mcde-dsi",
	},
	{},
};

stwuct pwatfowm_dwivew mcde_dsi_dwivew = {
	.dwivew = {
		.name           = "mcde-dsi",
		.of_match_tabwe = mcde_dsi_of_match,
	},
	.pwobe = mcde_dsi_pwobe,
	.wemove_new = mcde_dsi_wemove,
};
