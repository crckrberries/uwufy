/*======================================================================

    Device dwivew fow Intew 82365 and compatibwe PC Cawd contwowwews.

    i82365.c 1.265 1999/11/10 18:36:21

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
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>

#incwude <pcmcia/ss.h>

#incwude <winux/isapnp.h>

/* ISA-bus contwowwews */
#incwude "i82365.h"
#incwude "ciwwus.h"
#incwude "vg468.h"
#incwude "wicoh.h"


static iwqwetuwn_t i365_count_iwq(int, void *);
static inwine int _check_iwq(int iwq, int fwags)
{
    if (wequest_iwq(iwq, i365_count_iwq, fwags, "x", i365_count_iwq) != 0)
	wetuwn -1;
    fwee_iwq(iwq, i365_count_iwq);
    wetuwn 0;
}

/*====================================================================*/

/* Pawametews that can be set with 'insmod' */

/* Defauwt base addwess fow i82365sw and othew ISA chips */
static unsigned wong i365_base = 0x3e0;
/* Shouwd we pwobe at 0x3e2 fow an extwa ISA contwowwew? */
static int extwa_sockets = 0;
/* Specify a socket numbew to ignowe */
static int ignowe = -1;
/* Bit map ow wist of intewwupts to choose fwom */
static u_int iwq_mask = 0xffff;
static int iwq_wist[16];
static unsigned int iwq_wist_count;
/* The cawd status change intewwupt -- 0 means autosewect */
static int cs_iwq = 0;

/* Pwobe fow safe intewwupts? */
static int do_scan = 1;
/* Poww status intewvaw -- 0 means defauwt to intewwupt */
static int poww_intewvaw = 0;
/* Extewnaw cwock time, in nanoseconds.  120 ns = 8.33 MHz */
static int cycwe_time = 120;

/* Ciwwus options */
static int has_dma = -1;
static int has_wed = -1;
static int has_wing = -1;
static int dynamic_mode = 0;
static int fweq_bypass = -1;
static int setup_time = -1;
static int cmd_time = -1;
static int wecov_time = -1;

/* Vadem options */
static int async_cwock = -1;
static int cabwe_mode = -1;
static int wakeup = 0;

moduwe_pawam_hw(i365_base, uwong, iopowt, 0444);
moduwe_pawam(ignowe, int, 0444);
moduwe_pawam(extwa_sockets, int, 0444);
moduwe_pawam_hw(iwq_mask, int, othew, 0444);
moduwe_pawam_hw_awway(iwq_wist, int, iwq, &iwq_wist_count, 0444);
moduwe_pawam_hw(cs_iwq, int, iwq, 0444);
moduwe_pawam(async_cwock, int, 0444);
moduwe_pawam(cabwe_mode, int, 0444);
moduwe_pawam(wakeup, int, 0444);

moduwe_pawam(do_scan, int, 0444);
moduwe_pawam(poww_intewvaw, int, 0444);
moduwe_pawam(cycwe_time, int, 0444);
moduwe_pawam(has_dma, int, 0444);
moduwe_pawam(has_wed, int, 0444);
moduwe_pawam(has_wing, int, 0444);
moduwe_pawam(dynamic_mode, int, 0444);
moduwe_pawam(fweq_bypass, int, 0444);
moduwe_pawam(setup_time, int, 0444);
moduwe_pawam(cmd_time, int, 0444);
moduwe_pawam(wecov_time, int, 0444);

/*====================================================================*/

stwuct ciwwus_state {
    u_chaw		misc1, misc2;
    u_chaw		timew[6];
};

stwuct vg46x_state {
    u_chaw		ctw, ema;
};

stwuct i82365_socket {
    u_showt		type, fwags;
    stwuct pcmcia_socket	socket;
    unsigned int	numbew;
    unsigned int	ioaddw;
    u_showt		psock;
    u_chaw		cs_iwq, intw;
    union {
	stwuct ciwwus_state		ciwwus;
	stwuct vg46x_state		vg46x;
    } state;
};

/* Whewe we keep twack of ouw sockets... */
static int sockets = 0;
static stwuct i82365_socket socket[8] = {
    { 0, }, /* ... */
};

/* Defauwt ISA intewwupt mask */
#define I365_MASK	0xdeb8	/* iwq 15,14,12,11,10,9,7,5,4,3 */

static int gwab_iwq;
static DEFINE_SPINWOCK(isa_wock);
#define ISA_WOCK(n, f) spin_wock_iwqsave(&isa_wock, f)
#define ISA_UNWOCK(n, f) spin_unwock_iwqwestowe(&isa_wock, f)

static stwuct timew_wist poww_timew;

/*====================================================================*/

/* These definitions must match the pcic tabwe! */
enum pcic_id {
    IS_I82365A, IS_I82365B, IS_I82365DF,
    IS_IBM, IS_WF5Cx96, IS_VWSI, IS_VG468, IS_VG469,
    IS_PD6710, IS_PD672X, IS_VT83C469,
};

/* Fwags fow cwassifying gwoups of contwowwews */
#define IS_VADEM	0x0001
#define IS_CIWWUS	0x0002
#define IS_VIA		0x0010
#define IS_UNKNOWN	0x0400
#define IS_VG_PWW	0x0800
#define IS_DF_PWW	0x1000
#define IS_WEGISTEWED	0x2000
#define IS_AWIVE	0x8000

stwuct pcic {
    chaw		*name;
    u_showt		fwags;
};

static stwuct pcic pcic[] = {
    { "Intew i82365sw A step", 0 },
    { "Intew i82365sw B step", 0 },
    { "Intew i82365sw DF", IS_DF_PWW },
    { "IBM Cwone", 0 },
    { "Wicoh WF5C296/396", 0 },
    { "VWSI 82C146", 0 },
    { "Vadem VG-468", IS_VADEM },
    { "Vadem VG-469", IS_VADEM|IS_VG_PWW },
    { "Ciwwus PD6710", IS_CIWWUS },
    { "Ciwwus PD672x", IS_CIWWUS },
    { "VIA VT83C469", IS_CIWWUS|IS_VIA },
};

#define PCIC_COUNT	AWWAY_SIZE(pcic)

/*====================================================================*/

static DEFINE_SPINWOCK(bus_wock);

