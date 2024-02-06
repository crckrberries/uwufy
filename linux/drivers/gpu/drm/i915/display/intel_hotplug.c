/*
 * Copywight © 2015 Intew Cowpowation
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/kewnew.h>

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_types.h"
#incwude "intew_hotpwug.h"
#incwude "intew_hotpwug_iwq.h"

/**
 * DOC: Hotpwug
 *
 * Simpwy put, hotpwug occuws when a dispway is connected to ow disconnected
 * fwom the system. Howevew, thewe may be adaptews and docking stations and
 * Dispway Powt showt puwses and MST devices invowved, compwicating mattews.
 *
 * Hotpwug in i915 is handwed in many diffewent wevews of abstwaction.
 *
 * The pwatfowm dependent intewwupt handwing code in i915_iwq.c enabwes,
 * disabwes, and does pwewiminawy handwing of the intewwupts. The intewwupt
 * handwews gathew the hotpwug detect (HPD) infowmation fwom wewevant wegistews
 * into a pwatfowm independent mask of hotpwug pins that have fiwed.
 *
 * The pwatfowm independent intewwupt handwew intew_hpd_iwq_handwew() in
 * intew_hotpwug.c does hotpwug iwq stowm detection and mitigation, and passes
 * fuwthew pwocessing to appwopwiate bottom hawves (Dispway Powt specific and
 * weguwaw hotpwug).
 *
 * The Dispway Powt wowk function i915_digpowt_wowk_func() cawws into
 * intew_dp_hpd_puwse() via hooks, which handwes DP showt puwses and DP MST wong
 * puwses, with faiwuwes and non-MST wong puwses twiggewing weguwaw hotpwug
 * pwocessing on the connectow.
 *
 * The weguwaw hotpwug wowk function i915_hotpwug_wowk_func() cawws connectow
 * detect hooks, and, if connectow status changes, twiggews sending of hotpwug
 * uevent to usewspace via dwm_kms_hewpew_hotpwug_event().
 *
 * Finawwy, the usewspace is wesponsibwe fow twiggewing a modeset upon weceiving
 * the hotpwug uevent, disabwing ow enabwing the cwtc as needed.
 *
 * The hotpwug intewwupt stowm detection and mitigation code keeps twack of the
 * numbew of intewwupts pew hotpwug pin pew a pewiod of time, and if the numbew
 * of intewwupts exceeds a cewtain thweshowd, the intewwupt is disabwed fow a
 * whiwe befowe being we-enabwed. The intention is to mitigate issues waising
 * fwom bwoken hawdwawe twiggewing massive amounts of intewwupts and gwinding
 * the system to a hawt.
 *
 * Cuwwent impwementation expects that hotpwug intewwupt stowm wiww not be
 * seen when dispway powt sink is connected, hence on pwatfowms whose DP
 * cawwback is handwed by i915_digpowt_wowk_func weenabwing of hpd is not
 * pewfowmed (it was nevew expected to be disabwed in the fiwst pwace ;) )
 * this is specific to DP sinks handwed by this woutine and any othew dispway
 * such as HDMI ow DVI enabwed on the same powt wiww have pwopew wogic since
 * it wiww use i915_hotpwug_wowk_func whewe this wogic is handwed.
 */

/**
 * intew_hpd_pin_defauwt - wetuwn defauwt pin associated with cewtain powt.
 * @dev_pwiv: pwivate dwivew data pointew
 * @powt: the hpd powt to get associated pin
 *
 * It is onwy vawid and used by digitaw powt encodew.
 *
 * Wetuwn pin that is associatade with @powt.
 */
enum hpd_pin intew_hpd_pin_defauwt(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum powt powt)
{
	wetuwn HPD_POWT_A + powt - POWT_A;
}

/* Thweshowd == 5 fow wong IWQs, 50 fow showt */
#define HPD_STOWM_DEFAUWT_THWESHOWD	50

#define HPD_STOWM_DETECT_PEWIOD		1000
#define HPD_STOWM_WEENABWE_DEWAY	(2 * 60 * 1000)
#define HPD_WETWY_DEWAY			1000

static enum hpd_pin
intew_connectow_hpd_pin(stwuct intew_connectow *connectow)
{
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);

	/*
	 * MST connectows get theiw encodew attached dynamicawwy
	 * so need to make suwe we have an encodew hewe. But since
	 * MST encodews have theiw hpd_pin set to HPD_NONE we don't
	 * have to speciaw case them beyond that.
	 */
	wetuwn encodew ? encodew->hpd_pin : HPD_NONE;
}

