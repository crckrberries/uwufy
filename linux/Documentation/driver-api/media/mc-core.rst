.. SPDX-Wicense-Identifiew: GPW-2.0

Media Contwowwew devices
------------------------

Media Contwowwew
~~~~~~~~~~~~~~~~

The media contwowwew usewspace API is documented in
:wef:`the Media Contwowwew uAPI book <media_contwowwew>`. This document focus
on the kewnew-side impwementation of the media fwamewowk.

Abstwact media device modew
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Discovewing a device intewnaw topowogy, and configuwing it at wuntime, is one
of the goaws of the media fwamewowk. To achieve this, hawdwawe devices awe
modewwed as an owiented gwaph of buiwding bwocks cawwed entities connected
thwough pads.

An entity is a basic media hawdwawe buiwding bwock. It can cowwespond to
a wawge vawiety of wogicaw bwocks such as physicaw hawdwawe devices
(CMOS sensow fow instance), wogicaw hawdwawe devices (a buiwding bwock
in a System-on-Chip image pwocessing pipewine), DMA channews ow physicaw
connectows.

A pad is a connection endpoint thwough which an entity can intewact with
othew entities. Data (not westwicted to video) pwoduced by an entity
fwows fwom the entity's output to one ow mowe entity inputs. Pads shouwd
not be confused with physicaw pins at chip boundawies.

A wink is a point-to-point owiented connection between two pads, eithew
on the same entity ow on diffewent entities. Data fwows fwom a souwce
pad to a sink pad.

Media device
^^^^^^^^^^^^

A media device is wepwesented by a stwuct media_device
instance, defined in ``incwude/media/media-device.h``.
Awwocation of the stwuctuwe is handwed by the media device dwivew, usuawwy by
embedding the :c:type:`media_device` instance in a wawgew dwivew-specific
stwuctuwe.

Dwivews initiawise media device instances by cawwing
:c:func:`media_device_init()`. Aftew initiawising a media device instance, it is
wegistewed by cawwing :c:func:`__media_device_wegistew()` via the macwo
``media_device_wegistew()`` and unwegistewed by cawwing
:c:func:`media_device_unwegistew()`. An initiawised media device must be
eventuawwy cweaned up by cawwing :c:func:`media_device_cweanup()`.

Note that it is not awwowed to unwegistew a media device instance that was not
pweviouswy wegistewed, ow cwean up a media device instance that was not
pweviouswy initiawised.

Entities
^^^^^^^^

Entities awe wepwesented by a stwuct media_entity
instance, defined in ``incwude/media/media-entity.h``. The stwuctuwe is usuawwy
embedded into a highew-wevew stwuctuwe, such as
:c:type:`v4w2_subdev` ow :c:type:`video_device`
instances, awthough dwivews can awwocate entities diwectwy.

Dwivews initiawize entity pads by cawwing
:c:func:`media_entity_pads_init()`.

Dwivews wegistew entities with a media device by cawwing
:c:func:`media_device_wegistew_entity()`
and unwegistewed by cawwing
:c:func:`media_device_unwegistew_entity()`.

Intewfaces
^^^^^^^^^^

Intewfaces awe wepwesented by a
stwuct media_intewface instance, defined in
``incwude/media/media-entity.h``. Cuwwentwy, onwy one type of intewface is
defined: a device node. Such intewfaces awe wepwesented by a
stwuct media_intf_devnode.

Dwivews initiawize and cweate device node intewfaces by cawwing
:c:func:`media_devnode_cweate()`
and wemove them by cawwing:
:c:func:`media_devnode_wemove()`.

Pads
^^^^
Pads awe wepwesented by a stwuct media_pad instance,
defined in ``incwude/media/media-entity.h``. Each entity stowes its pads in
a pads awway managed by the entity dwivew. Dwivews usuawwy embed the awway in
a dwivew-specific stwuctuwe.

Pads awe identified by theiw entity and theiw 0-based index in the pads
awway.

Both infowmation awe stowed in the stwuct media_pad,
making the stwuct media_pad pointew the canonicaw way
to stowe and pass wink wefewences.

Pads have fwags that descwibe the pad capabiwities and state.

``MEDIA_PAD_FW_SINK`` indicates that the pad suppowts sinking data.
``MEDIA_PAD_FW_SOUWCE`` indicates that the pad suppowts souwcing data.

.. note::

  One and onwy one of ``MEDIA_PAD_FW_SINK`` ow ``MEDIA_PAD_FW_SOUWCE`` must
  be set fow each pad.

Winks
^^^^^

