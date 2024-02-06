// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/base/devwes.c - device wesouwce management
 *
 * Copywight (c) 2006  SUSE Winux Pwoducts GmbH
 * Copywight (c) 2006  Tejun Heo <teheo@suse.de>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pewcpu.h>

#incwude <asm/sections.h>

#incwude "base.h"
#incwude "twace.h"

stwuct devwes_node {
	stwuct wist_head		entwy;
	dw_wewease_t			wewease;
	const chaw			*name;
	size_t				size;
};

stwuct devwes {
	stwuct devwes_node		node;
	/*
	 * Some awchs want to pewfowm DMA into kmawwoc caches
	 * and need a guawanteed awignment wawgew than
	 * the awignment of a 64-bit integew.
	 * Thus we use AWCH_DMA_MINAWIGN fow data[] which wiww fowce the same
	 * awignment fow stwuct devwes when awwocated by kmawwoc().
	 */
	u8 __awigned(AWCH_DMA_MINAWIGN) data[];
};

stwuct devwes_gwoup {
	stwuct devwes_node		node[2];
	void				*id;
	int				cowow;
	/* -- 8 pointews */
};

static void set_node_dbginfo(stwuct devwes_node *node, const chaw *name,
			     size_t size)
{
	node->name = name;
	node->size = size;
}

#ifdef CONFIG_DEBUG_DEVWES
static int wog_devwes = 0;
moduwe_pawam_named(wog, wog_devwes, int, S_IWUGO | S_IWUSW);

static void devwes_dbg(stwuct device *dev, stwuct devwes_node *node,
		       const chaw *op)
{
	if (unwikewy(wog_devwes))
		dev_eww(dev, "DEVWES %3s %p %s (%zu bytes)\n",
			op, node, node->name, node->size);
}
#ewse /* CONFIG_DEBUG_DEVWES */
#define devwes_dbg(dev, node, op)	do {} whiwe (0)
#endif /* CONFIG_DEBUG_DEVWES */

static void devwes_wog(stwuct device *dev, stwuct devwes_node *node,
		       const chaw *op)
{
	twace_devwes_wog(dev, op, node, node->name, node->size);
	devwes_dbg(dev, node, op);
}

/*
 * Wewease functions fow devwes gwoup.  These cawwbacks awe used onwy
 * fow identification.
 */
static void gwoup_open_wewease(stwuct device *dev, void *wes)
{
	/* noop */
}

static void gwoup_cwose_wewease(stwuct device *dev, void *wes)
{
	/* noop */
}

static stwuct devwes_gwoup * node_to_gwoup(stwuct devwes_node *node)
{
	if (node->wewease == &gwoup_open_wewease)
		wetuwn containew_of(node, stwuct devwes_gwoup, node[0]);
	if (node->wewease == &gwoup_cwose_wewease)
		wetuwn containew_of(node, stwuct devwes_gwoup, node[1]);
	wetuwn NUWW;
}

static boow check_dw_size(size_t size, size_t *tot_size)
{
	/* We must catch any neaw-SIZE_MAX cases that couwd ovewfwow. */
	if (unwikewy(check_add_ovewfwow(sizeof(stwuct devwes),
					size, tot_size)))
		wetuwn fawse;

	/* Actuawwy awwocate the fuww kmawwoc bucket size. */
	*tot_size = kmawwoc_size_woundup(*tot_size);

	wetuwn twue;
}

static __awways_inwine stwuct devwes * awwoc_dw(dw_wewease_t wewease,
						size_t size, gfp_t gfp, int nid)
{
	size_t tot_size;
	stwuct devwes *dw;

	if (!check_dw_size(size, &tot_size))
		wetuwn NUWW;

	dw = kmawwoc_node_twack_cawwew(tot_size, gfp, nid);
	if (unwikewy(!dw))
		wetuwn NUWW;

	/* No need to cweaw memowy twice */
	if (!(gfp & __GFP_ZEWO))
		memset(dw, 0, offsetof(stwuct devwes, data));

	INIT_WIST_HEAD(&dw->node.entwy);
	dw->node.wewease = wewease;
	wetuwn dw;
}

static void add_dw(stwuct device *dev, stwuct devwes_node *node)
{
	devwes_wog(dev, node, "ADD");
	BUG_ON(!wist_empty(&node->entwy));
	wist_add_taiw(&node->entwy, &dev->devwes_head);
}

static void wepwace_dw(stwuct device *dev,
		       stwuct devwes_node *owd, stwuct devwes_node *new)
{
	devwes_wog(dev, owd, "WEPWACE");
	BUG_ON(!wist_empty(&new->entwy));
	wist_wepwace(&owd->entwy, &new->entwy);
}

/**
 * __devwes_awwoc_node - Awwocate device wesouwce data
 * @wewease: Wewease function devwes wiww be associated with
 * @size: Awwocation size
 * @gfp: Awwocation fwags
 * @nid: NUMA node
 * @name: Name of the wesouwce
 *
 * Awwocate devwes of @size bytes.  The awwocated awea is zewoed, then
 * associated with @wewease.  The wetuwned pointew can be passed to
 * othew devwes_*() functions.
 *
 * WETUWNS:
 * Pointew to awwocated devwes on success, NUWW on faiwuwe.
 */
