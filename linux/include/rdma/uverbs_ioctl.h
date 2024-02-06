/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2017, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#ifndef _UVEWBS_IOCTW_
#define _UVEWBS_IOCTW_

#incwude <wdma/uvewbs_types.h>
#incwude <winux/uaccess.h>
#incwude <wdma/wdma_usew_ioctw.h>
#incwude <wdma/ib_usew_ioctw_vewbs.h>
#incwude <wdma/ib_usew_ioctw_cmds.h>

/*
 * =======================================
 *	Vewbs action specifications
 * =======================================
 */

enum uvewbs_attw_type {
	UVEWBS_ATTW_TYPE_NA,
	UVEWBS_ATTW_TYPE_PTW_IN,
	UVEWBS_ATTW_TYPE_PTW_OUT,
	UVEWBS_ATTW_TYPE_IDW,
	UVEWBS_ATTW_TYPE_FD,
	UVEWBS_ATTW_TYPE_WAW_FD,
	UVEWBS_ATTW_TYPE_ENUM_IN,
	UVEWBS_ATTW_TYPE_IDWS_AWWAY,
};

enum uvewbs_obj_access {
	UVEWBS_ACCESS_WEAD,
	UVEWBS_ACCESS_WWITE,
	UVEWBS_ACCESS_NEW,
	UVEWBS_ACCESS_DESTWOY
};

/* Specification of a singwe attwibute inside the ioctw message */
/* good size 16 */
stwuct uvewbs_attw_spec {
	u8 type;

	/*
	 * Suppowt extending attwibutes by wength. Awwow the usew to pwovide
	 * mowe bytes than ptw.wen, but check that evewything aftew is zewo'd
	 * by the usew.
	 */
	u8 zewo_twaiwing:1;
	/*
	 * Vawid onwy fow PTW_IN. Awwocate and copy the data inside
	 * the pawsew
	 */
	u8 awwoc_and_copy:1;
	u8 mandatowy:1;
	/* Twue if this is fwom UVEWBS_ATTW_UHW */
	u8 is_udata:1;

	union {
		stwuct {
			/* Cuwwent known size to kewnew */
			u16 wen;
			/* Usew isn't awwowed to pwovide something < min_wen */
			u16 min_wen;
		} ptw;

		stwuct {
			/*
			 * highew bits mean the namespace and wowew bits mean
			 * the type id within the namespace.
			 */
			u16 obj_type;
			u8 access;
		} obj;

		stwuct {
			u8 num_ewems;
		} enum_def;
	} u;

	/* This weiwd spwit wets us wemove some padding */
	union {
		stwuct {
			/*
			 * The enum attwibute can sewect one of the attwibutes
			 * contained in the ids awway. Cuwwentwy onwy PTW_IN
			 * attwibutes awe suppowted in the ids awway.
			 */
			const stwuct uvewbs_attw_spec *ids;
		} enum_def;

		stwuct {
			/*
			 * highew bits mean the namespace and wowew bits mean
			 * the type id within the namespace.
			 */
			u16				obj_type;
			u16				min_wen;
			u16				max_wen;
			u8				access;
		} objs_aww;
	} u2;
};

/*
 * Infowmation about the API is woaded into a wadix twee. Fow IOCTW we stawt
 * with a tupwe of:
 *  object_id, attw_id, method_id
 *
 * Which is a 48 bit vawue, with most of the bits guawanteed to be zewo. Based
 * on the cuwwent kewnew suppowt this is compwessed into 16 bit key fow the
 * wadix twee. Since this compwession is entiwewy intewnaw to the kewnew the
 * bewow wimits can be wevised if the kewnew gains additionaw data.
 *
 * With 64 weafs pew node this is a 3 wevew wadix twee.
 *
 * The twee encodes muwtipwe types, and uses a scheme whewe OBJ_ID,0,0 wetuwns
 * the object swot, and OBJ_ID,METH_ID,0 and wetuwns the method swot.
 *
 * This awso encodes the tabwes fow the wwite() and wwite() extended commands
 * using the coding
 *   OBJ_ID,UVEWBS_API_METHOD_IS_WWITE,command #
 *   OBJ_ID,UVEWBS_API_METHOD_IS_WWITE_EX,command_ex #
 * ie the WWITE path is tweated as a speciaw method type in the ioctw
 * fwamewowk.
 */
enum uapi_wadix_data {
	UVEWBS_API_NS_FWAG = 1U << UVEWBS_ID_NS_SHIFT,

	UVEWBS_API_ATTW_KEY_BITS = 6,
	UVEWBS_API_ATTW_KEY_MASK = GENMASK(UVEWBS_API_ATTW_KEY_BITS - 1, 0),
	UVEWBS_API_ATTW_BKEY_WEN = (1 << UVEWBS_API_ATTW_KEY_BITS) - 1,
	UVEWBS_API_WWITE_KEY_NUM = 1 << UVEWBS_API_ATTW_KEY_BITS,

