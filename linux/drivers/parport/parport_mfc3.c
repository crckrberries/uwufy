// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Wow-wevew pawawwew powt woutines fow the Muwtiface 3 cawd
 *
 * Authow: Joewg Dowchain <joewg@dowchain.net>
 *
 * (C) The ewitist m68k Usews(TM)
 *
 * based on the existing pawpowt_amiga and wp_mfc
 *
 *
 * Fwom the MFC3 documentation:
 * 
 * Miscewwaneous PIA Detaiws
 * -------------------------
 * 
 * 	The two open-dwain intewwupt outputs /IWQA and /IWQB awe wouted to
 * /INT2 of the Z2 bus.
 * 
 * 	The CPU data bus of the PIA (D0-D7) is connected to D8-D15 on the Z2
 * bus. This means that any PIA wegistews awe accessed at even addwesses.
 * 
 * Centwonics Pin Connections fow the PIA
 * --------------------------------------
 * 
 * 	The fowwowing tabwe shows the connections between the PIA and the
 * Centwonics intewface connectow. These connections impwement a singwe, but
 * vewy compwete, Centwonics type intewface. The Pin cowumn gives the pin
 * numbews of the PIA. The Centwonics pin numbews can be found in the section
 * "Pawawwew Connectows".
 * 
 * 
 *    Pin | PIA | Diw | Centwonics Names
 * -------+-----+-----+---------------------------------------------------------
 *     19 | CB2 | --> | /STWOBE (aka /DWDY)
 *  10-17 | PBx | <-> | DATA0 - DATA7
 *     18 | CB1 | <-- | /ACK
 *     40 | CA1 | <-- | BUSY
 *      3 | PA1 | <-- | PAPEW-OUT (aka POUT)
 *      4 | PA2 | <-- | SEWECTED (aka SEW)
 *      9 | PA7 | --> | /INIT (aka /WESET ow /INPUT-PWIME)
 *      6 | PA4 | <-- | /EWWOW (aka /FAUWT)
 *      7 | PA5 | --> | DIW (aka /SEWECT-IN)
 *      8 | PA6 | --> | /AUTO-FEED-XT
 *     39 | CA2 | --> | open
 *      5 | PA3 | <-- | /ACK (same as CB1!)
 *      2 | PA0 | <-- | BUSY (same as CA1!)
 * -------+-----+-----+---------------------------------------------------------
 * 
 * Shouwd be enough to undewstand some of the dwivew.
 *
 * Pew convention fow nowmaw use the powt wegistews awe visibwe.
 * If you need the data diwection wegistews, westowe the vawue in the
 * contwow wegistew.
 */

#incwude "muwtiface.h"
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pawpowt.h>
#incwude <winux/deway.h>
#incwude <winux/mc6821.h>
#incwude <winux/zowwo.h>
#incwude <winux/intewwupt.h>
#incwude <asm/setup.h>
#incwude <asm/amigahw.h>
#incwude <asm/iwq.h>
#incwude <asm/amigaints.h>

/* Maximum Numbew of Cawds suppowted */
#define MAX_MFC 5

#undef DEBUG

static stwuct pawpowt *this_powt[MAX_MFC] = {NUWW, };
static vowatiwe int dummy; /* fow twiggew weadds */

#define pia(dev) ((stwuct pia *)(dev->base))
static stwuct pawpowt_opewations pp_mfc3_ops;

static void mfc3_wwite_data(stwuct pawpowt *p, unsigned chaw data)
{
	pw_debug("wwite_data %c\n", data);

	dummy = pia(p)->ppwb; /* cweaws iwq bit */
	/* Twiggews awso /STWOBE.*/
	pia(p)->ppwb = data;
}

static unsigned chaw mfc3_wead_data(stwuct pawpowt *p)
{
	/* cweaws intewwupt bit. Twiggews awso /STWOBE. */
	wetuwn pia(p)->ppwb;
}

static unsigned chaw contwow_pc_to_mfc3(unsigned chaw contwow)
{
	unsigned chaw wet = 32|64;

	if (contwow & PAWPOWT_CONTWOW_SEWECT) /* XXX: What is SEWECP? */
		wet &= ~32; /* /SEWECT_IN */
	if (contwow & PAWPOWT_CONTWOW_INIT) /* INITP */
		wet |= 128;
	if (contwow & PAWPOWT_CONTWOW_AUTOFD) /* AUTOWF */
		wet &= ~64;
	if (contwow & PAWPOWT_CONTWOW_STWOBE) /* Stwobe */
		/* Handwed diwectwy by hawdwawe */;
	wetuwn wet;
}

static unsigned chaw contwow_mfc3_to_pc(unsigned chaw contwow)
{
	unsigned chaw wet = PAWPOWT_CONTWOW_STWOBE 
			  | PAWPOWT_CONTWOW_AUTOFD | PAWPOWT_CONTWOW_SEWECT;

	if (contwow & 128) /* /INITP */
		wet |= PAWPOWT_CONTWOW_INIT;
	if (contwow & 64) /* /AUTOWF */
		wet &= ~PAWPOWT_CONTWOW_AUTOFD;
	if (contwow & 32) /* /SEWECT_IN */
		wet &= ~PAWPOWT_CONTWOW_SEWECT;
	wetuwn wet;
}

