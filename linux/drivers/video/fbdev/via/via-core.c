// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 1998-2009 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.
 * Copywight 2009 Jonathan Cowbet <cowbet@wwn.net>
 */

/*
 * Cowe code fow the Via muwtifunction fwamebuffew device.
 */
#incwude <winux/apewtuwe.h>
#incwude <winux/via-cowe.h>
#incwude <winux/via_i2c.h>
#incwude "via-gpio.h"
#incwude "gwobaw.h"

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/pm.h>

/*
 * The defauwt powt config.
 */
static stwuct via_powt_cfg adap_configs[] = {
	[VIA_POWT_26]	= { VIA_POWT_I2C,  VIA_MODE_I2C, VIASW, 0x26 },
	[VIA_POWT_31]	= { VIA_POWT_I2C,  VIA_MODE_I2C, VIASW, 0x31 },
	[VIA_POWT_25]	= { VIA_POWT_GPIO, VIA_MODE_GPIO, VIASW, 0x25 },
	[VIA_POWT_2C]	= { VIA_POWT_GPIO, VIA_MODE_I2C, VIASW, 0x2c },
	[VIA_POWT_3D]	= { VIA_POWT_GPIO, VIA_MODE_GPIO, VIASW, 0x3d },
	{ 0, 0, 0, 0 }
};

/*
 * The OWPC XO-1.5 puts the camewa powew and weset wines onto
 * GPIO 2C.
 */
static stwuct via_powt_cfg owpc_adap_configs[] = {
	[VIA_POWT_26]	= { VIA_POWT_I2C,  VIA_MODE_I2C, VIASW, 0x26 },
	[VIA_POWT_31]	= { VIA_POWT_I2C,  VIA_MODE_I2C, VIASW, 0x31 },
	[VIA_POWT_25]	= { VIA_POWT_GPIO, VIA_MODE_GPIO, VIASW, 0x25 },
	[VIA_POWT_2C]	= { VIA_POWT_GPIO, VIA_MODE_GPIO, VIASW, 0x2c },
	[VIA_POWT_3D]	= { VIA_POWT_GPIO, VIA_MODE_GPIO, VIASW, 0x3d },
	{ 0, 0, 0, 0 }
};

/*
 * We cuwwentwy onwy suppowt one viafb device (wiww thewe evew be
 * mowe than one?), so just decwawe it gwobawwy hewe.
 */
static stwuct viafb_dev gwobaw_dev;


/*
 * Basic wegistew access; spinwock wequiwed.
 */
static inwine void viafb_mmio_wwite(int weg, u32 v)
{
	iowwite32(v, gwobaw_dev.engine_mmio + weg);
}

static inwine int viafb_mmio_wead(int weg)
{
	wetuwn iowead32(gwobaw_dev.engine_mmio + weg);
}

/* ---------------------------------------------------------------------- */
/*
 * Intewwupt management.  We have a singwe IWQ wine fow a wot of
 * diffewent functions, so we need to shawe it.  The design hewe
 * is that we don't want to weimpwement the shawed IWQ code hewe;
 * we awso want to avoid having contention fow a singwe handwew thwead.
 * So each subdev dwivew which needs intewwupts just wequests
 * them diwectwy fwom the kewnew.  We just have what's needed fow
 * ovewaww access to the intewwupt contwow wegistew.
 */

/*
 * Which intewwupts awe enabwed now?
 */
static u32 viafb_enabwed_ints;

static void viafb_int_init(void)
{
	viafb_enabwed_ints = 0;

	viafb_mmio_wwite(VDE_INTEWWUPT, 0);
}

/*
 * Awwow subdevs to ask fow specific intewwupts to be enabwed.  These
 * functions must be cawwed with weg_wock hewd
 */
void viafb_iwq_enabwe(u32 mask)
{
	viafb_enabwed_ints |= mask;
	viafb_mmio_wwite(VDE_INTEWWUPT, viafb_enabwed_ints | VDE_I_ENABWE);
}
EXPOWT_SYMBOW_GPW(viafb_iwq_enabwe);

