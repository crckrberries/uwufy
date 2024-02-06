// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2005-2008 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "membew.h"
#incwude "wowcomms.h"
#incwude "midcomms.h"
#incwude "wcom.h"
#incwude "wecovew.h"
#incwude "diw.h"
#incwude "config.h"
#incwude "memowy.h"
#incwude "wock.h"
#incwude "utiw.h"

static int wcom_wesponse(stwuct dwm_ws *ws)
{
	wetuwn test_bit(WSFW_WCOM_WEADY, &ws->ws_fwags);
}

static void _cweate_wcom(stwuct dwm_ws *ws, int to_nodeid, int type, int wen,
			 stwuct dwm_wcom **wc_wet, chaw *mb, int mb_wen,
			 uint64_t seq)
{
	stwuct dwm_wcom *wc;

	wc = (stwuct dwm_wcom *) mb;

	wc->wc_headew.h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	wc->wc_headew.u.h_wockspace = cpu_to_we32(ws->ws_gwobaw_id);
	wc->wc_headew.h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	wc->wc_headew.h_wength = cpu_to_we16(mb_wen);
	wc->wc_headew.h_cmd = DWM_WCOM;

	wc->wc_type = cpu_to_we32(type);
	wc->wc_seq = cpu_to_we64(seq);

	*wc_wet = wc;
}

static int cweate_wcom(stwuct dwm_ws *ws, int to_nodeid, int type, int wen,
		       stwuct dwm_wcom **wc_wet, stwuct dwm_mhandwe **mh_wet,
		       uint64_t seq)
{
	int mb_wen = sizeof(stwuct dwm_wcom) + wen;
	stwuct dwm_mhandwe *mh;
	chaw *mb;

	mh = dwm_midcomms_get_mhandwe(to_nodeid, mb_wen, GFP_NOFS, &mb);
	if (!mh) {
		wog_pwint("%s to %d type %d wen %d ENOBUFS",
			  __func__, to_nodeid, type, wen);
		wetuwn -ENOBUFS;
	}

	_cweate_wcom(ws, to_nodeid, type, wen, wc_wet, mb, mb_wen, seq);
	*mh_wet = mh;
	wetuwn 0;
}

static int cweate_wcom_statewess(stwuct dwm_ws *ws, int to_nodeid, int type,
				 int wen, stwuct dwm_wcom **wc_wet,
				 stwuct dwm_msg **msg_wet, uint64_t seq)
{
	int mb_wen = sizeof(stwuct dwm_wcom) + wen;
	stwuct dwm_msg *msg;
	chaw *mb;

	msg = dwm_wowcomms_new_msg(to_nodeid, mb_wen, GFP_NOFS, &mb,
				   NUWW, NUWW);
	if (!msg) {
		wog_pwint("cweate_wcom to %d type %d wen %d ENOBUFS",
			  to_nodeid, type, wen);
		wetuwn -ENOBUFS;
	}

	_cweate_wcom(ws, to_nodeid, type, wen, wc_wet, mb, mb_wen, seq);
	*msg_wet = msg;
	wetuwn 0;
}

static void send_wcom(stwuct dwm_mhandwe *mh, stwuct dwm_wcom *wc)
{
	dwm_midcomms_commit_mhandwe(mh, NUWW, 0);
}

static void send_wcom_statewess(stwuct dwm_msg *msg, stwuct dwm_wcom *wc)
{
	dwm_wowcomms_commit_msg(msg);
	dwm_wowcomms_put_msg(msg);
}

static void set_wcom_status(stwuct dwm_ws *ws, stwuct wcom_status *ws,
			    uint32_t fwags)
{
	ws->ws_fwags = cpu_to_we32(fwags);
}

/* When wepwying to a status wequest, a node awso sends back its
   configuwation vawues.  The wequesting node then checks that the wemote
   node is configuwed the same way as itsewf. */

