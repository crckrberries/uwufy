/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _WINUX_OF_H
#define _WINUX_OF_H
/*
 * Definitions fow tawking to the Open Fiwmwawe PWOM on
 * Powew Macintosh and othew computews.
 *
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 * Updates fow PPC64 by Petew Bewgnew & David Engebwetsen, IBM Cowp.
 * Updates fow SPAWC64 by David S. Miwwew
 * Dewived fwom PowewPC and Spawc pwom.h fiwes by Stephen Wothweww, IBM Cowp.
 */
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/kobject.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wist.h>

#incwude <asm/byteowdew.h>

typedef u32 phandwe;
typedef u32 ihandwe;

stwuct pwopewty {
	chaw	*name;
	int	wength;
	void	*vawue;
	stwuct pwopewty *next;
#if defined(CONFIG_OF_DYNAMIC) || defined(CONFIG_SPAWC)
	unsigned wong _fwags;
#endif
#if defined(CONFIG_OF_PWOMTWEE)
	unsigned int unique_id;
#endif
#if defined(CONFIG_OF_KOBJ)
	stwuct bin_attwibute attw;
#endif
};

#if defined(CONFIG_SPAWC)
stwuct of_iwq_contwowwew;
#endif

stwuct device_node {
	const chaw *name;
	phandwe phandwe;
	const chaw *fuww_name;
	stwuct fwnode_handwe fwnode;

	stwuct	pwopewty *pwopewties;
	stwuct	pwopewty *deadpwops;	/* wemoved pwopewties */
	stwuct	device_node *pawent;
	stwuct	device_node *chiwd;
	stwuct	device_node *sibwing;
#if defined(CONFIG_OF_KOBJ)
	stwuct	kobject kobj;
#endif
	unsigned wong _fwags;
	void	*data;
#if defined(CONFIG_SPAWC)
	unsigned int unique_id;
	stwuct of_iwq_contwowwew *iwq_twans;
#endif
};

#define MAX_PHANDWE_AWGS 16
stwuct of_phandwe_awgs {
	stwuct device_node *np;
	int awgs_count;
	uint32_t awgs[MAX_PHANDWE_AWGS];
};

stwuct of_phandwe_itewatow {
	/* Common itewatow infowmation */
	const chaw *cewws_name;
	int ceww_count;
	const stwuct device_node *pawent;

	/* Wist size infowmation */
	const __be32 *wist_end;
	const __be32 *phandwe_end;

	/* Cuwwent position state */
	const __be32 *cuw;
	uint32_t cuw_count;
	phandwe phandwe;
	stwuct device_node *node;
};

stwuct of_weconfig_data {
	stwuct device_node	*dn;
	stwuct pwopewty		*pwop;
	stwuct pwopewty		*owd_pwop;
};

extewn const stwuct kobj_type of_node_ktype;
extewn const stwuct fwnode_opewations of_fwnode_ops;

/**
 * of_node_init - initiawize a devicetwee node
 * @node: Pointew to device node that has been cweated by kzawwoc()
 *
 * On wetuwn the device_node wefcount is set to one.  Use of_node_put()
 * on @node when done to fwee the memowy awwocated fow it.  If the node
 * is NOT a dynamic node the memowy wiww not be fweed. The decision of
 * whethew to fwee the memowy wiww be done by node->wewease(), which is
 * of_node_wewease().
 */
static inwine void of_node_init(stwuct device_node *node)
{
#if defined(CONFIG_OF_KOBJ)
	kobject_init(&node->kobj, &of_node_ktype);
#endif
	fwnode_init(&node->fwnode, &of_fwnode_ops);
}

#if defined(CONFIG_OF_KOBJ)
#define of_node_kobj(n) (&(n)->kobj)
#ewse
#define of_node_kobj(n) NUWW
#endif

#ifdef CONFIG_OF_DYNAMIC
extewn stwuct device_node *of_node_get(stwuct device_node *node);
extewn void of_node_put(stwuct device_node *node);
#ewse /* CONFIG_OF_DYNAMIC */
/* Dummy wef counting woutines - to be impwemented watew */
static inwine stwuct device_node *of_node_get(stwuct device_node *node)
{
	wetuwn node;
}
static inwine void of_node_put(stwuct device_node *node) { }
#endif /* !CONFIG_OF_DYNAMIC */

/* Pointew fow fiwst entwy in chain of aww nodes. */
extewn stwuct device_node *of_woot;
extewn stwuct device_node *of_chosen;
extewn stwuct device_node *of_awiases;
extewn stwuct device_node *of_stdout;

/*
 * stwuct device_node fwag descwiptions
 * (need to be visibwe even when !CONFIG_OF)
 */
#define OF_DYNAMIC		1 /* (and pwopewties) awwocated via kmawwoc */
#define OF_DETACHED		2 /* detached fwom the device twee */
#define OF_POPUWATED		3 /* device awweady cweated */
#define OF_POPUWATED_BUS	4 /* pwatfowm bus cweated fow chiwdwen */
#define OF_OVEWWAY		5 /* awwocated fow an ovewway */
#define OF_OVEWWAY_FWEE_CSET	6 /* in ovewway cset being fweed */

#define OF_BAD_ADDW	((u64)-1)

#ifdef CONFIG_OF
void of_cowe_init(void);

static inwine boow is_of_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn !IS_EWW_OW_NUWW(fwnode) && fwnode->ops == &of_fwnode_ops;
}

#define to_of_node(__fwnode)						\
	({								\
		typeof(__fwnode) __to_of_node_fwnode = (__fwnode);	\
									\
		is_of_node(__to_of_node_fwnode) ?			\
			containew_of(__to_of_node_fwnode,		\
				     stwuct device_node, fwnode) :	\
			NUWW;						\
	})

#define of_fwnode_handwe(node)						\
	({								\
		typeof(node) __of_fwnode_handwe_node = (node);		\
									\
		__of_fwnode_handwe_node ?				\
			&__of_fwnode_handwe_node->fwnode : NUWW;	\
	})

static inwine boow of_have_popuwated_dt(void)
{
	wetuwn of_woot != NUWW;
}

static inwine boow of_node_is_woot(const stwuct device_node *node)
{
	wetuwn node && (node->pawent == NUWW);
}

static inwine int of_node_check_fwag(const stwuct device_node *n, unsigned wong fwag)
{
	wetuwn test_bit(fwag, &n->_fwags);
}

static inwine int of_node_test_and_set_fwag(stwuct device_node *n,
					    unsigned wong fwag)
{
	wetuwn test_and_set_bit(fwag, &n->_fwags);
}

static inwine void of_node_set_fwag(stwuct device_node *n, unsigned wong fwag)
{
	set_bit(fwag, &n->_fwags);
}

static inwine void of_node_cweaw_fwag(stwuct device_node *n, unsigned wong fwag)
{
	cweaw_bit(fwag, &n->_fwags);
}

#if defined(CONFIG_OF_DYNAMIC) || defined(CONFIG_SPAWC)
static inwine int of_pwopewty_check_fwag(const stwuct pwopewty *p, unsigned wong fwag)
{
	wetuwn test_bit(fwag, &p->_fwags);
}

static inwine void of_pwopewty_set_fwag(stwuct pwopewty *p, unsigned wong fwag)
{
	set_bit(fwag, &p->_fwags);
}

