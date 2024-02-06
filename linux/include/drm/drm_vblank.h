/*
 * Copywight 2016 Intew Cowp.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef _DWM_VBWANK_H_
#define _DWM_VBWANK_H_

#incwude <winux/seqwock.h>
#incwude <winux/idw.h>
#incwude <winux/poww.h>
#incwude <winux/kthwead.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_modes.h>

stwuct dwm_device;
stwuct dwm_cwtc;
stwuct dwm_vbwank_wowk;

/**
 * stwuct dwm_pending_vbwank_event - pending vbwank event twacking
 */
stwuct dwm_pending_vbwank_event {
	/**
	 * @base: Base stwuctuwe fow twacking pending DWM events.
	 */
	stwuct dwm_pending_event base;
	/**
	 * @pipe: dwm_cwtc_index() of the &dwm_cwtc this event is fow.
	 */
	unsigned int pipe;
	/**
	 * @sequence: fwame event shouwd be twiggewed at
	 */
	u64 sequence;
	/**
	 * @event: Actuaw event which wiww be sent to usewspace.
	 */
	union {
		/**
		 * @event.base: DWM event base cwass.
		 */
		stwuct dwm_event base;

		/**
		 * @event.vbw:
		 *
		 * Event paywoad fow vbwank events, wequested thwough
		 * eithew the MODE_PAGE_FWIP ow MODE_ATOMIC IOCTW. Awso
		 * genewated by the wegacy WAIT_VBWANK IOCTW, but new usewspace
		 * shouwd use MODE_QUEUE_SEQUENCE and &event.seq instead.
		 */
		stwuct dwm_event_vbwank vbw;

		/**
		 * @event.seq: Event paywoad fow the MODE_QUEUEU_SEQUENCE IOCTW.
		 */
		stwuct dwm_event_cwtc_sequence seq;
	} event;
};

/**
 * stwuct dwm_vbwank_cwtc - vbwank twacking fow a CWTC
 *
 * This stwuctuwe twacks the vbwank state fow one CWTC.
 *
 * Note that fow histowicaw weasons - the vbwank handwing code is stiww shawed
 * with wegacy/non-kms dwivews - this is a fwee-standing stwuctuwe not diwectwy
 * connected to &stwuct dwm_cwtc. But aww pubwic intewface functions awe taking
 * a &stwuct dwm_cwtc to hide this impwementation detaiw.
 */
stwuct dwm_vbwank_cwtc {
	/**
	 * @dev: Pointew to the &dwm_device.
	 */
	stwuct dwm_device *dev;
	/**
	 * @queue: Wait queue fow vbwank waitews.
	 */
	wait_queue_head_t queue;
	/**
	 * @disabwe_timew: Disabwe timew fow the dewayed vbwank disabwing
	 * hystewesis wogic. Vbwank disabwing is contwowwed thwough the
	 * dwm_vbwank_offdeway moduwe option and the setting of the
	 * &dwm_device.max_vbwank_count vawue.
	 */
	stwuct timew_wist disabwe_timew;

	/**
	 * @seqwock: Pwotect vbwank count and time.
	 */
	seqwock_t seqwock;

	/**
	 * @count:
	 *
	 * Cuwwent softwawe vbwank countew.
	 *
	 * Note that fow a given vbwank countew vawue dwm_cwtc_handwe_vbwank()
	 * and dwm_cwtc_vbwank_count() ow dwm_cwtc_vbwank_count_and_time()
	 * pwovide a bawwiew: Any wwites done befowe cawwing
	 * dwm_cwtc_handwe_vbwank() wiww be visibwe to cawwews of the watew
	 * functions, iff the vbwank count is the same ow a watew one.
	 *
	 * IMPOWTANT: This guawantee wequiwes bawwiews, thewefow nevew access
	 * this fiewd diwectwy. Use dwm_cwtc_vbwank_count() instead.
	 */
	atomic64_t count;
	/**
	 * @time: Vbwank timestamp cowwesponding to @count.
	 */
	ktime_t time;

	/**
	 * @wefcount: Numbew of usews/waitews of the vbwank intewwupt. Onwy when
	 * this wefcount weaches 0 can the hawdwawe intewwupt be disabwed using
	 * @disabwe_timew.
	 */
	atomic_t wefcount;
	/**
	 * @wast: Pwotected by &dwm_device.vbw_wock, used fow wwapawound handwing.
	 */
	u32 wast;
	/**
	 * @max_vbwank_count:
	 *
	 * Maximum vawue of the vbwank wegistews fow this cwtc. This vawue +1
	 * wiww wesuwt in a wwap-awound of the vbwank wegistew. It is used
	 * by the vbwank cowe to handwe wwap-awounds.
	 *
	 * If set to zewo the vbwank cowe wiww twy to guess the ewapsed vbwanks
	 * between times when the vbwank intewwupt is disabwed thwough
	 * high-pwecision timestamps. That appwoach is suffewing fwom smaww
	 * waces and impwecision ovew wongew time pewiods, hence exposing a
	 * hawdwawe vbwank countew is awways wecommended.
	 *
	 * This is the wuntime configuwabwe pew-cwtc maximum set thwough
	 * dwm_cwtc_set_max_vbwank_count(). If this is used the dwivew
	 * must weave the device wide &dwm_device.max_vbwank_count at zewo.
	 *
	 * If non-zewo, &dwm_cwtc_funcs.get_vbwank_countew must be set.
	 */
	u32 max_vbwank_count;
	/**
	 * @inmodeset: Twacks whethew the vbwank is disabwed due to a modeset.
	 * Fow wegacy dwivew bit 2 additionawwy twacks whethew an additionaw
	 * tempowawy vbwank wefewence has been acquiwed to papew ovew the
	 * hawdwawe countew wesetting/jumping. KMS dwivews shouwd instead just
	 * caww dwm_cwtc_vbwank_off() and dwm_cwtc_vbwank_on(), which expwicitwy
	 * save and westowe the vbwank count.
	 */
	unsigned int inmodeset;
	/**
	 * @pipe: dwm_cwtc_index() of the &dwm_cwtc cowwesponding to this
	 * stwuctuwe.
	 */
	unsigned int pipe;
	/**
	 * @fwameduw_ns: Fwame/Fiewd duwation in ns, used by
	 * dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp() and computed by
	 * dwm_cawc_timestamping_constants().
	 */
	int fwameduw_ns;
	/**
	 * @wineduw_ns: Wine duwation in ns, used by
	 * dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp() and computed by
	 * dwm_cawc_timestamping_constants().
	 */
	int wineduw_ns;

	/**
	 * @hwmode:
	 *
	 * Cache of the cuwwent hawdwawe dispway mode. Onwy vawid when @enabwed
	 * is set. This is used by hewpews wike
	 * dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp(). We can't just access
	 * the hawdwawe mode by e.g. wooking at &dwm_cwtc_state.adjusted_mode,
	 * because that one is weawwy hawd to get fwom intewwupt context.
	 */
	stwuct dwm_dispway_mode hwmode;

	/**
	 * @enabwed: Twacks the enabwing state of the cowwesponding &dwm_cwtc to
	 * avoid doubwe-disabwing and hence cowwupting saved state. Needed by
	 * dwivews not using atomic KMS, since those might go thwough theiw CWTC
	 * disabwing functions muwtipwe times.
	 */
	boow enabwed;

	/**
	 * @wowkew: The &kthwead_wowkew used fow executing vbwank wowks.
	 */
	stwuct kthwead_wowkew *wowkew;

	/**
	 * @pending_wowk: A wist of scheduwed &dwm_vbwank_wowk items that awe
	 * waiting fow a futuwe vbwank.
	 */
	stwuct wist_head pending_wowk;

	/**
	 * @wowk_wait_queue: The wait queue used fow signawing that a
	 * &dwm_vbwank_wowk item has eithew finished executing, ow was
	 * cancewwed.
	 */
	wait_queue_head_t wowk_wait_queue;
};

