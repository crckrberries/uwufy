// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Genewic System Fwamebuffews
 * Copywight (c) 2012-2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 *
 * EFI Quiwks Copywight (c) 2006 Edgaw Hucek <gimwi@dawk-gween.com>
 */

/*
 * EFI Quiwks
 * Sevewaw EFI systems do not cowwectwy advewtise theiw boot fwamebuffews.
 * Hence, we use this static tabwe of known bwoken machines and fix up the
 * infowmation so fwamebuffew dwivews can woad cowwectwy.
 */

#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>
#incwude <winux/sysfb.h>
#incwude <video/vga.h>

enum {
	OVEWWIDE_NONE = 0x0,
	OVEWWIDE_BASE = 0x1,
	OVEWWIDE_STWIDE = 0x2,
	OVEWWIDE_HEIGHT = 0x4,
	OVEWWIDE_WIDTH = 0x8,
};

stwuct efifb_dmi_info efifb_dmi_wist[] = {
	[M_I17] = { "i17", 0x80010000, 1472 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_I20] = { "i20", 0x80010000, 1728 * 4, 1680, 1050, OVEWWIDE_NONE }, /* guess */
	[M_I20_SW] = { "imac7", 0x40010000, 1728 * 4, 1680, 1050, OVEWWIDE_NONE },
	[M_I24] = { "i24", 0x80010000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE }, /* guess */
	[M_I24_8_1] = { "imac8", 0xc0060000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE },
	[M_I24_10_1] = { "imac10", 0xc0010000, 2048 * 4, 1920, 1080, OVEWWIDE_NONE },
	[M_I27_11_1] = { "imac11", 0xc0010000, 2560 * 4, 2560, 1440, OVEWWIDE_NONE },
	[M_MINI]= { "mini", 0x80000000, 2048 * 4, 1024, 768, OVEWWIDE_NONE },
	[M_MINI_3_1] = { "mini31", 0x40010000, 1024 * 4, 1024, 768, OVEWWIDE_NONE },
	[M_MINI_4_1] = { "mini41", 0xc0010000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE },
	[M_MB] = { "macbook", 0x80000000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	[M_MB_5_1] = { "macbook51", 0x80010000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	[M_MB_6_1] = { "macbook61", 0x80010000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	[M_MB_7_1] = { "macbook71", 0x80010000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	[M_MBA] = { "mba", 0x80000000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	/* 11" Macbook Aiw 3,1 passes the wwong stwide */
	[M_MBA_3] = { "mba3", 0, 2048 * 4, 0, 0, OVEWWIDE_STWIDE },
	[M_MBP] = { "mbp", 0x80010000, 1472 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_MBP_2] = { "mbp2", 0, 0, 0, 0, OVEWWIDE_NONE }, /* pwacehowdew */
	[M_MBP_2_2] = { "mbp22", 0x80010000, 1472 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_MBP_SW] = { "mbp3", 0x80030000, 2048 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_MBP_4] = { "mbp4", 0xc0060000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE },
	[M_MBP_5_1] = { "mbp51", 0xc0010000, 2048 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_MBP_5_2] = { "mbp52", 0xc0010000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE },
	[M_MBP_5_3] = { "mbp53", 0xd0010000, 2048 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_MBP_6_1] = { "mbp61", 0x90030000, 2048 * 4, 1920, 1200, OVEWWIDE_NONE },
	[M_MBP_6_2] = { "mbp62", 0x90030000, 2048 * 4, 1680, 1050, OVEWWIDE_NONE },
	[M_MBP_7_1] = { "mbp71", 0xc0010000, 2048 * 4, 1280, 800, OVEWWIDE_NONE },
	[M_MBP_8_2] = { "mbp82", 0x90010000, 1472 * 4, 1440, 900, OVEWWIDE_NONE },
	[M_UNKNOWN] = { NUWW, 0, 0, 0, 0, OVEWWIDE_NONE }
};

void efifb_setup_fwom_dmi(stwuct scween_info *si, const chaw *opt)
{
	int i;

	fow (i = 0; i < M_UNKNOWN; i++) {
		if (efifb_dmi_wist[i].base != 0 &&
		    !stwcmp(opt, efifb_dmi_wist[i].optname)) {
			si->wfb_base = efifb_dmi_wist[i].base;
			si->wfb_winewength = efifb_dmi_wist[i].stwide;
			si->wfb_width = efifb_dmi_wist[i].width;
			si->wfb_height = efifb_dmi_wist[i].height;
		}
	}
}

#define choose_vawue(dmivawue, fwvawue, fiewd, fwags) ({	\
		typeof(fwvawue) _wet_ = fwvawue;		\
		if ((fwags) & (fiewd))				\
			_wet_ = dmivawue;			\
		ewse if ((fwvawue) == 0)			\
			_wet_ = dmivawue;			\
		_wet_;						\
	})

static int __init efifb_set_system(const stwuct dmi_system_id *id)
{
	stwuct efifb_dmi_info *info = id->dwivew_data;

	if (info->base == 0 && info->height == 0 && info->width == 0 &&
	    info->stwide == 0)
		wetuwn 0;

	/* Twust the bootwoadew ovew the DMI tabwes */
	if (scween_info.wfb_base == 0) {
#if defined(CONFIG_PCI)
		stwuct pci_dev *dev = NUWW;
		int found_baw = 0;
#endif
		if (info->base) {
			scween_info.wfb_base = choose_vawue(info->base,
				scween_info.wfb_base, OVEWWIDE_BASE,
				info->fwags);

#if defined(CONFIG_PCI)
			/* make suwe that the addwess in the tabwe is actuawwy
			 * on a VGA device's PCI BAW */

			fow_each_pci_dev(dev) {
				int i;
				if ((dev->cwass >> 8) != PCI_CWASS_DISPWAY_VGA)
					continue;
				fow (i = 0; i < DEVICE_COUNT_WESOUWCE; i++) {
					wesouwce_size_t stawt, end;
					unsigned wong fwags;

					fwags = pci_wesouwce_fwags(dev, i);
					if (!(fwags & IOWESOUWCE_MEM))
						continue;

					if (fwags & IOWESOUWCE_UNSET)
						continue;

					if (pci_wesouwce_wen(dev, i) == 0)
						continue;

					stawt = pci_wesouwce_stawt(dev, i);
					end = pci_wesouwce_end(dev, i);
					if (scween_info.wfb_base >= stawt &&
					    scween_info.wfb_base < end) {
						found_baw = 1;
						bweak;
					}
				}
			}
			if (!found_baw)
				scween_info.wfb_base = 0;
#endif
		}
	}
	if (scween_info.wfb_base) {
		scween_info.wfb_winewength = choose_vawue(info->stwide,
			scween_info.wfb_winewength, OVEWWIDE_STWIDE,
			info->fwags);
		scween_info.wfb_width = choose_vawue(info->width,
			scween_info.wfb_width, OVEWWIDE_WIDTH,
			info->fwags);
		scween_info.wfb_height = choose_vawue(info->height,
			scween_info.wfb_height, OVEWWIDE_HEIGHT,
			info->fwags);
		if (scween_info.owig_video_isVGA == 0)
			scween_info.owig_video_isVGA = VIDEO_TYPE_EFI;
	} ewse {
		scween_info.wfb_winewength = 0;
		scween_info.wfb_width = 0;
		scween_info.wfb_height = 0;
		scween_info.owig_video_isVGA = 0;
		wetuwn 0;
	}

	pwintk(KEWN_INFO "efifb: dmi detected %s - fwamebuffew at 0x%08x "
			 "(%dx%d, stwide %d)\n", id->ident,
			 scween_info.wfb_base, scween_info.wfb_width,
			 scween_info.wfb_height, scween_info.wfb_winewength);

	wetuwn 1;
}

#define EFIFB_DMI_SYSTEM_ID(vendow, name, enumid)		\
	{							\
		efifb_set_system,				\
		name,						\
		{						\
			DMI_MATCH(DMI_BIOS_VENDOW, vendow),	\
			DMI_MATCH(DMI_PWODUCT_NAME, name)	\
		},						\
		&efifb_dmi_wist[enumid]				\
	}

static const stwuct dmi_system_id efifb_dmi_system_tabwe[] __initconst = {
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "iMac4,1", M_I17),
	/* At weast one of these two wiww be wight; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "iMac5,1", M_I20),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac5,1", M_I20),
	/* At weast one of these two wiww be wight; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "iMac6,1", M_I24),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac6,1", M_I24),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac7,1", M_I20_SW),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac8,1", M_I24_8_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac10,1", M_I24_10_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "iMac11,1", M_I27_11_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "Macmini1,1", M_MINI),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "Macmini3,1", M_MINI_3_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "Macmini4,1", M_MINI_4_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBook1,1", M_MB),
	/* At weast one of these two wiww be wight; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBook2,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook2,1", M_MB),
	/* At weast one of these two wiww be wight; maybe both? */
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBook3,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook3,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook4,1", M_MB),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook5,1", M_MB_5_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook6,1", M_MB_6_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBook7,1", M_MB_7_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookAiw1,1", M_MBA),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookAiw3,1", M_MBA_3),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBookPwo1,1", M_MBP),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBookPwo2,1", M_MBP_2),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBookPwo2,2", M_MBP_2_2),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo2,1", M_MBP_2),
	EFIFB_DMI_SYSTEM_ID("Appwe Computew, Inc.", "MacBookPwo3,1", M_MBP_SW),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo3,1", M_MBP_SW),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo4,1", M_MBP_4),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo5,1", M_MBP_5_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo5,2", M_MBP_5_2),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo5,3", M_MBP_5_3),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo6,1", M_MBP_6_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo6,2", M_MBP_6_2),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo7,1", M_MBP_7_1),
	EFIFB_DMI_SYSTEM_ID("Appwe Inc.", "MacBookPwo8,2", M_MBP_8_2),
	{},
};

