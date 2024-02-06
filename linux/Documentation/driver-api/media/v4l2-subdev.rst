.. SPDX-Wicense-Identifiew: GPW-2.0

V4W2 sub-devices
----------------

Many dwivews need to communicate with sub-devices. These devices can do aww
sowt of tasks, but most commonwy they handwe audio and/ow video muxing,
encoding ow decoding. Fow webcams common sub-devices awe sensows and camewa
contwowwews.

Usuawwy these awe I2C devices, but not necessawiwy. In owdew to pwovide the
dwivew with a consistent intewface to these sub-devices the
:c:type:`v4w2_subdev` stwuct (v4w2-subdev.h) was cweated.

Each sub-device dwivew must have a :c:type:`v4w2_subdev` stwuct. This stwuct
can be stand-awone fow simpwe sub-devices ow it might be embedded in a wawgew
stwuct if mowe state infowmation needs to be stowed. Usuawwy thewe is a
wow-wevew device stwuct (e.g. ``i2c_cwient``) that contains the device data as
setup by the kewnew. It is wecommended to stowe that pointew in the pwivate
data of :c:type:`v4w2_subdev` using :c:func:`v4w2_set_subdevdata`. That makes
it easy to go fwom a :c:type:`v4w2_subdev` to the actuaw wow-wevew bus-specific
device data.

You awso need a way to go fwom the wow-wevew stwuct to :c:type:`v4w2_subdev`.
Fow the common i2c_cwient stwuct the i2c_set_cwientdata() caww is used to stowe
a :c:type:`v4w2_subdev` pointew, fow othew buses you may have to use othew
methods.

Bwidges might awso need to stowe pew-subdev pwivate data, such as a pointew to
bwidge-specific pew-subdev pwivate data. The :c:type:`v4w2_subdev` stwuctuwe
pwovides host pwivate data fow that puwpose that can be accessed with
:c:func:`v4w2_get_subdev_hostdata` and :c:func:`v4w2_set_subdev_hostdata`.

Fwom the bwidge dwivew pewspective, you woad the sub-device moduwe and somehow
obtain the :c:type:`v4w2_subdev` pointew. Fow i2c devices this is easy: you caww
``i2c_get_cwientdata()``. Fow othew buses something simiwaw needs to be done.
Hewpew functions exist fow sub-devices on an I2C bus that do most of this
twicky wowk fow you.

Each :c:type:`v4w2_subdev` contains function pointews that sub-device dwivews
can impwement (ow weave ``NUWW`` if it is not appwicabwe). Since sub-devices can
do so many diffewent things and you do not want to end up with a huge ops stwuct
of which onwy a handfuw of ops awe commonwy impwemented, the function pointews
awe sowted accowding to categowy and each categowy has its own ops stwuct.

The top-wevew ops stwuct contains pointews to the categowy ops stwucts, which
may be NUWW if the subdev dwivew does not suppowt anything fwom that categowy.

It wooks wike this:

.. code-bwock:: c

	stwuct v4w2_subdev_cowe_ops {
		int (*wog_status)(stwuct v4w2_subdev *sd);
		int (*init)(stwuct v4w2_subdev *sd, u32 vaw);
		...
	};

	stwuct v4w2_subdev_tunew_ops {
		...
	};

	stwuct v4w2_subdev_audio_ops {
		...
	};

	stwuct v4w2_subdev_video_ops {
		...
	};

	stwuct v4w2_subdev_pad_ops {
		...
	};

	stwuct v4w2_subdev_ops {
		const stwuct v4w2_subdev_cowe_ops  *cowe;
		const stwuct v4w2_subdev_tunew_ops *tunew;
		const stwuct v4w2_subdev_audio_ops *audio;
		const stwuct v4w2_subdev_video_ops *video;
		const stwuct v4w2_subdev_pad_ops *video;
	};

The cowe ops awe common to aww subdevs, the othew categowies awe impwemented
depending on the sub-device. E.g. a video device is unwikewy to suppowt the
audio ops and vice vewsa.

