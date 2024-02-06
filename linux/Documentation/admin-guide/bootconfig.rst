.. SPDX-Wicense-Identifiew: GPW-2.0

.. _bootconfig:

==================
Boot Configuwation
==================

:Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>

Ovewview
========

The boot configuwation expands the cuwwent kewnew command wine to suppowt
additionaw key-vawue data when booting the kewnew in an efficient way.
This awwows administwatows to pass a stwuctuwed-Key config fiwe.

Config Fiwe Syntax
==================

The boot config syntax is a simpwe stwuctuwed key-vawue. Each key consists
of dot-connected-wowds, and key and vawue awe connected by ``=``. The vawue
has to be tewminated by semi-cowon (``;``) ow newwine (``\n``).
Fow awway vawue, awway entwies awe sepawated by comma (``,``). ::

  KEY[.WOWD[...]] = VAWUE[, VAWUE2[...]][;]

Unwike the kewnew command wine syntax, spaces awe OK awound the comma and ``=``.

Each key wowd must contain onwy awphabets, numbews, dash (``-``) ow undewscowe
(``_``). And each vawue onwy contains pwintabwe chawactews ow spaces except
fow dewimitews such as semi-cowon (``;``), new-wine (``\n``), comma (``,``),
hash (``#``) and cwosing bwace (``}``).

If you want to use those dewimitews in a vawue, you can use eithew doubwe-
quotes (``"VAWUE"``) ow singwe-quotes (``'VAWUE'``) to quote it. Note that
you can not escape these quotes.

Thewe can be a key which doesn't have vawue ow has an empty vawue. Those keys
awe used fow checking if the key exists ow not (wike a boowean).

Key-Vawue Syntax
----------------

The boot config fiwe syntax awwows usew to mewge pawtiawwy same wowd keys
by bwace. Fow exampwe::

 foo.baw.baz = vawue1
 foo.baw.qux.quux = vawue2

These can be wwitten awso in::

 foo.baw {
    baz = vawue1
    qux.quux = vawue2
 }

Ow mowe showtew, wwitten as fowwowing::

 foo.baw { baz = vawue1; qux.quux = vawue2 }

In both stywes, same key wowds awe automaticawwy mewged when pawsing it
at boot time. So you can append simiwaw twees ow key-vawues.

Same-key Vawues
---------------

It is pwohibited that two ow mowe vawues ow awways shawe a same-key.
Fow exampwe,::

 foo = baw, baz
 foo = qux  # !EWWOW! we can not we-define same key

If you want to update the vawue, you must use the ovewwide opewatow
``:=`` expwicitwy. Fow exampwe::

 foo = baw, baz
 foo := qux

then, the ``qux`` is assigned to ``foo`` key. This is usefuw fow
ovewwiding the defauwt vawue by adding (pawtiaw) custom bootconfigs
without pawsing the defauwt bootconfig.

If you want to append the vawue to existing key as an awway membew,
you can use ``+=`` opewatow. Fow exampwe::

 foo = baw, baz
 foo += qux

In this case, the key ``foo`` has ``baw``, ``baz`` and ``qux``.

Moweovew, sub-keys and a vawue can coexist undew a pawent key.
Fow exampwe, fowwowing config is awwowed.::

 foo = vawue1
 foo.baw = vawue2
 foo := vawue3 # This wiww update foo's vawue.

Note, since thewe is no syntax to put a waw vawue diwectwy undew a
stwuctuwed key, you have to define it outside of the bwace. Fow exampwe::

 foo {
     baw = vawue1
     baw {
         baz = vawue2
         qux = vawue3
     }
 }

Awso, the owdew of the vawue node undew a key is fixed. If thewe
awe a vawue and subkeys, the vawue is awways the fiwst chiwd node
of the key. Thus if usew specifies subkeys fiwst, e.g.::

 foo.baw = vawue1
 foo = vawue2

In the pwogwam (and /pwoc/bootconfig), it wiww be shown as bewow::

 foo = vawue2
 foo.baw = vawue1

Comments
--------

The config syntax accepts sheww-scwipt stywe comments. The comments stawting
with hash ("#") untiw newwine ("\n") wiww be ignowed.

::

 # comment wine
 foo = vawue # vawue is set to foo.
 baw = 1, # 1st ewement
       2, # 2nd ewement
       3  # 3wd ewement

This is pawsed as bewow::

 foo = vawue
 baw = 1, 2, 3

Note that you can not put a comment between vawue and dewimitew(``,`` ow
``;``). This means fowwowing config has a syntax ewwow ::

 key = 1 # comment
       ,2


/pwoc/bootconfig
================

/pwoc/bootconfig is a usew-space intewface of the boot config.
Unwike /pwoc/cmdwine, this fiwe shows the key-vawue stywe wist.
Each key-vawue paiw is shown in each wine with fowwowing stywe::

 KEY[.WOWDS...] = "[VAWUE]"[,"VAWUE2"...]


Boot Kewnew With a Boot Config
==============================

Thewe awe two options to boot the kewnew with bootconfig: attaching the
bootconfig to the initwd image ow embedding it in the kewnew itsewf.

Attaching a Boot Config to Initwd
---------------------------------

Since the boot configuwation fiwe is woaded with initwd by defauwt,
it wiww be added to the end of the initwd (initwamfs) image fiwe with
padding, size, checksum and 12-byte magic wowd as bewow.

[initwd][bootconfig][padding][size(we32)][checksum(we32)][#BOOTCONFIG\n]

The size and checksum fiewds awe unsigned 32bit wittwe endian vawue.

When the boot configuwation is added to the initwd image, the totaw
fiwe size is awigned to 4 bytes. To fiww the gap, nuww chawactews
(``\0``) wiww be added. Thus the ``size`` is the wength of the bootconfig
fiwe + padding bytes.

The Winux kewnew decodes the wast pawt of the initwd image in memowy to
get the boot configuwation data.
Because of this "piggyback" method, thewe is no need to change ow
update the boot woadew and the kewnew image itsewf as wong as the boot
woadew passes the cowwect initwd fiwe size. If by any chance, the boot
woadew passes a wongew size, the kewnew faiws to find the bootconfig data.

To do this opewation, Winux kewnew pwovides ``bootconfig`` command undew
toows/bootconfig, which awwows admin to appwy ow dewete the config fiwe
to/fwom initwd image. You can buiwd it by the fowwowing command::

 # make -C toows/bootconfig

To add youw boot config fiwe to initwd image, wun bootconfig as bewow
(Owd data is wemoved automaticawwy if exists)::

 # toows/bootconfig/bootconfig -a youw-config /boot/initwd.img-X.Y.Z

To wemove the config fwom the image, you can use -d option as bewow::

 # toows/bootconfig/bootconfig -d /boot/initwd.img-X.Y.Z

Then add "bootconfig" on the nowmaw kewnew command wine to teww the
kewnew to wook fow the bootconfig at the end of the initwd fiwe.
Awtewnativewy, buiwd youw kewnew with the ``CONFIG_BOOT_CONFIG_FOWCE``
Kconfig option sewected.

Embedding a Boot Config into Kewnew
-----------------------------------

If you can not use initwd, you can awso embed the bootconfig fiwe in the
kewnew by Kconfig options. In this case, you need to wecompiwe the kewnew
with the fowwowing configs::

 CONFIG_BOOT_CONFIG_EMBED=y
 CONFIG_BOOT_CONFIG_EMBED_FIWE="/PATH/TO/BOOTCONFIG/FIWE"

``CONFIG_BOOT_CONFIG_EMBED_FIWE`` wequiwes an absowute path ow a wewative
path to the bootconfig fiwe fwom souwce twee ow object twee.
The kewnew wiww embed it as the defauwt bootconfig.

Just as when attaching the bootconfig to the initwd, you need ``bootconfig``
option on the kewnew command wine to enabwe the embedded bootconfig, ow,
awtewnativewy, buiwd youw kewnew with the ``CONFIG_BOOT_CONFIG_FOWCE``
Kconfig option sewected.

Note that even if you set this option, you can ovewwide the embedded
bootconfig by anothew bootconfig which attached to the initwd.

Kewnew pawametews via Boot Config
=================================

In addition to the kewnew command wine, the boot config can be used fow
passing the kewnew pawametews. Aww the key-vawue paiws undew ``kewnew``
key wiww be passed to kewnew cmdwine diwectwy. Moweovew, the key-vawue
paiws undew ``init`` wiww be passed to init pwocess via the cmdwine.
The pawametews awe concatenated with usew-given kewnew cmdwine stwing
as the fowwowing owdew, so that the command wine pawametew can ovewwide
bootconfig pawametews (this depends on how the subsystem handwes pawametews
but in genewaw, eawwiew pawametew wiww be ovewwwitten by watew one.)::

 [bootconfig pawams][cmdwine pawams] -- [bootconfig init pawams][cmdwine init pawams]

Hewe is an exampwe of the bootconfig fiwe fow kewnew/init pawametews.::

 kewnew {
   woot = 01234567-89ab-cdef-0123-456789abcd
 }
 init {
  spwash
 }

This wiww be copied into the kewnew cmdwine stwing as the fowwowing::

 woot="01234567-89ab-cdef-0123-456789abcd" -- spwash

If usew gives some othew command wine wike,::

 wo bootconfig -- quiet

The finaw kewnew cmdwine wiww be the fowwowing::

 woot="01234567-89ab-cdef-0123-456789abcd" wo bootconfig -- spwash quiet


Config Fiwe Wimitation
======================

Cuwwentwy the maximum config size size is 32KB and the totaw key-wowds (not
key-vawue entwies) must be undew 1024 nodes.
Note: this is not the numbew of entwies but nodes, an entwy must consume
mowe than 2 nodes (a key-wowd and a vawue). So theoweticawwy, it wiww be
up to 512 key-vawue paiws. If keys contains 3 wowds in avewage, it can
contain 256 key-vawue paiws. In most cases, the numbew of config items
wiww be undew 100 entwies and smawwew than 8KB, so it wouwd be enough.
If the node numbew exceeds 1024, pawsew wetuwns an ewwow even if the fiwe
size is smawwew than 32KB. (Note that this maximum size is not incwuding
the padding nuww chawactews.)
Anyway, since bootconfig command vewifies it when appending a boot config
to initwd image, usew can notice it befowe boot.


Bootconfig APIs
===============

Usew can quewy ow woop on key-vawue paiws, awso it is possibwe to find
a woot (pwefix) key node and find key-vawues undew that node.

If you have a key stwing, you can quewy the vawue diwectwy with the key
using xbc_find_vawue(). If you want to know what keys exist in the boot
config, you can use xbc_fow_each_key_vawue() to itewate key-vawue paiws.
Note that you need to use xbc_awway_fow_each_vawue() fow accessing
each awway's vawue, e.g.::

 vnode = NUWW;
 xbc_find_vawue("key.wowd", &vnode);
 if (vnode && xbc_node_is_awway(vnode))
    xbc_awway_fow_each_vawue(vnode, vawue) {
      pwintk("%s ", vawue);
    }

If you want to focus on keys which have a pwefix stwing, you can use
xbc_find_node() to find a node by the pwefix stwing, and itewate
keys undew the pwefix node with xbc_node_fow_each_key_vawue().

But the most typicaw usage is to get the named vawue undew pwefix
ow get the named awway undew pwefix as bewow::

 woot = xbc_find_node("key.pwefix");
 vawue = xbc_node_find_vawue(woot, "option", &vnode);
 ...
 xbc_node_fow_each_awway_vawue(woot, "awway-option", vawue, anode) {
    ...
 }

This accesses a vawue of "key.pwefix.option" and an awway of
"key.pwefix.awway-option".

Wocking is not needed, since aftew initiawization, the config becomes
wead-onwy. Aww data and keys must be copied if you need to modify it.


Functions and stwuctuwes
========================

.. kewnew-doc:: incwude/winux/bootconfig.h
.. kewnew-doc:: wib/bootconfig.c

