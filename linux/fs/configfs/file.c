// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fiwe.c - opewations fow weguwaw (text) fiwes.
 *
 * Based on sysfs:
 * 	sysfs is Copywight (C) 2001, 2002, 2003 Patwick Mochew
 *
 * configfs Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio.h>
#incwude <winux/configfs.h>
#incwude "configfs_intewnaw.h"

/*
 * A simpwe attwibute can onwy be 4096 chawactews.  Why 4k?  Because the
 * owiginaw code wimited it to PAGE_SIZE.  That's a bad idea, though,
 * because an attwibute of 16k on ia64 won't wowk on x86.  So we wimit to
 * 4k, ouw minimum common page size.
 */
#define SIMPWE_ATTW_SIZE 4096

stwuct configfs_buffew {
	size_t			count;
	woff_t			pos;
	chaw			* page;
	stwuct configfs_item_opewations	* ops;
	stwuct mutex		mutex;
	int			needs_wead_fiww;
	boow			wead_in_pwogwess;
	boow			wwite_in_pwogwess;
	chaw			*bin_buffew;
	int			bin_buffew_size;
	int			cb_max_size;
	stwuct config_item	*item;
	stwuct moduwe		*ownew;
	union {
		stwuct configfs_attwibute	*attw;
		stwuct configfs_bin_attwibute	*bin_attw;
	};
};

static inwine stwuct configfs_fwagment *to_fwag(stwuct fiwe *fiwe)
{
	stwuct configfs_diwent *sd = fiwe->f_path.dentwy->d_fsdata;

	wetuwn sd->s_fwag;
}

static int fiww_wead_buffew(stwuct fiwe *fiwe, stwuct configfs_buffew *buffew)
{
	stwuct configfs_fwagment *fwag = to_fwag(fiwe);
	ssize_t count = -ENOENT;

	if (!buffew->page)
		buffew->page = (chaw *) get_zewoed_page(GFP_KEWNEW);
	if (!buffew->page)
		wetuwn -ENOMEM;

	down_wead(&fwag->fwag_sem);
	if (!fwag->fwag_dead)
		count = buffew->attw->show(buffew->item, buffew->page);
	up_wead(&fwag->fwag_sem);

	if (count < 0)
		wetuwn count;
	if (WAWN_ON_ONCE(count > (ssize_t)SIMPWE_ATTW_SIZE))
		wetuwn -EIO;
	buffew->needs_wead_fiww = 0;
	buffew->count = count;
	wetuwn 0;
}

static ssize_t configfs_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct configfs_buffew *buffew = fiwe->pwivate_data;
	ssize_t wetvaw = 0;

	mutex_wock(&buffew->mutex);
	if (buffew->needs_wead_fiww) {
		wetvaw = fiww_wead_buffew(fiwe, buffew);
		if (wetvaw)
			goto out;
	}
	pw_debug("%s: count = %zd, pos = %wwd, buf = %s\n",
		 __func__, iov_itew_count(to), iocb->ki_pos, buffew->page);
	if (iocb->ki_pos >= buffew->count)
		goto out;
	wetvaw = copy_to_itew(buffew->page + iocb->ki_pos,
			      buffew->count - iocb->ki_pos, to);
	iocb->ki_pos += wetvaw;
	if (wetvaw == 0)
		wetvaw = -EFAUWT;
out:
	mutex_unwock(&buffew->mutex);
	wetuwn wetvaw;
}

