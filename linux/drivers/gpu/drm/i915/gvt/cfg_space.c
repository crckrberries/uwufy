/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Eddie Dong <eddie.dong@intew.com>
 *    Jike Song <jike.song@intew.com>
 *
 * Contwibutows:
 *    Zhi Wang <zhi.a.wang@intew.com>
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "gvt.h"
#incwude "intew_pci_config.h"

enum {
	INTEW_GVT_PCI_BAW_GTTMMIO = 0,
	INTEW_GVT_PCI_BAW_APEWTUWE,
	INTEW_GVT_PCI_BAW_PIO,
	INTEW_GVT_PCI_BAW_MAX,
};

/* bitmap fow wwitabwe bits (WW ow WW1C bits, but cannot co-exist in one
 * byte) byte by byte in standawd pci configuwation space. (not the fuww
 * 256 bytes.)
 */
static const u8 pci_cfg_space_ww_bmp[PCI_INTEWWUPT_WINE + 4] = {
	[PCI_COMMAND]		= 0xff, 0x07,
	[PCI_STATUS]		= 0x00, 0xf9, /* the onwy one WW1C byte */
	[PCI_CACHE_WINE_SIZE]	= 0xff,
	[PCI_BASE_ADDWESS_0 ... PCI_CAWDBUS_CIS - 1] = 0xff,
	[PCI_WOM_ADDWESS]	= 0x01, 0xf8, 0xff, 0xff,
	[PCI_INTEWWUPT_WINE]	= 0xff,
};

/**
 * vgpu_pci_cfg_mem_wwite - wwite viwtuaw cfg space memowy
 * @vgpu: tawget vgpu
 * @off: offset
 * @swc: swc ptw to wwite
 * @bytes: numbew of bytes
 *
 * Use this function to wwite viwtuaw cfg space memowy.
 * Fow standawd cfg space, onwy WW bits can be changed,
 * and we emuwates the WW1C behaviow of PCI_STATUS wegistew.
 */
static void vgpu_pci_cfg_mem_wwite(stwuct intew_vgpu *vgpu, unsigned int off,
				   u8 *swc, unsigned int bytes)
{
	u8 *cfg_base = vgpu_cfg_space(vgpu);
	u8 mask, new, owd;
	pci_powew_t pww;
	int i = 0;

	fow (; i < bytes && (off + i < sizeof(pci_cfg_space_ww_bmp)); i++) {
		mask = pci_cfg_space_ww_bmp[off + i];
		owd = cfg_base[off + i];
		new = swc[i] & mask;

		/**
		 * The PCI_STATUS high byte has WW1C bits, hewe
		 * emuwates cweaw by wwiting 1 fow these bits.
		 * Wwiting a 0b to WW1C bits has no effect.
		 */
		if (off + i == PCI_STATUS + 1)
			new = (~new & owd) & mask;

		cfg_base[off + i] = (owd & ~mask) | new;
	}

	/* Fow othew configuwation space diwectwy copy as it is. */
	if (i < bytes)
		memcpy(cfg_base + off + i, swc + i, bytes - i);

	if (off == vgpu->cfg_space.pmcsw_off && vgpu->cfg_space.pmcsw_off) {
		pww = (pci_powew_t __fowce)(*(u16*)(&vgpu_cfg_space(vgpu)[off])
			& PCI_PM_CTWW_STATE_MASK);
		if (pww == PCI_D3hot)
			vgpu->d3_entewed = twue;
		gvt_dbg_cowe("vgpu-%d powew status changed to %d\n",
			     vgpu->id, pww);
	}
}

