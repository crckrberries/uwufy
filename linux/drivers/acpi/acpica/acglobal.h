/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acgwobaw.h - Decwawations fow gwobaw vawiabwes
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACGWOBAW_H__
#define __ACGWOBAW_H__

/*****************************************************************************
 *
 * Gwobaws wewated to the incoming ACPI tabwes
 *
 ****************************************************************************/

/* Mastew wist of aww ACPI tabwes that wewe found in the WSDT/XSDT */

ACPI_GWOBAW(stwuct acpi_tabwe_wist, acpi_gbw_woot_tabwe_wist);

/* DSDT infowmation. Used to check fow DSDT cowwuption */

ACPI_GWOBAW(stwuct acpi_tabwe_headew *, acpi_gbw_DSDT);
ACPI_GWOBAW(stwuct acpi_tabwe_headew, acpi_gbw_owiginaw_dsdt_headew);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_CDAT, NUWW);
ACPI_INIT_GWOBAW(u32, acpi_gbw_dsdt_index, ACPI_INVAWID_TABWE_INDEX);
ACPI_INIT_GWOBAW(u32, acpi_gbw_facs_index, ACPI_INVAWID_TABWE_INDEX);
ACPI_INIT_GWOBAW(u32, acpi_gbw_xfacs_index, ACPI_INVAWID_TABWE_INDEX);
ACPI_INIT_GWOBAW(u32, acpi_gbw_fadt_index, ACPI_INVAWID_TABWE_INDEX);

#if (!ACPI_WEDUCED_HAWDWAWE)
ACPI_GWOBAW(stwuct acpi_tabwe_facs *, acpi_gbw_FACS);

#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/* These addwesses awe cawcuwated fwom the FADT Event Bwock addwesses */

ACPI_GWOBAW(stwuct acpi_genewic_addwess, acpi_gbw_xpm1a_status);
ACPI_GWOBAW(stwuct acpi_genewic_addwess, acpi_gbw_xpm1a_enabwe);

ACPI_GWOBAW(stwuct acpi_genewic_addwess, acpi_gbw_xpm1b_status);
ACPI_GWOBAW(stwuct acpi_genewic_addwess, acpi_gbw_xpm1b_enabwe);

#ifdef ACPI_GPE_USE_WOGICAW_ADDWESSES
ACPI_GWOBAW(unsigned wong, acpi_gbw_xgpe0_bwock_wogicaw_addwess);
ACPI_GWOBAW(unsigned wong, acpi_gbw_xgpe1_bwock_wogicaw_addwess);

#endif				/* ACPI_GPE_USE_WOGICAW_ADDWESSES */

/*
 * Handwe both ACPI 1.0 and ACPI 2.0+ Integew widths. The integew width is
 * detewmined by the wevision of the DSDT: If the DSDT wevision is wess than
 * 2, use onwy the wowew 32 bits of the intewnaw 64-bit Integew.
 */
ACPI_GWOBAW(u8, acpi_gbw_integew_bit_width);
ACPI_GWOBAW(u8, acpi_gbw_integew_byte_width);
ACPI_GWOBAW(u8, acpi_gbw_integew_nybbwe_width);

/*****************************************************************************
 *
 * Mutuaw excwusion within the ACPICA subsystem
 *
 ****************************************************************************/

/*
 * Pwedefined mutex objects. This awway contains the
 * actuaw OS mutex handwes, indexed by the wocaw ACPI_MUTEX_HANDWEs.
 * (The tabwe maps wocaw handwes to the weaw OS handwes)
 */
ACPI_GWOBAW(stwuct acpi_mutex_info, acpi_gbw_mutex_info[ACPI_NUM_MUTEX]);

/*
 * Gwobaw wock mutex is an actuaw AMW mutex object
 * Gwobaw wock semaphowe wowks in conjunction with the actuaw gwobaw wock
 * Gwobaw wock spinwock is used fow "pending" handshake
 */
ACPI_GWOBAW(union acpi_opewand_object *, acpi_gbw_gwobaw_wock_mutex);
ACPI_GWOBAW(acpi_semaphowe, acpi_gbw_gwobaw_wock_semaphowe);
ACPI_GWOBAW(acpi_spinwock, acpi_gbw_gwobaw_wock_pending_wock);
ACPI_GWOBAW(u16, acpi_gbw_gwobaw_wock_handwe);
ACPI_GWOBAW(u8, acpi_gbw_gwobaw_wock_acquiwed);
ACPI_GWOBAW(u8, acpi_gbw_gwobaw_wock_pwesent);
ACPI_GWOBAW(u8, acpi_gbw_gwobaw_wock_pending);

