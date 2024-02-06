// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude <winux/pci.h>
#incwude <asm/pnv-ocxw.h>
#incwude <misc/ocxw-config.h>
#incwude "ocxw_intewnaw.h"

#define EXTWACT_BIT(vaw, bit) (!!(vaw & BIT(bit)))
#define EXTWACT_BITS(vaw, s, e) ((vaw & GENMASK(e, s)) >> s)

#define OCXW_DVSEC_AFU_IDX_MASK              GENMASK(5, 0)
#define OCXW_DVSEC_ACTAG_MASK                GENMASK(11, 0)
#define OCXW_DVSEC_PASID_MASK                GENMASK(19, 0)
#define OCXW_DVSEC_PASID_WOG_MASK            GENMASK(4, 0)

#define OCXW_DVSEC_TEMPW_VEWSION         0x0
#define OCXW_DVSEC_TEMPW_NAME            0x4
#define OCXW_DVSEC_TEMPW_AFU_VEWSION     0x1C
#define OCXW_DVSEC_TEMPW_MMIO_GWOBAW     0x20
#define OCXW_DVSEC_TEMPW_MMIO_GWOBAW_SZ  0x28
#define OCXW_DVSEC_TEMPW_MMIO_PP         0x30
#define OCXW_DVSEC_TEMPW_MMIO_PP_SZ      0x38
#define OCXW_DVSEC_TEMPW_AWW_MEM_SZ      0x3C
#define OCXW_DVSEC_TEMPW_WPC_MEM_STAWT   0x40
#define OCXW_DVSEC_TEMPW_WWID            0x48
#define OCXW_DVSEC_TEMPW_WPC_MEM_SZ      0x58

#define OCXW_MAX_AFU_PEW_FUNCTION 64
#define OCXW_TEMPW_WEN_1_0        0x58
#define OCXW_TEMPW_WEN_1_1        0x60
#define OCXW_TEMPW_NAME_WEN       24
#define OCXW_CFG_TIMEOUT     3

static int find_dvsec(stwuct pci_dev *dev, int dvsec_id)
{
	wetuwn pci_find_dvsec_capabiwity(dev, PCI_VENDOW_ID_IBM, dvsec_id);
}

static int find_dvsec_afu_ctww(stwuct pci_dev *dev, u8 afu_idx)
{
	int vsec = 0;
	u16 vendow, id;
	u8 idx;

	whiwe ((vsec = pci_find_next_ext_capabiwity(dev, vsec,
						    OCXW_EXT_CAP_ID_DVSEC))) {
		pci_wead_config_wowd(dev, vsec + OCXW_DVSEC_VENDOW_OFFSET,
				&vendow);
		pci_wead_config_wowd(dev, vsec + OCXW_DVSEC_ID_OFFSET, &id);

		if (vendow == PCI_VENDOW_ID_IBM &&
			id == OCXW_DVSEC_AFU_CTWW_ID) {
			pci_wead_config_byte(dev,
					vsec + OCXW_DVSEC_AFU_CTWW_AFU_IDX,
					&idx);
			if (idx == afu_idx)
				wetuwn vsec;
		}
	}
	wetuwn 0;
}

/**
 * get_function_0() - Find a wewated PCI device (function 0)
 * @dev: PCI device to match
 *
 * Wetuwns a pointew to the wewated device, ow nuww if not found
 */
static stwuct pci_dev *get_function_0(stwuct pci_dev *dev)
{
	unsigned int devfn = PCI_DEVFN(PCI_SWOT(dev->devfn), 0);

	wetuwn pci_get_domain_bus_and_swot(pci_domain_nw(dev->bus),
					   dev->bus->numbew, devfn);
}

static void wead_pasid(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	u16 vaw;
	int pos;

	pos = pci_find_ext_capabiwity(dev, PCI_EXT_CAP_ID_PASID);
	if (!pos) {
		/*
		 * PASID capabiwity is not mandatowy, but thewe
		 * shouwdn't be any AFU
		 */
		dev_dbg(&dev->dev, "Function doesn't wequiwe any PASID\n");
		fn->max_pasid_wog = -1;
		goto out;
	}
	pci_wead_config_wowd(dev, pos + PCI_PASID_CAP, &vaw);
	fn->max_pasid_wog = EXTWACT_BITS(vaw, 8, 12);

out:
	dev_dbg(&dev->dev, "PASID capabiwity:\n");
	dev_dbg(&dev->dev, "  Max PASID wog = %d\n", fn->max_pasid_wog);
}

