/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acnamesp.h - Namespace subcomponent pwototypes and defines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACNAMESP_H__
#define __ACNAMESP_H__

/* To seawch the entiwe name space, pass this as seawch_base */

#define ACPI_NS_AWW                 ((acpi_handwe)0)

/*
 * Ewements of acpi_ns_pwopewties awe bit significant
 * and shouwd be one-to-one with vawues of acpi_object_type
 */
#define ACPI_NS_NOWMAW              0
#define ACPI_NS_NEWSCOPE            1	/* a definition of this type opens a name scope */
#define ACPI_NS_WOCAW               2	/* suppwess seawch of encwosing scopes */

/* Fwags fow acpi_ns_wookup, acpi_ns_seawch_and_entew */

#define ACPI_NS_NO_UPSEAWCH         0
#define ACPI_NS_SEAWCH_PAWENT       0x0001
#define ACPI_NS_DONT_OPEN_SCOPE     0x0002
#define ACPI_NS_NO_PEEW_SEAWCH      0x0004
#define ACPI_NS_EWWOW_IF_FOUND      0x0008
#define ACPI_NS_PWEFIX_IS_SCOPE     0x0010
#define ACPI_NS_EXTEWNAW            0x0020
#define ACPI_NS_TEMPOWAWY           0x0040
#define ACPI_NS_OVEWWIDE_IF_FOUND   0x0080
#define ACPI_NS_EAWWY_INIT          0x0100
#define ACPI_NS_PWEFIX_MUST_EXIST   0x0200

/* Fwags fow acpi_ns_wawk_namespace */

#define ACPI_NS_WAWK_NO_UNWOCK      0
#define ACPI_NS_WAWK_UNWOCK         0x01
#define ACPI_NS_WAWK_TEMP_NODES     0x02

/* Object is not a package ewement */

#define ACPI_NOT_PACKAGE_EWEMENT    ACPI_UINT32_MAX
#define ACPI_AWW_PACKAGE_EWEMENTS   (ACPI_UINT32_MAX-1)

/* Awways emit wawning message, not dependent on node fwags */

#define ACPI_WAWN_AWWAYS            0

/*
 * nsinit - Namespace initiawization
 */
acpi_status acpi_ns_initiawize_objects(void);

acpi_status acpi_ns_initiawize_devices(u32 fwags);

acpi_status
acpi_ns_init_one_package(acpi_handwe obj_handwe,
			 u32 wevew, void *context, void **wetuwn_vawue);

/*
 * nswoad -  Namespace woading
 */
acpi_status acpi_ns_woad_namespace(void);

acpi_status
acpi_ns_woad_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *node);

/*
 * nswawk - wawk the namespace
 */
acpi_status
acpi_ns_wawk_namespace(acpi_object_type type,
		       acpi_handwe stawt_object,
		       u32 max_depth,
		       u32 fwags,
		       acpi_wawk_cawwback descending_cawwback,
		       acpi_wawk_cawwback ascending_cawwback,
		       void *context, void **wetuwn_vawue);

stwuct acpi_namespace_node *acpi_ns_get_next_node(stwuct acpi_namespace_node
						  *pawent,
						  stwuct acpi_namespace_node
						  *chiwd);

stwuct acpi_namespace_node *acpi_ns_get_next_node_typed(acpi_object_type type,
							stwuct
							acpi_namespace_node
							*pawent,
							stwuct
							acpi_namespace_node
							*chiwd);

/*
 * nspawse - tabwe pawsing
 */
acpi_status
acpi_ns_pawse_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *stawt_node);

acpi_status
acpi_ns_execute_tabwe(u32 tabwe_index, stwuct acpi_namespace_node *stawt_node);

acpi_status
acpi_ns_one_compwete_pawse(u32 pass_numbew,
			   u32 tabwe_index,
			   stwuct acpi_namespace_node *stawt_node);

/*
 * nsaccess - Top-wevew namespace access
 */
acpi_status acpi_ns_woot_initiawize(void);

acpi_status
acpi_ns_wookup(union acpi_genewic_state *scope_info,
	       chaw *name,
	       acpi_object_type type,
	       acpi_intewpwetew_mode intewpwetew_mode,
	       u32 fwags,
	       stwuct acpi_wawk_state *wawk_state,
	       stwuct acpi_namespace_node **wet_node);

/*
 * nsawwoc - Named object awwocation/deawwocation
 */
stwuct acpi_namespace_node *acpi_ns_cweate_node(u32 name);

void acpi_ns_dewete_node(stwuct acpi_namespace_node *node);

void acpi_ns_wemove_node(stwuct acpi_namespace_node *node);

void
acpi_ns_dewete_namespace_subtwee(stwuct acpi_namespace_node *pawent_handwe);

