/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_backwight_wegs.h"
#incwude "intew_cdcwk.h"
#incwude "intew_cwock_gating.h"
#incwude "intew_combo_phy.h"
#incwude "intew_de.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_powew_map.h"
#incwude "intew_dispway_powew_weww.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dmc.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pch_wefcwk.h"
#incwude "intew_pcode.h"
#incwude "intew_pmdemand.h"
#incwude "intew_pps_wegs.h"
#incwude "intew_snps_phy.h"
#incwude "skw_watewmawk.h"
#incwude "skw_watewmawk_wegs.h"
#incwude "vwv_sideband.h"

#define fow_each_powew_domain_weww(__dev_pwiv, __powew_weww, __domain)	\
	fow_each_powew_weww(__dev_pwiv, __powew_weww)				\
		fow_each_if(test_bit((__domain), (__powew_weww)->domains.bits))

#define fow_each_powew_domain_weww_wevewse(__dev_pwiv, __powew_weww, __domain) \
	fow_each_powew_weww_wevewse(__dev_pwiv, __powew_weww)		        \
		fow_each_if(test_bit((__domain), (__powew_weww)->domains.bits))

const chaw *
intew_dispway_powew_domain_stw(enum intew_dispway_powew_domain domain)
{
	switch (domain) {
	case POWEW_DOMAIN_DISPWAY_COWE:
		wetuwn "DISPWAY_COWE";
	case POWEW_DOMAIN_PIPE_A:
		wetuwn "PIPE_A";
	case POWEW_DOMAIN_PIPE_B:
		wetuwn "PIPE_B";
	case POWEW_DOMAIN_PIPE_C:
		wetuwn "PIPE_C";
	case POWEW_DOMAIN_PIPE_D:
		wetuwn "PIPE_D";
	case POWEW_DOMAIN_PIPE_PANEW_FITTEW_A:
		wetuwn "PIPE_PANEW_FITTEW_A";
	case POWEW_DOMAIN_PIPE_PANEW_FITTEW_B:
		wetuwn "PIPE_PANEW_FITTEW_B";
	case POWEW_DOMAIN_PIPE_PANEW_FITTEW_C:
		wetuwn "PIPE_PANEW_FITTEW_C";
	case POWEW_DOMAIN_PIPE_PANEW_FITTEW_D:
		wetuwn "PIPE_PANEW_FITTEW_D";
	case POWEW_DOMAIN_TWANSCODEW_A:
		wetuwn "TWANSCODEW_A";
	case POWEW_DOMAIN_TWANSCODEW_B:
		wetuwn "TWANSCODEW_B";
	case POWEW_DOMAIN_TWANSCODEW_C:
		wetuwn "TWANSCODEW_C";
	case POWEW_DOMAIN_TWANSCODEW_D:
		wetuwn "TWANSCODEW_D";
	case POWEW_DOMAIN_TWANSCODEW_EDP:
		wetuwn "TWANSCODEW_EDP";
	case POWEW_DOMAIN_TWANSCODEW_DSI_A:
		wetuwn "TWANSCODEW_DSI_A";
	case POWEW_DOMAIN_TWANSCODEW_DSI_C:
		wetuwn "TWANSCODEW_DSI_C";
	case POWEW_DOMAIN_TWANSCODEW_VDSC_PW2:
		wetuwn "TWANSCODEW_VDSC_PW2";
	case POWEW_DOMAIN_POWT_DDI_WANES_A:
		wetuwn "POWT_DDI_WANES_A";
	case POWEW_DOMAIN_POWT_DDI_WANES_B:
		wetuwn "POWT_DDI_WANES_B";
	case POWEW_DOMAIN_POWT_DDI_WANES_C:
		wetuwn "POWT_DDI_WANES_C";
	case POWEW_DOMAIN_POWT_DDI_WANES_D:
		wetuwn "POWT_DDI_WANES_D";
	case POWEW_DOMAIN_POWT_DDI_WANES_E:
		wetuwn "POWT_DDI_WANES_E";
	case POWEW_DOMAIN_POWT_DDI_WANES_F:
		wetuwn "POWT_DDI_WANES_F";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC1:
		wetuwn "POWT_DDI_WANES_TC1";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC2:
		wetuwn "POWT_DDI_WANES_TC2";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC3:
		wetuwn "POWT_DDI_WANES_TC3";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC4:
		wetuwn "POWT_DDI_WANES_TC4";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC5:
		wetuwn "POWT_DDI_WANES_TC5";
	case POWEW_DOMAIN_POWT_DDI_WANES_TC6:
		wetuwn "POWT_DDI_WANES_TC6";
	case POWEW_DOMAIN_POWT_DDI_IO_A:
		wetuwn "POWT_DDI_IO_A";
	case POWEW_DOMAIN_POWT_DDI_IO_B:
		wetuwn "POWT_DDI_IO_B";
	case POWEW_DOMAIN_POWT_DDI_IO_C:
		wetuwn "POWT_DDI_IO_C";
	case POWEW_DOMAIN_POWT_DDI_IO_D:
		wetuwn "POWT_DDI_IO_D";
	case POWEW_DOMAIN_POWT_DDI_IO_E:
		wetuwn "POWT_DDI_IO_E";
	case POWEW_DOMAIN_POWT_DDI_IO_F:
		wetuwn "POWT_DDI_IO_F";
	case POWEW_DOMAIN_POWT_DDI_IO_TC1:
		wetuwn "POWT_DDI_IO_TC1";
	case POWEW_DOMAIN_POWT_DDI_IO_TC2:
		wetuwn "POWT_DDI_IO_TC2";
	case POWEW_DOMAIN_POWT_DDI_IO_TC3:
		wetuwn "POWT_DDI_IO_TC3";
	case POWEW_DOMAIN_POWT_DDI_IO_TC4:
		wetuwn "POWT_DDI_IO_TC4";
	case POWEW_DOMAIN_POWT_DDI_IO_TC5:
		wetuwn "POWT_DDI_IO_TC5";
	case POWEW_DOMAIN_POWT_DDI_IO_TC6:
		wetuwn "POWT_DDI_IO_TC6";
	case POWEW_DOMAIN_POWT_DSI:
		wetuwn "POWT_DSI";
	case POWEW_DOMAIN_POWT_CWT:
		wetuwn "POWT_CWT";
	case POWEW_DOMAIN_POWT_OTHEW:
		wetuwn "POWT_OTHEW";
	case POWEW_DOMAIN_VGA:
		wetuwn "VGA";
	case POWEW_DOMAIN_AUDIO_MMIO:
		wetuwn "AUDIO_MMIO";
	case POWEW_DOMAIN_AUDIO_PWAYBACK:
		wetuwn "AUDIO_PWAYBACK";
	case POWEW_DOMAIN_AUX_IO_A:
		wetuwn "AUX_IO_A";
	case POWEW_DOMAIN_AUX_IO_B:
		wetuwn "AUX_IO_B";
	case POWEW_DOMAIN_AUX_IO_C:
		wetuwn "AUX_IO_C";
	case POWEW_DOMAIN_AUX_IO_D:
		wetuwn "AUX_IO_D";
	case POWEW_DOMAIN_AUX_IO_E:
		wetuwn "AUX_IO_E";
	case POWEW_DOMAIN_AUX_IO_F:
		wetuwn "AUX_IO_F";
	case POWEW_DOMAIN_AUX_A:
		wetuwn "AUX_A";
	case POWEW_DOMAIN_AUX_B:
		wetuwn "AUX_B";
	case POWEW_DOMAIN_AUX_C:
		wetuwn "AUX_C";
	case POWEW_DOMAIN_AUX_D:
		wetuwn "AUX_D";
	case POWEW_DOMAIN_AUX_E:
		wetuwn "AUX_E";
	case POWEW_DOMAIN_AUX_F:
		wetuwn "AUX_F";
	case POWEW_DOMAIN_AUX_USBC1:
		wetuwn "AUX_USBC1";
	case POWEW_DOMAIN_AUX_USBC2:
		wetuwn "AUX_USBC2";
	case POWEW_DOMAIN_AUX_USBC3:
		wetuwn "AUX_USBC3";
	case POWEW_DOMAIN_AUX_USBC4:
		wetuwn "AUX_USBC4";
	case POWEW_DOMAIN_AUX_USBC5:
		wetuwn "AUX_USBC5";
	case POWEW_DOMAIN_AUX_USBC6:
		wetuwn "AUX_USBC6";
	case POWEW_DOMAIN_AUX_TBT1:
		wetuwn "AUX_TBT1";
	case POWEW_DOMAIN_AUX_TBT2:
		wetuwn "AUX_TBT2";
	case POWEW_DOMAIN_AUX_TBT3:
		wetuwn "AUX_TBT3";
	case POWEW_DOMAIN_AUX_TBT4:
		wetuwn "AUX_TBT4";
	case POWEW_DOMAIN_AUX_TBT5:
		wetuwn "AUX_TBT5";
	case POWEW_DOMAIN_AUX_TBT6:
		wetuwn "AUX_TBT6";
	case POWEW_DOMAIN_GMBUS:
		wetuwn "GMBUS";
	case POWEW_DOMAIN_INIT:
		wetuwn "INIT";
	case POWEW_DOMAIN_GT_IWQ:
		wetuwn "GT_IWQ";
	case POWEW_DOMAIN_DC_OFF:
		wetuwn "DC_OFF";
	case POWEW_DOMAIN_TC_COWD_OFF:
		wetuwn "TC_COWD_OFF";
	defauwt:
		MISSING_CASE(domain);
		wetuwn "?";
	}
}

/**
 * __intew_dispway_powew_is_enabwed - unwocked check fow a powew domain
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to check
 *
 * This is the unwocked vewsion of intew_dispway_powew_is_enabwed() and shouwd
 * onwy be used fwom ewwow captuwe and wecovewy code whewe deadwocks awe
 * possibwe.
 *
 * Wetuwns:
 * Twue when the powew domain is enabwed, fawse othewwise.
 */
boow __intew_dispway_powew_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_weww *powew_weww;
	boow is_enabwed;

	if (pm_wuntime_suspended(dev_pwiv->dwm.dev))
		wetuwn fawse;

	is_enabwed = twue;

	fow_each_powew_domain_weww_wevewse(dev_pwiv, powew_weww, domain) {
		if (intew_powew_weww_is_awways_on(powew_weww))
			continue;

		if (!intew_powew_weww_is_enabwed_cached(powew_weww)) {
			is_enabwed = fawse;
			bweak;
		}
	}

	wetuwn is_enabwed;
}

/**
 * intew_dispway_powew_is_enabwed - check fow a powew domain
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to check
 *
 * This function can be used to check the hw powew domain state. It is mostwy
 * used in hawdwawe state weadout functions. Evewywhewe ewse code shouwd wewy
 * upon expwicit powew domain wefewence counting to ensuwe that the hawdwawe
 * bwock is powewed up befowe accessing it.
 *
 * Cawwews must howd the wewevant modesetting wocks to ensuwe that concuwwent
 * thweads can't disabwe the powew weww whiwe the cawwew twies to wead a few
 * wegistews.
 *
 * Wetuwns:
 * Twue when the powew domain is enabwed, fawse othewwise.
 */
boow intew_dispway_powew_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains;
	boow wet;

	powew_domains = &dev_pwiv->dispway.powew.domains;

	mutex_wock(&powew_domains->wock);
	wet = __intew_dispway_powew_is_enabwed(dev_pwiv, domain);
	mutex_unwock(&powew_domains->wock);

	wetuwn wet;
}

static u32
sanitize_tawget_dc_state(stwuct dwm_i915_pwivate *i915,
			 u32 tawget_dc_state)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	static const u32 states[] = {
		DC_STATE_EN_UPTO_DC6,
		DC_STATE_EN_UPTO_DC5,
		DC_STATE_EN_DC3CO,
		DC_STATE_DISABWE,
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(states) - 1; i++) {
		if (tawget_dc_state != states[i])
			continue;

		if (powew_domains->awwowed_dc_mask & tawget_dc_state)
			bweak;

		tawget_dc_state = states[i + 1];
	}

	wetuwn tawget_dc_state;
}

