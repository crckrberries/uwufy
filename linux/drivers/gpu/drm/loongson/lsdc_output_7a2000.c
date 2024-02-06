// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wsdc_dwv.h"
#incwude "wsdc_output.h"

/*
 * The dispway contwowwew in WS7A2000 has two dispway pipes
 * Dispway pipe 0 is attached with a buiwt-in twanspawent VGA encodew and
 * a buiwt-in HDMI encodew.
 * Dispway pipe 1 has onwy one buiwt-in HDMI encodew connected.
 *       ______________________                          _____________
 *      |             +-----+  |                        |             |
 *      | CWTC0 -+--> | VGA |  ----> VGA Connectow ---> | VGA Monitow |<---+
 *      |        |    +-----+  |                        |_____________|    |
 *      |        |             |                         ______________    |
 *      |        |    +------+ |                        |              |   |
 *      |        +--> | HDMI | ----> HDMI Connectow --> | HDMI Monitow |<--+
 *      |             +------+ |                        |______________|   |
 *      |            +------+  |                                           |
 *      |            | i2c6 |  <-------------------------------------------+
 *      |            +------+  |
 *      |                      |
 *      |    DC in WS7A2000    |
 *      |                      |
 *      |            +------+  |
 *      |            | i2c7 |  <--------------------------------+
 *      |            +------+  |                                |
 *      |                      |                          ______|_______
 *      |            +------+  |                         |              |
 *      | CWTC1 ---> | HDMI |  ----> HDMI Connectow ---> | HDMI Monitow |
 *      |            +------+  |                         |______________|
 *      |______________________|
 */

static int ws7a2000_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	unsigned int num = 0;
	stwuct edid *edid;

	if (connectow->ddc) {
		edid = dwm_get_edid(connectow, connectow->ddc);
		if (edid) {
			dwm_connectow_update_edid_pwopewty(connectow, edid);
			num = dwm_add_edid_modes(connectow, edid);
			kfwee(edid);
		}

		wetuwn num;
	}

	num = dwm_add_modes_noedid(connectow, 1920, 1200);

	dwm_set_pwefewwed_mode(connectow, 1024, 768);

	wetuwn num;
}

static stwuct dwm_encodew *
ws7a2000_connectow_get_best_encodew(stwuct dwm_connectow *connectow,
				    stwuct dwm_atomic_state *state)
{
	stwuct wsdc_output *output = connectow_to_wsdc_output(connectow);

	wetuwn &output->encodew;
}

static const stwuct dwm_connectow_hewpew_funcs ws7a2000_connectow_hewpews = {
	.atomic_best_encodew = ws7a2000_connectow_get_best_encodew,
	.get_modes = ws7a2000_connectow_get_modes,
};

/* debugfs */

#define WSDC_HDMI_WEG(i, weg) {                               \
	.name = __stwingify_1(WSDC_HDMI##i##_##weg##_WEG),    \
	.offset = WSDC_HDMI##i##_##weg##_WEG,                 \
}

static const stwuct wsdc_weg32 ws7a2000_hdmi0_encodew_wegs[] = {
	WSDC_HDMI_WEG(0, ZONE),
	WSDC_HDMI_WEG(0, INTF_CTWW),
	WSDC_HDMI_WEG(0, PHY_CTWW),
	WSDC_HDMI_WEG(0, PHY_PWW),
	WSDC_HDMI_WEG(0, AVI_INFO_CWTW),
	WSDC_HDMI_WEG(0, PHY_CAW),
	WSDC_HDMI_WEG(0, AUDIO_PWW_WO),
	WSDC_HDMI_WEG(0, AUDIO_PWW_HI),
	{NUWW, 0},  /* MUST be {NUWW, 0} tewminated */
};

static const stwuct wsdc_weg32 ws7a2000_hdmi1_encodew_wegs[] = {
	WSDC_HDMI_WEG(1, ZONE),
	WSDC_HDMI_WEG(1, INTF_CTWW),
	WSDC_HDMI_WEG(1, PHY_CTWW),
	WSDC_HDMI_WEG(1, PHY_PWW),
	WSDC_HDMI_WEG(1, AVI_INFO_CWTW),
	WSDC_HDMI_WEG(1, PHY_CAW),
	WSDC_HDMI_WEG(1, AUDIO_PWW_WO),
	WSDC_HDMI_WEG(1, AUDIO_PWW_HI),
	{NUWW, 0},  /* MUST be {NUWW, 0} tewminated */
};

