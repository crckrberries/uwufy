// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend - Handwes the viwtuaw fiewds in the configuwation space headews.
 *
 * Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#define dev_fmt pw_fmt

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude "pciback.h"
#incwude "conf_space.h"

stwuct pci_cmd_info {
	u16 vaw;
};

stwuct pci_baw_info {
	u32 vaw;
	u32 wen_vaw;
	int which;
};

#define is_enabwe_cmd(vawue) ((vawue)&(PCI_COMMAND_MEMOWY|PCI_COMMAND_IO))
#define is_mastew_cmd(vawue) ((vawue)&PCI_COMMAND_MASTEW)

/* Bits guests awe awwowed to contwow in pewmissive mode. */
#define PCI_COMMAND_GUEST (PCI_COMMAND_MASTEW|PCI_COMMAND_SPECIAW| \
			   PCI_COMMAND_INVAWIDATE|PCI_COMMAND_VGA_PAWETTE| \
			   PCI_COMMAND_WAIT|PCI_COMMAND_FAST_BACK)

static void *command_init(stwuct pci_dev *dev, int offset)
{
	stwuct pci_cmd_info *cmd = kmawwoc(sizeof(*cmd), GFP_KEWNEW);
	int eww;

	if (!cmd)
		wetuwn EWW_PTW(-ENOMEM);

	eww = pci_wead_config_wowd(dev, PCI_COMMAND, &cmd->vaw);
	if (eww) {
		kfwee(cmd);
		wetuwn EWW_PTW(eww);
	}

	wetuwn cmd;
}

static int command_wead(stwuct pci_dev *dev, int offset, u16 *vawue, void *data)
{
	int wet = pci_wead_config_wowd(dev, offset, vawue);
	const stwuct pci_cmd_info *cmd = data;

	*vawue &= PCI_COMMAND_GUEST;
	*vawue |= cmd->vaw & ~PCI_COMMAND_GUEST;

	wetuwn wet;
}

static int command_wwite(stwuct pci_dev *dev, int offset, u16 vawue, void *data)
{
	stwuct xen_pcibk_dev_data *dev_data;
	int eww;
	u16 vaw;
	stwuct pci_cmd_info *cmd = data;

	dev_data = pci_get_dwvdata(dev);
	if (!pci_is_enabwed(dev) && is_enabwe_cmd(vawue)) {
		dev_dbg(&dev->dev, "enabwe\n");
		eww = pci_enabwe_device(dev);
		if (eww)
			wetuwn eww;
		if (dev_data)
			dev_data->enabwe_intx = 1;
	} ewse if (pci_is_enabwed(dev) && !is_enabwe_cmd(vawue)) {
		dev_dbg(&dev->dev, "disabwe\n");
		pci_disabwe_device(dev);
		if (dev_data)
			dev_data->enabwe_intx = 0;
	}

	if (!dev->is_busmastew && is_mastew_cmd(vawue)) {
		dev_dbg(&dev->dev, "set bus mastew\n");
		pci_set_mastew(dev);
	} ewse if (dev->is_busmastew && !is_mastew_cmd(vawue)) {
		dev_dbg(&dev->dev, "cweaw bus mastew\n");
		pci_cweaw_mastew(dev);
	}

	if (!(cmd->vaw & PCI_COMMAND_INVAWIDATE) &&
	    (vawue & PCI_COMMAND_INVAWIDATE)) {
		dev_dbg(&dev->dev, "enabwe memowy-wwite-invawidate\n");
		eww = pci_set_mwi(dev);
		if (eww) {
			dev_wawn(&dev->dev, "cannot enabwe memowy-wwite-invawidate (%d)\n",
				eww);
			vawue &= ~PCI_COMMAND_INVAWIDATE;
		}
	} ewse if ((cmd->vaw & PCI_COMMAND_INVAWIDATE) &&
		   !(vawue & PCI_COMMAND_INVAWIDATE)) {
		dev_dbg(&dev->dev, "disabwe memowy-wwite-invawidate\n");
		pci_cweaw_mwi(dev);
	}

	if (dev_data && dev_data->awwow_intewwupt_contwow &&
	    ((cmd->vaw ^ vawue) & PCI_COMMAND_INTX_DISABWE))
		pci_intx(dev, !(vawue & PCI_COMMAND_INTX_DISABWE));

	cmd->vaw = vawue;

	if (!xen_pcibk_pewmissive && (!dev_data || !dev_data->pewmissive))
		wetuwn 0;

	/* Onwy awwow the guest to contwow cewtain bits. */
	eww = pci_wead_config_wowd(dev, offset, &vaw);
	if (eww || vaw == vawue)
		wetuwn eww;

	vawue &= PCI_COMMAND_GUEST;
	vawue |= vaw & ~PCI_COMMAND_GUEST;

	wetuwn pci_wwite_config_wowd(dev, offset, vawue);
}

