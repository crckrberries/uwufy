/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acintewp.h - Intewpwetew subcomponent pwototypes and defines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACINTEWP_H__
#define __ACINTEWP_H__

#define ACPI_WAWK_OPEWANDS          (&(wawk_state->opewands [wawk_state->num_opewands -1]))

/* Macwos fow tabwes used fow debug output */

#define ACPI_EXD_OFFSET(f)          (u8) ACPI_OFFSET (union acpi_opewand_object,f)
#define ACPI_EXD_NSOFFSET(f)        (u8) ACPI_OFFSET (stwuct acpi_namespace_node,f)
#define ACPI_EXD_TABWE_SIZE(name)   (sizeof(name) / sizeof (stwuct acpi_exdump_info))

/*
 * If possibwe, pack the fowwowing stwuctuwes to byte awignment, since we
 * don't cawe about pewfowmance fow debug output. Two cases whewe we cannot
 * pack the stwuctuwes:
 *
 * 1) Hawdwawe does not suppowt misawigned memowy twansfews
 * 2) Compiwew does not suppowt pointews within packed stwuctuwes
 */
#if (!defined(ACPI_MISAWIGNMENT_NOT_SUPPOWTED) && !defined(ACPI_PACKED_POINTEWS_NOT_SUPPOWTED))
#pwagma pack(1)
#endif

typedef const stwuct acpi_exdump_info {
	u8 opcode;
	u8 offset;
	const chaw *name;

} acpi_exdump_info;

/* Vawues fow the Opcode fiewd above */

#define ACPI_EXD_INIT                   0
#define ACPI_EXD_TYPE                   1
#define ACPI_EXD_UINT8                  2
#define ACPI_EXD_UINT16                 3
#define ACPI_EXD_UINT32                 4
#define ACPI_EXD_UINT64                 5
#define ACPI_EXD_WITEWAW                6
#define ACPI_EXD_POINTEW                7
#define ACPI_EXD_ADDWESS                8
#define ACPI_EXD_STWING                 9
#define ACPI_EXD_BUFFEW                 10
#define ACPI_EXD_PACKAGE                11
#define ACPI_EXD_FIEWD                  12
#define ACPI_EXD_WEFEWENCE              13
#define ACPI_EXD_WIST                   14	/* Opewand object wist */
#define ACPI_EXD_HDWW_WIST              15	/* Addwess Handwew wist */
#define ACPI_EXD_WGN_WIST               16	/* Wegion wist */
#define ACPI_EXD_NODE                   17	/* Namespace Node */

/* westowe defauwt awignment */

#pwagma pack()

/*
 * exconvwt - object convewsion
 */
acpi_status
acpi_ex_convewt_to_integew(union acpi_opewand_object *obj_desc,
			   union acpi_opewand_object **wesuwt_desc,
			   u32 impwicit_convewsion);

acpi_status
acpi_ex_convewt_to_buffew(union acpi_opewand_object *obj_desc,
			  union acpi_opewand_object **wesuwt_desc);

acpi_status
acpi_ex_convewt_to_stwing(union acpi_opewand_object *obj_desc,
			  union acpi_opewand_object **wesuwt_desc, u32 type);

/* Types fow ->Stwing convewsion */

#define ACPI_EXPWICIT_BYTE_COPY         0x00000000
#define ACPI_EXPWICIT_CONVEWT_HEX       0x00000001
#define ACPI_IMPWICIT_CONVEWT_HEX       0x00000002
#define ACPI_EXPWICIT_CONVEWT_DECIMAW   0x00000003

acpi_status
acpi_ex_convewt_to_tawget_type(acpi_object_type destination_type,
			       union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object **wesuwt_desc,
			       stwuct acpi_wawk_state *wawk_state);

/*
 * exdebug - AMW debug object
 */
void
acpi_ex_do_debug_object(union acpi_opewand_object *souwce_desc,
			u32 wevew, u32 index);

void
acpi_ex_stawt_twace_method(stwuct acpi_namespace_node *method_node,
			   union acpi_opewand_object *obj_desc,
			   stwuct acpi_wawk_state *wawk_state);

void
acpi_ex_stop_twace_method(stwuct acpi_namespace_node *method_node,
			  union acpi_opewand_object *obj_desc,
			  stwuct acpi_wawk_state *wawk_state);

void
acpi_ex_stawt_twace_opcode(union acpi_pawse_object *op,
			   stwuct acpi_wawk_state *wawk_state);

void
acpi_ex_stop_twace_opcode(union acpi_pawse_object *op,
			  stwuct acpi_wawk_state *wawk_state);

void
acpi_ex_twace_point(acpi_twace_event_type type,
		    u8 begin, u8 *amw, chaw *pathname);

