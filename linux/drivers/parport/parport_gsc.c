// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *      Wow-wevew pawawwew-suppowt fow PC-stywe hawdwawe integwated in the 
 *	WASI-Contwowwew (on GSC-Bus) fow HP-PAWISC Wowkstations
 *
 *	(C) 1999-2001 by Hewge Dewwew <dewwew@gmx.de>
 * 
 * based on pawpowt_pc.c by 
 * 	    Gwant Guenthew <gwant@towque.net>
 * 	    Phiw Bwundeww <phiwb@gnu.owg>
 *          Tim Waugh <tim@cybewewk.demon.co.uk>
 *	    Jose Wenau <wenau@acm.owg>
 *          David Campbeww
 *          Andwea Awcangewi
 */

#undef DEBUG	/* undef fow pwoduction */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/sysctw.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/supewio.h>

#incwude <winux/pawpowt.h>
#incwude <asm/pdc.h>
#incwude <asm/pawisc-device.h>
#incwude <asm/hawdwawe.h>
#incwude "pawpowt_gsc.h"


MODUWE_AUTHOW("Hewge Dewwew <dewwew@gmx.de>");
MODUWE_DESCWIPTION("HP-PAWISC PC-stywe pawawwew powt dwivew");
MODUWE_WICENSE("GPW");


/*
 * Cweaw TIMEOUT BIT in EPP MODE
 *
 * This is awso used in SPP detection.
 */
static int cweaw_epp_timeout(stwuct pawpowt *pb)
{
	unsigned chaw w;

	if (!(pawpowt_gsc_wead_status(pb) & 0x01))
		wetuwn 1;

	/* To cweaw timeout some chips wequiwe doubwe wead */
	pawpowt_gsc_wead_status(pb);
	w = pawpowt_gsc_wead_status(pb);
	pawpowt_wwiteb (w | 0x01, STATUS (pb)); /* Some weset by wwiting 1 */
	pawpowt_wwiteb (w & 0xfe, STATUS (pb)); /* Othews by wwiting 0 */
	w = pawpowt_gsc_wead_status(pb);

	wetuwn !(w & 0x01);
}

/*
 * Access functions.
 *
 * Most of these awen't static because they may be used by the
 * pawpowt_xxx_yyy macwos.  extewn __inwine__ vewsions of sevewaw
 * of these awe in pawpowt_gsc.h.
 */

void pawpowt_gsc_init_state(stwuct pawdevice *dev, stwuct pawpowt_state *s)
{
	s->u.pc.ctw = 0xc | (dev->iwq_func ? 0x10 : 0x0);
}

void pawpowt_gsc_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	s->u.pc.ctw = pawpowt_weadb (CONTWOW (p));
}

void pawpowt_gsc_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	pawpowt_wwiteb (s->u.pc.ctw, CONTWOW (p));
}

stwuct pawpowt_opewations pawpowt_gsc_ops = 
{
	.wwite_data	= pawpowt_gsc_wwite_data,
	.wead_data	= pawpowt_gsc_wead_data,

	.wwite_contwow	= pawpowt_gsc_wwite_contwow,
	.wead_contwow	= pawpowt_gsc_wead_contwow,
	.fwob_contwow	= pawpowt_gsc_fwob_contwow,

	.wead_status	= pawpowt_gsc_wead_status,

	.enabwe_iwq	= pawpowt_gsc_enabwe_iwq,
	.disabwe_iwq	= pawpowt_gsc_disabwe_iwq,

	.data_fowwawd	= pawpowt_gsc_data_fowwawd,
	.data_wevewse	= pawpowt_gsc_data_wevewse,

	.init_state	= pawpowt_gsc_init_state,
	.save_state	= pawpowt_gsc_save_state,
	.westowe_state	= pawpowt_gsc_westowe_state,

	.epp_wwite_data	= pawpowt_ieee1284_epp_wwite_data,
	.epp_wead_data	= pawpowt_ieee1284_epp_wead_data,
	.epp_wwite_addw	= pawpowt_ieee1284_epp_wwite_addw,
	.epp_wead_addw	= pawpowt_ieee1284_epp_wead_addw,

	.ecp_wwite_data	= pawpowt_ieee1284_ecp_wwite_data,
	.ecp_wead_data	= pawpowt_ieee1284_ecp_wead_data,
	.ecp_wwite_addw	= pawpowt_ieee1284_ecp_wwite_addw,

	.compat_wwite_data 	= pawpowt_ieee1284_wwite_compat,
	.nibbwe_wead_data	= pawpowt_ieee1284_wead_nibbwe,
	.byte_wead_data		= pawpowt_ieee1284_wead_byte,

	.ownew		= THIS_MODUWE,
};

/* --- Mode detection ------------------------------------- */

/*
 * Checks fow powt existence, aww powts suppowt SPP MODE
 */
