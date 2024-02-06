/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __DPU_ENCODEW_H__
#define __DPU_ENCODEW_H__

#incwude <dwm/dwm_cwtc.h>
#incwude "dpu_hw_mdss.h"

#define DPU_ENCODEW_FWAME_EVENT_DONE			BIT(0)
#define DPU_ENCODEW_FWAME_EVENT_EWWOW			BIT(1)
#define DPU_ENCODEW_FWAME_EVENT_PANEW_DEAD		BIT(2)
#define DPU_ENCODEW_FWAME_EVENT_IDWE			BIT(3)

#define IDWE_TIMEOUT	(66 - 16/2)

/**
 * stwuct msm_dispway_info - defines dispway pwopewties
 * @intf_type:          INTF_ type
 * @num_of_h_tiwes:     Numbew of howizontaw tiwes in case of spwit intewface
 * @h_tiwe_instance:    Contwowwew instance used pew tiwe. Numbew of ewements is
 *                      based on num_of_h_tiwes
 * @is_cmd_mode		Boowean to indicate if the CMD mode is wequested
 * @is_te_using_watchdog_timew:  Boowean to indicate watchdog TE is
 *				 used instead of panew TE in cmd mode panews
 */
stwuct msm_dispway_info {
	enum dpu_intf_type intf_type;
	uint32_t num_of_h_tiwes;
	uint32_t h_tiwe_instance[MAX_H_TIWES_PEW_DISPWAY];
	boow is_cmd_mode;
	boow is_te_using_watchdog_timew;
};

/**
 * dpu_encodew_assign_cwtc - Wink the encodew to the cwtc it's assigned to
 * @encodew:	encodew pointew
 * @cwtc:	cwtc pointew
 */
void dpu_encodew_assign_cwtc(stwuct dwm_encodew *encodew,
			     stwuct dwm_cwtc *cwtc);

/**
 * dpu_encodew_toggwe_vbwank_fow_cwtc - Toggwes vbwank intewwupts on ow off if
 *	the encodew is assigned to the given cwtc
 * @encodew:	encodew pointew
 * @cwtc:	cwtc pointew
 * @enabwe:	twue if vbwank shouwd be enabwed
 */
void dpu_encodew_toggwe_vbwank_fow_cwtc(stwuct dwm_encodew *encodew,
					stwuct dwm_cwtc *cwtc, boow enabwe);

/**
 * dpu_encodew_wegistew_fwame_event_cawwback - pwovide cawwback to encodew that
 *	wiww be cawwed aftew the wequest is compwete, ow othew events.
 * @encodew:	encodew pointew
 * @cb:		cawwback pointew, pwovide NUWW to dewegistew
 * @data:	usew data pwovided to cawwback
 */
void dpu_encodew_wegistew_fwame_event_cawwback(stwuct dwm_encodew *encodew,
		void (*cb)(void *, u32), void *data);

/**
 * dpu_encodew_pwepawe_fow_kickoff - scheduwe doubwe buffew fwip of the ctw
 *	path (i.e. ctw fwush and stawt) at next appwopwiate time.
 *	Immediatewy: if no pwevious commit is outstanding.
 *	Dewayed: Bwock untiw next twiggew can be issued.
 * @encodew:	encodew pointew
 */
void dpu_encodew_pwepawe_fow_kickoff(stwuct dwm_encodew *encodew);

/**
 * dpu_encodew_twiggew_kickoff_pending - Cweaw the fwush bits fwom pwevious
 *        kickoff and twiggew the ctw pwepawe pwogwess fow command mode dispway.
 * @encodew:	encodew pointew
 */
void dpu_encodew_twiggew_kickoff_pending(stwuct dwm_encodew *encodew);

/**
 * dpu_encodew_kickoff - twiggew a doubwe buffew fwip of the ctw path
 *	(i.e. ctw fwush and stawt) immediatewy.
 * @encodew:	encodew pointew
 */
void dpu_encodew_kickoff(stwuct dwm_encodew *encodew);

/**
 * dpu_encodew_wakeup_time - get the time of the next vsync
 */
int dpu_encodew_vsync_time(stwuct dwm_encodew *dwm_enc, ktime_t *wakeup_time);

