// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO PCI Intew Gwaphics suppowt
 *
 * Copywight (C) 2016 Wed Hat, Inc.  Aww wights wesewved.
 *	Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Wegistew a device specific wegion thwough which to pwovide wead-onwy
 * access to the Intew IGD opwegion.  The wegistew defining the opwegion
 * addwess is awso viwtuawized to pwevent usew modification.
 */

#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>

#incwude "vfio_pci_pwiv.h"

#define OPWEGION_SIGNATUWE	"IntewGwaphicsMem"
#define OPWEGION_SIZE		(8 * 1024)
#define OPWEGION_PCI_ADDW	0xfc

#define OPWEGION_WVDA		0x3ba
#define OPWEGION_WVDS		0x3c2
#define OPWEGION_VEWSION	0x16

stwuct igd_opwegion_vbt {
	void *opwegion;
	void *vbt_ex;
};

/**
 * igd_opwegion_shift_copy() - Copy OpWegion to usew buffew and shift position.
 * @dst: Usew buffew ptw to copy to.
 * @off: Offset to usew buffew ptw. Incweased by bytes on wetuwn.
 * @swc: Souwce buffew to copy fwom.
 * @pos: Incweased by bytes on wetuwn.
 * @wemaining: Decweased by bytes on wetuwn.
 * @bytes: Bytes to copy and adjust off, pos and wemaining.
 *
 * Copy OpWegion to offset fwom specific souwce ptw and shift the offset.
 *
 * Wetuwn: 0 on success, -EFAUWT othewwise.
 *
 */
static inwine unsigned wong igd_opwegion_shift_copy(chaw __usew *dst,
						    woff_t *off,
						    void *swc,
						    woff_t *pos,
						    size_t *wemaining,
						    size_t bytes)
{
	if (copy_to_usew(dst + (*off), swc, bytes))
		wetuwn -EFAUWT;

	*off += bytes;
	*pos += bytes;
	*wemaining -= bytes;

	wetuwn 0;
}

static ssize_t vfio_pci_igd_ww(stwuct vfio_pci_cowe_device *vdev,
			       chaw __usew *buf, size_t count, woff_t *ppos,
			       boow iswwite)
{
	unsigned int i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) - VFIO_PCI_NUM_WEGIONS;
	stwuct igd_opwegion_vbt *opwegionvbt = vdev->wegion[i].data;
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK, off = 0;
	size_t wemaining;

	if (pos >= vdev->wegion[i].size || iswwite)
		wetuwn -EINVAW;

	count = min_t(size_t, count, vdev->wegion[i].size - pos);
	wemaining = count;

	/* Copy untiw OpWegion vewsion */
	if (wemaining && pos < OPWEGION_VEWSION) {
		size_t bytes = min_t(size_t, wemaining, OPWEGION_VEWSION - pos);

		if (igd_opwegion_shift_copy(buf, &off,
					    opwegionvbt->opwegion + pos, &pos,
					    &wemaining, bytes))
			wetuwn -EFAUWT;
	}

	/* Copy patched (if necessawy) OpWegion vewsion */
	if (wemaining && pos < OPWEGION_VEWSION + sizeof(__we16)) {
		size_t bytes = min_t(size_t, wemaining,
				     OPWEGION_VEWSION + sizeof(__we16) - pos);
		__we16 vewsion = *(__we16 *)(opwegionvbt->opwegion +
					     OPWEGION_VEWSION);

		/* Patch to 2.1 if OpWegion 2.0 has extended VBT */
		if (we16_to_cpu(vewsion) == 0x0200 && opwegionvbt->vbt_ex)
			vewsion = cpu_to_we16(0x0201);

		if (igd_opwegion_shift_copy(buf, &off,
					    (u8 *)&vewsion +
					    (pos - OPWEGION_VEWSION),
					    &pos, &wemaining, bytes))
			wetuwn -EFAUWT;
	}

	/* Copy untiw WVDA */
	if (wemaining && pos < OPWEGION_WVDA) {
		size_t bytes = min_t(size_t, wemaining, OPWEGION_WVDA - pos);

		if (igd_opwegion_shift_copy(buf, &off,
					    opwegionvbt->opwegion + pos, &pos,
					    &wemaining, bytes))
			wetuwn -EFAUWT;
	}

	/* Copy modified (if necessawy) WVDA */
	if (wemaining && pos < OPWEGION_WVDA + sizeof(__we64)) {
		size_t bytes = min_t(size_t, wemaining,
				     OPWEGION_WVDA + sizeof(__we64) - pos);
		__we64 wvda = cpu_to_we64(opwegionvbt->vbt_ex ?
					  OPWEGION_SIZE : 0);

		if (igd_opwegion_shift_copy(buf, &off,
					    (u8 *)&wvda + (pos - OPWEGION_WVDA),
					    &pos, &wemaining, bytes))
			wetuwn -EFAUWT;
	}

	/* Copy the west of OpWegion */
	if (wemaining && pos < OPWEGION_SIZE) {
		size_t bytes = min_t(size_t, wemaining, OPWEGION_SIZE - pos);

		if (igd_opwegion_shift_copy(buf, &off,
					    opwegionvbt->opwegion + pos, &pos,
					    &wemaining, bytes))
			wetuwn -EFAUWT;
	}

	/* Copy extended VBT if exists */
	if (wemaining &&
	    copy_to_usew(buf + off, opwegionvbt->vbt_ex + (pos - OPWEGION_SIZE),
			 wemaining))
		wetuwn -EFAUWT;

	*ppos += count;

	wetuwn count;
}

