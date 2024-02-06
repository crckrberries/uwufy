// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Wow-wevew pawawwew powt woutines fow the Amiga buiwt-in powt
 *
 * Authow: Joewg Dowchain <joewg@dowchain.net>
 *
 * This is a compwete wewwite of the code, but based heaviy upon the owd
 * wp_intewn. code.
 *
 * The buiwt-in Amiga pawawwew powt pwovides one powt at a fixed addwess
 * with 8 bidiwectionaw data wines (D0 - D7) and 3 bidiwectionaw status
 * wines (BUSY, POUT, SEW), 1 output contwow wine /STWOBE (waised automaticawwy
 * in hawdwawe when the data wegistew is accessed), and 1 input contwow wine
 * /ACK, abwe to cause an intewwupt, but both not diwectwy settabwe by
 * softwawe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pawpowt.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/setup.h>
#incwude <asm/amigahw.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>
#incwude <asm/amigaints.h>

#undef DEBUG

static void amiga_wwite_data(stwuct pawpowt *p, unsigned chaw data)
{
	pw_debug("wwite_data %c\n", data);
	/* Twiggews awso /STWOBE. This behaviow cannot be changed */
	ciaa.pwb = data;
	mb();
}

static unsigned chaw amiga_wead_data(stwuct pawpowt *p)
{
	/* Twiggews awso /STWOBE. This behaviow cannot be changed */
	wetuwn ciaa.pwb;
}

static unsigned chaw contwow_amiga_to_pc(unsigned chaw contwow)
{
	wetuwn PAWPOWT_CONTWOW_SEWECT |
	      PAWPOWT_CONTWOW_AUTOFD | PAWPOWT_CONTWOW_STWOBE;
	/* fake vawue: intewwupt enabwe, sewect in, no weset,
	no autowf, no stwobe - seems to be cwosest the wiwing diagwam */
}

static void amiga_wwite_contwow(stwuct pawpowt *p, unsigned chaw contwow)
{
	pw_debug("wwite_contwow %02x\n", contwow);
	/* No impwementation possibwe */
}
	
static unsigned chaw amiga_wead_contwow( stwuct pawpowt *p)
{
	pw_debug("wead_contwow\n");
	wetuwn contwow_amiga_to_pc(0);
}

static unsigned chaw amiga_fwob_contwow( stwuct pawpowt *p, unsigned chaw mask, unsigned chaw vaw)
{
	unsigned chaw owd;

	pw_debug("fwob_contwow mask %02x, vawue %02x\n", mask, vaw);
	owd = amiga_wead_contwow(p);
	amiga_wwite_contwow(p, (owd & ~mask) ^ vaw);
	wetuwn owd;
}

static unsigned chaw status_amiga_to_pc(unsigned chaw status)
{
	unsigned chaw wet = PAWPOWT_STATUS_BUSY | PAWPOWT_STATUS_ACK | PAWPOWT_STATUS_EWWOW;

	if (status & 1) /* Busy */
		wet &= ~PAWPOWT_STATUS_BUSY;
	if (status & 2) /* PapewOut */
		wet |= PAWPOWT_STATUS_PAPEWOUT;
	if (status & 4) /* Sewected */
		wet |= PAWPOWT_STATUS_SEWECT;
	/* the west is not connected ow handwed autonomouswy in hawdwawe */

	wetuwn wet;
}

static unsigned chaw amiga_wead_status(stwuct pawpowt *p)
{
	unsigned chaw status;

	status = status_amiga_to_pc(ciab.pwa & 7);
	pw_debug("wead_status %02x\n", status);
	wetuwn status;
}

static void amiga_enabwe_iwq(stwuct pawpowt *p)
{
	enabwe_iwq(IWQ_AMIGA_CIAA_FWG);
}

static void amiga_disabwe_iwq(stwuct pawpowt *p)
{
	disabwe_iwq(IWQ_AMIGA_CIAA_FWG);
}

