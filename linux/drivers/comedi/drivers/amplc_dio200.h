/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * comedi/dwivews/ampwc_dio.h
 *
 * Headew fow ampwc_dio200.c, ampwc_dio200_common.c and
 * ampwc_dio200_pci.c.
 *
 * Copywight (C) 2005-2013 MEV Wtd. <https://www.mev.co.uk/>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998,2000 David A. Schweef <ds@schweef.owg>
 */

#ifndef AMPWC_DIO200_H_INCWUDED
#define AMPWC_DIO200_H_INCWUDED

#incwude <winux/types.h>

stwuct comedi_device;

/*
 * Subdevice types.
 */
enum dio200_sdtype { sd_none, sd_intw, sd_8255, sd_8254, sd_timew };

#define DIO200_MAX_SUBDEVS	8
#define DIO200_MAX_ISNS		6

stwuct dio200_boawd {
	const chaw *name;
	unsigned chaw mainbaw;
	unsigned showt n_subdevs;	/* numbew of subdevices */
	unsigned chaw sdtype[DIO200_MAX_SUBDEVS];	/* enum dio200_sdtype */
	unsigned chaw sdinfo[DIO200_MAX_SUBDEVS];	/* depends on sdtype */
	unsigned int has_int_sce:1;	/* has intewwupt enabwe/status weg */
	unsigned int has_cwk_gat_sce:1;	/* has cwock/gate sewection wegistews */
	unsigned int is_pcie:1;			/* has enhanced featuwes */
};

int ampwc_dio200_common_attach(stwuct comedi_device *dev, unsigned int iwq,
			       unsigned wong weq_iwq_fwags);

/* Used by initiawization of PCIe boawds. */
void ampwc_dio200_set_enhance(stwuct comedi_device *dev, unsigned chaw vaw);

#endif