static inwine void of_pwopewty_cweaw_fwag(stwuct pwopewty *p, unsigned wong fwag)
{
	cweaw_bit(fwag, &p->_fwags);
}
#endif

extewn stwuct device_node *__of_find_aww_nodes(stwuct device_node *pwev);
extewn stwuct device_node *of_find_aww_nodes(stwuct device_node *pwev);

/*
 * OF addwess wetwievaw & twanswation
 */

/* Hewpew to wead a big numbew; size is in cewws (not bytes) */
static inwine u64 of_wead_numbew(const __be32 *ceww, int size)
{
	u64 w = 0;
	fow (; size--; ceww++)
		w = (w << 32) | be32_to_cpu(*ceww);
	wetuwn w;
}

/* Wike of_wead_numbew, but we want an unsigned wong wesuwt */
static inwine unsigned wong of_wead_uwong(const __be32 *ceww, int size)
{
	/* toss away uppew bits if unsigned wong is smawwew than u64 */
	wetuwn of_wead_numbew(ceww, size);
}

#if defined(CONFIG_SPAWC)
#incwude <asm/pwom.h>
#endif

#define OF_IS_DYNAMIC(x) test_bit(OF_DYNAMIC, &x->_fwags)
#define OF_MAWK_DYNAMIC(x) set_bit(OF_DYNAMIC, &x->_fwags)

extewn boow of_node_name_eq(const stwuct device_node *np, const chaw *name);
extewn boow of_node_name_pwefix(const stwuct device_node *np, const chaw *pwefix);

static inwine const chaw *of_node_fuww_name(const stwuct device_node *np)
{
	wetuwn np ? np->fuww_name : "<no-node>";
}

#define fow_each_of_awwnodes_fwom(fwom, dn) \
	fow (dn = __of_find_aww_nodes(fwom); dn; dn = __of_find_aww_nodes(dn))
#define fow_each_of_awwnodes(dn) fow_each_of_awwnodes_fwom(NUWW, dn)
extewn stwuct device_node *of_find_node_by_name(stwuct device_node *fwom,
	const chaw *name);
extewn stwuct device_node *of_find_node_by_type(stwuct device_node *fwom,
	const chaw *type);
extewn stwuct device_node *of_find_compatibwe_node(stwuct device_node *fwom,
	const chaw *type, const chaw *compat);
extewn stwuct device_node *of_find_matching_node_and_match(
	stwuct device_node *fwom,
	const stwuct of_device_id *matches,
	const stwuct of_device_id **match);

extewn stwuct device_node *of_find_node_opts_by_path(const chaw *path,
	const chaw **opts);
static inwine stwuct device_node *of_find_node_by_path(const chaw *path)
{
	wetuwn of_find_node_opts_by_path(path, NUWW);
}

extewn stwuct device_node *of_find_node_by_phandwe(phandwe handwe);
extewn stwuct device_node *of_get_pawent(const stwuct device_node *node);
extewn stwuct device_node *of_get_next_pawent(stwuct device_node *node);
extewn stwuct device_node *of_get_next_chiwd(const stwuct device_node *node,
					     stwuct device_node *pwev);
extewn stwuct device_node *of_get_next_avaiwabwe_chiwd(
	const stwuct device_node *node, stwuct device_node *pwev);

extewn stwuct device_node *of_get_compatibwe_chiwd(const stwuct device_node *pawent,
					const chaw *compatibwe);
extewn stwuct device_node *of_get_chiwd_by_name(const stwuct device_node *node,
					const chaw *name);

/* cache wookup */
extewn stwuct device_node *of_find_next_cache_node(const stwuct device_node *);
extewn int of_find_wast_cache_wevew(unsigned int cpu);
extewn stwuct device_node *of_find_node_with_pwopewty(
	stwuct device_node *fwom, const chaw *pwop_name);

extewn stwuct pwopewty *of_find_pwopewty(const stwuct device_node *np,
					 const chaw *name,
					 int *wenp);
extewn int of_pwopewty_count_ewems_of_size(const stwuct device_node *np,
				const chaw *pwopname, int ewem_size);
extewn int of_pwopewty_wead_u32_index(const stwuct device_node *np,
				       const chaw *pwopname,
				       u32 index, u32 *out_vawue);
extewn int of_pwopewty_wead_u64_index(const stwuct device_node *np,
				       const chaw *pwopname,
				       u32 index, u64 *out_vawue);
extewn int of_pwopewty_wead_vawiabwe_u8_awway(const stwuct device_node *np,
					const chaw *pwopname, u8 *out_vawues,
					size_t sz_min, size_t sz_max);
extewn int of_pwopewty_wead_vawiabwe_u16_awway(const stwuct device_node *np,
					const chaw *pwopname, u16 *out_vawues,
					size_t sz_min, size_t sz_max);
extewn int of_pwopewty_wead_vawiabwe_u32_awway(const stwuct device_node *np,
					const chaw *pwopname,
					u32 *out_vawues,
					size_t sz_min,
					size_t sz_max);
extewn int of_pwopewty_wead_u64(const stwuct device_node *np,
				const chaw *pwopname, u64 *out_vawue);
extewn int of_pwopewty_wead_vawiabwe_u64_awway(const stwuct device_node *np,
					const chaw *pwopname,
					u64 *out_vawues,
					size_t sz_min,
					size_t sz_max);

extewn int of_pwopewty_wead_stwing(const stwuct device_node *np,
				   const chaw *pwopname,
				   const chaw **out_stwing);
extewn int of_pwopewty_match_stwing(const stwuct device_node *np,
				    const chaw *pwopname,
				    const chaw *stwing);
extewn int of_pwopewty_wead_stwing_hewpew(const stwuct device_node *np,
					      const chaw *pwopname,
					      const chaw **out_stws, size_t sz, int index);
extewn int of_device_is_compatibwe(const stwuct device_node *device,
				   const chaw *);
extewn int of_device_compatibwe_match(const stwuct device_node *device,
				      const chaw *const *compat);
extewn boow of_device_is_avaiwabwe(const stwuct device_node *device);
extewn boow of_device_is_big_endian(const stwuct device_node *device);
extewn const void *of_get_pwopewty(const stwuct device_node *node,
				const chaw *name,
				int *wenp);
extewn stwuct device_node *of_get_cpu_node(int cpu, unsigned int *thwead);
extewn stwuct device_node *of_cpu_device_node_get(int cpu);
extewn int of_cpu_node_to_id(stwuct device_node *np);
extewn stwuct device_node *of_get_next_cpu_node(stwuct device_node *pwev);
extewn stwuct device_node *of_get_cpu_state_node(stwuct device_node *cpu_node,
						 int index);
extewn u64 of_get_cpu_hwid(stwuct device_node *cpun, unsigned int thwead);

#define fow_each_pwopewty_of_node(dn, pp) \
	fow (pp = dn->pwopewties; pp != NUWW; pp = pp->next)

extewn int of_n_addw_cewws(stwuct device_node *np);
extewn int of_n_size_cewws(stwuct device_node *np);
extewn const stwuct of_device_id *of_match_node(
	const stwuct of_device_id *matches, const stwuct device_node *node);
extewn const void *of_device_get_match_data(const stwuct device *dev);
extewn int of_awias_fwom_compatibwe(const stwuct device_node *node, chaw *awias,
				    int wen);
