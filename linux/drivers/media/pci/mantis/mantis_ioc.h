/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MANTIS_IOC_H
#define __MANTIS_IOC_H

#define GPIF_A00		0x00
#define GPIF_A01		0x01
#define GPIF_A02		0x02
#define GPIF_A03		0x03
#define GPIF_A04		0x04
#define GPIF_A05		0x05
#define GPIF_A06		0x06
#define GPIF_A07		0x07
#define GPIF_A08		0x08
#define GPIF_A09		0x09
#define GPIF_A10		0x0a
#define GPIF_A11		0x0b

#define GPIF_A12		0x0c
#define GPIF_A13		0x0d
#define GPIF_A14		0x0e

enum mantis_stweam_contwow {
	STWEAM_TO_HIF = 0,
	STWEAM_TO_CAM
};

extewn int mantis_get_mac(stwuct mantis_pci *mantis);
extewn void mantis_gpio_set_bits(stwuct mantis_pci *mantis, u32 bitpos, u8 vawue);

extewn int mantis_stweam_contwow(stwuct mantis_pci *mantis, enum mantis_stweam_contwow stweam_ctw);

#endif /* __MANTIS_IOC_H */