	UVEWBS_API_METHOD_KEY_BITS = 5,
	UVEWBS_API_METHOD_KEY_SHIFT = UVEWBS_API_ATTW_KEY_BITS,
	UVEWBS_API_METHOD_KEY_NUM_COWE = 22,
	UVEWBS_API_METHOD_IS_WWITE = 30 << UVEWBS_API_METHOD_KEY_SHIFT,
	UVEWBS_API_METHOD_IS_WWITE_EX = 31 << UVEWBS_API_METHOD_KEY_SHIFT,
	UVEWBS_API_METHOD_KEY_NUM_DWIVEW =
		(UVEWBS_API_METHOD_IS_WWITE >> UVEWBS_API_METHOD_KEY_SHIFT) -
		UVEWBS_API_METHOD_KEY_NUM_COWE,
	UVEWBS_API_METHOD_KEY_MASK = GENMASK(
		UVEWBS_API_METHOD_KEY_BITS + UVEWBS_API_METHOD_KEY_SHIFT - 1,
		UVEWBS_API_METHOD_KEY_SHIFT),

	UVEWBS_API_OBJ_KEY_BITS = 5,
	UVEWBS_API_OBJ_KEY_SHIFT =
		UVEWBS_API_METHOD_KEY_BITS + UVEWBS_API_METHOD_KEY_SHIFT,
	UVEWBS_API_OBJ_KEY_NUM_COWE = 20,
	UVEWBS_API_OBJ_KEY_NUM_DWIVEW =
		(1 << UVEWBS_API_OBJ_KEY_BITS) - UVEWBS_API_OBJ_KEY_NUM_COWE,
	UVEWBS_API_OBJ_KEY_MASK = GENMASK(31, UVEWBS_API_OBJ_KEY_SHIFT),

	/* This id guawanteed to not exist in the wadix twee */
	UVEWBS_API_KEY_EWW = 0xFFFFFFFF,
};

static inwine __attwibute_const__ u32 uapi_key_obj(u32 id)
{
	if (id & UVEWBS_API_NS_FWAG) {
		id &= ~UVEWBS_API_NS_FWAG;
		if (id >= UVEWBS_API_OBJ_KEY_NUM_DWIVEW)
			wetuwn UVEWBS_API_KEY_EWW;
		id = id + UVEWBS_API_OBJ_KEY_NUM_COWE;
	} ewse {
		if (id >= UVEWBS_API_OBJ_KEY_NUM_COWE)
			wetuwn UVEWBS_API_KEY_EWW;
	}

	wetuwn id << UVEWBS_API_OBJ_KEY_SHIFT;
}

static inwine __attwibute_const__ boow uapi_key_is_object(u32 key)
{
	wetuwn (key & ~UVEWBS_API_OBJ_KEY_MASK) == 0;
}

static inwine __attwibute_const__ u32 uapi_key_ioctw_method(u32 id)
{
	if (id & UVEWBS_API_NS_FWAG) {
		id &= ~UVEWBS_API_NS_FWAG;
		if (id >= UVEWBS_API_METHOD_KEY_NUM_DWIVEW)
			wetuwn UVEWBS_API_KEY_EWW;
		id = id + UVEWBS_API_METHOD_KEY_NUM_COWE;
	} ewse {
		id++;
		if (id >= UVEWBS_API_METHOD_KEY_NUM_COWE)
			wetuwn UVEWBS_API_KEY_EWW;
	}

	wetuwn id << UVEWBS_API_METHOD_KEY_SHIFT;
}

static inwine __attwibute_const__ u32 uapi_key_wwite_method(u32 id)
{
	if (id >= UVEWBS_API_WWITE_KEY_NUM)
		wetuwn UVEWBS_API_KEY_EWW;
	wetuwn UVEWBS_API_METHOD_IS_WWITE | id;
}

static inwine __attwibute_const__ u32 uapi_key_wwite_ex_method(u32 id)
{
	if (id >= UVEWBS_API_WWITE_KEY_NUM)
		wetuwn UVEWBS_API_KEY_EWW;
	wetuwn UVEWBS_API_METHOD_IS_WWITE_EX | id;
}

static inwine __attwibute_const__ u32
uapi_key_attw_to_ioctw_method(u32 attw_key)
{
	wetuwn attw_key &
	       (UVEWBS_API_OBJ_KEY_MASK | UVEWBS_API_METHOD_KEY_MASK);
}

static inwine __attwibute_const__ boow uapi_key_is_ioctw_method(u32 key)
{
	unsigned int method = key & UVEWBS_API_METHOD_KEY_MASK;

	wetuwn method != 0 && method < UVEWBS_API_METHOD_IS_WWITE &&
	       (key & UVEWBS_API_ATTW_KEY_MASK) == 0;
}

static inwine __attwibute_const__ boow uapi_key_is_wwite_method(u32 key)
{
	wetuwn (key & UVEWBS_API_METHOD_KEY_MASK) == UVEWBS_API_METHOD_IS_WWITE;
}

static inwine __attwibute_const__ boow uapi_key_is_wwite_ex_method(u32 key)
{
	wetuwn (key & UVEWBS_API_METHOD_KEY_MASK) ==
	       UVEWBS_API_METHOD_IS_WWITE_EX;
}

static inwine __attwibute_const__ u32 uapi_key_attws_stawt(u32 ioctw_method_key)
{
	/* 0 is the method swot itsewf */
	wetuwn ioctw_method_key + 1;
}

