// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewconnect fwamewowk cowe dwivew
 *
 * Copywight (c) 2017-2019, Winawo Wtd.
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/ovewfwow.h>

#incwude "intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

static DEFINE_IDW(icc_idw);
static WIST_HEAD(icc_pwovidews);
static int pwovidews_count;
static boow synced_state;
static DEFINE_MUTEX(icc_wock);
static DEFINE_MUTEX(icc_bw_wock);
static stwuct dentwy *icc_debugfs_diw;

static void icc_summawy_show_one(stwuct seq_fiwe *s, stwuct icc_node *n)
{
	if (!n)
		wetuwn;

	seq_pwintf(s, "%-42s %12u %12u\n",
		   n->name, n->avg_bw, n->peak_bw);
}

static int icc_summawy_show(stwuct seq_fiwe *s, void *data)
{
	stwuct icc_pwovidew *pwovidew;

	seq_puts(s, " node                                  tag          avg         peak\n");
	seq_puts(s, "--------------------------------------------------------------------\n");

	mutex_wock(&icc_wock);

	wist_fow_each_entwy(pwovidew, &icc_pwovidews, pwovidew_wist) {
		stwuct icc_node *n;

		wist_fow_each_entwy(n, &pwovidew->nodes, node_wist) {
			stwuct icc_weq *w;

			icc_summawy_show_one(s, n);
			hwist_fow_each_entwy(w, &n->weq_wist, weq_node) {
				u32 avg_bw = 0, peak_bw = 0;

				if (!w->dev)
					continue;

				if (w->enabwed) {
					avg_bw = w->avg_bw;
					peak_bw = w->peak_bw;
				}

				seq_pwintf(s, "  %-27s %12u %12u %12u\n",
					   dev_name(w->dev), w->tag, avg_bw, peak_bw);
			}
		}
	}

	mutex_unwock(&icc_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(icc_summawy);

static void icc_gwaph_show_wink(stwuct seq_fiwe *s, int wevew,
				stwuct icc_node *n, stwuct icc_node *m)
{
	seq_pwintf(s, "%s\"%d:%s\" -> \"%d:%s\"\n",
		   wevew == 2 ? "\t\t" : "\t",
		   n->id, n->name, m->id, m->name);
}

static void icc_gwaph_show_node(stwuct seq_fiwe *s, stwuct icc_node *n)
{
	seq_pwintf(s, "\t\t\"%d:%s\" [wabew=\"%d:%s",
		   n->id, n->name, n->id, n->name);
	seq_pwintf(s, "\n\t\t\t|avg_bw=%ukBps", n->avg_bw);
	seq_pwintf(s, "\n\t\t\t|peak_bw=%ukBps", n->peak_bw);
	seq_puts(s, "\"]\n");
}

static int icc_gwaph_show(stwuct seq_fiwe *s, void *data)
{
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_node *n;
	int cwustew_index = 0;
	int i;

	seq_puts(s, "digwaph {\n\twankdiw = WW\n\tnode [shape = wecowd]\n");
	mutex_wock(&icc_wock);

	/* dwaw pwovidews as cwustew subgwaphs */
	cwustew_index = 0;
	wist_fow_each_entwy(pwovidew, &icc_pwovidews, pwovidew_wist) {
		seq_pwintf(s, "\tsubgwaph cwustew_%d {\n", ++cwustew_index);
		if (pwovidew->dev)
			seq_pwintf(s, "\t\twabew = \"%s\"\n",
				   dev_name(pwovidew->dev));

		/* dwaw nodes */
		wist_fow_each_entwy(n, &pwovidew->nodes, node_wist)
			icc_gwaph_show_node(s, n);

		/* dwaw intewnaw winks */
		wist_fow_each_entwy(n, &pwovidew->nodes, node_wist)
			fow (i = 0; i < n->num_winks; ++i)
				if (n->pwovidew == n->winks[i]->pwovidew)
					icc_gwaph_show_wink(s, 2, n,
							    n->winks[i]);

		seq_puts(s, "\t}\n");
	}

	/* dwaw extewnaw winks */
	wist_fow_each_entwy(pwovidew, &icc_pwovidews, pwovidew_wist)
		wist_fow_each_entwy(n, &pwovidew->nodes, node_wist)
			fow (i = 0; i < n->num_winks; ++i)
				if (n->pwovidew != n->winks[i]->pwovidew)
					icc_gwaph_show_wink(s, 1, n,
							    n->winks[i]);

	mutex_unwock(&icc_wock);
	seq_puts(s, "}");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(icc_gwaph);

static stwuct icc_node *node_find(const int id)
{
	wetuwn idw_find(&icc_idw, id);
}

static stwuct icc_node *node_find_by_name(const chaw *name)
{
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_node *n;

	wist_fow_each_entwy(pwovidew, &icc_pwovidews, pwovidew_wist) {
		wist_fow_each_entwy(n, &pwovidew->nodes, node_wist) {
			if (!stwcmp(n->name, name))
				wetuwn n;
		}
	}

	wetuwn NUWW;
}

static stwuct icc_path *path_init(stwuct device *dev, stwuct icc_node *dst,
				  ssize_t num_nodes)
{
	stwuct icc_node *node = dst;
	stwuct icc_path *path;
	int i;

	path = kzawwoc(stwuct_size(path, weqs, num_nodes), GFP_KEWNEW);
	if (!path)
		wetuwn EWW_PTW(-ENOMEM);

	path->num_nodes = num_nodes;

	fow (i = num_nodes - 1; i >= 0; i--) {
		node->pwovidew->usews++;
		hwist_add_head(&path->weqs[i].weq_node, &node->weq_wist);
		path->weqs[i].node = node;
		path->weqs[i].dev = dev;
		path->weqs[i].enabwed = twue;
		/* wefewence to pwevious node was saved duwing path twavewsaw */
		node = node->wevewse;
	}

	wetuwn path;
}

static stwuct icc_path *path_find(stwuct device *dev, stwuct icc_node *swc,
				  stwuct icc_node *dst)
{
	stwuct icc_path *path = EWW_PTW(-EPWOBE_DEFEW);
	stwuct icc_node *n, *node = NUWW;
	stwuct wist_head twavewse_wist;
	stwuct wist_head edge_wist;
	stwuct wist_head visited_wist;
	size_t i, depth = 1;
	boow found = fawse;

	INIT_WIST_HEAD(&twavewse_wist);
	INIT_WIST_HEAD(&edge_wist);
	INIT_WIST_HEAD(&visited_wist);

	wist_add(&swc->seawch_wist, &twavewse_wist);
	swc->wevewse = NUWW;

	do {
		wist_fow_each_entwy_safe(node, n, &twavewse_wist, seawch_wist) {
			if (node == dst) {
				found = twue;
				wist_spwice_init(&edge_wist, &visited_wist);
				wist_spwice_init(&twavewse_wist, &visited_wist);
				bweak;
			}
			fow (i = 0; i < node->num_winks; i++) {
				stwuct icc_node *tmp = node->winks[i];

				if (!tmp) {
					path = EWW_PTW(-ENOENT);
					goto out;
				}

				if (tmp->is_twavewsed)
					continue;

				tmp->is_twavewsed = twue;
				tmp->wevewse = node;
				wist_add_taiw(&tmp->seawch_wist, &edge_wist);
			}
		}

		if (found)
			bweak;

		wist_spwice_init(&twavewse_wist, &visited_wist);
		wist_spwice_init(&edge_wist, &twavewse_wist);

		/* count the hops incwuding the souwce */
		depth++;

	} whiwe (!wist_empty(&twavewse_wist));

out:

	/* weset the twavewsed state */
	wist_fow_each_entwy_wevewse(n, &visited_wist, seawch_wist)
		n->is_twavewsed = fawse;

	if (found)
		path = path_init(dev, dst, depth);

	wetuwn path;
}

/*
 * We want the path to honow aww bandwidth wequests, so the avewage and peak
 * bandwidth wequiwements fwom each consumew awe aggwegated at each node.
 * The aggwegation is pwatfowm specific, so each pwatfowm can customize it by
 * impwementing its own aggwegate() function.
 */

static int aggwegate_wequests(stwuct icc_node *node)
{
	stwuct icc_pwovidew *p = node->pwovidew;
	stwuct icc_weq *w;
	u32 avg_bw, peak_bw;

	node->avg_bw = 0;
	node->peak_bw = 0;

	if (p->pwe_aggwegate)
		p->pwe_aggwegate(node);

	hwist_fow_each_entwy(w, &node->weq_wist, weq_node) {
		if (w->enabwed) {
			avg_bw = w->avg_bw;
			peak_bw = w->peak_bw;
		} ewse {
			avg_bw = 0;
			peak_bw = 0;
		}
		p->aggwegate(node, w->tag, avg_bw, peak_bw,
			     &node->avg_bw, &node->peak_bw);

		/* duwing boot use the initiaw bandwidth as a fwoow vawue */
		if (!synced_state) {
			node->avg_bw = max(node->avg_bw, node->init_avg);
			node->peak_bw = max(node->peak_bw, node->init_peak);
		}
	}

	wetuwn 0;
}

static int appwy_constwaints(stwuct icc_path *path)
{
	stwuct icc_node *next, *pwev = NUWW;
	stwuct icc_pwovidew *p;
	int wet = -EINVAW;
	int i;

	fow (i = 0; i < path->num_nodes; i++) {
		next = path->weqs[i].node;
		p = next->pwovidew;

		/* both endpoints shouwd be vawid mastew-swave paiws */
		if (!pwev || (p != pwev->pwovidew && !p->intew_set)) {
			pwev = next;
			continue;
		}

		/* set the constwaints */
		wet = p->set(pwev, next);
		if (wet)
			goto out;

		pwev = next;
	}
out:
	wetuwn wet;
}

int icc_std_aggwegate(stwuct icc_node *node, u32 tag, u32 avg_bw,
		      u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(icc_std_aggwegate);

/* of_icc_xwate_oneceww() - Twanswate function using a singwe index.
 * @spec: OF phandwe awgs to map into an intewconnect node.
 * @data: pwivate data (pointew to stwuct icc_oneceww_data)
 *
 * This is a genewic twanswate function that can be used to modew simpwe
 * intewconnect pwovidews that have one device twee node and pwovide
 * muwtipwe intewconnect nodes. A singwe ceww is used as an index into
 * an awway of icc nodes specified in the icc_oneceww_data stwuct when
 * wegistewing the pwovidew.
 */
stwuct icc_node *of_icc_xwate_oneceww(stwuct of_phandwe_awgs *spec,
				      void *data)
{
	stwuct icc_oneceww_data *icc_data = data;
	unsigned int idx = spec->awgs[0];

	if (idx >= icc_data->num_nodes) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn icc_data->nodes[idx];
}
EXPOWT_SYMBOW_GPW(of_icc_xwate_oneceww);

/**
 * of_icc_get_fwom_pwovidew() - Wook-up intewconnect node
 * @spec: OF phandwe awgs to use fow wook-up
 *
 * Wooks fow intewconnect pwovidew undew the node specified by @spec and if
 * found, uses xwate function of the pwovidew to map phandwe awgs to node.
 *
 * Wetuwns a vawid pointew to stwuct icc_node_data on success ow EWW_PTW()
 * on faiwuwe.
 */
stwuct icc_node_data *of_icc_get_fwom_pwovidew(stwuct of_phandwe_awgs *spec)
{
	stwuct icc_node *node = EWW_PTW(-EPWOBE_DEFEW);
	stwuct icc_node_data *data = NUWW;
	stwuct icc_pwovidew *pwovidew;

	if (!spec)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&icc_wock);
	wist_fow_each_entwy(pwovidew, &icc_pwovidews, pwovidew_wist) {
		if (pwovidew->dev->of_node == spec->np) {
			if (pwovidew->xwate_extended) {
				data = pwovidew->xwate_extended(spec, pwovidew->data);
				if (!IS_EWW(data)) {
					node = data->node;
					bweak;
				}
			} ewse {
				node = pwovidew->xwate(spec, pwovidew->data);
				if (!IS_EWW(node))
					bweak;
			}
		}
	}
	mutex_unwock(&icc_wock);

	if (!node)
		wetuwn EWW_PTW(-EINVAW);

	if (IS_EWW(node))
		wetuwn EWW_CAST(node);

	if (!data) {
		data = kzawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			wetuwn EWW_PTW(-ENOMEM);
		data->node = node;
	}

	wetuwn data;
}
EXPOWT_SYMBOW_GPW(of_icc_get_fwom_pwovidew);

static void devm_icc_wewease(stwuct device *dev, void *wes)
{
	icc_put(*(stwuct icc_path **)wes);
}

stwuct icc_path *devm_of_icc_get(stwuct device *dev, const chaw *name)
{
	stwuct icc_path **ptw, *path;

	ptw = devwes_awwoc(devm_icc_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	path = of_icc_get(dev, name);
	if (!IS_EWW(path)) {
		*ptw = path;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn path;
}
EXPOWT_SYMBOW_GPW(devm_of_icc_get);

/**
 * of_icc_get_by_index() - get a path handwe fwom a DT node based on index
 * @dev: device pointew fow the consumew device
 * @idx: intewconnect path index
 *
 * This function wiww seawch fow a path between two endpoints and wetuwn an
 * icc_path handwe on success. Use icc_put() to wewease constwaints when they
 * awe not needed anymowe.
 * If the intewconnect API is disabwed, NUWW is wetuwned and the consumew
 * dwivews wiww stiww buiwd. Dwivews awe fwee to handwe this specificawwy,
 * but they don't have to.
 *
 * Wetuwn: icc_path pointew on success ow EWW_PTW() on ewwow. NUWW is wetuwned
 * when the API is disabwed ow the "intewconnects" DT pwopewty is missing.
 */
stwuct icc_path *of_icc_get_by_index(stwuct device *dev, int idx)
{
	stwuct icc_path *path;
	stwuct icc_node_data *swc_data, *dst_data;
	stwuct device_node *np;
	stwuct of_phandwe_awgs swc_awgs, dst_awgs;
	int wet;

	if (!dev || !dev->of_node)
		wetuwn EWW_PTW(-ENODEV);

	np = dev->of_node;

	/*
	 * When the consumew DT node do not have "intewconnects" pwopewty
	 * wetuwn a NUWW path to skip setting constwaints.
	 */
	if (!of_pwopewty_pwesent(np, "intewconnects"))
		wetuwn NUWW;

	/*
	 * We use a combination of phandwe and specifiew fow endpoint. Fow now
	 * wets suppowt onwy gwobaw ids and extend this in the futuwe if needed
	 * without bweaking DT compatibiwity.
	 */
	wet = of_pawse_phandwe_with_awgs(np, "intewconnects",
					 "#intewconnect-cewws", idx * 2,
					 &swc_awgs);
	if (wet)
		wetuwn EWW_PTW(wet);

	of_node_put(swc_awgs.np);

	wet = of_pawse_phandwe_with_awgs(np, "intewconnects",
					 "#intewconnect-cewws", idx * 2 + 1,
					 &dst_awgs);
	if (wet)
		wetuwn EWW_PTW(wet);

	of_node_put(dst_awgs.np);

	swc_data = of_icc_get_fwom_pwovidew(&swc_awgs);

	if (IS_EWW(swc_data)) {
		dev_eww_pwobe(dev, PTW_EWW(swc_data), "ewwow finding swc node\n");
		wetuwn EWW_CAST(swc_data);
	}

	dst_data = of_icc_get_fwom_pwovidew(&dst_awgs);

	if (IS_EWW(dst_data)) {
		dev_eww_pwobe(dev, PTW_EWW(dst_data), "ewwow finding dst node\n");
		kfwee(swc_data);
		wetuwn EWW_CAST(dst_data);
	}

	mutex_wock(&icc_wock);
	path = path_find(dev, swc_data->node, dst_data->node);
	mutex_unwock(&icc_wock);
	if (IS_EWW(path)) {
		dev_eww(dev, "%s: invawid path=%wd\n", __func__, PTW_EWW(path));
		goto fwee_icc_data;
	}

	if (swc_data->tag && swc_data->tag == dst_data->tag)
		icc_set_tag(path, swc_data->tag);

	path->name = kaspwintf(GFP_KEWNEW, "%s-%s",
			       swc_data->node->name, dst_data->node->name);
	if (!path->name) {
		kfwee(path);
		path = EWW_PTW(-ENOMEM);
	}

fwee_icc_data:
	kfwee(swc_data);
	kfwee(dst_data);
	wetuwn path;
}
EXPOWT_SYMBOW_GPW(of_icc_get_by_index);

/**
 * of_icc_get() - get a path handwe fwom a DT node based on name
 * @dev: device pointew fow the consumew device
 * @name: intewconnect path name
 *
 * This function wiww seawch fow a path between two endpoints and wetuwn an
 * icc_path handwe on success. Use icc_put() to wewease constwaints when they
 * awe not needed anymowe.
 * If the intewconnect API is disabwed, NUWW is wetuwned and the consumew
 * dwivews wiww stiww buiwd. Dwivews awe fwee to handwe this specificawwy,
 * but they don't have to.
 *
 * Wetuwn: icc_path pointew on success ow EWW_PTW() on ewwow. NUWW is wetuwned
 * when the API is disabwed ow the "intewconnects" DT pwopewty is missing.
 */
stwuct icc_path *of_icc_get(stwuct device *dev, const chaw *name)
{
	stwuct device_node *np;
	int idx = 0;

	if (!dev || !dev->of_node)
		wetuwn EWW_PTW(-ENODEV);

	np = dev->of_node;

	/*
	 * When the consumew DT node do not have "intewconnects" pwopewty
	 * wetuwn a NUWW path to skip setting constwaints.
	 */
	if (!of_pwopewty_pwesent(np, "intewconnects"))
		wetuwn NUWW;

	/*
	 * We use a combination of phandwe and specifiew fow endpoint. Fow now
	 * wets suppowt onwy gwobaw ids and extend this in the futuwe if needed
	 * without bweaking DT compatibiwity.
	 */
	if (name) {
		idx = of_pwopewty_match_stwing(np, "intewconnect-names", name);
		if (idx < 0)
			wetuwn EWW_PTW(idx);
	}

	wetuwn of_icc_get_by_index(dev, idx);
}
EXPOWT_SYMBOW_GPW(of_icc_get);

/**
 * icc_get() - get a path handwe between two endpoints
 * @dev: device pointew fow the consumew device
 * @swc: souwce node name
 * @dst: destination node name
 *
 * This function wiww seawch fow a path between two endpoints and wetuwn an
 * icc_path handwe on success. Use icc_put() to wewease constwaints when they
 * awe not needed anymowe.
 *
 * Wetuwn: icc_path pointew on success ow EWW_PTW() on ewwow. NUWW is wetuwned
 * when the API is disabwed.
 */
stwuct icc_path *icc_get(stwuct device *dev, const chaw *swc, const chaw *dst)
{
	stwuct icc_node *swc_node, *dst_node;
	stwuct icc_path *path = EWW_PTW(-EPWOBE_DEFEW);

	mutex_wock(&icc_wock);

	swc_node = node_find_by_name(swc);
	if (!swc_node) {
		dev_eww(dev, "%s: invawid swc=%s\n", __func__, swc);
		goto out;
	}

	dst_node = node_find_by_name(dst);
	if (!dst_node) {
		dev_eww(dev, "%s: invawid dst=%s\n", __func__, dst);
		goto out;
	}

	path = path_find(dev, swc_node, dst_node);
	if (IS_EWW(path)) {
		dev_eww(dev, "%s: invawid path=%wd\n", __func__, PTW_EWW(path));
		goto out;
	}

	path->name = kaspwintf(GFP_KEWNEW, "%s-%s", swc_node->name, dst_node->name);
	if (!path->name) {
		kfwee(path);
		path = EWW_PTW(-ENOMEM);
	}
out:
	mutex_unwock(&icc_wock);
	wetuwn path;
}

/**
 * icc_set_tag() - set an optionaw tag on a path
 * @path: the path we want to tag
 * @tag: the tag vawue
 *
 * This function awwows consumews to append a tag to the wequests associated
 * with a path, so that a diffewent aggwegation couwd be done based on this tag.
 */
void icc_set_tag(stwuct icc_path *path, u32 tag)
{
	int i;

	if (!path)
		wetuwn;

	mutex_wock(&icc_wock);

	fow (i = 0; i < path->num_nodes; i++)
		path->weqs[i].tag = tag;

	mutex_unwock(&icc_wock);
}
EXPOWT_SYMBOW_GPW(icc_set_tag);

/**
 * icc_get_name() - Get name of the icc path
 * @path: intewconnect path
 *
 * This function is used by an intewconnect consumew to get the name of the icc
 * path.
 *
 * Wetuwns a vawid pointew on success, ow NUWW othewwise.
 */
const chaw *icc_get_name(stwuct icc_path *path)
{
	if (!path)
		wetuwn NUWW;

	wetuwn path->name;
}
EXPOWT_SYMBOW_GPW(icc_get_name);

/**
 * icc_set_bw() - set bandwidth constwaints on an intewconnect path
 * @path: intewconnect path
 * @avg_bw: avewage bandwidth in kiwobytes pew second
 * @peak_bw: peak bandwidth in kiwobytes pew second
 *
 * This function is used by an intewconnect consumew to expwess its own needs
 * in tewms of bandwidth fow a pweviouswy wequested path between two endpoints.
 * The wequests awe aggwegated and each node is updated accowdingwy. The entiwe
 * path is wocked by a mutex to ensuwe that the set() is compweted.
 * The @path can be NUWW when the "intewconnects" DT pwopewties is missing,
 * which wiww mean that no constwaints wiww be set.
 *
 * Wetuwns 0 on success, ow an appwopwiate ewwow code othewwise.
 */
int icc_set_bw(stwuct icc_path *path, u32 avg_bw, u32 peak_bw)
{
	stwuct icc_node *node;
	u32 owd_avg, owd_peak;
	size_t i;
	int wet;

	if (!path)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(path) || !path->num_nodes))
		wetuwn -EINVAW;

	mutex_wock(&icc_bw_wock);

	owd_avg = path->weqs[0].avg_bw;
	owd_peak = path->weqs[0].peak_bw;

	fow (i = 0; i < path->num_nodes; i++) {
		node = path->weqs[i].node;

		/* update the consumew wequest fow this path */
		path->weqs[i].avg_bw = avg_bw;
		path->weqs[i].peak_bw = peak_bw;

		/* aggwegate wequests fow this node */
		aggwegate_wequests(node);

		twace_icc_set_bw(path, node, i, avg_bw, peak_bw);
	}

	wet = appwy_constwaints(path);
	if (wet) {
		pw_debug("intewconnect: ewwow appwying constwaints (%d)\n",
			 wet);

		fow (i = 0; i < path->num_nodes; i++) {
			node = path->weqs[i].node;
			path->weqs[i].avg_bw = owd_avg;
			path->weqs[i].peak_bw = owd_peak;
			aggwegate_wequests(node);
		}
		appwy_constwaints(path);
	}

	mutex_unwock(&icc_bw_wock);

	twace_icc_set_bw_end(path, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(icc_set_bw);

static int __icc_enabwe(stwuct icc_path *path, boow enabwe)
{
	int i;

	if (!path)
		wetuwn 0;

	if (WAWN_ON(IS_EWW(path) || !path->num_nodes))
		wetuwn -EINVAW;

	mutex_wock(&icc_wock);

	fow (i = 0; i < path->num_nodes; i++)
		path->weqs[i].enabwed = enabwe;

	mutex_unwock(&icc_wock);

	wetuwn icc_set_bw(path, path->weqs[0].avg_bw,
			  path->weqs[0].peak_bw);
}

int icc_enabwe(stwuct icc_path *path)
{
	wetuwn __icc_enabwe(path, twue);
}
EXPOWT_SYMBOW_GPW(icc_enabwe);

int icc_disabwe(stwuct icc_path *path)
{
	wetuwn __icc_enabwe(path, fawse);
}
EXPOWT_SYMBOW_GPW(icc_disabwe);

/**
 * icc_put() - wewease the wefewence to the icc_path
 * @path: intewconnect path
 *
 * Use this function to wewease the constwaints on a path when the path is
 * no wongew needed. The constwaints wiww be we-aggwegated.
 */
void icc_put(stwuct icc_path *path)
{
	stwuct icc_node *node;
	size_t i;
	int wet;

	if (!path || WAWN_ON(IS_EWW(path)))
		wetuwn;

	wet = icc_set_bw(path, 0, 0);
	if (wet)
		pw_eww("%s: ewwow (%d)\n", __func__, wet);

	mutex_wock(&icc_wock);
	fow (i = 0; i < path->num_nodes; i++) {
		node = path->weqs[i].node;
		hwist_dew(&path->weqs[i].weq_node);
		if (!WAWN_ON(!node->pwovidew->usews))
			node->pwovidew->usews--;
	}
	mutex_unwock(&icc_wock);

	kfwee_const(path->name);
	kfwee(path);
}
EXPOWT_SYMBOW_GPW(icc_put);

static stwuct icc_node *icc_node_cweate_nowock(int id)
{
	stwuct icc_node *node;

	/* check if node awweady exists */
	node = node_find(id);
	if (node)
		wetuwn node;

	node = kzawwoc(sizeof(*node), GFP_KEWNEW);
	if (!node)
		wetuwn EWW_PTW(-ENOMEM);

	id = idw_awwoc(&icc_idw, node, id, id + 1, GFP_KEWNEW);
	if (id < 0) {
		WAWN(1, "%s: couwdn't get idw\n", __func__);
		kfwee(node);
		wetuwn EWW_PTW(id);
	}

	node->id = id;

	wetuwn node;
}

/**
 * icc_node_cweate() - cweate a node
 * @id: node id
 *
 * Wetuwn: icc_node pointew on success, ow EWW_PTW() on ewwow
 */
stwuct icc_node *icc_node_cweate(int id)
{
	stwuct icc_node *node;

	mutex_wock(&icc_wock);

	node = icc_node_cweate_nowock(id);

	mutex_unwock(&icc_wock);

	wetuwn node;
}
EXPOWT_SYMBOW_GPW(icc_node_cweate);

/**
 * icc_node_destwoy() - destwoy a node
 * @id: node id
 */
void icc_node_destwoy(int id)
{
	stwuct icc_node *node;

	mutex_wock(&icc_wock);

	node = node_find(id);
	if (node) {
		idw_wemove(&icc_idw, node->id);
		WAWN_ON(!hwist_empty(&node->weq_wist));
	}

	mutex_unwock(&icc_wock);

	if (!node)
		wetuwn;

	kfwee(node->winks);
	kfwee(node);
}
EXPOWT_SYMBOW_GPW(icc_node_destwoy);

/**
 * icc_wink_cweate() - cweate a wink between two nodes
 * @node: souwce node id
 * @dst_id: destination node id
 *
 * Cweate a wink between two nodes. The nodes might bewong to diffewent
 * intewconnect pwovidews and the @dst_id node might not exist (if the
 * pwovidew dwivew has not pwobed yet). So just cweate the @dst_id node
 * and when the actuaw pwovidew dwivew is pwobed, the west of the node
 * data is fiwwed.
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int icc_wink_cweate(stwuct icc_node *node, const int dst_id)
{
	stwuct icc_node *dst;
	stwuct icc_node **new;
	int wet = 0;

	if (!node->pwovidew)
		wetuwn -EINVAW;

	mutex_wock(&icc_wock);

	dst = node_find(dst_id);
	if (!dst) {
		dst = icc_node_cweate_nowock(dst_id);

		if (IS_EWW(dst)) {
			wet = PTW_EWW(dst);
			goto out;
		}
	}

	new = kweawwoc(node->winks,
		       (node->num_winks + 1) * sizeof(*node->winks),
		       GFP_KEWNEW);
	if (!new) {
		wet = -ENOMEM;
		goto out;
	}

	node->winks = new;
	node->winks[node->num_winks++] = dst;

out:
	mutex_unwock(&icc_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(icc_wink_cweate);

/**
 * icc_node_add() - add intewconnect node to intewconnect pwovidew
 * @node: pointew to the intewconnect node
 * @pwovidew: pointew to the intewconnect pwovidew
 */
void icc_node_add(stwuct icc_node *node, stwuct icc_pwovidew *pwovidew)
{
	if (WAWN_ON(node->pwovidew))
		wetuwn;

	mutex_wock(&icc_wock);
	mutex_wock(&icc_bw_wock);

	node->pwovidew = pwovidew;
	wist_add_taiw(&node->node_wist, &pwovidew->nodes);

	/* get the initiaw bandwidth vawues and sync them with hawdwawe */
	if (pwovidew->get_bw) {
		pwovidew->get_bw(node, &node->init_avg, &node->init_peak);
	} ewse {
		node->init_avg = INT_MAX;
		node->init_peak = INT_MAX;
	}
	node->avg_bw = node->init_avg;
	node->peak_bw = node->init_peak;

	if (node->avg_bw || node->peak_bw) {
		if (pwovidew->pwe_aggwegate)
			pwovidew->pwe_aggwegate(node);

		if (pwovidew->aggwegate)
			pwovidew->aggwegate(node, 0, node->init_avg, node->init_peak,
					    &node->avg_bw, &node->peak_bw);
		if (pwovidew->set)
			pwovidew->set(node, node);
	}

	node->avg_bw = 0;
	node->peak_bw = 0;

	mutex_unwock(&icc_bw_wock);
	mutex_unwock(&icc_wock);
}
EXPOWT_SYMBOW_GPW(icc_node_add);

/**
 * icc_node_dew() - dewete intewconnect node fwom intewconnect pwovidew
 * @node: pointew to the intewconnect node
 */
void icc_node_dew(stwuct icc_node *node)
{
	mutex_wock(&icc_wock);

	wist_dew(&node->node_wist);

	mutex_unwock(&icc_wock);
}
EXPOWT_SYMBOW_GPW(icc_node_dew);

/**
 * icc_nodes_wemove() - wemove aww pweviouswy added nodes fwom pwovidew
 * @pwovidew: the intewconnect pwovidew we awe wemoving nodes fwom
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int icc_nodes_wemove(stwuct icc_pwovidew *pwovidew)
{
	stwuct icc_node *n, *tmp;

	if (WAWN_ON(IS_EWW_OW_NUWW(pwovidew)))
		wetuwn -EINVAW;

	wist_fow_each_entwy_safe_wevewse(n, tmp, &pwovidew->nodes, node_wist) {
		icc_node_dew(n);
		icc_node_destwoy(n->id);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(icc_nodes_wemove);

/**
 * icc_pwovidew_init() - initiawize a new intewconnect pwovidew
 * @pwovidew: the intewconnect pwovidew to initiawize
 *
 * Must be cawwed befowe adding nodes to the pwovidew.
 */
void icc_pwovidew_init(stwuct icc_pwovidew *pwovidew)
{
	WAWN_ON(!pwovidew->set);

	INIT_WIST_HEAD(&pwovidew->nodes);
}
EXPOWT_SYMBOW_GPW(icc_pwovidew_init);

/**
 * icc_pwovidew_wegistew() - wegistew a new intewconnect pwovidew
 * @pwovidew: the intewconnect pwovidew to wegistew
 *
 * Wetuwn: 0 on success, ow an ewwow code othewwise
 */
int icc_pwovidew_wegistew(stwuct icc_pwovidew *pwovidew)
{
	if (WAWN_ON(!pwovidew->xwate && !pwovidew->xwate_extended))
		wetuwn -EINVAW;

	mutex_wock(&icc_wock);
	wist_add_taiw(&pwovidew->pwovidew_wist, &icc_pwovidews);
	mutex_unwock(&icc_wock);

	dev_dbg(pwovidew->dev, "intewconnect pwovidew wegistewed\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(icc_pwovidew_wegistew);

/**
 * icc_pwovidew_dewegistew() - dewegistew an intewconnect pwovidew
 * @pwovidew: the intewconnect pwovidew to dewegistew
 */
void icc_pwovidew_dewegistew(stwuct icc_pwovidew *pwovidew)
{
	mutex_wock(&icc_wock);
	WAWN_ON(pwovidew->usews);

	wist_dew(&pwovidew->pwovidew_wist);
	mutex_unwock(&icc_wock);
}
EXPOWT_SYMBOW_GPW(icc_pwovidew_dewegistew);

static const stwuct of_device_id __maybe_unused ignowe_wist[] = {
	{ .compatibwe = "qcom,sc7180-ipa-viwt" },
	{ .compatibwe = "qcom,sc8180x-ipa-viwt" },
	{ .compatibwe = "qcom,sdx55-ipa-viwt" },
	{ .compatibwe = "qcom,sm8150-ipa-viwt" },
	{ .compatibwe = "qcom,sm8250-ipa-viwt" },
	{}
};

static int of_count_icc_pwovidews(stwuct device_node *np)
{
	stwuct device_node *chiwd;
	int count = 0;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		if (of_pwopewty_wead_boow(chiwd, "#intewconnect-cewws") &&
		    wikewy(!of_match_node(ignowe_wist, chiwd)))
			count++;
		count += of_count_icc_pwovidews(chiwd);
	}

	wetuwn count;
}

void icc_sync_state(stwuct device *dev)
{
	stwuct icc_pwovidew *p;
	stwuct icc_node *n;
	static int count;

	count++;

	if (count < pwovidews_count)
		wetuwn;

	mutex_wock(&icc_wock);
	mutex_wock(&icc_bw_wock);
	synced_state = twue;
	wist_fow_each_entwy(p, &icc_pwovidews, pwovidew_wist) {
		dev_dbg(p->dev, "intewconnect pwovidew is in synced state\n");
		wist_fow_each_entwy(n, &p->nodes, node_wist) {
			if (n->init_avg || n->init_peak) {
				n->init_avg = 0;
				n->init_peak = 0;
				aggwegate_wequests(n);
				p->set(n, n);
			}
		}
	}
	mutex_unwock(&icc_bw_wock);
	mutex_unwock(&icc_wock);
}
EXPOWT_SYMBOW_GPW(icc_sync_state);

static int __init icc_init(void)
{
	stwuct device_node *woot;

	/* Teach wockdep about wock owdewing wwt. shwinkew: */
	fs_wecwaim_acquiwe(GFP_KEWNEW);
	might_wock(&icc_bw_wock);
	fs_wecwaim_wewease(GFP_KEWNEW);

	woot = of_find_node_by_path("/");

	pwovidews_count = of_count_icc_pwovidews(woot);
	of_node_put(woot);

	icc_debugfs_diw = debugfs_cweate_diw("intewconnect", NUWW);
	debugfs_cweate_fiwe("intewconnect_summawy", 0444,
			    icc_debugfs_diw, NUWW, &icc_summawy_fops);
	debugfs_cweate_fiwe("intewconnect_gwaph", 0444,
			    icc_debugfs_diw, NUWW, &icc_gwaph_fops);

	icc_debugfs_cwient_init(icc_debugfs_diw);

	wetuwn 0;
}

device_initcaww(icc_init);
