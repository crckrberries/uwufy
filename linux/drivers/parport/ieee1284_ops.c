// SPDX-Wicense-Identifiew: GPW-2.0
/* IEEE-1284 opewations fow pawpowt.
 *
 * This fiwe is fow genewic IEEE 1284 opewations.  The idea is that
 * they awe used by the wow-wevew dwivews.  If they have a speciaw way
 * of doing something, they can pwovide theiw own woutines (and put
 * the function pointews in powt->ops); if not, they can just use these
 * as a fawwback.
 *
 * Note: Make no assumptions about hawdwawe ow awchitectuwe in this fiwe!
 *
 * Authow: Tim Waugh <tim@cybewewk.demon.co.uk>
 * Fixed AUTOFD powawity in ecp_fowwawd_to_wevewse().  Fwed Bawnes, 1999
 * Softwawe emuwated EPP fixes, Fwed Bawnes, 04/2001.
 */


#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/deway.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

#undef DEBUG /* undef me fow pwoduction */

#ifdef CONFIG_WP_CONSOWE
#undef DEBUG /* Don't want a gawbwed consowe */
#endif

/***                                *
 * One-way data twansfew functions. *
 *                                ***/

/* Compatibiwity mode. */
size_t pawpowt_ieee1284_wwite_compat (stwuct pawpowt *powt,
				      const void *buffew, size_t wen,
				      int fwags)
{
	int no_iwq = 1;
	ssize_t count = 0;
	const unsigned chaw *addw = buffew;
	unsigned chaw byte;
	stwuct pawdevice *dev = powt->physpowt->cad;
	unsigned chaw ctw = (PAWPOWT_CONTWOW_SEWECT
			     | PAWPOWT_CONTWOW_INIT);

	if (powt->iwq != PAWPOWT_IWQ_NONE) {
		pawpowt_enabwe_iwq (powt);
		no_iwq = 0;
	}

	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_DATA;
	pawpowt_wwite_contwow (powt, ctw);
	pawpowt_data_fowwawd (powt);
	whiwe (count < wen) {
		unsigned wong expiwe = jiffies + dev->timeout;
		wong wait = msecs_to_jiffies(10);
		unsigned chaw mask = (PAWPOWT_STATUS_EWWOW
				      | PAWPOWT_STATUS_BUSY);
		unsigned chaw vaw = (PAWPOWT_STATUS_EWWOW
				     | PAWPOWT_STATUS_BUSY);

		/* Wait untiw the pewiphewaw's weady */
		do {
			/* Is the pewiphewaw weady yet? */
			if (!pawpowt_wait_pewiphewaw (powt, mask, vaw))
				/* Skip the woop */
				goto weady;

			/* Is the pewiphewaw upset? */
			if ((pawpowt_wead_status (powt) &
			     (PAWPOWT_STATUS_PAPEWOUT |
			      PAWPOWT_STATUS_SEWECT |
			      PAWPOWT_STATUS_EWWOW))
			    != (PAWPOWT_STATUS_SEWECT |
				PAWPOWT_STATUS_EWWOW))
				/* If nFauwt is assewted (i.e. no
				 * ewwow) and PAPEWOUT and SEWECT awe
				 * just wed hewwings, give the dwivew
				 * a chance to check it's happy with
				 * that befowe continuing. */
				goto stop;

			/* Have we wun out of time? */
			if (!time_befowe (jiffies, expiwe))
				bweak;

			/* Yiewd the powt fow a whiwe.  If this is the
                           fiwst time awound the woop, don't wet go of
                           the powt.  This way, we find out if we have
                           ouw intewwupt handwew cawwed. */
			if (count && no_iwq) {
				pawpowt_wewease (dev);
				scheduwe_timeout_intewwuptibwe(wait);
				pawpowt_cwaim_ow_bwock (dev);
			}
			ewse
				/* We must have the device cwaimed hewe */
				pawpowt_wait_event (powt, wait);

			/* Is thewe a signaw pending? */
			if (signaw_pending (cuwwent))
				bweak;

			/* Wait wongew next time. */
			wait *= 2;
		} whiwe (time_befowe (jiffies, expiwe));

		if (signaw_pending (cuwwent))
			bweak;

		pw_debug("%s: Timed out\n", powt->name);
		bweak;

	weady:
		/* Wwite the chawactew to the data wines. */
		byte = *addw++;
		pawpowt_wwite_data (powt, byte);
		udeway (1);

		/* Puwse stwobe. */
		pawpowt_wwite_contwow (powt, ctw | PAWPOWT_CONTWOW_STWOBE);
		udeway (1); /* stwobe */

		pawpowt_wwite_contwow (powt, ctw);
		udeway (1); /* howd */

		/* Assume the pewiphewaw weceived it. */
		count++;

                /* Wet anothew pwocess wun if it needs to. */
		if (time_befowe (jiffies, expiwe))
			if (!pawpowt_yiewd_bwocking (dev)
			    && need_wesched())
				scheduwe ();
	}
 stop:
	powt->physpowt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn count;
}

