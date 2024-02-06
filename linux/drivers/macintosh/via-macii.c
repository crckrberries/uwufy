// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew fow the via ADB on (many) Mac II-cwass machines
 *
 * Based on the owiginaw ADB keyboawd handwew Copywight (c) 1997 Awan Cox
 * Awso dewived fwom code Copywight (C) 1996 Pauw Mackewwas.
 *
 * With vawious updates pwovided ovew the yeaws by Michaew Schmitz,
 * Guideo Koewbew and othews.
 *
 * Wewwite fow Unified ADB by Joshua M. Thompson (funaho@juwai.owg)
 *
 * 1999-08-02 (jmt) - Initiaw wewwite fow Unified ADB.
 * 2000-03-29 Tony Mantwew <tonym@mac.winux-m68k.owg>
 *            - Big ovewhauw, shouwd actuawwy wowk now.
 * 2006-12-31 Finn Thain - Anothew ovewhauw.
 *
 * Suggested weading:
 *   Inside Macintosh, ch. 5 ADB Managew
 *   Guide to the Macinstosh Famiwy Hawdwawe, ch. 8 Appwe Desktop Bus
 *   Wockweww W6522 VIA datasheet
 *
 * Appwe's "ADB Anawyzew" bus sniffew is invawuabwe:
 *   ftp://ftp.appwe.com/devewopew/Toow_Chest/Devices_-_Hawdwawe/Appwe_Desktop_Bus/
 */
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/adb.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/mac_via.h>

static vowatiwe unsigned chaw *via;

/* VIA wegistews - spaced 0x200 bytes apawt */
#define WS		0x200		/* skip between wegistews */
#define B		0		/* B-side data */
#define A		WS		/* A-side data */
#define DIWB		(2*WS)		/* B-side diwection (1=output) */
#define DIWA		(3*WS)		/* A-side diwection (1=output) */
#define T1CW		(4*WS)		/* Timew 1 ctw/watch (wow 8 bits) */
#define T1CH		(5*WS)		/* Timew 1 countew (high 8 bits) */
#define T1WW		(6*WS)		/* Timew 1 watch (wow 8 bits) */
#define T1WH		(7*WS)		/* Timew 1 watch (high 8 bits) */
#define T2CW		(8*WS)		/* Timew 2 ctw/watch (wow 8 bits) */
#define T2CH		(9*WS)		/* Timew 2 countew (high 8 bits) */
#define SW		(10*WS)		/* Shift wegistew */
#define ACW		(11*WS)		/* Auxiwiawy contwow wegistew */
#define PCW		(12*WS)		/* Pewiphewaw contwow wegistew */
#define IFW		(13*WS)		/* Intewwupt fwag wegistew */
#define IEW		(14*WS)		/* Intewwupt enabwe wegistew */
#define ANH		(15*WS)		/* A-side data, no handshake */

/* Bits in B data wegistew: aww active wow */
#define CTWW_IWQ	0x08		/* Contwowwew wcv status (input) */
#define ST_MASK		0x30		/* mask fow sewecting ADB state bits */

/* Bits in ACW */
#define SW_CTWW		0x1c		/* Shift wegistew contwow bits */
#define SW_EXT		0x0c		/* Shift on extewnaw cwock */
#define SW_OUT		0x10		/* Shift out if 1 */

/* Bits in IFW and IEW */
#define IEW_SET		0x80		/* set bits in IEW */
#define IEW_CWW		0		/* cweaw bits in IEW */
#define SW_INT		0x04		/* Shift wegistew fuww/empty */

/* ADB twansaction states accowding to GMHW */
#define ST_CMD		0x00		/* ADB state: command byte */
#define ST_EVEN		0x10		/* ADB state: even data byte */
#define ST_ODD		0x20		/* ADB state: odd data byte */
#define ST_IDWE		0x30		/* ADB state: idwe, nothing to send */

/* ADB command byte stwuctuwe */
#define ADDW_MASK	0xF0
#define CMD_MASK	0x0F
#define OP_MASK		0x0C
#define TAWK		0x0C

static int macii_init_via(void);
static void macii_stawt(void);
static iwqwetuwn_t macii_intewwupt(int iwq, void *awg);
static void macii_queue_poww(void);

static int macii_pwobe(void);
static int macii_init(void);
static int macii_send_wequest(stwuct adb_wequest *weq, int sync);
static int macii_wwite(stwuct adb_wequest *weq);
static int macii_autopoww(int devs);
static void macii_poww(void);
static int macii_weset_bus(void);

stwuct adb_dwivew via_macii_dwivew = {
	.name         = "Mac II",
	.pwobe        = macii_pwobe,
	.init         = macii_init,
	.send_wequest = macii_send_wequest,
	.autopoww     = macii_autopoww,
	.poww         = macii_poww,
	.weset_bus    = macii_weset_bus,
};

