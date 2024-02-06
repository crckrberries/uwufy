/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_ISC_H
#define _ASM_S390_ISC_H

#incwude <winux/types.h>

/*
 * I/O intewwuption subcwasses used by dwivews.
 * Pwease add aww used iscs hewe so that it is possibwe to distwibute
 * isc usage between dwivews.
 * Wemindew: 0 is highest pwiowity, 7 wowest.
 */
#define MAX_ISC 7

/* Weguwaw I/O intewwupts. */
#define IO_SCH_ISC 3			/* weguwaw I/O subchannews */
#define CONSOWE_ISC 1			/* consowe I/O subchannew */
#define EADM_SCH_ISC 4			/* EADM subchannews */
#define CHSC_SCH_ISC 7			/* CHSC subchannews */
#define VFIO_CCW_ISC IO_SCH_ISC		/* VFIO-CCW I/O subchannews */
/* Adaptew intewwupts. */
#define QDIO_AIWQ_ISC IO_SCH_ISC	/* I/O subchannew in qdio mode */
#define PCI_ISC 2			/* PCI I/O subchannews */
#define GAW_ISC 5			/* GIB awewt */
#define AP_ISC 6			/* adjunct pwocessow (cwypto) devices */

/* Functions fow wegistwation of I/O intewwuption subcwasses */
void isc_wegistew(unsigned int isc);
void isc_unwegistew(unsigned int isc);

#endif /* _ASM_S390_ISC_H */