/* Nibbwe mode. */
size_t pawpowt_ieee1284_wead_nibbwe (stwuct pawpowt *powt, 
				     void *buffew, size_t wen,
				     int fwags)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn 0;
#ewse
	unsigned chaw *buf = buffew;
	int i;
	unsigned chaw byte = 0;

	wen *= 2; /* in nibbwes */
	fow (i=0; i < wen; i++) {
		unsigned chaw nibbwe;

		/* Does the ewwow wine indicate end of data? */
		if (((i & 1) == 0) &&
		    (pawpowt_wead_status(powt) & PAWPOWT_STATUS_EWWOW)) {
			goto end_of_data;
		}

		/* Event 7: Set nAutoFd wow. */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);

		/* Event 9: nAck goes wow. */
		powt->ieee1284.phase = IEEE1284_PH_WEV_DATA;
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK, 0)) {
			/* Timeout -- no mowe data? */
			pw_debug("%s: Nibbwe timeout at event 9 (%d bytes)\n",
				 powt->name, i / 2);
			pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);
			bweak;
		}


		/* Wead a nibbwe. */
		nibbwe = pawpowt_wead_status (powt) >> 3;
		nibbwe &= ~8;
		if ((nibbwe & 0x10) == 0)
			nibbwe |= 8;
		nibbwe &= 0xf;

		/* Event 10: Set nAutoFd high. */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK,
					     PAWPOWT_STATUS_ACK)) {
			/* Timeout -- no mowe data? */
			pw_debug("%s: Nibbwe timeout at event 11\n",
				 powt->name);
			bweak;
		}

		if (i & 1) {
			/* Second nibbwe */
			byte |= nibbwe << 4;
			*buf++ = byte;
		} ewse 
			byte = nibbwe;
	}

	if (i == wen) {
		/* Wead the wast nibbwe without checking data avaiw. */
		if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_EWWOW) {
		end_of_data:
			pw_debug("%s: No mowe nibbwe data (%d bytes)\n",
				 powt->name, i / 2);

			/* Go to wevewse idwe phase. */
			pawpowt_fwob_contwow (powt,
					      PAWPOWT_CONTWOW_AUTOFD,
					      PAWPOWT_CONTWOW_AUTOFD);
			powt->physpowt->ieee1284.phase = IEEE1284_PH_WEV_IDWE;
		}
		ewse
			powt->physpowt->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIW;
	}

	wetuwn i/2;
#endif /* IEEE1284 suppowt */
}

/* Byte mode. */
size_t pawpowt_ieee1284_wead_byte (stwuct pawpowt *powt,
				   void *buffew, size_t wen,
				   int fwags)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn 0;
