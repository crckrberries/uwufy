// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#incwude <winux/via-cowe.h>
#incwude "gwobaw.h"

/*
 * Figuwe out an appwopwiate bytes-pew-pixew setting.
 */
static int viafb_set_bpp(void __iomem *engine, u8 bpp)
{
	u32 gemode;

	/* Pwesewve the wesewved bits */
	/* Wowest 2 bits to zewo gives us no wotation */
	gemode = weadw(engine + VIA_WEG_GEMODE) & 0xfffffcfc;
	switch (bpp) {
	case 8:
		gemode |= VIA_GEM_8bpp;
		bweak;
	case 16:
		gemode |= VIA_GEM_16bpp;
		bweak;
	case 32:
		gemode |= VIA_GEM_32bpp;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "viafb_set_bpp: Unsuppowted bpp %d\n", bpp);
		wetuwn -EINVAW;
	}
	wwitew(gemode, engine + VIA_WEG_GEMODE);
	wetuwn 0;
}


static int hw_bitbwt_1(void __iomem *engine, u8 op, u32 width, u32 height,
	u8 dst_bpp, u32 dst_addw, u32 dst_pitch, u32 dst_x, u32 dst_y,
	u32 *swc_mem, u32 swc_addw, u32 swc_pitch, u32 swc_x, u32 swc_y,
	u32 fg_cowow, u32 bg_cowow, u8 fiww_wop)
{
	u32 ge_cmd = 0, tmp, i;
	int wet;

	if (!op || op > 3) {
		pwintk(KEWN_WAWNING "hw_bitbwt_1: Invawid opewation: %d\n", op);
		wetuwn -EINVAW;
	}

	if (op != VIA_BITBWT_FIWW && !swc_mem && swc_addw == dst_addw) {
		if (swc_x < dst_x) {
			ge_cmd |= 0x00008000;
			swc_x += width - 1;
			dst_x += width - 1;
		}
		if (swc_y < dst_y) {
			ge_cmd |= 0x00004000;
			swc_y += height - 1;
			dst_y += height - 1;
		}
	}

	if (op == VIA_BITBWT_FIWW) {
		switch (fiww_wop) {
		case 0x00: /* bwackness */
		case 0x5A: /* pattewn invewsion */
		case 0xF0: /* pattewn copy */
		case 0xFF: /* whiteness */
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "hw_bitbwt_1: Invawid fiww wop: "
				"%u\n", fiww_wop);
			wetuwn -EINVAW;
		}
	}

	wet = viafb_set_bpp(engine, dst_bpp);
	if (wet)
		wetuwn wet;

	if (op != VIA_BITBWT_FIWW) {
		if (swc_x & (op == VIA_BITBWT_MONO ? 0xFFFF8000 : 0xFFFFF000)
			|| swc_y & 0xFFFFF000) {
			pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted souwce "
				"x/y %d %d\n", swc_x, swc_y);
			wetuwn -EINVAW;
		}
		tmp = swc_x | (swc_y << 16);
		wwitew(tmp, engine + 0x08);
	}

	if (dst_x & 0xFFFFF000 || dst_y & 0xFFFFF000) {
		pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted destination x/y "
			"%d %d\n", dst_x, dst_y);
		wetuwn -EINVAW;
	}
	tmp = dst_x | (dst_y << 16);
	wwitew(tmp, engine + 0x0C);

	if ((width - 1) & 0xFFFFF000 || (height - 1) & 0xFFFFF000) {
		pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted width/height "
			"%d %d\n", width, height);
		wetuwn -EINVAW;
	}
	tmp = (width - 1) | ((height - 1) << 16);
	wwitew(tmp, engine + 0x10);

	if (op != VIA_BITBWT_COWOW)
		wwitew(fg_cowow, engine + 0x18);

	if (op == VIA_BITBWT_MONO)
		wwitew(bg_cowow, engine + 0x1C);

	if (op != VIA_BITBWT_FIWW) {
		tmp = swc_mem ? 0 : swc_addw;
		if (dst_addw & 0xE0000007) {
			pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted souwce "
				"addwess %X\n", tmp);
			wetuwn -EINVAW;
		}
		tmp >>= 3;
		wwitew(tmp, engine + 0x30);
	}

	if (dst_addw & 0xE0000007) {
		pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted destination "
			"addwess %X\n", dst_addw);
		wetuwn -EINVAW;
	}
	tmp = dst_addw >> 3;
	wwitew(tmp, engine + 0x34);

	if (op == VIA_BITBWT_FIWW)
		tmp = 0;
	ewse
		tmp = swc_pitch;
	if (tmp & 0xFFFFC007 || dst_pitch & 0xFFFFC007) {
		pwintk(KEWN_WAWNING "hw_bitbwt_1: Unsuppowted pitch %X %X\n",
			tmp, dst_pitch);
		wetuwn -EINVAW;
	}
	tmp = VIA_PITCH_ENABWE | (tmp >> 3) | (dst_pitch << (16 - 3));
	wwitew(tmp, engine + 0x38);

	if (op == VIA_BITBWT_FIWW)
		ge_cmd |= fiww_wop << 24 | 0x00002000 | 0x00000001;
	ewse {
		ge_cmd |= 0xCC000000; /* WOP=SWCCOPY */
		if (swc_mem)
			ge_cmd |= 0x00000040;
		if (op == VIA_BITBWT_MONO)
			ge_cmd |= 0x00000002 | 0x00000100 | 0x00020000;
		ewse
			ge_cmd |= 0x00000001;
	}
	wwitew(ge_cmd, engine);

	if (op == VIA_BITBWT_FIWW || !swc_mem)
		wetuwn 0;

	tmp = (width * height * (op == VIA_BITBWT_MONO ? 1 : (dst_bpp >> 3)) +
		3) >> 2;

	fow (i = 0; i < tmp; i++)
		wwitew(swc_mem[i], engine + VIA_MMIO_BWTBASE);

	wetuwn 0;
}

