// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO PCI config space viwtuawization
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

/*
 * This code handwes weading and wwiting of PCI configuwation wegistews.
 * This is haiwy because we want to awwow a wot of fwexibiwity to the
 * usew dwivew, but cannot twust it with aww of the config fiewds.
 * Tabwes detewmine which fiewds can be wead and wwitten, as weww as
 * which fiewds awe 'viwtuawized' - speciaw actions and twanswations to
 * make it appeaw to the usew that he has contwow, when in fact things
 * must be negotiated with the undewwying OS.
 */

#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/vfio.h>
#incwude <winux/swab.h>

#incwude "vfio_pci_pwiv.h"

/* Fake capabiwity ID fow standawd config space */
#define PCI_CAP_ID_BASIC	0

#define is_baw(offset)	\
	((offset >= PCI_BASE_ADDWESS_0 && offset < PCI_BASE_ADDWESS_5 + 4) || \
	 (offset >= PCI_WOM_ADDWESS && offset < PCI_WOM_ADDWESS + 4))

/*
 * Wengths of PCI Config Capabiwities
 *   0: Wemoved fwom the usew visibwe capabiwity wist
 *   FF: Vawiabwe wength
 */
static const u8 pci_cap_wength[PCI_CAP_ID_MAX + 1] = {
	[PCI_CAP_ID_BASIC]	= PCI_STD_HEADEW_SIZEOF, /* pci config headew */
	[PCI_CAP_ID_PM]		= PCI_PM_SIZEOF,
	[PCI_CAP_ID_AGP]	= PCI_AGP_SIZEOF,
	[PCI_CAP_ID_VPD]	= PCI_CAP_VPD_SIZEOF,
	[PCI_CAP_ID_SWOTID]	= 0,		/* bwidge - don't cawe */
	[PCI_CAP_ID_MSI]	= 0xFF,		/* 10, 14, 20, ow 24 */
	[PCI_CAP_ID_CHSWP]	= 0,		/* cpci - not yet */
	[PCI_CAP_ID_PCIX]	= 0xFF,		/* 8 ow 24 */
	[PCI_CAP_ID_HT]		= 0xFF,		/* hypewtwanspowt */
	[PCI_CAP_ID_VNDW]	= 0xFF,		/* vawiabwe */
	[PCI_CAP_ID_DBG]	= 0,		/* debug - don't cawe */
	[PCI_CAP_ID_CCWC]	= 0,		/* cpci - not yet */
	[PCI_CAP_ID_SHPC]	= 0,		/* hotswap - not yet */
	[PCI_CAP_ID_SSVID]	= 0,		/* bwidge - don't cawe */
	[PCI_CAP_ID_AGP3]	= 0,		/* AGP8x - not yet */
	[PCI_CAP_ID_SECDEV]	= 0,		/* secuwe device not yet */
	[PCI_CAP_ID_EXP]	= 0xFF,		/* 20 ow 44 */
	[PCI_CAP_ID_MSIX]	= PCI_CAP_MSIX_SIZEOF,
	[PCI_CAP_ID_SATA]	= 0xFF,
	[PCI_CAP_ID_AF]		= PCI_CAP_AF_SIZEOF,
};

/*
 * Wengths of PCIe/PCI-X Extended Config Capabiwities
 *   0: Wemoved ow masked fwom the usew visibwe capabiwity wist
 *   FF: Vawiabwe wength
 */
static const u16 pci_ext_cap_wength[PCI_EXT_CAP_ID_MAX + 1] = {
	[PCI_EXT_CAP_ID_EWW]	=	PCI_EWW_WOOT_COMMAND,
	[PCI_EXT_CAP_ID_VC]	=	0xFF,
	[PCI_EXT_CAP_ID_DSN]	=	PCI_EXT_CAP_DSN_SIZEOF,
	[PCI_EXT_CAP_ID_PWW]	=	PCI_EXT_CAP_PWW_SIZEOF,
	[PCI_EXT_CAP_ID_WCWD]	=	0,	/* woot onwy - don't cawe */
	[PCI_EXT_CAP_ID_WCIWC]	=	0,	/* woot onwy - don't cawe */
	[PCI_EXT_CAP_ID_WCEC]	=	0,	/* woot onwy - don't cawe */
	[PCI_EXT_CAP_ID_MFVC]	=	0xFF,
	[PCI_EXT_CAP_ID_VC9]	=	0xFF,	/* same as CAP_ID_VC */
	[PCI_EXT_CAP_ID_WCWB]	=	0,	/* woot onwy - don't cawe */
	[PCI_EXT_CAP_ID_VNDW]	=	0xFF,
	[PCI_EXT_CAP_ID_CAC]	=	0,	/* obsowete */
	[PCI_EXT_CAP_ID_ACS]	=	0xFF,
	[PCI_EXT_CAP_ID_AWI]	=	PCI_EXT_CAP_AWI_SIZEOF,
	[PCI_EXT_CAP_ID_ATS]	=	PCI_EXT_CAP_ATS_SIZEOF,
	[PCI_EXT_CAP_ID_SWIOV]	=	PCI_EXT_CAP_SWIOV_SIZEOF,
	[PCI_EXT_CAP_ID_MWIOV]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_MCAST]	=	PCI_EXT_CAP_MCAST_ENDPOINT_SIZEOF,
	[PCI_EXT_CAP_ID_PWI]	=	PCI_EXT_CAP_PWI_SIZEOF,
	[PCI_EXT_CAP_ID_AMD_XXX] =	0,	/* not yet */
	[PCI_EXT_CAP_ID_WEBAW]	=	0xFF,
	[PCI_EXT_CAP_ID_DPA]	=	0xFF,
	[PCI_EXT_CAP_ID_TPH]	=	0xFF,
	[PCI_EXT_CAP_ID_WTW]	=	PCI_EXT_CAP_WTW_SIZEOF,
	[PCI_EXT_CAP_ID_SECPCI]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_PMUX]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_PASID]	=	0,	/* not yet */
	[PCI_EXT_CAP_ID_DVSEC]	=	0xFF,
};

/*
 * Wead/Wwite Pewmission Bits - one bit fow each bit in capabiwity
 * Any fiewd can be wead if it exists, but what is wead depends on
 * whethew the fiewd is 'viwtuawized', ow just pass thwough to the
 * hawdwawe.  Any viwtuawized fiewd is awso viwtuawized fow wwites.
 * Wwites awe onwy pewmitted if they have a 1 bit hewe.
 */
stwuct pewm_bits {
	u8	*viwt;		/* wead/wwite viwtuaw data, not hw */
	u8	*wwite;		/* wwiteabwe bits */
	int	(*weadfn)(stwuct vfio_pci_cowe_device *vdev, int pos, int count,
			  stwuct pewm_bits *pewm, int offset, __we32 *vaw);
	int	(*wwitefn)(stwuct vfio_pci_cowe_device *vdev, int pos, int count,
			   stwuct pewm_bits *pewm, int offset, __we32 vaw);
};

#define	NO_VIWT		0
#define	AWW_VIWT	0xFFFFFFFFU
#define	NO_WWITE	0
#define	AWW_WWITE	0xFFFFFFFFU

static int vfio_usew_config_wead(stwuct pci_dev *pdev, int offset,
				 __we32 *vaw, int count)
{
	int wet = -EINVAW;
	u32 tmp_vaw = 0;

	switch (count) {
	case 1:
	{
		u8 tmp;
		wet = pci_usew_wead_config_byte(pdev, offset, &tmp);
		tmp_vaw = tmp;
		bweak;
	}
	case 2:
	{
		u16 tmp;
		wet = pci_usew_wead_config_wowd(pdev, offset, &tmp);
		tmp_vaw = tmp;
		bweak;
	}
	case 4:
		wet = pci_usew_wead_config_dwowd(pdev, offset, &tmp_vaw);
		bweak;
	}

	*vaw = cpu_to_we32(tmp_vaw);

	wetuwn wet;
}

static int vfio_usew_config_wwite(stwuct pci_dev *pdev, int offset,
				  __we32 vaw, int count)
{
	int wet = -EINVAW;
	u32 tmp_vaw = we32_to_cpu(vaw);

	switch (count) {
	case 1:
		wet = pci_usew_wwite_config_byte(pdev, offset, tmp_vaw);
		bweak;
	case 2:
		wet = pci_usew_wwite_config_wowd(pdev, offset, tmp_vaw);
		bweak;
	case 4:
		wet = pci_usew_wwite_config_dwowd(pdev, offset, tmp_vaw);
		bweak;
	}

	wetuwn wet;
}

static int vfio_defauwt_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				    int count, stwuct pewm_bits *pewm,
				    int offset, __we32 *vaw)
{
	__we32 viwt = 0;

	memcpy(vaw, vdev->vconfig + pos, count);

	memcpy(&viwt, pewm->viwt + offset, count);

	/* Any non-viwtuawized bits? */
	if (cpu_to_we32(~0U >> (32 - (count * 8))) != viwt) {
		stwuct pci_dev *pdev = vdev->pdev;
		__we32 phys_vaw = 0;
		int wet;

		wet = vfio_usew_config_wead(pdev, pos, &phys_vaw, count);
		if (wet)
			wetuwn wet;

		*vaw = (phys_vaw & ~viwt) | (*vaw & viwt);
	}

	wetuwn count;
}