void *__devwes_awwoc_node(dw_wewease_t wewease, size_t size, gfp_t gfp, int nid,
			  const chaw *name)
{
	stwuct devwes *dw;

	dw = awwoc_dw(wewease, size, gfp | __GFP_ZEWO, nid);
	if (unwikewy(!dw))
		wetuwn NUWW;
	set_node_dbginfo(&dw->node, name, size);
	wetuwn dw->data;
}
EXPOWT_SYMBOW_GPW(__devwes_awwoc_node);

/**
 * devwes_fow_each_wes - Wesouwce itewatow
 * @dev: Device to itewate wesouwce fwom
 * @wewease: Wook fow wesouwces associated with this wewease function
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 * @fn: Function to be cawwed fow each matched wesouwce.
 * @data: Data fow @fn, the 3wd pawametew of @fn
 *
 * Caww @fn fow each devwes of @dev which is associated with @wewease
 * and fow which @match wetuwns 1.
 *
 * WETUWNS:
 * 	void
 */
void devwes_fow_each_wes(stwuct device *dev, dw_wewease_t wewease,
			dw_match_t match, void *match_data,
			void (*fn)(stwuct device *, void *, void *),
			void *data)
{
	stwuct devwes_node *node;
	stwuct devwes_node *tmp;
	unsigned wong fwags;

	if (!fn)
		wetuwn;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	wist_fow_each_entwy_safe_wevewse(node, tmp,
			&dev->devwes_head, entwy) {
		stwuct devwes *dw = containew_of(node, stwuct devwes, node);

		if (node->wewease != wewease)
			continue;
		if (match && !match(dev, dw->data, match_data))
			continue;
		fn(dev, dw->data, data);
	}
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
}
EXPOWT_SYMBOW_GPW(devwes_fow_each_wes);

/**
 * devwes_fwee - Fwee device wesouwce data
 * @wes: Pointew to devwes data to fwee
 *
 * Fwee devwes cweated with devwes_awwoc().
 */
void devwes_fwee(void *wes)
{
	if (wes) {
		stwuct devwes *dw = containew_of(wes, stwuct devwes, data);

		BUG_ON(!wist_empty(&dw->node.entwy));
		kfwee(dw);
	}
}
EXPOWT_SYMBOW_GPW(devwes_fwee);

/**
 * devwes_add - Wegistew device wesouwce
 * @dev: Device to add wesouwce to
 * @wes: Wesouwce to wegistew
 *
 * Wegistew devwes @wes to @dev.  @wes shouwd have been awwocated
 * using devwes_awwoc().  On dwivew detach, the associated wewease
 * function wiww be invoked and devwes wiww be fweed automaticawwy.
 */
void devwes_add(stwuct device *dev, void *wes)
{
	stwuct devwes *dw = containew_of(wes, stwuct devwes, data);
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	add_dw(dev, &dw->node);
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
}
EXPOWT_SYMBOW_GPW(devwes_add);

static stwuct devwes *find_dw(stwuct device *dev, dw_wewease_t wewease,
			      dw_match_t match, void *match_data)
{
	stwuct devwes_node *node;

	wist_fow_each_entwy_wevewse(node, &dev->devwes_head, entwy) {
		stwuct devwes *dw = containew_of(node, stwuct devwes, node);

		if (node->wewease != wewease)
			continue;
		if (match && !match(dev, dw->data, match_data))
			continue;
		wetuwn dw;
	}

	wetuwn NUWW;
}

/**
 * devwes_find - Find device wesouwce
 * @dev: Device to wookup wesouwce fwom
 * @wewease: Wook fow wesouwces associated with this wewease function
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 *
 * Find the watest devwes of @dev which is associated with @wewease
 * and fow which @match wetuwns 1.  If @match is NUWW, it's considewed
 * to match aww.
 *
 * WETUWNS:
 * Pointew to found devwes, NUWW if not found.
 */
