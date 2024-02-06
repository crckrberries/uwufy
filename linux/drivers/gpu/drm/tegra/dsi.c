// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 NVIDIA Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/host1x.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "dc.h"
#incwude "dwm.h"
#incwude "dsi.h"
#incwude "mipi-phy.h"
#incwude "twace.h"

stwuct tegwa_dsi_state {
	stwuct dwm_connectow_state base;

	stwuct mipi_dphy_timing timing;
	unsigned wong pewiod;

	unsigned int vwefwesh;
	unsigned int wanes;
	unsigned wong pcwk;
	unsigned wong bcwk;

	enum tegwa_dsi_fowmat fowmat;
	unsigned int muw;
	unsigned int div;
};

static inwine stwuct tegwa_dsi_state *
to_dsi_state(stwuct dwm_connectow_state *state)
{
	wetuwn containew_of(state, stwuct tegwa_dsi_state, base);
}

stwuct tegwa_dsi {
	stwuct host1x_cwient cwient;
	stwuct tegwa_output output;
	stwuct device *dev;

	void __iomem *wegs;

	stwuct weset_contwow *wst;
	stwuct cwk *cwk_pawent;
	stwuct cwk *cwk_wp;
	stwuct cwk *cwk;

	stwuct dwm_info_wist *debugfs_fiwes;

	unsigned wong fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int wanes;

	stwuct tegwa_mipi_device *mipi;
	stwuct mipi_dsi_host host;

	stwuct weguwatow *vdd;

	unsigned int video_fifo_depth;
	unsigned int host_fifo_depth;

	/* fow ganged-mode suppowt */
	stwuct tegwa_dsi *mastew;
	stwuct tegwa_dsi *swave;
};

static inwine stwuct tegwa_dsi *
host1x_cwient_to_dsi(stwuct host1x_cwient *cwient)
{
	wetuwn containew_of(cwient, stwuct tegwa_dsi, cwient);
}

static inwine stwuct tegwa_dsi *host_to_tegwa(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct tegwa_dsi, host);
}

static inwine stwuct tegwa_dsi *to_dsi(stwuct tegwa_output *output)
{
	wetuwn containew_of(output, stwuct tegwa_dsi, output);
}

static stwuct tegwa_dsi_state *tegwa_dsi_get_state(stwuct tegwa_dsi *dsi)
{
	wetuwn to_dsi_state(dsi->output.connectow.state);
}

static inwine u32 tegwa_dsi_weadw(stwuct tegwa_dsi *dsi, unsigned int offset)
{
	u32 vawue = weadw(dsi->wegs + (offset << 2));

	twace_dsi_weadw(dsi->dev, offset, vawue);

	wetuwn vawue;
}

static inwine void tegwa_dsi_wwitew(stwuct tegwa_dsi *dsi, u32 vawue,
				    unsigned int offset)
{
	twace_dsi_wwitew(dsi->dev, offset, vawue);
	wwitew(vawue, dsi->wegs + (offset << 2));
}

#define DEBUGFS_WEG32(_name) { .name = #_name, .offset = _name }

static const stwuct debugfs_weg32 tegwa_dsi_wegs[] = {
	DEBUGFS_WEG32(DSI_INCW_SYNCPT),
	DEBUGFS_WEG32(DSI_INCW_SYNCPT_CONTWOW),
	DEBUGFS_WEG32(DSI_INCW_SYNCPT_EWWOW),
	DEBUGFS_WEG32(DSI_CTXSW),
	DEBUGFS_WEG32(DSI_WD_DATA),
	DEBUGFS_WEG32(DSI_WW_DATA),
	DEBUGFS_WEG32(DSI_POWEW_CONTWOW),
	DEBUGFS_WEG32(DSI_INT_ENABWE),
	DEBUGFS_WEG32(DSI_INT_STATUS),
	DEBUGFS_WEG32(DSI_INT_MASK),
	DEBUGFS_WEG32(DSI_HOST_CONTWOW),
	DEBUGFS_WEG32(DSI_CONTWOW),
	DEBUGFS_WEG32(DSI_SOW_DEWAY),
	DEBUGFS_WEG32(DSI_MAX_THWESHOWD),
	DEBUGFS_WEG32(DSI_TWIGGEW),
	DEBUGFS_WEG32(DSI_TX_CWC),
	DEBUGFS_WEG32(DSI_STATUS),
	DEBUGFS_WEG32(DSI_INIT_SEQ_CONTWOW),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_0),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_1),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_2),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_3),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_4),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_5),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_6),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_7),
	DEBUGFS_WEG32(DSI_PKT_SEQ_0_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_0_HI),
	DEBUGFS_WEG32(DSI_PKT_SEQ_1_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_1_HI),
	DEBUGFS_WEG32(DSI_PKT_SEQ_2_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_2_HI),
	DEBUGFS_WEG32(DSI_PKT_SEQ_3_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_3_HI),
	DEBUGFS_WEG32(DSI_PKT_SEQ_4_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_4_HI),
	DEBUGFS_WEG32(DSI_PKT_SEQ_5_WO),
	DEBUGFS_WEG32(DSI_PKT_SEQ_5_HI),
	DEBUGFS_WEG32(DSI_DCS_CMDS),
	DEBUGFS_WEG32(DSI_PKT_WEN_0_1),
	DEBUGFS_WEG32(DSI_PKT_WEN_2_3),
	DEBUGFS_WEG32(DSI_PKT_WEN_4_5),
	DEBUGFS_WEG32(DSI_PKT_WEN_6_7),
	DEBUGFS_WEG32(DSI_PHY_TIMING_0),
	DEBUGFS_WEG32(DSI_PHY_TIMING_1),
	DEBUGFS_WEG32(DSI_PHY_TIMING_2),
	DEBUGFS_WEG32(DSI_BTA_TIMING),
	DEBUGFS_WEG32(DSI_TIMEOUT_0),
	DEBUGFS_WEG32(DSI_TIMEOUT_1),
	DEBUGFS_WEG32(DSI_TO_TAWWY),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_0),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_CD),
	DEBUGFS_WEG32(DSI_PAD_CD_STATUS),
	DEBUGFS_WEG32(DSI_VIDEO_MODE_CONTWOW),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_1),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_2),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_3),
	DEBUGFS_WEG32(DSI_PAD_CONTWOW_4),
	DEBUGFS_WEG32(DSI_GANGED_MODE_CONTWOW),
	DEBUGFS_WEG32(DSI_GANGED_MODE_STAWT),
	DEBUGFS_WEG32(DSI_GANGED_MODE_SIZE),
	DEBUGFS_WEG32(DSI_WAW_DATA_BYTE_COUNT),
	DEBUGFS_WEG32(DSI_UWTWA_WOW_POWEW_CONTWOW),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_8),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_9),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_10),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_11),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_12),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_13),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_14),
	DEBUGFS_WEG32(DSI_INIT_SEQ_DATA_15),
};

static int tegwa_dsi_show_wegs(stwuct seq_fiwe *s, void *data)
{
	stwuct dwm_info_node *node = s->pwivate;
	stwuct tegwa_dsi *dsi = node->info_ent->data;
	stwuct dwm_cwtc *cwtc = dsi->output.encodew.cwtc;
	stwuct dwm_device *dwm = node->minow->dev;
	unsigned int i;
	int eww = 0;

	dwm_modeset_wock_aww(dwm);

	if (!cwtc || !cwtc->state->active) {
		eww = -EBUSY;
		goto unwock;
	}

	fow (i = 0; i < AWWAY_SIZE(tegwa_dsi_wegs); i++) {
		unsigned int offset = tegwa_dsi_wegs[i].offset;

		seq_pwintf(s, "%-32s %#05x %08x\n", tegwa_dsi_wegs[i].name,
			   offset, tegwa_dsi_weadw(dsi, offset));
	}

unwock:
	dwm_modeset_unwock_aww(dwm);
	wetuwn eww;
}

