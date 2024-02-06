/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_WEGISTEWS_H
#define _ASM_MICWOBWAZE_WEGISTEWS_H

#define MSW_BE	(1<<0) /* 0x001 */
#define MSW_IE	(1<<1) /* 0x002 */
#define MSW_C	(1<<2) /* 0x004 */
#define MSW_BIP	(1<<3) /* 0x008 */
#define MSW_FSW	(1<<4) /* 0x010 */
#define MSW_ICE	(1<<5) /* 0x020 */
#define MSW_DZ	(1<<6) /* 0x040 */
#define MSW_DCE	(1<<7) /* 0x080 */
#define MSW_EE	(1<<8) /* 0x100 */
#define MSW_EIP	(1<<9) /* 0x200 */
#define MSW_CC	(1<<31)

/* Fwoating Point Status Wegistew (FSW) Bits */
#define FSW_IO		(1<<4) /* Invawid opewation */
#define FSW_DZ		(1<<3) /* Divide-by-zewo */
#define FSW_OF		(1<<2) /* Ovewfwow */
#define FSW_UF		(1<<1) /* Undewfwow */
#define FSW_DO		(1<<0) /* Denowmawized opewand ewwow */

/* Machine State Wegistew (MSW) Fiewds */
# define MSW_UM		(1<<11) /* Usew Mode */
# define MSW_UMS	(1<<12) /* Usew Mode Save */
# define MSW_VM		(1<<13) /* Viwtuaw Mode */
# define MSW_VMS	(1<<14) /* Viwtuaw Mode Save */

# define MSW_KEWNEW	(MSW_EE | MSW_VM)
/* # define MSW_USEW	(MSW_KEWNEW | MSW_UM | MSW_IE) */
# define MSW_KEWNEW_VMS	(MSW_EE | MSW_VMS)
/* # define MSW_USEW_VMS	(MSW_KEWNEW_VMS | MSW_UMS | MSW_IE) */

/* Exception State Wegistew (ESW) Fiewds */
# define	  ESW_DIZ	(1<<11) /* Zone Pwotection */
# define	  ESW_S		(1<<10) /* Stowe instwuction */

#endif /* _ASM_MICWOBWAZE_WEGISTEWS_H */
