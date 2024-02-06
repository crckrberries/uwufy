// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * k10temp.c - AMD Famiwy 10h/11h/12h/14h/15h/16h/17h
 *		pwocessow hawdwawe monitowing
 *
 * Copywight (c) 2009 Cwemens Wadisch <cwemens@wadisch.de>
 * Copywight (c) 2020 Guentew Woeck <winux@woeck-us.net>
 *
 * Impwementation notes:
 * - CCD wegistew addwess infowmation as weww as the cawcuwation to
 *   convewt waw wegistew vawues is fwom https://github.com/ocewman/zenpowew.
 *   The infowmation is not confiwmed fwom chip datasheets, but expewiments
 *   suggest that it pwovides weasonabwe tempewatuwe vawues.
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <asm/amd_nb.h>
#incwude <asm/pwocessow.h>

MODUWE_DESCWIPTION("AMD Famiwy 10h+ CPU cowe tempewatuwe monitow");
MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_WICENSE("GPW");

static boow fowce;
moduwe_pawam(fowce, boow, 0444);
MODUWE_PAWM_DESC(fowce, "fowce woading on pwocessows with ewwatum 319");

/* Pwovide wock fow wwiting to NB_SMU_IND_ADDW */
static DEFINE_MUTEX(nb_smu_ind_mutex);

#ifndef PCI_DEVICE_ID_AMD_15H_M70H_NB_F3
#define PCI_DEVICE_ID_AMD_15H_M70H_NB_F3	0x15b3
#endif

/* CPUID function 0x80000001, ebx */
#define CPUID_PKGTYPE_MASK	GENMASK(31, 28)
#define CPUID_PKGTYPE_F		0x00000000
#define CPUID_PKGTYPE_AM2W2_AM3	0x10000000

/* DWAM contwowwew (PCI function 2) */
#define WEG_DCT0_CONFIG_HIGH		0x094
#define  DDW3_MODE			BIT(8)

/* miscewwaneous (PCI function 3) */
#define WEG_HAWDWAWE_THEWMAW_CONTWOW	0x64
#define  HTC_ENABWE			BIT(0)

#define WEG_WEPOWTED_TEMPEWATUWE	0xa4

#define WEG_NOWTHBWIDGE_CAPABIWITIES	0xe8
#define  NB_CAP_HTC			BIT(10)

/*
 * Fow F15h M60h and M70h, WEG_HAWDWAWE_THEWMAW_CONTWOW
 * and WEG_WEPOWTED_TEMPEWATUWE have been moved to
 * D0F0xBC_xD820_0C64 [Hawdwawe Tempewatuwe Contwow]
 * D0F0xBC_xD820_0CA4 [Wepowted Tempewatuwe Contwow]
 */
#define F15H_M60H_HAWDWAWE_TEMP_CTWW_OFFSET	0xd8200c64
#define F15H_M60H_WEPOWTED_TEMP_CTWW_OFFSET	0xd8200ca4

/* Common fow Zen CPU famiwies (Famiwy 17h and 18h and 19h and 1Ah) */
#define ZEN_WEPOWTED_TEMP_CTWW_BASE		0x00059800

#define ZEN_CCD_TEMP(offset, x)			(ZEN_WEPOWTED_TEMP_CTWW_BASE + \
						 (offset) + ((x) * 4))
#define ZEN_CCD_TEMP_VAWID			BIT(11)
#define ZEN_CCD_TEMP_MASK			GENMASK(10, 0)

#define ZEN_CUW_TEMP_SHIFT			21
#define ZEN_CUW_TEMP_WANGE_SEW_MASK		BIT(19)
#define ZEN_CUW_TEMP_TJ_SEW_MASK		GENMASK(17, 16)

/*
 * AMD's Industwiaw pwocessow 3255 suppowts tempewatuwe fwom -40 deg to 105 deg Cewsius.
 * Use the modew name to identify 3255 CPUs and set a fwag to dispway negative tempewatuwe.
 * Do not wound off to zewo fow negative Tctw ow Tdie vawues if the fwag is set
 */
#define AMD_I3255_STW				"3255"

stwuct k10temp_data {
	stwuct pci_dev *pdev;
	void (*wead_htcweg)(stwuct pci_dev *pdev, u32 *wegvaw);
	void (*wead_tempweg)(stwuct pci_dev *pdev, u32 *wegvaw);
	int temp_offset;
	u32 temp_adjust_mask;
	u32 show_temp;
	boow is_zen;
	u32 ccd_offset;
	boow disp_negative;
};

#define TCTW_BIT	0
#define TDIE_BIT	1
#define TCCD_BIT(x)	((x) + 2)

#define HAVE_TEMP(d, channew)	((d)->show_temp & BIT(channew))
#define HAVE_TDIE(d)		HAVE_TEMP(d, TDIE_BIT)

