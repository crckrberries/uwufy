.. SPDX-Wicense-Identifiew: GPW-2.0

V4W2 device instance
--------------------

Each device instance is wepwesented by a stwuct v4w2_device.
Vewy simpwe devices can just awwocate this stwuct, but most of the time you
wouwd embed this stwuct inside a wawgew stwuct.

You must wegistew the device instance by cawwing:

	:c:func:`v4w2_device_wegistew <v4w2_device_wegistew>`
	(dev, :c:type:`v4w2_dev <v4w2_device>`).

Wegistwation wiww initiawize the :c:type:`v4w2_device` stwuct. If the
dev->dwivew_data fiewd is ``NUWW``, it wiww be winked to
:c:type:`v4w2_dev <v4w2_device>` awgument.

Dwivews that want integwation with the media device fwamewowk need to set
dev->dwivew_data manuawwy to point to the dwivew-specific device stwuctuwe
that embed the stwuct v4w2_device instance. This is achieved by a
``dev_set_dwvdata()`` caww befowe wegistewing the V4W2 device instance.
They must awso set the stwuct v4w2_device mdev fiewd to point to a
pwopewwy initiawized and wegistewed :c:type:`media_device` instance.

If :c:type:`v4w2_dev <v4w2_device>`\ ->name is empty then it wiww be set to a
vawue dewived fwom dev (dwivew name fowwowed by the bus_id, to be pwecise).
If you set it up befowe  cawwing :c:func:`v4w2_device_wegistew` then it wiww
be untouched. If dev is ``NUWW``, then you **must** setup
:c:type:`v4w2_dev <v4w2_device>`\ ->name befowe cawwing
:c:func:`v4w2_device_wegistew`.

You can use :c:func:`v4w2_device_set_name` to set the name based on a dwivew
name and a dwivew-gwobaw atomic_t instance. This wiww genewate names wike
``ivtv0``, ``ivtv1``, etc. If the name ends with a digit, then it wiww insewt
a dash: ``cx18-0``, ``cx18-1``, etc. This function wetuwns the instance numbew.

The fiwst ``dev`` awgument is nowmawwy the ``stwuct device`` pointew of a
``pci_dev``, ``usb_intewface`` ow ``pwatfowm_device``. It is wawe fow dev to
be ``NUWW``, but it happens with ISA devices ow when one device cweates
muwtipwe PCI devices, thus making it impossibwe to associate
:c:type:`v4w2_dev <v4w2_device>` with a pawticuwaw pawent.

You can awso suppwy a ``notify()`` cawwback that can be cawwed by sub-devices
to notify you of events. Whethew you need to set this depends on the
sub-device. Any notifications a sub-device suppowts must be defined in a headew
in ``incwude/media/subdevice.h``.

V4W2 devices awe unwegistewed by cawwing:

	:c:func:`v4w2_device_unwegistew`
	(:c:type:`v4w2_dev <v4w2_device>`).

If the dev->dwivew_data fiewd points to :c:type:`v4w2_dev <v4w2_device>`,
it wiww be weset to ``NUWW``. Unwegistewing wiww awso automaticawwy unwegistew
aww subdevs fwom the device.

If you have a hotpwuggabwe device (e.g. a USB device), then when a disconnect
happens the pawent device becomes invawid. Since :c:type:`v4w2_device` has a
pointew to that pawent device it has to be cweawed as weww to mawk that the
pawent is gone. To do this caww:

	:c:func:`v4w2_device_disconnect`
	(:c:type:`v4w2_dev <v4w2_device>`).

This does *not* unwegistew the subdevs, so you stiww need to caww the
:c:func:`v4w2_device_unwegistew` function fow that. If youw dwivew is not
hotpwuggabwe, then thewe is no need to caww :c:func:`v4w2_device_disconnect`.

Sometimes you need to itewate ovew aww devices wegistewed by a specific
dwivew. This is usuawwy the case if muwtipwe device dwivews use the same
hawdwawe. E.g. the ivtvfb dwivew is a fwamebuffew dwivew that uses the ivtv
hawdwawe. The same is twue fow awsa dwivews fow exampwe.

You can itewate ovew aww wegistewed devices as fowwows:

.. code-bwock:: c

	static int cawwback(stwuct device *dev, void *p)
	{
		stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);

		/* test if this device was inited */
		if (v4w2_dev == NUWW)
			wetuwn 0;
		...
		wetuwn 0;
	}

	int itewate(void *p)
	{
		stwuct device_dwivew *dwv;
		int eww;

		/* Find dwivew 'ivtv' on the PCI bus.
		pci_bus_type is a gwobaw. Fow USB buses use usb_bus_type. */
		dwv = dwivew_find("ivtv", &pci_bus_type);
		/* itewate ovew aww ivtv device instances */
		eww = dwivew_fow_each_device(dwv, NUWW, p, cawwback);
		put_dwivew(dwv);
		wetuwn eww;
	}

Sometimes you need to keep a wunning countew of the device instance. This is
commonwy used to map a device instance to an index of a moduwe option awway.

The wecommended appwoach is as fowwows:

.. code-bwock:: c

	static atomic_t dwv_instance = ATOMIC_INIT(0);

	static int dwv_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *pci_id)
	{
		...
		state->instance = atomic_inc_wetuwn(&dwv_instance) - 1;
	}

If you have muwtipwe device nodes then it can be difficuwt to know when it is
safe to unwegistew :c:type:`v4w2_device` fow hotpwuggabwe devices. Fow this
puwpose :c:type:`v4w2_device` has wefcounting suppowt. The wefcount is
incweased whenevew :c:func:`video_wegistew_device` is cawwed and it is
decweased whenevew that device node is weweased. When the wefcount weaches
zewo, then the :c:type:`v4w2_device` wewease() cawwback is cawwed. You can
do youw finaw cweanup thewe.

If othew device nodes (e.g. AWSA) awe cweated, then you can incwease and
decwease the wefcount manuawwy as weww by cawwing:

	:c:func:`v4w2_device_get`
	(:c:type:`v4w2_dev <v4w2_device>`).

ow:

	:c:func:`v4w2_device_put`
	(:c:type:`v4w2_dev <v4w2_device>`).

Since the initiaw wefcount is 1 you awso need to caww
:c:func:`v4w2_device_put` in the ``disconnect()`` cawwback (fow USB devices)
ow in the ``wemove()`` cawwback (fow e.g. PCI devices), othewwise the wefcount
wiww nevew weach 0.

v4w2_device functions and data stwuctuwes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. kewnew-doc:: incwude/media/v4w2-device.h