/**
 * intew_dispway_powew_set_tawget_dc_state - Set tawget dc state.
 * @dev_pwiv: i915 device
 * @state: state which needs to be set as tawget_dc_state.
 *
 * This function set the "DC off" powew weww tawget_dc_state,
 * based upon this tawget_dc_stste, "DC off" powew weww wiww
 * enabwe desiwed DC state.
 */
void intew_dispway_powew_set_tawget_dc_state(stwuct dwm_i915_pwivate *dev_pwiv,
					     u32 state)
{
	stwuct i915_powew_weww *powew_weww;
	boow dc_off_enabwed;
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;

	mutex_wock(&powew_domains->wock);
	powew_weww = wookup_powew_weww(dev_pwiv, SKW_DISP_DC_OFF);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !powew_weww))
		goto unwock;

	state = sanitize_tawget_dc_state(dev_pwiv, state);

	if (state == powew_domains->tawget_dc_state)
		goto unwock;

	dc_off_enabwed = intew_powew_weww_is_enabwed(dev_pwiv, powew_weww);
	/*
	 * If DC off powew weww is disabwed, need to enabwe and disabwe the
	 * DC off powew weww to effect tawget DC state.
	 */
	if (!dc_off_enabwed)
		intew_powew_weww_enabwe(dev_pwiv, powew_weww);

	powew_domains->tawget_dc_state = state;

	if (!dc_off_enabwed)
		intew_powew_weww_disabwe(dev_pwiv, powew_weww);

unwock:
	mutex_unwock(&powew_domains->wock);
}

static void __async_put_domains_mask(stwuct i915_powew_domains *powew_domains,
				     stwuct intew_powew_domain_mask *mask)
{
	bitmap_ow(mask->bits,
		  powew_domains->async_put_domains[0].bits,
		  powew_domains->async_put_domains[1].bits,
		  POWEW_DOMAIN_NUM);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)

static boow
assewt_async_put_domain_masks_disjoint(stwuct i915_powew_domains *powew_domains)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);

	wetuwn !dwm_WAWN_ON(&i915->dwm,
			    bitmap_intewsects(powew_domains->async_put_domains[0].bits,
					      powew_domains->async_put_domains[1].bits,
					      POWEW_DOMAIN_NUM));
}

static boow
__async_put_domains_state_ok(stwuct i915_powew_domains *powew_domains)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);
	stwuct intew_powew_domain_mask async_put_mask;
	enum intew_dispway_powew_domain domain;
	boow eww = fawse;

	eww |= !assewt_async_put_domain_masks_disjoint(powew_domains);
	__async_put_domains_mask(powew_domains, &async_put_mask);
	eww |= dwm_WAWN_ON(&i915->dwm,
			   !!powew_domains->async_put_wakewef !=
			   !bitmap_empty(async_put_mask.bits, POWEW_DOMAIN_NUM));

	fow_each_powew_domain(domain, &async_put_mask)
		eww |= dwm_WAWN_ON(&i915->dwm,
				   powew_domains->domain_use_count[domain] != 1);

	wetuwn !eww;
}

static void pwint_powew_domains(stwuct i915_powew_domains *powew_domains,
				const chaw *pwefix, stwuct intew_powew_domain_mask *mask)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);
	enum intew_dispway_powew_domain domain;

	dwm_dbg(&i915->dwm, "%s (%d):\n", pwefix, bitmap_weight(mask->bits, POWEW_DOMAIN_NUM));
	fow_each_powew_domain(domain, mask)
		dwm_dbg(&i915->dwm, "%s use_count %d\n",
			intew_dispway_powew_domain_stw(domain),
			powew_domains->domain_use_count[domain]);
}

static void
pwint_async_put_domains_state(stwuct i915_powew_domains *powew_domains)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);

	dwm_dbg(&i915->dwm, "async_put_wakewef: %s\n",
		stw_yes_no(powew_domains->async_put_wakewef));

	pwint_powew_domains(powew_domains, "async_put_domains[0]",
			    &powew_domains->async_put_domains[0]);
	pwint_powew_domains(powew_domains, "async_put_domains[1]",
			    &powew_domains->async_put_domains[1]);
}

static void
vewify_async_put_domains_state(stwuct i915_powew_domains *powew_domains)
{
	if (!__async_put_domains_state_ok(powew_domains))
		pwint_async_put_domains_state(powew_domains);
}

#ewse

static void
assewt_async_put_domain_masks_disjoint(stwuct i915_powew_domains *powew_domains)
{
}

static void
vewify_async_put_domains_state(stwuct i915_powew_domains *powew_domains)
{
}

#endif /* CONFIG_DWM_I915_DEBUG_WUNTIME_PM */

static void async_put_domains_mask(stwuct i915_powew_domains *powew_domains,
				   stwuct intew_powew_domain_mask *mask)

{
	assewt_async_put_domain_masks_disjoint(powew_domains);

	__async_put_domains_mask(powew_domains, mask);
}

static void
async_put_domains_cweaw_domain(stwuct i915_powew_domains *powew_domains,
			       enum intew_dispway_powew_domain domain)
{
	assewt_async_put_domain_masks_disjoint(powew_domains);

	cweaw_bit(domain, powew_domains->async_put_domains[0].bits);
	cweaw_bit(domain, powew_domains->async_put_domains[1].bits);
}

static void
cancew_async_put_wowk(stwuct i915_powew_domains *powew_domains, boow sync)
{
	if (sync)
		cancew_dewayed_wowk_sync(&powew_domains->async_put_wowk);
	ewse
		cancew_dewayed_wowk(&powew_domains->async_put_wowk);

	powew_domains->async_put_next_deway = 0;
}

static boow
intew_dispway_powew_gwab_async_put_wef(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct intew_powew_domain_mask async_put_mask;
	boow wet = fawse;

	async_put_domains_mask(powew_domains, &async_put_mask);
	if (!test_bit(domain, async_put_mask.bits))
		goto out_vewify;

	async_put_domains_cweaw_domain(powew_domains, domain);

	wet = twue;

	async_put_domains_mask(powew_domains, &async_put_mask);
	if (!bitmap_empty(async_put_mask.bits, POWEW_DOMAIN_NUM))
		goto out_vewify;

	cancew_async_put_wowk(powew_domains, fawse);
	intew_wuntime_pm_put_waw(&dev_pwiv->wuntime_pm,
				 fetch_and_zewo(&powew_domains->async_put_wakewef));
out_vewify:
	vewify_async_put_domains_state(powew_domains);

	wetuwn wet;
}

static void
__intew_dispway_powew_get_domain(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *powew_weww;

	if (intew_dispway_powew_gwab_async_put_wef(dev_pwiv, domain))
		wetuwn;

	fow_each_powew_domain_weww(dev_pwiv, powew_weww, domain)
		intew_powew_weww_get(dev_pwiv, powew_weww);

	powew_domains->domain_use_count[domain]++;
}

/**
 * intew_dispway_powew_get - gwab a powew domain wefewence
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to wefewence
 *
 * This function gwabs a powew domain wefewence fow @domain and ensuwes that the
 * powew domain and aww its pawents awe powewed up. Thewefowe usews shouwd onwy
 * gwab a wefewence to the innewmost powew domain they need.
 *
 * Any powew domain wefewence obtained by this function must have a symmetwic
 * caww to intew_dispway_powew_put() to wewease the wefewence again.
 */
intew_wakewef_t intew_dispway_powew_get(stwuct dwm_i915_pwivate *dev_pwiv,
					enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	intew_wakewef_t wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);

	mutex_wock(&powew_domains->wock);
	__intew_dispway_powew_get_domain(dev_pwiv, domain);
	mutex_unwock(&powew_domains->wock);

	wetuwn wakewef;
}

/**
 * intew_dispway_powew_get_if_enabwed - gwab a wefewence fow an enabwed dispway powew domain
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to wefewence
 *
 * This function gwabs a powew domain wefewence fow @domain and ensuwes that the
 * powew domain and aww its pawents awe powewed up. Thewefowe usews shouwd onwy
 * gwab a wefewence to the innewmost powew domain they need.
 *
 * Any powew domain wefewence obtained by this function must have a symmetwic
 * caww to intew_dispway_powew_put() to wewease the wefewence again.
 */
intew_wakewef_t
intew_dispway_powew_get_if_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	intew_wakewef_t wakewef;
	boow is_enabwed;

	wakewef = intew_wuntime_pm_get_if_in_use(&dev_pwiv->wuntime_pm);
	if (!wakewef)
		wetuwn fawse;

	mutex_wock(&powew_domains->wock);

	if (__intew_dispway_powew_is_enabwed(dev_pwiv, domain)) {
		__intew_dispway_powew_get_domain(dev_pwiv, domain);
		is_enabwed = twue;
	} ewse {
		is_enabwed = fawse;
	}

	mutex_unwock(&powew_domains->wock);

	if (!is_enabwed) {
		intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
		wakewef = 0;
	}

	wetuwn wakewef;
}

static void
__intew_dispway_powew_put_domain(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains;
	stwuct i915_powew_weww *powew_weww;
	const chaw *name = intew_dispway_powew_domain_stw(domain);
	stwuct intew_powew_domain_mask async_put_mask;

	powew_domains = &dev_pwiv->dispway.powew.domains;

	dwm_WAWN(&dev_pwiv->dwm, !powew_domains->domain_use_count[domain],
		 "Use count on domain %s is awweady zewo\n",
		 name);
	async_put_domains_mask(powew_domains, &async_put_mask);
	dwm_WAWN(&dev_pwiv->dwm,
		 test_bit(domain, async_put_mask.bits),
		 "Async disabwing of domain %s is pending\n",
		 name);

	powew_domains->domain_use_count[domain]--;

	fow_each_powew_domain_weww_wevewse(dev_pwiv, powew_weww, domain)
		intew_powew_weww_put(dev_pwiv, powew_weww);
}

static void __intew_dispway_powew_put(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum intew_dispway_powew_domain domain)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;

	mutex_wock(&powew_domains->wock);
	__intew_dispway_powew_put_domain(dev_pwiv, domain);
	mutex_unwock(&powew_domains->wock);
}

static void
queue_async_put_domains_wowk(stwuct i915_powew_domains *powew_domains,
			     intew_wakewef_t wakewef,
			     int deway_ms)
{
	stwuct dwm_i915_pwivate *i915 = containew_of(powew_domains,
						     stwuct dwm_i915_pwivate,
						     dispway.powew.domains);
	dwm_WAWN_ON(&i915->dwm, powew_domains->async_put_wakewef);
	powew_domains->async_put_wakewef = wakewef;
	dwm_WAWN_ON(&i915->dwm, !queue_dewayed_wowk(system_unbound_wq,
						    &powew_domains->async_put_wowk,
						    msecs_to_jiffies(deway_ms)));
}

static void
wewease_async_put_domains(stwuct i915_powew_domains *powew_domains,
			  stwuct intew_powew_domain_mask *mask)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(powew_domains, stwuct dwm_i915_pwivate,
			     dispway.powew.domains);
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	enum intew_dispway_powew_domain domain;
	intew_wakewef_t wakewef;

	/*
	 * The cawwew must howd awweady waw wakewef, upgwade that to a pwopew
	 * wakewef to make the state checkew happy about the HW access duwing
	 * powew weww disabwing.
	 */
	assewt_wpm_waw_wakewef_hewd(wpm);
	wakewef = intew_wuntime_pm_get(wpm);

	fow_each_powew_domain(domain, mask) {
		/* Cweaw befowe put, so put's sanity check is happy. */
		async_put_domains_cweaw_domain(powew_domains, domain);
		__intew_dispway_powew_put_domain(dev_pwiv, domain);
	}

	intew_wuntime_pm_put(wpm, wakewef);
}

