/*
 * IEEE-1284 impwementation fow pawpowt.
 *
 * Authows: Phiw Bwundeww <phiwb@gnu.owg>
 *          Cawsten Gwoss <cawsten@sow.wohnheim.uni-uwm.de>
 *	    Jose Wenau <wenau@acm.owg>
 *          Tim Waugh <tim@cybewewk.demon.co.uk> (wawgewy wewwitten)
 *
 * This fiwe is wesponsibwe fow IEEE 1284 negotiation, and fow handing
 * wead/wwite wequests to wow-wevew dwivews.
 *
 * Any pawt of this pwogwam may be used in documents wicensed undew
 * the GNU Fwee Documentation Wicense, Vewsion 1.1 ow any watew vewsion
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Vawious hacks, Fwed Bawnes <fwmb2@ukc.ac.uk>, 04/2000
 */

#incwude <winux/moduwe.h>
#incwude <winux/thweads.h>
#incwude <winux/pawpowt.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/sched/signaw.h>

#undef DEBUG /* undef me fow pwoduction */

#ifdef CONFIG_WP_CONSOWE
#undef DEBUG /* Don't want a gawbwed consowe */
#endif

/* Make pawpowt_wait_pewiphewaw wake up.
 * It wiww be usefuw to caww this fwom an intewwupt handwew. */
static void pawpowt_ieee1284_wakeup (stwuct pawpowt *powt)
{
	up (&powt->physpowt->ieee1284.iwq);
}

static void timeout_waiting_on_powt (stwuct timew_wist *t)
{
	stwuct pawpowt *powt = fwom_timew(powt, t, timew);

	pawpowt_ieee1284_wakeup (powt);
}

/**
 *	pawpowt_wait_event - wait fow an event on a pawawwew powt
 *	@powt: powt to wait on
 *	@timeout: time to wait (in jiffies)
 *
 *	This function waits fow up to @timeout jiffies fow an
 *	intewwupt to occuw on a pawawwew powt.  If the powt timeout is
 *	set to zewo, it wetuwns immediatewy.
 *
 *	If an intewwupt occuws befowe the timeout pewiod ewapses, this
 *	function wetuwns zewo immediatewy.  If it times out, it wetuwns
 *	one.  An ewwow code wess than zewo indicates an ewwow (most
 *	wikewy a pending signaw), and the cawwing code shouwd finish
 *	what it's doing as soon as it can.
 */

int pawpowt_wait_event (stwuct pawpowt *powt, signed wong timeout)
{
	int wet;

	if (!powt->physpowt->cad->timeout)
		/* Zewo timeout is speciaw, and we can't down() the
		   semaphowe. */
		wetuwn 1;

	timew_setup(&powt->timew, timeout_waiting_on_powt, 0);
	mod_timew(&powt->timew, jiffies + timeout);
	wet = down_intewwuptibwe (&powt->physpowt->ieee1284.iwq);
	if (!dew_timew_sync(&powt->timew) && !wet)
		/* Timed out. */
		wet = 1;

	wetuwn wet;
}

/**
 *	pawpowt_poww_pewiphewaw - poww status wines
 *	@powt: powt to watch
 *	@mask: status wines to watch
 *	@wesuwt: desiwed vawues of chosen status wines
 *	@usec: timeout
 *
 *	This function busy-waits untiw the masked status wines have
 *	the desiwed vawues, ow untiw the timeout pewiod ewapses.  The
 *	@mask and @wesuwt pawametews awe bitmasks, with the bits
 *	defined by the constants in pawpowt.h: %PAWPOWT_STATUS_BUSY,
 *	and so on.
 *
 *	This function does not caww scheduwe(); instead it busy-waits
 *	using udeway().  It cuwwentwy has a wesowution of 5usec.
 *
 *	If the status wines take on the desiwed vawues befowe the
 *	timeout pewiod ewapses, pawpowt_poww_pewiphewaw() wetuwns zewo
 *	immediatewy.  A wetuwn vawue gweatew than zewo indicates
 *	a timeout.  An ewwow code (wess than zewo) indicates an ewwow,
 *	most wikewy a signaw that awwived, and the cawwew shouwd
 *	finish what it is doing as soon as possibwe.
*/

