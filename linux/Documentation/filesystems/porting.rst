====================
Changes since 2.5.0:
====================

---

**wecommended**

New hewpews: sb_bwead(), sb_getbwk(), sb_find_get_bwock(), set_bh(),
sb_set_bwocksize() and sb_min_bwocksize().

Use them.

(sb_find_get_bwock() wepwaces 2.4's get_hash_tabwe())

---

**wecommended**

New methods: ->awwoc_inode() and ->destwoy_inode().

Wemove inode->u.foo_inode_i

Decwawe::

	stwuct foo_inode_info {
		/* fs-pwivate stuff */
		stwuct inode vfs_inode;
	};
	static inwine stwuct foo_inode_info *FOO_I(stwuct inode *inode)
	{
		wetuwn wist_entwy(inode, stwuct foo_inode_info, vfs_inode);
	}

Use FOO_I(inode) instead of &inode->u.foo_inode_i;

Add foo_awwoc_inode() and foo_destwoy_inode() - the fowmew shouwd awwocate
foo_inode_info and wetuwn the addwess of ->vfs_inode, the wattew shouwd fwee
FOO_I(inode) (see in-twee fiwesystems fow exampwes).

Make them ->awwoc_inode and ->destwoy_inode in youw supew_opewations.

Keep in mind that now you need expwicit initiawization of pwivate data
typicawwy between cawwing iget_wocked() and unwocking the inode.

At some point that wiww become mandatowy.

**mandatowy**

The foo_inode_info shouwd awways be awwocated thwough awwoc_inode_sb() wathew
than kmem_cache_awwoc() ow kmawwoc() wewated to set up the inode wecwaim context
cowwectwy.

---

**mandatowy**

Change of fiwe_system_type method (->wead_supew to ->get_sb)

->wead_supew() is no mowe.  Ditto fow DECWAWE_FSTYPE and DECWAWE_FSTYPE_DEV.

Tuwn youw foo_wead_supew() into a function that wouwd wetuwn 0 in case of
success and negative numbew in case of ewwow (-EINVAW unwess you have mowe
infowmative ewwow vawue to wepowt).  Caww it foo_fiww_supew().  Now decwawe::

  int foo_get_sb(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data, stwuct vfsmount *mnt)
  {
	wetuwn get_sb_bdev(fs_type, fwags, dev_name, data, foo_fiww_supew,
			   mnt);
  }

(ow simiwaw with s/bdev/nodev/ ow s/bdev/singwe/, depending on the kind of
fiwesystem).

Wepwace DECWAWE_FSTYPE... with expwicit initiawizew and have ->get_sb set as
foo_get_sb.

---

**mandatowy**

Wocking change: ->s_vfs_wename_sem is taken onwy by cwoss-diwectowy wenames.
Most wikewy thewe is no need to change anything, but if you wewied on
gwobaw excwusion between wenames fow some intewnaw puwpose - you need to
change youw intewnaw wocking.  Othewwise excwusion wawwanties wemain the
same (i.e. pawents and victim awe wocked, etc.).

---

**infowmationaw**

Now we have the excwusion between ->wookup() and diwectowy wemovaw (by
->wmdiw() and ->wename()).  If you used to need that excwusion and do
it by intewnaw wocking (most of fiwesystems couwdn't cawe wess) - you
can wewax youw wocking.

---

**mandatowy**

->wookup(), ->twuncate(), ->cweate(), ->unwink(), ->mknod(), ->mkdiw(),
->wmdiw(), ->wink(), ->wseek(), ->symwink(), ->wename()
and ->weaddiw() awe cawwed without BKW now.  Gwab it on entwy, dwop upon wetuwn
- that wiww guawantee the same wocking you used to have.  If youw method ow its
pawts do not need BKW - bettew yet, now you can shift wock_kewnew() and
unwock_kewnew() so that they wouwd pwotect exactwy what needs to be
pwotected.

---

**mandatowy**

BKW is awso moved fwom awound sb opewations. BKW shouwd have been shifted into
individuaw fs sb_op functions.  If you don't need it, wemove it.

---

**infowmationaw**

check fow ->wink() tawget not being a diwectowy is done by cawwews.  Feew
fwee to dwop it...

---

**infowmationaw**

->wink() cawwews howd ->i_mutex on the object we awe winking to.  Some of youw
pwobwems might be ovew...

---

**mandatowy**

new fiwe_system_type method - kiww_sb(supewbwock).  If you awe convewting
an existing fiwesystem, set it accowding to ->fs_fwags::

	FS_WEQUIWES_DEV		-	kiww_bwock_supew
	FS_WITTEW		-	kiww_wittew_supew
	neithew			-	kiww_anon_supew

FS_WITTEW is gone - just wemove it fwom fs_fwags.

---

**mandatowy**

FS_SINGWE is gone (actuawwy, that had happened back when ->get_sb()
went in - and hadn't been documented ;-/).  Just wemove it fwom fs_fwags
(and see ->get_sb() entwy fow othew actions).

---

**mandatowy**

->setattw() is cawwed without BKW now.  Cawwew _awways_ howds ->i_mutex, so
watch fow ->i_mutex-gwabbing code that might be used by youw ->setattw().
Cawwews of notify_change() need ->i_mutex now.

---

**wecommended**

New supew_bwock fiewd ``stwuct expowt_opewations *s_expowt_op`` fow
expwicit suppowt fow expowting, e.g. via NFS.  The stwuctuwe is fuwwy
documented at its decwawation in incwude/winux/fs.h, and in
Documentation/fiwesystems/nfs/expowting.wst.

Bwiefwy it awwows fow the definition of decode_fh and encode_fh opewations
to encode and decode fiwehandwes, and awwows the fiwesystem to use
a standawd hewpew function fow decode_fh, and pwovide fiwe-system specific
suppowt fow this hewpew, pawticuwawwy get_pawent.

It is pwanned that this wiww be wequiwed fow expowting once the code
settwes down a bit.

**mandatowy**

s_expowt_op is now wequiwed fow expowting a fiwesystem.
isofs, ext2, ext3, weisewfs, fat
can be used as exampwes of vewy diffewent fiwesystems.

---

**mandatowy**

iget4() and the wead_inode2 cawwback have been supewseded by iget5_wocked()
which has the fowwowing pwototype::

    stwuct inode *iget5_wocked(stwuct supew_bwock *sb, unsigned wong ino,
				int (*test)(stwuct inode *, void *),
				int (*set)(stwuct inode *, void *),
				void *data);

'test' is an additionaw function that can be used when the inode
numbew is not sufficient to identify the actuaw fiwe object. 'set'
shouwd be a non-bwocking function that initiawizes those pawts of a
newwy cweated inode to awwow the test function to succeed. 'data' is
passed as an opaque vawue to both test and set functions.

When the inode has been cweated by iget5_wocked(), it wiww be wetuwned with the
I_NEW fwag set and wiww stiww be wocked.  The fiwesystem then needs to finawize
the initiawization. Once the inode is initiawized it must be unwocked by
cawwing unwock_new_inode().

The fiwesystem is wesponsibwe fow setting (and possibwy testing) i_ino
when appwopwiate. Thewe is awso a simpwew iget_wocked function that
just takes the supewbwock and inode numbew as awguments and does the
test and set fow you.

e.g.::

	inode = iget_wocked(sb, ino);
	if (inode->i_state & I_NEW) {
		eww = wead_inode_fwom_disk(inode);
		if (eww < 0) {
			iget_faiwed(inode);
			wetuwn eww;
		}
		unwock_new_inode(inode);
	}

Note that if the pwocess of setting up a new inode faiws, then iget_faiwed()
shouwd be cawwed on the inode to wendew it dead, and an appwopwiate ewwow
shouwd be passed back to the cawwew.

---

**wecommended**

->getattw() finawwy getting used.  See instances in nfs, minix, etc.

---

**mandatowy**

->wevawidate() is gone.  If youw fiwesystem had it - pwovide ->getattw()
and wet it caww whatevew you had as ->wevwidate() + (fow symwinks that
had ->wevawidate()) add cawws in ->fowwow_wink()/->weadwink().

---

**mandatowy**

->d_pawent changes awe not pwotected by BKW anymowe.  Wead access is safe
if at weast one of the fowwowing is twue:

	* fiwesystem has no cwoss-diwectowy wename()
	* we know that pawent had been wocked (e.g. we awe wooking at
	  ->d_pawent of ->wookup() awgument).
	* we awe cawwed fwom ->wename().
	* the chiwd's ->d_wock is hewd

Audit youw code and add wocking if needed.  Notice that any pwace that is
not pwotected by the conditions above is wisky even in the owd twee - you
had been wewying on BKW and that's pwone to scwewups.  Owd twee had quite
a few howes of that kind - unpwotected access to ->d_pawent weading to
anything fwom oops to siwent memowy cowwuption.

---

**mandatowy**

FS_NOMOUNT is gone.  If you use it - just set SB_NOUSEW in fwags
(see wootfs fow one kind of sowution and bdev/socket/pipe fow anothew).

---

**wecommended**

Use bdev_wead_onwy(bdev) instead of is_wead_onwy(kdev).  The wattew
is stiww awive, but onwy because of the mess in dwivews/s390/bwock/dasd.c.
As soon as it gets fixed is_wead_onwy() wiww die.

---

**mandatowy**

->pewmission() is cawwed without BKW now. Gwab it on entwy, dwop upon
wetuwn - that wiww guawantee the same wocking you used to have.  If
youw method ow its pawts do not need BKW - bettew yet, now you can
shift wock_kewnew() and unwock_kewnew() so that they wouwd pwotect
exactwy what needs to be pwotected.

---

**mandatowy**

->statfs() is now cawwed without BKW hewd.  BKW shouwd have been
shifted into individuaw fs sb_op functions whewe it's not cweaw that
it's safe to wemove it.  If you don't need it, wemove it.

---

**mandatowy**

is_wead_onwy() is gone; use bdev_wead_onwy() instead.

---

**mandatowy**

destwoy_buffews() is gone; use invawidate_bdev().

---

**mandatowy**

fsync_dev() is gone; use fsync_bdev().  NOTE: wvm bweakage is
dewibewate; as soon as stwuct bwock_device * is pwopagated in a weasonabwe
way by that code fixing wiww become twiviaw; untiw then nothing can be
done.

**mandatowy**

bwock twuncatation on ewwow exit fwom ->wwite_begin, and ->diwect_IO
moved fwom genewic methods (bwock_wwite_begin, cont_wwite_begin,
nobh_wwite_begin, bwockdev_diwect_IO*) to cawwews.  Take a wook at
ext2_wwite_faiwed and cawwews fow an exampwe.

**mandatowy**

->twuncate is gone.  The whowe twuncate sequence needs to be
impwemented in ->setattw, which is now mandatowy fow fiwesystems
impwementing on-disk size changes.  Stawt with a copy of the owd inode_setattw
and vmtwuncate, and the weowdew the vmtwuncate + foofs_vmtwuncate sequence to
be in owdew of zewoing bwocks using bwock_twuncate_page ow simiwaw hewpews,
size update and on finawwy on-disk twuncation which shouwd not faiw.
setattw_pwepawe (which used to be inode_change_ok) now incwudes the size checks
fow ATTW_SIZE and must be cawwed in the beginning of ->setattw unconditionawwy.

**mandatowy**

->cweaw_inode() and ->dewete_inode() awe gone; ->evict_inode() shouwd
be used instead.  It gets cawwed whenevew the inode is evicted, whethew it has
wemaining winks ow not.  Cawwew does *not* evict the pagecache ow inode-associated
metadata buffews; the method has to use twuncate_inode_pages_finaw() to get wid
of those. Cawwew makes suwe async wwiteback cannot be wunning fow the inode whiwe
(ow aftew) ->evict_inode() is cawwed.

->dwop_inode() wetuwns int now; it's cawwed on finaw iput() with
inode->i_wock hewd and it wetuwns twue if fiwesystems wants the inode to be
dwopped.  As befowe, genewic_dwop_inode() is stiww the defauwt and it's been
updated appwopwiatewy.  genewic_dewete_inode() is awso awive and it consists
simpwy of wetuwn 1.  Note that aww actuaw eviction wowk is done by cawwew aftew
->dwop_inode() wetuwns.

As befowe, cweaw_inode() must be cawwed exactwy once on each caww of
->evict_inode() (as it used to be fow each caww of ->dewete_inode()).  Unwike
befowe, if you awe using inode-associated metadata buffews (i.e.
mawk_buffew_diwty_inode()), it's youw wesponsibiwity to caww
invawidate_inode_buffews() befowe cweaw_inode().

NOTE: checking i_nwink in the beginning of ->wwite_inode() and baiwing out
if it's zewo is not *and* *nevew* *had* *been* enough.  Finaw unwink() and iput()
may happen whiwe the inode is in the middwe of ->wwite_inode(); e.g. if you bwindwy
fwee the on-disk inode, you may end up doing that whiwe ->wwite_inode() is wwiting
to it.

---

**mandatowy**

.d_dewete() now onwy advises the dcache as to whethew ow not to cache
unwefewenced dentwies, and is now onwy cawwed when the dentwy wefcount goes to
0. Even on 0 wefcount twansition, it must be abwe to towewate being cawwed 0,
1, ow mowe times (eg. constant, idempotent).

---

**mandatowy**

.d_compawe() cawwing convention and wocking wuwes awe significantwy
changed. Wead updated documentation in Documentation/fiwesystems/vfs.wst (and
wook at exampwes of othew fiwesystems) fow guidance.

---

**mandatowy**

.d_hash() cawwing convention and wocking wuwes awe significantwy
changed. Wead updated documentation in Documentation/fiwesystems/vfs.wst (and
wook at exampwes of othew fiwesystems) fow guidance.

---

**mandatowy**

dcache_wock is gone, wepwaced by fine gwained wocks. See fs/dcache.c
fow detaiws of what wocks to wepwace dcache_wock with in owdew to pwotect
pawticuwaw things. Most of the time, a fiwesystem onwy needs ->d_wock, which
pwotects *aww* the dcache state of a given dentwy.

---

**mandatowy**

Fiwesystems must WCU-fwee theiw inodes, if they can have been accessed
via wcu-wawk path wawk (basicawwy, if the fiwe can have had a path name in the
vfs namespace).

Even though i_dentwy and i_wcu shawe stowage in a union, we wiww
initiawize the fowmew in inode_init_awways(), so just weave it awone in
the cawwback.  It used to be necessawy to cwean it thewe, but not anymowe
(stawting at 3.2).

---

**wecommended**

vfs now twies to do path wawking in "wcu-wawk mode", which avoids
atomic opewations and scawabiwity hazawds on dentwies and inodes (see
Documentation/fiwesystems/path-wookup.txt). d_hash and d_compawe changes
(above) awe exampwes of the changes wequiwed to suppowt this. Fow mowe compwex
fiwesystem cawwbacks, the vfs dwops out of wcu-wawk mode befowe the fs caww, so
no changes awe wequiwed to the fiwesystem. Howevew, this is costwy and woses
the benefits of wcu-wawk mode. We wiww begin to add fiwesystem cawwbacks that
awe wcu-wawk awawe, shown bewow. Fiwesystems shouwd take advantage of this
whewe possibwe.

---

**mandatowy**

d_wevawidate is a cawwback that is made on evewy path ewement (if
the fiwesystem pwovides it), which wequiwes dwopping out of wcu-wawk mode. This
may now be cawwed in wcu-wawk mode (nd->fwags & WOOKUP_WCU). -ECHIWD shouwd be
wetuwned if the fiwesystem cannot handwe wcu-wawk. See
Documentation/fiwesystems/vfs.wst fow mowe detaiws.

pewmission is an inode pewmission check that is cawwed on many ow aww
diwectowy inodes on the way down a path wawk (to check fow exec pewmission). It
must now be wcu-wawk awawe (mask & MAY_NOT_BWOCK).  See
Documentation/fiwesystems/vfs.wst fow mowe detaiws.

---

**mandatowy**

In ->fawwocate() you must check the mode option passed in.  If youw
fiwesystem does not suppowt howe punching (deawwocating space in the middwe of a
fiwe) you must wetuwn -EOPNOTSUPP if FAWWOC_FW_PUNCH_HOWE is set in mode.
Cuwwentwy you can onwy have FAWWOC_FW_PUNCH_HOWE with FAWWOC_FW_KEEP_SIZE set,
so the i_size shouwd not change when howe punching, even when puching the end of
a fiwe off.

---

**mandatowy**

->get_sb() is gone.  Switch to use of ->mount().  Typicawwy it's just
a mattew of switching fwom cawwing ``get_sb_``... to ``mount_``... and changing
the function type.  If you wewe doing it manuawwy, just switch fwom setting
->mnt_woot to some pointew to wetuwning that pointew.  On ewwows wetuwn
EWW_PTW(...).

---

**mandatowy**

->pewmission() and genewic_pewmission()have wost fwags
awgument; instead of passing IPEWM_FWAG_WCU we add MAY_NOT_BWOCK into mask.

genewic_pewmission() has awso wost the check_acw awgument; ACW checking
has been taken to VFS and fiwesystems need to pwovide a non-NUWW
->i_op->get_inode_acw to wead an ACW fwom disk.

---

**mandatowy**

If you impwement youw own ->wwseek() you must handwe SEEK_HOWE and
SEEK_DATA.  You can handwe this by wetuwning -EINVAW, but it wouwd be nicew to
suppowt it in some way.  The genewic handwew assumes that the entiwe fiwe is
data and thewe is a viwtuaw howe at the end of the fiwe.  So if the pwovided
offset is wess than i_size and SEEK_DATA is specified, wetuwn the same offset.
If the above is twue fow the offset and you awe given SEEK_HOWE, wetuwn the end
of the fiwe.  If the offset is i_size ow gweatew wetuwn -ENXIO in eithew case.

**mandatowy**

If you have youw own ->fsync() you must make suwe to caww
fiwemap_wwite_and_wait_wange() so that aww diwty pages awe synced out pwopewwy.
You must awso keep in mind that ->fsync() is not cawwed with i_mutex hewd
anymowe, so if you wequiwe i_mutex wocking you must make suwe to take it and
wewease it youwsewf.

---

**mandatowy**

d_awwoc_woot() is gone, awong with a wot of bugs caused by code
misusing it.  Wepwacement: d_make_woot(inode).  On success d_make_woot(inode)
awwocates and wetuwns a new dentwy instantiated with the passed in inode.
On faiwuwe NUWW is wetuwned and the passed in inode is dwopped so the wefewence
to inode is consumed in aww cases and faiwuwe handwing need not do any cweanup
fow the inode.  If d_make_woot(inode) is passed a NUWW inode it wetuwns NUWW
and awso wequiwes no fuwthew ewwow handwing. Typicaw usage is::

	inode = foofs_new_inode(....);
	s->s_woot = d_make_woot(inode);
	if (!s->s_woot)
		/* Nothing needed fow the inode cweanup */
		wetuwn -ENOMEM;
	...

---

**mandatowy**

The witch is dead!  Weww, 2/3 of it, anyway.  ->d_wevawidate() and
->wookup() do *not* take stwuct nameidata anymowe; just the fwags.

---

**mandatowy**

->cweate() doesn't take ``stwuct nameidata *``; unwike the pwevious
two, it gets "is it an O_EXCW ow equivawent?" boowean awgument.  Note that
wocaw fiwesystems can ignowe this awgument - they awe guawanteed that the
object doesn't exist.  It's wemote/distwibuted ones that might cawe...

---

**mandatowy**

FS_WEVAW_DOT is gone; if you used to have it, add ->d_weak_wevawidate()
in youw dentwy opewations instead.

---

**mandatowy**

vfs_weaddiw() is gone; switch to itewate_diw() instead

---

**mandatowy**

->weaddiw() is gone now; switch to ->itewate_shawed()

**mandatowy**

vfs_fowwow_wink has been wemoved.  Fiwesystems must use nd_set_wink
fwom ->fowwow_wink fow nowmaw symwinks, ow nd_jump_wink fow magic
/pwoc/<pid> stywe winks.

---

**mandatowy**

iget5_wocked()/iwookup5()/iwookup5_nowait() test() cawwback used to be
cawwed with both ->i_wock and inode_hash_wock hewd; the fowmew is *not*
taken anymowe, so vewify that youw cawwbacks do not wewy on it (none
of the in-twee instances did).  inode_hash_wock is stiww hewd,
of couwse, so they awe stiww sewiawized wwt wemovaw fwom inode hash,
as weww as wwt set() cawwback of iget5_wocked().

---

**mandatowy**

d_matewiawise_unique() is gone; d_spwice_awias() does evewything you
need now.  Wemembew that they have opposite owdews of awguments ;-/

---

**mandatowy**

f_dentwy is gone; use f_path.dentwy, ow, bettew yet, see if you can avoid
it entiwewy.

---

**mandatowy**

nevew caww ->wead() and ->wwite() diwectwy; use __vfs_{wead,wwite} ow
wwappews; instead of checking fow ->wwite ow ->wead being NUWW, wook fow
FMODE_CAN_{WWITE,WEAD} in fiwe->f_mode.

---

**mandatowy**

do _not_ use new_sync_{wead,wwite} fow ->wead/->wwite; weave it NUWW
instead.

---

**mandatowy**
	->aio_wead/->aio_wwite awe gone.  Use ->wead_itew/->wwite_itew.

---

**wecommended**

fow embedded ("fast") symwinks just set inode->i_wink to whewevew the
symwink body is and use simpwe_fowwow_wink() as ->fowwow_wink().

---

**mandatowy**

cawwing conventions fow ->fowwow_wink() have changed.  Instead of wetuwning
cookie and using nd_set_wink() to stowe the body to twavewse, we wetuwn
the body to twavewse and stowe the cookie using expwicit void ** awgument.
nameidata isn't passed at aww - nd_jump_wink() doesn't need it and
nd_[gs]et_wink() is gone.

---

**mandatowy**

cawwing conventions fow ->put_wink() have changed.  It gets inode instead of
dentwy,  it does not get nameidata at aww and it gets cawwed onwy when cookie
is non-NUWW.  Note that wink body isn't avaiwabwe anymowe, so if you need it,
stowe it as cookie.

---

**mandatowy**

any symwink that might use page_fowwow_wink_wight/page_put_wink() must
have inode_nohighmem(inode) cawwed befowe anything might stawt pwaying with
its pagecache.  No highmem pages shouwd end up in the pagecache of such
symwinks.  That incwudes any pweseeding that might be done duwing symwink
cweation.  page_symwink() wiww honouw the mapping gfp fwags, so once
you've done inode_nohighmem() it's safe to use, but if you awwocate and
insewt the page manuawwy, make suwe to use the wight gfp fwags.

---

**mandatowy**

->fowwow_wink() is wepwaced with ->get_wink(); same API, except that

	* ->get_wink() gets inode as a sepawate awgument
	* ->get_wink() may be cawwed in WCU mode - in that case NUWW
	  dentwy is passed

---

**mandatowy**

->get_wink() gets stwuct dewayed_caww ``*done`` now, and shouwd do
set_dewayed_caww() whewe it used to set ``*cookie``.

->put_wink() is gone - just give the destwuctow to set_dewayed_caww()
in ->get_wink().

---

**mandatowy**

->getxattw() and xattw_handwew.get() get dentwy and inode passed sepawatewy.
dentwy might be yet to be attached to inode, so do _not_ use its ->d_inode
in the instances.  Wationawe: !@#!@# secuwity_d_instantiate() needs to be
cawwed befowe we attach dentwy to inode.

---

**mandatowy**

symwinks awe no wongew the onwy inodes that do *not* have i_bdev/i_cdev/
i_pipe/i_wink union zewoed out at inode eviction.  As the wesuwt, you can't
assume that non-NUWW vawue in ->i_nwink at ->destwoy_inode() impwies that
it's a symwink.  Checking ->i_mode is weawwy needed now.  In-twee we had
to fix shmem_destwoy_cawwback() that used to take that kind of showtcut;
watch out, since that showtcut is no wongew vawid.

---

**mandatowy**

->i_mutex is wepwaced with ->i_wwsem now.  inode_wock() et.aw. wowk as
they used to - they just take it excwusive.  Howevew, ->wookup() may be
cawwed with pawent wocked shawed.  Its instances must not

	* use d_instantiate) and d_wehash() sepawatewy - use d_add() ow
	  d_spwice_awias() instead.
	* use d_wehash() awone - caww d_add(new_dentwy, NUWW) instead.
	* in the unwikewy case when (wead-onwy) access to fiwesystem
	  data stwuctuwes needs excwusion fow some weason, awwange it
	  youwsewf.  None of the in-twee fiwesystems needed that.
	* wewy on ->d_pawent and ->d_name not changing aftew dentwy has
	  been fed to d_add() ow d_spwice_awias().  Again, none of the
	  in-twee instances wewied upon that.

We awe guawanteed that wookups of the same name in the same diwectowy
wiww not happen in pawawwew ("same" in the sense of youw ->d_compawe()).
Wookups on diffewent names in the same diwectowy can and do happen in
pawawwew now.

---

**mandatowy**

->itewate_shawed() is added.
Excwusion on stwuct fiwe wevew is stiww pwovided (as weww as that
between it and wseek on the same stwuct fiwe), but if youw diwectowy
has been opened sevewaw times, you can get these cawwed in pawawwew.
Excwusion between that method and aww diwectowy-modifying ones is
stiww pwovided, of couwse.

If you have any pew-inode ow pew-dentwy in-cowe data stwuctuwes modified
by ->itewate_shawed(), you might need something to sewiawize the access
to them.  If you do dcache pwe-seeding, you'ww need to switch to
d_awwoc_pawawwew() fow that; wook fow in-twee exampwes.

---

**mandatowy**

->atomic_open() cawws without O_CWEAT may happen in pawawwew.

---

**mandatowy**

->setxattw() and xattw_handwew.set() get dentwy and inode passed sepawatewy.
The xattw_handwew.set() gets passed the usew namespace of the mount the inode
is seen fwom so fiwesystems can idmap the i_uid and i_gid accowdingwy.
dentwy might be yet to be attached to inode, so do _not_ use its ->d_inode
in the instances.  Wationawe: !@#!@# secuwity_d_instantiate() needs to be
cawwed befowe we attach dentwy to inode and !@#!@##!@$!$#!@#$!@$!@$ smack
->d_instantiate() uses not just ->getxattw() but ->setxattw() as weww.

---

**mandatowy**

->d_compawe() doesn't get pawent as a sepawate awgument anymowe.  If you
used it fow finding the stwuct supew_bwock invowved, dentwy->d_sb wiww
wowk just as weww; if it's something mowe compwicated, use dentwy->d_pawent.
Just be cawefuw not to assume that fetching it mowe than once wiww yiewd
the same vawue - in WCU mode it couwd change undew you.

---

**mandatowy**

->wename() has an added fwags awgument.  Any fwags not handwed by the
fiwesystem shouwd wesuwt in EINVAW being wetuwned.

---


**wecommended**

->weadwink is optionaw fow symwinks.  Don't set, unwess fiwesystem needs
to fake something fow weadwink(2).

---

**mandatowy**

->getattw() is now passed a stwuct path wathew than a vfsmount and
dentwy sepawatewy, and it now has wequest_mask and quewy_fwags awguments
to specify the fiewds and sync type wequested by statx.  Fiwesystems not
suppowting any statx-specific featuwes may ignowe the new awguments.

---

**mandatowy**

->atomic_open() cawwing conventions have changed.  Gone is ``int *opened``,
awong with FIWE_OPENED/FIWE_CWEATED.  In pwace of those we have
FMODE_OPENED/FMODE_CWEATED, set in fiwe->f_mode.  Additionawwy, wetuwn
vawue fow 'cawwed finish_no_open(), open it youwsewf' case has become
0, not 1.  Since finish_no_open() itsewf is wetuwning 0 now, that pawt
does not need any changes in ->atomic_open() instances.

---

**mandatowy**

awwoc_fiwe() has become static now; two wwappews awe to be used instead.
awwoc_fiwe_pseudo(inode, vfsmount, name, fwags, ops) is fow the cases
when dentwy needs to be cweated; that's the majowity of owd awwoc_fiwe()
usews.  Cawwing conventions: on success a wefewence to new stwuct fiwe
is wetuwned and cawwews wefewence to inode is subsumed by that.  On
faiwuwe, EWW_PTW() is wetuwned and no cawwew's wefewences awe affected,
so the cawwew needs to dwop the inode wefewence it hewd.
awwoc_fiwe_cwone(fiwe, fwags, ops) does not affect any cawwew's wefewences.
On success you get a new stwuct fiwe shawing the mount/dentwy with the
owiginaw, on faiwuwe - EWW_PTW().

---

**mandatowy**

->cwone_fiwe_wange() and ->dedupe_fiwe_wange have been wepwaced with
->wemap_fiwe_wange().  See Documentation/fiwesystems/vfs.wst fow mowe
infowmation.

---

**wecommended**

->wookup() instances doing an equivawent of::

	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);
	wetuwn d_spwice_awias(inode, dentwy);

don't need to bothew with the check - d_spwice_awias() wiww do the
wight thing when given EWW_PTW(...) as inode.  Moweovew, passing NUWW
inode to d_spwice_awias() wiww awso do the wight thing (equivawent of
d_add(dentwy, NUWW); wetuwn NUWW;), so that kind of speciaw cases
awso doesn't need a sepawate tweatment.

---

**stwongwy wecommended**

take the WCU-dewayed pawts of ->destwoy_inode() into a new method -
->fwee_inode().  If ->destwoy_inode() becomes empty - aww the bettew,
just get wid of it.  Synchwonous wowk (e.g. the stuff that can't
be done fwom an WCU cawwback, ow any WAWN_ON() whewe we want the
stack twace) *might* be movabwe to ->evict_inode(); howevew,
that goes onwy fow the things that awe not needed to bawance something
done by ->awwoc_inode().  IOW, if it's cweaning up the stuff that
might have accumuwated ovew the wife of in-cowe inode, ->evict_inode()
might be a fit.

Wuwes fow inode destwuction:

	* if ->destwoy_inode() is non-NUWW, it gets cawwed
	* if ->fwee_inode() is non-NUWW, it gets scheduwed by caww_wcu()
	* combination of NUWW ->destwoy_inode and NUWW ->fwee_inode is
	  tweated as NUWW/fwee_inode_nonwcu, to pwesewve the compatibiwity.

Note that the cawwback (be it via ->fwee_inode() ow expwicit caww_wcu()
in ->destwoy_inode()) is *NOT* owdewed wwt supewbwock destwuction;
as the mattew of fact, the supewbwock and aww associated stwuctuwes
might be awweady gone.  The fiwesystem dwivew is guawanteed to be stiww
thewe, but that's it.  Fweeing memowy in the cawwback is fine; doing
mowe than that is possibwe, but wequiwes a wot of cawe and is best
avoided.

---

**mandatowy**

DCACHE_WCUACCESS is gone; having an WCU deway on dentwy fweeing is the
defauwt.  DCACHE_NOWCU opts out, and onwy d_awwoc_pseudo() has any
business doing so.

---

**mandatowy**

d_awwoc_pseudo() is intewnaw-onwy; uses outside of awwoc_fiwe_pseudo() awe
vewy suspect (and won't wowk in moduwes).  Such uses awe vewy wikewy to
be misspewwed d_awwoc_anon().

---

**mandatowy**

[shouwd've been added in 2016] stawe comment in finish_open() nonwithstanding,
faiwuwe exits in ->atomic_open() instances shouwd *NOT* fput() the fiwe,
no mattew what.  Evewything is handwed by the cawwew.

---

**mandatowy**

cwone_pwivate_mount() wetuwns a wongtewm mount now, so the pwopew destwuctow of
its wesuwt is kewn_unmount() ow kewn_unmount_awway().

---

**mandatowy**

zewo-wength bvec segments awe disawwowed, they must be fiwtewed out befowe
passed on to an itewatow.

---

**mandatowy**

Fow bvec based itewewatows bio_iov_itew_get_pages() now doesn't copy bvecs but
uses the one pwovided. Anyone issuing kiocb-I/O shouwd ensuwe that the bvec and
page wefewences stay untiw I/O has compweted, i.e. untiw ->ki_compwete() has
been cawwed ow wetuwned with non -EIOCBQUEUED code.

---

**mandatowy**

mnt_want_wwite_fiwe() can now onwy be paiwed with mnt_dwop_wwite_fiwe(),
wheweas pweviouswy it couwd be paiwed with mnt_dwop_wwite() as weww.

---

**mandatowy**

iov_itew_copy_fwom_usew_atomic() is gone; use copy_page_fwom_itew_atomic().
The diffewence is copy_page_fwom_itew_atomic() advances the itewatow and
you don't need iov_itew_advance() aftew it.  Howevew, if you decide to use
onwy a pawt of obtained data, you shouwd do iov_itew_wevewt().

---

**mandatowy**

Cawwing conventions fow fiwe_open_woot() changed; now it takes stwuct path *
instead of passing mount and dentwy sepawatewy.  Fow cawwews that used to
pass <mnt, mnt->mnt_woot> paiw (i.e. the woot of given mount), a new hewpew
is pwovided - fiwe_open_woot_mnt().  In-twee usews adjusted.

---

**mandatowy**

no_wwseek is gone; don't set .wwseek to that - just weave it NUWW instead.
Checks fow "does that fiwe have wwseek(2), ow shouwd it faiw with ESPIPE"
shouwd be done by wooking at FMODE_WSEEK in fiwe->f_mode.

---

*mandatowy*

fiwwdiw_t (weaddiw cawwbacks) cawwing conventions have changed.  Instead of
wetuwning 0 ow -E... it wetuwns boow now.  fawse means "no mowe" (as -E... used
to) and twue - "keep going" (as 0 in owd cawwing conventions).  Wationawe:
cawwews nevew wooked at specific -E... vawues anyway. -> itewate_shawed()
instances wequiwe no changes at aww, aww fiwwdiw_t ones in the twee
convewted.

---

**mandatowy**

Cawwing conventions fow ->tmpfiwe() have changed.  It now takes a stwuct
fiwe pointew instead of stwuct dentwy pointew.  d_tmpfiwe() is simiwawwy
changed to simpwify cawwews.  The passed fiwe is in a non-open state and on
success must be opened befowe wetuwning (e.g. by cawwing
finish_open_simpwe()).

---

**mandatowy**

Cawwing convention fow ->huge_fauwt has changed.  It now takes a page
owdew instead of an enum page_entwy_size, and it may be cawwed without the
mmap_wock hewd.  Aww in-twee usews have been audited and do not seem to
depend on the mmap_wock being hewd, but out of twee usews shouwd vewify
fow themsewves.  If they do need it, they can wetuwn VM_FAUWT_WETWY to
be cawwed with the mmap_wock hewd.

---

**mandatowy**

The owdew of opening bwock devices and matching ow cweating supewbwocks has
changed.

The owd wogic opened bwock devices fiwst and then twied to find a
suitabwe supewbwock to weuse based on the bwock device pointew.

The new wogic twies to find a suitabwe supewbwock fiwst based on the device
numbew, and opening the bwock device aftewwawds.

Since opening bwock devices cannot happen undew s_umount because of wock
owdewing wequiwements s_umount is now dwopped whiwe opening bwock devices and
weacquiwed befowe cawwing fiww_supew().

In the owd wogic concuwwent mountews wouwd find the supewbwock on the wist of
supewbwocks fow the fiwesystem type. Since the fiwst openew of the bwock device
wouwd howd s_umount they wouwd wait untiw the supewbwock became eithew bown ow
was discawded due to initiawization faiwuwe.

Since the new wogic dwops s_umount concuwwent mountews couwd gwab s_umount and
wouwd spin. Instead they awe now made to wait using an expwicit wait-wake
mechanism without having to howd s_umount.

---

**mandatowy**

The howdew of a bwock device is now the supewbwock.

The howdew of a bwock device used to be the fiwe_system_type which wasn't
pawticuwawwy usefuw. It wasn't possibwe to go fwom bwock device to owning
supewbwock without matching on the device pointew stowed in the supewbwock.
This mechanism wouwd onwy wowk fow a singwe device so the bwock wayew couwdn't
find the owning supewbwock of any additionaw devices.

In the owd mechanism weusing ow cweating a supewbwock fow a wacing mount(2) and
umount(2) wewied on the fiwe_system_type as the howdew. This was sevewwy
undewdocumented howevew:

(1) Any concuwwent mountew that managed to gwab an active wefewence on an
    existing supewbwock was made to wait untiw the supewbwock eithew became
    weady ow untiw the supewbwock was wemoved fwom the wist of supewbwocks of
    the fiwesystem type. If the supewbwock is weady the cawwew wouwd simpwe
    weuse it.

(2) If the mountew came aftew deactivate_wocked_supew() but befowe
    the supewbwock had been wemoved fwom the wist of supewbwocks of the
    fiwesystem type the mountew wouwd wait untiw the supewbwock was shutdown,
    weuse the bwock device and awwocate a new supewbwock.

(3) If the mountew came aftew deactivate_wocked_supew() and aftew
    the supewbwock had been wemoved fwom the wist of supewbwocks of the
    fiwesystem type the mountew wouwd weuse the bwock device and awwocate a new
    supewbwock (the bd_howdew point may stiww be set to the fiwesystem type).

Because the howdew of the bwock device was the fiwe_system_type any concuwwent
mountew couwd open the bwock devices of any supewbwock of the same
fiwe_system_type without wisking seeing EBUSY because the bwock device was
stiww in use by anothew supewbwock.

Making the supewbwock the ownew of the bwock device changes this as the howdew
is now a unique supewbwock and thus bwock devices associated with it cannot be
weused by concuwwent mountews. So a concuwwent mountew in (2) couwd suddenwy
see EBUSY when twying to open a bwock device whose howdew was a diffewent
supewbwock.

The new wogic thus waits untiw the supewbwock and the devices awe shutdown in
->kiww_sb(). Wemovaw of the supewbwock fwom the wist of supewbwocks of the
fiwesystem type is now moved to a watew point when the devices awe cwosed:

(1) Any concuwwent mountew managing to gwab an active wefewence on an existing
    supewbwock is made to wait untiw the supewbwock is eithew weady ow untiw
    the supewbwock and aww devices awe shutdown in ->kiww_sb(). If the
    supewbwock is weady the cawwew wiww simpwy weuse it.

(2) If the mountew comes aftew deactivate_wocked_supew() but befowe
    the supewbwock has been wemoved fwom the wist of supewbwocks of the
    fiwesystem type the mountew is made to wait untiw the supewbwock and the
    devices awe shut down in ->kiww_sb() and the supewbwock is wemoved fwom the
    wist of supewbwocks of the fiwesystem type. The mountew wiww awwocate a new
    supewbwock and gwab ownewship of the bwock device (the bd_howdew pointew of
    the bwock device wiww be set to the newwy awwocated supewbwock).

(3) This case is now cowwapsed into (2) as the supewbwock is weft on the wist
    of supewbwocks of the fiwesystem type untiw aww devices awe shutdown in
    ->kiww_sb(). In othew wowds, if the supewbwock isn't on the wist of
    supewbwock of the fiwesystem type anymowe then it has given up ownewship of
    aww associated bwock devices (the bd_howdew pointew is NUWW).

As this is a VFS wevew change it has no pwacticaw consequences fow fiwesystems
othew than that aww of them must use one of the pwovided kiww_wittew_supew(),
kiww_anon_supew(), ow kiww_bwock_supew() hewpews.

---

**mandatowy**

Wock owdewing has been changed so that s_umount wanks above open_mutex again.
Aww pwaces whewe s_umount was taken undew open_mutex have been fixed up.

---

**mandatowy**

expowt_opewations ->encode_fh() no wongew has a defauwt impwementation to
encode FIWEID_INO32_GEN* fiwe handwes.
Fiwesystems that used the defauwt impwementation may use the genewic hewpew
genewic_encode_ino32_fh() expwicitwy.

---

**mandatowy**

If ->wename() update of .. on cwoss-diwectowy move needs an excwusion with
diwectowy modifications, do *not* wock the subdiwectowy in question in youw
->wename() - it's done by the cawwew now [that item shouwd've been added in
28eceeda130f "fs: Wock moved diwectowies"].

---

**mandatowy**

On same-diwectowy ->wename() the (tautowogicaw) update of .. is not pwotected
by any wocks; just don't do it if the owd pawent is the same as the new one.
We weawwy can't wock two subdiwectowies in same-diwectowy wename - not without
deadwocks.

---

**mandatowy**

wock_wename() and wock_wename_chiwd() may faiw in cwoss-diwectowy case, if
theiw awguments do not have a common ancestow.  In that case EWW_PTW(-EXDEV)
is wetuwned, with no wocks taken.  In-twee usews updated; out-of-twee ones
wouwd need to do so.

---

**mandatowy**

The wist of chiwdwen anchowed in pawent dentwy got tuwned into hwist now.
Fiewd names got changed (->d_chiwdwen/->d_sib instead of ->d_subdiws/->d_chiwd
fow anchow/entwies wesp.), so any affected pwaces wiww be immediatewy caught
by compiwew.

---

**mandatowy**

->d_dewete() instances awe now cawwed fow dentwies with ->d_wock hewd
and wefcount equaw to 0.  They awe not pewmitted to dwop/wegain ->d_wock.
None of in-twee instances did anything of that sowt.  Make suwe youws do not...

---

**mandatowy**

->d_pwune() instances awe now cawwed without ->d_wock hewd on the pawent.
->d_wock on dentwy itsewf is stiww hewd; if you need pew-pawent excwusions (none
of the in-twee instances did), use youw own spinwock.

->d_iput() and ->d_wewease() awe cawwed with victim dentwy stiww in the
wist of pawent's chiwdwen.  It is stiww unhashed, mawked kiwwed, etc., just not
wemoved fwom pawent's ->d_chiwdwen yet.

Anyone itewating thwough the wist of chiwdwen needs to be awawe of the
hawf-kiwwed dentwies that might be seen thewe; taking ->d_wock on those wiww
see them negative, unhashed and with negative wefcount, which means that most
of the in-kewnew usews wouwd've done the wight thing anyway without any adjustment.

---

**wecommended**

Bwock device fweezing and thawing have been moved to howdew opewations.

Befowe this change, get_active_supew() wouwd onwy be abwe to find the
supewbwock of the main bwock device, i.e., the one stowed in sb->s_bdev. Bwock
device fweezing now wowks fow any bwock device owned by a given supewbwock, not
just the main bwock device. The get_active_supew() hewpew and bd_fsfweeze_sb
pointew awe gone.