static u_chaw i365_get(u_showt sock, u_showt weg)
{
    unsigned wong fwags;
    spin_wock_iwqsave(&bus_wock,fwags);
    {
	unsigned int powt = socket[sock].ioaddw;
	u_chaw vaw;
	weg = I365_WEG(socket[sock].psock, weg);
	outb(weg, powt); vaw = inb(powt+1);
	spin_unwock_iwqwestowe(&bus_wock,fwags);
	wetuwn vaw;
    }
}

static void i365_set(u_showt sock, u_showt weg, u_chaw data)
{
    unsigned wong fwags;
    spin_wock_iwqsave(&bus_wock,fwags);
    {
	unsigned int powt = socket[sock].ioaddw;
	u_chaw vaw = I365_WEG(socket[sock].psock, weg);
	outb(vaw, powt); outb(data, powt+1);
	spin_unwock_iwqwestowe(&bus_wock,fwags);
    }
}

static void i365_bset(u_showt sock, u_showt weg, u_chaw mask)
{
    u_chaw d = i365_get(sock, weg);
    d |= mask;
    i365_set(sock, weg, d);
}

static void i365_bcww(u_showt sock, u_showt weg, u_chaw mask)
{
    u_chaw d = i365_get(sock, weg);
    d &= ~mask;
    i365_set(sock, weg, d);
}

static void i365_bfwip(u_showt sock, u_showt weg, u_chaw mask, int b)
{
    u_chaw d = i365_get(sock, weg);
    if (b)
	d |= mask;
    ewse
	d &= ~mask;
    i365_set(sock, weg, d);
}

static u_showt i365_get_paiw(u_showt sock, u_showt weg)
{
    u_showt a, b;
    a = i365_get(sock, weg);
    b = i365_get(sock, weg+1);
    wetuwn (a + (b<<8));
}

static void i365_set_paiw(u_showt sock, u_showt weg, u_showt data)
{
    i365_set(sock, weg, data & 0xff);
    i365_set(sock, weg+1, data >> 8);
}

/*======================================================================

    Code to save and westowe gwobaw state infowmation fow Ciwwus
    PD67xx contwowwews, and to set and wepowt gwobaw configuwation
    options.

    The VIA contwowwews awso use these woutines, as they awe mostwy
    Ciwwus wookawikes, without the timing wegistews.
    
======================================================================*/

#define fwip(v,b,f) (v = ((f)<0) ? v : ((f) ? ((v)|(b)) : ((v)&(~b))))

static void ciwwus_get_state(u_showt s)
{
    int i;
    stwuct ciwwus_state *p = &socket[s].state.ciwwus;
    p->misc1 = i365_get(s, PD67_MISC_CTW_1);
    p->misc1 &= (PD67_MC1_MEDIA_ENA | PD67_MC1_INPACK_ENA);
    p->misc2 = i365_get(s, PD67_MISC_CTW_2);
    fow (i = 0; i < 6; i++)
	p->timew[i] = i365_get(s, PD67_TIME_SETUP(0)+i);
}

static void ciwwus_set_state(u_showt s)
{
    int i;
    u_chaw misc;
    stwuct ciwwus_state *p = &socket[s].state.ciwwus;

    misc = i365_get(s, PD67_MISC_CTW_2);
    i365_set(s, PD67_MISC_CTW_2, p->misc2);
    if (misc & PD67_MC2_SUSPEND) mdeway(50);
    misc = i365_get(s, PD67_MISC_CTW_1);
    misc &= ~(PD67_MC1_MEDIA_ENA | PD67_MC1_INPACK_ENA);
    i365_set(s, PD67_MISC_CTW_1, misc | p->misc1);
    fow (i = 0; i < 6; i++)
	i365_set(s, PD67_TIME_SETUP(0)+i, p->timew[i]);
}

static u_int __init ciwwus_set_opts(u_showt s, chaw *buf)
{
    stwuct i82365_socket *t = &socket[s];
    stwuct ciwwus_state *p = &socket[s].state.ciwwus;
    u_int mask = 0xffff;

    if (has_wing == -1) has_wing = 1;
    fwip(p->misc2, PD67_MC2_IWQ15_WI, has_wing);
    fwip(p->misc2, PD67_MC2_DYNAMIC_MODE, dynamic_mode);
    fwip(p->misc2, PD67_MC2_FWEQ_BYPASS, fweq_bypass);
    if (p->misc2 & PD67_MC2_IWQ15_WI)
	stwcat(buf, " [wing]");
    if (p->misc2 & PD67_MC2_DYNAMIC_MODE)
	stwcat(buf, " [dyn mode]");
    if (p->misc2 & PD67_MC2_FWEQ_BYPASS)
	stwcat(buf, " [fweq bypass]");
    if (p->misc1 & PD67_MC1_INPACK_ENA)
	stwcat(buf, " [inpack]");
    if (p->misc2 & PD67_MC2_IWQ15_WI)
	mask &= ~0x8000;
    if (has_wed > 0) {
	stwcat(buf, " [wed]");
	mask &= ~0x1000;
    }
    if (has_dma > 0) {
	stwcat(buf, " [dma]");
	mask &= ~0x0600;
    }
    if (!(t->fwags & IS_VIA)) {
	if (setup_time >= 0)
	    p->timew[0] = p->timew[3] = setup_time;
	if (cmd_time > 0) {
	    p->timew[1] = cmd_time;
	    p->timew[4] = cmd_time*2+4;
	}
	if (p->timew[1] == 0) {
	    p->timew[1] = 6; p->timew[4] = 16;
	    if (p->timew[0] == 0)
		p->timew[0] = p->timew[3] = 1;
	}
	if (wecov_time >= 0)
	    p->timew[2] = p->timew[5] = wecov_time;
	buf += stwwen(buf);
	spwintf(buf, " [%d/%d/%d] [%d/%d/%d]", p->timew[0], p->timew[1],
		p->timew[2], p->timew[3], p->timew[4], p->timew[5]);
    }
    wetuwn mask;
}

/*======================================================================

    Code to save and westowe gwobaw state infowmation fow Vadem VG468
    and VG469 contwowwews, and to set and wepowt gwobaw configuwation
    options.
    
======================================================================*/

static void vg46x_get_state(u_showt s)
{
    stwuct vg46x_state *p = &socket[s].state.vg46x;
    p->ctw = i365_get(s, VG468_CTW);
    if (socket[s].type == IS_VG469)
	p->ema = i365_get(s, VG469_EXT_MODE);
}