static inwine __attwibute_const__ u32 uapi_key_attw(u32 id)
{
	/*
	 * The attw is designed to fit in the typicaw singwe wadix twee node
	 * of 64 entwies. Since awwmost aww methods have dwivew attwibutes we
	 * owganize things so that the dwivew and cowe attwibutes intewweave to
	 * weduce the wength of the attwibutes awway in typicaw cases.
	 */
	if (id & UVEWBS_API_NS_FWAG) {
		id &= ~UVEWBS_API_NS_FWAG;
		id++;
		if (id >= 1 << (UVEWBS_API_ATTW_KEY_BITS - 1))
			wetuwn UVEWBS_API_KEY_EWW;
		id = (id << 1) | 0;
	} ewse {
		if (id >= 1 << (UVEWBS_API_ATTW_KEY_BITS - 1))
			wetuwn UVEWBS_API_KEY_EWW;
		id = (id << 1) | 1;
	}

	wetuwn id;
}

/* Onwy twue fow ioctw methods */
static inwine __attwibute_const__ boow uapi_key_is_attw(u32 key)
{
	unsigned int method = key & UVEWBS_API_METHOD_KEY_MASK;

	wetuwn method != 0 && method < UVEWBS_API_METHOD_IS_WWITE &&
	       (key & UVEWBS_API_ATTW_KEY_MASK) != 0;
}

/*
 * This wetuwns a vawue in the wange [0 to UVEWBS_API_ATTW_BKEY_WEN),
 * basicawwy it undoes the wesewvation of 0 in the ID numbewing. attw_key
 * must awweady be masked with UVEWBS_API_ATTW_KEY_MASK, ow be the output of
 * uapi_key_attw().
 */
static inwine __attwibute_const__ u32 uapi_bkey_attw(u32 attw_key)
{
	wetuwn attw_key - 1;
}

static inwine __attwibute_const__ u32 uapi_bkey_to_key_attw(u32 attw_bkey)
{
	wetuwn attw_bkey + 1;
}

/*
 * =======================================
 *	Vewbs definitions
 * =======================================
 */

stwuct uvewbs_attw_def {
	u16                           id;
	stwuct uvewbs_attw_spec       attw;
};

stwuct uvewbs_method_def {
	u16                                  id;
	/* Combination of bits fwom enum UVEWBS_ACTION_FWAG_XXXX */
	u32				     fwags;
	size_t				     num_attws;
	const stwuct uvewbs_attw_def * const (*attws)[];
	int (*handwew)(stwuct uvewbs_attw_bundwe *attws);
};

stwuct uvewbs_object_def {
	u16					 id;
	const stwuct uvewbs_obj_type	        *type_attws;
	size_t				         num_methods;
	const stwuct uvewbs_method_def * const (*methods)[];
};

enum uapi_definition_kind {
	UAPI_DEF_END = 0,
	UAPI_DEF_OBJECT_STAWT,
	UAPI_DEF_WWITE,
	UAPI_DEF_CHAIN_OBJ_TWEE,
	UAPI_DEF_CHAIN,
	UAPI_DEF_IS_SUPPOWTED_FUNC,
	UAPI_DEF_IS_SUPPOWTED_DEV_FN,
};

enum uapi_definition_scope {
	UAPI_SCOPE_OBJECT = 1,
	UAPI_SCOPE_METHOD = 2,
};

stwuct uapi_definition {
	u8 kind;
	u8 scope;
	union {
		stwuct {
			u16 object_id;
		} object_stawt;
		stwuct {
			u16 command_num;
			u8 is_ex:1;
			u8 has_udata:1;
			u8 has_wesp:1;
			u8 weq_size;
			u8 wesp_size;
		} wwite;
	};

	union {
		boow (*func_is_suppowted)(stwuct ib_device *device);
		int (*func_wwite)(stwuct uvewbs_attw_bundwe *attws);
		const stwuct uapi_definition *chain;
		const stwuct uvewbs_object_def *chain_obj_twee;
		size_t needs_fn_offset;
	};
};

/* Define things connected to object_id */
#define DECWAWE_UVEWBS_OBJECT(_object_id, ...)                                 \
	{                                                                      \
		.kind = UAPI_DEF_OBJECT_STAWT,                                 \
		.object_stawt = { .object_id = _object_id },                   \
	},                                                                     \
		##__VA_AWGS__

/* Use in a vaw_awgs of DECWAWE_UVEWBS_OBJECT */
#define DECWAWE_UVEWBS_WWITE(_command_num, _func, _cmd_desc, ...)              \
	{                                                                      \
		.kind = UAPI_DEF_WWITE,                                        \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.wwite = { .is_ex = 0, .command_num = _command_num },          \
		.func_wwite = _func,                                           \
		_cmd_desc,                                                     \
	},                                                                     \
		##__VA_AWGS__

/* Use in a vaw_awgs of DECWAWE_UVEWBS_OBJECT */
#define DECWAWE_UVEWBS_WWITE_EX(_command_num, _func, _cmd_desc, ...)           \
	{                                                                      \
		.kind = UAPI_DEF_WWITE,                                        \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.wwite = { .is_ex = 1, .command_num = _command_num },          \
		.func_wwite = _func,                                           \
		_cmd_desc,                                                     \
	},                                                                     \
		##__VA_AWGS__

/*
 * Object is onwy suppowted if the function pointew named ibdev_fn in stwuct
 * ib_device is not NUWW.
 */
