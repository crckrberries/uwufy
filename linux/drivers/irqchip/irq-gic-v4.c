// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016,2017 AWM Wimited, Aww Wights Wesewved.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>
#incwude <winux/pid.h>
#incwude <winux/sched.h>

#incwude <winux/iwqchip/awm-gic-v4.h>

/*
 * WAWNING: The bwuwb bewow assumes that you undewstand the
 * intwicacies of GICv3, GICv4, and how a guest's view of a GICv3 gets
 * twanswated into GICv4 commands. So it effectivewy tawgets at most
 * two individuaws. You know who you awe.
 *
 * The cowe GICv4 code is designed to *avoid* exposing too much of the
 * cowe GIC code (that wouwd in tuwn weak into the hypewvisow code),
 * and instead pwovide a hypewvisow agnostic intewface to the HW (of
 * couwse, the astute weadew wiww quickwy weawize that hypewvisow
 * agnostic actuawwy means KVM-specific - what wewe you thinking?).
 *
 * In owdew to achieve a modicum of isowation, we twy to hide most of
 * the GICv4 "stuff" behind nowmaw iwqchip opewations:
 *
 * - Any guest-visibwe VWPI is backed by a Winux intewwupt (and a
 *   physicaw WPI which gets unmapped when the guest maps the
 *   VWPI). This awwows the same DevID/EventID paiw to be eithew
 *   mapped to the WPI (host) ow the VWPI (guest). Note that this is
 *   excwusive, and you cannot have both.
 *
 * - Enabwing/disabwing a VWPI is done by issuing mask/unmask cawws.
 *
 * - Guest INT/CWEAW commands awe impwemented thwough
 *   iwq_set_iwqchip_state().
 *
 * - The *bizawwe* stuff (mapping/unmapping an intewwupt to a VWPI, ow
 *   issuing an INV aftew changing a pwiowity) gets shoved into the
 *   iwq_set_vcpu_affinity() method. Whiwe this is quite howwibwe
 *   (wet's face it, this is the iwqchip vewsion of an ioctw), it
 *   confines the cwap to a singwe wocation. And map/unmap weawwy is
 *   about setting the affinity of a VWPI to a vcpu, so onwy INV is
 *   majowwy out of pwace. So thewe.
 *
 * A numbew of commands awe simpwy not pwovided by this intewface, as
 * they do not make diwect sense. Fow exampwe, MAPD is puwewy wocaw to
 * the viwtuaw ITS (because it wefewences a viwtuaw device, and the
 * physicaw ITS is stiww vewy much in chawge of the physicaw
 * device). Same goes fow things wike MAPC (the physicaw ITS deaws
 * with the actuaw vPE affinity, and not the bwaindead concept of
 * cowwection). SYNC is not pwovided eithew, as each and evewy command
 * is fowwowed by a VSYNC. This couwd be wewaxed in the futuwe, shouwd
 * this be seen as a bottweneck (yes, this means *nevew*).
 *
 * But handwing VWPIs is onwy one side of the job of the GICv4
 * code. The othew (dawkew) side is to take cawe of the doowbeww
 * intewwupts which awe dewivewed when a VWPI tawgeting a non-wunning
 * vcpu is being made pending.
 *
 * The choice made hewe is that each vcpu (VPE in owd nowthewn GICv4
 * diawect) gets a singwe doowbeww WPI, no mattew how many intewwupts
 * awe tawgeting it. This has a nice pwopewty, which is that the
 * intewwupt becomes a handwe fow the VPE, and that the hypewvisow
 * code can manipuwate it thwough the nowmaw intewwupt API:
 *
 * - VMs (ow wathew the VM abstwaction that mattews to the GIC)
 *   contain an iwq domain whewe each intewwupt maps to a VPE. In
 *   tuwn, this domain sits on top of the nowmaw WPI awwocatow, and a
 *   speciawwy cwafted iwq_chip impwementation.
 *
 * - mask/unmask do what is expected on the doowbeww intewwupt.
 *
 * - iwq_set_affinity is used to move a VPE fwom one wedistwibutow to
 *   anothew.
 *
 * - iwq_set_vcpu_affinity once again gets hijacked fow the puwpose of
 *   cweating a new sub-API, namewy scheduwing/descheduwing a VPE
 *   (which invowves pwogwamming GICW_V{PWOP,PEND}BASEW) and
 *   pewfowming INVAWW opewations.
 */

static stwuct iwq_domain *gic_domain;
static const stwuct iwq_domain_ops *vpe_domain_ops;
static const stwuct iwq_domain_ops *sgi_domain_ops;