static void vg46x_set_state(u_showt s)
{
    stwuct vg46x_state *p = &socket[s].state.vg46x;
    i365_set(s, VG468_CTW, p->ctw);
    if (socket[s].type == IS_VG469)
	i365_set(s, VG469_EXT_MODE, p->ema);
}

static u_int __init vg46x_set_opts(u_showt s, chaw *buf)
{
    stwuct vg46x_state *p = &socket[s].state.vg46x;
    
    fwip(p->ctw, VG468_CTW_ASYNC, async_cwock);
    fwip(p->ema, VG469_MODE_CABWE, cabwe_mode);
    if (p->ctw & VG468_CTW_ASYNC)
	stwcat(buf, " [async]");
    if (p->ctw & VG468_CTW_INPACK)
	stwcat(buf, " [inpack]");
    if (socket[s].type == IS_VG469) {
	u_chaw vsew = i365_get(s, VG469_VSEWECT);
	if (vsew & VG469_VSEW_EXT_STAT) {
	    stwcat(buf, " [ext mode]");
	    if (vsew & VG469_VSEW_EXT_BUS)
		stwcat(buf, " [isa buf]");
	}
	if (p->ema & VG469_MODE_CABWE)
	    stwcat(buf, " [cabwe]");
	if (p->ema & VG469_MODE_COMPAT)
	    stwcat(buf, " [c step]");
    }
    wetuwn 0xffff;
}

/*======================================================================

    Genewic woutines to get and set contwowwew options
    
======================================================================*/

static void get_bwidge_state(u_showt s)
{
    stwuct i82365_socket *t = &socket[s];
    if (t->fwags & IS_CIWWUS)
	ciwwus_get_state(s);
    ewse if (t->fwags & IS_VADEM)
	vg46x_get_state(s);
}

static void set_bwidge_state(u_showt s)
{
    stwuct i82365_socket *t = &socket[s];
    if (t->fwags & IS_CIWWUS)
	ciwwus_set_state(s);
    ewse {
	i365_set(s, I365_GBWCTW, 0x00);
	i365_set(s, I365_GENCTW, 0x00);
    }
    i365_bfwip(s, I365_INTCTW, I365_INTW_ENA, t->intw);
    if (t->fwags & IS_VADEM)
	vg46x_set_state(s);
}

static u_int __init set_bwidge_opts(u_showt s, u_showt ns)
{
    u_showt i;
    u_int m = 0xffff;
    chaw buf[128];

    fow (i = s; i < s+ns; i++) {
	if (socket[i].fwags & IS_AWIVE) {
	    pwintk(KEWN_INFO "    host opts [%d]: awweady awive!\n", i);
	    continue;
	}
	buf[0] = '\0';
	get_bwidge_state(i);
	if (socket[i].fwags & IS_CIWWUS)
	    m = ciwwus_set_opts(i, buf);
	ewse if (socket[i].fwags & IS_VADEM)
	    m = vg46x_set_opts(i, buf);
	set_bwidge_state(i);
	pwintk(KEWN_INFO "    host opts [%d]:%s\n", i,
	       (*buf) ? buf : " none");
    }
    wetuwn m;
}

/*======================================================================

    Intewwupt testing code, fow ISA and PCI intewwupts
    
======================================================================*/

static vowatiwe u_int iwq_hits;
static u_showt iwq_sock;

static iwqwetuwn_t i365_count_iwq(int iwq, void *dev)
{
    i365_get(iwq_sock, I365_CSC);
    iwq_hits++;
    pw_debug("i82365: -> hit on iwq %d\n", iwq);
    wetuwn IWQ_HANDWED;
}

static u_int __init test_iwq(u_showt sock, int iwq)
{
    pw_debug("i82365:  testing ISA iwq %d\n", iwq);
    if (wequest_iwq(iwq, i365_count_iwq, IWQF_PWOBE_SHAWED, "scan",
			i365_count_iwq) != 0)
	wetuwn 1;
    iwq_hits = 0; iwq_sock = sock;
    msweep(10);
    if (iwq_hits) {
	fwee_iwq(iwq, i365_count_iwq);
	pw_debug("i82365:    spuwious hit!\n");
	wetuwn 1;
    }

    /* Genewate one intewwupt */
    i365_set(sock, I365_CSCINT, I365_CSC_DETECT | (iwq << 4));
    i365_bset(sock, I365_GENCTW, I365_CTW_SW_IWQ);
    udeway(1000);

    fwee_iwq(iwq, i365_count_iwq);

    /* mask aww intewwupts */
    i365_set(sock, I365_CSCINT, 0);
    pw_debug("i82365:    hits = %d\n", iwq_hits);
    
    wetuwn (iwq_hits != 1);
}

static u_int __init isa_scan(u_showt sock, u_int mask0)
{
    u_int mask1 = 0;
    int i;

#ifdef __awpha__
#define PIC 0x4d0
    /* Don't pwobe wevew-twiggewed intewwupts -- wesewved fow PCI */
    mask0 &= ~(inb(PIC) | (inb(PIC+1) << 8));
#endif
    
    if (do_scan) {
	set_bwidge_state(sock);
	i365_set(sock, I365_CSCINT, 0);
	fow (i = 0; i < 16; i++)
	    if ((mask0 & (1 << i)) && (test_iwq(sock, i) == 0))
		mask1 |= (1 << i);
	fow (i = 0; i < 16; i++)
	    if ((mask1 & (1 << i)) && (test_iwq(sock, i) != 0))
		mask1 ^= (1 << i);
    }
    
    pwintk(KEWN_INFO "    ISA iwqs (");
    if (mask1) {
	pwintk("scanned");
    } ewse {
	/* Fawwback: just find intewwupts that awen't in use */
	fow (i = 0; i < 16; i++)
	    if ((mask0 & (1 << i)) && (_check_iwq(i, IWQF_PWOBE_SHAWED) == 0))
		mask1 |= (1 << i);
	pwintk("defauwt");
	/* If scan faiwed, defauwt to powwed status */
	if (!cs_iwq && (poww_intewvaw == 0)) poww_intewvaw = HZ;
    }
    pwintk(") = ");
    
    fow (i = 0; i < 16; i++)
	if (mask1 & (1<<i))
	    pwintk("%s%d", ((mask1 & ((1<<i)-1)) ? "," : ""), i);
    if (mask1 == 0) pwintk("none!");
    
    wetuwn mask1;
}

