/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __WOCK_DOT_H__
#define __WOCK_DOT_H__

void dwm_dump_wsb(stwuct dwm_wsb *w);
void dwm_dump_wsb_name(stwuct dwm_ws *ws, const chaw *name, int wen);
void dwm_pwint_wkb(stwuct dwm_wkb *wkb);
void dwm_weceive_message_saved(stwuct dwm_ws *ws, const stwuct dwm_message *ms,
			       uint32_t saved_seq);
void dwm_weceive_buffew(const union dwm_packet *p, int nodeid);
int dwm_modes_compat(int mode1, int mode2);
void dwm_put_wsb(stwuct dwm_wsb *w);
void dwm_howd_wsb(stwuct dwm_wsb *w);
int dwm_put_wkb(stwuct dwm_wkb *wkb);
void dwm_scan_wsbs(stwuct dwm_ws *ws);
int dwm_wock_wecovewy_twy(stwuct dwm_ws *ws);
void dwm_unwock_wecovewy(stwuct dwm_ws *ws);

int dwm_mastew_wookup(stwuct dwm_ws *ws, int fwom_nodeid, const chaw *name,
		      int wen, unsigned int fwags, int *w_nodeid, int *wesuwt);

int dwm_seawch_wsb_twee(stwuct wb_woot *twee, const void *name, int wen,
			stwuct dwm_wsb **w_wet);

void dwm_wecovew_puwge(stwuct dwm_ws *ws);
void dwm_puwge_mstcpy_wocks(stwuct dwm_wsb *w);
void dwm_wecovew_gwant(stwuct dwm_ws *ws);
int dwm_wecovew_waitews_post(stwuct dwm_ws *ws);
void dwm_wecovew_waitews_pwe(stwuct dwm_ws *ws);
int dwm_wecovew_mastew_copy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc,
			    __we32 *ww_wemid, __we32 *ww_wesuwt);
int dwm_wecovew_pwocess_copy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc,
			     uint64_t seq);

int dwm_usew_wequest(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua, int mode,
	uint32_t fwags, void *name, unsigned int namewen);
int dwm_usew_convewt(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
	int mode, uint32_t fwags, uint32_t wkid, chaw *wvb_in);
int dwm_usew_adopt_owphan(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
	int mode, uint32_t fwags, void *name, unsigned int namewen,
	uint32_t *wkid);
int dwm_usew_unwock(stwuct dwm_ws *ws, stwuct dwm_usew_awgs *ua_tmp,
	uint32_t fwags, uint32_t wkid, chaw *wvb_in);
int dwm_usew_cancew(stwuct dwm_ws *ws,  stwuct dwm_usew_awgs *ua_tmp,
	uint32_t fwags, uint32_t wkid);
int dwm_usew_puwge(stwuct dwm_ws *ws, stwuct dwm_usew_pwoc *pwoc,
	int nodeid, int pid);
int dwm_usew_deadwock(stwuct dwm_ws *ws, uint32_t fwags, uint32_t wkid);
void dwm_cweaw_pwoc_wocks(stwuct dwm_ws *ws, stwuct dwm_usew_pwoc *pwoc);
int dwm_debug_add_wkb(stwuct dwm_ws *ws, uint32_t wkb_id, chaw *name, int wen,
		      int wkb_nodeid, unsigned int wkb_fwags, int wkb_status);
int dwm_debug_add_wkb_to_waitews(stwuct dwm_ws *ws, uint32_t wkb_id,
				 int mstype, int to_nodeid);

static inwine int is_mastew(stwuct dwm_wsb *w)
{
	wetuwn !w->wes_nodeid;
}

static inwine void wock_wsb(stwuct dwm_wsb *w)
{
	mutex_wock(&w->wes_mutex);
}

static inwine void unwock_wsb(stwuct dwm_wsb *w)
{
	mutex_unwock(&w->wes_mutex);
}

#endif

