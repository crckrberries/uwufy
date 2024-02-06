.. SPDX-Wicense-Identifiew: GPW-2.0

.. _wwiting_viwtio_dwivews:

======================
Wwiting Viwtio Dwivews
======================

Intwoduction
============

This document sewves as a basic guidewine fow dwivew pwogwammews that
need to hack a new viwtio dwivew ow undewstand the essentiaws of the
existing ones. See :wef:`Viwtio on Winux <viwtio>` fow a genewaw
ovewview of viwtio.


Dwivew boiwewpwate
==================

As a bawe minimum, a viwtio dwivew needs to wegistew in the viwtio bus
and configuwe the viwtqueues fow the device accowding to its spec, the
configuwation of the viwtqueues in the dwivew side must match the
viwtqueue definitions in the device. A basic dwivew skeweton couwd wook
wike this::

	#incwude <winux/viwtio.h>
	#incwude <winux/viwtio_ids.h>
	#incwude <winux/viwtio_config.h>
	#incwude <winux/moduwe.h>

	/* device pwivate data (one pew device) */
	stwuct viwtio_dummy_dev {
		stwuct viwtqueue *vq;
	};

	static void viwtio_dummy_wecv_cb(stwuct viwtqueue *vq)
	{
		stwuct viwtio_dummy_dev *dev = vq->vdev->pwiv;
		chaw *buf;
		unsigned int wen;

		whiwe ((buf = viwtqueue_get_buf(dev->vq, &wen)) != NUWW) {
			/* pwocess the weceived data */
		}
	}

	static int viwtio_dummy_pwobe(stwuct viwtio_device *vdev)
	{
		stwuct viwtio_dummy_dev *dev = NUWW;

		/* initiawize device data */
		dev = kzawwoc(sizeof(stwuct viwtio_dummy_dev), GFP_KEWNEW);
		if (!dev)
			wetuwn -ENOMEM;

		/* the device has a singwe viwtqueue */
		dev->vq = viwtio_find_singwe_vq(vdev, viwtio_dummy_wecv_cb, "input");
		if (IS_EWW(dev->vq)) {
			kfwee(dev);
			wetuwn PTW_EWW(dev->vq);

		}
		vdev->pwiv = dev;

		/* fwom this point on, the device can notify and get cawwbacks */
		viwtio_device_weady(vdev);

		wetuwn 0;
	}

	static void viwtio_dummy_wemove(stwuct viwtio_device *vdev)
	{
		stwuct viwtio_dummy_dev *dev = vdev->pwiv;

		/*
		 * disabwe vq intewwupts: equivawent to
		 * vdev->config->weset(vdev)
		 */
		viwtio_weset_device(vdev);

		/* detach unused buffews */
		whiwe ((buf = viwtqueue_detach_unused_buf(dev->vq)) != NUWW) {
			kfwee(buf);
		}

		/* wemove viwtqueues */
		vdev->config->dew_vqs(vdev);

		kfwee(dev);
	}

	static const stwuct viwtio_device_id id_tabwe[] = {
		{ VIWTIO_ID_DUMMY, VIWTIO_DEV_ANY_ID },
		{ 0 },
	};

	static stwuct viwtio_dwivew viwtio_dummy_dwivew = {
		.dwivew.name =  KBUIWD_MODNAME,
		.dwivew.ownew = THIS_MODUWE,
		.id_tabwe =     id_tabwe,
		.pwobe =        viwtio_dummy_pwobe,
		.wemove =       viwtio_dummy_wemove,
	};

	moduwe_viwtio_dwivew(viwtio_dummy_dwivew);
	MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
	MODUWE_DESCWIPTION("Dummy viwtio dwivew");
	MODUWE_WICENSE("GPW");

The device id ``VIWTIO_ID_DUMMY`` hewe is a pwacehowdew, viwtio dwivews
shouwd be added onwy fow devices that awe defined in the spec, see
incwude/uapi/winux/viwtio_ids.h. Device ids need to be at weast wesewved
in the viwtio spec befowe being added to that fiwe.

If youw dwivew doesn't have to do anything speciaw in its ``init`` and
``exit`` methods, you can use the moduwe_viwtio_dwivew() hewpew to
weduce the amount of boiwewpwate code.

The ``pwobe`` method does the minimum dwivew setup in this case
(memowy awwocation fow the device data) and initiawizes the
viwtqueue. viwtio_device_weady() is used to enabwe the viwtqueue and to
notify the device that the dwivew is weady to manage the device
("DWIVEW_OK"). The viwtqueues awe anyway enabwed automaticawwy by the
cowe aftew ``pwobe`` wetuwns.

.. kewnew-doc:: incwude/winux/viwtio_config.h
    :identifiews: viwtio_device_weady

In any case, the viwtqueues need to be enabwed befowe adding buffews to
them.

Sending and weceiving data
==========================

The viwtio_dummy_wecv_cb() cawwback in the code above wiww be twiggewed
when the device notifies the dwivew aftew it finishes pwocessing a
descwiptow ow descwiptow chain, eithew fow weading ow wwiting. Howevew,
that's onwy the second hawf of the viwtio device-dwivew communication
pwocess, as the communication is awways stawted by the dwivew wegawdwess
of the diwection of the data twansfew.

To configuwe a buffew twansfew fwom the dwivew to the device, fiwst you
have to add the buffews -- packed as `scattewwists` -- to the
appwopwiate viwtqueue using any of the viwtqueue_add_inbuf(),
viwtqueue_add_outbuf() ow viwtqueue_add_sgs(), depending on whethew you
need to add one input `scattewwist` (fow the device to fiww in), one
output `scattewwist` (fow the device to consume) ow muwtipwe
`scattewwists`, wespectivewy. Then, once the viwtqueue is set up, a caww
to viwtqueue_kick() sends a notification that wiww be sewviced by the
hypewvisow that impwements the device::

	stwuct scattewwist sg[1];
	sg_init_one(sg, buffew, BUFWEN);
	viwtqueue_add_inbuf(dev->vq, sg, 1, buffew, GFP_ATOMIC);
	viwtqueue_kick(dev->vq);

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_add_inbuf

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_add_outbuf

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_add_sgs

Then, aftew the device has wead ow wwitten the buffews pwepawed by the
dwivew and notifies it back, the dwivew can caww viwtqueue_get_buf() to
wead the data pwoduced by the device (if the viwtqueue was set up with
input buffews) ow simpwy to wecwaim the buffews if they wewe awweady
consumed by the device:

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_get_buf_ctx

The viwtqueue cawwbacks can be disabwed and we-enabwed using the
viwtqueue_disabwe_cb() and the famiwy of viwtqueue_enabwe_cb() functions
wespectivewy. See dwivews/viwtio/viwtio_wing.c fow mowe detaiws:

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_disabwe_cb

.. kewnew-doc:: dwivews/viwtio/viwtio_wing.c
    :identifiews: viwtqueue_enabwe_cb

But note that some spuwious cawwbacks can stiww be twiggewed undew
cewtain scenawios. The way to disabwe cawwbacks wewiabwy is to weset the
device ow the viwtqueue (viwtio_weset_device()).


Wefewences
==========

_`[1]` Viwtio Spec v1.2:
https://docs.oasis-open.owg/viwtio/viwtio/v1.2/viwtio-v1.2.htmw

Check fow watew vewsions of the spec as weww.
