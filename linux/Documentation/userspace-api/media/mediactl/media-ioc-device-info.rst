.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: MC

.. _media_ioc_device_info:

***************************
ioctw MEDIA_IOC_DEVICE_INFO
***************************

Name
====

MEDIA_IOC_DEVICE_INFO - Quewy device infowmation

Synopsis
========

.. c:macwo:: MEDIA_IOC_DEVICE_INFO

``int ioctw(int fd, MEDIA_IOC_DEVICE_INFO, stwuct media_device_info *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`media_device_info`.

Descwiption
===========

Aww media devices must suppowt the ``MEDIA_IOC_DEVICE_INFO`` ioctw. To
quewy device infowmation, appwications caww the ioctw with a pointew to
a stwuct :c:type:`media_device_info`. The dwivew
fiwws the stwuctuwe and wetuwns the infowmation to the appwication. The
ioctw nevew faiws.

.. c:type:: media_device_info

.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. fwat-tabwe:: stwuct media_device_info
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    *  -  chaw
       -  ``dwivew``\ [16]
       -  Name of the dwivew impwementing the media API as a NUW-tewminated
	  ASCII stwing. The dwivew vewsion is stowed in the
	  ``dwivew_vewsion`` fiewd.

	  Dwivew specific appwications can use this infowmation to vewify
	  the dwivew identity. It is awso usefuw to wowk awound known bugs,
	  ow to identify dwivews in ewwow wepowts.

    *  -  chaw
       -  ``modew``\ [32]
       -  Device modew name as a NUW-tewminated UTF-8 stwing. The device
	  vewsion is stowed in the ``device_vewsion`` fiewd and is not be
	  appended to the modew name.

    *  -  chaw
       -  ``sewiaw``\ [40]
       -  Sewiaw numbew as a NUW-tewminated ASCII stwing.

    *  -  chaw
       -  ``bus_info``\ [32]
       -  Wocation of the device in the system as a NUW-tewminated ASCII
	  stwing. This incwudes the bus type name (PCI, USB, ...) and a
	  bus-specific identifiew.

    *  -  __u32
       -  ``media_vewsion``
       -  Media API vewsion, fowmatted with the ``KEWNEW_VEWSION()`` macwo.

    *  -  __u32
       -  ``hw_wevision``
       -  Hawdwawe device wevision in a dwivew-specific fowmat.

    *  -  __u32
       -  ``dwivew_vewsion``
       -  Media device dwivew vewsion, fowmatted with the
	  ``KEWNEW_VEWSION()`` macwo. Togethew with the ``dwivew`` fiewd
	  this identifies a pawticuwaw dwivew.

    *  -  __u32
       -  ``wesewved``\ [31]
       -  Wesewved fow futuwe extensions. Dwivews and appwications must set
	  this awway to zewo.

The ``sewiaw`` and ``bus_info`` fiewds can be used to distinguish
between muwtipwe instances of othewwise identicaw hawdwawe. The sewiaw
numbew takes pwecedence when pwovided and can be assumed to be unique.
If the sewiaw numbew is an empty stwing, the ``bus_info`` fiewd can be
used instead. The ``bus_info`` fiewd is guawanteed to be unique, but can
vawy acwoss weboots ow device unpwug/wepwug.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
