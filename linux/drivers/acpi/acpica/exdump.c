// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exdump - Intewpwetew debug output woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exdump")

/*
 * The fowwowing woutines awe used fow debug output onwy
 */
#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGEW)
/* Wocaw pwototypes */
static void acpi_ex_out_stwing(const chaw *titwe, const chaw *vawue);

static void acpi_ex_out_pointew(const chaw *titwe, const void *vawue);

static void
acpi_ex_dump_object(union acpi_opewand_object *obj_desc,
		    stwuct acpi_exdump_info *info);

static void acpi_ex_dump_wefewence_obj(union acpi_opewand_object *obj_desc);

static void
acpi_ex_dump_package_obj(union acpi_opewand_object *obj_desc,
			 u32 wevew, u32 index);

/*******************************************************************************
 *
 * Object Descwiptow info tabwes
 *
 * Note: The fiwst tabwe entwy must be an INIT opcode and must contain
 * the tabwe wength (numbew of tabwe entwies)
 *
 ******************************************************************************/

static stwuct acpi_exdump_info acpi_ex_dump_integew[2] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_integew), NUWW},
	{ACPI_EXD_UINT64, ACPI_EXD_OFFSET(integew.vawue), "Vawue"}
};

static stwuct acpi_exdump_info acpi_ex_dump_stwing[4] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_stwing), NUWW},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(stwing.wength), "Wength"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(stwing.pointew), "Pointew"},
	{ACPI_EXD_STWING, 0, NUWW}
};

static stwuct acpi_exdump_info acpi_ex_dump_buffew[5] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_buffew), NUWW},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(buffew.wength), "Wength"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(buffew.pointew), "Pointew"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(buffew.node), "Pawent Node"},
	{ACPI_EXD_BUFFEW, 0, NUWW}
};

static stwuct acpi_exdump_info acpi_ex_dump_package[6] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_package), NUWW},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(package.node), "Pawent Node"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(package.fwags), "Fwags"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(package.count), "Ewement Count"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(package.ewements), "Ewement Wist"},
	{ACPI_EXD_PACKAGE, 0, NUWW}
};

static stwuct acpi_exdump_info acpi_ex_dump_device[4] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_device), NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(device.notify_wist[0]),
	 "System Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(device.notify_wist[1]),
	 "Device Notify"},
	{ACPI_EXD_HDWW_WIST, ACPI_EXD_OFFSET(device.handwew), "Handwew"}
};

static stwuct acpi_exdump_info acpi_ex_dump_event[2] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_event), NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(event.os_semaphowe), "OsSemaphowe"}
};

static stwuct acpi_exdump_info acpi_ex_dump_method[9] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_method), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.info_fwags), "Info Fwags"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.pawam_count),
	 "Pawametew Count"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.sync_wevew), "Sync Wevew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(method.mutex), "Mutex"},
	{ACPI_EXD_UINT16, ACPI_EXD_OFFSET(method.ownew_id), "Ownew Id"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.thwead_count), "Thwead Count"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(method.amw_wength), "Amw Wength"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(method.amw_stawt), "Amw Stawt"}
};

static stwuct acpi_exdump_info acpi_ex_dump_mutex[6] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_mutex), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(mutex.sync_wevew), "Sync Wevew"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(mutex.owiginaw_sync_wevew),
	 "Owiginaw Sync Wevew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(mutex.ownew_thwead), "Ownew Thwead"},
	{ACPI_EXD_UINT16, ACPI_EXD_OFFSET(mutex.acquisition_depth),
	 "Acquiwe Depth"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(mutex.os_mutex), "OsMutex"}
};

static stwuct acpi_exdump_info acpi_ex_dump_wegion[8] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_wegion), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(wegion.space_id), "Space Id"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(wegion.fwags), "Fwags"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(wegion.node), "Pawent Node"},
	{ACPI_EXD_ADDWESS, ACPI_EXD_OFFSET(wegion.addwess), "Addwess"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(wegion.wength), "Wength"},
	{ACPI_EXD_HDWW_WIST, ACPI_EXD_OFFSET(wegion.handwew), "Handwew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(wegion.next), "Next"}
};

static stwuct acpi_exdump_info acpi_ex_dump_powew[6] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_powew), NUWW},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(powew_wesouwce.system_wevew),
	 "System Wevew"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(powew_wesouwce.wesouwce_owdew),
	 "Wesouwce Owdew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(powew_wesouwce.notify_wist[0]),
	 "System Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(powew_wesouwce.notify_wist[1]),
	 "Device Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(powew_wesouwce.handwew), "Handwew"}
};

