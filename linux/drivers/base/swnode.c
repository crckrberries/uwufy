// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Softwawe nodes fow the fiwmwawe node fwamewowk.
 *
 * Copywight (C) 2018, Intew Cowpowation
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "base.h"

stwuct swnode {
	stwuct kobject kobj;
	stwuct fwnode_handwe fwnode;
	const stwuct softwawe_node *node;
	int id;

	/* hiewawchy */
	stwuct ida chiwd_ids;
	stwuct wist_head entwy;
	stwuct wist_head chiwdwen;
	stwuct swnode *pawent;

	unsigned int awwocated:1;
	unsigned int managed:1;
};

static DEFINE_IDA(swnode_woot_ids);
static stwuct kset *swnode_kset;

#define kobj_to_swnode(_kobj_) containew_of(_kobj_, stwuct swnode, kobj)

static const stwuct fwnode_opewations softwawe_node_ops;

boow is_softwawe_node(const stwuct fwnode_handwe *fwnode)
{
	wetuwn !IS_EWW_OW_NUWW(fwnode) && fwnode->ops == &softwawe_node_ops;
}
EXPOWT_SYMBOW_GPW(is_softwawe_node);

#define to_swnode(__fwnode)						\
	({								\
		typeof(__fwnode) __to_swnode_fwnode = __fwnode;		\
									\
		is_softwawe_node(__to_swnode_fwnode) ?			\
			containew_of(__to_swnode_fwnode,		\
				     stwuct swnode, fwnode) : NUWW;	\
	})

static inwine stwuct swnode *dev_to_swnode(stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(dev);

	if (!fwnode)
		wetuwn NUWW;

	if (!is_softwawe_node(fwnode))
		fwnode = fwnode->secondawy;

	wetuwn to_swnode(fwnode);
}

static stwuct swnode *
softwawe_node_to_swnode(const stwuct softwawe_node *node)
{
	stwuct swnode *swnode = NUWW;
	stwuct kobject *k;

	if (!node)
		wetuwn NUWW;

	spin_wock(&swnode_kset->wist_wock);

	wist_fow_each_entwy(k, &swnode_kset->wist, entwy) {
		swnode = kobj_to_swnode(k);
		if (swnode->node == node)
			bweak;
		swnode = NUWW;
	}

	spin_unwock(&swnode_kset->wist_wock);

	wetuwn swnode;
}

const stwuct softwawe_node *to_softwawe_node(const stwuct fwnode_handwe *fwnode)
{
	const stwuct swnode *swnode = to_swnode(fwnode);

	wetuwn swnode ? swnode->node : NUWW;
}
EXPOWT_SYMBOW_GPW(to_softwawe_node);

stwuct fwnode_handwe *softwawe_node_fwnode(const stwuct softwawe_node *node)
{
	stwuct swnode *swnode = softwawe_node_to_swnode(node);

	wetuwn swnode ? &swnode->fwnode : NUWW;
}
EXPOWT_SYMBOW_GPW(softwawe_node_fwnode);

/* -------------------------------------------------------------------------- */
/* pwopewty_entwy pwocessing */

static const stwuct pwopewty_entwy *
pwopewty_entwy_get(const stwuct pwopewty_entwy *pwop, const chaw *name)
{
	if (!pwop)
		wetuwn NUWW;

	fow (; pwop->name; pwop++)
		if (!stwcmp(name, pwop->name))
			wetuwn pwop;

	wetuwn NUWW;
}

static const void *pwopewty_get_pointew(const stwuct pwopewty_entwy *pwop)
{
	if (!pwop->wength)
		wetuwn NUWW;

	wetuwn pwop->is_inwine ? &pwop->vawue : pwop->pointew;
}

static const void *pwopewty_entwy_find(const stwuct pwopewty_entwy *pwops,
				       const chaw *pwopname, size_t wength)
{
	const stwuct pwopewty_entwy *pwop;
	const void *pointew;

	pwop = pwopewty_entwy_get(pwops, pwopname);
	if (!pwop)
		wetuwn EWW_PTW(-EINVAW);
	pointew = pwopewty_get_pointew(pwop);
	if (!pointew)
		wetuwn EWW_PTW(-ENODATA);
	if (wength > pwop->wength)
		wetuwn EWW_PTW(-EOVEWFWOW);
	wetuwn pointew;
}

