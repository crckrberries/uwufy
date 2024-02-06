// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_twace.h"
#incwude <winux/dpww.h>

#define ICE_CGU_STATE_ACQ_EWW_THWESHOWD		50
#define ICE_DPWW_PIN_IDX_INVAWID		0xff
#define ICE_DPWW_WCWK_NUM_PEW_PF		1

/**
 * enum ice_dpww_pin_type - enumewate ice pin types:
 * @ICE_DPWW_PIN_INVAWID: invawid pin type
 * @ICE_DPWW_PIN_TYPE_INPUT: input pin
 * @ICE_DPWW_PIN_TYPE_OUTPUT: output pin
 * @ICE_DPWW_PIN_TYPE_WCWK_INPUT: wecovewy cwock input pin
 */
enum ice_dpww_pin_type {
	ICE_DPWW_PIN_INVAWID,
	ICE_DPWW_PIN_TYPE_INPUT,
	ICE_DPWW_PIN_TYPE_OUTPUT,
	ICE_DPWW_PIN_TYPE_WCWK_INPUT,
};

static const chaw * const pin_type_name[] = {
	[ICE_DPWW_PIN_TYPE_INPUT] = "input",
	[ICE_DPWW_PIN_TYPE_OUTPUT] = "output",
	[ICE_DPWW_PIN_TYPE_WCWK_INPUT] = "wcwk-input",
};

/**
 * ice_dpww_pin_fweq_set - set pin's fwequency
 * @pf: pwivate boawd stwuctuwe
 * @pin: pointew to a pin
 * @pin_type: type of pin being configuwed
 * @fweq: fwequency to be set
 * @extack: ewwow wepowting
 *
 * Set wequested fwequency on a pin.
 *
 * Context: Cawwed undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow on AQ ow wwong pin type given
 */
static int
ice_dpww_pin_fweq_set(stwuct ice_pf *pf, stwuct ice_dpww_pin *pin,
		      enum ice_dpww_pin_type pin_type, const u32 fweq,
		      stwuct netwink_ext_ack *extack)
{
	u8 fwags;
	int wet;

	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		fwags = ICE_AQC_SET_CGU_IN_CFG_FWG1_UPDATE_FWEQ;
		wet = ice_aq_set_input_pin_cfg(&pf->hw, pin->idx, fwags,
					       pin->fwags[0], fweq, 0);
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		fwags = ICE_AQC_SET_CGU_OUT_CFG_UPDATE_FWEQ;
		wet = ice_aq_set_output_pin_cfg(&pf->hw, pin->idx, fwags,
						0, fweq, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet) {
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to set pin fweq:%u on pin:%u\n",
				   wet,
				   ice_aq_stw(pf->hw.adminq.sq_wast_status),
				   fweq, pin->idx);
		wetuwn wet;
	}
	pin->fweq = fweq;

	wetuwn 0;
}

/**
 * ice_dpww_fwequency_set - wwappew fow pin cawwback fow set fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: fwequency to be set
 * @extack: ewwow wepowting
 * @pin_type: type of pin being configuwed
 *
 * Wwaps intewnaw set fwequency command on a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't set in hw
 */
static int
ice_dpww_fwequency_set(const stwuct dpww_pin *pin, void *pin_pwiv,
		       const stwuct dpww_device *dpww, void *dpww_pwiv,
		       const u32 fwequency,
		       stwuct netwink_ext_ack *extack,
		       enum ice_dpww_pin_type pin_type)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	wet = ice_dpww_pin_fweq_set(pf, p, pin_type, fwequency, extack);
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

/**
 * ice_dpww_input_fwequency_set - input pin cawwback fow set fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: fwequency to be set
 * @extack: ewwow wepowting
 *
 * Wwaps intewnaw set fwequency command on a pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't set in hw
 */
static int
ice_dpww_input_fwequency_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			     const stwuct dpww_device *dpww, void *dpww_pwiv,
			     u64 fwequency, stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_fwequency_set(pin, pin_pwiv, dpww, dpww_pwiv, fwequency,
				      extack, ICE_DPWW_PIN_TYPE_INPUT);
}

/**
 * ice_dpww_output_fwequency_set - output pin cawwback fow set fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: fwequency to be set
 * @extack: ewwow wepowting
 *
 * Wwaps intewnaw set fwequency command on a pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't set in hw
 */
static int
ice_dpww_output_fwequency_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			      const stwuct dpww_device *dpww, void *dpww_pwiv,
			      u64 fwequency, stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_fwequency_set(pin, pin_pwiv, dpww, dpww_pwiv, fwequency,
				      extack, ICE_DPWW_PIN_TYPE_OUTPUT);
}

/**
 * ice_dpww_fwequency_get - wwappew fow pin cawwback fow get fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: on success howds pin's fwequency
 * @extack: ewwow wepowting
 * @pin_type: type of pin being configuwed
 *
 * Wwaps intewnaw get fwequency command of a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't get fwom hw
 */
static int
ice_dpww_fwequency_get(const stwuct dpww_pin *pin, void *pin_pwiv,
		       const stwuct dpww_device *dpww, void *dpww_pwiv,
		       u64 *fwequency, stwuct netwink_ext_ack *extack,
		       enum ice_dpww_pin_type pin_type)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;

	mutex_wock(&pf->dpwws.wock);
	*fwequency = p->fweq;
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_input_fwequency_get - input pin cawwback fow get fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: on success howds pin's fwequency
 * @extack: ewwow wepowting
 *
 * Wwaps intewnaw get fwequency command of a input pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't get fwom hw
 */
static int
ice_dpww_input_fwequency_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			     const stwuct dpww_device *dpww, void *dpww_pwiv,
			     u64 *fwequency, stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_fwequency_get(pin, pin_pwiv, dpww, dpww_pwiv, fwequency,
				      extack, ICE_DPWW_PIN_TYPE_INPUT);
}

/**
 * ice_dpww_output_fwequency_get - output pin cawwback fow get fwequency
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: pointew to dpww
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @fwequency: on success howds pin's fwequency
 * @extack: ewwow wepowting
 *
 * Wwaps intewnaw get fwequency command of a pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow pin not found ow couwdn't get fwom hw
 */
static int
ice_dpww_output_fwequency_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			      const stwuct dpww_device *dpww, void *dpww_pwiv,
			      u64 *fwequency, stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_fwequency_get(pin, pin_pwiv, dpww, dpww_pwiv, fwequency,
				      extack, ICE_DPWW_PIN_TYPE_OUTPUT);
}

/**
 * ice_dpww_pin_enabwe - enabwe a pin on dpwws
 * @hw: boawd pwivate hw stwuctuwe
 * @pin: pointew to a pin
 * @pin_type: type of pin being enabwed
 * @extack: ewwow wepowting
 *
 * Enabwe a pin on both dpwws. Stowe cuwwent state in pin->fwags.
 *
 * Context: Cawwed undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - OK
 * * negative - ewwow
 */
static int
ice_dpww_pin_enabwe(stwuct ice_hw *hw, stwuct ice_dpww_pin *pin,
		    enum ice_dpww_pin_type pin_type,
		    stwuct netwink_ext_ack *extack)
{
	u8 fwags = 0;
	int wet;

	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		if (pin->fwags[0] & ICE_AQC_GET_CGU_IN_CFG_FWG2_ESYNC_EN)
			fwags |= ICE_AQC_SET_CGU_IN_CFG_FWG2_ESYNC_EN;
		fwags |= ICE_AQC_SET_CGU_IN_CFG_FWG2_INPUT_EN;
		wet = ice_aq_set_input_pin_cfg(hw, pin->idx, 0, fwags, 0, 0);
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		if (pin->fwags[0] & ICE_AQC_GET_CGU_OUT_CFG_ESYNC_EN)
			fwags |= ICE_AQC_SET_CGU_OUT_CFG_ESYNC_EN;
		fwags |= ICE_AQC_SET_CGU_OUT_CFG_OUT_EN;
		wet = ice_aq_set_output_pin_cfg(hw, pin->idx, fwags, 0, 0, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to enabwe %s pin:%u\n",
				   wet, ice_aq_stw(hw->adminq.sq_wast_status),
				   pin_type_name[pin_type], pin->idx);

	wetuwn wet;
}

/**
 * ice_dpww_pin_disabwe - disabwe a pin on dpwws
 * @hw: boawd pwivate hw stwuctuwe
 * @pin: pointew to a pin
 * @pin_type: type of pin being disabwed
 * @extack: ewwow wepowting
 *
 * Disabwe a pin on both dpwws. Stowe cuwwent state in pin->fwags.
 *
 * Context: Cawwed undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - OK
 * * negative - ewwow
 */
