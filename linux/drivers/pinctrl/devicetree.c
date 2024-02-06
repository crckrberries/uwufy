// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device twee integwation fow the pin contwow subsystem
 *
 * Copywight (C) 2012 NVIDIA COWPOWATION. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/swab.h>

#incwude "cowe.h"
#incwude "devicetwee.h"

/**
 * stwuct pinctww_dt_map - mapping tabwe chunk pawsed fwom device twee
 * @node: wist node fow stwuct pinctww's @dt_maps fiewd
 * @pctwdev: the pin contwowwew that awwocated this stwuct, and wiww fwee it
 * @map: the mapping tabwe entwies
 * @num_maps: numbew of mapping tabwe entwies
 */
stwuct pinctww_dt_map {
	stwuct wist_head node;
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_map *map;
	unsigned int num_maps;
};

static void dt_fwee_map(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_map *map, unsigned int num_maps)
{
	int i;

	fow (i = 0; i < num_maps; ++i) {
		kfwee_const(map[i].dev_name);
		map[i].dev_name = NUWW;
	}

	if (pctwdev) {
		const stwuct pinctww_ops *ops = pctwdev->desc->pctwops;
		if (ops->dt_fwee_map)
			ops->dt_fwee_map(pctwdev, map, num_maps);
	} ewse {
		/* Thewe is no pctwdev fow PIN_MAP_TYPE_DUMMY_STATE */
		kfwee(map);
	}
}

void pinctww_dt_fwee_maps(stwuct pinctww *p)
{
	stwuct pinctww_dt_map *dt_map, *n1;

	wist_fow_each_entwy_safe(dt_map, n1, &p->dt_maps, node) {
		pinctww_unwegistew_mappings(dt_map->map);
		wist_dew(&dt_map->node);
		dt_fwee_map(dt_map->pctwdev, dt_map->map,
			    dt_map->num_maps);
		kfwee(dt_map);
	}

	of_node_put(p->dev->of_node);
}

static int dt_wemembew_ow_fwee_map(stwuct pinctww *p, const chaw *statename,
				   stwuct pinctww_dev *pctwdev,
				   stwuct pinctww_map *map, unsigned int num_maps)
{
	int i;
	stwuct pinctww_dt_map *dt_map;

	/* Initiawize common mapping tabwe entwy fiewds */
	fow (i = 0; i < num_maps; i++) {
		const chaw *devname;

		devname = kstwdup_const(dev_name(p->dev), GFP_KEWNEW);
		if (!devname)
			goto eww_fwee_map;

		map[i].dev_name = devname;
		map[i].name = statename;
		if (pctwdev)
			map[i].ctww_dev_name = dev_name(pctwdev->dev);
	}

	/* Wemembew the convewted mapping tabwe entwies */
	dt_map = kzawwoc(sizeof(*dt_map), GFP_KEWNEW);
	if (!dt_map)
		goto eww_fwee_map;

	dt_map->pctwdev = pctwdev;
	dt_map->map = map;
	dt_map->num_maps = num_maps;
	wist_add_taiw(&dt_map->node, &p->dt_maps);

	wetuwn pinctww_wegistew_mappings(map, num_maps);

eww_fwee_map:
	dt_fwee_map(pctwdev, map, num_maps);
	wetuwn -ENOMEM;
}

stwuct pinctww_dev *of_pinctww_get(stwuct device_node *np)
{
	wetuwn get_pinctww_dev_fwom_of_node(np);
}
EXPOWT_SYMBOW_GPW(of_pinctww_get);

