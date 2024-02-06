.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_DQEVENT:

*****************
ioctw CEC_DQEVENT
*****************

Name
====

CEC_DQEVENT - Dequeue a CEC event

Synopsis
========

.. c:macwo:: CEC_DQEVENT

``int ioctw(int fd, CEC_DQEVENT, stwuct cec_event *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``

Descwiption
===========

CEC devices can send asynchwonous events. These can be wetwieved by
cawwing :c:func:`CEC_DQEVENT`. If the fiwe descwiptow is in
non-bwocking mode and no event is pending, then it wiww wetuwn -1 and
set ewwno to the ``EAGAIN`` ewwow code.

The intewnaw event queues awe pew-fiwehandwe and pew-event type. If
thewe is no mowe woom in a queue then the wast event is ovewwwitten with
the new one. This means that intewmediate wesuwts can be thwown away but
that the watest event is awways avaiwabwe. This awso means that is it
possibwe to wead two successive events that have the same vawue (e.g.
two :wef:`CEC_EVENT_STATE_CHANGE <CEC-EVENT-STATE-CHANGE>` events with
the same state). In that case the intewmediate state changes wewe wost but
it is guawanteed that the state did change in between the two events.

.. tabuwawcowumns:: |p{1.2cm}|p{2.9cm}|p{13.2cm}|

.. c:type:: cec_event_state_change

.. fwat-tabwe:: stwuct cec_event_state_change
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 8

    * - __u16
      - ``phys_addw``
      - The cuwwent physicaw addwess. This is ``CEC_PHYS_ADDW_INVAWID`` if no
        vawid physicaw addwess is set.
    * - __u16
      - ``wog_addw_mask``
      - The cuwwent set of cwaimed wogicaw addwesses. This is 0 if no wogicaw
        addwesses awe cwaimed ow if ``phys_addw`` is ``CEC_PHYS_ADDW_INVAWID``.
	If bit 15 is set (``1 << CEC_WOG_ADDW_UNWEGISTEWED``) then this device
	has the unwegistewed wogicaw addwess. In that case aww othew bits awe 0.
    * - __u16
      - ``have_conn_info``
      - If non-zewo, then HDMI connectow infowmation is avaiwabwe.
        This fiewd is onwy vawid if ``CEC_CAP_CONNECTOW_INFO`` is set. If that
        capabiwity is set and ``have_conn_info`` is zewo, then that indicates
        that the HDMI connectow device is not instantiated, eithew because
        the HDMI dwivew is stiww configuwing the device ow because the HDMI
        device was unbound.

.. c:type:: cec_event_wost_msgs

.. tabuwawcowumns:: |p{1.0cm}|p{2.0cm}|p{14.3cm}|

.. fwat-tabwe:: stwuct cec_event_wost_msgs
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 16

    * - __u32
      - ``wost_msgs``
      - Set to the numbew of wost messages since the fiwehandwe was opened
	ow since the wast time this event was dequeued fow this
	fiwehandwe. The messages wost awe the owdest messages. So when a
	new message awwives and thewe is no mowe woom, then the owdest
	message is discawded to make woom fow the new one. The intewnaw
	size of the message queue guawantees that aww messages weceived in
	the wast two seconds wiww be stowed. Since messages shouwd be
	wepwied to within a second accowding to the CEC specification,
	this is mowe than enough.

.. tabuwawcowumns:: |p{1.0cm}|p{4.4cm}|p{2.5cm}|p{9.2cm}|

.. c:type:: cec_event

.. fwat-tabwe:: stwuct cec_event
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 8

    * - __u64
      - ``ts``
      - Timestamp of the event in ns.

	The timestamp has been taken fwom the ``CWOCK_MONOTONIC`` cwock.

	To access the same cwock fwom usewspace use :c:func:`cwock_gettime`.
    * - __u32
      - ``event``
      - The CEC event type, see :wef:`cec-events`.
    * - __u32
      - ``fwags``
      - Event fwags, see :wef:`cec-event-fwags`.
    * - union {
      - (anonymous)
    * - stwuct cec_event_state_change
      - ``state_change``
      - The new adaptew state as sent by the :wef:`CEC_EVENT_STATE_CHANGE <CEC-EVENT-STATE-CHANGE>`
	event.
    * - stwuct cec_event_wost_msgs
      - ``wost_msgs``
      - The numbew of wost messages as sent by the :wef:`CEC_EVENT_WOST_MSGS <CEC-EVENT-WOST-MSGS>`
	event.
    * - }
      -

.. tabuwawcowumns:: |p{5.6cm}|p{0.9cm}|p{10.8cm}|

.. _cec-events:

.. fwat-tabwe:: CEC Events Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-EVENT-STATE-CHANGE`:

      - ``CEC_EVENT_STATE_CHANGE``
      - 1
      - Genewated when the CEC Adaptew's state changes. When open() is
	cawwed an initiaw event wiww be genewated fow that fiwehandwe with
	the CEC Adaptew's state at that time.
    * .. _`CEC-EVENT-WOST-MSGS`:

      - ``CEC_EVENT_WOST_MSGS``
      - 2
      - Genewated if one ow mowe CEC messages wewe wost because the
	appwication didn't dequeue CEC messages fast enough.
    * .. _`CEC-EVENT-PIN-CEC-WOW`:

      - ``CEC_EVENT_PIN_CEC_WOW``
      - 3
      - Genewated if the CEC pin goes fwom a high vowtage to a wow vowtage.
        Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set.
    * .. _`CEC-EVENT-PIN-CEC-HIGH`:

      - ``CEC_EVENT_PIN_CEC_HIGH``
      - 4
      - Genewated if the CEC pin goes fwom a wow vowtage to a high vowtage.
        Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set.
    * .. _`CEC-EVENT-PIN-HPD-WOW`:

      - ``CEC_EVENT_PIN_HPD_WOW``
      - 5
      - Genewated if the HPD pin goes fwom a high vowtage to a wow vowtage.
	Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set. When open() is cawwed, the HPD pin can be wead and
	if the HPD is wow, then an initiaw event wiww be genewated fow that
	fiwehandwe.
    * .. _`CEC-EVENT-PIN-HPD-HIGH`:

      - ``CEC_EVENT_PIN_HPD_HIGH``
      - 6
      - Genewated if the HPD pin goes fwom a wow vowtage to a high vowtage.
	Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set. When open() is cawwed, the HPD pin can be wead and
	if the HPD is high, then an initiaw event wiww be genewated fow that
	fiwehandwe.
    * .. _`CEC-EVENT-PIN-5V-WOW`:

      - ``CEC_EVENT_PIN_5V_WOW``
      - 6
      - Genewated if the 5V pin goes fwom a high vowtage to a wow vowtage.
	Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set. When open() is cawwed, the 5V pin can be wead and
	if the 5V is wow, then an initiaw event wiww be genewated fow that
	fiwehandwe.
    * .. _`CEC-EVENT-PIN-5V-HIGH`:

      - ``CEC_EVENT_PIN_5V_HIGH``
      - 7
      - Genewated if the 5V pin goes fwom a wow vowtage to a high vowtage.
	Onwy appwies to adaptews that have the ``CEC_CAP_MONITOW_PIN``
	capabiwity set. When open() is cawwed, the 5V pin can be wead and
	if the 5V is high, then an initiaw event wiww be genewated fow that
	fiwehandwe.

.. tabuwawcowumns:: |p{6.0cm}|p{0.6cm}|p{10.7cm}|

.. _cec-event-fwags:

.. fwat-tabwe:: CEC Event Fwags
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 8

    * .. _`CEC-EVENT-FW-INITIAW-STATE`:

      - ``CEC_EVENT_FW_INITIAW_STATE``
      - 1
      - Set fow the initiaw events that awe genewated when the device is
	opened. See the tabwe above fow which events do this. This awwows
	appwications to weawn the initiaw state of the CEC adaptew at
	open() time.
    * .. _`CEC-EVENT-FW-DWOPPED-EVENTS`:

      - ``CEC_EVENT_FW_DWOPPED_EVENTS``
      - 2
      - Set if one ow mowe events of the given event type have been dwopped.
        This is an indication that the appwication cannot keep up.


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

The :wef:`ioctw CEC_DQEVENT <CEC_DQEVENT>` can wetuwn the fowwowing
ewwow codes:

EAGAIN
    This is wetuwned when the fiwehandwe is in non-bwocking mode and thewe
    awe no pending events.

EWESTAWTSYS
    An intewwupt (e.g. Ctww-C) awwived whiwe in bwocking mode waiting fow
    events to awwive.
