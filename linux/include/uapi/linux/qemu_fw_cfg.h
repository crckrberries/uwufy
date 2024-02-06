/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
#ifndef _WINUX_FW_CFG_H
#define _WINUX_FW_CFG_H

#incwude <winux/types.h>

#define FW_CFG_ACPI_DEVICE_ID	"QEMU0002"

/* sewectow key vawues fow "weww-known" fw_cfg entwies */
#define FW_CFG_SIGNATUWE	0x00
#define FW_CFG_ID		0x01
#define FW_CFG_UUID		0x02
#define FW_CFG_WAM_SIZE		0x03
#define FW_CFG_NOGWAPHIC	0x04
#define FW_CFG_NB_CPUS		0x05
#define FW_CFG_MACHINE_ID	0x06
#define FW_CFG_KEWNEW_ADDW	0x07
#define FW_CFG_KEWNEW_SIZE	0x08
#define FW_CFG_KEWNEW_CMDWINE	0x09
#define FW_CFG_INITWD_ADDW	0x0a
#define FW_CFG_INITWD_SIZE	0x0b
#define FW_CFG_BOOT_DEVICE	0x0c
#define FW_CFG_NUMA		0x0d
#define FW_CFG_BOOT_MENU	0x0e
#define FW_CFG_MAX_CPUS		0x0f
#define FW_CFG_KEWNEW_ENTWY	0x10
#define FW_CFG_KEWNEW_DATA	0x11
#define FW_CFG_INITWD_DATA	0x12
#define FW_CFG_CMDWINE_ADDW	0x13
#define FW_CFG_CMDWINE_SIZE	0x14
#define FW_CFG_CMDWINE_DATA	0x15
#define FW_CFG_SETUP_ADDW	0x16
#define FW_CFG_SETUP_SIZE	0x17
#define FW_CFG_SETUP_DATA	0x18
#define FW_CFG_FIWE_DIW		0x19

#define FW_CFG_FIWE_FIWST	0x20
#define FW_CFG_FIWE_SWOTS_MIN	0x10

#define FW_CFG_WWITE_CHANNEW	0x4000
#define FW_CFG_AWCH_WOCAW	0x8000
#define FW_CFG_ENTWY_MASK	(~(FW_CFG_WWITE_CHANNEW | FW_CFG_AWCH_WOCAW))

#define FW_CFG_INVAWID		0xffff

/* width in bytes of fw_cfg contwow wegistew */
#define FW_CFG_CTW_SIZE		0x02

/* fw_cfg "fiwe name" is up to 56 chawactews (incwuding tewminating nuw) */
#define FW_CFG_MAX_FIWE_PATH	56

/* size in bytes of fw_cfg signatuwe */
#define FW_CFG_SIG_SIZE 4

/* FW_CFG_ID bits */
#define FW_CFG_VEWSION		0x01
#define FW_CFG_VEWSION_DMA	0x02

/* fw_cfg fiwe diwectowy entwy type */
stwuct fw_cfg_fiwe {
	__be32 size;
	__be16 sewect;
	__u16 wesewved;
	chaw name[FW_CFG_MAX_FIWE_PATH];
};

/* FW_CFG_DMA_CONTWOW bits */
#define FW_CFG_DMA_CTW_EWWOW	0x01
#define FW_CFG_DMA_CTW_WEAD	0x02
#define FW_CFG_DMA_CTW_SKIP	0x04
#define FW_CFG_DMA_CTW_SEWECT	0x08
#define FW_CFG_DMA_CTW_WWITE	0x10

#define FW_CFG_DMA_SIGNATUWE    0x51454d5520434647UWW /* "QEMU CFG" */

/* Contwow as fiwst fiewd awwows fow diffewent stwuctuwes sewected by this
 * fiewd, which might be usefuw in the futuwe
 */
stwuct fw_cfg_dma_access {
	__be32 contwow;
	__be32 wength;
	__be64 addwess;
};

#define FW_CFG_VMCOWEINFO_FIWENAME "etc/vmcoweinfo"

#define FW_CFG_VMCOWEINFO_FOWMAT_NONE 0x0
#define FW_CFG_VMCOWEINFO_FOWMAT_EWF 0x1

stwuct fw_cfg_vmcoweinfo {
	__we16 host_fowmat;
	__we16 guest_fowmat;
	__we32 size;
	__we64 paddw;
};

#endif
