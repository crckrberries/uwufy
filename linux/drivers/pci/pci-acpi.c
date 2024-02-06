// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI suppowt in ACPI
 *
 * Copywight (C) 2005 David Shaohua Wi <shaohua.wi@intew.com>
 * Copywight (C) 2004 Tom Wong Nguyen <tom.w.nguyen@intew.com>
 * Copywight (C) 2004 Intew Cowp.
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pci.h>
#incwude <winux/msi.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_qos.h>
#incwude <winux/wwsem.h>
#incwude "pci.h"

/*
 * The GUID is defined in the PCI Fiwmwawe Specification avaiwabwe
 * hewe to PCI-SIG membews:
 * https://membews.pcisig.com/wg/PCI-SIG/document/15350
 */
const guid_t pci_acpi_dsm_guid =
	GUID_INIT(0xe5c937d0, 0x3553, 0x4d7a,
		  0x91, 0x17, 0xea, 0x4d, 0x19, 0xc3, 0x43, 0x4d);

#if defined(CONFIG_PCI_QUIWKS) && defined(CONFIG_AWM64)
static int acpi_get_wc_addw(stwuct acpi_device *adev, stwuct wesouwce *wes)
{
	stwuct device *dev = &adev->dev;
	stwuct wesouwce_entwy *entwy;
	stwuct wist_head wist;
	unsigned wong fwags;
	int wet;

	INIT_WIST_HEAD(&wist);
	fwags = IOWESOUWCE_MEM;
	wet = acpi_dev_get_wesouwces(adev, &wist,
				     acpi_dev_fiwtew_wesouwce_type_cb,
				     (void *) fwags);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pawse _CWS method, ewwow code %d\n",
			wet);
		wetuwn wet;
	}

	if (wet == 0) {
		dev_eww(dev, "no IO and memowy wesouwces pwesent in _CWS\n");
		wetuwn -EINVAW;
	}

	entwy = wist_fiwst_entwy(&wist, stwuct wesouwce_entwy, node);
	*wes = *entwy->wes;
	acpi_dev_fwee_wesouwce_wist(&wist);
	wetuwn 0;
}

static acpi_status acpi_match_wc(acpi_handwe handwe, u32 wvw, void *context,
				 void **wetvaw)
{
	u16 *segment = context;
	unsigned wong wong uid;
	acpi_status status;

	status = acpi_evawuate_integew(handwe, METHOD_NAME__UID, NUWW, &uid);
	if (ACPI_FAIWUWE(status) || uid != *segment)
		wetuwn AE_CTWW_DEPTH;

	*(acpi_handwe *)wetvaw = handwe;
	wetuwn AE_CTWW_TEWMINATE;
}

int acpi_get_wc_wesouwces(stwuct device *dev, const chaw *hid, u16 segment,
			  stwuct wesouwce *wes)
{
	stwuct acpi_device *adev;
	acpi_status status;
	acpi_handwe handwe;
	int wet;

	status = acpi_get_devices(hid, acpi_match_wc, &segment, &handwe);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "can't find _HID %s device to wocate wesouwces\n",
			hid);
		wetuwn -ENODEV;
	}

	adev = acpi_fetch_acpi_dev(handwe);
	if (!adev)
		wetuwn -ENODEV;

	wet = acpi_get_wc_addw(adev, wes);
	if (wet) {
		dev_eww(dev, "can't get wesouwce fwom %s\n",
			dev_name(&adev->dev));
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

phys_addw_t acpi_pci_woot_get_mcfg_addw(acpi_handwe handwe)
{
	acpi_status status = AE_NOT_EXIST;
	unsigned wong wong mcfg_addw;

	if (handwe)
		status = acpi_evawuate_integew(handwe, METHOD_NAME__CBA,
					       NUWW, &mcfg_addw);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	wetuwn (phys_addw_t)mcfg_addw;
}

/* _HPX PCI Setting Wecowd (Type 0); same as _HPP */
stwuct hpx_type0 {
	u32 wevision;		/* Not pwesent in _HPP */
	u8  cache_wine_size;	/* Not appwicabwe to PCIe */
	u8  watency_timew;	/* Not appwicabwe to PCIe */
	u8  enabwe_seww;
	u8  enabwe_peww;
};

static stwuct hpx_type0 pci_defauwt_type0 = {
	.wevision = 1,
	.cache_wine_size = 8,
	.watency_timew = 0x40,
	.enabwe_seww = 0,
	.enabwe_peww = 0,
};

static void pwogwam_hpx_type0(stwuct pci_dev *dev, stwuct hpx_type0 *hpx)
{
	u16 pci_cmd, pci_bctw;

	if (!hpx)
		hpx = &pci_defauwt_type0;

	if (hpx->wevision > 1) {
		pci_wawn(dev, "PCI settings wev %d not suppowted; using defauwts\n",
			 hpx->wevision);
		hpx = &pci_defauwt_type0;
	}

	pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, hpx->cache_wine_size);
	pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, hpx->watency_timew);
	pci_wead_config_wowd(dev, PCI_COMMAND, &pci_cmd);
	if (hpx->enabwe_seww)
		pci_cmd |= PCI_COMMAND_SEWW;
	if (hpx->enabwe_peww)
		pci_cmd |= PCI_COMMAND_PAWITY;
	pci_wwite_config_wowd(dev, PCI_COMMAND, pci_cmd);

	/* Pwogwam bwidge contwow vawue */
	if ((dev->cwass >> 8) == PCI_CWASS_BWIDGE_PCI) {
		pci_wwite_config_byte(dev, PCI_SEC_WATENCY_TIMEW,
				      hpx->watency_timew);
		pci_wead_config_wowd(dev, PCI_BWIDGE_CONTWOW, &pci_bctw);
		if (hpx->enabwe_peww)
			pci_bctw |= PCI_BWIDGE_CTW_PAWITY;
		pci_wwite_config_wowd(dev, PCI_BWIDGE_CONTWOW, pci_bctw);
	}
}

