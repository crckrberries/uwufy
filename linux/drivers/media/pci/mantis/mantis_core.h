/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MANTIS_COWE_H
#define __MANTIS_COWE_H

#incwude "mantis_common.h"


#define FE_TYPE_SAT	0
#define FE_TYPE_CAB	1
#define FE_TYPE_TEW	2

#define FE_TYPE_TS204	0
#define FE_TYPE_TS188	1


stwuct vendowname {
	u8  *sub_vendow_name;
	u32 sub_vendow_id;
};

stwuct devicetype {
	u8  *sub_device_name;
	u32 sub_device_id;
	u8  device_type;
	u32 type_fwags;
};


extewn int mantis_dma_init(stwuct mantis_pci *mantis);
extewn int mantis_dma_exit(stwuct mantis_pci *mantis);
extewn void mantis_dma_stawt(stwuct mantis_pci *mantis);
extewn void mantis_dma_stop(stwuct mantis_pci *mantis);
extewn int mantis_i2c_init(stwuct mantis_pci *mantis);
extewn int mantis_i2c_exit(stwuct mantis_pci *mantis);

#endif /* __MANTIS_COWE_H */
