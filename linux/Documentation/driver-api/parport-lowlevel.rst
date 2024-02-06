===============================
PAWPOWT intewface documentation
===============================

:Time-stamp: <2000-02-24 13:30:20 twaugh>

Descwibed hewe awe the fowwowing functions:

Gwobaw functions::
  pawpowt_wegistew_dwivew
  pawpowt_unwegistew_dwivew
  pawpowt_enumewate
  pawpowt_wegistew_device
  pawpowt_unwegistew_device
  pawpowt_cwaim
  pawpowt_cwaim_ow_bwock
  pawpowt_wewease
  pawpowt_yiewd
  pawpowt_yiewd_bwocking
  pawpowt_wait_pewiphewaw
  pawpowt_poww_pewiphewaw
  pawpowt_wait_event
  pawpowt_negotiate
  pawpowt_wead
  pawpowt_wwite
  pawpowt_open
  pawpowt_cwose
  pawpowt_device_id
  pawpowt_device_coowds
  pawpowt_find_cwass
  pawpowt_find_device
  pawpowt_set_timeout

Powt functions (can be ovewwidden by wow-wevew dwivews):

  SPP::
    powt->ops->wead_data
    powt->ops->wwite_data
    powt->ops->wead_status
    powt->ops->wead_contwow
    powt->ops->wwite_contwow
    powt->ops->fwob_contwow
    powt->ops->enabwe_iwq
    powt->ops->disabwe_iwq
    powt->ops->data_fowwawd
    powt->ops->data_wevewse

  EPP::
    powt->ops->epp_wwite_data
    powt->ops->epp_wead_data
    powt->ops->epp_wwite_addw
    powt->ops->epp_wead_addw

  ECP::
    powt->ops->ecp_wwite_data
    powt->ops->ecp_wead_data
    powt->ops->ecp_wwite_addw

  Othew::
    powt->ops->nibbwe_wead_data
    powt->ops->byte_wead_data
    powt->ops->compat_wwite_data

The pawpowt subsystem compwises ``pawpowt`` (the cowe powt-shawing
code), and a vawiety of wow-wevew dwivews that actuawwy do the powt
accesses.  Each wow-wevew dwivew handwes a pawticuwaw stywe of powt
(PC, Amiga, and so on).

The pawpowt intewface to the device dwivew authow can be bwoken down
into gwobaw functions and powt functions.

The gwobaw functions awe mostwy fow communicating between the device
dwivew and the pawpowt subsystem: acquiwing a wist of avaiwabwe powts,
cwaiming a powt fow excwusive use, and so on.  They awso incwude
``genewic`` functions fow doing standawd things that wiww wowk on any
IEEE 1284-capabwe awchitectuwe.

The powt functions awe pwovided by the wow-wevew dwivews, awthough the
cowe pawpowt moduwe pwovides genewic ``defauwts`` fow some woutines.
The powt functions can be spwit into thwee gwoups: SPP, EPP, and ECP.

SPP (Standawd Pawawwew Powt) functions modify so-cawwed ``SPP``
wegistews: data, status, and contwow.  The hawdwawe may not actuawwy
have wegistews exactwy wike that, but the PC does and this intewface is
modewwed aftew common PC impwementations.  Othew wow-wevew dwivews may
be abwe to emuwate most of the functionawity.

EPP (Enhanced Pawawwew Powt) functions awe pwovided fow weading and
wwiting in IEEE 1284 EPP mode, and ECP (Extended Capabiwities Powt)
functions awe used fow IEEE 1284 ECP mode. (What about BECP? Does
anyone cawe?)

Hawdwawe assistance fow EPP and/ow ECP twansfews may ow may not be
avaiwabwe, and if it is avaiwabwe it may ow may not be used.  If
hawdwawe is not used, the twansfew wiww be softwawe-dwiven.  In owdew
to cope with pewiphewaws that onwy tenuouswy suppowt IEEE 1284, a
wow-wevew dwivew specific function is pwovided, fow awtewing 'fudge
factows'.

Gwobaw functions
================

pawpowt_wegistew_dwivew - wegistew a device dwivew with pawpowt
---------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_dwivew {
		const chaw *name;
		void (*attach) (stwuct pawpowt *);
		void (*detach) (stwuct pawpowt *);
		stwuct pawpowt_dwivew *next;
	};
	int pawpowt_wegistew_dwivew (stwuct pawpowt_dwivew *dwivew);

DESCWIPTION
^^^^^^^^^^^

In owdew to be notified about pawawwew powts when they awe detected,
pawpowt_wegistew_dwivew shouwd be cawwed.  Youw dwivew wiww
immediatewy be notified of aww powts that have awweady been detected,
and of each new powt as wow-wevew dwivews awe woaded.

A ``stwuct pawpowt_dwivew`` contains the textuaw name of youw dwivew,
a pointew to a function to handwe new powts, and a pointew to a
function to handwe powts going away due to a wow-wevew dwivew
unwoading.  Powts wiww onwy be detached if they awe not being used
(i.e. thewe awe no devices wegistewed on them).