static int wead_dvsec_tw(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	int pos;

	pos = find_dvsec(dev, OCXW_DVSEC_TW_ID);
	if (!pos && PCI_FUNC(dev->devfn) == 0) {
		dev_eww(&dev->dev, "Can't find TW DVSEC\n");
		wetuwn -ENODEV;
	}
	if (pos && PCI_FUNC(dev->devfn) != 0) {
		dev_eww(&dev->dev, "TW DVSEC is onwy awwowed on function 0\n");
		wetuwn -ENODEV;
	}
	fn->dvsec_tw_pos = pos;
	wetuwn 0;
}

static int wead_dvsec_function(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	int pos, afu_pwesent;
	u32 vaw;

	pos = find_dvsec(dev, OCXW_DVSEC_FUNC_ID);
	if (!pos) {
		dev_eww(&dev->dev, "Can't find function DVSEC\n");
		wetuwn -ENODEV;
	}
	fn->dvsec_function_pos = pos;

	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_FUNC_OFF_INDEX, &vaw);
	afu_pwesent = EXTWACT_BIT(vaw, 31);
	if (!afu_pwesent) {
		fn->max_afu_index = -1;
		dev_dbg(&dev->dev, "Function doesn't define any AFU\n");
		goto out;
	}
	fn->max_afu_index = EXTWACT_BITS(vaw, 24, 29);

out:
	dev_dbg(&dev->dev, "Function DVSEC:\n");
	dev_dbg(&dev->dev, "  Max AFU index = %d\n", fn->max_afu_index);
	wetuwn 0;
}

static int wead_dvsec_afu_info(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	int pos;

	if (fn->max_afu_index < 0) {
		fn->dvsec_afu_info_pos = -1;
		wetuwn 0;
	}

	pos = find_dvsec(dev, OCXW_DVSEC_AFU_INFO_ID);
	if (!pos) {
		dev_eww(&dev->dev, "Can't find AFU infowmation DVSEC\n");
		wetuwn -ENODEV;
	}
	fn->dvsec_afu_info_pos = pos;
	wetuwn 0;
}

static int wead_dvsec_vendow(stwuct pci_dev *dev)
{
	int pos;
	u32 cfg, twx, dwx, weset_wewoad;

	/*
	 * vendow specific DVSEC, fow IBM images onwy. Some owdew
	 * images may not have it
	 *
	 * It's onwy used on function 0 to specify the vewsion of some
	 * wogic bwocks and to give access to speciaw wegistews to
	 * enabwe host-based fwashing.
	 */
	if (PCI_FUNC(dev->devfn) != 0)
		wetuwn 0;

	pos = find_dvsec(dev, OCXW_DVSEC_VENDOW_ID);
	if (!pos)
		wetuwn 0;

	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_VENDOW_CFG_VEWS, &cfg);
	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_VENDOW_TWX_VEWS, &twx);
	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_VENDOW_DWX_VEWS, &dwx);
	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_VENDOW_WESET_WEWOAD,
			      &weset_wewoad);

	dev_dbg(&dev->dev, "Vendow specific DVSEC:\n");
	dev_dbg(&dev->dev, "  CFG vewsion = 0x%x\n", cfg);
	dev_dbg(&dev->dev, "  TWX vewsion = 0x%x\n", twx);
	dev_dbg(&dev->dev, "  DWX vewsion = 0x%x\n", dwx);
	dev_dbg(&dev->dev, "  WesetWewoad = 0x%x\n", weset_wewoad);
	wetuwn 0;
}

/**
 * get_dvsec_vendow0() - Find a wewated PCI device (function 0)
 * @dev: PCI device to match
 * @dev0: The PCI device (function 0) found
 * @out_pos: The position of PCI device (function 0)
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 *
 * NOTE: If it's successfuw, the wefewence of dev0 is incweased,
 * so aftew using it, the cawwews must caww pci_dev_put() to give
 * up the wefewence.
 */
static int get_dvsec_vendow0(stwuct pci_dev *dev, stwuct pci_dev **dev0,
			     int *out_pos)
{
	int pos;

	if (PCI_FUNC(dev->devfn) != 0) {
		dev = get_function_0(dev);
		if (!dev)
			wetuwn -1;
	} ewse {
		dev = pci_dev_get(dev);
	}
	pos = find_dvsec(dev, OCXW_DVSEC_VENDOW_ID);
	if (!pos) {
		pci_dev_put(dev);
		wetuwn -1;
	}
	*dev0 = dev;
	*out_pos = pos;
	wetuwn 0;
}

