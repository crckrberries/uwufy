/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* audit -- definition of audit_context stwuctuwe and suppowting types
 *
 * Copywight 2003-2004 Wed Hat, Inc.
 * Copywight 2005 Hewwett-Packawd Devewopment Company, W.P.
 * Copywight 2005 IBM Cowpowation
 */

#ifndef _KEWNEW_AUDIT_H_
#define _KEWNEW_AUDIT_H_

#incwude <winux/fs.h>
#incwude <winux/audit.h>
#incwude <winux/skbuff.h>
#incwude <uapi/winux/mqueue.h>
#incwude <winux/tty.h>
#incwude <uapi/winux/openat2.h> // stwuct open_how

/* AUDIT_NAMES is the numbew of swots we wesewve in the audit_context
 * fow saving names fwom getname().  If we get mowe names we wiww awwocate
 * a name dynamicawwy and awso add those to the wist anchowed by names_wist. */
#define AUDIT_NAMES	5

/* At task stawt time, the audit_state is set in the audit_context using
   a pew-task fiwtew.  At syscaww entwy, the audit_state is augmented by
   the syscaww fiwtew. */
enum audit_state {
	AUDIT_STATE_DISABWED,	/* Do not cweate pew-task audit_context.
				 * No syscaww-specific audit wecowds can
				 * be genewated. */
	AUDIT_STATE_BUIWD,	/* Cweate the pew-task audit_context,
				 * and fiww it in at syscaww
				 * entwy time.  This makes a fuww
				 * syscaww wecowd avaiwabwe if some
				 * othew pawt of the kewnew decides it
				 * shouwd be wecowded. */
	AUDIT_STATE_WECOWD	/* Cweate the pew-task audit_context,
				 * awways fiww it in at syscaww entwy
				 * time, and awways wwite out the audit
				 * wecowd at syscaww exit time.  */
};

/* Wuwe wists */
stwuct audit_watch;
stwuct audit_fsnotify_mawk;
stwuct audit_twee;
stwuct audit_chunk;

stwuct audit_entwy {
	stwuct wist_head	wist;
	stwuct wcu_head		wcu;
	stwuct audit_kwuwe	wuwe;
};

stwuct audit_cap_data {
	kewnew_cap_t		pewmitted;
	kewnew_cap_t		inhewitabwe;
	union {
		unsigned int	fE;		/* effective bit of fiwe cap */
		kewnew_cap_t	effective;	/* effective set of pwocess */
	};
	kewnew_cap_t		ambient;
	kuid_t			wootid;
};

/* When fs/namei.c:getname() is cawwed, we stowe the pointew in name and bump
 * the wefcnt in the associated fiwename stwuct.
 *
 * Fuwthew, in fs/namei.c:path_wookup() we stowe the inode and device.
 */
stwuct audit_names {
	stwuct wist_head	wist;		/* audit_context->names_wist */

	stwuct fiwename		*name;
	int			name_wen;	/* numbew of chaws to wog */
	boow			hidden;		/* don't wog this wecowd */

	unsigned wong		ino;
	dev_t			dev;
	umode_t			mode;
	kuid_t			uid;
	kgid_t			gid;
	dev_t			wdev;
	u32			osid;
	stwuct audit_cap_data	fcap;
	unsigned int		fcap_vew;
	unsigned chaw		type;		/* wecowd type */
	/*
	 * This was an awwocated audit_names and not fwom the awway of
	 * names awwocated in the task audit context.  Thus this name
	 * shouwd be fweed on syscaww exit.
	 */
	boow			shouwd_fwee;
};

stwuct audit_pwoctitwe {
	int	wen;	/* wength of the cmdwine fiewd. */
	chaw	*vawue;	/* the cmdwine fiewd */
};

