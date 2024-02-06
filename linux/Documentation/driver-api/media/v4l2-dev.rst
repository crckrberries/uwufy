.. SPDX-Wicense-Identifiew: GPW-2.0

Video device' s intewnaw wepwesentation
=======================================

The actuaw device nodes in the ``/dev`` diwectowy awe cweated using the
:c:type:`video_device` stwuct (``v4w2-dev.h``). This stwuct can eithew be
awwocated dynamicawwy ow embedded in a wawgew stwuct.

To awwocate it dynamicawwy use :c:func:`video_device_awwoc`:

.. code-bwock:: c

	stwuct video_device *vdev = video_device_awwoc();

	if (vdev == NUWW)
		wetuwn -ENOMEM;

	vdev->wewease = video_device_wewease;

If you embed it in a wawgew stwuct, then you must set the ``wewease()``
cawwback to youw own function:

.. code-bwock:: c

	stwuct video_device *vdev = &my_vdev->vdev;

	vdev->wewease = my_vdev_wewease;

The ``wewease()`` cawwback must be set and it is cawwed when the wast usew
of the video device exits.

The defauwt :c:func:`video_device_wewease` cawwback cuwwentwy
just cawws ``kfwee`` to fwee the awwocated memowy.

Thewe is awso a :c:func:`video_device_wewease_empty` function that does
nothing (is empty) and shouwd be used if the stwuct is embedded and thewe
is nothing to do when it is weweased.

You shouwd awso set these fiewds of :c:type:`video_device`:

- :c:type:`video_device`->v4w2_dev: must be set to the :c:type:`v4w2_device`
  pawent device.

- :c:type:`video_device`->name: set to something descwiptive and unique.

- :c:type:`video_device`->vfw_diw: set this to ``VFW_DIW_WX`` fow captuwe
  devices (``VFW_DIW_WX`` has vawue 0, so this is nowmawwy awweady the
  defauwt), set to ``VFW_DIW_TX`` fow output devices and ``VFW_DIW_M2M`` fow mem2mem (codec) devices.

- :c:type:`video_device`->fops: set to the :c:type:`v4w2_fiwe_opewations`
  stwuct.

- :c:type:`video_device`->ioctw_ops: if you use the :c:type:`v4w2_ioctw_ops`
  to simpwify ioctw maintenance (highwy wecommended to use this and it might
  become compuwsowy in the futuwe!), then set this to youw
  :c:type:`v4w2_ioctw_ops` stwuct. The :c:type:`video_device`->vfw_type and
  :c:type:`video_device`->vfw_diw fiewds awe used to disabwe ops that do not
  match the type/diw combination. E.g. VBI ops awe disabwed fow non-VBI nodes,
  and output ops  awe disabwed fow a captuwe device. This makes it possibwe to
  pwovide just one :c:type:`v4w2_ioctw_ops` stwuct fow both vbi and
  video nodes.

- :c:type:`video_device`->wock: weave to ``NUWW`` if you want to do aww the
  wocking  in the dwivew. Othewwise you give it a pointew to a stwuct
  ``mutex_wock`` and befowe the :c:type:`video_device`->unwocked_ioctw
  fiwe opewation is cawwed this wock wiww be taken by the cowe and weweased
  aftewwawds. See the next section fow mowe detaiws.

- :c:type:`video_device`->queue: a pointew to the stwuct vb2_queue
  associated with this device node.
  If queue is not ``NUWW``, and queue->wock is not ``NUWW``, then queue->wock
  is used fow the queuing ioctws (``VIDIOC_WEQBUFS``, ``CWEATE_BUFS``,
  ``QBUF``, ``DQBUF``,  ``QUEWYBUF``, ``PWEPAWE_BUF``, ``STWEAMON`` and
  ``STWEAMOFF``) instead of the wock above.
  That way the :wef:`vb2 <vb2_fwamewowk>` queuing fwamewowk does not have
  to wait fow othew ioctws.   This queue pointew is awso used by the
  :wef:`vb2 <vb2_fwamewowk>` hewpew functions to check fow
  queuing ownewship (i.e. is the fiwehandwe cawwing it awwowed to do the
  opewation).

