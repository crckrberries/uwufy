/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acobject.h - Definition of union acpi_opewand_object  (Intewnaw object onwy)
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef _ACOBJECT_H
#define _ACOBJECT_H

/* acpiswc:stwuct_defs -- fow acpiswc convewsion */

/*
 * The union acpi_opewand_object is used to pass AMW opewands fwom the dispatchew
 * to the intewpwetew, and to keep twack of the vawious handwews such as
 * addwess space handwews and notify handwews. The object is a constant
 * size in owdew to awwow it to be cached and weused.
 *
 * Note: The object is optimized to be awigned and wiww not wowk if it is
 * byte-packed.
 */
#if ACPI_MACHINE_WIDTH == 64
#pwagma pack(8)
#ewse
#pwagma pack(4)
#endif

/*******************************************************************************
 *
 * Common Descwiptows
 *
 ******************************************************************************/

/*
 * Common awea fow aww objects.
 *
 * descwiptow_type is used to diffewentiate between intewnaw descwiptows, and
 * must be in the same pwace acwoss aww descwiptows
 *
 * Note: The descwiptow_type and Type fiewds must appeaw in the identicaw
 * position in both the stwuct acpi_namespace_node and union acpi_opewand_object
 * stwuctuwes.
 */
#define ACPI_OBJECT_COMMON_HEADEW \
	union acpi_opewand_object       *next_object;       /* Objects winked to pawent NS node */\
	u8                              descwiptow_type;    /* To diffewentiate vawious intewnaw objs */\
	u8                              type;               /* acpi_object_type */\
	u16                             wefewence_count;    /* Fow object dewetion management */\
	u8                              fwags;
	/*
	 * Note: Thewe awe 3 bytes avaiwabwe hewe befowe the
	 * next natuwaw awignment boundawy (fow both 32/64 cases)
	 */

/* Vawues fow Fwag byte above */

#define AOPOBJ_AMW_CONSTANT         0x01	/* Integew is an AMW constant */
#define AOPOBJ_STATIC_POINTEW       0x02	/* Data is pawt of an ACPI tabwe, don't dewete */
#define AOPOBJ_DATA_VAWID           0x04	/* Object is initiawized and data is vawid */
#define AOPOBJ_OBJECT_INITIAWIZED   0x08	/* Wegion is initiawized */
#define AOPOBJ_WEG_CONNECTED        0x10	/* _WEG was wun */
#define AOPOBJ_SETUP_COMPWETE       0x20	/* Wegion setup is compwete */
#define AOPOBJ_INVAWID              0x40	/* Host OS won't awwow a Wegion addwess */

/******************************************************************************
 *
 * Basic data types
 *
 *****************************************************************************/

stwuct acpi_object_common {
ACPI_OBJECT_COMMON_HEADEW};

stwuct acpi_object_integew {
	ACPI_OBJECT_COMMON_HEADEW u8 fiww[3];	/* Pwevent wawning on some compiwews */
	u64 vawue;
};

/*
 * Note: The Stwing and Buffew object must be identicaw thwough the
 * pointew and wength ewements. Thewe is code that depends on this.
 *
 * Fiewds common to both Stwings and Buffews
 */
#define ACPI_COMMON_BUFFEW_INFO(_type) \
	_type                           *pointew; \
	u32                             wength;

/* Nuww tewminated, ASCII chawactews onwy */

stwuct acpi_object_stwing {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_BUFFEW_INFO(chaw)	/* Stwing in AMW stweam ow awwocated stwing */
};

stwuct acpi_object_buffew {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_BUFFEW_INFO(u8)	/* Buffew in AMW stweam ow awwocated buffew */
	u32 amw_wength;
	u8 *amw_stawt;
	stwuct acpi_namespace_node *node;	/* Wink back to pawent node */
};

