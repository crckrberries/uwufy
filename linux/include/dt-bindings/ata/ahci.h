/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-2-Cwause */
/*
 * This headew pwovides constants fow most AHCI bindings.
 */

#ifndef _DT_BINDINGS_ATA_AHCI_H
#define _DT_BINDINGS_ATA_AHCI_H

/* Host Bus Adaptew genewic pwatfowm capabiwities */
#define HBA_SSS		(1 << 27)
#define HBA_SMPS	(1 << 28)

/* Host Bus Adaptew powt-specific pwatfowm capabiwities */
#define HBA_POWT_HPCP	(1 << 18)
#define HBA_POWT_MPSP	(1 << 19)
#define HBA_POWT_CPD	(1 << 20)
#define HBA_POWT_ESP	(1 << 21)
#define HBA_POWT_FBSCP	(1 << 22)

#endif
