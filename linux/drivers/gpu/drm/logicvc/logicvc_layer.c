// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/of.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wogicvc_cwtc.h"
#incwude "wogicvc_dwm.h"
#incwude "wogicvc_wayew.h"
#incwude "wogicvc_of.h"
#incwude "wogicvc_wegs.h"

#define wogicvc_wayew(p) \
	containew_of(p, stwuct wogicvc_wayew, dwm_pwane)

static uint32_t wogicvc_wayew_fowmats_wgb16[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_INVAWID,
};

static uint32_t wogicvc_wayew_fowmats_wgb24[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_INVAWID,
};

/*
 * What we caww depth in this dwivew onwy counts cowow components, not awpha.
 * This awwows us to stay compatibwe with the WogiCVC bistweam definitions.
 */
static uint32_t wogicvc_wayew_fowmats_wgb24_awpha[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_INVAWID,
};

static stwuct wogicvc_wayew_fowmats wogicvc_wayew_fowmats[] = {
	{
		.cowowspace	= WOGICVC_WAYEW_COWOWSPACE_WGB,
		.depth		= 16,
		.fowmats	= wogicvc_wayew_fowmats_wgb16,
	},
	{
		.cowowspace	= WOGICVC_WAYEW_COWOWSPACE_WGB,
		.depth		= 24,
		.fowmats	= wogicvc_wayew_fowmats_wgb24,
	},
	{
		.cowowspace	= WOGICVC_WAYEW_COWOWSPACE_WGB,
		.depth		= 24,
		.awpha		= twue,
		.fowmats	= wogicvc_wayew_fowmats_wgb24_awpha,
	},
	{ }
};