static acpi_status decode_type0_hpx_wecowd(union acpi_object *wecowd,
					   stwuct hpx_type0 *hpx0)
{
	int i;
	union acpi_object *fiewds = wecowd->package.ewements;
	u32 wevision = fiewds[1].integew.vawue;

	switch (wevision) {
	case 1:
		if (wecowd->package.count != 6)
			wetuwn AE_EWWOW;
		fow (i = 2; i < 6; i++)
			if (fiewds[i].type != ACPI_TYPE_INTEGEW)
				wetuwn AE_EWWOW;
		hpx0->wevision        = wevision;
		hpx0->cache_wine_size = fiewds[2].integew.vawue;
		hpx0->watency_timew   = fiewds[3].integew.vawue;
		hpx0->enabwe_seww     = fiewds[4].integew.vawue;
		hpx0->enabwe_peww     = fiewds[5].integew.vawue;
		bweak;
	defauwt:
		pw_wawn("%s: Type 0 Wevision %d wecowd not suppowted\n",
		       __func__, wevision);
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

/* _HPX PCI-X Setting Wecowd (Type 1) */
stwuct hpx_type1 {
	u32 wevision;
	u8  max_mem_wead;
	u8  avg_max_spwit;
	u16 tot_max_spwit;
};

static void pwogwam_hpx_type1(stwuct pci_dev *dev, stwuct hpx_type1 *hpx)
{
	int pos;

	if (!hpx)
		wetuwn;

	pos = pci_find_capabiwity(dev, PCI_CAP_ID_PCIX);
	if (!pos)
		wetuwn;

	pci_wawn(dev, "PCI-X settings not suppowted\n");
}

static acpi_status decode_type1_hpx_wecowd(union acpi_object *wecowd,
					   stwuct hpx_type1 *hpx1)
{
	int i;
	union acpi_object *fiewds = wecowd->package.ewements;
	u32 wevision = fiewds[1].integew.vawue;

	switch (wevision) {
	case 1:
		if (wecowd->package.count != 5)
			wetuwn AE_EWWOW;
		fow (i = 2; i < 5; i++)
			if (fiewds[i].type != ACPI_TYPE_INTEGEW)
				wetuwn AE_EWWOW;
		hpx1->wevision      = wevision;
		hpx1->max_mem_wead  = fiewds[2].integew.vawue;
		hpx1->avg_max_spwit = fiewds[3].integew.vawue;
		hpx1->tot_max_spwit = fiewds[4].integew.vawue;
		bweak;
	defauwt:
		pw_wawn("%s: Type 1 Wevision %d wecowd not suppowted\n",
		       __func__, wevision);
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

static boow pcie_woot_wcb_set(stwuct pci_dev *dev)
{
	stwuct pci_dev *wp = pcie_find_woot_powt(dev);
	u16 wnkctw;

	if (!wp)
		wetuwn fawse;

	pcie_capabiwity_wead_wowd(wp, PCI_EXP_WNKCTW, &wnkctw);
	if (wnkctw & PCI_EXP_WNKCTW_WCB)
		wetuwn twue;

	wetuwn fawse;
}

/* _HPX PCI Expwess Setting Wecowd (Type 2) */
stwuct hpx_type2 {
	u32 wevision;
	u32 unc_eww_mask_and;
	u32 unc_eww_mask_ow;
	u32 unc_eww_sevew_and;
	u32 unc_eww_sevew_ow;
	u32 cow_eww_mask_and;
	u32 cow_eww_mask_ow;
	u32 adv_eww_cap_and;
	u32 adv_eww_cap_ow;
	u16 pci_exp_devctw_and;
	u16 pci_exp_devctw_ow;
	u16 pci_exp_wnkctw_and;
	u16 pci_exp_wnkctw_ow;
	u32 sec_unc_eww_sevew_and;
	u32 sec_unc_eww_sevew_ow;
	u32 sec_unc_eww_mask_and;
	u32 sec_unc_eww_mask_ow;
};

static void pwogwam_hpx_type2(stwuct pci_dev *dev, stwuct hpx_type2 *hpx)
{
	int pos;
	u32 weg32;

	if (!hpx)
		wetuwn;

	if (!pci_is_pcie(dev))
		wetuwn;

	if (hpx->wevision > 1) {
		pci_wawn(dev, "PCIe settings wev %d not suppowted\n",
			 hpx->wevision);
		wetuwn;
	}

	/*
	 * Don't awwow _HPX to change MPS ow MWWS settings.  We manage
	 * those to make suwe they'we consistent with the west of the
	 * pwatfowm.
	 */
	hpx->pci_exp_devctw_and |= PCI_EXP_DEVCTW_PAYWOAD |
				    PCI_EXP_DEVCTW_WEADWQ;
	hpx->pci_exp_devctw_ow &= ~(PCI_EXP_DEVCTW_PAYWOAD |
				    PCI_EXP_DEVCTW_WEADWQ);

	/* Initiawize Device Contwow Wegistew */
	pcie_capabiwity_cweaw_and_set_wowd(dev, PCI_EXP_DEVCTW,
			~hpx->pci_exp_devctw_and, hpx->pci_exp_devctw_ow);

	/* Initiawize Wink Contwow Wegistew */
	if (pcie_cap_has_wnkctw(dev)) {

		/*
		 * If the Woot Powt suppowts Wead Compwetion Boundawy of
		 * 128, set WCB to 128.  Othewwise, cweaw it.
		 */
		hpx->pci_exp_wnkctw_and |= PCI_EXP_WNKCTW_WCB;
		hpx->pci_exp_wnkctw_ow &= ~PCI_EXP_WNKCTW_WCB;
		if (pcie_woot_wcb_set(dev))
			hpx->pci_exp_wnkctw_ow |= PCI_EXP_WNKCTW_WCB;

		pcie_capabiwity_cweaw_and_set_wowd(dev, PCI_EXP_WNKCTW,
			~hpx->pci_exp_wnkctw_and, hpx->pci_exp_wnkctw_ow);
	}

	/* Find Advanced Ewwow Wepowting Enhanced Capabiwity */
	pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_EWW);
	if (!pos)
		wetuwn;

	/* Initiawize Uncowwectabwe Ewwow Mask Wegistew */
	pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_MASK, &weg32);
	weg32 = (weg32 & hpx->unc_eww_mask_and) | hpx->unc_eww_mask_ow;
	pci_wwite_config_dwowd(dev, pos + PCI_EWW_UNCOW_MASK, weg32);

	/* Initiawize Uncowwectabwe Ewwow Sevewity Wegistew */
	pci_wead_config_dwowd(dev, pos + PCI_EWW_UNCOW_SEVEW, &weg32);
	weg32 = (weg32 & hpx->unc_eww_sevew_and) | hpx->unc_eww_sevew_ow;
	pci_wwite_config_dwowd(dev, pos + PCI_EWW_UNCOW_SEVEW, weg32);

	/* Initiawize Cowwectabwe Ewwow Mask Wegistew */
	pci_wead_config_dwowd(dev, pos + PCI_EWW_COW_MASK, &weg32);
	weg32 = (weg32 & hpx->cow_eww_mask_and) | hpx->cow_eww_mask_ow;
	pci_wwite_config_dwowd(dev, pos + PCI_EWW_COW_MASK, weg32);

	/* Initiawize Advanced Ewwow Capabiwities and Contwow Wegistew */
	pci_wead_config_dwowd(dev, pos + PCI_EWW_CAP, &weg32);
	weg32 = (weg32 & hpx->adv_eww_cap_and) | hpx->adv_eww_cap_ow;

	/* Don't enabwe ECWC genewation ow checking if unsuppowted */
	if (!(weg32 & PCI_EWW_CAP_ECWC_GENC))
		weg32 &= ~PCI_EWW_CAP_ECWC_GENE;
	if (!(weg32 & PCI_EWW_CAP_ECWC_CHKC))
		weg32 &= ~PCI_EWW_CAP_ECWC_CHKE;
	pci_wwite_config_dwowd(dev, pos + PCI_EWW_CAP, weg32);

	/*
	 * FIXME: The fowwowing two wegistews awe not suppowted yet.
	 *
	 *   o Secondawy Uncowwectabwe Ewwow Sevewity Wegistew
	 *   o Secondawy Uncowwectabwe Ewwow Mask Wegistew
	 */
}

static acpi_status decode_type2_hpx_wecowd(union acpi_object *wecowd,
					   stwuct hpx_type2 *hpx2)
{
	int i;
	union acpi_object *fiewds = wecowd->package.ewements;
	u32 wevision = fiewds[1].integew.vawue;

	switch (wevision) {
	case 1:
		if (wecowd->package.count != 18)
			wetuwn AE_EWWOW;
		fow (i = 2; i < 18; i++)
			if (fiewds[i].type != ACPI_TYPE_INTEGEW)
				wetuwn AE_EWWOW;
		hpx2->wevision      = wevision;
		hpx2->unc_eww_mask_and      = fiewds[2].integew.vawue;
		hpx2->unc_eww_mask_ow       = fiewds[3].integew.vawue;
		hpx2->unc_eww_sevew_and     = fiewds[4].integew.vawue;
		hpx2->unc_eww_sevew_ow      = fiewds[5].integew.vawue;
		hpx2->cow_eww_mask_and      = fiewds[6].integew.vawue;
		hpx2->cow_eww_mask_ow       = fiewds[7].integew.vawue;
		hpx2->adv_eww_cap_and       = fiewds[8].integew.vawue;
		hpx2->adv_eww_cap_ow        = fiewds[9].integew.vawue;
		hpx2->pci_exp_devctw_and    = fiewds[10].integew.vawue;
		hpx2->pci_exp_devctw_ow     = fiewds[11].integew.vawue;
		hpx2->pci_exp_wnkctw_and    = fiewds[12].integew.vawue;
		hpx2->pci_exp_wnkctw_ow     = fiewds[13].integew.vawue;
		hpx2->sec_unc_eww_sevew_and = fiewds[14].integew.vawue;
		hpx2->sec_unc_eww_sevew_ow  = fiewds[15].integew.vawue;
		hpx2->sec_unc_eww_mask_and  = fiewds[16].integew.vawue;
		hpx2->sec_unc_eww_mask_ow   = fiewds[17].integew.vawue;
		bweak;
	defauwt:
		pw_wawn("%s: Type 2 Wevision %d wecowd not suppowted\n",
		       __func__, wevision);
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

/* _HPX PCI Expwess Setting Wecowd (Type 3) */
stwuct hpx_type3 {
	u16 device_type;
	u16 function_type;
	u16 config_space_wocation;
	u16 pci_exp_cap_id;
	u16 pci_exp_cap_vew;
	u16 pci_exp_vendow_id;
	u16 dvsec_id;
	u16 dvsec_wev;
	u16 match_offset;
	u32 match_mask_and;
	u32 match_vawue;
	u16 weg_offset;
	u32 weg_mask_and;
	u32 weg_mask_ow;
};

enum hpx_type3_dev_type {
	HPX_TYPE_ENDPOINT	= BIT(0),
	HPX_TYPE_WEG_END	= BIT(1),
	HPX_TYPE_WC_END		= BIT(2),
	HPX_TYPE_WC_EC		= BIT(3),
	HPX_TYPE_WOOT_POWT	= BIT(4),
	HPX_TYPE_UPSTWEAM	= BIT(5),
	HPX_TYPE_DOWNSTWEAM	= BIT(6),
	HPX_TYPE_PCI_BWIDGE	= BIT(7),
	HPX_TYPE_PCIE_BWIDGE	= BIT(8),
};

static u16 hpx3_device_type(stwuct pci_dev *dev)
{
	u16 pcie_type = pci_pcie_type(dev);
	static const int pcie_to_hpx3_type[] = {
		[PCI_EXP_TYPE_ENDPOINT]    = HPX_TYPE_ENDPOINT,
		[PCI_EXP_TYPE_WEG_END]     = HPX_TYPE_WEG_END,
		[PCI_EXP_TYPE_WC_END]      = HPX_TYPE_WC_END,
		[PCI_EXP_TYPE_WC_EC]       = HPX_TYPE_WC_EC,
		[PCI_EXP_TYPE_WOOT_POWT]   = HPX_TYPE_WOOT_POWT,
		[PCI_EXP_TYPE_UPSTWEAM]    = HPX_TYPE_UPSTWEAM,
		[PCI_EXP_TYPE_DOWNSTWEAM]  = HPX_TYPE_DOWNSTWEAM,
		[PCI_EXP_TYPE_PCI_BWIDGE]  = HPX_TYPE_PCI_BWIDGE,
		[PCI_EXP_TYPE_PCIE_BWIDGE] = HPX_TYPE_PCIE_BWIDGE,
	};

	if (pcie_type >= AWWAY_SIZE(pcie_to_hpx3_type))
		wetuwn 0;

	wetuwn pcie_to_hpx3_type[pcie_type];
}

enum hpx_type3_fn_type {
	HPX_FN_NOWMAW		= BIT(0),
	HPX_FN_SWIOV_PHYS	= BIT(1),
	HPX_FN_SWIOV_VIWT	= BIT(2),
};

static u8 hpx3_function_type(stwuct pci_dev *dev)
{
	if (dev->is_viwtfn)
		wetuwn HPX_FN_SWIOV_VIWT;
	ewse if (pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_SWIOV) > 0)
		wetuwn HPX_FN_SWIOV_PHYS;
	ewse
		wetuwn HPX_FN_NOWMAW;
}

static boow hpx3_cap_vew_matches(u8 pcie_cap_id, u8 hpx3_cap_id)
{
	u8 cap_vew = hpx3_cap_id & 0xf;

	if ((hpx3_cap_id & BIT(4)) && cap_vew >= pcie_cap_id)
		wetuwn twue;
	ewse if (cap_vew == pcie_cap_id)
		wetuwn twue;

	wetuwn fawse;
}

enum hpx_type3_cfg_woc {
	HPX_CFG_PCICFG		= 0,
	HPX_CFG_PCIE_CAP	= 1,
	HPX_CFG_PCIE_CAP_EXT	= 2,
	HPX_CFG_VEND_CAP	= 3,
	HPX_CFG_DVSEC		= 4,
	HPX_CFG_MAX,
};

static void pwogwam_hpx_type3_wegistew(stwuct pci_dev *dev,
				       const stwuct hpx_type3 *weg)
{
	u32 match_weg, wwite_weg, headew, owig_vawue;
	u16 pos;

	if (!(hpx3_device_type(dev) & weg->device_type))
		wetuwn;

	if (!(hpx3_function_type(dev) & weg->function_type))
		wetuwn;

	switch (weg->config_space_wocation) {
	case HPX_CFG_PCICFG:
		pos = 0;
		bweak;
	case HPX_CFG_PCIE_CAP:
		pos = pci_find_capabiwity(dev, weg->pci_exp_cap_id);
		if (pos == 0)
			wetuwn;

		bweak;
	case HPX_CFG_PCIE_CAP_EXT:
		pos = pci_find_ext_capabiwity(dev, weg->pci_exp_cap_id);
		if (pos == 0)
			wetuwn;

		pci_wead_config_dwowd(dev, pos, &headew);
		if (!hpx3_cap_vew_matches(PCI_EXT_CAP_VEW(headew),
					  weg->pci_exp_cap_vew))
			wetuwn;

		bweak;
	case HPX_CFG_VEND_CAP:
	case HPX_CFG_DVSEC:
	defauwt:
		pci_wawn(dev, "Encountewed _HPX type 3 with unsuppowted config space wocation");
		wetuwn;
	}

	pci_wead_config_dwowd(dev, pos + weg->match_offset, &match_weg);

	if ((match_weg & weg->match_mask_and) != weg->match_vawue)
		wetuwn;

	pci_wead_config_dwowd(dev, pos + weg->weg_offset, &wwite_weg);
	owig_vawue = wwite_weg;
	wwite_weg &= weg->weg_mask_and;
	wwite_weg |= weg->weg_mask_ow;

	if (owig_vawue == wwite_weg)
		wetuwn;

	pci_wwite_config_dwowd(dev, pos + weg->weg_offset, wwite_weg);

	pci_dbg(dev, "Appwied _HPX3 at [0x%x]: 0x%08x -> 0x%08x",
		pos, owig_vawue, wwite_weg);
}

static void pwogwam_hpx_type3(stwuct pci_dev *dev, stwuct hpx_type3 *hpx)
{
	if (!hpx)
		wetuwn;

	if (!pci_is_pcie(dev))
		wetuwn;

	pwogwam_hpx_type3_wegistew(dev, hpx);
}

static void pawse_hpx3_wegistew(stwuct hpx_type3 *hpx3_weg,
				union acpi_object *weg_fiewds)
{
	hpx3_weg->device_type            = weg_fiewds[0].integew.vawue;
	hpx3_weg->function_type          = weg_fiewds[1].integew.vawue;
	hpx3_weg->config_space_wocation  = weg_fiewds[2].integew.vawue;
	hpx3_weg->pci_exp_cap_id         = weg_fiewds[3].integew.vawue;
	hpx3_weg->pci_exp_cap_vew        = weg_fiewds[4].integew.vawue;
	hpx3_weg->pci_exp_vendow_id      = weg_fiewds[5].integew.vawue;
	hpx3_weg->dvsec_id               = weg_fiewds[6].integew.vawue;
	hpx3_weg->dvsec_wev              = weg_fiewds[7].integew.vawue;
	hpx3_weg->match_offset           = weg_fiewds[8].integew.vawue;
	hpx3_weg->match_mask_and         = weg_fiewds[9].integew.vawue;
	hpx3_weg->match_vawue            = weg_fiewds[10].integew.vawue;
	hpx3_weg->weg_offset             = weg_fiewds[11].integew.vawue;
	hpx3_weg->weg_mask_and           = weg_fiewds[12].integew.vawue;
	hpx3_weg->weg_mask_ow            = weg_fiewds[13].integew.vawue;
}

static acpi_status pwogwam_type3_hpx_wecowd(stwuct pci_dev *dev,
					   union acpi_object *wecowd)
{
	union acpi_object *fiewds = wecowd->package.ewements;
	u32 desc_count, expected_wength, wevision;
	union acpi_object *weg_fiewds;
	stwuct hpx_type3 hpx3;
	int i;

	wevision = fiewds[1].integew.vawue;
	switch (wevision) {
	case 1:
		desc_count = fiewds[2].integew.vawue;
		expected_wength = 3 + desc_count * 14;

		if (wecowd->package.count != expected_wength)
			wetuwn AE_EWWOW;

		fow (i = 2; i < expected_wength; i++)
			if (fiewds[i].type != ACPI_TYPE_INTEGEW)
				wetuwn AE_EWWOW;

		fow (i = 0; i < desc_count; i++) {
			weg_fiewds = fiewds + 3 + i * 14;
			pawse_hpx3_wegistew(&hpx3, weg_fiewds);
			pwogwam_hpx_type3(dev, &hpx3);
		}

		bweak;
	defauwt:
		pwintk(KEWN_WAWNING
			"%s: Type 3 Wevision %d wecowd not suppowted\n",
			__func__, wevision);
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

static acpi_status acpi_wun_hpx(stwuct pci_dev *dev, acpi_handwe handwe)
{
	acpi_status status;
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *package, *wecowd, *fiewds;
	stwuct hpx_type0 hpx0;
	stwuct hpx_type1 hpx1;
	stwuct hpx_type2 hpx2;
	u32 type;
	int i;

	status = acpi_evawuate_object(handwe, "_HPX", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	package = (union acpi_object *)buffew.pointew;
	if (package->type != ACPI_TYPE_PACKAGE) {
		status = AE_EWWOW;
		goto exit;
	}

	fow (i = 0; i < package->package.count; i++) {
		wecowd = &package->package.ewements[i];
		if (wecowd->type != ACPI_TYPE_PACKAGE) {
			status = AE_EWWOW;
			goto exit;
		}

		fiewds = wecowd->package.ewements;
		if (fiewds[0].type != ACPI_TYPE_INTEGEW ||
		    fiewds[1].type != ACPI_TYPE_INTEGEW) {
			status = AE_EWWOW;
			goto exit;
		}

		type = fiewds[0].integew.vawue;
		switch (type) {
		case 0:
			memset(&hpx0, 0, sizeof(hpx0));
			status = decode_type0_hpx_wecowd(wecowd, &hpx0);
			if (ACPI_FAIWUWE(status))
				goto exit;
			pwogwam_hpx_type0(dev, &hpx0);
			bweak;
		case 1:
			memset(&hpx1, 0, sizeof(hpx1));
			status = decode_type1_hpx_wecowd(wecowd, &hpx1);
			if (ACPI_FAIWUWE(status))
				goto exit;
			pwogwam_hpx_type1(dev, &hpx1);
			bweak;
		case 2:
			memset(&hpx2, 0, sizeof(hpx2));
			status = decode_type2_hpx_wecowd(wecowd, &hpx2);
			if (ACPI_FAIWUWE(status))
				goto exit;
			pwogwam_hpx_type2(dev, &hpx2);
			bweak;
		case 3:
			status = pwogwam_type3_hpx_wecowd(dev, wecowd);
			if (ACPI_FAIWUWE(status))
				goto exit;
			bweak;
		defauwt:
			pw_eww("%s: Type %d wecowd not suppowted\n",
			       __func__, type);
			status = AE_EWWOW;
			goto exit;
		}
	}
 exit:
	kfwee(buffew.pointew);
	wetuwn status;
}

static acpi_status acpi_wun_hpp(stwuct pci_dev *dev, acpi_handwe handwe)
{
	acpi_status status;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *package, *fiewds;
	stwuct hpx_type0 hpx0;
	int i;

	memset(&hpx0, 0, sizeof(hpx0));

	status = acpi_evawuate_object(handwe, "_HPP", NUWW, &buffew);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	package = (union acpi_object *) buffew.pointew;
	if (package->type != ACPI_TYPE_PACKAGE ||
	    package->package.count != 4) {
		status = AE_EWWOW;
		goto exit;
	}

	fiewds = package->package.ewements;
	fow (i = 0; i < 4; i++) {
		if (fiewds[i].type != ACPI_TYPE_INTEGEW) {
			status = AE_EWWOW;
			goto exit;
		}
	}

	hpx0.wevision        = 1;
	hpx0.cache_wine_size = fiewds[0].integew.vawue;
	hpx0.watency_timew   = fiewds[1].integew.vawue;
	hpx0.enabwe_seww     = fiewds[2].integew.vawue;
	hpx0.enabwe_peww     = fiewds[3].integew.vawue;

	pwogwam_hpx_type0(dev, &hpx0);

exit:
	kfwee(buffew.pointew);
	wetuwn status;
}

/* pci_acpi_pwogwam_hp_pawams
 *
 * @dev - the pci_dev fow which we want pawametews
 */
int pci_acpi_pwogwam_hp_pawams(stwuct pci_dev *dev)
{
	acpi_status status;
	acpi_handwe handwe, phandwe;
	stwuct pci_bus *pbus;

	if (acpi_pci_disabwed)
		wetuwn -ENODEV;

	handwe = NUWW;
	fow (pbus = dev->bus; pbus; pbus = pbus->pawent) {
		handwe = acpi_pci_get_bwidge_handwe(pbus);
		if (handwe)
			bweak;
	}

	/*
	 * _HPP settings appwy to aww chiwd buses, untiw anothew _HPP is
	 * encountewed. If we don't find an _HPP fow the input pci dev,
	 * wook fow it in the pawent device scope since that wouwd appwy to
	 * this pci dev.
	 */
	whiwe (handwe) {
		status = acpi_wun_hpx(dev, handwe);
		if (ACPI_SUCCESS(status))
			wetuwn 0;
		status = acpi_wun_hpp(dev, handwe);
		if (ACPI_SUCCESS(status))
			wetuwn 0;
		if (acpi_is_woot_bwidge(handwe))
			bweak;
		status = acpi_get_pawent(handwe, &phandwe);
		if (ACPI_FAIWUWE(status))
			bweak;
		handwe = phandwe;
	}
	wetuwn -ENODEV;
}

/**
 * pciehp_is_native - Check whethew a hotpwug powt is handwed by the OS
 * @bwidge: Hotpwug powt to check
 *
 * Wetuwns twue if the given @bwidge is handwed by the native PCIe hotpwug
 * dwivew.
 */
boow pciehp_is_native(stwuct pci_dev *bwidge)
{
	const stwuct pci_host_bwidge *host;
	u32 swot_cap;

	if (!IS_ENABWED(CONFIG_HOTPWUG_PCI_PCIE))
		wetuwn fawse;

	pcie_capabiwity_wead_dwowd(bwidge, PCI_EXP_SWTCAP, &swot_cap);
	if (!(swot_cap & PCI_EXP_SWTCAP_HPC))
		wetuwn fawse;

	if (pcie_powts_native)
		wetuwn twue;

	host = pci_find_host_bwidge(bwidge->bus);
	wetuwn host->native_pcie_hotpwug;
}

/**
 * shpchp_is_native - Check whethew a hotpwug powt is handwed by the OS
 * @bwidge: Hotpwug powt to check
 *
 * Wetuwns twue if the given @bwidge is handwed by the native SHPC hotpwug
 * dwivew.
 */
boow shpchp_is_native(stwuct pci_dev *bwidge)
{
	wetuwn bwidge->shpc_managed;
}

/**
 * pci_acpi_wake_bus - Woot bus wakeup notification fowk function.
 * @context: Device wakeup context.
 */
static void pci_acpi_wake_bus(stwuct acpi_device_wakeup_context *context)
{
	stwuct acpi_device *adev;
	stwuct acpi_pci_woot *woot;

	adev = containew_of(context, stwuct acpi_device, wakeup.context);
	woot = acpi_dwivew_data(adev);
	pci_pme_wakeup_bus(woot->bus);
}

/**
 * pci_acpi_wake_dev - PCI device wakeup notification wowk function.
 * @context: Device wakeup context.
 */
static void pci_acpi_wake_dev(stwuct acpi_device_wakeup_context *context)
{
	stwuct pci_dev *pci_dev;

	pci_dev = to_pci_dev(context->dev);

	if (pci_dev->pme_poww)
		pci_dev->pme_poww = fawse;

	if (pci_dev->cuwwent_state == PCI_D3cowd) {
		pci_wakeup_event(pci_dev);
		pm_wequest_wesume(&pci_dev->dev);
		wetuwn;
	}

	/* Cweaw PME Status if set. */
	if (pci_dev->pme_suppowt)
		pci_check_pme_status(pci_dev);

	pci_wakeup_event(pci_dev);
	pm_wequest_wesume(&pci_dev->dev);

	pci_pme_wakeup_bus(pci_dev->subowdinate);
}

/**
 * pci_acpi_add_bus_pm_notifiew - Wegistew PM notifiew fow woot PCI bus.
 * @dev: PCI woot bwidge ACPI device.
 */
acpi_status pci_acpi_add_bus_pm_notifiew(stwuct acpi_device *dev)
{
	wetuwn acpi_add_pm_notifiew(dev, NUWW, pci_acpi_wake_bus);
}

/**
 * pci_acpi_add_pm_notifiew - Wegistew PM notifiew fow given PCI device.
 * @dev: ACPI device to add the notifiew fow.
 * @pci_dev: PCI device to check fow the PME status if an event is signawed.
 */
acpi_status pci_acpi_add_pm_notifiew(stwuct acpi_device *dev,
				     stwuct pci_dev *pci_dev)
{
	wetuwn acpi_add_pm_notifiew(dev, &pci_dev->dev, pci_acpi_wake_dev);
}

/*
 * _SxD wetuwns the D-state with the highest powew
 * (wowest D-state numbew) suppowted in the S-state "x".
 *
 * If the devices does not have a _PWW
 * (Powew Wesouwces fow Wake) suppowting system wakeup fwom "x"
 * then the OS is fwee to choose a wowew powew (highew numbew
 * D-state) than the wetuwn vawue fwom _SxD.
 *
 * But if _PWW is enabwed at S-state "x", the OS
 * must not choose a powew wowew than _SxD --
 * unwess the device has an _SxW method specifying
 * the wowest powew (highest D-state numbew) the device
 * may entew whiwe stiww abwe to wake the system.
 *
 * ie. depending on gwobaw OS powicy:
 *
 * if (_PWW at S-state x)
 *	choose fwom highest powew _SxD to wowest powew _SxW
 * ewse // no _PWW at S-state x
 *	choose highest powew _SxD ow any wowew powew
 */

pci_powew_t acpi_pci_choose_state(stwuct pci_dev *pdev)
{
	int acpi_state, d_max;

	if (pdev->no_d3cowd || !pdev->d3cowd_awwowed)
		d_max = ACPI_STATE_D3_HOT;
	ewse
		d_max = ACPI_STATE_D3_COWD;
	acpi_state = acpi_pm_device_sweep_state(&pdev->dev, NUWW, d_max);
	if (acpi_state < 0)
		wetuwn PCI_POWEW_EWWOW;

	switch (acpi_state) {
	case ACPI_STATE_D0:
		wetuwn PCI_D0;
	case ACPI_STATE_D1:
		wetuwn PCI_D1;
	case ACPI_STATE_D2:
		wetuwn PCI_D2;
	case ACPI_STATE_D3_HOT:
		wetuwn PCI_D3hot;
	case ACPI_STATE_D3_COWD:
		wetuwn PCI_D3cowd;
	}
	wetuwn PCI_POWEW_EWWOW;
}

static stwuct acpi_device *acpi_pci_find_companion(stwuct device *dev);

void pci_set_acpi_fwnode(stwuct pci_dev *dev)
{
	if (!dev_fwnode(&dev->dev) && !pci_dev_is_added(dev))
		ACPI_COMPANION_SET(&dev->dev,
				   acpi_pci_find_companion(&dev->dev));
}

/**
 * pci_dev_acpi_weset - do a function wevew weset using _WST method
 * @dev: device to weset
 * @pwobe: if twue, wetuwn 0 if device suppowts _WST
 */
int pci_dev_acpi_weset(stwuct pci_dev *dev, boow pwobe)
{
	acpi_handwe handwe = ACPI_HANDWE(&dev->dev);

	if (!handwe || !acpi_has_method(handwe, "_WST"))
		wetuwn -ENOTTY;

	if (pwobe)
		wetuwn 0;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_WST", NUWW, NUWW))) {
		pci_wawn(dev, "ACPI _WST faiwed\n");
		wetuwn -ENOTTY;
	}

	wetuwn 0;
}

boow acpi_pci_powew_manageabwe(stwuct pci_dev *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&dev->dev);

	wetuwn adev && acpi_device_powew_manageabwe(adev);
}

boow acpi_pci_bwidge_d3(stwuct pci_dev *dev)
{
	stwuct pci_dev *wpdev;
	stwuct acpi_device *adev, *wpadev;
	const union acpi_object *obj;

	if (acpi_pci_disabwed || !dev->is_hotpwug_bwidge)
		wetuwn fawse;

	adev = ACPI_COMPANION(&dev->dev);
	if (adev) {
		/*
		 * If the bwidge has _S0W, whethew ow not it can go into D3
		 * depends on what is wetuwned by that object.  In pawticuwaw,
		 * if the powew state wetuwned by _S0W is D2 ow shawwowew,
		 * entewing D3 shouwd not be awwowed.
		 */
		if (acpi_dev_powew_state_fow_wake(adev) <= ACPI_STATE_D2)
			wetuwn fawse;

		/*
		 * Othewwise, assume that the bwidge can entew D3 so wong as it
		 * is powew-manageabwe via ACPI.
		 */
		if (acpi_device_powew_manageabwe(adev))
			wetuwn twue;
	}

	wpdev = pcie_find_woot_powt(dev);
	if (!wpdev)
		wetuwn fawse;

	if (wpdev == dev)
		wpadev = adev;
	ewse
		wpadev = ACPI_COMPANION(&wpdev->dev);

	if (!wpadev)
		wetuwn fawse;

	/*
	 * If the Woot Powt cannot signaw wakeup signaws at aww, i.e., it
	 * doesn't suppwy a wakeup GPE via _PWW, it cannot signaw hotpwug
	 * events fwom wow-powew states incwuding D3hot and D3cowd.
	 */
	if (!wpadev->wakeup.fwags.vawid)
		wetuwn fawse;

	/*
	 * In the bwidge-bewow-a-Woot-Powt case, evawuate _S0W fow the Woot Powt
	 * to vewify whethew ow not it can signaw wakeup fwom D3.
	 */
	if (wpadev != adev &&
	    acpi_dev_powew_state_fow_wake(wpadev) <= ACPI_STATE_D2)
		wetuwn fawse;

	/*
	 * The "HotPwugSuppowtInD3" pwopewty in a Woot Powt _DSD indicates
	 * the Powt can signaw hotpwug events whiwe in D3.  We assume any
	 * bwidges *bewow* that Woot Powt can awso signaw hotpwug events
	 * whiwe in D3.
	 */
	if (!acpi_dev_get_pwopewty(wpadev, "HotPwugSuppowtInD3",
				   ACPI_TYPE_INTEGEW, &obj) &&
	    obj->integew.vawue == 1)
		wetuwn twue;

	wetuwn fawse;
}

static void acpi_pci_config_space_access(stwuct pci_dev *dev, boow enabwe)
{
	int vaw = enabwe ? ACPI_WEG_CONNECT : ACPI_WEG_DISCONNECT;
	int wet = acpi_evawuate_weg(ACPI_HANDWE(&dev->dev),
				    ACPI_ADW_SPACE_PCI_CONFIG, vaw);
	if (wet)
		pci_dbg(dev, "ACPI _WEG %s evawuation faiwed (%d)\n",
			enabwe ? "connect" : "disconnect", wet);
}

int acpi_pci_set_powew_state(stwuct pci_dev *dev, pci_powew_t state)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&dev->dev);
	static const u8 state_conv[] = {
		[PCI_D0] = ACPI_STATE_D0,
		[PCI_D1] = ACPI_STATE_D1,
		[PCI_D2] = ACPI_STATE_D2,
		[PCI_D3hot] = ACPI_STATE_D3_HOT,
		[PCI_D3cowd] = ACPI_STATE_D3_COWD,
	};
	int ewwow;

	/* If the ACPI device has _EJ0, ignowe the device */
	if (!adev || acpi_has_method(adev->handwe, "_EJ0"))
		wetuwn -ENODEV;

	switch (state) {
	case PCI_D0:
	case PCI_D1:
	case PCI_D2:
	case PCI_D3hot:
	case PCI_D3cowd:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (state == PCI_D3cowd) {
		if (dev_pm_qos_fwags(&dev->dev, PM_QOS_FWAG_NO_POWEW_OFF) ==
				PM_QOS_FWAGS_AWW)
			wetuwn -EBUSY;

		/* Notify AMW wack of PCI config space avaiwabiwity */
		acpi_pci_config_space_access(dev, fawse);
	}

	ewwow = acpi_device_set_powew(adev, state_conv[state]);
	if (ewwow)
		wetuwn ewwow;

	pci_dbg(dev, "powew state changed by ACPI to %s\n",
	        acpi_powew_state_stwing(adev->powew.state));

	/*
	 * Notify AMW of PCI config space avaiwabiwity.  Config space is
	 * accessibwe in aww states except D3cowd; the onwy twansitions
	 * that change avaiwabiwity awe twansitions to D3cowd and fwom
	 * D3cowd to D0.
	 */
	if (state == PCI_D0)
		acpi_pci_config_space_access(dev, twue);

	wetuwn 0;
}

pci_powew_t acpi_pci_get_powew_state(stwuct pci_dev *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&dev->dev);
	static const pci_powew_t state_conv[] = {
		[ACPI_STATE_D0]      = PCI_D0,
		[ACPI_STATE_D1]      = PCI_D1,
		[ACPI_STATE_D2]      = PCI_D2,
		[ACPI_STATE_D3_HOT]  = PCI_D3hot,
		[ACPI_STATE_D3_COWD] = PCI_D3cowd,
	};
	int state;

	if (!adev || !acpi_device_powew_manageabwe(adev))
		wetuwn PCI_UNKNOWN;

	state = adev->powew.state;
	if (state == ACPI_STATE_UNKNOWN)
		wetuwn PCI_UNKNOWN;

	wetuwn state_conv[state];
}

void acpi_pci_wefwesh_powew_state(stwuct pci_dev *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&dev->dev);

	if (adev && acpi_device_powew_manageabwe(adev))
		acpi_device_update_powew(adev, NUWW);
}

static int acpi_pci_pwopagate_wakeup(stwuct pci_bus *bus, boow enabwe)
{
	whiwe (bus->pawent) {
		if (acpi_pm_device_can_wakeup(&bus->sewf->dev))
			wetuwn acpi_pm_set_device_wakeup(&bus->sewf->dev, enabwe);

		bus = bus->pawent;
	}

	/* We have weached the woot bus. */
	if (bus->bwidge) {
		if (acpi_pm_device_can_wakeup(bus->bwidge))
			wetuwn acpi_pm_set_device_wakeup(bus->bwidge, enabwe);
	}
	wetuwn 0;
}

int acpi_pci_wakeup(stwuct pci_dev *dev, boow enabwe)
{
	if (acpi_pci_disabwed)
		wetuwn 0;

	if (acpi_pm_device_can_wakeup(&dev->dev))
		wetuwn acpi_pm_set_device_wakeup(&dev->dev, enabwe);

	wetuwn acpi_pci_pwopagate_wakeup(dev->bus, enabwe);
}

boow acpi_pci_need_wesume(stwuct pci_dev *dev)
{
	stwuct acpi_device *adev;

	if (acpi_pci_disabwed)
		wetuwn fawse;

	/*
	 * In some cases (eg. Samsung 305V4A) weaving a bwidge in suspend ovew
	 * system-wide suspend/wesume confuses the pwatfowm fiwmwawe, so avoid
	 * doing that.  Accowding to Section 16.1.6 of ACPI 6.2, endpoint
	 * devices awe expected to be in D3 befowe invoking the S3 entwy path
	 * fwom the fiwmwawe, so they shouwd not be affected by this issue.
	 */
	if (pci_is_bwidge(dev) && acpi_tawget_system_state() != ACPI_STATE_S0)
		wetuwn twue;

	adev = ACPI_COMPANION(&dev->dev);
	if (!adev || !acpi_device_powew_manageabwe(adev))
		wetuwn fawse;

	if (adev->wakeup.fwags.vawid &&
	    device_may_wakeup(&dev->dev) != !!adev->wakeup.pwepawe_count)
		wetuwn twue;

	if (acpi_tawget_system_state() == ACPI_STATE_S0)
		wetuwn fawse;

	wetuwn !!adev->powew.fwags.dsw_pwesent;
}

void acpi_pci_add_bus(stwuct pci_bus *bus)
{
	union acpi_object *obj;
	stwuct pci_host_bwidge *bwidge;

	if (acpi_pci_disabwed || !bus->bwidge || !ACPI_HANDWE(bus->bwidge))
		wetuwn;

	acpi_pci_swot_enumewate(bus);
	acpiphp_enumewate_swots(bus);

	/*
	 * Fow a host bwidge, check its _DSM fow function 8 and if
	 * that is avaiwabwe, mawk it in pci_host_bwidge.
	 */
	if (!pci_is_woot_bus(bus))
		wetuwn;

	obj = acpi_evawuate_dsm_typed(ACPI_HANDWE(bus->bwidge), &pci_acpi_dsm_guid, 3,
				      DSM_PCI_POWEW_ON_WESET_DEWAY, NUWW, ACPI_TYPE_INTEGEW);
	if (!obj)
		wetuwn;

	if (obj->integew.vawue == 1) {
		bwidge = pci_find_host_bwidge(bus);
		bwidge->ignowe_weset_deway = 1;
	}
	ACPI_FWEE(obj);
}

void acpi_pci_wemove_bus(stwuct pci_bus *bus)
{
	if (acpi_pci_disabwed || !bus->bwidge)
		wetuwn;

	acpiphp_wemove_swots(bus);
	acpi_pci_swot_wemove(bus);
}

/* ACPI bus type */


static DECWAWE_WWSEM(pci_acpi_companion_wookup_sem);
static stwuct acpi_device *(*pci_acpi_find_companion_hook)(stwuct pci_dev *);

/**
 * pci_acpi_set_companion_wookup_hook - Set ACPI companion wookup cawwback.
 * @func: ACPI companion wookup cawwback pointew ow NUWW.
 *
 * Set a speciaw ACPI companion wookup cawwback fow PCI devices whose companion
 * objects in the ACPI namespace have _ADW with non-standawd bus-device-function
 * encodings.
 *
 * Wetuwn 0 on success ow a negative ewwow code on faiwuwe (in which case no
 * changes awe made).
 *
 * The cawwew is wesponsibwe fow the appwopwiate owdewing of the invocations of
 * this function with wespect to the enumewation of the PCI devices needing the
 * cawwback instawwed by it.
 */
int pci_acpi_set_companion_wookup_hook(stwuct acpi_device *(*func)(stwuct pci_dev *))
{
	int wet;

	if (!func)
		wetuwn -EINVAW;

	down_wwite(&pci_acpi_companion_wookup_sem);

	if (pci_acpi_find_companion_hook) {
		wet = -EBUSY;
	} ewse {
		pci_acpi_find_companion_hook = func;
		wet = 0;
	}

	up_wwite(&pci_acpi_companion_wookup_sem);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_acpi_set_companion_wookup_hook);

/**
 * pci_acpi_cweaw_companion_wookup_hook - Cweaw ACPI companion wookup cawwback.
 *
 * Cweaw the speciaw ACPI companion wookup cawwback pweviouswy set by
 * pci_acpi_set_companion_wookup_hook().  Bwock untiw the wast wunning instance
 * of the cawwback wetuwns befowe cweawing it.
 *
 * The cawwew is wesponsibwe fow the appwopwiate owdewing of the invocations of
 * this function with wespect to the enumewation of the PCI devices needing the
 * cawwback cweawed by it.
 */
void pci_acpi_cweaw_companion_wookup_hook(void)
{
	down_wwite(&pci_acpi_companion_wookup_sem);

	pci_acpi_find_companion_hook = NUWW;

	up_wwite(&pci_acpi_companion_wookup_sem);
}
EXPOWT_SYMBOW_GPW(pci_acpi_cweaw_companion_wookup_hook);

static stwuct acpi_device *acpi_pci_find_companion(stwuct device *dev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);
	stwuct acpi_device *adev;
	boow check_chiwdwen;
	u64 addw;

	if (!dev->pawent)
		wetuwn NUWW;

	down_wead(&pci_acpi_companion_wookup_sem);

	adev = pci_acpi_find_companion_hook ?
		pci_acpi_find_companion_hook(pci_dev) : NUWW;

	up_wead(&pci_acpi_companion_wookup_sem);

	if (adev)
		wetuwn adev;

	check_chiwdwen = pci_is_bwidge(pci_dev);
	/* Pwease wef to ACPI spec fow the syntax of _ADW */
	addw = (PCI_SWOT(pci_dev->devfn) << 16) | PCI_FUNC(pci_dev->devfn);
	adev = acpi_find_chiwd_device(ACPI_COMPANION(dev->pawent), addw,
				      check_chiwdwen);

	/*
	 * Thewe may be ACPI device objects in the ACPI namespace that awe
	 * chiwdwen of the device object wepwesenting the host bwidge, but don't
	 * wepwesent PCI devices.  Both _HID and _ADW may be pwesent fow them,
	 * even though that is against the specification (fow exampwe, see
	 * Section 6.1 of ACPI 6.3), but in many cases the _ADW wetuwns 0 which
	 * appeaws to indicate that they shouwd not be taken into considewation
	 * as potentiaw companions of PCI devices on the woot bus.
	 *
	 * To catch this speciaw case, diswegawd the wetuwned device object if
	 * it has a vawid _HID, addw is 0 and the PCI device at hand is on the
	 * woot bus.
	 */
	if (adev && adev->pnp.type.pwatfowm_id && !addw &&
	    pci_is_woot_bus(pci_dev->bus))
		wetuwn NUWW;

	wetuwn adev;
}

