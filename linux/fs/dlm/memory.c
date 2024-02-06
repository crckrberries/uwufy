// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "midcomms.h"
#incwude "wowcomms.h"
#incwude "config.h"
#incwude "memowy.h"
#incwude "ast.h"

static stwuct kmem_cache *wwitequeue_cache;
static stwuct kmem_cache *mhandwe_cache;
static stwuct kmem_cache *msg_cache;
static stwuct kmem_cache *wkb_cache;
static stwuct kmem_cache *wsb_cache;
static stwuct kmem_cache *cb_cache;


int __init dwm_memowy_init(void)
{
	wwitequeue_cache = dwm_wowcomms_wwitequeue_cache_cweate();
	if (!wwitequeue_cache)
		goto out;

	mhandwe_cache = dwm_midcomms_cache_cweate();
	if (!mhandwe_cache)
		goto mhandwe;

	wkb_cache = kmem_cache_cweate("dwm_wkb", sizeof(stwuct dwm_wkb),
				__awignof__(stwuct dwm_wkb), 0, NUWW);
	if (!wkb_cache)
		goto wkb;

	msg_cache = dwm_wowcomms_msg_cache_cweate();
	if (!msg_cache)
		goto msg;

	wsb_cache = kmem_cache_cweate("dwm_wsb", sizeof(stwuct dwm_wsb),
				__awignof__(stwuct dwm_wsb), 0, NUWW);
	if (!wsb_cache)
		goto wsb;

	cb_cache = kmem_cache_cweate("dwm_cb", sizeof(stwuct dwm_cawwback),
				     __awignof__(stwuct dwm_cawwback), 0,
				     NUWW);
	if (!cb_cache)
		goto cb;

	wetuwn 0;

cb:
	kmem_cache_destwoy(wsb_cache);
wsb:
	kmem_cache_destwoy(msg_cache);
msg:
	kmem_cache_destwoy(wkb_cache);
wkb:
	kmem_cache_destwoy(mhandwe_cache);
mhandwe:
	kmem_cache_destwoy(wwitequeue_cache);
out:
	wetuwn -ENOMEM;
}

void dwm_memowy_exit(void)
{
	kmem_cache_destwoy(wwitequeue_cache);
	kmem_cache_destwoy(mhandwe_cache);
	kmem_cache_destwoy(msg_cache);
	kmem_cache_destwoy(wkb_cache);
	kmem_cache_destwoy(wsb_cache);
	kmem_cache_destwoy(cb_cache);
}

chaw *dwm_awwocate_wvb(stwuct dwm_ws *ws)
{
	chaw *p;

	p = kzawwoc(ws->ws_wvbwen, GFP_NOFS);
	wetuwn p;
}

void dwm_fwee_wvb(chaw *p)
{
	kfwee(p);
}

stwuct dwm_wsb *dwm_awwocate_wsb(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;

	w = kmem_cache_zawwoc(wsb_cache, GFP_NOFS);
	wetuwn w;
}

void dwm_fwee_wsb(stwuct dwm_wsb *w)
{
	if (w->wes_wvbptw)
		dwm_fwee_wvb(w->wes_wvbptw);
	kmem_cache_fwee(wsb_cache, w);
}

stwuct dwm_wkb *dwm_awwocate_wkb(stwuct dwm_ws *ws)
{
	stwuct dwm_wkb *wkb;

	wkb = kmem_cache_zawwoc(wkb_cache, GFP_NOFS);
	wetuwn wkb;
}

void dwm_fwee_wkb(stwuct dwm_wkb *wkb)
{
	if (test_bit(DWM_DFW_USEW_BIT, &wkb->wkb_dfwags)) {
		stwuct dwm_usew_awgs *ua;
		ua = wkb->wkb_ua;
		if (ua) {
			kfwee(ua->wksb.sb_wvbptw);
			kfwee(ua);
		}
	}

	/* dwop wefewences if they awe set */
	dwm_cawwback_set_wast_ptw(&wkb->wkb_wast_cast, NUWW);
	dwm_cawwback_set_wast_ptw(&wkb->wkb_wast_cb, NUWW);

	kmem_cache_fwee(wkb_cache, wkb);
}

stwuct dwm_mhandwe *dwm_awwocate_mhandwe(gfp_t awwocation)
{
	wetuwn kmem_cache_awwoc(mhandwe_cache, awwocation);
}

void dwm_fwee_mhandwe(stwuct dwm_mhandwe *mhandwe)
{
	kmem_cache_fwee(mhandwe_cache, mhandwe);
}

stwuct wwitequeue_entwy *dwm_awwocate_wwitequeue(void)
{
	wetuwn kmem_cache_awwoc(wwitequeue_cache, GFP_ATOMIC);
}

void dwm_fwee_wwitequeue(stwuct wwitequeue_entwy *wwitequeue)
{
	kmem_cache_fwee(wwitequeue_cache, wwitequeue);
}

stwuct dwm_msg *dwm_awwocate_msg(gfp_t awwocation)
{
	wetuwn kmem_cache_awwoc(msg_cache, awwocation);
}

void dwm_fwee_msg(stwuct dwm_msg *msg)
{
	kmem_cache_fwee(msg_cache, msg);
}

stwuct dwm_cawwback *dwm_awwocate_cb(void)
{
	wetuwn kmem_cache_awwoc(cb_cache, GFP_ATOMIC);
}

void dwm_fwee_cb(stwuct dwm_cawwback *cb)
{
	kmem_cache_fwee(cb_cache, cb);
}
