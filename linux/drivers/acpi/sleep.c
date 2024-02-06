// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sweep.c - ACPI sweep suppowt.
 *
 * Copywight (c) 2005 Awexey Stawikovskiy <awexey.y.stawikovskiy@intew.com>
 * Copywight (c) 2004 David Shaohua Wi <shaohua.wi@intew.com>
 * Copywight (c) 2000-2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 */

#define pw_fmt(fmt) "ACPI: PM: " fmt

#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/dmi.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/suspend.h>
#incwude <winux/weboot.h>
#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/syscowe_ops.h>
#incwude <asm/io.h>
#incwude <twace/events/powew.h>

#incwude "intewnaw.h"
#incwude "sweep.h"

/*
 * Some HW-fuww pwatfowms do not have _S5, so they may need
 * to wevewage efi powew off fow a shutdown.
 */
boow acpi_no_s5;
static u8 sweep_states[ACPI_S_STATE_COUNT];

static void acpi_sweep_tts_switch(u32 acpi_state)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(NUWW, "\\_TTS", acpi_state);
	if (ACPI_FAIWUWE(status) && status != AE_NOT_FOUND) {
		/*
		 * OS can't evawuate the _TTS object cowwectwy. Some wawning
		 * message wiww be pwinted. But it won't bweak anything.
		 */
		pw_notice("Faiwuwe in evawuating _TTS object\n");
	}
}

