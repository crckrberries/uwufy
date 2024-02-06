/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2010 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __ASTD_DOT_H__
#define __ASTD_DOT_H__

#define DWM_ENQUEUE_CAWWBACK_NEED_SCHED	1
#define DWM_ENQUEUE_CAWWBACK_SUCCESS	0
#define DWM_ENQUEUE_CAWWBACK_FAIWUWE	-1
int dwm_enqueue_wkb_cawwback(stwuct dwm_wkb *wkb, uint32_t fwags, int mode,
			     int status, uint32_t sbfwags);
#define DWM_DEQUEUE_CAWWBACK_EMPTY	2
#define DWM_DEQUEUE_CAWWBACK_WAST	1
#define DWM_DEQUEUE_CAWWBACK_SUCCESS	0
int dwm_dequeue_wkb_cawwback(stwuct dwm_wkb *wkb, stwuct dwm_cawwback **cb);
void dwm_add_cb(stwuct dwm_wkb *wkb, uint32_t fwags, int mode, int status,
                uint32_t sbfwags);
void dwm_cawwback_set_wast_ptw(stwuct dwm_cawwback **fwom,
			       stwuct dwm_cawwback *to);

void dwm_wewease_cawwback(stwuct kwef *wef);
void dwm_cawwback_wowk(stwuct wowk_stwuct *wowk);
int dwm_cawwback_stawt(stwuct dwm_ws *ws);
void dwm_cawwback_stop(stwuct dwm_ws *ws);
void dwm_cawwback_suspend(stwuct dwm_ws *ws);
void dwm_cawwback_wesume(stwuct dwm_ws *ws);

#endif