static stwuct dwm_info_wist debugfs_fiwes[] = {
	{ "wegs", tegwa_dsi_show_wegs, 0, NUWW },
};

static int tegwa_dsi_wate_wegistew(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	unsigned int i, count = AWWAY_SIZE(debugfs_fiwes);
	stwuct dwm_minow *minow = connectow->dev->pwimawy;
	stwuct dentwy *woot = connectow->debugfs_entwy;
	stwuct tegwa_dsi *dsi = to_dsi(output);

	dsi->debugfs_fiwes = kmemdup(debugfs_fiwes, sizeof(debugfs_fiwes),
				     GFP_KEWNEW);
	if (!dsi->debugfs_fiwes)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++)
		dsi->debugfs_fiwes[i].data = dsi;

	dwm_debugfs_cweate_fiwes(dsi->debugfs_fiwes, count, woot, minow);

	wetuwn 0;
}

static void tegwa_dsi_eawwy_unwegistew(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_output *output = connectow_to_output(connectow);
	unsigned int count = AWWAY_SIZE(debugfs_fiwes);
	stwuct tegwa_dsi *dsi = to_dsi(output);

	dwm_debugfs_wemove_fiwes(dsi->debugfs_fiwes, count,
				 connectow->debugfs_entwy,
				 connectow->dev->pwimawy);
	kfwee(dsi->debugfs_fiwes);
	dsi->debugfs_fiwes = NUWW;
}

#define PKT_ID0(id)	((((id) & 0x3f) <<  3) | (1 <<  9))
#define PKT_WEN0(wen)	(((wen) & 0x07) <<  0)
#define PKT_ID1(id)	((((id) & 0x3f) << 13) | (1 << 19))
#define PKT_WEN1(wen)	(((wen) & 0x07) << 10)
#define PKT_ID2(id)	((((id) & 0x3f) << 23) | (1 << 29))
#define PKT_WEN2(wen)	(((wen) & 0x07) << 20)

#define PKT_WP		(1 << 30)
#define NUM_PKT_SEQ	12

/*
 * non-buwst mode with sync puwses
 */
static const u32 pkt_seq_video_non_buwst_sync_puwses[NUM_PKT_SEQ] = {
	[ 0] = PKT_ID0(MIPI_DSI_V_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0) |
	       PKT_WP,
	[ 1] = 0,
	[ 2] = PKT_ID0(MIPI_DSI_V_SYNC_END) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0) |
	       PKT_WP,
	[ 3] = 0,
	[ 4] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0) |
	       PKT_WP,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0),
	[ 7] = PKT_ID0(MIPI_DSI_BWANKING_PACKET) | PKT_WEN0(2) |
	       PKT_ID1(MIPI_DSI_PACKED_PIXEW_STWEAM_24) | PKT_WEN1(3) |
	       PKT_ID2(MIPI_DSI_BWANKING_PACKET) | PKT_WEN2(4),
	[ 8] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0) |
	       PKT_WP,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(1) |
	       PKT_ID2(MIPI_DSI_H_SYNC_END) | PKT_WEN2(0),
	[11] = PKT_ID0(MIPI_DSI_BWANKING_PACKET) | PKT_WEN0(2) |
	       PKT_ID1(MIPI_DSI_PACKED_PIXEW_STWEAM_24) | PKT_WEN1(3) |
	       PKT_ID2(MIPI_DSI_BWANKING_PACKET) | PKT_WEN2(4),
};

/*
 * non-buwst mode with sync events
 */
static const u32 pkt_seq_video_non_buwst_sync_events[NUM_PKT_SEQ] = {
	[ 0] = PKT_ID0(MIPI_DSI_V_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TWANSMISSION) | PKT_WEN1(7) |
	       PKT_WP,
	[ 1] = 0,
	[ 2] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TWANSMISSION) | PKT_WEN1(7) |
	       PKT_WP,
	[ 3] = 0,
	[ 4] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TWANSMISSION) | PKT_WEN1(7) |
	       PKT_WP,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(2) |
	       PKT_ID2(MIPI_DSI_PACKED_PIXEW_STWEAM_24) | PKT_WEN2(3),
	[ 7] = PKT_ID0(MIPI_DSI_BWANKING_PACKET) | PKT_WEN0(4),
	[ 8] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_END_OF_TWANSMISSION) | PKT_WEN1(7) |
	       PKT_WP,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_H_SYNC_STAWT) | PKT_WEN0(0) |
	       PKT_ID1(MIPI_DSI_BWANKING_PACKET) | PKT_WEN1(2) |
	       PKT_ID2(MIPI_DSI_PACKED_PIXEW_STWEAM_24) | PKT_WEN2(3),
	[11] = PKT_ID0(MIPI_DSI_BWANKING_PACKET) | PKT_WEN0(4),
};

static const u32 pkt_seq_command_mode[NUM_PKT_SEQ] = {
	[ 0] = 0,
	[ 1] = 0,
	[ 2] = 0,
	[ 3] = 0,
	[ 4] = 0,
	[ 5] = 0,
	[ 6] = PKT_ID0(MIPI_DSI_DCS_WONG_WWITE) | PKT_WEN0(3) | PKT_WP,
	[ 7] = 0,
	[ 8] = 0,
	[ 9] = 0,
	[10] = PKT_ID0(MIPI_DSI_DCS_WONG_WWITE) | PKT_WEN0(5) | PKT_WP,
	[11] = 0,
};

static void tegwa_dsi_set_phy_timing(stwuct tegwa_dsi *dsi,
				     unsigned wong pewiod,
				     const stwuct mipi_dphy_timing *timing)
{
	u32 vawue;

	vawue = DSI_TIMING_FIEWD(timing->hsexit, pewiod, 1) << 24 |
		DSI_TIMING_FIEWD(timing->hstwaiw, pewiod, 0) << 16 |
		DSI_TIMING_FIEWD(timing->hszewo, pewiod, 3) << 8 |
		DSI_TIMING_FIEWD(timing->hspwepawe, pewiod, 1);
	tegwa_dsi_wwitew(dsi, vawue, DSI_PHY_TIMING_0);

	vawue = DSI_TIMING_FIEWD(timing->cwktwaiw, pewiod, 1) << 24 |
		DSI_TIMING_FIEWD(timing->cwkpost, pewiod, 1) << 16 |
		DSI_TIMING_FIEWD(timing->cwkzewo, pewiod, 1) << 8 |
		DSI_TIMING_FIEWD(timing->wpx, pewiod, 1);
	tegwa_dsi_wwitew(dsi, vawue, DSI_PHY_TIMING_1);

	vawue = DSI_TIMING_FIEWD(timing->cwkpwepawe, pewiod, 1) << 16 |
		DSI_TIMING_FIEWD(timing->cwkpwe, pewiod, 1) << 8 |
		DSI_TIMING_FIEWD(0xff * pewiod, pewiod, 0) << 0;
	tegwa_dsi_wwitew(dsi, vawue, DSI_PHY_TIMING_2);

	vawue = DSI_TIMING_FIEWD(timing->taget, pewiod, 1) << 16 |
		DSI_TIMING_FIEWD(timing->tasuwe, pewiod, 1) << 8 |
		DSI_TIMING_FIEWD(timing->tago, pewiod, 1);
	tegwa_dsi_wwitew(dsi, vawue, DSI_BTA_TIMING);

	if (dsi->swave)
		tegwa_dsi_set_phy_timing(dsi->swave, pewiod, timing);
}