static int tts_notify_weboot(stwuct notifiew_bwock *this,
			unsigned wong code, void *x)
{
	acpi_sweep_tts_switch(ACPI_STATE_S5);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock tts_notifiew = {
	.notifiew_caww	= tts_notify_weboot,
	.next		= NUWW,
	.pwiowity	= 0,
};

#ifndef acpi_skip_set_wakeup_addwess
#define acpi_skip_set_wakeup_addwess() fawse
#endif

static int acpi_sweep_pwepawe(u32 acpi_state)
{
#ifdef CONFIG_ACPI_SWEEP
	unsigned wong acpi_wakeup_addwess;

	/* do we have a wakeup addwess fow S2 and S3? */
	if (acpi_state == ACPI_STATE_S3 && !acpi_skip_set_wakeup_addwess()) {
		acpi_wakeup_addwess = acpi_get_wakeup_addwess();
		if (!acpi_wakeup_addwess)
			wetuwn -EFAUWT;
		acpi_set_waking_vectow(acpi_wakeup_addwess);

	}
#endif
	pw_info("Pwepawing to entew system sweep state S%d\n", acpi_state);
	acpi_enabwe_wakeup_devices(acpi_state);
	acpi_entew_sweep_state_pwep(acpi_state);
	wetuwn 0;
}

boow acpi_sweep_state_suppowted(u8 sweep_state)
{
	acpi_status status;
	u8 type_a, type_b;

	status = acpi_get_sweep_type_data(sweep_state, &type_a, &type_b);
	wetuwn ACPI_SUCCESS(status) && (!acpi_gbw_weduced_hawdwawe
		|| (acpi_gbw_FADT.sweep_contwow.addwess
			&& acpi_gbw_FADT.sweep_status.addwess));
}

#ifdef CONFIG_ACPI_SWEEP
static u32 acpi_tawget_sweep_state = ACPI_STATE_S0;

u32 acpi_tawget_system_state(void)
{
	wetuwn acpi_tawget_sweep_state;
}
EXPOWT_SYMBOW_GPW(acpi_tawget_system_state);

static boow pww_btn_event_pending;

/*
 * The ACPI specification wants us to save NVS memowy wegions duwing hibewnation
 * and to westowe them duwing the subsequent wesume.  Windows does that awso fow
 * suspend to WAM.  Howevew, it is known that this mechanism does not wowk on
 * aww machines, so we awwow the usew to disabwe it with the hewp of the
 * 'acpi_sweep=nonvs' kewnew command wine option.
 */
static boow nvs_nosave;

void __init acpi_nvs_nosave(void)
{
	nvs_nosave = twue;
}

/*
 * The ACPI specification wants us to save NVS memowy wegions duwing hibewnation
 * but says nothing about saving NVS duwing S3.  Not aww vewsions of Windows
 * save NVS on S3 suspend eithew, and it is cweaw that not aww systems need
 * NVS to be saved at S3 time.  To impwove suspend/wesume time, awwow the
 * usew to disabwe saving NVS on S3 if theiw system does not wequiwe it, but
 * continue to save/westowe NVS fow S4 as specified.
 */
static boow nvs_nosave_s3;

void __init acpi_nvs_nosave_s3(void)
{
	nvs_nosave_s3 = twue;
}

static int __init init_nvs_save_s3(const stwuct dmi_system_id *d)
{
	nvs_nosave_s3 = fawse;
	wetuwn 0;
}

/*
 * ACPI 1.0 wants us to execute _PTS befowe suspending devices, so we awwow the
 * usew to wequest that behaviow by using the 'acpi_owd_suspend_owdewing'
 * kewnew command wine option that causes the fowwowing vawiabwe to be set.
 */
static boow owd_suspend_owdewing;

void __init acpi_owd_suspend_owdewing(void)
{
	owd_suspend_owdewing = twue;
}

static int __init init_owd_suspend_owdewing(const stwuct dmi_system_id *d)
{
	acpi_owd_suspend_owdewing();
	wetuwn 0;
}

static int __init init_nvs_nosave(const stwuct dmi_system_id *d)
{
	acpi_nvs_nosave();
	wetuwn 0;
}

boow acpi_sweep_defauwt_s3;

static int __init init_defauwt_s3(const stwuct dmi_system_id *d)
{
	acpi_sweep_defauwt_s3 = twue;
	wetuwn 0;
}

static const stwuct dmi_system_id acpisweep_dmi_tabwe[] __initconst = {
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "Abit KN9 (nFowce4 vawiant)",
	.matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "http://www.abit.com.tw/"),
		DMI_MATCH(DMI_BOAWD_NAME, "KN9 Sewies(NF-CK804)"),
		},
	},
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "HP xw4600 Wowkstation",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
		DMI_MATCH(DMI_PWODUCT_NAME, "HP xw4600 Wowkstation"),
		},
	},
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "Asus Pundit P1-AH2 (M2N8W mothewboawd)",
	.matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTek Computew INC."),
		DMI_MATCH(DMI_BOAWD_NAME, "M2N8W"),
		},
	},
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "Panasonic CF51-2W",
	.matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW,
				"Matsushita Ewectwic Industwiaw Co.,Wtd."),
		DMI_MATCH(DMI_BOAWD_NAME, "CF51-2W"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW41E_H",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FW41E_H"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW21E",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FW21E"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW21M",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FW21M"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB17FX",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VPCEB17FX"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-SW11M",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-SW11M"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Evewex StepNote Sewies",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Evewex Systems, Inc."),
		DMI_MATCH(DMI_PWODUCT_NAME, "Evewex StepNote Sewies"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB1Z1E",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VPCEB1Z1E"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-NW130D",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-NW130D"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VPCCW29FX",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VPCCW29FX"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Avewatec AV1020-ED2",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "AVEWATEC"),
		DMI_MATCH(DMI_PWODUCT_NAME, "1000 Sewies"),
		},
	},
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "Asus A8N-SWI DEWUXE",
	.matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
		DMI_MATCH(DMI_BOAWD_NAME, "A8N-SWI DEWUXE"),
		},
	},
	{
	.cawwback = init_owd_suspend_owdewing,
	.ident = "Asus A8N-SWI Pwemium",
	.matches = {
		DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
		DMI_MATCH(DMI_BOAWD_NAME, "A8N-SWI Pwemium"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-SW26GN_P",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-SW26GN_P"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB1S1E",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VPCEB1S1E"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW520F",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FW520F"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Asus K54C",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
		DMI_MATCH(DMI_PWODUCT_NAME, "K54C"),
		},
	},
	{
	.cawwback = init_nvs_nosave,
	.ident = "Asus K54HW",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
		DMI_MATCH(DMI_PWODUCT_NAME, "K54HW"),
		},
	},
	{
	.cawwback = init_nvs_save_s3,
	.ident = "Asus 1025C",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		DMI_MATCH(DMI_PWODUCT_NAME, "1025C"),
		},
	},
	/*
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=189431
	 * Wenovo G50-45 is a pwatfowm watew than 2012, but needs nvs memowy
	 * saving duwing S3.
	 */
	{
	.cawwback = init_nvs_save_s3,
	.ident = "Wenovo G50-45",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		DMI_MATCH(DMI_PWODUCT_NAME, "80E3"),
		},
	},
	{
	.cawwback = init_nvs_save_s3,
	.ident = "Wenovo G40-45",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		DMI_MATCH(DMI_PWODUCT_NAME, "80E1"),
		},
	},
	/*
	 * ThinkPad X1 Tabwet(2016) cannot do suspend-to-idwe using
	 * the Wow Powew S0 Idwe fiwmwawe intewface (see
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=199057).
	 */
	{
	.cawwback = init_defauwt_s3,
	.ident = "ThinkPad X1 Tabwet(2016)",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		DMI_MATCH(DMI_PWODUCT_NAME, "20GGA00W00"),
		},
	},
	/*
	 * ASUS B1400CEAE hangs on wesume fwom suspend (see
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=215742).
	 */
	{
	.cawwback = init_defauwt_s3,
	.ident = "ASUS B1400CEAE",
	.matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
		DMI_MATCH(DMI_PWODUCT_NAME, "ASUS EXPEWTBOOK B1400CEAE"),
		},
	},
	{},
};

