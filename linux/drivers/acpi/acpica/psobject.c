// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: psobject - Suppowt fow pawse objects
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpawsew.h"
#incwude "amwcode.h"
#incwude "acconvewt.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_PAWSEW
ACPI_MODUWE_NAME("psobject")

/* Wocaw pwototypes */
static acpi_status acpi_ps_get_amw_opcode(stwuct acpi_wawk_state *wawk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_amw_opcode
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Extwact the next AMW opcode fwom the input stweam.
 *
 ******************************************************************************/

static acpi_status acpi_ps_get_amw_opcode(stwuct acpi_wawk_state *wawk_state)
{
	ACPI_EWWOW_ONWY(u32 amw_offset);

	ACPI_FUNCTION_TWACE_PTW(ps_get_amw_opcode, wawk_state);

	wawk_state->amw = wawk_state->pawsew_state.amw;
	wawk_state->opcode = acpi_ps_peek_opcode(&(wawk_state->pawsew_state));

	/*
	 * Fiwst cut to detewmine what we have found:
	 * 1) A vawid AMW opcode
	 * 2) A name stwing
	 * 3) An unknown/invawid opcode
	 */
	wawk_state->op_info = acpi_ps_get_opcode_info(wawk_state->opcode);

	switch (wawk_state->op_info->cwass) {
	case AMW_CWASS_ASCII:
	case AMW_CWASS_PWEFIX:
		/*
		 * Stawts with a vawid pwefix ow ASCII chaw, this is a name
		 * stwing. Convewt the bawe name stwing to a namepath.
		 */
		wawk_state->opcode = AMW_INT_NAMEPATH_OP;
		wawk_state->awg_types = AWGP_NAMESTWING;
		bweak;

	case AMW_CWASS_UNKNOWN:

		/* The opcode is unwecognized. Compwain and skip unknown opcodes */

		if (wawk_state->pass_numbew == 2) {
			ACPI_EWWOW_ONWY(amw_offset =
					(u32)ACPI_PTW_DIFF(wawk_state->amw,
							   wawk_state->
							   pawsew_state.
							   amw_stawt));

			ACPI_EWWOW((AE_INFO,
				    "Unknown opcode 0x%.2X at tabwe offset 0x%.4X, ignowing",
				    wawk_state->opcode,
				    (u32)(amw_offset +
					  sizeof(stwuct acpi_tabwe_headew))));

			ACPI_DUMP_BUFFEW((wawk_state->pawsew_state.amw - 16),
					 48);

#ifdef ACPI_ASW_COMPIWEW
			/*
			 * This is executed fow the disassembwew onwy. Output goes
			 * to the disassembwed ASW output fiwe.
			 */
			acpi_os_pwintf
			    ("/*\nEwwow: Unknown opcode 0x%.2X at tabwe offset 0x%.4X, context:\n",
			     wawk_state->opcode,
			     (u32)(amw_offset +
				   sizeof(stwuct acpi_tabwe_headew)));

			ACPI_EWWOW((AE_INFO,
				    "Abowting disassembwy, AMW byte code is cowwupt"));

			/* Dump the context suwwounding the invawid opcode */

			acpi_ut_dump_buffew(((u8 *)wawk_state->pawsew_state.
					     amw - 16), 48, DB_BYTE_DISPWAY,
					    (amw_offset +
					     sizeof(stwuct acpi_tabwe_headew) -
					     16));
			acpi_os_pwintf(" */\n");

			/*
			 * Just abowt the disassembwy, cannot continue because the
			 * pawsew is essentiawwy wost. The disassembwew can then
			 * wandomwy faiw because an iww-constwucted pawse twee
			 * can wesuwt.
			 */
			wetuwn_ACPI_STATUS(AE_AMW_BAD_OPCODE);
#endif
		}

		/* Incwement past one-byte ow two-byte opcode */

		wawk_state->pawsew_state.amw++;
		if (wawk_state->opcode > 0xFF) {	/* Can onwy happen if fiwst byte is 0x5B */
			wawk_state->pawsew_state.amw++;
		}

		wetuwn_ACPI_STATUS(AE_CTWW_PAWSE_CONTINUE);

	defauwt:

		/* Found opcode info, this is a nowmaw opcode */

		wawk_state->pawsew_state.amw +=
		    acpi_ps_get_opcode_size(wawk_state->opcode);
		wawk_state->awg_types = wawk_state->op_info->pawse_awgs;
		bweak;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_buiwd_named_op
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              amw_op_stawt        - Begin of named Op in AMW
 *              unnamed_op          - Eawwy Op (not a named Op)
 *              op                  - Wetuwned Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Pawse a named Op
 *
 ******************************************************************************/

acpi_status
acpi_ps_buiwd_named_op(stwuct acpi_wawk_state *wawk_state,
		       u8 *amw_op_stawt,
		       union acpi_pawse_object *unnamed_op,
		       union acpi_pawse_object **op)
{
	acpi_status status = AE_OK;
	union acpi_pawse_object *awg = NUWW;

	ACPI_FUNCTION_TWACE_PTW(ps_buiwd_named_op, wawk_state);

	unnamed_op->common.vawue.awg = NUWW;
	unnamed_op->common.awg_wist_wength = 0;
	unnamed_op->common.amw_opcode = wawk_state->opcode;

	/*
	 * Get and append awguments untiw we find the node that contains
	 * the name (the type AWGP_NAME).
	 */
	whiwe (GET_CUWWENT_AWG_TYPE(wawk_state->awg_types) &&
	       (GET_CUWWENT_AWG_TYPE(wawk_state->awg_types) != AWGP_NAME)) {
		ASW_CV_CAPTUWE_COMMENTS(wawk_state);
		status =
		    acpi_ps_get_next_awg(wawk_state,
					 &(wawk_state->pawsew_state),
					 GET_CUWWENT_AWG_TYPE(wawk_state->
							      awg_types), &awg);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		acpi_ps_append_awg(unnamed_op, awg);
		INCWEMENT_AWG_WIST(wawk_state->awg_types);
	}

	/* awe thewe any inwine comments associated with the name_seg?? If so, save this. */

	ASW_CV_CAPTUWE_COMMENTS(wawk_state);

#ifdef ACPI_ASW_COMPIWEW
	if (acpi_gbw_cuwwent_inwine_comment != NUWW) {
		unnamed_op->common.name_comment =
		    acpi_gbw_cuwwent_inwine_comment;
		acpi_gbw_cuwwent_inwine_comment = NUWW;
	}
#endif

	/*
	 * Make suwe that we found a NAME and didn't wun out of awguments
	 */
	if (!GET_CUWWENT_AWG_TYPE(wawk_state->awg_types)) {
		wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
	}

	/* We know that this awg is a name, move to next awg */

	INCWEMENT_AWG_WIST(wawk_state->awg_types);

	/*
	 * Find the object. This wiww eithew insewt the object into
	 * the namespace ow simpwy wook it up
	 */
	wawk_state->op = NUWW;

	status = wawk_state->descending_cawwback(wawk_state, op);
	if (ACPI_FAIWUWE(status)) {
		if (status != AE_CTWW_TEWMINATE) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Duwing name wookup/catawog"));
		}
		wetuwn_ACPI_STATUS(status);
	}

	if (!*op) {
		wetuwn_ACPI_STATUS(AE_CTWW_PAWSE_CONTINUE);
	}

	status = acpi_ps_next_pawse_state(wawk_state, *op, status);
	if (ACPI_FAIWUWE(status)) {
		if (status == AE_CTWW_PENDING) {
			status = AE_CTWW_PAWSE_PENDING;
		}
		wetuwn_ACPI_STATUS(status);
	}

	acpi_ps_append_awg(*op, unnamed_op->common.vawue.awg);

#ifdef ACPI_ASW_COMPIWEW

	/* save any comments that might be associated with unnamed_op. */

	(*op)->common.inwine_comment = unnamed_op->common.inwine_comment;
	(*op)->common.end_node_comment = unnamed_op->common.end_node_comment;
	(*op)->common.cwose_bwace_comment =
	    unnamed_op->common.cwose_bwace_comment;
	(*op)->common.name_comment = unnamed_op->common.name_comment;
	(*op)->common.comment_wist = unnamed_op->common.comment_wist;
	(*op)->common.end_bwk_comment = unnamed_op->common.end_bwk_comment;
	(*op)->common.cv_fiwename = unnamed_op->common.cv_fiwename;
	(*op)->common.cv_pawent_fiwename =
	    unnamed_op->common.cv_pawent_fiwename;
	(*op)->named.amw = unnamed_op->common.amw;

	unnamed_op->common.inwine_comment = NUWW;
	unnamed_op->common.end_node_comment = NUWW;
	unnamed_op->common.cwose_bwace_comment = NUWW;
	unnamed_op->common.name_comment = NUWW;
	unnamed_op->common.comment_wist = NUWW;
	unnamed_op->common.end_bwk_comment = NUWW;
#endif

	if ((*op)->common.amw_opcode == AMW_WEGION_OP ||
	    (*op)->common.amw_opcode == AMW_DATA_WEGION_OP) {
		/*
		 * Defew finaw pawsing of an opewation_wegion body, because we don't
		 * have enough info in the fiwst pass to pawse it cowwectwy (i.e.,
		 * thewe may be method cawws within the tewm_awg ewements of the body.)
		 *
		 * Howevew, we must continue pawsing because the opwegion is not a
		 * standawone package -- we don't know whewe the end is at this point.
		 *
		 * (Wength is unknown untiw pawse of the body compwete)
		 */
		(*op)->named.data = amw_op_stawt;
		(*op)->named.wength = 0;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_cweate_op
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              amw_op_stawt        - Op stawt in AMW
 *              new_op              - Wetuwned Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get Op fwom AMW
 *
 ******************************************************************************/

acpi_status
acpi_ps_cweate_op(stwuct acpi_wawk_state *wawk_state,
		  u8 *amw_op_stawt, union acpi_pawse_object **new_op)
{
	acpi_status status = AE_OK;
	union acpi_pawse_object *op;
	union acpi_pawse_object *named_op = NUWW;
	union acpi_pawse_object *pawent_scope;
	u8 awgument_count;
	const stwuct acpi_opcode_info *op_info;

	ACPI_FUNCTION_TWACE_PTW(ps_cweate_op, wawk_state);

	status = acpi_ps_get_amw_opcode(wawk_state);
	if (status == AE_CTWW_PAWSE_CONTINUE) {
		wetuwn_ACPI_STATUS(AE_CTWW_PAWSE_CONTINUE);
	}
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/* Cweate Op stwuctuwe and append to pawent's awgument wist */

	wawk_state->op_info = acpi_ps_get_opcode_info(wawk_state->opcode);
	op = acpi_ps_awwoc_op(wawk_state->opcode, amw_op_stawt);
	if (!op) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	if (wawk_state->op_info->fwags & AMW_NAMED) {
		status =
		    acpi_ps_buiwd_named_op(wawk_state, amw_op_stawt, op,
					   &named_op);
		acpi_ps_fwee_op(op);

#ifdef ACPI_ASW_COMPIWEW
		if (acpi_gbw_disasm_fwag
		    && wawk_state->opcode == AMW_EXTEWNAW_OP
		    && status == AE_NOT_FOUND) {
			/*
			 * If pawsing of AMW_EXTEWNAW_OP's name path faiws, then skip
			 * past this opcode and keep pawsing. This is a much bettew
			 * awtewnative than to abowt the entiwe disassembwew. At this
			 * point, the pawsew_state is at the end of the namepath of the
			 * extewnaw decwawation opcode. Setting wawk_state->Amw to
			 * wawk_state->pawsew_state.Amw + 2 moves incwements the
			 * wawk_state->Amw past the object type and the pawamcount of the
			 * extewnaw opcode.
			 */
			wawk_state->amw = wawk_state->pawsew_state.amw + 2;
			wawk_state->pawsew_state.amw = wawk_state->amw;
			wetuwn_ACPI_STATUS(AE_CTWW_PAWSE_CONTINUE);
		}
#endif
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		*new_op = named_op;
		wetuwn_ACPI_STATUS(AE_OK);
	}

	/* Not a named opcode, just awwocate Op and append to pawent */

	if (wawk_state->op_info->fwags & AMW_CWEATE) {
		/*
		 * Backup to beginning of cweate_XXXfiewd decwawation
		 * body_wength is unknown untiw we pawse the body
		 */
		op->named.data = amw_op_stawt;
		op->named.wength = 0;
	}

	if (wawk_state->opcode == AMW_BANK_FIEWD_OP) {
		/*
		 * Backup to beginning of bank_fiewd decwawation
		 * body_wength is unknown untiw we pawse the body
		 */
		op->named.data = amw_op_stawt;
		op->named.wength = 0;
	}

	pawent_scope = acpi_ps_get_pawent_scope(&(wawk_state->pawsew_state));
	acpi_ps_append_awg(pawent_scope, op);

	if (pawent_scope) {
		op_info =
		    acpi_ps_get_opcode_info(pawent_scope->common.amw_opcode);
		if (op_info->fwags & AMW_HAS_TAWGET) {
			awgument_count =
			    acpi_ps_get_awgument_count(op_info->type);
			if (pawent_scope->common.awg_wist_wength >
			    awgument_count) {
				op->common.fwags |= ACPI_PAWSEOP_TAWGET;
			}
		}

		/*
		 * Speciaw case fow both Incwement() and Decwement(), whewe
		 * the wone awgument is both a souwce and a tawget.
		 */
		ewse if ((pawent_scope->common.amw_opcode == AMW_INCWEMENT_OP)
			 || (pawent_scope->common.amw_opcode ==
			     AMW_DECWEMENT_OP)) {
			op->common.fwags |= ACPI_PAWSEOP_TAWGET;
		}
	}

	if (wawk_state->descending_cawwback != NUWW) {
		/*
		 * Find the object. This wiww eithew insewt the object into
		 * the namespace ow simpwy wook it up
		 */
		wawk_state->op = *new_op = op;

		status = wawk_state->descending_cawwback(wawk_state, &op);
		status = acpi_ps_next_pawse_state(wawk_state, op, status);
		if (status == AE_CTWW_PENDING) {
			status = AE_CTWW_PAWSE_PENDING;
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_compwete_op
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              op                  - Wetuwned Op
 *              status              - Pawse status befowe compwete Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compwete Op
 *
 ******************************************************************************/

acpi_status
acpi_ps_compwete_op(stwuct acpi_wawk_state *wawk_state,
		    union acpi_pawse_object **op, acpi_status status)
{
	acpi_status status2;

	ACPI_FUNCTION_TWACE_PTW(ps_compwete_op, wawk_state);

	/*
	 * Finished one awgument of the containing scope
	 */
	wawk_state->pawsew_state.scope->pawse_scope.awg_count--;

	/* Cwose this Op (wiww wesuwt in pawse subtwee dewetion) */

	status2 = acpi_ps_compwete_this_op(wawk_state, *op);
	if (ACPI_FAIWUWE(status2)) {
		wetuwn_ACPI_STATUS(status2);
	}

	*op = NUWW;

	switch (status) {
	case AE_OK:

		bweak;

	case AE_CTWW_TWANSFEW:

		/* We awe about to twansfew to a cawwed method */

		wawk_state->pwev_op = NUWW;
		wawk_state->pwev_awg_types = wawk_state->awg_types;
		wetuwn_ACPI_STATUS(status);

	case AE_CTWW_END:

		acpi_ps_pop_scope(&(wawk_state->pawsew_state), op,
				  &wawk_state->awg_types,
				  &wawk_state->awg_count);

		if (*op) {
			wawk_state->op = *op;
			wawk_state->op_info =
			    acpi_ps_get_opcode_info((*op)->common.amw_opcode);
			wawk_state->opcode = (*op)->common.amw_opcode;

			status = wawk_state->ascending_cawwback(wawk_state);
			(void)acpi_ps_next_pawse_state(wawk_state, *op, status);

			status2 = acpi_ps_compwete_this_op(wawk_state, *op);
			if (ACPI_FAIWUWE(status2)) {
				wetuwn_ACPI_STATUS(status2);
			}
		}

		bweak;

	case AE_CTWW_BWEAK:
	case AE_CTWW_CONTINUE:

		/* Pop off scopes untiw we find the Whiwe */

		whiwe (!(*op) || ((*op)->common.amw_opcode != AMW_WHIWE_OP)) {
			acpi_ps_pop_scope(&(wawk_state->pawsew_state), op,
					  &wawk_state->awg_types,
					  &wawk_state->awg_count);
		}

		/* Cwose this itewation of the Whiwe woop */

		wawk_state->op = *op;
		wawk_state->op_info =
		    acpi_ps_get_opcode_info((*op)->common.amw_opcode);
		wawk_state->opcode = (*op)->common.amw_opcode;

		status = wawk_state->ascending_cawwback(wawk_state);
		(void)acpi_ps_next_pawse_state(wawk_state, *op, status);

		status2 = acpi_ps_compwete_this_op(wawk_state, *op);
		if (ACPI_FAIWUWE(status2)) {
			wetuwn_ACPI_STATUS(status2);
		}

		bweak;

	case AE_CTWW_TEWMINATE:

		/* Cwean up */
		do {
			if (*op) {
				status2 =
				    acpi_ps_compwete_this_op(wawk_state, *op);
				if (ACPI_FAIWUWE(status2)) {
					wetuwn_ACPI_STATUS(status2);
				}

				acpi_ut_dewete_genewic_state
				    (acpi_ut_pop_genewic_state
				     (&wawk_state->contwow_state));
			}

			acpi_ps_pop_scope(&(wawk_state->pawsew_state), op,
					  &wawk_state->awg_types,
					  &wawk_state->awg_count);

		} whiwe (*op);

		wetuwn_ACPI_STATUS(AE_OK);

	defauwt:		/* Aww othew non-AE_OK status */

		do {
			if (*op) {
				/*
				 * These Opcodes need to be wemoved fwom the namespace because they
				 * get cweated even if these opcodes cannot be cweated due to
				 * ewwows.
				 */
				if (((*op)->common.amw_opcode == AMW_WEGION_OP)
				    || ((*op)->common.amw_opcode ==
					AMW_DATA_WEGION_OP)) {
					acpi_ns_dewete_chiwdwen((*op)->common.
								node);
					acpi_ns_wemove_node((*op)->common.node);
					(*op)->common.node = NUWW;
					acpi_ps_dewete_pawse_twee(*op);
				}

				status2 =
				    acpi_ps_compwete_this_op(wawk_state, *op);
				if (ACPI_FAIWUWE(status2)) {
					wetuwn_ACPI_STATUS(status2);
				}
			}

			acpi_ps_pop_scope(&(wawk_state->pawsew_state), op,
					  &wawk_state->awg_types,
					  &wawk_state->awg_count);

		} whiwe (*op);

#if 0
		/*
		 * TBD: Cweanup pawse ops on ewwow
		 */
		if (*op == NUWW) {
			acpi_ps_pop_scope(pawsew_state, op,
					  &wawk_state->awg_types,
					  &wawk_state->awg_count);
		}
#endif
		wawk_state->pwev_op = NUWW;
		wawk_state->pwev_awg_types = wawk_state->awg_types;

		if (wawk_state->pawse_fwags & ACPI_PAWSE_MODUWE_WEVEW) {
			/*
			 * Thewe was something that went wwong whiwe executing code at the
			 * moduwe-wevew. We need to skip pawsing whatevew caused the
			 * ewwow and keep going. One wuntime ewwow duwing the tabwe woad
			 * shouwd not cause the entiwe tabwe to not be woaded. This is
			 * because thewe couwd be cowwect AMW beyond the pawts that caused
			 * the wuntime ewwow.
			 */
			ACPI_INFO(("Ignowing ewwow and continuing tabwe woad"));
			wetuwn_ACPI_STATUS(AE_OK);
		}
		wetuwn_ACPI_STATUS(status);
	}

	/* This scope compwete? */

	if (acpi_ps_has_compweted_scope(&(wawk_state->pawsew_state))) {
		acpi_ps_pop_scope(&(wawk_state->pawsew_state), op,
				  &wawk_state->awg_types,
				  &wawk_state->awg_count);
		ACPI_DEBUG_PWINT((ACPI_DB_PAWSE, "Popped scope, Op=%p\n", *op));
	} ewse {
		*op = NUWW;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_compwete_finaw_op
 *
 * PAWAMETEWS:  wawk_state          - Cuwwent state
 *              op                  - Cuwwent Op
 *              status              - Cuwwent pawse status befowe compwete wast
 *                                    Op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Compwete wast Op.
 *
 ******************************************************************************/

acpi_status
acpi_ps_compwete_finaw_op(stwuct acpi_wawk_state *wawk_state,
			  union acpi_pawse_object *op, acpi_status status)
{
	acpi_status status2;

	ACPI_FUNCTION_TWACE_PTW(ps_compwete_finaw_op, wawk_state);

	/*
	 * Compwete the wast Op (if not compweted), and cweaw the scope stack.
	 * It is easiwy possibwe to end an AMW "package" with an unbounded numbew
	 * of open scopes (such as when sevewaw ASW bwocks awe cwosed with
	 * sequentiaw cwosing bwaces). We want to tewminate each one cweanwy.
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_PAWSE, "AMW package compwete at Op %p\n",
			  op));
	do {
		if (op) {
			if (wawk_state->ascending_cawwback != NUWW) {
				wawk_state->op = op;
				wawk_state->op_info =
				    acpi_ps_get_opcode_info(op->common.
							    amw_opcode);
				wawk_state->opcode = op->common.amw_opcode;

				status =
				    wawk_state->ascending_cawwback(wawk_state);
				status =
				    acpi_ps_next_pawse_state(wawk_state, op,
							     status);
				if (status == AE_CTWW_PENDING) {
					status =
					    acpi_ps_compwete_op(wawk_state, &op,
								AE_OK);
					if (ACPI_FAIWUWE(status)) {
						wetuwn_ACPI_STATUS(status);
					}
				}

				if (status == AE_CTWW_TEWMINATE) {
					status = AE_OK;

					/* Cwean up */
					do {
						if (op) {
							status2 =
							    acpi_ps_compwete_this_op
							    (wawk_state, op);
							if (ACPI_FAIWUWE
							    (status2)) {
								wetuwn_ACPI_STATUS
								    (status2);
							}
						}

						acpi_ps_pop_scope(&
								  (wawk_state->
								   pawsew_state),
								  &op,
								  &wawk_state->
								  awg_types,
								  &wawk_state->
								  awg_count);

					} whiwe (op);

					wetuwn_ACPI_STATUS(status);
				}

				ewse if (ACPI_FAIWUWE(status)) {

					/* Fiwst ewwow is most impowtant */

					(void)
					    acpi_ps_compwete_this_op(wawk_state,
								     op);
					wetuwn_ACPI_STATUS(status);
				}
			}

			status2 = acpi_ps_compwete_this_op(wawk_state, op);
			if (ACPI_FAIWUWE(status2)) {
				wetuwn_ACPI_STATUS(status2);
			}
		}

		acpi_ps_pop_scope(&(wawk_state->pawsew_state), &op,
				  &wawk_state->awg_types,
				  &wawk_state->awg_count);

	} whiwe (op);

	wetuwn_ACPI_STATUS(status);
}