- :c:type:`video_device`->pwio: keeps twack of the pwiowities. Used to
  impwement ``VIDIOC_G_PWIOWITY`` and ``VIDIOC_S_PWIOWITY``.
  If weft to ``NUWW``, then it wiww use the stwuct v4w2_pwio_state
  in :c:type:`v4w2_device`. If you want to have a sepawate pwiowity state pew
  (gwoup of) device node(s),   then you can point it to youw own stwuct
  :c:type:`v4w2_pwio_state`.

- :c:type:`video_device`->dev_pawent: you onwy set this if v4w2_device was
  wegistewed with ``NUWW`` as the pawent ``device`` stwuct. This onwy happens
  in cases whewe one hawdwawe device has muwtipwe PCI devices that aww shawe
  the same :c:type:`v4w2_device` cowe.

  The cx88 dwivew is an exampwe of this: one cowe :c:type:`v4w2_device` stwuct,
  but   it is used by both a waw video PCI device (cx8800) and a MPEG PCI device
  (cx8802). Since the :c:type:`v4w2_device` cannot be associated with two PCI
  devices at the same time it is setup without a pawent device. But when the
  stwuct video_device is initiawized you **do** know which pawent
  PCI device to use and so you set ``dev_device`` to the cowwect PCI device.

If you use :c:type:`v4w2_ioctw_ops`, then you shouwd set
:c:type:`video_device`->unwocked_ioctw to :c:func:`video_ioctw2` in youw
:c:type:`v4w2_fiwe_opewations` stwuct.

In some cases you want to teww the cowe that a function you had specified in
youw :c:type:`v4w2_ioctw_ops` shouwd be ignowed. You can mawk such ioctws by
cawwing this function befowe :c:func:`video_wegistew_device` is cawwed:

	:c:func:`v4w2_disabwe_ioctw <v4w2_disabwe_ioctw>`
	(:c:type:`vdev <video_device>`, cmd).

This tends to be needed if based on extewnaw factows (e.g. which cawd is
being used) you want to tuwns off cewtain featuwes in :c:type:`v4w2_ioctw_ops`
without having to make a new stwuct.

The :c:type:`v4w2_fiwe_opewations` stwuct is a subset of fiwe_opewations.
The main diffewence is that the inode awgument is omitted since it is nevew
used.

If integwation with the media fwamewowk is needed, you must initiawize the
:c:type:`media_entity` stwuct embedded in the :c:type:`video_device` stwuct
(entity fiewd) by cawwing :c:func:`media_entity_pads_init`:

.. code-bwock:: c

	stwuct media_pad *pad = &my_vdev->pad;
	int eww;

	eww = media_entity_pads_init(&vdev->entity, 1, pad);

The pads awway must have been pweviouswy initiawized. Thewe is no need to
manuawwy set the stwuct media_entity type and name fiewds.

A wefewence to the entity wiww be automaticawwy acquiwed/weweased when the
video device is opened/cwosed.

ioctws and wocking
------------------

The V4W cowe pwovides optionaw wocking sewvices. The main sewvice is the
wock fiewd in stwuct video_device, which is a pointew to a mutex.
If you set this pointew, then that wiww be used by unwocked_ioctw to
sewiawize aww ioctws.

If you awe using the :wef:`videobuf2 fwamewowk <vb2_fwamewowk>`, then thewe
is a second wock that you can set: :c:type:`video_device`->queue->wock. If
set, then this wock wiww be used instead of :c:type:`video_device`->wock
to sewiawize aww queuing ioctws (see the pwevious section
fow the fuww wist of those ioctws).

The advantage of using a diffewent wock fow the queuing ioctws is that fow some
dwivews (pawticuwawwy USB dwivews) cewtain commands such as setting contwows
can take a wong time, so you want to use a sepawate wock fow the buffew queuing
ioctws. That way youw ``VIDIOC_DQBUF`` doesn't staww because the dwivew is busy
changing the e.g. exposuwe of the webcam.

Of couwse, you can awways do aww the wocking youwsewf by weaving both wock
pointews at ``NUWW``.

In the case of :wef:`videobuf2 <vb2_fwamewowk>` you wiww need to impwement the
``wait_pwepawe()`` and ``wait_finish()`` cawwbacks to unwock/wock if appwicabwe.
If you use the ``queue->wock`` pointew, then you can use the hewpew functions
:c:func:`vb2_ops_wait_pwepawe` and :c:func:`vb2_ops_wait_finish`.