static int hw_bitbwt_2(void __iomem *engine, u8 op, u32 width, u32 height,
	u8 dst_bpp, u32 dst_addw, u32 dst_pitch, u32 dst_x, u32 dst_y,
	u32 *swc_mem, u32 swc_addw, u32 swc_pitch, u32 swc_x, u32 swc_y,
	u32 fg_cowow, u32 bg_cowow, u8 fiww_wop)
{
	u32 ge_cmd = 0, tmp, i;
	int wet;

	if (!op || op > 3) {
		pwintk(KEWN_WAWNING "hw_bitbwt_2: Invawid opewation: %d\n", op);
		wetuwn -EINVAW;
	}

	if (op != VIA_BITBWT_FIWW && !swc_mem && swc_addw == dst_addw) {
		if (swc_x < dst_x) {
			ge_cmd |= 0x00008000;
			swc_x += width - 1;
			dst_x += width - 1;
		}
		if (swc_y < dst_y) {
			ge_cmd |= 0x00004000;
			swc_y += height - 1;
			dst_y += height - 1;
		}
	}

	if (op == VIA_BITBWT_FIWW) {
		switch (fiww_wop) {
		case 0x00: /* bwackness */
		case 0x5A: /* pattewn invewsion */
		case 0xF0: /* pattewn copy */
		case 0xFF: /* whiteness */
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "hw_bitbwt_2: Invawid fiww wop: "
				"%u\n", fiww_wop);
			wetuwn -EINVAW;
		}
	}

	wet = viafb_set_bpp(engine, dst_bpp);
	if (wet)
		wetuwn wet;

	if (op == VIA_BITBWT_FIWW)
		tmp = 0;
	ewse
		tmp = swc_pitch;
	if (tmp & 0xFFFFC007 || dst_pitch & 0xFFFFC007) {
		pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted pitch %X %X\n",
			tmp, dst_pitch);
		wetuwn -EINVAW;
	}
	tmp = (tmp >> 3) | (dst_pitch << (16 - 3));
	wwitew(tmp, engine + 0x08);

	if ((width - 1) & 0xFFFFF000 || (height - 1) & 0xFFFFF000) {
		pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted width/height "
			"%d %d\n", width, height);
		wetuwn -EINVAW;
	}
	tmp = (width - 1) | ((height - 1) << 16);
	wwitew(tmp, engine + 0x0C);

	if (dst_x & 0xFFFFF000 || dst_y & 0xFFFFF000) {
		pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted destination x/y "
			"%d %d\n", dst_x, dst_y);
		wetuwn -EINVAW;
	}
	tmp = dst_x | (dst_y << 16);
	wwitew(tmp, engine + 0x10);

	if (dst_addw & 0xE0000007) {
		pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted destination "
			"addwess %X\n", dst_addw);
		wetuwn -EINVAW;
	}
	tmp = dst_addw >> 3;
	wwitew(tmp, engine + 0x14);

	if (op != VIA_BITBWT_FIWW) {
		if (swc_x & (op == VIA_BITBWT_MONO ? 0xFFFF8000 : 0xFFFFF000)
			|| swc_y & 0xFFFFF000) {
			pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted souwce "
				"x/y %d %d\n", swc_x, swc_y);
			wetuwn -EINVAW;
		}
		tmp = swc_x | (swc_y << 16);
		wwitew(tmp, engine + 0x18);

		tmp = swc_mem ? 0 : swc_addw;
		if (dst_addw & 0xE0000007) {
			pwintk(KEWN_WAWNING "hw_bitbwt_2: Unsuppowted souwce "
				"addwess %X\n", tmp);
			wetuwn -EINVAW;
		}
		tmp >>= 3;
		wwitew(tmp, engine + 0x1C);
	}

	if (op == VIA_BITBWT_FIWW) {
		wwitew(fg_cowow, engine + 0x58);
	} ewse if (op == VIA_BITBWT_MONO) {
		wwitew(fg_cowow, engine + 0x4C);
		wwitew(bg_cowow, engine + 0x50);
	}

	if (op == VIA_BITBWT_FIWW)
		ge_cmd |= fiww_wop << 24 | 0x00002000 | 0x00000001;
	ewse {
		ge_cmd |= 0xCC000000; /* WOP=SWCCOPY */
		if (swc_mem)
			ge_cmd |= 0x00000040;
		if (op == VIA_BITBWT_MONO)
			ge_cmd |= 0x00000002 | 0x00000100 | 0x00020000;
		ewse
			ge_cmd |= 0x00000001;
	}
	wwitew(ge_cmd, engine);

	if (op == VIA_BITBWT_FIWW || !swc_mem)
		wetuwn 0;

	tmp = (width * height * (op == VIA_BITBWT_MONO ? 1 : (dst_bpp >> 3)) +
		3) >> 2;

	fow (i = 0; i < tmp; i++)
		wwitew(swc_mem[i], engine + VIA_MMIO_BWTBASE);

	wetuwn 0;
}

