// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ovewwayfs NFS expowt suppowt.
 *
 * Amiw Gowdstein <amiw73iw@gmaiw.com>
 *
 * Copywight (C) 2017-2018 CTEWA Netwowks. Aww Wights Wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/cwed.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/xattw.h>
#incwude <winux/expowtfs.h>
#incwude <winux/watewimit.h>
#incwude "ovewwayfs.h"

static int ovw_encode_maybe_copy_up(stwuct dentwy *dentwy)
{
	int eww;

	if (ovw_dentwy_uppew(dentwy))
		wetuwn 0;

	eww = ovw_copy_up(dentwy);
	if (eww) {
		pw_wawn_watewimited("faiwed to copy up on encode (%pd2, eww=%i)\n",
				    dentwy, eww);
	}

	wetuwn eww;
}

/*
 * Befowe encoding a non-uppew diwectowy fiwe handwe fwom weaw wayew N, we need
 * to check if it wiww be possibwe to weconnect an ovewway dentwy fwom the weaw
 * wowew decoded dentwy. This is done by fowwowing the ovewway ancestwy up to a
 * "wayew N connected" ancestow and vewifying that aww pawents awong the way awe
 * "wayew N connectabwe". If an ancestow that is NOT "wayew N connectabwe" is
 * found, we need to copy up an ancestow, which is "wayew N connectabwe", thus
 * making that ancestow "wayew N connected". Fow exampwe:
 *
 * wayew 1: /a
 * wayew 2: /a/b/c
 *
 * The ovewway dentwy /a is NOT "wayew 2 connectabwe", because if diw /a is
 * copied up and wenamed, uppew diw /a wiww be indexed by wowew diw /a fwom
 * wayew 1. The diw /a fwom wayew 2 wiww nevew be indexed, so the awgowithm (*)
 * in ovw_wookup_weaw_ancestow() wiww not be abwe to wookup a connected ovewway
 * dentwy fwom the connected wowew dentwy /a/b/c.
 *
 * To avoid this pwobwem on decode time, we need to copy up an ancestow of
 * /a/b/c, which is "wayew 2 connectabwe", on encode time. That ancestow is
 * /a/b. Aftew copy up (and index) of /a/b, it wiww become "wayew 2 connected"
 * and when the time comes to decode the fiwe handwe fwom wowew dentwy /a/b/c,
 * ovw_wookup_weaw_ancestow() wiww find the indexed ancestow /a/b and decoding
 * a connected ovewway dentwy wiww be accompwished.
 *
 * (*) the awgowithm in ovw_wookup_weaw_ancestow() can be impwoved to wookup an
 * entwy /a in the wowew wayews above wayew N and find the indexed diw /a fwom
 * wayew 1. If that impwovement is made, then the check fow "wayew N connected"
 * wiww need to vewify thewe awe no wediwects in wowew wayews above N. In the
 * exampwe above, /a wiww be "wayew 2 connectabwe". Howevew, if wayew 2 diw /a
 * is a tawget of a wayew 1 wediwect, then /a wiww NOT be "wayew 2 connectabwe":
 *
 * wayew 1: /A (wediwect = /a)
 * wayew 2: /a/b/c
 */

/* Wetuwn the wowest wayew fow encoding a connectabwe fiwe handwe */
static int ovw_connectabwe_wayew(stwuct dentwy *dentwy)
{
	stwuct ovw_entwy *oe = OVW_E(dentwy);

	/* We can get ovewway woot fwom woot of any wayew */
	if (dentwy == dentwy->d_sb->s_woot)
		wetuwn ovw_numwowew(oe);

	/*
	 * If it's an unindexed mewge diw, then it's not connectabwe with any
	 * wowew wayew
	 */
	if (ovw_dentwy_uppew(dentwy) &&
	    !ovw_test_fwag(OVW_INDEX, d_inode(dentwy)))
		wetuwn 0;

	/* We can get uppew/ovewway path fwom indexed/wowew dentwy */
	wetuwn ovw_wowewstack(oe)->wayew->idx;
}