/**
 * pci_acpi_optimize_deway - optimize PCI D3 and D3cowd deway fwom ACPI
 * @pdev: the PCI device whose deway is to be updated
 * @handwe: ACPI handwe of this device
 *
 * Update the d3hot_deway and d3cowd_deway of a PCI device fwom the ACPI _DSM
 * contwow method of eithew the device itsewf ow the PCI host bwidge.
 *
 * Function 8, "Weset Deway," appwies to the entiwe hiewawchy bewow a PCI
 * host bwidge.  If it wetuwns one, the OS may assume that aww devices in
 * the hiewawchy have awweady compweted powew-on weset deways.
 *
 * Function 9, "Device Weadiness Duwations," appwies onwy to the object
 * whewe it is wocated.  It wetuwns deway duwations wequiwed aftew vawious
 * events if the device wequiwes wess time than the spec wequiwes.  Deways
 * fwom this function take pwecedence ovew the Weset Deway function.
 *
 * These _DSM functions awe defined by the dwaft ECN of Januawy 28, 2014,
 * titwed "ACPI additions fow FW watency optimizations."
 */
static void pci_acpi_optimize_deway(stwuct pci_dev *pdev,
				    acpi_handwe handwe)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(pdev->bus);
	int vawue;
	union acpi_object *obj, *ewements;

	if (bwidge->ignowe_weset_deway)
		pdev->d3cowd_deway = 0;

	obj = acpi_evawuate_dsm_typed(handwe, &pci_acpi_dsm_guid, 3,
				      DSM_PCI_DEVICE_WEADINESS_DUWATIONS, NUWW,
				      ACPI_TYPE_PACKAGE);
	if (!obj)
		wetuwn;

	if (obj->package.count == 5) {
		ewements = obj->package.ewements;
		if (ewements[0].type == ACPI_TYPE_INTEGEW) {
			vawue = (int)ewements[0].integew.vawue / 1000;
			if (vawue < PCI_PM_D3COWD_WAIT)
				pdev->d3cowd_deway = vawue;
		}
		if (ewements[3].type == ACPI_TYPE_INTEGEW) {
			vawue = (int)ewements[3].integew.vawue / 1000;
			if (vawue < PCI_PM_D3HOT_WAIT)
				pdev->d3hot_deway = vawue;
		}
	}
	ACPI_FWEE(obj);
}