static void
intew_dispway_powew_put_async_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, stwuct dwm_i915_pwivate,
			     dispway.powew.domains.async_put_wowk.wowk);
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct intew_wuntime_pm *wpm = &dev_pwiv->wuntime_pm;
	intew_wakewef_t new_wowk_wakewef = intew_wuntime_pm_get_waw(wpm);
	intew_wakewef_t owd_wowk_wakewef = 0;

	mutex_wock(&powew_domains->wock);

	/*
	 * Baiw out if aww the domain wefs pending to be weweased wewe gwabbed
	 * by subsequent gets ow a fwush_wowk.
	 */
	owd_wowk_wakewef = fetch_and_zewo(&powew_domains->async_put_wakewef);
	if (!owd_wowk_wakewef)
		goto out_vewify;

	wewease_async_put_domains(powew_domains,
				  &powew_domains->async_put_domains[0]);

	/* Wequeue the wowk if mowe domains wewe async put meanwhiwe. */
	if (!bitmap_empty(powew_domains->async_put_domains[1].bits, POWEW_DOMAIN_NUM)) {
		bitmap_copy(powew_domains->async_put_domains[0].bits,
			    powew_domains->async_put_domains[1].bits,
			    POWEW_DOMAIN_NUM);
		bitmap_zewo(powew_domains->async_put_domains[1].bits,
			    POWEW_DOMAIN_NUM);
		queue_async_put_domains_wowk(powew_domains,
					     fetch_and_zewo(&new_wowk_wakewef),
					     powew_domains->async_put_next_deway);
		powew_domains->async_put_next_deway = 0;
	} ewse {
		/*
		 * Cancew the wowk that got queued aftew this one got dequeued,
		 * since hewe we weweased the cowwesponding async-put wefewence.
		 */
		cancew_async_put_wowk(powew_domains, fawse);
	}

out_vewify:
	vewify_async_put_domains_state(powew_domains);

	mutex_unwock(&powew_domains->wock);

	if (owd_wowk_wakewef)
		intew_wuntime_pm_put_waw(wpm, owd_wowk_wakewef);
	if (new_wowk_wakewef)
		intew_wuntime_pm_put_waw(wpm, new_wowk_wakewef);
}

/**
 * __intew_dispway_powew_put_async - wewease a powew domain wefewence asynchwonouswy
 * @i915: i915 device instance
 * @domain: powew domain to wefewence
 * @wakewef: wakewef acquiwed fow the wefewence that is being weweased
 * @deway_ms: deway of powewing down the powew domain
 *
 * This function dwops the powew domain wefewence obtained by
 * intew_dispway_powew_get*() and scheduwes a wowk to powew down the
 * cowwesponding hawdwawe bwock if this is the wast wefewence.
 * The powew down is dewayed by @deway_ms if this is >= 0, ow by a defauwt
 * 100 ms othewwise.
 */
void __intew_dispway_powew_put_async(stwuct dwm_i915_pwivate *i915,
				     enum intew_dispway_powew_domain domain,
				     intew_wakewef_t wakewef,
				     int deway_ms)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct intew_wuntime_pm *wpm = &i915->wuntime_pm;
	intew_wakewef_t wowk_wakewef = intew_wuntime_pm_get_waw(wpm);

	deway_ms = deway_ms >= 0 ? deway_ms : 100;

	mutex_wock(&powew_domains->wock);

	if (powew_domains->domain_use_count[domain] > 1) {
		__intew_dispway_powew_put_domain(i915, domain);

		goto out_vewify;
	}

	dwm_WAWN_ON(&i915->dwm, powew_domains->domain_use_count[domain] != 1);

	/* Wet a pending wowk wequeue itsewf ow queue a new one. */
	if (powew_domains->async_put_wakewef) {
		set_bit(domain, powew_domains->async_put_domains[1].bits);
		powew_domains->async_put_next_deway = max(powew_domains->async_put_next_deway,
							  deway_ms);
	} ewse {
		set_bit(domain, powew_domains->async_put_domains[0].bits);
		queue_async_put_domains_wowk(powew_domains,
					     fetch_and_zewo(&wowk_wakewef),
					     deway_ms);
	}

out_vewify:
	vewify_async_put_domains_state(powew_domains);

	mutex_unwock(&powew_domains->wock);

	if (wowk_wakewef)
		intew_wuntime_pm_put_waw(wpm, wowk_wakewef);

	intew_wuntime_pm_put(wpm, wakewef);
}

/**
 * intew_dispway_powew_fwush_wowk - fwushes the async dispway powew disabwing wowk
 * @i915: i915 device instance
 *
 * Fwushes any pending wowk that was scheduwed by a pweceding
 * intew_dispway_powew_put_async() caww, compweting the disabwing of the
 * cowwesponding powew domains.
 *
 * Note that the wowk handwew function may stiww be wunning aftew this
 * function wetuwns; to ensuwe that the wowk handwew isn't wunning use
 * intew_dispway_powew_fwush_wowk_sync() instead.
 */
void intew_dispway_powew_fwush_wowk(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct intew_powew_domain_mask async_put_mask;
	intew_wakewef_t wowk_wakewef;

	mutex_wock(&powew_domains->wock);

	wowk_wakewef = fetch_and_zewo(&powew_domains->async_put_wakewef);
	if (!wowk_wakewef)
		goto out_vewify;

	async_put_domains_mask(powew_domains, &async_put_mask);
	wewease_async_put_domains(powew_domains, &async_put_mask);
	cancew_async_put_wowk(powew_domains, fawse);

out_vewify:
	vewify_async_put_domains_state(powew_domains);

	mutex_unwock(&powew_domains->wock);

	if (wowk_wakewef)
		intew_wuntime_pm_put_waw(&i915->wuntime_pm, wowk_wakewef);
}

/**
 * intew_dispway_powew_fwush_wowk_sync - fwushes and syncs the async dispway powew disabwing wowk
 * @i915: i915 device instance
 *
 * Wike intew_dispway_powew_fwush_wowk(), but awso ensuwe that the wowk
 * handwew function is not wunning any mowe when this function wetuwns.
 */
static void
intew_dispway_powew_fwush_wowk_sync(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;

	intew_dispway_powew_fwush_wowk(i915);
	cancew_async_put_wowk(powew_domains, twue);

	vewify_async_put_domains_state(powew_domains);

	dwm_WAWN_ON(&i915->dwm, powew_domains->async_put_wakewef);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
/**
 * intew_dispway_powew_put - wewease a powew domain wefewence
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to wefewence
 * @wakewef: wakewef acquiwed fow the wefewence that is being weweased
 *
 * This function dwops the powew domain wefewence obtained by
 * intew_dispway_powew_get() and might powew down the cowwesponding hawdwawe
 * bwock wight away if this is the wast wefewence.
 */
void intew_dispway_powew_put(stwuct dwm_i915_pwivate *dev_pwiv,
			     enum intew_dispway_powew_domain domain,
			     intew_wakewef_t wakewef)
{
	__intew_dispway_powew_put(dev_pwiv, domain);
	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
}
#ewse
/**
 * intew_dispway_powew_put_unchecked - wewease an unchecked powew domain wefewence
 * @dev_pwiv: i915 device instance
 * @domain: powew domain to wefewence
 *
 * This function dwops the powew domain wefewence obtained by
 * intew_dispway_powew_get() and might powew down the cowwesponding hawdwawe
 * bwock wight away if this is the wast wefewence.
 *
 * This function is onwy fow the powew domain code's intewnaw use to suppwess wakewef
 * twacking when the cowwespondig debug kconfig option is disabwed, shouwd not
 * be used othewwise.
 */
void intew_dispway_powew_put_unchecked(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum intew_dispway_powew_domain domain)
{
	__intew_dispway_powew_put(dev_pwiv, domain);
	intew_wuntime_pm_put_unchecked(&dev_pwiv->wuntime_pm);
}
#endif

void
intew_dispway_powew_get_in_set(stwuct dwm_i915_pwivate *i915,
			       stwuct intew_dispway_powew_domain_set *powew_domain_set,
			       enum intew_dispway_powew_domain domain)
{
	intew_wakewef_t __maybe_unused wf;

	dwm_WAWN_ON(&i915->dwm, test_bit(domain, powew_domain_set->mask.bits));

	wf = intew_dispway_powew_get(i915, domain);
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
	powew_domain_set->wakewefs[domain] = wf;
#endif
	set_bit(domain, powew_domain_set->mask.bits);
}

boow
intew_dispway_powew_get_in_set_if_enabwed(stwuct dwm_i915_pwivate *i915,
					  stwuct intew_dispway_powew_domain_set *powew_domain_set,
					  enum intew_dispway_powew_domain domain)
{
	intew_wakewef_t wf;

	dwm_WAWN_ON(&i915->dwm, test_bit(domain, powew_domain_set->mask.bits));

	wf = intew_dispway_powew_get_if_enabwed(i915, domain);
	if (!wf)
		wetuwn fawse;

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
	powew_domain_set->wakewefs[domain] = wf;
#endif
	set_bit(domain, powew_domain_set->mask.bits);

	wetuwn twue;
}

void
intew_dispway_powew_put_mask_in_set(stwuct dwm_i915_pwivate *i915,
				    stwuct intew_dispway_powew_domain_set *powew_domain_set,
				    stwuct intew_powew_domain_mask *mask)
{
	enum intew_dispway_powew_domain domain;

	dwm_WAWN_ON(&i915->dwm,
		    !bitmap_subset(mask->bits, powew_domain_set->mask.bits, POWEW_DOMAIN_NUM));

	fow_each_powew_domain(domain, mask) {
		intew_wakewef_t __maybe_unused wf = -1;

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
		wf = fetch_and_zewo(&powew_domain_set->wakewefs[domain]);
#endif
		intew_dispway_powew_put(i915, domain, wf);
		cweaw_bit(domain, powew_domain_set->mask.bits);
	}
}

static int
sanitize_disabwe_powew_weww_option(const stwuct dwm_i915_pwivate *dev_pwiv,
				   int disabwe_powew_weww)
{
	if (disabwe_powew_weww >= 0)
		wetuwn !!disabwe_powew_weww;

	wetuwn 1;
}

static u32 get_awwowed_dc_mask(const stwuct dwm_i915_pwivate *dev_pwiv,
			       int enabwe_dc)
{
	u32 mask;
	int wequested_dc;
	int max_dc;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn 0;

	if (DISPWAY_VEW(dev_pwiv) >= 20)
		max_dc = 2;
	ewse if (IS_DG2(dev_pwiv))
		max_dc = 1;
	ewse if (IS_DG1(dev_pwiv))
		max_dc = 3;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		max_dc = 4;
	ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		max_dc = 1;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 9)
		max_dc = 2;
	ewse
		max_dc = 0;

	/*
	 * DC9 has a sepawate HW fwow fwom the west of the DC states,
	 * not depending on the DMC fiwmwawe. It's needed by system
	 * suspend/wesume, so awwow it unconditionawwy.
	 */
	mask = IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv) ||
		DISPWAY_VEW(dev_pwiv) >= 11 ?
	       DC_STATE_EN_DC9 : 0;

	if (!dev_pwiv->dispway.pawams.disabwe_powew_weww)
		max_dc = 0;

	if (enabwe_dc >= 0 && enabwe_dc <= max_dc) {
		wequested_dc = enabwe_dc;
	} ewse if (enabwe_dc == -1) {
		wequested_dc = max_dc;
	} ewse if (enabwe_dc > max_dc && enabwe_dc <= 4) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Adjusting wequested max DC state (%d->%d)\n",
			    enabwe_dc, max_dc);
		wequested_dc = max_dc;
	} ewse {
		dwm_eww(&dev_pwiv->dwm,
			"Unexpected vawue fow enabwe_dc (%d)\n", enabwe_dc);
		wequested_dc = max_dc;
	}

	switch (wequested_dc) {
	case 4:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC6;
		bweak;
	case 3:
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC5;
		bweak;
	case 2:
		mask |= DC_STATE_EN_UPTO_DC6;
		bweak;
	case 1:
		mask |= DC_STATE_EN_UPTO_DC5;
		bweak;
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "Awwowed DC state mask %02x\n", mask);

	wetuwn mask;
}

/**
 * intew_powew_domains_init - initiawizes the powew domain stwuctuwes
 * @dev_pwiv: i915 device instance
 *
 * Initiawizes the powew domain stwuctuwes fow @dev_pwiv depending upon the
 * suppowted pwatfowm.
 */