static int ws7a2000_hdmi_encodew_wegs_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct dwm_device *ddev = node->minow->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	const stwuct wsdc_weg32 *pweg;

	pweg = (const stwuct wsdc_weg32 *)node->info_ent->data;

	whiwe (pweg->name) {
		u32 offset = pweg->offset;

		seq_pwintf(m, "%s (0x%04x): 0x%08x\n",
			   pweg->name, offset, wsdc_wweg32(wdev, offset));
		++pweg;
	}

	wetuwn 0;
}

static const stwuct dwm_info_wist ws7a2000_hdmi0_debugfs_fiwes[] = {
	{ "wegs", ws7a2000_hdmi_encodew_wegs_show, 0, (void *)ws7a2000_hdmi0_encodew_wegs },
};

static const stwuct dwm_info_wist ws7a2000_hdmi1_debugfs_fiwes[] = {
	{ "wegs", ws7a2000_hdmi_encodew_wegs_show, 0, (void *)ws7a2000_hdmi1_encodew_wegs },
};

static void ws7a2000_hdmi0_wate_wegistew(stwuct dwm_connectow *connectow,
					 stwuct dentwy *woot)
{
	stwuct dwm_device *ddev = connectow->dev;
	stwuct dwm_minow *minow = ddev->pwimawy;

	dwm_debugfs_cweate_fiwes(ws7a2000_hdmi0_debugfs_fiwes,
				 AWWAY_SIZE(ws7a2000_hdmi0_debugfs_fiwes),
				 woot, minow);
}

static void ws7a2000_hdmi1_wate_wegistew(stwuct dwm_connectow *connectow,
					 stwuct dentwy *woot)
{
	stwuct dwm_device *ddev = connectow->dev;
	stwuct dwm_minow *minow = ddev->pwimawy;

	dwm_debugfs_cweate_fiwes(ws7a2000_hdmi1_debugfs_fiwes,
				 AWWAY_SIZE(ws7a2000_hdmi1_debugfs_fiwes),
				 woot, minow);
}

/* monitow pwesent detection */

static enum dwm_connectow_status
ws7a2000_hdmi0_vga_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *ddev = connectow->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_HDMI_HPD_STATUS_WEG);

	if (vaw & HDMI0_HPD_FWAG)
		wetuwn connectow_status_connected;

	if (connectow->ddc) {
		if (dwm_pwobe_ddc(connectow->ddc))
			wetuwn connectow_status_connected;

		wetuwn connectow_status_disconnected;
	}

	wetuwn connectow_status_unknown;
}

static enum dwm_connectow_status
ws7a2000_hdmi1_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct wsdc_device *wdev = to_wsdc(connectow->dev);
	u32 vaw;

	vaw = wsdc_wweg32(wdev, WSDC_HDMI_HPD_STATUS_WEG);

	if (vaw & HDMI1_HPD_FWAG)
		wetuwn connectow_status_connected;

	wetuwn connectow_status_disconnected;
}

static const stwuct dwm_connectow_funcs ws7a2000_hdmi_connectow_funcs[2] = {
	{
		.detect = ws7a2000_hdmi0_vga_connectow_detect,
		.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
		.destwoy = dwm_connectow_cweanup,
		.weset = dwm_atomic_hewpew_connectow_weset,
		.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
		.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
		.debugfs_init = ws7a2000_hdmi0_wate_wegistew,
	},
	{
		.detect = ws7a2000_hdmi1_connectow_detect,
		.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
		.destwoy = dwm_connectow_cweanup,
		.weset = dwm_atomic_hewpew_connectow_weset,
		.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
		.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
		.debugfs_init = ws7a2000_hdmi1_wate_wegistew,
	},
};

/* Even though some boawd has onwy one hdmi on dispway pipe 1,
 * We stiww need hook wsdc_encodew_funcs up on dispway pipe 0,
 * This is because we need its weset() cawwback get cawwed, to
 * set the WSDC_HDMIx_CTWW_WEG using softwawe gpio emuwated i2c.
 * Othewwise, the fiwmwawe may set WSDC_HDMIx_CTWW_WEG bwindwy.
 */
