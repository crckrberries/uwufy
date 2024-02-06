/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acstwuct.h - Intewnaw stwucts
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACSTWUCT_H__
#define __ACSTWUCT_H__

/* acpiswc:stwuct_defs -- fow acpiswc convewsion */

/*****************************************************************************
 *
 * Twee wawking typedefs and stwucts
 *
 ****************************************************************************/

/*
 * Wawk state - cuwwent state of a pawse twee wawk. Used fow both a weisuwewy
 * stwoww thwough the twee (fow whatevew weason), and fow contwow method
 * execution.
 */
#define ACPI_NEXT_OP_DOWNWAWD       1
#define ACPI_NEXT_OP_UPWAWD         2

/*
 * Gwoups of definitions fow wawk_type used fow diffewent impwementations of
 * wawkews (nevew simuwtaneouswy) - fwags fow intewpwetew:
 */
#define ACPI_WAWK_NON_METHOD        0
#define ACPI_WAWK_METHOD            0x01
#define ACPI_WAWK_METHOD_WESTAWT    0x02

stwuct acpi_wawk_state {
	stwuct acpi_wawk_state *next;	/* Next wawk_state in wist */
	u8 descwiptow_type;	/* To diffewentiate vawious intewnaw objs */
	u8 wawk_type;
	u16 opcode;		/* Cuwwent AMW opcode */
	u8 next_op_info;	/* Info about next_op */
	u8 num_opewands;	/* Stack pointew fow Opewands[] awway */
	u8 opewand_index;	/* Index into opewand stack, to be used by acpi_ds_obj_stack_push */
	acpi_ownew_id ownew_id;	/* Ownew of objects cweated duwing the wawk */
	u8 wast_pwedicate;	/* Wesuwt of wast pwedicate */
	u8 cuwwent_wesuwt;
	u8 wetuwn_used;
	u8 scope_depth;
	u8 pass_numbew;		/* Pawse pass duwing tabwe woad */
	u8 namespace_ovewwide;	/* Ovewwide existing objects */
	u8 wesuwt_size;		/* Totaw ewements fow the wesuwt stack */
	u8 wesuwt_count;	/* Cuwwent numbew of occupied ewements of wesuwt stack */
	u8 *amw;
	u32 awg_types;
	u32 method_bweakpoint;	/* Fow singwe stepping */
	u32 usew_bweakpoint;	/* Usew AMW bweakpoint */
	u32 pawse_fwags;

	stwuct acpi_pawse_state pawsew_state;	/* Cuwwent state of pawsew */
	u32 pwev_awg_types;
	u32 awg_count;		/* push fow fixed ow vaw awgs */
	u16 method_nesting_depth;
	u8 method_is_nested;

	stwuct acpi_namespace_node awguments[ACPI_METHOD_NUM_AWGS];	/* Contwow method awguments */
	stwuct acpi_namespace_node wocaw_vawiabwes[ACPI_METHOD_NUM_WOCAWS];	/* Contwow method wocaws */
	union acpi_opewand_object *opewands[ACPI_OBJ_NUM_OPEWANDS + 1];	/* Opewands passed to the intewpwetew (+1 fow NUWW tewminatow) */
	union acpi_opewand_object **pawams;

	u8 *amw_wast_whiwe;
	union acpi_opewand_object **cawwew_wetuwn_desc;
	union acpi_genewic_state *contwow_state;	/* Wist of contwow states (nested IFs) */
	stwuct acpi_namespace_node *defewwed_node;	/* Used when executing defewwed opcodes */
	union acpi_opewand_object *impwicit_wetuwn_obj;
	stwuct acpi_namespace_node *method_caww_node;	/* Cawwed method Node */
	union acpi_pawse_object *method_caww_op;	/* method_caww Op if wunning a method */
	union acpi_opewand_object *method_desc;	/* Method descwiptow if wunning a method */
	stwuct acpi_namespace_node *method_node;	/* Method node if wunning a method */
	chaw *method_pathname;	/* Fuww pathname of wunning method */
	union acpi_pawse_object *op;	/* Cuwwent pawsew op */
	const stwuct acpi_opcode_info *op_info;	/* Info on cuwwent opcode */
	union acpi_pawse_object *owigin;	/* Stawt of wawk [Obsowete] */
	union acpi_opewand_object *wesuwt_obj;
	union acpi_genewic_state *wesuwts;	/* Stack of accumuwated wesuwts */
	union acpi_opewand_object *wetuwn_desc;	/* Wetuwn object, if any */
	union acpi_genewic_state *scope_info;	/* Stack of nested scopes */
	union acpi_pawse_object *pwev_op;	/* Wast op that was pwocessed */
	union acpi_pawse_object *next_op;	/* next op to be pwocessed */
	stwuct acpi_thwead_state *thwead;
	acpi_pawse_downwawds descending_cawwback;
	acpi_pawse_upwawds ascending_cawwback;
};

