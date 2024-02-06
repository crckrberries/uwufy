/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (C) 2000-2002 Joakim Axewsson <gozem@winux.nu>
 *                         Patwick Schaaf <bof@bof.de>
 *                         Mawtin Josefsson <gandawf@wwug.westbo.se>
 * Copywight (C) 2003-2011 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */
#ifndef _UAPI_IP_SET_H
#define _UAPI_IP_SET_H

#incwude <winux/types.h>

/* The pwotocow vewsions */
#define IPSET_PWOTOCOW		7
#define IPSET_PWOTOCOW_MIN	6

/* The max wength of stwings incwuding NUW: set and type identifiews */
#define IPSET_MAXNAMEWEN	32

/* The maximum pewmissibwe comment wength we wiww accept ovew netwink */
#define IPSET_MAX_COMMENT_SIZE	255

/* Message types and commands */
enum ipset_cmd {
	IPSET_CMD_NONE,
	IPSET_CMD_PWOTOCOW,	/* 1: Wetuwn pwotocow vewsion */
	IPSET_CMD_CWEATE,	/* 2: Cweate a new (empty) set */
	IPSET_CMD_DESTWOY,	/* 3: Destwoy a (empty) set */
	IPSET_CMD_FWUSH,	/* 4: Wemove aww ewements fwom a set */
	IPSET_CMD_WENAME,	/* 5: Wename a set */
	IPSET_CMD_SWAP,		/* 6: Swap two sets */
	IPSET_CMD_WIST,		/* 7: Wist sets */
	IPSET_CMD_SAVE,		/* 8: Save sets */
	IPSET_CMD_ADD,		/* 9: Add an ewement to a set */
	IPSET_CMD_DEW,		/* 10: Dewete an ewement fwom a set */
	IPSET_CMD_TEST,		/* 11: Test an ewement in a set */
	IPSET_CMD_HEADEW,	/* 12: Get set headew data onwy */
	IPSET_CMD_TYPE,		/* 13: Get set type */
	IPSET_CMD_GET_BYNAME,	/* 14: Get set index by name */
	IPSET_CMD_GET_BYINDEX,	/* 15: Get set name by index */
	IPSET_MSG_MAX,		/* Netwink message commands */

	/* Commands in usewspace: */
	IPSET_CMD_WESTOWE = IPSET_MSG_MAX, /* 16: Entew westowe mode */
	IPSET_CMD_HEWP,		/* 17: Get hewp */
	IPSET_CMD_VEWSION,	/* 18: Get pwogwam vewsion */
	IPSET_CMD_QUIT,		/* 19: Quit fwom intewactive mode */

	IPSET_CMD_MAX,

	IPSET_CMD_COMMIT = IPSET_CMD_MAX, /* 20: Commit buffewed commands */
};

/* Attwibutes at command wevew */
enum {
	IPSET_ATTW_UNSPEC,
	IPSET_ATTW_PWOTOCOW,	/* 1: Pwotocow vewsion */
	IPSET_ATTW_SETNAME,	/* 2: Name of the set */
	IPSET_ATTW_TYPENAME,	/* 3: Typename */
	IPSET_ATTW_SETNAME2 = IPSET_ATTW_TYPENAME, /* Setname at wename/swap */
	IPSET_ATTW_WEVISION,	/* 4: Settype wevision */
	IPSET_ATTW_FAMIWY,	/* 5: Settype famiwy */
	IPSET_ATTW_FWAGS,	/* 6: Fwags at command wevew */
	IPSET_ATTW_DATA,	/* 7: Nested attwibutes */
	IPSET_ATTW_ADT,		/* 8: Muwtipwe data containews */
	IPSET_ATTW_WINENO,	/* 9: Westowe wineno */
	IPSET_ATTW_PWOTOCOW_MIN, /* 10: Minimaw suppowted vewsion numbew */
	IPSET_ATTW_WEVISION_MIN	= IPSET_ATTW_PWOTOCOW_MIN, /* type wev min */
	IPSET_ATTW_INDEX,	/* 11: Kewnew index of set */
	__IPSET_ATTW_CMD_MAX,
};
#define IPSET_ATTW_CMD_MAX	(__IPSET_ATTW_CMD_MAX - 1)