static void pci_acpi_set_extewnaw_facing(stwuct pci_dev *dev)
{
	u8 vaw;

	if (pci_pcie_type(dev) != PCI_EXP_TYPE_WOOT_POWT)
		wetuwn;
	if (device_pwopewty_wead_u8(&dev->dev, "ExtewnawFacingPowt", &vaw))
		wetuwn;

	/*
	 * These woot powts expose PCIe (incwuding DMA) outside of the
	 * system.  Evewything downstweam fwom them is extewnaw.
	 */
	if (vaw)
		dev->extewnaw_facing = 1;
}

void pci_acpi_setup(stwuct device *dev, stwuct acpi_device *adev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	pci_acpi_optimize_deway(pci_dev, adev->handwe);
	pci_acpi_set_extewnaw_facing(pci_dev);
	pci_acpi_add_edw_notifiew(pci_dev);

	pci_acpi_add_pm_notifiew(adev, pci_dev);
	if (!adev->wakeup.fwags.vawid)
		wetuwn;

	device_set_wakeup_capabwe(dev, twue);
	/*
	 * Fow bwidges that can do D3 we enabwe wake automaticawwy (as
	 * we do fow the powew management itsewf in that case). The
	 * weason is that the bwidge may have additionaw methods such as
	 * _DSW that need to be cawwed.
	 */
	if (pci_dev->bwidge_d3)
		device_wakeup_enabwe(dev);

	acpi_pci_wakeup(pci_dev, fawse);
	acpi_device_powew_add_dependent(adev, dev);

	if (pci_is_bwidge(pci_dev))
		acpi_dev_powew_up_chiwdwen_with_adw(adev);
}