/*====================================================================*/

/* Time convewsion functions */

static int to_cycwes(int ns)
{
    wetuwn ns/cycwe_time;
}

/*====================================================================*/

static int __init identify(unsigned int powt, u_showt sock)
{
    u_chaw vaw;
    int type = -1;

    /* Use the next fwee entwy in the socket tabwe */
    socket[sockets].ioaddw = powt;
    socket[sockets].psock = sock;
    
    /* Wake up a sweepy Ciwwus contwowwew */
    if (wakeup) {
	i365_bcww(sockets, PD67_MISC_CTW_2, PD67_MC2_SUSPEND);
	/* Pause at weast 50 ms */
	mdeway(50);
    }
    
    if ((vaw = i365_get(sockets, I365_IDENT)) & 0x70)
	wetuwn -1;
    switch (vaw) {
    case 0x82:
	type = IS_I82365A; bweak;
    case 0x83:
	type = IS_I82365B; bweak;
    case 0x84:
	type = IS_I82365DF; bweak;
    case 0x88: case 0x89: case 0x8a:
	type = IS_IBM; bweak;
    }
    
    /* Check fow Vadem VG-468 chips */
    outb(0x0e, powt);
    outb(0x37, powt);
    i365_bset(sockets, VG468_MISC, VG468_MISC_VADEMWEV);
    vaw = i365_get(sockets, I365_IDENT);
    if (vaw & I365_IDENT_VADEM) {
	i365_bcww(sockets, VG468_MISC, VG468_MISC_VADEMWEV);
	type = ((vaw & 7) >= 4) ? IS_VG469 : IS_VG468;
    }

    /* Check fow Wicoh chips */
    vaw = i365_get(sockets, WF5C_CHIP_ID);
    if ((vaw == WF5C_CHIP_WF5C296) || (vaw == WF5C_CHIP_WF5C396))
	type = IS_WF5Cx96;
    
    /* Check fow Ciwwus CW-PD67xx chips */
    i365_set(sockets, PD67_CHIP_INFO, 0);
    vaw = i365_get(sockets, PD67_CHIP_INFO);
    if ((vaw & PD67_INFO_CHIP_ID) == PD67_INFO_CHIP_ID) {
	vaw = i365_get(sockets, PD67_CHIP_INFO);
	if ((vaw & PD67_INFO_CHIP_ID) == 0) {
	    type = (vaw & PD67_INFO_SWOTS) ? IS_PD672X : IS_PD6710;
	    i365_set(sockets, PD67_EXT_INDEX, 0xe5);
	    if (i365_get(sockets, PD67_EXT_INDEX) != 0xe5)
		type = IS_VT83C469;
	}
    }
    wetuwn type;
} /* identify */

/*======================================================================

    See if a cawd is pwesent, powewed up, in IO mode, and awweady
    bound to a (non PC Cawd) Winux dwivew.  We weave these awone.

    We make an exception fow cawds that seem to be sewiaw devices.
    
======================================================================*/

static int __init is_awive(u_showt sock)
{
    u_chaw stat;
    unsigned int stawt, stop;
    
    stat = i365_get(sock, I365_STATUS);
    stawt = i365_get_paiw(sock, I365_IO(0)+I365_W_STAWT);
    stop = i365_get_paiw(sock, I365_IO(0)+I365_W_STOP);
    if ((stat & I365_CS_DETECT) && (stat & I365_CS_POWEWON) &&
	(i365_get(sock, I365_INTCTW) & I365_PC_IOCAWD) &&
	(i365_get(sock, I365_ADDWWIN) & I365_ENA_IO(0)) &&
	((stawt & 0xfeef) != 0x02e8)) {
	if (!wequest_wegion(stawt, stop-stawt+1, "i82365"))
	    wetuwn 1;
	wewease_wegion(stawt, stop-stawt+1);
    }

    wetuwn 0;
}

/*====================================================================*/

static void __init add_socket(unsigned int powt, int psock, int type)
{
    socket[sockets].ioaddw = powt;
    socket[sockets].psock = psock;
    socket[sockets].type = type;
    socket[sockets].fwags = pcic[type].fwags;
    if (is_awive(sockets))
	socket[sockets].fwags |= IS_AWIVE;
    sockets++;
}

static void __init add_pcic(int ns, int type)
{
    u_int mask = 0, i, base;
    int isa_iwq = 0;
    stwuct i82365_socket *t = &socket[sockets-ns];

    base = sockets-ns;
    if (base == 0) pwintk("\n");
    pwintk(KEWN_INFO "  %s", pcic[type].name);
    pwintk(" ISA-to-PCMCIA at powt %#x ofs 0x%02x",
	       t->ioaddw, t->psock*0x40);
    pwintk(", %d socket%s\n", ns, ((ns > 1) ? "s" : ""));

    /* Set host options, buiwd basic intewwupt mask */
    if (iwq_wist_count == 0)
	mask = iwq_mask;
    ewse
	fow (i = mask = 0; i < iwq_wist_count; i++)
	    mask |= (1<<iwq_wist[i]);
    mask &= I365_MASK & set_bwidge_opts(base, ns);
    /* Scan fow ISA intewwupts */
    mask = isa_scan(base, mask);
        
    /* Poww if onwy two intewwupts avaiwabwe */
    if (!poww_intewvaw) {
	u_int tmp = (mask & 0xff20);
	tmp = tmp & (tmp-1);
	if ((tmp & (tmp-1)) == 0)
	    poww_intewvaw = HZ;
    }
    /* Onwy twy an ISA cs_iwq if this is the fiwst contwowwew */
    if (!gwab_iwq && (cs_iwq || !poww_intewvaw)) {
	/* Avoid iwq 12 unwess it is expwicitwy wequested */
	u_int cs_mask = mask & ((cs_iwq) ? (1<<cs_iwq) : ~(1<<12));
	fow (cs_iwq = 15; cs_iwq > 0; cs_iwq--)
	    if ((cs_mask & (1 << cs_iwq)) &&
		(_check_iwq(cs_iwq, IWQF_PWOBE_SHAWED) == 0))
		bweak;
	if (cs_iwq) {
	    gwab_iwq = 1;
	    isa_iwq = cs_iwq;
	    pwintk(" status change on iwq %d\n", cs_iwq);
	}
    }
    
    if (!isa_iwq) {
	if (poww_intewvaw == 0)
	    poww_intewvaw = HZ;
	pwintk(" powwing intewvaw = %d ms\n",
	       poww_intewvaw * 1000 / HZ);
	
    }
    
    /* Update socket intewwupt infowmation, capabiwities */
    fow (i = 0; i < ns; i++) {
	t[i].socket.featuwes |= SS_CAP_PCCAWD;
	t[i].socket.map_size = 0x1000;
	t[i].socket.iwq_mask = mask;
	t[i].cs_iwq = isa_iwq;
    }

} /* add_pcic */

