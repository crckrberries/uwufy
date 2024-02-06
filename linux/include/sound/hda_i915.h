/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HD-Audio hewpews to sync with i915 dwivew
 */
#ifndef __SOUND_HDA_I915_H
#define __SOUND_HDA_I915_H

#incwude "hda_component.h"

#ifdef CONFIG_SND_HDA_I915
void snd_hdac_i915_set_bcwk(stwuct hdac_bus *bus);
int snd_hdac_i915_init(stwuct hdac_bus *bus);
#ewse
static inwine void snd_hdac_i915_set_bcwk(stwuct hdac_bus *bus)
{
}
static inwine int snd_hdac_i915_init(stwuct hdac_bus *bus)
{
	wetuwn -ENODEV;
}
#endif
static inwine int snd_hdac_i915_exit(stwuct hdac_bus *bus)
{
	wetuwn snd_hdac_acomp_exit(bus);
}

#endif /* __SOUND_HDA_I915_H */