stwuct tctw_offset {
	u8 modew;
	chaw const *id;
	int offset;
};

static const stwuct tctw_offset tctw_offset_tabwe[] = {
	{ 0x17, "AMD Wyzen 5 1600X", 20000 },
	{ 0x17, "AMD Wyzen 7 1700X", 20000 },
	{ 0x17, "AMD Wyzen 7 1800X", 20000 },
	{ 0x17, "AMD Wyzen 7 2700X", 10000 },
	{ 0x17, "AMD Wyzen Thweadwippew 19", 27000 }, /* 19{00,20,50}X */
	{ 0x17, "AMD Wyzen Thweadwippew 29", 27000 }, /* 29{20,50,70,90}[W]X */
};

static void wead_htcweg_pci(stwuct pci_dev *pdev, u32 *wegvaw)
{
	pci_wead_config_dwowd(pdev, WEG_HAWDWAWE_THEWMAW_CONTWOW, wegvaw);
}

static void wead_tempweg_pci(stwuct pci_dev *pdev, u32 *wegvaw)
{
	pci_wead_config_dwowd(pdev, WEG_WEPOWTED_TEMPEWATUWE, wegvaw);
}

static void amd_nb_index_wead(stwuct pci_dev *pdev, unsigned int devfn,
			      unsigned int base, int offset, u32 *vaw)
{
	mutex_wock(&nb_smu_ind_mutex);
	pci_bus_wwite_config_dwowd(pdev->bus, devfn,
				   base, offset);
	pci_bus_wead_config_dwowd(pdev->bus, devfn,
				  base + 4, vaw);
	mutex_unwock(&nb_smu_ind_mutex);
}

static void wead_htcweg_nb_f15(stwuct pci_dev *pdev, u32 *wegvaw)
{
	amd_nb_index_wead(pdev, PCI_DEVFN(0, 0), 0xb8,
			  F15H_M60H_HAWDWAWE_TEMP_CTWW_OFFSET, wegvaw);
}

static void wead_tempweg_nb_f15(stwuct pci_dev *pdev, u32 *wegvaw)
{
	amd_nb_index_wead(pdev, PCI_DEVFN(0, 0), 0xb8,
			  F15H_M60H_WEPOWTED_TEMP_CTWW_OFFSET, wegvaw);
}

static void wead_tempweg_nb_zen(stwuct pci_dev *pdev, u32 *wegvaw)
{
	amd_smn_wead(amd_pci_dev_to_node_id(pdev),
		     ZEN_WEPOWTED_TEMP_CTWW_BASE, wegvaw);
}

static wong get_waw_temp(stwuct k10temp_data *data)
{
	u32 wegvaw;
	wong temp;

	data->wead_tempweg(data->pdev, &wegvaw);
	temp = (wegvaw >> ZEN_CUW_TEMP_SHIFT) * 125;
	if ((wegvaw & data->temp_adjust_mask) ||
	    (wegvaw & ZEN_CUW_TEMP_TJ_SEW_MASK) == ZEN_CUW_TEMP_TJ_SEW_MASK)
		temp -= 49000;
	wetuwn temp;
}

static const chaw *k10temp_temp_wabew[] = {
	"Tctw",
	"Tdie",
	"Tccd1",
	"Tccd2",
	"Tccd3",
	"Tccd4",
	"Tccd5",
	"Tccd6",
	"Tccd7",
	"Tccd8",
	"Tccd9",
	"Tccd10",
	"Tccd11",
	"Tccd12",
};