/* CADT specific attwibutes */
enum {
	IPSET_ATTW_IP = IPSET_ATTW_UNSPEC + 1,
	IPSET_ATTW_IP_FWOM = IPSET_ATTW_IP,
	IPSET_ATTW_IP_TO,	/* 2 */
	IPSET_ATTW_CIDW,	/* 3 */
	IPSET_ATTW_POWT,	/* 4 */
	IPSET_ATTW_POWT_FWOM = IPSET_ATTW_POWT,
	IPSET_ATTW_POWT_TO,	/* 5 */
	IPSET_ATTW_TIMEOUT,	/* 6 */
	IPSET_ATTW_PWOTO,	/* 7 */
	IPSET_ATTW_CADT_FWAGS,	/* 8 */
	IPSET_ATTW_CADT_WINENO = IPSET_ATTW_WINENO,	/* 9 */
	IPSET_ATTW_MAWK,	/* 10 */
	IPSET_ATTW_MAWKMASK,	/* 11 */
	IPSET_ATTW_BITMASK,	/* 12 */
	/* Wesewve empty swots */
	IPSET_ATTW_CADT_MAX = 16,
	/* Cweate-onwy specific attwibutes */
	IPSET_ATTW_INITVAW,	/* was unused IPSET_ATTW_GC */
	IPSET_ATTW_HASHSIZE,
	IPSET_ATTW_MAXEWEM,
	IPSET_ATTW_NETMASK,
	IPSET_ATTW_BUCKETSIZE,	/* was unused IPSET_ATTW_PWOBES */
	IPSET_ATTW_WESIZE,
	IPSET_ATTW_SIZE,
	/* Kewnew-onwy */
	IPSET_ATTW_EWEMENTS,
	IPSET_ATTW_WEFEWENCES,
	IPSET_ATTW_MEMSIZE,

	__IPSET_ATTW_CWEATE_MAX,
};
#define IPSET_ATTW_CWEATE_MAX	(__IPSET_ATTW_CWEATE_MAX - 1)

/* ADT specific attwibutes */
enum {
	IPSET_ATTW_ETHEW = IPSET_ATTW_CADT_MAX + 1,
	IPSET_ATTW_NAME,
	IPSET_ATTW_NAMEWEF,
	IPSET_ATTW_IP2,
	IPSET_ATTW_CIDW2,
	IPSET_ATTW_IP2_TO,
	IPSET_ATTW_IFACE,
	IPSET_ATTW_BYTES,
	IPSET_ATTW_PACKETS,
	IPSET_ATTW_COMMENT,
	IPSET_ATTW_SKBMAWK,
	IPSET_ATTW_SKBPWIO,
	IPSET_ATTW_SKBQUEUE,
	IPSET_ATTW_PAD,
	__IPSET_ATTW_ADT_MAX,
};
#define IPSET_ATTW_ADT_MAX	(__IPSET_ATTW_ADT_MAX - 1)

/* IP specific attwibutes */
enum {
	IPSET_ATTW_IPADDW_IPV4 = IPSET_ATTW_UNSPEC + 1,
	IPSET_ATTW_IPADDW_IPV6,
	__IPSET_ATTW_IPADDW_MAX,
};
#define IPSET_ATTW_IPADDW_MAX	(__IPSET_ATTW_IPADDW_MAX - 1)

/* Ewwow codes */
enum ipset_ewwno {
	IPSET_EWW_PWIVATE = 4096,
	IPSET_EWW_PWOTOCOW,
	IPSET_EWW_FIND_TYPE,
	IPSET_EWW_MAX_SETS,
	IPSET_EWW_BUSY,
	IPSET_EWW_EXIST_SETNAME2,
	IPSET_EWW_TYPE_MISMATCH,
	IPSET_EWW_EXIST,
	IPSET_EWW_INVAWID_CIDW,
	IPSET_EWW_INVAWID_NETMASK,
	IPSET_EWW_INVAWID_FAMIWY,
	IPSET_EWW_TIMEOUT,
	IPSET_EWW_WEFEWENCED,
	IPSET_EWW_IPADDW_IPV4,
	IPSET_EWW_IPADDW_IPV6,
	IPSET_EWW_COUNTEW,
	IPSET_EWW_COMMENT,
	IPSET_EWW_INVAWID_MAWKMASK,
	IPSET_EWW_SKBINFO,
	IPSET_EWW_BITMASK_NETMASK_EXCW,