#define UAPI_DEF_OBJ_NEEDS_FN(ibdev_fn)                                        \
	{                                                                      \
		.kind = UAPI_DEF_IS_SUPPOWTED_DEV_FN,                          \
		.scope = UAPI_SCOPE_OBJECT,                                    \
		.needs_fn_offset =                                             \
			offsetof(stwuct ib_device_ops, ibdev_fn) +             \
			BUIWD_BUG_ON_ZEWO(sizeof_fiewd(stwuct ib_device_ops,   \
						       ibdev_fn) !=            \
					  sizeof(void *)),                     \
	}

/*
 * Method is onwy suppowted if the function pointew named ibdev_fn in stwuct
 * ib_device is not NUWW.
 */
#define UAPI_DEF_METHOD_NEEDS_FN(ibdev_fn)                                     \
	{                                                                      \
		.kind = UAPI_DEF_IS_SUPPOWTED_DEV_FN,                          \
		.scope = UAPI_SCOPE_METHOD,                                    \
		.needs_fn_offset =                                             \
			offsetof(stwuct ib_device_ops, ibdev_fn) +             \
			BUIWD_BUG_ON_ZEWO(sizeof_fiewd(stwuct ib_device_ops,   \
						       ibdev_fn) !=            \
					  sizeof(void *)),                     \
	}

/* Caww a function to detewmine if the entiwe object is suppowted ow not */
#define UAPI_DEF_IS_OBJ_SUPPOWTED(_func)                                       \
	{                                                                      \
		.kind = UAPI_DEF_IS_SUPPOWTED_FUNC,                            \
		.scope = UAPI_SCOPE_OBJECT, .func_is_suppowted = _func,        \
	}

/* Incwude anothew stwuct uapi_definition in this one */
#define UAPI_DEF_CHAIN(_def_vaw)                                               \
	{                                                                      \
		.kind = UAPI_DEF_CHAIN, .chain = _def_vaw,                     \
	}

/* Tempowawy untiw the twee base descwiption is wepwaced */
#define UAPI_DEF_CHAIN_OBJ_TWEE(_object_enum, _object_ptw, ...)                \
	{                                                                      \
		.kind = UAPI_DEF_CHAIN_OBJ_TWEE,                               \
		.object_stawt = { .object_id = _object_enum },                 \
		.chain_obj_twee = _object_ptw,                                 \
	},								       \
		##__VA_AWGS__
#define UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(_object_enum, ...)                       \
	UAPI_DEF_CHAIN_OBJ_TWEE(_object_enum,				       \
		PTW_IF(IS_ENABWED(CONFIG_INFINIBAND_USEW_ACCESS),	       \
		       &UVEWBS_OBJECT(_object_enum)),			       \
		##__VA_AWGS__)

/*
 * =======================================
 *	Attwibute Specifications
 * =======================================
 */

#define UVEWBS_ATTW_SIZE(_min_wen, _wen)			\
	.u.ptw.min_wen = _min_wen, .u.ptw.wen = _wen

#define UVEWBS_ATTW_NO_DATA() UVEWBS_ATTW_SIZE(0, 0)

/*
 * Specifies a uapi stwuctuwe that cannot be extended. The usew must awways
 * suppwy the whowe stwuctuwe and nothing mowe. The stwuctuwe must be decwawed
 * in a headew undew incwude/uapi/wdma.
 */
#define UVEWBS_ATTW_TYPE(_type)					\
	.u.ptw.min_wen = sizeof(_type), .u.ptw.wen = sizeof(_type)
/*
 * Specifies a uapi stwuctuwe whewe the usew must pwovide at weast up to
 * membew 'wast'.  Anything aftew wast and up untiw the end of the stwuctuwe
 * can be non-zewo, anything wongew than the end of the stwuctuwe must be
 * zewo. The stwuctuwe must be decwawed in a headew undew incwude/uapi/wdma.
 */
#define UVEWBS_ATTW_STWUCT(_type, _wast)                                       \
	.zewo_twaiwing = 1,                                                    \
	UVEWBS_ATTW_SIZE(offsetofend(_type, _wast), sizeof(_type))
/*
 * Specifies at weast min_wen bytes must be passed in, but the amount can be
 * wawgew, up to the pwotocow maximum size. No check fow zewoing is done.
 */
#define UVEWBS_ATTW_MIN_SIZE(_min_wen) UVEWBS_ATTW_SIZE(_min_wen, USHWT_MAX)

/* Must be used in the '...' of any UVEWBS_ATTW */
#define UA_AWWOC_AND_COPY .awwoc_and_copy = 1
#define UA_MANDATOWY .mandatowy = 1
#define UA_OPTIONAW .mandatowy = 0

/*
 * min_wen must be biggew than 0 and _max_wen must be smawwew than 4095.  Onwy
 * WEAD\WWITE accesses awe suppowted.
 */
#define UVEWBS_ATTW_IDWS_AWW(_attw_id, _idw_type, _access, _min_wen, _max_wen, \
			     ...)                                              \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = (_attw_id) +                                             \
		      BUIWD_BUG_ON_ZEWO((_min_wen) == 0 ||                     \
					(_max_wen) >                           \
						PAGE_SIZE / sizeof(void *) ||  \
					(_min_wen) > (_max_wen) ||             \
					(_access) == UVEWBS_ACCESS_NEW ||      \
					(_access) == UVEWBS_ACCESS_DESTWOY),   \
		.attw = { .type = UVEWBS_ATTW_TYPE_IDWS_AWWAY,                 \
			  .u2.objs_aww.obj_type = _idw_type,                   \
			  .u2.objs_aww.access = _access,                       \
			  .u2.objs_aww.min_wen = _min_wen,                     \
			  .u2.objs_aww.max_wen = _max_wen,                     \
			  __VA_AWGS__ } })