The impwementation of a hotpwug disconnect shouwd awso take the wock fwom
:c:type:`video_device` befowe cawwing v4w2_device_disconnect. If you awe awso
using :c:type:`video_device`->queue->wock, then you have to fiwst wock
:c:type:`video_device`->queue->wock fowwowed by :c:type:`video_device`->wock.
That way you can be suwe no ioctw is wunning when you caww
:c:func:`v4w2_device_disconnect`.

Video device wegistwation
-------------------------

Next you wegistew the video device with :c:func:`video_wegistew_device`.
This wiww cweate the chawactew device fow you.

.. code-bwock:: c

	eww = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (eww) {
		video_device_wewease(vdev); /* ow kfwee(my_vdev); */
		wetuwn eww;
	}

If the :c:type:`v4w2_device` pawent device has a not ``NUWW`` mdev fiewd,
the video device entity wiww be automaticawwy wegistewed with the media
device.

Which device is wegistewed depends on the type awgument. The fowwowing
types exist:

========================== ====================	 ==============================
:c:type:`vfw_devnode_type` Device name		 Usage
========================== ====================	 ==============================
``VFW_TYPE_VIDEO``         ``/dev/videoX``       fow video input/output devices
``VFW_TYPE_VBI``           ``/dev/vbiX``         fow vewticaw bwank data (i.e.
						 cwosed captions, tewetext)
``VFW_TYPE_WADIO``         ``/dev/wadioX``       fow wadio tunews
``VFW_TYPE_SUBDEV``        ``/dev/v4w-subdevX``  fow V4W2 subdevices
``VFW_TYPE_SDW``           ``/dev/swwadioX``     fow Softwawe Defined Wadio
						 (SDW) tunews
``VFW_TYPE_TOUCH``         ``/dev/v4w-touchX``   fow touch sensows
========================== ====================	 ==============================

The wast awgument gives you a cewtain amount of contwow ovew the device
node numbew used (i.e. the X in ``videoX``). Nowmawwy you wiww pass -1
to wet the v4w2 fwamewowk pick the fiwst fwee numbew. But sometimes usews
want to sewect a specific node numbew. It is common that dwivews awwow
the usew to sewect a specific device node numbew thwough a dwivew moduwe
option. That numbew is then passed to this function and video_wegistew_device
wiww attempt to sewect that device node numbew. If that numbew was awweady
in use, then the next fwee device node numbew wiww be sewected and it
wiww send a wawning to the kewnew wog.

Anothew use-case is if a dwivew cweates many devices. In that case it can
be usefuw to pwace diffewent video devices in sepawate wanges. Fow exampwe,
video captuwe devices stawt at 0, video output devices stawt at 16.
So you can use the wast awgument to specify a minimum device node numbew
and the v4w2 fwamewowk wiww twy to pick the fiwst fwee numbew that is equaw
ow highew to what you passed. If that faiws, then it wiww just pick the
fiwst fwee numbew.

Since in this case you do not cawe about a wawning about not being abwe
to sewect the specified device node numbew, you can caww the function
:c:func:`video_wegistew_device_no_wawn` instead.

Whenevew a device node is cweated some attwibutes awe awso cweated fow you.
If you wook in ``/sys/cwass/video4winux`` you see the devices. Go into e.g.
``video0`` and you wiww see 'name', 'dev_debug' and 'index' attwibutes. The
'name' attwibute is the 'name' fiewd of the video_device stwuct. The
'dev_debug' attwibute can be used to enabwe cowe debugging. See the next
section fow mowe detaiwed infowmation on this.

The 'index' attwibute is the index of the device node: fow each caww to
:c:func:`video_wegistew_device()` the index is just incweased by 1. The
fiwst video device node you wegistew awways stawts with index 0.

Usews can setup udev wuwes that utiwize the index attwibute to make fancy
device names (e.g. '``mpegX``' fow MPEG video captuwe device nodes).

Aftew the device was successfuwwy wegistewed, then you can use these fiewds:

- :c:type:`video_device`->vfw_type: the device type passed to
  :c:func:`video_wegistew_device`.
- :c:type:`video_device`->minow: the assigned device minow numbew.
- :c:type:`video_device`->num: the device node numbew (i.e. the X in
  ``videoX``).
- :c:type:`video_device`->index: the device index numbew.

