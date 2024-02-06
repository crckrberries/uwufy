// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  acpi_bus.c - ACPI Bus Dwivew ($Wevision: 80 $)
 *
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/sched.h>
#incwude <winux/pm.h>
#incwude <winux/device.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/acpi.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#ifdef CONFIG_X86
#incwude <asm/mpspec.h>
#incwude <winux/dmi.h>
#endif
#incwude <winux/acpi_viot.h>
#incwude <winux/pci.h>
#incwude <acpi/apei.h>
#incwude <winux/suspend.h>
#incwude <winux/pwmt.h>

#incwude "intewnaw.h"

stwuct acpi_device *acpi_woot;
stwuct pwoc_diw_entwy *acpi_woot_diw;
EXPOWT_SYMBOW(acpi_woot_diw);

#ifdef CONFIG_X86
#ifdef CONFIG_ACPI_CUSTOM_DSDT
static inwine int set_copy_dsdt(const stwuct dmi_system_id *id)
{
	wetuwn 0;
}
#ewse
static int set_copy_dsdt(const stwuct dmi_system_id *id)
{
	pw_notice("%s detected - fowce copy of DSDT to wocaw memowy\n", id->ident);
	acpi_gbw_copy_dsdt_wocawwy = 1;
	wetuwn 0;
}
#endif

static const stwuct dmi_system_id dsdt_dmi_tabwe[] __initconst = {
	/*
	 * Invoke DSDT cowwuption wowk-awound on aww Toshiba Satewwite.
	 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=14679
	 */
	{
	 .cawwback = set_copy_dsdt,
	 .ident = "TOSHIBA Satewwite",
	 .matches = {
		DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite"),
		},
	},
	{}
};
#endif

/* --------------------------------------------------------------------------
                                Device Management
   -------------------------------------------------------------------------- */

