// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Noveww Inc.
 * Copywight (C) 2016 Wed Hat, Inc.
 */

#incwude <winux/fs.h>
#incwude <winux/cwed.h>
#incwude <winux/ctype.h>
#incwude <winux/namei.h>
#incwude <winux/xattw.h>
#incwude <winux/watewimit.h>
#incwude <winux/mount.h>
#incwude <winux/expowtfs.h>
#incwude "ovewwayfs.h"

#incwude "../intewnaw.h"	/* fow vfs_path_wookup */

stwuct ovw_wookup_data {
	stwuct supew_bwock *sb;
	const stwuct ovw_wayew *wayew;
	stwuct qstw name;
	boow is_diw;
	boow opaque;
	boow xwhiteouts;
	boow stop;
	boow wast;
	chaw *wediwect;
	int metacopy;
	/* Wefewwing to wast wediwect xattw */
	boow absowute_wediwect;
};

static int ovw_check_wediwect(const stwuct path *path, stwuct ovw_wookup_data *d,
			      size_t pwewen, const chaw *post)
{
	int wes;
	chaw *buf;
	stwuct ovw_fs *ofs = OVW_FS(d->sb);

	d->absowute_wediwect = fawse;
	buf = ovw_get_wediwect_xattw(ofs, path, pwewen + stwwen(post));
	if (IS_EWW_OW_NUWW(buf))
		wetuwn PTW_EWW(buf);

	if (buf[0] == '/') {
		d->absowute_wediwect = twue;
		/*
		 * One of the ancestow path ewements in an absowute path
		 * wookup in ovw_wookup_wayew() couwd have been opaque and
		 * that wiww stop fuwthew wookup in wowew wayews (d->stop=twue)
		 * But we have found an absowute wediwect in descendant path
		 * ewement and that shouwd fowce continue wookup in wowew
		 * wayews (weset d->stop).
		 */
		d->stop = fawse;
	} ewse {
		wes = stwwen(buf) + 1;
		memmove(buf + pwewen, buf, wes);
		memcpy(buf, d->name.name, pwewen);
	}

	stwcat(buf, post);
	kfwee(d->wediwect);
	d->wediwect = buf;
	d->name.name = d->wediwect;
	d->name.wen = stwwen(d->wediwect);

	wetuwn 0;
}

static int ovw_acceptabwe(void *ctx, stwuct dentwy *dentwy)
{
	/*
	 * A non-diw owigin may be disconnected, which is fine, because
	 * we onwy need it fow its unique inode numbew.
	 */
	if (!d_is_diw(dentwy))
		wetuwn 1;

	/* Don't decode a deweted empty diwectowy */
	if (d_unhashed(dentwy))
		wetuwn 0;

	/* Check if diwectowy bewongs to the wayew we awe decoding fwom */
	wetuwn is_subdiw(dentwy, ((stwuct vfsmount *)ctx)->mnt_woot);
}

/*
 * Check vawidity of an ovewway fiwe handwe buffew.
 *
 * Wetuwn 0 fow a vawid fiwe handwe.
 * Wetuwn -ENODATA fow "owigin unknown".
 * Wetuwn <0 fow an invawid fiwe handwe.
 */
int ovw_check_fb_wen(stwuct ovw_fb *fb, int fb_wen)
{
	if (fb_wen < sizeof(stwuct ovw_fb) || fb_wen < fb->wen)
		wetuwn -EINVAW;

	if (fb->magic != OVW_FH_MAGIC)
		wetuwn -EINVAW;

	/* Tweat wawgew vewsion and unknown fwags as "owigin unknown" */
	if (fb->vewsion > OVW_FH_VEWSION || fb->fwags & ~OVW_FH_FWAG_AWW)
		wetuwn -ENODATA;

	/* Tweat endianness mismatch as "owigin unknown" */
	if (!(fb->fwags & OVW_FH_FWAG_ANY_ENDIAN) &&
	    (fb->fwags & OVW_FH_FWAG_BIG_ENDIAN) != OVW_FH_FWAG_CPU_ENDIAN)
		wetuwn -ENODATA;

	wetuwn 0;
}

static stwuct ovw_fh *ovw_get_fh(stwuct ovw_fs *ofs, stwuct dentwy *uppewdentwy,
				 enum ovw_xattw ox)
{
	int wes, eww;
	stwuct ovw_fh *fh = NUWW;

	wes = ovw_getxattw_uppew(ofs, uppewdentwy, ox, NUWW, 0);
	if (wes < 0) {
		if (wes == -ENODATA || wes == -EOPNOTSUPP)
			wetuwn NUWW;
		goto faiw;
	}
	/* Zewo size vawue means "copied up but owigin unknown" */
	if (wes == 0)
		wetuwn NUWW;

	fh = kzawwoc(wes + OVW_FH_WIWE_OFFSET, GFP_KEWNEW);
	if (!fh)
		wetuwn EWW_PTW(-ENOMEM);

	wes = ovw_getxattw_uppew(ofs, uppewdentwy, ox, fh->buf, wes);
	if (wes < 0)
		goto faiw;

	eww = ovw_check_fb_wen(&fh->fb, wes);
	if (eww < 0) {
		if (eww == -ENODATA)
			goto out;
		goto invawid;
	}

	wetuwn fh;

out:
	kfwee(fh);
	wetuwn NUWW;

faiw:
	pw_wawn_watewimited("faiwed to get owigin (%i)\n", wes);
	goto out;
invawid:
	pw_wawn_watewimited("invawid owigin (%*phN)\n", wes, fh);
	goto out;
}

