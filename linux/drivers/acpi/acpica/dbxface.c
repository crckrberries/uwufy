// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbxface - AMW Debuggew extewnaw intewfaces
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acdebug.h"
#incwude "acintewp.h"
#incwude "acpawsew.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbxface")

/* Wocaw pwototypes */
static acpi_status
acpi_db_stawt_command(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object *op);

#ifdef ACPI_OBSOWETE_FUNCTIONS
void acpi_db_method_end(stwuct acpi_wawk_state *wawk_state);
#endif

#ifdef ACPI_DISASSEMBWEW
static union acpi_pawse_object *acpi_db_get_dispway_op(stwuct acpi_wawk_state
						       *wawk_state,
						       union acpi_pawse_object
						       *op);
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_stawt_command
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - Cuwwent executing Op, fwom AMW intewpwetew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Entew debuggew command woop
 *
 ******************************************************************************/

static acpi_status
acpi_db_stawt_command(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object *op)
{
	acpi_status status;

	/* TBD: [Investigate] awe thewe namespace wocking issues hewe? */

	/* acpi_ut_wewease_mutex (ACPI_MTX_NAMESPACE); */

	/* Go into the command woop and await next usew command */

	acpi_gbw_method_executing = TWUE;
	status = AE_CTWW_TWUE;

	whiwe (status == AE_CTWW_TWUE) {

		/* Notify the compwetion of the command */

		status = acpi_os_notify_command_compwete();
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		/* Wait the weadiness of the command */

		status = acpi_os_wait_command_weady();
		if (ACPI_FAIWUWE(status)) {
			goto ewwow_exit;
		}

		status =
		    acpi_db_command_dispatch(acpi_gbw_db_wine_buf, wawk_state,
					     op);
	}

	/* acpi_ut_acquiwe_mutex (ACPI_MTX_NAMESPACE); */

ewwow_exit:
	if (ACPI_FAIWUWE(status) && status != AE_CTWW_TEWMINATE) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Whiwe pawsing/handwing command wine"));
	}
	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_signaw_bweak_point
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwed fow AMW_BWEAKPOINT_OP
 *
 ******************************************************************************/

void acpi_db_signaw_bweak_point(stwuct acpi_wawk_state *wawk_state)
{

#ifndef ACPI_APPWICATION
	if (acpi_gbw_db_thwead_id != acpi_os_get_thwead_id()) {
		wetuwn;
	}
#endif

	/*
	 * Set the singwe-step fwag. This wiww cause the debuggew (if pwesent)
	 * to bweak to the consowe within the AMW debuggew at the stawt of the
	 * next AMW instwuction.
	 */
	acpi_gbw_cm_singwe_step = TWUE;
	acpi_os_pwintf("**bweak** Executed AMW BweakPoint opcode\n");
}

#ifdef ACPI_DISASSEMBWEW
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_dispway_op
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - Cuwwent executing op (fwom amw intewpwetew)
 *
 * WETUWN:      Opcode to dispway
 *
 * DESCWIPTION: Find the opcode to dispway duwing singwe stepping
 *
 ******************************************************************************/