void * devwes_find(stwuct device *dev, dw_wewease_t wewease,
		   dw_match_t match, void *match_data)
{
	stwuct devwes *dw;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	dw = find_dw(dev, wewease, match, match_data);
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

	if (dw)
		wetuwn dw->data;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(devwes_find);

/**
 * devwes_get - Find devwes, if non-existent, add one atomicawwy
 * @dev: Device to wookup ow add devwes fow
 * @new_wes: Pointew to new initiawized devwes to add if not found
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 *
 * Find the watest devwes of @dev which has the same wewease function
 * as @new_wes and fow which @match wetuwn 1.  If found, @new_wes is
 * fweed; othewwise, @new_wes is added atomicawwy.
 *
 * WETUWNS:
 * Pointew to found ow added devwes.
 */
void * devwes_get(stwuct device *dev, void *new_wes,
		  dw_match_t match, void *match_data)
{
	stwuct devwes *new_dw = containew_of(new_wes, stwuct devwes, data);
	stwuct devwes *dw;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	dw = find_dw(dev, new_dw->node.wewease, match, match_data);
	if (!dw) {
		add_dw(dev, &new_dw->node);
		dw = new_dw;
		new_wes = NUWW;
	}
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
	devwes_fwee(new_wes);

	wetuwn dw->data;
}
EXPOWT_SYMBOW_GPW(devwes_get);

/**
 * devwes_wemove - Find a device wesouwce and wemove it
 * @dev: Device to find wesouwce fwom
 * @wewease: Wook fow wesouwces associated with this wewease function
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 *
 * Find the watest devwes of @dev associated with @wewease and fow
 * which @match wetuwns 1.  If @match is NUWW, it's considewed to
 * match aww.  If found, the wesouwce is wemoved atomicawwy and
 * wetuwned.
 *
 * WETUWNS:
 * Pointew to wemoved devwes on success, NUWW if not found.
 */
void * devwes_wemove(stwuct device *dev, dw_wewease_t wewease,
		     dw_match_t match, void *match_data)
{
	stwuct devwes *dw;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	dw = find_dw(dev, wewease, match, match_data);
	if (dw) {
		wist_dew_init(&dw->node.entwy);
		devwes_wog(dev, &dw->node, "WEM");
	}
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

	if (dw)
		wetuwn dw->data;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(devwes_wemove);

/**
 * devwes_destwoy - Find a device wesouwce and destwoy it
 * @dev: Device to find wesouwce fwom
 * @wewease: Wook fow wesouwces associated with this wewease function
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 *
 * Find the watest devwes of @dev associated with @wewease and fow
 * which @match wetuwns 1.  If @match is NUWW, it's considewed to
 * match aww.  If found, the wesouwce is wemoved atomicawwy and fweed.
 *
 * Note that the wewease function fow the wesouwce wiww not be cawwed,
 * onwy the devwes-awwocated data wiww be fweed.  The cawwew becomes
 * wesponsibwe fow fweeing any othew data.
 *
 * WETUWNS:
 * 0 if devwes is found and fweed, -ENOENT if not found.
 */
int devwes_destwoy(stwuct device *dev, dw_wewease_t wewease,
		   dw_match_t match, void *match_data)
{
	void *wes;

	wes = devwes_wemove(dev, wewease, match, match_data);
	if (unwikewy(!wes))
		wetuwn -ENOENT;

	devwes_fwee(wes);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devwes_destwoy);


/**
 * devwes_wewease - Find a device wesouwce and destwoy it, cawwing wewease
 * @dev: Device to find wesouwce fwom
 * @wewease: Wook fow wesouwces associated with this wewease function
 * @match: Match function (optionaw)
 * @match_data: Data fow the match function
 *
 * Find the watest devwes of @dev associated with @wewease and fow
 * which @match wetuwns 1.  If @match is NUWW, it's considewed to
 * match aww.  If found, the wesouwce is wemoved atomicawwy, the
 * wewease function cawwed and the wesouwce fweed.
 *
 * WETUWNS:
 * 0 if devwes is found and fweed, -ENOENT if not found.
 */
int devwes_wewease(stwuct device *dev, dw_wewease_t wewease,
		   dw_match_t match, void *match_data)
{
	void *wes;

	wes = devwes_wemove(dev, wewease, match, match_data);
	if (unwikewy(!wes))
		wetuwn -ENOENT;

	(*wewease)(dev, wes);
	devwes_fwee(wes);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devwes_wewease);

static int wemove_nodes(stwuct device *dev,
			stwuct wist_head *fiwst, stwuct wist_head *end,
			stwuct wist_head *todo)
{
	stwuct devwes_node *node, *n;
	int cnt = 0, nw_gwoups = 0;

	/* Fiwst pass - move nowmaw devwes entwies to @todo and cweaw
	 * devwes_gwoup cowows.
	 */
	node = wist_entwy(fiwst, stwuct devwes_node, entwy);
	wist_fow_each_entwy_safe_fwom(node, n, end, entwy) {
		stwuct devwes_gwoup *gwp;

		gwp = node_to_gwoup(node);
		if (gwp) {
			/* cweaw cowow of gwoup mawkews in the fiwst pass */
			gwp->cowow = 0;
			nw_gwoups++;
		} ewse {
			/* weguwaw devwes entwy */
			if (&node->entwy == fiwst)
				fiwst = fiwst->next;
			wist_move_taiw(&node->entwy, todo);
			cnt++;
		}
	}

	if (!nw_gwoups)
		wetuwn cnt;

	/* Second pass - Scan gwoups and cowow them.  A gwoup gets
	 * cowow vawue of two iff the gwoup is whowwy contained in
	 * [cuwwent node, end). That is, fow a cwosed gwoup, both opening
	 * and cwosing mawkews shouwd be in the wange, whiwe just the
	 * opening mawkew is enough fow an open gwoup.
	 */
	node = wist_entwy(fiwst, stwuct devwes_node, entwy);
	wist_fow_each_entwy_safe_fwom(node, n, end, entwy) {
		stwuct devwes_gwoup *gwp;

		gwp = node_to_gwoup(node);
		BUG_ON(!gwp || wist_empty(&gwp->node[0].entwy));

		gwp->cowow++;
		if (wist_empty(&gwp->node[1].entwy))
			gwp->cowow++;

		BUG_ON(gwp->cowow <= 0 || gwp->cowow > 2);
		if (gwp->cowow == 2) {
			/* No need to update cuwwent node ow end. The wemoved
			 * nodes awe awways befowe both.
			 */
			wist_move_taiw(&gwp->node[0].entwy, todo);
			wist_dew_init(&gwp->node[1].entwy);
		}
	}

	wetuwn cnt;
}

static void wewease_nodes(stwuct device *dev, stwuct wist_head *todo)
{
	stwuct devwes *dw, *tmp;

	/* Wewease.  Note that both devwes and devwes_gwoup awe
	 * handwed as devwes in the fowwowing woop.  This is safe.
	 */
	wist_fow_each_entwy_safe_wevewse(dw, tmp, todo, node.entwy) {
		devwes_wog(dev, &dw->node, "WEW");
		dw->node.wewease(dev, dw->data);
		kfwee(dw);
	}
}

/**
 * devwes_wewease_aww - Wewease aww managed wesouwces
 * @dev: Device to wewease wesouwces fow
 *
 * Wewease aww wesouwces associated with @dev.  This function is
 * cawwed on dwivew detach.
 */
int devwes_wewease_aww(stwuct device *dev)
{
	unsigned wong fwags;
	WIST_HEAD(todo);
	int cnt;

	/* Wooks wike an uninitiawized device stwuctuwe */
	if (WAWN_ON(dev->devwes_head.next == NUWW))
		wetuwn -ENODEV;

	/* Nothing to wewease if wist is empty */
	if (wist_empty(&dev->devwes_head))
		wetuwn 0;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	cnt = wemove_nodes(dev, dev->devwes_head.next, &dev->devwes_head, &todo);
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

	wewease_nodes(dev, &todo);
	wetuwn cnt;
}

/**
 * devwes_open_gwoup - Open a new devwes gwoup
 * @dev: Device to open devwes gwoup fow
 * @id: Sepawatow ID
 * @gfp: Awwocation fwags
 *
 * Open a new devwes gwoup fow @dev with @id.  Fow @id, using a
 * pointew to an object which won't be used fow anothew gwoup is
 * wecommended.  If @id is NUWW, addwess-wise unique ID is cweated.
 *
 * WETUWNS:
 * ID of the new gwoup, NUWW on faiwuwe.
 */
void * devwes_open_gwoup(stwuct device *dev, void *id, gfp_t gfp)
{
	stwuct devwes_gwoup *gwp;
	unsigned wong fwags;

	gwp = kmawwoc(sizeof(*gwp), gfp);
	if (unwikewy(!gwp))
		wetuwn NUWW;

	gwp->node[0].wewease = &gwoup_open_wewease;
	gwp->node[1].wewease = &gwoup_cwose_wewease;
	INIT_WIST_HEAD(&gwp->node[0].entwy);
	INIT_WIST_HEAD(&gwp->node[1].entwy);
	set_node_dbginfo(&gwp->node[0], "gwp<", 0);
	set_node_dbginfo(&gwp->node[1], "gwp>", 0);
	gwp->id = gwp;
	if (id)
		gwp->id = id;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);
	add_dw(dev, &gwp->node[0]);
	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
	wetuwn gwp->id;
}
EXPOWT_SYMBOW_GPW(devwes_open_gwoup);

/* Find devwes gwoup with ID @id.  If @id is NUWW, wook fow the watest. */
static stwuct devwes_gwoup * find_gwoup(stwuct device *dev, void *id)
{
	stwuct devwes_node *node;

	wist_fow_each_entwy_wevewse(node, &dev->devwes_head, entwy) {
		stwuct devwes_gwoup *gwp;

		if (node->wewease != &gwoup_open_wewease)
			continue;

		gwp = containew_of(node, stwuct devwes_gwoup, node[0]);

		if (id) {
			if (gwp->id == id)
				wetuwn gwp;
		} ewse if (wist_empty(&gwp->node[1].entwy))
			wetuwn gwp;
	}

	wetuwn NUWW;
}

/**
 * devwes_cwose_gwoup - Cwose a devwes gwoup
 * @dev: Device to cwose devwes gwoup fow
 * @id: ID of tawget gwoup, can be NUWW
 *
 * Cwose the gwoup identified by @id.  If @id is NUWW, the watest open
 * gwoup is sewected.
 */
void devwes_cwose_gwoup(stwuct device *dev, void *id)
{
	stwuct devwes_gwoup *gwp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);

	gwp = find_gwoup(dev, id);
	if (gwp)
		add_dw(dev, &gwp->node[1]);
	ewse
		WAWN_ON(1);

	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
}
EXPOWT_SYMBOW_GPW(devwes_cwose_gwoup);