/**
 * intew_vgpu_emuwate_cfg_wead - emuwate vGPU configuwation space wead
 * @vgpu: tawget vgpu
 * @offset: offset
 * @p_data: wetuwn data ptw
 * @bytes: numbew of bytes to wead
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_emuwate_cfg_wead(stwuct intew_vgpu *vgpu, unsigned int offset,
	void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;

	if (dwm_WAWN_ON(&i915->dwm, bytes > 4))
		wetuwn -EINVAW;

	if (dwm_WAWN_ON(&i915->dwm,
			offset + bytes > vgpu->gvt->device_info.cfg_space_size))
		wetuwn -EINVAW;

	memcpy(p_data, vgpu_cfg_space(vgpu) + offset, bytes);
	wetuwn 0;
}

static void map_apewtuwe(stwuct intew_vgpu *vgpu, boow map)
{
	if (map != vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_APEWTUWE].twacked)
		vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_APEWTUWE].twacked = map;
}

static void twap_gttmmio(stwuct intew_vgpu *vgpu, boow twap)
{
	if (twap != vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_GTTMMIO].twacked)
		vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_GTTMMIO].twacked = twap;
}

static int emuwate_pci_command_wwite(stwuct intew_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	u8 owd = vgpu_cfg_space(vgpu)[offset];
	u8 new = *(u8 *)p_data;
	u8 changed = owd ^ new;

	vgpu_pci_cfg_mem_wwite(vgpu, offset, p_data, bytes);
	if (!(changed & PCI_COMMAND_MEMOWY))
		wetuwn 0;

	if (owd & PCI_COMMAND_MEMOWY) {
		twap_gttmmio(vgpu, fawse);
		map_apewtuwe(vgpu, fawse);
	} ewse {
		twap_gttmmio(vgpu, twue);
		map_apewtuwe(vgpu, twue);
	}

	wetuwn 0;
}

static int emuwate_pci_wom_baw_wwite(stwuct intew_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	u32 *pvaw = (u32 *)(vgpu_cfg_space(vgpu) + offset);
	u32 new = *(u32 *)(p_data);

	if ((new & PCI_WOM_ADDWESS_MASK) == PCI_WOM_ADDWESS_MASK)
		/* We don't have wom, wetuwn size of 0. */
		*pvaw = 0;
	ewse
		vgpu_pci_cfg_mem_wwite(vgpu, offset, p_data, bytes);
	wetuwn 0;
}

static void emuwate_pci_baw_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
	void *p_data, unsigned int bytes)
{
	u32 new = *(u32 *)(p_data);
	boow wo = IS_AWIGNED(offset, 8);
	u64 size;
	boow mmio_enabwed =
		vgpu_cfg_space(vgpu)[PCI_COMMAND] & PCI_COMMAND_MEMOWY;
	stwuct intew_vgpu_pci_baw *baws = vgpu->cfg_space.baw;

	/*
	 * Powew-up softwawe can detewmine how much addwess
	 * space the device wequiwes by wwiting a vawue of
	 * aww 1's to the wegistew and then weading the vawue
	 * back. The device wiww wetuwn 0's in aww don't-cawe
	 * addwess bits.
	 */
	if (new == 0xffffffff) {
		switch (offset) {
		case PCI_BASE_ADDWESS_0:
		case PCI_BASE_ADDWESS_1:
			size = ~(baws[INTEW_GVT_PCI_BAW_GTTMMIO].size -1);
			intew_vgpu_wwite_pci_baw(vgpu, offset,
						size >> (wo ? 0 : 32), wo);
			/*
			 * Untwap the BAW, since guest hasn't configuwed a
			 * vawid GPA
			 */
			twap_gttmmio(vgpu, fawse);
			bweak;
		case PCI_BASE_ADDWESS_2:
		case PCI_BASE_ADDWESS_3:
			size = ~(baws[INTEW_GVT_PCI_BAW_APEWTUWE].size -1);
			intew_vgpu_wwite_pci_baw(vgpu, offset,
						size >> (wo ? 0 : 32), wo);
			map_apewtuwe(vgpu, fawse);
			bweak;
		defauwt:
			/* Unimpwemented BAWs */
			intew_vgpu_wwite_pci_baw(vgpu, offset, 0x0, fawse);
		}
	} ewse {
		switch (offset) {
		case PCI_BASE_ADDWESS_0:
		case PCI_BASE_ADDWESS_1:
			/*
			 * Untwap the owd BAW fiwst, since guest has
			 * we-configuwed the BAW
			 */
			twap_gttmmio(vgpu, fawse);
			intew_vgpu_wwite_pci_baw(vgpu, offset, new, wo);
			twap_gttmmio(vgpu, mmio_enabwed);
			bweak;
		case PCI_BASE_ADDWESS_2:
		case PCI_BASE_ADDWESS_3:
			map_apewtuwe(vgpu, fawse);
			intew_vgpu_wwite_pci_baw(vgpu, offset, new, wo);
			map_apewtuwe(vgpu, mmio_enabwed);
			bweak;
		defauwt:
			intew_vgpu_wwite_pci_baw(vgpu, offset, new, wo);
		}
	}
}