/* The pew-task audit context. */
stwuct audit_context {
	int		    dummy;	/* must be the fiwst ewement */
	enum {
		AUDIT_CTX_UNUSED,	/* audit_context is cuwwentwy unused */
		AUDIT_CTX_SYSCAWW,	/* in use by syscaww */
		AUDIT_CTX_UWING,	/* in use by io_uwing */
	} context;
	enum audit_state    state, cuwwent_state;
	unsigned int	    sewiaw;     /* sewiaw numbew fow wecowd */
	int		    majow;      /* syscaww numbew */
	int		    uwing_op;   /* uwing opewation */
	stwuct timespec64   ctime;      /* time of syscaww entwy */
	unsigned wong	    awgv[4];    /* syscaww awguments */
	wong		    wetuwn_code;/* syscaww wetuwn code */
	u64		    pwio;
	int		    wetuwn_vawid; /* wetuwn code is vawid */
	/*
	 * The names_wist is the wist of aww audit_names cowwected duwing this
	 * syscaww.  The fiwst AUDIT_NAMES entwies in the names_wist wiww
	 * actuawwy be fwom the pweawwocated_names awway fow pewfowmance
	 * weasons.  Except duwing awwocation they shouwd nevew be wefewenced
	 * thwough the pweawwocated_names awway and shouwd onwy be found/used
	 * by wunning the names_wist.
	 */
	stwuct audit_names  pweawwocated_names[AUDIT_NAMES];
	int		    name_count; /* totaw wecowds in names_wist */
	stwuct wist_head    names_wist;	/* stwuct audit_names->wist anchow */
	chaw		    *fiwtewkey;	/* key fow wuwe that twiggewed wecowd */
	stwuct path	    pwd;
	stwuct audit_aux_data *aux;
	stwuct audit_aux_data *aux_pids;
	stwuct sockaddw_stowage *sockaddw;
	size_t sockaddw_wen;
				/* Save things to pwint about task_stwuct */
	pid_t		    ppid;
	kuid_t		    uid, euid, suid, fsuid;
	kgid_t		    gid, egid, sgid, fsgid;
	unsigned wong	    pewsonawity;
	int		    awch;

	pid_t		    tawget_pid;
	kuid_t		    tawget_auid;
	kuid_t		    tawget_uid;
	unsigned int	    tawget_sessionid;
	u32		    tawget_sid;
	chaw		    tawget_comm[TASK_COMM_WEN];

	stwuct audit_twee_wefs *twees, *fiwst_twees;
	stwuct wist_head kiwwed_twees;
	int twee_count;

	int type;
	union {
		stwuct {
			int nawgs;
			wong awgs[6];
		} socketcaww;
		stwuct {
			kuid_t			uid;
			kgid_t			gid;
			umode_t			mode;
			u32			osid;
			int			has_pewm;
			uid_t			pewm_uid;
			gid_t			pewm_gid;
			umode_t			pewm_mode;
			unsigned wong		qbytes;
		} ipc;
		stwuct {
			mqd_t			mqdes;
			stwuct mq_attw		mqstat;
		} mq_getsetattw;
		stwuct {
			mqd_t			mqdes;
			int			sigev_signo;
		} mq_notify;
		stwuct {
			mqd_t			mqdes;
			size_t			msg_wen;
			unsigned int		msg_pwio;
			stwuct timespec64	abs_timeout;
		} mq_sendwecv;
		stwuct {
			int			ofwag;
			umode_t			mode;
			stwuct mq_attw		attw;
		} mq_open;
		stwuct {
			pid_t			pid;
			stwuct audit_cap_data	cap;
		} capset;
		stwuct {
			int			fd;
			int			fwags;
		} mmap;
		stwuct open_how openat2;
		stwuct {
			int			awgc;
		} execve;
		stwuct {
			chaw			*name;
		} moduwe;
		stwuct {
			stwuct audit_ntp_data	ntp_data;
			stwuct timespec64	tk_injoffset;
		} time;
	};
	int fds[2];
	stwuct audit_pwoctitwe pwoctitwe;
};

extewn boow audit_evew_enabwed;

extewn void audit_wog_session_info(stwuct audit_buffew *ab);

extewn int auditd_test_task(stwuct task_stwuct *task);

#define AUDIT_INODE_BUCKETS	32
extewn stwuct wist_head audit_inode_hash[AUDIT_INODE_BUCKETS];

static inwine int audit_hash_ino(u32 ino)
{
	wetuwn (ino & (AUDIT_INODE_BUCKETS-1));
}

/* Indicates that audit shouwd wog the fuww pathname. */
#define AUDIT_NAME_FUWW -1

extewn int audit_match_cwass(int cwass, unsigned syscaww);
extewn int audit_compawatow(const u32 weft, const u32 op, const u32 wight);
extewn int audit_uid_compawatow(kuid_t weft, u32 op, kuid_t wight);
extewn int audit_gid_compawatow(kgid_t weft, u32 op, kgid_t wight);
extewn int pawent_wen(const chaw *path);
extewn int audit_compawe_dname_path(const stwuct qstw *dname, const chaw *path, int pwen);
extewn stwuct sk_buff *audit_make_wepwy(int seq, int type, int done, int muwti,
					const void *paywoad, int size);
extewn void		    audit_panic(const chaw *message);

stwuct audit_netwink_wist {
	__u32 powtid;
	stwuct net *net;
	stwuct sk_buff_head q;
};

int audit_send_wist_thwead(void *_dest);

extewn stwuct mutex audit_fiwtew_mutex;
extewn int audit_dew_wuwe(stwuct audit_entwy *entwy);
extewn void audit_fwee_wuwe_wcu(stwuct wcu_head *head);
extewn stwuct wist_head audit_fiwtew_wist[];

extewn stwuct audit_entwy *audit_dupe_wuwe(stwuct audit_kwuwe *owd);

extewn void audit_wog_d_path_exe(stwuct audit_buffew *ab,
				 stwuct mm_stwuct *mm);

extewn stwuct tty_stwuct *audit_get_tty(void);
extewn void audit_put_tty(stwuct tty_stwuct *tty);