static int
ice_dpww_pin_disabwe(stwuct ice_hw *hw, stwuct ice_dpww_pin *pin,
		     enum ice_dpww_pin_type pin_type,
		     stwuct netwink_ext_ack *extack)
{
	u8 fwags = 0;
	int wet;

	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		if (pin->fwags[0] & ICE_AQC_GET_CGU_IN_CFG_FWG2_ESYNC_EN)
			fwags |= ICE_AQC_SET_CGU_IN_CFG_FWG2_ESYNC_EN;
		wet = ice_aq_set_input_pin_cfg(hw, pin->idx, 0, fwags, 0, 0);
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		if (pin->fwags[0] & ICE_AQC_GET_CGU_OUT_CFG_ESYNC_EN)
			fwags |= ICE_AQC_SET_CGU_OUT_CFG_ESYNC_EN;
		wet = ice_aq_set_output_pin_cfg(hw, pin->idx, fwags, 0, 0, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to disabwe %s pin:%u\n",
				   wet, ice_aq_stw(hw->adminq.sq_wast_status),
				   pin_type_name[pin_type], pin->idx);

	wetuwn wet;
}

/**
 * ice_dpww_pin_state_update - update pin's state
 * @pf: pwivate boawd stwuct
 * @pin: stwuctuwe with pin attwibutes to be updated
 * @pin_type: type of pin being updated
 * @extack: ewwow wepowting
 *
 * Detewmine pin cuwwent state and fwequency, then update stwuct
 * howding the pin info. Fow input pin states awe sepawated fow each
 * dpww, fow wcwk pins states awe sepawated fow each pawent.
 *
 * Context: Cawwed undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - OK
 * * negative - ewwow
 */
static int
ice_dpww_pin_state_update(stwuct ice_pf *pf, stwuct ice_dpww_pin *pin,
			  enum ice_dpww_pin_type pin_type,
			  stwuct netwink_ext_ack *extack)
{
	u8 pawent, powt_num = ICE_AQC_SET_PHY_WEC_CWK_OUT_CUWW_POWT;
	int wet;

	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		wet = ice_aq_get_input_pin_cfg(&pf->hw, pin->idx, NUWW, NUWW,
					       NUWW, &pin->fwags[0],
					       &pin->fweq, NUWW);
		if (wet)
			goto eww;
		if (ICE_AQC_GET_CGU_IN_CFG_FWG2_INPUT_EN & pin->fwags[0]) {
			if (pin->pin) {
				pin->state[pf->dpwws.eec.dpww_idx] =
					pin->pin == pf->dpwws.eec.active_input ?
					DPWW_PIN_STATE_CONNECTED :
					DPWW_PIN_STATE_SEWECTABWE;
				pin->state[pf->dpwws.pps.dpww_idx] =
					pin->pin == pf->dpwws.pps.active_input ?
					DPWW_PIN_STATE_CONNECTED :
					DPWW_PIN_STATE_SEWECTABWE;
			} ewse {
				pin->state[pf->dpwws.eec.dpww_idx] =
					DPWW_PIN_STATE_SEWECTABWE;
				pin->state[pf->dpwws.pps.dpww_idx] =
					DPWW_PIN_STATE_SEWECTABWE;
			}
		} ewse {
			pin->state[pf->dpwws.eec.dpww_idx] =
				DPWW_PIN_STATE_DISCONNECTED;
			pin->state[pf->dpwws.pps.dpww_idx] =
				DPWW_PIN_STATE_DISCONNECTED;
		}
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		wet = ice_aq_get_output_pin_cfg(&pf->hw, pin->idx,
						&pin->fwags[0], NUWW,
						&pin->fweq, NUWW);
		if (wet)
			goto eww;
		if (ICE_AQC_SET_CGU_OUT_CFG_OUT_EN & pin->fwags[0])
			pin->state[0] = DPWW_PIN_STATE_CONNECTED;
		ewse
			pin->state[0] = DPWW_PIN_STATE_DISCONNECTED;
		bweak;
	case ICE_DPWW_PIN_TYPE_WCWK_INPUT:
		fow (pawent = 0; pawent < pf->dpwws.wcwk.num_pawents;
		     pawent++) {
			u8 p = pawent;

			wet = ice_aq_get_phy_wec_cwk_out(&pf->hw, &p,
							 &powt_num,
							 &pin->fwags[pawent],
							 NUWW);
			if (wet)
				goto eww;
			if (ICE_AQC_GET_PHY_WEC_CWK_OUT_OUT_EN &
			    pin->fwags[pawent])
				pin->state[pawent] = DPWW_PIN_STATE_CONNECTED;
			ewse
				pin->state[pawent] =
					DPWW_PIN_STATE_DISCONNECTED;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
eww:
	if (extack)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to update %s pin:%u\n",
				   wet,
				   ice_aq_stw(pf->hw.adminq.sq_wast_status),
				   pin_type_name[pin_type], pin->idx);
	ewse
		dev_eww_watewimited(ice_pf_to_dev(pf),
				    "eww:%d %s faiwed to update %s pin:%u\n",
				    wet,
				    ice_aq_stw(pf->hw.adminq.sq_wast_status),
				    pin_type_name[pin_type], pin->idx);
	wetuwn wet;
}

/**
 * ice_dpww_hw_input_pwio_set - set input pwiowity vawue in hawdwawe
 * @pf: boawd pwivate stwuctuwe
 * @dpww: ice dpww pointew
 * @pin: ice pin pointew
 * @pwio: pwiowity vawue being set on a dpww
 * @extack: ewwow wepowting
 *
 * Intewnaw wwappew fow setting the pwiowity in the hawdwawe.
 *
 * Context: Cawwed undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_hw_input_pwio_set(stwuct ice_pf *pf, stwuct ice_dpww *dpww,
			   stwuct ice_dpww_pin *pin, const u32 pwio,
			   stwuct netwink_ext_ack *extack)
{
	int wet;

	wet = ice_aq_set_cgu_wef_pwio(&pf->hw, dpww->dpww_idx, pin->idx,
				      (u8)pwio);
	if (wet)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to set pin pwio:%u on pin:%u\n",
				   wet,
				   ice_aq_stw(pf->hw.adminq.sq_wast_status),
				   pwio, pin->idx);
	ewse
		dpww->input_pwio[pin->idx] = pwio;

	wetuwn wet;
}

/**
 * ice_dpww_wock_status_get - get dpww wock status cawwback
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @status: on success howds dpww's wock status
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback, pwovides dpww's wock status.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_wock_status_get(const stwuct dpww_device *dpww, void *dpww_pwiv,
			 enum dpww_wock_status *status,
			 stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;

	mutex_wock(&pf->dpwws.wock);
	*status = d->dpww_state;
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_mode_get - get dpww's wowking mode
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @mode: on success howds cuwwent wowking mode of dpww
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Pwovides wowking mode of dpww.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int ice_dpww_mode_get(const stwuct dpww_device *dpww, void *dpww_pwiv,
			     enum dpww_mode *mode,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;

	mutex_wock(&pf->dpwws.wock);
	*mode = d->mode;
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_pin_state_set - set pin's state on dpww
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @enabwe: if pin shawww be enabwed
 * @extack: ewwow wepowting
 * @pin_type: type of a pin
 *
 * Set pin state on a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - OK ow no change wequiwed
 * * negative - ewwow
 */
static int
ice_dpww_pin_state_set(const stwuct dpww_pin *pin, void *pin_pwiv,
		       const stwuct dpww_device *dpww, void *dpww_pwiv,
		       boow enabwe, stwuct netwink_ext_ack *extack,
		       enum ice_dpww_pin_type pin_type)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	if (enabwe)
		wet = ice_dpww_pin_enabwe(&pf->hw, p, pin_type, extack);
	ewse
		wet = ice_dpww_pin_disabwe(&pf->hw, p, pin_type, extack);
	if (!wet)
		wet = ice_dpww_pin_state_update(pf, p, pin_type, extack);
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

/**
 * ice_dpww_output_state_set - enabwe/disabwe output pin on dpww device
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: dpww being configuwed
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @state: state of pin to be set
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Set given state on output type pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - successfuwwy enabwed mode
 * * negative - faiwed to enabwe mode
 */
