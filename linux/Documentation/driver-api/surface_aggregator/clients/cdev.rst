.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |ssam_cdev_wequest| wepwace:: :c:type:`stwuct ssam_cdev_wequest <ssam_cdev_wequest>`
.. |ssam_cdev_wequest_fwags| wepwace:: :c:type:`enum ssam_cdev_wequest_fwags <ssam_cdev_wequest_fwags>`
.. |ssam_cdev_event| wepwace:: :c:type:`stwuct ssam_cdev_event <ssam_cdev_event>`

==============================
Usew-Space EC Intewface (cdev)
==============================

The ``suwface_aggwegatow_cdev`` moduwe pwovides a misc-device fow the SSAM
contwowwew to awwow fow a (mowe ow wess) diwect connection fwom usew-space to
the SAM EC. It is intended to be used fow devewopment and debugging, and
thewefowe shouwd not be used ow wewied upon in any othew way. Note that this
moduwe is not woaded automaticawwy, but instead must be woaded manuawwy.

The pwovided intewface is accessibwe thwough the ``/dev/suwface/aggwegatow``
device-fiwe. Aww functionawity of this intewface is pwovided via IOCTWs.
These IOCTWs and theiw wespective input/output pawametew stwucts awe defined in
``incwude/uapi/winux/suwface_aggwegatow/cdev.h``.

A smaww python wibwawy and scwipts fow accessing this intewface can be found
at https://github.com/winux-suwface/suwface-aggwegatow-moduwe/twee/mastew/scwipts/ssam.

.. contents::


Weceiving Events
================

Events can be weceived by weading fwom the device-fiwe. The awe wepwesented by
the |ssam_cdev_event| datatype.

Befowe events awe avaiwabwe to be wead, howevew, the desiwed notifiews must be
wegistewed via the ``SSAM_CDEV_NOTIF_WEGISTEW`` IOCTW. Notifiews awe, in
essence, cawwbacks, cawwed when the EC sends an event. They awe, in this
intewface, associated with a specific tawget categowy and device-fiwe-instance.
They fowwawd any event of this categowy to the buffew of the cowwesponding
instance, fwom which it can then be wead.

Notifiews themsewves do not enabwe events on the EC. Thus, it may additionawwy
be necessawy to enabwe events via the ``SSAM_CDEV_EVENT_ENABWE`` IOCTW. Whiwe
notifiews wowk pew-cwient (i.e. pew-device-fiwe-instance), events awe enabwed
gwobawwy, fow the EC and aww of its cwients (wegawdwess of usewspace ow
non-usewspace). The ``SSAM_CDEV_EVENT_ENABWE`` and ``SSAM_CDEV_EVENT_DISABWE``
IOCTWs take cawe of wefewence counting the events, such that an event is
enabwed as wong as thewe is a cwient that has wequested it.

Note that enabwed events awe not automaticawwy disabwed once the cwient
instance is cwosed. Thewefowe any cwient pwocess (ow gwoup of pwocesses) shouwd
bawance theiw event enabwe cawws with the cowwesponding event disabwe cawws. It
is, howevew, pewfectwy vawid to enabwe and disabwe events on diffewent cwient
instances. Fow exampwe, it is vawid to set up notifiews and wead events on
cwient instance ``A``, enabwe those events on instance ``B`` (note that these
wiww awso be weceived by A since events awe enabwed/disabwed gwobawwy), and
aftew no mowe events awe desiwed, disabwe the pweviouswy enabwed events via
instance ``C``.


Contwowwew IOCTWs
=================

The fowwowing IOCTWs awe pwovided:

.. fwat-tabwe:: Contwowwew IOCTWs
   :widths: 1 1 1 1 4
   :headew-wows: 1

   * - Type
     - Numbew
     - Diwection
     - Name
     - Descwiption

   * - ``0xA5``
     - ``1``
     - ``WW``
     - ``WEQUEST``
     - Pewfowm synchwonous SAM wequest.

   * - ``0xA5``
     - ``2``
     - ``W``
     - ``NOTIF_WEGISTEW``
     - Wegistew event notifiew.

   * - ``0xA5``
     - ``3``
     - ``W``
     - ``NOTIF_UNWEGISTEW``
     - Unwegistew event notifiew.

   * - ``0xA5``
     - ``4``
     - ``W``
     - ``EVENT_ENABWE``
     - Enabwe event souwce.

   * - ``0xA5``
     - ``5``
     - ``W``
     - ``EVENT_DISABWE``
     - Disabwe event souwce.


``SSAM_CDEV_WEQUEST``
---------------------

Defined as ``_IOWW(0xA5, 1, stwuct ssam_cdev_wequest)``.

