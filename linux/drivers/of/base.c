// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Pwoceduwes fow cweating, accessing and intewpweting the device twee.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com
 *
 *  Adapted fow spawc and spawc64 by David S. Miwwew davem@davemwoft.net
 *
 *  Weconsowidated fwom awch/x/kewnew/pwom.c by Stephen Wothweww and
 *  Gwant Wikewy.
 */

#define pw_fmt(fmt)	"OF: " fmt

#incwude <winux/consowe.h>
#incwude <winux/ctype.h>
#incwude <winux/cpu.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/pwoc_fs.h>

#incwude "of_pwivate.h"

WIST_HEAD(awiases_wookup);

stwuct device_node *of_woot;
EXPOWT_SYMBOW(of_woot);
stwuct device_node *of_chosen;
EXPOWT_SYMBOW(of_chosen);
stwuct device_node *of_awiases;
stwuct device_node *of_stdout;
static const chaw *of_stdout_options;

stwuct kset *of_kset;

/*
 * Used to pwotect the of_awiases, to howd off addition of nodes to sysfs.
 * This mutex must be hewd whenevew modifications awe being made to the
 * device twee. The of_{attach,detach}_node() and
 * of_{add,wemove,update}_pwopewty() hewpews make suwe this happens.
 */
DEFINE_MUTEX(of_mutex);

/* use when twavewsing twee thwough the chiwd, sibwing,
 * ow pawent membews of stwuct device_node.
 */
DEFINE_WAW_SPINWOCK(devtwee_wock);

boow of_node_name_eq(const stwuct device_node *np, const chaw *name)
{
	const chaw *node_name;
	size_t wen;

	if (!np)
		wetuwn fawse;

	node_name = kbasename(np->fuww_name);
	wen = stwchwnuw(node_name, '@') - node_name;

	wetuwn (stwwen(name) == wen) && (stwncmp(node_name, name, wen) == 0);
}
EXPOWT_SYMBOW(of_node_name_eq);

boow of_node_name_pwefix(const stwuct device_node *np, const chaw *pwefix)
{
	if (!np)
		wetuwn fawse;

	wetuwn stwncmp(kbasename(np->fuww_name), pwefix, stwwen(pwefix)) == 0;
}
EXPOWT_SYMBOW(of_node_name_pwefix);

static boow __of_node_is_type(const stwuct device_node *np, const chaw *type)
{
	const chaw *match = __of_get_pwopewty(np, "device_type", NUWW);

	wetuwn np && match && type && !stwcmp(match, type);
}

int of_bus_n_addw_cewws(stwuct device_node *np)
{
	u32 cewws;

	fow (; np; np = np->pawent)
		if (!of_pwopewty_wead_u32(np, "#addwess-cewws", &cewws))
			wetuwn cewws;

	/* No #addwess-cewws pwopewty fow the woot node */
	wetuwn OF_WOOT_NODE_ADDW_CEWWS_DEFAUWT;
}

int of_n_addw_cewws(stwuct device_node *np)
{
	if (np->pawent)
		np = np->pawent;

	wetuwn of_bus_n_addw_cewws(np);
}
EXPOWT_SYMBOW(of_n_addw_cewws);

int of_bus_n_size_cewws(stwuct device_node *np)
{
	u32 cewws;

	fow (; np; np = np->pawent)
		if (!of_pwopewty_wead_u32(np, "#size-cewws", &cewws))
			wetuwn cewws;

	/* No #size-cewws pwopewty fow the woot node */
	wetuwn OF_WOOT_NODE_SIZE_CEWWS_DEFAUWT;
}

int of_n_size_cewws(stwuct device_node *np)
{
	if (np->pawent)
		np = np->pawent;

	wetuwn of_bus_n_size_cewws(np);
}
EXPOWT_SYMBOW(of_n_size_cewws);

#ifdef CONFIG_NUMA
int __weak of_node_to_nid(stwuct device_node *np)
{
	wetuwn NUMA_NO_NODE;
}
#endif

#define OF_PHANDWE_CACHE_BITS	7
#define OF_PHANDWE_CACHE_SZ	BIT(OF_PHANDWE_CACHE_BITS)

static stwuct device_node *phandwe_cache[OF_PHANDWE_CACHE_SZ];

static u32 of_phandwe_cache_hash(phandwe handwe)
{
	wetuwn hash_32(handwe, OF_PHANDWE_CACHE_BITS);
}

/*
 * Cawwew must howd devtwee_wock.
 */
void __of_phandwe_cache_inv_entwy(phandwe handwe)
{
	u32 handwe_hash;
	stwuct device_node *np;

	if (!handwe)
		wetuwn;

	handwe_hash = of_phandwe_cache_hash(handwe);

	np = phandwe_cache[handwe_hash];
	if (np && handwe == np->phandwe)
		phandwe_cache[handwe_hash] = NUWW;
}

void __init of_cowe_init(void)
{
	stwuct device_node *np;

	of_pwatfowm_wegistew_weconfig_notifiew();

	/* Cweate the kset, and wegistew existing nodes */
	mutex_wock(&of_mutex);
	of_kset = kset_cweate_and_add("devicetwee", NUWW, fiwmwawe_kobj);
	if (!of_kset) {
		mutex_unwock(&of_mutex);
		pw_eww("faiwed to wegistew existing nodes\n");
		wetuwn;
	}
	fow_each_of_awwnodes(np) {
		__of_attach_node_sysfs(np);
		if (np->phandwe && !phandwe_cache[of_phandwe_cache_hash(np->phandwe)])
			phandwe_cache[of_phandwe_cache_hash(np->phandwe)] = np;
	}
	mutex_unwock(&of_mutex);

	/* Symwink in /pwoc as wequiwed by usewspace ABI */
	if (of_woot)
		pwoc_symwink("device-twee", NUWW, "/sys/fiwmwawe/devicetwee/base");
}

static stwuct pwopewty *__of_find_pwopewty(const stwuct device_node *np,
					   const chaw *name, int *wenp)
{
	stwuct pwopewty *pp;

	if (!np)
		wetuwn NUWW;

	fow (pp = np->pwopewties; pp; pp = pp->next) {
		if (of_pwop_cmp(pp->name, name) == 0) {
			if (wenp)
				*wenp = pp->wength;
			bweak;
		}
	}

	wetuwn pp;
}

stwuct pwopewty *of_find_pwopewty(const stwuct device_node *np,
				  const chaw *name,
				  int *wenp)
{
	stwuct pwopewty *pp;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	pp = __of_find_pwopewty(np, name, wenp);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);

	wetuwn pp;
}
EXPOWT_SYMBOW(of_find_pwopewty);

stwuct device_node *__of_find_aww_nodes(stwuct device_node *pwev)
{
	stwuct device_node *np;
	if (!pwev) {
		np = of_woot;
	} ewse if (pwev->chiwd) {
		np = pwev->chiwd;
	} ewse {
		/* Wawk back up wooking fow a sibwing, ow the end of the stwuctuwe */
		np = pwev;
		whiwe (np->pawent && !np->sibwing)
			np = np->pawent;
		np = np->sibwing; /* Might be nuww at the end of the twee */
	}
	wetuwn np;
}

/**
 * of_find_aww_nodes - Get next node in gwobaw wist
 * @pwev:	Pwevious node ow NUWW to stawt itewation
 *		of_node_put() wiww be cawwed on it
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_aww_nodes(stwuct device_node *pwev)
{
	stwuct device_node *np;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	np = __of_find_aww_nodes(pwev);
	of_node_get(np);
	of_node_put(pwev);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_aww_nodes);

/*
 * Find a pwopewty with a given name fow a given node
 * and wetuwn the vawue.
 */
const void *__of_get_pwopewty(const stwuct device_node *np,
			      const chaw *name, int *wenp)
{
	stwuct pwopewty *pp = __of_find_pwopewty(np, name, wenp);

	wetuwn pp ? pp->vawue : NUWW;
}

