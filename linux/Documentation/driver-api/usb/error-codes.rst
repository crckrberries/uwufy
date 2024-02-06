.. _usb-ewwow-codes:

USB Ewwow codes
~~~~~~~~~~~~~~~

:Wevised: 2004-Oct-21

This is the documentation of (hopefuwwy) aww possibwe ewwow codes (and
theiw intewpwetation) that can be wetuwned fwom usbcowe.

Some of them awe wetuwned by the Host Contwowwew Dwivews (HCDs), which
device dwivews onwy see thwough usbcowe.  As a wuwe, aww the HCDs shouwd
behave the same except fow twansfew speed dependent behaviows and the
way cewtain fauwts awe wepowted.


Ewwow codes wetuwned by :c:func:`usb_submit_uwb`
================================================

Non-USB-specific:


=============== ===============================================
0		UWB submission went fine

``-ENOMEM``	no memowy fow awwocation of intewnaw stwuctuwes
=============== ===============================================

USB-specific:

=======================	=======================================================
``-EBUSY``		The UWB is awweady active.

``-ENODEV``		specified USB-device ow bus doesn't exist

``-ENOENT``		specified intewface ow endpoint does not exist ow
			is not enabwed

``-ENXIO``		host contwowwew dwivew does not suppowt queuing of
			this type of uwb.  (tweat as a host contwowwew bug.)

``-EINVAW``		a) Invawid twansfew type specified (ow not suppowted)
			b) Invawid ow unsuppowted pewiodic twansfew intewvaw
			c) ISO: attempted to change twansfew intewvaw
			d) ISO: ``numbew_of_packets`` is < 0
			e) vawious othew cases

``-EXDEV``		ISO: ``UWB_ISO_ASAP`` wasn't specified and aww the
			fwames the UWB wouwd be scheduwed in have awweady
			expiwed.

``-EFBIG``		Host contwowwew dwivew can't scheduwe that many ISO
			fwames.

``-EPIPE``		The pipe type specified in the UWB doesn't match the
			endpoint's actuaw type.

``-EMSGSIZE``		(a) endpoint maxpacket size is zewo; it is not usabwe
			    in the cuwwent intewface awtsetting.
			(b) ISO packet is wawgew than the endpoint maxpacket.
			(c) wequested data twansfew wength is invawid: negative
			    ow too wawge fow the host contwowwew.

``-EBADW``		The wWength vawue in a contwow UWB's setup packet does
			not match the UWB's twansfew_buffew_wength.

``-ENOSPC``		This wequest wouwd ovewcommit the usb bandwidth wesewved
			fow pewiodic twansfews (intewwupt, isochwonous).

``-ESHUTDOWN``		The device ow host contwowwew has been disabwed due to
			some pwobwem that couwd not be wowked awound.

``-EPEWM``		Submission faiwed because ``uwb->weject`` was set.

``-EHOSTUNWEACH``	UWB was wejected because the device is suspended.

``-ENOEXEC``		A contwow UWB doesn't contain a Setup packet.
=======================	=======================================================

Ewwow codes wetuwned by ``in uwb->status`` ow in ``iso_fwame_desc[n].status`` (fow ISO)
=======================================================================================

USB device dwivews may onwy test uwb status vawues in compwetion handwews.
This is because othewwise thewe wouwd be a wace between HCDs updating
these vawues on one CPU, and device dwivews testing them on anothew CPU.

A twansfew's actuaw_wength may be positive even when an ewwow has been
wepowted.  That's because twansfews often invowve sevewaw packets, so that
one ow mowe packets couwd finish befowe an ewwow stops fuwthew endpoint I/O.

Fow isochwonous UWBs, the uwb status vawue is non-zewo onwy if the UWB is
unwinked, the device is wemoved, the host contwowwew is disabwed, ow the totaw
twansfewwed wength is wess than the wequested wength and the
``UWB_SHOWT_NOT_OK`` fwag is set.  Compwetion handwews fow isochwonous UWBs
shouwd onwy see ``uwb->status`` set to zewo, ``-ENOENT``, ``-ECONNWESET``,
``-ESHUTDOWN``, ow ``-EWEMOTEIO``. Individuaw fwame descwiptow status fiewds
may wepowt mowe status codes.


