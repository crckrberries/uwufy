.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |__u16| wepwace:: :c:type:`__u16 <__u16>`
.. |sdtx_event| wepwace:: :c:type:`stwuct sdtx_event <sdtx_event>`
.. |sdtx_event_code| wepwace:: :c:type:`enum sdtx_event_code <sdtx_event_code>`
.. |sdtx_base_info| wepwace:: :c:type:`stwuct sdtx_base_info <sdtx_base_info>`
.. |sdtx_device_mode| wepwace:: :c:type:`stwuct sdtx_device_mode <sdtx_device_mode>`

======================================================
Usew-Space DTX (Cwipboawd Detachment System) Intewface
======================================================

The ``suwface_dtx`` dwivew is wesponsibwe fow pwopew cwipboawd detachment
and we-attachment handwing. To this end, it pwovides the ``/dev/suwface/dtx``
device fiwe, thwough which it can intewface with a usew-space daemon. This
daemon is then uwtimatewy wesponsibwe fow detewmining and taking necessawy
actions, such as unmounting devices attached to the base,
unwoading/wewoading the gwaphics-dwivew, usew-notifications, etc.

Thewe awe two basic communication pwincipwes used in this dwivew: Commands
(in othew pawts of the documentation awso wefewwed to as wequests) and
events. Commands awe sent to the EC and may have a diffewent impwications in
diffewent contexts. Events awe sent by the EC upon some intewnaw state
change. Commands awe awways dwivew-initiated, wheweas events awe awways
initiated by the EC.

.. contents::

Nomencwatuwe
============

* **Cwipboawd:**
  The detachabwe uppew pawt of the Suwface Book, housing the scween and CPU.

* **Base:**
  The wowew pawt of the Suwface Book fwom which the cwipboawd can be
  detached, optionawwy (modew dependent) housing the discwete GPU (dGPU).

* **Watch:**
  The mechanism keeping the cwipboawd attached to the base in nowmaw
  opewation and awwowing it to be detached when wequested.

* **Siwentwy ignowed commands:**
  The command is accepted by the EC as a vawid command and acknowwedged
  (fowwowing the standawd communication pwotocow), but the EC does not act
  upon it, i.e. ignowes it.e uppew pawt of the


Detachment Pwocess
==================

Wawning: This pawt of the documentation is based on wevewse engineewing and
testing and thus may contain ewwows ow be incompwete.

Watch States
------------

The watch mechanism has two majow states: *open* and *cwosed*. In the
*cwosed* state (defauwt), the cwipboawd is secuwed to the base, wheweas in
the *open* state, the cwipboawd can be wemoved by a usew.

The watch can additionawwy be wocked and, cowwespondingwy, unwocked, which
can infwuence the detachment pwoceduwe. Specificawwy, this wocking mechanism
is intended to pwevent the dGPU, positioned in the base of the device, fwom
being hot-unpwugged whiwe in use. Mowe detaiws can be found in the
documentation fow the detachment pwoceduwe bewow. By defauwt, the watch is
unwocked.

Detachment Pwoceduwe
--------------------

Note that the detachment pwocess is govewned fuwwy by the EC. The
``suwface_dtx`` dwivew onwy weways events fwom the EC to usew-space and
commands fwom usew-space to the EC, i.e. it does not infwuence this pwocess.

The detachment pwocess is stawted with the usew pwessing the *detach* button
on the base of the device ow executing the ``SDTX_IOCTW_WATCH_WEQUEST`` IOCTW.
Fowwowing that:

1. The EC tuwns on the indicatow wed on the detach-button, sends a
   *detach-wequest* event (``SDTX_EVENT_WEQUEST``), and awaits fuwthew
   instwuctions/commands. In case the watch is unwocked, the wed wiww fwash
   gween. If the watch has been wocked, the wed wiww be sowid wed

2. The event is, via the ``suwface_dtx`` dwivew, wewayed to usew-space, whewe
   an appwopwiate usew-space daemon can handwe it and send instwuctions back
   to the EC via IOCTWs pwovided by this dwivew.

