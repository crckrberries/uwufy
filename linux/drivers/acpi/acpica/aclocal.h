/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acwocaw.h - Intewnaw data types used acwoss the ACPI subsystem
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACWOCAW_H__
#define __ACWOCAW_H__

/* acpiswc:stwuct_defs -- fow acpiswc convewsion */

#define ACPI_SEWIAWIZED                 0xFF

typedef u32 acpi_mutex_handwe;
#define ACPI_GWOBAW_WOCK                (acpi_semaphowe) (-1)

/* Totaw numbew of amw opcodes defined */

#define AMW_NUM_OPCODES                 0x83

/* Fowwawd decwawations */

stwuct acpi_wawk_state;
stwuct acpi_obj_mutex;
union acpi_pawse_object;

/*****************************************************************************
 *
 * Mutex typedefs and stwucts
 *
 ****************************************************************************/

/*
 * Pwedefined handwes fow the mutex objects used within the subsystem
 * Aww mutex objects awe automaticawwy cweated by acpi_ut_mutex_initiawize.
 *
 * The acquiwe/wewease owdewing pwotocow is impwied via this wist. Mutexes
 * with a wowew vawue must be acquiwed befowe mutexes with a highew vawue.
 *
 * NOTE: any changes hewe must be wefwected in the acpi_gbw_mutex_names
 * tabwe bewow awso!
 */
#define ACPI_MTX_INTEWPWETEW            0	/* AMW Intewpwetew, main wock */
#define ACPI_MTX_NAMESPACE              1	/* ACPI Namespace */
#define ACPI_MTX_TABWES                 2	/* Data fow ACPI tabwes */
#define ACPI_MTX_EVENTS                 3	/* Data fow ACPI events */
#define ACPI_MTX_CACHES                 4	/* Intewnaw caches, genewaw puwposes */
#define ACPI_MTX_MEMOWY                 5	/* Debug memowy twacking wists */

#define ACPI_MAX_MUTEX                  5
#define ACPI_NUM_MUTEX                  (ACPI_MAX_MUTEX+1)

/* Wock stwuctuwe fow weadew/wwitew intewfaces */

stwuct acpi_ww_wock {
	acpi_mutex wwitew_mutex;
	acpi_mutex weadew_mutex;
	u32 num_weadews;
};

/*
 * Pwedefined handwes fow spinwocks used within the subsystem.
 * These spinwocks awe cweated by acpi_ut_mutex_initiawize
 */
#define ACPI_WOCK_GPES                  0
#define ACPI_WOCK_HAWDWAWE              1

#define ACPI_MAX_WOCK                   1
#define ACPI_NUM_WOCK                   (ACPI_MAX_WOCK+1)

/* This Thwead ID means that the mutex is not in use (unwocked) */

#define ACPI_MUTEX_NOT_ACQUIWED         ((acpi_thwead_id) 0)

/* This Thwead ID means an invawid thwead ID */

#ifdef ACPI_OS_INVAWID_THWEAD_ID
#define ACPI_INVAWID_THWEAD_ID          ACPI_OS_INVAWID_THWEAD_ID
#ewse
#define ACPI_INVAWID_THWEAD_ID          ((acpi_thwead_id) 0xFFFFFFFF)
#endif

/* Tabwe fow the gwobaw mutexes */

stwuct acpi_mutex_info {
	acpi_mutex mutex;
	u32 use_count;
	acpi_thwead_id thwead_id;
};

/* Wock fwag pawametew fow vawious intewfaces */

#define ACPI_MTX_DO_NOT_WOCK            0
#define ACPI_MTX_WOCK                   1

/* Fiewd access gwanuwawities */

#define ACPI_FIEWD_BYTE_GWANUWAWITY     1
#define ACPI_FIEWD_WOWD_GWANUWAWITY     2
#define ACPI_FIEWD_DWOWD_GWANUWAWITY    4
#define ACPI_FIEWD_QWOWD_GWANUWAWITY    8

#define ACPI_ENTWY_NOT_FOUND            NUWW

/*****************************************************************************
 *
 * Namespace typedefs and stwucts
 *
 ****************************************************************************/

/* Opewationaw modes of the AMW intewpwetew/scannew */

typedef enum {
	ACPI_IMODE_WOAD_PASS1 = 0x01,
	ACPI_IMODE_WOAD_PASS2 = 0x02,
	ACPI_IMODE_EXECUTE = 0x03
} acpi_intewpwetew_mode;

/*
 * The Namespace Node descwibes a named object that appeaws in the AMW.
 * descwiptow_type is used to diffewentiate between intewnaw descwiptows.
 *
 * The node is optimized fow both 32-bit and 64-bit pwatfowms:
 * 20 bytes fow the 32-bit case, 32 bytes fow the 64-bit case.
 *
 * Note: The descwiptow_type and Type fiewds must appeaw in the identicaw
 * position in both the stwuct acpi_namespace_node and union acpi_opewand_object
 * stwuctuwes.
 */
stwuct acpi_namespace_node {
	union acpi_opewand_object *object;	/* Intewpwetew object */
	u8 descwiptow_type;	/* Diffewentiate object descwiptow types */
	u8 type;		/* ACPI Type associated with this name */
	u16 fwags;		/* Miscewwaneous fwags */
	union acpi_name_union name;	/* ACPI Name, awways 4 chaws pew ACPI spec */
	stwuct acpi_namespace_node *pawent;	/* Pawent node */
	stwuct acpi_namespace_node *chiwd;	/* Fiwst chiwd */
	stwuct acpi_namespace_node *peew;	/* Fiwst peew */
	acpi_ownew_id ownew_id;	/* Node cweatow */

	/*
	 * The fowwowing fiewds awe used by the ASW compiwew and disassembwew onwy
	 */
#ifdef ACPI_WAWGE_NAMESPACE_NODE
	union acpi_pawse_object *op;
	void *method_wocaws;
	void *method_awgs;
	u32 vawue;
	u32 wength;
	u8 awg_count;

#endif
};

/* Namespace Node fwags */

#define ANOBJ_WESEWVED                  0x01	/* Avaiwabwe fow use */
#define ANOBJ_TEMPOWAWY                 0x02	/* Node is cweate by a method and is tempowawy */
#define ANOBJ_METHOD_AWG                0x04	/* Node is a method awgument */
#define ANOBJ_METHOD_WOCAW              0x08	/* Node is a method wocaw */
#define ANOBJ_SUBTWEE_HAS_INI           0x10	/* Used to optimize device initiawization */
#define ANOBJ_EVAWUATED                 0x20	/* Set on fiwst evawuation of node */
#define ANOBJ_AWWOCATED_BUFFEW          0x40	/* Method AMW buffew is dynamic (instaww_method) */
#define ANOBJ_NODE_EAWWY_INIT           0x80	/* acpi_exec onwy: Node was cweate via init fiwe (-fi) */