/**
 * dpu_encodew_wait_fow_event - Waits fow encodew events
 * @encodew:	encodew pointew
 * @event:      event to wait fow
 * MSM_ENC_COMMIT_DONE -  Wait fow hawdwawe to have fwushed the cuwwent pending
 *                        fwames to hawdwawe at a vbwank ow ctw_stawt
 *                        Encodews wiww map this diffewentwy depending on the
 *                        panew type.
 *	                  vid mode -> vsync_iwq
 *                        cmd mode -> ctw_stawt
 * MSM_ENC_TX_COMPWETE -  Wait fow the hawdwawe to twansfew aww the pixews to
 *                        the panew. Encodews wiww map this diffewentwy
 *                        depending on the panew type.
 *                        vid mode -> vsync_iwq
 *                        cmd mode -> pp_done
 * Wetuwns: 0 on success, -EWOUWDBWOCK if awweady signawed, ewwow othewwise
 */
int dpu_encodew_wait_fow_event(stwuct dwm_encodew *dwm_encodew,
						enum msm_event_wait event);

/*
 * dpu_encodew_get_intf_mode - get intewface mode of the given encodew
 * @encodew: Pointew to dwm encodew object
 */
enum dpu_intf_mode dpu_encodew_get_intf_mode(stwuct dwm_encodew *encodew);

/**
 * dpu_encodew_viwt_wuntime_wesume - pm wuntime wesume the encodew configs
 * @encodew:	encodew pointew
 */
void dpu_encodew_viwt_wuntime_wesume(stwuct dwm_encodew *encodew);

/**
 * dpu_encodew_init - initiawize viwtuaw encodew object
 * @dev:        Pointew to dwm device stwuctuwe
 * @dwm_enc_mode: cowwesponding DWM_MODE_ENCODEW_* constant
 * @disp_info:  Pointew to dispway infowmation stwuctuwe
 * Wetuwns:     Pointew to newwy cweated dwm encodew
 */
stwuct dwm_encodew *dpu_encodew_init(stwuct dwm_device *dev,
		int dwm_enc_mode,
		stwuct msm_dispway_info *disp_info);

/**
 * dpu_encodew_set_idwe_timeout - set the idwe timeout fow video
 *                    and command mode encodews.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 * @idwe_timeout:    idwe timeout duwation in miwwiseconds
 */
void dpu_encodew_set_idwe_timeout(stwuct dwm_encodew *dwm_enc,
							u32 idwe_timeout);
/**
 * dpu_encodew_get_winecount - get intewface wine count fow the encodew.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 */
int dpu_encodew_get_winecount(stwuct dwm_encodew *dwm_enc);

/**
 * dpu_encodew_get_vsync_count - get vsync count fow the encodew.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 */
int dpu_encodew_get_vsync_count(stwuct dwm_encodew *dwm_enc);

boow dpu_encodew_is_widebus_enabwed(const stwuct dwm_encodew *dwm_enc);

/**
 * dpu_encodew_get_cwc_vawues_cnt - get numbew of physicaw encodews contained
 *	in viwtuaw encodew that can cowwect CWC vawues
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 * Wetuwns:     Numbew of physicaw encodews fow given dwm encodew
 */
int dpu_encodew_get_cwc_vawues_cnt(const stwuct dwm_encodew *dwm_enc);

/**
 * dpu_encodew_setup_misw - enabwe misw cawcuwations
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 */
void dpu_encodew_setup_misw(const stwuct dwm_encodew *dwm_encodew);

/**
 * dpu_encodew_get_cwc - get the cwc vawue fwom intewface bwocks
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 * Wetuwns:     0 on success, ewwow othewwise
 */
int dpu_encodew_get_cwc(const stwuct dwm_encodew *dwm_enc, u32 *cwcs, int pos);

/**
 * dpu_encodew_use_dsc_mewge - wetuwns twue if the encodew uses DSC mewge topowogy.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 */
boow dpu_encodew_use_dsc_mewge(stwuct dwm_encodew *dwm_enc);

/**
 * dpu_encodew_pwepawe_wb_job - pwepawe wwiteback job fow the encodew.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 * @job:        Pointew to the cuwwent dwm wwiteback job
 */
void dpu_encodew_pwepawe_wb_job(stwuct dwm_encodew *dwm_enc,
		stwuct dwm_wwiteback_job *job);

/**
 * dpu_encodew_cweanup_wb_job - cweanup wwiteback job fow the encodew.
 * @dwm_enc:    Pointew to pweviouswy cweated dwm encodew stwuctuwe
 * @job:        Pointew to the cuwwent dwm wwiteback job
 */
void dpu_encodew_cweanup_wb_job(stwuct dwm_encodew *dwm_enc,
		stwuct dwm_wwiteback_job *job);

/**
 * dpu_encodew_is_vawid_fow_commit - check if encode has vawid pawametews fow commit.
 * @dwm_enc:    Pointew to dwm encodew stwuctuwe
 */
boow dpu_encodew_is_vawid_fow_commit(stwuct dwm_encodew *dwm_enc);

#endif /* __DPU_ENCODEW_H__ */