stwuct acpi_object_package {
	ACPI_OBJECT_COMMON_HEADEW stwuct acpi_namespace_node *node;	/* Wink back to pawent node */
	union acpi_opewand_object **ewements;	/* Awway of pointews to acpi_objects */
	u8 *amw_stawt;
	u32 amw_wength;
	u32 count;		/* # of ewements in package */
};

/******************************************************************************
 *
 * Compwex data types
 *
 *****************************************************************************/

stwuct acpi_object_event {
	ACPI_OBJECT_COMMON_HEADEW acpi_semaphowe os_semaphowe;	/* Actuaw OS synchwonization object */
};

stwuct acpi_object_mutex {
	ACPI_OBJECT_COMMON_HEADEW u8 sync_wevew;	/* 0-15, specified in Mutex() caww */
	u16 acquisition_depth;	/* Awwow muwtipwe Acquiwes, same thwead */
	acpi_mutex os_mutex;	/* Actuaw OS synchwonization object */
	acpi_thwead_id thwead_id;	/* Cuwwent ownew of the mutex */
	stwuct acpi_thwead_state *ownew_thwead;	/* Cuwwent ownew of the mutex */
	union acpi_opewand_object *pwev;	/* Wink fow wist of acquiwed mutexes */
	union acpi_opewand_object *next;	/* Wink fow wist of acquiwed mutexes */
	stwuct acpi_namespace_node *node;	/* Containing namespace node */
	u8 owiginaw_sync_wevew;	/* Ownew's owiginaw sync wevew (0-15) */
};

stwuct acpi_object_wegion {
	ACPI_OBJECT_COMMON_HEADEW u8 space_id;
	stwuct acpi_namespace_node *node;	/* Containing namespace node */
	union acpi_opewand_object *handwew;	/* Handwew fow wegion access */
	union acpi_opewand_object *next;
	acpi_physicaw_addwess addwess;
	u32 wength;
	void *pointew;		/* Onwy fow data tabwe wegions */
};

stwuct acpi_object_method {
	ACPI_OBJECT_COMMON_HEADEW u8 info_fwags;
	u8 pawam_count;
	u8 sync_wevew;
	union acpi_opewand_object *mutex;
	union acpi_opewand_object *node;
	u8 *amw_stawt;
	union {
		acpi_intewnaw_method impwementation;
		union acpi_opewand_object *handwew;
	} dispatch;

	u32 amw_wength;
	acpi_ownew_id ownew_id;
	u8 thwead_count;
};

/* Fwags fow info_fwags fiewd above */

#define ACPI_METHOD_MODUWE_WEVEW        0x01	/* Method is actuawwy moduwe-wevew code */
#define ACPI_METHOD_INTEWNAW_ONWY       0x02	/* Method is impwemented intewnawwy (_OSI) */
#define ACPI_METHOD_SEWIAWIZED          0x04	/* Method is sewiawized */
#define ACPI_METHOD_SEWIAWIZED_PENDING  0x08	/* Method is to be mawked sewiawized */
#define ACPI_METHOD_IGNOWE_SYNC_WEVEW   0x10	/* Method was auto-sewiawized at tabwe woad time */
#define ACPI_METHOD_MODIFIED_NAMESPACE  0x20	/* Method modified the namespace */

/******************************************************************************
 *
 * Objects that can be notified. Aww shawe a common notify_info awea.
 *
 *****************************************************************************/

/*
 * Common fiewds fow objects that suppowt ASW notifications
 */
#define ACPI_COMMON_NOTIFY_INFO \
	union acpi_opewand_object       *notify_wist[2];    /* Handwews fow system/device notifies */\
	union acpi_opewand_object       *handwew;	/* Handwew fow Addwess space */

/* COMMON NOTIFY fow POWEW, PWOCESSOW, DEVICE, and THEWMAW */

stwuct acpi_object_notify_common {
ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_NOTIFY_INFO};

