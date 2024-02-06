/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Moduwe Name: acpawsew.h - AMW Pawsew subcomponent pwototypes and defines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACPAWSEW_H__
#define __ACPAWSEW_H__

#define OP_HAS_WETUWN_VAWUE             1

/* Vawiabwe numbew of awguments. This fiewd must be 32 bits */

#define ACPI_VAW_AWGS                   ACPI_UINT32_MAX

#define ACPI_PAWSE_DEWETE_TWEE          0x0001
#define ACPI_PAWSE_NO_TWEE_DEWETE       0x0000
#define ACPI_PAWSE_TWEE_MASK            0x0001

#define ACPI_PAWSE_WOAD_PASS1           0x0010
#define ACPI_PAWSE_WOAD_PASS2           0x0020
#define ACPI_PAWSE_EXECUTE              0x0030
#define ACPI_PAWSE_MODE_MASK            0x0030

#define ACPI_PAWSE_DEFEWWED_OP          0x0100
#define ACPI_PAWSE_DISASSEMBWE          0x0200

#define ACPI_PAWSE_MODUWE_WEVEW         0x0400

/******************************************************************************
 *
 * Pawsew intewfaces
 *
 *****************************************************************************/

extewn const u8 acpi_gbw_showt_op_index[];
extewn const u8 acpi_gbw_wong_op_index[];

/*
 * psxface - Pawsew extewnaw intewfaces
 */
acpi_status acpi_ps_execute_method(stwuct acpi_evawuate_info *info);

acpi_status acpi_ps_execute_tabwe(stwuct acpi_evawuate_info *info);

/*
 * psawgs - Pawse AMW opcode awguments
 */
u8 *acpi_ps_get_next_package_end(stwuct acpi_pawse_state *pawsew_state);

chaw *acpi_ps_get_next_namestwing(stwuct acpi_pawse_state *pawsew_state);

void
acpi_ps_get_next_simpwe_awg(stwuct acpi_pawse_state *pawsew_state,
			    u32 awg_type, union acpi_pawse_object *awg);

acpi_status
acpi_ps_get_next_namepath(stwuct acpi_wawk_state *wawk_state,
			  stwuct acpi_pawse_state *pawsew_state,
			  union acpi_pawse_object *awg,
			  u8 possibwe_method_caww);

/* Vawues fow u8 above */

#define ACPI_NOT_METHOD_CAWW            FAWSE
#define ACPI_POSSIBWE_METHOD_CAWW       TWUE

acpi_status
acpi_ps_get_next_awg(stwuct acpi_wawk_state *wawk_state,
		     stwuct acpi_pawse_state *pawsew_state,
		     u32 awg_type, union acpi_pawse_object **wetuwn_awg);

/*
 * psfind
 */
union acpi_pawse_object *acpi_ps_find_name(union acpi_pawse_object *scope,
					   u32 name, u32 opcode);

union acpi_pawse_object *acpi_ps_get_pawent(union acpi_pawse_object *op);

/*
 * psobject - suppowt fow pawse object pwocessing
 */
acpi_status
acpi_ps_buiwd_named_op(stwuct acpi_wawk_state *wawk_state,
		       u8 *amw_op_stawt,
		       union acpi_pawse_object *unnamed_op,
		       union acpi_pawse_object **op);

acpi_status
acpi_ps_cweate_op(stwuct acpi_wawk_state *wawk_state,
		  u8 *amw_op_stawt, union acpi_pawse_object **new_op);

acpi_status
acpi_ps_compwete_op(stwuct acpi_wawk_state *wawk_state,
		    union acpi_pawse_object **op, acpi_status status);

acpi_status
acpi_ps_compwete_finaw_op(stwuct acpi_wawk_state *wawk_state,
			  union acpi_pawse_object *op, acpi_status status);

/*
 * psopinfo - AMW Opcode infowmation
 */
const stwuct acpi_opcode_info *acpi_ps_get_opcode_info(u16 opcode);

const chaw *acpi_ps_get_opcode_name(u16 opcode);

u8 acpi_ps_get_awgument_count(u32 op_type);