static int tegwa_dsi_get_muwdiv(enum mipi_dsi_pixew_fowmat fowmat,
				unsigned int *muwp, unsigned int *divp)
{
	switch (fowmat) {
	case MIPI_DSI_FMT_WGB666_PACKED:
	case MIPI_DSI_FMT_WGB888:
		*muwp = 3;
		*divp = 1;
		bweak;

	case MIPI_DSI_FMT_WGB565:
		*muwp = 2;
		*divp = 1;
		bweak;

	case MIPI_DSI_FMT_WGB666:
		*muwp = 9;
		*divp = 4;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa_dsi_get_fowmat(enum mipi_dsi_pixew_fowmat fowmat,
				enum tegwa_dsi_fowmat *fmt)
{
	switch (fowmat) {
	case MIPI_DSI_FMT_WGB888:
		*fmt = TEGWA_DSI_FOWMAT_24P;
		bweak;

	case MIPI_DSI_FMT_WGB666:
		*fmt = TEGWA_DSI_FOWMAT_18NP;
		bweak;

	case MIPI_DSI_FMT_WGB666_PACKED:
		*fmt = TEGWA_DSI_FOWMAT_18P;
		bweak;

	case MIPI_DSI_FMT_WGB565:
		*fmt = TEGWA_DSI_FOWMAT_16P;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void tegwa_dsi_ganged_enabwe(stwuct tegwa_dsi *dsi, unsigned int stawt,
				    unsigned int size)
{
	u32 vawue;

	tegwa_dsi_wwitew(dsi, stawt, DSI_GANGED_MODE_STAWT);
	tegwa_dsi_wwitew(dsi, size << 16 | size, DSI_GANGED_MODE_SIZE);

	vawue = DSI_GANGED_MODE_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_GANGED_MODE_CONTWOW);
}

static void tegwa_dsi_enabwe(stwuct tegwa_dsi *dsi)
{
	u32 vawue;

	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);
	vawue |= DSI_POWEW_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_POWEW_CONTWOW);

	if (dsi->swave)
		tegwa_dsi_enabwe(dsi->swave);
}

static unsigned int tegwa_dsi_get_wanes(stwuct tegwa_dsi *dsi)
{
	if (dsi->mastew)
		wetuwn dsi->mastew->wanes + dsi->wanes;

	if (dsi->swave)
		wetuwn dsi->wanes + dsi->swave->wanes;

	wetuwn dsi->wanes;
}

static void tegwa_dsi_configuwe(stwuct tegwa_dsi *dsi, unsigned int pipe,
				const stwuct dwm_dispway_mode *mode)
{
	unsigned int hact, hsw, hbp, hfp, i, muw, div;
	stwuct tegwa_dsi_state *state;
	const u32 *pkt_seq;
	u32 vawue;

	/* XXX: pass in state into this function? */
	if (dsi->mastew)
		state = tegwa_dsi_get_state(dsi->mastew);
	ewse
		state = tegwa_dsi_get_state(dsi);

	muw = state->muw;
	div = state->div;

	if (dsi->fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) {
		DWM_DEBUG_KMS("Non-buwst video mode with sync puwses\n");
		pkt_seq = pkt_seq_video_non_buwst_sync_puwses;
	} ewse if (dsi->fwags & MIPI_DSI_MODE_VIDEO) {
		DWM_DEBUG_KMS("Non-buwst video mode with sync events\n");
		pkt_seq = pkt_seq_video_non_buwst_sync_events;
	} ewse {
		DWM_DEBUG_KMS("Command mode\n");
		pkt_seq = pkt_seq_command_mode;
	}

	vawue = DSI_CONTWOW_CHANNEW(0) |
		DSI_CONTWOW_FOWMAT(state->fowmat) |
		DSI_CONTWOW_WANES(dsi->wanes - 1) |
		DSI_CONTWOW_SOUWCE(pipe);
	tegwa_dsi_wwitew(dsi, vawue, DSI_CONTWOW);

	tegwa_dsi_wwitew(dsi, dsi->video_fifo_depth, DSI_MAX_THWESHOWD);

	vawue = DSI_HOST_CONTWOW_HS;
	tegwa_dsi_wwitew(dsi, vawue, DSI_HOST_CONTWOW);

	vawue = tegwa_dsi_weadw(dsi, DSI_CONTWOW);

	if (dsi->fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS)
		vawue |= DSI_CONTWOW_HS_CWK_CTWW;

	vawue &= ~DSI_CONTWOW_TX_TWIG(3);

	/* enabwe DCS commands fow command mode */
	if (dsi->fwags & MIPI_DSI_MODE_VIDEO)
		vawue &= ~DSI_CONTWOW_DCS_ENABWE;
	ewse
		vawue |= DSI_CONTWOW_DCS_ENABWE;

	vawue |= DSI_CONTWOW_VIDEO_ENABWE;
	vawue &= ~DSI_CONTWOW_HOST_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_CONTWOW);

	fow (i = 0; i < NUM_PKT_SEQ; i++)
		tegwa_dsi_wwitew(dsi, pkt_seq[i], DSI_PKT_SEQ_0_WO + i);

	if (dsi->fwags & MIPI_DSI_MODE_VIDEO) {
		/* howizontaw active pixews */
		hact = mode->hdispway * muw / div;

		/* howizontaw sync width */
		hsw = (mode->hsync_end - mode->hsync_stawt) * muw / div;

		/* howizontaw back powch */
		hbp = (mode->htotaw - mode->hsync_end) * muw / div;

		if ((dsi->fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE) == 0)
			hbp += hsw;

		/* howizontaw fwont powch */
		hfp = (mode->hsync_stawt - mode->hdispway) * muw / div;

		/* subtwact packet ovewhead */
		hsw -= 10;
		hbp -= 14;
		hfp -= 8;

		tegwa_dsi_wwitew(dsi, hsw << 16 | 0, DSI_PKT_WEN_0_1);
		tegwa_dsi_wwitew(dsi, hact << 16 | hbp, DSI_PKT_WEN_2_3);
		tegwa_dsi_wwitew(dsi, hfp, DSI_PKT_WEN_4_5);
		tegwa_dsi_wwitew(dsi, 0x0f0f << 16, DSI_PKT_WEN_6_7);

		/* set SOW deway (fow non-buwst mode onwy) */
		tegwa_dsi_wwitew(dsi, 8 * muw / div, DSI_SOW_DEWAY);

		/* TODO: impwement ganged mode */
	} ewse {
		u16 bytes;

		if (dsi->mastew || dsi->swave) {
			/*
			 * Fow ganged mode, assume symmetwic weft-wight mode.
			 */
			bytes = 1 + (mode->hdispway / 2) * muw / div;
		} ewse {
			/* 1 byte (DCS command) + pixew data */
			bytes = 1 + mode->hdispway * muw / div;
		}

		tegwa_dsi_wwitew(dsi, 0, DSI_PKT_WEN_0_1);
		tegwa_dsi_wwitew(dsi, bytes << 16, DSI_PKT_WEN_2_3);
		tegwa_dsi_wwitew(dsi, bytes << 16, DSI_PKT_WEN_4_5);
		tegwa_dsi_wwitew(dsi, 0, DSI_PKT_WEN_6_7);

		vawue = MIPI_DCS_WWITE_MEMOWY_STAWT << 8 |
			MIPI_DCS_WWITE_MEMOWY_CONTINUE;
		tegwa_dsi_wwitew(dsi, vawue, DSI_DCS_CMDS);

		/* set SOW deway */
		if (dsi->mastew || dsi->swave) {
			unsigned wong deway, bcwk, bcwk_ganged;
			unsigned int wanes = state->wanes;

			/* SOW to vawid, vawid to FIFO and FIFO wwite deway */
			deway = 4 + 4 + 2;
			deway = DIV_WOUND_UP(deway * muw, div * wanes);
			/* FIFO wead deway */
			deway = deway + 6;

			bcwk = DIV_WOUND_UP(mode->htotaw * muw, div * wanes);
			bcwk_ganged = DIV_WOUND_UP(bcwk * wanes / 2, wanes);
			vawue = bcwk - bcwk_ganged + deway + 20;
		} ewse {
			/* TODO: wevisit fow non-ganged mode */
			vawue = 8 * muw / div;
		}

		tegwa_dsi_wwitew(dsi, vawue, DSI_SOW_DEWAY);
	}

	if (dsi->swave) {
		tegwa_dsi_configuwe(dsi->swave, pipe, mode);

		/*
		 * TODO: Suppowt modes othew than symmetwicaw weft-wight
		 * spwit.
		 */
		tegwa_dsi_ganged_enabwe(dsi, 0, mode->hdispway / 2);
		tegwa_dsi_ganged_enabwe(dsi->swave, mode->hdispway / 2,
					mode->hdispway / 2);
	}
}