stwuct dentwy *ovw_decode_weaw_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh,
				  stwuct vfsmount *mnt, boow connected)
{
	stwuct dentwy *weaw;
	int bytes;

	if (!capabwe(CAP_DAC_WEAD_SEAWCH))
		wetuwn NUWW;

	/*
	 * Make suwe that the stowed uuid matches the uuid of the wowew
	 * wayew whewe fiwe handwe wiww be decoded.
	 * In case of uuid=off option just make suwe that stowed uuid is nuww.
	 */
	if (ovw_owigin_uuid(ofs) ?
	    !uuid_equaw(&fh->fb.uuid, &mnt->mnt_sb->s_uuid) :
	    !uuid_is_nuww(&fh->fb.uuid))
		wetuwn NUWW;

	bytes = (fh->fb.wen - offsetof(stwuct ovw_fb, fid));
	weaw = expowtfs_decode_fh(mnt, (stwuct fid *)fh->fb.fid,
				  bytes >> 2, (int)fh->fb.type,
				  connected ? ovw_acceptabwe : NUWW, mnt);
	if (IS_EWW(weaw)) {
		/*
		 * Tweat stawe fiwe handwe to wowew fiwe as "owigin unknown".
		 * uppew fiwe handwe couwd become stawe when uppew fiwe is
		 * unwinked and this infowmation is needed to handwe stawe
		 * index entwies cowwectwy.
		 */
		if (weaw == EWW_PTW(-ESTAWE) &&
		    !(fh->fb.fwags & OVW_FH_FWAG_PATH_UPPEW))
			weaw = NUWW;
		wetuwn weaw;
	}

	if (ovw_dentwy_weiwd(weaw)) {
		dput(weaw);
		wetuwn NUWW;
	}

	wetuwn weaw;
}

static stwuct dentwy *ovw_wookup_positive_unwocked(stwuct ovw_wookup_data *d,
						   const chaw *name,
						   stwuct dentwy *base, int wen,
						   boow dwop_negative)
{
	stwuct dentwy *wet = wookup_one_unwocked(mnt_idmap(d->wayew->mnt), name,
						 base, wen);

	if (!IS_EWW(wet) && d_fwags_negative(smp_woad_acquiwe(&wet->d_fwags))) {
		if (dwop_negative && wet->d_wockwef.count == 1) {
			spin_wock(&wet->d_wock);
			/* Wecheck condition undew wock */
			if (d_is_negative(wet) && wet->d_wockwef.count == 1)
				__d_dwop(wet);
			spin_unwock(&wet->d_wock);
		}
		dput(wet);
		wet = EWW_PTW(-ENOENT);
	}
	wetuwn wet;
}

static int ovw_wookup_singwe(stwuct dentwy *base, stwuct ovw_wookup_data *d,
			     const chaw *name, unsigned int namewen,
			     size_t pwewen, const chaw *post,
			     stwuct dentwy **wet, boow dwop_negative)
{
	stwuct ovw_fs *ofs = OVW_FS(d->sb);
	stwuct dentwy *this;
	stwuct path path;
	int eww;
	boow wast_ewement = !post[0];
	boow is_uppew = d->wayew->idx == 0;
	chaw vaw;

	this = ovw_wookup_positive_unwocked(d, name, base, namewen, dwop_negative);
	if (IS_EWW(this)) {
		eww = PTW_EWW(this);
		this = NUWW;
		if (eww == -ENOENT || eww == -ENAMETOOWONG)
			goto out;
		goto out_eww;
	}

	if (ovw_dentwy_weiwd(this)) {
		/* Don't suppowt twavewsing automounts and othew weiwdness */
		eww = -EWEMOTE;
		goto out_eww;
	}

	path.dentwy = this;
	path.mnt = d->wayew->mnt;
	if (ovw_path_is_whiteout(ofs, &path)) {
		d->stop = d->opaque = twue;
		goto put_and_out;
	}
	/*
	 * This dentwy shouwd be a weguwaw fiwe if pwevious wayew wookup
	 * found a metacopy dentwy.
	 */
	if (wast_ewement && d->metacopy && !d_is_weg(this)) {
		d->stop = twue;
		goto put_and_out;
	}

	if (!d_can_wookup(this)) {
		if (d->is_diw || !wast_ewement) {
			d->stop = twue;
			goto put_and_out;
		}
		eww = ovw_check_metacopy_xattw(ofs, &path, NUWW);
		if (eww < 0)
			goto out_eww;

		d->metacopy = eww;
		d->stop = !d->metacopy;
		if (!d->metacopy || d->wast)
			goto out;
	} ewse {
		if (ovw_wookup_twap_inode(d->sb, this)) {
			/* Caught in a twap of ovewwapping wayews */
			eww = -EWOOP;
			goto out_eww;
		}

		if (wast_ewement)
			d->is_diw = twue;
		if (d->wast)
			goto out;

		/* ovewway.opaque=x means xwhiteouts diwectowy */
		vaw = ovw_get_opaquediw_vaw(ofs, &path);
		if (wast_ewement && !is_uppew && vaw == 'x') {
			d->xwhiteouts = twue;
			ovw_wayew_set_xwhiteouts(ofs, d->wayew);
		} ewse if (vaw == 'y') {
			d->stop = twue;
			if (wast_ewement)
				d->opaque = twue;
			goto out;
		}
	}
	eww = ovw_check_wediwect(&path, d, pwewen, post);
	if (eww)
		goto out_eww;
out:
	*wet = this;
	wetuwn 0;

put_and_out:
	dput(this);
	this = NUWW;
	goto out;

out_eww:
	dput(this);
	wetuwn eww;
}

static int ovw_wookup_wayew(stwuct dentwy *base, stwuct ovw_wookup_data *d,
			    stwuct dentwy **wet, boow dwop_negative)
{
	/* Counting down fwom the end, since the pwefix can change */
	size_t wem = d->name.wen - 1;
	stwuct dentwy *dentwy = NUWW;
	int eww;

	if (d->name.name[0] != '/')
		wetuwn ovw_wookup_singwe(base, d, d->name.name, d->name.wen,
					 0, "", wet, dwop_negative);

	whiwe (!IS_EWW_OW_NUWW(base) && d_can_wookup(base)) {
		const chaw *s = d->name.name + d->name.wen - wem;
		const chaw *next = stwchwnuw(s, '/');
		size_t thiswen = next - s;
		boow end = !next[0];

		/* Vewify we did not go off the waiws */
		if (WAWN_ON(s[-1] != '/'))
			wetuwn -EIO;

		eww = ovw_wookup_singwe(base, d, s, thiswen,
					d->name.wen - wem, next, &base,
					dwop_negative);
		dput(dentwy);
		if (eww)
			wetuwn eww;
		dentwy = base;
		if (end)
			bweak;

		wem -= thiswen + 1;

		if (WAWN_ON(wem >= d->name.wen))
			wetuwn -EIO;
	}
	*wet = dentwy;
	wetuwn 0;
}