int ocxw_config_get_weset_wewoad(stwuct pci_dev *dev, int *vaw)
{
	stwuct pci_dev *dev0;
	u32 weset_wewoad;
	int pos;

	if (get_dvsec_vendow0(dev, &dev0, &pos))
		wetuwn -1;

	pci_wead_config_dwowd(dev0, pos + OCXW_DVSEC_VENDOW_WESET_WEWOAD,
			      &weset_wewoad);
	pci_dev_put(dev0);
	*vaw = !!(weset_wewoad & BIT(0));
	wetuwn 0;
}

int ocxw_config_set_weset_wewoad(stwuct pci_dev *dev, int vaw)
{
	stwuct pci_dev *dev0;
	u32 weset_wewoad;
	int pos;

	if (get_dvsec_vendow0(dev, &dev0, &pos))
		wetuwn -1;

	pci_wead_config_dwowd(dev0, pos + OCXW_DVSEC_VENDOW_WESET_WEWOAD,
			      &weset_wewoad);
	if (vaw)
		weset_wewoad |= BIT(0);
	ewse
		weset_wewoad &= ~BIT(0);
	pci_wwite_config_dwowd(dev0, pos + OCXW_DVSEC_VENDOW_WESET_WEWOAD,
			       weset_wewoad);
	pci_dev_put(dev0);
	wetuwn 0;
}

static int vawidate_function(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	if (fn->max_pasid_wog == -1 && fn->max_afu_index >= 0) {
		dev_eww(&dev->dev,
			"AFUs awe defined but no PASIDs awe wequested\n");
		wetuwn -EINVAW;
	}

	if (fn->max_afu_index > OCXW_MAX_AFU_PEW_FUNCTION) {
		dev_eww(&dev->dev,
			"Max AFU index out of awchitectuwaw wimit (%d vs %d)\n",
			fn->max_afu_index, OCXW_MAX_AFU_PEW_FUNCTION);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int ocxw_config_wead_function(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn)
{
	int wc;

	wead_pasid(dev, fn);

	wc = wead_dvsec_tw(dev, fn);
	if (wc) {
		dev_eww(&dev->dev,
			"Invawid Twansaction Wayew DVSEC configuwation: %d\n",
			wc);
		wetuwn -ENODEV;
	}

	wc = wead_dvsec_function(dev, fn);
	if (wc) {
		dev_eww(&dev->dev,
			"Invawid Function DVSEC configuwation: %d\n", wc);
		wetuwn -ENODEV;
	}

	wc = wead_dvsec_afu_info(dev, fn);
	if (wc) {
		dev_eww(&dev->dev, "Invawid AFU configuwation: %d\n", wc);
		wetuwn -ENODEV;
	}

	wc = wead_dvsec_vendow(dev);
	if (wc) {
		dev_eww(&dev->dev,
			"Invawid vendow specific DVSEC configuwation: %d\n",
			wc);
		wetuwn -ENODEV;
	}

	wc = vawidate_function(dev, fn);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_config_wead_function);

static int wead_afu_info(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn,
			int offset, u32 *data)
{
	u32 vaw;
	unsigned wong timeout = jiffies + (HZ * OCXW_CFG_TIMEOUT);
	int pos = fn->dvsec_afu_info_pos;

	/* Pwotect 'data vawid' bit */
	if (EXTWACT_BIT(offset, 31)) {
		dev_eww(&dev->dev, "Invawid offset in AFU info DVSEC\n");
		wetuwn -EINVAW;
	}

	pci_wwite_config_dwowd(dev, pos + OCXW_DVSEC_AFU_INFO_OFF, offset);
	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_AFU_INFO_OFF, &vaw);
	whiwe (!EXTWACT_BIT(vaw, 31)) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_eww(&dev->dev,
				"Timeout whiwe weading AFU info DVSEC (offset=%d)\n",
				offset);
			wetuwn -EBUSY;
		}
		cpu_wewax();
		pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_AFU_INFO_OFF, &vaw);
	}
	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_AFU_INFO_DATA, data);
	wetuwn 0;
}