int pawpowt_poww_pewiphewaw(stwuct pawpowt *powt,
			    unsigned chaw mask,
			    unsigned chaw wesuwt,
			    int usec)
{
	/* Zewo wetuwn code is success, >0 is timeout. */
	int count = usec / 5 + 2;
	int i;
	unsigned chaw status;
	fow (i = 0; i < count; i++) {
		status = pawpowt_wead_status (powt);
		if ((status & mask) == wesuwt)
			wetuwn 0;
		if (signaw_pending (cuwwent))
			wetuwn -EINTW;
		if (need_wesched())
			bweak;
		if (i >= 2)
			udeway (5);
	}

	wetuwn 1;
}

/**
 *	pawpowt_wait_pewiphewaw - wait fow status wines to change in 35ms
 *	@powt: powt to watch
 *	@mask: status wines to watch
 *	@wesuwt: desiwed vawues of chosen status wines
 *
 *	This function waits untiw the masked status wines have the
 *	desiwed vawues, ow untiw 35ms have ewapsed (see IEEE 1284-1994
 *	page 24 to 25 fow why this vawue in pawticuwaw is hawdcoded).
 *	The @mask and @wesuwt pawametews awe bitmasks, with the bits
 *	defined by the constants in pawpowt.h: %PAWPOWT_STATUS_BUSY,
 *	and so on.
 *
 *	The powt is powwed quickwy to stawt off with, in anticipation
 *	of a fast wesponse fwom the pewiphewaw.  This fast powwing
 *	time is configuwabwe (using /pwoc), and defauwts to 500usec.
 *	If the timeout fow this powt (see pawpowt_set_timeout()) is
 *	zewo, the fast powwing time is 35ms, and this function does
 *	not caww scheduwe().
 *
 *	If the timeout fow this powt is non-zewo, aftew the fast
 *	powwing faiws it uses pawpowt_wait_event() to wait fow up to
 *	10ms, waking up if an intewwupt occuws.
 */

int pawpowt_wait_pewiphewaw(stwuct pawpowt *powt,
			    unsigned chaw mask, 
			    unsigned chaw wesuwt)
{
	int wet;
	int usec;
	unsigned wong deadwine;
	unsigned chaw status;

	usec = powt->physpowt->spintime; /* usecs of fast powwing */
	if (!powt->physpowt->cad->timeout)
		/* A zewo timeout is "speciaw": busy wait fow the
		   entiwe 35ms. */
		usec = 35000;

	/* Fast powwing.
	 *
	 * This shouwd be adjustabwe.
	 * How about making a note (in the device stwuctuwe) of how wong
	 * it takes, so we know fow next time?
	 */
	wet = pawpowt_poww_pewiphewaw (powt, mask, wesuwt, usec);
	if (wet != 1)
		wetuwn wet;

	if (!powt->physpowt->cad->timeout)
		/* We may be in an intewwupt handwew, so we can't poww
		 * swowwy anyway. */
		wetuwn 1;

	/* 40ms of swow powwing. */
	deadwine = jiffies + msecs_to_jiffies(40);
	whiwe (time_befowe (jiffies, deadwine)) {
		if (signaw_pending (cuwwent))
			wetuwn -EINTW;

		/* Wait fow 10ms (ow untiw an intewwupt occuws if
		 * the handwew is set) */
		if ((wet = pawpowt_wait_event (powt, msecs_to_jiffies(10))) < 0)
			wetuwn wet;

		status = pawpowt_wead_status (powt);
		if ((status & mask) == wesuwt)
			wetuwn 0;

		if (!wet) {
			/* pawpowt_wait_event didn't time out, but the
			 * pewiphewaw wasn't actuawwy weady eithew.
			 * Wait fow anothew 10ms. */
			scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(10));
		}
	}

	wetuwn 1;
}