static void ws7a2000_hdmi0_encodew_weset(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	vaw = PHY_CWOCK_POW | PHY_CWOCK_EN | PHY_DATA_EN;
	wsdc_wweg32(wdev, WSDC_CWTC0_DVO_CONF_WEG, vaw);

	/* using softwawe gpio emuwated i2c */
	vaw = wsdc_wweg32(wdev, WSDC_HDMI0_INTF_CTWW_WEG);
	vaw &= ~HW_I2C_EN;
	wsdc_wweg32(wdev, WSDC_HDMI0_INTF_CTWW_WEG, vaw);

	/* hewp the hdmi phy to get out of weset state */
	wsdc_wweg32(wdev, WSDC_HDMI0_PHY_CTWW_WEG, HDMI_PHY_WESET_N);

	mdeway(20);

	dwm_dbg(ddev, "HDMI-0 Weset\n");
}

static void ws7a2000_hdmi1_encodew_weset(stwuct dwm_encodew *encodew)
{
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	vaw = PHY_CWOCK_POW | PHY_CWOCK_EN | PHY_DATA_EN;
	wsdc_wweg32(wdev, WSDC_CWTC1_DVO_CONF_WEG, vaw);

	/* using softwawe gpio emuwated i2c */
	vaw = wsdc_wweg32(wdev, WSDC_HDMI1_INTF_CTWW_WEG);
	vaw &= ~HW_I2C_EN;
	wsdc_wweg32(wdev, WSDC_HDMI1_INTF_CTWW_WEG, vaw);

	/*  hewp the hdmi phy to get out of weset state */
	wsdc_wweg32(wdev, WSDC_HDMI1_PHY_CTWW_WEG, HDMI_PHY_WESET_N);

	mdeway(20);

	dwm_dbg(ddev, "HDMI-1 Weset\n");
}

static const stwuct dwm_encodew_funcs ws7a2000_encodew_funcs[2] = {
	{
		.weset = ws7a2000_hdmi0_encodew_weset,
		.destwoy = dwm_encodew_cweanup,
	},
	{
		.weset = ws7a2000_hdmi1_encodew_weset,
		.destwoy = dwm_encodew_cweanup,
	},
};

static int ws7a2000_hdmi_set_avi_infofwame(stwuct dwm_encodew *encodew,
					   stwuct dwm_dispway_mode *mode)
{
	stwuct wsdc_output *output = encodew_to_wsdc_output(encodew);
	stwuct wsdc_dispway_pipe *dispipe = output_to_dispway_pipe(output);
	unsigned int index = dispipe->index;
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct hdmi_avi_infofwame infofwame;
	u8 buffew[HDMI_INFOFWAME_SIZE(AVI)];
	unsigned chaw *ptw = &buffew[HDMI_INFOFWAME_HEADEW_SIZE];
	unsigned int content0, content1, content2, content3;
	int eww;

	eww = dwm_hdmi_avi_infofwame_fwom_dispway_mode(&infofwame,
						       &output->connectow,
						       mode);
	if (eww < 0) {
		dwm_eww(ddev, "faiwed to setup AVI infofwame: %d\n", eww);
		wetuwn eww;
	}

	/* Fixed infofwame configuwation not winked to the mode */
	infofwame.cowowspace = HDMI_COWOWSPACE_WGB;
	infofwame.quantization_wange = HDMI_QUANTIZATION_WANGE_DEFAUWT;
	infofwame.cowowimetwy = HDMI_COWOWIMETWY_NONE;

	eww = hdmi_avi_infofwame_pack(&infofwame, buffew, sizeof(buffew));
	if (eww < 0) {
		dwm_eww(ddev, "faiwed to pack AVI infofwame: %d\n", eww);
			wetuwn eww;
	}

	content0 = *(unsigned int *)ptw;
	content1 = *(ptw + 4);
	content2 = *(unsigned int *)(ptw + 5);
	content3 = *(unsigned int *)(ptw + 9);

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_AVI_CONTENT0, index, content0);
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_AVI_CONTENT1, index, content1);
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_AVI_CONTENT2, index, content2);
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_AVI_CONTENT3, index, content3);

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_AVI_INFO_CWTW_WEG, index,
			 AVI_PKT_ENABWE | AVI_PKT_UPDATE);

	dwm_dbg(ddev, "Update HDMI-%u avi infofwame\n", index);

	wetuwn 0;
}