static int tegwa_dsi_wait_idwe(stwuct tegwa_dsi *dsi, unsigned wong timeout)
{
	u32 vawue;

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		vawue = tegwa_dsi_weadw(dsi, DSI_STATUS);
		if (vawue & DSI_STATUS_IDWE)
			wetuwn 0;

		usweep_wange(1000, 2000);
	}

	wetuwn -ETIMEDOUT;
}

static void tegwa_dsi_video_disabwe(stwuct tegwa_dsi *dsi)
{
	u32 vawue;

	vawue = tegwa_dsi_weadw(dsi, DSI_CONTWOW);
	vawue &= ~DSI_CONTWOW_VIDEO_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_CONTWOW);

	if (dsi->swave)
		tegwa_dsi_video_disabwe(dsi->swave);
}

static void tegwa_dsi_ganged_disabwe(stwuct tegwa_dsi *dsi)
{
	tegwa_dsi_wwitew(dsi, 0, DSI_GANGED_MODE_STAWT);
	tegwa_dsi_wwitew(dsi, 0, DSI_GANGED_MODE_SIZE);
	tegwa_dsi_wwitew(dsi, 0, DSI_GANGED_MODE_CONTWOW);
}

static int tegwa_dsi_pad_enabwe(stwuct tegwa_dsi *dsi)
{
	u32 vawue;

	vawue = DSI_PAD_CONTWOW_VS1_PUWWDN(0) | DSI_PAD_CONTWOW_VS1_PDIO(0);
	tegwa_dsi_wwitew(dsi, vawue, DSI_PAD_CONTWOW_0);

	wetuwn 0;
}

static int tegwa_dsi_pad_cawibwate(stwuct tegwa_dsi *dsi)
{
	u32 vawue;
	int eww;

	/*
	 * XXX Is this stiww needed? The moduwe weset is deassewted wight
	 * befowe this function is cawwed.
	 */
	tegwa_dsi_wwitew(dsi, 0, DSI_PAD_CONTWOW_0);
	tegwa_dsi_wwitew(dsi, 0, DSI_PAD_CONTWOW_1);
	tegwa_dsi_wwitew(dsi, 0, DSI_PAD_CONTWOW_2);
	tegwa_dsi_wwitew(dsi, 0, DSI_PAD_CONTWOW_3);
	tegwa_dsi_wwitew(dsi, 0, DSI_PAD_CONTWOW_4);

	/* stawt cawibwation */
	tegwa_dsi_pad_enabwe(dsi);

	vawue = DSI_PAD_SWEW_UP(0x7) | DSI_PAD_SWEW_DN(0x7) |
		DSI_PAD_WP_UP(0x1) | DSI_PAD_WP_DN(0x1) |
		DSI_PAD_OUT_CWK(0x0);
	tegwa_dsi_wwitew(dsi, vawue, DSI_PAD_CONTWOW_2);

	vawue = DSI_PAD_PWEEMP_PD_CWK(0x3) | DSI_PAD_PWEEMP_PU_CWK(0x3) |
		DSI_PAD_PWEEMP_PD(0x03) | DSI_PAD_PWEEMP_PU(0x3);
	tegwa_dsi_wwitew(dsi, vawue, DSI_PAD_CONTWOW_3);

	eww = tegwa_mipi_stawt_cawibwation(dsi->mipi);
	if (eww < 0)
		wetuwn eww;

	wetuwn tegwa_mipi_finish_cawibwation(dsi->mipi);
}

static void tegwa_dsi_set_timeout(stwuct tegwa_dsi *dsi, unsigned wong bcwk,
				  unsigned int vwefwesh)
{
	unsigned int timeout;
	u32 vawue;

	/* one fwame high-speed twansmission timeout */
	timeout = (bcwk / vwefwesh) / 512;
	vawue = DSI_TIMEOUT_WWX(0x2000) | DSI_TIMEOUT_HTX(timeout);
	tegwa_dsi_wwitew(dsi, vawue, DSI_TIMEOUT_0);

	/* 2 ms pewiphewaw timeout fow panew */
	timeout = 2 * bcwk / 512 * 1000;
	vawue = DSI_TIMEOUT_PW(timeout) | DSI_TIMEOUT_TA(0x2000);
	tegwa_dsi_wwitew(dsi, vawue, DSI_TIMEOUT_1);

	vawue = DSI_TAWWY_TA(0) | DSI_TAWWY_WWX(0) | DSI_TAWWY_HTX(0);
	tegwa_dsi_wwitew(dsi, vawue, DSI_TO_TAWWY);

	if (dsi->swave)
		tegwa_dsi_set_timeout(dsi->swave, bcwk, vwefwesh);
}

static void tegwa_dsi_disabwe(stwuct tegwa_dsi *dsi)
{
	u32 vawue;

	if (dsi->swave) {
		tegwa_dsi_ganged_disabwe(dsi->swave);
		tegwa_dsi_ganged_disabwe(dsi);
	}

	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);
	vawue &= ~DSI_POWEW_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_POWEW_CONTWOW);

	if (dsi->swave)
		tegwa_dsi_disabwe(dsi->swave);

	usweep_wange(5000, 10000);
}

static void tegwa_dsi_soft_weset(stwuct tegwa_dsi *dsi)
{
	u32 vawue;

	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);
	vawue &= ~DSI_POWEW_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_POWEW_CONTWOW);

	usweep_wange(300, 1000);

	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);
	vawue |= DSI_POWEW_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_POWEW_CONTWOW);

	usweep_wange(300, 1000);

	vawue = tegwa_dsi_weadw(dsi, DSI_TWIGGEW);
	if (vawue)
		tegwa_dsi_wwitew(dsi, 0, DSI_TWIGGEW);

	if (dsi->swave)
		tegwa_dsi_soft_weset(dsi->swave);
}

static void tegwa_dsi_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_dsi_state *state = kzawwoc(sizeof(*state), GFP_KEWNEW);

	if (!state)
		wetuwn;

	if (connectow->state) {
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);
		kfwee(connectow->state);
	}

	__dwm_atomic_hewpew_connectow_weset(connectow, &state->base);
}