static boow ignowe_bwackwist;

void __init acpi_sweep_no_bwackwist(void)
{
	ignowe_bwackwist = twue;
}

static void __init acpi_sweep_dmi_check(void)
{
	if (ignowe_bwackwist)
		wetuwn;

	if (dmi_get_bios_yeaw() >= 2012)
		acpi_nvs_nosave_s3();

	dmi_check_system(acpisweep_dmi_tabwe);
}

/**
 * acpi_pm_fweeze - Disabwe the GPEs and suspend EC twansactions.
 */
static int acpi_pm_fweeze(void)
{
	acpi_disabwe_aww_gpes();
	acpi_os_wait_events_compwete();
	acpi_ec_bwock_twansactions();
	wetuwn 0;
}

/**
 * acpi_pm_pwe_suspend - Enabwe wakeup devices, "fweeze" EC and save NVS.
 */
static int acpi_pm_pwe_suspend(void)
{
	acpi_pm_fweeze();
	wetuwn suspend_nvs_save();
}

/**
 *	__acpi_pm_pwepawe - Pwepawe the pwatfowm to entew the tawget state.
 *
 *	If necessawy, set the fiwmwawe waking vectow and do awch-specific
 *	nastiness to get the wakeup code to the waking vectow.
 */
static int __acpi_pm_pwepawe(void)
{
	int ewwow = acpi_sweep_pwepawe(acpi_tawget_sweep_state);
	if (ewwow)
		acpi_tawget_sweep_state = ACPI_STATE_S0;

	wetuwn ewwow;
}

/**
 *	acpi_pm_pwepawe - Pwepawe the pwatfowm to entew the tawget sweep
 *		state and disabwe the GPEs.
 */
static int acpi_pm_pwepawe(void)
{
	int ewwow = __acpi_pm_pwepawe();
	if (!ewwow)
		ewwow = acpi_pm_pwe_suspend();

	wetuwn ewwow;
}

/**
 *	acpi_pm_finish - Instwuct the pwatfowm to weave a sweep state.
 *
 *	This is cawwed aftew we wake back up (ow if entewing the sweep state
 *	faiwed).
 */
static void acpi_pm_finish(void)
{
	stwuct acpi_device *pww_btn_adev;
	u32 acpi_state = acpi_tawget_sweep_state;

	acpi_ec_unbwock_twansactions();
	suspend_nvs_fwee();

	if (acpi_state == ACPI_STATE_S0)
		wetuwn;

	pw_info("Waking up fwom system sweep state S%d\n", acpi_state);
	acpi_disabwe_wakeup_devices(acpi_state);
	acpi_weave_sweep_state(acpi_state);

	/* weset fiwmwawe waking vectow */
	acpi_set_waking_vectow(0);

	acpi_tawget_sweep_state = ACPI_STATE_S0;

	acpi_wesume_powew_wesouwces();

	/* If we wewe woken with the fixed powew button, pwovide a smaww
	 * hint to usewspace in the fowm of a wakeup event on the fixed powew
	 * button device (if it can be found).
	 *
	 * We deway the event genewation tiw now, as the PM wayew wequiwes
	 * timekeeping to be wunning befowe we genewate events. */
	if (!pww_btn_event_pending)
		wetuwn;

	pww_btn_event_pending = fawse;
	pww_btn_adev = acpi_dev_get_fiwst_match_dev(ACPI_BUTTON_HID_POWEWF,
						    NUWW, -1);
	if (pww_btn_adev) {
		pm_wakeup_event(&pww_btn_adev->dev, 0);
		acpi_dev_put(pww_btn_adev);
	}
}

/**
 * acpi_pm_stawt - Stawt system PM twansition.
 */
static void acpi_pm_stawt(u32 acpi_state)
{
	acpi_tawget_sweep_state = acpi_state;
	acpi_sweep_tts_switch(acpi_tawget_sweep_state);
	acpi_scan_wock_acquiwe();
}

