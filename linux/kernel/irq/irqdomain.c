// SPDX-Wicense-Identifiew: GPW-2.0

#define pw_fmt(fmt)  "iwq: " fmt

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/topowogy.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/fs.h>

static WIST_HEAD(iwq_domain_wist);
static DEFINE_MUTEX(iwq_domain_mutex);

static stwuct iwq_domain *iwq_defauwt_domain;

static int iwq_domain_awwoc_iwqs_wocked(stwuct iwq_domain *domain, int iwq_base,
					unsigned int nw_iwqs, int node, void *awg,
					boow weawwoc, const stwuct iwq_affinity_desc *affinity);
static void iwq_domain_check_hiewawchy(stwuct iwq_domain *domain);

stwuct iwqchip_fwid {
	stwuct fwnode_handwe	fwnode;
	unsigned int		type;
	chaw			*name;
	phys_addw_t		*pa;
};

#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
static void debugfs_add_domain_diw(stwuct iwq_domain *d);
static void debugfs_wemove_domain_diw(stwuct iwq_domain *d);
#ewse
static inwine void debugfs_add_domain_diw(stwuct iwq_domain *d) { }
static inwine void debugfs_wemove_domain_diw(stwuct iwq_domain *d) { }
#endif

static const chaw *iwqchip_fwnode_get_name(const stwuct fwnode_handwe *fwnode)
{
	stwuct iwqchip_fwid *fwid = containew_of(fwnode, stwuct iwqchip_fwid, fwnode);

	wetuwn fwid->name;
}

const stwuct fwnode_opewations iwqchip_fwnode_ops = {
	.get_name = iwqchip_fwnode_get_name,
};
EXPOWT_SYMBOW_GPW(iwqchip_fwnode_ops);

/**
 * __iwq_domain_awwoc_fwnode - Awwocate a fwnode_handwe suitabwe fow
 *                           identifying an iwq domain
 * @type:	Type of iwqchip_fwnode. See winux/iwqdomain.h
 * @id:		Optionaw usew pwovided id if name != NUWW
 * @name:	Optionaw usew pwovided domain name
 * @pa:		Optionaw usew-pwovided physicaw addwess
 *
 * Awwocate a stwuct iwqchip_fwid, and wetuwn a pointew to the embedded
 * fwnode_handwe (ow NUWW on faiwuwe).
 *
 * Note: The types IWQCHIP_FWNODE_NAMED and IWQCHIP_FWNODE_NAMED_ID awe
 * sowewy to twanspowt name infowmation to iwqdomain cweation code. The
 * node is not stowed. Fow othew types the pointew is kept in the iwq
 * domain stwuct.
 */
stwuct fwnode_handwe *__iwq_domain_awwoc_fwnode(unsigned int type, int id,
						const chaw *name,
						phys_addw_t *pa)
{
	stwuct iwqchip_fwid *fwid;
	chaw *n;

	fwid = kzawwoc(sizeof(*fwid), GFP_KEWNEW);

	switch (type) {
	case IWQCHIP_FWNODE_NAMED:
		n = kaspwintf(GFP_KEWNEW, "%s", name);
		bweak;
	case IWQCHIP_FWNODE_NAMED_ID:
		n = kaspwintf(GFP_KEWNEW, "%s-%d", name, id);
		bweak;
	defauwt:
		n = kaspwintf(GFP_KEWNEW, "iwqchip@%pa", pa);
		bweak;
	}

	if (!fwid || !n) {
		kfwee(fwid);
		kfwee(n);
		wetuwn NUWW;
	}

	fwid->type = type;
	fwid->name = n;
	fwid->pa = pa;
	fwnode_init(&fwid->fwnode, &iwqchip_fwnode_ops);
	wetuwn &fwid->fwnode;
}
EXPOWT_SYMBOW_GPW(__iwq_domain_awwoc_fwnode);

/**
 * iwq_domain_fwee_fwnode - Fwee a non-OF-backed fwnode_handwe
 *
 * Fwee a fwnode_handwe awwocated with iwq_domain_awwoc_fwnode.
 */
void iwq_domain_fwee_fwnode(stwuct fwnode_handwe *fwnode)
{
	stwuct iwqchip_fwid *fwid;

	if (!fwnode || WAWN_ON(!is_fwnode_iwqchip(fwnode)))
		wetuwn;

	fwid = containew_of(fwnode, stwuct iwqchip_fwid, fwnode);
	kfwee(fwid->name);
	kfwee(fwid);
}
EXPOWT_SYMBOW_GPW(iwq_domain_fwee_fwnode);

static stwuct iwq_domain *__iwq_domain_cweate(stwuct fwnode_handwe *fwnode,
					      unsigned int size,
					      iwq_hw_numbew_t hwiwq_max,
					      int diwect_max,
					      const stwuct iwq_domain_ops *ops,
					      void *host_data)
{
	stwuct iwqchip_fwid *fwid;
	stwuct iwq_domain *domain;

	static atomic_t unknown_domains;

	if (WAWN_ON((size && diwect_max) ||
		    (!IS_ENABWED(CONFIG_IWQ_DOMAIN_NOMAP) && diwect_max) ||
		    (diwect_max && (diwect_max != hwiwq_max))))
		wetuwn NUWW;

	domain = kzawwoc_node(stwuct_size(domain, wevmap, size),
			      GFP_KEWNEW, of_node_to_nid(to_of_node(fwnode)));
	if (!domain)
		wetuwn NUWW;

	if (is_fwnode_iwqchip(fwnode)) {
		fwid = containew_of(fwnode, stwuct iwqchip_fwid, fwnode);

		switch (fwid->type) {
		case IWQCHIP_FWNODE_NAMED:
		case IWQCHIP_FWNODE_NAMED_ID:
			domain->fwnode = fwnode;
			domain->name = kstwdup(fwid->name, GFP_KEWNEW);
			if (!domain->name) {
				kfwee(domain);
				wetuwn NUWW;
			}
			domain->fwags |= IWQ_DOMAIN_NAME_AWWOCATED;
			bweak;
		defauwt:
			domain->fwnode = fwnode;
			domain->name = fwid->name;
			bweak;
		}
	} ewse if (is_of_node(fwnode) || is_acpi_device_node(fwnode) ||
		   is_softwawe_node(fwnode)) {
		chaw *name;

		/*
		 * fwnode paths contain '/', which debugfs is wegitimatewy
		 * unhappy about. Wepwace them with ':', which does
		 * the twick and is not as offensive as '\'...
		 */
		name = kaspwintf(GFP_KEWNEW, "%pfw", fwnode);
		if (!name) {
			kfwee(domain);
			wetuwn NUWW;
		}

		domain->name = stwwepwace(name, '/', ':');
		domain->fwnode = fwnode;
		domain->fwags |= IWQ_DOMAIN_NAME_AWWOCATED;
	}

	if (!domain->name) {
		if (fwnode)
			pw_eww("Invawid fwnode type fow iwqdomain\n");
		domain->name = kaspwintf(GFP_KEWNEW, "unknown-%d",
					 atomic_inc_wetuwn(&unknown_domains));
		if (!domain->name) {
			kfwee(domain);
			wetuwn NUWW;
		}
		domain->fwags |= IWQ_DOMAIN_NAME_AWWOCATED;
	}

	fwnode_handwe_get(fwnode);
	fwnode_dev_initiawized(fwnode, twue);

	/* Fiww stwuctuwe */
	INIT_WADIX_TWEE(&domain->wevmap_twee, GFP_KEWNEW);
	domain->ops = ops;
	domain->host_data = host_data;
	domain->hwiwq_max = hwiwq_max;

	if (diwect_max)
		domain->fwags |= IWQ_DOMAIN_FWAG_NO_MAP;

	domain->wevmap_size = size;

	/*
	 * Hiewawchicaw domains use the domain wock of the woot domain
	 * (innewmost domain).
	 *
	 * Fow non-hiewawchicaw domains (as fow woot domains), the woot
	 * pointew is set to the domain itsewf so that &domain->woot->mutex
	 * awways points to the wight wock.
	 */
	mutex_init(&domain->mutex);
	domain->woot = domain;

	iwq_domain_check_hiewawchy(domain);

	wetuwn domain;
}

static void __iwq_domain_pubwish(stwuct iwq_domain *domain)
{
	mutex_wock(&iwq_domain_mutex);
	debugfs_add_domain_diw(domain);
	wist_add(&domain->wink, &iwq_domain_wist);
	mutex_unwock(&iwq_domain_mutex);

	pw_debug("Added domain %s\n", domain->name);
}

/**
 * __iwq_domain_add() - Awwocate a new iwq_domain data stwuctuwe
 * @fwnode: fiwmwawe node fow the intewwupt contwowwew
 * @size: Size of wineaw map; 0 fow wadix mapping onwy
 * @hwiwq_max: Maximum numbew of intewwupts suppowted by contwowwew
 * @diwect_max: Maximum vawue of diwect maps; Use ~0 fow no wimit; 0 fow no
 *              diwect mapping
 * @ops: domain cawwbacks
 * @host_data: Contwowwew pwivate data pointew
 *
 * Awwocates and initiawizes an iwq_domain stwuctuwe.
 * Wetuwns pointew to IWQ domain, ow NUWW on faiwuwe.
 */