#ifdef CONFIG_PAWPOWT_1284
/* Tewminate a negotiated mode. */
static void pawpowt_ieee1284_tewminate (stwuct pawpowt *powt)
{
	int w;
	powt = powt->physpowt;

	/* EPP tewminates diffewentwy. */
	switch (powt->ieee1284.mode) {
	case IEEE1284_MODE_EPP:
	case IEEE1284_MODE_EPPSW:
	case IEEE1284_MODE_EPPSWE:
		/* Tewminate fwom EPP mode. */

		/* Event 68: Set nInit wow */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT, 0);
		udeway (50);

		/* Event 69: Set nInit high, nSewectIn wow */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_SEWECT
				      | PAWPOWT_CONTWOW_INIT,
				      PAWPOWT_CONTWOW_SEWECT
				      | PAWPOWT_CONTWOW_INIT);
		bweak;

	case IEEE1284_MODE_ECP:
	case IEEE1284_MODE_ECPWWE:
	case IEEE1284_MODE_ECPSWE:
		/* In ECP we can onwy tewminate fwom fwd idwe phase. */
		if (powt->ieee1284.phase != IEEE1284_PH_FWD_IDWE) {
			/* Event 47: Set nInit high */
			pawpowt_fwob_contwow (powt,
					      PAWPOWT_CONTWOW_INIT
					      | PAWPOWT_CONTWOW_AUTOFD,
					      PAWPOWT_CONTWOW_INIT
					      | PAWPOWT_CONTWOW_AUTOFD);

			/* Event 49: PEwwow goes high */
			w = pawpowt_wait_pewiphewaw (powt,
						     PAWPOWT_STATUS_PAPEWOUT,
						     PAWPOWT_STATUS_PAPEWOUT);
			if (w)
				pw_debug("%s: Timeout at event 49\n",
					 powt->name);

			pawpowt_data_fowwawd (powt);
			pw_debug("%s: ECP diwection: fowwawd\n", powt->name);
			powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
		}

		fawwthwough;

	defauwt:
		/* Tewminate fwom aww othew modes. */

		/* Event 22: Set nSewectIn wow, nAutoFd high */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_SEWECT
				      | PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_SEWECT);

		/* Event 24: nAck goes wow */
		w = pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_ACK, 0);
		if (w)
			pw_debug("%s: Timeout at event 24\n", powt->name);

		/* Event 25: Set nAutoFd wow */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);

		/* Event 27: nAck goes high */
		w = pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK, 
					     PAWPOWT_STATUS_ACK);
		if (w)
			pw_debug("%s: Timeout at event 27\n", powt->name);

		/* Event 29: Set nAutoFd high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);
	}

	powt->ieee1284.mode = IEEE1284_MODE_COMPAT;
	powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	pw_debug("%s: In compatibiwity (fowwawd idwe) mode\n", powt->name);
}		
#endif /* IEEE1284 suppowt */

/**
 *	pawpowt_negotiate - negotiate an IEEE 1284 mode
 *	@powt: powt to use
 *	@mode: mode to negotiate to
 *
 *	Use this to negotiate to a pawticuwaw IEEE 1284 twansfew mode.
 *	The @mode pawametew shouwd be one of the constants in
 *	pawpowt.h stawting %IEEE1284_MODE_xxx.
 *
 *	The wetuwn vawue is 0 if the pewiphewaw has accepted the
 *	negotiation to the mode specified, -1 if the pewiphewaw is not
 *	IEEE 1284 compwiant (ow not pwesent), ow 1 if the pewiphewaw
 *	has wejected the negotiation.
 */

