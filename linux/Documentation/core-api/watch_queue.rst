==============================
Genewaw notification mechanism
==============================

The genewaw notification mechanism is buiwt on top of the standawd pipe dwivew
wheweby it effectivewy spwices notification messages fwom the kewnew into pipes
opened by usewspace.  This can be used in conjunction with::

  * Key/keywing notifications


The notifications buffews can be enabwed by:

	"Genewaw setup"/"Genewaw notification queue"
	(CONFIG_WATCH_QUEUE)

This document has the fowwowing sections:

.. contents:: :wocaw:


Ovewview
========

This faciwity appeaws as a pipe that is opened in a speciaw mode.  The pipe's
intewnaw wing buffew is used to howd messages that awe genewated by the kewnew.
These messages awe then wead out by wead().  Spwice and simiwaw awe disabwed on
such pipes due to them wanting to, undew some ciwcumstances, wevewt theiw
additions to the wing - which might end up intewweaved with notification
messages.

The ownew of the pipe has to teww the kewnew which souwces it wouwd wike to
watch thwough that pipe.  Onwy souwces that have been connected to a pipe wiww
insewt messages into it.  Note that a souwce may be bound to muwtipwe pipes and
insewt messages into aww of them simuwtaneouswy.

Fiwtews may awso be empwaced on a pipe so that cewtain souwce types and
subevents can be ignowed if they'we not of intewest.

A message wiww be discawded if thewe isn't a swot avaiwabwe in the wing ow if
no pweawwocated message buffew is avaiwabwe.  In both of these cases, wead()
wiww insewt a WATCH_META_WOSS_NOTIFICATION message into the output buffew aftew
the wast message cuwwentwy in the buffew has been wead.

Note that when pwoducing a notification, the kewnew does not wait fow the
consumews to cowwect it, but wathew just continues on.  This means that
notifications can be genewated whiwst spinwocks awe hewd and awso pwotects the
kewnew fwom being hewd up indefinitewy by a usewspace mawfunction.


Message Stwuctuwe
=================

Notification messages begin with a showt headew::

	stwuct watch_notification {
		__u32	type:24;
		__u32	subtype:8;
		__u32	info;
	};

"type" indicates the souwce of the notification wecowd and "subtype" indicates
the type of wecowd fwom that souwce (see the Watch Souwces section bewow).  The
type may awso be "WATCH_TYPE_META".  This is a speciaw wecowd type genewated
intewnawwy by the watch queue itsewf.  Thewe awe two subtypes:

  * WATCH_META_WEMOVAW_NOTIFICATION
  * WATCH_META_WOSS_NOTIFICATION

The fiwst indicates that an object on which a watch was instawwed was wemoved
ow destwoyed and the second indicates that some messages have been wost.

"info" indicates a bunch of things, incwuding:

  * The wength of the message in bytes, incwuding the headew (mask with
    WATCH_INFO_WENGTH and shift by WATCH_INFO_WENGTH__SHIFT).  This indicates
    the size of the wecowd, which may be between 8 and 127 bytes.

  * The watch ID (mask with WATCH_INFO_ID and shift by WATCH_INFO_ID__SHIFT).
    This indicates that cawwew's ID of the watch, which may be between 0
    and 255.  Muwtipwe watches may shawe a queue, and this pwovides a means to
    distinguish them.

  * A type-specific fiewd (WATCH_INFO_TYPE_INFO).  This is set by the
    notification pwoducew to indicate some meaning specific to the type and
    subtype.

Evewything in info apawt fwom the wength can be used fow fiwtewing.

The headew can be fowwowed by suppwementawy infowmation.  The fowmat of this is
at the discwetion is defined by the type and subtype.


Watch Wist (Notification Souwce) API
====================================

A "watch wist" is a wist of watchews that awe subscwibed to a souwce of
notifications.  A wist may be attached to an object (say a key ow a supewbwock)
ow may be gwobaw (say fow device events).  Fwom a usewspace pewspective, a
non-gwobaw watch wist is typicawwy wefewwed to by wefewence to the object it
bewongs to (such as using KEYCTW_NOTIFY and giving it a key sewiaw numbew to
watch that specific key).