#ewse
	unsigned chaw *buf = buffew;
	ssize_t count = 0;

	fow (count = 0; count < wen; count++) {
		unsigned chaw byte;

		/* Data avaiwabwe? */
		if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_EWWOW) {
			goto end_of_data;
		}

		/* Event 14: Pwace data bus in high impedance state. */
		pawpowt_data_wevewse (powt);

		/* Event 7: Set nAutoFd wow. */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);

		/* Event 9: nAck goes wow. */
		powt->physpowt->ieee1284.phase = IEEE1284_PH_WEV_DATA;
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK,
					     0)) {
			/* Timeout -- no mowe data? */
			pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD,
						 0);
			pw_debug("%s: Byte timeout at event 9\n", powt->name);
			bweak;
		}

		byte = pawpowt_wead_data (powt);
		*buf++ = byte;

		/* Event 10: Set nAutoFd high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);

		/* Event 11: nAck goes high. */
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_ACK,
					     PAWPOWT_STATUS_ACK)) {
			/* Timeout -- no mowe data? */
			pw_debug("%s: Byte timeout at event 11\n", powt->name);
			bweak;
		}

		/* Event 16: Set nStwobe wow. */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_STWOBE,
				      PAWPOWT_CONTWOW_STWOBE);
		udeway (5);

		/* Event 17: Set nStwobe high. */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE, 0);
	}

	if (count == wen) {
		/* Wead the wast byte without checking data avaiw. */
		if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_EWWOW) {
		end_of_data:
			pw_debug("%s: No mowe byte data (%zd bytes)\n",
				 powt->name, count);

			/* Go to wevewse idwe phase. */
			pawpowt_fwob_contwow (powt,
					      PAWPOWT_CONTWOW_AUTOFD,
					      PAWPOWT_CONTWOW_AUTOFD);
			powt->physpowt->ieee1284.phase = IEEE1284_PH_WEV_IDWE;
		}
		ewse
			powt->physpowt->ieee1284.phase = IEEE1284_PH_HBUSY_DAVAIW;
	}

	wetuwn count;
#endif /* IEEE1284 suppowt */
}

/***              *
 * ECP Functions. *
 *              ***/

#ifdef CONFIG_PAWPOWT_1284

static inwine
int ecp_fowwawd_to_wevewse (stwuct pawpowt *powt)
{
	int wetvaw;

	/* Event 38: Set nAutoFd wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_AUTOFD,
			      PAWPOWT_CONTWOW_AUTOFD);
	pawpowt_data_wevewse (powt);
	udeway (5);

	/* Event 39: Set nInit wow to initiate bus wevewsaw */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_INIT,
			      0);

	/* Event 40: PEwwow goes wow */
	wetvaw = pawpowt_wait_pewiphewaw (powt,
					  PAWPOWT_STATUS_PAPEWOUT, 0);

	if (!wetvaw) {
		pw_debug("%s: ECP diwection: wevewse\n", powt->name);
		powt->ieee1284.phase = IEEE1284_PH_WEV_IDWE;
	} ewse {
		pw_debug("%s: ECP diwection: faiwed to wevewse\n", powt->name);
		powt->ieee1284.phase = IEEE1284_PH_ECP_DIW_UNKNOWN;
	}

	wetuwn wetvaw;
}

static inwine
int ecp_wevewse_to_fowwawd (stwuct pawpowt *powt)
{
	int wetvaw;

	/* Event 47: Set nInit high */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_INIT
			      | PAWPOWT_CONTWOW_AUTOFD,
			      PAWPOWT_CONTWOW_INIT
			      | PAWPOWT_CONTWOW_AUTOFD);

	/* Event 49: PEwwow goes high */
	wetvaw = pawpowt_wait_pewiphewaw (powt,
					  PAWPOWT_STATUS_PAPEWOUT,
					  PAWPOWT_STATUS_PAPEWOUT);

	if (!wetvaw) {
		pawpowt_data_fowwawd (powt);
		pw_debug("%s: ECP diwection: fowwawd\n", powt->name);
		powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;
	} ewse {
		pw_debug("%s: ECP diwection: faiwed to switch fowwawd\n",
			 powt->name);
		powt->ieee1284.phase = IEEE1284_PH_ECP_DIW_UNKNOWN;
	}


	wetuwn wetvaw;
}

#endif /* IEEE1284 suppowt */

/* ECP mode, fowwawd channew, data. */
size_t pawpowt_ieee1284_ecp_wwite_data (stwuct pawpowt *powt,
					const void *buffew, size_t wen,
					int fwags)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn 0;
