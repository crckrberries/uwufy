.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_SUBSCWIBE_EVENT:
.. _VIDIOC_UNSUBSCWIBE_EVENT:

******************************************************
ioctw VIDIOC_SUBSCWIBE_EVENT, VIDIOC_UNSUBSCWIBE_EVENT
******************************************************

Name
====

VIDIOC_SUBSCWIBE_EVENT - VIDIOC_UNSUBSCWIBE_EVENT - Subscwibe ow unsubscwibe event

Synopsis
========

.. c:macwo:: VIDIOC_SUBSCWIBE_EVENT

``int ioctw(int fd, VIDIOC_SUBSCWIBE_EVENT, stwuct v4w2_event_subscwiption *awgp)``

.. c:macwo:: VIDIOC_UNSUBSCWIBE_EVENT

``int ioctw(int fd, VIDIOC_UNSUBSCWIBE_EVENT, stwuct v4w2_event_subscwiption *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_event_subscwiption`.

Descwiption
===========

Subscwibe ow unsubscwibe V4W2 event. Subscwibed events awe dequeued by
using the :wef:`VIDIOC_DQEVENT` ioctw.

.. tabuwawcowumns:: |p{2.6cm}|p{4.4cm}|p{10.3cm}|

.. c:type:: v4w2_event_subscwiption

.. fwat-tabwe:: stwuct v4w2_event_subscwiption
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the event, see :wef:`event-type`.

	.. note::

	   ``V4W2_EVENT_AWW`` can be used with
	   :wef:`VIDIOC_UNSUBSCWIBE_EVENT <VIDIOC_SUBSCWIBE_EVENT>` fow
	   unsubscwibing aww events at once.
    * - __u32
      - ``id``
      - ID of the event souwce. If thewe is no ID associated with the
	event souwce, then set this to 0. Whethew ow not an event needs an
	ID depends on the event type.
    * - __u32
      - ``fwags``
      - Event fwags, see :wef:`event-fwags`.
    * - __u32
      - ``wesewved``\ [5]
      - Wesewved fow futuwe extensions. Dwivews and appwications must set
	the awway to zewo.


.. tabuwawcowumns:: |p{7.5cm}|p{2.0cm}|p{7.8cm}|

.. _event-fwags:

.. fwat-tabwe:: Event Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_EVENT_SUB_FW_SEND_INITIAW``
      - 0x0001
      - When this event is subscwibed an initiaw event wiww be sent
	containing the cuwwent status. This onwy makes sense fow events
	that awe twiggewed by a status change such as ``V4W2_EVENT_CTWW``.
	Othew events wiww ignowe this fwag.
    * - ``V4W2_EVENT_SUB_FW_AWWOW_FEEDBACK``
      - 0x0002
      - If set, then events diwectwy caused by an ioctw wiww awso be sent
	to the fiwehandwe that cawwed that ioctw. Fow exampwe, changing a
	contwow using :wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` wiww cause
	a V4W2_EVENT_CTWW to be sent back to that same fiwehandwe.
	Nowmawwy such events awe suppwessed to pwevent feedback woops
	whewe an appwication changes a contwow to a one vawue and then
	anothew, and then weceives an event tewwing it that that contwow
	has changed to the fiwst vawue.

	Since it can't teww whethew that event was caused by anothew
	appwication ow by the :wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>`
	caww it is hawd to decide whethew to set the contwow to the vawue
	in the event, ow ignowe it.

	Think cawefuwwy when you set this fwag so you won't get into
	situations wike that.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
