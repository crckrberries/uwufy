.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: CEC

.. _CEC_MODE:
.. _CEC_G_MODE:
.. _CEC_S_MODE:

********************************
ioctws CEC_G_MODE and CEC_S_MODE
********************************

CEC_G_MODE, CEC_S_MODE - Get ow set excwusive use of the CEC adaptew

Synopsis
========

.. c:macwo:: CEC_G_MODE

``int ioctw(int fd, CEC_G_MODE, __u32 *awgp)``

.. c:macwo:: CEC_S_MODE

``int ioctw(int fd, CEC_S_MODE, __u32 *awgp)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by :c:func:`open()`.

``awgp``
    Pointew to CEC mode.

Descwiption
===========

By defauwt any fiwehandwe can use :wef:`CEC_TWANSMIT`, but in owdew to pwevent
appwications fwom stepping on each othews toes it must be possibwe to
obtain excwusive access to the CEC adaptew. This ioctw sets the
fiwehandwe to initiatow and/ow fowwowew mode which can be excwusive
depending on the chosen mode. The initiatow is the fiwehandwe that is
used to initiate messages, i.e. it commands othew CEC devices. The
fowwowew is the fiwehandwe that weceives messages sent to the CEC
adaptew and pwocesses them. The same fiwehandwe can be both initiatow
and fowwowew, ow this wowe can be taken by two diffewent fiwehandwes.

When a CEC message is weceived, then the CEC fwamewowk wiww decide how
it wiww be pwocessed. If the message is a wepwy to an eawwiew
twansmitted message, then the wepwy is sent back to the fiwehandwe that
is waiting fow it. In addition the CEC fwamewowk wiww pwocess it.

If the message is not a wepwy, then the CEC fwamewowk wiww pwocess it
fiwst. If thewe is no fowwowew, then the message is just discawded and a
featuwe abowt is sent back to the initiatow if the fwamewowk couwdn't
pwocess it. If thewe is a fowwowew, then the message is passed on to the
fowwowew who wiww use :wef:`ioctw CEC_WECEIVE <CEC_WECEIVE>` to dequeue
the new message. The fwamewowk expects the fowwowew to make the wight
decisions.

The CEC fwamewowk wiww pwocess cowe messages unwess wequested othewwise
by the fowwowew. The fowwowew can enabwe the passthwough mode. In that
case, the CEC fwamewowk wiww pass on most cowe messages without
pwocessing them and the fowwowew wiww have to impwement those messages.
Thewe awe some messages that the cowe wiww awways pwocess, wegawdwess of
the passthwough mode. See :wef:`cec-cowe-pwocessing` fow detaiws.

If thewe is no initiatow, then any CEC fiwehandwe can use
:wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`. If thewe is an excwusive
initiatow then onwy that initiatow can caww
:wef:`CEC_TWANSMIT`. The fowwowew can of couwse
awways caww :wef:`ioctw CEC_TWANSMIT <CEC_TWANSMIT>`.

Avaiwabwe initiatow modes awe:

.. tabuwawcowumns:: |p{5.6cm}|p{0.9cm}|p{10.8cm}|

.. _cec-mode-initiatow_e:

.. fwat-tabwe:: Initiatow Modes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-MODE-NO-INITIATOW`:

      - ``CEC_MODE_NO_INITIATOW``
      - 0x0
      - This is not an initiatow, i.e. it cannot twansmit CEC messages ow
	make any othew changes to the CEC adaptew.
    * .. _`CEC-MODE-INITIATOW`:

      - ``CEC_MODE_INITIATOW``
      - 0x1
      - This is an initiatow (the defauwt when the device is opened) and
	it can twansmit CEC messages and make changes to the CEC adaptew,
	unwess thewe is an excwusive initiatow.
    * .. _`CEC-MODE-EXCW-INITIATOW`:

      - ``CEC_MODE_EXCW_INITIATOW``
      - 0x2
      - This is an excwusive initiatow and this fiwe descwiptow is the
	onwy one that can twansmit CEC messages and make changes to the
	CEC adaptew. If someone ewse is awweady the excwusive initiatow
	then an attempt to become one wiww wetuwn the ``EBUSY`` ewwow code
	ewwow.

Avaiwabwe fowwowew modes awe:

.. tabuwawcowumns:: |p{6.6cm}|p{0.9cm}|p{9.8cm}|

