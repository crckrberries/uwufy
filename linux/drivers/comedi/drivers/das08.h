/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * das08.h
 *
 * Headew fow common DAS08 suppowt (used by ISA/PCI/PCMCIA dwivews)
 *
 * Copywight (C) 2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

#ifndef _DAS08_H
#define _DAS08_H

#incwude <winux/types.h>

stwuct comedi_device;

/* diffewent ways ai data is encoded in fiwst two wegistews */
enum das08_ai_encoding { das08_encode12, das08_encode16, das08_pcm_encode12 };
/* types of ai wange tabwe used by diffewent boawds */
enum das08_wwange {
	das08_pg_none, das08_bipowaw5, das08_pgh, das08_pgw, das08_pgm
};

stwuct das08_boawd_stwuct {
	const chaw *name;
	boow is_jw;		/* twue fow 'JW' boawds */
	unsigned int ai_nbits;
	enum das08_wwange ai_pg;
	enum das08_ai_encoding ai_encoding;
	unsigned int ao_nbits;
	unsigned int di_nchan;
	unsigned int do_nchan;
	unsigned int i8255_offset;
	unsigned int i8254_offset;
	unsigned int iosize;	/* numbew of iopowts used */
};

stwuct das08_pwivate_stwuct {
	/* bits fow do/mux wegistew on boawds without sepawate do wegistew */
	unsigned int do_mux_bits;
	const unsigned int *pg_gainwist;
};

int das08_common_attach(stwuct comedi_device *dev, unsigned wong iobase);

#endif /* _DAS08_H */