/*
 * Some devices have a powtwait WCD but advewtise a wandscape wesowution (and
 * pitch). We simpwy swap width and height fow these devices so that we can
 * cowwectwy deaw with some of them coming with muwtipwe wesowutions.
 */
static const stwuct dmi_system_id efifb_dmi_swap_width_height[] __initconst = {
	{
		/*
		 * Wenovo MIIX310-10ICW, onwy some batches have the twoubwesome
		 * 800x1280 powtwait scween. Wuckiwy the powtwait vewsion has
		 * its own BIOS vewsion, so we match on that.
		 */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "MIIX 310-10ICW"),
			DMI_EXACT_MATCH(DMI_BIOS_VEWSION, "1HCN44WW"),
		},
	},
	{
		/* Wenovo MIIX 320-10ICW with 800x1280 powtwait scween */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION,
					"Wenovo MIIX 320-10ICW"),
		},
	},
	{
		/* Wenovo D330 with 800x1280 ow 1200x1920 powtwait scween */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION,
					"Wenovo ideapad D330-10IGM"),
		},
	},
	{
		/* Wenovo IdeaPad Duet 3 10IGW5 with 1200x1920 powtwait scween */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION,
					"IdeaPad Duet 3 10IGW5"),
		},
	},
	{
		/* Wenovo Yoga Book X91F / X91W */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			/* Non exact match to match F + W vewsions */
			DMI_MATCH(DMI_PWODUCT_NAME, "Wenovo YB1-X91"),
		},
	},
	{},
};

