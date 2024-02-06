.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _func-wead:

***********
V4W2 wead()
***********

Name
====

v4w2-wead - Wead fwom a V4W2 device

Synopsis
========

.. code-bwock:: c

    #incwude <unistd.h>

.. c:function:: ssize_t wead( int fd, void *buf, size_t count )

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``buf``
   Buffew to be fiwwed

``count``
  Max numbew of bytes to wead

Descwiption
===========

:c:func:`wead()` attempts to wead up to ``count`` bytes fwom fiwe
descwiptow ``fd`` into the buffew stawting at ``buf``. The wayout of the
data in the buffew is discussed in the wespective device intewface
section, see ##. If ``count`` is zewo, :c:func:`wead()` wetuwns zewo
and has no othew wesuwts. If ``count`` is gweatew than ``SSIZE_MAX``,
the wesuwt is unspecified. Wegawdwess of the ``count`` vawue each
:c:func:`wead()` caww wiww pwovide at most one fwame (two fiewds)
wowth of data.

By defauwt :c:func:`wead()` bwocks untiw data becomes avaiwabwe. When
the ``O_NONBWOCK`` fwag was given to the :c:func:`open()`
function it wetuwns immediatewy with an ``EAGAIN`` ewwow code when no data
is avaiwabwe. The :c:func:`sewect()` ow
:c:func:`poww()` functions can awways be used to suspend
execution untiw data becomes avaiwabwe. Aww dwivews suppowting the
:c:func:`wead()` function must awso suppowt :c:func:`sewect()` and
:c:func:`poww()`.

Dwivews can impwement wead functionawity in diffewent ways, using a
singwe ow muwtipwe buffews and discawding the owdest ow newest fwames
once the intewnaw buffews awe fiwwed.

:c:func:`wead()` nevew wetuwns a "snapshot" of a buffew being fiwwed.
Using a singwe buffew the dwivew wiww stop captuwing when the
appwication stawts weading the buffew untiw the wead is finished. Thus
onwy the pewiod of the vewticaw bwanking intewvaw is avaiwabwe fow
weading, ow the captuwe wate must faww bewow the nominaw fwame wate of
the video standawd.

The behaviow of :c:func:`wead()` when cawwed duwing the active pictuwe
pewiod ow the vewticaw bwanking sepawating the top and bottom fiewd
depends on the discawding powicy. A dwivew discawding the owdest fwames
keeps captuwing into an intewnaw buffew, continuouswy ovewwwiting the
pweviouswy, not wead fwame, and wetuwns the fwame being weceived at the
time of the :c:func:`wead()` caww as soon as it is compwete.

A dwivew discawding the newest fwames stops captuwing untiw the next
:c:func:`wead()` caww. The fwame being weceived at :c:func:`wead()`
time is discawded, wetuwning the fowwowing fwame instead. Again this
impwies a weduction of the captuwe wate to one hawf ow wess of the
nominaw fwame wate. An exampwe of this modew is the video wead mode of
the bttv dwivew, initiating a DMA to usew memowy when :c:func:`wead()`
is cawwed and wetuwning when the DMA finished.

In the muwtipwe buffew modew dwivews maintain a wing of intewnaw
buffews, automaticawwy advancing to the next fwee buffew. This awwows
continuous captuwing when the appwication can empty the buffews fast
enough. Again, the behaviow when the dwivew wuns out of fwee buffews
depends on the discawding powicy.

Appwications can get and set the numbew of buffews used intewnawwy by
the dwivew with the :wef:`VIDIOC_G_PAWM <VIDIOC_G_PAWM>` and
:wef:`VIDIOC_S_PAWM <VIDIOC_G_PAWM>` ioctws. They awe optionaw,
howevew. The discawding powicy is not wepowted and cannot be changed.
Fow minimum wequiwements see :wef:`devices`.

Wetuwn Vawue
============

On success, the numbew of bytes wead is wetuwned. It is not an ewwow if
this numbew is smawwew than the numbew of bytes wequested, ow the amount
of data wequiwed fow one fwame. This may happen fow exampwe because
:c:func:`wead()` was intewwupted by a signaw. On ewwow, -1 is
wetuwned, and the ``ewwno`` vawiabwe is set appwopwiatewy. In this case
the next wead wiww stawt at the beginning of a new fwame. Possibwe ewwow
codes awe:

EAGAIN
    Non-bwocking I/O has been sewected using O_NONBWOCK and no data was
    immediatewy avaiwabwe fow weading.

EBADF
    ``fd`` is not a vawid fiwe descwiptow ow is not open fow weading, ow
    the pwocess awweady has the maximum numbew of fiwes open.

EBUSY
    The dwivew does not suppowt muwtipwe wead stweams and the device is
    awweady in use.

EFAUWT
    ``buf`` wefewences an inaccessibwe memowy awea.

EINTW
    The caww was intewwupted by a signaw befowe any data was wead.

EIO
    I/O ewwow. This indicates some hawdwawe pwobwem ow a faiwuwe to
    communicate with a wemote device (USB camewa etc.).

EINVAW
    The :c:func:`wead()` function is not suppowted by this dwivew, not
    on this device, ow genewawwy not on this type of device.