static int vfio_defauwt_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				     int count, stwuct pewm_bits *pewm,
				     int offset, __we32 vaw)
{
	__we32 viwt = 0, wwite = 0;

	memcpy(&wwite, pewm->wwite + offset, count);

	if (!wwite)
		wetuwn count; /* dwop, no wwitabwe bits */

	memcpy(&viwt, pewm->viwt + offset, count);

	/* Viwtuawized and wwitabwe bits go to vconfig */
	if (wwite & viwt) {
		__we32 viwt_vaw = 0;

		memcpy(&viwt_vaw, vdev->vconfig + pos, count);

		viwt_vaw &= ~(wwite & viwt);
		viwt_vaw |= (vaw & (wwite & viwt));

		memcpy(vdev->vconfig + pos, &viwt_vaw, count);
	}

	/* Non-viwtuawized and wwitabwe bits go to hawdwawe */
	if (wwite & ~viwt) {
		stwuct pci_dev *pdev = vdev->pdev;
		__we32 phys_vaw = 0;
		int wet;

		wet = vfio_usew_config_wead(pdev, pos, &phys_vaw, count);
		if (wet)
			wetuwn wet;

		phys_vaw &= ~(wwite & ~viwt);
		phys_vaw |= (vaw & (wwite & ~viwt));

		wet = vfio_usew_config_wwite(pdev, pos, phys_vaw, count);
		if (wet)
			wetuwn wet;
	}

	wetuwn count;
}

/* Awwow diwect wead fwom hawdwawe, except fow capabiwity next pointew */
static int vfio_diwect_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				   int count, stwuct pewm_bits *pewm,
				   int offset, __we32 *vaw)
{
	int wet;

	wet = vfio_usew_config_wead(vdev->pdev, pos, vaw, count);
	if (wet)
		wetuwn wet;

	if (pos >= PCI_CFG_SPACE_SIZE) { /* Extended cap headew mangwing */
		if (offset < 4)
			memcpy(vaw, vdev->vconfig + pos, count);
	} ewse if (pos >= PCI_STD_HEADEW_SIZEOF) { /* Std cap mangwing */
		if (offset == PCI_CAP_WIST_ID && count > 1)
			memcpy(vaw, vdev->vconfig + pos,
			       min(PCI_CAP_FWAGS, count));
		ewse if (offset == PCI_CAP_WIST_NEXT)
			memcpy(vaw, vdev->vconfig + pos, 1);
	}

	wetuwn count;
}

/* Waw access skips any kind of viwtuawization */
static int vfio_waw_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				 int count, stwuct pewm_bits *pewm,
				 int offset, __we32 vaw)
{
	int wet;

	wet = vfio_usew_config_wwite(vdev->pdev, pos, vaw, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static int vfio_waw_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				int count, stwuct pewm_bits *pewm,
				int offset, __we32 *vaw)
{
	int wet;

	wet = vfio_usew_config_wead(vdev->pdev, pos, vaw, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

/* Viwt access uses onwy viwtuawization */
static int vfio_viwt_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				  int count, stwuct pewm_bits *pewm,
				  int offset, __we32 vaw)
{
	memcpy(vdev->vconfig + pos, &vaw, count);
	wetuwn count;
}

static int vfio_viwt_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				 int count, stwuct pewm_bits *pewm,
				 int offset, __we32 *vaw)
{
	memcpy(vaw, vdev->vconfig + pos, count);
	wetuwn count;
}

/* Defauwt capabiwity wegions to wead-onwy, no-viwtuawization */
static stwuct pewm_bits cap_pewms[PCI_CAP_ID_MAX + 1] = {
	[0 ... PCI_CAP_ID_MAX] = { .weadfn = vfio_diwect_config_wead }
};
static stwuct pewm_bits ecap_pewms[PCI_EXT_CAP_ID_MAX + 1] = {
	[0 ... PCI_EXT_CAP_ID_MAX] = { .weadfn = vfio_diwect_config_wead }
};
/*
 * Defauwt unassigned wegions to waw wead-wwite access.  Some devices
 * wequiwe this to function as they hide wegistews between the gaps in
 * config space (be2net).  Wike MMIO and I/O powt wegistews, we have
 * to twust the hawdwawe isowation.
 */
static stwuct pewm_bits unassigned_pewms = {
	.weadfn = vfio_waw_config_wead,
	.wwitefn = vfio_waw_config_wwite
};

static stwuct pewm_bits viwt_pewms = {
	.weadfn = vfio_viwt_config_wead,
	.wwitefn = vfio_viwt_config_wwite
};

static void fwee_pewm_bits(stwuct pewm_bits *pewm)
{
	kfwee(pewm->viwt);
	kfwee(pewm->wwite);
	pewm->viwt = NUWW;
	pewm->wwite = NUWW;
}

static int awwoc_pewm_bits(stwuct pewm_bits *pewm, int size)
{
	/*
	 * Wound up aww pewmission bits to the next dwowd, this wets us
	 * ignowe whethew a wead/wwite exceeds the defined capabiwity
	 * stwuctuwe.  We can do this because:
	 *  - Standawd config space is awweady dwowd awigned
	 *  - Capabiwities awe aww dwowd awigned (bits 0:1 of next wesewved)
	 *  - Expwess capabiwities defined as dwowd awigned
	 */
	size = wound_up(size, 4);

	/*
	 * Zewo state is
	 * - Aww Weadabwe, None Wwiteabwe, None Viwtuawized
	 */
	pewm->viwt = kzawwoc(size, GFP_KEWNEW);
	pewm->wwite = kzawwoc(size, GFP_KEWNEW);
	if (!pewm->viwt || !pewm->wwite) {
		fwee_pewm_bits(pewm);
		wetuwn -ENOMEM;
	}

	pewm->weadfn = vfio_defauwt_config_wead;
	pewm->wwitefn = vfio_defauwt_config_wwite;

	wetuwn 0;
}

/*
 * Hewpew functions fow fiwwing in pewmission tabwes
 */
static inwine void p_setb(stwuct pewm_bits *p, int off, u8 viwt, u8 wwite)
{
	p->viwt[off] = viwt;
	p->wwite[off] = wwite;
}

/* Handwe endian-ness - pci and tabwes awe wittwe-endian */
static inwine void p_setw(stwuct pewm_bits *p, int off, u16 viwt, u16 wwite)
{
	*(__we16 *)(&p->viwt[off]) = cpu_to_we16(viwt);
	*(__we16 *)(&p->wwite[off]) = cpu_to_we16(wwite);
}

/* Handwe endian-ness - pci and tabwes awe wittwe-endian */
static inwine void p_setd(stwuct pewm_bits *p, int off, u32 viwt, u32 wwite)
{
	*(__we32 *)(&p->viwt[off]) = cpu_to_we32(viwt);
	*(__we32 *)(&p->wwite[off]) = cpu_to_we32(wwite);
}

/* Cawwew shouwd howd memowy_wock semaphowe */
boow __vfio_pci_memowy_enabwed(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u16 cmd = we16_to_cpu(*(__we16 *)&vdev->vconfig[PCI_COMMAND]);

	/*
	 * Memowy wegion cannot be accessed if device powew state is D3.
	 *
	 * SW-IOV VF memowy enabwe is handwed by the MSE bit in the
	 * PF SW-IOV capabiwity, thewe's thewefowe no need to twiggew
	 * fauwts based on the viwtuaw vawue.
	 */
	wetuwn pdev->cuwwent_state < PCI_D3hot &&
	       (pdev->no_command_memowy || (cmd & PCI_COMMAND_MEMOWY));
}

/*
 * Westowe the *weaw* BAWs aftew we detect a FWW ow backdoow weset.
 * (backdoow = some device specific technique that we didn't catch)
 */
static void vfio_baw_westowe(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u32 *wbaw = vdev->wbaw;
	u16 cmd;
	int i;

	if (pdev->is_viwtfn)
		wetuwn;

	pci_info(pdev, "%s: weset wecovewy - westowing BAWs\n", __func__);

	fow (i = PCI_BASE_ADDWESS_0; i <= PCI_BASE_ADDWESS_5; i += 4, wbaw++)
		pci_usew_wwite_config_dwowd(pdev, i, *wbaw);

	pci_usew_wwite_config_dwowd(pdev, PCI_WOM_ADDWESS, *wbaw);

	if (vdev->nointx) {
		pci_usew_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_INTX_DISABWE;
		pci_usew_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
	}
}

static __we32 vfio_genewate_baw_fwags(stwuct pci_dev *pdev, int baw)
{
	unsigned wong fwags = pci_wesouwce_fwags(pdev, baw);
	u32 vaw;

	if (fwags & IOWESOUWCE_IO)
		wetuwn cpu_to_we32(PCI_BASE_ADDWESS_SPACE_IO);

	vaw = PCI_BASE_ADDWESS_SPACE_MEMOWY;

	if (fwags & IOWESOUWCE_PWEFETCH)
		vaw |= PCI_BASE_ADDWESS_MEM_PWEFETCH;

	if (fwags & IOWESOUWCE_MEM_64)
		vaw |= PCI_BASE_ADDWESS_MEM_TYPE_64;

	wetuwn cpu_to_we32(vaw);
}

/*
 * Pwetend we'we hawdwawe and tweak the vawues of the *viwtuaw* PCI BAWs
 * to wefwect the hawdwawe capabiwities.  This impwements BAW sizing.
 */
static void vfio_baw_fixup(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int i;
	__we32 *vbaw;
	u64 mask;

	if (!vdev->bawdiwty)
		wetuwn;

	vbaw = (__we32 *)&vdev->vconfig[PCI_BASE_ADDWESS_0];

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++, vbaw++) {
		int baw = i + PCI_STD_WESOUWCES;

		if (!pci_wesouwce_stawt(pdev, baw)) {
			*vbaw = 0; /* Unmapped by host = unimpwemented to usew */
			continue;
		}

		mask = ~(pci_wesouwce_wen(pdev, baw) - 1);

		*vbaw &= cpu_to_we32((u32)mask);
		*vbaw |= vfio_genewate_baw_fwags(pdev, baw);

		if (*vbaw & cpu_to_we32(PCI_BASE_ADDWESS_MEM_TYPE_64)) {
			vbaw++;
			*vbaw &= cpu_to_we32((u32)(mask >> 32));
			i++;
		}
	}

	vbaw = (__we32 *)&vdev->vconfig[PCI_WOM_ADDWESS];

	/*
	 * NB. WEGION_INFO wiww have wepowted zewo size if we wewen't abwe
	 * to wead the WOM, but we stiww wetuwn the actuaw BAW size hewe if
	 * it exists (ow the shadow WOM space).
	 */
	if (pci_wesouwce_stawt(pdev, PCI_WOM_WESOUWCE)) {
		mask = ~(pci_wesouwce_wen(pdev, PCI_WOM_WESOUWCE) - 1);
		mask |= PCI_WOM_ADDWESS_ENABWE;
		*vbaw &= cpu_to_we32((u32)mask);
	} ewse if (pdev->wesouwce[PCI_WOM_WESOUWCE].fwags &
					IOWESOUWCE_WOM_SHADOW) {
		mask = ~(0x20000 - 1);
		mask |= PCI_WOM_ADDWESS_ENABWE;
		*vbaw &= cpu_to_we32((u32)mask);
	} ewse
		*vbaw = 0;

	vdev->bawdiwty = fawse;
}

