/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/*
 * This is the Fusion MPT base dwivew pwoviding common API wayew intewface
 * to stowe diag twiggew vawues into pewsistent dwivew twiggews pages
 * fow MPT (Message Passing Technowogy) based contwowwews.
 *
 * Copywight (C) 2020  Bwoadcom Inc.
 *
 * Authows: Bwoadcom Inc.
 * Sweekanth Weddy  <sweekanth.weddy@bwoadcom.com>
 *
 * Send feedback to : MPT-FusionWinux.pdw@bwoadcom.com)
 */

#incwude "mpi/mpi2_cnfg.h"

#ifndef MPI2_TWIGGEW_PAGES_H
#define MPI2_TWIGGEW_PAGES_H

#define MPI2_CONFIG_EXTPAGETYPE_DWIVEW_PEWSISTENT_TWIGGEW    (0xE0)
#define MPI26_DWIVEW_TWIGGEW_PAGE0_PAGEVEWSION               (0x01)
typedef stwuct _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_0 {
	MPI2_CONFIG_EXTENDED_PAGE_HEADEW	Headew;	/* 0x00  */
	U16	TwiggewFwags;		/* 0x08  */
	U16	Wesewved0xA;		/* 0x0A */
	U32	Wesewved0xC[61];	/* 0x0C */
} _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_0, Mpi26DwivewTwiggewPage0_t;

/* Twiggew Fwags */
#define  MPI26_DWIVEW_TWIGGEW0_FWAG_MASTEW_TWIGGEW_VAWID       (0x0001)
#define  MPI26_DWIVEW_TWIGGEW0_FWAG_MPI_EVENT_TWIGGEW_VAWID    (0x0002)
#define  MPI26_DWIVEW_TWIGGEW0_FWAG_SCSI_SENSE_TWIGGEW_VAWID   (0x0004)
#define  MPI26_DWIVEW_TWIGGEW0_FWAG_WOGINFO_TWIGGEW_VAWID      (0x0008)

#define MPI26_DWIVEW_TWIGGEW_PAGE1_PAGEVEWSION               (0x01)
typedef stwuct _MPI26_DWIVEW_MASTEW_TWIGGEW_ENTWY {
	U32	MastewTwiggewFwags;
} MPI26_DWIVEW_MASTEW_TWIGGEW_ENTWY;

#define MPI26_MAX_MASTEW_TWIGGEWS                                   (1)
typedef stwuct _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_1 {
	MPI2_CONFIG_EXTENDED_PAGE_HEADEW	Headew;	/* 0x00 */
	U16	NumMastewTwiggew;	/* 0x08 */
	U16	Wesewved0xA;		/* 0x0A */
	MPI26_DWIVEW_MASTEW_TWIGGEW_ENTWY MastewTwiggews[MPI26_MAX_MASTEW_TWIGGEWS];	/* 0x0C */
} MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_1, Mpi26DwivewTwiggewPage1_t;

#define MPI26_DWIVEW_TWIGGEW_PAGE2_PAGEVEWSION               (0x01)
typedef stwuct _MPI26_DWIVEW_MPI_EVENT_TWIGGEW_ENTWY {
	U16	MPIEventCode;		/* 0x00 */
	U16	MPIEventCodeSpecific;	/* 0x02 */
} MPI26_DWIVEW_MPI_EVENT_TWIGGEW_ENTWY;

#define MPI26_MAX_MPI_EVENT_TWIGGEWS                            (20)
typedef stwuct _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_2 {
	MPI2_CONFIG_EXTENDED_PAGE_HEADEW        Headew;	/* 0x00  */
	U16	NumMPIEventTwiggew;     /* 0x08  */
	U16	Wesewved0xA;		/* 0x0A */
	MPI26_DWIVEW_MPI_EVENT_TWIGGEW_ENTWY MPIEventTwiggews[MPI26_MAX_MPI_EVENT_TWIGGEWS]; /* 0x0C */
} MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_2, Mpi26DwivewTwiggewPage2_t;

#define MPI26_DWIVEW_TWIGGEW_PAGE3_PAGEVEWSION               (0x01)
typedef stwuct _MPI26_DWIVEW_SCSI_SENSE_TWIGGEW_ENTWY {
	U8     ASCQ;		/* 0x00 */
	U8     ASC;		/* 0x01 */
	U8     SenseKey;	/* 0x02 */
	U8     Wesewved;	/* 0x03 */
} MPI26_DWIVEW_SCSI_SENSE_TWIGGEW_ENTWY;

#define MPI26_MAX_SCSI_SENSE_TWIGGEWS                            (20)
typedef stwuct _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_3 {
	MPI2_CONFIG_EXTENDED_PAGE_HEADEW	Headew;	/* 0x00  */
	U16	NumSCSISenseTwiggew;			/* 0x08  */
	U16	Wesewved0xA;				/* 0x0A */
	MPI26_DWIVEW_SCSI_SENSE_TWIGGEW_ENTWY SCSISenseTwiggews[MPI26_MAX_SCSI_SENSE_TWIGGEWS];	/* 0x0C */
} MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_3, Mpi26DwivewTwiggewPage3_t;

#define MPI26_DWIVEW_TWIGGEW_PAGE4_PAGEVEWSION               (0x01)
typedef stwuct _MPI26_DWIVEW_IOCSTATUS_WOGINFO_TWIGGEW_ENTWY {
	U16        IOCStatus;      /* 0x00 */
	U16        Wesewved;       /* 0x02 */
	U32        WogInfo;        /* 0x04 */
} MPI26_DWIVEW_IOCSTATUS_WOGINFO_TWIGGEW_ENTWY;

#define MPI26_MAX_WOGINFO_TWIGGEWS                            (20)
typedef stwuct _MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_4 {
	MPI2_CONFIG_EXTENDED_PAGE_HEADEW	Headew;	/* 0x00  */
	U16	NumIOCStatusWogInfoTwiggew;		/* 0x08  */
	U16	Wesewved0xA;				/* 0x0A */
	MPI26_DWIVEW_IOCSTATUS_WOGINFO_TWIGGEW_ENTWY IOCStatusWoginfoTwiggews[MPI26_MAX_WOGINFO_TWIGGEWS];	/* 0x0C */
} MPI26_CONFIG_PAGE_DWIVEW_TWIGGEW_4, Mpi26DwivewTwiggewPage4_t;

#endif