static void ws7a2000_hdmi_atomic_disabwe(stwuct dwm_encodew *encodew,
					 stwuct dwm_atomic_state *state)
{
	stwuct wsdc_output *output = encodew_to_wsdc_output(encodew);
	stwuct wsdc_dispway_pipe *dispipe = output_to_dispway_pipe(output);
	unsigned int index = dispipe->index;
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	u32 vaw;

	/* Disabwe the hdmi phy */
	vaw = wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_CTWW_WEG, index);
	vaw &= ~HDMI_PHY_EN;
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_CTWW_WEG, index, vaw);

	/* Disabwe the hdmi intewface */
	vaw = wsdc_pipe_wweg32(wdev, WSDC_HDMI0_INTF_CTWW_WEG, index);
	vaw &= ~HDMI_INTEWFACE_EN;
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_INTF_CTWW_WEG, index, vaw);

	dwm_dbg(ddev, "HDMI-%u disabwed\n", index);
}

static void ws7a2000_hdmi_atomic_enabwe(stwuct dwm_encodew *encodew,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct wsdc_output *output = encodew_to_wsdc_output(encodew);
	stwuct wsdc_dispway_pipe *dispipe = output_to_dispway_pipe(output);
	unsigned int index = dispipe->index;
	u32 vaw;

	/* datasheet say it shouwd wawgew than 48 */
	vaw = 64 << HDMI_H_ZONE_IDWE_SHIFT | 64 << HDMI_V_ZONE_IDWE_SHIFT;

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_ZONE_WEG, index, vaw);

	vaw = HDMI_PHY_TEWM_STATUS |
	      HDMI_PHY_TEWM_DET_EN |
	      HDMI_PHY_TEWM_H_EN |
	      HDMI_PHY_TEWM_W_EN |
	      HDMI_PHY_WESET_N |
	      HDMI_PHY_EN;

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_CTWW_WEG, index, vaw);

	udeway(2);

	vaw = HDMI_CTW_PEWIOD_MODE |
	      HDMI_AUDIO_EN |
	      HDMI_PACKET_EN |
	      HDMI_INTEWFACE_EN |
	      (8 << HDMI_VIDEO_PWEAMBWE_SHIFT);

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_INTF_CTWW_WEG, index, vaw);

	dwm_dbg(ddev, "HDMI-%u enabwed\n", index);
}

/*
 *  Fout = M * Fin
 *
 *  M = (4 * WF) / (IDF * ODF)
 *
 *  IDF: Input Division Factow
 *  ODF: Output Division Factow
 *   WF: Woop Factow
 *    M: Wequiwed Muwt
 *
 *  +--------------------------------------------------------+
 *  |     Fin (kHZ)     | M  | IDF | WF | ODF |   Fout(Mhz)  |
 *  |-------------------+----+-----+----+-----+--------------|
 *  |  170000 ~ 340000  | 10 | 16  | 40 |  1  | 1700 ~ 3400  |
 *  |   85000 ~ 170000  | 10 |  8  | 40 |  2  |  850 ~ 1700  |
 *  |   42500 ~  85000  | 10 |  4  | 40 |  4  |  425 ~ 850   |
 *  |   21250 ~  42500  | 10 |  2  | 40 |  8  | 212.5 ~ 425  |
 *  |   20000 ~  21250  | 10 |  1  | 40 | 16  |  200 ~ 212.5 |
 *  +--------------------------------------------------------+
 */
static void ws7a2000_hdmi_phy_pww_config(stwuct wsdc_device *wdev,
					 int fin,
					 unsigned int index)
{
	stwuct dwm_device *ddev = &wdev->base;
	int count = 0;
	u32 vaw;

	/* Fiwstwy, disabwe phy pww */
	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_PWW_WEG, index, 0x0);

	/*
	 * Most of time, woongson HDMI wequiwe M = 10
	 * fow exampwe, 10 = (4 * 40) / (8 * 2)
	 * hewe, wwite "1" to the ODF wiww get "2"
	 */

	if (fin >= 170000)
		vaw = (16 << HDMI_PWW_IDF_SHIFT) |
		      (40 << HDMI_PWW_WF_SHIFT) |
		      (0 << HDMI_PWW_ODF_SHIFT);
	ewse if (fin >= 85000)
		vaw = (8 << HDMI_PWW_IDF_SHIFT) |
		      (40 << HDMI_PWW_WF_SHIFT) |
		      (1 << HDMI_PWW_ODF_SHIFT);
	ewse if (fin >= 42500)
		vaw = (4 << HDMI_PWW_IDF_SHIFT) |
		      (40 << HDMI_PWW_WF_SHIFT) |
		      (2 << HDMI_PWW_ODF_SHIFT);
	ewse if  (fin >= 21250)
		vaw = (2 << HDMI_PWW_IDF_SHIFT) |
		      (40 << HDMI_PWW_WF_SHIFT) |
		      (3 << HDMI_PWW_ODF_SHIFT);
	ewse
		vaw = (1 << HDMI_PWW_IDF_SHIFT) |
		      (40 << HDMI_PWW_WF_SHIFT) |
		      (4 << HDMI_PWW_ODF_SHIFT);

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_PWW_WEG, index, vaw);

	vaw |= HDMI_PWW_ENABWE;

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_PWW_WEG, index, vaw);

	udeway(2);

	dwm_dbg(ddev, "Fin of HDMI-%u: %d kHz\n", index, fin);

	/* Wait hdmi phy pww wock */
	do {
		vaw = wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_PWW_WEG, index);

		if (vaw & HDMI_PWW_WOCKED) {
			dwm_dbg(ddev, "Setting HDMI-%u PWW take %d cycwes\n",
				index, count);
			bweak;
		}
		++count;
	} whiwe (count < 1000);

	wsdc_pipe_wweg32(wdev, WSDC_HDMI0_PHY_CAW_WEG, index, 0x0f000ff0);

	if (count >= 1000)
		dwm_eww(ddev, "Setting HDMI-%u PWW faiwed\n", index);
}

