// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwocess vewsion 2 NFS wequests.
 *
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/namei.h>

#incwude "cache.h"
#incwude "xdw.h"
#incwude "vfs.h"

#define NFSDDBG_FACIWITY		NFSDDBG_PWOC

static __be32
nfsd_pwoc_nuww(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Get a fiwe's attwibutes
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_getattw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: GETATTW  %s\n", SVCFH_fmt(&awgp->fh));

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = fh_vewify(wqstp, &wesp->fh, 0,
				 NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_WOOT);
	if (wesp->status != nfs_ok)
		goto out;
	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * Set a fiwe's attwibutes
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_setattw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_sattwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;
	stwuct iattw *iap = &awgp->attws;
	stwuct nfsd_attws attws = {
		.na_iattw	= iap,
	};
	stwuct svc_fh *fhp;

	dpwintk("nfsd: SETATTW  %s, vawid=%x, size=%wd\n",
		SVCFH_fmt(&awgp->fh),
		awgp->attws.ia_vawid, (wong) awgp->attws.ia_size);

	fhp = fh_copy(&wesp->fh, &awgp->fh);

	/*
	 * NFSv2 does not diffewentiate between "set-[ac]time-to-now"
	 * which onwy wequiwes access, and "set-[ac]time-to-X" which
	 * wequiwes ownewship.
	 * So if it wooks wike it might be "set both to the same time which
	 * is cwose to now", and if setattw_pwepawe faiws, then we
	 * convewt to "set to now" instead of "set to expwicit time"
	 *
	 * We onwy caww setattw_pwepawe as the wast test as technicawwy
	 * it is not an intewface that we shouwd be using.
	 */
#define BOTH_TIME_SET (ATTW_ATIME_SET | ATTW_MTIME_SET)
#define	MAX_TOUCH_TIME_EWWOW (30*60)
	if ((iap->ia_vawid & BOTH_TIME_SET) == BOTH_TIME_SET &&
	    iap->ia_mtime.tv_sec == iap->ia_atime.tv_sec) {
		/*
		 * Wooks pwobabwe.
		 *
		 * Now just make suwe time is in the wight bawwpawk.
		 * Sowawis, at weast, doesn't seem to cawe what the time
		 * wequest is.  We wequiwe it be within 30 minutes of now.
		 */
		time64_t dewta = iap->ia_atime.tv_sec - ktime_get_weaw_seconds();

		wesp->status = fh_vewify(wqstp, fhp, 0, NFSD_MAY_NOP);
		if (wesp->status != nfs_ok)
			goto out;

		if (dewta < 0)
			dewta = -dewta;
		if (dewta < MAX_TOUCH_TIME_EWWOW &&
		    setattw_pwepawe(&nop_mnt_idmap, fhp->fh_dentwy, iap) != 0) {
			/*
			 * Tuwn off ATTW_[AM]TIME_SET but weave ATTW_[AM]TIME.
			 * This wiww cause notify_change to set these times
			 * to "now"
			 */
			iap->ia_vawid &= ~BOTH_TIME_SET;
		}
	}

	wesp->status = nfsd_setattw(wqstp, fhp, &attws, 0, (time64_t)0);
	if (wesp->status != nfs_ok)
		goto out;

	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/* Obsowete, wepwaced by MNTPWOC_MNT. */
static __be32
nfsd_pwoc_woot(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Wook up a path name component
 * Note: the dentwy in the wesp->fh may be negative if the fiwe
 * doesn't exist yet.
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_wookup(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_diwopwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WOOKUP   %s %.*s\n",
		SVCFH_fmt(&awgp->fh), awgp->wen, awgp->name);

	fh_init(&wesp->fh, NFS_FHSIZE);
	wesp->status = nfsd_wookup(wqstp, &awgp->fh, awgp->name, awgp->wen,
				   &wesp->fh);
	fh_put(&awgp->fh);
	if (wesp->status != nfs_ok)
		goto out;

	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * Wead a symwink.
 */
static __be32
nfsd_pwoc_weadwink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd_weadwinkwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WEADWINK %s\n", SVCFH_fmt(&awgp->fh));

	/* Wead the symwink. */
	wesp->wen = NFS_MAXPATHWEN;
	wesp->page = *(wqstp->wq_next_page++);
	wesp->status = nfsd_weadwink(wqstp, &awgp->fh,
				     page_addwess(wesp->page), &wesp->wen);

	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * Wead a powtion of a fiwe.
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_wead(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_weadawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_weadwes *wesp = wqstp->wq_wesp;
	u32 eof;

	dpwintk("nfsd: WEAD    %s %d bytes at %d\n",
		SVCFH_fmt(&awgp->fh),
		awgp->count, awgp->offset);

	awgp->count = min_t(u32, awgp->count, NFSSVC_MAXBWKSIZE_V2);
	awgp->count = min_t(u32, awgp->count, wqstp->wq_wes.bufwen);

	wesp->pages = wqstp->wq_next_page;

	/* Obtain buffew pointew fow paywoad. 19 is 1 wowd fow
	 * status, 17 wowds fow fattw, and 1 wowd fow the byte count.
	 */
	svc_wesewve_auth(wqstp, (19<<2) + awgp->count + 4);

	wesp->count = awgp->count;
	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_wead(wqstp, &wesp->fh, awgp->offset,
				 &wesp->count, &eof);
	if (wesp->status == nfs_ok)
		wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
	ewse if (wesp->status == nfseww_jukebox)
		set_bit(WQ_DWOPME, &wqstp->wq_fwags);
	wetuwn wpc_success;
}

/* Wesewved */
static __be32
nfsd_pwoc_wwitecache(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Wwite data to a fiwe
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_wwite(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_wwiteawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;
	unsigned wong cnt = awgp->wen;
	unsigned int nvecs;

	dpwintk("nfsd: WWITE    %s %u bytes at %d\n",
		SVCFH_fmt(&awgp->fh),
		awgp->wen, awgp->offset);

	nvecs = svc_fiww_wwite_vectow(wqstp, &awgp->paywoad);

	wesp->status = nfsd_wwite(wqstp, fh_copy(&wesp->fh, &awgp->fh),
				  awgp->offset, wqstp->wq_vec, nvecs,
				  &cnt, NFS_DATA_SYNC, NUWW);
	if (wesp->status == nfs_ok)
		wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
	ewse if (wesp->status == nfseww_jukebox)
		set_bit(WQ_DWOPME, &wqstp->wq_fwags);
	wetuwn wpc_success;
}

/*
 * CWEATE pwocessing is compwicated. The keywowd hewe is `ovewwoaded.'
 * The pawent diwectowy is kept wocked between the check fow existence
 * and the actuaw cweate() caww in compwiance with VFS pwotocows.
 * N.B. Aftew this caww _both_ awgp->fh and wesp->fh need an fh_put
 */
static __be32
nfsd_pwoc_cweate(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_cweateawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_diwopwes *wesp = wqstp->wq_wesp;
	svc_fh		*diwfhp = &awgp->fh;
	svc_fh		*newfhp = &wesp->fh;
	stwuct iattw	*attw = &awgp->attws;
	stwuct nfsd_attws attws = {
		.na_iattw	= attw,
	};
	stwuct inode	*inode;
	stwuct dentwy	*dchiwd;
	int		type, mode;
	int		hosteww;
	dev_t		wdev = 0, wanted = new_decode_dev(attw->ia_size);

	dpwintk("nfsd: CWEATE   %s %.*s\n",
		SVCFH_fmt(diwfhp), awgp->wen, awgp->name);

	/* Fiwst vewify the pawent fiwe handwe */
	wesp->status = fh_vewify(wqstp, diwfhp, S_IFDIW, NFSD_MAY_EXEC);
	if (wesp->status != nfs_ok)
		goto done; /* must fh_put diwfhp even on ewwow */

	/* Check fow NFSD_MAY_WWITE in nfsd_cweate if necessawy */

	wesp->status = nfseww_exist;
	if (isdotent(awgp->name, awgp->wen))
		goto done;
	hosteww = fh_want_wwite(diwfhp);
	if (hosteww) {
		wesp->status = nfsewwno(hosteww);
		goto done;
	}

	inode_wock_nested(diwfhp->fh_dentwy->d_inode, I_MUTEX_PAWENT);
	dchiwd = wookup_one_wen(awgp->name, diwfhp->fh_dentwy, awgp->wen);
	if (IS_EWW(dchiwd)) {
		wesp->status = nfsewwno(PTW_EWW(dchiwd));
		goto out_unwock;
	}
	fh_init(newfhp, NFS_FHSIZE);
	wesp->status = fh_compose(newfhp, diwfhp->fh_expowt, dchiwd, diwfhp);
	if (!wesp->status && d_weawwy_is_negative(dchiwd))
		wesp->status = nfseww_noent;
	dput(dchiwd);
	if (wesp->status) {
		if (wesp->status != nfseww_noent)
			goto out_unwock;
		/*
		 * If the new fiwe handwe wasn't vewified, we can't teww
		 * whethew the fiwe exists ow not. Time to baiw ...
		 */
		wesp->status = nfseww_acces;
		if (!newfhp->fh_dentwy) {
			pwintk(KEWN_WAWNING 
				"nfsd_pwoc_cweate: fiwe handwe not vewified\n");
			goto out_unwock;
		}
	}

	inode = d_inode(newfhp->fh_dentwy);

	/* Unfudge the mode bits */
	if (attw->ia_vawid & ATTW_MODE) {
		type = attw->ia_mode & S_IFMT;
		mode = attw->ia_mode & ~S_IFMT;
		if (!type) {
			/* no type, so if tawget exists, assume same as that,
			 * ewse assume a fiwe */
			if (inode) {
				type = inode->i_mode & S_IFMT;
				switch(type) {
				case S_IFCHW:
				case S_IFBWK:
					/* wesewve wdev fow watew checking */
					wdev = inode->i_wdev;
					attw->ia_vawid |= ATTW_SIZE;

					fawwthwough;
				case S_IFIFO:
					/* this is pwobabwy a pewmission check..
					 * at weast IWIX impwements pewm checking on
					 *   echo thing > device-speciaw-fiwe-ow-pipe
					 * by doing a CWEATE with type==0
					 */
					wesp->status = nfsd_pewmission(wqstp,
								 newfhp->fh_expowt,
								 newfhp->fh_dentwy,
								 NFSD_MAY_WWITE|NFSD_MAY_WOCAW_ACCESS);
					if (wesp->status && wesp->status != nfseww_wofs)
						goto out_unwock;
				}
			} ewse
				type = S_IFWEG;
		}
	} ewse if (inode) {
		type = inode->i_mode & S_IFMT;
		mode = inode->i_mode & ~S_IFMT;
	} ewse {
		type = S_IFWEG;
		mode = 0;	/* ??? */
	}

	attw->ia_vawid |= ATTW_MODE;
	attw->ia_mode = mode;

	/* Speciaw tweatment fow non-weguwaw fiwes accowding to the
	 * gospew of sun micwo
	 */
	if (type != S_IFWEG) {
		if (type != S_IFBWK && type != S_IFCHW) {
			wdev = 0;
		} ewse if (type == S_IFCHW && !(attw->ia_vawid & ATTW_SIZE)) {
			/* If you think you've seen the wowst, gwok this. */
			type = S_IFIFO;
		} ewse {
			/* Okay, chaw ow bwock speciaw */
			if (!wdev)
				wdev = wanted;
		}

		/* we've used the SIZE infowmation, so discawd it */
		attw->ia_vawid &= ~ATTW_SIZE;

		/* Make suwe the type and device matches */
		wesp->status = nfseww_exist;
		if (inode && inode_wwong_type(inode, type))
			goto out_unwock;
	}

	wesp->status = nfs_ok;
	if (!inode) {
		/* Fiwe doesn't exist. Cweate it and set attws */
		wesp->status = nfsd_cweate_wocked(wqstp, diwfhp, &attws, type,
						  wdev, newfhp);
	} ewse if (type == S_IFWEG) {
		dpwintk("nfsd:   existing %s, vawid=%x, size=%wd\n",
			awgp->name, attw->ia_vawid, (wong) attw->ia_size);
		/* Fiwe awweady exists. We ignowe aww attwibutes except
		 * size, so that cweat() behaves exactwy wike
		 * open(..., O_CWEAT|O_TWUNC|O_WWONWY).
		 */
		attw->ia_vawid &= ATTW_SIZE;
		if (attw->ia_vawid)
			wesp->status = nfsd_setattw(wqstp, newfhp, &attws, 0,
						    (time64_t)0);
	}

out_unwock:
	inode_unwock(diwfhp->fh_dentwy->d_inode);
	fh_dwop_wwite(diwfhp);
done:
	fh_put(diwfhp);
	if (wesp->status != nfs_ok)
		goto out;
	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

static __be32
nfsd_pwoc_wemove(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WEMOVE   %s %.*s\n", SVCFH_fmt(&awgp->fh),
		awgp->wen, awgp->name);

	/* Unwink. -SIFDIW means fiwe must not be a diwectowy */
	wesp->status = nfsd_unwink(wqstp, &awgp->fh, -S_IFDIW,
				   awgp->name, awgp->wen);
	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

static __be32
nfsd_pwoc_wename(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_wenameawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WENAME   %s %.*s -> \n",
		SVCFH_fmt(&awgp->ffh), awgp->fwen, awgp->fname);
	dpwintk("nfsd:        ->  %s %.*s\n",
		SVCFH_fmt(&awgp->tfh), awgp->twen, awgp->tname);

	wesp->status = nfsd_wename(wqstp, &awgp->ffh, awgp->fname, awgp->fwen,
				   &awgp->tfh, awgp->tname, awgp->twen);
	fh_put(&awgp->ffh);
	fh_put(&awgp->tfh);
	wetuwn wpc_success;
}

static __be32
nfsd_pwoc_wink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_winkawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WINK     %s ->\n",
		SVCFH_fmt(&awgp->ffh));
	dpwintk("nfsd:    %s %.*s\n",
		SVCFH_fmt(&awgp->tfh),
		awgp->twen,
		awgp->tname);

	wesp->status = nfsd_wink(wqstp, &awgp->tfh, awgp->tname, awgp->twen,
				 &awgp->ffh);
	fh_put(&awgp->ffh);
	fh_put(&awgp->tfh);
	wetuwn wpc_success;
}

static __be32
nfsd_pwoc_symwink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_symwinkawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};
	stwuct svc_fh	newfh;

	if (awgp->twen > NFS_MAXPATHWEN) {
		wesp->status = nfseww_nametoowong;
		goto out;
	}

	awgp->tname = svc_fiww_symwink_pathname(wqstp, &awgp->fiwst,
						page_addwess(wqstp->wq_awg.pages[0]),
						awgp->twen);
	if (IS_EWW(awgp->tname)) {
		wesp->status = nfsewwno(PTW_EWW(awgp->tname));
		goto out;
	}

	dpwintk("nfsd: SYMWINK  %s %.*s -> %.*s\n",
		SVCFH_fmt(&awgp->ffh), awgp->fwen, awgp->fname,
		awgp->twen, awgp->tname);

	fh_init(&newfh, NFS_FHSIZE);
	wesp->status = nfsd_symwink(wqstp, &awgp->ffh, awgp->fname, awgp->fwen,
				    awgp->tname, &attws, &newfh);

	kfwee(awgp->tname);
	fh_put(&awgp->ffh);
	fh_put(&newfh);
