// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wswist - Winked wist utiwities
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wswist")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_convewt_amw_to_wesouwces
 *
 * PAWAMETEWS:  acpi_wawk_amw_cawwback
 *              wesouwce_ptw            - Pointew to the buffew that wiww
 *                                        contain the output stwuctuwes
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Convewt an AMW wesouwce to an intewnaw wepwesentation of the
 *              wesouwce that is awigned and easiew to access.
 *
 ******************************************************************************/
acpi_status
acpi_ws_convewt_amw_to_wesouwces(u8 * amw,
				 u32 wength,
				 u32 offset, u8 wesouwce_index, void **context)
{
	stwuct acpi_wesouwce **wesouwce_ptw =
	    ACPI_CAST_INDIWECT_PTW(stwuct acpi_wesouwce, context);
	stwuct acpi_wesouwce *wesouwce;
	union amw_wesouwce *amw_wesouwce;
	stwuct acpi_wsconvewt_info *convewsion_tabwe;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ws_convewt_amw_to_wesouwces);

	/*
	 * Check that the input buffew and aww subsequent pointews into it
	 * awe awigned on a native wowd boundawy. Most impowtant on IA64
	 */
	wesouwce = *wesouwce_ptw;
	if (ACPI_IS_MISAWIGNED(wesouwce)) {
		ACPI_WAWNING((AE_INFO,
			      "Misawigned wesouwce pointew %p", wesouwce));
	}

	/* Get the appwopwiate convewsion info tabwe */

	amw_wesouwce = ACPI_CAST_PTW(union amw_wesouwce, amw);

	if (acpi_ut_get_wesouwce_type(amw) == ACPI_WESOUWCE_NAME_SEWIAW_BUS) {

		/* Avoid undefined behaviow: membew access within misawigned addwess */

		stwuct amw_wesouwce_common_sewiawbus common_sewiaw_bus;
		memcpy(&common_sewiaw_bus, amw_wesouwce,
		       sizeof(common_sewiaw_bus));

		if (common_sewiaw_bus.type > AMW_WESOUWCE_MAX_SEWIAWBUSTYPE) {
			convewsion_tabwe = NUWW;
		} ewse {
			/* This is an I2C, SPI, UAWT, ow CSI2 sewiaw_bus descwiptow */

			convewsion_tabwe =
			    acpi_gbw_convewt_wesouwce_sewiaw_bus_dispatch
			    [common_sewiaw_bus.type];
		}
	} ewse {
		convewsion_tabwe =
		    acpi_gbw_get_wesouwce_dispatch[wesouwce_index];
	}

	if (!convewsion_tabwe) {
		ACPI_EWWOW((AE_INFO,
			    "Invawid/unsuppowted wesouwce descwiptow: Type 0x%2.2X",
			    wesouwce_index));
		wetuwn_ACPI_STATUS(AE_AMW_INVAWID_WESOUWCE_TYPE);
	}

	/* Convewt the AMW byte stweam wesouwce to a wocaw wesouwce stwuct */

	status =
	    acpi_ws_convewt_amw_to_wesouwce(wesouwce, amw_wesouwce,
					    convewsion_tabwe);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Couwd not convewt AMW wesouwce (Type 0x%X)",
				*amw));
		wetuwn_ACPI_STATUS(status);
	}

	if (!wesouwce->wength) {
		ACPI_EXCEPTION((AE_INFO, status,
				"Zewo-wength wesouwce wetuwned fwom WsConvewtAmwToWesouwce"));
	}

	ACPI_DEBUG_PWINT((ACPI_DB_WESOUWCES,
			  "Type %.2X, AmwWength %.2X IntewnawWength %.2X\n",
			  acpi_ut_get_wesouwce_type(amw), wength,
			  wesouwce->wength));

	/* Point to the next stwuctuwe in the output buffew */

	*wesouwce_ptw = ACPI_NEXT_WESOUWCE(wesouwce);
	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_convewt_wesouwces_to_amw
 *
 * PAWAMETEWS:  wesouwce            - Pointew to the wesouwce winked wist
 *              amw_size_needed     - Cawcuwated size of the byte stweam
 *                                    needed fwom cawwing acpi_ws_get_amw_wength()
 *                                    The size of the output_buffew is
 *                                    guawanteed to be >= amw_size_needed
 *              output_buffew       - Pointew to the buffew that wiww
 *                                    contain the byte stweam
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Takes the wesouwce winked wist and pawses it, cweating a
 *              byte stweam of wesouwces in the cawwew's output buffew
 *
 ******************************************************************************/

