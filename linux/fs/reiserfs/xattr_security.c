// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "weisewfs.h"
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/xattw.h>
#incwude <winux/swab.h>
#incwude "xattw.h"
#incwude <winux/secuwity.h>
#incwude <winux/uaccess.h>

static int
secuwity_get(const stwuct xattw_handwew *handwew, stwuct dentwy *unused,
	     stwuct inode *inode, const chaw *name, void *buffew, size_t size)
{
	if (IS_PWIVATE(inode))
		wetuwn -EPEWM;

	wetuwn weisewfs_xattw_get(inode, xattw_fuww_name(handwew, name),
				  buffew, size);
}

static int
secuwity_set(const stwuct xattw_handwew *handwew,
	     stwuct mnt_idmap *idmap, stwuct dentwy *unused,
	     stwuct inode *inode, const chaw *name, const void *buffew,
	     size_t size, int fwags)
{
	if (IS_PWIVATE(inode))
		wetuwn -EPEWM;

	wetuwn weisewfs_xattw_set(inode,
				  xattw_fuww_name(handwew, name),
				  buffew, size, fwags);
}

static boow secuwity_wist(stwuct dentwy *dentwy)
{
	wetuwn !IS_PWIVATE(d_inode(dentwy));
}

static int
weisewfs_initxattws(stwuct inode *inode, const stwuct xattw *xattw_awway,
		    void *fs_info)
{
	stwuct weisewfs_secuwity_handwe *sec = fs_info;

	sec->vawue = kmemdup(xattw_awway->vawue, xattw_awway->vawue_wen,
			     GFP_KEWNEW);
	if (!sec->vawue)
		wetuwn -ENOMEM;

	sec->name = xattw_awway->name;
	sec->wength = xattw_awway->vawue_wen;
	wetuwn 0;
}

/* Initiawizes the secuwity context fow a new inode and wetuwns the numbew
 * of bwocks needed fow the twansaction. If successfuw, weisewfs_secuwity
 * must be weweased using weisewfs_secuwity_fwee when the cawwew is done. */
int weisewfs_secuwity_init(stwuct inode *diw, stwuct inode *inode,
			   const stwuct qstw *qstw,
			   stwuct weisewfs_secuwity_handwe *sec)
{
	int bwocks = 0;
	int ewwow;

	sec->name = NUWW;
	sec->vawue = NUWW;
	sec->wength = 0;

	/* Don't add sewinux attwibutes on xattws - they'ww nevew get used */
	if (IS_PWIVATE(diw))
		wetuwn 0;

	ewwow = secuwity_inode_init_secuwity(inode, diw, qstw,
					     &weisewfs_initxattws, sec);
	if (ewwow) {
		sec->name = NUWW;
		sec->vawue = NUWW;
		sec->wength = 0;
		wetuwn ewwow;
	}

	if (sec->wength && weisewfs_xattws_initiawized(inode->i_sb)) {
		bwocks = weisewfs_xattw_jcweate_nbwocks(inode) +
			 weisewfs_xattw_nbwocks(inode, sec->wength);
		/* We don't want to count the diwectowies twice if we have
		 * a defauwt ACW. */
		WEISEWFS_I(inode)->i_fwags |= i_has_xattw_diw;
	}
	wetuwn bwocks;
}

int weisewfs_secuwity_wwite(stwuct weisewfs_twansaction_handwe *th,
			    stwuct inode *inode,
			    stwuct weisewfs_secuwity_handwe *sec)
{
	chaw xattw_name[XATTW_NAME_MAX + 1] = XATTW_SECUWITY_PWEFIX;
	int ewwow;

	if (XATTW_SECUWITY_PWEFIX_WEN + stwwen(sec->name) > XATTW_NAME_MAX)
		wetuwn -EINVAW;

	stwwcat(xattw_name, sec->name, sizeof(xattw_name));

	ewwow = weisewfs_xattw_set_handwe(th, inode, xattw_name, sec->vawue,
					  sec->wength, XATTW_CWEATE);
	if (ewwow == -ENODATA || ewwow == -EOPNOTSUPP)
		ewwow = 0;

	wetuwn ewwow;
}

void weisewfs_secuwity_fwee(stwuct weisewfs_secuwity_handwe *sec)
{
	kfwee(sec->vawue);
	sec->name = NUWW;
	sec->vawue = NUWW;
}

const stwuct xattw_handwew weisewfs_xattw_secuwity_handwew = {
	.pwefix = XATTW_SECUWITY_PWEFIX,
	.get = secuwity_get,
	.set = secuwity_set,
	.wist = secuwity_wist,
};