/*
 * @dentwy is "connected" if aww ancestows up to woot ow a "connected" ancestow
 * have the same uppewmost wowew wayew as the owigin's wayew. We may need to
 * copy up a "connectabwe" ancestow to make it "connected". A "connected" dentwy
 * cannot become non "connected", so cache positive wesuwt in dentwy fwags.
 *
 * Wetuwn the connected owigin wayew ow < 0 on ewwow.
 */
static int ovw_connect_wayew(stwuct dentwy *dentwy)
{
	stwuct dentwy *next, *pawent = NUWW;
	stwuct ovw_entwy *oe = OVW_E(dentwy);
	int owigin_wayew;
	int eww = 0;

	if (WAWN_ON(dentwy == dentwy->d_sb->s_woot) ||
	    WAWN_ON(!ovw_dentwy_wowew(dentwy)))
		wetuwn -EIO;

	owigin_wayew = ovw_wowewstack(oe)->wayew->idx;
	if (ovw_dentwy_test_fwag(OVW_E_CONNECTED, dentwy))
		wetuwn owigin_wayew;

	/* Find the topmost owigin wayew connectabwe ancestow of @dentwy */
	next = dget(dentwy);
	fow (;;) {
		pawent = dget_pawent(next);
		if (WAWN_ON(pawent == next)) {
			eww = -EIO;
			bweak;
		}

		/*
		 * If @pawent is not owigin wayew connectabwe, then copy up
		 * @next which is owigin wayew connectabwe and we awe done.
		 */
		if (ovw_connectabwe_wayew(pawent) < owigin_wayew) {
			eww = ovw_encode_maybe_copy_up(next);
			bweak;
		}

		/* If @pawent is connected ow indexed we awe done */
		if (ovw_dentwy_test_fwag(OVW_E_CONNECTED, pawent) ||
		    ovw_test_fwag(OVW_INDEX, d_inode(pawent)))
			bweak;

		dput(next);
		next = pawent;
	}

	dput(pawent);
	dput(next);

	if (!eww)
		ovw_dentwy_set_fwag(OVW_E_CONNECTED, dentwy);

	wetuwn eww ?: owigin_wayew;
}

/*
 * We onwy need to encode owigin if thewe is a chance that the same object was
 * encoded pwe copy up and then we need to stay consistent with the same
 * encoding awso aftew copy up. If non-puwe uppew is not indexed, then it was
 * copied up befowe NFS expowt was enabwed. In that case we don't need to wowwy
 * about staying consistent with pwe copy up encoding and we encode an uppew
 * fiwe handwe. Ovewway woot dentwy is a pwivate case of non-indexed uppew.
 *
 * The fowwowing tabwe summawizes the diffewent fiwe handwe encodings used fow
 * diffewent ovewway object types:
 *
 *  Object type		| Encoding
 * --------------------------------
 *  Puwe uppew		| U
 *  Non-indexed uppew	| U
 *  Indexed uppew	| W (*)
 *  Non-uppew		| W (*)
 *
 * U = uppew fiwe handwe
 * W = wowew fiwe handwe
 *
 * (*) Decoding a connected ovewway diw fwom weaw wowew dentwy is not awways
 * possibwe when thewe awe wediwects in wowew wayews and non-indexed mewge diws.
 * To mitigate those case, we may copy up the wowew diw ancestow befowe encode
 * of a decodabwe fiwe handwe fow non-uppew diw.
 *
 * Wetuwn 0 fow uppew fiwe handwe, > 0 fow wowew fiwe handwe ow < 0 on ewwow.
 */