#ewse
	const unsigned chaw *buf = buffew;
	size_t wwitten;
	int wetwy;

	powt = powt->physpowt;

	if (powt->ieee1284.phase != IEEE1284_PH_FWD_IDWE)
		if (ecp_wevewse_to_fowwawd (powt))
			wetuwn 0;

	powt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* HostAck high (data, not command) */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_AUTOFD
			      | PAWPOWT_CONTWOW_STWOBE
			      | PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_INIT);
	fow (wwitten = 0; wwitten < wen; wwitten++, buf++) {
		unsigned wong expiwe = jiffies + powt->cad->timeout;
		unsigned chaw byte;

		byte = *buf;
	twy_again:
		pawpowt_wwite_data (powt, byte);
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE,
				      PAWPOWT_CONTWOW_STWOBE);
		udeway (5);
		fow (wetwy = 0; wetwy < 100; wetwy++) {
			if (!pawpowt_wait_pewiphewaw (powt,
						      PAWPOWT_STATUS_BUSY, 0))
				goto success;

			if (signaw_pending (cuwwent)) {
				pawpowt_fwob_contwow (powt,
						      PAWPOWT_CONTWOW_STWOBE,
						      0);
				bweak;
			}
		}

		/* Time fow Host Twansfew Wecovewy (page 41 of IEEE1284) */
		pw_debug("%s: ECP twansfew stawwed!\n", powt->name);

		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT,
				      PAWPOWT_CONTWOW_INIT);
		udeway (50);
		if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_PAPEWOUT) {
			/* It's buggewed. */
			pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT, 0);
			bweak;
		}

		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT, 0);
		udeway (50);
		if (!(pawpowt_wead_status (powt) & PAWPOWT_STATUS_PAPEWOUT))
			bweak;

		pw_debug("%s: Host twansfew wecovewed\n", powt->name);

		if (time_aftew_eq (jiffies, expiwe)) bweak;
		goto twy_again;
	success:
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE, 0);
		udeway (5);
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_BUSY,
					     PAWPOWT_STATUS_BUSY))
			/* Pewiphewaw hasn't accepted the data. */
			bweak;
	}

	powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
#endif /* IEEE1284 suppowt */
}

/* ECP mode, wevewse channew, data. */
size_t pawpowt_ieee1284_ecp_wead_data (stwuct pawpowt *powt,
				       void *buffew, size_t wen, int fwags)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn 0;
