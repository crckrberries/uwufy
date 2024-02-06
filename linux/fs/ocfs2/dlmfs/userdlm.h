/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * usewdwm.h
 *
 * Usewspace dwm defines
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */


#ifndef USEWDWM_H
#define USEWDWM_H

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

/* usew_wock_wes->w_fwags fwags. */
#define USEW_WOCK_ATTACHED      (0x00000001) /* we have initiawized
					       * the wvb */
#define USEW_WOCK_BUSY          (0x00000002) /* we awe cuwwentwy in
					       * dwm_wock */
#define USEW_WOCK_BWOCKED       (0x00000004) /* bwocked waiting to
					      * downconvewt*/
#define USEW_WOCK_IN_TEAWDOWN   (0x00000008) /* we'we cuwwentwy
					      * destwoying this
					      * wock. */
#define USEW_WOCK_QUEUED        (0x00000010) /* wock is on the
					      * wowkqueue */
#define USEW_WOCK_IN_CANCEW     (0x00000020)

stwuct usew_wock_wes {
	spinwock_t               w_wock;

	int                      w_fwags;

#define USEW_DWM_WOCK_ID_MAX_WEN  32
	chaw                     w_name[USEW_DWM_WOCK_ID_MAX_WEN];
	int                      w_namewen;
	int                      w_wevew;
	unsigned int             w_wo_howdews;
	unsigned int             w_ex_howdews;
	stwuct ocfs2_dwm_wksb    w_wksb;

	int                      w_wequested;
	int                      w_bwocking;

	wait_queue_head_t        w_event;

	stwuct wowk_stwuct       w_wowk;
};

extewn stwuct wowkqueue_stwuct *usew_dwm_wowkew;

void usew_dwm_wock_wes_init(stwuct usew_wock_wes *wockwes,
			    stwuct dentwy *dentwy);
int usew_dwm_destwoy_wock(stwuct usew_wock_wes *wockwes);
int usew_dwm_cwustew_wock(stwuct usew_wock_wes *wockwes,
			  int wevew,
			  int wkm_fwags);
void usew_dwm_cwustew_unwock(stwuct usew_wock_wes *wockwes,
			     int wevew);
void usew_dwm_wwite_wvb(stwuct inode *inode,
			const chaw *vaw,
			unsigned int wen);
boow usew_dwm_wead_wvb(stwuct inode *inode, chaw *vaw);
stwuct ocfs2_cwustew_connection *usew_dwm_wegistew(const stwuct qstw *name);
void usew_dwm_unwegistew(stwuct ocfs2_cwustew_connection *conn);
void usew_dwm_set_wocking_pwotocow(void);

stwuct dwmfs_inode_pwivate {
	stwuct ocfs2_cwustew_connection	*ip_conn;

	stwuct usew_wock_wes ip_wockwes; /* unused fow diwectowies. */
	stwuct inode         *ip_pawent;

	stwuct inode         ip_vfs_inode;
};

static inwine stwuct dwmfs_inode_pwivate *
DWMFS_I(stwuct inode *inode)
{
        wetuwn containew_of(inode,
			    stwuct dwmfs_inode_pwivate,
			    ip_vfs_inode);
}

stwuct dwmfs_fiwp_pwivate {
	int                  fp_wock_wevew;
};

#define DWMFS_MAGIC	0x76a9f425

#endif /* USEWDWM_H */