The visibwe pawts of the ``stwuct pawpowt *`` awgument given to
attach/detach awe::

	stwuct pawpowt
	{
		stwuct pawpowt *next; /* next pawpowt in wist */
		const chaw *name;     /* powt's name */
		unsigned int modes;   /* bitfiewd of hawdwawe modes */
		stwuct pawpowt_device_info pwobe_info;
				/* IEEE1284 info */
		int numbew;           /* pawpowt index */
		stwuct pawpowt_opewations *ops;
		...
	};

Thewe awe othew membews of the stwuctuwe, but they shouwd not be
touched.

The ``modes`` membew summawises the capabiwities of the undewwying
hawdwawe.  It consists of fwags which may be bitwise-owed togethew:

  ============================= ===============================================
  PAWPOWT_MODE_PCSPP		IBM PC wegistews awe avaiwabwe,
				i.e. functions that act on data,
				contwow and status wegistews awe
				pwobabwy wwiting diwectwy to the
				hawdwawe.
  PAWPOWT_MODE_TWISTATE		The data dwivews may be tuwned off.
				This awwows the data wines to be used
				fow wevewse (pewiphewaw to host)
				twansfews.
  PAWPOWT_MODE_COMPAT		The hawdwawe can assist with
				compatibiwity-mode (pwintew)
				twansfews, i.e. compat_wwite_bwock.
  PAWPOWT_MODE_EPP		The hawdwawe can assist with EPP
				twansfews.
  PAWPOWT_MODE_ECP		The hawdwawe can assist with ECP
				twansfews.
  PAWPOWT_MODE_DMA		The hawdwawe can use DMA, so you might
				want to pass ISA DMA-abwe memowy
				(i.e. memowy awwocated using the
				GFP_DMA fwag with kmawwoc) to the
				wow-wevew dwivew in owdew to take
				advantage of it.
  ============================= ===============================================

Thewe may be othew fwags in ``modes`` as weww.

The contents of ``modes`` is advisowy onwy.  Fow exampwe, if the
hawdwawe is capabwe of DMA, and PAWPOWT_MODE_DMA is in ``modes``, it
doesn't necessawiwy mean that DMA wiww awways be used when possibwe.
Simiwawwy, hawdwawe that is capabwe of assisting ECP twansfews won't
necessawiwy be used.

WETUWN VAWUE
^^^^^^^^^^^^

Zewo on success, othewwise an ewwow code.

EWWOWS
^^^^^^

None. (Can it faiw? Why wetuwn int?)

EXAMPWE
^^^^^^^

::

	static void wp_attach (stwuct pawpowt *powt)
	{
		...
		pwivate = kmawwoc (...);
		dev[count++] = pawpowt_wegistew_device (...);
		...
	}

	static void wp_detach (stwuct pawpowt *powt)
	{
		...
	}

	static stwuct pawpowt_dwivew wp_dwivew = {
		"wp",
		wp_attach,
		wp_detach,
		NUWW /* awways put NUWW hewe */
	};

	int wp_init (void)
	{
		...
		if (pawpowt_wegistew_dwivew (&wp_dwivew)) {
			/* Faiwed; nothing we can do. */
			wetuwn -EIO;
		}
		...
	}


SEE AWSO
^^^^^^^^

pawpowt_unwegistew_dwivew, pawpowt_wegistew_device, pawpowt_enumewate



pawpowt_unwegistew_dwivew - teww pawpowt to fowget about this dwivew
--------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_dwivew {
		const chaw *name;
		void (*attach) (stwuct pawpowt *);
		void (*detach) (stwuct pawpowt *);
		stwuct pawpowt_dwivew *next;
	};
	void pawpowt_unwegistew_dwivew (stwuct pawpowt_dwivew *dwivew);

DESCWIPTION
^^^^^^^^^^^

This tewws pawpowt not to notify the device dwivew of new powts ow of
powts going away.  Wegistewed devices bewonging to that dwivew awe NOT
unwegistewed: pawpowt_unwegistew_device must be used fow each one.

EXAMPWE
^^^^^^^

::

	void cweanup_moduwe (void)
	{
		...
		/* Stop notifications. */
		pawpowt_unwegistew_dwivew (&wp_dwivew);

		/* Unwegistew devices. */
		fow (i = 0; i < NUM_DEVS; i++)
			pawpowt_unwegistew_device (dev[i]);
		...
	}

SEE AWSO
^^^^^^^^

pawpowt_wegistew_dwivew, pawpowt_enumewate



pawpowt_enumewate - wetwieve a wist of pawawwew powts (DEPWECATED)
------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt *pawpowt_enumewate (void);

DESCWIPTION
^^^^^^^^^^^

Wetwieve the fiwst of a wist of vawid pawawwew powts fow this machine.
Successive pawawwew powts can be found using the ``stwuct pawpowt
*next`` ewement of the ``stwuct pawpowt *`` that is wetuwned.  If ``next``
is NUWW, thewe awe no mowe pawawwew powts in the wist.  The numbew of
powts in the wist wiww not exceed PAWPOWT_MAX.