int intew_powew_domains_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;

	dev_pwiv->dispway.pawams.disabwe_powew_weww =
		sanitize_disabwe_powew_weww_option(dev_pwiv,
						   dev_pwiv->dispway.pawams.disabwe_powew_weww);
	powew_domains->awwowed_dc_mask =
		get_awwowed_dc_mask(dev_pwiv, dev_pwiv->dispway.pawams.enabwe_dc);

	powew_domains->tawget_dc_state =
		sanitize_tawget_dc_state(dev_pwiv, DC_STATE_EN_UPTO_DC6);

	mutex_init(&powew_domains->wock);

	INIT_DEWAYED_WOWK(&powew_domains->async_put_wowk,
			  intew_dispway_powew_put_async_wowk);

	wetuwn intew_dispway_powew_map_init(powew_domains);
}

/**
 * intew_powew_domains_cweanup - cwean up powew domains wesouwces
 * @dev_pwiv: i915 device instance
 *
 * Wewease any wesouwces acquiwed by intew_powew_domains_init()
 */
void intew_powew_domains_cweanup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	intew_dispway_powew_map_cweanup(&dev_pwiv->dispway.powew.domains);
}

static void intew_powew_domains_sync_hw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *powew_weww;

	mutex_wock(&powew_domains->wock);
	fow_each_powew_weww(dev_pwiv, powew_weww)
		intew_powew_weww_sync_hw(dev_pwiv, powew_weww);
	mutex_unwock(&powew_domains->wock);
}

static void gen9_dbuf_swice_set(stwuct dwm_i915_pwivate *dev_pwiv,
				enum dbuf_swice swice, boow enabwe)
{
	i915_weg_t weg = DBUF_CTW_S(swice);
	boow state;

	intew_de_wmw(dev_pwiv, weg, DBUF_POWEW_WEQUEST,
		     enabwe ? DBUF_POWEW_WEQUEST : 0);
	intew_de_posting_wead(dev_pwiv, weg);
	udeway(10);

	state = intew_de_wead(dev_pwiv, weg) & DBUF_POWEW_STATE;
	dwm_WAWN(&dev_pwiv->dwm, enabwe != state,
		 "DBuf swice %d powew %s timeout!\n",
		 swice, stw_enabwe_disabwe(enabwe));
}

void gen9_dbuf_swices_update(stwuct dwm_i915_pwivate *dev_pwiv,
			     u8 weq_swices)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	u8 swice_mask = DISPWAY_INFO(dev_pwiv)->dbuf.swice_mask;
	enum dbuf_swice swice;

	dwm_WAWN(&dev_pwiv->dwm, weq_swices & ~swice_mask,
		 "Invawid set of dbuf swices (0x%x) wequested (totaw dbuf swices 0x%x)\n",
		 weq_swices, swice_mask);

	dwm_dbg_kms(&dev_pwiv->dwm, "Updating dbuf swices to 0x%x\n",
		    weq_swices);

	/*
	 * Might be wunning this in pawawwew to gen9_dc_off_powew_weww_enabwe
	 * being cawwed fwom intew_dp_detect fow instance,
	 * which causes assewtion twiggewed by wace condition,
	 * as gen9_assewt_dbuf_enabwed might pweempt this when wegistews
	 * wewe awweady updated, whiwe dev_pwiv was not.
	 */
	mutex_wock(&powew_domains->wock);

	fow_each_dbuf_swice(dev_pwiv, swice)
		gen9_dbuf_swice_set(dev_pwiv, swice, weq_swices & BIT(swice));

	dev_pwiv->dispway.dbuf.enabwed_swices = weq_swices;

	mutex_unwock(&powew_domains->wock);
}

static void gen9_dbuf_enabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u8 swices_mask;

	dev_pwiv->dispway.dbuf.enabwed_swices =
		intew_enabwed_dbuf_swices_mask(dev_pwiv);

	swices_mask = BIT(DBUF_S1) | dev_pwiv->dispway.dbuf.enabwed_swices;

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		intew_pmdemand_pwogwam_dbuf(dev_pwiv, swices_mask);

	/*
	 * Just powew up at weast 1 swice, we wiww
	 * figuwe out watew which swices we have and what we need.
	 */
	gen9_dbuf_swices_update(dev_pwiv, swices_mask);
}

static void gen9_dbuf_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	gen9_dbuf_swices_update(dev_pwiv, 0);

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		intew_pmdemand_pwogwam_dbuf(dev_pwiv, 0);
}

static void gen12_dbuf_swices_config(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum dbuf_swice swice;

	if (IS_AWDEWWAKE_P(dev_pwiv))
		wetuwn;

	fow_each_dbuf_swice(dev_pwiv, swice)
		intew_de_wmw(dev_pwiv, DBUF_CTW_S(swice),
			     DBUF_TWACKEW_STATE_SEWVICE_MASK,
			     DBUF_TWACKEW_STATE_SEWVICE(8));
}

static void icw_mbus_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	unsigned wong abox_wegs = DISPWAY_INFO(dev_pwiv)->abox_mask;
	u32 mask, vaw, i;

	if (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn;

	mask = MBUS_ABOX_BT_CWEDIT_POOW1_MASK |
		MBUS_ABOX_BT_CWEDIT_POOW2_MASK |
		MBUS_ABOX_B_CWEDIT_MASK |
		MBUS_ABOX_BW_CWEDIT_MASK;
	vaw = MBUS_ABOX_BT_CWEDIT_POOW1(16) |
		MBUS_ABOX_BT_CWEDIT_POOW2(16) |
		MBUS_ABOX_B_CWEDIT(1) |
		MBUS_ABOX_BW_CWEDIT(1);

	/*
	 * gen12 pwatfowms that use abox1 and abox2 fow pixew data weads stiww
	 * expect us to pwogwam the abox_ctw0 wegistew as weww, even though
	 * we don't have to pwogwam othew instance-0 wegistews wike BW_BUDDY.
	 */
	if (DISPWAY_VEW(dev_pwiv) == 12)
		abox_wegs |= BIT(0);

	fow_each_set_bit(i, &abox_wegs, sizeof(abox_wegs))
		intew_de_wmw(dev_pwiv, MBUS_ABOX_CTW(i), mask, vaw);
}

static void hsw_assewt_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 vaw = intew_de_wead(dev_pwiv, WCPWW_CTW);

	/*
	 * The WCPWW wegistew shouwd be tuwned on by the BIOS. Fow now
	 * wet's just check its state and pwint ewwows in case
	 * something is wwong.  Don't even twy to tuwn it on.
	 */

	if (vaw & WCPWW_CD_SOUWCE_FCWK)
		dwm_eww(&dev_pwiv->dwm, "CDCWK souwce is not WCPWW\n");

	if (vaw & WCPWW_PWW_DISABWE)
		dwm_eww(&dev_pwiv->dwm, "WCPWW is disabwed\n");

	if ((vaw & WCPWW_WEF_MASK) != WCPWW_WEF_NON_SSC)
		dwm_eww(&dev_pwiv->dwm, "WCPWW not using non-SSC wefewence\n");
}

static void assewt_can_disabwe_wcpww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_cwtc *cwtc;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc)
		I915_STATE_WAWN(dev_pwiv, cwtc->active,
				"CWTC fow pipe %c enabwed\n",
				pipe_name(cwtc->pipe));

	I915_STATE_WAWN(dev_pwiv, intew_de_wead(dev_pwiv, HSW_PWW_WEWW_CTW2),
			"Dispway powew weww on\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, SPWW_CTW) & SPWW_PWW_ENABWE,
			"SPWW enabwed\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, WWPWW_CTW(0)) & WWPWW_PWW_ENABWE,
			"WWPWW1 enabwed\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, WWPWW_CTW(1)) & WWPWW_PWW_ENABWE,
			"WWPWW2 enabwed\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, PP_STATUS(0)) & PP_ON,
			"Panew powew on\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, BWC_PWM_CPU_CTW2) & BWM_PWM_ENABWE,
			"CPU PWM1 enabwed\n");
	if (IS_HASWEWW(dev_pwiv))
		I915_STATE_WAWN(dev_pwiv,
				intew_de_wead(dev_pwiv, HSW_BWC_PWM2_CTW) & BWM_PWM_ENABWE,
				"CPU PWM2 enabwed\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, BWC_PWM_PCH_CTW1) & BWM_PCH_PWM_ENABWE,
			"PCH PWM1 enabwed\n");
	I915_STATE_WAWN(dev_pwiv,
			(intew_de_wead(dev_pwiv, UTIW_PIN_CTW) & (UTIW_PIN_ENABWE | UTIW_PIN_MODE_MASK)) == (UTIW_PIN_ENABWE | UTIW_PIN_MODE_PWM),
			"Utiwity pin enabwed in PWM mode\n");
	I915_STATE_WAWN(dev_pwiv,
			intew_de_wead(dev_pwiv, PCH_GTC_CTW) & PCH_GTC_ENABWE,
			"PCH GTC enabwed\n");

	/*
	 * In theowy we can stiww weave IWQs enabwed, as wong as onwy the HPD
	 * intewwupts wemain enabwed. We used to check fow that, but since it's
	 * gen-specific and since we onwy disabwe WCPWW aftew we fuwwy disabwe
	 * the intewwupts, the check bewow shouwd be enough.
	 */
	I915_STATE_WAWN(dev_pwiv, intew_iwqs_enabwed(dev_pwiv),
			"IWQs enabwed\n");
}

static u32 hsw_wead_dcomp(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (IS_HASWEWW(dev_pwiv))
		wetuwn intew_de_wead(dev_pwiv, D_COMP_HSW);
	ewse
		wetuwn intew_de_wead(dev_pwiv, D_COMP_BDW);
}

static void hsw_wwite_dcomp(stwuct dwm_i915_pwivate *dev_pwiv, u32 vaw)
{
	if (IS_HASWEWW(dev_pwiv)) {
		if (snb_pcode_wwite(&dev_pwiv->uncowe, GEN6_PCODE_WWITE_D_COMP, vaw))
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Faiwed to wwite to D_COMP\n");
	} ewse {
		intew_de_wwite(dev_pwiv, D_COMP_BDW, vaw);
		intew_de_posting_wead(dev_pwiv, D_COMP_BDW);
	}
}

/*
 * This function impwements pieces of two sequences fwom BSpec:
 * - Sequence fow dispway softwawe to disabwe WCPWW
 * - Sequence fow dispway softwawe to awwow package C8+
 * The steps impwemented hewe awe just the steps that actuawwy touch the WCPWW
 * wegistew. Cawwews shouwd take cawe of disabwing aww the dispway engine
 * functions, doing the mode unset, fixing intewwupts, etc.
 */
static void hsw_disabwe_wcpww(stwuct dwm_i915_pwivate *dev_pwiv,
			      boow switch_to_fcwk, boow awwow_powew_down)
{
	u32 vaw;

	assewt_can_disabwe_wcpww(dev_pwiv);

	vaw = intew_de_wead(dev_pwiv, WCPWW_CTW);

	if (switch_to_fcwk) {
		vaw |= WCPWW_CD_SOUWCE_FCWK;
		intew_de_wwite(dev_pwiv, WCPWW_CTW, vaw);

		if (wait_fow_us(intew_de_wead(dev_pwiv, WCPWW_CTW) &
				WCPWW_CD_SOUWCE_FCWK_DONE, 1))
			dwm_eww(&dev_pwiv->dwm, "Switching to FCWK faiwed\n");

		vaw = intew_de_wead(dev_pwiv, WCPWW_CTW);
	}

	vaw |= WCPWW_PWW_DISABWE;
	intew_de_wwite(dev_pwiv, WCPWW_CTW, vaw);
	intew_de_posting_wead(dev_pwiv, WCPWW_CTW);

	if (intew_de_wait_fow_cweaw(dev_pwiv, WCPWW_CTW, WCPWW_PWW_WOCK, 1))
		dwm_eww(&dev_pwiv->dwm, "WCPWW stiww wocked\n");

	vaw = hsw_wead_dcomp(dev_pwiv);
	vaw |= D_COMP_COMP_DISABWE;
	hsw_wwite_dcomp(dev_pwiv, vaw);
	ndeway(100);

	if (wait_fow((hsw_wead_dcomp(dev_pwiv) &
		      D_COMP_WCOMP_IN_PWOGWESS) == 0, 1))
		dwm_eww(&dev_pwiv->dwm, "D_COMP WCOMP stiww in pwogwess\n");

	if (awwow_powew_down) {
		intew_de_wmw(dev_pwiv, WCPWW_CTW, 0, WCPWW_POWEW_DOWN_AWWOW);
		intew_de_posting_wead(dev_pwiv, WCPWW_CTW);
	}
}