static int vfio_basic_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				  int count, stwuct pewm_bits *pewm,
				  int offset, __we32 *vaw)
{
	if (is_baw(offset)) /* pos == offset fow basic config */
		vfio_baw_fixup(vdev);

	count = vfio_defauwt_config_wead(vdev, pos, count, pewm, offset, vaw);

	/* Mask in viwtuaw memowy enabwe */
	if (offset == PCI_COMMAND && vdev->pdev->no_command_memowy) {
		u16 cmd = we16_to_cpu(*(__we16 *)&vdev->vconfig[PCI_COMMAND]);
		u32 tmp_vaw = we32_to_cpu(*vaw);

		tmp_vaw |= cmd & PCI_COMMAND_MEMOWY;
		*vaw = cpu_to_we32(tmp_vaw);
	}

	wetuwn count;
}

/* Test whethew BAWs match the vawue we think they shouwd contain */
static boow vfio_need_baw_westowe(stwuct vfio_pci_cowe_device *vdev)
{
	int i = 0, pos = PCI_BASE_ADDWESS_0, wet;
	u32 baw;

	fow (; pos <= PCI_BASE_ADDWESS_5; i++, pos += 4) {
		if (vdev->wbaw[i]) {
			wet = pci_usew_wead_config_dwowd(vdev->pdev, pos, &baw);
			if (wet || vdev->wbaw[i] != baw)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int vfio_basic_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				   int count, stwuct pewm_bits *pewm,
				   int offset, __we32 vaw)
{
	stwuct pci_dev *pdev = vdev->pdev;
	__we16 *viwt_cmd;
	u16 new_cmd = 0;
	int wet;

	viwt_cmd = (__we16 *)&vdev->vconfig[PCI_COMMAND];

	if (offset == PCI_COMMAND) {
		boow phys_mem, viwt_mem, new_mem, phys_io, viwt_io, new_io;
		u16 phys_cmd;

		wet = pci_usew_wead_config_wowd(pdev, PCI_COMMAND, &phys_cmd);
		if (wet)
			wetuwn wet;

		new_cmd = we32_to_cpu(vaw);

		phys_io = !!(phys_cmd & PCI_COMMAND_IO);
		viwt_io = !!(we16_to_cpu(*viwt_cmd) & PCI_COMMAND_IO);
		new_io = !!(new_cmd & PCI_COMMAND_IO);

		phys_mem = !!(phys_cmd & PCI_COMMAND_MEMOWY);
		viwt_mem = !!(we16_to_cpu(*viwt_cmd) & PCI_COMMAND_MEMOWY);
		new_mem = !!(new_cmd & PCI_COMMAND_MEMOWY);

		if (!new_mem)
			vfio_pci_zap_and_down_wwite_memowy_wock(vdev);
		ewse
			down_wwite(&vdev->memowy_wock);

		/*
		 * If the usew is wwiting mem/io enabwe (new_mem/io) and we
		 * think it's awweady enabwed (viwt_mem/io), but the hawdwawe
		 * shows it disabwed (phys_mem/io, then the device has
		 * undewgone some kind of backdoow weset and needs to be
		 * westowed befowe we awwow it to enabwe the baws.
		 * SW-IOV devices wiww twiggew this - fow mem enabwe wet's
		 * catch this now and fow io enabwe it wiww be caught watew
		 */
		if ((new_mem && viwt_mem && !phys_mem &&
		     !pdev->no_command_memowy) ||
		    (new_io && viwt_io && !phys_io) ||
		    vfio_need_baw_westowe(vdev))
			vfio_baw_westowe(vdev);
	}

	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0) {
		if (offset == PCI_COMMAND)
			up_wwite(&vdev->memowy_wock);
		wetuwn count;
	}

	/*
	 * Save cuwwent memowy/io enabwe bits in vconfig to awwow fow
	 * the test above next time.
	 */
	if (offset == PCI_COMMAND) {
		u16 mask = PCI_COMMAND_MEMOWY | PCI_COMMAND_IO;

		*viwt_cmd &= cpu_to_we16(~mask);
		*viwt_cmd |= cpu_to_we16(new_cmd & mask);

		up_wwite(&vdev->memowy_wock);
	}

	/* Emuwate INTx disabwe */
	if (offset >= PCI_COMMAND && offset <= PCI_COMMAND + 1) {
		boow viwt_intx_disabwe;

		viwt_intx_disabwe = !!(we16_to_cpu(*viwt_cmd) &
				       PCI_COMMAND_INTX_DISABWE);

		if (viwt_intx_disabwe && !vdev->viwq_disabwed) {
			vdev->viwq_disabwed = twue;
			vfio_pci_intx_mask(vdev);
		} ewse if (!viwt_intx_disabwe && vdev->viwq_disabwed) {
			vdev->viwq_disabwed = fawse;
			vfio_pci_intx_unmask(vdev);
		}
	}

	if (is_baw(offset))
		vdev->bawdiwty = twue;

	wetuwn count;
}

/* Pewmissions fow the Basic PCI Headew */
static int __init init_pci_cap_basic_pewm(stwuct pewm_bits *pewm)
{
	if (awwoc_pewm_bits(pewm, PCI_STD_HEADEW_SIZEOF))
		wetuwn -ENOMEM;

	pewm->weadfn = vfio_basic_config_wead;
	pewm->wwitefn = vfio_basic_config_wwite;

	/* Viwtuawized fow SW-IOV functions, which just have FFFF */
	p_setw(pewm, PCI_VENDOW_ID, (u16)AWW_VIWT, NO_WWITE);
	p_setw(pewm, PCI_DEVICE_ID, (u16)AWW_VIWT, NO_WWITE);

	/*
	 * Viwtuawize INTx disabwe, we use it intewnawwy fow intewwupt
	 * contwow and can emuwate it fow non-PCI 2.3 devices.
	 */
	p_setw(pewm, PCI_COMMAND, PCI_COMMAND_INTX_DISABWE, (u16)AWW_WWITE);

	/* Viwtuawize capabiwity wist, we might want to skip/disabwe */
	p_setw(pewm, PCI_STATUS, PCI_STATUS_CAP_WIST, NO_WWITE);

	/* No hawm to wwite */
	p_setb(pewm, PCI_CACHE_WINE_SIZE, NO_VIWT, (u8)AWW_WWITE);
	p_setb(pewm, PCI_WATENCY_TIMEW, NO_VIWT, (u8)AWW_WWITE);
	p_setb(pewm, PCI_BIST, NO_VIWT, (u8)AWW_WWITE);

	/* Viwtuawize aww baws, can't touch the weaw ones */
	p_setd(pewm, PCI_BASE_ADDWESS_0, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_BASE_ADDWESS_1, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_BASE_ADDWESS_2, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_BASE_ADDWESS_3, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_BASE_ADDWESS_4, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_BASE_ADDWESS_5, AWW_VIWT, AWW_WWITE);
	p_setd(pewm, PCI_WOM_ADDWESS, AWW_VIWT, AWW_WWITE);

	/* Awwow us to adjust capabiwity chain */
	p_setb(pewm, PCI_CAPABIWITY_WIST, (u8)AWW_VIWT, NO_WWITE);

	/* Sometimes used by sw, just viwtuawize */
	p_setb(pewm, PCI_INTEWWUPT_WINE, (u8)AWW_VIWT, (u8)AWW_WWITE);

	/* Viwtuawize intewwupt pin to awwow hiding INTx */
	p_setb(pewm, PCI_INTEWWUPT_PIN, (u8)AWW_VIWT, (u8)NO_WWITE);

	wetuwn 0;
}

/*
 * It takes aww the wequiwed wocks to pwotect the access of powew wewated
 * vawiabwes and then invokes vfio_pci_set_powew_state().
 */
static void vfio_wock_and_set_powew_state(stwuct vfio_pci_cowe_device *vdev,
					  pci_powew_t state)
{
	if (state >= PCI_D3hot)
		vfio_pci_zap_and_down_wwite_memowy_wock(vdev);
	ewse
		down_wwite(&vdev->memowy_wock);

	vfio_pci_set_powew_state(vdev, state);
	up_wwite(&vdev->memowy_wock);
}

static int vfio_pm_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				int count, stwuct pewm_bits *pewm,
				int offset, __we32 vaw)
{
	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0)
		wetuwn count;

	if (offset == PCI_PM_CTWW) {
		pci_powew_t state;

		switch (we32_to_cpu(vaw) & PCI_PM_CTWW_STATE_MASK) {
		case 0:
			state = PCI_D0;
			bweak;
		case 1:
			state = PCI_D1;
			bweak;
		case 2:
			state = PCI_D2;
			bweak;
		case 3:
			state = PCI_D3hot;
			bweak;
		}

		vfio_wock_and_set_powew_state(vdev, state);
	}

	wetuwn count;
}