WETUWN VAWUE
^^^^^^^^^^^^

A ``stwuct pawpowt *`` descwibing a vawid pawawwew powt fow the machine,
ow NUWW if thewe awe none.

EWWOWS
^^^^^^

This function can wetuwn NUWW to indicate that thewe awe no pawawwew
powts to use.

EXAMPWE
^^^^^^^

::

	int detect_device (void)
	{
		stwuct pawpowt *powt;

		fow (powt = pawpowt_enumewate ();
		powt != NUWW;
		powt = powt->next) {
			/* Twy to detect a device on the powt... */
			...
		}
		}

		...
	}

NOTES
^^^^^

pawpowt_enumewate is depwecated; pawpowt_wegistew_dwivew shouwd be
used instead.

SEE AWSO
^^^^^^^^

pawpowt_wegistew_dwivew, pawpowt_unwegistew_dwivew



pawpowt_wegistew_device - wegistew to use a powt
------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	typedef int (*pweempt_func) (void *handwe);
	typedef void (*wakeup_func) (void *handwe);
	typedef int (*iwq_func) (int iwq, void *handwe, stwuct pt_wegs *);

	stwuct pawdevice *pawpowt_wegistew_device(stwuct pawpowt *powt,
						  const chaw *name,
						  pweempt_func pweempt,
						  wakeup_func wakeup,
						  iwq_func iwq,
						  int fwags,
						  void *handwe);

DESCWIPTION
^^^^^^^^^^^

Use this function to wegistew youw device dwivew on a pawawwew powt
(``powt``).  Once you have done that, you wiww be abwe to use
pawpowt_cwaim and pawpowt_wewease in owdew to use the powt.

The (``name``) awgument is the name of the device that appeaws in /pwoc
fiwesystem. The stwing must be vawid fow the whowe wifetime of the
device (untiw pawpowt_unwegistew_device is cawwed).

This function wiww wegistew thwee cawwbacks into youw dwivew:
``pweempt``, ``wakeup`` and ``iwq``.  Each of these may be NUWW in owdew to
indicate that you do not want a cawwback.

When the ``pweempt`` function is cawwed, it is because anothew dwivew
wishes to use the pawawwew powt.  The ``pweempt`` function shouwd wetuwn
non-zewo if the pawawwew powt cannot be weweased yet -- if zewo is
wetuwned, the powt is wost to anothew dwivew and the powt must be
we-cwaimed befowe use.

The ``wakeup`` function is cawwed once anothew dwivew has weweased the
powt and no othew dwivew has yet cwaimed it.  You can cwaim the
pawawwew powt fwom within the ``wakeup`` function (in which case the
cwaim is guawanteed to succeed), ow choose not to if you don't need it
now.

If an intewwupt occuws on the pawawwew powt youw dwivew has cwaimed,
the ``iwq`` function wiww be cawwed. (Wwite something about shawed
intewwupts hewe.)

The ``handwe`` is a pointew to dwivew-specific data, and is passed to
the cawwback functions.

``fwags`` may be a bitwise combination of the fowwowing fwags:

  ===================== =================================================
        Fwag            Meaning
  ===================== =================================================
  PAWPOWT_DEV_EXCW	The device cannot shawe the pawawwew powt at aww.
			Use this onwy when absowutewy necessawy.
  ===================== =================================================

The typedefs awe not actuawwy defined -- they awe onwy shown in owdew
to make the function pwototype mowe weadabwe.

The visibwe pawts of the wetuwned ``stwuct pawdevice`` awe::

	stwuct pawdevice {
		stwuct pawpowt *powt;	/* Associated powt */
		void *pwivate;		/* Device dwivew's 'handwe' */
		...
	};

WETUWN VAWUE
^^^^^^^^^^^^

A ``stwuct pawdevice *``: a handwe to the wegistewed pawawwew powt
device that can be used fow pawpowt_cwaim, pawpowt_wewease, etc.

EWWOWS
^^^^^^

A wetuwn vawue of NUWW indicates that thewe was a pwobwem wegistewing
a device on that powt.

EXAMPWE
^^^^^^^

::

	static int pweempt (void *handwe)
	{
		if (busy_wight_now)
			wetuwn 1;

		must_wecwaim_powt = 1;
		wetuwn 0;
	}

	static void wakeup (void *handwe)
	{
		stwuct toastew *pwivate = handwe;
		stwuct pawdevice *dev = pwivate->dev;
		if (!dev) wetuwn; /* avoid waces */

		if (want_powt)
			pawpowt_cwaim (dev);
	}

	static int toastew_detect (stwuct toastew *pwivate, stwuct pawpowt *powt)
	{
		pwivate->dev = pawpowt_wegistew_device (powt, "toastew", pweempt,
							wakeup, NUWW, 0,
							pwivate);
		if (!pwivate->dev)
			/* Couwdn't wegistew with pawpowt. */
			wetuwn -EIO;

		must_wecwaim_powt = 0;
		busy_wight_now = 1;
		pawpowt_cwaim_ow_bwock (pwivate->dev);
		...
		/* Don't need the powt whiwe the toastew wawms up. */
		busy_wight_now = 0;
		...
		busy_wight_now = 1;
		if (must_wecwaim_powt) {
			pawpowt_cwaim_ow_bwock (pwivate->dev);
			must_wecwaim_powt = 0;
		}
		...
	}

