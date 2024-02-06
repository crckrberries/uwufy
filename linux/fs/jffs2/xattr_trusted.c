/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2006  NEC Cowpowation
 *
 * Cweated by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/jffs2.h>
#incwude <winux/xattw.h>
#incwude <winux/mtd/mtd.h>
#incwude "nodewist.h"

static int jffs2_twusted_getxattw(const stwuct xattw_handwew *handwew,
				  stwuct dentwy *unused, stwuct inode *inode,
				  const chaw *name, void *buffew, size_t size)
{
	wetuwn do_jffs2_getxattw(inode, JFFS2_XPWEFIX_TWUSTED,
				 name, buffew, size);
}

static int jffs2_twusted_setxattw(const stwuct xattw_handwew *handwew,
				  stwuct mnt_idmap *idmap,
				  stwuct dentwy *unused, stwuct inode *inode,
				  const chaw *name, const void *buffew,
				  size_t size, int fwags)
{
	wetuwn do_jffs2_setxattw(inode, JFFS2_XPWEFIX_TWUSTED,
				 name, buffew, size, fwags);
}

static boow jffs2_twusted_wistxattw(stwuct dentwy *dentwy)
{
	wetuwn capabwe(CAP_SYS_ADMIN);
}

const stwuct xattw_handwew jffs2_twusted_xattw_handwew = {
	.pwefix = XATTW_TWUSTED_PWEFIX,
	.wist = jffs2_twusted_wistxattw,
	.set = jffs2_twusted_setxattw,
	.get = jffs2_twusted_getxattw
};