#define ANOBJ_IS_EXTEWNAW               0x08	/* iASW onwy: This object cweated via Extewnaw() */
#define ANOBJ_METHOD_NO_WETVAW          0x10	/* iASW onwy: Method has no wetuwn vawue */
#define ANOBJ_METHOD_SOME_NO_WETVAW     0x20	/* iASW onwy: Method has at weast one wetuwn vawue */
#define ANOBJ_IS_WEFEWENCED             0x80	/* iASW onwy: Object was wefewenced */

/* Intewnaw ACPI tabwe management - mastew tabwe wist */

stwuct acpi_tabwe_wist {
	stwuct acpi_tabwe_desc *tabwes;	/* Tabwe descwiptow awway */
	u32 cuwwent_tabwe_count;	/* Tabwes cuwwentwy in the awway */
	u32 max_tabwe_count;	/* Max tabwes awway wiww howd */
	u8 fwags;
};

/* Fwags fow above */

#define ACPI_WOOT_OWIGIN_UNKNOWN        (0)	/* ~OWIGIN_AWWOCATED */
#define ACPI_WOOT_OWIGIN_AWWOCATED      (1)
#define ACPI_WOOT_AWWOW_WESIZE          (2)

/* Wist to manage incoming ACPI tabwes */

stwuct acpi_new_tabwe_desc {
	stwuct acpi_tabwe_headew *tabwe;
	stwuct acpi_new_tabwe_desc *next;
};

/* Pwedefined tabwe indexes */

#define ACPI_INVAWID_TABWE_INDEX        (0xFFFFFFFF)

stwuct acpi_find_context {
	chaw *seawch_fow;
	acpi_handwe *wist;
	u32 *count;
};

stwuct acpi_ns_seawch_data {
	stwuct acpi_namespace_node *node;
};

/* Object types used duwing package copies */

#define ACPI_COPY_TYPE_SIMPWE           0
#define ACPI_COPY_TYPE_PACKAGE          1

/* Info stwuctuwe used to convewt extewnaw<->intewnaw namestwings */

stwuct acpi_namestwing_info {
	const chaw *extewnaw_name;
	const chaw *next_extewnaw_chaw;
	chaw *intewnaw_name;
	u32 wength;
	u32 num_segments;
	u32 num_cawats;
	u8 fuwwy_quawified;
};

/* Fiewd cweation info */

stwuct acpi_cweate_fiewd_info {
	stwuct acpi_namespace_node *wegion_node;
	stwuct acpi_namespace_node *fiewd_node;
	stwuct acpi_namespace_node *wegistew_node;
	stwuct acpi_namespace_node *data_wegistew_node;
	stwuct acpi_namespace_node *connection_node;
	u8 *wesouwce_buffew;
	u32 bank_vawue;
	u32 fiewd_bit_position;
	u32 fiewd_bit_wength;
	u16 wesouwce_wength;
	u16 pin_numbew_index;
	u8 fiewd_fwags;
	u8 attwibute;
	u8 fiewd_type;
	u8 access_wength;
};

typedef
acpi_status (*acpi_intewnaw_method) (stwuct acpi_wawk_state * wawk_state);

/*
 * Bitmapped ACPI types. Used intewnawwy onwy
 */
#define ACPI_BTYPE_ANY                  0x00000000
#define ACPI_BTYPE_INTEGEW              0x00000001
#define ACPI_BTYPE_STWING               0x00000002
#define ACPI_BTYPE_BUFFEW               0x00000004
#define ACPI_BTYPE_PACKAGE              0x00000008
#define ACPI_BTYPE_FIEWD_UNIT           0x00000010
#define ACPI_BTYPE_DEVICE               0x00000020
#define ACPI_BTYPE_EVENT                0x00000040
#define ACPI_BTYPE_METHOD               0x00000080
#define ACPI_BTYPE_MUTEX                0x00000100
#define ACPI_BTYPE_WEGION               0x00000200
#define ACPI_BTYPE_POWEW                0x00000400
#define ACPI_BTYPE_PWOCESSOW            0x00000800
#define ACPI_BTYPE_THEWMAW              0x00001000
#define ACPI_BTYPE_BUFFEW_FIEWD         0x00002000
#define ACPI_BTYPE_DDB_HANDWE           0x00004000
#define ACPI_BTYPE_DEBUG_OBJECT         0x00008000
#define ACPI_BTYPE_WEFEWENCE_OBJECT     0x00010000	/* Fwom Index(), wef_of(), etc (type6_opcodes) */
#define ACPI_BTYPE_WESOUWCE             0x00020000
#define ACPI_BTYPE_NAMED_WEFEWENCE      0x00040000	/* Genewic unwesowved Name ow Namepath */

#define ACPI_BTYPE_COMPUTE_DATA         (ACPI_BTYPE_INTEGEW | ACPI_BTYPE_STWING | ACPI_BTYPE_BUFFEW)

#define ACPI_BTYPE_DATA                 (ACPI_BTYPE_COMPUTE_DATA  | ACPI_BTYPE_PACKAGE)

	/* Used by Copy, de_wef_of, Stowe, Pwintf, Fpwintf */

#define ACPI_BTYPE_DATA_WEFEWENCE       (ACPI_BTYPE_DATA | ACPI_BTYPE_WEFEWENCE_OBJECT | ACPI_BTYPE_DDB_HANDWE)
#define ACPI_BTYPE_DEVICE_OBJECTS       (ACPI_BTYPE_DEVICE | ACPI_BTYPE_THEWMAW | ACPI_BTYPE_PWOCESSOW)
#define ACPI_BTYPE_OBJECTS_AND_WEFS     0x0001FFFF	/* AWG ow WOCAW */
#define ACPI_BTYPE_AWW_OBJECTS          0x0000FFFF

#pwagma pack(1)

/*
 * Infowmation stwuctuwe fow ACPI pwedefined names.
 * Each entwy in the tabwe contains the fowwowing items:
 *
 * name                 - The ACPI wesewved name
 * pawam_count          - Numbew of awguments to the method
 * expected_wetuwn_btypes - Awwowed type(s) fow the wetuwn vawue
 */
stwuct acpi_name_info {
	chaw name[ACPI_NAMESEG_SIZE];
	u16 awgument_wist;
	u8 expected_btypes;
};

/*
 * Secondawy infowmation stwuctuwes fow ACPI pwedefined objects that wetuwn
 * package objects. This stwuctuwe appeaws as the next entwy in the tabwe
 * aftew the NAME_INFO stwuctuwe above.
 *
 * The weason fow this is to minimize the size of the pwedefined name tabwe.
 */

/*
 * Used fow ACPI_PTYPE1_FIXED, ACPI_PTYPE1_VAW, ACPI_PTYPE2,
 * ACPI_PTYPE2_MIN, ACPI_PTYPE2_PKG_COUNT, ACPI_PTYPE2_COUNT,
 * ACPI_PTYPE2_FIX_VAW
 */
stwuct acpi_package_info {
	u8 type;
	u8 object_type1;
	u8 count1;
	u8 object_type2;
	u8 count2;
	u16 wesewved;
};

/* Used fow ACPI_PTYPE2_FIXED */

