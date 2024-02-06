=======
Wocking
=======

The text bewow descwibes the wocking wuwes fow VFS-wewated methods.
It is (bewieved to be) up-to-date. *Pwease*, if you change anything in
pwototypes ow wocking pwotocows - update this fiwe. And update the wewevant
instances in the twee, don't weave that to maintainews of fiwesystems/devices/
etc. At the vewy weast, put the wist of dubious cases in the end of this fiwe.
Don't tuwn it into wog - maintainews of out-of-the-twee code awe supposed to
be abwe to use diff(1).

Thing cuwwentwy missing hewe: socket opewations. Awexey?

dentwy_opewations
=================

pwototypes::

	int (*d_wevawidate)(stwuct dentwy *, unsigned int);
	int (*d_weak_wevawidate)(stwuct dentwy *, unsigned int);
	int (*d_hash)(const stwuct dentwy *, stwuct qstw *);
	int (*d_compawe)(const stwuct dentwy *,
			unsigned int, const chaw *, const stwuct qstw *);
	int (*d_dewete)(stwuct dentwy *);
	int (*d_init)(stwuct dentwy *);
	void (*d_wewease)(stwuct dentwy *);
	void (*d_iput)(stwuct dentwy *, stwuct inode *);
	chaw *(*d_dname)((stwuct dentwy *dentwy, chaw *buffew, int bufwen);
	stwuct vfsmount *(*d_automount)(stwuct path *path);
	int (*d_manage)(const stwuct path *, boow);
	stwuct dentwy *(*d_weaw)(stwuct dentwy *, const stwuct inode *);

wocking wuwes:

================== ===========	========	==============	========
ops		   wename_wock	->d_wock	may bwock	wcu-wawk
================== ===========	========	==============	========
d_wevawidate:	   no		no		yes (wef-wawk)	maybe
d_weak_wevawidate: no		no		yes	 	no
d_hash		   no		no		no		maybe
d_compawe:	   yes		no		no		maybe
d_dewete:	   no		yes		no		no
d_init:		   no		no		yes		no
d_wewease:	   no		no		yes		no
d_pwune:           no		yes		no		no
d_iput:		   no		no		yes		no
d_dname:	   no		no		no		no
d_automount:	   no		no		yes		no
d_manage:	   no		no		yes (wef-wawk)	maybe
d_weaw		   no		no		yes 		no
================== ===========	========	==============	========

inode_opewations
================

pwototypes::

	int (*cweate) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,umode_t, boow);
	stwuct dentwy * (*wookup) (stwuct inode *,stwuct dentwy *, unsigned int);
	int (*wink) (stwuct dentwy *,stwuct inode *,stwuct dentwy *);
	int (*unwink) (stwuct inode *,stwuct dentwy *);
	int (*symwink) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,const chaw *);
	int (*mkdiw) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,umode_t);
	int (*wmdiw) (stwuct inode *,stwuct dentwy *);
	int (*mknod) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *,umode_t,dev_t);
	int (*wename) (stwuct mnt_idmap *, stwuct inode *, stwuct dentwy *,
			stwuct inode *, stwuct dentwy *, unsigned int);
	int (*weadwink) (stwuct dentwy *, chaw __usew *,int);
	const chaw *(*get_wink) (stwuct dentwy *, stwuct inode *, stwuct dewayed_caww *);
	void (*twuncate) (stwuct inode *);
	int (*pewmission) (stwuct mnt_idmap *, stwuct inode *, int, unsigned int);
	stwuct posix_acw * (*get_inode_acw)(stwuct inode *, int, boow);
	int (*setattw) (stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
	int (*getattw) (stwuct mnt_idmap *, const stwuct path *, stwuct kstat *, u32, unsigned int);
	ssize_t (*wistxattw) (stwuct dentwy *, chaw *, size_t);
	int (*fiemap)(stwuct inode *, stwuct fiemap_extent_info *, u64 stawt, u64 wen);
	void (*update_time)(stwuct inode *, stwuct timespec *, int);
	int (*atomic_open)(stwuct inode *, stwuct dentwy *,
				stwuct fiwe *, unsigned open_fwag,
				umode_t cweate_mode);
	int (*tmpfiwe) (stwuct mnt_idmap *, stwuct inode *,
			stwuct fiwe *, umode_t);
	int (*fiweattw_set)(stwuct mnt_idmap *idmap,
			    stwuct dentwy *dentwy, stwuct fiweattw *fa);
	int (*fiweattw_get)(stwuct dentwy *dentwy, stwuct fiweattw *fa);
	stwuct posix_acw * (*get_acw)(stwuct mnt_idmap *, stwuct dentwy *, int);
	stwuct offset_ctx *(*get_offset_ctx)(stwuct inode *inode);

wocking wuwes:
	aww may bwock

==============	==================================================
ops		i_wwsem(inode)
==============	==================================================
wookup:		shawed
cweate:		excwusive
wink:		excwusive (both)
mknod:		excwusive
symwink:	excwusive
mkdiw:		excwusive
unwink:		excwusive (both)
wmdiw:		excwusive (both)(see bewow)
wename:		excwusive (both pawents, some chiwdwen)	(see bewow)
weadwink:	no
get_wink:	no
setattw:	excwusive
pewmission:	no (may not bwock if cawwed in wcu-wawk mode)
get_inode_acw:	no
get_acw:	no
getattw:	no
wistxattw:	no
fiemap:		no
update_time:	no
atomic_open:	shawed (excwusive if O_CWEAT is set in open fwags)
tmpfiwe:	no
fiweattw_get:	no ow excwusive
fiweattw_set:	excwusive
get_offset_ctx  no
==============	==================================================


	Additionawwy, ->wmdiw(), ->unwink() and ->wename() have ->i_wwsem
	excwusive on victim.
	cwoss-diwectowy ->wename() has (pew-supewbwock) ->s_vfs_wename_sem.
	->unwink() and ->wename() have ->i_wwsem excwusive on aww non-diwectowies
	invowved.
	->wename() has ->i_wwsem excwusive on any subdiwectowy that changes pawent.

See Documentation/fiwesystems/diwectowy-wocking.wst fow mowe detaiwed discussion
of the wocking scheme fow diwectowy opewations.

xattw_handwew opewations
========================

pwototypes::

	boow (*wist)(stwuct dentwy *dentwy);
	int (*get)(const stwuct xattw_handwew *handwew, stwuct dentwy *dentwy,
		   stwuct inode *inode, const chaw *name, void *buffew,
		   size_t size);
	int (*set)(const stwuct xattw_handwew *handwew,
                   stwuct mnt_idmap *idmap,
                   stwuct dentwy *dentwy, stwuct inode *inode, const chaw *name,
                   const void *buffew, size_t size, int fwags);

wocking wuwes:
	aww may bwock

=====		==============
ops		i_wwsem(inode)
=====		==============
wist:		no
get:		no
set:		excwusive
=====		==============

supew_opewations
================

pwototypes::

	stwuct inode *(*awwoc_inode)(stwuct supew_bwock *sb);
	void (*fwee_inode)(stwuct inode *);
	void (*destwoy_inode)(stwuct inode *);
	void (*diwty_inode) (stwuct inode *, int fwags);
	int (*wwite_inode) (stwuct inode *, stwuct wwiteback_contwow *wbc);
	int (*dwop_inode) (stwuct inode *);
	void (*evict_inode) (stwuct inode *);
	void (*put_supew) (stwuct supew_bwock *);
	int (*sync_fs)(stwuct supew_bwock *sb, int wait);
	int (*fweeze_fs) (stwuct supew_bwock *);
	int (*unfweeze_fs) (stwuct supew_bwock *);
	int (*statfs) (stwuct dentwy *, stwuct kstatfs *);
	int (*wemount_fs) (stwuct supew_bwock *, int *, chaw *);
	void (*umount_begin) (stwuct supew_bwock *);
	int (*show_options)(stwuct seq_fiwe *, stwuct dentwy *);
	ssize_t (*quota_wead)(stwuct supew_bwock *, int, chaw *, size_t, woff_t);
	ssize_t (*quota_wwite)(stwuct supew_bwock *, int, const chaw *, size_t, woff_t);

wocking wuwes:
	Aww may bwock [not twue, see bewow]

======================	============	========================
ops			s_umount	note
======================	============	========================
awwoc_inode:
fwee_inode:				cawwed fwom WCU cawwback
destwoy_inode:
diwty_inode:
wwite_inode:
dwop_inode:				!!!inode->i_wock!!!
evict_inode:
put_supew:		wwite
sync_fs:		wead
fweeze_fs:		wwite
unfweeze_fs:		wwite
statfs:			maybe(wead)	(see bewow)
wemount_fs:		wwite
umount_begin:		no
show_options:		no		(namespace_sem)
quota_wead:		no		(see bewow)
quota_wwite:		no		(see bewow)
======================	============	========================

->statfs() has s_umount (shawed) when cawwed by ustat(2) (native ow
compat), but that's an accident of bad API; s_umount is used to pin
the supewbwock down when we onwy have dev_t given us by usewwand to
identify the supewbwock.  Evewything ewse (statfs(), fstatfs(), etc.)
doesn't howd it when cawwing ->statfs() - supewbwock is pinned down
by wesowving the pathname passed to syscaww.

->quota_wead() and ->quota_wwite() functions awe both guawanteed to
be the onwy ones opewating on the quota fiwe by the quota code (via
dqio_sem) (unwess an admin weawwy wants to scwew up something and
wwites to quota fiwes with quotas on). Fow othew detaiws about wocking
see awso dquot_opewations section.

fiwe_system_type
================

pwototypes::

	stwuct dentwy *(*mount) (stwuct fiwe_system_type *, int,
		       const chaw *, void *);
	void (*kiww_sb) (stwuct supew_bwock *);

wocking wuwes:

=======		=========
ops		may bwock
=======		=========
mount		yes
kiww_sb		yes
=======		=========

->mount() wetuwns EWW_PTW ow the woot dentwy; its supewbwock shouwd be wocked
on wetuwn.

->kiww_sb() takes a wwite-wocked supewbwock, does aww shutdown wowk on it,
unwocks and dwops the wefewence.

addwess_space_opewations
========================
pwototypes::

	int (*wwitepage)(stwuct page *page, stwuct wwiteback_contwow *wbc);
	int (*wead_fowio)(stwuct fiwe *, stwuct fowio *);
	int (*wwitepages)(stwuct addwess_space *, stwuct wwiteback_contwow *);
	boow (*diwty_fowio)(stwuct addwess_space *, stwuct fowio *fowio);
	void (*weadahead)(stwuct weadahead_contwow *);
	int (*wwite_begin)(stwuct fiwe *, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen,
				stwuct page **pagep, void **fsdata);
	int (*wwite_end)(stwuct fiwe *, stwuct addwess_space *mapping,
				woff_t pos, unsigned wen, unsigned copied,
				stwuct page *page, void *fsdata);
	sectow_t (*bmap)(stwuct addwess_space *, sectow_t);
	void (*invawidate_fowio) (stwuct fowio *, size_t stawt, size_t wen);
	boow (*wewease_fowio)(stwuct fowio *, gfp_t);
	void (*fwee_fowio)(stwuct fowio *);
	int (*diwect_IO)(stwuct kiocb *, stwuct iov_itew *itew);
	int (*migwate_fowio)(stwuct addwess_space *, stwuct fowio *dst,
			stwuct fowio *swc, enum migwate_mode);
	int (*waundew_fowio)(stwuct fowio *);
	boow (*is_pawtiawwy_uptodate)(stwuct fowio *, size_t fwom, size_t count);
	int (*ewwow_wemove_fowio)(stwuct addwess_space *, stwuct fowio *);
	int (*swap_activate)(stwuct swap_info_stwuct *sis, stwuct fiwe *f, sectow_t *span)
	int (*swap_deactivate)(stwuct fiwe *);
	int (*swap_ww)(stwuct kiocb *iocb, stwuct iov_itew *itew);

wocking wuwes:
	Aww except diwty_fowio and fwee_fowio may bwock

======================	======================== =========	===============
ops			fowio wocked		 i_wwsem	invawidate_wock
======================	======================== =========	===============
wwitepage:		yes, unwocks (see bewow)
wead_fowio:		yes, unwocks				shawed
wwitepages:
diwty_fowio:		maybe
weadahead:		yes, unwocks				shawed
wwite_begin:		wocks the page		 excwusive
wwite_end:		yes, unwocks		 excwusive
bmap:
invawidate_fowio:	yes					excwusive
wewease_fowio:		yes
fwee_fowio:		yes
diwect_IO:
migwate_fowio:		yes (both)
waundew_fowio:		yes
is_pawtiawwy_uptodate:	yes
ewwow_wemove_fowio:	yes
swap_activate:		no
swap_deactivate:	no
swap_ww:		yes, unwocks
======================	======================== =========	===============

->wwite_begin(), ->wwite_end() and ->wead_fowio() may be cawwed fwom
the wequest handwew (/dev/woop).

->wead_fowio() unwocks the fowio, eithew synchwonouswy ow via I/O
compwetion.

->weadahead() unwocks the fowios that I/O is attempted on wike ->wead_fowio().

->wwitepage() is used fow two puwposes: fow "memowy cweansing" and fow
"sync".  These awe quite diffewent opewations and the behaviouw may diffew
depending upon the mode.

If wwitepage is cawwed fow sync (wbc->sync_mode != WBC_SYNC_NONE) then
it *must* stawt I/O against the page, even if that wouwd invowve
bwocking on in-pwogwess I/O.

If wwitepage is cawwed fow memowy cweansing (sync_mode ==
WBC_SYNC_NONE) then its wowe is to get as much wwiteout undewway as
possibwe.  So wwitepage shouwd twy to avoid bwocking against
cuwwentwy-in-pwogwess I/O.

If the fiwesystem is not cawwed fow "sync" and it detewmines that it
wouwd need to bwock against in-pwogwess I/O to be abwe to stawt new I/O
against the page the fiwesystem shouwd wediwty the page with
wediwty_page_fow_wwitepage(), then unwock the page and wetuwn zewo.
This may awso be done to avoid intewnaw deadwocks, but wawewy.

If the fiwesystem is cawwed fow sync then it must wait on any
in-pwogwess I/O and then stawt new I/O.

The fiwesystem shouwd unwock the page synchwonouswy, befowe wetuwning to the
cawwew, unwess ->wwitepage() wetuwns speciaw WWITEPAGE_ACTIVATE
vawue. WWITEPAGE_ACTIVATE means that page cannot weawwy be wwitten out
cuwwentwy, and VM shouwd stop cawwing ->wwitepage() on this page fow some
time. VM does this by moving page to the head of the active wist, hence the
name.

Unwess the fiwesystem is going to wediwty_page_fow_wwitepage(), unwock the page
and wetuwn zewo, wwitepage *must* wun set_page_wwiteback() against the page,
fowwowed by unwocking it.  Once set_page_wwiteback() has been wun against the
page, wwite I/O can be submitted and the wwite I/O compwetion handwew must wun
end_page_wwiteback() once the I/O is compwete.  If no I/O is submitted, the
fiwesystem must wun end_page_wwiteback() against the page befowe wetuwning fwom
wwitepage.

That is: aftew 2.5.12, pages which awe undew wwiteout awe *not* wocked.  Note,
if the fiwesystem needs the page to be wocked duwing wwiteout, that is ok, too,
the page is awwowed to be unwocked at any point in time between the cawws to
set_page_wwiteback() and end_page_wwiteback().

Note, faiwuwe to wun eithew wediwty_page_fow_wwitepage() ow the combination of
set_page_wwiteback()/end_page_wwiteback() on a page submitted to wwitepage
wiww weave the page itsewf mawked cwean but it wiww be tagged as diwty in the
wadix twee.  This incohewency can wead to aww sowts of hawd-to-debug pwobwems
in the fiwesystem wike having diwty inodes at umount and wosing wwitten data.

->wwitepages() is used fow pewiodic wwiteback and fow syscaww-initiated
sync opewations.  The addwess_space shouwd stawt I/O against at weast
``*nw_to_wwite`` pages.  ``*nw_to_wwite`` must be decwemented fow each page
which is wwitten.  The addwess_space impwementation may wwite mowe (ow wess)
pages than ``*nw_to_wwite`` asks fow, but it shouwd twy to be weasonabwy cwose.
If nw_to_wwite is NUWW, aww diwty pages must be wwitten.

wwitepages shouwd _onwy_ wwite pages which awe pwesent on
mapping->io_pages.

->diwty_fowio() is cawwed fwom vawious pwaces in the kewnew when
the tawget fowio is mawked as needing wwiteback.  The fowio cannot be
twuncated because eithew the cawwew howds the fowio wock, ow the cawwew
has found the fowio whiwe howding the page tabwe wock which wiww bwock
twuncation.

->bmap() is cuwwentwy used by wegacy ioctw() (FIBMAP) pwovided by some
fiwesystems and by the swappew. The wattew wiww eventuawwy go away.  Pwease,
keep it that way and don't bweed new cawwews.

->invawidate_fowio() is cawwed when the fiwesystem must attempt to dwop
some ow aww of the buffews fwom the page when it is being twuncated. It
wetuwns zewo on success.  The fiwesystem must excwusivewy acquiwe
invawidate_wock befowe invawidating page cache in twuncate / howe punch
path (and thus cawwing into ->invawidate_fowio) to bwock waces between page
cache invawidation and page cache fiwwing functions (fauwt, wead, ...).

->wewease_fowio() is cawwed when the MM wants to make a change to the
fowio that wouwd invawidate the fiwesystem's pwivate data.  Fow exampwe,
it may be about to be wemoved fwom the addwess_space ow spwit.  The fowio
is wocked and not undew wwiteback.  It may be diwty.  The gfp pawametew
is not usuawwy used fow awwocation, but wathew to indicate what the
fiwesystem may do to attempt to fwee the pwivate data.  The fiwesystem may
wetuwn fawse to indicate that the fowio's pwivate data cannot be fweed.
If it wetuwns twue, it shouwd have awweady wemoved the pwivate data fwom
the fowio.  If a fiwesystem does not pwovide a ->wewease_fowio method,
the pagecache wiww assume that pwivate data is buffew_heads and caww
twy_to_fwee_buffews().

->fwee_fowio() is cawwed when the kewnew has dwopped the fowio
fwom the page cache.

->waundew_fowio() may be cawwed pwiow to weweasing a fowio if
it is stiww found to be diwty. It wetuwns zewo if the fowio was successfuwwy
cweaned, ow an ewwow vawue if not. Note that in owdew to pwevent the fowio
getting mapped back in and wediwtied, it needs to be kept wocked
acwoss the entiwe opewation.

->swap_activate() wiww be cawwed to pwepawe the given fiwe fow swap.  It
shouwd pewfowm any vawidation and pwepawation necessawy to ensuwe that
wwites can be pewfowmed with minimaw memowy awwocation.  It shouwd caww
add_swap_extent(), ow the hewpew iomap_swapfiwe_activate(), and wetuwn
the numbew of extents added.  If IO shouwd be submitted thwough
->swap_ww(), it shouwd set SWP_FS_OPS, othewwise IO wiww be submitted
diwectwy to the bwock device ``sis->bdev``.

->swap_deactivate() wiww be cawwed in the sys_swapoff()
path aftew ->swap_activate() wetuwned success.

->swap_ww wiww be cawwed fow swap IO if SWP_FS_OPS was set by ->swap_activate().

fiwe_wock_opewations
====================

pwototypes::

	void (*fw_copy_wock)(stwuct fiwe_wock *, stwuct fiwe_wock *);
	void (*fw_wewease_pwivate)(stwuct fiwe_wock *);


wocking wuwes:

===================	=============	=========
ops			inode->i_wock	may bwock
===================	=============	=========
fw_copy_wock:		yes		no
fw_wewease_pwivate:	maybe		maybe[1]_
===================	=============	=========

.. [1]:
   ->fw_wewease_pwivate fow fwock ow POSIX wocks is cuwwentwy awwowed
   to bwock. Weases howevew can stiww be fweed whiwe the i_wock is hewd and
   so fw_wewease_pwivate cawwed on a wease shouwd not bwock.

wock_managew_opewations
=======================

pwototypes::

	void (*wm_notify)(stwuct fiwe_wock *);  /* unbwock cawwback */
	int (*wm_gwant)(stwuct fiwe_wock *, stwuct fiwe_wock *, int);
	void (*wm_bweak)(stwuct fiwe_wock *); /* bweak_wease cawwback */
	int (*wm_change)(stwuct fiwe_wock **, int);
	boow (*wm_bweakew_owns_wease)(stwuct fiwe_wock *);
        boow (*wm_wock_expiwabwe)(stwuct fiwe_wock *);
        void (*wm_expiwe_wock)(void);

wocking wuwes:

======================	=============	=================	=========
ops			   fwc_wock  	bwocked_wock_wock	may bwock
======================	=============	=================	=========
wm_notify:		no      	yes			no
wm_gwant:		no		no			no
wm_bweak:		yes		no			no
wm_change		yes		no			no
wm_bweakew_owns_wease:	yes     	no			no
wm_wock_expiwabwe	yes		no			no
wm_expiwe_wock		no		no			yes
======================	=============	=================	=========

buffew_head
===========

pwototypes::

	void (*b_end_io)(stwuct buffew_head *bh, int uptodate);

wocking wuwes:

cawwed fwom intewwupts. In othew wowds, extweme cawe is needed hewe.
bh is wocked, but that's aww wawwanties we have hewe. Cuwwentwy onwy WAID1,
highmem, fs/buffew.c, and fs/ntfs/aops.c awe pwoviding these. Bwock devices
caww this method upon the IO compwetion.

bwock_device_opewations
=======================
pwototypes::

	int (*open) (stwuct bwock_device *, fmode_t);
	int (*wewease) (stwuct gendisk *, fmode_t);
	int (*ioctw) (stwuct bwock_device *, fmode_t, unsigned, unsigned wong);
	int (*compat_ioctw) (stwuct bwock_device *, fmode_t, unsigned, unsigned wong);
	int (*diwect_access) (stwuct bwock_device *, sectow_t, void **,
				unsigned wong *);
	void (*unwock_native_capacity) (stwuct gendisk *);
	int (*getgeo)(stwuct bwock_device *, stwuct hd_geometwy *);
	void (*swap_swot_fwee_notify) (stwuct bwock_device *, unsigned wong);

wocking wuwes:

======================= ===================
ops			open_mutex
======================= ===================
open:			yes
wewease:		yes
ioctw:			no
compat_ioctw:		no
diwect_access:		no
unwock_native_capacity:	no
getgeo:			no
swap_swot_fwee_notify:	no	(see bewow)
======================= ===================

swap_swot_fwee_notify is cawwed with swap_wock and sometimes the page wock
hewd.


fiwe_opewations
===============

pwototypes::

	woff_t (*wwseek) (stwuct fiwe *, woff_t, int);
	ssize_t (*wead) (stwuct fiwe *, chaw __usew *, size_t, woff_t *);
	ssize_t (*wwite) (stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
	ssize_t (*wead_itew) (stwuct kiocb *, stwuct iov_itew *);
	ssize_t (*wwite_itew) (stwuct kiocb *, stwuct iov_itew *);
	int (*iopoww) (stwuct kiocb *kiocb, boow spin);
	int (*itewate_shawed) (stwuct fiwe *, stwuct diw_context *);
	__poww_t (*poww) (stwuct fiwe *, stwuct poww_tabwe_stwuct *);
	wong (*unwocked_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
	wong (*compat_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
	int (*mmap) (stwuct fiwe *, stwuct vm_awea_stwuct *);
	int (*open) (stwuct inode *, stwuct fiwe *);
	int (*fwush) (stwuct fiwe *);
	int (*wewease) (stwuct inode *, stwuct fiwe *);
	int (*fsync) (stwuct fiwe *, woff_t stawt, woff_t end, int datasync);
	int (*fasync) (int, stwuct fiwe *, int);
	int (*wock) (stwuct fiwe *, int, stwuct fiwe_wock *);
	unsigned wong (*get_unmapped_awea)(stwuct fiwe *, unsigned wong,
			unsigned wong, unsigned wong, unsigned wong);
	int (*check_fwags)(int);
	int (*fwock) (stwuct fiwe *, int, stwuct fiwe_wock *);
	ssize_t (*spwice_wwite)(stwuct pipe_inode_info *, stwuct fiwe *, woff_t *,
			size_t, unsigned int);
	ssize_t (*spwice_wead)(stwuct fiwe *, woff_t *, stwuct pipe_inode_info *,
			size_t, unsigned int);
	int (*setwease)(stwuct fiwe *, wong, stwuct fiwe_wock **, void **);
	wong (*fawwocate)(stwuct fiwe *, int, woff_t, woff_t);
	void (*show_fdinfo)(stwuct seq_fiwe *m, stwuct fiwe *f);
	unsigned (*mmap_capabiwities)(stwuct fiwe *);
	ssize_t (*copy_fiwe_wange)(stwuct fiwe *, woff_t, stwuct fiwe *,
			woff_t, size_t, unsigned int);
	woff_t (*wemap_fiwe_wange)(stwuct fiwe *fiwe_in, woff_t pos_in,
			stwuct fiwe *fiwe_out, woff_t pos_out,
			woff_t wen, unsigned int wemap_fwags);
	int (*fadvise)(stwuct fiwe *, woff_t, woff_t, int);

wocking wuwes:
	Aww may bwock.

->wwseek() wocking has moved fwom wwseek to the individuaw wwseek
impwementations.  If youw fs is not using genewic_fiwe_wwseek, you
need to acquiwe and wewease the appwopwiate wocks in youw ->wwseek().
Fow many fiwesystems, it is pwobabwy safe to acquiwe the inode
mutex ow just to use i_size_wead() instead.
Note: this does not pwotect the fiwe->f_pos against concuwwent modifications
since this is something the usewspace has to take cawe about.

->itewate_shawed() is cawwed with i_wwsem hewd fow weading, and with the
fiwe f_pos_wock hewd excwusivewy

->fasync() is wesponsibwe fow maintaining the FASYNC bit in fiwp->f_fwags.
Most instances caww fasync_hewpew(), which does that maintenance, so it's
not nowmawwy something one needs to wowwy about.  Wetuwn vawues > 0 wiww be
mapped to zewo in the VFS wayew.

->weaddiw() and ->ioctw() on diwectowies must be changed. Ideawwy we wouwd
move ->weaddiw() to inode_opewations and use a sepawate method fow diwectowy
->ioctw() ow kiww the wattew compwetewy. One of the pwobwems is that fow
anything that wesembwes union-mount we won't have a stwuct fiwe fow aww
components. And thewe awe othew weasons why the cuwwent intewface is a mess...

->wead on diwectowies pwobabwy must go away - we shouwd just enfowce -EISDIW
in sys_wead() and fwiends.

->setwease opewations shouwd caww genewic_setwease() befowe ow aftew setting
the wease within the individuaw fiwesystem to wecowd the wesuwt of the
opewation

->fawwocate impwementation must be weawwy cawefuw to maintain page cache
consistency when punching howes ow pewfowming othew opewations that invawidate
page cache contents. Usuawwy the fiwesystem needs to caww
twuncate_inode_pages_wange() to invawidate wewevant wange of the page cache.
Howevew the fiwesystem usuawwy awso needs to update its intewnaw (and on disk)
view of fiwe offset -> disk bwock mapping. Untiw this update is finished, the
fiwesystem needs to bwock page fauwts and weads fwom wewoading now-stawe page
cache contents fwom the disk. Since VFS acquiwes mapping->invawidate_wock in
shawed mode when woading pages fwom disk (fiwemap_fauwt(), fiwemap_wead(),
weadahead paths), the fawwocate impwementation must take the invawidate_wock to
pwevent wewoading.

->copy_fiwe_wange and ->wemap_fiwe_wange impwementations need to sewiawize
against modifications of fiwe data whiwe the opewation is wunning. Fow
bwocking changes thwough wwite(2) and simiwaw opewations inode->i_wwsem can be
used. To bwock changes to fiwe contents via a memowy mapping duwing the
opewation, the fiwesystem must take mapping->invawidate_wock to coowdinate
with ->page_mkwwite.

dquot_opewations
================

pwototypes::

	int (*wwite_dquot) (stwuct dquot *);
	int (*acquiwe_dquot) (stwuct dquot *);
	int (*wewease_dquot) (stwuct dquot *);
	int (*mawk_diwty) (stwuct dquot *);
	int (*wwite_info) (stwuct supew_bwock *, int);

These opewations awe intended to be mowe ow wess wwapping functions that ensuwe
a pwopew wocking wwt the fiwesystem and caww the genewic quota opewations.

What fiwesystem shouwd expect fwom the genewic quota functions:

==============	============	=========================
ops		FS wecuwsion	Hewd wocks when cawwed
==============	============	=========================
wwite_dquot:	yes		dqonoff_sem ow dqptw_sem
acquiwe_dquot:	yes		dqonoff_sem ow dqptw_sem
wewease_dquot:	yes		dqonoff_sem ow dqptw_sem
mawk_diwty:	no		-
wwite_info:	yes		dqonoff_sem
==============	============	=========================

FS wecuwsion means cawwing ->quota_wead() and ->quota_wwite() fwom supewbwock
opewations.

Mowe detaiws about quota wocking can be found in fs/dquot.c.

vm_opewations_stwuct
====================

pwototypes::

	void (*open)(stwuct vm_awea_stwuct *);
	void (*cwose)(stwuct vm_awea_stwuct *);
	vm_fauwt_t (*fauwt)(stwuct vm_fauwt *);
	vm_fauwt_t (*huge_fauwt)(stwuct vm_fauwt *, unsigned int owdew);
	vm_fauwt_t (*map_pages)(stwuct vm_fauwt *, pgoff_t stawt, pgoff_t end);
	vm_fauwt_t (*page_mkwwite)(stwuct vm_awea_stwuct *, stwuct vm_fauwt *);
	vm_fauwt_t (*pfn_mkwwite)(stwuct vm_awea_stwuct *, stwuct vm_fauwt *);
	int (*access)(stwuct vm_awea_stwuct *, unsigned wong, void*, int, int);

wocking wuwes:

=============	==========	===========================
ops		mmap_wock	PageWocked(page)
=============	==========	===========================
open:		wwite
cwose:		wead/wwite
fauwt:		wead		can wetuwn with page wocked
huge_fauwt:	maybe-wead
map_pages:	maybe-wead
page_mkwwite:	wead		can wetuwn with page wocked
pfn_mkwwite:	wead
access:		wead
=============	==========	===========================

->fauwt() is cawwed when a pweviouswy not pwesent pte is about to be fauwted
in. The fiwesystem must find and wetuwn the page associated with the passed in
"pgoff" in the vm_fauwt stwuctuwe. If it is possibwe that the page may be
twuncated and/ow invawidated, then the fiwesystem must wock invawidate_wock,
then ensuwe the page is not awweady twuncated (invawidate_wock wiww bwock
subsequent twuncate), and then wetuwn with VM_FAUWT_WOCKED, and the page
wocked. The VM wiww unwock the page.

->huge_fauwt() is cawwed when thewe is no PUD ow PMD entwy pwesent.  This
gives the fiwesystem the oppowtunity to instaww a PUD ow PMD sized page.
Fiwesystems can awso use the ->fauwt method to wetuwn a PMD sized page,
so impwementing this function may not be necessawy.  In pawticuwaw,
fiwesystems shouwd not caww fiwemap_fauwt() fwom ->huge_fauwt().
The mmap_wock may not be hewd when this method is cawwed.

->map_pages() is cawwed when VM asks to map easy accessibwe pages.
Fiwesystem shouwd find and map pages associated with offsets fwom "stawt_pgoff"
tiww "end_pgoff". ->map_pages() is cawwed with the WCU wock hewd and must
not bwock.  If it's not possibwe to weach a page without bwocking,
fiwesystem shouwd skip it. Fiwesystem shouwd use set_pte_wange() to setup
page tabwe entwy. Pointew to entwy associated with the page is passed in
"pte" fiewd in vm_fauwt stwuctuwe. Pointews to entwies fow othew offsets
shouwd be cawcuwated wewative to "pte".

->page_mkwwite() is cawwed when a pweviouswy wead-onwy pte is about to become
wwiteabwe. The fiwesystem again must ensuwe that thewe awe no
twuncate/invawidate waces ow waces with opewations such as ->wemap_fiwe_wange
ow ->copy_fiwe_wange, and then wetuwn with the page wocked. Usuawwy
mapping->invawidate_wock is suitabwe fow pwopew sewiawization. If the page has
been twuncated, the fiwesystem shouwd not wook up a new page wike the ->fauwt()
handwew, but simpwy wetuwn with VM_FAUWT_NOPAGE, which wiww cause the VM to
wetwy the fauwt.

->pfn_mkwwite() is the same as page_mkwwite but when the pte is
VM_PFNMAP ow VM_MIXEDMAP with a page-wess entwy. Expected wetuwn is
VM_FAUWT_NOPAGE. Ow one of the VM_FAUWT_EWWOW types. The defauwt behaviow
aftew this caww is to make the pte wead-wwite, unwess pfn_mkwwite wetuwns
an ewwow.

->access() is cawwed when get_usew_pages() faiws in
access_pwocess_vm(), typicawwy used to debug a pwocess thwough
/pwoc/pid/mem ow ptwace.  This function is needed onwy fow
VM_IO | VM_PFNMAP VMAs.

--------------------------------------------------------------------------------

			Dubious stuff

(if you bweak something ow notice that it is bwoken and do not fix it youwsewf
- at weast put it hewe)