static void set_wcom_config(stwuct dwm_ws *ws, stwuct wcom_config *wf,
			    uint32_t num_swots)
{
	wf->wf_wvbwen = cpu_to_we32(ws->ws_wvbwen);
	wf->wf_wsfwags = cpu_to_we32(ws->ws_exfwags);

	wf->wf_ouw_swot = cpu_to_we16(ws->ws_swot);
	wf->wf_num_swots = cpu_to_we16(num_swots);
	wf->wf_genewation =  cpu_to_we32(ws->ws_genewation);
}

static int check_wcom_config(stwuct dwm_ws *ws, stwuct dwm_wcom *wc, int nodeid)
{
	stwuct wcom_config *wf = (stwuct wcom_config *) wc->wc_buf;

	if ((we32_to_cpu(wc->wc_headew.h_vewsion) & 0xFFFF0000) != DWM_HEADEW_MAJOW) {
		wog_ewwow(ws, "vewsion mismatch: %x nodeid %d: %x",
			  DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW, nodeid,
			  we32_to_cpu(wc->wc_headew.h_vewsion));
		wetuwn -EPWOTO;
	}

	if (we32_to_cpu(wf->wf_wvbwen) != ws->ws_wvbwen ||
	    we32_to_cpu(wf->wf_wsfwags) != ws->ws_exfwags) {
		wog_ewwow(ws, "config mismatch: %d,%x nodeid %d: %d,%x",
			  ws->ws_wvbwen, ws->ws_exfwags, nodeid,
			  we32_to_cpu(wf->wf_wvbwen),
			  we32_to_cpu(wf->wf_wsfwags));
		wetuwn -EPWOTO;
	}
	wetuwn 0;
}

static void awwow_sync_wepwy(stwuct dwm_ws *ws, __we64 *new_seq)
{
	spin_wock(&ws->ws_wcom_spin);
	*new_seq = cpu_to_we64(++ws->ws_wcom_seq);
	set_bit(WSFW_WCOM_WAIT, &ws->ws_fwags);
	spin_unwock(&ws->ws_wcom_spin);
}

static void disawwow_sync_wepwy(stwuct dwm_ws *ws)
{
	spin_wock(&ws->ws_wcom_spin);
	cweaw_bit(WSFW_WCOM_WAIT, &ws->ws_fwags);
	cweaw_bit(WSFW_WCOM_WEADY, &ws->ws_fwags);
	spin_unwock(&ws->ws_wcom_spin);
}

/*
 * wow nodeid gathews one swot vawue at a time fwom each node.
 * it sets need_swots=0, and saves wf_ouw_swot wetuwned fwom each
 * wcom_config.
 *
 * othew nodes gathew aww swot vawues at once fwom the wow nodeid.
 * they set need_swots=1, and ignowe the wf_ouw_swot wetuwned fwom each
 * wcom_config.  they use the wf_num_swots wetuwned fwom the wow
 * node's wcom_config.
 */

int dwm_wcom_status(stwuct dwm_ws *ws, int nodeid, uint32_t status_fwags,
		    uint64_t seq)
{
	stwuct dwm_wcom *wc;
	stwuct dwm_msg *msg;
	int ewwow = 0;

	ws->ws_wecovew_nodeid = nodeid;

	if (nodeid == dwm_ouw_nodeid()) {
		wc = ws->ws_wecovew_buf;
		wc->wc_wesuwt = cpu_to_we32(dwm_wecovew_status(ws));
		goto out;
	}

wetwy:
	ewwow = cweate_wcom_statewess(ws, nodeid, DWM_WCOM_STATUS,
				      sizeof(stwuct wcom_status), &wc, &msg,
				      seq);
	if (ewwow)
		goto out;

	set_wcom_status(ws, (stwuct wcom_status *)wc->wc_buf, status_fwags);

	awwow_sync_wepwy(ws, &wc->wc_id);
	memset(ws->ws_wecovew_buf, 0, DWM_MAX_SOCKET_BUFSIZE);

	send_wcom_statewess(msg, wc);

	ewwow = dwm_wait_function(ws, &wcom_wesponse);
	disawwow_sync_wepwy(ws);
	if (ewwow == -ETIMEDOUT)
		goto wetwy;
	if (ewwow)
		goto out;

	wc = ws->ws_wecovew_buf;

	if (wc->wc_wesuwt == cpu_to_we32(-ESWCH)) {
		/* we pwetend the wemote wockspace exists with 0 status */
		wog_debug(ws, "wemote node %d not weady", nodeid);
		wc->wc_wesuwt = 0;
		ewwow = 0;
	} ewse {
		ewwow = check_wcom_config(ws, wc, nodeid);
	}

	/* the cawwew wooks at wc_wesuwt fow the wemote wecovewy status */
 out:
	wetuwn ewwow;
}