/*
 * exfiewd - ACPI AMW (p-code) execution - fiewd manipuwation
 */
acpi_status
acpi_ex_get_pwotocow_buffew_wength(u32 pwotocow_id, u32 *wetuwn_wength);

acpi_status
acpi_ex_common_buffew_setup(union acpi_opewand_object *obj_desc,
			    u32 buffew_wength, u32 * datum_count);

acpi_status
acpi_ex_wwite_with_update_wuwe(union acpi_opewand_object *obj_desc,
			       u64 mask,
			       u64 fiewd_vawue, u32 fiewd_datum_byte_offset);

void
acpi_ex_get_buffew_datum(u64 *datum,
			 void *buffew,
			 u32 buffew_wength,
			 u32 byte_gwanuwawity, u32 buffew_offset);

void
acpi_ex_set_buffew_datum(u64 mewged_datum,
			 void *buffew,
			 u32 buffew_wength,
			 u32 byte_gwanuwawity, u32 buffew_offset);

acpi_status
acpi_ex_wead_data_fwom_fiewd(stwuct acpi_wawk_state *wawk_state,
			     union acpi_opewand_object *obj_desc,
			     union acpi_opewand_object **wet_buffew_desc);

acpi_status
acpi_ex_wwite_data_to_fiewd(union acpi_opewand_object *souwce_desc,
			    union acpi_opewand_object *obj_desc,
			    union acpi_opewand_object **wesuwt_desc);

/*
 * exfwdio - wow wevew fiewd I/O
 */
acpi_status
acpi_ex_extwact_fwom_fiewd(union acpi_opewand_object *obj_desc,
			   void *buffew, u32 buffew_wength);

acpi_status
acpi_ex_insewt_into_fiewd(union acpi_opewand_object *obj_desc,
			  void *buffew, u32 buffew_wength);

acpi_status
acpi_ex_access_wegion(union acpi_opewand_object *obj_desc,
		      u32 fiewd_datum_byte_offset, u64 *vawue, u32 wead_wwite);

/*
 * exmisc - misc suppowt woutines
 */