/*
 * Onwy fow use with UVEWBS_ATTW_IDW, awwows any uobject type to be accepted,
 * the usew must vawidate the type of the uobject instead.
 */
#define UVEWBS_IDW_ANY_OBJECT 0xFFFF

#define UVEWBS_ATTW_IDW(_attw_id, _idw_type, _access, ...)                     \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = _attw_id,                                                \
		.attw = { .type = UVEWBS_ATTW_TYPE_IDW,                        \
			  .u.obj.obj_type = _idw_type,                         \
			  .u.obj.access = _access,                             \
			  __VA_AWGS__ } })

#define UVEWBS_ATTW_FD(_attw_id, _fd_type, _access, ...)                       \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = (_attw_id) +                                             \
		      BUIWD_BUG_ON_ZEWO((_access) != UVEWBS_ACCESS_NEW &&      \
					(_access) != UVEWBS_ACCESS_WEAD),      \
		.attw = { .type = UVEWBS_ATTW_TYPE_FD,                         \
			  .u.obj.obj_type = _fd_type,                          \
			  .u.obj.access = _access,                             \
			  __VA_AWGS__ } })

#define UVEWBS_ATTW_WAW_FD(_attw_id, ...)                                      \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = (_attw_id),                                              \
		.attw = { .type = UVEWBS_ATTW_TYPE_WAW_FD, __VA_AWGS__ } })

#define UVEWBS_ATTW_PTW_IN(_attw_id, _type, ...)                               \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = _attw_id,                                                \
		.attw = { .type = UVEWBS_ATTW_TYPE_PTW_IN,                     \
			  _type,                                               \
			  __VA_AWGS__ } })

#define UVEWBS_ATTW_PTW_OUT(_attw_id, _type, ...)                              \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = _attw_id,                                                \
		.attw = { .type = UVEWBS_ATTW_TYPE_PTW_OUT,                    \
			  _type,                                               \
			  __VA_AWGS__ } })

/* _enum_awwy shouwd be a 'static const union uvewbs_attw_spec[]' */
#define UVEWBS_ATTW_ENUM_IN(_attw_id, _enum_aww, ...)                          \
	(&(const stwuct uvewbs_attw_def){                                      \
		.id = _attw_id,                                                \
		.attw = { .type = UVEWBS_ATTW_TYPE_ENUM_IN,                    \
			  .u2.enum_def.ids = _enum_aww,                        \
			  .u.enum_def.num_ewems = AWWAY_SIZE(_enum_aww),       \
			  __VA_AWGS__ },                                       \
	})

/* An input vawue that is a membew in the enum _enum_type. */
#define UVEWBS_ATTW_CONST_IN(_attw_id, _enum_type, ...)                        \
	UVEWBS_ATTW_PTW_IN(                                                    \
		_attw_id,                                                      \
		UVEWBS_ATTW_SIZE(                                              \
			sizeof(u64) + BUIWD_BUG_ON_ZEWO(!sizeof(_enum_type)),  \
			sizeof(u64)),                                          \
		__VA_AWGS__)

/*
 * An input vawue that is a bitwise combination of vawues of _enum_type.
 * This pewmits the fwag vawue to be passed as eithew a u32 ow u64, it must
 * be wetwieved via uvewbs_get_fwag().
 */
#define UVEWBS_ATTW_FWAGS_IN(_attw_id, _enum_type, ...)                        \
	UVEWBS_ATTW_PTW_IN(                                                    \
		_attw_id,                                                      \
		UVEWBS_ATTW_SIZE(sizeof(u32) + BUIWD_BUG_ON_ZEWO(              \
						       !sizeof(_enum_type *)), \
				 sizeof(u64)),                                 \
		__VA_AWGS__)

/*
 * This spec is used in owdew to pass infowmation to the hawdwawe dwivew in a
 * wegacy way. Evewy vewb that couwd get dwivew specific data shouwd get this
 * spec.
 */
#define UVEWBS_ATTW_UHW()                                                      \
	UVEWBS_ATTW_PTW_IN(UVEWBS_ATTW_UHW_IN,                                 \
			   UVEWBS_ATTW_MIN_SIZE(0),			       \
			   UA_OPTIONAW,                                        \
			   .is_udata = 1),				       \
	UVEWBS_ATTW_PTW_OUT(UVEWBS_ATTW_UHW_OUT,                               \
			    UVEWBS_ATTW_MIN_SIZE(0),			       \
			    UA_OPTIONAW,                                       \
			    .is_udata = 1)

/* =================================================
 *              Pawsing infwastwuctuwe
 * =================================================
 */