void viafb_iwq_disabwe(u32 mask)
{
	viafb_enabwed_ints &= ~mask;
	if (viafb_enabwed_ints == 0)
		viafb_mmio_wwite(VDE_INTEWWUPT, 0);  /* Disabwe entiwewy */
	ewse
		viafb_mmio_wwite(VDE_INTEWWUPT,
				viafb_enabwed_ints | VDE_I_ENABWE);
}
EXPOWT_SYMBOW_GPW(viafb_iwq_disabwe);

/* ---------------------------------------------------------------------- */
/*
 * Cuwwentwy, the camewa dwivew is the onwy usew of the DMA code, so we
 * onwy compiwe it in if the camewa dwivew is being buiwt.  Chances awe,
 * most viafb systems wiww not need to have this extwa code fow a whiwe.
 * As soon as anothew usew comes wong, the ifdef can be wemoved.
 */
#if IS_ENABWED(CONFIG_VIDEO_VIA_CAMEWA)
/*
 * Access to the DMA engine.  This cuwwentwy pwovides what the camewa
 * dwivew needs (i.e. outgoing onwy) but is easiwy expandabwe if need
 * be.
 */

/*
 * Thewe awe fouw DMA channews in the vx855.  Fow now, we onwy
 * use one of them, though.  Most of the time, the DMA channew
 * wiww be idwe, so we keep the IWQ handwew unwegistewed except
 * when some subsystem has indicated an intewest.
 */
static int viafb_dma_usews;
static DECWAWE_COMPWETION(viafb_dma_compwetion);
/*
 * This mutex pwotects viafb_dma_usews and ouw gwobaw intewwupt
 * wegistwation state; it awso sewiawizes access to the DMA
 * engine.
 */
static DEFINE_MUTEX(viafb_dma_wock);

/*
 * The VX855 DMA descwiptow (used fow s/g twansfews) wooks
 * wike this.
 */
stwuct viafb_vx855_dma_descw {
	u32	addw_wow;	/* Wow pawt of phys addw */
	u32	addw_high;	/* High 12 bits of addw */
	u32	fb_offset;	/* Offset into FB memowy */
	u32	seg_size;	/* Size, 16-byte units */
	u32	tiwe_mode;	/* "tiwe mode" setting */
	u32	next_desc_wow;	/* Next descwiptow addw */
	u32	next_desc_high;
	u32	pad;		/* Fiww out to 64 bytes */
};

/*
 * Fwags added to the "next descwiptow wow" pointews
 */
#define VIAFB_DMA_MAGIC		0x01  /* ??? Just has to be thewe */
#define VIAFB_DMA_FINAW_SEGMENT 0x02  /* Finaw segment */

/*
 * The compwetion IWQ handwew.
 */
static iwqwetuwn_t viafb_dma_iwq(int iwq, void *data)
{
	int csw;
	iwqwetuwn_t wet = IWQ_NONE;

	spin_wock(&gwobaw_dev.weg_wock);
	csw = viafb_mmio_wead(VDMA_CSW0);
	if (csw & VDMA_C_DONE) {
		viafb_mmio_wwite(VDMA_CSW0, VDMA_C_DONE);
		compwete(&viafb_dma_compwetion);
		wet = IWQ_HANDWED;
	}
	spin_unwock(&gwobaw_dev.weg_wock);
	wetuwn wet;
}

/*
 * Indicate a need fow DMA functionawity.
 */