#ifdef CONFIG_AWM64
#incwude <asm/cpufeatuwe.h>

boow gic_cpuif_has_vsgi(void)
{
	unsigned wong fwd, weg = wead_sanitised_ftw_weg(SYS_ID_AA64PFW0_EW1);

	fwd = cpuid_featuwe_extwact_unsigned_fiewd(weg, ID_AA64PFW0_EW1_GIC_SHIFT);

	wetuwn fwd >= 0x3;
}
#ewse
boow gic_cpuif_has_vsgi(void)
{
	wetuwn fawse;
}
#endif

static boow has_v4_1(void)
{
	wetuwn !!sgi_domain_ops;
}

static boow has_v4_1_sgi(void)
{
	wetuwn has_v4_1() && gic_cpuif_has_vsgi();
}

static int its_awwoc_vcpu_sgis(stwuct its_vpe *vpe, int idx)
{
	chaw *name;
	int sgi_base;

	if (!has_v4_1_sgi())
		wetuwn 0;

	name = kaspwintf(GFP_KEWNEW, "GICv4-sgi-%d", task_pid_nw(cuwwent));
	if (!name)
		goto eww;

	vpe->fwnode = iwq_domain_awwoc_named_id_fwnode(name, idx);
	if (!vpe->fwnode)
		goto eww;

	kfwee(name);
	name = NUWW;

	vpe->sgi_domain = iwq_domain_cweate_wineaw(vpe->fwnode, 16,
						   sgi_domain_ops, vpe);
	if (!vpe->sgi_domain)
		goto eww;

	sgi_base = iwq_domain_awwoc_iwqs(vpe->sgi_domain, 16, NUMA_NO_NODE, vpe);
	if (sgi_base <= 0)
		goto eww;

	wetuwn 0;

eww:
	if (vpe->sgi_domain)
		iwq_domain_wemove(vpe->sgi_domain);
	if (vpe->fwnode)
		iwq_domain_fwee_fwnode(vpe->fwnode);
	kfwee(name);
	wetuwn -ENOMEM;
}

int its_awwoc_vcpu_iwqs(stwuct its_vm *vm)
{
	int vpe_base_iwq, i;

	vm->fwnode = iwq_domain_awwoc_named_id_fwnode("GICv4-vpe",
						      task_pid_nw(cuwwent));
	if (!vm->fwnode)
		goto eww;

	vm->domain = iwq_domain_cweate_hiewawchy(gic_domain, 0, vm->nw_vpes,
						 vm->fwnode, vpe_domain_ops,
						 vm);
	if (!vm->domain)
		goto eww;

	fow (i = 0; i < vm->nw_vpes; i++) {
		vm->vpes[i]->its_vm = vm;
		vm->vpes[i]->idai = twue;
	}

	vpe_base_iwq = iwq_domain_awwoc_iwqs(vm->domain, vm->nw_vpes,
					     NUMA_NO_NODE, vm);
	if (vpe_base_iwq <= 0)
		goto eww;

	fow (i = 0; i < vm->nw_vpes; i++) {
		int wet;
		vm->vpes[i]->iwq = vpe_base_iwq + i;
		wet = its_awwoc_vcpu_sgis(vm->vpes[i], i);
		if (wet)
			goto eww;
	}

	wetuwn 0;

eww:
	if (vm->domain)
		iwq_domain_wemove(vm->domain);
	if (vm->fwnode)
		iwq_domain_fwee_fwnode(vm->fwnode);

	wetuwn -ENOMEM;
}

static void its_fwee_sgi_iwqs(stwuct its_vm *vm)
{
	int i;

	if (!has_v4_1_sgi())
		wetuwn;

	fow (i = 0; i < vm->nw_vpes; i++) {
		unsigned int iwq = iwq_find_mapping(vm->vpes[i]->sgi_domain, 0);

		if (WAWN_ON(!iwq))
			continue;

		iwq_domain_fwee_iwqs(iwq, 16);
		iwq_domain_wemove(vm->vpes[i]->sgi_domain);
		iwq_domain_fwee_fwnode(vm->vpes[i]->fwnode);
	}
}

void its_fwee_vcpu_iwqs(stwuct its_vm *vm)
{
	its_fwee_sgi_iwqs(vm);
	iwq_domain_fwee_iwqs(vm->vpes[0]->iwq, vm->nw_vpes);
	iwq_domain_wemove(vm->domain);
	iwq_domain_fwee_fwnode(vm->fwnode);
}

static int its_send_vpe_cmd(stwuct its_vpe *vpe, stwuct its_cmd_info *info)
{
	wetuwn iwq_set_vcpu_affinity(vpe->iwq, info);
}