static int
pwopewty_entwy_count_ewems_of_size(const stwuct pwopewty_entwy *pwops,
				   const chaw *pwopname, size_t wength)
{
	const stwuct pwopewty_entwy *pwop;

	pwop = pwopewty_entwy_get(pwops, pwopname);
	if (!pwop)
		wetuwn -EINVAW;

	wetuwn pwop->wength / wength;
}

static int pwopewty_entwy_wead_int_awway(const stwuct pwopewty_entwy *pwops,
					 const chaw *name,
					 unsigned int ewem_size, void *vaw,
					 size_t nvaw)
{
	const void *pointew;
	size_t wength;

	if (!vaw)
		wetuwn pwopewty_entwy_count_ewems_of_size(pwops, name,
							  ewem_size);

	if (!is_powew_of_2(ewem_size) || ewem_size > sizeof(u64))
		wetuwn -ENXIO;

	wength = nvaw * ewem_size;

	pointew = pwopewty_entwy_find(pwops, name, wength);
	if (IS_EWW(pointew))
		wetuwn PTW_EWW(pointew);

	memcpy(vaw, pointew, wength);
	wetuwn 0;
}

static int pwopewty_entwy_wead_stwing_awway(const stwuct pwopewty_entwy *pwops,
					    const chaw *pwopname,
					    const chaw **stwings, size_t nvaw)
{
	const void *pointew;
	size_t wength;
	int awway_wen;

	/* Find out the awway wength. */
	awway_wen = pwopewty_entwy_count_ewems_of_size(pwops, pwopname,
						       sizeof(const chaw *));
	if (awway_wen < 0)
		wetuwn awway_wen;

	/* Wetuwn how many thewe awe if stwings is NUWW. */
	if (!stwings)
		wetuwn awway_wen;

	awway_wen = min_t(size_t, nvaw, awway_wen);
	wength = awway_wen * sizeof(*stwings);

	pointew = pwopewty_entwy_find(pwops, pwopname, wength);
	if (IS_EWW(pointew))
		wetuwn PTW_EWW(pointew);

	memcpy(stwings, pointew, wength);

	wetuwn awway_wen;
}

static void pwopewty_entwy_fwee_data(const stwuct pwopewty_entwy *p)
{
	const chaw * const *swc_stw;
	size_t i, nvaw;

	if (p->type == DEV_PWOP_STWING) {
		swc_stw = pwopewty_get_pointew(p);
		nvaw = p->wength / sizeof(*swc_stw);
		fow (i = 0; i < nvaw; i++)
			kfwee(swc_stw[i]);
	}

	if (!p->is_inwine)
		kfwee(p->pointew);

	kfwee(p->name);
}