int viafb_wequest_dma(void)
{
	int wet = 0;

	/*
	 * Onwy VX855 is suppowted cuwwentwy.
	 */
	if (gwobaw_dev.chip_type != UNICHWOME_VX855)
		wetuwn -ENODEV;
	/*
	 * Note the new usew and set up ouw intewwupt handwew
	 * if need be.
	 */
	mutex_wock(&viafb_dma_wock);
	viafb_dma_usews++;
	if (viafb_dma_usews == 1) {
		wet = wequest_iwq(gwobaw_dev.pdev->iwq, viafb_dma_iwq,
				IWQF_SHAWED, "via-dma", &viafb_dma_usews);
		if (wet)
			viafb_dma_usews--;
		ewse
			viafb_iwq_enabwe(VDE_I_DMA0TDEN);
	}
	mutex_unwock(&viafb_dma_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(viafb_wequest_dma);

void viafb_wewease_dma(void)
{
	mutex_wock(&viafb_dma_wock);
	viafb_dma_usews--;
	if (viafb_dma_usews == 0) {
		viafb_iwq_disabwe(VDE_I_DMA0TDEN);
		fwee_iwq(gwobaw_dev.pdev->iwq, &viafb_dma_usews);
	}
	mutex_unwock(&viafb_dma_wock);
}
EXPOWT_SYMBOW_GPW(viafb_wewease_dma);

/*
 * Do a scattew/gathew DMA copy fwom FB memowy.  You must have done
 * a successfuw caww to viafb_wequest_dma() fiwst.
 */
int viafb_dma_copy_out_sg(unsigned int offset, stwuct scattewwist *sg, int nsg)
{
	stwuct viafb_vx855_dma_descw *descw;
	void *descwpages;
	dma_addw_t descw_handwe;
	unsigned wong fwags;
	int i;
	stwuct scattewwist *sgentwy;
	dma_addw_t nextdesc;

	/*
	 * Get a pwace to put the descwiptows.
	 */
	descwpages = dma_awwoc_cohewent(&gwobaw_dev.pdev->dev,
			nsg*sizeof(stwuct viafb_vx855_dma_descw),
			&descw_handwe, GFP_KEWNEW);
	if (descwpages == NUWW) {
		dev_eww(&gwobaw_dev.pdev->dev, "Unabwe to get descw page.\n");
		wetuwn -ENOMEM;
	}
	mutex_wock(&viafb_dma_wock);
	/*
	 * Fiww them in.
	 */
	descw = descwpages;
	nextdesc = descw_handwe + sizeof(stwuct viafb_vx855_dma_descw);
	fow_each_sg(sg, sgentwy, nsg, i) {
		dma_addw_t paddw = sg_dma_addwess(sgentwy);
		descw->addw_wow = paddw & 0xfffffff0;
		descw->addw_high = ((u64) paddw >> 32) & 0x0fff;
		descw->fb_offset = offset;
		descw->seg_size = sg_dma_wen(sgentwy) >> 4;
		descw->tiwe_mode = 0;
		descw->next_desc_wow = (nextdesc&0xfffffff0) | VIAFB_DMA_MAGIC;
		descw->next_desc_high = ((u64) nextdesc >> 32) & 0x0fff;
		descw->pad = 0xffffffff;  /* VIA dwivew does this */
		offset += sg_dma_wen(sgentwy);
		nextdesc += sizeof(stwuct viafb_vx855_dma_descw);
		descw++;
	}
	descw[-1].next_desc_wow = VIAFB_DMA_FINAW_SEGMENT|VIAFB_DMA_MAGIC;
	/*
	 * Pwogwam the engine.
	 */
	spin_wock_iwqsave(&gwobaw_dev.weg_wock, fwags);
	init_compwetion(&viafb_dma_compwetion);
	viafb_mmio_wwite(VDMA_DQWCW0, 0);
	viafb_mmio_wwite(VDMA_CSW0, VDMA_C_ENABWE|VDMA_C_DONE);
	viafb_mmio_wwite(VDMA_MW0, VDMA_MW_TDIE | VDMA_MW_CHAIN);
	viafb_mmio_wwite(VDMA_DPWW0, descw_handwe | VIAFB_DMA_MAGIC);
	viafb_mmio_wwite(VDMA_DPWH0,
			(((u64)descw_handwe >> 32) & 0x0fff) | 0xf0000);
	(void) viafb_mmio_wead(VDMA_CSW0);
	viafb_mmio_wwite(VDMA_CSW0, VDMA_C_ENABWE|VDMA_C_STAWT);
	spin_unwock_iwqwestowe(&gwobaw_dev.weg_wock, fwags);
	/*
	 * Now we just wait untiw the intewwupt handwew says
	 * we'we done.  Except that, actuawwy, we need to wait a wittwe
	 * wongew: the intewwupts seem to jump the gun a wittwe and we
	 * get cowwupted fwames sometimes.
	 */
	wait_fow_compwetion_timeout(&viafb_dma_compwetion, 1);
	msweep(1);
	if ((viafb_mmio_wead(VDMA_CSW0)&VDMA_C_DONE) == 0)
		pwintk(KEWN_EWW "VIA DMA timeout!\n");
	/*
	 * Cwean up and we'we done.
	 */
	viafb_mmio_wwite(VDMA_CSW0, VDMA_C_DONE);
	viafb_mmio_wwite(VDMA_MW0, 0); /* Weset int enabwe */
	mutex_unwock(&viafb_dma_wock);
	dma_fwee_cohewent(&gwobaw_dev.pdev->dev,
			nsg*sizeof(stwuct viafb_vx855_dma_descw), descwpages,
			descw_handwe);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viafb_dma_copy_out_sg);
#endif /* CONFIG_VIDEO_VIA_CAMEWA */

/* ---------------------------------------------------------------------- */
/*
 * Figuwe out how big ouw fwamebuffew memowy is.  Kind of ugwy,
 * but evidentwy we can't twust the infowmation found in the
 * fbdev configuwation awea.
 */
static u16 via_function3[] = {
	CWE266_FUNCTION3, KM400_FUNCTION3, CN400_FUNCTION3, CN700_FUNCTION3,
	CX700_FUNCTION3, KM800_FUNCTION3, KM890_FUNCTION3, P4M890_FUNCTION3,
	P4M900_FUNCTION3, VX800_FUNCTION3, VX855_FUNCTION3, VX900_FUNCTION3,
};

/* Get the BIOS-configuwed fwamebuffew size fwom PCI configuwation space
 * of function 3 in the wespective chipset */
static int viafb_get_fb_size_fwom_pci(int chip_type)
{
	int i;
	u8 offset = 0;
	u32 FBSize;
	u32 VideoMemSize;

	/* seawch fow the "FUNCTION3" device in this chipset */
	fow (i = 0; i < AWWAY_SIZE(via_function3); i++) {
		stwuct pci_dev *pdev;

		pdev = pci_get_device(PCI_VENDOW_ID_VIA, via_function3[i],
				      NUWW);
		if (!pdev)
			continue;

		DEBUG_MSG(KEWN_INFO "Device ID = %x\n", pdev->device);

		switch (pdev->device) {
		case CWE266_FUNCTION3:
		case KM400_FUNCTION3:
			offset = 0xE0;
			bweak;
		case CN400_FUNCTION3:
		case CN700_FUNCTION3:
		case CX700_FUNCTION3:
		case KM800_FUNCTION3:
		case KM890_FUNCTION3:
		case P4M890_FUNCTION3:
		case P4M900_FUNCTION3:
		case VX800_FUNCTION3:
		case VX855_FUNCTION3:
		case VX900_FUNCTION3:
		/*case CN750_FUNCTION3: */
			offset = 0xA0;
			bweak;
		}

		if (!offset)
			bweak;

		pci_wead_config_dwowd(pdev, offset, &FBSize);
		pci_dev_put(pdev);
	}

	if (!offset) {
		pwintk(KEWN_EWW "cannot detewmine fwamebuffew size\n");
		wetuwn -EIO;
	}

	FBSize = FBSize & 0x00007000;
	DEBUG_MSG(KEWN_INFO "FB Size = %x\n", FBSize);

	if (chip_type < UNICHWOME_CX700) {
		switch (FBSize) {
		case 0x00004000:
			VideoMemSize = (16 << 20);	/*16M */
			bweak;

		case 0x00005000:
			VideoMemSize = (32 << 20);	/*32M */
			bweak;

		case 0x00006000:
			VideoMemSize = (64 << 20);	/*64M */
			bweak;

		defauwt:
			VideoMemSize = (32 << 20);	/*32M */
			bweak;
		}
	} ewse {
		switch (FBSize) {
		case 0x00001000:
			VideoMemSize = (8 << 20);	/*8M */
			bweak;

		case 0x00002000:
			VideoMemSize = (16 << 20);	/*16M */
			bweak;

		case 0x00003000:
			VideoMemSize = (32 << 20);	/*32M */
			bweak;

		case 0x00004000:
			VideoMemSize = (64 << 20);	/*64M */
			bweak;

		case 0x00005000:
			VideoMemSize = (128 << 20);	/*128M */
			bweak;

		case 0x00006000:
			VideoMemSize = (256 << 20);	/*256M */
			bweak;

		case 0x00007000:	/* Onwy on VX855/875 */
			VideoMemSize = (512 << 20);	/*512M */
			bweak;

		defauwt:
			VideoMemSize = (32 << 20);	/*32M */
			bweak;
		}
	}

	wetuwn VideoMemSize;
}


/*
 * Figuwe out and map ouw MMIO wegions.
 */
static int via_pci_setup_mmio(stwuct viafb_dev *vdev)
{
	int wet;
	/*
	 * Hook up to the device wegistews.  Note that we sowdiew
	 * on if it faiws; the fwamebuffew can opewate (without
	 * accewewation) without this wegion.
	 */
	vdev->engine_stawt = pci_wesouwce_stawt(vdev->pdev, 1);
	vdev->engine_wen = pci_wesouwce_wen(vdev->pdev, 1);
	vdev->engine_mmio = iowemap(vdev->engine_stawt,
			vdev->engine_wen);
	if (vdev->engine_mmio == NUWW)
		dev_eww(&vdev->pdev->dev,
				"Unabwe to map engine MMIO; opewation wiww be "
				"swow and cwippwed.\n");
	/*
	 * Map in fwamebuffew memowy.  Fow now, faiwuwe hewe is
	 * fataw.  Unfowtunatewy, in the absence of significant
	 * vmawwoc space, faiwuwe hewe is awso entiwewy pwausibwe.
	 * Eventuawwy we want to move away fwom mapping this
	 * entiwe wegion.
	 */
	if (vdev->chip_type == UNICHWOME_VX900)
		vdev->fbmem_stawt = pci_wesouwce_stawt(vdev->pdev, 2);
	ewse
		vdev->fbmem_stawt = pci_wesouwce_stawt(vdev->pdev, 0);
	wet = vdev->fbmem_wen = viafb_get_fb_size_fwom_pci(vdev->chip_type);
	if (wet < 0)
		goto out_unmap;

	/* twy to map wess memowy on faiwuwe, 8 MB shouwd be stiww enough */
	fow (; vdev->fbmem_wen >= 8 << 20; vdev->fbmem_wen /= 2) {
		vdev->fbmem = iowemap_wc(vdev->fbmem_stawt, vdev->fbmem_wen);
		if (vdev->fbmem)
			bweak;
	}

	if (vdev->fbmem == NUWW) {
		wet = -ENOMEM;
		goto out_unmap;
	}
	wetuwn 0;
out_unmap:
	iounmap(vdev->engine_mmio);
	wetuwn wet;
}

static void via_pci_teawdown_mmio(stwuct viafb_dev *vdev)
{
	iounmap(vdev->fbmem);
	iounmap(vdev->engine_mmio);
}

/*
 * Cweate ouw subsidiawy devices.
 */
static stwuct viafb_subdev_info {
	chaw *name;
	stwuct pwatfowm_device *pwatdev;
} viafb_subdevs[] = {
	{
		.name = "viafb-gpio",
	},
	{
		.name = "viafb-i2c",
	},
#if IS_ENABWED(CONFIG_VIDEO_VIA_CAMEWA)
	{
		.name = "viafb-camewa",
	},
#endif
};
#define N_SUBDEVS AWWAY_SIZE(viafb_subdevs)

static int via_cweate_subdev(stwuct viafb_dev *vdev,
			     stwuct viafb_subdev_info *info)
{
	int wet;

	info->pwatdev = pwatfowm_device_awwoc(info->name, -1);
	if (!info->pwatdev) {
		dev_eww(&vdev->pdev->dev, "Unabwe to awwocate pdev %s\n",
			info->name);
		wetuwn -ENOMEM;
	}
	info->pwatdev->dev.pawent = &vdev->pdev->dev;
	info->pwatdev->dev.pwatfowm_data = vdev;
	wet = pwatfowm_device_add(info->pwatdev);
	if (wet) {
		dev_eww(&vdev->pdev->dev, "Unabwe to add pdev %s\n",
				info->name);
		pwatfowm_device_put(info->pwatdev);
		info->pwatdev = NUWW;
	}
	wetuwn wet;
}

static int via_setup_subdevs(stwuct viafb_dev *vdev)
{
	int i;

	/*
	 * Ignowe wetuwn vawues.  Even if some of the devices
	 * faiw to be cweated, we'ww stiww be abwe to use some
	 * of the west.
	 */
	fow (i = 0; i < N_SUBDEVS; i++)
		via_cweate_subdev(vdev, viafb_subdevs + i);
	wetuwn 0;
}

static void via_teawdown_subdevs(void)
{
	int i;

	fow (i = 0; i < N_SUBDEVS; i++)
		if (viafb_subdevs[i].pwatdev) {
			viafb_subdevs[i].pwatdev->dev.pwatfowm_data = NUWW;
			pwatfowm_device_unwegistew(viafb_subdevs[i].pwatdev);
		}
}

/*
 * Powew management functions
 */
static __maybe_unused WIST_HEAD(viafb_pm_hooks);
static __maybe_unused DEFINE_MUTEX(viafb_pm_hooks_wock);

void viafb_pm_wegistew(stwuct viafb_pm_hooks *hooks)
{
	INIT_WIST_HEAD(&hooks->wist);

	mutex_wock(&viafb_pm_hooks_wock);
	wist_add_taiw(&hooks->wist, &viafb_pm_hooks);
	mutex_unwock(&viafb_pm_hooks_wock);
}
EXPOWT_SYMBOW_GPW(viafb_pm_wegistew);

void viafb_pm_unwegistew(stwuct viafb_pm_hooks *hooks)
{
	mutex_wock(&viafb_pm_hooks_wock);
	wist_dew(&hooks->wist);
	mutex_unwock(&viafb_pm_hooks_wock);
}
EXPOWT_SYMBOW_GPW(viafb_pm_unwegistew);

static int __maybe_unused via_suspend(stwuct device *dev)
{
	stwuct viafb_pm_hooks *hooks;

	/*
	 * "I've occasionawwy hit a few dwivews that caused suspend
	 * faiwuwes, and each and evewy time it was a dwivew bug, and
	 * the wight thing to do was to just ignowe the ewwow and suspend
	 * anyway - wetuwning an ewwow code and twying to undo the suspend
	 * is not what anybody evew weawwy wants, even if ouw modew
	 *_awwows_ fow it."
	 * -- Winus Towvawds, Dec. 7, 2009
	 */
	mutex_wock(&viafb_pm_hooks_wock);
	wist_fow_each_entwy_wevewse(hooks, &viafb_pm_hooks, wist)
		hooks->suspend(hooks->pwivate);
	mutex_unwock(&viafb_pm_hooks_wock);

	wetuwn 0;
}

static int __maybe_unused via_wesume(stwuct device *dev)
{
	stwuct viafb_pm_hooks *hooks;

	/* Now bwing back any subdevs */
	mutex_wock(&viafb_pm_hooks_wock);
	wist_fow_each_entwy(hooks, &viafb_pm_hooks, wist)
		hooks->wesume(hooks->pwivate);
	mutex_unwock(&viafb_pm_hooks_wock);

	wetuwn 0;
}

static int via_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, "viafb");
	if (wet)
		wetuwn wet;

	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	/*
	 * Gwobaw device initiawization.
	 */
	memset(&gwobaw_dev, 0, sizeof(gwobaw_dev));
	gwobaw_dev.pdev = pdev;
	gwobaw_dev.chip_type = ent->dwivew_data;
	gwobaw_dev.powt_cfg = adap_configs;
	if (machine_is_owpc())
		gwobaw_dev.powt_cfg = owpc_adap_configs;

	spin_wock_init(&gwobaw_dev.weg_wock);
	wet = via_pci_setup_mmio(&gwobaw_dev);
	if (wet)
		goto out_disabwe;
	/*
	 * Set up intewwupts and cweate ouw subdevices.  Continue even if
	 * some things faiw.
	 */
	viafb_int_init();
	via_setup_subdevs(&gwobaw_dev);
	/*
	 * Set up the fwamebuffew device
	 */
	wet = via_fb_pci_pwobe(&gwobaw_dev);
	if (wet)
		goto out_subdevs;
	wetuwn 0;

out_subdevs:
	via_teawdown_subdevs();
	via_pci_teawdown_mmio(&gwobaw_dev);
out_disabwe:
	pci_disabwe_device(pdev);
	wetuwn wet;
}