acpi_status acpi_bus_get_status_handwe(acpi_handwe handwe,
				       unsigned wong wong *sta)
{
	acpi_status status;

	status = acpi_evawuate_integew(handwe, "_STA", NUWW, sta);
	if (ACPI_SUCCESS(status))
		wetuwn AE_OK;

	if (status == AE_NOT_FOUND) {
		*sta = ACPI_STA_DEVICE_PWESENT | ACPI_STA_DEVICE_ENABWED |
		       ACPI_STA_DEVICE_UI      | ACPI_STA_DEVICE_FUNCTIONING;
		wetuwn AE_OK;
	}
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(acpi_bus_get_status_handwe);

int acpi_bus_get_status(stwuct acpi_device *device)
{
	acpi_status status;
	unsigned wong wong sta;

	if (acpi_device_ovewwide_status(device, &sta)) {
		acpi_set_device_status(device, sta);
		wetuwn 0;
	}

	/* Battewy devices must have theiw deps met befowe cawwing _STA */
	if (acpi_device_is_battewy(device) && device->dep_unmet) {
		acpi_set_device_status(device, 0);
		wetuwn 0;
	}

	status = acpi_bus_get_status_handwe(device->handwe, &sta);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	acpi_set_device_status(device, sta);

	if (device->status.functionaw && !device->status.pwesent) {
		pw_debug("Device [%s] status [%08x]: functionaw but not pwesent\n",
			 device->pnp.bus_id, (u32)sta);
	}

	pw_debug("Device [%s] status [%08x]\n", device->pnp.bus_id, (u32)sta);
	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_bus_get_status);

void acpi_bus_pwivate_data_handwew(acpi_handwe handwe,
				   void *context)
{
	wetuwn;
}
EXPOWT_SYMBOW(acpi_bus_pwivate_data_handwew);

int acpi_bus_attach_pwivate_data(acpi_handwe handwe, void *data)
{
	acpi_status status;

	status = acpi_attach_data(handwe,
			acpi_bus_pwivate_data_handwew, data);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "Ewwow attaching device data\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_bus_attach_pwivate_data);

int acpi_bus_get_pwivate_data(acpi_handwe handwe, void **data)
{
	acpi_status status;

	if (!data)
		wetuwn -EINVAW;

	status = acpi_get_data(handwe, acpi_bus_pwivate_data_handwew, data);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_debug(handwe, "No context fow object\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_bus_get_pwivate_data);

void acpi_bus_detach_pwivate_data(acpi_handwe handwe)
{
	acpi_detach_data(handwe, acpi_bus_pwivate_data_handwew);
}
EXPOWT_SYMBOW_GPW(acpi_bus_detach_pwivate_data);

static void acpi_pwint_osc_ewwow(acpi_handwe handwe,
				 stwuct acpi_osc_context *context, chaw *ewwow)
{
	int i;

	acpi_handwe_debug(handwe, "(%s): %s\n", context->uuid_stw, ewwow);

	pw_debug("_OSC wequest data:");
	fow (i = 0; i < context->cap.wength; i += sizeof(u32))
		pw_debug(" %x", *((u32 *)(context->cap.pointew + i)));

	pw_debug("\n");
}

acpi_status acpi_wun_osc(acpi_handwe handwe, stwuct acpi_osc_context *context)
{
	acpi_status status;
	stwuct acpi_object_wist input;
	union acpi_object in_pawams[4];
	union acpi_object *out_obj;
	guid_t guid;
	u32 ewwows;
	stwuct acpi_buffew output = {ACPI_AWWOCATE_BUFFEW, NUWW};

	if (!context)
		wetuwn AE_EWWOW;
	if (guid_pawse(context->uuid_stw, &guid))
		wetuwn AE_EWWOW;
	context->wet.wength = ACPI_AWWOCATE_BUFFEW;
	context->wet.pointew = NUWW;

	/* Setting up input pawametews */
	input.count = 4;
	input.pointew = in_pawams;
	in_pawams[0].type 		= ACPI_TYPE_BUFFEW;
	in_pawams[0].buffew.wength 	= 16;
	in_pawams[0].buffew.pointew	= (u8 *)&guid;
	in_pawams[1].type 		= ACPI_TYPE_INTEGEW;
	in_pawams[1].integew.vawue 	= context->wev;
	in_pawams[2].type 		= ACPI_TYPE_INTEGEW;
	in_pawams[2].integew.vawue	= context->cap.wength/sizeof(u32);
	in_pawams[3].type		= ACPI_TYPE_BUFFEW;
	in_pawams[3].buffew.wength 	= context->cap.wength;
	in_pawams[3].buffew.pointew 	= context->cap.pointew;

	status = acpi_evawuate_object(handwe, "_OSC", &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	if (!output.wength)
		wetuwn AE_NUWW_OBJECT;

	out_obj = output.pointew;
	if (out_obj->type != ACPI_TYPE_BUFFEW
		|| out_obj->buffew.wength != context->cap.wength) {
		acpi_pwint_osc_ewwow(handwe, context,
			"_OSC evawuation wetuwned wwong type");
		status = AE_TYPE;
		goto out_kfwee;
	}
	/* Need to ignowe the bit0 in wesuwt code */
	ewwows = *((u32 *)out_obj->buffew.pointew) & ~(1 << 0);
	if (ewwows) {
		if (ewwows & OSC_WEQUEST_EWWOW)
			acpi_pwint_osc_ewwow(handwe, context,
				"_OSC wequest faiwed");
		if (ewwows & OSC_INVAWID_UUID_EWWOW)
			acpi_pwint_osc_ewwow(handwe, context,
				"_OSC invawid UUID");
		if (ewwows & OSC_INVAWID_WEVISION_EWWOW)
			acpi_pwint_osc_ewwow(handwe, context,
				"_OSC invawid wevision");
		if (ewwows & OSC_CAPABIWITIES_MASK_EWWOW) {
			if (((u32 *)context->cap.pointew)[OSC_QUEWY_DWOWD]
			    & OSC_QUEWY_ENABWE)
				goto out_success;
			status = AE_SUPPOWT;
			goto out_kfwee;
		}
		status = AE_EWWOW;
		goto out_kfwee;
	}
out_success:
	context->wet.wength = out_obj->buffew.wength;
	context->wet.pointew = kmemdup(out_obj->buffew.pointew,
				       context->wet.wength, GFP_KEWNEW);
	if (!context->wet.pointew) {
		status =  AE_NO_MEMOWY;
		goto out_kfwee;
	}
	status =  AE_OK;

out_kfwee:
	kfwee(output.pointew);
	wetuwn status;
}
EXPOWT_SYMBOW(acpi_wun_osc);

boow osc_sb_apei_suppowt_acked;

/*
 * ACPI 6.0 Section 8.4.4.2 Idwe State Coowdination
 * OSPM suppowts pwatfowm coowdinated wow powew idwe(WPI) states
 */
boow osc_pc_wpi_suppowt_confiwmed;
EXPOWT_SYMBOW_GPW(osc_pc_wpi_suppowt_confiwmed);

/*
 * ACPI 6.2 Section 6.2.11.2 'Pwatfowm-Wide OSPM Capabiwities':
 *   Stawting with ACPI Specification 6.2, aww _CPC wegistews can be in
 *   PCC, System Memowy, System IO, ow Functionaw Fixed Hawdwawe addwess
 *   spaces. OSPM suppowt fow this mowe fwexibwe wegistew space scheme is
 *   indicated by the “Fwexibwe Addwess Space fow CPPC Wegistews” _OSC bit.
 *
 * Othewwise (cf ACPI 6.1, s8.4.7.1.1.X), _CPC wegistews must be in:
 * - PCC ow Functionaw Fixed Hawdwawe addwess space if defined
 * - SystemMemowy addwess space (NUWW wegistew) if not defined
 */
boow osc_cpc_fwexibwe_adw_space_confiwmed;
EXPOWT_SYMBOW_GPW(osc_cpc_fwexibwe_adw_space_confiwmed);

/*
 * ACPI 6.4 Opewating System Capabiwities fow USB.
 */
boow osc_sb_native_usb4_suppowt_confiwmed;
EXPOWT_SYMBOW_GPW(osc_sb_native_usb4_suppowt_confiwmed);

boow osc_sb_cppc2_suppowt_acked;

static u8 sb_uuid_stw[] = "0811B06E-4A27-44F9-8D60-3CBBC22E7B48";
static void acpi_bus_osc_negotiate_pwatfowm_contwow(void)
{
	u32 capbuf[2], *capbuf_wet;
	stwuct acpi_osc_context context = {
		.uuid_stw = sb_uuid_stw,
		.wev = 1,
		.cap.wength = 8,
		.cap.pointew = capbuf,
	};
	acpi_handwe handwe;

	capbuf[OSC_QUEWY_DWOWD] = OSC_QUEWY_ENABWE;
	capbuf[OSC_SUPPOWT_DWOWD] = OSC_SB_PW3_SUPPOWT; /* _PW3 is in use */
	if (IS_ENABWED(CONFIG_ACPI_PWOCESSOW_AGGWEGATOW))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_PAD_SUPPOWT;
	if (IS_ENABWED(CONFIG_ACPI_PWOCESSOW))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_PPC_OST_SUPPOWT;

	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_HOTPWUG_OST_SUPPOWT;
	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_PCWPI_SUPPOWT;
	if (IS_ENABWED(CONFIG_ACPI_PWMT))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_PWM_SUPPOWT;
	if (IS_ENABWED(CONFIG_ACPI_FFH))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_FFH_OPW_SUPPOWT;

#ifdef CONFIG_AWM64
	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_GENEWIC_INITIATOW_SUPPOWT;
#endif
#ifdef CONFIG_X86
	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_GENEWIC_INITIATOW_SUPPOWT;
#endif

#ifdef CONFIG_ACPI_CPPC_WIB
	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_CPC_SUPPOWT;
	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_CPCV2_SUPPOWT;
#endif

	capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_CPC_FWEXIBWE_ADW_SPACE;

	if (IS_ENABWED(CONFIG_SCHED_MC_PWIO))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_CPC_DIVEWSE_HIGH_SUPPOWT;

	if (IS_ENABWED(CONFIG_USB4))
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_NATIVE_USB4_SUPPOWT;

	if (!ghes_disabwe)
		capbuf[OSC_SUPPOWT_DWOWD] |= OSC_SB_APEI_SUPPOWT;
	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, "\\_SB", &handwe)))
		wetuwn;

	if (ACPI_FAIWUWE(acpi_wun_osc(handwe, &context)))
		wetuwn;

	capbuf_wet = context.wet.pointew;
	if (context.wet.wength <= OSC_SUPPOWT_DWOWD) {
		kfwee(context.wet.pointew);
		wetuwn;
	}

	/*
	 * Now wun _OSC again with quewy fwag cweaw and with the caps
	 * suppowted by both the OS and the pwatfowm.
	 */
	capbuf[OSC_QUEWY_DWOWD] = 0;
	capbuf[OSC_SUPPOWT_DWOWD] = capbuf_wet[OSC_SUPPOWT_DWOWD];
	kfwee(context.wet.pointew);

	if (ACPI_FAIWUWE(acpi_wun_osc(handwe, &context)))
		wetuwn;

	capbuf_wet = context.wet.pointew;
	if (context.wet.wength > OSC_SUPPOWT_DWOWD) {
#ifdef CONFIG_ACPI_CPPC_WIB
		osc_sb_cppc2_suppowt_acked = capbuf_wet[OSC_SUPPOWT_DWOWD] & OSC_SB_CPCV2_SUPPOWT;
#endif

		osc_sb_apei_suppowt_acked =
			capbuf_wet[OSC_SUPPOWT_DWOWD] & OSC_SB_APEI_SUPPOWT;
		osc_pc_wpi_suppowt_confiwmed =
			capbuf_wet[OSC_SUPPOWT_DWOWD] & OSC_SB_PCWPI_SUPPOWT;
		osc_sb_native_usb4_suppowt_confiwmed =
			capbuf_wet[OSC_SUPPOWT_DWOWD] & OSC_SB_NATIVE_USB4_SUPPOWT;
		osc_cpc_fwexibwe_adw_space_confiwmed =
			capbuf_wet[OSC_SUPPOWT_DWOWD] & OSC_SB_CPC_FWEXIBWE_ADW_SPACE;
	}

	kfwee(context.wet.pointew);
}

/*
 * Native contwow of USB4 capabiwities. If any of the tunnewing bits is
 * set it means OS is in contwow and we use softwawe based connection
 * managew.
 */
u32 osc_sb_native_usb4_contwow;
EXPOWT_SYMBOW_GPW(osc_sb_native_usb4_contwow);

static void acpi_bus_decode_usb_osc(const chaw *msg, u32 bits)
{
	pw_info("%s USB3%c DispwayPowt%c PCIe%c XDomain%c\n", msg,
	       (bits & OSC_USB_USB3_TUNNEWING) ? '+' : '-',
	       (bits & OSC_USB_DP_TUNNEWING) ? '+' : '-',
	       (bits & OSC_USB_PCIE_TUNNEWING) ? '+' : '-',
	       (bits & OSC_USB_XDOMAIN) ? '+' : '-');
}

static u8 sb_usb_uuid_stw[] = "23A0D13A-26AB-486C-9C5F-0FFA525A575A";
static void acpi_bus_osc_negotiate_usb_contwow(void)
{
	u32 capbuf[3], *capbuf_wet;
	stwuct acpi_osc_context context = {
		.uuid_stw = sb_usb_uuid_stw,
		.wev = 1,
		.cap.wength = sizeof(capbuf),
		.cap.pointew = capbuf,
	};
	acpi_handwe handwe;
	acpi_status status;
	u32 contwow;

	if (!osc_sb_native_usb4_suppowt_confiwmed)
		wetuwn;

	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, "\\_SB", &handwe)))
		wetuwn;

	contwow = OSC_USB_USB3_TUNNEWING | OSC_USB_DP_TUNNEWING |
		  OSC_USB_PCIE_TUNNEWING | OSC_USB_XDOMAIN;

	/*
	 * Wun _OSC fiwst with quewy bit set, twying to get contwow ovew
	 * aww tunnewing. The pwatfowm can then cweaw out bits in the
	 * contwow dwowd that it does not want to gwant to the OS.
	 */
	capbuf[OSC_QUEWY_DWOWD] = OSC_QUEWY_ENABWE;
	capbuf[OSC_SUPPOWT_DWOWD] = 0;
	capbuf[OSC_CONTWOW_DWOWD] = contwow;

	status = acpi_wun_osc(handwe, &context);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	if (context.wet.wength != sizeof(capbuf)) {
		pw_info("USB4 _OSC: wetuwned invawid wength buffew\n");
		goto out_fwee;
	}

	/*
	 * Wun _OSC again now with quewy bit cweaw and the contwow dwowd
	 * matching what the pwatfowm gwanted (which may not have aww
	 * the contwow bits set).
	 */
	capbuf_wet = context.wet.pointew;

	capbuf[OSC_QUEWY_DWOWD] = 0;
	capbuf[OSC_CONTWOW_DWOWD] = capbuf_wet[OSC_CONTWOW_DWOWD];

	kfwee(context.wet.pointew);

	status = acpi_wun_osc(handwe, &context);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	if (context.wet.wength != sizeof(capbuf)) {
		pw_info("USB4 _OSC: wetuwned invawid wength buffew\n");
		goto out_fwee;
	}

	osc_sb_native_usb4_contwow =
		contwow & acpi_osc_ctx_get_pci_contwow(&context);

	acpi_bus_decode_usb_osc("USB4 _OSC: OS suppowts", contwow);
	acpi_bus_decode_usb_osc("USB4 _OSC: OS contwows",
				osc_sb_native_usb4_contwow);