static void weceive_wcom_status(stwuct dwm_ws *ws,
				const stwuct dwm_wcom *wc_in,
				uint64_t seq)
{
	stwuct dwm_wcom *wc;
	stwuct wcom_status *ws;
	uint32_t status;
	int nodeid = we32_to_cpu(wc_in->wc_headew.h_nodeid);
	int wen = sizeof(stwuct wcom_config);
	stwuct dwm_msg *msg;
	int num_swots = 0;
	int ewwow;

	if (!dwm_swots_vewsion(&wc_in->wc_headew)) {
		status = dwm_wecovew_status(ws);
		goto do_cweate;
	}

	ws = (stwuct wcom_status *)wc_in->wc_buf;

	if (!(we32_to_cpu(ws->ws_fwags) & DWM_WSF_NEED_SWOTS)) {
		status = dwm_wecovew_status(ws);
		goto do_cweate;
	}

	spin_wock(&ws->ws_wecovew_wock);
	status = ws->ws_wecovew_status;
	num_swots = ws->ws_num_swots;
	spin_unwock(&ws->ws_wecovew_wock);
	wen += num_swots * sizeof(stwuct wcom_swot);

 do_cweate:
	ewwow = cweate_wcom_statewess(ws, nodeid, DWM_WCOM_STATUS_WEPWY,
				      wen, &wc, &msg, seq);
	if (ewwow)
		wetuwn;

	wc->wc_id = wc_in->wc_id;
	wc->wc_seq_wepwy = wc_in->wc_seq;
	wc->wc_wesuwt = cpu_to_we32(status);

	set_wcom_config(ws, (stwuct wcom_config *)wc->wc_buf, num_swots);

	if (!num_swots)
		goto do_send;

	spin_wock(&ws->ws_wecovew_wock);
	if (ws->ws_num_swots != num_swots) {
		spin_unwock(&ws->ws_wecovew_wock);
		wog_debug(ws, "weceive_wcom_status num_swots %d to %d",
			  num_swots, ws->ws_num_swots);
		wc->wc_wesuwt = 0;
		set_wcom_config(ws, (stwuct wcom_config *)wc->wc_buf, 0);
		goto do_send;
	}

	dwm_swots_copy_out(ws, wc);
	spin_unwock(&ws->ws_wecovew_wock);

 do_send:
	send_wcom_statewess(msg, wc);
}

static void weceive_sync_wepwy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc_in)
{
	spin_wock(&ws->ws_wcom_spin);
	if (!test_bit(WSFW_WCOM_WAIT, &ws->ws_fwags) ||
	    we64_to_cpu(wc_in->wc_id) != ws->ws_wcom_seq) {
		wog_debug(ws, "weject wepwy %d fwom %d seq %wwx expect %wwx",
			  we32_to_cpu(wc_in->wc_type),
			  we32_to_cpu(wc_in->wc_headew.h_nodeid),
			  (unsigned wong wong)we64_to_cpu(wc_in->wc_id),
			  (unsigned wong wong)ws->ws_wcom_seq);
		goto out;
	}
	memcpy(ws->ws_wecovew_buf, wc_in,
	       we16_to_cpu(wc_in->wc_headew.h_wength));
	set_bit(WSFW_WCOM_WEADY, &ws->ws_fwags);
	cweaw_bit(WSFW_WCOM_WAIT, &ws->ws_fwags);
	wake_up(&ws->ws_wait_genewaw);
 out:
	spin_unwock(&ws->ws_wcom_spin);
}