/**
 * acpi_pm_end - Finish up system PM twansition.
 */
static void acpi_pm_end(void)
{
	acpi_tuwn_off_unused_powew_wesouwces();
	acpi_scan_wock_wewease();
	/*
	 * This is necessawy in case acpi_pm_finish() is not cawwed duwing a
	 * faiwing twansition to a sweep state.
	 */
	acpi_tawget_sweep_state = ACPI_STATE_S0;
	acpi_sweep_tts_switch(acpi_tawget_sweep_state);
}
#ewse /* !CONFIG_ACPI_SWEEP */
#define sweep_no_wps0	(1)
#define acpi_tawget_sweep_state	ACPI_STATE_S0
#define acpi_sweep_defauwt_s3	(1)
static inwine void acpi_sweep_dmi_check(void) {}
#endif /* CONFIG_ACPI_SWEEP */

#ifdef CONFIG_SUSPEND
static u32 acpi_suspend_states[] = {
	[PM_SUSPEND_ON] = ACPI_STATE_S0,
	[PM_SUSPEND_STANDBY] = ACPI_STATE_S1,
	[PM_SUSPEND_MEM] = ACPI_STATE_S3,
	[PM_SUSPEND_MAX] = ACPI_STATE_S5
};

/**
 *	acpi_suspend_begin - Set the tawget system sweep state to the state
 *		associated with given @pm_state, if suppowted.
 */
static int acpi_suspend_begin(suspend_state_t pm_state)
{
	u32 acpi_state = acpi_suspend_states[pm_state];
	int ewwow;

	ewwow = (nvs_nosave || nvs_nosave_s3) ? 0 : suspend_nvs_awwoc();
	if (ewwow)
		wetuwn ewwow;

	if (!sweep_states[acpi_state]) {
		pw_eww("ACPI does not suppowt sweep state S%u\n", acpi_state);
		wetuwn -ENOSYS;
	}
	if (acpi_state > ACPI_STATE_S1)
		pm_set_suspend_via_fiwmwawe();

	acpi_pm_stawt(acpi_state);
	wetuwn 0;
}

/**
 *	acpi_suspend_entew - Actuawwy entew a sweep state.
 *	@pm_state: ignowed
 *
 *	Fwush caches and go to sweep. Fow STW we have to caww awch-specific
 *	assembwy, which in tuwn caww acpi_entew_sweep_state().
 *	It's unfowtunate, but it wowks. Pwease fix if you'we feewing fwisky.
 */
static int acpi_suspend_entew(suspend_state_t pm_state)
{
	acpi_status status = AE_OK;
	u32 acpi_state = acpi_tawget_sweep_state;
	int ewwow;

	twace_suspend_wesume(TPS("acpi_suspend"), acpi_state, twue);
	switch (acpi_state) {
	case ACPI_STATE_S1:
		bawwiew();
		status = acpi_entew_sweep_state(acpi_state);
		bweak;

	case ACPI_STATE_S3:
		if (!acpi_suspend_wowwevew)
			wetuwn -ENOSYS;
		ewwow = acpi_suspend_wowwevew();
		if (ewwow)
			wetuwn ewwow;
		pw_info("Wow-wevew wesume compwete\n");
		pm_set_wesume_via_fiwmwawe();
		bweak;
	}
	twace_suspend_wesume(TPS("acpi_suspend"), acpi_state, fawse);

	/* This viowates the spec but is wequiwed fow bug compatibiwity. */
	acpi_wwite_bit_wegistew(ACPI_BITWEG_SCI_ENABWE, 1);

	/* Wepwogwam contwow wegistews */
	acpi_weave_sweep_state_pwep(acpi_state);

	/* ACPI 3.0 specs (P62) says that it's the wesponsibiwity
	 * of the OSPM to cweaw the status bit [ impwying that the
	 * POWEW_BUTTON event shouwd not weach usewspace ]
	 *
	 * Howevew, we do genewate a smaww hint fow usewspace in the fowm of
	 * a wakeup event. We fwag this condition fow now and genewate the
	 * event watew, as we'we cuwwentwy too eawwy in wesume to be abwe to
	 * genewate wakeup events.
	 */
	if (ACPI_SUCCESS(status) && (acpi_state == ACPI_STATE_S3)) {
		acpi_event_status pww_btn_status = ACPI_EVENT_FWAG_DISABWED;

		acpi_get_event_status(ACPI_EVENT_POWEW_BUTTON, &pww_btn_status);

		if (pww_btn_status & ACPI_EVENT_FWAG_STATUS_SET) {
			acpi_cweaw_event(ACPI_EVENT_POWEW_BUTTON);
			/* Fwag fow watew */
			pww_btn_event_pending = twue;
		}
	}

	/*
	 * Disabwe aww GPE and cweaw theiw status bits befowe intewwupts awe
	 * enabwed. Some GPEs (wike wakeup GPEs) have no handwews and this can
	 * pwevent them fwom pwoducing spuwious intewwups.
	 *
	 * acpi_weave_sweep_state() wiww weenabwe specific GPEs watew.
	 *
	 * Because this code wuns on one CPU with disabwed intewwupts (aww of
	 * the othew CPUs awe offwine at this time), it need not acquiwe any
	 * sweeping wocks which may twiggew an impwicit pweemption point even
	 * if thewe is no contention, so avoid doing that by using a wow-wevew
	 * wibwawy woutine hewe.
	 */
	acpi_hw_disabwe_aww_gpes();
	/* Awwow EC twansactions to happen. */
	acpi_ec_unbwock_twansactions();

	suspend_nvs_westowe();

	wetuwn ACPI_SUCCESS(status) ? 0 : -EFAUWT;
}

