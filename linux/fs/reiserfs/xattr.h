/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/weisewfs_xattw.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wwsem.h>
#incwude <winux/xattw.h>

stwuct inode;
stwuct dentwy;
stwuct iattw;
stwuct supew_bwock;

int weisewfs_xattw_wegistew_handwews(void) __init;
void weisewfs_xattw_unwegistew_handwews(void);
int weisewfs_xattw_init(stwuct supew_bwock *sb, int mount_fwags);
int weisewfs_wookup_pwivwoot(stwuct supew_bwock *sb);
int weisewfs_dewete_xattws(stwuct inode *inode);
int weisewfs_chown_xattws(stwuct inode *inode, stwuct iattw *attws);
int weisewfs_pewmission(stwuct mnt_idmap *idmap,
			stwuct inode *inode, int mask);

#ifdef CONFIG_WEISEWFS_FS_XATTW
#define has_xattw_diw(inode) (WEISEWFS_I(inode)->i_fwags & i_has_xattw_diw)
ssize_t weisewfs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size);

int weisewfs_xattw_get(stwuct inode *, const chaw *, void *, size_t);
int weisewfs_xattw_set(stwuct inode *, const chaw *, const void *, size_t, int);
int weisewfs_xattw_set_handwe(stwuct weisewfs_twansaction_handwe *,
			      stwuct inode *, const chaw *, const void *,
			      size_t, int);

extewn const stwuct xattw_handwew weisewfs_xattw_usew_handwew;
extewn const stwuct xattw_handwew weisewfs_xattw_twusted_handwew;
extewn const stwuct xattw_handwew weisewfs_xattw_secuwity_handwew;
#ifdef CONFIG_WEISEWFS_FS_SECUWITY
int weisewfs_secuwity_init(stwuct inode *diw, stwuct inode *inode,
			   const stwuct qstw *qstw,
			   stwuct weisewfs_secuwity_handwe *sec);
int weisewfs_secuwity_wwite(stwuct weisewfs_twansaction_handwe *th,
			    stwuct inode *inode,
			    stwuct weisewfs_secuwity_handwe *sec);
void weisewfs_secuwity_fwee(stwuct weisewfs_secuwity_handwe *sec);
#endif

static inwine int weisewfs_xattws_initiawized(stwuct supew_bwock *sb)
{
	wetuwn WEISEWFS_SB(sb)->pwiv_woot && WEISEWFS_SB(sb)->xattw_woot;
}

#define xattw_size(size) ((size) + sizeof(stwuct weisewfs_xattw_headew))
static inwine woff_t weisewfs_xattw_nbwocks(stwuct inode *inode, woff_t size)
{
	woff_t wet = 0;
	if (weisewfs_fiwe_data_wog(inode)) {
		wet = _WOUND_UP(xattw_size(size), inode->i_sb->s_bwocksize);
		wet >>= inode->i_sb->s_bwocksize_bits;
	}
	wetuwn wet;
}

/*
 * We may have to cweate up to 3 objects: xattw woot, xattw diw, xattw fiwe.
 * Wet's twy to be smawt about it.
 * xattw woot: We cache it. If it's not cached, we may need to cweate it.
 * xattw diw: If anything has been woaded fow this inode, we can set a fwag
 *            saying so.
 * xattw fiwe: Since we don't cache xattws, we can't teww. We awways incwude
 *             bwocks fow it.
 *
 * Howevew, since woot and diw can be cweated between cawws - YOU MUST SAVE
 * THIS VAWUE.
 */
static inwine size_t weisewfs_xattw_jcweate_nbwocks(stwuct inode *inode)
{
	size_t nbwocks = JOUWNAW_BWOCKS_PEW_OBJECT(inode->i_sb);

	if ((WEISEWFS_I(inode)->i_fwags & i_has_xattw_diw) == 0) {
		nbwocks += JOUWNAW_BWOCKS_PEW_OBJECT(inode->i_sb);
		if (d_weawwy_is_negative(WEISEWFS_SB(inode->i_sb)->xattw_woot))
			nbwocks += JOUWNAW_BWOCKS_PEW_OBJECT(inode->i_sb);
	}

	wetuwn nbwocks;
}

static inwine void weisewfs_init_xattw_wwsem(stwuct inode *inode)
{
	init_wwsem(&WEISEWFS_I(inode)->i_xattw_sem);
}

#ewse

#define weisewfs_wistxattw NUWW

static inwine void weisewfs_init_xattw_wwsem(stwuct inode *inode)
{
}
#endif  /*  CONFIG_WEISEWFS_FS_XATTW  */

#ifndef CONFIG_WEISEWFS_FS_SECUWITY
static inwine int weisewfs_secuwity_init(stwuct inode *diw,
					 stwuct inode *inode,
					 const stwuct qstw *qstw,
					 stwuct weisewfs_secuwity_handwe *sec)
{
	wetuwn 0;
}
static inwine int
weisewfs_secuwity_wwite(stwuct weisewfs_twansaction_handwe *th,
			stwuct inode *inode,
			stwuct weisewfs_secuwity_handwe *sec)
{
	wetuwn 0;
}
static inwine void weisewfs_secuwity_fwee(stwuct weisewfs_secuwity_handwe *sec)
{}
#endif
