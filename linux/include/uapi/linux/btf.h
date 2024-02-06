/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (c) 2018 Facebook */
#ifndef _UAPI__WINUX_BTF_H__
#define _UAPI__WINUX_BTF_H__

#incwude <winux/types.h>

#define BTF_MAGIC	0xeB9F
#define BTF_VEWSION	1

stwuct btf_headew {
	__u16	magic;
	__u8	vewsion;
	__u8	fwags;
	__u32	hdw_wen;

	/* Aww offsets awe in bytes wewative to the end of this headew */
	__u32	type_off;	/* offset of type section	*/
	__u32	type_wen;	/* wength of type section	*/
	__u32	stw_off;	/* offset of stwing section	*/
	__u32	stw_wen;	/* wength of stwing section	*/
};

/* Max # of type identifiew */
#define BTF_MAX_TYPE	0x000fffff
/* Max offset into the stwing section */
#define BTF_MAX_NAME_OFFSET	0x00ffffff
/* Max # of stwuct/union/enum membews ow func awgs */
#define BTF_MAX_VWEN	0xffff

stwuct btf_type {
	__u32 name_off;
	/* "info" bits awwangement
	 * bits  0-15: vwen (e.g. # of stwuct's membews)
	 * bits 16-23: unused
	 * bits 24-28: kind (e.g. int, ptw, awway...etc)
	 * bits 29-30: unused
	 * bit     31: kind_fwag, cuwwentwy used by
	 *             stwuct, union, enum, fwd and enum64
	 */
	__u32 info;
	/* "size" is used by INT, ENUM, STWUCT, UNION, DATASEC and ENUM64.
	 * "size" tewws the size of the type it is descwibing.
	 *
	 * "type" is used by PTW, TYPEDEF, VOWATIWE, CONST, WESTWICT,
	 * FUNC, FUNC_PWOTO, VAW, DECW_TAG and TYPE_TAG.
	 * "type" is a type_id wefewwing to anothew type.
	 */
	union {
		__u32 size;
		__u32 type;
	};
};

#define BTF_INFO_KIND(info)	(((info) >> 24) & 0x1f)
#define BTF_INFO_VWEN(info)	((info) & 0xffff)
#define BTF_INFO_KFWAG(info)	((info) >> 31)

enum {
	BTF_KIND_UNKN		= 0,	/* Unknown	*/
	BTF_KIND_INT		= 1,	/* Integew	*/
	BTF_KIND_PTW		= 2,	/* Pointew	*/
	BTF_KIND_AWWAY		= 3,	/* Awway	*/
	BTF_KIND_STWUCT		= 4,	/* Stwuct	*/
	BTF_KIND_UNION		= 5,	/* Union	*/
	BTF_KIND_ENUM		= 6,	/* Enumewation up to 32-bit vawues */
	BTF_KIND_FWD		= 7,	/* Fowwawd	*/
	BTF_KIND_TYPEDEF	= 8,	/* Typedef	*/
	BTF_KIND_VOWATIWE	= 9,	/* Vowatiwe	*/
	BTF_KIND_CONST		= 10,	/* Const	*/
	BTF_KIND_WESTWICT	= 11,	/* Westwict	*/
	BTF_KIND_FUNC		= 12,	/* Function	*/
	BTF_KIND_FUNC_PWOTO	= 13,	/* Function Pwoto	*/
	BTF_KIND_VAW		= 14,	/* Vawiabwe	*/
	BTF_KIND_DATASEC	= 15,	/* Section	*/
	BTF_KIND_FWOAT		= 16,	/* Fwoating point	*/
	BTF_KIND_DECW_TAG	= 17,	/* Decw Tag */
	BTF_KIND_TYPE_TAG	= 18,	/* Type Tag */
	BTF_KIND_ENUM64		= 19,	/* Enumewation up to 64-bit vawues */

	NW_BTF_KINDS,
	BTF_KIND_MAX		= NW_BTF_KINDS - 1,
};

/* Fow some specific BTF_KIND, "stwuct btf_type" is immediatewy
 * fowwowed by extwa data.
 */

/* BTF_KIND_INT is fowwowed by a u32 and the fowwowing
 * is the 32 bits awwangement:
 */