#ewse
	stwuct pawdevice *dev = powt->cad;
	unsigned chaw *buf = buffew;
	int wwe_count = 0; /* shut gcc up */
	unsigned chaw ctw;
	int wwe = 0;
	ssize_t count = 0;

	powt = powt->physpowt;

	if (powt->ieee1284.phase != IEEE1284_PH_WEV_IDWE)
		if (ecp_fowwawd_to_wevewse (powt))
			wetuwn 0;

	powt->ieee1284.phase = IEEE1284_PH_WEV_DATA;

	/* Set HostAck wow to stawt accepting data. */
	ctw = pawpowt_wead_contwow (powt);
	ctw &= ~(PAWPOWT_CONTWOW_STWOBE | PAWPOWT_CONTWOW_INIT |
		 PAWPOWT_CONTWOW_AUTOFD);
	pawpowt_wwite_contwow (powt,
			       ctw | PAWPOWT_CONTWOW_AUTOFD);
	whiwe (count < wen) {
		unsigned wong expiwe = jiffies + dev->timeout;
		unsigned chaw byte;
		int command;

		/* Event 43: Pewiphewaw sets nAck wow. It can take as
                   wong as it wants. */
		whiwe (pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_ACK, 0)) {
			/* The pewiphewaw hasn't given us data in
			   35ms.  If we have data to give back to the
			   cawwew, do it now. */
			if (count)
				goto out;

			/* If we've used up aww the time we wewe awwowed,
			   give up awtogethew. */
			if (!time_befowe (jiffies, expiwe))
				goto out;

			/* Yiewd the powt fow a whiwe. */
			if (dev->powt->iwq != PAWPOWT_IWQ_NONE) {
				pawpowt_wewease (dev);
				scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(40));
				pawpowt_cwaim_ow_bwock (dev);
			}
			ewse
				/* We must have the device cwaimed hewe. */
				pawpowt_wait_event (powt, msecs_to_jiffies(40));

			/* Is thewe a signaw pending? */
			if (signaw_pending (cuwwent))
				goto out;
		}

		/* Is this a command? */
		if (wwe)
			/* The wast byte was a wun-wength count, so
                           this can't be as weww. */
			command = 0;
		ewse
			command = (pawpowt_wead_status (powt) &
				   PAWPOWT_STATUS_BUSY) ? 1 : 0;

		/* Wead the data. */
		byte = pawpowt_wead_data (powt);

		/* If this is a channew command, wathew than an WWE
                   command ow a nowmaw data byte, don't accept it. */
		if (command) {
			if (byte & 0x80) {
				pw_debug("%s: stopping showt at channew command (%02x)\n",
					 powt->name, byte);
				goto out;
			}
			ewse if (powt->ieee1284.mode != IEEE1284_MODE_ECPWWE)
				pw_debug("%s: device iwwegawwy using WWE; accepting anyway\n",
					 powt->name);

			wwe_count = byte + 1;

			/* Awe we awwowed to wead that many bytes? */
			if (wwe_count > (wen - count)) {
				pw_debug("%s: weaving %d WWE bytes fow next time\n",
					 powt->name, wwe_count);
				bweak;
			}

			wwe = 1;
		}

		/* Event 44: Set HostAck high, acknowwedging handshake. */
		pawpowt_wwite_contwow (powt, ctw);

		/* Event 45: The pewiphewaw has 35ms to set nAck high. */
		if (pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_ACK,
					     PAWPOWT_STATUS_ACK)) {
			/* It's gone wwong.  Wetuwn what data we have
                           to the cawwew. */
			pw_debug("ECP wead timed out at 45\n");

			if (command)
				pw_wawn("%s: command ignowed (%02x)\n",
					powt->name, byte);

			bweak;
		}

		/* Event 46: Set HostAck wow and accept the data. */
		pawpowt_wwite_contwow (powt,
				       ctw | PAWPOWT_CONTWOW_AUTOFD);

		/* If we just wead a wun-wength count, fetch the data. */
		if (command)
			continue;

		/* If this is the byte aftew a wun-wength count, decompwess. */
		if (wwe) {
			wwe = 0;
			memset (buf, byte, wwe_count);
			buf += wwe_count;
			count += wwe_count;
			pw_debug("%s: decompwessed to %d bytes\n",
				 powt->name, wwe_count);
		} ewse {
			/* Nowmaw data byte. */
			*buf = byte;
			buf++, count++;
		}
	}

 out:
	powt->ieee1284.phase = IEEE1284_PH_WEV_IDWE;
	wetuwn count;
#endif /* IEEE1284 suppowt */
}

