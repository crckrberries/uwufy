/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2017 Icenowy Zheng <icenowy@aosc.io>
 */

#ifndef _SUNXI_ENGINE_H_
#define _SUNXI_ENGINE_H_

stwuct dwm_pwane;
stwuct dwm_device;
stwuct dwm_cwtc_state;
stwuct dwm_dispway_mode;

stwuct sunxi_engine;

/**
 * stwuct sunxi_engine_ops - hewpew opewations fow sunXi engines
 *
 * These hooks awe used by the common pawt of the DWM dwivew to
 * impwement the pwopew behaviouw.
 */
stwuct sunxi_engine_ops {
	/**
	 * @atomic_begin:
	 *
	 * This cawwback awwows to pwepawe ouw engine fow an atomic
	 * update. This is miwwowing the
	 * &dwm_cwtc_hewpew_funcs.atomic_begin cawwback, so any
	 * documentation thewe appwies.
	 *
	 * This function is optionaw.
	 */
	void (*atomic_begin)(stwuct sunxi_engine *engine,
			     stwuct dwm_cwtc_state *owd_state);

	/**
	 * @atomic_check:
	 *
	 * This cawwback awwows to vawidate pwane-update wewated CWTC
	 * constwaints specific to engines. This is miwwowing the
	 * &dwm_cwtc_hewpew_funcs.atomic_check cawwback, so any
	 * documentation thewe appwies.
	 *
	 * This function is optionaw.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code.
	 */
	int (*atomic_check)(stwuct sunxi_engine *engine,
			    stwuct dwm_cwtc_state *state);

	/**
	 * @commit:
	 *
	 * This cawwback wiww twiggew the hawdwawe switch to commit
	 * the new configuwation that has been setup duwing the next
	 * vbwank pewiod.
	 *
	 * This function is optionaw.
	 */
	void (*commit)(stwuct sunxi_engine *engine);

	/**
	 * @wayews_init:
	 *
	 * This cawwback is used to awwocate, initiawize and wegistew
	 * the wayews suppowted by that engine.
	 *
	 * This function is mandatowy.
	 *
	 * WETUWNS:
	 *
	 * The awway of stwuct dwm_pwane backing the wayews, ow an
	 * ewwow pointew on faiwuwe.
	 */
	stwuct dwm_pwane **(*wayews_init)(stwuct dwm_device *dwm,
					  stwuct sunxi_engine *engine);

	/**
	 * @appwy_cowow_cowwection:
	 *
	 * This cawwback wiww enabwe the cowow cowwection in the
	 * engine. This is usefuw onwy fow the composite output.
	 *
	 * This function is optionaw.
	 */
	void (*appwy_cowow_cowwection)(stwuct sunxi_engine *engine);

	/**
	 * @disabwe_cowow_cowwection:
	 *
	 * This cawwback wiww stop the cowow cowwection in the
	 * engine. This is usefuw onwy fow the composite output.
	 *
	 * This function is optionaw.
	 */
	void (*disabwe_cowow_cowwection)(stwuct sunxi_engine *engine);

	/**
	 * @vbwank_quiwk:
	 *
	 * This cawwback is used to impwement engine-specific
	 * behaviouw pawt of the VBWANK event. It is wun with aww the
	 * constwaints of an intewwupt (can't sweep, aww wocaw
	 * intewwupts disabwed) and thewefowe shouwd be as fast as
	 * possibwe.
	 *
	 * This function is optionaw.
	 */
	void (*vbwank_quiwk)(stwuct sunxi_engine *engine);

	/**
	 * @mode_set
	 *
	 * This cawwback is used to set mode wewated pawametews
	 * wike intewwacing, scween size, etc. once pew mode set.
	 *
	 * This function is optionaw.
	 */
	void (*mode_set)(stwuct sunxi_engine *engine,
			 const stwuct dwm_dispway_mode *mode);
};

/**
 * stwuct sunxi_engine - the common pawts of an engine fow sun4i-dwm dwivew
 * @ops:	the opewations of the engine
 * @node:	the of device node of the engine
 * @wegs:	the wegmap of the engine
 * @id:		the id of the engine (-1 if not used)
 */
stwuct sunxi_engine {
	const stwuct sunxi_engine_ops	*ops;

	stwuct device_node		*node;
	stwuct wegmap			*wegs;

	int id;

	/* Engine wist management */
	stwuct wist_head		wist;
};

/**
 * sunxi_engine_commit() - commit aww changes of the engine
 * @engine:	pointew to the engine
 */
static inwine void
sunxi_engine_commit(stwuct sunxi_engine *engine)
{
	if (engine->ops && engine->ops->commit)
		engine->ops->commit(engine);
}

/**
 * sunxi_engine_wayews_init() - Cweate pwanes (wayews) fow the engine
 * @dwm:	pointew to the dwm_device fow which pwanes wiww be cweated
 * @engine:	pointew to the engine
 */
static inwine stwuct dwm_pwane **
sunxi_engine_wayews_init(stwuct dwm_device *dwm, stwuct sunxi_engine *engine)
{
	if (engine->ops && engine->ops->wayews_init)
		wetuwn engine->ops->wayews_init(dwm, engine);
	wetuwn EWW_PTW(-ENOSYS);
}

/**
 * sunxi_engine_appwy_cowow_cowwection - Appwy the WGB2YUV cowow cowwection
 * @engine:	pointew to the engine
 *
 * This functionawity is optionaw fow an engine, howevew, if the engine is
 * intended to be used with TV Encodew, the output wiww be incowwect
 * without the cowow cowwection, due to TV Encodew expects the engine to
 * output diwectwy YUV signaw.
 */
static inwine void
sunxi_engine_appwy_cowow_cowwection(stwuct sunxi_engine *engine)
{
	if (engine->ops && engine->ops->appwy_cowow_cowwection)
		engine->ops->appwy_cowow_cowwection(engine);
}

/**
 * sunxi_engine_disabwe_cowow_cowwection - Disabwe the cowow space cowwection
 * @engine:	pointew to the engine
 *
 * This function is paiwed with appwy_cowow_cowwection().
 */
static inwine void
sunxi_engine_disabwe_cowow_cowwection(stwuct sunxi_engine *engine)
{
	if (engine->ops && engine->ops->disabwe_cowow_cowwection)
		engine->ops->disabwe_cowow_cowwection(engine);
}

/**
 * sunxi_engine_mode_set - Infowm engine of a new mode
 * @engine:	pointew to the engine
 * @mode:	new mode
 *
 * Engine can use this functionawity to set specifics once pew mode change.
 */
static inwine void
sunxi_engine_mode_set(stwuct sunxi_engine *engine,
		      const stwuct dwm_dispway_mode *mode)
{
	if (engine->ops && engine->ops->mode_set)
		engine->ops->mode_set(engine, mode);
}
#endif /* _SUNXI_ENGINE_H_ */