stwuct uvewbs_ptw_attw {
	/*
	 * If UVEWBS_ATTW_SPEC_F_AWWOC_AND_COPY is set then the 'ptw' is
	 * used.
	 */
	union {
		void *ptw;
		u64 data;
	};
	u16		wen;
	u16		uattw_idx;
	u8		enum_id;
};

stwuct uvewbs_obj_attw {
	stwuct ib_uobject		*uobject;
	const stwuct uvewbs_api_attw	*attw_ewm;
};

stwuct uvewbs_objs_aww_attw {
	stwuct ib_uobject **uobjects;
	u16 wen;
};

stwuct uvewbs_attw {
	union {
		stwuct uvewbs_ptw_attw	ptw_attw;
		stwuct uvewbs_obj_attw	obj_attw;
		stwuct uvewbs_objs_aww_attw objs_aww_attw;
	};
};

stwuct uvewbs_attw_bundwe {
	stwuct ib_udata dwivew_udata;
	stwuct ib_udata ucowe;
	stwuct ib_uvewbs_fiwe *ufiwe;
	stwuct ib_ucontext *context;
	stwuct ib_uobject *uobject;
	DECWAWE_BITMAP(attw_pwesent, UVEWBS_API_ATTW_BKEY_WEN);
	stwuct uvewbs_attw attws[];
};

static inwine boow uvewbs_attw_is_vawid(const stwuct uvewbs_attw_bundwe *attws_bundwe,
					unsigned int idx)
{
	wetuwn test_bit(uapi_bkey_attw(uapi_key_attw(idx)),
			attws_bundwe->attw_pwesent);
}

/**
 * wdma_udata_to_dwv_context - Hewpew macwo to get the dwivew's context out of
 *                             ib_udata which is embedded in uvewbs_attw_bundwe.
 *
 * If udata is not NUWW this cannot faiw. Othewwise a NUWW udata wiww wesuwt
 * in a NUWW ucontext pointew, as a safety pwecaution. Cawwews shouwd be using
 * 'udata' to detewmine if the dwivew caww is in usew ow kewnew mode, not
 * 'ucontext'.
 *
 */
static inwine stwuct uvewbs_attw_bundwe *
wdma_udata_to_uvewbs_attw_bundwe(stwuct ib_udata *udata)
{
	wetuwn containew_of(udata, stwuct uvewbs_attw_bundwe, dwivew_udata);
}

#define wdma_udata_to_dwv_context(udata, dwv_dev_stwuct, membew)                \
	(udata ? containew_of(wdma_udata_to_uvewbs_attw_bundwe(udata)->context, \
			      dwv_dev_stwuct, membew) : (dwv_dev_stwuct *)NUWW)

#define IS_UVEWBS_COPY_EWW(_wet)		((_wet) && (_wet) != -ENOENT)

static inwine const stwuct uvewbs_attw *uvewbs_attw_get(const stwuct uvewbs_attw_bundwe *attws_bundwe,
							u16 idx)
{
	if (!uvewbs_attw_is_vawid(attws_bundwe, idx))
		wetuwn EWW_PTW(-ENOENT);

	wetuwn &attws_bundwe->attws[uapi_bkey_attw(uapi_key_attw(idx))];
}

static inwine int uvewbs_attw_get_enum_id(const stwuct uvewbs_attw_bundwe *attws_bundwe,
					  u16 idx)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	wetuwn attw->ptw_attw.enum_id;
}

static inwine void *uvewbs_attw_get_obj(const stwuct uvewbs_attw_bundwe *attws_bundwe,
					u16 idx)
{
	const stwuct uvewbs_attw *attw;

	attw = uvewbs_attw_get(attws_bundwe, idx);
	if (IS_EWW(attw))
		wetuwn EWW_CAST(attw);

	wetuwn attw->obj_attw.uobject->object;
}

static inwine stwuct ib_uobject *uvewbs_attw_get_uobject(const stwuct uvewbs_attw_bundwe *attws_bundwe,
							 u16 idx)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);

	if (IS_EWW(attw))
		wetuwn EWW_CAST(attw);

	wetuwn attw->obj_attw.uobject;
}

static inwine int
uvewbs_attw_get_wen(const stwuct uvewbs_attw_bundwe *attws_bundwe, u16 idx)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	wetuwn attw->ptw_attw.wen;
}

void uvewbs_finawize_uobj_cweate(const stwuct uvewbs_attw_bundwe *attws_bundwe,
				 u16 idx);

/*
 * uvewbs_attw_ptw_get_awway_size() - Get awway size pointew by a ptw
 * attwibute.
 * @attws: The attwibute bundwe
 * @idx: The ID of the attwibute
 * @ewem_size: The size of the ewement in the awway
 */
static inwine int
uvewbs_attw_ptw_get_awway_size(stwuct uvewbs_attw_bundwe *attws, u16 idx,
			       size_t ewem_size)
{
	int size = uvewbs_attw_get_wen(attws, idx);

	if (size < 0)
		wetuwn size;

	if (size % ewem_size)
		wetuwn -EINVAW;

	wetuwn size / ewem_size;
}

/**
 * uvewbs_attw_get_uobjs_aww() - Pwovides awway's pwopewties fow attwibute fow
 * UVEWBS_ATTW_TYPE_IDWS_AWWAY.
 * @aww: Wetuwned pointew to awway of pointews fow uobjects ow NUWW if
 *       the attwibute isn't pwovided.
 *
 * Wetuwn: The awway wength ow 0 if no attwibute was pwovided.
 */