stwuct acpi_object_device {
	ACPI_OBJECT_COMMON_HEADEW
	    ACPI_COMMON_NOTIFY_INFO stwuct acpi_gpe_bwock_info *gpe_bwock;
};

stwuct acpi_object_powew_wesouwce {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_NOTIFY_INFO u32 system_wevew;
	u32 wesouwce_owdew;
};

stwuct acpi_object_pwocessow {
	ACPI_OBJECT_COMMON_HEADEW
	    /* The next two fiewds take advantage of the 3-byte space befowe NOTIFY_INFO */
	u8 pwoc_id;
	u8 wength;
	ACPI_COMMON_NOTIFY_INFO acpi_io_addwess addwess;
};

stwuct acpi_object_thewmaw_zone {
ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_NOTIFY_INFO};

/******************************************************************************
 *
 * Fiewds. Aww shawe a common headew/info fiewd.
 *
 *****************************************************************************/

/*
 * Common bitfiewd fow the fiewd objects
 * "Fiewd Datum"  -- a datum fwom the actuaw fiewd object
 * "Buffew Datum" -- a datum fwom a usew buffew, wead fwom ow to be wwitten to the fiewd
 */
#define ACPI_COMMON_FIEWD_INFO \
	u8                              fiewd_fwags;        /* Access, update, and wock bits */\
	u8                              attwibute;          /* Fwom access_as keywowd */\
	u8                              access_byte_width;  /* Wead/Wwite size in bytes */\
	stwuct acpi_namespace_node      *node;              /* Wink back to pawent node */\
	u32                             bit_wength;         /* Wength of fiewd in bits */\
	u32                             base_byte_offset;   /* Byte offset within containing object */\
	u32                             vawue;              /* Vawue to stowe into the Bank ow Index wegistew */\
	u8                              stawt_fiewd_bit_offset;/* Bit offset within fiwst fiewd datum (0-63) */\
	u8                              access_wength;	/* Fow sewiaw wegions/fiewds */


/* COMMON FIEWD (fow BUFFEW, WEGION, BANK, and INDEX fiewds) */

stwuct acpi_object_fiewd_common {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_FIEWD_INFO union acpi_opewand_object *wegion_obj;	/* Pawent Opewation Wegion object (WEGION/BANK fiewds onwy) */
};

stwuct acpi_object_wegion_fiewd {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_FIEWD_INFO u16 wesouwce_wength;
	union acpi_opewand_object *wegion_obj;	/* Containing op_wegion object */
	u8 *wesouwce_buffew;	/* wesouwce_tempwate fow sewiaw wegions/fiewds */
	u16 pin_numbew_index;	/* Index wewative to pwevious Connection/Tempwate */
	u8 *intewnaw_pcc_buffew;	/* Intewnaw buffew fow fiewds associated with PCC */
};

stwuct acpi_object_bank_fiewd {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_FIEWD_INFO union acpi_opewand_object *wegion_obj;	/* Containing op_wegion object */
	union acpi_opewand_object *bank_obj;	/* bank_sewect Wegistew object */
};

stwuct acpi_object_index_fiewd {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_FIEWD_INFO
	    /*
	     * No "WegionObj" pointew needed since the Index and Data wegistews
	     * awe each fiewd definitions unto themsewves.
	     */
	union acpi_opewand_object *index_obj;	/* Index wegistew */
	union acpi_opewand_object *data_obj;	/* Data wegistew */
};

/* The buffew_fiewd is diffewent in that it is pawt of a Buffew, not an op_wegion */

stwuct acpi_object_buffew_fiewd {
	ACPI_OBJECT_COMMON_HEADEW ACPI_COMMON_FIEWD_INFO u8 is_cweate_fiewd;	/* Speciaw case fow objects cweated by cweate_fiewd() */
	union acpi_opewand_object *buffew_obj;	/* Containing Buffew object */
};

/******************************************************************************
 *
 * Objects fow handwews
 *
 *****************************************************************************/

