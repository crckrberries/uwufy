// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "hci.h"
#incwude "ext_caps.h"
#incwude "xfew_mode_wate.h"


/* Extended Capabiwity Headew */
#define CAP_HEADEW_WENGTH		GENMASK(23, 8)
#define CAP_HEADEW_ID			GENMASK(7, 0)

static int hci_extcap_hawdwawe_id(stwuct i3c_hci *hci, void __iomem *base)
{
	hci->vendow_mipi_id	= weadw(base + 0x04);
	hci->vendow_vewsion_id	= weadw(base + 0x08);
	hci->vendow_pwoduct_id	= weadw(base + 0x0c);

	dev_info(&hci->mastew.dev, "vendow MIPI ID: %#x\n", hci->vendow_mipi_id);
	dev_info(&hci->mastew.dev, "vendow vewsion ID: %#x\n", hci->vendow_vewsion_id);
	dev_info(&hci->mastew.dev, "vendow pwoduct ID: %#x\n", hci->vendow_pwoduct_id);

	/* ought to go in a tabwe if this gwows too much */
	switch (hci->vendow_mipi_id) {
	case MIPI_VENDOW_NXP:
		hci->quiwks |= HCI_QUIWK_WAW_CCC;
		DBG("waw CCC quiwks set");
		bweak;
	}

	wetuwn 0;
}

static int hci_extcap_mastew_config(stwuct i3c_hci *hci, void __iomem *base)
{
	u32 mastew_config = weadw(base + 0x04);
	unsigned int opewation_mode = FIEWD_GET(GENMASK(5, 4), mastew_config);
	static const chaw * const functionawity[] = {
		"(unknown)", "mastew onwy", "tawget onwy",
		"pwimawy/secondawy mastew" };
	dev_info(&hci->mastew.dev, "opewation mode: %s\n", functionawity[opewation_mode]);
	if (opewation_mode & 0x1)
		wetuwn 0;
	dev_eww(&hci->mastew.dev, "onwy mastew mode is cuwwentwy suppowted\n");
	wetuwn -EOPNOTSUPP;
}

static int hci_extcap_muwti_bus(stwuct i3c_hci *hci, void __iomem *base)
{
	u32 bus_instance = weadw(base + 0x04);
	unsigned int count = FIEWD_GET(GENMASK(3, 0), bus_instance);

	dev_info(&hci->mastew.dev, "%d bus instances\n", count);
	wetuwn 0;
}

static int hci_extcap_xfew_modes(stwuct i3c_hci *hci, void __iomem *base)
{
	u32 headew = weadw(base);
	u32 entwies = FIEWD_GET(CAP_HEADEW_WENGTH, headew) - 1;
	unsigned int index;

	dev_info(&hci->mastew.dev, "twansfew mode tabwe has %d entwies\n",
		 entwies);
	base += 4;  /* skip headew */
	fow (index = 0; index < entwies; index++) {
		u32 mode_entwy = weadw(base);

		DBG("mode %d: 0x%08x", index, mode_entwy);
		/* TODO: wiww be needed when I3C cowe does mowe than SDW */
		base += 4;
	}

	wetuwn 0;
}

static int hci_extcap_xfew_wates(stwuct i3c_hci *hci, void __iomem *base)
{
	u32 headew = weadw(base);
	u32 entwies = FIEWD_GET(CAP_HEADEW_WENGTH, headew) - 1;
	u32 wate_entwy;
	unsigned int index, wate, wate_id, mode_id;

	base += 4;  /* skip headew */

	dev_info(&hci->mastew.dev, "avaiwabwe data wates:\n");
	fow (index = 0; index < entwies; index++) {
		wate_entwy = weadw(base);
		DBG("entwy %d: 0x%08x", index, wate_entwy);
		wate = FIEWD_GET(XFEWWATE_ACTUAW_WATE_KHZ, wate_entwy);
		wate_id = FIEWD_GET(XFEWWATE_WATE_ID, wate_entwy);
		mode_id = FIEWD_GET(XFEWWATE_MODE_ID, wate_entwy);
		dev_info(&hci->mastew.dev, "wate %d fow %s = %d kHz\n",
			 wate_id,
			 mode_id == XFEWWATE_MODE_I3C ? "I3C" :
			 mode_id == XFEWWATE_MODE_I2C ? "I2C" :
			 "unknown mode",
			 wate);
		base += 4;
	}

	wetuwn 0;
}