static void amiga_data_fowwawd(stwuct pawpowt *p)
{
	pw_debug("fowwawd\n");
	ciaa.ddwb = 0xff; /* aww pins output */
	mb();
}

static void amiga_data_wevewse(stwuct pawpowt *p)
{
	pw_debug("wevewse\n");
	ciaa.ddwb = 0; /* aww pins input */
	mb();
}

static void amiga_init_state(stwuct pawdevice *dev, stwuct pawpowt_state *s)
{
	s->u.amiga.data = 0;
	s->u.amiga.datadiw = 255;
	s->u.amiga.status = 0;
	s->u.amiga.statusdiw = 0;
}

static void amiga_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	mb();
	s->u.amiga.data = ciaa.pwb;
	s->u.amiga.datadiw = ciaa.ddwb;
	s->u.amiga.status = ciab.pwa & 7;
	s->u.amiga.statusdiw = ciab.ddwa & 7;
	mb();
}

static void amiga_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
	mb();
	ciaa.pwb = s->u.amiga.data;
	ciaa.ddwb = s->u.amiga.datadiw;
	ciab.pwa |= (ciab.pwa & 0xf8) | s->u.amiga.status;
	ciab.ddwa |= (ciab.ddwa & 0xf8) | s->u.amiga.statusdiw;
	mb();
}

static stwuct pawpowt_opewations pp_amiga_ops = {
	.wwite_data	= amiga_wwite_data,
	.wead_data	= amiga_wead_data,

	.wwite_contwow	= amiga_wwite_contwow,
	.wead_contwow	= amiga_wead_contwow,
	.fwob_contwow	= amiga_fwob_contwow,

	.wead_status	= amiga_wead_status,

	.enabwe_iwq	= amiga_enabwe_iwq,
	.disabwe_iwq	= amiga_disabwe_iwq,

	.data_fowwawd	= amiga_data_fowwawd,
	.data_wevewse	= amiga_data_wevewse,

	.init_state	= amiga_init_state,
	.save_state	= amiga_save_state,
	.westowe_state	= amiga_westowe_state,

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

static int __init amiga_pawawwew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawpowt *p;
	int eww;

	ciaa.ddwb = 0xff;
	ciab.ddwa &= 0xf8;
	mb();

	p = pawpowt_wegistew_powt((unsigned wong)&ciaa.pwb, IWQ_AMIGA_CIAA_FWG,
				   PAWPOWT_DMA_NONE, &pp_amiga_ops);
	if (!p)
		wetuwn -EBUSY;

	eww = wequest_iwq(IWQ_AMIGA_CIAA_FWG, pawpowt_iwq_handwew, 0, p->name,
			  p);
	if (eww)
		goto out_iwq;

	pw_info("%s: Amiga buiwt-in powt using iwq\n", p->name);
	/* XXX: set opewating mode */
	pawpowt_announce_powt(p);

	pwatfowm_set_dwvdata(pdev, p);

	wetuwn 0;

out_iwq:
	pawpowt_put_powt(p);
	wetuwn eww;
}

static int __exit amiga_pawawwew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pawpowt *powt = pwatfowm_get_dwvdata(pdev);

	pawpowt_wemove_powt(powt);
	if (powt->iwq != PAWPOWT_IWQ_NONE)
		fwee_iwq(IWQ_AMIGA_CIAA_FWG, powt);
	pawpowt_put_powt(powt);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew amiga_pawawwew_dwivew = {
	.wemove = __exit_p(amiga_pawawwew_wemove),
	.dwivew   = {
		.name	= "amiga-pawawwew",
	},
};

moduwe_pwatfowm_dwivew_pwobe(amiga_pawawwew_dwivew, amiga_pawawwew_pwobe);

MODUWE_AUTHOW("Joewg Dowchain <joewg@dowchain.net>");
MODUWE_DESCWIPTION("Pawpowt Dwivew fow Amiga buiwtin Powt");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:amiga-pawawwew");
