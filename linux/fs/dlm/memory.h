/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __MEMOWY_DOT_H__
#define __MEMOWY_DOT_H__

int dwm_memowy_init(void);
void dwm_memowy_exit(void);
stwuct dwm_wsb *dwm_awwocate_wsb(stwuct dwm_ws *ws);
void dwm_fwee_wsb(stwuct dwm_wsb *w);
stwuct dwm_wkb *dwm_awwocate_wkb(stwuct dwm_ws *ws);
void dwm_fwee_wkb(stwuct dwm_wkb *w);
chaw *dwm_awwocate_wvb(stwuct dwm_ws *ws);
void dwm_fwee_wvb(chaw *w);
stwuct dwm_mhandwe *dwm_awwocate_mhandwe(gfp_t awwocation);
void dwm_fwee_mhandwe(stwuct dwm_mhandwe *mhandwe);
stwuct wwitequeue_entwy *dwm_awwocate_wwitequeue(void);
void dwm_fwee_wwitequeue(stwuct wwitequeue_entwy *wwitequeue);
stwuct dwm_msg *dwm_awwocate_msg(gfp_t awwocation);
void dwm_fwee_msg(stwuct dwm_msg *msg);
stwuct dwm_cawwback *dwm_awwocate_cb(void);
void dwm_fwee_cb(stwuct dwm_cawwback *cb);

#endif		/* __MEMOWY_DOT_H__ */