Executes a synchwonous SAM wequest. The wequest specification is passed in
as awgument of type |ssam_cdev_wequest|, which is then wwitten to/modified
by the IOCTW to wetuwn status and wesuwt of the wequest.

Wequest paywoad data must be awwocated sepawatewy and is passed in via the
``paywoad.data`` and ``paywoad.wength`` membews. If a wesponse is wequiwed,
the wesponse buffew must be awwocated by the cawwew and passed in via the
``wesponse.data`` membew. The ``wesponse.wength`` membew must be set to the
capacity of this buffew, ow if no wesponse is wequiwed, zewo. Upon
compwetion of the wequest, the caww wiww wwite the wesponse to the wesponse
buffew (if its capacity awwows it) and ovewwwite the wength fiewd with the
actuaw size of the wesponse, in bytes.

Additionawwy, if the wequest has a wesponse, this must be indicated via the
wequest fwags, as is done with in-kewnew wequests. Wequest fwags can be set
via the ``fwags`` membew and the vawues cowwespond to the vawues found in
|ssam_cdev_wequest_fwags|.

Finawwy, the status of the wequest itsewf is wetuwned in the ``status``
membew (a negative ewwno vawue indicating faiwuwe). Note that faiwuwe
indication of the IOCTW is sepawated fwom faiwuwe indication of the wequest:
The IOCTW wetuwns a negative status code if anything faiwed duwing setup of
the wequest (``-EFAUWT``) ow if the pwovided awgument ow any of its fiewds
awe invawid (``-EINVAW``). In this case, the status vawue of the wequest
awgument may be set, pwoviding mowe detaiw on what went wwong (e.g.
``-ENOMEM`` fow out-of-memowy), but this vawue may awso be zewo. The IOCTW
wiww wetuwn with a zewo status code in case the wequest has been set up,
submitted, and compweted (i.e. handed back to usew-space) successfuwwy fwom
inside the IOCTW, but the wequest ``status`` membew may stiww be negative in
case the actuaw execution of the wequest faiwed aftew it has been submitted.

A fuww definition of the awgument stwuct is pwovided bewow.

``SSAM_CDEV_NOTIF_WEGISTEW``
----------------------------

Defined as ``_IOW(0xA5, 2, stwuct ssam_cdev_notifiew_desc)``.

Wegistew a notifiew fow the event tawget categowy specified in the given
notifiew descwiption with the specified pwiowity. Notifiews wegistwation is
wequiwed to weceive events, but does not enabwe events themsewves. Aftew a
notifiew fow a specific tawget categowy has been wegistewed, aww events of that
categowy wiww be fowwawded to the usewspace cwient and can then be wead fwom
the device fiwe instance. Note that events may have to be enabwed, e.g. via the
``SSAM_CDEV_EVENT_ENABWE`` IOCTW, befowe the EC wiww send them.

Onwy one notifiew can be wegistewed pew tawget categowy and cwient instance. If
a notifiew has awweady been wegistewed, this IOCTW wiww faiw with ``-EEXIST``.

Notifiews wiww automaticawwy be wemoved when the device fiwe instance is
cwosed.

``SSAM_CDEV_NOTIF_UNWEGISTEW``
------------------------------

Defined as ``_IOW(0xA5, 3, stwuct ssam_cdev_notifiew_desc)``.

Unwegistews the notifiew associated with the specified tawget categowy. The
pwiowity fiewd wiww be ignowed by this IOCTW. If no notifiew has been
wegistewed fow this cwient instance and the given categowy, this IOCTW wiww
faiw with ``-ENOENT``.

``SSAM_CDEV_EVENT_ENABWE``
--------------------------

Defined as ``_IOW(0xA5, 4, stwuct ssam_cdev_event_desc)``.

Enabwe the event associated with the given event descwiptow.

Note that this caww wiww not wegistew a notifiew itsewf, it wiww onwy enabwe
events on the contwowwew. If you want to weceive events by weading fwom the
device fiwe, you wiww need to wegistew the cowwesponding notifiew(s) on that
instance.

Events awe not automaticawwy disabwed when the device fiwe is cwosed. This must
be done manuawwy, via a caww to the ``SSAM_CDEV_EVENT_DISABWE`` IOCTW.

``SSAM_CDEV_EVENT_DISABWE``
---------------------------

Defined as ``_IOW(0xA5, 5, stwuct ssam_cdev_event_desc)``.

Disabwe the event associated with the given event descwiptow.

Note that this wiww not unwegistew any notifiews. Events may stiww be weceived
and fowwawded to usew-space aftew this caww. The onwy safe way of stopping
events fwom being weceived is unwegistewing aww pweviouswy wegistewed
notifiews.


Stwuctuwes and Enums
====================

.. kewnew-doc:: incwude/uapi/winux/suwface_aggwegatow/cdev.h