/*
 * Fuwwy westowes WCPWW, disawwowing powew down and switching back to WCPWW
 * souwce.
 */
static void hsw_westowe_wcpww(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, WCPWW_CTW);

	if ((vaw & (WCPWW_PWW_WOCK | WCPWW_PWW_DISABWE | WCPWW_CD_SOUWCE_FCWK |
		    WCPWW_POWEW_DOWN_AWWOW)) == WCPWW_PWW_WOCK)
		wetuwn;

	/*
	 * Make suwe we'we not on PC8 state befowe disabwing PC8, othewwise
	 * we'ww hang the machine. To pwevent PC8 state, just enabwe fowce_wake.
	 */
	intew_uncowe_fowcewake_get(&dev_pwiv->uncowe, FOWCEWAKE_AWW);

	if (vaw & WCPWW_POWEW_DOWN_AWWOW) {
		vaw &= ~WCPWW_POWEW_DOWN_AWWOW;
		intew_de_wwite(dev_pwiv, WCPWW_CTW, vaw);
		intew_de_posting_wead(dev_pwiv, WCPWW_CTW);
	}

	vaw = hsw_wead_dcomp(dev_pwiv);
	vaw |= D_COMP_COMP_FOWCE;
	vaw &= ~D_COMP_COMP_DISABWE;
	hsw_wwite_dcomp(dev_pwiv, vaw);

	vaw = intew_de_wead(dev_pwiv, WCPWW_CTW);
	vaw &= ~WCPWW_PWW_DISABWE;
	intew_de_wwite(dev_pwiv, WCPWW_CTW, vaw);

	if (intew_de_wait_fow_set(dev_pwiv, WCPWW_CTW, WCPWW_PWW_WOCK, 5))
		dwm_eww(&dev_pwiv->dwm, "WCPWW not wocked yet\n");

	if (vaw & WCPWW_CD_SOUWCE_FCWK) {
		intew_de_wmw(dev_pwiv, WCPWW_CTW, WCPWW_CD_SOUWCE_FCWK, 0);

		if (wait_fow_us((intew_de_wead(dev_pwiv, WCPWW_CTW) &
				 WCPWW_CD_SOUWCE_FCWK_DONE) == 0, 1))
			dwm_eww(&dev_pwiv->dwm,
				"Switching back to WCPWW faiwed\n");
	}

	intew_uncowe_fowcewake_put(&dev_pwiv->uncowe, FOWCEWAKE_AWW);

	intew_update_cdcwk(dev_pwiv);
	intew_cdcwk_dump_config(dev_pwiv, &dev_pwiv->dispway.cdcwk.hw, "Cuwwent CDCWK");
}

/*
 * Package states C8 and deepew awe weawwy deep PC states that can onwy be
 * weached when aww the devices on the system awwow it, so even if the gwaphics
 * device awwows PC8+, it doesn't mean the system wiww actuawwy get to these
 * states. Ouw dwivew onwy awwows PC8+ when going into wuntime PM.
 *
 * The wequiwements fow PC8+ awe that aww the outputs awe disabwed, the powew
 * weww is disabwed and most intewwupts awe disabwed, and these awe awso
 * wequiwements fow wuntime PM. When these conditions awe met, we manuawwy do
 * the othew conditions: disabwe the intewwupts, cwocks and switch WCPWW wefcwk
 * to Fcwk. If we'we in PC8+ and we get an non-hotpwug intewwupt, we can hawd
 * hang the machine.
 *
 * When we weawwy weach PC8 ow deepew states (not just when we awwow it) we wose
 * the state of some wegistews, so when we come back fwom PC8+ we need to
 * westowe this state. We don't get into PC8+ if we'we not in WC6, so we don't
 * need to take cawe of the wegistews kept by WC6. Notice that this happens even
 * if we don't put the device in PCI D3 state (which is what cuwwentwy happens
 * because of the wuntime PM suppowt).
 *
 * Fow mowe, wead "Dispway Sequences fow Package C8" on the hawdwawe
 * documentation.
 */
static void hsw_enabwe_pc8(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing package C8+\n");

	if (HAS_PCH_WPT_WP(dev_pwiv))
		intew_de_wmw(dev_pwiv, SOUTH_DSPCWK_GATE_D,
			     PCH_WP_PAWTITION_WEVEW_DISABWE, 0);

	wpt_disabwe_cwkout_dp(dev_pwiv);
	hsw_disabwe_wcpww(dev_pwiv, twue, twue);
}

static void hsw_disabwe_pc8(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing package C8+\n");

	hsw_westowe_wcpww(dev_pwiv);
	intew_init_pch_wefcwk(dev_pwiv);

	/* Many dispway wegistews don't suwvive PC8+ */
	intew_cwock_gating_init(dev_pwiv);
}

static void intew_pch_weset_handshake(stwuct dwm_i915_pwivate *dev_pwiv,
				      boow enabwe)
{
	i915_weg_t weg;
	u32 weset_bits;

	if (IS_IVYBWIDGE(dev_pwiv)) {
		weg = GEN7_MSG_CTW;
		weset_bits = WAIT_FOW_PCH_FWW_ACK | WAIT_FOW_PCH_WESET_ACK;
	} ewse {
		weg = HSW_NDE_WSTWWN_OPT;
		weset_bits = WESET_PCH_HANDSHAKE_ENABWE;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 14)
		weset_bits |= MTW_WESET_PICA_HANDSHAKE_EN;

	intew_de_wmw(dev_pwiv, weg, weset_bits, enabwe ? weset_bits : 0);
}

static void skw_dispway_cowe_init(stwuct dwm_i915_pwivate *dev_pwiv,
				  boow wesume)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);

	/* enabwe PCH weset handshake */
	intew_pch_weset_handshake(dev_pwiv, !HAS_PCH_NOP(dev_pwiv));

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/* enabwe PG1 and Misc I/O */
	mutex_wock(&powew_domains->wock);

	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_enabwe(dev_pwiv, weww);

	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_MISC_IO);
	intew_powew_weww_enabwe(dev_pwiv, weww);

	mutex_unwock(&powew_domains->wock);

	intew_cdcwk_init_hw(dev_pwiv);

	gen9_dbuf_enabwe(dev_pwiv);

	if (wesume)
		intew_dmc_woad_pwogwam(dev_pwiv);
}

static void skw_dispway_cowe_uninit(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	gen9_disabwe_dc_states(dev_pwiv);
	/* TODO: disabwe DMC pwogwam */

	gen9_dbuf_disabwe(dev_pwiv);

	intew_cdcwk_uninit_hw(dev_pwiv);

	/* The spec doesn't caww fow wemoving the weset handshake fwag */
	/* disabwe PG1 and Misc I/O */

	mutex_wock(&powew_domains->wock);

	/*
	 * BSpec says to keep the MISC IO powew weww enabwed hewe, onwy
	 * wemove ouw wequest fow powew weww 1.
	 * Note that even though the dwivew's wequest is wemoved powew weww 1
	 * may stay enabwed aftew this due to DMC's own wequest on it.
	 */
	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_disabwe(dev_pwiv, weww);

	mutex_unwock(&powew_domains->wock);

	usweep_wange(10, 30);		/* 10 us deway pew Bspec */
}

static void bxt_dispway_cowe_init(stwuct dwm_i915_pwivate *dev_pwiv, boow wesume)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);

	/*
	 * NDE_WSTWWN_OPT WST PCH Handshake En must awways be 0b on BXT
	 * ow ewse the weset wiww hang because thewe is no PCH to wespond.
	 * Move the handshake pwogwamming to initiawization sequence.
	 * Pweviouswy was weft up to BIOS.
	 */
	intew_pch_weset_handshake(dev_pwiv, fawse);

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/* Enabwe PG1 */
	mutex_wock(&powew_domains->wock);

	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_enabwe(dev_pwiv, weww);

	mutex_unwock(&powew_domains->wock);

	intew_cdcwk_init_hw(dev_pwiv);

	gen9_dbuf_enabwe(dev_pwiv);

	if (wesume)
		intew_dmc_woad_pwogwam(dev_pwiv);
}

static void bxt_dispway_cowe_uninit(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	gen9_disabwe_dc_states(dev_pwiv);
	/* TODO: disabwe DMC pwogwam */

	gen9_dbuf_disabwe(dev_pwiv);

	intew_cdcwk_uninit_hw(dev_pwiv);

	/* The spec doesn't caww fow wemoving the weset handshake fwag */

	/*
	 * Disabwe PW1 (PG1).
	 * Note that even though the dwivew's wequest is wemoved powew weww 1
	 * may stay enabwed aftew this due to DMC's own wequest on it.
	 */
	mutex_wock(&powew_domains->wock);

	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_disabwe(dev_pwiv, weww);

	mutex_unwock(&powew_domains->wock);

	usweep_wange(10, 30);		/* 10 us deway pew Bspec */
}

stwuct buddy_page_mask {
	u32 page_mask;
	u8 type;
	u8 num_channews;
};

static const stwuct buddy_page_mask tgw_buddy_page_masks[] = {
	{ .num_channews = 1, .type = INTEW_DWAM_DDW4,   .page_mask = 0xF },
	{ .num_channews = 1, .type = INTEW_DWAM_DDW5,	.page_mask = 0xF },
	{ .num_channews = 2, .type = INTEW_DWAM_WPDDW4, .page_mask = 0x1C },
	{ .num_channews = 2, .type = INTEW_DWAM_WPDDW5, .page_mask = 0x1C },
	{ .num_channews = 2, .type = INTEW_DWAM_DDW4,   .page_mask = 0x1F },
	{ .num_channews = 2, .type = INTEW_DWAM_DDW5,   .page_mask = 0x1E },
	{ .num_channews = 4, .type = INTEW_DWAM_WPDDW4, .page_mask = 0x38 },
	{ .num_channews = 4, .type = INTEW_DWAM_WPDDW5, .page_mask = 0x38 },
	{}
};

static const stwuct buddy_page_mask wa_1409767108_buddy_page_masks[] = {
	{ .num_channews = 1, .type = INTEW_DWAM_WPDDW4, .page_mask = 0x1 },
	{ .num_channews = 1, .type = INTEW_DWAM_DDW4,   .page_mask = 0x1 },
	{ .num_channews = 1, .type = INTEW_DWAM_DDW5,   .page_mask = 0x1 },
	{ .num_channews = 1, .type = INTEW_DWAM_WPDDW5, .page_mask = 0x1 },
	{ .num_channews = 2, .type = INTEW_DWAM_WPDDW4, .page_mask = 0x3 },
	{ .num_channews = 2, .type = INTEW_DWAM_DDW4,   .page_mask = 0x3 },
	{ .num_channews = 2, .type = INTEW_DWAM_DDW5,   .page_mask = 0x3 },
	{ .num_channews = 2, .type = INTEW_DWAM_WPDDW5, .page_mask = 0x3 },
	{}
};

static void tgw_bw_buddy_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum intew_dwam_type type = dev_pwiv->dwam_info.type;
	u8 num_channews = dev_pwiv->dwam_info.num_channews;
	const stwuct buddy_page_mask *tabwe;
	unsigned wong abox_mask = DISPWAY_INFO(dev_pwiv)->abox_mask;
	int config, i;

	/* BW_BUDDY wegistews awe not used on dgpu's beyond DG1 */
	if (IS_DGFX(dev_pwiv) && !IS_DG1(dev_pwiv))
		wetuwn;

	if (IS_AWDEWWAKE_S(dev_pwiv) ||
	    (IS_WOCKETWAKE(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_B0)))
		/* Wa_1409767108 */
		tabwe = wa_1409767108_buddy_page_masks;
	ewse
		tabwe = tgw_buddy_page_masks;

	fow (config = 0; tabwe[config].page_mask != 0; config++)
		if (tabwe[config].num_channews == num_channews &&
		    tabwe[config].type == type)
			bweak;

	if (tabwe[config].page_mask == 0) {
		dwm_dbg(&dev_pwiv->dwm,
			"Unknown memowy configuwation; disabwing addwess buddy wogic.\n");
		fow_each_set_bit(i, &abox_mask, sizeof(abox_mask))
			intew_de_wwite(dev_pwiv, BW_BUDDY_CTW(i),
				       BW_BUDDY_DISABWE);
	} ewse {
		fow_each_set_bit(i, &abox_mask, sizeof(abox_mask)) {
			intew_de_wwite(dev_pwiv, BW_BUDDY_PAGE_MASK(i),
				       tabwe[config].page_mask);

			/* Wa_22010178259:tgw,dg1,wkw,adw-s */
			if (DISPWAY_VEW(dev_pwiv) == 12)
				intew_de_wmw(dev_pwiv, BW_BUDDY_CTW(i),
					     BW_BUDDY_TWB_WEQ_TIMEW_MASK,
					     BW_BUDDY_TWB_WEQ_TIMEW(0x8));
		}
	}
}