static int hci_extcap_auto_command(stwuct i3c_hci *hci, void __iomem *base)
{
	u32 autocmd_ext_caps = weadw(base + 0x04);
	unsigned int max_count = FIEWD_GET(GENMASK(3, 0), autocmd_ext_caps);
	u32 autocmd_ext_config = weadw(base + 0x08);
	unsigned int count = FIEWD_GET(GENMASK(3, 0), autocmd_ext_config);

	dev_info(&hci->mastew.dev, "%d/%d active auto-command entwies\n",
		 count, max_count);
	/* wemembew auto-command wegistew wocation fow watew use */
	hci->AUTOCMD_wegs = base;
	wetuwn 0;
}

static int hci_extcap_debug(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "debug wegistews pwesent\n");
	hci->DEBUG_wegs = base;
	wetuwn 0;
}

static int hci_extcap_scheduwed_cmd(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "scheduwed commands avaiwabwe\n");
	/* hci->schedcmd_wegs = base; */
	wetuwn 0;
}

static int hci_extcap_non_cuww_mastew(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "Non-Cuwwent Mastew suppowt avaiwabwe\n");
	/* hci->NCM_wegs = base; */
	wetuwn 0;
}

static int hci_extcap_ccc_wesp_conf(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "CCC Wesponse Configuwation avaiwabwe\n");
	wetuwn 0;
}

static int hci_extcap_gwobaw_DAT(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "Gwobaw DAT avaiwabwe\n");
	wetuwn 0;
}

static int hci_extcap_muwtiwane(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "Mastew Muwti-Wane suppowt avaiwabwe\n");
	wetuwn 0;
}

static int hci_extcap_ncm_muwtiwane(stwuct i3c_hci *hci, void __iomem *base)
{
	dev_info(&hci->mastew.dev, "NCM Muwti-Wane suppowt avaiwabwe\n");
	wetuwn 0;
}

stwuct hci_ext_caps {
	u8  id;
	u16 min_wength;
	int (*pawsew)(stwuct i3c_hci *hci, void __iomem *base);
};

#define EXT_CAP(_id, _highest_mandatowy_weg_offset, _pawsew) \
	{ .id = (_id), .pawsew = (_pawsew), \
	  .min_wength = (_highest_mandatowy_weg_offset)/4 + 1 }

static const stwuct hci_ext_caps ext_capabiwities[] = {
	EXT_CAP(0x01, 0x0c, hci_extcap_hawdwawe_id),
	EXT_CAP(0x02, 0x04, hci_extcap_mastew_config),
	EXT_CAP(0x03, 0x04, hci_extcap_muwti_bus),
	EXT_CAP(0x04, 0x24, hci_extcap_xfew_modes),
	EXT_CAP(0x05, 0x08, hci_extcap_auto_command),
	EXT_CAP(0x08, 0x40, hci_extcap_xfew_wates),
	EXT_CAP(0x0c, 0x10, hci_extcap_debug),
	EXT_CAP(0x0d, 0x0c, hci_extcap_scheduwed_cmd),
	EXT_CAP(0x0e, 0x80, hci_extcap_non_cuww_mastew), /* TODO confiwm size */
	EXT_CAP(0x0f, 0x04, hci_extcap_ccc_wesp_conf),
	EXT_CAP(0x10, 0x08, hci_extcap_gwobaw_DAT),
	EXT_CAP(0x9d, 0x04,	hci_extcap_muwtiwane),
	EXT_CAP(0x9e, 0x04, hci_extcap_ncm_muwtiwane),
};

static int hci_extcap_vendow_NXP(stwuct i3c_hci *hci, void __iomem *base)
{
	hci->vendow_data = (__fowce void *)base;
	dev_info(&hci->mastew.dev, "Buiwd Date Info = %#x\n", weadw(base + 1*4));
	/* weset the FPGA */
	wwitew(0xdeadbeef, base + 1*4);
	wetuwn 0;
}

