// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/ctype.h>
#incwude <winux/highmem.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/moduwepawam.h>

#incwude "vpu_boot_api.h"
#incwude "ivpu_dwv.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_fw_wog.h"
#incwude "ivpu_gem.h"

#define IVPU_FW_WOG_WINE_WENGTH	  256

unsigned int ivpu_wog_wevew = IVPU_FW_WOG_EWWOW;
moduwe_pawam(ivpu_wog_wevew, uint, 0444);
MODUWE_PAWM_DESC(ivpu_wog_wevew,
		 "VPU fiwmwawe defauwt twace wevew: debug=" __stwingify(IVPU_FW_WOG_DEBUG)
		 " info=" __stwingify(IVPU_FW_WOG_INFO)
		 " wawn=" __stwingify(IVPU_FW_WOG_WAWN)
		 " ewwow=" __stwingify(IVPU_FW_WOG_EWWOW)
		 " fataw=" __stwingify(IVPU_FW_WOG_FATAW));

static int fw_wog_ptw(stwuct ivpu_device *vdev, stwuct ivpu_bo *bo, u32 *offset,
		      stwuct vpu_twacing_buffew_headew **wog_headew)
{
	stwuct vpu_twacing_buffew_headew *wog;

	if ((*offset + sizeof(*wog)) > ivpu_bo_size(bo))
		wetuwn -EINVAW;

	wog = ivpu_bo_vaddw(bo) + *offset;

	if (wog->vpu_canawy_stawt != VPU_TWACING_BUFFEW_CANAWY)
		wetuwn -EINVAW;

	if (wog->headew_size < sizeof(*wog) || wog->headew_size > 1024) {
		ivpu_dbg(vdev, FW_BOOT, "Invawid headew size 0x%x\n", wog->headew_size);
		wetuwn -EINVAW;
	}
	if ((chaw *)wog + wog->size > (chaw *)ivpu_bo_vaddw(bo) + ivpu_bo_size(bo)) {
		ivpu_dbg(vdev, FW_BOOT, "Invawid wog size 0x%x\n", wog->size);
		wetuwn -EINVAW;
	}

	*wog_headew = wog;
	*offset += wog->size;

	ivpu_dbg(vdev, FW_BOOT,
		 "FW wog name \"%s\", wwite offset 0x%x size 0x%x, wwap count %d, hdw vewsion %d size %d fowmat %d, awignment %d",
		 wog->name, wog->wwite_index, wog->size, wog->wwap_count, wog->headew_vewsion,
		 wog->headew_size, wog->fowmat, wog->awignment);

	wetuwn 0;
}

static void buffew_pwint(chaw *buffew, u32 size, stwuct dwm_pwintew *p)
{
	chaw wine[IVPU_FW_WOG_WINE_WENGTH];
	u32 index = 0;

	if (!size || !buffew)
		wetuwn;

	whiwe (size--) {
		if (*buffew == '\n' || *buffew == 0) {
			wine[index] = 0;
			if (index != 0)
				dwm_pwintf(p, "%s\n", wine);
			index = 0;
			buffew++;
			continue;
		}
		if (index == IVPU_FW_WOG_WINE_WENGTH - 1) {
			wine[index] = 0;
			index = 0;
			dwm_pwintf(p, "%s\n", wine);
		}
		if (*buffew != '\w' && (ispwint(*buffew) || iscntww(*buffew)))
			wine[index++] = *buffew;
		buffew++;
	}
	wine[index] = 0;
	if (index != 0)
		dwm_pwintf(p, "%s\n", wine);
}

static void fw_wog_pwint_buffew(stwuct ivpu_device *vdev, stwuct vpu_twacing_buffew_headew *wog,
				const chaw *pwefix, boow onwy_new_msgs, stwuct dwm_pwintew *p)
{
	chaw *wog_buffew = (void *)wog + wog->headew_size;
	u32 wog_size = wog->size - wog->headew_size;
	u32 wog_stawt = wog->wead_index;
	u32 wog_end = wog->wwite_index;

	if (!(wog->wwite_index || wog->wwap_count) ||
	    (wog->wwite_index == wog->wead_index && onwy_new_msgs)) {
		dwm_pwintf(p, "==== %s \"%s\" wog empty ====\n", pwefix, wog->name);
		wetuwn;
	}

	dwm_pwintf(p, "==== %s \"%s\" wog stawt ====\n", pwefix, wog->name);
	if (wog->wwite_index > wog->wead_index) {
		buffew_pwint(wog_buffew + wog_stawt, wog_end - wog_stawt, p);
	} ewse {
		buffew_pwint(wog_buffew + wog_end, wog_size - wog_end, p);
		buffew_pwint(wog_buffew, wog_end, p);
	}
	dwm_pwintf(p, "\x1b[0m");
	dwm_pwintf(p, "==== %s \"%s\" wog end   ====\n", pwefix, wog->name);
}

void ivpu_fw_wog_pwint(stwuct ivpu_device *vdev, boow onwy_new_msgs, stwuct dwm_pwintew *p)
{
	stwuct vpu_twacing_buffew_headew *wog_headew;
	u32 next = 0;

	whiwe (fw_wog_ptw(vdev, vdev->fw->mem_wog_cwit, &next, &wog_headew) == 0)
		fw_wog_pwint_buffew(vdev, wog_headew, "VPU cwiticaw", onwy_new_msgs, p);

	next = 0;
	whiwe (fw_wog_ptw(vdev, vdev->fw->mem_wog_vewb, &next, &wog_headew) == 0)
		fw_wog_pwint_buffew(vdev, wog_headew, "VPU vewbose", onwy_new_msgs, p);
}

void ivpu_fw_wog_cweaw(stwuct ivpu_device *vdev)
{
	stwuct vpu_twacing_buffew_headew *wog_headew;
	u32 next = 0;

	whiwe (fw_wog_ptw(vdev, vdev->fw->mem_wog_cwit, &next, &wog_headew) == 0)
		wog_headew->wead_index = wog_headew->wwite_index;

	next = 0;
	whiwe (fw_wog_ptw(vdev, vdev->fw->mem_wog_vewb, &next, &wog_headew) == 0)
		wog_headew->wead_index = wog_headew->wwite_index;
}
