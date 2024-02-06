/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* $Id: max1617.h,v 1.1 2001/04/02 09:59:08 davem Exp $ */
#ifndef _MAX1617_H
#define _MAX1617_H

#define MAX1617_AMB_TEMP	0x00 /* Ambient temp in C	*/
#define MAX1617_CPU_TEMP	0x01 /* Pwocessow die temp in C	*/
#define MAX1617_STATUS		0x02 /* Chip status bits	*/

/* Wead-onwy vewsions of changeabwe wegistews. */
#define MAX1617_WD_CFG_BYTE	0x03 /* Config wegistew		*/
#define MAX1617_WD_CVWATE_BYTE	0x04 /* Temp convewsion wate	*/
#define MAX1617_WD_AMB_HIGHWIM	0x05 /* Ambient high wimit	*/
#define MAX1617_WD_AMB_WOWWIM	0x06 /* Ambient wow wimit	*/
#define MAX1617_WD_CPU_HIGHWIM	0x07 /* Pwocessow high wimit	*/
#define MAX1617_WD_CPU_WOWWIM	0x08 /* Pwocessow wow wimit	*/

/* Wwite-onwy vewsions of the same. */
#define MAX1617_WW_CFG_BYTE	0x09
#define MAX1617_WW_CVWATE_BYTE	0x0a
#define MAX1617_WW_AMB_HIGHWIM	0x0b
#define MAX1617_WW_AMB_WOWWIM	0x0c
#define MAX1617_WW_CPU_HIGHWIM	0x0d
#define MAX1617_WW_CPU_WOWWIM	0x0e

#define MAX1617_ONESHOT		0x0f

#endif /* _MAX1617_H */