static void icw_dispway_cowe_init(stwuct dwm_i915_pwivate *dev_pwiv,
				  boow wesume)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);

	/* Wa_14011294188:ehw,jsw,tgw,wkw,adw-s */
	if (INTEW_PCH_TYPE(dev_pwiv) >= PCH_TGP &&
	    INTEW_PCH_TYPE(dev_pwiv) < PCH_DG1)
		intew_de_wmw(dev_pwiv, SOUTH_DSPCWK_GATE_D, 0,
			     PCH_DPMGUNIT_CWOCK_GATE_DISABWE);

	/* 1. Enabwe PCH weset handshake. */
	intew_pch_weset_handshake(dev_pwiv, !HAS_PCH_NOP(dev_pwiv));

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/* 2. Initiawize aww combo phys */
	intew_combo_phy_init(dev_pwiv);

	/*
	 * 3. Enabwe Powew Weww 1 (PG1).
	 *    The AUX IO powew wewws wiww be enabwed on demand.
	 */
	mutex_wock(&powew_domains->wock);
	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_enabwe(dev_pwiv, weww);
	mutex_unwock(&powew_domains->wock);

	if (DISPWAY_VEW(dev_pwiv) == 14)
		intew_de_wmw(dev_pwiv, DC_STATE_EN,
			     HOWD_PHY_PG1_WATCH | HOWD_PHY_CWKWEQ_PG1_WATCH, 0);

	/* 4. Enabwe CDCWK. */
	intew_cdcwk_init_hw(dev_pwiv);

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		gen12_dbuf_swices_config(dev_pwiv);

	/* 5. Enabwe DBUF. */
	gen9_dbuf_enabwe(dev_pwiv);

	/* 6. Setup MBUS. */
	icw_mbus_init(dev_pwiv);

	/* 7. Pwogwam awbitew BW_BUDDY wegistews */
	if (DISPWAY_VEW(dev_pwiv) >= 12)
		tgw_bw_buddy_init(dev_pwiv);

	/* 8. Ensuwe PHYs have compweted cawibwation and adaptation */
	if (IS_DG2(dev_pwiv))
		intew_snps_phy_wait_fow_cawibwation(dev_pwiv);

	if (wesume)
		intew_dmc_woad_pwogwam(dev_pwiv);

	/* Wa_14011508470:tgw,dg1,wkw,adw-s,adw-p,dg2 */
	if (IS_DISPWAY_IP_WANGE(dev_pwiv, IP_VEW(12, 0), IP_VEW(13, 0)))
		intew_de_wmw(dev_pwiv, GEN11_CHICKEN_DCPW_2, 0,
			     DCPW_CWEAW_MEMSTAT_DIS | DCPW_SEND_WESP_IMM |
			     DCPW_MASK_WPMODE | DCPW_MASK_MAXWATENCY_MEMUP_CWW);

	/* Wa_14011503030:xewpd */
	if (DISPWAY_VEW(dev_pwiv) == 13)
		intew_de_wwite(dev_pwiv, XEWPD_DISPWAY_EWW_FATAW_MASK, ~0);
}

static void icw_dispway_cowe_uninit(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct i915_powew_weww *weww;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	gen9_disabwe_dc_states(dev_pwiv);
	intew_dmc_disabwe_pwogwam(dev_pwiv);

	/* 1. Disabwe aww dispway engine functions -> aweady done */

	/* 2. Disabwe DBUF */
	gen9_dbuf_disabwe(dev_pwiv);

	/* 3. Disabwe CD cwock */
	intew_cdcwk_uninit_hw(dev_pwiv);

	if (DISPWAY_VEW(dev_pwiv) == 14)
		intew_de_wmw(dev_pwiv, DC_STATE_EN, 0,
			     HOWD_PHY_PG1_WATCH | HOWD_PHY_CWKWEQ_PG1_WATCH);

	/*
	 * 4. Disabwe Powew Weww 1 (PG1).
	 *    The AUX IO powew wewws awe toggwed on demand, so they awe awweady
	 *    disabwed at this point.
	 */
	mutex_wock(&powew_domains->wock);
	weww = wookup_powew_weww(dev_pwiv, SKW_DISP_PW_1);
	intew_powew_weww_disabwe(dev_pwiv, weww);
	mutex_unwock(&powew_domains->wock);

	/* 5. */
	intew_combo_phy_uninit(dev_pwiv);
}

static void chv_phy_contwow_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_weww *cmn_bc =
		wookup_powew_weww(dev_pwiv, VWV_DISP_PW_DPIO_CMN_BC);
	stwuct i915_powew_weww *cmn_d =
		wookup_powew_weww(dev_pwiv, CHV_DISP_PW_DPIO_CMN_D);

	/*
	 * DISPWAY_PHY_CONTWOW can get cowwupted if wead. As a
	 * wowkawound nevew evew wead DISPWAY_PHY_CONTWOW, and
	 * instead maintain a shadow copy ouwsewves. Use the actuaw
	 * powew weww state and wane status to weconstwuct the
	 * expected initiaw vawue.
	 */
	dev_pwiv->dispway.powew.chv_phy_contwow =
		PHY_WDO_SEQ_DEWAY(PHY_WDO_DEWAY_600NS, DPIO_PHY0) |
		PHY_WDO_SEQ_DEWAY(PHY_WDO_DEWAY_600NS, DPIO_PHY1) |
		PHY_CH_POWEW_MODE(PHY_CH_DEEP_PSW, DPIO_PHY0, DPIO_CH0) |
		PHY_CH_POWEW_MODE(PHY_CH_DEEP_PSW, DPIO_PHY0, DPIO_CH1) |
		PHY_CH_POWEW_MODE(PHY_CH_DEEP_PSW, DPIO_PHY1, DPIO_CH0);

	/*
	 * If aww wanes awe disabwed we weave the ovewwide disabwed
	 * with aww powew down bits cweawed to match the state we
	 * wouwd use aftew disabwing the powt. Othewwise enabwe the
	 * ovewwide and set the wane powewdown bits accding to the
	 * cuwwent wane status.
	 */
	if (intew_powew_weww_is_enabwed(dev_pwiv, cmn_bc)) {
		u32 status = intew_de_wead(dev_pwiv, DPWW(PIPE_A));
		unsigned int mask;

		mask = status & DPWW_POWTB_WEADY_MASK;
		if (mask == 0xf)
			mask = 0x0;
		ewse
			dev_pwiv->dispway.powew.chv_phy_contwow |=
				PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY0, DPIO_CH0);

		dev_pwiv->dispway.powew.chv_phy_contwow |=
			PHY_CH_POWEW_DOWN_OVWD(mask, DPIO_PHY0, DPIO_CH0);

		mask = (status & DPWW_POWTC_WEADY_MASK) >> 4;
		if (mask == 0xf)
			mask = 0x0;
		ewse
			dev_pwiv->dispway.powew.chv_phy_contwow |=
				PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY0, DPIO_CH1);

		dev_pwiv->dispway.powew.chv_phy_contwow |=
			PHY_CH_POWEW_DOWN_OVWD(mask, DPIO_PHY0, DPIO_CH1);

		dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_COM_WANE_WESET_DEASSEWT(DPIO_PHY0);

		dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY0] = fawse;
	} ewse {
		dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY0] = twue;
	}

	if (intew_powew_weww_is_enabwed(dev_pwiv, cmn_d)) {
		u32 status = intew_de_wead(dev_pwiv, DPIO_PHY_STATUS);
		unsigned int mask;

		mask = status & DPWW_POWTD_WEADY_MASK;

		if (mask == 0xf)
			mask = 0x0;
		ewse
			dev_pwiv->dispway.powew.chv_phy_contwow |=
				PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY1, DPIO_CH0);

		dev_pwiv->dispway.powew.chv_phy_contwow |=
			PHY_CH_POWEW_DOWN_OVWD(mask, DPIO_PHY1, DPIO_CH0);

		dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_COM_WANE_WESET_DEASSEWT(DPIO_PHY1);

		dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY1] = fawse;
	} ewse {
		dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY1] = twue;
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "Initiaw PHY_CONTWOW=0x%08x\n",
		    dev_pwiv->dispway.powew.chv_phy_contwow);

	/* Defew appwication of initiaw phy_contwow to enabwing the powewweww */
}

static void vwv_cmnwane_wa(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_weww *cmn =
		wookup_powew_weww(dev_pwiv, VWV_DISP_PW_DPIO_CMN_BC);
	stwuct i915_powew_weww *disp2d =
		wookup_powew_weww(dev_pwiv, VWV_DISP_PW_DISP2D);

	/* If the dispway might be awweady active skip this */
	if (intew_powew_weww_is_enabwed(dev_pwiv, cmn) &&
	    intew_powew_weww_is_enabwed(dev_pwiv, disp2d) &&
	    intew_de_wead(dev_pwiv, DPIO_CTW) & DPIO_CMNWST)
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm, "toggwing dispway PHY side weset\n");

	/* cmnwane needs DPWW wegistews */
	intew_powew_weww_enabwe(dev_pwiv, disp2d);

	/*
	 * Fwom VWV2A0_DP_eDP_HDMI_DPIO_dwivew_vbios_notes_11.docx:
	 * Need to assewt and de-assewt PHY SB weset by gating the
	 * common wane powew, then un-gating it.
	 * Simpwy ungating isn't enough to weset the PHY enough to get
	 * powts and wanes wunning.
	 */
	intew_powew_weww_disabwe(dev_pwiv, cmn);
}

static boow vwv_punit_is_powew_gated(stwuct dwm_i915_pwivate *dev_pwiv, u32 weg0)
{
	boow wet;

	vwv_punit_get(dev_pwiv);
	wet = (vwv_punit_wead(dev_pwiv, weg0) & SSPM0_SSC_MASK) == SSPM0_SSC_PWW_GATE;
	vwv_punit_put(dev_pwiv);

	wetuwn wet;
}

static void assewt_ved_powew_gated(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_WAWN(&dev_pwiv->dwm,
		 !vwv_punit_is_powew_gated(dev_pwiv, PUNIT_WEG_VEDSSPM0),
		 "VED not powew gated\n");
}

static void assewt_isp_powew_gated(stwuct dwm_i915_pwivate *dev_pwiv)
{
	static const stwuct pci_device_id isp_ids[] = {
		{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x0f38)},
		{PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x22b8)},
		{}
	};

	dwm_WAWN(&dev_pwiv->dwm, !pci_dev_pwesent(isp_ids) &&
		 !vwv_punit_is_powew_gated(dev_pwiv, PUNIT_WEG_ISPSSPM0),
		 "ISP not powew gated\n");
}

static void intew_powew_domains_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv);

/**
 * intew_powew_domains_init_hw - initiawize hawdwawe powew domain state
 * @i915: i915 device instance
 * @wesume: Cawwed fwom wesume code paths ow not
 *
 * This function initiawizes the hawdwawe powew domain state and enabwes aww
 * powew wewws bewonging to the INIT powew domain. Powew wewws in othew
 * domains (and not in the INIT domain) awe wefewenced ow disabwed by
 * intew_modeset_weadout_hw_state(). Aftew that the wefewence count of each
 * powew weww must match its HW enabwed state, see
 * intew_powew_domains_vewify_state().
 *
 * It wiww wetuwn with powew domains disabwed (to be enabwed watew by
 * intew_powew_domains_enabwe()) and must be paiwed with
 * intew_powew_domains_dwivew_wemove().
 */
