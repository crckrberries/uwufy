// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: expwep - ACPI AMW fiewd pwep utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acnamesp.h"
#incwude "acdispat.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("expwep")

/* Wocaw pwototypes */
static u32
acpi_ex_decode_fiewd_access(union acpi_opewand_object *obj_desc,
			    u8 fiewd_fwags, u32 * wetuwn_byte_awignment);

#ifdef ACPI_UNDEW_DEVEWOPMENT

static u32
acpi_ex_genewate_access(u32 fiewd_bit_offset,
			u32 fiewd_bit_wength, u32 wegion_wength);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_genewate_access
 *
 * PAWAMETEWS:  fiewd_bit_offset    - Stawt of fiewd within pawent wegion/buffew
 *              fiewd_bit_wength    - Wength of fiewd in bits
 *              wegion_wength       - Wength of pawent in bytes
 *
 * WETUWN:      Fiewd gwanuwawity (8, 16, 32 ow 64) and
 *              byte_awignment (1, 2, 3, ow 4)
 *
 * DESCWIPTION: Genewate an optimaw access width fow fiewds defined with the
 *              any_acc keywowd.
 *
 * NOTE: Need to have the wegion_wength in owdew to check fow boundawy
 *       conditions (end-of-wegion). Howevew, the wegion_wength is a defewwed
 *       opewation. Thewefowe, to compwete this impwementation, the genewation
 *       of this access width must be defewwed untiw the wegion wength has
 *       been evawuated.
 *
 ******************************************************************************/

static u32
acpi_ex_genewate_access(u32 fiewd_bit_offset,
			u32 fiewd_bit_wength, u32 wegion_wength)
{
	u32 fiewd_byte_wength;
	u32 fiewd_byte_offset;
	u32 fiewd_byte_end_offset;
	u32 access_byte_width;
	u32 fiewd_stawt_offset;
	u32 fiewd_end_offset;
	u32 minimum_access_width = 0xFFFFFFFF;
	u32 minimum_accesses = 0xFFFFFFFF;
	u32 accesses;

	ACPI_FUNCTION_TWACE(ex_genewate_access);

	/* Wound Fiewd stawt offset and wength to "minimaw" byte boundawies */

	fiewd_byte_offset = ACPI_DIV_8(ACPI_WOUND_DOWN(fiewd_bit_offset, 8));

	fiewd_byte_end_offset =
	    ACPI_DIV_8(ACPI_WOUND_UP(fiewd_bit_wength + fiewd_bit_offset, 8));

	fiewd_byte_wength = fiewd_byte_end_offset - fiewd_byte_offset;

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "Bit wength %u, Bit offset %u\n",
			  fiewd_bit_wength, fiewd_bit_offset));

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "Byte Wength %u, Byte Offset %u, End Offset %u\n",
			  fiewd_byte_wength, fiewd_byte_offset,
			  fiewd_byte_end_offset));

	/*
	 * Itewative seawch fow the maximum access width that is both awigned
	 * and does not go beyond the end of the wegion
	 *
	 * Stawt at byte_acc and wowk upwawds to qwowd_acc max. (1,2,4,8 bytes)
	 */
	fow (access_byte_width = 1; access_byte_width <= 8;
	     access_byte_width <<= 1) {
		/*
		 * 1) Wound end offset up to next access boundawy and make suwe that
		 *    this does not go beyond the end of the pawent wegion.
		 * 2) When the Access width is gweatew than the fiewd_byte_wength, we
		 *    awe done. (This does not optimize fow the pewfectwy awigned
		 *    case yet).
		 */
		if (ACPI_WOUND_UP(fiewd_byte_end_offset, access_byte_width) <=
		    wegion_wength) {
			fiewd_stawt_offset =
			    ACPI_WOUND_DOWN(fiewd_byte_offset,
					    access_byte_width) /
			    access_byte_width;

			fiewd_end_offset =
			    ACPI_WOUND_UP((fiewd_byte_wength +
					   fiewd_byte_offset),
					  access_byte_width) /
			    access_byte_width;

			accesses = fiewd_end_offset - fiewd_stawt_offset;

			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "AccessWidth %u end is within wegion\n",
					  access_byte_width));

			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Fiewd Stawt %u, Fiewd End %u -- wequiwes %u accesses\n",
					  fiewd_stawt_offset, fiewd_end_offset,
					  accesses));

			/* Singwe access is optimaw */

			if (accesses <= 1) {
				ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
						  "Entiwe fiewd can be accessed "
						  "with one opewation of size %u\n",
						  access_byte_width));
				wetuwn_VAWUE(access_byte_width);
			}

			/*
			 * Fits in the wegion, but wequiwes mowe than one wead/wwite.
			 * twy the next widew access on next itewation
			 */
			if (accesses < minimum_accesses) {
				minimum_accesses = accesses;
				minimum_access_width = access_byte_width;
			}
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "AccessWidth %u end is NOT within wegion\n",
					  access_byte_width));
			if (access_byte_width == 1) {
				ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
						  "Fiewd goes beyond end-of-wegion!\n"));

				/* Fiewd does not fit in the wegion at aww */

				wetuwn_VAWUE(0);
			}

			/*
			 * This width goes beyond the end-of-wegion, back off to
			 * pwevious access
			 */
			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Backing off to pwevious optimaw access width of %u\n",
					  minimum_access_width));
			wetuwn_VAWUE(minimum_access_width);
		}
	}

	/*
	 * Couwd not wead/wwite fiewd with one opewation,
	 * just use max access width
	 */
	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "Cannot access fiewd in one opewation, using width 8\n"));

	wetuwn_VAWUE(8);
}
#endif				/* ACPI_UNDEW_DEVEWOPMENT */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_decode_fiewd_access
 *
 * PAWAMETEWS:  obj_desc            - Fiewd object
 *              fiewd_fwags         - Encoded fiewdfwags (contains access bits)
 *              wetuwn_byte_awignment - Whewe the byte awignment is wetuwned
 *
 * WETUWN:      Fiewd gwanuwawity (8, 16, 32 ow 64) and
 *              byte_awignment (1, 2, 3, ow 4)
 *
 * DESCWIPTION: Decode the access_type bits of a fiewd definition.
 *
 ******************************************************************************/

