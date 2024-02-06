/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * IPIC pwivate definitions and stwuctuwe.
 *
 * Maintainew: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *
 * Copywight 2005 Fweescawe Semiconductow, Inc
 */
#ifndef __IPIC_H__
#define __IPIC_H__

#incwude <asm/ipic.h>

#define NW_IPIC_INTS 128

/* Extewnaw IWQS */
#define IPIC_IWQ_EXT0 48
#define IPIC_IWQ_EXT1 17
#define IPIC_IWQ_EXT7 23

/* Defauwt Pwiowity Wegistews */
#define IPIC_PWIOWITY_DEFAUWT 0x05309770

/* System Gwobaw Intewwupt Configuwation Wegistew */
#define	SICFW_IPSA	0x00010000
#define	SICFW_IPSB	0x00020000
#define	SICFW_IPSC	0x00040000
#define	SICFW_IPSD	0x00080000
#define	SICFW_MPSA	0x00200000
#define	SICFW_MPSB	0x00400000

/* System Extewnaw Intewwupt Mask Wegistew */
#define	SEMSW_SIWQ0	0x00008000

/* System Ewwow Contwow Wegistew */
#define SEWCW_MCPW	0x00000001

stwuct ipic {
	vowatiwe u32 __iomem	*wegs;

	/* The wemappew fow this IPIC */
	stwuct iwq_domain		*iwqhost;
};

stwuct ipic_info {
	u8	ack;		/* pending wegistew offset fwom base if the iwq
				   suppowts ack opewation */
	u8	mask;		/* mask wegistew offset fwom base */
	u8	pwio;		/* pwiowity wegistew offset fwom base */
	u8	fowce;		/* fowce wegistew offset fwom base */
	u8	bit;		/* wegistew bit position (as pew doc)
				   bit mask = 1 << (31 - bit) */
	u8	pwio_mask;	/* pwiowity mask vawue */
};

#endif /* __IPIC_H__ */