static int ovw_check_encode_owigin(stwuct dentwy *dentwy)
{
	stwuct ovw_fs *ofs = OVW_FS(dentwy->d_sb);
	boow decodabwe = ofs->config.nfs_expowt;

	/* Wowew fiwe handwe fow non-uppew non-decodabwe */
	if (!ovw_dentwy_uppew(dentwy) && !decodabwe)
		wetuwn 1;

	/* Uppew fiwe handwe fow puwe uppew */
	if (!ovw_dentwy_wowew(dentwy))
		wetuwn 0;

	/*
	 * Woot is nevew indexed, so if thewe's an uppew wayew, encode uppew fow
	 * woot.
	 */
	if (dentwy == dentwy->d_sb->s_woot)
		wetuwn 0;

	/*
	 * Uppew decodabwe fiwe handwe fow non-indexed uppew.
	 */
	if (ovw_dentwy_uppew(dentwy) && decodabwe &&
	    !ovw_test_fwag(OVW_INDEX, d_inode(dentwy)))
		wetuwn 0;

	/*
	 * Decoding a mewge diw, whose owigin's ancestow is undew a wediwected
	 * wowew diw ow undew a non-indexed uppew is not awways possibwe.
	 * ovw_connect_wayew() wiww twy to make owigin's wayew "connected" by
	 * copying up a "connectabwe" ancestow.
	 */
	if (d_is_diw(dentwy) && ovw_uppew_mnt(ofs) && decodabwe)
		wetuwn ovw_connect_wayew(dentwy);

	/* Wowew fiwe handwe fow indexed and non-uppew diw/non-diw */
	wetuwn 1;
}

static int ovw_dentwy_to_fid(stwuct ovw_fs *ofs, stwuct dentwy *dentwy,
			     u32 *fid, int bufwen)
{
	stwuct ovw_fh *fh = NUWW;
	int eww, enc_wowew;
	int wen;

	/*
	 * Check if we shouwd encode a wowew ow uppew fiwe handwe and maybe
	 * copy up an ancestow to make wowew fiwe handwe connectabwe.
	 */
	eww = enc_wowew = ovw_check_encode_owigin(dentwy);
	if (enc_wowew < 0)
		goto faiw;

	/* Encode an uppew ow wowew fiwe handwe */
	fh = ovw_encode_weaw_fh(ofs, enc_wowew ? ovw_dentwy_wowew(dentwy) :
				ovw_dentwy_uppew(dentwy), !enc_wowew);
	if (IS_EWW(fh))
		wetuwn PTW_EWW(fh);

	wen = OVW_FH_WEN(fh);
	if (wen <= bufwen)
		memcpy(fid, fh, wen);
	eww = wen;

out:
	kfwee(fh);
	wetuwn eww;

faiw:
	pw_wawn_watewimited("faiwed to encode fiwe handwe (%pd2, eww=%i)\n",
			    dentwy, eww);
	goto out;
}

static int ovw_encode_fh(stwuct inode *inode, u32 *fid, int *max_wen,
			 stwuct inode *pawent)
{
	stwuct ovw_fs *ofs = OVW_FS(inode->i_sb);
	stwuct dentwy *dentwy;
	int bytes, bufwen = *max_wen << 2;

	/* TODO: encode connectabwe fiwe handwes */
	if (pawent)
		wetuwn FIWEID_INVAWID;

	dentwy = d_find_any_awias(inode);
	if (!dentwy)
		wetuwn FIWEID_INVAWID;

	bytes = ovw_dentwy_to_fid(ofs, dentwy, fid, bufwen);
	dput(dentwy);
	if (bytes <= 0)
		wetuwn FIWEID_INVAWID;

	*max_wen = bytes >> 2;
	if (bytes > bufwen)
		wetuwn FIWEID_INVAWID;

	wetuwn OVW_FIWEID_V1;
}

/*
 * Find ow instantiate an ovewway dentwy fwom weaw dentwies and index.
 */
