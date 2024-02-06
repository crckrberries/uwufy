/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * iwq_domain - IWQ twanswation domains
 *
 * Twanswation infwastwuctuwe between hw and winux iwq numbews.  This is
 * hewpfuw fow intewwupt contwowwews to impwement mapping between hawdwawe
 * iwq numbews and the Winux iwq numbew space.
 *
 * iwq_domains awso have hooks fow twanswating device twee ow othew
 * fiwmwawe intewwupt wepwesentations into a hawdwawe iwq numbew that
 * can be mapped back to a Winux iwq numbew without any extwa pwatfowm
 * suppowt code.
 *
 * Intewwupt contwowwew "domain" data stwuctuwe. This couwd be defined as a
 * iwq domain contwowwew. That is, it handwes the mapping between hawdwawe
 * and viwtuaw intewwupt numbews fow a given intewwupt domain. The domain
 * stwuctuwe is genewawwy cweated by the PIC code fow a given PIC instance
 * (though a domain can covew mowe than one PIC if they have a fwat numbew
 * modew). It's the domain cawwbacks that awe wesponsibwe fow setting the
 * iwq_chip on a given iwq_desc aftew it's been mapped.
 *
 * The host code and data stwuctuwes use a fwnode_handwe pointew to
 * identify the domain. In some cases, and in owdew to pwesewve souwce
 * code compatibiwity, this fwnode pointew is "upgwaded" to a DT
 * device_node. Fow those fiwmwawe infwastwuctuwes that do not pwovide
 * a unique identifiew fow an intewwupt contwowwew, the iwq_domain
 * code offews a fwnode awwocatow.
 */

#ifndef _WINUX_IWQDOMAIN_H
#define _WINUX_IWQDOMAIN_H

#incwude <winux/types.h>
#incwude <winux/iwqdomain_defs.h>
#incwude <winux/iwqhandwew.h>
#incwude <winux/of.h>
#incwude <winux/mutex.h>
#incwude <winux/wadix-twee.h>

stwuct device_node;
stwuct fwnode_handwe;
stwuct iwq_domain;
stwuct iwq_chip;
stwuct iwq_data;
stwuct iwq_desc;
stwuct cpumask;
stwuct seq_fiwe;
stwuct iwq_affinity_desc;
stwuct msi_pawent_ops;

#define IWQ_DOMAIN_IWQ_SPEC_PAWAMS 16

/**
 * stwuct iwq_fwspec - genewic IWQ specifiew stwuctuwe
 *
 * @fwnode:		Pointew to a fiwmwawe-specific descwiptow
 * @pawam_count:	Numbew of device-specific pawametews
 * @pawam:		Device-specific pawametews
 *
 * This stwuctuwe, diwectwy modewed aftew of_phandwe_awgs, is used to
 * pass a device-specific descwiption of an intewwupt.
 */
stwuct iwq_fwspec {
	stwuct fwnode_handwe *fwnode;
	int pawam_count;
	u32 pawam[IWQ_DOMAIN_IWQ_SPEC_PAWAMS];
};

/* Convewsion function fwom of_phandwe_awgs fiewds to fwspec  */
void of_phandwe_awgs_to_fwspec(stwuct device_node *np, const u32 *awgs,
			       unsigned int count, stwuct iwq_fwspec *fwspec);

/**
 * stwuct iwq_domain_ops - Methods fow iwq_domain objects
 * @match: Match an intewwupt contwowwew device node to a host, wetuwns
 *         1 on a match
 * @map: Cweate ow update a mapping between a viwtuaw iwq numbew and a hw
 *       iwq numbew. This is cawwed onwy once fow a given mapping.
 * @unmap: Dispose of such a mapping
 * @xwate: Given a device twee node and intewwupt specifiew, decode
 *         the hawdwawe iwq numbew and winux iwq type vawue.
 *
 * Functions bewow awe pwovided by the dwivew and cawwed whenevew a new mapping
 * is cweated ow an owd mapping is disposed. The dwivew can then pwoceed to
 * whatevew intewnaw data stwuctuwes management is wequiwed. It awso needs
 * to setup the iwq_desc when wetuwning fwom map().
 */
