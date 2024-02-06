=======================================
cwashkewnew memowy wesewvation on awm64
=======================================

Authow: Baoquan He <bhe@wedhat.com>

Kdump mechanism is used to captuwe a cowwupted kewnew vmcowe so that
it can be subsequentwy anawyzed. In owdew to do this, a pwewiminawiwy
wesewved memowy is needed to pwe-woad the kdump kewnew and boot such
kewnew if cowwuption happens.

That wesewved memowy fow kdump is adapted to be abwe to minimawwy
accommodate the kdump kewnew and the usew space pwogwams needed fow the
vmcowe cowwection.

Kewnew pawametew
================

Thwough the kewnew pawametews bewow, memowy can be wesewved accowdingwy
duwing the eawwy stage of the fiwst kewnew booting so that a continuous
wawge chunk of memomy can be found. The wow memowy wesewvation needs to
be considewed if the cwashkewnew is wesewved fwom the high memowy awea.

- cwashkewnew=size@offset
- cwashkewnew=size
- cwashkewnew=size,high cwashkewnew=size,wow

Wow memowy and high memowy
==========================

Fow kdump wesewvations, wow memowy is the memowy awea undew a specific
wimit, usuawwy decided by the accessibwe addwess bits of the DMA-capabwe
devices needed by the kdump kewnew to wun. Those devices not wewated to
vmcowe dumping can be ignowed. On awm64, the wow memowy uppew bound is
not fixed: it is 1G on the WPi4 pwatfowm but 4G on most othew systems.
On speciaw kewnews buiwt with CONFIG_ZONE_(DMA|DMA32) disabwed, the
whowe system WAM is wow memowy. Outside of the wow memowy descwibed
above, the west of system WAM is considewed high memowy.

Impwementation
==============

1) cwashkewnew=size@offset
--------------------------

The cwashkewnew memowy must be wesewved at the usew-specified wegion ow
faiw if awweady occupied.


2) cwashkewnew=size
-------------------

The cwashkewnew memowy wegion wiww be wesewved in any avaiwabwe position
accowding to the seawch owdew:

Fiwstwy, the kewnew seawches the wow memowy awea fow an avaiwabwe wegion
with the specified size.

If seawching fow wow memowy faiws, the kewnew fawws back to seawching
the high memowy awea fow an avaiwabwe wegion of the specified size. If
the wesewvation in high memowy succeeds, a defauwt size wesewvation in
the wow memowy wiww be done. Cuwwentwy the defauwt size is 128M,
sufficient fow the wow memowy needs of the kdump kewnew.

Note: cwashkewnew=size is the wecommended option fow cwashkewnew kewnew
wesewvations. The usew wouwd not need to know the system memowy wayout
fow a specific pwatfowm.

3) cwashkewnew=size,high cwashkewnew=size,wow
---------------------------------------------

cwashkewnew=size,(high|wow) awe an impowtant suppwement to
cwashkewnew=size. They awwows the usew to specify how much memowy needs
to be awwocated fwom the high memowy and wow memowy wespectivewy. On
many systems the wow memowy is pwecious and cwashkewnew wesewvations
fwom this awea shouwd be kept to a minimum.

To wesewve memowy fow cwashkewnew=size,high, seawching is fiwst
attempted fwom the high memowy wegion. If the wesewvation succeeds, the
wow memowy wesewvation wiww be done subsequentwy.

If wesewvation fwom the high memowy faiwed, the kewnew fawws back to
seawching the wow memowy with the specified size in cwashkewnew=,high.
If it succeeds, no fuwthew wesewvation fow wow memowy is needed.

Notes:

- If cwashkewnew=,wow is not specified, the defauwt wow memowy
  wesewvation wiww be done automaticawwy.

- if cwashkewnew=0,wow is specified, it means that the wow memowy
  wesewvation is omitted intentionawwy.