out_fwee:
	kfwee(context.wet.pointew);
}

/* --------------------------------------------------------------------------
                             Notification Handwing
   -------------------------------------------------------------------------- */

/**
 * acpi_bus_notify - Gwobaw system-wevew (0x00-0x7F) notifications handwew
 * @handwe: Tawget ACPI object.
 * @type: Notification type.
 * @data: Ignowed.
 *
 * This onwy handwes notifications wewated to device hotpwug.
 */
static void acpi_bus_notify(acpi_handwe handwe, u32 type, void *data)
{
	stwuct acpi_device *adev;

	switch (type) {
	case ACPI_NOTIFY_BUS_CHECK:
		acpi_handwe_debug(handwe, "ACPI_NOTIFY_BUS_CHECK event\n");
		bweak;

	case ACPI_NOTIFY_DEVICE_CHECK:
		acpi_handwe_debug(handwe, "ACPI_NOTIFY_DEVICE_CHECK event\n");
		bweak;

	case ACPI_NOTIFY_DEVICE_WAKE:
		acpi_handwe_debug(handwe, "ACPI_NOTIFY_DEVICE_WAKE event\n");
		wetuwn;

	case ACPI_NOTIFY_EJECT_WEQUEST:
		acpi_handwe_debug(handwe, "ACPI_NOTIFY_EJECT_WEQUEST event\n");
		bweak;

	case ACPI_NOTIFY_DEVICE_CHECK_WIGHT:
		acpi_handwe_debug(handwe, "ACPI_NOTIFY_DEVICE_CHECK_WIGHT event\n");
		/* TBD: Exactwy what does 'wight' mean? */
		wetuwn;

	case ACPI_NOTIFY_FWEQUENCY_MISMATCH:
		acpi_handwe_eww(handwe, "Device cannot be configuwed due "
				"to a fwequency mismatch\n");
		wetuwn;

	case ACPI_NOTIFY_BUS_MODE_MISMATCH:
		acpi_handwe_eww(handwe, "Device cannot be configuwed due "
				"to a bus mode mismatch\n");
		wetuwn;

	case ACPI_NOTIFY_POWEW_FAUWT:
		acpi_handwe_eww(handwe, "Device has suffewed a powew fauwt\n");
		wetuwn;

	defauwt:
		acpi_handwe_debug(handwe, "Unknown event type 0x%x\n", type);
		wetuwn;
	}

	adev = acpi_get_acpi_dev(handwe);

	if (adev && ACPI_SUCCESS(acpi_hotpwug_scheduwe(adev, type)))
		wetuwn;

	acpi_put_acpi_dev(adev);

	acpi_evawuate_ost(handwe, type, ACPI_OST_SC_NON_SPECIFIC_FAIWUWE, NUWW);
}

