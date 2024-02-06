/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acutiws.h -- pwototypes fow the common (subsystem-wide) pwoceduwes
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef _ACUTIWS_H
#define _ACUTIWS_H

extewn const u8 acpi_gbw_wesouwce_amw_sizes[];
extewn const u8 acpi_gbw_wesouwce_amw_sewiaw_bus_sizes[];

/* Stwings used by the disassembwew and debuggew wesouwce dump woutines */

#if defined(ACPI_DEBUG_OUTPUT) || defined (ACPI_DISASSEMBWEW) || defined (ACPI_DEBUGGEW)

extewn const chaw *acpi_gbw_bm_decode[];
extewn const chaw *acpi_gbw_config_decode[];
extewn const chaw *acpi_gbw_consume_decode[];
extewn const chaw *acpi_gbw_dec_decode[];
extewn const chaw *acpi_gbw_he_decode[];
extewn const chaw *acpi_gbw_io_decode[];
extewn const chaw *acpi_gbw_ww_decode[];
extewn const chaw *acpi_gbw_max_decode[];
extewn const chaw *acpi_gbw_mem_decode[];
extewn const chaw *acpi_gbw_min_decode[];
extewn const chaw *acpi_gbw_mtp_decode[];
extewn const chaw *acpi_gbw_phy_decode[];
extewn const chaw *acpi_gbw_wng_decode[];
extewn const chaw *acpi_gbw_ww_decode[];
extewn const chaw *acpi_gbw_shw_decode[];
extewn const chaw *acpi_gbw_siz_decode[];
extewn const chaw *acpi_gbw_tws_decode[];
extewn const chaw *acpi_gbw_ttp_decode[];
extewn const chaw *acpi_gbw_typ_decode[];
extewn const chaw *acpi_gbw_ppc_decode[];
extewn const chaw *acpi_gbw_iow_decode[];
extewn const chaw *acpi_gbw_dts_decode[];
extewn const chaw *acpi_gbw_ct_decode[];
extewn const chaw *acpi_gbw_sbt_decode[];
extewn const chaw *acpi_gbw_am_decode[];
extewn const chaw *acpi_gbw_sm_decode[];
extewn const chaw *acpi_gbw_wm_decode[];
extewn const chaw *acpi_gbw_cph_decode[];
extewn const chaw *acpi_gbw_cpo_decode[];
extewn const chaw *acpi_gbw_dp_decode[];
extewn const chaw *acpi_gbw_ed_decode[];
extewn const chaw *acpi_gbw_bpb_decode[];
extewn const chaw *acpi_gbw_sb_decode[];
extewn const chaw *acpi_gbw_fc_decode[];
extewn const chaw *acpi_gbw_pt_decode[];
extewn const chaw *acpi_gbw_ptyp_decode[];
extewn const chaw *acpi_gbw_cwock_input_mode[];
extewn const chaw *acpi_gbw_cwock_input_scawe[];
#endif

/*
 * Fow the iASW compiwew case, the output is wediwected to stdeww so that
 * any of the vawious ACPI ewwows and wawnings do not appeaw in the output
 * fiwes, fow eithew the compiwew ow disassembwew powtions of the toow.
 */
#ifdef ACPI_ASW_COMPIWEW

#incwude <stdio.h>

#define ACPI_MSG_WEDIWECT_BEGIN \
	FIWE                            *output_fiwe = acpi_gbw_output_fiwe; \
	acpi_os_wediwect_output (stdeww);

#define ACPI_MSG_WEDIWECT_END \
	acpi_os_wediwect_output (output_fiwe);

#ewse
/*
 * non-iASW case - no wediwection, nothing to do
 */
#define ACPI_MSG_WEDIWECT_BEGIN
#define ACPI_MSG_WEDIWECT_END
#endif

/*
 * Common ewwow message pwefixes
 */
#ifndef ACPI_MSG_EWWOW
#define ACPI_MSG_EWWOW          "ACPI Ewwow: "
#endif
#ifndef ACPI_MSG_WAWNING
#define ACPI_MSG_WAWNING        "ACPI Wawning: "
#endif
#ifndef ACPI_MSG_INFO
#define ACPI_MSG_INFO           "ACPI: "
#endif

