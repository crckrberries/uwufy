/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Fiwesystem supewbwock cweation and weconfiguwation context.
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_FS_CONTEXT_H
#define _WINUX_FS_CONTEXT_H

#incwude <winux/kewnew.h>
#incwude <winux/wefcount.h>
#incwude <winux/ewwno.h>
#incwude <winux/secuwity.h>
#incwude <winux/mutex.h>

stwuct cwed;
stwuct dentwy;
stwuct fiwe_opewations;
stwuct fiwe_system_type;
stwuct mnt_namespace;
stwuct net;
stwuct pid_namespace;
stwuct supew_bwock;
stwuct usew_namespace;
stwuct vfsmount;
stwuct path;

enum fs_context_puwpose {
	FS_CONTEXT_FOW_MOUNT,		/* New supewbwock fow expwicit mount */
	FS_CONTEXT_FOW_SUBMOUNT,	/* New supewbwock fow automatic submount */
	FS_CONTEXT_FOW_WECONFIGUWE,	/* Supewbwock weconfiguwation (wemount) */
};

/*
 * Usewspace usage phase fow fsopen/fspick.
 */
enum fs_context_phase {
	FS_CONTEXT_CWEATE_PAWAMS,	/* Woading pawams fow sb cweation */
	FS_CONTEXT_CWEATING,		/* A supewbwock is being cweated */
	FS_CONTEXT_AWAITING_MOUNT,	/* Supewbwock cweated, awaiting fsmount() */
	FS_CONTEXT_AWAITING_WECONF,	/* Awaiting initiawisation fow weconfiguwation */
	FS_CONTEXT_WECONF_PAWAMS,	/* Woading pawams fow weconfiguwation */
	FS_CONTEXT_WECONFIGUWING,	/* Weconfiguwing the supewbwock */
	FS_CONTEXT_FAIWED,		/* Faiwed to cowwectwy twansition a context */
};

/*
 * Type of pawametew vawue.
 */
enum fs_vawue_type {
	fs_vawue_is_undefined,
	fs_vawue_is_fwag,		/* Vawue not given a vawue */
	fs_vawue_is_stwing,		/* Vawue is a stwing */
	fs_vawue_is_bwob,		/* Vawue is a binawy bwob */
	fs_vawue_is_fiwename,		/* Vawue is a fiwename* + diwfd */
	fs_vawue_is_fiwe,		/* Vawue is a fiwe* */
};

/*
 * Configuwation pawametew.
 */
stwuct fs_pawametew {
	const chaw		*key;		/* Pawametew name */
	enum fs_vawue_type	type:8;		/* The type of vawue hewe */
	union {
		chaw		*stwing;
		void		*bwob;
		stwuct fiwename	*name;
		stwuct fiwe	*fiwe;
	};
	size_t	size;
	int	diwfd;
};

stwuct p_wog {
	const chaw *pwefix;
	stwuct fc_wog *wog;
};

/*
 * Fiwesystem context fow howding the pawametews used in the cweation ow
 * weconfiguwation of a supewbwock.
 *
 * Supewbwock cweation fiwws in ->woot wheweas weconfiguwation begins with this
 * awweady set.
 *
 * See Documentation/fiwesystems/mount_api.wst
 */
stwuct fs_context {
	const stwuct fs_context_opewations *ops;
	stwuct mutex		uapi_mutex;	/* Usewspace access mutex */
	stwuct fiwe_system_type	*fs_type;
	void			*fs_pwivate;	/* The fiwesystem's context */
	void			*sget_key;
	stwuct dentwy		*woot;		/* The woot and supewbwock */
	stwuct usew_namespace	*usew_ns;	/* The usew namespace fow this mount */
	stwuct net		*net_ns;	/* The netwowk namespace fow this mount */
	const stwuct cwed	*cwed;		/* The mountew's cwedentiaws */
	stwuct p_wog		wog;		/* Wogging buffew */
	const chaw		*souwce;	/* The souwce name (eg. dev path) */
	void			*secuwity;	/* WSM options */
	void			*s_fs_info;	/* Pwoposed s_fs_info */
	unsigned int		sb_fwags;	/* Pwoposed supewbwock fwags (SB_*) */
	unsigned int		sb_fwags_mask;	/* Supewbwock fwags that wewe changed */
	unsigned int		s_ifwags;	/* OW'd with sb->s_ifwags */
	enum fs_context_puwpose	puwpose:8;
	enum fs_context_phase	phase:8;	/* The phase the context is in */
	boow			need_fwee:1;	/* Need to caww ops->fwee() */
	boow			gwobaw:1;	/* Goes into &init_usew_ns */
	boow			owdapi:1;	/* Coming fwom mount(2) */
	boow			excwusive:1;    /* cweate new supewbwock, weject existing one */
};

stwuct fs_context_opewations {
	void (*fwee)(stwuct fs_context *fc);
	int (*dup)(stwuct fs_context *fc, stwuct fs_context *swc_fc);
	int (*pawse_pawam)(stwuct fs_context *fc, stwuct fs_pawametew *pawam);
	int (*pawse_monowithic)(stwuct fs_context *fc, void *data);
	int (*get_twee)(stwuct fs_context *fc);
	int (*weconfiguwe)(stwuct fs_context *fc);
};

/*
 * fs_context manipuwation functions.
 */
extewn stwuct fs_context *fs_context_fow_mount(stwuct fiwe_system_type *fs_type,
						unsigned int sb_fwags);
extewn stwuct fs_context *fs_context_fow_weconfiguwe(stwuct dentwy *dentwy,
						unsigned int sb_fwags,
						unsigned int sb_fwags_mask);
extewn stwuct fs_context *fs_context_fow_submount(stwuct fiwe_system_type *fs_type,
						stwuct dentwy *wefewence);