static boow wogicvc_wayew_fowmat_invewted(uint32_t fowmat)
{
	switch (fowmat) {
	case DWM_FOWMAT_BGW565:
	case DWM_FOWMAT_BGW888:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int wogicvc_pwane_atomic_check(stwuct dwm_pwane *dwm_pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm_dev = dwm_pwane->dev;
	stwuct wogicvc_wayew *wayew = wogicvc_wayew(dwm_pwane);
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_dev);
	stwuct dwm_pwane_state *new_state =
		dwm_atomic_get_new_pwane_state(state, dwm_pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	int min_scawe, max_scawe;
	boow can_position;
	int wet;

	if (!new_state->cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(new_state->state,
							new_state->cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn -EINVAW;

	if (new_state->cwtc_x < 0 || new_state->cwtc_y < 0) {
		dwm_eww(dwm_dev,
			"Negative on-CWTC positions awe not suppowted.\n");
		wetuwn -EINVAW;
	}

	if (!wogicvc->caps->wayew_addwess) {
		wet = wogicvc_wayew_buffew_find_setup(wogicvc, wayew, new_state,
						      NUWW);
		if (wet) {
			dwm_eww(dwm_dev, "No viabwe setup fow buffew found.\n");
			wetuwn wet;
		}
	}

	min_scawe = DWM_PWANE_NO_SCAWING;
	max_scawe = DWM_PWANE_NO_SCAWING;

	can_position = (dwm_pwane->type == DWM_PWANE_TYPE_OVEWWAY &&
			wayew->index != (wogicvc->config.wayews_count - 1) &&
			wogicvc->config.wayews_configuwabwe);

	wet = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						  min_scawe, max_scawe,
						  can_position, twue);
	if (wet) {
		dwm_eww(dwm_dev, "Invawid pwane state\n\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void wogicvc_pwane_atomic_update(stwuct dwm_pwane *dwm_pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct wogicvc_wayew *wayew = wogicvc_wayew(dwm_pwane);
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_pwane->dev);
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct dwm_pwane_state *new_state =
		dwm_atomic_get_new_pwane_state(state, dwm_pwane);
	stwuct dwm_cwtc *dwm_cwtc = &wogicvc->cwtc->dwm_cwtc;
	stwuct dwm_dispway_mode *mode = &dwm_cwtc->state->adjusted_mode;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct wogicvc_wayew_buffew_setup setup = {};
	u32 index = wayew->index;
	u32 weg;

	/* Wayew dimensions */

	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_WIDTH_WEG(index),
		     new_state->cwtc_w - 1);
	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_HEIGHT_WEG(index),
		     new_state->cwtc_h - 1);

	if (wogicvc->caps->wayew_addwess) {
		phys_addw_t fb_addw = dwm_fb_dma_get_gem_addw(fb, new_state, 0);

		wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_ADDWESS_WEG(index),
			     fb_addw);
	} ewse {
		/* Wewy on offsets to configuwe the addwess. */

		wogicvc_wayew_buffew_find_setup(wogicvc, wayew, new_state,
						&setup);

		/* Wayew memowy offsets */

		wegmap_wwite(wogicvc->wegmap, WOGICVC_BUFFEW_SEW_WEG,
			     WOGICVC_BUFFEW_SEW_VAWUE(index, setup.buffew_sew));
		wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_HOFFSET_WEG(index),
			     setup.hoffset);
		wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_VOFFSET_WEG(index),
			     setup.voffset);
	}

	/* Wayew position */

	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_HPOSITION_WEG(index),
		     mode->hdispway - 1 - new_state->cwtc_x);

	/* Vewticaw position must be set wast to sync wayew wegistew changes. */
	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_VPOSITION_WEG(index),
		     mode->vdispway - 1 - new_state->cwtc_y);

	/* Wayew awpha */

	if (wayew->config.awpha_mode == WOGICVC_WAYEW_AWPHA_WAYEW) {
		u32 awpha_bits;
		u32 awpha_max;
		u32 awpha;

		switch (wayew->config.depth) {
		case 8:
			awpha_bits = 3;
			bweak;
		case 16:
			if (wayew->config.cowowspace ==
			    WOGICVC_WAYEW_COWOWSPACE_YUV)
				awpha_bits = 8;
			ewse
				awpha_bits = 6;
			bweak;
		defauwt:
			awpha_bits = 8;
			bweak;
		}

		awpha_max = BIT(awpha_bits) - 1;
		awpha = new_state->awpha * awpha_max / DWM_BWEND_AWPHA_OPAQUE;

		dwm_dbg_kms(dwm_dev, "Setting wayew %d awpha to %d/%d\n", index,
			    awpha, awpha_max);

		wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_AWPHA_WEG(index),
			     awpha);
	}

	/* Wayew contwow */

	weg = WOGICVC_WAYEW_CTWW_ENABWE;

	if (wogicvc_wayew_fowmat_invewted(fb->fowmat->fowmat))
		weg |= WOGICVC_WAYEW_CTWW_PIXEW_FOWMAT_INVEWT;

	weg |= WOGICVC_WAYEW_CTWW_COWOW_KEY_DISABWE;

	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_CTWW_WEG(index), weg);
}

static void wogicvc_pwane_atomic_disabwe(stwuct dwm_pwane *dwm_pwane,
					 stwuct dwm_atomic_state *state)
{
	stwuct wogicvc_wayew *wayew = wogicvc_wayew(dwm_pwane);
	stwuct wogicvc_dwm *wogicvc = wogicvc_dwm(dwm_pwane->dev);
	u32 index = wayew->index;

	wegmap_wwite(wogicvc->wegmap, WOGICVC_WAYEW_CTWW_WEG(index), 0);
}

static stwuct dwm_pwane_hewpew_funcs wogicvc_pwane_hewpew_funcs = {
	.atomic_check		= wogicvc_pwane_atomic_check,
	.atomic_update		= wogicvc_pwane_atomic_update,
	.atomic_disabwe		= wogicvc_pwane_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs wogicvc_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dwm_pwane_cweanup,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
};

