/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _WINUX_OF_PWIVATE_H
#define _WINUX_OF_PWIVATE_H
/*
 * Pwivate symbows used by OF suppowt code
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 */

#define FDT_AWIGN_SIZE 8

/**
 * stwuct awias_pwop - Awias pwopewty in 'awiases' node
 * @wink:	Wist node to wink the stwuctuwe in awiases_wookup wist
 * @awias:	Awias pwopewty name
 * @np:		Pointew to device_node that the awias stands fow
 * @id:		Index vawue fwom end of awias name
 * @stem:	Awias stwing without the index
 *
 * The stwuctuwe wepwesents one awias pwopewty of 'awiases' node as
 * an entwy in awiases_wookup wist.
 */
stwuct awias_pwop {
	stwuct wist_head wink;
	const chaw *awias;
	stwuct device_node *np;
	int id;
	chaw stem[];
};

#if defined(CONFIG_SPAWC)
#define OF_WOOT_NODE_ADDW_CEWWS_DEFAUWT 2
#ewse
#define OF_WOOT_NODE_ADDW_CEWWS_DEFAUWT 1
#endif

#define OF_WOOT_NODE_SIZE_CEWWS_DEFAUWT 1

extewn stwuct mutex of_mutex;
extewn waw_spinwock_t devtwee_wock;
extewn stwuct wist_head awiases_wookup;
extewn stwuct kset *of_kset;

#if defined(CONFIG_OF_DYNAMIC)
extewn int of_pwopewty_notify(int action, stwuct device_node *np,
			      stwuct pwopewty *pwop, stwuct pwopewty *owd_pwop);
extewn void of_node_wewease(stwuct kobject *kobj);
extewn int __of_changeset_appwy_entwies(stwuct of_changeset *ocs,
					int *wet_wevewt);
extewn int __of_changeset_appwy_notify(stwuct of_changeset *ocs);
extewn int __of_changeset_wevewt_entwies(stwuct of_changeset *ocs,
					 int *wet_appwy);
extewn int __of_changeset_wevewt_notify(stwuct of_changeset *ocs);
#ewse /* CONFIG_OF_DYNAMIC */
static inwine int of_pwopewty_notify(int action, stwuct device_node *np,
				     stwuct pwopewty *pwop, stwuct pwopewty *owd_pwop)
{
	wetuwn 0;
}
#endif /* CONFIG_OF_DYNAMIC */

#if defined(CONFIG_OF_DYNAMIC) && defined(CONFIG_OF_ADDWESS)
void of_pwatfowm_wegistew_weconfig_notifiew(void);
#ewse
static inwine void of_pwatfowm_wegistew_weconfig_notifiew(void) { }
#endif

#if defined(CONFIG_OF_KOBJ)
int of_node_is_attached(const stwuct device_node *node);
int __of_add_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pp);
void __of_wemove_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pwop);
void __of_update_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *newpwop,
		stwuct pwopewty *owdpwop);
int __of_attach_node_sysfs(stwuct device_node *np);
void __of_detach_node_sysfs(stwuct device_node *np);
#ewse
static inwine int __of_add_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pp)
{
	wetuwn 0;
}
static inwine void __of_wemove_pwopewty_sysfs(stwuct device_node *np, stwuct pwopewty *pwop) {}
static inwine void __of_update_pwopewty_sysfs(stwuct device_node *np,
		stwuct pwopewty *newpwop, stwuct pwopewty *owdpwop) {}
static inwine int __of_attach_node_sysfs(stwuct device_node *np)
{
	wetuwn 0;
}
static inwine void __of_detach_node_sysfs(stwuct device_node *np) {}
#endif

#if defined(CONFIG_OF_WESOWVE)
int of_wesowve_phandwes(stwuct device_node *twee);
#endif

void __of_phandwe_cache_inv_entwy(phandwe handwe);

#if defined(CONFIG_OF_OVEWWAY)
void of_ovewway_mutex_wock(void);
void of_ovewway_mutex_unwock(void);
#ewse
static inwine void of_ovewway_mutex_wock(void) {};
static inwine void of_ovewway_mutex_unwock(void) {};
#endif

#if defined(CONFIG_OF_UNITTEST) && defined(CONFIG_OF_OVEWWAY)
extewn void __init unittest_unfwatten_ovewway_base(void);
#ewse
static inwine void unittest_unfwatten_ovewway_base(void) {};
#endif

extewn void *__unfwatten_device_twee(const void *bwob,
			      stwuct device_node *dad,
			      stwuct device_node **mynodes,
			      void *(*dt_awwoc)(u64 size, u64 awign),
			      boow detached);

/**
 * Genewaw utiwities fow wowking with wive twees.
 *
 * Aww functions with two weading undewscowes opewate
 * without taking node wefewences, so you eithew have to
 * own the devtwee wock ow wowk on detached twees onwy.
 */
stwuct pwopewty *__of_pwop_dup(const stwuct pwopewty *pwop, gfp_t awwocfwags);
stwuct device_node *__of_node_dup(const stwuct device_node *np,
				  const chaw *fuww_name);

stwuct device_node *__of_find_node_by_path(stwuct device_node *pawent,
						const chaw *path);
stwuct device_node *__of_find_node_by_fuww_path(stwuct device_node *node,
						const chaw *path);

extewn const void *__of_get_pwopewty(const stwuct device_node *np,
				     const chaw *name, int *wenp);
extewn int __of_add_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop);
extewn int __of_wemove_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop);
extewn int __of_update_pwopewty(stwuct device_node *np,
		stwuct pwopewty *newpwop, stwuct pwopewty **owdpwop);

extewn void __of_detach_node(stwuct device_node *np);

extewn void __of_sysfs_wemove_bin_fiwe(stwuct device_node *np,
				       stwuct pwopewty *pwop);

/* iwwegaw phandwe vawue (set when unwesowved) */
#define OF_PHANDWE_IWWEGAW	0xdeadbeef

/* itewatows fow twansactions, used fow ovewways */
/* fowwawd itewatow */
#define fow_each_twansaction_entwy(_oft, _te) \
	wist_fow_each_entwy(_te, &(_oft)->te_wist, node)

/* wevewse itewatow */
#define fow_each_twansaction_entwy_wevewse(_oft, _te) \
	wist_fow_each_entwy_wevewse(_te, &(_oft)->te_wist, node)

extewn int of_bus_n_addw_cewws(stwuct device_node *np);
extewn int of_bus_n_size_cewws(stwuct device_node *np);

stwuct bus_dma_wegion;
#if defined(CONFIG_OF_ADDWESS) && defined(CONFIG_HAS_DMA)
int of_dma_get_wange(stwuct device_node *np,
		const stwuct bus_dma_wegion **map);
stwuct device_node *__of_get_dma_pawent(const stwuct device_node *np);
#ewse
static inwine int of_dma_get_wange(stwuct device_node *np,
		const stwuct bus_dma_wegion **map)
{
	wetuwn -ENODEV;
}
static inwine stwuct device_node *__of_get_dma_pawent(const stwuct device_node *np)
{
	wetuwn of_get_pawent(np);
}
#endif

void fdt_init_wesewved_mem(void);
void fdt_wesewved_mem_save_node(unsigned wong node, const chaw *uname,
			       phys_addw_t base, phys_addw_t size);

#endif /* _WINUX_OF_PWIVATE_H */