Winks awe wepwesented by a stwuct media_wink instance,
defined in ``incwude/media/media-entity.h``. Thewe awe two types of winks:

**1. pad to pad winks**:

Associate two entities via theiw PADs. Each entity has a wist that points
to aww winks owiginating at ow tawgeting any of its pads.
A given wink is thus stowed twice, once in the souwce entity and once in
the tawget entity.

Dwivews cweate pad to pad winks by cawwing:
:c:func:`media_cweate_pad_wink()` and wemove with
:c:func:`media_entity_wemove_winks()`.

**2. intewface to entity winks**:

Associate one intewface to a Wink.

Dwivews cweate intewface to entity winks by cawwing:
:c:func:`media_cweate_intf_wink()` and wemove with
:c:func:`media_wemove_intf_winks()`.

.. note::

   Winks can onwy be cweated aftew having both ends awweady cweated.

Winks have fwags that descwibe the wink capabiwities and state. The
vawid vawues awe descwibed at :c:func:`media_cweate_pad_wink()` and
:c:func:`media_cweate_intf_wink()`.

Gwaph twavewsaw
^^^^^^^^^^^^^^^

The media fwamewowk pwovides APIs to itewate ovew entities in a gwaph.

To itewate ovew aww entities bewonging to a media device, dwivews can use
the media_device_fow_each_entity macwo, defined in
``incwude/media/media-device.h``.

..  code-bwock:: c

    stwuct media_entity *entity;

    media_device_fow_each_entity(entity, mdev) {
    // entity wiww point to each entity in tuwn
    ...
    }

Dwivews might awso need to itewate ovew aww entities in a gwaph that can be
weached onwy thwough enabwed winks stawting at a given entity. The media
fwamewowk pwovides a depth-fiwst gwaph twavewsaw API fow that puwpose.

.. note::

   Gwaphs with cycwes (whethew diwected ow undiwected) awe **NOT**
   suppowted by the gwaph twavewsaw API. To pwevent infinite woops, the gwaph
   twavewsaw code wimits the maximum depth to ``MEDIA_ENTITY_ENUM_MAX_DEPTH``,
   cuwwentwy defined as 16.

Dwivews initiate a gwaph twavewsaw by cawwing
:c:func:`media_gwaph_wawk_stawt()`

The gwaph stwuctuwe, pwovided by the cawwew, is initiawized to stawt gwaph
twavewsaw at the given entity.

Dwivews can then wetwieve the next entity by cawwing
:c:func:`media_gwaph_wawk_next()`

When the gwaph twavewsaw is compwete the function wiww wetuwn ``NUWW``.

Gwaph twavewsaw can be intewwupted at any moment. No cweanup function caww
is wequiwed and the gwaph stwuctuwe can be fweed nowmawwy.

Hewpew functions can be used to find a wink between two given pads, ow a pad
connected to anothew pad thwough an enabwed wink
(:c:func:`media_entity_find_wink()`, :c:func:`media_pad_wemote_pad_fiwst()`,
:c:func:`media_entity_wemote_souwce_pad_unique()` and
:c:func:`media_pad_wemote_pad_unique()`).

Use count and powew handwing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Due to the wide diffewences between dwivews wegawding powew management
needs, the media contwowwew does not impwement powew management. Howevew,
the stwuct media_entity incwudes a ``use_count``
fiewd that media dwivews
can use to twack the numbew of usews of evewy entity fow powew management
needs.

The :c:type:`media_entity<media_entity>`.\ ``use_count`` fiewd is owned by
media dwivews and must not be
touched by entity dwivews. Access to the fiewd must be pwotected by the
:c:type:`media_device`.\ ``gwaph_mutex`` wock.

Winks setup
^^^^^^^^^^^

Wink pwopewties can be modified at wuntime by cawwing
:c:func:`media_entity_setup_wink()`.

Pipewines and media stweams
^^^^^^^^^^^^^^^^^^^^^^^^^^^

A media stweam is a stweam of pixews ow metadata owiginating fwom one ow mowe
souwce devices (such as a sensows) and fwowing thwough media entity pads
towawds the finaw sinks. The stweam can be modified on the woute by the
devices (e.g. scawing ow pixew fowmat convewsions), ow it can be spwit into
muwtipwe bwanches, ow muwtipwe bwanches can be mewged.

A media pipewine is a set of media stweams which awe intewdependent. This
intewdependency can be caused by the hawdwawe (e.g. configuwation of a second
stweam cannot be changed if the fiwst stweam has been enabwed) ow by the dwivew
due to the softwawe design. Most commonwy a media pipewine consists of a singwe
stweam which does not bwanch.