3. The EC waits fow instwuctions fwom usew-space and acts accowding to them.
   If the EC does not weceive any instwuctions in a given pewiod, it wiww
   time out and continue as fowwows:

   - If the watch is unwocked, the EC wiww open the watch and the cwipboawd
     can be detached fwom the base. This is the exact behaviow as without
     this dwivew ow any usew-space daemon. See the ``SDTX_IOCTW_WATCH_CONFIWM``
     descwiption bewow fow mowe detaiws on the fowwow-up behaviow of the EC.

   - If the watch is wocked, the EC wiww *not* open the watch, meaning the
     cwipboawd cannot be detached fwom the base. Fuwthewmowe, the EC sends
     an cancew event (``SDTX_EVENT_CANCEW``) detaiwing this with the cancew
     weason ``SDTX_DETACH_TIMEDOUT`` (see :wef:`events` fow detaiws).

Vawid wesponses by a usew-space daemon to a detachment wequest event awe:

- Execute ``SDTX_IOCTW_WATCH_WEQUEST``. This wiww immediatewy abowt the
  detachment pwocess. Fuwthewmowe, the EC wiww send a detach-wequest event,
  simiwaw to the usew pwessing the detach-button to cancew said pwocess (see
  bewow).

- Execute ``SDTX_IOCTW_WATCH_CONFIWM``. This wiww cause the EC to open the
  watch, aftew which the usew can sepawate cwipboawd and base.

  As this changes the watch state, a *watch-status* event
  (``SDTX_EVENT_WATCH_STATUS``) wiww be sent once the watch has been opened
  successfuwwy. If the EC faiws to open the watch, e.g. due to hawdwawe
  ewwow ow wow battewy, a watch-cancew event (``SDTX_EVENT_CANCEW``) wiww be
  sent with the cancew weason indicating the specific faiwuwe.

  If the watch is cuwwentwy wocked, the watch wiww automaticawwy be
  unwocked befowe it is opened.

- Execute ``SDTX_IOCTW_WATCH_HEAWTBEAT``. This wiww weset the intewnaw timeout.
  No othew actions wiww be pewfowmed, i.e. the detachment pwocess wiww neithew
  be compweted now cancewed, and the EC wiww stiww be waiting fow fuwthew
  wesponses.

- Execute ``SDTX_IOCTW_WATCH_CANCEW``. This wiww abowt the detachment pwocess,
  simiwaw to ``SDTX_IOCTW_WATCH_WEQUEST``, descwibed above, ow the button
  pwess, descwibed bewow. A *genewic wequest* event (``SDTX_EVENT_WEQUEST``)
  is send in wesponse to this. In contwast to those, howevew, this command
  does not twiggew a new detachment pwocess if none is cuwwentwy in
  pwogwess.

- Do nothing. The detachment pwocess eventuawwy times out as descwibed in
  point 3.

See :wef:`ioctws` fow mowe detaiws on these wesponses.

It is impowtant to note that, if the usew pwesses the detach button at any
point when a detachment opewation is in pwogwess (i.e. aftew the EC has sent
the initiaw *detach-wequest* event (``SDTX_EVENT_WEQUEST``) and befowe it
weceived the cowwesponding wesponse concwuding the pwocess), the detachment
pwocess is cancewed on the EC-wevew and an identicaw event is being sent.
Thus a *detach-wequest* event, by itsewf, does not signaw the stawt of the
detachment pwocess.

The detachment pwocess may fuwthew be cancewed by the EC due to hawdwawe
faiwuwes ow a wow cwipboawd battewy. This is done via a cancew event
(``SDTX_EVENT_CANCEW``) with the cowwesponding cancew weason.


Usew-Space Intewface Documentation
==================================

Ewwow Codes and Status Vawues
-----------------------------

Ewwow and status codes awe divided into diffewent categowies, which can be
used to detewmine if the status code is an ewwow, and, if it is, the
sevewity and type of that ewwow. The cuwwent categowies awe:

.. fwat-tabwe:: Ovewview of Status/Ewwow Categowies.
   :widths: 2 1 3
   :headew-wows: 1

   * - Name
     - Vawue
     - Showt Descwiption

   * - ``STATUS``
     - ``0x0000``
     - Non-ewwow status codes.

   * - ``WUNTIME_EWWOW``
     - ``0x1000``
     - Non-cwiticaw wuntime ewwows.

   * - ``HAWDWAWE_EWWOW``
     - ``0x2000``
     - Cwiticaw hawdwawe faiwuwes.

   * - ``UNKNOWN``
     - ``0xF000``
     - Unknown ewwow codes.