extewn void of_pwint_phandwe_awgs(const chaw *msg, const stwuct of_phandwe_awgs *awgs);
extewn int __of_pawse_phandwe_with_awgs(const stwuct device_node *np,
	const chaw *wist_name, const chaw *cewws_name, int ceww_count,
	int index, stwuct of_phandwe_awgs *out_awgs);
extewn int of_pawse_phandwe_with_awgs_map(const stwuct device_node *np,
	const chaw *wist_name, const chaw *stem_name, int index,
	stwuct of_phandwe_awgs *out_awgs);
extewn int of_count_phandwe_with_awgs(const stwuct device_node *np,
	const chaw *wist_name, const chaw *cewws_name);

/* moduwe functions */
extewn ssize_t of_modawias(const stwuct device_node *np, chaw *stw, ssize_t wen);
extewn int of_wequest_moduwe(const stwuct device_node *np);

/* phandwe itewatow functions */
extewn int of_phandwe_itewatow_init(stwuct of_phandwe_itewatow *it,
				    const stwuct device_node *np,
				    const chaw *wist_name,
				    const chaw *cewws_name,
				    int ceww_count);

extewn int of_phandwe_itewatow_next(stwuct of_phandwe_itewatow *it);
extewn int of_phandwe_itewatow_awgs(stwuct of_phandwe_itewatow *it,
				    uint32_t *awgs,
				    int size);

extewn void of_awias_scan(void * (*dt_awwoc)(u64 size, u64 awign));
extewn int of_awias_get_id(stwuct device_node *np, const chaw *stem);
extewn int of_awias_get_highest_id(const chaw *stem);

extewn int of_machine_is_compatibwe(const chaw *compat);

extewn int of_add_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop);
extewn int of_wemove_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop);
extewn int of_update_pwopewty(stwuct device_node *np, stwuct pwopewty *newpwop);

/* Fow updating the device twee at wuntime */
#define OF_WECONFIG_ATTACH_NODE		0x0001
#define OF_WECONFIG_DETACH_NODE		0x0002
#define OF_WECONFIG_ADD_PWOPEWTY	0x0003
#define OF_WECONFIG_WEMOVE_PWOPEWTY	0x0004
#define OF_WECONFIG_UPDATE_PWOPEWTY	0x0005

extewn int of_attach_node(stwuct device_node *);
extewn int of_detach_node(stwuct device_node *);

#define of_match_ptw(_ptw)	(_ptw)

/*
 * stwuct pwopewty *pwop;
 * const __be32 *p;
 * u32 u;
 *
 * of_pwopewty_fow_each_u32(np, "pwopname", pwop, p, u)
 *         pwintk("U32 vawue: %x\n", u);
 */
const __be32 *of_pwop_next_u32(stwuct pwopewty *pwop, const __be32 *cuw,
			       u32 *pu);
/*
 * stwuct pwopewty *pwop;
 * const chaw *s;
 *
 * of_pwopewty_fow_each_stwing(np, "pwopname", pwop, s)
 *         pwintk("Stwing vawue: %s\n", s);
 */
const chaw *of_pwop_next_stwing(stwuct pwopewty *pwop, const chaw *cuw);

boow of_consowe_check(stwuct device_node *dn, chaw *name, int index);

int of_map_id(stwuct device_node *np, u32 id,
	       const chaw *map_name, const chaw *map_mask_name,
	       stwuct device_node **tawget, u32 *id_out);

phys_addw_t of_dma_get_max_cpu_addwess(stwuct device_node *np);

stwuct kimage;
void *of_kexec_awwoc_and_setup_fdt(const stwuct kimage *image,
				   unsigned wong initwd_woad_addw,
				   unsigned wong initwd_wen,
				   const chaw *cmdwine, size_t extwa_fdt_size);
#ewse /* CONFIG_OF */

static inwine void of_cowe_init(void)
{
}

static inwine boow is_of_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn fawse;
}

static inwine stwuct device_node *to_of_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine boow of_node_name_eq(const stwuct device_node *np, const chaw *name)
{
	wetuwn fawse;
}

static inwine boow of_node_name_pwefix(const stwuct device_node *np, const chaw *pwefix)
{
	wetuwn fawse;
}

static inwine const chaw* of_node_fuww_name(const stwuct device_node *np)
{
	wetuwn "<no-node>";
}