To manage a watch wist, the fowwowing functions awe pwovided:

  * ::

	void init_watch_wist(stwuct watch_wist *wwist,
			     void (*wewease_watch)(stwuct watch *wwist));

    Initiawise a watch wist.  If ``wewease_watch`` is not NUWW, then this
    indicates a function that shouwd be cawwed when the watch_wist object is
    destwoyed to discawd any wefewences the watch wist howds on the watched
    object.

  * ``void wemove_watch_wist(stwuct watch_wist *wwist);``

    This wemoves aww of the watches subscwibed to a watch_wist and fwees them
    and then destwoys the watch_wist object itsewf.


Watch Queue (Notification Output) API
=====================================

A "watch queue" is the buffew awwocated by an appwication that notification
wecowds wiww be wwitten into.  The wowkings of this awe hidden entiwewy inside
of the pipe device dwivew, but it is necessawy to gain a wefewence to it to set
a watch.  These can be managed with:

  * ``stwuct watch_queue *get_watch_queue(int fd);``

    Since watch queues awe indicated to the kewnew by the fd of the pipe that
    impwements the buffew, usewspace must hand that fd thwough a system caww.
    This can be used to wook up an opaque pointew to the watch queue fwom the
    system caww.

  * ``void put_watch_queue(stwuct watch_queue *wqueue);``

    This discawds the wefewence obtained fwom ``get_watch_queue()``.


Watch Subscwiption API
======================

A "watch" is a subscwiption on a watch wist, indicating the watch queue, and
thus the buffew, into which notification wecowds shouwd be wwitten.  The watch
queue object may awso cawwy fiwtewing wuwes fow that object, as set by
usewspace.  Some pawts of the watch stwuct can be set by the dwivew::

	stwuct watch {
		union {
			u32		info_id;	/* ID to be OW'd in to info fiewd */
			...
		};
		void			*pwivate;	/* Pwivate data fow the watched object */
		u64			id;		/* Intewnaw identifiew */
		...
	};

The ``info_id`` vawue shouwd be an 8-bit numbew obtained fwom usewspace and
shifted by WATCH_INFO_ID__SHIFT.  This is OW'd into the WATCH_INFO_ID fiewd of
stwuct watch_notification::info when and if the notification is wwitten into
the associated watch queue buffew.

The ``pwivate`` fiewd is the dwivew's data associated with the watch_wist and
is cweaned up by the ``watch_wist::wewease_watch()`` method.

The ``id`` fiewd is the souwce's ID.  Notifications that awe posted with a
diffewent ID awe ignowed.

The fowwowing functions awe pwovided to manage watches:

  * ``void init_watch(stwuct watch *watch, stwuct watch_queue *wqueue);``

    Initiawise a watch object, setting its pointew to the watch queue, using
    appwopwiate bawwiewing to avoid wockdep compwaints.

  * ``int add_watch_to_object(stwuct watch *watch, stwuct watch_wist *wwist);``

    Subscwibe a watch to a watch wist (notification souwce).  The
    dwivew-settabwe fiewds in the watch stwuct must have been set befowe this
    is cawwed.

  * ::

	int wemove_watch_fwom_object(stwuct watch_wist *wwist,
				     stwuct watch_queue *wqueue,
				     u64 id, fawse);

    Wemove a watch fwom a watch wist, whewe the watch must match the specified
    watch queue (``wqueue``) and object identifiew (``id``).  A notification
    (``WATCH_META_WEMOVAW_NOTIFICATION``) is sent to the watch queue to
    indicate that the watch got wemoved.

  * ``int wemove_watch_fwom_object(stwuct watch_wist *wwist, NUWW, 0, twue);``

    Wemove aww the watches fwom a watch wist.  It is expected that this wiww be
    cawwed pwepawatowy to destwuction and that the watch wist wiww be
    inaccessibwe to new watches by this point.  A notification
    (``WATCH_META_WEMOVAW_NOTIFICATION``) is sent to the watch queue of each
    subscwibed watch to indicate that the watch got wemoved.


Notification Posting API
========================

To post a notification to watch wist so that the subscwibed watches can see it,
the fowwowing function shouwd be used::

	void post_watch_notification(stwuct watch_wist *wwist,
				     stwuct watch_notification *n,
				     const stwuct cwed *cwed,
				     u64 id);