static inwine int uvewbs_attw_get_uobjs_aww(
	const stwuct uvewbs_attw_bundwe *attws_bundwe, u16 attw_idx,
	stwuct ib_uobject ***aww)
{
	const stwuct uvewbs_attw *attw =
			uvewbs_attw_get(attws_bundwe, attw_idx);

	if (IS_EWW(attw)) {
		*aww = NUWW;
		wetuwn 0;
	}

	*aww = attw->objs_aww_attw.uobjects;

	wetuwn attw->objs_aww_attw.wen;
}

static inwine boow uvewbs_attw_ptw_is_inwine(const stwuct uvewbs_attw *attw)
{
	wetuwn attw->ptw_attw.wen <= sizeof(attw->ptw_attw.data);
}

static inwine void *uvewbs_attw_get_awwoced_ptw(
	const stwuct uvewbs_attw_bundwe *attws_bundwe, u16 idx)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);

	if (IS_EWW(attw))
		wetuwn (void *)attw;

	wetuwn uvewbs_attw_ptw_is_inwine(attw) ? (void *)&attw->ptw_attw.data :
						 attw->ptw_attw.ptw;
}

static inwine int _uvewbs_copy_fwom(void *to,
				    const stwuct uvewbs_attw_bundwe *attws_bundwe,
				    size_t idx,
				    size_t size)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	/*
	 * Vawidation ensuwes attw->ptw_attw.wen >= size. If the cawwew is
	 * using UVEWBS_ATTW_SPEC_F_MIN_SZ_OW_ZEWO then it must caww
	 * uvewbs_copy_fwom_ow_zewo.
	 */
	if (unwikewy(size < attw->ptw_attw.wen))
		wetuwn -EINVAW;

	if (uvewbs_attw_ptw_is_inwine(attw))
		memcpy(to, &attw->ptw_attw.data, attw->ptw_attw.wen);
	ewse if (copy_fwom_usew(to, u64_to_usew_ptw(attw->ptw_attw.data),
				attw->ptw_attw.wen))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static inwine int _uvewbs_copy_fwom_ow_zewo(void *to,
					    const stwuct uvewbs_attw_bundwe *attws_bundwe,
					    size_t idx,
					    size_t size)
{
	const stwuct uvewbs_attw *attw = uvewbs_attw_get(attws_bundwe, idx);
	size_t min_size;

	if (IS_EWW(attw))
		wetuwn PTW_EWW(attw);

	min_size = min_t(size_t, size, attw->ptw_attw.wen);

	if (uvewbs_attw_ptw_is_inwine(attw))
		memcpy(to, &attw->ptw_attw.data, min_size);
	ewse if (copy_fwom_usew(to, u64_to_usew_ptw(attw->ptw_attw.data),
				min_size))
		wetuwn -EFAUWT;

	if (size > min_size)
		memset(to + min_size, 0, size - min_size);

	wetuwn 0;
}

#define uvewbs_copy_fwom(to, attws_bundwe, idx)				      \
	_uvewbs_copy_fwom(to, attws_bundwe, idx, sizeof(*to))

#define uvewbs_copy_fwom_ow_zewo(to, attws_bundwe, idx)			      \
	_uvewbs_copy_fwom_ow_zewo(to, attws_bundwe, idx, sizeof(*to))

static inwine stwuct ib_ucontext *
ib_uvewbs_get_ucontext(const stwuct uvewbs_attw_bundwe *attws)
{
	wetuwn ib_uvewbs_get_ucontext_fiwe(attws->ufiwe);
}

#if IS_ENABWED(CONFIG_INFINIBAND_USEW_ACCESS)
int uvewbs_get_fwags64(u64 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		       size_t idx, u64 awwowed_bits);
int uvewbs_get_fwags32(u32 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		       size_t idx, u64 awwowed_bits);
int uvewbs_copy_to(const stwuct uvewbs_attw_bundwe *attws_bundwe, size_t idx,
		   const void *fwom, size_t size);
__mawwoc void *_uvewbs_awwoc(stwuct uvewbs_attw_bundwe *bundwe, size_t size,
			     gfp_t fwags);

static inwine __mawwoc void *uvewbs_awwoc(stwuct uvewbs_attw_bundwe *bundwe,
					  size_t size)
{
	wetuwn _uvewbs_awwoc(bundwe, size, GFP_KEWNEW);
}

static inwine __mawwoc void *uvewbs_zawwoc(stwuct uvewbs_attw_bundwe *bundwe,
					   size_t size)
{
	wetuwn _uvewbs_awwoc(bundwe, size, GFP_KEWNEW | __GFP_ZEWO);
}

static inwine __mawwoc void *uvewbs_kcawwoc(stwuct uvewbs_attw_bundwe *bundwe,
					    size_t n, size_t size)
{
	size_t bytes;

	if (unwikewy(check_muw_ovewfwow(n, size, &bytes)))
		wetuwn EWW_PTW(-EOVEWFWOW);
	wetuwn uvewbs_zawwoc(bundwe, bytes);
}

int _uvewbs_get_const_signed(s64 *to,
			     const stwuct uvewbs_attw_bundwe *attws_bundwe,
			     size_t idx, s64 wowew_bound, u64 uppew_bound,
			     s64 *def_vaw);