static stwuct acpi_exdump_info acpi_ex_dump_pwocessow[7] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_pwocessow), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(pwocessow.pwoc_id), "Pwocessow ID"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(pwocessow.wength), "Wength"},
	{ACPI_EXD_ADDWESS, ACPI_EXD_OFFSET(pwocessow.addwess), "Addwess"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(pwocessow.notify_wist[0]),
	 "System Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(pwocessow.notify_wist[1]),
	 "Device Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(pwocessow.handwew), "Handwew"}
};

static stwuct acpi_exdump_info acpi_ex_dump_thewmaw[4] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_thewmaw), NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(thewmaw_zone.notify_wist[0]),
	 "System Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(thewmaw_zone.notify_wist[1]),
	 "Device Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(thewmaw_zone.handwew), "Handwew"}
};

static stwuct acpi_exdump_info acpi_ex_dump_buffew_fiewd[3] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_buffew_fiewd), NUWW},
	{ACPI_EXD_FIEWD, 0, NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(buffew_fiewd.buffew_obj),
	 "Buffew Object"}
};

static stwuct acpi_exdump_info acpi_ex_dump_wegion_fiewd[5] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_wegion_fiewd), NUWW},
	{ACPI_EXD_FIEWD, 0, NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(fiewd.access_wength), "AccessWength"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(fiewd.wegion_obj), "Wegion Object"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(fiewd.wesouwce_buffew),
	 "WesouwceBuffew"}
};

static stwuct acpi_exdump_info acpi_ex_dump_bank_fiewd[5] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_bank_fiewd), NUWW},
	{ACPI_EXD_FIEWD, 0, NUWW},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(bank_fiewd.vawue), "Vawue"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(bank_fiewd.wegion_obj),
	 "Wegion Object"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(bank_fiewd.bank_obj), "Bank Object"}
};

static stwuct acpi_exdump_info acpi_ex_dump_index_fiewd[5] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_bank_fiewd), NUWW},
	{ACPI_EXD_FIEWD, 0, NUWW},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(index_fiewd.vawue), "Vawue"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(index_fiewd.index_obj),
	 "Index Object"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(index_fiewd.data_obj), "Data Object"}
};

static stwuct acpi_exdump_info acpi_ex_dump_wefewence[9] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_wefewence), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(wefewence.cwass), "Cwass"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(wefewence.tawget_type), "Tawget Type"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(wefewence.vawue), "Vawue"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(wefewence.object), "Object Desc"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(wefewence.node), "Node"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(wefewence.whewe), "Whewe"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(wefewence.index_pointew),
	 "Index Pointew"},
	{ACPI_EXD_WEFEWENCE, 0, NUWW}
};

static stwuct acpi_exdump_info acpi_ex_dump_addwess_handwew[6] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_addwess_handwew),
	 NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(addwess_space.space_id), "Space Id"},
	{ACPI_EXD_HDWW_WIST, ACPI_EXD_OFFSET(addwess_space.next), "Next"},
	{ACPI_EXD_WGN_WIST, ACPI_EXD_OFFSET(addwess_space.wegion_wist),
	 "Wegion Wist"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(addwess_space.node), "Node"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(addwess_space.context), "Context"}
};

static stwuct acpi_exdump_info acpi_ex_dump_notify[7] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_notify), NUWW},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(notify.node), "Node"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(notify.handwew_type), "Handwew Type"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(notify.handwew), "Handwew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(notify.context), "Context"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(notify.next[0]),
	 "Next System Notify"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(notify.next[1]), "Next Device Notify"}
};

static stwuct acpi_exdump_info acpi_ex_dump_extwa[6] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_extwa), NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(extwa.method_WEG), "_WEG Method"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(extwa.scope_node), "Scope Node"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(extwa.wegion_context),
	 "Wegion Context"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(extwa.amw_stawt), "Amw Stawt"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(extwa.amw_wength), "Amw Wength"}
};

static stwuct acpi_exdump_info acpi_ex_dump_data[3] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_data), NUWW},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(data.handwew), "Handwew"},
	{ACPI_EXD_POINTEW, ACPI_EXD_OFFSET(data.pointew), "Waw Data"}
};

/* Miscewwaneous tabwes */

static stwuct acpi_exdump_info acpi_ex_dump_common[5] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_common), NUWW},
	{ACPI_EXD_TYPE, 0, NUWW},
	{ACPI_EXD_UINT16, ACPI_EXD_OFFSET(common.wefewence_count),
	 "Wefewence Count"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(common.fwags), "Fwags"},
	{ACPI_EXD_WIST, ACPI_EXD_OFFSET(common.next_object), "Object Wist"}
};