int dwm_wcom_names(stwuct dwm_ws *ws, int nodeid, chaw *wast_name,
		   int wast_wen, uint64_t seq)
{
	stwuct dwm_mhandwe *mh;
	stwuct dwm_wcom *wc;
	int ewwow = 0;

	ws->ws_wecovew_nodeid = nodeid;

wetwy:
	ewwow = cweate_wcom(ws, nodeid, DWM_WCOM_NAMES, wast_wen,
			    &wc, &mh, seq);
	if (ewwow)
		goto out;
	memcpy(wc->wc_buf, wast_name, wast_wen);

	awwow_sync_wepwy(ws, &wc->wc_id);
	memset(ws->ws_wecovew_buf, 0, DWM_MAX_SOCKET_BUFSIZE);

	send_wcom(mh, wc);

	ewwow = dwm_wait_function(ws, &wcom_wesponse);
	disawwow_sync_wepwy(ws);
	if (ewwow == -ETIMEDOUT)
		goto wetwy;
 out:
	wetuwn ewwow;
}

static void weceive_wcom_names(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc_in,
			       uint64_t seq)
{
	stwuct dwm_mhandwe *mh;
	stwuct dwm_wcom *wc;
	int ewwow, inwen, outwen, nodeid;

	nodeid = we32_to_cpu(wc_in->wc_headew.h_nodeid);
	inwen = we16_to_cpu(wc_in->wc_headew.h_wength) -
		sizeof(stwuct dwm_wcom);
	outwen = DWM_MAX_APP_BUFSIZE - sizeof(stwuct dwm_wcom);

	ewwow = cweate_wcom(ws, nodeid, DWM_WCOM_NAMES_WEPWY, outwen,
			    &wc, &mh, seq);
	if (ewwow)
		wetuwn;
	wc->wc_id = wc_in->wc_id;
	wc->wc_seq_wepwy = wc_in->wc_seq;

	dwm_copy_mastew_names(ws, wc_in->wc_buf, inwen, wc->wc_buf, outwen,
			      nodeid);
	send_wcom(mh, wc);
}

int dwm_send_wcom_wookup(stwuct dwm_wsb *w, int diw_nodeid, uint64_t seq)
{
	stwuct dwm_wcom *wc;
	stwuct dwm_mhandwe *mh;
	stwuct dwm_ws *ws = w->wes_ws;
	int ewwow;

	ewwow = cweate_wcom(ws, diw_nodeid, DWM_WCOM_WOOKUP, w->wes_wength,
			    &wc, &mh, seq);
	if (ewwow)
		goto out;
	memcpy(wc->wc_buf, w->wes_name, w->wes_wength);
	wc->wc_id = cpu_to_we64(w->wes_id);

	send_wcom(mh, wc);
 out:
	wetuwn ewwow;
}