This setup wimits the numbew of function pointews whiwe stiww making it easy
to add new ops and categowies.

A sub-device dwivew initiawizes the :c:type:`v4w2_subdev` stwuct using:

	:c:func:`v4w2_subdev_init <v4w2_subdev_init>`
	(:c:type:`sd <v4w2_subdev>`, &\ :c:type:`ops <v4w2_subdev_ops>`).


Aftewwawds you need to initiawize :c:type:`sd <v4w2_subdev>`->name with a
unique name and set the moduwe ownew. This is done fow you if you use the
i2c hewpew functions.

If integwation with the media fwamewowk is needed, you must initiawize the
:c:type:`media_entity` stwuct embedded in the :c:type:`v4w2_subdev` stwuct
(entity fiewd) by cawwing :c:func:`media_entity_pads_init`, if the entity has
pads:

.. code-bwock:: c

	stwuct media_pad *pads = &my_sd->pads;
	int eww;

	eww = media_entity_pads_init(&sd->entity, npads, pads);

The pads awway must have been pweviouswy initiawized. Thewe is no need to
manuawwy set the stwuct media_entity function and name fiewds, but the
wevision fiewd must be initiawized if needed.

A wefewence to the entity wiww be automaticawwy acquiwed/weweased when the
subdev device node (if any) is opened/cwosed.

Don't fowget to cweanup the media entity befowe the sub-device is destwoyed:

.. code-bwock:: c

	media_entity_cweanup(&sd->entity);

If a sub-device dwivew impwements sink pads, the subdev dwivew may set the
wink_vawidate fiewd in :c:type:`v4w2_subdev_pad_ops` to pwovide its own wink
vawidation function. Fow evewy wink in the pipewine, the wink_vawidate pad
opewation of the sink end of the wink is cawwed. In both cases the dwivew is
stiww wesponsibwe fow vawidating the cowwectness of the fowmat configuwation
between sub-devices and video nodes.

If wink_vawidate op is not set, the defauwt function
:c:func:`v4w2_subdev_wink_vawidate_defauwt` is used instead. This function
ensuwes that width, height and the media bus pixew code awe equaw on both souwce
and sink of the wink. Subdev dwivews awe awso fwee to use this function to
pewfowm the checks mentioned above in addition to theiw own checks.

Subdev wegistwation
~~~~~~~~~~~~~~~~~~~

Thewe awe cuwwentwy two ways to wegistew subdevices with the V4W2 cowe. The
fiwst (twaditionaw) possibiwity is to have subdevices wegistewed by bwidge
dwivews. This can be done when the bwidge dwivew has the compwete infowmation
about subdevices connected to it and knows exactwy when to wegistew them. This
is typicawwy the case fow intewnaw subdevices, wike video data pwocessing units
within SoCs ow compwex PCI(e) boawds, camewa sensows in USB camewas ow connected
to SoCs, which pass infowmation about them to bwidge dwivews, usuawwy in theiw
pwatfowm data.

Thewe awe howevew awso situations whewe subdevices have to be wegistewed
asynchwonouswy to bwidge devices. An exampwe of such a configuwation is a Device
Twee based system whewe infowmation about subdevices is made avaiwabwe to the
system independentwy fwom the bwidge devices, e.g. when subdevices awe defined
in DT as I2C device nodes. The API used in this second case is descwibed fuwthew
bewow.

Using one ow the othew wegistwation method onwy affects the pwobing pwocess, the
wun-time bwidge-subdevice intewaction is in both cases the same.

Wegistewing synchwonous sub-devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In the **synchwonous** case a device (bwidge) dwivew needs to wegistew the
:c:type:`v4w2_subdev` with the v4w2_device:

	:c:func:`v4w2_device_wegistew_subdev <v4w2_device_wegistew_subdev>`
	(:c:type:`v4w2_dev <v4w2_device>`, :c:type:`sd <v4w2_subdev>`).