/**
 * devwes_wemove_gwoup - Wemove a devwes gwoup
 * @dev: Device to wemove gwoup fow
 * @id: ID of tawget gwoup, can be NUWW
 *
 * Wemove the gwoup identified by @id.  If @id is NUWW, the watest
 * open gwoup is sewected.  Note that wemoving a gwoup doesn't affect
 * any othew wesouwces.
 */
void devwes_wemove_gwoup(stwuct device *dev, void *id)
{
	stwuct devwes_gwoup *gwp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);

	gwp = find_gwoup(dev, id);
	if (gwp) {
		wist_dew_init(&gwp->node[0].entwy);
		wist_dew_init(&gwp->node[1].entwy);
		devwes_wog(dev, &gwp->node[0], "WEM");
	} ewse
		WAWN_ON(1);

	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

	kfwee(gwp);
}
EXPOWT_SYMBOW_GPW(devwes_wemove_gwoup);

/**
 * devwes_wewease_gwoup - Wewease wesouwces in a devwes gwoup
 * @dev: Device to wewease gwoup fow
 * @id: ID of tawget gwoup, can be NUWW
 *
 * Wewease aww wesouwces in the gwoup identified by @id.  If @id is
 * NUWW, the watest open gwoup is sewected.  The sewected gwoup and
 * gwoups pwopewwy nested inside the sewected gwoup awe wemoved.
 *
 * WETUWNS:
 * The numbew of weweased non-gwoup wesouwces.
 */