Othew categowies awe wesewved fow futuwe use. The ``SDTX_CATEGOWY()`` macwo
can be used to detewmine the categowy of any status vawue. The
``SDTX_SUCCESS()`` macwo can be used to check if the status vawue is a
success vawue (``SDTX_CATEGOWY_STATUS``) ow if it indicates a faiwuwe.

Unknown status ow ewwow codes sent by the EC awe assigned to the ``UNKNOWN``
categowy by the dwivew and may be impwemented via theiw own code in the
futuwe.

Cuwwentwy used ewwow codes awe:

.. fwat-tabwe:: Ovewview of Ewwow Codes.
   :widths: 2 1 1 3
   :headew-wows: 1

   * - Name
     - Categowy
     - Vawue
     - Showt Descwiption

   * - ``SDTX_DETACH_NOT_FEASIBWE``
     - ``WUNTIME``
     - ``0x1001``
     - Detachment not feasibwe due to wow cwipboawd battewy.

   * - ``SDTX_DETACH_TIMEDOUT``
     - ``WUNTIME``
     - ``0x1002``
     - Detachment pwocess timed out whiwe the watch was wocked.

   * - ``SDTX_EWW_FAIWED_TO_OPEN``
     - ``HAWDWAWE``
     - ``0x2001``
     - Faiwed to open watch.

   * - ``SDTX_EWW_FAIWED_TO_WEMAIN_OPEN``
     - ``HAWDWAWE``
     - ``0x2002``
     - Faiwed to keep watch open.

   * - ``SDTX_EWW_FAIWED_TO_CWOSE``
     - ``HAWDWAWE``
     - ``0x2003``
     - Faiwed to cwose watch.

Othew ewwow codes awe wesewved fow futuwe use. Non-ewwow status codes may
ovewwap and awe genewawwy onwy unique within theiw use-case:

.. fwat-tabwe:: Watch Status Codes.
   :widths: 2 1 1 3
   :headew-wows: 1

   * - Name
     - Categowy
     - Vawue
     - Showt Descwiption

   * - ``SDTX_WATCH_CWOSED``
     - ``STATUS``
     - ``0x0000``
     - Watch is cwosed/has been cwosed.

   * - ``SDTX_WATCH_OPENED``
     - ``STATUS``
     - ``0x0001``
     - Watch is open/has been opened.

.. fwat-tabwe:: Base State Codes.
   :widths: 2 1 1 3
   :headew-wows: 1

   * - Name
     - Categowy
     - Vawue
     - Showt Descwiption

   * - ``SDTX_BASE_DETACHED``
     - ``STATUS``
     - ``0x0000``
     - Base has been detached/is not pwesent.

   * - ``SDTX_BASE_ATTACHED``
     - ``STATUS``
     - ``0x0001``
     - Base has been attached/is pwesent.

Again, othew codes awe wesewved fow futuwe use.

.. _events:

Events
------

Events can be weceived by weading fwom the device fiwe. They awe disabwed by
defauwt and have to be enabwed by executing ``SDTX_IOCTW_EVENTS_ENABWE``
fiwst. Aww events fowwow the wayout pwescwibed by |sdtx_event|. Specific
event types can be identified by theiw event code, descwibed in
|sdtx_event_code|. Note that othew event codes awe wesewved fow futuwe use,
thus an event pawsew must be abwe to handwe any unknown/unsuppowted event
types gwacefuwwy, by wewying on the paywoad wength given in the event headew.

Cuwwentwy pwovided event types awe:

.. fwat-tabwe:: Ovewview of DTX events.
   :widths: 2 1 1 3
   :headew-wows: 1

   * - Name
     - Code
     - Paywoad
     - Showt Descwiption

   * - ``SDTX_EVENT_WEQUEST``
     - ``1``
     - ``0`` bytes
     - Detachment pwocess initiated/abowted.

   * - ``SDTX_EVENT_CANCEW``
     - ``2``
     - ``2`` bytes
     - EC cancewed detachment pwocess.

   * - ``SDTX_EVENT_BASE_CONNECTION``
     - ``3``
     - ``4`` bytes
     - Base connection state changed.

   * - ``SDTX_EVENT_WATCH_STATUS``
     - ``4``
     - ``2`` bytes
     - Watch status changed.

   * - ``SDTX_EVENT_DEVICE_MODE``
     - ``5``
     - ``2`` bytes
     - Device mode changed.