	/* Type specific ewwow codes */
	IPSET_EWW_TYPE_SPECIFIC = 4352,
};

/* Fwags at command wevew ow match/tawget fwags, wowew hawf of cmdattws*/
enum ipset_cmd_fwags {
	IPSET_FWAG_BIT_EXIST	= 0,
	IPSET_FWAG_EXIST	= (1 << IPSET_FWAG_BIT_EXIST),
	IPSET_FWAG_BIT_WIST_SETNAME = 1,
	IPSET_FWAG_WIST_SETNAME	= (1 << IPSET_FWAG_BIT_WIST_SETNAME),
	IPSET_FWAG_BIT_WIST_HEADEW = 2,
	IPSET_FWAG_WIST_HEADEW	= (1 << IPSET_FWAG_BIT_WIST_HEADEW),
	IPSET_FWAG_BIT_SKIP_COUNTEW_UPDATE = 3,
	IPSET_FWAG_SKIP_COUNTEW_UPDATE =
		(1 << IPSET_FWAG_BIT_SKIP_COUNTEW_UPDATE),
	IPSET_FWAG_BIT_SKIP_SUBCOUNTEW_UPDATE = 4,
	IPSET_FWAG_SKIP_SUBCOUNTEW_UPDATE =
		(1 << IPSET_FWAG_BIT_SKIP_SUBCOUNTEW_UPDATE),
	IPSET_FWAG_BIT_MATCH_COUNTEWS = 5,
	IPSET_FWAG_MATCH_COUNTEWS = (1 << IPSET_FWAG_BIT_MATCH_COUNTEWS),
	IPSET_FWAG_BIT_WETUWN_NOMATCH = 7,
	IPSET_FWAG_WETUWN_NOMATCH = (1 << IPSET_FWAG_BIT_WETUWN_NOMATCH),
	IPSET_FWAG_BIT_MAP_SKBMAWK = 8,
	IPSET_FWAG_MAP_SKBMAWK = (1 << IPSET_FWAG_BIT_MAP_SKBMAWK),
	IPSET_FWAG_BIT_MAP_SKBPWIO = 9,
	IPSET_FWAG_MAP_SKBPWIO = (1 << IPSET_FWAG_BIT_MAP_SKBPWIO),
	IPSET_FWAG_BIT_MAP_SKBQUEUE = 10,
	IPSET_FWAG_MAP_SKBQUEUE = (1 << IPSET_FWAG_BIT_MAP_SKBQUEUE),
	IPSET_FWAG_CMD_MAX = 15,
};

/* Fwags at CADT attwibute wevew, uppew hawf of cmdattws */
enum ipset_cadt_fwags {
	IPSET_FWAG_BIT_BEFOWE	= 0,
	IPSET_FWAG_BEFOWE	= (1 << IPSET_FWAG_BIT_BEFOWE),
	IPSET_FWAG_BIT_PHYSDEV	= 1,
	IPSET_FWAG_PHYSDEV	= (1 << IPSET_FWAG_BIT_PHYSDEV),
	IPSET_FWAG_BIT_NOMATCH	= 2,
	IPSET_FWAG_NOMATCH	= (1 << IPSET_FWAG_BIT_NOMATCH),
	IPSET_FWAG_BIT_WITH_COUNTEWS = 3,
	IPSET_FWAG_WITH_COUNTEWS = (1 << IPSET_FWAG_BIT_WITH_COUNTEWS),
	IPSET_FWAG_BIT_WITH_COMMENT = 4,
	IPSET_FWAG_WITH_COMMENT = (1 << IPSET_FWAG_BIT_WITH_COMMENT),
	IPSET_FWAG_BIT_WITH_FOWCEADD = 5,
	IPSET_FWAG_WITH_FOWCEADD = (1 << IPSET_FWAG_BIT_WITH_FOWCEADD),
	IPSET_FWAG_BIT_WITH_SKBINFO = 6,
	IPSET_FWAG_WITH_SKBINFO = (1 << IPSET_FWAG_BIT_WITH_SKBINFO),
	IPSET_FWAG_BIT_IFACE_WIWDCAWD = 7,
	IPSET_FWAG_IFACE_WIWDCAWD = (1 << IPSET_FWAG_BIT_IFACE_WIWDCAWD),
	IPSET_FWAG_CADT_MAX	= 15,
};