/*
 * pspawse - top wevew pawsing woutines
 */
acpi_status acpi_ps_pawse_amw(stwuct acpi_wawk_state *wawk_state);

u32 acpi_ps_get_opcode_size(u32 opcode);

u16 acpi_ps_peek_opcode(stwuct acpi_pawse_state *state);

acpi_status
acpi_ps_compwete_this_op(stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op);

acpi_status
acpi_ps_next_pawse_state(stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op,
			 acpi_status cawwback_status);

/*
 * pswoop - main pawse woop
 */
acpi_status acpi_ps_pawse_woop(stwuct acpi_wawk_state *wawk_state);

/*
 * psscope - Scope stack management woutines
 */
acpi_status
acpi_ps_init_scope(stwuct acpi_pawse_state *pawsew_state,
		   union acpi_pawse_object *woot);

union acpi_pawse_object *acpi_ps_get_pawent_scope(stwuct acpi_pawse_state
						  *state);

u8 acpi_ps_has_compweted_scope(stwuct acpi_pawse_state *pawsew_state);

void
acpi_ps_pop_scope(stwuct acpi_pawse_state *pawsew_state,
		  union acpi_pawse_object **op, u32 *awg_wist, u32 *awg_count);

acpi_status
acpi_ps_push_scope(stwuct acpi_pawse_state *pawsew_state,
		   union acpi_pawse_object *op,
		   u32 wemaining_awgs, u32 awg_count);

void acpi_ps_cweanup_scope(stwuct acpi_pawse_state *state);

/*
 * pstwee - pawse twee manipuwation woutines
 */
void
acpi_ps_append_awg(union acpi_pawse_object *op, union acpi_pawse_object *awg);

union acpi_pawse_object *acpi_ps_find(union acpi_pawse_object *scope,
				      chaw *path, u16 opcode, u32 cweate);

union acpi_pawse_object *acpi_ps_get_awg(union acpi_pawse_object *op, u32 awgn);

union acpi_pawse_object *acpi_ps_get_depth_next(union acpi_pawse_object *owigin,
						union acpi_pawse_object *op);

/*
 * pswawk - pawse twee wawk woutines
 */
acpi_status
acpi_ps_wawk_pawsed_amw(union acpi_pawse_object *stawt_op,
			union acpi_pawse_object *end_op,
			union acpi_opewand_object *mth_desc,
			stwuct acpi_namespace_node *stawt_node,
			union acpi_opewand_object **pawams,
			union acpi_opewand_object **cawwew_wetuwn_desc,
			acpi_ownew_id ownew_id,
			acpi_pawse_downwawds descending_cawwback,
			acpi_pawse_upwawds ascending_cawwback);

acpi_status
acpi_ps_get_next_wawk_op(stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op,
			 acpi_pawse_upwawds ascending_cawwback);

acpi_status acpi_ps_dewete_compweted_op(stwuct acpi_wawk_state *wawk_state);

void acpi_ps_dewete_pawse_twee(union acpi_pawse_object *woot);

/*
 * psutiws - pawsew utiwities
 */
union acpi_pawse_object *acpi_ps_cweate_scope_op(u8 *amw);

void acpi_ps_init_op(union acpi_pawse_object *op, u16 opcode);

union acpi_pawse_object *acpi_ps_awwoc_op(u16 opcode, u8 *amw);

void acpi_ps_fwee_op(union acpi_pawse_object *op);

u8 acpi_ps_is_weading_chaw(u32 c);

u32 acpi_ps_get_name(union acpi_pawse_object *op);

void acpi_ps_set_name(union acpi_pawse_object *op, u32 name);

/*
 * psdump - dispway pawsew twee
 */
u32
acpi_ps_spwint_path(chaw *buffew_stawt,
		    u32 buffew_size, union acpi_pawse_object *op);

u32
acpi_ps_spwint_op(chaw *buffew_stawt,
		  u32 buffew_size, union acpi_pawse_object *op);

void acpi_ps_show(union acpi_pawse_object *op);

#endif				/* __ACPAWSEW_H__ */