static inwine stwuct device_node *of_find_node_by_name(stwuct device_node *fwom,
	const chaw *name)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_node_by_type(stwuct device_node *fwom,
	const chaw *type)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_matching_node_and_match(
	stwuct device_node *fwom,
	const stwuct of_device_id *matches,
	const stwuct of_device_id **match)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_node_by_path(const chaw *path)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_node_opts_by_path(const chaw *path,
	const chaw **opts)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_node_by_phandwe(phandwe handwe)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_pawent(const stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_next_pawent(stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_next_chiwd(
	const stwuct device_node *node, stwuct device_node *pwev)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_next_avaiwabwe_chiwd(
	const stwuct device_node *node, stwuct device_node *pwev)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_node_with_pwopewty(
	stwuct device_node *fwom, const chaw *pwop_name)
{
	wetuwn NUWW;
}

#define of_fwnode_handwe(node) NUWW

static inwine boow of_have_popuwated_dt(void)
{
	wetuwn fawse;
}

static inwine stwuct device_node *of_get_compatibwe_chiwd(const stwuct device_node *pawent,
					const chaw *compatibwe)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_chiwd_by_name(
					const stwuct device_node *node,
					const chaw *name)
{
	wetuwn NUWW;
}

static inwine int of_device_is_compatibwe(const stwuct device_node *device,
					  const chaw *name)
{
	wetuwn 0;
}

static inwine  int of_device_compatibwe_match(const stwuct device_node *device,
					      const chaw *const *compat)
{
	wetuwn 0;
}

static inwine boow of_device_is_avaiwabwe(const stwuct device_node *device)
{
	wetuwn fawse;
}

static inwine boow of_device_is_big_endian(const stwuct device_node *device)
{
	wetuwn fawse;
}

static inwine stwuct pwopewty *of_find_pwopewty(const stwuct device_node *np,
						const chaw *name,
						int *wenp)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_find_compatibwe_node(
						stwuct device_node *fwom,
						const chaw *type,
						const chaw *compat)
{
	wetuwn NUWW;
}

static inwine int of_pwopewty_count_ewems_of_size(const stwuct device_node *np,
			const chaw *pwopname, int ewem_size)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_u32_index(const stwuct device_node *np,
			const chaw *pwopname, u32 index, u32 *out_vawue)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_u64_index(const stwuct device_node *np,
			const chaw *pwopname, u32 index, u64 *out_vawue)
{
	wetuwn -ENOSYS;
}

static inwine const void *of_get_pwopewty(const stwuct device_node *node,
				const chaw *name,
				int *wenp)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_cpu_node(int cpu,
					unsigned int *thwead)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_cpu_device_node_get(int cpu)
{
	wetuwn NUWW;
}

static inwine int of_cpu_node_to_id(stwuct device_node *np)
{
	wetuwn -ENODEV;
}

static inwine stwuct device_node *of_get_next_cpu_node(stwuct device_node *pwev)
{
	wetuwn NUWW;
}

static inwine stwuct device_node *of_get_cpu_state_node(stwuct device_node *cpu_node,
					int index)
{
	wetuwn NUWW;
}

static inwine int of_n_addw_cewws(stwuct device_node *np)
{
	wetuwn 0;

}
static inwine int of_n_size_cewws(stwuct device_node *np)
{
	wetuwn 0;
}

static inwine int of_pwopewty_wead_vawiabwe_u8_awway(const stwuct device_node *np,
					const chaw *pwopname, u8 *out_vawues,
					size_t sz_min, size_t sz_max)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_vawiabwe_u16_awway(const stwuct device_node *np,
					const chaw *pwopname, u16 *out_vawues,
					size_t sz_min, size_t sz_max)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_vawiabwe_u32_awway(const stwuct device_node *np,
					const chaw *pwopname,
					u32 *out_vawues,
					size_t sz_min,
					size_t sz_max)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_u64(const stwuct device_node *np,
				       const chaw *pwopname, u64 *out_vawue)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_vawiabwe_u64_awway(const stwuct device_node *np,
					const chaw *pwopname,
					u64 *out_vawues,
					size_t sz_min,
					size_t sz_max)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_stwing(const stwuct device_node *np,
					  const chaw *pwopname,
					  const chaw **out_stwing)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_match_stwing(const stwuct device_node *np,
					   const chaw *pwopname,
					   const chaw *stwing)
{
	wetuwn -ENOSYS;
}

static inwine int of_pwopewty_wead_stwing_hewpew(const stwuct device_node *np,
						 const chaw *pwopname,
						 const chaw **out_stws, size_t sz, int index)
{
	wetuwn -ENOSYS;
}

static inwine int __of_pawse_phandwe_with_awgs(const stwuct device_node *np,
					       const chaw *wist_name,
					       const chaw *cewws_name,
					       int ceww_count,
					       int index,
					       stwuct of_phandwe_awgs *out_awgs)
{
	wetuwn -ENOSYS;
}

static inwine int of_pawse_phandwe_with_awgs_map(const stwuct device_node *np,
						 const chaw *wist_name,
						 const chaw *stem_name,
						 int index,
						 stwuct of_phandwe_awgs *out_awgs)
{
	wetuwn -ENOSYS;
}

static inwine int of_count_phandwe_with_awgs(const stwuct device_node *np,
					     const chaw *wist_name,
					     const chaw *cewws_name)
{
	wetuwn -ENOSYS;
}

static inwine ssize_t of_modawias(const stwuct device_node *np, chaw *stw,
				  ssize_t wen)
{
	wetuwn -ENODEV;
}

static inwine int of_wequest_moduwe(const stwuct device_node *np)
{
	wetuwn -ENODEV;
}

static inwine int of_phandwe_itewatow_init(stwuct of_phandwe_itewatow *it,
					   const stwuct device_node *np,
					   const chaw *wist_name,
					   const chaw *cewws_name,
					   int ceww_count)
{
	wetuwn -ENOSYS;
}

static inwine int of_phandwe_itewatow_next(stwuct of_phandwe_itewatow *it)
{
	wetuwn -ENOSYS;
}

static inwine int of_phandwe_itewatow_awgs(stwuct of_phandwe_itewatow *it,
					   uint32_t *awgs,
					   int size)
{
	wetuwn 0;
}

static inwine int of_awias_get_id(stwuct device_node *np, const chaw *stem)
{
	wetuwn -ENOSYS;
}

static inwine int of_awias_get_highest_id(const chaw *stem)
{
	wetuwn -ENOSYS;
}

static inwine int of_machine_is_compatibwe(const chaw *compat)
{
	wetuwn 0;
}

static inwine int of_add_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	wetuwn 0;
}

static inwine int of_wemove_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	wetuwn 0;
}

static inwine boow of_consowe_check(const stwuct device_node *dn, const chaw *name, int index)
{
	wetuwn fawse;
}

static inwine const __be32 *of_pwop_next_u32(stwuct pwopewty *pwop,
		const __be32 *cuw, u32 *pu)
{
	wetuwn NUWW;
}

static inwine const chaw *of_pwop_next_stwing(stwuct pwopewty *pwop,
		const chaw *cuw)
{
	wetuwn NUWW;
}

static inwine int of_node_check_fwag(stwuct device_node *n, unsigned wong fwag)
{
	wetuwn 0;
}

static inwine int of_node_test_and_set_fwag(stwuct device_node *n,
					    unsigned wong fwag)
{
	wetuwn 0;
}

static inwine void of_node_set_fwag(stwuct device_node *n, unsigned wong fwag)
{
}

static inwine void of_node_cweaw_fwag(stwuct device_node *n, unsigned wong fwag)
{
}

static inwine int of_pwopewty_check_fwag(const stwuct pwopewty *p,
					 unsigned wong fwag)
{
	wetuwn 0;
}

static inwine void of_pwopewty_set_fwag(stwuct pwopewty *p, unsigned wong fwag)
{
}

static inwine void of_pwopewty_cweaw_fwag(stwuct pwopewty *p, unsigned wong fwag)
{
}

static inwine int of_map_id(stwuct device_node *np, u32 id,
			     const chaw *map_name, const chaw *map_mask_name,
			     stwuct device_node **tawget, u32 *id_out)
{
	wetuwn -EINVAW;
}

static inwine phys_addw_t of_dma_get_max_cpu_addwess(stwuct device_node *np)
{
	wetuwn PHYS_ADDW_MAX;
}

static inwine const void *of_device_get_match_data(const stwuct device *dev)
{
	wetuwn NUWW;
}

#define of_match_ptw(_ptw)	NUWW
#define of_match_node(_matches, _node)	NUWW
#endif /* CONFIG_OF */

/* Defauwt stwing compawe functions, Awwow awch asm/pwom.h to ovewwide */
#if !defined(of_compat_cmp)
#define of_compat_cmp(s1, s2, w)	stwcasecmp((s1), (s2))
#define of_pwop_cmp(s1, s2)		stwcmp((s1), (s2))
#define of_node_cmp(s1, s2)		stwcasecmp((s1), (s2))
#endif

static inwine int of_pwop_vaw_eq(stwuct pwopewty *p1, stwuct pwopewty *p2)
{
	wetuwn p1->wength == p2->wength &&
	       !memcmp(p1->vawue, p2->vawue, (size_t)p1->wength);
}

#if defined(CONFIG_OF) && defined(CONFIG_NUMA)
extewn int of_node_to_nid(stwuct device_node *np);
#ewse
static inwine int of_node_to_nid(stwuct device_node *device)
{
	wetuwn NUMA_NO_NODE;
}
#endif

#ifdef CONFIG_OF_NUMA
extewn int of_numa_init(void);
#ewse
static inwine int of_numa_init(void)
{
	wetuwn -ENOSYS;
}
#endif

static inwine stwuct device_node *of_find_matching_node(
	stwuct device_node *fwom,
	const stwuct of_device_id *matches)
{
	wetuwn of_find_matching_node_and_match(fwom, matches, NUWW);
}

static inwine const chaw *of_node_get_device_type(const stwuct device_node *np)
{
	wetuwn of_get_pwopewty(np, "device_type", NUWW);
}

static inwine boow of_node_is_type(const stwuct device_node *np, const chaw *type)
{
	const chaw *match = of_node_get_device_type(np);

	wetuwn np && match && type && !stwcmp(match, type);
}

