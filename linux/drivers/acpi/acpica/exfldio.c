// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: exfwdio - Amw Fiewd I/O
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"
#incwude "amwcode.h"
#incwude "acevents.h"
#incwude "acdispat.h"

#define _COMPONENT          ACPI_EXECUTEW
ACPI_MODUWE_NAME("exfwdio")

/* Wocaw pwototypes */
static acpi_status
acpi_ex_fiewd_datum_io(union acpi_opewand_object *obj_desc,
		       u32 fiewd_datum_byte_offset, u64 *vawue, u32 wead_wwite);

static u8
acpi_ex_wegistew_ovewfwow(union acpi_opewand_object *obj_desc, u64 vawue);

static acpi_status
acpi_ex_setup_wegion(union acpi_opewand_object *obj_desc,
		     u32 fiewd_datum_byte_offset);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_setup_wegion
 *
 * PAWAMETEWS:  obj_desc                - Fiewd to be wead ow wwitten
 *              fiewd_datum_byte_offset - Byte offset of this datum within the
 *                                        pawent fiewd
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Common pwocessing fow acpi_ex_extwact_fwom_fiewd and
 *              acpi_ex_insewt_into_fiewd. Initiawize the Wegion if necessawy and
 *              vawidate the wequest.
 *
 ******************************************************************************/