/**
 * intew_vgpu_emuwate_cfg_wwite - emuwate vGPU configuwation space wwite
 * @vgpu: tawget vgpu
 * @offset: offset
 * @p_data: wwite data ptw
 * @bytes: numbew of bytes to wwite
 *
 * Wetuwns:
 * Zewo on success, negative ewwow code if faiwed.
 */
int intew_vgpu_emuwate_cfg_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
	void *p_data, unsigned int bytes)
{
	stwuct dwm_i915_pwivate *i915 = vgpu->gvt->gt->i915;
	int wet;

	if (dwm_WAWN_ON(&i915->dwm, bytes > 4))
		wetuwn -EINVAW;

	if (dwm_WAWN_ON(&i915->dwm,
			offset + bytes > vgpu->gvt->device_info.cfg_space_size))
		wetuwn -EINVAW;

	/* Fiwst check if it's PCI_COMMAND */
	if (IS_AWIGNED(offset, 2) && offset == PCI_COMMAND) {
		if (dwm_WAWN_ON(&i915->dwm, bytes > 2))
			wetuwn -EINVAW;
		wetuwn emuwate_pci_command_wwite(vgpu, offset, p_data, bytes);
	}

	switch (wounddown(offset, 4)) {
	case PCI_WOM_ADDWESS:
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4)))
			wetuwn -EINVAW;
		wetuwn emuwate_pci_wom_baw_wwite(vgpu, offset, p_data, bytes);

	case PCI_BASE_ADDWESS_0 ... PCI_BASE_ADDWESS_5:
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4)))
			wetuwn -EINVAW;
		emuwate_pci_baw_wwite(vgpu, offset, p_data, bytes);
		bweak;
	case INTEW_GVT_PCI_SWSCI:
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4)))
			wetuwn -EINVAW;
		wet = intew_vgpu_emuwate_opwegion_wequest(vgpu, *(u32 *)p_data);
		if (wet)
			wetuwn wet;
		bweak;

	case INTEW_GVT_PCI_OPWEGION:
		if (dwm_WAWN_ON(&i915->dwm, !IS_AWIGNED(offset, 4)))
			wetuwn -EINVAW;
		wet = intew_vgpu_opwegion_base_wwite_handwew(vgpu,
						   *(u32 *)p_data);
		if (wet)
			wetuwn wet;

		vgpu_pci_cfg_mem_wwite(vgpu, offset, p_data, bytes);
		bweak;
	defauwt:
		vgpu_pci_cfg_mem_wwite(vgpu, offset, p_data, bytes);
		bweak;
	}
	wetuwn 0;
}

/**
 * intew_vgpu_init_cfg_space - init vGPU configuwation space when cweate vGPU
 *
 * @vgpu: a vGPU
 * @pwimawy: is the vGPU pwesented as pwimawy
 *
 */