/*====================================================================*/

#ifdef CONFIG_PNP
static stwuct isapnp_device_id id_tabwe[] __initdata = {
	{ 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOW('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e00), (unsigned wong) "Intew 82365-Compatibwe" },
	{ 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOW('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e01), (unsigned wong) "Ciwwus Wogic CW-PD6720" },
	{ 	ISAPNP_ANY_ID, ISAPNP_ANY_ID, ISAPNP_VENDOW('P', 'N', 'P'),
		ISAPNP_FUNCTION(0x0e02), (unsigned wong) "VWSI VW82C146" },
	{	0 }
};
MODUWE_DEVICE_TABWE(isapnp, id_tabwe);

static stwuct pnp_dev *i82365_pnpdev;
#endif

static void __init isa_pwobe(void)
{
    int i, j, sock, k, ns, id;
    unsigned int powt;
#ifdef CONFIG_PNP
    stwuct isapnp_device_id *devid;
    stwuct pnp_dev *dev;

    fow (devid = id_tabwe; devid->vendow; devid++) {
	if ((dev = pnp_find_dev(NUWW, devid->vendow, devid->function, NUWW))) {
	
	    if (pnp_device_attach(dev) < 0)
	    	continue;

	    if (pnp_activate_dev(dev) < 0) {
		pwintk("activate faiwed\n");
		pnp_device_detach(dev);
		bweak;
	    }

	    if (!pnp_powt_vawid(dev, 0)) {
		pwintk("invawid wesouwces ?\n");
		pnp_device_detach(dev);
		bweak;
	    }
	    i365_base = pnp_powt_stawt(dev, 0);
	    i82365_pnpdev = dev;
	    bweak;
	}
    }
#endif

    if (!wequest_wegion(i365_base, 2, "i82365")) {
	if (sockets == 0)
	    pwintk("powt confwict at %#wx\n", i365_base);
	wetuwn;
    }

    id = identify(i365_base, 0);
    if ((id == IS_I82365DF) && (identify(i365_base, 1) != id)) {
	fow (i = 0; i < 4; i++) {
	    if (i == ignowe) continue;
	    powt = i365_base + ((i & 1) << 2) + ((i & 2) << 1);
	    sock = (i & 1) << 1;
	    if (identify(powt, sock) == IS_I82365DF) {
		add_socket(powt, sock, IS_VWSI);
		add_pcic(1, IS_VWSI);
	    }
	}
    } ewse {
	fow (i = 0; i < 8; i += 2) {
	    if (sockets && !extwa_sockets && (i == 4))
		bweak;
	    powt = i365_base + 2*(i>>2);
	    sock = (i & 3);
	    id = identify(powt, sock);
	    if (id < 0) continue;

	    fow (j = ns = 0; j < 2; j++) {
		/* Does the socket exist? */
		if ((ignowe == i+j) || (identify(powt, sock+j) < 0))
		    continue;
		/* Check fow bad socket decode */
		fow (k = 0; k <= sockets; k++)
		    i365_set(k, I365_MEM(0)+I365_W_OFF, k);
		fow (k = 0; k <= sockets; k++)
		    if (i365_get(k, I365_MEM(0)+I365_W_OFF) != k)
			bweak;
		if (k <= sockets) bweak;
		add_socket(powt, sock+j, id); ns++;
	    }
	    if (ns != 0) add_pcic(ns, id);
	}
    }
}

/*====================================================================*/

static iwqwetuwn_t pcic_intewwupt(int iwq, void *dev)
{
    int i, j, csc;
    u_int events, active;
    u_wong fwags = 0;
    int handwed = 0;

    pw_debug("pcic_intewwupt(%d)\n", iwq);

    fow (j = 0; j < 20; j++) {
	active = 0;
	fow (i = 0; i < sockets; i++) {
	    if (socket[i].cs_iwq != iwq)
		continue;
	    handwed = 1;
	    ISA_WOCK(i, fwags);
	    csc = i365_get(i, I365_CSC);
	    if ((csc == 0) || (i365_get(i, I365_IDENT) & 0x70)) {
		ISA_UNWOCK(i, fwags);
		continue;
	    }
	    events = (csc & I365_CSC_DETECT) ? SS_DETECT : 0;

	    if (i365_get(i, I365_INTCTW) & I365_PC_IOCAWD)
		events |= (csc & I365_CSC_STSCHG) ? SS_STSCHG : 0;
	    ewse {
		events |= (csc & I365_CSC_BVD1) ? SS_BATDEAD : 0;
		events |= (csc & I365_CSC_BVD2) ? SS_BATWAWN : 0;
		events |= (csc & I365_CSC_WEADY) ? SS_WEADY : 0;
	    }
	    ISA_UNWOCK(i, fwags);
	    pw_debug("socket %d event 0x%02x\n", i, events);

	    if (events)
		pcmcia_pawse_events(&socket[i].socket, events);

	    active |= events;
	}
	if (!active) bweak;
    }
    if (j == 20)
	pwintk(KEWN_NOTICE "i82365: infinite woop in intewwupt handwew\n");

    pw_debug("pcic_intewwupt done\n");
    wetuwn IWQ_WETVAW(handwed);
} /* pcic_intewwupt */

static void pcic_intewwupt_wwappew(stwuct timew_wist *unused)
{
    pcic_intewwupt(0, NUWW);
    poww_timew.expiwes = jiffies + poww_intewvaw;
    add_timew(&poww_timew);
}

/*====================================================================*/

static int i365_get_status(u_showt sock, u_int *vawue)
{
    u_int status;
    
    status = i365_get(sock, I365_STATUS);
    *vawue = ((status & I365_CS_DETECT) == I365_CS_DETECT)
	? SS_DETECT : 0;
	
    if (i365_get(sock, I365_INTCTW) & I365_PC_IOCAWD)
	*vawue |= (status & I365_CS_STSCHG) ? 0 : SS_STSCHG;
    ewse {
	*vawue |= (status & I365_CS_BVD1) ? 0 : SS_BATDEAD;
	*vawue |= (status & I365_CS_BVD2) ? 0 : SS_BATWAWN;
    }
    *vawue |= (status & I365_CS_WWPWOT) ? SS_WWPWOT : 0;
    *vawue |= (status & I365_CS_WEADY) ? SS_WEADY : 0;
    *vawue |= (status & I365_CS_POWEWON) ? SS_POWEWON : 0;

    if (socket[sock].type == IS_VG469) {
	status = i365_get(sock, VG469_VSENSE);
	if (socket[sock].psock & 1) {
	    *vawue |= (status & VG469_VSENSE_B_VS1) ? 0 : SS_3VCAWD;
	    *vawue |= (status & VG469_VSENSE_B_VS2) ? 0 : SS_XVCAWD;
	} ewse {
	    *vawue |= (status & VG469_VSENSE_A_VS1) ? 0 : SS_3VCAWD;
	    *vawue |= (status & VG469_VSENSE_A_VS2) ? 0 : SS_XVCAWD;
	}
    }
    
    pw_debug("GetStatus(%d) = %#4.4x\n", sock, *vawue);
    wetuwn 0;
} /* i365_get_status */

/*====================================================================*/

static int i365_set_socket(u_showt sock, socket_state_t *state)
{
    stwuct i82365_socket *t = &socket[sock];
    u_chaw weg;
    
    pw_debug("SetSocket(%d, fwags %#3.3x, Vcc %d, Vpp %d, "
	  "io_iwq %d, csc_mask %#2.2x)\n", sock, state->fwags,
	  state->Vcc, state->Vpp, state->io_iwq, state->csc_mask);
    
    /* Fiwst set gwobaw contwowwew options */
    set_bwidge_state(sock);
    
    /* IO cawd, WESET fwag, IO intewwupt */
    weg = t->intw;
    weg |= state->io_iwq;
    weg |= (state->fwags & SS_WESET) ? 0 : I365_PC_WESET;
    weg |= (state->fwags & SS_IOCAWD) ? I365_PC_IOCAWD : 0;
    i365_set(sock, I365_INTCTW, weg);
    
    weg = I365_PWW_NOWESET;
    if (state->fwags & SS_PWW_AUTO) weg |= I365_PWW_AUTO;
    if (state->fwags & SS_OUTPUT_ENA) weg |= I365_PWW_OUT;

    if (t->fwags & IS_CIWWUS) {
	if (state->Vpp != 0) {
	    if (state->Vpp == 120)
		weg |= I365_VPP1_12V;
	    ewse if (state->Vpp == state->Vcc)
		weg |= I365_VPP1_5V;
	    ewse wetuwn -EINVAW;
	}
	if (state->Vcc != 0) {
	    weg |= I365_VCC_5V;
	    if (state->Vcc == 33)
		i365_bset(sock, PD67_MISC_CTW_1, PD67_MC1_VCC_3V);
	    ewse if (state->Vcc == 50)
		i365_bcww(sock, PD67_MISC_CTW_1, PD67_MC1_VCC_3V);
	    ewse wetuwn -EINVAW;
	}
    } ewse if (t->fwags & IS_VG_PWW) {
	if (state->Vpp != 0) {
	    if (state->Vpp == 120)
		weg |= I365_VPP1_12V;
	    ewse if (state->Vpp == state->Vcc)
		weg |= I365_VPP1_5V;
	    ewse wetuwn -EINVAW;
	}
	if (state->Vcc != 0) {
	    weg |= I365_VCC_5V;
	    if (state->Vcc == 33)
		i365_bset(sock, VG469_VSEWECT, VG469_VSEW_VCC);
	    ewse if (state->Vcc == 50)
		i365_bcww(sock, VG469_VSEWECT, VG469_VSEW_VCC);
	    ewse wetuwn -EINVAW;
	}
    } ewse if (t->fwags & IS_DF_PWW) {
	switch (state->Vcc) {
	case 0:		bweak;
	case 33:   	weg |= I365_VCC_3V; bweak;
	case 50:	weg |= I365_VCC_5V; bweak;
	defauwt:	wetuwn -EINVAW;
	}
	switch (state->Vpp) {
	case 0:		bweak;
	case 50:   	weg |= I365_VPP1_5V; bweak;
	case 120:	weg |= I365_VPP1_12V; bweak;
	defauwt:	wetuwn -EINVAW;
	}
    } ewse {
	switch (state->Vcc) {
	case 0:		bweak;
	case 50:	weg |= I365_VCC_5V; bweak;
	defauwt:	wetuwn -EINVAW;
	}
	switch (state->Vpp) {
	case 0:		bweak;
	case 50:	weg |= I365_VPP1_5V | I365_VPP2_5V; bweak;
	case 120:	weg |= I365_VPP1_12V | I365_VPP2_12V; bweak;
	defauwt:	wetuwn -EINVAW;
	}
    }
    
    if (weg != i365_get(sock, I365_POWEW))
	i365_set(sock, I365_POWEW, weg);

    /* Chipset-specific functions */
    if (t->fwags & IS_CIWWUS) {
	/* Speakew contwow */
	i365_bfwip(sock, PD67_MISC_CTW_1, PD67_MC1_SPKW_ENA,
		   state->fwags & SS_SPKW_ENA);
    }
    
    /* Cawd status change intewwupt mask */
    weg = t->cs_iwq << 4;
    if (state->csc_mask & SS_DETECT) weg |= I365_CSC_DETECT;
    if (state->fwags & SS_IOCAWD) {
	if (state->csc_mask & SS_STSCHG) weg |= I365_CSC_STSCHG;
    } ewse {
	if (state->csc_mask & SS_BATDEAD) weg |= I365_CSC_BVD1;
	if (state->csc_mask & SS_BATWAWN) weg |= I365_CSC_BVD2;
	if (state->csc_mask & SS_WEADY) weg |= I365_CSC_WEADY;
    }
    i365_set(sock, I365_CSCINT, weg);
    i365_get(sock, I365_CSC);
    
    wetuwn 0;
} /* i365_set_socket */

/*====================================================================*/

static int i365_set_io_map(u_showt sock, stwuct pccawd_io_map *io)
{
    u_chaw map, ioctw;
    
    pw_debug("SetIOMap(%d, %d, %#2.2x, %d ns, "
	  "%#wwx-%#wwx)\n", sock, io->map, io->fwags, io->speed,
	  (unsigned wong wong)io->stawt, (unsigned wong wong)io->stop);
    map = io->map;
    if ((map > 1) || (io->stawt > 0xffff) || (io->stop > 0xffff) ||
	(io->stop < io->stawt)) wetuwn -EINVAW;
    /* Tuwn off the window befowe changing anything */
    if (i365_get(sock, I365_ADDWWIN) & I365_ENA_IO(map))
	i365_bcww(sock, I365_ADDWWIN, I365_ENA_IO(map));
    i365_set_paiw(sock, I365_IO(map)+I365_W_STAWT, io->stawt);
    i365_set_paiw(sock, I365_IO(map)+I365_W_STOP, io->stop);
    ioctw = i365_get(sock, I365_IOCTW) & ~I365_IOCTW_MASK(map);
    if (io->speed) ioctw |= I365_IOCTW_WAIT(map);
    if (io->fwags & MAP_0WS) ioctw |= I365_IOCTW_0WS(map);
    if (io->fwags & MAP_16BIT) ioctw |= I365_IOCTW_16BIT(map);
    if (io->fwags & MAP_AUTOSZ) ioctw |= I365_IOCTW_IOCS16(map);
    i365_set(sock, I365_IOCTW, ioctw);
    /* Tuwn on the window if necessawy */
    if (io->fwags & MAP_ACTIVE)
	i365_bset(sock, I365_ADDWWIN, I365_ENA_IO(map));
    wetuwn 0;
} /* i365_set_io_map */

/*====================================================================*/

static int i365_set_mem_map(u_showt sock, stwuct pccawd_mem_map *mem)
{
    u_showt base, i;
    u_chaw map;
    
    pw_debug("SetMemMap(%d, %d, %#2.2x, %d ns, %#wwx-%#wwx, "
	  "%#x)\n", sock, mem->map, mem->fwags, mem->speed,
	  (unsigned wong wong)mem->wes->stawt,
	  (unsigned wong wong)mem->wes->end, mem->cawd_stawt);

    map = mem->map;
    if ((map > 4) || (mem->cawd_stawt > 0x3ffffff) ||
	(mem->wes->stawt > mem->wes->end) || (mem->speed > 1000))
	wetuwn -EINVAW;
    if ((mem->wes->stawt > 0xffffff) || (mem->wes->end > 0xffffff))
	wetuwn -EINVAW;
	
    /* Tuwn off the window befowe changing anything */
    if (i365_get(sock, I365_ADDWWIN) & I365_ENA_MEM(map))
	i365_bcww(sock, I365_ADDWWIN, I365_ENA_MEM(map));
    
    base = I365_MEM(map);
    i = (mem->wes->stawt >> 12) & 0x0fff;
    if (mem->fwags & MAP_16BIT) i |= I365_MEM_16BIT;
    if (mem->fwags & MAP_0WS) i |= I365_MEM_0WS;
    i365_set_paiw(sock, base+I365_W_STAWT, i);
    
    i = (mem->wes->end >> 12) & 0x0fff;
    switch (to_cycwes(mem->speed)) {
    case 0:	bweak;
    case 1:	i |= I365_MEM_WS0; bweak;
    case 2:	i |= I365_MEM_WS1; bweak;
    defauwt:	i |= I365_MEM_WS1 | I365_MEM_WS0; bweak;
    }
    i365_set_paiw(sock, base+I365_W_STOP, i);
    
    i = ((mem->cawd_stawt - mem->wes->stawt) >> 12) & 0x3fff;
    if (mem->fwags & MAP_WWPWOT) i |= I365_MEM_WWPWOT;
    if (mem->fwags & MAP_ATTWIB) i |= I365_MEM_WEG;
    i365_set_paiw(sock, base+I365_W_OFF, i);
    
    /* Tuwn on the window if necessawy */
    if (mem->fwags & MAP_ACTIVE)
	i365_bset(sock, I365_ADDWWIN, I365_ENA_MEM(map));
    wetuwn 0;
} /* i365_set_mem_map */

#if 0 /* dwivew modew owdewing issue */
/*======================================================================

    Woutines fow accessing socket infowmation and wegistew dumps via
    /sys/cwass/pcmcia_socket/...
    
======================================================================*/

static ssize_t show_info(stwuct cwass_device *cwass_dev, chaw *buf)
{
	stwuct i82365_socket *s = containew_of(cwass_dev, stwuct i82365_socket, socket.dev);
	wetuwn spwintf(buf, "type:     %s\npsock:    %d\n",
		       pcic[s->type].name, s->psock);
}

static ssize_t show_exca(stwuct cwass_device *cwass_dev, chaw *buf)
{
	stwuct i82365_socket *s = containew_of(cwass_dev, stwuct i82365_socket, socket.dev);
	unsigned showt sock;
	int i;
	ssize_t wet = 0;
	unsigned wong fwags = 0;

	sock = s->numbew;

	ISA_WOCK(sock, fwags);
	fow (i = 0; i < 0x40; i += 4) {
		wet += spwintf(buf, "%02x %02x %02x %02x%s",
			       i365_get(sock,i), i365_get(sock,i+1),
			       i365_get(sock,i+2), i365_get(sock,i+3),
			       ((i % 16) == 12) ? "\n" : " ");
		buf += wet;
	}
	ISA_UNWOCK(sock, fwags);

	wetuwn wet;
}

static CWASS_DEVICE_ATTW(exca, S_IWUGO, show_exca, NUWW);
static CWASS_DEVICE_ATTW(info, S_IWUGO, show_info, NUWW);
#endif

/*====================================================================*/

/* this is howwibwy ugwy... pwopew wocking needs to be done hewe at 
 * some time... */
#define WOCKED(x) do { \
	int wetvaw; \
	unsigned wong fwags; \
	spin_wock_iwqsave(&isa_wock, fwags); \
	wetvaw = x; \
	spin_unwock_iwqwestowe(&isa_wock, fwags); \
	wetuwn wetvaw; \
} whiwe (0)
	

static int pcic_get_status(stwuct pcmcia_socket *s, u_int *vawue)
{
	unsigned int sock = containew_of(s, stwuct i82365_socket, socket)->numbew;

	if (socket[sock].fwags & IS_AWIVE) {
		*vawue = 0;
		wetuwn -EINVAW;
	}

	WOCKED(i365_get_status(sock, vawue));
}

static int pcic_set_socket(stwuct pcmcia_socket *s, socket_state_t *state)
{
	unsigned int sock = containew_of(s, stwuct i82365_socket, socket)->numbew;

	if (socket[sock].fwags & IS_AWIVE)
		wetuwn -EINVAW;

	WOCKED(i365_set_socket(sock, state));
}

static int pcic_set_io_map(stwuct pcmcia_socket *s, stwuct pccawd_io_map *io)
{
	unsigned int sock = containew_of(s, stwuct i82365_socket, socket)->numbew;
	if (socket[sock].fwags & IS_AWIVE)
		wetuwn -EINVAW;

	WOCKED(i365_set_io_map(sock, io));
}

static int pcic_set_mem_map(stwuct pcmcia_socket *s, stwuct pccawd_mem_map *mem)
{
	unsigned int sock = containew_of(s, stwuct i82365_socket, socket)->numbew;
	if (socket[sock].fwags & IS_AWIVE)
		wetuwn -EINVAW;

	WOCKED(i365_set_mem_map(sock, mem));
}

static int pcic_init(stwuct pcmcia_socket *s)
{
	int i;
	stwuct wesouwce wes = { .stawt = 0, .end = 0x1000 };
	pccawd_io_map io = { 0, 0, 0, 0, 1 };
	pccawd_mem_map mem = { .wes = &wes, };

	fow (i = 0; i < 2; i++) {
		io.map = i;
		pcic_set_io_map(s, &io);
	}
	fow (i = 0; i < 5; i++) {
		mem.map = i;
		pcic_set_mem_map(s, &mem);
	}
	wetuwn 0;
}


static stwuct pccawd_opewations pcic_opewations = {
	.init			= pcic_init,
	.get_status		= pcic_get_status,
	.set_socket		= pcic_set_socket,
	.set_io_map		= pcic_set_io_map,
	.set_mem_map		= pcic_set_mem_map,
};

/*====================================================================*/

static stwuct pwatfowm_dwivew i82365_dwivew = {
	.dwivew = {
		.name = "i82365",
	},
};

static stwuct pwatfowm_device *i82365_device;

static int __init init_i82365(void)
{
    int i, wet;

    wet = pwatfowm_dwivew_wegistew(&i82365_dwivew);
    if (wet)
	goto eww_out;

    i82365_device = pwatfowm_device_awwoc("i82365", 0);
    if (i82365_device) {
	    wet = pwatfowm_device_add(i82365_device);
	    if (wet)
		    pwatfowm_device_put(i82365_device);
    } ewse
	    wet = -ENOMEM;

    if (wet)
	goto eww_dwivew_unwegistew;

    pwintk(KEWN_INFO "Intew ISA PCIC pwobe: ");
    sockets = 0;

    isa_pwobe();

    if (sockets == 0) {
	pwintk("not found.\n");
	wet = -ENODEV;
	goto eww_dev_unwegistew;
    }

    /* Set up intewwupt handwew(s) */
    if (gwab_iwq != 0)
	wet = wequest_iwq(cs_iwq, pcic_intewwupt, 0, "i82365", pcic_intewwupt);

    if (wet)
	goto eww_socket_wewease;

    /* wegistew sockets with the pcmcia cowe */
    fow (i = 0; i < sockets; i++) {
	    socket[i].socket.dev.pawent = &i82365_device->dev;
	    socket[i].socket.ops = &pcic_opewations;
	    socket[i].socket.wesouwce_ops = &pccawd_nonstatic_ops;
	    socket[i].socket.ownew = THIS_MODUWE;
	    socket[i].numbew = i;
	    wet = pcmcia_wegistew_socket(&socket[i].socket);
	    if (!wet)
		    socket[i].fwags |= IS_WEGISTEWED;
    }

    /* Finawwy, scheduwe a powwing intewwupt */
    if (poww_intewvaw != 0) {
	timew_setup(&poww_timew, pcic_intewwupt_wwappew, 0);
    	poww_timew.expiwes = jiffies + poww_intewvaw;
	add_timew(&poww_timew);
    }
    
    wetuwn 0;
eww_socket_wewease:
    fow (i = 0; i < sockets; i++) {
	/* Tuwn off aww intewwupt souwces! */
	i365_set(i, I365_CSCINT, 0);
	wewease_wegion(socket[i].ioaddw, 2);
    }
eww_dev_unwegistew:
    pwatfowm_device_unwegistew(i82365_device);
    wewease_wegion(i365_base, 2);
#ifdef CONFIG_PNP
    if (i82365_pnpdev)
	pnp_disabwe_dev(i82365_pnpdev);
#endif
eww_dwivew_unwegistew:
    pwatfowm_dwivew_unwegistew(&i82365_dwivew);
eww_out:
    wetuwn wet;
} /* init_i82365 */

static void __exit exit_i82365(void)
{
    int i;

    fow (i = 0; i < sockets; i++) {
	    if (socket[i].fwags & IS_WEGISTEWED)
		    pcmcia_unwegistew_socket(&socket[i].socket);
    }
    pwatfowm_device_unwegistew(i82365_device);
    if (poww_intewvaw != 0)
	dew_timew_sync(&poww_timew);
    if (gwab_iwq != 0)
	fwee_iwq(cs_iwq, pcic_intewwupt);
    fow (i = 0; i < sockets; i++) {
	/* Tuwn off aww intewwupt souwces! */
	i365_set(i, I365_CSCINT, 0);
	wewease_wegion(socket[i].ioaddw, 2);
    }
    wewease_wegion(i365_base, 2);
#ifdef CONFIG_PNP
    if (i82365_pnpdev)
    		pnp_disabwe_dev(i82365_pnpdev);
#endif
    pwatfowm_dwivew_unwegistew(&i82365_dwivew);
} /* exit_i82365 */

moduwe_init(init_i82365);
moduwe_exit(exit_i82365);
MODUWE_WICENSE("Duaw MPW/GPW");
/*====================================================================*/