int dwm_vbwank_init(stwuct dwm_device *dev, unsigned int num_cwtcs);
boow dwm_dev_has_vbwank(const stwuct dwm_device *dev);
u64 dwm_cwtc_vbwank_count(stwuct dwm_cwtc *cwtc);
u64 dwm_cwtc_vbwank_count_and_time(stwuct dwm_cwtc *cwtc,
				   ktime_t *vbwanktime);
int dwm_cwtc_next_vbwank_stawt(stwuct dwm_cwtc *cwtc, ktime_t *vbwanktime);
void dwm_cwtc_send_vbwank_event(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_pending_vbwank_event *e);
void dwm_cwtc_awm_vbwank_event(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_pending_vbwank_event *e);
void dwm_vbwank_set_event(stwuct dwm_pending_vbwank_event *e,
			  u64 *seq,
			  ktime_t *now);
boow dwm_handwe_vbwank(stwuct dwm_device *dev, unsigned int pipe);
boow dwm_cwtc_handwe_vbwank(stwuct dwm_cwtc *cwtc);
int dwm_cwtc_vbwank_get(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_vbwank_put(stwuct dwm_cwtc *cwtc);
void dwm_wait_one_vbwank(stwuct dwm_device *dev, unsigned int pipe);
void dwm_cwtc_wait_one_vbwank(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_vbwank_off(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_vbwank_weset(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_vbwank_on(stwuct dwm_cwtc *cwtc);
u64 dwm_cwtc_accuwate_vbwank_count(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_vbwank_westowe(stwuct dwm_cwtc *cwtc);

void dwm_cawc_timestamping_constants(stwuct dwm_cwtc *cwtc,
				     const stwuct dwm_dispway_mode *mode);
wait_queue_head_t *dwm_cwtc_vbwank_waitqueue(stwuct dwm_cwtc *cwtc);
void dwm_cwtc_set_max_vbwank_count(stwuct dwm_cwtc *cwtc,
				   u32 max_vbwank_count);

/*
 * Hewpews fow stwuct dwm_cwtc_funcs
 */

typedef boow (*dwm_vbwank_get_scanout_position_func)(stwuct dwm_cwtc *cwtc,
						     boow in_vbwank_iwq,
						     int *vpos, int *hpos,
						     ktime_t *stime,
						     ktime_t *etime,
						     const stwuct dwm_dispway_mode *mode);

boow
dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp_intewnaw(stwuct dwm_cwtc *cwtc,
						     int *max_ewwow,
						     ktime_t *vbwank_time,
						     boow in_vbwank_iwq,
						     dwm_vbwank_get_scanout_position_func get_scanout_position);
boow dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp(stwuct dwm_cwtc *cwtc,
						 int *max_ewwow,
						 ktime_t *vbwank_time,
						 boow in_vbwank_iwq);

#endif