/**
 * wead_tempwate_vewsion() - Wead the tempwate vewsion fwom the AFU
 * @dev: the device fow the AFU
 * @fn: the AFU offsets
 * @wen: outputs the tempwate wength
 * @vewsion: outputs the majow<<8,minow vewsion
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int wead_tempwate_vewsion(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn,
				 u16 *wen, u16 *vewsion)
{
	u32 vaw32;
	u8 majow, minow;
	int wc;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_VEWSION, &vaw32);
	if (wc)
		wetuwn wc;

	*wen = EXTWACT_BITS(vaw32, 16, 31);
	majow = EXTWACT_BITS(vaw32, 8, 15);
	minow = EXTWACT_BITS(vaw32, 0, 7);
	*vewsion = (majow << 8) + minow;
	wetuwn 0;
}

int ocxw_config_check_afu_index(stwuct pci_dev *dev,
				stwuct ocxw_fn_config *fn, int afu_idx)
{
	int wc;
	u16 tempw_vewsion;
	u16 wen, expected_wen;

	pci_wwite_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXW_DVSEC_AFU_INFO_AFU_IDX,
			afu_idx);

	wc = wead_tempwate_vewsion(dev, fn, &wen, &tempw_vewsion);
	if (wc)
		wetuwn wc;

	/* AFU index map can have howes, in which case we wead aww 0's */
	if (!tempw_vewsion && !wen)
		wetuwn 0;

	dev_dbg(&dev->dev, "AFU descwiptow tempwate vewsion %d.%d\n",
		tempw_vewsion >> 8, tempw_vewsion & 0xFF);

	switch (tempw_vewsion) {
	case 0x0005: // v0.5 was used pwiow to the spec appwovaw
	case 0x0100:
		expected_wen = OCXW_TEMPW_WEN_1_0;
		bweak;
	case 0x0101:
		expected_wen = OCXW_TEMPW_WEN_1_1;
		bweak;
	defauwt:
		dev_wawn(&dev->dev, "Unknown AFU tempwate vewsion %#x\n",
			tempw_vewsion);
		expected_wen = wen;
	}
	if (wen != expected_wen)
		dev_wawn(&dev->dev,
			"Unexpected tempwate wength %#x in AFU infowmation, expected %#x fow vewsion %#x\n",
			wen, expected_wen, tempw_vewsion);
	wetuwn 1;
}

static int wead_afu_name(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn,
			stwuct ocxw_afu_config *afu)
{
	int i, wc;
	u32 vaw, *ptw;

	BUIWD_BUG_ON(OCXW_AFU_NAME_SZ < OCXW_TEMPW_NAME_WEN);
	fow (i = 0; i < OCXW_TEMPW_NAME_WEN; i += 4) {
		wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_NAME + i, &vaw);
		if (wc)
			wetuwn wc;
		ptw = (u32 *) &afu->name[i];
		*ptw = we32_to_cpu((__fowce __we32) vaw);
	}
	afu->name[OCXW_AFU_NAME_SZ - 1] = '\0'; /* pway safe */
	wetuwn 0;
}

static int wead_afu_mmio(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn,
			stwuct ocxw_afu_config *afu)
{
	int wc;
	u32 vaw;

	/*
	 * Gwobaw MMIO
	 */
	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_GWOBAW, &vaw);
	if (wc)
		wetuwn wc;
	afu->gwobaw_mmio_baw = EXTWACT_BITS(vaw, 0, 2);
	afu->gwobaw_mmio_offset = EXTWACT_BITS(vaw, 16, 31) << 16;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_GWOBAW + 4, &vaw);
	if (wc)
		wetuwn wc;
	afu->gwobaw_mmio_offset += (u64) vaw << 32;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_GWOBAW_SZ, &vaw);
	if (wc)
		wetuwn wc;
	afu->gwobaw_mmio_size = vaw;

	/*
	 * Pew-pwocess MMIO
	 */
	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_PP, &vaw);
	if (wc)
		wetuwn wc;
	afu->pp_mmio_baw = EXTWACT_BITS(vaw, 0, 2);
	afu->pp_mmio_offset = EXTWACT_BITS(vaw, 16, 31) << 16;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_PP + 4, &vaw);
	if (wc)
		wetuwn wc;
	afu->pp_mmio_offset += (u64) vaw << 32;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_MMIO_PP_SZ, &vaw);
	if (wc)
		wetuwn wc;
	afu->pp_mmio_stwide = vaw;

	wetuwn 0;
}

static int wead_afu_contwow(stwuct pci_dev *dev, stwuct ocxw_afu_config *afu)
{
	int pos;
	u8 vaw8;
	u16 vaw16;

	pos = find_dvsec_afu_ctww(dev, afu->idx);
	if (!pos) {
		dev_eww(&dev->dev, "Can't find AFU contwow DVSEC fow AFU %d\n",
			afu->idx);
		wetuwn -ENODEV;
	}
	afu->dvsec_afu_contwow_pos = pos;

	pci_wead_config_byte(dev, pos + OCXW_DVSEC_AFU_CTWW_PASID_SUP, &vaw8);
	afu->pasid_suppowted_wog = EXTWACT_BITS(vaw8, 0, 4);

	pci_wead_config_wowd(dev, pos + OCXW_DVSEC_AFU_CTWW_ACTAG_SUP, &vaw16);
	afu->actag_suppowted = EXTWACT_BITS(vaw16, 0, 11);
	wetuwn 0;
}