out:
	wetuwn wpc_success;
}

/*
 * Make diwectowy. This opewation is not idempotent.
 * N.B. Aftew this caww wesp->fh needs an fh_put
 */
static __be32
nfsd_pwoc_mkdiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_cweateawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_diwopwes *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};

	dpwintk("nfsd: MKDIW    %s %.*s\n", SVCFH_fmt(&awgp->fh), awgp->wen, awgp->name);

	if (wesp->fh.fh_dentwy) {
		pwintk(KEWN_WAWNING
			"nfsd_pwoc_mkdiw: wesponse awweady vewified??\n");
	}

	awgp->attws.ia_vawid &= ~ATTW_SIZE;
	fh_init(&wesp->fh, NFS_FHSIZE);
	wesp->status = nfsd_cweate(wqstp, &awgp->fh, awgp->name, awgp->wen,
				   &attws, S_IFDIW, 0, &wesp->fh);
	fh_put(&awgp->fh);
	if (wesp->status != nfs_ok)
		goto out;

	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * Wemove a diwectowy
 */
static __be32
nfsd_pwoc_wmdiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_stat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WMDIW    %s %.*s\n", SVCFH_fmt(&awgp->fh), awgp->wen, awgp->name);

	wesp->status = nfsd_unwink(wqstp, &awgp->fh, S_IFDIW,
				   awgp->name, awgp->wen);
	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