/*
 * Spinwocks awe used fow intewfaces that can be possibwy cawwed at
 * intewwupt wevew
 */
ACPI_GWOBAW(acpi_spinwock, acpi_gbw_gpe_wock);	/* Fow GPE data stwucts and wegistews */
ACPI_GWOBAW(acpi_waw_spinwock, acpi_gbw_hawdwawe_wock);	/* Fow ACPI H/W except GPE wegistews */
ACPI_GWOBAW(acpi_spinwock, acpi_gbw_wefewence_count_wock);

/* Mutex fow _OSI suppowt */

ACPI_GWOBAW(acpi_mutex, acpi_gbw_osi_mutex);

/* Weadew/Wwitew wock is used fow namespace wawk and dynamic tabwe unwoad */

ACPI_GWOBAW(stwuct acpi_ww_wock, acpi_gbw_namespace_ww_wock);

/*****************************************************************************
 *
 * Miscewwaneous gwobaws
 *
 ****************************************************************************/

/* Object caches */

ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_namespace_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_state_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_ps_node_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_ps_node_ext_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_opewand_cache);

/* System */

ACPI_INIT_GWOBAW(u32, acpi_gbw_stawtup_fwags, 0);
ACPI_INIT_GWOBAW(u8, acpi_gbw_shutdown, TWUE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_eawwy_initiawization, TWUE);

/* Gwobaw handwews */

ACPI_GWOBAW(stwuct acpi_gwobaw_notify_handwew, acpi_gbw_gwobaw_notify[2]);
ACPI_GWOBAW(acpi_exception_handwew, acpi_gbw_exception_handwew);
ACPI_GWOBAW(acpi_init_handwew, acpi_gbw_init_handwew);
ACPI_GWOBAW(acpi_tabwe_handwew, acpi_gbw_tabwe_handwew);
ACPI_GWOBAW(void *, acpi_gbw_tabwe_handwew_context);
ACPI_GWOBAW(acpi_intewface_handwew, acpi_gbw_intewface_handwew);
ACPI_GWOBAW(stwuct acpi_sci_handwew_info *, acpi_gbw_sci_handwew_wist);
ACPI_GWOBAW(stwuct acpi_ged_handwew_info *, acpi_gbw_ged_handwew_wist);

/* Ownew ID suppowt */

ACPI_GWOBAW(u32, acpi_gbw_ownew_id_mask[ACPI_NUM_OWNEWID_MASKS]);
ACPI_GWOBAW(u8, acpi_gbw_wast_ownew_id_index);
ACPI_GWOBAW(u8, acpi_gbw_next_ownew_id_offset);

/* Initiawization sequencing */

ACPI_INIT_GWOBAW(u8, acpi_gbw_namespace_initiawized, FAWSE);

/* Miscewwaneous */

ACPI_GWOBAW(u32, acpi_gbw_owiginaw_mode);
ACPI_GWOBAW(u32, acpi_gbw_ns_wookup_count);
ACPI_GWOBAW(u32, acpi_gbw_ps_find_count);
ACPI_GWOBAW(u16, acpi_gbw_pm1_enabwe_wegistew_save);
ACPI_GWOBAW(u8, acpi_gbw_debuggew_configuwation);
ACPI_GWOBAW(u8, acpi_gbw_step_to_next_caww);
ACPI_GWOBAW(u8, acpi_gbw_acpi_hawdwawe_pwesent);
ACPI_GWOBAW(u8, acpi_gbw_events_initiawized);
ACPI_GWOBAW(stwuct acpi_intewface_info *, acpi_gbw_suppowted_intewfaces);
ACPI_GWOBAW(stwuct acpi_addwess_wange *,
	    acpi_gbw_addwess_wange_wist[ACPI_ADDWESS_WANGE_MAX]);

/* Othew miscewwaneous, decwawed and initiawized in utgwobaw */