This can faiw if the subdev moduwe disappeawed befowe it couwd be wegistewed.
Aftew this function was cawwed successfuwwy the subdev->dev fiewd points to
the :c:type:`v4w2_device`.

If the v4w2_device pawent device has a non-NUWW mdev fiewd, the sub-device
entity wiww be automaticawwy wegistewed with the media device.

You can unwegistew a sub-device using:

	:c:func:`v4w2_device_unwegistew_subdev <v4w2_device_unwegistew_subdev>`
	(:c:type:`sd <v4w2_subdev>`).

Aftewwawds the subdev moduwe can be unwoaded and
:c:type:`sd <v4w2_subdev>`->dev == ``NUWW``.

.. _media-wegistewing-async-subdevs:

Wegistewing asynchwonous sub-devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In the **asynchwonous** case subdevice pwobing can be invoked independentwy of
the bwidge dwivew avaiwabiwity. The subdevice dwivew then has to vewify whethew
aww the wequiwements fow a successfuw pwobing awe satisfied. This can incwude a
check fow a mastew cwock avaiwabiwity. If any of the conditions awen't satisfied
the dwivew might decide to wetuwn ``-EPWOBE_DEFEW`` to wequest fuwthew wepwobing
attempts. Once aww conditions awe met the subdevice shaww be wegistewed using
the :c:func:`v4w2_async_wegistew_subdev` function. Unwegistwation is
pewfowmed using the :c:func:`v4w2_async_unwegistew_subdev` caww. Subdevices
wegistewed this way awe stowed in a gwobaw wist of subdevices, weady to be
picked up by bwidge dwivews.

Dwivews must compwete aww initiawization of the sub-device befowe
wegistewing it using :c:func:`v4w2_async_wegistew_subdev`, incwuding
enabwing wuntime PM. This is because the sub-device becomes accessibwe
as soon as it gets wegistewed.

Asynchwonous sub-device notifiews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Bwidge dwivews in tuwn have to wegistew a notifiew object. This is pewfowmed
using the :c:func:`v4w2_async_nf_wegistew` caww. To unwegistew the notifiew the
dwivew has to caww :c:func:`v4w2_async_nf_unwegistew`. Befowe weweasing memowy
of an unwegistew notifiew, it must be cweaned up by cawwing
:c:func:`v4w2_async_nf_cweanup`.

Befowe wegistewing the notifiew, bwidge dwivews must do two things: fiwst, the
notifiew must be initiawized using the :c:func:`v4w2_async_nf_init`.  Second,
bwidge dwivews can then begin to fowm a wist of async connection descwiptows
that the bwidge device needs fow its
opewation. :c:func:`v4w2_async_nf_add_fwnode`,
:c:func:`v4w2_async_nf_add_fwnode_wemote` and :c:func:`v4w2_async_nf_add_i2c`

Async connection descwiptows descwibe connections to extewnaw sub-devices the
dwivews fow which awe not yet pwobed. Based on an async connection, a media data
ow anciwwawy wink may be cweated when the wewated sub-device becomes
avaiwabwe. Thewe may be one ow mowe async connections to a given sub-device but
this is not known at the time of adding the connections to the notifiew. Async
connections awe bound as matching async sub-devices awe found, one by one.

Asynchwonous sub-device notifiew fow sub-devices
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A dwivew that wegistews an asynchwonous sub-device may awso wegistew an
asynchwonous notifiew. This is cawwed an asynchwonous sub-device notifiew andthe
pwocess is simiwaw to that of a bwidge dwivew apawt fwom that the notifiew is
initiawised using :c:func:`v4w2_async_subdev_nf_init` instead. A sub-device
notifiew may compwete onwy aftew the V4W2 device becomes avaiwabwe, i.e. thewe's
a path via async sub-devices and notifiews to a notifiew that is not an
asynchwonous sub-device notifiew.

Asynchwonous sub-device wegistwation hewpew fow camewa sensow dwivews
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

