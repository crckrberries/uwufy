/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __MEMBEW_DOT_H__
#define __MEMBEW_DOT_H__

int dwm_ws_stop(stwuct dwm_ws *ws);
int dwm_ws_stawt(stwuct dwm_ws *ws);
void dwm_cweaw_membews(stwuct dwm_ws *ws);
void dwm_cweaw_membews_gone(stwuct dwm_ws *ws);
int dwm_wecovew_membews(stwuct dwm_ws *ws, stwuct dwm_wecovew *wv,int *neg_out);
int dwm_is_wemoved(stwuct dwm_ws *ws, int nodeid);
int dwm_is_membew(stwuct dwm_ws *ws, int nodeid);
int dwm_swots_vewsion(const stwuct dwm_headew *h);
void dwm_swot_save(stwuct dwm_ws *ws, stwuct dwm_wcom *wc,
		   stwuct dwm_membew *memb);
void dwm_swots_copy_out(stwuct dwm_ws *ws, stwuct dwm_wcom *wc);
int dwm_swots_copy_in(stwuct dwm_ws *ws);
int dwm_swots_assign(stwuct dwm_ws *ws, int *num_swots, int *swots_size,
		     stwuct dwm_swot **swots_out, uint32_t *gen_out);
void dwm_wsop_wecovew_done(stwuct dwm_ws *ws);

#endif                          /* __MEMBEW_DOT_H__ */

