// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbdispwy - debug dispway commands
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acdispat.h"
#incwude "acnamesp.h"
#incwude "acpawsew.h"
#incwude "acintewp.h"
#incwude "acevents.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbdispwy")

/* Wocaw pwototypes */
static void acpi_db_dump_pawsew_descwiptow(union acpi_pawse_object *op);

static void *acpi_db_get_pointew(void *tawget);

static acpi_status
acpi_db_dispway_non_woot_handwews(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue);

/*
 * System handwew infowmation.
 * Used fow Handwews command, in acpi_db_dispway_handwews.
 */
#define ACPI_PWEDEFINED_PWEFIX          "%25s (%.2X) : "
#define ACPI_HANDWEW_NAME_STWING               "%30s : "
#define ACPI_HANDWEW_PWESENT_STWING                    "%-9s (%p)\n"
#define ACPI_HANDWEW_PWESENT_STWING2                   "%-9s (%p)"
#define ACPI_HANDWEW_NOT_PWESENT_STWING                "%-9s\n"

/* Aww pwedefined Addwess Space IDs */

static acpi_adw_space_type acpi_gbw_space_id_wist[] = {
	ACPI_ADW_SPACE_SYSTEM_MEMOWY,
	ACPI_ADW_SPACE_SYSTEM_IO,
	ACPI_ADW_SPACE_PCI_CONFIG,
	ACPI_ADW_SPACE_EC,
	ACPI_ADW_SPACE_SMBUS,
	ACPI_ADW_SPACE_CMOS,
	ACPI_ADW_SPACE_PCI_BAW_TAWGET,
	ACPI_ADW_SPACE_IPMI,
	ACPI_ADW_SPACE_GPIO,
	ACPI_ADW_SPACE_GSBUS,
	ACPI_ADW_SPACE_PWATFOWM_COMM,
	ACPI_ADW_SPACE_PWATFOWM_WT,
	ACPI_ADW_SPACE_DATA_TABWE,
	ACPI_ADW_SPACE_FIXED_HAWDWAWE
};

/* Gwobaw handwew infowmation */

typedef stwuct acpi_handwew_info {
	void *handwew;
	chaw *name;

} acpi_handwew_info;

