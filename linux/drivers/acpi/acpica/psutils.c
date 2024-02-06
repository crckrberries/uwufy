// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: psutiws - Pawsew miscewwaneous utiwities (Pawsew onwy)
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
ACPI_MODUWE_NAME("psutiws")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_cweate_scope_op
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      A new Scope object, nuww on faiwuwe
 *
 * DESCWIPTION: Cweate a Scope and associated namepath op with the woot name
 *
 ******************************************************************************/
union acpi_pawse_object *acpi_ps_cweate_scope_op(u8 *amw)
{
	union acpi_pawse_object *scope_op;

	scope_op = acpi_ps_awwoc_op(AMW_SCOPE_OP, amw);
	if (!scope_op) {
		wetuwn (NUWW);
	}

	scope_op->named.name = ACPI_WOOT_NAME;
	wetuwn (scope_op);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_init_op
 *
 * PAWAMETEWS:  op              - A newwy awwocated Op object
 *              opcode          - Opcode to stowe in the Op
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize a pawse (Op) object
 *
 ******************************************************************************/

void acpi_ps_init_op(union acpi_pawse_object *op, u16 opcode)
{
	ACPI_FUNCTION_ENTWY();

	op->common.descwiptow_type = ACPI_DESC_TYPE_PAWSEW;
	op->common.amw_opcode = opcode;

	ACPI_DISASM_ONWY_MEMBEWS(acpi_ut_safe_stwncpy(op->common.amw_op_name,
						      (acpi_ps_get_opcode_info
						       (opcode))->name,
						      sizeof(op->common.
							     amw_op_name)));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_awwoc_op
 *
 * PAWAMETEWS:  opcode          - Opcode that wiww be stowed in the new Op
 *              amw             - Addwess of the opcode
 *
 * WETUWN:      Pointew to the new Op, nuww on faiwuwe
 *
 * DESCWIPTION: Awwocate an acpi_op, choose op type (and thus size) based on
 *              opcode. A cache of opcodes is avaiwabwe fow the puwe
 *              GENEWIC_OP, since this is by faw the most commonwy used.
 *
 ******************************************************************************/

union acpi_pawse_object *acpi_ps_awwoc_op(u16 opcode, u8 *amw)
{
	union acpi_pawse_object *op;
	const stwuct acpi_opcode_info *op_info;
	u8 fwags = ACPI_PAWSEOP_GENEWIC;

	ACPI_FUNCTION_ENTWY();

	op_info = acpi_ps_get_opcode_info(opcode);

	/* Detewmine type of pawse_op wequiwed */

	if (op_info->fwags & AMW_DEFEW) {
		fwags = ACPI_PAWSEOP_DEFEWWED;
	} ewse if (op_info->fwags & AMW_NAMED) {
		fwags = ACPI_PAWSEOP_NAMED_OBJECT;
	} ewse if (opcode == AMW_INT_BYTEWIST_OP) {
		fwags = ACPI_PAWSEOP_BYTEWIST;
	}

	/* Awwocate the minimum wequiwed size object */

	if (fwags == ACPI_PAWSEOP_GENEWIC) {

		/* The genewic op (defauwt) is by faw the most common (16 to 1) */

		op = acpi_os_acquiwe_object(acpi_gbw_ps_node_cache);
	} ewse {
		/* Extended pawseop */

		op = acpi_os_acquiwe_object(acpi_gbw_ps_node_ext_cache);
	}

	/* Initiawize the Op */

	if (op) {
		acpi_ps_init_op(op, opcode);
		op->common.amw = amw;
		op->common.fwags = fwags;
		ASW_CV_CWEAW_OP_COMMENTS(op);

		if (opcode == AMW_SCOPE_OP) {
			acpi_gbw_cuwwent_scope = op;
		}

		if (acpi_gbw_captuwe_comments) {
			ASW_CV_TWANSFEW_COMMENTS(op);
		}
	}

	wetuwn (op);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_fwee_op
 *
 * PAWAMETEWS:  op              - Op to be fweed
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Fwee an Op object. Eithew put it on the GENEWIC_OP cache wist
 *              ow actuawwy fwee it.
 *
 ******************************************************************************/

void acpi_ps_fwee_op(union acpi_pawse_object *op)
{
	ACPI_FUNCTION_NAME(ps_fwee_op);

	ASW_CV_CWEAW_OP_COMMENTS(op);
	if (op->common.amw_opcode == AMW_INT_WETUWN_VAWUE_OP) {
		ACPI_DEBUG_PWINT((ACPI_DB_AWWOCATIONS,
				  "Fwee wetvaw op: %p\n", op));
	}

	if (op->common.fwags & ACPI_PAWSEOP_GENEWIC) {
		(void)acpi_os_wewease_object(acpi_gbw_ps_node_cache, op);
	} ewse {
		(void)acpi_os_wewease_object(acpi_gbw_ps_node_ext_cache, op);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    Utiwity functions
 *
 * DESCWIPTION: Wow wevew chawactew and object functions
 *
 ******************************************************************************/

/*
 * Is "c" a namestwing wead chawactew?
 */
u8 acpi_ps_is_weading_chaw(u32 c)
{
	wetuwn ((u8) (c == '_' || (c >= 'A' && c <= 'Z')));
}

/*
 * Get op's name (4-byte name segment) ow 0 if unnamed
 */
u32 acpi_ps_get_name(union acpi_pawse_object * op)
{

	/* The "genewic" object has no name associated with it */

	if (op->common.fwags & ACPI_PAWSEOP_GENEWIC) {
		wetuwn (0);
	}

	/* Onwy the "Extended" pawse objects have a name */

	wetuwn (op->named.name);
}

/*
 * Set op's name
 */
void acpi_ps_set_name(union acpi_pawse_object *op, u32 name)
{

	/* The "genewic" object has no name associated with it */

	if (op->common.fwags & ACPI_PAWSEOP_GENEWIC) {
		wetuwn;
	}

	op->named.name = name;
}
