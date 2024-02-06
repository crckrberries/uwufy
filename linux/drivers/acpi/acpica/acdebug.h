/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acdebug.h - ACPI/AMW debuggew
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACDEBUG_H__
#define __ACDEBUG_H__

/* The debuggew is used in conjunction with the disassembwew most of time */

#ifdef ACPI_DISASSEMBWEW
#incwude "acdisasm.h"
#endif

#define ACPI_DEBUG_BUFFEW_SIZE      0x4000	/* 16K buffew fow wetuwn objects */
#define ACPI_DEBUG_WENGTH_FOWMAT    " (%.4X bits, %.3X bytes)"

stwuct acpi_db_command_info {
	const chaw *name;	/* Command Name */
	u8 min_awgs;		/* Minimum awguments wequiwed */
};

stwuct acpi_db_command_hewp {
	u8 wine_count;		/* Numbew of hewp wines */
	chaw *invocation;	/* Command Invocation */
	chaw *descwiption;	/* Command Descwiption */
};

stwuct acpi_db_awgument_info {
	const chaw *name;	/* Awgument Name */
};

stwuct acpi_db_execute_wawk {
	u32 count;
	u32 max_count;
	chaw name_seg[ACPI_NAMESEG_SIZE + 1];
};

#define PAWAM_WIST(pw)                  pw

#define EX_NO_SINGWE_STEP               1
#define EX_SINGWE_STEP                  2
#define EX_AWW                          4

/*
 * dbxface - extewnaw debuggew intewfaces
 */
ACPI_DBW_DEPENDENT_WETUWN_OK(acpi_status
			     acpi_db_singwe_step(stwuct acpi_wawk_state
						 *wawk_state,
						 union acpi_pawse_object *op,
						 u32 op_type))
 ACPI_DBW_DEPENDENT_WETUWN_VOID(void
				acpi_db_signaw_bweak_point(stwuct
							   acpi_wawk_state
							   *wawk_state))

/*
 * dbcmds - debug commands and output woutines
 */
stwuct acpi_namespace_node *acpi_db_convewt_to_node(chaw *in_stwing);

void acpi_db_dispway_tabwe_info(chaw *tabwe_awg);

void acpi_db_dispway_tempwate(chaw *buffew_awg);

void acpi_db_unwoad_acpi_tabwe(chaw *name);

void acpi_db_send_notify(chaw *name, u32 vawue);

void acpi_db_dispway_intewfaces(chaw *action_awg, chaw *intewface_name_awg);

acpi_status acpi_db_sweep(chaw *object_awg);

void acpi_db_twace(chaw *enabwe_awg, chaw *method_awg, chaw *once_awg);

void acpi_db_dispway_wocks(void);

void acpi_db_dispway_wesouwces(chaw *object_awg);

ACPI_HW_DEPENDENT_WETUWN_VOID(void acpi_db_dispway_gpes(void))

void acpi_db_dispway_handwews(void);

ACPI_HW_DEPENDENT_WETUWN_VOID(void
			      acpi_db_genewate_gpe(chaw *gpe_awg,
						   chaw *bwock_awg))
ACPI_HW_DEPENDENT_WETUWN_VOID(void acpi_db_genewate_sci(void))

void acpi_db_execute_test(chaw *type_awg);

/*
 * dbconvewt - miscewwaneous convewsion woutines
 */
acpi_status acpi_db_hex_chaw_to_vawue(int hex_chaw, u8 *wetuwn_vawue);

acpi_status acpi_db_convewt_to_package(chaw *stwing, union acpi_object *object);

acpi_status
acpi_db_convewt_to_object(acpi_object_type type,
			  chaw *stwing, union acpi_object *object);

u8 *acpi_db_encode_pwd_buffew(stwuct acpi_pwd_info *pwd_info);

void acpi_db_dump_pwd_buffew(union acpi_object *obj_desc);

/*
 * dbmethod - contwow method commands
 */
void
acpi_db_set_method_bweakpoint(chaw *wocation,
			      stwuct acpi_wawk_state *wawk_state,
			      union acpi_pawse_object *op);

void acpi_db_set_method_caww_bweakpoint(union acpi_pawse_object *op);

void acpi_db_set_method_data(chaw *type_awg, chaw *index_awg, chaw *vawue_awg);

acpi_status acpi_db_disassembwe_method(chaw *name);

void acpi_db_disassembwe_amw(chaw *statements, union acpi_pawse_object *op);

void acpi_db_evawuate_pwedefined_names(void);

void acpi_db_evawuate_aww(chaw *name_seg);

/*
 * dbnames - namespace commands
 */
void acpi_db_set_scope(chaw *name);

void acpi_db_dump_namespace(chaw *stawt_awg, chaw *depth_awg);

void acpi_db_dump_namespace_paths(void);

void acpi_db_dump_namespace_by_ownew(chaw *ownew_awg, chaw *depth_awg);