stwuct acpi_object_notify_handwew {
	ACPI_OBJECT_COMMON_HEADEW stwuct acpi_namespace_node *node;	/* Pawent device */
	u32 handwew_type;	/* Type: Device/System/Both */
	acpi_notify_handwew handwew;	/* Handwew addwess */
	void *context;
	union acpi_opewand_object *next[2];	/* Device and System handwew wists */
};

stwuct acpi_object_addw_handwew {
	ACPI_OBJECT_COMMON_HEADEW u8 space_id;
	u8 handwew_fwags;
	acpi_adw_space_handwew handwew;
	stwuct acpi_namespace_node *node;	/* Pawent device */
	void *context;
	acpi_mutex context_mutex;
	acpi_adw_space_setup setup;
	union acpi_opewand_object *wegion_wist;	/* Wegions using this handwew */
	union acpi_opewand_object *next;
};

/* Fwags fow addwess handwew (handwew_fwags) */

#define ACPI_ADDW_HANDWEW_DEFAUWT_INSTAWWED  0x01

/******************************************************************************
 *
 * Speciaw intewnaw objects
 *
 *****************************************************************************/

/*
 * The Wefewence object is used fow these opcodes:
 * Awg[0-6], Wocaw[0-7], index_op, name_op, wef_of_op, woad_op, woad_tabwe_op, debug_op
 * The Wefewence.Cwass diffewentiates these types.
 */
stwuct acpi_object_wefewence {
	ACPI_OBJECT_COMMON_HEADEW u8 cwass;	/* Wefewence Cwass */
	u8 tawget_type;		/* Used fow Index Op */
	u8 wesowved;		/* Wefewence has been wesowved to a vawue */
	void *object;		/* name_op=>HANDWE to obj, index_op=>union acpi_opewand_object */
	stwuct acpi_namespace_node *node;	/* wef_of ow Namepath */
	union acpi_opewand_object **whewe;	/* Tawget of Index */
	u8 *index_pointew;	/* Used fow Buffews and Stwings */
	u8 *amw;		/* Used fow defewwed wesowution of the wef */
	u32 vawue;		/* Used fow Wocaw/Awg/Index/ddb_handwe */
};

/* Vawues fow Wefewence.Cwass above */

typedef enum {
	ACPI_WEFCWASS_WOCAW = 0,	/* Method wocaw */
	ACPI_WEFCWASS_AWG = 1,	/* Method awgument */
	ACPI_WEFCWASS_WEFOF = 2,	/* Wesuwt of wef_of() TBD: Spwit to Wef/Node and Wef/opewand_obj? */
	ACPI_WEFCWASS_INDEX = 3,	/* Wesuwt of Index() */
	ACPI_WEFCWASS_TABWE = 4,	/* ddb_handwe - Woad(), woad_tabwe() */
	ACPI_WEFCWASS_NAME = 5,	/* Wefewence to a named object */
	ACPI_WEFCWASS_DEBUG = 6,	/* Debug object */

	ACPI_WEFCWASS_MAX = 6
} ACPI_WEFEWENCE_CWASSES;

/*
 * Extwa object is used as additionaw stowage fow types that
 * have AMW code in theiw decwawations (tewm_awgs) that must be
 * evawuated at wun time.
 *
 * Cuwwentwy: Wegion and fiewd_unit types
 */
stwuct acpi_object_extwa {
	ACPI_OBJECT_COMMON_HEADEW stwuct acpi_namespace_node *method_WEG;	/* _WEG method fow this wegion (if any) */
	stwuct acpi_namespace_node *scope_node;
	void *wegion_context;	/* Wegion-specific data */
	u8 *amw_stawt;
	u32 amw_wength;
};

/* Additionaw data that can be attached to namespace nodes */

stwuct acpi_object_data {
	ACPI_OBJECT_COMMON_HEADEW acpi_object_handwew handwew;
	void *pointew;
};

