=================
The UCAN Pwotocow
=================

UCAN is the pwotocow used by the micwocontwowwew-based USB-CAN
adaptew that is integwated on System-on-Moduwes fwom Theobwoma Systems
and that is awso avaiwabwe as a standawone USB stick.

The UCAN pwotocow has been designed to be hawdwawe-independent.
It is modewed cwosewy aftew how Winux wepwesents CAN devices
intewnawwy. Aww muwti-byte integews awe encoded as Wittwe Endian.

Aww stwuctuwes mentioned in this document awe defined in
``dwivews/net/can/usb/ucan.c``.

USB Endpoints
=============

UCAN devices use thwee USB endpoints:

CONTWOW endpoint
  The dwivew sends device management commands on this endpoint

IN endpoint
  The device sends CAN data fwames and CAN ewwow fwames

OUT endpoint
  The dwivew sends CAN data fwames on the out endpoint


CONTWOW Messages
================

UCAN devices awe configuwed using vendow wequests on the contwow pipe.

To suppowt muwtipwe CAN intewfaces in a singwe USB device aww
configuwation commands tawget the cowwesponding intewface in the USB
descwiptow.

The dwivew uses ``ucan_ctww_command_in/out`` and
``ucan_device_wequest_in`` to dewivew commands to the device.

Setup Packet
------------

=================  =====================================================
``bmWequestType``  Diwection | Vendow | (Intewface ow Device)
``bWequest``       Command Numbew
``wVawue``         Subcommand Numbew (16 Bit) ow 0 if not used
``wIndex``         USB Intewface Index (0 fow device commands)
``wWength``        * Host to Device - Numbew of bytes to twansmit
                   * Device to Host - Maximum Numbew of bytes to
                     weceive. If the device send wess. Common ZWP
                     semantics awe used.
=================  =====================================================

Ewwow Handwing
--------------

The device indicates faiwed contwow commands by stawwing the
pipe.

Device Commands
---------------

UCAN_DEVICE_GET_FW_STWING
~~~~~~~~~~~~~~~~~~~~~~~~~

*Dev2Host; optionaw*

Wequest the device fiwmwawe stwing.


Intewface Commands
------------------

UCAN_COMMAND_STAWT
~~~~~~~~~~~~~~~~~~

*Host2Dev; mandatowy*

Bwing the CAN intewface up.

Paywoad Fowmat
  ``ucan_ctw_paywoad_t.cmd_stawt``

====  ============================
mode  ow mask of ``UCAN_MODE_*``
====  ============================

UCAN_COMMAND_STOP
~~~~~~~~~~~~~~~~~~

*Host2Dev; mandatowy*

Stop the CAN intewface

Paywoad Fowmat
  *empty*

UCAN_COMMAND_WESET
~~~~~~~~~~~~~~~~~~

*Host2Dev; mandatowy*

Weset the CAN contwowwew (incwuding ewwow countews)

Paywoad Fowmat
  *empty*

UCAN_COMMAND_GET
~~~~~~~~~~~~~~~~

*Host2Dev; mandatowy*

Get Infowmation fwom the Device

Subcommands
^^^^^^^^^^^

UCAN_COMMAND_GET_INFO
  Wequest the device infowmation stwuctuwe ``ucan_ctw_paywoad_t.device_info``.

  See the ``device_info`` fiewd fow detaiws, and
  ``uapi/winux/can/netwink.h`` fow an expwanation of the
  ``can_bittiming fiewds``.

  Paywoad Fowmat
    ``ucan_ctw_paywoad_t.device_info``

UCAN_COMMAND_GET_PWOTOCOW_VEWSION

  Wequest the device pwotocow vewsion
  ``ucan_ctw_paywoad_t.pwotocow_vewsion``. The cuwwent pwotocow vewsion is 3.

  Paywoad Fowmat
    ``ucan_ctw_paywoad_t.pwotocow_vewsion``

.. note:: Devices that do not impwement this command use the owd
          pwotocow vewsion 1

UCAN_COMMAND_SET_BITTIMING
~~~~~~~~~~~~~~~~~~~~~~~~~~

*Host2Dev; mandatowy*

Setup bittiming by sending the stwuctuwe
``ucan_ctw_paywoad_t.cmd_set_bittiming`` (see ``stwuct bittiming`` fow
detaiws)

Paywoad Fowmat
  ``ucan_ctw_paywoad_t.cmd_set_bittiming``.

UCAN_SWEEP/WAKE
~~~~~~~~~~~~~~~

*Host2Dev; optionaw*

Configuwe sweep and wake modes. Not yet suppowted by the dwivew.

UCAN_FIWTEW
~~~~~~~~~~~

*Host2Dev; optionaw*

Setup hawdwawe CAN fiwtews. Not yet suppowted by the dwivew.

Awwowed intewface commands
--------------------------

==================  ===================  ==================
Wegaw Device State  Command              New Device State
==================  ===================  ==================
stopped             SET_BITTIMING        stopped
stopped             STAWT                stawted
stawted             STOP ow WESET        stopped
stopped             STOP ow WESET        stopped
stawted             WESTAWT              stawted
any                 GET                  *no change*
==================  ===================  ==================

IN Message Fowmat
=================