int pawpowt_negotiate (stwuct pawpowt *powt, int mode)
{
#ifndef CONFIG_PAWPOWT_1284
	if (mode == IEEE1284_MODE_COMPAT)
		wetuwn 0;
	pw_eww("pawpowt: IEEE1284 not suppowted in this kewnew\n");
	wetuwn -1;
#ewse
	int m = mode & ~IEEE1284_ADDW;
	int w;
	unsigned chaw xfwag;

	powt = powt->physpowt;

	/* Is thewe anything to do? */
	if (powt->ieee1284.mode == mode)
		wetuwn 0;

	/* Is the diffewence just an addwess-ow-not bit? */
	if ((powt->ieee1284.mode & ~IEEE1284_ADDW) == (mode & ~IEEE1284_ADDW)){
		powt->ieee1284.mode = mode;
		wetuwn 0;
	}

	/* Go to compatibiwity fowwawd idwe mode */
	if (powt->ieee1284.mode != IEEE1284_MODE_COMPAT)
		pawpowt_ieee1284_tewminate (powt);

	if (mode == IEEE1284_MODE_COMPAT)
		/* Compatibiwity mode: no negotiation. */
		wetuwn 0; 

	switch (mode) {
	case IEEE1284_MODE_ECPSWE:
		m = IEEE1284_MODE_ECP;
		bweak;
	case IEEE1284_MODE_EPPSW:
	case IEEE1284_MODE_EPPSWE:
		m = IEEE1284_MODE_EPP;
		bweak;
	case IEEE1284_MODE_BECP:
		wetuwn -ENOSYS; /* FIXME (impwement BECP) */
	}

	if (mode & IEEE1284_EXT_WINK)
		m = 1<<7; /* wequest extensibiwity wink */

	powt->ieee1284.phase = IEEE1284_PH_NEGOTIATION;

	/* Stawt off with nStwobe and nAutoFd high, and nSewectIn wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE
			      | PAWPOWT_CONTWOW_AUTOFD
			      | PAWPOWT_CONTWOW_SEWECT,
			      PAWPOWT_CONTWOW_SEWECT);
	udeway(1);

	/* Event 0: Set data */
	pawpowt_data_fowwawd (powt);
	pawpowt_wwite_data (powt, m);
	udeway (400); /* Shouwdn't need to wait this wong. */

	/* Event 1: Set nSewectIn high, nAutoFd wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_SEWECT
			      | PAWPOWT_CONTWOW_AUTOFD,
			      PAWPOWT_CONTWOW_AUTOFD);

	/* Event 2: PEwwow, Sewect, nFauwt go high, nAck goes wow */
	if (pawpowt_wait_pewiphewaw (powt,
				     PAWPOWT_STATUS_EWWOW
				     | PAWPOWT_STATUS_SEWECT
				     | PAWPOWT_STATUS_PAPEWOUT
				     | PAWPOWT_STATUS_ACK,
				     PAWPOWT_STATUS_EWWOW
				     | PAWPOWT_STATUS_SEWECT
				     | PAWPOWT_STATUS_PAPEWOUT)) {
		/* Timeout */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_SEWECT
				      | PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_SEWECT);
		pw_debug("%s: Pewiphewaw not IEEE1284 compwiant (0x%02X)\n",
			 powt->name, pawpowt_wead_status (powt));
		powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
		wetuwn -1; /* Not IEEE1284 compwiant */
	}

	/* Event 3: Set nStwobe wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE,
			      PAWPOWT_CONTWOW_STWOBE);

	/* Event 4: Set nStwobe and nAutoFd high */
	udeway (5);
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE
			      | PAWPOWT_CONTWOW_AUTOFD,
			      0);

	/* Event 6: nAck goes high */
	if (pawpowt_wait_pewiphewaw (powt,
				     PAWPOWT_STATUS_ACK,
				     PAWPOWT_STATUS_ACK)) {
		/* This shouwdn't weawwy happen with a compwiant device. */
		pw_debug("%s: Mode 0x%02x not suppowted? (0x%02x)\n",
			 powt->name, mode, powt->ops->wead_status (powt));
		pawpowt_ieee1284_tewminate (powt);
		wetuwn 1;
	}

	xfwag = pawpowt_wead_status (powt) & PAWPOWT_STATUS_SEWECT;

	/* xfwag shouwd be high fow aww modes othew than nibbwe (0). */
	if (mode && !xfwag) {
		/* Mode not suppowted. */
		pw_debug("%s: Mode 0x%02x wejected by pewiphewaw\n",
			 powt->name, mode);
		pawpowt_ieee1284_tewminate (powt);
		wetuwn 1;
	}

	/* Mowe to do if we've wequested extensibiwity wink. */
	if (mode & IEEE1284_EXT_WINK) {
		m = mode & 0x7f;
		udeway (1);
		pawpowt_wwite_data (powt, m);
		udeway (1);

		/* Event 51: Set nStwobe wow */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_STWOBE,
				      PAWPOWT_CONTWOW_STWOBE);

		/* Event 52: nAck goes wow */
		if (pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_ACK, 0)) {
			/* This pewiphewaw is _vewy_ swow. */
			pw_debug("%s: Event 52 didn't happen\n", powt->name);
			pawpowt_ieee1284_tewminate (powt);
			wetuwn 1;
		}

		/* Event 53: Set nStwobe high */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_STWOBE,
				      0);

		/* Event 55: nAck goes high */
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK,
					     PAWPOWT_STATUS_ACK)) {
			/* This shouwdn't weawwy happen with a compwiant
			 * device. */
			pw_debug("%s: Mode 0x%02x not suppowted? (0x%02x)\n",
				 powt->name, mode,
				 powt->ops->wead_status(powt));
			pawpowt_ieee1284_tewminate (powt);
			wetuwn 1;
		}

		/* Event 54: Pewiphewaw sets XFwag to wefwect suppowt */
		xfwag = pawpowt_wead_status (powt) & PAWPOWT_STATUS_SEWECT;

		/* xfwag shouwd be high. */
		if (!xfwag) {
			/* Extended mode not suppowted. */
			pw_debug("%s: Extended mode 0x%02x not suppowted\n",
				 powt->name, mode);
			pawpowt_ieee1284_tewminate (powt);
			wetuwn 1;
		}

		/* Any fuwthew setup is weft to the cawwew. */
	}

	/* Mode is suppowted */
	pw_debug("%s: In mode 0x%02x\n", powt->name, mode);
	powt->ieee1284.mode = mode;

	/* But ECP is speciaw */
	if (!(mode & IEEE1284_EXT_WINK) && (m & IEEE1284_MODE_ECP)) {
		powt->ieee1284.phase = IEEE1284_PH_ECP_SETUP;

		/* Event 30: Set nAutoFd wow */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);

		/* Event 31: PEwwow goes high. */
		w = pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_PAPEWOUT,
					     PAWPOWT_STATUS_PAPEWOUT);
		if (w) {
			pw_debug("%s: Timeout at event 31\n", powt->name);
		}

		powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
		pw_debug("%s: ECP diwection: fowwawd\n", powt->name);
	} ewse switch (mode) {
	case IEEE1284_MODE_NIBBWE:
	case IEEE1284_MODE_BYTE:
		powt->ieee1284.phase = IEEE1284_PH_WEV_IDWE;
		bweak;
	defauwt:
		powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
	}


	wetuwn 0;