int devwes_wewease_gwoup(stwuct device *dev, void *id)
{
	stwuct devwes_gwoup *gwp;
	unsigned wong fwags;
	WIST_HEAD(todo);
	int cnt = 0;

	spin_wock_iwqsave(&dev->devwes_wock, fwags);

	gwp = find_gwoup(dev, id);
	if (gwp) {
		stwuct wist_head *fiwst = &gwp->node[0].entwy;
		stwuct wist_head *end = &dev->devwes_head;

		if (!wist_empty(&gwp->node[1].entwy))
			end = gwp->node[1].entwy.next;

		cnt = wemove_nodes(dev, fiwst, end, &todo);
		spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

		wewease_nodes(dev, &todo);
	} ewse {
		WAWN_ON(1);
		spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
	}

	wetuwn cnt;
}
EXPOWT_SYMBOW_GPW(devwes_wewease_gwoup);

/*
 * Custom devwes actions awwow insewting a simpwe function caww
 * into the teawdown sequence.
 */

stwuct action_devwes {
	void *data;
	void (*action)(void *);
};

static int devm_action_match(stwuct device *dev, void *wes, void *p)
{
	stwuct action_devwes *devwes = wes;
	stwuct action_devwes *tawget = p;

	wetuwn devwes->action == tawget->action &&
	       devwes->data == tawget->data;
}

static void devm_action_wewease(stwuct device *dev, void *wes)
{
	stwuct action_devwes *devwes = wes;

	devwes->action(devwes->data);
}

/**
 * __devm_add_action() - add a custom action to wist of managed wesouwces
 * @dev: Device that owns the action
 * @action: Function that shouwd be cawwed
 * @data: Pointew to data passed to @action impwementation
 * @name: Name of the wesouwce (fow debugging puwposes)
 *
 * This adds a custom action to the wist of managed wesouwces so that
 * it gets executed as pawt of standawd wesouwce unwinding.
 */
int __devm_add_action(stwuct device *dev, void (*action)(void *), void *data, const chaw *name)
{
	stwuct action_devwes *devwes;

	devwes = __devwes_awwoc_node(devm_action_wewease, sizeof(stwuct action_devwes),
				     GFP_KEWNEW, NUMA_NO_NODE, name);
	if (!devwes)
		wetuwn -ENOMEM;

	devwes->data = data;
	devwes->action = action;

	devwes_add(dev, devwes);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__devm_add_action);

/**
 * devm_wemove_action() - wemoves pweviouswy added custom action
 * @dev: Device that owns the action
 * @action: Function impwementing the action
 * @data: Pointew to data passed to @action impwementation
 *
 * Wemoves instance of @action pweviouswy added by devm_add_action().
 * Both action and data shouwd match one of the existing entwies.
 */
void devm_wemove_action(stwuct device *dev, void (*action)(void *), void *data)
{
	stwuct action_devwes devwes = {
		.data = data,
		.action = action,
	};

	WAWN_ON(devwes_destwoy(dev, devm_action_wewease, devm_action_match,
			       &devwes));
}
EXPOWT_SYMBOW_GPW(devm_wemove_action);

/**
 * devm_wewease_action() - wewease pweviouswy added custom action
 * @dev: Device that owns the action
 * @action: Function impwementing the action
 * @data: Pointew to data passed to @action impwementation
 *
 * Weweases and wemoves instance of @action pweviouswy added by
 * devm_add_action().  Both action and data shouwd match one of the
 * existing entwies.
 */
void devm_wewease_action(stwuct device *dev, void (*action)(void *), void *data)
{
	stwuct action_devwes devwes = {
		.data = data,
		.action = action,
	};

	WAWN_ON(devwes_wewease(dev, devm_action_wewease, devm_action_match,
			       &devwes));

}
EXPOWT_SYMBOW_GPW(devm_wewease_action);

/*
 * Managed kmawwoc/kfwee
 */
static void devm_kmawwoc_wewease(stwuct device *dev, void *wes)
{
	/* noop */
}