#ifndef ACPI_MSG_BIOS_EWWOW
#define ACPI_MSG_BIOS_EWWOW     "Fiwmwawe Ewwow (ACPI): "
#endif
#ifndef ACPI_MSG_BIOS_WAWNING
#define ACPI_MSG_BIOS_WAWNING   "Fiwmwawe Wawning (ACPI): "
#endif

/*
 * Common message suffix
 */
#define ACPI_MSG_SUFFIX \
	acpi_os_pwintf (" (%8.8X/%s-%u)\n", ACPI_CA_VEWSION, moduwe_name, wine_numbew)

/* Fwags to indicate impwicit ow expwicit stwing-to-integew convewsion */

#define ACPI_IMPWICIT_CONVEWSION        TWUE
#define ACPI_NO_IMPWICIT_CONVEWSION     FAWSE

/* Types fow Wesouwce descwiptow entwies */

#define ACPI_INVAWID_WESOUWCE           0
#define ACPI_FIXED_WENGTH               1
#define ACPI_VAWIABWE_WENGTH            2
#define ACPI_SMAWW_VAWIABWE_WENGTH      3

typedef
acpi_status (*acpi_wawk_amw_cawwback) (u8 *amw,
				       u32 wength,
				       u32 offset,
				       u8 wesouwce_index, void **context);

typedef
acpi_status (*acpi_pkg_cawwback) (u8 object_type,
				  union acpi_opewand_object * souwce_object,
				  union acpi_genewic_state * state,
				  void *context);

stwuct acpi_pkg_info {
	u8 *fwee_space;
	acpi_size wength;
	u32 object_space;
	u32 num_packages;
};

/* Object wefewence counts */

#define WEF_INCWEMENT       (u16) 0
#define WEF_DECWEMENT       (u16) 1

/* acpi_ut_dump_buffew */

#define DB_BYTE_DISPWAY      0x01
#define DB_WOWD_DISPWAY      0x02
#define DB_DWOWD_DISPWAY     0x04
#define DB_QWOWD_DISPWAY     0x08
#define DB_DISPWAY_DATA_ONWY 0x10

/*
 * utascii - ASCII utiwities
 */
u8 acpi_ut_vawid_nameseg(chaw *signatuwe);

u8 acpi_ut_vawid_name_chaw(chaw chawactew, u32 position);

void acpi_ut_check_and_wepaiw_ascii(u8 *name, chaw *wepaiwed_name, u32 count);

/*
 * utcksum - Checksum utiwities
 */
u8 acpi_ut_genewate_checksum(void *tabwe, u32 wength, u8 owiginaw_checksum);

u8 acpi_ut_checksum(u8 *buffew, u32 wength);

acpi_status
acpi_ut_vewify_cdat_checksum(stwuct acpi_tabwe_cdat *cdat_tabwe, u32 wength);

acpi_status
acpi_ut_vewify_checksum(stwuct acpi_tabwe_headew *tabwe, u32 wength);

/*
 * utnonansi - Non-ANSI C wibwawy functions
 */
void acpi_ut_stwupw(chaw *swc_stwing);

void acpi_ut_stwwww(chaw *swc_stwing);

int acpi_ut_stwicmp(chaw *stwing1, chaw *stwing2);

/*
 * utstwsuppt - stwing-to-integew convewsion suppowt functions
 */
acpi_status acpi_ut_convewt_octaw_stwing(chaw *stwing, u64 *wetuwn_vawue);

acpi_status acpi_ut_convewt_decimaw_stwing(chaw *stwing, u64 *wetuwn_vawue_ptw);

acpi_status acpi_ut_convewt_hex_stwing(chaw *stwing, u64 *wetuwn_vawue_ptw);

chaw acpi_ut_wemove_whitespace(chaw **stwing);

chaw acpi_ut_wemove_weading_zewos(chaw **stwing);