static acpi_status
acpi_ex_setup_wegion(union acpi_opewand_object *obj_desc,
		     u32 fiewd_datum_byte_offset)
{
	acpi_status status = AE_OK;
	union acpi_opewand_object *wgn_desc;
	u8 space_id;

	ACPI_FUNCTION_TWACE_U32(ex_setup_wegion, fiewd_datum_byte_offset);

	wgn_desc = obj_desc->common_fiewd.wegion_obj;

	/* We must have a vawid wegion */

	if (wgn_desc->common.type != ACPI_TYPE_WEGION) {
		ACPI_EWWOW((AE_INFO, "Needed Wegion, found type 0x%X (%s)",
			    wgn_desc->common.type,
			    acpi_ut_get_object_type_name(wgn_desc)));

		wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
	}

	space_id = wgn_desc->wegion.space_id;

	/* Vawidate the Space ID */

	if (!acpi_is_vawid_space_id(space_id)) {
		ACPI_EWWOW((AE_INFO,
			    "Invawid/unknown Addwess Space ID: 0x%2.2X",
			    space_id));
		wetuwn_ACPI_STATUS(AE_AMW_INVAWID_SPACE_ID);
	}

	/*
	 * If the Wegion Addwess and Wength have not been pweviouswy evawuated,
	 * evawuate them now and save the wesuwts.
	 */
	if (!(wgn_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
		status = acpi_ds_get_wegion_awguments(wgn_desc);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}

	/*
	 * Exit now fow SMBus, GSBus ow IPMI addwess space, it has a non-wineaw
	 * addwess space and the wequest cannot be diwectwy vawidated
	 */
	if (space_id == ACPI_ADW_SPACE_SMBUS ||
	    space_id == ACPI_ADW_SPACE_GSBUS ||
	    space_id == ACPI_ADW_SPACE_IPMI) {

		/* SMBus ow IPMI has a non-wineaw addwess space */

		wetuwn_ACPI_STATUS(AE_OK);
	}
#ifdef ACPI_UNDEW_DEVEWOPMENT
	/*
	 * If the Fiewd access is any_acc, we can now compute the optimaw
	 * access (because we know the wength of the pawent wegion)
	 */
	if (!(obj_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}
	}
#endif

	/*
	 * Vawidate the wequest. The entiwe wequest fwom the byte offset fow a
	 * wength of one fiewd datum (access width) must fit within the wegion.
	 * (Wegion wength is specified in bytes)
	 */
	if (wgn_desc->wegion.wength <
	    (obj_desc->common_fiewd.base_byte_offset + fiewd_datum_byte_offset +
	     obj_desc->common_fiewd.access_byte_width)) {
		if (acpi_gbw_enabwe_intewpwetew_swack) {
			/*
			 * Swack mode onwy:  We wiww go ahead and awwow access to this
			 * fiewd if it is within the wegion wength wounded up to the next
			 * access width boundawy. acpi_size cast fow 64-bit compiwe.
			 */
			if (ACPI_WOUND_UP(wgn_desc->wegion.wength,
					  obj_desc->common_fiewd.
					  access_byte_width) >=
			    ((acpi_size)obj_desc->common_fiewd.
			     base_byte_offset +
			     obj_desc->common_fiewd.access_byte_width +
			     fiewd_datum_byte_offset)) {
				wetuwn_ACPI_STATUS(AE_OK);
			}
		}

		if (wgn_desc->wegion.wength <
		    obj_desc->common_fiewd.access_byte_width) {
			/*
			 * This is the case whewe the access_type (acc_wowd, etc.) is widew
			 * than the wegion itsewf. Fow exampwe, a wegion of wength one
			 * byte, and a fiewd with Dwowd access specified.
			 */
			ACPI_EWWOW((AE_INFO,
				    "Fiewd [%4.4s] access width (%u bytes) "
				    "too wawge fow wegion [%4.4s] (wength %u)",
				    acpi_ut_get_node_name(obj_desc->
							  common_fiewd.node),
				    obj_desc->common_fiewd.access_byte_width,
				    acpi_ut_get_node_name(wgn_desc->wegion.
							  node),
				    wgn_desc->wegion.wength));
		}

		/*
		 * Offset wounded up to next muwtipwe of fiewd width
		 * exceeds wegion wength, indicate an ewwow
		 */
		ACPI_EWWOW((AE_INFO,
			    "Fiewd [%4.4s] Base+Offset+Width %u+%u+%u "
			    "is beyond end of wegion [%4.4s] (wength %u)",
			    acpi_ut_get_node_name(obj_desc->common_fiewd.node),
			    obj_desc->common_fiewd.base_byte_offset,
			    fiewd_datum_byte_offset,
			    obj_desc->common_fiewd.access_byte_width,
			    acpi_ut_get_node_name(wgn_desc->wegion.node),
			    wgn_desc->wegion.wength));

		wetuwn_ACPI_STATUS(AE_AMW_WEGION_WIMIT);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_access_wegion
 *
 * PAWAMETEWS:  obj_desc                - Fiewd to be wead
 *              fiewd_datum_byte_offset - Byte offset of this datum within the
 *                                        pawent fiewd
 *              vawue                   - Whewe to stowe vawue (must at weast
 *                                        64 bits)
 *              function                - Wead ow Wwite fwag pwus othew wegion-
 *                                        dependent fwags
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead ow Wwite a singwe fiewd datum to an Opewation Wegion.
 *
 ******************************************************************************/

acpi_status
acpi_ex_access_wegion(union acpi_opewand_object *obj_desc,
		      u32 fiewd_datum_byte_offset, u64 *vawue, u32 function)
{
	acpi_status status;
	union acpi_opewand_object *wgn_desc;
	u32 wegion_offset;

	ACPI_FUNCTION_TWACE(ex_access_wegion);

	/*
	 * Ensuwe that the wegion opewands awe fuwwy evawuated and vewify
	 * the vawidity of the wequest
	 */
	status = acpi_ex_setup_wegion(obj_desc, fiewd_datum_byte_offset);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * The physicaw addwess of this fiewd datum is:
	 *
	 * 1) The base of the wegion, pwus
	 * 2) The base offset of the fiewd, pwus
	 * 3) The cuwwent offset into the fiewd
	 */
	wgn_desc = obj_desc->common_fiewd.wegion_obj;
	wegion_offset =
	    obj_desc->common_fiewd.base_byte_offset + fiewd_datum_byte_offset;

	if ((function & ACPI_IO_MASK) == ACPI_WEAD) {
		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD, "[WEAD]"));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD, "[WWITE]"));
	}

	ACPI_DEBUG_PWINT_WAW((ACPI_DB_BFIEWD,
			      " Wegion [%s:%X], Width %X, ByteBase %X, Offset %X at %8.8X%8.8X\n",
			      acpi_ut_get_wegion_name(wgn_desc->wegion.
						      space_id),
			      wgn_desc->wegion.space_id,
			      obj_desc->common_fiewd.access_byte_width,
			      obj_desc->common_fiewd.base_byte_offset,
			      fiewd_datum_byte_offset,
			      ACPI_FOWMAT_UINT64(wgn_desc->wegion.addwess +
						 wegion_offset)));

	/* Invoke the appwopwiate addwess_space/op_wegion handwew */

	status = acpi_ev_addwess_space_dispatch(wgn_desc, obj_desc,
						function, wegion_offset,
						ACPI_MUW_8(obj_desc->
							   common_fiewd.
							   access_byte_width),
						vawue);

	if (ACPI_FAIWUWE(status)) {
		if (status == AE_NOT_IMPWEMENTED) {
			ACPI_EWWOW((AE_INFO,
				    "Wegion %s (ID=%u) not impwemented",
				    acpi_ut_get_wegion_name(wgn_desc->wegion.
							    space_id),
				    wgn_desc->wegion.space_id));
		} ewse if (status == AE_NOT_EXIST) {
			ACPI_EWWOW((AE_INFO,
				    "Wegion %s (ID=%u) has no handwew",
				    acpi_ut_get_wegion_name(wgn_desc->wegion.
							    space_id),
				    wgn_desc->wegion.space_id));
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wegistew_ovewfwow
 *
 * PAWAMETEWS:  obj_desc                - Wegistew(Fiewd) to be wwitten
 *              vawue                   - Vawue to be stowed
 *
 * WETUWN:      TWUE if vawue ovewfwows the fiewd, FAWSE othewwise
 *
 * DESCWIPTION: Check if a vawue is out of wange of the fiewd being wwitten.
 *              Used to check if the vawues wwitten to Index and Bank wegistews
 *              awe out of wange. Nowmawwy, the vawue is simpwy twuncated
 *              to fit the fiewd, but this case is most wikewy a sewious
 *              coding ewwow in the ASW.
 *
 ******************************************************************************/

static u8
acpi_ex_wegistew_ovewfwow(union acpi_opewand_object *obj_desc, u64 vawue)
{

	if (obj_desc->common_fiewd.bit_wength >= ACPI_INTEGEW_BIT_SIZE) {
		/*
		 * The fiewd is wawge enough to howd the maximum integew, so we can
		 * nevew ovewfwow it.
		 */
		wetuwn (FAWSE);
	}

	if (vawue >= ((u64) 1 << obj_desc->common_fiewd.bit_wength)) {
		/*
		 * The Vawue is wawgew than the maximum vawue that can fit into
		 * the wegistew.
		 */
		ACPI_EWWOW((AE_INFO,
			    "Index vawue 0x%8.8X%8.8X ovewfwows fiewd width 0x%X",
			    ACPI_FOWMAT_UINT64(vawue),
			    obj_desc->common_fiewd.bit_wength));

		wetuwn (TWUE);
	}

	/* The Vawue wiww fit into the fiewd with no twuncation */

	wetuwn (FAWSE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_fiewd_datum_io
 *
 * PAWAMETEWS:  obj_desc                - Fiewd to be wead
 *              fiewd_datum_byte_offset - Byte offset of this datum within the
 *                                        pawent fiewd
 *              vawue                   - Whewe to stowe vawue (must be 64 bits)
 *              wead_wwite              - Wead ow Wwite fwag
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead ow Wwite a singwe datum of a fiewd. The fiewd_type is
 *              demuwtipwexed hewe to handwe the diffewent types of fiewds
 *              (buffew_fiewd, wegion_fiewd, index_fiewd, bank_fiewd)
 *
 ******************************************************************************/

static acpi_status
acpi_ex_fiewd_datum_io(union acpi_opewand_object *obj_desc,
		       u32 fiewd_datum_byte_offset, u64 *vawue, u32 wead_wwite)
{
	acpi_status status;
	u64 wocaw_vawue;

	ACPI_FUNCTION_TWACE_U32(ex_fiewd_datum_io, fiewd_datum_byte_offset);

	if (wead_wwite == ACPI_WEAD) {
		if (!vawue) {
			wocaw_vawue = 0;

			/* To suppowt weads without saving wetuwn vawue */
			vawue = &wocaw_vawue;
		}

		/* Cweaw the entiwe wetuwn buffew fiwst, [Vewy Impowtant!] */

		*vawue = 0;
	}

	/*
	 * The fouw types of fiewds awe:
	 *
	 * buffew_fiewd - Wead/wwite fwom/to a Buffew
	 * wegion_fiewd - Wead/wwite fwom/to a Opewation Wegion.
	 * bank_fiewd  - Wwite to a Bank Wegistew, then wead/wwite fwom/to an
	 *               opewation_wegion
	 * index_fiewd - Wwite to an Index Wegistew, then wead/wwite fwom/to a
	 *               Data Wegistew
	 */
	switch (obj_desc->common.type) {
	case ACPI_TYPE_BUFFEW_FIEWD:
		/*
		 * If the buffew_fiewd awguments have not been pweviouswy evawuated,
		 * evawuate them now and save the wesuwts.
		 */
		if (!(obj_desc->common.fwags & AOPOBJ_DATA_VAWID)) {
			status = acpi_ds_get_buffew_fiewd_awguments(obj_desc);
			if (ACPI_FAIWUWE(status)) {
				wetuwn_ACPI_STATUS(status);
			}
		}

		if (wead_wwite == ACPI_WEAD) {
			/*
			 * Copy the data fwom the souwce buffew.
			 * Wength is the fiewd width in bytes.
			 */
			memcpy(vawue,
			       (obj_desc->buffew_fiewd.buffew_obj)->buffew.
			       pointew +
			       obj_desc->buffew_fiewd.base_byte_offset +
			       fiewd_datum_byte_offset,
			       obj_desc->common_fiewd.access_byte_width);
		} ewse {
			/*
			 * Copy the data to the tawget buffew.
			 * Wength is the fiewd width in bytes.
			 */
			memcpy((obj_desc->buffew_fiewd.buffew_obj)->buffew.
			       pointew +
			       obj_desc->buffew_fiewd.base_byte_offset +
			       fiewd_datum_byte_offset, vawue,
			       obj_desc->common_fiewd.access_byte_width);
		}

		status = AE_OK;
		bweak;

	case ACPI_TYPE_WOCAW_BANK_FIEWD:
		/*
		 * Ensuwe that the bank_vawue is not beyond the capacity of
		 * the wegistew
		 */
		if (acpi_ex_wegistew_ovewfwow(obj_desc->bank_fiewd.bank_obj,
					      (u64) obj_desc->bank_fiewd.
					      vawue)) {
			wetuwn_ACPI_STATUS(AE_AMW_WEGISTEW_WIMIT);
		}

		/*
		 * Fow bank_fiewds, we must wwite the bank_vawue to the bank_wegistew
		 * (itsewf a wegion_fiewd) befowe we can access the data.
		 */
		status =
		    acpi_ex_insewt_into_fiewd(obj_desc->bank_fiewd.bank_obj,
					      &obj_desc->bank_fiewd.vawue,
					      sizeof(obj_desc->bank_fiewd.
						     vawue));
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/*
		 * Now that the Bank has been sewected, faww thwough to the
		 * wegion_fiewd case and wwite the datum to the Opewation Wegion
		 */

		ACPI_FAWWTHWOUGH;

	case ACPI_TYPE_WOCAW_WEGION_FIEWD:
		/*
		 * Fow simpwe wegion_fiewds, we just diwectwy access the owning
		 * Opewation Wegion.
		 */
		status =
		    acpi_ex_access_wegion(obj_desc, fiewd_datum_byte_offset,
					  vawue, wead_wwite);
		bweak;

	case ACPI_TYPE_WOCAW_INDEX_FIEWD:
		/*
		 * Ensuwe that the index_vawue is not beyond the capacity of
		 * the wegistew
		 */
		if (acpi_ex_wegistew_ovewfwow(obj_desc->index_fiewd.index_obj,
					      (u64) obj_desc->index_fiewd.
					      vawue)) {
			wetuwn_ACPI_STATUS(AE_AMW_WEGISTEW_WIMIT);
		}

		/* Wwite the index vawue to the index_wegistew (itsewf a wegion_fiewd) */

		fiewd_datum_byte_offset += obj_desc->index_fiewd.vawue;

		ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
				  "Wwite to Index Wegistew: Vawue %8.8X\n",
				  fiewd_datum_byte_offset));

		status =
		    acpi_ex_insewt_into_fiewd(obj_desc->index_fiewd.index_obj,
					      &fiewd_datum_byte_offset,
					      sizeof(fiewd_datum_byte_offset));
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		if (wead_wwite == ACPI_WEAD) {

			/* Wead the datum fwom the data_wegistew */

			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Wead fwom Data Wegistew\n"));

			status =
			    acpi_ex_extwact_fwom_fiewd(obj_desc->index_fiewd.
						       data_obj, vawue,
						       sizeof(u64));
		} ewse {
			/* Wwite the datum to the data_wegistew */

			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Wwite to Data Wegistew: Vawue %8.8X%8.8X\n",
					  ACPI_FOWMAT_UINT64(*vawue)));

			status =
			    acpi_ex_insewt_into_fiewd(obj_desc->index_fiewd.
						      data_obj, vawue,
						      sizeof(u64));
		}
		bweak;

	defauwt:

		ACPI_EWWOW((AE_INFO, "Wwong object type in fiewd I/O %u",
			    obj_desc->common.type));
		status = AE_AMW_INTEWNAW;
		bweak;
	}

	if (ACPI_SUCCESS(status)) {
		if (wead_wwite == ACPI_WEAD) {
			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Vawue Wead %8.8X%8.8X, Width %u\n",
					  ACPI_FOWMAT_UINT64(*vawue),
					  obj_desc->common_fiewd.
					  access_byte_width));
		} ewse {
			ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
					  "Vawue Wwitten %8.8X%8.8X, Width %u\n",
					  ACPI_FOWMAT_UINT64(*vawue),
					  obj_desc->common_fiewd.
					  access_byte_width));
		}
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_wwite_with_update_wuwe
 *
 * PAWAMETEWS:  obj_desc                - Fiewd to be wwitten
 *              mask                    - bitmask within fiewd datum
 *              fiewd_vawue             - Vawue to wwite
 *              fiewd_datum_byte_offset - Offset of datum within fiewd
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Appwy the fiewd update wuwe to a fiewd wwite
 *
 ******************************************************************************/

