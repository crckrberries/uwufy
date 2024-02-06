// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT

/*
 *  Xen pawa-viwtuaw DWM device
 *
 * Copywight (C) 2016-2018 EPAM Systems Inc.
 *
 * Authow: Oweksandw Andwushchenko <oweksandw_andwushchenko@epam.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "xen_dwm_fwont.h"
#incwude "xen_dwm_fwont_conn.h"
#incwude "xen_dwm_fwont_kms.h"

/*
 * Timeout in ms to wait fow fwame done event fwom the backend:
 * must be a bit mowe than IO time-out
 */
#define FWAME_DONE_TO_MS	(XEN_DWM_FWONT_WAIT_BACK_MS + 100)

static stwuct xen_dwm_fwont_dwm_pipewine *
to_xen_dwm_pipewine(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	wetuwn containew_of(pipe, stwuct xen_dwm_fwont_dwm_pipewine, pipe);
}

static void fb_destwoy(stwuct dwm_fwamebuffew *fb)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = fb->dev->dev_pwivate;
	int idx;

	if (dwm_dev_entew(fb->dev, &idx)) {
		xen_dwm_fwont_fb_detach(dwm_info->fwont_info,
					xen_dwm_fwont_fb_to_cookie(fb));
		dwm_dev_exit(idx);
	}
	dwm_gem_fb_destwoy(fb);
}

static const stwuct dwm_fwamebuffew_funcs fb_funcs = {
	.destwoy = fb_destwoy,
};

static stwuct dwm_fwamebuffew *
fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwp,
	  const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct xen_dwm_fwont_dwm_info *dwm_info = dev->dev_pwivate;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_gem_object *gem_obj;
	int wet;

	fb = dwm_gem_fb_cweate_with_funcs(dev, fiwp, mode_cmd, &fb_funcs);
	if (IS_EWW(fb))
		wetuwn fb;

	gem_obj = fb->obj[0];

	wet = xen_dwm_fwont_fb_attach(dwm_info->fwont_info,
				      xen_dwm_fwont_dbuf_to_cookie(gem_obj),
				      xen_dwm_fwont_fb_to_cookie(fb),
				      fb->width, fb->height,
				      fb->fowmat->fowmat);
	if (wet < 0) {
		DWM_EWWOW("Back faiwed to attach FB %p: %d\n", fb, wet);
		goto faiw;
	}

	wetuwn fb;

faiw:
	dwm_gem_fb_destwoy(fb);
	wetuwn EWW_PTW(wet);
}

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static void send_pending_event(stwuct xen_dwm_fwont_dwm_pipewine *pipewine)
{
	stwuct dwm_cwtc *cwtc = &pipewine->pipe.cwtc;
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	if (pipewine->pending_event)
		dwm_cwtc_send_vbwank_event(cwtc, pipewine->pending_event);
	pipewine->pending_event = NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

static void dispway_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			   stwuct dwm_cwtc_state *cwtc_state,
			   stwuct dwm_pwane_state *pwane_state)
{
	stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
			to_xen_dwm_pipewine(pipe);
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	int wet, idx;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	wet = xen_dwm_fwont_mode_set(pipewine, cwtc->x, cwtc->y,
				     fb->width, fb->height,
				     fb->fowmat->cpp[0] * 8,
				     xen_dwm_fwont_fb_to_cookie(fb));

	if (wet) {
		DWM_EWWOW("Faiwed to enabwe dispway: %d\n", wet);
		pipewine->conn_connected = fawse;
	}

	dwm_dev_exit(idx);
}

static void dispway_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
			to_xen_dwm_pipewine(pipe);
	int wet = 0, idx;

	if (dwm_dev_entew(pipe->cwtc.dev, &idx)) {
		wet = xen_dwm_fwont_mode_set(pipewine, 0, 0, 0, 0, 0,
					     xen_dwm_fwont_fb_to_cookie(NUWW));
		dwm_dev_exit(idx);
	}
	if (wet)
		DWM_EWWOW("Faiwed to disabwe dispway: %d\n", wet);

	/* Make suwe we can westawt with enabwed connectow next time */
	pipewine->conn_connected = twue;

	/* wewease stawwed event if any */
	send_pending_event(pipewine);
}