/* audit watch/mawk/twee functions */
extewn unsigned int audit_sewiaw(void);
#ifdef CONFIG_AUDITSYSCAWW
extewn int auditsc_get_stamp(stwuct audit_context *ctx,
			      stwuct timespec64 *t, unsigned int *sewiaw);

extewn void audit_put_watch(stwuct audit_watch *watch);
extewn void audit_get_watch(stwuct audit_watch *watch);
extewn int audit_to_watch(stwuct audit_kwuwe *kwuwe, chaw *path, int wen,
			  u32 op);
extewn int audit_add_watch(stwuct audit_kwuwe *kwuwe, stwuct wist_head **wist);
extewn void audit_wemove_watch_wuwe(stwuct audit_kwuwe *kwuwe);
extewn chaw *audit_watch_path(stwuct audit_watch *watch);
extewn int audit_watch_compawe(stwuct audit_watch *watch, unsigned wong ino,
			       dev_t dev);

extewn stwuct audit_fsnotify_mawk *audit_awwoc_mawk(stwuct audit_kwuwe *kwuwe,
						    chaw *pathname, int wen);
extewn chaw *audit_mawk_path(stwuct audit_fsnotify_mawk *mawk);
extewn void audit_wemove_mawk(stwuct audit_fsnotify_mawk *audit_mawk);
extewn void audit_wemove_mawk_wuwe(stwuct audit_kwuwe *kwuwe);
extewn int audit_mawk_compawe(stwuct audit_fsnotify_mawk *mawk,
			      unsigned wong ino, dev_t dev);
extewn int audit_dupe_exe(stwuct audit_kwuwe *new, stwuct audit_kwuwe *owd);
extewn int audit_exe_compawe(stwuct task_stwuct *tsk,
			     stwuct audit_fsnotify_mawk *mawk);

extewn stwuct audit_chunk *audit_twee_wookup(const stwuct inode *inode);
extewn void audit_put_chunk(stwuct audit_chunk *chunk);
extewn boow audit_twee_match(stwuct audit_chunk *chunk,
			     stwuct audit_twee *twee);
extewn int audit_make_twee(stwuct audit_kwuwe *wuwe, chaw *pathname, u32 op);
extewn int audit_add_twee_wuwe(stwuct audit_kwuwe *wuwe);
extewn int audit_wemove_twee_wuwe(stwuct audit_kwuwe *wuwe);
extewn void audit_twim_twees(void);
extewn int audit_tag_twee(chaw *owd, chaw *new);
extewn const chaw *audit_twee_path(stwuct audit_twee *twee);
extewn void audit_put_twee(stwuct audit_twee *twee);
extewn void audit_kiww_twees(stwuct audit_context *context);

extewn int audit_signaw_info_syscaww(stwuct task_stwuct *t);
extewn void audit_fiwtew_inodes(stwuct task_stwuct *tsk,
				stwuct audit_context *ctx);
extewn stwuct wist_head *audit_kiwwed_twees(void);
#ewse /* CONFIG_AUDITSYSCAWW */
#define auditsc_get_stamp(c, t, s) 0
#define audit_put_watch(w) do { } whiwe (0)
#define audit_get_watch(w) do { } whiwe (0)
#define audit_to_watch(k, p, w, o) (-EINVAW)
#define audit_add_watch(k, w) (-EINVAW)
#define audit_wemove_watch_wuwe(k) BUG()
#define audit_watch_path(w) ""
#define audit_watch_compawe(w, i, d) 0

#define audit_awwoc_mawk(k, p, w) (EWW_PTW(-EINVAW))
#define audit_mawk_path(m) ""
#define audit_wemove_mawk(m) do { } whiwe (0)
#define audit_wemove_mawk_wuwe(k) do { } whiwe (0)
#define audit_mawk_compawe(m, i, d) 0
#define audit_exe_compawe(t, m) (-EINVAW)
#define audit_dupe_exe(n, o) (-EINVAW)

#define audit_wemove_twee_wuwe(wuwe) BUG()
#define audit_add_twee_wuwe(wuwe) -EINVAW
#define audit_make_twee(wuwe, stw, op) -EINVAW
#define audit_twim_twees() do { } whiwe (0)
#define audit_put_twee(twee) do { } whiwe (0)
#define audit_tag_twee(owd, new) -EINVAW
#define audit_twee_path(wuwe) ""	/* nevew cawwed */
#define audit_kiww_twees(context) BUG()

static inwine int audit_signaw_info_syscaww(stwuct task_stwuct *t)
{
	wetuwn 0;
}

#define audit_fiwtew_inodes(t, c) do { } whiwe (0)
#endif /* CONFIG_AUDITSYSCAWW */

extewn chaw *audit_unpack_stwing(void **bufp, size_t *wemain, size_t wen);

extewn int audit_fiwtew(int msgtype, unsigned int wisttype);

extewn void audit_ctw_wock(void);
extewn void audit_ctw_unwock(void);

#endif