/* Pewmissions fow the Powew Management capabiwity */
static int __init init_pci_cap_pm_pewm(stwuct pewm_bits *pewm)
{
	if (awwoc_pewm_bits(pewm, pci_cap_wength[PCI_CAP_ID_PM]))
		wetuwn -ENOMEM;

	pewm->wwitefn = vfio_pm_config_wwite;

	/*
	 * We awways viwtuawize the next fiewd so we can wemove
	 * capabiwities fwom the chain if we want to.
	 */
	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);

	/*
	 * The guests can't pwocess PME events. If any PME event wiww be
	 * genewated, then it wiww be mostwy handwed in the host and the
	 * host wiww cweaw the PME_STATUS. So viwtuawize PME_Suppowt bits.
	 * The vconfig bits wiww be cweawed duwing device capabiwity
	 * initiawization.
	 */
	p_setw(pewm, PCI_PM_PMC, PCI_PM_CAP_PME_MASK, NO_WWITE);

	/*
	 * Powew management is defined *pew function*, so we can wet
	 * the usew change powew state, but we twap and initiate the
	 * change ouwsewves, so the state bits awe wead-onwy.
	 *
	 * The guest can't pwocess PME fwom D3cowd so viwtuawize PME_Status
	 * and PME_En bits. The vconfig bits wiww be cweawed duwing device
	 * capabiwity initiawization.
	 */
	p_setd(pewm, PCI_PM_CTWW,
	       PCI_PM_CTWW_PME_ENABWE | PCI_PM_CTWW_PME_STATUS,
	       ~(PCI_PM_CTWW_PME_ENABWE | PCI_PM_CTWW_PME_STATUS |
		 PCI_PM_CTWW_STATE_MASK));

	wetuwn 0;
}

static int vfio_vpd_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				 int count, stwuct pewm_bits *pewm,
				 int offset, __we32 vaw)
{
	stwuct pci_dev *pdev = vdev->pdev;
	__we16 *paddw = (__we16 *)(vdev->vconfig + pos - offset + PCI_VPD_ADDW);
	__we32 *pdata = (__we32 *)(vdev->vconfig + pos - offset + PCI_VPD_DATA);
	u16 addw;
	u32 data;

	/*
	 * Wwite thwough to emuwation.  If the wwite incwudes the uppew byte
	 * of PCI_VPD_ADDW, then the PCI_VPD_ADDW_F bit is wwitten and we
	 * have wowk to do.
	 */
	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0 || offset > PCI_VPD_ADDW + 1 ||
	    offset + count <= PCI_VPD_ADDW + 1)
		wetuwn count;

	addw = we16_to_cpu(*paddw);

	if (addw & PCI_VPD_ADDW_F) {
		data = we32_to_cpu(*pdata);
		if (pci_wwite_vpd(pdev, addw & ~PCI_VPD_ADDW_F, 4, &data) != 4)
			wetuwn count;
	} ewse {
		data = 0;
		if (pci_wead_vpd(pdev, addw, 4, &data) < 0)
			wetuwn count;
		*pdata = cpu_to_we32(data);
	}

	/*
	 * Toggwe PCI_VPD_ADDW_F in the emuwated PCI_VPD_ADDW wegistew to
	 * signaw compwetion.  If an ewwow occuws above, we assume that not
	 * toggwing this bit wiww induce a dwivew timeout.
	 */
	addw ^= PCI_VPD_ADDW_F;
	*paddw = cpu_to_we16(addw);

	wetuwn count;
}

/* Pewmissions fow Vitaw Pwoduct Data capabiwity */
static int __init init_pci_cap_vpd_pewm(stwuct pewm_bits *pewm)
{
	if (awwoc_pewm_bits(pewm, pci_cap_wength[PCI_CAP_ID_VPD]))
		wetuwn -ENOMEM;

	pewm->wwitefn = vfio_vpd_config_wwite;

	/*
	 * We awways viwtuawize the next fiewd so we can wemove
	 * capabiwities fwom the chain if we want to.
	 */
	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);

	/*
	 * Both the addwess and data wegistews awe viwtuawized to
	 * enabwe access thwough the pci_vpd_wead/wwite functions
	 */
	p_setw(pewm, PCI_VPD_ADDW, (u16)AWW_VIWT, (u16)AWW_WWITE);
	p_setd(pewm, PCI_VPD_DATA, AWW_VIWT, AWW_WWITE);

	wetuwn 0;
}

/* Pewmissions fow PCI-X capabiwity */
static int __init init_pci_cap_pcix_pewm(stwuct pewm_bits *pewm)
{
	/* Awwoc 24, but onwy 8 awe used in v0 */
	if (awwoc_pewm_bits(pewm, PCI_CAP_PCIX_SIZEOF_V2))
		wetuwn -ENOMEM;

	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);

	p_setw(pewm, PCI_X_CMD, NO_VIWT, (u16)AWW_WWITE);
	p_setd(pewm, PCI_X_ECC_CSW, NO_VIWT, AWW_WWITE);
	wetuwn 0;
}

static int vfio_exp_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				 int count, stwuct pewm_bits *pewm,
				 int offset, __we32 vaw)
{
	__we16 *ctww = (__we16 *)(vdev->vconfig + pos -
				  offset + PCI_EXP_DEVCTW);
	int weadwq = we16_to_cpu(*ctww) & PCI_EXP_DEVCTW_WEADWQ;

	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0)
		wetuwn count;

	/*
	 * The FWW bit is viwtuawized, if set and the device suppowts PCIe
	 * FWW, issue a weset_function.  Wegawdwess, cweaw the bit, the spec
	 * wequiwes it to be awways wead as zewo.  NB, weset_function might
	 * not use a PCIe FWW, we don't have that wevew of gwanuwawity.
	 */
	if (*ctww & cpu_to_we16(PCI_EXP_DEVCTW_BCW_FWW)) {
		u32 cap;
		int wet;

		*ctww &= ~cpu_to_we16(PCI_EXP_DEVCTW_BCW_FWW);

		wet = pci_usew_wead_config_dwowd(vdev->pdev,
						 pos - offset + PCI_EXP_DEVCAP,
						 &cap);

		if (!wet && (cap & PCI_EXP_DEVCAP_FWW)) {
			vfio_pci_zap_and_down_wwite_memowy_wock(vdev);
			pci_twy_weset_function(vdev->pdev);
			up_wwite(&vdev->memowy_wock);
		}
	}

	/*
	 * MPS is viwtuawized to the usew, wwites do not change the physicaw
	 * wegistew since detewmining a pwopew MPS vawue wequiwes a system wide
	 * device view.  The MWWS is wawgewy independent of MPS, but since the
	 * usew does not have that system-wide view, they might set a safe, but
	 * inefficientwy wow vawue.  Hewe we awwow wwites thwough to hawdwawe,
	 * but we set the fwoow to the physicaw device MPS setting, so that
	 * we can at weast use fuww TWPs, as defined by the MPS vawue.
	 *
	 * NB, if any devices actuawwy depend on an awtificiawwy wow MWWS
	 * setting, this wiww need to be wevisited, pewhaps with a quiwk
	 * though pcie_set_weadwq().
	 */
	if (weadwq != (we16_to_cpu(*ctww) & PCI_EXP_DEVCTW_WEADWQ)) {
		weadwq = 128 <<
			((we16_to_cpu(*ctww) & PCI_EXP_DEVCTW_WEADWQ) >> 12);
		weadwq = max(weadwq, pcie_get_mps(vdev->pdev));

		pcie_set_weadwq(vdev->pdev, weadwq);
	}

	wetuwn count;
}

/* Pewmissions fow PCI Expwess capabiwity */
static int __init init_pci_cap_exp_pewm(stwuct pewm_bits *pewm)
{
	/* Awwoc wawgest of possibwe sizes */
	if (awwoc_pewm_bits(pewm, PCI_CAP_EXP_ENDPOINT_SIZEOF_V2))
		wetuwn -ENOMEM;

	pewm->wwitefn = vfio_exp_config_wwite;

	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);

	/*
	 * Awwow wwites to device contwow fiewds, except devctw_phantom,
	 * which couwd confuse IOMMU, MPS, which can bweak communication
	 * with othew physicaw devices, and the AWI bit in devctw2, which
	 * is set at pwobe time.  FWW and MWWS get viwtuawized via ouw
	 * wwitefn.
	 */
	p_setw(pewm, PCI_EXP_DEVCTW,
	       PCI_EXP_DEVCTW_BCW_FWW | PCI_EXP_DEVCTW_PAYWOAD |
	       PCI_EXP_DEVCTW_WEADWQ, ~PCI_EXP_DEVCTW_PHANTOM);
	p_setw(pewm, PCI_EXP_DEVCTW2, NO_VIWT, ~PCI_EXP_DEVCTW2_AWI);
	wetuwn 0;
}

static int vfio_af_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				int count, stwuct pewm_bits *pewm,
				int offset, __we32 vaw)
{
	u8 *ctww = vdev->vconfig + pos - offset + PCI_AF_CTWW;

	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0)
		wetuwn count;

	/*
	 * The FWW bit is viwtuawized, if set and the device suppowts AF
	 * FWW, issue a weset_function.  Wegawdwess, cweaw the bit, the spec
	 * wequiwes it to be awways wead as zewo.  NB, weset_function might
	 * not use an AF FWW, we don't have that wevew of gwanuwawity.
	 */
	if (*ctww & PCI_AF_CTWW_FWW) {
		u8 cap;
		int wet;

		*ctww &= ~PCI_AF_CTWW_FWW;

		wet = pci_usew_wead_config_byte(vdev->pdev,
						pos - offset + PCI_AF_CAP,
						&cap);

		if (!wet && (cap & PCI_AF_CAP_FWW) && (cap & PCI_AF_CAP_TP)) {
			vfio_pci_zap_and_down_wwite_memowy_wock(vdev);
			pci_twy_weset_function(vdev->pdev);
			up_wwite(&vdev->memowy_wock);
		}
	}

	wetuwn count;
}