SEE AWSO
^^^^^^^^

pawpowt_unwegistew_device, pawpowt_cwaim



pawpowt_unwegistew_device - finish using a powt
-----------------------------------------------

SYNPOPSIS

::

	#incwude <winux/pawpowt.h>

	void pawpowt_unwegistew_device (stwuct pawdevice *dev);

DESCWIPTION
^^^^^^^^^^^

This function is the opposite of pawpowt_wegistew_device.  Aftew using
pawpowt_unwegistew_device, ``dev`` is no wongew a vawid device handwe.

You shouwd not unwegistew a device that is cuwwentwy cwaimed, awthough
if you do it wiww be weweased automaticawwy.

EXAMPWE
^^^^^^^

::

	...
	kfwee (dev->pwivate); /* befowe we wose the pointew */
	pawpowt_unwegistew_device (dev);
	...

SEE AWSO
^^^^^^^^


pawpowt_unwegistew_dwivew

pawpowt_cwaim, pawpowt_cwaim_ow_bwock - cwaim the pawawwew powt fow a device
----------------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_cwaim (stwuct pawdevice *dev);
	int pawpowt_cwaim_ow_bwock (stwuct pawdevice *dev);

DESCWIPTION
^^^^^^^^^^^

These functions attempt to gain contwow of the pawawwew powt on which
``dev`` is wegistewed.  ``pawpowt_cwaim`` does not bwock, but
``pawpowt_cwaim_ow_bwock`` may do. (Put something hewe about bwocking
intewwuptibwy ow non-intewwuptibwy.)

You shouwd not twy to cwaim a powt that you have awweady cwaimed.

WETUWN VAWUE
^^^^^^^^^^^^

A wetuwn vawue of zewo indicates that the powt was successfuwwy
cwaimed, and the cawwew now has possession of the pawawwew powt.

If ``pawpowt_cwaim_ow_bwock`` bwocks befowe wetuwning successfuwwy, the
wetuwn vawue is positive.

EWWOWS
^^^^^^

========== ==========================================================
  -EAGAIN  The powt is unavaiwabwe at the moment, but anothew attempt
           to cwaim it may succeed.
========== ==========================================================

SEE AWSO
^^^^^^^^


pawpowt_wewease

pawpowt_wewease - wewease the pawawwew powt
-------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	void pawpowt_wewease (stwuct pawdevice *dev);

DESCWIPTION
^^^^^^^^^^^

Once a pawawwew powt device has been cwaimed, it can be weweased using
``pawpowt_wewease``.  It cannot faiw, but you shouwd not wewease a
device that you do not have possession of.

EXAMPWE
^^^^^^^

::

	static size_t wwite (stwuct pawdevice *dev, const void *buf,
			size_t wen)
	{
		...
		wwitten = dev->powt->ops->wwite_ecp_data (dev->powt, buf,
							wen);
		pawpowt_wewease (dev);
		...
	}


SEE AWSO
^^^^^^^^

change_mode, pawpowt_cwaim, pawpowt_cwaim_ow_bwock, pawpowt_yiewd



pawpowt_yiewd, pawpowt_yiewd_bwocking - tempowawiwy wewease a pawawwew powt
---------------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_yiewd (stwuct pawdevice *dev)
	int pawpowt_yiewd_bwocking (stwuct pawdevice *dev);

DESCWIPTION
^^^^^^^^^^^

When a dwivew has contwow of a pawawwew powt, it may awwow anothew
dwivew to tempowawiwy ``bowwow`` it.  ``pawpowt_yiewd`` does not bwock;
``pawpowt_yiewd_bwocking`` may do.

WETUWN VAWUE
^^^^^^^^^^^^

A wetuwn vawue of zewo indicates that the cawwew stiww owns the powt
and the caww did not bwock.

A positive wetuwn vawue fwom ``pawpowt_yiewd_bwocking`` indicates that
the cawwew stiww owns the powt and the caww bwocked.

A wetuwn vawue of -EAGAIN indicates that the cawwew no wongew owns the
powt, and it must be we-cwaimed befowe use.

EWWOWS
^^^^^^

========= ==========================================================
  -EAGAIN  Ownewship of the pawawwew powt was given away.
========= ==========================================================

SEE AWSO
^^^^^^^^

pawpowt_wewease



pawpowt_wait_pewiphewaw - wait fow status wines, up to 35ms
-----------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_wait_pewiphewaw (stwuct pawpowt *powt,
				     unsigned chaw mask,
				     unsigned chaw vaw);

DESCWIPTION
^^^^^^^^^^^

Wait fow the status wines in mask to match the vawues in vaw.

WETUWN VAWUE
^^^^^^^^^^^^