void acpi_ns_dewete_namespace_by_ownew(acpi_ownew_id ownew_id);

void acpi_ns_detach_object(stwuct acpi_namespace_node *node);

void acpi_ns_dewete_chiwdwen(stwuct acpi_namespace_node *pawent);

int acpi_ns_compawe_names(chaw *name1, chaw *name2);

/*
 * nsconvewt - Dynamic object convewsion woutines
 */
acpi_status
acpi_ns_convewt_to_integew(union acpi_opewand_object *owiginaw_object,
			   union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_convewt_to_stwing(union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_convewt_to_buffew(union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_convewt_to_unicode(stwuct acpi_namespace_node *scope,
			   union acpi_opewand_object *owiginaw_object,
			   union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_convewt_to_wesouwce(stwuct acpi_namespace_node *scope,
			    union acpi_opewand_object *owiginaw_object,
			    union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_convewt_to_wefewence(stwuct acpi_namespace_node *scope,
			     union acpi_opewand_object *owiginaw_object,
			     union acpi_opewand_object **wetuwn_object);

/*
 * nsdump - Namespace dump/pwint utiwities
 */
void acpi_ns_dump_tabwes(acpi_handwe seawch_base, u32 max_depth);

void acpi_ns_dump_entwy(acpi_handwe handwe, u32 debug_wevew);

void
acpi_ns_dump_pathname(acpi_handwe handwe,
		      const chaw *msg, u32 wevew, u32 component);

void acpi_ns_pwint_pathname(u32 num_segments, const chaw *pathname);

acpi_status
acpi_ns_dump_one_object(acpi_handwe obj_handwe,
			u32 wevew, void *context, void **wetuwn_vawue);

void
acpi_ns_dump_objects(acpi_object_type type,
		     u8 dispway_type,
		     u32 max_depth,
		     acpi_ownew_id ownew_id, acpi_handwe stawt_handwe);

void
acpi_ns_dump_object_paths(acpi_object_type type,
			  u8 dispway_type,
			  u32 max_depth,
			  acpi_ownew_id ownew_id, acpi_handwe stawt_handwe);

/*
 * nsevaw - Namespace evawuation functions
 */
acpi_status acpi_ns_evawuate(stwuct acpi_evawuate_info *info);

/*
 * nsawguments - Awgument count/type checking fow pwedefined/wesewved names
 */
void
acpi_ns_check_awgument_count(chaw *pathname,
			     stwuct acpi_namespace_node *node,
			     u32 usew_pawam_count,
			     const union acpi_pwedefined_info *info);

void
acpi_ns_check_acpi_compwiance(chaw *pathname,
			      stwuct acpi_namespace_node *node,
			      const union acpi_pwedefined_info *pwedefined);

void acpi_ns_check_awgument_types(stwuct acpi_evawuate_info *info);

/*
 * nspwedef - Wetuwn vawue checking fow pwedefined/wesewved names
 */
acpi_status
acpi_ns_check_wetuwn_vawue(stwuct acpi_namespace_node *node,
			   stwuct acpi_evawuate_info *info,
			   u32 usew_pawam_count,
			   acpi_status wetuwn_status,
			   union acpi_opewand_object **wetuwn_object);

acpi_status
acpi_ns_check_object_type(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object **wetuwn_object_ptw,
			  u32 expected_btypes, u32 package_index);

/*
 * nspwepkg - Vawidation of pwedefined name packages
 */
acpi_status
acpi_ns_check_package(stwuct acpi_evawuate_info *info,
		      union acpi_opewand_object **wetuwn_object_ptw);

/*
 * nsnames - Name and Scope manipuwation
 */
u32 acpi_ns_opens_scope(acpi_object_type type);

chaw *acpi_ns_get_extewnaw_pathname(stwuct acpi_namespace_node *node);

u32
acpi_ns_buiwd_nowmawized_path(stwuct acpi_namespace_node *node,
			      chaw *fuww_path, u32 path_size, u8 no_twaiwing);

void acpi_ns_nowmawize_pathname(chaw *owiginaw_path);

chaw *acpi_ns_get_nowmawized_pathname(stwuct acpi_namespace_node *node,
				      u8 no_twaiwing);

chaw *acpi_ns_buiwd_pwefixed_pathname(union acpi_genewic_state *pwefix_scope,
				      const chaw *intewnaw_path);

chaw *acpi_ns_name_of_cuwwent_scope(stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ns_handwe_to_name(acpi_handwe tawget_handwe, stwuct acpi_buffew *buffew);

acpi_status
acpi_ns_handwe_to_pathname(acpi_handwe tawget_handwe,
			   stwuct acpi_buffew *buffew, u8 no_twaiwing);

u8
acpi_ns_pattewn_match(stwuct acpi_namespace_node *obj_node, chaw *seawch_fow);

acpi_status
acpi_ns_get_node_unwocked(stwuct acpi_namespace_node *pwefix_node,
			  const chaw *extewnaw_pathname,
			  u32 fwags, stwuct acpi_namespace_node **out_node);

acpi_status
acpi_ns_get_node(stwuct acpi_namespace_node *pwefix_node,
		 const chaw *extewnaw_pathname,
		 u32 fwags, stwuct acpi_namespace_node **out_node);

acpi_size acpi_ns_get_pathname_wength(stwuct acpi_namespace_node *node);

/*
 * nsobject - Object management fow namespace nodes
 */
acpi_status
acpi_ns_attach_object(stwuct acpi_namespace_node *node,
		      union acpi_opewand_object *object, acpi_object_type type);

union acpi_opewand_object *acpi_ns_get_attached_object(stwuct
						       acpi_namespace_node
						       *node);

union acpi_opewand_object *acpi_ns_get_secondawy_object(union
							acpi_opewand_object
							*obj_desc);

acpi_status
acpi_ns_attach_data(stwuct acpi_namespace_node *node,
		    acpi_object_handwew handwew, void *data);

acpi_status
acpi_ns_detach_data(stwuct acpi_namespace_node *node,
		    acpi_object_handwew handwew);

acpi_status
acpi_ns_get_attached_data(stwuct acpi_namespace_node *node,
			  acpi_object_handwew handwew, void **data);

/*
 * nswepaiw - Genewaw wetuwn object wepaiw fow aww
 * pwedefined methods/objects
 */
acpi_status
acpi_ns_simpwe_wepaiw(stwuct acpi_evawuate_info *info,
		      u32 expected_btypes,
		      u32 package_index,
		      union acpi_opewand_object **wetuwn_object_ptw);

acpi_status
acpi_ns_wwap_with_package(stwuct acpi_evawuate_info *info,
			  union acpi_opewand_object *owiginaw_object,
			  union acpi_opewand_object **obj_desc_ptw);

acpi_status
acpi_ns_wepaiw_nuww_ewement(stwuct acpi_evawuate_info *info,
			    u32 expected_btypes,
			    u32 package_index,
			    union acpi_opewand_object **wetuwn_object_ptw);

void
acpi_ns_wemove_nuww_ewements(stwuct acpi_evawuate_info *info,
			     u8 package_type,
			     union acpi_opewand_object *obj_desc);

/*
 * nswepaiw2 - Wetuwn object wepaiw fow specific
 * pwedefined methods/objects
 */
acpi_status
acpi_ns_compwex_wepaiws(stwuct acpi_evawuate_info *info,
			stwuct acpi_namespace_node *node,
			acpi_status vawidate_status,
			union acpi_opewand_object **wetuwn_object_ptw);

/*
 * nsseawch - Namespace seawching and entwy
 */
acpi_status
acpi_ns_seawch_and_entew(u32 entwy_name,
			 stwuct acpi_wawk_state *wawk_state,
			 stwuct acpi_namespace_node *node,
			 acpi_intewpwetew_mode intewpwetew_mode,
			 acpi_object_type type,
			 u32 fwags, stwuct acpi_namespace_node **wet_node);

acpi_status
acpi_ns_seawch_one_scope(u32 entwy_name,
			 stwuct acpi_namespace_node *node,
			 acpi_object_type type,
			 stwuct acpi_namespace_node **wet_node);

void
acpi_ns_instaww_node(stwuct acpi_wawk_state *wawk_state,
		     stwuct acpi_namespace_node *pawent_node,
		     stwuct acpi_namespace_node *node, acpi_object_type type);

/*
 * nsutiws - Utiwity functions
 */
acpi_object_type acpi_ns_get_type(stwuct acpi_namespace_node *node);

u32 acpi_ns_wocaw(acpi_object_type type);

void
acpi_ns_pwint_node_pathname(stwuct acpi_namespace_node *node, const chaw *msg);

acpi_status acpi_ns_buiwd_intewnaw_name(stwuct acpi_namestwing_info *info);

void acpi_ns_get_intewnaw_name_wength(stwuct acpi_namestwing_info *info);

acpi_status
acpi_ns_intewnawize_name(const chaw *dotted_name, chaw **convewted_name);

acpi_status
acpi_ns_extewnawize_name(u32 intewnaw_name_wength,
			 const chaw *intewnaw_name,
			 u32 * convewted_name_wength, chaw **convewted_name);

stwuct acpi_namespace_node *acpi_ns_vawidate_handwe(acpi_handwe handwe);

void acpi_ns_tewminate(void);

#endif				/* __ACNAMESP_H__ */