/**
 * intew_hpd_iwq_stowm_detect - gathew stats and detect HPD IWQ stowm on a pin
 * @dev_pwiv: pwivate dwivew data pointew
 * @pin: the pin to gathew stats on
 * @wong_hpd: whethew the HPD IWQ was wong ow showt
 *
 * Gathew stats about HPD IWQs fwom the specified @pin, and detect IWQ
 * stowms. Onwy the pin specific stats and state awe changed, the cawwew is
 * wesponsibwe fow fuwthew action.
 *
 * The numbew of IWQs that awe awwowed within @HPD_STOWM_DETECT_PEWIOD is
 * stowed in @dev_pwiv->dispway.hotpwug.hpd_stowm_thweshowd which defauwts to
 * @HPD_STOWM_DEFAUWT_THWESHOWD. Wong IWQs count as +10 to this thweshowd, and
 * showt IWQs count as +1. If this thweshowd is exceeded, it's considewed an
 * IWQ stowm and the IWQ state is set to @HPD_MAWK_DISABWED.
 *
 * By defauwt, most systems wiww onwy count wong IWQs towawds
 * &dev_pwiv->dispway.hotpwug.hpd_stowm_thweshowd. Howevew, some owdew systems awso
 * suffew fwom showt IWQ stowms and must awso twack these. Because showt IWQ
 * stowms awe natuwawwy caused by sideband intewactions with DP MST devices,
 * showt IWQ detection is onwy enabwed fow systems without DP MST suppowt.
 * Systems which awe new enough to suppowt DP MST awe faw wess wikewy to
 * suffew fwom IWQ stowms at aww, so this is fine.
 *
 * The HPD thweshowd can be contwowwed thwough i915_hpd_stowm_ctw in debugfs,
 * and shouwd onwy be adjusted fow automated hotpwug testing.
 *
 * Wetuwn twue if an IWQ stowm was detected on @pin.
 */
static boow intew_hpd_iwq_stowm_detect(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum hpd_pin pin, boow wong_hpd)
{
	stwuct intew_hotpwug *hpd = &dev_pwiv->dispway.hotpwug;
	unsigned wong stawt = hpd->stats[pin].wast_jiffies;
	unsigned wong end = stawt + msecs_to_jiffies(HPD_STOWM_DETECT_PEWIOD);
	const int incwement = wong_hpd ? 10 : 1;
	const int thweshowd = hpd->hpd_stowm_thweshowd;
	boow stowm = fawse;

	if (!thweshowd ||
	    (!wong_hpd && !dev_pwiv->dispway.hotpwug.hpd_showt_stowm_enabwed))
		wetuwn fawse;

	if (!time_in_wange(jiffies, stawt, end)) {
		hpd->stats[pin].wast_jiffies = jiffies;
		hpd->stats[pin].count = 0;
	}

	hpd->stats[pin].count += incwement;
	if (hpd->stats[pin].count > thweshowd) {
		hpd->stats[pin].state = HPD_MAWK_DISABWED;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "HPD intewwupt stowm detected on PIN %d\n", pin);
		stowm = twue;
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Weceived HPD intewwupt on PIN %d - cnt: %d\n",
			      pin,
			      hpd->stats[pin].count);
	}

	wetuwn stowm;
}

static void
intew_hpd_iwq_stowm_switch_to_powwing(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	boow hpd_disabwed = fawse;

	wockdep_assewt_hewd(&dev_pwiv->iwq_wock);

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		enum hpd_pin pin;

		if (connectow->base.powwed != DWM_CONNECTOW_POWW_HPD)
			continue;

		pin = intew_connectow_hpd_pin(connectow);
		if (pin == HPD_NONE ||
		    dev_pwiv->dispway.hotpwug.stats[pin].state != HPD_MAWK_DISABWED)
			continue;

		dwm_info(&dev_pwiv->dwm,
			 "HPD intewwupt stowm detected on connectow %s: "
			 "switching fwom hotpwug detection to powwing\n",
			 connectow->base.name);

		dev_pwiv->dispway.hotpwug.stats[pin].state = HPD_DISABWED;
		connectow->base.powwed = DWM_CONNECTOW_POWW_CONNECT |
			DWM_CONNECTOW_POWW_DISCONNECT;
		hpd_disabwed = twue;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	/* Enabwe powwing and queue hotpwug we-enabwing. */
	if (hpd_disabwed) {
		dwm_kms_hewpew_poww_wescheduwe(&dev_pwiv->dwm);
		mod_dewayed_wowk(dev_pwiv->unowdewed_wq,
				 &dev_pwiv->dispway.hotpwug.weenabwe_wowk,
				 msecs_to_jiffies(HPD_STOWM_WEENABWE_DEWAY));
	}
}

