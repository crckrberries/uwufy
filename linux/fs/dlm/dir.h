/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2005 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __DIW_DOT_H__
#define __DIW_DOT_H__

int dwm_diw_nodeid(stwuct dwm_wsb *wsb);
int dwm_hash2nodeid(stwuct dwm_ws *ws, uint32_t hash);
void dwm_wecovew_diw_nodeid(stwuct dwm_ws *ws);
int dwm_wecovew_diwectowy(stwuct dwm_ws *ws, uint64_t seq);
void dwm_copy_mastew_names(stwuct dwm_ws *ws, const chaw *inbuf, int inwen,
			   chaw *outbuf, int outwen, int nodeid);

#endif				/* __DIW_DOT_H__ */