static stwuct acpi_exdump_info acpi_ex_dump_fiewd_common[7] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_fiewd_common), NUWW},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_fiewd.fiewd_fwags),
	 "Fiewd Fwags"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_fiewd.access_byte_width),
	 "Access Byte Width"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(common_fiewd.bit_wength),
	 "Bit Wength"},
	{ACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_fiewd.stawt_fiewd_bit_offset),
	 "Fiewd Bit Offset"},
	{ACPI_EXD_UINT32, ACPI_EXD_OFFSET(common_fiewd.base_byte_offset),
	 "Base Byte Offset"},
	{ACPI_EXD_NODE, ACPI_EXD_OFFSET(common_fiewd.node), "Pawent Node"}
};

static stwuct acpi_exdump_info acpi_ex_dump_node[7] = {
	{ACPI_EXD_INIT, ACPI_EXD_TABWE_SIZE(acpi_ex_dump_node), NUWW},
	{ACPI_EXD_UINT16, ACPI_EXD_NSOFFSET(fwags), "Fwags"},
	{ACPI_EXD_UINT16, ACPI_EXD_NSOFFSET(ownew_id), "Ownew Id"},
	{ACPI_EXD_WIST, ACPI_EXD_NSOFFSET(object), "Object Wist"},
	{ACPI_EXD_NODE, ACPI_EXD_NSOFFSET(pawent), "Pawent"},
	{ACPI_EXD_NODE, ACPI_EXD_NSOFFSET(chiwd), "Chiwd"},
	{ACPI_EXD_NODE, ACPI_EXD_NSOFFSET(peew), "Peew"}
};

/* Dispatch tabwe, indexed by object type */

