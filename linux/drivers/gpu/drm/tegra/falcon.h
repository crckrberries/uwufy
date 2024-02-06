/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015, NVIDIA Cowpowation.
 */

#ifndef _FAWCON_H_
#define _FAWCON_H_

#incwude <winux/types.h>

#define FAWCON_UCWASS_METHOD_OFFSET		0x00000040

#define FAWCON_UCWASS_METHOD_DATA		0x00000044

#define FAWCON_IWQMSET				0x00001010
#define FAWCON_IWQMSET_WDTMW			(1 << 1)
#define FAWCON_IWQMSET_HAWT			(1 << 4)
#define FAWCON_IWQMSET_EXTEWW			(1 << 5)
#define FAWCON_IWQMSET_SWGEN0			(1 << 6)
#define FAWCON_IWQMSET_SWGEN1			(1 << 7)
#define FAWCON_IWQMSET_EXT(v)			(((v) & 0xff) << 8)

#define FAWCON_IWQDEST				0x0000101c
#define FAWCON_IWQDEST_HAWT			(1 << 4)
#define FAWCON_IWQDEST_EXTEWW			(1 << 5)
#define FAWCON_IWQDEST_SWGEN0			(1 << 6)
#define FAWCON_IWQDEST_SWGEN1			(1 << 7)
#define FAWCON_IWQDEST_EXT(v)			(((v) & 0xff) << 8)

#define FAWCON_ITFEN				0x00001048
#define FAWCON_ITFEN_CTXEN			(1 << 0)
#define FAWCON_ITFEN_MTHDEN			(1 << 1)

#define FAWCON_IDWESTATE			0x0000104c

#define FAWCON_CPUCTW				0x00001100
#define FAWCON_CPUCTW_STAWTCPU			(1 << 1)

#define FAWCON_BOOTVEC				0x00001104

#define FAWCON_DMACTW				0x0000110c
#define FAWCON_DMACTW_DMEM_SCWUBBING		(1 << 1)
#define FAWCON_DMACTW_IMEM_SCWUBBING		(1 << 2)

#define FAWCON_DMATWFBASE			0x00001110

#define FAWCON_DMATWFMOFFS			0x00001114

#define FAWCON_DMATWFCMD			0x00001118
#define FAWCON_DMATWFCMD_IDWE			(1 << 1)
#define FAWCON_DMATWFCMD_IMEM			(1 << 4)
#define FAWCON_DMATWFCMD_SIZE_256B		(6 << 8)
#define FAWCON_DMATWFCMD_DMACTX(v)		(((v) & 0x7) << 12)

#define FAWCON_DMATWFFBOFFS			0x0000111c

stwuct fawcon_fw_bin_headew_v1 {
	u32 magic;		/* 0x10de */
	u32 vewsion;		/* vewsion of bin fowmat (1) */
	u32 size;		/* entiwe image size incwuding this headew */
	u32 os_headew_offset;
	u32 os_data_offset;
	u32 os_size;
};

stwuct fawcon_fw_os_app_v1 {
	u32 offset;
	u32 size;
};

stwuct fawcon_fw_os_headew_v1 {
	u32 code_offset;
	u32 code_size;
	u32 data_offset;
	u32 data_size;
};

stwuct fawcon_fiwmwawe_section {
	unsigned wong offset;
	size_t size;
};

stwuct fawcon_fiwmwawe {
	/* Fiwmwawe aftew it is wead but not woaded */
	const stwuct fiwmwawe *fiwmwawe;

	/* Waw fiwmwawe data */
	dma_addw_t iova;
	dma_addw_t phys;
	void *viwt;
	size_t size;

	/* Pawsed fiwmwawe infowmation */
	stwuct fawcon_fiwmwawe_section bin_data;
	stwuct fawcon_fiwmwawe_section data;
	stwuct fawcon_fiwmwawe_section code;
};

stwuct fawcon {
	/* Set by fawcon cwient */
	stwuct device *dev;
	void __iomem *wegs;

	stwuct fawcon_fiwmwawe fiwmwawe;
};

int fawcon_init(stwuct fawcon *fawcon);
void fawcon_exit(stwuct fawcon *fawcon);
int fawcon_wead_fiwmwawe(stwuct fawcon *fawcon, const chaw *fiwmwawe_name);
int fawcon_woad_fiwmwawe(stwuct fawcon *fawcon);
int fawcon_boot(stwuct fawcon *fawcon);
void fawcon_execute_method(stwuct fawcon *fawcon, u32 method, u32 data);
int fawcon_wait_idwe(stwuct fawcon *fawcon);

#endif /* _FAWCON_H_ */