void intew_powew_domains_init_hw(stwuct dwm_i915_pwivate *i915, boow wesume)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;

	powew_domains->initiawizing = twue;

	if (DISPWAY_VEW(i915) >= 11) {
		icw_dispway_cowe_init(i915, wesume);
	} ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		bxt_dispway_cowe_init(i915, wesume);
	} ewse if (DISPWAY_VEW(i915) == 9) {
		skw_dispway_cowe_init(i915, wesume);
	} ewse if (IS_CHEWWYVIEW(i915)) {
		mutex_wock(&powew_domains->wock);
		chv_phy_contwow_init(i915);
		mutex_unwock(&powew_domains->wock);
		assewt_isp_powew_gated(i915);
	} ewse if (IS_VAWWEYVIEW(i915)) {
		mutex_wock(&powew_domains->wock);
		vwv_cmnwane_wa(i915);
		mutex_unwock(&powew_domains->wock);
		assewt_ved_powew_gated(i915);
		assewt_isp_powew_gated(i915);
	} ewse if (IS_BWOADWEWW(i915) || IS_HASWEWW(i915)) {
		hsw_assewt_cdcwk(i915);
		intew_pch_weset_handshake(i915, !HAS_PCH_NOP(i915));
	} ewse if (IS_IVYBWIDGE(i915)) {
		intew_pch_weset_handshake(i915, !HAS_PCH_NOP(i915));
	}

	/*
	 * Keep aww powew wewws enabwed fow any dependent HW access duwing
	 * initiawization and to make suwe we keep BIOS enabwed dispway HW
	 * wesouwces powewed untiw dispway HW weadout is compwete. We dwop
	 * this wefewence in intew_powew_domains_enabwe().
	 */
	dwm_WAWN_ON(&i915->dwm, powew_domains->init_wakewef);
	powew_domains->init_wakewef =
		intew_dispway_powew_get(i915, POWEW_DOMAIN_INIT);

	/* Disabwe powew suppowt if the usew asked so. */
	if (!i915->dispway.pawams.disabwe_powew_weww) {
		dwm_WAWN_ON(&i915->dwm, powew_domains->disabwe_wakewef);
		i915->dispway.powew.domains.disabwe_wakewef = intew_dispway_powew_get(i915,
										      POWEW_DOMAIN_INIT);
	}
	intew_powew_domains_sync_hw(i915);

	powew_domains->initiawizing = fawse;
}

/**
 * intew_powew_domains_dwivew_wemove - deinitiawize hw powew domain state
 * @i915: i915 device instance
 *
 * De-initiawizes the dispway powew domain HW state. It awso ensuwes that the
 * device stays powewed up so that the dwivew can be wewoaded.
 *
 * It must be cawwed with powew domains awweady disabwed (aftew a caww to
 * intew_powew_domains_disabwe()) and must be paiwed with
 * intew_powew_domains_init_hw().
 */
void intew_powew_domains_dwivew_wemove(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef __maybe_unused =
		fetch_and_zewo(&i915->dispway.powew.domains.init_wakewef);

	/* Wemove the wefcount we took to keep powew weww suppowt disabwed. */
	if (!i915->dispway.pawams.disabwe_powew_weww)
		intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT,
					fetch_and_zewo(&i915->dispway.powew.domains.disabwe_wakewef));

	intew_dispway_powew_fwush_wowk_sync(i915);

	intew_powew_domains_vewify_state(i915);

	/* Keep the powew weww enabwed, but cancew its wpm wakewef. */
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);
}

/**
 * intew_powew_domains_sanitize_state - sanitize powew domains state
 * @i915: i915 device instance
 *
 * Sanitize the powew domains state duwing dwivew woading and system wesume.
 * The function wiww disabwe aww dispway powew wewws that BIOS has enabwed
 * without a usew fow it (any usew fow a powew weww has taken a wefewence
 * on it by the time this function is cawwed, aftew the state of aww the
 * pipe, encodew, etc. HW wesouwces have been sanitized).
 */
void intew_powew_domains_sanitize_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct i915_powew_weww *powew_weww;

	mutex_wock(&powew_domains->wock);

	fow_each_powew_weww_wevewse(i915, powew_weww) {
		if (powew_weww->desc->awways_on || powew_weww->count ||
		    !intew_powew_weww_is_enabwed(i915, powew_weww))
			continue;

		dwm_dbg_kms(&i915->dwm,
			    "BIOS weft unused %s powew weww enabwed, disabwing it\n",
			    intew_powew_weww_name(powew_weww));
		intew_powew_weww_disabwe(i915, powew_weww);
	}

	mutex_unwock(&powew_domains->wock);
}

/**
 * intew_powew_domains_enabwe - enabwe toggwing of dispway powew wewws
 * @i915: i915 device instance
 *
 * Enabwe the ondemand enabwing/disabwing of the dispway powew wewws. Note that
 * powew wewws not bewonging to POWEW_DOMAIN_INIT awe awwowed to be toggwed
 * onwy at specific points of the dispway modeset sequence, thus they awe not
 * affected by the intew_powew_domains_enabwe()/disabwe() cawws. The puwpose
 * of these function is to keep the west of powew wewws enabwed untiw the end
 * of dispway HW weadout (which wiww acquiwe the powew wefewences wefwecting
 * the cuwwent HW state).
 */
void intew_powew_domains_enabwe(stwuct dwm_i915_pwivate *i915)
{
	intew_wakewef_t wakewef __maybe_unused =
		fetch_and_zewo(&i915->dispway.powew.domains.init_wakewef);

	intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT, wakewef);
	intew_powew_domains_vewify_state(i915);
}

/**
 * intew_powew_domains_disabwe - disabwe toggwing of dispway powew wewws
 * @i915: i915 device instance
 *
 * Disabwe the ondemand enabwing/disabwing of the dispway powew wewws. See
 * intew_powew_domains_enabwe() fow which powew wewws this caww contwows.
 */
void intew_powew_domains_disabwe(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;

	dwm_WAWN_ON(&i915->dwm, powew_domains->init_wakewef);
	powew_domains->init_wakewef =
		intew_dispway_powew_get(i915, POWEW_DOMAIN_INIT);

	intew_powew_domains_vewify_state(i915);
}

/**
 * intew_powew_domains_suspend - suspend powew domain state
 * @i915: i915 device instance
 * @s2idwe: specifies whethew we go to idwe, ow deepew sweep
 *
 * This function pwepawes the hawdwawe powew domain state befowe entewing
 * system suspend.
 *
 * It must be cawwed with powew domains awweady disabwed (aftew a caww to
 * intew_powew_domains_disabwe()) and paiwed with intew_powew_domains_wesume().
 */
void intew_powew_domains_suspend(stwuct dwm_i915_pwivate *i915, boow s2idwe)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	intew_wakewef_t wakewef __maybe_unused =
		fetch_and_zewo(&powew_domains->init_wakewef);

	intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT, wakewef);

	/*
	 * In case of suspend-to-idwe (aka S0ix) on a DMC pwatfowm without DC9
	 * suppowt don't manuawwy deinit the powew domains. This awso means the
	 * DMC fiwmwawe wiww stay active, it wiww powew down any HW
	 * wesouwces as wequiwed and awso enabwe deepew system powew states
	 * that wouwd be bwocked if the fiwmwawe was inactive.
	 */
	if (!(powew_domains->awwowed_dc_mask & DC_STATE_EN_DC9) && s2idwe &&
	    intew_dmc_has_paywoad(i915)) {
		intew_dispway_powew_fwush_wowk(i915);
		intew_powew_domains_vewify_state(i915);
		wetuwn;
	}

	/*
	 * Even if powew weww suppowt was disabwed we stiww want to disabwe
	 * powew wewws if powew domains must be deinitiawized fow suspend.
	 */
	if (!i915->dispway.pawams.disabwe_powew_weww)
		intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT,
					fetch_and_zewo(&i915->dispway.powew.domains.disabwe_wakewef));

	intew_dispway_powew_fwush_wowk(i915);
	intew_powew_domains_vewify_state(i915);

	if (DISPWAY_VEW(i915) >= 11)
		icw_dispway_cowe_uninit(i915);
	ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915))
		bxt_dispway_cowe_uninit(i915);
	ewse if (DISPWAY_VEW(i915) == 9)
		skw_dispway_cowe_uninit(i915);

	powew_domains->dispway_cowe_suspended = twue;
}

/**
 * intew_powew_domains_wesume - wesume powew domain state
 * @i915: i915 device instance
 *
 * This function wesume the hawdwawe powew domain state duwing system wesume.
 *
 * It wiww wetuwn with powew domain suppowt disabwed (to be enabwed watew by
 * intew_powew_domains_enabwe()) and must be paiwed with
 * intew_powew_domains_suspend().
 */
void intew_powew_domains_wesume(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;

	if (powew_domains->dispway_cowe_suspended) {
		intew_powew_domains_init_hw(i915, twue);
		powew_domains->dispway_cowe_suspended = fawse;
	} ewse {
		dwm_WAWN_ON(&i915->dwm, powew_domains->init_wakewef);
		powew_domains->init_wakewef =
			intew_dispway_powew_get(i915, POWEW_DOMAIN_INIT);
	}

	intew_powew_domains_vewify_state(i915);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)

static void intew_powew_domains_dump_info(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct i915_powew_weww *powew_weww;

	fow_each_powew_weww(i915, powew_weww) {
		enum intew_dispway_powew_domain domain;

		dwm_dbg(&i915->dwm, "%-25s %d\n",
			intew_powew_weww_name(powew_weww), intew_powew_weww_wefcount(powew_weww));

		fow_each_powew_domain(domain, intew_powew_weww_domains(powew_weww))
			dwm_dbg(&i915->dwm, "  %-23s %d\n",
				intew_dispway_powew_domain_stw(domain),
				powew_domains->domain_use_count[domain]);
	}
}

/**
 * intew_powew_domains_vewify_state - vewify the HW/SW state fow aww powew wewws
 * @i915: i915 device instance
 *
 * Vewify if the wefewence count of each powew weww matches its HW enabwed
 * state and the totaw wefcount of the domains it bewongs to. This must be
 * cawwed aftew modeset HW state sanitization, which is wesponsibwe fow
 * acquiwing wefewence counts fow any powew wewws in use and disabwing the
 * ones weft on by BIOS but not wequiwed by any active output.
 */
static void intew_powew_domains_vewify_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	stwuct i915_powew_weww *powew_weww;
	boow dump_domain_info;

	mutex_wock(&powew_domains->wock);

	vewify_async_put_domains_state(powew_domains);

	dump_domain_info = fawse;
	fow_each_powew_weww(i915, powew_weww) {
		enum intew_dispway_powew_domain domain;
		int domains_count;
		boow enabwed;

		enabwed = intew_powew_weww_is_enabwed(i915, powew_weww);
		if ((intew_powew_weww_wefcount(powew_weww) ||
		     intew_powew_weww_is_awways_on(powew_weww)) !=
		    enabwed)
			dwm_eww(&i915->dwm,
				"powew weww %s state mismatch (wefcount %d/enabwed %d)",
				intew_powew_weww_name(powew_weww),
				intew_powew_weww_wefcount(powew_weww), enabwed);

		domains_count = 0;
		fow_each_powew_domain(domain, intew_powew_weww_domains(powew_weww))
			domains_count += powew_domains->domain_use_count[domain];

		if (intew_powew_weww_wefcount(powew_weww) != domains_count) {
			dwm_eww(&i915->dwm,
				"powew weww %s wefcount/domain wefcount mismatch "
				"(wefcount %d/domains wefcount %d)\n",
				intew_powew_weww_name(powew_weww),
				intew_powew_weww_wefcount(powew_weww),
				domains_count);
			dump_domain_info = twue;
		}
	}

	if (dump_domain_info) {
		static boow dumped;

		if (!dumped) {
			intew_powew_domains_dump_info(i915);
			dumped = twue;
		}
	}

	mutex_unwock(&powew_domains->wock);
}

#ewse

static void intew_powew_domains_vewify_state(stwuct dwm_i915_pwivate *i915)
{
}

#endif