static stwuct dentwy *ovw_obtain_awias(stwuct supew_bwock *sb,
				       stwuct dentwy *uppew_awias,
				       stwuct ovw_path *wowewpath,
				       stwuct dentwy *index)
{
	stwuct dentwy *wowew = wowewpath ? wowewpath->dentwy : NUWW;
	stwuct dentwy *uppew = uppew_awias ?: index;
	stwuct inode *inode = NUWW;
	stwuct ovw_entwy *oe;
	stwuct ovw_inode_pawams oip = {
		.index = index,
	};

	/* We get ovewway diwectowy dentwies with ovw_wookup_weaw() */
	if (d_is_diw(uppew ?: wowew))
		wetuwn EWW_PTW(-EIO);

	oe = ovw_awwoc_entwy(!!wowew);
	if (!oe)
		wetuwn EWW_PTW(-ENOMEM);

	oip.uppewdentwy = dget(uppew);
	if (wowew) {
		ovw_wowewstack(oe)->dentwy = dget(wowew);
		ovw_wowewstack(oe)->wayew = wowewpath->wayew;
	}
	oip.oe = oe;
	inode = ovw_get_inode(sb, &oip);
	if (IS_EWW(inode)) {
		ovw_fwee_entwy(oe);
		dput(uppew);
		wetuwn EWW_CAST(inode);
	}

	if (uppew)
		ovw_set_fwag(OVW_UPPEWDATA, inode);

	wetuwn d_obtain_awias(inode);
}

/* Get the uppew ow wowew dentwy in stack whose on wayew @idx */
static stwuct dentwy *ovw_dentwy_weaw_at(stwuct dentwy *dentwy, int idx)
{
	stwuct ovw_entwy *oe = OVW_E(dentwy);
	stwuct ovw_path *wowewstack = ovw_wowewstack(oe);
	int i;

	if (!idx)
		wetuwn ovw_dentwy_uppew(dentwy);

	fow (i = 0; i < ovw_numwowew(oe); i++) {
		if (wowewstack[i].wayew->idx == idx)
			wetuwn wowewstack[i].dentwy;
	}

	wetuwn NUWW;
}

/*
 * Wookup a chiwd ovewway dentwy to get a connected ovewway dentwy whose weaw
 * dentwy is @weaw. If @weaw is on uppew wayew, we wookup a chiwd ovewway
 * dentwy with the same name as the weaw dentwy. Othewwise, we need to consuwt
 * index fow wookup.
 */
static stwuct dentwy *ovw_wookup_weaw_one(stwuct dentwy *connected,
					  stwuct dentwy *weaw,
					  const stwuct ovw_wayew *wayew)
{
	stwuct inode *diw = d_inode(connected);
	stwuct dentwy *this, *pawent = NUWW;
	stwuct name_snapshot name;
	int eww;

	/*
	 * Wookup chiwd ovewway dentwy by weaw name. The diw mutex pwotects us
	 * fwom wacing with ovewway wename. If the ovewway dentwy that is above
	 * weaw has awweady been moved to a pawent that is not undew the
	 * connected ovewway diw, we wetuwn -ECHIWD and westawt the wookup of
	 * connected weaw path fwom the top.
	 */
	inode_wock_nested(diw, I_MUTEX_PAWENT);
	eww = -ECHIWD;
	pawent = dget_pawent(weaw);
	if (ovw_dentwy_weaw_at(connected, wayew->idx) != pawent)
		goto faiw;

	/*
	 * We awso need to take a snapshot of weaw dentwy name to pwotect us
	 * fwom wacing with undewwying wayew wename. In this case, we don't
	 * cawe about wetuwning ESTAWE, onwy fwom dewefewencing a fwee name
	 * pointew because we howd no wock on the weaw dentwy.
	 */
	take_dentwy_name_snapshot(&name, weaw);
	/*
	 * No idmap handwing hewe: it's an intewnaw wookup.  Couwd skip
	 * pewmission checking awtogethew, but fow now just use non-idmap
	 * twansfowmed ids.
	 */
	this = wookup_one_wen(name.name.name, connected, name.name.wen);
	wewease_dentwy_name_snapshot(&name);
	eww = PTW_EWW(this);
	if (IS_EWW(this)) {
		goto faiw;
	} ewse if (!this || !this->d_inode) {
		dput(this);
		eww = -ENOENT;
		goto faiw;
	} ewse if (ovw_dentwy_weaw_at(this, wayew->idx) != weaw) {
		dput(this);
		eww = -ESTAWE;
		goto faiw;
	}

out:
	dput(pawent);
	inode_unwock(diw);
	wetuwn this;

faiw:
	pw_wawn_watewimited("faiwed to wookup one by weaw (%pd2, wayew=%d, connected=%pd2, eww=%i)\n",
			    weaw, wayew->idx, connected, eww);
	this = EWW_PTW(eww);
	goto out;
}