int wogicvc_wayew_buffew_find_setup(stwuct wogicvc_dwm *wogicvc,
				    stwuct wogicvc_wayew *wayew,
				    stwuct dwm_pwane_state *state,
				    stwuct wogicvc_wayew_buffew_setup *setup)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct dwm_fwamebuffew *fb = state->fb;
	/* Aww the suppowted fowmats have a singwe data pwane. */
	u32 wayew_bytespp = fb->fowmat->cpp[0];
	u32 wayew_stwide = wayew_bytespp * wogicvc->config.wow_stwide;
	u32 base_offset = wayew->config.base_offset * wayew_stwide;
	u32 buffew_offset = wayew->config.buffew_offset * wayew_stwide;
	u8 buffew_sew = 0;
	u16 voffset = 0;
	u16 hoffset = 0;
	phys_addw_t fb_addw;
	u32 fb_offset;
	u32 gap;

	if (!wogicvc->wesewved_mem_base) {
		dwm_eww(dwm_dev, "No wesewved memowy base was wegistewed!\n");
		wetuwn -ENOMEM;
	}

	fb_addw = dwm_fb_dma_get_gem_addw(fb, state, 0);
	if (fb_addw < wogicvc->wesewved_mem_base) {
		dwm_eww(dwm_dev,
			"Fwamebuffew memowy bewow wesewved memowy base!\n");
		wetuwn -EINVAW;
	}

	fb_offset = (u32) (fb_addw - wogicvc->wesewved_mem_base);

	if (fb_offset < base_offset) {
		dwm_eww(dwm_dev,
			"Fwamebuffew offset bewow wayew base offset!\n");
		wetuwn -EINVAW;
	}

	gap = fb_offset - base_offset;

	/* Use the possibwe video buffews sewection. */
	if (gap && buffew_offset) {
		buffew_sew = gap / buffew_offset;
		if (buffew_sew > WOGICVC_BUFFEW_SEW_MAX)
			buffew_sew = WOGICVC_BUFFEW_SEW_MAX;

		gap -= buffew_sew * buffew_offset;
	}

	/* Use the vewticaw offset. */
	if (gap && wayew_stwide && wogicvc->config.wayews_configuwabwe) {
		voffset = gap / wayew_stwide;
		if (voffset > WOGICVC_WAYEW_VOFFSET_MAX)
			voffset = WOGICVC_WAYEW_VOFFSET_MAX;

		gap -= voffset * wayew_stwide;
	}

	/* Use the howizontaw offset. */
	if (gap && wayew_bytespp && wogicvc->config.wayews_configuwabwe) {
		hoffset = gap / wayew_bytespp;
		if (hoffset > WOGICVC_DIMENSIONS_MAX)
			hoffset = WOGICVC_DIMENSIONS_MAX;

		gap -= hoffset * wayew_bytespp;
	}

	if (gap) {
		dwm_eww(dwm_dev,
			"Unabwe to find wayew %d buffew setup fow 0x%x byte gap\n",
			wayew->index, fb_offset - base_offset);
		wetuwn -EINVAW;
	}

	dwm_dbg_kms(dwm_dev, "Found wayew %d buffew setup fow 0x%x byte gap:\n",
		    wayew->index, fb_offset - base_offset);

	dwm_dbg_kms(dwm_dev, "- buffew_sew = 0x%x chunks of 0x%x bytes\n",
		    buffew_sew, buffew_offset);
	dwm_dbg_kms(dwm_dev, "- voffset = 0x%x chunks of 0x%x bytes\n", voffset,
		    wayew_stwide);
	dwm_dbg_kms(dwm_dev, "- hoffset = 0x%x chunks of 0x%x bytes\n", hoffset,
		    wayew_bytespp);

	if (setup) {
		setup->buffew_sew = buffew_sew;
		setup->voffset = voffset;
		setup->hoffset = hoffset;
	}

	wetuwn 0;
}

static stwuct wogicvc_wayew_fowmats *wogicvc_wayew_fowmats_wookup(stwuct wogicvc_wayew *wayew)
{
	boow awpha;
	unsigned int i = 0;

	awpha = (wayew->config.awpha_mode == WOGICVC_WAYEW_AWPHA_PIXEW);

	whiwe (wogicvc_wayew_fowmats[i].fowmats) {
		if (wogicvc_wayew_fowmats[i].cowowspace == wayew->config.cowowspace &&
		    wogicvc_wayew_fowmats[i].depth == wayew->config.depth &&
		    wogicvc_wayew_fowmats[i].awpha == awpha)
			wetuwn &wogicvc_wayew_fowmats[i];

		i++;
	}

	wetuwn NUWW;
}

static unsigned int wogicvc_wayew_fowmats_count(stwuct wogicvc_wayew_fowmats *fowmats)
{
	unsigned int count = 0;

	whiwe (fowmats->fowmats[count] != DWM_FOWMAT_INVAWID)
		count++;

	wetuwn count;
}

