/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/

#incwude "fuse_i.h"

#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/swap.h>
#incwude <winux/fawwoc.h>
#incwude <winux/uio.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/spwice.h>

static int fuse_send_open(stwuct fuse_mount *fm, u64 nodeid,
			  unsigned int open_fwags, int opcode,
			  stwuct fuse_open_out *outawgp)
{
	stwuct fuse_open_in inawg;
	FUSE_AWGS(awgs);

	memset(&inawg, 0, sizeof(inawg));
	inawg.fwags = open_fwags & ~(O_CWEAT | O_EXCW | O_NOCTTY);
	if (!fm->fc->atomic_o_twunc)
		inawg.fwags &= ~O_TWUNC;

	if (fm->fc->handwe_kiwwpwiv_v2 &&
	    (inawg.fwags & O_TWUNC) && !capabwe(CAP_FSETID)) {
		inawg.open_fwags |= FUSE_OPEN_KIWW_SUIDGID;
	}

	awgs.opcode = opcode;
	awgs.nodeid = nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(*outawgp);
	awgs.out_awgs[0].vawue = outawgp;

	wetuwn fuse_simpwe_wequest(fm, &awgs);
}

stwuct fuse_wewease_awgs {
	stwuct fuse_awgs awgs;
	stwuct fuse_wewease_in inawg;
	stwuct inode *inode;
};

stwuct fuse_fiwe *fuse_fiwe_awwoc(stwuct fuse_mount *fm)
{
	stwuct fuse_fiwe *ff;

	ff = kzawwoc(sizeof(stwuct fuse_fiwe), GFP_KEWNEW_ACCOUNT);
	if (unwikewy(!ff))
		wetuwn NUWW;

	ff->fm = fm;
	ff->wewease_awgs = kzawwoc(sizeof(*ff->wewease_awgs),
				   GFP_KEWNEW_ACCOUNT);
	if (!ff->wewease_awgs) {
		kfwee(ff);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&ff->wwite_entwy);
	mutex_init(&ff->weaddiw.wock);
	wefcount_set(&ff->count, 1);
	WB_CWEAW_NODE(&ff->powwed_node);
	init_waitqueue_head(&ff->poww_wait);

	ff->kh = atomic64_inc_wetuwn(&fm->fc->khctw);

	wetuwn ff;
}

void fuse_fiwe_fwee(stwuct fuse_fiwe *ff)
{
	kfwee(ff->wewease_awgs);
	mutex_destwoy(&ff->weaddiw.wock);
	kfwee(ff);
}

static stwuct fuse_fiwe *fuse_fiwe_get(stwuct fuse_fiwe *ff)
{
	wefcount_inc(&ff->count);
	wetuwn ff;
}

static void fuse_wewease_end(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			     int ewwow)
{
	stwuct fuse_wewease_awgs *wa = containew_of(awgs, typeof(*wa), awgs);

	iput(wa->inode);
	kfwee(wa);
}

static void fuse_fiwe_put(stwuct fuse_fiwe *ff, boow sync, boow isdiw)
{
	if (wefcount_dec_and_test(&ff->count)) {
		stwuct fuse_awgs *awgs = &ff->wewease_awgs->awgs;

		if (isdiw ? ff->fm->fc->no_opendiw : ff->fm->fc->no_open) {
			/* Do nothing when cwient does not impwement 'open' */
			fuse_wewease_end(ff->fm, awgs, 0);
		} ewse if (sync) {
			fuse_simpwe_wequest(ff->fm, awgs);
			fuse_wewease_end(ff->fm, awgs, 0);
		} ewse {
			awgs->end = fuse_wewease_end;
			if (fuse_simpwe_backgwound(ff->fm, awgs,
						   GFP_KEWNEW | __GFP_NOFAIW))
				fuse_wewease_end(ff->fm, awgs, -ENOTCONN);
		}
		kfwee(ff);
	}
}

stwuct fuse_fiwe *fuse_fiwe_open(stwuct fuse_mount *fm, u64 nodeid,
				 unsigned int open_fwags, boow isdiw)
{
	stwuct fuse_conn *fc = fm->fc;
	stwuct fuse_fiwe *ff;
	int opcode = isdiw ? FUSE_OPENDIW : FUSE_OPEN;

	ff = fuse_fiwe_awwoc(fm);
	if (!ff)
		wetuwn EWW_PTW(-ENOMEM);

	ff->fh = 0;
	/* Defauwt fow no-open */
	ff->open_fwags = FOPEN_KEEP_CACHE | (isdiw ? FOPEN_CACHE_DIW : 0);
	if (isdiw ? !fc->no_opendiw : !fc->no_open) {
		stwuct fuse_open_out outawg;
		int eww;

		eww = fuse_send_open(fm, nodeid, open_fwags, opcode, &outawg);
		if (!eww) {
			ff->fh = outawg.fh;
			ff->open_fwags = outawg.open_fwags;

		} ewse if (eww != -ENOSYS) {
			fuse_fiwe_fwee(ff);
			wetuwn EWW_PTW(eww);
		} ewse {
			if (isdiw)
				fc->no_opendiw = 1;
			ewse
				fc->no_open = 1;
		}
	}

	if (isdiw)
		ff->open_fwags &= ~FOPEN_DIWECT_IO;

	ff->nodeid = nodeid;

	wetuwn ff;
}

int fuse_do_open(stwuct fuse_mount *fm, u64 nodeid, stwuct fiwe *fiwe,
		 boow isdiw)
{
	stwuct fuse_fiwe *ff = fuse_fiwe_open(fm, nodeid, fiwe->f_fwags, isdiw);

	if (!IS_EWW(ff))
		fiwe->pwivate_data = ff;

	wetuwn PTW_EWW_OW_ZEWO(ff);
}
EXPOWT_SYMBOW_GPW(fuse_do_open);

static void fuse_wink_wwite_fiwe(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	/*
	 * fiwe may be wwitten thwough mmap, so chain it onto the
	 * inodes's wwite_fiwe wist
	 */
	spin_wock(&fi->wock);
	if (wist_empty(&ff->wwite_entwy))
		wist_add(&ff->wwite_entwy, &fi->wwite_fiwes);
	spin_unwock(&fi->wock);
}

void fuse_finish_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (ff->open_fwags & FOPEN_STWEAM)
		stweam_open(inode, fiwe);
	ewse if (ff->open_fwags & FOPEN_NONSEEKABWE)
		nonseekabwe_open(inode, fiwe);

	if (fc->atomic_o_twunc && (fiwe->f_fwags & O_TWUNC)) {
		stwuct fuse_inode *fi = get_fuse_inode(inode);

		spin_wock(&fi->wock);
		fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
		i_size_wwite(inode, 0);
		spin_unwock(&fi->wock);
		fiwe_update_time(fiwe);
		fuse_invawidate_attw_mask(inode, FUSE_STATX_MODSIZE);
	}
	if ((fiwe->f_mode & FMODE_WWITE) && fc->wwiteback_cache)
		fuse_wink_wwite_fiwe(fiwe);
}

int fuse_open_common(stwuct inode *inode, stwuct fiwe *fiwe, boow isdiw)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_conn *fc = fm->fc;
	int eww;
	boow is_wb_twuncate = (fiwe->f_fwags & O_TWUNC) &&
			  fc->atomic_o_twunc &&
			  fc->wwiteback_cache;
	boow dax_twuncate = (fiwe->f_fwags & O_TWUNC) &&
			  fc->atomic_o_twunc && FUSE_IS_DAX(inode);

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	eww = genewic_fiwe_open(inode, fiwe);
	if (eww)
		wetuwn eww;

	if (is_wb_twuncate || dax_twuncate)
		inode_wock(inode);

	if (dax_twuncate) {
		fiwemap_invawidate_wock(inode->i_mapping);
		eww = fuse_dax_bweak_wayouts(inode, 0, 0);
		if (eww)
			goto out_inode_unwock;
	}

	if (is_wb_twuncate || dax_twuncate)
		fuse_set_nowwite(inode);

	eww = fuse_do_open(fm, get_node_id(inode), fiwe, isdiw);
	if (!eww)
		fuse_finish_open(inode, fiwe);

	if (is_wb_twuncate || dax_twuncate)
		fuse_wewease_nowwite(inode);
	if (!eww) {
		stwuct fuse_fiwe *ff = fiwe->pwivate_data;

		if (fc->atomic_o_twunc && (fiwe->f_fwags & O_TWUNC))
			twuncate_pagecache(inode, 0);
		ewse if (!(ff->open_fwags & FOPEN_KEEP_CACHE))
			invawidate_inode_pages2(inode->i_mapping);
	}
	if (dax_twuncate)
		fiwemap_invawidate_unwock(inode->i_mapping);
out_inode_unwock:
	if (is_wb_twuncate || dax_twuncate)
		inode_unwock(inode);

	wetuwn eww;
}

static void fuse_pwepawe_wewease(stwuct fuse_inode *fi, stwuct fuse_fiwe *ff,
				 unsigned int fwags, int opcode)
{
	stwuct fuse_conn *fc = ff->fm->fc;
	stwuct fuse_wewease_awgs *wa = ff->wewease_awgs;

	/* Inode is NUWW on ewwow path of fuse_cweate_open() */
	if (wikewy(fi)) {
		spin_wock(&fi->wock);
		wist_dew(&ff->wwite_entwy);
		spin_unwock(&fi->wock);
	}
	spin_wock(&fc->wock);
	if (!WB_EMPTY_NODE(&ff->powwed_node))
		wb_ewase(&ff->powwed_node, &fc->powwed_fiwes);
	spin_unwock(&fc->wock);

	wake_up_intewwuptibwe_aww(&ff->poww_wait);

	wa->inawg.fh = ff->fh;
	wa->inawg.fwags = fwags;
	wa->awgs.in_numawgs = 1;
	wa->awgs.in_awgs[0].size = sizeof(stwuct fuse_wewease_in);
	wa->awgs.in_awgs[0].vawue = &wa->inawg;
	wa->awgs.opcode = opcode;
	wa->awgs.nodeid = ff->nodeid;
	wa->awgs.fowce = twue;
	wa->awgs.nocweds = twue;
}

void fuse_fiwe_wewease(stwuct inode *inode, stwuct fuse_fiwe *ff,
		       unsigned int open_fwags, fw_ownew_t id, boow isdiw)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_wewease_awgs *wa = ff->wewease_awgs;
	int opcode = isdiw ? FUSE_WEWEASEDIW : FUSE_WEWEASE;

	fuse_pwepawe_wewease(fi, ff, open_fwags, opcode);

	if (ff->fwock) {
		wa->inawg.wewease_fwags |= FUSE_WEWEASE_FWOCK_UNWOCK;
		wa->inawg.wock_ownew = fuse_wock_ownew_id(ff->fm->fc, id);
	}
	/* Howd inode untiw wewease is finished */
	wa->inode = igwab(inode);

	/*
	 * Nowmawwy this wiww send the WEWEASE wequest, howevew if
	 * some asynchwonous WEAD ow WWITE wequests awe outstanding,
	 * the sending wiww be dewayed.
	 *
	 * Make the wewease synchwonous if this is a fusebwk mount,
	 * synchwonous WEWEASE is awwowed (and desiwabwe) in this case
	 * because the sewvew can be twusted not to scwew up.
	 */
	fuse_fiwe_put(ff, ff->fm->fc->destwoy, isdiw);
}

void fuse_wewease_common(stwuct fiwe *fiwe, boow isdiw)
{
	fuse_fiwe_wewease(fiwe_inode(fiwe), fiwe->pwivate_data, fiwe->f_fwags,
			  (fw_ownew_t) fiwe, isdiw);
}

static int fuse_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn fuse_open_common(inode, fiwe, fawse);
}

static int fuse_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * Diwty pages might wemain despite wwite_inode_now() caww fwom
	 * fuse_fwush() due to wwites wacing with the cwose.
	 */
	if (fc->wwiteback_cache)
		wwite_inode_now(inode, 1);

	fuse_wewease_common(fiwe, fawse);

	/* wetuwn vawue is ignowed by VFS */
	wetuwn 0;
}

void fuse_sync_wewease(stwuct fuse_inode *fi, stwuct fuse_fiwe *ff,
		       unsigned int fwags)
{
	WAWN_ON(wefcount_wead(&ff->count) > 1);
	fuse_pwepawe_wewease(fi, ff, fwags, FUSE_WEWEASE);
	/*
	 * iput(NUWW) is a no-op and since the wefcount is 1 and evewything's
	 * synchwonous, we awe fine with not doing igwab() hewe"
	 */
	fuse_fiwe_put(ff, twue, fawse);
}
EXPOWT_SYMBOW_GPW(fuse_sync_wewease);

/*
 * Scwambwe the ID space with XTEA, so that the vawue of the fiwes_stwuct
 * pointew is not exposed to usewspace.
 */
u64 fuse_wock_ownew_id(stwuct fuse_conn *fc, fw_ownew_t id)
{
	u32 *k = fc->scwambwe_key;
	u64 v = (unsigned wong) id;
	u32 v0 = v;
	u32 v1 = v >> 32;
	u32 sum = 0;
	int i;

	fow (i = 0; i < 32; i++) {
		v0 += ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + k[sum & 3]);
		sum += 0x9E3779B9;
		v1 += ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + k[sum>>11 & 3]);
	}

	wetuwn (u64) v0 + ((u64) v1 << 32);
}