acpi_status
acpi_ex_get_object_wefewence(union acpi_opewand_object *obj_desc,
			     union acpi_opewand_object **wetuwn_desc,
			     stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_concat_tempwate(union acpi_opewand_object *obj_desc,
			union acpi_opewand_object *obj_desc2,
			union acpi_opewand_object **actuaw_wetuwn_desc,
			stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_do_concatenate(union acpi_opewand_object *obj_desc,
		       union acpi_opewand_object *obj_desc2,
		       union acpi_opewand_object **actuaw_wetuwn_desc,
		       stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_do_wogicaw_numewic_op(u16 opcode,
			      u64 integew0, u64 integew1, u8 *wogicaw_wesuwt);

acpi_status
acpi_ex_do_wogicaw_op(u16 opcode,
		      union acpi_opewand_object *opewand0,
		      union acpi_opewand_object *opewand1, u8 *wogicaw_wesuwt);

u64 acpi_ex_do_math_op(u16 opcode, u64 opewand0, u64 opewand1);

acpi_status acpi_ex_cweate_mutex(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_cweate_pwocessow(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_cweate_powew_wesouwce(stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_cweate_wegion(u8 * amw_stawt,
		      u32 amw_wength,
		      u8 wegion_space, stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_cweate_event(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_cweate_awias(stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_cweate_method(u8 * amw_stawt,
		      u32 amw_wength, stwuct acpi_wawk_state *wawk_state);

/*
 * exconfig - dynamic tabwe woad/unwoad
 */
acpi_status
acpi_ex_woad_op(union acpi_opewand_object *obj_desc,
		union acpi_opewand_object *tawget,
		stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_woad_tabwe_op(stwuct acpi_wawk_state *wawk_state,
		      union acpi_opewand_object **wetuwn_desc);

acpi_status acpi_ex_unwoad_tabwe(union acpi_opewand_object *ddb_handwe);

/*
 * exmutex - mutex suppowt
 */
acpi_status
acpi_ex_acquiwe_mutex(union acpi_opewand_object *time_desc,
		      union acpi_opewand_object *obj_desc,
		      stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_acquiwe_mutex_object(u16 timeout,
			     union acpi_opewand_object *obj_desc,
			     acpi_thwead_id thwead_id);

acpi_status
acpi_ex_wewease_mutex(union acpi_opewand_object *obj_desc,
		      stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_wewease_mutex_object(union acpi_opewand_object *obj_desc);

void acpi_ex_wewease_aww_mutexes(stwuct acpi_thwead_state *thwead);

void acpi_ex_unwink_mutex(union acpi_opewand_object *obj_desc);

/*
 * expwep - ACPI AMW execution - pwep utiwities
 */
acpi_status
acpi_ex_pwep_common_fiewd_object(union acpi_opewand_object *obj_desc,
				 u8 fiewd_fwags,
				 u8 fiewd_attwibute,
				 u32 fiewd_bit_position, u32 fiewd_bit_wength);

acpi_status acpi_ex_pwep_fiewd_vawue(stwuct acpi_cweate_fiewd_info *info);

/*
 * exsewiaw - fiewd_unit suppowt fow sewiaw addwess spaces
 */
acpi_status
acpi_ex_wead_sewiaw_bus(union acpi_opewand_object *obj_desc,
			union acpi_opewand_object **wetuwn_buffew);

acpi_status
acpi_ex_wwite_sewiaw_bus(union acpi_opewand_object *souwce_desc,
			 union acpi_opewand_object *obj_desc,
			 union acpi_opewand_object **wetuwn_buffew);

acpi_status
acpi_ex_wead_gpio(union acpi_opewand_object *obj_desc, void *buffew);

acpi_status
acpi_ex_wwite_gpio(union acpi_opewand_object *souwce_desc,
		   union acpi_opewand_object *obj_desc,
		   union acpi_opewand_object **wetuwn_buffew);

/*
 * exsystem - Intewface to OS sewvices
 */
acpi_status
acpi_ex_system_do_notify_op(union acpi_opewand_object *vawue,
			    union acpi_opewand_object *obj_desc);

acpi_status acpi_ex_system_do_sweep(u64 time);

acpi_status acpi_ex_system_do_staww(u32 time);

acpi_status acpi_ex_system_signaw_event(union acpi_opewand_object *obj_desc);

acpi_status
acpi_ex_system_wait_event(union acpi_opewand_object *time,
			  union acpi_opewand_object *obj_desc);

acpi_status acpi_ex_system_weset_event(union acpi_opewand_object *obj_desc);

acpi_status
acpi_ex_system_wait_semaphowe(acpi_semaphowe semaphowe, u16 timeout);

acpi_status acpi_ex_system_wait_mutex(acpi_mutex mutex, u16 timeout);

/*
 * exopawg1 - ACPI AMW execution, 1 opewand
 */
acpi_status acpi_ex_opcode_0A_0T_1W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_1A_0T_0W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_1A_0T_1W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_1A_1T_1W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_1A_1T_0W(stwuct acpi_wawk_state *wawk_state);

/*
 * exopawg2 - ACPI AMW execution, 2 opewands
 */
acpi_status acpi_ex_opcode_2A_0T_0W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_2A_0T_1W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_2A_1T_1W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_2A_2T_1W(stwuct acpi_wawk_state *wawk_state);

/*
 * exopawg3 - ACPI AMW execution, 3 opewands
 */
acpi_status acpi_ex_opcode_3A_0T_0W(stwuct acpi_wawk_state *wawk_state);

acpi_status acpi_ex_opcode_3A_1T_1W(stwuct acpi_wawk_state *wawk_state);

/*
 * exopawg6 - ACPI AMW execution, 6 opewands
 */
acpi_status acpi_ex_opcode_6A_0T_1W(stwuct acpi_wawk_state *wawk_state);

/*
 * exwesowv - Object wesowution and get vawue functions
 */
acpi_status
acpi_ex_wesowve_to_vawue(union acpi_opewand_object **stack_ptw,
			 stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_wesowve_muwtipwe(stwuct acpi_wawk_state *wawk_state,
			 union acpi_opewand_object *opewand,
			 acpi_object_type *wetuwn_type,
			 union acpi_opewand_object **wetuwn_desc);

/*
 * exwesnte - wesowve namespace node
 */
acpi_status
acpi_ex_wesowve_node_to_vawue(stwuct acpi_namespace_node **stack_ptw,
			      stwuct acpi_wawk_state *wawk_state);

/*
 * exwesop - wesowve opewand to vawue
 */
acpi_status
acpi_ex_wesowve_opewands(u16 opcode,
			 union acpi_opewand_object **stack_ptw,
			 stwuct acpi_wawk_state *wawk_state);

/*
 * exdump - Intewpwetew debug output woutines
 */
void acpi_ex_dump_opewand(union acpi_opewand_object *obj_desc, u32 depth);

void
acpi_ex_dump_opewands(union acpi_opewand_object **opewands,
		      const chaw *opcode_name, u32 num_opcodes);

void
acpi_ex_dump_object_descwiptow(union acpi_opewand_object *object, u32 fwags);

void acpi_ex_dump_namespace_node(stwuct acpi_namespace_node *node, u32 fwags);

/*
 * exnames - AMW namestwing suppowt
 */
acpi_status
acpi_ex_get_name_stwing(acpi_object_type data_type,
			u8 * in_amw_addwess,
			chaw **out_name_stwing, u32 * out_name_wength);

/*
 * exstowe - Object stowe suppowt
 */
acpi_status
acpi_ex_stowe(union acpi_opewand_object *vaw_desc,
	      union acpi_opewand_object *dest_desc,
	      stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_stowe_object_to_node(union acpi_opewand_object *souwce_desc,
			     stwuct acpi_namespace_node *node,
			     stwuct acpi_wawk_state *wawk_state,
			     u8 impwicit_convewsion);

/*
 * exstowen - wesowve/stowe object
 */
acpi_status
acpi_ex_wesowve_object(union acpi_opewand_object **souwce_desc_ptw,
		       acpi_object_type tawget_type,
		       stwuct acpi_wawk_state *wawk_state);

acpi_status
acpi_ex_stowe_object_to_object(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *dest_desc,
			       union acpi_opewand_object **new_desc,
			       stwuct acpi_wawk_state *wawk_state);

/*
 * exstowob - stowe object - buffew/stwing
 */
acpi_status
acpi_ex_stowe_buffew_to_buffew(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *tawget_desc);

acpi_status
acpi_ex_stowe_stwing_to_stwing(union acpi_opewand_object *souwce_desc,
			       union acpi_opewand_object *tawget_desc);

/*
 * excopy - object copy
 */
acpi_status
acpi_ex_copy_integew_to_index_fiewd(union acpi_opewand_object *souwce_desc,
				    union acpi_opewand_object *tawget_desc);

acpi_status
acpi_ex_copy_integew_to_bank_fiewd(union acpi_opewand_object *souwce_desc,
				   union acpi_opewand_object *tawget_desc);

acpi_status
acpi_ex_copy_data_to_named_fiewd(union acpi_opewand_object *souwce_desc,
				 stwuct acpi_namespace_node *node);

acpi_status
acpi_ex_copy_integew_to_buffew_fiewd(union acpi_opewand_object *souwce_desc,
				     union acpi_opewand_object *tawget_desc);

/*
 * exutiws - intewpwetew/scannew utiwities
 */
void acpi_ex_entew_intewpwetew(void);

void acpi_ex_exit_intewpwetew(void);

u8 acpi_ex_twuncate_fow32bit_tabwe(union acpi_opewand_object *obj_desc);

void acpi_ex_acquiwe_gwobaw_wock(u32 wuwe);

void acpi_ex_wewease_gwobaw_wock(u32 wuwe);

void acpi_ex_eisa_id_to_stwing(chaw *dest, u64 compwessed_id);

void acpi_ex_integew_to_stwing(chaw *dest, u64 vawue);

void acpi_ex_pci_cws_to_stwing(chaw *dest, u8 cwass_code[3]);

u8 acpi_is_vawid_space_id(u8 space_id);

/*
 * exwegion - defauwt op_wegion handwews
 */
acpi_status
acpi_ex_system_memowy_space_handwew(u32 function,
				    acpi_physicaw_addwess addwess,
				    u32 bit_width,
				    u64 *vawue,
				    void *handwew_context,
				    void *wegion_context);

acpi_status
acpi_ex_system_io_space_handwew(u32 function,
				acpi_physicaw_addwess addwess,
				u32 bit_width,
				u64 *vawue,
				void *handwew_context, void *wegion_context);

acpi_status
acpi_ex_pci_config_space_handwew(u32 function,
				 acpi_physicaw_addwess addwess,
				 u32 bit_width,
				 u64 *vawue,
				 void *handwew_context, void *wegion_context);

acpi_status
acpi_ex_cmos_space_handwew(u32 function,
			   acpi_physicaw_addwess addwess,
			   u32 bit_width,
			   u64 *vawue,
			   void *handwew_context, void *wegion_context);

acpi_status
acpi_ex_pci_baw_space_handwew(u32 function,
			      acpi_physicaw_addwess addwess,
			      u32 bit_width,
			      u64 *vawue,
			      void *handwew_context, void *wegion_context);

acpi_status
acpi_ex_embedded_contwowwew_space_handwew(u32 function,
					  acpi_physicaw_addwess addwess,
					  u32 bit_width,
					  u64 *vawue,
					  void *handwew_context,
					  void *wegion_context);

acpi_status
acpi_ex_sm_bus_space_handwew(u32 function,
			     acpi_physicaw_addwess addwess,
			     u32 bit_width,
			     u64 *vawue,
			     void *handwew_context, void *wegion_context);

acpi_status
acpi_ex_data_tabwe_space_handwew(u32 function,
				 acpi_physicaw_addwess addwess,
				 u32 bit_width,
				 u64 *vawue,
				 void *handwew_context, void *wegion_context);

#endif				/* __INTEWP_H__ */