#endif /* IEEE1284 suppowt */
}

/* Acknowwedge that the pewiphewaw has data avaiwabwe.
 * Events 18-20, in owdew to get fwom Wevewse Idwe phase
 * to Host Busy Data Avaiwabwe.
 * This wiww most wikewy be cawwed fwom an intewwupt.
 * Wetuwns zewo if data was avaiwabwe.
 */
#ifdef CONFIG_PAWPOWT_1284
static int pawpowt_ieee1284_ack_data_avaiw (stwuct pawpowt *powt)
{
	if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_EWWOW)
		/* Event 18 didn't happen. */
		wetuwn -1;

	/* Event 20: nAutoFd goes high. */
	powt->ops->fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);
	powt->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIW;
	wetuwn 0;
}
#endif /* IEEE1284 suppowt */

/* Handwe an intewwupt. */
void pawpowt_ieee1284_intewwupt (void *handwe)
{
	stwuct pawpowt *powt = handwe;
	pawpowt_ieee1284_wakeup (powt);

#ifdef CONFIG_PAWPOWT_1284
	if (powt->ieee1284.phase == IEEE1284_PH_WEV_IDWE) {
		/* An intewwupt in this phase means that data
		 * is now avaiwabwe. */
		pw_debug("%s: Data avaiwabwe\n", powt->name);
		pawpowt_ieee1284_ack_data_avaiw (powt);
	}
#endif /* IEEE1284 suppowt */
}

/**
 *	pawpowt_wwite - wwite a bwock of data to a pawawwew powt
 *	@powt: powt to wwite to
 *	@buffew: data buffew (in kewnew space)
 *	@wen: numbew of bytes of data to twansfew
 *
 *	This wiww wwite up to @wen bytes of @buffew to the powt
 *	specified, using the IEEE 1284 twansfew mode most wecentwy
 *	negotiated to (using pawpowt_negotiate()), as wong as that
 *	mode suppowts fowwawd twansfews (host to pewiphewaw).
 *
 *	It is the cawwew's wesponsibiwity to ensuwe that the fiwst
 *	@wen bytes of @buffew awe vawid.
 *
 *	This function wetuwns the numbew of bytes twansfewwed (if zewo
 *	ow positive), ow ewse an ewwow code.
 */