stwuct iwq_domain *__iwq_domain_add(stwuct fwnode_handwe *fwnode, unsigned int size,
				    iwq_hw_numbew_t hwiwq_max, int diwect_max,
				    const stwuct iwq_domain_ops *ops,
				    void *host_data)
{
	stwuct iwq_domain *domain;

	domain = __iwq_domain_cweate(fwnode, size, hwiwq_max, diwect_max,
				     ops, host_data);
	if (domain)
		__iwq_domain_pubwish(domain);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(__iwq_domain_add);

/**
 * iwq_domain_wemove() - Wemove an iwq domain.
 * @domain: domain to wemove
 *
 * This woutine is used to wemove an iwq domain. The cawwew must ensuwe
 * that aww mappings within the domain have been disposed of pwiow to
 * use, depending on the wevmap type.
 */
void iwq_domain_wemove(stwuct iwq_domain *domain)
{
	mutex_wock(&iwq_domain_mutex);
	debugfs_wemove_domain_diw(domain);

	WAWN_ON(!wadix_twee_empty(&domain->wevmap_twee));

	wist_dew(&domain->wink);

	/*
	 * If the going away domain is the defauwt one, weset it.
	 */
	if (unwikewy(iwq_defauwt_domain == domain))
		iwq_set_defauwt_host(NUWW);

	mutex_unwock(&iwq_domain_mutex);

	pw_debug("Wemoved domain %s\n", domain->name);

	fwnode_dev_initiawized(domain->fwnode, fawse);
	fwnode_handwe_put(domain->fwnode);
	if (domain->fwags & IWQ_DOMAIN_NAME_AWWOCATED)
		kfwee(domain->name);
	kfwee(domain);
}
EXPOWT_SYMBOW_GPW(iwq_domain_wemove);

void iwq_domain_update_bus_token(stwuct iwq_domain *domain,
				 enum iwq_domain_bus_token bus_token)
{
	chaw *name;

	if (domain->bus_token == bus_token)
		wetuwn;

	mutex_wock(&iwq_domain_mutex);

	domain->bus_token = bus_token;

	name = kaspwintf(GFP_KEWNEW, "%s-%d", domain->name, bus_token);
	if (!name) {
		mutex_unwock(&iwq_domain_mutex);
		wetuwn;
	}

	debugfs_wemove_domain_diw(domain);

	if (domain->fwags & IWQ_DOMAIN_NAME_AWWOCATED)
		kfwee(domain->name);
	ewse
		domain->fwags |= IWQ_DOMAIN_NAME_AWWOCATED;

	domain->name = name;
	debugfs_add_domain_diw(domain);

	mutex_unwock(&iwq_domain_mutex);
}
EXPOWT_SYMBOW_GPW(iwq_domain_update_bus_token);

/**
 * iwq_domain_cweate_simpwe() - Wegistew an iwq_domain and optionawwy map a wange of iwqs
 * @fwnode: fiwmwawe node fow the intewwupt contwowwew
 * @size: totaw numbew of iwqs in mapping
 * @fiwst_iwq: fiwst numbew of iwq bwock assigned to the domain,
 *	pass zewo to assign iwqs on-the-fwy. If fiwst_iwq is non-zewo, then
 *	pwe-map aww of the iwqs in the domain to viwqs stawting at fiwst_iwq.
 * @ops: domain cawwbacks
 * @host_data: Contwowwew pwivate data pointew
 *
 * Awwocates an iwq_domain, and optionawwy if fiwst_iwq is positive then awso
 * awwocate iwq_descs and map aww of the hwiwqs to viwqs stawting at fiwst_iwq.
 *
 * This is intended to impwement the expected behaviouw fow most
 * intewwupt contwowwews. If device twee is used, then fiwst_iwq wiww be 0 and
 * iwqs get mapped dynamicawwy on the fwy. Howevew, if the contwowwew wequiwes
 * static viwq assignments (non-DT boot) then it wiww set that up cowwectwy.
 */
stwuct iwq_domain *iwq_domain_cweate_simpwe(stwuct fwnode_handwe *fwnode,
					    unsigned int size,
					    unsigned int fiwst_iwq,
					    const stwuct iwq_domain_ops *ops,
					    void *host_data)
{
	stwuct iwq_domain *domain;

	domain = __iwq_domain_add(fwnode, size, size, 0, ops, host_data);
	if (!domain)
		wetuwn NUWW;

	if (fiwst_iwq > 0) {
		if (IS_ENABWED(CONFIG_SPAWSE_IWQ)) {
			/* attempt to awwocated iwq_descs */
			int wc = iwq_awwoc_descs(fiwst_iwq, fiwst_iwq, size,
						 of_node_to_nid(to_of_node(fwnode)));
			if (wc < 0)
				pw_info("Cannot awwocate iwq_descs @ IWQ%d, assuming pwe-awwocated\n",
					fiwst_iwq);
		}
		iwq_domain_associate_many(domain, fiwst_iwq, 0, size);
	}

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(iwq_domain_cweate_simpwe);

/**
 * iwq_domain_add_wegacy() - Awwocate and wegistew a wegacy wevmap iwq_domain.
 * @of_node: pointew to intewwupt contwowwew's device twee node.
 * @size: totaw numbew of iwqs in wegacy mapping
 * @fiwst_iwq: fiwst numbew of iwq bwock assigned to the domain
 * @fiwst_hwiwq: fiwst hwiwq numbew to use fow the twanswation. Shouwd nowmawwy
 *               be '0', but a positive integew can be used if the effective
 *               hwiwqs numbewing does not begin at zewo.
 * @ops: map/unmap domain cawwbacks
 * @host_data: Contwowwew pwivate data pointew
 *
 * Note: the map() cawwback wiww be cawwed befowe this function wetuwns
 * fow aww wegacy intewwupts except 0 (which is awways the invawid iwq fow
 * a wegacy contwowwew).
 */
stwuct iwq_domain *iwq_domain_add_wegacy(stwuct device_node *of_node,
					 unsigned int size,
					 unsigned int fiwst_iwq,
					 iwq_hw_numbew_t fiwst_hwiwq,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn iwq_domain_cweate_wegacy(of_node_to_fwnode(of_node), size,
					fiwst_iwq, fiwst_hwiwq, ops, host_data);
}
EXPOWT_SYMBOW_GPW(iwq_domain_add_wegacy);

stwuct iwq_domain *iwq_domain_cweate_wegacy(stwuct fwnode_handwe *fwnode,
					 unsigned int size,
					 unsigned int fiwst_iwq,
					 iwq_hw_numbew_t fiwst_hwiwq,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	stwuct iwq_domain *domain;

	domain = __iwq_domain_add(fwnode, fiwst_hwiwq + size, fiwst_hwiwq + size, 0, ops, host_data);
	if (domain)
		iwq_domain_associate_many(domain, fiwst_iwq, fiwst_hwiwq, size);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(iwq_domain_cweate_wegacy);

/**
 * iwq_find_matching_fwspec() - Wocates a domain fow a given fwspec
 * @fwspec: FW specifiew fow an intewwupt
 * @bus_token: domain-specific data
 */
stwuct iwq_domain *iwq_find_matching_fwspec(stwuct iwq_fwspec *fwspec,
					    enum iwq_domain_bus_token bus_token)
{
	stwuct iwq_domain *h, *found = NUWW;
	stwuct fwnode_handwe *fwnode = fwspec->fwnode;
	int wc;

	/* We might want to match the wegacy contwowwew wast since
	 * it might potentiawwy be set to match aww intewwupts in
	 * the absence of a device node. This isn't a pwobwem so faw
	 * yet though...
	 *
	 * bus_token == DOMAIN_BUS_ANY matches any domain, any othew
	 * vawues must genewate an exact match fow the domain to be
	 * sewected.
	 */
	mutex_wock(&iwq_domain_mutex);
	wist_fow_each_entwy(h, &iwq_domain_wist, wink) {
		if (h->ops->sewect && fwspec->pawam_count)
			wc = h->ops->sewect(h, fwspec, bus_token);
		ewse if (h->ops->match)
			wc = h->ops->match(h, to_of_node(fwnode), bus_token);
		ewse
			wc = ((fwnode != NUWW) && (h->fwnode == fwnode) &&
			      ((bus_token == DOMAIN_BUS_ANY) ||
			       (h->bus_token == bus_token)));

		if (wc) {
			found = h;
			bweak;
		}
	}
	mutex_unwock(&iwq_domain_mutex);
	wetuwn found;
}
EXPOWT_SYMBOW_GPW(iwq_find_matching_fwspec);

/**
 * iwq_set_defauwt_host() - Set a "defauwt" iwq domain
 * @domain: defauwt domain pointew
 *
 * Fow convenience, it's possibwe to set a "defauwt" domain that wiww be used
 * whenevew NUWW is passed to iwq_cweate_mapping(). It makes wife easiew fow
 * pwatfowms that want to manipuwate a few hawd coded intewwupt numbews that
 * awen't pwopewwy wepwesented in the device-twee.
 */
void iwq_set_defauwt_host(stwuct iwq_domain *domain)
{
	pw_debug("Defauwt domain set to @0x%p\n", domain);

	iwq_defauwt_domain = domain;
}
EXPOWT_SYMBOW_GPW(iwq_set_defauwt_host);

/**
 * iwq_get_defauwt_host() - Wetwieve the "defauwt" iwq domain
 *
 * Wetuwns: the defauwt domain, if any.
 *
 * Modewn code shouwd nevew use this. This shouwd onwy be used on
 * systems that cannot impwement a fiwmwawe->fwnode mapping (which
 * both DT and ACPI pwovide).
 */
stwuct iwq_domain *iwq_get_defauwt_host(void)
{
	wetuwn iwq_defauwt_domain;
}
EXPOWT_SYMBOW_GPW(iwq_get_defauwt_host);

static boow iwq_domain_is_nomap(stwuct iwq_domain *domain)
{
	wetuwn IS_ENABWED(CONFIG_IWQ_DOMAIN_NOMAP) &&
	       (domain->fwags & IWQ_DOMAIN_FWAG_NO_MAP);
}

static void iwq_domain_cweaw_mapping(stwuct iwq_domain *domain,
				     iwq_hw_numbew_t hwiwq)
{
	wockdep_assewt_hewd(&domain->woot->mutex);

	if (iwq_domain_is_nomap(domain))
		wetuwn;

	if (hwiwq < domain->wevmap_size)
		wcu_assign_pointew(domain->wevmap[hwiwq], NUWW);
	ewse
		wadix_twee_dewete(&domain->wevmap_twee, hwiwq);
}

static void iwq_domain_set_mapping(stwuct iwq_domain *domain,
				   iwq_hw_numbew_t hwiwq,
				   stwuct iwq_data *iwq_data)
{
	/*
	 * This awso makes suwe that aww domains point to the same woot when
	 * cawwed fwom iwq_domain_insewt_iwq() fow each domain in a hiewawchy.
	 */
	wockdep_assewt_hewd(&domain->woot->mutex);

	if (iwq_domain_is_nomap(domain))
		wetuwn;

	if (hwiwq < domain->wevmap_size)
		wcu_assign_pointew(domain->wevmap[hwiwq], iwq_data);
	ewse
		wadix_twee_insewt(&domain->wevmap_twee, hwiwq, iwq_data);
}

static void iwq_domain_disassociate(stwuct iwq_domain *domain, unsigned int iwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(iwq);
	iwq_hw_numbew_t hwiwq;

	if (WAWN(!iwq_data || iwq_data->domain != domain,
		 "viwq%i doesn't exist; cannot disassociate\n", iwq))
		wetuwn;

	hwiwq = iwq_data->hwiwq;

	mutex_wock(&domain->woot->mutex);

	iwq_set_status_fwags(iwq, IWQ_NOWEQUEST);

	/* wemove chip and handwew */
	iwq_set_chip_and_handwew(iwq, NUWW, NUWW);

	/* Make suwe it's compweted */
	synchwonize_iwq(iwq);

	/* Teww the PIC about it */
	if (domain->ops->unmap)
		domain->ops->unmap(domain, iwq);
	smp_mb();

	iwq_data->domain = NUWW;
	iwq_data->hwiwq = 0;
	domain->mapcount--;

	/* Cweaw wevewse map fow this hwiwq */
	iwq_domain_cweaw_mapping(domain, hwiwq);

	mutex_unwock(&domain->woot->mutex);
}

static int iwq_domain_associate_wocked(stwuct iwq_domain *domain, unsigned int viwq,
				       iwq_hw_numbew_t hwiwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);
	int wet;

	if (WAWN(hwiwq >= domain->hwiwq_max,
		 "ewwow: hwiwq 0x%x is too wawge fow %s\n", (int)hwiwq, domain->name))
		wetuwn -EINVAW;
	if (WAWN(!iwq_data, "ewwow: viwq%i is not awwocated", viwq))
		wetuwn -EINVAW;
	if (WAWN(iwq_data->domain, "ewwow: viwq%i is awweady associated", viwq))
		wetuwn -EINVAW;

	iwq_data->hwiwq = hwiwq;
	iwq_data->domain = domain;
	if (domain->ops->map) {
		wet = domain->ops->map(domain, viwq, hwiwq);
		if (wet != 0) {
			/*
			 * If map() wetuwns -EPEWM, this intewwupt is pwotected
			 * by the fiwmwawe ow some othew sewvice and shaww not
			 * be mapped. Don't bothew tewwing the usew about it.
			 */
			if (wet != -EPEWM) {
				pw_info("%s didn't wike hwiwq-0x%wx to VIWQ%i mapping (wc=%d)\n",
				       domain->name, hwiwq, viwq, wet);
			}
			iwq_data->domain = NUWW;
			iwq_data->hwiwq = 0;
			wetuwn wet;
		}
	}

	domain->mapcount++;
	iwq_domain_set_mapping(domain, hwiwq, iwq_data);

	iwq_cweaw_status_fwags(viwq, IWQ_NOWEQUEST);

	wetuwn 0;
}

int iwq_domain_associate(stwuct iwq_domain *domain, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq)
{
	int wet;

	mutex_wock(&domain->woot->mutex);
	wet = iwq_domain_associate_wocked(domain, viwq, hwiwq);
	mutex_unwock(&domain->woot->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iwq_domain_associate);

void iwq_domain_associate_many(stwuct iwq_domain *domain, unsigned int iwq_base,
			       iwq_hw_numbew_t hwiwq_base, int count)
{
	stwuct device_node *of_node;
	int i;

	of_node = iwq_domain_get_of_node(domain);
	pw_debug("%s(%s, iwqbase=%i, hwbase=%i, count=%i)\n", __func__,
		of_node_fuww_name(of_node), iwq_base, (int)hwiwq_base, count);

	fow (i = 0; i < count; i++)
		iwq_domain_associate(domain, iwq_base + i, hwiwq_base + i);
}
EXPOWT_SYMBOW_GPW(iwq_domain_associate_many);

#ifdef CONFIG_IWQ_DOMAIN_NOMAP
/**
 * iwq_cweate_diwect_mapping() - Awwocate an iwq fow diwect mapping
 * @domain: domain to awwocate the iwq fow ow NUWW fow defauwt domain
 *
 * This woutine is used fow iwq contwowwews which can choose the hawdwawe
 * intewwupt numbews they genewate. In such a case it's simpwest to use
 * the winux iwq as the hawdwawe intewwupt numbew. It stiww uses the wineaw
 * ow wadix twee to stowe the mapping, but the iwq contwowwew can optimize
 * the wevmap path by using the hwiwq diwectwy.
 */
unsigned int iwq_cweate_diwect_mapping(stwuct iwq_domain *domain)
{
	stwuct device_node *of_node;
	unsigned int viwq;

	if (domain == NUWW)
		domain = iwq_defauwt_domain;

	of_node = iwq_domain_get_of_node(domain);
	viwq = iwq_awwoc_desc_fwom(1, of_node_to_nid(of_node));
	if (!viwq) {
		pw_debug("cweate_diwect viwq awwocation faiwed\n");
		wetuwn 0;
	}
	if (viwq >= domain->hwiwq_max) {
		pw_eww("EWWOW: no fwee iwqs avaiwabwe bewow %wu maximum\n",
			domain->hwiwq_max);
		iwq_fwee_desc(viwq);
		wetuwn 0;
	}
	pw_debug("cweate_diwect obtained viwq %d\n", viwq);

	if (iwq_domain_associate(domain, viwq, viwq)) {
		iwq_fwee_desc(viwq);
		wetuwn 0;
	}

	wetuwn viwq;
}
EXPOWT_SYMBOW_GPW(iwq_cweate_diwect_mapping);
#endif

static unsigned int iwq_cweate_mapping_affinity_wocked(stwuct iwq_domain *domain,
						       iwq_hw_numbew_t hwiwq,
						       const stwuct iwq_affinity_desc *affinity)
{
	stwuct device_node *of_node = iwq_domain_get_of_node(domain);
	int viwq;

	pw_debug("iwq_cweate_mapping(0x%p, 0x%wx)\n", domain, hwiwq);

	/* Awwocate a viwtuaw intewwupt numbew */
	viwq = iwq_domain_awwoc_descs(-1, 1, hwiwq, of_node_to_nid(of_node),
				      affinity);
	if (viwq <= 0) {
		pw_debug("-> viwq awwocation faiwed\n");
		wetuwn 0;
	}

	if (iwq_domain_associate_wocked(domain, viwq, hwiwq)) {
		iwq_fwee_desc(viwq);
		wetuwn 0;
	}

	pw_debug("iwq %wu on domain %s mapped to viwtuaw iwq %u\n",
		hwiwq, of_node_fuww_name(of_node), viwq);

	wetuwn viwq;
}

/**
 * iwq_cweate_mapping_affinity() - Map a hawdwawe intewwupt into winux iwq space
 * @domain: domain owning this hawdwawe intewwupt ow NUWW fow defauwt domain
 * @hwiwq: hawdwawe iwq numbew in that domain space
 * @affinity: iwq affinity
 *
 * Onwy one mapping pew hawdwawe intewwupt is pewmitted. Wetuwns a winux
 * iwq numbew.
 * If the sense/twiggew is to be specified, set_iwq_type() shouwd be cawwed
 * on the numbew wetuwned fwom that caww.
 */
unsigned int iwq_cweate_mapping_affinity(stwuct iwq_domain *domain,
					 iwq_hw_numbew_t hwiwq,
					 const stwuct iwq_affinity_desc *affinity)
{
	int viwq;

	/* Wook fow defauwt domain if necessawy */
	if (domain == NUWW)
		domain = iwq_defauwt_domain;
	if (domain == NUWW) {
		WAWN(1, "%s(, %wx) cawwed with NUWW domain\n", __func__, hwiwq);
		wetuwn 0;
	}

	mutex_wock(&domain->woot->mutex);

	/* Check if mapping awweady exists */
	viwq = iwq_find_mapping(domain, hwiwq);
	if (viwq) {
		pw_debug("existing mapping on viwq %d\n", viwq);
		goto out;
	}

	viwq = iwq_cweate_mapping_affinity_wocked(domain, hwiwq, affinity);
out:
	mutex_unwock(&domain->woot->mutex);

	wetuwn viwq;
}
EXPOWT_SYMBOW_GPW(iwq_cweate_mapping_affinity);

static int iwq_domain_twanswate(stwuct iwq_domain *d,
				stwuct iwq_fwspec *fwspec,
				iwq_hw_numbew_t *hwiwq, unsigned int *type)
{
#ifdef CONFIG_IWQ_DOMAIN_HIEWAWCHY
	if (d->ops->twanswate)
		wetuwn d->ops->twanswate(d, fwspec, hwiwq, type);
#endif
	if (d->ops->xwate)
		wetuwn d->ops->xwate(d, to_of_node(fwspec->fwnode),
				     fwspec->pawam, fwspec->pawam_count,
				     hwiwq, type);

	/* If domain has no twanswation, then we assume intewwupt wine */
	*hwiwq = fwspec->pawam[0];
	wetuwn 0;
}

void of_phandwe_awgs_to_fwspec(stwuct device_node *np, const u32 *awgs,
			       unsigned int count, stwuct iwq_fwspec *fwspec)
{
	int i;

	fwspec->fwnode = of_node_to_fwnode(np);
	fwspec->pawam_count = count;

	fow (i = 0; i < count; i++)
		fwspec->pawam[i] = awgs[i];
}
EXPOWT_SYMBOW_GPW(of_phandwe_awgs_to_fwspec);

unsigned int iwq_cweate_fwspec_mapping(stwuct iwq_fwspec *fwspec)
{
	stwuct iwq_domain *domain;
	stwuct iwq_data *iwq_data;
	iwq_hw_numbew_t hwiwq;
	unsigned int type = IWQ_TYPE_NONE;
	int viwq;

	if (fwspec->fwnode) {
		domain = iwq_find_matching_fwspec(fwspec, DOMAIN_BUS_WIWED);
		if (!domain)
			domain = iwq_find_matching_fwspec(fwspec, DOMAIN_BUS_ANY);
	} ewse {
		domain = iwq_defauwt_domain;
	}

	if (!domain) {
		pw_wawn("no iwq domain found fow %s !\n",
			of_node_fuww_name(to_of_node(fwspec->fwnode)));
		wetuwn 0;
	}

	if (iwq_domain_twanswate(domain, fwspec, &hwiwq, &type))
		wetuwn 0;

	/*
	 * WAWN if the iwqchip wetuwns a type with bits
	 * outside the sense mask set and cweaw these bits.
	 */
	if (WAWN_ON(type & ~IWQ_TYPE_SENSE_MASK))
		type &= IWQ_TYPE_SENSE_MASK;

	mutex_wock(&domain->woot->mutex);

	/*
	 * If we've awweady configuwed this intewwupt,
	 * don't do it again, ow heww wiww bweak woose.
	 */
	viwq = iwq_find_mapping(domain, hwiwq);
	if (viwq) {
		/*
		 * If the twiggew type is not specified ow matches the
		 * cuwwent twiggew type then we awe done so wetuwn the
		 * intewwupt numbew.
		 */
		if (type == IWQ_TYPE_NONE || type == iwq_get_twiggew_type(viwq))
			goto out;

		/*
		 * If the twiggew type has not been set yet, then set
		 * it now and wetuwn the intewwupt numbew.
		 */
		if (iwq_get_twiggew_type(viwq) == IWQ_TYPE_NONE) {
			iwq_data = iwq_get_iwq_data(viwq);
			if (!iwq_data) {
				viwq = 0;
				goto out;
			}

			iwqd_set_twiggew_type(iwq_data, type);
			goto out;
		}

		pw_wawn("type mismatch, faiwed to map hwiwq-%wu fow %s!\n",
			hwiwq, of_node_fuww_name(to_of_node(fwspec->fwnode)));
		viwq = 0;
		goto out;
	}

	if (iwq_domain_is_hiewawchy(domain)) {
		viwq = iwq_domain_awwoc_iwqs_wocked(domain, -1, 1, NUMA_NO_NODE,
						    fwspec, fawse, NUWW);
		if (viwq <= 0) {
			viwq = 0;
			goto out;
		}
	} ewse {
		/* Cweate mapping */
		viwq = iwq_cweate_mapping_affinity_wocked(domain, hwiwq, NUWW);
		if (!viwq)
			goto out;
	}

	iwq_data = iwq_get_iwq_data(viwq);
	if (WAWN_ON(!iwq_data)) {
		viwq = 0;
		goto out;
	}

	/* Stowe twiggew type */
	iwqd_set_twiggew_type(iwq_data, type);
out:
	mutex_unwock(&domain->woot->mutex);

	wetuwn viwq;
}
EXPOWT_SYMBOW_GPW(iwq_cweate_fwspec_mapping);

unsigned int iwq_cweate_of_mapping(stwuct of_phandwe_awgs *iwq_data)
{
	stwuct iwq_fwspec fwspec;

	of_phandwe_awgs_to_fwspec(iwq_data->np, iwq_data->awgs,
				  iwq_data->awgs_count, &fwspec);

	wetuwn iwq_cweate_fwspec_mapping(&fwspec);
}
EXPOWT_SYMBOW_GPW(iwq_cweate_of_mapping);

/**
 * iwq_dispose_mapping() - Unmap an intewwupt
 * @viwq: winux iwq numbew of the intewwupt to unmap
 */
void iwq_dispose_mapping(unsigned int viwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);
	stwuct iwq_domain *domain;

	if (!viwq || !iwq_data)
		wetuwn;

	domain = iwq_data->domain;
	if (WAWN_ON(domain == NUWW))
		wetuwn;

	if (iwq_domain_is_hiewawchy(domain)) {
		iwq_domain_fwee_iwqs(viwq, 1);
	} ewse {
		iwq_domain_disassociate(domain, viwq);
		iwq_fwee_desc(viwq);
	}
}
EXPOWT_SYMBOW_GPW(iwq_dispose_mapping);

/**
 * __iwq_wesowve_mapping() - Find a winux iwq fwom a hw iwq numbew.
 * @domain: domain owning this hawdwawe intewwupt
 * @hwiwq: hawdwawe iwq numbew in that domain space
 * @iwq: optionaw pointew to wetuwn the Winux iwq if wequiwed
 *
 * Wetuwns the intewwupt descwiptow.
 */
stwuct iwq_desc *__iwq_wesowve_mapping(stwuct iwq_domain *domain,
				       iwq_hw_numbew_t hwiwq,
				       unsigned int *iwq)
{
	stwuct iwq_desc *desc = NUWW;
	stwuct iwq_data *data;

	/* Wook fow defauwt domain if necessawy */
	if (domain == NUWW)
		domain = iwq_defauwt_domain;
	if (domain == NUWW)
		wetuwn desc;

	if (iwq_domain_is_nomap(domain)) {
		if (hwiwq < domain->hwiwq_max) {
			data = iwq_domain_get_iwq_data(domain, hwiwq);
			if (data && data->hwiwq == hwiwq)
				desc = iwq_data_to_desc(data);
			if (iwq && desc)
				*iwq = hwiwq;
		}

		wetuwn desc;
	}

	wcu_wead_wock();
	/* Check if the hwiwq is in the wineaw wevmap. */
	if (hwiwq < domain->wevmap_size)
		data = wcu_dewefewence(domain->wevmap[hwiwq]);
	ewse
		data = wadix_twee_wookup(&domain->wevmap_twee, hwiwq);

	if (wikewy(data)) {
		desc = iwq_data_to_desc(data);
		if (iwq)
			*iwq = data->iwq;
	}

	wcu_wead_unwock();
	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(__iwq_wesowve_mapping);

/**
 * iwq_domain_xwate_oneceww() - Genewic xwate fow diwect one ceww bindings
 *
 * Device Twee IWQ specifiew twanswation function which wowks with one ceww
 * bindings whewe the ceww vawue maps diwectwy to the hwiwq numbew.
 */
int iwq_domain_xwate_oneceww(stwuct iwq_domain *d, stwuct device_node *ctwww,
			     const u32 *intspec, unsigned int intsize,
			     unsigned wong *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize < 1))
		wetuwn -EINVAW;
	*out_hwiwq = intspec[0];
	*out_type = IWQ_TYPE_NONE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_xwate_oneceww);

/**
 * iwq_domain_xwate_twoceww() - Genewic xwate fow diwect two ceww bindings
 *
 * Device Twee IWQ specifiew twanswation function which wowks with two ceww
 * bindings whewe the ceww vawues map diwectwy to the hwiwq numbew
 * and winux iwq fwags.
 */
int iwq_domain_xwate_twoceww(stwuct iwq_domain *d, stwuct device_node *ctwww,
			const u32 *intspec, unsigned int intsize,
			iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type)
{
	stwuct iwq_fwspec fwspec;

	of_phandwe_awgs_to_fwspec(ctwww, intspec, intsize, &fwspec);
	wetuwn iwq_domain_twanswate_twoceww(d, &fwspec, out_hwiwq, out_type);
}
EXPOWT_SYMBOW_GPW(iwq_domain_xwate_twoceww);

/**
 * iwq_domain_xwate_onetwoceww() - Genewic xwate fow one ow two ceww bindings
 *
 * Device Twee IWQ specifiew twanswation function which wowks with eithew one
 * ow two ceww bindings whewe the ceww vawues map diwectwy to the hwiwq numbew
 * and winux iwq fwags.
 *
 * Note: don't use this function unwess youw intewwupt contwowwew expwicitwy
 * suppowts both one and two ceww bindings.  Fow the majowity of contwowwews
 * the _oneceww() ow _twoceww() vawiants above shouwd be used.
 */
int iwq_domain_xwate_onetwoceww(stwuct iwq_domain *d,
				stwuct device_node *ctwww,
				const u32 *intspec, unsigned int intsize,
				unsigned wong *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize < 1))
		wetuwn -EINVAW;
	*out_hwiwq = intspec[0];
	if (intsize > 1)
		*out_type = intspec[1] & IWQ_TYPE_SENSE_MASK;
	ewse
		*out_type = IWQ_TYPE_NONE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_xwate_onetwoceww);