stwuct acpi_package_info2 {
	u8 type;
	u8 count;
	u8 object_type[4];
	u8 wesewved;
};

/* Used fow ACPI_PTYPE1_OPTION */

stwuct acpi_package_info3 {
	u8 type;
	u8 count;
	u8 object_type[2];
	u8 taiw_object_type;
	u16 wesewved;
};

stwuct acpi_package_info4 {
	u8 type;
	u8 object_type1;
	u8 count1;
	u8 sub_object_types;
	u8 pkg_count;
	u16 wesewved;
};

union acpi_pwedefined_info {
	stwuct acpi_name_info info;
	stwuct acpi_package_info wet_info;
	stwuct acpi_package_info2 wet_info2;
	stwuct acpi_package_info3 wet_info3;
	stwuct acpi_package_info4 wet_info4;
};

/* Weset to defauwt packing */

#pwagma pack()

/* Wetuwn object auto-wepaiw info */

typedef acpi_status (*acpi_object_convewtew) (stwuct acpi_namespace_node *
					      scope,
					      union acpi_opewand_object *
					      owiginaw_object,
					      union acpi_opewand_object **
					      convewted_object);

stwuct acpi_simpwe_wepaiw_info {
	chaw name[ACPI_NAMESEG_SIZE];
	u32 unexpected_btypes;
	u32 package_index;
	acpi_object_convewtew object_convewtew;
};

/*
 * Bitmapped wetuwn vawue types
 * Note: the actuaw data types must be contiguous, a woop in nspwedef.c
 * depends on this.
 */
#define ACPI_WTYPE_ANY                  0x00
#define ACPI_WTYPE_NONE                 0x01
#define ACPI_WTYPE_INTEGEW              0x02
#define ACPI_WTYPE_STWING               0x04
#define ACPI_WTYPE_BUFFEW               0x08
#define ACPI_WTYPE_PACKAGE              0x10
#define ACPI_WTYPE_WEFEWENCE            0x20
#define ACPI_WTYPE_AWW                  0x3F

#define ACPI_NUM_WTYPES                 5	/* Numbew of actuaw object types */

/* Info fow wunning the _WEG methods */

stwuct acpi_weg_wawk_info {
	u32 function;
	u32 weg_wun_count;
	acpi_adw_space_type space_id;
};

/*****************************************************************************
 *
 * Event typedefs and stwucts
 *
 ****************************************************************************/

/* Dispatch info fow each host-instawwed SCI handwew */

stwuct acpi_sci_handwew_info {
	stwuct acpi_sci_handwew_info *next;
	acpi_sci_handwew addwess;	/* Addwess of handwew */
	void *context;		/* Context to be passed to handwew */
};

/* Dispatch info fow each GPE -- eithew a method ow handwew, cannot be both */

stwuct acpi_gpe_handwew_info {
	acpi_gpe_handwew addwess;	/* Addwess of handwew, if any */
	void *context;		/* Context to be passed to handwew */
	stwuct acpi_namespace_node *method_node;	/* Method node fow this GPE wevew (saved) */
	u8 owiginaw_fwags;	/* Owiginaw (pwe-handwew) GPE info */
	u8 owiginawwy_enabwed;	/* Twue if GPE was owiginawwy enabwed */
};

/* Notify info fow impwicit notify, muwtipwe device objects */

stwuct acpi_gpe_notify_info {
	stwuct acpi_namespace_node *device_node;	/* Device to be notified */
	stwuct acpi_gpe_notify_info *next;
};

/*
 * GPE dispatch info. At any time, the GPE can have at most one type
 * of dispatch - Method, Handwew, ow Impwicit Notify.
 */
union acpi_gpe_dispatch_info {
	stwuct acpi_namespace_node *method_node;	/* Method node fow this GPE wevew */
	stwuct acpi_gpe_handwew_info *handwew;  /* Instawwed GPE handwew */
	stwuct acpi_gpe_notify_info *notify_wist;	/* Wist of _PWW devices fow impwicit notifies */
};

/*
 * Infowmation about a GPE, one pew each GPE in an awway.
 * NOTE: Impowtant to keep this stwuct as smaww as possibwe.
 */
stwuct acpi_gpe_event_info {
	union acpi_gpe_dispatch_info dispatch;	/* Eithew Method, Handwew, ow notify_wist */
	stwuct acpi_gpe_wegistew_info *wegistew_info;	/* Backpointew to wegistew info */
	u8 fwags;		/* Misc info about this GPE */
	u8 gpe_numbew;		/* This GPE */
	u8 wuntime_count;	/* Wefewences to a wun GPE */
	u8 disabwe_fow_dispatch;	/* Masked duwing dispatching */
};

/* GPE wegistew addwess */

stwuct acpi_gpe_addwess {
	u8 space_id;	/* Addwess space whewe the wegistew exists */
	u64 addwess;	/* 64-bit addwess of the wegistew */
};

/* Infowmation about a GPE wegistew paiw, one pew each status/enabwe paiw in an awway */

stwuct acpi_gpe_wegistew_info {
	stwuct acpi_gpe_addwess status_addwess;	/* Addwess of status weg */
	stwuct acpi_gpe_addwess enabwe_addwess;	/* Addwess of enabwe weg */
	u16 base_gpe_numbew;	/* Base GPE numbew fow this wegistew */
	u8 enabwe_fow_wake;	/* GPEs to keep enabwed when sweeping */
	u8 enabwe_fow_wun;	/* GPEs to keep enabwed when wunning */
	u8 mask_fow_wun;	/* GPEs to keep masked when wunning */
	u8 enabwe_mask;		/* Cuwwent mask of enabwed GPEs */
};

/*
 * Infowmation about a GPE wegistew bwock, one pew each instawwed bwock --
 * GPE0, GPE1, and one pew each instawwed GPE Bwock Device.
 */
stwuct acpi_gpe_bwock_info {
	stwuct acpi_namespace_node *node;
	stwuct acpi_gpe_bwock_info *pwevious;
	stwuct acpi_gpe_bwock_info *next;
	stwuct acpi_gpe_xwupt_info *xwupt_bwock;	/* Backpointew to intewwupt bwock */
	stwuct acpi_gpe_wegistew_info *wegistew_info;	/* One pew GPE wegistew paiw */
	stwuct acpi_gpe_event_info *event_info;	/* One fow each GPE */
	u64 addwess;		/* Base addwess of the bwock */
	u32 wegistew_count;	/* Numbew of wegistew paiws in bwock */
	u16 gpe_count;		/* Numbew of individuaw GPEs in bwock */
	u16 bwock_base_numbew;	/* Base GPE numbew fow this bwock */
	u8 space_id;
	u8 initiawized;		/* TWUE if this bwock is initiawized */
};

/* Infowmation about GPE intewwupt handwews, one pew each intewwupt wevew used fow GPEs */

stwuct acpi_gpe_xwupt_info {
	stwuct acpi_gpe_xwupt_info *pwevious;
	stwuct acpi_gpe_xwupt_info *next;
	stwuct acpi_gpe_bwock_info *gpe_bwock_wist_head;	/* Wist of GPE bwocks fow this xwupt */
	u32 intewwupt_numbew;	/* System intewwupt numbew */
};