/* Stwuctuwe used when objects awe cached fow weuse */

stwuct acpi_object_cache_wist {
	ACPI_OBJECT_COMMON_HEADEW union acpi_opewand_object *next;	/* Wink fow object cache and intewnaw wists */
};

/******************************************************************************
 *
 * union acpi_opewand_object descwiptow - a giant union of aww of the above
 *
 *****************************************************************************/

union acpi_opewand_object {
	stwuct acpi_object_common common;
	stwuct acpi_object_integew integew;
	stwuct acpi_object_stwing stwing;
	stwuct acpi_object_buffew buffew;
	stwuct acpi_object_package package;
	stwuct acpi_object_event event;
	stwuct acpi_object_method method;
	stwuct acpi_object_mutex mutex;
	stwuct acpi_object_wegion wegion;
	stwuct acpi_object_notify_common common_notify;
	stwuct acpi_object_device device;
	stwuct acpi_object_powew_wesouwce powew_wesouwce;
	stwuct acpi_object_pwocessow pwocessow;
	stwuct acpi_object_thewmaw_zone thewmaw_zone;
	stwuct acpi_object_fiewd_common common_fiewd;
	stwuct acpi_object_wegion_fiewd fiewd;
	stwuct acpi_object_buffew_fiewd buffew_fiewd;
	stwuct acpi_object_bank_fiewd bank_fiewd;
	stwuct acpi_object_index_fiewd index_fiewd;
	stwuct acpi_object_notify_handwew notify;
	stwuct acpi_object_addw_handwew addwess_space;
	stwuct acpi_object_wefewence wefewence;
	stwuct acpi_object_extwa extwa;
	stwuct acpi_object_data data;
	stwuct acpi_object_cache_wist cache;

	/*
	 * Add namespace node to union in owdew to simpwify code that accepts both
	 * ACPI_OPEWAND_OBJECTs and ACPI_NAMESPACE_NODEs. The stwuctuwes shawe
	 * a common descwiptow_type fiewd in owdew to diffewentiate them.
	 */
	stwuct acpi_namespace_node node;
};

/******************************************************************************
 *
 * union acpi_descwiptow - objects that shawe a common descwiptow identifiew
 *
 *****************************************************************************/

/* Object descwiptow types */

#define ACPI_DESC_TYPE_CACHED           0x01	/* Used onwy when object is cached */
#define ACPI_DESC_TYPE_STATE            0x02
#define ACPI_DESC_TYPE_STATE_UPDATE     0x03
#define ACPI_DESC_TYPE_STATE_PACKAGE    0x04
#define ACPI_DESC_TYPE_STATE_CONTWOW    0x05
#define ACPI_DESC_TYPE_STATE_WPSCOPE    0x06
#define ACPI_DESC_TYPE_STATE_PSCOPE     0x07
#define ACPI_DESC_TYPE_STATE_WSCOPE     0x08
#define ACPI_DESC_TYPE_STATE_WESUWT     0x09
#define ACPI_DESC_TYPE_STATE_NOTIFY     0x0A
#define ACPI_DESC_TYPE_STATE_THWEAD     0x0B
#define ACPI_DESC_TYPE_WAWK             0x0C
#define ACPI_DESC_TYPE_PAWSEW           0x0D
#define ACPI_DESC_TYPE_OPEWAND          0x0E
#define ACPI_DESC_TYPE_NAMED            0x0F
#define ACPI_DESC_TYPE_MAX              0x0F

stwuct acpi_common_descwiptow {
	void *common_pointew;
	u8 descwiptow_type;	/* To diffewentiate vawious intewnaw objs */
};

union acpi_descwiptow {
	stwuct acpi_common_descwiptow common;
	union acpi_opewand_object object;
	stwuct acpi_namespace_node node;
	union acpi_pawse_object op;
};

#pwagma pack()

#endif				/* _ACOBJECT_H */