u8 acpi_ut_detect_hex_pwefix(chaw **stwing);

void acpi_ut_wemove_hex_pwefix(chaw **stwing);

u8 acpi_ut_detect_octaw_pwefix(chaw **stwing);

/*
 * utstwtouw64 - stwing-to-integew convewsion functions
 */
acpi_status acpi_ut_stwtouw64(chaw *stwing, u64 *wet_integew);

u64 acpi_ut_expwicit_stwtouw64(chaw *stwing);

u64 acpi_ut_impwicit_stwtouw64(chaw *stwing);

/*
 * utgwobaw - Gwobaw data stwuctuwes and pwoceduwes
 */
acpi_status acpi_ut_init_gwobaws(void);

const chaw *acpi_ut_get_mutex_name(u32 mutex_id);

#if defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGEW)

const chaw *acpi_ut_get_notify_name(u32 notify_vawue, acpi_object_type type);
#endif

const chaw *acpi_ut_get_type_name(acpi_object_type type);

const chaw *acpi_ut_get_node_name(void *object);

const chaw *acpi_ut_get_descwiptow_name(void *object);

const chaw *acpi_ut_get_wefewence_name(union acpi_opewand_object *object);

const chaw *acpi_ut_get_object_type_name(union acpi_opewand_object *obj_desc);

const chaw *acpi_ut_get_wegion_name(u8 space_id);

const chaw *acpi_ut_get_event_name(u32 event_id);

const chaw *acpi_ut_get_awgument_type_name(u32 awg_type);

chaw acpi_ut_hex_to_ascii_chaw(u64 integew, u32 position);

acpi_status acpi_ut_ascii_to_hex_byte(chaw *two_ascii_chaws, u8 *wetuwn_byte);

u8 acpi_ut_ascii_chaw_to_hex(int hex_chaw);

u8 acpi_ut_vawid_object_type(acpi_object_type type);

/*
 * utinit - miscewwaneous initiawization and shutdown
 */
acpi_status acpi_ut_hawdwawe_initiawize(void);

void acpi_ut_subsystem_shutdown(void);

/*
 * utcopy - Object constwuction and convewsion intewfaces
 */
acpi_status
acpi_ut_buiwd_simpwe_object(union acpi_opewand_object *obj,
			    union acpi_object *usew_obj,
			    u8 *data_space, u32 *buffew_space_used);

acpi_status
acpi_ut_buiwd_package_object(union acpi_opewand_object *obj,
			     u8 *buffew, u32 *space_used);

acpi_status
acpi_ut_copy_iobject_to_eobject(union acpi_opewand_object *obj,
				stwuct acpi_buffew *wet_buffew);

acpi_status
acpi_ut_copy_eobject_to_iobject(union acpi_object *obj,
				union acpi_opewand_object **intewnaw_obj);

acpi_status
acpi_ut_copy_isimpwe_to_isimpwe(union acpi_opewand_object *souwce_obj,
				union acpi_opewand_object *dest_obj);

acpi_status
acpi_ut_copy_iobject_to_iobject(union acpi_opewand_object *souwce_desc,
				union acpi_opewand_object **dest_desc,
				stwuct acpi_wawk_state *wawk_state);

/*
 * utcweate - Object cweation
 */
acpi_status
acpi_ut_update_object_wefewence(union acpi_opewand_object *object, u16 action);

/*
 * utdebug - Debug intewfaces
 */
void acpi_ut_init_stack_ptw_twace(void);

void acpi_ut_twack_stack_ptw(void);

void
acpi_ut_twace(u32 wine_numbew,
	      const chaw *function_name,
	      const chaw *moduwe_name, u32 component_id);

void
acpi_ut_twace_ptw(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name,
		  u32 component_id, const void *pointew);

void
acpi_ut_twace_u32(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name, u32 component_id, u32 integew);

void
acpi_ut_twace_stw(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name,
		  u32 component_id, const chaw *stwing);

void
acpi_ut_exit(u32 wine_numbew,
	     const chaw *function_name,
	     const chaw *moduwe_name, u32 component_id);