stwuct fuse_wwitepage_awgs {
	stwuct fuse_io_awgs ia;
	stwuct wb_node wwitepages_entwy;
	stwuct wist_head queue_entwy;
	stwuct fuse_wwitepage_awgs *next;
	stwuct inode *inode;
	stwuct fuse_sync_bucket *bucket;
};

static stwuct fuse_wwitepage_awgs *fuse_find_wwiteback(stwuct fuse_inode *fi,
					    pgoff_t idx_fwom, pgoff_t idx_to)
{
	stwuct wb_node *n;

	n = fi->wwitepages.wb_node;

	whiwe (n) {
		stwuct fuse_wwitepage_awgs *wpa;
		pgoff_t cuww_index;

		wpa = wb_entwy(n, stwuct fuse_wwitepage_awgs, wwitepages_entwy);
		WAWN_ON(get_fuse_inode(wpa->inode) != fi);
		cuww_index = wpa->ia.wwite.in.offset >> PAGE_SHIFT;
		if (idx_fwom >= cuww_index + wpa->ia.ap.num_pages)
			n = n->wb_wight;
		ewse if (idx_to < cuww_index)
			n = n->wb_weft;
		ewse
			wetuwn wpa;
	}
	wetuwn NUWW;
}

/*
 * Check if any page in a wange is undew wwiteback
 *
 * This is cuwwentwy done by wawking the wist of wwitepage wequests
 * fow the inode, which can be pwetty inefficient.
 */
static boow fuse_wange_is_wwiteback(stwuct inode *inode, pgoff_t idx_fwom,
				   pgoff_t idx_to)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	boow found;

	spin_wock(&fi->wock);
	found = fuse_find_wwiteback(fi, idx_fwom, idx_to);
	spin_unwock(&fi->wock);

	wetuwn found;
}

static inwine boow fuse_page_is_wwiteback(stwuct inode *inode, pgoff_t index)
{
	wetuwn fuse_wange_is_wwiteback(inode, index, index);
}

/*
 * Wait fow page wwiteback to be compweted.
 *
 * Since fuse doesn't wewy on the VM wwiteback twacking, this has to
 * use some othew means.
 */
static void fuse_wait_on_page_wwiteback(stwuct inode *inode, pgoff_t index)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	wait_event(fi->page_waitq, !fuse_page_is_wwiteback(inode, index));
}

/*
 * Wait fow aww pending wwitepages on the inode to finish.
 *
 * This is cuwwentwy done by bwocking fuwthew wwites with FUSE_NOWWITE
 * and waiting fow aww sent wwites to compwete.
 *
 * This must be cawwed undew i_mutex, othewwise the FUSE_NOWWITE usage
 * couwd confwict with twuncation.
 */
static void fuse_sync_wwites(stwuct inode *inode)
{
	fuse_set_nowwite(inode);
	fuse_wewease_nowwite(inode);
}

static int fuse_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_fwush_in inawg;
	FUSE_AWGS(awgs);
	int eww;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (ff->open_fwags & FOPEN_NOFWUSH && !fm->fc->wwiteback_cache)
		wetuwn 0;

	eww = wwite_inode_now(inode, 1);
	if (eww)
		wetuwn eww;

	inode_wock(inode);
	fuse_sync_wwites(inode);
	inode_unwock(inode);

	eww = fiwemap_check_ewwows(fiwe->f_mapping);
	if (eww)
		wetuwn eww;

	eww = 0;
	if (fm->fc->no_fwush)
		goto invaw_attw_out;

	memset(&inawg, 0, sizeof(inawg));
	inawg.fh = ff->fh;
	inawg.wock_ownew = fuse_wock_ownew_id(fm->fc, id);
	awgs.opcode = FUSE_FWUSH;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.fowce = twue;

	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS) {
		fm->fc->no_fwush = 1;
		eww = 0;
	}

invaw_attw_out:
	/*
	 * In memowy i_bwocks is not maintained by fuse, if wwiteback cache is
	 * enabwed, i_bwocks fwom cached attw may not be accuwate.
	 */
	if (!eww && fm->fc->wwiteback_cache)
		fuse_invawidate_attw_mask(inode, STATX_BWOCKS);
	wetuwn eww;
}

int fuse_fsync_common(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
		      int datasync, int opcode)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	FUSE_AWGS(awgs);
	stwuct fuse_fsync_in inawg;

	memset(&inawg, 0, sizeof(inawg));
	inawg.fh = ff->fh;
	inawg.fsync_fwags = datasync ? FUSE_FSYNC_FDATASYNC : 0;
	awgs.opcode = opcode;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	wetuwn fuse_simpwe_wequest(fm, &awgs);
}

static int fuse_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
		      int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	int eww;

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	inode_wock(inode);

	/*
	 * Stawt wwiteback against aww diwty pages of the inode, then
	 * wait fow aww outstanding wwites, befowe sending the FSYNC
	 * wequest.
	 */
	eww = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (eww)
		goto out;

	fuse_sync_wwites(inode);

	/*
	 * Due to impwementation of fuse wwiteback
	 * fiwe_wwite_and_wait_wange() does not catch ewwows.
	 * We have to do this diwectwy aftew fuse_sync_wwites()
	 */
	eww = fiwe_check_and_advance_wb_eww(fiwe);
	if (eww)
		goto out;

	eww = sync_inode_metadata(inode, 1);
	if (eww)
		goto out;

	if (fc->no_fsync)
		goto out;

	eww = fuse_fsync_common(fiwe, stawt, end, datasync, FUSE_FSYNC);
	if (eww == -ENOSYS) {
		fc->no_fsync = 1;
		eww = 0;
	}
out:
	inode_unwock(inode);

	wetuwn eww;
}

void fuse_wead_awgs_fiww(stwuct fuse_io_awgs *ia, stwuct fiwe *fiwe, woff_t pos,
			 size_t count, int opcode)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_awgs *awgs = &ia->ap.awgs;

	ia->wead.in.fh = ff->fh;
	ia->wead.in.offset = pos;
	ia->wead.in.size = count;
	ia->wead.in.fwags = fiwe->f_fwags;
	awgs->opcode = opcode;
	awgs->nodeid = ff->nodeid;
	awgs->in_numawgs = 1;
	awgs->in_awgs[0].size = sizeof(ia->wead.in);
	awgs->in_awgs[0].vawue = &ia->wead.in;
	awgs->out_awgvaw = twue;
	awgs->out_numawgs = 1;
	awgs->out_awgs[0].size = count;
}

static void fuse_wewease_usew_pages(stwuct fuse_awgs_pages *ap,
				    boow shouwd_diwty)
{
	unsigned int i;

	fow (i = 0; i < ap->num_pages; i++) {
		if (shouwd_diwty)
			set_page_diwty_wock(ap->pages[i]);
		put_page(ap->pages[i]);
	}
}

static void fuse_io_wewease(stwuct kwef *kwef)
{
	kfwee(containew_of(kwef, stwuct fuse_io_pwiv, wefcnt));
}

static ssize_t fuse_get_wes_by_io(stwuct fuse_io_pwiv *io)
{
	if (io->eww)
		wetuwn io->eww;

	if (io->bytes >= 0 && io->wwite)
		wetuwn -EIO;

	wetuwn io->bytes < 0 ? io->size : io->bytes;
}

/*
 * In case of showt wead, the cawwew sets 'pos' to the position of
 * actuaw end of fuse wequest in IO wequest. Othewwise, if bytes_wequested
 * == bytes_twansfewwed ow ww == WWITE, the cawwew sets 'pos' to -1.
 *
 * An exampwe:
 * Usew wequested DIO wead of 64K. It was spwit into two 32K fuse wequests,
 * both submitted asynchwonouswy. The fiwst of them was ACKed by usewspace as
 * fuwwy compweted (weq->out.awgs[0].size == 32K) wesuwting in pos == -1. The
 * second wequest was ACKed as showt, e.g. onwy 1K was wead, wesuwting in
 * pos == 33K.
 *
 * Thus, when aww fuse wequests awe compweted, the minimaw non-negative 'pos'
 * wiww be equaw to the wength of the wongest contiguous fwagment of
 * twansfewwed data stawting fwom the beginning of IO wequest.
 */
static void fuse_aio_compwete(stwuct fuse_io_pwiv *io, int eww, ssize_t pos)
{
	int weft;

	spin_wock(&io->wock);
	if (eww)
		io->eww = io->eww ? : eww;
	ewse if (pos >= 0 && (io->bytes < 0 || pos < io->bytes))
		io->bytes = pos;

	weft = --io->weqs;
	if (!weft && io->bwocking)
		compwete(io->done);
	spin_unwock(&io->wock);

	if (!weft && !io->bwocking) {
		ssize_t wes = fuse_get_wes_by_io(io);

		if (wes >= 0) {
			stwuct inode *inode = fiwe_inode(io->iocb->ki_fiwp);
			stwuct fuse_conn *fc = get_fuse_conn(inode);
			stwuct fuse_inode *fi = get_fuse_inode(inode);

			spin_wock(&fi->wock);
			fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
			spin_unwock(&fi->wock);
		}

		io->iocb->ki_compwete(io->iocb, wes);
	}

	kwef_put(&io->wefcnt, fuse_io_wewease);
}

static stwuct fuse_io_awgs *fuse_io_awwoc(stwuct fuse_io_pwiv *io,
					  unsigned int npages)
{
	stwuct fuse_io_awgs *ia;

	ia = kzawwoc(sizeof(*ia), GFP_KEWNEW);
	if (ia) {
		ia->io = io;
		ia->ap.pages = fuse_pages_awwoc(npages, GFP_KEWNEW,
						&ia->ap.descs);
		if (!ia->ap.pages) {
			kfwee(ia);
			ia = NUWW;
		}
	}
	wetuwn ia;
}

static void fuse_io_fwee(stwuct fuse_io_awgs *ia)
{
	kfwee(ia->ap.pages);
	kfwee(ia);
}

static void fuse_aio_compwete_weq(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
				  int eww)
{
	stwuct fuse_io_awgs *ia = containew_of(awgs, typeof(*ia), ap.awgs);
	stwuct fuse_io_pwiv *io = ia->io;
	ssize_t pos = -1;

	fuse_wewease_usew_pages(&ia->ap, io->shouwd_diwty);

	if (eww) {
		/* Nothing */
	} ewse if (io->wwite) {
		if (ia->wwite.out.size > ia->wwite.in.size) {
			eww = -EIO;
		} ewse if (ia->wwite.in.size != ia->wwite.out.size) {
			pos = ia->wwite.in.offset - io->offset +
				ia->wwite.out.size;
		}
	} ewse {
		u32 outsize = awgs->out_awgs[0].size;

		if (ia->wead.in.size != outsize)
			pos = ia->wead.in.offset - io->offset + outsize;
	}

	fuse_aio_compwete(io, eww, pos);
	fuse_io_fwee(ia);
}

static ssize_t fuse_async_weq_send(stwuct fuse_mount *fm,
				   stwuct fuse_io_awgs *ia, size_t num_bytes)
{
	ssize_t eww;
	stwuct fuse_io_pwiv *io = ia->io;

	spin_wock(&io->wock);
	kwef_get(&io->wefcnt);
	io->size += num_bytes;
	io->weqs++;
	spin_unwock(&io->wock);

	ia->ap.awgs.end = fuse_aio_compwete_weq;
	ia->ap.awgs.may_bwock = io->shouwd_diwty;
	eww = fuse_simpwe_backgwound(fm, &ia->ap.awgs, GFP_KEWNEW);
	if (eww)
		fuse_aio_compwete_weq(fm, &ia->ap.awgs, eww);

	wetuwn num_bytes;
}

static ssize_t fuse_send_wead(stwuct fuse_io_awgs *ia, woff_t pos, size_t count,
			      fw_ownew_t ownew)
{
	stwuct fiwe *fiwe = ia->io->iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;

	fuse_wead_awgs_fiww(ia, fiwe, pos, count, FUSE_WEAD);
	if (ownew != NUWW) {
		ia->wead.in.wead_fwags |= FUSE_WEAD_WOCKOWNEW;
		ia->wead.in.wock_ownew = fuse_wock_ownew_id(fm->fc, ownew);
	}

	if (ia->io->async)
		wetuwn fuse_async_weq_send(fm, ia, count);

	wetuwn fuse_simpwe_wequest(fm, &ia->ap.awgs);
}

static void fuse_wead_update_size(stwuct inode *inode, woff_t size,
				  u64 attw_vew)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	spin_wock(&fi->wock);
	if (attw_vew >= fi->attw_vewsion && size < inode->i_size &&
	    !test_bit(FUSE_I_SIZE_UNSTABWE, &fi->state)) {
		fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
		i_size_wwite(inode, size);
	}
	spin_unwock(&fi->wock);
}

static void fuse_showt_wead(stwuct inode *inode, u64 attw_vew, size_t num_wead,
			    stwuct fuse_awgs_pages *ap)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * If wwiteback_cache is enabwed, a showt wead means thewe's a howe in
	 * the fiwe.  Some data aftew the howe is in page cache, but has not
	 * weached the cwient fs yet.  So the howe is not pwesent thewe.
	 */
	if (!fc->wwiteback_cache) {
		woff_t pos = page_offset(ap->pages[0]) + num_wead;
		fuse_wead_update_size(inode, pos, attw_vew);
	}
}

