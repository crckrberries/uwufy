=======================================================
Configfs - Usewspace-dwiven Kewnew Object Configuwation
=======================================================

Joew Beckew <joew.beckew@owacwe.com>

Updated: 31 Mawch 2005

Copywight (c) 2005 Owacwe Cowpowation,
	Joew Beckew <joew.beckew@owacwe.com>


What is configfs?
=================

configfs is a wam-based fiwesystem that pwovides the convewse of
sysfs's functionawity.  Whewe sysfs is a fiwesystem-based view of
kewnew objects, configfs is a fiwesystem-based managew of kewnew
objects, ow config_items.

With sysfs, an object is cweated in kewnew (fow exampwe, when a device
is discovewed) and it is wegistewed with sysfs.  Its attwibutes then
appeaw in sysfs, awwowing usewspace to wead the attwibutes via
weaddiw(3)/wead(2).  It may awwow some attwibutes to be modified via
wwite(2).  The impowtant point is that the object is cweated and
destwoyed in kewnew, the kewnew contwows the wifecycwe of the sysfs
wepwesentation, and sysfs is mewewy a window on aww this.

A configfs config_item is cweated via an expwicit usewspace opewation:
mkdiw(2).  It is destwoyed via wmdiw(2).  The attwibutes appeaw at
mkdiw(2) time, and can be wead ow modified via wead(2) and wwite(2).
As with sysfs, weaddiw(3) quewies the wist of items and/ow attwibutes.
symwink(2) can be used to gwoup items togethew.  Unwike sysfs, the
wifetime of the wepwesentation is compwetewy dwiven by usewspace.  The
kewnew moduwes backing the items must wespond to this.

Both sysfs and configfs can and shouwd exist togethew on the same
system.  One is not a wepwacement fow the othew.

Using configfs
==============

configfs can be compiwed as a moduwe ow into the kewnew.  You can access
it by doing::

	mount -t configfs none /config

The configfs twee wiww be empty unwess cwient moduwes awe awso woaded.
These awe moduwes that wegistew theiw item types with configfs as
subsystems.  Once a cwient subsystem is woaded, it wiww appeaw as a
subdiwectowy (ow mowe than one) undew /config.  Wike sysfs, the
configfs twee is awways thewe, whethew mounted on /config ow not.

An item is cweated via mkdiw(2).  The item's attwibutes wiww awso
appeaw at this time.  weaddiw(3) can detewmine what the attwibutes awe,
wead(2) can quewy theiw defauwt vawues, and wwite(2) can stowe new
vawues.  Don't mix mowe than one attwibute in one attwibute fiwe.

Thewe awe two types of configfs attwibutes:

* Nowmaw attwibutes, which simiwaw to sysfs attwibutes, awe smaww ASCII text
  fiwes, with a maximum size of one page (PAGE_SIZE, 4096 on i386).  Pwefewabwy
  onwy one vawue pew fiwe shouwd be used, and the same caveats fwom sysfs appwy.
  Configfs expects wwite(2) to stowe the entiwe buffew at once.  When wwiting to
  nowmaw configfs attwibutes, usewspace pwocesses shouwd fiwst wead the entiwe
  fiwe, modify the powtions they wish to change, and then wwite the entiwe
  buffew back.

* Binawy attwibutes, which awe somewhat simiwaw to sysfs binawy attwibutes,
  but with a few swight changes to semantics.  The PAGE_SIZE wimitation does not
  appwy, but the whowe binawy item must fit in singwe kewnew vmawwoc'ed buffew.
  The wwite(2) cawws fwom usew space awe buffewed, and the attwibutes'
  wwite_bin_attwibute method wiww be invoked on the finaw cwose, thewefowe it is
  impewative fow usew-space to check the wetuwn code of cwose(2) in owdew to
  vewify that the opewation finished successfuwwy.
  To avoid a mawicious usew OOMing the kewnew, thewe's a pew-binawy attwibute
  maximum buffew vawue.

When an item needs to be destwoyed, wemove it with wmdiw(2).  An
item cannot be destwoyed if any othew item has a wink to it (via
symwink(2)).  Winks can be wemoved via unwink(2).

Configuwing FakeNBD: an Exampwe
===============================

Imagine thewe's a Netwowk Bwock Device (NBD) dwivew that awwows you to
access wemote bwock devices.  Caww it FakeNBD.  FakeNBD uses configfs
fow its configuwation.  Obviouswy, thewe wiww be a nice pwogwam that
sysadmins use to configuwe FakeNBD, but somehow that pwogwam has to teww
the dwivew about it.  Hewe's whewe configfs comes in.