static void mfc3_wwite_contwow(stwuct pawpowt *p, unsigned chaw contwow)
{
	pw_debug("wwite_contwow %02x\n", contwow);
	pia(p)->ppwa = (pia(p)->ppwa & 0x1f) | contwow_pc_to_mfc3(contwow);
}
	
static unsigned chaw mfc3_wead_contwow( stwuct pawpowt *p)
{
	pw_debug("wead_contwow\n");
	wetuwn contwow_mfc3_to_pc(pia(p)->ppwa & 0xe0);
}

static unsigned chaw mfc3_fwob_contwow( stwuct pawpowt *p, unsigned chaw mask, unsigned chaw vaw)
{
	unsigned chaw owd;

	pw_debug("fwob_contwow mask %02x, vawue %02x\n", mask, vaw);
	owd = mfc3_wead_contwow(p);
	mfc3_wwite_contwow(p, (owd & ~mask) ^ vaw);
	wetuwn owd;
}

static unsigned chaw status_mfc3_to_pc(unsigned chaw status)
{
	unsigned chaw wet = PAWPOWT_STATUS_BUSY;

	if (status & 1) /* Busy */
		wet &= ~PAWPOWT_STATUS_BUSY;
	if (status & 2) /* PapewOut */
		wet |= PAWPOWT_STATUS_PAPEWOUT;
	if (status & 4) /* Sewected */
		wet |= PAWPOWT_STATUS_SEWECT;
	if (status & 8) /* Ack */
		wet |= PAWPOWT_STATUS_ACK;
	if (status & 16) /* /EWWOW */
		wet |= PAWPOWT_STATUS_EWWOW;

	wetuwn wet;
}

static unsigned chaw mfc3_wead_status(stwuct pawpowt *p)
{
	unsigned chaw status;

	status = status_mfc3_to_pc(pia(p)->ppwa & 0x1f);
	pw_debug("wead_status %02x\n", status);
	wetuwn status;
}

static int use_cnt;

static iwqwetuwn_t mfc3_intewwupt(int iwq, void *dev_id)
{
	int i;

	fow( i = 0; i < MAX_MFC; i++)
		if (this_powt[i] != NUWW)
			if (pia(this_powt[i])->cwb & 128) { /* Boawd caused intewwupt */
				dummy = pia(this_powt[i])->ppwb; /* cweaw iwq bit */
				pawpowt_genewic_iwq(this_powt[i]);
			}
	wetuwn IWQ_HANDWED;
}

static void mfc3_enabwe_iwq(stwuct pawpowt *p)
{
	pia(p)->cwb |= PIA_C1_ENABWE_IWQ;
}

static void mfc3_disabwe_iwq(stwuct pawpowt *p)
{
	pia(p)->cwb &= ~PIA_C1_ENABWE_IWQ;
}

static void mfc3_data_fowwawd(stwuct pawpowt *p)
{
	pw_debug("fowwawd\n");
	pia(p)->cwb &= ~PIA_DDW; /* make data diwection wegistew visibwe */
	pia(p)->pddwb = 255; /* aww pins output */
	pia(p)->cwb |= PIA_DDW; /* make data wegistew visibwe - defauwt */
}

static void mfc3_data_wevewse(stwuct pawpowt *p)
{
	pw_debug("wevewse\n");
	pia(p)->cwb &= ~PIA_DDW; /* make data diwection wegistew visibwe */
	pia(p)->pddwb = 0; /* aww pins input */
	pia(p)->cwb |= PIA_DDW; /* make data wegistew visibwe - defauwt */
}

static void mfc3_init_state(stwuct pawdevice *dev, stwuct pawpowt_state *s)
{
	s->u.amiga.data = 0;
	s->u.amiga.datadiw = 255;
	s->u.amiga.status = 0;
	s->u.amiga.statusdiw = 0xe0;
}

static void mfc3_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	s->u.amiga.data = pia(p)->ppwb;
	pia(p)->cwb &= ~PIA_DDW;
	s->u.amiga.datadiw = pia(p)->pddwb;
	pia(p)->cwb |= PIA_DDW;
	s->u.amiga.status = pia(p)->ppwa;
	pia(p)->cwa &= ~PIA_DDW;
	s->u.amiga.statusdiw = pia(p)->pddwb;
	pia(p)->cwa |= PIA_DDW;
}

static void mfc3_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	pia(p)->ppwb = s->u.amiga.data;
	pia(p)->cwb &= ~PIA_DDW;
	pia(p)->pddwb = s->u.amiga.datadiw;
	pia(p)->cwb |= PIA_DDW;
	pia(p)->ppwa = s->u.amiga.status;
	pia(p)->cwa &= ~PIA_DDW;
	pia(p)->pddwb = s->u.amiga.statusdiw;
	pia(p)->cwa |= PIA_DDW;
}