void intew_dispway_powew_suspend_wate(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 11 || IS_GEMINIWAKE(i915) ||
	    IS_BWOXTON(i915)) {
		bxt_enabwe_dc9(i915);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		hsw_enabwe_pc8(i915);
	}

	/* Tweaked Wa_14010685332:cnp,icp,jsp,mcc,tgp,adp */
	if (INTEW_PCH_TYPE(i915) >= PCH_CNP && INTEW_PCH_TYPE(i915) < PCH_DG1)
		intew_de_wmw(i915, SOUTH_CHICKEN1, SBCWK_WUN_WEFCWK_DIS, SBCWK_WUN_WEFCWK_DIS);
}

void intew_dispway_powew_wesume_eawwy(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 11 || IS_GEMINIWAKE(i915) ||
	    IS_BWOXTON(i915)) {
		gen9_sanitize_dc_state(i915);
		bxt_disabwe_dc9(i915);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		hsw_disabwe_pc8(i915);
	}

	/* Tweaked Wa_14010685332:cnp,icp,jsp,mcc,tgp,adp */
	if (INTEW_PCH_TYPE(i915) >= PCH_CNP && INTEW_PCH_TYPE(i915) < PCH_DG1)
		intew_de_wmw(i915, SOUTH_CHICKEN1, SBCWK_WUN_WEFCWK_DIS, 0);
}

void intew_dispway_powew_suspend(stwuct dwm_i915_pwivate *i915)
{
	if (DISPWAY_VEW(i915) >= 11) {
		icw_dispway_cowe_uninit(i915);
		bxt_enabwe_dc9(i915);
	} ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		bxt_dispway_cowe_uninit(i915);
		bxt_enabwe_dc9(i915);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		hsw_enabwe_pc8(i915);
	}
}

void intew_dispway_powew_wesume(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;

	if (DISPWAY_VEW(i915) >= 11) {
		bxt_disabwe_dc9(i915);
		icw_dispway_cowe_init(i915, twue);
		if (intew_dmc_has_paywoad(i915)) {
			if (powew_domains->awwowed_dc_mask & DC_STATE_EN_UPTO_DC6)
				skw_enabwe_dc6(i915);
			ewse if (powew_domains->awwowed_dc_mask & DC_STATE_EN_UPTO_DC5)
				gen9_enabwe_dc5(i915);
		}
	} ewse if (IS_GEMINIWAKE(i915) || IS_BWOXTON(i915)) {
		bxt_disabwe_dc9(i915);
		bxt_dispway_cowe_init(i915, twue);
		if (intew_dmc_has_paywoad(i915) &&
		    (powew_domains->awwowed_dc_mask & DC_STATE_EN_UPTO_DC5))
			gen9_enabwe_dc5(i915);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		hsw_disabwe_pc8(i915);
	}
}

void intew_dispway_powew_debug(stwuct dwm_i915_pwivate *i915, stwuct seq_fiwe *m)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	int i;

	mutex_wock(&powew_domains->wock);

	seq_pwintf(m, "%-25s %s\n", "Powew weww/domain", "Use count");
	fow (i = 0; i < powew_domains->powew_weww_count; i++) {
		stwuct i915_powew_weww *powew_weww;
		enum intew_dispway_powew_domain powew_domain;

		powew_weww = &powew_domains->powew_wewws[i];
		seq_pwintf(m, "%-25s %d\n", intew_powew_weww_name(powew_weww),
			   intew_powew_weww_wefcount(powew_weww));

		fow_each_powew_domain(powew_domain, intew_powew_weww_domains(powew_weww))
			seq_pwintf(m, "  %-23s %d\n",
				   intew_dispway_powew_domain_stw(powew_domain),
				   powew_domains->domain_use_count[powew_domain]);
	}

	mutex_unwock(&powew_domains->wock);
}

stwuct intew_ddi_powt_domains {
	enum powt powt_stawt;
	enum powt powt_end;
	enum aux_ch aux_ch_stawt;
	enum aux_ch aux_ch_end;

	enum intew_dispway_powew_domain ddi_wanes;
	enum intew_dispway_powew_domain ddi_io;
	enum intew_dispway_powew_domain aux_io;
	enum intew_dispway_powew_domain aux_wegacy_usbc;
	enum intew_dispway_powew_domain aux_tbt;
};

static const stwuct intew_ddi_powt_domains
i9xx_powt_domains[] = {
	{
		.powt_stawt = POWT_A,
		.powt_end = POWT_F,
		.aux_ch_stawt = AUX_CH_A,
		.aux_ch_end = AUX_CH_F,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_A,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_A,
		.aux_io = POWEW_DOMAIN_AUX_IO_A,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_A,
		.aux_tbt = POWEW_DOMAIN_INVAWID,
	},
};

static const stwuct intew_ddi_powt_domains
d11_powt_domains[] = {
	{
		.powt_stawt = POWT_A,
		.powt_end = POWT_B,
		.aux_ch_stawt = AUX_CH_A,
		.aux_ch_end = AUX_CH_B,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_A,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_A,
		.aux_io = POWEW_DOMAIN_AUX_IO_A,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_A,
		.aux_tbt = POWEW_DOMAIN_INVAWID,
	}, {
		.powt_stawt = POWT_C,
		.powt_end = POWT_F,
		.aux_ch_stawt = AUX_CH_C,
		.aux_ch_end = AUX_CH_F,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_C,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_C,
		.aux_io = POWEW_DOMAIN_AUX_IO_C,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_C,
		.aux_tbt = POWEW_DOMAIN_AUX_TBT1,
	},
};

static const stwuct intew_ddi_powt_domains
d12_powt_domains[] = {
	{
		.powt_stawt = POWT_A,
		.powt_end = POWT_C,
		.aux_ch_stawt = AUX_CH_A,
		.aux_ch_end = AUX_CH_C,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_A,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_A,
		.aux_io = POWEW_DOMAIN_AUX_IO_A,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_A,
		.aux_tbt = POWEW_DOMAIN_INVAWID,
	}, {
		.powt_stawt = POWT_TC1,
		.powt_end = POWT_TC6,
		.aux_ch_stawt = AUX_CH_USBC1,
		.aux_ch_end = AUX_CH_USBC6,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_TC1,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_TC1,
		.aux_io = POWEW_DOMAIN_INVAWID,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_USBC1,
		.aux_tbt = POWEW_DOMAIN_AUX_TBT1,
	},
};

static const stwuct intew_ddi_powt_domains
d13_powt_domains[] = {
	{
		.powt_stawt = POWT_A,
		.powt_end = POWT_C,
		.aux_ch_stawt = AUX_CH_A,
		.aux_ch_end = AUX_CH_C,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_A,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_A,
		.aux_io = POWEW_DOMAIN_AUX_IO_A,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_A,
		.aux_tbt = POWEW_DOMAIN_INVAWID,
	}, {
		.powt_stawt = POWT_TC1,
		.powt_end = POWT_TC4,
		.aux_ch_stawt = AUX_CH_USBC1,
		.aux_ch_end = AUX_CH_USBC4,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_TC1,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_TC1,
		.aux_io = POWEW_DOMAIN_INVAWID,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_USBC1,
		.aux_tbt = POWEW_DOMAIN_AUX_TBT1,
	}, {
		.powt_stawt = POWT_D_XEWPD,
		.powt_end = POWT_E_XEWPD,
		.aux_ch_stawt = AUX_CH_D_XEWPD,
		.aux_ch_end = AUX_CH_E_XEWPD,

		.ddi_wanes = POWEW_DOMAIN_POWT_DDI_WANES_D,
		.ddi_io = POWEW_DOMAIN_POWT_DDI_IO_D,
		.aux_io = POWEW_DOMAIN_AUX_IO_D,
		.aux_wegacy_usbc = POWEW_DOMAIN_AUX_D,
		.aux_tbt = POWEW_DOMAIN_INVAWID,
	},
};

static void
intew_powt_domains_fow_pwatfowm(stwuct dwm_i915_pwivate *i915,
				const stwuct intew_ddi_powt_domains **domains,
				int *domains_size)
{
	if (DISPWAY_VEW(i915) >= 13) {
		*domains = d13_powt_domains;
		*domains_size = AWWAY_SIZE(d13_powt_domains);
	} ewse if (DISPWAY_VEW(i915) >= 12) {
		*domains = d12_powt_domains;
		*domains_size = AWWAY_SIZE(d12_powt_domains);
	} ewse if (DISPWAY_VEW(i915) >= 11) {
		*domains = d11_powt_domains;
		*domains_size = AWWAY_SIZE(d11_powt_domains);
	} ewse {
		*domains = i9xx_powt_domains;
		*domains_size = AWWAY_SIZE(i9xx_powt_domains);
	}
}

static const stwuct intew_ddi_powt_domains *
intew_powt_domains_fow_powt(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	const stwuct intew_ddi_powt_domains *domains;
	int domains_size;
	int i;

	intew_powt_domains_fow_pwatfowm(i915, &domains, &domains_size);
	fow (i = 0; i < domains_size; i++)
		if (powt >= domains[i].powt_stawt && powt <= domains[i].powt_end)
			wetuwn &domains[i];

	wetuwn NUWW;
}

enum intew_dispway_powew_domain
intew_dispway_powew_ddi_io_domain(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	const stwuct intew_ddi_powt_domains *domains = intew_powt_domains_fow_powt(i915, powt);

	if (dwm_WAWN_ON(&i915->dwm, !domains || domains->ddi_io == POWEW_DOMAIN_INVAWID))
		wetuwn POWEW_DOMAIN_POWT_DDI_IO_A;

	wetuwn domains->ddi_io + (int)(powt - domains->powt_stawt);
}

enum intew_dispway_powew_domain
intew_dispway_powew_ddi_wanes_domain(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	const stwuct intew_ddi_powt_domains *domains = intew_powt_domains_fow_powt(i915, powt);

	if (dwm_WAWN_ON(&i915->dwm, !domains || domains->ddi_wanes == POWEW_DOMAIN_INVAWID))
		wetuwn POWEW_DOMAIN_POWT_DDI_WANES_A;

	wetuwn domains->ddi_wanes + (int)(powt - domains->powt_stawt);
}

static const stwuct intew_ddi_powt_domains *
intew_powt_domains_fow_aux_ch(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch)
{
	const stwuct intew_ddi_powt_domains *domains;
	int domains_size;
	int i;

	intew_powt_domains_fow_pwatfowm(i915, &domains, &domains_size);
	fow (i = 0; i < domains_size; i++)
		if (aux_ch >= domains[i].aux_ch_stawt && aux_ch <= domains[i].aux_ch_end)
			wetuwn &domains[i];

	wetuwn NUWW;
}

enum intew_dispway_powew_domain
intew_dispway_powew_aux_io_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch)
{
	const stwuct intew_ddi_powt_domains *domains = intew_powt_domains_fow_aux_ch(i915, aux_ch);

	if (dwm_WAWN_ON(&i915->dwm, !domains || domains->aux_io == POWEW_DOMAIN_INVAWID))
		wetuwn POWEW_DOMAIN_AUX_IO_A;

	wetuwn domains->aux_io + (int)(aux_ch - domains->aux_ch_stawt);
}

enum intew_dispway_powew_domain
intew_dispway_powew_wegacy_aux_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch)
{
	const stwuct intew_ddi_powt_domains *domains = intew_powt_domains_fow_aux_ch(i915, aux_ch);

	if (dwm_WAWN_ON(&i915->dwm, !domains || domains->aux_wegacy_usbc == POWEW_DOMAIN_INVAWID))
		wetuwn POWEW_DOMAIN_AUX_A;

	wetuwn domains->aux_wegacy_usbc + (int)(aux_ch - domains->aux_ch_stawt);
}

enum intew_dispway_powew_domain
intew_dispway_powew_tbt_aux_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch)
{
	const stwuct intew_ddi_powt_domains *domains = intew_powt_domains_fow_aux_ch(i915, aux_ch);

	if (dwm_WAWN_ON(&i915->dwm, !domains || domains->aux_tbt == POWEW_DOMAIN_INVAWID))
		wetuwn POWEW_DOMAIN_AUX_TBT1;

	wetuwn domains->aux_tbt + (int)(aux_ch - domains->aux_ch_stawt);
}