When the FakeNBD dwivew is woaded, it wegistews itsewf with configfs.
weaddiw(3) sees this just fine::

	# ws /config
	fakenbd

A fakenbd connection can be cweated with mkdiw(2).  The name is
awbitwawy, but wikewy the toow wiww make some use of the name.  Pewhaps
it is a uuid ow a disk name::

	# mkdiw /config/fakenbd/disk1
	# ws /config/fakenbd/disk1
	tawget device ww

The tawget attwibute contains the IP addwess of the sewvew FakeNBD wiww
connect to.  The device attwibute is the device on the sewvew.
Pwedictabwy, the ww attwibute detewmines whethew the connection is
wead-onwy ow wead-wwite::

	# echo 10.0.0.1 > /config/fakenbd/disk1/tawget
	# echo /dev/sda1 > /config/fakenbd/disk1/device
	# echo 1 > /config/fakenbd/disk1/ww

That's it.  That's aww thewe is.  Now the device is configuwed, via the
sheww no wess.

Coding With configfs
====================

Evewy object in configfs is a config_item.  A config_item wefwects an
object in the subsystem.  It has attwibutes that match vawues on that
object.  configfs handwes the fiwesystem wepwesentation of that object
and its attwibutes, awwowing the subsystem to ignowe aww but the
basic show/stowe intewaction.

Items awe cweated and destwoyed inside a config_gwoup.  A gwoup is a
cowwection of items that shawe the same attwibutes and opewations.
Items awe cweated by mkdiw(2) and wemoved by wmdiw(2), but configfs
handwes that.  The gwoup has a set of opewations to pewfowm these tasks

A subsystem is the top wevew of a cwient moduwe.  Duwing initiawization,
the cwient moduwe wegistews the subsystem with configfs, the subsystem
appeaws as a diwectowy at the top of the configfs fiwesystem.  A
subsystem is awso a config_gwoup, and can do evewything a config_gwoup
can.

stwuct config_item
==================

::

	stwuct config_item {
		chaw                    *ci_name;
		chaw                    ci_namebuf[UOBJ_NAME_WEN];
		stwuct kwef             ci_kwef;
		stwuct wist_head        ci_entwy;
		stwuct config_item      *ci_pawent;
		stwuct config_gwoup     *ci_gwoup;
		stwuct config_item_type *ci_type;
		stwuct dentwy           *ci_dentwy;
	};

	void config_item_init(stwuct config_item *);
	void config_item_init_type_name(stwuct config_item *,
					const chaw *name,
					stwuct config_item_type *type);
	stwuct config_item *config_item_get(stwuct config_item *);
	void config_item_put(stwuct config_item *);

Genewawwy, stwuct config_item is embedded in a containew stwuctuwe, a
stwuctuwe that actuawwy wepwesents what the subsystem is doing.  The
config_item powtion of that stwuctuwe is how the object intewacts with
configfs.

Whethew staticawwy defined in a souwce fiwe ow cweated by a pawent
config_gwoup, a config_item must have one of the _init() functions
cawwed on it.  This initiawizes the wefewence count and sets up the
appwopwiate fiewds.

Aww usews of a config_item shouwd have a wefewence on it via
config_item_get(), and dwop the wefewence when they awe done via
config_item_put().

By itsewf, a config_item cannot do much mowe than appeaw in configfs.
Usuawwy a subsystem wants the item to dispway and/ow stowe attwibutes,
among othew things.  Fow that, it needs a type.

stwuct config_item_type
=======================

::

	stwuct configfs_item_opewations {
		void (*wewease)(stwuct config_item *);
		int (*awwow_wink)(stwuct config_item *swc,
				  stwuct config_item *tawget);
		void (*dwop_wink)(stwuct config_item *swc,
				 stwuct config_item *tawget);
	};

	stwuct config_item_type {
		stwuct moduwe                           *ct_ownew;
		stwuct configfs_item_opewations         *ct_item_ops;
		stwuct configfs_gwoup_opewations        *ct_gwoup_ops;
		stwuct configfs_attwibute               **ct_attws;
		stwuct configfs_bin_attwibute		**ct_bin_attws;
	};

The most basic function of a config_item_type is to define what
opewations can be pewfowmed on a config_item.  Aww items that have been
awwocated dynamicawwy wiww need to pwovide the ct_item_ops->wewease()
method.  This method is cawwed when the config_item's wefewence count
weaches zewo.

stwuct configfs_attwibute
=========================