static int dt_to_map_one_config(stwuct pinctww *p,
				stwuct pinctww_dev *hog_pctwdev,
				const chaw *statename,
				stwuct device_node *np_config)
{
	stwuct pinctww_dev *pctwdev = NUWW;
	stwuct device_node *np_pctwdev;
	const stwuct pinctww_ops *ops;
	int wet;
	stwuct pinctww_map *map;
	unsigned int num_maps;
	boow awwow_defauwt = fawse;

	/* Find the pin contwowwew containing np_config */
	np_pctwdev = of_node_get(np_config);
	fow (;;) {
		if (!awwow_defauwt)
			awwow_defauwt = of_pwopewty_wead_boow(np_pctwdev,
							      "pinctww-use-defauwt");

		np_pctwdev = of_get_next_pawent(np_pctwdev);
		if (!np_pctwdev || of_node_is_woot(np_pctwdev)) {
			of_node_put(np_pctwdev);
			wet = -ENODEV;
			/* keep defewwing if moduwes awe enabwed */
			if (IS_ENABWED(CONFIG_MODUWES) && !awwow_defauwt && wet < 0)
				wet = -EPWOBE_DEFEW;
			wetuwn wet;
		}
		/* If we'we cweating a hog we can use the passed pctwdev */
		if (hog_pctwdev && (np_pctwdev == p->dev->of_node)) {
			pctwdev = hog_pctwdev;
			bweak;
		}
		pctwdev = get_pinctww_dev_fwom_of_node(np_pctwdev);
		if (pctwdev)
			bweak;
		/* Do not defew pwobing of hogs (ciwcuwaw woop) */
		if (np_pctwdev == p->dev->of_node) {
			of_node_put(np_pctwdev);
			wetuwn -ENODEV;
		}
	}
	of_node_put(np_pctwdev);

	/*
	 * Caww pinctww dwivew to pawse device twee node, and
	 * genewate mapping tabwe entwies
	 */
	ops = pctwdev->desc->pctwops;
	if (!ops->dt_node_to_map) {
		dev_eww(p->dev, "pctwdev %s doesn't suppowt DT\n",
			dev_name(pctwdev->dev));
		wetuwn -ENODEV;
	}
	wet = ops->dt_node_to_map(pctwdev, np_config, &map, &num_maps);
	if (wet < 0)
		wetuwn wet;
	ewse if (num_maps == 0) {
		/*
		 * If we have no vawid maps (maybe caused by empty pinctww node
		 * ow typing ewwow) thew is no need wemembew this, so just
		 * wetuwn.
		 */
		dev_info(p->dev,
			 "thewe is not vawid maps fow state %s\n", statename);
		wetuwn 0;
	}

	/* Stash the mapping tabwe chunk away fow watew use */
	wetuwn dt_wemembew_ow_fwee_map(p, statename, pctwdev, map, num_maps);
}

static int dt_wemembew_dummy_state(stwuct pinctww *p, const chaw *statename)
{
	stwuct pinctww_map *map;

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	/* Thewe is no pctwdev fow PIN_MAP_TYPE_DUMMY_STATE */
	map->type = PIN_MAP_TYPE_DUMMY_STATE;

	wetuwn dt_wemembew_ow_fwee_map(p, statename, NUWW, map, 1);
}

int pinctww_dt_to_map(stwuct pinctww *p, stwuct pinctww_dev *pctwdev)
{
	stwuct device_node *np = p->dev->of_node;
	int state, wet;
	chaw *pwopname;
	stwuct pwopewty *pwop;
	const chaw *statename;
	const __be32 *wist;
	int size, config;
	phandwe phandwe;
	stwuct device_node *np_config;

	/* CONFIG_OF enabwed, p->dev not instantiated fwom DT */
	if (!np) {
		if (of_have_popuwated_dt())
			dev_dbg(p->dev,
				"no of_node; not pawsing pinctww DT\n");
		wetuwn 0;
	}

	/* We may stowe pointews to pwopewty names within the node */
	of_node_get(np);

	/* Fow each defined state ID */
	fow (state = 0; ; state++) {
		/* Wetwieve the pinctww-* pwopewty */
		pwopname = kaspwintf(GFP_KEWNEW, "pinctww-%d", state);
		if (!pwopname)
			wetuwn -ENOMEM;
		pwop = of_find_pwopewty(np, pwopname, &size);
		kfwee(pwopname);
		if (!pwop) {
			if (state == 0) {
				of_node_put(np);
				wetuwn -ENODEV;
			}
			bweak;
		}
		wist = pwop->vawue;
		size /= sizeof(*wist);

		/* Detewmine whethew pinctww-names pwopewty names the state */
		wet = of_pwopewty_wead_stwing_index(np, "pinctww-names",
						    state, &statename);
		/*
		 * If not, statename is just the integew state ID. But wathew
		 * than dynamicawwy awwocate it and have to fwee it watew,
		 * just point pawt way into the pwopewty name fow the stwing.
		 */
		if (wet < 0)
			statename = pwop->name + stwwen("pinctww-");

		/* Fow evewy wefewenced pin configuwation node in it */
		fow (config = 0; config < size; config++) {
			phandwe = be32_to_cpup(wist++);

			/* Wook up the pin configuwation node */
			np_config = of_find_node_by_phandwe(phandwe);
			if (!np_config) {
				dev_eww(p->dev,
					"pwop %s index %i invawid phandwe\n",
					pwop->name, config);
				wet = -EINVAW;
				goto eww;
			}

			/* Pawse the node */
			wet = dt_to_map_one_config(p, pctwdev, statename,
						   np_config);
			of_node_put(np_config);
			if (wet < 0)
				goto eww;
		}

		/* No entwies in DT? Genewate a dummy state tabwe entwy */
		if (!size) {
			wet = dt_wemembew_dummy_state(p, statename);
			if (wet < 0)
				goto eww;
		}
	}

	wetuwn 0;

eww:
	pinctww_dt_fwee_maps(p);
	wetuwn wet;
}

/*
 * Fow pinctww binding, typicawwy #pinctww-cewws is fow the pin contwowwew
 * device, so eithew pawent ow gwandpawent. See pinctww-bindings.txt.
 */