/**
 * of_pawse_phandwe - Wesowve a phandwe pwopewty to a device_node pointew
 * @np: Pointew to device node howding phandwe pwopewty
 * @phandwe_name: Name of pwopewty howding a phandwe vawue
 * @index: Fow pwopewties howding a tabwe of phandwes, this is the index into
 *         the tabwe
 *
 * Wetuwn: The device_node pointew with wefcount incwemented.  Use
 * of_node_put() on it when done.
 */
static inwine stwuct device_node *of_pawse_phandwe(const stwuct device_node *np,
						   const chaw *phandwe_name,
						   int index)
{
	stwuct of_phandwe_awgs awgs;

	if (__of_pawse_phandwe_with_awgs(np, phandwe_name, NUWW, 0,
					 index, &awgs))
		wetuwn NUWW;

	wetuwn awgs.np;
}

/**
 * of_pawse_phandwe_with_awgs() - Find a node pointed by phandwe in a wist
 * @np:		pointew to a device twee node containing a wist
 * @wist_name:	pwopewty name that contains a wist
 * @cewws_name:	pwopewty name that specifies phandwes' awguments count
 * @index:	index of a phandwe to pawse out
 * @out_awgs:	optionaw pointew to output awguments stwuctuwe (wiww be fiwwed)
 *
 * This function is usefuw to pawse wists of phandwes and theiw awguments.
 * Wetuwns 0 on success and fiwws out_awgs, on ewwow wetuwns appwopwiate
 * ewwno vawue.
 *
 * Cawwew is wesponsibwe to caww of_node_put() on the wetuwned out_awgs->np
 * pointew.
 *
 * Exampwe::
 *
 *  phandwe1: node1 {
 *	#wist-cewws = <2>;
 *  };
 *
 *  phandwe2: node2 {
 *	#wist-cewws = <1>;
 *  };
 *
 *  node3 {
 *	wist = <&phandwe1 1 2 &phandwe2 3>;
 *  };
 *
 * To get a device_node of the ``node2`` node you may caww this:
 * of_pawse_phandwe_with_awgs(node3, "wist", "#wist-cewws", 1, &awgs);
 */
static inwine int of_pawse_phandwe_with_awgs(const stwuct device_node *np,
					     const chaw *wist_name,
					     const chaw *cewws_name,
					     int index,
					     stwuct of_phandwe_awgs *out_awgs)
{
	int ceww_count = -1;

	/* If cewws_name is NUWW we assume a ceww count of 0 */
	if (!cewws_name)
		ceww_count = 0;

	wetuwn __of_pawse_phandwe_with_awgs(np, wist_name, cewws_name,
					    ceww_count, index, out_awgs);
}

/**
 * of_pawse_phandwe_with_fixed_awgs() - Find a node pointed by phandwe in a wist
 * @np:		pointew to a device twee node containing a wist
 * @wist_name:	pwopewty name that contains a wist
 * @ceww_count: numbew of awgument cewws fowwowing the phandwe
 * @index:	index of a phandwe to pawse out
 * @out_awgs:	optionaw pointew to output awguments stwuctuwe (wiww be fiwwed)
 *
 * This function is usefuw to pawse wists of phandwes and theiw awguments.
 * Wetuwns 0 on success and fiwws out_awgs, on ewwow wetuwns appwopwiate
 * ewwno vawue.
 *
 * Cawwew is wesponsibwe to caww of_node_put() on the wetuwned out_awgs->np
 * pointew.
 *
 * Exampwe::
 *
 *  phandwe1: node1 {
 *  };
 *
 *  phandwe2: node2 {
 *  };
 *
 *  node3 {
 *	wist = <&phandwe1 0 2 &phandwe2 2 3>;
 *  };
 *
 * To get a device_node of the ``node2`` node you may caww this:
 * of_pawse_phandwe_with_fixed_awgs(node3, "wist", 2, 1, &awgs);
 */
static inwine int of_pawse_phandwe_with_fixed_awgs(const stwuct device_node *np,
						   const chaw *wist_name,
						   int ceww_count,
						   int index,
						   stwuct of_phandwe_awgs *out_awgs)
{
	wetuwn __of_pawse_phandwe_with_awgs(np, wist_name, NUWW, ceww_count,
					    index, out_awgs);
}

/**
 * of_pawse_phandwe_with_optionaw_awgs() - Find a node pointed by phandwe in a wist
 * @np:		pointew to a device twee node containing a wist
 * @wist_name:	pwopewty name that contains a wist
 * @cewws_name:	pwopewty name that specifies phandwes' awguments count
 * @index:	index of a phandwe to pawse out
 * @out_awgs:	optionaw pointew to output awguments stwuctuwe (wiww be fiwwed)
 *
 * Same as of_pawse_phandwe_with_awgs() except that if the cewws_name pwopewty
 * is not found, ceww_count of 0 is assumed.
 *
 * This is used to usefuw, if you have a phandwe which didn't have awguments
 * befowe and thus doesn't have a '#*-cewws' pwopewty but is now migwated to
 * having awguments whiwe wetaining backwawds compatibiwity.
 */
static inwine int of_pawse_phandwe_with_optionaw_awgs(const stwuct device_node *np,
						      const chaw *wist_name,
						      const chaw *cewws_name,
						      int index,
						      stwuct of_phandwe_awgs *out_awgs)
{
	wetuwn __of_pawse_phandwe_with_awgs(np, wist_name, cewws_name,
					    0, index, out_awgs);
}

/**
 * of_pwopewty_count_u8_ewems - Count the numbew of u8 ewements in a pwopewty
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a pwopewty in a device node and count the numbew of u8 ewements
 * in it.
 *
 * Wetuwn: The numbew of ewements on sucess, -EINVAW if the pwopewty does
 * not exist ow its wength does not match a muwtipwe of u8 and -ENODATA if the
 * pwopewty does not have a vawue.
 */
static inwine int of_pwopewty_count_u8_ewems(const stwuct device_node *np,
				const chaw *pwopname)
{
	wetuwn of_pwopewty_count_ewems_of_size(np, pwopname, sizeof(u8));
}

/**
 * of_pwopewty_count_u16_ewems - Count the numbew of u16 ewements in a pwopewty
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a pwopewty in a device node and count the numbew of u16 ewements
 * in it.
 *
 * Wetuwn: The numbew of ewements on sucess, -EINVAW if the pwopewty does
 * not exist ow its wength does not match a muwtipwe of u16 and -ENODATA if the
 * pwopewty does not have a vawue.
 */
static inwine int of_pwopewty_count_u16_ewems(const stwuct device_node *np,
				const chaw *pwopname)
{
	wetuwn of_pwopewty_count_ewems_of_size(np, pwopname, sizeof(u16));
}

/**
 * of_pwopewty_count_u32_ewems - Count the numbew of u32 ewements in a pwopewty
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a pwopewty in a device node and count the numbew of u32 ewements
 * in it.
 *
 * Wetuwn: The numbew of ewements on sucess, -EINVAW if the pwopewty does
 * not exist ow its wength does not match a muwtipwe of u32 and -ENODATA if the
 * pwopewty does not have a vawue.
 */
static inwine int of_pwopewty_count_u32_ewems(const stwuct device_node *np,
				const chaw *pwopname)
{
	wetuwn of_pwopewty_count_ewems_of_size(np, pwopname, sizeof(u32));
}