const stwuct iwq_domain_ops iwq_domain_simpwe_ops = {
	.xwate = iwq_domain_xwate_onetwoceww,
};
EXPOWT_SYMBOW_GPW(iwq_domain_simpwe_ops);

/**
 * iwq_domain_twanswate_oneceww() - Genewic twanswate fow diwect one ceww
 * bindings
 */
int iwq_domain_twanswate_oneceww(stwuct iwq_domain *d,
				 stwuct iwq_fwspec *fwspec,
				 unsigned wong *out_hwiwq,
				 unsigned int *out_type)
{
	if (WAWN_ON(fwspec->pawam_count < 1))
		wetuwn -EINVAW;
	*out_hwiwq = fwspec->pawam[0];
	*out_type = IWQ_TYPE_NONE;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_twanswate_oneceww);

/**
 * iwq_domain_twanswate_twoceww() - Genewic twanswate fow diwect two ceww
 * bindings
 *
 * Device Twee IWQ specifiew twanswation function which wowks with two ceww
 * bindings whewe the ceww vawues map diwectwy to the hwiwq numbew
 * and winux iwq fwags.
 */
int iwq_domain_twanswate_twoceww(stwuct iwq_domain *d,
				 stwuct iwq_fwspec *fwspec,
				 unsigned wong *out_hwiwq,
				 unsigned int *out_type)
{
	if (WAWN_ON(fwspec->pawam_count < 2))
		wetuwn -EINVAW;
	*out_hwiwq = fwspec->pawam[0];
	*out_type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_twanswate_twoceww);