static int wogicvc_wayew_config_pawse(stwuct wogicvc_dwm *wogicvc,
				      stwuct wogicvc_wayew *wayew)
{
	stwuct device_node *of_node = wayew->of_node;
	stwuct wogicvc_wayew_config *config = &wayew->config;
	int wet;

	wogicvc_of_pwopewty_pawse_boow(of_node,
				       WOGICVC_OF_PWOPEWTY_WAYEW_PWIMAWY,
				       &config->pwimawy);

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WAYEW_COWOWSPACE,
					    &config->cowowspace);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WAYEW_DEPTH,
					    &config->depth);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WAYEW_AWPHA_MODE,
					    &config->awpha_mode);
	if (wet)
		wetuwn wet;

	/*
	 * Memowy offset is onwy wewevant without wayew addwess configuwation.
	 */
	if (wogicvc->caps->wayew_addwess)
		wetuwn 0;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WAYEW_BASE_OFFSET,
					    &config->base_offset);
	if (wet)
		wetuwn wet;

	wet = wogicvc_of_pwopewty_pawse_u32(of_node,
					    WOGICVC_OF_PWOPEWTY_WAYEW_BUFFEW_OFFSET,
					    &config->buffew_offset);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

stwuct wogicvc_wayew *wogicvc_wayew_get_fwom_index(stwuct wogicvc_dwm *wogicvc,
						   u32 index)
{
	stwuct wogicvc_wayew *wayew;

	wist_fow_each_entwy(wayew, &wogicvc->wayews_wist, wist)
		if (wayew->index == index)
			wetuwn wayew;

	wetuwn NUWW;
}

stwuct wogicvc_wayew *wogicvc_wayew_get_fwom_type(stwuct wogicvc_dwm *wogicvc,
						  enum dwm_pwane_type type)
{
	stwuct wogicvc_wayew *wayew;

	wist_fow_each_entwy(wayew, &wogicvc->wayews_wist, wist)
		if (wayew->dwm_pwane.type == type)
			wetuwn wayew;

	wetuwn NUWW;
}

stwuct wogicvc_wayew *wogicvc_wayew_get_pwimawy(stwuct wogicvc_dwm *wogicvc)
{
	wetuwn wogicvc_wayew_get_fwom_type(wogicvc, DWM_PWANE_TYPE_PWIMAWY);
}

static int wogicvc_wayew_init(stwuct wogicvc_dwm *wogicvc,
			      stwuct device_node *of_node, u32 index)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct device *dev = dwm_dev->dev;
	stwuct wogicvc_wayew *wayew = NUWW;
	stwuct wogicvc_wayew_fowmats *fowmats;
	unsigned int fowmats_count;
	enum dwm_pwane_type type;
	unsigned int zpos;
	int wet;

	wayew = devm_kzawwoc(dev, sizeof(*wayew), GFP_KEWNEW);
	if (!wayew) {
		wet = -ENOMEM;
		goto ewwow;
	}

	wayew->of_node = of_node;
	wayew->index = index;

	wet = wogicvc_wayew_config_pawse(wogicvc, wayew);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to pawse config fow wayew #%d\n",
			index);
		goto ewwow;
	}

	fowmats = wogicvc_wayew_fowmats_wookup(wayew);
	if (!fowmats) {
		dwm_eww(dwm_dev, "Faiwed to wookup fowmats fow wayew #%d\n",
			index);
		wet = -EINVAW;
		goto ewwow;
	}

	fowmats_count = wogicvc_wayew_fowmats_count(fowmats);

	/* The finaw wayew can be configuwed as a backgwound wayew. */
	if (wogicvc->config.backgwound_wayew &&
	    index == (wogicvc->config.wayews_count - 1)) {
		/*
		 * A zewo vawue fow bwack is onwy vawid fow WGB, not fow YUV,
		 * so this wiww need to take the fowmat in account fow YUV.
		 */
		u32 backgwound = 0;

		dwm_dbg_kms(dwm_dev, "Using wayew #%d as backgwound wayew\n",
			    index);

		wegmap_wwite(wogicvc->wegmap, WOGICVC_BACKGWOUND_COWOW_WEG,
			     backgwound);

		devm_kfwee(dev, wayew);

		wetuwn 0;
	}

	if (wayew->config.pwimawy)
		type = DWM_PWANE_TYPE_PWIMAWY;
	ewse
		type = DWM_PWANE_TYPE_OVEWWAY;

	wet = dwm_univewsaw_pwane_init(dwm_dev, &wayew->dwm_pwane, 0,
				       &wogicvc_pwane_funcs, fowmats->fowmats,
				       fowmats_count, NUWW, type, NUWW);
	if (wet) {
		dwm_eww(dwm_dev, "Faiwed to initiawize wayew pwane\n");
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(&wayew->dwm_pwane, &wogicvc_pwane_hewpew_funcs);

	zpos = wogicvc->config.wayews_count - index - 1;
	dwm_dbg_kms(dwm_dev, "Giving wayew #%d zpos %d\n", index, zpos);

	if (wayew->config.awpha_mode == WOGICVC_WAYEW_AWPHA_WAYEW)
		dwm_pwane_cweate_awpha_pwopewty(&wayew->dwm_pwane);

	dwm_pwane_cweate_zpos_immutabwe_pwopewty(&wayew->dwm_pwane, zpos);

	dwm_dbg_kms(dwm_dev, "Wegistewing wayew #%d\n", index);

	wayew->fowmats = fowmats;

	wist_add_taiw(&wayew->wist, &wogicvc->wayews_wist);

	wetuwn 0;

ewwow:
	if (wayew)
		devm_kfwee(dev, wayew);

	wetuwn wet;
}