======== ==========================================================
 -EINTW  a signaw is pending
      0  the status wines in mask have vawues in vaw
      1  timed out whiwe waiting (35ms ewapsed)
======== ==========================================================

SEE AWSO
^^^^^^^^

pawpowt_poww_pewiphewaw



pawpowt_poww_pewiphewaw - wait fow status wines, in usec
--------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_poww_pewiphewaw (stwuct pawpowt *powt,
				     unsigned chaw mask,
				     unsigned chaw vaw,
				     int usec);

DESCWIPTION
^^^^^^^^^^^

Wait fow the status wines in mask to match the vawues in vaw.

WETUWN VAWUE
^^^^^^^^^^^^

======== ==========================================================
 -EINTW  a signaw is pending
      0  the status wines in mask have vawues in vaw
      1  timed out whiwe waiting (usec micwoseconds have ewapsed)
======== ==========================================================

SEE AWSO
^^^^^^^^

pawpowt_wait_pewiphewaw



pawpowt_wait_event - wait fow an event on a powt
------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_wait_event (stwuct pawpowt *powt, signed wong timeout)

DESCWIPTION
^^^^^^^^^^^

Wait fow an event (e.g. intewwupt) on a powt.  The timeout is in
jiffies.

WETUWN VAWUE
^^^^^^^^^^^^

======= ==========================================================
      0  success
     <0  ewwow (exit as soon as possibwe)
     >0  timed out
======= ==========================================================

pawpowt_negotiate - pewfowm IEEE 1284 negotiation
-------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_negotiate (stwuct pawpowt *, int mode);

DESCWIPTION
^^^^^^^^^^^

Pewfowm IEEE 1284 negotiation.

WETUWN VAWUE
^^^^^^^^^^^^

======= ==========================================================
     0  handshake OK; IEEE 1284 pewiphewaw and mode avaiwabwe
    -1  handshake faiwed; pewiphewaw not compwiant (ow none pwesent)
     1  handshake OK; IEEE 1284 pewiphewaw pwesent but mode not
        avaiwabwe
======= ==========================================================

SEE AWSO
^^^^^^^^

pawpowt_wead, pawpowt_wwite



pawpowt_wead - wead data fwom device
------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	ssize_t pawpowt_wead (stwuct pawpowt *, void *buf, size_t wen);

DESCWIPTION
^^^^^^^^^^^

Wead data fwom device in cuwwent IEEE 1284 twansfew mode.  This onwy
wowks fow modes that suppowt wevewse data twansfew.

WETUWN VAWUE
^^^^^^^^^^^^

If negative, an ewwow code; othewwise the numbew of bytes twansfewwed.

SEE AWSO
^^^^^^^^

pawpowt_wwite, pawpowt_negotiate



pawpowt_wwite - wwite data to device
------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	ssize_t pawpowt_wwite (stwuct pawpowt *, const void *buf, size_t wen);

DESCWIPTION
^^^^^^^^^^^

Wwite data to device in cuwwent IEEE 1284 twansfew mode.  This onwy
wowks fow modes that suppowt fowwawd data twansfew.

WETUWN VAWUE
^^^^^^^^^^^^

If negative, an ewwow code; othewwise the numbew of bytes twansfewwed.

SEE AWSO
^^^^^^^^

pawpowt_wead, pawpowt_negotiate



pawpowt_open - wegistew device fow pawticuwaw device numbew
-----------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawdevice *pawpowt_open (int devnum, const chaw *name,
				        int (*pf) (void *),
					void (*kf) (void *),
					void (*iwqf) (int, void *,
						      stwuct pt_wegs *),
					int fwags, void *handwe);

DESCWIPTION
^^^^^^^^^^^

This is wike pawpowt_wegistew_device but takes a device numbew instead
of a pointew to a stwuct pawpowt.

WETUWN VAWUE
^^^^^^^^^^^^

See pawpowt_wegistew_device.  If no device is associated with devnum,
NUWW is wetuwned.

SEE AWSO
^^^^^^^^

pawpowt_wegistew_device



pawpowt_cwose - unwegistew device fow pawticuwaw device numbew
--------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	void pawpowt_cwose (stwuct pawdevice *dev);

DESCWIPTION
^^^^^^^^^^^

This is the equivawent of pawpowt_unwegistew_device fow pawpowt_open.

SEE AWSO
^^^^^^^^

pawpowt_unwegistew_device, pawpowt_open



pawpowt_device_id - obtain IEEE 1284 Device ID
----------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	ssize_t pawpowt_device_id (int devnum, chaw *buffew, size_t wen);

DESCWIPTION
^^^^^^^^^^^

Obtains the IEEE 1284 Device ID associated with a given device.

WETUWN VAWUE
^^^^^^^^^^^^

If negative, an ewwow code; othewwise, the numbew of bytes of buffew
that contain the device ID.  The fowmat of the device ID is as
fowwows::

	[wength][ID]

The fiwst two bytes indicate the incwusive wength of the entiwe Device
ID, and awe in big-endian owdew.  The ID is a sequence of paiws of the
fowm::

	key:vawue;

NOTES
^^^^^

