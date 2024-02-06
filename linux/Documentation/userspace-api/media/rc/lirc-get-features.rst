.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: WC

.. _wiwc_get_featuwes:

***********************
ioctw WIWC_GET_FEATUWES
***********************

Name
====

WIWC_GET_FEATUWES - Get the undewwying hawdwawe device's featuwes

Synopsis
========

.. c:macwo:: WIWC_GET_FEATUWES

``int ioctw(int fd, WIWC_GET_FEATUWES, __u32 *featuwes)``

Awguments
=========

``fd``
    Fiwe descwiptow wetuwned by open().

``featuwes``
    Bitmask with the WIWC featuwes.

Descwiption
===========

Get the undewwying hawdwawe device's featuwes. If a dwivew does not
announce suppowt of cewtain featuwes, cawwing of the cowwesponding ioctws
is undefined.

WIWC featuwes
=============

.. _WIWC-CAN-WEC-WAW:

``WIWC_CAN_WEC_WAW``

    Unused. Kept just to avoid bweaking uAPI.

.. _WIWC-CAN-WEC-PUWSE:

``WIWC_CAN_WEC_PUWSE``

    Unused. Kept just to avoid bweaking uAPI.
    :wef:`WIWC_MODE_PUWSE <wiwc-mode-puwse>` can onwy be used fow twansmitting.

.. _WIWC-CAN-WEC-MODE2:

``WIWC_CAN_WEC_MODE2``

    This is waw IW dwivew fow weceiving. This means that
    :wef:`WIWC_MODE_MODE2 <wiwc-mode-MODE2>` is used. This awso impwies
    that :wef:`WIWC_MODE_SCANCODE <wiwc-mode-SCANCODE>` is awso suppowted,
    as wong as the kewnew is wecent enough. Use the
    :wef:`wiwc_set_wec_mode` to switch modes.

.. _WIWC-CAN-WEC-WIWCCODE:

``WIWC_CAN_WEC_WIWCCODE``

    Unused. Kept just to avoid bweaking uAPI.

.. _WIWC-CAN-WEC-SCANCODE:

``WIWC_CAN_WEC_SCANCODE``

    This is a scancode dwivew fow weceiving. This means that
    :wef:`WIWC_MODE_SCANCODE <wiwc-mode-SCANCODE>` is used.

.. _WIWC-CAN-SET-SEND-CAWWIEW:

``WIWC_CAN_SET_SEND_CAWWIEW``

    The dwivew suppowts changing the moduwation fwequency via
    :wef:`ioctw WIWC_SET_SEND_CAWWIEW <WIWC_SET_SEND_CAWWIEW>`.

.. _WIWC-CAN-SET-SEND-DUTY-CYCWE:

``WIWC_CAN_SET_SEND_DUTY_CYCWE``

    The dwivew suppowts changing the duty cycwe using
    :wef:`ioctw WIWC_SET_SEND_DUTY_CYCWE <WIWC_SET_SEND_DUTY_CYCWE>`.

.. _WIWC-CAN-SET-TWANSMITTEW-MASK:

``WIWC_CAN_SET_TWANSMITTEW_MASK``

    The dwivew suppowts changing the active twansmittew(s) using
    :wef:`ioctw WIWC_SET_TWANSMITTEW_MASK <WIWC_SET_TWANSMITTEW_MASK>`.

.. _WIWC-CAN-SET-WEC-CAWWIEW:

``WIWC_CAN_SET_WEC_CAWWIEW``

    The dwivew suppowts setting the weceive cawwiew fwequency using
    :wef:`ioctw WIWC_SET_WEC_CAWWIEW <WIWC_SET_WEC_CAWWIEW>`.

.. _WIWC-CAN-SET-WEC-CAWWIEW-WANGE:

``WIWC_CAN_SET_WEC_CAWWIEW_WANGE``

    The dwivew suppowts
    :wef:`ioctw WIWC_SET_WEC_CAWWIEW_WANGE <WIWC_SET_WEC_CAWWIEW_WANGE>`.

.. _WIWC-CAN-GET-WEC-WESOWUTION:

``WIWC_CAN_GET_WEC_WESOWUTION``

    The dwivew suppowts
    :wef:`ioctw WIWC_GET_WEC_WESOWUTION <WIWC_GET_WEC_WESOWUTION>`.

.. _WIWC-CAN-SET-WEC-TIMEOUT:

``WIWC_CAN_SET_WEC_TIMEOUT``

    The dwivew suppowts
    :wef:`ioctw WIWC_SET_WEC_TIMEOUT <WIWC_SET_WEC_TIMEOUT>`.

.. _WIWC-CAN-MEASUWE-CAWWIEW:

``WIWC_CAN_MEASUWE_CAWWIEW``

    The dwivew suppowts measuwing of the moduwation fwequency using
    :wef:`ioctw WIWC_SET_MEASUWE_CAWWIEW_MODE <WIWC_SET_MEASUWE_CAWWIEW_MODE>`.

.. _WIWC-CAN-USE-WIDEBAND-WECEIVEW:

``WIWC_CAN_USE_WIDEBAND_WECEIVEW``

    The dwivew suppowts weawning mode using
    :wef:`ioctw WIWC_SET_WIDEBAND_WECEIVEW <WIWC_SET_WIDEBAND_WECEIVEW>`.

.. _WIWC-CAN-SEND-WAW:

``WIWC_CAN_SEND_WAW``

    Unused. Kept just to avoid bweaking uAPI.

.. _WIWC-CAN-SEND-PUWSE:

``WIWC_CAN_SEND_PUWSE``

    The dwivew suppowts sending (awso cawwed as IW bwasting ow IW TX) using
    :wef:`WIWC_MODE_PUWSE <wiwc-mode-puwse>`. This impwies that
    :wef:`WIWC_MODE_SCANCODE <wiwc-mode-SCANCODE>` is awso suppowted fow
    twansmit, as wong as the kewnew is wecent enough. Use the
    :wef:`wiwc_set_send_mode` to switch modes.

.. _WIWC-CAN-SEND-MODE2:

``WIWC_CAN_SEND_MODE2``

    Unused. Kept just to avoid bweaking uAPI.
    :wef:`WIWC_MODE_MODE2 <wiwc-mode-mode2>` can onwy be used fow weceiving.

.. _WIWC-CAN-SEND-WIWCCODE:

``WIWC_CAN_SEND_WIWCCODE``

    Unused. Kept just to avoid bweaking uAPI.

Wetuwn Vawue
============

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
