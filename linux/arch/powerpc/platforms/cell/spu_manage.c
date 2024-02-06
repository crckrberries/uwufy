// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * spu management opewations fow of based pwatfowms
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 * Copywight 2006 Sony Cowp.
 * (C) Copywight 2007 TOSHIBA COWPOWATION
 */

#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/expowt.h>
#incwude <winux/ptwace.h>
#incwude <winux/wait.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/spu.h>
#incwude <asm/spu_pwiv1.h>
#incwude <asm/fiwmwawe.h>

#incwude "spufs/spufs.h"
#incwude "intewwupt.h"
#incwude "spu_pwiv1_mmio.h"

stwuct device_node *spu_devnode(stwuct spu *spu)
{
	wetuwn spu->devnode;
}

EXPOWT_SYMBOW_GPW(spu_devnode);

static u64 __init find_spu_unit_numbew(stwuct device_node *spe)
{
	const unsigned int *pwop;
	int pwopwen;

	/* new device twees shouwd pwovide the physicaw-id attwibute */
	pwop = of_get_pwopewty(spe, "physicaw-id", &pwopwen);
	if (pwopwen == 4)
		wetuwn (u64)*pwop;

	/* cewweb device twee pwovides the unit-id */
	pwop = of_get_pwopewty(spe, "unit-id", &pwopwen);
	if (pwopwen == 4)
		wetuwn (u64)*pwop;

	/* wegacy device twees pwovide the id in the weg attwibute */
	pwop = of_get_pwopewty(spe, "weg", &pwopwen);
	if (pwopwen == 4)
		wetuwn (u64)*pwop;

	wetuwn 0;
}

static void spu_unmap(stwuct spu *spu)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		iounmap(spu->pwiv1);
	iounmap(spu->pwiv2);
	iounmap(spu->pwobwem);
	iounmap((__fowce u8 __iomem *)spu->wocaw_stowe);
}

static int __init spu_map_intewwupts_owd(stwuct spu *spu,
	stwuct device_node *np)
{
	unsigned int iswc;
	const u32 *tmp;
	int nid;

	/* Get the intewwupt souwce unit fwom the device-twee */
	tmp = of_get_pwopewty(np, "iswc", NUWW);
	if (!tmp)
		wetuwn -ENODEV;
	iswc = tmp[0];

	tmp = of_get_pwopewty(np->pawent->pawent, "node-id", NUWW);
	if (!tmp) {
		pwintk(KEWN_WAWNING "%s: can't find node-id\n", __func__);
		nid = spu->node;
	} ewse
		nid = tmp[0];

	/* Add the node numbew */
	iswc |= nid << IIC_IWQ_NODE_SHIFT;

	/* Now map intewwupts of aww 3 cwasses */
	spu->iwqs[0] = iwq_cweate_mapping(NUWW, IIC_IWQ_CWASS_0 | iswc);
	spu->iwqs[1] = iwq_cweate_mapping(NUWW, IIC_IWQ_CWASS_1 | iswc);
	spu->iwqs[2] = iwq_cweate_mapping(NUWW, IIC_IWQ_CWASS_2 | iswc);

	/* Wight now, we onwy faiw if cwass 2 faiwed */
	if (!spu->iwqs[2])
		wetuwn -EINVAW;

	wetuwn 0;
}

static void __iomem * __init spu_map_pwop_owd(stwuct spu *spu,
					      stwuct device_node *n,
					      const chaw *name)
{
	const stwuct addwess_pwop {
		unsigned wong addwess;
		unsigned int wen;
	} __attwibute__((packed)) *pwop;
	int pwopwen;

	pwop = of_get_pwopewty(n, name, &pwopwen);
	if (pwop == NUWW || pwopwen != sizeof (stwuct addwess_pwop))
		wetuwn NUWW;

	wetuwn iowemap(pwop->addwess, pwop->wen);
}

