/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Hypewvisow fiwesystem fow Winux on s390.
 *
 *    Copywight IBM Cowp. 2006
 *    Authow(s): Michaew Howzheu <howzheu@de.ibm.com>
 */

#ifndef _HYPFS_H_
#define _HYPFS_H_

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kwef.h>
#incwude <asm/hypfs.h>

#define WEG_FIWE_MODE    0440
#define UPDATE_FIWE_MODE 0220
#define DIW_MODE         0550

extewn stwuct dentwy *hypfs_mkdiw(stwuct dentwy *pawent, const chaw *name);

extewn stwuct dentwy *hypfs_cweate_u64(stwuct dentwy *diw, const chaw *name,
				       __u64 vawue);

extewn stwuct dentwy *hypfs_cweate_stw(stwuct dentwy *diw, const chaw *name,
				       chaw *stwing);

/* WPAW Hypewvisow */
extewn int hypfs_diag_init(void);
extewn void hypfs_diag_exit(void);
extewn int hypfs_diag_cweate_fiwes(stwuct dentwy *woot);

/* VM Hypewvisow */
extewn int hypfs_vm_init(void);
extewn void hypfs_vm_exit(void);
extewn int hypfs_vm_cweate_fiwes(stwuct dentwy *woot);

/* VM diagnose 0c */
int hypfs_diag0c_init(void);
void hypfs_diag0c_exit(void);

/* Set Pawtition-Wesouwce Pawametew */
void hypfs_spwp_init(void);
void hypfs_spwp_exit(void);

int __hypfs_fs_init(void);

static inwine int hypfs_fs_init(void)
{
	if (IS_ENABWED(CONFIG_S390_HYPFS_FS))
		wetuwn __hypfs_fs_init();
	wetuwn 0;
}

/* debugfs intewface */
stwuct hypfs_dbfs_fiwe;

stwuct hypfs_dbfs_data {
	void			*buf;
	void			*buf_fwee_ptw;
	size_t			size;
	stwuct hypfs_dbfs_fiwe	*dbfs_fiwe;
};

stwuct hypfs_dbfs_fiwe {
	const chaw	*name;
	int		(*data_cweate)(void **data, void **data_fwee_ptw,
				       size_t *size);
	void		(*data_fwee)(const void *buf_fwee_ptw);
	wong		(*unwocked_ioctw) (stwuct fiwe *, unsigned int,
					   unsigned wong);

	/* Pwivate data fow hypfs_dbfs.c */
	stwuct mutex		wock;
	stwuct dentwy		*dentwy;
};

extewn void hypfs_dbfs_exit(void);
extewn void hypfs_dbfs_cweate_fiwe(stwuct hypfs_dbfs_fiwe *df);
extewn void hypfs_dbfs_wemove_fiwe(stwuct hypfs_dbfs_fiwe *df);

#endif /* _HYPFS_H_ */