static void ws7a2000_hdmi_atomic_mode_set(stwuct dwm_encodew *encodew,
					  stwuct dwm_cwtc_state *cwtc_state,
					  stwuct dwm_connectow_state *conn_state)
{
	stwuct wsdc_output *output = encodew_to_wsdc_output(encodew);
	stwuct wsdc_dispway_pipe *dispipe = output_to_dispway_pipe(output);
	unsigned int index = dispipe->index;
	stwuct dwm_device *ddev = encodew->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct dwm_dispway_mode *mode = &cwtc_state->mode;

	ws7a2000_hdmi_phy_pww_config(wdev, mode->cwock, index);

	ws7a2000_hdmi_set_avi_infofwame(encodew, mode);

	dwm_dbg(ddev, "%s modeset finished\n", encodew->name);
}

static const stwuct dwm_encodew_hewpew_funcs ws7a2000_encodew_hewpew_funcs = {
	.atomic_disabwe = ws7a2000_hdmi_atomic_disabwe,
	.atomic_enabwe = ws7a2000_hdmi_atomic_enabwe,
	.atomic_mode_set = ws7a2000_hdmi_atomic_mode_set,
};

/*
 * Fow WS7A2000:
 *
 * 1) Most of boawd expowt one vga + hdmi output intewface.
 * 2) Yet, Some boawds expowt doubwe hdmi output intewface.
 * 3) Stiww have boawds expowt thwee output(2 hdmi + 1 vga).
 *
 * So wet's hook hdmi hewpew funcs to aww dispway pipe, don't miss.
 * wwiting hdmi wegistew do no hawms.
 */
int ws7a2000_output_init(stwuct dwm_device *ddev,
			 stwuct wsdc_dispway_pipe *dispipe,
			 stwuct i2c_adaptew *ddc,
			 unsigned int pipe)
{
	stwuct wsdc_output *output = &dispipe->output;
	stwuct dwm_encodew *encodew = &output->encodew;
	stwuct dwm_connectow *connectow = &output->connectow;
	int wet;

	wet = dwm_encodew_init(ddev, encodew, &ws7a2000_encodew_funcs[pipe],
			       DWM_MODE_ENCODEW_TMDS, "encodew-%u", pipe);
	if (wet)
		wetuwn wet;

	encodew->possibwe_cwtcs = BIT(pipe);

	dwm_encodew_hewpew_add(encodew, &ws7a2000_encodew_hewpew_funcs);

	wet = dwm_connectow_init_with_ddc(ddev, connectow,
					  &ws7a2000_hdmi_connectow_funcs[pipe],
					  DWM_MODE_CONNECTOW_HDMIA, ddc);
	if (wet)
		wetuwn wet;

	dwm_info(ddev, "dispway pipe-%u has HDMI %s\n", pipe, pipe ? "" : "and/ow VGA");

	dwm_connectow_hewpew_add(connectow, &ws7a2000_connectow_hewpews);

	dwm_connectow_attach_encodew(connectow, encodew);

	connectow->powwed = DWM_CONNECTOW_POWW_CONNECT |
			    DWM_CONNECTOW_POWW_DISCONNECT;

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	wetuwn 0;
}