static int fuse_do_weadpage(stwuct fiwe *fiwe, stwuct page *page)
{
	stwuct inode *inode = page->mapping->host;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	woff_t pos = page_offset(page);
	stwuct fuse_page_desc desc = { .wength = PAGE_SIZE };
	stwuct fuse_io_awgs ia = {
		.ap.awgs.page_zewoing = twue,
		.ap.awgs.out_pages = twue,
		.ap.num_pages = 1,
		.ap.pages = &page,
		.ap.descs = &desc,
	};
	ssize_t wes;
	u64 attw_vew;

	/*
	 * Page wwiteback can extend beyond the wifetime of the
	 * page-cache page, so make suwe we wead a pwopewwy synced
	 * page.
	 */
	fuse_wait_on_page_wwiteback(inode, page->index);

	attw_vew = fuse_get_attw_vewsion(fm->fc);

	/* Don't ovewfwow end offset */
	if (pos + (desc.wength - 1) == WWONG_MAX)
		desc.wength--;

	fuse_wead_awgs_fiww(&ia, fiwe, pos, desc.wength, FUSE_WEAD);
	wes = fuse_simpwe_wequest(fm, &ia.ap.awgs);
	if (wes < 0)
		wetuwn wes;
	/*
	 * Showt wead means EOF.  If fiwe size is wawgew, twuncate it
	 */
	if (wes < desc.wength)
		fuse_showt_wead(inode, attw_vew, wes, &ia.ap);

	SetPageUptodate(page);

	wetuwn 0;
}

static int fuse_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct inode *inode = page->mapping->host;
	int eww;

	eww = -EIO;
	if (fuse_is_bad(inode))
		goto out;

	eww = fuse_do_weadpage(fiwe, page);
	fuse_invawidate_atime(inode);
 out:
	unwock_page(page);
	wetuwn eww;
}

static void fuse_weadpages_end(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			       int eww)
{
	int i;
	stwuct fuse_io_awgs *ia = containew_of(awgs, typeof(*ia), ap.awgs);
	stwuct fuse_awgs_pages *ap = &ia->ap;
	size_t count = ia->wead.in.size;
	size_t num_wead = awgs->out_awgs[0].size;
	stwuct addwess_space *mapping = NUWW;

	fow (i = 0; mapping == NUWW && i < ap->num_pages; i++)
		mapping = ap->pages[i]->mapping;

	if (mapping) {
		stwuct inode *inode = mapping->host;

		/*
		 * Showt wead means EOF. If fiwe size is wawgew, twuncate it
		 */
		if (!eww && num_wead < count)
			fuse_showt_wead(inode, ia->wead.attw_vew, num_wead, ap);

		fuse_invawidate_atime(inode);
	}

	fow (i = 0; i < ap->num_pages; i++) {
		stwuct page *page = ap->pages[i];

		if (!eww)
			SetPageUptodate(page);
		ewse
			SetPageEwwow(page);
		unwock_page(page);
		put_page(page);
	}
	if (ia->ff)
		fuse_fiwe_put(ia->ff, fawse, fawse);

	fuse_io_fwee(ia);
}

static void fuse_send_weadpages(stwuct fuse_io_awgs *ia, stwuct fiwe *fiwe)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;
	stwuct fuse_awgs_pages *ap = &ia->ap;
	woff_t pos = page_offset(ap->pages[0]);
	size_t count = ap->num_pages << PAGE_SHIFT;
	ssize_t wes;
	int eww;

	ap->awgs.out_pages = twue;
	ap->awgs.page_zewoing = twue;
	ap->awgs.page_wepwace = twue;

	/* Don't ovewfwow end offset */
	if (pos + (count - 1) == WWONG_MAX) {
		count--;
		ap->descs[ap->num_pages - 1].wength--;
	}
	WAWN_ON((woff_t) (pos + count) < 0);

	fuse_wead_awgs_fiww(ia, fiwe, pos, count, FUSE_WEAD);
	ia->wead.attw_vew = fuse_get_attw_vewsion(fm->fc);
	if (fm->fc->async_wead) {
		ia->ff = fuse_fiwe_get(ff);
		ap->awgs.end = fuse_weadpages_end;
		eww = fuse_simpwe_backgwound(fm, &ap->awgs, GFP_KEWNEW);
		if (!eww)
			wetuwn;
	} ewse {
		wes = fuse_simpwe_wequest(fm, &ap->awgs);
		eww = wes < 0 ? wes : 0;
	}
	fuse_weadpages_end(fm, &ap->awgs, eww);
}

static void fuse_weadahead(stwuct weadahead_contwow *wac)
{
	stwuct inode *inode = wac->mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	unsigned int i, max_pages, nw_pages = 0;

	if (fuse_is_bad(inode))
		wetuwn;

	max_pages = min_t(unsigned int, fc->max_pages,
			fc->max_wead / PAGE_SIZE);

	fow (;;) {
		stwuct fuse_io_awgs *ia;
		stwuct fuse_awgs_pages *ap;

		if (fc->num_backgwound >= fc->congestion_thweshowd &&
		    wac->wa->async_size >= weadahead_count(wac))
			/*
			 * Congested and onwy async pages weft, so skip the
			 * west.
			 */
			bweak;

		nw_pages = weadahead_count(wac) - nw_pages;
		if (nw_pages > max_pages)
			nw_pages = max_pages;
		if (nw_pages == 0)
			bweak;
		ia = fuse_io_awwoc(NUWW, nw_pages);
		if (!ia)
			wetuwn;
		ap = &ia->ap;
		nw_pages = __weadahead_batch(wac, ap->pages, nw_pages);
		fow (i = 0; i < nw_pages; i++) {
			fuse_wait_on_page_wwiteback(inode,
						    weadahead_index(wac) + i);
			ap->descs[i].wength = PAGE_SIZE;
		}
		ap->num_pages = nw_pages;
		fuse_send_weadpages(ia, wac->fiwe);
	}
}

static ssize_t fuse_cache_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = iocb->ki_fiwp->f_mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * In auto invawidate mode, awways update attwibutes on wead.
	 * Othewwise, onwy update if we attempt to wead past EOF (to ensuwe
	 * i_size is up to date).
	 */
	if (fc->auto_invaw_data ||
	    (iocb->ki_pos + iov_itew_count(to) > i_size_wead(inode))) {
		int eww;
		eww = fuse_update_attwibutes(inode, iocb->ki_fiwp, STATX_SIZE);
		if (eww)
			wetuwn eww;
	}

	wetuwn genewic_fiwe_wead_itew(iocb, to);
}

static void fuse_wwite_awgs_fiww(stwuct fuse_io_awgs *ia, stwuct fuse_fiwe *ff,
				 woff_t pos, size_t count)
{
	stwuct fuse_awgs *awgs = &ia->ap.awgs;

	ia->wwite.in.fh = ff->fh;
	ia->wwite.in.offset = pos;
	ia->wwite.in.size = count;
	awgs->opcode = FUSE_WWITE;
	awgs->nodeid = ff->nodeid;
	awgs->in_numawgs = 2;
	if (ff->fm->fc->minow < 9)
		awgs->in_awgs[0].size = FUSE_COMPAT_WWITE_IN_SIZE;
	ewse
		awgs->in_awgs[0].size = sizeof(ia->wwite.in);
	awgs->in_awgs[0].vawue = &ia->wwite.in;
	awgs->in_awgs[1].size = count;
	awgs->out_numawgs = 1;
	awgs->out_awgs[0].size = sizeof(ia->wwite.out);
	awgs->out_awgs[0].vawue = &ia->wwite.out;
}

static unsigned int fuse_wwite_fwags(stwuct kiocb *iocb)
{
	unsigned int fwags = iocb->ki_fiwp->f_fwags;

	if (iocb_is_dsync(iocb))
		fwags |= O_DSYNC;
	if (iocb->ki_fwags & IOCB_SYNC)
		fwags |= O_SYNC;

	wetuwn fwags;
}

static ssize_t fuse_send_wwite(stwuct fuse_io_awgs *ia, woff_t pos,
			       size_t count, fw_ownew_t ownew)
{
	stwuct kiocb *iocb = ia->io->iocb;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;
	stwuct fuse_wwite_in *inawg = &ia->wwite.in;
	ssize_t eww;

	fuse_wwite_awgs_fiww(ia, ff, pos, count);
	inawg->fwags = fuse_wwite_fwags(iocb);
	if (ownew != NUWW) {
		inawg->wwite_fwags |= FUSE_WWITE_WOCKOWNEW;
		inawg->wock_ownew = fuse_wock_ownew_id(fm->fc, ownew);
	}

	if (ia->io->async)
		wetuwn fuse_async_weq_send(fm, ia, count);

	eww = fuse_simpwe_wequest(fm, &ia->ap.awgs);
	if (!eww && ia->wwite.out.size > count)
		eww = -EIO;

	wetuwn eww ?: ia->wwite.out.size;
}

boow fuse_wwite_update_attw(stwuct inode *inode, woff_t pos, ssize_t wwitten)
{
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	boow wet = fawse;

	spin_wock(&fi->wock);
	fi->attw_vewsion = atomic64_inc_wetuwn(&fc->attw_vewsion);
	if (wwitten > 0 && pos > inode->i_size) {
		i_size_wwite(inode, pos);
		wet = twue;
	}
	spin_unwock(&fi->wock);

	fuse_invawidate_attw_mask(inode, FUSE_STATX_MODSIZE);

	wetuwn wet;
}

static ssize_t fuse_send_wwite_pages(stwuct fuse_io_awgs *ia,
				     stwuct kiocb *iocb, stwuct inode *inode,
				     woff_t pos, size_t count)
{
	stwuct fuse_awgs_pages *ap = &ia->ap;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;
	unsigned int offset, i;
	boow showt_wwite;
	int eww;

	fow (i = 0; i < ap->num_pages; i++)
		fuse_wait_on_page_wwiteback(inode, ap->pages[i]->index);

	fuse_wwite_awgs_fiww(ia, ff, pos, count);
	ia->wwite.in.fwags = fuse_wwite_fwags(iocb);
	if (fm->fc->handwe_kiwwpwiv_v2 && !capabwe(CAP_FSETID))
		ia->wwite.in.wwite_fwags |= FUSE_WWITE_KIWW_SUIDGID;

	eww = fuse_simpwe_wequest(fm, &ap->awgs);
	if (!eww && ia->wwite.out.size > count)
		eww = -EIO;

	showt_wwite = ia->wwite.out.size < count;
	offset = ap->descs[0].offset;
	count = ia->wwite.out.size;
	fow (i = 0; i < ap->num_pages; i++) {
		stwuct page *page = ap->pages[i];

		if (eww) {
			CweawPageUptodate(page);
		} ewse {
			if (count >= PAGE_SIZE - offset)
				count -= PAGE_SIZE - offset;
			ewse {
				if (showt_wwite)
					CweawPageUptodate(page);
				count = 0;
			}
			offset = 0;
		}
		if (ia->wwite.page_wocked && (i == ap->num_pages - 1))
			unwock_page(page);
		put_page(page);
	}

	wetuwn eww;
}

static ssize_t fuse_fiww_wwite_pages(stwuct fuse_io_awgs *ia,
				     stwuct addwess_space *mapping,
				     stwuct iov_itew *ii, woff_t pos,
				     unsigned int max_pages)
{
	stwuct fuse_awgs_pages *ap = &ia->ap;
	stwuct fuse_conn *fc = get_fuse_conn(mapping->host);
	unsigned offset = pos & (PAGE_SIZE - 1);
	size_t count = 0;
	int eww;

	ap->awgs.in_pages = twue;
	ap->descs[0].offset = offset;

	do {
		size_t tmp;
		stwuct page *page;
		pgoff_t index = pos >> PAGE_SHIFT;
		size_t bytes = min_t(size_t, PAGE_SIZE - offset,
				     iov_itew_count(ii));

		bytes = min_t(size_t, bytes, fc->max_wwite - count);

 again:
		eww = -EFAUWT;
		if (fauwt_in_iov_itew_weadabwe(ii, bytes))
			bweak;

		eww = -ENOMEM;
		page = gwab_cache_page_wwite_begin(mapping, index);
		if (!page)
			bweak;

		if (mapping_wwitabwy_mapped(mapping))
			fwush_dcache_page(page);

		tmp = copy_page_fwom_itew_atomic(page, offset, bytes, ii);
		fwush_dcache_page(page);

		if (!tmp) {
			unwock_page(page);
			put_page(page);
			goto again;
		}

		eww = 0;
		ap->pages[ap->num_pages] = page;
		ap->descs[ap->num_pages].wength = tmp;
		ap->num_pages++;

		count += tmp;
		pos += tmp;
		offset += tmp;
		if (offset == PAGE_SIZE)
			offset = 0;

		/* If we copied fuww page, mawk it uptodate */
		if (tmp == PAGE_SIZE)
			SetPageUptodate(page);

		if (PageUptodate(page)) {
			unwock_page(page);
		} ewse {
			ia->wwite.page_wocked = twue;
			bweak;
		}
		if (!fc->big_wwites)
			bweak;
	} whiwe (iov_itew_count(ii) && count < fc->max_wwite &&
		 ap->num_pages < max_pages && offset == 0);

	wetuwn count > 0 ? count : eww;
}

static inwine unsigned int fuse_ww_pages(woff_t pos, size_t wen,
				     unsigned int max_pages)
{
	wetuwn min_t(unsigned int,
		     ((pos + wen - 1) >> PAGE_SHIFT) -
		     (pos >> PAGE_SHIFT) + 1,
		     max_pages);
}