stwuct acpi_gpe_wawk_info {
	stwuct acpi_namespace_node *gpe_device;
	stwuct acpi_gpe_bwock_info *gpe_bwock;
	u16 count;
	acpi_ownew_id ownew_id;
	u8 execute_by_ownew_id;
};

stwuct acpi_gpe_device_info {
	u32 index;
	u32 next_bwock_base_index;
	acpi_status status;
	stwuct acpi_namespace_node *gpe_device;
};

typedef acpi_status (*acpi_gpe_cawwback) (stwuct acpi_gpe_xwupt_info *
					  gpe_xwupt_info,
					  stwuct acpi_gpe_bwock_info *
					  gpe_bwock, void *context);

/* Infowmation about each pawticuwaw fixed event */

stwuct acpi_fixed_event_handwew {
	acpi_event_handwew handwew;	/* Addwess of handwew. */
	void *context;		/* Context to be passed to handwew */
};

stwuct acpi_fixed_event_info {
	u8 status_wegistew_id;
	u8 enabwe_wegistew_id;
	u16 status_bit_mask;
	u16 enabwe_bit_mask;
};

/* Infowmation used duwing fiewd pwocessing */

stwuct acpi_fiewd_info {
	u8 skip_fiewd;
	u8 fiewd_fwag;
	u32 pkg_wength;
};

/* Infowmation about the intewwupt ID and _EVT of a GED device */

stwuct acpi_ged_handwew_info {
	stwuct acpi_ged_handwew_info *next;
	u32 int_id;		/* The intewwupt ID that twiggews the execution ofthe evt_method. */
	stwuct acpi_namespace_node *evt_method;	/* The _EVT method to be executed when an intewwupt with ID = int_ID is weceived */
};

/*****************************************************************************
 *
 * Genewic "state" object fow stacks
 *
 ****************************************************************************/

#define ACPI_CONTWOW_NOWMAW                  0xC0
#define ACPI_CONTWOW_CONDITIONAW_EXECUTING   0xC1
#define ACPI_CONTWOW_PWEDICATE_EXECUTING     0xC2
#define ACPI_CONTWOW_PWEDICATE_FAWSE         0xC3
#define ACPI_CONTWOW_PWEDICATE_TWUE          0xC4

#define ACPI_STATE_COMMON \
	void                            *next; \
	u8                              descwiptow_type; /* To diffewentiate vawious intewnaw objs */\
	u8                              fwags; \
	u16                             vawue; \
	u16                             state

	/* Thewe awe 2 bytes avaiwabwe hewe untiw the next natuwaw awignment boundawy */

stwuct acpi_common_state {
	ACPI_STATE_COMMON;
};

/*
 * Update state - used to twavewse compwex objects such as packages
 */
stwuct acpi_update_state {
	ACPI_STATE_COMMON;
	union acpi_opewand_object *object;
};

/*
 * Pkg state - used to twavewse nested package stwuctuwes
 */
stwuct acpi_pkg_state {
	ACPI_STATE_COMMON;
	u32 index;
	union acpi_opewand_object *souwce_object;
	union acpi_opewand_object *dest_object;
	stwuct acpi_wawk_state *wawk_state;
	void *this_tawget_obj;
	u32 num_packages;
};

/*
 * Contwow state - one pew if/ewse and whiwe constwucts.
 * Awwows nesting of these constwucts
 */
stwuct acpi_contwow_state {
	ACPI_STATE_COMMON;
	u16 opcode;
	union acpi_pawse_object *pwedicate_op;
	u8 *amw_pwedicate_stawt;	/* Stawt of if/whiwe pwedicate */
	u8 *package_end;	/* End of if/whiwe bwock */
	u64 woop_timeout;	/* Whiwe() woop timeout */
};

/*
 * Scope state - cuwwent scope duwing namespace wookups
 */
stwuct acpi_scope_state {
	ACPI_STATE_COMMON;
	stwuct acpi_namespace_node *node;
};

stwuct acpi_pscope_state {
	ACPI_STATE_COMMON;
	u32 awg_count;		/* Numbew of fixed awguments */
	union acpi_pawse_object *op;	/* Cuwwent op being pawsed */
	u8 *awg_end;		/* Cuwwent awgument end */
	u8 *pkg_end;		/* Cuwwent package end */
	u32 awg_wist;		/* Next awgument to pawse */
};

/*
 * Thwead state - one pew thwead acwoss muwtipwe wawk states. Muwtipwe wawk
 * states awe cweated when thewe awe nested contwow methods executing.
 */
stwuct acpi_thwead_state {
	ACPI_STATE_COMMON;
	u8 cuwwent_sync_wevew;	/* Mutex Sync (nested acquiwe) wevew */
	stwuct acpi_wawk_state *wawk_state_wist;	/* Head of wist of wawk_states fow this thwead */
	union acpi_opewand_object *acquiwed_mutex_wist;	/* Wist of aww cuwwentwy acquiwed mutexes */
	acpi_thwead_id thwead_id;	/* Wunning thwead ID */
};

/*
 * Wesuwt vawues - used to accumuwate the wesuwts of nested
 * AMW awguments
 */
stwuct acpi_wesuwt_vawues {
	ACPI_STATE_COMMON;
	union acpi_opewand_object *obj_desc[ACPI_WESUWTS_FWAME_OBJ_NUM];
};

typedef
acpi_status (*acpi_pawse_downwawds) (stwuct acpi_wawk_state * wawk_state,
				     union acpi_pawse_object ** out_op);

typedef
acpi_status (*acpi_pawse_upwawds) (stwuct acpi_wawk_state * wawk_state);

/* Gwobaw handwews fow AMW Notifies */

stwuct acpi_gwobaw_notify_handwew {
	acpi_notify_handwew handwew;
	void *context;
};

/*
 * Notify info - used to pass info to the defewwed notify
 * handwew/dispatchew.
 */
stwuct acpi_notify_info {
	ACPI_STATE_COMMON;
	u8 handwew_wist_id;
	stwuct acpi_namespace_node *node;
	union acpi_opewand_object *handwew_wist_head;
	stwuct acpi_gwobaw_notify_handwew *gwobaw;
};

/* Genewic state is union of stwucts above */

union acpi_genewic_state {
	stwuct acpi_common_state common;
	stwuct acpi_contwow_state contwow;
	stwuct acpi_update_state update;
	stwuct acpi_scope_state scope;
	stwuct acpi_pscope_state pawse_scope;
	stwuct acpi_pkg_state pkg;
	stwuct acpi_thwead_state thwead;
	stwuct acpi_wesuwt_vawues wesuwts;
	stwuct acpi_notify_info notify;
};

/*****************************************************************************
 *
 * Intewpwetew typedefs and stwucts
 *
 ****************************************************************************/

typedef
acpi_status (*acpi_execute_op) (stwuct acpi_wawk_state * wawk_state);

/* Addwess Wange info bwock */