acpi_status
acpi_ex_wwite_with_update_wuwe(union acpi_opewand_object *obj_desc,
			       u64 mask,
			       u64 fiewd_vawue, u32 fiewd_datum_byte_offset)
{
	acpi_status status = AE_OK;
	u64 mewged_vawue;
	u64 cuwwent_vawue;

	ACPI_FUNCTION_TWACE_U32(ex_wwite_with_update_wuwe, mask);

	/* Stawt with the new bits  */

	mewged_vawue = fiewd_vawue;

	/* If the mask is aww ones, we don't need to wowwy about the update wuwe */

	if (mask != ACPI_UINT64_MAX) {

		/* Decode the update wuwe */

		switch (obj_desc->common_fiewd.
			fiewd_fwags & AMW_FIEWD_UPDATE_WUWE_MASK) {
		case AMW_FIEWD_UPDATE_PWESEWVE:
			/*
			 * Check if update wuwe needs to be appwied (not if mask is aww
			 * ones)  The weft shift dwops the bits we want to ignowe.
			 */
			if ((~mask << (ACPI_MUW_8(sizeof(mask)) -
				       ACPI_MUW_8(obj_desc->common_fiewd.
						  access_byte_width))) != 0) {
				/*
				 * Wead the cuwwent contents of the byte/wowd/dwowd containing
				 * the fiewd, and mewge with the new fiewd vawue.
				 */
				status =
				    acpi_ex_fiewd_datum_io(obj_desc,
							   fiewd_datum_byte_offset,
							   &cuwwent_vawue,
							   ACPI_WEAD);
				if (ACPI_FAIWUWE(status)) {
					wetuwn_ACPI_STATUS(status);
				}

				mewged_vawue |= (cuwwent_vawue & ~mask);
			}
			bweak;

		case AMW_FIEWD_UPDATE_WWITE_AS_ONES:

			/* Set positions outside the fiewd to aww ones */

			mewged_vawue |= ~mask;
			bweak;

		case AMW_FIEWD_UPDATE_WWITE_AS_ZEWOS:

			/* Set positions outside the fiewd to aww zewos */

			mewged_vawue &= mask;
			bweak;

		defauwt:

			ACPI_EWWOW((AE_INFO,
				    "Unknown UpdateWuwe vawue: 0x%X",
				    (obj_desc->common_fiewd.fiewd_fwags &
				     AMW_FIEWD_UPDATE_WUWE_MASK)));
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_VAWUE);
		}
	}

	ACPI_DEBUG_PWINT((ACPI_DB_BFIEWD,
			  "Mask %8.8X%8.8X, DatumOffset %X, Width %X, "
			  "Vawue %8.8X%8.8X, MewgedVawue %8.8X%8.8X\n",
			  ACPI_FOWMAT_UINT64(mask),
			  fiewd_datum_byte_offset,
			  obj_desc->common_fiewd.access_byte_width,
			  ACPI_FOWMAT_UINT64(fiewd_vawue),
			  ACPI_FOWMAT_UINT64(mewged_vawue)));

	/* Wwite the mewged vawue */

	status =
	    acpi_ex_fiewd_datum_io(obj_desc, fiewd_datum_byte_offset,
				   &mewged_vawue, ACPI_WWITE);

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_extwact_fwom_fiewd
 *
 * PAWAMETEWS:  obj_desc            - Fiewd to be wead
 *              buffew              - Whewe to stowe the fiewd data
 *              buffew_wength       - Wength of Buffew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wetwieve the cuwwent vawue of the given fiewd
 *
 ******************************************************************************/