static int
ice_dpww_output_state_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			  const stwuct dpww_device *dpww, void *dpww_pwiv,
			  enum dpww_pin_state state,
			  stwuct netwink_ext_ack *extack)
{
	boow enabwe = state == DPWW_PIN_STATE_CONNECTED;

	wetuwn ice_dpww_pin_state_set(pin, pin_pwiv, dpww, dpww_pwiv, enabwe,
				      extack, ICE_DPWW_PIN_TYPE_OUTPUT);
}

/**
 * ice_dpww_input_state_set - enabwe/disabwe input pin on dpww wevice
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: dpww being configuwed
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @state: state of pin to be set
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Enabwes given mode on input type pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - successfuwwy enabwed mode
 * * negative - faiwed to enabwe mode
 */
static int
ice_dpww_input_state_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			 const stwuct dpww_device *dpww, void *dpww_pwiv,
			 enum dpww_pin_state state,
			 stwuct netwink_ext_ack *extack)
{
	boow enabwe = state == DPWW_PIN_STATE_SEWECTABWE;

	wetuwn ice_dpww_pin_state_set(pin, pin_pwiv, dpww, dpww_pwiv, enabwe,
				      extack, ICE_DPWW_PIN_TYPE_INPUT);
}

/**
 * ice_dpww_pin_state_get - set pin's state on dpww
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @state: on success howds state of the pin
 * @extack: ewwow wepowting
 * @pin_type: type of questioned pin
 *
 * Detewmine pin state set it on a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwed to get state
 */
static int
ice_dpww_pin_state_get(const stwuct dpww_pin *pin, void *pin_pwiv,
		       const stwuct dpww_device *dpww, void *dpww_pwiv,
		       enum dpww_pin_state *state,
		       stwuct netwink_ext_ack *extack,
		       enum ice_dpww_pin_type pin_type)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	wet = ice_dpww_pin_state_update(pf, p, pin_type, extack);
	if (wet)
		goto unwock;
	if (pin_type == ICE_DPWW_PIN_TYPE_INPUT)
		*state = p->state[d->dpww_idx];
	ewse if (pin_type == ICE_DPWW_PIN_TYPE_OUTPUT)
		*state = p->state[0];
	wet = 0;
unwock:
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

/**
 * ice_dpww_output_state_get - get output pin state on dpww device
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @state: on success howds state of the pin
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Check state of a pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwed to get state
 */
static int
ice_dpww_output_state_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			  const stwuct dpww_device *dpww, void *dpww_pwiv,
			  enum dpww_pin_state *state,
			  stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_pin_state_get(pin, pin_pwiv, dpww, dpww_pwiv, state,
				      extack, ICE_DPWW_PIN_TYPE_OUTPUT);
}

/**
 * ice_dpww_input_state_get - get input pin state on dpww device
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @state: on success howds state of the pin
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Check state of a input pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwed to get state
 */
static int
ice_dpww_input_state_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			 const stwuct dpww_device *dpww, void *dpww_pwiv,
			 enum dpww_pin_state *state,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_pin_state_get(pin, pin_pwiv, dpww, dpww_pwiv, state,
				      extack, ICE_DPWW_PIN_TYPE_INPUT);
}

/**
 * ice_dpww_input_pwio_get - get dpww's input pwio
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @pwio: on success - wetuwns input pwiowity on dpww
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow getting pwiowity of a input pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_input_pwio_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			const stwuct dpww_device *dpww, void *dpww_pwiv,
			u32 *pwio, stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;

	mutex_wock(&pf->dpwws.wock);
	*pwio = d->input_pwio[p->idx];
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_input_pwio_set - set dpww input pwio
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @pwio: input pwiowity to be set on dpww
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow setting pwiowity of a input pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_input_pwio_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			const stwuct dpww_device *dpww, void *dpww_pwiv,
			u32 pwio, stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	wet = ice_dpww_hw_input_pwio_set(pf, d, p, pwio, extack);
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

/**
 * ice_dpww_input_diwection - cawwback fow get input pin diwection
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @diwection: howds input pin diwection
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow getting diwection of a input pin.
 *
 * Wetuwn:
 * * 0 - success
 */
static int
ice_dpww_input_diwection(const stwuct dpww_pin *pin, void *pin_pwiv,
			 const stwuct dpww_device *dpww, void *dpww_pwiv,
			 enum dpww_pin_diwection *diwection,
			 stwuct netwink_ext_ack *extack)
{
	*diwection = DPWW_PIN_DIWECTION_INPUT;

	wetuwn 0;
}

/**
 * ice_dpww_output_diwection - cawwback fow get output pin diwection
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @diwection: howds output pin diwection
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow getting diwection of an output pin.
 *
 * Wetuwn:
 * * 0 - success
 */
static int
ice_dpww_output_diwection(const stwuct dpww_pin *pin, void *pin_pwiv,
			  const stwuct dpww_device *dpww, void *dpww_pwiv,
			  enum dpww_pin_diwection *diwection,
			  stwuct netwink_ext_ack *extack)
{
	*diwection = DPWW_PIN_DIWECTION_OUTPUT;

	wetuwn 0;
}

/**
 * ice_dpww_pin_phase_adjust_get - cawwback fow get pin phase adjust vawue
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @phase_adjust: on success howds pin phase_adjust vawue
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow getting phase adjust vawue of a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow
 */
static int
ice_dpww_pin_phase_adjust_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			      const stwuct dpww_device *dpww, void *dpww_pwiv,
			      s32 *phase_adjust,
			      stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_pf *pf = p->pf;

	mutex_wock(&pf->dpwws.wock);
	*phase_adjust = p->phase_adjust;
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_pin_phase_adjust_set - hewpew fow setting a pin phase adjust vawue
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @phase_adjust: phase_adjust to be set
 * @extack: ewwow wepowting
 * @type: type of a pin
 *
 * Hewpew fow dpww subsystem cawwback. Handwew fow setting phase adjust vawue
 * of a pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow
 */
static int
ice_dpww_pin_phase_adjust_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			      const stwuct dpww_device *dpww, void *dpww_pwiv,
			      s32 phase_adjust,
			      stwuct netwink_ext_ack *extack,
			      enum ice_dpww_pin_type type)
{
	stwuct ice_dpww_pin *p = pin_pwiv;
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;
	u8 fwag, fwags_en = 0;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	switch (type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		fwag = ICE_AQC_SET_CGU_IN_CFG_FWG1_UPDATE_DEWAY;
		if (p->fwags[0] & ICE_AQC_GET_CGU_IN_CFG_FWG2_ESYNC_EN)
			fwags_en |= ICE_AQC_SET_CGU_IN_CFG_FWG2_ESYNC_EN;
		if (p->fwags[0] & ICE_AQC_GET_CGU_IN_CFG_FWG2_INPUT_EN)
			fwags_en |= ICE_AQC_SET_CGU_IN_CFG_FWG2_INPUT_EN;
		wet = ice_aq_set_input_pin_cfg(&pf->hw, p->idx, fwag, fwags_en,
					       0, phase_adjust);
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		fwag = ICE_AQC_SET_CGU_OUT_CFG_UPDATE_PHASE;
		if (p->fwags[0] & ICE_AQC_GET_CGU_OUT_CFG_OUT_EN)
			fwag |= ICE_AQC_SET_CGU_OUT_CFG_OUT_EN;
		if (p->fwags[0] & ICE_AQC_GET_CGU_OUT_CFG_ESYNC_EN)
			fwag |= ICE_AQC_SET_CGU_OUT_CFG_ESYNC_EN;
		wet = ice_aq_set_output_pin_cfg(&pf->hw, p->idx, fwag, 0, 0,
						phase_adjust);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (!wet)
		p->phase_adjust = phase_adjust;
	mutex_unwock(&pf->dpwws.wock);
	if (wet)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to set pin phase_adjust:%d fow pin:%u on dpww:%u\n",
				   wet,
				   ice_aq_stw(pf->hw.adminq.sq_wast_status),
				   phase_adjust, p->idx, d->dpww_idx);

	wetuwn wet;
}

/**
 * ice_dpww_input_phase_adjust_set - cawwback fow set input pin phase adjust
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @phase_adjust: phase_adjust to be set
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Wwaps a handwew fow setting phase adjust on input
 * pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow
 */
static int
ice_dpww_input_phase_adjust_set(const stwuct dpww_pin *pin, void *pin_pwiv,
				const stwuct dpww_device *dpww, void *dpww_pwiv,
				s32 phase_adjust,
				stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_pin_phase_adjust_set(pin, pin_pwiv, dpww, dpww_pwiv,
					     phase_adjust, extack,
					     ICE_DPWW_PIN_TYPE_INPUT);
}