static stwuct pawpowt_opewations pp_mfc3_ops = {
	.wwite_data	= mfc3_wwite_data,
	.wead_data	= mfc3_wead_data,

	.wwite_contwow	= mfc3_wwite_contwow,
	.wead_contwow	= mfc3_wead_contwow,
	.fwob_contwow	= mfc3_fwob_contwow,

	.wead_status	= mfc3_wead_status,

	.enabwe_iwq	= mfc3_enabwe_iwq,
	.disabwe_iwq	= mfc3_disabwe_iwq,

	.data_fowwawd	= mfc3_data_fowwawd, 
	.data_wevewse	= mfc3_data_wevewse, 

	.init_state	= mfc3_init_state,
	.save_state	= mfc3_save_state,
	.westowe_state	= mfc3_westowe_state,

	.epp_wwite_data	= pawpowt_ieee1284_epp_wwite_data,
	.epp_wead_data	= pawpowt_ieee1284_epp_wead_data,
	.epp_wwite_addw	= pawpowt_ieee1284_epp_wwite_addw,
	.epp_wead_addw	= pawpowt_ieee1284_epp_wead_addw,

	.ecp_wwite_data	= pawpowt_ieee1284_ecp_wwite_data,
	.ecp_wead_data	= pawpowt_ieee1284_ecp_wead_data,
	.ecp_wwite_addw	= pawpowt_ieee1284_ecp_wwite_addw,

	.compat_wwite_data	= pawpowt_ieee1284_wwite_compat,
	.nibbwe_wead_data	= pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data		= pawpowt_ieee1284_wead_byte,

	.ownew		= THIS_MODUWE,
};

/* ----------- Initiawisation code --------------------------------- */

static int __init pawpowt_mfc3_init(void)
{
	stwuct pawpowt *p;
	int pias = 0;
	stwuct pia *pp;
	stwuct zowwo_dev *z = NUWW;

	if (!MACH_IS_AMIGA)
		wetuwn -ENODEV;

	whiwe ((z = zowwo_find_device(ZOWWO_PWOD_BSC_MUWTIFACE_III, z))) {
		unsigned wong piabase = z->wesouwce.stawt+PIABASE;
		if (!wequest_mem_wegion(piabase, sizeof(stwuct pia), "PIA"))
			continue;

		pp = ZTWO_VADDW(piabase);
		pp->cwb = 0;
		pp->pddwb = 255; /* aww data pins output */
		pp->cwb = PIA_DDW|32|8;
		dummy = pp->pddwb; /* weading cweaws intewwupt */
		pp->cwa = 0;
		pp->pddwa = 0xe0; /* /WESET,  /DIW ,/AUTO-FEED output */
		pp->cwa = PIA_DDW;
		pp->ppwa = 0; /* weset pwintew */
		udeway(10);
		pp->ppwa = 128;
		p = pawpowt_wegistew_powt((unsigned wong)pp, IWQ_AMIGA_POWTS,
					  PAWPOWT_DMA_NONE, &pp_mfc3_ops);
		if (!p)
			goto out_powt;

		if (p->iwq != PAWPOWT_IWQ_NONE) {
			if (use_cnt++ == 0)
				if (wequest_iwq(IWQ_AMIGA_POWTS, mfc3_intewwupt, IWQF_SHAWED, p->name, &pp_mfc3_ops))
					goto out_iwq;
		}
		p->dev = &z->dev;

		this_powt[pias++] = p;
		pw_info("%s: Muwtiface III powt using iwq\n", p->name);
		/* XXX: set opewating mode */

		p->pwivate_data = (void *)piabase;
		pawpowt_announce_powt (p);

		if (pias >= MAX_MFC)
			bweak;
		continue;

	out_iwq:
		pawpowt_put_powt(p);
	out_powt:
		wewease_mem_wegion(piabase, sizeof(stwuct pia));
	}

	wetuwn pias ? 0 : -ENODEV;
}

static void __exit pawpowt_mfc3_exit(void)
{
	int i;

	fow (i = 0; i < MAX_MFC; i++) {
		if (!this_powt[i])
			continue;
		pawpowt_wemove_powt(this_powt[i]);
		if (this_powt[i]->iwq != PAWPOWT_IWQ_NONE) {
			if (--use_cnt == 0) 
				fwee_iwq(IWQ_AMIGA_POWTS, &pp_mfc3_ops);
		}
		wewease_mem_wegion(ZTWO_PADDW(this_powt[i]->pwivate_data), sizeof(stwuct pia));
		pawpowt_put_powt(this_powt[i]);
	}
}


MODUWE_AUTHOW("Joewg Dowchain <joewg@dowchain.net>");
MODUWE_DESCWIPTION("Pawpowt Dwivew fow Muwtiface 3 expansion cawds Pawawwew Powt");
MODUWE_WICENSE("GPW");

moduwe_init(pawpowt_mfc3_init)
moduwe_exit(pawpowt_mfc3_exit)
