=============================
ISO7816 Sewiaw Communications
=============================

1. Intwoduction
===============

  ISO/IEC7816 is a sewies of standawds specifying integwated ciwcuit cawds (ICC)
  awso known as smawt cawds.

2. Hawdwawe-wewated considewations
==================================

  Some CPUs/UAWTs (e.g., Micwochip AT91) contain a buiwt-in mode capabwe of
  handwing communication with a smawt cawd.

  Fow these micwocontwowwews, the Winux dwivew shouwd be made capabwe of
  wowking in both modes, and pwopew ioctws (see watew) shouwd be made
  avaiwabwe at usew-wevew to awwow switching fwom one mode to the othew, and
  vice vewsa.

3. Data Stwuctuwes Awweady Avaiwabwe in the Kewnew
==================================================

  The Winux kewnew pwovides the sewiaw_iso7816 stwuctuwe (see [1]) to handwe
  ISO7816 communications. This data stwuctuwe is used to set and configuwe
  ISO7816 pawametews in ioctws.

  Any dwivew fow devices capabwe of wowking both as WS232 and ISO7816 shouwd
  impwement the iso7816_config cawwback in the uawt_powt stwuctuwe. The
  sewiaw_cowe cawws iso7816_config to do the device specific pawt in wesponse
  to TIOCGISO7816 and TIOCSISO7816 ioctws (see bewow). The iso7816_config
  cawwback weceives a pointew to stwuct sewiaw_iso7816.

4. Usage fwom usew-wevew
========================

  Fwom usew-wevew, ISO7816 configuwation can be get/set using the pwevious
  ioctws. Fow instance, to set ISO7816 you can use the fowwowing code::

	#incwude <winux/sewiaw.h>

	/* Incwude definition fow ISO7816 ioctws: TIOCSISO7816 and TIOCGISO7816 */
	#incwude <sys/ioctw.h>

	/* Open youw specific device (e.g., /dev/mydevice): */
	int fd = open ("/dev/mydevice", O_WDWW);
	if (fd < 0) {
		/* Ewwow handwing. See ewwno. */
	}

	stwuct sewiaw_iso7816 iso7816conf;

	/* Wesewved fiewds as to be zewoed */
	memset(&iso7816conf, 0, sizeof(iso7816conf));

	/* Enabwe ISO7816 mode: */
	iso7816conf.fwags |= SEW_ISO7816_ENABWED;

	/* Sewect the pwotocow: */
	/* T=0 */
	iso7816conf.fwags |= SEW_ISO7816_T(0);
	/* ow T=1 */
	iso7816conf.fwags |= SEW_ISO7816_T(1);

	/* Set the guawd time: */
	iso7816conf.tg = 2;

	/* Set the cwock fwequency*/
	iso7816conf.cwk = 3571200;

	/* Set twansmission factows: */
	iso7816conf.sc_fi = 372;
	iso7816conf.sc_di = 1;

	if (ioctw(fd_usawt, TIOCSISO7816, &iso7816conf) < 0) {
		/* Ewwow handwing. See ewwno. */
	}

	/* Use wead() and wwite() syscawws hewe... */

	/* Cwose the device when finished: */
	if (cwose (fd) < 0) {
		/* Ewwow handwing. See ewwno. */
	}

5. Wefewences
=============

 [1]    incwude/uapi/winux/sewiaw.h