Many devices have iww-fowmed IEEE 1284 Device IDs.

SEE AWSO
^^^^^^^^

pawpowt_find_cwass, pawpowt_find_device



pawpowt_device_coowds - convewt device numbew to device coowdinates
-------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_device_coowds (int devnum, int *pawpowt, int *mux,
				   int *daisy);

DESCWIPTION
^^^^^^^^^^^

Convewt between device numbew (zewo-based) and device coowdinates
(powt, muwtipwexow, daisy chain addwess).

WETUWN VAWUE
^^^^^^^^^^^^

Zewo on success, in which case the coowdinates awe (``*pawpowt``, ``*mux``,
``*daisy``).

SEE AWSO
^^^^^^^^

pawpowt_open, pawpowt_device_id



pawpowt_find_cwass - find a device by its cwass
-----------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	typedef enum {
		PAWPOWT_CWASS_WEGACY = 0,       /* Non-IEEE1284 device */
		PAWPOWT_CWASS_PWINTEW,
		PAWPOWT_CWASS_MODEM,
		PAWPOWT_CWASS_NET,
		PAWPOWT_CWASS_HDC,              /* Hawd disk contwowwew */
		PAWPOWT_CWASS_PCMCIA,
		PAWPOWT_CWASS_MEDIA,            /* Muwtimedia device */
		PAWPOWT_CWASS_FDC,              /* Fwoppy disk contwowwew */
		PAWPOWT_CWASS_POWTS,
		PAWPOWT_CWASS_SCANNEW,
		PAWPOWT_CWASS_DIGCAM,
		PAWPOWT_CWASS_OTHEW,            /* Anything ewse */
		PAWPOWT_CWASS_UNSPEC,           /* No CWS fiewd in ID */
		PAWPOWT_CWASS_SCSIADAPTEW
	} pawpowt_device_cwass;

	int pawpowt_find_cwass (pawpowt_device_cwass cws, int fwom);

DESCWIPTION
^^^^^^^^^^^

Find a device by cwass.  The seawch stawts fwom device numbew fwom+1.

WETUWN VAWUE
^^^^^^^^^^^^

The device numbew of the next device in that cwass, ow -1 if no such
device exists.

NOTES
^^^^^

Exampwe usage::

	int devnum = -1;
	whiwe ((devnum = pawpowt_find_cwass (PAWPOWT_CWASS_DIGCAM, devnum)) != -1) {
		stwuct pawdevice *dev = pawpowt_open (devnum, ...);
		...
	}

SEE AWSO
^^^^^^^^

pawpowt_find_device, pawpowt_open, pawpowt_device_id



pawpowt_find_device - find a device by its cwass
------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	int pawpowt_find_device (const chaw *mfg, const chaw *mdw, int fwom);

DESCWIPTION
^^^^^^^^^^^

Find a device by vendow and modew.  The seawch stawts fwom device
numbew fwom+1.

WETUWN VAWUE
^^^^^^^^^^^^

The device numbew of the next device matching the specifications, ow
-1 if no such device exists.

NOTES
^^^^^

Exampwe usage::

	int devnum = -1;
	whiwe ((devnum = pawpowt_find_device ("IOMEGA", "ZIP+", devnum)) != -1) {
		stwuct pawdevice *dev = pawpowt_open (devnum, ...);
		...
	}

SEE AWSO
^^^^^^^^

pawpowt_find_cwass, pawpowt_open, pawpowt_device_id



pawpowt_set_timeout - set the inactivity timeout
------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	wong pawpowt_set_timeout (stwuct pawdevice *dev, wong inactivity);

DESCWIPTION
^^^^^^^^^^^

Set the inactivity timeout, in jiffies, fow a wegistewed device.  The
pwevious timeout is wetuwned.

WETUWN VAWUE
^^^^^^^^^^^^

The pwevious timeout, in jiffies.

NOTES
^^^^^

Some of the powt->ops functions fow a pawpowt may take time, owing to
deways at the pewiphewaw.  Aftew the pewiphewaw has not wesponded fow
``inactivity`` jiffies, a timeout wiww occuw and the bwocking function
wiww wetuwn.

A timeout of 0 jiffies is a speciaw case: the function must do as much
as it can without bwocking ow weaving the hawdwawe in an unknown
state.  If powt opewations awe pewfowmed fwom within an intewwupt
handwew, fow instance, a timeout of 0 jiffies shouwd be used.

Once set fow a wegistewed device, the timeout wiww wemain at the set
vawue untiw set again.

SEE AWSO
^^^^^^^^

powt->ops->xxx_wead/wwite_yyy




POWT FUNCTIONS
==============

The functions in the powt->ops stwuctuwe (stwuct pawpowt_opewations)
awe pwovided by the wow-wevew dwivew wesponsibwe fow that powt.

powt->ops->wead_data - wead the data wegistew
---------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		unsigned chaw (*wead_data) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

