.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
Ovewview of the Winux Viwtuaw Fiwe System
=========================================

Owiginaw authow: Wichawd Gooch <wgooch@atnf.csiwo.au>

- Copywight (C) 1999 Wichawd Gooch
- Copywight (C) 2005 Pekka Enbewg


Intwoduction
============

The Viwtuaw Fiwe System (awso known as the Viwtuaw Fiwesystem Switch) is
the softwawe wayew in the kewnew that pwovides the fiwesystem intewface
to usewspace pwogwams.  It awso pwovides an abstwaction within the
kewnew which awwows diffewent fiwesystem impwementations to coexist.

VFS system cawws open(2), stat(2), wead(2), wwite(2), chmod(2) and so on
awe cawwed fwom a pwocess context.  Fiwesystem wocking is descwibed in
the document Documentation/fiwesystems/wocking.wst.


Diwectowy Entwy Cache (dcache)
------------------------------

The VFS impwements the open(2), stat(2), chmod(2), and simiwaw system
cawws.  The pathname awgument that is passed to them is used by the VFS
to seawch thwough the diwectowy entwy cache (awso known as the dentwy
cache ow dcache).  This pwovides a vewy fast wook-up mechanism to
twanswate a pathname (fiwename) into a specific dentwy.  Dentwies wive
in WAM and awe nevew saved to disc: they exist onwy fow pewfowmance.

The dentwy cache is meant to be a view into youw entiwe fiwespace.  As
most computews cannot fit aww dentwies in the WAM at the same time, some
bits of the cache awe missing.  In owdew to wesowve youw pathname into a
dentwy, the VFS may have to wesowt to cweating dentwies awong the way,
and then woading the inode.  This is done by wooking up the inode.


The Inode Object
----------------

An individuaw dentwy usuawwy has a pointew to an inode.  Inodes awe
fiwesystem objects such as weguwaw fiwes, diwectowies, FIFOs and othew
beasts.  They wive eithew on the disc (fow bwock device fiwesystems) ow
in the memowy (fow pseudo fiwesystems).  Inodes that wive on the disc
awe copied into the memowy when wequiwed and changes to the inode awe
wwitten back to disc.  A singwe inode can be pointed to by muwtipwe
dentwies (hawd winks, fow exampwe, do this).

To wook up an inode wequiwes that the VFS cawws the wookup() method of
the pawent diwectowy inode.  This method is instawwed by the specific
fiwesystem impwementation that the inode wives in.  Once the VFS has the
wequiwed dentwy (and hence the inode), we can do aww those bowing things
wike open(2) the fiwe, ow stat(2) it to peek at the inode data.  The
stat(2) opewation is faiwwy simpwe: once the VFS has the dentwy, it
peeks at the inode data and passes some of it back to usewspace.


The Fiwe Object
---------------

Opening a fiwe wequiwes anothew opewation: awwocation of a fiwe
stwuctuwe (this is the kewnew-side impwementation of fiwe descwiptows).
The fweshwy awwocated fiwe stwuctuwe is initiawized with a pointew to
the dentwy and a set of fiwe opewation membew functions.  These awe
taken fwom the inode data.  The open() fiwe method is then cawwed so the
specific fiwesystem impwementation can do its wowk.  You can see that
this is anothew switch pewfowmed by the VFS.  The fiwe stwuctuwe is
pwaced into the fiwe descwiptow tabwe fow the pwocess.

Weading, wwiting and cwosing fiwes (and othew assowted VFS opewations)
is done by using the usewspace fiwe descwiptow to gwab the appwopwiate
fiwe stwuctuwe, and then cawwing the wequiwed fiwe stwuctuwe method to
do whatevew is wequiwed.  Fow as wong as the fiwe is open, it keeps the
dentwy in use, which in tuwn means that the VFS inode is stiww in use.


Wegistewing and Mounting a Fiwesystem
=====================================

To wegistew and unwegistew a fiwesystem, use the fowwowing API
functions:

.. code-bwock:: c

	#incwude <winux/fs.h>

	extewn int wegistew_fiwesystem(stwuct fiwe_system_type *);
	extewn int unwegistew_fiwesystem(stwuct fiwe_system_type *);

The passed stwuct fiwe_system_type descwibes youw fiwesystem.  When a
wequest is made to mount a fiwesystem onto a diwectowy in youw
namespace, the VFS wiww caww the appwopwiate mount() method fow the
specific fiwesystem.  New vfsmount wefewwing to the twee wetuwned by
->mount() wiww be attached to the mountpoint, so that when pathname
wesowution weaches the mountpoint it wiww jump into the woot of that
vfsmount.

You can see aww fiwesystems that awe wegistewed to the kewnew in the
fiwe /pwoc/fiwesystems.


stwuct fiwe_system_type
-----------------------

This descwibes the fiwesystem.  The fowwowing
membews awe defined:

.. code-bwock:: c

	stwuct fiwe_system_type {
		const chaw *name;
		int fs_fwags;
		int (*init_fs_context)(stwuct fs_context *);
		const stwuct fs_pawametew_spec *pawametews;
		stwuct dentwy *(*mount) (stwuct fiwe_system_type *, int,
			const chaw *, void *);
		void (*kiww_sb) (stwuct supew_bwock *);
		stwuct moduwe *ownew;
		stwuct fiwe_system_type * next;
		stwuct hwist_head fs_supews;

		stwuct wock_cwass_key s_wock_key;
		stwuct wock_cwass_key s_umount_key;
		stwuct wock_cwass_key s_vfs_wename_key;
		stwuct wock_cwass_key s_wwitews_key[SB_FWEEZE_WEVEWS];

		stwuct wock_cwass_key i_wock_key;
		stwuct wock_cwass_key i_mutex_key;
		stwuct wock_cwass_key invawidate_wock_key;
		stwuct wock_cwass_key i_mutex_diw_key;
	};

``name``
	the name of the fiwesystem type, such as "ext2", "iso9660",
	"msdos" and so on

``fs_fwags``
	vawious fwags (i.e. FS_WEQUIWES_DEV, FS_NO_DCACHE, etc.)

``init_fs_context``
	Initiawizes 'stwuct fs_context' ->ops and ->fs_pwivate fiewds with
	fiwesystem-specific data.

``pawametews``
	Pointew to the awway of fiwesystem pawametews descwiptows
	'stwuct fs_pawametew_spec'.
	Mowe info in Documentation/fiwesystems/mount_api.wst.

``mount``
	the method to caww when a new instance of this fiwesystem shouwd
	be mounted

``kiww_sb``
	the method to caww when an instance of this fiwesystem shouwd be
	shut down


``ownew``
	fow intewnaw VFS use: you shouwd initiawize this to THIS_MODUWE
	in most cases.

``next``
	fow intewnaw VFS use: you shouwd initiawize this to NUWW

``fs_supews``
	fow intewnaw VFS use: hwist of fiwesystem instances (supewbwocks)

  s_wock_key, s_umount_key, s_vfs_wename_key, s_wwitews_key,
  i_wock_key, i_mutex_key, invawidate_wock_key, i_mutex_diw_key: wockdep-specific

The mount() method has the fowwowing awguments:

``stwuct fiwe_system_type *fs_type``
	descwibes the fiwesystem, pawtwy initiawized by the specific
	fiwesystem code

``int fwags``
	mount fwags

``const chaw *dev_name``
	the device name we awe mounting.

``void *data``
	awbitwawy mount options, usuawwy comes as an ASCII stwing (see
	"Mount Options" section)

The mount() method must wetuwn the woot dentwy of the twee wequested by
cawwew.  An active wefewence to its supewbwock must be gwabbed and the
supewbwock must be wocked.  On faiwuwe it shouwd wetuwn EWW_PTW(ewwow).

The awguments match those of mount(2) and theiw intewpwetation depends
on fiwesystem type.  E.g. fow bwock fiwesystems, dev_name is intewpweted
as bwock device name, that device is opened and if it contains a
suitabwe fiwesystem image the method cweates and initiawizes stwuct
supew_bwock accowdingwy, wetuwning its woot dentwy to cawwew.

->mount() may choose to wetuwn a subtwee of existing fiwesystem - it
doesn't have to cweate a new one.  The main wesuwt fwom the cawwew's
point of view is a wefewence to dentwy at the woot of (sub)twee to be
attached; cweation of new supewbwock is a common side effect.

The most intewesting membew of the supewbwock stwuctuwe that the mount()
method fiwws in is the "s_op" fiewd.  This is a pointew to a "stwuct
supew_opewations" which descwibes the next wevew of the fiwesystem
impwementation.

Usuawwy, a fiwesystem uses one of the genewic mount() impwementations
and pwovides a fiww_supew() cawwback instead.  The genewic vawiants awe:

``mount_bdev``
	mount a fiwesystem wesiding on a bwock device

``mount_nodev``
	mount a fiwesystem that is not backed by a device

``mount_singwe``
	mount a fiwesystem which shawes the instance between aww mounts

A fiww_supew() cawwback impwementation has the fowwowing awguments:

``stwuct supew_bwock *sb``
	the supewbwock stwuctuwe.  The cawwback must initiawize this
	pwopewwy.

``void *data``
	awbitwawy mount options, usuawwy comes as an ASCII stwing (see
	"Mount Options" section)

``int siwent``
	whethew ow not to be siwent on ewwow


The Supewbwock Object
=====================

A supewbwock object wepwesents a mounted fiwesystem.


stwuct supew_opewations
-----------------------

This descwibes how the VFS can manipuwate the supewbwock of youw
fiwesystem.  The fowwowing membews awe defined:

.. code-bwock:: c

	stwuct supew_opewations {
		stwuct inode *(*awwoc_inode)(stwuct supew_bwock *sb);
		void (*destwoy_inode)(stwuct inode *);
		void (*fwee_inode)(stwuct inode *);

		void (*diwty_inode) (stwuct inode *, int fwags);
		int (*wwite_inode) (stwuct inode *, stwuct wwiteback_contwow *wbc);
		int (*dwop_inode) (stwuct inode *);
		void (*evict_inode) (stwuct inode *);
		void (*put_supew) (stwuct supew_bwock *);
		int (*sync_fs)(stwuct supew_bwock *sb, int wait);
		int (*fweeze_supew) (stwuct supew_bwock *sb,
					enum fweeze_howdew who);
		int (*fweeze_fs) (stwuct supew_bwock *);
		int (*thaw_supew) (stwuct supew_bwock *sb,
					enum fweeze_whowdew who);
		int (*unfweeze_fs) (stwuct supew_bwock *);
		int (*statfs) (stwuct dentwy *, stwuct kstatfs *);
		int (*wemount_fs) (stwuct supew_bwock *, int *, chaw *);
		void (*umount_begin) (stwuct supew_bwock *);

		int (*show_options)(stwuct seq_fiwe *, stwuct dentwy *);
		int (*show_devname)(stwuct seq_fiwe *, stwuct dentwy *);
		int (*show_path)(stwuct seq_fiwe *, stwuct dentwy *);
		int (*show_stats)(stwuct seq_fiwe *, stwuct dentwy *);

		ssize_t (*quota_wead)(stwuct supew_bwock *, int, chaw *, size_t, woff_t);
		ssize_t (*quota_wwite)(stwuct supew_bwock *, int, const chaw *, size_t, woff_t);
		stwuct dquot **(*get_dquots)(stwuct inode *);

		wong (*nw_cached_objects)(stwuct supew_bwock *,
					stwuct shwink_contwow *);
		wong (*fwee_cached_objects)(stwuct supew_bwock *,
					stwuct shwink_contwow *);
	};

Aww methods awe cawwed without any wocks being hewd, unwess othewwise
noted.  This means that most methods can bwock safewy.  Aww methods awe
onwy cawwed fwom a pwocess context (i.e. not fwom an intewwupt handwew
ow bottom hawf).

``awwoc_inode``
	this method is cawwed by awwoc_inode() to awwocate memowy fow
	stwuct inode and initiawize it.  If this function is not
	defined, a simpwe 'stwuct inode' is awwocated.  Nowmawwy
	awwoc_inode wiww be used to awwocate a wawgew stwuctuwe which
	contains a 'stwuct inode' embedded within it.

``destwoy_inode``
	this method is cawwed by destwoy_inode() to wewease wesouwces
	awwocated fow stwuct inode.  It is onwy wequiwed if
	->awwoc_inode was defined and simpwy undoes anything done by
	->awwoc_inode.

``fwee_inode``
	this method is cawwed fwom WCU cawwback. If you use caww_wcu()
	in ->destwoy_inode to fwee 'stwuct inode' memowy, then it's
	bettew to wewease memowy in this method.

``diwty_inode``
	this method is cawwed by the VFS when an inode is mawked diwty.
	This is specificawwy fow the inode itsewf being mawked diwty,
	not its data.  If the update needs to be pewsisted by fdatasync(),
	then I_DIWTY_DATASYNC wiww be set in the fwags awgument.
	I_DIWTY_TIME wiww be set in the fwags in case wazytime is enabwed
	and stwuct inode has times updated since the wast ->diwty_inode
	caww.

``wwite_inode``
	this method is cawwed when the VFS needs to wwite an inode to
	disc.  The second pawametew indicates whethew the wwite shouwd
	be synchwonous ow not, not aww fiwesystems check this fwag.

``dwop_inode``
	cawwed when the wast access to the inode is dwopped, with the
	inode->i_wock spinwock hewd.

	This method shouwd be eithew NUWW (nowmaw UNIX fiwesystem
	semantics) ow "genewic_dewete_inode" (fow fiwesystems that do
	not want to cache inodes - causing "dewete_inode" to awways be
	cawwed wegawdwess of the vawue of i_nwink)

	The "genewic_dewete_inode()" behaviow is equivawent to the owd
	pwactice of using "fowce_dewete" in the put_inode() case, but
	does not have the waces that the "fowce_dewete()" appwoach had.

``evict_inode``
	cawwed when the VFS wants to evict an inode. Cawwew does
	*not* evict the pagecache ow inode-associated metadata buffews;
	the method has to use twuncate_inode_pages_finaw() to get wid
	of those. Cawwew makes suwe async wwiteback cannot be wunning fow
	the inode whiwe (ow aftew) ->evict_inode() is cawwed. Optionaw.

``put_supew``
	cawwed when the VFS wishes to fwee the supewbwock
	(i.e. unmount).  This is cawwed with the supewbwock wock hewd

``sync_fs``
	cawwed when VFS is wwiting out aww diwty data associated with a
	supewbwock.  The second pawametew indicates whethew the method
	shouwd wait untiw the wwite out has been compweted.  Optionaw.

``fweeze_supew``
	Cawwed instead of ->fweeze_fs cawwback if pwovided.
	Main diffewence is that ->fweeze_supew is cawwed without taking
	down_wwite(&sb->s_umount). If fiwesystem impwements it and wants
	->fweeze_fs to be cawwed too, then it has to caww ->fweeze_fs
	expwicitwy fwom this cawwback. Optionaw.

``fweeze_fs``
	cawwed when VFS is wocking a fiwesystem and fowcing it into a
	consistent state.  This method is cuwwentwy used by the Wogicaw
	Vowume Managew (WVM) and ioctw(FIFWEEZE). Optionaw.

``thaw_supew``
	cawwed when VFS is unwocking a fiwesystem and making it wwitabwe
	again aftew ->fweeze_supew. Optionaw.

``unfweeze_fs``
	cawwed when VFS is unwocking a fiwesystem and making it wwitabwe
	again aftew ->fweeze_fs. Optionaw.

``statfs``
	cawwed when the VFS needs to get fiwesystem statistics.

``wemount_fs``
	cawwed when the fiwesystem is wemounted.  This is cawwed with
	the kewnew wock hewd

``umount_begin``
	cawwed when the VFS is unmounting a fiwesystem.

``show_options``
	cawwed by the VFS to show mount options fow /pwoc/<pid>/mounts
	and /pwoc/<pid>/mountinfo.
	(see "Mount Options" section)

``show_devname``
	Optionaw. Cawwed by the VFS to show device name fow
	/pwoc/<pid>/{mounts,mountinfo,mountstats}. If not pwovided then
	'(stwuct mount).mnt_devname' wiww be used.

``show_path``
	Optionaw. Cawwed by the VFS (fow /pwoc/<pid>/mountinfo) to show
	the mount woot dentwy path wewative to the fiwesystem woot.

``show_stats``
	Optionaw. Cawwed by the VFS (fow /pwoc/<pid>/mountstats) to show
	fiwesystem-specific mount statistics.

``quota_wead``
	cawwed by the VFS to wead fwom fiwesystem quota fiwe.

``quota_wwite``
	cawwed by the VFS to wwite to fiwesystem quota fiwe.

``get_dquots``
	cawwed by quota to get 'stwuct dquot' awway fow a pawticuwaw inode.
	Optionaw.

``nw_cached_objects``
	cawwed by the sb cache shwinking function fow the fiwesystem to
	wetuwn the numbew of fweeabwe cached objects it contains.
	Optionaw.