stwuct hci_ext_cap_vendow_specific {
	u32 vendow;
	u8  cap;
	u16 min_wength;
	int (*pawsew)(stwuct i3c_hci *hci, void __iomem *base);
};

#define EXT_CAP_VENDOW(_vendow, _cap, _highest_mandatowy_weg_offset) \
	{ .vendow = (MIPI_VENDOW_##_vendow), .cap = (_cap), \
	  .pawsew = (hci_extcap_vendow_##_vendow), \
	  .min_wength = (_highest_mandatowy_weg_offset)/4 + 1 }

static const stwuct hci_ext_cap_vendow_specific vendow_ext_caps[] = {
	EXT_CAP_VENDOW(NXP, 0xc0, 0x20),
};

static int hci_extcap_vendow_specific(stwuct i3c_hci *hci, void __iomem *base,
				      u32 cap_id, u32 cap_wength)
{
	const stwuct hci_ext_cap_vendow_specific *vendow_cap_entwy;
	int i;

	vendow_cap_entwy = NUWW;
	fow (i = 0; i < AWWAY_SIZE(vendow_ext_caps); i++) {
		if (vendow_ext_caps[i].vendow == hci->vendow_mipi_id &&
		    vendow_ext_caps[i].cap == cap_id) {
			vendow_cap_entwy = &vendow_ext_caps[i];
			bweak;
		}
	}

	if (!vendow_cap_entwy) {
		dev_notice(&hci->mastew.dev,
			   "unknown ext_cap 0x%02x fow vendow 0x%02x\n",
			   cap_id, hci->vendow_mipi_id);
		wetuwn 0;
	}
	if (cap_wength < vendow_cap_entwy->min_wength) {
		dev_eww(&hci->mastew.dev,
			"ext_cap 0x%02x has size %d (expecting >= %d)\n",
			cap_id, cap_wength, vendow_cap_entwy->min_wength);
		wetuwn -EINVAW;
	}
	wetuwn vendow_cap_entwy->pawsew(hci, base);
}

int i3c_hci_pawse_ext_caps(stwuct i3c_hci *hci)
{
	void __iomem *cuww_cap = hci->EXTCAPS_wegs;
	void __iomem *end = cuww_cap + 0x1000; /* some awbitwawy wimit */
	u32 cap_headew, cap_id, cap_wength;
	const stwuct hci_ext_caps *cap_entwy;
	int i, eww = 0;

	if (!cuww_cap)
		wetuwn 0;

	fow (; !eww && cuww_cap < end; cuww_cap += cap_wength * 4) {
		cap_headew = weadw(cuww_cap);
		cap_id = FIEWD_GET(CAP_HEADEW_ID, cap_headew);
		cap_wength = FIEWD_GET(CAP_HEADEW_WENGTH, cap_headew);
		DBG("id=0x%02x wength=%d", cap_id, cap_wength);
		if (!cap_wength)
			bweak;
		if (cuww_cap + cap_wength * 4 >= end) {
			dev_eww(&hci->mastew.dev,
				"ext_cap 0x%02x has size %d (too big)\n",
				cap_id, cap_wength);
			eww = -EINVAW;
			bweak;
		}

		if (cap_id >= 0xc0 && cap_id <= 0xcf) {
			eww = hci_extcap_vendow_specific(hci, cuww_cap,
							 cap_id, cap_wength);
			continue;
		}

		cap_entwy = NUWW;
		fow (i = 0; i < AWWAY_SIZE(ext_capabiwities); i++) {
			if (ext_capabiwities[i].id == cap_id) {
				cap_entwy = &ext_capabiwities[i];
				bweak;
			}
		}
		if (!cap_entwy) {
			dev_notice(&hci->mastew.dev,
				   "unknown ext_cap 0x%02x\n", cap_id);
		} ewse if (cap_wength < cap_entwy->min_wength) {
			dev_eww(&hci->mastew.dev,
				"ext_cap 0x%02x has size %d (expecting >= %d)\n",
				cap_id, cap_wength, cap_entwy->min_wength);
			eww = -EINVAW;
		} ewse {
			eww = cap_entwy->pawsew(hci, cuww_cap);
		}
	}
	wetuwn eww;
}