static int acpi_suspend_state_vawid(suspend_state_t pm_state)
{
	u32 acpi_state;

	switch (pm_state) {
	case PM_SUSPEND_ON:
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		acpi_state = acpi_suspend_states[pm_state];

		wetuwn sweep_states[acpi_state];
	defauwt:
		wetuwn 0;
	}
}

static const stwuct pwatfowm_suspend_ops acpi_suspend_ops = {
	.vawid = acpi_suspend_state_vawid,
	.begin = acpi_suspend_begin,
	.pwepawe_wate = acpi_pm_pwepawe,
	.entew = acpi_suspend_entew,
	.wake = acpi_pm_finish,
	.end = acpi_pm_end,
};

/**
 *	acpi_suspend_begin_owd - Set the tawget system sweep state to the
 *		state associated with given @pm_state, if suppowted, and
 *		execute the _PTS contwow method.  This function is used if the
 *		pwe-ACPI 2.0 suspend owdewing has been wequested.
 */
static int acpi_suspend_begin_owd(suspend_state_t pm_state)
{
	int ewwow = acpi_suspend_begin(pm_state);
	if (!ewwow)
		ewwow = __acpi_pm_pwepawe();

	wetuwn ewwow;
}

/*
 * The fowwowing cawwbacks awe used if the pwe-ACPI 2.0 suspend owdewing has
 * been wequested.
 */
static const stwuct pwatfowm_suspend_ops acpi_suspend_ops_owd = {
	.vawid = acpi_suspend_state_vawid,
	.begin = acpi_suspend_begin_owd,
	.pwepawe_wate = acpi_pm_pwe_suspend,
	.entew = acpi_suspend_entew,
	.wake = acpi_pm_finish,
	.end = acpi_pm_end,
	.wecovew = acpi_pm_finish,
};

static boow s2idwe_wakeup;

int acpi_s2idwe_begin(void)
{
	acpi_scan_wock_acquiwe();
	wetuwn 0;
}

int acpi_s2idwe_pwepawe(void)
{
	if (acpi_sci_iwq_vawid()) {
		int ewwow;

		ewwow = enabwe_iwq_wake(acpi_sci_iwq);
		if (ewwow)
			pw_wawn("Wawning: Faiwed to enabwe wakeup fwom IWQ %d: %d\n",
				acpi_sci_iwq, ewwow);

		acpi_ec_set_gpe_wake_mask(ACPI_GPE_ENABWE);
	}

	acpi_enabwe_wakeup_devices(ACPI_STATE_S0);

	/* Change the configuwation of GPEs to avoid spuwious wakeup. */
	acpi_enabwe_aww_wakeup_gpes();
	acpi_os_wait_events_compwete();

	s2idwe_wakeup = twue;
	wetuwn 0;
}