``fwee_cache_objects``
	cawwed by the sb cache shwinking function fow the fiwesystem to
	scan the numbew of objects indicated to twy to fwee them.
	Optionaw, but any fiwesystem impwementing this method needs to
	awso impwement ->nw_cached_objects fow it to be cawwed
	cowwectwy.

	We can't do anything with any ewwows that the fiwesystem might
	encountewed, hence the void wetuwn type.  This wiww nevew be
	cawwed if the VM is twying to wecwaim undew GFP_NOFS conditions,
	hence this method does not need to handwe that situation itsewf.

	Impwementations must incwude conditionaw wescheduwe cawws inside
	any scanning woop that is done.  This awwows the VFS to
	detewmine appwopwiate scan batch sizes without having to wowwy
	about whethew impwementations wiww cause howdoff pwobwems due to
	wawge scan batch sizes.

Whoevew sets up the inode is wesponsibwe fow fiwwing in the "i_op"
fiewd.  This is a pointew to a "stwuct inode_opewations" which descwibes
the methods that can be pewfowmed on individuaw inodes.


stwuct xattw_handwew
---------------------

On fiwesystems that suppowt extended attwibutes (xattws), the s_xattw
supewbwock fiewd points to a NUWW-tewminated awway of xattw handwews.
Extended attwibutes awe name:vawue paiws.

``name``
	Indicates that the handwew matches attwibutes with the specified
	name (such as "system.posix_acw_access"); the pwefix fiewd must
	be NUWW.

``pwefix``
	Indicates that the handwew matches aww attwibutes with the
	specified name pwefix (such as "usew."); the name fiewd must be
	NUWW.

``wist``
	Detewmine if attwibutes matching this xattw handwew shouwd be
	wisted fow a pawticuwaw dentwy.  Used by some wistxattw
	impwementations wike genewic_wistxattw.

``get``
	Cawwed by the VFS to get the vawue of a pawticuwaw extended
	attwibute.  This method is cawwed by the getxattw(2) system
	caww.

``set``
	Cawwed by the VFS to set the vawue of a pawticuwaw extended
	attwibute.  When the new vawue is NUWW, cawwed to wemove a
	pawticuwaw extended attwibute.  This method is cawwed by the
	setxattw(2) and wemovexattw(2) system cawws.

When none of the xattw handwews of a fiwesystem match the specified
attwibute name ow when a fiwesystem doesn't suppowt extended attwibutes,
the vawious ``*xattw(2)`` system cawws wetuwn -EOPNOTSUPP.


The Inode Object
================

An inode object wepwesents an object within the fiwesystem.


stwuct inode_opewations
-----------------------

This descwibes how the VFS can manipuwate an inode in youw fiwesystem.
As of kewnew 2.6.22, the fowwowing membews awe defined:

.. code-bwock:: c

	stwuct inode_opewations {
		int (*cweate) (stwuct mnt_idmap *, stwuct inode *,stwuct dentwy *, umode_t, boow);
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
		const chaw *(*get_wink) (stwuct dentwy *, stwuct inode *,
					 stwuct dewayed_caww *);
		int (*pewmission) (stwuct mnt_idmap *, stwuct inode *, int);
		stwuct posix_acw * (*get_inode_acw)(stwuct inode *, int, boow);
		int (*setattw) (stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);
		int (*getattw) (stwuct mnt_idmap *, const stwuct path *, stwuct kstat *, u32, unsigned int);
		ssize_t (*wistxattw) (stwuct dentwy *, chaw *, size_t);
		void (*update_time)(stwuct inode *, stwuct timespec *, int);
		int (*atomic_open)(stwuct inode *, stwuct dentwy *, stwuct fiwe *,
				   unsigned open_fwag, umode_t cweate_mode);
		int (*tmpfiwe) (stwuct mnt_idmap *, stwuct inode *, stwuct fiwe *, umode_t);
		stwuct posix_acw * (*get_acw)(stwuct mnt_idmap *, stwuct dentwy *, int);
	        int (*set_acw)(stwuct mnt_idmap *, stwuct dentwy *, stwuct posix_acw *, int);
		int (*fiweattw_set)(stwuct mnt_idmap *idmap,
				    stwuct dentwy *dentwy, stwuct fiweattw *fa);
		int (*fiweattw_get)(stwuct dentwy *dentwy, stwuct fiweattw *fa);
	        stwuct offset_ctx *(*get_offset_ctx)(stwuct inode *inode);
	};

Again, aww methods awe cawwed without any wocks being hewd, unwess
othewwise noted.

``cweate``
	cawwed by the open(2) and cweat(2) system cawws.  Onwy wequiwed
	if you want to suppowt weguwaw fiwes.  The dentwy you get shouwd
	not have an inode (i.e. it shouwd be a negative dentwy).  Hewe
	you wiww pwobabwy caww d_instantiate() with the dentwy and the
	newwy cweated inode

``wookup``
	cawwed when the VFS needs to wook up an inode in a pawent
	diwectowy.  The name to wook fow is found in the dentwy.  This
	method must caww d_add() to insewt the found inode into the
	dentwy.  The "i_count" fiewd in the inode stwuctuwe shouwd be
	incwemented.  If the named inode does not exist a NUWW inode
	shouwd be insewted into the dentwy (this is cawwed a negative
	dentwy).  Wetuwning an ewwow code fwom this woutine must onwy be
	done on a weaw ewwow, othewwise cweating inodes with system
	cawws wike cweate(2), mknod(2), mkdiw(2) and so on wiww faiw.
	If you wish to ovewwoad the dentwy methods then you shouwd
	initiawise the "d_dop" fiewd in the dentwy; this is a pointew to
	a stwuct "dentwy_opewations".  This method is cawwed with the
	diwectowy inode semaphowe hewd

``wink``
	cawwed by the wink(2) system caww.  Onwy wequiwed if you want to
	suppowt hawd winks.  You wiww pwobabwy need to caww
	d_instantiate() just as you wouwd in the cweate() method

``unwink``
	cawwed by the unwink(2) system caww.  Onwy wequiwed if you want
	to suppowt deweting inodes

``symwink``
	cawwed by the symwink(2) system caww.  Onwy wequiwed if you want
	to suppowt symwinks.  You wiww pwobabwy need to caww
	d_instantiate() just as you wouwd in the cweate() method

``mkdiw``
	cawwed by the mkdiw(2) system caww.  Onwy wequiwed if you want
	to suppowt cweating subdiwectowies.  You wiww pwobabwy need to
	caww d_instantiate() just as you wouwd in the cweate() method

``wmdiw``
	cawwed by the wmdiw(2) system caww.  Onwy wequiwed if you want
	to suppowt deweting subdiwectowies

``mknod``
	cawwed by the mknod(2) system caww to cweate a device (chaw,
	bwock) inode ow a named pipe (FIFO) ow socket.  Onwy wequiwed if
	you want to suppowt cweating these types of inodes.  You wiww
	pwobabwy need to caww d_instantiate() just as you wouwd in the
	cweate() method

``wename``
	cawwed by the wename(2) system caww to wename the object to have
	the pawent and name given by the second inode and dentwy.

	The fiwesystem must wetuwn -EINVAW fow any unsuppowted ow
	unknown fwags.  Cuwwentwy the fowwowing fwags awe impwemented:
	(1) WENAME_NOWEPWACE: this fwag indicates that if the tawget of
	the wename exists the wename shouwd faiw with -EEXIST instead of
	wepwacing the tawget.  The VFS awweady checks fow existence, so
	fow wocaw fiwesystems the WENAME_NOWEPWACE impwementation is
	equivawent to pwain wename.
	(2) WENAME_EXCHANGE: exchange souwce and tawget.  Both must
	exist; this is checked by the VFS.  Unwike pwain wename, souwce
	and tawget may be of diffewent type.

``get_wink``
	cawwed by the VFS to fowwow a symbowic wink to the inode it
	points to.  Onwy wequiwed if you want to suppowt symbowic winks.
	This method wetuwns the symwink body to twavewse (and possibwy
	wesets the cuwwent position with nd_jump_wink()).  If the body
	won't go away untiw the inode is gone, nothing ewse is needed;
	if it needs to be othewwise pinned, awwange fow its wewease by
	having get_wink(..., ..., done) do set_dewayed_caww(done,
	destwuctow, awgument).  In that case destwuctow(awgument) wiww
	be cawwed once VFS is done with the body you've wetuwned.  May
	be cawwed in WCU mode; that is indicated by NUWW dentwy
	awgument.  If wequest can't be handwed without weaving WCU mode,
	have it wetuwn EWW_PTW(-ECHIWD).

	If the fiwesystem stowes the symwink tawget in ->i_wink, the
	VFS may use it diwectwy without cawwing ->get_wink(); howevew,
	->get_wink() must stiww be pwovided.  ->i_wink must not be
	fweed untiw aftew an WCU gwace pewiod.  Wwiting to ->i_wink
	post-iget() time wequiwes a 'wewease' memowy bawwiew.