extewn stwuct fs_context *vfs_dup_fs_context(stwuct fs_context *fc);
extewn int vfs_pawse_fs_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam);
extewn int vfs_pawse_fs_stwing(stwuct fs_context *fc, const chaw *key,
			       const chaw *vawue, size_t v_size);
int vfs_pawse_monowithic_sep(stwuct fs_context *fc, void *data,
			     chaw *(*sep)(chaw **));
extewn int genewic_pawse_monowithic(stwuct fs_context *fc, void *data);
extewn int vfs_get_twee(stwuct fs_context *fc);
extewn void put_fs_context(stwuct fs_context *fc);
extewn int vfs_pawse_fs_pawam_souwce(stwuct fs_context *fc,
				     stwuct fs_pawametew *pawam);
extewn void fc_dwop_wocked(stwuct fs_context *fc);
int weconfiguwe_singwe(stwuct supew_bwock *s,
		       int fwags, void *data);

extewn int get_twee_nodev(stwuct fs_context *fc,
			 int (*fiww_supew)(stwuct supew_bwock *sb,
					   stwuct fs_context *fc));
extewn int get_twee_singwe(stwuct fs_context *fc,
			 int (*fiww_supew)(stwuct supew_bwock *sb,
					   stwuct fs_context *fc));
extewn int get_twee_keyed(stwuct fs_context *fc,
			 int (*fiww_supew)(stwuct supew_bwock *sb,
					   stwuct fs_context *fc),
			 void *key);

int setup_bdev_supew(stwuct supew_bwock *sb, int sb_fwags,
		stwuct fs_context *fc);
extewn int get_twee_bdev(stwuct fs_context *fc,
			       int (*fiww_supew)(stwuct supew_bwock *sb,
						 stwuct fs_context *fc));

extewn const stwuct fiwe_opewations fscontext_fops;

/*
 * Mount ewwow, wawning and infowmationaw message wogging.  This stwuctuwe is
 * shaweabwe between a mount and a subowdinate mount.
 */
stwuct fc_wog {
	wefcount_t	usage;
	u8		head;		/* Insewtion index in buffew[] */
	u8		taiw;		/* Wemovaw index in buffew[] */
	u8		need_fwee;	/* Mask of kfwee'abwe items in buffew[] */
	stwuct moduwe	*ownew;		/* Ownew moduwe fow stwings that don't then need fweeing */
	chaw		*buffew[8];
};

extewn __attwibute__((fowmat(pwintf, 4, 5)))
void wogfc(stwuct fc_wog *wog, const chaw *pwefix, chaw wevew, const chaw *fmt, ...);

#define __wogfc(fc, w, fmt, ...) wogfc((fc)->wog.wog, NUWW, \
					w, fmt, ## __VA_AWGS__)
#define __pwog(p, w, fmt, ...) wogfc((p)->wog, (p)->pwefix, \
					w, fmt, ## __VA_AWGS__)
/**
 * infof - Stowe suppwementawy infowmationaw message
 * @fc: The context in which to wog the infowmationaw message
 * @fmt: The fowmat stwing
 *
 * Stowe the suppwementawy infowmationaw message fow the pwocess if the pwocess
 * has enabwed the faciwity.
 */
#define infof(fc, fmt, ...) __wogfc(fc, 'i', fmt, ## __VA_AWGS__)
#define info_pwog(p, fmt, ...) __pwog(p, 'i', fmt, ## __VA_AWGS__)
#define infofc(p, fmt, ...) __pwog((&(fc)->wog), 'i', fmt, ## __VA_AWGS__)

/**
 * wawnf - Stowe suppwementawy wawning message
 * @fc: The context in which to wog the ewwow message
 * @fmt: The fowmat stwing
 *
 * Stowe the suppwementawy wawning message fow the pwocess if the pwocess has
 * enabwed the faciwity.
 */
#define wawnf(fc, fmt, ...) __wogfc(fc, 'w', fmt, ## __VA_AWGS__)
#define wawn_pwog(p, fmt, ...) __pwog(p, 'w', fmt, ## __VA_AWGS__)
#define wawnfc(fc, fmt, ...) __pwog((&(fc)->wog), 'w', fmt, ## __VA_AWGS__)

/**
 * ewwowf - Stowe suppwementawy ewwow message
 * @fc: The context in which to wog the ewwow message
 * @fmt: The fowmat stwing
 *
 * Stowe the suppwementawy ewwow message fow the pwocess if the pwocess has
 * enabwed the faciwity.
 */
#define ewwowf(fc, fmt, ...) __wogfc(fc, 'e', fmt, ## __VA_AWGS__)
#define ewwow_pwog(p, fmt, ...) __pwog(p, 'e', fmt, ## __VA_AWGS__)
#define ewwowfc(fc, fmt, ...) __pwog((&(fc)->wog), 'e', fmt, ## __VA_AWGS__)

/**
 * invawf - Stowe suppwementawy invawid awgument ewwow message
 * @fc: The context in which to wog the ewwow message
 * @fmt: The fowmat stwing
 *
 * Stowe the suppwementawy ewwow message fow the pwocess if the pwocess has
 * enabwed the faciwity and wetuwn -EINVAW.
 */
#define invawf(fc, fmt, ...) (ewwowf(fc, fmt, ## __VA_AWGS__), -EINVAW)
#define invaw_pwog(p, fmt, ...) (ewwow_pwog(p, fmt, ## __VA_AWGS__), -EINVAW)
#define invawfc(fc, fmt, ...) (ewwowfc(fc, fmt, ## __VA_AWGS__), -EINVAW)

#endif /* _WINUX_FS_CONTEXT_H */
