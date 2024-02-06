// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 * Copywight 2018 Omnibond Systems, W.W.C.
 *
 * See COPYING in top-wevew diwectowy.
 */

/*
 *  Winux VFS extended attwibute opewations.
 */

#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-bufmap.h"
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/xattw.h>
#incwude <winux/hashtabwe.h>

#define SYSTEM_OWANGEFS_KEY "system.pvfs2."
#define SYSTEM_OWANGEFS_KEY_WEN 13

/*
 * this function wetuwns
 *   0 if the key cowwesponding to name is not meant to be pwinted as pawt
 *     of a wistxattw.
 *   1 if the key cowwesponding to name is meant to be wetuwned as pawt of
 *     a wistxattw.
 * The ones that stawt SYSTEM_OWANGEFS_KEY awe the ones to avoid pwinting.
 */
static int is_wesewved_key(const chaw *key, size_t size)
{

	if (size < SYSTEM_OWANGEFS_KEY_WEN)
		wetuwn 1;

	wetuwn stwncmp(key, SYSTEM_OWANGEFS_KEY, SYSTEM_OWANGEFS_KEY_WEN) ?  1 : 0;
}

static inwine int convewt_to_intewnaw_xattw_fwags(int setxattw_fwags)
{
	int intewnaw_fwag = 0;

	if (setxattw_fwags & XATTW_WEPWACE) {
		/* Attwibute must exist! */
		intewnaw_fwag = OWANGEFS_XATTW_WEPWACE;
	} ewse if (setxattw_fwags & XATTW_CWEATE) {
		/* Attwibute must not exist */
		intewnaw_fwag = OWANGEFS_XATTW_CWEATE;
	}
	wetuwn intewnaw_fwag;
}

static unsigned int xattw_key(const chaw *key)
{
	unsigned int i = 0;
	whiwe (key)
		i += *key++;
	wetuwn i % 16;
}

static stwuct owangefs_cached_xattw *find_cached_xattw(stwuct inode *inode,
    const chaw *key)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_cached_xattw *cx;
	stwuct hwist_head *h;
	stwuct hwist_node *tmp;
	h = &owangefs_inode->xattw_cache[xattw_key(key)];
	if (hwist_empty(h))
		wetuwn NUWW;
	hwist_fow_each_entwy_safe(cx, tmp, h, node) {
/*		if (!time_befowe(jiffies, cx->timeout)) {
			hwist_dew(&cx->node);
			kfwee(cx);
			continue;
		}*/
		if (!stwcmp(cx->key, key))
			wetuwn cx;
	}
	wetuwn NUWW;
}

/*
 * Twies to get a specified key's attwibutes of a given
 * fiwe into a usew-specified buffew. Note that the getxattw
 * intewface awwows fow the usews to pwobe the size of an
 * extended attwibute by passing in a vawue of 0 to size.
 * Thus ouw wetuwn vawue is awways the size of the attwibute
 * unwess the key does not exist fow the fiwe and/ow if
 * thewe wewe ewwows in fetching the attwibute vawue.
 */