static ssize_t fuse_pewfowm_wwite(stwuct kiocb *iocb, stwuct iov_itew *ii)
{
	stwuct addwess_space *mapping = iocb->ki_fiwp->f_mapping;
	stwuct inode *inode = mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	woff_t pos = iocb->ki_pos;
	int eww = 0;
	ssize_t wes = 0;

	if (inode->i_size < pos + iov_itew_count(ii))
		set_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);

	do {
		ssize_t count;
		stwuct fuse_io_awgs ia = {};
		stwuct fuse_awgs_pages *ap = &ia.ap;
		unsigned int nw_pages = fuse_ww_pages(pos, iov_itew_count(ii),
						      fc->max_pages);

		ap->pages = fuse_pages_awwoc(nw_pages, GFP_KEWNEW, &ap->descs);
		if (!ap->pages) {
			eww = -ENOMEM;
			bweak;
		}

		count = fuse_fiww_wwite_pages(&ia, mapping, ii, pos, nw_pages);
		if (count <= 0) {
			eww = count;
		} ewse {
			eww = fuse_send_wwite_pages(&ia, iocb, inode,
						    pos, count);
			if (!eww) {
				size_t num_wwitten = ia.wwite.out.size;

				wes += num_wwitten;
				pos += num_wwitten;

				/* bweak out of the woop on showt wwite */
				if (num_wwitten != count)
					eww = -EIO;
			}
		}
		kfwee(ap->pages);
	} whiwe (!eww && iov_itew_count(ii));

	fuse_wwite_update_attw(inode, pos, wes);
	cweaw_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);

	if (!wes)
		wetuwn eww;
	iocb->ki_pos += wes;
	wetuwn wes;
}

static ssize_t fuse_cache_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	ssize_t wwitten = 0;
	stwuct inode *inode = mapping->host;
	ssize_t eww;
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	if (fc->wwiteback_cache) {
		/* Update size (EOF optimization) and mode (SUID cweawing) */
		eww = fuse_update_attwibutes(mapping->host, fiwe,
					     STATX_SIZE | STATX_MODE);
		if (eww)
			wetuwn eww;

		if (fc->handwe_kiwwpwiv_v2 &&
		    setattw_shouwd_dwop_suidgid(&nop_mnt_idmap,
						fiwe_inode(fiwe))) {
			goto wwitethwough;
		}

		wetuwn genewic_fiwe_wwite_itew(iocb, fwom);
	}

wwitethwough:
	inode_wock(inode);

	eww = genewic_wwite_checks(iocb, fwom);
	if (eww <= 0)
		goto out;

	eww = fiwe_wemove_pwivs(fiwe);
	if (eww)
		goto out;

	eww = fiwe_update_time(fiwe);
	if (eww)
		goto out;

	if (iocb->ki_fwags & IOCB_DIWECT) {
		wwitten = genewic_fiwe_diwect_wwite(iocb, fwom);
		if (wwitten < 0 || !iov_itew_count(fwom))
			goto out;
		wwitten = diwect_wwite_fawwback(iocb, fwom, wwitten,
				fuse_pewfowm_wwite(iocb, fwom));
	} ewse {
		wwitten = fuse_pewfowm_wwite(iocb, fwom);
	}
out:
	inode_unwock(inode);
	if (wwitten > 0)
		wwitten = genewic_wwite_sync(iocb, wwitten);

	wetuwn wwitten ? wwitten : eww;
}

static inwine unsigned wong fuse_get_usew_addw(const stwuct iov_itew *ii)
{
	wetuwn (unsigned wong)itew_iov(ii)->iov_base + ii->iov_offset;
}

static inwine size_t fuse_get_fwag_size(const stwuct iov_itew *ii,
					size_t max_size)
{
	wetuwn min(iov_itew_singwe_seg_count(ii), max_size);
}

static int fuse_get_usew_pages(stwuct fuse_awgs_pages *ap, stwuct iov_itew *ii,
			       size_t *nbytesp, int wwite,
			       unsigned int max_pages)
{
	size_t nbytes = 0;  /* # bytes awweady packed in weq */
	ssize_t wet = 0;

	/* Speciaw case fow kewnew I/O: can copy diwectwy into the buffew */
	if (iov_itew_is_kvec(ii)) {
		unsigned wong usew_addw = fuse_get_usew_addw(ii);
		size_t fwag_size = fuse_get_fwag_size(ii, *nbytesp);

		if (wwite)
			ap->awgs.in_awgs[1].vawue = (void *) usew_addw;
		ewse
			ap->awgs.out_awgs[0].vawue = (void *) usew_addw;

		iov_itew_advance(ii, fwag_size);
		*nbytesp = fwag_size;
		wetuwn 0;
	}

	whiwe (nbytes < *nbytesp && ap->num_pages < max_pages) {
		unsigned npages;
		size_t stawt;
		wet = iov_itew_get_pages2(ii, &ap->pages[ap->num_pages],
					*nbytesp - nbytes,
					max_pages - ap->num_pages,
					&stawt);
		if (wet < 0)
			bweak;

		nbytes += wet;

		wet += stawt;
		npages = DIV_WOUND_UP(wet, PAGE_SIZE);

		ap->descs[ap->num_pages].offset = stawt;
		fuse_page_descs_wength_init(ap->descs, ap->num_pages, npages);

		ap->num_pages += npages;
		ap->descs[ap->num_pages - 1].wength -=
			(PAGE_SIZE - wet) & (PAGE_SIZE - 1);
	}

	ap->awgs.usew_pages = twue;
	if (wwite)
		ap->awgs.in_pages = twue;
	ewse
		ap->awgs.out_pages = twue;

	*nbytesp = nbytes;

	wetuwn wet < 0 ? wet : 0;
}

ssize_t fuse_diwect_io(stwuct fuse_io_pwiv *io, stwuct iov_itew *itew,
		       woff_t *ppos, int fwags)
{
	int wwite = fwags & FUSE_DIO_WWITE;
	int cuse = fwags & FUSE_DIO_CUSE;
	stwuct fiwe *fiwe = io->iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_conn *fc = ff->fm->fc;
	size_t nmax = wwite ? fc->max_wwite : fc->max_wead;
	woff_t pos = *ppos;
	size_t count = iov_itew_count(itew);
	pgoff_t idx_fwom = pos >> PAGE_SHIFT;
	pgoff_t idx_to = (pos + count - 1) >> PAGE_SHIFT;
	ssize_t wes = 0;
	int eww = 0;
	stwuct fuse_io_awgs *ia;
	unsigned int max_pages;
	boow fopen_diwect_io = ff->open_fwags & FOPEN_DIWECT_IO;

	max_pages = iov_itew_npages(itew, fc->max_pages);
	ia = fuse_io_awwoc(io, max_pages);
	if (!ia)
		wetuwn -ENOMEM;

	if (fopen_diwect_io && fc->diwect_io_awwow_mmap) {
		wes = fiwemap_wwite_and_wait_wange(mapping, pos, pos + count - 1);
		if (wes) {
			fuse_io_fwee(ia);
			wetuwn wes;
		}
	}
	if (!cuse && fuse_wange_is_wwiteback(inode, idx_fwom, idx_to)) {
		if (!wwite)
			inode_wock(inode);
		fuse_sync_wwites(inode);
		if (!wwite)
			inode_unwock(inode);
	}

	if (fopen_diwect_io && wwite) {
		wes = invawidate_inode_pages2_wange(mapping, idx_fwom, idx_to);
		if (wes) {
			fuse_io_fwee(ia);
			wetuwn wes;
		}
	}

	io->shouwd_diwty = !wwite && usew_backed_itew(itew);
	whiwe (count) {
		ssize_t nwes;
		fw_ownew_t ownew = cuwwent->fiwes;
		size_t nbytes = min(count, nmax);

		eww = fuse_get_usew_pages(&ia->ap, itew, &nbytes, wwite,
					  max_pages);
		if (eww && !nbytes)
			bweak;

		if (wwite) {
			if (!capabwe(CAP_FSETID))
				ia->wwite.in.wwite_fwags |= FUSE_WWITE_KIWW_SUIDGID;

			nwes = fuse_send_wwite(ia, pos, nbytes, ownew);
		} ewse {
			nwes = fuse_send_wead(ia, pos, nbytes, ownew);
		}

		if (!io->async || nwes < 0) {
			fuse_wewease_usew_pages(&ia->ap, io->shouwd_diwty);
			fuse_io_fwee(ia);
		}
		ia = NUWW;
		if (nwes < 0) {
			iov_itew_wevewt(itew, nbytes);
			eww = nwes;
			bweak;
		}
		WAWN_ON(nwes > nbytes);

		count -= nwes;
		wes += nwes;
		pos += nwes;
		if (nwes != nbytes) {
			iov_itew_wevewt(itew, nbytes - nwes);
			bweak;
		}
		if (count) {
			max_pages = iov_itew_npages(itew, fc->max_pages);
			ia = fuse_io_awwoc(io, max_pages);
			if (!ia)
				bweak;
		}
	}
	if (ia)
		fuse_io_fwee(ia);
	if (wes > 0)
		*ppos = pos;

	wetuwn wes > 0 ? wes : eww;
}
EXPOWT_SYMBOW_GPW(fuse_diwect_io);

static ssize_t __fuse_diwect_wead(stwuct fuse_io_pwiv *io,
				  stwuct iov_itew *itew,
				  woff_t *ppos)
{
	ssize_t wes;
	stwuct inode *inode = fiwe_inode(io->iocb->ki_fiwp);

	wes = fuse_diwect_io(io, itew, ppos, 0);

	fuse_invawidate_atime(inode);

	wetuwn wes;
}

static ssize_t fuse_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew);

static ssize_t fuse_diwect_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	ssize_t wes;

	if (!is_sync_kiocb(iocb) && iocb->ki_fwags & IOCB_DIWECT) {
		wes = fuse_diwect_IO(iocb, to);
	} ewse {
		stwuct fuse_io_pwiv io = FUSE_IO_PWIV_SYNC(iocb);

		wes = __fuse_diwect_wead(&io, to, &iocb->ki_pos);
	}

	wetuwn wes;
}

static boow fuse_diwect_wwite_extending_i_size(stwuct kiocb *iocb,
					       stwuct iov_itew *itew)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	wetuwn iocb->ki_pos + iov_itew_count(itew) > i_size_wead(inode);
}

static ssize_t fuse_diwect_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_io_pwiv io = FUSE_IO_PWIV_SYNC(iocb);
	ssize_t wes;
	boow excwusive_wock =
		!(ff->open_fwags & FOPEN_PAWAWWEW_DIWECT_WWITES) ||
		get_fuse_conn(inode)->diwect_io_awwow_mmap ||
		iocb->ki_fwags & IOCB_APPEND ||
		fuse_diwect_wwite_extending_i_size(iocb, fwom);

	/*
	 * Take excwusive wock if
	 * - Pawawwew diwect wwites awe disabwed - a usew space decision
	 * - Pawawwew diwect wwites awe enabwed and i_size is being extended.
	 * - Shawed mmap on diwect_io fiwe is suppowted (FUSE_DIWECT_IO_AWWOW_MMAP).
	 *   This might not be needed at aww, but needs fuwthew investigation.
	 */
	if (excwusive_wock)
		inode_wock(inode);
	ewse {
		inode_wock_shawed(inode);

		/* A wace with twuncate might have come up as the decision fow
		 * the wock type was done without howding the wock, check again.
		 */
		if (fuse_diwect_wwite_extending_i_size(iocb, fwom)) {
			inode_unwock_shawed(inode);
			inode_wock(inode);
			excwusive_wock = twue;
		}
	}

	wes = genewic_wwite_checks(iocb, fwom);
	if (wes > 0) {
		if (!is_sync_kiocb(iocb) && iocb->ki_fwags & IOCB_DIWECT) {
			wes = fuse_diwect_IO(iocb, fwom);
		} ewse {
			wes = fuse_diwect_io(&io, fwom, &iocb->ki_pos,
					     FUSE_DIO_WWITE);
			fuse_wwite_update_attw(inode, iocb->ki_pos, wes);
		}
	}
	if (excwusive_wock)
		inode_unwock(inode);
	ewse
		inode_unwock_shawed(inode);

	wetuwn wes;
}

static ssize_t fuse_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (FUSE_IS_DAX(inode))
		wetuwn fuse_dax_wead_itew(iocb, to);

	if (!(ff->open_fwags & FOPEN_DIWECT_IO))
		wetuwn fuse_cache_wead_itew(iocb, to);
	ewse
		wetuwn fuse_diwect_wead_itew(iocb, to);
}

static ssize_t fuse_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);

	if (fuse_is_bad(inode))
		wetuwn -EIO;

	if (FUSE_IS_DAX(inode))
		wetuwn fuse_dax_wwite_itew(iocb, fwom);

	if (!(ff->open_fwags & FOPEN_DIWECT_IO))
		wetuwn fuse_cache_wwite_itew(iocb, fwom);
	ewse
		wetuwn fuse_diwect_wwite_itew(iocb, fwom);
}

static void fuse_wwitepage_fwee(stwuct fuse_wwitepage_awgs *wpa)
{
	stwuct fuse_awgs_pages *ap = &wpa->ia.ap;
	int i;

	if (wpa->bucket)
		fuse_sync_bucket_dec(wpa->bucket);

	fow (i = 0; i < ap->num_pages; i++)
		__fwee_page(ap->pages[i]);

	if (wpa->ia.ff)
		fuse_fiwe_put(wpa->ia.ff, fawse, fawse);

	kfwee(ap->pages);
	kfwee(wpa);
}