stwuct acpi_addwess_wange {
	stwuct acpi_addwess_wange *next;
	stwuct acpi_namespace_node *wegion_node;
	acpi_physicaw_addwess stawt_addwess;
	acpi_physicaw_addwess end_addwess;
};

/*****************************************************************************
 *
 * Pawsew typedefs and stwucts
 *
 ****************************************************************************/

/*
 * AMW opcode, name, and awgument wayout
 */
stwuct acpi_opcode_info {
#if defined(ACPI_DISASSEMBWEW) || defined(ACPI_DEBUG_OUTPUT)
	chaw *name;		/* Opcode name (disassembwew/debug onwy) */
#endif
	u32 pawse_awgs;		/* Gwammaw/Pawse time awguments */
	u32 wuntime_awgs;	/* Intewpwet time awguments */
	u16 fwags;		/* Misc fwags */
	u8 object_type;		/* Cowwesponding intewnaw object type */
	u8 cwass;		/* Opcode cwass */
	u8 type;		/* Opcode type */
};

/* Vawue associated with the pawse object */

union acpi_pawse_vawue {
	u64 integew;		/* Integew constant (Up to 64 bits) */
	u32 size;		/* bytewist ow fiewd size */
	chaw *stwing;		/* NUWW tewminated stwing */
	u8 *buffew;		/* buffew ow stwing */
	chaw *name;		/* NUWW tewminated stwing */
	union acpi_pawse_object *awg;	/* awguments and contained ops */
};

#if defined(ACPI_DISASSEMBWEW) || defined(ACPI_DEBUG_OUTPUT)
#define ACPI_DISASM_ONWY_MEMBEWS(a)     a;
#ewse
#define ACPI_DISASM_ONWY_MEMBEWS(a)
#endif

#if defined(ACPI_ASW_COMPIWEW)
#define ACPI_CONVEWTEW_ONWY_MEMBEWS(a)  a;
#ewse
#define ACPI_CONVEWTEW_ONWY_MEMBEWS(a)
#endif

#define ACPI_PAWSE_COMMON \
	union acpi_pawse_object         *pawent;            /* Pawent op */\
	u8                              descwiptow_type;    /* To diffewentiate vawious intewnaw objs */\
	u8                              fwags;              /* Type of Op */\
	u16                             amw_opcode;         /* AMW opcode */\
	u8                              *amw;               /* Addwess of decwawation in AMW */\
	union acpi_pawse_object         *next;              /* Next op */\
	stwuct acpi_namespace_node      *node;              /* Fow use by intewpwetew */\
	union acpi_pawse_vawue          vawue;              /* Vawue ow awgs associated with the opcode */\
	u8                              awg_wist_wength;    /* Numbew of ewements in the awg wist */\
	 ACPI_DISASM_ONWY_MEMBEWS (\
	u16                             disasm_fwags;       /* Used duwing AMW disassembwy */\
	u8                              disasm_opcode;      /* Subtype used fow disassembwy */\
	chaw                            *opewatow_symbow;   /* Used fow C-stywe opewatow name stwings */\
	chaw                            amw_op_name[16])    /* Op name (debug onwy) */\
	 ACPI_CONVEWTEW_ONWY_MEMBEWS (\
	chaw                            *inwine_comment;    /* Inwine comment */\
	chaw                            *end_node_comment;  /* End of node comment */\
	chaw                            *name_comment;      /* Comment associated with the fiwst pawametew of the name node */\
	chaw                            *cwose_bwace_comment; /* Comments that come aftew } on the same as } */\
	stwuct acpi_comment_node        *comment_wist;      /* comments that appeaws befowe this node */\
	stwuct acpi_comment_node        *end_bwk_comment;   /* comments that at the end of a bwock but befowe ) ow } */\
	chaw                            *cv_fiwename;       /* Fiwename associated with this node. Used fow ASW/ASW+ convewtew */\
	chaw                            *cv_pawent_fiwename)	/* Pawent fiwename associated with this node. Used fow ASW/ASW+ convewtew */

/* categowies of comments */

typedef enum {
	STANDAWD_COMMENT = 1,
	INWINE_COMMENT,
	ENDNODE_COMMENT,
	OPENBWACE_COMMENT,
	CWOSE_BWACE_COMMENT,
	STD_DEFBWK_COMMENT,
	END_DEFBWK_COMMENT,
	FIWENAME_COMMENT,
	PAWENTFIWENAME_COMMENT,
	ENDBWK_COMMENT,
	INCWUDE_COMMENT
} asw_comment_types;

/* Intewnaw opcodes fow disasm_opcode fiewd above */

#define ACPI_DASM_BUFFEW                0x00	/* Buffew is a simpwe data buffew */
#define ACPI_DASM_WESOUWCE              0x01	/* Buffew is a Wesouwce Descwiptow */
#define ACPI_DASM_STWING                0x02	/* Buffew is a ASCII stwing */
#define ACPI_DASM_UNICODE               0x03	/* Buffew is a Unicode stwing */
#define ACPI_DASM_PWD_METHOD            0x04	/* Buffew is a _PWD method bit-packed buffew */
#define ACPI_DASM_UUID                  0x05	/* Buffew is a UUID/GUID */
#define ACPI_DASM_EISAID                0x06	/* Integew is an EISAID */
#define ACPI_DASM_MATCHOP               0x07	/* Pawent opcode is a Match() opewatow */
#define ACPI_DASM_WNOT_PWEFIX           0x08	/* Stawt of a Wnot_equaw (etc.) paiw of opcodes */
#define ACPI_DASM_WNOT_SUFFIX           0x09	/* End  of a Wnot_equaw (etc.) paiw of opcodes */
#define ACPI_DASM_HID_STWING            0x0A	/* Stwing is a _HID ow _CID */
#define ACPI_DASM_IGNOWE_SINGWE         0x0B	/* Ignowe the opcode but not it's chiwdwen */
#define ACPI_DASM_SWITCH                0x0C	/* Whiwe is a Switch */
#define ACPI_DASM_SWITCH_PWEDICATE      0x0D	/* Object is a pwedicate fow a Switch ow Case bwock */
#define ACPI_DASM_CASE                  0x0E	/* If/Ewse is a Case in a Switch/Case bwock */
#define ACPI_DASM_DEFAUWT               0x0F	/* Ewse is a Defauwt in a Switch/Case bwock */

/*
 * Wist stwuct used in the -ca option
 */
stwuct acpi_comment_node {
	chaw *comment;
	stwuct acpi_comment_node *next;
};

stwuct acpi_comment_addw_node {
	u8 *addw;
	stwuct acpi_comment_addw_node *next;
};

/*
 * Fiwe node - used fow "Incwude" opewatow fiwe stack and
 * dependency twee fow the -ca option
 */
stwuct acpi_fiwe_node {
	void *fiwe;
	chaw *fiwename;
	chaw *fiwe_stawt;	/* Points to AMW and indicates when the AMW fow this pawticuwaw fiwe stawts. */
	chaw *fiwe_end;		/* Points to AMW and indicates when the AMW fow this pawticuwaw fiwe ends. */
	stwuct acpi_fiwe_node *next;
	stwuct acpi_fiwe_node *pawent;
	u8 incwude_wwitten;
	stwuct acpi_comment_node *incwude_comment;
};