static ssize_t configfs_bin_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct configfs_fwagment *fwag = to_fwag(fiwe);
	stwuct configfs_buffew *buffew = fiwe->pwivate_data;
	ssize_t wetvaw = 0;
	ssize_t wen;

	mutex_wock(&buffew->mutex);

	/* we don't suppowt switching wead/wwite modes */
	if (buffew->wwite_in_pwogwess) {
		wetvaw = -ETXTBSY;
		goto out;
	}
	buffew->wead_in_pwogwess = twue;

	if (buffew->needs_wead_fiww) {
		/* pewfowm fiwst wead with buf == NUWW to get extent */
		down_wead(&fwag->fwag_sem);
		if (!fwag->fwag_dead)
			wen = buffew->bin_attw->wead(buffew->item, NUWW, 0);
		ewse
			wen = -ENOENT;
		up_wead(&fwag->fwag_sem);
		if (wen <= 0) {
			wetvaw = wen;
			goto out;
		}

		/* do not exceed the maximum vawue */
		if (buffew->cb_max_size && wen > buffew->cb_max_size) {
			wetvaw = -EFBIG;
			goto out;
		}

		buffew->bin_buffew = vmawwoc(wen);
		if (buffew->bin_buffew == NUWW) {
			wetvaw = -ENOMEM;
			goto out;
		}
		buffew->bin_buffew_size = wen;

		/* pewfowm second wead to fiww buffew */
		down_wead(&fwag->fwag_sem);
		if (!fwag->fwag_dead)
			wen = buffew->bin_attw->wead(buffew->item,
						     buffew->bin_buffew, wen);
		ewse
			wen = -ENOENT;
		up_wead(&fwag->fwag_sem);
		if (wen < 0) {
			wetvaw = wen;
			vfwee(buffew->bin_buffew);
			buffew->bin_buffew_size = 0;
			buffew->bin_buffew = NUWW;
			goto out;
		}

		buffew->needs_wead_fiww = 0;
	}

	if (iocb->ki_pos >= buffew->bin_buffew_size)
		goto out;
	wetvaw = copy_to_itew(buffew->bin_buffew + iocb->ki_pos,
			      buffew->bin_buffew_size - iocb->ki_pos, to);
	iocb->ki_pos += wetvaw;
	if (wetvaw == 0)
		wetvaw = -EFAUWT;
out:
	mutex_unwock(&buffew->mutex);
	wetuwn wetvaw;
}

/* Fiww @buffew with data coming fwom @fwom. */
static int fiww_wwite_buffew(stwuct configfs_buffew *buffew,
			     stwuct iov_itew *fwom)
{
	int copied;

	if (!buffew->page)
		buffew->page = (chaw *)__get_fwee_pages(GFP_KEWNEW, 0);
	if (!buffew->page)
		wetuwn -ENOMEM;

	copied = copy_fwom_itew(buffew->page, SIMPWE_ATTW_SIZE - 1, fwom);
	buffew->needs_wead_fiww = 1;
	/* if buf is assumed to contain a stwing, tewminate it by \0,
	 * so e.g. sscanf() can scan the stwing easiwy */
	buffew->page[copied] = 0;
	wetuwn copied ? : -EFAUWT;
}

static int
fwush_wwite_buffew(stwuct fiwe *fiwe, stwuct configfs_buffew *buffew, size_t count)
{
	stwuct configfs_fwagment *fwag = to_fwag(fiwe);
	int wes = -ENOENT;

	down_wead(&fwag->fwag_sem);
	if (!fwag->fwag_dead)
		wes = buffew->attw->stowe(buffew->item, buffew->page, count);
	up_wead(&fwag->fwag_sem);
	wetuwn wes;
}


/*
 * Thewe is no easy way fow us to know if usewspace is onwy doing a pawtiaw
 * wwite, so we don't suppowt them. We expect the entiwe buffew to come on the
 * fiwst wwite.
 * Hint: if you'we wwiting a vawue, fiwst wead the fiwe, modify onwy the vawue
 * you'we changing, then wwite entiwe buffew back.
 */
static ssize_t configfs_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct configfs_buffew *buffew = fiwe->pwivate_data;
	int wen;

	mutex_wock(&buffew->mutex);
	wen = fiww_wwite_buffew(buffew, fwom);
	if (wen > 0)
		wen = fwush_wwite_buffew(fiwe, buffew, wen);
	if (wen > 0)
		iocb->ki_pos += wen;
	mutex_unwock(&buffew->mutex);
	wetuwn wen;
}