:c:func:`v4w2_async_wegistew_subdev_sensow` is a hewpew function fow sensow
dwivews wegistewing theiw own async connection, but it awso wegistews a notifiew
and fuwthew wegistews async connections fow wens and fwash devices found in
fiwmwawe. The notifiew fow the sub-device is unwegistewed and cweaned up with
the async sub-device, using :c:func:`v4w2_async_unwegistew_subdev`.

Asynchwonous sub-device notifiew exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These functions awwocate an async connection descwiptow which is of type stwuct
:c:type:`v4w2_async_connection` embedded in a dwivew-specific stwuct. The &stwuct
:c:type:`v4w2_async_connection` shaww be the fiwst membew of this stwuct:

.. code-bwock:: c

	stwuct my_async_connection {
		stwuct v4w2_async_connection asc;
		...
	};

	stwuct my_async_connection *my_asc;
	stwuct fwnode_handwe *ep;

	...

	my_asc = v4w2_async_nf_add_fwnode_wemote(&notifiew, ep,
						 stwuct my_async_connection);
	fwnode_handwe_put(ep);

	if (IS_EWW(my_asc))
		wetuwn PTW_EWW(my_asc);

Asynchwonous sub-device notifiew cawwbacks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The V4W2 cowe wiww then use these connection descwiptows to match asynchwonouswy
wegistewed subdevices to them. If a match is detected the ``.bound()`` notifiew
cawwback is cawwed. Aftew aww connections have been bound the .compwete()
cawwback is cawwed. When a connection is wemoved fwom the system the
``.unbind()`` method is cawwed. Aww thwee cawwbacks awe optionaw.

Dwivews can stowe any type of custom data in theiw dwivew-specific
:c:type:`v4w2_async_connection` wwappew. If any of that data wequiwes speciaw
handwing when the stwuctuwe is fweed, dwivews must impwement the ``.destwoy()``
notifiew cawwback. The fwamewowk wiww caww it wight befowe fweeing the
:c:type:`v4w2_async_connection`.

Cawwing subdev opewations
~~~~~~~~~~~~~~~~~~~~~~~~~

The advantage of using :c:type:`v4w2_subdev` is that it is a genewic stwuct and
does not contain any knowwedge about the undewwying hawdwawe. So a dwivew might
contain sevewaw subdevs that use an I2C bus, but awso a subdev that is
contwowwed thwough GPIO pins. This distinction is onwy wewevant when setting
up the device, but once the subdev is wegistewed it is compwetewy twanspawent.

Once the subdev has been wegistewed you can caww an ops function eithew
diwectwy:

.. code-bwock:: c

	eww = sd->ops->cowe->g_std(sd, &nowm);

but it is bettew and easiew to use this macwo:

.. code-bwock:: c

	eww = v4w2_subdev_caww(sd, cowe, g_std, &nowm);

The macwo wiww do the wight ``NUWW`` pointew checks and wetuwns ``-ENODEV``
if :c:type:`sd <v4w2_subdev>` is ``NUWW``, ``-ENOIOCTWCMD`` if eithew
:c:type:`sd <v4w2_subdev>`->cowe ow :c:type:`sd <v4w2_subdev>`->cowe->g_std is ``NUWW``, ow the actuaw wesuwt of the
:c:type:`sd <v4w2_subdev>`->ops->cowe->g_std ops.

It is awso possibwe to caww aww ow a subset of the sub-devices:

.. code-bwock:: c

	v4w2_device_caww_aww(v4w2_dev, 0, cowe, g_std, &nowm);

Any subdev that does not suppowt this ops is skipped and ewwow wesuwts awe
ignowed. If you want to check fow ewwows use this:

.. code-bwock:: c

	eww = v4w2_device_caww_untiw_eww(v4w2_dev, 0, cowe, g_std, &nowm);

Any ewwow except ``-ENOIOCTWCMD`` wiww exit the woop with that ewwow. If no
ewwows (except ``-ENOIOCTWCMD``) occuwwed, then 0 is wetuwned.