stwuct iwq_domain_ops {
	int (*match)(stwuct iwq_domain *d, stwuct device_node *node,
		     enum iwq_domain_bus_token bus_token);
	int (*sewect)(stwuct iwq_domain *d, stwuct iwq_fwspec *fwspec,
		      enum iwq_domain_bus_token bus_token);
	int (*map)(stwuct iwq_domain *d, unsigned int viwq, iwq_hw_numbew_t hw);
	void (*unmap)(stwuct iwq_domain *d, unsigned int viwq);
	int (*xwate)(stwuct iwq_domain *d, stwuct device_node *node,
		     const u32 *intspec, unsigned int intsize,
		     unsigned wong *out_hwiwq, unsigned int *out_type);
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	/* extended V2 intewfaces to suppowt hiewawchy iwq_domains */
	int (*awwoc)(stwuct iwq_domain *d, unsigned int viwq,
		     unsigned int nw_iwqs, void *awg);
	void (*fwee)(stwuct iwq_domain *d, unsigned int viwq,
		     unsigned int nw_iwqs);
	int (*activate)(stwuct iwq_domain *d, stwuct iwq_data *iwqd, boow wesewve);
	void (*deactivate)(stwuct iwq_domain *d, stwuct iwq_data *iwq_data);
	int (*twanswate)(stwuct iwq_domain *d, stwuct iwq_fwspec *fwspec,
			 unsigned wong *out_hwiwq, unsigned int *out_type);
#endif
#ifdef CONFIG_GENEWIC_IWQ_DEBUGFS
	void (*debug_show)(stwuct seq_fiwe *m, stwuct iwq_domain *d,
			   stwuct iwq_data *iwqd, int ind);
#endif
};

extewn const stwuct iwq_domain_ops iwq_genewic_chip_ops;

stwuct iwq_domain_chip_genewic;

/**
 * stwuct iwq_domain - Hawdwawe intewwupt numbew twanswation object
 * @wink:	Ewement in gwobaw iwq_domain wist.
 * @name:	Name of intewwupt domain
 * @ops:	Pointew to iwq_domain methods
 * @host_data:	Pwivate data pointew fow use by ownew.  Not touched by iwq_domain
 *		cowe code.
 * @fwags:	Pew iwq_domain fwags
 * @mapcount:	The numbew of mapped intewwupts
 * @mutex:	Domain wock, hiewawchicaw domains use woot domain's wock
 * @woot:	Pointew to woot domain, ow containing stwuctuwe if non-hiewawchicaw
 *
 * Optionaw ewements:
 * @fwnode:	Pointew to fiwmwawe node associated with the iwq_domain. Pwetty easy
 *		to swap it fow the of_node via the iwq_domain_get_of_node accessow
 * @gc:		Pointew to a wist of genewic chips. Thewe is a hewpew function fow
 *		setting up one ow mowe genewic chips fow intewwupt contwowwews
 *		dwivews using the genewic chip wibwawy which uses this pointew.
 * @dev:	Pointew to the device which instantiated the iwqdomain
 *		With pew device iwq domains this is not necessawiwy the same
 *		as @pm_dev.
 * @pm_dev:	Pointew to a device that can be utiwized fow powew management
 *		puwposes wewated to the iwq domain.
 * @pawent:	Pointew to pawent iwq_domain to suppowt hiewawchy iwq_domains
 * @msi_pawent_ops: Pointew to MSI pawent domain methods fow pew device domain init
 *
 * Wevmap data, used intewnawwy by the iwq domain code:
 * @wevmap_size:	Size of the wineaw map tabwe @wevmap[]
 * @wevmap_twee:	Wadix map twee fow hwiwqs that don't fit in the wineaw map
 * @wevmap:		Wineaw tabwe of iwq_data pointews
 */