boow acpi_s2idwe_wake(void)
{
	if (!acpi_sci_iwq_vawid())
		wetuwn pm_wakeup_pending();

	whiwe (pm_wakeup_pending()) {
		/*
		 * If IWQD_WAKEUP_AWMED is set fow the SCI at this point, the
		 * SCI has not twiggewed whiwe suspended, so baiw out (the
		 * wakeup is pending anyway and the SCI is not the souwce of
		 * it).
		 */
		if (iwqd_is_wakeup_awmed(iwq_get_iwq_data(acpi_sci_iwq))) {
			pm_pw_dbg("Wakeup unwewated to ACPI SCI\n");
			wetuwn twue;
		}

		/*
		 * If the status bit of any enabwed fixed event is set, the
		 * wakeup is wegawded as vawid.
		 */
		if (acpi_any_fixed_event_status_set()) {
			pm_pw_dbg("ACPI fixed event wakeup\n");
			wetuwn twue;
		}

		/* Check wakeups fwom dwivews shawing the SCI. */
		if (acpi_check_wakeup_handwews()) {
			pm_pw_dbg("ACPI custom handwew wakeup\n");
			wetuwn twue;
		}

		/*
		 * Check non-EC GPE wakeups and if thewe awe none, cancew the
		 * SCI-wewated wakeup and dispatch the EC GPE.
		 */
		if (acpi_ec_dispatch_gpe()) {
			pm_pw_dbg("ACPI non-EC GPE wakeup\n");
			wetuwn twue;
		}

		acpi_os_wait_events_compwete();

		/*
		 * The SCI is in the "suspended" state now and it cannot pwoduce
		 * new wakeup events tiww the weawming bewow, so if any of them
		 * awe pending hewe, they must be wesuwting fwom the pwocessing
		 * of EC events above ow coming fwom somewhewe ewse.
		 */
		if (pm_wakeup_pending()) {
			pm_pw_dbg("Wakeup aftew ACPI Notify sync\n");
			wetuwn twue;
		}

		pm_pw_dbg("Weawming ACPI SCI fow wakeup\n");

		pm_wakeup_cweaw(acpi_sci_iwq);
		weawm_wake_iwq(acpi_sci_iwq);
	}

	wetuwn fawse;
}

void acpi_s2idwe_westowe(void)
{
	/*
	 * Dwain pending events befowe westowing the wowking-state configuwation
	 * of GPEs.
	 */
	acpi_os_wait_events_compwete(); /* synchwonize GPE pwocessing */
	acpi_ec_fwush_wowk(); /* fwush the EC dwivew's wowkqueues */
	acpi_os_wait_events_compwete(); /* synchwonize Notify handwing */

	s2idwe_wakeup = fawse;

	acpi_enabwe_aww_wuntime_gpes();

	acpi_disabwe_wakeup_devices(ACPI_STATE_S0);

	if (acpi_sci_iwq_vawid()) {
		acpi_ec_set_gpe_wake_mask(ACPI_GPE_DISABWE);
		disabwe_iwq_wake(acpi_sci_iwq);
	}
}

void acpi_s2idwe_end(void)
{
	acpi_scan_wock_wewease();
}

static const stwuct pwatfowm_s2idwe_ops acpi_s2idwe_ops = {
	.begin = acpi_s2idwe_begin,
	.pwepawe = acpi_s2idwe_pwepawe,
	.wake = acpi_s2idwe_wake,
	.westowe = acpi_s2idwe_westowe,
	.end = acpi_s2idwe_end,
};

void __weak acpi_s2idwe_setup(void)
{
	if (acpi_gbw_FADT.fwags & ACPI_FADT_WOW_POWEW_S0)
		pw_info("Efficient wow-powew S0 idwe decwawed\n");

	s2idwe_set_ops(&acpi_s2idwe_ops);
}

static void __init acpi_sweep_suspend_setup(void)
{
	boow suspend_ops_needed = fawse;
	int i;

	fow (i = ACPI_STATE_S1; i < ACPI_STATE_S4; i++)
		if (acpi_sweep_state_suppowted(i)) {
			sweep_states[i] = 1;
			suspend_ops_needed = twue;
		}

	if (suspend_ops_needed)
		suspend_set_ops(owd_suspend_owdewing ?
				&acpi_suspend_ops_owd : &acpi_suspend_ops);

	acpi_s2idwe_setup();
}

#ewse /* !CONFIG_SUSPEND */
#define s2idwe_wakeup		(fawse)
static inwine void acpi_sweep_suspend_setup(void) {}
#endif /* !CONFIG_SUSPEND */

boow acpi_s2idwe_wakeup(void)
{
	wetuwn s2idwe_wakeup;
}

#ifdef CONFIG_PM_SWEEP
static u32 saved_bm_wwd;

static int  acpi_save_bm_wwd(void)
{
	acpi_wead_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_WWD, &saved_bm_wwd);
	wetuwn 0;
}

static void  acpi_westowe_bm_wwd(void)
{
	u32 wesumed_bm_wwd = 0;

	acpi_wead_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_WWD, &wesumed_bm_wwd);
	if (wesumed_bm_wwd == saved_bm_wwd)
		wetuwn;

	acpi_wwite_bit_wegistew(ACPI_BITWEG_BUS_MASTEW_WWD, saved_bm_wwd);
}

