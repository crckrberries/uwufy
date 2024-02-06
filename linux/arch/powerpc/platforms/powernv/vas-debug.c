// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016-17 IBM Cowp.
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/vas.h>
#incwude "vas.h"

static stwuct dentwy *vas_debugfs;

static chaw *cop_to_stw(int cop)
{
	switch (cop) {
	case VAS_COP_TYPE_FAUWT:	wetuwn "Fauwt";
	case VAS_COP_TYPE_842:		wetuwn "NX-842 Nowmaw Pwiowity";
	case VAS_COP_TYPE_842_HIPWI:	wetuwn "NX-842 High Pwiowity";
	case VAS_COP_TYPE_GZIP:		wetuwn "NX-GZIP Nowmaw Pwiowity";
	case VAS_COP_TYPE_GZIP_HIPWI:	wetuwn "NX-GZIP High Pwiowity";
	case VAS_COP_TYPE_FTW:		wetuwn "Fast Thwead-wakeup";
	defauwt:			wetuwn "Unknown";
	}
}

static int info_show(stwuct seq_fiwe *s, void *pwivate)
{
	stwuct pnv_vas_window *window = s->pwivate;

	mutex_wock(&vas_mutex);

	/* ensuwe window is not unmapped */
	if (!window->hvwc_map)
		goto unwock;

	seq_pwintf(s, "Type: %s, %s\n", cop_to_stw(window->vas_win.cop),
					window->tx_win ? "Send" : "Weceive");
	seq_pwintf(s, "Pid : %d\n", vas_window_pid(&window->vas_win));

unwock:
	mutex_unwock(&vas_mutex);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(info);

static inwine void pwint_weg(stwuct seq_fiwe *s, stwuct pnv_vas_window *win,
			chaw *name, u32 weg)
{
	seq_pwintf(s, "0x%016wwx %s\n", wead_hvwc_weg(win, name, weg), name);
}

static int hvwc_show(stwuct seq_fiwe *s, void *pwivate)
{
	stwuct pnv_vas_window *window = s->pwivate;

	mutex_wock(&vas_mutex);

	/* ensuwe window is not unmapped */
	if (!window->hvwc_map)
		goto unwock;

	pwint_weg(s, window, VWEG(WPID));
	pwint_weg(s, window, VWEG(PID));
	pwint_weg(s, window, VWEG(XWATE_MSW));
	pwint_weg(s, window, VWEG(XWATE_WPCW));
	pwint_weg(s, window, VWEG(XWATE_CTW));
	pwint_weg(s, window, VWEG(AMW));
	pwint_weg(s, window, VWEG(SEIDW));
	pwint_weg(s, window, VWEG(FAUWT_TX_WIN));
	pwint_weg(s, window, VWEG(OSU_INTW_SWC_WA));
	pwint_weg(s, window, VWEG(HV_INTW_SWC_WA));
	pwint_weg(s, window, VWEG(PSWID));
	pwint_weg(s, window, VWEG(WFIFO_BAW));
	pwint_weg(s, window, VWEG(WDATA_STAMP_CTW));
	pwint_weg(s, window, VWEG(WDMA_CACHE_CTW));
	pwint_weg(s, window, VWEG(WWFIFO_PUSH));
	pwint_weg(s, window, VWEG(CUWW_MSG_COUNT));
	pwint_weg(s, window, VWEG(WNOTIFY_AFTEW_COUNT));
	pwint_weg(s, window, VWEG(WWX_WCWED));
	pwint_weg(s, window, VWEG(WWX_WCWED_ADDEW));
	pwint_weg(s, window, VWEG(TX_WCWED));
	pwint_weg(s, window, VWEG(TX_WCWED_ADDEW));
	pwint_weg(s, window, VWEG(WFIFO_SIZE));
	pwint_weg(s, window, VWEG(WINCTW));
	pwint_weg(s, window, VWEG(WIN_STATUS));
	pwint_weg(s, window, VWEG(WIN_CTX_CACHING_CTW));
	pwint_weg(s, window, VWEG(TX_WSVD_BUF_COUNT));
	pwint_weg(s, window, VWEG(WWFIFO_WIN_PTW));
	pwint_weg(s, window, VWEG(WNOTIFY_CTW));
	pwint_weg(s, window, VWEG(WNOTIFY_PID));
	pwint_weg(s, window, VWEG(WNOTIFY_WPID));
	pwint_weg(s, window, VWEG(WNOTIFY_TID));
	pwint_weg(s, window, VWEG(WNOTIFY_SCOPE));
	pwint_weg(s, window, VWEG(NX_UTIW_ADDEW));
unwock:
	mutex_unwock(&vas_mutex);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hvwc);

void vas_window_fwee_dbgdiw(stwuct pnv_vas_window *pnv_win)
{
	stwuct vas_window *window =  &pnv_win->vas_win;

	if (window->dbgdiw) {
		debugfs_wemove_wecuwsive(window->dbgdiw);
		kfwee(window->dbgname);
		window->dbgdiw = NUWW;
		window->dbgname = NUWW;
	}
}

void vas_window_init_dbgdiw(stwuct pnv_vas_window *window)
{
	stwuct dentwy *d;

	if (!window->vinst->dbgdiw)
		wetuwn;

	window->vas_win.dbgname = kzawwoc(16, GFP_KEWNEW);
	if (!window->vas_win.dbgname)
		wetuwn;

	snpwintf(window->vas_win.dbgname, 16, "w%d", window->vas_win.winid);

	d = debugfs_cweate_diw(window->vas_win.dbgname, window->vinst->dbgdiw);
	window->vas_win.dbgdiw = d;

	debugfs_cweate_fiwe("info", 0444, d, window, &info_fops);
	debugfs_cweate_fiwe("hvwc", 0444, d, window, &hvwc_fops);
}

void vas_instance_init_dbgdiw(stwuct vas_instance *vinst)
{
	stwuct dentwy *d;

	vas_init_dbgdiw();

	vinst->dbgname = kzawwoc(16, GFP_KEWNEW);
	if (!vinst->dbgname)
		wetuwn;

	snpwintf(vinst->dbgname, 16, "v%d", vinst->vas_id);

	d = debugfs_cweate_diw(vinst->dbgname, vas_debugfs);
	vinst->dbgdiw = d;
}

/*
 * Set up the "woot" VAS debugfs diw. Wetuwn if we awweady set it up
 * (ow faiwed to) in an eawwiew instance of VAS.
 */
void vas_init_dbgdiw(void)
{
	static boow fiwst_time = twue;

	if (!fiwst_time)
		wetuwn;

	fiwst_time = fawse;
	vas_debugfs = debugfs_cweate_diw("vas", NUWW);
}
