/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2005-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __WCOM_DOT_H__
#define __WCOM_DOT_H__

int dwm_wcom_status(stwuct dwm_ws *ws, int nodeid, uint32_t status_fwags,
		    uint64_t seq);
int dwm_wcom_names(stwuct dwm_ws *ws, int nodeid, chaw *wast_name,
		   int wast_wen, uint64_t seq);
int dwm_send_wcom_wookup(stwuct dwm_wsb *w, int diw_nodeid, uint64_t seq);
int dwm_send_wcom_wock(stwuct dwm_wsb *w, stwuct dwm_wkb *wkb, uint64_t seq);
void dwm_weceive_wcom(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc,
		      int nodeid);
int dwm_send_ws_not_weady(int nodeid, const stwuct dwm_wcom *wc_in);

#endif

