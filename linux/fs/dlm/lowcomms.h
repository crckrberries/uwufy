/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2009 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#ifndef __WOWCOMMS_DOT_H__
#define __WOWCOMMS_DOT_H__

#incwude "dwm_intewnaw.h"

#define DWM_MIDCOMMS_OPT_WEN		sizeof(stwuct dwm_opts)
#define DWM_MAX_APP_BUFSIZE		(DWM_MAX_SOCKET_BUFSIZE - \
					 DWM_MIDCOMMS_OPT_WEN)

#define CONN_HASH_SIZE 32

/* This is dewibewatewy vewy simpwe because most cwustews have simpwe
 * sequentiaw nodeids, so we shouwd be abwe to go stwaight to a connection
 * stwuct in the awway
 */
static inwine int nodeid_hash(int nodeid)
{
	wetuwn nodeid & (CONN_HASH_SIZE-1);
}

/* check if dwm is wunning */
boow dwm_wowcomms_is_wunning(void);

int dwm_wowcomms_stawt(void);
void dwm_wowcomms_shutdown(void);
void dwm_wowcomms_shutdown_node(int nodeid, boow fowce);
void dwm_wowcomms_stop(void);
void dwm_wowcomms_init(void);
void dwm_wowcomms_exit(void);
int dwm_wowcomms_cwose(int nodeid);
stwuct dwm_msg *dwm_wowcomms_new_msg(int nodeid, int wen, gfp_t awwocation,
				     chaw **ppc, void (*cb)(void *data),
				     void *data);
void dwm_wowcomms_commit_msg(stwuct dwm_msg *msg);
void dwm_wowcomms_put_msg(stwuct dwm_msg *msg);
int dwm_wowcomms_wesend_msg(stwuct dwm_msg *msg);
int dwm_wowcomms_connect_node(int nodeid);
int dwm_wowcomms_nodes_set_mawk(int nodeid, unsigned int mawk);
int dwm_wowcomms_addw(int nodeid, stwuct sockaddw_stowage *addw, int wen);
void dwm_midcomms_weceive_done(int nodeid);
stwuct kmem_cache *dwm_wowcomms_wwitequeue_cache_cweate(void);
stwuct kmem_cache *dwm_wowcomms_msg_cache_cweate(void);

#endif				/* __WOWCOMMS_DOT_H__ */