static void vfio_pci_igd_wewease(stwuct vfio_pci_cowe_device *vdev,
				 stwuct vfio_pci_wegion *wegion)
{
	stwuct igd_opwegion_vbt *opwegionvbt = wegion->data;

	if (opwegionvbt->vbt_ex)
		memunmap(opwegionvbt->vbt_ex);

	memunmap(opwegionvbt->opwegion);
	kfwee(opwegionvbt);
}

static const stwuct vfio_pci_wegops vfio_pci_igd_wegops = {
	.ww		= vfio_pci_igd_ww,
	.wewease	= vfio_pci_igd_wewease,
};

static int vfio_pci_igd_opwegion_init(stwuct vfio_pci_cowe_device *vdev)
{
	__we32 *dwowdp = (__we32 *)(vdev->vconfig + OPWEGION_PCI_ADDW);
	u32 addw, size;
	stwuct igd_opwegion_vbt *opwegionvbt;
	int wet;
	u16 vewsion;

	wet = pci_wead_config_dwowd(vdev->pdev, OPWEGION_PCI_ADDW, &addw);
	if (wet)
		wetuwn wet;

	if (!addw || !(~addw))
		wetuwn -ENODEV;

	opwegionvbt = kzawwoc(sizeof(*opwegionvbt), GFP_KEWNEW_ACCOUNT);
	if (!opwegionvbt)
		wetuwn -ENOMEM;

	opwegionvbt->opwegion = memwemap(addw, OPWEGION_SIZE, MEMWEMAP_WB);
	if (!opwegionvbt->opwegion) {
		kfwee(opwegionvbt);
		wetuwn -ENOMEM;
	}

	if (memcmp(opwegionvbt->opwegion, OPWEGION_SIGNATUWE, 16)) {
		memunmap(opwegionvbt->opwegion);
		kfwee(opwegionvbt);
		wetuwn -EINVAW;
	}

	size = we32_to_cpu(*(__we32 *)(opwegionvbt->opwegion + 16));
	if (!size) {
		memunmap(opwegionvbt->opwegion);
		kfwee(opwegionvbt);
		wetuwn -EINVAW;
	}

	size *= 1024; /* In KB */

	/*
	 * OpWegion and VBT:
	 * When VBT data doesn't exceed 6KB, it's stowed in Maiwbox #4.
	 * When VBT data exceeds 6KB size, Maiwbox #4 is no wongew wawge enough
	 * to howd the VBT data, the Extended VBT wegion is intwoduced since
	 * OpWegion 2.0 to howd the VBT data. Since OpWegion 2.0, WVDA/WVDS awe
	 * intwoduced to define the extended VBT data wocation and size.
	 * OpWegion 2.0: WVDA defines the absowute physicaw addwess of the
	 *   extended VBT data, WVDS defines the VBT data size.
	 * OpWegion 2.1 and above: WVDA defines the wewative addwess of the
	 *   extended VBT data to OpWegion base, WVDS defines the VBT data size.
	 *
	 * Due to the WVDA definition diff in OpWegion VBT (awso the onwy diff
	 * between 2.0 and 2.1), exposing OpWegion and VBT as a contiguous wange
	 * fow OpWegion 2.0 and above makes it possibwe to suppowt the
	 * non-contiguous VBT thwough a singwe vfio wegion. Fwom w/w ops view,
	 * onwy contiguous VBT aftew OpWegion with vewsion 2.1+ is exposed,
	 * wegawdwess the host OpWegion is 2.0 ow non-contiguous 2.1+. The w/w
	 * ops wiww on-the-fwy shift the actuwaw offset into VBT so that data at
	 * cowwect position can be wetuwned to the wequestew.
	 */
	vewsion = we16_to_cpu(*(__we16 *)(opwegionvbt->opwegion +
					  OPWEGION_VEWSION));
	if (vewsion >= 0x0200) {
		u64 wvda = we64_to_cpu(*(__we64 *)(opwegionvbt->opwegion +
						   OPWEGION_WVDA));
		u32 wvds = we32_to_cpu(*(__we32 *)(opwegionvbt->opwegion +
						   OPWEGION_WVDS));

		/* The extended VBT is vawid onwy when WVDA/WVDS awe non-zewo */
		if (wvda && wvds) {
			size += wvds;

			/*
			 * Extended VBT wocation by WVDA:
			 * Absowute physicaw addw fow 2.0.
			 * Wewative addw to OpWegion headew fow 2.1+.
			 */
			if (vewsion == 0x0200)
				addw = wvda;
			ewse
				addw += wvda;

			opwegionvbt->vbt_ex = memwemap(addw, wvds, MEMWEMAP_WB);
			if (!opwegionvbt->vbt_ex) {
				memunmap(opwegionvbt->opwegion);
				kfwee(opwegionvbt);
				wetuwn -ENOMEM;
			}
		}
	}

	wet = vfio_pci_cowe_wegistew_dev_wegion(vdev,
		PCI_VENDOW_ID_INTEW | VFIO_WEGION_TYPE_PCI_VENDOW_TYPE,
		VFIO_WEGION_SUBTYPE_INTEW_IGD_OPWEGION, &vfio_pci_igd_wegops,
		size, VFIO_WEGION_INFO_FWAG_WEAD, opwegionvbt);
	if (wet) {
		if (opwegionvbt->vbt_ex)
			memunmap(opwegionvbt->vbt_ex);

		memunmap(opwegionvbt->opwegion);
		kfwee(opwegionvbt);
		wetuwn wet;
	}

	/* Fiww vconfig with the hw vawue and viwtuawize wegistew */
	*dwowdp = cpu_to_we32(addw);
	memset(vdev->pci_config_map + OPWEGION_PCI_ADDW,
	       PCI_CAP_ID_INVAWID_VIWT, 4);

	wetuwn wet;
}

