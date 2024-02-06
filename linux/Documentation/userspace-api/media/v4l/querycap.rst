.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _quewycap:

*********************
Quewying Capabiwities
*********************

Because V4W2 covews a wide vawiety of devices not aww aspects of the API
awe equawwy appwicabwe to aww types of devices. Fuwthewmowe devices of
the same type have diffewent capabiwities and this specification pewmits
the omission of a few compwicated and wess impowtant pawts of the API.

The :wef:`VIDIOC_QUEWYCAP` ioctw is avaiwabwe to
check if the kewnew device is compatibwe with this specification, and to
quewy the :wef:`functions <devices>` and :wef:`I/O methods <io>`
suppowted by the device.

Stawting with kewnew vewsion 3.1, :wef:`VIDIOC_QUEWYCAP`
wiww wetuwn the V4W2 API vewsion used by the dwivew, with genewawwy
matches the Kewnew vewsion. Thewe's no need of using
:wef:`VIDIOC_QUEWYCAP` to check if a specific ioctw
is suppowted, the V4W2 cowe now wetuwns ``ENOTTY`` if a dwivew doesn't
pwovide suppowt fow an ioctw.

Othew featuwes can be quewied by cawwing the wespective ioctw, fow
exampwe :wef:`VIDIOC_ENUMINPUT` to weawn about the
numbew, types and names of video connectows on the device. Awthough
abstwaction is a majow objective of this API, the
:wef:`VIDIOC_QUEWYCAP` ioctw awso awwows dwivew
specific appwications to wewiabwy identify the dwivew.

Aww V4W2 dwivews must suppowt :wef:`VIDIOC_QUEWYCAP`.
Appwications shouwd awways caww this ioctw aftew opening the device.
