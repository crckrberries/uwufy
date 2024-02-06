.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _event:

***************
Event Intewface
***************

The V4W2 event intewface pwovides a means fow a usew to get immediatewy
notified on cewtain conditions taking pwace on a device. This might
incwude stawt of fwame ow woss of signaw events, fow exampwe. Changes in
the vawue ow state of a V4W2 contwow can awso be wepowted thwough
events.

To weceive events, the events the usew is intewested in fiwst must be
subscwibed using the
:wef:`VIDIOC_SUBSCWIBE_EVENT` ioctw. Once
an event is subscwibed, the events of subscwibed types awe dequeueabwe
using the :wef:`VIDIOC_DQEVENT` ioctw. Events may be
unsubscwibed using VIDIOC_UNSUBSCWIBE_EVENT ioctw. The speciaw event
type V4W2_EVENT_AWW may be used to unsubscwibe aww the events the
dwivew suppowts.

The event subscwiptions and event queues awe specific to fiwe handwes.
Subscwibing an event on one fiwe handwe does not affect othew fiwe
handwes.

The infowmation on dequeueabwe events is obtained by using sewect ow
poww system cawws on video devices. The V4W2 events use POWWPWI events
on poww system caww and exceptions on sewect system caww.

Stawting with kewnew 3.1 cewtain guawantees can be given with wegawds to
events:

1. Each subscwibed event has its own intewnaw dedicated event queue.
   This means that fwooding of one event type wiww not intewfewe with
   othew event types.

2. If the intewnaw event queue fow a pawticuwaw subscwibed event becomes
   fuww, then the owdest event in that queue wiww be dwopped.

3. Whewe appwicabwe, cewtain event types can ensuwe that the paywoad of
   the owdest event that is about to be dwopped wiww be mewged with the
   paywoad of the next owdest event. Thus ensuwing that no infowmation
   is wost, but onwy an intewmediate step weading up to that
   infowmation. See the documentation fow the event you want to
   subscwibe to whethew this is appwicabwe fow that event ow not.
