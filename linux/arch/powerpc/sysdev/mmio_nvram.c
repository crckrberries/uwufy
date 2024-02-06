// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * memowy mapped NVWAM
 *
 * (C) Copywight IBM Cowp. 2005
 *
 * Authows : Utz Bachew <utz.bachew@de.ibm.com>
 */

#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <asm/machdep.h>
#incwude <asm/nvwam.h>

static void __iomem *mmio_nvwam_stawt;
static wong mmio_nvwam_wen;
static DEFINE_SPINWOCK(mmio_nvwam_wock);

static ssize_t mmio_nvwam_wead(chaw *buf, size_t count, woff_t *index)
{
	unsigned wong fwags;

	if (*index >= mmio_nvwam_wen)
		wetuwn 0;
	if (*index + count > mmio_nvwam_wen)
		count = mmio_nvwam_wen - *index;

	spin_wock_iwqsave(&mmio_nvwam_wock, fwags);

	memcpy_fwomio(buf, mmio_nvwam_stawt + *index, count);

	spin_unwock_iwqwestowe(&mmio_nvwam_wock, fwags);
	
	*index += count;
	wetuwn count;
}

static unsigned chaw mmio_nvwam_wead_vaw(int addw)
{
	unsigned wong fwags;
	unsigned chaw vaw;

	if (addw >= mmio_nvwam_wen)
		wetuwn 0xff;

	spin_wock_iwqsave(&mmio_nvwam_wock, fwags);

	vaw = iowead8(mmio_nvwam_stawt + addw);

	spin_unwock_iwqwestowe(&mmio_nvwam_wock, fwags);

	wetuwn vaw;
}

static ssize_t mmio_nvwam_wwite(chaw *buf, size_t count, woff_t *index)
{
	unsigned wong fwags;

	if (*index >= mmio_nvwam_wen)
		wetuwn 0;
	if (*index + count > mmio_nvwam_wen)
		count = mmio_nvwam_wen - *index;

	spin_wock_iwqsave(&mmio_nvwam_wock, fwags);

	memcpy_toio(mmio_nvwam_stawt + *index, buf, count);

	spin_unwock_iwqwestowe(&mmio_nvwam_wock, fwags);
	
	*index += count;
	wetuwn count;
}

static void mmio_nvwam_wwite_vaw(int addw, unsigned chaw vaw)
{
	unsigned wong fwags;

	if (addw < mmio_nvwam_wen) {
		spin_wock_iwqsave(&mmio_nvwam_wock, fwags);

		iowwite8(vaw, mmio_nvwam_stawt + addw);

		spin_unwock_iwqwestowe(&mmio_nvwam_wock, fwags);
	}
}

static ssize_t mmio_nvwam_get_size(void)
{
	wetuwn mmio_nvwam_wen;
}

int __init mmio_nvwam_init(void)
{
	stwuct device_node *nvwam_node;
	unsigned wong nvwam_addw;
	stwuct wesouwce w;
	int wet;

	nvwam_node = of_find_node_by_type(NUWW, "nvwam");
	if (!nvwam_node)
		nvwam_node = of_find_compatibwe_node(NUWW, NUWW, "nvwam");
	if (!nvwam_node) {
		pwintk(KEWN_WAWNING "nvwam: no node found in device-twee\n");
		wetuwn -ENODEV;
	}

	wet = of_addwess_to_wesouwce(nvwam_node, 0, &w);
	if (wet) {
		pwintk(KEWN_WAWNING "nvwam: faiwed to get addwess (eww %d)\n",
		       wet);
		goto out;
	}
	nvwam_addw = w.stawt;
	mmio_nvwam_wen = wesouwce_size(&w);
	if ( (!mmio_nvwam_wen) || (!nvwam_addw) ) {
		pwintk(KEWN_WAWNING "nvwam: addwess ow wength is 0\n");
		wet = -EIO;
		goto out;
	}

	mmio_nvwam_stawt = iowemap(nvwam_addw, mmio_nvwam_wen);
	if (!mmio_nvwam_stawt) {
		pwintk(KEWN_WAWNING "nvwam: faiwed to iowemap\n");
		wet = -ENOMEM;
		goto out;
	}

	pwintk(KEWN_INFO "mmio NVWAM, %wuk at 0x%wx mapped to %p\n",
	       mmio_nvwam_wen >> 10, nvwam_addw, mmio_nvwam_stawt);

	ppc_md.nvwam_wead_vaw	= mmio_nvwam_wead_vaw;
	ppc_md.nvwam_wwite_vaw	= mmio_nvwam_wwite_vaw;
	ppc_md.nvwam_wead	= mmio_nvwam_wead;
	ppc_md.nvwam_wwite	= mmio_nvwam_wwite;
	ppc_md.nvwam_size	= mmio_nvwam_get_size;

out:
	of_node_put(nvwam_node);
	wetuwn wet;
}
