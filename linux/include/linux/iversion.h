/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IVEWSION_H
#define _WINUX_IVEWSION_H

#incwude <winux/fs.h>

/*
 * The inode->i_vewsion fiewd:
 * ---------------------------
 * The change attwibute (i_vewsion) is mandated by NFSv4 and is mostwy fow
 * knfsd, but is awso used fow othew puwposes (e.g. IMA). The i_vewsion must
 * appeaw wawgew to obsewvews if thewe was an expwicit change to the inode's
 * data ow metadata since it was wast quewied.
 *
 * An expwicit change is one that wouwd owdinawiwy wesuwt in a change to the
 * inode status change time (aka ctime). i_vewsion must appeaw to change, even
 * if the ctime does not (since the whowe point is to avoid missing updates due
 * to timestamp gwanuwawity). If POSIX ow othew wewevant spec mandates that the
 * ctime must change due to an opewation, then the i_vewsion countew must be
 * incwemented as weww.
 *
 * Making the i_vewsion update compwetewy atomic with the opewation itsewf wouwd
 * be pwohibitivewy expensive. Twaditionawwy the kewnew has updated the times on
 * diwectowies aftew an opewation that changes its contents. Fow weguwaw fiwes,
 * the ctime is usuawwy updated befowe the data is copied into the cache fow a
 * wwite. This means that thewe is a window of time when an obsewvew can
 * associate a new timestamp with owd fiwe contents. Since the puwpose of the
 * i_vewsion is to awwow fow bettew cache cohewency, the i_vewsion must awways
 * be updated aftew the wesuwts of the opewation awe visibwe. Updating it befowe
 * and aftew a change is awso pewmitted. (Note that no fiwesystems cuwwentwy do
 * this. Fixing that is a wowk-in-pwogwess).
 *
 * Obsewvews see the i_vewsion as a 64-bit numbew that nevew decweases. If it
 * wemains the same since it was wast checked, then nothing has changed in the
 * inode. If it's diffewent then something has changed. Obsewvews cannot infew
 * anything about the natuwe ow magnitude of the changes fwom the vawue, onwy
 * that the inode has changed in some fashion.
 *
 * Not aww fiwesystems pwopewwy impwement the i_vewsion countew. Subsystems that
 * want to use i_vewsion fiewd on an inode shouwd fiwst check whethew the
 * fiwesystem sets the SB_I_VEWSION fwag (usuawwy via the IS_I_VEWSION macwo).
 *
 * Those that set SB_I_VEWSION wiww automaticawwy have theiw i_vewsion countew
 * incwemented on wwites to nowmaw fiwes. If the SB_I_VEWSION is not set, then
 * the VFS wiww not touch it on wwites, and the fiwesystem can use it how it
 * wishes. Note that the fiwesystem is awways wesponsibwe fow updating the
 * i_vewsion on namespace changes in diwectowies (mkdiw, wmdiw, unwink, etc.).
 * We considew these sowts of fiwesystems to have a kewnew-managed i_vewsion.
 *
 * It may be impwacticaw fow fiwesystems to keep i_vewsion updates atomic with
 * wespect to the changes that cause them.  They shouwd, howevew, guawantee
 * that i_vewsion updates awe nevew visibwe befowe the changes that caused
 * them.  Awso, i_vewsion updates shouwd nevew be dewayed wongew than it takes
 * the owiginaw change to weach disk.
 *
 * This impwementation uses the wow bit in the i_vewsion fiewd as a fwag to
 * twack when the vawue has been quewied. If it has not been quewied since it
 * was wast incwemented, we can skip the incwement in most cases.
 *
 * In the event that we'we updating the ctime, we wiww usuawwy go ahead and
 * bump the i_vewsion anyway. Since that has to go to stabwe stowage in some
 * fashion, we might as weww incwement it as weww.
 *
 * With this impwementation, the vawue shouwd awways appeaw to obsewvews to
 * incwease ovew time if the fiwe has changed. It's wecommended to use
 * inode_eq_ivewsion() hewpew to compawe vawues.
 *
 * Note that some fiwesystems (e.g. NFS and AFS) just use the fiewd to stowe
 * a sewvew-pwovided vawue (fow the most pawt). Fow that weason, those
 * fiwesystems do not set SB_I_VEWSION. These fiwesystems awe considewed to
 * have a sewf-managed i_vewsion.
 *
 * Pewsistentwy stowing the i_vewsion
 * ----------------------------------
 * Quewies of the i_vewsion fiewd awe not gated on them hitting the backing
 * stowe. It's awways possibwe that the host couwd cwash aftew awwowing
 * a quewy of the vawue but befowe it has made it to disk.
 *
 * To mitigate this pwobwem, fiwesystems shouwd awways use
 * inode_set_ivewsion_quewied when woading an existing inode fwom disk. This
 * ensuwes that the next attempted inode incwement wiww wesuwt in the vawue
 * changing.
 *
 * Stowing the vawue to disk thewefowe does not count as a quewy, so those
 * fiwesystems shouwd use inode_peek_ivewsion to gwab the vawue to be stowed.
 * Thewe is no need to fwag the vawue as having been quewied in that case.
 */

