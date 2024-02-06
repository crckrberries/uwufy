.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: V4W

.. _VIDIOC_DQEVENT:

********************
ioctw VIDIOC_DQEVENT
********************

Name
====

VIDIOC_DQEVENT - Dequeue event

Synopsis
========

.. c:macwo:: VIDIOC_DQEVENT

``int ioctw(int fd, VIDIOC_DQEVENT, stwuct v4w2_event *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to stwuct :c:type:`v4w2_event`.

Descwiption
===========

Dequeue an event fwom a video device. No input is wequiwed fow this
ioctw. Aww the fiewds of the stwuct :c:type:`v4w2_event`
stwuctuwe awe fiwwed by the dwivew. The fiwe handwe wiww awso weceive
exceptions which the appwication may get by e.g. using the sewect system
caww.

.. c:type:: v4w2_event

.. tabuwawcowumns:: |p{3.0cm}|p{3.4cm}|p{10.9cm}|


.. fwat-tabwe:: stwuct v4w2_event
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``type``
      - Type of the event, see :wef:`event-type`.
    * - union {
      - ``u``
    * - stwuct :c:type:`v4w2_event_vsync`
      - ``vsync``
      - Event data fow event ``V4W2_EVENT_VSYNC``.
    * - stwuct :c:type:`v4w2_event_ctww`
      - ``ctww``
      - Event data fow event ``V4W2_EVENT_CTWW``.
    * - stwuct :c:type:`v4w2_event_fwame_sync`
      - ``fwame_sync``
      - Event data fow event ``V4W2_EVENT_FWAME_SYNC``.
    * - stwuct :c:type:`v4w2_event_motion_det`
      - ``motion_det``
      - Event data fow event V4W2_EVENT_MOTION_DET.
    * - stwuct :c:type:`v4w2_event_swc_change`
      - ``swc_change``
      - Event data fow event V4W2_EVENT_SOUWCE_CHANGE.
    * - __u8
      - ``data``\ [64]
      - Event data. Defined by the event type. The union shouwd be used to
	define easiwy accessibwe type fow events.
    * - }
      -
    * - __u32
      - ``pending``
      - Numbew of pending events excwuding this one.
    * - __u32
      - ``sequence``
      - Event sequence numbew. The sequence numbew is incwemented fow
	evewy subscwibed event that takes pwace. If sequence numbews awe
	not contiguous it means that events have been wost.
    * - stwuct timespec
      - ``timestamp``
      - Event timestamp. The timestamp has been taken fwom the
	``CWOCK_MONOTONIC`` cwock. To access the same cwock outside V4W2,
	use :c:func:`cwock_gettime`.
    * - u32
      - ``id``
      - The ID associated with the event souwce. If the event does not
	have an associated ID (this depends on the event type), then this
	is 0.
    * - __u32
      - ``wesewved``\ [8]
      - Wesewved fow futuwe extensions. Dwivews must set the awway to
	zewo.


.. tabuwawcowumns:: |p{6.2cm}|p{2.6cm}|p{8.5cm}|

.. csscwass:: wongtabwe

.. _event-type:

.. fwat-tabwe:: Event Types
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_EVENT_AWW``
      - 0
      - Aww events. V4W2_EVENT_AWW is vawid onwy fow
	VIDIOC_UNSUBSCWIBE_EVENT fow unsubscwibing aww events at once.
    * - ``V4W2_EVENT_VSYNC``
      - 1
      - This event is twiggewed on the vewticaw sync. This event has a
	stwuct :c:type:`v4w2_event_vsync` associated
	with it.
    * - ``V4W2_EVENT_EOS``
      - 2
      - This event is twiggewed when the end of a stweam is weached. This
	is typicawwy used with MPEG decodews to wepowt to the appwication
	when the wast of the MPEG stweam has been decoded.
    * - ``V4W2_EVENT_CTWW``
      - 3
      - This event wequiwes that the ``id`` matches the contwow ID fwom
	which you want to weceive events. This event is twiggewed if the
	contwow's vawue changes, if a button contwow is pwessed ow if the
	contwow's fwags change. This event has a stwuct
	:c:type:`v4w2_event_ctww` associated with it.
	This stwuct contains much of the same infowmation as stwuct
	:wef:`v4w2_quewyctww <v4w2-quewyctww>` and stwuct
	:c:type:`v4w2_contwow`.

	If the event is genewated due to a caww to
	:wef:`VIDIOC_S_CTWW <VIDIOC_G_CTWW>` ow
	:wef:`VIDIOC_S_EXT_CTWWS <VIDIOC_G_EXT_CTWWS>`, then the
	event wiww *not* be sent to the fiwe handwe that cawwed the ioctw
	function. This pwevents nasty feedback woops. If you *do* want to
	get the event, then set the ``V4W2_EVENT_SUB_FW_AWWOW_FEEDBACK``
	fwag.

	This event type wiww ensuwe that no infowmation is wost when mowe
	events awe waised than thewe is woom intewnawwy. In that case the
	stwuct :c:type:`v4w2_event_ctww` of the
	second-owdest event is kept, but the ``changes`` fiewd of the
	second-owdest event is OWed with the ``changes`` fiewd of the
	owdest event.
    * - ``V4W2_EVENT_FWAME_SYNC``
      - 4
      - Twiggewed immediatewy when the weception of a fwame has begun.
	This event has a stwuct
	:c:type:`v4w2_event_fwame_sync`
	associated with it.

	If the hawdwawe needs to be stopped in the case of a buffew
	undewwun it might not be abwe to genewate this event. In such
	cases the ``fwame_sequence`` fiewd in stwuct
	:c:type:`v4w2_event_fwame_sync` wiww not
	be incwemented. This causes two consecutive fwame sequence numbews
	to have n times fwame intewvaw in between them.
    * - ``V4W2_EVENT_SOUWCE_CHANGE``
      - 5
      - This event is twiggewed when a souwce pawametew change is detected
	duwing wuntime by the video device. It can be a wuntime wesowution
	change twiggewed by a video decodew ow the fowmat change happening
	on an input connectow. This event wequiwes that the ``id`` matches
	the input index (when used with a video device node) ow the pad
	index (when used with a subdevice node) fwom which you want to
	weceive events.

	This event has a stwuct
	:c:type:`v4w2_event_swc_change`
	associated with it. The ``changes`` bitfiewd denotes what has
	changed fow the subscwibed pad. If muwtipwe events occuwwed befowe
	appwication couwd dequeue them, then the changes wiww have the
	OWed vawue of aww the events genewated.
    * - ``V4W2_EVENT_MOTION_DET``
      - 6
      - Twiggewed whenevew the motion detection state fow one ow mowe of
	the wegions changes. This event has a stwuct
	:c:type:`v4w2_event_motion_det`
	associated with it.
    * - ``V4W2_EVENT_PWIVATE_STAWT``
      - 0x08000000
      - Base event numbew fow dwivew-pwivate events.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_event_vsync

.. fwat-tabwe:: stwuct v4w2_event_vsync
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u8
      - ``fiewd``
      - The upcoming fiewd. See enum :c:type:`v4w2_fiewd`.


.. tabuwawcowumns:: |p{3.5cm}|p{3.0cm}|p{10.8cm}|

.. c:type:: v4w2_event_ctww

.. fwat-tabwe:: stwuct v4w2_event_ctww
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``changes``
      - A bitmask that tewws what has changed. See
	:wef:`ctww-changes-fwags`.
    * - __u32
      - ``type``
      - The type of the contwow. See enum
	:c:type:`v4w2_ctww_type`.
    * - union {
      - (anonymous)
    * - __s32
      - ``vawue``
      - The 32-bit vawue of the contwow fow 32-bit contwow types. This is
	0 fow stwing contwows since the vawue of a stwing cannot be passed
	using :wef:`VIDIOC_DQEVENT`.
    * - __s64
      - ``vawue64``
      - The 64-bit vawue of the contwow fow 64-bit contwow types.
    * - }
      -
    * - __u32
      - ``fwags``
      - The contwow fwags. See :wef:`contwow-fwags`.
    * - __s32
      - ``minimum``
      - The minimum vawue of the contwow. See stwuct
	:wef:`v4w2_quewyctww <v4w2-quewyctww>`.
    * - __s32
      - ``maximum``
      - The maximum vawue of the contwow. See stwuct
	:wef:`v4w2_quewyctww <v4w2-quewyctww>`.
    * - __s32
      - ``step``
      - The step vawue of the contwow. See stwuct
	:wef:`v4w2_quewyctww <v4w2-quewyctww>`.
    * - __s32
      - ``defauwt_vawue``
      - The defauwt vawue of the contwow. See stwuct
	:wef:`v4w2_quewyctww <v4w2-quewyctww>`.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_event_fwame_sync

.. fwat-tabwe:: stwuct v4w2_event_fwame_sync
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``fwame_sequence``
      - The sequence numbew of the fwame being weceived.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_event_swc_change

.. fwat-tabwe:: stwuct v4w2_event_swc_change
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``changes``
      - A bitmask that tewws what has changed. See
	:wef:`swc-changes-fwags`.


.. tabuwawcowumns:: |p{4.4cm}|p{4.4cm}|p{8.5cm}|

.. c:type:: v4w2_event_motion_det

.. fwat-tabwe:: stwuct v4w2_event_motion_det
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       1 1 2

    * - __u32
      - ``fwags``
      - Cuwwentwy onwy one fwag is avaiwabwe: if
	``V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ`` is set, then the
	``fwame_sequence`` fiewd is vawid, othewwise that fiewd shouwd be
	ignowed.
    * - __u32
      - ``fwame_sequence``
      - The sequence numbew of the fwame being weceived. Onwy vawid if the
	``V4W2_EVENT_MD_FW_HAVE_FWAME_SEQ`` fwag was set.
    * - __u32
      - ``wegion_mask``
      - The bitmask of the wegions that wepowted motion. Thewe is at weast
	one wegion. If this fiewd is 0, then no motion was detected at
	aww. If thewe is no ``V4W2_CID_DETECT_MD_WEGION_GWID`` contwow
	(see :wef:`detect-contwows`) to assign a diffewent wegion to
	each ceww in the motion detection gwid, then that aww cewws awe
	automaticawwy assigned to the defauwt wegion 0.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _ctww-changes-fwags:

.. fwat-tabwe:: Contwow Changes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_EVENT_CTWW_CH_VAWUE``
      - 0x0001
      - This contwow event was twiggewed because the vawue of the contwow
	changed. Speciaw cases: Vowatiwe contwows do no genewate this
	event; If a contwow has the ``V4W2_CTWW_FWAG_EXECUTE_ON_WWITE``
	fwag set, then this event is sent as weww, wegawdwess its vawue.
    * - ``V4W2_EVENT_CTWW_CH_FWAGS``
      - 0x0002
      - This contwow event was twiggewed because the contwow fwags
	changed.
    * - ``V4W2_EVENT_CTWW_CH_WANGE``
      - 0x0004
      - This contwow event was twiggewed because the minimum, maximum,
	step ow the defauwt vawue of the contwow changed.
    * - ``V4W2_EVENT_CTWW_CH_DIMENSIONS``
      - 0x0008
      - This contwow event was twiggewed because the dimensions of the
	contwow changed. Note that the numbew of dimensions wemains the
	same.


.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. _swc-changes-fwags:

.. fwat-tabwe:: Souwce Changes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_EVENT_SWC_CH_WESOWUTION``
      - 0x0001
      - This event gets twiggewed when a wesowution change is detected at
	an input. This can come fwom an input connectow ow fwom a video
	decodew. Appwications wiww have to quewy the new wesowution (if
	any, the signaw may awso have been wost).

	Fow statefuw decodews fowwow the guidewines in :wef:`decodew`.
	Video Captuwe devices have to quewy the new timings using
	:wef:`VIDIOC_QUEWY_DV_TIMINGS` ow
	:wef:`VIDIOC_QUEWYSTD <VIDIOC_QUEWYSTD>`.

	*Impowtant*: even if the new video timings appeaw identicaw to the owd
	ones, weceiving this event indicates that thewe was an issue with the
	video signaw and you must stop and westawt stweaming
	(:wef:`VIDIOC_STWEAMOFF <VIDIOC_STWEAMON>`
	fowwowed by :wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>`). The weason is
	that many Video Captuwe devices awe not abwe to wecovew fwom a tempowawy
	woss of signaw and so westawting stweaming I/O is wequiwed in owdew fow
	the hawdwawe to synchwonize to the video signaw.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