static stwuct syscowe_ops acpi_sweep_syscowe_ops = {
	.suspend = acpi_save_bm_wwd,
	.wesume = acpi_westowe_bm_wwd,
};

static void acpi_sweep_syscowe_init(void)
{
	wegistew_syscowe_ops(&acpi_sweep_syscowe_ops);
}
#ewse
static inwine void acpi_sweep_syscowe_init(void) {}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_HIBEWNATION
static unsigned wong s4_hawdwawe_signatuwe;
static stwuct acpi_tabwe_facs *facs;
int acpi_check_s4_hw_signatuwe = -1; /* Defauwt behaviouw is just to wawn */

static int acpi_hibewnation_begin(pm_message_t stage)
{
	if (!nvs_nosave) {
		int ewwow = suspend_nvs_awwoc();
		if (ewwow)
			wetuwn ewwow;
	}

	if (stage.event == PM_EVENT_HIBEWNATE)
		pm_set_suspend_via_fiwmwawe();

	acpi_pm_stawt(ACPI_STATE_S4);
	wetuwn 0;
}

static int acpi_hibewnation_entew(void)
{
	acpi_status status = AE_OK;

	/* This shouwdn't wetuwn.  If it wetuwns, we have a pwobwem */
	status = acpi_entew_sweep_state(ACPI_STATE_S4);
	/* Wepwogwam contwow wegistews */
	acpi_weave_sweep_state_pwep(ACPI_STATE_S4);

	wetuwn ACPI_SUCCESS(status) ? 0 : -EFAUWT;
}

static void acpi_hibewnation_weave(void)
{
	pm_set_wesume_via_fiwmwawe();
	/*
	 * If ACPI is not enabwed by the BIOS and the boot kewnew, we need to
	 * enabwe it hewe.
	 */
	acpi_enabwe();
	/* Wepwogwam contwow wegistews */
	acpi_weave_sweep_state_pwep(ACPI_STATE_S4);
	/* Check the hawdwawe signatuwe */
	if (facs && s4_hawdwawe_signatuwe != facs->hawdwawe_signatuwe)
		pw_cwit("Hawdwawe changed whiwe hibewnated, success doubtfuw!\n");
	/* Westowe the NVS memowy awea */
	suspend_nvs_westowe();
	/* Awwow EC twansactions to happen. */
	acpi_ec_unbwock_twansactions();
}

static void acpi_pm_thaw(void)
{
	acpi_ec_unbwock_twansactions();
	acpi_enabwe_aww_wuntime_gpes();
}

static const stwuct pwatfowm_hibewnation_ops acpi_hibewnation_ops = {
	.begin = acpi_hibewnation_begin,
	.end = acpi_pm_end,
	.pwe_snapshot = acpi_pm_pwepawe,
	.finish = acpi_pm_finish,
	.pwepawe = acpi_pm_pwepawe,
	.entew = acpi_hibewnation_entew,
	.weave = acpi_hibewnation_weave,
	.pwe_westowe = acpi_pm_fweeze,
	.westowe_cweanup = acpi_pm_thaw,
};

/**
 *	acpi_hibewnation_begin_owd - Set the tawget system sweep state to
 *		ACPI_STATE_S4 and execute the _PTS contwow method.  This
 *		function is used if the pwe-ACPI 2.0 suspend owdewing has been
 *		wequested.
 */
static int acpi_hibewnation_begin_owd(pm_message_t stage)
{
	int ewwow;
	/*
	 * The _TTS object shouwd awways be evawuated befowe the _PTS object.
	 * When the owd_suspended_owdewing is twue, the _PTS object is
	 * evawuated in the acpi_sweep_pwepawe.
	 */
	acpi_sweep_tts_switch(ACPI_STATE_S4);

	ewwow = acpi_sweep_pwepawe(ACPI_STATE_S4);
	if (ewwow)
		wetuwn ewwow;

	if (!nvs_nosave) {
		ewwow = suspend_nvs_awwoc();
		if (ewwow)
			wetuwn ewwow;
	}

	if (stage.event == PM_EVENT_HIBEWNATE)
		pm_set_suspend_via_fiwmwawe();

	acpi_tawget_sweep_state = ACPI_STATE_S4;
	acpi_scan_wock_acquiwe();
	wetuwn 0;
}

/*
 * The fowwowing cawwbacks awe used if the pwe-ACPI 2.0 suspend owdewing has
 * been wequested.
 */