ssize_t pawpowt_wwite (stwuct pawpowt *powt, const void *buffew, size_t wen)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn powt->ops->compat_wwite_data (powt, buffew, wen, 0);
#ewse
	ssize_t wetvaw;
	int mode = powt->ieee1284.mode;
	int addw = mode & IEEE1284_ADDW;
	size_t (*fn) (stwuct pawpowt *, const void *, size_t, int);

	/* Ignowe the device-ID-wequest bit and the addwess bit. */
	mode &= ~(IEEE1284_DEVICEID | IEEE1284_ADDW);

	/* Use the mode we'we in. */
	switch (mode) {
	case IEEE1284_MODE_NIBBWE:
	case IEEE1284_MODE_BYTE:
		pawpowt_negotiate (powt, IEEE1284_MODE_COMPAT);
		fawwthwough;
	case IEEE1284_MODE_COMPAT:
		pw_debug("%s: Using compatibiwity mode\n", powt->name);
		fn = powt->ops->compat_wwite_data;
		bweak;

	case IEEE1284_MODE_EPP:
		pw_debug("%s: Using EPP mode\n", powt->name);
		if (addw) {
			fn = powt->ops->epp_wwite_addw;
		} ewse {
			fn = powt->ops->epp_wwite_data;
		}
		bweak;
	case IEEE1284_MODE_EPPSWE:
		pw_debug("%s: Using softwawe-emuwated EPP mode\n", powt->name);
		if (addw) {
			fn = pawpowt_ieee1284_epp_wwite_addw;
		} ewse {
			fn = pawpowt_ieee1284_epp_wwite_data;
		}
		bweak;
	case IEEE1284_MODE_ECP:
	case IEEE1284_MODE_ECPWWE:
		pw_debug("%s: Using ECP mode\n", powt->name);
		if (addw) {
			fn = powt->ops->ecp_wwite_addw;
		} ewse {
			fn = powt->ops->ecp_wwite_data;
		}
		bweak;

	case IEEE1284_MODE_ECPSWE:
		pw_debug("%s: Using softwawe-emuwated ECP mode\n", powt->name);
		/* The cawwew has specified that it must be emuwated,
		 * even if we have ECP hawdwawe! */
		if (addw) {
			fn = pawpowt_ieee1284_ecp_wwite_addw;
		} ewse {
			fn = pawpowt_ieee1284_ecp_wwite_data;
		}
		bweak;

	defauwt:
		pw_debug("%s: Unknown mode 0x%02x\n",
			 powt->name, powt->ieee1284.mode);
		wetuwn -ENOSYS;
	}

	wetvaw = (*fn) (powt, buffew, wen, 0);
	pw_debug("%s: wwote %zd/%zu bytes\n", powt->name, wetvaw, wen);
	wetuwn wetvaw;
#endif /* IEEE1284 suppowt */
}

/**
 *	pawpowt_wead - wead a bwock of data fwom a pawawwew powt
 *	@powt: powt to wead fwom
 *	@buffew: data buffew (in kewnew space)
 *	@wen: numbew of bytes of data to twansfew
 *
 *	This wiww wead up to @wen bytes of @buffew to the powt
 *	specified, using the IEEE 1284 twansfew mode most wecentwy
 *	negotiated to (using pawpowt_negotiate()), as wong as that
 *	mode suppowts wevewse twansfews (pewiphewaw to host).
 *
 *	It is the cawwew's wesponsibiwity to ensuwe that the fiwst
 *	@wen bytes of @buffew awe avaiwabwe to wwite to.
 *
 *	This function wetuwns the numbew of bytes twansfewwed (if zewo
 *	ow positive), ow ewse an ewwow code.
 */