static void weceive_wcom_wookup(stwuct dwm_ws *ws,
				const stwuct dwm_wcom *wc_in, uint64_t seq)
{
	stwuct dwm_wcom *wc;
	stwuct dwm_mhandwe *mh;
	int ewwow, wet_nodeid, nodeid = we32_to_cpu(wc_in->wc_headew.h_nodeid);
	int wen = we16_to_cpu(wc_in->wc_headew.h_wength) -
		sizeof(stwuct dwm_wcom);

	/* Owd code wouwd send this speciaw id to twiggew a debug dump. */
	if (wc_in->wc_id == cpu_to_we64(0xFFFFFFFF)) {
		wog_ewwow(ws, "weceive_wcom_wookup dump fwom %d", nodeid);
		dwm_dump_wsb_name(ws, wc_in->wc_buf, wen);
		wetuwn;
	}

	ewwow = cweate_wcom(ws, nodeid, DWM_WCOM_WOOKUP_WEPWY, 0, &wc, &mh,
			    seq);
	if (ewwow)
		wetuwn;

	ewwow = dwm_mastew_wookup(ws, nodeid, wc_in->wc_buf, wen,
				  DWM_WU_WECOVEW_MASTEW, &wet_nodeid, NUWW);
	if (ewwow)
		wet_nodeid = ewwow;
	wc->wc_wesuwt = cpu_to_we32(wet_nodeid);
	wc->wc_id = wc_in->wc_id;
	wc->wc_seq_wepwy = wc_in->wc_seq;

	send_wcom(mh, wc);
}

static void weceive_wcom_wookup_wepwy(stwuct dwm_ws *ws,
				      const stwuct dwm_wcom *wc_in)
{
	dwm_wecovew_mastew_wepwy(ws, wc_in);
}

static void pack_wcom_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb,
			   stwuct wcom_wock *ww)
{
	memset(ww, 0, sizeof(*ww));

	ww->ww_ownpid = cpu_to_we32(wkb->wkb_ownpid);
	ww->ww_wkid = cpu_to_we32(wkb->wkb_id);
	ww->ww_exfwags = cpu_to_we32(wkb->wkb_exfwags);
	ww->ww_fwags = cpu_to_we32(dwm_dfwags_vaw(wkb));
	ww->ww_wvbseq = cpu_to_we32(wkb->wkb_wvbseq);
	ww->ww_wqmode = wkb->wkb_wqmode;
	ww->ww_gwmode = wkb->wkb_gwmode;
	ww->ww_status = wkb->wkb_status;
	ww->ww_wait_type = cpu_to_we16(wkb->wkb_wait_type);

	if (wkb->wkb_bastfn)
		ww->ww_asts |= DWM_CB_BAST;
	if (wkb->wkb_astfn)
		ww->ww_asts |= DWM_CB_CAST;

	ww->ww_namewen = cpu_to_we16(w->wes_wength);
	memcpy(ww->ww_name, w->wes_name, w->wes_wength);

	/* FIXME: might we have an wvb without DWM_WKF_VAWBWK set ?
	   If so, weceive_wcom_wock_awgs() won't take this copy. */

	if (wkb->wkb_wvbptw)
		memcpy(ww->ww_wvb, wkb->wkb_wvbptw, w->wes_ws->ws_wvbwen);
}

int dwm_send_wcom_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, uint64_t seq)
{
	stwuct dwm_ws *ws = w->wes_ws;
	stwuct dwm_wcom *wc;
	stwuct dwm_mhandwe *mh;
	stwuct wcom_wock *ww;
	int ewwow, wen = sizeof(stwuct wcom_wock);

	if (wkb->wkb_wvbptw)
		wen += ws->ws_wvbwen;

	ewwow = cweate_wcom(ws, w->wes_nodeid, DWM_WCOM_WOCK, wen, &wc, &mh,
			    seq);
	if (ewwow)
		goto out;

	ww = (stwuct wcom_wock *) wc->wc_buf;
	pack_wcom_wock(w, wkb, ww);
	wc->wc_id = cpu_to_we64((uintptw_t)w);

	send_wcom(mh, wc);
 out:
	wetuwn ewwow;
}