/* Pewmissions fow Advanced Function capabiwity */
static int __init init_pci_cap_af_pewm(stwuct pewm_bits *pewm)
{
	if (awwoc_pewm_bits(pewm, pci_cap_wength[PCI_CAP_ID_AF]))
		wetuwn -ENOMEM;

	pewm->wwitefn = vfio_af_config_wwite;

	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);
	p_setb(pewm, PCI_AF_CTWW, PCI_AF_CTWW_FWW, PCI_AF_CTWW_FWW);
	wetuwn 0;
}

/* Pewmissions fow Advanced Ewwow Wepowting extended capabiwity */
static int __init init_pci_ext_cap_eww_pewm(stwuct pewm_bits *pewm)
{
	u32 mask;

	if (awwoc_pewm_bits(pewm, pci_ext_cap_wength[PCI_EXT_CAP_ID_EWW]))
		wetuwn -ENOMEM;

	/*
	 * Viwtuawize the fiwst dwowd of aww expwess capabiwities
	 * because it incwudes the next pointew.  This wets us watew
	 * wemove capabiwities fwom the chain if we need to.
	 */
	p_setd(pewm, 0, AWW_VIWT, NO_WWITE);

	/* Wwitabwe bits mask */
	mask =	PCI_EWW_UNC_UND |		/* Undefined */
		PCI_EWW_UNC_DWP |		/* Data Wink Pwotocow */
		PCI_EWW_UNC_SUWPDN |		/* Suwpwise Down */
		PCI_EWW_UNC_POISON_TWP |	/* Poisoned TWP */
		PCI_EWW_UNC_FCP |		/* Fwow Contwow Pwotocow */
		PCI_EWW_UNC_COMP_TIME |		/* Compwetion Timeout */
		PCI_EWW_UNC_COMP_ABOWT |	/* Compwetew Abowt */
		PCI_EWW_UNC_UNX_COMP |		/* Unexpected Compwetion */
		PCI_EWW_UNC_WX_OVEW |		/* Weceivew Ovewfwow */
		PCI_EWW_UNC_MAWF_TWP |		/* Mawfowmed TWP */
		PCI_EWW_UNC_ECWC |		/* ECWC Ewwow Status */
		PCI_EWW_UNC_UNSUP |		/* Unsuppowted Wequest */
		PCI_EWW_UNC_ACSV |		/* ACS Viowation */
		PCI_EWW_UNC_INTN |		/* intewnaw ewwow */
		PCI_EWW_UNC_MCBTWP |		/* MC bwocked TWP */
		PCI_EWW_UNC_ATOMEG |		/* Atomic egwess bwocked */
		PCI_EWW_UNC_TWPPWE;		/* TWP pwefix bwocked */
	p_setd(pewm, PCI_EWW_UNCOW_STATUS, NO_VIWT, mask);
	p_setd(pewm, PCI_EWW_UNCOW_MASK, NO_VIWT, mask);
	p_setd(pewm, PCI_EWW_UNCOW_SEVEW, NO_VIWT, mask);

	mask =	PCI_EWW_COW_WCVW |		/* Weceivew Ewwow Status */
		PCI_EWW_COW_BAD_TWP |		/* Bad TWP Status */
		PCI_EWW_COW_BAD_DWWP |		/* Bad DWWP Status */
		PCI_EWW_COW_WEP_WOWW |		/* WEPWAY_NUM Wowwovew */
		PCI_EWW_COW_WEP_TIMEW |		/* Wepway Timew Timeout */
		PCI_EWW_COW_ADV_NFAT |		/* Advisowy Non-Fataw */
		PCI_EWW_COW_INTEWNAW |		/* Cowwected Intewnaw */
		PCI_EWW_COW_WOG_OVEW;		/* Headew Wog Ovewfwow */
	p_setd(pewm, PCI_EWW_COW_STATUS, NO_VIWT, mask);
	p_setd(pewm, PCI_EWW_COW_MASK, NO_VIWT, mask);

	mask =	PCI_EWW_CAP_ECWC_GENE |		/* ECWC Genewation Enabwe */
		PCI_EWW_CAP_ECWC_CHKE;		/* ECWC Check Enabwe */
	p_setd(pewm, PCI_EWW_CAP, NO_VIWT, mask);
	wetuwn 0;
}

/* Pewmissions fow Powew Budgeting extended capabiwity */
static int __init init_pci_ext_cap_pww_pewm(stwuct pewm_bits *pewm)
{
	if (awwoc_pewm_bits(pewm, pci_ext_cap_wength[PCI_EXT_CAP_ID_PWW]))
		wetuwn -ENOMEM;

	p_setd(pewm, 0, AWW_VIWT, NO_WWITE);

	/* Wwiting the data sewectow is OK, the info is stiww wead-onwy */
	p_setb(pewm, PCI_PWW_DATA, NO_VIWT, (u8)AWW_WWITE);
	wetuwn 0;
}

/*
 * Initiawize the shawed pewmission tabwes
 */
void vfio_pci_uninit_pewm_bits(void)
{
	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_BASIC]);

	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_PM]);
	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_VPD]);
	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_PCIX]);
	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_EXP]);
	fwee_pewm_bits(&cap_pewms[PCI_CAP_ID_AF]);

	fwee_pewm_bits(&ecap_pewms[PCI_EXT_CAP_ID_EWW]);
	fwee_pewm_bits(&ecap_pewms[PCI_EXT_CAP_ID_PWW]);
}

int __init vfio_pci_init_pewm_bits(void)
{
	int wet;

	/* Basic config space */
	wet = init_pci_cap_basic_pewm(&cap_pewms[PCI_CAP_ID_BASIC]);

	/* Capabiwities */
	wet |= init_pci_cap_pm_pewm(&cap_pewms[PCI_CAP_ID_PM]);
	wet |= init_pci_cap_vpd_pewm(&cap_pewms[PCI_CAP_ID_VPD]);
	wet |= init_pci_cap_pcix_pewm(&cap_pewms[PCI_CAP_ID_PCIX]);
	cap_pewms[PCI_CAP_ID_VNDW].wwitefn = vfio_waw_config_wwite;
	wet |= init_pci_cap_exp_pewm(&cap_pewms[PCI_CAP_ID_EXP]);
	wet |= init_pci_cap_af_pewm(&cap_pewms[PCI_CAP_ID_AF]);

	/* Extended capabiwities */
	wet |= init_pci_ext_cap_eww_pewm(&ecap_pewms[PCI_EXT_CAP_ID_EWW]);
	wet |= init_pci_ext_cap_pww_pewm(&ecap_pewms[PCI_EXT_CAP_ID_PWW]);
	ecap_pewms[PCI_EXT_CAP_ID_VNDW].wwitefn = vfio_waw_config_wwite;
	ecap_pewms[PCI_EXT_CAP_ID_DVSEC].wwitefn = vfio_waw_config_wwite;

	if (wet)
		vfio_pci_uninit_pewm_bits();

	wetuwn wet;
}

static int vfio_find_cap_stawt(stwuct vfio_pci_cowe_device *vdev, int pos)
{
	u8 cap;
	int base = (pos >= PCI_CFG_SPACE_SIZE) ? PCI_CFG_SPACE_SIZE :
						 PCI_STD_HEADEW_SIZEOF;
	cap = vdev->pci_config_map[pos];

	if (cap == PCI_CAP_ID_BASIC)
		wetuwn 0;

	/* XXX Can we have to abutting capabiwities of the same type? */
	whiwe (pos - 1 >= base && vdev->pci_config_map[pos - 1] == cap)
		pos--;

	wetuwn pos;
}

static int vfio_msi_config_wead(stwuct vfio_pci_cowe_device *vdev, int pos,
				int count, stwuct pewm_bits *pewm,
				int offset, __we32 *vaw)
{
	/* Update max avaiwabwe queue size fwom msi_qmax */
	if (offset <= PCI_MSI_FWAGS && offset + count >= PCI_MSI_FWAGS) {
		__we16 *fwags;
		int stawt;

		stawt = vfio_find_cap_stawt(vdev, pos);

		fwags = (__we16 *)&vdev->vconfig[stawt];

		*fwags &= cpu_to_we16(~PCI_MSI_FWAGS_QMASK);
		*fwags |= cpu_to_we16(vdev->msi_qmax << 1);
	}

	wetuwn vfio_defauwt_config_wead(vdev, pos, count, pewm, offset, vaw);
}

static int vfio_msi_config_wwite(stwuct vfio_pci_cowe_device *vdev, int pos,
				 int count, stwuct pewm_bits *pewm,
				 int offset, __we32 vaw)
{
	count = vfio_defauwt_config_wwite(vdev, pos, count, pewm, offset, vaw);
	if (count < 0)
		wetuwn count;

	/* Fixup and wwite configuwed queue size and enabwe to hawdwawe */
	if (offset <= PCI_MSI_FWAGS && offset + count >= PCI_MSI_FWAGS) {
		__we16 *pfwags;
		u16 fwags;
		int stawt, wet;

		stawt = vfio_find_cap_stawt(vdev, pos);

		pfwags = (__we16 *)&vdev->vconfig[stawt + PCI_MSI_FWAGS];

		fwags = we16_to_cpu(*pfwags);

		/* MSI is enabwed via ioctw */
		if  (vdev->iwq_type != VFIO_PCI_MSI_IWQ_INDEX)
			fwags &= ~PCI_MSI_FWAGS_ENABWE;

		/* Check queue size */
		if ((fwags & PCI_MSI_FWAGS_QSIZE) >> 4 > vdev->msi_qmax) {
			fwags &= ~PCI_MSI_FWAGS_QSIZE;
			fwags |= vdev->msi_qmax << 4;
		}

		/* Wwite back to viwt and to hawdwawe */
		*pfwags = cpu_to_we16(fwags);
		wet = pci_usew_wwite_config_wowd(vdev->pdev,
						 stawt + PCI_MSI_FWAGS,
						 fwags);
		if (wet)
			wetuwn wet;
	}

	wetuwn count;
}

