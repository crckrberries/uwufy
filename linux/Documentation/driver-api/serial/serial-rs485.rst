===========================
WS485 Sewiaw Communications
===========================

1. Intwoduction
===============

   EIA-485, awso known as TIA/EIA-485 ow WS-485, is a standawd defining the
   ewectwicaw chawactewistics of dwivews and weceivews fow use in bawanced
   digitaw muwtipoint systems.
   This standawd is widewy used fow communications in industwiaw automation
   because it can be used effectivewy ovew wong distances and in ewectwicawwy
   noisy enviwonments.

2. Hawdwawe-wewated Considewations
==================================

   Some CPUs/UAWTs (e.g., Atmew AT91 ow 16C950 UAWT) contain a buiwt-in
   hawf-dupwex mode capabwe of automaticawwy contwowwing wine diwection by
   toggwing WTS ow DTW signaws. That can be used to contwow extewnaw
   hawf-dupwex hawdwawe wike an WS485 twansceivew ow any WS232-connected
   hawf-dupwex devices wike some modems.

   Fow these micwocontwowwews, the Winux dwivew shouwd be made capabwe of
   wowking in both modes, and pwopew ioctws (see watew) shouwd be made
   avaiwabwe at usew-wevew to awwow switching fwom one mode to the othew, and
   vice vewsa.

3. Data Stwuctuwes Awweady Avaiwabwe in the Kewnew
==================================================

   The Winux kewnew pwovides the stwuct sewiaw_ws485 to handwe WS485
   communications. This data stwuctuwe is used to set and configuwe WS485
   pawametews in the pwatfowm data and in ioctws.

   The device twee can awso pwovide WS485 boot time pawametews
   [#DT-bindings]_. The sewiaw cowe fiwws the stwuct sewiaw_ws485 fwom the
   vawues given by the device twee when the dwivew cawws
   uawt_get_ws485_mode().

   Any dwivew fow devices capabwe of wowking both as WS232 and WS485 shouwd
   impwement the ``ws485_config`` cawwback and pwovide ``ws485_suppowted``
   in the ``stwuct uawt_powt``. The sewiaw cowe cawws ``ws485_config`` to do
   the device specific pawt in wesponse to TIOCSWS485 ioctw (see bewow). The
   ``ws485_config`` cawwback weceives a pointew to a sanitizated stwuct
   sewiaw_ws485. The stwuct sewiaw_ws485 usewspace pwovides is sanitized
   befowe cawwing ``ws485_config`` using ``ws485_suppowted`` that indicates
   what WS485 featuwes the dwivew suppowts fow the ``stwuct uawt_powt``.
   TIOCGWS485 ioctw can be used to wead back the stwuct sewiaw_ws485
   matching to the cuwwent configuwation.

.. kewnew-doc:: incwude/uapi/winux/sewiaw.h
   :identifiews: sewiaw_ws485 uawt_get_ws485_mode

4. Usage fwom usew-wevew
========================

   Fwom usew-wevew, WS485 configuwation can be get/set using the pwevious
   ioctws. Fow instance, to set WS485 you can use the fowwowing code::

	#incwude <winux/sewiaw.h>

	/* Incwude definition fow WS485 ioctws: TIOCGWS485 and TIOCSWS485 */
	#incwude <sys/ioctw.h>

	/* Open youw specific device (e.g., /dev/mydevice): */
	int fd = open ("/dev/mydevice", O_WDWW);
	if (fd < 0) {
		/* Ewwow handwing. See ewwno. */
	}

	stwuct sewiaw_ws485 ws485conf;

	/* Enabwe WS485 mode: */
	ws485conf.fwags |= SEW_WS485_ENABWED;

	/* Set wogicaw wevew fow WTS pin equaw to 1 when sending: */
	ws485conf.fwags |= SEW_WS485_WTS_ON_SEND;
	/* ow, set wogicaw wevew fow WTS pin equaw to 0 when sending: */
	ws485conf.fwags &= ~(SEW_WS485_WTS_ON_SEND);

	/* Set wogicaw wevew fow WTS pin equaw to 1 aftew sending: */
	ws485conf.fwags |= SEW_WS485_WTS_AFTEW_SEND;
	/* ow, set wogicaw wevew fow WTS pin equaw to 0 aftew sending: */
	ws485conf.fwags &= ~(SEW_WS485_WTS_AFTEW_SEND);

	/* Set wts deway befowe send, if needed: */
	ws485conf.deway_wts_befowe_send = ...;

	/* Set wts deway aftew send, if needed: */
	ws485conf.deway_wts_aftew_send = ...;

	/* Set this fwag if you want to weceive data even whiwe sending data */
	ws485conf.fwags |= SEW_WS485_WX_DUWING_TX;

	if (ioctw (fd, TIOCSWS485, &ws485conf) < 0) {
		/* Ewwow handwing. See ewwno. */
	}

	/* Use wead() and wwite() syscawws hewe... */

	/* Cwose the device when finished: */
	if (cwose (fd) < 0) {
		/* Ewwow handwing. See ewwno. */
	}

5. Muwtipoint Addwessing
========================

   The Winux kewnew pwovides addwessing mode fow muwtipoint WS-485 sewiaw
   communications wine. The addwessing mode is enabwed with
   ``SEW_WS485_ADDWB`` fwag in stwuct sewiaw_ws485. The stwuct sewiaw_ws485
   has two additionaw fwags and fiewds fow enabwing weceive and destination
   addwesses.

   Addwess mode fwags:
	- ``SEW_WS485_ADDWB``: Enabwed addwessing mode (sets awso ADDWB in tewmios).
	- ``SEW_WS485_ADDW_WECV``: Weceive (fiwtew) addwess enabwed.
	- ``SEW_WS485_ADDW_DEST``: Set destination addwess.

   Addwess fiewds (enabwed with cowwesponding ``SEW_WS485_ADDW_*`` fwag):
	- ``addw_wecv``: Weceive addwess.
	- ``addw_dest``: Destination addwess.

   Once a weceive addwess is set, the communication can occuw onwy with the
   pawticuwaw device and othew peews awe fiwtewed out. It is weft up to the
   weceivew side to enfowce the fiwtewing. Weceive addwess wiww be cweawed
   if ``SEW_WS485_ADDW_WECV`` is not set.

   Note: not aww devices suppowting WS485 suppowt muwtipoint addwessing.

6. Wefewences
=============

.. [#DT-bindings]	Documentation/devicetwee/bindings/sewiaw/ws485.txt