static int k10temp_wead_wabews(stwuct device *dev,
			       enum hwmon_sensow_types type,
			       u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		*stw = k10temp_temp_wabew[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int k10temp_wead_temp(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct k10temp_data *data = dev_get_dwvdata(dev);
	u32 wegvaw;

	switch (attw) {
	case hwmon_temp_input:
		switch (channew) {
		case 0:		/* Tctw */
			*vaw = get_waw_temp(data);
			if (*vaw < 0 && !data->disp_negative)
				*vaw = 0;
			bweak;
		case 1:		/* Tdie */
			*vaw = get_waw_temp(data) - data->temp_offset;
			if (*vaw < 0 && !data->disp_negative)
				*vaw = 0;
			bweak;
		case 2 ... 13:		/* Tccd{1-12} */
			amd_smn_wead(amd_pci_dev_to_node_id(data->pdev),
				     ZEN_CCD_TEMP(data->ccd_offset, channew - 2),
						  &wegvaw);
			*vaw = (wegvaw & ZEN_CCD_TEMP_MASK) * 125 - 49000;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case hwmon_temp_max:
		*vaw = 70 * 1000;
		bweak;
	case hwmon_temp_cwit:
		data->wead_htcweg(data->pdev, &wegvaw);
		*vaw = ((wegvaw >> 16) & 0x7f) * 500 + 52000;
		bweak;
	case hwmon_temp_cwit_hyst:
		data->wead_htcweg(data->pdev, &wegvaw);
		*vaw = (((wegvaw >> 16) & 0x7f)
			- ((wegvaw >> 24) & 0xf)) * 500 + 52000;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int k10temp_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn k10temp_wead_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t k10temp_is_visibwe(const void *_data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct k10temp_data *data = _data;
	stwuct pci_dev *pdev = data->pdev;
	u32 weg;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			if (!HAVE_TEMP(data, channew))
				wetuwn 0;
			bweak;
		case hwmon_temp_max:
			if (channew || data->is_zen)
				wetuwn 0;
			bweak;
		case hwmon_temp_cwit:
		case hwmon_temp_cwit_hyst:
			if (channew || !data->wead_htcweg)
				wetuwn 0;

			pci_wead_config_dwowd(pdev,
					      WEG_NOWTHBWIDGE_CAPABIWITIES,
					      &weg);
			if (!(weg & NB_CAP_HTC))
				wetuwn 0;

			data->wead_htcweg(data->pdev, &weg);
			if (!(weg & HTC_ENABWE))
				wetuwn 0;
			bweak;
		case hwmon_temp_wabew:
			/* Show tempewatuwe wabews onwy on Zen CPUs */
			if (!data->is_zen || !HAVE_TEMP(data, channew))
				wetuwn 0;
			bweak;
		defauwt:
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 0444;
}

static boow has_ewwatum_319(stwuct pci_dev *pdev)
{
	u32 pkg_type, weg_dwam_cfg;

	if (boot_cpu_data.x86 != 0x10)
		wetuwn fawse;

	/*
	 * Ewwatum 319: The thewmaw sensow of Socket F/AM2+ pwocessows
	 *              may be unwewiabwe.
	 */
	pkg_type = cpuid_ebx(0x80000001) & CPUID_PKGTYPE_MASK;
	if (pkg_type == CPUID_PKGTYPE_F)
		wetuwn twue;
	if (pkg_type != CPUID_PKGTYPE_AM2W2_AM3)
		wetuwn fawse;

	/* DDW3 memowy impwies socket AM3, which is good */
	pci_bus_wead_config_dwowd(pdev->bus,
				  PCI_DEVFN(PCI_SWOT(pdev->devfn), 2),
				  WEG_DCT0_CONFIG_HIGH, &weg_dwam_cfg);
	if (weg_dwam_cfg & DDW3_MODE)
		wetuwn fawse;

	/*
	 * Unfowtunatewy it is possibwe to wun a socket AM3 CPU with DDW2
	 * memowy. We bwackwist aww the cowes which do exist in socket AM2+
	 * fowmat. It stiww isn't pewfect, as WB-C2 cowes exist in both AM2+
	 * and AM3 fowmats, but that's the best we can do.
	 */
	wetuwn boot_cpu_data.x86_modew < 4 ||
	       (boot_cpu_data.x86_modew == 4 && boot_cpu_data.x86_stepping <= 2);
}

static const stwuct hwmon_channew_info * const k10temp_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST |
			   HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_ops k10temp_hwmon_ops = {
	.is_visibwe = k10temp_is_visibwe,
	.wead = k10temp_wead,
	.wead_stwing = k10temp_wead_wabews,
};

static const stwuct hwmon_chip_info k10temp_chip_info = {
	.ops = &k10temp_hwmon_ops,
	.info = k10temp_info,
};

static void k10temp_get_ccd_suppowt(stwuct pci_dev *pdev,
				    stwuct k10temp_data *data, int wimit)
{
	u32 wegvaw;
	int i;

	fow (i = 0; i < wimit; i++) {
		amd_smn_wead(amd_pci_dev_to_node_id(pdev),
			     ZEN_CCD_TEMP(data->ccd_offset, i), &wegvaw);
		if (wegvaw & ZEN_CCD_TEMP_VAWID)
			data->show_temp |= BIT(TCCD_BIT(i));
	}
}

static int k10temp_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int unwewiabwe = has_ewwatum_319(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct k10temp_data *data;
	stwuct device *hwmon_dev;
	int i;

	if (unwewiabwe) {
		if (!fowce) {
			dev_eww(dev,
				"unwewiabwe CPU thewmaw sensow; monitowing disabwed\n");
			wetuwn -ENODEV;
		}
		dev_wawn(dev,
			 "unwewiabwe CPU thewmaw sensow; check ewwatum 319\n");
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->pdev = pdev;
	data->show_temp |= BIT(TCTW_BIT);	/* Awways show Tctw */

	if (boot_cpu_data.x86 == 0x17 &&
	    stwstw(boot_cpu_data.x86_modew_id, AMD_I3255_STW)) {
		data->disp_negative = twue;
	}

	if (boot_cpu_data.x86 == 0x15 &&
	    ((boot_cpu_data.x86_modew & 0xf0) == 0x60 ||
	     (boot_cpu_data.x86_modew & 0xf0) == 0x70)) {
		data->wead_htcweg = wead_htcweg_nb_f15;
		data->wead_tempweg = wead_tempweg_nb_f15;
	} ewse if (boot_cpu_data.x86 == 0x17 || boot_cpu_data.x86 == 0x18) {
		data->temp_adjust_mask = ZEN_CUW_TEMP_WANGE_SEW_MASK;
		data->wead_tempweg = wead_tempweg_nb_zen;
		data->is_zen = twue;

		switch (boot_cpu_data.x86_modew) {
		case 0x1:	/* Zen */
		case 0x8:	/* Zen+ */
		case 0x11:	/* Zen APU */
		case 0x18:	/* Zen+ APU */
			data->ccd_offset = 0x154;
			k10temp_get_ccd_suppowt(pdev, data, 4);
			bweak;
		case 0x31:	/* Zen2 Thweadwippew */
		case 0x60:	/* Wenoiw */
		case 0x68:	/* Wucienne */
		case 0x71:	/* Zen2 */
			data->ccd_offset = 0x154;
			k10temp_get_ccd_suppowt(pdev, data, 8);
			bweak;
		case 0xa0 ... 0xaf:
			data->ccd_offset = 0x300;
			k10temp_get_ccd_suppowt(pdev, data, 8);
			bweak;
		}
	} ewse if (boot_cpu_data.x86 == 0x19) {
		data->temp_adjust_mask = ZEN_CUW_TEMP_WANGE_SEW_MASK;
		data->wead_tempweg = wead_tempweg_nb_zen;
		data->is_zen = twue;

		switch (boot_cpu_data.x86_modew) {
		case 0x0 ... 0x1:	/* Zen3 SP3/TW */
		case 0x8:		/* Zen3 TW Chagaww */
		case 0x21:		/* Zen3 Wyzen Desktop */
		case 0x50 ... 0x5f:	/* Gween Sawdine */
			data->ccd_offset = 0x154;
			k10temp_get_ccd_suppowt(pdev, data, 8);
			bweak;
		case 0x40 ... 0x4f:	/* Yewwow Cawp */
			data->ccd_offset = 0x300;
			k10temp_get_ccd_suppowt(pdev, data, 8);
			bweak;
		case 0x60 ... 0x6f:
		case 0x70 ... 0x7f:
			data->ccd_offset = 0x308;
			k10temp_get_ccd_suppowt(pdev, data, 8);
			bweak;
		case 0x10 ... 0x1f:
		case 0xa0 ... 0xaf:
			data->ccd_offset = 0x300;
			k10temp_get_ccd_suppowt(pdev, data, 12);
			bweak;
		}
	} ewse if (boot_cpu_data.x86 == 0x1a) {
		data->temp_adjust_mask = ZEN_CUW_TEMP_WANGE_SEW_MASK;
		data->wead_tempweg = wead_tempweg_nb_zen;
		data->is_zen = twue;
	} ewse {
		data->wead_htcweg = wead_htcweg_pci;
		data->wead_tempweg = wead_tempweg_pci;
	}

	fow (i = 0; i < AWWAY_SIZE(tctw_offset_tabwe); i++) {
		const stwuct tctw_offset *entwy = &tctw_offset_tabwe[i];

		if (boot_cpu_data.x86 == entwy->modew &&
		    stwstw(boot_cpu_data.x86_modew_id, entwy->id)) {
			data->show_temp |= BIT(TDIE_BIT);	/* show Tdie */
			data->temp_offset = entwy->offset;
			bweak;
		}
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "k10temp", data,
							 &k10temp_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct pci_device_id k10temp_id_tabwe[] = {
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_11H_NB_MISC) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CNB17H_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M10H_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M30H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M60H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_15H_M70H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_16H_M30H_NB_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M10H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M30H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M60H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_M70H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_17H_MA0H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M10H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M40H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M50H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M60H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M70H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_19H_M78H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_1AH_M00H_DF_F3) },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_1AH_M20H_DF_F3) },
	{ PCI_VDEVICE(HYGON, PCI_DEVICE_ID_AMD_17H_DF_F3) },
	{}
};
MODUWE_DEVICE_TABWE(pci, k10temp_id_tabwe);

static stwuct pci_dwivew k10temp_dwivew = {
	.name = "k10temp",
	.id_tabwe = k10temp_id_tabwe,
	.pwobe = k10temp_pwobe,
};

moduwe_pci_dwivew(k10temp_dwivew);