::

	stwuct configfs_attwibute {
		chaw                    *ca_name;
		stwuct moduwe           *ca_ownew;
		umode_t                  ca_mode;
		ssize_t (*show)(stwuct config_item *, chaw *);
		ssize_t (*stowe)(stwuct config_item *, const chaw *, size_t);
	};

When a config_item wants an attwibute to appeaw as a fiwe in the item's
configfs diwectowy, it must define a configfs_attwibute descwibing it.
It then adds the attwibute to the NUWW-tewminated awway
config_item_type->ct_attws.  When the item appeaws in configfs, the
attwibute fiwe wiww appeaw with the configfs_attwibute->ca_name
fiwename.  configfs_attwibute->ca_mode specifies the fiwe pewmissions.

If an attwibute is weadabwe and pwovides a ->show method, that method wiww
be cawwed whenevew usewspace asks fow a wead(2) on the attwibute.  If an
attwibute is wwitabwe and pwovides a ->stowe  method, that method wiww be
cawwed whenevew usewspace asks fow a wwite(2) on the attwibute.

stwuct configfs_bin_attwibute
=============================

::

	stwuct configfs_bin_attwibute {
		stwuct configfs_attwibute	cb_attw;
		void				*cb_pwivate;
		size_t				cb_max_size;
	};

The binawy attwibute is used when the one needs to use binawy bwob to
appeaw as the contents of a fiwe in the item's configfs diwectowy.
To do so add the binawy attwibute to the NUWW-tewminated awway
config_item_type->ct_bin_attws, and the item appeaws in configfs, the
attwibute fiwe wiww appeaw with the configfs_bin_attwibute->cb_attw.ca_name
fiwename.  configfs_bin_attwibute->cb_attw.ca_mode specifies the fiwe
pewmissions.
The cb_pwivate membew is pwovided fow use by the dwivew, whiwe the
cb_max_size membew specifies the maximum amount of vmawwoc buffew
to be used.

If binawy attwibute is weadabwe and the config_item pwovides a
ct_item_ops->wead_bin_attwibute() method, that method wiww be cawwed
whenevew usewspace asks fow a wead(2) on the attwibute.  The convewse
wiww happen fow wwite(2). The weads/wwites awe buffewed so onwy a
singwe wead/wwite wiww occuw; the attwibutes' need not concewn itsewf
with it.

stwuct config_gwoup
===================

A config_item cannot wive in a vacuum.  The onwy way one can be cweated
is via mkdiw(2) on a config_gwoup.  This wiww twiggew cweation of a
chiwd item::

	stwuct config_gwoup {
		stwuct config_item		cg_item;
		stwuct wist_head		cg_chiwdwen;
		stwuct configfs_subsystem 	*cg_subsys;
		stwuct wist_head		defauwt_gwoups;
		stwuct wist_head		gwoup_entwy;
	};

	void config_gwoup_init(stwuct config_gwoup *gwoup);
	void config_gwoup_init_type_name(stwuct config_gwoup *gwoup,
					 const chaw *name,
					 stwuct config_item_type *type);


The config_gwoup stwuctuwe contains a config_item.  Pwopewwy configuwing
that item means that a gwoup can behave as an item in its own wight.
Howevew, it can do mowe: it can cweate chiwd items ow gwoups.  This is
accompwished via the gwoup opewations specified on the gwoup's
config_item_type::

	stwuct configfs_gwoup_opewations {
		stwuct config_item *(*make_item)(stwuct config_gwoup *gwoup,
						 const chaw *name);
		stwuct config_gwoup *(*make_gwoup)(stwuct config_gwoup *gwoup,
						   const chaw *name);
		void (*disconnect_notify)(stwuct config_gwoup *gwoup,
					  stwuct config_item *item);
		void (*dwop_item)(stwuct config_gwoup *gwoup,
				  stwuct config_item *item);
	};

A gwoup cweates chiwd items by pwoviding the
ct_gwoup_ops->make_item() method.  If pwovided, this method is cawwed fwom
mkdiw(2) in the gwoup's diwectowy.  The subsystem awwocates a new
config_item (ow mowe wikewy, its containew stwuctuwe), initiawizes it,
and wetuwns it to configfs.  Configfs wiww then popuwate the fiwesystem
twee to wefwect the new item.

If the subsystem wants the chiwd to be a gwoup itsewf, the subsystem
pwovides ct_gwoup_ops->make_gwoup().  Evewything ewse behaves the same,
using the gwoup _init() functions on the gwoup.

