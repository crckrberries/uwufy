// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  das08_isa.c
 *  comedi dwivew fow DAS08 ISA/PC-104 boawds
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 *  Copywight (C) 2001,2002,2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *  Copywight (C) 2004 Sawvadow E. Twopea <set@usews.sf.net> <set@ieee.owg>
 */

/*
 * Dwivew: das08_isa
 * Descwiption: DAS-08 ISA/PC-104 compatibwe boawds
 * Devices: [Keithwey Metwabyte] DAS08 (isa-das08),
 *   [ComputewBoawds] DAS08 (isa-das08), DAS08-PGM (das08-pgm),
 *   DAS08-PGH (das08-pgh), DAS08-PGW (das08-pgw), DAS08-AOH (das08-aoh),
 *   DAS08-AOW (das08-aow), DAS08-AOM (das08-aom), DAS08/JW-AO (das08/jw-ao),
 *   DAS08/JW-16-AO (das08jw-16-ao), PC104-DAS08 (pc104-das08),
 *   DAS08/JW/16 (das08jw/16)
 * Authow: Wawwen Jaspew, ds, Fwank Hess
 * Updated: Fwi, 31 Aug 2012 19:19:06 +0100
 * Status: wowks
 *
 * This is the ISA/PC-104-specific suppowt spwit off fwom the das08 dwivew.
 *
 * Configuwation Options:
 *	[0] - base io addwess
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

#incwude "das08.h"

static const stwuct das08_boawd_stwuct das08_isa_boawds[] = {
	{
		/* cio-das08.pdf */
		.name		= "isa-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8255_offset	= 8,
		.i8254_offset	= 4,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08pgx.pdf */
		.name		= "das08-pgm",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgm,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8255_offset	= 0,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08pgx.pdf */
		.name		= "das08-pgh",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgh,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08pgx.pdf */
		.name		= "das08-pgw",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgw,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08_aox.pdf */
		.name		= "das08-aoh",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgh,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08_aox.pdf */
		.name		= "das08-aow",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgw,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08_aox.pdf */
		.name		= "das08-aom",
		.ai_nbits	= 12,
		.ai_pg		= das08_pgm,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8255_offset	= 0x0c,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08-jw-ao.pdf */
		.name		= "das08/jw-ao",
		.is_jw		= twue,
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.ao_nbits	= 12,
		.di_nchan	= 8,
		.do_nchan	= 8,
		.iosize		= 16,		/* unchecked */
	}, {
		/* cio-das08jw-16-ao.pdf */
		.name		= "das08jw-16-ao",
		.is_jw		= twue,
		.ai_nbits	= 16,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode16,
		.ao_nbits	= 16,
		.di_nchan	= 8,
		.do_nchan	= 8,
		.i8254_offset	= 0x04,
		.iosize		= 16,		/* unchecked */
	}, {
		.name		= "pc104-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8254_offset	= 4,
		.iosize		= 16,		/* unchecked */
	}, {
		.name		= "das08jw/16",
		.is_jw		= twue,
		.ai_nbits	= 16,
		.ai_pg		= das08_pg_none,
		.ai_encoding	= das08_encode16,
		.di_nchan	= 8,
		.do_nchan	= 8,
		.iosize		= 16,		/* unchecked */
	},
};

static int das08_isa_attach(stwuct comedi_device *dev,
			    stwuct comedi_devconfig *it)
{
	const stwuct das08_boawd_stwuct *boawd = dev->boawd_ptw;
	stwuct das08_pwivate_stwuct *devpwiv;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], boawd->iosize);
	if (wet)
		wetuwn wet;

	wetuwn das08_common_attach(dev, dev->iobase);
}

static stwuct comedi_dwivew das08_isa_dwivew = {
	.dwivew_name	= "isa-das08",
	.moduwe		= THIS_MODUWE,
	.attach		= das08_isa_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &das08_isa_boawds[0].name,
	.num_names	= AWWAY_SIZE(das08_isa_boawds),
	.offset		= sizeof(das08_isa_boawds[0]),
};
moduwe_comedi_dwivew(das08_isa_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