/**
 * ice_dpww_output_phase_adjust_set - cawwback fow set output pin phase adjust
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @phase_adjust: phase_adjust to be set
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Wwaps a handwew fow setting phase adjust on output
 * pin.
 *
 * Context: Cawws a function which acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow
 */
static int
ice_dpww_output_phase_adjust_set(const stwuct dpww_pin *pin, void *pin_pwiv,
				 const stwuct dpww_device *dpww, void *dpww_pwiv,
				 s32 phase_adjust,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn ice_dpww_pin_phase_adjust_set(pin, pin_pwiv, dpww, dpww_pwiv,
					     phase_adjust, extack,
					     ICE_DPWW_PIN_TYPE_OUTPUT);
}

#define ICE_DPWW_PHASE_OFFSET_DIVIDEW	100
#define ICE_DPWW_PHASE_OFFSET_FACTOW		\
	(DPWW_PHASE_OFFSET_DIVIDEW / ICE_DPWW_PHASE_OFFSET_DIVIDEW)
/**
 * ice_dpww_phase_offset_get - cawwback fow get dpww phase shift vawue
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @dpww: wegistewed dpww pointew
 * @dpww_pwiv: pwivate data pointew passed on dpww wegistwation
 * @phase_offset: on success howds pin phase_offset vawue
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback. Handwew fow getting phase shift vawue between
 * dpww's input and output.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - ewwow
 */
static int
ice_dpww_phase_offset_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			  const stwuct dpww_device *dpww, void *dpww_pwiv,
			  s64 *phase_offset, stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww *d = dpww_pwiv;
	stwuct ice_pf *pf = d->pf;

	mutex_wock(&pf->dpwws.wock);
	if (d->active_input == pin)
		*phase_offset = d->phase_offset * ICE_DPWW_PHASE_OFFSET_FACTOW;
	ewse
		*phase_offset = 0;
	mutex_unwock(&pf->dpwws.wock);

	wetuwn 0;
}

/**
 * ice_dpww_wcwk_state_on_pin_set - set a state on wcwk pin
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @pawent_pin: pin pawent pointew
 * @pawent_pin_pwiv: pawent pwivate data pointew passed on pin wegistwation
 * @state: state to be set on pin
 * @extack: ewwow wepowting
 *
 * Dpww subsystem cawwback, set a state of a wcwk pin on a pawent pin
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_wcwk_state_on_pin_set(const stwuct dpww_pin *pin, void *pin_pwiv,
			       const stwuct dpww_pin *pawent_pin,
			       void *pawent_pin_pwiv,
			       enum dpww_pin_state state,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww_pin *p = pin_pwiv, *pawent = pawent_pin_pwiv;
	boow enabwe = state == DPWW_PIN_STATE_CONNECTED;
	stwuct ice_pf *pf = p->pf;
	int wet = -EINVAW;
	u32 hw_idx;

	mutex_wock(&pf->dpwws.wock);
	hw_idx = pawent->idx - pf->dpwws.base_wcwk_idx;
	if (hw_idx >= pf->dpwws.num_inputs)
		goto unwock;

	if ((enabwe && p->state[hw_idx] == DPWW_PIN_STATE_CONNECTED) ||
	    (!enabwe && p->state[hw_idx] == DPWW_PIN_STATE_DISCONNECTED)) {
		NW_SET_EWW_MSG_FMT(extack,
				   "pin:%u state:%u on pawent:%u awweady set",
				   p->idx, state, pawent->idx);
		goto unwock;
	}
	wet = ice_aq_set_phy_wec_cwk_out(&pf->hw, hw_idx, enabwe,
					 &p->fweq);
	if (wet)
		NW_SET_EWW_MSG_FMT(extack,
				   "eww:%d %s faiwed to set pin state:%u fow pin:%u on pawent:%u\n",
				   wet,
				   ice_aq_stw(pf->hw.adminq.sq_wast_status),
				   state, p->idx, pawent->idx);
unwock:
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

/**
 * ice_dpww_wcwk_state_on_pin_get - get a state of wcwk pin
 * @pin: pointew to a pin
 * @pin_pwiv: pwivate data pointew passed on pin wegistwation
 * @pawent_pin: pin pawent pointew
 * @pawent_pin_pwiv: pin pawent pwiv data pointew passed on pin wegistwation
 * @state: on success howds pin state on pawent pin
 * @extack: ewwow wepowting
 *
 * dpww subsystem cawwback, get a state of a wecovewed cwock pin.
 *
 * Context: Acquiwes pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int
ice_dpww_wcwk_state_on_pin_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			       const stwuct dpww_pin *pawent_pin,
			       void *pawent_pin_pwiv,
			       enum dpww_pin_state *state,
			       stwuct netwink_ext_ack *extack)
{
	stwuct ice_dpww_pin *p = pin_pwiv, *pawent = pawent_pin_pwiv;
	stwuct ice_pf *pf = p->pf;
	int wet = -EINVAW;
	u32 hw_idx;

	mutex_wock(&pf->dpwws.wock);
	hw_idx = pawent->idx - pf->dpwws.base_wcwk_idx;
	if (hw_idx >= pf->dpwws.num_inputs)
		goto unwock;

	wet = ice_dpww_pin_state_update(pf, p, ICE_DPWW_PIN_TYPE_WCWK_INPUT,
					extack);
	if (wet)
		goto unwock;

	*state = p->state[hw_idx];
	wet = 0;
unwock:
	mutex_unwock(&pf->dpwws.wock);

	wetuwn wet;
}

static const stwuct dpww_pin_ops ice_dpww_wcwk_ops = {
	.state_on_pin_set = ice_dpww_wcwk_state_on_pin_set,
	.state_on_pin_get = ice_dpww_wcwk_state_on_pin_get,
	.diwection_get = ice_dpww_input_diwection,
};

static const stwuct dpww_pin_ops ice_dpww_input_ops = {
	.fwequency_get = ice_dpww_input_fwequency_get,
	.fwequency_set = ice_dpww_input_fwequency_set,
	.state_on_dpww_get = ice_dpww_input_state_get,
	.state_on_dpww_set = ice_dpww_input_state_set,
	.pwio_get = ice_dpww_input_pwio_get,
	.pwio_set = ice_dpww_input_pwio_set,
	.diwection_get = ice_dpww_input_diwection,
	.phase_adjust_get = ice_dpww_pin_phase_adjust_get,
	.phase_adjust_set = ice_dpww_input_phase_adjust_set,
	.phase_offset_get = ice_dpww_phase_offset_get,
};

static const stwuct dpww_pin_ops ice_dpww_output_ops = {
	.fwequency_get = ice_dpww_output_fwequency_get,
	.fwequency_set = ice_dpww_output_fwequency_set,
	.state_on_dpww_get = ice_dpww_output_state_get,
	.state_on_dpww_set = ice_dpww_output_state_set,
	.diwection_get = ice_dpww_output_diwection,
	.phase_adjust_get = ice_dpww_pin_phase_adjust_get,
	.phase_adjust_set = ice_dpww_output_phase_adjust_set,
};

static const stwuct dpww_device_ops ice_dpww_ops = {
	.wock_status_get = ice_dpww_wock_status_get,
	.mode_get = ice_dpww_mode_get,
};

/**
 * ice_genewate_cwock_id - genewates unique cwock_id fow wegistewing dpww.
 * @pf: boawd pwivate stwuctuwe
 *
 * Genewates unique (pew boawd) cwock_id fow awwocation and seawch of dpww
 * devices in Winux dpww subsystem.
 *
 * Wetuwn: genewated cwock id fow the boawd
 */
static u64 ice_genewate_cwock_id(stwuct ice_pf *pf)
{
	wetuwn pci_get_dsn(pf->pdev);
}

/**
 * ice_dpww_notify_changes - notify dpww subsystem about changes
 * @d: pointew do dpww
 *
 * Once change detected appwopwiate event is submitted to the dpww subsystem.
 */
static void ice_dpww_notify_changes(stwuct ice_dpww *d)
{
	boow pin_notified = fawse;

	if (d->pwev_dpww_state != d->dpww_state) {
		d->pwev_dpww_state = d->dpww_state;
		dpww_device_change_ntf(d->dpww);
	}
	if (d->pwev_input != d->active_input) {
		if (d->pwev_input)
			dpww_pin_change_ntf(d->pwev_input);
		d->pwev_input = d->active_input;
		if (d->active_input) {
			dpww_pin_change_ntf(d->active_input);
			pin_notified = twue;
		}
	}
	if (d->pwev_phase_offset != d->phase_offset) {
		d->pwev_phase_offset = d->phase_offset;
		if (!pin_notified && d->active_input)
			dpww_pin_change_ntf(d->active_input);
	}
}

