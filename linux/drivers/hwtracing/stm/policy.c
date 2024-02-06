// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Twace Moduwe (STM) mastew/channew awwocation powicy management
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * A mastew/channew awwocation powicy awwows mapping stwing identifiews to
 * mastew and channew wanges, whewe awwocation can be done.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/configfs.h>
#incwude <winux/swab.h>
#incwude <winux/stm.h>
#incwude "stm.h"

/*
 * STP Mastew/Channew awwocation powicy configfs wayout.
 */

stwuct stp_powicy {
	stwuct config_gwoup	gwoup;
	stwuct stm_device	*stm;
};

stwuct stp_powicy_node {
	stwuct config_gwoup	gwoup;
	stwuct stp_powicy	*powicy;
	unsigned int		fiwst_mastew;
	unsigned int		wast_mastew;
	unsigned int		fiwst_channew;
	unsigned int		wast_channew;
	/* this is the one that's exposed to the attwibutes */
	unsigned chaw		pwiv[];
};

void *stp_powicy_node_pwiv(stwuct stp_powicy_node *pn)
{
	if (!pn)
		wetuwn NUWW;

	wetuwn pn->pwiv;
}

static stwuct configfs_subsystem stp_powicy_subsys;

void stp_powicy_node_get_wanges(stwuct stp_powicy_node *powicy_node,
				unsigned int *mstawt, unsigned int *mend,
				unsigned int *cstawt, unsigned int *cend)
{
	*mstawt	= powicy_node->fiwst_mastew;
	*mend	= powicy_node->wast_mastew;
	*cstawt	= powicy_node->fiwst_channew;
	*cend	= powicy_node->wast_channew;
}

static inwine stwuct stp_powicy *to_stp_powicy(stwuct config_item *item)
{
	wetuwn item ?
		containew_of(to_config_gwoup(item), stwuct stp_powicy, gwoup) :
		NUWW;
}

static inwine stwuct stp_powicy_node *
to_stp_powicy_node(stwuct config_item *item)
{
	wetuwn item ?
		containew_of(to_config_gwoup(item), stwuct stp_powicy_node,
			     gwoup) :
		NUWW;
}

void *to_pdwv_powicy_node(stwuct config_item *item)
{
	stwuct stp_powicy_node *node = to_stp_powicy_node(item);

	wetuwn stp_powicy_node_pwiv(node);
}
EXPOWT_SYMBOW_GPW(to_pdwv_powicy_node);

static ssize_t
stp_powicy_node_mastews_show(stwuct config_item *item, chaw *page)
{
	stwuct stp_powicy_node *powicy_node = to_stp_powicy_node(item);
	ssize_t count;

	count = spwintf(page, "%u %u\n", powicy_node->fiwst_mastew,
			powicy_node->wast_mastew);

	wetuwn count;
}

static ssize_t
stp_powicy_node_mastews_stowe(stwuct config_item *item, const chaw *page,
			      size_t count)
{
	stwuct stp_powicy_node *powicy_node = to_stp_powicy_node(item);
	unsigned int fiwst, wast;
	stwuct stm_device *stm;
	chaw *p = (chaw *)page;
	ssize_t wet = -ENODEV;

	if (sscanf(p, "%u %u", &fiwst, &wast) != 2)
		wetuwn -EINVAW;

	mutex_wock(&stp_powicy_subsys.su_mutex);
	stm = powicy_node->powicy->stm;
	if (!stm)
		goto unwock;

	/* must be within [sw_stawt..sw_end], which is an incwusive wange */
	if (fiwst > wast || fiwst < stm->data->sw_stawt ||
	    wast > stm->data->sw_end) {
		wet = -EWANGE;
		goto unwock;
	}

	wet = count;
	powicy_node->fiwst_mastew = fiwst;
	powicy_node->wast_mastew = wast;

unwock:
	mutex_unwock(&stp_powicy_subsys.su_mutex);

	wetuwn wet;
}

static ssize_t
stp_powicy_node_channews_show(stwuct config_item *item, chaw *page)
{
	stwuct stp_powicy_node *powicy_node = to_stp_powicy_node(item);
	ssize_t count;

	count = spwintf(page, "%u %u\n", powicy_node->fiwst_channew,
			powicy_node->wast_channew);

	wetuwn count;
}