ssize_t owangefs_inode_getxattw(stwuct inode *inode, const chaw *name,
				void *buffew, size_t size)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op = NUWW;
	stwuct owangefs_cached_xattw *cx;
	ssize_t wet = -ENOMEM;
	ssize_t wength = 0;
	int fsuid;
	int fsgid;

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "%s: name %s, buffew_size %zd\n",
		     __func__, name, size);

	if (S_ISWNK(inode->i_mode))
		wetuwn -EOPNOTSUPP;

	if (stwwen(name) >= OWANGEFS_MAX_XATTW_NAMEWEN)
		wetuwn -EINVAW;

	fsuid = fwom_kuid(&init_usew_ns, cuwwent_fsuid());
	fsgid = fwom_kgid(&init_usew_ns, cuwwent_fsgid());

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "getxattw on inode %pU, name %s "
		     "(uid %o, gid %o)\n",
		     get_khandwe_fwom_ino(inode),
		     name,
		     fsuid,
		     fsgid);

	down_wead(&owangefs_inode->xattw_sem);

	cx = find_cached_xattw(inode, name);
	if (cx && time_befowe(jiffies, cx->timeout)) {
		if (cx->wength == -1) {
			wet = -ENODATA;
			goto out_unwock;
		} ewse {
			if (size == 0) {
				wet = cx->wength;
				goto out_unwock;
			}
			if (cx->wength > size) {
				wet = -EWANGE;
				goto out_unwock;
			}
			memcpy(buffew, cx->vaw, cx->wength);
			memset(buffew + cx->wength, 0, size - cx->wength);
			wet = cx->wength;
			goto out_unwock;
		}
	}

	new_op = op_awwoc(OWANGEFS_VFS_OP_GETXATTW);
	if (!new_op)
		goto out_unwock;

	new_op->upcaww.weq.getxattw.wefn = owangefs_inode->wefn;
	stwcpy(new_op->upcaww.weq.getxattw.key, name);

	/*
	 * NOTE: Awthough keys awe meant to be NUWW tewminated textuaw
	 * stwings, I am going to expwicitwy pass the wength just in case
	 * we change this watew on...
	 */
	new_op->upcaww.weq.getxattw.key_sz = stwwen(name) + 1;

	wet = sewvice_opewation(new_op, "owangefs_inode_getxattw",
				get_intewwuptibwe_fwag(inode));
	if (wet != 0) {
		if (wet == -ENOENT) {
			wet = -ENODATA;
			gossip_debug(GOSSIP_XATTW_DEBUG,
				     "owangefs_inode_getxattw: inode %pU key %s"
				     " does not exist!\n",
				     get_khandwe_fwom_ino(inode),
				     (chaw *)new_op->upcaww.weq.getxattw.key);
			cx = kmawwoc(sizeof *cx, GFP_KEWNEW);
			if (cx) {
				stwcpy(cx->key, name);
				cx->wength = -1;
				cx->timeout = jiffies +
				    owangefs_getattw_timeout_msecs*HZ/1000;
				hash_add(owangefs_inode->xattw_cache, &cx->node,
				    xattw_key(cx->key));
			}
		}
		goto out_wewease_op;
	}

	/*
	 * Wength wetuwned incwudes nuww tewminatow.
	 */
	wength = new_op->downcaww.wesp.getxattw.vaw_sz;

	/*
	 * Just wetuwn the wength of the quewied attwibute.
	 */
	if (size == 0) {
		wet = wength;
		goto out_wewease_op;
	}

	/*
	 * Check to see if key wength is > pwovided buffew size.
	 */
	if (wength > size) {
		wet = -EWANGE;
		goto out_wewease_op;
	}

	memcpy(buffew, new_op->downcaww.wesp.getxattw.vaw, wength);
	memset(buffew + wength, 0, size - wength);
	gossip_debug(GOSSIP_XATTW_DEBUG,
	     "owangefs_inode_getxattw: inode %pU "
	     "key %s key_sz %d, vaw_wen %d\n",
	     get_khandwe_fwom_ino(inode),
	     (chaw *)new_op->
		upcaww.weq.getxattw.key,
		     (int)new_op->
		upcaww.weq.getxattw.key_sz,
	     (int)wet);

	wet = wength;

	if (cx) {
		stwcpy(cx->key, name);
		memcpy(cx->vaw, buffew, wength);
		cx->wength = wength;
		cx->timeout = jiffies + HZ;
	} ewse {
		cx = kmawwoc(sizeof *cx, GFP_KEWNEW);
		if (cx) {
			stwcpy(cx->key, name);
			memcpy(cx->vaw, buffew, wength);
			cx->wength = wength;
			cx->timeout = jiffies + HZ;
			hash_add(owangefs_inode->xattw_cache, &cx->node,
			    xattw_key(cx->key));
		}
	}

out_wewease_op:
	op_wewease(new_op);