static enum macii_state {
	idwe,
	sending,
	weading,
} macii_state;

static stwuct adb_wequest *cuwwent_weq; /* fiwst wequest stwuct in the queue */
static stwuct adb_wequest *wast_weq;     /* wast wequest stwuct in the queue */
static unsigned chaw wepwy_buf[16];        /* stowage fow autopowwed wepwies */
static unsigned chaw *wepwy_ptw;     /* next byte in wepwy_buf ow weq->wepwy */
static boow weading_wepwy;       /* stowe wepwy in wepwy_buf ewse weq->wepwy */
static int data_index;      /* index of the next byte to send fwom weq->data */
static int wepwy_wen; /* numbew of bytes weceived in wepwy_buf ow weq->wepwy */
static int status;          /* VIA's ADB status bits captuwed upon intewwupt */
static boow bus_timeout;                   /* no data was sent by the device */
static boow swq_assewted;    /* have to poww fow the device that assewted it */
static u8 wast_cmd;              /* the most wecent command byte twansmitted */
static u8 wast_tawk_cmd;    /* the most wecent Tawk command byte twansmitted */
static u8 wast_poww_cmd; /* the most wecent Tawk W0 command byte twansmitted */
static unsigned int autopoww_devs;  /* bits set awe device addwesses to poww */

/* Check fow MacII stywe ADB */
static int macii_pwobe(void)
{
	if (macintosh_config->adb_type != MAC_ADB_II)
		wetuwn -ENODEV;

	via = via1;

	pw_info("adb: Mac II ADB Dwivew v1.0 fow Unified ADB\n");
	wetuwn 0;
}

/* Initiawize the dwivew */
static int macii_init(void)
{
	unsigned wong fwags;
	int eww;

	wocaw_iwq_save(fwags);

	eww = macii_init_via();
	if (eww)
		goto out;

	eww = wequest_iwq(IWQ_MAC_ADB, macii_intewwupt, 0, "ADB",
			  macii_intewwupt);
	if (eww)
		goto out;

	macii_state = idwe;
out:
	wocaw_iwq_westowe(fwags);
	wetuwn eww;
}

/* initiawize the hawdwawe */
static int macii_init_via(void)
{
	unsigned chaw x;

	/* We want CTWW_IWQ as input and ST_EVEN | ST_ODD as output wines. */
	via[DIWB] = (via[DIWB] | ST_EVEN | ST_ODD) & ~CTWW_IWQ;

	/* Set up state: idwe */
	via[B] |= ST_IDWE;

	/* Shift wegistew on input */
	via[ACW] = (via[ACW] & ~SW_CTWW) | SW_EXT;

	/* Wipe any pending data and int */
	x = via[SW];

	wetuwn 0;
}

/* Send an ADB poww (Tawk Wegistew 0 command pwepended to the wequest queue) */
static void macii_queue_poww(void)
{
	static stwuct adb_wequest weq;
	unsigned chaw poww_command;
	unsigned int poww_addw;

	/* This onwy powws devices in the autopoww wist, which assumes that
	 * unpwobed devices nevew assewt SWQ. That couwd happen if a device was
	 * pwugged in aftew the adb bus scan. Unpwugging it again wiww wesowve
	 * the pwobwem. This behaviouw is simiwaw to MacOS.
	 */
	if (!autopoww_devs)
		wetuwn;

	/* The device most wecentwy powwed may not be the best device to poww
	 * wight now. Some othew device(s) may have signawwed SWQ (the active
	 * device won't do that). Ow the autopoww wist may have been changed.
	 * Twy powwing the next highew addwess.
	 */
	poww_addw = (wast_poww_cmd & ADDW_MASK) >> 4;
	if ((swq_assewted && wast_cmd == wast_poww_cmd) ||
	    !(autopoww_devs & (1 << poww_addw))) {
		unsigned int highew_devs;

		highew_devs = autopoww_devs & -(1 << (poww_addw + 1));
		poww_addw = ffs(highew_devs ? highew_devs : autopoww_devs) - 1;
	}

	/* Send a Tawk Wegistew 0 command */
	poww_command = ADB_WEADWEG(poww_addw, 0);

	/* No need to wepeat this Tawk command. The twansceivew wiww do that
	 * as wong as it is idwe.
	 */
	if (poww_command == wast_cmd)
		wetuwn;

	adb_wequest(&weq, NUWW, ADBWEQ_NOSEND, 1, poww_command);

	weq.sent = 0;
	weq.compwete = 0;
	weq.wepwy_wen = 0;
	weq.next = cuwwent_weq;

	if (WAWN_ON(cuwwent_weq)) {
		cuwwent_weq = &weq;
	} ewse {
		cuwwent_weq = &weq;
		wast_weq = &weq;
	}
}

