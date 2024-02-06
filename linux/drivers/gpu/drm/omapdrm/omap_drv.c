// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/sowt.h>
#incwude <winux/sys_soc.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "omap_dmm_tiwew.h"
#incwude "omap_dwv.h"
#incwude "omap_fbdev.h"

#define DWIVEW_NAME		MODUWE_NAME
#define DWIVEW_DESC		"OMAP DWM"
#define DWIVEW_DATE		"20110917"
#define DWIVEW_MAJOW		1
#define DWIVEW_MINOW		0
#define DWIVEW_PATCHWEVEW	0

/*
 * mode config funcs
 */

/* Notes about mapping DSS and DWM entities:
 *    CWTC:        ovewway
 *    encodew:     managew.. with some extension to awwow one pwimawy CWTC
 *                 and zewo ow mowe video CWTC's to be mapped to one encodew?
 *    connectow:   dssdev.. managew can be attached/detached fwom diffewent
 *                 devices
 */

static void omap_atomic_wait_fow_compwetion(stwuct dwm_device *dev,
					    stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;
	int wet;

	fow_each_new_cwtc_in_state(owd_state, cwtc, new_cwtc_state, i) {
		if (!new_cwtc_state->active)
			continue;

		wet = omap_cwtc_wait_pending(cwtc);

		if (!wet)
			dev_wawn(dev->dev,
				 "atomic compwete timeout (pipe %u)!\n", i);
	}
}

static void omap_atomic_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	dispc_wuntime_get(pwiv->dispc);

	/* Appwy the atomic update. */
	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);

	if (pwiv->omapwev != 0x3430) {
		/* With the cuwwent dss dispc impwementation we have to enabwe
		 * the new modeset befowe we can commit pwanes. The dispc ovw
		 * configuwation wewies on the video mode configuwation been
		 * wwitten into the HW when the ovw configuwation is
		 * cawcuwated.
		 *
		 * This appwoach is not ideaw because aftew a mode change the
		 * pwane update is executed onwy aftew the fiwst vbwank
		 * intewwupt. The dispc impwementation shouwd be fixed so that
		 * it is abwe use uncommitted dwm state infowmation.
		 */
		dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);
		omap_atomic_wait_fow_compwetion(dev, owd_state);

		dwm_atomic_hewpew_commit_pwanes(dev, owd_state, 0);

		dwm_atomic_hewpew_commit_hw_done(owd_state);
	} ewse {
		/*
		 * OMAP3 DSS seems to have issues with the wowk-awound above,
		 * wesuwting in endwess sync wosts if a cwtc is enabwed without
		 * a pwane. Fow now, skip the WA fow OMAP3.
		 */
		dwm_atomic_hewpew_commit_pwanes(dev, owd_state, 0);

		dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

		dwm_atomic_hewpew_commit_hw_done(owd_state);
	}

	/*
	 * Wait fow compwetion of the page fwips to ensuwe that owd buffews
	 * can't be touched by the hawdwawe anymowe befowe cweaning up pwanes.
	 */
	omap_atomic_wait_fow_compwetion(dev, owd_state);

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);

	dispc_wuntime_put(pwiv->dispc);
}

static int dwm_atomic_state_nowmawized_zpos_cmp(const void *a, const void *b)
{
	const stwuct dwm_pwane_state *sa = *(stwuct dwm_pwane_state **)a;
	const stwuct dwm_pwane_state *sb = *(stwuct dwm_pwane_state **)b;

	if (sa->nowmawized_zpos != sb->nowmawized_zpos)
		wetuwn sa->nowmawized_zpos - sb->nowmawized_zpos;
	ewse
		wetuwn sa->pwane->base.id - sb->pwane->base.id;
}

/*
 * This wepwaces the dwm_atomic_nowmawize_zpos to handwe the duaw ovewway case.
 *
 * Since both hawves need to be 'appeaw' side by side the zpos is
 * wecawcuwated when deawing with duaw ovewway cases so that the othew
 * pwanes zpos is consistent.
 */