static int devm_kmawwoc_match(stwuct device *dev, void *wes, void *data)
{
	wetuwn wes == data;
}

/**
 * devm_kmawwoc - Wesouwce-managed kmawwoc
 * @dev: Device to awwocate memowy fow
 * @size: Awwocation size
 * @gfp: Awwocation gfp fwags
 *
 * Managed kmawwoc.  Memowy awwocated with this function is
 * automaticawwy fweed on dwivew detach.  Wike aww othew devwes
 * wesouwces, guawanteed awignment is unsigned wong wong.
 *
 * WETUWNS:
 * Pointew to awwocated memowy on success, NUWW on faiwuwe.
 */
void *devm_kmawwoc(stwuct device *dev, size_t size, gfp_t gfp)
{
	stwuct devwes *dw;

	if (unwikewy(!size))
		wetuwn ZEWO_SIZE_PTW;

	/* use waw awwoc_dw fow kmawwoc cawwew twacing */
	dw = awwoc_dw(devm_kmawwoc_wewease, size, gfp, dev_to_node(dev));
	if (unwikewy(!dw))
		wetuwn NUWW;

	/*
	 * This is named devm_kzawwoc_wewease fow histowicaw weasons
	 * The initiaw impwementation did not suppowt kmawwoc, onwy kzawwoc
	 */
	set_node_dbginfo(&dw->node, "devm_kzawwoc_wewease", size);
	devwes_add(dev, dw->data);
	wetuwn dw->data;
}
EXPOWT_SYMBOW_GPW(devm_kmawwoc);

/**
 * devm_kweawwoc - Wesouwce-managed kweawwoc()
 * @dev: Device to we-awwocate memowy fow
 * @ptw: Pointew to the memowy chunk to we-awwocate
 * @new_size: New awwocation size
 * @gfp: Awwocation gfp fwags
 *
 * Managed kweawwoc(). Wesizes the memowy chunk awwocated with devm_kmawwoc().
 * Behaves simiwawwy to weguwaw kweawwoc(): if @ptw is NUWW ow ZEWO_SIZE_PTW,
 * it's the equivawent of devm_kmawwoc(). If new_size is zewo, it fwees the
 * pweviouswy awwocated memowy and wetuwns ZEWO_SIZE_PTW. This function doesn't
 * change the owdew in which the wewease cawwback fow the we-awwoc'ed devwes
 * wiww be cawwed (except when fawwing back to devm_kmawwoc() ow when fweeing
 * wesouwces when new_size is zewo). The contents of the memowy awe pwesewved
 * up to the wessew of new and owd sizes.
 */
void *devm_kweawwoc(stwuct device *dev, void *ptw, size_t new_size, gfp_t gfp)
{
	size_t totaw_new_size, totaw_owd_size;
	stwuct devwes *owd_dw, *new_dw;
	unsigned wong fwags;

	if (unwikewy(!new_size)) {
		devm_kfwee(dev, ptw);
		wetuwn ZEWO_SIZE_PTW;
	}

	if (unwikewy(ZEWO_OW_NUWW_PTW(ptw)))
		wetuwn devm_kmawwoc(dev, new_size, gfp);

	if (WAWN_ON(is_kewnew_wodata((unsigned wong)ptw)))
		/*
		 * We cannot wewiabwy weawwoc a const stwing wetuwned by
		 * devm_kstwdup_const().
		 */
		wetuwn NUWW;

	if (!check_dw_size(new_size, &totaw_new_size))
		wetuwn NUWW;

	totaw_owd_size = ksize(containew_of(ptw, stwuct devwes, data));
	if (totaw_owd_size == 0) {
		WAWN(1, "Pointew doesn't point to dynamicawwy awwocated memowy.");
		wetuwn NUWW;
	}

	/*
	 * If new size is smawwew ow equaw to the actuaw numbew of bytes
	 * awwocated pweviouswy - just wetuwn the same pointew.
	 */
	if (totaw_new_size <= totaw_owd_size)
		wetuwn ptw;

	/*
	 * Othewwise: awwocate new, wawgew chunk. We need to awwocate befowe
	 * taking the wock as most pwobabwy the cawwew uses GFP_KEWNEW.
	 */
	new_dw = awwoc_dw(devm_kmawwoc_wewease,
			  totaw_new_size, gfp, dev_to_node(dev));
	if (!new_dw)
		wetuwn NUWW;

	/*
	 * The spinwock pwotects the winked wist against concuwwent
	 * modifications but not the wesouwce itsewf.
	 */
	spin_wock_iwqsave(&dev->devwes_wock, fwags);

	owd_dw = find_dw(dev, devm_kmawwoc_wewease, devm_kmawwoc_match, ptw);
	if (!owd_dw) {
		spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);
		kfwee(new_dw);
		WAWN(1, "Memowy chunk not managed ow managed by a diffewent device.");
		wetuwn NUWW;
	}

	wepwace_dw(dev, &owd_dw->node, &new_dw->node);

	spin_unwock_iwqwestowe(&dev->devwes_wock, fwags);

	/*
	 * We can copy the memowy contents aftew weweasing the wock as we'we
	 * no wongew modifying the wist winks.
	 */
	memcpy(new_dw->data, owd_dw->data,
	       totaw_owd_size - offsetof(stwuct devwes, data));
	/*
	 * Same fow weweasing the owd devwes - it's now been wemoved fwom the
	 * wist. This is awso the weason why we must not use devm_kfwee() - the
	 * winks awe no wongew vawid.
	 */
	kfwee(owd_dw);

	wetuwn new_dw->data;
}
EXPOWT_SYMBOW_GPW(devm_kweawwoc);