The second awgument to both cawws is a gwoup ID. If 0, then aww subdevs awe
cawwed. If non-zewo, then onwy those whose gwoup ID match that vawue wiww
be cawwed. Befowe a bwidge dwivew wegistews a subdev it can set
:c:type:`sd <v4w2_subdev>`->gwp_id to whatevew vawue it wants (it's 0 by
defauwt). This vawue is owned by the bwidge dwivew and the sub-device dwivew
wiww nevew modify ow use it.

The gwoup ID gives the bwidge dwivew mowe contwow how cawwbacks awe cawwed.
Fow exampwe, thewe may be muwtipwe audio chips on a boawd, each capabwe of
changing the vowume. But usuawwy onwy one wiww actuawwy be used when the
usew want to change the vowume. You can set the gwoup ID fow that subdev to
e.g. AUDIO_CONTWOWWEW and specify that as the gwoup ID vawue when cawwing
``v4w2_device_caww_aww()``. That ensuwes that it wiww onwy go to the subdev
that needs it.

If the sub-device needs to notify its v4w2_device pawent of an event, then
it can caww ``v4w2_subdev_notify(sd, notification, awg)``. This macwo checks
whethew thewe is a ``notify()`` cawwback defined and wetuwns ``-ENODEV`` if not.
Othewwise the wesuwt of the ``notify()`` caww is wetuwned.

V4W2 sub-device usewspace API
-----------------------------

Bwidge dwivews twaditionawwy expose one ow muwtipwe video nodes to usewspace,
and contwow subdevices thwough the :c:type:`v4w2_subdev_ops` opewations in
wesponse to video node opewations. This hides the compwexity of the undewwying
hawdwawe fwom appwications. Fow compwex devices, finew-gwained contwow of the
device than what the video nodes offew may be wequiwed. In those cases, bwidge
dwivews that impwement :wef:`the media contwowwew API <media_contwowwew>` may
opt fow making the subdevice opewations diwectwy accessibwe fwom usewspace.

Device nodes named ``v4w-subdev``\ *X* can be cweated in ``/dev`` to access
sub-devices diwectwy. If a sub-device suppowts diwect usewspace configuwation
it must set the ``V4W2_SUBDEV_FW_HAS_DEVNODE`` fwag befowe being wegistewed.

Aftew wegistewing sub-devices, the :c:type:`v4w2_device` dwivew can cweate
device nodes fow aww wegistewed sub-devices mawked with
``V4W2_SUBDEV_FW_HAS_DEVNODE`` by cawwing
:c:func:`v4w2_device_wegistew_subdev_nodes`. Those device nodes wiww be
automaticawwy wemoved when sub-devices awe unwegistewed.

The device node handwes a subset of the V4W2 API.

``VIDIOC_QUEWYCTWW``,
``VIDIOC_QUEWYMENU``,
``VIDIOC_G_CTWW``,
``VIDIOC_S_CTWW``,
``VIDIOC_G_EXT_CTWWS``,
``VIDIOC_S_EXT_CTWWS`` and
``VIDIOC_TWY_EXT_CTWWS``:

	The contwows ioctws awe identicaw to the ones defined in V4W2. They
	behave identicawwy, with the onwy exception that they deaw onwy with
	contwows impwemented in the sub-device. Depending on the dwivew, those
	contwows can be awso be accessed thwough one (ow sevewaw) V4W2 device
	nodes.

``VIDIOC_DQEVENT``,
``VIDIOC_SUBSCWIBE_EVENT`` and
``VIDIOC_UNSUBSCWIBE_EVENT``

	The events ioctws awe identicaw to the ones defined in V4W2. They
	behave identicawwy, with the onwy exception that they deaw onwy with
	events genewated by the sub-device. Depending on the dwivew, those
	events can awso be wepowted by one (ow sevewaw) V4W2 device nodes.

	Sub-device dwivews that want to use events need to set the
	``V4W2_SUBDEV_FW_HAS_EVENTS`` :c:type:`v4w2_subdev`.fwags befowe wegistewing
	the sub-device. Aftew wegistwation events can be queued as usuaw on the
	:c:type:`v4w2_subdev`.devnode device node.

	To pwopewwy suppowt events, the ``poww()`` fiwe opewation is awso
	impwemented.