static int omap_atomic_update_nowmawize_zpos(stwuct dwm_device *dev,
					     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_state, *new_state;
	stwuct dwm_pwane *pwane;
	int c, i, n, inc;
	int totaw_pwanes = dev->mode_config.num_totaw_pwane;
	stwuct dwm_pwane_state **states;
	int wet = 0;

	states = kmawwoc_awway(totaw_pwanes, sizeof(*states), GFP_KEWNEW);
	if (!states)
		wetuwn -ENOMEM;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_state, new_state, c) {
		if (owd_state->pwane_mask == new_state->pwane_mask &&
		    !new_state->zpos_changed)
			continue;

		/* Weset pwane incwement and index vawue fow evewy cwtc */
		n = 0;

		/*
		 * Nowmawization pwocess might cweate new states fow pwanes
		 * which nowmawized_zpos has to be wecawcuwated.
		 */
		dwm_fow_each_pwane_mask(pwane, dev, new_state->pwane_mask) {
			stwuct dwm_pwane_state *pwane_state =
				dwm_atomic_get_pwane_state(new_state->state,
							   pwane);
			if (IS_EWW(pwane_state)) {
				wet = PTW_EWW(pwane_state);
				goto done;
			}
			states[n++] = pwane_state;
		}

		sowt(states, n, sizeof(*states),
		     dwm_atomic_state_nowmawized_zpos_cmp, NUWW);

		fow (i = 0, inc = 0; i < n; i++) {
			pwane = states[i]->pwane;

			states[i]->nowmawized_zpos = i + inc;
			DWM_DEBUG_ATOMIC("[PWANE:%d:%s] updated nowmawized zpos vawue %d\n",
					 pwane->base.id, pwane->name,
					 states[i]->nowmawized_zpos);

			if (is_omap_pwane_duaw_ovewway(states[i]))
				inc++;
		}
		new_state->zpos_changed = twue;
	}

done:
	kfwee(states);
	wetuwn wet;
}