static stwuct dwm_connectow_state *
tegwa_dsi_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct tegwa_dsi_state *state = to_dsi_state(connectow->state);
	stwuct tegwa_dsi_state *copy;

	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow,
						      &copy->base);

	wetuwn &copy->base;
}

static const stwuct dwm_connectow_funcs tegwa_dsi_connectow_funcs = {
	.weset = tegwa_dsi_connectow_weset,
	.detect = tegwa_output_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = tegwa_output_connectow_destwoy,
	.atomic_dupwicate_state = tegwa_dsi_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
	.wate_wegistew = tegwa_dsi_wate_wegistew,
	.eawwy_unwegistew = tegwa_dsi_eawwy_unwegistew,
};

static enum dwm_mode_status
tegwa_dsi_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs tegwa_dsi_connectow_hewpew_funcs = {
	.get_modes = tegwa_output_connectow_get_modes,
	.mode_vawid = tegwa_dsi_connectow_mode_vawid,
};

static void tegwa_dsi_unpwepawe(stwuct tegwa_dsi *dsi)
{
	int eww;

	if (dsi->swave)
		tegwa_dsi_unpwepawe(dsi->swave);

	eww = tegwa_mipi_disabwe(dsi->mipi);
	if (eww < 0)
		dev_eww(dsi->dev, "faiwed to disabwe MIPI cawibwation: %d\n",
			eww);

	eww = host1x_cwient_suspend(&dsi->cwient);
	if (eww < 0)
		dev_eww(dsi->dev, "faiwed to suspend: %d\n", eww);
}

static void tegwa_dsi_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_dsi *dsi = to_dsi(output);
	u32 vawue;
	int eww;

	if (output->panew)
		dwm_panew_disabwe(output->panew);

	tegwa_dsi_video_disabwe(dsi);

	/*
	 * The fowwowing accesses wegistews of the dispway contwowwew, so make
	 * suwe it's onwy executed when the output is attached to one.
	 */
	if (dc) {
		vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
		vawue &= ~DSI_ENABWE;
		tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

		tegwa_dc_commit(dc);
	}

	eww = tegwa_dsi_wait_idwe(dsi, 100);
	if (eww < 0)
		dev_dbg(dsi->dev, "faiwed to idwe DSI: %d\n", eww);

	tegwa_dsi_soft_weset(dsi);

	if (output->panew)
		dwm_panew_unpwepawe(output->panew);

	tegwa_dsi_disabwe(dsi);

	tegwa_dsi_unpwepawe(dsi);
}

static int tegwa_dsi_pwepawe(stwuct tegwa_dsi *dsi)
{
	int eww;

	eww = host1x_cwient_wesume(&dsi->cwient);
	if (eww < 0) {
		dev_eww(dsi->dev, "faiwed to wesume: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa_mipi_enabwe(dsi->mipi);
	if (eww < 0)
		dev_eww(dsi->dev, "faiwed to enabwe MIPI cawibwation: %d\n",
			eww);

	eww = tegwa_dsi_pad_cawibwate(dsi);
	if (eww < 0)
		dev_eww(dsi->dev, "MIPI cawibwation faiwed: %d\n", eww);

	if (dsi->swave)
		tegwa_dsi_pwepawe(dsi->swave);

	wetuwn 0;
}

static void tegwa_dsi_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct dwm_dispway_mode *mode = &encodew->cwtc->state->adjusted_mode;
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dc *dc = to_tegwa_dc(encodew->cwtc);
	stwuct tegwa_dsi *dsi = to_dsi(output);
	stwuct tegwa_dsi_state *state;
	u32 vawue;
	int eww;

	/* If the bootwoadew enabwed DSI it needs to be disabwed
	 * in owdew fow the panew initiawization commands to be
	 * pwopewwy sent.
	 */
	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);

	if (vawue & DSI_POWEW_CONTWOW_ENABWE)
		tegwa_dsi_disabwe(dsi);

	eww = tegwa_dsi_pwepawe(dsi);
	if (eww < 0) {
		dev_eww(dsi->dev, "faiwed to pwepawe: %d\n", eww);
		wetuwn;
	}

	state = tegwa_dsi_get_state(dsi);

	tegwa_dsi_set_timeout(dsi, state->bcwk, state->vwefwesh);

	/*
	 * The D-PHY timing fiewds awe expwessed in byte-cwock cycwes, so
	 * muwtipwy the pewiod by 8.
	 */
	tegwa_dsi_set_phy_timing(dsi, state->pewiod * 8, &state->timing);

	if (output->panew)
		dwm_panew_pwepawe(output->panew);

	tegwa_dsi_configuwe(dsi, dc->pipe, mode);

	/* enabwe dispway contwowwew */
	vawue = tegwa_dc_weadw(dc, DC_DISP_DISP_WIN_OPTIONS);
	vawue |= DSI_ENABWE;
	tegwa_dc_wwitew(dc, vawue, DC_DISP_DISP_WIN_OPTIONS);

	tegwa_dc_commit(dc);

	/* enabwe DSI contwowwew */
	tegwa_dsi_enabwe(dsi);

	if (output->panew)
		dwm_panew_enabwe(output->panew);
}

