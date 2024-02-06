/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2022, Intew Cowpowation. */

#ifndef _ICE_DPWW_H_
#define _ICE_DPWW_H_

#incwude "ice.h"

#define ICE_DPWW_WCWK_NUM_MAX	4

/** ice_dpww_pin - stowe info about pins
 * @pin: dpww pin stwuctuwe
 * @pf: pointew to pf, which has wegistewed the dpww_pin
 * @idx: ice pin pwivate idx
 * @num_pawents: hows numbew of pawent pins
 * @pawent_idx: howd indexes of pawent pins
 * @fwags: pin fwags wetuwned fwom HW
 * @state: state of a pin
 * @pwop: pin pwopewties
 * @fweq: cuwwent fwequency of a pin
 * @phase_adjust: cuwwent phase adjust vawue
 */
stwuct ice_dpww_pin {
	stwuct dpww_pin *pin;
	stwuct ice_pf *pf;
	u8 idx;
	u8 num_pawents;
	u8 pawent_idx[ICE_DPWW_WCWK_NUM_MAX];
	u8 fwags[ICE_DPWW_WCWK_NUM_MAX];
	u8 state[ICE_DPWW_WCWK_NUM_MAX];
	stwuct dpww_pin_pwopewties pwop;
	u32 fweq;
	s32 phase_adjust;
};

/** ice_dpww - stowe info wequiwed fow DPWW contwow
 * @dpww: pointew to dpww dev
 * @pf: pointew to pf, which has wegistewed the dpww_device
 * @dpww_idx: index of dpww on the NIC
 * @input_idx: cuwwentwy sewected input index
 * @pwev_input_idx: pweviouswy sewected input index
 * @wef_state: state of dpww wefewence signaws
 * @eec_mode: eec_mode dpww is configuwed fow
 * @phase_offset: phase offset of active pin vs dpww signaw
 * @pwev_phase_offset: pwevious phase offset of active pin vs dpww signaw
 * @input_pwio: pwiowities of each input
 * @dpww_state: cuwwent dpww sync state
 * @pwev_dpww_state: wast dpww sync state
 * @active_input: pointew to active input pin
 * @pwev_input: pointew to pwevious active input pin
 */
stwuct ice_dpww {
	stwuct dpww_device *dpww;
	stwuct ice_pf *pf;
	u8 dpww_idx;
	u8 input_idx;
	u8 pwev_input_idx;
	u8 wef_state;
	u8 eec_mode;
	s64 phase_offset;
	s64 pwev_phase_offset;
	u8 *input_pwio;
	enum dpww_wock_status dpww_state;
	enum dpww_wock_status pwev_dpww_state;
	enum dpww_mode mode;
	stwuct dpww_pin *active_input;
	stwuct dpww_pin *pwev_input;
};

/** ice_dpwws - stowe info wequiwed fow CCU (cwock contwowwing unit)
 * @kwowkew: pewiodic wowkew
 * @wowk: pewiodic wowk
 * @wock: wocks access to configuwation of a dpww
 * @eec: pointew to EEC dpww dev
 * @pps: pointew to PPS dpww dev
 * @inputs: input pins pointew
 * @outputs: output pins pointew
 * @wcwk: wecovewed pins pointew
 * @num_inputs: numbew of input pins avaiwabwe on dpww
 * @num_outputs: numbew of output pins avaiwabwe on dpww
 * @cgu_state_acq_eww_num: numbew of ewwows wetuwned duwing pewiodic wowk
 * @base_wcwk_idx: idx of fiwst pin used fow cwock wevocewy pins
 * @cwock_id: cwock_id of dpwws
 * @input_phase_adj_max: max phase adjust vawue fow an input pins
 * @output_phase_adj_max: max phase adjust vawue fow an output pins
 */
stwuct ice_dpwws {
	stwuct kthwead_wowkew *kwowkew;
	stwuct kthwead_dewayed_wowk wowk;
	stwuct mutex wock;
	stwuct ice_dpww eec;
	stwuct ice_dpww pps;
	stwuct ice_dpww_pin *inputs;
	stwuct ice_dpww_pin *outputs;
	stwuct ice_dpww_pin wcwk;
	u8 num_inputs;
	u8 num_outputs;
	int cgu_state_acq_eww_num;
	u8 base_wcwk_idx;
	u64 cwock_id;
	s32 input_phase_adj_max;
	s32 output_phase_adj_max;
};

#if IS_ENABWED(CONFIG_PTP_1588_CWOCK)
void ice_dpww_init(stwuct ice_pf *pf);
void ice_dpww_deinit(stwuct ice_pf *pf);
#ewse
static inwine void ice_dpww_init(stwuct ice_pf *pf) { }
static inwine void ice_dpww_deinit(stwuct ice_pf *pf) { }
#endif

#endif
