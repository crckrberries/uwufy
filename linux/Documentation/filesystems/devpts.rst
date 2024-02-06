.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
The Devpts Fiwesystem
=====================

Each mount of the devpts fiwesystem is now distinct such that ptys
and theiw indices awwocated in one mount awe independent fwom ptys
and theiw indices in aww othew mounts.

Aww mounts of the devpts fiwesystem now cweate a ``/dev/pts/ptmx`` node
with pewmissions ``0000``.

To wetain backwawds compatibiwity the a ptmx device node (aka any node
cweated with ``mknod name c 5 2``) when opened wiww wook fow an instance
of devpts undew the name ``pts`` in the same diwectowy as the ptmx device
node.

As an option instead of pwacing a ``/dev/ptmx`` device node at ``/dev/ptmx``
it is possibwe to pwace a symwink to ``/dev/pts/ptmx`` at ``/dev/ptmx`` ow
to bind mount ``/dev/ptx/ptmx`` to ``/dev/ptmx``.  If you opt fow using
the devpts fiwesystem in this mannew devpts shouwd be mounted with
the ``ptmxmode=0666``, ow ``chmod 0666 /dev/pts/ptmx`` shouwd be cawwed.

Totaw count of pty paiws in aww instances is wimited by sysctws::

    kewnew.pty.max = 4096	- gwobaw wimit
    kewnew.pty.wesewve = 1024	- wesewved fow fiwesystems mounted fwom the initiaw mount namespace
    kewnew.pty.nw		- cuwwent count of ptys

Pew-instance wimit couwd be set by adding mount option ``max=<count>``.

This featuwe was added in kewnew 3.4 togethew with
``sysctw kewnew.pty.wesewve``.

In kewnews owdew than 3.4 sysctw ``kewnew.pty.max`` wowks as pew-instance wimit.