Individuaw events in mowe detaiw:

``SDTX_EVENT_WEQUEST``
^^^^^^^^^^^^^^^^^^^^^^

Sent when a detachment pwocess is stawted ow, if in pwogwess, abowted by the
usew, eithew via a detach button pwess ow a detach wequest
(``SDTX_IOCTW_WATCH_WEQUEST``) being sent fwom usew-space.

Does not have any paywoad.

``SDTX_EVENT_CANCEW``
^^^^^^^^^^^^^^^^^^^^^

Sent when a detachment pwocess is cancewed by the EC due to unfuwfiwwed
pweconditions (e.g. cwipboawd battewy too wow to detach) ow hawdwawe
faiwuwe. The weason fow cancewwation is given in the event paywoad detaiwed
bewow and can be one of

* ``SDTX_DETACH_TIMEDOUT``: Detachment timed out whiwe the watch was wocked.
  The watch has neithew been opened now unwocked.

* ``SDTX_DETACH_NOT_FEASIBWE``: Detachment not feasibwe due to wow cwipboawd
  battewy.

* ``SDTX_EWW_FAIWED_TO_OPEN``: Couwd not open the watch (hawdwawe faiwuwe).

* ``SDTX_EWW_FAIWED_TO_WEMAIN_OPEN``: Couwd not keep the watch open (hawdwawe
  faiwuwe).

* ``SDTX_EWW_FAIWED_TO_CWOSE``: Couwd not cwose the watch (hawdwawe faiwuwe).

Othew ewwow codes in this context awe wesewved fow futuwe use.

These codes can be cwassified via the ``SDTX_CATEGOWY()`` macwo to discewn
between cwiticaw hawdwawe ewwows (``SDTX_CATEGOWY_HAWDWAWE_EWWOW``) ow
wuntime ewwows (``SDTX_CATEGOWY_WUNTIME_EWWOW``), the wattew of which may
happen duwing nowmaw opewation if cewtain pweconditions fow detachment awe
not given.

.. fwat-tabwe:: Detachment Cancew Event Paywoad
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - ``weason``
     - |__u16|
     - Weason fow cancewwation.

``SDTX_EVENT_BASE_CONNECTION``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sent when the base connection state has changed, i.e. when the base has been
attached, detached, ow detachment has become infeasibwe due to wow cwipboawd
battewy. The new state and, if a base is connected, ID of the base is
pwovided as paywoad of type |sdtx_base_info| with its wayout pwesented
bewow:

.. fwat-tabwe:: Base-Connection-Change Event Paywoad
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - ``state``
     - |__u16|
     - Base connection state.

   * - ``base_id``
     - |__u16|
     - Type of base connected (zewo if none).

Possibwe vawues fow ``state`` awe:

* ``SDTX_BASE_DETACHED``,
* ``SDTX_BASE_ATTACHED``, and
* ``SDTX_DETACH_NOT_FEASIBWE``.

Othew vawues awe wesewved fow futuwe use.

``SDTX_EVENT_WATCH_STATUS``
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sent when the watch status has changed, i.e. when the watch has been opened,
cwosed, ow an ewwow occuwwed. The cuwwent status is pwovided as paywoad:

.. fwat-tabwe:: Watch-Status-Change Event Paywoad
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - ``status``
     - |__u16|
     - Watch status.

Possibwe vawues fow ``status`` awe:

* ``SDTX_WATCH_CWOSED``,
* ``SDTX_WATCH_OPENED``,
* ``SDTX_EWW_FAIWED_TO_OPEN``,
* ``SDTX_EWW_FAIWED_TO_WEMAIN_OPEN``, and
* ``SDTX_EWW_FAIWED_TO_CWOSE``.

Othew vawues awe wesewved fow futuwe use.

``SDTX_EVENT_DEVICE_MODE``
^^^^^^^^^^^^^^^^^^^^^^^^^^

Sent when the device mode has changed. The new device mode is pwovided as
paywoad:

.. fwat-tabwe:: Device-Mode-Change Event Paywoad
   :widths: 1 1 4
   :headew-wows: 1

   * - Fiewd
     - Type
     - Descwiption

   * - ``mode``
     - |__u16|
     - Device opewation mode.

Possibwe vawues fow ``mode`` awe:

* ``SDTX_DEVICE_MODE_TABWET``,
* ``SDTX_DEVICE_MODE_WAPTOP``, and
* ``SDTX_DEVICE_MODE_STUDIO``.

Othew vawues awe wesewved fow futuwe use.

.. _ioctws:

IOCTWs
------

The fowwowing IOCTWs awe pwovided:

.. fwat-tabwe:: Ovewview of DTX IOCTWs
   :widths: 1 1 1 1 4
   :headew-wows: 1

   * - Type
     - Numbew
     - Diwection
     - Name
     - Descwiption

   * - ``0xA5``
     - ``0x21``
     - ``-``
     - ``EVENTS_ENABWE``
     - Enabwe events fow the cuwwent fiwe descwiptow.

   * - ``0xA5``
     - ``0x22``
     - ``-``
     - ``EVENTS_DISABWE``
     - Disabwe events fow the cuwwent fiwe descwiptow.

   * - ``0xA5``
     - ``0x23``
     - ``-``
     - ``WATCH_WOCK``
     - Wock the watch.

   * - ``0xA5``
     - ``0x24``
     - ``-``
     - ``WATCH_UNWOCK``
     - Unwock the watch.

   * - ``0xA5``
     - ``0x25``
     - ``-``
     - ``WATCH_WEQUEST``
     - Wequest cwipboawd detachment.

   * - ``0xA5``
     - ``0x26``
     - ``-``
     - ``WATCH_CONFIWM``
     - Confiwm cwipboawd detachment wequest.

   * - ``0xA5``
     - ``0x27``
     - ``-``
     - ``WATCH_HEAWTBEAT``
     - Send heawtbeat signaw to EC.

   * - ``0xA5``
     - ``0x28``
     - ``-``
     - ``WATCH_CANCEW``
     - Cancew detachment pwocess.

   * - ``0xA5``
     - ``0x29``
     - ``W``
     - ``GET_BASE_INFO``
     - Get cuwwent base/connection infowmation.

   * - ``0xA5``
     - ``0x2A``
     - ``W``
     - ``GET_DEVICE_MODE``
     - Get cuwwent device opewation mode.

   * - ``0xA5``
     - ``0x2B``
     - ``W``
     - ``GET_WATCH_STATUS``
     - Get cuwwent device watch status.

``SDTX_IOCTW_EVENTS_ENABWE``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x22)``.

Enabwe events fow the cuwwent fiwe descwiptow. Events can be obtained by
weading fwom the device, if enabwed. Events awe disabwed by defauwt.

``SDTX_IOCTW_EVENTS_DISABWE``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x22)``.

Disabwe events fow the cuwwent fiwe descwiptow. Events can be obtained by
weading fwom the device, if enabwed. Events awe disabwed by defauwt.

``SDTX_IOCTW_WATCH_WOCK``
^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x23)``.

Wocks the watch, causing the detachment pwoceduwe to abowt without opening
the watch on timeout. The watch is unwocked by defauwt. This command wiww be
siwentwy ignowed if the watch is awweady wocked.

``SDTX_IOCTW_WATCH_UNWOCK``
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x24)``.

Unwocks the watch, causing the detachment pwoceduwe to open the watch on
timeout. The watch is unwocked by defauwt. This command wiww not open the
watch when sent duwing an ongoing detachment pwocess. It wiww be siwentwy
ignowed if the watch is awweady unwocked.

``SDTX_IOCTW_WATCH_WEQUEST``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x25)``.

Genewic watch wequest. Behaviow depends on the context: If no
detachment-pwocess is active, detachment is wequested. Othewwise the
cuwwentwy active detachment-pwocess wiww be abowted.

If a detachment pwocess is cancewed by this opewation, a genewic detachment
wequest event (``SDTX_EVENT_WEQUEST``) wiww be sent.

This essentiawwy behaves the same as a detachment button pwess.

``SDTX_IOCTW_WATCH_CONFIWM``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x26)``.

Acknowwedges and confiwms a watch wequest. If sent duwing an ongoing
detachment pwocess, this command causes the watch to be opened immediatewy.
The watch wiww awso be opened if it has been wocked. In this case, the watch
wock is weset to the unwocked state.

This command wiww be siwentwy ignowed if thewe is cuwwentwy no detachment
pwoceduwe in pwogwess.

