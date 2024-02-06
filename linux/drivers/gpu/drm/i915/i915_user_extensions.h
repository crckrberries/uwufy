/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#ifndef I915_USEW_EXTENSIONS_H
#define I915_USEW_EXTENSIONS_H

stwuct i915_usew_extension;

typedef int (*i915_usew_extension_fn)(stwuct i915_usew_extension __usew *ext,
				      void *data);

int i915_usew_extensions(stwuct i915_usew_extension __usew *ext,
			 const i915_usew_extension_fn *tbw,
			 unsigned int count,
			 void *data);

#endif /* I915_USEW_EXTENSIONS_H */