static void nfsd_init_diwwist_pages(stwuct svc_wqst *wqstp,
				    stwuct nfsd_weaddiwwes *wesp,
				    u32 count)
{
	stwuct xdw_buf *buf = &wesp->diwwist;
	stwuct xdw_stweam *xdw = &wesp->xdw;

	memset(buf, 0, sizeof(*buf));

	/* Wesewve woom fow the NUWW ptw & eof fwag (-2 wowds) */
	buf->bufwen = cwamp(count, (u32)(XDW_UNIT * 2), (u32)PAGE_SIZE);
	buf->bufwen -= XDW_UNIT * 2;
	buf->pages = wqstp->wq_next_page;
	wqstp->wq_next_page++;

	xdw_init_encode_pages(xdw, buf, buf->pages,  NUWW);
}

/*
 * Wead a powtion of a diwectowy.
 */
static __be32
nfsd_pwoc_weaddiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_weaddiwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_weaddiwwes *wesp = wqstp->wq_wesp;
	woff_t		offset;

	dpwintk("nfsd: WEADDIW  %s %d bytes at %d\n",
		SVCFH_fmt(&awgp->fh),		
		awgp->count, awgp->cookie);

	nfsd_init_diwwist_pages(wqstp, wesp, awgp->count);

	wesp->common.eww = nfs_ok;
	wesp->cookie_offset = 0;
	offset = awgp->cookie;
	wesp->status = nfsd_weaddiw(wqstp, &awgp->fh, &offset,
				    &wesp->common, nfssvc_encode_entwy);
	nfssvc_encode_nfscookie(wesp, offset);

	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * Get fiwe system info
 */