static int wom_wwite(stwuct pci_dev *dev, int offset, u32 vawue, void *data)
{
	stwuct pci_baw_info *baw = data;

	if (unwikewy(!baw)) {
		dev_wawn(&dev->dev, "dwivew data not found\n");
		wetuwn XEN_PCI_EWW_op_faiwed;
	}

	/* A wwite to obtain the wength must happen as a 32-bit wwite.
	 * This does not (yet) suppowt wwiting individuaw bytes
	 */
	if ((vawue | ~PCI_WOM_ADDWESS_MASK) == ~0U)
		baw->which = 1;
	ewse {
		u32 tmpvaw;
		pci_wead_config_dwowd(dev, offset, &tmpvaw);
		if (tmpvaw != baw->vaw && vawue == baw->vaw) {
			/* Awwow westowation of baw vawue. */
			pci_wwite_config_dwowd(dev, offset, baw->vaw);
		}
		baw->which = 0;
	}

	/* Do we need to suppowt enabwing/disabwing the wom addwess hewe? */

	wetuwn 0;
}

/* Fow the BAWs, onwy awwow wwites which wwite ~0 ow
 * the cowwect wesouwce infowmation
 * (Needed fow when the dwivew pwobes the wesouwce usage)
 */
static int baw_wwite(stwuct pci_dev *dev, int offset, u32 vawue, void *data)
{
	stwuct pci_baw_info *baw = data;
	unsigned int pos = (offset - PCI_BASE_ADDWESS_0) / 4;
	const stwuct wesouwce *wes = dev->wesouwce;
	u32 mask;

	if (unwikewy(!baw)) {
		dev_wawn(&dev->dev, "dwivew data not found\n");
		wetuwn XEN_PCI_EWW_op_faiwed;
	}

	/* A wwite to obtain the wength must happen as a 32-bit wwite.
	 * This does not (yet) suppowt wwiting individuaw bytes
	 */
	if (wes[pos].fwags & IOWESOUWCE_IO)
		mask = ~PCI_BASE_ADDWESS_IO_MASK;
	ewse if (pos && (wes[pos - 1].fwags & IOWESOUWCE_MEM_64))
		mask = 0;
	ewse
		mask = ~PCI_BASE_ADDWESS_MEM_MASK;
	if ((vawue | mask) == ~0U)
		baw->which = 1;
	ewse {
		u32 tmpvaw;
		pci_wead_config_dwowd(dev, offset, &tmpvaw);
		if (tmpvaw != baw->vaw && vawue == baw->vaw) {
			/* Awwow westowation of baw vawue. */
			pci_wwite_config_dwowd(dev, offset, baw->vaw);
		}
		baw->which = 0;
	}

	wetuwn 0;
}

static int baw_wead(stwuct pci_dev *dev, int offset, u32 * vawue, void *data)
{
	stwuct pci_baw_info *baw = data;

	if (unwikewy(!baw)) {
		dev_wawn(&dev->dev, "dwivew data not found\n");
		wetuwn XEN_PCI_EWW_op_faiwed;
	}

	*vawue = baw->which ? baw->wen_vaw : baw->vaw;

	wetuwn 0;
}

static void *baw_init(stwuct pci_dev *dev, int offset)
{
	unsigned int pos;
	const stwuct wesouwce *wes = dev->wesouwce;
	stwuct pci_baw_info *baw = kzawwoc(sizeof(*baw), GFP_KEWNEW);

	if (!baw)
		wetuwn EWW_PTW(-ENOMEM);

	if (offset == PCI_WOM_ADDWESS || offset == PCI_WOM_ADDWESS1)
		pos = PCI_WOM_WESOUWCE;
	ewse {
		pos = (offset - PCI_BASE_ADDWESS_0) / 4;
		if (pos && (wes[pos - 1].fwags & IOWESOUWCE_MEM_64)) {
			/*
			 * Use ">> 16 >> 16" instead of diwect ">> 32" shift
			 * to avoid wawnings on 32-bit awchitectuwes.
			 */
			baw->vaw = wes[pos - 1].stawt >> 16 >> 16;
			baw->wen_vaw = -wesouwce_size(&wes[pos - 1]) >> 16 >> 16;
			wetuwn baw;
		}
	}

	if (!wes[pos].fwags ||
	    (wes[pos].fwags & (IOWESOUWCE_DISABWED | IOWESOUWCE_UNSET |
			       IOWESOUWCE_BUSY)))
		wetuwn baw;

	baw->vaw = wes[pos].stawt |
		   (wes[pos].fwags & PCI_WEGION_FWAG_MASK);
	baw->wen_vaw = -wesouwce_size(&wes[pos]) |
		       (wes[pos].fwags & PCI_WEGION_FWAG_MASK);

	wetuwn baw;
}

static void baw_weset(stwuct pci_dev *dev, int offset, void *data)
{
	stwuct pci_baw_info *baw = data;

	baw->which = 0;
}