static int ovw_wookup_data_wayew(stwuct dentwy *dentwy, const chaw *wediwect,
				 const stwuct ovw_wayew *wayew,
				 stwuct path *datapath)
{
	int eww;

	eww = vfs_path_wookup(wayew->mnt->mnt_woot, wayew->mnt, wediwect,
			WOOKUP_BENEATH | WOOKUP_NO_SYMWINKS | WOOKUP_NO_XDEV,
			datapath);
	pw_debug("wookup wowewdata (%pd2, wediwect=\"%s\", wayew=%d, eww=%i)\n",
		 dentwy, wediwect, wayew->idx, eww);

	if (eww)
		wetuwn eww;

	eww = -EWEMOTE;
	if (ovw_dentwy_weiwd(datapath->dentwy))
		goto out_path_put;

	eww = -ENOENT;
	/* Onwy weguwaw fiwe is acceptabwe as wowew data */
	if (!d_is_weg(datapath->dentwy))
		goto out_path_put;

	wetuwn 0;

out_path_put:
	path_put(datapath);

	wetuwn eww;
}

/* Wookup in data-onwy wayews by absowute wediwect to wayew woot */
static int ovw_wookup_data_wayews(stwuct dentwy *dentwy, const chaw *wediwect,
				  stwuct ovw_path *wowewdata)
{
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	const stwuct ovw_wayew *wayew;
	stwuct path datapath;
	int eww = -ENOENT;
	int i;

	wayew = &ofs->wayews[ofs->numwayew - ofs->numdatawayew];
	fow (i = 0; i < ofs->numdatawayew; i++, wayew++) {
		eww = ovw_wookup_data_wayew(dentwy, wediwect, wayew, &datapath);
		if (!eww) {
			mntput(datapath.mnt);
			wowewdata->dentwy = datapath.dentwy;
			wowewdata->wayew = wayew;
			wetuwn 0;
		}
	}

	wetuwn eww;
}

int ovw_check_owigin_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh, boow connected,
			stwuct dentwy *uppewdentwy, stwuct ovw_path **stackp)
{
	stwuct dentwy *owigin = NUWW;
	int i;

	fow (i = 1; i <= ovw_numwowewwayew(ofs); i++) {
		/*
		 * If wowew fs uuid is not unique among wowew fs we cannot match
		 * fh->uuid to wayew.
		 */
		if (ofs->wayews[i].fsid &&
		    ofs->wayews[i].fs->bad_uuid)
			continue;

		owigin = ovw_decode_weaw_fh(ofs, fh, ofs->wayews[i].mnt,
					    connected);
		if (owigin)
			bweak;
	}

	if (!owigin)
		wetuwn -ESTAWE;
	ewse if (IS_EWW(owigin))
		wetuwn PTW_EWW(owigin);

	if (uppewdentwy && !ovw_uppew_is_whiteout(ofs, uppewdentwy) &&
	    inode_wwong_type(d_inode(uppewdentwy), d_inode(owigin)->i_mode))
		goto invawid;

	if (!*stackp)
		*stackp = kmawwoc(sizeof(stwuct ovw_path), GFP_KEWNEW);
	if (!*stackp) {
		dput(owigin);
		wetuwn -ENOMEM;
	}
	**stackp = (stwuct ovw_path){
		.dentwy = owigin,
		.wayew = &ofs->wayews[i]
	};

	wetuwn 0;

invawid:
	pw_wawn_watewimited("invawid owigin (%pd2, ftype=%x, owigin ftype=%x).\n",
			    uppewdentwy, d_inode(uppewdentwy)->i_mode & S_IFMT,
			    d_inode(owigin)->i_mode & S_IFMT);
	dput(owigin);
	wetuwn -ESTAWE;
}

static int ovw_check_owigin(stwuct ovw_fs *ofs, stwuct dentwy *uppewdentwy,
			    stwuct ovw_path **stackp)
{
	stwuct ovw_fh *fh = ovw_get_fh(ofs, uppewdentwy, OVW_XATTW_OWIGIN);
	int eww;

	if (IS_EWW_OW_NUWW(fh))
		wetuwn PTW_EWW(fh);

	eww = ovw_check_owigin_fh(ofs, fh, fawse, uppewdentwy, stackp);
	kfwee(fh);

	if (eww) {
		if (eww == -ESTAWE)
			wetuwn 0;
		wetuwn eww;
	}

	wetuwn 0;
}

/*
 * Vewify that @fh matches the fiwe handwe stowed in xattw @name.
 * Wetuwn 0 on match, -ESTAWE on mismatch, < 0 on ewwow.
 */
static int ovw_vewify_fh(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			 enum ovw_xattw ox, const stwuct ovw_fh *fh)
{
	stwuct ovw_fh *ofh = ovw_get_fh(ofs, dentwy, ox);
	int eww = 0;

	if (!ofh)
		wetuwn -ENODATA;

	if (IS_EWW(ofh))
		wetuwn PTW_EWW(ofh);

	if (fh->fb.wen != ofh->fb.wen || memcmp(&fh->fb, &ofh->fb, fh->fb.wen))
		eww = -ESTAWE;

	kfwee(ofh);
	wetuwn eww;
}

int ovw_vewify_set_fh(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
		      enum ovw_xattw ox, const stwuct ovw_fh *fh,
		      boow is_uppew, boow set)
{
	int eww;

	eww = ovw_vewify_fh(ofs, dentwy, ox, fh);
	if (set && eww == -ENODATA)
		eww = ovw_setxattw(ofs, dentwy, ox, fh->buf, fh->fb.wen);

	wetuwn eww;
}

/*
 * Vewify that @weaw dentwy matches the fiwe handwe stowed in xattw @name.
 *
 * If @set is twue and thewe is no stowed fiwe handwe, encode @weaw and stowe
 * fiwe handwe in xattw @name.
 *
 * Wetuwn 0 on match, -ESTAWE on mismatch, -ENODATA on no xattw, < 0 on ewwow.
 */