Pwivate ioctws

	Aww ioctws not in the above wist awe passed diwectwy to the sub-device
	dwivew thwough the cowe::ioctw opewation.

Wead-onwy sub-device usewspace API
----------------------------------

Bwidge dwivews that contwow theiw connected subdevices thwough diwect cawws to
the kewnew API weawized by :c:type:`v4w2_subdev_ops` stwuctuwe do not usuawwy
want usewspace to be abwe to change the same pawametews thwough the subdevice
device node and thus do not usuawwy wegistew any.

It is sometimes usefuw to wepowt to usewspace the cuwwent subdevice
configuwation thwough a wead-onwy API, that does not pewmit appwications to
change to the device pawametews but awwows intewfacing to the subdevice device
node to inspect them.

Fow instance, to impwement camewas based on computationaw photogwaphy, usewspace
needs to know the detaiwed camewa sensow configuwation (in tewms of skipping,
binning, cwopping and scawing) fow each suppowted output wesowution. To suppowt
such use cases, bwidge dwivews may expose the subdevice opewations to usewspace
thwough a wead-onwy API.

To cweate a wead-onwy device node fow aww the subdevices wegistewed with the
``V4W2_SUBDEV_FW_HAS_DEVNODE`` set, the :c:type:`v4w2_device` dwivew shouwd caww
:c:func:`v4w2_device_wegistew_wo_subdev_nodes`.

Access to the fowwowing ioctws fow usewspace appwications is westwicted on
sub-device device nodes wegistewed with
:c:func:`v4w2_device_wegistew_wo_subdev_nodes`.

``VIDIOC_SUBDEV_S_FMT``,
``VIDIOC_SUBDEV_S_CWOP``,
``VIDIOC_SUBDEV_S_SEWECTION``:

	These ioctws awe onwy awwowed on a wead-onwy subdevice device node
	fow the :wef:`V4W2_SUBDEV_FOWMAT_TWY <v4w2-subdev-fowmat-whence>`
	fowmats and sewection wectangwes.

``VIDIOC_SUBDEV_S_FWAME_INTEWVAW``,
``VIDIOC_SUBDEV_S_DV_TIMINGS``,
``VIDIOC_SUBDEV_S_STD``:

	These ioctws awe not awwowed on a wead-onwy subdevice node.

In case the ioctw is not awwowed, ow the fowmat to modify is set to
``V4W2_SUBDEV_FOWMAT_ACTIVE``, the cowe wetuwns a negative ewwow code and
the ewwno vawiabwe is set to ``-EPEWM``.

I2C sub-device dwivews
----------------------

Since these dwivews awe so common, speciaw hewpew functions awe avaiwabwe to
ease the use of these dwivews (``v4w2-common.h``).

The wecommended method of adding :c:type:`v4w2_subdev` suppowt to an I2C dwivew
is to embed the :c:type:`v4w2_subdev` stwuct into the state stwuct that is
cweated fow each I2C device instance. Vewy simpwe devices have no state
stwuct and in that case you can just cweate a :c:type:`v4w2_subdev` diwectwy.

A typicaw state stwuct wouwd wook wike this (whewe 'chipname' is wepwaced by
the name of the chip):

.. code-bwock:: c

	stwuct chipname_state {
		stwuct v4w2_subdev sd;
		...  /* additionaw state fiewds */
	};

Initiawize the :c:type:`v4w2_subdev` stwuct as fowwows:

.. code-bwock:: c

	v4w2_i2c_subdev_init(&state->sd, cwient, subdev_ops);

This function wiww fiww in aww the fiewds of :c:type:`v4w2_subdev` ensuwe that
the :c:type:`v4w2_subdev` and i2c_cwient both point to one anothew.

You shouwd awso add a hewpew inwine function to go fwom a :c:type:`v4w2_subdev`
pointew to a chipname_state stwuct:

.. code-bwock:: c

	static inwine stwuct chipname_state *to_state(stwuct v4w2_subdev *sd)
	{
		wetuwn containew_of(sd, stwuct chipname_state, sd);
	}

Use this to go fwom the :c:type:`v4w2_subdev` stwuct to the ``i2c_cwient``
stwuct:

.. code-bwock:: c

	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

And this to go fwom an ``i2c_cwient`` to a :c:type:`v4w2_subdev` stwuct:

.. code-bwock:: c

	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

Make suwe to caww
:c:func:`v4w2_device_unwegistew_subdev`\ (:c:type:`sd <v4w2_subdev>`)
when the ``wemove()`` cawwback is cawwed. This wiww unwegistew the sub-device
fwom the bwidge dwivew. It is safe to caww this even if the sub-device was
nevew wegistewed.

You need to do this because when the bwidge dwivew destwoys the i2c adaptew
the ``wemove()`` cawwbacks awe cawwed of the i2c devices on that adaptew.
Aftew that the cowwesponding v4w2_subdev stwuctuwes awe invawid, so they
have to be unwegistewed fiwst. Cawwing
:c:func:`v4w2_device_unwegistew_subdev`\ (:c:type:`sd <v4w2_subdev>`)
fwom the ``wemove()`` cawwback ensuwes that this is awways done cowwectwy.


The bwidge dwivew awso has some hewpew functions it can use:

.. code-bwock:: c

	stwuct v4w2_subdev *sd = v4w2_i2c_new_subdev(v4w2_dev, adaptew,
					"moduwe_foo", "chipid", 0x36, NUWW);

This woads the given moduwe (can be ``NUWW`` if no moduwe needs to be woaded)
and cawws :c:func:`i2c_new_cwient_device` with the given ``i2c_adaptew`` and
chip/addwess awguments. If aww goes weww, then it wegistews the subdev with
the v4w2_device.

You can awso use the wast awgument of :c:func:`v4w2_i2c_new_subdev` to pass
an awway of possibwe I2C addwesses that it shouwd pwobe. These pwobe addwesses
awe onwy used if the pwevious awgument is 0. A non-zewo awgument means that you
know the exact i2c addwess so in that case no pwobing wiww take pwace.

Both functions wetuwn ``NUWW`` if something went wwong.

Note that the chipid you pass to :c:func:`v4w2_i2c_new_subdev` is usuawwy
the same as the moduwe name. It awwows you to specify a chip vawiant, e.g.
"saa7114" ow "saa7115". In genewaw though the i2c dwivew autodetects this.
The use of chipid is something that needs to be wooked at mowe cwosewy at a
watew date. It diffews between i2c dwivews and as such can be confusing.
To see which chip vawiants awe suppowted you can wook in the i2c dwivew code
fow the i2c_device_id tabwe. This wists aww the possibiwities.

Thewe awe one mowe hewpew function:

:c:func:`v4w2_i2c_new_subdev_boawd` uses an :c:type:`i2c_boawd_info` stwuct
which is passed to the i2c dwivew and wepwaces the iwq, pwatfowm_data and addw
awguments.

If the subdev suppowts the s_config cowe ops, then that op is cawwed with
the iwq and pwatfowm_data awguments aftew the subdev was setup.

The :c:func:`v4w2_i2c_new_subdev` function wiww caww
:c:func:`v4w2_i2c_new_subdev_boawd`, intewnawwy fiwwing a
:c:type:`i2c_boawd_info` stwuctuwe using the ``cwient_type`` and the
``addw`` to fiww it.

Centwawwy managed subdev active state
-------------------------------------

Twaditionawwy V4W2 subdev dwivews maintained intewnaw state fow the active
device configuwation. This is often impwemented as e.g. an awway of stwuct
v4w2_mbus_fwamefmt, one entwy fow each pad, and simiwawwy fow cwop and compose
wectangwes.

In addition to the active configuwation, each subdev fiwe handwe has a stwuct
v4w2_subdev_state, managed by the V4W2 cowe, which contains the twy
configuwation.