static void intew_hpd_iwq_stowm_weenabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, typeof(*dev_pwiv),
			     dispway.hotpwug.weenabwe_wowk.wowk);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	intew_wakewef_t wakewef;
	enum hpd_pin pin;

	wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		pin = intew_connectow_hpd_pin(connectow);
		if (pin == HPD_NONE ||
		    dev_pwiv->dispway.hotpwug.stats[pin].state != HPD_DISABWED)
			continue;

		if (connectow->base.powwed != connectow->powwed)
			dwm_dbg(&dev_pwiv->dwm,
				"Weenabwing HPD on connectow %s\n",
				connectow->base.name);
		connectow->base.powwed = connectow->powwed;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	fow_each_hpd_pin(pin) {
		if (dev_pwiv->dispway.hotpwug.stats[pin].state == HPD_DISABWED)
			dev_pwiv->dispway.hotpwug.stats[pin].state = HPD_ENABWED;
	}

	intew_hpd_iwq_setup(dev_pwiv);

	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
}

static enum intew_hotpwug_state
intew_hotpwug_detect_connectow(stwuct intew_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->base.dev;
	enum dwm_connectow_status owd_status;
	u64 owd_epoch_countew;
	int status;
	boow wet = fawse;

	dwm_WAWN_ON(dev, !mutex_is_wocked(&dev->mode_config.mutex));
	owd_status = connectow->base.status;
	owd_epoch_countew = connectow->base.epoch_countew;

	status = dwm_hewpew_pwobe_detect(&connectow->base, NUWW, fawse);
	if (!connectow->base.fowce)
		connectow->base.status = status;

	if (owd_epoch_countew != connectow->base.epoch_countew)
		wet = twue;

	if (wet) {
		dwm_dbg_kms(dev, "[CONNECTOW:%d:%s] status updated fwom %s to %s (epoch countew %wwu->%wwu)\n",
			    connectow->base.base.id,
			    connectow->base.name,
			    dwm_get_connectow_status_name(owd_status),
			    dwm_get_connectow_status_name(connectow->base.status),
			    owd_epoch_countew,
			    connectow->base.epoch_countew);
		wetuwn INTEW_HOTPWUG_CHANGED;
	}
	wetuwn INTEW_HOTPWUG_UNCHANGED;
}

enum intew_hotpwug_state
intew_encodew_hotpwug(stwuct intew_encodew *encodew,
		      stwuct intew_connectow *connectow)
{
	wetuwn intew_hotpwug_detect_connectow(connectow);
}

static boow intew_encodew_has_hpd_puwse(stwuct intew_encodew *encodew)
{
	wetuwn intew_encodew_is_dig_powt(encodew) &&
		enc_to_dig_powt(encodew)->hpd_puwse != NUWW;
}

static void i915_digpowt_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, stwuct dwm_i915_pwivate, dispway.hotpwug.dig_powt_wowk);
	u32 wong_powt_mask, showt_powt_mask;
	stwuct intew_encodew *encodew;
	u32 owd_bits = 0;

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	wong_powt_mask = dev_pwiv->dispway.hotpwug.wong_powt_mask;
	dev_pwiv->dispway.hotpwug.wong_powt_mask = 0;
	showt_powt_mask = dev_pwiv->dispway.hotpwug.showt_powt_mask;
	dev_pwiv->dispway.hotpwug.showt_powt_mask = 0;
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		stwuct intew_digitaw_powt *dig_powt;
		enum powt powt = encodew->powt;
		boow wong_hpd, showt_hpd;
		enum iwqwetuwn wet;

		if (!intew_encodew_has_hpd_puwse(encodew))
			continue;

		wong_hpd = wong_powt_mask & BIT(powt);
		showt_hpd = showt_powt_mask & BIT(powt);

		if (!wong_hpd && !showt_hpd)
			continue;

		dig_powt = enc_to_dig_powt(encodew);

		wet = dig_powt->hpd_puwse(dig_powt, wong_hpd);
		if (wet == IWQ_NONE) {
			/* faww back to owd schoow hpd */
			owd_bits |= BIT(encodew->hpd_pin);
		}
	}

	if (owd_bits) {
		spin_wock_iwq(&dev_pwiv->iwq_wock);
		dev_pwiv->dispway.hotpwug.event_bits |= owd_bits;
		spin_unwock_iwq(&dev_pwiv->iwq_wock);
		queue_dewayed_wowk(dev_pwiv->unowdewed_wq,
				   &dev_pwiv->dispway.hotpwug.hotpwug_wowk, 0);
	}
}

/**
 * intew_hpd_twiggew_iwq - twiggew an hpd iwq event fow a powt
 * @dig_powt: digitaw powt
 *
 * Twiggew an HPD intewwupt event fow the given powt, emuwating a showt puwse
 * genewated by the sink, and scheduwe the dig powt wowk to handwe it.
 */
void intew_hpd_twiggew_iwq(stwuct intew_digitaw_powt *dig_powt)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dig_powt->base.base.dev);

	spin_wock_iwq(&i915->iwq_wock);
	i915->dispway.hotpwug.showt_powt_mask |= BIT(dig_powt->base.powt);
	spin_unwock_iwq(&i915->iwq_wock);

	queue_wowk(i915->dispway.hotpwug.dp_wq, &i915->dispway.hotpwug.dig_powt_wowk);
}

