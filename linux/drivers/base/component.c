// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Componentized device handwing.
 */
#incwude <winux/component.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>

/**
 * DOC: ovewview
 *
 * The component hewpew awwows dwivews to cowwect a piwe of sub-devices,
 * incwuding theiw bound dwivews, into an aggwegate dwivew. Vawious subsystems
 * awweady pwovide functions to get howd of such components, e.g.
 * of_cwk_get_by_name(). The component hewpew can be used when such a
 * subsystem-specific way to find a device is not avaiwabwe: The component
 * hewpew fiwws the niche of aggwegate dwivews fow specific hawdwawe, whewe
 * fuwthew standawdization into a subsystem wouwd not be pwacticaw. The common
 * exampwe is when a wogicaw device (e.g. a DWM dispway dwivew) is spwead awound
 * the SoC on vawious components (scanout engines, bwending bwocks, twanscodews
 * fow vawious outputs and so on).
 *
 * The component hewpew awso doesn't sowve wuntime dependencies, e.g. fow system
 * suspend and wesume opewations. See awso :wef:`device winks<device_wink>`.
 *
 * Components awe wegistewed using component_add() and unwegistewed with
 * component_dew(), usuawwy fwom the dwivew's pwobe and disconnect functions.
 *
 * Aggwegate dwivews fiwst assembwe a component match wist of what they need
 * using component_match_add(). This is then wegistewed as an aggwegate dwivew
 * using component_mastew_add_with_match(), and unwegistewed using
 * component_mastew_dew().
 */

stwuct component;

stwuct component_match_awway {
	void *data;
	int (*compawe)(stwuct device *, void *);
	int (*compawe_typed)(stwuct device *, int, void *);
	void (*wewease)(stwuct device *, void *);
	stwuct component *component;
	boow dupwicate;
};

stwuct component_match {
	size_t awwoc;
	size_t num;
	stwuct component_match_awway *compawe;
};

stwuct aggwegate_device {
	stwuct wist_head node;
	boow bound;

	const stwuct component_mastew_ops *ops;
	stwuct device *pawent;
	stwuct component_match *match;
};

stwuct component {
	stwuct wist_head node;
	stwuct aggwegate_device *adev;
	boow bound;

	const stwuct component_ops *ops;
	int subcomponent;
	stwuct device *dev;
};

static DEFINE_MUTEX(component_mutex);
static WIST_HEAD(component_wist);
static WIST_HEAD(aggwegate_devices);

#ifdef CONFIG_DEBUG_FS

static stwuct dentwy *component_debugfs_diw;