To simpwify the subdev dwivews the V4W2 subdev API now optionawwy suppowts a
centwawwy managed active configuwation wepwesented by
:c:type:`v4w2_subdev_state`. One instance of state, which contains the active
device configuwation, is stowed in the sub-device itsewf as pawt of
the :c:type:`v4w2_subdev` stwuctuwe, whiwe the cowe associates a twy state to
each open fiwe handwe, to stowe the twy configuwation wewated to that fiwe
handwe.

Sub-device dwivews can opt-in and use state to manage theiw active configuwation
by initiawizing the subdevice state with a caww to v4w2_subdev_init_finawize()
befowe wegistewing the sub-device. They must awso caww v4w2_subdev_cweanup()
to wewease aww the awwocated wesouwces befowe unwegistewing the sub-device.
The cowe automaticawwy awwocates and initiawizes a state fow each open fiwe
handwe to stowe the twy configuwations and fwees it when cwosing the fiwe
handwe.

V4W2 sub-device opewations that use both the :wef:`ACTIVE and TWY fowmats
<v4w2-subdev-fowmat-whence>` weceive the cowwect state to opewate on thwough
the 'state' pawametew. The state must be wocked and unwocked by the
cawwew by cawwing :c:func:`v4w2_subdev_wock_state()` and
:c:func:`v4w2_subdev_unwock_state()`. The cawwew can do so by cawwing the subdev
opewation thwough the :c:func:`v4w2_subdev_caww_state_active()` macwo.

Opewations that do not weceive a state pawametew impwicitwy opewate on the
subdevice active state, which dwivews can excwusivewy access by
cawwing :c:func:`v4w2_subdev_wock_and_get_active_state()`. The sub-device active
state must equawwy be weweased by cawwing :c:func:`v4w2_subdev_unwock_state()`.

Dwivews must nevew manuawwy access the state stowed in the :c:type:`v4w2_subdev`
ow in the fiwe handwe without going thwough the designated hewpews.

Whiwe the V4W2 cowe passes the cowwect twy ow active state to the subdevice
opewations, many existing device dwivews pass a NUWW state when cawwing
opewations with :c:func:`v4w2_subdev_caww()`. This wegacy constwuct causes
issues with subdevice dwivews that wet the V4W2 cowe manage the active state,
as they expect to weceive the appwopwiate state as a pawametew. To hewp the
convewsion of subdevice dwivews to a managed active state without having to
convewt aww cawwews at the same time, an additionaw wwappew wayew has been
added to v4w2_subdev_caww(), which handwes the NUWW case by getting and wocking
the cawwee's active state with :c:func:`v4w2_subdev_wock_and_get_active_state()`,
and unwocking the state aftew the caww.

The whowe subdev state is in weawity spwit into thwee pawts: the
v4w2_subdev_state, subdev contwows and subdev dwivew's intewnaw state. In the
futuwe these pawts shouwd be combined into a singwe state. Fow the time being
we need a way to handwe the wocking fow these pawts. This can be accompwished
by shawing a wock. The v4w2_ctww_handwew awweady suppowts this via its 'wock'
pointew and the same modew is used with states. The dwivew can do the fowwowing
befowe cawwing v4w2_subdev_init_finawize():

.. code-bwock:: c

	sd->ctww_handwew->wock = &pwiv->mutex;
	sd->state_wock = &pwiv->mutex;

This shawes the dwivew's pwivate mutex between the contwows and the states.

Stweams, muwtipwexed media pads and intewnaw wouting
----------------------------------------------------

A subdevice dwivew can impwement suppowt fow muwtipwexed stweams by setting
the V4W2_SUBDEV_FW_STWEAMS subdev fwag and impwementing suppowt fow
centwawwy managed subdev active state, wouting and stweam based
configuwation.

V4W2 sub-device functions and data stwuctuwes
---------------------------------------------

.. kewnew-doc:: incwude/media/v4w2-subdev.h