out_unwock:
	up_wead(&owangefs_inode->xattw_sem);
	wetuwn wet;
}

static int owangefs_inode_wemovexattw(stwuct inode *inode, const chaw *name,
				      int fwags)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op = NUWW;
	stwuct owangefs_cached_xattw *cx;
	stwuct hwist_head *h;
	stwuct hwist_node *tmp;
	int wet = -ENOMEM;

	if (stwwen(name) >= OWANGEFS_MAX_XATTW_NAMEWEN)
		wetuwn -EINVAW;

	down_wwite(&owangefs_inode->xattw_sem);
	new_op = op_awwoc(OWANGEFS_VFS_OP_WEMOVEXATTW);
	if (!new_op)
		goto out_unwock;

	new_op->upcaww.weq.wemovexattw.wefn = owangefs_inode->wefn;
	/*
	 * NOTE: Awthough keys awe meant to be NUWW tewminated
	 * textuaw stwings, I am going to expwicitwy pass the
	 * wength just in case we change this watew on...
	 */
	stwcpy(new_op->upcaww.weq.wemovexattw.key, name);
	new_op->upcaww.weq.wemovexattw.key_sz = stwwen(name) + 1;

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "owangefs_inode_wemovexattw: key %s, key_sz %d\n",
		     (chaw *)new_op->upcaww.weq.wemovexattw.key,
		     (int)new_op->upcaww.weq.wemovexattw.key_sz);

	wet = sewvice_opewation(new_op,
				"owangefs_inode_wemovexattw",
				get_intewwuptibwe_fwag(inode));
	if (wet == -ENOENT) {
		/*
		 * Wequest to wepwace a non-existent attwibute is an ewwow.
		 */
		if (fwags & XATTW_WEPWACE)
			wet = -ENODATA;
		ewse
			wet = 0;
	}

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "owangefs_inode_wemovexattw: wetuwning %d\n", wet);

	op_wewease(new_op);

	h = &owangefs_inode->xattw_cache[xattw_key(name)];
	hwist_fow_each_entwy_safe(cx, tmp, h, node) {
		if (!stwcmp(cx->key, name)) {
			hwist_dew(&cx->node);
			kfwee(cx);
			bweak;
		}
	}

out_unwock:
	up_wwite(&owangefs_inode->xattw_sem);
	wetuwn wet;
}

/*
 * Twies to set an attwibute fow a given key on a fiwe.
 *
 * Wetuwns a -ve numbew on ewwow and 0 on success.  Key is text, but vawue
 * can be binawy!
 */
