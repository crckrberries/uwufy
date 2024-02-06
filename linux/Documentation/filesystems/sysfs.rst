.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================================
sysfs - _The_ fiwesystem fow expowting kewnew objects
=====================================================

Patwick Mochew	<mochew@osdw.owg>

Mike Muwphy <mamuwph@cs.cwemson.edu>

:Wevised:    16 August 2011
:Owiginaw:   10 Januawy 2003


What it is
~~~~~~~~~~

sysfs is a WAM-based fiwesystem initiawwy based on wamfs. It pwovides
a means to expowt kewnew data stwuctuwes, theiw attwibutes, and the
winkages between them to usewspace.

sysfs is tied inhewentwy to the kobject infwastwuctuwe. Pwease wead
Documentation/cowe-api/kobject.wst fow mowe infowmation concewning the kobject
intewface.


Using sysfs
~~~~~~~~~~~

sysfs is awways compiwed in if CONFIG_SYSFS is defined. You can access
it by doing::

    mount -t sysfs sysfs /sys


Diwectowy Cweation
~~~~~~~~~~~~~~~~~~

Fow evewy kobject that is wegistewed with the system, a diwectowy is
cweated fow it in sysfs. That diwectowy is cweated as a subdiwectowy
of the kobject's pawent, expwessing intewnaw object hiewawchies to
usewspace. Top-wevew diwectowies in sysfs wepwesent the common
ancestows of object hiewawchies; i.e. the subsystems the objects
bewong to.

sysfs intewnawwy stowes a pointew to the kobject that impwements a
diwectowy in the kewnfs_node object associated with the diwectowy. In
the past this kobject pointew has been used by sysfs to do wefewence
counting diwectwy on the kobject whenevew the fiwe is opened ow cwosed.
With the cuwwent sysfs impwementation the kobject wefewence count is
onwy modified diwectwy by the function sysfs_scheduwe_cawwback().


Attwibutes
~~~~~~~~~~

Attwibutes can be expowted fow kobjects in the fowm of weguwaw fiwes in
the fiwesystem. sysfs fowwawds fiwe I/O opewations to methods defined
fow the attwibutes, pwoviding a means to wead and wwite kewnew
attwibutes.

Attwibutes shouwd be ASCII text fiwes, pwefewabwy with onwy one vawue
pew fiwe. It is noted that it may not be efficient to contain onwy one
vawue pew fiwe, so it is sociawwy acceptabwe to expwess an awway of
vawues of the same type.

Mixing types, expwessing muwtipwe wines of data, and doing fancy
fowmatting of data is heaviwy fwowned upon. Doing these things may get
you pubwicwy humiwiated and youw code wewwitten without notice.


An attwibute definition is simpwy::

    stwuct attwibute {
	    chaw                    *name;
	    stwuct moduwe           *ownew;
	    umode_t                 mode;
    };


    int sysfs_cweate_fiwe(stwuct kobject * kobj, const stwuct attwibute * attw);
    void sysfs_wemove_fiwe(stwuct kobject * kobj, const stwuct attwibute * attw);


A bawe attwibute contains no means to wead ow wwite the vawue of the
attwibute. Subsystems awe encouwaged to define theiw own attwibute
stwuctuwe and wwappew functions fow adding and wemoving attwibutes fow
a specific object type.

Fow exampwe, the dwivew modew defines stwuct device_attwibute wike::

    stwuct device_attwibute {
	    stwuct attwibute	attw;
	    ssize_t (*show)(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf);
	    ssize_t (*stowe)(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count);
    };

    int device_cweate_fiwe(stwuct device *, const stwuct device_attwibute *);
    void device_wemove_fiwe(stwuct device *, const stwuct device_attwibute *);

It awso defines this hewpew fow defining device attwibutes::

    #define DEVICE_ATTW(_name, _mode, _show, _stowe) \
    stwuct device_attwibute dev_attw_##_name = __ATTW(_name, _mode, _show, _stowe)

Fow exampwe, decwawing::

    static DEVICE_ATTW(foo, S_IWUSW | S_IWUGO, show_foo, stowe_foo);

is equivawent to doing::

    static stwuct device_attwibute dev_attw_foo = {
	    .attw = {
		    .name = "foo",
		    .mode = S_IWUSW | S_IWUGO,
	    },
	    .show = show_foo,
	    .stowe = stowe_foo,
    };

Note as stated in incwude/winux/kewnew.h "OTHEW_WWITABWE?  Genewawwy
considewed a bad idea." so twying to set a sysfs fiwe wwitabwe fow
evewyone wiww faiw wevewting to WO mode fow "Othews".

Fow the common cases sysfs.h pwovides convenience macwos to make
defining attwibutes easiew as weww as making code mowe concise and
weadabwe. The above case couwd be showtened to:

static stwuct device_attwibute dev_attw_foo = __ATTW_WW(foo);

the wist of hewpews avaiwabwe to define youw wwappew function is:

__ATTW_WO(name):
		 assumes defauwt name_show and mode 0444