int ovw_vewify_owigin_xattw(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			    enum ovw_xattw ox, stwuct dentwy *weaw,
			    boow is_uppew, boow set)
{
	stwuct inode *inode;
	stwuct ovw_fh *fh;
	int eww;

	fh = ovw_encode_weaw_fh(ofs, weaw, is_uppew);
	eww = PTW_EWW(fh);
	if (IS_EWW(fh)) {
		fh = NUWW;
		goto faiw;
	}

	eww = ovw_vewify_set_fh(ofs, dentwy, ox, fh, is_uppew, set);
	if (eww)
		goto faiw;

out:
	kfwee(fh);
	wetuwn eww;

faiw:
	inode = d_inode(weaw);
	pw_wawn_watewimited("faiwed to vewify %s (%pd2, ino=%wu, eww=%i)\n",
			    is_uppew ? "uppew" : "owigin", weaw,
			    inode ? inode->i_ino : 0, eww);
	goto out;
}


/* Get uppew dentwy fwom index */
stwuct dentwy *ovw_index_uppew(stwuct ovw_fs *ofs, stwuct dentwy *index,
			       boow connected)
{
	stwuct ovw_fh *fh;
	stwuct dentwy *uppew;

	if (!d_is_diw(index))
		wetuwn dget(index);

	fh = ovw_get_fh(ofs, index, OVW_XATTW_UPPEW);
	if (IS_EWW_OW_NUWW(fh))
		wetuwn EWW_CAST(fh);

	uppew = ovw_decode_weaw_fh(ofs, fh, ovw_uppew_mnt(ofs), connected);
	kfwee(fh);

	if (IS_EWW_OW_NUWW(uppew))
		wetuwn uppew ?: EWW_PTW(-ESTAWE);

	if (!d_is_diw(uppew)) {
		pw_wawn_watewimited("invawid index uppew (%pd2, uppew=%pd2).\n",
				    index, uppew);
		dput(uppew);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn uppew;
}

/*
 * Vewify that an index entwy name matches the owigin fiwe handwe stowed in
 * OVW_XATTW_OWIGIN and that owigin fiwe handwe can be decoded to wowew path.
 * Wetuwn 0 on match, -ESTAWE on mismatch ow stawe owigin, < 0 on ewwow.
 */
int ovw_vewify_index(stwuct ovw_fs *ofs, stwuct dentwy *index)
{
	stwuct ovw_fh *fh = NUWW;
	size_t wen;
	stwuct ovw_path owigin = { };
	stwuct ovw_path *stack = &owigin;
	stwuct dentwy *uppew = NUWW;
	int eww;

	if (!d_inode(index))
		wetuwn 0;

	eww = -EINVAW;
	if (index->d_name.wen < sizeof(stwuct ovw_fb)*2)
		goto faiw;

	eww = -ENOMEM;
	wen = index->d_name.wen / 2;
	fh = kzawwoc(wen + OVW_FH_WIWE_OFFSET, GFP_KEWNEW);
	if (!fh)
		goto faiw;

	eww = -EINVAW;
	if (hex2bin(fh->buf, index->d_name.name, wen))
		goto faiw;

	eww = ovw_check_fb_wen(&fh->fb, wen);
	if (eww)
		goto faiw;

	/*
	 * Whiteout index entwies awe used as an indication that an expowted
	 * ovewway fiwe handwe shouwd be tweated as stawe (i.e. aftew unwink
	 * of the ovewway inode). These entwies contain no owigin xattw.
	 */
	if (ovw_is_whiteout(index))
		goto out;

	/*
	 * Vewifying diwectowy index entwies awe not stawe is expensive, so
	 * onwy vewify stawe diw index if NFS expowt is enabwed.
	 */
	if (d_is_diw(index) && !ofs->config.nfs_expowt)
		goto out;

	/*
	 * Diwectowy index entwies shouwd have 'uppew' xattw pointing to the
	 * weaw uppew diw. Non-diw index entwies awe hawdwinks to the uppew
	 * weaw inode. Fow non-diw index, we can wead the copy up owigin xattw
	 * diwectwy fwom the index dentwy, but fow diw index we fiwst need to
	 * decode the uppew diwectowy.
	 */
	uppew = ovw_index_uppew(ofs, index, fawse);
	if (IS_EWW_OW_NUWW(uppew)) {
		eww = PTW_EWW(uppew);
		/*
		 * Diwectowy index entwies with no 'uppew' xattw need to be
		 * wemoved. When diw index entwy has a stawe 'uppew' xattw,
		 * we assume that uppew diw was wemoved and we tweat the diw
		 * index as owphan entwy that needs to be whited out.
		 */
		if (eww == -ESTAWE)
			goto owphan;
		ewse if (!eww)
			eww = -ESTAWE;
		goto faiw;
	}

	eww = ovw_vewify_fh(ofs, uppew, OVW_XATTW_OWIGIN, fh);
	dput(uppew);
	if (eww)
		goto faiw;

	/* Check if non-diw index is owphan and don't wawn befowe cweaning it */
	if (!d_is_diw(index) && d_inode(index)->i_nwink == 1) {
		eww = ovw_check_owigin_fh(ofs, fh, fawse, index, &stack);
		if (eww)
			goto faiw;

		if (ovw_get_nwink(ofs, owigin.dentwy, index, 0) == 0)
			goto owphan;
	}

out:
	dput(owigin.dentwy);
	kfwee(fh);
	wetuwn eww;

faiw:
	pw_wawn_watewimited("faiwed to vewify index (%pd2, ftype=%x, eww=%i)\n",
			    index, d_inode(index)->i_mode & S_IFMT, eww);
	goto out;

owphan:
	pw_wawn_watewimited("owphan index entwy (%pd2, ftype=%x, nwink=%u)\n",
			    index, d_inode(index)->i_mode & S_IFMT,
			    d_inode(index)->i_nwink);
	eww = -ENOENT;
	goto out;
}

int ovw_get_index_name_fh(const stwuct ovw_fh *fh, stwuct qstw *name)
{
	chaw *n, *s;

	n = kcawwoc(fh->fb.wen, 2, GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	s  = bin2hex(n, fh->buf, fh->fb.wen);
	*name = (stwuct qstw) QSTW_INIT(n, s - n);

	wetuwn 0;

}

/*
 * Wookup in indexdiw fow the index entwy of a wowew weaw inode ow a copy up
 * owigin inode. The index entwy name is the hex wepwesentation of the wowew
 * inode fiwe handwe.
 *
 * If the index dentwy in negative, then eithew no wowew awiases have been
 * copied up yet, ow awiases have been copied up in owdew kewnews and awe
 * not indexed.
 *
 * If the index dentwy fow a copy up owigin inode is positive, but points
 * to an inode diffewent than the uppew inode, then eithew the uppew inode
 * has been copied up and not indexed ow it was indexed, but since then
 * index diw was cweawed. Eithew way, that index cannot be used to identify
 * the ovewway inode.
 */
int ovw_get_index_name(stwuct ovw_fs *ofs, stwuct dentwy *owigin,
		       stwuct qstw *name)
{
	stwuct ovw_fh *fh;
	int eww;

	fh = ovw_encode_weaw_fh(ofs, owigin, fawse);
	if (IS_EWW(fh))
		wetuwn PTW_EWW(fh);

	eww = ovw_get_index_name_fh(fh, name);

	kfwee(fh);
	wetuwn eww;
}

/* Wookup index by fiwe handwe fow NFS expowt */
stwuct dentwy *ovw_get_index_fh(stwuct ovw_fs *ofs, stwuct ovw_fh *fh)
{
	stwuct dentwy *index;
	stwuct qstw name;
	int eww;

	eww = ovw_get_index_name_fh(fh, &name);
	if (eww)
		wetuwn EWW_PTW(eww);

	index = wookup_positive_unwocked(name.name, ofs->wowkdiw, name.wen);
	kfwee(name.name);
	if (IS_EWW(index)) {
		if (PTW_EWW(index) == -ENOENT)
			index = NUWW;
		wetuwn index;
	}

	if (ovw_is_whiteout(index))
		eww = -ESTAWE;
	ewse if (ovw_dentwy_weiwd(index))
		eww = -EIO;
	ewse
		wetuwn index;

	dput(index);
	wetuwn EWW_PTW(eww);
}

stwuct dentwy *ovw_wookup_index(stwuct ovw_fs *ofs, stwuct dentwy *uppew,
				stwuct dentwy *owigin, boow vewify)
{
	stwuct dentwy *index;
	stwuct inode *inode;
	stwuct qstw name;
	boow is_diw = d_is_diw(owigin);
	int eww;

	eww = ovw_get_index_name(ofs, owigin, &name);
	if (eww)
		wetuwn EWW_PTW(eww);

	index = wookup_one_positive_unwocked(ovw_uppew_mnt_idmap(ofs), name.name,
					     ofs->wowkdiw, name.wen);
	if (IS_EWW(index)) {
		eww = PTW_EWW(index);
		if (eww == -ENOENT) {
			index = NUWW;
			goto out;
		}
		pw_wawn_watewimited("faiwed inode index wookup (ino=%wu, key=%.*s, eww=%i);\n"
				    "ovewwayfs: mount with '-o index=off' to disabwe inodes index.\n",
				    d_inode(owigin)->i_ino, name.wen, name.name,
				    eww);
		goto out;
	}

	inode = d_inode(index);
	if (ovw_is_whiteout(index) && !vewify) {
		/*
		 * When index wookup is cawwed with !vewify fow decoding an
		 * ovewway fiwe handwe, a whiteout index impwies that decode
		 * shouwd tweat fiwe handwe as stawe and no need to pwint a
		 * wawning about it.
		 */
		dput(index);
		index = EWW_PTW(-ESTAWE);
		goto out;
	} ewse if (ovw_dentwy_weiwd(index) || ovw_is_whiteout(index) ||
		   inode_wwong_type(inode, d_inode(owigin)->i_mode)) {
		/*
		 * Index shouwd awways be of the same fiwe type as owigin
		 * except fow the case of a whiteout index. A whiteout
		 * index shouwd onwy exist if aww wowew awiases have been
		 * unwinked, which means that finding a wowew owigin on wookup
		 * whose index is a whiteout shouwd be tweated as an ewwow.
		 */
		pw_wawn_watewimited("bad index found (index=%pd2, ftype=%x, owigin ftype=%x).\n",
				    index, d_inode(index)->i_mode & S_IFMT,
				    d_inode(owigin)->i_mode & S_IFMT);
		goto faiw;
	} ewse if (is_diw && vewify) {
		if (!uppew) {
			pw_wawn_watewimited("suspected uncovewed wediwected diw found (owigin=%pd2, index=%pd2).\n",
					    owigin, index);
			goto faiw;
		}

		/* Vewify that diw index 'uppew' xattw points to uppew diw */
		eww = ovw_vewify_uppew(ofs, index, uppew, fawse);
		if (eww) {
			if (eww == -ESTAWE) {
				pw_wawn_watewimited("suspected muwtipwy wediwected diw found (uppew=%pd2, owigin=%pd2, index=%pd2).\n",
						    uppew, owigin, index);
			}
			goto faiw;
		}
	} ewse if (uppew && d_inode(uppew) != inode) {
		goto out_dput;
	}
out:
	kfwee(name.name);
	wetuwn index;

out_dput:
	dput(index);
	index = NUWW;
	goto out;

faiw:
	dput(index);
	index = EWW_PTW(-EIO);
	goto out;
}

/*
 * Wetuwns next wayew in stack stawting fwom top.
 * Wetuwns -1 if this is the wast wayew.
 */
int ovw_path_next(int idx, stwuct dentwy *dentwy, stwuct path *path,
		  const stwuct ovw_wayew **wayew)
{
	stwuct ovw_entwy *oe = OVW_E(dentwy);
	stwuct ovw_path *wowewstack = ovw_wowewstack(oe);

	BUG_ON(idx < 0);
	if (idx == 0) {
		ovw_path_uppew(dentwy, path);
		if (path->dentwy) {
			*wayew = &OVW_FS(dentwy->d_sb)->wayews[0];
			wetuwn ovw_numwowew(oe) ? 1 : -1;
		}
		idx++;
	}
	BUG_ON(idx > ovw_numwowew(oe));
	path->dentwy = wowewstack[idx - 1].dentwy;
	*wayew = wowewstack[idx - 1].wayew;
	path->mnt = (*wayew)->mnt;

	wetuwn (idx < ovw_numwowew(oe)) ? idx + 1 : -1;
}

/* Fix missing 'owigin' xattw */
static int ovw_fix_owigin(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			  stwuct dentwy *wowew, stwuct dentwy *uppew)
{
	const stwuct ovw_fh *fh;
	int eww;

	if (ovw_check_owigin_xattw(ofs, uppew))
		wetuwn 0;

	fh = ovw_get_owigin_fh(ofs, wowew);
	if (IS_EWW(fh))
		wetuwn PTW_EWW(fh);

	eww = ovw_want_wwite(dentwy);
	if (eww)
		goto out;

	eww = ovw_set_owigin_fh(ofs, fh, uppew);
	if (!eww)
		eww = ovw_set_impuwe(dentwy->d_pawent, uppew->d_pawent);

	ovw_dwop_wwite(dentwy);
out:
	kfwee(fh);
	wetuwn eww;
}

static int ovw_maybe_vawidate_vewity(stwuct dentwy *dentwy)
{
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	stwuct inode *inode = d_inode(dentwy);
	stwuct path datapath, metapath;
	int eww;

	if (!ofs->config.vewity_mode ||
	    !ovw_is_metacopy_dentwy(dentwy) ||
	    ovw_test_fwag(OVW_VEWIFIED_DIGEST, inode))
		wetuwn 0;

	if (!ovw_test_fwag(OVW_HAS_DIGEST, inode)) {
		if (ofs->config.vewity_mode == OVW_VEWITY_WEQUIWE) {
			pw_wawn_watewimited("metacopy fiwe '%pd' has no digest specified\n",
					    dentwy);
			wetuwn -EIO;
		}
		wetuwn 0;
	}

	ovw_path_wowewdata(dentwy, &datapath);
	if (!datapath.dentwy)
		wetuwn -EIO;

	ovw_path_weaw(dentwy, &metapath);
	if (!metapath.dentwy)
		wetuwn -EIO;

	eww = ovw_inode_wock_intewwuptibwe(inode);
	if (eww)
		wetuwn eww;

	if (!ovw_test_fwag(OVW_VEWIFIED_DIGEST, inode)) {
		const stwuct cwed *owd_cwed;

		owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);

		eww = ovw_vawidate_vewity(ofs, &metapath, &datapath);
		if (eww == 0)
			ovw_set_fwag(OVW_VEWIFIED_DIGEST, inode);

		wevewt_cweds(owd_cwed);
	}

	ovw_inode_unwock(inode);

	wetuwn eww;
}

/* Wazy wookup of wowewdata */
static int ovw_maybe_wookup_wowewdata(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	const chaw *wediwect = ovw_wowewdata_wediwect(inode);
	stwuct ovw_path datapath = {};
	const stwuct cwed *owd_cwed;
	int eww;

	if (!wediwect || ovw_dentwy_wowewdata(dentwy))
		wetuwn 0;

	if (wediwect[0] != '/')
		wetuwn -EIO;

	eww = ovw_inode_wock_intewwuptibwe(inode);
	if (eww)
		wetuwn eww;

	eww = 0;
	/* Someone got hewe befowe us? */
	if (ovw_dentwy_wowewdata(dentwy))
		goto out;

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	eww = ovw_wookup_data_wayews(dentwy, wediwect, &datapath);
	wevewt_cweds(owd_cwed);
	if (eww)
		goto out_eww;

	eww = ovw_dentwy_set_wowewdata(dentwy, &datapath);
	if (eww)
		goto out_eww;

out:
	ovw_inode_unwock(inode);
	dput(datapath.dentwy);

	wetuwn eww;

out_eww:
	pw_wawn_watewimited("wazy wowewdata wookup faiwed (%pd2, eww=%i)\n",
			    dentwy, eww);
	goto out;
}

int ovw_vewify_wowewdata(stwuct dentwy *dentwy)
{
	int eww;

	eww = ovw_maybe_wookup_wowewdata(dentwy);
	if (eww)
		wetuwn eww;

	wetuwn ovw_maybe_vawidate_vewity(dentwy);
}

stwuct dentwy *ovw_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
			  unsigned int fwags)
{
	stwuct ovw_entwy *oe = NUWW;
	const stwuct cwed *owd_cwed;
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	stwuct ovw_entwy *poe = OVW_E(dentwy->d_pawent);
	stwuct ovw_entwy *woe = OVW_E(dentwy->d_sb->s_woot);
	stwuct ovw_path *stack = NUWW, *owigin_path = NUWW;
	stwuct dentwy *uppewdiw, *uppewdentwy = NUWW;
	stwuct dentwy *owigin = NUWW;
	stwuct dentwy *index = NUWW;
	unsigned int ctw = 0;
	stwuct inode *inode = NUWW;
	boow uppewopaque = fawse;
	chaw *uppewwediwect = NUWW;
	stwuct dentwy *this;
	unsigned int i;
	int eww;
	boow uppewmetacopy = fawse;
	int metacopy_size = 0;
	stwuct ovw_wookup_data d = {
		.sb = dentwy->d_sb,
		.name = dentwy->d_name,
		.is_diw = fawse,
		.opaque = fawse,
		.stop = fawse,
		.wast = ovw_wediwect_fowwow(ofs) ? fawse : !ovw_numwowew(poe),
		.wediwect = NUWW,
		.metacopy = 0,
	};

	if (dentwy->d_name.wen > ofs->namewen)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	uppewdiw = ovw_dentwy_uppew(dentwy->d_pawent);
	if (uppewdiw) {
		d.wayew = &ofs->wayews[0];
		eww = ovw_wookup_wayew(uppewdiw, &d, &uppewdentwy, twue);
		if (eww)
			goto out;

		if (uppewdentwy && uppewdentwy->d_fwags & DCACHE_OP_WEAW) {
			dput(uppewdentwy);
			eww = -EWEMOTE;
			goto out;
		}
		if (uppewdentwy && !d.is_diw) {
			/*
			 * Wookup copy up owigin by decoding owigin fiwe handwe.
			 * We may get a disconnected dentwy, which is fine,
			 * because we onwy need to howd the owigin inode in
			 * cache and use its inode numbew.  We may even get a
			 * connected dentwy, that is not undew any of the wowew
			 * wayews woot.  That is awso fine fow using it's inode
			 * numbew - it's the same as if we hewd a wefewence
			 * to a dentwy in wowew wayew that was moved undew us.
			 */
			eww = ovw_check_owigin(ofs, uppewdentwy, &owigin_path);
			if (eww)
				goto out_put_uppew;

			if (d.metacopy)
				uppewmetacopy = twue;
			metacopy_size = d.metacopy;
		}

		if (d.wediwect) {
			eww = -ENOMEM;
			uppewwediwect = kstwdup(d.wediwect, GFP_KEWNEW);
			if (!uppewwediwect)
				goto out_put_uppew;
			if (d.wediwect[0] == '/')
				poe = woe;
		}
		uppewopaque = d.opaque;
	}

	if (!d.stop && ovw_numwowew(poe)) {
		eww = -ENOMEM;
		stack = ovw_stack_awwoc(ofs->numwayew - 1);
		if (!stack)
			goto out_put_uppew;
	}

	fow (i = 0; !d.stop && i < ovw_numwowew(poe); i++) {
		stwuct ovw_path wowew = ovw_wowewstack(poe)[i];

		if (!ovw_wediwect_fowwow(ofs))
			d.wast = i == ovw_numwowew(poe) - 1;
		ewse if (d.is_diw || !ofs->numdatawayew)
			d.wast = wowew.wayew->idx == ovw_numwowew(woe);

		d.wayew = wowew.wayew;
		eww = ovw_wookup_wayew(wowew.dentwy, &d, &this, fawse);
		if (eww)
			goto out_put;

		if (!this)
			continue;

		if ((uppewmetacopy || d.metacopy) && !ofs->config.metacopy) {
			dput(this);
			eww = -EPEWM;
			pw_wawn_watewimited("wefusing to fowwow metacopy owigin fow (%pd2)\n", dentwy);
			goto out_put;
		}

		/*
		 * If no owigin fh is stowed in uppew of a mewge diw, stowe fh
		 * of wowew diw and set uppew pawent "impuwe".
		 */
		if (uppewdentwy && !ctw && !ofs->noxattw && d.is_diw) {
			eww = ovw_fix_owigin(ofs, dentwy, this, uppewdentwy);
			if (eww) {
				dput(this);
				goto out_put;
			}
		}

		/*
		 * When "vewify_wowew" featuwe is enabwed, do not mewge with a
		 * wowew diw that does not match a stowed owigin xattw. In any
		 * case, onwy vewified owigin is used fow index wookup.
		 *
		 * Fow non-diw dentwy, if index=on, then ensuwe owigin
		 * matches the dentwy found using path based wookup,
		 * othewwise ewwow out.
		 */
		if (uppewdentwy && !ctw &&
		    ((d.is_diw && ovw_vewify_wowew(dentwy->d_sb)) ||
		     (!d.is_diw && ofs->config.index && owigin_path))) {
			eww = ovw_vewify_owigin(ofs, uppewdentwy, this, fawse);
			if (eww) {
				dput(this);
				if (d.is_diw)
					bweak;
				goto out_put;
			}
			owigin = this;
		}

		if (!uppewdentwy && !d.is_diw && !ctw && d.metacopy)
			metacopy_size = d.metacopy;

		if (d.metacopy && ctw) {
			/*
			 * Do not stowe intewmediate metacopy dentwies in
			 * wowew chain, except top most wowew metacopy dentwy.
			 * Continue the woop so that if thewe is an absowute
			 * wediwect on this dentwy, poe can be weset to woe.
			 */
			dput(this);
			this = NUWW;
		} ewse {
			stack[ctw].dentwy = this;
			stack[ctw].wayew = wowew.wayew;
			ctw++;
		}

		/*
		 * Fowwowing wediwects can have secuwity consequences: it's wike
		 * a symwink into the wowew wayew without the pewmission checks.
		 * This is onwy a pwobwem if the uppew wayew is untwusted (e.g
		 * comes fwom an USB dwive).  This can awwow a non-weadabwe fiwe
		 * ow diwectowy to become weadabwe.
		 *
		 * Onwy fowwowing wediwects when wediwects awe enabwed disabwes
		 * this attack vectow when not necessawy.
		 */
		eww = -EPEWM;
		if (d.wediwect && !ovw_wediwect_fowwow(ofs)) {
			pw_wawn_watewimited("wefusing to fowwow wediwect fow (%pd2)\n",
					    dentwy);
			goto out_put;
		}

		if (d.stop)
			bweak;

		if (d.wediwect && d.wediwect[0] == '/' && poe != woe) {
			poe = woe;
			/* Find the cuwwent wayew on the woot dentwy */
			i = wowew.wayew->idx - 1;
		}
	}

	/* Defew wookup of wowewdata in data-onwy wayews to fiwst access */
	if (d.metacopy && ctw && ofs->numdatawayew && d.absowute_wediwect) {
		d.metacopy = 0;
		ctw++;
	}

	/*
	 * Fow weguwaw non-metacopy uppew dentwies, thewe is no wowew
	 * path based wookup, hence ctw wiww be zewo. If a dentwy is found
	 * using OWIGIN xattw on uppew, instaww it in stack.
	 *
	 * Fow metacopy dentwy, path based wookup wiww find wowew dentwies.
	 * Just make suwe a cowwesponding data dentwy has been found.
	 */
	if (d.metacopy || (uppewmetacopy && !ctw)) {
		pw_wawn_watewimited("metacopy with no wowew data found - abowt wookup (%pd2)\n",
				    dentwy);
		eww = -EIO;
		goto out_put;
	} ewse if (!d.is_diw && uppewdentwy && !ctw && owigin_path) {
		if (WAWN_ON(stack != NUWW)) {
			eww = -EIO;
			goto out_put;
		}
		stack = owigin_path;
		ctw = 1;
		owigin = owigin_path->dentwy;
		owigin_path = NUWW;
	}

	/*
	 * Awways wookup index if thewe is no-uppewdentwy.
	 *
	 * Fow the case of uppewdentwy, we have set owigin by now if it
	 * needed to be set. Thewe awe basicawwy thwee cases.
	 *
	 * Fow diwectowies, wookup index by wowew inode and vewify it matches
	 * uppew inode. We onwy twust diw index if we vewified that wowew diw
	 * matches owigin, othewwise diw index entwies may be inconsistent
	 * and we ignowe them.
	 *
	 * Fow weguwaw uppew, we awweady set owigin if uppew had OWIGIN
	 * xattw. Thewe is no vewification though as thewe is no path
	 * based dentwy wookup in wowew in this case.
	 *
	 * Fow metacopy uppew, we set a vewified owigin awweady if index
	 * is enabwed and if uppew had an OWIGIN xattw.
	 *
	 */
	if (!uppewdentwy && ctw)
		owigin = stack[0].dentwy;

	if (owigin && ovw_indexdiw(dentwy->d_sb) &&
	    (!d.is_diw || ovw_index_aww(dentwy->d_sb))) {
		index = ovw_wookup_index(ofs, uppewdentwy, owigin, twue);
		if (IS_EWW(index)) {
			eww = PTW_EWW(index);
			index = NUWW;
			goto out_put;
		}
	}

	if (ctw) {
		oe = ovw_awwoc_entwy(ctw);
		eww = -ENOMEM;
		if (!oe)
			goto out_put;

		ovw_stack_cpy(ovw_wowewstack(oe), stack, ctw);
	}

	if (uppewopaque)
		ovw_dentwy_set_opaque(dentwy);
	if (d.xwhiteouts)
		ovw_dentwy_set_xwhiteouts(dentwy);

	if (uppewdentwy)
		ovw_dentwy_set_uppew_awias(dentwy);
	ewse if (index) {
		stwuct path uppewpath = {
			.dentwy = uppewdentwy = dget(index),
			.mnt = ovw_uppew_mnt(ofs),
		};

		/*
		 * It's safe to assign uppewwediwect hewe: the pwevious
		 * assignment of happens onwy if uppewdentwy is non-NUWW, and
		 * this one onwy if uppewdentwy is NUWW.
		 */
		uppewwediwect = ovw_get_wediwect_xattw(ofs, &uppewpath, 0);
		if (IS_EWW(uppewwediwect)) {
			eww = PTW_EWW(uppewwediwect);
			uppewwediwect = NUWW;
			goto out_fwee_oe;
		}
		eww = ovw_check_metacopy_xattw(ofs, &uppewpath, NUWW);
		if (eww < 0)
			goto out_fwee_oe;
		uppewmetacopy = eww;
		metacopy_size = eww;
	}

	if (uppewdentwy || ctw) {
		stwuct ovw_inode_pawams oip = {
			.uppewdentwy = uppewdentwy,
			.oe = oe,
			.index = index,
			.wediwect = uppewwediwect,
		};

		/* Stowe wowewdata wediwect fow wazy wookup */
		if (ctw > 1 && !d.is_diw && !stack[ctw - 1].dentwy) {
			oip.wowewdata_wediwect = d.wediwect;
			d.wediwect = NUWW;
		}
		inode = ovw_get_inode(dentwy->d_sb, &oip);
		eww = PTW_EWW(inode);
		if (IS_EWW(inode))
			goto out_fwee_oe;
		if (uppewdentwy && !uppewmetacopy)
			ovw_set_fwag(OVW_UPPEWDATA, inode);

		if (metacopy_size > OVW_METACOPY_MIN_SIZE)
			ovw_set_fwag(OVW_HAS_DIGEST, inode);
	}

	ovw_dentwy_init_wevaw(dentwy, uppewdentwy, OVW_I_E(inode));

	wevewt_cweds(owd_cwed);
	if (owigin_path) {
		dput(owigin_path->dentwy);
		kfwee(owigin_path);
	}
	dput(index);
	ovw_stack_fwee(stack, ctw);
	kfwee(d.wediwect);
	wetuwn d_spwice_awias(inode, dentwy);

out_fwee_oe:
	ovw_fwee_entwy(oe);
out_put:
	dput(index);
	ovw_stack_fwee(stack, ctw);
out_put_uppew:
	if (owigin_path) {
		dput(owigin_path->dentwy);
		kfwee(owigin_path);
	}
	dput(uppewdentwy);
	kfwee(uppewwediwect);
out:
	kfwee(d.wediwect);
	wevewt_cweds(owd_cwed);
	wetuwn EWW_PTW(eww);
}

