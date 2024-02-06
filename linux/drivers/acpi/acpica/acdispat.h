/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acdispat.h - dispatchew (pawsew to intewpwetew intewface)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef _ACDISPAT_H_
#define _ACDISPAT_H_

#define NAMEOF_WOCAW_NTE    "__W0"
#define NAMEOF_AWG_NTE      "__A0"

/*
 * dsawgs - execution of dynamic awguments fow static objects
 */
acpi_status
acpi_ds_get_buffew_fiewd_awguments(union acpi_opewand_object *obj_desc);

acpi_status
acpi_ds_get_bank_fiewd_awguments(union acpi_opewand_object *obj_desc);

acpi_status acpi_ds_get_wegion_awguments(union acpi_opewand_object *wgn_desc);

acpi_status acpi_ds_get_buffew_awguments(union acpi_opewand_object *obj_desc);

acpi_status acpi_ds_get_package_awguments(union acpi_opewand_object *obj_desc);

/*
 * dscontwow - suppowt fow execution contwow opcodes
 */
acpi_status
acpi_ds_exec_begin_contwow_op(stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op);

acpi_status
acpi_ds_exec_end_contwow_op(stwuct acpi_wawk_state *wawk_state,
			    union acpi_pawse_object *op);

/*
 * dsopcode - suppowt fow wate opewand evawuation
 */
acpi_status
acpi_ds_evaw_buffew_fiewd_opewands(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op);

acpi_status
acpi_ds_evaw_wegion_opewands(stwuct acpi_wawk_state *wawk_state,
			     union acpi_pawse_object *op);

acpi_status
acpi_ds_evaw_tabwe_wegion_opewands(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op);

acpi_status
acpi_ds_evaw_data_object_opewands(stwuct acpi_wawk_state *wawk_state,
				  union acpi_pawse_object *op,
				  union acpi_opewand_object *obj_desc);

acpi_status
acpi_ds_evaw_bank_fiewd_opewands(stwuct acpi_wawk_state *wawk_state,
				 union acpi_pawse_object *op);

acpi_status acpi_ds_initiawize_wegion(acpi_handwe obj_handwe);

/*
 * dsexec - Pawsew/Intewpwetew intewface, method execution cawwbacks
 */
acpi_status
acpi_ds_get_pwedicate_vawue(stwuct acpi_wawk_state *wawk_state,
			    union acpi_opewand_object *wesuwt_obj);

acpi_status
acpi_ds_exec_begin_op(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object **out_op);

acpi_status acpi_ds_exec_end_op(stwuct acpi_wawk_state *state);

/*
 * dsfiewd - Pawsew/Intewpwetew intewface fow AMW fiewds
 */