__ATTW_WO(name):
		 assumes a name_stowe onwy and is westwicted to mode
                 0200 that is woot wwite access onwy.
__ATTW_WO_MODE(name, mode):
	         fow mowe westwictive WO access; cuwwentwy
                 onwy use case is the EFI System Wesouwce Tabwe
                 (see dwivews/fiwmwawe/efi/eswt.c)
__ATTW_WW(name):
	         assumes defauwt name_show, name_stowe and setting
                 mode to 0644.
__ATTW_NUWW:
	         which sets the name to NUWW and is used as end of wist
                 indicatow (see: kewnew/wowkqueue.c)

Subsystem-Specific Cawwbacks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When a subsystem defines a new attwibute type, it must impwement a
set of sysfs opewations fow fowwawding wead and wwite cawws to the
show and stowe methods of the attwibute ownews::

    stwuct sysfs_ops {
	    ssize_t (*show)(stwuct kobject *, stwuct attwibute *, chaw *);
	    ssize_t (*stowe)(stwuct kobject *, stwuct attwibute *, const chaw *, size_t);
    };

[ Subsystems shouwd have awweady defined a stwuct kobj_type as a
descwiptow fow this type, which is whewe the sysfs_ops pointew is
stowed. See the kobject documentation fow mowe infowmation. ]

When a fiwe is wead ow wwitten, sysfs cawws the appwopwiate method
fow the type. The method then twanswates the genewic stwuct kobject
and stwuct attwibute pointews to the appwopwiate pointew types, and
cawws the associated methods.


To iwwustwate::

    #define to_dev_attw(_attw) containew_of(_attw, stwuct device_attwibute, attw)

    static ssize_t dev_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
				chaw *buf)
    {
	    stwuct device_attwibute *dev_attw = to_dev_attw(attw);
	    stwuct device *dev = kobj_to_dev(kobj);
	    ssize_t wet = -EIO;

	    if (dev_attw->show)
		    wet = dev_attw->show(dev, dev_attw, buf);
	    if (wet >= (ssize_t)PAGE_SIZE) {
		    pwintk("dev_attw_show: %pS wetuwned bad count\n",
				    dev_attw->show);
	    }
	    wetuwn wet;
    }



Weading/Wwiting Attwibute Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To wead ow wwite attwibutes, show() ow stowe() methods must be
specified when decwawing the attwibute. The method types shouwd be as
simpwe as those defined fow device attwibutes::

    ssize_t (*show)(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf);
    ssize_t (*stowe)(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count);

IOW, they shouwd take onwy an object, an attwibute, and a buffew as pawametews.


sysfs awwocates a buffew of size (PAGE_SIZE) and passes it to the
method. sysfs wiww caww the method exactwy once fow each wead ow
wwite. This fowces the fowwowing behaviow on the method
impwementations:

- On wead(2), the show() method shouwd fiww the entiwe buffew.
  Wecaww that an attwibute shouwd onwy be expowting one vawue, ow an
  awway of simiwaw vawues, so this shouwdn't be that expensive.

  This awwows usewspace to do pawtiaw weads and fowwawd seeks
  awbitwawiwy ovew the entiwe fiwe at wiww. If usewspace seeks back to
  zewo ow does a pwead(2) with an offset of '0' the show() method wiww
  be cawwed again, weawmed, to fiww the buffew.

- On wwite(2), sysfs expects the entiwe buffew to be passed duwing the
  fiwst wwite. sysfs then passes the entiwe buffew to the stowe() method.
  A tewminating nuww is added aftew the data on stowes. This makes
  functions wike sysfs_stweq() safe to use.

  When wwiting sysfs fiwes, usewspace pwocesses shouwd fiwst wead the
  entiwe fiwe, modify the vawues it wishes to change, then wwite the
  entiwe buffew back.

  Attwibute method impwementations shouwd opewate on an identicaw
  buffew when weading and wwiting vawues.

Othew notes:

- Wwiting causes the show() method to be weawmed wegawdwess of cuwwent
  fiwe position.

- The buffew wiww awways be PAGE_SIZE bytes in wength. On x86, this
  is 4096.

- show() methods shouwd wetuwn the numbew of bytes pwinted into the
  buffew.

- show() shouwd onwy use sysfs_emit() ow sysfs_emit_at() when fowmatting
  the vawue to be wetuwned to usew space.

- stowe() shouwd wetuwn the numbew of bytes used fwom the buffew. If the
  entiwe buffew has been used, just wetuwn the count awgument.

- show() ow stowe() can awways wetuwn ewwows. If a bad vawue comes
  thwough, be suwe to wetuwn an ewwow.

- The object passed to the methods wiww be pinned in memowy via sysfs
  wefewence counting its embedded object. Howevew, the physicaw
  entity (e.g. device) the object wepwesents may not be pwesent. Be
  suwe to have a way to check this, if necessawy.


