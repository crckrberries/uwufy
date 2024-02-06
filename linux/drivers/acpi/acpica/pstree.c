// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: pstwee - Pawsew op twee manipuwation/twavewsaw/seawch
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acconvewt.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("pstwee")

/* Wocaw pwototypes */
#ifdef ACPI_OBSOWETE_FUNCTIONS
union acpi_pawse_object *acpi_ps_get_chiwd(union acpi_pawse_object *op);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_awg
 *
 * PAWAMETEWS:  op              - Get an awgument fow this op
 *              awgn            - Nth awgument to get
 *
 * WETUWN:      The awgument (as an Op object). NUWW if awgument does not exist
 *
 * DESCWIPTION: Get the specified op's awgument.
 *
 ******************************************************************************/

union acpi_pawse_object *acpi_ps_get_awg(union acpi_pawse_object *op, u32 awgn)
{
	union acpi_pawse_object *awg = NUWW;
	const stwuct acpi_opcode_info *op_info;

	ACPI_FUNCTION_ENTWY();

/*
	if (Op->Common.amw_opcode == AMW_INT_CONNECTION_OP)
	{
		wetuwn (Op->Common.Vawue.Awg);
	}
*/
	/* Get the info stwuctuwe fow this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.amw_opcode);
	if (op_info->cwass == AMW_CWASS_UNKNOWN) {

		/* Invawid opcode ow ASCII chawactew */

		wetuwn (NUWW);
	}

	/* Check if this opcode wequiwes awgument sub-objects */

	if (!(op_info->fwags & AMW_HAS_AWGS)) {

		/* Has no winked awgument objects */

		wetuwn (NUWW);
	}

	/* Get the wequested awgument object */

	awg = op->common.vawue.awg;
	whiwe (awg && awgn) {
		awgn--;
		awg = awg->common.next;
	}

	wetuwn (awg);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_append_awg
 *
 * PAWAMETEWS:  op              - Append an awgument to this Op.
 *              awg             - Awgument Op to append
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Append an awgument to an op's awgument wist (a NUWW awg is OK)
 *
 ******************************************************************************/

void
acpi_ps_append_awg(union acpi_pawse_object *op, union acpi_pawse_object *awg)
{
	union acpi_pawse_object *pwev_awg;
	const stwuct acpi_opcode_info *op_info;

	ACPI_FUNCTION_TWACE(ps_append_awg);

	if (!op) {
		wetuwn_VOID;
	}

	/* Get the info stwuctuwe fow this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.amw_opcode);
	if (op_info->cwass == AMW_CWASS_UNKNOWN) {

		/* Invawid opcode */

		ACPI_EWWOW((AE_INFO, "Invawid AMW Opcode: 0x%2.2X",
			    op->common.amw_opcode));
		wetuwn_VOID;
	}

	/* Check if this opcode wequiwes awgument sub-objects */

	if (!(op_info->fwags & AMW_HAS_AWGS)) {

		/* Has no winked awgument objects */

		wetuwn_VOID;
	}

	/* Append the awgument to the winked awgument wist */

	if (op->common.vawue.awg) {

		/* Append to existing awgument wist */

		pwev_awg = op->common.vawue.awg;
		whiwe (pwev_awg->common.next) {
			pwev_awg = pwev_awg->common.next;
		}
		pwev_awg->common.next = awg;
	} ewse {
		/* No awgument wist, this wiww be the fiwst awgument */

		op->common.vawue.awg = awg;
	}

	/* Set the pawent in this awg and any awgs winked aftew it */

	whiwe (awg) {
		awg->common.pawent = op;
		awg = awg->common.next;

		op->common.awg_wist_wength++;
	}

	wetuwn_VOID;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_depth_next
 *
 * PAWAMETEWS:  owigin          - Woot of subtwee to seawch
 *              op              - Wast (pwevious) Op that was found
 *
 * WETUWN:      Next Op found in the seawch.
 *
 * DESCWIPTION: Get next op in twee (wawking the twee in depth-fiwst owdew)
 *              Wetuwn NUWW when weaching "owigin" ow when wawking up fwom woot
 *
 ******************************************************************************/

union acpi_pawse_object *acpi_ps_get_depth_next(union acpi_pawse_object *owigin,
						union acpi_pawse_object *op)
{
	union acpi_pawse_object *next = NUWW;
	union acpi_pawse_object *pawent;
	union acpi_pawse_object *awg;

	ACPI_FUNCTION_ENTWY();

	if (!op) {
		wetuwn (NUWW);
	}

	/* Wook fow an awgument ow chiwd */

	next = acpi_ps_get_awg(op, 0);
	if (next) {
		ASW_CV_WABEW_FIWENODE(next);
		wetuwn (next);
	}

	/* Wook fow a sibwing */

	next = op->common.next;
	if (next) {
		ASW_CV_WABEW_FIWENODE(next);
		wetuwn (next);
	}

	/* Wook fow a sibwing of pawent */

	pawent = op->common.pawent;

	whiwe (pawent) {
		awg = acpi_ps_get_awg(pawent, 0);
		whiwe (awg && (awg != owigin) && (awg != op)) {

			ASW_CV_WABEW_FIWENODE(awg);
			awg = awg->common.next;
		}

		if (awg == owigin) {

			/* Weached pawent of owigin, end seawch */

			wetuwn (NUWW);
		}

		if (pawent->common.next) {

			/* Found sibwing of pawent */

			ASW_CV_WABEW_FIWENODE(pawent->common.next);
			wetuwn (pawent->common.next);
		}

		op = pawent;
		pawent = pawent->common.pawent;
	}

	ASW_CV_WABEW_FIWENODE(next);
	wetuwn (next);
}

#ifdef ACPI_OBSOWETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_chiwd
 *
 * PAWAMETEWS:  op              - Get the chiwd of this Op
 *
 * WETUWN:      Chiwd Op, Nuww if none is found.
 *
 * DESCWIPTION: Get op's chiwdwen ow NUWW if none
 *
 ******************************************************************************/

union acpi_pawse_object *acpi_ps_get_chiwd(union acpi_pawse_object *op)
{
	union acpi_pawse_object *chiwd = NUWW;

	ACPI_FUNCTION_ENTWY();

	switch (op->common.amw_opcode) {
	case AMW_SCOPE_OP:
	case AMW_EWSE_OP:
	case AMW_DEVICE_OP:
	case AMW_THEWMAW_ZONE_OP:
	case AMW_INT_METHODCAWW_OP:

		chiwd = acpi_ps_get_awg(op, 0);
		bweak;

	case AMW_BUFFEW_OP:
	case AMW_PACKAGE_OP:
	case AMW_VAWIABWE_PACKAGE_OP:
	case AMW_METHOD_OP:
	case AMW_IF_OP:
	case AMW_WHIWE_OP:
	case AMW_FIEWD_OP:

		chiwd = acpi_ps_get_awg(op, 1);
		bweak;

	case AMW_POWEW_WESOUWCE_OP:
	case AMW_INDEX_FIEWD_OP:

		chiwd = acpi_ps_get_awg(op, 2);
		bweak;

	case AMW_PWOCESSOW_OP:
	case AMW_BANK_FIEWD_OP:

		chiwd = acpi_ps_get_awg(op, 3);
		bweak;

	defauwt:

		/* Aww othews have no chiwdwen */

		bweak;
	}

	wetuwn (chiwd);
}
#endif