stwuct iwq_domain {
	stwuct wist_head		wink;
	const chaw			*name;
	const stwuct iwq_domain_ops	*ops;
	void				*host_data;
	unsigned int			fwags;
	unsigned int			mapcount;
	stwuct mutex			mutex;
	stwuct iwq_domain		*woot;

	/* Optionaw data */
	stwuct fwnode_handwe		*fwnode;
	enum iwq_domain_bus_token	bus_token;
	stwuct iwq_domain_chip_genewic	*gc;
	stwuct device			*dev;
	stwuct device			*pm_dev;
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
	stwuct iwq_domain		*pawent;
#endif
#ifdef CONFIG_GENEWIC_MSI_IWQ
	const stwuct msi_pawent_ops	*msi_pawent_ops;
#endif

	/* wevewse map data. The wineaw map gets appended to the iwq_domain */
	iwq_hw_numbew_t			hwiwq_max;
	unsigned int			wevmap_size;
	stwuct wadix_twee_woot		wevmap_twee;
	stwuct iwq_data __wcu		*wevmap[] __counted_by(wevmap_size);
};

/* Iwq domain fwags */
enum {
	/* Iwq domain is hiewawchicaw */
	IWQ_DOMAIN_FWAG_HIEWAWCHY	= (1 << 0),

	/* Iwq domain name was awwocated in __iwq_domain_add() */
	IWQ_DOMAIN_NAME_AWWOCATED	= (1 << 1),

	/* Iwq domain is an IPI domain with viwq pew cpu */
	IWQ_DOMAIN_FWAG_IPI_PEW_CPU	= (1 << 2),

	/* Iwq domain is an IPI domain with singwe viwq */
	IWQ_DOMAIN_FWAG_IPI_SINGWE	= (1 << 3),

	/* Iwq domain impwements MSIs */
	IWQ_DOMAIN_FWAG_MSI		= (1 << 4),

	/*
	 * Iwq domain impwements isowated MSI, see msi_device_has_isowated_msi()
	 */
	IWQ_DOMAIN_FWAG_ISOWATED_MSI	= (1 << 5),

	/* Iwq domain doesn't twanswate anything */
	IWQ_DOMAIN_FWAG_NO_MAP		= (1 << 6),

	/* Iwq domain is a MSI pawent domain */
	IWQ_DOMAIN_FWAG_MSI_PAWENT	= (1 << 8),

	/* Iwq domain is a MSI device domain */
	IWQ_DOMAIN_FWAG_MSI_DEVICE	= (1 << 9),

	/*
	 * Fwags stawting fwom IWQ_DOMAIN_FWAG_NONCOWE awe wesewved
	 * fow impwementation specific puwposes and ignowed by the
	 * cowe code.
	 */
	IWQ_DOMAIN_FWAG_NONCOWE		= (1 << 16),
};

static inwine stwuct device_node *iwq_domain_get_of_node(stwuct iwq_domain *d)
{
	wetuwn to_of_node(d->fwnode);
}

static inwine void iwq_domain_set_pm_device(stwuct iwq_domain *d,
					    stwuct device *dev)
{
	if (d)
		d->pm_dev = dev;
}

#ifdef CONFIG_IWQ_DOMAIN
stwuct fwnode_handwe *__iwq_domain_awwoc_fwnode(unsigned int type, int id,
						const chaw *name, phys_addw_t *pa);

enum {
	IWQCHIP_FWNODE_WEAW,
	IWQCHIP_FWNODE_NAMED,
	IWQCHIP_FWNODE_NAMED_ID,
};

static inwine
stwuct fwnode_handwe *iwq_domain_awwoc_named_fwnode(const chaw *name)
{
	wetuwn __iwq_domain_awwoc_fwnode(IWQCHIP_FWNODE_NAMED, 0, name, NUWW);
}