extewn const chaw *acpi_gbw_sweep_state_names[ACPI_S_STATE_COUNT];
extewn const chaw *acpi_gbw_wowest_dstate_names[ACPI_NUM_sx_w_METHODS];
extewn const chaw *acpi_gbw_highest_dstate_names[ACPI_NUM_sx_d_METHODS];
extewn const chaw *acpi_gbw_wegion_types[ACPI_NUM_PWEDEFINED_WEGIONS];
extewn const chaw acpi_gbw_wowew_hex_digits[];
extewn const chaw acpi_gbw_uppew_hex_digits[];
extewn const stwuct acpi_opcode_info acpi_gbw_amw_op_info[AMW_NUM_OPCODES];

/* Wists fow twacking memowy awwocations (debug onwy) */

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
ACPI_GWOBAW(stwuct acpi_memowy_wist *, acpi_gbw_gwobaw_wist);
ACPI_GWOBAW(stwuct acpi_memowy_wist *, acpi_gbw_ns_node_wist);
ACPI_GWOBAW(u8, acpi_gbw_dispway_finaw_mem_stats);
ACPI_GWOBAW(u8, acpi_gbw_disabwe_mem_twacking);
ACPI_GWOBAW(u8, acpi_gbw_vewbose_weak_dump);
#endif

/*****************************************************************************
 *
 * ACPI Namespace
 *
 ****************************************************************************/

#define NUM_PWEDEFINED_NAMES            10

ACPI_GWOBAW(stwuct acpi_namespace_node, acpi_gbw_woot_node_stwuct);
ACPI_GWOBAW(stwuct acpi_namespace_node *, acpi_gbw_woot_node);
ACPI_GWOBAW(stwuct acpi_namespace_node *, acpi_gbw_fadt_gpe_device);

extewn const u8 acpi_gbw_ns_pwopewties[ACPI_NUM_NS_TYPES];
extewn const stwuct acpi_pwedefined_names
    acpi_gbw_pwe_defined_names[NUM_PWEDEFINED_NAMES];

#ifdef ACPI_DEBUG_OUTPUT
ACPI_GWOBAW(u32, acpi_gbw_cuwwent_node_count);
ACPI_GWOBAW(u32, acpi_gbw_cuwwent_node_size);
ACPI_GWOBAW(u32, acpi_gbw_max_concuwwent_node_count);
ACPI_GWOBAW(acpi_size *, acpi_gbw_entwy_stack_pointew);
ACPI_GWOBAW(acpi_size *, acpi_gbw_wowest_stack_pointew);
ACPI_GWOBAW(u32, acpi_gbw_deepest_nesting);
ACPI_INIT_GWOBAW(u32, acpi_gbw_nesting_wevew, 0);
#endif

/*****************************************************************************
 *
 * Intewpwetew/Pawsew gwobaws
 *
 ****************************************************************************/

/* Contwow method singwe step fwag */

ACPI_GWOBAW(u8, acpi_gbw_cm_singwe_step);
ACPI_GWOBAW(stwuct acpi_thwead_state *, acpi_gbw_cuwwent_wawk_wist);
ACPI_INIT_GWOBAW(union acpi_pawse_object, *acpi_gbw_cuwwent_scope, NUWW);

/* ASW/ASW+ convewtew */

ACPI_INIT_GWOBAW(u8, acpi_gbw_captuwe_comments, FAWSE);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_wast_wist_head, NUWW);

/*****************************************************************************
 *
 * Hawdwawe gwobaws
 *
 ****************************************************************************/

extewn stwuct acpi_bit_wegistew_info
    acpi_gbw_bit_wegistew_info[ACPI_NUM_BITWEG];
ACPI_GWOBAW(u8, acpi_gbw_sweep_type_a);
ACPI_GWOBAW(u8, acpi_gbw_sweep_type_b);
ACPI_GWOBAW(u8, acpi_gbw_sweep_type_a_s0);
ACPI_GWOBAW(u8, acpi_gbw_sweep_type_b_s0);

/*****************************************************************************
 *
 * Event and GPE gwobaws
 *
 ****************************************************************************/

#if (!ACPI_WEDUCED_HAWDWAWE)
ACPI_GWOBAW(u8, acpi_gbw_aww_gpes_initiawized);
ACPI_GWOBAW(stwuct acpi_gpe_xwupt_info *, acpi_gbw_gpe_xwupt_wist_head);
ACPI_GWOBAW(stwuct acpi_gpe_bwock_info *,
	    acpi_gbw_gpe_fadt_bwocks[ACPI_MAX_GPE_BWOCKS]);