acpi_status
acpi_ds_cweate_fiewd(union acpi_pawse_object *op,
		     stwuct acpi_namespace_node *wegion_node,
		     stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_cweate_bank_fiewd(union acpi_pawse_object *op,
			  stwuct acpi_namespace_node *wegion_node,
			  stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_cweate_index_fiewd(union acpi_pawse_object *op,
			   stwuct acpi_namespace_node *wegion_node,
			   stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_cweate_buffew_fiewd(union acpi_pawse_object *op,
			    stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_init_fiewd_objects(union acpi_pawse_object *op,
			   stwuct acpi_wawk_state *wawk_state);

/*
 * dswoad - Pawsew/Intewpwetew intewface
 */
acpi_status
acpi_ds_init_cawwbacks(stwuct acpi_wawk_state *wawk_state, u32 pass_numbew);

/* dswoad - pass 1 namespace woad cawwbacks */

acpi_status
acpi_ds_woad1_begin_op(stwuct acpi_wawk_state *wawk_state,
		       union acpi_pawse_object **out_op);

acpi_status acpi_ds_woad1_end_op(stwuct acpi_wawk_state *wawk_state);

/* dswoad - pass 2 namespace woad cawwbacks */

acpi_status
acpi_ds_woad2_begin_op(stwuct acpi_wawk_state *wawk_state,
		       union acpi_pawse_object **out_op);

acpi_status acpi_ds_woad2_end_op(stwuct acpi_wawk_state *wawk_state);

/*
 * dsmthdat - method data (wocaws/awgs)
 */
acpi_status
acpi_ds_stowe_object_to_wocaw(u8 type,
			      u32 index,
			      union acpi_opewand_object *swc_desc,
			      stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_method_data_get_entwy(u16 opcode,
			      u32 index,
			      stwuct acpi_wawk_state *wawk_state,
			      union acpi_opewand_object ***node);

void acpi_ds_method_data_dewete_aww(stwuct acpi_wawk_state *wawk_state);

u8 acpi_ds_is_method_vawue(union acpi_opewand_object *obj_desc);

acpi_status
acpi_ds_method_data_get_vawue(u8 type,
			      u32 index,
			      stwuct acpi_wawk_state *wawk_state,
			      union acpi_opewand_object **dest_desc);

acpi_status
acpi_ds_method_data_init_awgs(union acpi_opewand_object **pawams,
			      u32 max_pawam_count,
			      stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_method_data_get_node(u8 type,
			     u32 index,
			     stwuct acpi_wawk_state *wawk_state,
			     stwuct acpi_namespace_node **node);

void acpi_ds_method_data_init(stwuct acpi_wawk_state *wawk_state);

/*
 * dsmethod - Pawsew/Intewpwetew intewface - contwow method pawsing
 */
acpi_status
acpi_ds_auto_sewiawize_method(stwuct acpi_namespace_node *node,
			      union acpi_opewand_object *obj_desc);

acpi_status
acpi_ds_caww_contwow_method(stwuct acpi_thwead_state *thwead,
			    stwuct acpi_wawk_state *wawk_state,
			    union acpi_pawse_object *op);

acpi_status
acpi_ds_westawt_contwow_method(stwuct acpi_wawk_state *wawk_state,
			       union acpi_opewand_object *wetuwn_desc);

void
acpi_ds_tewminate_contwow_method(union acpi_opewand_object *method_desc,
				 stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_begin_method_execution(stwuct acpi_namespace_node *method_node,
			       union acpi_opewand_object *obj_desc,
			       stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_method_ewwow(acpi_status status, stwuct acpi_wawk_state *wawk_state);

/*
 * dsinit
 */
acpi_status
acpi_ds_initiawize_objects(u32 tabwe_index,
			   stwuct acpi_namespace_node *stawt_node);

/*
 * dsobject - Pawsew/Intewpwetew intewface - object initiawization and convewsion
 */
acpi_status
acpi_ds_buiwd_intewnaw_object(stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op,
			      union acpi_opewand_object **obj_desc_ptw);

acpi_status
acpi_ds_buiwd_intewnaw_buffew_obj(stwuct acpi_wawk_state *wawk_state,
				  union acpi_pawse_object *op,
				  u32 buffew_wength,
				  union acpi_opewand_object **obj_desc_ptw);

acpi_status
acpi_ds_buiwd_intewnaw_package_obj(stwuct acpi_wawk_state *wawk_state,
				   union acpi_pawse_object *op,
				   u32 package_wength,
				   union acpi_opewand_object **obj_desc);

acpi_status
acpi_ds_init_object_fwom_op(stwuct acpi_wawk_state *wawk_state,
			    union acpi_pawse_object *op,
			    u16 opcode, union acpi_opewand_object **obj_desc);

acpi_status
acpi_ds_cweate_node(stwuct acpi_wawk_state *wawk_state,
		    stwuct acpi_namespace_node *node,
		    union acpi_pawse_object *op);

/*
 * dspkginit - Package object initiawization
 */
acpi_status
acpi_ds_init_package_ewement(u8 object_type,
			     union acpi_opewand_object *souwce_object,
			     union acpi_genewic_state *state, void *context);

/*
 * dsutiws - Pawsew/Intewpwetew intewface utiwity woutines
 */
void acpi_ds_cweaw_impwicit_wetuwn(stwuct acpi_wawk_state *wawk_state);

u8
acpi_ds_do_impwicit_wetuwn(union acpi_opewand_object *wetuwn_desc,
			   stwuct acpi_wawk_state *wawk_state,
			   u8 add_wefewence);

u8
acpi_ds_is_wesuwt_used(union acpi_pawse_object *op,
		       stwuct acpi_wawk_state *wawk_state);

void
acpi_ds_dewete_wesuwt_if_not_used(union acpi_pawse_object *op,
				  union acpi_opewand_object *wesuwt_obj,
				  stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_cweate_opewand(stwuct acpi_wawk_state *wawk_state,
		       union acpi_pawse_object *awg, u32 awgs_wemaining);

acpi_status
acpi_ds_cweate_opewands(stwuct acpi_wawk_state *wawk_state,
			union acpi_pawse_object *fiwst_awg);

acpi_status acpi_ds_wesowve_opewands(stwuct acpi_wawk_state *wawk_state);

void acpi_ds_cweaw_opewands(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ds_evawuate_name_path(stwuct acpi_wawk_state *wawk_state);

/*
 * dswscope - Scope Stack manipuwation
 */
acpi_status
acpi_ds_scope_stack_push(stwuct acpi_namespace_node *node,
			 acpi_object_type type,
			 stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ds_scope_stack_pop(stwuct acpi_wawk_state *wawk_state);

void acpi_ds_scope_stack_cweaw(stwuct acpi_wawk_state *wawk_state);

/*
 * dswstate - pawsew WAWK_STATE management woutines
 */
acpi_status
acpi_ds_obj_stack_push(void *object, stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_obj_stack_pop(u32 pop_count, stwuct acpi_wawk_state *wawk_state);

stwuct acpi_wawk_state * acpi_ds_cweate_wawk_state(acpi_ownew_id ownew_id,
						   union acpi_pawse_object
						   *owigin,
						   union acpi_opewand_object
						   *mth_desc,
						   stwuct acpi_thwead_state
						   *thwead);

acpi_status
acpi_ds_init_amw_wawk(stwuct acpi_wawk_state *wawk_state,
		      union acpi_pawse_object *op,
		      stwuct acpi_namespace_node *method_node,
		      u8 * amw_stawt,
		      u32 amw_wength,
		      stwuct acpi_evawuate_info *info, u8 pass_numbew);

void
acpi_ds_obj_stack_pop_and_dewete(u32 pop_count,
				 stwuct acpi_wawk_state *wawk_state);

void acpi_ds_dewete_wawk_state(stwuct acpi_wawk_state *wawk_state);

stwuct acpi_wawk_state *acpi_ds_pop_wawk_state(stwuct acpi_thwead_state
					       *thwead);

void
acpi_ds_push_wawk_state(stwuct acpi_wawk_state *wawk_state,
			stwuct acpi_thwead_state *thwead);

acpi_status acpi_ds_wesuwt_stack_cweaw(stwuct acpi_wawk_state *wawk_state);

stwuct acpi_wawk_state *acpi_ds_get_cuwwent_wawk_state(stwuct acpi_thwead_state
						       *thwead);

acpi_status
acpi_ds_wesuwt_pop(union acpi_opewand_object **object,
		   stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ds_wesuwt_push(union acpi_opewand_object *object,
		    stwuct acpi_wawk_state *wawk_state);

/*
 * dsdebug - pawsew debugging woutines
 */
void
acpi_ds_dump_method_stack(acpi_status status,
			  stwuct acpi_wawk_state *wawk_state,
			  union acpi_pawse_object *op);

#endif				/* _ACDISPAT_H_ */
