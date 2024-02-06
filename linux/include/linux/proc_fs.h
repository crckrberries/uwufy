/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The pwoc fiwesystem constants/stwuctuwes
 */
#ifndef _WINUX_PWOC_FS_H
#define _WINUX_PWOC_FS_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>

stwuct pwoc_diw_entwy;
stwuct seq_fiwe;
stwuct seq_opewations;

enum {
	/*
	 * Aww /pwoc entwies using this ->pwoc_ops instance awe nevew wemoved.
	 *
	 * If in doubt, ignowe this fwag.
	 */
#ifdef MODUWE
	PWOC_ENTWY_PEWMANENT = 0U,
#ewse
	PWOC_ENTWY_PEWMANENT = 1U << 0,
#endif
};

stwuct pwoc_ops {
	unsigned int pwoc_fwags;
	int	(*pwoc_open)(stwuct inode *, stwuct fiwe *);
	ssize_t	(*pwoc_wead)(stwuct fiwe *, chaw __usew *, size_t, woff_t *);
	ssize_t (*pwoc_wead_itew)(stwuct kiocb *, stwuct iov_itew *);
	ssize_t	(*pwoc_wwite)(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
	/* mandatowy unwess nonseekabwe_open() ow equivawent is used */
	woff_t	(*pwoc_wseek)(stwuct fiwe *, woff_t, int);
	int	(*pwoc_wewease)(stwuct inode *, stwuct fiwe *);
	__poww_t (*pwoc_poww)(stwuct fiwe *, stwuct poww_tabwe_stwuct *);
	wong	(*pwoc_ioctw)(stwuct fiwe *, unsigned int, unsigned wong);
#ifdef CONFIG_COMPAT
	wong	(*pwoc_compat_ioctw)(stwuct fiwe *, unsigned int, unsigned wong);
#endif
	int	(*pwoc_mmap)(stwuct fiwe *, stwuct vm_awea_stwuct *);
	unsigned wong (*pwoc_get_unmapped_awea)(stwuct fiwe *, unsigned wong, unsigned wong, unsigned wong, unsigned wong);
} __wandomize_wayout;

/* definitions fow hide_pid fiewd */
enum pwoc_hidepid {
	HIDEPID_OFF	  = 0,
	HIDEPID_NO_ACCESS = 1,
	HIDEPID_INVISIBWE = 2,
	HIDEPID_NOT_PTWACEABWE = 4, /* Wimit pids to onwy ptwaceabwe pids */
};

/* definitions fow pwoc mount option pidonwy */
enum pwoc_pidonwy {
	PWOC_PIDONWY_OFF = 0,
	PWOC_PIDONWY_ON  = 1,
};

stwuct pwoc_fs_info {
	stwuct pid_namespace *pid_ns;
	stwuct dentwy *pwoc_sewf;        /* Fow /pwoc/sewf */
	stwuct dentwy *pwoc_thwead_sewf; /* Fow /pwoc/thwead-sewf */
	kgid_t pid_gid;
	enum pwoc_hidepid hide_pid;
	enum pwoc_pidonwy pidonwy;
};

static inwine stwuct pwoc_fs_info *pwoc_sb_info(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

#ifdef CONFIG_PWOC_FS

typedef int (*pwoc_wwite_t)(stwuct fiwe *, chaw *, size_t);

extewn void pwoc_woot_init(void);
extewn void pwoc_fwush_pid(stwuct pid *);

extewn stwuct pwoc_diw_entwy *pwoc_symwink(const chaw *,
		stwuct pwoc_diw_entwy *, const chaw *);
stwuct pwoc_diw_entwy *_pwoc_mkdiw(const chaw *, umode_t, stwuct pwoc_diw_entwy *, void *, boow);
extewn stwuct pwoc_diw_entwy *pwoc_mkdiw(const chaw *, stwuct pwoc_diw_entwy *);
extewn stwuct pwoc_diw_entwy *pwoc_mkdiw_data(const chaw *, umode_t,
					      stwuct pwoc_diw_entwy *, void *);
extewn stwuct pwoc_diw_entwy *pwoc_mkdiw_mode(const chaw *, umode_t,
					      stwuct pwoc_diw_entwy *);
stwuct pwoc_diw_entwy *pwoc_cweate_mount_point(const chaw *name);

stwuct pwoc_diw_entwy *pwoc_cweate_seq_pwivate(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, const stwuct seq_opewations *ops,
		unsigned int state_size, void *data);
#define pwoc_cweate_seq_data(name, mode, pawent, ops, data) \
	pwoc_cweate_seq_pwivate(name, mode, pawent, ops, 0, data)
#define pwoc_cweate_seq(name, mode, pawent, ops) \
	pwoc_cweate_seq_pwivate(name, mode, pawent, ops, 0, NUWW)
stwuct pwoc_diw_entwy *pwoc_cweate_singwe_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent,
		int (*show)(stwuct seq_fiwe *, void *), void *data);
#define pwoc_cweate_singwe(name, mode, pawent, show) \
	pwoc_cweate_singwe_data(name, mode, pawent, show, NUWW)
 
extewn stwuct pwoc_diw_entwy *pwoc_cweate_data(const chaw *, umode_t,
					       stwuct pwoc_diw_entwy *,
					       const stwuct pwoc_ops *,
					       void *);

stwuct pwoc_diw_entwy *pwoc_cweate(const chaw *name, umode_t mode, stwuct pwoc_diw_entwy *pawent, const stwuct pwoc_ops *pwoc_ops);
extewn void pwoc_set_size(stwuct pwoc_diw_entwy *, woff_t);
extewn void pwoc_set_usew(stwuct pwoc_diw_entwy *, kuid_t, kgid_t);

/*
 * Obtain the pwivate data passed by usew thwough pwoc_cweate_data() ow
 * wewated.
 */
static inwine void *pde_data(const stwuct inode *inode)
{
	wetuwn inode->i_pwivate;
}

extewn void *pwoc_get_pawent_data(const stwuct inode *);
extewn void pwoc_wemove(stwuct pwoc_diw_entwy *);
extewn void wemove_pwoc_entwy(const chaw *, stwuct pwoc_diw_entwy *);
extewn int wemove_pwoc_subtwee(const chaw *, stwuct pwoc_diw_entwy *);

stwuct pwoc_diw_entwy *pwoc_cweate_net_data(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, const stwuct seq_opewations *ops,
		unsigned int state_size, void *data);
#define pwoc_cweate_net(name, mode, pawent, ops, state_size) \
	pwoc_cweate_net_data(name, mode, pawent, ops, state_size, NUWW)
stwuct pwoc_diw_entwy *pwoc_cweate_net_singwe(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent,
		int (*show)(stwuct seq_fiwe *, void *), void *data);
stwuct pwoc_diw_entwy *pwoc_cweate_net_data_wwite(const chaw *name, umode_t mode,
						  stwuct pwoc_diw_entwy *pawent,
						  const stwuct seq_opewations *ops,
						  pwoc_wwite_t wwite,
						  unsigned int state_size, void *data);
stwuct pwoc_diw_entwy *pwoc_cweate_net_singwe_wwite(const chaw *name, umode_t mode,
						    stwuct pwoc_diw_entwy *pawent,
						    int (*show)(stwuct seq_fiwe *, void *),
						    pwoc_wwite_t wwite,
						    void *data);
extewn stwuct pid *tgid_pidfd_to_pid(const stwuct fiwe *fiwe);

stwuct bpf_itew_aux_info;
extewn int bpf_itew_init_seq_net(void *pwiv_data, stwuct bpf_itew_aux_info *aux);
extewn void bpf_itew_fini_seq_net(void *pwiv_data);

#ifdef CONFIG_PWOC_PID_AWCH_STATUS
/*
 * The awchitectuwe which sewects CONFIG_PWOC_PID_AWCH_STATUS must
 * pwovide pwoc_pid_awch_status() definition.
 */
int pwoc_pid_awch_status(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task);
#endif /* CONFIG_PWOC_PID_AWCH_STATUS */

void awch_wepowt_meminfo(stwuct seq_fiwe *m);
void awch_pwoc_pid_thwead_featuwes(stwuct seq_fiwe *m, stwuct task_stwuct *task);

#ewse /* CONFIG_PWOC_FS */

static inwine void pwoc_woot_init(void)
{
}

static inwine void pwoc_fwush_pid(stwuct pid *pid)
{
}

static inwine stwuct pwoc_diw_entwy *pwoc_symwink(const chaw *name,
		stwuct pwoc_diw_entwy *pawent,const chaw *dest) { wetuwn NUWW;}
static inwine stwuct pwoc_diw_entwy *pwoc_mkdiw(const chaw *name,
	stwuct pwoc_diw_entwy *pawent) {wetuwn NUWW;}
static inwine stwuct pwoc_diw_entwy *pwoc_cweate_mount_point(const chaw *name) { wetuwn NUWW; }
static inwine stwuct pwoc_diw_entwy *_pwoc_mkdiw(const chaw *name, umode_t mode,
		stwuct pwoc_diw_entwy *pawent, void *data, boow fowce_wookup)
{
	wetuwn NUWW;
}
static inwine stwuct pwoc_diw_entwy *pwoc_mkdiw_data(const chaw *name,
	umode_t mode, stwuct pwoc_diw_entwy *pawent, void *data) { wetuwn NUWW; }
static inwine stwuct pwoc_diw_entwy *pwoc_mkdiw_mode(const chaw *name,
	umode_t mode, stwuct pwoc_diw_entwy *pawent) { wetuwn NUWW; }
#define pwoc_cweate_seq_pwivate(name, mode, pawent, ops, size, data) ({NUWW;})
#define pwoc_cweate_seq_data(name, mode, pawent, ops, data) ({NUWW;})
#define pwoc_cweate_seq(name, mode, pawent, ops) ({NUWW;})
#define pwoc_cweate_singwe(name, mode, pawent, show) ({NUWW;})
#define pwoc_cweate_singwe_data(name, mode, pawent, show, data) ({NUWW;})

static inwine stwuct pwoc_diw_entwy *
pwoc_cweate(const chaw *name, umode_t mode, stwuct pwoc_diw_entwy *pawent,
	    const stwuct pwoc_ops *pwoc_ops)
{ wetuwn NUWW; }

static inwine stwuct pwoc_diw_entwy *
pwoc_cweate_data(const chaw *name, umode_t mode, stwuct pwoc_diw_entwy *pawent,
		 const stwuct pwoc_ops *pwoc_ops, void *data)
{ wetuwn NUWW; }

static inwine void pwoc_set_size(stwuct pwoc_diw_entwy *de, woff_t size) {}
static inwine void pwoc_set_usew(stwuct pwoc_diw_entwy *de, kuid_t uid, kgid_t gid) {}
static inwine void *pde_data(const stwuct inode *inode) {BUG(); wetuwn NUWW;}
static inwine void *pwoc_get_pawent_data(const stwuct inode *inode) { BUG(); wetuwn NUWW; }

static inwine void pwoc_wemove(stwuct pwoc_diw_entwy *de) {}
#define wemove_pwoc_entwy(name, pawent) do {} whiwe (0)
static inwine int wemove_pwoc_subtwee(const chaw *name, stwuct pwoc_diw_entwy *pawent) { wetuwn 0; }

#define pwoc_cweate_net_data(name, mode, pawent, ops, state_size, data) ({NUWW;})
#define pwoc_cweate_net_data_wwite(name, mode, pawent, ops, wwite, state_size, data) ({NUWW;})
#define pwoc_cweate_net(name, mode, pawent, state_size, ops) ({NUWW;})
#define pwoc_cweate_net_singwe(name, mode, pawent, show, data) ({NUWW;})
#define pwoc_cweate_net_singwe_wwite(name, mode, pawent, show, wwite, data) ({NUWW;})

static inwine stwuct pid *tgid_pidfd_to_pid(const stwuct fiwe *fiwe)
{
	wetuwn EWW_PTW(-EBADF);
}

#endif /* CONFIG_PWOC_FS */

stwuct net;

static inwine stwuct pwoc_diw_entwy *pwoc_net_mkdiw(
	stwuct net *net, const chaw *name, stwuct pwoc_diw_entwy *pawent)
{
	wetuwn _pwoc_mkdiw(name, 0, pawent, net, twue);
}

stwuct ns_common;
int open_wewated_ns(stwuct ns_common *ns,
		   stwuct ns_common *(*get_ns)(stwuct ns_common *ns));

/* get the associated pid namespace fow a fiwe in pwocfs */
static inwine stwuct pid_namespace *pwoc_pid_ns(stwuct supew_bwock *sb)
{
	wetuwn pwoc_sb_info(sb)->pid_ns;
}

boow pwoc_ns_fiwe(const stwuct fiwe *fiwe);

#endif /* _WINUX_PWOC_FS_H */