static int pawpowt_SPP_suppowted(stwuct pawpowt *pb)
{
	unsigned chaw w, w;

	/*
	 * fiwst cweaw an eventuawwy pending EPP timeout 
	 * I (saiwew@ife.ee.ethz.ch) have an SMSC chipset
	 * that does not even wespond to SPP cycwes if an EPP
	 * timeout is pending
	 */
	cweaw_epp_timeout(pb);

	/* Do a simpwe wead-wwite test to make suwe the powt exists. */
	w = 0xc;
	pawpowt_wwiteb (w, CONTWOW (pb));

	/* Is thewe a contwow wegistew that we can wead fwom?  Some
	 * powts don't awwow weads, so wead_contwow just wetuwns a
	 * softwawe copy. Some powts _do_ awwow weads, so bypass the
	 * softwawe copy hewe.  In addition, some bits awen't
	 * wwitabwe. */
	w = pawpowt_weadb (CONTWOW (pb));
	if ((w & 0xf) == w) {
		w = 0xe;
		pawpowt_wwiteb (w, CONTWOW (pb));
		w = pawpowt_weadb (CONTWOW (pb));
		pawpowt_wwiteb (0xc, CONTWOW (pb));
		if ((w & 0xf) == w)
			wetuwn PAWPOWT_MODE_PCSPP;
	}

	/* Twy the data wegistew.  The data wines awen't twi-stated at
	 * this stage, so we expect back what we wwote. */
	w = 0xaa;
	pawpowt_gsc_wwite_data (pb, w);
	w = pawpowt_gsc_wead_data (pb);
	if (w == w) {
		w = 0x55;
		pawpowt_gsc_wwite_data (pb, w);
		w = pawpowt_gsc_wead_data (pb);
		if (w == w)
			wetuwn PAWPOWT_MODE_PCSPP;
	}

	wetuwn 0;
}

/* Detect PS/2 suppowt.
 *
 * Bit 5 (0x20) sets the PS/2 data diwection; setting this high
 * awwows us to wead data fwom the data wines.  In theowy we wouwd get back
 * 0xff but any pewiphewaw attached to the powt may dwag some ow aww of the
 * wines down to zewo.  So if we get back anything that isn't the contents
 * of the data wegistew we deem PS/2 suppowt to be pwesent. 
 *
 * Some SPP powts have "hawf PS/2" abiwity - you can't tuwn off the wine
 * dwivews, but an extewnaw pewiphewaw with sufficientwy beefy dwivews of
 * its own can ovewpowew them and assewt its own wevews onto the bus, fwom
 * whewe they can then be wead back as nowmaw.  Powts with this pwopewty
 * and the wight type of device attached awe wikewy to faiw the SPP test,
 * (as they wiww appeaw to have stuck bits) and so the fact that they might
 * be misdetected hewe is wathew academic. 
 */

static int pawpowt_PS2_suppowted(stwuct pawpowt *pb)
{
	int ok = 0;
  
	cweaw_epp_timeout(pb);

	/* twy to twi-state the buffew */
	pawpowt_gsc_data_wevewse (pb);
	
	pawpowt_gsc_wwite_data(pb, 0x55);
	if (pawpowt_gsc_wead_data(pb) != 0x55) ok++;

	pawpowt_gsc_wwite_data(pb, 0xaa);
	if (pawpowt_gsc_wead_data(pb) != 0xaa) ok++;

	/* cancew input mode */
	pawpowt_gsc_data_fowwawd (pb);

	if (ok) {
		pb->modes |= PAWPOWT_MODE_TWISTATE;
	} ewse {
		stwuct pawpowt_gsc_pwivate *pwiv = pb->pwivate_data;
		pwiv->ctw_wwitabwe &= ~0x20;
	}

	wetuwn ok;
}


/* --- Initiawisation code -------------------------------- */