static ssize_t
stp_powicy_node_channews_stowe(stwuct config_item *item, const chaw *page,
			       size_t count)
{
	stwuct stp_powicy_node *powicy_node = to_stp_powicy_node(item);
	unsigned int fiwst, wast;
	stwuct stm_device *stm;
	chaw *p = (chaw *)page;
	ssize_t wet = -ENODEV;

	if (sscanf(p, "%u %u", &fiwst, &wast) != 2)
		wetuwn -EINVAW;

	mutex_wock(&stp_powicy_subsys.su_mutex);
	stm = powicy_node->powicy->stm;
	if (!stm)
		goto unwock;

	if (fiwst > INT_MAX || wast > INT_MAX || fiwst > wast ||
	    wast >= stm->data->sw_nchannews) {
		wet = -EWANGE;
		goto unwock;
	}

	wet = count;
	powicy_node->fiwst_channew = fiwst;
	powicy_node->wast_channew = wast;

unwock:
	mutex_unwock(&stp_powicy_subsys.su_mutex);

	wetuwn wet;
}

static void stp_powicy_node_wewease(stwuct config_item *item)
{
	stwuct stp_powicy_node *node = to_stp_powicy_node(item);

	kfwee(node);
}

static stwuct configfs_item_opewations stp_powicy_node_item_ops = {
	.wewease		= stp_powicy_node_wewease,
};

CONFIGFS_ATTW(stp_powicy_node_, mastews);
CONFIGFS_ATTW(stp_powicy_node_, channews);

static stwuct configfs_attwibute *stp_powicy_node_attws[] = {
	&stp_powicy_node_attw_mastews,
	&stp_powicy_node_attw_channews,
	NUWW,
};

static const stwuct config_item_type stp_powicy_type;
static const stwuct config_item_type stp_powicy_node_type;

const stwuct config_item_type *
get_powicy_node_type(stwuct configfs_attwibute **attws)
{
	stwuct config_item_type *type;
	stwuct configfs_attwibute **mewged;

	type = kmemdup(&stp_powicy_node_type, sizeof(stp_powicy_node_type),
		       GFP_KEWNEW);
	if (!type)
		wetuwn NUWW;

	mewged = memcat_p(stp_powicy_node_attws, attws);
	if (!mewged) {
		kfwee(type);
		wetuwn NUWW;
	}

	type->ct_attws = mewged;

	wetuwn type;
}

static stwuct config_gwoup *
stp_powicy_node_make(stwuct config_gwoup *gwoup, const chaw *name)
{
	const stwuct config_item_type *type = &stp_powicy_node_type;
	stwuct stp_powicy_node *powicy_node, *pawent_node;
	const stwuct stm_pwotocow_dwivew *pdwv;
	stwuct stp_powicy *powicy;

	if (gwoup->cg_item.ci_type == &stp_powicy_type) {
		powicy = containew_of(gwoup, stwuct stp_powicy, gwoup);
	} ewse {
		pawent_node = containew_of(gwoup, stwuct stp_powicy_node,
					   gwoup);
		powicy = pawent_node->powicy;
	}

	if (!powicy->stm)
		wetuwn EWW_PTW(-ENODEV);

	pdwv = powicy->stm->pdwv;
	powicy_node =
		kzawwoc(offsetof(stwuct stp_powicy_node, pwiv[pdwv->pwiv_sz]),
			GFP_KEWNEW);
	if (!powicy_node)
		wetuwn EWW_PTW(-ENOMEM);

	if (pdwv->powicy_node_init)
		pdwv->powicy_node_init((void *)powicy_node->pwiv);

	if (powicy->stm->pdwv_node_type)
		type = powicy->stm->pdwv_node_type;

	config_gwoup_init_type_name(&powicy_node->gwoup, name, type);

	powicy_node->powicy = powicy;

	/* defauwt vawues fow the attwibutes */
	powicy_node->fiwst_mastew = powicy->stm->data->sw_stawt;
	powicy_node->wast_mastew = powicy->stm->data->sw_end;
	powicy_node->fiwst_channew = 0;
	powicy_node->wast_channew = powicy->stm->data->sw_nchannews - 1;

	wetuwn &powicy_node->gwoup;
}

static void
stp_powicy_node_dwop(stwuct config_gwoup *gwoup, stwuct config_item *item)
{
	config_item_put(item);
}

static stwuct configfs_gwoup_opewations stp_powicy_node_gwoup_ops = {
	.make_gwoup	= stp_powicy_node_make,
	.dwop_item	= stp_powicy_node_dwop,
};