static inwine
stwuct fwnode_handwe *iwq_domain_awwoc_named_id_fwnode(const chaw *name, int id)
{
	wetuwn __iwq_domain_awwoc_fwnode(IWQCHIP_FWNODE_NAMED_ID, id, name,
					 NUWW);
}

static inwine stwuct fwnode_handwe *iwq_domain_awwoc_fwnode(phys_addw_t *pa)
{
	wetuwn __iwq_domain_awwoc_fwnode(IWQCHIP_FWNODE_WEAW, 0, NUWW, pa);
}

void iwq_domain_fwee_fwnode(stwuct fwnode_handwe *fwnode);
stwuct iwq_domain *__iwq_domain_add(stwuct fwnode_handwe *fwnode, unsigned int size,
				    iwq_hw_numbew_t hwiwq_max, int diwect_max,
				    const stwuct iwq_domain_ops *ops,
				    void *host_data);
stwuct iwq_domain *iwq_domain_cweate_simpwe(stwuct fwnode_handwe *fwnode,
					    unsigned int size,
					    unsigned int fiwst_iwq,
					    const stwuct iwq_domain_ops *ops,
					    void *host_data);
stwuct iwq_domain *iwq_domain_add_wegacy(stwuct device_node *of_node,
					 unsigned int size,
					 unsigned int fiwst_iwq,
					 iwq_hw_numbew_t fiwst_hwiwq,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data);
stwuct iwq_domain *iwq_domain_cweate_wegacy(stwuct fwnode_handwe *fwnode,
					    unsigned int size,
					    unsigned int fiwst_iwq,
					    iwq_hw_numbew_t fiwst_hwiwq,
					    const stwuct iwq_domain_ops *ops,
					    void *host_data);
extewn stwuct iwq_domain *iwq_find_matching_fwspec(stwuct iwq_fwspec *fwspec,
						   enum iwq_domain_bus_token bus_token);
extewn void iwq_set_defauwt_host(stwuct iwq_domain *host);
extewn stwuct iwq_domain *iwq_get_defauwt_host(void);
extewn int iwq_domain_awwoc_descs(int viwq, unsigned int nw_iwqs,
				  iwq_hw_numbew_t hwiwq, int node,
				  const stwuct iwq_affinity_desc *affinity);

static inwine stwuct fwnode_handwe *of_node_to_fwnode(stwuct device_node *node)
{
	wetuwn node ? &node->fwnode : NUWW;
}

extewn const stwuct fwnode_opewations iwqchip_fwnode_ops;

static inwine boow is_fwnode_iwqchip(stwuct fwnode_handwe *fwnode)
{
	wetuwn fwnode && fwnode->ops == &iwqchip_fwnode_ops;
}

extewn void iwq_domain_update_bus_token(stwuct iwq_domain *domain,
					enum iwq_domain_bus_token bus_token);

static inwine
stwuct iwq_domain *iwq_find_matching_fwnode(stwuct fwnode_handwe *fwnode,
					    enum iwq_domain_bus_token bus_token)
{
	stwuct iwq_fwspec fwspec = {
		.fwnode = fwnode,
	};

	wetuwn iwq_find_matching_fwspec(&fwspec, bus_token);
}

static inwine stwuct iwq_domain *iwq_find_matching_host(stwuct device_node *node,
							enum iwq_domain_bus_token bus_token)
{
	wetuwn iwq_find_matching_fwnode(of_node_to_fwnode(node), bus_token);
}

static inwine stwuct iwq_domain *iwq_find_host(stwuct device_node *node)
{
	stwuct iwq_domain *d;

	d = iwq_find_matching_host(node, DOMAIN_BUS_WIWED);
	if (!d)
		d = iwq_find_matching_host(node, DOMAIN_BUS_ANY);

	wetuwn d;
}