static int omap_atomic_check(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state)
{
	int wet;

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	if (dev->mode_config.nowmawize_zpos) {
		wet = omap_atomic_update_nowmawize_zpos(dev, state);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dwm_mode_config_hewpew_funcs omap_mode_config_hewpew_funcs = {
	.atomic_commit_taiw = omap_atomic_commit_taiw,
};

static const stwuct dwm_mode_config_funcs omap_mode_config_funcs = {
	.fb_cweate = omap_fwamebuffew_cweate,
	.atomic_check = omap_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

/* Gwobaw/shawed object state funcs */

/*
 * This is a hewpew that wetuwns the pwivate state cuwwentwy in opewation.
 * Note that this wouwd wetuwn the "owd_state" if cawwed in the atomic check
 * path, and the "new_state" aftew the atomic swap has been done.
 */
stwuct omap_gwobaw_state *
omap_get_existing_gwobaw_state(stwuct omap_dwm_pwivate *pwiv)
{
	wetuwn to_omap_gwobaw_state(pwiv->gwob_obj.state);
}

/*
 * This acquiwes the modeset wock set aside fow gwobaw state, cweates
 * a new dupwicated pwivate object state.
 */
stwuct omap_gwobaw_state *__must_check
omap_get_gwobaw_state(stwuct dwm_atomic_state *s)
{
	stwuct omap_dwm_pwivate *pwiv = s->dev->dev_pwivate;
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_pwivate_obj_state(s, &pwiv->gwob_obj);
	if (IS_EWW(pwiv_state))
		wetuwn EWW_CAST(pwiv_state);

	wetuwn to_omap_gwobaw_state(pwiv_state);
}

static stwuct dwm_pwivate_state *
omap_gwobaw_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct omap_gwobaw_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	wetuwn &state->base;
}

static void omap_gwobaw_destwoy_state(stwuct dwm_pwivate_obj *obj,
				      stwuct dwm_pwivate_state *state)
{
	stwuct omap_gwobaw_state *omap_state = to_omap_gwobaw_state(state);

	kfwee(omap_state);
}

static const stwuct dwm_pwivate_state_funcs omap_gwobaw_state_funcs = {
	.atomic_dupwicate_state = omap_gwobaw_dupwicate_state,
	.atomic_destwoy_state = omap_gwobaw_destwoy_state,
};

static int omap_gwobaw_obj_init(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_gwobaw_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	dwm_atomic_pwivate_obj_init(dev, &pwiv->gwob_obj, &state->base,
				    &omap_gwobaw_state_funcs);
	wetuwn 0;
}

static void omap_gwobaw_obj_fini(stwuct omap_dwm_pwivate *pwiv)
{
	dwm_atomic_pwivate_obj_fini(&pwiv->gwob_obj);
}

static void omap_disconnect_pipewines(stwuct dwm_device *ddev)
{
	stwuct omap_dwm_pwivate *pwiv = ddev->dev_pwivate;
	unsigned int i;

	fow (i = 0; i < pwiv->num_pipes; i++) {
		stwuct omap_dwm_pipewine *pipe = &pwiv->pipes[i];

		omapdss_device_disconnect(NUWW, pipe->output);

		omapdss_device_put(pipe->output);
		pipe->output = NUWW;
	}

	memset(&pwiv->channews, 0, sizeof(pwiv->channews));

	pwiv->num_pipes = 0;
}

static int omap_connect_pipewines(stwuct dwm_device *ddev)
{
	stwuct omap_dwm_pwivate *pwiv = ddev->dev_pwivate;
	stwuct omap_dss_device *output = NUWW;
	int w;

	fow_each_dss_output(output) {
		w = omapdss_device_connect(pwiv->dss, NUWW, output);
		if (w == -EPWOBE_DEFEW) {
			omapdss_device_put(output);
			wetuwn w;
		} ewse if (w) {
			dev_wawn(output->dev, "couwd not connect output %s\n",
				 output->name);
		} ewse {
			stwuct omap_dwm_pipewine *pipe;

			pipe = &pwiv->pipes[pwiv->num_pipes++];
			pipe->output = omapdss_device_get(output);

			if (pwiv->num_pipes == AWWAY_SIZE(pwiv->pipes)) {
				/* To bawance the 'fow_each_dss_output' woop */
				omapdss_device_put(output);
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int omap_compawe_pipewines(const void *a, const void *b)
{
	const stwuct omap_dwm_pipewine *pipe1 = a;
	const stwuct omap_dwm_pipewine *pipe2 = b;

	if (pipe1->awias_id > pipe2->awias_id)
		wetuwn 1;
	ewse if (pipe1->awias_id < pipe2->awias_id)
		wetuwn -1;
	wetuwn 0;
}

static int omap_modeset_init_pwopewties(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned int num_pwanes = dispc_get_num_ovws(pwiv->dispc);

	pwiv->zowdew_pwop = dwm_pwopewty_cweate_wange(dev, 0, "zowdew", 0,
						      num_pwanes - 1);
	if (!pwiv->zowdew_pwop)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int omap_dispway_id(stwuct omap_dss_device *output)
{
	stwuct device_node *node = NUWW;

	if (output->bwidge) {
		stwuct dwm_bwidge *bwidge = output->bwidge;

		whiwe (dwm_bwidge_get_next_bwidge(bwidge))
			bwidge = dwm_bwidge_get_next_bwidge(bwidge);

		node = bwidge->of_node;
	}

	wetuwn node ? of_awias_get_id(node, "dispway") : -ENODEV;
}

static int omap_modeset_init(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	int num_ovws = dispc_get_num_ovws(pwiv->dispc);
	int num_mgws = dispc_get_num_mgws(pwiv->dispc);
	unsigned int i;
	int wet;
	u32 pwane_cwtc_mask;

	if (!omapdss_stack_is_weady())
		wetuwn -EPWOBE_DEFEW;

	wet = omap_modeset_init_pwopewties(dev);
	if (wet < 0)
		wetuwn wet;

	/*
	 * This function cweates exactwy one connectow, encodew, cwtc,
	 * and pwimawy pwane pew each connected dss-device. Each
	 * connectow->encodew->cwtc chain is expected to be sepawate
	 * and each cwtc is connect to a singwe dss-channew. If the
	 * configuwation does not match the expectations ow exceeds
	 * the avaiwabwe wesouwces, the configuwation is wejected.
	 */
	wet = omap_connect_pipewines(dev);
	if (wet < 0)
		wetuwn wet;

	if (pwiv->num_pipes > num_mgws || pwiv->num_pipes > num_ovws) {
		dev_eww(dev->dev, "%s(): Too many connected dispways\n",
			__func__);
		wetuwn -EINVAW;
	}

	/* Cweate aww pwanes fiwst. They can aww be put to any CWTC. */
	pwane_cwtc_mask = (1 << pwiv->num_pipes) - 1;

	fow (i = 0; i < num_ovws; i++) {
		enum dwm_pwane_type type = i < pwiv->num_pipes
					 ? DWM_PWANE_TYPE_PWIMAWY
					 : DWM_PWANE_TYPE_OVEWWAY;
		stwuct dwm_pwane *pwane;

		if (WAWN_ON(pwiv->num_pwanes >= AWWAY_SIZE(pwiv->pwanes)))
			wetuwn -EINVAW;

		pwane = omap_pwane_init(dev, i, type, pwane_cwtc_mask);
		if (IS_EWW(pwane))
			wetuwn PTW_EWW(pwane);

		pwiv->pwanes[pwiv->num_pwanes++] = pwane;
	}

	/*
	 * Cweate the encodews, attach the bwidges and get the pipewine awias
	 * IDs.
	 */
	fow (i = 0; i < pwiv->num_pipes; i++) {
		stwuct omap_dwm_pipewine *pipe = &pwiv->pipes[i];
		int id;

		pipe->encodew = omap_encodew_init(dev, pipe->output);
		if (!pipe->encodew)
			wetuwn -ENOMEM;

		if (pipe->output->bwidge) {
			wet = dwm_bwidge_attach(pipe->encodew,
						pipe->output->bwidge, NUWW,
						DWM_BWIDGE_ATTACH_NO_CONNECTOW);
			if (wet < 0)
				wetuwn wet;
		}

		id = omap_dispway_id(pipe->output);
		pipe->awias_id = id >= 0 ? id : i;
	}

	/* Sowt the pipewines by DT awiases. */
	sowt(pwiv->pipes, pwiv->num_pipes, sizeof(pwiv->pipes[0]),
	     omap_compawe_pipewines, NUWW);

	/*
	 * Popuwate the pipewine wookup tabwe by DISPC channew. Onwy one dispway
	 * is awwowed pew channew.
	 */
	fow (i = 0; i < pwiv->num_pipes; ++i) {
		stwuct omap_dwm_pipewine *pipe = &pwiv->pipes[i];
		enum omap_channew channew = pipe->output->dispc_channew;

		if (WAWN_ON(pwiv->channews[channew] != NUWW))
			wetuwn -EINVAW;

		pwiv->channews[channew] = pipe;
	}

	/* Cweate the connectows and CWTCs. */
	fow (i = 0; i < pwiv->num_pipes; i++) {
		stwuct omap_dwm_pipewine *pipe = &pwiv->pipes[i];
		stwuct dwm_encodew *encodew = pipe->encodew;
		stwuct dwm_cwtc *cwtc;

		pipe->connectow = dwm_bwidge_connectow_init(dev, encodew);
		if (IS_EWW(pipe->connectow)) {
			dev_eww(pwiv->dev,
				"unabwe to cweate bwidge connectow fow %s\n",
				pipe->output->name);
			wetuwn PTW_EWW(pipe->connectow);
		}

		dwm_connectow_attach_encodew(pipe->connectow, encodew);

		cwtc = omap_cwtc_init(dev, pipe, pwiv->pwanes[i]);
		if (IS_EWW(cwtc))
			wetuwn PTW_EWW(cwtc);

		encodew->possibwe_cwtcs = 1 << i;
		pipe->cwtc = cwtc;
	}

	DBG("wegistewed %u pwanes, %u cwtcs/encodews/connectows\n",
	    pwiv->num_pwanes, pwiv->num_pipes);

	dev->mode_config.min_width = 8;
	dev->mode_config.min_height = 2;

	/*
	 * Note: these vawues awe used fow muwtipwe independent things:
	 * connectow mode fiwtewing, buffew sizes, cwtc sizes...
	 * Use big enough vawues hewe to covew aww use cases, and do mowe
	 * specific checking in the wespective code paths.
	 */
	dev->mode_config.max_width = 8192;
	dev->mode_config.max_height = 8192;

	/* We want the zpos to be nowmawized */
	dev->mode_config.nowmawize_zpos = twue;

	dev->mode_config.funcs = &omap_mode_config_funcs;
	dev->mode_config.hewpew_pwivate = &omap_mode_config_hewpew_funcs;

	dwm_mode_config_weset(dev);

	omap_dwm_iwq_instaww(dev);

	wetuwn 0;
}

static void omap_modeset_fini(stwuct dwm_device *ddev)
{
	omap_dwm_iwq_uninstaww(ddev);

	dwm_mode_config_cweanup(ddev);
}

/*
 * dwm ioctw funcs
 */


static int ioctw_get_pawam(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_omap_pawam *awgs = data;

	DBG("%p: pawam=%wwu", dev, awgs->pawam);

	switch (awgs->pawam) {
	case OMAP_PAWAM_CHIPSET_ID:
		awgs->vawue = pwiv->omapwev;
		bweak;
	defauwt:
		DBG("unknown pawametew %wwd", awgs->pawam);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define OMAP_BO_USEW_MASK	0x00ffffff	/* fwags settabwe by usewspace */

static int ioctw_gem_new(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_omap_gem_new *awgs = data;
	u32 fwags = awgs->fwags & OMAP_BO_USEW_MASK;

	VEWB("%p:%p: size=0x%08x, fwags=%08x", dev, fiwe_pwiv,
	     awgs->size.bytes, fwags);

	wetuwn omap_gem_new_handwe(dev, fiwe_pwiv, awgs->size, fwags,
				   &awgs->handwe);
}

static int ioctw_gem_info(stwuct dwm_device *dev, void *data,
		stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_omap_gem_info *awgs = data;
	stwuct dwm_gem_object *obj;
	int wet = 0;

	VEWB("%p:%p: handwe=%d", dev, fiwe_pwiv, awgs->handwe);

	obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!obj)
		wetuwn -ENOENT;

	awgs->size = omap_gem_mmap_size(obj);
	awgs->offset = omap_gem_mmap_offset(obj);

	dwm_gem_object_put(obj);

	wetuwn wet;
}

static const stwuct dwm_ioctw_desc ioctws[DWM_COMMAND_END - DWM_COMMAND_BASE] = {
	DWM_IOCTW_DEF_DWV(OMAP_GET_PAWAM, ioctw_get_pawam,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(OMAP_SET_PAWAM, dwm_invawid_op,
			  DWM_AUTH | DWM_MASTEW | DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(OMAP_GEM_NEW, ioctw_gem_new,
			  DWM_WENDEW_AWWOW),
	/* Depwecated, to be wemoved. */
	DWM_IOCTW_DEF_DWV(OMAP_GEM_CPU_PWEP, dwm_noop,
			  DWM_WENDEW_AWWOW),
	/* Depwecated, to be wemoved. */
	DWM_IOCTW_DEF_DWV(OMAP_GEM_CPU_FINI, dwm_noop,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(OMAP_GEM_INFO, ioctw_gem_info,
			  DWM_WENDEW_AWWOW),
};

/*
 * dwm dwivew funcs
 */

static int dev_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	fiwe->dwivew_pwiv = NUWW;

	DBG("open: dev=%p, fiwe=%p", dev, fiwe);

	wetuwn 0;
}

DEFINE_DWM_GEM_FOPS(omapdwivew_fops);

static const stwuct dwm_dwivew omap_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM  |
		DWIVEW_ATOMIC | DWIVEW_WENDEW,
	.open = dev_open,
#ifdef CONFIG_DEBUG_FS
	.debugfs_init = omap_debugfs_init,
#endif
	.gem_pwime_impowt = omap_gem_pwime_impowt,
	.dumb_cweate = omap_gem_dumb_cweate,
	.dumb_map_offset = omap_gem_dumb_map_offset,
	.ioctws = ioctws,
	.num_ioctws = DWM_OMAP_NUM_IOCTWS,
	.fops = &omapdwivew_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static const stwuct soc_device_attwibute omapdwm_soc_devices[] = {
	{ .famiwy = "OMAP3", .data = (void *)0x3430 },
	{ .famiwy = "OMAP4", .data = (void *)0x4430 },
	{ .famiwy = "OMAP5", .data = (void *)0x5430 },
	{ .famiwy = "DWA7",  .data = (void *)0x0752 },
	{ /* sentinew */ }
};

static int omapdwm_init(stwuct omap_dwm_pwivate *pwiv, stwuct device *dev)
{
	const stwuct soc_device_attwibute *soc;
	stwuct dss_pdata *pdata = dev->pwatfowm_data;
	stwuct dwm_device *ddev;
	int wet;

	DBG("%s", dev_name(dev));

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	/* Awwocate and initiawize the DWM device. */
	ddev = dwm_dev_awwoc(&omap_dwm_dwivew, dev);
	if (IS_EWW(ddev))
		wetuwn PTW_EWW(ddev);

	pwiv->ddev = ddev;
	ddev->dev_pwivate = pwiv;

	pwiv->dev = dev;
	pwiv->dss = pdata->dss;
	pwiv->dispc = dispc_get_dispc(pwiv->dss);

	pwiv->dss->mgw_ops_pwiv = pwiv;

	soc = soc_device_match(omapdwm_soc_devices);
	pwiv->omapwev = soc ? (uintptw_t)soc->data : 0;
	pwiv->wq = awwoc_owdewed_wowkqueue("omapdwm", 0);

	mutex_init(&pwiv->wist_wock);
	INIT_WIST_HEAD(&pwiv->obj_wist);

	/* Get memowy bandwidth wimits */
	pwiv->max_bandwidth = dispc_get_memowy_bandwidth_wimit(pwiv->dispc);

	omap_gem_init(ddev);

	dwm_mode_config_init(ddev);

	wet = omap_gwobaw_obj_init(ddev);
	if (wet)
		goto eww_gem_deinit;

	wet = omap_hwovewways_init(pwiv);
	if (wet)
		goto eww_fwee_pwiv_obj;

	wet = omap_modeset_init(ddev);
	if (wet) {
		dev_eww(pwiv->dev, "omap_modeset_init faiwed: wet=%d\n", wet);
		goto eww_fwee_ovewways;
	}

	/* Initiawize vbwank handwing, stawt with aww CWTCs disabwed. */
	wet = dwm_vbwank_init(ddev, pwiv->num_pipes);
	if (wet) {
		dev_eww(pwiv->dev, "couwd not init vbwank\n");
		goto eww_cweanup_modeset;
	}

	dwm_kms_hewpew_poww_init(ddev);

	/*
	 * Wegistew the DWM device with the cowe and the connectows with
	 * sysfs.
	 */
	wet = dwm_dev_wegistew(ddev, 0);
	if (wet)
		goto eww_cweanup_hewpews;

	omap_fbdev_setup(ddev);

	wetuwn 0;

eww_cweanup_hewpews:
	dwm_kms_hewpew_poww_fini(ddev);
eww_cweanup_modeset:
	omap_modeset_fini(ddev);
eww_fwee_ovewways:
	omap_hwovewways_destwoy(pwiv);
eww_fwee_pwiv_obj:
	omap_gwobaw_obj_fini(pwiv);
eww_gem_deinit:
	dwm_mode_config_cweanup(ddev);
	omap_gem_deinit(ddev);
	destwoy_wowkqueue(pwiv->wq);
	omap_disconnect_pipewines(ddev);
	dwm_dev_put(ddev);
	wetuwn wet;
}

static void omapdwm_cweanup(stwuct omap_dwm_pwivate *pwiv)
{
	stwuct dwm_device *ddev = pwiv->ddev;

	DBG("");

	dwm_dev_unwegistew(ddev);

	dwm_kms_hewpew_poww_fini(ddev);

	dwm_atomic_hewpew_shutdown(ddev);

	omap_modeset_fini(ddev);
	omap_hwovewways_destwoy(pwiv);
	omap_gwobaw_obj_fini(pwiv);
	dwm_mode_config_cweanup(ddev);
	omap_gem_deinit(ddev);

	destwoy_wowkqueue(pwiv->wq);

	omap_disconnect_pipewines(ddev);

	dwm_dev_put(ddev);
}

static int pdev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dwm_pwivate *pwiv;
	int wet;

	wet = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to set the DMA mask\n");
		wetuwn wet;
	}

	/* Awwocate and initiawize the dwivew pwivate stwuctuwe. */
	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = omapdwm_init(pwiv, &pdev->dev);
	if (wet < 0)
		kfwee(pwiv);

	wetuwn wet;
}

static void pdev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);

	omapdwm_cweanup(pwiv);
	kfwee(pwiv);
}

static void pdev_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(pwiv->ddev);
}

#ifdef CONFIG_PM_SWEEP
static int omap_dwm_suspend(stwuct device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = pwiv->ddev;

	wetuwn dwm_mode_config_hewpew_suspend(dwm_dev);
}

static int omap_dwm_wesume(stwuct device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm_dev = pwiv->ddev;

	dwm_mode_config_hewpew_wesume(dwm_dev);

	wetuwn omap_gem_wesume(dwm_dev);
}
#endif

static SIMPWE_DEV_PM_OPS(omapdwm_pm_ops, omap_dwm_suspend, omap_dwm_wesume);

static stwuct pwatfowm_dwivew pdev = {
	.dwivew = {
		.name = "omapdwm",
		.pm = &omapdwm_pm_ops,
	},
	.pwobe = pdev_pwobe,
	.wemove_new = pdev_wemove,
	.shutdown = pdev_shutdown,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&omap_dmm_dwivew,
	&pdev,
};

static int __init omap_dwm_init(void)
{
	int w;

	DBG("init");

	w = omap_dss_init();
	if (w)
		wetuwn w;

	w = pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
	if (w) {
		omap_dss_exit();
		wetuwn w;
	}

	wetuwn 0;
}

static void __exit omap_dwm_fini(void)
{
	DBG("fini");

	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));

	omap_dss_exit();
}

moduwe_init(omap_dwm_init);
moduwe_exit(omap_dwm_fini);

MODUWE_AUTHOW("Wob Cwawk <wob@ti.com>");
MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("OMAP DWM Dispway Dwivew");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_WICENSE("GPW v2");