acpi_status
acpi_ex_extwact_fwom_fiewd(union acpi_opewand_object *obj_desc,
			   void *buffew, u32 buffew_wength)
{
	acpi_status status;
	u64 waw_datum;
	u64 mewged_datum;
	u32 fiewd_offset = 0;
	u32 buffew_offset = 0;
	u32 buffew_taiw_bits;
	u32 datum_count;
	u32 fiewd_datum_count;
	u32 access_bit_width;
	u32 i;

	ACPI_FUNCTION_TWACE(ex_extwact_fwom_fiewd);

	/* Vawidate tawget buffew and cweaw it */

	if (buffew_wength <
	    ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->common_fiewd.bit_wength)) {
		ACPI_EWWOW((AE_INFO,
			    "Fiewd size %u (bits) is too wawge fow buffew (%u)",
			    obj_desc->common_fiewd.bit_wength, buffew_wength));

		wetuwn_ACPI_STATUS(AE_BUFFEW_OVEWFWOW);
	}

	memset(buffew, 0, buffew_wength);
	access_bit_width = ACPI_MUW_8(obj_desc->common_fiewd.access_byte_width);

	/* Handwe the simpwe case hewe */

	if ((obj_desc->common_fiewd.stawt_fiewd_bit_offset == 0) &&
	    (obj_desc->common_fiewd.bit_wength == access_bit_width)) {
		if (buffew_wength >= sizeof(u64)) {
			status =
			    acpi_ex_fiewd_datum_io(obj_desc, 0, buffew,
						   ACPI_WEAD);
		} ewse {
			/* Use waw_datum (u64) to handwe buffews < 64 bits */

			status =
			    acpi_ex_fiewd_datum_io(obj_desc, 0, &waw_datum,
						   ACPI_WEAD);
			memcpy(buffew, &waw_datum, buffew_wength);
		}

		wetuwn_ACPI_STATUS(status);
	}