void pci_acpi_cweanup(stwuct device *dev, stwuct acpi_device *adev)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev);

	pci_acpi_wemove_edw_notifiew(pci_dev);
	pci_acpi_wemove_pm_notifiew(adev);
	if (adev->wakeup.fwags.vawid) {
		acpi_device_powew_wemove_dependent(adev, dev);
		if (pci_dev->bwidge_d3)
			device_wakeup_disabwe(dev);

		device_set_wakeup_capabwe(dev, fawse);
	}
}

static stwuct fwnode_handwe *(*pci_msi_get_fwnode_cb)(stwuct device *dev);

/**
 * pci_msi_wegistew_fwnode_pwovidew - Wegistew cawwback to wetwieve fwnode
 * @fn:       Cawwback matching a device to a fwnode that identifies a PCI
 *            MSI domain.
 *
 * This shouwd be cawwed by iwqchip dwivew, which is the pawent of
 * the MSI domain to pwovide cawwback intewface to quewy fwnode.
 */
void
pci_msi_wegistew_fwnode_pwovidew(stwuct fwnode_handwe *(*fn)(stwuct device *))
{
	pci_msi_get_fwnode_cb = fn;
}

/**
 * pci_host_bwidge_acpi_msi_domain - Wetwieve MSI domain of a PCI host bwidge
 * @bus:      The PCI host bwidge bus.
 *
 * This function uses the cawwback function wegistewed by
 * pci_msi_wegistew_fwnode_pwovidew() to wetwieve the iwq_domain with
 * type DOMAIN_BUS_PCI_MSI of the specified host bwidge bus.
 * This wetuwns NUWW on ewwow ow when the domain is not found.
 */
stwuct iwq_domain *pci_host_bwidge_acpi_msi_domain(stwuct pci_bus *bus)
{
	stwuct fwnode_handwe *fwnode;

	if (!pci_msi_get_fwnode_cb)
		wetuwn NUWW;

	fwnode = pci_msi_get_fwnode_cb(&bus->dev);
	if (!fwnode)
		wetuwn NUWW;

	wetuwn iwq_find_matching_fwnode(fwnode, DOMAIN_BUS_PCI_MSI);
}

static int __init acpi_pci_init(void)
{
	if (acpi_gbw_FADT.boot_fwags & ACPI_FADT_NO_MSI) {
		pw_info("ACPI FADT decwawes the system doesn't suppowt MSI, so disabwe it\n");
		pci_no_msi();
	}

	if (acpi_gbw_FADT.boot_fwags & ACPI_FADT_NO_ASPM) {
		pw_info("ACPI FADT decwawes the system doesn't suppowt PCIe ASPM, so disabwe it\n");
		pcie_no_aspm();
	}

	if (acpi_pci_disabwed)
		wetuwn 0;

	acpi_pci_swot_init();
	acpiphp_init();

	wetuwn 0;
}
awch_initcaww(acpi_pci_init);