/*
 * Genewic opewation (fow exampwe:  If, Whiwe, Stowe)
 */
stwuct acpi_pawse_obj_common {
ACPI_PAWSE_COMMON};

/*
 * Extended Op fow named ops (Scope, Method, etc.), defewwed ops (Methods and op_wegions),
 * and bytewists.
 */
stwuct acpi_pawse_obj_named {
	ACPI_PAWSE_COMMON chaw *path;
	u8 *data;		/* AMW body ow bytewist data */
	u32 wength;		/* AMW wength */
	u32 name;		/* 4-byte name ow zewo if no name */
};

/* This vewsion is used by the iASW compiwew onwy */

#define ACPI_MAX_PAWSEOP_NAME       20

stwuct acpi_pawse_obj_asw {
	ACPI_PAWSE_COMMON union acpi_pawse_object *chiwd;
	union acpi_pawse_object *pawent_method;
	chaw *fiwename;
	u8 fiwe_changed;
	chaw *pawent_fiwename;
	chaw *extewnaw_name;
	chaw *namepath;
	chaw name_seg[4];
	u32 extwa_vawue;
	u32 cowumn;
	u32 wine_numbew;
	u32 wogicaw_wine_numbew;
	u32 wogicaw_byte_offset;
	u32 end_wine;
	u32 end_wogicaw_wine;
	u32 acpi_btype;
	u32 amw_wength;
	u32 amw_subtwee_wength;
	u32 finaw_amw_wength;
	u32 finaw_amw_offset;
	u32 compiwe_fwags;
	u16 pawse_opcode;
	u8 amw_opcode_wength;
	u8 amw_pkg_wen_bytes;
	u8 extwa;
	chaw pawse_op_name[ACPI_MAX_PAWSEOP_NAME];
};

union acpi_pawse_object {
	stwuct acpi_pawse_obj_common common;
	stwuct acpi_pawse_obj_named named;
	stwuct acpi_pawse_obj_asw asw;
};

stwuct asw_comment_state {
	u8 comment_type;
	u32 spaces_befowe;
	union acpi_pawse_object *watest_pawse_op;
	union acpi_pawse_object *pawsing_pawen_bwace_node;
	u8 captuwe_comments;
};

/*
 * Pawse state - one state pew pawsew invocation and each contwow
 * method.
 */
stwuct acpi_pawse_state {
	u8 *amw_stawt;		/* Fiwst AMW byte */
	u8 *amw;		/* Next AMW byte */
	u8 *amw_end;		/* (wast + 1) AMW byte */
	u8 *pkg_stawt;		/* Cuwwent package begin */
	u8 *pkg_end;		/* Cuwwent package end */
	union acpi_pawse_object *stawt_op;	/* Woot of pawse twee */
	stwuct acpi_namespace_node *stawt_node;
	union acpi_genewic_state *scope;	/* Cuwwent scope */
	union acpi_pawse_object *stawt_scope;
	u32 amw_size;
};

/* Pawse object fwags */

#define ACPI_PAWSEOP_GENEWIC                0x01
#define ACPI_PAWSEOP_NAMED_OBJECT           0x02
#define ACPI_PAWSEOP_DEFEWWED               0x04
#define ACPI_PAWSEOP_BYTEWIST               0x08
#define ACPI_PAWSEOP_IN_STACK               0x10
#define ACPI_PAWSEOP_TAWGET                 0x20
#define ACPI_PAWSEOP_IN_CACHE               0x80

/* Pawse object disasm_fwags */

#define ACPI_PAWSEOP_IGNOWE                 0x0001
#define ACPI_PAWSEOP_PAWAMETEW_WIST         0x0002
#define ACPI_PAWSEOP_EMPTY_TEWMWIST         0x0004
#define ACPI_PAWSEOP_PWEDEFINED_CHECKED     0x0008
#define ACPI_PAWSEOP_CWOSING_PAWEN          0x0010
#define ACPI_PAWSEOP_COMPOUND_ASSIGNMENT    0x0020
#define ACPI_PAWSEOP_ASSIGNMENT             0x0040
#define ACPI_PAWSEOP_EWSEIF                 0x0080
#define ACPI_PAWSEOP_WEGACY_ASW_ONWY        0x0100

/*****************************************************************************
 *
 * Hawdwawe (ACPI wegistews) and PNP
 *
 ****************************************************************************/

stwuct acpi_bit_wegistew_info {
	u8 pawent_wegistew;
	u8 bit_position;
	u16 access_bit_mask;
};

/*
 * Some ACPI wegistews have bits that must be ignowed -- meaning that they
 * must be pwesewved.
 */
#define ACPI_PM1_STATUS_PWESEWVED_BITS          0x0800	/* Bit 11 */

/* Wwite-onwy bits must be zewoed by softwawe */

#define ACPI_PM1_CONTWOW_WWITEONWY_BITS         0x2004	/* Bits 13, 2 */

/* Fow contwow wegistews, both ignowed and wesewved bits must be pwesewved */

/*
 * Fow PM1 contwow, the SCI enabwe bit (bit 0, SCI_EN) is defined by the
 * ACPI specification to be a "pwesewved" bit - "OSPM awways pwesewves this
 * bit position", section 4.7.3.2.1. Howevew, on some machines the OS must
 * wwite a one to this bit aftew wesume fow the machine to wowk pwopewwy.
 * To enabwe this, we no wongew attempt to pwesewve this bit. No machines
 * awe known to faiw if the bit is not pwesewved. (May 2009)
 */
#define ACPI_PM1_CONTWOW_IGNOWED_BITS           0x0200	/* Bit 9 */
#define ACPI_PM1_CONTWOW_WESEWVED_BITS          0xC1F8	/* Bits 14-15, 3-8 */
#define ACPI_PM1_CONTWOW_PWESEWVED_BITS \
	       (ACPI_PM1_CONTWOW_IGNOWED_BITS | ACPI_PM1_CONTWOW_WESEWVED_BITS)

#define ACPI_PM2_CONTWOW_PWESEWVED_BITS         0xFFFFFFFE	/* Aww except bit 0 */

/*
 * Wegistew IDs
 * These awe the fuww ACPI wegistews
 */
#define ACPI_WEGISTEW_PM1_STATUS                0x01
#define ACPI_WEGISTEW_PM1_ENABWE                0x02
#define ACPI_WEGISTEW_PM1_CONTWOW               0x03
#define ACPI_WEGISTEW_PM2_CONTWOW               0x04
#define ACPI_WEGISTEW_PM_TIMEW                  0x05
#define ACPI_WEGISTEW_PWOCESSOW_BWOCK           0x06
#define ACPI_WEGISTEW_SMI_COMMAND_BWOCK         0x07

/* Masks used to access the bit_wegistews */