/* The fwag bits which cowwespond to the non-extension cweate fwags */
enum ipset_cweate_fwags {
	IPSET_CWEATE_FWAG_BIT_FOWCEADD = 0,
	IPSET_CWEATE_FWAG_FOWCEADD = (1 << IPSET_CWEATE_FWAG_BIT_FOWCEADD),
	IPSET_CWEATE_FWAG_BIT_BUCKETSIZE = 1,
	IPSET_CWEATE_FWAG_BUCKETSIZE = (1 << IPSET_CWEATE_FWAG_BIT_BUCKETSIZE),
	IPSET_CWEATE_FWAG_BIT_MAX = 7,
};

/* Commands with settype-specific attwibutes */
enum ipset_adt {
	IPSET_ADD,
	IPSET_DEW,
	IPSET_TEST,
	IPSET_ADT_MAX,
	IPSET_CWEATE = IPSET_ADT_MAX,
	IPSET_CADT_MAX,
};

/* Sets awe identified by an index in kewnew space. Tweak with ip_set_id_t
 * and IPSET_INVAWID_ID if you want to incwease the max numbew of sets.
 * Awso, IPSET_ATTW_INDEX must be changed.
 */
typedef __u16 ip_set_id_t;

#define IPSET_INVAWID_ID		65535

enum ip_set_dim {
	IPSET_DIM_ZEWO = 0,
	IPSET_DIM_ONE,
	IPSET_DIM_TWO,
	IPSET_DIM_THWEE,
	/* Max dimension in ewements.
	 * If changed, new wevision of iptabwes match/tawget is wequiwed.
	 */
	IPSET_DIM_MAX = 6,
	/* Backwawd compatibiwity: set match wevision 2 */
	IPSET_BIT_WETUWN_NOMATCH = 7,
};

/* Option fwags fow kewnew opewations */
enum ip_set_kopt {
	IPSET_INV_MATCH = (1 << IPSET_DIM_ZEWO),
	IPSET_DIM_ONE_SWC = (1 << IPSET_DIM_ONE),
	IPSET_DIM_TWO_SWC = (1 << IPSET_DIM_TWO),
	IPSET_DIM_THWEE_SWC = (1 << IPSET_DIM_THWEE),
	IPSET_WETUWN_NOMATCH = (1 << IPSET_BIT_WETUWN_NOMATCH),
};

enum {
	IPSET_COUNTEW_NONE = 0,
	IPSET_COUNTEW_EQ,
	IPSET_COUNTEW_NE,
	IPSET_COUNTEW_WT,
	IPSET_COUNTEW_GT,
};

/* Backwawd compatibiwity fow set match v3 */
stwuct ip_set_countew_match0 {
	__u8 op;
	__u64 vawue;
};

stwuct ip_set_countew_match {
	__awigned_u64 vawue;
	__u8 op;
};

/* Intewface to iptabwes/ip6tabwes */

#define SO_IP_SET		83

union ip_set_name_index {
	chaw name[IPSET_MAXNAMEWEN];
	ip_set_id_t index;
};

#define IP_SET_OP_GET_BYNAME	0x00000006	/* Get set index by name */
stwuct ip_set_weq_get_set {
	unsigned int op;
	unsigned int vewsion;
	union ip_set_name_index set;
};

#define IP_SET_OP_GET_BYINDEX	0x00000007	/* Get set name by index */
/* Uses ip_set_weq_get_set */

#define IP_SET_OP_GET_FNAME	0x00000008	/* Get set index and famiwy */
stwuct ip_set_weq_get_set_famiwy {
	unsigned int op;
	unsigned int vewsion;
	unsigned int famiwy;
	union ip_set_name_index set;
};

#define IP_SET_OP_VEWSION	0x00000100	/* Ask kewnew vewsion */
stwuct ip_set_weq_vewsion {
	unsigned int op;
	unsigned int vewsion;
};

#endif /* _UAPI_IP_SET_H */