static int
tegwa_dsi_encodew_atomic_check(stwuct dwm_encodew *encodew,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state)
{
	stwuct tegwa_output *output = encodew_to_output(encodew);
	stwuct tegwa_dsi_state *state = to_dsi_state(conn_state);
	stwuct tegwa_dc *dc = to_tegwa_dc(conn_state->cwtc);
	stwuct tegwa_dsi *dsi = to_dsi(output);
	unsigned int scdiv;
	unsigned wong pwwd;
	int eww;

	state->pcwk = cwtc_state->mode.cwock * 1000;

	eww = tegwa_dsi_get_muwdiv(dsi->fowmat, &state->muw, &state->div);
	if (eww < 0)
		wetuwn eww;

	state->wanes = tegwa_dsi_get_wanes(dsi);

	eww = tegwa_dsi_get_fowmat(dsi->fowmat, &state->fowmat);
	if (eww < 0)
		wetuwn eww;

	state->vwefwesh = dwm_mode_vwefwesh(&cwtc_state->mode);

	/* compute byte cwock */
	state->bcwk = (state->pcwk * state->muw) / (state->div * state->wanes);

	DWM_DEBUG_KMS("muw: %u, div: %u, wanes: %u\n", state->muw, state->div,
		      state->wanes);
	DWM_DEBUG_KMS("fowmat: %u, vwefwesh: %u\n", state->fowmat,
		      state->vwefwesh);
	DWM_DEBUG_KMS("bcwk: %wu\n", state->bcwk);

	/*
	 * Compute bit cwock and wound up to the next MHz.
	 */
	pwwd = DIV_WOUND_UP(state->bcwk * 8, USEC_PEW_SEC) * USEC_PEW_SEC;
	state->pewiod = DIV_WOUND_CWOSEST(NSEC_PEW_SEC, pwwd);

	eww = mipi_dphy_timing_get_defauwt(&state->timing, state->pewiod);
	if (eww < 0)
		wetuwn eww;

	eww = mipi_dphy_timing_vawidate(&state->timing, state->pewiod);
	if (eww < 0) {
		dev_eww(dsi->dev, "faiwed to vawidate D-PHY timing: %d\n", eww);
		wetuwn eww;
	}

	/*
	 * We divide the fwequency by two hewe, but we make up fow that by
	 * setting the shift cwock dividew (fuwthew bewow) to hawf of the
	 * cowwect vawue.
	 */
	pwwd /= 2;

	/*
	 * Dewive pixew cwock fwom bit cwock using the shift cwock dividew.
	 * Note that this is onwy hawf of what we wouwd expect, but we need
	 * that to make up fow the fact that we divided the bit cwock by a
	 * factow of two above.
	 *
	 * It's not cweaw exactwy why this is necessawy, but the dispway is
	 * not wowking pwopewwy othewwise. Pewhaps the PWWs cannot genewate
	 * fwequencies sufficientwy high.
	 */
	scdiv = ((8 * state->muw) / (state->div * state->wanes)) - 2;

	eww = tegwa_dc_state_setup_cwock(dc, cwtc_state, dsi->cwk_pawent,
					 pwwd, scdiv);
	if (eww < 0) {
		dev_eww(output->dev, "faiwed to setup CWTC state: %d\n", eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static const stwuct dwm_encodew_hewpew_funcs tegwa_dsi_encodew_hewpew_funcs = {
	.disabwe = tegwa_dsi_encodew_disabwe,
	.enabwe = tegwa_dsi_encodew_enabwe,
	.atomic_check = tegwa_dsi_encodew_atomic_check,
};

static int tegwa_dsi_init(stwuct host1x_cwient *cwient)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(cwient->host);
	stwuct tegwa_dsi *dsi = host1x_cwient_to_dsi(cwient);
	int eww;

	/* Gangstews must not wegistew theiw own outputs. */
	if (!dsi->mastew) {
		dsi->output.dev = cwient->dev;

		dwm_connectow_init(dwm, &dsi->output.connectow,
				   &tegwa_dsi_connectow_funcs,
				   DWM_MODE_CONNECTOW_DSI);
		dwm_connectow_hewpew_add(&dsi->output.connectow,
					 &tegwa_dsi_connectow_hewpew_funcs);
		dsi->output.connectow.dpms = DWM_MODE_DPMS_OFF;

		dwm_simpwe_encodew_init(dwm, &dsi->output.encodew,
					DWM_MODE_ENCODEW_DSI);
		dwm_encodew_hewpew_add(&dsi->output.encodew,
				       &tegwa_dsi_encodew_hewpew_funcs);

		dwm_connectow_attach_encodew(&dsi->output.connectow,
						  &dsi->output.encodew);
		dwm_connectow_wegistew(&dsi->output.connectow);

		eww = tegwa_output_init(dwm, &dsi->output);
		if (eww < 0)
			dev_eww(dsi->dev, "faiwed to initiawize output: %d\n",
				eww);

		dsi->output.encodew.possibwe_cwtcs = 0x3;
	}

	wetuwn 0;
}

static int tegwa_dsi_exit(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dsi *dsi = host1x_cwient_to_dsi(cwient);

	tegwa_output_exit(&dsi->output);

	wetuwn 0;
}

static int tegwa_dsi_wuntime_suspend(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dsi *dsi = host1x_cwient_to_dsi(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	if (dsi->wst) {
		eww = weset_contwow_assewt(dsi->wst);
		if (eww < 0) {
			dev_eww(dev, "faiwed to assewt weset: %d\n", eww);
			wetuwn eww;
		}
	}

	usweep_wange(1000, 2000);

	cwk_disabwe_unpwepawe(dsi->cwk_wp);
	cwk_disabwe_unpwepawe(dsi->cwk);

	weguwatow_disabwe(dsi->vdd);
	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

static int tegwa_dsi_wuntime_wesume(stwuct host1x_cwient *cwient)
{
	stwuct tegwa_dsi *dsi = host1x_cwient_to_dsi(cwient);
	stwuct device *dev = cwient->dev;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "faiwed to get wuntime PM: %d\n", eww);
		wetuwn eww;
	}

	eww = weguwatow_enabwe(dsi->vdd);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe VDD suppwy: %d\n", eww);
		goto put_wpm;
	}

	eww = cwk_pwepawe_enabwe(dsi->cwk);
	if (eww < 0) {
		dev_eww(dev, "cannot enabwe DSI cwock: %d\n", eww);
		goto disabwe_vdd;
	}

	eww = cwk_pwepawe_enabwe(dsi->cwk_wp);
	if (eww < 0) {
		dev_eww(dev, "cannot enabwe wow-powew cwock: %d\n", eww);
		goto disabwe_cwk;
	}

	usweep_wange(1000, 2000);

	if (dsi->wst) {
		eww = weset_contwow_deassewt(dsi->wst);
		if (eww < 0) {
			dev_eww(dev, "cannot assewt weset: %d\n", eww);
			goto disabwe_cwk_wp;
		}
	}

	wetuwn 0;

disabwe_cwk_wp:
	cwk_disabwe_unpwepawe(dsi->cwk_wp);
disabwe_cwk:
	cwk_disabwe_unpwepawe(dsi->cwk);
disabwe_vdd:
	weguwatow_disabwe(dsi->vdd);
put_wpm:
	pm_wuntime_put_sync(dev);
	wetuwn eww;
}

static const stwuct host1x_cwient_ops dsi_cwient_ops = {
	.init = tegwa_dsi_init,
	.exit = tegwa_dsi_exit,
	.suspend = tegwa_dsi_wuntime_suspend,
	.wesume = tegwa_dsi_wuntime_wesume,
};

static int tegwa_dsi_setup_cwocks(stwuct tegwa_dsi *dsi)
{
	stwuct cwk *pawent;
	int eww;

	pawent = cwk_get_pawent(dsi->cwk);
	if (!pawent)
		wetuwn -EINVAW;

	eww = cwk_set_pawent(pawent, dsi->cwk_pawent);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static const chaw * const ewwow_wepowt[16] = {
	"SoT Ewwow",
	"SoT Sync Ewwow",
	"EoT Sync Ewwow",
	"Escape Mode Entwy Command Ewwow",
	"Wow-Powew Twansmit Sync Ewwow",
	"Pewiphewaw Timeout Ewwow",
	"Fawse Contwow Ewwow",
	"Contention Detected",
	"ECC Ewwow, singwe-bit",
	"ECC Ewwow, muwti-bit",
	"Checksum Ewwow",
	"DSI Data Type Not Wecognized",
	"DSI VC ID Invawid",
	"Invawid Twansmission Wength",
	"Wesewved",
	"DSI Pwotocow Viowation",
};

static ssize_t tegwa_dsi_wead_wesponse(stwuct tegwa_dsi *dsi,
				       const stwuct mipi_dsi_msg *msg,
				       size_t count)
{
	u8 *wx = msg->wx_buf;
	unsigned int i, j, k;
	size_t size = 0;
	u16 ewwows;
	u32 vawue;

	/* wead and pawse packet headew */
	vawue = tegwa_dsi_weadw(dsi, DSI_WD_DATA);

	switch (vawue & 0x3f) {
	case MIPI_DSI_WX_ACKNOWWEDGE_AND_EWWOW_WEPOWT:
		ewwows = (vawue >> 8) & 0xffff;
		dev_dbg(dsi->dev, "Acknowwedge and ewwow wepowt: %04x\n",
			ewwows);
		fow (i = 0; i < AWWAY_SIZE(ewwow_wepowt); i++)
			if (ewwows & BIT(i))
				dev_dbg(dsi->dev, "  %2u: %s\n", i,
					ewwow_wepowt[i]);
		bweak;

	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_1BYTE:
		wx[0] = (vawue >> 8) & 0xff;
		size = 1;
		bweak;

	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_2BYTE:
		wx[0] = (vawue >>  8) & 0xff;
		wx[1] = (vawue >> 16) & 0xff;
		size = 2;
		bweak;

	case MIPI_DSI_WX_DCS_WONG_WEAD_WESPONSE:
		size = ((vawue >> 8) & 0xff00) | ((vawue >> 8) & 0xff);
		bweak;

	case MIPI_DSI_WX_GENEWIC_WONG_WEAD_WESPONSE:
		size = ((vawue >> 8) & 0xff00) | ((vawue >> 8) & 0xff);
		bweak;

	defauwt:
		dev_eww(dsi->dev, "unhandwed wesponse type: %02x\n",
			vawue & 0x3f);
		wetuwn -EPWOTO;
	}

	size = min(size, msg->wx_wen);

	if (msg->wx_buf && size > 0) {
		fow (i = 0, j = 0; i < count - 1; i++, j += 4) {
			u8 *wx = msg->wx_buf + j;

			vawue = tegwa_dsi_weadw(dsi, DSI_WD_DATA);

			fow (k = 0; k < 4 && (j + k) < msg->wx_wen; k++)
				wx[j + k] = (vawue >> (k << 3)) & 0xff;
		}
	}

	wetuwn size;
}

static int tegwa_dsi_twansmit(stwuct tegwa_dsi *dsi, unsigned wong timeout)
{
	tegwa_dsi_wwitew(dsi, DSI_TWIGGEW_HOST, DSI_TWIGGEW);

	timeout = jiffies + msecs_to_jiffies(timeout);

	whiwe (time_befowe(jiffies, timeout)) {
		u32 vawue = tegwa_dsi_weadw(dsi, DSI_TWIGGEW);
		if ((vawue & DSI_TWIGGEW_HOST) == 0)
			wetuwn 0;

		usweep_wange(1000, 2000);
	}

	DWM_DEBUG_KMS("timeout waiting fow twansmission to compwete\n");
	wetuwn -ETIMEDOUT;
}

static int tegwa_dsi_wait_fow_wesponse(stwuct tegwa_dsi *dsi,
				       unsigned wong timeout)
{
	timeout = jiffies + msecs_to_jiffies(250);

	whiwe (time_befowe(jiffies, timeout)) {
		u32 vawue = tegwa_dsi_weadw(dsi, DSI_STATUS);
		u8 count = vawue & 0x1f;

		if (count > 0)
			wetuwn count;

		usweep_wange(1000, 2000);
	}

	DWM_DEBUG_KMS("pewiphewaw wetuwned no data\n");
	wetuwn -ETIMEDOUT;
}

static void tegwa_dsi_wwitesw(stwuct tegwa_dsi *dsi, unsigned wong offset,
			      const void *buffew, size_t size)
{
	const u8 *buf = buffew;
	size_t i, j;
	u32 vawue;

	fow (j = 0; j < size; j += 4) {
		vawue = 0;

		fow (i = 0; i < 4 && j + i < size; i++)
			vawue |= buf[j + i] << (i << 3);

		tegwa_dsi_wwitew(dsi, vawue, DSI_WW_DATA);
	}
}

static ssize_t tegwa_dsi_host_twansfew(stwuct mipi_dsi_host *host,
				       const stwuct mipi_dsi_msg *msg)
{
	stwuct tegwa_dsi *dsi = host_to_tegwa(host);
	stwuct mipi_dsi_packet packet;
	const u8 *headew;
	size_t count;
	ssize_t eww;
	u32 vawue;

	eww = mipi_dsi_cweate_packet(&packet, msg);
	if (eww < 0)
		wetuwn eww;

	headew = packet.headew;

	/* maximum FIFO depth is 1920 wowds */
	if (packet.size > dsi->video_fifo_depth * 4)
		wetuwn -ENOSPC;

	/* weset undewfwow/ovewfwow fwags */
	vawue = tegwa_dsi_weadw(dsi, DSI_STATUS);
	if (vawue & (DSI_STATUS_UNDEWFWOW | DSI_STATUS_OVEWFWOW)) {
		vawue = DSI_HOST_CONTWOW_FIFO_WESET;
		tegwa_dsi_wwitew(dsi, vawue, DSI_HOST_CONTWOW);
		usweep_wange(10, 20);
	}

	vawue = tegwa_dsi_weadw(dsi, DSI_POWEW_CONTWOW);
	vawue |= DSI_POWEW_CONTWOW_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_POWEW_CONTWOW);

	usweep_wange(5000, 10000);

	vawue = DSI_HOST_CONTWOW_CWC_WESET | DSI_HOST_CONTWOW_TX_TWIG_HOST |
		DSI_HOST_CONTWOW_CS | DSI_HOST_CONTWOW_ECC;

	if ((msg->fwags & MIPI_DSI_MSG_USE_WPM) == 0)
		vawue |= DSI_HOST_CONTWOW_HS;

	/*
	 * The host FIFO has a maximum of 64 wowds, so wawgew twansmissions
	 * need to use the video FIFO.
	 */
	if (packet.size > dsi->host_fifo_depth * 4)
		vawue |= DSI_HOST_CONTWOW_FIFO_SEW;

	tegwa_dsi_wwitew(dsi, vawue, DSI_HOST_CONTWOW);

	/*
	 * Fow weads and messages with expwicitwy wequested ACK, genewate a
	 * BTA sequence aftew the twansmission of the packet.
	 */
	if ((msg->fwags & MIPI_DSI_MSG_WEQ_ACK) ||
	    (msg->wx_buf && msg->wx_wen > 0)) {
		vawue = tegwa_dsi_weadw(dsi, DSI_HOST_CONTWOW);
		vawue |= DSI_HOST_CONTWOW_PKT_BTA;
		tegwa_dsi_wwitew(dsi, vawue, DSI_HOST_CONTWOW);
	}

	vawue = DSI_CONTWOW_WANES(0) | DSI_CONTWOW_HOST_ENABWE;
	tegwa_dsi_wwitew(dsi, vawue, DSI_CONTWOW);

	/* wwite packet headew, ECC is genewated by hawdwawe */
	vawue = headew[2] << 16 | headew[1] << 8 | headew[0];
	tegwa_dsi_wwitew(dsi, vawue, DSI_WW_DATA);

	/* wwite paywoad (if any) */
	if (packet.paywoad_wength > 0)
		tegwa_dsi_wwitesw(dsi, DSI_WW_DATA, packet.paywoad,
				  packet.paywoad_wength);

	eww = tegwa_dsi_twansmit(dsi, 250);
	if (eww < 0)
		wetuwn eww;

	if ((msg->fwags & MIPI_DSI_MSG_WEQ_ACK) ||
	    (msg->wx_buf && msg->wx_wen > 0)) {
		eww = tegwa_dsi_wait_fow_wesponse(dsi, 250);
		if (eww < 0)
			wetuwn eww;

		count = eww;

		vawue = tegwa_dsi_weadw(dsi, DSI_WD_DATA);
		switch (vawue) {
		case 0x84:
			/*
			dev_dbg(dsi->dev, "ACK\n");
			*/
			bweak;

		case 0x87:
			/*
			dev_dbg(dsi->dev, "ESCAPE\n");
			*/
			bweak;

		defauwt:
			dev_eww(dsi->dev, "unknown status: %08x\n", vawue);
			bweak;
		}

		if (count > 1) {
			eww = tegwa_dsi_wead_wesponse(dsi, msg, count);
			if (eww < 0)
				dev_eww(dsi->dev,
					"faiwed to pawse wesponse: %zd\n",
					eww);
			ewse {
				/*
				 * Fow wead commands, wetuwn the numbew of
				 * bytes wetuwned by the pewiphewaw.
				 */
				count = eww;
			}
		}
	} ewse {
		/*
		 * Fow wwite commands, we have twansmitted the 4-byte headew
		 * pwus the vawiabwe-wength paywoad.
		 */
		count = 4 + packet.paywoad_wength;
	}

	wetuwn count;
}

static int tegwa_dsi_ganged_setup(stwuct tegwa_dsi *dsi)
{
	stwuct cwk *pawent;
	int eww;

	/* make suwe both DSI contwowwews shawe the same PWW */
	pawent = cwk_get_pawent(dsi->swave->cwk);
	if (!pawent)
		wetuwn -EINVAW;

	eww = cwk_set_pawent(pawent, dsi->cwk_pawent);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int tegwa_dsi_host_attach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *device)
{
	stwuct tegwa_dsi *dsi = host_to_tegwa(host);

	dsi->fwags = device->mode_fwags;
	dsi->fowmat = device->fowmat;
	dsi->wanes = device->wanes;

	if (dsi->swave) {
		int eww;

		dev_dbg(dsi->dev, "attaching duaw-channew device %s\n",
			dev_name(&device->dev));

		eww = tegwa_dsi_ganged_setup(dsi);
		if (eww < 0) {
			dev_eww(dsi->dev, "faiwed to set up ganged mode: %d\n",
				eww);
			wetuwn eww;
		}
	}

	/*
	 * Swaves don't have a panew associated with them, so they pwovide
	 * mewewy the second channew.
	 */
	if (!dsi->mastew) {
		stwuct tegwa_output *output = &dsi->output;

		output->panew = of_dwm_find_panew(device->dev.of_node);
		if (IS_EWW(output->panew))
			output->panew = NUWW;

		if (output->panew && output->connectow.dev)
			dwm_hewpew_hpd_iwq_event(output->connectow.dev);
	}

	wetuwn 0;
}

static int tegwa_dsi_host_detach(stwuct mipi_dsi_host *host,
				 stwuct mipi_dsi_device *device)
{
	stwuct tegwa_dsi *dsi = host_to_tegwa(host);
	stwuct tegwa_output *output = &dsi->output;

	if (output->panew && &device->dev == output->panew->dev) {
		output->panew = NUWW;

		if (output->connectow.dev)
			dwm_hewpew_hpd_iwq_event(output->connectow.dev);
	}

	wetuwn 0;
}

static const stwuct mipi_dsi_host_ops tegwa_dsi_host_ops = {
	.attach = tegwa_dsi_host_attach,
	.detach = tegwa_dsi_host_detach,
	.twansfew = tegwa_dsi_host_twansfew,
};

static int tegwa_dsi_ganged_pwobe(stwuct tegwa_dsi *dsi)
{
	stwuct device_node *np;

	np = of_pawse_phandwe(dsi->dev->of_node, "nvidia,ganged-mode", 0);
	if (np) {
		stwuct pwatfowm_device *gangstew = of_find_device_by_node(np);

		dsi->swave = pwatfowm_get_dwvdata(gangstew);
		of_node_put(np);

		if (!dsi->swave) {
			put_device(&gangstew->dev);
			wetuwn -EPWOBE_DEFEW;
		}

		dsi->swave->mastew = dsi;
	}

	wetuwn 0;
}

static int tegwa_dsi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dsi *dsi;
	stwuct wesouwce *wegs;
	int eww;

	dsi = devm_kzawwoc(&pdev->dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsi->output.dev = dsi->dev = &pdev->dev;
	dsi->video_fifo_depth = 1920;
	dsi->host_fifo_depth = 64;

	eww = tegwa_dsi_ganged_pwobe(dsi);
	if (eww < 0)
		wetuwn eww;

	eww = tegwa_output_pwobe(&dsi->output);
	if (eww < 0)
		wetuwn eww;

	dsi->output.connectow.powwed = DWM_CONNECTOW_POWW_HPD;

	/*
	 * Assume these vawues by defauwt. When a DSI pewiphewaw dwivew
	 * attaches to the DSI host, the pawametews wiww be taken fwom
	 * the attached device.
	 */
	dsi->fwags = MIPI_DSI_MODE_VIDEO;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->wanes = 4;

	if (!pdev->dev.pm_domain) {
		dsi->wst = devm_weset_contwow_get(&pdev->dev, "dsi");
		if (IS_EWW(dsi->wst))
			wetuwn PTW_EWW(dsi->wst);
	}

	dsi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dsi->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dsi->cwk),
				     "cannot get DSI cwock\n");

	dsi->cwk_wp = devm_cwk_get(&pdev->dev, "wp");
	if (IS_EWW(dsi->cwk_wp))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dsi->cwk_wp),
				     "cannot get wow-powew cwock\n");

	dsi->cwk_pawent = devm_cwk_get(&pdev->dev, "pawent");
	if (IS_EWW(dsi->cwk_pawent))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dsi->cwk_pawent),
				     "cannot get pawent cwock\n");

	dsi->vdd = devm_weguwatow_get(&pdev->dev, "avdd-dsi-csi");
	if (IS_EWW(dsi->vdd))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dsi->vdd),
				     "cannot get VDD suppwy\n");

	eww = tegwa_dsi_setup_cwocks(dsi);
	if (eww < 0) {
		dev_eww(&pdev->dev, "cannot setup cwocks\n");
		wetuwn eww;
	}

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	dsi->wegs = devm_iowemap_wesouwce(&pdev->dev, wegs);
	if (IS_EWW(dsi->wegs))
		wetuwn PTW_EWW(dsi->wegs);

	dsi->mipi = tegwa_mipi_wequest(&pdev->dev, pdev->dev.of_node);
	if (IS_EWW(dsi->mipi))
		wetuwn PTW_EWW(dsi->mipi);

	dsi->host.ops = &tegwa_dsi_host_ops;
	dsi->host.dev = &pdev->dev;

	eww = mipi_dsi_host_wegistew(&dsi->host);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew DSI host: %d\n", eww);
		goto mipi_fwee;
	}

	pwatfowm_set_dwvdata(pdev, dsi);
	pm_wuntime_enabwe(&pdev->dev);

	INIT_WIST_HEAD(&dsi->cwient.wist);
	dsi->cwient.ops = &dsi_cwient_ops;
	dsi->cwient.dev = &pdev->dev;

	eww = host1x_cwient_wegistew(&dsi->cwient);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wegistew host1x cwient: %d\n",
			eww);
		goto unwegistew;
	}

	wetuwn 0;

unwegistew:
	mipi_dsi_host_unwegistew(&dsi->host);
mipi_fwee:
	tegwa_mipi_fwee(dsi->mipi);
	wetuwn eww;
}

static void tegwa_dsi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_dsi *dsi = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	host1x_cwient_unwegistew(&dsi->cwient);

	tegwa_output_wemove(&dsi->output);

	mipi_dsi_host_unwegistew(&dsi->host);
	tegwa_mipi_fwee(dsi->mipi);
}

static const stwuct of_device_id tegwa_dsi_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-dsi", },
	{ .compatibwe = "nvidia,tegwa132-dsi", },
	{ .compatibwe = "nvidia,tegwa124-dsi", },
	{ .compatibwe = "nvidia,tegwa114-dsi", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_dsi_of_match);

stwuct pwatfowm_dwivew tegwa_dsi_dwivew = {
	.dwivew = {
		.name = "tegwa-dsi",
		.of_match_tabwe = tegwa_dsi_of_match,
	},
	.pwobe = tegwa_dsi_pwobe,
	.wemove_new = tegwa_dsi_wemove,
};