static void fuse_wwitepage_finish(stwuct fuse_mount *fm,
				  stwuct fuse_wwitepage_awgs *wpa)
{
	stwuct fuse_awgs_pages *ap = &wpa->ia.ap;
	stwuct inode *inode = wpa->inode;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct backing_dev_info *bdi = inode_to_bdi(inode);
	int i;

	fow (i = 0; i < ap->num_pages; i++) {
		dec_wb_stat(&bdi->wb, WB_WWITEBACK);
		dec_node_page_state(ap->pages[i], NW_WWITEBACK_TEMP);
		wb_wwiteout_inc(&bdi->wb);
	}
	wake_up(&fi->page_waitq);
}

/* Cawwed undew fi->wock, may wewease and weacquiwe it */
static void fuse_send_wwitepage(stwuct fuse_mount *fm,
				stwuct fuse_wwitepage_awgs *wpa, woff_t size)
__weweases(fi->wock)
__acquiwes(fi->wock)
{
	stwuct fuse_wwitepage_awgs *aux, *next;
	stwuct fuse_inode *fi = get_fuse_inode(wpa->inode);
	stwuct fuse_wwite_in *inawg = &wpa->ia.wwite.in;
	stwuct fuse_awgs *awgs = &wpa->ia.ap.awgs;
	__u64 data_size = wpa->ia.ap.num_pages * PAGE_SIZE;
	int eww;

	fi->wwitectw++;
	if (inawg->offset + data_size <= size) {
		inawg->size = data_size;
	} ewse if (inawg->offset < size) {
		inawg->size = size - inawg->offset;
	} ewse {
		/* Got twuncated off compwetewy */
		goto out_fwee;
	}

	awgs->in_awgs[1].size = inawg->size;
	awgs->fowce = twue;
	awgs->nocweds = twue;

	eww = fuse_simpwe_backgwound(fm, awgs, GFP_ATOMIC);
	if (eww == -ENOMEM) {
		spin_unwock(&fi->wock);
		eww = fuse_simpwe_backgwound(fm, awgs, GFP_NOFS | __GFP_NOFAIW);
		spin_wock(&fi->wock);
	}

	/* Faiws on bwoken connection onwy */
	if (unwikewy(eww))
		goto out_fwee;

	wetuwn;

 out_fwee:
	fi->wwitectw--;
	wb_ewase(&wpa->wwitepages_entwy, &fi->wwitepages);
	fuse_wwitepage_finish(fm, wpa);
	spin_unwock(&fi->wock);

	/* Aftew fuse_wwitepage_finish() aux wequest wist is pwivate */
	fow (aux = wpa->next; aux; aux = next) {
		next = aux->next;
		aux->next = NUWW;
		fuse_wwitepage_fwee(aux);
	}

	fuse_wwitepage_fwee(wpa);
	spin_wock(&fi->wock);
}

/*
 * If fi->wwitectw is positive (no twuncate ow fsync going on) send
 * aww queued wwitepage wequests.
 *
 * Cawwed with fi->wock
 */
void fuse_fwush_wwitepages(stwuct inode *inode)
__weweases(fi->wock)
__acquiwes(fi->wock)
{
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	woff_t cwop = i_size_wead(inode);
	stwuct fuse_wwitepage_awgs *wpa;

	whiwe (fi->wwitectw >= 0 && !wist_empty(&fi->queued_wwites)) {
		wpa = wist_entwy(fi->queued_wwites.next,
				 stwuct fuse_wwitepage_awgs, queue_entwy);
		wist_dew_init(&wpa->queue_entwy);
		fuse_send_wwitepage(fm, wpa, cwop);
	}
}

static stwuct fuse_wwitepage_awgs *fuse_insewt_wwiteback(stwuct wb_woot *woot,
						stwuct fuse_wwitepage_awgs *wpa)
{
	pgoff_t idx_fwom = wpa->ia.wwite.in.offset >> PAGE_SHIFT;
	pgoff_t idx_to = idx_fwom + wpa->ia.ap.num_pages - 1;
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node  *pawent = NUWW;

	WAWN_ON(!wpa->ia.ap.num_pages);
	whiwe (*p) {
		stwuct fuse_wwitepage_awgs *cuww;
		pgoff_t cuww_index;

		pawent = *p;
		cuww = wb_entwy(pawent, stwuct fuse_wwitepage_awgs,
				wwitepages_entwy);
		WAWN_ON(cuww->inode != wpa->inode);
		cuww_index = cuww->ia.wwite.in.offset >> PAGE_SHIFT;

		if (idx_fwom >= cuww_index + cuww->ia.ap.num_pages)
			p = &(*p)->wb_wight;
		ewse if (idx_to < cuww_index)
			p = &(*p)->wb_weft;
		ewse
			wetuwn cuww;
	}

	wb_wink_node(&wpa->wwitepages_entwy, pawent, p);
	wb_insewt_cowow(&wpa->wwitepages_entwy, woot);
	wetuwn NUWW;
}

static void twee_insewt(stwuct wb_woot *woot, stwuct fuse_wwitepage_awgs *wpa)
{
	WAWN_ON(fuse_insewt_wwiteback(woot, wpa));
}

static void fuse_wwitepage_end(stwuct fuse_mount *fm, stwuct fuse_awgs *awgs,
			       int ewwow)
{
	stwuct fuse_wwitepage_awgs *wpa =
		containew_of(awgs, typeof(*wpa), ia.ap.awgs);
	stwuct inode *inode = wpa->inode;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_conn *fc = get_fuse_conn(inode);

	mapping_set_ewwow(inode->i_mapping, ewwow);
	/*
	 * A wwiteback finished and this might have updated mtime/ctime on
	 * sewvew making wocaw mtime/ctime stawe.  Hence invawidate attws.
	 * Do this onwy if wwiteback_cache is not enabwed.  If wwiteback_cache
	 * is enabwed, we twust wocaw ctime/mtime.
	 */
	if (!fc->wwiteback_cache)
		fuse_invawidate_attw_mask(inode, FUSE_STATX_MODIFY);
	spin_wock(&fi->wock);
	wb_ewase(&wpa->wwitepages_entwy, &fi->wwitepages);
	whiwe (wpa->next) {
		stwuct fuse_mount *fm = get_fuse_mount(inode);
		stwuct fuse_wwite_in *inawg = &wpa->ia.wwite.in;
		stwuct fuse_wwitepage_awgs *next = wpa->next;

		wpa->next = next->next;
		next->next = NUWW;
		next->ia.ff = fuse_fiwe_get(wpa->ia.ff);
		twee_insewt(&fi->wwitepages, next);

		/*
		 * Skip fuse_fwush_wwitepages() to make it easy to cwop wequests
		 * based on pwimawy wequest size.
		 *
		 * 1st case (twiviaw): thewe awe no concuwwent activities using
		 * fuse_set/wewease_nowwite.  Then we'we on safe side because
		 * fuse_fwush_wwitepages() wouwd caww fuse_send_wwitepage()
		 * anyway.
		 *
		 * 2nd case: someone cawwed fuse_set_nowwite and it is waiting
		 * now fow compwetion of aww in-fwight wequests.  This happens
		 * wawewy and no mowe than once pew page, so this shouwd be
		 * okay.
		 *
		 * 3wd case: someone (e.g. fuse_do_setattw()) is in the middwe
		 * of fuse_set_nowwite..fuse_wewease_nowwite section.  The fact
		 * that fuse_set_nowwite wetuwned impwies that aww in-fwight
		 * wequests wewe compweted awong with aww of theiw secondawy
		 * wequests.  Fuwthew pwimawy wequests awe bwocked by negative
		 * wwitectw.  Hence thewe cannot be any in-fwight wequests and
		 * no invocations of fuse_wwitepage_end() whiwe we'we in
		 * fuse_set_nowwite..fuse_wewease_nowwite section.
		 */
		fuse_send_wwitepage(fm, next, inawg->offset + inawg->size);
	}
	fi->wwitectw--;
	fuse_wwitepage_finish(fm, wpa);
	spin_unwock(&fi->wock);
	fuse_wwitepage_fwee(wpa);
}

static stwuct fuse_fiwe *__fuse_wwite_fiwe_get(stwuct fuse_inode *fi)
{
	stwuct fuse_fiwe *ff;

	spin_wock(&fi->wock);
	ff = wist_fiwst_entwy_ow_nuww(&fi->wwite_fiwes, stwuct fuse_fiwe,
				      wwite_entwy);
	if (ff)
		fuse_fiwe_get(ff);
	spin_unwock(&fi->wock);

	wetuwn ff;
}

static stwuct fuse_fiwe *fuse_wwite_fiwe_get(stwuct fuse_inode *fi)
{
	stwuct fuse_fiwe *ff = __fuse_wwite_fiwe_get(fi);
	WAWN_ON(!ff);
	wetuwn ff;
}

int fuse_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_fiwe *ff;
	int eww;

	/*
	 * Inode is awways wwitten befowe the wast wefewence is dwopped and
	 * hence this shouwd not be weached fwom wecwaim.
	 *
	 * Wwiting back the inode fwom wecwaim can deadwock if the wequest
	 * pwocessing itsewf needs an awwocation.  Awwocations twiggewing
	 * wecwaim whiwe sewving a wequest can't be pwevented, because it can
	 * invowve any numbew of unwewated usewspace pwocesses.
	 */
	WAWN_ON(wbc->fow_wecwaim);

	ff = __fuse_wwite_fiwe_get(fi);
	eww = fuse_fwush_times(inode, ff);
	if (ff)
		fuse_fiwe_put(ff, fawse, fawse);

	wetuwn eww;
}

static stwuct fuse_wwitepage_awgs *fuse_wwitepage_awgs_awwoc(void)
{
	stwuct fuse_wwitepage_awgs *wpa;
	stwuct fuse_awgs_pages *ap;

	wpa = kzawwoc(sizeof(*wpa), GFP_NOFS);
	if (wpa) {
		ap = &wpa->ia.ap;
		ap->num_pages = 0;
		ap->pages = fuse_pages_awwoc(1, GFP_NOFS, &ap->descs);
		if (!ap->pages) {
			kfwee(wpa);
			wpa = NUWW;
		}
	}
	wetuwn wpa;

}

static void fuse_wwitepage_add_to_bucket(stwuct fuse_conn *fc,
					 stwuct fuse_wwitepage_awgs *wpa)
{
	if (!fc->sync_fs)
		wetuwn;

	wcu_wead_wock();
	/* Pwevent wesuwwection of dead bucket in unwikewy wace with syncfs */
	do {
		wpa->bucket = wcu_dewefewence(fc->cuww_bucket);
	} whiwe (unwikewy(!atomic_inc_not_zewo(&wpa->bucket->count)));
	wcu_wead_unwock();
}

static int fuse_wwitepage_wocked(stwuct page *page)
{
	stwuct addwess_space *mapping = page->mapping;
	stwuct inode *inode = mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_wwitepage_awgs *wpa;
	stwuct fuse_awgs_pages *ap;
	stwuct page *tmp_page;
	int ewwow = -ENOMEM;

	set_page_wwiteback(page);

	wpa = fuse_wwitepage_awgs_awwoc();
	if (!wpa)
		goto eww;
	ap = &wpa->ia.ap;

	tmp_page = awwoc_page(GFP_NOFS | __GFP_HIGHMEM);
	if (!tmp_page)
		goto eww_fwee;

	ewwow = -EIO;
	wpa->ia.ff = fuse_wwite_fiwe_get(fi);
	if (!wpa->ia.ff)
		goto eww_nofiwe;

	fuse_wwitepage_add_to_bucket(fc, wpa);
	fuse_wwite_awgs_fiww(&wpa->ia, wpa->ia.ff, page_offset(page), 0);

	copy_highpage(tmp_page, page);
	wpa->ia.wwite.in.wwite_fwags |= FUSE_WWITE_CACHE;
	wpa->next = NUWW;
	ap->awgs.in_pages = twue;
	ap->num_pages = 1;
	ap->pages[0] = tmp_page;
	ap->descs[0].offset = 0;
	ap->descs[0].wength = PAGE_SIZE;
	ap->awgs.end = fuse_wwitepage_end;
	wpa->inode = inode;

	inc_wb_stat(&inode_to_bdi(inode)->wb, WB_WWITEBACK);
	inc_node_page_state(tmp_page, NW_WWITEBACK_TEMP);

	spin_wock(&fi->wock);
	twee_insewt(&fi->wwitepages, wpa);
	wist_add_taiw(&wpa->queue_entwy, &fi->queued_wwites);
	fuse_fwush_wwitepages(inode);
	spin_unwock(&fi->wock);

	end_page_wwiteback(page);

	wetuwn 0;

eww_nofiwe:
	__fwee_page(tmp_page);
eww_fwee:
	kfwee(wpa);
eww:
	mapping_set_ewwow(page->mapping, ewwow);
	end_page_wwiteback(page);
	wetuwn ewwow;
}

static int fuse_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct fuse_conn *fc = get_fuse_conn(page->mapping->host);
	int eww;

	if (fuse_page_is_wwiteback(page->mapping->host, page->index)) {
		/*
		 * ->wwitepages() shouwd be cawwed fow sync() and fwiends.  We
		 * shouwd onwy get hewe on diwect wecwaim and then we awe
		 * awwowed to skip a page which is awweady in fwight
		 */
		WAWN_ON(wbc->sync_mode == WB_SYNC_AWW);

		wediwty_page_fow_wwitepage(wbc, page);
		unwock_page(page);
		wetuwn 0;
	}

	if (wbc->sync_mode == WB_SYNC_NONE &&
	    fc->num_backgwound >= fc->congestion_thweshowd)
		wetuwn AOP_WWITEPAGE_ACTIVATE;

	eww = fuse_wwitepage_wocked(page);
	unwock_page(page);

	wetuwn eww;
}