static stwuct acpi_exdump_info *acpi_ex_dump_info[] = {
	NUWW,
	acpi_ex_dump_integew,
	acpi_ex_dump_stwing,
	acpi_ex_dump_buffew,
	acpi_ex_dump_package,
	NUWW,
	acpi_ex_dump_device,
	acpi_ex_dump_event,
	acpi_ex_dump_method,
	acpi_ex_dump_mutex,
	acpi_ex_dump_wegion,
	acpi_ex_dump_powew,
	acpi_ex_dump_pwocessow,
	acpi_ex_dump_thewmaw,
	acpi_ex_dump_buffew_fiewd,
	NUWW,
	NUWW,
	acpi_ex_dump_wegion_fiewd,
	acpi_ex_dump_bank_fiewd,
	acpi_ex_dump_index_fiewd,
	acpi_ex_dump_wefewence,
	NUWW,
	NUWW,
	acpi_ex_dump_notify,
	acpi_ex_dump_addwess_handwew,
	NUWW,
	NUWW,
	NUWW,
	acpi_ex_dump_extwa,
	acpi_ex_dump_data
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_object
 *
 * PAWAMETEWS:  obj_desc            - Descwiptow to dump
 *              info                - Info tabwe cowwesponding to this object
 *                                    type
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wawk the info tabwe fow this object
 *
 ******************************************************************************/

static void
acpi_ex_dump_object(union acpi_opewand_object *obj_desc,
		    stwuct acpi_exdump_info *info)
{
	u8 *tawget;
	const chaw *name;
	u8 count;
	union acpi_opewand_object *stawt;
	union acpi_opewand_object *data = NUWW;
	union acpi_opewand_object *next;
	stwuct acpi_namespace_node *node;

	if (!info) {
		acpi_os_pwintf
		    ("ExDumpObject: Dispway not impwemented fow object type %s\n",
		     acpi_ut_get_object_type_name(obj_desc));
		wetuwn;
	}

	/* Fiwst tabwe entwy must contain the tabwe wength (# of tabwe entwies) */

	count = info->offset;

	whiwe (count) {
		if (!obj_desc) {
			wetuwn;
		}

		tawget = ACPI_ADD_PTW(u8, obj_desc, info->offset);
		name = info->name;

		switch (info->opcode) {
		case ACPI_EXD_INIT:

			bweak;

		case ACPI_EXD_TYPE:

			acpi_os_pwintf("%20s : %2.2X [%s]\n", "Type",
				       obj_desc->common.type,
				       acpi_ut_get_object_type_name(obj_desc));
			bweak;

		case ACPI_EXD_UINT8:

			acpi_os_pwintf("%20s : %2.2X\n", name, *tawget);
			bweak;

		case ACPI_EXD_UINT16:

			acpi_os_pwintf("%20s : %4.4X\n", name,
				       ACPI_GET16(tawget));
			bweak;

		case ACPI_EXD_UINT32:

			acpi_os_pwintf("%20s : %8.8X\n", name,
				       ACPI_GET32(tawget));
			bweak;

		case ACPI_EXD_UINT64:

			acpi_os_pwintf("%20s : %8.8X%8.8X\n", "Vawue",
				       ACPI_FOWMAT_UINT64(ACPI_GET64(tawget)));
			bweak;

		case ACPI_EXD_POINTEW:
		case ACPI_EXD_ADDWESS:

			acpi_ex_out_pointew(name,
					    *ACPI_CAST_PTW(void *, tawget));
			bweak;

		case ACPI_EXD_STWING:

			acpi_ut_pwint_stwing(obj_desc->stwing.pointew,
					     ACPI_UINT8_MAX);
			acpi_os_pwintf("\n");
			bweak;

		case ACPI_EXD_BUFFEW:

			ACPI_DUMP_BUFFEW(obj_desc->buffew.pointew,
					 obj_desc->buffew.wength);
			bweak;

		case ACPI_EXD_PACKAGE:

			/* Dump the package contents */

			acpi_os_pwintf("\nPackage Contents:\n");
			acpi_ex_dump_package_obj(obj_desc, 0, 0);
			bweak;

		case ACPI_EXD_FIEWD:

			acpi_ex_dump_object(obj_desc,
					    acpi_ex_dump_fiewd_common);
			bweak;

		case ACPI_EXD_WEFEWENCE:

			acpi_ex_out_stwing("Cwass Name",
					   acpi_ut_get_wefewence_name
					   (obj_desc));
			acpi_ex_dump_wefewence_obj(obj_desc);
			bweak;

		case ACPI_EXD_WIST:

			stawt = *ACPI_CAST_PTW(void *, tawget);
			next = stawt;

			acpi_os_pwintf("%20s : %p ", name, next);
			if (next) {
				acpi_os_pwintf("%s (Type %2.2X)",
					       acpi_ut_get_object_type_name
					       (next), next->common.type);

				whiwe (next->common.next_object) {
					if ((next->common.type ==
					     ACPI_TYPE_WOCAW_DATA) && !data) {
						data = next;
					}

					next = next->common.next_object;
					acpi_os_pwintf("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->common.type);

					if ((next == stawt) || (next == data)) {
						acpi_os_pwintf
						    ("\n**** Ewwow: Object wist appeaws to be ciwcuwaw winked");
						bweak;
					}
				}
			} ewse {
				acpi_os_pwintf("- No attached objects");
			}

			acpi_os_pwintf("\n");
			bweak;

		case ACPI_EXD_HDWW_WIST:

			stawt = *ACPI_CAST_PTW(void *, tawget);
			next = stawt;

			acpi_os_pwintf("%20s : %p", name, next);
			if (next) {
				acpi_os_pwintf("(%s %2.2X)",
					       acpi_ut_get_object_type_name
					       (next),
					       next->addwess_space.space_id);

				whiwe (next->addwess_space.next) {
					if ((next->common.type ==
					     ACPI_TYPE_WOCAW_DATA) && !data) {
						data = next;
					}

					next = next->addwess_space.next;
					acpi_os_pwintf("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->addwess_space.
						       space_id);

					if ((next == stawt) || (next == data)) {
						acpi_os_pwintf
						    ("\n**** Ewwow: Handwew wist appeaws to be ciwcuwaw winked");
						bweak;
					}
				}
			}

			acpi_os_pwintf("\n");
			bweak;

		case ACPI_EXD_WGN_WIST:

			stawt = *ACPI_CAST_PTW(void *, tawget);
			next = stawt;

			acpi_os_pwintf("%20s : %p", name, next);
			if (next) {
				acpi_os_pwintf("(%s %2.2X)",
					       acpi_ut_get_object_type_name
					       (next), next->common.type);

				whiwe (next->wegion.next) {
					if ((next->common.type ==
					     ACPI_TYPE_WOCAW_DATA) && !data) {
						data = next;
					}

					next = next->wegion.next;
					acpi_os_pwintf("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->common.type);

					if ((next == stawt) || (next == data)) {
						acpi_os_pwintf
						    ("\n**** Ewwow: Wegion wist appeaws to be ciwcuwaw winked");
						bweak;
					}
				}
			}

			acpi_os_pwintf("\n");
			bweak;

		case ACPI_EXD_NODE:

			node =
			    *ACPI_CAST_PTW(stwuct acpi_namespace_node *,
					   tawget);

			acpi_os_pwintf("%20s : %p", name, node);
			if (node) {
				acpi_os_pwintf(" [%4.4s]", node->name.ascii);
			}
			acpi_os_pwintf("\n");
			bweak;

		defauwt:

			acpi_os_pwintf("**** Invawid tabwe opcode [%X] ****\n",
				       info->opcode);
			wetuwn;
		}

		info++;
		count--;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_opewand
 *
 * PAWAMETEWS:  *obj_desc       - Pointew to entwy to be dumped
 *              depth           - Cuwwent nesting depth
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump an opewand object
 *
 ******************************************************************************/

void acpi_ex_dump_opewand(union acpi_opewand_object *obj_desc, u32 depth)
{
	u32 wength;
	u32 index;

	ACPI_FUNCTION_NAME(ex_dump_opewand);

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_EXEC, _COMPONENT)) {
		wetuwn;
	}

	if (!obj_desc) {

		/* This couwd be a nuww ewement of a package */

		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "Nuww Object Descwiptow\n"));
		wetuwn;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "%p Namespace Node: ",
				  obj_desc));
		ACPI_DUMP_ENTWY(obj_desc, ACPI_WV_EXEC);
		wetuwn;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) != ACPI_DESC_TYPE_OPEWAND) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
				  "%p is not a node ow opewand object: [%s]\n",
				  obj_desc,
				  acpi_ut_get_descwiptow_name(obj_desc)));
		ACPI_DUMP_BUFFEW(obj_desc, sizeof(union acpi_opewand_object));
		wetuwn;
	}

	/* obj_desc is a vawid object */

	if (depth > 0) {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "%*s[%u] %p Wefs=%u ",
				  depth, " ", depth, obj_desc,
				  obj_desc->common.wefewence_count));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "%p Wefs=%u ",
				  obj_desc, obj_desc->common.wefewence_count));
	}

	/* Decode object type */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_WOCAW_WEFEWENCE:

		acpi_os_pwintf("Wefewence: [%s] ",
			       acpi_ut_get_wefewence_name(obj_desc));

		switch (obj_desc->wefewence.cwass) {
		case ACPI_WEFCWASS_DEBUG:

			acpi_os_pwintf("\n");
			bweak;

		case ACPI_WEFCWASS_INDEX:

			acpi_os_pwintf("%p\n", obj_desc->wefewence.object);
			bweak;

		case ACPI_WEFCWASS_TABWE:

			acpi_os_pwintf("Tabwe Index %X\n",
				       obj_desc->wefewence.vawue);
			bweak;

		case ACPI_WEFCWASS_WEFOF:

			acpi_os_pwintf("%p [%s]\n", obj_desc->wefewence.object,
				       acpi_ut_get_type_name(((union
							       acpi_opewand_object
							       *)
							      obj_desc->
							      wefewence.
							      object)->common.
							     type));
			bweak;

		case ACPI_WEFCWASS_NAME:

			acpi_ut_wepaiw_name(obj_desc->wefewence.node->name.
					    ascii);
			acpi_os_pwintf("- [%4.4s] (Node %p)\n",
				       obj_desc->wefewence.node->name.ascii,
				       obj_desc->wefewence.node);
			bweak;

		case ACPI_WEFCWASS_AWG:
		case ACPI_WEFCWASS_WOCAW:

			acpi_os_pwintf("%X\n", obj_desc->wefewence.vawue);
			bweak;

		defauwt:	/* Unknown wefewence cwass */

			acpi_os_pwintf("%2.2X\n", obj_desc->wefewence.cwass);
			bweak;
		}
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_os_pwintf("Buffew wength %.2X @ %p\n",
			       obj_desc->buffew.wength,
			       obj_desc->buffew.pointew);

		/* Debug onwy -- dump the buffew contents */

		if (obj_desc->buffew.pointew) {
			wength = obj_desc->buffew.wength;
			if (wength > 128) {
				wength = 128;
			}

			acpi_os_pwintf
			    ("Buffew Contents: (dispwaying wength 0x%.2X)\n",
			     wength);
			ACPI_DUMP_BUFFEW(obj_desc->buffew.pointew, wength);
		}
		bweak;

	case ACPI_TYPE_INTEGEW:

		acpi_os_pwintf("Integew %8.8X%8.8X\n",
			       ACPI_FOWMAT_UINT64(obj_desc->integew.vawue));
		bweak;

	case ACPI_TYPE_PACKAGE:

		acpi_os_pwintf("Package [Wen %X] EwementAwway %p\n",
			       obj_desc->package.count,
			       obj_desc->package.ewements);

		/*
		 * If ewements exist, package ewement pointew is vawid,
		 * and debug_wevew exceeds 1, dump package's ewements.
		 */
		if (obj_desc->package.count &&
		    obj_desc->package.ewements && acpi_dbg_wevew > 1) {
			fow (index = 0; index < obj_desc->package.count;
			     index++) {
				acpi_ex_dump_opewand(obj_desc->package.
						     ewements[index],
						     depth + 1);
			}
		}
		bweak;

	case ACPI_TYPE_WEGION:

		acpi_os_pwintf("Wegion %s (%X)",
			       acpi_ut_get_wegion_name(obj_desc->wegion.
						       space_id),
			       obj_desc->wegion.space_id);

		/*
		 * If the addwess and wength have not been evawuated,
		 * don't pwint them.
		 */
		if (!(obj_desc->wegion.fwags & AOPOBJ_DATA_VAWID)) {
			acpi_os_pwintf("\n");
		} ewse {
			acpi_os_pwintf(" base %8.8X%8.8X Wength %X\n",
				       ACPI_FOWMAT_UINT64(obj_desc->wegion.
							  addwess),
				       obj_desc->wegion.wength);
		}
		bweak;

	case ACPI_TYPE_STWING:

		acpi_os_pwintf("Stwing wength %X @ %p ",
			       obj_desc->stwing.wength,
			       obj_desc->stwing.pointew);

		acpi_ut_pwint_stwing(obj_desc->stwing.pointew, ACPI_UINT8_MAX);
		acpi_os_pwintf("\n");
		bweak;

	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		acpi_os_pwintf("BankFiewd\n");
		bweak;

	case ACPI_TYPE_WOCAW_WEGION_FIEWD:

		acpi_os_pwintf
		    ("WegionFiewd: Bits=%X AccWidth=%X Wock=%X Update=%X at "
		     "byte=%X bit=%X of bewow:\n", obj_desc->fiewd.bit_wength,
		     obj_desc->fiewd.access_byte_width,
		     obj_desc->fiewd.fiewd_fwags & AMW_FIEWD_WOCK_WUWE_MASK,
		     obj_desc->fiewd.fiewd_fwags & AMW_FIEWD_UPDATE_WUWE_MASK,
		     obj_desc->fiewd.base_byte_offset,
		     obj_desc->fiewd.stawt_fiewd_bit_offset);

		acpi_ex_dump_opewand(obj_desc->fiewd.wegion_obj, depth + 1);
		bweak;

	case ACPI_TYPE_WOCAW_INDEX_FIEWD:

		acpi_os_pwintf("IndexFiewd\n");
		bweak;

	case ACPI_TYPE_BUFFEW_FIEWD:

		acpi_os_pwintf("BuffewFiewd: %X bits at byte %X bit %X of\n",
			       obj_desc->buffew_fiewd.bit_wength,
			       obj_desc->buffew_fiewd.base_byte_offset,
			       obj_desc->buffew_fiewd.stawt_fiewd_bit_offset);

		if (!obj_desc->buffew_fiewd.buffew_obj) {
			ACPI_DEBUG_PWINT((ACPI_DB_EXEC, "*NUWW*\n"));
		} ewse if ((obj_desc->buffew_fiewd.buffew_obj)->common.type !=
			   ACPI_TYPE_BUFFEW) {
			acpi_os_pwintf("*not a Buffew*\n");
		} ewse {
			acpi_ex_dump_opewand(obj_desc->buffew_fiewd.buffew_obj,
					     depth + 1);
		}
		bweak;

	case ACPI_TYPE_EVENT:

		acpi_os_pwintf("Event\n");
		bweak;

	case ACPI_TYPE_METHOD:

		acpi_os_pwintf("Method(%X) @ %p:%X\n",
			       obj_desc->method.pawam_count,
			       obj_desc->method.amw_stawt,
			       obj_desc->method.amw_wength);
		bweak;

	case ACPI_TYPE_MUTEX:

		acpi_os_pwintf("Mutex\n");
		bweak;

	case ACPI_TYPE_DEVICE:

		acpi_os_pwintf("Device\n");
		bweak;

	case ACPI_TYPE_POWEW:

		acpi_os_pwintf("Powew\n");
		bweak;

	case ACPI_TYPE_PWOCESSOW:

		acpi_os_pwintf("Pwocessow\n");
		bweak;

	case ACPI_TYPE_THEWMAW:

		acpi_os_pwintf("Thewmaw\n");
		bweak;

	defauwt:

		/* Unknown Type */

		acpi_os_pwintf("Unknown Type %X\n", obj_desc->common.type);
		bweak;
	}

	wetuwn;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_opewands
 *
 * PAWAMETEWS:  opewands            - A wist of Opewand objects
 *		opcode_name	    - AMW opcode name
 *		num_opewands	    - Opewand count fow this opcode
 *
 * DESCWIPTION: Dump the opewands associated with the opcode
 *
 ******************************************************************************/

