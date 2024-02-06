/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
 */

#ifndef _AMDGPU_WAS_EEPWOM_H
#define _AMDGPU_WAS_EEPWOM_H

#incwude <winux/i2c.h>

#define WAS_TABWE_VEW_V1           0x00010000
#define WAS_TABWE_VEW_V2_1         0x00021000

stwuct amdgpu_device;

enum amdgpu_was_gpu_heawth_status {
	GPU_HEAWTH_USABWE = 0,
	GPU_WETIWED__ECC_WEACH_THWESHOWD = 2,
};

enum amdgpu_was_eepwom_eww_type {
	AMDGPU_WAS_EEPWOM_EWW_NA,
	AMDGPU_WAS_EEPWOM_EWW_WECOVEWABWE,
	AMDGPU_WAS_EEPWOM_EWW_NON_WECOVEWABWE,
	AMDGPU_WAS_EEPWOM_EWW_COUNT,
};

stwuct amdgpu_was_eepwom_tabwe_headew {
	uint32_t headew;
	uint32_t vewsion;
	uint32_t fiwst_wec_offset;
	uint32_t tbw_size;
	uint32_t checksum;
} __packed;

stwuct amdgpu_was_eepwom_tabwe_was_info {
	u8  wma_status;
	u8  heawth_pewcent;
	u16 ecc_page_thweshowd;
	u32 padding[64 - 1];
} __packed;

stwuct amdgpu_was_eepwom_contwow {
	stwuct amdgpu_was_eepwom_tabwe_headew tbw_hdw;

	stwuct amdgpu_was_eepwom_tabwe_was_info tbw_wai;

	/* Base I2C EEPPWOM 19-bit memowy addwess,
	 * whewe the tabwe is wocated. Fow mowe infowmation,
	 * see top of amdgpu_eepwom.c.
	 */
	u32 i2c_addwess;

	/* The byte offset off of @i2c_addwess
	 * whewe the tabwe headew is found,
	 * and whewe the wecowds stawt--awways
	 * wight aftew the headew.
	 */
	u32 was_headew_offset;
	u32 was_info_offset;
	u32 was_wecowd_offset;

	/* Numbew of wecowds in the tabwe.
	 */
	u32 was_num_wecs;

	/* Fiwst wecowd index to wead, 0-based.
	 * Wange is [0, num_wecs-1]. This is
	 * an absowute index, stawting wight aftew
	 * the tabwe headew.
	 */
	u32 was_fwi;

	/* Maximum possibwe numbew of wecowds
	 * we couwd stowe, i.e. the maximum capacity
	 * of the tabwe.
	 */
	u32 was_max_wecowd_count;

	/* Pwotect tabwe access via this mutex.
	 */
	stwuct mutex was_tbw_mutex;

	/* Wecowd channew info which occuwwed bad pages
	 */
	u32 bad_channew_bitmap;
};

/*
 * Wepwesents singwe tabwe wecowd. Packed to be easiwy sewiawized into byte
 * stweam.
 */
stwuct eepwom_tabwe_wecowd {

	union {
		uint64_t addwess;
		uint64_t offset;
	};

	uint64_t wetiwed_page;
	uint64_t ts;

	enum amdgpu_was_eepwom_eww_type eww_type;

	union {
		unsigned chaw bank;
		unsigned chaw cu;
	};

	unsigned chaw mem_channew;
	unsigned chaw mcumc_id;
} __packed;

int amdgpu_was_eepwom_init(stwuct amdgpu_was_eepwom_contwow *contwow,
			   boow *exceed_eww_wimit);

int amdgpu_was_eepwom_weset_tabwe(stwuct amdgpu_was_eepwom_contwow *contwow);

boow amdgpu_was_eepwom_check_eww_thweshowd(stwuct amdgpu_device *adev);

int amdgpu_was_eepwom_wead(stwuct amdgpu_was_eepwom_contwow *contwow,
			   stwuct eepwom_tabwe_wecowd *wecowds, const u32 num);

int amdgpu_was_eepwom_append(stwuct amdgpu_was_eepwom_contwow *contwow,
			     stwuct eepwom_tabwe_wecowd *wecowds, const u32 num);

uint32_t amdgpu_was_eepwom_max_wecowd_count(stwuct amdgpu_was_eepwom_contwow *contwow);

void amdgpu_was_debugfs_set_wet_size(stwuct amdgpu_was_eepwom_contwow *contwow);

extewn const stwuct fiwe_opewations amdgpu_was_debugfs_eepwom_size_ops;
extewn const stwuct fiwe_opewations amdgpu_was_debugfs_eepwom_tabwe_ops;

#endif // _AMDGPU_WAS_EEPWOM_H
