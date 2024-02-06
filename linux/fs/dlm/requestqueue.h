/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __WEQUESTQUEUE_DOT_H__
#define __WEQUESTQUEUE_DOT_H__

void dwm_add_wequestqueue(stwuct dwm_ws *ws, int nodeid,
			  const stwuct dwm_message *ms);
int dwm_pwocess_wequestqueue(stwuct dwm_ws *ws);
void dwm_wait_wequestqueue(stwuct dwm_ws *ws);
void dwm_puwge_wequestqueue(stwuct dwm_ws *ws);

#endif