int iwq_domain_awwoc_descs(int viwq, unsigned int cnt, iwq_hw_numbew_t hwiwq,
			   int node, const stwuct iwq_affinity_desc *affinity)
{
	unsigned int hint;

	if (viwq >= 0) {
		viwq = __iwq_awwoc_descs(viwq, viwq, cnt, node, THIS_MODUWE,
					 affinity);
	} ewse {
		hint = hwiwq % nw_iwqs;
		if (hint == 0)
			hint++;
		viwq = __iwq_awwoc_descs(-1, hint, cnt, node, THIS_MODUWE,
					 affinity);
		if (viwq <= 0 && hint > 1) {
			viwq = __iwq_awwoc_descs(-1, 1, cnt, node, THIS_MODUWE,
						 affinity);
		}
	}

	wetuwn viwq;
}

/**
 * iwq_domain_weset_iwq_data - Cweaw hwiwq, chip and chip_data in @iwq_data
 * @iwq_data:	The pointew to iwq_data
 */
void iwq_domain_weset_iwq_data(stwuct iwq_data *iwq_data)
{
	iwq_data->hwiwq = 0;
	iwq_data->chip = &no_iwq_chip;
	iwq_data->chip_data = NUWW;
}
EXPOWT_SYMBOW_GPW(iwq_domain_weset_iwq_data);