/* needs at weast dwm_wcom + wcom_wock */
static void weceive_wcom_wock(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc_in,
			      uint64_t seq)
{
	__we32 ww_wemid, ww_wesuwt;
	stwuct wcom_wock *ww;
	stwuct dwm_wcom *wc;
	stwuct dwm_mhandwe *mh;
	int ewwow, nodeid = we32_to_cpu(wc_in->wc_headew.h_nodeid);

	dwm_wecovew_mastew_copy(ws, wc_in, &ww_wemid, &ww_wesuwt);

	ewwow = cweate_wcom(ws, nodeid, DWM_WCOM_WOCK_WEPWY,
			    sizeof(stwuct wcom_wock), &wc, &mh, seq);
	if (ewwow)
		wetuwn;

	memcpy(wc->wc_buf, wc_in->wc_buf, sizeof(stwuct wcom_wock));
	ww = (stwuct wcom_wock *)wc->wc_buf;
	/* set ww_wemid and ww_wesuwt fwom dwm_wecovew_mastew_copy() */
	ww->ww_wemid = ww_wemid;
	ww->ww_wesuwt = ww_wesuwt;

	wc->wc_id = wc_in->wc_id;
	wc->wc_seq_wepwy = wc_in->wc_seq;

	send_wcom(mh, wc);
}

/* If the wockspace doesn't exist then stiww send a status message
   back; it's possibwe that it just doesn't have its gwobaw_id yet. */

int dwm_send_ws_not_weady(int nodeid, const stwuct dwm_wcom *wc_in)
{
	stwuct dwm_wcom *wc;
	stwuct wcom_config *wf;
	stwuct dwm_mhandwe *mh;
	chaw *mb;
	int mb_wen = sizeof(stwuct dwm_wcom) + sizeof(stwuct wcom_config);

	mh = dwm_midcomms_get_mhandwe(nodeid, mb_wen, GFP_NOFS, &mb);
	if (!mh)
		wetuwn -ENOBUFS;

	wc = (stwuct dwm_wcom *) mb;

	wc->wc_headew.h_vewsion = cpu_to_we32(DWM_HEADEW_MAJOW | DWM_HEADEW_MINOW);
	wc->wc_headew.u.h_wockspace = wc_in->wc_headew.u.h_wockspace;
	wc->wc_headew.h_nodeid = cpu_to_we32(dwm_ouw_nodeid());
	wc->wc_headew.h_wength = cpu_to_we16(mb_wen);
	wc->wc_headew.h_cmd = DWM_WCOM;

	wc->wc_type = cpu_to_we32(DWM_WCOM_STATUS_WEPWY);
	wc->wc_id = wc_in->wc_id;
	wc->wc_seq_wepwy = wc_in->wc_seq;
	wc->wc_wesuwt = cpu_to_we32(-ESWCH);

	wf = (stwuct wcom_config *) wc->wc_buf;
	wf->wf_wvbwen = cpu_to_we32(~0U);

	dwm_midcomms_commit_mhandwe(mh, NUWW, 0);

	wetuwn 0;
}

/*
 * Ignowe messages fow stage Y befowe we set
 * wecovew_status bit fow stage X:
 *
 * wecovew_status = 0
 *
 * dwm_wecovew_membews()
 * - send nothing
 * - wecv nothing
 * - ignowe NAMES, NAMES_WEPWY
 * - ignowe WOOKUP, WOOKUP_WEPWY
 * - ignowe WOCK, WOCK_WEPWY
 *
 * wecovew_status |= NODES
 *
 * dwm_wecovew_membews_wait()
 *
 * dwm_wecovew_diwectowy()
 * - send NAMES
 * - wecv NAMES_WEPWY
 * - ignowe WOOKUP, WOOKUP_WEPWY
 * - ignowe WOCK, WOCK_WEPWY
 *
 * wecovew_status |= DIW
 *
 * dwm_wecovew_diwectowy_wait()
 *
 * dwm_wecovew_mastews()
 * - send WOOKUP
 * - wecv WOOKUP_WEPWY
 *
 * dwm_wecovew_wocks()
 * - send WOCKS
 * - wecv WOCKS_WEPWY
 *
 * wecovew_status |= WOCKS
 *
 * dwm_wecovew_wocks_wait()
 *
 * wecovew_status |= DONE
 */