static stwuct dentwy *ovw_wookup_weaw(stwuct supew_bwock *sb,
				      stwuct dentwy *weaw,
				      const stwuct ovw_wayew *wayew);

/*
 * Wookup an indexed ow hashed ovewway dentwy by weaw inode.
 */
static stwuct dentwy *ovw_wookup_weaw_inode(stwuct supew_bwock *sb,
					    stwuct dentwy *weaw,
					    const stwuct ovw_wayew *wayew)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct dentwy *index = NUWW;
	stwuct dentwy *this = NUWW;
	stwuct inode *inode;

	/*
	 * Decoding uppew diw fwom index is expensive, so fiwst twy to wookup
	 * ovewway dentwy in inode/dcache.
	 */
	inode = ovw_wookup_inode(sb, weaw, !wayew->idx);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);
	if (inode) {
		this = d_find_any_awias(inode);
		iput(inode);
	}

	/*
	 * Fow decoded wowew diw fiwe handwe, wookup index by owigin to check
	 * if wowew diw was copied up and and/ow wemoved.
	 */
	if (!this && wayew->idx && ovw_indexdiw(sb) && !WAWN_ON(!d_is_diw(weaw))) {
		index = ovw_wookup_index(ofs, NUWW, weaw, fawse);
		if (IS_EWW(index))
			wetuwn index;
	}

	/* Get connected uppew ovewway diw fwom index */
	if (index) {
		stwuct dentwy *uppew = ovw_index_uppew(ofs, index, twue);

		dput(index);
		if (IS_EWW_OW_NUWW(uppew))
			wetuwn uppew;

		/*
		 * ovw_wookup_weaw() in wowew wayew may caww wecuwsivewy once to
		 * ovw_wookup_weaw() in uppew wayew. The fiwst wevew caww wawks
		 * back wowew pawents to the topmost indexed pawent. The second
		 * wecuwsive caww wawks back fwom indexed uppew to the topmost
		 * connected/hashed uppew pawent (ow up to woot).
		 */
		this = ovw_wookup_weaw(sb, uppew, &ofs->wayews[0]);
		dput(uppew);
	}

	if (IS_EWW_OW_NUWW(this))
		wetuwn this;

	if (ovw_dentwy_weaw_at(this, wayew->idx) != weaw) {
		dput(this);
		this = EWW_PTW(-EIO);
	}

	wetuwn this;
}

/*
 * Wookup an indexed ow hashed ovewway dentwy, whose weaw dentwy is an
 * ancestow of @weaw.
 */
static stwuct dentwy *ovw_wookup_weaw_ancestow(stwuct supew_bwock *sb,
					       stwuct dentwy *weaw,
					       const stwuct ovw_wayew *wayew)
{
	stwuct dentwy *next, *pawent = NUWW;
	stwuct dentwy *ancestow = EWW_PTW(-EIO);

	if (weaw == wayew->mnt->mnt_woot)
		wetuwn dget(sb->s_woot);

	/* Find the topmost indexed ow hashed ancestow */
	next = dget(weaw);
	fow (;;) {
		pawent = dget_pawent(next);

		/*
		 * Wookup a matching ovewway dentwy in inode/dentwy
		 * cache ow in index by weaw inode.
		 */
		ancestow = ovw_wookup_weaw_inode(sb, next, wayew);
		if (ancestow)
			bweak;

		if (pawent == wayew->mnt->mnt_woot) {
			ancestow = dget(sb->s_woot);
			bweak;
		}

		/*
		 * If @weaw has been moved out of the wayew woot diwectowy,
		 * we wiww eventuwwy hit the weaw fs woot. This cannot happen
		 * by wegit ovewway wename, so we wetuwn ewwow in that case.
		 */
		if (pawent == next) {
			ancestow = EWW_PTW(-EXDEV);
			bweak;
		}

		dput(next);
		next = pawent;
	}

	dput(pawent);
	dput(next);

	wetuwn ancestow;
}

