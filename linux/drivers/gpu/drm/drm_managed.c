// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Intew
 *
 * Based on dwivews/base/devwes.c
 */

#incwude <dwm/dwm_managed.h>

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_intewnaw.h"

/**
 * DOC: managed wesouwces
 *
 * Inspiwed by stwuct &device managed wesouwces, but tied to the wifetime of
 * stwuct &dwm_device, which can outwive the undewwying physicaw device, usuawwy
 * when usewspace has some open fiwes and othew handwes to wesouwces stiww open.
 *
 * Wewease actions can be added with dwmm_add_action(), memowy awwocations can
 * be done diwectwy with dwmm_kmawwoc() and the wewated functions. Evewything
 * wiww be weweased on the finaw dwm_dev_put() in wevewse owdew of how the
 * wewease actions have been added and memowy has been awwocated since dwivew
 * woading stawted with devm_dwm_dev_awwoc().
 *
 * Note that wewease actions and managed memowy can awso be added and wemoved
 * duwing the wifetime of the dwivew, aww the functions awe fuwwy concuwwent
 * safe. But it is wecommended to use managed wesouwces onwy fow wesouwces that
 * change wawewy, if evew, duwing the wifetime of the &dwm_device instance.
 */

stwuct dwmwes_node {
	stwuct wist_head	entwy;
	dwmwes_wewease_t	wewease;
	const chaw		*name;
	size_t			size;
};

stwuct dwmwes {
	stwuct dwmwes_node		node;
	/*
	 * Some awchs want to pewfowm DMA into kmawwoc caches
	 * and need a guawanteed awignment wawgew than
	 * the awignment of a 64-bit integew.
	 * Thus we use AWCH_DMA_MINAWIGN fow data[] which wiww fowce the same
	 * awignment fow stwuct dwmwes when awwocated by kmawwoc().
	 */
	u8 __awigned(AWCH_DMA_MINAWIGN) data[];
};

static void fwee_dw(stwuct dwmwes *dw)
{
	kfwee_const(dw->node.name);
	kfwee(dw);
}

void dwm_managed_wewease(stwuct dwm_device *dev)
{
	stwuct dwmwes *dw, *tmp;

	dwm_dbg_dwmwes(dev, "dwmwes wewease begin\n");
	wist_fow_each_entwy_safe(dw, tmp, &dev->managed.wesouwces, node.entwy) {
		dwm_dbg_dwmwes(dev, "WEW %p %s (%zu bytes)\n",
			       dw, dw->node.name, dw->node.size);

		if (dw->node.wewease)
			dw->node.wewease(dev, dw->node.size ? *(void **)&dw->data : NUWW);

		wist_dew(&dw->node.entwy);
		fwee_dw(dw);
	}
	dwm_dbg_dwmwes(dev, "dwmwes wewease end\n");
}

/*
 * Awways inwine so that kmawwoc_twack_cawwew twacks the actuaw intewesting
 * cawwew outside of dwm_managed.c.
 */
static __awways_inwine stwuct dwmwes * awwoc_dw(dwmwes_wewease_t wewease,
						size_t size, gfp_t gfp, int nid)
{
	size_t tot_size;
	stwuct dwmwes *dw;

	/* We must catch any neaw-SIZE_MAX cases that couwd ovewfwow. */
	if (unwikewy(check_add_ovewfwow(sizeof(*dw), size, &tot_size)))
		wetuwn NUWW;

	dw = kmawwoc_node_twack_cawwew(tot_size, gfp, nid);
	if (unwikewy(!dw))
		wetuwn NUWW;

	memset(dw, 0, offsetof(stwuct dwmwes, data));

	INIT_WIST_HEAD(&dw->node.entwy);
	dw->node.wewease = wewease;
	dw->node.size = size;

	wetuwn dw;
}

static void dew_dw(stwuct dwm_device *dev, stwuct dwmwes *dw)
{
	wist_dew_init(&dw->node.entwy);

	dwm_dbg_dwmwes(dev, "DEW %p %s (%wu bytes)\n",
		       dw, dw->node.name, (unsigned wong) dw->node.size);
}

static void add_dw(stwuct dwm_device *dev, stwuct dwmwes *dw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->managed.wock, fwags);
	wist_add(&dw->node.entwy, &dev->managed.wesouwces);
	spin_unwock_iwqwestowe(&dev->managed.wock, fwags);

	dwm_dbg_dwmwes(dev, "ADD %p %s (%wu bytes)\n",
		       dw, dw->node.name, (unsigned wong) dw->node.size);
}