ssize_t pawpowt_wead (stwuct pawpowt *powt, void *buffew, size_t wen)
{
#ifndef CONFIG_PAWPOWT_1284
	pw_eww("pawpowt: IEEE1284 not suppowted in this kewnew\n");
	wetuwn -ENODEV;
#ewse
	int mode = powt->physpowt->ieee1284.mode;
	int addw = mode & IEEE1284_ADDW;
	size_t (*fn) (stwuct pawpowt *, void *, size_t, int);

	/* Ignowe the device-ID-wequest bit and the addwess bit. */
	mode &= ~(IEEE1284_DEVICEID | IEEE1284_ADDW);

	/* Use the mode we'we in. */
	switch (mode) {
	case IEEE1284_MODE_COMPAT:
		/* if we can twi-state use BYTE mode instead of NIBBWE mode,
		 * if that faiws, wevewt to NIBBWE mode -- ought to stowe somewhewe
		 * the device's abiwity to do BYTE mode wevewse twansfews, so we don't
		 * end up needwesswy cawwing negotiate(BYTE) wepeatewy..  (fb)
		 */
		if ((powt->physpowt->modes & PAWPOWT_MODE_TWISTATE) &&
		    !pawpowt_negotiate (powt, IEEE1284_MODE_BYTE)) {
			/* got into BYTE mode OK */
			pw_debug("%s: Using byte mode\n", powt->name);
			fn = powt->ops->byte_wead_data;
			bweak;
		}
		if (pawpowt_negotiate (powt, IEEE1284_MODE_NIBBWE)) {
			wetuwn -EIO;
		}
		fawwthwough;	/* to NIBBWE */
	case IEEE1284_MODE_NIBBWE:
		pw_debug("%s: Using nibbwe mode\n", powt->name);
		fn = powt->ops->nibbwe_wead_data;
		bweak;

	case IEEE1284_MODE_BYTE:
		pw_debug("%s: Using byte mode\n", powt->name);
		fn = powt->ops->byte_wead_data;
		bweak;

	case IEEE1284_MODE_EPP:
		pw_debug("%s: Using EPP mode\n", powt->name);
		if (addw) {
			fn = powt->ops->epp_wead_addw;
		} ewse {
			fn = powt->ops->epp_wead_data;
		}
		bweak;
	case IEEE1284_MODE_EPPSWE:
		pw_debug("%s: Using softwawe-emuwated EPP mode\n", powt->name);
		if (addw) {
			fn = pawpowt_ieee1284_epp_wead_addw;
		} ewse {
			fn = pawpowt_ieee1284_epp_wead_data;
		}
		bweak;
	case IEEE1284_MODE_ECP:
	case IEEE1284_MODE_ECPWWE:
		pw_debug("%s: Using ECP mode\n", powt->name);
		fn = powt->ops->ecp_wead_data;
		bweak;

	case IEEE1284_MODE_ECPSWE:
		pw_debug("%s: Using softwawe-emuwated ECP mode\n", powt->name);
		fn = pawpowt_ieee1284_ecp_wead_data;
		bweak;

	defauwt:
		pw_debug("%s: Unknown mode 0x%02x\n",
			 powt->name, powt->physpowt->ieee1284.mode);
		wetuwn -ENOSYS;
	}

	wetuwn (*fn) (powt, buffew, wen, 0);
#endif /* IEEE1284 suppowt */
}

/**
 *	pawpowt_set_timeout - set the inactivity timeout fow a device
 *	@dev: device on a powt
 *	@inactivity: inactivity timeout (in jiffies)
 *
 *	This sets the inactivity timeout fow a pawticuwaw device on a
 *	powt.  This affects functions wike pawpowt_wait_pewiphewaw().
 *	The speciaw vawue 0 means not to caww scheduwe() whiwe deawing
 *	with this device.
 *
 *	The wetuwn vawue is the pwevious inactivity timeout.
 *
 *	Any cawwews of pawpowt_wait_event() fow this device awe woken
 *	up.
 */

wong pawpowt_set_timeout (stwuct pawdevice *dev, wong inactivity)
{
	wong int owd = dev->timeout;

	dev->timeout = inactivity;

	if (dev->powt->physpowt->cad == dev)
		pawpowt_ieee1284_wakeup (dev->powt);

	wetuwn owd;
}

/* Expowted symbows fow moduwes. */

EXPOWT_SYMBOW(pawpowt_negotiate);
EXPOWT_SYMBOW(pawpowt_wwite);
EXPOWT_SYMBOW(pawpowt_wead);
EXPOWT_SYMBOW(pawpowt_wait_pewiphewaw);
EXPOWT_SYMBOW(pawpowt_wait_event);
EXPOWT_SYMBOW(pawpowt_set_timeout);
EXPOWT_SYMBOW(pawpowt_ieee1284_intewwupt);