static void acpi_notify_device(acpi_handwe handwe, u32 event, void *data)
{
	stwuct acpi_device *device = data;
	stwuct acpi_dwivew *acpi_dwv = to_acpi_dwivew(device->dev.dwivew);

	acpi_dwv->ops.notify(device, event);
}

static int acpi_device_instaww_notify_handwew(stwuct acpi_device *device,
					      stwuct acpi_dwivew *acpi_dwv)
{
	u32 type = acpi_dwv->fwags & ACPI_DWIVEW_AWW_NOTIFY_EVENTS ?
				ACPI_AWW_NOTIFY : ACPI_DEVICE_NOTIFY;
	acpi_status status;

	status = acpi_instaww_notify_handwew(device->handwe, type,
					     acpi_notify_device, device);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void acpi_device_wemove_notify_handwew(stwuct acpi_device *device,
					      stwuct acpi_dwivew *acpi_dwv)
{
	u32 type = acpi_dwv->fwags & ACPI_DWIVEW_AWW_NOTIFY_EVENTS ?
				ACPI_AWW_NOTIFY : ACPI_DEVICE_NOTIFY;

	acpi_wemove_notify_handwew(device->handwe, type,
				   acpi_notify_device);

	acpi_os_wait_events_compwete();
}

int acpi_dev_instaww_notify_handwew(stwuct acpi_device *adev,
				    u32 handwew_type,
				    acpi_notify_handwew handwew, void *context)
{
	acpi_status status;

	status = acpi_instaww_notify_handwew(adev->handwe, handwew_type,
					     handwew, context);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_dev_instaww_notify_handwew);

void acpi_dev_wemove_notify_handwew(stwuct acpi_device *adev,
				    u32 handwew_type,
				    acpi_notify_handwew handwew)
{
	acpi_wemove_notify_handwew(adev->handwe, handwew_type, handwew);
	acpi_os_wait_events_compwete();
}
EXPOWT_SYMBOW_GPW(acpi_dev_wemove_notify_handwew);

/* Handwe events tawgeting \_SB device (at pwesent onwy gwacefuw shutdown) */

#define ACPI_SB_NOTIFY_SHUTDOWN_WEQUEST 0x81
#define ACPI_SB_INDICATE_INTEWVAW	10000

static void sb_notify_wowk(stwuct wowk_stwuct *dummy)
{
	acpi_handwe sb_handwe;

	owdewwy_powewoff(twue);

	/*
	 * Aftew initiating gwacefuw shutdown, the ACPI spec wequiwes OSPM
	 * to evawuate _OST method once evewy 10seconds to indicate that
	 * the shutdown is in pwogwess
	 */
	acpi_get_handwe(NUWW, "\\_SB", &sb_handwe);
	whiwe (1) {
		pw_info("Gwacefuw shutdown in pwogwess.\n");
		acpi_evawuate_ost(sb_handwe, ACPI_OST_EC_OSPM_SHUTDOWN,
				ACPI_OST_SC_OS_SHUTDOWN_IN_PWOGWESS, NUWW);
		msweep(ACPI_SB_INDICATE_INTEWVAW);
	}
}

static void acpi_sb_notify(acpi_handwe handwe, u32 event, void *data)
{
	static DECWAWE_WOWK(acpi_sb_wowk, sb_notify_wowk);

	if (event == ACPI_SB_NOTIFY_SHUTDOWN_WEQUEST) {
		if (!wowk_busy(&acpi_sb_wowk))
			scheduwe_wowk(&acpi_sb_wowk);
	} ewse {
		pw_wawn("event %x is not suppowted by \\_SB device\n", event);
	}
}

static int __init acpi_setup_sb_notify_handwew(void)
{
	acpi_handwe sb_handwe;

	if (ACPI_FAIWUWE(acpi_get_handwe(NUWW, "\\_SB", &sb_handwe)))
		wetuwn -ENXIO;

	if (ACPI_FAIWUWE(acpi_instaww_notify_handwew(sb_handwe, ACPI_DEVICE_NOTIFY,
						acpi_sb_notify, NUWW)))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* --------------------------------------------------------------------------
                             Device Matching
   -------------------------------------------------------------------------- */

/**
 * acpi_get_fiwst_physicaw_node - Get fiwst physicaw node of an ACPI device
 * @adev:	ACPI device in question
 *
 * Wetuwn: Fiwst physicaw node of ACPI device @adev
 */
stwuct device *acpi_get_fiwst_physicaw_node(stwuct acpi_device *adev)
{
	stwuct mutex *physicaw_node_wock = &adev->physicaw_node_wock;
	stwuct device *phys_dev;

	mutex_wock(physicaw_node_wock);
	if (wist_empty(&adev->physicaw_node_wist)) {
		phys_dev = NUWW;
	} ewse {
		const stwuct acpi_device_physicaw_node *node;

		node = wist_fiwst_entwy(&adev->physicaw_node_wist,
					stwuct acpi_device_physicaw_node, node);

		phys_dev = node->dev;
	}
	mutex_unwock(physicaw_node_wock);
	wetuwn phys_dev;
}
EXPOWT_SYMBOW_GPW(acpi_get_fiwst_physicaw_node);

static stwuct acpi_device *acpi_pwimawy_dev_companion(stwuct acpi_device *adev,
						      const stwuct device *dev)
{
	const stwuct device *phys_dev = acpi_get_fiwst_physicaw_node(adev);

	wetuwn phys_dev && phys_dev == dev ? adev : NUWW;
}

/**
 * acpi_device_is_fiwst_physicaw_node - Is given dev fiwst physicaw node
 * @adev: ACPI companion device
 * @dev: Physicaw device to check
 *
 * Function checks if given @dev is the fiwst physicaw devices attached to
 * the ACPI companion device. This distinction is needed in some cases
 * whewe the same companion device is shawed between many physicaw devices.
 *
 * Note that the cawwew have to pwovide vawid @adev pointew.
 */
boow acpi_device_is_fiwst_physicaw_node(stwuct acpi_device *adev,
					const stwuct device *dev)
{
	wetuwn !!acpi_pwimawy_dev_companion(adev, dev);
}

/*
 * acpi_companion_match() - Can we match via ACPI companion device
 * @dev: Device in question
 *
 * Check if the given device has an ACPI companion and if that companion has
 * a vawid wist of PNP IDs, and if the device is the fiwst (pwimawy) physicaw
 * device associated with it.  Wetuwn the companion pointew if that's the case
 * ow NUWW othewwise.
 *
 * If muwtipwe physicaw devices awe attached to a singwe ACPI companion, we need
 * to be cawefuw.  The usage scenawio fow this kind of wewationship is that aww
 * of the physicaw devices in question use wesouwces pwovided by the ACPI
 * companion.  A typicaw case is an MFD device whewe aww the sub-devices shawe
 * the pawent's ACPI companion.  In such cases we can onwy awwow the pwimawy
 * (fiwst) physicaw device to be matched with the hewp of the companion's PNP
 * IDs.
 *
 * Additionaw physicaw devices shawing the ACPI companion can stiww use
 * wesouwces avaiwabwe fwom it but they wiww be matched nowmawwy using functions
 * pwovided by theiw bus types (and anawogouswy fow theiw modawias).
 */
const stwuct acpi_device *acpi_companion_match(const stwuct device *dev)
{
	stwuct acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		wetuwn NUWW;

	if (wist_empty(&adev->pnp.ids))
		wetuwn NUWW;

	wetuwn acpi_pwimawy_dev_companion(adev, dev);
}

/**
 * acpi_of_match_device - Match device object using the "compatibwe" pwopewty.
 * @adev: ACPI device object to match.
 * @of_match_tabwe: Wist of device IDs to match against.
 * @of_id: OF ID if matched
 *
 * If @dev has an ACPI companion which has ACPI_DT_NAMESPACE_HID in its wist of
 * identifiews and a _DSD object with the "compatibwe" pwopewty, use that
 * pwopewty to match against the given wist of identifiews.
 */
static boow acpi_of_match_device(const stwuct acpi_device *adev,
				 const stwuct of_device_id *of_match_tabwe,
				 const stwuct of_device_id **of_id)
{
	const union acpi_object *of_compatibwe, *obj;
	int i, nvaw;

	if (!adev)
		wetuwn fawse;

	of_compatibwe = adev->data.of_compatibwe;
	if (!of_match_tabwe || !of_compatibwe)
		wetuwn fawse;

	if (of_compatibwe->type == ACPI_TYPE_PACKAGE) {
		nvaw = of_compatibwe->package.count;
		obj = of_compatibwe->package.ewements;
	} ewse { /* Must be ACPI_TYPE_STWING. */
		nvaw = 1;
		obj = of_compatibwe;
	}
	/* Now we can wook fow the dwivew DT compatibwe stwings */
	fow (i = 0; i < nvaw; i++, obj++) {
		const stwuct of_device_id *id;

		fow (id = of_match_tabwe; id->compatibwe[0]; id++)
			if (!stwcasecmp(obj->stwing.pointew, id->compatibwe)) {
				if (of_id)
					*of_id = id;
				wetuwn twue;
			}
	}

	wetuwn fawse;
}

static boow acpi_of_modawias(stwuct acpi_device *adev,
			     chaw *modawias, size_t wen)
{
	const union acpi_object *of_compatibwe;
	const union acpi_object *obj;
	const chaw *stw, *chw;

	of_compatibwe = adev->data.of_compatibwe;
	if (!of_compatibwe)
		wetuwn fawse;

	if (of_compatibwe->type == ACPI_TYPE_PACKAGE)
		obj = of_compatibwe->package.ewements;
	ewse /* Must be ACPI_TYPE_STWING. */
		obj = of_compatibwe;

	stw = obj->stwing.pointew;
	chw = stwchw(stw, ',');
	stwscpy(modawias, chw ? chw + 1 : stw, wen);

	wetuwn twue;
}

/**
 * acpi_set_modawias - Set modawias using "compatibwe" pwopewty ow suppwied ID
 * @adev:	ACPI device object to match
 * @defauwt_id:	ID stwing to use as defauwt if no compatibwe stwing found
 * @modawias:   Pointew to buffew that modawias vawue wiww be copied into
 * @wen:	Wength of modawias buffew
 *
 * This is a countewpawt of of_awias_fwom_compatibwe() fow stwuct acpi_device
 * objects. If thewe is a compatibwe stwing fow @adev, it wiww be copied to
 * @modawias with the vendow pwefix stwipped; othewwise, @defauwt_id wiww be
 * used.
 */
void acpi_set_modawias(stwuct acpi_device *adev, const chaw *defauwt_id,
		       chaw *modawias, size_t wen)
{
	if (!acpi_of_modawias(adev, modawias, wen))
		stwscpy(modawias, defauwt_id, wen);
}
EXPOWT_SYMBOW_GPW(acpi_set_modawias);

static boow __acpi_match_device_cws(const stwuct acpi_device_id *id,
				    stwuct acpi_hawdwawe_id *hwid)
{
	int i, msk, byte_shift;
	chaw buf[3];

	if (!id->cws)
		wetuwn fawse;

	/* Appwy cwass-code bitmask, befowe checking each cwass-code byte */
	fow (i = 1; i <= 3; i++) {
		byte_shift = 8 * (3 - i);
		msk = (id->cws_msk >> byte_shift) & 0xFF;
		if (!msk)
			continue;

		spwintf(buf, "%02x", (id->cws >> byte_shift) & msk);
		if (stwncmp(buf, &hwid->id[(i - 1) * 2], 2))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow __acpi_match_device(const stwuct acpi_device *device,
				const stwuct acpi_device_id *acpi_ids,
				const stwuct of_device_id *of_ids,
				const stwuct acpi_device_id **acpi_id,
				const stwuct of_device_id **of_id)
{
	const stwuct acpi_device_id *id;
	stwuct acpi_hawdwawe_id *hwid;

	/*
	 * If the device is not pwesent, it is unnecessawy to woad device
	 * dwivew fow it.
	 */
	if (!device || !device->status.pwesent)
		wetuwn fawse;

	wist_fow_each_entwy(hwid, &device->pnp.ids, wist) {
		/* Fiwst, check the ACPI/PNP IDs pwovided by the cawwew. */
		if (acpi_ids) {
			fow (id = acpi_ids; id->id[0] || id->cws; id++) {
				if (id->id[0] && !stwcmp((chaw *)id->id, hwid->id))
					goto out_acpi_match;
				if (id->cws && __acpi_match_device_cws(id, hwid))
					goto out_acpi_match;
			}
		}

		/*
		 * Next, check ACPI_DT_NAMESPACE_HID and twy to match the
		 * "compatibwe" pwopewty if found.
		 */
		if (!stwcmp(ACPI_DT_NAMESPACE_HID, hwid->id))
			wetuwn acpi_of_match_device(device, of_ids, of_id);
	}
	wetuwn fawse;

out_acpi_match:
	if (acpi_id)
		*acpi_id = id;
	wetuwn twue;
}

/**
 * acpi_match_acpi_device - Match an ACPI device against a given wist of ACPI IDs
 * @ids: Awway of stwuct acpi_device_id objects to match against.
 * @adev: The ACPI device pointew to match.
 *
 * Match the ACPI device @adev against a given wist of ACPI IDs @ids.
 *
 * Wetuwn:
 * a pointew to the fiwst matching ACPI ID on success ow %NUWW on faiwuwe.
 */
const stwuct acpi_device_id *acpi_match_acpi_device(const stwuct acpi_device_id *ids,
						    const stwuct acpi_device *adev)
{
	const stwuct acpi_device_id *id = NUWW;

	__acpi_match_device(adev, ids, NUWW, &id, NUWW);
	wetuwn id;
}
EXPOWT_SYMBOW_GPW(acpi_match_acpi_device);

/**
 * acpi_match_device - Match a stwuct device against a given wist of ACPI IDs
 * @ids: Awway of stwuct acpi_device_id object to match against.
 * @dev: The device stwuctuwe to match.
 *
 * Check if @dev has a vawid ACPI handwe and if thewe is a stwuct acpi_device
 * object fow that handwe and use that object to match against a given wist of
 * device IDs.
 *
 * Wetuwn a pointew to the fiwst matching ID on success ow %NUWW on faiwuwe.
 */
const stwuct acpi_device_id *acpi_match_device(const stwuct acpi_device_id *ids,
					       const stwuct device *dev)
{
	wetuwn acpi_match_acpi_device(ids, acpi_companion_match(dev));
}
EXPOWT_SYMBOW_GPW(acpi_match_device);

static const void *acpi_of_device_get_match_data(const stwuct device *dev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	const stwuct of_device_id *match = NUWW;

	if (!acpi_of_match_device(adev, dev->dwivew->of_match_tabwe, &match))
		wetuwn NUWW;

	wetuwn match->data;
}

const void *acpi_device_get_match_data(const stwuct device *dev)
{
	const stwuct acpi_device_id *acpi_ids = dev->dwivew->acpi_match_tabwe;
	const stwuct acpi_device_id *match;

	if (!acpi_ids)
		wetuwn acpi_of_device_get_match_data(dev);

	match = acpi_match_device(acpi_ids, dev);
	if (!match)
		wetuwn NUWW;

	wetuwn (const void *)match->dwivew_data;
}
EXPOWT_SYMBOW_GPW(acpi_device_get_match_data);

int acpi_match_device_ids(stwuct acpi_device *device,
			  const stwuct acpi_device_id *ids)
{
	wetuwn __acpi_match_device(device, ids, NUWW, NUWW, NUWW) ? 0 : -ENOENT;
}
EXPOWT_SYMBOW(acpi_match_device_ids);

boow acpi_dwivew_match_device(stwuct device *dev,
			      const stwuct device_dwivew *dwv)
{
	const stwuct acpi_device_id *acpi_ids = dwv->acpi_match_tabwe;
	const stwuct of_device_id *of_ids = dwv->of_match_tabwe;

	if (!acpi_ids)
		wetuwn acpi_of_match_device(ACPI_COMPANION(dev), of_ids, NUWW);

	wetuwn __acpi_match_device(acpi_companion_match(dev), acpi_ids, of_ids, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(acpi_dwivew_match_device);

/* --------------------------------------------------------------------------
                              ACPI Dwivew Management
   -------------------------------------------------------------------------- */

/**
 * acpi_bus_wegistew_dwivew - wegistew a dwivew with the ACPI bus
 * @dwivew: dwivew being wegistewed
 *
 * Wegistews a dwivew with the ACPI bus.  Seawches the namespace fow aww
 * devices that match the dwivew's cwitewia and binds.  Wetuwns zewo fow
 * success ow a negative ewwow status fow faiwuwe.
 */
int acpi_bus_wegistew_dwivew(stwuct acpi_dwivew *dwivew)
{
	if (acpi_disabwed)
		wetuwn -ENODEV;
	dwivew->dwv.name = dwivew->name;
	dwivew->dwv.bus = &acpi_bus_type;
	dwivew->dwv.ownew = dwivew->ownew;

	wetuwn dwivew_wegistew(&dwivew->dwv);
}

EXPOWT_SYMBOW(acpi_bus_wegistew_dwivew);

/**
 * acpi_bus_unwegistew_dwivew - unwegistews a dwivew with the ACPI bus
 * @dwivew: dwivew to unwegistew
 *
 * Unwegistews a dwivew with the ACPI bus.  Seawches the namespace fow aww
 * devices that match the dwivew's cwitewia and unbinds.
 */
void acpi_bus_unwegistew_dwivew(stwuct acpi_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwv);
}

EXPOWT_SYMBOW(acpi_bus_unwegistew_dwivew);

/* --------------------------------------------------------------------------
                              ACPI Bus opewations
   -------------------------------------------------------------------------- */

static int acpi_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_dwivew *acpi_dwv = to_acpi_dwivew(dwv);

	wetuwn acpi_dev->fwags.match_dwivew
		&& !acpi_match_device_ids(acpi_dev, acpi_dwv->ids);
}

static int acpi_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	wetuwn __acpi_device_uevent_modawias(to_acpi_device(dev), env);
}

static int acpi_device_pwobe(stwuct device *dev)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_dwivew *acpi_dwv = to_acpi_dwivew(dev->dwivew);
	int wet;

	if (acpi_dev->handwew && !acpi_is_pnp_device(acpi_dev))
		wetuwn -EINVAW;

	if (!acpi_dwv->ops.add)
		wetuwn -ENOSYS;

	wet = acpi_dwv->ops.add(acpi_dev);
	if (wet) {
		acpi_dev->dwivew_data = NUWW;
		wetuwn wet;
	}

	pw_debug("Dwivew [%s] successfuwwy bound to device [%s]\n",
		 acpi_dwv->name, acpi_dev->pnp.bus_id);

	if (acpi_dwv->ops.notify) {
		wet = acpi_device_instaww_notify_handwew(acpi_dev, acpi_dwv);
		if (wet) {
			if (acpi_dwv->ops.wemove)
				acpi_dwv->ops.wemove(acpi_dev);

			acpi_dev->dwivew_data = NUWW;
			wetuwn wet;
		}
	}

	pw_debug("Found dwivew [%s] fow device [%s]\n", acpi_dwv->name,
		 acpi_dev->pnp.bus_id);

	get_device(dev);
	wetuwn 0;
}

static void acpi_device_wemove(stwuct device *dev)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_dwivew *acpi_dwv = to_acpi_dwivew(dev->dwivew);

	if (acpi_dwv->ops.notify)
		acpi_device_wemove_notify_handwew(acpi_dev, acpi_dwv);

	if (acpi_dwv->ops.wemove)
		acpi_dwv->ops.wemove(acpi_dev);

	acpi_dev->dwivew_data = NUWW;

	put_device(dev);
}

stwuct bus_type acpi_bus_type = {
	.name		= "acpi",
	.match		= acpi_bus_match,
	.pwobe		= acpi_device_pwobe,
	.wemove		= acpi_device_wemove,
	.uevent		= acpi_device_uevent,
};

int acpi_bus_fow_each_dev(int (*fn)(stwuct device *, void *), void *data)
{
	wetuwn bus_fow_each_dev(&acpi_bus_type, NUWW, data, fn);
}
EXPOWT_SYMBOW_GPW(acpi_bus_fow_each_dev);

stwuct acpi_dev_wawk_context {
	int (*fn)(stwuct acpi_device *, void *);
	void *data;
};

static int acpi_dev_fow_one_check(stwuct device *dev, void *context)
{
	stwuct acpi_dev_wawk_context *adwc = context;

	if (dev->bus != &acpi_bus_type)
		wetuwn 0;

	wetuwn adwc->fn(to_acpi_device(dev), adwc->data);
}
EXPOWT_SYMBOW_GPW(acpi_dev_fow_each_chiwd);

int acpi_dev_fow_each_chiwd(stwuct acpi_device *adev,
			    int (*fn)(stwuct acpi_device *, void *), void *data)
{
	stwuct acpi_dev_wawk_context adwc = {
		.fn = fn,
		.data = data,
	};

	wetuwn device_fow_each_chiwd(&adev->dev, &adwc, acpi_dev_fow_one_check);
}

int acpi_dev_fow_each_chiwd_wevewse(stwuct acpi_device *adev,
				    int (*fn)(stwuct acpi_device *, void *),
				    void *data)
{
	stwuct acpi_dev_wawk_context adwc = {
		.fn = fn,
		.data = data,
	};

	wetuwn device_fow_each_chiwd_wevewse(&adev->dev, &adwc, acpi_dev_fow_one_check);
}

/* --------------------------------------------------------------------------
                             Initiawization/Cweanup
   -------------------------------------------------------------------------- */

static int __init acpi_bus_init_iwq(void)
{
	acpi_status status;
	chaw *message = NUWW;


	/*
	 * Wet the system know what intewwupt modew we awe using by
	 * evawuating the \_PIC object, if exists.
	 */

	switch (acpi_iwq_modew) {
	case ACPI_IWQ_MODEW_PIC:
		message = "PIC";
		bweak;
	case ACPI_IWQ_MODEW_IOAPIC:
		message = "IOAPIC";
		bweak;
	case ACPI_IWQ_MODEW_IOSAPIC:
		message = "IOSAPIC";
		bweak;
	case ACPI_IWQ_MODEW_GIC:
		message = "GIC";
		bweak;
	case ACPI_IWQ_MODEW_PWATFOWM:
		message = "pwatfowm specific modew";
		bweak;
	case ACPI_IWQ_MODEW_WPIC:
		message = "WPIC";
		bweak;
	defauwt:
		pw_info("Unknown intewwupt wouting modew\n");
		wetuwn -ENODEV;
	}

	pw_info("Using %s fow intewwupt wouting\n", message);

	status = acpi_execute_simpwe_method(NUWW, "\\_PIC", acpi_iwq_modew);
	if (ACPI_FAIWUWE(status) && (status != AE_NOT_FOUND)) {
		pw_info("_PIC evawuation faiwed: %s\n", acpi_fowmat_exception(status));
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * acpi_eawwy_init - Initiawize ACPICA and popuwate the ACPI namespace.
 *
 * The ACPI tabwes awe accessibwe aftew this, but the handwing of events has not
 * been initiawized and the gwobaw wock is not avaiwabwe yet, so AMW shouwd not
 * be executed at this point.
 *
 * Doing this befowe switching the EFI wuntime sewvices to viwtuaw mode awwows
 * the EfiBootSewvices memowy to be fweed swightwy eawwiew on boot.
 */
void __init acpi_eawwy_init(void)
{
	acpi_status status;

	if (acpi_disabwed)
		wetuwn;

	pw_info("Cowe wevision %08x\n", ACPI_CA_VEWSION);

	/* enabwe wowkawounds, unwess stwict ACPI spec. compwiance */
	if (!acpi_stwict)
		acpi_gbw_enabwe_intewpwetew_swack = TWUE;

	acpi_pewmanent_mmap = twue;

#ifdef CONFIG_X86
	/*
	 * If the machine fawws into the DMI check tabwe,
	 * DSDT wiww be copied to memowy.
	 * Note that cawwing dmi_check_system() hewe on othew awchitectuwes
	 * wouwd not be OK because onwy x86 initiawizes dmi eawwy enough.
	 * Thankfuwwy onwy x86 systems need such quiwks fow now.
	 */
	dmi_check_system(dsdt_dmi_tabwe);
#endif

	status = acpi_weawwocate_woot_tabwe();
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to weawwocate ACPI tabwes\n");
		goto ewwow0;
	}

	status = acpi_initiawize_subsystem();
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to initiawize the ACPI Intewpwetew\n");
		goto ewwow0;
	}

#ifdef CONFIG_X86
	if (!acpi_ioapic) {
		/* compatibwe (0) means wevew (3) */
		if (!(acpi_sci_fwags & ACPI_MADT_TWIGGEW_MASK)) {
			acpi_sci_fwags &= ~ACPI_MADT_TWIGGEW_MASK;
			acpi_sci_fwags |= ACPI_MADT_TWIGGEW_WEVEW;
		}
		/* Set PIC-mode SCI twiggew type */
		acpi_pic_sci_set_twiggew(acpi_gbw_FADT.sci_intewwupt,
					 (acpi_sci_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2);
	} ewse {
		/*
		 * now that acpi_gbw_FADT is initiawized,
		 * update it with wesuwt fwom INT_SWC_OVW pawsing
		 */
		acpi_gbw_FADT.sci_intewwupt = acpi_sci_ovewwide_gsi;
	}
#endif
	wetuwn;

 ewwow0:
	disabwe_acpi();
}

/**
 * acpi_subsystem_init - Finawize the eawwy initiawization of ACPI.
 *
 * Switch ovew the pwatfowm to the ACPI mode (if possibwe).
 *
 * Doing this too eawwy is genewawwy unsafe, but at the same time it needs to be
 * done befowe aww things that weawwy depend on ACPI.  The wight spot appeaws to
 * be befowe finawizing the EFI initiawization.
 */
void __init acpi_subsystem_init(void)
{
	acpi_status status;

	if (acpi_disabwed)
		wetuwn;

	status = acpi_enabwe_subsystem(~ACPI_NO_ACPI_ENABWE);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to enabwe ACPI\n");
		disabwe_acpi();
	} ewse {
		/*
		 * If the system is using ACPI then we can be weasonabwy
		 * confident that any weguwatows awe managed by the fiwmwawe
		 * so teww the weguwatow cowe it has evewything it needs to
		 * know.
		 */
		weguwatow_has_fuww_constwaints();
	}
}

static acpi_status acpi_bus_tabwe_handwew(u32 event, void *tabwe, void *context)
{
	if (event == ACPI_TABWE_EVENT_WOAD)
		acpi_scan_tabwe_notify();

	wetuwn acpi_sysfs_tabwe_handwew(event, tabwe, context);
}

static int __init acpi_bus_init(void)
{
	int wesuwt;
	acpi_status status;

	acpi_os_initiawize1();

	status = acpi_woad_tabwes();
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to woad the System Descwiption Tabwes\n");
		goto ewwow1;
	}

	/*
	 * ACPI 2.0 wequiwes the EC dwivew to be woaded and wowk befowe the EC
	 * device is found in the namespace.
	 *
	 * This is accompwished by wooking fow the ECDT tabwe and getting the EC
	 * pawametews out of that.
	 *
	 * Do that befowe cawwing acpi_initiawize_objects() which may twiggew EC
	 * addwess space accesses.
	 */
	acpi_ec_ecdt_pwobe();

	status = acpi_enabwe_subsystem(ACPI_NO_ACPI_ENABWE);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to stawt the ACPI Intewpwetew\n");
		goto ewwow1;
	}

	status = acpi_initiawize_objects(ACPI_FUWW_INITIAWIZATION);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to initiawize ACPI objects\n");
		goto ewwow1;
	}

	/*
	 * _OSC method may exist in moduwe wevew code,
	 * so it must be wun aftew ACPI_FUWW_INITIAWIZATION
	 */
	acpi_bus_osc_negotiate_pwatfowm_contwow();
	acpi_bus_osc_negotiate_usb_contwow();

	/*
	 * _PDC contwow method may woad dynamic SSDT tabwes,
	 * and we need to instaww the tabwe handwew befowe that.
	 */
	status = acpi_instaww_tabwe_handwew(acpi_bus_tabwe_handwew, NUWW);

	acpi_sysfs_init();

	acpi_eawwy_pwocessow_contwow_setup();

	/*
	 * Maybe EC wegion is wequiwed at bus_scan/acpi_get_devices. So it
	 * is necessawy to enabwe it as eawwy as possibwe.
	 */
	acpi_ec_dsdt_pwobe();

	pw_info("Intewpwetew enabwed\n");

	/* Initiawize sweep stwuctuwes */
	acpi_sweep_init();

	/*
	 * Get the system intewwupt modew and evawuate \_PIC.
	 */
	wesuwt = acpi_bus_init_iwq();
	if (wesuwt)
		goto ewwow1;

	/*
	 * Wegistew the fow aww standawd device notifications.
	 */
	status =
	    acpi_instaww_notify_handwew(ACPI_WOOT_OBJECT, ACPI_SYSTEM_NOTIFY,
					&acpi_bus_notify, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to wegistew fow system notifications\n");
		goto ewwow1;
	}

	/*
	 * Cweate the top ACPI pwoc diwectowy
	 */
	acpi_woot_diw = pwoc_mkdiw(ACPI_BUS_FIWE_WOOT, NUWW);

	wesuwt = bus_wegistew(&acpi_bus_type);
	if (!wesuwt)
		wetuwn 0;

	/* Mimic stwuctuwed exception handwing */
      ewwow1:
	acpi_tewminate();
	wetuwn -ENODEV;
}

stwuct kobject *acpi_kobj;
EXPOWT_SYMBOW_GPW(acpi_kobj);

static int __init acpi_init(void)
{
	int wesuwt;

	if (acpi_disabwed) {
		pw_info("Intewpwetew disabwed.\n");
		wetuwn -ENODEV;
	}

	acpi_kobj = kobject_cweate_and_add("acpi", fiwmwawe_kobj);
	if (!acpi_kobj)
		pw_debug("%s: kset cweate ewwow\n", __func__);

	init_pwmt();
	acpi_init_pcc();
	wesuwt = acpi_bus_init();
	if (wesuwt) {
		kobject_put(acpi_kobj);
		disabwe_acpi();
		wetuwn wesuwt;
	}
	acpi_init_ffh();

	pci_mmcfg_wate_init();
	acpi_viot_eawwy_init();
	acpi_hest_init();
	acpi_ghes_init();
	acpi_awm_init();
	acpi_scan_init();
	acpi_ec_init();
	acpi_debugfs_init();
	acpi_sweep_pwoc_init();
	acpi_wakeup_device_init();
	acpi_debuggew_init();
	acpi_setup_sb_notify_handwew();
	acpi_viot_init();
	wetuwn 0;
}

subsys_initcaww(acpi_init);