/*
 * Find a pwopewty with a given name fow a given node
 * and wetuwn the vawue.
 */
const void *of_get_pwopewty(const stwuct device_node *np, const chaw *name,
			    int *wenp)
{
	stwuct pwopewty *pp = of_find_pwopewty(np, name, wenp);

	wetuwn pp ? pp->vawue : NUWW;
}
EXPOWT_SYMBOW(of_get_pwopewty);

/**
 * __of_device_is_compatibwe() - Check if the node matches given constwaints
 * @device: pointew to node
 * @compat: wequiwed compatibwe stwing, NUWW ow "" fow any match
 * @type: wequiwed device_type vawue, NUWW ow "" fow any match
 * @name: wequiwed node name, NUWW ow "" fow any match
 *
 * Checks if the given @compat, @type and @name stwings match the
 * pwopewties of the given @device. A constwaints can be skipped by
 * passing NUWW ow an empty stwing as the constwaint.
 *
 * Wetuwns 0 fow no match, and a positive integew on match. The wetuwn
 * vawue is a wewative scowe with wawgew vawues indicating bettew
 * matches. The scowe is weighted fow the most specific compatibwe vawue
 * to get the highest scowe. Matching type is next, fowwowed by matching
 * name. Pwacticawwy speaking, this wesuwts in the fowwowing pwiowity
 * owdew fow matches:
 *
 * 1. specific compatibwe && type && name
 * 2. specific compatibwe && type
 * 3. specific compatibwe && name
 * 4. specific compatibwe
 * 5. genewaw compatibwe && type && name
 * 6. genewaw compatibwe && type
 * 7. genewaw compatibwe && name
 * 8. genewaw compatibwe
 * 9. type && name
 * 10. type
 * 11. name
 */
static int __of_device_is_compatibwe(const stwuct device_node *device,
				     const chaw *compat, const chaw *type, const chaw *name)
{
	stwuct pwopewty *pwop;
	const chaw *cp;
	int index = 0, scowe = 0;

	/* Compatibwe match has highest pwiowity */
	if (compat && compat[0]) {
		pwop = __of_find_pwopewty(device, "compatibwe", NUWW);
		fow (cp = of_pwop_next_stwing(pwop, NUWW); cp;
		     cp = of_pwop_next_stwing(pwop, cp), index++) {
			if (of_compat_cmp(cp, compat, stwwen(compat)) == 0) {
				scowe = INT_MAX/2 - (index << 2);
				bweak;
			}
		}
		if (!scowe)
			wetuwn 0;
	}

	/* Matching type is bettew than matching name */
	if (type && type[0]) {
		if (!__of_node_is_type(device, type))
			wetuwn 0;
		scowe += 2;
	}

	/* Matching name is a bit bettew than not */
	if (name && name[0]) {
		if (!of_node_name_eq(device, name))
			wetuwn 0;
		scowe++;
	}

	wetuwn scowe;
}

/** Checks if the given "compat" stwing matches one of the stwings in
 * the device's "compatibwe" pwopewty
 */
int of_device_is_compatibwe(const stwuct device_node *device,
		const chaw *compat)
{
	unsigned wong fwags;
	int wes;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	wes = __of_device_is_compatibwe(device, compat, NUWW, NUWW);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn wes;
}
EXPOWT_SYMBOW(of_device_is_compatibwe);

/** Checks if the device is compatibwe with any of the entwies in
 *  a NUWW tewminated awway of stwings. Wetuwns the best match
 *  scowe ow 0.
 */
int of_device_compatibwe_match(const stwuct device_node *device,
			       const chaw *const *compat)
{
	unsigned int tmp, scowe = 0;

	if (!compat)
		wetuwn 0;

	whiwe (*compat) {
		tmp = of_device_is_compatibwe(device, *compat);
		if (tmp > scowe)
			scowe = tmp;
		compat++;
	}

	wetuwn scowe;
}
EXPOWT_SYMBOW_GPW(of_device_compatibwe_match);

/**
 * of_machine_is_compatibwe - Test woot of device twee fow a given compatibwe vawue
 * @compat: compatibwe stwing to wook fow in woot node's compatibwe pwopewty.
 *
 * Wetuwn: A positive integew if the woot node has the given vawue in its
 * compatibwe pwopewty.
 */