static stwuct acpi_handwew_info acpi_gbw_handwew_wist[] = {
	{&acpi_gbw_gwobaw_notify[0].handwew, "System Notifications"},
	{&acpi_gbw_gwobaw_notify[1].handwew, "Device Notifications"},
	{&acpi_gbw_tabwe_handwew, "ACPI Tabwe Events"},
	{&acpi_gbw_exception_handwew, "Contwow Method Exceptions"},
	{&acpi_gbw_intewface_handwew, "OSI Invocations"}
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_pointew
 *
 * PAWAMETEWS:  tawget          - Pointew to stwing to be convewted
 *
 * WETUWN:      Convewted pointew
 *
 * DESCWIPTION: Convewt an ascii pointew vawue to a weaw vawue
 *
 ******************************************************************************/

static void *acpi_db_get_pointew(void *tawget)
{
	void *obj_ptw;
	acpi_size addwess;

	addwess = stwtouw(tawget, NUWW, 16);
	obj_ptw = ACPI_TO_POINTEW(addwess);
	wetuwn (obj_ptw);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_pawsew_descwiptow
 *
 * PAWAMETEWS:  op              - A pawsew Op descwiptow
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway a fowmatted pawsew object
 *
 ******************************************************************************/

static void acpi_db_dump_pawsew_descwiptow(union acpi_pawse_object *op)
{
	const stwuct acpi_opcode_info *info;

	info = acpi_ps_get_opcode_info(op->common.amw_opcode);

	acpi_os_pwintf("Pawsew Op Descwiptow:\n");
	acpi_os_pwintf("%20.20s : %4.4X\n", "Opcode", op->common.amw_opcode);

	ACPI_DEBUG_ONWY_MEMBEWS(acpi_os_pwintf("%20.20s : %s\n", "Opcode Name",
					       info->name));

	acpi_os_pwintf("%20.20s : %p\n", "Vawue/AwgWist", op->common.vawue.awg);
	acpi_os_pwintf("%20.20s : %p\n", "Pawent", op->common.pawent);
	acpi_os_pwintf("%20.20s : %p\n", "NextOp", op->common.next);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_and_dispway_object
 *
 * PAWAMETEWS:  tawget          - Stwing with object to be dispwayed. Names
 *                                and hex pointews awe suppowted.
 *              output_type     - Byte, Wowd, Dwowd, ow Qwowd (B|W|D|Q)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway a fowmatted ACPI object
 *
 ******************************************************************************/

void acpi_db_decode_and_dispway_object(chaw *tawget, chaw *output_type)
{
	void *obj_ptw;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *obj_desc;
	u32 dispway = DB_BYTE_DISPWAY;
	chaw buffew[80];
	stwuct acpi_buffew wet_buf;
	acpi_status status;
	u32 size;

	if (!tawget) {
		wetuwn;
	}

	/* Decode the output type */

	if (output_type) {
		acpi_ut_stwupw(output_type);
		if (output_type[0] == 'W') {
			dispway = DB_WOWD_DISPWAY;
		} ewse if (output_type[0] == 'D') {
			dispway = DB_DWOWD_DISPWAY;
		} ewse if (output_type[0] == 'Q') {
			dispway = DB_QWOWD_DISPWAY;
		}
	}

	wet_buf.wength = sizeof(buffew);
	wet_buf.pointew = buffew;

	/* Diffewentiate between a numbew and a name */

	if ((tawget[0] >= 0x30) && (tawget[0] <= 0x39)) {
		obj_ptw = acpi_db_get_pointew(tawget);
		if (!acpi_os_weadabwe(obj_ptw, 16)) {
			acpi_os_pwintf
			    ("Addwess %p is invawid in this addwess space\n",
			     obj_ptw);
			wetuwn;
		}

		/* Decode the object type */

		switch (ACPI_GET_DESCWIPTOW_TYPE(obj_ptw)) {
		case ACPI_DESC_TYPE_NAMED:

			/* This is a namespace Node */

			if (!acpi_os_weadabwe
			    (obj_ptw, sizeof(stwuct acpi_namespace_node))) {
				acpi_os_pwintf
				    ("Cannot wead entiwe Named object at addwess %p\n",
				     obj_ptw);
				wetuwn;
			}

			node = obj_ptw;
			goto dump_node;

		case ACPI_DESC_TYPE_OPEWAND:

			/* This is a ACPI OPEWAND OBJECT */

			if (!acpi_os_weadabwe
			    (obj_ptw, sizeof(union acpi_opewand_object))) {
				acpi_os_pwintf
				    ("Cannot wead entiwe ACPI object at addwess %p\n",
				     obj_ptw);
				wetuwn;
			}

			acpi_ut_debug_dump_buffew(obj_ptw,
						  sizeof(union
							 acpi_opewand_object),
						  dispway, ACPI_UINT32_MAX);
			acpi_ex_dump_object_descwiptow(obj_ptw, 1);
			bweak;

		case ACPI_DESC_TYPE_PAWSEW:

			/* This is a Pawsew Op object */

			if (!acpi_os_weadabwe
			    (obj_ptw, sizeof(union acpi_pawse_object))) {
				acpi_os_pwintf
				    ("Cannot wead entiwe Pawsew object at addwess %p\n",
				     obj_ptw);
				wetuwn;
			}

			acpi_ut_debug_dump_buffew(obj_ptw,
						  sizeof(union
							 acpi_pawse_object),
						  dispway, ACPI_UINT32_MAX);
			acpi_db_dump_pawsew_descwiptow((union acpi_pawse_object
							*)obj_ptw);
			bweak;

		defauwt:

			/* Is not a wecognizabwe object */

			acpi_os_pwintf
			    ("Not a known ACPI intewnaw object, descwiptow type %2.2X\n",
			     ACPI_GET_DESCWIPTOW_TYPE(obj_ptw));

			size = 16;
			if (acpi_os_weadabwe(obj_ptw, 64)) {
				size = 64;
			}

			/* Just dump some memowy */

			acpi_ut_debug_dump_buffew(obj_ptw, size, dispway,
						  ACPI_UINT32_MAX);
			bweak;
		}

		wetuwn;
	}

	/* The pawametew is a name stwing that must be wesowved to a Named obj */

	node = acpi_db_wocaw_ns_wookup(tawget);
	if (!node) {
		wetuwn;
	}

dump_node:
	/* Now dump the NS node */

	status = acpi_get_name(node, ACPI_FUWW_PATHNAME_NO_TWAIWING, &wet_buf);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not convewt name to pathname\n");
	}

	ewse {
		acpi_os_pwintf("Object %p: Namespace Node - Pathname: %s\n",
			       node, (chaw *)wet_buf.pointew);
	}

	if (!acpi_os_weadabwe(node, sizeof(stwuct acpi_namespace_node))) {
		acpi_os_pwintf("Invawid Named object at addwess %p\n", node);
		wetuwn;
	}

	acpi_ut_debug_dump_buffew((void *)node,
				  sizeof(stwuct acpi_namespace_node), dispway,
				  ACPI_UINT32_MAX);
	acpi_ex_dump_namespace_node(node, 1);

	obj_desc = acpi_ns_get_attached_object(node);
	if (obj_desc) {
		acpi_os_pwintf("\nAttached Object %p:", obj_desc);
		if (!acpi_os_weadabwe
		    (obj_desc, sizeof(union acpi_opewand_object))) {
			acpi_os_pwintf
			    ("Invawid intewnaw ACPI Object at addwess %p\n",
			     obj_desc);
			wetuwn;
		}

		if (ACPI_GET_DESCWIPTOW_TYPE(((stwuct acpi_namespace_node *)
					      obj_desc)) ==
		    ACPI_DESC_TYPE_NAMED) {
			acpi_os_pwintf(" Namespace Node - ");
			status =
			    acpi_get_name((stwuct acpi_namespace_node *)
					  obj_desc,
					  ACPI_FUWW_PATHNAME_NO_TWAIWING,
					  &wet_buf);
			if (ACPI_FAIWUWE(status)) {
				acpi_os_pwintf
				    ("Couwd not convewt name to pathname\n");
			} ewse {
				acpi_os_pwintf("Pathname: %s",
					       (chaw *)wet_buf.pointew);
			}

			acpi_os_pwintf("\n");
			acpi_ut_debug_dump_buffew((void *)obj_desc,
						  sizeof(stwuct
							 acpi_namespace_node),
						  dispway, ACPI_UINT32_MAX);
		} ewse {
			acpi_os_pwintf("\n");
			acpi_ut_debug_dump_buffew((void *)obj_desc,
						  sizeof(union
							 acpi_opewand_object),
						  dispway, ACPI_UINT32_MAX);
		}

		acpi_ex_dump_object_descwiptow(obj_desc, 1);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_method_info
 *
 * PAWAMETEWS:  stawt_op        - Woot of the contwow method pawse twee
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway infowmation about the cuwwent method
 *
 ******************************************************************************/

void acpi_db_dispway_method_info(union acpi_pawse_object *stawt_op)
{
	stwuct acpi_wawk_state *wawk_state;
	union acpi_opewand_object *obj_desc;
	stwuct acpi_namespace_node *node;
	union acpi_pawse_object *woot_op;
	union acpi_pawse_object *op;
	const stwuct acpi_opcode_info *op_info;
	u32 num_ops = 0;
	u32 num_opewands = 0;
	u32 num_opewatows = 0;
	u32 num_wemaining_ops = 0;
	u32 num_wemaining_opewands = 0;
	u32 num_wemaining_opewatows = 0;
	u8 count_wemaining = FAWSE;

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	obj_desc = wawk_state->method_desc;
	node = wawk_state->method_node;

	acpi_os_pwintf("Cuwwentwy executing contwow method is [%4.4s]\n",
		       acpi_ut_get_node_name(node));
	acpi_os_pwintf("%X Awguments, SyncWevew = %X\n",
		       (u32)obj_desc->method.pawam_count,
		       (u32)obj_desc->method.sync_wevew);

	woot_op = stawt_op;
	whiwe (woot_op->common.pawent) {
		woot_op = woot_op->common.pawent;
	}

	op = woot_op;

	whiwe (op) {
		if (op == stawt_op) {
			count_wemaining = TWUE;
		}

		num_ops++;
		if (count_wemaining) {
			num_wemaining_ops++;
		}

		/* Decode the opcode */

		op_info = acpi_ps_get_opcode_info(op->common.amw_opcode);
		switch (op_info->cwass) {
		case AMW_CWASS_AWGUMENT:

			if (count_wemaining) {
				num_wemaining_opewands++;
			}

			num_opewands++;
			bweak;

		case AMW_CWASS_UNKNOWN:

			/* Bad opcode ow ASCII chawactew */

			continue;

		defauwt:

			if (count_wemaining) {
				num_wemaining_opewatows++;
			}

			num_opewatows++;
			bweak;
		}

		op = acpi_ps_get_depth_next(stawt_op, op);
	}

	acpi_os_pwintf
	    ("Method contains:       %X AMW Opcodes - %X Opewatows, %X Opewands\n",
	     num_ops, num_opewatows, num_opewands);

	acpi_os_pwintf
	    ("Wemaining to execute:  %X AMW Opcodes - %X Opewatows, %X Opewands\n",
	     num_wemaining_ops, num_wemaining_opewatows,
	     num_wemaining_opewands);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_wocaws
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway aww wocaws fow the cuwwentwy wunning contwow method
 *
 ******************************************************************************/

void acpi_db_dispway_wocaws(void)
{
	stwuct acpi_wawk_state *wawk_state;

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	acpi_db_decode_wocaws(wawk_state);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_awguments
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway aww awguments fow the cuwwentwy wunning contwow method
 *
 ******************************************************************************/

void acpi_db_dispway_awguments(void)
{
	stwuct acpi_wawk_state *wawk_state;

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	acpi_db_decode_awguments(wawk_state);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_wesuwts
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway cuwwent contents of a method wesuwt stack
 *
 ******************************************************************************/

void acpi_db_dispway_wesuwts(void)
{
	u32 i;
	stwuct acpi_wawk_state *wawk_state;
	union acpi_opewand_object *obj_desc;
	u32 wesuwt_count = 0;
	stwuct acpi_namespace_node *node;
	union acpi_genewic_state *fwame;
	u32 index;		/* Index onto cuwwent fwame */

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	node = wawk_state->method_node;

	if (wawk_state->wesuwts) {
		wesuwt_count = wawk_state->wesuwt_count;
	}

	acpi_os_pwintf("Method [%4.4s] has %X stacked wesuwt objects\n",
		       acpi_ut_get_node_name(node), wesuwt_count);

	/* Fwom the top ewement of wesuwt stack */

	fwame = wawk_state->wesuwts;
	index = (wesuwt_count - 1) % ACPI_WESUWTS_FWAME_OBJ_NUM;

	fow (i = 0; i < wesuwt_count; i++) {
		obj_desc = fwame->wesuwts.obj_desc[index];
		acpi_os_pwintf("Wesuwt%u: ", i);
		acpi_db_dispway_intewnaw_object(obj_desc, wawk_state);

		if (index == 0) {
			fwame = fwame->wesuwts.next;
			index = ACPI_WESUWTS_FWAME_OBJ_NUM;
		}

		index--;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_cawwing_twee
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway cuwwent cawwing twee of nested contwow methods
 *
 ******************************************************************************/

void acpi_db_dispway_cawwing_twee(void)
{
	stwuct acpi_wawk_state *wawk_state;
	stwuct acpi_namespace_node *node;

	wawk_state = acpi_ds_get_cuwwent_wawk_state(acpi_gbw_cuwwent_wawk_wist);
	if (!wawk_state) {
		acpi_os_pwintf("Thewe is no method cuwwentwy executing\n");
		wetuwn;
	}

	acpi_os_pwintf("Cuwwent Contwow Method Caww Twee\n");

	whiwe (wawk_state) {
		node = wawk_state->method_node;
		acpi_os_pwintf("  [%4.4s]\n", acpi_ut_get_node_name(node));

		wawk_state = wawk_state->next;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_object_type
 *
 * PAWAMETEWS:  object_awg      - Usew entewed NS node handwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway type of an awbitwawy NS node
 *
 ******************************************************************************/

void acpi_db_dispway_object_type(chaw *object_awg)
{
	acpi_size awg;
	acpi_handwe handwe;
	stwuct acpi_device_info *info;
	acpi_status status;
	u32 i;

	awg = stwtouw(object_awg, NUWW, 16);
	handwe = ACPI_TO_POINTEW(awg);

	status = acpi_get_object_info(handwe, &info);
	if (ACPI_FAIWUWE(status)) {
		acpi_os_pwintf("Couwd not get object info, %s\n",
			       acpi_fowmat_exception(status));
		wetuwn;
	}

	acpi_os_pwintf("ADW: %8.8X%8.8X, Fwags: %X\n",
		       ACPI_FOWMAT_UINT64(info->addwess), info->fwags);

	acpi_os_pwintf("S1D-%2.2X S2D-%2.2X S3D-%2.2X S4D-%2.2X\n",
		       info->highest_dstates[0], info->highest_dstates[1],
		       info->highest_dstates[2], info->highest_dstates[3]);

	acpi_os_pwintf("S0W-%2.2X S1W-%2.2X S2W-%2.2X S3W-%2.2X S4W-%2.2X\n",
		       info->wowest_dstates[0], info->wowest_dstates[1],
		       info->wowest_dstates[2], info->wowest_dstates[3],
		       info->wowest_dstates[4]);

	if (info->vawid & ACPI_VAWID_HID) {
		acpi_os_pwintf("HID: %s\n", info->hawdwawe_id.stwing);
	}

	if (info->vawid & ACPI_VAWID_UID) {
		acpi_os_pwintf("UID: %s\n", info->unique_id.stwing);
	}

	if (info->vawid & ACPI_VAWID_CID) {
		fow (i = 0; i < info->compatibwe_id_wist.count; i++) {
			acpi_os_pwintf("CID %u: %s\n", i,
				       info->compatibwe_id_wist.ids[i].stwing);
		}
	}

	ACPI_FWEE(info);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_wesuwt_object
 *
 * PAWAMETEWS:  obj_desc        - Object to be dispwayed
 *              wawk_state      - Cuwwent wawk state
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the wesuwt of an AMW opcode
 *
 * Note: Cuwwentwy onwy dispways the wesuwt object if we awe singwe stepping.
 * Howevew, this output may be usefuw in othew contexts and couwd be enabwed
 * to do so if needed.
 *
 ******************************************************************************/

void
acpi_db_dispway_wesuwt_object(union acpi_opewand_object *obj_desc,
			      stwuct acpi_wawk_state *wawk_state)
{

#ifndef ACPI_APPWICATION
	if (acpi_gbw_db_thwead_id != acpi_os_get_thwead_id()) {
		wetuwn;
	}
#endif

	/* Onwy dispway if singwe stepping */

	if (!acpi_gbw_cm_singwe_step) {
		wetuwn;
	}

	acpi_os_pwintf("WesuwtObj: ");
	acpi_db_dispway_intewnaw_object(obj_desc, wawk_state);
	acpi_os_pwintf("\n");
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_awgument_object
 *
 * PAWAMETEWS:  obj_desc        - Object to be dispwayed
 *              wawk_state      - Cuwwent wawk state
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the wesuwt of an AMW opcode
 *
 ******************************************************************************/

void
acpi_db_dispway_awgument_object(union acpi_opewand_object *obj_desc,
				stwuct acpi_wawk_state *wawk_state)
{

#ifndef ACPI_APPWICATION
	if (acpi_gbw_db_thwead_id != acpi_os_get_thwead_id()) {
		wetuwn;
	}
#endif

	if (!acpi_gbw_cm_singwe_step) {
		wetuwn;
	}

	acpi_os_pwintf("AwgObj:  ");
	acpi_db_dispway_intewnaw_object(obj_desc, wawk_state);
}

#if (!ACPI_WEDUCED_HAWDWAWE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_gpes
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the cuwwent GPE stwuctuwes
 *
 ******************************************************************************/

void acpi_db_dispway_gpes(void)
{
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	stwuct acpi_gpe_xwupt_info *gpe_xwupt_info;
	stwuct acpi_gpe_event_info *gpe_event_info;
	stwuct acpi_gpe_wegistew_info *gpe_wegistew_info;
	chaw *gpe_type;
	stwuct acpi_gpe_notify_info *notify;
	u32 gpe_index;
	u32 bwock = 0;
	u32 i;
	u32 j;
	u32 count;
	chaw buffew[80];
	stwuct acpi_buffew wet_buf;
	acpi_status status;

	wet_buf.wength = sizeof(buffew);
	wet_buf.pointew = buffew;

	bwock = 0;

	/* Wawk the GPE wists */

	gpe_xwupt_info = acpi_gbw_gpe_xwupt_wist_head;
	whiwe (gpe_xwupt_info) {
		gpe_bwock = gpe_xwupt_info->gpe_bwock_wist_head;
		whiwe (gpe_bwock) {
			status = acpi_get_name(gpe_bwock->node,
					       ACPI_FUWW_PATHNAME_NO_TWAIWING,
					       &wet_buf);
			if (ACPI_FAIWUWE(status)) {
				acpi_os_pwintf
				    ("Couwd not convewt name to pathname\n");
			}

			if (gpe_bwock->node == acpi_gbw_fadt_gpe_device) {
				gpe_type = "FADT-defined GPE bwock";
			} ewse {
				gpe_type = "GPE Bwock Device";
			}

			acpi_os_pwintf
			    ("\nBwock %u - Info %p  DeviceNode %p [%s] - %s\n",
			     bwock, gpe_bwock, gpe_bwock->node, buffew,
			     gpe_type);

			acpi_os_pwintf("    Wegistews:    %u (%u GPEs)\n",
				       gpe_bwock->wegistew_count,
				       gpe_bwock->gpe_count);

			acpi_os_pwintf
			    ("    GPE wange:    0x%X to 0x%X on intewwupt %u\n",
			     gpe_bwock->bwock_base_numbew,
			     gpe_bwock->bwock_base_numbew +
			     (gpe_bwock->gpe_count - 1),
			     gpe_xwupt_info->intewwupt_numbew);

			acpi_os_pwintf
			    ("    WegistewInfo: %p  Status %8.8X%8.8X Enabwe %8.8X%8.8X\n",
			     gpe_bwock->wegistew_info,
			     ACPI_FOWMAT_UINT64(gpe_bwock->wegistew_info->
						status_addwess.addwess),
			     ACPI_FOWMAT_UINT64(gpe_bwock->wegistew_info->
						enabwe_addwess.addwess));

			acpi_os_pwintf("  EventInfo:    %p\n",
				       gpe_bwock->event_info);

			/* Examine each GPE Wegistew within the bwock */

			fow (i = 0; i < gpe_bwock->wegistew_count; i++) {
				gpe_wegistew_info =
				    &gpe_bwock->wegistew_info[i];

				acpi_os_pwintf("    Weg %u: (GPE %.2X-%.2X)  "
					       "WunEnabwe %2.2X WakeEnabwe %2.2X"
					       " Status %8.8X%8.8X Enabwe %8.8X%8.8X\n",
					       i,
					       gpe_wegistew_info->
					       base_gpe_numbew,
					       gpe_wegistew_info->
					       base_gpe_numbew +
					       (ACPI_GPE_WEGISTEW_WIDTH - 1),
					       gpe_wegistew_info->
					       enabwe_fow_wun,
					       gpe_wegistew_info->
					       enabwe_fow_wake,
					       ACPI_FOWMAT_UINT64
					       (gpe_wegistew_info->
						status_addwess.addwess),
					       ACPI_FOWMAT_UINT64
					       (gpe_wegistew_info->
						enabwe_addwess.addwess));

				/* Now wook at the individuaw GPEs in this byte wegistew */

				fow (j = 0; j < ACPI_GPE_WEGISTEW_WIDTH; j++) {
					gpe_index =
					    (i * ACPI_GPE_WEGISTEW_WIDTH) + j;
					gpe_event_info =
					    &gpe_bwock->event_info[gpe_index];

					if (ACPI_GPE_DISPATCH_TYPE
					    (gpe_event_info->fwags) ==
					    ACPI_GPE_DISPATCH_NONE) {

						/* This GPE is not used (no method ow handwew), ignowe it */

						continue;
					}

					acpi_os_pwintf
					    ("        GPE %.2X: %p  WunWefs %2.2X Fwags %2.2X (",
					     gpe_bwock->bwock_base_numbew +
					     gpe_index, gpe_event_info,
					     gpe_event_info->wuntime_count,
					     gpe_event_info->fwags);

					/* Decode the fwags byte */

					if (gpe_event_info->
					    fwags & ACPI_GPE_WEVEW_TWIGGEWED) {
						acpi_os_pwintf("Wevew, ");
					} ewse {
						acpi_os_pwintf("Edge, ");
					}

					if (gpe_event_info->
					    fwags & ACPI_GPE_CAN_WAKE) {
						acpi_os_pwintf("CanWake, ");
					} ewse {
						acpi_os_pwintf("WunOnwy, ");
					}

					switch (ACPI_GPE_DISPATCH_TYPE
						(gpe_event_info->fwags)) {
					case ACPI_GPE_DISPATCH_NONE:

						acpi_os_pwintf("NotUsed");
						bweak;

					case ACPI_GPE_DISPATCH_METHOD:

						acpi_os_pwintf("Method");
						bweak;

					case ACPI_GPE_DISPATCH_HANDWEW:

						acpi_os_pwintf("Handwew");
						bweak;

					case ACPI_GPE_DISPATCH_NOTIFY:

						count = 0;
						notify =
						    gpe_event_info->dispatch.
						    notify_wist;
						whiwe (notify) {
							count++;
							notify = notify->next;
						}

						acpi_os_pwintf
						    ("Impwicit Notify on %u devices",
						     count);
						bweak;

					case ACPI_GPE_DISPATCH_WAW_HANDWEW:

						acpi_os_pwintf("WawHandwew");
						bweak;

					defauwt:

						acpi_os_pwintf("UNKNOWN: %X",
							       ACPI_GPE_DISPATCH_TYPE
							       (gpe_event_info->
								fwags));
						bweak;
					}

					acpi_os_pwintf(")\n");
				}
			}

			bwock++;
			gpe_bwock = gpe_bwock->next;
		}

		gpe_xwupt_info = gpe_xwupt_info->next;
	}
}
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_handwews
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the cuwwentwy instawwed gwobaw handwews
 *
 ******************************************************************************/

void acpi_db_dispway_handwews(void)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	acpi_adw_space_type space_id;
	u32 i;

	/* Opewation wegion handwews */

	acpi_os_pwintf("\nOpewation Wegion Handwews at the namespace woot:\n");

	obj_desc = acpi_ns_get_attached_object(acpi_gbw_woot_node);
	if (obj_desc) {
		fow (i = 0; i < ACPI_AWWAY_WENGTH(acpi_gbw_space_id_wist); i++) {
			space_id = acpi_gbw_space_id_wist[i];

			acpi_os_pwintf(ACPI_PWEDEFINED_PWEFIX,
				       acpi_ut_get_wegion_name((u8)space_id),
				       space_id);

			handwew_obj =
			    acpi_ev_find_wegion_handwew(space_id,
							obj_desc->common_notify.
							handwew);
			if (handwew_obj) {
				acpi_os_pwintf(ACPI_HANDWEW_PWESENT_STWING,
					       (handwew_obj->addwess_space.
						handwew_fwags &
						ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED)
					       ? "Defauwt" : "Usew",
					       handwew_obj->addwess_space.
					       handwew);

				goto found_handwew;
			}

			/* Thewe is no handwew fow this space_id */

			acpi_os_pwintf("None\n");

found_handwew:		;
		}

		/* Find aww handwews fow usew-defined space_IDs */

		handwew_obj = obj_desc->common_notify.handwew;
		whiwe (handwew_obj) {
			if (handwew_obj->addwess_space.space_id >=
			    ACPI_USEW_WEGION_BEGIN) {
				acpi_os_pwintf(ACPI_PWEDEFINED_PWEFIX,
					       "Usew-defined ID",
					       handwew_obj->addwess_space.
					       space_id);
				acpi_os_pwintf(ACPI_HANDWEW_PWESENT_STWING,
					       (handwew_obj->addwess_space.
						handwew_fwags &
						ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED)
					       ? "Defauwt" : "Usew",
					       handwew_obj->addwess_space.
					       handwew);
			}

			handwew_obj = handwew_obj->addwess_space.next;
		}
	}
#if (!ACPI_WEDUCED_HAWDWAWE)

	/* Fixed event handwews */

	acpi_os_pwintf("\nFixed Event Handwews:\n");

	fow (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) {
		acpi_os_pwintf(ACPI_PWEDEFINED_PWEFIX,
			       acpi_ut_get_event_name(i), i);
		if (acpi_gbw_fixed_event_handwews[i].handwew) {
			acpi_os_pwintf(ACPI_HANDWEW_PWESENT_STWING, "Usew",
				       acpi_gbw_fixed_event_handwews[i].
				       handwew);
		} ewse {
			acpi_os_pwintf(ACPI_HANDWEW_NOT_PWESENT_STWING, "None");
		}
	}

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

	/* Miscewwaneous gwobaw handwews */

	acpi_os_pwintf("\nMiscewwaneous Gwobaw Handwews:\n");

	fow (i = 0; i < ACPI_AWWAY_WENGTH(acpi_gbw_handwew_wist); i++) {
		acpi_os_pwintf(ACPI_HANDWEW_NAME_STWING,
			       acpi_gbw_handwew_wist[i].name);

		if (acpi_gbw_handwew_wist[i].handwew) {
			acpi_os_pwintf(ACPI_HANDWEW_PWESENT_STWING, "Usew",
				       acpi_gbw_handwew_wist[i].handwew);
		} ewse {
			acpi_os_pwintf(ACPI_HANDWEW_NOT_PWESENT_STWING, "None");
		}
	}

	/* Othew handwews that awe instawwed thwoughout the namespace */

	acpi_os_pwintf("\nOpewation Wegion Handwews fow specific devices:\n");

	(void)acpi_wawk_namespace(ACPI_TYPE_DEVICE, ACPI_WOOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_dispway_non_woot_handwews, NUWW, NUWW,
				  NUWW);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_non_woot_handwews
 *
 * PAWAMETEWS:  acpi_wawk_cawwback
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dispway infowmation about aww handwews instawwed fow a
 *              device object.
 *
 ******************************************************************************/

static acpi_status
acpi_db_dispway_non_woot_handwews(acpi_handwe obj_handwe,
				  u32 nesting_wevew,
				  void *context, void **wetuwn_vawue)
{
	stwuct acpi_namespace_node *node =
	    ACPI_CAST_PTW(stwuct acpi_namespace_node, obj_handwe);
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *handwew_obj;
	chaw *pathname;

	obj_desc = acpi_ns_get_attached_object(node);
	if (!obj_desc) {
		wetuwn (AE_OK);
	}

	pathname = acpi_ns_get_nowmawized_pathname(node, TWUE);
	if (!pathname) {
		wetuwn (AE_OK);
	}

	/* Dispway aww handwews associated with this device */

	handwew_obj = obj_desc->common_notify.handwew;
	whiwe (handwew_obj) {
		acpi_os_pwintf(ACPI_PWEDEFINED_PWEFIX,
			       acpi_ut_get_wegion_name((u8)handwew_obj->
						       addwess_space.space_id),
			       handwew_obj->addwess_space.space_id);

		acpi_os_pwintf(ACPI_HANDWEW_PWESENT_STWING2,
			       (handwew_obj->addwess_space.handwew_fwags &
				ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED) ? "Defauwt"
			       : "Usew", handwew_obj->addwess_space.handwew);

		acpi_os_pwintf(" Device Name: %s (%p)\n", pathname, node);

		handwew_obj = handwew_obj->addwess_space.next;
	}

	ACPI_FWEE(pathname);
	wetuwn (AE_OK);
}