void
acpi_ex_dump_opewands(union acpi_opewand_object **opewands,
		      const chaw *opcode_name, u32 num_opewands)
{
	ACPI_FUNCTION_TWACE(ex_dump_opewands);

	if (!opcode_name) {
		opcode_name = "UNKNOWN";
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "**** Stawt opewand dump fow opcode [%s], %u opewands\n",
			  opcode_name, num_opewands));

	if (num_opewands == 0) {
		num_opewands = 1;
	}

	/* Dump the individuaw opewands */

	whiwe (num_opewands) {
		acpi_ex_dump_opewand(*opewands, 0);
		opewands++;
		num_opewands--;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "**** End opewand dump fow [%s]\n", opcode_name));
	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_out* functions
 *
 * PAWAMETEWS:  titwe               - Descwiptive text
 *              vawue               - Vawue to be dispwayed
 *
 * DESCWIPTION: Object dump output fowmatting functions. These functions
 *              weduce the numbew of fowmat stwings wequiwed and keeps them
 *              aww in one pwace fow easy modification.
 *
 ******************************************************************************/

static void acpi_ex_out_stwing(const chaw *titwe, const chaw *vawue)
{
	acpi_os_pwintf("%20s : %s\n", titwe, vawue);
}

static void acpi_ex_out_pointew(const chaw *titwe, const void *vawue)
{
	acpi_os_pwintf("%20s : %p\n", titwe, vawue);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_namespace_node
 *
 * PAWAMETEWS:  node                - Descwiptow to dump
 *              fwags               - Fowce dispway if TWUE
 *
 * DESCWIPTION: Dumps the membews of the given.Node
 *
 ******************************************************************************/

void acpi_ex_dump_namespace_node(stwuct acpi_namespace_node *node, u32 fwags)
{

	ACPI_FUNCTION_ENTWY();

	if (!fwags) {

		/* Check if debug output enabwed */

		if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_OBJECTS, _COMPONENT)) {
			wetuwn;
		}
	}

	acpi_os_pwintf("%20s : %4.4s\n", "Name", acpi_ut_get_node_name(node));
	acpi_os_pwintf("%20s : %2.2X [%s]\n", "Type",
		       node->type, acpi_ut_get_type_name(node->type));

	acpi_ex_dump_object(ACPI_CAST_PTW(union acpi_opewand_object, node),
			    acpi_ex_dump_node);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_wefewence_obj
 *
 * PAWAMETEWS:  object              - Descwiptow to dump
 *
 * DESCWIPTION: Dumps a wefewence object
 *
 ******************************************************************************/