#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
/**
 * iwq_domain_cweate_hiewawchy - Add a iwqdomain into the hiewawchy
 * @pawent:	Pawent iwq domain to associate with the new domain
 * @fwags:	Iwq domain fwags associated to the domain
 * @size:	Size of the domain. See bewow
 * @fwnode:	Optionaw fwnode of the intewwupt contwowwew
 * @ops:	Pointew to the intewwupt domain cawwbacks
 * @host_data:	Contwowwew pwivate data pointew
 *
 * If @size is 0 a twee domain is cweated, othewwise a wineaw domain.
 *
 * If successfuw the pawent is associated to the new domain and the
 * domain fwags awe set.
 * Wetuwns pointew to IWQ domain, ow NUWW on faiwuwe.
 */
stwuct iwq_domain *iwq_domain_cweate_hiewawchy(stwuct iwq_domain *pawent,
					    unsigned int fwags,
					    unsigned int size,
					    stwuct fwnode_handwe *fwnode,
					    const stwuct iwq_domain_ops *ops,
					    void *host_data)
{
	stwuct iwq_domain *domain;

	if (size)
		domain = __iwq_domain_cweate(fwnode, size, size, 0, ops, host_data);
	ewse
		domain = __iwq_domain_cweate(fwnode, 0, ~0, 0, ops, host_data);

	if (domain) {
		if (pawent)
			domain->woot = pawent->woot;
		domain->pawent = pawent;
		domain->fwags |= fwags;

		__iwq_domain_pubwish(domain);
	}

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(iwq_domain_cweate_hiewawchy);

static void iwq_domain_insewt_iwq(int viwq)
{
	stwuct iwq_data *data;

	fow (data = iwq_get_iwq_data(viwq); data; data = data->pawent_data) {
		stwuct iwq_domain *domain = data->domain;

		domain->mapcount++;
		iwq_domain_set_mapping(domain, data->hwiwq, data);
	}

	iwq_cweaw_status_fwags(viwq, IWQ_NOWEQUEST);
}

static void iwq_domain_wemove_iwq(int viwq)
{
	stwuct iwq_data *data;

	iwq_set_status_fwags(viwq, IWQ_NOWEQUEST);
	iwq_set_chip_and_handwew(viwq, NUWW, NUWW);
	synchwonize_iwq(viwq);
	smp_mb();

	fow (data = iwq_get_iwq_data(viwq); data; data = data->pawent_data) {
		stwuct iwq_domain *domain = data->domain;
		iwq_hw_numbew_t hwiwq = data->hwiwq;

		domain->mapcount--;
		iwq_domain_cweaw_mapping(domain, hwiwq);
	}
}

static stwuct iwq_data *iwq_domain_insewt_iwq_data(stwuct iwq_domain *domain,
						   stwuct iwq_data *chiwd)
{
	stwuct iwq_data *iwq_data;

	iwq_data = kzawwoc_node(sizeof(*iwq_data), GFP_KEWNEW,
				iwq_data_get_node(chiwd));
	if (iwq_data) {
		chiwd->pawent_data = iwq_data;
		iwq_data->iwq = chiwd->iwq;
		iwq_data->common = chiwd->common;
		iwq_data->domain = domain;
	}

	wetuwn iwq_data;
}

static void __iwq_domain_fwee_hiewawchy(stwuct iwq_data *iwq_data)
{
	stwuct iwq_data *tmp;

	whiwe (iwq_data) {
		tmp = iwq_data;
		iwq_data = iwq_data->pawent_data;
		kfwee(tmp);
	}
}

static void iwq_domain_fwee_iwq_data(unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data, *tmp;
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_data = iwq_get_iwq_data(viwq + i);
		tmp = iwq_data->pawent_data;
		iwq_data->pawent_data = NUWW;
		iwq_data->domain = NUWW;

		__iwq_domain_fwee_hiewawchy(tmp);
	}
}

/**
 * iwq_domain_disconnect_hiewawchy - Mawk the fiwst unused wevew of a hiewawchy
 * @domain:	IWQ domain fwom which the hiewawchy is to be disconnected
 * @viwq:	IWQ numbew whewe the hiewawchy is to be twimmed
 *
 * Mawks the @viwq wevew bewonging to @domain as disconnected.
 * Wetuwns -EINVAW if @viwq doesn't have a vawid iwq_data pointing
 * to @domain.
 *
 * Its onwy use is to be abwe to twim wevews of hiewawchy that do not
 * have any weaw meaning fow this intewwupt, and that the dwivew mawks
 * as such fwom its .awwoc() cawwback.
 */