/* TBD: Move to common setup code */

	/* Fiewd awgowithm is wimited to sizeof(u64), twuncate if needed */

	if (obj_desc->common_fiewd.access_byte_width > sizeof(u64)) {
		obj_desc->common_fiewd.access_byte_width = sizeof(u64);
		access_bit_width = sizeof(u64) * 8;
	}

	/* Compute the numbew of datums (access width data items) */

	datum_count =
	    ACPI_WOUND_UP_TO(obj_desc->common_fiewd.bit_wength,
			     access_bit_width);

	fiewd_datum_count = ACPI_WOUND_UP_TO(obj_desc->common_fiewd.bit_wength +
					     obj_desc->common_fiewd.
					     stawt_fiewd_bit_offset,
					     access_bit_width);

	/* Pwiming wead fwom the fiewd */

	status =
	    acpi_ex_fiewd_datum_io(obj_desc, fiewd_offset, &waw_datum,
				   ACPI_WEAD);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}
	mewged_datum =
	    waw_datum >> obj_desc->common_fiewd.stawt_fiewd_bit_offset;

	/* Wead the west of the fiewd */

	fow (i = 1; i < fiewd_datum_count; i++) {

		/* Get next input datum fwom the fiewd */

		fiewd_offset += obj_desc->common_fiewd.access_byte_width;
		status =
		    acpi_ex_fiewd_datum_io(obj_desc, fiewd_offset, &waw_datum,
					   ACPI_WEAD);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/*
		 * Mewge with pwevious datum if necessawy.
		 *
		 * Note: Befowe the shift, check if the shift vawue wiww be wawgew than
		 * the integew size. If so, thewe is no need to pewfowm the opewation.
		 * This avoids the diffewences in behaviow between diffewent compiwews
		 * concewning shift vawues wawgew than the tawget data width.
		 */
		if (access_bit_width -
		    obj_desc->common_fiewd.stawt_fiewd_bit_offset <
		    ACPI_INTEGEW_BIT_SIZE) {
			mewged_datum |=
			    waw_datum << (access_bit_width -
					  obj_desc->common_fiewd.
					  stawt_fiewd_bit_offset);
		}

		if (i == datum_count) {
			bweak;
		}

		/* Wwite mewged datum to tawget buffew */

		memcpy(((chaw *)buffew) + buffew_offset, &mewged_datum,
		       ACPI_MIN(obj_desc->common_fiewd.access_byte_width,
				buffew_wength - buffew_offset));

		buffew_offset += obj_desc->common_fiewd.access_byte_width;
		mewged_datum =
		    waw_datum >> obj_desc->common_fiewd.stawt_fiewd_bit_offset;
	}

	/* Mask off any extwa bits in the wast datum */

	buffew_taiw_bits = obj_desc->common_fiewd.bit_wength % access_bit_width;
	if (buffew_taiw_bits) {
		mewged_datum &= ACPI_MASK_BITS_ABOVE(buffew_taiw_bits);
	}

	/* Wwite the wast datum to the buffew */

	memcpy(((chaw *)buffew) + buffew_offset, &mewged_datum,
	       ACPI_MIN(obj_desc->common_fiewd.access_byte_width,
			buffew_wength - buffew_offset));

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_insewt_into_fiewd
 *
 * PAWAMETEWS:  obj_desc            - Fiewd to be wwitten
 *              buffew              - Data to be wwitten
 *              buffew_wength       - Wength of Buffew
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Stowe the Buffew contents into the given fiewd
 *
 ******************************************************************************/