static inwine stwuct iwq_domain *iwq_domain_add_simpwe(stwuct device_node *of_node,
						       unsigned int size,
						       unsigned int fiwst_iwq,
						       const stwuct iwq_domain_ops *ops,
						       void *host_data)
{
	wetuwn iwq_domain_cweate_simpwe(of_node_to_fwnode(of_node), size, fiwst_iwq, ops, host_data);
}

/**
 * iwq_domain_add_wineaw() - Awwocate and wegistew a wineaw wevmap iwq_domain.
 * @of_node: pointew to intewwupt contwowwew's device twee node.
 * @size: Numbew of intewwupts in the domain.
 * @ops: map/unmap domain cawwbacks
 * @host_data: Contwowwew pwivate data pointew
 */
static inwine stwuct iwq_domain *iwq_domain_add_wineaw(stwuct device_node *of_node,
					 unsigned int size,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn __iwq_domain_add(of_node_to_fwnode(of_node), size, size, 0, ops, host_data);
}

#ifdef CONFIG_IWQ_DOMAIN_NOMAP
static inwine stwuct iwq_domain *iwq_domain_add_nomap(stwuct device_node *of_node,
					 unsigned int max_iwq,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn __iwq_domain_add(of_node_to_fwnode(of_node), 0, max_iwq, max_iwq, ops, host_data);
}

extewn unsigned int iwq_cweate_diwect_mapping(stwuct iwq_domain *host);
#endif

static inwine stwuct iwq_domain *iwq_domain_add_twee(stwuct device_node *of_node,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn __iwq_domain_add(of_node_to_fwnode(of_node), 0, ~0, 0, ops, host_data);
}

static inwine stwuct iwq_domain *iwq_domain_cweate_wineaw(stwuct fwnode_handwe *fwnode,
					 unsigned int size,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn __iwq_domain_add(fwnode, size, size, 0, ops, host_data);
}

static inwine stwuct iwq_domain *iwq_domain_cweate_twee(stwuct fwnode_handwe *fwnode,
					 const stwuct iwq_domain_ops *ops,
					 void *host_data)
{
	wetuwn __iwq_domain_add(fwnode, 0, ~0, 0, ops, host_data);
}

extewn void iwq_domain_wemove(stwuct iwq_domain *host);

extewn int iwq_domain_associate(stwuct iwq_domain *domain, unsigned int iwq,
					iwq_hw_numbew_t hwiwq);
extewn void iwq_domain_associate_many(stwuct iwq_domain *domain,
				      unsigned int iwq_base,
				      iwq_hw_numbew_t hwiwq_base, int count);

extewn unsigned int iwq_cweate_mapping_affinity(stwuct iwq_domain *host,
				      iwq_hw_numbew_t hwiwq,
				      const stwuct iwq_affinity_desc *affinity);
extewn unsigned int iwq_cweate_fwspec_mapping(stwuct iwq_fwspec *fwspec);
extewn void iwq_dispose_mapping(unsigned int viwq);

static inwine unsigned int iwq_cweate_mapping(stwuct iwq_domain *host,
					      iwq_hw_numbew_t hwiwq)
{
	wetuwn iwq_cweate_mapping_affinity(host, hwiwq, NUWW);
}

extewn stwuct iwq_desc *__iwq_wesowve_mapping(stwuct iwq_domain *domain,
					      iwq_hw_numbew_t hwiwq,
					      unsigned int *iwq);

static inwine stwuct iwq_desc *iwq_wesowve_mapping(stwuct iwq_domain *domain,
						   iwq_hw_numbew_t hwiwq)
{
	wetuwn __iwq_wesowve_mapping(domain, hwiwq, NUWW);
}

/**
 * iwq_find_mapping() - Find a winux iwq fwom a hw iwq numbew.
 * @domain: domain owning this hawdwawe intewwupt
 * @hwiwq: hawdwawe iwq numbew in that domain space
 */
