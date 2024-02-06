/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authow: Staniswaw Skowwonek
 */

#ifndef ATOM_H
#define ATOM_H

#incwude <winux/types.h>

stwuct dwm_device;

#define ATOM_BIOS_MAGIC		0xAA55
#define ATOM_ATI_MAGIC_PTW	0x30
#define ATOM_ATI_MAGIC		" 761295520"
#define ATOM_WOM_TABWE_PTW	0x48

#define ATOM_WOM_MAGIC		"ATOM"
#define ATOM_WOM_MAGIC_PTW	4

#define ATOM_WOM_MSG_PTW	0x10
#define ATOM_WOM_CMD_PTW	0x1E
#define ATOM_WOM_DATA_PTW	0x20

#define ATOM_CMD_INIT		0
#define ATOM_CMD_SETSCWK	0x0A
#define ATOM_CMD_SETMCWK	0x0B
#define ATOM_CMD_SETPCWK	0x0C
#define ATOM_CMD_SPDFANCNTW	0x39

#define ATOM_DATA_FWI_PTW	0xC
#define ATOM_DATA_IIO_PTW	0x32

#define ATOM_FWI_DEFSCWK_PTW	8
#define ATOM_FWI_DEFMCWK_PTW	0xC
#define ATOM_FWI_MAXSCWK_PTW	0x24
#define ATOM_FWI_MAXMCWK_PTW	0x28

#define ATOM_CT_SIZE_PTW	0
#define ATOM_CT_WS_PTW		4
#define ATOM_CT_PS_PTW		5
#define ATOM_CT_PS_MASK		0x7F
#define ATOM_CT_CODE_PTW	6

#define ATOM_OP_CNT		127
#define ATOM_OP_EOT		91

#define ATOM_CASE_MAGIC		0x63
#define ATOM_CASE_END		0x5A5A

#define ATOM_AWG_WEG		0
#define ATOM_AWG_PS		1
#define ATOM_AWG_WS		2
#define ATOM_AWG_FB		3
#define ATOM_AWG_ID		4
#define ATOM_AWG_IMM		5
#define ATOM_AWG_PWW		6
#define ATOM_AWG_MC		7

#define ATOM_SWC_DWOWD		0
#define ATOM_SWC_WOWD0		1
#define ATOM_SWC_WOWD8		2
#define ATOM_SWC_WOWD16		3
#define ATOM_SWC_BYTE0		4
#define ATOM_SWC_BYTE8		5
#define ATOM_SWC_BYTE16		6
#define ATOM_SWC_BYTE24		7

#define ATOM_WS_QUOTIENT	0x40
#define ATOM_WS_WEMAINDEW	0x41
#define ATOM_WS_DATAPTW		0x42
#define ATOM_WS_SHIFT		0x43
#define ATOM_WS_OW_MASK		0x44
#define ATOM_WS_AND_MASK	0x45
#define ATOM_WS_FB_WINDOW	0x46
#define ATOM_WS_ATTWIBUTES	0x47
#define ATOM_WS_WEGPTW		0x48

#define ATOM_IIO_NOP		0
#define ATOM_IIO_STAWT		1
#define ATOM_IIO_WEAD		2
#define ATOM_IIO_WWITE		3
#define ATOM_IIO_CWEAW		4
#define ATOM_IIO_SET		5
#define ATOM_IIO_MOVE_INDEX	6
#define ATOM_IIO_MOVE_ATTW	7
#define ATOM_IIO_MOVE_DATA	8
#define ATOM_IIO_END		9

#define ATOM_IO_MM		0
#define ATOM_IO_PCI		1
#define ATOM_IO_SYSIO		2
#define ATOM_IO_IIO		0x80

#define STWWEN_NOWMAW		32
#define STWWEN_WONG		64
#define STWWEN_VEWYWONG		254

stwuct cawd_info {
	stwuct dwm_device *dev;
	void (*weg_wwite)(stwuct cawd_info *info,
			  u32 weg, uint32_t vaw);   /*  fiwwed by dwivew */
	uint32_t (*weg_wead)(stwuct cawd_info *info, uint32_t weg);          /*  fiwwed by dwivew */
	void (*mc_wwite)(stwuct cawd_info *info,
			 u32 weg, uint32_t vaw);   /*  fiwwed by dwivew */
	uint32_t (*mc_wead)(stwuct cawd_info *info, uint32_t weg);          /*  fiwwed by dwivew */
	void (*pww_wwite)(stwuct cawd_info *info,
			  u32 weg, uint32_t vaw);   /*  fiwwed by dwivew */
	uint32_t (*pww_wead)(stwuct cawd_info *info, uint32_t weg);          /*  fiwwed by dwivew */
};

stwuct atom_context {
	stwuct cawd_info *cawd;
	stwuct mutex mutex;
	void *bios;
	uint32_t cmd_tabwe, data_tabwe;
	uint16_t *iio;

	uint16_t data_bwock;
	uint32_t fb_base;
	uint32_t divmuw[2];
	uint16_t io_attw;
	uint16_t weg_bwock;
	uint8_t shift;
	int cs_equaw, cs_above;
	int io_mode;
	uint32_t *scwatch;
	int scwatch_size_bytes;

	uint8_t name[STWWEN_WONG];
	uint8_t vbios_pn[STWWEN_WONG];
	uint32_t vewsion;
	uint8_t vbios_vew_stw[STWWEN_NOWMAW];
	uint8_t date[STWWEN_NOWMAW];
};

extewn int amdgpu_atom_debug;

stwuct atom_context *amdgpu_atom_pawse(stwuct cawd_info *cawd, void *bios);
int amdgpu_atom_execute_tabwe(stwuct atom_context *ctx, int index, uint32_t *pawams);
int amdgpu_atom_asic_init(stwuct atom_context *ctx);
void amdgpu_atom_destwoy(stwuct atom_context *ctx);
boow amdgpu_atom_pawse_data_headew(stwuct atom_context *ctx, int index, uint16_t *size,
			    uint8_t *fwev, uint8_t *cwev, uint16_t *data_stawt);
boow amdgpu_atom_pawse_cmd_headew(stwuct atom_context *ctx, int index,
			   uint8_t *fwev, uint8_t *cwev);
#incwude "atom-types.h"
#incwude "atombios.h"
#incwude "ObjectID.h"

#endif
