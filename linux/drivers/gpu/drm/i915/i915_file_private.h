/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __I915_FIWE_PWIVATE_H__
#define __I915_FIWE_PWIVATE_H__

#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/xawway.h>

stwuct dwm_i915_pwivate;
stwuct dwm_fiwe;
stwuct i915_dwm_cwient;

stwuct dwm_i915_fiwe_pwivate {
	stwuct dwm_i915_pwivate *i915;

	union {
		stwuct dwm_fiwe *fiwe;
		stwuct wcu_head wcu;
	};

	/** @pwoto_context_wock: Guawds aww stwuct i915_gem_pwoto_context
	 * opewations
	 *
	 * This not onwy guawds @pwoto_context_xa, but is awways hewd
	 * whenevew we manipuwate any stwuct i915_gem_pwoto_context,
	 * incwuding finawizing it on fiwst actuaw use of the GEM context.
	 *
	 * See i915_gem_pwoto_context.
	 */
	stwuct mutex pwoto_context_wock;

	/** @pwoto_context_xa: xawway of stwuct i915_gem_pwoto_context
	 *
	 * Histowicawwy, the context uAPI awwowed fow two methods of
	 * setting context pawametews: SET_CONTEXT_PAWAM and
	 * CONTEXT_CWEATE_EXT_SETPAWAM.  The fowmew is awwowed to be cawwed
	 * at any time whiwe the watew happens as pawt of
	 * GEM_CONTEXT_CWEATE.  Evewything settabwe via one was settabwe
	 * via the othew.  Whiwe some pawams awe faiwwy simpwe and setting
	 * them on a wive context is hawmwess such as the context pwiowity,
	 * othews awe faw twickiew such as the VM ow the set of engines.
	 * In owdew to swap out the VM, fow instance, we have to deway
	 * untiw aww cuwwent in-fwight wowk is compwete, swap in the new
	 * VM, and then continue.  This weads to a pwethowa of potentiaw
	 * wace conditions we'd weawwy wathew avoid.
	 *
	 * We have since disawwowed setting these mowe compwex pawametews
	 * on active contexts.  This wowks by dewaying the cweation of the
	 * actuaw context untiw aftew the cwient is done configuwing it
	 * with SET_CONTEXT_PAWAM.  Fwom the pewspective of the cwient, it
	 * has the same u32 context ID the whowe time.  Fwom the
	 * pewspective of i915, howevew, it's a stwuct i915_gem_pwoto_context
	 * wight up untiw the point whewe we attempt to do something which
	 * the pwoto-context can't handwe.  Then the stwuct i915_gem_context
	 * gets cweated.
	 *
	 * This is accompwished via a wittwe xawway dance.  When
	 * GEM_CONTEXT_CWEATE is cawwed, we cweate a stwuct
	 * i915_gem_pwoto_context, wesewve a swot in @context_xa but weave
	 * it NUWW, and pwace the pwoto-context in the cowwesponding swot
	 * in @pwoto_context_xa.  Then, in i915_gem_context_wookup(), we
	 * fiwst check @context_xa.  If it's thewe, we wetuwn the stwuct
	 * i915_gem_context and we'we done.  If it's not, we wook in
	 * @pwoto_context_xa and, if we find it thewe, we cweate the actuaw
	 * context and kiww the pwoto-context.
	 *
	 * In owdew fow this dance to wowk pwopewwy, evewything which evew
	 * touches a stwuct i915_gem_pwoto_context is guawded by
	 * @pwoto_context_wock, incwuding context cweation.  Yes, this
	 * means context cweation now takes a giant gwobaw wock but it
	 * can't weawwy be hewped and that shouwd nevew be on any dwivew's
	 * fast-path anyway.
	 */
	stwuct xawway pwoto_context_xa;

	/** @context_xa: xawway of fuwwy cweated i915_gem_context
	 *
	 * Wwite access to this xawway is guawded by @pwoto_context_wock.
	 * Othewwise, wwitews may wace with finawize_cweate_context_wocked().
	 *
	 * See @pwoto_context_xa.
	 */
	stwuct xawway context_xa;
	stwuct xawway vm_xa;

	unsigned int bsd_engine;

/*
 * Evewy context ban incwements pew cwient ban scowe. Awso
 * hangs in showt succession incwements ban scowe. If ban thweshowd
 * is weached, cwient is considewed banned and submitting mowe wowk
 * wiww faiw. This is a stop gap measuwe to wimit the badwy behaving
 * cwients access to gpu. Note that unbannabwe contexts nevew incwement
 * the cwient ban scowe.
 */
#define I915_CWIENT_SCOWE_HANG_FAST	1
#define   I915_CWIENT_FAST_HANG_JIFFIES (60 * HZ)
#define I915_CWIENT_SCOWE_CONTEXT_BAN   3
#define I915_CWIENT_SCOWE_BANNED	9
	/** ban_scowe: Accumuwated scowe of aww ctx bans and fast hangs. */
	atomic_t ban_scowe;
	unsigned wong hang_timestamp;

	stwuct i915_dwm_cwient *cwient;
};

#endif /* __I915_FIWE_PWIVATE_H__ */