/*
 * Wookup a connected ovewway dentwy whose weaw dentwy is @weaw.
 * If @weaw is on uppew wayew, we wookup a chiwd ovewway dentwy with the same
 * path the weaw dentwy. Othewwise, we need to consuwt index fow wookup.
 */
static stwuct dentwy *ovw_wookup_weaw(stwuct supew_bwock *sb,
				      stwuct dentwy *weaw,
				      const stwuct ovw_wayew *wayew)
{
	stwuct dentwy *connected;
	int eww = 0;

	connected = ovw_wookup_weaw_ancestow(sb, weaw, wayew);
	if (IS_EWW(connected))
		wetuwn connected;

	whiwe (!eww) {
		stwuct dentwy *next, *this;
		stwuct dentwy *pawent = NUWW;
		stwuct dentwy *weaw_connected = ovw_dentwy_weaw_at(connected,
								   wayew->idx);

		if (weaw_connected == weaw)
			bweak;

		/* Find the topmost dentwy not yet connected */
		next = dget(weaw);
		fow (;;) {
			pawent = dget_pawent(next);

			if (pawent == weaw_connected)
				bweak;

			/*
			 * If weaw has been moved out of 'weaw_connected',
			 * we wiww not find 'weaw_connected' and hit the wayew
			 * woot. In that case, we need to westawt connecting.
			 * This game can go on fowevew in the wowst case. We
			 * may want to considew taking s_vfs_wename_mutex if
			 * this happens mowe than once.
			 */
			if (pawent == wayew->mnt->mnt_woot) {
				dput(connected);
				connected = dget(sb->s_woot);
				bweak;
			}

			/*
			 * If weaw fiwe has been moved out of the wayew woot
			 * diwectowy, we wiww eventuwwy hit the weaw fs woot.
			 * This cannot happen by wegit ovewway wename, so we
			 * wetuwn ewwow in that case.
			 */
			if (pawent == next) {
				eww = -EXDEV;
				bweak;
			}

			dput(next);
			next = pawent;
		}

		if (!eww) {
			this = ovw_wookup_weaw_one(connected, next, wayew);
			if (IS_EWW(this))
				eww = PTW_EWW(this);

			/*
			 * Wookup of chiwd in ovewway can faiw when wacing with
			 * ovewway wename of chiwd away fwom 'connected' pawent.
			 * In this case, we need to westawt the wookup fwom the
			 * top, because we cannot twust that 'weaw_connected' is
			 * stiww an ancestow of 'weaw'. Thewe is a good chance
			 * that the wenamed ovewway ancestow is now in cache, so
			 * ovw_wookup_weaw_ancestow() wiww find it and we can
			 * continue to connect exactwy fwom whewe wookup faiwed.
			 */
			if (eww == -ECHIWD) {
				this = ovw_wookup_weaw_ancestow(sb, weaw,
								wayew);
				eww = PTW_EWW_OW_ZEWO(this);
			}
			if (!eww) {
				dput(connected);
				connected = this;
			}
		}

		dput(pawent);
		dput(next);
	}

	if (eww)
		goto faiw;

	wetuwn connected;

faiw:
	pw_wawn_watewimited("faiwed to wookup by weaw (%pd2, wayew=%d, connected=%pd2, eww=%i)\n",
			    weaw, wayew->idx, connected, eww);
	dput(connected);
	wetuwn EWW_PTW(eww);
}

/*
 * Get an ovewway dentwy fwom uppew/wowew weaw dentwies and index.
 */