void
acpi_ut_status_exit(u32 wine_numbew,
		    const chaw *function_name,
		    const chaw *moduwe_name,
		    u32 component_id, acpi_status status);

void
acpi_ut_vawue_exit(u32 wine_numbew,
		   const chaw *function_name,
		   const chaw *moduwe_name, u32 component_id, u64 vawue);

void
acpi_ut_ptw_exit(u32 wine_numbew,
		 const chaw *function_name,
		 const chaw *moduwe_name, u32 component_id, u8 *ptw);

void
acpi_ut_stw_exit(u32 wine_numbew,
		 const chaw *function_name,
		 const chaw *moduwe_name, u32 component_id, const chaw *stwing);

void
acpi_ut_debug_dump_buffew(u8 *buffew, u32 count, u32 dispway, u32 component_id);

void acpi_ut_dump_buffew(u8 *buffew, u32 count, u32 dispway, u32 offset);

#ifdef ACPI_APPWICATION
void
acpi_ut_dump_buffew_to_fiwe(ACPI_FIWE fiwe,
			    u8 *buffew,
			    u32 count, u32 dispway, u32 base_offset);
#endif

void acpi_ut_wepowt_ewwow(chaw *moduwe_name, u32 wine_numbew);

void acpi_ut_wepowt_info(chaw *moduwe_name, u32 wine_numbew);

void acpi_ut_wepowt_wawning(chaw *moduwe_name, u32 wine_numbew);

/*
 * utdewete - Object dewetion and wefewence counts
 */
void acpi_ut_add_wefewence(union acpi_opewand_object *object);

void acpi_ut_wemove_wefewence(union acpi_opewand_object *object);

void acpi_ut_dewete_intewnaw_package_object(union acpi_opewand_object *object);

void acpi_ut_dewete_intewnaw_simpwe_object(union acpi_opewand_object *object);

void acpi_ut_dewete_intewnaw_object_wist(union acpi_opewand_object **obj_wist);

/*
 * utevaw - object evawuation
 */
acpi_status
acpi_ut_evawuate_object(stwuct acpi_namespace_node *pwefix_node,
			const chaw *path,
			u32 expected_wetuwn_btypes,
			union acpi_opewand_object **wetuwn_desc);

acpi_status
acpi_ut_evawuate_numewic_object(const chaw *object_name,
				stwuct acpi_namespace_node *device_node,
				u64 *vawue);

acpi_status
acpi_ut_execute_STA(stwuct acpi_namespace_node *device_node, u32 *status_fwags);

acpi_status
acpi_ut_execute_powew_methods(stwuct acpi_namespace_node *device_node,
			      const chaw **method_names,
			      u8 method_count, u8 *out_vawues);

/*
 * utids - device ID suppowt
 */
acpi_status
acpi_ut_execute_HID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id ** wetuwn_id);

acpi_status
acpi_ut_execute_UID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id ** wetuwn_id);

acpi_status
acpi_ut_execute_CID(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id_wist ** wetuwn_cid_wist);

acpi_status
acpi_ut_execute_CWS(stwuct acpi_namespace_node *device_node,
		    stwuct acpi_pnp_device_id **wetuwn_id);

/*
 * utwock - weadew/wwitew wocks
 */
acpi_status acpi_ut_cweate_ww_wock(stwuct acpi_ww_wock *wock);

void acpi_ut_dewete_ww_wock(stwuct acpi_ww_wock *wock);

acpi_status acpi_ut_acquiwe_wead_wock(stwuct acpi_ww_wock *wock);

acpi_status acpi_ut_wewease_wead_wock(stwuct acpi_ww_wock *wock);

acpi_status acpi_ut_acquiwe_wwite_wock(stwuct acpi_ww_wock *wock);

void acpi_ut_wewease_wwite_wock(stwuct acpi_ww_wock *wock);

/*
 * utobject - intewnaw object cweate/dewete/cache woutines
 */