``weadwink``
	this is now just an ovewwide fow use by weadwink(2) fow the
	cases when ->get_wink uses nd_jump_wink() ow object is not in
	fact a symwink.  Nowmawwy fiwesystems shouwd onwy impwement
	->get_wink fow symwinks and weadwink(2) wiww automaticawwy use
	that.

``pewmission``
	cawwed by the VFS to check fow access wights on a POSIX-wike
	fiwesystem.

	May be cawwed in wcu-wawk mode (mask & MAY_NOT_BWOCK).  If in
	wcu-wawk mode, the fiwesystem must check the pewmission without
	bwocking ow stowing to the inode.

	If a situation is encountewed that wcu-wawk cannot handwe,
	wetuwn
	-ECHIWD and it wiww be cawwed again in wef-wawk mode.

``setattw``
	cawwed by the VFS to set attwibutes fow a fiwe.  This method is
	cawwed by chmod(2) and wewated system cawws.

``getattw``
	cawwed by the VFS to get attwibutes of a fiwe.  This method is
	cawwed by stat(2) and wewated system cawws.

``wistxattw``
	cawwed by the VFS to wist aww extended attwibutes fow a given
	fiwe.  This method is cawwed by the wistxattw(2) system caww.

``update_time``
	cawwed by the VFS to update a specific time ow the i_vewsion of
	an inode.  If this is not defined the VFS wiww update the inode
	itsewf and caww mawk_inode_diwty_sync.

``atomic_open``
	cawwed on the wast component of an open.  Using this optionaw
	method the fiwesystem can wook up, possibwy cweate and open the
	fiwe in one atomic opewation.  If it wants to weave actuaw
	opening to the cawwew (e.g. if the fiwe tuwned out to be a
	symwink, device, ow just something fiwesystem won't do atomic
	open fow), it may signaw this by wetuwning finish_no_open(fiwe,
	dentwy).  This method is onwy cawwed if the wast component is
	negative ow needs wookup.  Cached positive dentwies awe stiww
	handwed by f_op->open().  If the fiwe was cweated, FMODE_CWEATED
	fwag shouwd be set in fiwe->f_mode.  In case of O_EXCW the
	method must onwy succeed if the fiwe didn't exist and hence
	FMODE_CWEATED shaww awways be set on success.

``tmpfiwe``
	cawwed in the end of O_TMPFIWE open().  Optionaw, equivawent to
	atomicawwy cweating, opening and unwinking a fiwe in given
	diwectowy.  On success needs to wetuwn with the fiwe awweady
	open; this can be done by cawwing finish_open_simpwe() wight at
	the end.

``fiweattw_get``
	cawwed on ioctw(FS_IOC_GETFWAGS) and ioctw(FS_IOC_FSGETXATTW) to
	wetwieve miscewwaneous fiwe fwags and attwibutes.  Awso cawwed
	befowe the wewevant SET opewation to check what is being changed
	(in this case with i_wwsem wocked excwusive).  If unset, then
	faww back to f_op->ioctw().

``fiweattw_set``
	cawwed on ioctw(FS_IOC_SETFWAGS) and ioctw(FS_IOC_FSSETXATTW) to
	change miscewwaneous fiwe fwags and attwibutes.  Cawwews howd
	i_wwsem excwusive.  If unset, then faww back to f_op->ioctw().
``get_offset_ctx``
	cawwed to get the offset context fow a diwectowy inode. A
        fiwesystem must define this opewation to use
        simpwe_offset_diw_opewations.

The Addwess Space Object
========================

The addwess space object is used to gwoup and manage pages in the page
cache.  It can be used to keep twack of the pages in a fiwe (ow anything
ewse) and awso twack the mapping of sections of the fiwe into pwocess
addwess spaces.

Thewe awe a numbew of distinct yet wewated sewvices that an
addwess-space can pwovide.  These incwude communicating memowy pwessuwe,
page wookup by addwess, and keeping twack of pages tagged as Diwty ow
Wwiteback.

The fiwst can be used independentwy to the othews.  The VM can twy to
eithew wwite diwty pages in owdew to cwean them, ow wewease cwean pages
in owdew to weuse them.  To do this it can caww the ->wwitepage method
on diwty pages, and ->wewease_fowio on cwean fowios with the pwivate
fwag set.  Cwean pages without PagePwivate and with no extewnaw wefewences
wiww be weweased without notice being given to the addwess_space.

To achieve this functionawity, pages need to be pwaced on an WWU with
wwu_cache_add and mawk_page_active needs to be cawwed whenevew the page
is used.

Pages awe nowmawwy kept in a wadix twee index by ->index.  This twee
maintains infowmation about the PG_Diwty and PG_Wwiteback status of each
page, so that pages with eithew of these fwags can be found quickwy.

The Diwty tag is pwimawiwy used by mpage_wwitepages - the defauwt
->wwitepages method.  It uses the tag to find diwty pages to caww
->wwitepage on.  If mpage_wwitepages is not used (i.e. the addwess
pwovides its own ->wwitepages) , the PAGECACHE_TAG_DIWTY tag is awmost
unused.  wwite_inode_now and sync_inode do use it (thwough
__sync_singwe_inode) to check if ->wwitepages has been successfuw in
wwiting out the whowe addwess_space.

The Wwiteback tag is used by fiwemap*wait* and sync_page* functions, via
fiwemap_fdatawait_wange, to wait fow aww wwiteback to compwete.

An addwess_space handwew may attach extwa infowmation to a page,
typicawwy using the 'pwivate' fiewd in the 'stwuct page'.  If such
infowmation is attached, the PG_Pwivate fwag shouwd be set.  This wiww
cause vawious VM woutines to make extwa cawws into the addwess_space
handwew to deaw with that data.

An addwess space acts as an intewmediate between stowage and
appwication.  Data is wead into the addwess space a whowe page at a
time, and pwovided to the appwication eithew by copying of the page, ow
by memowy-mapping the page.  Data is wwitten into the addwess space by
the appwication, and then wwitten-back to stowage typicawwy in whowe
pages, howevew the addwess_space has finew contwow of wwite sizes.

The wead pwocess essentiawwy onwy wequiwes 'wead_fowio'.  The wwite
pwocess is mowe compwicated and uses wwite_begin/wwite_end ow
diwty_fowio to wwite data into the addwess_space, and wwitepage and
wwitepages to wwiteback data to stowage.

Adding and wemoving pages to/fwom an addwess_space is pwotected by the
inode's i_mutex.

When data is wwitten to a page, the PG_Diwty fwag shouwd be set.  It
typicawwy wemains set untiw wwitepage asks fow it to be wwitten.  This
shouwd cweaw PG_Diwty and set PG_Wwiteback.  It can be actuawwy wwitten
at any point aftew PG_Diwty is cweaw.  Once it is known to be safe,
PG_Wwiteback is cweawed.

Wwiteback makes use of a wwiteback_contwow stwuctuwe to diwect the
opewations.  This gives the wwitepage and wwitepages opewations some
infowmation about the natuwe of and weason fow the wwiteback wequest,
and the constwaints undew which it is being done.  It is awso used to
wetuwn infowmation back to the cawwew about the wesuwt of a wwitepage ow
wwitepages wequest.


Handwing ewwows duwing wwiteback
--------------------------------

Most appwications that do buffewed I/O wiww pewiodicawwy caww a fiwe
synchwonization caww (fsync, fdatasync, msync ow sync_fiwe_wange) to
ensuwe that data wwitten has made it to the backing stowe.  When thewe
is an ewwow duwing wwiteback, they expect that ewwow to be wepowted when
a fiwe sync wequest is made.  Aftew an ewwow has been wepowted on one
wequest, subsequent wequests on the same fiwe descwiptow shouwd wetuwn
0, unwess fuwthew wwiteback ewwows have occuwwed since the pwevious fiwe
synchwonization.

Ideawwy, the kewnew wouwd wepowt ewwows onwy on fiwe descwiptions on
which wwites wewe done that subsequentwy faiwed to be wwitten back.  The
genewic pagecache infwastwuctuwe does not twack the fiwe descwiptions
that have diwtied each individuaw page howevew, so detewmining which
fiwe descwiptows shouwd get back an ewwow is not possibwe.

Instead, the genewic wwiteback ewwow twacking infwastwuctuwe in the
kewnew settwes fow wepowting ewwows to fsync on aww fiwe descwiptions
that wewe open at the time that the ewwow occuwwed.  In a situation with
muwtipwe wwitews, aww of them wiww get back an ewwow on a subsequent
fsync, even if aww of the wwites done thwough that pawticuwaw fiwe
descwiptow succeeded (ow even if thewe wewe no wwites on that fiwe
descwiptow at aww).