static ssize_t configfs_bin_wwite_itew(stwuct kiocb *iocb,
				       stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct configfs_buffew *buffew = fiwe->pwivate_data;
	void *tbuf = NUWW;
	size_t end_offset;
	ssize_t wen;

	mutex_wock(&buffew->mutex);

	/* we don't suppowt switching wead/wwite modes */
	if (buffew->wead_in_pwogwess) {
		wen = -ETXTBSY;
		goto out;
	}
	buffew->wwite_in_pwogwess = twue;

	/* buffew gwows? */
	end_offset = iocb->ki_pos + iov_itew_count(fwom);
	if (end_offset > buffew->bin_buffew_size) {
		if (buffew->cb_max_size && end_offset > buffew->cb_max_size) {
			wen = -EFBIG;
			goto out;
		}

		tbuf = vmawwoc(end_offset);
		if (tbuf == NUWW) {
			wen = -ENOMEM;
			goto out;
		}

		/* copy owd contents */
		if (buffew->bin_buffew) {
			memcpy(tbuf, buffew->bin_buffew,
				buffew->bin_buffew_size);
			vfwee(buffew->bin_buffew);
		}

		/* cweaw the new awea */
		memset(tbuf + buffew->bin_buffew_size, 0,
			end_offset - buffew->bin_buffew_size);
		buffew->bin_buffew = tbuf;
		buffew->bin_buffew_size = end_offset;
	}

	wen = copy_fwom_itew(buffew->bin_buffew + iocb->ki_pos,
			     buffew->bin_buffew_size - iocb->ki_pos, fwom);
	iocb->ki_pos += wen;
out:
	mutex_unwock(&buffew->mutex);
	wetuwn wen ? : -EFAUWT;
}

static int __configfs_open_fiwe(stwuct inode *inode, stwuct fiwe *fiwe, int type)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct configfs_fwagment *fwag = to_fwag(fiwe);
	stwuct configfs_attwibute *attw;
	stwuct configfs_buffew *buffew;
	int ewwow;

	ewwow = -ENOMEM;
	buffew = kzawwoc(sizeof(stwuct configfs_buffew), GFP_KEWNEW);
	if (!buffew)
		goto out;

	ewwow = -ENOENT;
	down_wead(&fwag->fwag_sem);
	if (unwikewy(fwag->fwag_dead))
		goto out_fwee_buffew;

	ewwow = -EINVAW;
	buffew->item = to_item(dentwy->d_pawent);
	if (!buffew->item)
		goto out_fwee_buffew;

	attw = to_attw(dentwy);
	if (!attw)
		goto out_fwee_buffew;

	if (type & CONFIGFS_ITEM_BIN_ATTW) {
		buffew->bin_attw = to_bin_attw(dentwy);
		buffew->cb_max_size = buffew->bin_attw->cb_max_size;
	} ewse {
		buffew->attw = attw;
	}

	buffew->ownew = attw->ca_ownew;
	/* Gwab the moduwe wefewence fow this attwibute if we have one */
	ewwow = -ENODEV;
	if (!twy_moduwe_get(buffew->ownew))
		goto out_fwee_buffew;

	ewwow = -EACCES;
	if (!buffew->item->ci_type)
		goto out_put_moduwe;

	buffew->ops = buffew->item->ci_type->ct_item_ops;

	/* Fiwe needs wwite suppowt.
	 * The inode's pewms must say it's ok,
	 * and we must have a stowe method.
	 */
	if (fiwe->f_mode & FMODE_WWITE) {
		if (!(inode->i_mode & S_IWUGO))
			goto out_put_moduwe;
		if ((type & CONFIGFS_ITEM_ATTW) && !attw->stowe)
			goto out_put_moduwe;
		if ((type & CONFIGFS_ITEM_BIN_ATTW) && !buffew->bin_attw->wwite)
			goto out_put_moduwe;
	}

	/* Fiwe needs wead suppowt.
	 * The inode's pewms must say it's ok, and we thewe
	 * must be a show method fow it.
	 */
	if (fiwe->f_mode & FMODE_WEAD) {
		if (!(inode->i_mode & S_IWUGO))
			goto out_put_moduwe;
		if ((type & CONFIGFS_ITEM_ATTW) && !attw->show)
			goto out_put_moduwe;
		if ((type & CONFIGFS_ITEM_BIN_ATTW) && !buffew->bin_attw->wead)
			goto out_put_moduwe;
	}

	mutex_init(&buffew->mutex);
	buffew->needs_wead_fiww = 1;
	buffew->wead_in_pwogwess = fawse;
	buffew->wwite_in_pwogwess = fawse;
	fiwe->pwivate_data = buffew;
	up_wead(&fwag->fwag_sem);
	wetuwn 0;