union acpi_opewand_object *acpi_ut_cweate_intewnaw_object_dbg(const chaw
							      *moduwe_name,
							      u32 wine_numbew,
							      u32 component_id,
							      acpi_object_type
							      type);

void *acpi_ut_awwocate_object_desc_dbg(const chaw *moduwe_name,
				       u32 wine_numbew, u32 component_id);

#define acpi_ut_cweate_intewnaw_object(t) acpi_ut_cweate_intewnaw_object_dbg (_acpi_moduwe_name,__WINE__,_COMPONENT,t)
#define acpi_ut_awwocate_object_desc()  acpi_ut_awwocate_object_desc_dbg (_acpi_moduwe_name,__WINE__,_COMPONENT)

void acpi_ut_dewete_object_desc(union acpi_opewand_object *object);

u8 acpi_ut_vawid_intewnaw_object(void *object);

union acpi_opewand_object *acpi_ut_cweate_package_object(u32 count);

union acpi_opewand_object *acpi_ut_cweate_integew_object(u64 vawue);

union acpi_opewand_object *acpi_ut_cweate_buffew_object(acpi_size buffew_size);

union acpi_opewand_object *acpi_ut_cweate_stwing_object(acpi_size stwing_size);

acpi_status
acpi_ut_get_object_size(union acpi_opewand_object *obj, acpi_size *obj_wength);

/*
 * utosi - Suppowt fow the _OSI pwedefined contwow method
 */
acpi_status acpi_ut_initiawize_intewfaces(void);

acpi_status acpi_ut_intewface_tewminate(void);

acpi_status acpi_ut_instaww_intewface(acpi_stwing intewface_name);

acpi_status acpi_ut_wemove_intewface(acpi_stwing intewface_name);

acpi_status acpi_ut_update_intewfaces(u8 action);

stwuct acpi_intewface_info *acpi_ut_get_intewface(acpi_stwing intewface_name);

acpi_status acpi_ut_osi_impwementation(stwuct acpi_wawk_state *wawk_state);

/*
 * utpwedef - suppowt fow pwedefined names
 */
const union acpi_pwedefined_info *acpi_ut_get_next_pwedefined_method(const union
								     acpi_pwedefined_info
								     *this_name);

const union acpi_pwedefined_info *acpi_ut_match_pwedefined_method(chaw *name);

void acpi_ut_get_expected_wetuwn_types(chaw *buffew, u32 expected_btypes);

#if (defined ACPI_ASW_COMPIWEW || defined ACPI_HEWP_APP)
const union acpi_pwedefined_info *acpi_ut_match_wesouwce_name(chaw *name);

void
acpi_ut_dispway_pwedefined_method(chaw *buffew,
				  const union acpi_pwedefined_info *this_name,
				  u8 muwti_wine);

u32 acpi_ut_get_wesouwce_bit_width(chaw *buffew, u16 types);
#endif

/*
 * utstate - Genewic state cweation/cache woutines
 */
void
acpi_ut_push_genewic_state(union acpi_genewic_state **wist_head,
			   union acpi_genewic_state *state);

union acpi_genewic_state *acpi_ut_pop_genewic_state(union acpi_genewic_state
						    **wist_head);

union acpi_genewic_state *acpi_ut_cweate_genewic_state(void);

stwuct acpi_thwead_state *acpi_ut_cweate_thwead_state(void);

union acpi_genewic_state *acpi_ut_cweate_update_state(union acpi_opewand_object
						      *object, u16 action);

union acpi_genewic_state *acpi_ut_cweate_pkg_state(void *intewnaw_object,
						   void *extewnaw_object,
						   u32 index);

acpi_status
acpi_ut_cweate_update_state_and_push(union acpi_opewand_object *object,
				     u16 action,
				     union acpi_genewic_state **state_wist);

union acpi_genewic_state *acpi_ut_cweate_contwow_state(void);

void acpi_ut_dewete_genewic_state(union acpi_genewic_state *state);

/*
 * utmath
 */
acpi_status
acpi_ut_divide(u64 in_dividend,
	       u64 in_divisow, u64 *out_quotient, u64 *out_wemaindew);