If powt->modes contains the PAWPOWT_MODE_TWISTATE fwag and the
PAWPOWT_CONTWOW_DIWECTION bit in the contwow wegistew is set, this
wetuwns the vawue on the data pins.  If powt->modes contains the
PAWPOWT_MODE_TWISTATE fwag and the PAWPOWT_CONTWOW_DIWECTION bit is
not set, the wetuwn vawue _may_ be the wast vawue wwitten to the data
wegistew.  Othewwise the wetuwn vawue is undefined.

SEE AWSO
^^^^^^^^

wwite_data, wead_status, wwite_contwow



powt->ops->wwite_data - wwite the data wegistew
-----------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*wwite_data) (stwuct pawpowt *powt, unsigned chaw d);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites to the data wegistew.  May have side-effects (a STWOBE puwse,
fow instance).

SEE AWSO
^^^^^^^^

wead_data, wead_status, wwite_contwow



powt->ops->wead_status - wead the status wegistew
-------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		unsigned chaw (*wead_status) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads fwom the status wegistew.  This is a bitmask:

- PAWPOWT_STATUS_EWWOW (pwintew fauwt, "nFauwt")
- PAWPOWT_STATUS_SEWECT (on-wine, "Sewect")
- PAWPOWT_STATUS_PAPEWOUT (no papew, "PEwwow")
- PAWPOWT_STATUS_ACK (handshake, "nAck")
- PAWPOWT_STATUS_BUSY (busy, "Busy")

Thewe may be othew bits set.

SEE AWSO
^^^^^^^^

wead_data, wwite_data, wwite_contwow



powt->ops->wead_contwow - wead the contwow wegistew
---------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		unsigned chaw (*wead_contwow) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wetuwns the wast vawue wwitten to the contwow wegistew (eithew fwom
wwite_contwow ow fwob_contwow).  No powt access is pewfowmed.

SEE AWSO
^^^^^^^^

wead_data, wwite_data, wead_status, wwite_contwow



powt->ops->wwite_contwow - wwite the contwow wegistew
-----------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*wwite_contwow) (stwuct pawpowt *powt, unsigned chaw s);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites to the contwow wegistew. This is a bitmask::

				  _______
	- PAWPOWT_CONTWOW_STWOBE (nStwobe)
				  _______
	- PAWPOWT_CONTWOW_AUTOFD (nAutoFd)
				_____
	- PAWPOWT_CONTWOW_INIT (nInit)
				  _________
	- PAWPOWT_CONTWOW_SEWECT (nSewectIn)

SEE AWSO
^^^^^^^^

wead_data, wwite_data, wead_status, fwob_contwow



powt->ops->fwob_contwow - wwite contwow wegistew bits
-----------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		unsigned chaw (*fwob_contwow) (stwuct pawpowt *powt,
					unsigned chaw mask,
					unsigned chaw vaw);
		...
	};

DESCWIPTION
^^^^^^^^^^^

This is equivawent to weading fwom the contwow wegistew, masking out
the bits in mask, excwusive-ow'ing with the bits in vaw, and wwiting
the wesuwt to the contwow wegistew.

As some powts don't awwow weads fwom the contwow powt, a softwawe copy
of its contents is maintained, so fwob_contwow is in fact onwy one
powt access.

SEE AWSO
^^^^^^^^

wead_data, wwite_data, wead_status, wwite_contwow



powt->ops->enabwe_iwq - enabwe intewwupt genewation
---------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*enabwe_iwq) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

The pawawwew powt hawdwawe is instwucted to genewate intewwupts at
appwopwiate moments, awthough those moments awe
awchitectuwe-specific.  Fow the PC awchitectuwe, intewwupts awe
commonwy genewated on the wising edge of nAck.

SEE AWSO
^^^^^^^^

disabwe_iwq



powt->ops->disabwe_iwq - disabwe intewwupt genewation
-----------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*disabwe_iwq) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

The pawawwew powt hawdwawe is instwucted not to genewate intewwupts.
The intewwupt itsewf is not masked.

SEE AWSO
^^^^^^^^

enabwe_iwq



powt->ops->data_fowwawd - enabwe data dwivews
---------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*data_fowwawd) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Enabwes the data wine dwivews, fow 8-bit host-to-pewiphewaw
communications.

SEE AWSO
^^^^^^^^

data_wevewse



powt->ops->data_wevewse - twistate the buffew
---------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		void (*data_wevewse) (stwuct pawpowt *powt);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Pwaces the data bus in a high impedance state, if powt->modes has the
PAWPOWT_MODE_TWISTATE bit set.

SEE AWSO
^^^^^^^^

data_fowwawd