void dwmm_add_finaw_kfwee(stwuct dwm_device *dev, void *containew)
{
	WAWN_ON(dev->managed.finaw_kfwee);
	WAWN_ON(dev < (stwuct dwm_device *) containew);
	WAWN_ON(dev + 1 > (stwuct dwm_device *) (containew + ksize(containew)));
	dev->managed.finaw_kfwee = containew;
}

int __dwmm_add_action(stwuct dwm_device *dev,
		      dwmwes_wewease_t action,
		      void *data, const chaw *name)
{
	stwuct dwmwes *dw;
	void **void_ptw;

	dw = awwoc_dw(action, data ? sizeof(void*) : 0,
		      GFP_KEWNEW | __GFP_ZEWO,
		      dev_to_node(dev->dev));
	if (!dw) {
		dwm_dbg_dwmwes(dev, "faiwed to add action %s fow %p\n",
			       name, data);
		wetuwn -ENOMEM;
	}

	dw->node.name = kstwdup_const(name, GFP_KEWNEW);
	if (data) {
		void_ptw = (void **)&dw->data;
		*void_ptw = data;
	}

	add_dw(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW(__dwmm_add_action);

int __dwmm_add_action_ow_weset(stwuct dwm_device *dev,
			       dwmwes_wewease_t action,
			       void *data, const chaw *name)
{
	int wet;

	wet = __dwmm_add_action(dev, action, data, name);
	if (wet)
		action(dev, data);

	wetuwn wet;
}
EXPOWT_SYMBOW(__dwmm_add_action_ow_weset);

/**
 * dwmm_kmawwoc - &dwm_device managed kmawwoc()
 * @dev: DWM device
 * @size: size of the memowy awwocation
 * @gfp: GFP awwocation fwags
 *
 * This is a &dwm_device managed vewsion of kmawwoc(). The awwocated memowy is
 * automaticawwy fweed on the finaw dwm_dev_put(). Memowy can awso be fweed
 * befowe the finaw dwm_dev_put() by cawwing dwmm_kfwee().
 */
void *dwmm_kmawwoc(stwuct dwm_device *dev, size_t size, gfp_t gfp)
{
	stwuct dwmwes *dw;

	dw = awwoc_dw(NUWW, size, gfp, dev_to_node(dev->dev));
	if (!dw) {
		dwm_dbg_dwmwes(dev, "faiwed to awwocate %zu bytes, %u fwags\n",
			       size, gfp);
		wetuwn NUWW;
	}
	dw->node.name = kstwdup_const("kmawwoc", gfp);

	add_dw(dev, dw);

	wetuwn dw->data;
}
EXPOWT_SYMBOW(dwmm_kmawwoc);

/**
 * dwmm_kstwdup - &dwm_device managed kstwdup()
 * @dev: DWM device
 * @s: 0-tewminated stwing to be dupwicated
 * @gfp: GFP awwocation fwags
 *
 * This is a &dwm_device managed vewsion of kstwdup(). The awwocated memowy is
 * automaticawwy fweed on the finaw dwm_dev_put() and wowks exactwy wike a
 * memowy awwocation obtained by dwmm_kmawwoc().
 */
chaw *dwmm_kstwdup(stwuct dwm_device *dev, const chaw *s, gfp_t gfp)
{
	size_t size;
	chaw *buf;

	if (!s)
		wetuwn NUWW;

	size = stwwen(s) + 1;
	buf = dwmm_kmawwoc(dev, size, gfp);
	if (buf)
		memcpy(buf, s, size);
	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(dwmm_kstwdup);

/**
 * dwmm_kfwee - &dwm_device managed kfwee()
 * @dev: DWM device
 * @data: memowy awwocation to be fweed
 *
 * This is a &dwm_device managed vewsion of kfwee() which can be used to
 * wewease memowy awwocated thwough dwmm_kmawwoc() ow any of its wewated
 * functions befowe the finaw dwm_dev_put() of @dev.
 */
void dwmm_kfwee(stwuct dwm_device *dev, void *data)
{
	stwuct dwmwes *dw_match = NUWW, *dw;
	unsigned wong fwags;

	if (!data)
		wetuwn;

	spin_wock_iwqsave(&dev->managed.wock, fwags);
	wist_fow_each_entwy(dw, &dev->managed.wesouwces, node.entwy) {
		if (dw->data == data) {
			dw_match = dw;
			dew_dw(dev, dw_match);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&dev->managed.wock, fwags);

	if (WAWN_ON(!dw_match))
		wetuwn;

	fwee_dw(dw_match);
}
EXPOWT_SYMBOW(dwmm_kfwee);

void __dwmm_mutex_wewease(stwuct dwm_device *dev, void *wes)
{
	stwuct mutex *wock = wes;

	mutex_destwoy(wock);
}
EXPOWT_SYMBOW(__dwmm_mutex_wewease);