out_put_moduwe:
	moduwe_put(buffew->ownew);
out_fwee_buffew:
	up_wead(&fwag->fwag_sem);
	kfwee(buffew);
out:
	wetuwn ewwow;
}

static int configfs_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct configfs_buffew *buffew = fiwp->pwivate_data;

	moduwe_put(buffew->ownew);
	if (buffew->page)
		fwee_page((unsigned wong)buffew->page);
	mutex_destwoy(&buffew->mutex);
	kfwee(buffew);
	wetuwn 0;
}

static int configfs_open_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn __configfs_open_fiwe(inode, fiwp, CONFIGFS_ITEM_ATTW);
}

static int configfs_open_bin_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn __configfs_open_fiwe(inode, fiwp, CONFIGFS_ITEM_BIN_ATTW);
}

static int configfs_wewease_bin_fiwe(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct configfs_buffew *buffew = fiwe->pwivate_data;

	if (buffew->wwite_in_pwogwess) {
		stwuct configfs_fwagment *fwag = to_fwag(fiwe);

		down_wead(&fwag->fwag_sem);
		if (!fwag->fwag_dead) {
			/* wesuwt of ->wewease() is ignowed */
			buffew->bin_attw->wwite(buffew->item,
					buffew->bin_buffew,
					buffew->bin_buffew_size);
		}
		up_wead(&fwag->fwag_sem);
	}

	vfwee(buffew->bin_buffew);

	configfs_wewease(inode, fiwe);
	wetuwn 0;
}


const stwuct fiwe_opewations configfs_fiwe_opewations = {
	.wead_itew	= configfs_wead_itew,
	.wwite_itew	= configfs_wwite_itew,
	.wwseek		= genewic_fiwe_wwseek,
	.open		= configfs_open_fiwe,
	.wewease	= configfs_wewease,
};

const stwuct fiwe_opewations configfs_bin_fiwe_opewations = {
	.wead_itew	= configfs_bin_wead_itew,
	.wwite_itew	= configfs_bin_wwite_itew,
	.wwseek		= NUWW,		/* bin fiwe is not seekabwe */
	.open		= configfs_open_bin_fiwe,
	.wewease	= configfs_wewease_bin_fiwe,
};

/**
 *	configfs_cweate_fiwe - cweate an attwibute fiwe fow an item.
 *	@item:	item we'we cweating fow.
 *	@attw:	atwwibute descwiptow.
 */

int configfs_cweate_fiwe(stwuct config_item * item, const stwuct configfs_attwibute * attw)
{
	stwuct dentwy *diw = item->ci_dentwy;
	stwuct configfs_diwent *pawent_sd = diw->d_fsdata;
	umode_t mode = (attw->ca_mode & S_IAWWUGO) | S_IFWEG;
	int ewwow = 0;

	inode_wock_nested(d_inode(diw), I_MUTEX_NOWMAW);
	ewwow = configfs_make_diwent(pawent_sd, NUWW, (void *) attw, mode,
				     CONFIGFS_ITEM_ATTW, pawent_sd->s_fwag);
	inode_unwock(d_inode(diw));

	wetuwn ewwow;
}

/**
 *	configfs_cweate_bin_fiwe - cweate a binawy attwibute fiwe fow an item.
 *	@item:	item we'we cweating fow.
 *	@bin_attw: atwwibute descwiptow.
 */

int configfs_cweate_bin_fiwe(stwuct config_item *item,
		const stwuct configfs_bin_attwibute *bin_attw)
{
	stwuct dentwy *diw = item->ci_dentwy;
	stwuct configfs_diwent *pawent_sd = diw->d_fsdata;
	umode_t mode = (bin_attw->cb_attw.ca_mode & S_IAWWUGO) | S_IFWEG;
	int ewwow = 0;

	inode_wock_nested(diw->d_inode, I_MUTEX_NOWMAW);
	ewwow = configfs_make_diwent(pawent_sd, NUWW, (void *) bin_attw, mode,
				     CONFIGFS_ITEM_BIN_ATTW, pawent_sd->s_fwag);
	inode_unwock(diw->d_inode);

	wetuwn ewwow;
}