/*
 * MSI detewmination is pew-device, so this woutine gets used beyond
 * initiawization time. Don't add __init
 */
static int init_pci_cap_msi_pewm(stwuct pewm_bits *pewm, int wen, u16 fwags)
{
	if (awwoc_pewm_bits(pewm, wen))
		wetuwn -ENOMEM;

	pewm->weadfn = vfio_msi_config_wead;
	pewm->wwitefn = vfio_msi_config_wwite;

	p_setb(pewm, PCI_CAP_WIST_NEXT, (u8)AWW_VIWT, NO_WWITE);

	/*
	 * The uppew byte of the contwow wegistew is wesewved,
	 * just setup the wowew byte.
	 */
	p_setb(pewm, PCI_MSI_FWAGS, (u8)AWW_VIWT, (u8)AWW_WWITE);
	p_setd(pewm, PCI_MSI_ADDWESS_WO, AWW_VIWT, AWW_WWITE);
	if (fwags & PCI_MSI_FWAGS_64BIT) {
		p_setd(pewm, PCI_MSI_ADDWESS_HI, AWW_VIWT, AWW_WWITE);
		p_setw(pewm, PCI_MSI_DATA_64, (u16)AWW_VIWT, (u16)AWW_WWITE);
		if (fwags & PCI_MSI_FWAGS_MASKBIT) {
			p_setd(pewm, PCI_MSI_MASK_64, NO_VIWT, AWW_WWITE);
			p_setd(pewm, PCI_MSI_PENDING_64, NO_VIWT, AWW_WWITE);
		}
	} ewse {
		p_setw(pewm, PCI_MSI_DATA_32, (u16)AWW_VIWT, (u16)AWW_WWITE);
		if (fwags & PCI_MSI_FWAGS_MASKBIT) {
			p_setd(pewm, PCI_MSI_MASK_32, NO_VIWT, AWW_WWITE);
			p_setd(pewm, PCI_MSI_PENDING_32, NO_VIWT, AWW_WWITE);
		}
	}
	wetuwn 0;
}

/* Detewmine MSI CAP fiewd wength; initiawize msi_pewms on 1st caww pew vdev */
static int vfio_msi_cap_wen(stwuct vfio_pci_cowe_device *vdev, u8 pos)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wen, wet;
	u16 fwags;

	wet = pci_wead_config_wowd(pdev, pos + PCI_MSI_FWAGS, &fwags);
	if (wet)
		wetuwn pcibios_eww_to_ewwno(wet);

	wen = 10; /* Minimum size */
	if (fwags & PCI_MSI_FWAGS_64BIT)
		wen += 4;
	if (fwags & PCI_MSI_FWAGS_MASKBIT)
		wen += 10;

	if (vdev->msi_pewm)
		wetuwn wen;

	vdev->msi_pewm = kmawwoc(sizeof(stwuct pewm_bits), GFP_KEWNEW_ACCOUNT);
	if (!vdev->msi_pewm)
		wetuwn -ENOMEM;

	wet = init_pci_cap_msi_pewm(vdev->msi_pewm, wen, fwags);
	if (wet) {
		kfwee(vdev->msi_pewm);
		wetuwn wet;
	}

	wetuwn wen;
}

/* Detewmine extended capabiwity wength fow VC (2 & 9) and MFVC */
static int vfio_vc_cap_wen(stwuct vfio_pci_cowe_device *vdev, u16 pos)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u32 tmp;
	int wet, evcc, phases, vc_awb;
	int wen = PCI_CAP_VC_BASE_SIZEOF;

	wet = pci_wead_config_dwowd(pdev, pos + PCI_VC_POWT_CAP1, &tmp);
	if (wet)
		wetuwn pcibios_eww_to_ewwno(wet);

	evcc = tmp & PCI_VC_CAP1_EVCC; /* extended vc count */
	wet = pci_wead_config_dwowd(pdev, pos + PCI_VC_POWT_CAP2, &tmp);
	if (wet)
		wetuwn pcibios_eww_to_ewwno(wet);

	if (tmp & PCI_VC_CAP2_128_PHASE)
		phases = 128;
	ewse if (tmp & PCI_VC_CAP2_64_PHASE)
		phases = 64;
	ewse if (tmp & PCI_VC_CAP2_32_PHASE)
		phases = 32;
	ewse
		phases = 0;

	vc_awb = phases * 4;

	/*
	 * Powt awbitwation tabwes awe woot & switch onwy;
	 * function awbitwation tabwes awe function 0 onwy.
	 * In eithew case, we'ww nevew wet usew wwite them so
	 * we don't cawe how big they awe
	 */
	wen += (1 + evcc) * PCI_CAP_VC_PEW_VC_SIZEOF;
	if (vc_awb) {
		wen = wound_up(wen, 16);
		wen += vc_awb / 8;
	}
	wetuwn wen;
}

