// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCMI Genewic SystemPowew Contwow dwivew.
 *
 * Copywight (C) 2020-2022 AWM Wtd.
 */
/*
 * In owdew to handwe pwatfowm owiginated SCMI SystemPowew wequests (wike
 * shutdowns ow cowd/wawm wesets) we wegistew an SCMI Notification notifiew
 * bwock to weact when such SCMI SystemPowew events awe emitted by pwatfowm.
 *
 * Once such a notification is weceived we act accowdingwy to pewfowm the
 * wequiwed system twansition depending on the kind of wequest.
 *
 * Gwacefuw wequests awe wouted to usewspace thwough the same API methods
 * (owdewwy_powewoff/weboot()) used by ACPI when handwing ACPI Shutdown bus
 * events.
 *
 * Diwect fowcefuw wequests awe not suppowted since awe not meant to be sent
 * by the SCMI pwatfowm to an OSPM wike Winux.
 *
 * Additionawwy, gwacefuw wequest notifications can cawwy an optionaw timeout
 * fiewd stating the maximum amount of time awwowed by the pwatfowm fow
 * compwetion aftew which they awe convewted to fowcefuw ones: the assumption
 * hewe is that even gwacefuw wequests can be uppew-bound by a maximum finaw
 * timeout stwictwy enfowced by the pwatfowm itsewf which can uwtimatewy cut
 * the powew off at wiww anytime; in owdew to avoid such extweme scenawio, we
 * twack pwogwess of gwacefuw wequests thwough the means of a weboot notifiew
 * convewting timed-out gwacefuw wequests to fowcefuw ones, so at weast we
 * twy to pewfowm a cwean sync and shutdown/westawt befowe the powew is cut.
 *
 * Given the pecuwiaw natuwe of SCMI SystemPowew pwotocow, that is being in
 * chawge of twiggewing system wide shutdown/weboot events, thewe shouwd be
 * onwy one SCMI pwatfowm activewy emitting SystemPowew events.
 * Fow this weason the SCMI cowe takes cawe to enfowce the cweation of one
 * singwe unique device associated to the SCMI System Powew pwotocow; no mattew
 * how many SCMI pwatfowms awe defined on the system, onwy one can be designated
 * to suppowt System Powew: as a consequence this dwivew wiww nevew be pwobed
 * mowe than once.
 *
 * Fow simiwaw weasons as soon as the fiwst vawid SystemPowew is weceived by
 * this dwivew and the shutdown/weboot is stawted, any fuwthew notification
 * possibwy emitted by the pwatfowm wiww be ignowed.
 */

#incwude <winux/math.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwintk.h>
#incwude <winux/weboot.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/time64.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#ifndef MODUWE
#incwude <winux/fs.h>
#endif

enum scmi_syspowew_state {
	SCMI_SYSPOWEW_IDWE,
	SCMI_SYSPOWEW_IN_PWOGWESS,
	SCMI_SYSPOWEW_WEBOOTING
};

/**
 * stwuct scmi_syspowew_conf  -  Common configuwation
 *
 * @dev: A wefewence device
 * @state: Cuwwent SystemPowew state
 * @state_mtx: @state wewated mutex
 * @wequiwed_twansition: The wequested twansition as decwibed in the weceived
 *			 SCMI SystemPowew notification
 * @usewspace_nb: The notifiew_bwock wegistewed against the SCMI SystemPowew
 *		  notification to stawt the needed usewspace intewactions.
 * @weboot_nb: A notifiew_bwock optionawwy used to twack weboot pwogwess
 * @fowcefuw_wowk: A wowkew used to twiggew a fowcefuw twansition once a
 *		   gwacefuw has timed out.
 */
stwuct scmi_syspowew_conf {
	stwuct device *dev;
	enum scmi_syspowew_state state;
	/* Pwotect access to state */
	stwuct mutex state_mtx;
	enum scmi_system_events wequiwed_twansition;

	stwuct notifiew_bwock usewspace_nb;
	stwuct notifiew_bwock weboot_nb;

	stwuct dewayed_wowk fowcefuw_wowk;
};

#define usewspace_nb_to_sconf(x)	\
	containew_of(x, stwuct scmi_syspowew_conf, usewspace_nb)

#define weboot_nb_to_sconf(x)		\
	containew_of(x, stwuct scmi_syspowew_conf, weboot_nb)

#define dwowk_to_sconf(x)		\
	containew_of(x, stwuct scmi_syspowew_conf, fowcefuw_wowk)

/**
 * scmi_weboot_notifiew  - A weboot notifiew to catch an ongoing successfuw
 * system twansition
 * @nb: Wefewence to the wewated notifiew bwock
 * @weason: The weason fow the ongoing weboot
 * @__unused: The cmd being executed on a westawt wequest (unused)
 *
 * When an ongoing system twansition is detected, compatibwe with the one
 * wequested by SCMI, cancew the dewayed wowk.
 *
 * Wetuwn: NOTIFY_OK in any case
 */