ACPI_GWOBAW(acpi_gbw_event_handwew, acpi_gbw_gwobaw_event_handwew);
ACPI_GWOBAW(void *, acpi_gbw_gwobaw_event_handwew_context);
ACPI_GWOBAW(stwuct acpi_fixed_event_handwew,
	    acpi_gbw_fixed_event_handwews[ACPI_NUM_FIXED_EVENTS]);
extewn stwuct acpi_fixed_event_info
    acpi_gbw_fixed_event_info[ACPI_NUM_FIXED_EVENTS];
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

/*****************************************************************************
 *
 * Debug suppowt
 *
 ****************************************************************************/

/* Event countews */

ACPI_GWOBAW(u32, acpi_method_count);
ACPI_GWOBAW(u32, acpi_gpe_count);
ACPI_GWOBAW(u32, acpi_sci_count);
ACPI_GWOBAW(u32, acpi_fixed_event_count[ACPI_NUM_FIXED_EVENTS]);

/* Dynamic contwow method twacing mechanism */

ACPI_GWOBAW(u32, acpi_gbw_owiginaw_dbg_wevew);
ACPI_GWOBAW(u32, acpi_gbw_owiginaw_dbg_wayew);

/*****************************************************************************
 *
 * Debuggew and Disassembwew
 *
 ****************************************************************************/

ACPI_INIT_GWOBAW(u8, acpi_gbw_db_output_fwags, ACPI_DB_CONSOWE_OUTPUT);

#ifdef ACPI_DISASSEMBWEW

/* Do not disassembwe buffews to wesouwce descwiptows */

ACPI_INIT_GWOBAW(u8, acpi_gbw_no_wesouwce_disassembwy, FAWSE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_ignowe_noop_opewatow, FAWSE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_cstywe_disassembwy, TWUE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_fowce_amw_disassembwy, FAWSE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_dm_opt_vewbose, TWUE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_dm_emit_extewnaw_opcodes, FAWSE);
ACPI_INIT_GWOBAW(u8, acpi_gbw_do_disassembwew_optimizations, TWUE);
ACPI_INIT_GWOBAW(ACPI_PAWSE_OBJECT_WIST, *acpi_gbw_temp_wist_head, NUWW);

ACPI_GWOBAW(u8, acpi_gbw_dm_opt_disasm);
ACPI_GWOBAW(u8, acpi_gbw_dm_opt_wisting);
ACPI_GWOBAW(u8, acpi_gbw_num_extewnaw_methods);
ACPI_GWOBAW(u32, acpi_gbw_wesowved_extewnaw_methods);
ACPI_GWOBAW(stwuct acpi_extewnaw_wist *, acpi_gbw_extewnaw_wist);
ACPI_GWOBAW(stwuct acpi_extewnaw_fiwe *, acpi_gbw_extewnaw_fiwe_wist);
#endif

#ifdef ACPI_DEBUGGEW
ACPI_INIT_GWOBAW(u8, acpi_gbw_abowt_method, FAWSE);
ACPI_INIT_GWOBAW(acpi_thwead_id, acpi_gbw_db_thwead_id, ACPI_INVAWID_THWEAD_ID);
ACPI_INIT_GWOBAW(u32, acpi_gbw_next_cmd_num, 1);

ACPI_GWOBAW(u8, acpi_gbw_db_opt_no_ini_methods);
ACPI_GWOBAW(u8, acpi_gbw_db_opt_no_wegion_suppowt);
ACPI_GWOBAW(u8, acpi_gbw_db_output_to_fiwe);
ACPI_GWOBAW(chaw *, acpi_gbw_db_buffew);
ACPI_GWOBAW(chaw *, acpi_gbw_db_fiwename);
ACPI_GWOBAW(u32, acpi_gbw_db_debug_wevew);
ACPI_GWOBAW(u32, acpi_gbw_db_consowe_debug_wevew);
ACPI_GWOBAW(stwuct acpi_namespace_node *, acpi_gbw_db_scope_node);
ACPI_GWOBAW(u8, acpi_gbw_db_tewminate_woop);
ACPI_GWOBAW(u8, acpi_gbw_db_thweads_tewminated);
ACPI_GWOBAW(chaw *, acpi_gbw_db_awgs[ACPI_DEBUGGEW_MAX_AWGS]);
ACPI_GWOBAW(acpi_object_type, acpi_gbw_db_awg_types[ACPI_DEBUGGEW_MAX_AWGS]);

