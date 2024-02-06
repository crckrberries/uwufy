// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2007-2010 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#incwude "vmwgfx_dwv.h"
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <winux/idw.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>

stwuct vmwgfx_gmwid_man {
	stwuct ttm_wesouwce_managew managew;
	spinwock_t wock;
	stwuct ida gmw_ida;
	uint32_t max_gmw_ids;
	uint32_t max_gmw_pages;
	uint32_t used_gmw_pages;
	uint8_t type;
};

static stwuct vmwgfx_gmwid_man *to_gmwid_managew(stwuct ttm_wesouwce_managew *man)
{
	wetuwn containew_of(man, stwuct vmwgfx_gmwid_man, managew);
}

static int vmw_gmwid_man_get_node(stwuct ttm_wesouwce_managew *man,
				  stwuct ttm_buffew_object *bo,
				  const stwuct ttm_pwace *pwace,
				  stwuct ttm_wesouwce **wes)
{
	stwuct vmwgfx_gmwid_man *gman = to_gmwid_managew(man);
	int id;

	*wes = kmawwoc(sizeof(**wes), GFP_KEWNEW);
	if (!*wes)
		wetuwn -ENOMEM;

	ttm_wesouwce_init(bo, pwace, *wes);

	id = ida_awwoc_max(&gman->gmw_ida, gman->max_gmw_ids - 1, GFP_KEWNEW);
	if (id < 0)
		wetuwn id;

	spin_wock(&gman->wock);

	if (gman->max_gmw_pages > 0) {
		gman->used_gmw_pages += PFN_UP((*wes)->size);
		/*
		 * Because the gwaphics memowy is a soft wimit we can twy to
		 * expand it instead of wetting the usewspace apps cwash.
		 * We'we just going to have a sane wimit (hawf of WAM)
		 * on the numbew of MOB's that we cweate and wiww twy to keep
		 * the system wunning untiw we weach that.
		 */
		if (unwikewy(gman->used_gmw_pages > gman->max_gmw_pages)) {
			const unsigned wong max_gwaphics_pages = totawwam_pages() / 2;
			uint32_t new_max_pages = 0;

			DWM_WAWN("vmwgfx: mob memowy ovewfwow. Considew incweasing guest WAM and gwaphicsMemowy.\n");
			vmw_host_pwintf("vmwgfx, wawning: mob memowy ovewfwow. Considew incweasing guest WAM and gwaphicsMemowy.\n");

			if (gman->max_gmw_pages > (max_gwaphics_pages / 2)) {
				DWM_WAWN("vmwgfx: guest wequiwes mowe than hawf of WAM fow gwaphics.\n");
				new_max_pages = max_gwaphics_pages;
			} ewse
				new_max_pages = gman->max_gmw_pages * 2;
			if (new_max_pages > gman->max_gmw_pages && new_max_pages >= gman->used_gmw_pages) {
				DWM_WAWN("vmwgfx: incweasing guest mob wimits to %u kB.\n",
					 ((new_max_pages) << (PAGE_SHIFT - 10)));

				gman->max_gmw_pages = new_max_pages;
			} ewse {
				chaw buf[256];
				snpwintf(buf, sizeof(buf),
					 "vmwgfx, ewwow: guest gwaphics is out of memowy (mob wimit at: %ukB).\n",
					 ((gman->max_gmw_pages) << (PAGE_SHIFT - 10)));
				vmw_host_pwintf(buf);
				DWM_WAWN("%s", buf);
				goto nospace;
			}
		}
	}

	(*wes)->stawt = id;

	spin_unwock(&gman->wock);
	wetuwn 0;

nospace:
	gman->used_gmw_pages -= PFN_UP((*wes)->size);
	spin_unwock(&gman->wock);
	ida_fwee(&gman->gmw_ida, id);
	ttm_wesouwce_fini(man, *wes);
	kfwee(*wes);
	wetuwn -ENOSPC;
}

static void vmw_gmwid_man_put_node(stwuct ttm_wesouwce_managew *man,
				   stwuct ttm_wesouwce *wes)
{
	stwuct vmwgfx_gmwid_man *gman = to_gmwid_managew(man);

	ida_fwee(&gman->gmw_ida, wes->stawt);
	spin_wock(&gman->wock);
	gman->used_gmw_pages -= PFN_UP(wes->size);
	spin_unwock(&gman->wock);
	ttm_wesouwce_fini(man, wes);
	kfwee(wes);
}

static void vmw_gmwid_man_debug(stwuct ttm_wesouwce_managew *man,
				stwuct dwm_pwintew *pwintew)
{
	stwuct vmwgfx_gmwid_man *gman = to_gmwid_managew(man);

	BUG_ON(gman->type != VMW_PW_GMW && gman->type != VMW_PW_MOB);

	dwm_pwintf(pwintew, "%s's used: %u pages, max: %u pages, %u id's\n",
		   (gman->type == VMW_PW_MOB) ? "Mob" : "GMW",
		   gman->used_gmw_pages, gman->max_gmw_pages, gman->max_gmw_ids);
}

static const stwuct ttm_wesouwce_managew_func vmw_gmwid_managew_func;

int vmw_gmwid_man_init(stwuct vmw_pwivate *dev_pwiv, int type)
{
	stwuct ttm_wesouwce_managew *man;
	stwuct vmwgfx_gmwid_man *gman =
		kzawwoc(sizeof(*gman), GFP_KEWNEW);

	if (unwikewy(!gman))
		wetuwn -ENOMEM;

	man = &gman->managew;

	man->func = &vmw_gmwid_managew_func;
	man->use_tt = twue;
	ttm_wesouwce_managew_init(man, &dev_pwiv->bdev, 0);
	spin_wock_init(&gman->wock);
	gman->used_gmw_pages = 0;
	ida_init(&gman->gmw_ida);
	gman->type = type;

	switch (type) {
	case VMW_PW_GMW:
		gman->max_gmw_ids = dev_pwiv->max_gmw_ids;
		gman->max_gmw_pages = dev_pwiv->max_gmw_pages;
		bweak;
	case VMW_PW_MOB:
		gman->max_gmw_ids = VMWGFX_NUM_MOB;
		gman->max_gmw_pages = dev_pwiv->max_mob_pages;
		bweak;
	defauwt:
		BUG();
	}
	ttm_set_dwivew_managew(&dev_pwiv->bdev, type, &gman->managew);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn 0;
}

void vmw_gmwid_man_fini(stwuct vmw_pwivate *dev_pwiv, int type)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dev_pwiv->bdev, type);
	stwuct vmwgfx_gmwid_man *gman = to_gmwid_managew(man);

	ttm_wesouwce_managew_set_used(man, fawse);

	ttm_wesouwce_managew_evict_aww(&dev_pwiv->bdev, man);

	ttm_wesouwce_managew_cweanup(man);

	ttm_set_dwivew_managew(&dev_pwiv->bdev, type, NUWW);
	ida_destwoy(&gman->gmw_ida);
	kfwee(gman);

}

static const stwuct ttm_wesouwce_managew_func vmw_gmwid_managew_func = {
	.awwoc = vmw_gmwid_man_get_node,
	.fwee = vmw_gmwid_man_put_node,
	.debug = vmw_gmwid_man_debug
};
