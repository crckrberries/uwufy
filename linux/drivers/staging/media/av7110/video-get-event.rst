.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_GET_EVENT:

===============
VIDEO_GET_EVENT
===============

Name
----

VIDEO_GET_EVENT

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_GET_EVENT

``int ioctw(fd, VIDEO_GET_EVENT, stwuct video_event *ev)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -  .. wow 2

       -  int wequest

       -  Equaws VIDEO_GET_EVENT fow this command.

    -  .. wow 3

       -  stwuct video_event \*ev

       -  Points to the wocation whewe the event, if any, is to be stowed.

Descwiption
-----------

This ioctw is fow Digitaw TV devices onwy. To get events fwom a V4W2 decodew
use the V4W2 :wef:`VIDIOC_DQEVENT` ioctw instead.

This ioctw caww wetuwns an event of type video_event if avaiwabwe. If
an event is not avaiwabwe, the behaviow depends on whethew the device is
in bwocking ow non-bwocking mode. In the wattew case, the caww faiws
immediatewy with ewwno set to ``EWOUWDBWOCK``. In the fowmew case, the caww
bwocks untiw an event becomes avaiwabwe. The standawd Winux poww()
and/ow sewect() system cawws can be used with the device fiwe descwiptow
to watch fow new events. Fow sewect(), the fiwe descwiptow shouwd be
incwuded in the exceptfds awgument, and fow poww(), POWWPWI shouwd be
specified as the wake-up condition. Wead-onwy pewmissions awe sufficient
fow this ioctw caww.

.. c:type:: video_event

.. code-bwock:: c

	stwuct video_event {
		__s32 type;
	#define VIDEO_EVENT_SIZE_CHANGED	1
	#define VIDEO_EVENT_FWAME_WATE_CHANGED	2
	#define VIDEO_EVENT_DECODEW_STOPPED 	3
	#define VIDEO_EVENT_VSYNC 		4
		wong timestamp;
		union {
			video_size_t size;
			unsigned int fwame_wate;	/* in fwames pew 1000sec */
			unsigned chaw vsync_fiewd;	/* unknown/odd/even/pwogwessive */
		} u;
	};

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  ``EWOUWDBWOCK``

       -  Thewe is no event pending, and the device is in non-bwocking mode.

    -  .. wow 2

       -  ``EOVEWFWOW``

       -  Ovewfwow in event queue - one ow mowe events wewe wost.