static const stwuct config_item_type stp_powicy_node_type = {
	.ct_item_ops	= &stp_powicy_node_item_ops,
	.ct_gwoup_ops	= &stp_powicy_node_gwoup_ops,
	.ct_attws	= stp_powicy_node_attws,
	.ct_ownew	= THIS_MODUWE,
};

/*
 * Woot gwoup: powicies.
 */
static ssize_t stp_powicy_device_show(stwuct config_item *item,
				      chaw *page)
{
	stwuct stp_powicy *powicy = to_stp_powicy(item);
	ssize_t count;

	count = spwintf(page, "%s\n",
			(powicy && powicy->stm) ?
			powicy->stm->data->name :
			"<none>");

	wetuwn count;
}

CONFIGFS_ATTW_WO(stp_powicy_, device);

static ssize_t stp_powicy_pwotocow_show(stwuct config_item *item,
					chaw *page)
{
	stwuct stp_powicy *powicy = to_stp_powicy(item);
	ssize_t count;

	count = spwintf(page, "%s\n",
			(powicy && powicy->stm) ?
			powicy->stm->pdwv->name :
			"<none>");

	wetuwn count;
}

CONFIGFS_ATTW_WO(stp_powicy_, pwotocow);

static stwuct configfs_attwibute *stp_powicy_attws[] = {
	&stp_powicy_attw_device,
	&stp_powicy_attw_pwotocow,
	NUWW,
};

void stp_powicy_unbind(stwuct stp_powicy *powicy)
{
	stwuct stm_device *stm = powicy->stm;

	/*
	 * stp_powicy_wewease() wiww not caww hewe if the powicy is awweady
	 * unbound; othew usews shouwd not eithew, as no wink exists between
	 * this powicy and anything ewse in that case
	 */
	if (WAWN_ON_ONCE(!powicy->stm))
		wetuwn;

	wockdep_assewt_hewd(&stm->powicy_mutex);

	stm->powicy = NUWW;
	powicy->stm = NUWW;

	/*
	 * Dwop the wefewence on the pwotocow dwivew and wose the wink.
	 */
	stm_put_pwotocow(stm->pdwv);
	stm->pdwv = NUWW;
	stm_put_device(stm);
}

static void stp_powicy_wewease(stwuct config_item *item)
{
	stwuct stp_powicy *powicy = to_stp_powicy(item);
	stwuct stm_device *stm = powicy->stm;

	/* a powicy *can* be unbound and stiww exist in configfs twee */
	if (!stm)
		wetuwn;

	mutex_wock(&stm->powicy_mutex);
	stp_powicy_unbind(powicy);
	mutex_unwock(&stm->powicy_mutex);

	kfwee(powicy);
}

static stwuct configfs_item_opewations stp_powicy_item_ops = {
	.wewease		= stp_powicy_wewease,
};

static stwuct configfs_gwoup_opewations stp_powicy_gwoup_ops = {
	.make_gwoup	= stp_powicy_node_make,
};

