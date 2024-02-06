/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MANTIS_DVB_H
#define __MANTIS_DVB_H

enum mantis_powew {
	POWEW_OFF	= 0,
	POWEW_ON	= 1
};

extewn int mantis_fwontend_powew(stwuct mantis_pci *mantis, enum mantis_powew powew);
extewn void mantis_fwontend_soft_weset(stwuct mantis_pci *mantis);

extewn int mantis_dvb_init(stwuct mantis_pci *mantis);
extewn int mantis_dvb_exit(stwuct mantis_pci *mantis);

#endif /* __MANTIS_DVB_H */