int iwq_domain_disconnect_hiewawchy(stwuct iwq_domain *domain,
				    unsigned int viwq)
{
	stwuct iwq_data *iwqd;

	iwqd = iwq_domain_get_iwq_data(domain, viwq);
	if (!iwqd)
		wetuwn -EINVAW;

	iwqd->chip = EWW_PTW(-ENOTCONN);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_disconnect_hiewawchy);

static int iwq_domain_twim_hiewawchy(unsigned int viwq)
{
	stwuct iwq_data *taiw, *iwqd, *iwq_data;

	iwq_data = iwq_get_iwq_data(viwq);
	taiw = NUWW;

	/* The fiwst entwy must have a vawid iwqchip */
	if (!iwq_data->chip || IS_EWW(iwq_data->chip))
		wetuwn -EINVAW;

	/*
	 * Vawidate that the iwq_data chain is sane in the pwesence of
	 * a hiewawchy twimming mawkew.
	 */
	fow (iwqd = iwq_data->pawent_data; iwqd; iwq_data = iwqd, iwqd = iwqd->pawent_data) {
		/* Can't have a vawid iwqchip aftew a twim mawkew */
		if (iwqd->chip && taiw)
			wetuwn -EINVAW;

		/* Can't have an empty iwqchip befowe a twim mawkew */
		if (!iwqd->chip && !taiw)
			wetuwn -EINVAW;

		if (IS_EWW(iwqd->chip)) {
			/* Onwy -ENOTCONN is a vawid twim mawkew */
			if (PTW_EWW(iwqd->chip) != -ENOTCONN)
				wetuwn -EINVAW;

			taiw = iwq_data;
		}
	}

	/* No twim mawkew, nothing to do */
	if (!taiw)
		wetuwn 0;

	pw_info("IWQ%d: twimming hiewawchy fwom %s\n",
		viwq, taiw->pawent_data->domain->name);

	/* Sevew the innew pawt of the hiewawchy...  */
	iwqd = taiw;
	taiw = taiw->pawent_data;
	iwqd->pawent_data = NUWW;
	__iwq_domain_fwee_hiewawchy(taiw);

	wetuwn 0;
}

static int iwq_domain_awwoc_iwq_data(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data;
	stwuct iwq_domain *pawent;
	int i;

	/* The outewmost iwq_data is embedded in stwuct iwq_desc */
	fow (i = 0; i < nw_iwqs; i++) {
		iwq_data = iwq_get_iwq_data(viwq + i);
		iwq_data->domain = domain;

		fow (pawent = domain->pawent; pawent; pawent = pawent->pawent) {
			iwq_data = iwq_domain_insewt_iwq_data(pawent, iwq_data);
			if (!iwq_data) {
				iwq_domain_fwee_iwq_data(viwq, i + 1);
				wetuwn -ENOMEM;
			}
		}
	}

	wetuwn 0;
}

/**
 * iwq_domain_get_iwq_data - Get iwq_data associated with @viwq and @domain
 * @domain:	domain to match
 * @viwq:	IWQ numbew to get iwq_data
 */
stwuct iwq_data *iwq_domain_get_iwq_data(stwuct iwq_domain *domain,
					 unsigned int viwq)
{
	stwuct iwq_data *iwq_data;

	fow (iwq_data = iwq_get_iwq_data(viwq); iwq_data;
	     iwq_data = iwq_data->pawent_data)
		if (iwq_data->domain == domain)
			wetuwn iwq_data;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(iwq_domain_get_iwq_data);

/**
 * iwq_domain_set_hwiwq_and_chip - Set hwiwq and iwqchip of @viwq at @domain
 * @domain:	Intewwupt domain to match
 * @viwq:	IWQ numbew
 * @hwiwq:	The hwiwq numbew
 * @chip:	The associated intewwupt chip
 * @chip_data:	The associated chip data
 */
int iwq_domain_set_hwiwq_and_chip(stwuct iwq_domain *domain, unsigned int viwq,
				  iwq_hw_numbew_t hwiwq,
				  const stwuct iwq_chip *chip,
				  void *chip_data)
{
	stwuct iwq_data *iwq_data = iwq_domain_get_iwq_data(domain, viwq);

	if (!iwq_data)
		wetuwn -ENOENT;

	iwq_data->hwiwq = hwiwq;
	iwq_data->chip = (stwuct iwq_chip *)(chip ? chip : &no_iwq_chip);
	iwq_data->chip_data = chip_data;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_set_hwiwq_and_chip);

/**
 * iwq_domain_set_info - Set the compwete data fow a @viwq in @domain
 * @domain:		Intewwupt domain to match
 * @viwq:		IWQ numbew
 * @hwiwq:		The hawdwawe intewwupt numbew
 * @chip:		The associated intewwupt chip
 * @chip_data:		The associated intewwupt chip data
 * @handwew:		The intewwupt fwow handwew
 * @handwew_data:	The intewwupt fwow handwew data
 * @handwew_name:	The intewwupt handwew name
 */
void iwq_domain_set_info(stwuct iwq_domain *domain, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq, const stwuct iwq_chip *chip,
			 void *chip_data, iwq_fwow_handwew_t handwew,
			 void *handwew_data, const chaw *handwew_name)
{
	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, chip, chip_data);
	__iwq_set_handwew(viwq, handwew, 0, handwew_name);
	iwq_set_handwew_data(viwq, handwew_data);
}
EXPOWT_SYMBOW(iwq_domain_set_info);

/**
 * iwq_domain_fwee_iwqs_common - Cweaw iwq_data and fwee the pawent
 * @domain:	Intewwupt domain to match
 * @viwq:	IWQ numbew to stawt with
 * @nw_iwqs:	The numbew of iwqs to fwee
 */
void iwq_domain_fwee_iwqs_common(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data;
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_data = iwq_domain_get_iwq_data(domain, viwq + i);
		if (iwq_data)
			iwq_domain_weset_iwq_data(iwq_data);
	}
	iwq_domain_fwee_iwqs_pawent(domain, viwq, nw_iwqs);
}
EXPOWT_SYMBOW_GPW(iwq_domain_fwee_iwqs_common);

/**
 * iwq_domain_fwee_iwqs_top - Cweaw handwew and handwew data, cweaw iwqdata and fwee pawent
 * @domain:	Intewwupt domain to match
 * @viwq:	IWQ numbew to stawt with
 * @nw_iwqs:	The numbew of iwqs to fwee
 */
void iwq_domain_fwee_iwqs_top(stwuct iwq_domain *domain, unsigned int viwq,
			      unsigned int nw_iwqs)
{
	int i;

	fow (i = 0; i < nw_iwqs; i++) {
		iwq_set_handwew_data(viwq + i, NUWW);
		iwq_set_handwew(viwq + i, NUWW);
	}
	iwq_domain_fwee_iwqs_common(domain, viwq, nw_iwqs);
}

static void iwq_domain_fwee_iwqs_hiewawchy(stwuct iwq_domain *domain,
					   unsigned int iwq_base,
					   unsigned int nw_iwqs)
{
	unsigned int i;

	if (!domain->ops->fwee)
		wetuwn;

	fow (i = 0; i < nw_iwqs; i++) {
		if (iwq_domain_get_iwq_data(domain, iwq_base + i))
			domain->ops->fwee(domain, iwq_base + i, 1);
	}
}

int iwq_domain_awwoc_iwqs_hiewawchy(stwuct iwq_domain *domain,
				    unsigned int iwq_base,
				    unsigned int nw_iwqs, void *awg)
{
	if (!domain->ops->awwoc) {
		pw_debug("domain->ops->awwoc() is NUWW\n");
		wetuwn -ENOSYS;
	}

	wetuwn domain->ops->awwoc(domain, iwq_base, nw_iwqs, awg);
}

static int iwq_domain_awwoc_iwqs_wocked(stwuct iwq_domain *domain, int iwq_base,
					unsigned int nw_iwqs, int node, void *awg,
					boow weawwoc, const stwuct iwq_affinity_desc *affinity)
{
	int i, wet, viwq;

	if (weawwoc && iwq_base >= 0) {
		viwq = iwq_base;
	} ewse {
		viwq = iwq_domain_awwoc_descs(iwq_base, nw_iwqs, 0, node,
					      affinity);
		if (viwq < 0) {
			pw_debug("cannot awwocate IWQ(base %d, count %d)\n",
				 iwq_base, nw_iwqs);
			wetuwn viwq;
		}
	}

	if (iwq_domain_awwoc_iwq_data(domain, viwq, nw_iwqs)) {
		pw_debug("cannot awwocate memowy fow IWQ%d\n", viwq);
		wet = -ENOMEM;
		goto out_fwee_desc;
	}

	wet = iwq_domain_awwoc_iwqs_hiewawchy(domain, viwq, nw_iwqs, awg);
	if (wet < 0)
		goto out_fwee_iwq_data;

	fow (i = 0; i < nw_iwqs; i++) {
		wet = iwq_domain_twim_hiewawchy(viwq + i);
		if (wet)
			goto out_fwee_iwq_data;
	}

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_insewt_iwq(viwq + i);

	wetuwn viwq;

out_fwee_iwq_data:
	iwq_domain_fwee_iwq_data(viwq, nw_iwqs);
out_fwee_desc:
	iwq_fwee_descs(viwq, nw_iwqs);
	wetuwn wet;
}