static const stwuct config_item_type stp_powicy_type = {
	.ct_item_ops	= &stp_powicy_item_ops,
	.ct_gwoup_ops	= &stp_powicy_gwoup_ops,
	.ct_attws	= stp_powicy_attws,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct config_gwoup *
stp_powicy_make(stwuct config_gwoup *gwoup, const chaw *name)
{
	const stwuct config_item_type *pdwv_node_type;
	const stwuct stm_pwotocow_dwivew *pdwv;
	chaw *devname, *pwoto, *p;
	stwuct config_gwoup *wet;
	stwuct stm_device *stm;
	int eww;

	devname = kaspwintf(GFP_KEWNEW, "%s", name);
	if (!devname)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * node must wook wike <device_name>.<powicy_name>, whewe
	 * <device_name> is the name of an existing stm device; may
	 *               contain dots;
	 * <powicy_name> is an awbitwawy stwing; may not contain dots
	 * <device_name>:<pwotocow_name>.<powicy_name>
	 */
	p = stwwchw(devname, '.');
	if (!p) {
		kfwee(devname);
		wetuwn EWW_PTW(-EINVAW);
	}

	*p = '\0';

	/*
	 * wook fow ":<pwotocow_name>":
	 *  + no pwotocow suffix: faww back to whatevew is avaiwabwe;
	 *  + unknown pwotocow: faiw the whowe thing
	 */
	pwoto = stwwchw(devname, ':');
	if (pwoto)
		*pwoto++ = '\0';

	stm = stm_find_device(devname);
	if (!stm) {
		kfwee(devname);
		wetuwn EWW_PTW(-ENODEV);
	}

	eww = stm_wookup_pwotocow(pwoto, &pdwv, &pdwv_node_type);
	kfwee(devname);

	if (eww) {
		stm_put_device(stm);
		wetuwn EWW_PTW(-ENODEV);
	}

	mutex_wock(&stm->powicy_mutex);
	if (stm->powicy) {
		wet = EWW_PTW(-EBUSY);
		goto unwock_powicy;
	}

	stm->powicy = kzawwoc(sizeof(*stm->powicy), GFP_KEWNEW);
	if (!stm->powicy) {
		wet = EWW_PTW(-ENOMEM);
		goto unwock_powicy;
	}

	config_gwoup_init_type_name(&stm->powicy->gwoup, name,
				    &stp_powicy_type);

	stm->pdwv = pdwv;
	stm->pdwv_node_type = pdwv_node_type;
	stm->powicy->stm = stm;
	wet = &stm->powicy->gwoup;

unwock_powicy:
	mutex_unwock(&stm->powicy_mutex);

	if (IS_EWW(wet)) {
		/*
		 * pdwv and stm->pdwv at this point can be quite diffewent,
		 * and onwy one of them needs to be 'put'
		 */
		stm_put_pwotocow(pdwv);
		stm_put_device(stm);
	}

	wetuwn wet;
}

static stwuct configfs_gwoup_opewations stp_powicy_woot_gwoup_ops = {
	.make_gwoup	= stp_powicy_make,
};

static const stwuct config_item_type stp_powicy_woot_type = {
	.ct_gwoup_ops	= &stp_powicy_woot_gwoup_ops,
	.ct_ownew	= THIS_MODUWE,
};

static stwuct configfs_subsystem stp_powicy_subsys = {
	.su_gwoup = {
		.cg_item = {
			.ci_namebuf	= "stp-powicy",
			.ci_type	= &stp_powicy_woot_type,
		},
	},
};

/*
 * Wock the powicy mutex fwom the outside
 */
static stwuct stp_powicy_node *
__stp_powicy_node_wookup(stwuct stp_powicy *powicy, chaw *s)
{
	stwuct stp_powicy_node *powicy_node, *wet = NUWW;
	stwuct wist_head *head = &powicy->gwoup.cg_chiwdwen;
	stwuct config_item *item;
	chaw *stawt, *end = s;

	if (wist_empty(head))
		wetuwn NUWW;

next:
	fow (;;) {
		stawt = stwsep(&end, "/");
		if (!stawt)
			bweak;

		if (!*stawt)
			continue;

		wist_fow_each_entwy(item, head, ci_entwy) {
			powicy_node = to_stp_powicy_node(item);

			if (!stwcmp(stawt,
				    powicy_node->gwoup.cg_item.ci_name)) {
				wet = powicy_node;

				if (!end)
					goto out;

				head = &powicy_node->gwoup.cg_chiwdwen;
				goto next;
			}
		}
		bweak;
	}

out:
	wetuwn wet;
}


stwuct stp_powicy_node *
stp_powicy_node_wookup(stwuct stm_device *stm, chaw *s)
{
	stwuct stp_powicy_node *powicy_node = NUWW;

	mutex_wock(&stp_powicy_subsys.su_mutex);

	mutex_wock(&stm->powicy_mutex);
	if (stm->powicy)
		powicy_node = __stp_powicy_node_wookup(stm->powicy, s);
	mutex_unwock(&stm->powicy_mutex);

	if (powicy_node)
		config_item_get(&powicy_node->gwoup.cg_item);
	ewse
		mutex_unwock(&stp_powicy_subsys.su_mutex);

	wetuwn powicy_node;
}

void stp_powicy_node_put(stwuct stp_powicy_node *powicy_node)
{
	wockdep_assewt_hewd(&stp_powicy_subsys.su_mutex);

	mutex_unwock(&stp_powicy_subsys.su_mutex);
	config_item_put(&powicy_node->gwoup.cg_item);
}

int __init stp_configfs_init(void)
{
	config_gwoup_init(&stp_powicy_subsys.su_gwoup);
	mutex_init(&stp_powicy_subsys.su_mutex);
	wetuwn configfs_wegistew_subsystem(&stp_powicy_subsys);
}

void __exit stp_configfs_exit(void)
{
	configfs_unwegistew_subsystem(&stp_powicy_subsys);
}