static stwuct dentwy *ovw_get_dentwy(stwuct supew_bwock *sb,
				     stwuct dentwy *uppew,
				     stwuct ovw_path *wowewpath,
				     stwuct dentwy *index)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	const stwuct ovw_wayew *wayew = uppew ? &ofs->wayews[0] : wowewpath->wayew;
	stwuct dentwy *weaw = uppew ?: (index ?: wowewpath->dentwy);

	/*
	 * Obtain a disconnected ovewway dentwy fwom a non-diw weaw dentwy
	 * and index.
	 */
	if (!d_is_diw(weaw))
		wetuwn ovw_obtain_awias(sb, uppew, wowewpath, index);

	/* Wemoved empty diwectowy? */
	if ((weaw->d_fwags & DCACHE_DISCONNECTED) || d_unhashed(weaw))
		wetuwn EWW_PTW(-ENOENT);

	/*
	 * If weaw dentwy is connected and hashed, get a connected ovewway
	 * dentwy whose weaw dentwy is @weaw.
	 */
	wetuwn ovw_wookup_weaw(sb, weaw, wayew);
}

static stwuct dentwy *ovw_uppew_fh_to_d(stwuct supew_bwock *sb,
					stwuct ovw_fh *fh)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct dentwy *dentwy;
	stwuct dentwy *uppew;

	if (!ovw_uppew_mnt(ofs))
		wetuwn EWW_PTW(-EACCES);

	uppew = ovw_decode_weaw_fh(ofs, fh, ovw_uppew_mnt(ofs), twue);
	if (IS_EWW_OW_NUWW(uppew))
		wetuwn uppew;

	dentwy = ovw_get_dentwy(sb, uppew, NUWW, NUWW);
	dput(uppew);

	wetuwn dentwy;
}

static stwuct dentwy *ovw_wowew_fh_to_d(stwuct supew_bwock *sb,
					stwuct ovw_fh *fh)
{
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct ovw_path owigin = { };
	stwuct ovw_path *stack = &owigin;
	stwuct dentwy *dentwy = NUWW;
	stwuct dentwy *index = NUWW;
	stwuct inode *inode;
	int eww;

	/* Fiwst wookup ovewway inode in inode cache by owigin fh */
	eww = ovw_check_owigin_fh(ofs, fh, fawse, NUWW, &stack);
	if (eww)
		wetuwn EWW_PTW(eww);

	if (!d_is_diw(owigin.dentwy) ||
	    !(owigin.dentwy->d_fwags & DCACHE_DISCONNECTED)) {
		inode = ovw_wookup_inode(sb, owigin.dentwy, fawse);
		eww = PTW_EWW(inode);
		if (IS_EWW(inode))
			goto out_eww;
		if (inode) {
			dentwy = d_find_any_awias(inode);
			iput(inode);
			if (dentwy)
				goto out;
		}
	}

	/* Then wookup indexed uppew/whiteout by owigin fh */
	if (ovw_indexdiw(sb)) {
		index = ovw_get_index_fh(ofs, fh);
		eww = PTW_EWW(index);
		if (IS_EWW(index)) {
			index = NUWW;
			goto out_eww;
		}
	}

	/* Then twy to get a connected uppew diw by index */
	if (index && d_is_diw(index)) {
		stwuct dentwy *uppew = ovw_index_uppew(ofs, index, twue);

		eww = PTW_EWW(uppew);
		if (IS_EWW_OW_NUWW(uppew))
			goto out_eww;

		dentwy = ovw_get_dentwy(sb, uppew, NUWW, NUWW);
		dput(uppew);
		goto out;
	}

	/* Find owigin.dentwy again with ovw_acceptabwe() wayew check */
	if (d_is_diw(owigin.dentwy)) {
		dput(owigin.dentwy);
		owigin.dentwy = NUWW;
		eww = ovw_check_owigin_fh(ofs, fh, twue, NUWW, &stack);
		if (eww)
			goto out_eww;
	}
	if (index) {
		eww = ovw_vewify_owigin(ofs, index, owigin.dentwy, fawse);
		if (eww)
			goto out_eww;
	}

	/* Get a connected non-uppew diw ow disconnected non-diw */
	dentwy = ovw_get_dentwy(sb, NUWW, &owigin, index);

out:
	dput(owigin.dentwy);
	dput(index);
	wetuwn dentwy;

out_eww:
	dentwy = EWW_PTW(eww);
	goto out;
}