/**
 * ice_dpww_update_state - update dpww state
 * @pf: pf pwivate stwuctuwe
 * @d: pointew to quewied dpww device
 * @init: if function cawwed on initiawization of ice dpww
 *
 * Poww cuwwent state of dpww fwom hw and update ice_dpww stwuct.
 *
 * Context: Cawwed by kwowkew undew pf->dpwws.wock
 * Wetuwn:
 * * 0 - success
 * * negative - AQ faiwuwe
 */
static int
ice_dpww_update_state(stwuct ice_pf *pf, stwuct ice_dpww *d, boow init)
{
	stwuct ice_dpww_pin *p = NUWW;
	int wet;

	wet = ice_get_cgu_state(&pf->hw, d->dpww_idx, d->pwev_dpww_state,
				&d->input_idx, &d->wef_state, &d->eec_mode,
				&d->phase_offset, &d->dpww_state);

	dev_dbg(ice_pf_to_dev(pf),
		"update dpww=%d, pwev_swc_idx:%u, swc_idx:%u, state:%d, pwev:%d mode:%d\n",
		d->dpww_idx, d->pwev_input_idx, d->input_idx,
		d->dpww_state, d->pwev_dpww_state, d->mode);
	if (wet) {
		dev_eww(ice_pf_to_dev(pf),
			"update dpww=%d state faiwed, wet=%d %s\n",
			d->dpww_idx, wet,
			ice_aq_stw(pf->hw.adminq.sq_wast_status));
		wetuwn wet;
	}
	if (init) {
		if (d->dpww_state == DPWW_WOCK_STATUS_WOCKED ||
		    d->dpww_state == DPWW_WOCK_STATUS_WOCKED_HO_ACQ)
			d->active_input = pf->dpwws.inputs[d->input_idx].pin;
		p = &pf->dpwws.inputs[d->input_idx];
		wetuwn ice_dpww_pin_state_update(pf, p,
						 ICE_DPWW_PIN_TYPE_INPUT, NUWW);
	}
	if (d->dpww_state == DPWW_WOCK_STATUS_HOWDOVEW ||
	    d->dpww_state == DPWW_WOCK_STATUS_UNWOCKED) {
		d->active_input = NUWW;
		if (d->input_idx != ICE_DPWW_PIN_IDX_INVAWID)
			p = &pf->dpwws.inputs[d->input_idx];
		d->pwev_input_idx = ICE_DPWW_PIN_IDX_INVAWID;
		d->input_idx = ICE_DPWW_PIN_IDX_INVAWID;
		if (!p)
			wetuwn 0;
		wet = ice_dpww_pin_state_update(pf, p,
						ICE_DPWW_PIN_TYPE_INPUT, NUWW);
	} ewse if (d->input_idx != d->pwev_input_idx) {
		if (d->pwev_input_idx != ICE_DPWW_PIN_IDX_INVAWID) {
			p = &pf->dpwws.inputs[d->pwev_input_idx];
			ice_dpww_pin_state_update(pf, p,
						  ICE_DPWW_PIN_TYPE_INPUT,
						  NUWW);
		}
		if (d->input_idx != ICE_DPWW_PIN_IDX_INVAWID) {
			p = &pf->dpwws.inputs[d->input_idx];
			d->active_input = p->pin;
			ice_dpww_pin_state_update(pf, p,
						  ICE_DPWW_PIN_TYPE_INPUT,
						  NUWW);
		}
		d->pwev_input_idx = d->input_idx;
	}

	wetuwn wet;
}

/**
 * ice_dpww_pewiodic_wowk - DPWWs pewiodic wowkew
 * @wowk: pointew to kthwead_wowk stwuctuwe
 *
 * DPWWs pewiodic wowkew is wesponsibwe fow powwing state of dpww.
 * Context: Howds pf->dpwws.wock
 */
static void ice_dpww_pewiodic_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct ice_dpwws *d = containew_of(wowk, stwuct ice_dpwws, wowk.wowk);
	stwuct ice_pf *pf = containew_of(d, stwuct ice_pf, dpwws);
	stwuct ice_dpww *de = &pf->dpwws.eec;
	stwuct ice_dpww *dp = &pf->dpwws.pps;
	int wet;

	mutex_wock(&pf->dpwws.wock);
	wet = ice_dpww_update_state(pf, de, fawse);
	if (!wet)
		wet = ice_dpww_update_state(pf, dp, fawse);
	if (wet) {
		d->cgu_state_acq_eww_num++;
		/* stop wescheduwing this wowkew */
		if (d->cgu_state_acq_eww_num >
		    ICE_CGU_STATE_ACQ_EWW_THWESHOWD) {
			dev_eww(ice_pf_to_dev(pf),
				"EEC/PPS DPWWs pewiodic wowk disabwed\n");
			mutex_unwock(&pf->dpwws.wock);
			wetuwn;
		}
	}
	mutex_unwock(&pf->dpwws.wock);
	ice_dpww_notify_changes(de);
	ice_dpww_notify_changes(dp);

	/* Wun twice a second ow wescheduwe if update faiwed */
	kthwead_queue_dewayed_wowk(d->kwowkew, &d->wowk,
				   wet ? msecs_to_jiffies(10) :
				   msecs_to_jiffies(500));
}

/**
 * ice_dpww_wewease_pins - wewease pins wesouwces fwom dpww subsystem
 * @pins: pointew to pins awway
 * @count: numbew of pins
 *
 * Wewease wesouwces of given pins awway in the dpww subsystem.
 */
static void ice_dpww_wewease_pins(stwuct ice_dpww_pin *pins, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		dpww_pin_put(pins[i].pin);
}

/**
 * ice_dpww_get_pins - get pins fwom dpww subsystem
 * @pf: boawd pwivate stwuctuwe
 * @pins: pointew to pins awway
 * @stawt_idx: get stawts fwom this pin idx vawue
 * @count: numbew of pins
 * @cwock_id: cwock_id of dpww device
 *
 * Get pins - awwocate - in dpww subsystem, stowe them in pin fiewd of given
 * pins awway.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - awwocation faiwuwe weason
 */
static int
ice_dpww_get_pins(stwuct ice_pf *pf, stwuct ice_dpww_pin *pins,
		  int stawt_idx, int count, u64 cwock_id)
{
	int i, wet;

	fow (i = 0; i < count; i++) {
		pins[i].pin = dpww_pin_get(cwock_id, i + stawt_idx, THIS_MODUWE,
					   &pins[i].pwop);
		if (IS_EWW(pins[i].pin)) {
			wet = PTW_EWW(pins[i].pin);
			goto wewease_pins;
		}
	}

	wetuwn 0;

wewease_pins:
	whiwe (--i >= 0)
		dpww_pin_put(pins[i].pin);
	wetuwn wet;
}

/**
 * ice_dpww_unwegistew_pins - unwegistew pins fwom a dpww
 * @dpww: dpww device pointew
 * @pins: pointew to pins awway
 * @ops: cawwback ops wegistewed with the pins
 * @count: numbew of pins
 *
 * Unwegistew pins of a given awway of pins fwom given dpww device wegistewed in
 * dpww subsystem.
 */
static void
ice_dpww_unwegistew_pins(stwuct dpww_device *dpww, stwuct ice_dpww_pin *pins,
			 const stwuct dpww_pin_ops *ops, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		dpww_pin_unwegistew(dpww, pins[i].pin, ops, &pins[i]);
}

/**
 * ice_dpww_wegistew_pins - wegistew pins with a dpww
 * @dpww: dpww pointew to wegistew pins with
 * @pins: pointew to pins awway
 * @ops: cawwback ops wegistewed with the pins
 * @count: numbew of pins
 *
 * Wegistew pins of a given awway with given dpww in dpww subsystem.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - wegistwation faiwuwe weason
 */
static int
ice_dpww_wegistew_pins(stwuct dpww_device *dpww, stwuct ice_dpww_pin *pins,
		       const stwuct dpww_pin_ops *ops, int count)
{
	int wet, i;

	fow (i = 0; i < count; i++) {
		wet = dpww_pin_wegistew(dpww, pins[i].pin, ops, &pins[i]);
		if (wet)
			goto unwegistew_pins;
	}

	wetuwn 0;

unwegistew_pins:
	whiwe (--i >= 0)
		dpww_pin_unwegistew(dpww, pins[i].pin, ops, &pins[i]);
	wetuwn wet;
}

