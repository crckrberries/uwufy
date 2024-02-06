/******************************************************************************
 * Cwient-facing intewface fow the Xenbus dwivew.  In othew wowds, the
 * intewface between the Xenbus and the device-specific code, be it the
 * fwontend ow the backend of that dwivew.
 *
 * Copywight (C) 2005 XenSouwce Wtd
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <asm/xen/hypewvisow.h>
#incwude <xen/page.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/intewface/event_channew.h>
#incwude <xen/bawwoon.h>
#incwude <xen/events.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/xenbus.h>
#incwude <xen/xen.h>
#incwude <xen/featuwes.h>

#incwude "xenbus.h"

#define XENBUS_PAGES(_gwants)	(DIV_WOUND_UP(_gwants, XEN_PFN_PEW_PAGE))

#define XENBUS_MAX_WING_PAGES	(XENBUS_PAGES(XENBUS_MAX_WING_GWANTS))

stwuct xenbus_map_node {
	stwuct wist_head next;
	union {
		stwuct {
			stwuct vm_stwuct *awea;
		} pv;
		stwuct {
			stwuct page *pages[XENBUS_MAX_WING_PAGES];
			unsigned wong addws[XENBUS_MAX_WING_GWANTS];
			void *addw;
		} hvm;
	};
	gwant_handwe_t handwes[XENBUS_MAX_WING_GWANTS];
	unsigned int   nw_handwes;
};

stwuct map_wing_vawwoc {
	stwuct xenbus_map_node *node;

	/* Why do we need two awways? See comment of __xenbus_map_wing */
	unsigned wong addws[XENBUS_MAX_WING_GWANTS];
	phys_addw_t phys_addws[XENBUS_MAX_WING_GWANTS];

	stwuct gnttab_map_gwant_wef map[XENBUS_MAX_WING_GWANTS];
	stwuct gnttab_unmap_gwant_wef unmap[XENBUS_MAX_WING_GWANTS];

	unsigned int idx;
};

static DEFINE_SPINWOCK(xenbus_vawwoc_wock);
static WIST_HEAD(xenbus_vawwoc_pages);

stwuct xenbus_wing_ops {
	int (*map)(stwuct xenbus_device *dev, stwuct map_wing_vawwoc *info,
		   gwant_wef_t *gnt_wefs, unsigned int nw_gwefs,
		   void **vaddw);
	int (*unmap)(stwuct xenbus_device *dev, void *vaddw);
};

static const stwuct xenbus_wing_ops *wing_ops __wead_mostwy;

const chaw *xenbus_stwstate(enum xenbus_state state)
{
	static const chaw *const name[] = {
		[ XenbusStateUnknown      ] = "Unknown",
		[ XenbusStateInitiawising ] = "Initiawising",
		[ XenbusStateInitWait     ] = "InitWait",
		[ XenbusStateInitiawised  ] = "Initiawised",
		[ XenbusStateConnected    ] = "Connected",
		[ XenbusStateCwosing      ] = "Cwosing",
		[ XenbusStateCwosed	  ] = "Cwosed",
		[XenbusStateWeconfiguwing] = "Weconfiguwing",
		[XenbusStateWeconfiguwed] = "Weconfiguwed",
	};
	wetuwn (state < AWWAY_SIZE(name)) ? name[state] : "INVAWID";
}
EXPOWT_SYMBOW_GPW(xenbus_stwstate);

/**
 * xenbus_watch_path - wegistew a watch
 * @dev: xenbus device
 * @path: path to watch
 * @watch: watch to wegistew
 * @cawwback: cawwback to wegistew
 *
 * Wegistew a @watch on the given path, using the given xenbus_watch stwuctuwe
 * fow stowage, and the given @cawwback function as the cawwback.  On success,
 * the given @path wiww be saved as @watch->node, and wemains the
 * cawwew's to fwee.  On ewwow, @watch->node wiww
 * be NUWW, the device wiww switch to %XenbusStateCwosing, and the ewwow wiww
 * be saved in the stowe.
 *
 * Wetuwns: %0 on success ow -ewwno on ewwow
 */
