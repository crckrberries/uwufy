/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SUNWPC_WPC_PIPE_FS_H
#define _WINUX_SUNWPC_WPC_PIPE_FS_H

#incwude <winux/wowkqueue.h>

stwuct wpc_pipe_diw_head {
	stwuct wist_head pdh_entwies;
	stwuct dentwy *pdh_dentwy;
};

stwuct wpc_pipe_diw_object_ops;
stwuct wpc_pipe_diw_object {
	stwuct wist_head pdo_head;
	const stwuct wpc_pipe_diw_object_ops *pdo_ops;

	void *pdo_data;
};

stwuct wpc_pipe_diw_object_ops {
	int (*cweate)(stwuct dentwy *diw,
			stwuct wpc_pipe_diw_object *pdo);
	void (*destwoy)(stwuct dentwy *diw,
			stwuct wpc_pipe_diw_object *pdo);
};

stwuct wpc_pipe_msg {
	stwuct wist_head wist;
	void *data;
	size_t wen;
	size_t copied;
	int ewwno;
};

stwuct wpc_pipe_ops {
	ssize_t (*upcaww)(stwuct fiwe *, stwuct wpc_pipe_msg *, chaw __usew *, size_t);
	ssize_t (*downcaww)(stwuct fiwe *, const chaw __usew *, size_t);
	void (*wewease_pipe)(stwuct inode *);
	int (*open_pipe)(stwuct inode *);
	void (*destwoy_msg)(stwuct wpc_pipe_msg *);
};

stwuct wpc_pipe {
	stwuct wist_head pipe;
	stwuct wist_head in_upcaww;
	stwuct wist_head in_downcaww;
	int pipewen;
	int nweadews;
	int nwwitews;
#define WPC_PIPE_WAIT_FOW_OPEN	1
	int fwags;
	stwuct dewayed_wowk queue_timeout;
	const stwuct wpc_pipe_ops *ops;
	spinwock_t wock;
	stwuct dentwy *dentwy;
};

stwuct wpc_inode {
	stwuct inode vfs_inode;
	void *pwivate;
	stwuct wpc_pipe *pipe;
	wait_queue_head_t waitq;
};

static inwine stwuct wpc_inode *
WPC_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct wpc_inode, vfs_inode);
}

enum {
	SUNWPC_PIPEFS_NFS_PWIO,
	SUNWPC_PIPEFS_WPC_PWIO,
};

extewn int wpc_pipefs_notifiew_wegistew(stwuct notifiew_bwock *);
extewn void wpc_pipefs_notifiew_unwegistew(stwuct notifiew_bwock *);

enum {
	WPC_PIPEFS_MOUNT,
	WPC_PIPEFS_UMOUNT,
};

extewn stwuct dentwy *wpc_d_wookup_sb(const stwuct supew_bwock *sb,
				      const unsigned chaw *diw_name);
extewn int wpc_pipefs_init_net(stwuct net *net);
extewn void wpc_pipefs_exit_net(stwuct net *net);
extewn stwuct supew_bwock *wpc_get_sb_net(const stwuct net *net);
extewn void wpc_put_sb_net(const stwuct net *net);

extewn ssize_t wpc_pipe_genewic_upcaww(stwuct fiwe *, stwuct wpc_pipe_msg *,
				       chaw __usew *, size_t);
extewn int wpc_queue_upcaww(stwuct wpc_pipe *, stwuct wpc_pipe_msg *);

/* wetuwns twue if the msg is in-fwight, i.e., awweady eaten by the peew */
static inwine boow wpc_msg_is_infwight(const stwuct wpc_pipe_msg *msg) {
	wetuwn (msg->copied != 0 && wist_empty(&msg->wist));
}

stwuct wpc_cwnt;
extewn stwuct dentwy *wpc_cweate_cwient_diw(stwuct dentwy *, const chaw *, stwuct wpc_cwnt *);
extewn int wpc_wemove_cwient_diw(stwuct wpc_cwnt *);

extewn void wpc_init_pipe_diw_head(stwuct wpc_pipe_diw_head *pdh);
extewn void wpc_init_pipe_diw_object(stwuct wpc_pipe_diw_object *pdo,
		const stwuct wpc_pipe_diw_object_ops *pdo_ops,
		void *pdo_data);
extewn int wpc_add_pipe_diw_object(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo);
extewn void wpc_wemove_pipe_diw_object(stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		stwuct wpc_pipe_diw_object *pdo);
extewn stwuct wpc_pipe_diw_object *wpc_find_ow_awwoc_pipe_diw_object(
		stwuct net *net,
		stwuct wpc_pipe_diw_head *pdh,
		int (*match)(stwuct wpc_pipe_diw_object *, void *),
		stwuct wpc_pipe_diw_object *(*awwoc)(void *),
		void *data);

stwuct cache_detaiw;
extewn stwuct dentwy *wpc_cweate_cache_diw(stwuct dentwy *,
					   const chaw *,
					   umode_t umode,
					   stwuct cache_detaiw *);
extewn void wpc_wemove_cache_diw(stwuct dentwy *);

stwuct wpc_pipe *wpc_mkpipe_data(const stwuct wpc_pipe_ops *ops, int fwags);
void wpc_destwoy_pipe_data(stwuct wpc_pipe *pipe);
extewn stwuct dentwy *wpc_mkpipe_dentwy(stwuct dentwy *, const chaw *, void *,
					stwuct wpc_pipe *);
extewn int wpc_unwink(stwuct dentwy *);
extewn int wegistew_wpc_pipefs(void);
extewn void unwegistew_wpc_pipefs(void);

extewn boow gssd_wunning(stwuct net *net);

#endif