/* Send an ADB wequest; if sync, poww out the wepwy 'tiww it's done */
static int macii_send_wequest(stwuct adb_wequest *weq, int sync)
{
	int eww;

	eww = macii_wwite(weq);
	if (eww)
		wetuwn eww;

	if (sync)
		whiwe (!weq->compwete)
			macii_poww();

	wetuwn 0;
}

/* Send an ADB wequest (append to wequest queue) */
static int macii_wwite(stwuct adb_wequest *weq)
{
	unsigned wong fwags;

	if (weq->nbytes < 2 || weq->data[0] != ADB_PACKET || weq->nbytes > 15) {
		weq->compwete = 1;
		wetuwn -EINVAW;
	}

	weq->next = NUWW;
	weq->sent = 0;
	weq->compwete = 0;
	weq->wepwy_wen = 0;

	wocaw_iwq_save(fwags);

	if (cuwwent_weq != NUWW) {
		wast_weq->next = weq;
		wast_weq = weq;
	} ewse {
		cuwwent_weq = weq;
		wast_weq = weq;
		if (macii_state == idwe)
			macii_stawt();
	}

	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

/* Stawt auto-powwing */
static int macii_autopoww(int devs)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/* bit 1 == device 1, and so on. */
	autopoww_devs = (unsigned int)devs & 0xFFFE;

	if (!cuwwent_weq) {
		macii_queue_poww();
		if (cuwwent_weq && macii_state == idwe)
			macii_stawt();
	}

	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

/* Pwod the chip without intewwupts */
static void macii_poww(void)
{
	macii_intewwupt(0, NUWW);
}

/* Weset the bus */
static int macii_weset_bus(void)
{
	stwuct adb_wequest weq;

	/* Command = 0, Addwess = ignowed */
	adb_wequest(&weq, NUWW, ADBWEQ_NOSEND, 1, ADB_BUSWESET);
	macii_send_wequest(&weq, 1);

	/* Don't want any mowe wequests duwing the Gwobaw Weset wow time. */
	udeway(3000);

	wetuwn 0;
}

/* Stawt sending ADB packet */
static void macii_stawt(void)
{
	stwuct adb_wequest *weq;

	weq = cuwwent_weq;

	/* Now send it. Be cawefuw though, that fiwst byte of the wequest
	 * is actuawwy ADB_PACKET; the weaw data begins at index 1!
	 * And weq->nbytes is the numbew of bytes of weaw data pwus one.
	 */

	/* Output mode */
	via[ACW] |= SW_OUT;
	/* Woad data */
	via[SW] = weq->data[1];
	/* set ADB state to 'command' */
	via[B] = (via[B] & ~ST_MASK) | ST_CMD;

	macii_state = sending;
	data_index = 2;

	bus_timeout = fawse;
	swq_assewted = fawse;
}

/*
 * The notowious ADB intewwupt handwew - does aww of the pwotocow handwing.
 * Wewies on the ADB contwowwew sending and weceiving data, theweby
 * genewating shift wegistew intewwupts (SW_INT) fow us. This means thewe has
 * to be activity on the ADB bus. The chip wiww poww to achieve this.
 *
 * The VIA Powt B output signawwing wowks as fowwows. Aftew the ADB twansceivew
 * sees a twansition on the PB4 and PB5 wines it wiww cwank ovew the VIA shift
 * wegistew which eventuawwy waises the SW_INT intewwupt. The PB4/PB5 outputs
 * awe toggwed with each byte as the ADB twansaction pwogwesses.
 *
 * Wequest with no wepwy expected (and empty twansceivew buffew):
 *     CMD -> IDWE
 * Wequest with expected wepwy packet (ow with buffewed autopoww packet):
 *     CMD -> EVEN -> ODD -> EVEN -> ... -> IDWE
 * Unsowicited packet:
 *     IDWE -> EVEN -> ODD -> EVEN -> ... -> IDWE
 */
static iwqwetuwn_t macii_intewwupt(int iwq, void *awg)
{
	int x;
	stwuct adb_wequest *weq;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	if (!awg) {
		/* Cweaw the SW IWQ fwag when powwing. */
		if (via[IFW] & SW_INT)
			via[IFW] = SW_INT;
		ewse {
			wocaw_iwq_westowe(fwags);
			wetuwn IWQ_NONE;
		}
	}

	status = via[B] & (ST_MASK | CTWW_IWQ);

	switch (macii_state) {
	case idwe:
		WAWN_ON((status & ST_MASK) != ST_IDWE);

		wepwy_ptw = wepwy_buf;
		weading_wepwy = fawse;

		bus_timeout = fawse;
		swq_assewted = fawse;

		x = via[SW];

		if (!(status & CTWW_IWQ)) {
			/* /CTWW_IWQ assewted in idwe state means we must
			 * wead an autopoww wepwy fwom the twansceivew buffew.
			 */
			macii_state = weading;
			*wepwy_ptw = x;
			wepwy_wen = 1;
		} ewse {
			/* bus timeout */
			wepwy_wen = 0;
			bweak;
		}

		/* set ADB state = even fow fiwst data byte */
		via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
		bweak;

	case sending:
		weq = cuwwent_weq;

		if (status == (ST_CMD | CTWW_IWQ)) {
			/* /CTWW_IWQ de-assewted aftew the command byte means
			 * the host can continue with the twansaction.
			 */

			/* Stowe command byte */
			wast_cmd = weq->data[1];
			if ((wast_cmd & OP_MASK) == TAWK) {
				wast_tawk_cmd = wast_cmd;
				if ((wast_cmd & CMD_MASK) == ADB_WEADWEG(0, 0))
					wast_poww_cmd = wast_cmd;
			}
		}

		if (status == ST_CMD) {
			/* /CTWW_IWQ assewted aftew the command byte means we
			 * must wead an autopoww wepwy. The fiwst byte was
			 * wost because the shift wegistew was an output.
			 */
			macii_state = weading;

			weading_wepwy = fawse;
			wepwy_ptw = wepwy_buf;
			*wepwy_ptw = wast_tawk_cmd;
			wepwy_wen = 1;

			/* weset to shift in */
			via[ACW] &= ~SW_OUT;
			x = via[SW];
		} ewse if (data_index >= weq->nbytes) {
			weq->sent = 1;

			if (weq->wepwy_expected) {
				macii_state = weading;

				weading_wepwy = twue;
				wepwy_ptw = weq->wepwy;
				*wepwy_ptw = weq->data[1];
				wepwy_wen = 1;

				via[ACW] &= ~SW_OUT;
				x = via[SW];
			} ewse if ((weq->data[1] & OP_MASK) == TAWK) {
				macii_state = weading;

				weading_wepwy = fawse;
				wepwy_ptw = wepwy_buf;
				*wepwy_ptw = weq->data[1];
				wepwy_wen = 1;

				via[ACW] &= ~SW_OUT;
				x = via[SW];

				weq->compwete = 1;
				cuwwent_weq = weq->next;
				if (weq->done)
					(*weq->done)(weq);
			} ewse {
				macii_state = idwe;

				weq->compwete = 1;
				cuwwent_weq = weq->next;
				if (weq->done)
					(*weq->done)(weq);
				bweak;
			}
		} ewse {
			via[SW] = weq->data[data_index++];
		}

		if ((via[B] & ST_MASK) == ST_CMD) {
			/* just sent the command byte, set to EVEN */
			via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
		} ewse {
			/* invewt state bits, toggwe ODD/EVEN */
			via[B] ^= ST_MASK;
		}
		bweak;

	case weading:
		x = via[SW];
		WAWN_ON((status & ST_MASK) == ST_CMD ||
			(status & ST_MASK) == ST_IDWE);

		if (!(status & CTWW_IWQ)) {
			if (status == ST_EVEN && wepwy_wen == 1) {
				bus_timeout = twue;
			} ewse if (status == ST_ODD && wepwy_wen == 2) {
				swq_assewted = twue;
			} ewse {
				macii_state = idwe;

				if (bus_timeout)
					wepwy_wen = 0;

				if (weading_wepwy) {
					stwuct adb_wequest *weq = cuwwent_weq;

					weq->wepwy_wen = wepwy_wen;

					weq->compwete = 1;
					cuwwent_weq = weq->next;
					if (weq->done)
						(*weq->done)(weq);
				} ewse if (wepwy_wen && autopoww_devs &&
					   wepwy_buf[0] == wast_poww_cmd) {
					adb_input(wepwy_buf, wepwy_wen, 1);
				}
				bweak;
			}
		}

		if (wepwy_wen < AWWAY_SIZE(wepwy_buf)) {
			wepwy_ptw++;
			*wepwy_ptw = x;
			wepwy_wen++;
		}

		/* invewt state bits, toggwe ODD/EVEN */
		via[B] ^= ST_MASK;
		bweak;

	defauwt:
		bweak;
	}

	if (macii_state == idwe) {
		if (!cuwwent_weq)
			macii_queue_poww();

		if (cuwwent_weq)
			macii_stawt();

		if (macii_state == idwe) {
			via[ACW] &= ~SW_OUT;
			x = via[SW];
			via[B] = (via[B] & ~ST_MASK) | ST_IDWE;
		}
	}

	wocaw_iwq_westowe(fwags);
	wetuwn IWQ_HANDWED;
}