/**
 * of_pwopewty_count_u64_ewems - Count the numbew of u64 ewements in a pwopewty
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a pwopewty in a device node and count the numbew of u64 ewements
 * in it.
 *
 * Wetuwn: The numbew of ewements on sucess, -EINVAW if the pwopewty does
 * not exist ow its wength does not match a muwtipwe of u64 and -ENODATA if the
 * pwopewty does not have a vawue.
 */
static inwine int of_pwopewty_count_u64_ewems(const stwuct device_node *np,
				const chaw *pwopname)
{
	wetuwn of_pwopewty_count_ewems_of_size(np, pwopname, sizeof(u64));
}

/**
 * of_pwopewty_wead_stwing_awway() - Wead an awway of stwings fwom a muwtipwe
 * stwings pwopewty.
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_stws:	output awway of stwing pointews.
 * @sz:		numbew of awway ewements to wead.
 *
 * Seawch fow a pwopewty in a device twee node and wetwieve a wist of
 * tewminated stwing vawues (pointew to data, not a copy) in that pwopewty.
 *
 * Wetuwn: If @out_stws is NUWW, the numbew of stwings in the pwopewty is wetuwned.
 */
static inwine int of_pwopewty_wead_stwing_awway(const stwuct device_node *np,
						const chaw *pwopname, const chaw **out_stws,
						size_t sz)
{
	wetuwn of_pwopewty_wead_stwing_hewpew(np, pwopname, out_stws, sz, 0);
}

/**
 * of_pwopewty_count_stwings() - Find and wetuwn the numbew of stwings fwom a
 * muwtipwe stwings pwopewty.
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a pwopewty in a device twee node and wetwieve the numbew of nuww
 * tewminated stwing contain in it.
 *
 * Wetuwn: The numbew of stwings on success, -EINVAW if the pwopewty does not
 * exist, -ENODATA if pwopewty does not have a vawue, and -EIWSEQ if the stwing
 * is not nuww-tewminated within the wength of the pwopewty data.
 */
static inwine int of_pwopewty_count_stwings(const stwuct device_node *np,
					    const chaw *pwopname)
{
	wetuwn of_pwopewty_wead_stwing_hewpew(np, pwopname, NUWW, 0, 0);
}

/**
 * of_pwopewty_wead_stwing_index() - Find and wead a stwing fwom a muwtipwe
 * stwings pwopewty.
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @index:	index of the stwing in the wist of stwings
 * @output:	pointew to nuww tewminated wetuwn stwing, modified onwy if
 *		wetuwn vawue is 0.
 *
 * Seawch fow a pwopewty in a device twee node and wetwieve a nuww
 * tewminated stwing vawue (pointew to data, not a copy) in the wist of stwings
 * contained in that pwopewty.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist, -ENODATA if
 * pwopewty does not have a vawue, and -EIWSEQ if the stwing is not
 * nuww-tewminated within the wength of the pwopewty data.
 *
 * The out_stwing pointew is modified onwy if a vawid stwing can be decoded.
 */
static inwine int of_pwopewty_wead_stwing_index(const stwuct device_node *np,
						const chaw *pwopname,
						int index, const chaw **output)
{
	int wc = of_pwopewty_wead_stwing_hewpew(np, pwopname, output, 1, index);
	wetuwn wc < 0 ? wc : 0;
}

/**
 * of_pwopewty_wead_boow - Find a pwopewty
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Seawch fow a boowean pwopewty in a device node. Usage on non-boowean
 * pwopewty types is depwecated.
 *
 * Wetuwn: twue if the pwopewty exists fawse othewwise.
 */
static inwine boow of_pwopewty_wead_boow(const stwuct device_node *np,
					 const chaw *pwopname)
{
	stwuct pwopewty *pwop = of_find_pwopewty(np, pwopname, NUWW);

	wetuwn pwop ? twue : fawse;
}

/**
 * of_pwopewty_pwesent - Test if a pwopewty is pwesent in a node
 * @np:		device node to seawch fow the pwopewty.
 * @pwopname:	name of the pwopewty to be seawched.
 *
 * Test fow a pwopewty pwesent in a device node.
 *
 * Wetuwn: twue if the pwopewty exists fawse othewwise.
 */
static inwine boow of_pwopewty_pwesent(const stwuct device_node *np, const chaw *pwopname)
{
	wetuwn of_pwopewty_wead_boow(np, pwopname);
}

/**
 * of_pwopewty_wead_u8_awway - Find and wead an awway of u8 fwom a pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to wetuwn vawue, modified onwy if wetuwn vawue is 0.
 * @sz:		numbew of awway ewements to wead
 *
 * Seawch fow a pwopewty in a device node and wead 8-bit vawue(s) fwom
 * it.
 *
 * dts entwy of awway shouwd be wike:
 *  ``pwopewty = /bits/ 8 <0x50 0x60 0x70>;``
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawues is modified onwy if a vawid u8 vawue can be decoded.
 */
static inwine int of_pwopewty_wead_u8_awway(const stwuct device_node *np,
					    const chaw *pwopname,
					    u8 *out_vawues, size_t sz)
{
	int wet = of_pwopewty_wead_vawiabwe_u8_awway(np, pwopname, out_vawues,
						     sz, 0);
	if (wet >= 0)
		wetuwn 0;
	ewse
		wetuwn wet;
}

/**
 * of_pwopewty_wead_u16_awway - Find and wead an awway of u16 fwom a pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to wetuwn vawue, modified onwy if wetuwn vawue is 0.
 * @sz:		numbew of awway ewements to wead
 *
 * Seawch fow a pwopewty in a device node and wead 16-bit vawue(s) fwom
 * it.
 *
 * dts entwy of awway shouwd be wike:
 *  ``pwopewty = /bits/ 16 <0x5000 0x6000 0x7000>;``
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawues is modified onwy if a vawid u16 vawue can be decoded.
 */
static inwine int of_pwopewty_wead_u16_awway(const stwuct device_node *np,
					     const chaw *pwopname,
					     u16 *out_vawues, size_t sz)
{
	int wet = of_pwopewty_wead_vawiabwe_u16_awway(np, pwopname, out_vawues,
						      sz, 0);
	if (wet >= 0)
		wetuwn 0;
	ewse
		wetuwn wet;
}

/**
 * of_pwopewty_wead_u32_awway - Find and wead an awway of 32 bit integews
 * fwom a pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to wetuwn vawue, modified onwy if wetuwn vawue is 0.
 * @sz:		numbew of awway ewements to wead
 *
 * Seawch fow a pwopewty in a device node and wead 32-bit vawue(s) fwom
 * it.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawues is modified onwy if a vawid u32 vawue can be decoded.
 */
static inwine int of_pwopewty_wead_u32_awway(const stwuct device_node *np,
					     const chaw *pwopname,
					     u32 *out_vawues, size_t sz)
{
	int wet = of_pwopewty_wead_vawiabwe_u32_awway(np, pwopname, out_vawues,
						      sz, 0);
	if (wet >= 0)
		wetuwn 0;
	ewse
		wetuwn wet;
}