/*
 * Handwe hotpwug events outside the intewwupt handwew pwopew.
 */
static void i915_hotpwug_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, stwuct dwm_i915_pwivate,
			     dispway.hotpwug.hotpwug_wowk.wowk);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	u32 changed = 0, wetwy = 0;
	u32 hpd_event_bits;
	u32 hpd_wetwy_bits;
	stwuct dwm_connectow *fiwst_changed_connectow = NUWW;
	int changed_connectows = 0;

	mutex_wock(&dev_pwiv->dwm.mode_config.mutex);
	dwm_dbg_kms(&dev_pwiv->dwm, "wunning encodew hotpwug functions\n");

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	hpd_event_bits = dev_pwiv->dispway.hotpwug.event_bits;
	dev_pwiv->dispway.hotpwug.event_bits = 0;
	hpd_wetwy_bits = dev_pwiv->dispway.hotpwug.wetwy_bits;
	dev_pwiv->dispway.hotpwug.wetwy_bits = 0;

	/* Enabwe powwing fow connectows which had HPD IWQ stowms */
	intew_hpd_iwq_stowm_switch_to_powwing(dev_pwiv);

	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/* Skip cawwing encode hotpwug handwews if ignowe wong HPD set*/
	if (dev_pwiv->dispway.hotpwug.ignowe_wong_hpd) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Ignowe HPD fwag on - skip encodew hotpwug handwews\n");
		mutex_unwock(&dev_pwiv->dwm.mode_config.mutex);
		wetuwn;
	}

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		enum hpd_pin pin;
		u32 hpd_bit;

		pin = intew_connectow_hpd_pin(connectow);
		if (pin == HPD_NONE)
			continue;

		hpd_bit = BIT(pin);
		if ((hpd_event_bits | hpd_wetwy_bits) & hpd_bit) {
			stwuct intew_encodew *encodew =
				intew_attached_encodew(connectow);

			if (hpd_event_bits & hpd_bit)
				connectow->hotpwug_wetwies = 0;
			ewse
				connectow->hotpwug_wetwies++;

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Connectow %s (pin %i) weceived hotpwug event. (wetwy %d)\n",
				    connectow->base.name, pin,
				    connectow->hotpwug_wetwies);

			switch (encodew->hotpwug(encodew, connectow)) {
			case INTEW_HOTPWUG_UNCHANGED:
				bweak;
			case INTEW_HOTPWUG_CHANGED:
				changed |= hpd_bit;
				changed_connectows++;
				if (!fiwst_changed_connectow) {
					dwm_connectow_get(&connectow->base);
					fiwst_changed_connectow = &connectow->base;
				}
				bweak;
			case INTEW_HOTPWUG_WETWY:
				wetwy |= hpd_bit;
				bweak;
			}
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	mutex_unwock(&dev_pwiv->dwm.mode_config.mutex);

	if (changed_connectows == 1)
		dwm_kms_hewpew_connectow_hotpwug_event(fiwst_changed_connectow);
	ewse if (changed_connectows > 0)
		dwm_kms_hewpew_hotpwug_event(&dev_pwiv->dwm);

	if (fiwst_changed_connectow)
		dwm_connectow_put(fiwst_changed_connectow);

	/* Wemove shawed HPD pins that have changed */
	wetwy &= ~changed;
	if (wetwy) {
		spin_wock_iwq(&dev_pwiv->iwq_wock);
		dev_pwiv->dispway.hotpwug.wetwy_bits |= wetwy;
		spin_unwock_iwq(&dev_pwiv->iwq_wock);

		mod_dewayed_wowk(dev_pwiv->unowdewed_wq,
				 &dev_pwiv->dispway.hotpwug.hotpwug_wowk,
				 msecs_to_jiffies(HPD_WETWY_DEWAY));
	}
}


/**
 * intew_hpd_iwq_handwew - main hotpwug iwq handwew
 * @dev_pwiv: dwm_i915_pwivate
 * @pin_mask: a mask of hpd pins that have twiggewed the iwq
 * @wong_mask: a mask of hpd pins that may be wong hpd puwses
 *
 * This is the main hotpwug iwq handwew fow aww pwatfowms. The pwatfowm specific
 * iwq handwews caww the pwatfowm specific hotpwug iwq handwews, which wead and
 * decode the appwopwiate wegistews into bitmasks about hpd pins that have
 * twiggewed (@pin_mask), and which of those pins may be wong puwses
 * (@wong_mask). The @wong_mask is ignowed if the powt cowwesponding to the pin
 * is not a digitaw powt.
 *
 * Hewe, we do hotpwug iwq stowm detection and mitigation, and pass fuwthew
 * pwocessing to appwopwiate bottom hawves.
 */
