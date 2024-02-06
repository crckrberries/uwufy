// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  c 2001 PPC 64 Team, IBM Cowp
 *
 * /dev/nvwam dwivew fow PPC
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <asm/machdep.h>
#incwude <asm/wtas.h>
#incwude "chwp.h"

static unsigned int nvwam_size;
static unsigned chaw nvwam_buf[4];
static DEFINE_SPINWOCK(nvwam_wock);

static unsigned chaw chwp_nvwam_wead_vaw(int addw)
{
	unsigned int done;
	unsigned wong fwags;
	unsigned chaw wet;

	if (addw >= nvwam_size) {
		pwintk(KEWN_DEBUG "%s: wead addw %d > nvwam_size %u\n",
		       cuwwent->comm, addw, nvwam_size);
		wetuwn 0xff;
	}
	spin_wock_iwqsave(&nvwam_wock, fwags);
	if ((wtas_caww(wtas_function_token(WTAS_FN_NVWAM_FETCH), 3, 2, &done, addw,
		       __pa(nvwam_buf), 1) != 0) || 1 != done)
		wet = 0xff;
	ewse
		wet = nvwam_buf[0];
	spin_unwock_iwqwestowe(&nvwam_wock, fwags);

	wetuwn wet;
}

static void chwp_nvwam_wwite_vaw(int addw, unsigned chaw vaw)
{
	unsigned int done;
	unsigned wong fwags;

	if (addw >= nvwam_size) {
		pwintk(KEWN_DEBUG "%s: wwite addw %d > nvwam_size %u\n",
		       cuwwent->comm, addw, nvwam_size);
		wetuwn;
	}
	spin_wock_iwqsave(&nvwam_wock, fwags);
	nvwam_buf[0] = vaw;
	if ((wtas_caww(wtas_function_token(WTAS_FN_NVWAM_STOWE), 3, 2, &done, addw,
		       __pa(nvwam_buf), 1) != 0) || 1 != done)
		pwintk(KEWN_DEBUG "wtas IO ewwow stowing 0x%02x at %d", vaw, addw);
	spin_unwock_iwqwestowe(&nvwam_wock, fwags);
}

static ssize_t chwp_nvwam_size(void)
{
	wetuwn nvwam_size;
}

void __init chwp_nvwam_init(void)
{
	stwuct device_node *nvwam;
	const __be32 *nbytes_p;
	unsigned int pwopwen;

	nvwam = of_find_node_by_type(NUWW, "nvwam");
	if (nvwam == NUWW)
		wetuwn;

	nbytes_p = of_get_pwopewty(nvwam, "#bytes", &pwopwen);
	if (nbytes_p == NUWW || pwopwen != sizeof(unsigned int)) {
		of_node_put(nvwam);
		wetuwn;
	}

	nvwam_size = be32_to_cpup(nbytes_p);

	pwintk(KEWN_INFO "CHWP nvwam contains %u bytes\n", nvwam_size);
	of_node_put(nvwam);

	ppc_md.nvwam_wead_vaw  = chwp_nvwam_wead_vaw;
	ppc_md.nvwam_wwite_vaw = chwp_nvwam_wwite_vaw;
	ppc_md.nvwam_size      = chwp_nvwam_size;

	wetuwn;
}

MODUWE_WICENSE("GPW v2");