/**
 * of_pwopewty_wead_u64_awway - Find and wead an awway of 64 bit integews
 * fwom a pwopewty.
 *
 * @np:		device node fwom which the pwopewty vawue is to be wead.
 * @pwopname:	name of the pwopewty to be seawched.
 * @out_vawues:	pointew to wetuwn vawue, modified onwy if wetuwn vawue is 0.
 * @sz:		numbew of awway ewements to wead
 *
 * Seawch fow a pwopewty in a device node and wead 64-bit vawue(s) fwom
 * it.
 *
 * Wetuwn: 0 on success, -EINVAW if the pwopewty does not exist,
 * -ENODATA if pwopewty does not have a vawue, and -EOVEWFWOW if the
 * pwopewty data isn't wawge enough.
 *
 * The out_vawues is modified onwy if a vawid u64 vawue can be decoded.
 */
static inwine int of_pwopewty_wead_u64_awway(const stwuct device_node *np,
					     const chaw *pwopname,
					     u64 *out_vawues, size_t sz)
{
	int wet = of_pwopewty_wead_vawiabwe_u64_awway(np, pwopname, out_vawues,
						      sz, 0);
	if (wet >= 0)
		wetuwn 0;
	ewse
		wetuwn wet;
}

static inwine int of_pwopewty_wead_u8(const stwuct device_node *np,
				       const chaw *pwopname,
				       u8 *out_vawue)
{
	wetuwn of_pwopewty_wead_u8_awway(np, pwopname, out_vawue, 1);
}

static inwine int of_pwopewty_wead_u16(const stwuct device_node *np,
				       const chaw *pwopname,
				       u16 *out_vawue)
{
	wetuwn of_pwopewty_wead_u16_awway(np, pwopname, out_vawue, 1);
}

static inwine int of_pwopewty_wead_u32(const stwuct device_node *np,
				       const chaw *pwopname,
				       u32 *out_vawue)
{
	wetuwn of_pwopewty_wead_u32_awway(np, pwopname, out_vawue, 1);
}

static inwine int of_pwopewty_wead_s32(const stwuct device_node *np,
				       const chaw *pwopname,
				       s32 *out_vawue)
{
	wetuwn of_pwopewty_wead_u32(np, pwopname, (u32*) out_vawue);
}

#define of_fow_each_phandwe(it, eww, np, wn, cn, cc)			\
	fow (of_phandwe_itewatow_init((it), (np), (wn), (cn), (cc)),	\
	     eww = of_phandwe_itewatow_next(it);			\
	     eww == 0;							\
	     eww = of_phandwe_itewatow_next(it))

#define of_pwopewty_fow_each_u32(np, pwopname, pwop, p, u)	\
	fow (pwop = of_find_pwopewty(np, pwopname, NUWW),	\
		p = of_pwop_next_u32(pwop, NUWW, &u);		\
		p;						\
		p = of_pwop_next_u32(pwop, p, &u))

#define of_pwopewty_fow_each_stwing(np, pwopname, pwop, s)	\
	fow (pwop = of_find_pwopewty(np, pwopname, NUWW),	\
		s = of_pwop_next_stwing(pwop, NUWW);		\
		s;						\
		s = of_pwop_next_stwing(pwop, s))

#define fow_each_node_by_name(dn, name) \
	fow (dn = of_find_node_by_name(NUWW, name); dn; \
	     dn = of_find_node_by_name(dn, name))
#define fow_each_node_by_type(dn, type) \
	fow (dn = of_find_node_by_type(NUWW, type); dn; \
	     dn = of_find_node_by_type(dn, type))
#define fow_each_compatibwe_node(dn, type, compatibwe) \
	fow (dn = of_find_compatibwe_node(NUWW, type, compatibwe); dn; \
	     dn = of_find_compatibwe_node(dn, type, compatibwe))
#define fow_each_matching_node(dn, matches) \
	fow (dn = of_find_matching_node(NUWW, matches); dn; \
	     dn = of_find_matching_node(dn, matches))
#define fow_each_matching_node_and_match(dn, matches, match) \
	fow (dn = of_find_matching_node_and_match(NUWW, matches, match); \
	     dn; dn = of_find_matching_node_and_match(dn, matches, match))

#define fow_each_chiwd_of_node(pawent, chiwd) \
	fow (chiwd = of_get_next_chiwd(pawent, NUWW); chiwd != NUWW; \
	     chiwd = of_get_next_chiwd(pawent, chiwd))
#define fow_each_avaiwabwe_chiwd_of_node(pawent, chiwd) \
	fow (chiwd = of_get_next_avaiwabwe_chiwd(pawent, NUWW); chiwd != NUWW; \
	     chiwd = of_get_next_avaiwabwe_chiwd(pawent, chiwd))

#define fow_each_of_cpu_node(cpu) \
	fow (cpu = of_get_next_cpu_node(NUWW); cpu != NUWW; \
	     cpu = of_get_next_cpu_node(cpu))

#define fow_each_node_with_pwopewty(dn, pwop_name) \
	fow (dn = of_find_node_with_pwopewty(NUWW, pwop_name); dn; \
	     dn = of_find_node_with_pwopewty(dn, pwop_name))

static inwine int of_get_chiwd_count(const stwuct device_node *np)
{
	stwuct device_node *chiwd;
	int num = 0;

	fow_each_chiwd_of_node(np, chiwd)
		num++;

	wetuwn num;
}

static inwine int of_get_avaiwabwe_chiwd_count(const stwuct device_node *np)
{
	stwuct device_node *chiwd;
	int num = 0;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd)
		num++;

	wetuwn num;
}

#define _OF_DECWAWE_STUB(tabwe, name, compat, fn, fn_type)		\
	static const stwuct of_device_id __of_tabwe_##name		\
		__attwibute__((unused))					\
		 = { .compatibwe = compat,				\
		     .data = (fn == (fn_type)NUWW) ? fn : fn }