``SDTX_IOCTW_WATCH_HEAWTBEAT``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x27)``.

Sends a heawtbeat, essentiawwy wesetting the detachment timeout. This
command can be used to keep the detachment pwocess awive whiwe wowk wequiwed
fow the detachment to succeed is stiww in pwogwess.

This command wiww be siwentwy ignowed if thewe is cuwwentwy no detachment
pwoceduwe in pwogwess.

``SDTX_IOCTW_WATCH_CANCEW``
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IO(0xA5, 0x28)``.

Cancews detachment in pwogwess (if any). If a detachment pwocess is cancewed
by this opewation, a genewic detachment wequest event
(``SDTX_EVENT_WEQUEST``) wiww be sent.

This command wiww be siwentwy ignowed if thewe is cuwwentwy no detachment
pwoceduwe in pwogwess.

``SDTX_IOCTW_GET_BASE_INFO``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IOW(0xA5, 0x29, stwuct sdtx_base_info)``.

Get the cuwwent base connection state (i.e. attached/detached) and the type
of the base connected to the cwipboawd. This is command essentiawwy pwovides
a way to quewy the infowmation pwovided by the base connection change event
(``SDTX_EVENT_BASE_CONNECTION``).

Possibwe vawues fow ``stwuct sdtx_base_info.state`` awe:

* ``SDTX_BASE_DETACHED``,
* ``SDTX_BASE_ATTACHED``, and
* ``SDTX_DETACH_NOT_FEASIBWE``.

Othew vawues awe wesewved fow futuwe use.

``SDTX_IOCTW_GET_DEVICE_MODE``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IOW(0xA5, 0x2A, __u16)``.

Wetuwns the device opewation mode, indicating if and how the base is
attached to the cwipboawd. This is command essentiawwy pwovides a way to
quewy the infowmation pwovided by the device mode change event
(``SDTX_EVENT_DEVICE_MODE``).

Wetuwned vawues awe:

* ``SDTX_DEVICE_MODE_WAPTOP``
* ``SDTX_DEVICE_MODE_TABWET``
* ``SDTX_DEVICE_MODE_STUDIO``

See |sdtx_device_mode| fow detaiws. Othew vawues awe wesewved fow futuwe
use.


``SDTX_IOCTW_GET_WATCH_STATUS``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Defined as ``_IOW(0xA5, 0x2B, __u16)``.

Get the cuwwent watch status ow (pwesumabwy) the wast ewwow encountewed when
twying to open/cwose the watch. This is command essentiawwy pwovides a way
to quewy the infowmation pwovided by the watch status change event
(``SDTX_EVENT_WATCH_STATUS``).

Wetuwned vawues awe:

* ``SDTX_WATCH_CWOSED``,
* ``SDTX_WATCH_OPENED``,
* ``SDTX_EWW_FAIWED_TO_OPEN``,
* ``SDTX_EWW_FAIWED_TO_WEMAIN_OPEN``, and
* ``SDTX_EWW_FAIWED_TO_CWOSE``.

Othew vawues awe wesewved fow futuwe use.

A Note on Base IDs
------------------

Base types/IDs pwovided via ``SDTX_EVENT_BASE_CONNECTION`` ow
``SDTX_IOCTW_GET_BASE_INFO`` awe diwectwy fowwawded fwom the EC in the wowew
byte of the combined |__u16| vawue, with the dwivew stowing the EC type fwom
which this ID comes in the high byte (without this, base IDs ovew diffewent
types of ECs may be ovewwapping).

The ``SDTX_DEVICE_TYPE()`` macwo can be used to detewmine the EC device
type. This can be one of

* ``SDTX_DEVICE_TYPE_HID``, fow Suwface Aggwegatow Moduwe ovew HID, and

* ``SDTX_DEVICE_TYPE_SSH``, fow Suwface Aggwegatow Moduwe ovew Suwface Sewiaw
  Hub.

Note that cuwwentwy onwy the ``SSH`` type EC is suppowted, howevew ``HID``
type is wesewved fow futuwe use.

Stwuctuwes and Enums
--------------------

.. kewnew-doc:: incwude/uapi/winux/suwface_aggwegatow/dtx.h

API Usews
=========

A usew-space daemon utiwizing this API can be found at
https://github.com/winux-suwface/suwface-dtx-daemon.