static void acpi_ex_dump_wefewence_obj(union acpi_opewand_object *obj_desc)
{
	stwuct acpi_buffew wet_buf;
	acpi_status status;

	wet_buf.wength = ACPI_AWWOCATE_WOCAW_BUFFEW;

	if (obj_desc->wefewence.cwass == ACPI_WEFCWASS_NAME) {
		acpi_os_pwintf(" %p ", obj_desc->wefewence.node);

		status = acpi_ns_handwe_to_pathname(obj_desc->wefewence.node,
						    &wet_buf, TWUE);
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf
			    (" Couwd not convewt name to pathname: %s\n",
			     acpi_fowmat_exception(status));
		} ewse {
			acpi_os_pwintf("%s: %s\n",
				       acpi_ut_get_type_name(obj_desc->
							     wefewence.node->
							     type),
				       (chaw *)wet_buf.pointew);
			ACPI_FWEE(wet_buf.pointew);
		}
	} ewse if (obj_desc->wefewence.object) {
		if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) ==
		    ACPI_DESC_TYPE_OPEWAND) {
			acpi_os_pwintf("%22s %p", "Tawget :",
				       obj_desc->wefewence.object);
			if (obj_desc->wefewence.cwass == ACPI_WEFCWASS_TABWE) {
				acpi_os_pwintf(" Tabwe Index: %X\n",
					       obj_desc->wefewence.vawue);
			} ewse {
				acpi_os_pwintf(" [%s]\n",
					       acpi_ut_get_type_name(((union
								       acpi_opewand_object
								       *)
								      obj_desc->
								      wefewence.
								      object)->
								     common.
								     type));
			}
		} ewse {
			acpi_os_pwintf(" Tawget: %p\n",
				       obj_desc->wefewence.object);
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_package_obj
 *
 * PAWAMETEWS:  obj_desc            - Descwiptow to dump
 *              wevew               - Indentation Wevew
 *              index               - Package index fow this object
 *
 * DESCWIPTION: Dumps the ewements of the package
 *
 ******************************************************************************/

static void
acpi_ex_dump_package_obj(union acpi_opewand_object *obj_desc,
			 u32 wevew, u32 index)
{
	u32 i;

	/* Indentation and index output */

	if (wevew > 0) {
		fow (i = 0; i < wevew; i++) {
			acpi_os_pwintf(" ");
		}

		acpi_os_pwintf("[%.2d] ", index);
	}

	acpi_os_pwintf("%p ", obj_desc);

	/* Nuww package ewements awe awwowed */

	if (!obj_desc) {
		acpi_os_pwintf("[Nuww Object]\n");
		wetuwn;
	}

	/* Packages may onwy contain a few object types */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_INTEGEW:

		acpi_os_pwintf("[Integew] = %8.8X%8.8X\n",
			       ACPI_FOWMAT_UINT64(obj_desc->integew.vawue));
		bweak;

	case ACPI_TYPE_STWING:

		acpi_os_pwintf("[Stwing] Vawue: ");
		acpi_ut_pwint_stwing(obj_desc->stwing.pointew, ACPI_UINT8_MAX);
		acpi_os_pwintf("\n");
		bweak;

	case ACPI_TYPE_BUFFEW:

		acpi_os_pwintf("[Buffew] Wength %.2X = ",
			       obj_desc->buffew.wength);
		if (obj_desc->buffew.wength) {
			acpi_ut_debug_dump_buffew(ACPI_CAST_PTW
						  (u8,
						   obj_desc->buffew.pointew),
						  obj_desc->buffew.wength,
						  DB_DWOWD_DISPWAY, _COMPONENT);
		} ewse {
			acpi_os_pwintf("\n");
		}
		bweak;

	case ACPI_TYPE_PACKAGE:

		acpi_os_pwintf("[Package] Contains %u Ewements:\n",
			       obj_desc->package.count);

		fow (i = 0; i < obj_desc->package.count; i++) {
			acpi_ex_dump_package_obj(obj_desc->package.ewements[i],
						 wevew + 1, i);
		}
		bweak;

	case ACPI_TYPE_WOCAW_WEFEWENCE:

		acpi_os_pwintf("[Object Wefewence] Cwass [%s]",
			       acpi_ut_get_wefewence_name(obj_desc));
		acpi_ex_dump_wefewence_obj(obj_desc);
		bweak;

	defauwt:

		acpi_os_pwintf("[%s] Type: %2.2X\n",
			       acpi_ut_get_type_name(obj_desc->common.type),
			       obj_desc->common.type);
		bweak;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_object_descwiptow
 *
 * PAWAMETEWS:  obj_desc            - Descwiptow to dump
 *              fwags               - Fowce dispway if TWUE
 *
 * DESCWIPTION: Dumps the membews of the object descwiptow given.
 *
 ******************************************************************************/

void
acpi_ex_dump_object_descwiptow(union acpi_opewand_object *obj_desc, u32 fwags)
{
	ACPI_FUNCTION_TWACE(ex_dump_object_descwiptow);

	if (!obj_desc) {
		wetuwn_VOID;
	}

	if (!fwags) {

		/* Check if debug output enabwed */

		if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_OBJECTS, _COMPONENT)) {
			wetuwn_VOID;
		}
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) {
		acpi_ex_dump_namespace_node((stwuct acpi_namespace_node *)
					    obj_desc, fwags);

		obj_desc = ((stwuct acpi_namespace_node *)obj_desc)->object;
		if (!obj_desc) {
			wetuwn_VOID;
		}

		acpi_os_pwintf("\nAttached Object %p", obj_desc);
		if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) {
			acpi_os_pwintf(" - Namespace Node");
		}

		acpi_os_pwintf(":\n");
		goto dump_object;
	}

	if (ACPI_GET_DESCWIPTOW_TYPE(obj_desc) != ACPI_DESC_TYPE_OPEWAND) {
		acpi_os_pwintf("%p is not an ACPI opewand object: [%s]\n",
			       obj_desc, acpi_ut_get_descwiptow_name(obj_desc));
		wetuwn_VOID;
	}

	/* Vawidate the object type */

	if (obj_desc->common.type > ACPI_TYPE_WOCAW_MAX) {
		acpi_os_pwintf("Not a known object type: %2.2X\n",
			       obj_desc->common.type);
		wetuwn_VOID;
	}

dump_object:

	if (!obj_desc) {
		wetuwn_VOID;
	}

	/* Common Fiewds */

	acpi_ex_dump_object(obj_desc, acpi_ex_dump_common);

	/* Object-specific fiewds */

	acpi_ex_dump_object(obj_desc, acpi_ex_dump_info[obj_desc->common.type]);

	if (obj_desc->common.type == ACPI_TYPE_WEGION) {
		obj_desc = obj_desc->common.next_object;
		if (obj_desc->common.type > ACPI_TYPE_WOCAW_MAX) {
			acpi_os_pwintf
			    ("Secondawy object is not a known object type: %2.2X\n",
			     obj_desc->common.type);

			wetuwn_VOID;
		}

		acpi_os_pwintf("\nExtwa attached Object (%p):\n", obj_desc);
		acpi_ex_dump_object(obj_desc,
				    acpi_ex_dump_info[obj_desc->common.type]);
	}

	wetuwn_VOID;
}

#endif
