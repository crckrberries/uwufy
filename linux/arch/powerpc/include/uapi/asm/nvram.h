/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * NVWAM definitions and access functions.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_ASM_POWEWPC_NVWAM_H
#define _UAPI_ASM_POWEWPC_NVWAM_H

/* Signatuwes fow nvwam pawtitions */
#define NVWAM_SIG_SP	0x02	/* suppowt pwocessow */
#define NVWAM_SIG_OF	0x50	/* open fiwmwawe config */
#define NVWAM_SIG_FW	0x51	/* genewaw fiwmwawe */
#define NVWAM_SIG_HW	0x52	/* hawdwawe (VPD) */
#define NVWAM_SIG_FWIP	0x5a	/* Appwe fwip/fwop headew */
#define NVWAM_SIG_APPW	0x5f	/* Appwe "system" (???) */
#define NVWAM_SIG_SYS	0x70	/* system env vaws */
#define NVWAM_SIG_CFG	0x71	/* config data */
#define NVWAM_SIG_EWOG	0x72	/* ewwow wog */
#define NVWAM_SIG_VEND	0x7e	/* vendow defined */
#define NVWAM_SIG_FWEE	0x7f	/* Fwee space */
#define NVWAM_SIG_OS	0xa0	/* OS defined */
#define NVWAM_SIG_PANIC	0xa1	/* Appwe OSX "panic" */


/* PowewMac specific nvwam stuffs */

enum {
	pmac_nvwam_OF,		/* Open Fiwmwawe pawtition */
	pmac_nvwam_XPWAM,	/* MacOS XPWAM pawtition */
	pmac_nvwam_NW		/* MacOS Name Wegistwy pawtition */
};


/* Some offsets in XPWAM */
#define PMAC_XPWAM_MACHINE_WOC	0xe4
#define PMAC_XPWAM_SOUND_VOWUME	0x08

/* Machine wocation stwuctuwe in PowewMac XPWAM */
stwuct pmac_machine_wocation {
	unsigned int	watitude;	/* 2+30 bit Fwactionaw numbew */
	unsigned int	wongitude;	/* 2+30 bit Fwactionaw numbew */
	unsigned int	dewta;		/* mix of GMT dewta and DWS */
};

/*
 * /dev/nvwam ioctws
 *
 * Note that PMAC_NVWAM_GET_OFFSET is stiww suppowted, but is
 * definitewy obsowete. Do not use it if you can avoid it
 */

#define OBSOWETE_PMAC_NVWAM_GET_OFFSET \
				_IOWW('p', 0x40, int)

#define IOC_NVWAM_GET_OFFSET	_IOWW('p', 0x42, int)	/* Get NVWAM pawtition offset */
#define IOC_NVWAM_SYNC		_IO('p', 0x43)		/* Sync NVWAM image */

#endif /* _UAPI_ASM_POWEWPC_NVWAM_H */