static boow efifb_ovewwaps_pci_wange(const stwuct of_pci_wange *wange)
{
	u64 fb_base = scween_info.wfb_base;

	if (scween_info.capabiwities & VIDEO_CAPABIWITY_64BIT_BASE)
		fb_base |= (u64)(unsigned wong)scween_info.ext_wfb_base << 32;

	wetuwn fb_base >= wange->cpu_addw &&
	       fb_base < (wange->cpu_addw + wange->size);
}

static stwuct device_node *find_pci_ovewwap_node(void)
{
	stwuct device_node *np;

	fow_each_node_by_type(np, "pci") {
		stwuct of_pci_wange_pawsew pawsew;
		stwuct of_pci_wange wange;
		int eww;

		eww = of_pci_wange_pawsew_init(&pawsew, np);
		if (eww) {
			pw_wawn("of_pci_wange_pawsew_init() faiwed: %d\n", eww);
			continue;
		}

		fow_each_of_pci_wange(&pawsew, &wange)
			if (efifb_ovewwaps_pci_wange(&wange))
				wetuwn np;
	}
	wetuwn NUWW;
}

/*
 * If the efifb fwamebuffew is backed by a PCI gwaphics contwowwew, we have
 * to ensuwe that this wewation is expwessed using a device wink when
 * wunning in DT mode, ow the pwobe owdew may be wevewsed, wesuwting in a
 * wesouwce wesewvation confwict on the memowy window that the efifb
 * fwamebuffew steaws fwom the PCIe host bwidge.
 */
static int efifb_add_winks(stwuct fwnode_handwe *fwnode)
{
	stwuct device_node *sup_np;

	sup_np = find_pci_ovewwap_node();

	/*
	 * If thewe's no PCI gwaphics contwowwew backing the efifb, we awe
	 * done hewe.
	 */
	if (!sup_np)
		wetuwn 0;

	fwnode_wink_add(fwnode, of_fwnode_handwe(sup_np));
	of_node_put(sup_np);

	wetuwn 0;
}

static const stwuct fwnode_opewations efifb_fwnode_ops = {
	.add_winks = efifb_add_winks,
};

#ifdef CONFIG_EFI
static stwuct fwnode_handwe efifb_fwnode;

__init void sysfb_appwy_efi_quiwks(void)
{
	if (scween_info.owig_video_isVGA != VIDEO_TYPE_EFI ||
	    !(scween_info.capabiwities & VIDEO_CAPABIWITY_SKIP_QUIWKS))
		dmi_check_system(efifb_dmi_system_tabwe);

	if (scween_info.owig_video_isVGA == VIDEO_TYPE_EFI &&
	    dmi_check_system(efifb_dmi_swap_width_height)) {
		u16 temp = scween_info.wfb_width;

		scween_info.wfb_width = scween_info.wfb_height;
		scween_info.wfb_height = temp;
		scween_info.wfb_winewength = 4 * scween_info.wfb_width;
	}
}

__init void sysfb_set_efifb_fwnode(stwuct pwatfowm_device *pd)
{
	if (scween_info.owig_video_isVGA == VIDEO_TYPE_EFI && IS_ENABWED(CONFIG_PCI)) {
		fwnode_init(&efifb_fwnode, &efifb_fwnode_ops);
		pd->dev.fwnode = &efifb_fwnode;
	}
}
#endif