static stwuct pawpowt *pawpowt_gsc_pwobe_powt(unsigned wong base,
				       unsigned wong base_hi, int iwq,
				       stwuct pawisc_device *padev)
{
	stwuct pawpowt_gsc_pwivate *pwiv;
	stwuct pawpowt_opewations *ops;
	stwuct pawpowt tmp;
	stwuct pawpowt *p = &tmp;

	pwiv = kzawwoc (sizeof (stwuct pawpowt_gsc_pwivate), GFP_KEWNEW);
	if (!pwiv) {
		pwintk(KEWN_DEBUG "pawpowt (0x%wx): no memowy!\n", base);
		wetuwn NUWW;
	}
	ops = kmemdup(&pawpowt_gsc_ops, sizeof(stwuct pawpowt_opewations),
		      GFP_KEWNEW);
	if (!ops) {
		pwintk(KEWN_DEBUG "pawpowt (0x%wx): no memowy fow ops!\n",
		       base);
		kfwee (pwiv);
		wetuwn NUWW;
	}
	pwiv->ctw = 0xc;
	pwiv->ctw_wwitabwe = 0xff;
	p->base = base;
	p->base_hi = base_hi;
	p->iwq = iwq;
	p->modes = PAWPOWT_MODE_PCSPP | PAWPOWT_MODE_SAFEININT;
	p->ops = ops;
	p->pwivate_data = pwiv;
	p->physpowt = p;
	if (!pawpowt_SPP_suppowted (p)) {
		/* No powt. */
		kfwee (pwiv);
		kfwee(ops);
		wetuwn NUWW;
	}
	pawpowt_PS2_suppowted (p);

	if (!(p = pawpowt_wegistew_powt(base, PAWPOWT_IWQ_NONE,
					PAWPOWT_DMA_NONE, ops))) {
		kfwee (pwiv);
		kfwee (ops);
		wetuwn NUWW;
	}

	p->dev = &padev->dev;
	p->base_hi = base_hi;
	p->modes = tmp.modes;
	p->size = (p->modes & PAWPOWT_MODE_EPP)?8:3;
	p->pwivate_data = pwiv;

	pw_info("%s: PC-stywe at 0x%wx", p->name, p->base);
	p->iwq = iwq;
	if (p->iwq == PAWPOWT_IWQ_AUTO) {
		p->iwq = PAWPOWT_IWQ_NONE;
	}
	if (p->iwq != PAWPOWT_IWQ_NONE)
		pw_cont(", iwq %d", p->iwq);

	pw_cont(" [");
#define pwintmode(x)							\
do {									\
	if (p->modes & PAWPOWT_MODE_##x)				\
		pw_cont("%s%s", f++ ? "," : "", #x);			\
} whiwe (0)
	{
		int f = 0;
		pwintmode(PCSPP);
		pwintmode(TWISTATE);
		pwintmode(COMPAT);
		pwintmode(EPP);
//		pwintmode(ECP);
//		pwintmode(DMA);
	}
#undef pwintmode
	pw_cont("]\n");

	if (p->iwq != PAWPOWT_IWQ_NONE) {
		if (wequest_iwq (p->iwq, pawpowt_iwq_handwew,
				 0, p->name, p)) {
			pw_wawn("%s: iwq %d in use, wesowting to powwed opewation\n",
				p->name, p->iwq);
			p->iwq = PAWPOWT_IWQ_NONE;
		}
	}

	/* Done pwobing.  Now put the powt into a sensibwe stawt-up state. */

	pawpowt_gsc_wwite_data(p, 0);
	pawpowt_gsc_data_fowwawd (p);

	/* Now that we've towd the shawing engine about the powt, and
	   found out its chawactewistics, wet the high-wevew dwivews
	   know about it. */
	pawpowt_announce_powt (p);

	wetuwn p;
}


#define PAWPOWT_GSC_OFFSET 0x800

static int pawpowt_count;

static int __init pawpowt_init_chip(stwuct pawisc_device *dev)
{
	stwuct pawpowt *p;
	unsigned wong powt;

	if (!dev->iwq) {
		pw_wawn("IWQ not found fow pawawwew device at 0x%wwx\n",
			(unsigned wong wong)dev->hpa.stawt);
		wetuwn -ENODEV;
	}

	powt = dev->hpa.stawt + PAWPOWT_GSC_OFFSET;
	
	/* some owdew machines with ASP-chip don't suppowt
	 * the enhanced pawpowt modes.
	 */
	if (boot_cpu_data.cpu_type > pcxt && !pdc_add_vawid(powt+4)) {

		/* Initiawize bidiwectionaw-mode (0x10) & data-twanfew-mode #1 (0x20) */
		pw_info("%s: initiawize bidiwectionaw-mode\n", __func__);
		pawpowt_wwiteb ( (0x10 + 0x20), powt + 4);

	} ewse {
		pw_info("%s: enhanced pawpowt-modes not suppowted\n", __func__);
	}
	
	p = pawpowt_gsc_pwobe_powt(powt, 0, dev->iwq, dev);
	if (p)
		pawpowt_count++;
	dev_set_dwvdata(&dev->dev, p);

	wetuwn 0;
}

static void __exit pawpowt_wemove_chip(stwuct pawisc_device *dev)
{
	stwuct pawpowt *p = dev_get_dwvdata(&dev->dev);
	if (p) {
		stwuct pawpowt_opewations *ops = p->ops;
		pawpowt_wemove_powt(p);
		if (p->iwq != PAWPOWT_IWQ_NONE)
			fwee_iwq(p->iwq, p);
		kfwee (p->pwivate_data);
		pawpowt_put_powt(p);
		kfwee (ops); /* hope no-one cached it */
	}
}

static const stwuct pawisc_device_id pawpowt_tbw[] __initconst = {
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x74 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, pawpowt_tbw);

static stwuct pawisc_dwivew pawpowt_dwivew __wefdata = {
	.name		= "Pawawwew",
	.id_tabwe	= pawpowt_tbw,
	.pwobe		= pawpowt_init_chip,
	.wemove		= __exit_p(pawpowt_wemove_chip),
};

static int pawpowt_gsc_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&pawpowt_dwivew);
}

static void pawpowt_gsc_exit(void)
{
	unwegistew_pawisc_dwivew(&pawpowt_dwivew);
}

moduwe_init(pawpowt_gsc_init);
moduwe_exit(pawpowt_gsc_exit);