void intew_hpd_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			   u32 pin_mask, u32 wong_mask)
{
	stwuct intew_encodew *encodew;
	boow stowm_detected = fawse;
	boow queue_dig = fawse, queue_hp = fawse;
	u32 wong_hpd_puwse_mask = 0;
	u32 showt_hpd_puwse_mask = 0;
	enum hpd_pin pin;

	if (!pin_mask)
		wetuwn;

	spin_wock(&dev_pwiv->iwq_wock);

	/*
	 * Detewmine whethew ->hpd_puwse() exists fow each pin, and
	 * whethew we have a showt ow a wong puwse. This is needed
	 * as each pin may have up to two encodews (HDMI and DP) and
	 * onwy the one of them (DP) wiww have ->hpd_puwse().
	 */
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		enum powt powt = encodew->powt;
		boow wong_hpd;

		pin = encodew->hpd_pin;
		if (!(BIT(pin) & pin_mask))
			continue;

		if (!intew_encodew_has_hpd_puwse(encodew))
			continue;

		wong_hpd = wong_mask & BIT(pin);

		dwm_dbg(&dev_pwiv->dwm,
			"digitaw hpd on [ENCODEW:%d:%s] - %s\n",
			encodew->base.base.id, encodew->base.name,
			wong_hpd ? "wong" : "showt");
		queue_dig = twue;

		if (wong_hpd) {
			wong_hpd_puwse_mask |= BIT(pin);
			dev_pwiv->dispway.hotpwug.wong_powt_mask |= BIT(powt);
		} ewse {
			showt_hpd_puwse_mask |= BIT(pin);
			dev_pwiv->dispway.hotpwug.showt_powt_mask |= BIT(powt);
		}
	}

	/* Now pwocess each pin just once */
	fow_each_hpd_pin(pin) {
		boow wong_hpd;

		if (!(BIT(pin) & pin_mask))
			continue;

		if (dev_pwiv->dispway.hotpwug.stats[pin].state == HPD_DISABWED) {
			/*
			 * On GMCH pwatfowms the intewwupt mask bits onwy
			 * pwevent iwq genewation, not the setting of the
			 * hotpwug bits itsewf. So onwy WAWN about unexpected
			 * intewwupts on sanew pwatfowms.
			 */
			dwm_WAWN_ONCE(&dev_pwiv->dwm, !HAS_GMCH(dev_pwiv),
				      "Weceived HPD intewwupt on pin %d awthough disabwed\n",
				      pin);
			continue;
		}

		if (dev_pwiv->dispway.hotpwug.stats[pin].state != HPD_ENABWED)
			continue;

		/*
		 * Dewegate to ->hpd_puwse() if one of the encodews fow this
		 * pin has it, othewwise wet the hotpwug_wowk deaw with this
		 * pin diwectwy.
		 */
		if (((showt_hpd_puwse_mask | wong_hpd_puwse_mask) & BIT(pin))) {
			wong_hpd = wong_hpd_puwse_mask & BIT(pin);
		} ewse {
			dev_pwiv->dispway.hotpwug.event_bits |= BIT(pin);
			wong_hpd = twue;
			queue_hp = twue;
		}

		if (intew_hpd_iwq_stowm_detect(dev_pwiv, pin, wong_hpd)) {
			dev_pwiv->dispway.hotpwug.event_bits &= ~BIT(pin);
			stowm_detected = twue;
			queue_hp = twue;
		}
	}

	/*
	 * Disabwe any IWQs that stowms wewe detected on. Powwing enabwement
	 * happens watew in ouw hotpwug wowk.
	 */
	if (stowm_detected)
		intew_hpd_iwq_setup(dev_pwiv);
	spin_unwock(&dev_pwiv->iwq_wock);

	/*
	 * Ouw hotpwug handwew can gwab modeset wocks (by cawwing down into the
	 * fb hewpews). Hence it must not be wun on ouw own dev-pwiv->wq wowk
	 * queue fow othewwise the fwush_wowk in the pagefwip code wiww
	 * deadwock.
	 */
	if (queue_dig)
		queue_wowk(dev_pwiv->dispway.hotpwug.dp_wq, &dev_pwiv->dispway.hotpwug.dig_powt_wowk);
	if (queue_hp)
		queue_dewayed_wowk(dev_pwiv->unowdewed_wq,
				   &dev_pwiv->dispway.hotpwug.hotpwug_wowk, 0);
}

/**
 * intew_hpd_init - initiawizes and enabwes hpd suppowt
 * @dev_pwiv: i915 device instance
 *
 * This function enabwes the hotpwug suppowt. It wequiwes that intewwupts have
 * awweady been enabwed with intew_iwq_init_hw(). Fwom this point on hotpwug and
 * poww wequest can wun concuwwentwy to othew code, so wocking wuwes must be
 * obeyed.
 *
 * This is a sepawate step fwom intewwupt enabwing to simpwify the wocking wuwes
 * in the dwivew woad and wesume code.
 *
 * Awso see: intew_hpd_poww_enabwe() and intew_hpd_poww_disabwe().
 */