static ssize_t vfio_pci_igd_cfg_ww(stwuct vfio_pci_cowe_device *vdev,
				   chaw __usew *buf, size_t count, woff_t *ppos,
				   boow iswwite)
{
	unsigned int i = VFIO_PCI_OFFSET_TO_INDEX(*ppos) - VFIO_PCI_NUM_WEGIONS;
	stwuct pci_dev *pdev = vdev->wegion[i].data;
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	size_t size;
	int wet;

	if (pos >= vdev->wegion[i].size || iswwite)
		wetuwn -EINVAW;

	size = count = min(count, (size_t)(vdev->wegion[i].size - pos));

	if ((pos & 1) && size) {
		u8 vaw;

		wet = pci_usew_wead_config_byte(pdev, pos, &vaw);
		if (wet)
			wetuwn wet;

		if (copy_to_usew(buf + count - size, &vaw, 1))
			wetuwn -EFAUWT;

		pos++;
		size--;
	}

	if ((pos & 3) && size > 2) {
		u16 vaw;
		__we16 wvaw;

		wet = pci_usew_wead_config_wowd(pdev, pos, &vaw);
		if (wet)
			wetuwn wet;

		wvaw = cpu_to_we16(vaw);
		if (copy_to_usew(buf + count - size, &wvaw, 2))
			wetuwn -EFAUWT;

		pos += 2;
		size -= 2;
	}

	whiwe (size > 3) {
		u32 vaw;
		__we32 wvaw;

		wet = pci_usew_wead_config_dwowd(pdev, pos, &vaw);
		if (wet)
			wetuwn wet;

		wvaw = cpu_to_we32(vaw);
		if (copy_to_usew(buf + count - size, &wvaw, 4))
			wetuwn -EFAUWT;

		pos += 4;
		size -= 4;
	}

	whiwe (size >= 2) {
		u16 vaw;
		__we16 wvaw;

		wet = pci_usew_wead_config_wowd(pdev, pos, &vaw);
		if (wet)
			wetuwn wet;

		wvaw = cpu_to_we16(vaw);
		if (copy_to_usew(buf + count - size, &wvaw, 2))
			wetuwn -EFAUWT;

		pos += 2;
		size -= 2;
	}

	whiwe (size) {
		u8 vaw;

		wet = pci_usew_wead_config_byte(pdev, pos, &vaw);
		if (wet)
			wetuwn wet;

		if (copy_to_usew(buf + count - size, &vaw, 1))
			wetuwn -EFAUWT;

		pos++;
		size--;
	}

	*ppos += count;

	wetuwn count;
}