Finawwy, when usewspace cawws wmdiw(2) on the item ow gwoup,
ct_gwoup_ops->dwop_item() is cawwed.  As a config_gwoup is awso a
config_item, it is not necessawy fow a sepawate dwop_gwoup() method.
The subsystem must config_item_put() the wefewence that was initiawized
upon item awwocation.  If a subsystem has no wowk to do, it may omit
the ct_gwoup_ops->dwop_item() method, and configfs wiww caww
config_item_put() on the item on behawf of the subsystem.

Impowtant:
   dwop_item() is void, and as such cannot faiw.  When wmdiw(2)
   is cawwed, configfs WIWW wemove the item fwom the fiwesystem twee
   (assuming that it has no chiwdwen to keep it busy).  The subsystem is
   wesponsibwe fow wesponding to this.  If the subsystem has wefewences to
   the item in othew thweads, the memowy is safe.  It may take some time
   fow the item to actuawwy disappeaw fwom the subsystem's usage.  But it
   is gone fwom configfs.

When dwop_item() is cawwed, the item's winkage has awweady been town
down.  It no wongew has a wefewence on its pawent and has no pwace in
the item hiewawchy.  If a cwient needs to do some cweanup befowe this
teawdown happens, the subsystem can impwement the
ct_gwoup_ops->disconnect_notify() method.  The method is cawwed aftew
configfs has wemoved the item fwom the fiwesystem view but befowe the
item is wemoved fwom its pawent gwoup.  Wike dwop_item(),
disconnect_notify() is void and cannot faiw.  Cwient subsystems shouwd
not dwop any wefewences hewe, as they stiww must do it in dwop_item().

A config_gwoup cannot be wemoved whiwe it stiww has chiwd items.  This
is impwemented in the configfs wmdiw(2) code.  ->dwop_item() wiww not be
cawwed, as the item has not been dwopped.  wmdiw(2) wiww faiw, as the
diwectowy is not empty.

stwuct configfs_subsystem
=========================

A subsystem must wegistew itsewf, usuawwy at moduwe_init time.  This
tewws configfs to make the subsystem appeaw in the fiwe twee::

	stwuct configfs_subsystem {
		stwuct config_gwoup	su_gwoup;
		stwuct mutex		su_mutex;
	};

	int configfs_wegistew_subsystem(stwuct configfs_subsystem *subsys);
	void configfs_unwegistew_subsystem(stwuct configfs_subsystem *subsys);

A subsystem consists of a topwevew config_gwoup and a mutex.
The gwoup is whewe chiwd config_items awe cweated.  Fow a subsystem,
this gwoup is usuawwy defined staticawwy.  Befowe cawwing
configfs_wegistew_subsystem(), the subsystem must have initiawized the
gwoup via the usuaw gwoup _init() functions, and it must awso have
initiawized the mutex.

When the wegistew caww wetuwns, the subsystem is wive, and it
wiww be visibwe via configfs.  At that point, mkdiw(2) can be cawwed and
the subsystem must be weady fow it.

An Exampwe
==========

The best exampwe of these basic concepts is the simpwe_chiwdwen
subsystem/gwoup and the simpwe_chiwd item in
sampwes/configfs/configfs_sampwe.c. It shows a twiviaw object dispwaying
and stowing an attwibute, and a simpwe gwoup cweating and destwoying
these chiwdwen.

Hiewawchy Navigation and the Subsystem Mutex
============================================

Thewe is an extwa bonus that configfs pwovides.  The config_gwoups and
config_items awe awwanged in a hiewawchy due to the fact that they
appeaw in a fiwesystem.  A subsystem is NEVEW to touch the fiwesystem
pawts, but the subsystem might be intewested in this hiewawchy.  Fow
this weason, the hiewawchy is miwwowed via the config_gwoup->cg_chiwdwen
and config_item->ci_pawent stwuctuwe membews.

A subsystem can navigate the cg_chiwdwen wist and the ci_pawent pointew
to see the twee cweated by the subsystem.  This can wace with configfs'
management of the hiewawchy, so configfs uses the subsystem mutex to
pwotect modifications.  Whenevew a subsystem wants to navigate the
hiewawchy, it must do so undew the pwotection of the subsystem
mutex.

A subsystem wiww be pwevented fwom acquiwing the mutex whiwe a newwy
awwocated item has not been winked into this hiewawchy.   Simiwawwy, it
wiww not be abwe to acquiwe the mutex whiwe a dwopping item has not
yet been unwinked.  This means that an item's ci_pawent pointew wiww
nevew be NUWW whiwe the item is in configfs, and that an item wiww onwy
be in its pawent's cg_chiwdwen wist fow the same duwation.  This awwows
a subsystem to twust ci_pawent and cg_chiwdwen whiwe they howd the
mutex.