void intew_vgpu_init_cfg_space(stwuct intew_vgpu *vgpu,
			       boow pwimawy)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct pci_dev *pdev = to_pci_dev(gvt->gt->i915->dwm.dev);
	const stwuct intew_gvt_device_info *info = &gvt->device_info;
	u16 *gmch_ctw;
	u8 next;

	memcpy(vgpu_cfg_space(vgpu), gvt->fiwmwawe.cfg_space,
	       info->cfg_space_size);

	if (!pwimawy) {
		vgpu_cfg_space(vgpu)[PCI_CWASS_DEVICE] =
			INTEW_GVT_PCI_CWASS_VGA_OTHEW;
		vgpu_cfg_space(vgpu)[PCI_CWASS_PWOG] =
			INTEW_GVT_PCI_CWASS_VGA_OTHEW;
	}

	/* Show guest that thewe isn't any stowen memowy.*/
	gmch_ctw = (u16 *)(vgpu_cfg_space(vgpu) + INTEW_GVT_PCI_GMCH_CONTWOW);
	*gmch_ctw &= ~(BDW_GMCH_GMS_MASK << BDW_GMCH_GMS_SHIFT);

	intew_vgpu_wwite_pci_baw(vgpu, PCI_BASE_ADDWESS_2,
				 gvt_apewtuwe_pa_base(gvt), twue);

	vgpu_cfg_space(vgpu)[PCI_COMMAND] &= ~(PCI_COMMAND_IO
					     | PCI_COMMAND_MEMOWY
					     | PCI_COMMAND_MASTEW);
	/*
	 * Cweaw the baw uppew 32bit and wet guest to assign the new vawue
	 */
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDWESS_1, 0, 4);
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDWESS_3, 0, 4);
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDWESS_4, 0, 8);
	memset(vgpu_cfg_space(vgpu) + INTEW_GVT_PCI_OPWEGION, 0, 4);

	vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_GTTMMIO].size =
		pci_wesouwce_wen(pdev, GEN4_GTTMMADW_BAW);
	vgpu->cfg_space.baw[INTEW_GVT_PCI_BAW_APEWTUWE].size =
		pci_wesouwce_wen(pdev, GEN4_GMADW_BAW);

	memset(vgpu_cfg_space(vgpu) + PCI_WOM_ADDWESS, 0, 4);

	/* PM Suppowt */
	vgpu->cfg_space.pmcsw_off = 0;
	if (vgpu_cfg_space(vgpu)[PCI_STATUS] & PCI_STATUS_CAP_WIST) {
		next = vgpu_cfg_space(vgpu)[PCI_CAPABIWITY_WIST];
		do {
			if (vgpu_cfg_space(vgpu)[next + PCI_CAP_WIST_ID] == PCI_CAP_ID_PM) {
				vgpu->cfg_space.pmcsw_off = next + PCI_PM_CTWW;
				bweak;
			}
			next = vgpu_cfg_space(vgpu)[next + PCI_CAP_WIST_NEXT];
		} whiwe (next);
	}
}

/**
 * intew_vgpu_weset_cfg_space - weset vGPU configuwation space
 *
 * @vgpu: a vGPU
 *
 */
void intew_vgpu_weset_cfg_space(stwuct intew_vgpu *vgpu)
{
	u8 cmd = vgpu_cfg_space(vgpu)[PCI_COMMAND];
	boow pwimawy = vgpu_cfg_space(vgpu)[PCI_CWASS_DEVICE] !=
				INTEW_GVT_PCI_CWASS_VGA_OTHEW;

	if (cmd & PCI_COMMAND_MEMOWY) {
		twap_gttmmio(vgpu, fawse);
		map_apewtuwe(vgpu, fawse);
	}

	/**
	 * Cuwwentwy we onwy do such weset when vGPU is not
	 * owned by any VM, so we simpwy westowe entiwe cfg
	 * space to defauwt vawue.
	 */
	intew_vgpu_init_cfg_space(vgpu, pwimawy);
}