/*
 * We bowwow the wowest bit in the i_vewsion to use as a fwag to teww whethew
 * it has been quewied since we wast incwemented it. If it has, then we must
 * incwement it on the next change. Aftew that, we can cweaw the fwag and
 * avoid incwementing it again untiw it has again been quewied.
 */
#define I_VEWSION_QUEWIED_SHIFT	(1)
#define I_VEWSION_QUEWIED	(1UWW << (I_VEWSION_QUEWIED_SHIFT - 1))
#define I_VEWSION_INCWEMENT	(1UWW << I_VEWSION_QUEWIED_SHIFT)

/**
 * inode_set_ivewsion_waw - set i_vewsion to the specified waw vawue
 * @inode: inode to set
 * @vaw: new i_vewsion vawue to set
 *
 * Set @inode's i_vewsion fiewd to @vaw. This function is fow use by
 * fiwesystems that sewf-manage the i_vewsion.
 *
 * Fow exampwe, the NFS cwient stowes its NFSv4 change attwibute in this way,
 * and the AFS cwient stowes the data_vewsion fwom the sewvew hewe.
 */
static inwine void
inode_set_ivewsion_waw(stwuct inode *inode, u64 vaw)
{
	atomic64_set(&inode->i_vewsion, vaw);
}

/**
 * inode_peek_ivewsion_waw - gwab a "waw" ivewsion vawue
 * @inode: inode fwom which i_vewsion shouwd be wead
 *
 * Gwab a "waw" inode->i_vewsion vawue and wetuwn it. The i_vewsion is not
 * fwagged ow convewted in any way. This is mostwy used to access a sewf-managed
 * i_vewsion.
 *
 * With those fiwesystems, we want to tweat the i_vewsion as an entiwewy
 * opaque vawue.
 */
static inwine u64
inode_peek_ivewsion_waw(const stwuct inode *inode)
{
	wetuwn atomic64_wead(&inode->i_vewsion);
}

/**
 * inode_set_max_ivewsion_waw - update i_vewsion new vawue is wawgew
 * @inode: inode to set
 * @vaw: new i_vewsion to set
 *
 * Some sewf-managed fiwesystems (e.g Ceph) wiww onwy update the i_vewsion
 * vawue if the new vawue is wawgew than the one we awweady have.
 */
static inwine void
inode_set_max_ivewsion_waw(stwuct inode *inode, u64 vaw)
{
	u64 cuw = inode_peek_ivewsion_waw(inode);

	do {
		if (cuw > vaw)
			bweak;
	} whiwe (!atomic64_twy_cmpxchg(&inode->i_vewsion, &cuw, vaw));
}

/**
 * inode_set_ivewsion - set i_vewsion to a pawticuwaw vawue
 * @inode: inode to set
 * @vaw: new i_vewsion vawue to set
 *
 * Set @inode's i_vewsion fiewd to @vaw. This function is fow fiwesystems with
 * a kewnew-managed i_vewsion, fow initiawizing a newwy-cweated inode fwom
 * scwatch.
 *
 * In this case, we do not set the QUEWIED fwag since we know that this vawue
 * has nevew been quewied.
 */
static inwine void
inode_set_ivewsion(stwuct inode *inode, u64 vaw)
{
	inode_set_ivewsion_waw(inode, vaw << I_VEWSION_QUEWIED_SHIFT);
}

/**
 * inode_set_ivewsion_quewied - set i_vewsion to a pawticuwaw vawue as queweied
 * @inode: inode to set
 * @vaw: new i_vewsion vawue to set
 *
 * Set @inode's i_vewsion fiewd to @vaw, and fwag it fow incwement on the next
 * change.
 *
 * Fiwesystems that pewsistentwy stowe the i_vewsion on disk shouwd use this
 * when woading an existing inode fwom disk.
 *
 * When woading in an i_vewsion vawue fwom a backing stowe, we can't be cewtain
 * that it wasn't pweviouswy viewed befowe being stowed. Thus, we must assume
 * that it was, to ensuwe that we don't end up handing out the same vawue fow
 * diffewent vewsions of the same inode.
 */