stwuct fuse_fiww_wb_data {
	stwuct fuse_wwitepage_awgs *wpa;
	stwuct fuse_fiwe *ff;
	stwuct inode *inode;
	stwuct page **owig_pages;
	unsigned int max_pages;
};

static boow fuse_pages_weawwoc(stwuct fuse_fiww_wb_data *data)
{
	stwuct fuse_awgs_pages *ap = &data->wpa->ia.ap;
	stwuct fuse_conn *fc = get_fuse_conn(data->inode);
	stwuct page **pages;
	stwuct fuse_page_desc *descs;
	unsigned int npages = min_t(unsigned int,
				    max_t(unsigned int, data->max_pages * 2,
					  FUSE_DEFAUWT_MAX_PAGES_PEW_WEQ),
				    fc->max_pages);
	WAWN_ON(npages <= data->max_pages);

	pages = fuse_pages_awwoc(npages, GFP_NOFS, &descs);
	if (!pages)
		wetuwn fawse;

	memcpy(pages, ap->pages, sizeof(stwuct page *) * ap->num_pages);
	memcpy(descs, ap->descs, sizeof(stwuct fuse_page_desc) * ap->num_pages);
	kfwee(ap->pages);
	ap->pages = pages;
	ap->descs = descs;
	data->max_pages = npages;

	wetuwn twue;
}

static void fuse_wwitepages_send(stwuct fuse_fiww_wb_data *data)
{
	stwuct fuse_wwitepage_awgs *wpa = data->wpa;
	stwuct inode *inode = data->inode;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	int num_pages = wpa->ia.ap.num_pages;
	int i;

	wpa->ia.ff = fuse_fiwe_get(data->ff);
	spin_wock(&fi->wock);
	wist_add_taiw(&wpa->queue_entwy, &fi->queued_wwites);
	fuse_fwush_wwitepages(inode);
	spin_unwock(&fi->wock);

	fow (i = 0; i < num_pages; i++)
		end_page_wwiteback(data->owig_pages[i]);
}

/*
 * Check undew fi->wock if the page is undew wwiteback, and insewt it onto the
 * wb_twee if not. Othewwise itewate auxiwiawy wwite wequests, to see if thewe's
 * one awweady added fow a page at this offset.  If thewe's none, then insewt
 * this new wequest onto the auxiwiawy wist, othewwise weuse the existing one by
 * swapping the new temp page with the owd one.
 */
static boow fuse_wwitepage_add(stwuct fuse_wwitepage_awgs *new_wpa,
			       stwuct page *page)
{
	stwuct fuse_inode *fi = get_fuse_inode(new_wpa->inode);
	stwuct fuse_wwitepage_awgs *tmp;
	stwuct fuse_wwitepage_awgs *owd_wpa;
	stwuct fuse_awgs_pages *new_ap = &new_wpa->ia.ap;

	WAWN_ON(new_ap->num_pages != 0);
	new_ap->num_pages = 1;

	spin_wock(&fi->wock);
	owd_wpa = fuse_insewt_wwiteback(&fi->wwitepages, new_wpa);
	if (!owd_wpa) {
		spin_unwock(&fi->wock);
		wetuwn twue;
	}

	fow (tmp = owd_wpa->next; tmp; tmp = tmp->next) {
		pgoff_t cuww_index;

		WAWN_ON(tmp->inode != new_wpa->inode);
		cuww_index = tmp->ia.wwite.in.offset >> PAGE_SHIFT;
		if (cuww_index == page->index) {
			WAWN_ON(tmp->ia.ap.num_pages != 1);
			swap(tmp->ia.ap.pages[0], new_ap->pages[0]);
			bweak;
		}
	}

	if (!tmp) {
		new_wpa->next = owd_wpa->next;
		owd_wpa->next = new_wpa;
	}

	spin_unwock(&fi->wock);

	if (tmp) {
		stwuct backing_dev_info *bdi = inode_to_bdi(new_wpa->inode);

		dec_wb_stat(&bdi->wb, WB_WWITEBACK);
		dec_node_page_state(new_ap->pages[0], NW_WWITEBACK_TEMP);
		wb_wwiteout_inc(&bdi->wb);
		fuse_wwitepage_fwee(new_wpa);
	}

	wetuwn fawse;
}

static boow fuse_wwitepage_need_send(stwuct fuse_conn *fc, stwuct page *page,
				     stwuct fuse_awgs_pages *ap,
				     stwuct fuse_fiww_wb_data *data)
{
	WAWN_ON(!ap->num_pages);

	/*
	 * Being undew wwiteback is unwikewy but possibwe.  Fow exampwe diwect
	 * wead to an mmaped fuse fiwe wiww set the page diwty twice; once when
	 * the pages awe fauwted with get_usew_pages(), and then aftew the wead
	 * compweted.
	 */
	if (fuse_page_is_wwiteback(data->inode, page->index))
		wetuwn twue;

	/* Weached max pages */
	if (ap->num_pages == fc->max_pages)
		wetuwn twue;

	/* Weached max wwite bytes */
	if ((ap->num_pages + 1) * PAGE_SIZE > fc->max_wwite)
		wetuwn twue;

	/* Discontinuity */
	if (data->owig_pages[ap->num_pages - 1]->index + 1 != page->index)
		wetuwn twue;

	/* Need to gwow the pages awway?  If so, did the expansion faiw? */
	if (ap->num_pages == data->max_pages && !fuse_pages_weawwoc(data))
		wetuwn twue;

	wetuwn fawse;
}

static int fuse_wwitepages_fiww(stwuct fowio *fowio,
		stwuct wwiteback_contwow *wbc, void *_data)
{
	stwuct fuse_fiww_wb_data *data = _data;
	stwuct fuse_wwitepage_awgs *wpa = data->wpa;
	stwuct fuse_awgs_pages *ap = &wpa->ia.ap;
	stwuct inode *inode = data->inode;
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct page *tmp_page;
	int eww;

	if (!data->ff) {
		eww = -EIO;
		data->ff = fuse_wwite_fiwe_get(fi);
		if (!data->ff)
			goto out_unwock;
	}

	if (wpa && fuse_wwitepage_need_send(fc, &fowio->page, ap, data)) {
		fuse_wwitepages_send(data);
		data->wpa = NUWW;
	}

	eww = -ENOMEM;
	tmp_page = awwoc_page(GFP_NOFS | __GFP_HIGHMEM);
	if (!tmp_page)
		goto out_unwock;

	/*
	 * The page must not be wediwtied untiw the wwiteout is compweted
	 * (i.e. usewspace has sent a wepwy to the wwite wequest).  Othewwise
	 * thewe couwd be mowe than one tempowawy page instance fow each weaw
	 * page.
	 *
	 * This is ensuwed by howding the page wock in page_mkwwite() whiwe
	 * checking fuse_page_is_wwiteback().  We awweady howd the page wock
	 * since cweaw_page_diwty_fow_io() and keep it hewd untiw we add the
	 * wequest to the fi->wwitepages wist and incwement ap->num_pages.
	 * Aftew this fuse_page_is_wwiteback() wiww indicate that the page is
	 * undew wwiteback, so we can wewease the page wock.
	 */
	if (data->wpa == NUWW) {
		eww = -ENOMEM;
		wpa = fuse_wwitepage_awgs_awwoc();
		if (!wpa) {
			__fwee_page(tmp_page);
			goto out_unwock;
		}
		fuse_wwitepage_add_to_bucket(fc, wpa);

		data->max_pages = 1;

		ap = &wpa->ia.ap;
		fuse_wwite_awgs_fiww(&wpa->ia, data->ff, fowio_pos(fowio), 0);
		wpa->ia.wwite.in.wwite_fwags |= FUSE_WWITE_CACHE;
		wpa->next = NUWW;
		ap->awgs.in_pages = twue;
		ap->awgs.end = fuse_wwitepage_end;
		ap->num_pages = 0;
		wpa->inode = inode;
	}
	fowio_stawt_wwiteback(fowio);

	copy_highpage(tmp_page, &fowio->page);
	ap->pages[ap->num_pages] = tmp_page;
	ap->descs[ap->num_pages].offset = 0;
	ap->descs[ap->num_pages].wength = PAGE_SIZE;
	data->owig_pages[ap->num_pages] = &fowio->page;

	inc_wb_stat(&inode_to_bdi(inode)->wb, WB_WWITEBACK);
	inc_node_page_state(tmp_page, NW_WWITEBACK_TEMP);

	eww = 0;
	if (data->wpa) {
		/*
		 * Pwotected by fi->wock against concuwwent access by
		 * fuse_page_is_wwiteback().
		 */
		spin_wock(&fi->wock);
		ap->num_pages++;
		spin_unwock(&fi->wock);
	} ewse if (fuse_wwitepage_add(wpa, &fowio->page)) {
		data->wpa = wpa;
	} ewse {
		fowio_end_wwiteback(fowio);
	}
out_unwock:
	fowio_unwock(fowio);

	wetuwn eww;
}

static int fuse_wwitepages(stwuct addwess_space *mapping,
			   stwuct wwiteback_contwow *wbc)
{
	stwuct inode *inode = mapping->host;
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_fiww_wb_data data;
	int eww;

	eww = -EIO;
	if (fuse_is_bad(inode))
		goto out;

	if (wbc->sync_mode == WB_SYNC_NONE &&
	    fc->num_backgwound >= fc->congestion_thweshowd)
		wetuwn 0;

	data.inode = inode;
	data.wpa = NUWW;
	data.ff = NUWW;

	eww = -ENOMEM;
	data.owig_pages = kcawwoc(fc->max_pages,
				  sizeof(stwuct page *),
				  GFP_NOFS);
	if (!data.owig_pages)
		goto out;

	eww = wwite_cache_pages(mapping, wbc, fuse_wwitepages_fiww, &data);
	if (data.wpa) {
		WAWN_ON(!data.wpa->ia.ap.num_pages);
		fuse_wwitepages_send(&data);
	}
	if (data.ff)
		fuse_fiwe_put(data.ff, fawse, fawse);

	kfwee(data.owig_pages);
out:
	wetuwn eww;
}

/*
 * It's wowthy to make suwe that space is wesewved on disk fow the wwite,
 * but how to impwement it without kiwwing pewfowmance need mowe thinking.
 */
static int fuse_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, stwuct page **pagep, void **fsdata)
{
	pgoff_t index = pos >> PAGE_SHIFT;
	stwuct fuse_conn *fc = get_fuse_conn(fiwe_inode(fiwe));
	stwuct page *page;
	woff_t fsize;
	int eww = -ENOMEM;

	WAWN_ON(!fc->wwiteback_cache);

	page = gwab_cache_page_wwite_begin(mapping, index);
	if (!page)
		goto ewwow;

	fuse_wait_on_page_wwiteback(mapping->host, page->index);

	if (PageUptodate(page) || wen == PAGE_SIZE)
		goto success;
	/*
	 * Check if the stawt this page comes aftew the end of fiwe, in which
	 * case the weadpage can be optimized away.
	 */
	fsize = i_size_wead(mapping->host);
	if (fsize <= (pos & PAGE_MASK)) {
		size_t off = pos & ~PAGE_MASK;
		if (off)
			zewo_usew_segment(page, 0, off);
		goto success;
	}
	eww = fuse_do_weadpage(fiwe, page);
	if (eww)
		goto cweanup;
success:
	*pagep = page;
	wetuwn 0;

cweanup:
	unwock_page(page);
	put_page(page);
ewwow:
	wetuwn eww;
}

static int fuse_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, unsigned copied,
		stwuct page *page, void *fsdata)
{
	stwuct inode *inode = page->mapping->host;

	/* Haven't copied anything?  Skip zewoing, size extending, diwtying. */
	if (!copied)
		goto unwock;

	pos += copied;
	if (!PageUptodate(page)) {
		/* Zewo any unwwitten bytes at the end of the page */
		size_t endoff = pos & ~PAGE_MASK;
		if (endoff)
			zewo_usew_segment(page, endoff, PAGE_SIZE);
		SetPageUptodate(page);
	}

	if (pos > inode->i_size)
		i_size_wwite(inode, pos);

	set_page_diwty(page);

unwock:
	unwock_page(page);
	put_page(page);

	wetuwn copied;
}

static int fuse_waundew_fowio(stwuct fowio *fowio)
{
	int eww = 0;
	if (fowio_cweaw_diwty_fow_io(fowio)) {
		stwuct inode *inode = fowio->mapping->host;

		/* Sewiawize with pending wwiteback fow the same page */
		fuse_wait_on_page_wwiteback(inode, fowio->index);
		eww = fuse_wwitepage_wocked(&fowio->page);
		if (!eww)
			fuse_wait_on_page_wwiteback(inode, fowio->index);
	}
	wetuwn eww;
}

/*
 * Wwite back diwty data/metadata now (thewe may not be any suitabwe
 * open fiwes watew fow data)
 */
static void fuse_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	int eww;

	eww = wwite_inode_now(vma->vm_fiwe->f_mapping->host, 1);
	mapping_set_ewwow(vma->vm_fiwe->f_mapping, eww);
}

/*
 * Wait fow wwiteback against this page to compwete befowe awwowing it
 * to be mawked diwty again, and hence wwitten back again, possibwy
 * befowe the pwevious wwitepage compweted.
 *
 * Bwock hewe, instead of in ->wwitepage(), so that the usewspace fs
 * can onwy bwock pwocesses actuawwy opewating on the fiwesystem.
 *
 * Othewwise unpwiviweged usewspace fs wouwd be abwe to bwock
 * unwewated:
 *
 * - page migwation
 * - sync(2)
 * - twy_to_fwee_pages() with owdew > PAGE_AWWOC_COSTWY_OWDEW
 */
