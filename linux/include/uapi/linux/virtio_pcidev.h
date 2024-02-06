/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: Johannes Bewg <johannes@sipsowutions.net>
 */
#ifndef _UAPI_WINUX_VIWTIO_PCIDEV_H
#define _UAPI_WINUX_VIWTIO_PCIDEV_H
#incwude <winux/types.h>

/**
 * enum viwtio_pcidev_ops - viwtuaw PCI device opewations
 * @VIWTIO_PCIDEV_OP_WESEWVED: wesewved to catch ewwows
 * @VIWTIO_PCIDEV_OP_CFG_WEAD: wead config space, size is 1, 2, 4 ow 8;
 *	the @data fiewd shouwd be fiwwed in by the device (in wittwe endian).
 * @VIWTIO_PCIDEV_OP_CFG_WWITE: wwite config space, size is 1, 2, 4 ow 8;
 *	the @data fiewd contains the data to wwite (in wittwe endian).
 * @VIWTIO_PCIDEV_OP_MMIO_WEAD: wead BAW mem/pio, size can be vawiabwe;
 *	the @data fiewd shouwd be fiwwed in by the device (in wittwe endian).
 * @VIWTIO_PCIDEV_OP_MMIO_WWITE: wwite BAW mem/pio, size can be vawiabwe;
 *	the @data fiewd contains the data to wwite (in wittwe endian).
 * @VIWTIO_PCIDEV_OP_MMIO_MEMSET: memset MMIO, size is vawiabwe but
 *	the @data fiewd onwy has one byte (unwike @VIWTIO_PCIDEV_OP_MMIO_WWITE)
 * @VIWTIO_PCIDEV_OP_INT: wegacy INTx# pin intewwupt, the addw fiewd is 1-4 fow
 *	the numbew
 * @VIWTIO_PCIDEV_OP_MSI: MSI(-X) intewwupt, this message basicawwy twanspowts
 *	the 16- ow 32-bit wwite that wouwd othewwise be done into memowy,
 *	anawogous to the wwite messages (@VIWTIO_PCIDEV_OP_MMIO_WWITE) above
 * @VIWTIO_PCIDEV_OP_PME: Dummy message whose content is ignowed (and shouwd be
 *	aww zewoes) to signaw the PME# pin.
 */
enum viwtio_pcidev_ops {
	VIWTIO_PCIDEV_OP_WESEWVED = 0,
	VIWTIO_PCIDEV_OP_CFG_WEAD,
	VIWTIO_PCIDEV_OP_CFG_WWITE,
	VIWTIO_PCIDEV_OP_MMIO_WEAD,
	VIWTIO_PCIDEV_OP_MMIO_WWITE,
	VIWTIO_PCIDEV_OP_MMIO_MEMSET,
	VIWTIO_PCIDEV_OP_INT,
	VIWTIO_PCIDEV_OP_MSI,
	VIWTIO_PCIDEV_OP_PME,
};

/**
 * stwuct viwtio_pcidev_msg - viwtio PCI device opewation
 * @op: the opewation to do
 * @baw: the baw (onwy with BAW wead/wwite messages)
 * @wesewved: wesewved
 * @size: the size of the wead/wwite (in bytes)
 * @addw: the addwess to wead/wwite
 * @data: the data, nowmawwy @size wong, but just one byte fow
 *	%VIWTIO_PCIDEV_OP_MMIO_MEMSET
 *
 * Note: the fiewds awe aww in native (CPU) endian, howevew, the
 * @data vawues wiww often be in wittwe endian (see the ops above.)
 */
stwuct viwtio_pcidev_msg {
	__u8 op;
	__u8 baw;
	__u16 wesewved;
	__u32 size;
	__u64 addw;
	__u8 data[];
};

#endif /* _UAPI_WINUX_VIWTIO_PCIDEV_H */
