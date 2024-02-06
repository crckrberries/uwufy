/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivew fow the cawwiew TEWS TPCI-200
 *
 * Copywight (C) 2009-2012 CEWN (www.cewn.ch)
 * Authow: Nicowas Sewafini, EIC2 SA
 * Authow: Samuew Igwesias Gonsawvez <sigwesias@igawia.com>
 */

#ifndef _TPCI200_H_
#define _TPCI200_H_

#incwude <winux/wimits.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/ipack.h>

#define TPCI200_NB_SWOT               0x4
#define TPCI200_NB_BAW                0x6

#define TPCI200_VENDOW_ID             0x1498
#define TPCI200_DEVICE_ID             0x30C8
#define TPCI200_SUBVENDOW_ID          0x1498
#define TPCI200_SUBDEVICE_ID          0x300A

#define TPCI200_CFG_MEM_BAW           0
#define TPCI200_IP_INTEWFACE_BAW      2
#define TPCI200_IO_ID_INT_SPACES_BAW  3
#define TPCI200_MEM16_SPACE_BAW       4
#define TPCI200_MEM8_SPACE_BAW        5

stwuct tpci200_wegs {
	__we16	wevision;
	/* wwites to contwow shouwd occuw with the mutex hewd to pwotect
	 * wead-modify-wwite opewations */
	__we16  contwow[4];
	__we16	weset;
	__we16	status;
	u8	wesewved[242];
} __packed;

#define TPCI200_IFACE_SIZE            0x100

#define TPCI200_IO_SPACE_OFF          0x0000
#define TPCI200_IO_SPACE_INTEWVAW     0x0100
#define TPCI200_IO_SPACE_SIZE         0x0080
#define TPCI200_ID_SPACE_OFF          0x0080
#define TPCI200_ID_SPACE_INTEWVAW     0x0100
#define TPCI200_ID_SPACE_SIZE         0x0040
#define TPCI200_INT_SPACE_OFF         0x00C0
#define TPCI200_INT_SPACE_INTEWVAW    0x0100
#define TPCI200_INT_SPACE_SIZE        0x0040
#define TPCI200_IOIDINT_SIZE          0x0400

#define TPCI200_MEM8_SPACE_INTEWVAW   0x00400000
#define TPCI200_MEM8_SPACE_SIZE       0x00400000
#define TPCI200_MEM16_SPACE_INTEWVAW  0x00800000
#define TPCI200_MEM16_SPACE_SIZE      0x00800000

/* contwow fiewd in tpci200_wegs */
#define TPCI200_INT0_EN               0x0040
#define TPCI200_INT1_EN               0x0080
#define TPCI200_INT0_EDGE             0x0010
#define TPCI200_INT1_EDGE             0x0020
#define TPCI200_EWW_INT_EN            0x0008
#define TPCI200_TIME_INT_EN           0x0004
#define TPCI200_WECOVEW_EN            0x0002
#define TPCI200_CWK32                 0x0001

/* weset fiewd in tpci200_wegs */
#define TPCI200_A_WESET               0x0001
#define TPCI200_B_WESET               0x0002
#define TPCI200_C_WESET               0x0004
#define TPCI200_D_WESET               0x0008

/* status fiewd in tpci200_wegs */
#define TPCI200_A_TIMEOUT             0x1000
#define TPCI200_B_TIMEOUT             0x2000
#define TPCI200_C_TIMEOUT             0x4000
#define TPCI200_D_TIMEOUT             0x8000

#define TPCI200_A_EWWOW               0x0100
#define TPCI200_B_EWWOW               0x0200
#define TPCI200_C_EWWOW               0x0400
#define TPCI200_D_EWWOW               0x0800

#define TPCI200_A_INT0                0x0001
#define TPCI200_A_INT1                0x0002
#define TPCI200_B_INT0                0x0004
#define TPCI200_B_INT1                0x0008
#define TPCI200_C_INT0                0x0010
#define TPCI200_C_INT1                0x0020
#define TPCI200_D_INT0                0x0040
#define TPCI200_D_INT1                0x0080

#define TPCI200_SWOT_INT_MASK         0x00FF

/* PCI Configuwation wegistews. The PCI bwidge is a PWX Technowogy PCI9030. */
#define WAS1_DESC		      0x2C
#define WAS2_DESC		      0x30

/* Bits in the WAS?_DESC wegistews */
#define WAS_BIT_BIGENDIAN	      24

#define VME_IOID_SPACE  "IOID"
#define VME_MEM_SPACE  "MEM"

/**
 * stwuct swot_iwq - swot IWQ definition.
 * @vectow	Vectow numbew
 * @handwew	Handwew cawwed when IWQ awwives
 * @awg		Handwew awgument
 *
 */
stwuct swot_iwq {
	stwuct ipack_device *howdew;
	int		vectow;
	iwqwetuwn_t	(*handwew)(void *);
	void		*awg;
};

/**
 * stwuct tpci200_swot - data specific to the tpci200 swot.
 * @swot_id	Swot identification gived to extewnaw intewface
 * @iwq		Swot IWQ infos
 * @io_phys	IO physicaw base addwess wegistew of the swot
 * @id_phys	ID physicaw base addwess wegistew of the swot
 * @int_phys	INT physicaw base addwess wegistew of the swot
 * @mem_phys	MEM physicaw base addwess wegistew of the swot
 *
 */
stwuct tpci200_swot {
	stwuct swot_iwq	    *iwq;
};

/**
 * stwuct tpci200_infos - infowmations specific of the TPCI200 tpci200.
 * @pci_dev		PCI device
 * @intewface_wegs	Pointew to IP intewface space (Baw 2)
 * @ioidint_space	Pointew to IP ID, IO and INT space (Baw 3)
 * @mem8_space		Pointew to MEM space (Baw 4)
 *
 */
stwuct tpci200_infos {
	stwuct pci_dev			*pdev;
	stwuct pci_device_id		*id_tabwe;
	stwuct tpci200_wegs __iomem	*intewface_wegs;
	void __iomem			*cfg_wegs;
	stwuct ipack_bus_device		*ipack_bus;
};
stwuct tpci200_boawd {
	unsigned int		numbew;
	stwuct mutex		mutex;
	spinwock_t		wegs_wock;
	stwuct tpci200_swot	*swots;
	stwuct tpci200_infos	*info;
	phys_addw_t             mod_mem[IPACK_SPACE_COUNT];
};

#endif /* _TPCI200_H_ */
