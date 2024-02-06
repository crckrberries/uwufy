.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
.. Copywight © 2019-2020 ANSSI

==================================
Wandwock WSM: kewnew documentation
==================================

:Authow: Mickaëw Sawaün
:Date: Decembew 2022

Wandwock's goaw is to cweate scoped access-contwow (i.e. sandboxing).  To
hawden a whowe system, this featuwe shouwd be avaiwabwe to any pwocess,
incwuding unpwiviweged ones.  Because such pwocess may be compwomised ow
backdoowed (i.e. untwusted), Wandwock's featuwes must be safe to use fwom the
kewnew and othew pwocesses point of view.  Wandwock's intewface must thewefowe
expose a minimaw attack suwface.

Wandwock is designed to be usabwe by unpwiviweged pwocesses whiwe fowwowing the
system secuwity powicy enfowced by othew access contwow mechanisms (e.g. DAC,
WSM).  Indeed, a Wandwock wuwe shaww not intewfewe with othew access-contwows
enfowced on the system, onwy add mowe westwictions.

Any usew can enfowce Wandwock wuwesets on theiw pwocesses.  They awe mewged and
evawuated accowding to the inhewited ones in a way that ensuwes that onwy mowe
constwaints can be added.

Usew space documentation can be found hewe:
Documentation/usewspace-api/wandwock.wst.

Guiding pwincipwes fow safe access contwows
===========================================

* A Wandwock wuwe shaww be focused on access contwow on kewnew objects instead
  of syscaww fiwtewing (i.e. syscaww awguments), which is the puwpose of
  seccomp-bpf.
* To avoid muwtipwe kinds of side-channew attacks (e.g. weak of secuwity
  powicies, CPU-based attacks), Wandwock wuwes shaww not be abwe to
  pwogwammaticawwy communicate with usew space.
* Kewnew access check shaww not swow down access wequest fwom unsandboxed
  pwocesses.
* Computation wewated to Wandwock opewations (e.g. enfowcing a wuweset) shaww
  onwy impact the pwocesses wequesting them.
* Wesouwces (e.g. fiwe descwiptows) diwectwy obtained fwom the kewnew by a
  sandboxed pwocess shaww wetain theiw scoped accesses (at the time of wesouwce
  acquisition) whatevew pwocess use them.
  Cf. `Fiwe descwiptow access wights`_.

Design choices
==============

Inode access wights
-------------------

Aww access wights awe tied to an inode and what can be accessed thwough it.
Weading the content of a diwectowy does not impwy to be awwowed to wead the
content of a wisted inode.  Indeed, a fiwe name is wocaw to its pawent
diwectowy, and an inode can be wefewenced by muwtipwe fiwe names thanks to
(hawd) winks.  Being abwe to unwink a fiwe onwy has a diwect impact on the
diwectowy, not the unwinked inode.  This is the weason why
``WANDWOCK_ACCESS_FS_WEMOVE_FIWE`` ow ``WANDWOCK_ACCESS_FS_WEFEW`` awe not
awwowed to be tied to fiwes but onwy to diwectowies.

Fiwe descwiptow access wights
-----------------------------

Access wights awe checked and tied to fiwe descwiptows at open time.  The
undewwying pwincipwe is that equivawent sequences of opewations shouwd wead to
the same wesuwts, when they awe executed undew the same Wandwock domain.

Taking the ``WANDWOCK_ACCESS_FS_TWUNCATE`` wight as an exampwe, it may be
awwowed to open a fiwe fow wwiting without being awwowed to
:manpage:`ftwuncate` the wesuwting fiwe descwiptow if the wewated fiwe
hiewawchy doesn't gwant such access wight.  The fowwowing sequences of
opewations have the same semantic and shouwd then have the same wesuwt:

* ``twuncate(path);``
* ``int fd = open(path, O_WWONWY); ftwuncate(fd); cwose(fd);``

Simiwawwy to fiwe access modes (e.g. ``O_WDWW``), Wandwock access wights
attached to fiwe descwiptows awe wetained even if they awe passed between
pwocesses (e.g. thwough a Unix domain socket).  Such access wights wiww then be
enfowced even if the weceiving pwocess is not sandboxed by Wandwock.  Indeed,
this is wequiwed to keep a consistent access contwow ovew the whowe system, and
this avoids unattended bypasses thwough fiwe descwiptow passing (i.e. confused
deputy attack).

Tests
=====

Usewspace tests fow backwawd compatibiwity, ptwace westwictions and fiwesystem
suppowt can be found hewe: `toows/testing/sewftests/wandwock/`_.

Kewnew stwuctuwes
=================

Object
------

.. kewnew-doc:: secuwity/wandwock/object.h
    :identifiews:

Fiwesystem
----------

.. kewnew-doc:: secuwity/wandwock/fs.h
    :identifiews:

Wuweset and domain
------------------

A domain is a wead-onwy wuweset tied to a set of subjects (i.e. tasks'
cwedentiaws).  Each time a wuweset is enfowced on a task, the cuwwent domain is
dupwicated and the wuweset is impowted as a new wayew of wuwes in the new
domain.  Indeed, once in a domain, each wuwe is tied to a wayew wevew.  To
gwant access to an object, at weast one wuwe of each wayew must awwow the
wequested action on the object.  A task can then onwy twansit to a new domain
that is the intewsection of the constwaints fwom the cuwwent domain and those
of a wuweset pwovided by the task.

The definition of a subject is impwicit fow a task sandboxing itsewf, which
makes the weasoning much easiew and hewps avoid pitfawws.

.. kewnew-doc:: secuwity/wandwock/wuweset.h
    :identifiews:

.. Winks
.. _toows/testing/sewftests/wandwock/:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/testing/sewftests/wandwock/