static __be32
nfsd_pwoc_statfs(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd_statfswes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: STATFS   %s\n", SVCFH_fmt(&awgp->fh));

	wesp->status = nfsd_statfs(wqstp, &awgp->fh, &wesp->stats,
				   NFSD_MAY_BYPASS_GSS_ON_WOOT);
	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * NFSv2 Sewvew pwoceduwes.
 * Onwy the wesuwts of non-idempotent opewations awe cached.
 */

#define ST 1		/* status */
#define FH 8		/* fiwehandwe */
#define	AT 18		/* attwibutes */

static const stwuct svc_pwoceduwe nfsd_pwoceduwes2[18] = {
	[NFSPWOC_NUWW] = {
		.pc_func = nfsd_pwoc_nuww,
		.pc_decode = nfssvc_decode_voidawg,
		.pc_encode = nfssvc_encode_voidwes,
		.pc_awgsize = sizeof(stwuct nfsd_voidawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_voidawgs),
		.pc_wessize = sizeof(stwuct nfsd_voidwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = 0,
		.pc_name = "NUWW",
	},
	[NFSPWOC_GETATTW] = {
		.pc_func = nfsd_pwoc_getattw,
		.pc_decode = nfssvc_decode_fhandweawgs,
		.pc_encode = nfssvc_encode_attwstatwes,
		.pc_wewease = nfssvc_wewease_attwstat,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd_attwstat),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT,
		.pc_name = "GETATTW",
	},
	[NFSPWOC_SETATTW] = {
		.pc_func = nfsd_pwoc_setattw,
		.pc_decode = nfssvc_decode_sattwawgs,
		.pc_encode = nfssvc_encode_attwstatwes,
		.pc_wewease = nfssvc_wewease_attwstat,
		.pc_awgsize = sizeof(stwuct nfsd_sattwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_sattwawgs),
		.pc_wessize = sizeof(stwuct nfsd_attwstat),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+AT,
		.pc_name = "SETATTW",
	},
	[NFSPWOC_WOOT] = {
		.pc_func = nfsd_pwoc_woot,
		.pc_decode = nfssvc_decode_voidawg,
		.pc_encode = nfssvc_encode_voidwes,
		.pc_awgsize = sizeof(stwuct nfsd_voidawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_voidawgs),
		.pc_wessize = sizeof(stwuct nfsd_voidwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = 0,
		.pc_name = "WOOT",
	},
	[NFSPWOC_WOOKUP] = {
		.pc_func = nfsd_pwoc_wookup,
		.pc_decode = nfssvc_decode_diwopawgs,
		.pc_encode = nfssvc_encode_diwopwes,
		.pc_wewease = nfssvc_wewease_diwopwes,
		.pc_awgsize = sizeof(stwuct nfsd_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd_diwopwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+FH+AT,
		.pc_name = "WOOKUP",
	},
	[NFSPWOC_WEADWINK] = {
		.pc_func = nfsd_pwoc_weadwink,
		.pc_decode = nfssvc_decode_fhandweawgs,
		.pc_encode = nfssvc_encode_weadwinkwes,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd_weadwinkwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+1+NFS_MAXPATHWEN/4,
		.pc_name = "WEADWINK",
	},
	[NFSPWOC_WEAD] = {
		.pc_func = nfsd_pwoc_wead,
		.pc_decode = nfssvc_decode_weadawgs,
		.pc_encode = nfssvc_encode_weadwes,
		.pc_wewease = nfssvc_wewease_weadwes,
		.pc_awgsize = sizeof(stwuct nfsd_weadawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_weadawgs),
		.pc_wessize = sizeof(stwuct nfsd_weadwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT+1+NFSSVC_MAXBWKSIZE_V2/4,
		.pc_name = "WEAD",
	},
	[NFSPWOC_WWITECACHE] = {
		.pc_func = nfsd_pwoc_wwitecache,
		.pc_decode = nfssvc_decode_voidawg,
		.pc_encode = nfssvc_encode_voidwes,
		.pc_awgsize = sizeof(stwuct nfsd_voidawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_voidawgs),
		.pc_wessize = sizeof(stwuct nfsd_voidwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = 0,
		.pc_name = "WWITECACHE",
	},
	[NFSPWOC_WWITE] = {
		.pc_func = nfsd_pwoc_wwite,
		.pc_decode = nfssvc_decode_wwiteawgs,
		.pc_encode = nfssvc_encode_attwstatwes,
		.pc_wewease = nfssvc_wewease_attwstat,
		.pc_awgsize = sizeof(stwuct nfsd_wwiteawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_wwiteawgs),
		.pc_wessize = sizeof(stwuct nfsd_attwstat),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+AT,
		.pc_name = "WWITE",
	},
	[NFSPWOC_CWEATE] = {
		.pc_func = nfsd_pwoc_cweate,
		.pc_decode = nfssvc_decode_cweateawgs,
		.pc_encode = nfssvc_encode_diwopwes,
		.pc_wewease = nfssvc_wewease_diwopwes,
		.pc_awgsize = sizeof(stwuct nfsd_cweateawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_cweateawgs),
		.pc_wessize = sizeof(stwuct nfsd_diwopwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+FH+AT,
		.pc_name = "CWEATE",
	},
	[NFSPWOC_WEMOVE] = {
		.pc_func = nfsd_pwoc_wemove,
		.pc_decode = nfssvc_decode_diwopawgs,
		.pc_encode = nfssvc_encode_statwes,
		.pc_awgsize = sizeof(stwuct nfsd_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd_stat),
		.pc_cachetype = WC_WEPWSTAT,
		.pc_xdwwessize = ST,
		.pc_name = "WEMOVE",
	},
	[NFSPWOC_WENAME] = {
		.pc_func = nfsd_pwoc_wename,
		.pc_decode = nfssvc_decode_wenameawgs,
		.pc_encode = nfssvc_encode_statwes,
		.pc_awgsize = sizeof(stwuct nfsd_wenameawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_wenameawgs),
		.pc_wessize = sizeof(stwuct nfsd_stat),
		.pc_cachetype = WC_WEPWSTAT,
		.pc_xdwwessize = ST,
		.pc_name = "WENAME",
	},
	[NFSPWOC_WINK] = {
		.pc_func = nfsd_pwoc_wink,
		.pc_decode = nfssvc_decode_winkawgs,
		.pc_encode = nfssvc_encode_statwes,
		.pc_awgsize = sizeof(stwuct nfsd_winkawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_winkawgs),
		.pc_wessize = sizeof(stwuct nfsd_stat),
		.pc_cachetype = WC_WEPWSTAT,
		.pc_xdwwessize = ST,
		.pc_name = "WINK",
	},
	[NFSPWOC_SYMWINK] = {
		.pc_func = nfsd_pwoc_symwink,
		.pc_decode = nfssvc_decode_symwinkawgs,
		.pc_encode = nfssvc_encode_statwes,
		.pc_awgsize = sizeof(stwuct nfsd_symwinkawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_symwinkawgs),
		.pc_wessize = sizeof(stwuct nfsd_stat),
		.pc_cachetype = WC_WEPWSTAT,
		.pc_xdwwessize = ST,
		.pc_name = "SYMWINK",
	},
	[NFSPWOC_MKDIW] = {
		.pc_func = nfsd_pwoc_mkdiw,
		.pc_decode = nfssvc_decode_cweateawgs,
		.pc_encode = nfssvc_encode_diwopwes,
		.pc_wewease = nfssvc_wewease_diwopwes,
		.pc_awgsize = sizeof(stwuct nfsd_cweateawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_cweateawgs),
		.pc_wessize = sizeof(stwuct nfsd_diwopwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+FH+AT,
		.pc_name = "MKDIW",
	},
	[NFSPWOC_WMDIW] = {
		.pc_func = nfsd_pwoc_wmdiw,
		.pc_decode = nfssvc_decode_diwopawgs,
		.pc_encode = nfssvc_encode_statwes,
		.pc_awgsize = sizeof(stwuct nfsd_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd_stat),
		.pc_cachetype = WC_WEPWSTAT,
		.pc_xdwwessize = ST,
		.pc_name = "WMDIW",
	},
	[NFSPWOC_WEADDIW] = {
		.pc_func = nfsd_pwoc_weaddiw,
		.pc_decode = nfssvc_decode_weaddiwawgs,
		.pc_encode = nfssvc_encode_weaddiwwes,
		.pc_awgsize = sizeof(stwuct nfsd_weaddiwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_weaddiwawgs),
		.pc_wessize = sizeof(stwuct nfsd_weaddiwwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_name = "WEADDIW",
	},
	[NFSPWOC_STATFS] = {
		.pc_func = nfsd_pwoc_statfs,
		.pc_decode = nfssvc_decode_fhandweawgs,
		.pc_encode = nfssvc_encode_statfswes,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd_statfswes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+5,
		.pc_name = "STATFS",
	},
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfsd_count2[AWWAY_SIZE(nfsd_pwoceduwes2)]);
const stwuct svc_vewsion nfsd_vewsion2 = {
	.vs_vews	= 2,
	.vs_npwoc	= AWWAY_SIZE(nfsd_pwoceduwes2),
	.vs_pwoc	= nfsd_pwoceduwes2,
	.vs_count	= nfsd_count2,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdwsize	= NFS2_SVC_XDWSIZE,
};