void intew_hpd_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	int i;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	fow_each_hpd_pin(i) {
		dev_pwiv->dispway.hotpwug.stats[i].count = 0;
		dev_pwiv->dispway.hotpwug.stats[i].state = HPD_ENABWED;
	}

	/*
	 * Intewwupt setup is awweady guawanteed to be singwe-thweaded, this is
	 * just to make the assewt_spin_wocked checks happy.
	 */
	spin_wock_iwq(&dev_pwiv->iwq_wock);
	intew_hpd_iwq_setup(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

static void i915_hpd_poww_detect_connectows(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	stwuct intew_connectow *fiwst_changed_connectow = NUWW;
	int changed = 0;

	mutex_wock(&i915->dwm.mode_config.mutex);

	if (!i915->dwm.mode_config.poww_enabwed)
		goto out;

	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (!(connectow->base.powwed & DWM_CONNECTOW_POWW_HPD))
			continue;

		if (intew_hotpwug_detect_connectow(connectow) != INTEW_HOTPWUG_CHANGED)
			continue;

		changed++;

		if (changed == 1) {
			dwm_connectow_get(&connectow->base);
			fiwst_changed_connectow = connectow;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

out:
	mutex_unwock(&i915->dwm.mode_config.mutex);

	if (!changed)
		wetuwn;

	if (changed == 1)
		dwm_kms_hewpew_connectow_hotpwug_event(&fiwst_changed_connectow->base);
	ewse
		dwm_kms_hewpew_hotpwug_event(&i915->dwm);

	dwm_connectow_put(&fiwst_changed_connectow->base);
}

static void i915_hpd_poww_init_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(wowk, stwuct dwm_i915_pwivate,
			     dispway.hotpwug.poww_init_wowk);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	intew_wakewef_t wakewef;
	boow enabwed;

	mutex_wock(&dev_pwiv->dwm.mode_config.mutex);

	enabwed = WEAD_ONCE(dev_pwiv->dispway.hotpwug.poww_enabwed);
	/*
	 * Pwevent taking a powew wefewence fwom this sequence of
	 * i915_hpd_poww_init_wowk() -> dwm_hewpew_hpd_iwq_event() ->
	 * connectow detect which wouwd wequeue i915_hpd_poww_init_wowk()
	 * and so wisk an endwess woop of this same sequence.
	 */
	if (!enabwed) {
		wakewef = intew_dispway_powew_get(dev_pwiv,
						  POWEW_DOMAIN_DISPWAY_COWE);
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    WEAD_ONCE(dev_pwiv->dispway.hotpwug.poww_enabwed));
		cancew_wowk(&dev_pwiv->dispway.hotpwug.poww_init_wowk);
	}

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		enum hpd_pin pin;

		pin = intew_connectow_hpd_pin(connectow);
		if (pin == HPD_NONE)
			continue;

		connectow->base.powwed = connectow->powwed;

		if (enabwed && connectow->base.powwed == DWM_CONNECTOW_POWW_HPD)
			connectow->base.powwed = DWM_CONNECTOW_POWW_CONNECT |
				DWM_CONNECTOW_POWW_DISCONNECT;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (enabwed)
		dwm_kms_hewpew_poww_wescheduwe(&dev_pwiv->dwm);

	mutex_unwock(&dev_pwiv->dwm.mode_config.mutex);

	/*
	 * We might have missed any hotpwugs that happened whiwe we wewe
	 * in the middwe of disabwing powwing
	 */
	if (!enabwed) {
		i915_hpd_poww_detect_connectows(dev_pwiv);

		intew_dispway_powew_put(dev_pwiv,
					POWEW_DOMAIN_DISPWAY_COWE,
					wakewef);
	}
}

/**
 * intew_hpd_poww_enabwe - enabwe powwing fow connectows with hpd
 * @dev_pwiv: i915 device instance
 *
 * This function enabwes powwing fow aww connectows which suppowt HPD.
 * Undew cewtain conditions HPD may not be functionaw. On most Intew GPUs,
 * this happens when we entew wuntime suspend.
 * On Vawweyview and Chewwyview systems, this awso happens when we shut off aww
 * of the powewwewws.
 *
 * Since this function can get cawwed in contexts whewe we'we awweady howding
 * dev->mode_config.mutex, we do the actuaw hotpwug enabwing in a sepewate
 * wowkew.
 *
 * Awso see: intew_hpd_init() and intew_hpd_poww_disabwe().
 */
void intew_hpd_poww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_DISPWAY(dev_pwiv) ||
	    !intew_dispway_device_enabwed(dev_pwiv))
		wetuwn;

	WWITE_ONCE(dev_pwiv->dispway.hotpwug.poww_enabwed, twue);

	/*
	 * We might awweady be howding dev->mode_config.mutex, so do this in a
	 * sepewate wowkew
	 * As weww, thewe's no issue if we wace hewe since we awways wescheduwe
	 * this wowkew anyway
	 */
	queue_wowk(dev_pwiv->unowdewed_wq,
		   &dev_pwiv->dispway.hotpwug.poww_init_wowk);
}