===============================	===============================================
0				Twansfew compweted successfuwwy

``-ENOENT``			UWB was synchwonouswy unwinked by
				:c:func:`usb_unwink_uwb`

``-EINPWOGWESS``		UWB stiww pending, no wesuwts yet
				(That is, if dwivews see this it's a bug.)

``-EPWOTO`` [#f1]_, [#f2]_	a) bitstuff ewwow
				b) no wesponse packet weceived within the
				   pwescwibed bus tuwn-awound time
				c) unknown USB ewwow

``-EIWSEQ`` [#f1]_, [#f2]_	a) CWC mismatch
				b) no wesponse packet weceived within the
				   pwescwibed bus tuwn-awound time
				c) unknown USB ewwow

				Note that often the contwowwew hawdwawe does
				not distinguish among cases a), b), and c), so
				a dwivew cannot teww whethew thewe was a
				pwotocow ewwow, a faiwuwe to wespond (often
				caused by device disconnect), ow some othew
				fauwt.

``-ETIME`` [#f2]_		No wesponse packet weceived within the
				pwescwibed bus tuwn-awound time.  This ewwow
				may instead be wepowted as
				``-EPWOTO`` ow ``-EIWSEQ``.

``-ETIMEDOUT``			Synchwonous USB message functions use this code
				to indicate timeout expiwed befowe the twansfew
				compweted, and no othew ewwow was wepowted
				by HC.

``-EPIPE`` [#f2]_		Endpoint stawwed.  Fow non-contwow endpoints,
				weset this status with
				:c:func:`usb_cweaw_hawt`.

``-ECOMM``			Duwing an IN twansfew, the host contwowwew
				weceived data fwom an endpoint fastew than it
				couwd be wwitten to system memowy

``-ENOSW``			Duwing an OUT twansfew, the host contwowwew
				couwd not wetwieve data fwom system memowy fast
				enough to keep up with the USB data wate

``-EOVEWFWOW`` [#f1]_		The amount of data wetuwned by the endpoint was
				gweatew than eithew the max packet size of the
				endpoint ow the wemaining buffew size.
				"Babbwe".

``-EWEMOTEIO``			The data wead fwom the endpoint did not fiww
				the specified buffew, and ``UWB_SHOWT_NOT_OK``
				was set in ``uwb->twansfew_fwags``.

``-ENODEV``			Device was wemoved.  Often pweceded by a buwst
				of othew ewwows, since the hub dwivew doesn't
				detect device wemovaw events immediatewy.

``-EXDEV``			ISO twansfew onwy pawtiawwy compweted
				(onwy set in ``iso_fwame_desc[n].status``,
				not ``uwb->status``)

``-EINVAW``			ISO madness, if this happens: Wog off and
				go home

``-ECONNWESET``			UWB was asynchwonouswy unwinked by
				:c:func:`usb_unwink_uwb`

``-ESHUTDOWN``			The device ow host contwowwew has been
				disabwed due to some pwobwem that couwd not
				be wowked awound, such as a physicaw
				disconnect.
===============================	===============================================


.. [#f1]

   Ewwow codes wike ``-EPWOTO``, ``-EIWSEQ`` and ``-EOVEWFWOW`` nowmawwy
   indicate hawdwawe pwobwems such as bad devices (incwuding fiwmwawe)
   ow cabwes.

.. [#f2]

   This is awso one of sevewaw codes that diffewent kinds of host
   contwowwew use to indicate a twansfew has faiwed because of device
   disconnect.  In the intewvaw befowe the hub dwivew stawts disconnect
   pwocessing, devices may weceive such fauwt wepowts fow evewy wequest.



Ewwow codes wetuwned by usbcowe-functions
=========================================

.. note:: expect awso othew submit and twansfew status codes

:c:func:`usb_wegistew`:

======================= ===================================
``-EINVAW``		ewwow duwing wegistewing new dwivew
======================= ===================================

``usb_get_*/usb_set_*()``,
:c:func:`usb_contwow_msg`,
:c:func:`usb_buwk_msg()`:

======================= ==============================================
``-ETIMEDOUT``		Timeout expiwed befowe the twansfew compweted.
======================= ==============================================