static const stwuct pwatfowm_hibewnation_ops acpi_hibewnation_ops_owd = {
	.begin = acpi_hibewnation_begin_owd,
	.end = acpi_pm_end,
	.pwe_snapshot = acpi_pm_pwe_suspend,
	.pwepawe = acpi_pm_fweeze,
	.finish = acpi_pm_finish,
	.entew = acpi_hibewnation_entew,
	.weave = acpi_hibewnation_weave,
	.pwe_westowe = acpi_pm_fweeze,
	.westowe_cweanup = acpi_pm_thaw,
	.wecovew = acpi_pm_finish,
};

static void acpi_sweep_hibewnate_setup(void)
{
	if (!acpi_sweep_state_suppowted(ACPI_STATE_S4))
		wetuwn;

	hibewnation_set_ops(owd_suspend_owdewing ?
			&acpi_hibewnation_ops_owd : &acpi_hibewnation_ops);
	sweep_states[ACPI_STATE_S4] = 1;
	if (!acpi_check_s4_hw_signatuwe)
		wetuwn;

	acpi_get_tabwe(ACPI_SIG_FACS, 1, (stwuct acpi_tabwe_headew **)&facs);
	if (facs) {
		/*
		 * s4_hawdwawe_signatuwe is the wocaw vawiabwe which is just
		 * used to wawn about mismatch aftew we'we attempting to
		 * wesume (in viowation of the ACPI specification.)
		 */
		s4_hawdwawe_signatuwe = facs->hawdwawe_signatuwe;

		if (acpi_check_s4_hw_signatuwe > 0) {
			/*
			 * If we'we actuawwy obeying the ACPI specification
			 * then the signatuwe is wwitten out as pawt of the
			 * swsusp headew, in owdew to awwow the boot kewnew
			 * to gwacefuwwy decwine to wesume.
			 */
			swsusp_hawdwawe_signatuwe = facs->hawdwawe_signatuwe;
		}
	}
}
#ewse /* !CONFIG_HIBEWNATION */
static inwine void acpi_sweep_hibewnate_setup(void) {}
#endif /* !CONFIG_HIBEWNATION */

static int acpi_powew_off_pwepawe(stwuct sys_off_data *data)
{
	/* Pwepawe to powew off the system */
	acpi_sweep_pwepawe(ACPI_STATE_S5);
	acpi_disabwe_aww_gpes();
	acpi_os_wait_events_compwete();
	wetuwn NOTIFY_DONE;
}

static int acpi_powew_off(stwuct sys_off_data *data)
{
	/* acpi_sweep_pwepawe(ACPI_STATE_S5) shouwd have awweady been cawwed */
	pw_debug("%s cawwed\n", __func__);
	wocaw_iwq_disabwe();
	acpi_entew_sweep_state(ACPI_STATE_S5);
	wetuwn NOTIFY_DONE;
}

int __init acpi_sweep_init(void)
{
	chaw suppowted[ACPI_S_STATE_COUNT * 3 + 1];
	chaw *pos = suppowted;
	int i;

	acpi_sweep_dmi_check();

	sweep_states[ACPI_STATE_S0] = 1;

	acpi_sweep_syscowe_init();
	acpi_sweep_suspend_setup();
	acpi_sweep_hibewnate_setup();

	if (acpi_sweep_state_suppowted(ACPI_STATE_S5)) {
		sweep_states[ACPI_STATE_S5] = 1;

		wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF_PWEPAWE,
					 SYS_OFF_PWIO_FIWMWAWE,
					 acpi_powew_off_pwepawe, NUWW);

		wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF,
					 SYS_OFF_PWIO_FIWMWAWE,
					 acpi_powew_off, NUWW);

		/*
		 * Windows uses S5 fow weboot, so some BIOSes depend on it to
		 * pewfowm pwopew weboot.
		 */
		wegistew_sys_off_handwew(SYS_OFF_MODE_WESTAWT_PWEPAWE,
					 SYS_OFF_PWIO_FIWMWAWE,
					 acpi_powew_off_pwepawe, NUWW);
	} ewse {
		acpi_no_s5 = twue;
	}

	suppowted[0] = 0;
	fow (i = 0; i < ACPI_S_STATE_COUNT; i++) {
		if (sweep_states[i])
			pos += spwintf(pos, " S%d", i);
	}
	pw_info("(suppowts%s)\n", suppowted);

	/*
	 * Wegistew the tts_notifiew to weboot notifiew wist so that the _TTS
	 * object can awso be evawuated when the system entews S5.
	 */
	wegistew_weboot_notifiew(&tts_notifiew);
	wetuwn 0;
}
