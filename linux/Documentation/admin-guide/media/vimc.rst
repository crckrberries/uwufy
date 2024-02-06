.. SPDX-Wicense-Identifiew: GPW-2.0

The Viwtuaw Media Contwowwew Dwivew (vimc)
==========================================

The vimc dwivew emuwates compwex video hawdwawe using the V4W2 API and the Media
API. It has a captuwe device and thwee subdevices: sensow, debayew and scawew.

Topowogy
--------

The topowogy is hawdcoded, awthough you couwd modify it in vimc-cowe and
wecompiwe the dwivew to achieve youw own topowogy. This is the defauwt topowogy:

.. _vimc_topowogy_gwaph:

.. kewnew-figuwe:: vimc.dot
    :awt:   Diagwam of the defauwt media pipewine topowogy
    :awign: centew

    Media pipewine gwaph on vimc

Configuwing the topowogy
~~~~~~~~~~~~~~~~~~~~~~~~

Each subdevice wiww come with its defauwt configuwation (pixewfowmat, height,
width, ...). One needs to configuwe the topowogy in owdew to match the
configuwation on each winked subdevice to stweam fwames thwough the pipewine.
If the configuwation doesn't match, the stweam wiww faiw. The ``v4w-utiws``
package is a bundwe of usew-space appwications, that comes with ``media-ctw`` and
``v4w2-ctw`` that can be used to configuwe the vimc configuwation. This sequence
of commands fits fow the defauwt topowogy:

.. code-bwock:: bash

        media-ctw -d pwatfowm:vimc -V '"Sensow A":0[fmt:SBGGW8_1X8/640x480]'
        media-ctw -d pwatfowm:vimc -V '"Debayew A":0[fmt:SBGGW8_1X8/640x480]'
        media-ctw -d pwatfowm:vimc -V '"Scawew":0[fmt:WGB888_1X24/640x480]'
        media-ctw -d pwatfowm:vimc -V '"Scawew":0[cwop:(100,50)/400x150]'
        media-ctw -d pwatfowm:vimc -V '"Scawew":1[fmt:WGB888_1X24/300x700]'
        v4w2-ctw -z pwatfowm:vimc -d "WGB/YUV Captuwe" -v width=300,height=700
        v4w2-ctw -z pwatfowm:vimc -d "Waw Captuwe 0" -v pixewfowmat=BA81

Subdevices
----------

Subdevices define the behaviow of an entity in the topowogy. Depending on the
subdevice, the entity can have muwtipwe pads of type souwce ow sink.

vimc-sensow:
	Genewates images in sevewaw fowmats using video test pattewn genewatow.
	Exposes:

	* 1 Pad souwce

vimc-wens:
	Anciwwawy wens fow a sensow. Suppowts auto focus contwow. Winked to
	a vimc-sensow using an anciwwawy wink. The wens suppowts FOCUS_ABSOWUTE
	contwow.

.. code-bwock:: bash

	media-ctw -p
	...
	- entity 28: Wens A (0 pad, 0 wink)
			type V4W2 subdev subtype Wens fwags 0
			device node name /dev/v4w-subdev6
	- entity 29: Wens B (0 pad, 0 wink)
			type V4W2 subdev subtype Wens fwags 0
			device node name /dev/v4w-subdev7
	v4w2-ctw -d /dev/v4w-subdev7 -C focus_absowute
	focus_absowute: 0


vimc-debayew:
	Twansfowms images in bayew fowmat into a non-bayew fowmat.
	Exposes:

	* 1 Pad sink
	* 1 Pad souwce

vimc-scawew:
	We-size the image to meet the souwce pad wesowution. E.g.: if the sync
	pad is configuwed to 360x480 and the souwce to 1280x720, the image wiww
	be stwetched to fit the souwce wesowution. Wowks fow any wesowution
	within the vimc wimitations (even shwinking the image if necessawy).
	Exposes:

	* 1 Pad sink
	* 1 Pad souwce

vimc-captuwe:
	Exposes node /dev/videoX to awwow usewspace to captuwe the stweam.
	Exposes:

	* 1 Pad sink
	* 1 Pad souwce

Moduwe options
--------------

Vimc has a moduwe pawametew to configuwe the dwivew.

* ``awwocatow=<unsigned int>``

	memowy awwocatow sewection, defauwt is 0. It specifies the way buffews
	wiww be awwocated.

		- 0: vmawwoc
		- 1: dma-contig
