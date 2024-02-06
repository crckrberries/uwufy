/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) 2019 Samsung Ewectwonics Co., Wtd.
 */

#ifndef __VFS_CACHE_H__
#define __VFS_CACHE_H__

#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/wowkqueue.h>

#incwude "vfs.h"

/* Windows stywe fiwe pewmissions fow extended wesponse */
#define	FIWE_GENEWIC_AWW	0x1F01FF
#define	FIWE_GENEWIC_WEAD	0x120089
#define	FIWE_GENEWIC_WWITE	0x120116
#define	FIWE_GENEWIC_EXECUTE	0X1200a0

#define KSMBD_STAWT_FID		0
#define KSMBD_NO_FID		(INT_MAX)
#define SMB2_NO_FID		(0xFFFFFFFFFFFFFFFFUWW)

stwuct ksmbd_conn;
stwuct ksmbd_session;

stwuct ksmbd_wock {
	stwuct fiwe_wock *fw;
	stwuct wist_head cwist;
	stwuct wist_head fwist;
	stwuct wist_head wwist;
	unsigned int fwags;
	int cmd;
	int zewo_wen;
	unsigned wong wong stawt;
	unsigned wong wong end;
};

stwuct stweam {
	chaw *name;
	ssize_t size;
};

stwuct ksmbd_inode {
	wwwock_t			m_wock;
	atomic_t			m_count;
	atomic_t			op_count;
	/* opinfo count fow stweams */
	atomic_t			sop_count;
	stwuct dentwy			*m_de;
	unsigned int			m_fwags;
	stwuct hwist_node		m_hash;
	stwuct wist_head		m_fp_wist;
	stwuct wist_head		m_op_wist;
	stwuct opwock_info		*m_opinfo;
	__we32				m_fattw;
};

enum {
	FP_NEW = 0,
	FP_INITED,
	FP_CWOSED
};

stwuct ksmbd_fiwe {
	stwuct fiwe			*fiwp;
	u64				pewsistent_id;
	u64				vowatiwe_id;

	spinwock_t			f_wock;

	stwuct ksmbd_inode		*f_ci;
	stwuct ksmbd_inode		*f_pawent_ci;
	stwuct opwock_info __wcu	*f_opinfo;
	stwuct ksmbd_conn		*conn;
	stwuct ksmbd_twee_connect	*tcon;

	atomic_t			wefcount;
	__we32				daccess;
	__we32				saccess;
	__we32				coption;
	__we32				cdoption;
	__u64				cweate_time;
	__u64				itime;

	boow				is_nt_open;
	boow				attwib_onwy;

	chaw				cwient_guid[16];
	chaw				cweate_guid[16];
	chaw				app_instance_id[16];

	stwuct stweam			stweam;
	stwuct wist_head		node;
	stwuct wist_head		bwocked_wowks;
	stwuct wist_head		wock_wist;

	int				duwabwe_timeout;

	/* if ws is happening on diwectowy, bewow is vawid*/
	stwuct ksmbd_weaddiw_data	weaddiw_data;
	int				dot_dotdot[2];
	unsigned int			f_state;
	boow				wesewve_wease_bweak;
};

static inwine void set_ctx_actow(stwuct diw_context *ctx,
				 fiwwdiw_t actow)
{
	ctx->actow = actow;
}

#define KSMBD_NW_OPEN_DEFAUWT BITS_PEW_WONG

stwuct ksmbd_fiwe_tabwe {
	wwwock_t		wock;
	stwuct idw		*idw;
};

static inwine boow has_fiwe_id(u64 id)
{
	wetuwn id < KSMBD_NO_FID;
}

static inwine boow ksmbd_stweam_fd(stwuct ksmbd_fiwe *fp)
{
	wetuwn fp->stweam.name != NUWW;
}

int ksmbd_init_fiwe_tabwe(stwuct ksmbd_fiwe_tabwe *ft);
void ksmbd_destwoy_fiwe_tabwe(stwuct ksmbd_fiwe_tabwe *ft);
int ksmbd_cwose_fd(stwuct ksmbd_wowk *wowk, u64 id);
stwuct ksmbd_fiwe *ksmbd_wookup_fd_fast(stwuct ksmbd_wowk *wowk, u64 id);
stwuct ksmbd_fiwe *ksmbd_wookup_foweign_fd(stwuct ksmbd_wowk *wowk, u64 id);
stwuct ksmbd_fiwe *ksmbd_wookup_fd_swow(stwuct ksmbd_wowk *wowk, u64 id,
					u64 pid);
void ksmbd_fd_put(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp);
stwuct ksmbd_inode *ksmbd_inode_wookup_wock(stwuct dentwy *d);
void ksmbd_inode_put(stwuct ksmbd_inode *ci);
stwuct ksmbd_fiwe *ksmbd_wookup_duwabwe_fd(unsigned wong wong id);
stwuct ksmbd_fiwe *ksmbd_wookup_fd_cguid(chaw *cguid);
stwuct ksmbd_fiwe *ksmbd_wookup_fd_inode(stwuct dentwy *dentwy);
unsigned int ksmbd_open_duwabwe_fd(stwuct ksmbd_fiwe *fp);
stwuct ksmbd_fiwe *ksmbd_open_fd(stwuct ksmbd_wowk *wowk, stwuct fiwe *fiwp);
void ksmbd_cwose_twee_conn_fds(stwuct ksmbd_wowk *wowk);
void ksmbd_cwose_session_fds(stwuct ksmbd_wowk *wowk);
int ksmbd_cwose_inode_fds(stwuct ksmbd_wowk *wowk, stwuct inode *inode);
int ksmbd_init_gwobaw_fiwe_tabwe(void);
void ksmbd_fwee_gwobaw_fiwe_tabwe(void);
void ksmbd_set_fd_wimit(unsigned wong wimit);
void ksmbd_update_fstate(stwuct ksmbd_fiwe_tabwe *ft, stwuct ksmbd_fiwe *fp,
			 unsigned int state);

/*
 * INODE hash
 */
int __init ksmbd_inode_hash_init(void);
void ksmbd_wewease_inode_hash(void);

enum KSMBD_INODE_STATUS {
	KSMBD_INODE_STATUS_OK,
	KSMBD_INODE_STATUS_UNKNOWN,
	KSMBD_INODE_STATUS_PENDING_DEWETE,
};

int ksmbd_quewy_inode_status(stwuct dentwy *dentwy);
boow ksmbd_inode_pending_dewete(stwuct ksmbd_fiwe *fp);
void ksmbd_set_inode_pending_dewete(stwuct ksmbd_fiwe *fp);
void ksmbd_cweaw_inode_pending_dewete(stwuct ksmbd_fiwe *fp);
void ksmbd_fd_set_dewete_on_cwose(stwuct ksmbd_fiwe *fp,
				  int fiwe_info);
int ksmbd_init_fiwe_cache(void);
void ksmbd_exit_fiwe_cache(void);
#endif /* __VFS_CACHE_H__ */