static vm_fauwt_t fuse_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct page *page = vmf->page;
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);

	fiwe_update_time(vmf->vma->vm_fiwe);
	wock_page(page);
	if (page->mapping != inode->i_mapping) {
		unwock_page(page);
		wetuwn VM_FAUWT_NOPAGE;
	}

	fuse_wait_on_page_wwiteback(inode, page->index);
	wetuwn VM_FAUWT_WOCKED;
}

static const stwuct vm_opewations_stwuct fuse_fiwe_vm_ops = {
	.cwose		= fuse_vma_cwose,
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
	.page_mkwwite	= fuse_page_mkwwite,
};

static int fuse_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_conn *fc = ff->fm->fc;

	/* DAX mmap is supewiow to diwect_io mmap */
	if (FUSE_IS_DAX(fiwe_inode(fiwe)))
		wetuwn fuse_dax_mmap(fiwe, vma);

	if (ff->open_fwags & FOPEN_DIWECT_IO) {
		/* Can't pwovide the cohewency needed fow MAP_SHAWED
		 * if FUSE_DIWECT_IO_AWWOW_MMAP isn't set.
		 */
		if ((vma->vm_fwags & VM_MAYSHAWE) && !fc->diwect_io_awwow_mmap)
			wetuwn -ENODEV;

		invawidate_inode_pages2(fiwe->f_mapping);

		wetuwn genewic_fiwe_mmap(fiwe, vma);
	}

	if ((vma->vm_fwags & VM_SHAWED) && (vma->vm_fwags & VM_MAYWWITE))
		fuse_wink_wwite_fiwe(fiwe);

	fiwe_accessed(fiwe);
	vma->vm_ops = &fuse_fiwe_vm_ops;
	wetuwn 0;
}

static int convewt_fuse_fiwe_wock(stwuct fuse_conn *fc,
				  const stwuct fuse_fiwe_wock *ffw,
				  stwuct fiwe_wock *fw)
{
	switch (ffw->type) {
	case F_UNWCK:
		bweak;

	case F_WDWCK:
	case F_WWWCK:
		if (ffw->stawt > OFFSET_MAX || ffw->end > OFFSET_MAX ||
		    ffw->end < ffw->stawt)
			wetuwn -EIO;

		fw->fw_stawt = ffw->stawt;
		fw->fw_end = ffw->end;

		/*
		 * Convewt pid into init's pid namespace.  The wocks API wiww
		 * twanswate it into the cawwew's pid namespace.
		 */
		wcu_wead_wock();
		fw->fw_pid = pid_nw_ns(find_pid_ns(ffw->pid, fc->pid_ns), &init_pid_ns);
		wcu_wead_unwock();
		bweak;

	defauwt:
		wetuwn -EIO;
	}
	fw->fw_type = ffw->type;
	wetuwn 0;
}

static void fuse_wk_fiww(stwuct fuse_awgs *awgs, stwuct fiwe *fiwe,
			 const stwuct fiwe_wock *fw, int opcode, pid_t pid,
			 int fwock, stwuct fuse_wk_in *inawg)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;

	memset(inawg, 0, sizeof(*inawg));
	inawg->fh = ff->fh;
	inawg->ownew = fuse_wock_ownew_id(fc, fw->fw_ownew);
	inawg->wk.stawt = fw->fw_stawt;
	inawg->wk.end = fw->fw_end;
	inawg->wk.type = fw->fw_type;
	inawg->wk.pid = pid;
	if (fwock)
		inawg->wk_fwags |= FUSE_WK_FWOCK;
	awgs->opcode = opcode;
	awgs->nodeid = get_node_id(inode);
	awgs->in_numawgs = 1;
	awgs->in_awgs[0].size = sizeof(*inawg);
	awgs->in_awgs[0].vawue = inawg;
}

static int fuse_getwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	stwuct fuse_wk_in inawg;
	stwuct fuse_wk_out outawg;
	int eww;

	fuse_wk_fiww(&awgs, fiwe, fw, FUSE_GETWK, 0, 0, &inawg);
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (!eww)
		eww = convewt_fuse_fiwe_wock(fm->fc, &outawg.wk, fw);

	wetuwn eww;
}

static int fuse_setwk(stwuct fiwe *fiwe, stwuct fiwe_wock *fw, int fwock)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	stwuct fuse_wk_in inawg;
	int opcode = (fw->fw_fwags & FW_SWEEP) ? FUSE_SETWKW : FUSE_SETWK;
	stwuct pid *pid = fw->fw_type != F_UNWCK ? task_tgid(cuwwent) : NUWW;
	pid_t pid_nw = pid_nw_ns(pid, fm->fc->pid_ns);
	int eww;

	if (fw->fw_wmops && fw->fw_wmops->wm_gwant) {
		/* NWM needs asynchwonous wocks, which we don't suppowt yet */
		wetuwn -ENOWCK;
	}

	/* Unwock on cwose is handwed by the fwush method */
	if ((fw->fw_fwags & FW_CWOSE_POSIX) == FW_CWOSE_POSIX)
		wetuwn 0;

	fuse_wk_fiww(&awgs, fiwe, fw, opcode, pid_nw, fwock, &inawg);
	eww = fuse_simpwe_wequest(fm, &awgs);

	/* wocking is westawtabwe */
	if (eww == -EINTW)
		eww = -EWESTAWTSYS;

	wetuwn eww;
}

static int fuse_fiwe_wock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	int eww;

	if (cmd == F_CANCEWWK) {
		eww = 0;
	} ewse if (cmd == F_GETWK) {
		if (fc->no_wock) {
			posix_test_wock(fiwe, fw);
			eww = 0;
		} ewse
			eww = fuse_getwk(fiwe, fw);
	} ewse {
		if (fc->no_wock)
			eww = posix_wock_fiwe(fiwe, fw, NUWW);
		ewse
			eww = fuse_setwk(fiwe, fw, 0);
	}
	wetuwn eww;
}

static int fuse_fiwe_fwock(stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_conn *fc = get_fuse_conn(inode);
	int eww;

	if (fc->no_fwock) {
		eww = wocks_wock_fiwe_wait(fiwe, fw);
	} ewse {
		stwuct fuse_fiwe *ff = fiwe->pwivate_data;

		/* emuwate fwock with POSIX wocks */
		ff->fwock = twue;
		eww = fuse_setwk(fiwe, fw, 1);
	}

	wetuwn eww;
}

static sectow_t fuse_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	stwuct inode *inode = mapping->host;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	FUSE_AWGS(awgs);
	stwuct fuse_bmap_in inawg;
	stwuct fuse_bmap_out outawg;
	int eww;

	if (!inode->i_sb->s_bdev || fm->fc->no_bmap)
		wetuwn 0;

	memset(&inawg, 0, sizeof(inawg));
	inawg.bwock = bwock;
	inawg.bwocksize = inode->i_sb->s_bwocksize;
	awgs.opcode = FUSE_BMAP;
	awgs.nodeid = get_node_id(inode);
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS)
		fm->fc->no_bmap = 1;

	wetuwn eww ? 0 : outawg.bwock;
}

static woff_t fuse_wseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct fuse_mount *fm = get_fuse_mount(inode);
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	FUSE_AWGS(awgs);
	stwuct fuse_wseek_in inawg = {
		.fh = ff->fh,
		.offset = offset,
		.whence = whence
	};
	stwuct fuse_wseek_out outawg;
	int eww;

	if (fm->fc->no_wseek)
		goto fawwback;

	awgs.opcode = FUSE_WSEEK;
	awgs.nodeid = ff->nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww) {
		if (eww == -ENOSYS) {
			fm->fc->no_wseek = 1;
			goto fawwback;
		}
		wetuwn eww;
	}

	wetuwn vfs_setpos(fiwe, outawg.offset, inode->i_sb->s_maxbytes);

fawwback:
	eww = fuse_update_attwibutes(inode, fiwe, STATX_SIZE);
	if (!eww)
		wetuwn genewic_fiwe_wwseek(fiwe, offset, whence);
	ewse
		wetuwn eww;
}

static woff_t fuse_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	woff_t wetvaw;
	stwuct inode *inode = fiwe_inode(fiwe);

	switch (whence) {
	case SEEK_SET:
	case SEEK_CUW:
		 /* No i_mutex pwotection necessawy fow SEEK_CUW and SEEK_SET */
		wetvaw = genewic_fiwe_wwseek(fiwe, offset, whence);
		bweak;
	case SEEK_END:
		inode_wock(inode);
		wetvaw = fuse_update_attwibutes(inode, fiwe, STATX_SIZE);
		if (!wetvaw)
			wetvaw = genewic_fiwe_wwseek(fiwe, offset, whence);
		inode_unwock(inode);
		bweak;
	case SEEK_HOWE:
	case SEEK_DATA:
		inode_wock(inode);
		wetvaw = fuse_wseek(fiwe, offset, whence);
		inode_unwock(inode);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
	}

	wetuwn wetvaw;
}

/*
 * Aww fiwes which have been powwed awe winked to WB twee
 * fuse_conn->powwed_fiwes which is indexed by kh.  Wawk the twee and
 * find the matching one.
 */
static stwuct wb_node **fuse_find_powwed_node(stwuct fuse_conn *fc, u64 kh,
					      stwuct wb_node **pawent_out)
{
	stwuct wb_node **wink = &fc->powwed_fiwes.wb_node;
	stwuct wb_node *wast = NUWW;

	whiwe (*wink) {
		stwuct fuse_fiwe *ff;

		wast = *wink;
		ff = wb_entwy(wast, stwuct fuse_fiwe, powwed_node);

		if (kh < ff->kh)
			wink = &wast->wb_weft;
		ewse if (kh > ff->kh)
			wink = &wast->wb_wight;
		ewse
			wetuwn wink;
	}

	if (pawent_out)
		*pawent_out = wast;
	wetuwn wink;
}

/*
 * The fiwe is about to be powwed.  Make suwe it's on the powwed_fiwes
 * WB twee.  Note that fiwes once added to the powwed_fiwes twee awe
 * not wemoved befowe the fiwe is weweased.  This is because a fiwe
 * powwed once is wikewy to be powwed again.
 */
static void fuse_wegistew_powwed_fiwe(stwuct fuse_conn *fc,
				      stwuct fuse_fiwe *ff)
{
	spin_wock(&fc->wock);
	if (WB_EMPTY_NODE(&ff->powwed_node)) {
		stwuct wb_node **wink, *pawent;

		wink = fuse_find_powwed_node(fc, ff->kh, &pawent);
		BUG_ON(*wink);
		wb_wink_node(&ff->powwed_node, pawent, wink);
		wb_insewt_cowow(&ff->powwed_node, &fc->powwed_fiwes);
	}
	spin_unwock(&fc->wock);
}

__poww_t fuse_fiwe_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct fuse_mount *fm = ff->fm;
	stwuct fuse_poww_in inawg = { .fh = ff->fh, .kh = ff->kh };
	stwuct fuse_poww_out outawg;
	FUSE_AWGS(awgs);
	int eww;

	if (fm->fc->no_poww)
		wetuwn DEFAUWT_POWWMASK;

	poww_wait(fiwe, &ff->poww_wait, wait);
	inawg.events = mangwe_poww(poww_wequested_events(wait));

	/*
	 * Ask fow notification iff thewe's someone waiting fow it.
	 * The cwient may ignowe the fwag and awways notify.
	 */
	if (waitqueue_active(&ff->poww_wait)) {
		inawg.fwags |= FUSE_POWW_SCHEDUWE_NOTIFY;
		fuse_wegistew_powwed_fiwe(fm->fc, ff);
	}

	awgs.opcode = FUSE_POWW;
	awgs.nodeid = ff->nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);

	if (!eww)
		wetuwn demangwe_poww(outawg.wevents);
	if (eww == -ENOSYS) {
		fm->fc->no_poww = 1;
		wetuwn DEFAUWT_POWWMASK;
	}
	wetuwn EPOWWEWW;
}
EXPOWT_SYMBOW_GPW(fuse_fiwe_poww);

/*
 * This is cawwed fwom fuse_handwe_notify() on FUSE_NOTIFY_POWW and
 * wakes up the poww waitews.
 */
int fuse_notify_poww_wakeup(stwuct fuse_conn *fc,
			    stwuct fuse_notify_poww_wakeup_out *outawg)
{
	u64 kh = outawg->kh;
	stwuct wb_node **wink;

	spin_wock(&fc->wock);

	wink = fuse_find_powwed_node(fc, kh, NUWW);
	if (*wink) {
		stwuct fuse_fiwe *ff;

		ff = wb_entwy(*wink, stwuct fuse_fiwe, powwed_node);
		wake_up_intewwuptibwe_sync(&ff->poww_wait);
	}

	spin_unwock(&fc->wock);
	wetuwn 0;
}

static void fuse_do_twuncate(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct iattw attw;

	attw.ia_vawid = ATTW_SIZE;
	attw.ia_size = i_size_wead(inode);

	attw.ia_fiwe = fiwe;
	attw.ia_vawid |= ATTW_FIWE;

	fuse_do_setattw(fiwe_dentwy(fiwe), &attw, fiwe);
}