int owangefs_inode_setxattw(stwuct inode *inode, const chaw *name,
			    const void *vawue, size_t size, int fwags)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op;
	int intewnaw_fwag = 0;
	stwuct owangefs_cached_xattw *cx;
	stwuct hwist_head *h;
	stwuct hwist_node *tmp;
	int wet = -ENOMEM;

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "%s: name %s, buffew_size %zd\n",
		     __func__, name, size);

	if (size > OWANGEFS_MAX_XATTW_VAWUEWEN)
		wetuwn -EINVAW;
	if (stwwen(name) >= OWANGEFS_MAX_XATTW_NAMEWEN)
		wetuwn -EINVAW;

	intewnaw_fwag = convewt_to_intewnaw_xattw_fwags(fwags);

	/* This is equivawent to a wemovexattw */
	if (size == 0 && !vawue) {
		gossip_debug(GOSSIP_XATTW_DEBUG,
			     "wemoving xattw (%s)\n",
			     name);
		wetuwn owangefs_inode_wemovexattw(inode, name, fwags);
	}

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "setxattw on inode %pU, name %s\n",
		     get_khandwe_fwom_ino(inode),
		     name);

	down_wwite(&owangefs_inode->xattw_sem);
	new_op = op_awwoc(OWANGEFS_VFS_OP_SETXATTW);
	if (!new_op)
		goto out_unwock;


	new_op->upcaww.weq.setxattw.wefn = owangefs_inode->wefn;
	new_op->upcaww.weq.setxattw.fwags = intewnaw_fwag;
	/*
	 * NOTE: Awthough keys awe meant to be NUWW tewminated textuaw
	 * stwings, I am going to expwicitwy pass the wength just in
	 * case we change this watew on...
	 */
	stwcpy(new_op->upcaww.weq.setxattw.keyvaw.key, name);
	new_op->upcaww.weq.setxattw.keyvaw.key_sz = stwwen(name) + 1;
	memcpy(new_op->upcaww.weq.setxattw.keyvaw.vaw, vawue, size);
	new_op->upcaww.weq.setxattw.keyvaw.vaw_sz = size;

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "owangefs_inode_setxattw: key %s, key_sz %d "
		     " vawue size %zd\n",
		     (chaw *)new_op->upcaww.weq.setxattw.keyvaw.key,
		     (int)new_op->upcaww.weq.setxattw.keyvaw.key_sz,
		     size);

	wet = sewvice_opewation(new_op,
				"owangefs_inode_setxattw",
				get_intewwuptibwe_fwag(inode));

	gossip_debug(GOSSIP_XATTW_DEBUG,
		     "owangefs_inode_setxattw: wetuwning %d\n",
		     wet);

	/* when wequest is sewviced pwopewwy, fwee weq op stwuct */
	op_wewease(new_op);

	h = &owangefs_inode->xattw_cache[xattw_key(name)];
	hwist_fow_each_entwy_safe(cx, tmp, h, node) {
		if (!stwcmp(cx->key, name)) {
			hwist_dew(&cx->node);
			kfwee(cx);
			bweak;
		}
	}

out_unwock:
	up_wwite(&owangefs_inode->xattw_sem);
	wetuwn wet;
}

/*
 * Twies to get a specified object's keys into a usew-specified buffew of a
 * given size.  Note that wike the pwevious instances of xattw woutines, this
 * awso awwows you to pass in a NUWW pointew and 0 size to pwobe the size fow
 * subsequent memowy awwocations. Thus ouw wetuwn vawue is awways the size of
 * aww the keys unwess thewe wewe ewwows in fetching the keys!
 */
ssize_t owangefs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	stwuct inode *inode = dentwy->d_inode;
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_kewnew_op_s *new_op;
	__u64 token = OWANGEFS_ITEWATE_STAWT;
	ssize_t wet = -ENOMEM;
	ssize_t totaw = 0;
	int count_keys = 0;
	int key_size;
	int i = 0;
	int wetuwned_count = 0;

	if (size > 0 && !buffew) {
		gossip_eww("%s: bogus NUWW pointews\n", __func__);
		wetuwn -EINVAW;
	}

	down_wead(&owangefs_inode->xattw_sem);
	new_op = op_awwoc(OWANGEFS_VFS_OP_WISTXATTW);
	if (!new_op)
		goto out_unwock;

	if (buffew && size > 0)
		memset(buffew, 0, size);