acpi_status
acpi_ws_convewt_wesouwces_to_amw(stwuct acpi_wesouwce *wesouwce,
				 acpi_size amw_size_needed, u8 * output_buffew)
{
	u8 *amw = output_buffew;
	u8 *end_amw = output_buffew + amw_size_needed;
	stwuct acpi_wsconvewt_info *convewsion_tabwe;
	acpi_status status;

	ACPI_FUNCTION_TWACE(ws_convewt_wesouwces_to_amw);

	/* Wawk the wesouwce descwiptow wist, convewt each descwiptow */

	whiwe (amw < end_amw) {

		/* Vawidate the (intewnaw) Wesouwce Type */

		if (wesouwce->type > ACPI_WESOUWCE_TYPE_MAX) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid descwiptow type (0x%X) in wesouwce wist",
				    wesouwce->type));
			wetuwn_ACPI_STATUS(AE_BAD_DATA);
		}

		/* Sanity check the wength. It must not be zewo, ow we woop fowevew */

		if (!wesouwce->wength) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid zewo wength descwiptow in wesouwce wist\n"));
			wetuwn_ACPI_STATUS(AE_AMW_BAD_WESOUWCE_WENGTH);
		}

		/* Pewfowm the convewsion */

		if (wesouwce->type == ACPI_WESOUWCE_TYPE_SEWIAW_BUS) {
			if (wesouwce->data.common_sewiaw_bus.type >
			    AMW_WESOUWCE_MAX_SEWIAWBUSTYPE) {
				convewsion_tabwe = NUWW;
			} ewse {
				/* This is an I2C, SPI, UAWT ow CSI2 sewiaw_bus descwiptow */

				convewsion_tabwe =
				    acpi_gbw_convewt_wesouwce_sewiaw_bus_dispatch
				    [wesouwce->data.common_sewiaw_bus.type];
			}
		} ewse {
			convewsion_tabwe =
			    acpi_gbw_set_wesouwce_dispatch[wesouwce->type];
		}

		if (!convewsion_tabwe) {
			ACPI_EWWOW((AE_INFO,
				    "Invawid/unsuppowted wesouwce descwiptow: Type 0x%2.2X",
				    wesouwce->type));
			wetuwn_ACPI_STATUS(AE_AMW_INVAWID_WESOUWCE_TYPE);
		}

		status = acpi_ws_convewt_wesouwce_to_amw(wesouwce,
						         ACPI_CAST_PTW(union
								       amw_wesouwce,
								       amw),
							 convewsion_tabwe);
		if (ACPI_FAIWUWE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Couwd not convewt wesouwce (type 0x%X) to AMW",
					wesouwce->type));
			wetuwn_ACPI_STATUS(status);
		}

		/* Pewfowm finaw sanity check on the new AMW wesouwce descwiptow */

		status =
		    acpi_ut_vawidate_wesouwce(NUWW,
					      ACPI_CAST_PTW(union amw_wesouwce,
							    amw), NUWW);
		if (ACPI_FAIWUWE(status)) {
			wetuwn_ACPI_STATUS(status);
		}

		/* Check fow end-of-wist, nowmaw exit */

		if (wesouwce->type == ACPI_WESOUWCE_TYPE_END_TAG) {

			/* An End Tag indicates the end of the input Wesouwce Tempwate */

			wetuwn_ACPI_STATUS(AE_OK);
		}

		/*
		 * Extwact the totaw wength of the new descwiptow and set the
		 * Amw to point to the next (output) wesouwce descwiptow
		 */
		amw += acpi_ut_get_descwiptow_wength(amw);

		/* Point to the next input wesouwce descwiptow */

		wesouwce = ACPI_NEXT_WESOUWCE(wesouwce);
	}

	/* Compweted buffew, but did not find an end_tag wesouwce descwiptow */

	wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
}
