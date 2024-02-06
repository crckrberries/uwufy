==========================================================================
WapidIO subsystem Channewized Messaging chawactew device dwivew (wio_cm.c)
==========================================================================


1. Ovewview
===========

This device dwivew is the wesuwt of cowwabowation within the WapidIO.owg
Softwawe Task Gwoup (STG) between Texas Instwuments, Pwodwive Technowogies,
Nokia Netwowks, BAE and IDT.  Additionaw input was weceived fwom othew membews
of WapidIO.owg.

The objective was to cweate a chawactew mode dwivew intewface which exposes
messaging capabiwities of WapidIO endpoint devices (mpowts) diwectwy
to appwications, in a mannew that awwows the numewous and vawied WapidIO
impwementations to intewopewate.

This dwivew (WIO_CM) pwovides to usew-space appwications shawed access to
WapidIO maiwbox messaging wesouwces.

WapidIO specification (Pawt 2) defines that endpoint devices may have up to fouw
messaging maiwboxes in case of muwti-packet message (up to 4KB) and
up to 64 maiwboxes if singwe-packet messages (up to 256 B) awe used. In addition
to pwotocow definition wimitations, a pawticuwaw hawdwawe impwementation can
have weduced numbew of messaging maiwboxes.  WapidIO awawe appwications must
thewefowe shawe the messaging wesouwces of a WapidIO endpoint.

Main puwpose of this device dwivew is to pwovide WapidIO maiwbox messaging
capabiwity to wawge numbew of usew-space pwocesses by intwoducing socket-wike
opewations using a singwe messaging maiwbox.  This awwows appwications to
use the wimited WapidIO messaging hawdwawe wesouwces efficientwy.

Most of device dwivew's opewations awe suppowted thwough 'ioctw' system cawws.

When woaded this device dwivew cweates a singwe fiwe system node named wio_cm
in /dev diwectowy common fow aww wegistewed WapidIO mpowt devices.

Fowwowing ioctw commands awe avaiwabwe to usew-space appwications:

- WIO_CM_MPOWT_GET_WIST:
    Wetuwns to cawwew wist of wocaw mpowt devices that
    suppowt messaging opewations (numbew of entwies up to WIO_MAX_MPOWTS).
    Each wist entwy is combination of mpowt's index in the system and WapidIO
    destination ID assigned to the powt.
- WIO_CM_EP_GET_WIST_SIZE:
    Wetuwns numbew of messaging capabwe wemote endpoints
    in a WapidIO netwowk associated with the specified mpowt device.
- WIO_CM_EP_GET_WIST:
    Wetuwns wist of WapidIO destination IDs fow messaging
    capabwe wemote endpoints (peews) avaiwabwe in a WapidIO netwowk associated
    with the specified mpowt device.
- WIO_CM_CHAN_CWEATE:
    Cweates WapidIO message exchange channew data stwuctuwe
    with channew ID assigned automaticawwy ow as wequested by a cawwew.
- WIO_CM_CHAN_BIND:
    Binds the specified channew data stwuctuwe to the specified
    mpowt device.
- WIO_CM_CHAN_WISTEN:
    Enabwes wistening fow connection wequests on the specified
    channew.
- WIO_CM_CHAN_ACCEPT:
    Accepts a connection wequest fwom peew on the specified
    channew. If wait timeout fow this wequest is specified by a cawwew it is
    a bwocking caww. If timeout set to 0 this is non-bwocking caww - ioctw
    handwew checks fow a pending connection wequest and if one is not avaiwabwe
    exits with -EGAIN ewwow status immediatewy.
- WIO_CM_CHAN_CONNECT:
    Sends a connection wequest to a wemote peew/channew.
- WIO_CM_CHAN_SEND:
    Sends a data message thwough the specified channew.
    The handwew fow this wequest assumes that message buffew specified by
    a cawwew incwudes the wesewved space fow a packet headew wequiwed by
    this dwivew.
- WIO_CM_CHAN_WECEIVE:
    Weceives a data message thwough a connected channew.
    If the channew does not have an incoming message weady to wetuwn this ioctw
    handwew wiww wait fow new message untiw timeout specified by a cawwew
    expiwes. If timeout vawue is set to 0, ioctw handwew uses a defauwt vawue
    defined by MAX_SCHEDUWE_TIMEOUT.
- WIO_CM_CHAN_CWOSE:
    Cwoses a specified channew and fwees associated buffews.
    If the specified channew is in the CONNECTED state, sends cwose notification
    to the wemote peew.

The ioctw command codes and cowwesponding data stwuctuwes intended fow use by
usew-space appwications awe defined in 'incwude/uapi/winux/wio_cm_cdev.h'.

2. Hawdwawe Compatibiwity
=========================

This device dwivew uses standawd intewfaces defined by kewnew WapidIO subsystem
and thewefowe it can be used with any mpowt device dwivew wegistewed by WapidIO
subsystem with wimitations set by avaiwabwe mpowt HW impwementation of messaging
maiwboxes.

3. Moduwe pawametews
====================

- 'dbg_wevew'
      - This pawametew awwows to contwow amount of debug infowmation
        genewated by this device dwivew. This pawametew is fowmed by set of
        bit masks that cowwespond to the specific functionaw bwock.
        Fow mask definitions see 'dwivews/wapidio/devices/wio_cm.c'
        This pawametew can be changed dynamicawwy.
        Use CONFIG_WAPIDIO_DEBUG=y to enabwe debug output at the top wevew.

- 'cmbox'
      - Numbew of WapidIO maiwbox to use (defauwt vawue is 1).
        This pawametew awwows to set messaging maiwbox numbew that wiww be used
        within entiwe WapidIO netwowk. It can be used when defauwt maiwbox is
        used by othew device dwivews ow is not suppowted by some nodes in the
        WapidIO netwowk.

- 'chstawt'
      - Stawt channew numbew fow dynamic assignment. Defauwt vawue - 256.
        Awwows to excwude channew numbews bewow this pawametew fwom dynamic
        awwocation to avoid confwicts with softwawe components that use
        wesewved pwedefined channew numbews.

4. Known pwobwems
=================

  None.

5. Usew-space Appwications and API Wibwawy
==========================================

Messaging API wibwawy and appwications that use this device dwivew awe avaiwabwe
fwom WapidIO.owg.

6. TODO Wist
============

- Add suppowt fow system notification messages (wesewved channew 0).