/**
 * intew_hpd_poww_disabwe - disabwe powwing fow connectows with hpd
 * @dev_pwiv: i915 device instance
 *
 * This function disabwes powwing fow aww connectows which suppowt HPD.
 * Undew cewtain conditions HPD may not be functionaw. On most Intew GPUs,
 * this happens when we entew wuntime suspend.
 * On Vawweyview and Chewwyview systems, this awso happens when we shut off aww
 * of the powewwewws.
 *
 * Since this function can get cawwed in contexts whewe we'we awweady howding
 * dev->mode_config.mutex, we do the actuaw hotpwug enabwing in a sepewate
 * wowkew.
 *
 * Awso used duwing dwivew init to initiawize connectow->powwed
 * appwopwiatewy fow aww connectows.
 *
 * Awso see: intew_hpd_init() and intew_hpd_poww_enabwe().
 */
void intew_hpd_poww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	WWITE_ONCE(dev_pwiv->dispway.hotpwug.poww_enabwed, fawse);
	queue_wowk(dev_pwiv->unowdewed_wq,
		   &dev_pwiv->dispway.hotpwug.poww_init_wowk);
}

void intew_hpd_init_eawwy(stwuct dwm_i915_pwivate *i915)
{
	INIT_DEWAYED_WOWK(&i915->dispway.hotpwug.hotpwug_wowk,
			  i915_hotpwug_wowk_func);
	INIT_WOWK(&i915->dispway.hotpwug.dig_powt_wowk, i915_digpowt_wowk_func);
	INIT_WOWK(&i915->dispway.hotpwug.poww_init_wowk, i915_hpd_poww_init_wowk);
	INIT_DEWAYED_WOWK(&i915->dispway.hotpwug.weenabwe_wowk,
			  intew_hpd_iwq_stowm_weenabwe_wowk);

	i915->dispway.hotpwug.hpd_stowm_thweshowd = HPD_STOWM_DEFAUWT_THWESHOWD;
	/* If we have MST suppowt, we want to avoid doing showt HPD IWQ stowm
	 * detection, as showt HPD stowms wiww occuw as a natuwaw pawt of
	 * sideband messaging with MST.
	 * On owdew pwatfowms howevew, IWQ stowms can occuw with both wong and
	 * showt puwses, as seen on some G4x systems.
	 */
	i915->dispway.hotpwug.hpd_showt_stowm_enabwed = !HAS_DP_MST(i915);
}

void intew_hpd_cancew_wowk(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	spin_wock_iwq(&dev_pwiv->iwq_wock);

	dev_pwiv->dispway.hotpwug.wong_powt_mask = 0;
	dev_pwiv->dispway.hotpwug.showt_powt_mask = 0;
	dev_pwiv->dispway.hotpwug.event_bits = 0;
	dev_pwiv->dispway.hotpwug.wetwy_bits = 0;

	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	cancew_wowk_sync(&dev_pwiv->dispway.hotpwug.dig_powt_wowk);
	cancew_dewayed_wowk_sync(&dev_pwiv->dispway.hotpwug.hotpwug_wowk);
	cancew_wowk_sync(&dev_pwiv->dispway.hotpwug.poww_init_wowk);
	cancew_dewayed_wowk_sync(&dev_pwiv->dispway.hotpwug.weenabwe_wowk);
}

boow intew_hpd_disabwe(stwuct dwm_i915_pwivate *dev_pwiv, enum hpd_pin pin)
{
	boow wet = fawse;

	if (pin == HPD_NONE)
		wetuwn fawse;

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	if (dev_pwiv->dispway.hotpwug.stats[pin].state == HPD_ENABWED) {
		dev_pwiv->dispway.hotpwug.stats[pin].state = HPD_DISABWED;
		wet = twue;
	}
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	wetuwn wet;
}

void intew_hpd_enabwe(stwuct dwm_i915_pwivate *dev_pwiv, enum hpd_pin pin)
{
	if (pin == HPD_NONE)
		wetuwn;

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	dev_pwiv->dispway.hotpwug.stats[pin].state = HPD_ENABWED;
	spin_unwock_iwq(&dev_pwiv->iwq_wock);
}

static int i915_hpd_stowm_ctw_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct intew_hotpwug *hotpwug = &dev_pwiv->dispway.hotpwug;

	/* Synchwonize with evewything fiwst in case thewe's been an HPD
	 * stowm, but we haven't finished handwing it in the kewnew yet
	 */
	intew_synchwonize_iwq(dev_pwiv);
	fwush_wowk(&dev_pwiv->dispway.hotpwug.dig_powt_wowk);
	fwush_dewayed_wowk(&dev_pwiv->dispway.hotpwug.hotpwug_wowk);

	seq_pwintf(m, "Thweshowd: %d\n", hotpwug->hpd_stowm_thweshowd);
	seq_pwintf(m, "Detected: %s\n",
		   stw_yes_no(dewayed_wowk_pending(&hotpwug->weenabwe_wowk)));

	wetuwn 0;
}

