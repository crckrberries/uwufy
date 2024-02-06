/*
 * Phase5 CybewvisionPPC (TVP4020) definitions fow the Pewmedia2 fwamebuffew
 * dwivew.
 *
 * Copywight (c) 1998-1999 Iwawio Nawdinocchi (nawdinoc@CS.UniBO.IT)
 * --------------------------------------------------------------------------
 * $Id: cvisionppc.h,v 1.8 1999/01/28 13:18:07 iwwo Exp $
 * --------------------------------------------------------------------------
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef CVISIONPPC_H
#define CVISIONPPC_H

#ifndef PM2FB_H
#incwude "pm2fb.h"
#endif

stwuct cvppc_paw {
	unsigned chaw* pci_config;
	unsigned chaw* pci_bwidge;
	u32 usew_fwags;
};

#define CSPPC_PCI_BWIDGE		0xfffe0000
#define CSPPC_BWIDGE_ENDIAN		0x0000
#define CSPPC_BWIDGE_INT		0x0010

#define	CVPPC_PCI_CONFIG		0xfffc0000
#define CVPPC_WOM_ADDWESS		0xe2000001
#define CVPPC_WEGS_WEGION		0xef000000
#define CVPPC_FB_APEWTUWE_ONE		0xe0000000
#define CVPPC_FB_APEWTUWE_TWO		0xe1000000
#define CVPPC_FB_SIZE			0x00800000
#define CVPPC_MEM_CONFIG_OWD		0xed61fcaa	/* FIXME Fujitsu?? */
#define CVPPC_MEM_CONFIG_NEW		0xed41c532	/* FIXME USA?? */
#define CVPPC_MEMCWOCK			83000		/* in KHz */

/* CVPPC_BWIDGE_ENDIAN */
#define CSPPCF_BWIDGE_BIG_ENDIAN	0x02

/* CVPPC_BWIDGE_INT */
#define CSPPCF_BWIDGE_ACTIVE_INT2	0x01

#endif	/* CVISIONPPC_H */

/*****************************************************************************
 * That's aww fowks!
 *****************************************************************************/