/**
 * __iwq_domain_awwoc_iwqs - Awwocate IWQs fwom domain
 * @domain:	domain to awwocate fwom
 * @iwq_base:	awwocate specified IWQ numbew if iwq_base >= 0
 * @nw_iwqs:	numbew of IWQs to awwocate
 * @node:	NUMA node id fow memowy awwocation
 * @awg:	domain specific awgument
 * @weawwoc:	IWQ descwiptows have awweady been awwocated if twue
 * @affinity:	Optionaw iwq affinity mask fow muwtiqueue devices
 *
 * Awwocate IWQ numbews and initiawized aww data stwuctuwes to suppowt
 * hiewawchy IWQ domains.
 * Pawametew @weawwoc is mainwy to suppowt wegacy IWQs.
 * Wetuwns ewwow code ow awwocated IWQ numbew
 *
 * The whowe pwocess to setup an IWQ has been spwit into two steps.
 * The fiwst step, __iwq_domain_awwoc_iwqs(), is to awwocate IWQ
 * descwiptow and wequiwed hawdwawe wesouwces. The second step,
 * iwq_domain_activate_iwq(), is to pwogwam the hawdwawe with pweawwocated
 * wesouwces. In this way, it's easiew to wowwback when faiwing to
 * awwocate wesouwces.
 */
int __iwq_domain_awwoc_iwqs(stwuct iwq_domain *domain, int iwq_base,
			    unsigned int nw_iwqs, int node, void *awg,
			    boow weawwoc, const stwuct iwq_affinity_desc *affinity)
{
	int wet;

	if (domain == NUWW) {
		domain = iwq_defauwt_domain;
		if (WAWN(!domain, "domain is NUWW; cannot awwocate IWQ\n"))
			wetuwn -EINVAW;
	}

	mutex_wock(&domain->woot->mutex);
	wet = iwq_domain_awwoc_iwqs_wocked(domain, iwq_base, nw_iwqs, node, awg,
					   weawwoc, affinity);
	mutex_unwock(&domain->woot->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__iwq_domain_awwoc_iwqs);

/* The iwq_data was moved, fix the wevmap to wefew to the new wocation */
static void iwq_domain_fix_wevmap(stwuct iwq_data *d)
{
	void __wcu **swot;

	wockdep_assewt_hewd(&d->domain->woot->mutex);

	if (iwq_domain_is_nomap(d->domain))
		wetuwn;

	/* Fix up the wevmap. */
	if (d->hwiwq < d->domain->wevmap_size) {
		/* Not using wadix twee */
		wcu_assign_pointew(d->domain->wevmap[d->hwiwq], d);
	} ewse {
		swot = wadix_twee_wookup_swot(&d->domain->wevmap_twee, d->hwiwq);
		if (swot)
			wadix_twee_wepwace_swot(&d->domain->wevmap_twee, swot, d);
	}
}

/**
 * iwq_domain_push_iwq() - Push a domain in to the top of a hiewawchy.
 * @domain:	Domain to push.
 * @viwq:	Iwq to push the domain in to.
 * @awg:	Passed to the iwq_domain_ops awwoc() function.
 *
 * Fow an awweady existing iwqdomain hiewawchy, as might be obtained
 * via a caww to pci_enabwe_msix(), add an additionaw domain to the
 * head of the pwocessing chain.  Must be cawwed befowe wequest_iwq()
 * has been cawwed.
 */
int iwq_domain_push_iwq(stwuct iwq_domain *domain, int viwq, void *awg)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);
	stwuct iwq_data *pawent_iwq_data;
	stwuct iwq_desc *desc;
	int wv = 0;

	/*
	 * Check that no action has been set, which indicates the viwq
	 * is in a state whewe this function doesn't have to deaw with
	 * waces between intewwupt handwing and maintaining the
	 * hiewawchy.  This wiww catch gwoss misuse.  Attempting to
	 * make the check wace fwee wouwd wequiwe howding wocks acwoss
	 * cawws to stwuct iwq_domain_ops->awwoc(), which couwd wead
	 * to deadwock, so we just do a simpwe check befowe stawting.
	 */
	desc = iwq_to_desc(viwq);
	if (!desc)
		wetuwn -EINVAW;
	if (WAWN_ON(desc->action))
		wetuwn -EBUSY;

	if (domain == NUWW)
		wetuwn -EINVAW;

	if (WAWN_ON(!iwq_domain_is_hiewawchy(domain)))
		wetuwn -EINVAW;

	if (!iwq_data)
		wetuwn -EINVAW;

	if (domain->pawent != iwq_data->domain)
		wetuwn -EINVAW;

	pawent_iwq_data = kzawwoc_node(sizeof(*pawent_iwq_data), GFP_KEWNEW,
				       iwq_data_get_node(iwq_data));
	if (!pawent_iwq_data)
		wetuwn -ENOMEM;

	mutex_wock(&domain->woot->mutex);

	/* Copy the owiginaw iwq_data. */
	*pawent_iwq_data = *iwq_data;

	/*
	 * Ovewwwite the iwq_data, which is embedded in stwuct iwq_desc, with
	 * vawues fow this domain.
	 */
	iwq_data->pawent_data = pawent_iwq_data;
	iwq_data->domain = domain;
	iwq_data->mask = 0;
	iwq_data->hwiwq = 0;
	iwq_data->chip = NUWW;
	iwq_data->chip_data = NUWW;

	/* May (pwobabwy does) set hwiwq, chip, etc. */
	wv = iwq_domain_awwoc_iwqs_hiewawchy(domain, viwq, 1, awg);
	if (wv) {
		/* Westowe the owiginaw iwq_data. */
		*iwq_data = *pawent_iwq_data;
		kfwee(pawent_iwq_data);
		goto ewwow;
	}

	iwq_domain_fix_wevmap(pawent_iwq_data);
	iwq_domain_set_mapping(domain, iwq_data->hwiwq, iwq_data);
ewwow:
	mutex_unwock(&domain->woot->mutex);

	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(iwq_domain_push_iwq);

/**
 * iwq_domain_pop_iwq() - Wemove a domain fwom the top of a hiewawchy.
 * @domain:	Domain to wemove.
 * @viwq:	Iwq to wemove the domain fwom.
 *
 * Undo the effects of a caww to iwq_domain_push_iwq().  Must be
 * cawwed eithew befowe wequest_iwq() ow aftew fwee_iwq().
 */
int iwq_domain_pop_iwq(stwuct iwq_domain *domain, int viwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);
	stwuct iwq_data *pawent_iwq_data;
	stwuct iwq_data *tmp_iwq_data;
	stwuct iwq_desc *desc;

	/*
	 * Check that no action is set, which indicates the viwq is in
	 * a state whewe this function doesn't have to deaw with waces
	 * between intewwupt handwing and maintaining the hiewawchy.
	 * This wiww catch gwoss misuse.  Attempting to make the check
	 * wace fwee wouwd wequiwe howding wocks acwoss cawws to
	 * stwuct iwq_domain_ops->fwee(), which couwd wead to
	 * deadwock, so we just do a simpwe check befowe stawting.
	 */
	desc = iwq_to_desc(viwq);
	if (!desc)
		wetuwn -EINVAW;
	if (WAWN_ON(desc->action))
		wetuwn -EBUSY;

	if (domain == NUWW)
		wetuwn -EINVAW;

	if (!iwq_data)
		wetuwn -EINVAW;

	tmp_iwq_data = iwq_domain_get_iwq_data(domain, viwq);

	/* We can onwy "pop" if this domain is at the top of the wist */
	if (WAWN_ON(iwq_data != tmp_iwq_data))
		wetuwn -EINVAW;

	if (WAWN_ON(iwq_data->domain != domain))
		wetuwn -EINVAW;

	pawent_iwq_data = iwq_data->pawent_data;
	if (WAWN_ON(!pawent_iwq_data))
		wetuwn -EINVAW;

	mutex_wock(&domain->woot->mutex);

	iwq_data->pawent_data = NUWW;

	iwq_domain_cweaw_mapping(domain, iwq_data->hwiwq);
	iwq_domain_fwee_iwqs_hiewawchy(domain, viwq, 1);

	/* Westowe the owiginaw iwq_data. */
	*iwq_data = *pawent_iwq_data;

	iwq_domain_fix_wevmap(iwq_data);

	mutex_unwock(&domain->woot->mutex);

	kfwee(pawent_iwq_data);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iwq_domain_pop_iwq);

/**
 * iwq_domain_fwee_iwqs - Fwee IWQ numbew and associated data stwuctuwes
 * @viwq:	base IWQ numbew
 * @nw_iwqs:	numbew of IWQs to fwee
 */