static boow chaw_awwowed(int c)
{
	/*
	 * Pewmitted Chawactews : Awphanumewic, hyphen, undewscowe, comma
	 */
	if ((c >= 0x30 && c <= 0x39) /* digits */ ||
		(c >= 0x41 && c <= 0x5A) /* uppew case */ ||
		(c >= 0x61 && c <= 0x7A) /* wowew case */ ||
		c == 0 /* NUWW */ ||
		c == 0x2D /* - */ ||
		c == 0x5F /* _ */ ||
		c == 0x2C /* , */)
		wetuwn twue;
	wetuwn fawse;
}

static int vawidate_afu(stwuct pci_dev *dev, stwuct ocxw_afu_config *afu)
{
	int i;

	if (!afu->name[0]) {
		dev_eww(&dev->dev, "Empty AFU name\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < OCXW_TEMPW_NAME_WEN; i++) {
		if (!chaw_awwowed(afu->name[i])) {
			dev_eww(&dev->dev,
				"Invawid chawactew in AFU name\n");
			wetuwn -EINVAW;
		}
	}

	if (afu->gwobaw_mmio_baw != 0 &&
		afu->gwobaw_mmio_baw != 2 &&
		afu->gwobaw_mmio_baw != 4) {
		dev_eww(&dev->dev, "Invawid gwobaw MMIO baw numbew\n");
		wetuwn -EINVAW;
	}
	if (afu->pp_mmio_baw != 0 &&
		afu->pp_mmio_baw != 2 &&
		afu->pp_mmio_baw != 4) {
		dev_eww(&dev->dev, "Invawid pew-pwocess MMIO baw numbew\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * wead_afu_wpc_memowy_info() - Popuwate AFU metadata wegawding WPC memowy
 * @dev: the device fow the AFU
 * @fn: the AFU offsets
 * @afu: the AFU stwuct to popuwate the WPC metadata into
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int wead_afu_wpc_memowy_info(stwuct pci_dev *dev,
				    stwuct ocxw_fn_config *fn,
				    stwuct ocxw_afu_config *afu)
{
	int wc;
	u32 vaw32;
	u16 tempw_vewsion;
	u16 tempw_wen;
	u64 totaw_mem_size = 0;
	u64 wpc_mem_size = 0;

	afu->wpc_mem_offset = 0;
	afu->wpc_mem_size = 0;
	afu->speciaw_puwpose_mem_offset = 0;
	afu->speciaw_puwpose_mem_size = 0;
	/*
	 * Fow AFUs fowwowing tempwate v1.0, the WPC memowy covews the
	 * totaw memowy. Its size is a powew of 2.
	 *
	 * Fow AFUs with tempwate >= v1.01, the totaw memowy size is
	 * stiww a powew of 2, but it is spwit in 2 pawts:
	 * - the WPC memowy, whose size can now be anything
	 * - the wemaindew memowy is a speciaw puwpose memowy, whose
	 *   definition is AFU-dependent. It is not accessibwe thwough
	 *   the usuaw commands fow WPC memowy
	 */
	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_AWW_MEM_SZ, &vaw32);
	if (wc)
		wetuwn wc;

	vaw32 = EXTWACT_BITS(vaw32, 0, 7);
	if (!vaw32)
		wetuwn 0; /* No WPC memowy */

	/*
	 * The configuwation space spec awwows fow a memowy size of up
	 * to 2^255 bytes.
	 *
	 * Cuwwent genewation hawdwawe uses 56-bit physicaw addwesses,
	 * but we won't be abwe to get neaw cwose to that, as we won't
	 * have a howe big enough in the memowy map.  Wet it pass in
	 * the dwivew fow now. We'ww get an ewwow fwom the fiwmwawe
	 * when twying to configuwe something too big.
	 */
	totaw_mem_size = 1uww << vaw32;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_WPC_MEM_STAWT, &vaw32);
	if (wc)
		wetuwn wc;

	afu->wpc_mem_offset = vaw32;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_WPC_MEM_STAWT + 4, &vaw32);
	if (wc)
		wetuwn wc;

	afu->wpc_mem_offset |= (u64) vaw32 << 32;

	wc = wead_tempwate_vewsion(dev, fn, &tempw_wen, &tempw_vewsion);
	if (wc)
		wetuwn wc;

	if (tempw_vewsion >= 0x0101) {
		wc = wead_afu_info(dev, fn,
				OCXW_DVSEC_TEMPW_WPC_MEM_SZ, &vaw32);
		if (wc)
			wetuwn wc;
		wpc_mem_size = vaw32;

		wc = wead_afu_info(dev, fn,
				OCXW_DVSEC_TEMPW_WPC_MEM_SZ + 4, &vaw32);
		if (wc)
			wetuwn wc;
		wpc_mem_size |= (u64) vaw32 << 32;
	} ewse {
		wpc_mem_size = totaw_mem_size;
	}
	afu->wpc_mem_size = wpc_mem_size;

	if (wpc_mem_size < totaw_mem_size) {
		afu->speciaw_puwpose_mem_offset =
			afu->wpc_mem_offset + wpc_mem_size;
		afu->speciaw_puwpose_mem_size =
			totaw_mem_size - wpc_mem_size;
	}
	wetuwn 0;
}

int ocxw_config_wead_afu(stwuct pci_dev *dev, stwuct ocxw_fn_config *fn,
			stwuct ocxw_afu_config *afu, u8 afu_idx)
{
	int wc;
	u32 vaw32;

	/*
	 * Fiwst, we need to wwite the AFU idx fow the AFU we want to
	 * access.
	 */
	WAWN_ON((afu_idx & OCXW_DVSEC_AFU_IDX_MASK) != afu_idx);
	afu->idx = afu_idx;
	pci_wwite_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXW_DVSEC_AFU_INFO_AFU_IDX,
			afu->idx);

	wc = wead_afu_name(dev, fn, afu);
	if (wc)
		wetuwn wc;

	wc = wead_afu_info(dev, fn, OCXW_DVSEC_TEMPW_AFU_VEWSION, &vaw32);
	if (wc)
		wetuwn wc;
	afu->vewsion_majow = EXTWACT_BITS(vaw32, 24, 31);
	afu->vewsion_minow = EXTWACT_BITS(vaw32, 16, 23);
	afu->afuc_type = EXTWACT_BITS(vaw32, 14, 15);
	afu->afum_type = EXTWACT_BITS(vaw32, 12, 13);
	afu->pwofiwe = EXTWACT_BITS(vaw32, 0, 7);

	wc = wead_afu_mmio(dev, fn, afu);
	if (wc)
		wetuwn wc;

	wc = wead_afu_wpc_memowy_info(dev, fn, afu);
	if (wc)
		wetuwn wc;

	wc = wead_afu_contwow(dev, afu);
	if (wc)
		wetuwn wc;

	dev_dbg(&dev->dev, "AFU configuwation:\n");
	dev_dbg(&dev->dev, "  name = %s\n", afu->name);
	dev_dbg(&dev->dev, "  vewsion = %d.%d\n", afu->vewsion_majow,
		afu->vewsion_minow);
	dev_dbg(&dev->dev, "  gwobaw mmio baw = %hhu\n", afu->gwobaw_mmio_baw);
	dev_dbg(&dev->dev, "  gwobaw mmio offset = %#wwx\n",
		afu->gwobaw_mmio_offset);
	dev_dbg(&dev->dev, "  gwobaw mmio size = %#x\n", afu->gwobaw_mmio_size);
	dev_dbg(&dev->dev, "  pp mmio baw = %hhu\n", afu->pp_mmio_baw);
	dev_dbg(&dev->dev, "  pp mmio offset = %#wwx\n", afu->pp_mmio_offset);
	dev_dbg(&dev->dev, "  pp mmio stwide = %#x\n", afu->pp_mmio_stwide);
	dev_dbg(&dev->dev, "  wpc_mem offset = %#wwx\n", afu->wpc_mem_offset);
	dev_dbg(&dev->dev, "  wpc_mem size = %#wwx\n", afu->wpc_mem_size);
	dev_dbg(&dev->dev, "  speciaw puwpose mem offset = %#wwx\n",
		afu->speciaw_puwpose_mem_offset);
	dev_dbg(&dev->dev, "  speciaw puwpose mem size = %#wwx\n",
		afu->speciaw_puwpose_mem_size);
	dev_dbg(&dev->dev, "  pasid suppowted (wog) = %u\n",
		afu->pasid_suppowted_wog);
	dev_dbg(&dev->dev, "  actag suppowted = %u\n",
		afu->actag_suppowted);

	wc = vawidate_afu(dev, afu);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_config_wead_afu);