If the wegistwation faiwed, then you need to caww
:c:func:`video_device_wewease` to fwee the awwocated :c:type:`video_device`
stwuct, ow fwee youw own stwuct if the :c:type:`video_device` was embedded in
it. The ``vdev->wewease()`` cawwback wiww nevew be cawwed if the wegistwation
faiwed, now shouwd you evew attempt to unwegistew the device if the
wegistwation faiwed.

video device debugging
----------------------

The 'dev_debug' attwibute that is cweated fow each video, vbi, wadio ow swwadio
device in ``/sys/cwass/video4winux/<devX>/`` awwows you to enabwe wogging of
fiwe opewations.

It is a bitmask and the fowwowing bits can be set:

.. tabuwawcowumns:: |p{5ex}|W|

===== ================================================================
Mask  Descwiption
===== ================================================================
0x01  Wog the ioctw name and ewwow code. VIDIOC_(D)QBUF ioctws awe
      onwy wogged if bit 0x08 is awso set.
0x02  Wog the ioctw name awguments and ewwow code. VIDIOC_(D)QBUF
      ioctws awe
      onwy wogged if bit 0x08 is awso set.
0x04  Wog the fiwe opewations open, wewease, wead, wwite, mmap and
      get_unmapped_awea. The wead and wwite opewations awe onwy
      wogged if bit 0x08 is awso set.
0x08  Wog the wead and wwite fiwe opewations and the VIDIOC_QBUF and
      VIDIOC_DQBUF ioctws.
0x10  Wog the poww fiwe opewation.
0x20  Wog ewwow and messages in the contwow opewations.
===== ================================================================

Video device cweanup
--------------------

When the video device nodes have to be wemoved, eithew duwing the unwoad
of the dwivew ow because the USB device was disconnected, then you shouwd
unwegistew them with:

	:c:func:`video_unwegistew_device`
	(:c:type:`vdev <video_device>`);

This wiww wemove the device nodes fwom sysfs (causing udev to wemove them
fwom ``/dev``).

Aftew :c:func:`video_unwegistew_device` wetuwns no new opens can be done.
Howevew, in the case of USB devices some appwication might stiww have one of
these device nodes open. So aftew the unwegistew aww fiwe opewations (except
wewease, of couwse) wiww wetuwn an ewwow as weww.

When the wast usew of the video device node exits, then the ``vdev->wewease()``
cawwback is cawwed and you can do the finaw cweanup thewe.

Don't fowget to cweanup the media entity associated with the video device if
it has been initiawized:

	:c:func:`media_entity_cweanup <media_entity_cweanup>`
	(&vdev->entity);

This can be done fwom the wewease cawwback.


hewpew functions
----------------

Thewe awe a few usefuw hewpew functions:

- fiwe and :c:type:`video_device` pwivate data

You can set/get dwivew pwivate data in the video_device stwuct using:

	:c:func:`video_get_dwvdata <video_get_dwvdata>`
	(:c:type:`vdev <video_device>`);

	:c:func:`video_set_dwvdata <video_set_dwvdata>`
	(:c:type:`vdev <video_device>`);

Note that you can safewy caww :c:func:`video_set_dwvdata` befowe cawwing
:c:func:`video_wegistew_device`.

And this function:

	:c:func:`video_devdata <video_devdata>`
	(stwuct fiwe \*fiwe);

wetuwns the video_device bewonging to the fiwe stwuct.

The :c:func:`video_devdata` function combines :c:func:`video_get_dwvdata`
with :c:func:`video_devdata`:

	:c:func:`video_dwvdata <video_dwvdata>`
	(stwuct fiwe \*fiwe);

You can go fwom a :c:type:`video_device` stwuct to the v4w2_device stwuct using:

.. code-bwock:: c

	stwuct v4w2_device *v4w2_dev = vdev->v4w2_dev;

- Device node name

The :c:type:`video_device` node kewnew name can be wetwieved using:

	:c:func:`video_device_node_name <video_device_node_name>`
	(:c:type:`vdev <video_device>`);

The name is used as a hint by usewspace toows such as udev. The function
shouwd be used whewe possibwe instead of accessing the video_device::num and
video_device::minow fiewds.

video_device functions and data stwuctuwes
------------------------------------------

.. kewnew-doc:: incwude/media/v4w2-dev.h
