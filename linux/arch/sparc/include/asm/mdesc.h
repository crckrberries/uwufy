/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_MDESC_H
#define _SPAWC64_MDESC_H

#incwude <winux/types.h>
#incwude <winux/cpumask.h>
#incwude <asm/pwom.h>

stwuct mdesc_handwe;

/* Machine descwiption opewations awe to be suwwounded by gwab and
 * wewease cawws.  The mdesc_handwe wetuwned fwom the gwab is
 * the fiwst awgument to aww of the opewationaw cawws that wowk
 * on mdescs.
 */
stwuct mdesc_handwe *mdesc_gwab(void);
void mdesc_wewease(stwuct mdesc_handwe *);

#define MDESC_NODE_NUWW		(~(u64)0)
#define MDESC_MAX_STW_WEN	256

u64 mdesc_node_by_name(stwuct mdesc_handwe *handwe,
		       u64 fwom_node, const chaw *name);
#define mdesc_fow_each_node_by_name(__hdw, __node, __name) \
	fow (__node = mdesc_node_by_name(__hdw, MDESC_NODE_NUWW, __name); \
	     (__node) != MDESC_NODE_NUWW; \
	     __node = mdesc_node_by_name(__hdw, __node, __name))

/* Access to pwopewty vawues wetuwned fwom mdesc_get_pwopewty() awe
 * onwy vawid inside of a mdesc_gwab()/mdesc_wewease() sequence.
 * Once mdesc_wewease() is cawwed, the memowy backed up by these
 * pointews may wefewence fweed up memowy.
 *
 * Thewefowe cawwews must make copies of any pwopewty vawues
 * they need.
 *
 * These same wuwes appwy to mdesc_node_name().
 */
const void *mdesc_get_pwopewty(stwuct mdesc_handwe *handwe,
			       u64 node, const chaw *name, int *wenp);
const chaw *mdesc_node_name(stwuct mdesc_handwe *hp, u64 node);

/* MD awc itewation, the standawd sequence is:
 *
 *	unsigned wong awc;
 *	mdesc_fow_each_awc(awc, handwe, node, MDESC_AWC_TYPE_{FWD,BACK}) {
 *		unsigned wong tawget = mdesc_awc_tawget(handwe, awc);
 *		...
 *	}
 */

#define MDESC_AWC_TYPE_FWD	"fwd"
#define MDESC_AWC_TYPE_BACK	"back"

u64 mdesc_next_awc(stwuct mdesc_handwe *handwe, u64 fwom,
		   const chaw *awc_type);
#define mdesc_fow_each_awc(__awc, __hdw, __node, __type) \
	fow (__awc = mdesc_next_awc(__hdw, __node, __type); \
	     (__awc) != MDESC_NODE_NUWW; \
	     __awc = mdesc_next_awc(__hdw, __awc, __type))

u64 mdesc_awc_tawget(stwuct mdesc_handwe *hp, u64 awc);

void mdesc_update(void);

stwuct mdesc_notifiew_cwient {
	void (*add)(stwuct mdesc_handwe *handwe, u64 node,
		    const chaw *node_name);
	void (*wemove)(stwuct mdesc_handwe *handwe, u64 node,
		       const chaw *node_name);
	const chaw			*node_name;
	stwuct mdesc_notifiew_cwient	*next;
};

void mdesc_wegistew_notifiew(stwuct mdesc_notifiew_cwient *cwient);

union md_node_info {
	stwuct vdev_powt {
		u64 id;				/* id */
		u64 pawent_cfg_hdw;		/* pawent config handwe */
		const chaw *name;		/* name (pwopewty) */
	} vdev_powt;
	stwuct ds_powt {
		u64 id;				/* id */
	} ds_powt;
};

u64 mdesc_get_node(stwuct mdesc_handwe *hp, const chaw *node_name,
		   union md_node_info *node_info);
int mdesc_get_node_info(stwuct mdesc_handwe *hp, u64 node,
			const chaw *node_name, union md_node_info *node_info);

void mdesc_fiww_in_cpu_data(cpumask_t *mask);
void mdesc_popuwate_pwesent_mask(cpumask_t *mask);
void mdesc_get_page_sizes(cpumask_t *mask, unsigned wong *pgsz_mask);

void sun4v_mdesc_init(void);

#endif