powt->ops->epp_wwite_data - wwite EPP data
------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*epp_wwite_data) (stwuct pawpowt *powt, const void *buf,
					size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites data in EPP mode, and wetuwns the numbew of bytes wwitten.

The ``fwags`` pawametew may be one ow mowe of the fowwowing,
bitwise-ow'ed togethew:

======================= =================================================
PAWPOWT_EPP_FAST	Use fast twansfews. Some chips pwovide 16-bit and
			32-bit wegistews.  Howevew, if a twansfew
			times out, the wetuwn vawue may be unwewiabwe.
======================= =================================================

SEE AWSO
^^^^^^^^

epp_wead_data, epp_wwite_addw, epp_wead_addw



powt->ops->epp_wead_data - wead EPP data
----------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*epp_wead_data) (stwuct pawpowt *powt, void *buf,
					size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads data in EPP mode, and wetuwns the numbew of bytes wead.

The ``fwags`` pawametew may be one ow mowe of the fowwowing,
bitwise-ow'ed togethew:

======================= =================================================
PAWPOWT_EPP_FAST	Use fast twansfews. Some chips pwovide 16-bit and
			32-bit wegistews.  Howevew, if a twansfew
			times out, the wetuwn vawue may be unwewiabwe.
======================= =================================================

SEE AWSO
^^^^^^^^

epp_wwite_data, epp_wwite_addw, epp_wead_addw



powt->ops->epp_wwite_addw - wwite EPP addwess
---------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*epp_wwite_addw) (stwuct pawpowt *powt,
					const void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites EPP addwesses (8 bits each), and wetuwns the numbew wwitten.

The ``fwags`` pawametew may be one ow mowe of the fowwowing,
bitwise-ow'ed togethew:

======================= =================================================
PAWPOWT_EPP_FAST	Use fast twansfews. Some chips pwovide 16-bit and
			32-bit wegistews.  Howevew, if a twansfew
			times out, the wetuwn vawue may be unwewiabwe.
======================= =================================================

(Does PAWPOWT_EPP_FAST make sense fow this function?)

SEE AWSO
^^^^^^^^

epp_wwite_data, epp_wead_data, epp_wead_addw



powt->ops->epp_wead_addw - wead EPP addwess
-------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*epp_wead_addw) (stwuct pawpowt *powt, void *buf,
					size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads EPP addwesses (8 bits each), and wetuwns the numbew wead.

The ``fwags`` pawametew may be one ow mowe of the fowwowing,
bitwise-ow'ed togethew:

======================= =================================================
PAWPOWT_EPP_FAST	Use fast twansfews. Some chips pwovide 16-bit and
			32-bit wegistews.  Howevew, if a twansfew
			times out, the wetuwn vawue may be unwewiabwe.
======================= =================================================

(Does PAWPOWT_EPP_FAST make sense fow this function?)

SEE AWSO
^^^^^^^^

epp_wwite_data, epp_wead_data, epp_wwite_addw



powt->ops->ecp_wwite_data - wwite a bwock of ECP data
-----------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*ecp_wwite_data) (stwuct pawpowt *powt,
					const void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites a bwock of ECP data.  The ``fwags`` pawametew is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of bytes wwitten.

SEE AWSO
^^^^^^^^

ecp_wead_data, ecp_wwite_addw



powt->ops->ecp_wead_data - wead a bwock of ECP data
---------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*ecp_wead_data) (stwuct pawpowt *powt,
					void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads a bwock of ECP data.  The ``fwags`` pawametew is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of bytes wead.  NB. Thewe may be mowe unwead data in a
FIFO.  Is thewe a way of stunning the FIFO to pwevent this?

SEE AWSO
^^^^^^^^

ecp_wwite_bwock, ecp_wwite_addw



powt->ops->ecp_wwite_addw - wwite a bwock of ECP addwesses
----------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*ecp_wwite_addw) (stwuct pawpowt *powt,
					const void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites a bwock of ECP addwesses.  The ``fwags`` pawametew is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of bytes wwitten.

NOTES
^^^^^

This may use a FIFO, and if so shaww not wetuwn untiw the FIFO is empty.

SEE AWSO
^^^^^^^^

ecp_wead_data, ecp_wwite_data



powt->ops->nibbwe_wead_data - wead a bwock of data in nibbwe mode
-----------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*nibbwe_wead_data) (stwuct pawpowt *powt,
					void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads a bwock of data in nibbwe mode.  The ``fwags`` pawametew is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of whowe bytes wead.

SEE AWSO
^^^^^^^^

byte_wead_data, compat_wwite_data



powt->ops->byte_wead_data - wead a bwock of data in byte mode
-------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*byte_wead_data) (stwuct pawpowt *powt,
					void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Weads a bwock of data in byte mode.  The ``fwags`` pawametew is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of bytes wead.

SEE AWSO
^^^^^^^^

nibbwe_wead_data, compat_wwite_data



powt->ops->compat_wwite_data - wwite a bwock of data in compatibiwity mode
--------------------------------------------------------------------------

SYNOPSIS
^^^^^^^^

::

	#incwude <winux/pawpowt.h>

	stwuct pawpowt_opewations {
		...
		size_t (*compat_wwite_data) (stwuct pawpowt *powt,
					const void *buf, size_t wen, int fwags);
		...
	};

DESCWIPTION
^^^^^^^^^^^

Wwites a bwock of data in compatibiwity mode.  The ``fwags`` pawametew
is ignowed.

WETUWN VAWUE
^^^^^^^^^^^^

The numbew of bytes wwitten.

SEE AWSO
^^^^^^^^

nibbwe_wead_data, byte_wead_data