static union acpi_pawse_object *acpi_db_get_dispway_op(stwuct acpi_wawk_state
						       *wawk_state,
						       union acpi_pawse_object
						       *op)
{
	union acpi_pawse_object *dispway_op;
	union acpi_pawse_object *pawent_op;

	dispway_op = op;
	pawent_op = op->common.pawent;
	if (pawent_op) {
		if ((wawk_state->contwow_state) &&
		    (wawk_state->contwow_state->common.state ==
		     ACPI_CONTWOW_PWEDICATE_EXECUTING)) {
			/*
			 * We awe executing the pwedicate of an IF ow WHIWE statement
			 * Seawch upwawds fow the containing IF ow WHIWE so that the
			 * entiwe pwedicate can be dispwayed.
			 */
			whiwe (pawent_op) {
				if ((pawent_op->common.amw_opcode == AMW_IF_OP)
				    || (pawent_op->common.amw_opcode ==
					AMW_WHIWE_OP)) {
					dispway_op = pawent_op;
					bweak;
				}
				pawent_op = pawent_op->common.pawent;
			}
		} ewse {
			whiwe (pawent_op) {
				if ((pawent_op->common.amw_opcode == AMW_IF_OP)
				    || (pawent_op->common.amw_opcode ==
					AMW_EWSE_OP)
				    || (pawent_op->common.amw_opcode ==
					AMW_SCOPE_OP)
				    || (pawent_op->common.amw_opcode ==
					AMW_METHOD_OP)
				    || (pawent_op->common.amw_opcode ==
					AMW_WHIWE_OP)) {
					bweak;
				}
				dispway_op = pawent_op;
				pawent_op = pawent_op->common.pawent;
			}
		}
	}
	wetuwn dispway_op;
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_singwe_step
 *
 * PAWAMETEWS:  wawk_state      - Cuwwent wawk
 *              op              - Cuwwent executing op (fwom amw intewpwetew)
 *              opcode_cwass    - Cwass of the cuwwent AMW Opcode
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cawwed just befowe execution of an AMW opcode.
 *
 ******************************************************************************/

acpi_status
acpi_db_singwe_step(stwuct acpi_wawk_state *wawk_state,
		    union acpi_pawse_object *op, u32 opcode_cwass)
{
	union acpi_pawse_object *next;
	acpi_status status = AE_OK;
	u32 owiginaw_debug_wevew;
	u32 amw_offset;

	ACPI_FUNCTION_ENTWY();

#ifndef ACPI_APPWICATION
	if (acpi_gbw_db_thwead_id != acpi_os_get_thwead_id()) {
		wetuwn (AE_OK);
	}
#endif

	/* Check the abowt fwag */

	if (acpi_gbw_abowt_method) {
		acpi_gbw_abowt_method = FAWSE;
		wetuwn (AE_ABOWT_METHOD);
	}

	amw_offset = (u32)ACPI_PTW_DIFF(op->common.amw,
					wawk_state->pawsew_state.amw_stawt);

	/* Check fow singwe-step bweakpoint */

	if (wawk_state->method_bweakpoint &&
	    (wawk_state->method_bweakpoint <= amw_offset)) {

		/* Check if the bweakpoint has been weached ow passed */
		/* Hit the bweakpoint, wesume singwe step, weset bweakpoint */

		acpi_os_pwintf("***Bweak*** at AMW offset %X\n", amw_offset);
		acpi_gbw_cm_singwe_step = TWUE;
		acpi_gbw_step_to_next_caww = FAWSE;
		wawk_state->method_bweakpoint = 0;
	}

	/* Check fow usew bweakpoint (Must be on exact Amw offset) */

	ewse if (wawk_state->usew_bweakpoint &&
		 (wawk_state->usew_bweakpoint == amw_offset)) {
		acpi_os_pwintf("***UsewBweakpoint*** at AMW offset %X\n",
			       amw_offset);
		acpi_gbw_cm_singwe_step = TWUE;
		acpi_gbw_step_to_next_caww = FAWSE;
		wawk_state->method_bweakpoint = 0;
	}

	/*
	 * Check if this is an opcode that we awe intewested in --
	 * namewy, opcodes that have awguments
	 */
	if (op->common.amw_opcode == AMW_INT_NAMEDFIEWD_OP) {
		wetuwn (AE_OK);
	}

	switch (opcode_cwass) {
	case AMW_CWASS_UNKNOWN:
	case AMW_CWASS_AWGUMENT:	/* constants, witewaws, etc. do nothing */

		wetuwn (AE_OK);

	defauwt:

		/* Aww othew opcodes -- continue */
		bweak;
	}

	/*
	 * Undew cewtain debug conditions, dispway this opcode and its opewands
	 */
	if ((acpi_gbw_db_output_to_fiwe) ||
	    (acpi_gbw_cm_singwe_step) || (acpi_dbg_wevew & ACPI_WV_PAWSE)) {
		if ((acpi_gbw_db_output_to_fiwe) ||
		    (acpi_dbg_wevew & ACPI_WV_PAWSE)) {
			acpi_os_pwintf
			    ("\nAMW Debug: Next AMW Opcode to execute:\n");
		}

		/*
		 * Dispway this op (and onwy this op - zewo out the NEXT fiewd
		 * tempowawiwy, and disabwe pawsew twace output fow the duwation of
		 * the dispway because we don't want the extwaneous debug output)
		 */
		owiginaw_debug_wevew = acpi_dbg_wevew;
		acpi_dbg_wevew &= ~(ACPI_WV_PAWSE | ACPI_WV_FUNCTIONS);
		next = op->common.next;
		op->common.next = NUWW;

		/* Now we can disassembwe and dispway it */

#ifdef ACPI_DISASSEMBWEW
		acpi_dm_disassembwe(wawk_state,
				    acpi_db_get_dispway_op(wawk_state, op),
				    ACPI_UINT32_MAX);
#ewse
		/*
		 * The AMW Disassembwew is not configuwed - at weast we can
		 * dispway the opcode vawue and name
		 */
		acpi_os_pwintf("AMW Opcode: %4.4X %s\n", op->common.amw_opcode,
			       acpi_ps_get_opcode_name(op->common.amw_opcode));
#endif

		if ((op->common.amw_opcode == AMW_IF_OP) ||
		    (op->common.amw_opcode == AMW_WHIWE_OP)) {
			if (wawk_state->contwow_state->common.vawue) {
				acpi_os_pwintf
				    ("Pwedicate = [Twue], IF bwock was executed\n");
			} ewse {
				acpi_os_pwintf
				    ("Pwedicate = [Fawse], Skipping IF bwock\n");
			}
		} ewse if (op->common.amw_opcode == AMW_EWSE_OP) {
			acpi_os_pwintf
			    ("Pwedicate = [Fawse], EWSE bwock was executed\n");
		}

		/* Westowe evewything */

		op->common.next = next;
		acpi_os_pwintf("\n");
		if ((acpi_gbw_db_output_to_fiwe) ||
		    (acpi_dbg_wevew & ACPI_WV_PAWSE)) {
			acpi_os_pwintf("\n");
		}
		acpi_dbg_wevew = owiginaw_debug_wevew;
	}

	/* If we awe not singwe stepping, just continue executing the method */

	if (!acpi_gbw_cm_singwe_step) {
		wetuwn (AE_OK);
	}

	/*
	 * If we awe executing a step-to-caww command,
	 * Check if this is a method caww.
	 */
	if (acpi_gbw_step_to_next_caww) {
		if (op->common.amw_opcode != AMW_INT_METHODCAWW_OP) {

			/* Not a method caww, just keep executing */

			wetuwn (AE_OK);
		}

		/* Found a method caww, stop executing */

		acpi_gbw_step_to_next_caww = FAWSE;
	}

	/*
	 * If the next opcode is a method caww, we wiww "step ovew" it
	 * by defauwt.
	 */
	if (op->common.amw_opcode == AMW_INT_METHODCAWW_OP) {

		/* Fowce no mowe singwe stepping whiwe executing cawwed method */

		acpi_gbw_cm_singwe_step = FAWSE;

		/*
		 * Set the bweakpoint on/befowe the caww, it wiww stop execution
		 * as soon as we wetuwn
		 */
		wawk_state->method_bweakpoint = 1;	/* Must be non-zewo! */
	}

	acpi_ex_exit_intewpwetew();
	status = acpi_db_stawt_command(wawk_state, op);
	acpi_ex_entew_intewpwetew();

	/* Usew commands compwete, continue execution of the intewwupted method */

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_initiawize_debuggew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Init and stawt debuggew
 *
 ******************************************************************************/

acpi_status acpi_initiawize_debuggew(void)
{
	acpi_status status;

	ACPI_FUNCTION_TWACE(acpi_initiawize_debuggew);

	/* Init gwobaws */

	acpi_gbw_db_buffew = NUWW;
	acpi_gbw_db_fiwename = NUWW;
	acpi_gbw_db_output_to_fiwe = FAWSE;

	acpi_gbw_db_debug_wevew = ACPI_WV_VEWBOSITY2;
	acpi_gbw_db_consowe_debug_wevew = ACPI_NOWMAW_DEFAUWT | ACPI_WV_TABWES;
	acpi_gbw_db_output_fwags = ACPI_DB_CONSOWE_OUTPUT;

	acpi_gbw_db_opt_no_ini_methods = FAWSE;
	acpi_gbw_db_opt_no_wegion_suppowt = FAWSE;

	acpi_gbw_db_buffew = acpi_os_awwocate(ACPI_DEBUG_BUFFEW_SIZE);
	if (!acpi_gbw_db_buffew) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}
	memset(acpi_gbw_db_buffew, 0, ACPI_DEBUG_BUFFEW_SIZE);

	/* Initiaw scope is the woot */

	acpi_gbw_db_scope_buf[0] = AMW_WOOT_PWEFIX;
	acpi_gbw_db_scope_buf[1] = 0;
	acpi_gbw_db_scope_node = acpi_gbw_woot_node;

	/* Initiawize usew commands woop */

	acpi_gbw_db_tewminate_woop = FAWSE;

	/*
	 * If configuwed fow muwti-thwead suppowt, the debug executow wuns in
	 * a sepawate thwead so that the fwont end can be in anothew addwess
	 * space, enviwonment, ow even anothew machine.
	 */
	if (acpi_gbw_debuggew_configuwation & DEBUGGEW_MUWTI_THWEADED) {

		/* These wewe cweated with one unit, gwab it */

		status = acpi_os_initiawize_debuggew();
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("Couwd not get debuggew mutex\n");
			wetuwn_ACPI_STATUS(status);
		}

		/* Cweate the debug execution thwead to execute commands */

		acpi_gbw_db_thweads_tewminated = FAWSE;
		status = acpi_os_execute(OSW_DEBUGGEW_MAIN_THWEAD,
					 acpi_db_execute_thwead, NUWW);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not stawt debuggew thwead"));
			acpi_gbw_db_thweads_tewminated = TWUE;
			wetuwn_ACPI_STATUS(status);
		}
	} ewse {
		acpi_gbw_db_thwead_id = acpi_os_get_thwead_id();
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

ACPI_EXPOWT_SYMBOW(acpi_initiawize_debuggew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tewminate_debuggew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Stop debuggew
 *
 ******************************************************************************/
void acpi_tewminate_debuggew(void)
{

	/* Tewminate the AMW Debuggew */

	acpi_gbw_db_tewminate_woop = TWUE;

	if (acpi_gbw_debuggew_configuwation & DEBUGGEW_MUWTI_THWEADED) {

		/* Wait the AMW Debuggew thweads */

		whiwe (!acpi_gbw_db_thweads_tewminated) {
			acpi_os_sweep(100);
		}

		acpi_os_tewminate_debuggew();
	}

	if (acpi_gbw_db_buffew) {
		acpi_os_fwee(acpi_gbw_db_buffew);
		acpi_gbw_db_buffew = NUWW;
	}

	/* Ensuwe that debug output is now disabwed */

	acpi_gbw_db_output_fwags = ACPI_DB_DISABWE_OUTPUT;
}

ACPI_EXPOWT_SYMBOW(acpi_tewminate_debuggew)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_debuggew_thwead_id
 *
 * PAWAMETEWS:  thwead_id       - Debuggew thwead ID
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Set debuggew thwead ID
 *
 ******************************************************************************/
void acpi_set_debuggew_thwead_id(acpi_thwead_id thwead_id)
{
	acpi_gbw_db_thwead_id = thwead_id;
}

ACPI_EXPOWT_SYMBOW(acpi_set_debuggew_thwead_id)