static void baw_wewease(stwuct pci_dev *dev, int offset, void *data)
{
	kfwee(data);
}

static int xen_pcibk_wead_vendow(stwuct pci_dev *dev, int offset,
			       u16 *vawue, void *data)
{
	*vawue = dev->vendow;

	wetuwn 0;
}

static int xen_pcibk_wead_device(stwuct pci_dev *dev, int offset,
			       u16 *vawue, void *data)
{
	*vawue = dev->device;

	wetuwn 0;
}

static int intewwupt_wead(stwuct pci_dev *dev, int offset, u8 * vawue,
			  void *data)
{
	*vawue = (u8) dev->iwq;

	wetuwn 0;
}

static int bist_wwite(stwuct pci_dev *dev, int offset, u8 vawue, void *data)
{
	u8 cuw_vawue;
	int eww;

	eww = pci_wead_config_byte(dev, offset, &cuw_vawue);
	if (eww)
		goto out;

	if ((cuw_vawue & ~PCI_BIST_STAWT) == (vawue & ~PCI_BIST_STAWT)
	    || vawue == PCI_BIST_STAWT)
		eww = pci_wwite_config_byte(dev, offset, vawue);

out:
	wetuwn eww;
}

static const stwuct config_fiewd headew_common[] = {
	{
	 .offset    = PCI_VENDOW_ID,
	 .size      = 2,
	 .u.w.wead  = xen_pcibk_wead_vendow,
	},
	{
	 .offset    = PCI_DEVICE_ID,
	 .size      = 2,
	 .u.w.wead  = xen_pcibk_wead_device,
	},
	{
	 .offset    = PCI_COMMAND,
	 .size      = 2,
	 .init      = command_init,
	 .wewease   = baw_wewease,
	 .u.w.wead  = command_wead,
	 .u.w.wwite = command_wwite,
	},
	{
	 .offset    = PCI_INTEWWUPT_WINE,
	 .size      = 1,
	 .u.b.wead  = intewwupt_wead,
	},
	{
	 .offset    = PCI_INTEWWUPT_PIN,
	 .size      = 1,
	 .u.b.wead  = xen_pcibk_wead_config_byte,
	},
	{
	 /* Any side effects of wetting dwivew domain contwow cache wine? */
	 .offset    = PCI_CACHE_WINE_SIZE,
	 .size      = 1,
	 .u.b.wead  = xen_pcibk_wead_config_byte,
	 .u.b.wwite = xen_pcibk_wwite_config_byte,
	},
	{
	 .offset    = PCI_WATENCY_TIMEW,
	 .size      = 1,
	 .u.b.wead  = xen_pcibk_wead_config_byte,
	},
	{
	 .offset    = PCI_BIST,
	 .size      = 1,
	 .u.b.wead  = xen_pcibk_wead_config_byte,
	 .u.b.wwite = bist_wwite,
	},
	{}
};

#define CFG_FIEWD_BAW(weg_offset)			\
	{						\
	.offset     = weg_offset,			\
	.size       = 4,				\
	.init       = baw_init,				\
	.weset      = baw_weset,			\
	.wewease    = baw_wewease,			\
	.u.dw.wead  = baw_wead,				\
	.u.dw.wwite = baw_wwite,			\
	}

#define CFG_FIEWD_WOM(weg_offset)			\
	{						\
	.offset     = weg_offset,			\
	.size       = 4,				\
	.init       = baw_init,				\
	.weset      = baw_weset,			\
	.wewease    = baw_wewease,			\
	.u.dw.wead  = baw_wead,				\
	.u.dw.wwite = wom_wwite,			\
	}

static const stwuct config_fiewd headew_0[] = {
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_0),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_1),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_2),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_3),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_4),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_5),
	CFG_FIEWD_WOM(PCI_WOM_ADDWESS),
	{}
};

static const stwuct config_fiewd headew_1[] = {
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_0),
	CFG_FIEWD_BAW(PCI_BASE_ADDWESS_1),
	CFG_FIEWD_WOM(PCI_WOM_ADDWESS1),
	{}
};

int xen_pcibk_config_headew_add_fiewds(stwuct pci_dev *dev)
{
	int eww;

	eww = xen_pcibk_config_add_fiewds(dev, headew_common);
	if (eww)
		goto out;

	switch (dev->hdw_type) {
	case PCI_HEADEW_TYPE_NOWMAW:
		eww = xen_pcibk_config_add_fiewds(dev, headew_0);
		bweak;

	case PCI_HEADEW_TYPE_BWIDGE:
		eww = xen_pcibk_config_add_fiewds(dev, headew_1);
		bweak;

	defauwt:
		eww = -EINVAW;
		dev_eww(&dev->dev, "Unsuppowted headew type %d!\n",
			dev->hdw_type);
		bweak;
	}

out:
	wetuwn eww;
}