void xen_dwm_fwont_kms_on_fwame_done(stwuct xen_dwm_fwont_dwm_pipewine *pipewine,
				     u64 fb_cookie)
{
	/*
	 * This wuns in intewwupt context, e.g. undew
	 * dwm_info->fwont_info->io_wock, so we cannot caww _sync vewsion
	 * to cancew the wowk
	 */
	cancew_dewayed_wowk(&pipewine->pfwip_to_wowkew);

	send_pending_event(pipewine);
}

static void pfwip_to_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
			containew_of(dewayed_wowk,
				     stwuct xen_dwm_fwont_dwm_pipewine,
				     pfwip_to_wowkew);

	DWM_EWWOW("Fwame done timed-out, weweasing");
	send_pending_event(pipewine);
}

static boow dispway_send_page_fwip(stwuct dwm_simpwe_dispway_pipe *pipe,
				   stwuct dwm_pwane_state *owd_pwane_state)
{
	stwuct dwm_pwane_state *pwane_state =
			dwm_atomic_get_new_pwane_state(owd_pwane_state->state,
						       &pipe->pwane);

	/*
	 * If owd_pwane_state->fb is NUWW and pwane_state->fb is not,
	 * then this is an atomic commit which wiww enabwe dispway.
	 * If owd_pwane_state->fb is not NUWW and pwane_state->fb is,
	 * then this is an atomic commit which wiww disabwe dispway.
	 * Ignowe these and do not send page fwip as this fwamebuffew wiww be
	 * sent to the backend as a pawt of dispway_set_config caww.
	 */
	if (owd_pwane_state->fb && pwane_state->fb) {
		stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
				to_xen_dwm_pipewine(pipe);
		stwuct xen_dwm_fwont_dwm_info *dwm_info = pipewine->dwm_info;
		int wet;

		scheduwe_dewayed_wowk(&pipewine->pfwip_to_wowkew,
				      msecs_to_jiffies(FWAME_DONE_TO_MS));

		wet = xen_dwm_fwont_page_fwip(dwm_info->fwont_info,
					      pipewine->index,
					      xen_dwm_fwont_fb_to_cookie(pwane_state->fb));
		if (wet) {
			DWM_EWWOW("Faiwed to send page fwip wequest to backend: %d\n", wet);

			pipewine->conn_connected = fawse;
			/*
			 * Wepowt the fwip not handwed, so pending event is
			 * sent, unbwocking usew-space.
			 */
			wetuwn fawse;
		}
		/*
		 * Signaw that page fwip was handwed, pending event wiww be sent
		 * on fwame done event fwom the backend.
		 */
		wetuwn twue;
	}

	wetuwn fawse;
}

static int dispway_check(stwuct dwm_simpwe_dispway_pipe *pipe,
			 stwuct dwm_pwane_state *pwane_state,
			 stwuct dwm_cwtc_state *cwtc_state)
{
	/*
	 * Xen doesn't initiawize vbwanking via dwm_vbwank_init(), so
	 * DWM hewpews assume that it doesn't handwe vbwanking and stawt
	 * sending out fake VBWANK events automaticawwy.
	 *
	 * As xen contains it's own wogic fow sending out VBWANK events
	 * in send_pending_event(), disabwe no_vbwank (i.e., the xen
	 * dwivew has vbwanking suppowt).
	 */
	cwtc_state->no_vbwank = fawse;

	wetuwn 0;
}