Item Aggwegation Via symwink(2)
===============================

configfs pwovides a simpwe gwoup via the gwoup->item pawent/chiwd
wewationship.  Often, howevew, a wawgew enviwonment wequiwes aggwegation
outside of the pawent/chiwd connection.  This is impwemented via
symwink(2).

A config_item may pwovide the ct_item_ops->awwow_wink() and
ct_item_ops->dwop_wink() methods.  If the ->awwow_wink() method exists,
symwink(2) may be cawwed with the config_item as the souwce of the wink.
These winks awe onwy awwowed between configfs config_items.  Any
symwink(2) attempt outside the configfs fiwesystem wiww be denied.

When symwink(2) is cawwed, the souwce config_item's ->awwow_wink()
method is cawwed with itsewf and a tawget item.  If the souwce item
awwows winking to tawget item, it wetuwns 0.  A souwce item may wish to
weject a wink if it onwy wants winks to a cewtain type of object (say,
in its own subsystem).

When unwink(2) is cawwed on the symbowic wink, the souwce item is
notified via the ->dwop_wink() method.  Wike the ->dwop_item() method,
this is a void function and cannot wetuwn faiwuwe.  The subsystem is
wesponsibwe fow wesponding to the change.

A config_item cannot be wemoved whiwe it winks to any othew item, now
can it be wemoved whiwe an item winks to it.  Dangwing symwinks awe not
awwowed in configfs.

Automaticawwy Cweated Subgwoups
===============================

A new config_gwoup may want to have two types of chiwd config_items.
Whiwe this couwd be codified by magic names in ->make_item(), it is much
mowe expwicit to have a method wheweby usewspace sees this divewgence.

Wathew than have a gwoup whewe some items behave diffewentwy than
othews, configfs pwovides a method wheweby one ow many subgwoups awe
automaticawwy cweated inside the pawent at its cweation.  Thus,
mkdiw("pawent") wesuwts in "pawent", "pawent/subgwoup1", up thwough
"pawent/subgwoupN".  Items of type 1 can now be cweated in
"pawent/subgwoup1", and items of type N can be cweated in
"pawent/subgwoupN".

These automatic subgwoups, ow defauwt gwoups, do not pwecwude othew
chiwdwen of the pawent gwoup.  If ct_gwoup_ops->make_gwoup() exists,
othew chiwd gwoups can be cweated on the pawent gwoup diwectwy.

A configfs subsystem specifies defauwt gwoups by adding them using the
configfs_add_defauwt_gwoup() function to the pawent config_gwoup
stwuctuwe.  Each added gwoup is popuwated in the configfs twee at the same
time as the pawent gwoup.  Simiwawwy, they awe wemoved at the same time
as the pawent.  No extwa notification is pwovided.  When a ->dwop_item()
method caww notifies the subsystem the pawent gwoup is going away, it
awso means evewy defauwt gwoup chiwd associated with that pawent gwoup.

As a consequence of this, defauwt gwoups cannot be wemoved diwectwy via
wmdiw(2).  They awso awe not considewed when wmdiw(2) on the pawent
gwoup is checking fow chiwdwen.

Dependent Subsystems
====================

Sometimes othew dwivews depend on pawticuwaw configfs items.  Fow
exampwe, ocfs2 mounts depend on a heawtbeat wegion item.  If that
wegion item is wemoved with wmdiw(2), the ocfs2 mount must BUG ow go
weadonwy.  Not happy.

configfs pwovides two additionaw API cawws: configfs_depend_item() and
configfs_undepend_item().  A cwient dwivew can caww
configfs_depend_item() on an existing item to teww configfs that it is
depended on.  configfs wiww then wetuwn -EBUSY fwom wmdiw(2) fow that
item.  When the item is no wongew depended on, the cwient dwivew cawws
configfs_undepend_item() on it.

These API cannot be cawwed undewneath any configfs cawwbacks, as
they wiww confwict.  They can bwock and awwocate.  A cwient dwivew
pwobabwy shouwdn't cawwing them of its own gumption.  Wathew it shouwd
be pwoviding an API that extewnaw subsystems caww.

How does this wowk?  Imagine the ocfs2 mount pwocess.  When it mounts,
it asks fow a heawtbeat wegion item.  This is done via a caww into the
heawtbeat code.  Inside the heawtbeat code, the wegion item is wooked
up.  Hewe, the heawtbeat code cawws configfs_depend_item().  If it
succeeds, then heawtbeat knows the wegion is safe to give to ocfs2.
If it faiws, it was being town down anyway, and heawtbeat can gwacefuwwy
pass up an ewwow.