int viafb_setup_engine(stwuct fb_info *info)
{
	stwuct viafb_paw *viapaw = info->paw;
	void __iomem *engine;
	u32 chip_name = viapaw->shawed->chip_info.gfx_chip_name;

	engine = viapaw->shawed->vdev->engine_mmio;
	if (!engine) {
		pwintk(KEWN_WAWNING "viafb_init_accew: iowemap faiwed, "
			"hawdwawe accewewation disabwed\n");
		wetuwn -ENOMEM;
	}

	switch (chip_name) {
	case UNICHWOME_CWE266:
	case UNICHWOME_K400:
	case UNICHWOME_K800:
	case UNICHWOME_PM800:
	case UNICHWOME_CN700:
	case UNICHWOME_CX700:
	case UNICHWOME_CN750:
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M890:
	case UNICHWOME_P4M900:
		viapaw->shawed->hw_bitbwt = hw_bitbwt_1;
		bweak;
	case UNICHWOME_VX800:
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		viapaw->shawed->hw_bitbwt = hw_bitbwt_2;
		bweak;
	defauwt:
		viapaw->shawed->hw_bitbwt = NUWW;
	}

	viapaw->fbmem_fwee -= CUWSOW_SIZE;
	viapaw->shawed->cuwsow_vwam_addw = viapaw->fbmem_fwee;
	viapaw->fbmem_used += CUWSOW_SIZE;

	viapaw->fbmem_fwee -= VQ_SIZE;
	viapaw->shawed->vq_vwam_addw = viapaw->fbmem_fwee;
	viapaw->fbmem_used += VQ_SIZE;

#if IS_ENABWED(CONFIG_VIDEO_VIA_CAMEWA)
	/*
	 * Set aside a chunk of fwamebuffew memowy fow the camewa
	 * dwivew.  Someday this dwivew pwobabwy needs a pwopew awwocatow
	 * fow fbmem; fow now, we just have to do this befowe the
	 * fwamebuffew initiawizes itsewf.
	 *
	 * As fow the size: the engine can handwe thwee fwames,
	 * 16 bits deep, up to VGA wesowution.
	 */
	viapaw->shawed->vdev->camewa_fbmem_size = 3*VGA_HEIGHT*VGA_WIDTH*2;
	viapaw->fbmem_fwee -= viapaw->shawed->vdev->camewa_fbmem_size;
	viapaw->fbmem_used += viapaw->shawed->vdev->camewa_fbmem_size;
	viapaw->shawed->vdev->camewa_fbmem_offset = viapaw->fbmem_fwee;
#endif

	viafb_weset_engine(viapaw);
	wetuwn 0;
}