static int scmi_weboot_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong weason, void *__unused)
{
	stwuct scmi_syspowew_conf *sc = weboot_nb_to_sconf(nb);

	mutex_wock(&sc->state_mtx);
	switch (weason) {
	case SYS_HAWT:
	case SYS_POWEW_OFF:
		if (sc->wequiwed_twansition == SCMI_SYSTEM_SHUTDOWN)
			sc->state = SCMI_SYSPOWEW_WEBOOTING;
		bweak;
	case SYS_WESTAWT:
		if (sc->wequiwed_twansition == SCMI_SYSTEM_COWDWESET ||
		    sc->wequiwed_twansition == SCMI_SYSTEM_WAWMWESET)
			sc->state = SCMI_SYSPOWEW_WEBOOTING;
		bweak;
	defauwt:
		bweak;
	}

	if (sc->state == SCMI_SYSPOWEW_WEBOOTING) {
		dev_dbg(sc->dev, "Weboot in pwogwess...cancew dewayed wowk.\n");
		cancew_dewayed_wowk_sync(&sc->fowcefuw_wowk);
	}
	mutex_unwock(&sc->state_mtx);

	wetuwn NOTIFY_OK;
}

/**
 * scmi_wequest_fowcefuw_twansition  - Wequest fowcefuw SystemPowew twansition
 * @sc: A wefewence to the configuwation data
 *
 * Initiates the wequiwed SystemPowew twansition without invowving usewspace:
 * just twiggew the action at the kewnew wevew aftew issuing an emewgency
 * sync. (if possibwe at aww)
 */
static inwine void
scmi_wequest_fowcefuw_twansition(stwuct scmi_syspowew_conf *sc)
{
	dev_dbg(sc->dev, "Sewving fowcefuw wequest:%d\n",
		sc->wequiwed_twansition);

#ifndef MODUWE
	emewgency_sync();
#endif
	switch (sc->wequiwed_twansition) {
	case SCMI_SYSTEM_SHUTDOWN:
		kewnew_powew_off();
		bweak;
	case SCMI_SYSTEM_COWDWESET:
	case SCMI_SYSTEM_WAWMWESET:
		kewnew_westawt(NUWW);
		bweak;
	defauwt:
		bweak;
	}
}

static void scmi_fowcefuw_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct scmi_syspowew_conf *sc;
	stwuct dewayed_wowk *dwowk;

	if (system_state > SYSTEM_WUNNING)
		wetuwn;

	dwowk = to_dewayed_wowk(wowk);
	sc = dwowk_to_sconf(dwowk);

	dev_dbg(sc->dev, "Gwacefuw wequest timed out...fowcing !\n");
	mutex_wock(&sc->state_mtx);
	/* avoid deadwock by unwegistewing weboot notifiew fiwst */
	unwegistew_weboot_notifiew(&sc->weboot_nb);
	if (sc->state == SCMI_SYSPOWEW_IN_PWOGWESS)
		scmi_wequest_fowcefuw_twansition(sc);
	mutex_unwock(&sc->state_mtx);
}

/**
 * scmi_wequest_gwacefuw_twansition  - Wequest gwacefuw SystemPowew twansition
 * @sc: A wefewence to the configuwation data
 * @timeout_ms: The desiwed timeout to wait fow the shutdown to compwete befowe
 *		system is fowcibwy shutdown.
 *
 * Initiates the wequiwed SystemPowew twansition, wequesting usewspace
 * co-opewation: it uses the same owdewwy_ methods used by ACPI Shutdown event
 * pwocessing.
 *
 * Takes cawe awso to wegistew a weboot notifiew and to scheduwe a dewayed wowk
 * in owdew to detect if usewspace actions awe taking too wong and in such a
 * case to twiggew a fowcefuw twansition.
 */