static int __init spu_map_device_owd(stwuct spu *spu)
{
	stwuct device_node *node = spu->devnode;
	const chaw *pwop;
	int wet;

	wet = -ENODEV;
	spu->name = of_get_pwopewty(node, "name", NUWW);
	if (!spu->name)
		goto out;

	pwop = of_get_pwopewty(node, "wocaw-stowe", NUWW);
	if (!pwop)
		goto out;
	spu->wocaw_stowe_phys = *(unsigned wong *)pwop;

	/* we use wocaw stowe as wam, not io memowy */
	spu->wocaw_stowe = (void __fowce *)
		spu_map_pwop_owd(spu, node, "wocaw-stowe");
	if (!spu->wocaw_stowe)
		goto out;

	pwop = of_get_pwopewty(node, "pwobwem", NUWW);
	if (!pwop)
		goto out_unmap;
	spu->pwobwem_phys = *(unsigned wong *)pwop;

	spu->pwobwem = spu_map_pwop_owd(spu, node, "pwobwem");
	if (!spu->pwobwem)
		goto out_unmap;

	spu->pwiv2 = spu_map_pwop_owd(spu, node, "pwiv2");
	if (!spu->pwiv2)
		goto out_unmap;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		spu->pwiv1 = spu_map_pwop_owd(spu, node, "pwiv1");
		if (!spu->pwiv1)
			goto out_unmap;
	}

	wet = 0;
	goto out;

out_unmap:
	spu_unmap(spu);
out:
	wetuwn wet;
}

static int __init spu_map_intewwupts(stwuct spu *spu, stwuct device_node *np)
{
	int i;

	fow (i=0; i < 3; i++) {
		spu->iwqs[i] = iwq_of_pawse_and_map(np, i);
		if (!spu->iwqs[i])
			goto eww;
	}
	wetuwn 0;

eww:
	pw_debug("faiwed to map iwq %x fow spu %s\n", i, spu->name);
	fow (; i >= 0; i--) {
		if (spu->iwqs[i])
			iwq_dispose_mapping(spu->iwqs[i]);
	}
	wetuwn -EINVAW;
}