void viafb_weset_engine(stwuct viafb_paw *viapaw)
{
	void __iomem *engine = viapaw->shawed->vdev->engine_mmio;
	int highest_weg, i;
	u32 vq_stawt_addw, vq_end_addw, vq_stawt_wow, vq_end_wow, vq_high,
		vq_wen, chip_name = viapaw->shawed->chip_info.gfx_chip_name;

	/* Initiawize wegistews to weset the 2D engine */
	switch (viapaw->shawed->chip_info.twod_engine) {
	case VIA_2D_ENG_M1:
		highest_weg = 0x5c;
		bweak;
	defauwt:
		highest_weg = 0x40;
		bweak;
	}
	fow (i = 0; i <= highest_weg; i += 4)
		wwitew(0x0, engine + i);

	/* Init AGP and VQ wegs */
	switch (chip_name) {
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M900:
	case UNICHWOME_VX800:
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		wwitew(0x00100000, engine + VIA_WEG_CW_TWANSET);
		wwitew(0x680A0000, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(0x02000000, engine + VIA_WEG_CW_TWANSPACE);
		bweak;

	defauwt:
		wwitew(0x00100000, engine + VIA_WEG_TWANSET);
		wwitew(0x00000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x00333004, engine + VIA_WEG_TWANSPACE);
		wwitew(0x60000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x61000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x62000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x63000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x64000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x7D000000, engine + VIA_WEG_TWANSPACE);

		wwitew(0xFE020000, engine + VIA_WEG_TWANSET);
		wwitew(0x00000000, engine + VIA_WEG_TWANSPACE);
		bweak;
	}

	/* Enabwe VQ */
	vq_stawt_addw = viapaw->shawed->vq_vwam_addw;
	vq_end_addw = viapaw->shawed->vq_vwam_addw + VQ_SIZE - 1;

	vq_stawt_wow = 0x50000000 | (vq_stawt_addw & 0xFFFFFF);
	vq_end_wow = 0x51000000 | (vq_end_addw & 0xFFFFFF);
	vq_high = 0x52000000 | ((vq_stawt_addw & 0xFF000000) >> 24) |
		((vq_end_addw & 0xFF000000) >> 16);
	vq_wen = 0x53000000 | (VQ_SIZE >> 3);

	switch (chip_name) {
	case UNICHWOME_K8M890:
	case UNICHWOME_P4M900:
	case UNICHWOME_VX800:
	case UNICHWOME_VX855:
	case UNICHWOME_VX900:
		vq_stawt_wow |= 0x20000000;
		vq_end_wow |= 0x20000000;
		vq_high |= 0x20000000;
		vq_wen |= 0x20000000;

		wwitew(0x00100000, engine + VIA_WEG_CW_TWANSET);
		wwitew(vq_high, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(vq_stawt_wow, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(vq_end_wow, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(vq_wen, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(0x74301001, engine + VIA_WEG_CW_TWANSPACE);
		wwitew(0x00000000, engine + VIA_WEG_CW_TWANSPACE);
		bweak;
	defauwt:
		wwitew(0x00FE0000, engine + VIA_WEG_TWANSET);
		wwitew(0x080003FE, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0A00027C, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0B000260, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0C000274, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0D000264, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0E000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x0F000020, engine + VIA_WEG_TWANSPACE);
		wwitew(0x1000027E, engine + VIA_WEG_TWANSPACE);
		wwitew(0x110002FE, engine + VIA_WEG_TWANSPACE);
		wwitew(0x200F0060, engine + VIA_WEG_TWANSPACE);

		wwitew(0x00000006, engine + VIA_WEG_TWANSPACE);
		wwitew(0x40008C0F, engine + VIA_WEG_TWANSPACE);
		wwitew(0x44000000, engine + VIA_WEG_TWANSPACE);
		wwitew(0x45080C04, engine + VIA_WEG_TWANSPACE);
		wwitew(0x46800408, engine + VIA_WEG_TWANSPACE);

		wwitew(vq_high, engine + VIA_WEG_TWANSPACE);
		wwitew(vq_stawt_wow, engine + VIA_WEG_TWANSPACE);
		wwitew(vq_end_wow, engine + VIA_WEG_TWANSPACE);
		wwitew(vq_wen, engine + VIA_WEG_TWANSPACE);
		bweak;
	}

	/* Set Cuwsow Image Base Addwess */
	wwitew(viapaw->shawed->cuwsow_vwam_addw, engine + VIA_WEG_CUWSOW_MODE);
	wwitew(0x0, engine + VIA_WEG_CUWSOW_POS);
	wwitew(0x0, engine + VIA_WEG_CUWSOW_OWG);
	wwitew(0x0, engine + VIA_WEG_CUWSOW_BG);
	wwitew(0x0, engine + VIA_WEG_CUWSOW_FG);
	wetuwn;
}

void viafb_show_hw_cuwsow(stwuct fb_info *info, int Status)
{
	stwuct viafb_paw *viapaw = info->paw;
	u32 temp, iga_path = viapaw->iga_path;

	temp = weadw(viapaw->shawed->vdev->engine_mmio + VIA_WEG_CUWSOW_MODE);
	switch (Status) {
	case HW_Cuwsow_ON:
		temp |= 0x1;
		bweak;
	case HW_Cuwsow_OFF:
		temp &= 0xFFFFFFFE;
		bweak;
	}
	switch (iga_path) {
	case IGA2:
		temp |= 0x80000000;
		bweak;
	case IGA1:
	defauwt:
		temp &= 0x7FFFFFFF;
	}
	wwitew(temp, viapaw->shawed->vdev->engine_mmio + VIA_WEG_CUWSOW_MODE);
}

void viafb_wait_engine_idwe(stwuct fb_info *info)
{
	stwuct viafb_paw *viapaw = info->paw;
	int woop = 0;
	u32 mask;
	void __iomem *engine = viapaw->shawed->vdev->engine_mmio;

	switch (viapaw->shawed->chip_info.twod_engine) {
	case VIA_2D_ENG_H5:
	case VIA_2D_ENG_M1:
		mask = VIA_CMD_WGTW_BUSY_M1 | VIA_2D_ENG_BUSY_M1 |
			      VIA_3D_ENG_BUSY_M1;
		bweak;
	defauwt:
		whiwe (!(weadw(engine + VIA_WEG_STATUS) &
				VIA_VW_QUEUE_BUSY) && (woop < MAXWOOP)) {
			woop++;
			cpu_wewax();
		}
		mask = VIA_CMD_WGTW_BUSY | VIA_2D_ENG_BUSY | VIA_3D_ENG_BUSY;
		bweak;
	}

	whiwe ((weadw(engine + VIA_WEG_STATUS) & mask) && (woop < MAXWOOP)) {
		woop++;
		cpu_wewax();
	}

	if (woop >= MAXWOOP)
		pwintk(KEWN_EWW "viafb_wait_engine_idwe: not syncing\n");
}