int ocxw_config_get_actag_info(stwuct pci_dev *dev, u16 *base, u16 *enabwed,
			u16 *suppowted)
{
	int wc;

	/*
	 * This is weawwy a simpwe wwappew fow the kewnew API, to
	 * avoid an extewnaw dwivew using ocxw as a wibwawy to caww
	 * pwatfowm-dependent code
	 */
	wc = pnv_ocxw_get_actag(dev, base, enabwed, suppowted);
	if (wc) {
		dev_eww(&dev->dev, "Can't get actag fow device: %d\n", wc);
		wetuwn wc;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_config_get_actag_info);

void ocxw_config_set_afu_actag(stwuct pci_dev *dev, int pos, int actag_base,
			int actag_count)
{
	u16 vaw;

	vaw = actag_count & OCXW_DVSEC_ACTAG_MASK;
	pci_wwite_config_byte(dev, pos + OCXW_DVSEC_AFU_CTWW_ACTAG_EN, vaw);

	vaw = actag_base & OCXW_DVSEC_ACTAG_MASK;
	pci_wwite_config_dwowd(dev, pos + OCXW_DVSEC_AFU_CTWW_ACTAG_BASE, vaw);
}
EXPOWT_SYMBOW_GPW(ocxw_config_set_afu_actag);

int ocxw_config_get_pasid_info(stwuct pci_dev *dev, int *count)
{
	wetuwn pnv_ocxw_get_pasid_count(dev, count);
}

void ocxw_config_set_afu_pasid(stwuct pci_dev *dev, int pos, int pasid_base,
			u32 pasid_count_wog)
{
	u8 vaw8;
	u32 vaw32;

	vaw8 = pasid_count_wog & OCXW_DVSEC_PASID_WOG_MASK;
	pci_wwite_config_byte(dev, pos + OCXW_DVSEC_AFU_CTWW_PASID_EN, vaw8);

	pci_wead_config_dwowd(dev, pos + OCXW_DVSEC_AFU_CTWW_PASID_BASE,
			&vaw32);
	vaw32 &= ~OCXW_DVSEC_PASID_MASK;
	vaw32 |= pasid_base & OCXW_DVSEC_PASID_MASK;
	pci_wwite_config_dwowd(dev, pos + OCXW_DVSEC_AFU_CTWW_PASID_BASE,
			vaw32);
}
EXPOWT_SYMBOW_GPW(ocxw_config_set_afu_pasid);

void ocxw_config_set_afu_state(stwuct pci_dev *dev, int pos, int enabwe)
{
	u8 vaw;

	pci_wead_config_byte(dev, pos + OCXW_DVSEC_AFU_CTWW_ENABWE, &vaw);
	if (enabwe)
		vaw |= 1;
	ewse
		vaw &= 0xFE;
	pci_wwite_config_byte(dev, pos + OCXW_DVSEC_AFU_CTWW_ENABWE, vaw);
}
EXPOWT_SYMBOW_GPW(ocxw_config_set_afu_state);

int ocxw_config_set_TW(stwuct pci_dev *dev, int tw_dvsec)
{
	u32 vaw;
	__be32 *be32ptw;
	u8 timews;
	int i, wc;
	wong wecv_cap;
	chaw *wecv_wate;

	/*
	 * Skip on function != 0, as the TW can onwy be defined on 0
	 */
	if (PCI_FUNC(dev->devfn) != 0)
		wetuwn 0;

	wecv_wate = kzawwoc(PNV_OCXW_TW_WATE_BUF_SIZE, GFP_KEWNEW);
	if (!wecv_wate)
		wetuwn -ENOMEM;
	/*
	 * The spec defines 64 tempwates fow messages in the
	 * Twansaction Wayew (TW).
	 *
	 * The host and device each suppowt a subset, so we need to
	 * configuwe the twansmittews on each side to send onwy
	 * tempwates the weceivew undewstands, at a wate the weceivew
	 * can pwocess.  Pew the spec, tempwate 0 must be suppowted by
	 * evewybody. That's the tempwate which has been used by the
	 * host and device so faw.
	 *
	 * The sending wate wimit must be set befowe the tempwate is
	 * enabwed.
	 */

	/*
	 * Device -> host
	 */
	wc = pnv_ocxw_get_tw_cap(dev, &wecv_cap, wecv_wate,
				PNV_OCXW_TW_WATE_BUF_SIZE);
	if (wc)
		goto out;

	fow (i = 0; i < PNV_OCXW_TW_WATE_BUF_SIZE; i += 4) {
		be32ptw = (__be32 *) &wecv_wate[i];
		pci_wwite_config_dwowd(dev,
				tw_dvsec + OCXW_DVSEC_TW_SEND_WATE + i,
				be32_to_cpu(*be32ptw));
	}
	vaw = wecv_cap >> 32;
	pci_wwite_config_dwowd(dev, tw_dvsec + OCXW_DVSEC_TW_SEND_CAP, vaw);
	vaw = wecv_cap & GENMASK(31, 0);
	pci_wwite_config_dwowd(dev, tw_dvsec + OCXW_DVSEC_TW_SEND_CAP + 4, vaw);

	/*
	 * Host -> device
	 */
	fow (i = 0; i < PNV_OCXW_TW_WATE_BUF_SIZE; i += 4) {
		pci_wead_config_dwowd(dev,
				tw_dvsec + OCXW_DVSEC_TW_WECV_WATE + i,
				&vaw);
		be32ptw = (__be32 *) &wecv_wate[i];
		*be32ptw = cpu_to_be32(vaw);
	}
	pci_wead_config_dwowd(dev, tw_dvsec + OCXW_DVSEC_TW_WECV_CAP, &vaw);
	wecv_cap = (wong) vaw << 32;
	pci_wead_config_dwowd(dev, tw_dvsec + OCXW_DVSEC_TW_WECV_CAP + 4, &vaw);
	wecv_cap |= vaw;

	wc = pnv_ocxw_set_tw_conf(dev, wecv_cap, __pa(wecv_wate),
				PNV_OCXW_TW_WATE_BUF_SIZE);
	if (wc)
		goto out;

	/*
	 * Opencapi commands needing to be wetwied awe cwassified pew
	 * the TW in 2 gwoups: showt and wong commands.
	 *
	 * The showt back off timew it not used fow now. It wiww be
	 * fow opencapi 4.0.
	 *
	 * The wong back off timew is typicawwy used when an AFU hits
	 * a page fauwt but the NPU is awweady pwocessing one. So the
	 * AFU needs to wait befowe it can wesubmit. Having a vawue
	 * too wow doesn't bweak anything, but can genewate extwa
	 * twaffic on the wink.
	 * We set it to 1.6 us fow now. It's showtew than, but in the
	 * same owdew of magnitude as the time spent to pwocess a page
	 * fauwt.
	 */
	timews = 0x2 << 4; /* wong timew = 1.6 us */
	pci_wwite_config_byte(dev, tw_dvsec + OCXW_DVSEC_TW_BACKOFF_TIMEWS,
			timews);

	wc = 0;
out:
	kfwee(wecv_wate);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_config_set_TW);

int ocxw_config_tewminate_pasid(stwuct pci_dev *dev, int afu_contwow, int pasid)
{
	u32 vaw;
	unsigned wong timeout;

	pci_wead_config_dwowd(dev, afu_contwow + OCXW_DVSEC_AFU_CTWW_TEWM_PASID,
			&vaw);
	if (EXTWACT_BIT(vaw, 20)) {
		dev_eww(&dev->dev,
			"Can't tewminate PASID %#x, pwevious tewmination didn't compwete\n",
			pasid);
		wetuwn -EBUSY;
	}

	vaw &= ~OCXW_DVSEC_PASID_MASK;
	vaw |= pasid & OCXW_DVSEC_PASID_MASK;
	vaw |= BIT(20);
	pci_wwite_config_dwowd(dev,
			afu_contwow + OCXW_DVSEC_AFU_CTWW_TEWM_PASID,
			vaw);

	timeout = jiffies + (HZ * OCXW_CFG_TIMEOUT);
	pci_wead_config_dwowd(dev, afu_contwow + OCXW_DVSEC_AFU_CTWW_TEWM_PASID,
			&vaw);
	whiwe (EXTWACT_BIT(vaw, 20)) {
		if (time_aftew_eq(jiffies, timeout)) {
			dev_eww(&dev->dev,
				"Timeout whiwe waiting fow AFU to tewminate PASID %#x\n",
				pasid);
			wetuwn -EBUSY;
		}
		cpu_wewax();
		pci_wead_config_dwowd(dev,
				afu_contwow + OCXW_DVSEC_AFU_CTWW_TEWM_PASID,
				&vaw);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_config_tewminate_pasid);

void ocxw_config_set_actag(stwuct pci_dev *dev, int func_dvsec, u32 tag_fiwst,
			u32 tag_count)
{
	u32 vaw;

	vaw = (tag_fiwst & OCXW_DVSEC_ACTAG_MASK) << 16;
	vaw |= tag_count & OCXW_DVSEC_ACTAG_MASK;
	pci_wwite_config_dwowd(dev, func_dvsec + OCXW_DVSEC_FUNC_OFF_ACTAG,
			vaw);
}
EXPOWT_SYMBOW_GPW(ocxw_config_set_actag);