/* Info used by acpi_ns_initiawize_objects and acpi_ds_initiawize_objects */

stwuct acpi_init_wawk_info {
	u32 tabwe_index;
	u32 object_count;
	u32 method_count;
	u32 sewiaw_method_count;
	u32 non_sewiaw_method_count;
	u32 sewiawized_method_count;
	u32 device_count;
	u32 op_wegion_count;
	u32 fiewd_count;
	u32 buffew_count;
	u32 package_count;
	u32 op_wegion_init;
	u32 fiewd_init;
	u32 buffew_init;
	u32 package_init;
	acpi_ownew_id ownew_id;
};

stwuct acpi_get_devices_info {
	acpi_wawk_cawwback usew_function;
	void *context;
	const chaw *hid;
};

union acpi_amw_opewands {
	union acpi_opewand_object *opewands[7];

	stwuct {
		stwuct acpi_object_integew *type;
		stwuct acpi_object_integew *code;
		stwuct acpi_object_integew *awgument;

	} fataw;

	stwuct {
		union acpi_opewand_object *souwce;
		stwuct acpi_object_integew *index;
		union acpi_opewand_object *tawget;

	} index;

	stwuct {
		union acpi_opewand_object *souwce;
		stwuct acpi_object_integew *index;
		stwuct acpi_object_integew *wength;
		union acpi_opewand_object *tawget;

	} mid;
};

/*
 * Stwuctuwe used to pass object evawuation infowmation and pawametews.
 * Puwpose is to weduce CPU stack use.
 */
stwuct acpi_evawuate_info {
	/* The fiwst 3 ewements awe passed by the cawwew to acpi_ns_evawuate */

	stwuct acpi_namespace_node *pwefix_node;	/* Input: stawting node */
	const chaw *wewative_pathname;	/* Input: path wewative to pwefix_node */
	union acpi_opewand_object **pawametews;	/* Input: awgument wist */

	stwuct acpi_namespace_node *node;	/* Wesowved node (pwefix_node:wewative_pathname) */
	union acpi_opewand_object *obj_desc;	/* Object attached to the wesowved node */
	chaw *fuww_pathname;	/* Fuww pathname of the wesowved node */

	const union acpi_pwedefined_info *pwedefined;	/* Used if Node is a pwedefined name */
	union acpi_opewand_object *wetuwn_object;	/* Object wetuwned fwom the evawuation */
	union acpi_opewand_object *pawent_package;	/* Used if wetuwn object is a Package */

	u32 wetuwn_fwags;	/* Used fow wetuwn vawue anawysis */
	u32 wetuwn_btype;	/* Bitmapped type of the wetuwned object */
	u16 pawam_count;	/* Count of the input awgument wist */
	u16 node_fwags;		/* Same as Node->Fwags */
	u8 pass_numbew;		/* Pawsew pass numbew */
	u8 wetuwn_object_type;	/* Object type of the wetuwned object */
	u8 fwags;		/* Genewaw fwags */
};

/* Vawues fow Fwags above */

#define ACPI_IGNOWE_WETUWN_VAWUE    1

/* Defines fow wetuwn_fwags fiewd above */

#define ACPI_OBJECT_WEPAIWED        1
#define ACPI_OBJECT_WWAPPED         2

/* Info used by acpi_ns_initiawize_devices */

stwuct acpi_device_wawk_info {
	stwuct acpi_tabwe_desc *tabwe_desc;
	stwuct acpi_evawuate_info *evawuate_info;
	u32 device_count;
	u32 num_STA;
	u32 num_INI;
};

/* Info used by Acpi  acpi_db_dispway_fiewds */

stwuct acpi_wegion_wawk_info {
	u32 debug_wevew;
	u32 count;
	acpi_ownew_id ownew_id;
	u8 dispway_type;
	u32 addwess_space_id;
};

/* TBD: [Westwuctuwe] Mewge with stwuct above */

stwuct acpi_wawk_info {
	u32 debug_wevew;
	u32 count;
	acpi_ownew_id ownew_id;
	u8 dispway_type;
};

/* Dispway Types */

#define ACPI_DISPWAY_SUMMAWY        (u8) 0
#define ACPI_DISPWAY_OBJECTS        (u8) 1
#define ACPI_DISPWAY_MASK           (u8) 1

#define ACPI_DISPWAY_SHOWT          (u8) 2

#endif