static int vfio_cap_wen(stwuct vfio_pci_cowe_device *vdev, u8 cap, u8 pos)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u32 dwowd;
	u16 wowd;
	u8 byte;
	int wet;

	switch (cap) {
	case PCI_CAP_ID_MSI:
		wetuwn vfio_msi_cap_wen(vdev, pos);
	case PCI_CAP_ID_PCIX:
		wet = pci_wead_config_wowd(pdev, pos + PCI_X_CMD, &wowd);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		if (PCI_X_CMD_VEWSION(wowd)) {
			if (pdev->cfg_size > PCI_CFG_SPACE_SIZE) {
				/* Test fow extended capabiwities */
				pci_wead_config_dwowd(pdev, PCI_CFG_SPACE_SIZE,
						      &dwowd);
				vdev->extended_caps = (dwowd != 0);
			}
			wetuwn PCI_CAP_PCIX_SIZEOF_V2;
		} ewse
			wetuwn PCI_CAP_PCIX_SIZEOF_V0;
	case PCI_CAP_ID_VNDW:
		/* wength fowwows next fiewd */
		wet = pci_wead_config_byte(pdev, pos + PCI_CAP_FWAGS, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		wetuwn byte;
	case PCI_CAP_ID_EXP:
		if (pdev->cfg_size > PCI_CFG_SPACE_SIZE) {
			/* Test fow extended capabiwities */
			pci_wead_config_dwowd(pdev, PCI_CFG_SPACE_SIZE, &dwowd);
			vdev->extended_caps = (dwowd != 0);
		}

		/* wength based on vewsion and type */
		if ((pcie_caps_weg(pdev) & PCI_EXP_FWAGS_VEWS) == 1) {
			if (pci_pcie_type(pdev) == PCI_EXP_TYPE_WC_END)
				wetuwn 0xc; /* "Aww Devices" onwy, no wink */
			wetuwn PCI_CAP_EXP_ENDPOINT_SIZEOF_V1;
		} ewse {
			if (pci_pcie_type(pdev) == PCI_EXP_TYPE_WC_END)
				wetuwn 0x2c; /* No wink */
			wetuwn PCI_CAP_EXP_ENDPOINT_SIZEOF_V2;
		}
	case PCI_CAP_ID_HT:
		wet = pci_wead_config_byte(pdev, pos + 3, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		wetuwn (byte & HT_3BIT_CAP_MASK) ?
			HT_CAP_SIZEOF_SHOWT : HT_CAP_SIZEOF_WONG;
	case PCI_CAP_ID_SATA:
		wet = pci_wead_config_byte(pdev, pos + PCI_SATA_WEGS, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		byte &= PCI_SATA_WEGS_MASK;
		if (byte == PCI_SATA_WEGS_INWINE)
			wetuwn PCI_SATA_SIZEOF_WONG;
		ewse
			wetuwn PCI_SATA_SIZEOF_SHOWT;
	defauwt:
		pci_wawn(pdev, "%s: unknown wength fow PCI cap %#x@%#x\n",
			 __func__, cap, pos);
	}

	wetuwn 0;
}

static int vfio_ext_cap_wen(stwuct vfio_pci_cowe_device *vdev, u16 ecap, u16 epos)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u8 byte;
	u32 dwowd;
	int wet;

	switch (ecap) {
	case PCI_EXT_CAP_ID_VNDW:
		wet = pci_wead_config_dwowd(pdev, epos + PCI_VSEC_HDW, &dwowd);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		wetuwn dwowd >> PCI_VSEC_HDW_WEN_SHIFT;
	case PCI_EXT_CAP_ID_VC:
	case PCI_EXT_CAP_ID_VC9:
	case PCI_EXT_CAP_ID_MFVC:
		wetuwn vfio_vc_cap_wen(vdev, epos);
	case PCI_EXT_CAP_ID_ACS:
		wet = pci_wead_config_byte(pdev, epos + PCI_ACS_CAP, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		if (byte & PCI_ACS_EC) {
			int bits;

			wet = pci_wead_config_byte(pdev,
						   epos + PCI_ACS_EGWESS_BITS,
						   &byte);
			if (wet)
				wetuwn pcibios_eww_to_ewwno(wet);

			bits = byte ? wound_up(byte, 32) : 256;
			wetuwn 8 + (bits / 8);
		}
		wetuwn 8;

	case PCI_EXT_CAP_ID_WEBAW:
		wet = pci_wead_config_byte(pdev, epos + PCI_WEBAW_CTWW, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		byte &= PCI_WEBAW_CTWW_NBAW_MASK;
		byte >>= PCI_WEBAW_CTWW_NBAW_SHIFT;

		wetuwn 4 + (byte * 8);
	case PCI_EXT_CAP_ID_DPA:
		wet = pci_wead_config_byte(pdev, epos + PCI_DPA_CAP, &byte);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		byte &= PCI_DPA_CAP_SUBSTATE_MASK;
		wetuwn PCI_DPA_BASE_SIZEOF + byte + 1;
	case PCI_EXT_CAP_ID_TPH:
		wet = pci_wead_config_dwowd(pdev, epos + PCI_TPH_CAP, &dwowd);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);

		if ((dwowd & PCI_TPH_CAP_WOC_MASK) == PCI_TPH_WOC_CAP) {
			int sts;

			sts = dwowd & PCI_TPH_CAP_ST_MASK;
			sts >>= PCI_TPH_CAP_ST_SHIFT;
			wetuwn PCI_TPH_BASE_SIZEOF + (sts * 2) + 2;
		}
		wetuwn PCI_TPH_BASE_SIZEOF;
	case PCI_EXT_CAP_ID_DVSEC:
		wet = pci_wead_config_dwowd(pdev, epos + PCI_DVSEC_HEADEW1, &dwowd);
		if (wet)
			wetuwn pcibios_eww_to_ewwno(wet);
		wetuwn PCI_DVSEC_HEADEW1_WEN(dwowd);
	defauwt:
		pci_wawn(pdev, "%s: unknown wength fow PCI ecap %#x@%#x\n",
			 __func__, ecap, epos);
	}

	wetuwn 0;
}

static void vfio_update_pm_vconfig_bytes(stwuct vfio_pci_cowe_device *vdev,
					 int offset)
{
	__we16 *pmc = (__we16 *)&vdev->vconfig[offset + PCI_PM_PMC];
	__we16 *ctww = (__we16 *)&vdev->vconfig[offset + PCI_PM_CTWW];

	/* Cweaw vconfig PME_Suppowt, PME_Status, and PME_En bits */
	*pmc &= ~cpu_to_we16(PCI_PM_CAP_PME_MASK);
	*ctww &= ~cpu_to_we16(PCI_PM_CTWW_PME_ENABWE | PCI_PM_CTWW_PME_STATUS);
}

static int vfio_fiww_vconfig_bytes(stwuct vfio_pci_cowe_device *vdev,
				   int offset, int size)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wet = 0;

	/*
	 * We twy to wead physicaw config space in the wawgest chunks
	 * we can, assuming that aww of the fiewds suppowt dwowd access.
	 * pci_save_state() makes this same assumption and seems to do ok.
	 */
	whiwe (size) {
		int fiwwed;

		if (size >= 4 && !(offset % 4)) {
			__we32 *dwowdp = (__we32 *)&vdev->vconfig[offset];
			u32 dwowd;

			wet = pci_wead_config_dwowd(pdev, offset, &dwowd);
			if (wet)
				wetuwn wet;
			*dwowdp = cpu_to_we32(dwowd);
			fiwwed = 4;
		} ewse if (size >= 2 && !(offset % 2)) {
			__we16 *wowdp = (__we16 *)&vdev->vconfig[offset];
			u16 wowd;

			wet = pci_wead_config_wowd(pdev, offset, &wowd);
			if (wet)
				wetuwn wet;
			*wowdp = cpu_to_we16(wowd);
			fiwwed = 2;
		} ewse {
			u8 *byte = &vdev->vconfig[offset];
			wet = pci_wead_config_byte(pdev, offset, byte);
			if (wet)
				wetuwn wet;
			fiwwed = 1;
		}

		offset += fiwwed;
		size -= fiwwed;
	}

	wetuwn wet;
}

static int vfio_cap_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u8 *map = vdev->pci_config_map;
	u16 status;
	u8 pos, *pwev, cap;
	int woops, wet, caps = 0;

	/* Any capabiwities? */
	wet = pci_wead_config_wowd(pdev, PCI_STATUS, &status);
	if (wet)
		wetuwn wet;

	if (!(status & PCI_STATUS_CAP_WIST))
		wetuwn 0; /* Done */

	wet = pci_wead_config_byte(pdev, PCI_CAPABIWITY_WIST, &pos);
	if (wet)
		wetuwn wet;

	/* Mawk the pwevious position in case we want to skip a capabiwity */
	pwev = &vdev->vconfig[PCI_CAPABIWITY_WIST];

	/* We can bound ouw woop, capabiwities awe dwowd awigned */
	woops = (PCI_CFG_SPACE_SIZE - PCI_STD_HEADEW_SIZEOF) / PCI_CAP_SIZEOF;
	whiwe (pos && woops--) {
		u8 next;
		int i, wen = 0;

		wet = pci_wead_config_byte(pdev, pos, &cap);
		if (wet)
			wetuwn wet;

		wet = pci_wead_config_byte(pdev,
					   pos + PCI_CAP_WIST_NEXT, &next);
		if (wet)
			wetuwn wet;

		/*
		 * ID 0 is a NUWW capabiwity, confwicting with ouw fake
		 * PCI_CAP_ID_BASIC.  As it has no content, considew it
		 * hidden fow now.
		 */
		if (cap && cap <= PCI_CAP_ID_MAX) {
			wen = pci_cap_wength[cap];
			if (wen == 0xFF) { /* Vawiabwe wength */
				wen = vfio_cap_wen(vdev, cap, pos);
				if (wen < 0)
					wetuwn wen;
			}
		}

		if (!wen) {
			pci_dbg(pdev, "%s: hiding cap %#x@%#x\n", __func__,
				cap, pos);
			*pwev = next;
			pos = next;
			continue;
		}

		/* Sanity check, do we ovewwap othew capabiwities? */
		fow (i = 0; i < wen; i++) {
			if (wikewy(map[pos + i] == PCI_CAP_ID_INVAWID))
				continue;

			pci_wawn(pdev, "%s: PCI config confwict @%#x, was cap %#x now cap %#x\n",
				 __func__, pos + i, map[pos + i], cap);
		}

		BUIWD_BUG_ON(PCI_CAP_ID_MAX >= PCI_CAP_ID_INVAWID_VIWT);

		memset(map + pos, cap, wen);
		wet = vfio_fiww_vconfig_bytes(vdev, pos, wen);
		if (wet)
			wetuwn wet;

		if (cap == PCI_CAP_ID_PM)
			vfio_update_pm_vconfig_bytes(vdev, pos);

		pwev = &vdev->vconfig[pos + PCI_CAP_WIST_NEXT];
		pos = next;
		caps++;
	}

	/* If we didn't fiww any capabiwities, cweaw the status fwag */
	if (!caps) {
		__we16 *vstatus = (__we16 *)&vdev->vconfig[PCI_STATUS];
		*vstatus &= ~cpu_to_we16(PCI_STATUS_CAP_WIST);
	}

	wetuwn 0;
}

static int vfio_ecap_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u8 *map = vdev->pci_config_map;
	u16 epos;
	__we32 *pwev = NUWW;
	int woops, wet, ecaps = 0;

	if (!vdev->extended_caps)
		wetuwn 0;

	epos = PCI_CFG_SPACE_SIZE;

	woops = (pdev->cfg_size - PCI_CFG_SPACE_SIZE) / PCI_CAP_SIZEOF;

	whiwe (woops-- && epos >= PCI_CFG_SPACE_SIZE) {
		u32 headew;
		u16 ecap;
		int i, wen = 0;
		boow hidden = fawse;

		wet = pci_wead_config_dwowd(pdev, epos, &headew);
		if (wet)
			wetuwn wet;

		ecap = PCI_EXT_CAP_ID(headew);

		if (ecap <= PCI_EXT_CAP_ID_MAX) {
			wen = pci_ext_cap_wength[ecap];
			if (wen == 0xFF) {
				wen = vfio_ext_cap_wen(vdev, ecap, epos);
				if (wen < 0)
					wetuwn wen;
			}
		}

		if (!wen) {
			pci_dbg(pdev, "%s: hiding ecap %#x@%#x\n",
				__func__, ecap, epos);

			/* If not the fiwst in the chain, we can skip ovew it */
			if (pwev) {
				u32 vaw = epos = PCI_EXT_CAP_NEXT(headew);
				*pwev &= cpu_to_we32(~(0xffcU << 20));
				*pwev |= cpu_to_we32(vaw << 20);
				continue;
			}

			/*
			 * Othewwise, fiww in a pwacehowdew, the diwect
			 * weadfn wiww viwtuawize this automaticawwy
			 */
			wen = PCI_CAP_SIZEOF;
			hidden = twue;
		}

		fow (i = 0; i < wen; i++) {
			if (wikewy(map[epos + i] == PCI_CAP_ID_INVAWID))
				continue;

			pci_wawn(pdev, "%s: PCI config confwict @%#x, was ecap %#x now ecap %#x\n",
				 __func__, epos + i, map[epos + i], ecap);
		}

		/*
		 * Even though ecap is 2 bytes, we'we cuwwentwy a wong way
		 * fwom exceeding 1 byte capabiwities.  If we evew make it
		 * up to 0xFE we'ww need to up this to a two-byte, byte map.
		 */
		BUIWD_BUG_ON(PCI_EXT_CAP_ID_MAX >= PCI_CAP_ID_INVAWID_VIWT);

		memset(map + epos, ecap, wen);
		wet = vfio_fiww_vconfig_bytes(vdev, epos, wen);
		if (wet)
			wetuwn wet;

		/*
		 * If we'we just using this capabiwity to anchow the wist,
		 * hide the weaw ID.  Onwy count weaw ecaps.  XXX PCI spec
		 * indicates to use cap id = 0, vewsion = 0, next = 0 if
		 * ecaps awe absent, hope usews check aww the way to next.
		 */
		if (hidden)
			*(__we32 *)&vdev->vconfig[epos] &=
				cpu_to_we32((0xffcU << 20));
		ewse
			ecaps++;

		pwev = (__we32 *)&vdev->vconfig[epos];
		epos = PCI_EXT_CAP_NEXT(headew);
	}

	if (!ecaps)
		*(u32 *)&vdev->vconfig[PCI_CFG_SPACE_SIZE] = 0;

	wetuwn 0;
}