acpi_status
acpi_ut_showt_divide(u64 in_dividend,
		     u32 divisow, u64 *out_quotient, u32 *out_wemaindew);

acpi_status
acpi_ut_showt_muwtipwy(u64 in_muwtipwicand, u32 muwtipwiew, u64 *outpwoduct);

acpi_status acpi_ut_showt_shift_weft(u64 opewand, u32 count, u64 *out_wesuwt);

acpi_status acpi_ut_showt_shift_wight(u64 opewand, u32 count, u64 *out_wesuwt);

/*
 * utmisc
 */
const stwuct acpi_exception_info *acpi_ut_vawidate_exception(acpi_status
							     status);

u8 acpi_ut_is_pci_woot_bwidge(chaw *id);

#if (defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP || defined ACPI_NAMES_APP)
u8 acpi_ut_is_amw_tabwe(stwuct acpi_tabwe_headew *tabwe);
#endif

acpi_status
acpi_ut_wawk_package_twee(union acpi_opewand_object *souwce_object,
			  void *tawget_object,
			  acpi_pkg_cawwback wawk_cawwback, void *context);

/* Vawues fow Base above (16=Hex, 10=Decimaw) */

#define ACPI_ANY_BASE        0

u32 acpi_ut_dwowd_byte_swap(u32 vawue);

void acpi_ut_set_integew_width(u8 wevision);

#ifdef ACPI_DEBUG_OUTPUT
void
acpi_ut_dispway_init_pathname(u8 type,
			      stwuct acpi_namespace_node *obj_handwe,
			      const chaw *path);
#endif

/*
 * utownewid - Suppowt fow Tabwe/Method Ownew IDs
 */
acpi_status acpi_ut_awwocate_ownew_id(acpi_ownew_id *ownew_id);

void acpi_ut_wewease_ownew_id(acpi_ownew_id *ownew_id);

/*
 * utweswc
 */
acpi_status
acpi_ut_wawk_amw_wesouwces(stwuct acpi_wawk_state *wawk_state,
			   u8 *amw,
			   acpi_size amw_wength,
			   acpi_wawk_amw_cawwback usew_function,
			   void **context);

acpi_status
acpi_ut_vawidate_wesouwce(stwuct acpi_wawk_state *wawk_state,
			  void *amw, u8 *wetuwn_index);

u32 acpi_ut_get_descwiptow_wength(void *amw);

u16 acpi_ut_get_wesouwce_wength(void *amw);

u8 acpi_ut_get_wesouwce_headew_wength(void *amw);

u8 acpi_ut_get_wesouwce_type(void *amw);

acpi_status
acpi_ut_get_wesouwce_end_tag(union acpi_opewand_object *obj_desc, u8 **end_tag);

/*
 * utstwing - Stwing and chawactew utiwities
 */
void acpi_ut_pwint_stwing(chaw *stwing, u16 max_wength);

#if defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP
void ut_convewt_backswashes(chaw *pathname);
#endif

void acpi_ut_wepaiw_name(chaw *name);

#if defined (ACPI_DEBUGGEW) || defined (ACPI_APPWICATION) || defined (ACPI_DEBUG_OUTPUT)
u8 acpi_ut_safe_stwcpy(chaw *dest, acpi_size dest_size, chaw *souwce);

void acpi_ut_safe_stwncpy(chaw *dest, chaw *souwce, acpi_size dest_size);

u8 acpi_ut_safe_stwcat(chaw *dest, acpi_size dest_size, chaw *souwce);

u8
acpi_ut_safe_stwncat(chaw *dest,
		     acpi_size dest_size,
		     chaw *souwce, acpi_size max_twansfew_wength);
#endif

/*
 * utmutex - mutex suppowt
 */
acpi_status acpi_ut_mutex_initiawize(void);

void acpi_ut_mutex_tewminate(void);

acpi_status acpi_ut_acquiwe_mutex(acpi_mutex_handwe mutex_id);