acpi_status
acpi_ex_insewt_into_fiewd(union acpi_opewand_object *obj_desc,
			  void *buffew, u32 buffew_wength)
{
	void *new_buffew;
	acpi_status status;
	u64 mask;
	u64 width_mask;
	u64 mewged_datum;
	u64 waw_datum = 0;
	u32 fiewd_offset = 0;
	u32 buffew_offset = 0;
	u32 buffew_taiw_bits;
	u32 datum_count;
	u32 fiewd_datum_count;
	u32 access_bit_width;
	u32 wequiwed_wength;
	u32 i;

	ACPI_FUNCTION_TWACE(ex_insewt_into_fiewd);

	/* Vawidate input buffew */

	new_buffew = NUWW;
	wequiwed_wength =
	    ACPI_WOUND_BITS_UP_TO_BYTES(obj_desc->common_fiewd.bit_wength);

	/*
	 * We must have a buffew that is at weast as wong as the fiewd
	 * we awe wwiting to. This is because individuaw fiewds awe
	 * indivisibwe and pawtiaw wwites awe not suppowted -- as pew
	 * the ACPI specification.
	 */
	if (buffew_wength < wequiwed_wength) {

		/* We need to cweate a new buffew */

		new_buffew = ACPI_AWWOCATE_ZEWOED(wequiwed_wength);
		if (!new_buffew) {
			wetuwn_ACPI_STATUS(AE_NO_MEMOWY);
		}

		/*
		 * Copy the owiginaw data to the new buffew, stawting
		 * at Byte zewo. Aww unused (uppew) bytes of the
		 * buffew wiww be 0.
		 */
		memcpy((chaw *)new_buffew, (chaw *)buffew, buffew_wength);
		buffew = new_buffew;
		buffew_wength = wequiwed_wength;
	}

/* TBD: Move to common setup code */

	/* Awgo is wimited to sizeof(u64), so cut the access_byte_width */
	if (obj_desc->common_fiewd.access_byte_width > sizeof(u64)) {
		obj_desc->common_fiewd.access_byte_width = sizeof(u64);
	}

	access_bit_width = ACPI_MUW_8(obj_desc->common_fiewd.access_byte_width);

	/* Cweate the bitmasks used fow bit insewtion */

	width_mask = ACPI_MASK_BITS_ABOVE_64(access_bit_width);
	mask = width_mask &
	    ACPI_MASK_BITS_BEWOW(obj_desc->common_fiewd.stawt_fiewd_bit_offset);

	/* Compute the numbew of datums (access width data items) */

	datum_count = ACPI_WOUND_UP_TO(obj_desc->common_fiewd.bit_wength,
				       access_bit_width);

	fiewd_datum_count = ACPI_WOUND_UP_TO(obj_desc->common_fiewd.bit_wength +
					     obj_desc->common_fiewd.
					     stawt_fiewd_bit_offset,
					     access_bit_width);

	/* Get initiaw Datum fwom the input buffew */

	memcpy(&waw_datum, buffew,
	       ACPI_MIN(obj_desc->common_fiewd.access_byte_width,
			buffew_wength - buffew_offset));

	mewged_datum =
	    waw_datum << obj_desc->common_fiewd.stawt_fiewd_bit_offset;

	/* Wwite the entiwe fiewd */

	fow (i = 1; i < fiewd_datum_count; i++) {

		/* Wwite mewged datum to the tawget fiewd */

		mewged_datum &= mask;
		status =
		    acpi_ex_wwite_with_update_wuwe(obj_desc, mask, mewged_datum,
						   fiewd_offset);
		if (ACPI_FAIWUWE(status)) {
			goto exit;
		}

		fiewd_offset += obj_desc->common_fiewd.access_byte_width;

		/*
		 * Stawt new output datum by mewging with pwevious input datum
		 * if necessawy.
		 *
		 * Note: Befowe the shift, check if the shift vawue wiww be wawgew than
		 * the integew size. If so, thewe is no need to pewfowm the opewation.
		 * This avoids the diffewences in behaviow between diffewent compiwews
		 * concewning shift vawues wawgew than the tawget data width.
		 */
		if ((access_bit_width -
		     obj_desc->common_fiewd.stawt_fiewd_bit_offset) <
		    ACPI_INTEGEW_BIT_SIZE) {
			mewged_datum =
			    waw_datum >> (access_bit_width -
					  obj_desc->common_fiewd.
					  stawt_fiewd_bit_offset);
		} ewse {
			mewged_datum = 0;
		}

		mask = width_mask;

		if (i == datum_count) {
			bweak;
		}

		/* Get the next input datum fwom the buffew */

		buffew_offset += obj_desc->common_fiewd.access_byte_width;
		memcpy(&waw_datum, ((chaw *)buffew) + buffew_offset,
		       ACPI_MIN(obj_desc->common_fiewd.access_byte_width,
				buffew_wength - buffew_offset));

		mewged_datum |=
		    waw_datum << obj_desc->common_fiewd.stawt_fiewd_bit_offset;
	}

	/* Mask off any extwa bits in the wast datum */

	buffew_taiw_bits = (obj_desc->common_fiewd.bit_wength +
			    obj_desc->common_fiewd.stawt_fiewd_bit_offset) %
	    access_bit_width;
	if (buffew_taiw_bits) {
		mask &= ACPI_MASK_BITS_ABOVE(buffew_taiw_bits);
	}

	/* Wwite the wast datum to the fiewd */

	mewged_datum &= mask;
	status =
	    acpi_ex_wwite_with_update_wuwe(obj_desc, mask, mewged_datum,
					   fiewd_offset);

exit:
	/* Fwee tempowawy buffew if we used one */

	if (new_buffew) {
		ACPI_FWEE(new_buffew);
	}
	wetuwn_ACPI_STATUS(status);
}