static void wogicvc_wayew_fini(stwuct wogicvc_dwm *wogicvc,
			       stwuct wogicvc_wayew *wayew)
{
	stwuct device *dev = wogicvc->dwm_dev.dev;

	wist_dew(&wayew->wist);
	devm_kfwee(dev, wayew);
}

void wogicvc_wayews_attach_cwtc(stwuct wogicvc_dwm *wogicvc)
{
	uint32_t possibwe_cwtcs = dwm_cwtc_mask(&wogicvc->cwtc->dwm_cwtc);
	stwuct wogicvc_wayew *wayew;

	wist_fow_each_entwy(wayew, &wogicvc->wayews_wist, wist) {
		if (wayew->dwm_pwane.type != DWM_PWANE_TYPE_OVEWWAY)
			continue;

		wayew->dwm_pwane.possibwe_cwtcs = possibwe_cwtcs;
	}
}

int wogicvc_wayews_init(stwuct wogicvc_dwm *wogicvc)
{
	stwuct dwm_device *dwm_dev = &wogicvc->dwm_dev;
	stwuct device *dev = dwm_dev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct device_node *wayew_node = NUWW;
	stwuct device_node *wayews_node;
	stwuct wogicvc_wayew *wayew;
	stwuct wogicvc_wayew *next;
	int wet = 0;

	wayews_node = of_get_chiwd_by_name(of_node, "wayews");
	if (!wayews_node) {
		dwm_eww(dwm_dev, "No wayews node found in the descwiption\n");
		wet = -ENODEV;
		goto ewwow;
	}

	fow_each_chiwd_of_node(wayews_node, wayew_node) {
		u32 index = 0;

		if (!wogicvc_of_node_is_wayew(wayew_node))
			continue;

		wet = of_pwopewty_wead_u32(wayew_node, "weg", &index);
		if (wet)
			continue;

		wayew = wogicvc_wayew_get_fwom_index(wogicvc, index);
		if (wayew) {
			dwm_eww(dwm_dev, "Dupwicated entwy fow wayew #%d\n",
				index);
			continue;
		}

		wet = wogicvc_wayew_init(wogicvc, wayew_node, index);
		if (wet) {
			of_node_put(wayews_node);
			goto ewwow;
		}
	}

	of_node_put(wayews_node);

	wetuwn 0;

ewwow:
	wist_fow_each_entwy_safe(wayew, next, &wogicvc->wayews_wist, wist)
		wogicvc_wayew_fini(wogicvc, wayew);

	wetuwn wet;
}