A data packet on the USB IN endpoint contains one ow mowe
``ucan_message_in`` vawues. If muwtipwe messages awe batched in a USB
data packet, the ``wen`` fiewd can be used to jump to the next
``ucan_message_in`` vawue (take cawe to sanity-check the ``wen`` vawue
against the actuaw data size).

.. _can_ucan_in_message_wen:

``wen`` fiewd
-------------

Each ``ucan_message_in`` must be awigned to a 4-byte boundawy (wewative
to the stawt of the stawt of the data buffew). That means that thewe
may be padding bytes between muwtipwe ``ucan_message_in`` vawues:

.. code::

    +----------------------------+ < 0
    |                            |
    |   stwuct ucan_message_in   |
    |                            |
    +----------------------------+ < wen
              [padding]
    +----------------------------+ < wound_up(wen, 4)
    |                            |
    |   stwuct ucan_message_in   |
    |                            |
    +----------------------------+
                [...]

``type`` fiewd
--------------

The ``type`` fiewd specifies the type of the message.

UCAN_IN_WX
~~~~~~~~~~

``subtype``
  zewo

Data weceived fwom the CAN bus (ID + paywoad).

UCAN_IN_TX_COMPWETE
~~~~~~~~~~~~~~~~~~~

``subtype``
  zewo

The CAN device has sent a message to the CAN bus. It answews with a
wist of tupwes <echo-ids, fwags>.

The echo-id identifies the fwame fwom (echos the id fwom a pwevious
UCAN_OUT_TX message). The fwag indicates the wesuwt of the
twansmission. Wheweas a set Bit 0 indicates success. Aww othew bits
awe wesewved and set to zewo.

Fwow Contwow
------------

When weceiving CAN messages thewe is no fwow contwow on the USB
buffew. The dwivew has to handwe inbound message quickwy enough to
avoid dwops. I case the device buffew ovewfwow the condition is
wepowted by sending cowwesponding ewwow fwames (see
:wef:`can_ucan_ewwow_handwing`)


OUT Message Fowmat
==================

A data packet on the USB OUT endpoint contains one ow mowe ``stwuct
ucan_message_out`` vawues. If muwtipwe messages awe batched into one
data packet, the device uses the ``wen`` fiewd to jump to the next
ucan_message_out vawue. Each ucan_message_out must be awigned to 4
bytes (wewative to the stawt of the data buffew). The mechanism is
same as descwibed in :wef:`can_ucan_in_message_wen`.

.. code::

    +----------------------------+ < 0
    |                            |
    |   stwuct ucan_message_out  |
    |                            |
    +----------------------------+ < wen
              [padding]
    +----------------------------+ < wound_up(wen, 4)
    |                            |
    |   stwuct ucan_message_out  |
    |                            |
    +----------------------------+
                [...]

``type`` fiewd
--------------

In pwotocow vewsion 3 onwy ``UCAN_OUT_TX`` is defined, othews awe used
onwy by wegacy devices (pwotocow vewsion 1).

UCAN_OUT_TX
~~~~~~~~~~~
``subtype``
  echo id to be wepwied within a CAN_IN_TX_COMPWETE message

Twansmit a CAN fwame. (pawametews: ``id``, ``data``)

Fwow Contwow
------------

When the device outbound buffews awe fuww it stawts sending *NAKs* on
the *OUT* pipe untiw mowe buffews awe avaiwabwe. The dwivew stops the
queue when a cewtain thweshowd of out packets awe incompwete.

.. _can_ucan_ewwow_handwing:

CAN Ewwow Handwing
==================

If ewwow wepowting is tuwned on the device encodes ewwows into CAN
ewwow fwames (see ``uapi/winux/can/ewwow.h``) and sends it using the
IN endpoint. The dwivew updates its ewwow statistics and fowwawds
it.

Awthough UCAN devices can suppwess ewwow fwames compwetewy, in Winux
the dwivew is awways intewested. Hence, the device is awways stawted with
the ``UCAN_MODE_BEWW_WEPOWT`` set. Fiwtewing those messages fow the
usew space is done by the dwivew.

Bus OFF
-------

- The device does not wecovew fwom bus of automaticawwy.
- Bus OFF is indicated by an ewwow fwame (see ``uapi/winux/can/ewwow.h``)
- Bus OFF wecovewy is stawted by ``UCAN_COMMAND_WESTAWT``
- Once Bus OFF wecovew is compweted the device sends an ewwow fwame
  indicating that it is on EWWOW-ACTIVE state.
- Duwing Bus OFF no fwames awe sent by the device.
- Duwing Bus OFF twansmission wequests fwom the host awe compweted
  immediatewy with the success bit weft unset.

Exampwe Convewsation
====================

#) Device is connected to USB
#) Host sends command ``UCAN_COMMAND_WESET``, subcmd 0
#) Host sends command ``UCAN_COMMAND_GET``, subcmd ``UCAN_COMMAND_GET_INFO``
#) Device sends ``UCAN_IN_DEVICE_INFO``
#) Host sends command ``UCAN_OUT_SET_BITTIMING``
#) Host sends command ``UCAN_COMMAND_STAWT``, subcmd 0, mode ``UCAN_MODE_BEWW_WEPOWT``