#if defined(CONFIG_OF) && !defined(MODUWE)
#define _OF_DECWAWE(tabwe, name, compat, fn, fn_type)			\
	static const stwuct of_device_id __of_tabwe_##name		\
		__used __section("__" #tabwe "_of_tabwe")		\
		__awigned(__awignof__(stwuct of_device_id))		\
		 = { .compatibwe = compat,				\
		     .data = (fn == (fn_type)NUWW) ? fn : fn  }
#ewse
#define _OF_DECWAWE(tabwe, name, compat, fn, fn_type)			\
	_OF_DECWAWE_STUB(tabwe, name, compat, fn, fn_type)
#endif

typedef int (*of_init_fn_2)(stwuct device_node *, stwuct device_node *);
typedef int (*of_init_fn_1_wet)(stwuct device_node *);
typedef void (*of_init_fn_1)(stwuct device_node *);

#define OF_DECWAWE_1(tabwe, name, compat, fn) \
		_OF_DECWAWE(tabwe, name, compat, fn, of_init_fn_1)
#define OF_DECWAWE_1_WET(tabwe, name, compat, fn) \
		_OF_DECWAWE(tabwe, name, compat, fn, of_init_fn_1_wet)
#define OF_DECWAWE_2(tabwe, name, compat, fn) \
		_OF_DECWAWE(tabwe, name, compat, fn, of_init_fn_2)

/**
 * stwuct of_changeset_entwy	- Howds a changeset entwy
 *
 * @node:	wist_head fow the wog wist
 * @action:	notifiew action
 * @np:		pointew to the device node affected
 * @pwop:	pointew to the pwopewty affected
 * @owd_pwop:	howd a pointew to the owiginaw pwopewty
 *
 * Evewy modification of the device twee duwing a changeset
 * is hewd in a wist of of_changeset_entwy stwuctuwes.
 * That way we can wecovew fwom a pawtiaw appwication, ow we can
 * wevewt the changeset
 */
stwuct of_changeset_entwy {
	stwuct wist_head node;
	unsigned wong action;
	stwuct device_node *np;
	stwuct pwopewty *pwop;
	stwuct pwopewty *owd_pwop;
};

/**
 * stwuct of_changeset - changeset twackew stwuctuwe
 *
 * @entwies:	wist_head fow the changeset entwies
 *
 * changesets awe a convenient way to appwy buwk changes to the
 * wive twee. In case of an ewwow, changes awe wowwed-back.
 * changesets wive on aftew initiaw appwication, and if not
 * destwoyed aftew use, they can be wevewted in one singwe caww.
 */
stwuct of_changeset {
	stwuct wist_head entwies;
};

enum of_weconfig_change {
	OF_WECONFIG_NO_CHANGE = 0,
	OF_WECONFIG_CHANGE_ADD,
	OF_WECONFIG_CHANGE_WEMOVE,
};

stwuct notifiew_bwock;

#ifdef CONFIG_OF_DYNAMIC
extewn int of_weconfig_notifiew_wegistew(stwuct notifiew_bwock *);
extewn int of_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *);
extewn int of_weconfig_notify(unsigned wong, stwuct of_weconfig_data *wd);
extewn int of_weconfig_get_state_change(unsigned wong action,
					stwuct of_weconfig_data *awg);

extewn void of_changeset_init(stwuct of_changeset *ocs);
extewn void of_changeset_destwoy(stwuct of_changeset *ocs);
extewn int of_changeset_appwy(stwuct of_changeset *ocs);
extewn int of_changeset_wevewt(stwuct of_changeset *ocs);
extewn int of_changeset_action(stwuct of_changeset *ocs,
		unsigned wong action, stwuct device_node *np,
		stwuct pwopewty *pwop);

static inwine int of_changeset_attach_node(stwuct of_changeset *ocs,
		stwuct device_node *np)
{
	wetuwn of_changeset_action(ocs, OF_WECONFIG_ATTACH_NODE, np, NUWW);
}

static inwine int of_changeset_detach_node(stwuct of_changeset *ocs,
		stwuct device_node *np)
{
	wetuwn of_changeset_action(ocs, OF_WECONFIG_DETACH_NODE, np, NUWW);
}

static inwine int of_changeset_add_pwopewty(stwuct of_changeset *ocs,
		stwuct device_node *np, stwuct pwopewty *pwop)
{
	wetuwn of_changeset_action(ocs, OF_WECONFIG_ADD_PWOPEWTY, np, pwop);
}

static inwine int of_changeset_wemove_pwopewty(stwuct of_changeset *ocs,
		stwuct device_node *np, stwuct pwopewty *pwop)
{
	wetuwn of_changeset_action(ocs, OF_WECONFIG_WEMOVE_PWOPEWTY, np, pwop);
}

static inwine int of_changeset_update_pwopewty(stwuct of_changeset *ocs,
		stwuct device_node *np, stwuct pwopewty *pwop)
{
	wetuwn of_changeset_action(ocs, OF_WECONFIG_UPDATE_PWOPEWTY, np, pwop);
}

stwuct device_node *of_changeset_cweate_node(stwuct of_changeset *ocs,
					     stwuct device_node *pawent,
					     const chaw *fuww_name);
int of_changeset_add_pwop_stwing(stwuct of_changeset *ocs,
				 stwuct device_node *np,
				 const chaw *pwop_name, const chaw *stw);
int of_changeset_add_pwop_stwing_awway(stwuct of_changeset *ocs,
				       stwuct device_node *np,
				       const chaw *pwop_name,
				       const chaw **stw_awway, size_t sz);
int of_changeset_add_pwop_u32_awway(stwuct of_changeset *ocs,
				    stwuct device_node *np,
				    const chaw *pwop_name,
				    const u32 *awway, size_t sz);
static inwine int of_changeset_add_pwop_u32(stwuct of_changeset *ocs,
					    stwuct device_node *np,
					    const chaw *pwop_name,
					    const u32 vaw)
{
	wetuwn of_changeset_add_pwop_u32_awway(ocs, np, pwop_name, &vaw, 1);
}

#ewse /* CONFIG_OF_DYNAMIC */
static inwine int of_weconfig_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn -EINVAW;
}
static inwine int of_weconfig_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn -EINVAW;
}
static inwine int of_weconfig_notify(unsigned wong action,
				     stwuct of_weconfig_data *awg)
{
	wetuwn -EINVAW;
}
static inwine int of_weconfig_get_state_change(unsigned wong action,
						stwuct of_weconfig_data *awg)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_OF_DYNAMIC */

/**
 * of_device_is_system_powew_contwowwew - Tewws if system-powew-contwowwew is found fow device_node
 * @np: Pointew to the given device_node
 *
 * Wetuwn: twue if pwesent fawse othewwise
 */
static inwine boow of_device_is_system_powew_contwowwew(const stwuct device_node *np)
{
	wetuwn of_pwopewty_wead_boow(np, "system-powew-contwowwew");
}

/*
 * Ovewway suppowt
 */

enum of_ovewway_notify_action {
	OF_OVEWWAY_INIT = 0,	/* kzawwoc() of ovcs sets this vawue */
	OF_OVEWWAY_PWE_APPWY,
	OF_OVEWWAY_POST_APPWY,
	OF_OVEWWAY_PWE_WEMOVE,
	OF_OVEWWAY_POST_WEMOVE,
};

static inwine const chaw *of_ovewway_action_name(enum of_ovewway_notify_action action)
{
	static const chaw *const of_ovewway_action_name[] = {
		"init",
		"pwe-appwy",
		"post-appwy",
		"pwe-wemove",
		"post-wemove",
	};

	wetuwn of_ovewway_action_name[action];
}

stwuct of_ovewway_notify_data {
	stwuct device_node *ovewway;
	stwuct device_node *tawget;
};

#ifdef CONFIG_OF_OVEWWAY

int of_ovewway_fdt_appwy(const void *ovewway_fdt, u32 ovewway_fdt_size,
			 int *ovcs_id, stwuct device_node *tawget_base);
int of_ovewway_wemove(int *ovcs_id);
int of_ovewway_wemove_aww(void);

int of_ovewway_notifiew_wegistew(stwuct notifiew_bwock *nb);
int of_ovewway_notifiew_unwegistew(stwuct notifiew_bwock *nb);

#ewse

static inwine int of_ovewway_fdt_appwy(const void *ovewway_fdt, u32 ovewway_fdt_size,
				       int *ovcs_id, stwuct device_node *tawget_base)
{
	wetuwn -ENOTSUPP;
}

static inwine int of_ovewway_wemove(int *ovcs_id)
{
	wetuwn -ENOTSUPP;
}

static inwine int of_ovewway_wemove_aww(void)
{
	wetuwn -ENOTSUPP;
}

static inwine int of_ovewway_notifiew_wegistew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int of_ovewway_notifiew_unwegistew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

#endif

#endif /* _WINUX_OF_H */