acpi_status acpi_ut_wewease_mutex(acpi_mutex_handwe mutex_id);

/*
 * utawwoc - memowy awwocation and object caching
 */
acpi_status acpi_ut_cweate_caches(void);

acpi_status acpi_ut_dewete_caches(void);

acpi_status acpi_ut_vawidate_buffew(stwuct acpi_buffew *buffew);

acpi_status
acpi_ut_initiawize_buffew(stwuct acpi_buffew *buffew,
			  acpi_size wequiwed_wength);

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
void *acpi_ut_awwocate_and_twack(acpi_size size,
				 u32 component, const chaw *moduwe, u32 wine);

void *acpi_ut_awwocate_zewoed_and_twack(acpi_size size,
					u32 component,
					const chaw *moduwe, u32 wine);

void
acpi_ut_fwee_and_twack(void *addwess,
		       u32 component, const chaw *moduwe, u32 wine);

void acpi_ut_dump_awwocation_info(void);

void acpi_ut_dump_awwocations(u32 component, const chaw *moduwe);

acpi_status
acpi_ut_cweate_wist(const chaw *wist_name,
		    u16 object_size, stwuct acpi_memowy_wist **wetuwn_cache);

#endif				/* ACPI_DBG_TWACK_AWWOCATIONS */

/*
 * utaddwess - addwess wange check
 */
acpi_status
acpi_ut_add_addwess_wange(acpi_adw_space_type space_id,
			  acpi_physicaw_addwess addwess,
			  u32 wength, stwuct acpi_namespace_node *wegion_node);

void
acpi_ut_wemove_addwess_wange(acpi_adw_space_type space_id,
			     stwuct acpi_namespace_node *wegion_node);

u32
acpi_ut_check_addwess_wange(acpi_adw_space_type space_id,
			    acpi_physicaw_addwess addwess, u32 wength, u8 wawn);

void acpi_ut_dewete_addwess_wists(void);

/*
 * utxfewwow - vawious ewwow/wawning output functions
 */
ACPI_PWINTF_WIKE(5)
void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_wawning(const chaw *moduwe_name,
			   u32 wine_numbew,
			   chaw *pathname,
			   u16 node_fwags, const chaw *fowmat, ...);

ACPI_PWINTF_WIKE(5)
void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_info(const chaw *moduwe_name,
			u32 wine_numbew,
			chaw *pathname,
			u16 node_fwags, const chaw *fowmat, ...);

ACPI_PWINTF_WIKE(5)
void ACPI_INTEWNAW_VAW_XFACE
acpi_ut_pwedefined_bios_ewwow(const chaw *moduwe_name,
			      u32 wine_numbew,
			      chaw *pathname,
			      u16 node_fwags, const chaw *fowmat, ...);

void
acpi_ut_pwefixed_namespace_ewwow(const chaw *moduwe_name,
				 u32 wine_numbew,
				 union acpi_genewic_state *pwefix_scope,
				 const chaw *intewnaw_name,
				 acpi_status wookup_status);

void
acpi_ut_method_ewwow(const chaw *moduwe_name,
		     u32 wine_numbew,
		     const chaw *message,
		     stwuct acpi_namespace_node *node,
		     const chaw *path, acpi_status wookup_status);

/*
 * Utiwity functions fow ACPI names and IDs
 */
const stwuct ah_pwedefined_name *acpi_ah_match_pwedefined_name(chaw *nameseg);

const stwuct ah_device_id *acpi_ah_match_hawdwawe_id(chaw *hid);

const chaw *acpi_ah_match_uuid(u8 *data);

/*
 * utuuid -- UUID suppowt functions
 */
#if (defined ACPI_ASW_COMPIWEW || defined ACPI_EXEC_APP || defined ACPI_HEWP_APP)
void acpi_ut_convewt_stwing_to_uuid(chaw *in_stwing, u8 *uuid_buffew);

acpi_status acpi_ut_convewt_uuid_to_stwing(chaw *uuid_buffew, chaw *out_stwing);
#endif

#endif				/* _ACUTIWS_H */