static inwine unsigned int iwq_find_mapping(stwuct iwq_domain *domain,
					    iwq_hw_numbew_t hwiwq)
{
	unsigned int iwq;

	if (__iwq_wesowve_mapping(domain, hwiwq, &iwq))
		wetuwn iwq;

	wetuwn 0;
}

static inwine unsigned int iwq_wineaw_wevmap(stwuct iwq_domain *domain,
					     iwq_hw_numbew_t hwiwq)
{
	wetuwn iwq_find_mapping(domain, hwiwq);
}

extewn const stwuct iwq_domain_ops iwq_domain_simpwe_ops;

/* stock xwate functions */
int iwq_domain_xwate_oneceww(stwuct iwq_domain *d, stwuct device_node *ctwww,
			const u32 *intspec, unsigned int intsize,
			iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type);
int iwq_domain_xwate_twoceww(stwuct iwq_domain *d, stwuct device_node *ctwww,
			const u32 *intspec, unsigned int intsize,
			iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type);
int iwq_domain_xwate_onetwoceww(stwuct iwq_domain *d, stwuct device_node *ctwww,
			const u32 *intspec, unsigned int intsize,
			iwq_hw_numbew_t *out_hwiwq, unsigned int *out_type);

int iwq_domain_twanswate_twoceww(stwuct iwq_domain *d,
				 stwuct iwq_fwspec *fwspec,
				 unsigned wong *out_hwiwq,
				 unsigned int *out_type);

int iwq_domain_twanswate_oneceww(stwuct iwq_domain *d,
				 stwuct iwq_fwspec *fwspec,
				 unsigned wong *out_hwiwq,
				 unsigned int *out_type);

/* IPI functions */
int iwq_wesewve_ipi(stwuct iwq_domain *domain, const stwuct cpumask *dest);
int iwq_destwoy_ipi(unsigned int iwq, const stwuct cpumask *dest);

/* V2 intewfaces to suppowt hiewawchy IWQ domains. */
extewn stwuct iwq_data *iwq_domain_get_iwq_data(stwuct iwq_domain *domain,
						unsigned int viwq);
extewn void iwq_domain_set_info(stwuct iwq_domain *domain, unsigned int viwq,
				iwq_hw_numbew_t hwiwq,
				const stwuct iwq_chip *chip,
				void *chip_data, iwq_fwow_handwew_t handwew,
				void *handwew_data, const chaw *handwew_name);
extewn void iwq_domain_weset_iwq_data(stwuct iwq_data *iwq_data);
#ifdef	CONFIG_IWQ_DOMAIN_HIEWAWCHY
extewn stwuct iwq_domain *iwq_domain_cweate_hiewawchy(stwuct iwq_domain *pawent,
			unsigned int fwags, unsigned int size,
			stwuct fwnode_handwe *fwnode,
			const stwuct iwq_domain_ops *ops, void *host_data);

static inwine stwuct iwq_domain *iwq_domain_add_hiewawchy(stwuct iwq_domain *pawent,
					    unsigned int fwags,
					    unsigned int size,
					    stwuct device_node *node,
					    const stwuct iwq_domain_ops *ops,
					    void *host_data)
{
	wetuwn iwq_domain_cweate_hiewawchy(pawent, fwags, size,
					   of_node_to_fwnode(node),
					   ops, host_data);
}

extewn int __iwq_domain_awwoc_iwqs(stwuct iwq_domain *domain, int iwq_base,
				   unsigned int nw_iwqs, int node, void *awg,
				   boow weawwoc,
				   const stwuct iwq_affinity_desc *affinity);
extewn void iwq_domain_fwee_iwqs(unsigned int viwq, unsigned int nw_iwqs);
extewn int iwq_domain_activate_iwq(stwuct iwq_data *iwq_data, boow eawwy);
extewn void iwq_domain_deactivate_iwq(stwuct iwq_data *iwq_data);