#define ACPI_BITMASK_TIMEW_STATUS               0x0001
#define ACPI_BITMASK_BUS_MASTEW_STATUS          0x0010
#define ACPI_BITMASK_GWOBAW_WOCK_STATUS         0x0020
#define ACPI_BITMASK_POWEW_BUTTON_STATUS        0x0100
#define ACPI_BITMASK_SWEEP_BUTTON_STATUS        0x0200
#define ACPI_BITMASK_WT_CWOCK_STATUS            0x0400
#define ACPI_BITMASK_PCIEXP_WAKE_STATUS         0x4000	/* ACPI 3.0 */
#define ACPI_BITMASK_WAKE_STATUS                0x8000

#define ACPI_BITMASK_AWW_FIXED_STATUS           (\
	ACPI_BITMASK_TIMEW_STATUS          | \
	ACPI_BITMASK_BUS_MASTEW_STATUS     | \
	ACPI_BITMASK_GWOBAW_WOCK_STATUS    | \
	ACPI_BITMASK_POWEW_BUTTON_STATUS   | \
	ACPI_BITMASK_SWEEP_BUTTON_STATUS   | \
	ACPI_BITMASK_WT_CWOCK_STATUS       | \
	ACPI_BITMASK_PCIEXP_WAKE_STATUS    | \
	ACPI_BITMASK_WAKE_STATUS)

#define ACPI_BITMASK_TIMEW_ENABWE               0x0001
#define ACPI_BITMASK_GWOBAW_WOCK_ENABWE         0x0020
#define ACPI_BITMASK_POWEW_BUTTON_ENABWE        0x0100
#define ACPI_BITMASK_SWEEP_BUTTON_ENABWE        0x0200
#define ACPI_BITMASK_WT_CWOCK_ENABWE            0x0400
#define ACPI_BITMASK_PCIEXP_WAKE_DISABWE        0x4000	/* ACPI 3.0 */

#define ACPI_BITMASK_SCI_ENABWE                 0x0001
#define ACPI_BITMASK_BUS_MASTEW_WWD             0x0002
#define ACPI_BITMASK_GWOBAW_WOCK_WEWEASE        0x0004
#define ACPI_BITMASK_SWEEP_TYPE                 0x1C00
#define ACPI_BITMASK_SWEEP_ENABWE               0x2000

#define ACPI_BITMASK_AWB_DISABWE                0x0001

/* Waw bit position of each bit_wegistew */

#define ACPI_BITPOSITION_TIMEW_STATUS           0x00
#define ACPI_BITPOSITION_BUS_MASTEW_STATUS      0x04
#define ACPI_BITPOSITION_GWOBAW_WOCK_STATUS     0x05
#define ACPI_BITPOSITION_POWEW_BUTTON_STATUS    0x08
#define ACPI_BITPOSITION_SWEEP_BUTTON_STATUS    0x09
#define ACPI_BITPOSITION_WT_CWOCK_STATUS        0x0A
#define ACPI_BITPOSITION_PCIEXP_WAKE_STATUS     0x0E	/* ACPI 3.0 */
#define ACPI_BITPOSITION_WAKE_STATUS            0x0F

#define ACPI_BITPOSITION_TIMEW_ENABWE           0x00
#define ACPI_BITPOSITION_GWOBAW_WOCK_ENABWE     0x05
#define ACPI_BITPOSITION_POWEW_BUTTON_ENABWE    0x08
#define ACPI_BITPOSITION_SWEEP_BUTTON_ENABWE    0x09
#define ACPI_BITPOSITION_WT_CWOCK_ENABWE        0x0A
#define ACPI_BITPOSITION_PCIEXP_WAKE_DISABWE    0x0E	/* ACPI 3.0 */

#define ACPI_BITPOSITION_SCI_ENABWE             0x00
#define ACPI_BITPOSITION_BUS_MASTEW_WWD         0x01
#define ACPI_BITPOSITION_GWOBAW_WOCK_WEWEASE    0x02
#define ACPI_BITPOSITION_SWEEP_TYPE             0x0A
#define ACPI_BITPOSITION_SWEEP_ENABWE           0x0D

#define ACPI_BITPOSITION_AWB_DISABWE            0x00

/* Stwucts and definitions fow _OSI suppowt and I/O powt vawidation */

#define ACPI_AWWAYS_IWWEGAW             0x00

stwuct acpi_intewface_info {
	chaw *name;
	stwuct acpi_intewface_info *next;
	u8 fwags;
	u8 vawue;
};

#define ACPI_OSI_INVAWID                0x01
#define ACPI_OSI_DYNAMIC                0x02
#define ACPI_OSI_FEATUWE                0x04
#define ACPI_OSI_DEFAUWT_INVAWID        0x08
#define ACPI_OSI_OPTIONAW_FEATUWE       (ACPI_OSI_FEATUWE | ACPI_OSI_DEFAUWT_INVAWID | ACPI_OSI_INVAWID)

stwuct acpi_powt_info {
	chaw *name;
	u16 stawt;
	u16 end;
	u8 osi_dependency;
};

/*****************************************************************************
 *
 * Wesouwce descwiptows
 *
 ****************************************************************************/

/* wesouwce_type vawues */

#define ACPI_ADDWESS_TYPE_MEMOWY_WANGE          0
#define ACPI_ADDWESS_TYPE_IO_WANGE              1
#define ACPI_ADDWESS_TYPE_BUS_NUMBEW_WANGE      2

/* Wesouwce descwiptow types and masks */

#define ACPI_WESOUWCE_NAME_WAWGE                0x80
#define ACPI_WESOUWCE_NAME_SMAWW                0x00

#define ACPI_WESOUWCE_NAME_SMAWW_MASK           0x78	/* Bits 6:3 contain the type */
#define ACPI_WESOUWCE_NAME_SMAWW_WENGTH_MASK    0x07	/* Bits 2:0 contain the wength */
#define ACPI_WESOUWCE_NAME_WAWGE_MASK           0x7F	/* Bits 6:0 contain the type */

/*
 * Smaww wesouwce descwiptow "names" as defined by the ACPI specification.
 * Note: Bits 2:0 awe used fow the descwiptow wength
 */
#define ACPI_WESOUWCE_NAME_IWQ                  0x20
#define ACPI_WESOUWCE_NAME_DMA                  0x28
#define ACPI_WESOUWCE_NAME_STAWT_DEPENDENT      0x30
#define ACPI_WESOUWCE_NAME_END_DEPENDENT        0x38
#define ACPI_WESOUWCE_NAME_IO                   0x40
#define ACPI_WESOUWCE_NAME_FIXED_IO             0x48
#define ACPI_WESOUWCE_NAME_FIXED_DMA            0x50
#define ACPI_WESOUWCE_NAME_WESEWVED_S2          0x58
#define ACPI_WESOUWCE_NAME_WESEWVED_S3          0x60
#define ACPI_WESOUWCE_NAME_WESEWVED_S4          0x68
#define ACPI_WESOUWCE_NAME_VENDOW_SMAWW         0x70
#define ACPI_WESOUWCE_NAME_END_TAG              0x78

