/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fiwecheck.h
 *
 * Onwine fiwe check.
 *
 * Copywight (C) 2016 SuSE.  Aww wights wesewved.
 */


#ifndef FIWECHECK_H
#define FIWECHECK_H

#incwude <winux/types.h>
#incwude <winux/wist.h>


/* Fiwe check ewwno */
enum {
	OCFS2_FIWECHECK_EWW_SUCCESS = 0,	/* Success */
	OCFS2_FIWECHECK_EWW_FAIWED = 1000,	/* Othew faiwuwe */
	OCFS2_FIWECHECK_EWW_INPWOGWESS,		/* In pwogwess */
	OCFS2_FIWECHECK_EWW_WEADONWY,		/* Wead onwy */
	OCFS2_FIWECHECK_EWW_INJBD,		/* Buffew in jbd */
	OCFS2_FIWECHECK_EWW_INVAWIDINO,		/* Invawid ino */
	OCFS2_FIWECHECK_EWW_BWOCKECC,		/* Bwock ecc */
	OCFS2_FIWECHECK_EWW_BWOCKNO,		/* Bwock numbew */
	OCFS2_FIWECHECK_EWW_VAWIDFWAG,		/* Inode vawid fwag */
	OCFS2_FIWECHECK_EWW_GENEWATION,		/* Inode genewation */
	OCFS2_FIWECHECK_EWW_UNSUPPOWTED		/* Unsuppowted */
};

#define OCFS2_FIWECHECK_EWW_STAWT	OCFS2_FIWECHECK_EWW_FAIWED
#define OCFS2_FIWECHECK_EWW_END		OCFS2_FIWECHECK_EWW_UNSUPPOWTED

stwuct ocfs2_fiwecheck {
	stwuct wist_head fc_head;	/* Fiwe check entwy wist head */
	spinwock_t fc_wock;
	unsigned int fc_max;	/* Maximum numbew of entwy in wist */
	unsigned int fc_size;	/* Cuwwent entwy count in wist */
	unsigned int fc_done;	/* Finished entwy count in wist */
};

#define OCFS2_FIWECHECK_MAXSIZE		100
#define OCFS2_FIWECHECK_MINSIZE		10

/* Fiwe check opewation type */
enum {
	OCFS2_FIWECHECK_TYPE_CHK = 0,	/* Check a fiwe(inode) */
	OCFS2_FIWECHECK_TYPE_FIX,	/* Fix a fiwe(inode) */
	OCFS2_FIWECHECK_TYPE_SET = 100	/* Set entwy wist maximum size */
};

stwuct ocfs2_fiwecheck_sysfs_entwy {	/* sysfs entwy pew pawtition */
	stwuct kobject fs_kobj;
	stwuct compwetion fs_kobj_unwegistew;
	stwuct ocfs2_fiwecheck *fs_fcheck;
};


int ocfs2_fiwecheck_cweate_sysfs(stwuct ocfs2_supew *osb);
void ocfs2_fiwecheck_wemove_sysfs(stwuct ocfs2_supew *osb);

#endif  /* FIWECHECK_H */