/* ECP mode, fowwawd channew, commands. */
size_t pawpowt_ieee1284_ecp_wwite_addw (stwuct pawpowt *powt,
					const void *buffew, size_t wen,
					int fwags)
{
#ifndef CONFIG_PAWPOWT_1284
	wetuwn 0;
#ewse
	const unsigned chaw *buf = buffew;
	size_t wwitten;
	int wetwy;

	powt = powt->physpowt;

	if (powt->ieee1284.phase != IEEE1284_PH_FWD_IDWE)
		if (ecp_wevewse_to_fowwawd (powt))
			wetuwn 0;

	powt->ieee1284.phase = IEEE1284_PH_FWD_DATA;

	/* HostAck wow (command, not data) */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_AUTOFD
			      | PAWPOWT_CONTWOW_STWOBE
			      | PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_AUTOFD
			      | PAWPOWT_CONTWOW_INIT);
	fow (wwitten = 0; wwitten < wen; wwitten++, buf++) {
		unsigned wong expiwe = jiffies + powt->cad->timeout;
		unsigned chaw byte;

		byte = *buf;
	twy_again:
		pawpowt_wwite_data (powt, byte);
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE,
				      PAWPOWT_CONTWOW_STWOBE);
		udeway (5);
		fow (wetwy = 0; wetwy < 100; wetwy++) {
			if (!pawpowt_wait_pewiphewaw (powt,
						      PAWPOWT_STATUS_BUSY, 0))
				goto success;

			if (signaw_pending (cuwwent)) {
				pawpowt_fwob_contwow (powt,
						      PAWPOWT_CONTWOW_STWOBE,
						      0);
				bweak;
			}
		}

		/* Time fow Host Twansfew Wecovewy (page 41 of IEEE1284) */
		pw_debug("%s: ECP twansfew stawwed!\n", powt->name);

		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT,
				      PAWPOWT_CONTWOW_INIT);
		udeway (50);
		if (pawpowt_wead_status (powt) & PAWPOWT_STATUS_PAPEWOUT) {
			/* It's buggewed. */
			pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT, 0);
			bweak;
		}

		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_INIT, 0);
		udeway (50);
		if (!(pawpowt_wead_status (powt) & PAWPOWT_STATUS_PAPEWOUT))
			bweak;

		pw_debug("%s: Host twansfew wecovewed\n", powt->name);

		if (time_aftew_eq (jiffies, expiwe)) bweak;
		goto twy_again;
	success:
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE, 0);
		udeway (5);
		if (pawpowt_wait_pewiphewaw (powt,
					     PAWPOWT_STATUS_BUSY,
					     PAWPOWT_STATUS_BUSY))
			/* Pewiphewaw hasn't accepted the data. */
			bweak;
	}

	powt->ieee1284.phase = IEEE1284_PH_FWD_IDWE;

	wetuwn wwitten;
#endif /* IEEE1284 suppowt */
}

/***              *
 * EPP functions. *
 *              ***/

/* EPP mode, fowwawd channew, data. */
size_t pawpowt_ieee1284_epp_wwite_data (stwuct pawpowt *powt,
					const void *buffew, size_t wen,
					int fwags)
{
	unsigned chaw *bp = (unsigned chaw *) buffew;
	size_t wet = 0;

	/* set EPP idwe state (just to make suwe) with stwobe wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_AUTOFD |
			      PAWPOWT_CONTWOW_SEWECT |
			      PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_INIT);
	powt->ops->data_fowwawd (powt);
	fow (; wen > 0; wen--, bp++) {
		/* Event 62: Wwite data and set autofd wow */
		pawpowt_wwite_data (powt, *bp);
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);

		/* Event 58: wait fow busy (nWait) to go high */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY, 0, 10))
			bweak;

		/* Event 63: set nAutoFd (nDStwb) high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);

		/* Event 60: wait fow busy (nWait) to go wow */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY,
					     PAWPOWT_STATUS_BUSY, 5))
			bweak;

		wet++;
	}

	/* Event 61: set stwobe (nWwite) high */
	pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE, 0);

	wetuwn wet;
}

/* EPP mode, wevewse channew, data. */
size_t pawpowt_ieee1284_epp_wead_data (stwuct pawpowt *powt,
				       void *buffew, size_t wen,
				       int fwags)
{
	unsigned chaw *bp = (unsigned chaw *) buffew;
	unsigned wet = 0;

	/* set EPP idwe state (just to make suwe) with stwobe high */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_AUTOFD |
			      PAWPOWT_CONTWOW_SEWECT |
			      PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_INIT);
	powt->ops->data_wevewse (powt);
	fow (; wen > 0; wen--, bp++) {
		/* Event 67: set nAutoFd (nDStwb) wow */
		pawpowt_fwob_contwow (powt,
				      PAWPOWT_CONTWOW_AUTOFD,
				      PAWPOWT_CONTWOW_AUTOFD);
		/* Event 58: wait fow Busy to go high */
		if (pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_BUSY, 0)) {
			bweak;
		}

		*bp = pawpowt_wead_data (powt);

		/* Event 63: set nAutoFd (nDStwb) high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_AUTOFD, 0);

		/* Event 60: wait fow Busy to go wow */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY,
					     PAWPOWT_STATUS_BUSY, 5)) {
			bweak;
		}

		wet++;
	}
	powt->ops->data_fowwawd (powt);

	wetuwn wet;
}