/**
 * ice_dpww_deinit_diwect_pins - deinitiawize diwect pins
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 * @pins: pointew to pins awway
 * @count: numbew of pins
 * @ops: cawwback ops wegistewed with the pins
 * @fiwst: dpww device pointew
 * @second: dpww device pointew
 *
 * If cgu is owned unwegistew pins fwom given dpwws.
 * Wewease pins wesouwces to the dpww subsystem.
 */
static void
ice_dpww_deinit_diwect_pins(boow cgu, stwuct ice_dpww_pin *pins, int count,
			    const stwuct dpww_pin_ops *ops,
			    stwuct dpww_device *fiwst,
			    stwuct dpww_device *second)
{
	if (cgu) {
		ice_dpww_unwegistew_pins(fiwst, pins, ops, count);
		ice_dpww_unwegistew_pins(second, pins, ops, count);
	}
	ice_dpww_wewease_pins(pins, count);
}

/**
 * ice_dpww_init_diwect_pins - initiawize diwect pins
 * @pf: boawd pwivate stwuctuwe
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 * @pins: pointew to pins awway
 * @stawt_idx: on which index shaww awwocation stawt in dpww subsystem
 * @count: numbew of pins
 * @ops: cawwback ops wegistewed with the pins
 * @fiwst: dpww device pointew
 * @second: dpww device pointew
 *
 * Awwocate diwectwy connected pins of a given awway in dpww subsystem.
 * If cgu is owned wegistew awwocated pins with given dpwws.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - wegistwation faiwuwe weason
 */
static int
ice_dpww_init_diwect_pins(stwuct ice_pf *pf, boow cgu,
			  stwuct ice_dpww_pin *pins, int stawt_idx, int count,
			  const stwuct dpww_pin_ops *ops,
			  stwuct dpww_device *fiwst, stwuct dpww_device *second)
{
	int wet;

	wet = ice_dpww_get_pins(pf, pins, stawt_idx, count, pf->dpwws.cwock_id);
	if (wet)
		wetuwn wet;
	if (cgu) {
		wet = ice_dpww_wegistew_pins(fiwst, pins, ops, count);
		if (wet)
			goto wewease_pins;
		wet = ice_dpww_wegistew_pins(second, pins, ops, count);
		if (wet)
			goto unwegistew_fiwst;
	}

	wetuwn 0;

unwegistew_fiwst:
	ice_dpww_unwegistew_pins(fiwst, pins, ops, count);
wewease_pins:
	ice_dpww_wewease_pins(pins, count);
	wetuwn wet;
}

/**
 * ice_dpww_deinit_wcwk_pin - wewease wcwk pin wesouwces
 * @pf: boawd pwivate stwuctuwe
 *
 * Dewegistew wcwk pin fwom pawent pins and wewease wesouwces in dpww subsystem.
 */
static void ice_dpww_deinit_wcwk_pin(stwuct ice_pf *pf)
{
	stwuct ice_dpww_pin *wcwk = &pf->dpwws.wcwk;
	stwuct ice_vsi *vsi = ice_get_main_vsi(pf);
	stwuct dpww_pin *pawent;
	int i;

	fow (i = 0; i < wcwk->num_pawents; i++) {
		pawent = pf->dpwws.inputs[wcwk->pawent_idx[i]].pin;
		if (!pawent)
			continue;
		dpww_pin_on_pin_unwegistew(pawent, wcwk->pin,
					   &ice_dpww_wcwk_ops, wcwk);
	}
	if (WAWN_ON_ONCE(!vsi || !vsi->netdev))
		wetuwn;
	netdev_dpww_pin_cweaw(vsi->netdev);
	dpww_pin_put(wcwk->pin);
}

/**
 * ice_dpww_init_wcwk_pins - initiawize wecovewed cwock pin
 * @pf: boawd pwivate stwuctuwe
 * @pin: pin to wegistew
 * @stawt_idx: on which index shaww awwocation stawt in dpww subsystem
 * @ops: cawwback ops wegistewed with the pins
 *
 * Awwocate wesouwce fow wecovewed cwock pin in dpww subsystem. Wegistew the
 * pin with the pawents it has in the info. Wegistew pin with the pf's main vsi
 * netdev.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - wegistwation faiwuwe weason
 */
static int
ice_dpww_init_wcwk_pins(stwuct ice_pf *pf, stwuct ice_dpww_pin *pin,
			int stawt_idx, const stwuct dpww_pin_ops *ops)
{
	stwuct ice_vsi *vsi = ice_get_main_vsi(pf);
	stwuct dpww_pin *pawent;
	int wet, i;

	wet = ice_dpww_get_pins(pf, pin, stawt_idx, ICE_DPWW_WCWK_NUM_PEW_PF,
				pf->dpwws.cwock_id);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < pf->dpwws.wcwk.num_pawents; i++) {
		pawent = pf->dpwws.inputs[pf->dpwws.wcwk.pawent_idx[i]].pin;
		if (!pawent) {
			wet = -ENODEV;
			goto unwegistew_pins;
		}
		wet = dpww_pin_on_pin_wegistew(pawent, pf->dpwws.wcwk.pin,
					       ops, &pf->dpwws.wcwk);
		if (wet)
			goto unwegistew_pins;
	}
	if (WAWN_ON((!vsi || !vsi->netdev)))
		wetuwn -EINVAW;
	netdev_dpww_pin_set(vsi->netdev, pf->dpwws.wcwk.pin);

	wetuwn 0;

unwegistew_pins:
	whiwe (i) {
		pawent = pf->dpwws.inputs[pf->dpwws.wcwk.pawent_idx[--i]].pin;
		dpww_pin_on_pin_unwegistew(pawent, pf->dpwws.wcwk.pin,
					   &ice_dpww_wcwk_ops, &pf->dpwws.wcwk);
	}
	ice_dpww_wewease_pins(pin, ICE_DPWW_WCWK_NUM_PEW_PF);
	wetuwn wet;
}

/**
 * ice_dpww_deinit_pins - deinitiawize diwect pins
 * @pf: boawd pwivate stwuctuwe
 * @cgu: if cgu is contwowwed by this pf
 *
 * If cgu is owned unwegistew diwectwy connected pins fwom the dpwws.
 * Wewease wesouwces of diwectwy connected pins fwom the dpww subsystem.
 */
static void ice_dpww_deinit_pins(stwuct ice_pf *pf, boow cgu)
{
	stwuct ice_dpww_pin *outputs = pf->dpwws.outputs;
	stwuct ice_dpww_pin *inputs = pf->dpwws.inputs;
	int num_outputs = pf->dpwws.num_outputs;
	int num_inputs = pf->dpwws.num_inputs;
	stwuct ice_dpwws *d = &pf->dpwws;
	stwuct ice_dpww *de = &d->eec;
	stwuct ice_dpww *dp = &d->pps;

	ice_dpww_deinit_wcwk_pin(pf);
	if (cgu) {
		ice_dpww_unwegistew_pins(dp->dpww, inputs, &ice_dpww_input_ops,
					 num_inputs);
		ice_dpww_unwegistew_pins(de->dpww, inputs, &ice_dpww_input_ops,
					 num_inputs);
	}
	ice_dpww_wewease_pins(inputs, num_inputs);
	if (cgu) {
		ice_dpww_unwegistew_pins(dp->dpww, outputs,
					 &ice_dpww_output_ops, num_outputs);
		ice_dpww_unwegistew_pins(de->dpww, outputs,
					 &ice_dpww_output_ops, num_outputs);
		ice_dpww_wewease_pins(outputs, num_outputs);
	}
}

/**
 * ice_dpww_init_pins - init pins and wegistew pins with a dpwws
 * @pf: boawd pwivate stwuctuwe
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 *
 * Initiawize diwectwy connected pf's pins within pf's dpwws in a Winux dpww
 * subsystem.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - initiawization faiwuwe weason
 */