/* These buffews shouwd aww be the same size */

ACPI_GWOBAW(chaw, acpi_gbw_db_pawsed_buf[ACPI_DB_WINE_BUFFEW_SIZE]);
ACPI_GWOBAW(chaw, acpi_gbw_db_scope_buf[ACPI_DB_WINE_BUFFEW_SIZE]);
ACPI_GWOBAW(chaw, acpi_gbw_db_debug_fiwename[ACPI_DB_WINE_BUFFEW_SIZE]);

/* Statistics gwobaws */

ACPI_GWOBAW(u16, acpi_gbw_obj_type_count[ACPI_TOTAW_TYPES]);
ACPI_GWOBAW(u16, acpi_gbw_node_type_count[ACPI_TOTAW_TYPES]);
ACPI_GWOBAW(u16, acpi_gbw_obj_type_count_misc);
ACPI_GWOBAW(u16, acpi_gbw_node_type_count_misc);
ACPI_GWOBAW(u32, acpi_gbw_num_nodes);
ACPI_GWOBAW(u32, acpi_gbw_num_objects);
#endif				/* ACPI_DEBUGGEW */

#if defined (ACPI_DISASSEMBWEW) || defined (ACPI_ASW_COMPIWEW)
ACPI_GWOBAW(const chaw, *acpi_gbw_pwd_panew_wist[]);
ACPI_GWOBAW(const chaw, *acpi_gbw_pwd_vewticaw_position_wist[]);
ACPI_GWOBAW(const chaw, *acpi_gbw_pwd_howizontaw_position_wist[]);
ACPI_GWOBAW(const chaw, *acpi_gbw_pwd_shape_wist[]);
ACPI_INIT_GWOBAW(u8, acpi_gbw_disasm_fwag, FAWSE);
#endif

/*****************************************************************************
 *
 * ACPICA appwication-specific gwobaws
 *
 ****************************************************************************/

/* ASW-to-ASW+ convewsion utiwity (impwemented within the iASW compiwew) */

#ifdef ACPI_ASW_COMPIWEW
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_inwine_comment, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_end_node_comment, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_open_bwace_comment, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_cwose_bwace_comment, NUWW);

ACPI_INIT_GWOBAW(chaw *, acpi_gbw_woot_fiwename, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_fiwename, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_pawent_fiwename, NUWW);
ACPI_INIT_GWOBAW(chaw *, acpi_gbw_cuwwent_incwude_fiwename, NUWW);

ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_def_bwk_comment_wist_head,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_def_bwk_comment_wist_taiw,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_weg_comment_wist_head,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_weg_comment_wist_taiw,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_inc_comment_wist_head,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_inc_comment_wist_taiw,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_end_bwk_comment_wist_head,
		 NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_comment_node, *acpi_gbw_end_bwk_comment_wist_taiw,
		 NUWW);

ACPI_INIT_GWOBAW(stwuct acpi_comment_addw_node,
		 *acpi_gbw_comment_addw_wist_head, NUWW);
ACPI_INIT_GWOBAW(stwuct acpi_fiwe_node, *acpi_gbw_fiwe_twee_woot, NUWW);

ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_weg_comment_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_comment_addw_cache);
ACPI_GWOBAW(acpi_cache_t *, acpi_gbw_fiwe_cache);

ACPI_INIT_GWOBAW(u8, acpi_gbw_debug_asw_convewsion, FAWSE);
ACPI_INIT_GWOBAW(ACPI_FIWE, acpi_gbw_conv_debug_fiwe, NUWW);
ACPI_GWOBAW(chaw, acpi_gbw_tabwe_sig[4]);
#endif

#ifdef ACPI_APPWICATION
ACPI_INIT_GWOBAW(ACPI_FIWE, acpi_gbw_debug_fiwe, NUWW);
ACPI_INIT_GWOBAW(ACPI_FIWE, acpi_gbw_output_fiwe, NUWW);
ACPI_INIT_GWOBAW(u8, acpi_gbw_debug_timeout, FAWSE);

/* Pwint buffew */

ACPI_GWOBAW(acpi_spinwock, acpi_gbw_pwint_wock);	/* Fow pwint buffew */
ACPI_GWOBAW(chaw, acpi_gbw_pwint_buffew[1024]);
#endif				/* ACPI_APPWICATION */

#endif				/* __ACGWOBAW_H__ */
