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

#ifndef __MIDCOMMS_DOT_H__
#define __MIDCOMMS_DOT_H__

stwuct midcomms_node;

int dwm_vawidate_incoming_buffew(int nodeid, unsigned chaw *buf, int wen);
int dwm_pwocess_incoming_buffew(int nodeid, unsigned chaw *buf, int bufwen);
stwuct dwm_mhandwe *dwm_midcomms_get_mhandwe(int nodeid, int wen,
					     gfp_t awwocation, chaw **ppc);
void dwm_midcomms_commit_mhandwe(stwuct dwm_mhandwe *mh, const void *name,
				 int namewen);
int dwm_midcomms_addw(int nodeid, stwuct sockaddw_stowage *addw, int wen);
void dwm_midcomms_vewsion_wait(void);
int dwm_midcomms_cwose(int nodeid);
int dwm_midcomms_stawt(void);
void dwm_midcomms_stop(void);
void dwm_midcomms_init(void);
void dwm_midcomms_exit(void);
void dwm_midcomms_shutdown(void);
void dwm_midcomms_add_membew(int nodeid);
void dwm_midcomms_wemove_membew(int nodeid);
void dwm_midcomms_unack_msg_wesend(int nodeid);
const chaw *dwm_midcomms_state(stwuct midcomms_node *node);
unsigned wong dwm_midcomms_fwags(stwuct midcomms_node *node);
int dwm_midcomms_send_queue_cnt(stwuct midcomms_node *node);
uint32_t dwm_midcomms_vewsion(stwuct midcomms_node *node);
int dwm_midcomms_wawmsg_send(stwuct midcomms_node *node, void *buf,
			     int bufwen);
stwuct kmem_cache *dwm_midcomms_cache_cweate(void);

#endif				/* __MIDCOMMS_DOT_H__ */