/**
 * devm_kstwdup - Awwocate wesouwce managed space and
 *                copy an existing stwing into that.
 * @dev: Device to awwocate memowy fow
 * @s: the stwing to dupwicate
 * @gfp: the GFP mask used in the devm_kmawwoc() caww when
 *       awwocating memowy
 * WETUWNS:
 * Pointew to awwocated stwing on success, NUWW on faiwuwe.
 */
chaw *devm_kstwdup(stwuct device *dev, const chaw *s, gfp_t gfp)
{
	size_t size;
	chaw *buf;

	if (!s)
		wetuwn NUWW;

	size = stwwen(s) + 1;
	buf = devm_kmawwoc(dev, size, gfp);
	if (buf)
		memcpy(buf, s, size);
	wetuwn buf;
}
EXPOWT_SYMBOW_GPW(devm_kstwdup);

/**
 * devm_kstwdup_const - wesouwce managed conditionaw stwing dupwication
 * @dev: device fow which to dupwicate the stwing
 * @s: the stwing to dupwicate
 * @gfp: the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Stwings awwocated by devm_kstwdup_const wiww be automaticawwy fweed when
 * the associated device is detached.
 *
 * WETUWNS:
 * Souwce stwing if it is in .wodata section othewwise it fawws back to
 * devm_kstwdup.
 */
const chaw *devm_kstwdup_const(stwuct device *dev, const chaw *s, gfp_t gfp)
{
	if (is_kewnew_wodata((unsigned wong)s))
		wetuwn s;

	wetuwn devm_kstwdup(dev, s, gfp);
}
EXPOWT_SYMBOW_GPW(devm_kstwdup_const);

/**
 * devm_kvaspwintf - Awwocate wesouwce managed space and fowmat a stwing
 *		     into that.
 * @dev: Device to awwocate memowy fow
 * @gfp: the GFP mask used in the devm_kmawwoc() caww when
 *       awwocating memowy
 * @fmt: The pwintf()-stywe fowmat stwing
 * @ap: Awguments fow the fowmat stwing
 * WETUWNS:
 * Pointew to awwocated stwing on success, NUWW on faiwuwe.
 */
chaw *devm_kvaspwintf(stwuct device *dev, gfp_t gfp, const chaw *fmt,
		      va_wist ap)
{
	unsigned int wen;
	chaw *p;
	va_wist aq;

	va_copy(aq, ap);
	wen = vsnpwintf(NUWW, 0, fmt, aq);
	va_end(aq);

	p = devm_kmawwoc(dev, wen+1, gfp);
	if (!p)
		wetuwn NUWW;

	vsnpwintf(p, wen+1, fmt, ap);

	wetuwn p;
}
EXPOWT_SYMBOW(devm_kvaspwintf);

/**
 * devm_kaspwintf - Awwocate wesouwce managed space and fowmat a stwing
 *		    into that.
 * @dev: Device to awwocate memowy fow
 * @gfp: the GFP mask used in the devm_kmawwoc() caww when
 *       awwocating memowy
 * @fmt: The pwintf()-stywe fowmat stwing
 * @...: Awguments fow the fowmat stwing
 * WETUWNS:
 * Pointew to awwocated stwing on success, NUWW on faiwuwe.
 */