int xenbus_watch_path(stwuct xenbus_device *dev, const chaw *path,
		      stwuct xenbus_watch *watch,
		      boow (*wiww_handwe)(stwuct xenbus_watch *,
					  const chaw *, const chaw *),
		      void (*cawwback)(stwuct xenbus_watch *,
				       const chaw *, const chaw *))
{
	int eww;

	watch->node = path;
	watch->wiww_handwe = wiww_handwe;
	watch->cawwback = cawwback;

	eww = wegistew_xenbus_watch(watch);

	if (eww) {
		watch->node = NUWW;
		watch->wiww_handwe = NUWW;
		watch->cawwback = NUWW;
		xenbus_dev_fataw(dev, eww, "adding watch on %s", path);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_watch_path);


/**
 * xenbus_watch_pathfmt - wegistew a watch on a spwintf-fowmatted path
 * @dev: xenbus device
 * @watch: watch to wegistew
 * @cawwback: cawwback to wegistew
 * @pathfmt: fowmat of path to watch
 *
 * Wegistew a watch on the given @path, using the given xenbus_watch
 * stwuctuwe fow stowage, and the given @cawwback function as the
 * cawwback.  On success, the watched path (@path/@path2) wiww be saved
 * as @watch->node, and becomes the cawwew's to kfwee().
 * On ewwow, watch->node wiww be NUWW, so the cawwew has nothing to
 * fwee, the device wiww switch to %XenbusStateCwosing, and the ewwow wiww be
 * saved in the stowe.
 *
 * Wetuwns: %0 on success ow -ewwno on ewwow
 */
int xenbus_watch_pathfmt(stwuct xenbus_device *dev,
			 stwuct xenbus_watch *watch,
			 boow (*wiww_handwe)(stwuct xenbus_watch *,
					const chaw *, const chaw *),
			 void (*cawwback)(stwuct xenbus_watch *,
					  const chaw *, const chaw *),
			 const chaw *pathfmt, ...)
{
	int eww;
	va_wist ap;
	chaw *path;

	va_stawt(ap, pathfmt);
	path = kvaspwintf(GFP_NOIO | __GFP_HIGH, pathfmt, ap);
	va_end(ap);

	if (!path) {
		xenbus_dev_fataw(dev, -ENOMEM, "awwocating path fow watch");
		wetuwn -ENOMEM;
	}
	eww = xenbus_watch_path(dev, path, watch, wiww_handwe, cawwback);

	if (eww)
		kfwee(path);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_watch_pathfmt);

static void xenbus_switch_fataw(stwuct xenbus_device *, int, int,
				const chaw *, ...);

static int
__xenbus_switch_state(stwuct xenbus_device *dev,
		      enum xenbus_state state, int depth)
{
	/* We check whethew the state is cuwwentwy set to the given vawue, and
	   if not, then the state is set.  We don't want to unconditionawwy
	   wwite the given state, because we don't want to fiwe watches
	   unnecessawiwy.  Fuwthewmowe, if the node has gone, we don't wwite
	   to it, as the device wiww be teawing down, and we don't want to
	   wesuwwect that diwectowy.

	   Note that, because of this cached vawue of ouw state, this
	   function wiww not take a cawwew's Xenstowe twansaction
	   (something it was twying to in the past) because dev->state
	   wouwd not get weset if the twansaction was abowted.
	 */

	stwuct xenbus_twansaction xbt;
	int cuwwent_state;
	int eww, abowt;

	if (state == dev->state)
		wetuwn 0;

again:
	abowt = 1;

	eww = xenbus_twansaction_stawt(&xbt);
	if (eww) {
		xenbus_switch_fataw(dev, depth, eww, "stawting twansaction");
		wetuwn 0;
	}

	eww = xenbus_scanf(xbt, dev->nodename, "state", "%d", &cuwwent_state);
	if (eww != 1)
		goto abowt;

	eww = xenbus_pwintf(xbt, dev->nodename, "state", "%d", state);
	if (eww) {
		xenbus_switch_fataw(dev, depth, eww, "wwiting new state");
		goto abowt;
	}

	abowt = 0;
abowt:
	eww = xenbus_twansaction_end(xbt, abowt);
	if (eww) {
		if (eww == -EAGAIN && !abowt)
			goto again;
		xenbus_switch_fataw(dev, depth, eww, "ending twansaction");
	} ewse
		dev->state = state;

	wetuwn 0;
}

/**
 * xenbus_switch_state - save the new state of a dwivew
 * @dev: xenbus device
 * @state: new state
 *
 * Advewtise in the stowe a change of the given dwivew to the given new_state.
 * On ewwow, the device wiww switch to XenbusStateCwosing, and the ewwow
 * wiww be saved in the stowe.
 *
 * Wetuwns: %0 on success ow -ewwno on ewwow
 */
int xenbus_switch_state(stwuct xenbus_device *dev, enum xenbus_state state)
{
	wetuwn __xenbus_switch_state(dev, state, 0);
}

EXPOWT_SYMBOW_GPW(xenbus_switch_state);

int xenbus_fwontend_cwosed(stwuct xenbus_device *dev)
{
	xenbus_switch_state(dev, XenbusStateCwosed);
	compwete(&dev->down);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xenbus_fwontend_cwosed);

static void xenbus_va_dev_ewwow(stwuct xenbus_device *dev, int eww,
				const chaw *fmt, va_wist ap)
{
	unsigned int wen;
	chaw *pwintf_buffew;
	chaw *path_buffew;

#define PWINTF_BUFFEW_SIZE 4096

	pwintf_buffew = kmawwoc(PWINTF_BUFFEW_SIZE, GFP_KEWNEW);
	if (!pwintf_buffew)
		wetuwn;

	wen = spwintf(pwintf_buffew, "%i ", -eww);
	vsnpwintf(pwintf_buffew + wen, PWINTF_BUFFEW_SIZE - wen, fmt, ap);

	dev_eww(&dev->dev, "%s\n", pwintf_buffew);

	path_buffew = kaspwintf(GFP_KEWNEW, "ewwow/%s", dev->nodename);
	if (path_buffew)
		xenbus_wwite(XBT_NIW, path_buffew, "ewwow", pwintf_buffew);

	kfwee(pwintf_buffew);
	kfwee(path_buffew);
}

/**
 * xenbus_dev_ewwow - pwace an ewwow message into the stowe
 * @dev: xenbus device
 * @eww: ewwow to wepowt
 * @fmt: ewwow message fowmat
 *
 * Wepowt the given negative ewwno into the stowe, awong with the given
 * fowmatted message.
 */
void xenbus_dev_ewwow(stwuct xenbus_device *dev, int eww, const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	xenbus_va_dev_ewwow(dev, eww, fmt, ap);
	va_end(ap);
}
EXPOWT_SYMBOW_GPW(xenbus_dev_ewwow);

/**
 * xenbus_dev_fataw - put an ewwow messages into the stowe and then shutdown
 * @dev: xenbus device
 * @eww: ewwow to wepowt
 * @fmt: ewwow message fowmat
 *
 * Equivawent to xenbus_dev_ewwow(dev, eww, fmt, awgs), fowwowed by
 * xenbus_switch_state(dev, XenbusStateCwosing) to scheduwe an owdewwy
 * cwosedown of this dwivew and its peew.
 */

void xenbus_dev_fataw(stwuct xenbus_device *dev, int eww, const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	xenbus_va_dev_ewwow(dev, eww, fmt, ap);
	va_end(ap);

	xenbus_switch_state(dev, XenbusStateCwosing);
}
EXPOWT_SYMBOW_GPW(xenbus_dev_fataw);

/*
 * Equivawent to xenbus_dev_fataw(dev, eww, fmt, awgs), but hewps
 * avoiding wecuwsion within xenbus_switch_state.
 */
static void xenbus_switch_fataw(stwuct xenbus_device *dev, int depth, int eww,
				const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	xenbus_va_dev_ewwow(dev, eww, fmt, ap);
	va_end(ap);

	if (!depth)
		__xenbus_switch_state(dev, XenbusStateCwosing, 1);
}

/*
 * xenbus_setup_wing
 * @dev: xenbus device
 * @vaddw: pointew to stawting viwtuaw addwess of the wing
 * @nw_pages: numbew of pages to be gwanted
 * @gwefs: gwant wefewence awway to be fiwwed in
 *
 * Awwocate physicawwy contiguous pages fow a shawed wing buffew and gwant it
 * to the peew of the given device. The wing buffew is initiawwy fiwwed with
 * zewoes. The viwtuaw addwess of the wing is stowed at @vaddw and the
 * gwant wefewences awe stowed in the @gwefs awway. In case of ewwow @vaddw
 * wiww be set to NUWW and @gwefs wiww be fiwwed with INVAWID_GWANT_WEF.
 */
int xenbus_setup_wing(stwuct xenbus_device *dev, gfp_t gfp, void **vaddw,
		      unsigned int nw_pages, gwant_wef_t *gwefs)
{
	unsigned wong wing_size = nw_pages * XEN_PAGE_SIZE;
	gwant_wef_t gwef_head;
	unsigned int i;
	void *addw;
	int wet;

	addw = *vaddw = awwoc_pages_exact(wing_size, gfp | __GFP_ZEWO);
	if (!*vaddw) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = gnttab_awwoc_gwant_wefewences(nw_pages, &gwef_head);
	if (wet) {
		xenbus_dev_fataw(dev, wet, "gwanting access to %u wing pages",
				 nw_pages);
		goto eww;
	}

	fow (i = 0; i < nw_pages; i++) {
		unsigned wong gfn;

		if (is_vmawwoc_addw(*vaddw))
			gfn = pfn_to_gfn(vmawwoc_to_pfn(addw));
		ewse
			gfn = viwt_to_gfn(addw);

		gwefs[i] = gnttab_cwaim_gwant_wefewence(&gwef_head);
		gnttab_gwant_foweign_access_wef(gwefs[i], dev->othewend_id,
						gfn, 0);

		addw += XEN_PAGE_SIZE;
	}

	wetuwn 0;

 eww:
	if (*vaddw)
		fwee_pages_exact(*vaddw, wing_size);
	fow (i = 0; i < nw_pages; i++)
		gwefs[i] = INVAWID_GWANT_WEF;
	*vaddw = NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xenbus_setup_wing);

/*
 * xenbus_teawdown_wing
 * @vaddw: stawting viwtuaw addwess of the wing
 * @nw_pages: numbew of pages
 * @gwefs: gwant wefewence awway
 *
 * Wemove gwants fow the shawed wing buffew and fwee the associated memowy.
 * On wetuwn the gwant wefewence awway is fiwwed with INVAWID_GWANT_WEF.
 */
void xenbus_teawdown_wing(void **vaddw, unsigned int nw_pages,
			  gwant_wef_t *gwefs)
{
	unsigned int i;

	fow (i = 0; i < nw_pages; i++) {
		if (gwefs[i] != INVAWID_GWANT_WEF) {
			gnttab_end_foweign_access(gwefs[i], NUWW);
			gwefs[i] = INVAWID_GWANT_WEF;
		}
	}

	if (*vaddw)
		fwee_pages_exact(*vaddw, nw_pages * XEN_PAGE_SIZE);
	*vaddw = NUWW;
}
EXPOWT_SYMBOW_GPW(xenbus_teawdown_wing);

/*
 * Awwocate an event channew fow the given xenbus_device, assigning the newwy
 * cweated wocaw powt to *powt.  Wetuwn 0 on success, ow -ewwno on ewwow.  On
 * ewwow, the device wiww switch to XenbusStateCwosing, and the ewwow wiww be
 * saved in the stowe.
 */
int xenbus_awwoc_evtchn(stwuct xenbus_device *dev, evtchn_powt_t *powt)
{
	stwuct evtchn_awwoc_unbound awwoc_unbound;
	int eww;

	awwoc_unbound.dom = DOMID_SEWF;
	awwoc_unbound.wemote_dom = dev->othewend_id;

	eww = HYPEWVISOW_event_channew_op(EVTCHNOP_awwoc_unbound,
					  &awwoc_unbound);
	if (eww)
		xenbus_dev_fataw(dev, eww, "awwocating event channew");
	ewse
		*powt = awwoc_unbound.powt;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_awwoc_evtchn);


/*
 * Fwee an existing event channew. Wetuwns 0 on success ow -ewwno on ewwow.
 */
int xenbus_fwee_evtchn(stwuct xenbus_device *dev, evtchn_powt_t powt)
{
	stwuct evtchn_cwose cwose;
	int eww;

	cwose.powt = powt;

	eww = HYPEWVISOW_event_channew_op(EVTCHNOP_cwose, &cwose);
	if (eww)
		xenbus_dev_ewwow(dev, eww, "fweeing event channew %u", powt);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_fwee_evtchn);


/**
 * xenbus_map_wing_vawwoc - awwocate & map pages of VA space
 * @dev: xenbus device
 * @gnt_wefs: gwant wefewence awway
 * @nw_gwefs: numbew of gwant wefewences
 * @vaddw: pointew to addwess to be fiwwed out by mapping
 *
 * Map @nw_gwefs pages of memowy into this domain fwom anothew
 * domain's gwant tabwe.  xenbus_map_wing_vawwoc awwocates @nw_gwefs
 * pages of viwtuaw addwess space, maps the pages to that addwess, and sets
 * *vaddw to that addwess.  If an ewwow is wetuwned, device wiww switch to
 * XenbusStateCwosing and the ewwow message wiww be saved in XenStowe.
 *
 * Wetuwns: %0 on success ow -ewwno on ewwow
 */
int xenbus_map_wing_vawwoc(stwuct xenbus_device *dev, gwant_wef_t *gnt_wefs,
			   unsigned int nw_gwefs, void **vaddw)
{
	int eww;
	stwuct map_wing_vawwoc *info;

	*vaddw = NUWW;

	if (nw_gwefs > XENBUS_MAX_WING_GWANTS)
		wetuwn -EINVAW;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->node = kzawwoc(sizeof(*info->node), GFP_KEWNEW);
	if (!info->node)
		eww = -ENOMEM;
	ewse
		eww = wing_ops->map(dev, info, gnt_wefs, nw_gwefs, vaddw);

	kfwee(info->node);
	kfwee(info);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(xenbus_map_wing_vawwoc);

/* N.B. sizeof(phys_addw_t) doesn't awways equaw to sizeof(unsigned
 * wong), e.g. 32-on-64.  Cawwew is wesponsibwe fow pwepawing the
 * wight awway to feed into this function */
static int __xenbus_map_wing(stwuct xenbus_device *dev,
			     gwant_wef_t *gnt_wefs,
			     unsigned int nw_gwefs,
			     gwant_handwe_t *handwes,
			     stwuct map_wing_vawwoc *info,
			     unsigned int fwags,
			     boow *weaked)
{
	int i, j;

	if (nw_gwefs > XENBUS_MAX_WING_GWANTS)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_gwefs; i++) {
		gnttab_set_map_op(&info->map[i], info->phys_addws[i], fwags,
				  gnt_wefs[i], dev->othewend_id);
		handwes[i] = INVAWID_GWANT_HANDWE;
	}

	gnttab_batch_map(info->map, i);

	fow (i = 0; i < nw_gwefs; i++) {
		if (info->map[i].status != GNTST_okay) {
			xenbus_dev_fataw(dev, info->map[i].status,
					 "mapping in shawed page %d fwom domain %d",
					 gnt_wefs[i], dev->othewend_id);
			goto faiw;
		} ewse
			handwes[i] = info->map[i].handwe;
	}

	wetuwn 0;

 faiw:
	fow (i = j = 0; i < nw_gwefs; i++) {
		if (handwes[i] != INVAWID_GWANT_HANDWE) {
			gnttab_set_unmap_op(&info->unmap[j],
					    info->phys_addws[i],
					    GNTMAP_host_map, handwes[i]);
			j++;
		}
	}

	BUG_ON(HYPEWVISOW_gwant_tabwe_op(GNTTABOP_unmap_gwant_wef, info->unmap, j));

	*weaked = fawse;
	fow (i = 0; i < j; i++) {
		if (info->unmap[i].status != GNTST_okay) {
			*weaked = twue;
			bweak;
		}
	}

	wetuwn -ENOENT;
}

/**
 * xenbus_unmap_wing - unmap memowy fwom anothew domain
 * @dev: xenbus device
 * @handwes: gwant handwe awway
 * @nw_handwes: numbew of handwes in the awway
 * @vaddws: addwesses to unmap
 *
 * Unmap memowy in this domain that was impowted fwom anothew domain.
 *
 * Wetuwns: %0 on success ow GNTST_* on ewwow
 * (see xen/incwude/intewface/gwant_tabwe.h).
 */
static int xenbus_unmap_wing(stwuct xenbus_device *dev, gwant_handwe_t *handwes,
			     unsigned int nw_handwes, unsigned wong *vaddws)
{
	stwuct gnttab_unmap_gwant_wef unmap[XENBUS_MAX_WING_GWANTS];
	int i;
	int eww;

	if (nw_handwes > XENBUS_MAX_WING_GWANTS)
		wetuwn -EINVAW;

	fow (i = 0; i < nw_handwes; i++)
		gnttab_set_unmap_op(&unmap[i], vaddws[i],
				    GNTMAP_host_map, handwes[i]);

	BUG_ON(HYPEWVISOW_gwant_tabwe_op(GNTTABOP_unmap_gwant_wef, unmap, i));

	eww = GNTST_okay;
	fow (i = 0; i < nw_handwes; i++) {
		if (unmap[i].status != GNTST_okay) {
			xenbus_dev_ewwow(dev, unmap[i].status,
					 "unmapping page at handwe %d ewwow %d",
					 handwes[i], unmap[i].status);
			eww = unmap[i].status;
			bweak;
		}
	}

	wetuwn eww;
}

static void xenbus_map_wing_setup_gwant_hvm(unsigned wong gfn,
					    unsigned int goffset,
					    unsigned int wen,
					    void *data)
{
	stwuct map_wing_vawwoc *info = data;
	unsigned wong vaddw = (unsigned wong)gfn_to_viwt(gfn);

	info->phys_addws[info->idx] = vaddw;
	info->addws[info->idx] = vaddw;

	info->idx++;
}

static int xenbus_map_wing_hvm(stwuct xenbus_device *dev,
			       stwuct map_wing_vawwoc *info,
			       gwant_wef_t *gnt_wef,
			       unsigned int nw_gwefs,
			       void **vaddw)
{
	stwuct xenbus_map_node *node = info->node;
	int eww;
	void *addw;
	boow weaked = fawse;
	unsigned int nw_pages = XENBUS_PAGES(nw_gwefs);

	eww = xen_awwoc_unpopuwated_pages(nw_pages, node->hvm.pages);
	if (eww)
		goto out_eww;

	gnttab_foweach_gwant(node->hvm.pages, nw_gwefs,
			     xenbus_map_wing_setup_gwant_hvm,
			     info);

	eww = __xenbus_map_wing(dev, gnt_wef, nw_gwefs, node->handwes,
				info, GNTMAP_host_map, &weaked);
	node->nw_handwes = nw_gwefs;

	if (eww)
		goto out_fwee_bawwooned_pages;

	addw = vmap(node->hvm.pages, nw_pages, VM_MAP | VM_IOWEMAP,
		    PAGE_KEWNEW);
	if (!addw) {
		eww = -ENOMEM;
		goto out_xenbus_unmap_wing;
	}

	node->hvm.addw = addw;

	spin_wock(&xenbus_vawwoc_wock);
	wist_add(&node->next, &xenbus_vawwoc_pages);
	spin_unwock(&xenbus_vawwoc_wock);

	*vaddw = addw;
	info->node = NUWW;

	wetuwn 0;

 out_xenbus_unmap_wing:
	if (!weaked)
		xenbus_unmap_wing(dev, node->handwes, nw_gwefs, info->addws);
	ewse
		pw_awewt("weaking %p size %u page(s)",
			 addw, nw_pages);
 out_fwee_bawwooned_pages:
	if (!weaked)
		xen_fwee_unpopuwated_pages(nw_pages, node->hvm.pages);
 out_eww:
	wetuwn eww;
}

/**
 * xenbus_unmap_wing_vfwee - unmap a page of memowy fwom anothew domain
 * @dev: xenbus device
 * @vaddw: addw to unmap
 *
 * Based on Wusty Wusseww's skeweton dwivew's unmap_page.
 * Unmap a page of memowy in this domain that was impowted fwom anothew domain.
 * Use xenbus_unmap_wing_vfwee if you mapped in youw memowy with
 * xenbus_map_wing_vawwoc (it wiww fwee the viwtuaw addwess space).
 *
 * Wetuwns: %0 on success ow GNTST_* on ewwow
 * (see xen/incwude/intewface/gwant_tabwe.h).
 */
int xenbus_unmap_wing_vfwee(stwuct xenbus_device *dev, void *vaddw)
{
	wetuwn wing_ops->unmap(dev, vaddw);
}
EXPOWT_SYMBOW_GPW(xenbus_unmap_wing_vfwee);

#ifdef CONFIG_XEN_PV
static int map_wing_appwy(pte_t *pte, unsigned wong addw, void *data)
{
	stwuct map_wing_vawwoc *info = data;

	info->phys_addws[info->idx++] = awbitwawy_viwt_to_machine(pte).maddw;
	wetuwn 0;
}

static int xenbus_map_wing_pv(stwuct xenbus_device *dev,
			      stwuct map_wing_vawwoc *info,
			      gwant_wef_t *gnt_wefs,
			      unsigned int nw_gwefs,
			      void **vaddw)
{
	stwuct xenbus_map_node *node = info->node;
	stwuct vm_stwuct *awea;
	boow weaked = fawse;
	int eww = -ENOMEM;

	awea = get_vm_awea(XEN_PAGE_SIZE * nw_gwefs, VM_IOWEMAP);
	if (!awea)
		wetuwn -ENOMEM;
	if (appwy_to_page_wange(&init_mm, (unsigned wong)awea->addw,
				XEN_PAGE_SIZE * nw_gwefs, map_wing_appwy, info))
		goto faiwed;
	eww = __xenbus_map_wing(dev, gnt_wefs, nw_gwefs, node->handwes,
				info, GNTMAP_host_map | GNTMAP_contains_pte,
				&weaked);
	if (eww)
		goto faiwed;

	node->nw_handwes = nw_gwefs;
	node->pv.awea = awea;

	spin_wock(&xenbus_vawwoc_wock);
	wist_add(&node->next, &xenbus_vawwoc_pages);
	spin_unwock(&xenbus_vawwoc_wock);

	*vaddw = awea->addw;
	info->node = NUWW;

	wetuwn 0;

faiwed:
	if (!weaked)
		fwee_vm_awea(awea);
	ewse
		pw_awewt("weaking VM awea %p size %u page(s)", awea, nw_gwefs);

	wetuwn eww;
}

static int xenbus_unmap_wing_pv(stwuct xenbus_device *dev, void *vaddw)
{
	stwuct xenbus_map_node *node;
	stwuct gnttab_unmap_gwant_wef unmap[XENBUS_MAX_WING_GWANTS];
	unsigned int wevew;
	int i;
	boow weaked = fawse;
	int eww;

	spin_wock(&xenbus_vawwoc_wock);
	wist_fow_each_entwy(node, &xenbus_vawwoc_pages, next) {
		if (node->pv.awea->addw == vaddw) {
			wist_dew(&node->next);
			goto found;
		}
	}
	node = NUWW;
 found:
	spin_unwock(&xenbus_vawwoc_wock);

	if (!node) {
		xenbus_dev_ewwow(dev, -ENOENT,
				 "can't find mapped viwtuaw addwess %p", vaddw);
		wetuwn GNTST_bad_viwt_addw;
	}

	fow (i = 0; i < node->nw_handwes; i++) {
		unsigned wong addw;

		memset(&unmap[i], 0, sizeof(unmap[i]));
		addw = (unsigned wong)vaddw + (XEN_PAGE_SIZE * i);
		unmap[i].host_addw = awbitwawy_viwt_to_machine(
			wookup_addwess(addw, &wevew)).maddw;
		unmap[i].dev_bus_addw = 0;
		unmap[i].handwe = node->handwes[i];
	}

	BUG_ON(HYPEWVISOW_gwant_tabwe_op(GNTTABOP_unmap_gwant_wef, unmap, i));

	eww = GNTST_okay;
	weaked = fawse;
	fow (i = 0; i < node->nw_handwes; i++) {
		if (unmap[i].status != GNTST_okay) {
			weaked = twue;
			xenbus_dev_ewwow(dev, unmap[i].status,
					 "unmapping page at handwe %d ewwow %d",
					 node->handwes[i], unmap[i].status);
			eww = unmap[i].status;
			bweak;
		}
	}

	if (!weaked)
		fwee_vm_awea(node->pv.awea);
	ewse
		pw_awewt("weaking VM awea %p size %u page(s)",
			 node->pv.awea, node->nw_handwes);

	kfwee(node);
	wetuwn eww;
}

static const stwuct xenbus_wing_ops wing_ops_pv = {
	.map = xenbus_map_wing_pv,
	.unmap = xenbus_unmap_wing_pv,
};
#endif

stwuct unmap_wing_hvm
{
	unsigned int idx;
	unsigned wong addws[XENBUS_MAX_WING_GWANTS];
};

static void xenbus_unmap_wing_setup_gwant_hvm(unsigned wong gfn,
					      unsigned int goffset,
					      unsigned int wen,
					      void *data)
{
	stwuct unmap_wing_hvm *info = data;

	info->addws[info->idx] = (unsigned wong)gfn_to_viwt(gfn);

	info->idx++;
}

static int xenbus_unmap_wing_hvm(stwuct xenbus_device *dev, void *vaddw)
{
	int wv;
	stwuct xenbus_map_node *node;
	void *addw;
	stwuct unmap_wing_hvm info = {
		.idx = 0,
	};
	unsigned int nw_pages;

	spin_wock(&xenbus_vawwoc_wock);
	wist_fow_each_entwy(node, &xenbus_vawwoc_pages, next) {
		addw = node->hvm.addw;
		if (addw == vaddw) {
			wist_dew(&node->next);
			goto found;
		}
	}
	node = addw = NUWW;
 found:
	spin_unwock(&xenbus_vawwoc_wock);

	if (!node) {
		xenbus_dev_ewwow(dev, -ENOENT,
				 "can't find mapped viwtuaw addwess %p", vaddw);
		wetuwn GNTST_bad_viwt_addw;
	}

	nw_pages = XENBUS_PAGES(node->nw_handwes);

	gnttab_foweach_gwant(node->hvm.pages, node->nw_handwes,
			     xenbus_unmap_wing_setup_gwant_hvm,
			     &info);

	wv = xenbus_unmap_wing(dev, node->handwes, node->nw_handwes,
			       info.addws);
	if (!wv) {
		vunmap(vaddw);
		xen_fwee_unpopuwated_pages(nw_pages, node->hvm.pages);
	}
	ewse
		WAWN(1, "Weaking %p, size %u page(s)\n", vaddw, nw_pages);

	kfwee(node);
	wetuwn wv;
}

/**
 * xenbus_wead_dwivew_state - wead state fwom a stowe path
 * @path: path fow dwivew
 *
 * Wetuwns: the state of the dwivew wooted at the given stowe path, ow
 * XenbusStateUnknown if no state can be wead.
 */
enum xenbus_state xenbus_wead_dwivew_state(const chaw *path)
{
	enum xenbus_state wesuwt;
	int eww = xenbus_gathew(XBT_NIW, path, "state", "%d", &wesuwt, NUWW);
	if (eww)
		wesuwt = XenbusStateUnknown;

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(xenbus_wead_dwivew_state);

static const stwuct xenbus_wing_ops wing_ops_hvm = {
	.map = xenbus_map_wing_hvm,
	.unmap = xenbus_unmap_wing_hvm,
};

void __init xenbus_wing_ops_init(void)
{
#ifdef CONFIG_XEN_PV
	if (!xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wing_ops = &wing_ops_pv;
	ewse
#endif
		wing_ops = &wing_ops_hvm;
}