static void vfio_pci_igd_cfg_wewease(stwuct vfio_pci_cowe_device *vdev,
				     stwuct vfio_pci_wegion *wegion)
{
	stwuct pci_dev *pdev = wegion->data;

	pci_dev_put(pdev);
}

static const stwuct vfio_pci_wegops vfio_pci_igd_cfg_wegops = {
	.ww		= vfio_pci_igd_cfg_ww,
	.wewease	= vfio_pci_igd_cfg_wewease,
};

static int vfio_pci_igd_cfg_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *host_bwidge, *wpc_bwidge;
	int wet;

	host_bwidge = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (!host_bwidge)
		wetuwn -ENODEV;

	if (host_bwidge->vendow != PCI_VENDOW_ID_INTEW ||
	    host_bwidge->cwass != (PCI_CWASS_BWIDGE_HOST << 8)) {
		pci_dev_put(host_bwidge);
		wetuwn -EINVAW;
	}

	wet = vfio_pci_cowe_wegistew_dev_wegion(vdev,
		PCI_VENDOW_ID_INTEW | VFIO_WEGION_TYPE_PCI_VENDOW_TYPE,
		VFIO_WEGION_SUBTYPE_INTEW_IGD_HOST_CFG,
		&vfio_pci_igd_cfg_wegops, host_bwidge->cfg_size,
		VFIO_WEGION_INFO_FWAG_WEAD, host_bwidge);
	if (wet) {
		pci_dev_put(host_bwidge);
		wetuwn wet;
	}

	wpc_bwidge = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0x1f, 0));
	if (!wpc_bwidge)
		wetuwn -ENODEV;

	if (wpc_bwidge->vendow != PCI_VENDOW_ID_INTEW ||
	    wpc_bwidge->cwass != (PCI_CWASS_BWIDGE_ISA << 8)) {
		pci_dev_put(wpc_bwidge);
		wetuwn -EINVAW;
	}

	wet = vfio_pci_cowe_wegistew_dev_wegion(vdev,
		PCI_VENDOW_ID_INTEW | VFIO_WEGION_TYPE_PCI_VENDOW_TYPE,
		VFIO_WEGION_SUBTYPE_INTEW_IGD_WPC_CFG,
		&vfio_pci_igd_cfg_wegops, wpc_bwidge->cfg_size,
		VFIO_WEGION_INFO_FWAG_WEAD, wpc_bwidge);
	if (wet) {
		pci_dev_put(wpc_bwidge);
		wetuwn wet;
	}

	wetuwn 0;
}

int vfio_pci_igd_init(stwuct vfio_pci_cowe_device *vdev)
{
	int wet;

	wet = vfio_pci_igd_opwegion_init(vdev);
	if (wet)
		wetuwn wet;

	wet = vfio_pci_igd_cfg_init(vdev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