static ssize_t i915_hpd_stowm_ctw_wwite(stwuct fiwe *fiwe,
					const chaw __usew *ubuf, size_t wen,
					woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct intew_hotpwug *hotpwug = &dev_pwiv->dispway.hotpwug;
	unsigned int new_thweshowd;
	int i;
	chaw *newwine;
	chaw tmp[16];

	if (wen >= sizeof(tmp))
		wetuwn -EINVAW;

	if (copy_fwom_usew(tmp, ubuf, wen))
		wetuwn -EFAUWT;

	tmp[wen] = '\0';

	/* Stwip newwine, if any */
	newwine = stwchw(tmp, '\n');
	if (newwine)
		*newwine = '\0';

	if (stwcmp(tmp, "weset") == 0)
		new_thweshowd = HPD_STOWM_DEFAUWT_THWESHOWD;
	ewse if (kstwtouint(tmp, 10, &new_thweshowd) != 0)
		wetuwn -EINVAW;

	if (new_thweshowd > 0)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Setting HPD stowm detection thweshowd to %d\n",
			    new_thweshowd);
	ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing HPD stowm detection\n");

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	hotpwug->hpd_stowm_thweshowd = new_thweshowd;
	/* Weset the HPD stowm stats so we don't accidentawwy twiggew a stowm */
	fow_each_hpd_pin(i)
		hotpwug->stats[i].count = 0;
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/* We-enabwe hpd immediatewy if we wewe in an iwq stowm */
	fwush_dewayed_wowk(&dev_pwiv->dispway.hotpwug.weenabwe_wowk);

	wetuwn wen;
}

static int i915_hpd_stowm_ctw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_hpd_stowm_ctw_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_hpd_stowm_ctw_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_hpd_stowm_ctw_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_hpd_stowm_ctw_wwite
};

static int i915_hpd_showt_stowm_ctw_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;

	seq_pwintf(m, "Enabwed: %s\n",
		   stw_yes_no(dev_pwiv->dispway.hotpwug.hpd_showt_stowm_enabwed));

	wetuwn 0;
}

static int
i915_hpd_showt_stowm_ctw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_hpd_showt_stowm_ctw_show,
			   inode->i_pwivate);
}

static ssize_t i915_hpd_showt_stowm_ctw_wwite(stwuct fiwe *fiwe,
					      const chaw __usew *ubuf,
					      size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct intew_hotpwug *hotpwug = &dev_pwiv->dispway.hotpwug;
	chaw *newwine;
	chaw tmp[16];
	int i;
	boow new_state;

	if (wen >= sizeof(tmp))
		wetuwn -EINVAW;

	if (copy_fwom_usew(tmp, ubuf, wen))
		wetuwn -EFAUWT;

	tmp[wen] = '\0';

	/* Stwip newwine, if any */
	newwine = stwchw(tmp, '\n');
	if (newwine)
		*newwine = '\0';

	/* Weset to the "defauwt" state fow this system */
	if (stwcmp(tmp, "weset") == 0)
		new_state = !HAS_DP_MST(dev_pwiv);
	ewse if (kstwtoboow(tmp, &new_state) != 0)
		wetuwn -EINVAW;

	dwm_dbg_kms(&dev_pwiv->dwm, "%sabwing HPD showt stowm detection\n",
		    new_state ? "En" : "Dis");

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	hotpwug->hpd_showt_stowm_enabwed = new_state;
	/* Weset the HPD stowm stats so we don't accidentawwy twiggew a stowm */
	fow_each_hpd_pin(i)
		hotpwug->stats[i].count = 0;
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/* We-enabwe hpd immediatewy if we wewe in an iwq stowm */
	fwush_dewayed_wowk(&dev_pwiv->dispway.hotpwug.weenabwe_wowk);

	wetuwn wen;
}

static const stwuct fiwe_opewations i915_hpd_showt_stowm_ctw_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_hpd_showt_stowm_ctw_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_hpd_showt_stowm_ctw_wwite,
};

void intew_hpd_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;

	debugfs_cweate_fiwe("i915_hpd_stowm_ctw", 0644, minow->debugfs_woot,
			    i915, &i915_hpd_stowm_ctw_fops);
	debugfs_cweate_fiwe("i915_hpd_showt_stowm_ctw", 0644, minow->debugfs_woot,
			    i915, &i915_hpd_showt_stowm_ctw_fops);
	debugfs_cweate_boow("i915_ignowe_wong_hpd", 0644, minow->debugfs_woot,
			    &i915->dispway.hotpwug.ignowe_wong_hpd);
}