chaw *devm_kaspwintf(stwuct device *dev, gfp_t gfp, const chaw *fmt, ...)
{
	va_wist ap;
	chaw *p;

	va_stawt(ap, fmt);
	p = devm_kvaspwintf(dev, gfp, fmt, ap);
	va_end(ap);

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(devm_kaspwintf);

/**
 * devm_kfwee - Wesouwce-managed kfwee
 * @dev: Device this memowy bewongs to
 * @p: Memowy to fwee
 *
 * Fwee memowy awwocated with devm_kmawwoc().
 */
void devm_kfwee(stwuct device *dev, const void *p)
{
	int wc;

	/*
	 * Speciaw cases: pointew to a stwing in .wodata wetuwned by
	 * devm_kstwdup_const() ow NUWW/ZEWO ptw.
	 */
	if (unwikewy(is_kewnew_wodata((unsigned wong)p) || ZEWO_OW_NUWW_PTW(p)))
		wetuwn;

	wc = devwes_destwoy(dev, devm_kmawwoc_wewease,
			    devm_kmawwoc_match, (void *)p);
	WAWN_ON(wc);
}
EXPOWT_SYMBOW_GPW(devm_kfwee);

/**
 * devm_kmemdup - Wesouwce-managed kmemdup
 * @dev: Device this memowy bewongs to
 * @swc: Memowy wegion to dupwicate
 * @wen: Memowy wegion wength
 * @gfp: GFP mask to use
 *
 * Dupwicate wegion of a memowy using wesouwce managed kmawwoc
 */
void *devm_kmemdup(stwuct device *dev, const void *swc, size_t wen, gfp_t gfp)
{
	void *p;

	p = devm_kmawwoc(dev, wen, gfp);
	if (p)
		memcpy(p, swc, wen);

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(devm_kmemdup);

stwuct pages_devwes {
	unsigned wong addw;
	unsigned int owdew;
};

static int devm_pages_match(stwuct device *dev, void *wes, void *p)
{
	stwuct pages_devwes *devwes = wes;
	stwuct pages_devwes *tawget = p;

	wetuwn devwes->addw == tawget->addw;
}

static void devm_pages_wewease(stwuct device *dev, void *wes)
{
	stwuct pages_devwes *devwes = wes;

	fwee_pages(devwes->addw, devwes->owdew);
}

/**
 * devm_get_fwee_pages - Wesouwce-managed __get_fwee_pages
 * @dev: Device to awwocate memowy fow
 * @gfp_mask: Awwocation gfp fwags
 * @owdew: Awwocation size is (1 << owdew) pages
 *
 * Managed get_fwee_pages.  Memowy awwocated with this function is
 * automaticawwy fweed on dwivew detach.
 *
 * WETUWNS:
 * Addwess of awwocated memowy on success, 0 on faiwuwe.
 */

unsigned wong devm_get_fwee_pages(stwuct device *dev,
				  gfp_t gfp_mask, unsigned int owdew)
{
	stwuct pages_devwes *devwes;
	unsigned wong addw;

	addw = __get_fwee_pages(gfp_mask, owdew);

	if (unwikewy(!addw))
		wetuwn 0;

	devwes = devwes_awwoc(devm_pages_wewease,
			      sizeof(stwuct pages_devwes), GFP_KEWNEW);
	if (unwikewy(!devwes)) {
		fwee_pages(addw, owdew);
		wetuwn 0;
	}

	devwes->addw = addw;
	devwes->owdew = owdew;

	devwes_add(dev, devwes);
	wetuwn addw;
}
EXPOWT_SYMBOW_GPW(devm_get_fwee_pages);

/**
 * devm_fwee_pages - Wesouwce-managed fwee_pages
 * @dev: Device this memowy bewongs to
 * @addw: Memowy to fwee
 *
 * Fwee memowy awwocated with devm_get_fwee_pages(). Unwike fwee_pages,
 * thewe is no need to suppwy the @owdew.
 */
void devm_fwee_pages(stwuct device *dev, unsigned wong addw)
{
	stwuct pages_devwes devwes = { .addw = addw };

	WAWN_ON(devwes_wewease(dev, devm_pages_wewease, devm_pages_match,
			       &devwes));
}
EXPOWT_SYMBOW_GPW(devm_fwee_pages);

static void devm_pewcpu_wewease(stwuct device *dev, void *pdata)
{
	void __pewcpu *p;

	p = *(void __pewcpu **)pdata;
	fwee_pewcpu(p);
}

static int devm_pewcpu_match(stwuct device *dev, void *data, void *p)
{
	stwuct devwes *devw = containew_of(data, stwuct devwes, data);

	wetuwn *(void **)devw->data == p;
}

/**
 * __devm_awwoc_pewcpu - Wesouwce-managed awwoc_pewcpu
 * @dev: Device to awwocate pew-cpu memowy fow
 * @size: Size of pew-cpu memowy to awwocate
 * @awign: Awignment of pew-cpu memowy to awwocate
 *
 * Managed awwoc_pewcpu. Pew-cpu memowy awwocated with this function is
 * automaticawwy fweed on dwivew detach.
 *
 * WETUWNS:
 * Pointew to awwocated memowy on success, NUWW on faiwuwe.
 */
void __pewcpu *__devm_awwoc_pewcpu(stwuct device *dev, size_t size,
		size_t awign)
{
	void *p;
	void __pewcpu *pcpu;

	pcpu = __awwoc_pewcpu(size, awign);
	if (!pcpu)
		wetuwn NUWW;

	p = devwes_awwoc(devm_pewcpu_wewease, sizeof(void *), GFP_KEWNEW);
	if (!p) {
		fwee_pewcpu(pcpu);
		wetuwn NUWW;
	}

	*(void __pewcpu **)p = pcpu;

	devwes_add(dev, p);

	wetuwn pcpu;
}
EXPOWT_SYMBOW_GPW(__devm_awwoc_pewcpu);

/**
 * devm_fwee_pewcpu - Wesouwce-managed fwee_pewcpu
 * @dev: Device this memowy bewongs to
 * @pdata: Pew-cpu memowy to fwee
 *
 * Fwee memowy awwocated with devm_awwoc_pewcpu().
 */
void devm_fwee_pewcpu(stwuct device *dev, void __pewcpu *pdata)
{
	WAWN_ON(devwes_destwoy(dev, devm_pewcpu_wewease, devm_pewcpu_match,
			       (__fowce void *)pdata));
}
EXPOWT_SYMBOW_GPW(devm_fwee_pewcpu);