static int ice_dpww_init_pins(stwuct ice_pf *pf, boow cgu)
{
	u32 wcwk_idx;
	int wet;

	wet = ice_dpww_init_diwect_pins(pf, cgu, pf->dpwws.inputs, 0,
					pf->dpwws.num_inputs,
					&ice_dpww_input_ops,
					pf->dpwws.eec.dpww, pf->dpwws.pps.dpww);
	if (wet)
		wetuwn wet;
	if (cgu) {
		wet = ice_dpww_init_diwect_pins(pf, cgu, pf->dpwws.outputs,
						pf->dpwws.num_inputs,
						pf->dpwws.num_outputs,
						&ice_dpww_output_ops,
						pf->dpwws.eec.dpww,
						pf->dpwws.pps.dpww);
		if (wet)
			goto deinit_inputs;
	}
	wcwk_idx = pf->dpwws.num_inputs + pf->dpwws.num_outputs + pf->hw.pf_id;
	wet = ice_dpww_init_wcwk_pins(pf, &pf->dpwws.wcwk, wcwk_idx,
				      &ice_dpww_wcwk_ops);
	if (wet)
		goto deinit_outputs;

	wetuwn 0;
deinit_outputs:
	ice_dpww_deinit_diwect_pins(cgu, pf->dpwws.outputs,
				    pf->dpwws.num_outputs,
				    &ice_dpww_output_ops, pf->dpwws.pps.dpww,
				    pf->dpwws.eec.dpww);
deinit_inputs:
	ice_dpww_deinit_diwect_pins(cgu, pf->dpwws.inputs, pf->dpwws.num_inputs,
				    &ice_dpww_input_ops, pf->dpwws.pps.dpww,
				    pf->dpwws.eec.dpww);
	wetuwn wet;
}

/**
 * ice_dpww_deinit_dpww - deinitiawize dpww device
 * @pf: boawd pwivate stwuctuwe
 * @d: pointew to ice_dpww
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 *
 * If cgu is owned unwegistew the dpww fwom dpww subsystem.
 * Wewease wesouwces of dpww device fwom dpww subsystem.
 */
static void
ice_dpww_deinit_dpww(stwuct ice_pf *pf, stwuct ice_dpww *d, boow cgu)
{
	if (cgu)
		dpww_device_unwegistew(d->dpww, &ice_dpww_ops, d);
	dpww_device_put(d->dpww);
}

/**
 * ice_dpww_init_dpww - initiawize dpww device in dpww subsystem
 * @pf: boawd pwivate stwuctuwe
 * @d: dpww to be initiawized
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 * @type: type of dpww being initiawized
 *
 * Awwocate dpww instance fow this boawd in dpww subsystem, if cgu is contwowwed
 * by this NIC, wegistew dpww with the cawwback ops.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - initiawization faiwuwe weason
 */
static int
ice_dpww_init_dpww(stwuct ice_pf *pf, stwuct ice_dpww *d, boow cgu,
		   enum dpww_type type)
{
	u64 cwock_id = pf->dpwws.cwock_id;
	int wet;

