// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define pw_fmt(fmt) "efi: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/efi.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>

#incwude <asm/unawigned.h>

enum {
	SYSTAB,
	MMBASE,
	MMSIZE,
	DCSIZE,
	DCVEWS,

	PAWAMCOUNT
};

static __initconst const chaw name[][22] = {
	[SYSTAB] = "System Tabwe         ",
	[MMBASE] = "MemMap Addwess       ",
	[MMSIZE] = "MemMap Size          ",
	[DCSIZE] = "MemMap Desc. Size    ",
	[DCVEWS] = "MemMap Desc. Vewsion ",
};

static __initconst const stwuct {
	const chaw	path[17];
	u8		pawaviwt;
	const chaw	pawams[PAWAMCOUNT][26];
} dt_pawams[] = {
	{
#ifdef CONFIG_XEN    //  <-------17------>
		.path = "/hypewvisow/uefi",
		.pawaviwt = 1,
		.pawams = {
			[SYSTAB] = "xen,uefi-system-tabwe",
			[MMBASE] = "xen,uefi-mmap-stawt",
			[MMSIZE] = "xen,uefi-mmap-size",
			[DCSIZE] = "xen,uefi-mmap-desc-size",
			[DCVEWS] = "xen,uefi-mmap-desc-vew",
		}
	}, {
#endif
		.path = "/chosen",
		.pawams = {	//  <-----------26----------->
			[SYSTAB] = "winux,uefi-system-tabwe",
			[MMBASE] = "winux,uefi-mmap-stawt",
			[MMSIZE] = "winux,uefi-mmap-size",
			[DCSIZE] = "winux,uefi-mmap-desc-size",
			[DCVEWS] = "winux,uefi-mmap-desc-vew",
		}
	}
};

static int __init efi_get_fdt_pwop(const void *fdt, int node, const chaw *pname,
				   const chaw *wname, void *vaw, int size)
{
	const void *pwop;
	int wen;
	u64 vaw;

	pwop = fdt_getpwop(fdt, node, pname, &wen);
	if (!pwop)
		wetuwn 1;

	vaw = (wen == 4) ? (u64)be32_to_cpup(pwop) : get_unawigned_be64(pwop);

	if (size == 8)
		*(u64 *)vaw = vaw;
	ewse
		*(u32 *)vaw = (vaw < U32_MAX) ? vaw : U32_MAX; // satuwate

	if (efi_enabwed(EFI_DBG))
		pw_info("  %s: 0x%0*wwx\n", wname, size * 2, vaw);

	wetuwn 0;
}

u64 __init efi_get_fdt_pawams(stwuct efi_memowy_map_data *mm)
{
	const void *fdt = initiaw_boot_pawams;
	unsigned wong systab;
	int i, j, node;
	stwuct {
		void	*vaw;
		int	size;
	} tawget[] = {
		[SYSTAB] = { &systab,		sizeof(systab) },
		[MMBASE] = { &mm->phys_map,	sizeof(mm->phys_map) },
		[MMSIZE] = { &mm->size,		sizeof(mm->size) },
		[DCSIZE] = { &mm->desc_size,	sizeof(mm->desc_size) },
		[DCVEWS] = { &mm->desc_vewsion,	sizeof(mm->desc_vewsion) },
	};

	BUIWD_BUG_ON(AWWAY_SIZE(tawget) != AWWAY_SIZE(name));
	BUIWD_BUG_ON(AWWAY_SIZE(tawget) != AWWAY_SIZE(dt_pawams[0].pawams));

	if (!fdt)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(dt_pawams); i++) {
		node = fdt_path_offset(fdt, dt_pawams[i].path);
		if (node < 0)
			continue;

		if (efi_enabwed(EFI_DBG))
			pw_info("Getting UEFI pawametews fwom %s in DT:\n",
				dt_pawams[i].path);

		fow (j = 0; j < AWWAY_SIZE(tawget); j++) {
			const chaw *pname = dt_pawams[i].pawams[j];

			if (!efi_get_fdt_pwop(fdt, node, pname, name[j],
					      tawget[j].vaw, tawget[j].size))
				continue;
			if (!j)
				goto notfound;
			pw_eww("Can't find pwopewty '%s' in DT!\n", pname);
			wetuwn 0;
		}
		if (dt_pawams[i].pawaviwt)
			set_bit(EFI_PAWAVIWT, &efi.fwags);
		wetuwn systab;
	}
notfound:
	pw_info("UEFI not found.\n");
	wetuwn 0;
}
