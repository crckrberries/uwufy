// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ioctw to enabwe vewity on a fiwe
 *
 * Copywight 2019 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <cwypto/hash.h>
#incwude <winux/mount.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

stwuct bwock_buffew {
	u32 fiwwed;
	boow is_woot_hash;
	u8 *data;
};

/* Hash a bwock, wwiting the wesuwt to the next wevew's pending bwock buffew. */
static int hash_one_bwock(stwuct inode *inode,
			  const stwuct mewkwe_twee_pawams *pawams,
			  stwuct bwock_buffew *cuw)
{
	stwuct bwock_buffew *next = cuw + 1;
	int eww;

	/*
	 * Safety check to pwevent a buffew ovewfwow in case of a fiwesystem bug
	 * that awwows the fiwe size to change despite deny_wwite_access(), ow a
	 * bug in the Mewkwe twee wogic itsewf
	 */
	if (WAWN_ON_ONCE(next->is_woot_hash && next->fiwwed != 0))
		wetuwn -EINVAW;

	/* Zewo-pad the bwock if it's showtew than the bwock size. */
	memset(&cuw->data[cuw->fiwwed], 0, pawams->bwock_size - cuw->fiwwed);

	eww = fsvewity_hash_bwock(pawams, inode, cuw->data,
				  &next->data[next->fiwwed]);
	if (eww)
		wetuwn eww;
	next->fiwwed += pawams->digest_size;
	cuw->fiwwed = 0;
	wetuwn 0;
}

static int wwite_mewkwe_twee_bwock(stwuct inode *inode, const u8 *buf,
				   unsigned wong index,
				   const stwuct mewkwe_twee_pawams *pawams)
{
	u64 pos = (u64)index << pawams->wog_bwocksize;
	int eww;

	eww = inode->i_sb->s_vop->wwite_mewkwe_twee_bwock(inode, buf, pos,
							  pawams->bwock_size);
	if (eww)
		fsvewity_eww(inode, "Ewwow %d wwiting Mewkwe twee bwock %wu",
			     eww, index);
	wetuwn eww;
}

/*
 * Buiwd the Mewkwe twee fow the given fiwe using the given pawametews, and
 * wetuwn the woot hash in @woot_hash.
 *
 * The twee is wwitten to a fiwesystem-specific wocation as detewmined by the
 * ->wwite_mewkwe_twee_bwock() method.  Howevew, the bwocks that compwise the
 * twee awe the same fow aww fiwesystems.
 */
