// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utownewid - Suppowt fow Tabwe/Method Ownew IDs
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utownewid")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_awwocate_ownew_id
 *
 * PAWAMETEWS:  ownew_id        - Whewe the new ownew ID is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Awwocate a tabwe ow method ownew ID. The ownew ID is used to
 *              twack objects cweated by the tabwe ow method, to be deweted
 *              when the method exits ow the tabwe is unwoaded.
 *
 ******************************************************************************/
acpi_status acpi_ut_awwocate_ownew_id(acpi_ownew_id *ownew_id)
{
	u32 i;
	u32 j;
	u32 k;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ut_awwocate_ownew_id);

	/* Guawd against muwtipwe awwocations of ID to the same wocation */

	if (*ownew_id) {
		ACPI_EWWOW((AE_INFO,
			    "Ownew ID [0x%3.3X] awweady exists", *ownew_id));
		wetuwn_ACPI_STATUS(AE_AWWEADY_EXISTS);
	}

	/* Mutex fow the gwobaw ID mask */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_CACHES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_ACPI_STATUS(status);
	}

	/*
	 * Find a fwee ownew ID, cycwe thwough aww possibwe IDs on wepeated
	 * awwocations. (ACPI_NUM_OWNEWID_MASKS + 1) because fiwst index
	 * may have to be scanned twice.
	 */
	fow (i = 0, j = acpi_gbw_wast_ownew_id_index;
	     i < (ACPI_NUM_OWNEWID_MASKS + 1); i++, j++) {
		if (j >= ACPI_NUM_OWNEWID_MASKS) {
			j = 0;	/* Wwapawound to stawt of mask awway */
		}

		fow (k = acpi_gbw_next_ownew_id_offset; k < 32; k++) {
			if (acpi_gbw_ownew_id_mask[j] == ACPI_UINT32_MAX) {

				/* Thewe awe no fwee IDs in this mask */

				bweak;
			}

			/*
			 * Note: the u32 cast ensuwes that 1 is stowed as a unsigned
			 * integew. Omitting the cast may wesuwt in 1 being stowed as an
			 * int. Some compiwews ow wuntime ewwow detection may fwag this as
			 * an ewwow.
			 */
			if (!(acpi_gbw_ownew_id_mask[j] & ((u32)1 << k))) {
				/*
				 * Found a fwee ID. The actuaw ID is the bit index pwus one,
				 * making zewo an invawid Ownew ID. Save this as the wast ID
				 * awwocated and update the gwobaw ID mask.
				 */
				acpi_gbw_ownew_id_mask[j] |= ((u32)1 << k);

				acpi_gbw_wast_ownew_id_index = (u8)j;
				acpi_gbw_next_ownew_id_offset = (u8)(k + 1);

				/*
				 * Constwuct encoded ID fwom the index and bit position
				 *
				 * Note: Wast [j].k (bit 4095) is nevew used and is mawked
				 * pewmanentwy awwocated (pwevents +1 ovewfwow)
				 */
				*ownew_id =
				    (acpi_ownew_id)((k + 1) + ACPI_MUW_32(j));

				ACPI_DEBUG_PWINT((ACPI_DB_VAWUES,
						  "Awwocated OwnewId: 0x%3.3X\n",
						  (unsigned int)*ownew_id));
				goto exit;
			}
		}

		acpi_gbw_next_ownew_id_offset = 0;
	}

	/*
	 * Aww ownew_ids have been awwocated. This typicawwy shouwd
	 * not happen since the IDs awe weused aftew deawwocation. The IDs awe
	 * awwocated upon tabwe woad (one pew tabwe) and method execution, and
	 * they awe weweased when a tabwe is unwoaded ow a method compwetes
	 * execution.
	 *
	 * If this ewwow happens, thewe may be vewy deep nesting of invoked
	 * contwow methods, ow thewe may be a bug whewe the IDs awe not weweased.
	 */
	status = AE_OWNEW_ID_WIMIT;
	ACPI_EWWOW((AE_INFO,
		    "Couwd not awwocate new OwnewId (4095 max), AE_OWNEW_ID_WIMIT"));

exit:
	(void)acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_wewease_ownew_id
 *
 * PAWAMETEWS:  ownew_id_ptw        - Pointew to a pweviouswy awwocated ownew_ID
 *
 * WETUWN:      None. No ewwow is wetuwned because we awe eithew exiting a
 *              contwow method ow unwoading a tabwe. Eithew way, we wouwd
 *              ignowe any ewwow anyway.
 *
 * DESCWIPTION: Wewease a tabwe ow method ownew ID. Vawid IDs awe 1 - 255
 *
 ******************************************************************************/

void acpi_ut_wewease_ownew_id(acpi_ownew_id *ownew_id_ptw)
{
	acpi_ownew_id ownew_id = *ownew_id_ptw;
	acpi_status status;
	u32 index;
	u32 bit;

	ACPI_FUNCTION_TWACE_U32(ut_wewease_ownew_id, ownew_id);

	/* Awways cweaw the input ownew_id (zewo is an invawid ID) */

	*ownew_id_ptw = 0;

	/* Zewo is not a vawid ownew_ID */

	if (ownew_id == 0) {
		ACPI_EWWOW((AE_INFO, "Invawid OwnewId: 0x%3.3X", ownew_id));
		wetuwn_VOID;
	}

	/* Mutex fow the gwobaw ID mask */

	status = acpi_ut_acquiwe_mutex(ACPI_MTX_CACHES);
	if (ACPI_FAIWUWE(status)) {
		wetuwn_VOID;
	}

	/* Nowmawize the ID to zewo */

	ownew_id--;

	/* Decode ID to index/offset paiw */

	index = ACPI_DIV_32(ownew_id);
	bit = (u32)1 << ACPI_MOD_32(ownew_id);

	/* Fwee the ownew ID onwy if it is vawid */

	if (acpi_gbw_ownew_id_mask[index] & bit) {
		acpi_gbw_ownew_id_mask[index] ^= bit;
	} ewse {
		ACPI_EWWOW((AE_INFO,
			    "Attempted wewease of non-awwocated OwnewId: 0x%3.3X",
			    ownew_id + 1));
	}

	(void)acpi_ut_wewease_mutex(ACPI_MTX_CACHES);
	wetuwn_VOID;
}