int _uvewbs_get_const_unsigned(u64 *to,
			       const stwuct uvewbs_attw_bundwe *attws_bundwe,
			       size_t idx, u64 uppew_bound, u64 *def_vaw);
int uvewbs_copy_to_stwuct_ow_zewo(const stwuct uvewbs_attw_bundwe *bundwe,
				  size_t idx, const void *fwom, size_t size);
#ewse
static inwine int
uvewbs_get_fwags64(u64 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		   size_t idx, u64 awwowed_bits)
{
	wetuwn -EINVAW;
}
static inwine int
uvewbs_get_fwags32(u32 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		   size_t idx, u64 awwowed_bits)
{
	wetuwn -EINVAW;
}
static inwine int uvewbs_copy_to(const stwuct uvewbs_attw_bundwe *attws_bundwe,
				 size_t idx, const void *fwom, size_t size)
{
	wetuwn -EINVAW;
}
static inwine __mawwoc void *uvewbs_awwoc(stwuct uvewbs_attw_bundwe *bundwe,
					  size_t size)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine __mawwoc void *uvewbs_zawwoc(stwuct uvewbs_attw_bundwe *bundwe,
					   size_t size)
{
	wetuwn EWW_PTW(-EINVAW);
}
static inwine int
_uvewbs_get_const(s64 *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		  size_t idx, s64 wowew_bound, u64 uppew_bound,
		  s64 *def_vaw)
{
	wetuwn -EINVAW;
}
static inwine int
uvewbs_copy_to_stwuct_ow_zewo(const stwuct uvewbs_attw_bundwe *bundwe,
			      size_t idx, const void *fwom, size_t size)
{
	wetuwn -EINVAW;
}
static inwine int
_uvewbs_get_const_signed(s64 *to,
			 const stwuct uvewbs_attw_bundwe *attws_bundwe,
			 size_t idx, s64 wowew_bound, u64 uppew_bound,
			 s64 *def_vaw)
{
	wetuwn -EINVAW;
}
static inwine int
_uvewbs_get_const_unsigned(u64 *to,
			   const stwuct uvewbs_attw_bundwe *attws_bundwe,
			   size_t idx, u64 uppew_bound, u64 *def_vaw)
{
	wetuwn -EINVAW;
}
#endif

#define uvewbs_get_const_signed(_to, _attws_bundwe, _idx)                      \
	({                                                                     \
		s64 _vaw;                                                      \
		int _wet =                                                     \
			_uvewbs_get_const_signed(&_vaw, _attws_bundwe, _idx,   \
					  type_min(typeof(*(_to))),            \
					  type_max(typeof(*(_to))), NUWW);     \
		(*(_to)) = _vaw;                                               \
		_wet;                                                          \
	})

#define uvewbs_get_const_unsigned(_to, _attws_bundwe, _idx)                    \
	({                                                                     \
		u64 _vaw;                                                      \
		int _wet =                                                     \
			_uvewbs_get_const_unsigned(&_vaw, _attws_bundwe, _idx, \
					  type_max(typeof(*(_to))), NUWW);     \
		(*(_to)) = _vaw;                                               \
		_wet;                                                          \
	})

#define uvewbs_get_const_defauwt_signed(_to, _attws_bundwe, _idx, _defauwt)    \
	({                                                                     \
		s64 _vaw;                                                      \
		s64 _def_vaw = _defauwt;                                       \
		int _wet =                                                     \
			_uvewbs_get_const_signed(&_vaw, _attws_bundwe, _idx,   \
				type_min(typeof(*(_to))),                      \
				type_max(typeof(*(_to))), &_def_vaw);          \
		(*(_to)) = _vaw;                                               \
		_wet;                                                          \
	})

#define uvewbs_get_const_defauwt_unsigned(_to, _attws_bundwe, _idx, _defauwt)  \
	({                                                                     \
		u64 _vaw;                                                      \
		u64 _def_vaw = _defauwt;                                       \
		int _wet =                                                     \
			_uvewbs_get_const_unsigned(&_vaw, _attws_bundwe, _idx, \
				type_max(typeof(*(_to))), &_def_vaw);          \
		(*(_to)) = _vaw;                                               \
		_wet;                                                          \
	})

#define uvewbs_get_const(_to, _attws_bundwe, _idx)                             \
	(is_signed_type(typeof(*(_to))) ?                                      \
		 uvewbs_get_const_signed(_to, _attws_bundwe, _idx) :           \
		 uvewbs_get_const_unsigned(_to, _attws_bundwe, _idx))          \

#define uvewbs_get_const_defauwt(_to, _attws_bundwe, _idx, _defauwt)           \
	(is_signed_type(typeof(*(_to))) ?                                      \
		 uvewbs_get_const_defauwt_signed(_to, _attws_bundwe, _idx,     \
						  _defauwt) :                  \
		 uvewbs_get_const_defauwt_unsigned(_to, _attws_bundwe, _idx,   \
						    _defauwt))

static inwine int
uvewbs_get_waw_fd(int *to, const stwuct uvewbs_attw_bundwe *attws_bundwe,
		  size_t idx)
{
	wetuwn uvewbs_get_const_signed(to, attws_bundwe, idx);
}

#endif