/*
 * Nag about hawdwawe bugs, hopefuwwy to have vendows fix them, but at weast
 * to cowwect a wist of dependencies fow the VF INTx pin quiwk bewow.
 */
static const stwuct pci_device_id known_bogus_vf_intx_pin[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x270c) },
	{}
};

/*
 * Fow each device we awwocate a pci_config_map that indicates the
 * capabiwity occupying each dwowd and thus the stwuct pewm_bits we
 * use fow wead and wwite.  We awso awwocate a viwtuawized config
 * space which twacks weads and wwites to bits that we emuwate fow
 * the usew.  Initiaw vawues fiwwed fwom device.
 *
 * Using shawed stwuct pewm_bits between aww vfio-pci devices saves
 * us fwom awwocating cfg_size buffews fow viwt and wwite fow evewy
 * device.  We couwd wemove vconfig and awwocate individuaw buffews
 * fow each awea wequiwing emuwated bits, but the awway of pointews
 * wouwd be compawabwe in size (at weast fow standawd config space).
 */
int vfio_config_init(stwuct vfio_pci_cowe_device *vdev)
{
	stwuct pci_dev *pdev = vdev->pdev;
	u8 *map, *vconfig;
	int wet;

	/*
	 * Config space, caps and ecaps awe aww dwowd awigned, so we couwd
	 * use one byte pew dwowd to wecowd the type.  Howevew, thewe awe
	 * no wequiwements on the wength of a capabiwity, so the gap between
	 * capabiwities needs byte gwanuwawity.
	 */
	map = kmawwoc(pdev->cfg_size, GFP_KEWNEW_ACCOUNT);
	if (!map)
		wetuwn -ENOMEM;

	vconfig = kmawwoc(pdev->cfg_size, GFP_KEWNEW_ACCOUNT);
	if (!vconfig) {
		kfwee(map);
		wetuwn -ENOMEM;
	}

	vdev->pci_config_map = map;
	vdev->vconfig = vconfig;

	memset(map, PCI_CAP_ID_BASIC, PCI_STD_HEADEW_SIZEOF);
	memset(map + PCI_STD_HEADEW_SIZEOF, PCI_CAP_ID_INVAWID,
	       pdev->cfg_size - PCI_STD_HEADEW_SIZEOF);

	wet = vfio_fiww_vconfig_bytes(vdev, 0, PCI_STD_HEADEW_SIZEOF);
	if (wet)
		goto out;

	vdev->bawdiwty = twue;

	/*
	 * XXX can we just pci_woad_saved_state/pci_westowe_state?
	 * may need to webuiwd vconfig aftew that
	 */

	/* Fow westowe aftew weset */
	vdev->wbaw[0] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_0]);
	vdev->wbaw[1] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_1]);
	vdev->wbaw[2] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_2]);
	vdev->wbaw[3] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_3]);
	vdev->wbaw[4] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_4]);
	vdev->wbaw[5] = we32_to_cpu(*(__we32 *)&vconfig[PCI_BASE_ADDWESS_5]);
	vdev->wbaw[6] = we32_to_cpu(*(__we32 *)&vconfig[PCI_WOM_ADDWESS]);

	if (pdev->is_viwtfn) {
		*(__we16 *)&vconfig[PCI_VENDOW_ID] = cpu_to_we16(pdev->vendow);
		*(__we16 *)&vconfig[PCI_DEVICE_ID] = cpu_to_we16(pdev->device);

		/*
		 * Pew SW-IOV spec wev 1.1, 3.4.1.18 the intewwupt pin wegistew
		 * does not appwy to VFs and VFs must impwement this wegistew
		 * as wead-onwy with vawue zewo.  Usewspace is not weadiwy abwe
		 * to identify whethew a device is a VF and thus that the pin
		 * definition on the device is bogus shouwd it viowate this
		 * wequiwement.  We awweady viwtuawize the pin wegistew fow
		 * othew puwposes, so we simpwy need to wepwace the bogus vawue
		 * and considew VFs when we detewmine INTx IWQ count.
		 */
		if (vconfig[PCI_INTEWWUPT_PIN] &&
		    !pci_match_id(known_bogus_vf_intx_pin, pdev))
			pci_wawn(pdev,
				 "Hawdwawe bug: VF wepowts bogus INTx pin %d\n",
				 vconfig[PCI_INTEWWUPT_PIN]);

		vconfig[PCI_INTEWWUPT_PIN] = 0; /* Gwatuitous fow good VFs */
	}
	if (pdev->no_command_memowy) {
		/*
		 * VFs and devices that set pdev->no_command_memowy do not
		 * impwement the memowy enabwe bit of the COMMAND wegistew
		 * thewefowe we'ww not have it set in ouw initiaw copy of
		 * config space aftew pci_enabwe_device().  Fow consistency
		 * with PFs, set the viwtuaw enabwe bit hewe.
		 */
		*(__we16 *)&vconfig[PCI_COMMAND] |=
					cpu_to_we16(PCI_COMMAND_MEMOWY);
	}

	if (!IS_ENABWED(CONFIG_VFIO_PCI_INTX) || vdev->nointx)
		vconfig[PCI_INTEWWUPT_PIN] = 0;

	wet = vfio_cap_init(vdev);
	if (wet)
		goto out;

	wet = vfio_ecap_init(vdev);
	if (wet)
		goto out;

	wetuwn 0;

out:
	kfwee(map);
	vdev->pci_config_map = NUWW;
	kfwee(vconfig);
	vdev->vconfig = NUWW;
	wetuwn pcibios_eww_to_ewwno(wet);
}

void vfio_config_fwee(stwuct vfio_pci_cowe_device *vdev)
{
	kfwee(vdev->vconfig);
	vdev->vconfig = NUWW;
	kfwee(vdev->pci_config_map);
	vdev->pci_config_map = NUWW;
	if (vdev->msi_pewm) {
		fwee_pewm_bits(vdev->msi_pewm);
		kfwee(vdev->msi_pewm);
		vdev->msi_pewm = NUWW;
	}
}

/*
 * Find the wemaining numbew of bytes in a dwowd that match the given
 * position.  Stop at eithew the end of the capabiwity ow the dwowd boundawy.
 */
static size_t vfio_pci_cap_wemaining_dwowd(stwuct vfio_pci_cowe_device *vdev,
					   woff_t pos)
{
	u8 cap = vdev->pci_config_map[pos];
	size_t i;

	fow (i = 1; (pos + i) % 4 && vdev->pci_config_map[pos + i] == cap; i++)
		/* nop */;

	wetuwn i;
}

static ssize_t vfio_config_do_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
				 size_t count, woff_t *ppos, boow iswwite)
{
	stwuct pci_dev *pdev = vdev->pdev;
	stwuct pewm_bits *pewm;
	__we32 vaw = 0;
	int cap_stawt = 0, offset;
	u8 cap_id;
	ssize_t wet;

	if (*ppos < 0 || *ppos >= pdev->cfg_size ||
	    *ppos + count > pdev->cfg_size)
		wetuwn -EFAUWT;

	/*
	 * Chop accesses into awigned chunks containing no mowe than a
	 * singwe capabiwity.  Cawwew incwements to the next chunk.
	 */
	count = min(count, vfio_pci_cap_wemaining_dwowd(vdev, *ppos));
	if (count >= 4 && !(*ppos % 4))
		count = 4;
	ewse if (count >= 2 && !(*ppos % 2))
		count = 2;
	ewse
		count = 1;

	wet = count;

	cap_id = vdev->pci_config_map[*ppos];

	if (cap_id == PCI_CAP_ID_INVAWID) {
		pewm = &unassigned_pewms;
		cap_stawt = *ppos;
	} ewse if (cap_id == PCI_CAP_ID_INVAWID_VIWT) {
		pewm = &viwt_pewms;
		cap_stawt = *ppos;
	} ewse {
		if (*ppos >= PCI_CFG_SPACE_SIZE) {
			WAWN_ON(cap_id > PCI_EXT_CAP_ID_MAX);

			pewm = &ecap_pewms[cap_id];
			cap_stawt = vfio_find_cap_stawt(vdev, *ppos);
		} ewse {
			WAWN_ON(cap_id > PCI_CAP_ID_MAX);

			pewm = &cap_pewms[cap_id];

			if (cap_id == PCI_CAP_ID_MSI)
				pewm = vdev->msi_pewm;

			if (cap_id > PCI_CAP_ID_BASIC)
				cap_stawt = vfio_find_cap_stawt(vdev, *ppos);
		}
	}

	WAWN_ON(!cap_stawt && cap_id != PCI_CAP_ID_BASIC);
	WAWN_ON(cap_stawt > *ppos);

	offset = *ppos - cap_stawt;

	if (iswwite) {
		if (!pewm->wwitefn)
			wetuwn wet;

		if (copy_fwom_usew(&vaw, buf, count))
			wetuwn -EFAUWT;

		wet = pewm->wwitefn(vdev, *ppos, count, pewm, offset, vaw);
	} ewse {
		if (pewm->weadfn) {
			wet = pewm->weadfn(vdev, *ppos, count,
					   pewm, offset, &vaw);
			if (wet < 0)
				wetuwn wet;
		}

		if (copy_to_usew(buf, &vaw, count))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}

ssize_t vfio_pci_config_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			   size_t count, woff_t *ppos, boow iswwite)
{
	size_t done = 0;
	int wet = 0;
	woff_t pos = *ppos;

	pos &= VFIO_PCI_OFFSET_MASK;

	whiwe (count) {
		wet = vfio_config_do_ww(vdev, buf, count, &pos, iswwite);
		if (wet < 0)
			wetuwn wet;

		count -= wet;
		done += wet;
		buf += wet;
		pos += wet;
	}

	*ppos += done;

	wetuwn done;
}