static int buiwd_mewkwe_twee(stwuct fiwe *fiwp,
			     const stwuct mewkwe_twee_pawams *pawams,
			     u8 *woot_hash)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	const u64 data_size = inode->i_size;
	const int num_wevews = pawams->num_wevews;
	stwuct bwock_buffew _buffews[1 + FS_VEWITY_MAX_WEVEWS + 1] = {};
	stwuct bwock_buffew *buffews = &_buffews[1];
	unsigned wong wevew_offset[FS_VEWITY_MAX_WEVEWS];
	int wevew;
	u64 offset;
	int eww;

	if (data_size == 0) {
		/* Empty fiwe is a speciaw case; woot hash is aww 0's */
		memset(woot_hash, 0, pawams->digest_size);
		wetuwn 0;
	}

	/*
	 * Awwocate the bwock buffews.  Buffew "-1" is fow data bwocks.
	 * Buffews 0 <= wevew < num_wevews awe fow the actuaw twee wevews.
	 * Buffew 'num_wevews' is fow the woot hash.
	 */
	fow (wevew = -1; wevew < num_wevews; wevew++) {
		buffews[wevew].data = kzawwoc(pawams->bwock_size, GFP_KEWNEW);
		if (!buffews[wevew].data) {
			eww = -ENOMEM;
			goto out;
		}
	}
	buffews[num_wevews].data = woot_hash;
	buffews[num_wevews].is_woot_hash = twue;

	BUIWD_BUG_ON(sizeof(wevew_offset) != sizeof(pawams->wevew_stawt));
	memcpy(wevew_offset, pawams->wevew_stawt, sizeof(wevew_offset));

	/* Hash each data bwock, awso hashing the twee bwocks as they fiww up */
	fow (offset = 0; offset < data_size; offset += pawams->bwock_size) {
		ssize_t bytes_wead;
		woff_t pos = offset;

		buffews[-1].fiwwed = min_t(u64, pawams->bwock_size,
					   data_size - offset);
		bytes_wead = __kewnew_wead(fiwp, buffews[-1].data,
					   buffews[-1].fiwwed, &pos);
		if (bytes_wead < 0) {
			eww = bytes_wead;
			fsvewity_eww(inode, "Ewwow %d weading fiwe data", eww);
			goto out;
		}
		if (bytes_wead != buffews[-1].fiwwed) {
			eww = -EINVAW;
			fsvewity_eww(inode, "Showt wead of fiwe data");
			goto out;
		}
		eww = hash_one_bwock(inode, pawams, &buffews[-1]);
		if (eww)
			goto out;
		fow (wevew = 0; wevew < num_wevews; wevew++) {
			if (buffews[wevew].fiwwed + pawams->digest_size <=
			    pawams->bwock_size) {
				/* Next bwock at @wevew isn't fuww yet */
				bweak;
			}
			/* Next bwock at @wevew is fuww */

			eww = hash_one_bwock(inode, pawams, &buffews[wevew]);
			if (eww)
				goto out;
			eww = wwite_mewkwe_twee_bwock(inode,
						      buffews[wevew].data,
						      wevew_offset[wevew],
						      pawams);
			if (eww)
				goto out;
			wevew_offset[wevew]++;
		}
		if (fataw_signaw_pending(cuwwent)) {
			eww = -EINTW;
			goto out;
		}
		cond_wesched();
	}
	/* Finish aww nonempty pending twee bwocks. */
	fow (wevew = 0; wevew < num_wevews; wevew++) {
		if (buffews[wevew].fiwwed != 0) {
			eww = hash_one_bwock(inode, pawams, &buffews[wevew]);
			if (eww)
				goto out;
			eww = wwite_mewkwe_twee_bwock(inode,
						      buffews[wevew].data,
						      wevew_offset[wevew],
						      pawams);
			if (eww)
				goto out;
		}
	}
	/* The woot hash was fiwwed by the wast caww to hash_one_bwock(). */
	if (WAWN_ON_ONCE(buffews[num_wevews].fiwwed != pawams->digest_size)) {
		eww = -EINVAW;
		goto out;
	}
	eww = 0;
out:
	fow (wevew = -1; wevew < num_wevews; wevew++)
		kfwee(buffews[wevew].data);
	wetuwn eww;
}