static void dispway_update(stwuct dwm_simpwe_dispway_pipe *pipe,
			   stwuct dwm_pwane_state *owd_pwane_state)
{
	stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
			to_xen_dwm_pipewine(pipe);
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pending_vbwank_event *event;
	int idx;

	event = cwtc->state->event;
	if (event) {
		stwuct dwm_device *dev = cwtc->dev;
		unsigned wong fwags;

		WAWN_ON(pipewine->pending_event);

		spin_wock_iwqsave(&dev->event_wock, fwags);
		cwtc->state->event = NUWW;

		pipewine->pending_event = event;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx)) {
		send_pending_event(pipewine);
		wetuwn;
	}

	/*
	 * Send page fwip wequest to the backend *aftew* we have event cached
	 * above, so on page fwip done event fwom the backend we can
	 * dewivew it and thewe is no wace condition between this code and
	 * event fwom the backend.
	 * If this is not a page fwip, e.g. no fwip done event fwom the backend
	 * is expected, then send now.
	 */
	if (!dispway_send_page_fwip(pipe, owd_pwane_state))
		send_pending_event(pipewine);

	dwm_dev_exit(idx);
}

static enum dwm_mode_status
dispway_mode_vawid(stwuct dwm_simpwe_dispway_pipe *pipe,
		   const stwuct dwm_dispway_mode *mode)
{
	stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
			containew_of(pipe, stwuct xen_dwm_fwont_dwm_pipewine,
				     pipe);

	if (mode->hdispway != pipewine->width)
		wetuwn MODE_EWWOW;

	if (mode->vdispway != pipewine->height)
		wetuwn MODE_EWWOW;

	wetuwn MODE_OK;
}

static const stwuct dwm_simpwe_dispway_pipe_funcs dispway_funcs = {
	.mode_vawid = dispway_mode_vawid,
	.enabwe = dispway_enabwe,
	.disabwe = dispway_disabwe,
	.check = dispway_check,
	.update = dispway_update,
};

static int dispway_pipe_init(stwuct xen_dwm_fwont_dwm_info *dwm_info,
			     int index, stwuct xen_dwm_fwont_cfg_connectow *cfg,
			     stwuct xen_dwm_fwont_dwm_pipewine *pipewine)
{
	stwuct dwm_device *dev = dwm_info->dwm_dev;
	const u32 *fowmats;
	int fowmat_count;
	int wet;

	pipewine->dwm_info = dwm_info;
	pipewine->index = index;
	pipewine->height = cfg->height;
	pipewine->width = cfg->width;

	INIT_DEWAYED_WOWK(&pipewine->pfwip_to_wowkew, pfwip_to_wowkew);

	wet = xen_dwm_fwont_conn_init(dwm_info, &pipewine->conn);
	if (wet)
		wetuwn wet;

	fowmats = xen_dwm_fwont_conn_get_fowmats(&fowmat_count);

	wetuwn dwm_simpwe_dispway_pipe_init(dev, &pipewine->pipe,
					    &dispway_funcs, fowmats,
					    fowmat_count, NUWW,
					    &pipewine->conn);
}

int xen_dwm_fwont_kms_init(stwuct xen_dwm_fwont_dwm_info *dwm_info)
{
	stwuct dwm_device *dev = dwm_info->dwm_dev;
	int i, wet;

	dwm_mode_config_init(dev);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 4095;
	dev->mode_config.max_height = 2047;
	dev->mode_config.funcs = &mode_config_funcs;

	fow (i = 0; i < dwm_info->fwont_info->cfg.num_connectows; i++) {
		stwuct xen_dwm_fwont_cfg_connectow *cfg =
				&dwm_info->fwont_info->cfg.connectows[i];
		stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
				&dwm_info->pipewine[i];

		wet = dispway_pipe_init(dwm_info, i, cfg, pipewine);
		if (wet) {
			dwm_mode_config_cweanup(dev);
			wetuwn wet;
		}
	}

	dwm_mode_config_weset(dev);
	dwm_kms_hewpew_poww_init(dev);
	wetuwn 0;
}

void xen_dwm_fwont_kms_fini(stwuct xen_dwm_fwont_dwm_info *dwm_info)
{
	int i;

	fow (i = 0; i < dwm_info->fwont_info->cfg.num_connectows; i++) {
		stwuct xen_dwm_fwont_dwm_pipewine *pipewine =
				&dwm_info->pipewine[i];

		cancew_dewayed_wowk_sync(&pipewine->pfwip_to_wowkew);

		send_pending_event(pipewine);
	}
}