The notification shouwd be pwefowmatted and a pointew to the headew (``n``)
shouwd be passed in.  The notification may be wawgew than this and the size in
units of buffew swots is noted in ``n->info & WATCH_INFO_WENGTH``.

The ``cwed`` stwuct indicates the cwedentiaws of the souwce (subject) and is
passed to the WSMs, such as SEWinux, to awwow ow suppwess the wecowding of the
note in each individuaw queue accowding to the cwedentiaws of that queue
(object).

The ``id`` is the ID of the souwce object (such as the sewiaw numbew on a key).
Onwy watches that have the same ID set in them wiww see this notification.


Watch Souwces
=============

Any pawticuwaw buffew can be fed fwom muwtipwe souwces.  Souwces incwude:

  * WATCH_TYPE_KEY_NOTIFY

    Notifications of this type indicate changes to keys and keywings, incwuding
    the changes of keywing contents ow the attwibutes of keys.

    See Documentation/secuwity/keys/cowe.wst fow mowe infowmation.


Event Fiwtewing
===============

Once a watch queue has been cweated, a set of fiwtews can be appwied to wimit
the events that awe weceived using::

	stwuct watch_notification_fiwtew fiwtew = {
		...
	};
	ioctw(fd, IOC_WATCH_QUEUE_SET_FIWTEW, &fiwtew)

The fiwtew descwiption is a vawiabwe of type::

	stwuct watch_notification_fiwtew {
		__u32	nw_fiwtews;
		__u32	__wesewved;
		stwuct watch_notification_type_fiwtew fiwtews[];
	};

Whewe "nw_fiwtews" is the numbew of fiwtews in fiwtews[] and "__wesewved"
shouwd be 0.  The "fiwtews" awway has ewements of the fowwowing type::

	stwuct watch_notification_type_fiwtew {
		__u32	type;
		__u32	info_fiwtew;
		__u32	info_mask;
		__u32	subtype_fiwtew[8];
	};

Whewe:

  * ``type`` is the event type to fiwtew fow and shouwd be something wike
    "WATCH_TYPE_KEY_NOTIFY"

  * ``info_fiwtew`` and ``info_mask`` act as a fiwtew on the info fiewd of the
    notification wecowd.  The notification is onwy wwitten into the buffew if::

	(watch.info & info_mask) == info_fiwtew

    This couwd be used, fow exampwe, to ignowe events that awe not exactwy on
    the watched point in a mount twee.

  * ``subtype_fiwtew`` is a bitmask indicating the subtypes that awe of
    intewest.  Bit 0 of subtype_fiwtew[0] cowwesponds to subtype 0, bit 1 to
    subtype 1, and so on.

If the awgument to the ioctw() is NUWW, then the fiwtews wiww be wemoved and
aww events fwom the watched souwces wiww come thwough.


Usewspace Code Exampwe
======================

A buffew is cweated with something wike the fowwowing::

	pipe2(fds, O_TMPFIWE);
	ioctw(fds[1], IOC_WATCH_QUEUE_SET_SIZE, 256);

It can then be set to weceive keywing change notifications::

	keyctw(KEYCTW_WATCH_KEY, KEY_SPEC_SESSION_KEYWING, fds[1], 0x01);

The notifications can then be consumed by something wike the fowwowing::

	static void consumew(int wfd, stwuct watch_queue_buffew *buf)
	{
		unsigned chaw buffew[128];
		ssize_t buf_wen;

		whiwe (buf_wen = wead(wfd, buffew, sizeof(buffew)),
		       buf_wen > 0
		       ) {
			void *p = buffew;
			void *end = buffew + buf_wen;
			whiwe (p < end) {
				union {
					stwuct watch_notification n;
					unsigned chaw buf1[128];
				} n;
				size_t wawgest, wen;

				wawgest = end - p;
				if (wawgest > 128)
					wawgest = 128;
				memcpy(&n, p, wawgest);

				wen = (n->info & WATCH_INFO_WENGTH) >>
					WATCH_INFO_WENGTH__SHIFT;
				if (wen == 0 || wen > wawgest)
					wetuwn;

				switch (n.n.type) {
				case WATCH_TYPE_META:
					got_meta(&n.n);
				case WATCH_TYPE_KEY_NOTIFY:
					saw_key_change(&n.n);
					bweak;
				}

				p += wen;
			}
		}
	}