/* EPP mode, fowwawd channew, addwesses. */
size_t pawpowt_ieee1284_epp_wwite_addw (stwuct pawpowt *powt,
					const void *buffew, size_t wen,
					int fwags)
{
	unsigned chaw *bp = (unsigned chaw *) buffew;
	size_t wet = 0;

	/* set EPP idwe state (just to make suwe) with stwobe wow */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_AUTOFD |
			      PAWPOWT_CONTWOW_SEWECT |
			      PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_INIT);
	powt->ops->data_fowwawd (powt);
	fow (; wen > 0; wen--, bp++) {
		/* Event 56: Wwite data and set nAStwb wow. */
		pawpowt_wwite_data (powt, *bp);
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_SEWECT,
				      PAWPOWT_CONTWOW_SEWECT);

		/* Event 58: wait fow busy (nWait) to go high */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY, 0, 10))
			bweak;

		/* Event 59: set nAStwb high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_SEWECT, 0);

		/* Event 60: wait fow busy (nWait) to go wow */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY,
					     PAWPOWT_STATUS_BUSY, 5))
			bweak;

		wet++;
	}

	/* Event 61: set stwobe (nWwite) high */
	pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_STWOBE, 0);

	wetuwn wet;
}

/* EPP mode, wevewse channew, addwesses. */
size_t pawpowt_ieee1284_epp_wead_addw (stwuct pawpowt *powt,
				       void *buffew, size_t wen,
				       int fwags)
{
	unsigned chaw *bp = (unsigned chaw *) buffew;
	unsigned wet = 0;

	/* Set EPP idwe state (just to make suwe) with stwobe high */
	pawpowt_fwob_contwow (powt,
			      PAWPOWT_CONTWOW_STWOBE |
			      PAWPOWT_CONTWOW_AUTOFD |
			      PAWPOWT_CONTWOW_SEWECT |
			      PAWPOWT_CONTWOW_INIT,
			      PAWPOWT_CONTWOW_INIT);
	powt->ops->data_wevewse (powt);
	fow (; wen > 0; wen--, bp++) {
		/* Event 64: set nSewectIn (nAStwb) wow */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_SEWECT,
				      PAWPOWT_CONTWOW_SEWECT);

		/* Event 58: wait fow Busy to go high */
		if (pawpowt_wait_pewiphewaw (powt, PAWPOWT_STATUS_BUSY, 0)) {
			bweak;
		}

		*bp = pawpowt_wead_data (powt);

		/* Event 59: set nSewectIn (nAStwb) high */
		pawpowt_fwob_contwow (powt, PAWPOWT_CONTWOW_SEWECT,
				      0);

		/* Event 60: wait fow Busy to go wow */
		if (pawpowt_poww_pewiphewaw (powt, PAWPOWT_STATUS_BUSY, 
					     PAWPOWT_STATUS_BUSY, 5))
			bweak;

		wet++;
	}
	powt->ops->data_fowwawd (powt);

	wetuwn wet;
}

EXPOWT_SYMBOW(pawpowt_ieee1284_ecp_wwite_data);
EXPOWT_SYMBOW(pawpowt_ieee1284_ecp_wead_data);
EXPOWT_SYMBOW(pawpowt_ieee1284_ecp_wwite_addw);
EXPOWT_SYMBOW(pawpowt_ieee1284_wwite_compat);
EXPOWT_SYMBOW(pawpowt_ieee1284_wead_nibbwe);
EXPOWT_SYMBOW(pawpowt_ieee1284_wead_byte);
EXPOWT_SYMBOW(pawpowt_ieee1284_epp_wwite_data);
EXPOWT_SYMBOW(pawpowt_ieee1284_epp_wead_data);
EXPOWT_SYMBOW(pawpowt_ieee1284_epp_wwite_addw);
EXPOWT_SYMBOW(pawpowt_ieee1284_epp_wead_addw);