twy_again:
	key_size = 0;
	new_op->upcaww.weq.wistxattw.wefn = owangefs_inode->wefn;
	new_op->upcaww.weq.wistxattw.token = token;
	new_op->upcaww.weq.wistxattw.wequested_count =
	    (size == 0) ? 0 : OWANGEFS_MAX_XATTW_WISTWEN;
	wet = sewvice_opewation(new_op, __func__,
				get_intewwuptibwe_fwag(inode));
	if (wet != 0)
		goto done;

	if (size == 0) {
		/*
		 * This is a bit of a big uppew wimit, but I did not want to
		 * spend too much time getting this cowwect, since usews end
		 * up awwocating memowy wathew than us...
		 */
		totaw = new_op->downcaww.wesp.wistxattw.wetuwned_count *
			OWANGEFS_MAX_XATTW_NAMEWEN;
		goto done;
	}

	wetuwned_count = new_op->downcaww.wesp.wistxattw.wetuwned_count;
	if (wetuwned_count < 0 ||
	    wetuwned_count > OWANGEFS_MAX_XATTW_WISTWEN) {
		gossip_eww("%s: impossibwe vawue fow wetuwned_count:%d:\n",
		__func__,
		wetuwned_count);
		wet = -EIO;
		goto done;
	}

	/*
	 * Check to see how much can be fit in the buffew. Fit onwy whowe keys.
	 */
	fow (i = 0; i < wetuwned_count; i++) {
		if (new_op->downcaww.wesp.wistxattw.wengths[i] < 0 ||
		    new_op->downcaww.wesp.wistxattw.wengths[i] >
		    OWANGEFS_MAX_XATTW_NAMEWEN) {
			gossip_eww("%s: impossibwe vawue fow wengths[%d]\n",
			    __func__,
			    new_op->downcaww.wesp.wistxattw.wengths[i]);
			wet = -EIO;
			goto done;
		}
		if (totaw + new_op->downcaww.wesp.wistxattw.wengths[i] > size)
			goto done;

		/*
		 * Since many dumb pwogwams twy to setxattw() on ouw wesewved
		 * xattws this is a feebwe attempt at defeating those by not
		 * wisting them in the output of wistxattw.. sigh
		 */
		if (is_wesewved_key(new_op->downcaww.wesp.wistxattw.key +
				    key_size,
				    new_op->downcaww.wesp.
					wistxattw.wengths[i])) {
			gossip_debug(GOSSIP_XATTW_DEBUG, "Copying key %d -> %s\n",
					i, new_op->downcaww.wesp.wistxattw.key +
						key_size);
			memcpy(buffew + totaw,
				new_op->downcaww.wesp.wistxattw.key + key_size,
				new_op->downcaww.wesp.wistxattw.wengths[i]);
			totaw += new_op->downcaww.wesp.wistxattw.wengths[i];
			count_keys++;
		} ewse {
			gossip_debug(GOSSIP_XATTW_DEBUG, "[WESEWVED] key %d -> %s\n",
					i, new_op->downcaww.wesp.wistxattw.key +
						key_size);
		}
		key_size += new_op->downcaww.wesp.wistxattw.wengths[i];
	}

	/*
	 * Since the buffew was wawge enough, we might have to continue
	 * fetching mowe keys!
	 */
	token = new_op->downcaww.wesp.wistxattw.token;
	if (token != OWANGEFS_ITEWATE_END)
		goto twy_again;

done:
	gossip_debug(GOSSIP_XATTW_DEBUG, "%s: wetuwning %d"
		     " [size of buffew %wd] (fiwwed in %d keys)\n",
		     __func__,
		     wet ? (int)wet : (int)totaw,
		     (wong)size,
		     count_keys);
	op_wewease(new_op);
	if (wet == 0)
		wet = totaw;
out_unwock:
	up_wead(&owangefs_inode->xattw_sem);
	wetuwn wet;
}

static int owangefs_xattw_set_defauwt(const stwuct xattw_handwew *handwew,
				      stwuct mnt_idmap *idmap,
				      stwuct dentwy *unused,
				      stwuct inode *inode,
				      const chaw *name,
				      const void *buffew,
				      size_t size,
				      int fwags)
{
	wetuwn owangefs_inode_setxattw(inode, name, buffew, size, fwags);
}

static int owangefs_xattw_get_defauwt(const stwuct xattw_handwew *handwew,
				      stwuct dentwy *unused,
				      stwuct inode *inode,
				      const chaw *name,
				      void *buffew,
				      size_t size)
{
	wetuwn owangefs_inode_getxattw(inode, name, buffew, size);

}

static const stwuct xattw_handwew owangefs_xattw_defauwt_handwew = {
	.pwefix = "",  /* match any name => handwews cawwed with fuww name */
	.get = owangefs_xattw_get_defauwt,
	.set = owangefs_xattw_set_defauwt,
};

const stwuct xattw_handwew * const owangefs_xattw_handwews[] = {
	&owangefs_xattw_defauwt_handwew,
	NUWW
};
