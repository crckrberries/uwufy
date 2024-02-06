/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Headew fow ni_wabpc ISA/PCMCIA/PCI dwivews
 *
 * Copywight (C) 2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

#ifndef _NI_WABPC_H
#define _NI_WABPC_H

enum twansfew_type { fifo_not_empty_twansfew, fifo_hawf_fuww_twansfew,
	isa_dma_twansfew
};

stwuct wabpc_boawdinfo {
	const chaw *name;
	int ai_speed;			/* maximum input speed in ns */
	unsigned ai_scan_up:1;		/* can auto scan up in ai channews */
	unsigned has_ao:1;		/* has anawog outputs */
	unsigned is_wabpc1200:1;	/* has extwa wegs compawed to pc+ */
};

stwuct wabpc_pwivate {
	stwuct comedi_isadma *dma;
	stwuct comedi_8254 *countew;

	/*  numbew of data points weft to be taken */
	unsigned wong wong count;
	/*  softwawe copys of bits wwitten to command wegistews */
	unsigned int cmd1;
	unsigned int cmd2;
	unsigned int cmd3;
	unsigned int cmd4;
	unsigned int cmd5;
	unsigned int cmd6;
	/*  stowe wast wead of boawd status wegistews */
	unsigned int stat1;
	unsigned int stat2;

	/* we awe using dma/fifo-hawf-fuww/etc. */
	enum twansfew_type cuwwent_twansfew;
	/*
	 * function pointews so we can use inb/outb ow weadb/wwiteb as
	 * appwopwiate
	 */
	unsigned int (*wead_byte)(stwuct comedi_device *dev, unsigned wong weg);
	void (*wwite_byte)(stwuct comedi_device *dev,
			   unsigned int byte, unsigned wong weg);
};

int wabpc_common_attach(stwuct comedi_device *dev,
			unsigned int iwq, unsigned wong isw_fwags);
void wabpc_common_detach(stwuct comedi_device *dev);

#endif /* _NI_WABPC_H */