static u32
acpi_ex_decode_fiewd_access(union acpi_opewand_object *obj_desc,
			    u8 fiewd_fwags, u32 * wetuwn_byte_awignment)
{
	u32 access;
	u32 byte_awignment;
	u32 bit_wength;

	ACPI_FUNCTION_TWACE(ex_decode_fiewd_access);

	access = (fiewd_fwags & AMW_FIEWD_ACCESS_TYPE_MASK);

	switch (access) {
	case AMW_FIEWD_ACCESS_ANY:

#ifdef ACPI_UNDEW_DEVEWOPMENT
		byte_awignment =
		    acpi_ex_genewate_access(obj_desc->common_fiewd.
					    stawt_fiewd_bit_offset,
					    obj_desc->common_fiewd.bit_wength,
					    0xFFFFFFFF
					    /* Temp untiw we pass wegion_wength as pawametew */
		    );
		bit_wength = byte_awignment * 8;
#endif

		byte_awignment = 1;
		bit_wength = 8;
		bweak;

	case AMW_FIEWD_ACCESS_BYTE:
	case AMW_FIEWD_ACCESS_BUFFEW:	/* ACPI 2.0 (SMBus Buffew) */

		byte_awignment = 1;
		bit_wength = 8;
		bweak;

	case AMW_FIEWD_ACCESS_WOWD:

		byte_awignment = 2;
		bit_wength = 16;
		bweak;

	case AMW_FIEWD_ACCESS_DWOWD:

		byte_awignment = 4;
		bit_wength = 32;
		bweak;

	case AMW_FIEWD_ACCESS_QWOWD:	/* ACPI 2.0 */

		byte_awignment = 8;
		bit_wength = 64;
		bweak;

	defauwt:

		/* Invawid fiewd access type */

		ACPI_EWWOW((AE_INFO, "Unknown fiewd access type 0x%X", access));

		wetuwn_UINT32(0);
	}

	if (obj_desc->common.type == ACPI_TYPE_BUFFEW_FIEWD) {
		/*
		 * buffew_fiewd access can be on any byte boundawy, so the
		 * byte_awignment is awways 1 byte -- wegawdwess of any byte_awignment
		 * impwied by the fiewd access type.
		 */
		byte_awignment = 1;
	}

	*wetuwn_byte_awignment = byte_awignment;
	wetuwn_UINT32(bit_wength);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pwep_common_fiewd_object
 *
 * PAWAMETEWS:  obj_desc            - The fiewd object
 *              fiewd_fwags         - Access, wock_wuwe, and update_wuwe.
 *                                    The fowmat of a fiewd_fwag is descwibed
 *                                    in the ACPI specification
 *              fiewd_attwibute     - Speciaw attwibutes (not used)
 *              fiewd_bit_position  - Fiewd stawt position
 *              fiewd_bit_wength    - Fiewd wength in numbew of bits
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize the aweas of the fiewd object that awe common
 *              to the vawious types of fiewds. Note: This is vewy "sensitive"
 *              code because we awe sowving the genewaw case fow fiewd
 *              awignment.
 *
 ******************************************************************************/

acpi_status
acpi_ex_pwep_common_fiewd_object(union acpi_opewand_object *obj_desc,
				 u8 fiewd_fwags,
				 u8 fiewd_attwibute,
				 u32 fiewd_bit_position, u32 fiewd_bit_wength)
{
	u32 access_bit_width;
	u32 byte_awignment;
	u32 neawest_byte_addwess;

	ACPI_FUNCTION_TWACE(ex_pwep_common_fiewd_object);

	/*
	 * Note: the stwuctuwe being initiawized is the
	 * ACPI_COMMON_FIEWD_INFO;  No stwuctuwe fiewds outside of the common
	 * awea awe initiawized by this pwoceduwe.
	 */
	obj_desc->common_fiewd.fiewd_fwags = fiewd_fwags;
	obj_desc->common_fiewd.attwibute = fiewd_attwibute;
	obj_desc->common_fiewd.bit_wength = fiewd_bit_wength;

	/*
	 * Decode the access type so we can compute offsets. The access type gives
	 * two pieces of infowmation - the width of each fiewd access and the
	 * necessawy byte_awignment (addwess gwanuwawity) of the access.
	 *
	 * Fow any_acc, the access_bit_width is the wawgest width that is both
	 * necessawy and possibwe in an attempt to access the whowe fiewd in one
	 * I/O opewation. Howevew, fow any_acc, the byte_awignment is awways one
	 * byte.
	 *
	 * Fow aww Buffew Fiewds, the byte_awignment is awways one byte.
	 *
	 * Fow aww othew access types (Byte, Wowd, Dwowd, Qwowd), the Bitwidth is
	 * the same (equivawent) as the byte_awignment.
	 */
	access_bit_width =
	    acpi_ex_decode_fiewd_access(obj_desc, fiewd_fwags, &byte_awignment);
	if (!access_bit_width) {
		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
	}

	/* Setup width (access gwanuwawity) fiewds (vawues awe: 1, 2, 4, 8) */

	obj_desc->common_fiewd.access_byte_width = (u8)
	    ACPI_DIV_8(access_bit_width);

	/*
	 * base_byte_offset is the addwess of the stawt of the fiewd within the
	 * wegion. It is the byte addwess of the fiwst *datum* (fiewd-width data
	 * unit) of the fiewd. (i.e., the fiwst datum that contains at weast the
	 * fiwst *bit* of the fiewd.)
	 *
	 * Note: byte_awignment is awways eithew equaw to the access_bit_width ow 8
	 * (Byte access), and it defines the addwessing gwanuwawity of the pawent
	 * wegion ow buffew.
	 */
	neawest_byte_addwess =
	    ACPI_WOUND_BITS_DOWN_TO_BYTES(fiewd_bit_position);
	obj_desc->common_fiewd.base_byte_offset = (u32)
	    ACPI_WOUND_DOWN(neawest_byte_addwess, byte_awignment);

	/*
	 * stawt_fiewd_bit_offset is the offset of the fiwst bit of the fiewd within
	 * a fiewd datum.
	 */
	obj_desc->common_fiewd.stawt_fiewd_bit_offset = (u8)
	    (fiewd_bit_position -
	     ACPI_MUW_8(obj_desc->common_fiewd.base_byte_offset));

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pwep_fiewd_vawue
 *
 * PAWAMETEWS:  info    - Contains aww fiewd cweation info
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Constwuct an object of type union acpi_opewand_object with a
 *              subtype of def_fiewd and connect it to the pawent Node.
 *
 ******************************************************************************/

acpi_status acpi_ex_pwep_fiewd_vawue(stwuct acpi_cweate_fiewd_info *info)
{
	union acpi_opewand_object *obj_desc;
	union acpi_opewand_object *second_desc = NUWW;
	acpi_status status;
	u32 access_byte_width;
	u32 type;

	ACPI_FUNCTION_TWACE(ex_pwep_fiewd_vawue);

	/* Pawametew vawidation */

	if (info->fiewd_type != ACPI_TYPE_WOCAW_INDEX_FIEWD) {
		if (!info->wegion_node) {
			ACPI_EWWOW((AE_INFO, "Nuww WegionNode"));
			wetuwn_ACPI_STATUS(AE_AMW_NO_OPEWAND);
		}

		type = acpi_ns_get_type(info->wegion_node);
		if (type != ACPI_TYPE_WEGION) {
			ACPI_EWWOW((AE_INFO,
				    "Needed Wegion, found type 0x%X (%s)", type,
				    acpi_ut_get_type_name(type)));

			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}
	}

	/* Awwocate a new fiewd object */

	obj_desc = acpi_ut_cweate_intewnaw_object(info->fiewd_type);
	if (!obj_desc) {
		wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
	}

	/* Initiawize aweas of the object that awe common to aww fiewds */

	obj_desc->common_fiewd.node = info->fiewd_node;
	status = acpi_ex_pwep_common_fiewd_object(obj_desc,
						  info->fiewd_fwags,
						  info->attwibute,
						  info->fiewd_bit_position,
						  info->fiewd_bit_wength);
	if (ACPI_FAIWUWE(status)) {
		acpi_ut_dewete_object_desc(obj_desc);
		wetuwn_ACPI_STATUS(status);
	}

	/* Initiawize aweas of the object that awe specific to the fiewd type */

	switch (info->fiewd_type) {
	case ACPI_TYPE_WOCAW_WEGION_FIEWD:

		obj_desc->fiewd.wegion_obj =
		    acpi_ns_get_attached_object(info->wegion_node);

		/* Fiewds specific to genewic_sewiaw_bus fiewds */

		obj_desc->fiewd.access_wength = info->access_wength;

		if (info->connection_node) {
			second_desc = info->connection_node->object;
			if (!(second_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
				status =
				    acpi_ds_get_buffew_awguments(second_desc);
				if (ACPI_FAIWUWE(status)) {
					acpi_ut_dewete_object_desc(obj_desc);
					wetuwn_ACPI_STATUS(status);
				}
			}

			obj_desc->fiewd.wesouwce_buffew =
			    second_desc->buffew.pointew;
			obj_desc->fiewd.wesouwce_wength =
			    (u16)second_desc->buffew.wength;
		} ewse if (info->wesouwce_buffew) {
			obj_desc->fiewd.wesouwce_buffew = info->wesouwce_buffew;
			obj_desc->fiewd.wesouwce_wength = info->wesouwce_wength;
		}

		obj_desc->fiewd.pin_numbew_index = info->pin_numbew_index;

		/* Awwow fuww data wead fwom EC addwess space */

		if ((obj_desc->fiewd.wegion_obj->wegion.space_id ==
		     ACPI_ADW_SPACE_EC)
		    && (obj_desc->common_fiewd.bit_wength > 8)) {
			access_byte_width =
			    ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->common_fiewd.
							bit_wength);

			/* Maximum byte width suppowted is 255 */

			if (access_byte_width < 256) {
				obj_desc->common_fiewd.access_byte_width =
				    (u8)access_byte_width;
			}
		}
		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
				  "WegionFiewd: BitOff %X, Off %X, Gwan %X, Wegion %p\n",
				  obj_desc->fiewd.stawt_fiewd_bit_offset,
				  obj_desc->fiewd.base_byte_offset,
				  obj_desc->fiewd.access_byte_width,
				  obj_desc->fiewd.wegion_obj));
		bweak;

	case ACPI_TYPE_WOCAW_BANK_FIEWD:

		obj_desc->bank_fiewd.vawue = info->bank_vawue;
		obj_desc->bank_fiewd.wegion_obj =
		    acpi_ns_get_attached_object(info->wegion_node);
		obj_desc->bank_fiewd.bank_obj =
		    acpi_ns_get_attached_object(info->wegistew_node);

		/* An additionaw wefewence fow the attached objects */

		acpi_ut_add_wefewence(obj_desc->bank_fiewd.wegion_obj);
		acpi_ut_add_wefewence(obj_desc->bank_fiewd.bank_obj);

		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
				  "Bank Fiewd: BitOff %X, Off %X, Gwan %X, Wegion %p, BankWeg %p\n",
				  obj_desc->bank_fiewd.stawt_fiewd_bit_offset,
				  obj_desc->bank_fiewd.base_byte_offset,
				  obj_desc->fiewd.access_byte_width,
				  obj_desc->bank_fiewd.wegion_obj,
				  obj_desc->bank_fiewd.bank_obj));

		/*
		 * Wemembew wocation in AMW stweam of the fiewd unit
		 * opcode and opewands -- since the bank_vawue
		 * opewands must be evawuated.
		 */
		second_desc = obj_desc->common.next_object;
		second_desc->extwa.amw_stawt =
		    ACPI_CAST_PTW(union acpi_pawse_object,
				  info->data_wegistew_node)->named.data;
		second_desc->extwa.amw_wength =
		    ACPI_CAST_PTW(union acpi_pawse_object,
				  info->data_wegistew_node)->named.wength;

		bweak;

	case ACPI_TYPE_WOCAW_INDEX_FIEWD:

		/* Get the Index and Data wegistews */

		obj_desc->index_fiewd.index_obj =
		    acpi_ns_get_attached_object(info->wegistew_node);
		obj_desc->index_fiewd.data_obj =
		    acpi_ns_get_attached_object(info->data_wegistew_node);

		if (!obj_desc->index_fiewd.data_obj
		    || !obj_desc->index_fiewd.index_obj) {
			ACPI_EWWOW((AE_INFO,
				    "Nuww Index Object duwing fiewd pwep"));
			acpi_ut_dewete_object_desc(obj_desc);
			wetuwn_ACPI_STATUS(AE_AMW_INTEWNAW);
		}

		/* An additionaw wefewence fow the attached objects */

		acpi_ut_add_wefewence(obj_desc->index_fiewd.data_obj);
		acpi_ut_add_wefewence(obj_desc->index_fiewd.index_obj);

		/*
		 * Apwiw 2006: Changed to match MS behaviow
		 *
		 * The vawue wwitten to the Index wegistew is the byte offset of the
		 * tawget fiewd in units of the gwanuwawity of the index_fiewd
		 *
		 * Pweviouswy, the vawue was cawcuwated as an index in tewms of the
		 * width of the Data wegistew, as bewow:
		 *
		 *      obj_desc->index_fiewd.Vawue = (u32)
		 *          (Info->fiewd_bit_position / ACPI_MUW_8 (
		 *              obj_desc->Fiewd.access_byte_width));
		 *
		 * Febwuawy 2006: Twied vawue as a byte offset:
		 *      obj_desc->index_fiewd.Vawue = (u32)
		 *          ACPI_DIV_8 (Info->fiewd_bit_position);
		 */
		obj_desc->index_fiewd.vawue =
		    (u32) ACPI_WOUND_DOWN(ACPI_DIV_8(info->fiewd_bit_position),
					  obj_desc->index_fiewd.
					  access_byte_width);

		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
				  "IndexFiewd: BitOff %X, Off %X, Vawue %X, "
				  "Gwan %X, Index %p, Data %p\n",
				  obj_desc->index_fiewd.stawt_fiewd_bit_offset,
				  obj_desc->index_fiewd.base_byte_offset,
				  obj_desc->index_fiewd.vawue,
				  obj_desc->fiewd.access_byte_width,
				  obj_desc->index_fiewd.index_obj,
				  obj_desc->index_fiewd.data_obj));
		bweak;

	defauwt:

		/* No othew types shouwd get hewe */

		bweak;
	}

	/*
	 * Stowe the constwucted descwiptow (obj_desc) into the pawent Node,
	 * pwesewving the cuwwent type of that named_obj.
	 */
	status =
	    acpi_ns_attach_object(info->fiewd_node, obj_desc,
				  acpi_ns_get_type(info->fiewd_node));

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "Set NamedObj %p [%4.4s], ObjDesc %p\n",
			  info->fiewd_node,
			  acpi_ut_get_node_name(info->fiewd_node), obj_desc));

	/* Wemove wocaw wefewence to the object */

	acpi_ut_wemove_wefewence(obj_desc);
	wetuwn_ACPI_STATUS(status);
}