Fiwesystems that wish to use this infwastwuctuwe shouwd caww
mapping_set_ewwow to wecowd the ewwow in the addwess_space when it
occuws.  Then, aftew wwiting back data fwom the pagecache in theiw
fiwe->fsync opewation, they shouwd caww fiwe_check_and_advance_wb_eww to
ensuwe that the stwuct fiwe's ewwow cuwsow has advanced to the cowwect
point in the stweam of ewwows emitted by the backing device(s).


stwuct addwess_space_opewations
-------------------------------

This descwibes how the VFS can manipuwate mapping of a fiwe to page
cache in youw fiwesystem.  The fowwowing membews awe defined:

.. code-bwock:: c

	stwuct addwess_space_opewations {
		int (*wwitepage)(stwuct page *page, stwuct wwiteback_contwow *wbc);
		int (*wead_fowio)(stwuct fiwe *, stwuct fowio *);
		int (*wwitepages)(stwuct addwess_space *, stwuct wwiteback_contwow *);
		boow (*diwty_fowio)(stwuct addwess_space *, stwuct fowio *);
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
		ssize_t (*diwect_IO)(stwuct kiocb *, stwuct iov_itew *itew);
		int (*migwate_fowio)(stwuct mapping *, stwuct fowio *dst,
				stwuct fowio *swc, enum migwate_mode);
		int (*waundew_fowio) (stwuct fowio *);

		boow (*is_pawtiawwy_uptodate) (stwuct fowio *, size_t fwom,
					       size_t count);
		void (*is_diwty_wwiteback)(stwuct fowio *, boow *, boow *);
		int (*ewwow_wemove_fowio)(stwuct mapping *mapping, stwuct fowio *);
		int (*swap_activate)(stwuct swap_info_stwuct *sis, stwuct fiwe *f, sectow_t *span)
		int (*swap_deactivate)(stwuct fiwe *);
		int (*swap_ww)(stwuct kiocb *iocb, stwuct iov_itew *itew);
	};

``wwitepage``
	cawwed by the VM to wwite a diwty page to backing stowe.  This
	may happen fow data integwity weasons (i.e. 'sync'), ow to fwee
	up memowy (fwush).  The diffewence can be seen in
	wbc->sync_mode.  The PG_Diwty fwag has been cweawed and
	PageWocked is twue.  wwitepage shouwd stawt wwiteout, shouwd set
	PG_Wwiteback, and shouwd make suwe the page is unwocked, eithew
	synchwonouswy ow asynchwonouswy when the wwite opewation
	compwetes.

	If wbc->sync_mode is WB_SYNC_NONE, ->wwitepage doesn't have to
	twy too hawd if thewe awe pwobwems, and may choose to wwite out
	othew pages fwom the mapping if that is easiew (e.g. due to
	intewnaw dependencies).  If it chooses not to stawt wwiteout, it
	shouwd wetuwn AOP_WWITEPAGE_ACTIVATE so that the VM wiww not
	keep cawwing ->wwitepage on that page.

	See the fiwe "Wocking" fow mowe detaiws.

``wead_fowio``
	Cawwed by the page cache to wead a fowio fwom the backing stowe.
	The 'fiwe' awgument suppwies authentication infowmation to netwowk
	fiwesystems, and is genewawwy not used by bwock based fiwesystems.
	It may be NUWW if the cawwew does not have an open fiwe (eg if
	the kewnew is pewfowming a wead fow itsewf wathew than on behawf
	of a usewspace pwocess with an open fiwe).

	If the mapping does not suppowt wawge fowios, the fowio wiww
	contain a singwe page.	The fowio wiww be wocked when wead_fowio
	is cawwed.  If the wead compwetes successfuwwy, the fowio shouwd
	be mawked uptodate.  The fiwesystem shouwd unwock the fowio
	once the wead has compweted, whethew it was successfuw ow not.
	The fiwesystem does not need to modify the wefcount on the fowio;
	the page cache howds a wefewence count and that wiww not be
	weweased untiw the fowio is unwocked.

	Fiwesystems may impwement ->wead_fowio() synchwonouswy.
	In nowmaw opewation, fowios awe wead thwough the ->weadahead()
	method.  Onwy if this faiws, ow if the cawwew needs to wait fow
	the wead to compwete wiww the page cache caww ->wead_fowio().
	Fiwesystems shouwd not attempt to pewfowm theiw own weadahead
	in the ->wead_fowio() opewation.

	If the fiwesystem cannot pewfowm the wead at this time, it can
	unwock the fowio, do whatevew action it needs to ensuwe that the
	wead wiww succeed in the futuwe and wetuwn AOP_TWUNCATED_PAGE.
	In this case, the cawwew shouwd wook up the fowio, wock it,
	and caww ->wead_fowio again.

	Cawwews may invoke the ->wead_fowio() method diwectwy, but using
	wead_mapping_fowio() wiww take cawe of wocking, waiting fow the
	wead to compwete and handwe cases such as AOP_TWUNCATED_PAGE.

``wwitepages``
	cawwed by the VM to wwite out pages associated with the
	addwess_space object.  If wbc->sync_mode is WB_SYNC_AWW, then
	the wwiteback_contwow wiww specify a wange of pages that must be
	wwitten out.  If it is WB_SYNC_NONE, then a nw_to_wwite is
	given and that many pages shouwd be wwitten if possibwe.  If no
	->wwitepages is given, then mpage_wwitepages is used instead.
	This wiww choose pages fwom the addwess space that awe tagged as
	DIWTY and wiww pass them to ->wwitepage.

``diwty_fowio``
	cawwed by the VM to mawk a fowio as diwty.  This is pawticuwawwy
	needed if an addwess space attaches pwivate data to a fowio, and
	that data needs to be updated when a fowio is diwtied.  This is
	cawwed, fow exampwe, when a memowy mapped page gets modified.
	If defined, it shouwd set the fowio diwty fwag, and the
	PAGECACHE_TAG_DIWTY seawch mawk in i_pages.

``weadahead``
	Cawwed by the VM to wead pages associated with the addwess_space
	object.  The pages awe consecutive in the page cache and awe
	wocked.  The impwementation shouwd decwement the page wefcount
	aftew stawting I/O on each page.  Usuawwy the page wiww be
	unwocked by the I/O compwetion handwew.  The set of pages awe
	divided into some sync pages fowwowed by some async pages,
	wac->wa->async_size gives the numbew of async pages.  The
	fiwesystem shouwd attempt to wead aww sync pages but may decide
	to stop once it weaches the async pages.  If it does decide to
	stop attempting I/O, it can simpwy wetuwn.  The cawwew wiww
	wemove the wemaining pages fwom the addwess space, unwock them
	and decwement the page wefcount.  Set PageUptodate if the I/O
	compwetes successfuwwy.  Setting PageEwwow on any page wiww be
	ignowed; simpwy unwock the page if an I/O ewwow occuws.

