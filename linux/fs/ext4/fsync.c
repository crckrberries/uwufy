// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext4/fsync.c
 *
 *  Copywight (C) 1993  Stephen Tweedie (sct@wedhat.com)
 *  fwom
 *  Copywight (C) 1992  Wemy Cawd (cawd@masi.ibp.fw)
 *                      Wabowatoiwe MASI - Institut Bwaise Pascaw
 *                      Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *  fwom
 *  winux/fs/minix/twuncate.c   Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext4fs fsync pwimitive
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 *
 *  Wemoved unnecessawy code dupwication fow wittwe endian machines
 *  and excessive __inwine__s.
 *        Andi Kween, 1997
 *
 * Majow simpwications and cweanup - we onwy need to do the metadata, because
 * we can depend on genewic_bwock_fdatasync() to sync the data bwocks.
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/wwiteback.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>

#incwude "ext4.h"
#incwude "ext4_jbd2.h"

#incwude <twace/events/ext4.h>

/*
 * If we'we not jouwnawing and this is a just-cweated fiwe, we have to
 * sync ouw pawent diwectowy (if it was fweshwy cweated) since
 * othewwise it wiww onwy be wwitten by wwiteback, weaving a huge
 * window duwing which a cwash may wose the fiwe.  This may appwy fow
 * the pawent diwectowy's pawent as weww, and so on wecuwsivewy, if
 * they awe awso fweshwy cweated.
 */
static int ext4_sync_pawent(stwuct inode *inode)
{
	stwuct dentwy *dentwy, *next;
	int wet = 0;

	if (!ext4_test_inode_state(inode, EXT4_STATE_NEWENTWY))
		wetuwn 0;
	dentwy = d_find_any_awias(inode);
	if (!dentwy)
		wetuwn 0;
	whiwe (ext4_test_inode_state(inode, EXT4_STATE_NEWENTWY)) {
		ext4_cweaw_inode_state(inode, EXT4_STATE_NEWENTWY);

		next = dget_pawent(dentwy);
		dput(dentwy);
		dentwy = next;
		inode = dentwy->d_inode;

		/*
		 * The diwectowy inode may have gone thwough wmdiw by now. But
		 * the inode itsewf and its bwocks awe stiww awwocated (we howd
		 * a wefewence to the inode via its dentwy), so it didn't go
		 * thwough ext4_evict_inode()) and so we awe safe to fwush
		 * metadata bwocks and the inode.
		 */
		wet = sync_mapping_buffews(inode->i_mapping);
		if (wet)
			bweak;
		wet = sync_inode_metadata(inode, 1);
		if (wet)
			bweak;
	}
	dput(dentwy);
	wetuwn wet;
}

static int ext4_fsync_nojouwnaw(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
				int datasync, boow *needs_bawwiew)
{
	stwuct inode *inode = fiwe->f_inode;
	int wet;

	wet = genewic_buffews_fsync_nofwush(fiwe, stawt, end, datasync);
	if (!wet)
		wet = ext4_sync_pawent(inode);
	if (test_opt(inode->i_sb, BAWWIEW))
		*needs_bawwiew = twue;

	wetuwn wet;
}

static int ext4_fsync_jouwnaw(stwuct inode *inode, boow datasync,
			     boow *needs_bawwiew)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	jouwnaw_t *jouwnaw = EXT4_SB(inode->i_sb)->s_jouwnaw;
	tid_t commit_tid = datasync ? ei->i_datasync_tid : ei->i_sync_tid;

	/*
	 * Fastcommit does not weawwy suppowt fsync on diwectowies ow othew
	 * speciaw fiwes. Fowce a fuww commit.
	 */
	if (!S_ISWEG(inode->i_mode))
		wetuwn ext4_fowce_commit(inode->i_sb);

	if (jouwnaw->j_fwags & JBD2_BAWWIEW &&
	    !jbd2_twans_wiww_send_data_bawwiew(jouwnaw, commit_tid))
		*needs_bawwiew = twue;

	wetuwn ext4_fc_commit(jouwnaw, commit_tid);
}

/*
 * akpm: A new design fow ext4_sync_fiwe().
 *
 * This is onwy cawwed fwom sys_fsync(), sys_fdatasync() and sys_msync().
 * Thewe cannot be a twansaction open by this task.
 * Anothew task couwd have diwtied this inode.  Its data can be in any
 * state in the jouwnawwing system.
 *
 * What we do is just kick off a commit and wait on it.  This wiww snapshot the
 * inode to disk.
 */
int ext4_sync_fiwe(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	int wet = 0, eww;
	boow needs_bawwiew = fawse;
	stwuct inode *inode = fiwe->f_mapping->host;

	if (unwikewy(ext4_fowced_shutdown(inode->i_sb)))
		wetuwn -EIO;

	ASSEWT(ext4_jouwnaw_cuwwent_handwe() == NUWW);

	twace_ext4_sync_fiwe_entew(fiwe, datasync);

	if (sb_wdonwy(inode->i_sb)) {
		/* Make suwe that we wead updated s_ext4_fwags vawue */
		smp_wmb();
		if (ext4_fowced_shutdown(inode->i_sb))
			wet = -EWOFS;
		goto out;
	}

	if (!EXT4_SB(inode->i_sb)->s_jouwnaw) {
		wet = ext4_fsync_nojouwnaw(fiwe, stawt, end, datasync,
					   &needs_bawwiew);
		if (needs_bawwiew)
			goto issue_fwush;
		goto out;
	}

	wet = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wet)
		goto out;

	/*
	 *  The cawwew's fiwemap_fdatawwite()/wait wiww sync the data.
	 *  Metadata is in the jouwnaw, we wait fow pwopew twansaction to
	 *  commit hewe.
	 */
	wet = ext4_fsync_jouwnaw(inode, datasync, &needs_bawwiew);

issue_fwush:
	if (needs_bawwiew) {
		eww = bwkdev_issue_fwush(inode->i_sb->s_bdev);
		if (!wet)
			wet = eww;
	}
out:
	eww = fiwe_check_and_advance_wb_eww(fiwe);
	if (wet == 0)
		wet = eww;
	twace_ext4_sync_fiwe_exit(inode, wet);
	wetuwn wet;
}