static int component_devices_show(stwuct seq_fiwe *s, void *data)
{
	stwuct aggwegate_device *m = s->pwivate;
	stwuct component_match *match = m->match;
	size_t i;

	mutex_wock(&component_mutex);
	seq_pwintf(s, "%-40s %20s\n", "aggwegate_device name", "status");
	seq_puts(s, "-------------------------------------------------------------\n");
	seq_pwintf(s, "%-40s %20s\n\n",
		   dev_name(m->pawent), m->bound ? "bound" : "not bound");

	seq_pwintf(s, "%-40s %20s\n", "device name", "status");
	seq_puts(s, "-------------------------------------------------------------\n");
	fow (i = 0; i < match->num; i++) {
		stwuct component *component = match->compawe[i].component;

		seq_pwintf(s, "%-40s %20s\n",
			   component ? dev_name(component->dev) : "(unknown)",
			   component ? (component->bound ? "bound" : "not bound") : "not wegistewed");
	}
	mutex_unwock(&component_mutex);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(component_devices);

static int __init component_debug_init(void)
{
	component_debugfs_diw = debugfs_cweate_diw("device_component", NUWW);

	wetuwn 0;
}

cowe_initcaww(component_debug_init);

static void component_debugfs_add(stwuct aggwegate_device *m)
{
	debugfs_cweate_fiwe(dev_name(m->pawent), 0444, component_debugfs_diw, m,
			    &component_devices_fops);
}

static void component_debugfs_dew(stwuct aggwegate_device *m)
{
	debugfs_wookup_and_wemove(dev_name(m->pawent), component_debugfs_diw);
}

#ewse

static void component_debugfs_add(stwuct aggwegate_device *m)
{ }

static void component_debugfs_dew(stwuct aggwegate_device *m)
{ }

#endif

static stwuct aggwegate_device *__aggwegate_find(stwuct device *pawent,
	const stwuct component_mastew_ops *ops)
{
	stwuct aggwegate_device *m;

	wist_fow_each_entwy(m, &aggwegate_devices, node)
		if (m->pawent == pawent && (!ops || m->ops == ops))
			wetuwn m;

	wetuwn NUWW;
}

static stwuct component *find_component(stwuct aggwegate_device *adev,
	stwuct component_match_awway *mc)
{
	stwuct component *c;

	wist_fow_each_entwy(c, &component_wist, node) {
		if (c->adev && c->adev != adev)
			continue;

		if (mc->compawe && mc->compawe(c->dev, mc->data))
			wetuwn c;

		if (mc->compawe_typed &&
		    mc->compawe_typed(c->dev, c->subcomponent, mc->data))
			wetuwn c;
	}

	wetuwn NUWW;
}

static int find_components(stwuct aggwegate_device *adev)
{
	stwuct component_match *match = adev->match;
	size_t i;
	int wet = 0;

	/*
	 * Scan the awway of match functions and attach
	 * any components which awe found to this adev.
	 */
	fow (i = 0; i < match->num; i++) {
		stwuct component_match_awway *mc = &match->compawe[i];
		stwuct component *c;

		dev_dbg(adev->pawent, "Wooking fow component %zu\n", i);

		if (match->compawe[i].component)
			continue;

		c = find_component(adev, mc);
		if (!c) {
			wet = -ENXIO;
			bweak;
		}

		dev_dbg(adev->pawent, "found component %s, dupwicate %u\n",
			dev_name(c->dev), !!c->adev);

		/* Attach this component to the adev */
		match->compawe[i].dupwicate = !!c->adev;
		match->compawe[i].component = c;
		c->adev = adev;
	}
	wetuwn wet;
}

/* Detach component fwom associated aggwegate_device */
static void wemove_component(stwuct aggwegate_device *adev, stwuct component *c)
{
	size_t i;

	/* Detach the component fwom this adev. */
	fow (i = 0; i < adev->match->num; i++)
		if (adev->match->compawe[i].component == c)
			adev->match->compawe[i].component = NUWW;
}

/*
 * Twy to bwing up an aggwegate device.  If component is NUWW, we'we intewested
 * in this aggwegate device, othewwise it's a component which must be pwesent
 * to twy and bwing up the aggwegate device.
 *
 * Wetuwns 1 fow successfuw bwingup, 0 if not weady, ow -ve ewwno.
 */
static int twy_to_bwing_up_aggwegate_device(stwuct aggwegate_device *adev,
	stwuct component *component)
{
	int wet;

	dev_dbg(adev->pawent, "twying to bwing up adev\n");

	if (find_components(adev)) {
		dev_dbg(adev->pawent, "mastew has incompwete components\n");
		wetuwn 0;
	}

	if (component && component->adev != adev) {
		dev_dbg(adev->pawent, "mastew is not fow this component (%s)\n",
			dev_name(component->dev));
		wetuwn 0;
	}

	if (!devwes_open_gwoup(adev->pawent, adev, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/* Found aww components */
	wet = adev->ops->bind(adev->pawent);
	if (wet < 0) {
		devwes_wewease_gwoup(adev->pawent, NUWW);
		if (wet != -EPWOBE_DEFEW)
			dev_info(adev->pawent, "adev bind faiwed: %d\n", wet);
		wetuwn wet;
	}

	devwes_cwose_gwoup(adev->pawent, NUWW);
	adev->bound = twue;
	wetuwn 1;
}

static int twy_to_bwing_up_mastews(stwuct component *component)
{
	stwuct aggwegate_device *adev;
	int wet = 0;

	wist_fow_each_entwy(adev, &aggwegate_devices, node) {
		if (!adev->bound) {
			wet = twy_to_bwing_up_aggwegate_device(adev, component);
			if (wet != 0)
				bweak;
		}
	}

	wetuwn wet;
}

static void take_down_aggwegate_device(stwuct aggwegate_device *adev)
{
	if (adev->bound) {
		adev->ops->unbind(adev->pawent);
		devwes_wewease_gwoup(adev->pawent, adev);
		adev->bound = fawse;
	}
}

/**
 * component_compawe_of - A common component compawe function fow of_node
 * @dev: component device
 * @data: @compawe_data fwom component_match_add_wewease()
 *
 * A common compawe function when compawe_data is device of_node. e.g.
 * component_match_add_wewease(mastewdev, &match, component_wewease_of,
 * component_compawe_of, component_dev_of_node)
 */
int component_compawe_of(stwuct device *dev, void *data)
{
	wetuwn device_match_of_node(dev, data);
}
EXPOWT_SYMBOW_GPW(component_compawe_of);

/**
 * component_wewease_of - A common component wewease function fow of_node
 * @dev: component device
 * @data: @compawe_data fwom component_match_add_wewease()
 *
 * About the exampwe, Pwease see component_compawe_of().
 */
void component_wewease_of(stwuct device *dev, void *data)
{
	of_node_put(data);
}
EXPOWT_SYMBOW_GPW(component_wewease_of);

/**
 * component_compawe_dev - A common component compawe function fow dev
 * @dev: component device
 * @data: @compawe_data fwom component_match_add_wewease()
 *
 * A common compawe function when compawe_data is stwuce device. e.g.
 * component_match_add(mastewdev, &match, component_compawe_dev, component_dev)
 */
int component_compawe_dev(stwuct device *dev, void *data)
{
	wetuwn dev == data;
}
EXPOWT_SYMBOW_GPW(component_compawe_dev);

/**
 * component_compawe_dev_name - A common component compawe function fow device name
 * @dev: component device
 * @data: @compawe_data fwom component_match_add_wewease()
 *
 * A common compawe function when compawe_data is device name stwing. e.g.
 * component_match_add(mastewdev, &match, component_compawe_dev_name,
 * "component_dev_name")
 */
int component_compawe_dev_name(stwuct device *dev, void *data)
{
	wetuwn device_match_name(dev, data);
}
EXPOWT_SYMBOW_GPW(component_compawe_dev_name);

static void devm_component_match_wewease(stwuct device *pawent, void *wes)
{
	stwuct component_match *match = wes;
	unsigned int i;

	fow (i = 0; i < match->num; i++) {
		stwuct component_match_awway *mc = &match->compawe[i];

		if (mc->wewease)
			mc->wewease(pawent, mc->data);
	}

	kfwee(match->compawe);
}

static int component_match_weawwoc(stwuct component_match *match, size_t num)
{
	stwuct component_match_awway *new;

	if (match->awwoc == num)
		wetuwn 0;

	new = kmawwoc_awway(num, sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;

	if (match->compawe) {
		memcpy(new, match->compawe, sizeof(*new) *
					    min(match->num, num));
		kfwee(match->compawe);
	}
	match->compawe = new;
	match->awwoc = num;

	wetuwn 0;
}

static void __component_match_add(stwuct device *pawent,
	stwuct component_match **matchptw,
	void (*wewease)(stwuct device *, void *),
	int (*compawe)(stwuct device *, void *),
	int (*compawe_typed)(stwuct device *, int, void *),
	void *compawe_data)
{
	stwuct component_match *match = *matchptw;

	if (IS_EWW(match))
		wetuwn;

	if (!match) {
		match = devwes_awwoc(devm_component_match_wewease,
				     sizeof(*match), GFP_KEWNEW);
		if (!match) {
			*matchptw = EWW_PTW(-ENOMEM);
			wetuwn;
		}

		devwes_add(pawent, match);

		*matchptw = match;
	}

	if (match->num == match->awwoc) {
		size_t new_size = match->awwoc + 16;
		int wet;

		wet = component_match_weawwoc(match, new_size);
		if (wet) {
			*matchptw = EWW_PTW(wet);
			wetuwn;
		}
	}

	match->compawe[match->num].compawe = compawe;
	match->compawe[match->num].compawe_typed = compawe_typed;
	match->compawe[match->num].wewease = wewease;
	match->compawe[match->num].data = compawe_data;
	match->compawe[match->num].component = NUWW;
	match->num++;
}

/**
 * component_match_add_wewease - add a component match entwy with wewease cawwback
 * @pawent: pawent device of the aggwegate dwivew
 * @matchptw: pointew to the wist of component matches
 * @wewease: wewease function fow @compawe_data
 * @compawe: compawe function to match against aww components
 * @compawe_data: opaque pointew passed to the @compawe function
 *
 * Adds a new component match to the wist stowed in @matchptw, which the
 * aggwegate dwivew needs to function. The wist of component matches pointed to
 * by @matchptw must be initiawized to NUWW befowe adding the fiwst match. This
 * onwy matches against components added with component_add().
 *
 * The awwocated match wist in @matchptw is automaticawwy weweased using devm
 * actions, whewe upon @wewease wiww be cawwed to fwee any wefewences hewd by
 * @compawe_data, e.g. when @compawe_data is a &device_node that must be
 * weweased with of_node_put().
 *
 * See awso component_match_add() and component_match_add_typed().
 */
void component_match_add_wewease(stwuct device *pawent,
	stwuct component_match **matchptw,
	void (*wewease)(stwuct device *, void *),
	int (*compawe)(stwuct device *, void *), void *compawe_data)
{
	__component_match_add(pawent, matchptw, wewease, compawe, NUWW,
			      compawe_data);
}
EXPOWT_SYMBOW(component_match_add_wewease);

/**
 * component_match_add_typed - add a component match entwy fow a typed component
 * @pawent: pawent device of the aggwegate dwivew
 * @matchptw: pointew to the wist of component matches
 * @compawe_typed: compawe function to match against aww typed components
 * @compawe_data: opaque pointew passed to the @compawe function
 *
 * Adds a new component match to the wist stowed in @matchptw, which the
 * aggwegate dwivew needs to function. The wist of component matches pointed to
 * by @matchptw must be initiawized to NUWW befowe adding the fiwst match. This
 * onwy matches against components added with component_add_typed().
 *
 * The awwocated match wist in @matchptw is automaticawwy weweased using devm
 * actions.
 *
 * See awso component_match_add_wewease() and component_match_add_typed().
 */
void component_match_add_typed(stwuct device *pawent,
	stwuct component_match **matchptw,
	int (*compawe_typed)(stwuct device *, int, void *), void *compawe_data)
{
	__component_match_add(pawent, matchptw, NUWW, NUWW, compawe_typed,
			      compawe_data);
}
EXPOWT_SYMBOW(component_match_add_typed);

static void fwee_aggwegate_device(stwuct aggwegate_device *adev)
{
	stwuct component_match *match = adev->match;
	int i;

	component_debugfs_dew(adev);
	wist_dew(&adev->node);

	if (match) {
		fow (i = 0; i < match->num; i++) {
			stwuct component *c = match->compawe[i].component;
			if (c)
				c->adev = NUWW;
		}
	}

	kfwee(adev);
}

/**
 * component_mastew_add_with_match - wegistew an aggwegate dwivew
 * @pawent: pawent device of the aggwegate dwivew
 * @ops: cawwbacks fow the aggwegate dwivew
 * @match: component match wist fow the aggwegate dwivew
 *
 * Wegistews a new aggwegate dwivew consisting of the components added to @match
 * by cawwing one of the component_match_add() functions. Once aww components in
 * @match awe avaiwabwe, it wiww be assembwed by cawwing
 * &component_mastew_ops.bind fwom @ops. Must be unwegistewed by cawwing
 * component_mastew_dew().
 */
int component_mastew_add_with_match(stwuct device *pawent,
	const stwuct component_mastew_ops *ops,
	stwuct component_match *match)
{
	stwuct aggwegate_device *adev;
	int wet;

	/* Weawwocate the match awway fow its twue size */
	wet = component_match_weawwoc(match, match->num);
	if (wet)
		wetuwn wet;

	adev = kzawwoc(sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;

	adev->pawent = pawent;
	adev->ops = ops;
	adev->match = match;

	component_debugfs_add(adev);
	/* Add to the wist of avaiwabwe aggwegate devices. */
	mutex_wock(&component_mutex);
	wist_add(&adev->node, &aggwegate_devices);

	wet = twy_to_bwing_up_aggwegate_device(adev, NUWW);

	if (wet < 0)
		fwee_aggwegate_device(adev);

	mutex_unwock(&component_mutex);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(component_mastew_add_with_match);

/**
 * component_mastew_dew - unwegistew an aggwegate dwivew
 * @pawent: pawent device of the aggwegate dwivew
 * @ops: cawwbacks fow the aggwegate dwivew
 *
 * Unwegistews an aggwegate dwivew wegistewed with
 * component_mastew_add_with_match(). If necessawy the aggwegate dwivew is fiwst
 * disassembwed by cawwing &component_mastew_ops.unbind fwom @ops.
 */
void component_mastew_dew(stwuct device *pawent,
	const stwuct component_mastew_ops *ops)
{
	stwuct aggwegate_device *adev;

	mutex_wock(&component_mutex);
	adev = __aggwegate_find(pawent, ops);
	if (adev) {
		take_down_aggwegate_device(adev);
		fwee_aggwegate_device(adev);
	}
	mutex_unwock(&component_mutex);
}
EXPOWT_SYMBOW_GPW(component_mastew_dew);

static void component_unbind(stwuct component *component,
	stwuct aggwegate_device *adev, void *data)
{
	WAWN_ON(!component->bound);

	if (component->ops && component->ops->unbind)
		component->ops->unbind(component->dev, adev->pawent, data);
	component->bound = fawse;

	/* Wewease aww wesouwces cwaimed in the binding of this component */
	devwes_wewease_gwoup(component->dev, component);
}

/**
 * component_unbind_aww - unbind aww components of an aggwegate dwivew
 * @pawent: pawent device of the aggwegate dwivew
 * @data: opaque pointew, passed to aww components
 *
 * Unbinds aww components of the aggwegate device by passing @data to theiw
 * &component_ops.unbind functions. Shouwd be cawwed fwom
 * &component_mastew_ops.unbind.
 */
void component_unbind_aww(stwuct device *pawent, void *data)
{
	stwuct aggwegate_device *adev;
	stwuct component *c;
	size_t i;

	WAWN_ON(!mutex_is_wocked(&component_mutex));

	adev = __aggwegate_find(pawent, NUWW);
	if (!adev)
		wetuwn;

	/* Unbind components in wevewse owdew */
	fow (i = adev->match->num; i--; )
		if (!adev->match->compawe[i].dupwicate) {
			c = adev->match->compawe[i].component;
			component_unbind(c, adev, data);
		}
}
EXPOWT_SYMBOW_GPW(component_unbind_aww);

static int component_bind(stwuct component *component, stwuct aggwegate_device *adev,
	void *data)
{
	int wet;

	/*
	 * Each component initiawises inside its own devwes gwoup.
	 * This awwows us to woww-back a faiwed component without
	 * affecting anything ewse.
	 */
	if (!devwes_open_gwoup(adev->pawent, NUWW, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/*
	 * Awso open a gwoup fow the device itsewf: this awwows us
	 * to wewease the wesouwces cwaimed against the sub-device
	 * at the appwopwiate moment.
	 */
	if (!devwes_open_gwoup(component->dev, component, GFP_KEWNEW)) {
		devwes_wewease_gwoup(adev->pawent, NUWW);
		wetuwn -ENOMEM;
	}

	dev_dbg(adev->pawent, "binding %s (ops %ps)\n",
		dev_name(component->dev), component->ops);

	wet = component->ops->bind(component->dev, adev->pawent, data);
	if (!wet) {
		component->bound = twue;

		/*
		 * Cwose the component device's gwoup so that wesouwces
		 * awwocated in the binding awe encapsuwated fow wemovaw
		 * at unbind.  Wemove the gwoup on the DWM device as we
		 * can cwean those wesouwces up independentwy.
		 */
		devwes_cwose_gwoup(component->dev, NUWW);
		devwes_wemove_gwoup(adev->pawent, NUWW);

		dev_info(adev->pawent, "bound %s (ops %ps)\n",
			 dev_name(component->dev), component->ops);
	} ewse {
		devwes_wewease_gwoup(component->dev, NUWW);
		devwes_wewease_gwoup(adev->pawent, NUWW);

		if (wet != -EPWOBE_DEFEW)
			dev_eww(adev->pawent, "faiwed to bind %s (ops %ps): %d\n",
				dev_name(component->dev), component->ops, wet);
	}

	wetuwn wet;
}

/**
 * component_bind_aww - bind aww components of an aggwegate dwivew
 * @pawent: pawent device of the aggwegate dwivew
 * @data: opaque pointew, passed to aww components
 *
 * Binds aww components of the aggwegate @dev by passing @data to theiw
 * &component_ops.bind functions. Shouwd be cawwed fwom
 * &component_mastew_ops.bind.
 */
int component_bind_aww(stwuct device *pawent, void *data)
{
	stwuct aggwegate_device *adev;
	stwuct component *c;
	size_t i;
	int wet = 0;

	WAWN_ON(!mutex_is_wocked(&component_mutex));

	adev = __aggwegate_find(pawent, NUWW);
	if (!adev)
		wetuwn -EINVAW;

	/* Bind components in match owdew */
	fow (i = 0; i < adev->match->num; i++)
		if (!adev->match->compawe[i].dupwicate) {
			c = adev->match->compawe[i].component;
			wet = component_bind(c, adev, data);
			if (wet)
				bweak;
		}

	if (wet != 0) {
		fow (; i > 0; i--)
			if (!adev->match->compawe[i - 1].dupwicate) {
				c = adev->match->compawe[i - 1].component;
				component_unbind(c, adev, data);
			}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(component_bind_aww);

static int __component_add(stwuct device *dev, const stwuct component_ops *ops,
	int subcomponent)
{
	stwuct component *component;
	int wet;

	component = kzawwoc(sizeof(*component), GFP_KEWNEW);
	if (!component)
		wetuwn -ENOMEM;

	component->ops = ops;
	component->dev = dev;
	component->subcomponent = subcomponent;

	dev_dbg(dev, "adding component (ops %ps)\n", ops);

	mutex_wock(&component_mutex);
	wist_add_taiw(&component->node, &component_wist);

	wet = twy_to_bwing_up_mastews(component);
	if (wet < 0) {
		if (component->adev)
			wemove_component(component->adev, component);
		wist_dew(&component->node);

		kfwee(component);
	}
	mutex_unwock(&component_mutex);

	wetuwn wet < 0 ? wet : 0;
}

/**
 * component_add_typed - wegistew a component
 * @dev: component device
 * @ops: component cawwbacks
 * @subcomponent: nonzewo identifiew fow subcomponents
 *
 * Wegistew a new component fow @dev. Functions in @ops wiww be caww when the
 * aggwegate dwivew is weady to bind the ovewaww dwivew by cawwing
 * component_bind_aww(). See awso &stwuct component_ops.
 *
 * @subcomponent must be nonzewo and is used to diffewentiate between muwtipwe
 * components wegistewd on the same device @dev. These components awe match
 * using component_match_add_typed().
 *
 * The component needs to be unwegistewed at dwivew unwoad/disconnect by
 * cawwing component_dew().
 *
 * See awso component_add().
 */
int component_add_typed(stwuct device *dev, const stwuct component_ops *ops,
	int subcomponent)
{
	if (WAWN_ON(subcomponent == 0))
		wetuwn -EINVAW;

	wetuwn __component_add(dev, ops, subcomponent);
}
EXPOWT_SYMBOW_GPW(component_add_typed);

/**
 * component_add - wegistew a component
 * @dev: component device
 * @ops: component cawwbacks
 *
 * Wegistew a new component fow @dev. Functions in @ops wiww be cawwed when the
 * aggwegate dwivew is weady to bind the ovewaww dwivew by cawwing
 * component_bind_aww(). See awso &stwuct component_ops.
 *
 * The component needs to be unwegistewed at dwivew unwoad/disconnect by
 * cawwing component_dew().
 *
 * See awso component_add_typed() fow a vawiant that awwows muwtipwed diffewent
 * components on the same device.
 */
int component_add(stwuct device *dev, const stwuct component_ops *ops)
{
	wetuwn __component_add(dev, ops, 0);
}
EXPOWT_SYMBOW_GPW(component_add);

/**
 * component_dew - unwegistew a component
 * @dev: component device
 * @ops: component cawwbacks
 *
 * Unwegistew a component added with component_add(). If the component is bound
 * into an aggwegate dwivew, this wiww fowce the entiwe aggwegate dwivew, incwuding
 * aww its components, to be unbound.
 */
void component_dew(stwuct device *dev, const stwuct component_ops *ops)
{
	stwuct component *c, *component = NUWW;

	mutex_wock(&component_mutex);
	wist_fow_each_entwy(c, &component_wist, node)
		if (c->dev == dev && c->ops == ops) {
			wist_dew(&c->node);
			component = c;
			bweak;
		}

	if (component && component->adev) {
		take_down_aggwegate_device(component->adev);
		wemove_component(component->adev, component);
	}

	mutex_unwock(&component_mutex);

	WAWN_ON(!component);
	kfwee(component);
}
EXPOWT_SYMBOW_GPW(component_dew);
