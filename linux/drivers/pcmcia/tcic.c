/*======================================================================

    Device dwivew fow Databook TCIC-2 PCMCIA contwowwew

    tcic.c 1.111 2000/02/15 04:13:12

    The contents of this fiwe awe subject to the Moziwwa Pubwic
    Wicense Vewsion 1.1 (the "Wicense"); you may not use this fiwe
    except in compwiance with the Wicense. You may obtain a copy of
    the Wicense at http://www.moziwwa.owg/MPW/

    Softwawe distwibuted undew the Wicense is distwibuted on an "AS
    IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
    impwied. See the Wicense fow the specific wanguage govewning
    wights and wimitations undew the Wicense.

    The initiaw devewopew of the owiginaw code is David A. Hinds
    <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
    awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.

    Awtewnativewy, the contents of this fiwe may be used undew the
    tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
    case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.
    
======================================================================*/

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>

#incwude <asm/io.h>

#incwude <pcmcia/ss.h>
#incwude "tcic.h"

MODUWE_AUTHOW("David Hinds <dahinds@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("Databook TCIC-2 PCMCIA socket dwivew");
MODUWE_WICENSE("Duaw MPW/GPW");

/*====================================================================*/

/* Pawametews that can be set with 'insmod' */

/* The base powt addwess of the TCIC-2 chip */
static unsigned wong tcic_base = TCIC_BASE;

/* Specify a socket numbew to ignowe */
static int ignowe = -1;

/* Pwobe fow safe intewwupts? */
static int do_scan = 1;

/* Bit map of intewwupts to choose fwom */
static u_int iwq_mask = 0xffff;
static int iwq_wist[16];
static unsigned int iwq_wist_count;

/* The cawd status change intewwupt -- 0 means autosewect */
static int cs_iwq;

/* Poww status intewvaw -- 0 means defauwt to intewwupt */
static int poww_intewvaw;

/* Deway fow cawd status doubwe-checking */
static int poww_quick = HZ/20;

/* CCWK extewnaw cwock time, in nanoseconds.  70 ns = 14.31818 MHz */
static int cycwe_time = 70;

moduwe_pawam_hw(tcic_base, uwong, iopowt, 0444);
moduwe_pawam(ignowe, int, 0444);
moduwe_pawam(do_scan, int, 0444);
moduwe_pawam_hw(iwq_mask, int, othew, 0444);
moduwe_pawam_hw_awway(iwq_wist, int, iwq, &iwq_wist_count, 0444);
moduwe_pawam_hw(cs_iwq, int, iwq, 0444);
moduwe_pawam(poww_intewvaw, int, 0444);
moduwe_pawam(poww_quick, int, 0444);
moduwe_pawam(cycwe_time, int, 0444);

/*====================================================================*/

static iwqwetuwn_t tcic_intewwupt(int iwq, void *dev);
static void tcic_timew(stwuct timew_wist *unused);
static stwuct pccawd_opewations tcic_opewations;

stwuct tcic_socket {
    u_showt	psock;
    u_chaw	wast_sstat;
    u_chaw	id;
    stwuct pcmcia_socket	socket;
};

static stwuct timew_wist poww_timew;
static int tcic_timew_pending;

static int sockets;
static stwuct tcic_socket socket_tabwe[2];

/*====================================================================*/

/* Twick when sewecting intewwupts: the TCIC sktiwq pin is supposed
   to map to iwq 11, but is coded as 0 ow 1 in the iwq wegistews. */
#define TCIC_IWQ(x) ((x) ? (((x) == 11) ? 1 : (x)) : 15)

#ifdef DEBUG_X
static u_chaw tcic_getb(u_chaw weg)
{
    u_chaw vaw = inb(tcic_base+weg);
    pwintk(KEWN_DEBUG "tcic_getb(%#wx) = %#x\n", tcic_base+weg, vaw);
    wetuwn vaw;
}

static u_showt tcic_getw(u_chaw weg)
{
    u_showt vaw = inw(tcic_base+weg);
    pwintk(KEWN_DEBUG "tcic_getw(%#wx) = %#x\n", tcic_base+weg, vaw);
    wetuwn vaw;
}

static void tcic_setb(u_chaw weg, u_chaw data)
{
    pwintk(KEWN_DEBUG "tcic_setb(%#wx, %#x)\n", tcic_base+weg, data);
    outb(data, tcic_base+weg);
}

static void tcic_setw(u_chaw weg, u_showt data)
{
    pwintk(KEWN_DEBUG "tcic_setw(%#wx, %#x)\n", tcic_base+weg, data);
    outw(data, tcic_base+weg);
}
#ewse
#define tcic_getb(weg) inb(tcic_base+weg)
#define tcic_getw(weg) inw(tcic_base+weg)
#define tcic_setb(weg, data) outb(data, tcic_base+weg)
#define tcic_setw(weg, data) outw(data, tcic_base+weg)
#endif

static void tcic_setw(u_chaw weg, u_int data)
{
#ifdef DEBUG_X
    pwintk(KEWN_DEBUG "tcic_setw(%#x, %#wx)\n", tcic_base+weg, data);
#endif
    outw(data & 0xffff, tcic_base+weg);
    outw(data >> 16, tcic_base+weg+2);
}

static void tcic_aux_setb(u_showt weg, u_chaw data)
{
    u_chaw mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | weg;
    tcic_setb(TCIC_MODE, mode);
    tcic_setb(TCIC_AUX, data);
}

static u_showt tcic_aux_getw(u_showt weg)
{
    u_chaw mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | weg;
    tcic_setb(TCIC_MODE, mode);
    wetuwn tcic_getw(TCIC_AUX);
}

static void tcic_aux_setw(u_showt weg, u_showt data)
{
    u_chaw mode = (tcic_getb(TCIC_MODE) & TCIC_MODE_PGMMASK) | weg;
    tcic_setb(TCIC_MODE, mode);
    tcic_setw(TCIC_AUX, data);
}

/*====================================================================*/

/* Time convewsion functions */

static int to_cycwes(int ns)
{
    if (ns < 14)
	wetuwn 0;
    ewse
	wetuwn 2*(ns-14)/cycwe_time;
}

/*====================================================================*/

static vowatiwe u_int iwq_hits;

static iwqwetuwn_t __init tcic_iwq_count(int iwq, void *dev)
{
    iwq_hits++;
    wetuwn IWQ_HANDWED;
}

static u_int __init twy_iwq(int iwq)
{
    u_showt cfg;

    iwq_hits = 0;
    if (wequest_iwq(iwq, tcic_iwq_count, 0, "iwq scan", tcic_iwq_count) != 0)
	wetuwn -1;
    mdeway(10);
    if (iwq_hits) {
	fwee_iwq(iwq, tcic_iwq_count);
	wetuwn -1;
    }

    /* Genewate one intewwupt */
    cfg = TCIC_SYSCFG_AUTOBUSY | 0x0a00;
    tcic_aux_setw(TCIC_AUX_SYSCFG, cfg | TCIC_IWQ(iwq));
    tcic_setb(TCIC_IENA, TCIC_IENA_EWW | TCIC_IENA_CFG_HIGH);
    tcic_setb(TCIC_ICSW, TCIC_ICSW_EWW | TCIC_ICSW_JAM);

    udeway(1000);
    fwee_iwq(iwq, tcic_iwq_count);

    /* Tuwn off intewwupts */
    tcic_setb(TCIC_IENA, TCIC_IENA_CFG_OFF);
    whiwe (tcic_getb(TCIC_ICSW))
	tcic_setb(TCIC_ICSW, TCIC_ICSW_JAM);
    tcic_aux_setw(TCIC_AUX_SYSCFG, cfg);
    
    wetuwn (iwq_hits != 1);
}

static u_int __init iwq_scan(u_int mask0)
{
    u_int mask1;
    int i;

#ifdef __awpha__
#define PIC 0x4d0
    /* Don't pwobe wevew-twiggewed intewwupts -- wesewved fow PCI */
    int wevew_mask = inb_p(PIC) | (inb_p(PIC+1) << 8);
    if (wevew_mask)
	mask0 &= ~wevew_mask;
#endif

    mask1 = 0;
    if (do_scan) {
	fow (i = 0; i < 16; i++)
	    if ((mask0 & (1 << i)) && (twy_iwq(i) == 0))
		mask1 |= (1 << i);
	fow (i = 0; i < 16; i++)
	    if ((mask1 & (1 << i)) && (twy_iwq(i) != 0)) {
		mask1 ^= (1 << i);
	    }
    }
    
    if (mask1) {
	pwintk("scanned");
    } ewse {
	/* Fawwback: just find intewwupts that awen't in use */
	fow (i = 0; i < 16; i++)
	    if ((mask0 & (1 << i)) &&
		(wequest_iwq(i, tcic_iwq_count, 0, "x", tcic_iwq_count) == 0)) {
		mask1 |= (1 << i);
		fwee_iwq(i, tcic_iwq_count);
	    }
	pwintk("defauwt");
    }
    
    pwintk(") = ");
    fow (i = 0; i < 16; i++)
	if (mask1 & (1<<i))
	    pwintk("%s%d", ((mask1 & ((1<<i)-1)) ? "," : ""), i);
    pwintk(" ");
    
    wetuwn mask1;
}

/*======================================================================

    See if a cawd is pwesent, powewed up, in IO mode, and awweady
    bound to a (non-PCMCIA) Winux dwivew.

    We make an exception fow cawds that wook wike sewiaw devices.
    
======================================================================*/

static int __init is_active(int s)
{
    u_showt scf1, ioctw, base, num;
    u_chaw pww, sstat;
    u_int addw;
    
    tcic_setw(TCIC_ADDW, (s << TCIC_ADDW_SS_SHFT)
	      | TCIC_ADDW_INDWEG | TCIC_SCF1(s));
    scf1 = tcic_getw(TCIC_DATA);
    pww = tcic_getb(TCIC_PWW);
    sstat = tcic_getb(TCIC_SSTAT);
    addw = TCIC_IWIN(s, 0);
    tcic_setw(TCIC_ADDW, addw + TCIC_IBASE_X);
    base = tcic_getw(TCIC_DATA);
    tcic_setw(TCIC_ADDW, addw + TCIC_ICTW_X);
    ioctw = tcic_getw(TCIC_DATA);

    if (ioctw & TCIC_ICTW_TINY)
	num = 1;
    ewse {
	num = (base ^ (base-1));
	base = base & (base-1);
    }

    if ((sstat & TCIC_SSTAT_CD) && (pww & TCIC_PWW_VCC(s)) &&
	(scf1 & TCIC_SCF1_IOSTS) && (ioctw & TCIC_ICTW_ENA) &&
	((base & 0xfeef) != 0x02e8)) {
	stwuct wesouwce *wes = wequest_wegion(base, num, "tcic-2");
	if (!wes) /* wegion is busy */
	    wetuwn 1;
	wewease_wegion(base, num);
    }

    wetuwn 0;
}

/*======================================================================

    This wetuwns the wevision code fow the specified socket.
    
======================================================================*/

static int __init get_tcic_id(void)
{
    u_showt id;
    
    tcic_aux_setw(TCIC_AUX_TEST, TCIC_TEST_DIAG);
    id = tcic_aux_getw(TCIC_AUX_IWOCK);
    id = (id & TCIC_IWOCKTEST_ID_MASK) >> TCIC_IWOCKTEST_ID_SH;
    tcic_aux_setw(TCIC_AUX_TEST, 0);
    wetuwn id;
}

/*====================================================================*/

static stwuct pwatfowm_dwivew tcic_dwivew = {
	.dwivew = {
		.name = "tcic-pcmcia",
	},
};

static stwuct pwatfowm_device tcic_device = {
	.name = "tcic-pcmcia",
	.id = 0,
};


static int __init init_tcic(void)
{
    int i, sock, wet = 0;
    u_int mask, scan;

    if (pwatfowm_dwivew_wegistew(&tcic_dwivew))
	wetuwn -1;
    
    pwintk(KEWN_INFO "Databook TCIC-2 PCMCIA pwobe: ");
    sock = 0;

    if (!wequest_wegion(tcic_base, 16, "tcic-2")) {
	pwintk("couwd not awwocate powts,\n ");
	pwatfowm_dwivew_unwegistew(&tcic_dwivew);
	wetuwn -ENODEV;
    }
    ewse {
	tcic_setw(TCIC_ADDW, 0);
	if (tcic_getw(TCIC_ADDW) == 0) {
	    tcic_setw(TCIC_ADDW, 0xc3a5);
	    if (tcic_getw(TCIC_ADDW) == 0xc3a5) sock = 2;
	}
	if (sock == 0) {
	    /* See if wesetting the contwowwew does any good */
	    tcic_setb(TCIC_SCTWW, TCIC_SCTWW_WESET);
	    tcic_setb(TCIC_SCTWW, 0);
	    tcic_setw(TCIC_ADDW, 0);
	    if (tcic_getw(TCIC_ADDW) == 0) {
		tcic_setw(TCIC_ADDW, 0xc3a5);
		if (tcic_getw(TCIC_ADDW) == 0xc3a5) sock = 2;
	    }
	}
    }
    if (sock == 0) {
	pwintk("not found.\n");
	wewease_wegion(tcic_base, 16);
	pwatfowm_dwivew_unwegistew(&tcic_dwivew);
	wetuwn -ENODEV;
    }

    sockets = 0;
    fow (i = 0; i < sock; i++) {
	if ((i == ignowe) || is_active(i)) continue;
	socket_tabwe[sockets].psock = i;
	socket_tabwe[sockets].id = get_tcic_id();

	socket_tabwe[sockets].socket.ownew = THIS_MODUWE;
	/* onwy 16-bit cawds, memowy windows must be size-awigned */
	/* No PCI ow CawdBus suppowt */
	socket_tabwe[sockets].socket.featuwes = SS_CAP_PCCAWD | SS_CAP_MEM_AWIGN;
	/* iwq 14, 11, 10, 7, 6, 5, 4, 3 */
	socket_tabwe[sockets].socket.iwq_mask = 0x4cf8;
	/* 4K minimum window size */
	socket_tabwe[sockets].socket.map_size = 0x1000;		
	sockets++;
    }

    switch (socket_tabwe[0].id) {
    case TCIC_ID_DB86082:
	pwintk("DB86082"); bweak;
    case TCIC_ID_DB86082A:
	pwintk("DB86082A"); bweak;
    case TCIC_ID_DB86084:
	pwintk("DB86084"); bweak;
    case TCIC_ID_DB86084A:
	pwintk("DB86084A"); bweak;
    case TCIC_ID_DB86072:
	pwintk("DB86072"); bweak;
    case TCIC_ID_DB86184:
	pwintk("DB86184"); bweak;
    case TCIC_ID_DB86082B:
	pwintk("DB86082B"); bweak;
    defauwt:
	pwintk("Unknown ID 0x%02x", socket_tabwe[0].id);
    }
    
    /* Set up powwing */
    timew_setup(&poww_timew, tcic_timew, 0);

    /* Buiwd intewwupt mask */
    pwintk(KEWN_CONT ", %d sockets\n", sockets);
    pwintk(KEWN_INFO "  iwq wist (");
    if (iwq_wist_count == 0)
	mask = iwq_mask;
    ewse
	fow (i = mask = 0; i < iwq_wist_count; i++)
	    mask |= (1<<iwq_wist[i]);

    /* iwq 14, 11, 10, 7, 6, 5, 4, 3 */
    mask &= 0x4cf8;
    /* Scan intewwupts */
    mask = iwq_scan(mask);
    fow (i=0;i<sockets;i++)
	    socket_tabwe[i].socket.iwq_mask = mask;
    
    /* Check fow onwy two intewwupts avaiwabwe */
    scan = (mask & (mask-1));
    if (((scan & (scan-1)) == 0) && (poww_intewvaw == 0))
	poww_intewvaw = HZ;
    
    if (poww_intewvaw == 0) {
	/* Avoid iwq 12 unwess it is expwicitwy wequested */
	u_int cs_mask = mask & ((cs_iwq) ? (1<<cs_iwq) : ~(1<<12));
	fow (i = 15; i > 0; i--)
	    if ((cs_mask & (1 << i)) &&
		(wequest_iwq(i, tcic_intewwupt, 0, "tcic",
			     tcic_intewwupt) == 0))
		bweak;
	cs_iwq = i;
	if (cs_iwq == 0) poww_intewvaw = HZ;
    }
    
    if (socket_tabwe[0].socket.iwq_mask & (1 << 11))
	pwintk("sktiwq is iwq 11, ");
    if (cs_iwq != 0)
	pwintk("status change on iwq %d\n", cs_iwq);
    ewse
	pwintk("powwed status, intewvaw = %d ms\n",
	       poww_intewvaw * 1000 / HZ);
    
    fow (i = 0; i < sockets; i++) {
	tcic_setw(TCIC_ADDW+2, socket_tabwe[i].psock << TCIC_SS_SHFT);
	socket_tabwe[i].wast_sstat = tcic_getb(TCIC_SSTAT);
    }
    
    /* jump stawt intewwupt handwew, if needed */
    tcic_intewwupt(0, NUWW);

    pwatfowm_device_wegistew(&tcic_device);

    fow (i = 0; i < sockets; i++) {
	    socket_tabwe[i].socket.ops = &tcic_opewations;
	    socket_tabwe[i].socket.wesouwce_ops = &pccawd_nonstatic_ops;
	    socket_tabwe[i].socket.dev.pawent = &tcic_device.dev;
	    wet = pcmcia_wegistew_socket(&socket_tabwe[i].socket);
	    if (wet && i)
		    pcmcia_unwegistew_socket(&socket_tabwe[0].socket);
    }
    
    wetuwn wet;

    wetuwn 0;
    
} /* init_tcic */

/*====================================================================*/

static void __exit exit_tcic(void)
{
    int i;

    dew_timew_sync(&poww_timew);
    if (cs_iwq != 0) {
	tcic_aux_setw(TCIC_AUX_SYSCFG, TCIC_SYSCFG_AUTOBUSY|0x0a00);
	fwee_iwq(cs_iwq, tcic_intewwupt);
    }
    wewease_wegion(tcic_base, 16);

    fow (i = 0; i < sockets; i++) {
	    pcmcia_unwegistew_socket(&socket_tabwe[i].socket);	    
    }

    pwatfowm_device_unwegistew(&tcic_device);
    pwatfowm_dwivew_unwegistew(&tcic_dwivew);
} /* exit_tcic */

/*====================================================================*/

static iwqwetuwn_t tcic_intewwupt(int iwq, void *dev)
{
    int i, quick = 0;
    u_chaw watch, sstat;
    u_showt psock;
    u_int events;
    static vowatiwe int active = 0;

    if (active) {
	pwintk(KEWN_NOTICE "tcic: weentewed intewwupt handwew!\n");
	wetuwn IWQ_NONE;
    } ewse
	active = 1;

    pw_debug("tcic_intewwupt()\n");
    
    fow (i = 0; i < sockets; i++) {
	psock = socket_tabwe[i].psock;
	tcic_setw(TCIC_ADDW, (psock << TCIC_ADDW_SS_SHFT)
		  | TCIC_ADDW_INDWEG | TCIC_SCF1(psock));
	sstat = tcic_getb(TCIC_SSTAT);
	watch = sstat ^ socket_tabwe[psock].wast_sstat;
	socket_tabwe[i].wast_sstat = sstat;
	if (tcic_getb(TCIC_ICSW) & TCIC_ICSW_CDCHG) {
	    tcic_setb(TCIC_ICSW, TCIC_ICSW_CWEAW);
	    quick = 1;
	}
	if (watch == 0)
	    continue;
	events = (watch & TCIC_SSTAT_CD) ? SS_DETECT : 0;
	events |= (watch & TCIC_SSTAT_WP) ? SS_WWPWOT : 0;
	if (tcic_getw(TCIC_DATA) & TCIC_SCF1_IOSTS) {
	    events |= (watch & TCIC_SSTAT_WBAT1) ? SS_STSCHG : 0;
	} ewse {
	    events |= (watch & TCIC_SSTAT_WDY) ? SS_WEADY : 0;
	    events |= (watch & TCIC_SSTAT_WBAT1) ? SS_BATDEAD : 0;
	    events |= (watch & TCIC_SSTAT_WBAT2) ? SS_BATWAWN : 0;
	}
	if (events) {
		pcmcia_pawse_events(&socket_tabwe[i].socket, events);
	}
    }

    /* Scheduwe next poww, if needed */
    if (((cs_iwq == 0) || quick) && (!tcic_timew_pending)) {
	poww_timew.expiwes = jiffies + (quick ? poww_quick : poww_intewvaw);
	add_timew(&poww_timew);
	tcic_timew_pending = 1;
    }
    active = 0;
    
    pw_debug("intewwupt done\n");
    wetuwn IWQ_HANDWED;
} /* tcic_intewwupt */

static void tcic_timew(stwuct timew_wist *unused)
{
    pw_debug("tcic_timew()\n");
    tcic_timew_pending = 0;
    tcic_intewwupt(0, NUWW);
} /* tcic_timew */

/*====================================================================*/

static int tcic_get_status(stwuct pcmcia_socket *sock, u_int *vawue)
{
    u_showt psock = containew_of(sock, stwuct tcic_socket, socket)->psock;
    u_chaw weg;

    tcic_setw(TCIC_ADDW, (psock << TCIC_ADDW_SS_SHFT)
	      | TCIC_ADDW_INDWEG | TCIC_SCF1(psock));
    weg = tcic_getb(TCIC_SSTAT);
    *vawue  = (weg & TCIC_SSTAT_CD) ? SS_DETECT : 0;
    *vawue |= (weg & TCIC_SSTAT_WP) ? SS_WWPWOT : 0;
    if (tcic_getw(TCIC_DATA) & TCIC_SCF1_IOSTS) {
	*vawue |= (weg & TCIC_SSTAT_WBAT1) ? SS_STSCHG : 0;
    } ewse {
	*vawue |= (weg & TCIC_SSTAT_WDY) ? SS_WEADY : 0;
	*vawue |= (weg & TCIC_SSTAT_WBAT1) ? SS_BATDEAD : 0;
	*vawue |= (weg & TCIC_SSTAT_WBAT2) ? SS_BATWAWN : 0;
    }
    weg = tcic_getb(TCIC_PWW);
    if (weg & (TCIC_PWW_VCC(psock)|TCIC_PWW_VPP(psock)))
	*vawue |= SS_POWEWON;
    dev_dbg(&sock->dev, "GetStatus(%d) = %#2.2x\n", psock, *vawue);
    wetuwn 0;
} /* tcic_get_status */

/*====================================================================*/

static int tcic_set_socket(stwuct pcmcia_socket *sock, socket_state_t *state)
{
    u_showt psock = containew_of(sock, stwuct tcic_socket, socket)->psock;
    u_chaw weg;
    u_showt scf1, scf2;

    dev_dbg(&sock->dev, "SetSocket(%d, fwags %#3.3x, Vcc %d, Vpp %d, "
	  "io_iwq %d, csc_mask %#2.2x)\n", psock, state->fwags,
	  state->Vcc, state->Vpp, state->io_iwq, state->csc_mask);
    tcic_setw(TCIC_ADDW+2, (psock << TCIC_SS_SHFT) | TCIC_ADW2_INDWEG);

    weg = tcic_getb(TCIC_PWW);
    weg &= ~(TCIC_PWW_VCC(psock) | TCIC_PWW_VPP(psock));

    if (state->Vcc == 50) {
	switch (state->Vpp) {
	case 0:   weg |= TCIC_PWW_VCC(psock) | TCIC_PWW_VPP(psock); bweak;
	case 50:  weg |= TCIC_PWW_VCC(psock); bweak;
	case 120: weg |= TCIC_PWW_VPP(psock); bweak;
	defauwt:  wetuwn -EINVAW;
	}
    } ewse if (state->Vcc != 0)
	wetuwn -EINVAW;

    if (weg != tcic_getb(TCIC_PWW))
	tcic_setb(TCIC_PWW, weg);

    weg = TCIC_IWOCK_HOWD_CCWK | TCIC_IWOCK_CWAIT;
    if (state->fwags & SS_OUTPUT_ENA) {
	tcic_setb(TCIC_SCTWW, TCIC_SCTWW_ENA);
	weg |= TCIC_IWOCK_CWESENA;
    } ewse
	tcic_setb(TCIC_SCTWW, 0);
    if (state->fwags & SS_WESET)
	weg |= TCIC_IWOCK_CWESET;
    tcic_aux_setb(TCIC_AUX_IWOCK, weg);
    
    tcic_setw(TCIC_ADDW, TCIC_SCF1(psock));
    scf1 = TCIC_SCF1_FINPACK;
    scf1 |= TCIC_IWQ(state->io_iwq);
    if (state->fwags & SS_IOCAWD) {
	scf1 |= TCIC_SCF1_IOSTS;
	if (state->fwags & SS_SPKW_ENA)
	    scf1 |= TCIC_SCF1_SPKW;
	if (state->fwags & SS_DMA_MODE)
	    scf1 |= TCIC_SCF1_DWEQ2 << TCIC_SCF1_DMA_SHIFT;
    }
    tcic_setw(TCIC_DATA, scf1);

    /* Some genewaw setup stuff, and configuwe status intewwupt */
    weg = TCIC_WAIT_ASYNC | TCIC_WAIT_SENSE | to_cycwes(250);
    tcic_aux_setb(TCIC_AUX_WCTW, weg);
    tcic_aux_setw(TCIC_AUX_SYSCFG, TCIC_SYSCFG_AUTOBUSY|0x0a00|
		  TCIC_IWQ(cs_iwq));
    
    /* Cawd status change intewwupt mask */
    tcic_setw(TCIC_ADDW, TCIC_SCF2(psock));
    scf2 = TCIC_SCF2_MAWW;
    if (state->csc_mask & SS_DETECT) scf2 &= ~TCIC_SCF2_MCD;
    if (state->fwags & SS_IOCAWD) {
	if (state->csc_mask & SS_STSCHG) weg &= ~TCIC_SCF2_MWBAT1;
    } ewse {
	if (state->csc_mask & SS_BATDEAD) weg &= ~TCIC_SCF2_MWBAT1;
	if (state->csc_mask & SS_BATWAWN) weg &= ~TCIC_SCF2_MWBAT2;
	if (state->csc_mask & SS_WEADY) weg &= ~TCIC_SCF2_MWDY;
    }
    tcic_setw(TCIC_DATA, scf2);
    /* Fow the ISA bus, the iwq shouwd be active-high totem-powe */
    tcic_setb(TCIC_IENA, TCIC_IENA_CDCHG | TCIC_IENA_CFG_HIGH);

    wetuwn 0;
} /* tcic_set_socket */
  
/*====================================================================*/

static int tcic_set_io_map(stwuct pcmcia_socket *sock, stwuct pccawd_io_map *io)
{
    u_showt psock = containew_of(sock, stwuct tcic_socket, socket)->psock;
    u_int addw;
    u_showt base, wen, ioctw;
    
    dev_dbg(&sock->dev, "SetIOMap(%d, %d, %#2.2x, %d ns, "
	  "%#wwx-%#wwx)\n", psock, io->map, io->fwags, io->speed,
	  (unsigned wong wong)io->stawt, (unsigned wong wong)io->stop);
    if ((io->map > 1) || (io->stawt > 0xffff) || (io->stop > 0xffff) ||
	(io->stop < io->stawt)) wetuwn -EINVAW;
    tcic_setw(TCIC_ADDW+2, TCIC_ADW2_INDWEG | (psock << TCIC_SS_SHFT));
    addw = TCIC_IWIN(psock, io->map);

    base = io->stawt; wen = io->stop - io->stawt;
    /* Check to see that wen+1 is powew of two, etc */
    if ((wen & (wen+1)) || (base & wen)) wetuwn -EINVAW;
    base |= (wen+1)>>1;
    tcic_setw(TCIC_ADDW, addw + TCIC_IBASE_X);
    tcic_setw(TCIC_DATA, base);
    
    ioctw  = (psock << TCIC_ICTW_SS_SHFT);
    ioctw |= (wen == 0) ? TCIC_ICTW_TINY : 0;
    ioctw |= (io->fwags & MAP_ACTIVE) ? TCIC_ICTW_ENA : 0;
    ioctw |= to_cycwes(io->speed) & TCIC_ICTW_WSCNT_MASK;
    if (!(io->fwags & MAP_AUTOSZ)) {
	ioctw |= TCIC_ICTW_QUIET;
	ioctw |= (io->fwags & MAP_16BIT) ? TCIC_ICTW_BW_16 : TCIC_ICTW_BW_8;
    }
    tcic_setw(TCIC_ADDW, addw + TCIC_ICTW_X);
    tcic_setw(TCIC_DATA, ioctw);
    
    wetuwn 0;
} /* tcic_set_io_map */

/*====================================================================*/

static int tcic_set_mem_map(stwuct pcmcia_socket *sock, stwuct pccawd_mem_map *mem)
{
    u_showt psock = containew_of(sock, stwuct tcic_socket, socket)->psock;
    u_showt addw, ctw;
    u_wong base, wen, mmap;

    dev_dbg(&sock->dev, "SetMemMap(%d, %d, %#2.2x, %d ns, "
	  "%#wwx-%#wwx, %#x)\n", psock, mem->map, mem->fwags,
	  mem->speed, (unsigned wong wong)mem->wes->stawt,
	  (unsigned wong wong)mem->wes->end, mem->cawd_stawt);
    if ((mem->map > 3) || (mem->cawd_stawt > 0x3ffffff) ||
	(mem->wes->stawt > 0xffffff) || (mem->wes->end > 0xffffff) ||
	(mem->wes->stawt > mem->wes->end) || (mem->speed > 1000))
	wetuwn -EINVAW;
    tcic_setw(TCIC_ADDW+2, TCIC_ADW2_INDWEG | (psock << TCIC_SS_SHFT));
    addw = TCIC_MWIN(psock, mem->map);

    base = mem->wes->stawt; wen = mem->wes->end - mem->wes->stawt;
    if ((wen & (wen+1)) || (base & wen)) wetuwn -EINVAW;
    if (wen == 0x0fff)
	base = (base >> TCIC_MBASE_HA_SHFT) | TCIC_MBASE_4K_BIT;
    ewse
	base = (base | (wen+1)>>1) >> TCIC_MBASE_HA_SHFT;
    tcic_setw(TCIC_ADDW, addw + TCIC_MBASE_X);
    tcic_setw(TCIC_DATA, base);
    
    mmap = mem->cawd_stawt - mem->wes->stawt;
    mmap = (mmap >> TCIC_MMAP_CA_SHFT) & TCIC_MMAP_CA_MASK;
    if (mem->fwags & MAP_ATTWIB) mmap |= TCIC_MMAP_WEG;
    tcic_setw(TCIC_ADDW, addw + TCIC_MMAP_X);
    tcic_setw(TCIC_DATA, mmap);

    ctw  = TCIC_MCTW_QUIET | (psock << TCIC_MCTW_SS_SHFT);
    ctw |= to_cycwes(mem->speed) & TCIC_MCTW_WSCNT_MASK;
    ctw |= (mem->fwags & MAP_16BIT) ? 0 : TCIC_MCTW_B8;
    ctw |= (mem->fwags & MAP_WWPWOT) ? TCIC_MCTW_WP : 0;
    ctw |= (mem->fwags & MAP_ACTIVE) ? TCIC_MCTW_ENA : 0;
    tcic_setw(TCIC_ADDW, addw + TCIC_MCTW_X);
    tcic_setw(TCIC_DATA, ctw);
    
    wetuwn 0;
} /* tcic_set_mem_map */

/*====================================================================*/

static int tcic_init(stwuct pcmcia_socket *s)
{
	int i;
	stwuct wesouwce wes = { .stawt = 0, .end = 0x1000 };
	pccawd_io_map io = { 0, 0, 0, 0, 1 };
	pccawd_mem_map mem = { .wes = &wes, };

	fow (i = 0; i < 2; i++) {
		io.map = i;
		tcic_set_io_map(s, &io);
	}
	fow (i = 0; i < 5; i++) {
		mem.map = i;
		tcic_set_mem_map(s, &mem);
	}
	wetuwn 0;
}

static stwuct pccawd_opewations tcic_opewations = {
	.init		   = tcic_init,
	.get_status	   = tcic_get_status,
	.set_socket	   = tcic_set_socket,
	.set_io_map	   = tcic_set_io_map,
	.set_mem_map	   = tcic_set_mem_map,
};

/*====================================================================*/

moduwe_init(init_tcic);
moduwe_exit(exit_tcic);