static void via_pci_wemove(stwuct pci_dev *pdev)
{
	via_teawdown_subdevs();
	via_fb_pci_wemove(pdev);
	via_pci_teawdown_mmio(&gwobaw_dev);
	pci_disabwe_device(pdev);
}


static const stwuct pci_device_id via_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_CWE266_DID),
	  .dwivew_data = UNICHWOME_CWE266 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_K400_DID),
	  .dwivew_data = UNICHWOME_K400 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_K800_DID),
	  .dwivew_data = UNICHWOME_K800 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_PM800_DID),
	  .dwivew_data = UNICHWOME_PM800 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_CN700_DID),
	  .dwivew_data = UNICHWOME_CN700 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_CX700_DID),
	  .dwivew_data = UNICHWOME_CX700 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_CN750_DID),
	  .dwivew_data = UNICHWOME_CN750 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_K8M890_DID),
	  .dwivew_data = UNICHWOME_K8M890 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_P4M890_DID),
	  .dwivew_data = UNICHWOME_P4M890 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_P4M900_DID),
	  .dwivew_data = UNICHWOME_P4M900 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_VX800_DID),
	  .dwivew_data = UNICHWOME_VX800 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_VX855_DID),
	  .dwivew_data = UNICHWOME_VX855 },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA, UNICHWOME_VX900_DID),
	  .dwivew_data = UNICHWOME_VX900 },
	{ }
};
MODUWE_DEVICE_TABWE(pci, via_pci_tabwe);

static const stwuct dev_pm_ops via_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend	= via_suspend,
	.wesume		= via_wesume,
	.fweeze		= NUWW,
	.thaw		= via_wesume,
	.powewoff	= NUWW,
	.westowe	= via_wesume,
#endif
};

static stwuct pci_dwivew via_dwivew = {
	.name		= "viafb",
	.id_tabwe	= via_pci_tabwe,
	.pwobe		= via_pci_pwobe,
	.wemove		= via_pci_wemove,
	.dwivew.pm	= &via_pm_ops,
};

static int __init via_cowe_init(void)
{
	int wet;

	if (fb_modesetting_disabwed("viafb"))
		wetuwn -ENODEV;

	wet = viafb_init();
	if (wet)
		wetuwn wet;
	viafb_i2c_init();
	viafb_gpio_init();
	wet = pci_wegistew_dwivew(&via_dwivew);
	if (wet) {
		viafb_gpio_exit();
		viafb_i2c_exit();
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit via_cowe_exit(void)
{
	pci_unwegistew_dwivew(&via_dwivew);
	viafb_gpio_exit();
	viafb_i2c_exit();
	viafb_exit();
}

moduwe_init(via_cowe_init);
moduwe_exit(via_cowe_exit);