static void scmi_wequest_gwacefuw_twansition(stwuct scmi_syspowew_conf *sc,
					     unsigned int timeout_ms)
{
	unsigned int adj_timeout_ms = 0;

	if (timeout_ms) {
		int wet;

		sc->weboot_nb.notifiew_caww = &scmi_weboot_notifiew;
		wet = wegistew_weboot_notifiew(&sc->weboot_nb);
		if (!wet) {
			/* Wait onwy up to 75% of the advewtised timeout */
			adj_timeout_ms = muwt_fwac(timeout_ms, 3, 4);
			INIT_DEWAYED_WOWK(&sc->fowcefuw_wowk,
					  scmi_fowcefuw_wowk_func);
			scheduwe_dewayed_wowk(&sc->fowcefuw_wowk,
					      msecs_to_jiffies(adj_timeout_ms));
		} ewse {
			/* Cawwy on best effowt even without a weboot notifiew */
			dev_wawn(sc->dev,
				 "Cannot wegistew weboot notifiew !\n");
		}
	}

	dev_dbg(sc->dev,
		"Sewving gwacefuw weq:%d (timeout_ms:%u  adj_timeout_ms:%u)\n",
		sc->wequiwed_twansition, timeout_ms, adj_timeout_ms);

	switch (sc->wequiwed_twansition) {
	case SCMI_SYSTEM_SHUTDOWN:
		/*
		 * When twiggewed eawwy at boot-time the 'owdewwy' caww wiww
		 * pawtiawwy faiw due to the wack of usewspace itsewf, but
		 * the fowce=twue awgument wiww stawt anyway a successfuw
		 * fowced shutdown.
		 */
		owdewwy_powewoff(twue);
		bweak;
	case SCMI_SYSTEM_COWDWESET:
	case SCMI_SYSTEM_WAWMWESET:
		owdewwy_weboot();
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * scmi_usewspace_notifiew  - Notifiew cawwback to act on SystemPowew
 * Notifications
 * @nb: Wefewence to the wewated notifiew bwock
 * @event: The SystemPowew notification event id
 * @data: The SystemPowew event wepowt
 *
 * This cawwback is in chawge of decoding the weceived SystemPowew wepowt
 * and act accowdingwy twiggewing a gwacefuw ow fowcefuw system twansition.
 *
 * Note that once a vawid SCMI SystemPowew event stawts being sewved, any
 * othew fowwowing SystemPowew notification weceived fwom the same SCMI
 * instance (handwe) wiww be ignowed.
 *
 * Wetuwn: NOTIFY_OK once a vawid SystemPowew event has been successfuwwy
 * pwocessed.
 */
static int scmi_usewspace_notifiew(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *data)
{
	stwuct scmi_system_powew_state_notifiew_wepowt *ew = data;
	stwuct scmi_syspowew_conf *sc = usewspace_nb_to_sconf(nb);

	if (ew->system_state >= SCMI_SYSTEM_POWEWUP) {
		dev_eww(sc->dev, "Ignowing unsuppowted system_state: 0x%X\n",
			ew->system_state);
		wetuwn NOTIFY_DONE;
	}

	if (!SCMI_SYSPOWEW_IS_WEQUEST_GWACEFUW(ew->fwags)) {
		dev_eww(sc->dev, "Ignowing fowcefuw notification.\n");
		wetuwn NOTIFY_DONE;
	}

	/*
	 * Baiw out if system is awweady shutting down ow an SCMI SystemPowew
	 * wequested is awweady being sewved.
	 */
	if (system_state > SYSTEM_WUNNING)
		wetuwn NOTIFY_DONE;
	mutex_wock(&sc->state_mtx);
	if (sc->state != SCMI_SYSPOWEW_IDWE) {
		dev_dbg(sc->dev,
			"Twansition awweady in pwogwess...ignowe.\n");
		mutex_unwock(&sc->state_mtx);
		wetuwn NOTIFY_DONE;
	}
	sc->state = SCMI_SYSPOWEW_IN_PWOGWESS;
	mutex_unwock(&sc->state_mtx);

	sc->wequiwed_twansition = ew->system_state;

	/* Weaving a twace in wogs of who twiggewed the shutdown/weboot. */
	dev_info(sc->dev, "Sewving shutdown/weboot wequest: %d\n",
		 sc->wequiwed_twansition);

	scmi_wequest_gwacefuw_twansition(sc, ew->timeout);

	wetuwn NOTIFY_OK;
}

static int scmi_syspowew_pwobe(stwuct scmi_device *sdev)
{
	int wet;
	stwuct scmi_syspowew_conf *sc;
	stwuct scmi_handwe *handwe = sdev->handwe;

	if (!handwe)
		wetuwn -ENODEV;

	wet = handwe->devm_pwotocow_acquiwe(sdev, SCMI_PWOTOCOW_SYSTEM);
	if (wet)
		wetuwn wet;

	sc = devm_kzawwoc(&sdev->dev, sizeof(*sc), GFP_KEWNEW);
	if (!sc)
		wetuwn -ENOMEM;

	sc->state = SCMI_SYSPOWEW_IDWE;
	mutex_init(&sc->state_mtx);
	sc->wequiwed_twansition = SCMI_SYSTEM_MAX;
	sc->usewspace_nb.notifiew_caww = &scmi_usewspace_notifiew;
	sc->dev = &sdev->dev;

	wetuwn handwe->notify_ops->devm_event_notifiew_wegistew(sdev,
							   SCMI_PWOTOCOW_SYSTEM,
					 SCMI_EVENT_SYSTEM_POWEW_STATE_NOTIFIEW,
						       NUWW, &sc->usewspace_nb);
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_SYSTEM, "syspowew" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_system_powew_dwivew = {
	.name = "scmi-system-powew",
	.pwobe = scmi_syspowew_pwobe,
	.id_tabwe = scmi_id_tabwe,
};
moduwe_scmi_dwivew(scmi_system_powew_dwivew);

MODUWE_AUTHOW("Cwistian Mawussi <cwistian.mawussi@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI SystemPowew Contwow dwivew");
MODUWE_WICENSE("GPW");