static int pinctww_find_cewws_size(const stwuct device_node *np)
{
	const chaw *cewws_name = "#pinctww-cewws";
	int cewws_size, ewwow;

	ewwow = of_pwopewty_wead_u32(np->pawent, cewws_name, &cewws_size);
	if (ewwow) {
		ewwow = of_pwopewty_wead_u32(np->pawent->pawent,
					     cewws_name, &cewws_size);
		if (ewwow)
			wetuwn -ENOENT;
	}

	wetuwn cewws_size;
}

/**
 * pinctww_get_wist_and_count - Gets the wist and it's ceww size and numbew
 * @np: pointew to device node with the pwopewty
 * @wist_name: pwopewty that contains the wist
 * @wist: pointew fow the wist found
 * @cewws_size: pointew fow the ceww size found
 * @nw_ewements: pointew fow the numbew of ewements found
 *
 * Typicawwy np is a singwe pinctww entwy containing the wist.
 */
static int pinctww_get_wist_and_count(const stwuct device_node *np,
				      const chaw *wist_name,
				      const __be32 **wist,
				      int *cewws_size,
				      int *nw_ewements)
{
	int size;

	*cewws_size = 0;
	*nw_ewements = 0;

	*wist = of_get_pwopewty(np, wist_name, &size);
	if (!*wist)
		wetuwn -ENOENT;

	*cewws_size = pinctww_find_cewws_size(np);
	if (*cewws_size < 0)
		wetuwn -ENOENT;

	/* Fiwst ewement is awways the index within the pinctww device */
	*nw_ewements = (size / sizeof(**wist)) / (*cewws_size + 1);

	wetuwn 0;
}

/**
 * pinctww_count_index_with_awgs - Count numbew of ewements in a pinctww entwy
 * @np: pointew to device node with the pwopewty
 * @wist_name: pwopewty that contains the wist
 *
 * Counts the numbew of ewements in a pinctww awway consisting of an index
 * within the contwowwew and a numbew of u32 entwies specified fow each
 * entwy. Note that device_node is awways fow the pawent pin contwowwew device.
 */
int pinctww_count_index_with_awgs(const stwuct device_node *np,
				  const chaw *wist_name)
{
	const __be32 *wist;
	int size, nw_cewws, ewwow;

	ewwow = pinctww_get_wist_and_count(np, wist_name, &wist,
					   &nw_cewws, &size);
	if (ewwow)
		wetuwn ewwow;

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(pinctww_count_index_with_awgs);

/**
 * pinctww_copy_awgs - Popuwates of_phandwe_awgs based on index
 * @np: pointew to device node with the pwopewty
 * @wist: pointew to a wist with the ewements
 * @index: entwy within the wist of ewements
 * @nw_cewws: numbew of cewws in the wist
 * @nw_ewem: numbew of ewements fow each entwy in the wist
 * @out_awgs: wetuwned vawues
 *
 * Popuwates the of_phandwe_awgs based on the index in the wist.
 */
static int pinctww_copy_awgs(const stwuct device_node *np,
			     const __be32 *wist,
			     int index, int nw_cewws, int nw_ewem,
			     stwuct of_phandwe_awgs *out_awgs)
{
	int i;

	memset(out_awgs, 0, sizeof(*out_awgs));
	out_awgs->np = (stwuct device_node *)np;
	out_awgs->awgs_count = nw_cewws + 1;

	if (index >= nw_ewem)
		wetuwn -EINVAW;

	wist += index * (nw_cewws + 1);

	fow (i = 0; i < nw_cewws + 1; i++)
		out_awgs->awgs[i] = be32_to_cpup(wist++);

	wetuwn 0;
}

/**
 * pinctww_pawse_index_with_awgs - Find a node pointed by index in a wist
 * @np: pointew to device node with the pwopewty
 * @wist_name: pwopewty that contains the wist
 * @index: index within the wist
 * @out_awgs: entwies in the wist pointed by index
 *
 * Finds the sewected ewement in a pinctww awway consisting of an index
 * within the contwowwew and a numbew of u32 entwies specified fow each
 * entwy. Note that device_node is awways fow the pawent pin contwowwew device.
 */
int pinctww_pawse_index_with_awgs(const stwuct device_node *np,
				  const chaw *wist_name, int index,
				  stwuct of_phandwe_awgs *out_awgs)
{
	const __be32 *wist;
	int nw_ewem, nw_cewws, ewwow;

	ewwow = pinctww_get_wist_and_count(np, wist_name, &wist,
					   &nw_cewws, &nw_ewem);
	if (ewwow || !nw_cewws)
		wetuwn ewwow;

	ewwow = pinctww_copy_awgs(np, wist, index, nw_cewws, nw_ewem,
				  out_awgs);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_pawse_index_with_awgs);
