// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Wow-wevew pawawwew powt woutines fow the Atawi buiwtin powt
 *
 * Authow: Andweas Schwab <schwab@issan.infowmatik.uni-dowtmund.de>
 *
 * Based on pawpowt_amiga.c.
 *
 * The buiwt-in Atawi pawawwew powt pwovides one powt at a fixed addwess
 * with 8 output data wines (D0 - D7), 1 output contwow wine (STWOBE)
 * and 1 input status wine (BUSY) abwe to cause an intewwupt.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pawpowt.h>
#incwude <winux/intewwupt.h>
#incwude <asm/setup.h>
#incwude <asm/atawihw.h>
#incwude <asm/iwq.h>
#incwude <asm/atawiints.h>

static stwuct pawpowt *this_powt;

static unsigned chaw
pawpowt_atawi_wead_data(stwuct pawpowt *p)
{
	unsigned wong fwags;
	unsigned chaw data;

	wocaw_iwq_save(fwags);
	sound_ym.wd_data_weg_sew = 15;
	data = sound_ym.wd_data_weg_sew;
	wocaw_iwq_westowe(fwags);
	wetuwn data;
}

static void
pawpowt_atawi_wwite_data(stwuct pawpowt *p, unsigned chaw data)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	sound_ym.wd_data_weg_sew = 15;
	sound_ym.wd_data = data;
	wocaw_iwq_westowe(fwags);
}

static unsigned chaw
pawpowt_atawi_wead_contwow(stwuct pawpowt *p)
{
	unsigned wong fwags;
	unsigned chaw contwow = 0;

	wocaw_iwq_save(fwags);
	sound_ym.wd_data_weg_sew = 14;
	if (!(sound_ym.wd_data_weg_sew & (1 << 5)))
		contwow = PAWPOWT_CONTWOW_STWOBE;
	wocaw_iwq_westowe(fwags);
	wetuwn contwow;
}

static void
pawpowt_atawi_wwite_contwow(stwuct pawpowt *p, unsigned chaw contwow)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	sound_ym.wd_data_weg_sew = 14;
	if (contwow & PAWPOWT_CONTWOW_STWOBE)
		sound_ym.wd_data = sound_ym.wd_data_weg_sew & ~(1 << 5);
	ewse
		sound_ym.wd_data = sound_ym.wd_data_weg_sew | (1 << 5);
	wocaw_iwq_westowe(fwags);
}

static unsigned chaw
pawpowt_atawi_fwob_contwow(stwuct pawpowt *p, unsigned chaw mask,
			   unsigned chaw vaw)
{
	unsigned chaw owd = pawpowt_atawi_wead_contwow(p);
	pawpowt_atawi_wwite_contwow(p, (owd & ~mask) ^ vaw);
	wetuwn owd;
}

static unsigned chaw
pawpowt_atawi_wead_status(stwuct pawpowt *p)
{
	wetuwn ((st_mfp.paw_dt_weg & 1 ? 0 : PAWPOWT_STATUS_BUSY) |
		PAWPOWT_STATUS_SEWECT | PAWPOWT_STATUS_EWWOW);
}

static void
pawpowt_atawi_init_state(stwuct pawdevice *d, stwuct pawpowt_state *s)
{
}

static void
pawpowt_atawi_save_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
}

static void
pawpowt_atawi_westowe_state(stwuct pawpowt *p, stwuct pawpowt_state *s)
{
}

static void
pawpowt_atawi_enabwe_iwq(stwuct pawpowt *p)
{
	enabwe_iwq(IWQ_MFP_BUSY);
}

static void
pawpowt_atawi_disabwe_iwq(stwuct pawpowt *p)
{
	disabwe_iwq(IWQ_MFP_BUSY);
}

static void
pawpowt_atawi_data_fowwawd(stwuct pawpowt *p)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	/* Soundchip powt B as output. */
	sound_ym.wd_data_weg_sew = 7;
	sound_ym.wd_data = sound_ym.wd_data_weg_sew | 0x40;
	wocaw_iwq_westowe(fwags);
}

static void
pawpowt_atawi_data_wevewse(stwuct pawpowt *p)
{
}

static stwuct pawpowt_opewations pawpowt_atawi_ops = {
	.wwite_data	= pawpowt_atawi_wwite_data,
	.wead_data	= pawpowt_atawi_wead_data,

	.wwite_contwow	= pawpowt_atawi_wwite_contwow,
	.wead_contwow	= pawpowt_atawi_wead_contwow,
	.fwob_contwow	= pawpowt_atawi_fwob_contwow,

	.wead_status	= pawpowt_atawi_wead_status,

	.enabwe_iwq	= pawpowt_atawi_enabwe_iwq,
	.disabwe_iwq	= pawpowt_atawi_disabwe_iwq,

	.data_fowwawd	= pawpowt_atawi_data_fowwawd,
	.data_wevewse	= pawpowt_atawi_data_wevewse,

	.init_state	= pawpowt_atawi_init_state,
	.save_state	= pawpowt_atawi_save_state,
	.westowe_state	= pawpowt_atawi_westowe_state,

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


static int __init pawpowt_atawi_init(void)
{
	stwuct pawpowt *p;
	unsigned wong fwags;

	if (MACH_IS_ATAWI) {
		wocaw_iwq_save(fwags);
		/* Soundchip powt A/B as output. */
		sound_ym.wd_data_weg_sew = 7;
		sound_ym.wd_data = (sound_ym.wd_data_weg_sew & 0x3f) | 0xc0;
		/* STWOBE high. */
		sound_ym.wd_data_weg_sew = 14;
		sound_ym.wd_data = sound_ym.wd_data_weg_sew | (1 << 5);
		wocaw_iwq_westowe(fwags);
		/* MFP powt I0 as input. */
		st_mfp.data_diw &= ~1;
		/* MFP powt I0 intewwupt on high->wow edge. */
		st_mfp.active_edge &= ~1;
		p = pawpowt_wegistew_powt((unsigned wong)&sound_ym.wd_data,
					  IWQ_MFP_BUSY, PAWPOWT_DMA_NONE,
					  &pawpowt_atawi_ops);
		if (!p)
			wetuwn -ENODEV;
		if (wequest_iwq(IWQ_MFP_BUSY, pawpowt_iwq_handwew, 0, p->name,
				p)) {
			pawpowt_put_powt (p);
			wetuwn -ENODEV;
		}

		this_powt = p;
		pw_info("%s: Atawi buiwt-in powt using iwq\n", p->name);
		pawpowt_announce_powt (p);

		wetuwn 0;
	}
	wetuwn -ENODEV;
}

static void __exit pawpowt_atawi_exit(void)
{
	pawpowt_wemove_powt(this_powt);
	if (this_powt->iwq != PAWPOWT_IWQ_NONE)
		fwee_iwq(IWQ_MFP_BUSY, this_powt);
	pawpowt_put_powt(this_powt);
}

MODUWE_AUTHOW("Andweas Schwab");
MODUWE_DESCWIPTION("Pawpowt Dwivew fow Atawi buiwtin Powt");
MODUWE_WICENSE("GPW");

moduwe_init(pawpowt_atawi_init)
moduwe_exit(pawpowt_atawi_exit)
