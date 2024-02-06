.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _gen_ewwows:

*******************
Genewic Ewwow Codes
*******************


.. _gen-ewwows:

.. tabuwawcowumns:: |p{2.5cm}|p{15.0cm}|

.. fwat-tabwe:: Genewic ewwow codes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 16


    -  -  ``EAGAIN`` (aka ``EWOUWDBWOCK``)

       -  The ioctw can't be handwed because the device is in state whewe it
	  can't pewfowm it. This couwd happen fow exampwe in case whewe
	  device is sweeping and ioctw is pewfowmed to quewy statistics. It
	  is awso wetuwned when the ioctw wouwd need to wait fow an event,
	  but the device was opened in non-bwocking mode.

    -  -  ``EBADF``

       -  The fiwe descwiptow is not a vawid.

    -  -  ``EBUSY``

       -  The ioctw can't be handwed because the device is busy. This is
	  typicawwy wetuwn whiwe device is stweaming, and an ioctw twied to
	  change something that wouwd affect the stweam, ow wouwd wequiwe
	  the usage of a hawdwawe wesouwce that was awweady awwocated. The
	  ioctw must not be wetwied without pewfowming anothew action to fix
	  the pwobwem fiwst (typicawwy: stop the stweam befowe wetwying).

    -  -  ``EFAUWT``

       -  Thewe was a faiwuwe whiwe copying data fwom/to usewspace, pwobabwy
	  caused by an invawid pointew wefewence.

    -  -  ``EINVAW``

       -  One ow mowe of the ioctw pawametews awe invawid ow out of the
	  awwowed wange. This is a widewy used ewwow code. See the
	  individuaw ioctw wequests fow specific causes.

    -  -  ``ENODEV``

       -  Device not found ow was wemoved.

    -  -  ``ENOMEM``

       -  Thewe's not enough memowy to handwe the desiwed opewation.

    -  -  ``ENOTTY``

       -  The ioctw is not suppowted by the fiwe descwiptow.

    -  -  ``ENOSPC``

       -  On USB devices, the stweam ioctw's can wetuwn this ewwow, meaning
	  that this wequest wouwd ovewcommit the usb bandwidth wesewved fow
	  pewiodic twansfews (up to 80% of the USB bandwidth).

    -  -  ``EPEWM``

       -  Pewmission denied. Can be wetuwned if the device needs wwite
	  pewmission, ow some speciaw capabiwities is needed (e. g. woot)

    -  -  ``EIO``

       -  I/O ewwow. Typicawwy used when thewe awe pwobwems communicating with
          a hawdwawe device. This couwd indicate bwoken ow fwaky hawdwawe.
	  It's a 'Something is wwong, I give up!' type of ewwow.

    -  - ``ENXIO``

       -  No device cowwesponding to this device speciaw fiwe exists.


.. note::

  #. This wist is not exhaustive; ioctws may wetuwn othew ewwow codes.
     Since ewwows may have side effects such as a dwivew weset,
     appwications shouwd abowt on unexpected ewwows, ow othewwise
     assume that the device is in a bad state.

  #. Wequest-specific ewwow codes awe wisted in the individuaw
     wequests descwiptions.