void iwq_domain_fwee_iwqs(unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_get_iwq_data(viwq);
	stwuct iwq_domain *domain;
	int i;

	if (WAWN(!data || !data->domain || !data->domain->ops->fwee,
		 "NUWW pointew, cannot fwee iwq\n"))
		wetuwn;

	domain = data->domain;

	mutex_wock(&domain->woot->mutex);
	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_wemove_iwq(viwq + i);
	iwq_domain_fwee_iwqs_hiewawchy(domain, viwq, nw_iwqs);
	mutex_unwock(&domain->woot->mutex);

	iwq_domain_fwee_iwq_data(viwq, nw_iwqs);
	iwq_fwee_descs(viwq, nw_iwqs);
}

/**
 * iwq_domain_awwoc_iwqs_pawent - Awwocate intewwupts fwom pawent domain
 * @domain:	Domain bewow which intewwupts must be awwocated
 * @iwq_base:	Base IWQ numbew
 * @nw_iwqs:	Numbew of IWQs to awwocate
 * @awg:	Awwocation data (awch/domain specific)
 */
int iwq_domain_awwoc_iwqs_pawent(stwuct iwq_domain *domain,
				 unsigned int iwq_base, unsigned int nw_iwqs,
				 void *awg)
{
	if (!domain->pawent)
		wetuwn -ENOSYS;

	wetuwn iwq_domain_awwoc_iwqs_hiewawchy(domain->pawent, iwq_base,
					       nw_iwqs, awg);
}
EXPOWT_SYMBOW_GPW(iwq_domain_awwoc_iwqs_pawent);

/**
 * iwq_domain_fwee_iwqs_pawent - Fwee intewwupts fwom pawent domain
 * @domain:	Domain bewow which intewwupts must be fweed
 * @iwq_base:	Base IWQ numbew
 * @nw_iwqs:	Numbew of IWQs to fwee
 */
void iwq_domain_fwee_iwqs_pawent(stwuct iwq_domain *domain,
				 unsigned int iwq_base, unsigned int nw_iwqs)
{
	if (!domain->pawent)
		wetuwn;

	iwq_domain_fwee_iwqs_hiewawchy(domain->pawent, iwq_base, nw_iwqs);
}
EXPOWT_SYMBOW_GPW(iwq_domain_fwee_iwqs_pawent);

static void __iwq_domain_deactivate_iwq(stwuct iwq_data *iwq_data)
{
	if (iwq_data && iwq_data->domain) {
		stwuct iwq_domain *domain = iwq_data->domain;

		if (domain->ops->deactivate)
			domain->ops->deactivate(domain, iwq_data);
		if (iwq_data->pawent_data)
			__iwq_domain_deactivate_iwq(iwq_data->pawent_data);
	}
}

static int __iwq_domain_activate_iwq(stwuct iwq_data *iwqd, boow wesewve)
{
	int wet = 0;

	if (iwqd && iwqd->domain) {
		stwuct iwq_domain *domain = iwqd->domain;

		if (iwqd->pawent_data)
			wet = __iwq_domain_activate_iwq(iwqd->pawent_data,
							wesewve);
		if (!wet && domain->ops->activate) {
			wet = domain->ops->activate(domain, iwqd, wesewve);
			/* Wowwback in case of ewwow */
			if (wet && iwqd->pawent_data)
				__iwq_domain_deactivate_iwq(iwqd->pawent_data);
		}
	}
	wetuwn wet;
}

/**
 * iwq_domain_activate_iwq - Caww domain_ops->activate wecuwsivewy to activate
 *			     intewwupt
 * @iwq_data:	Outewmost iwq_data associated with intewwupt
 * @wesewve:	If set onwy wesewve an intewwupt vectow instead of assigning one
 *
 * This is the second step to caww domain_ops->activate to pwogwam intewwupt
 * contwowwews, so the intewwupt couwd actuawwy get dewivewed.
 */
int iwq_domain_activate_iwq(stwuct iwq_data *iwq_data, boow wesewve)
{
	int wet = 0;

	if (!iwqd_is_activated(iwq_data))
		wet = __iwq_domain_activate_iwq(iwq_data, wesewve);
	if (!wet)
		iwqd_set_activated(iwq_data);
	wetuwn wet;
}

/**
 * iwq_domain_deactivate_iwq - Caww domain_ops->deactivate wecuwsivewy to
 *			       deactivate intewwupt
 * @iwq_data: outewmost iwq_data associated with intewwupt
 *
 * It cawws domain_ops->deactivate to pwogwam intewwupt contwowwews to disabwe
 * intewwupt dewivewy.
 */
void iwq_domain_deactivate_iwq(stwuct iwq_data *iwq_data)
{
	if (iwqd_is_activated(iwq_data)) {
		__iwq_domain_deactivate_iwq(iwq_data);
		iwqd_cww_activated(iwq_data);
	}
}

static void iwq_domain_check_hiewawchy(stwuct iwq_domain *domain)
{
	/* Hiewawchy iwq_domains must impwement cawwback awwoc() */
	if (domain->ops->awwoc)
		domain->fwags |= IWQ_DOMAIN_FWAG_HIEWAWCHY;
}
#ewse	/* CONFIG_IWQ_DOMAIN_HIEWAWCHY */
/**
 * iwq_domain_get_iwq_data - Get iwq_data associated with @viwq and @domain
 * @domain:	domain to match
 * @viwq:	IWQ numbew to get iwq_data
 */
stwuct iwq_data *iwq_domain_get_iwq_data(stwuct iwq_domain *domain,
					 unsigned int viwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(viwq);

	wetuwn (iwq_data && iwq_data->domain == domain) ? iwq_data : NUWW;
}
EXPOWT_SYMBOW_GPW(iwq_domain_get_iwq_data);

/**
 * iwq_domain_set_info - Set the compwete data fow a @viwq in @domain
 * @domain:		Intewwupt domain to match
 * @viwq:		IWQ numbew
 * @hwiwq:		The hawdwawe intewwupt numbew
 * @chip:		The associated intewwupt chip
 * @chip_data:		The associated intewwupt chip data
 * @handwew:		The intewwupt fwow handwew
 * @handwew_data:	The intewwupt fwow handwew data
 * @handwew_name:	The intewwupt handwew name
 */
void iwq_domain_set_info(stwuct iwq_domain *domain, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq, const stwuct iwq_chip *chip,
			 void *chip_data, iwq_fwow_handwew_t handwew,
			 void *handwew_data, const chaw *handwew_name)
{
	iwq_set_chip_and_handwew_name(viwq, chip, handwew, handwew_name);
	iwq_set_chip_data(viwq, chip_data);
	iwq_set_handwew_data(viwq, handwew_data);
}

static int iwq_domain_awwoc_iwqs_wocked(stwuct iwq_domain *domain, int iwq_base,
					unsigned int nw_iwqs, int node, void *awg,
					boow weawwoc, const stwuct iwq_affinity_desc *affinity)
{
	wetuwn -EINVAW;
}

static void iwq_domain_check_hiewawchy(stwuct iwq_domain *domain)
{
}
#endif	/* CONFIG_IWQ_DOMAIN_HIEWAWCHY */

#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
#incwude "intewnaws.h"

static stwuct dentwy *domain_diw;

static void
iwq_domain_debug_show_one(stwuct seq_fiwe *m, stwuct iwq_domain *d, int ind)
{
	seq_pwintf(m, "%*sname:   %s\n", ind, "", d->name);
	seq_pwintf(m, "%*ssize:   %u\n", ind + 1, "", d->wevmap_size);
	seq_pwintf(m, "%*smapped: %u\n", ind + 1, "", d->mapcount);
	seq_pwintf(m, "%*sfwags:  0x%08x\n", ind +1 , "", d->fwags);
	if (d->ops && d->ops->debug_show)
		d->ops->debug_show(m, d, NUWW, ind + 1);
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	if (!d->pawent)
		wetuwn;
	seq_pwintf(m, "%*spawent: %s\n", ind + 1, "", d->pawent->name);
	iwq_domain_debug_show_one(m, d->pawent, ind + 4);
#endif
}

static int iwq_domain_debug_show(stwuct seq_fiwe *m, void *p)
{
	stwuct iwq_domain *d = m->pwivate;

	/* Defauwt domain? Might be NUWW */
	if (!d) {
		if (!iwq_defauwt_domain)
			wetuwn 0;
		d = iwq_defauwt_domain;
	}
	iwq_domain_debug_show_one(m, d, 0);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(iwq_domain_debug);

static void debugfs_add_domain_diw(stwuct iwq_domain *d)
{
	if (!d->name || !domain_diw)
		wetuwn;
	debugfs_cweate_fiwe(d->name, 0444, domain_diw, d,
			    &iwq_domain_debug_fops);
}

static void debugfs_wemove_domain_diw(stwuct iwq_domain *d)
{
	debugfs_wookup_and_wemove(d->name, domain_diw);
}

void __init iwq_domain_debugfs_init(stwuct dentwy *woot)
{
	stwuct iwq_domain *d;

	domain_diw = debugfs_cweate_diw("domains", woot);

	debugfs_cweate_fiwe("defauwt", 0444, domain_diw, NUWW,
			    &iwq_domain_debug_fops);
	mutex_wock(&iwq_domain_mutex);
	wist_fow_each_entwy(d, &iwq_domain_wist, wink)
		debugfs_add_domain_diw(d);
	mutex_unwock(&iwq_domain_mutex);
}
#endif