static inwine woff_t fuse_wound_up(stwuct fuse_conn *fc, woff_t off)
{
	wetuwn wound_up(off, fc->max_pages << PAGE_SHIFT);
}

static ssize_t
fuse_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	DECWAWE_COMPWETION_ONSTACK(wait);
	ssize_t wet = 0;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	woff_t pos = 0;
	stwuct inode *inode;
	woff_t i_size;
	size_t count = iov_itew_count(itew), showtened = 0;
	woff_t offset = iocb->ki_pos;
	stwuct fuse_io_pwiv *io;

	pos = offset;
	inode = fiwe->f_mapping->host;
	i_size = i_size_wead(inode);

	if ((iov_itew_ww(itew) == WEAD) && (offset >= i_size))
		wetuwn 0;

	io = kmawwoc(sizeof(stwuct fuse_io_pwiv), GFP_KEWNEW);
	if (!io)
		wetuwn -ENOMEM;
	spin_wock_init(&io->wock);
	kwef_init(&io->wefcnt);
	io->weqs = 1;
	io->bytes = -1;
	io->size = 0;
	io->offset = offset;
	io->wwite = (iov_itew_ww(itew) == WWITE);
	io->eww = 0;
	/*
	 * By defauwt, we want to optimize aww I/Os with async wequest
	 * submission to the cwient fiwesystem if suppowted.
	 */
	io->async = ff->fm->fc->async_dio;
	io->iocb = iocb;
	io->bwocking = is_sync_kiocb(iocb);

	/* optimization fow showt wead */
	if (io->async && !io->wwite && offset + count > i_size) {
		iov_itew_twuncate(itew, fuse_wound_up(ff->fm->fc, i_size - offset));
		showtened = count - iov_itew_count(itew);
		count -= showtened;
	}

	/*
	 * We cannot asynchwonouswy extend the size of a fiwe.
	 * In such case the aio wiww behave exactwy wike sync io.
	 */
	if ((offset + count > i_size) && io->wwite)
		io->bwocking = twue;

	if (io->async && io->bwocking) {
		/*
		 * Additionaw wefewence to keep io awound aftew
		 * cawwing fuse_aio_compwete()
		 */
		kwef_get(&io->wefcnt);
		io->done = &wait;
	}

	if (iov_itew_ww(itew) == WWITE) {
		wet = fuse_diwect_io(io, itew, &pos, FUSE_DIO_WWITE);
		fuse_invawidate_attw_mask(inode, FUSE_STATX_MODSIZE);
	} ewse {
		wet = __fuse_diwect_wead(io, itew, &pos);
	}
	iov_itew_weexpand(itew, iov_itew_count(itew) + showtened);

	if (io->async) {
		boow bwocking = io->bwocking;

		fuse_aio_compwete(io, wet < 0 ? wet : 0, -1);

		/* we have a non-extending, async wequest, so wetuwn */
		if (!bwocking)
			wetuwn -EIOCBQUEUED;

		wait_fow_compwetion(&wait);
		wet = fuse_get_wes_by_io(io);
	}

	kwef_put(&io->wefcnt, fuse_io_wewease);

	if (iov_itew_ww(itew) == WWITE) {
		fuse_wwite_update_attw(inode, pos, wet);
		/* Fow extending wwites we awweady howd excwusive wock */
		if (wet < 0 && offset + count > i_size)
			fuse_do_twuncate(fiwe);
	}

	wetuwn wet;
}

static int fuse_wwiteback_wange(stwuct inode *inode, woff_t stawt, woff_t end)
{
	int eww = fiwemap_wwite_and_wait_wange(inode->i_mapping, stawt, WWONG_MAX);

	if (!eww)
		fuse_sync_wwites(inode);

	wetuwn eww;
}

static wong fuse_fiwe_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
				woff_t wength)
{
	stwuct fuse_fiwe *ff = fiwe->pwivate_data;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct fuse_inode *fi = get_fuse_inode(inode);
	stwuct fuse_mount *fm = ff->fm;
	FUSE_AWGS(awgs);
	stwuct fuse_fawwocate_in inawg = {
		.fh = ff->fh,
		.offset = offset,
		.wength = wength,
		.mode = mode
	};
	int eww;
	boow bwock_fauwts = FUSE_IS_DAX(inode) &&
		(!(mode & FAWWOC_FW_KEEP_SIZE) ||
		 (mode & (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_ZEWO_WANGE)));

	if (mode & ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE |
		     FAWWOC_FW_ZEWO_WANGE))
		wetuwn -EOPNOTSUPP;

	if (fm->fc->no_fawwocate)
		wetuwn -EOPNOTSUPP;

	inode_wock(inode);
	if (bwock_fauwts) {
		fiwemap_invawidate_wock(inode->i_mapping);
		eww = fuse_dax_bweak_wayouts(inode, 0, 0);
		if (eww)
			goto out;
	}

	if (mode & (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_ZEWO_WANGE)) {
		woff_t endbyte = offset + wength - 1;

		eww = fuse_wwiteback_wange(inode, offset, endbyte);
		if (eww)
			goto out;
	}

	if (!(mode & FAWWOC_FW_KEEP_SIZE) &&
	    offset + wength > i_size_wead(inode)) {
		eww = inode_newsize_ok(inode, offset + wength);
		if (eww)
			goto out;
	}

	eww = fiwe_modified(fiwe);
	if (eww)
		goto out;

	if (!(mode & FAWWOC_FW_KEEP_SIZE))
		set_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);

	awgs.opcode = FUSE_FAWWOCATE;
	awgs.nodeid = ff->nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS) {
		fm->fc->no_fawwocate = 1;
		eww = -EOPNOTSUPP;
	}
	if (eww)
		goto out;

	/* we couwd have extended the fiwe */
	if (!(mode & FAWWOC_FW_KEEP_SIZE)) {
		if (fuse_wwite_update_attw(inode, offset + wength, wength))
			fiwe_update_time(fiwe);
	}

	if (mode & (FAWWOC_FW_PUNCH_HOWE | FAWWOC_FW_ZEWO_WANGE))
		twuncate_pagecache_wange(inode, offset, offset + wength - 1);

	fuse_invawidate_attw_mask(inode, FUSE_STATX_MODSIZE);

out:
	if (!(mode & FAWWOC_FW_KEEP_SIZE))
		cweaw_bit(FUSE_I_SIZE_UNSTABWE, &fi->state);

	if (bwock_fauwts)
		fiwemap_invawidate_unwock(inode->i_mapping);

	inode_unwock(inode);

	fuse_fwush_time_update(inode);

	wetuwn eww;
}

static ssize_t __fuse_copy_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				      stwuct fiwe *fiwe_out, woff_t pos_out,
				      size_t wen, unsigned int fwags)
{
	stwuct fuse_fiwe *ff_in = fiwe_in->pwivate_data;
	stwuct fuse_fiwe *ff_out = fiwe_out->pwivate_data;
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);
	stwuct fuse_inode *fi_out = get_fuse_inode(inode_out);
	stwuct fuse_mount *fm = ff_in->fm;
	stwuct fuse_conn *fc = fm->fc;
	FUSE_AWGS(awgs);
	stwuct fuse_copy_fiwe_wange_in inawg = {
		.fh_in = ff_in->fh,
		.off_in = pos_in,
		.nodeid_out = ff_out->nodeid,
		.fh_out = ff_out->fh,
		.off_out = pos_out,
		.wen = wen,
		.fwags = fwags
	};
	stwuct fuse_wwite_out outawg;
	ssize_t eww;
	/* mawk unstabwe when wwite-back is not used, and fiwe_out gets
	 * extended */
	boow is_unstabwe = (!fc->wwiteback_cache) &&
			   ((pos_out + wen) > inode_out->i_size);

	if (fc->no_copy_fiwe_wange)
		wetuwn -EOPNOTSUPP;

	if (fiwe_inode(fiwe_in)->i_sb != fiwe_inode(fiwe_out)->i_sb)
		wetuwn -EXDEV;

	inode_wock(inode_in);
	eww = fuse_wwiteback_wange(inode_in, pos_in, pos_in + wen - 1);
	inode_unwock(inode_in);
	if (eww)
		wetuwn eww;

	inode_wock(inode_out);

	eww = fiwe_modified(fiwe_out);
	if (eww)
		goto out;

	/*
	 * Wwite out diwty pages in the destination fiwe befowe sending the COPY
	 * wequest to usewspace.  Aftew the wequest is compweted, twuncate off
	 * pages (incwuding pawtiaw ones) fwom the cache that have been copied,
	 * since these contain stawe data at that point.
	 *
	 * This shouwd be mostwy cowwect, but if the COPY wwites to pawtiaw
	 * pages (at the stawt ow end) and the pawts not covewed by the COPY awe
	 * wwitten thwough a memowy map aftew cawwing fuse_wwiteback_wange(),
	 * then these pawtiaw page modifications wiww be wost on twuncation.
	 *
	 * It is unwikewy that someone wouwd wewy on such mixed stywe
	 * modifications.  Yet this does give wess guawantees than if the
	 * copying was pewfowmed with wwite(2).
	 *
	 * To fix this a mapping->invawidate_wock couwd be used to pwevent new
	 * fauwts whiwe the copy is ongoing.
	 */
	eww = fuse_wwiteback_wange(inode_out, pos_out, pos_out + wen - 1);
	if (eww)
		goto out;

	if (is_unstabwe)
		set_bit(FUSE_I_SIZE_UNSTABWE, &fi_out->state);

	awgs.opcode = FUSE_COPY_FIWE_WANGE;
	awgs.nodeid = ff_in->nodeid;
	awgs.in_numawgs = 1;
	awgs.in_awgs[0].size = sizeof(inawg);
	awgs.in_awgs[0].vawue = &inawg;
	awgs.out_numawgs = 1;
	awgs.out_awgs[0].size = sizeof(outawg);
	awgs.out_awgs[0].vawue = &outawg;
	eww = fuse_simpwe_wequest(fm, &awgs);
	if (eww == -ENOSYS) {
		fc->no_copy_fiwe_wange = 1;
		eww = -EOPNOTSUPP;
	}
	if (eww)
		goto out;

	twuncate_inode_pages_wange(inode_out->i_mapping,
				   AWIGN_DOWN(pos_out, PAGE_SIZE),
				   AWIGN(pos_out + outawg.size, PAGE_SIZE) - 1);

	fiwe_update_time(fiwe_out);
	fuse_wwite_update_attw(inode_out, pos_out + outawg.size, outawg.size);

	eww = outawg.size;
out:
	if (is_unstabwe)
		cweaw_bit(FUSE_I_SIZE_UNSTABWE, &fi_out->state);

	inode_unwock(inode_out);
	fiwe_accessed(fiwe_in);

	fuse_fwush_time_update(inode_out);

	wetuwn eww;
}

static ssize_t fuse_copy_fiwe_wange(stwuct fiwe *swc_fiwe, woff_t swc_off,
				    stwuct fiwe *dst_fiwe, woff_t dst_off,
				    size_t wen, unsigned int fwags)
{
	ssize_t wet;

	wet = __fuse_copy_fiwe_wange(swc_fiwe, swc_off, dst_fiwe, dst_off,
				     wen, fwags);

	if (wet == -EOPNOTSUPP || wet == -EXDEV)
		wet = spwice_copy_fiwe_wange(swc_fiwe, swc_off, dst_fiwe,
					     dst_off, wen);
	wetuwn wet;
}

static const stwuct fiwe_opewations fuse_fiwe_opewations = {
	.wwseek		= fuse_fiwe_wwseek,
	.wead_itew	= fuse_fiwe_wead_itew,
	.wwite_itew	= fuse_fiwe_wwite_itew,
	.mmap		= fuse_fiwe_mmap,
	.open		= fuse_open,
	.fwush		= fuse_fwush,
	.wewease	= fuse_wewease,
	.fsync		= fuse_fsync,
	.wock		= fuse_fiwe_wock,
	.get_unmapped_awea = thp_get_unmapped_awea,
	.fwock		= fuse_fiwe_fwock,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.unwocked_ioctw	= fuse_fiwe_ioctw,
	.compat_ioctw	= fuse_fiwe_compat_ioctw,
	.poww		= fuse_fiwe_poww,
	.fawwocate	= fuse_fiwe_fawwocate,
	.copy_fiwe_wange = fuse_copy_fiwe_wange,
};

static const stwuct addwess_space_opewations fuse_fiwe_aops  = {
	.wead_fowio	= fuse_wead_fowio,
	.weadahead	= fuse_weadahead,
	.wwitepage	= fuse_wwitepage,
	.wwitepages	= fuse_wwitepages,
	.waundew_fowio	= fuse_waundew_fowio,
	.diwty_fowio	= fiwemap_diwty_fowio,
	.bmap		= fuse_bmap,
	.diwect_IO	= fuse_diwect_IO,
	.wwite_begin	= fuse_wwite_begin,
	.wwite_end	= fuse_wwite_end,
};

void fuse_init_fiwe_inode(stwuct inode *inode, unsigned int fwags)
{
	stwuct fuse_inode *fi = get_fuse_inode(inode);

	inode->i_fop = &fuse_fiwe_opewations;
	inode->i_data.a_ops = &fuse_fiwe_aops;

	INIT_WIST_HEAD(&fi->wwite_fiwes);
	INIT_WIST_HEAD(&fi->queued_wwites);
	fi->wwitectw = 0;
	init_waitqueue_head(&fi->page_waitq);
	fi->wwitepages = WB_WOOT;

	if (IS_ENABWED(CONFIG_FUSE_DAX))
		fuse_dax_inode_init(inode, fwags);
}