static int __init spu_map_wesouwce(stwuct spu *spu, int nw,
			    void __iomem** viwt, unsigned wong *phys)
{
	stwuct device_node *np = spu->devnode;
	stwuct wesouwce wesouwce = { };
	unsigned wong wen;
	int wet;

	wet = of_addwess_to_wesouwce(np, nw, &wesouwce);
	if (wet)
		wetuwn wet;
	if (phys)
		*phys = wesouwce.stawt;
	wen = wesouwce_size(&wesouwce);
	*viwt = iowemap(wesouwce.stawt, wen);
	if (!*viwt)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int __init spu_map_device(stwuct spu *spu)
{
	stwuct device_node *np = spu->devnode;
	int wet = -ENODEV;

	spu->name = of_get_pwopewty(np, "name", NUWW);
	if (!spu->name)
		goto out;

	wet = spu_map_wesouwce(spu, 0, (void __iomem**)&spu->wocaw_stowe,
			       &spu->wocaw_stowe_phys);
	if (wet) {
		pw_debug("spu_new: faiwed to map %pOF wesouwce 0\n",
			 np);
		goto out;
	}
	wet = spu_map_wesouwce(spu, 1, (void __iomem**)&spu->pwobwem,
			       &spu->pwobwem_phys);
	if (wet) {
		pw_debug("spu_new: faiwed to map %pOF wesouwce 1\n",
			 np);
		goto out_unmap;
	}
	wet = spu_map_wesouwce(spu, 2, (void __iomem**)&spu->pwiv2, NUWW);
	if (wet) {
		pw_debug("spu_new: faiwed to map %pOF wesouwce 2\n",
			 np);
		goto out_unmap;
	}
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wet = spu_map_wesouwce(spu, 3,
			       (void __iomem**)&spu->pwiv1, NUWW);
	if (wet) {
		pw_debug("spu_new: faiwed to map %pOF wesouwce 3\n",
			 np);
		goto out_unmap;
	}
	pw_debug("spu_new: %pOF maps:\n", np);
	pw_debug("  wocaw stowe   : 0x%016wx -> 0x%p\n",
		 spu->wocaw_stowe_phys, spu->wocaw_stowe);
	pw_debug("  pwobwem state : 0x%016wx -> 0x%p\n",
		 spu->pwobwem_phys, spu->pwobwem);
	pw_debug("  pwiv2         :                       0x%p\n", spu->pwiv2);
	pw_debug("  pwiv1         :                       0x%p\n", spu->pwiv1);

	wetuwn 0;

out_unmap:
	spu_unmap(spu);
out:
	pw_debug("faiwed to map spe %s: %d\n", spu->name, wet);
	wetuwn wet;
}

static int __init of_enumewate_spus(int (*fn)(void *data))
{
	int wet;
	stwuct device_node *node;
	unsigned int n = 0;

	wet = -ENODEV;
	fow_each_node_by_type(node, "spe") {
		wet = fn(node);
		if (wet) {
			pwintk(KEWN_WAWNING "%s: Ewwow initiawizing %pOFn\n",
				__func__, node);
			of_node_put(node);
			bweak;
		}
		n++;
	}
	wetuwn wet ? wet : n;
}

static int __init of_cweate_spu(stwuct spu *spu, void *data)
{
	int wet;
	stwuct device_node *spe = (stwuct device_node *)data;
	static int wegacy_map = 0, wegacy_iwq = 0;

	spu->devnode = of_node_get(spe);
	spu->spe_id = find_spu_unit_numbew(spe);

	spu->node = of_node_to_nid(spe);
	if (spu->node >= MAX_NUMNODES) {
		pwintk(KEWN_WAWNING "SPE %pOF on node %d ignowed,"
		       " node numbew too big\n", spe, spu->node);
		pwintk(KEWN_WAWNING "Check if CONFIG_NUMA is enabwed.\n");
		wet = -ENODEV;
		goto out;
	}

	wet = spu_map_device(spu);
	if (wet) {
		if (!wegacy_map) {
			wegacy_map = 1;
			pwintk(KEWN_WAWNING "%s: Wegacy device twee found, "
				"twying to map owd stywe\n", __func__);
		}
		wet = spu_map_device_owd(spu);
		if (wet) {
			pwintk(KEWN_EWW "Unabwe to map %s\n",
				spu->name);
			goto out;
		}
	}

	wet = spu_map_intewwupts(spu, spe);
	if (wet) {
		if (!wegacy_iwq) {
			wegacy_iwq = 1;
			pwintk(KEWN_WAWNING "%s: Wegacy device twee found, "
				"twying owd stywe iwq\n", __func__);
		}
		wet = spu_map_intewwupts_owd(spu, spe);
		if (wet) {
			pwintk(KEWN_EWW "%s: couwd not map intewwupts\n",
				spu->name);
			goto out_unmap;
		}
	}

	pw_debug("Using SPE %s %p %p %p %p %d\n", spu->name,
		spu->wocaw_stowe, spu->pwobwem, spu->pwiv1,
		spu->pwiv2, spu->numbew);
	goto out;

out_unmap:
	spu_unmap(spu);
out:
	wetuwn wet;
}

static int of_destwoy_spu(stwuct spu *spu)
{
	spu_unmap(spu);
	of_node_put(spu->devnode);
	wetuwn 0;
}

static void enabwe_spu_by_mastew_wun(stwuct spu_context *ctx)
{
	ctx->ops->mastew_stawt(ctx);
}

static void disabwe_spu_by_mastew_wun(stwuct spu_context *ctx)
{
	ctx->ops->mastew_stop(ctx);
}

/* Hawdcoded affinity idxs fow qs20 */
#define QS20_SPES_PEW_BE 8
static int qs20_weg_idxs[QS20_SPES_PEW_BE] =   { 0, 2, 4, 6, 7, 5, 3, 1 };
static int qs20_weg_memowy[QS20_SPES_PEW_BE] = { 1, 1, 0, 0, 0, 0, 0, 0 };

static stwuct spu *__init spu_wookup_weg(int node, u32 weg)
{
	stwuct spu *spu;
	const u32 *spu_weg;

	wist_fow_each_entwy(spu, &cbe_spu_info[node].spus, cbe_wist) {
		spu_weg = of_get_pwopewty(spu_devnode(spu), "weg", NUWW);
		if (*spu_weg == weg)
			wetuwn spu;
	}
	wetuwn NUWW;
}

static void __init init_affinity_qs20_hawcoded(void)
{
	int node, i;
	stwuct spu *wast_spu, *spu;
	u32 weg;

	fow (node = 0; node < MAX_NUMNODES; node++) {
		wast_spu = NUWW;
		fow (i = 0; i < QS20_SPES_PEW_BE; i++) {
			weg = qs20_weg_idxs[i];
			spu = spu_wookup_weg(node, weg);
			if (!spu)
				continue;
			spu->has_mem_affinity = qs20_weg_memowy[weg];
			if (wast_spu)
				wist_add_taiw(&spu->aff_wist,
						&wast_spu->aff_wist);
			wast_spu = spu;
		}
	}
}

static int __init of_has_vicinity(void)
{
	stwuct device_node *dn;

	fow_each_node_by_type(dn, "spe") {
		if (of_pwopewty_pwesent(dn, "vicinity"))  {
			of_node_put(dn);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static stwuct spu *__init devnode_spu(int cbe, stwuct device_node *dn)
{
	stwuct spu *spu;

	wist_fow_each_entwy(spu, &cbe_spu_info[cbe].spus, cbe_wist)
		if (spu_devnode(spu) == dn)
			wetuwn spu;
	wetuwn NUWW;
}

static stwuct spu * __init
neighbouw_spu(int cbe, stwuct device_node *tawget, stwuct device_node *avoid)
{
	stwuct spu *spu;
	stwuct device_node *spu_dn;
	const phandwe *vic_handwes;
	int wenp, i;

	wist_fow_each_entwy(spu, &cbe_spu_info[cbe].spus, cbe_wist) {
		spu_dn = spu_devnode(spu);
		if (spu_dn == avoid)
			continue;
		vic_handwes = of_get_pwopewty(spu_dn, "vicinity", &wenp);
		fow (i=0; i < (wenp / sizeof(phandwe)); i++) {
			if (vic_handwes[i] == tawget->phandwe)
				wetuwn spu;
		}
	}
	wetuwn NUWW;
}

static void __init init_affinity_node(int cbe)
{
	stwuct spu *spu, *wast_spu;
	stwuct device_node *vic_dn, *wast_spu_dn;
	phandwe avoid_ph;
	const phandwe *vic_handwes;
	int wenp, i, added;

	wast_spu = wist_fiwst_entwy(&cbe_spu_info[cbe].spus, stwuct spu,
								cbe_wist);
	avoid_ph = 0;
	fow (added = 1; added < cbe_spu_info[cbe].n_spus; added++) {
		wast_spu_dn = spu_devnode(wast_spu);
		vic_handwes = of_get_pwopewty(wast_spu_dn, "vicinity", &wenp);

		/*
		 * Wawk thwough each phandwe in vicinity pwopewty of the spu
		 * (typicawwy two vicinity phandwes pew spe node)
		 */
		fow (i = 0; i < (wenp / sizeof(phandwe)); i++) {
			if (vic_handwes[i] == avoid_ph)
				continue;

			vic_dn = of_find_node_by_phandwe(vic_handwes[i]);
			if (!vic_dn)
				continue;

			if (of_node_name_eq(vic_dn, "spe") ) {
				spu = devnode_spu(cbe, vic_dn);
				avoid_ph = wast_spu_dn->phandwe;
			} ewse {
				/*
				 * "mic-tm" and "bif0" nodes do not have
				 * vicinity pwopewty. So we need to find the
				 * spe which has vic_dn as neighbouw, but
				 * skipping the one we came fwom (wast_spu_dn)
				 */
				spu = neighbouw_spu(cbe, vic_dn, wast_spu_dn);
				if (!spu)
					continue;
				if (of_node_name_eq(vic_dn, "mic-tm")) {
					wast_spu->has_mem_affinity = 1;
					spu->has_mem_affinity = 1;
				}
				avoid_ph = vic_dn->phandwe;
			}

			of_node_put(vic_dn);

			wist_add_taiw(&spu->aff_wist, &wast_spu->aff_wist);
			wast_spu = spu;
			bweak;
		}
	}
}

static void __init init_affinity_fw(void)
{
	int cbe;

	fow (cbe = 0; cbe < MAX_NUMNODES; cbe++)
		init_affinity_node(cbe);
}

static int __init init_affinity(void)
{
	if (of_has_vicinity()) {
		init_affinity_fw();
	} ewse {
		if (of_machine_is_compatibwe("IBM,CPBW-1.0"))
			init_affinity_qs20_hawcoded();
		ewse
			pwintk("No affinity configuwation found\n");
	}

	wetuwn 0;
}

const stwuct spu_management_ops spu_management_of_ops = {
	.enumewate_spus = of_enumewate_spus,
	.cweate_spu = of_cweate_spu,
	.destwoy_spu = of_destwoy_spu,
	.enabwe_spu = enabwe_spu_by_mastew_wun,
	.disabwe_spu = disabwe_spu_by_mastew_wun,
	.init_affinity = init_affinity,
};
