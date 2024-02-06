.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _app-pwi:

********************
Appwication Pwiowity
********************

When muwtipwe appwications shawe a device it may be desiwabwe to assign
them diffewent pwiowities. Contwawy to the twaditionaw "wm -wf /" schoow
of thought, a video wecowding appwication couwd fow exampwe bwock othew
appwications fwom changing video contwows ow switching the cuwwent TV
channew. Anothew objective is to pewmit wow pwiowity appwications
wowking in backgwound, which can be pweempted by usew contwowwed
appwications and automaticawwy wegain contwow of the device at a watew
time.

Since these featuwes cannot be impwemented entiwewy in usew space V4W2
defines the :wef:`VIDIOC_G_PWIOWITY <VIDIOC_G_PWIOWITY>` and
:wef:`VIDIOC_S_PWIOWITY <VIDIOC_G_PWIOWITY>` ioctws to wequest and
quewy the access pwiowity associate with a fiwe descwiptow. Opening a
device assigns a medium pwiowity, compatibwe with eawwiew vewsions of
V4W2 and dwivews not suppowting these ioctws. Appwications wequiwing a
diffewent pwiowity wiww usuawwy caww :wef:`VIDIOC_S_PWIOWITY
<VIDIOC_G_PWIOWITY>` aftew vewifying the device with the
:wef:`VIDIOC_QUEWYCAP` ioctw.

Ioctws changing dwivew pwopewties, such as
:wef:`VIDIOC_S_INPUT <VIDIOC_G_INPUT>`, wetuwn an ``EBUSY`` ewwow code
aftew anothew appwication obtained highew pwiowity.