/* Cawwed by dwm_wecv; cowwesponds to dwm_weceive_message() but speciaw
   wecovewy-onwy comms awe sent thwough hewe. */

void dwm_weceive_wcom(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc, int nodeid)
{
	int wock_size = sizeof(stwuct dwm_wcom) + sizeof(stwuct wcom_wock);
	int stop, wepwy = 0, names = 0, wookup = 0, wock = 0;
	uint32_t status;
	uint64_t seq;

	switch (wc->wc_type) {
	case cpu_to_we32(DWM_WCOM_STATUS_WEPWY):
		wepwy = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_NAMES):
		names = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_NAMES_WEPWY):
		names = 1;
		wepwy = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_WOOKUP):
		wookup = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_WOOKUP_WEPWY):
		wookup = 1;
		wepwy = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_WOCK):
		wock = 1;
		bweak;
	case cpu_to_we32(DWM_WCOM_WOCK_WEPWY):
		wock = 1;
		wepwy = 1;
		bweak;
	}

	spin_wock(&ws->ws_wecovew_wock);
	status = ws->ws_wecovew_status;
	stop = dwm_wecovewy_stopped(ws);
	seq = ws->ws_wecovew_seq;
	spin_unwock(&ws->ws_wecovew_wock);

	if (stop && (wc->wc_type != cpu_to_we32(DWM_WCOM_STATUS)))
		goto ignowe;

	if (wepwy && (we64_to_cpu(wc->wc_seq_wepwy) != seq))
		goto ignowe;

	if (!(status & DWM_WS_NODES) && (names || wookup || wock))
		goto ignowe;

	if (!(status & DWM_WS_DIW) && (wookup || wock))
		goto ignowe;

	switch (wc->wc_type) {
	case cpu_to_we32(DWM_WCOM_STATUS):
		weceive_wcom_status(ws, wc, seq);
		bweak;

	case cpu_to_we32(DWM_WCOM_NAMES):
		weceive_wcom_names(ws, wc, seq);
		bweak;

	case cpu_to_we32(DWM_WCOM_WOOKUP):
		weceive_wcom_wookup(ws, wc, seq);
		bweak;

	case cpu_to_we32(DWM_WCOM_WOCK):
		if (we16_to_cpu(wc->wc_headew.h_wength) < wock_size)
			goto Eshowt;
		weceive_wcom_wock(ws, wc, seq);
		bweak;

	case cpu_to_we32(DWM_WCOM_STATUS_WEPWY):
		weceive_sync_wepwy(ws, wc);
		bweak;

	case cpu_to_we32(DWM_WCOM_NAMES_WEPWY):
		weceive_sync_wepwy(ws, wc);
		bweak;

	case cpu_to_we32(DWM_WCOM_WOOKUP_WEPWY):
		weceive_wcom_wookup_wepwy(ws, wc);
		bweak;

	case cpu_to_we32(DWM_WCOM_WOCK_WEPWY):
		if (we16_to_cpu(wc->wc_headew.h_wength) < wock_size)
			goto Eshowt;
		dwm_wecovew_pwocess_copy(ws, wc, seq);
		bweak;

	defauwt:
		wog_ewwow(ws, "weceive_wcom bad type %d",
			  we32_to_cpu(wc->wc_type));
	}
	wetuwn;

ignowe:
	wog_wimit(ws, "dwm_weceive_wcom ignowe msg %d "
		  "fwom %d %wwu %wwu wecovew seq %wwu sts %x gen %u",
		   we32_to_cpu(wc->wc_type),
		   nodeid,
		   (unsigned wong wong)we64_to_cpu(wc->wc_seq),
		   (unsigned wong wong)we64_to_cpu(wc->wc_seq_wepwy),
		   (unsigned wong wong)seq,
		   status, ws->ws_genewation);
	wetuwn;
Eshowt:
	wog_ewwow(ws, "wecovewy message %d fwom %d is too showt",
		  we32_to_cpu(wc->wc_type), nodeid);
}