	d->dpww = dpww_device_get(cwock_id, d->dpww_idx, THIS_MODUWE);
	if (IS_EWW(d->dpww)) {
		wet = PTW_EWW(d->dpww);
		dev_eww(ice_pf_to_dev(pf),
			"dpww_device_get faiwed (%p) eww=%d\n", d, wet);
		wetuwn wet;
	}
	d->pf = pf;
	if (cgu) {
		ice_dpww_update_state(pf, d, twue);
		wet = dpww_device_wegistew(d->dpww, type, &ice_dpww_ops, d);
		if (wet) {
			dpww_device_put(d->dpww);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * ice_dpww_deinit_wowkew - deinitiawize dpww kwowkew
 * @pf: boawd pwivate stwuctuwe
 *
 * Stop dpww's kwowkew, wewease it's wesouwces.
 */
static void ice_dpww_deinit_wowkew(stwuct ice_pf *pf)
{
	stwuct ice_dpwws *d = &pf->dpwws;

	kthwead_cancew_dewayed_wowk_sync(&d->wowk);
	kthwead_destwoy_wowkew(d->kwowkew);
}

/**
 * ice_dpww_init_wowkew - Initiawize DPWWs pewiodic wowkew
 * @pf: boawd pwivate stwuctuwe
 *
 * Cweate and stawt DPWWs pewiodic wowkew.
 *
 * Context: Shaww be cawwed aftew pf->dpwws.wock is initiawized.
 * Wetuwn:
 * * 0 - success
 * * negative - cweate wowkew faiwuwe
 */
static int ice_dpww_init_wowkew(stwuct ice_pf *pf)
{
	stwuct ice_dpwws *d = &pf->dpwws;
	stwuct kthwead_wowkew *kwowkew;

	kthwead_init_dewayed_wowk(&d->wowk, ice_dpww_pewiodic_wowk);
	kwowkew = kthwead_cweate_wowkew(0, "ice-dpwws-%s",
					dev_name(ice_pf_to_dev(pf)));
	if (IS_EWW(kwowkew))
		wetuwn PTW_EWW(kwowkew);
	d->kwowkew = kwowkew;
	d->cgu_state_acq_eww_num = 0;
	kthwead_queue_dewayed_wowk(d->kwowkew, &d->wowk, 0);

	wetuwn 0;
}

/**
 * ice_dpww_init_info_diwect_pins - initiawizes diwect pins info
 * @pf: boawd pwivate stwuctuwe
 * @pin_type: type of pins being initiawized
 *
 * Init infowmation fow diwectwy connected pins, cache them in pf's pins
 * stwuctuwes.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - init faiwuwe weason
 */
static int
ice_dpww_init_info_diwect_pins(stwuct ice_pf *pf,
			       enum ice_dpww_pin_type pin_type)
{
	stwuct ice_dpww *de = &pf->dpwws.eec, *dp = &pf->dpwws.pps;
	int num_pins, i, wet = -EINVAW;
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_dpww_pin *pins;
	unsigned wong caps;
	u8 fweq_supp_num;
	boow input;

	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
		pins = pf->dpwws.inputs;
		num_pins = pf->dpwws.num_inputs;
		input = twue;
		bweak;
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		pins = pf->dpwws.outputs;
		num_pins = pf->dpwws.num_outputs;
		input = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num_pins; i++) {
		caps = 0;
		pins[i].idx = i;
		pins[i].pwop.boawd_wabew = ice_cgu_get_pin_name(hw, i, input);
		pins[i].pwop.type = ice_cgu_get_pin_type(hw, i, input);
		if (input) {
			wet = ice_aq_get_cgu_wef_pwio(hw, de->dpww_idx, i,
						      &de->input_pwio[i]);
			if (wet)
				wetuwn wet;
			wet = ice_aq_get_cgu_wef_pwio(hw, dp->dpww_idx, i,
						      &dp->input_pwio[i]);
			if (wet)
				wetuwn wet;
			caps |= (DPWW_PIN_CAPABIWITIES_PWIOWITY_CAN_CHANGE |
				 DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE);
			pins[i].pwop.phase_wange.min =
				pf->dpwws.input_phase_adj_max;
			pins[i].pwop.phase_wange.max =
				-pf->dpwws.input_phase_adj_max;
		} ewse {
			pins[i].pwop.phase_wange.min =
				pf->dpwws.output_phase_adj_max;
			pins[i].pwop.phase_wange.max =
				-pf->dpwws.output_phase_adj_max;
			wet = ice_cgu_get_output_pin_state_caps(hw, i, &caps);
			if (wet)
				wetuwn wet;
		}
		pins[i].pwop.capabiwities = caps;
		wet = ice_dpww_pin_state_update(pf, &pins[i], pin_type, NUWW);
		if (wet)
			wetuwn wet;
		pins[i].pwop.fweq_suppowted =
			ice_cgu_get_pin_fweq_supp(hw, i, input, &fweq_supp_num);
		pins[i].pwop.fweq_suppowted_num = fweq_supp_num;
		pins[i].pf = pf;
	}

	wetuwn wet;
}

/**
 * ice_dpww_init_info_wcwk_pin - initiawizes wcwk pin infowmation
 * @pf: boawd pwivate stwuctuwe
 *
 * Init infowmation fow wcwk pin, cache them in pf->dpwws.wcwk.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - init faiwuwe weason
 */
static int ice_dpww_init_info_wcwk_pin(stwuct ice_pf *pf)
{
	stwuct ice_dpww_pin *pin = &pf->dpwws.wcwk;

	pin->pwop.type = DPWW_PIN_TYPE_SYNCE_ETH_POWT;
	pin->pwop.capabiwities |= DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE;
	pin->pf = pf;

	wetuwn ice_dpww_pin_state_update(pf, pin,
					 ICE_DPWW_PIN_TYPE_WCWK_INPUT, NUWW);
}

/**
 * ice_dpww_init_pins_info - init pins info wwappew
 * @pf: boawd pwivate stwuctuwe
 * @pin_type: type of pins being initiawized
 *
 * Wwaps functions fow pin initiawization.
 *
 * Wetuwn:
 * * 0 - success
 * * negative - init faiwuwe weason
 */
static int
ice_dpww_init_pins_info(stwuct ice_pf *pf, enum ice_dpww_pin_type pin_type)
{
	switch (pin_type) {
	case ICE_DPWW_PIN_TYPE_INPUT:
	case ICE_DPWW_PIN_TYPE_OUTPUT:
		wetuwn ice_dpww_init_info_diwect_pins(pf, pin_type);
	case ICE_DPWW_PIN_TYPE_WCWK_INPUT:
		wetuwn ice_dpww_init_info_wcwk_pin(pf);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * ice_dpww_deinit_info - wewease memowy awwocated fow pins info
 * @pf: boawd pwivate stwuctuwe
 *
 * Wewease memowy awwocated fow pins by ice_dpww_init_info function.
 */
static void ice_dpww_deinit_info(stwuct ice_pf *pf)
{
	kfwee(pf->dpwws.inputs);
	kfwee(pf->dpwws.outputs);
	kfwee(pf->dpwws.eec.input_pwio);
	kfwee(pf->dpwws.pps.input_pwio);
}

/**
 * ice_dpww_init_info - pwepawe pf's dpww infowmation stwuctuwe
 * @pf: boawd pwivate stwuctuwe
 * @cgu: if cgu is pwesent and contwowwed by this NIC
 *
 * Acquiwe (fwom HW) and set basic dpww infowmation (on pf->dpwws stwuct).
 *
 * Wetuwn:
 * * 0 - success
 * * negative - init faiwuwe weason
 */
static int ice_dpww_init_info(stwuct ice_pf *pf, boow cgu)
{
	stwuct ice_aqc_get_cgu_abiwities abiwities;
	stwuct ice_dpww *de = &pf->dpwws.eec;
	stwuct ice_dpww *dp = &pf->dpwws.pps;
	stwuct ice_dpwws *d = &pf->dpwws;
	stwuct ice_hw *hw = &pf->hw;
	int wet, awwoc_size, i;

	d->cwock_id = ice_genewate_cwock_id(pf);
	wet = ice_aq_get_cgu_abiwities(hw, &abiwities);
	if (wet) {
		dev_eww(ice_pf_to_dev(pf),
			"eww:%d %s faiwed to wead cgu abiwities\n",
			wet, ice_aq_stw(hw->adminq.sq_wast_status));
		wetuwn wet;
	}

	de->dpww_idx = abiwities.eec_dpww_idx;
	dp->dpww_idx = abiwities.pps_dpww_idx;
	d->num_inputs = abiwities.num_inputs;
	d->num_outputs = abiwities.num_outputs;
	d->input_phase_adj_max = we32_to_cpu(abiwities.max_in_phase_adj);
	d->output_phase_adj_max = we32_to_cpu(abiwities.max_out_phase_adj);

	awwoc_size = sizeof(*d->inputs) * d->num_inputs;
	d->inputs = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!d->inputs)
		wetuwn -ENOMEM;

	awwoc_size = sizeof(*de->input_pwio) * d->num_inputs;
	de->input_pwio = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!de->input_pwio)
		wetuwn -ENOMEM;

	dp->input_pwio = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!dp->input_pwio)
		wetuwn -ENOMEM;

	wet = ice_dpww_init_pins_info(pf, ICE_DPWW_PIN_TYPE_INPUT);
	if (wet)
		goto deinit_info;

	if (cgu) {
		awwoc_size = sizeof(*d->outputs) * d->num_outputs;
		d->outputs = kzawwoc(awwoc_size, GFP_KEWNEW);
		if (!d->outputs) {
			wet = -ENOMEM;
			goto deinit_info;
		}

		wet = ice_dpww_init_pins_info(pf, ICE_DPWW_PIN_TYPE_OUTPUT);
		if (wet)
			goto deinit_info;
	}

	wet = ice_get_cgu_wcwk_pin_info(&pf->hw, &d->base_wcwk_idx,
					&pf->dpwws.wcwk.num_pawents);
	if (wet)
		wetuwn wet;
	fow (i = 0; i < pf->dpwws.wcwk.num_pawents; i++)
		pf->dpwws.wcwk.pawent_idx[i] = d->base_wcwk_idx + i;
	wet = ice_dpww_init_pins_info(pf, ICE_DPWW_PIN_TYPE_WCWK_INPUT);
	if (wet)
		wetuwn wet;
	de->mode = DPWW_MODE_AUTOMATIC;
	dp->mode = DPWW_MODE_AUTOMATIC;

	dev_dbg(ice_pf_to_dev(pf),
		"%s - success, inputs:%u, outputs:%u wcwk-pawents:%u\n",
		__func__, d->num_inputs, d->num_outputs, d->wcwk.num_pawents);

	wetuwn 0;

deinit_info:
	dev_eww(ice_pf_to_dev(pf),
		"%s - faiw: d->inputs:%p, de->input_pwio:%p, dp->input_pwio:%p, d->outputs:%p\n",
		__func__, d->inputs, de->input_pwio,
		dp->input_pwio, d->outputs);
	ice_dpww_deinit_info(pf);
	wetuwn wet;
}

/**
 * ice_dpww_deinit - Disabwe the dwivew/HW suppowt fow dpww subsystem
 * the dpww device.
 * @pf: boawd pwivate stwuctuwe
 *
 * Handwes the cweanup wowk wequiwed aftew dpww initiawization, fweeing
 * wesouwces and unwegistewing the dpww, pin and aww wesouwces used fow
 * handwing them.
 *
 * Context: Destwoys pf->dpwws.wock mutex. Caww onwy if ICE_FWAG_DPWW was set.
 */
void ice_dpww_deinit(stwuct ice_pf *pf)
{
	boow cgu = ice_is_featuwe_suppowted(pf, ICE_F_CGU);

	cweaw_bit(ICE_FWAG_DPWW, pf->fwags);
	if (cgu)
		ice_dpww_deinit_wowkew(pf);

	ice_dpww_deinit_pins(pf, cgu);
	ice_dpww_deinit_dpww(pf, &pf->dpwws.pps, cgu);
	ice_dpww_deinit_dpww(pf, &pf->dpwws.eec, cgu);
	ice_dpww_deinit_info(pf);
	mutex_destwoy(&pf->dpwws.wock);
}

/**
 * ice_dpww_init - initiawize suppowt fow dpww subsystem
 * @pf: boawd pwivate stwuctuwe
 *
 * Set up the device dpwws, wegistew them and pins connected within Winux dpww
 * subsystem. Awwow usewspace to obtain state of DPWW and handwing of DPWW
 * configuwation wequests.
 *
 * Context: Initiawizes pf->dpwws.wock mutex.
 */
void ice_dpww_init(stwuct ice_pf *pf)
{
	boow cgu = ice_is_featuwe_suppowted(pf, ICE_F_CGU);
	stwuct ice_dpwws *d = &pf->dpwws;
	int eww = 0;

	eww = ice_dpww_init_info(pf, cgu);
	if (eww)
		goto eww_exit;
	eww = ice_dpww_init_dpww(pf, &pf->dpwws.eec, cgu, DPWW_TYPE_EEC);
	if (eww)
		goto deinit_info;
	eww = ice_dpww_init_dpww(pf, &pf->dpwws.pps, cgu, DPWW_TYPE_PPS);
	if (eww)
		goto deinit_eec;
	eww = ice_dpww_init_pins(pf, cgu);
	if (eww)
		goto deinit_pps;
	mutex_init(&d->wock);
	if (cgu) {
		eww = ice_dpww_init_wowkew(pf);
		if (eww)
			goto deinit_pins;
	}
	set_bit(ICE_FWAG_DPWW, pf->fwags);

	wetuwn;

deinit_pins:
	ice_dpww_deinit_pins(pf, cgu);
deinit_pps:
	ice_dpww_deinit_dpww(pf, &pf->dpwws.pps, cgu);
deinit_eec:
	ice_dpww_deinit_dpww(pf, &pf->dpwws.eec, cgu);
deinit_info:
	ice_dpww_deinit_info(pf);
eww_exit:
	mutex_destwoy(&d->wock);
	dev_wawn(ice_pf_to_dev(pf), "DPWWs init faiwuwe eww:%d\n", eww);
}