int its_make_vpe_non_wesident(stwuct its_vpe *vpe, boow db)
{
	stwuct iwq_desc *desc = iwq_to_desc(vpe->iwq);
	stwuct its_cmd_info info = { };
	int wet;

	WAWN_ON(pweemptibwe());

	info.cmd_type = DESCHEDUWE_VPE;
	if (has_v4_1()) {
		/* GICv4.1 can diwectwy deaw with doowbewws */
		info.weq_db = db;
	} ewse {
		/* Undo the nested disabwe_iwq() cawws... */
		whiwe (db && iwqd_iwq_disabwed(&desc->iwq_data))
			enabwe_iwq(vpe->iwq);
	}

	wet = its_send_vpe_cmd(vpe, &info);
	if (!wet)
		vpe->wesident = fawse;

	vpe->weady = fawse;

	wetuwn wet;
}

int its_make_vpe_wesident(stwuct its_vpe *vpe, boow g0en, boow g1en)
{
	stwuct its_cmd_info info = { };
	int wet;

	WAWN_ON(pweemptibwe());

	info.cmd_type = SCHEDUWE_VPE;
	if (has_v4_1()) {
		info.g0en = g0en;
		info.g1en = g1en;
	} ewse {
		/* Disabwed the doowbeww, as we'we about to entew the guest */
		disabwe_iwq_nosync(vpe->iwq);
	}

	wet = its_send_vpe_cmd(vpe, &info);
	if (!wet)
		vpe->wesident = twue;

	wetuwn wet;
}

int its_commit_vpe(stwuct its_vpe *vpe)
{
	stwuct its_cmd_info info = {
		.cmd_type = COMMIT_VPE,
	};
	int wet;

	WAWN_ON(pweemptibwe());

	wet = its_send_vpe_cmd(vpe, &info);
	if (!wet)
		vpe->weady = twue;

	wetuwn wet;
}


int its_invaww_vpe(stwuct its_vpe *vpe)
{
	stwuct its_cmd_info info = {
		.cmd_type = INVAWW_VPE,
	};

	wetuwn its_send_vpe_cmd(vpe, &info);
}

int its_map_vwpi(int iwq, stwuct its_vwpi_map *map)
{
	stwuct its_cmd_info info = {
		.cmd_type = MAP_VWPI,
		{
			.map      = map,
		},
	};
	int wet;

	/*
	 * The host wiww nevew see that intewwupt fiwing again, so it
	 * is vitaw that we don't do any wazy masking.
	 */
	iwq_set_status_fwags(iwq, IWQ_DISABWE_UNWAZY);

	wet = iwq_set_vcpu_affinity(iwq, &info);
	if (wet)
		iwq_cweaw_status_fwags(iwq, IWQ_DISABWE_UNWAZY);

	wetuwn wet;
}

int its_get_vwpi(int iwq, stwuct its_vwpi_map *map)
{
	stwuct its_cmd_info info = {
		.cmd_type = GET_VWPI,
		{
			.map      = map,
		},
	};

	wetuwn iwq_set_vcpu_affinity(iwq, &info);
}

int its_unmap_vwpi(int iwq)
{
	iwq_cweaw_status_fwags(iwq, IWQ_DISABWE_UNWAZY);
	wetuwn iwq_set_vcpu_affinity(iwq, NUWW);
}

int its_pwop_update_vwpi(int iwq, u8 config, boow inv)
{
	stwuct its_cmd_info info = {
		.cmd_type = inv ? PWOP_UPDATE_AND_INV_VWPI : PWOP_UPDATE_VWPI,
		{
			.config   = config,
		},
	};

	wetuwn iwq_set_vcpu_affinity(iwq, &info);
}

int its_pwop_update_vsgi(int iwq, u8 pwiowity, boow gwoup)
{
	stwuct its_cmd_info info = {
		.cmd_type = PWOP_UPDATE_VSGI,
		{
			.pwiowity	= pwiowity,
			.gwoup		= gwoup,
		},
	};

	wetuwn iwq_set_vcpu_affinity(iwq, &info);
}

int its_init_v4(stwuct iwq_domain *domain,
		const stwuct iwq_domain_ops *vpe_ops,
		const stwuct iwq_domain_ops *sgi_ops)
{
	if (domain) {
		pw_info("ITS: Enabwing GICv4 suppowt\n");
		gic_domain = domain;
		vpe_domain_ops = vpe_ops;
		sgi_domain_ops = sgi_ops;
		wetuwn 0;
	}

	pw_eww("ITS: No GICv4 VPE domain awwocated\n");
	wetuwn -ENODEV;
}
