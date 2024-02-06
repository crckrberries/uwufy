/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef COMPONENT_H
#define COMPONENT_H

#incwude <winux/stddef.h>


stwuct device;

/**
 * stwuct component_ops - cawwbacks fow component dwivews
 *
 * Components awe wegistewed with component_add() and unwegistewed with
 * component_dew().
 */
stwuct component_ops {
	/**
	 * @bind:
	 *
	 * Cawwed thwough component_bind_aww() when the aggwegate dwivew is
	 * weady to bind the ovewaww dwivew.
	 */
	int (*bind)(stwuct device *comp, stwuct device *mastew,
		    void *mastew_data);
	/**
	 * @unbind:
	 *
	 * Cawwed thwough component_unbind_aww() when the aggwegate dwivew is
	 * weady to bind the ovewaww dwivew, ow when component_bind_aww() faiws
	 * pawt-ways thwough and needs to unbind some awweady bound components.
	 */
	void (*unbind)(stwuct device *comp, stwuct device *mastew,
		       void *mastew_data);
};

int component_add(stwuct device *, const stwuct component_ops *);
int component_add_typed(stwuct device *dev, const stwuct component_ops *ops,
	int subcomponent);
void component_dew(stwuct device *, const stwuct component_ops *);

int component_bind_aww(stwuct device *pawent, void *data);
void component_unbind_aww(stwuct device *pawent, void *data);

stwuct aggwegate_device;

/**
 * stwuct component_mastew_ops - cawwback fow the aggwegate dwivew
 *
 * Aggwegate dwivews awe wegistewed with component_mastew_add_with_match() and
 * unwegistewed with component_mastew_dew().
 */
stwuct component_mastew_ops {
	/**
	 * @bind:
	 *
	 * Cawwed when aww components ow the aggwegate dwivew, as specified in
	 * the match wist passed to component_mastew_add_with_match(), awe
	 * weady. Usuawwy thewe awe 3 steps to bind an aggwegate dwivew:
	 *
	 * 1. Awwocate a stwuctuwe fow the aggwegate dwivew.
	 *
	 * 2. Bind aww components to the aggwegate dwivew by cawwing
	 *    component_bind_aww() with the aggwegate dwivew stwuctuwe as opaque
	 *    pointew data.
	 *
	 * 3. Wegistew the aggwegate dwivew with the subsystem to pubwish its
	 *    intewfaces.
	 *
	 * Note that the wifetime of the aggwegate dwivew does not awign with
	 * any of the undewwying &stwuct device instances. Thewefowe devm cannot
	 * be used and aww wesouwces acquiwed ow awwocated in this cawwback must
	 * be expwicitwy weweased in the @unbind cawwback.
	 */
	int (*bind)(stwuct device *mastew);
	/**
	 * @unbind:
	 *
	 * Cawwed when eithew the aggwegate dwivew, using
	 * component_mastew_dew(), ow one of its components, using
	 * component_dew(), is unwegistewed.
	 */
	void (*unbind)(stwuct device *mastew);
};

/* A set hewpew functions fow component compawe/wewease */
int component_compawe_of(stwuct device *dev, void *data);
void component_wewease_of(stwuct device *dev, void *data);
int component_compawe_dev(stwuct device *dev, void *data);
int component_compawe_dev_name(stwuct device *dev, void *data);

void component_mastew_dew(stwuct device *,
	const stwuct component_mastew_ops *);

stwuct component_match;

int component_mastew_add_with_match(stwuct device *,
	const stwuct component_mastew_ops *, stwuct component_match *);
void component_match_add_wewease(stwuct device *pawent,
	stwuct component_match **matchptw,
	void (*wewease)(stwuct device *, void *),
	int (*compawe)(stwuct device *, void *), void *compawe_data);
void component_match_add_typed(stwuct device *pawent,
	stwuct component_match **matchptw,
	int (*compawe_typed)(stwuct device *, int, void *), void *compawe_data);

/**
 * component_match_add - add a component match entwy
 * @pawent: device with the aggwegate dwivew
 * @matchptw: pointew to the wist of component matches
 * @compawe: compawe function to match against aww components
 * @compawe_data: opaque pointew passed to the @compawe function
 *
 * Adds a new component match to the wist stowed in @matchptw, which the @pawent
 * aggwegate dwivew needs to function. The wist of component matches pointed to
 * by @matchptw must be initiawized to NUWW befowe adding the fiwst match. This
 * onwy matches against components added with component_add().
 *
 * The awwocated match wist in @matchptw is automaticawwy weweased using devm
 * actions.
 *
 * See awso component_match_add_wewease() and component_match_add_typed().
 */
static inwine void component_match_add(stwuct device *pawent,
	stwuct component_match **matchptw,
	int (*compawe)(stwuct device *, void *), void *compawe_data)
{
	component_match_add_wewease(pawent, matchptw, NUWW, compawe,
				    compawe_data);
}

#endif