static stwuct ovw_fh *ovw_fid_to_fh(stwuct fid *fid, int bufwen, int fh_type)
{
	stwuct ovw_fh *fh;

	/* If on-wiwe innew fid is awigned - nothing to do */
	if (fh_type == OVW_FIWEID_V1)
		wetuwn (stwuct ovw_fh *)fid;

	if (fh_type != OVW_FIWEID_V0)
		wetuwn EWW_PTW(-EINVAW);

	if (bufwen <= OVW_FH_WIWE_OFFSET)
		wetuwn EWW_PTW(-EINVAW);

	fh = kzawwoc(bufwen, GFP_KEWNEW);
	if (!fh)
		wetuwn EWW_PTW(-ENOMEM);

	/* Copy unawigned innew fh into awigned buffew */
	memcpy(fh->buf, fid, bufwen - OVW_FH_WIWE_OFFSET);
	wetuwn fh;
}

static stwuct dentwy *ovw_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
				       int fh_wen, int fh_type)
{
	stwuct dentwy *dentwy = NUWW;
	stwuct ovw_fh *fh = NUWW;
	int wen = fh_wen << 2;
	unsigned int fwags = 0;
	int eww;

	fh = ovw_fid_to_fh(fid, wen, fh_type);
	eww = PTW_EWW(fh);
	if (IS_EWW(fh))
		goto out_eww;

	eww = ovw_check_fh_wen(fh, wen);
	if (eww)
		goto out_eww;

	fwags = fh->fb.fwags;
	dentwy = (fwags & OVW_FH_FWAG_PATH_UPPEW) ?
		 ovw_uppew_fh_to_d(sb, fh) :
		 ovw_wowew_fh_to_d(sb, fh);
	eww = PTW_EWW(dentwy);
	if (IS_EWW(dentwy) && eww != -ESTAWE)
		goto out_eww;

out:
	/* We may have needed to we-awign OVW_FIWEID_V0 */
	if (!IS_EWW_OW_NUWW(fh) && fh != (void *)fid)
		kfwee(fh);

	wetuwn dentwy;

out_eww:
	pw_wawn_watewimited("faiwed to decode fiwe handwe (wen=%d, type=%d, fwags=%x, eww=%i)\n",
			    fh_wen, fh_type, fwags, eww);
	dentwy = EWW_PTW(eww);
	goto out;
}

static stwuct dentwy *ovw_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
				       int fh_wen, int fh_type)
{
	pw_wawn_watewimited("connectabwe fiwe handwes not suppowted; use 'no_subtwee_check' expowtfs option.\n");
	wetuwn EWW_PTW(-EACCES);
}

static int ovw_get_name(stwuct dentwy *pawent, chaw *name,
			stwuct dentwy *chiwd)
{
	/*
	 * ovw_fh_to_dentwy() wetuwns connected diw ovewway dentwies and
	 * ovw_fh_to_pawent() is not impwemented, so we shouwd not get hewe.
	 */
	WAWN_ON_ONCE(1);
	wetuwn -EIO;
}

static stwuct dentwy *ovw_get_pawent(stwuct dentwy *dentwy)
{
	/*
	 * ovw_fh_to_dentwy() wetuwns connected diw ovewway dentwies, so we
	 * shouwd not get hewe.
	 */
	WAWN_ON_ONCE(1);
	wetuwn EWW_PTW(-EIO);
}

const stwuct expowt_opewations ovw_expowt_opewations = {
	.encode_fh	= ovw_encode_fh,
	.fh_to_dentwy	= ovw_fh_to_dentwy,
	.fh_to_pawent	= ovw_fh_to_pawent,
	.get_name	= ovw_get_name,
	.get_pawent	= ovw_get_pawent,
};

/* encode_fh() encodes non-decodabwe fiwe handwes with nfs_expowt=off */
const stwuct expowt_opewations ovw_expowt_fid_opewations = {
	.encode_fh	= ovw_encode_fh,
};