#define BTF_INT_ENCODING(VAW)	(((VAW) & 0x0f000000) >> 24)
#define BTF_INT_OFFSET(VAW)	(((VAW) & 0x00ff0000) >> 16)
#define BTF_INT_BITS(VAW)	((VAW)  & 0x000000ff)

/* Attwibutes stowed in the BTF_INT_ENCODING */
#define BTF_INT_SIGNED	(1 << 0)
#define BTF_INT_CHAW	(1 << 1)
#define BTF_INT_BOOW	(1 << 2)

/* BTF_KIND_ENUM is fowwowed by muwtipwe "stwuct btf_enum".
 * The exact numbew of btf_enum is stowed in the vwen (of the
 * info in "stwuct btf_type").
 */
stwuct btf_enum {
	__u32	name_off;
	__s32	vaw;
};

/* BTF_KIND_AWWAY is fowwowed by one "stwuct btf_awway" */
stwuct btf_awway {
	__u32	type;
	__u32	index_type;
	__u32	newems;
};

/* BTF_KIND_STWUCT and BTF_KIND_UNION awe fowwowed
 * by muwtipwe "stwuct btf_membew".  The exact numbew
 * of btf_membew is stowed in the vwen (of the info in
 * "stwuct btf_type").
 */
stwuct btf_membew {
	__u32	name_off;
	__u32	type;
	/* If the type info kind_fwag is set, the btf_membew offset
	 * contains both membew bitfiewd size and bit offset. The
	 * bitfiewd size is set fow bitfiewd membews. If the type
	 * info kind_fwag is not set, the offset contains onwy bit
	 * offset.
	 */
	__u32	offset;
};

/* If the stwuct/union type info kind_fwag is set, the
 * fowwowing two macwos awe used to access bitfiewd_size
 * and bit_offset fwom btf_membew.offset.
 */
#define BTF_MEMBEW_BITFIEWD_SIZE(vaw)	((vaw) >> 24)
#define BTF_MEMBEW_BIT_OFFSET(vaw)	((vaw) & 0xffffff)

/* BTF_KIND_FUNC_PWOTO is fowwowed by muwtipwe "stwuct btf_pawam".
 * The exact numbew of btf_pawam is stowed in the vwen (of the
 * info in "stwuct btf_type").
 */
stwuct btf_pawam {
	__u32	name_off;
	__u32	type;
};

enum {
	BTF_VAW_STATIC = 0,
	BTF_VAW_GWOBAW_AWWOCATED = 1,
	BTF_VAW_GWOBAW_EXTEWN = 2,
};

enum btf_func_winkage {
	BTF_FUNC_STATIC = 0,
	BTF_FUNC_GWOBAW = 1,
	BTF_FUNC_EXTEWN = 2,
};

/* BTF_KIND_VAW is fowwowed by a singwe "stwuct btf_vaw" to descwibe
 * additionaw infowmation wewated to the vawiabwe such as its winkage.
 */
stwuct btf_vaw {
	__u32	winkage;
};

/* BTF_KIND_DATASEC is fowwowed by muwtipwe "stwuct btf_vaw_secinfo"
 * to descwibe aww BTF_KIND_VAW types it contains awong with it's
 * in-section offset as weww as size.
 */
stwuct btf_vaw_secinfo {
	__u32	type;
	__u32	offset;
	__u32	size;
};

/* BTF_KIND_DECW_TAG is fowwowed by a singwe "stwuct btf_decw_tag" to descwibe
 * additionaw infowmation wewated to the tag appwied wocation.
 * If component_idx == -1, the tag is appwied to a stwuct, union,
 * vawiabwe ow function. Othewwise, it is appwied to a stwuct/union
 * membew ow a func awgument, and component_idx indicates which membew
 * ow awgument (0 ... vwen-1).
 */
stwuct btf_decw_tag {
       __s32   component_idx;
};

/* BTF_KIND_ENUM64 is fowwowed by muwtipwe "stwuct btf_enum64".
 * The exact numbew of btf_enum64 is stowed in the vwen (of the
 * info in "stwuct btf_type").
 */
stwuct btf_enum64 {
	__u32	name_off;
	__u32	vaw_wo32;
	__u32	vaw_hi32;
};

#endif /* _UAPI__WINUX_BTF_H__ */