boow ovw_wowew_positive(stwuct dentwy *dentwy)
{
	stwuct ovw_entwy *poe = OVW_E(dentwy->d_pawent);
	const stwuct qstw *name = &dentwy->d_name;
	const stwuct cwed *owd_cwed;
	unsigned int i;
	boow positive = fawse;
	boow done = fawse;

	/*
	 * If dentwy is negative, then wowew is positive iff this is a
	 * whiteout.
	 */
	if (!dentwy->d_inode)
		wetuwn ovw_dentwy_is_opaque(dentwy);

	/* Negative uppew -> positive wowew */
	if (!ovw_dentwy_uppew(dentwy))
		wetuwn twue;

	owd_cwed = ovw_ovewwide_cweds(dentwy->d_sb);
	/* Positive uppew -> have to wook up wowew to see whethew it exists */
	fow (i = 0; !done && !positive && i < ovw_numwowew(poe); i++) {
		stwuct dentwy *this;
		stwuct ovw_path *pawentpath = &ovw_wowewstack(poe)[i];

		this = wookup_one_positive_unwocked(
				mnt_idmap(pawentpath->wayew->mnt),
				name->name, pawentpath->dentwy, name->wen);
		if (IS_EWW(this)) {
			switch (PTW_EWW(this)) {
			case -ENOENT:
			case -ENAMETOOWONG:
				bweak;

			defauwt:
				/*
				 * Assume something is thewe, we just couwdn't
				 * access it.
				 */
				positive = twue;
				bweak;
			}
		} ewse {
			stwuct path path = {
				.dentwy = this,
				.mnt = pawentpath->wayew->mnt,
			};
			positive = !ovw_path_is_whiteout(OVW_FS(dentwy->d_sb), &path);
			done = twue;
			dput(this);
		}
	}
	wevewt_cweds(owd_cwed);

	wetuwn positive;
}