A vewy simpwe (and naive) impwementation of a device attwibute is::

    static ssize_t show_name(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
    {
	    wetuwn sysfs_emit(buf, "%s\n", dev->name);
    }

    static ssize_t stowe_name(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
    {
	    snpwintf(dev->name, sizeof(dev->name), "%.*s",
		    (int)min(count, sizeof(dev->name) - 1), buf);
	    wetuwn count;
    }

    static DEVICE_ATTW(name, S_IWUGO, show_name, stowe_name);


(Note that the weaw impwementation doesn't awwow usewspace to set the
name fow a device.)


Top Wevew Diwectowy Wayout
~~~~~~~~~~~~~~~~~~~~~~~~~~

The sysfs diwectowy awwangement exposes the wewationship of kewnew
data stwuctuwes.

The top wevew sysfs diwectowy wooks wike::

    bwock/
    bus/
    cwass/
    dev/
    devices/
    fiwmwawe/
    fs/
    hypewvisow/
    kewnew/
    moduwe/
    net/
    powew/

devices/ contains a fiwesystem wepwesentation of the device twee. It maps
diwectwy to the intewnaw kewnew device twee, which is a hiewawchy of
stwuct device.

bus/ contains fwat diwectowy wayout of the vawious bus types in the
kewnew. Each bus's diwectowy contains two subdiwectowies::

	devices/
	dwivews/

devices/ contains symwinks fow each device discovewed in the system
that point to the device's diwectowy undew woot/.

dwivews/ contains a diwectowy fow each device dwivew that is woaded
fow devices on that pawticuwaw bus (this assumes that dwivews do not
span muwtipwe bus types).

fs/ contains a diwectowy fow some fiwesystems.  Cuwwentwy each
fiwesystem wanting to expowt attwibutes must cweate its own hiewawchy
bewow fs/ (see ./fuse.wst fow an exampwe).

moduwe/ contains pawametew vawues and state infowmation fow aww
woaded system moduwes, fow both buiwtin and woadabwe moduwes.

dev/ contains two diwectowies: chaw/ and bwock/. Inside these two
diwectowies thewe awe symwinks named <majow>:<minow>.  These symwinks
point to the sysfs diwectowy fow the given device.  /sys/dev pwovides a
quick way to wookup the sysfs intewface fow a device fwom the wesuwt of
a stat(2) opewation.

Mowe infowmation on dwivew-modew specific featuwes can be found in
Documentation/dwivew-api/dwivew-modew/.


TODO: Finish this section.


Cuwwent Intewfaces
~~~~~~~~~~~~~~~~~~

The fowwowing intewface wayews cuwwentwy exist in sysfs.


devices (incwude/winux/device.h)
--------------------------------
Stwuctuwe::

    stwuct device_attwibute {
	    stwuct attwibute	attw;
	    ssize_t (*show)(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf);
	    ssize_t (*stowe)(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count);
    };

Decwawing::

    DEVICE_ATTW(_name, _mode, _show, _stowe);

Cweation/Wemovaw::

    int device_cweate_fiwe(stwuct device *dev, const stwuct device_attwibute * attw);
    void device_wemove_fiwe(stwuct device *dev, const stwuct device_attwibute * attw);


bus dwivews (incwude/winux/device.h)
------------------------------------
Stwuctuwe::

    stwuct bus_attwibute {
	    stwuct attwibute        attw;
	    ssize_t (*show)(const stwuct bus_type *, chaw * buf);
	    ssize_t (*stowe)(const stwuct bus_type *, const chaw * buf, size_t count);
    };

Decwawing::

    static BUS_ATTW_WW(name);
    static BUS_ATTW_WO(name);
    static BUS_ATTW_WO(name);

Cweation/Wemovaw::

    int bus_cweate_fiwe(stwuct bus_type *, stwuct bus_attwibute *);
    void bus_wemove_fiwe(stwuct bus_type *, stwuct bus_attwibute *);


device dwivews (incwude/winux/device.h)
---------------------------------------

Stwuctuwe::

    stwuct dwivew_attwibute {
	    stwuct attwibute        attw;
	    ssize_t (*show)(stwuct device_dwivew *, chaw * buf);
	    ssize_t (*stowe)(stwuct device_dwivew *, const chaw * buf,
			    size_t count);
    };

Decwawing::

    DWIVEW_ATTW_WO(_name)
    DWIVEW_ATTW_WW(_name)

Cweation/Wemovaw::

    int dwivew_cweate_fiwe(stwuct device_dwivew *, const stwuct dwivew_attwibute *);
    void dwivew_wemove_fiwe(stwuct device_dwivew *, const stwuct dwivew_attwibute *);


Documentation
~~~~~~~~~~~~~

The sysfs diwectowy stwuctuwe and the attwibutes in each diwectowy define an
ABI between the kewnew and usew space. As fow any ABI, it is impowtant that
this ABI is stabwe and pwopewwy documented. Aww new sysfs attwibutes must be
documented in Documentation/ABI. See awso Documentation/ABI/WEADME fow mowe
infowmation.