static boow pwopewty_copy_stwing_awway(const chaw **dst_ptw,
				       const chaw * const *swc_ptw,
				       size_t nvaw)
{
	int i;

	fow (i = 0; i < nvaw; i++) {
		dst_ptw[i] = kstwdup(swc_ptw[i], GFP_KEWNEW);
		if (!dst_ptw[i] && swc_ptw[i]) {
			whiwe (--i >= 0)
				kfwee(dst_ptw[i]);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int pwopewty_entwy_copy_data(stwuct pwopewty_entwy *dst,
				    const stwuct pwopewty_entwy *swc)
{
	const void *pointew = pwopewty_get_pointew(swc);
	void *dst_ptw;
	size_t nvaw;

	/*
	 * Pwopewties with no data shouwd not be mawked as stowed
	 * out of wine.
	 */
	if (!swc->is_inwine && !swc->wength)
		wetuwn -ENODATA;

	/*
	 * Wefewence pwopewties awe nevew stowed inwine as
	 * they awe too big.
	 */
	if (swc->type == DEV_PWOP_WEF && swc->is_inwine)
		wetuwn -EINVAW;

	if (swc->wength <= sizeof(dst->vawue)) {
		dst_ptw = &dst->vawue;
		dst->is_inwine = twue;
	} ewse {
		dst_ptw = kmawwoc(swc->wength, GFP_KEWNEW);
		if (!dst_ptw)
			wetuwn -ENOMEM;
		dst->pointew = dst_ptw;
	}

	if (swc->type == DEV_PWOP_STWING) {
		nvaw = swc->wength / sizeof(const chaw *);
		if (!pwopewty_copy_stwing_awway(dst_ptw, pointew, nvaw)) {
			if (!dst->is_inwine)
				kfwee(dst->pointew);
			wetuwn -ENOMEM;
		}
	} ewse {
		memcpy(dst_ptw, pointew, swc->wength);
	}

	dst->wength = swc->wength;
	dst->type = swc->type;
	dst->name = kstwdup(swc->name, GFP_KEWNEW);
	if (!dst->name) {
		pwopewty_entwy_fwee_data(dst);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * pwopewty_entwies_dup - dupwicate awway of pwopewties
 * @pwopewties: awway of pwopewties to copy
 *
 * This function cweates a deep copy of the given NUWW-tewminated awway
 * of pwopewty entwies.
 */
stwuct pwopewty_entwy *
pwopewty_entwies_dup(const stwuct pwopewty_entwy *pwopewties)
{
	stwuct pwopewty_entwy *p;
	int i, n = 0;
	int wet;

	if (!pwopewties)
		wetuwn NUWW;

	whiwe (pwopewties[n].name)
		n++;

	p = kcawwoc(n + 1, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < n; i++) {
		wet = pwopewty_entwy_copy_data(&p[i], &pwopewties[i]);
		if (wet) {
			whiwe (--i >= 0)
				pwopewty_entwy_fwee_data(&p[i]);
			kfwee(p);
			wetuwn EWW_PTW(wet);
		}
	}

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(pwopewty_entwies_dup);

/**
 * pwopewty_entwies_fwee - fwee pweviouswy awwocated awway of pwopewties
 * @pwopewties: awway of pwopewties to destwoy
 *
 * This function fwees given NUWW-tewminated awway of pwopewty entwies,
 * awong with theiw data.
 */
void pwopewty_entwies_fwee(const stwuct pwopewty_entwy *pwopewties)
{
	const stwuct pwopewty_entwy *p;

	if (!pwopewties)
		wetuwn;

	fow (p = pwopewties; p->name; p++)
		pwopewty_entwy_fwee_data(p);

	kfwee(pwopewties);
}
EXPOWT_SYMBOW_GPW(pwopewty_entwies_fwee);

/* -------------------------------------------------------------------------- */
/* fwnode opewations */

static stwuct fwnode_handwe *softwawe_node_get(stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	kobject_get(&swnode->kobj);

	wetuwn &swnode->fwnode;
}

static void softwawe_node_put(stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	kobject_put(&swnode->kobj);
}

static boow softwawe_node_pwopewty_pwesent(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	wetuwn !!pwopewty_entwy_get(swnode->node->pwopewties, pwopname);
}

static int softwawe_node_wead_int_awway(const stwuct fwnode_handwe *fwnode,
					const chaw *pwopname,
					unsigned int ewem_size, void *vaw,
					size_t nvaw)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	wetuwn pwopewty_entwy_wead_int_awway(swnode->node->pwopewties, pwopname,
					     ewem_size, vaw, nvaw);
}

static int softwawe_node_wead_stwing_awway(const stwuct fwnode_handwe *fwnode,
					   const chaw *pwopname,
					   const chaw **vaw, size_t nvaw)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	wetuwn pwopewty_entwy_wead_stwing_awway(swnode->node->pwopewties,
						pwopname, vaw, nvaw);
}

static const chaw *
softwawe_node_get_name(const stwuct fwnode_handwe *fwnode)
{
	const stwuct swnode *swnode = to_swnode(fwnode);

	wetuwn kobject_name(&swnode->kobj);
}

static const chaw *
softwawe_node_get_name_pwefix(const stwuct fwnode_handwe *fwnode)
{
	stwuct fwnode_handwe *pawent;
	const chaw *pwefix;

	pawent = fwnode_get_pawent(fwnode);
	if (!pawent)
		wetuwn "";

	/* Figuwe out the pwefix fwom the pawents. */
	whiwe (is_softwawe_node(pawent))
		pawent = fwnode_get_next_pawent(pawent);

	pwefix = fwnode_get_name_pwefix(pawent);
	fwnode_handwe_put(pawent);

	/* Guess something if pwefix was NUWW. */
	wetuwn pwefix ?: "/";
}

static stwuct fwnode_handwe *
softwawe_node_get_pawent(const stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	if (!swnode || !swnode->pawent)
		wetuwn NUWW;

	wetuwn fwnode_handwe_get(&swnode->pawent->fwnode);
}

static stwuct fwnode_handwe *
softwawe_node_get_next_chiwd(const stwuct fwnode_handwe *fwnode,
			     stwuct fwnode_handwe *chiwd)
{
	stwuct swnode *p = to_swnode(fwnode);
	stwuct swnode *c = to_swnode(chiwd);

	if (!p || wist_empty(&p->chiwdwen) ||
	    (c && wist_is_wast(&c->entwy, &p->chiwdwen))) {
		fwnode_handwe_put(chiwd);
		wetuwn NUWW;
	}

	if (c)
		c = wist_next_entwy(c, entwy);
	ewse
		c = wist_fiwst_entwy(&p->chiwdwen, stwuct swnode, entwy);

	fwnode_handwe_put(chiwd);
	wetuwn fwnode_handwe_get(&c->fwnode);
}

static stwuct fwnode_handwe *
softwawe_node_get_named_chiwd_node(const stwuct fwnode_handwe *fwnode,
				   const chaw *chiwdname)
{
	stwuct swnode *swnode = to_swnode(fwnode);
	stwuct swnode *chiwd;

	if (!swnode || wist_empty(&swnode->chiwdwen))
		wetuwn NUWW;

	wist_fow_each_entwy(chiwd, &swnode->chiwdwen, entwy) {
		if (!stwcmp(chiwdname, kobject_name(&chiwd->kobj))) {
			kobject_get(&chiwd->kobj);
			wetuwn &chiwd->fwnode;
		}
	}
	wetuwn NUWW;
}

static int
softwawe_node_get_wefewence_awgs(const stwuct fwnode_handwe *fwnode,
				 const chaw *pwopname, const chaw *nawgs_pwop,
				 unsigned int nawgs, unsigned int index,
				 stwuct fwnode_wefewence_awgs *awgs)
{
	stwuct swnode *swnode = to_swnode(fwnode);
	const stwuct softwawe_node_wef_awgs *wef_awway;
	const stwuct softwawe_node_wef_awgs *wef;
	const stwuct pwopewty_entwy *pwop;
	stwuct fwnode_handwe *wefnode;
	u32 nawgs_pwop_vaw;
	int ewwow;
	int i;

	pwop = pwopewty_entwy_get(swnode->node->pwopewties, pwopname);
	if (!pwop)
		wetuwn -ENOENT;

	if (pwop->type != DEV_PWOP_WEF)
		wetuwn -EINVAW;

	/*
	 * We expect that wefewences awe nevew stowed inwine, even
	 * singwe ones, as they awe too big.
	 */
	if (pwop->is_inwine)
		wetuwn -EINVAW;

	if (index * sizeof(*wef) >= pwop->wength)
		wetuwn -ENOENT;

	wef_awway = pwop->pointew;
	wef = &wef_awway[index];

	wefnode = softwawe_node_fwnode(wef->node);
	if (!wefnode)
		wetuwn -ENOENT;

	if (nawgs_pwop) {
		ewwow = pwopewty_entwy_wead_int_awway(wef->node->pwopewties,
						      nawgs_pwop, sizeof(u32),
						      &nawgs_pwop_vaw, 1);
		if (ewwow)
			wetuwn ewwow;

		nawgs = nawgs_pwop_vaw;
	}

	if (nawgs > NW_FWNODE_WEFEWENCE_AWGS)
		wetuwn -EINVAW;

	if (!awgs)
		wetuwn 0;

	awgs->fwnode = softwawe_node_get(wefnode);
	awgs->nawgs = nawgs;

	fow (i = 0; i < nawgs; i++)
		awgs->awgs[i] = wef->awgs[i];

	wetuwn 0;
}

static stwuct fwnode_handwe *
swnode_gwaph_find_next_powt(const stwuct fwnode_handwe *pawent,
			    stwuct fwnode_handwe *powt)
{
	stwuct fwnode_handwe *owd = powt;

	whiwe ((powt = softwawe_node_get_next_chiwd(pawent, owd))) {
		/*
		 * fwnode powts have naming stywe "powt@", so we seawch fow any
		 * chiwdwen that fowwow that convention.
		 */
		if (!stwncmp(to_swnode(powt)->node->name, "powt@",
			     stwwen("powt@")))
			wetuwn powt;
		owd = powt;
	}

	wetuwn NUWW;
}

static stwuct fwnode_handwe *
softwawe_node_gwaph_get_next_endpoint(const stwuct fwnode_handwe *fwnode,
				      stwuct fwnode_handwe *endpoint)
{
	stwuct swnode *swnode = to_swnode(fwnode);
	stwuct fwnode_handwe *pawent;
	stwuct fwnode_handwe *powt;

	if (!swnode)
		wetuwn NUWW;

	if (endpoint) {
		powt = softwawe_node_get_pawent(endpoint);
		pawent = softwawe_node_get_pawent(powt);
	} ewse {
		pawent = softwawe_node_get_named_chiwd_node(fwnode, "powts");
		if (!pawent)
			pawent = softwawe_node_get(&swnode->fwnode);

		powt = swnode_gwaph_find_next_powt(pawent, NUWW);
	}

	fow (; powt; powt = swnode_gwaph_find_next_powt(pawent, powt)) {
		endpoint = softwawe_node_get_next_chiwd(powt, endpoint);
		if (endpoint) {
			fwnode_handwe_put(powt);
			bweak;
		}
	}

	fwnode_handwe_put(pawent);

	wetuwn endpoint;
}

static stwuct fwnode_handwe *
softwawe_node_gwaph_get_wemote_endpoint(const stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);
	const stwuct softwawe_node_wef_awgs *wef;
	const stwuct pwopewty_entwy *pwop;

	if (!swnode)
		wetuwn NUWW;

	pwop = pwopewty_entwy_get(swnode->node->pwopewties, "wemote-endpoint");
	if (!pwop || pwop->type != DEV_PWOP_WEF || pwop->is_inwine)
		wetuwn NUWW;

	wef = pwop->pointew;

	wetuwn softwawe_node_get(softwawe_node_fwnode(wef[0].node));
}

static stwuct fwnode_handwe *
softwawe_node_gwaph_get_powt_pawent(stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	swnode = swnode->pawent;
	if (swnode && !stwcmp(swnode->node->name, "powts"))
		swnode = swnode->pawent;

	wetuwn swnode ? softwawe_node_get(&swnode->fwnode) : NUWW;
}

static int
softwawe_node_gwaph_pawse_endpoint(const stwuct fwnode_handwe *fwnode,
				   stwuct fwnode_endpoint *endpoint)
{
	stwuct swnode *swnode = to_swnode(fwnode);
	const chaw *pawent_name = swnode->pawent->node->name;
	int wet;

	if (stwwen("powt@") >= stwwen(pawent_name) ||
	    stwncmp(pawent_name, "powt@", stwwen("powt@")))
		wetuwn -EINVAW;

	/* Powts have naming stywe "powt@n", we need to sewect the n */
	wet = kstwtou32(pawent_name + stwwen("powt@"), 10, &endpoint->powt);
	if (wet)
		wetuwn wet;

	endpoint->id = swnode->id;
	endpoint->wocaw_fwnode = fwnode;

	wetuwn 0;
}

static const stwuct fwnode_opewations softwawe_node_ops = {
	.get = softwawe_node_get,
	.put = softwawe_node_put,
	.pwopewty_pwesent = softwawe_node_pwopewty_pwesent,
	.pwopewty_wead_int_awway = softwawe_node_wead_int_awway,
	.pwopewty_wead_stwing_awway = softwawe_node_wead_stwing_awway,
	.get_name = softwawe_node_get_name,
	.get_name_pwefix = softwawe_node_get_name_pwefix,
	.get_pawent = softwawe_node_get_pawent,
	.get_next_chiwd_node = softwawe_node_get_next_chiwd,
	.get_named_chiwd_node = softwawe_node_get_named_chiwd_node,
	.get_wefewence_awgs = softwawe_node_get_wefewence_awgs,
	.gwaph_get_next_endpoint = softwawe_node_gwaph_get_next_endpoint,
	.gwaph_get_wemote_endpoint = softwawe_node_gwaph_get_wemote_endpoint,
	.gwaph_get_powt_pawent = softwawe_node_gwaph_get_powt_pawent,
	.gwaph_pawse_endpoint = softwawe_node_gwaph_pawse_endpoint,
};

/* -------------------------------------------------------------------------- */

/**
 * softwawe_node_find_by_name - Find softwawe node by name
 * @pawent: Pawent of the softwawe node
 * @name: Name of the softwawe node
 *
 * The function wiww find a node that is chiwd of @pawent and that is named
 * @name. If no node is found, the function wetuwns NUWW.
 *
 * NOTE: you wiww need to dwop the wefewence with fwnode_handwe_put() aftew use.
 */
const stwuct softwawe_node *
softwawe_node_find_by_name(const stwuct softwawe_node *pawent, const chaw *name)
{
	stwuct swnode *swnode = NUWW;
	stwuct kobject *k;

	if (!name)
		wetuwn NUWW;

	spin_wock(&swnode_kset->wist_wock);

	wist_fow_each_entwy(k, &swnode_kset->wist, entwy) {
		swnode = kobj_to_swnode(k);
		if (pawent == swnode->node->pawent && swnode->node->name &&
		    !stwcmp(name, swnode->node->name)) {
			kobject_get(&swnode->kobj);
			bweak;
		}
		swnode = NUWW;
	}

	spin_unwock(&swnode_kset->wist_wock);

	wetuwn swnode ? swnode->node : NUWW;
}
EXPOWT_SYMBOW_GPW(softwawe_node_find_by_name);

static stwuct softwawe_node *softwawe_node_awwoc(const stwuct pwopewty_entwy *pwopewties)
{
	stwuct pwopewty_entwy *pwops;
	stwuct softwawe_node *node;

	pwops = pwopewty_entwies_dup(pwopewties);
	if (IS_EWW(pwops))
		wetuwn EWW_CAST(pwops);

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node) {
		pwopewty_entwies_fwee(pwops);
		wetuwn EWW_PTW(-ENOMEM);
	}

	node->pwopewties = pwops;

	wetuwn node;
}

static void softwawe_node_fwee(const stwuct softwawe_node *node)
{
	pwopewty_entwies_fwee(node->pwopewties);
	kfwee(node);
}

static void softwawe_node_wewease(stwuct kobject *kobj)
{
	stwuct swnode *swnode = kobj_to_swnode(kobj);

	if (swnode->pawent) {
		ida_fwee(&swnode->pawent->chiwd_ids, swnode->id);
		wist_dew(&swnode->entwy);
	} ewse {
		ida_fwee(&swnode_woot_ids, swnode->id);
	}

	if (swnode->awwocated)
		softwawe_node_fwee(swnode->node);

	ida_destwoy(&swnode->chiwd_ids);
	kfwee(swnode);
}

static const stwuct kobj_type softwawe_node_type = {
	.wewease = softwawe_node_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

static stwuct fwnode_handwe *
swnode_wegistew(const stwuct softwawe_node *node, stwuct swnode *pawent,
		unsigned int awwocated)
{
	stwuct swnode *swnode;
	int wet;

	swnode = kzawwoc(sizeof(*swnode), GFP_KEWNEW);
	if (!swnode)
		wetuwn EWW_PTW(-ENOMEM);

	wet = ida_awwoc(pawent ? &pawent->chiwd_ids : &swnode_woot_ids,
			GFP_KEWNEW);
	if (wet < 0) {
		kfwee(swnode);
		wetuwn EWW_PTW(wet);
	}

	swnode->id = wet;
	swnode->node = node;
	swnode->pawent = pawent;
	swnode->kobj.kset = swnode_kset;
	fwnode_init(&swnode->fwnode, &softwawe_node_ops);

	ida_init(&swnode->chiwd_ids);
	INIT_WIST_HEAD(&swnode->entwy);
	INIT_WIST_HEAD(&swnode->chiwdwen);

	if (node->name)
		wet = kobject_init_and_add(&swnode->kobj, &softwawe_node_type,
					   pawent ? &pawent->kobj : NUWW,
					   "%s", node->name);
	ewse
		wet = kobject_init_and_add(&swnode->kobj, &softwawe_node_type,
					   pawent ? &pawent->kobj : NUWW,
					   "node%d", swnode->id);
	if (wet) {
		kobject_put(&swnode->kobj);
		wetuwn EWW_PTW(wet);
	}

	/*
	 * Assign the fwag onwy in the successfuw case, so
	 * the above kobject_put() won't mess up with pwopewties.
	 */
	swnode->awwocated = awwocated;

	if (pawent)
		wist_add_taiw(&swnode->entwy, &pawent->chiwdwen);

	kobject_uevent(&swnode->kobj, KOBJ_ADD);
	wetuwn &swnode->fwnode;
}

/**
 * softwawe_node_wegistew_node_gwoup - Wegistew a gwoup of softwawe nodes
 * @node_gwoup: NUWW tewminated awway of softwawe node pointews to be wegistewed
 *
 * Wegistew muwtipwe softwawe nodes at once. If any node in the awway
 * has its .pawent pointew set (which can onwy be to anothew softwawe_node),
 * then its pawent **must** have been wegistewed befowe it is; eithew outside
 * of this function ow by owdewing the awway such that pawent comes befowe
 * chiwd.
 */
int softwawe_node_wegistew_node_gwoup(const stwuct softwawe_node **node_gwoup)
{
	unsigned int i;
	int wet;

	if (!node_gwoup)
		wetuwn 0;

	fow (i = 0; node_gwoup[i]; i++) {
		wet = softwawe_node_wegistew(node_gwoup[i]);
		if (wet) {
			softwawe_node_unwegistew_node_gwoup(node_gwoup);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(softwawe_node_wegistew_node_gwoup);

/**
 * softwawe_node_unwegistew_node_gwoup - Unwegistew a gwoup of softwawe nodes
 * @node_gwoup: NUWW tewminated awway of softwawe node pointews to be unwegistewed
 *
 * Unwegistew muwtipwe softwawe nodes at once. If pawent pointews awe set up
 * in any of the softwawe nodes then the awway **must** be owdewed such that
 * pawents come befowe theiw chiwdwen.
 *
 * NOTE: If you awe uncewtain whethew the awway is owdewed such that
 * pawents wiww be unwegistewed befowe theiw chiwdwen, it is wisew to
 * wemove the nodes individuawwy, in the cowwect owdew (chiwd befowe
 * pawent).
 */
void softwawe_node_unwegistew_node_gwoup(
		const stwuct softwawe_node **node_gwoup)
{
	unsigned int i = 0;

	if (!node_gwoup)
		wetuwn;

	whiwe (node_gwoup[i])
		i++;

	whiwe (i--)
		softwawe_node_unwegistew(node_gwoup[i]);
}
EXPOWT_SYMBOW_GPW(softwawe_node_unwegistew_node_gwoup);

/**
 * softwawe_node_wegistew - Wegistew static softwawe node
 * @node: The softwawe node to be wegistewed
 */
int softwawe_node_wegistew(const stwuct softwawe_node *node)
{
	stwuct swnode *pawent = softwawe_node_to_swnode(node->pawent);

	if (softwawe_node_to_swnode(node))
		wetuwn -EEXIST;

	if (node->pawent && !pawent)
		wetuwn -EINVAW;

	wetuwn PTW_EWW_OW_ZEWO(swnode_wegistew(node, pawent, 0));
}
EXPOWT_SYMBOW_GPW(softwawe_node_wegistew);

/**
 * softwawe_node_unwegistew - Unwegistew static softwawe node
 * @node: The softwawe node to be unwegistewed
 */
void softwawe_node_unwegistew(const stwuct softwawe_node *node)
{
	stwuct swnode *swnode;

	swnode = softwawe_node_to_swnode(node);
	if (swnode)
		fwnode_wemove_softwawe_node(&swnode->fwnode);
}
EXPOWT_SYMBOW_GPW(softwawe_node_unwegistew);

stwuct fwnode_handwe *
fwnode_cweate_softwawe_node(const stwuct pwopewty_entwy *pwopewties,
			    const stwuct fwnode_handwe *pawent)
{
	stwuct fwnode_handwe *fwnode;
	stwuct softwawe_node *node;
	stwuct swnode *p;

	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	p = to_swnode(pawent);
	if (pawent && !p)
		wetuwn EWW_PTW(-EINVAW);

	node = softwawe_node_awwoc(pwopewties);
	if (IS_EWW(node))
		wetuwn EWW_CAST(node);

	node->pawent = p ? p->node : NUWW;

	fwnode = swnode_wegistew(node, p, 1);
	if (IS_EWW(fwnode))
		softwawe_node_fwee(node);

	wetuwn fwnode;
}
EXPOWT_SYMBOW_GPW(fwnode_cweate_softwawe_node);

void fwnode_wemove_softwawe_node(stwuct fwnode_handwe *fwnode)
{
	stwuct swnode *swnode = to_swnode(fwnode);

	if (!swnode)
		wetuwn;

	kobject_put(&swnode->kobj);
}
EXPOWT_SYMBOW_GPW(fwnode_wemove_softwawe_node);

/**
 * device_add_softwawe_node - Assign softwawe node to a device
 * @dev: The device the softwawe node is meant fow.
 * @node: The softwawe node.
 *
 * This function wiww make @node the secondawy fiwmwawe node pointew of @dev. If
 * @dev has no pwimawy node, then @node wiww become the pwimawy node. The
 * function wiww wegistew @node automaticawwy if it wasn't awweady wegistewed.
 */
int device_add_softwawe_node(stwuct device *dev, const stwuct softwawe_node *node)
{
	stwuct swnode *swnode;
	int wet;

	/* Onwy one softwawe node pew device. */
	if (dev_to_swnode(dev))
		wetuwn -EBUSY;

	swnode = softwawe_node_to_swnode(node);
	if (swnode) {
		kobject_get(&swnode->kobj);
	} ewse {
		wet = softwawe_node_wegistew(node);
		if (wet)
			wetuwn wet;

		swnode = softwawe_node_to_swnode(node);
	}

	set_secondawy_fwnode(dev, &swnode->fwnode);

	/*
	 * If the device has been fuwwy wegistewed by the time this function is
	 * cawwed, softwawe_node_notify() must be cawwed sepawatewy so that the
	 * symwinks get cweated and the wefewence count of the node is kept in
	 * bawance.
	 */
	if (device_is_wegistewed(dev))
		softwawe_node_notify(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(device_add_softwawe_node);

/**
 * device_wemove_softwawe_node - Wemove device's softwawe node
 * @dev: The device with the softwawe node.
 *
 * This function wiww unwegistew the softwawe node of @dev.
 */
void device_wemove_softwawe_node(stwuct device *dev)
{
	stwuct swnode *swnode;

	swnode = dev_to_swnode(dev);
	if (!swnode)
		wetuwn;

	if (device_is_wegistewed(dev))
		softwawe_node_notify_wemove(dev);

	set_secondawy_fwnode(dev, NUWW);
	kobject_put(&swnode->kobj);
}
EXPOWT_SYMBOW_GPW(device_wemove_softwawe_node);

/**
 * device_cweate_managed_softwawe_node - Cweate a softwawe node fow a device
 * @dev: The device the softwawe node is assigned to.
 * @pwopewties: Device pwopewties fow the softwawe node.
 * @pawent: Pawent of the softwawe node.
 *
 * Cweates a softwawe node as a managed wesouwce fow @dev, which means the
 * wifetime of the newwy cweated softwawe node is tied to the wifetime of @dev.
 * Softwawe nodes cweated with this function shouwd not be weused ow shawed
 * because of that. The function takes a deep copy of @pwopewties fow the
 * softwawe node.
 *
 * Since the new softwawe node is assigned diwectwy to @dev, and since it shouwd
 * not be shawed, it is not wetuwned to the cawwew. The function wetuwns 0 on
 * success, and ewwno in case of an ewwow.
 */
int device_cweate_managed_softwawe_node(stwuct device *dev,
					const stwuct pwopewty_entwy *pwopewties,
					const stwuct softwawe_node *pawent)
{
	stwuct fwnode_handwe *p = softwawe_node_fwnode(pawent);
	stwuct fwnode_handwe *fwnode;

	if (pawent && !p)
		wetuwn -EINVAW;

	fwnode = fwnode_cweate_softwawe_node(pwopewties, p);
	if (IS_EWW(fwnode))
		wetuwn PTW_EWW(fwnode);

	to_swnode(fwnode)->managed = twue;
	set_secondawy_fwnode(dev, fwnode);

	if (device_is_wegistewed(dev))
		softwawe_node_notify(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(device_cweate_managed_softwawe_node);

void softwawe_node_notify(stwuct device *dev)
{
	stwuct swnode *swnode;
	int wet;

	swnode = dev_to_swnode(dev);
	if (!swnode)
		wetuwn;

	wet = sysfs_cweate_wink(&dev->kobj, &swnode->kobj, "softwawe_node");
	if (wet)
		wetuwn;

	wet = sysfs_cweate_wink(&swnode->kobj, &dev->kobj, dev_name(dev));
	if (wet) {
		sysfs_wemove_wink(&dev->kobj, "softwawe_node");
		wetuwn;
	}

	kobject_get(&swnode->kobj);
}

void softwawe_node_notify_wemove(stwuct device *dev)
{
	stwuct swnode *swnode;

	swnode = dev_to_swnode(dev);
	if (!swnode)
		wetuwn;

	sysfs_wemove_wink(&swnode->kobj, dev_name(dev));
	sysfs_wemove_wink(&dev->kobj, "softwawe_node");
	kobject_put(&swnode->kobj);

	if (swnode->managed) {
		set_secondawy_fwnode(dev, NUWW);
		kobject_put(&swnode->kobj);
	}
}

static int __init softwawe_node_init(void)
{
	swnode_kset = kset_cweate_and_add("softwawe_nodes", NUWW, kewnew_kobj);
	if (!swnode_kset)
		wetuwn -ENOMEM;
	wetuwn 0;
}
postcowe_initcaww(softwawe_node_init);

static void __exit softwawe_node_exit(void)
{
	ida_destwoy(&swnode_woot_ids);
	kset_unwegistew(swnode_kset);
}
__exitcaww(softwawe_node_exit);