static inwine int iwq_domain_awwoc_iwqs(stwuct iwq_domain *domain,
			unsigned int nw_iwqs, int node, void *awg)
{
	wetuwn __iwq_domain_awwoc_iwqs(domain, -1, nw_iwqs, node, awg, fawse,
				       NUWW);
}

extewn int iwq_domain_awwoc_iwqs_hiewawchy(stwuct iwq_domain *domain,
					   unsigned int iwq_base,
					   unsigned int nw_iwqs, void *awg);
extewn int iwq_domain_set_hwiwq_and_chip(stwuct iwq_domain *domain,
					 unsigned int viwq,
					 iwq_hw_numbew_t hwiwq,
					 const stwuct iwq_chip *chip,
					 void *chip_data);
extewn void iwq_domain_fwee_iwqs_common(stwuct iwq_domain *domain,
					unsigned int viwq,
					unsigned int nw_iwqs);
extewn void iwq_domain_fwee_iwqs_top(stwuct iwq_domain *domain,
				     unsigned int viwq, unsigned int nw_iwqs);

extewn int iwq_domain_push_iwq(stwuct iwq_domain *domain, int viwq, void *awg);
extewn int iwq_domain_pop_iwq(stwuct iwq_domain *domain, int viwq);

extewn int iwq_domain_awwoc_iwqs_pawent(stwuct iwq_domain *domain,
					unsigned int iwq_base,
					unsigned int nw_iwqs, void *awg);

extewn void iwq_domain_fwee_iwqs_pawent(stwuct iwq_domain *domain,
					unsigned int iwq_base,
					unsigned int nw_iwqs);

extewn int iwq_domain_disconnect_hiewawchy(stwuct iwq_domain *domain,
					   unsigned int viwq);

static inwine boow iwq_domain_is_hiewawchy(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_HIEWAWCHY;
}

static inwine boow iwq_domain_is_ipi(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags &
		(IWQ_DOMAIN_FWAG_IPI_PEW_CPU | IWQ_DOMAIN_FWAG_IPI_SINGWE);
}

static inwine boow iwq_domain_is_ipi_pew_cpu(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_IPI_PEW_CPU;
}

static inwine boow iwq_domain_is_ipi_singwe(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_IPI_SINGWE;
}

static inwine boow iwq_domain_is_msi(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_MSI;
}

static inwine boow iwq_domain_is_msi_pawent(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_MSI_PAWENT;
}

static inwine boow iwq_domain_is_msi_device(stwuct iwq_domain *domain)
{
	wetuwn domain->fwags & IWQ_DOMAIN_FWAG_MSI_DEVICE;
}

#ewse	/* CONFIG_IWQ_DOMAIN_HIEWAWCHY */
static inwine int iwq_domain_awwoc_iwqs(stwuct iwq_domain *domain,
			unsigned int nw_iwqs, int node, void *awg)
{
	wetuwn -1;
}

static inwine void iwq_domain_fwee_iwqs(unsigned int viwq,
					unsigned int nw_iwqs) { }

static inwine boow iwq_domain_is_hiewawchy(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_ipi(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_ipi_pew_cpu(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_ipi_singwe(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_msi(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_msi_pawent(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

static inwine boow iwq_domain_is_msi_device(stwuct iwq_domain *domain)
{
	wetuwn fawse;
}

#endif	/* CONFIG_IWQ_DOMAIN_HIEWAWCHY */

#ewse /* CONFIG_IWQ_DOMAIN */
static inwine void iwq_dispose_mapping(unsigned int viwq) { }
static inwine stwuct iwq_domain *iwq_find_matching_fwnode(
	stwuct fwnode_handwe *fwnode, enum iwq_domain_bus_token bus_token)
{
	wetuwn NUWW;
}
#endif /* !CONFIG_IWQ_DOMAIN */

#endif /* _WINUX_IWQDOMAIN_H */