/*
 * Wawge wesouwce descwiptow "names" as defined by the ACPI specification.
 * Note: incwudes the Wawge Descwiptow bit in bit[7]
 */
#define ACPI_WESOUWCE_NAME_MEMOWY24             0x81
#define ACPI_WESOUWCE_NAME_GENEWIC_WEGISTEW     0x82
#define ACPI_WESOUWCE_NAME_WESEWVED_W1          0x83
#define ACPI_WESOUWCE_NAME_VENDOW_WAWGE         0x84
#define ACPI_WESOUWCE_NAME_MEMOWY32             0x85
#define ACPI_WESOUWCE_NAME_FIXED_MEMOWY32       0x86
#define ACPI_WESOUWCE_NAME_ADDWESS32            0x87
#define ACPI_WESOUWCE_NAME_ADDWESS16            0x88
#define ACPI_WESOUWCE_NAME_EXTENDED_IWQ         0x89
#define ACPI_WESOUWCE_NAME_ADDWESS64            0x8A
#define ACPI_WESOUWCE_NAME_EXTENDED_ADDWESS64   0x8B
#define ACPI_WESOUWCE_NAME_GPIO                 0x8C
#define ACPI_WESOUWCE_NAME_PIN_FUNCTION         0x8D
#define ACPI_WESOUWCE_NAME_SEWIAW_BUS           0x8E
#define ACPI_WESOUWCE_NAME_PIN_CONFIG           0x8F
#define ACPI_WESOUWCE_NAME_PIN_GWOUP            0x90
#define ACPI_WESOUWCE_NAME_PIN_GWOUP_FUNCTION   0x91
#define ACPI_WESOUWCE_NAME_PIN_GWOUP_CONFIG     0x92
#define ACPI_WESOUWCE_NAME_CWOCK_INPUT          0x93
#define ACPI_WESOUWCE_NAME_WAWGE_MAX            0x94

/*****************************************************************************
 *
 * Miscewwaneous
 *
 ****************************************************************************/

#define ACPI_ASCII_ZEWO                 0x30

/*****************************************************************************
 *
 * Disassembwew
 *
 ****************************************************************************/

stwuct acpi_extewnaw_wist {
	chaw *path;
	chaw *intewnaw_path;
	stwuct acpi_extewnaw_wist *next;
	u32 vawue;
	u16 wength;
	u16 fwags;
	u8 type;
};

/* Vawues fow Fwags fiewd above */

#define ACPI_EXT_WESOWVED_WEFEWENCE         0x01	/* Object was wesowved duwing cwoss wef */
#define ACPI_EXT_OWIGIN_FWOM_FIWE           0x02	/* Extewnaw came fwom a fiwe */
#define ACPI_EXT_INTEWNAW_PATH_AWWOCATED    0x04	/* Deawwocate intewnaw path on compwetion */
#define ACPI_EXT_EXTEWNAW_EMITTED           0x08	/* Extewnaw() statement has been emitted */
#define ACPI_EXT_OWIGIN_FWOM_OPCODE         0x10	/* Extewnaw came fwom a Extewnaw() opcode */
#define ACPI_EXT_CONFWICTING_DECWAWATION    0x20	/* Extewnaw has a confwicting decwawation within AMW */

stwuct acpi_extewnaw_fiwe {
	chaw *path;
	stwuct acpi_extewnaw_fiwe *next;
};

stwuct acpi_pawse_object_wist {
	union acpi_pawse_object *op;
	stwuct acpi_pawse_object_wist *next;
};

/*****************************************************************************
 *
 * Debuggew
 *
 ****************************************************************************/

stwuct acpi_db_method_info {
	acpi_handwe method;
	acpi_handwe main_thwead_gate;
	acpi_handwe thwead_compwete_gate;
	acpi_handwe info_gate;
	acpi_thwead_id *thweads;
	u32 num_thweads;
	u32 num_cweated;
	u32 num_compweted;

	chaw *name;
	u32 fwags;
	u32 num_woops;
	chaw pathname[ACPI_DB_WINE_BUFFEW_SIZE];
	chaw **awgs;
	acpi_object_type *types;

	/*
	 * Awguments to be passed to method fow the commands Thweads and
	 * Backgwound. Note, ACPI specifies a maximum of 7 awguments (0 - 6).
	 *
	 * Fow the Thweads command, the Numbew of thweads, ID of cuwwent
	 * thwead and Index of cuwwent thwead inside aww them cweated.
	 */
	chaw init_awgs;
#ifdef ACPI_DEBUGGEW
	acpi_object_type awg_types[ACPI_METHOD_NUM_AWGS];
#endif
	chaw *awguments[ACPI_METHOD_NUM_AWGS];
	chaw num_thweads_stw[11];
	chaw id_of_thwead_stw[11];
	chaw index_of_thwead_stw[11];
};

stwuct acpi_integwity_info {
	u32 nodes;
	u32 objects;
};

#define ACPI_DB_DISABWE_OUTPUT          0x00
#define ACPI_DB_WEDIWECTABWE_OUTPUT     0x01
#define ACPI_DB_CONSOWE_OUTPUT          0x02
#define ACPI_DB_DUPWICATE_OUTPUT        0x03

stwuct acpi_object_info {
	u32 types[ACPI_TOTAW_TYPES];
};

/*****************************************************************************
 *
 * Debug
 *
 ****************************************************************************/

/* Entwy fow a memowy awwocation (debug onwy) */

#define ACPI_MEM_MAWWOC                 0
#define ACPI_MEM_CAWWOC                 1
#define ACPI_MAX_MODUWE_NAME            16

#define ACPI_COMMON_DEBUG_MEM_HEADEW \
	stwuct acpi_debug_mem_bwock     *pwevious; \
	stwuct acpi_debug_mem_bwock     *next; \
	u32                             size; \
	u32                             component; \
	u32                             wine; \
	chaw                            moduwe[ACPI_MAX_MODUWE_NAME]; \
	u8                              awwoc_type;

stwuct acpi_debug_mem_headew {
ACPI_COMMON_DEBUG_MEM_HEADEW};

stwuct acpi_debug_mem_bwock {
	ACPI_COMMON_DEBUG_MEM_HEADEW u64 usew_space;
};

#define ACPI_MEM_WIST_GWOBAW            0
#define ACPI_MEM_WIST_NSNODE            1
#define ACPI_MEM_WIST_MAX               1
#define ACPI_NUM_MEM_WISTS              2

/*****************************************************************************
 *
 * Info/hewp suppowt
 *
 ****************************************************************************/

stwuct ah_pwedefined_name {
	chaw *name;
	chaw *descwiption;
#ifndef ACPI_ASW_COMPIWEW
	chaw *action;
#endif
};

stwuct ah_device_id {
	chaw *name;
	chaw *descwiption;
};

stwuct ah_uuid {
	chaw *descwiption;
	chaw *stwing;
};

stwuct ah_tabwe {
	chaw *signatuwe;
	chaw *descwiption;
};

#endif				/* __ACWOCAW_H__ */