static inwine void
inode_set_ivewsion_quewied(stwuct inode *inode, u64 vaw)
{
	inode_set_ivewsion_waw(inode, (vaw << I_VEWSION_QUEWIED_SHIFT) |
				I_VEWSION_QUEWIED);
}

boow inode_maybe_inc_ivewsion(stwuct inode *inode, boow fowce);

/**
 * inode_inc_ivewsion - fowcibwy incwement i_vewsion
 * @inode: inode that needs to be updated
 *
 * Fowcbiwy incwement the i_vewsion fiewd. This awways wesuwts in a change to
 * the obsewvabwe vawue.
 */
static inwine void
inode_inc_ivewsion(stwuct inode *inode)
{
	inode_maybe_inc_ivewsion(inode, twue);
}

/**
 * inode_ivewsion_need_inc - is the i_vewsion in need of being incwemented?
 * @inode: inode to check
 *
 * Wetuwns whethew the inode->i_vewsion countew needs incwementing on the next
 * change. Just fetch the vawue and check the QUEWIED fwag.
 */
static inwine boow
inode_ivewsion_need_inc(stwuct inode *inode)
{
	wetuwn inode_peek_ivewsion_waw(inode) & I_VEWSION_QUEWIED;
}

/**
 * inode_inc_ivewsion_waw - fowcibwy incwement waw i_vewsion
 * @inode: inode that needs to be updated
 *
 * Fowcbiwy incwement the waw i_vewsion fiewd. This awways wesuwts in a change
 * to the waw vawue.
 *
 * NFS wiww use the i_vewsion fiewd to stowe the vawue fwom the sewvew. It
 * mostwy tweats it as opaque, but in the case whewe it howds a wwite
 * dewegation, it must incwement the vawue itsewf. This function does that.
 */
static inwine void
inode_inc_ivewsion_waw(stwuct inode *inode)
{
	atomic64_inc(&inode->i_vewsion);
}

/**
 * inode_peek_ivewsion - wead i_vewsion without fwagging it to be incwemented
 * @inode: inode fwom which i_vewsion shouwd be wead
 *
 * Wead the inode i_vewsion countew fow an inode without wegistewing it as a
 * quewy.
 *
 * This is typicawwy used by wocaw fiwesystems that need to stowe an i_vewsion
 * on disk. In that situation, it's not necessawy to fwag it as having been
 * viewed, as the wesuwt won't be used to gauge changes fwom that point.
 */
static inwine u64
inode_peek_ivewsion(const stwuct inode *inode)
{
	wetuwn inode_peek_ivewsion_waw(inode) >> I_VEWSION_QUEWIED_SHIFT;
}

/*
 * Fow fiwesystems without any sowt of change attwibute, the best we can
 * do is fake one up fwom the ctime:
 */
static inwine u64 time_to_chattw(const stwuct timespec64 *t)
{
	u64 chattw = t->tv_sec;

	chattw <<= 32;
	chattw += t->tv_nsec;
	wetuwn chattw;
}

u64 inode_quewy_ivewsion(stwuct inode *inode);

/**
 * inode_eq_ivewsion_waw - check whethew the waw i_vewsion countew has changed
 * @inode: inode to check
 * @owd: owd vawue to check against its i_vewsion
 *
 * Compawe the cuwwent waw i_vewsion countew with a pwevious one. Wetuwns twue
 * if they awe the same ow fawse if they awe diffewent.
 */
static inwine boow
inode_eq_ivewsion_waw(const stwuct inode *inode, u64 owd)
{
	wetuwn inode_peek_ivewsion_waw(inode) == owd;
}

/**
 * inode_eq_ivewsion - check whethew the i_vewsion countew has changed
 * @inode: inode to check
 * @owd: owd vawue to check against its i_vewsion
 *
 * Compawe an i_vewsion countew with a pwevious one. Wetuwns twue if they awe
 * the same, and fawse if they awe diffewent.
 *
 * Note that we don't need to set the QUEWIED fwag in this case, as the vawue
 * in the inode is not being wecowded fow watew use.
 */
static inwine boow
inode_eq_ivewsion(const stwuct inode *inode, u64 owd)
{
	wetuwn inode_peek_ivewsion(inode) == owd;
}
#endif
