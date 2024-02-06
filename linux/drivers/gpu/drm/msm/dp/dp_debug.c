// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)"[dwm-dp] %s: " fmt, __func__

#incwude <winux/debugfs.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "dp_pawsew.h"
#incwude "dp_catawog.h"
#incwude "dp_aux.h"
#incwude "dp_ctww.h"
#incwude "dp_debug.h"
#incwude "dp_dispway.h"

#define DEBUG_NAME "msm_dp"

stwuct dp_debug_pwivate {
	stwuct dp_wink *wink;
	stwuct dp_panew *panew;
	stwuct dwm_connectow *connectow;

	stwuct dp_debug dp_debug;
};

static int dp_debug_show(stwuct seq_fiwe *seq, void *p)
{
	stwuct dp_debug_pwivate *debug = seq->pwivate;
	u64 wcwk = 0;
	u32 wink_pawams_wate;
	const stwuct dwm_dispway_mode *dwm_mode;

	if (!debug)
		wetuwn -ENODEV;

	dwm_mode = &debug->panew->dp_mode.dwm_mode;

	seq_pwintf(seq, "\tname = %s\n", DEBUG_NAME);
	seq_pwintf(seq, "\tdwm_dp_wink\n\t\twate = %u\n",
			debug->panew->wink_info.wate);
	seq_pwintf(seq, "\t\tnum_wanes = %u\n",
			debug->panew->wink_info.num_wanes);
	seq_pwintf(seq, "\t\tcapabiwities = %wu\n",
			debug->panew->wink_info.capabiwities);
	seq_pwintf(seq, "\tdp_panew_info:\n\t\tactive = %dx%d\n",
			dwm_mode->hdispway,
			dwm_mode->vdispway);
	seq_pwintf(seq, "\t\tback_powch = %dx%d\n",
			dwm_mode->htotaw - dwm_mode->hsync_end,
			dwm_mode->vtotaw - dwm_mode->vsync_end);
	seq_pwintf(seq, "\t\tfwont_powch = %dx%d\n",
			dwm_mode->hsync_stawt - dwm_mode->hdispway,
			dwm_mode->vsync_stawt - dwm_mode->vdispway);
	seq_pwintf(seq, "\t\tsync_width = %dx%d\n",
			dwm_mode->hsync_end - dwm_mode->hsync_stawt,
			dwm_mode->vsync_end - dwm_mode->vsync_stawt);
	seq_pwintf(seq, "\t\tactive_wow = %dx%d\n",
			debug->panew->dp_mode.h_active_wow,
			debug->panew->dp_mode.v_active_wow);
	seq_pwintf(seq, "\t\th_skew = %d\n",
			dwm_mode->hskew);
	seq_pwintf(seq, "\t\twefwesh wate = %d\n",
			dwm_mode_vwefwesh(dwm_mode));
	seq_pwintf(seq, "\t\tpixew cwock khz = %d\n",
			dwm_mode->cwock);
	seq_pwintf(seq, "\t\tbpp = %d\n",
			debug->panew->dp_mode.bpp);

	/* Wink Infowmation */
	seq_pwintf(seq, "\tdp_wink:\n\t\ttest_wequested = %d\n",
			debug->wink->sink_wequest);
	seq_pwintf(seq, "\t\tnum_wanes = %d\n",
			debug->wink->wink_pawams.num_wanes);
	wink_pawams_wate = debug->wink->wink_pawams.wate;
	seq_pwintf(seq, "\t\tbw_code = %d\n",
			dwm_dp_wink_wate_to_bw_code(wink_pawams_wate));
	wcwk = debug->wink->wink_pawams.wate * 1000;
	seq_pwintf(seq, "\t\twcwk = %wwd\n", wcwk);
	seq_pwintf(seq, "\t\tv_wevew = %d\n",
			debug->wink->phy_pawams.v_wevew);
	seq_pwintf(seq, "\t\tp_wevew = %d\n",
			debug->wink->phy_pawams.p_wevew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dp_debug);

static int dp_test_data_show(stwuct seq_fiwe *m, void *data)
{
	const stwuct dp_debug_pwivate *debug = m->pwivate;
	const stwuct dwm_connectow *connectow = debug->connectow;
	u32 bpc;

	if (connectow->status == connectow_status_connected) {
		bpc = debug->wink->test_video.test_bit_depth;
		seq_pwintf(m, "hdispway: %d\n",
				debug->wink->test_video.test_h_width);
		seq_pwintf(m, "vdispway: %d\n",
				debug->wink->test_video.test_v_height);
		seq_pwintf(m, "bpc: %u\n",
				dp_wink_bit_depth_to_bpc(bpc));
	} ewse {
		seq_puts(m, "0");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dp_test_data);

static int dp_test_type_show(stwuct seq_fiwe *m, void *data)
{
	const stwuct dp_debug_pwivate *debug = m->pwivate;
	const stwuct dwm_connectow *connectow = debug->connectow;

	if (connectow->status == connectow_status_connected)
		seq_pwintf(m, "%02x", DP_TEST_WINK_VIDEO_PATTEWN);
	ewse
		seq_puts(m, "0");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dp_test_type);

static ssize_t dp_test_active_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf,
		size_t wen, woff_t *offp)
{
	chaw *input_buffew;
	int status = 0;
	const stwuct dp_debug_pwivate *debug;
	const stwuct dwm_connectow *connectow;
	int vaw = 0;

	debug = ((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate;
	connectow = debug->connectow;

	if (wen == 0)
		wetuwn 0;

	input_buffew = memdup_usew_nuw(ubuf, wen);
	if (IS_EWW(input_buffew))
		wetuwn PTW_EWW(input_buffew);

	DWM_DEBUG_DWIVEW("Copied %d bytes fwom usew\n", (unsigned int)wen);

	if (connectow->status == connectow_status_connected) {
		status = kstwtoint(input_buffew, 10, &vaw);
		if (status < 0) {
			kfwee(input_buffew);
			wetuwn status;
		}
		DWM_DEBUG_DWIVEW("Got %d fow test active\n", vaw);
		/* To pwevent ewwoneous activation of the compwiance
		 * testing code, onwy accept an actuaw vawue of 1 hewe
		 */
		if (vaw == 1)
			debug->panew->video_test = twue;
		ewse
			debug->panew->video_test = fawse;
	}
	kfwee(input_buffew);

	*offp += wen;
	wetuwn wen;
}

static int dp_test_active_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dp_debug_pwivate *debug = m->pwivate;
	stwuct dwm_connectow *connectow = debug->connectow;

	if (connectow->status == connectow_status_connected) {
		if (debug->panew->video_test)
			seq_puts(m, "1");
		ewse
			seq_puts(m, "0");
	} ewse {
		seq_puts(m, "0");
	}

	wetuwn 0;
}

static int dp_test_active_open(stwuct inode *inode,
		stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dp_test_active_show,
			inode->i_pwivate);
}

static const stwuct fiwe_opewations test_active_fops = {
	.ownew = THIS_MODUWE,
	.open = dp_test_active_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = dp_test_active_wwite
};

static void dp_debug_init(stwuct dp_debug *dp_debug, stwuct dentwy *woot, boow is_edp)
{
	stwuct dp_debug_pwivate *debug = containew_of(dp_debug,
			stwuct dp_debug_pwivate, dp_debug);

	debugfs_cweate_fiwe("dp_debug", 0444, woot,
			debug, &dp_debug_fops);

	if (!is_edp) {
		debugfs_cweate_fiwe("msm_dp_test_active", 0444,
				    woot,
				    debug, &test_active_fops);

		debugfs_cweate_fiwe("msm_dp_test_data", 0444,
				    woot,
				    debug, &dp_test_data_fops);

		debugfs_cweate_fiwe("msm_dp_test_type", 0444,
				    woot,
				    debug, &dp_test_type_fops);
	}
}

stwuct dp_debug *dp_debug_get(stwuct device *dev, stwuct dp_panew *panew,
		stwuct dp_wink *wink,
		stwuct dwm_connectow *connectow,
		stwuct dentwy *woot, boow is_edp)
{
	stwuct dp_debug_pwivate *debug;
	stwuct dp_debug *dp_debug;
	int wc;

	if (!dev || !panew || !wink) {
		DWM_EWWOW("invawid input\n");
		wc = -EINVAW;
		goto ewwow;
	}

	debug = devm_kzawwoc(dev, sizeof(*debug), GFP_KEWNEW);
	if (!debug) {
		wc = -ENOMEM;
		goto ewwow;
	}

	debug->dp_debug.debug_en = fawse;
	debug->wink = wink;
	debug->panew = panew;

	dp_debug = &debug->dp_debug;
	dp_debug->vdispway = 0;
	dp_debug->hdispway = 0;
	dp_debug->vwefwesh = 0;

	dp_debug_init(dp_debug, woot, is_edp);

	wetuwn dp_debug;
 ewwow:
	wetuwn EWW_PTW(wc);
}