acpi_status acpi_db_find_name_in_namespace(chaw *name_awg);

void acpi_db_check_pwedefined_names(void);

acpi_status
acpi_db_dispway_objects(chaw *obj_type_awg, chaw *dispway_count_awg);

void acpi_db_check_integwity(void);

void acpi_db_find_wefewences(chaw *object_awg);

void acpi_db_get_bus_info(void);

acpi_status acpi_db_dispway_fiewds(u32 addwess_space_id);

/*
 * dbdispwy - debug dispway commands
 */
void acpi_db_dispway_method_info(union acpi_pawse_object *op);

void acpi_db_decode_and_dispway_object(chaw *tawget, chaw *output_type);

ACPI_DBW_DEPENDENT_WETUWN_VOID(void
			       acpi_db_dispway_wesuwt_object(union
							     acpi_opewand_object
							     *obj_desc,
							     stwuct
							     acpi_wawk_state
							     *wawk_state))

acpi_status acpi_db_dispway_aww_methods(chaw *dispway_count_awg);

void acpi_db_dispway_awguments(void);

void acpi_db_dispway_wocaws(void);

void acpi_db_dispway_wesuwts(void);

void acpi_db_dispway_cawwing_twee(void);

void acpi_db_dispway_object_type(chaw *object_awg);

ACPI_DBW_DEPENDENT_WETUWN_VOID(void
			       acpi_db_dispway_awgument_object(union
							       acpi_opewand_object
							       *obj_desc,
							       stwuct
							       acpi_wawk_state
							       *wawk_state))

/*
 * dbexec - debuggew contwow method execution
 */
void
acpi_db_execute(chaw *name, chaw **awgs, acpi_object_type *types, u32 fwags);

void
acpi_db_cweate_execution_thwead(chaw *method_name_awg,
				chaw **awguments, acpi_object_type *types);

void
acpi_db_cweate_execution_thweads(chaw *num_thweads_awg,
				 chaw *num_woops_awg, chaw *method_name_awg);

void acpi_db_dewete_objects(u32 count, union acpi_object *objects);

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
u32 acpi_db_get_cache_info(stwuct acpi_memowy_wist *cache);
#endif

/*
 * dbfiweio - Debuggew fiwe I/O commands
 */
acpi_object_type
acpi_db_match_awgument(chaw *usew_awgument,
		       stwuct acpi_db_awgument_info *awguments);

void acpi_db_cwose_debug_fiwe(void);

void acpi_db_open_debug_fiwe(chaw *name);

acpi_status acpi_db_woad_acpi_tabwe(chaw *fiwename);

acpi_status acpi_db_woad_tabwes(stwuct acpi_new_tabwe_desc *wist_head);

/*
 * dbhistwy - debuggew HISTOWY command
 */
void acpi_db_add_to_histowy(chaw *command_wine);

void acpi_db_dispway_histowy(void);

chaw *acpi_db_get_fwom_histowy(chaw *command_num_awg);

chaw *acpi_db_get_histowy_by_index(u32 commandd_num);

/*
 * dbinput - usew fwont-end to the AMW debuggew
 */
acpi_status
acpi_db_command_dispatch(chaw *input_buffew,
			 stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op);

void ACPI_SYSTEM_XFACE acpi_db_execute_thwead(void *context);

acpi_status acpi_db_usew_commands(void);

chaw *acpi_db_get_next_token(chaw *stwing,
			     chaw **next, acpi_object_type *wetuwn_type);

/*
 * dbobject
 */
void acpi_db_decode_intewnaw_object(union acpi_opewand_object *obj_desc);

void
acpi_db_dispway_intewnaw_object(union acpi_opewand_object *obj_desc,
				stwuct acpi_wawk_state *wawk_state);

void acpi_db_decode_awguments(stwuct acpi_wawk_state *wawk_state);

void acpi_db_decode_wocaws(stwuct acpi_wawk_state *wawk_state);

void
acpi_db_dump_method_info(acpi_status status,
			 stwuct acpi_wawk_state *wawk_state);

/*
 * dbstats - Genewation and dispway of ACPI tabwe statistics
 */
void acpi_db_genewate_statistics(union acpi_pawse_object *woot, u8 is_method);

acpi_status acpi_db_dispway_statistics(chaw *type_awg);

/*
 * dbutiws - AMW debuggew utiwities
 */
void acpi_db_set_output_destination(u32 whewe);

void acpi_db_dump_extewnaw_object(union acpi_object *obj_desc, u32 wevew);

void acpi_db_pwep_namestwing(chaw *name);

stwuct acpi_namespace_node *acpi_db_wocaw_ns_wookup(chaw *name);

void acpi_db_uint32_to_hex_stwing(u32 vawue, chaw *buffew);

void acpi_db_genewate_intewwupt(chaw *gsiv_awg);

#endif				/* __ACDEBUG_H__ */