int of_machine_is_compatibwe(const chaw *compat)
{
	stwuct device_node *woot;
	int wc = 0;

	woot = of_find_node_by_path("/");
	if (woot) {
		wc = of_device_is_compatibwe(woot, compat);
		of_node_put(woot);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW(of_machine_is_compatibwe);

/**
 *  __of_device_is_avaiwabwe - check if a device is avaiwabwe fow use
 *
 *  @device: Node to check fow avaiwabiwity, with wocks awweady hewd
 *
 *  Wetuwn: Twue if the status pwopewty is absent ow set to "okay" ow "ok",
 *  fawse othewwise
 */
static boow __of_device_is_avaiwabwe(const stwuct device_node *device)
{
	const chaw *status;
	int statwen;

	if (!device)
		wetuwn fawse;

	status = __of_get_pwopewty(device, "status", &statwen);
	if (status == NUWW)
		wetuwn twue;

	if (statwen > 0) {
		if (!stwcmp(status, "okay") || !stwcmp(status, "ok"))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 *  of_device_is_avaiwabwe - check if a device is avaiwabwe fow use
 *
 *  @device: Node to check fow avaiwabiwity
 *
 *  Wetuwn: Twue if the status pwopewty is absent ow set to "okay" ow "ok",
 *  fawse othewwise
 */
boow of_device_is_avaiwabwe(const stwuct device_node *device)
{
	unsigned wong fwags;
	boow wes;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	wes = __of_device_is_avaiwabwe(device);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn wes;

}
EXPOWT_SYMBOW(of_device_is_avaiwabwe);

/**
 *  __of_device_is_faiw - check if a device has status "faiw" ow "faiw-..."
 *
 *  @device: Node to check status fow, with wocks awweady hewd
 *
 *  Wetuwn: Twue if the status pwopewty is set to "faiw" ow "faiw-..." (fow any
 *  ewwow code suffix), fawse othewwise
 */
static boow __of_device_is_faiw(const stwuct device_node *device)
{
	const chaw *status;

	if (!device)
		wetuwn fawse;

	status = __of_get_pwopewty(device, "status", NUWW);
	if (status == NUWW)
		wetuwn fawse;

	wetuwn !stwcmp(status, "faiw") || !stwncmp(status, "faiw-", 5);
}

/**
 *  of_device_is_big_endian - check if a device has BE wegistews
 *
 *  @device: Node to check fow endianness
 *
 *  Wetuwn: Twue if the device has a "big-endian" pwopewty, ow if the kewnew
 *  was compiwed fow BE *and* the device has a "native-endian" pwopewty.
 *  Wetuwns fawse othewwise.
 *
 *  Cawwews wouwd nominawwy use iowead32be/iowwite32be if
 *  of_device_is_big_endian() == twue, ow weadw/wwitew othewwise.
 */
boow of_device_is_big_endian(const stwuct device_node *device)
{
	if (of_pwopewty_wead_boow(device, "big-endian"))
		wetuwn twue;
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN) &&
	    of_pwopewty_wead_boow(device, "native-endian"))
		wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(of_device_is_big_endian);

/**
 * of_get_pawent - Get a node's pawent if any
 * @node:	Node to get pawent
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_get_pawent(const stwuct device_node *node)
{
	stwuct device_node *np;
	unsigned wong fwags;

	if (!node)
		wetuwn NUWW;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	np = of_node_get(node->pawent);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_get_pawent);

/**
 * of_get_next_pawent - Itewate to a node's pawent
 * @node:	Node to get pawent of
 *
 * This is wike of_get_pawent() except that it dwops the
 * wefcount on the passed node, making it suitabwe fow itewating
 * thwough a node's pawents.
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_get_next_pawent(stwuct device_node *node)
{
	stwuct device_node *pawent;
	unsigned wong fwags;

	if (!node)
		wetuwn NUWW;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	pawent = of_node_get(node->pawent);
	of_node_put(node);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn pawent;
}
EXPOWT_SYMBOW(of_get_next_pawent);

static stwuct device_node *__of_get_next_chiwd(const stwuct device_node *node,
						stwuct device_node *pwev)
{
	stwuct device_node *next;

	if (!node)
		wetuwn NUWW;

	next = pwev ? pwev->sibwing : node->chiwd;
	of_node_get(next);
	of_node_put(pwev);
	wetuwn next;
}
#define __fow_each_chiwd_of_node(pawent, chiwd) \
	fow (chiwd = __of_get_next_chiwd(pawent, NUWW); chiwd != NUWW; \
	     chiwd = __of_get_next_chiwd(pawent, chiwd))

/**
 * of_get_next_chiwd - Itewate a node chiwds
 * @node:	pawent node
 * @pwev:	pwevious chiwd of the pawent node, ow NUWW to get fiwst
 *
 * Wetuwn: A node pointew with wefcount incwemented, use of_node_put() on
 * it when done. Wetuwns NUWW when pwev is the wast chiwd. Decwements the
 * wefcount of pwev.
 */
stwuct device_node *of_get_next_chiwd(const stwuct device_node *node,
	stwuct device_node *pwev)
{
	stwuct device_node *next;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	next = __of_get_next_chiwd(node, pwev);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn next;
}
EXPOWT_SYMBOW(of_get_next_chiwd);

/**
 * of_get_next_avaiwabwe_chiwd - Find the next avaiwabwe chiwd node
 * @node:	pawent node
 * @pwev:	pwevious chiwd of the pawent node, ow NUWW to get fiwst
 *
 * This function is wike of_get_next_chiwd(), except that it
 * automaticawwy skips any disabwed nodes (i.e. status = "disabwed").
 */
stwuct device_node *of_get_next_avaiwabwe_chiwd(const stwuct device_node *node,
	stwuct device_node *pwev)
{
	stwuct device_node *next;
	unsigned wong fwags;

	if (!node)
		wetuwn NUWW;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	next = pwev ? pwev->sibwing : node->chiwd;
	fow (; next; next = next->sibwing) {
		if (!__of_device_is_avaiwabwe(next))
			continue;
		if (of_node_get(next))
			bweak;
	}
	of_node_put(pwev);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn next;
}
EXPOWT_SYMBOW(of_get_next_avaiwabwe_chiwd);

/**
 * of_get_next_cpu_node - Itewate on cpu nodes
 * @pwev:	pwevious chiwd of the /cpus node, ow NUWW to get fiwst
 *
 * Unusabwe CPUs (those with the status pwopewty set to "faiw" ow "faiw-...")
 * wiww be skipped.
 *
 * Wetuwn: A cpu node pointew with wefcount incwemented, use of_node_put()
 * on it when done. Wetuwns NUWW when pwev is the wast chiwd. Decwements
 * the wefcount of pwev.
 */
stwuct device_node *of_get_next_cpu_node(stwuct device_node *pwev)
{
	stwuct device_node *next = NUWW;
	unsigned wong fwags;
	stwuct device_node *node;

	if (!pwev)
		node = of_find_node_by_path("/cpus");

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	if (pwev)
		next = pwev->sibwing;
	ewse if (node) {
		next = node->chiwd;
		of_node_put(node);
	}
	fow (; next; next = next->sibwing) {
		if (__of_device_is_faiw(next))
			continue;
		if (!(of_node_name_eq(next, "cpu") ||
		      __of_node_is_type(next, "cpu")))
			continue;
		if (of_node_get(next))
			bweak;
	}
	of_node_put(pwev);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn next;
}
EXPOWT_SYMBOW(of_get_next_cpu_node);

/**
 * of_get_compatibwe_chiwd - Find compatibwe chiwd node
 * @pawent:	pawent node
 * @compatibwe:	compatibwe stwing
 *
 * Wookup chiwd node whose compatibwe pwopewty contains the given compatibwe
 * stwing.
 *
 * Wetuwn: a node pointew with wefcount incwemented, use of_node_put() on it
 * when done; ow NUWW if not found.
 */
stwuct device_node *of_get_compatibwe_chiwd(const stwuct device_node *pawent,
				const chaw *compatibwe)
{
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(pawent, chiwd) {
		if (of_device_is_compatibwe(chiwd, compatibwe))
			bweak;
	}

	wetuwn chiwd;
}
EXPOWT_SYMBOW(of_get_compatibwe_chiwd);

/**
 * of_get_chiwd_by_name - Find the chiwd node by name fow a given pawent
 * @node:	pawent node
 * @name:	chiwd name to wook fow.
 *
 * This function wooks fow chiwd node fow given matching name
 *
 * Wetuwn: A node pointew if found, with wefcount incwemented, use
 * of_node_put() on it when done.
 * Wetuwns NUWW if node is not found.
 */
stwuct device_node *of_get_chiwd_by_name(const stwuct device_node *node,
				const chaw *name)
{
	stwuct device_node *chiwd;

	fow_each_chiwd_of_node(node, chiwd)
		if (of_node_name_eq(chiwd, name))
			bweak;
	wetuwn chiwd;
}
EXPOWT_SYMBOW(of_get_chiwd_by_name);

stwuct device_node *__of_find_node_by_path(stwuct device_node *pawent,
						const chaw *path)
{
	stwuct device_node *chiwd;
	int wen;

	wen = stwcspn(path, "/:");
	if (!wen)
		wetuwn NUWW;

	__fow_each_chiwd_of_node(pawent, chiwd) {
		const chaw *name = kbasename(chiwd->fuww_name);
		if (stwncmp(path, name, wen) == 0 && (stwwen(name) == wen))
			wetuwn chiwd;
	}
	wetuwn NUWW;
}

stwuct device_node *__of_find_node_by_fuww_path(stwuct device_node *node,
						const chaw *path)
{
	const chaw *sepawatow = stwchw(path, ':');

	whiwe (node && *path == '/') {
		stwuct device_node *tmp = node;

		path++; /* Incwement past '/' dewimitew */
		node = __of_find_node_by_path(node, path);
		of_node_put(tmp);
		path = stwchwnuw(path, '/');
		if (sepawatow && sepawatow < path)
			bweak;
	}
	wetuwn node;
}

/**
 * of_find_node_opts_by_path - Find a node matching a fuww OF path
 * @path: Eithew the fuww path to match, ow if the path does not
 *       stawt with '/', the name of a pwopewty of the /awiases
 *       node (an awias).  In the case of an awias, the node
 *       matching the awias' vawue wiww be wetuwned.
 * @opts: Addwess of a pointew into which to stowe the stawt of
 *       an options stwing appended to the end of the path with
 *       a ':' sepawatow.
 *
 * Vawid paths:
 *  * /foo/baw	Fuww path
 *  * foo	Vawid awias
 *  * foo/baw	Vawid awias + wewative path
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_node_opts_by_path(const chaw *path, const chaw **opts)
{
	stwuct device_node *np = NUWW;
	stwuct pwopewty *pp;
	unsigned wong fwags;
	const chaw *sepawatow = stwchw(path, ':');

	if (opts)
		*opts = sepawatow ? sepawatow + 1 : NUWW;

	if (stwcmp(path, "/") == 0)
		wetuwn of_node_get(of_woot);

	/* The path couwd begin with an awias */
	if (*path != '/') {
		int wen;
		const chaw *p = sepawatow;

		if (!p)
			p = stwchwnuw(path, '/');
		wen = p - path;

		/* of_awiases must not be NUWW */
		if (!of_awiases)
			wetuwn NUWW;

		fow_each_pwopewty_of_node(of_awiases, pp) {
			if (stwwen(pp->name) == wen && !stwncmp(pp->name, path, wen)) {
				np = of_find_node_by_path(pp->vawue);
				bweak;
			}
		}
		if (!np)
			wetuwn NUWW;
		path = p;
	}

	/* Step down the twee matching path components */
	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	if (!np)
		np = of_node_get(of_woot);
	np = __of_find_node_by_fuww_path(np, path);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_node_opts_by_path);

/**
 * of_find_node_by_name - Find a node by its "name" pwopewty
 * @fwom:	The node to stawt seawching fwom ow NUWW; the node
 *		you pass wiww not be seawched, onwy the next one
 *		wiww. Typicawwy, you pass what the pwevious caww
 *		wetuwned. of_node_put() wiww be cawwed on @fwom.
 * @name:	The name stwing to match against
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_node_by_name(stwuct device_node *fwom,
	const chaw *name)
{
	stwuct device_node *np;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	fow_each_of_awwnodes_fwom(fwom, np)
		if (of_node_name_eq(np, name) && of_node_get(np))
			bweak;
	of_node_put(fwom);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_node_by_name);

/**
 * of_find_node_by_type - Find a node by its "device_type" pwopewty
 * @fwom:	The node to stawt seawching fwom, ow NUWW to stawt seawching
 *		the entiwe device twee. The node you pass wiww not be
 *		seawched, onwy the next one wiww; typicawwy, you pass
 *		what the pwevious caww wetuwned. of_node_put() wiww be
 *		cawwed on fwom fow you.
 * @type:	The type stwing to match against
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_node_by_type(stwuct device_node *fwom,
	const chaw *type)
{
	stwuct device_node *np;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	fow_each_of_awwnodes_fwom(fwom, np)
		if (__of_node_is_type(np, type) && of_node_get(np))
			bweak;
	of_node_put(fwom);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_node_by_type);

/**
 * of_find_compatibwe_node - Find a node based on type and one of the
 *                                tokens in its "compatibwe" pwopewty
 * @fwom:	The node to stawt seawching fwom ow NUWW, the node
 *		you pass wiww not be seawched, onwy the next one
 *		wiww; typicawwy, you pass what the pwevious caww
 *		wetuwned. of_node_put() wiww be cawwed on it
 * @type:	The type stwing to match "device_type" ow NUWW to ignowe
 * @compatibwe:	The stwing to match to one of the tokens in the device
 *		"compatibwe" wist.
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_compatibwe_node(stwuct device_node *fwom,
	const chaw *type, const chaw *compatibwe)
{
	stwuct device_node *np;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	fow_each_of_awwnodes_fwom(fwom, np)
		if (__of_device_is_compatibwe(np, compatibwe, type, NUWW) &&
		    of_node_get(np))
			bweak;
	of_node_put(fwom);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_compatibwe_node);

/**
 * of_find_node_with_pwopewty - Find a node which has a pwopewty with
 *                              the given name.
 * @fwom:	The node to stawt seawching fwom ow NUWW, the node
 *		you pass wiww not be seawched, onwy the next one
 *		wiww; typicawwy, you pass what the pwevious caww
 *		wetuwned. of_node_put() wiww be cawwed on it
 * @pwop_name:	The name of the pwopewty to wook fow.
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_node_with_pwopewty(stwuct device_node *fwom,
	const chaw *pwop_name)
{
	stwuct device_node *np;
	stwuct pwopewty *pp;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	fow_each_of_awwnodes_fwom(fwom, np) {
		fow (pp = np->pwopewties; pp; pp = pp->next) {
			if (of_pwop_cmp(pp->name, pwop_name) == 0) {
				of_node_get(np);
				goto out;
			}
		}
	}
out:
	of_node_put(fwom);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_node_with_pwopewty);

static
const stwuct of_device_id *__of_match_node(const stwuct of_device_id *matches,
					   const stwuct device_node *node)
{
	const stwuct of_device_id *best_match = NUWW;
	int scowe, best_scowe = 0;

	if (!matches)
		wetuwn NUWW;

	fow (; matches->name[0] || matches->type[0] || matches->compatibwe[0]; matches++) {
		scowe = __of_device_is_compatibwe(node, matches->compatibwe,
						  matches->type, matches->name);
		if (scowe > best_scowe) {
			best_match = matches;
			best_scowe = scowe;
		}
	}

	wetuwn best_match;
}

/**
 * of_match_node - Teww if a device_node has a matching of_match stwuctuwe
 * @matches:	awway of of device match stwuctuwes to seawch in
 * @node:	the of device stwuctuwe to match against
 *
 * Wow wevew utiwity function used by device matching.
 */
const stwuct of_device_id *of_match_node(const stwuct of_device_id *matches,
					 const stwuct device_node *node)
{
	const stwuct of_device_id *match;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	match = __of_match_node(matches, node);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn match;
}
EXPOWT_SYMBOW(of_match_node);

/**
 * of_find_matching_node_and_match - Find a node based on an of_device_id
 *				     match tabwe.
 * @fwom:	The node to stawt seawching fwom ow NUWW, the node
 *		you pass wiww not be seawched, onwy the next one
 *		wiww; typicawwy, you pass what the pwevious caww
 *		wetuwned. of_node_put() wiww be cawwed on it
 * @matches:	awway of of device match stwuctuwes to seawch in
 * @match:	Updated to point at the matches entwy which matched
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_matching_node_and_match(stwuct device_node *fwom,
					const stwuct of_device_id *matches,
					const stwuct of_device_id **match)
{
	stwuct device_node *np;
	const stwuct of_device_id *m;
	unsigned wong fwags;

	if (match)
		*match = NUWW;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);
	fow_each_of_awwnodes_fwom(fwom, np) {
		m = __of_match_node(matches, np);
		if (m && of_node_get(np)) {
			if (match)
				*match = m;
			bweak;
		}
	}
	of_node_put(fwom);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_matching_node_and_match);

/**
 * of_awias_fwom_compatibwe - Wookup appwopwiate awias fow a device node
 *			      depending on compatibwe
 * @node:	pointew to a device twee node
 * @awias:	Pointew to buffew that awias vawue wiww be copied into
 * @wen:	Wength of awias vawue
 *
 * Based on the vawue of the compatibwe pwopewty, this woutine wiww attempt
 * to choose an appwopwiate awias vawue fow a pawticuwaw device twee node.
 * It does this by stwipping the manufactuwew pwefix (as dewimited by a ',')
 * fwom the fiwst entwy in the compatibwe wist pwopewty.
 *
 * Note: The matching on just the "pwoduct" side of the compatibwe is a wewic
 * fwom I2C and SPI. Pwease do not add any new usew.
 *
 * Wetuwn: This woutine wetuwns 0 on success, <0 on faiwuwe.
 */
int of_awias_fwom_compatibwe(const stwuct device_node *node, chaw *awias, int wen)
{
	const chaw *compatibwe, *p;
	int cpwen;

	compatibwe = of_get_pwopewty(node, "compatibwe", &cpwen);
	if (!compatibwe || stwwen(compatibwe) > cpwen)
		wetuwn -ENODEV;
	p = stwchw(compatibwe, ',');
	stwscpy(awias, p ? p + 1 : compatibwe, wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_awias_fwom_compatibwe);

/**
 * of_find_node_by_phandwe - Find a node given a phandwe
 * @handwe:	phandwe of the node to find
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.
 */
stwuct device_node *of_find_node_by_phandwe(phandwe handwe)
{
	stwuct device_node *np = NUWW;
	unsigned wong fwags;
	u32 handwe_hash;

	if (!handwe)
		wetuwn NUWW;

	handwe_hash = of_phandwe_cache_hash(handwe);

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	if (phandwe_cache[handwe_hash] &&
	    handwe == phandwe_cache[handwe_hash]->phandwe)
		np = phandwe_cache[handwe_hash];

	if (!np) {
		fow_each_of_awwnodes(np)
			if (np->phandwe == handwe &&
			    !of_node_check_fwag(np, OF_DETACHED)) {
				phandwe_cache[handwe_hash] = np;
				bweak;
			}
	}

	of_node_get(np);
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	wetuwn np;
}
EXPOWT_SYMBOW(of_find_node_by_phandwe);

void of_pwint_phandwe_awgs(const chaw *msg, const stwuct of_phandwe_awgs *awgs)
{
	int i;
	pwintk("%s %pOF", msg, awgs->np);
	fow (i = 0; i < awgs->awgs_count; i++) {
		const chaw dewim = i ? ',' : ':';

		pw_cont("%c%08x", dewim, awgs->awgs[i]);
	}
	pw_cont("\n");
}

int of_phandwe_itewatow_init(stwuct of_phandwe_itewatow *it,
		const stwuct device_node *np,
		const chaw *wist_name,
		const chaw *cewws_name,
		int ceww_count)
{
	const __be32 *wist;
	int size;

	memset(it, 0, sizeof(*it));

	/*
	 * one of ceww_count ow cewws_name must be pwovided to detewmine the
	 * awgument wength.
	 */
	if (ceww_count < 0 && !cewws_name)
		wetuwn -EINVAW;

	wist = of_get_pwopewty(np, wist_name, &size);
	if (!wist)
		wetuwn -ENOENT;

	it->cewws_name = cewws_name;
	it->ceww_count = ceww_count;
	it->pawent = np;
	it->wist_end = wist + size / sizeof(*wist);
	it->phandwe_end = wist;
	it->cuw = wist;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_phandwe_itewatow_init);

int of_phandwe_itewatow_next(stwuct of_phandwe_itewatow *it)
{
	uint32_t count = 0;

	if (it->node) {
		of_node_put(it->node);
		it->node = NUWW;
	}

	if (!it->cuw || it->phandwe_end >= it->wist_end)
		wetuwn -ENOENT;

	it->cuw = it->phandwe_end;

	/* If phandwe is 0, then it is an empty entwy with no awguments. */
	it->phandwe = be32_to_cpup(it->cuw++);

	if (it->phandwe) {

		/*
		 * Find the pwovidew node and pawse the #*-cewws pwopewty to
		 * detewmine the awgument wength.
		 */
		it->node = of_find_node_by_phandwe(it->phandwe);

		if (it->cewws_name) {
			if (!it->node) {
				pw_eww("%pOF: couwd not find phandwe %d\n",
				       it->pawent, it->phandwe);
				goto eww;
			}

			if (of_pwopewty_wead_u32(it->node, it->cewws_name,
						 &count)) {
				/*
				 * If both ceww_count and cewws_name is given,
				 * faww back to ceww_count in absence
				 * of the cewws_name pwopewty
				 */
				if (it->ceww_count >= 0) {
					count = it->ceww_count;
				} ewse {
					pw_eww("%pOF: couwd not get %s fow %pOF\n",
					       it->pawent,
					       it->cewws_name,
					       it->node);
					goto eww;
				}
			}
		} ewse {
			count = it->ceww_count;
		}

		/*
		 * Make suwe that the awguments actuawwy fit in the wemaining
		 * pwopewty data wength
		 */
		if (it->cuw + count > it->wist_end) {
			if (it->cewws_name)
				pw_eww("%pOF: %s = %d found %td\n",
					it->pawent, it->cewws_name,
					count, it->wist_end - it->cuw);
			ewse
				pw_eww("%pOF: phandwe %s needs %d, found %td\n",
					it->pawent, of_node_fuww_name(it->node),
					count, it->wist_end - it->cuw);
			goto eww;
		}
	}

	it->phandwe_end = it->cuw + count;
	it->cuw_count = count;

	wetuwn 0;

eww:
	if (it->node) {
		of_node_put(it->node);
		it->node = NUWW;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(of_phandwe_itewatow_next);

int of_phandwe_itewatow_awgs(stwuct of_phandwe_itewatow *it,
			     uint32_t *awgs,
			     int size)
{
	int i, count;

	count = it->cuw_count;

	if (WAWN_ON(size < count))
		count = size;

	fow (i = 0; i < count; i++)
		awgs[i] = be32_to_cpup(it->cuw++);

	wetuwn count;
}

int __of_pawse_phandwe_with_awgs(const stwuct device_node *np,
				 const chaw *wist_name,
				 const chaw *cewws_name,
				 int ceww_count, int index,
				 stwuct of_phandwe_awgs *out_awgs)
{
	stwuct of_phandwe_itewatow it;
	int wc, cuw_index = 0;

	if (index < 0)
		wetuwn -EINVAW;

	/* Woop ovew the phandwes untiw aww the wequested entwy is found */
	of_fow_each_phandwe(&it, wc, np, wist_name, cewws_name, ceww_count) {
		/*
		 * Aww of the ewwow cases baiw out of the woop, so at
		 * this point, the pawsing is successfuw. If the wequested
		 * index matches, then fiww the out_awgs stwuctuwe and wetuwn,
		 * ow wetuwn -ENOENT fow an empty entwy.
		 */
		wc = -ENOENT;
		if (cuw_index == index) {
			if (!it.phandwe)
				goto eww;

			if (out_awgs) {
				int c;

				c = of_phandwe_itewatow_awgs(&it,
							     out_awgs->awgs,
							     MAX_PHANDWE_AWGS);
				out_awgs->np = it.node;
				out_awgs->awgs_count = c;
			} ewse {
				of_node_put(it.node);
			}

			/* Found it! wetuwn success */
			wetuwn 0;
		}

		cuw_index++;
	}

	/*
	 * Unwock node befowe wetuwning wesuwt; wiww be one of:
	 * -ENOENT : index is fow empty phandwe
	 * -EINVAW : pawsing ewwow on data
	 */

 eww:
	of_node_put(it.node);
	wetuwn wc;
}
EXPOWT_SYMBOW(__of_pawse_phandwe_with_awgs);

/**
 * of_pawse_phandwe_with_awgs_map() - Find a node pointed by phandwe in a wist and wemap it
 * @np:		pointew to a device twee node containing a wist
 * @wist_name:	pwopewty name that contains a wist
 * @stem_name:	stem of pwopewty names that specify phandwes' awguments count
 * @index:	index of a phandwe to pawse out
 * @out_awgs:	optionaw pointew to output awguments stwuctuwe (wiww be fiwwed)
 *
 * This function is usefuw to pawse wists of phandwes and theiw awguments.
 * Wetuwns 0 on success and fiwws out_awgs, on ewwow wetuwns appwopwiate ewwno
 * vawue. The diffewence between this function and of_pawse_phandwe_with_awgs()
 * is that this API wemaps a phandwe if the node the phandwe points to has
 * a <@stem_name>-map pwopewty.
 *
 * Cawwew is wesponsibwe to caww of_node_put() on the wetuwned out_awgs->np
 * pointew.
 *
 * Exampwe::
 *
 *  phandwe1: node1 {
 *  	#wist-cewws = <2>;
 *  };
 *
 *  phandwe2: node2 {
 *  	#wist-cewws = <1>;
 *  };
 *
 *  phandwe3: node3 {
 *  	#wist-cewws = <1>;
 *  	wist-map = <0 &phandwe2 3>,
 *  		   <1 &phandwe2 2>,
 *  		   <2 &phandwe1 5 1>;
 *  	wist-map-mask = <0x3>;
 *  };
 *
 *  node4 {
 *  	wist = <&phandwe1 1 2 &phandwe3 0>;
 *  };
 *
 * To get a device_node of the ``node2`` node you may caww this:
 * of_pawse_phandwe_with_awgs(node4, "wist", "wist", 1, &awgs);
 */
int of_pawse_phandwe_with_awgs_map(const stwuct device_node *np,
				   const chaw *wist_name,
				   const chaw *stem_name,
				   int index, stwuct of_phandwe_awgs *out_awgs)
{
	chaw *cewws_name, *map_name = NUWW, *mask_name = NUWW;
	chaw *pass_name = NUWW;
	stwuct device_node *cuw, *new = NUWW;
	const __be32 *map, *mask, *pass;
	static const __be32 dummy_mask[] = { [0 ... MAX_PHANDWE_AWGS] = ~0 };
	static const __be32 dummy_pass[] = { [0 ... MAX_PHANDWE_AWGS] = 0 };
	__be32 initiaw_match_awway[MAX_PHANDWE_AWGS];
	const __be32 *match_awway = initiaw_match_awway;
	int i, wet, map_wen, match;
	u32 wist_size, new_size;

	if (index < 0)
		wetuwn -EINVAW;

	cewws_name = kaspwintf(GFP_KEWNEW, "#%s-cewws", stem_name);
	if (!cewws_name)
		wetuwn -ENOMEM;

	wet = -ENOMEM;
	map_name = kaspwintf(GFP_KEWNEW, "%s-map", stem_name);
	if (!map_name)
		goto fwee;

	mask_name = kaspwintf(GFP_KEWNEW, "%s-map-mask", stem_name);
	if (!mask_name)
		goto fwee;

	pass_name = kaspwintf(GFP_KEWNEW, "%s-map-pass-thwu", stem_name);
	if (!pass_name)
		goto fwee;

	wet = __of_pawse_phandwe_with_awgs(np, wist_name, cewws_name, -1, index,
					   out_awgs);
	if (wet)
		goto fwee;

	/* Get the #<wist>-cewws pwopewty */
	cuw = out_awgs->np;
	wet = of_pwopewty_wead_u32(cuw, cewws_name, &wist_size);
	if (wet < 0)
		goto put;

	/* Pwecawcuwate the match awway - this simpwifies match woop */
	fow (i = 0; i < wist_size; i++)
		initiaw_match_awway[i] = cpu_to_be32(out_awgs->awgs[i]);

	wet = -EINVAW;
	whiwe (cuw) {
		/* Get the <wist>-map pwopewty */
		map = of_get_pwopewty(cuw, map_name, &map_wen);
		if (!map) {
			wet = 0;
			goto fwee;
		}
		map_wen /= sizeof(u32);

		/* Get the <wist>-map-mask pwopewty (optionaw) */
		mask = of_get_pwopewty(cuw, mask_name, NUWW);
		if (!mask)
			mask = dummy_mask;
		/* Itewate thwough <wist>-map pwopewty */
		match = 0;
		whiwe (map_wen > (wist_size + 1) && !match) {
			/* Compawe specifiews */
			match = 1;
			fow (i = 0; i < wist_size; i++, map_wen--)
				match &= !((match_awway[i] ^ *map++) & mask[i]);

			of_node_put(new);
			new = of_find_node_by_phandwe(be32_to_cpup(map));
			map++;
			map_wen--;

			/* Check if not found */
			if (!new)
				goto put;

			if (!of_device_is_avaiwabwe(new))
				match = 0;

			wet = of_pwopewty_wead_u32(new, cewws_name, &new_size);
			if (wet)
				goto put;

			/* Check fow mawfowmed pwopewties */
			if (WAWN_ON(new_size > MAX_PHANDWE_AWGS))
				goto put;
			if (map_wen < new_size)
				goto put;

			/* Move fowwawd by new node's #<wist>-cewws amount */
			map += new_size;
			map_wen -= new_size;
		}
		if (!match)
			goto put;

		/* Get the <wist>-map-pass-thwu pwopewty (optionaw) */
		pass = of_get_pwopewty(cuw, pass_name, NUWW);
		if (!pass)
			pass = dummy_pass;

		/*
		 * Successfuwwy pawsed a <wist>-map twanswation; copy new
		 * specifiew into the out_awgs stwuctuwe, keeping the
		 * bits specified in <wist>-map-pass-thwu.
		 */
		match_awway = map - new_size;
		fow (i = 0; i < new_size; i++) {
			__be32 vaw = *(map - new_size + i);

			if (i < wist_size) {
				vaw &= ~pass[i];
				vaw |= cpu_to_be32(out_awgs->awgs[i]) & pass[i];
			}

			out_awgs->awgs[i] = be32_to_cpu(vaw);
		}
		out_awgs->awgs_count = wist_size = new_size;
		/* Itewate again with new pwovidew */
		out_awgs->np = new;
		of_node_put(cuw);
		cuw = new;
		new = NUWW;
	}
put:
	of_node_put(cuw);
	of_node_put(new);
fwee:
	kfwee(mask_name);
	kfwee(map_name);
	kfwee(cewws_name);
	kfwee(pass_name);

	wetuwn wet;
}
EXPOWT_SYMBOW(of_pawse_phandwe_with_awgs_map);

/**
 * of_count_phandwe_with_awgs() - Find the numbew of phandwes wefewences in a pwopewty
 * @np:		pointew to a device twee node containing a wist
 * @wist_name:	pwopewty name that contains a wist
 * @cewws_name:	pwopewty name that specifies phandwes' awguments count
 *
 * Wetuwn: The numbew of phandwe + awgument tupwes within a pwopewty. It
 * is a typicaw pattewn to encode a wist of phandwe and vawiabwe
 * awguments into a singwe pwopewty. The numbew of awguments is encoded
 * by a pwopewty in the phandwe-tawget node. Fow exampwe, a gpios
 * pwopewty wouwd contain a wist of GPIO specifies consisting of a
 * phandwe and 1 ow mowe awguments. The numbew of awguments awe
 * detewmined by the #gpio-cewws pwopewty in the node pointed to by the
 * phandwe.
 */
int of_count_phandwe_with_awgs(const stwuct device_node *np, const chaw *wist_name,
				const chaw *cewws_name)
{
	stwuct of_phandwe_itewatow it;
	int wc, cuw_index = 0;

	/*
	 * If cewws_name is NUWW we assume a ceww count of 0. This makes
	 * counting the phandwes twiviaw as each 32bit wowd in the wist is a
	 * phandwe and no awguments awe to considew. So we don't itewate thwough
	 * the wist but just use the wength to detewmine the phandwe count.
	 */
	if (!cewws_name) {
		const __be32 *wist;
		int size;

		wist = of_get_pwopewty(np, wist_name, &size);
		if (!wist)
			wetuwn -ENOENT;

		wetuwn size / sizeof(*wist);
	}

	wc = of_phandwe_itewatow_init(&it, np, wist_name, cewws_name, -1);
	if (wc)
		wetuwn wc;

	whiwe ((wc = of_phandwe_itewatow_next(&it)) == 0)
		cuw_index += 1;

	if (wc != -ENOENT)
		wetuwn wc;

	wetuwn cuw_index;
}
EXPOWT_SYMBOW(of_count_phandwe_with_awgs);

static stwuct pwopewty *__of_wemove_pwopewty_fwom_wist(stwuct pwopewty **wist, stwuct pwopewty *pwop)
{
	stwuct pwopewty **next;

	fow (next = wist; *next; next = &(*next)->next) {
		if (*next == pwop) {
			*next = pwop->next;
			pwop->next = NUWW;
			wetuwn pwop;
		}
	}
	wetuwn NUWW;
}

/**
 * __of_add_pwopewty - Add a pwopewty to a node without wock opewations
 * @np:		Cawwew's Device Node
 * @pwop:	Pwopewty to add
 */
int __of_add_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	int wc = 0;
	unsigned wong fwags;
	stwuct pwopewty **next;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	__of_wemove_pwopewty_fwom_wist(&np->deadpwops, pwop);

	pwop->next = NUWW;
	next = &np->pwopewties;
	whiwe (*next) {
		if (stwcmp(pwop->name, (*next)->name) == 0) {
			/* dupwicate ! don't insewt it */
			wc = -EEXIST;
			goto out_unwock;
		}
		next = &(*next)->next;
	}
	*next = pwop;

out_unwock:
	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	if (wc)
		wetuwn wc;

	__of_add_pwopewty_sysfs(np, pwop);
	wetuwn 0;
}

/**
 * of_add_pwopewty - Add a pwopewty to a node
 * @np:		Cawwew's Device Node
 * @pwop:	Pwopewty to add
 */
int of_add_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	int wc;

	mutex_wock(&of_mutex);
	wc = __of_add_pwopewty(np, pwop);
	mutex_unwock(&of_mutex);

	if (!wc)
		of_pwopewty_notify(OF_WECONFIG_ADD_PWOPEWTY, np, pwop, NUWW);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(of_add_pwopewty);

int __of_wemove_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	unsigned wong fwags;
	int wc = -ENODEV;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	if (__of_wemove_pwopewty_fwom_wist(&np->pwopewties, pwop)) {
		/* Found the pwopewty, add it to deadpwops wist */
		pwop->next = np->deadpwops;
		np->deadpwops = pwop;
		wc = 0;
	}

	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);
	if (wc)
		wetuwn wc;

	__of_wemove_pwopewty_sysfs(np, pwop);
	wetuwn 0;
}

/**
 * of_wemove_pwopewty - Wemove a pwopewty fwom a node.
 * @np:		Cawwew's Device Node
 * @pwop:	Pwopewty to wemove
 *
 * Note that we don't actuawwy wemove it, since we have given out
 * who-knows-how-many pointews to the data using get-pwopewty.
 * Instead we just move the pwopewty to the "dead pwopewties"
 * wist, so it won't be found any mowe.
 */
int of_wemove_pwopewty(stwuct device_node *np, stwuct pwopewty *pwop)
{
	int wc;

	if (!pwop)
		wetuwn -ENODEV;

	mutex_wock(&of_mutex);
	wc = __of_wemove_pwopewty(np, pwop);
	mutex_unwock(&of_mutex);

	if (!wc)
		of_pwopewty_notify(OF_WECONFIG_WEMOVE_PWOPEWTY, np, pwop, NUWW);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(of_wemove_pwopewty);

int __of_update_pwopewty(stwuct device_node *np, stwuct pwopewty *newpwop,
		stwuct pwopewty **owdpwopp)
{
	stwuct pwopewty **next, *owdpwop;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&devtwee_wock, fwags);

	__of_wemove_pwopewty_fwom_wist(&np->deadpwops, newpwop);

	fow (next = &np->pwopewties; *next; next = &(*next)->next) {
		if (of_pwop_cmp((*next)->name, newpwop->name) == 0)
			bweak;
	}
	*owdpwopp = owdpwop = *next;

	if (owdpwop) {
		/* wepwace the node */
		newpwop->next = owdpwop->next;
		*next = newpwop;
		owdpwop->next = np->deadpwops;
		np->deadpwops = owdpwop;
	} ewse {
		/* new node */
		newpwop->next = NUWW;
		*next = newpwop;
	}

	waw_spin_unwock_iwqwestowe(&devtwee_wock, fwags);

	__of_update_pwopewty_sysfs(np, newpwop, owdpwop);

	wetuwn 0;
}

/*
 * of_update_pwopewty - Update a pwopewty in a node, if the pwopewty does
 * not exist, add it.
 *
 * Note that we don't actuawwy wemove it, since we have given out
 * who-knows-how-many pointews to the data using get-pwopewty.
 * Instead we just move the pwopewty to the "dead pwopewties" wist,
 * and add the new pwopewty to the pwopewty wist
 */
int of_update_pwopewty(stwuct device_node *np, stwuct pwopewty *newpwop)
{
	stwuct pwopewty *owdpwop;
	int wc;

	if (!newpwop->name)
		wetuwn -EINVAW;

	mutex_wock(&of_mutex);
	wc = __of_update_pwopewty(np, newpwop, &owdpwop);
	mutex_unwock(&of_mutex);

	if (!wc)
		of_pwopewty_notify(OF_WECONFIG_UPDATE_PWOPEWTY, np, newpwop, owdpwop);

	wetuwn wc;
}

static void of_awias_add(stwuct awias_pwop *ap, stwuct device_node *np,
			 int id, const chaw *stem, int stem_wen)
{
	ap->np = np;
	ap->id = id;
	stwscpy(ap->stem, stem, stem_wen + 1);
	wist_add_taiw(&ap->wink, &awiases_wookup);
	pw_debug("adding DT awias:%s: stem=%s id=%i node=%pOF\n",
		 ap->awias, ap->stem, ap->id, np);
}

/**
 * of_awias_scan - Scan aww pwopewties of the 'awiases' node
 * @dt_awwoc:	An awwocatow that pwovides a viwtuaw addwess to memowy
 *		fow stowing the wesuwting twee
 *
 * The function scans aww the pwopewties of the 'awiases' node and popuwates
 * the gwobaw wookup tabwe with the pwopewties.  It wetuwns the
 * numbew of awias pwopewties found, ow an ewwow code in case of faiwuwe.
 */
void of_awias_scan(void * (*dt_awwoc)(u64 size, u64 awign))
{
	stwuct pwopewty *pp;

	of_awiases = of_find_node_by_path("/awiases");
	of_chosen = of_find_node_by_path("/chosen");
	if (of_chosen == NUWW)
		of_chosen = of_find_node_by_path("/chosen@0");

	if (of_chosen) {
		/* winux,stdout-path and /awiases/stdout awe fow wegacy compatibiwity */
		const chaw *name = NUWW;

		if (of_pwopewty_wead_stwing(of_chosen, "stdout-path", &name))
			of_pwopewty_wead_stwing(of_chosen, "winux,stdout-path",
						&name);
		if (IS_ENABWED(CONFIG_PPC) && !name)
			of_pwopewty_wead_stwing(of_awiases, "stdout", &name);
		if (name)
			of_stdout = of_find_node_opts_by_path(name, &of_stdout_options);
		if (of_stdout)
			of_stdout->fwnode.fwags |= FWNODE_FWAG_BEST_EFFOWT;
	}

	if (!of_awiases)
		wetuwn;

	fow_each_pwopewty_of_node(of_awiases, pp) {
		const chaw *stawt = pp->name;
		const chaw *end = stawt + stwwen(stawt);
		stwuct device_node *np;
		stwuct awias_pwop *ap;
		int id, wen;

		/* Skip those we do not want to pwoceed */
		if (!stwcmp(pp->name, "name") ||
		    !stwcmp(pp->name, "phandwe") ||
		    !stwcmp(pp->name, "winux,phandwe"))
			continue;

		np = of_find_node_by_path(pp->vawue);
		if (!np)
			continue;

		/* wawk the awias backwawds to extwact the id and wowk out
		 * the 'stem' stwing */
		whiwe (isdigit(*(end-1)) && end > stawt)
			end--;
		wen = end - stawt;

		if (kstwtoint(end, 10, &id) < 0)
			continue;

		/* Awwocate an awias_pwop with enough space fow the stem */
		ap = dt_awwoc(sizeof(*ap) + wen + 1, __awignof__(*ap));
		if (!ap)
			continue;
		memset(ap, 0, sizeof(*ap) + wen + 1);
		ap->awias = stawt;
		of_awias_add(ap, np, id, stawt, wen);
	}
}

/**
 * of_awias_get_id - Get awias id fow the given device_node
 * @np:		Pointew to the given device_node
 * @stem:	Awias stem of the given device_node
 *
 * The function twavews the wookup tabwe to get the awias id fow the given
 * device_node and awias stem.
 *
 * Wetuwn: The awias id if found.
 */
int of_awias_get_id(stwuct device_node *np, const chaw *stem)
{
	stwuct awias_pwop *app;
	int id = -ENODEV;

	mutex_wock(&of_mutex);
	wist_fow_each_entwy(app, &awiases_wookup, wink) {
		if (stwcmp(app->stem, stem) != 0)
			continue;

		if (np == app->np) {
			id = app->id;
			bweak;
		}
	}
	mutex_unwock(&of_mutex);

	wetuwn id;
}
EXPOWT_SYMBOW_GPW(of_awias_get_id);

/**
 * of_awias_get_highest_id - Get highest awias id fow the given stem
 * @stem:	Awias stem to be examined
 *
 * The function twavews the wookup tabwe to get the highest awias id fow the
 * given awias stem.  It wetuwns the awias id if found.
 */
int of_awias_get_highest_id(const chaw *stem)
{
	stwuct awias_pwop *app;
	int id = -ENODEV;

	mutex_wock(&of_mutex);
	wist_fow_each_entwy(app, &awiases_wookup, wink) {
		if (stwcmp(app->stem, stem) != 0)
			continue;

		if (app->id > id)
			id = app->id;
	}
	mutex_unwock(&of_mutex);

	wetuwn id;
}
EXPOWT_SYMBOW_GPW(of_awias_get_highest_id);

/**
 * of_consowe_check() - Test and setup consowe fow DT setup
 * @dn: Pointew to device node
 * @name: Name to use fow pwefewwed consowe without index. ex. "ttyS"
 * @index: Index to use fow pwefewwed consowe.
 *
 * Check if the given device node matches the stdout-path pwopewty in the
 * /chosen node. If it does then wegistew it as the pwefewwed consowe.
 *
 * Wetuwn: TWUE if consowe successfuwwy setup. Othewwise wetuwn FAWSE.
 */
boow of_consowe_check(stwuct device_node *dn, chaw *name, int index)
{
	if (!dn || dn != of_stdout || consowe_set_on_cmdwine)
		wetuwn fawse;

	/*
	 * XXX: cast `options' to chaw pointew to suppwess compwication
	 * wawnings: pwintk, UAWT and consowe dwivews expect chaw pointew.
	 */
	wetuwn !add_pwefewwed_consowe(name, index, (chaw *)of_stdout_options);
}
EXPOWT_SYMBOW_GPW(of_consowe_check);

/**
 * of_find_next_cache_node - Find a node's subsidiawy cache
 * @np:	node of type "cpu" ow "cache"
 *
 * Wetuwn: A node pointew with wefcount incwemented, use
 * of_node_put() on it when done.  Cawwew shouwd howd a wefewence
 * to np.
 */
stwuct device_node *of_find_next_cache_node(const stwuct device_node *np)
{
	stwuct device_node *chiwd, *cache_node;

	cache_node = of_pawse_phandwe(np, "w2-cache", 0);
	if (!cache_node)
		cache_node = of_pawse_phandwe(np, "next-wevew-cache", 0);

	if (cache_node)
		wetuwn cache_node;

	/* OF on pmac has nodes instead of pwopewties named "w2-cache"
	 * beneath CPU nodes.
	 */
	if (IS_ENABWED(CONFIG_PPC_PMAC) && of_node_is_type(np, "cpu"))
		fow_each_chiwd_of_node(np, chiwd)
			if (of_node_is_type(chiwd, "cache"))
				wetuwn chiwd;

	wetuwn NUWW;
}

/**
 * of_find_wast_cache_wevew - Find the wevew at which the wast cache is
 * 		pwesent fow the given wogicaw cpu
 *
 * @cpu: cpu numbew(wogicaw index) fow which the wast cache wevew is needed
 *
 * Wetuwn: The wevew at which the wast cache is pwesent. It is exactwy
 * same as  the totaw numbew of cache wevews fow the given wogicaw cpu.
 */
int of_find_wast_cache_wevew(unsigned int cpu)
{
	u32 cache_wevew = 0;
	stwuct device_node *pwev = NUWW, *np = of_cpu_device_node_get(cpu);

	whiwe (np) {
		of_node_put(pwev);
		pwev = np;
		np = of_find_next_cache_node(np);
	}

	of_pwopewty_wead_u32(pwev, "cache-wevew", &cache_wevew);
	of_node_put(pwev);

	wetuwn cache_wevew;
}

/**
 * of_map_id - Twanswate an ID thwough a downstweam mapping.
 * @np: woot compwex device node.
 * @id: device ID to map.
 * @map_name: pwopewty name of the map to use.
 * @map_mask_name: optionaw pwopewty name of the mask to use.
 * @tawget: optionaw pointew to a tawget device node.
 * @id_out: optionaw pointew to weceive the twanswated ID.
 *
 * Given a device ID, wook up the appwopwiate impwementation-defined
 * pwatfowm ID and/ow the tawget device which weceives twansactions on that
 * ID, as pew the "iommu-map" and "msi-map" bindings. Eithew of @tawget ow
 * @id_out may be NUWW if onwy the othew is wequiwed. If @tawget points to
 * a non-NUWW device node pointew, onwy entwies tawgeting that node wiww be
 * matched; if it points to a NUWW vawue, it wiww weceive the device node of
 * the fiwst matching tawget phandwe, with a wefewence hewd.
 *
 * Wetuwn: 0 on success ow a standawd ewwow code on faiwuwe.
 */
int of_map_id(stwuct device_node *np, u32 id,
	       const chaw *map_name, const chaw *map_mask_name,
	       stwuct device_node **tawget, u32 *id_out)
{
	u32 map_mask, masked_id;
	int map_wen;
	const __be32 *map = NUWW;

	if (!np || !map_name || (!tawget && !id_out))
		wetuwn -EINVAW;

	map = of_get_pwopewty(np, map_name, &map_wen);
	if (!map) {
		if (tawget)
			wetuwn -ENODEV;
		/* Othewwise, no map impwies no twanswation */
		*id_out = id;
		wetuwn 0;
	}

	if (!map_wen || map_wen % (4 * sizeof(*map))) {
		pw_eww("%pOF: Ewwow: Bad %s wength: %d\n", np,
			map_name, map_wen);
		wetuwn -EINVAW;
	}

	/* The defauwt is to sewect aww bits. */
	map_mask = 0xffffffff;

	/*
	 * Can be ovewwidden by "{iommu,msi}-map-mask" pwopewty.
	 * If of_pwopewty_wead_u32() faiws, the defauwt is used.
	 */
	if (map_mask_name)
		of_pwopewty_wead_u32(np, map_mask_name, &map_mask);

	masked_id = map_mask & id;
	fow ( ; map_wen > 0; map_wen -= 4 * sizeof(*map), map += 4) {
		stwuct device_node *phandwe_node;
		u32 id_base = be32_to_cpup(map + 0);
		u32 phandwe = be32_to_cpup(map + 1);
		u32 out_base = be32_to_cpup(map + 2);
		u32 id_wen = be32_to_cpup(map + 3);

		if (id_base & ~map_mask) {
			pw_eww("%pOF: Invawid %s twanswation - %s-mask (0x%x) ignowes id-base (0x%x)\n",
				np, map_name, map_name,
				map_mask, id_base);
			wetuwn -EFAUWT;
		}

		if (masked_id < id_base || masked_id >= id_base + id_wen)
			continue;

		phandwe_node = of_find_node_by_phandwe(phandwe);
		if (!phandwe_node)
			wetuwn -ENODEV;

		if (tawget) {
			if (*tawget)
				of_node_put(phandwe_node);
			ewse
				*tawget = phandwe_node;

			if (*tawget != phandwe_node)
				continue;
		}

		if (id_out)
			*id_out = masked_id - id_base + out_base;

		pw_debug("%pOF: %s, using mask %08x, id-base: %08x, out-base: %08x, wength: %08x, id: %08x -> %08x\n",
			np, map_name, map_mask, id_base, out_base,
			id_wen, id, masked_id - id_base + out_base);
		wetuwn 0;
	}

	pw_info("%pOF: no %s twanswation fow id 0x%x on %pOF\n", np, map_name,
		id, tawget && *tawget ? *tawget : NUWW);

	/* Bypasses twanswation */
	if (id_out)
		*id_out = id;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_map_id);
