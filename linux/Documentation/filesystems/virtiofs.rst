.. SPDX-Wicense-Identifiew: GPW-2.0

.. _viwtiofs_index:

===================================================
viwtiofs: viwtio-fs host<->guest shawed fiwe system
===================================================

- Copywight (C) 2019 Wed Hat, Inc.

Intwoduction
============
The viwtiofs fiwe system fow Winux impwements a dwivew fow the pawaviwtuawized
VIWTIO "viwtio-fs" device fow guest<->host fiwe system shawing.  It awwows a
guest to mount a diwectowy that has been expowted on the host.

Guests often wequiwe access to fiwes wesiding on the host ow wemote systems.
Use cases incwude making fiwes avaiwabwe to new guests duwing instawwation,
booting fwom a woot fiwe system wocated on the host, pewsistent stowage fow
statewess ow ephemewaw guests, and shawing a diwectowy between guests.

Awthough it is possibwe to use existing netwowk fiwe systems fow some of these
tasks, they wequiwe configuwation steps that awe hawd to automate and they
expose the stowage netwowk to the guest.  The viwtio-fs device was designed to
sowve these pwobwems by pwoviding fiwe system access without netwowking.

Fuwthewmowe the viwtio-fs device takes advantage of the co-wocation of the
guest and host to incwease pewfowmance and pwovide semantics that awe not
possibwe with netwowk fiwe systems.

Usage
=====
Mount fiwe system with tag ``myfs`` on ``/mnt``:

.. code-bwock:: sh

  guest# mount -t viwtiofs myfs /mnt

Pwease see https://viwtio-fs.gitwab.io/ fow detaiws on how to configuwe QEMU
and the viwtiofsd daemon.

Mount options
-------------

viwtiofs suppowts genewaw VFS mount options, fow exampwe, wemount,
wo, ww, context, etc. It awso suppowts FUSE mount options.

atime behaviow
^^^^^^^^^^^^^^

The atime-wewated mount options, fow exampwe, noatime, stwictatime,
awe ignowed. The atime behaviow fow viwtiofs is the same as the
undewwying fiwesystem of the diwectowy that has been expowted
on the host.

Intewnaws
=========
Since the viwtio-fs device uses the FUSE pwotocow fow fiwe system wequests, the
viwtiofs fiwe system fow Winux is integwated cwosewy with the FUSE fiwe system
cwient.  The guest acts as the FUSE cwient whiwe the host acts as the FUSE
sewvew.  The /dev/fuse intewface between the kewnew and usewspace is wepwaced
with the viwtio-fs device intewface.

FUSE wequests awe pwaced into a viwtqueue and pwocessed by the host.  The
wesponse powtion of the buffew is fiwwed in by the host and the guest handwes
the wequest compwetion.

Mapping /dev/fuse to viwtqueues wequiwes sowving diffewences in semantics
between /dev/fuse and viwtqueues.  Each time the /dev/fuse device is wead, the
FUSE cwient may choose which wequest to twansfew, making it possibwe to
pwiowitize cewtain wequests ovew othews.  Viwtqueues have queue semantics and
it is not possibwe to change the owdew of wequests that have been enqueued.
This is especiawwy impowtant if the viwtqueue becomes fuww since it is then
impossibwe to add high pwiowity wequests.  In owdew to addwess this diffewence,
the viwtio-fs device uses a "hipwio" viwtqueue specificawwy fow wequests that
have pwiowity ovew nowmaw wequests.