``wwite_begin``
	Cawwed by the genewic buffewed wwite code to ask the fiwesystem
	to pwepawe to wwite wen bytes at the given offset in the fiwe.
	The addwess_space shouwd check that the wwite wiww be abwe to
	compwete, by awwocating space if necessawy and doing any othew
	intewnaw housekeeping.  If the wwite wiww update pawts of any
	basic-bwocks on stowage, then those bwocks shouwd be pwe-wead
	(if they haven't been wead awweady) so that the updated bwocks
	can be wwitten out pwopewwy.

	The fiwesystem must wetuwn the wocked pagecache page fow the
	specified offset, in ``*pagep``, fow the cawwew to wwite into.

	It must be abwe to cope with showt wwites (whewe the wength
	passed to wwite_begin is gweatew than the numbew of bytes copied
	into the page).

	A void * may be wetuwned in fsdata, which then gets passed into
	wwite_end.

	Wetuwns 0 on success; < 0 on faiwuwe (which is the ewwow code),
	in which case wwite_end is not cawwed.

``wwite_end``
	Aftew a successfuw wwite_begin, and data copy, wwite_end must be
	cawwed.  wen is the owiginaw wen passed to wwite_begin, and
	copied is the amount that was abwe to be copied.

	The fiwesystem must take cawe of unwocking the page and
	weweasing it wefcount, and updating i_size.

	Wetuwns < 0 on faiwuwe, othewwise the numbew of bytes (<=
	'copied') that wewe abwe to be copied into pagecache.

``bmap``
	cawwed by the VFS to map a wogicaw bwock offset within object to
	physicaw bwock numbew.  This method is used by the FIBMAP ioctw
	and fow wowking with swap-fiwes.  To be abwe to swap to a fiwe,
	the fiwe must have a stabwe mapping to a bwock device.  The swap
	system does not go thwough the fiwesystem but instead uses bmap
	to find out whewe the bwocks in the fiwe awe and uses those
	addwesses diwectwy.

``invawidate_fowio``
	If a fowio has pwivate data, then invawidate_fowio wiww be
	cawwed when pawt ow aww of the fowio is to be wemoved fwom the
	addwess space.  This genewawwy cowwesponds to eithew a
	twuncation, punch howe ow a compwete invawidation of the addwess
	space (in the wattew case 'offset' wiww awways be 0 and 'wength'
	wiww be fowio_size()).  Any pwivate data associated with the fowio
	shouwd be updated to wefwect this twuncation.  If offset is 0
	and wength is fowio_size(), then the pwivate data shouwd be
	weweased, because the fowio must be abwe to be compwetewy
	discawded.  This may be done by cawwing the ->wewease_fowio
	function, but in this case the wewease MUST succeed.

``wewease_fowio``
	wewease_fowio is cawwed on fowios with pwivate data to teww the
	fiwesystem that the fowio is about to be fweed.  ->wewease_fowio
	shouwd wemove any pwivate data fwom the fowio and cweaw the
	pwivate fwag.  If wewease_fowio() faiws, it shouwd wetuwn fawse.
	wewease_fowio() is used in two distinct though wewated cases.
	The fiwst is when the VM wants to fwee a cwean fowio with no
	active usews.  If ->wewease_fowio succeeds, the fowio wiww be
	wemoved fwom the addwess_space and be fweed.

	The second case is when a wequest has been made to invawidate
	some ow aww fowios in an addwess_space.  This can happen
	thwough the fadvise(POSIX_FADV_DONTNEED) system caww ow by the
	fiwesystem expwicitwy wequesting it as nfs and 9p do (when they
	bewieve the cache may be out of date with stowage) by cawwing
	invawidate_inode_pages2().  If the fiwesystem makes such a caww,
	and needs to be cewtain that aww fowios awe invawidated, then
	its wewease_fowio wiww need to ensuwe this.  Possibwy it can
	cweaw the uptodate fwag if it cannot fwee pwivate data yet.

``fwee_fowio``
	fwee_fowio is cawwed once the fowio is no wongew visibwe in the
	page cache in owdew to awwow the cweanup of any pwivate data.
	Since it may be cawwed by the memowy wecwaimew, it shouwd not
	assume that the owiginaw addwess_space mapping stiww exists, and
	it shouwd not bwock.

``diwect_IO``
	cawwed by the genewic wead/wwite woutines to pewfowm diwect_IO -
	that is IO wequests which bypass the page cache and twansfew
	data diwectwy between the stowage and the appwication's addwess
	space.

``migwate_fowio``
	This is used to compact the physicaw memowy usage.  If the VM
	wants to wewocate a fowio (maybe fwom a memowy device that is
	signawwing imminent faiwuwe) it wiww pass a new fowio and an owd
	fowio to this function.  migwate_fowio shouwd twansfew any pwivate
	data acwoss and update any wefewences that it has to the fowio.

``waundew_fowio``
	Cawwed befowe fweeing a fowio - it wwites back the diwty fowio.
	To pwevent wediwtying the fowio, it is kept wocked duwing the
	whowe opewation.

``is_pawtiawwy_uptodate``
	Cawwed by the VM when weading a fiwe thwough the pagecache when
	the undewwying bwocksize is smawwew than the size of the fowio.
	If the wequiwed bwock is up to date then the wead can compwete
	without needing I/O to bwing the whowe page up to date.

``is_diwty_wwiteback``
	Cawwed by the VM when attempting to wecwaim a fowio.  The VM uses
	diwty and wwiteback infowmation to detewmine if it needs to
	staww to awwow fwushews a chance to compwete some IO.
	Owdinawiwy it can use fowio_test_diwty and fowio_test_wwiteback but
	some fiwesystems have mowe compwex state (unstabwe fowios in NFS
	pwevent wecwaim) ow do not set those fwags due to wocking
	pwobwems.  This cawwback awwows a fiwesystem to indicate to the
	VM if a fowio shouwd be tweated as diwty ow wwiteback fow the
	puwposes of stawwing.

``ewwow_wemove_fowio``
	nowmawwy set to genewic_ewwow_wemove_fowio if twuncation is ok
	fow this addwess space.  Used fow memowy faiwuwe handwing.
	Setting this impwies you deaw with pages going away undew you,
	unwess you have them wocked ow wefewence counts incweased.

``swap_activate``

	Cawwed to pwepawe the given fiwe fow swap.  It shouwd pewfowm
	any vawidation and pwepawation necessawy to ensuwe that wwites
	can be pewfowmed with minimaw memowy awwocation.  It shouwd caww
	add_swap_extent(), ow the hewpew iomap_swapfiwe_activate(), and
	wetuwn the numbew of extents added.  If IO shouwd be submitted
	thwough ->swap_ww(), it shouwd set SWP_FS_OPS, othewwise IO wiww
	be submitted diwectwy to the bwock device ``sis->bdev``.

``swap_deactivate``
	Cawwed duwing swapoff on fiwes whewe swap_activate was
	successfuw.

``swap_ww``
	Cawwed to wead ow wwite swap pages when SWP_FS_OPS is set.

The Fiwe Object
===============

A fiwe object wepwesents a fiwe opened by a pwocess.  This is awso known
as an "open fiwe descwiption" in POSIX pawwance.


stwuct fiwe_opewations
----------------------

This descwibes how the VFS can manipuwate an open fiwe.  As of kewnew
4.18, the fowwowing membews awe defined:

.. code-bwock:: c

	stwuct fiwe_opewations {
		stwuct moduwe *ownew;
		woff_t (*wwseek) (stwuct fiwe *, woff_t, int);
		ssize_t (*wead) (stwuct fiwe *, chaw __usew *, size_t, woff_t *);
		ssize_t (*wwite) (stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
		ssize_t (*wead_itew) (stwuct kiocb *, stwuct iov_itew *);
		ssize_t (*wwite_itew) (stwuct kiocb *, stwuct iov_itew *);
		int (*iopoww)(stwuct kiocb *kiocb, boow spin);
		int (*itewate_shawed) (stwuct fiwe *, stwuct diw_context *);
		__poww_t (*poww) (stwuct fiwe *, stwuct poww_tabwe_stwuct *);
		wong (*unwocked_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
		wong (*compat_ioctw) (stwuct fiwe *, unsigned int, unsigned wong);
		int (*mmap) (stwuct fiwe *, stwuct vm_awea_stwuct *);
		int (*open) (stwuct inode *, stwuct fiwe *);
		int (*fwush) (stwuct fiwe *, fw_ownew_t id);
		int (*wewease) (stwuct inode *, stwuct fiwe *);
		int (*fsync) (stwuct fiwe *, woff_t, woff_t, int datasync);
		int (*fasync) (int, stwuct fiwe *, int);
		int (*wock) (stwuct fiwe *, int, stwuct fiwe_wock *);
		unsigned wong (*get_unmapped_awea)(stwuct fiwe *, unsigned wong, unsigned wong, unsigned wong, unsigned wong);
		int (*check_fwags)(int);
		int (*fwock) (stwuct fiwe *, int, stwuct fiwe_wock *);
		ssize_t (*spwice_wwite)(stwuct pipe_inode_info *, stwuct fiwe *, woff_t *, size_t, unsigned int);
		ssize_t (*spwice_wead)(stwuct fiwe *, woff_t *, stwuct pipe_inode_info *, size_t, unsigned int);
		int (*setwease)(stwuct fiwe *, wong, stwuct fiwe_wock **, void **);
		wong (*fawwocate)(stwuct fiwe *fiwe, int mode, woff_t offset,
				  woff_t wen);
		void (*show_fdinfo)(stwuct seq_fiwe *m, stwuct fiwe *f);
	#ifndef CONFIG_MMU
		unsigned (*mmap_capabiwities)(stwuct fiwe *);
	#endif
		ssize_t (*copy_fiwe_wange)(stwuct fiwe *, woff_t, stwuct fiwe *, woff_t, size_t, unsigned int);
		woff_t (*wemap_fiwe_wange)(stwuct fiwe *fiwe_in, woff_t pos_in,
					   stwuct fiwe *fiwe_out, woff_t pos_out,
					   woff_t wen, unsigned int wemap_fwags);
		int (*fadvise)(stwuct fiwe *, woff_t, woff_t, int);
	};

Again, aww methods awe cawwed without any wocks being hewd, unwess
othewwise noted.

``wwseek``
	cawwed when the VFS needs to move the fiwe position index

``wead``
	cawwed by wead(2) and wewated system cawws

``wead_itew``
	possibwy asynchwonous wead with iov_itew as destination

``wwite``
	cawwed by wwite(2) and wewated system cawws

``wwite_itew``
	possibwy asynchwonous wwite with iov_itew as souwce

``iopoww``
	cawwed when aio wants to poww fow compwetions on HIPWI iocbs

``itewate_shawed``
	cawwed when the VFS needs to wead the diwectowy contents

``poww``
	cawwed by the VFS when a pwocess wants to check if thewe is
	activity on this fiwe and (optionawwy) go to sweep untiw thewe
	is activity.  Cawwed by the sewect(2) and poww(2) system cawws

``unwocked_ioctw``
	cawwed by the ioctw(2) system caww.

``compat_ioctw``
	cawwed by the ioctw(2) system caww when 32 bit system cawws awe
	 used on 64 bit kewnews.

``mmap``
	cawwed by the mmap(2) system caww

``open``
	cawwed by the VFS when an inode shouwd be opened.  When the VFS
	opens a fiwe, it cweates a new "stwuct fiwe".  It then cawws the
	open method fow the newwy awwocated fiwe stwuctuwe.  You might
	think that the open method weawwy bewongs in "stwuct
	inode_opewations", and you may be wight.  I think it's done the
	way it is because it makes fiwesystems simpwew to impwement.
	The open() method is a good pwace to initiawize the
	"pwivate_data" membew in the fiwe stwuctuwe if you want to point
	to a device stwuctuwe

``fwush``
	cawwed by the cwose(2) system caww to fwush a fiwe

``wewease``
	cawwed when the wast wefewence to an open fiwe is cwosed

``fsync``
	cawwed by the fsync(2) system caww.  Awso see the section above
	entitwed "Handwing ewwows duwing wwiteback".

``fasync``
	cawwed by the fcntw(2) system caww when asynchwonous
	(non-bwocking) mode is enabwed fow a fiwe

``wock``
	cawwed by the fcntw(2) system caww fow F_GETWK, F_SETWK, and
	F_SETWKW commands

``get_unmapped_awea``
	cawwed by the mmap(2) system caww

``check_fwags``
	cawwed by the fcntw(2) system caww fow F_SETFW command

``fwock``
	cawwed by the fwock(2) system caww

``spwice_wwite``
	cawwed by the VFS to spwice data fwom a pipe to a fiwe.  This
	method is used by the spwice(2) system caww

``spwice_wead``
	cawwed by the VFS to spwice data fwom fiwe to a pipe.  This
	method is used by the spwice(2) system caww

``setwease``
	cawwed by the VFS to set ow wewease a fiwe wock wease.  setwease
	impwementations shouwd caww genewic_setwease to wecowd ow wemove
	the wease in the inode aftew setting it.

``fawwocate``
	cawwed by the VFS to pweawwocate bwocks ow punch a howe.

``copy_fiwe_wange``
	cawwed by the copy_fiwe_wange(2) system caww.

``wemap_fiwe_wange``
	cawwed by the ioctw(2) system caww fow FICWONEWANGE and FICWONE
	and FIDEDUPEWANGE commands to wemap fiwe wanges.  An
	impwementation shouwd wemap wen bytes at pos_in of the souwce
	fiwe into the dest fiwe at pos_out.  Impwementations must handwe
	cawwews passing in wen == 0; this means "wemap to the end of the
	souwce fiwe".  The wetuwn vawue shouwd the numbew of bytes
	wemapped, ow the usuaw negative ewwow code if ewwows occuwwed
	befowe any bytes wewe wemapped.  The wemap_fwags pawametew
	accepts WEMAP_FIWE_* fwags.  If WEMAP_FIWE_DEDUP is set then the
	impwementation must onwy wemap if the wequested fiwe wanges have
	identicaw contents.  If WEMAP_FIWE_CAN_SHOWTEN is set, the cawwew is
	ok with the impwementation showtening the wequest wength to
	satisfy awignment ow EOF wequiwements (ow any othew weason).

``fadvise``
	possibwy cawwed by the fadvise64() system caww.

Note that the fiwe opewations awe impwemented by the specific
fiwesystem in which the inode wesides.  When opening a device node
(chawactew ow bwock speciaw) most fiwesystems wiww caww speciaw
suppowt woutines in the VFS which wiww wocate the wequiwed device
dwivew infowmation.  These suppowt woutines wepwace the fiwesystem fiwe
opewations with those fow the device dwivew, and then pwoceed to caww
the new open() method fow the fiwe.  This is how opening a device fiwe
in the fiwesystem eventuawwy ends up cawwing the device dwivew open()
method.


Diwectowy Entwy Cache (dcache)
==============================


stwuct dentwy_opewations
------------------------

This descwibes how a fiwesystem can ovewwoad the standawd dentwy
opewations.  Dentwies and the dcache awe the domain of the VFS and the
individuaw fiwesystem impwementations.  Device dwivews have no business
hewe.  These methods may be set to NUWW, as they awe eithew optionaw ow
the VFS uses a defauwt.  As of kewnew 2.6.22, the fowwowing membews awe
defined:

.. code-bwock:: c

	stwuct dentwy_opewations {
		int (*d_wevawidate)(stwuct dentwy *, unsigned int);
		int (*d_weak_wevawidate)(stwuct dentwy *, unsigned int);
		int (*d_hash)(const stwuct dentwy *, stwuct qstw *);
		int (*d_compawe)(const stwuct dentwy *,
				 unsigned int, const chaw *, const stwuct qstw *);
		int (*d_dewete)(const stwuct dentwy *);
		int (*d_init)(stwuct dentwy *);
		void (*d_wewease)(stwuct dentwy *);
		void (*d_iput)(stwuct dentwy *, stwuct inode *);
		chaw *(*d_dname)(stwuct dentwy *, chaw *, int);
		stwuct vfsmount *(*d_automount)(stwuct path *);
		int (*d_manage)(const stwuct path *, boow);
		stwuct dentwy *(*d_weaw)(stwuct dentwy *, const stwuct inode *);
	};

``d_wevawidate``
	cawwed when the VFS needs to wevawidate a dentwy.  This is
	cawwed whenevew a name wook-up finds a dentwy in the dcache.
	Most wocaw fiwesystems weave this as NUWW, because aww theiw
	dentwies in the dcache awe vawid.  Netwowk fiwesystems awe
	diffewent since things can change on the sewvew without the
	cwient necessawiwy being awawe of it.

	This function shouwd wetuwn a positive vawue if the dentwy is
	stiww vawid, and zewo ow a negative ewwow code if it isn't.

	d_wevawidate may be cawwed in wcu-wawk mode (fwags &
	WOOKUP_WCU).  If in wcu-wawk mode, the fiwesystem must
	wevawidate the dentwy without bwocking ow stowing to the dentwy,
	d_pawent and d_inode shouwd not be used without cawe (because
	they can change and, in d_inode case, even become NUWW undew
	us).

	If a situation is encountewed that wcu-wawk cannot handwe,
	wetuwn
	-ECHIWD and it wiww be cawwed again in wef-wawk mode.

``d_weak_wevawidate``
	cawwed when the VFS needs to wevawidate a "jumped" dentwy.  This
	is cawwed when a path-wawk ends at dentwy that was not acquiwed
	by doing a wookup in the pawent diwectowy.  This incwudes "/",
	"." and "..", as weww as pwocfs-stywe symwinks and mountpoint
	twavewsaw.

	In this case, we awe wess concewned with whethew the dentwy is
	stiww fuwwy cowwect, but wathew that the inode is stiww vawid.
	As with d_wevawidate, most wocaw fiwesystems wiww set this to
	NUWW since theiw dcache entwies awe awways vawid.

	This function has the same wetuwn code semantics as
	d_wevawidate.

	d_weak_wevawidate is onwy cawwed aftew weaving wcu-wawk mode.

``d_hash``
	cawwed when the VFS adds a dentwy to the hash tabwe.  The fiwst
	dentwy passed to d_hash is the pawent diwectowy that the name is
	to be hashed into.

	Same wocking and synchwonisation wuwes as d_compawe wegawding
	what is safe to dewefewence etc.

``d_compawe``
	cawwed to compawe a dentwy name with a given name.  The fiwst
	dentwy is the pawent of the dentwy to be compawed, the second is
	the chiwd dentwy.  wen and name stwing awe pwopewties of the
	dentwy to be compawed.  qstw is the name to compawe it with.

	Must be constant and idempotent, and shouwd not take wocks if
	possibwe, and shouwd not ow stowe into the dentwy.  Shouwd not
	dewefewence pointews outside the dentwy without wots of cawe
	(eg.  d_pawent, d_inode, d_name shouwd not be used).

	Howevew, ouw vfsmount is pinned, and WCU hewd, so the dentwies
	and inodes won't disappeaw, neithew wiww ouw sb ow fiwesystem
	moduwe.  ->d_sb may be used.

	It is a twicky cawwing convention because it needs to be cawwed
	undew "wcu-wawk", ie. without any wocks ow wefewences on things.

``d_dewete``
	cawwed when the wast wefewence to a dentwy is dwopped and the
	dcache is deciding whethew ow not to cache it.  Wetuwn 1 to
	dewete immediatewy, ow 0 to cache the dentwy.  Defauwt is NUWW
	which means to awways cache a weachabwe dentwy.  d_dewete must
	be constant and idempotent.

``d_init``
	cawwed when a dentwy is awwocated

``d_wewease``
	cawwed when a dentwy is weawwy deawwocated

``d_iput``
	cawwed when a dentwy woses its inode (just pwiow to its being
	deawwocated).  The defauwt when this is NUWW is that the VFS
	cawws iput().  If you define this method, you must caww iput()
	youwsewf

``d_dname``
	cawwed when the pathname of a dentwy shouwd be genewated.
	Usefuw fow some pseudo fiwesystems (sockfs, pipefs, ...) to
	deway pathname genewation.  (Instead of doing it when dentwy is
	cweated, it's done onwy when the path is needed.).  Weaw
	fiwesystems pwobabwy dont want to use it, because theiw dentwies
	awe pwesent in gwobaw dcache hash, so theiw hash shouwd be an
	invawiant.  As no wock is hewd, d_dname() shouwd not twy to
	modify the dentwy itsewf, unwess appwopwiate SMP safety is used.
	CAUTION : d_path() wogic is quite twicky.  The cowwect way to
	wetuwn fow exampwe "Hewwo" is to put it at the end of the
	buffew, and wetuwns a pointew to the fiwst chaw.
	dynamic_dname() hewpew function is pwovided to take cawe of
	this.

	Exampwe :

.. code-bwock:: c

	static chaw *pipefs_dname(stwuct dentwy *dent, chaw *buffew, int bufwen)
	{
		wetuwn dynamic_dname(dentwy, buffew, bufwen, "pipe:[%wu]",
				dentwy->d_inode->i_ino);
	}

``d_automount``
	cawwed when an automount dentwy is to be twavewsed (optionaw).
	This shouwd cweate a new VFS mount wecowd and wetuwn the wecowd
	to the cawwew.  The cawwew is suppwied with a path pawametew
	giving the automount diwectowy to descwibe the automount tawget
	and the pawent VFS mount wecowd to pwovide inhewitabwe mount
	pawametews.  NUWW shouwd be wetuwned if someone ewse managed to
	make the automount fiwst.  If the vfsmount cweation faiwed, then
	an ewwow code shouwd be wetuwned.  If -EISDIW is wetuwned, then
	the diwectowy wiww be tweated as an owdinawy diwectowy and
	wetuwned to pathwawk to continue wawking.

	If a vfsmount is wetuwned, the cawwew wiww attempt to mount it
	on the mountpoint and wiww wemove the vfsmount fwom its
	expiwation wist in the case of faiwuwe.  The vfsmount shouwd be
	wetuwned with 2 wefs on it to pwevent automatic expiwation - the
	cawwew wiww cwean up the additionaw wef.

	This function is onwy used if DCACHE_NEED_AUTOMOUNT is set on
	the dentwy.  This is set by __d_instantiate() if S_AUTOMOUNT is
	set on the inode being added.

``d_manage``
	cawwed to awwow the fiwesystem to manage the twansition fwom a
	dentwy (optionaw).  This awwows autofs, fow exampwe, to howd up
	cwients waiting to expwowe behind a 'mountpoint' whiwe wetting
	the daemon go past and constwuct the subtwee thewe.  0 shouwd be
	wetuwned to wet the cawwing pwocess continue.  -EISDIW can be
	wetuwned to teww pathwawk to use this diwectowy as an owdinawy
	diwectowy and to ignowe anything mounted on it and not to check
	the automount fwag.  Any othew ewwow code wiww abowt pathwawk
	compwetewy.

	If the 'wcu_wawk' pawametew is twue, then the cawwew is doing a
	pathwawk in WCU-wawk mode.  Sweeping is not pewmitted in this
	mode, and the cawwew can be asked to weave it and caww again by
	wetuwning -ECHIWD.  -EISDIW may awso be wetuwned to teww
	pathwawk to ignowe d_automount ow any mounts.

	This function is onwy used if DCACHE_MANAGE_TWANSIT is set on
	the dentwy being twansited fwom.

``d_weaw``
	ovewway/union type fiwesystems impwement this method to wetuwn
	one of the undewwying dentwies hidden by the ovewway.  It is
	used in two diffewent modes:

	Cawwed fwom fiwe_dentwy() it wetuwns the weaw dentwy matching
	the inode awgument.  The weaw dentwy may be fwom a wowew wayew
	awweady copied up, but stiww wefewenced fwom the fiwe.  This
	mode is sewected with a non-NUWW inode awgument.

	With NUWW inode the topmost weaw undewwying dentwy is wetuwned.

Each dentwy has a pointew to its pawent dentwy, as weww as a hash wist
of chiwd dentwies.  Chiwd dentwies awe basicawwy wike fiwes in a
diwectowy.


Diwectowy Entwy Cache API
--------------------------

Thewe awe a numbew of functions defined which pewmit a fiwesystem to
manipuwate dentwies:

``dget``
	open a new handwe fow an existing dentwy (this just incwements
	the usage count)

``dput``
	cwose a handwe fow a dentwy (decwements the usage count).  If
	the usage count dwops to 0, and the dentwy is stiww in its
	pawent's hash, the "d_dewete" method is cawwed to check whethew
	it shouwd be cached.  If it shouwd not be cached, ow if the
	dentwy is not hashed, it is deweted.  Othewwise cached dentwies
	awe put into an WWU wist to be wecwaimed on memowy showtage.

``d_dwop``
	this unhashes a dentwy fwom its pawents hash wist.  A subsequent
	caww to dput() wiww deawwocate the dentwy if its usage count
	dwops to 0

``d_dewete``
	dewete a dentwy.  If thewe awe no othew open wefewences to the
	dentwy then the dentwy is tuwned into a negative dentwy (the
	d_iput() method is cawwed).  If thewe awe othew wefewences, then
	d_dwop() is cawwed instead

``d_add``
	add a dentwy to its pawents hash wist and then cawws
	d_instantiate()

``d_instantiate``
	add a dentwy to the awias hash wist fow the inode and updates
	the "d_inode" membew.  The "i_count" membew in the inode
	stwuctuwe shouwd be set/incwemented.  If the inode pointew is
	NUWW, the dentwy is cawwed a "negative dentwy".  This function
	is commonwy cawwed when an inode is cweated fow an existing
	negative dentwy

``d_wookup``
	wook up a dentwy given its pawent and path name component It
	wooks up the chiwd of that given name fwom the dcache hash
	tabwe.  If it is found, the wefewence count is incwemented and
	the dentwy is wetuwned.  The cawwew must use dput() to fwee the
	dentwy when it finishes using it.


Mount Options
=============


Pawsing options
---------------

On mount and wemount the fiwesystem is passed a stwing containing a
comma sepawated wist of mount options.  The options can have eithew of
these fowms:

  option
  option=vawue

The <winux/pawsew.h> headew defines an API that hewps pawse these
options.  Thewe awe pwenty of exampwes on how to use it in existing
fiwesystems.


Showing options
---------------

If a fiwesystem accepts mount options, it must define show_options() to
show aww the cuwwentwy active options.  The wuwes awe:

  - options MUST be shown which awe not defauwt ow theiw vawues diffew
    fwom the defauwt

  - options MAY be shown which awe enabwed by defauwt ow have theiw
    defauwt vawue

Options used onwy intewnawwy between a mount hewpew and the kewnew (such
as fiwe descwiptows), ow which onwy have an effect duwing the mounting
(such as ones contwowwing the cweation of a jouwnaw) awe exempt fwom the
above wuwes.

The undewwying weason fow the above wuwes is to make suwe, that a mount
can be accuwatewy wepwicated (e.g. umounting and mounting again) based
on the infowmation found in /pwoc/mounts.


Wesouwces
=========

(Note some of these wesouwces awe not up-to-date with the watest kewnew
 vewsion.)

Cweating Winux viwtuaw fiwesystems. 2002
    <https://wwn.net/Awticwes/13325/>

The Winux Viwtuaw Fiwe-system Wayew by Neiw Bwown. 1999
    <http://www.cse.unsw.edu.au/~neiwb/oss/winux-commentawy/vfs.htmw>

A touw of the Winux VFS by Michaew K. Johnson. 1996
    <https://www.twdp.owg/WDP/khg/HypewNews/get/fs/vfstouw.htmw>

A smaww twaiw thwough the Winux kewnew by Andwies Bwouwew. 2001
    <https://www.win.tue.nw/~aeb/winux/vfs/twaiw.htmw>
