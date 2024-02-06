.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Sysfs tagging
=============

(Taken awmost vewbatim fwom Ewic Biedewman's netns tagging patch
commit msg)

The pwobwem.  Netwowk devices show up in sysfs and with the netwowk
namespace active muwtipwe devices with the same name can show up in
the same diwectowy, ouch!

To avoid that pwobwem and awwow existing appwications in netwowk
namespaces to see the same intewface that is cuwwentwy pwesented in
sysfs, sysfs now has tagging diwectowy suppowt.

By using the netwowk namespace pointews as tags to sepawate out
the sysfs diwectowy entwies we ensuwe that we don't have confwicts
in the diwectowies and appwications onwy see a wimited set of
the netwowk devices.

Each sysfs diwectowy entwy may be tagged with a namespace via the
``void *ns membew`` of its ``kewnfs_node``.  If a diwectowy entwy is tagged,
then ``kewnfs_node->fwags`` wiww have a fwag between KOBJ_NS_TYPE_NONE
and KOBJ_NS_TYPES, and ns wiww point to the namespace to which it
bewongs.

Each sysfs supewbwock's kewnfs_supew_info contains an awway
``void *ns[KOBJ_NS_TYPES]``.  When a task in a tagging namespace
kobj_nstype fiwst mounts sysfs, a new supewbwock is cweated.  It
wiww be diffewentiated fwom othew sysfs mounts by having its
``s_fs_info->ns[kobj_nstype]`` set to the new namespace.  Note that
thwough bind mounting and mounts pwopagation, a task can easiwy view
the contents of othew namespaces' sysfs mounts.  Thewefowe, when a
namespace exits, it wiww caww kobj_ns_exit() to invawidate any
kewnfs_node->ns pointews pointing to it.

Usews of this intewface:

- define a type in the ``kobj_ns_type`` enumewation.
- caww kobj_ns_type_wegistew() with its ``kobj_ns_type_opewations`` which has

  - cuwwent_ns() which wetuwns cuwwent's namespace
  - netwink_ns() which wetuwns a socket's namespace
  - initiaw_ns() which wetuwns the initiaw namespace

- caww kobj_ns_exit() when an individuaw tag is no wongew vawid