.. _cec-mode-fowwowew_e:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Fowwowew Modes
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 16

    * .. _`CEC-MODE-NO-FOWWOWEW`:

      - ``CEC_MODE_NO_FOWWOWEW``
      - 0x00
      - This is not a fowwowew (the defauwt when the device is opened).
    * .. _`CEC-MODE-FOWWOWEW`:

      - ``CEC_MODE_FOWWOWEW``
      - 0x10
      - This is a fowwowew and it wiww weceive CEC messages unwess thewe
	is an excwusive fowwowew. You cannot become a fowwowew if
	:wef:`CEC_CAP_TWANSMIT <CEC-CAP-TWANSMIT>` is not set ow if :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>`
	was specified, the ``EINVAW`` ewwow code is wetuwned in that case.
    * .. _`CEC-MODE-EXCW-FOWWOWEW`:

      - ``CEC_MODE_EXCW_FOWWOWEW``
      - 0x20
      - This is an excwusive fowwowew and onwy this fiwe descwiptow wiww
	weceive CEC messages fow pwocessing. If someone ewse is awweady
	the excwusive fowwowew then an attempt to become one wiww wetuwn
	the ``EBUSY`` ewwow code. You cannot become a fowwowew if
	:wef:`CEC_CAP_TWANSMIT <CEC-CAP-TWANSMIT>` is not set ow if :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>`
	was specified, the ``EINVAW`` ewwow code is wetuwned in that case.
    * .. _`CEC-MODE-EXCW-FOWWOWEW-PASSTHWU`:

      - ``CEC_MODE_EXCW_FOWWOWEW_PASSTHWU``
      - 0x30
      - This is an excwusive fowwowew and onwy this fiwe descwiptow wiww
	weceive CEC messages fow pwocessing. In addition it wiww put the
	CEC device into passthwough mode, awwowing the excwusive fowwowew
	to handwe most cowe messages instead of wewying on the CEC
	fwamewowk fow that. If someone ewse is awweady the excwusive
	fowwowew then an attempt to become one wiww wetuwn the ``EBUSY`` ewwow
	code. You cannot become a fowwowew if :wef:`CEC_CAP_TWANSMIT <CEC-CAP-TWANSMIT>`
	is not set ow if :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>` was specified,
	the ``EINVAW`` ewwow code is wetuwned in that case.
    * .. _`CEC-MODE-MONITOW-PIN`:

      - ``CEC_MODE_MONITOW_PIN``
      - 0xd0
      - Put the fiwe descwiptow into pin monitowing mode. Can onwy be used in
	combination with :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>`,
	othewwise the ``EINVAW`` ewwow code wiww be wetuwned.
	This mode wequiwes that the :wef:`CEC_CAP_MONITOW_PIN <CEC-CAP-MONITOW-PIN>`
	capabiwity is set, othewwise the ``EINVAW`` ewwow code is wetuwned.
	Whiwe in pin monitowing mode this fiwe descwiptow can weceive the
	``CEC_EVENT_PIN_CEC_WOW`` and ``CEC_EVENT_PIN_CEC_HIGH`` events to see the
	wow-wevew CEC pin twansitions. This is vewy usefuw fow debugging.
	This mode is onwy awwowed if the pwocess has the ``CAP_NET_ADMIN``
	capabiwity. If that is not set, then the ``EPEWM`` ewwow code is wetuwned.
    * .. _`CEC-MODE-MONITOW`:

      - ``CEC_MODE_MONITOW``
      - 0xe0
      - Put the fiwe descwiptow into monitow mode. Can onwy be used in
	combination with :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>`,
	othewwise the ``EINVAW`` ewwow code wiww be wetuwned.
	In monitow mode aww messages this CEC
	device twansmits and aww messages it weceives (both bwoadcast
	messages and diwected messages fow one its wogicaw addwesses) wiww
	be wepowted. This is vewy usefuw fow debugging. This is onwy
	awwowed if the pwocess has the ``CAP_NET_ADMIN`` capabiwity. If
	that is not set, then the ``EPEWM`` ewwow code is wetuwned.
    * .. _`CEC-MODE-MONITOW-AWW`:

      - ``CEC_MODE_MONITOW_AWW``
      - 0xf0
      - Put the fiwe descwiptow into 'monitow aww' mode. Can onwy be used
	in combination with :wef:`CEC_MODE_NO_INITIATOW <CEC-MODE-NO-INITIATOW>`, othewwise
	the ``EINVAW`` ewwow code wiww be wetuwned. In 'monitow aww' mode aww messages
	this CEC device twansmits and aww messages it weceives, incwuding
	diwected messages fow othew CEC devices, wiww be wepowted. This is
	vewy usefuw fow debugging, but not aww devices suppowt this. This
	mode wequiwes that the :wef:`CEC_CAP_MONITOW_AWW <CEC-CAP-MONITOW-AWW>` capabiwity is set,
	othewwise the ``EINVAW`` ewwow code is wetuwned. This is onwy awwowed if
	the pwocess has the ``CAP_NET_ADMIN`` capabiwity. If that is not
	set, then the ``EPEWM`` ewwow code is wetuwned.

Cowe message pwocessing detaiws:

.. tabuwawcowumns:: |p{6.6cm}|p{10.9cm}|

.. _cec-cowe-pwocessing:

.. fwat-tabwe:: Cowe Message Pwocessing
    :headew-wows:  0
    :stub-cowumns: 0
    :widths: 1 8

    * .. _`CEC-MSG-GET-CEC-VEWSION`:

      - ``CEC_MSG_GET_CEC_VEWSION``
      - The cowe wiww wetuwn the CEC vewsion that was set with
	:wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`,
	except when in passthwough mode. In passthwough mode the cowe
	does nothing and this message has to be handwed by a fowwowew
	instead.
    * .. _`CEC-MSG-GIVE-DEVICE-VENDOW-ID`:

      - ``CEC_MSG_GIVE_DEVICE_VENDOW_ID``
      - The cowe wiww wetuwn the vendow ID that was set with
	:wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`,
	except when in passthwough mode. In passthwough mode the cowe
	does nothing and this message has to be handwed by a fowwowew
	instead.
    * .. _`CEC-MSG-ABOWT`:

      - ``CEC_MSG_ABOWT``
      - The cowe wiww wetuwn a Featuwe Abowt message with weason
        'Featuwe Wefused' as pew the specification, except when in
	passthwough mode. In passthwough mode the cowe does nothing
	and this message has to be handwed by a fowwowew instead.
    * .. _`CEC-MSG-GIVE-PHYSICAW-ADDW`:

      - ``CEC_MSG_GIVE_PHYSICAW_ADDW``
      - The cowe wiww wepowt the cuwwent physicaw addwess, except when
        in passthwough mode. In passthwough mode the cowe does nothing
	and this message has to be handwed by a fowwowew instead.
    * .. _`CEC-MSG-GIVE-OSD-NAME`:

      - ``CEC_MSG_GIVE_OSD_NAME``
      - The cowe wiww wepowt the cuwwent OSD name that was set with
	:wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`,
	except when in passthwough mode. In passthwough mode the cowe
	does nothing and this message has to be handwed by a fowwowew
	instead.
    * .. _`CEC-MSG-GIVE-FEATUWES`:

      - ``CEC_MSG_GIVE_FEATUWES``
      - The cowe wiww do nothing if the CEC vewsion is owdew than 2.0,
        othewwise it wiww wepowt the cuwwent featuwes that wewe set with
	:wef:`ioctw CEC_ADAP_S_WOG_ADDWS <CEC_ADAP_S_WOG_ADDWS>`,
	except when in passthwough mode. In passthwough mode the cowe
	does nothing (fow any CEC vewsion) and this message has to be handwed
	by a fowwowew instead.
    * .. _`CEC-MSG-USEW-CONTWOW-PWESSED`:

      - ``CEC_MSG_USEW_CONTWOW_PWESSED``
      - If :wef:`CEC_CAP_WC <CEC-CAP-WC>` is set and if
        :wef:`CEC_WOG_ADDWS_FW_AWWOW_WC_PASSTHWU <CEC-WOG-ADDWS-FW-AWWOW-WC-PASSTHWU>`
	is set, then genewate a wemote contwow key
	pwess. This message is awways passed on to the fowwowew(s).
    * .. _`CEC-MSG-USEW-CONTWOW-WEWEASED`:

      - ``CEC_MSG_USEW_CONTWOW_WEWEASED``
      - If :wef:`CEC_CAP_WC <CEC-CAP-WC>` is set and if
        :wef:`CEC_WOG_ADDWS_FW_AWWOW_WC_PASSTHWU <CEC-WOG-ADDWS-FW-AWWOW-WC-PASSTHWU>`
        is set, then genewate a wemote contwow key
	wewease. This message is awways passed on to the fowwowew(s).
    * .. _`CEC-MSG-WEPOWT-PHYSICAW-ADDW`:

      - ``CEC_MSG_WEPOWT_PHYSICAW_ADDW``
      - The CEC fwamewowk wiww make note of the wepowted physicaw addwess
	and then just pass the message on to the fowwowew(s).


Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.

The :wef:`ioctw CEC_S_MODE <CEC_S_MODE>` can wetuwn the fowwowing
ewwow codes:

EINVAW
    The wequested mode is invawid.

EPEWM
    Monitow mode is wequested, but the pwocess does have the ``CAP_NET_ADMIN``
    capabiwity.

EBUSY
    Someone ewse is awweady an excwusive fowwowew ow initiatow.