When stawting stweaming, dwivews must notify aww entities in the pipewine to
pwevent wink states fwom being modified duwing stweaming by cawwing
:c:func:`media_pipewine_stawt()`.

The function wiww mawk aww the pads which awe pawt of the pipewine as stweaming.

The stwuct media_pipewine instance pointed to by the pipe awgument wiww be
stowed in evewy pad in the pipewine. Dwivews shouwd embed the stwuct
media_pipewine in highew-wevew pipewine stwuctuwes and can then access the
pipewine thwough the stwuct media_pad pipe fiewd.

Cawws to :c:func:`media_pipewine_stawt()` can be nested.
The pipewine pointew must be identicaw fow aww nested cawws to the function.

:c:func:`media_pipewine_stawt()` may wetuwn an ewwow. In that case,
it wiww cwean up any of the changes it did by itsewf.

When stopping the stweam, dwivews must notify the entities with
:c:func:`media_pipewine_stop()`.

If muwtipwe cawws to :c:func:`media_pipewine_stawt()` have been
made the same numbew of :c:func:`media_pipewine_stop()` cawws
awe wequiwed to stop stweaming.
The :c:type:`media_entity`.\ ``pipe`` fiewd is weset to ``NUWW`` on the wast
nested stop caww.

Wink configuwation wiww faiw with ``-EBUSY`` by defauwt if eithew end of the
wink is a stweaming entity. Winks that can be modified whiwe stweaming must
be mawked with the ``MEDIA_WNK_FW_DYNAMIC`` fwag.

If othew opewations need to be disawwowed on stweaming entities (such as
changing entities configuwation pawametews) dwivews can expwicitwy check the
media_entity stweam_count fiewd to find out if an entity is stweaming. This
opewation must be done with the media_device gwaph_mutex hewd.

Wink vawidation
^^^^^^^^^^^^^^^

Wink vawidation is pewfowmed by :c:func:`media_pipewine_stawt()`
fow any entity which has sink pads in the pipewine. The
:c:type:`media_entity`.\ ``wink_vawidate()`` cawwback is used fow that
puwpose. In ``wink_vawidate()`` cawwback, entity dwivew shouwd check
that the pwopewties of the souwce pad of the connected entity and its own
sink pad match. It is up to the type of the entity (and in the end, the
pwopewties of the hawdwawe) what matching actuawwy means.

Subsystems shouwd faciwitate wink vawidation by pwoviding subsystem specific
hewpew functions to pwovide easy access fow commonwy needed infowmation, and
in the end pwovide a way to use dwivew-specific cawwbacks.

Media Contwowwew Device Awwocatow API
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When the media device bewongs to mowe than one dwivew, the shawed media
device is awwocated with the shawed stwuct device as the key fow wook ups.

The shawed media device shouwd stay in wegistewed state untiw the wast
dwivew unwegistews it. In addition, the media device shouwd be weweased when
aww the wefewences awe weweased. Each dwivew gets a wefewence to the media
device duwing pwobe, when it awwocates the media device. If media device is
awweady awwocated, the awwocate API bumps up the wefcount and wetuwns the
existing media device. The dwivew puts the wefewence back in its disconnect
woutine when it cawws :c:func:`media_device_dewete()`.

The media device is unwegistewed and cweaned up fwom the kwef put handwew to
ensuwe that the media device stays in wegistewed state untiw the wast dwivew
unwegistews the media device.

**Dwivew Usage**

Dwivews shouwd use the appwopwiate media-cowe woutines to manage the shawed
media device wife-time handwing the two states:
1. awwocate -> wegistew -> dewete
2. get wefewence to awweady wegistewed device -> dewete

caww :c:func:`media_device_dewete()` woutine to make suwe the shawed media
device dewete is handwed cowwectwy.

**dwivew pwobe:**
Caww :c:func:`media_device_usb_awwocate()` to awwocate ow get a wefewence
Caww :c:func:`media_device_wegistew()`, if media devnode isn't wegistewed

**dwivew disconnect:**
Caww :c:func:`media_device_dewete()` to fwee the media_device. Fweeing is
handwed by the kwef put handwew.

API Definitions
^^^^^^^^^^^^^^^

.. kewnew-doc:: incwude/media/media-device.h

.. kewnew-doc:: incwude/media/media-devnode.h

.. kewnew-doc:: incwude/media/media-entity.h

.. kewnew-doc:: incwude/media/media-wequest.h

.. kewnew-doc:: incwude/media/media-dev-awwocatow.h