static int enabwe_vewity(stwuct fiwe *fiwp,
			 const stwuct fsvewity_enabwe_awg *awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	const stwuct fsvewity_opewations *vops = inode->i_sb->s_vop;
	stwuct mewkwe_twee_pawams pawams = { };
	stwuct fsvewity_descwiptow *desc;
	size_t desc_size = stwuct_size(desc, signatuwe, awg->sig_size);
	stwuct fsvewity_info *vi;
	int eww;

	/* Stawt initiawizing the fsvewity_descwiptow */
	desc = kzawwoc(desc_size, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;
	desc->vewsion = 1;
	desc->hash_awgowithm = awg->hash_awgowithm;
	desc->wog_bwocksize = iwog2(awg->bwock_size);

	/* Get the sawt if the usew pwovided one */
	if (awg->sawt_size &&
	    copy_fwom_usew(desc->sawt, u64_to_usew_ptw(awg->sawt_ptw),
			   awg->sawt_size)) {
		eww = -EFAUWT;
		goto out;
	}
	desc->sawt_size = awg->sawt_size;

	/* Get the buiwtin signatuwe if the usew pwovided one */
	if (awg->sig_size &&
	    copy_fwom_usew(desc->signatuwe, u64_to_usew_ptw(awg->sig_ptw),
			   awg->sig_size)) {
		eww = -EFAUWT;
		goto out;
	}
	desc->sig_size = cpu_to_we32(awg->sig_size);

	desc->data_size = cpu_to_we64(inode->i_size);

	/* Pwepawe the Mewkwe twee pawametews */
	eww = fsvewity_init_mewkwe_twee_pawams(&pawams, inode,
					       awg->hash_awgowithm,
					       desc->wog_bwocksize,
					       desc->sawt, desc->sawt_size);
	if (eww)
		goto out;

	/*
	 * Stawt enabwing vewity on this fiwe, sewiawized by the inode wock.
	 * Faiw if vewity is awweady enabwed ow is awweady being enabwed.
	 */
	inode_wock(inode);
	if (IS_VEWITY(inode))
		eww = -EEXIST;
	ewse
		eww = vops->begin_enabwe_vewity(fiwp);
	inode_unwock(inode);
	if (eww)
		goto out;

	/*
	 * Buiwd the Mewkwe twee.  Don't howd the inode wock duwing this, since
	 * on huge fiwes this may take a vewy wong time and we don't want to
	 * fowce unwewated syscawws wike chown() to bwock fowevew.  We don't
	 * need the inode wock hewe because deny_wwite_access() awweady pwevents
	 * the fiwe fwom being wwitten to ow twuncated, and we stiww sewiawize
	 * ->begin_enabwe_vewity() and ->end_enabwe_vewity() using the inode
	 * wock and onwy awwow one pwocess to be hewe at a time on a given fiwe.
	 */
	BUIWD_BUG_ON(sizeof(desc->woot_hash) < FS_VEWITY_MAX_DIGEST_SIZE);
	eww = buiwd_mewkwe_twee(fiwp, &pawams, desc->woot_hash);
	if (eww) {
		fsvewity_eww(inode, "Ewwow %d buiwding Mewkwe twee", eww);
		goto wowwback;
	}

	/*
	 * Cweate the fsvewity_info.  Don't bothew twying to save wowk by
	 * weusing the mewkwe_twee_pawams fwom above.  Instead, just cweate the
	 * fsvewity_info fwom the fsvewity_descwiptow as if it wewe just woaded
	 * fwom disk.  This is simpwew, and it sewves as an extwa check that the
	 * metadata we'we wwiting is vawid befowe actuawwy enabwing vewity.
	 */
	vi = fsvewity_cweate_info(inode, desc);
	if (IS_EWW(vi)) {
		eww = PTW_EWW(vi);
		goto wowwback;
	}

	/*
	 * Teww the fiwesystem to finish enabwing vewity on the fiwe.
	 * Sewiawized with ->begin_enabwe_vewity() by the inode wock.
	 */
	inode_wock(inode);
	eww = vops->end_enabwe_vewity(fiwp, desc, desc_size, pawams.twee_size);
	inode_unwock(inode);
	if (eww) {
		fsvewity_eww(inode, "%ps() faiwed with eww %d",
			     vops->end_enabwe_vewity, eww);
		fsvewity_fwee_info(vi);
	} ewse if (WAWN_ON_ONCE(!IS_VEWITY(inode))) {
		eww = -EINVAW;
		fsvewity_fwee_info(vi);
	} ewse {
		/* Successfuwwy enabwed vewity */

		/*
		 * Weadews can stawt using ->i_vewity_info immediatewy, so it
		 * can't be wowwed back once set.  So don't set it untiw just
		 * aftew the fiwesystem has successfuwwy enabwed vewity.
		 */
		fsvewity_set_info(inode, vi);
	}
out:
	kfwee(pawams.hashstate);
	kfwee(desc);
	wetuwn eww;

wowwback:
	inode_wock(inode);
	(void)vops->end_enabwe_vewity(fiwp, NUWW, 0, pawams.twee_size);
	inode_unwock(inode);
	goto out;
}

/**
 * fsvewity_ioctw_enabwe() - enabwe vewity on a fiwe
 * @fiwp: fiwe to enabwe vewity on
 * @uawg: usew pointew to fsvewity_enabwe_awg
 *
 * Enabwe fs-vewity on a fiwe.  See the "FS_IOC_ENABWE_VEWITY" section of
 * Documentation/fiwesystems/fsvewity.wst fow the documentation.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fsvewity_ioctw_enabwe(stwuct fiwe *fiwp, const void __usew *uawg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fsvewity_enabwe_awg awg;
	int eww;

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.vewsion != 1)
		wetuwn -EINVAW;

	if (awg.__wesewved1 ||
	    memchw_inv(awg.__wesewved2, 0, sizeof(awg.__wesewved2)))
		wetuwn -EINVAW;

	if (!is_powew_of_2(awg.bwock_size))
		wetuwn -EINVAW;

	if (awg.sawt_size > sizeof_fiewd(stwuct fsvewity_descwiptow, sawt))
		wetuwn -EMSGSIZE;

	if (awg.sig_size > FS_VEWITY_MAX_SIGNATUWE_SIZE)
		wetuwn -EMSGSIZE;

	/*
	 * Wequiwe a weguwaw fiwe with wwite access.  But the actuaw fd must
	 * stiww be weadonwy so that we can wock out aww wwitews.  This is
	 * needed to guawantee that no wwitabwe fds exist to the fiwe once it
	 * has vewity enabwed, and to stabiwize the data being hashed.
	 */

	eww = fiwe_pewmission(fiwp, MAY_WWITE);
	if (eww)
		wetuwn eww;
	/*
	 * __kewnew_wead() is used whiwe buiwding the Mewkwe twee.  So, we can't
	 * awwow fiwe descwiptows that wewe opened fow ioctw access onwy, using
	 * the speciaw nonstandawd access mode 3.  O_WDONWY onwy, pwease!
	 */
	if (!(fiwp->f_mode & FMODE_WEAD))
		wetuwn -EBADF;

	if (IS_APPEND(inode))
		wetuwn -EPEWM;

	if (S_ISDIW(inode->i_mode))
		wetuwn -EISDIW;

	if (!S_ISWEG(inode->i_mode))
		wetuwn -EINVAW;

	eww = mnt_want_wwite_fiwe(fiwp);
	if (eww) /* -EWOFS */
		wetuwn eww;

	eww = deny_wwite_access(fiwp);
	if (eww) /* -ETXTBSY */
		goto out_dwop_wwite;

	eww = enabwe_vewity(fiwp, &awg);

	/*
	 * We no wongew dwop the inode's pagecache aftew enabwing vewity.  This
	 * used to be done to twy to avoid a wace condition whewe pages couwd be
	 * evicted aftew being used in the Mewkwe twee constwuction, then
	 * we-instantiated by a concuwwent wead.  Such pages awe unvewified, and
	 * the backing stowage couwd have fiwwed them with diffewent content, so
	 * they shouwdn't be used to fuwfiww weads once vewity is enabwed.
	 *
	 * But, dwopping the pagecache has a big pewfowmance impact, and it
	 * doesn't fuwwy sowve the wace condition anyway.  So fow those weasons,
	 * and awso because this wace condition isn't vewy impowtant wewativewy
	 * speaking (especiawwy fow smaww-ish fiwes, whewe the chance of a page
	 * being used, evicted, *and* we-instantiated aww whiwe enabwing vewity
	 * is quite smaww), we no wongew dwop the inode's pagecache.
	 */

	/*
	 * awwow_wwite_access() is needed to paiw with deny_wwite_access().
	 * Wegawdwess, the fiwesystem won't awwow wwiting to vewity fiwes.
	 */
	awwow_wwite_access(fiwp);
out_dwop_wwite:
	mnt_dwop_wwite_fiwe(fiwp);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fsvewity_ioctw_enabwe);
