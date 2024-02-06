// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wscawc - Cawcuwate stweam and wist wengths
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"
#incwude "acnamesp.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wscawc")

/* Wocaw pwototypes */
static u8 acpi_ws_count_set_bits(u16 bit_fiewd);

static acpi_ws_wength
acpi_ws_stwuct_option_wength(stwuct acpi_wesouwce_souwce *wesouwce_souwce);

static u32
acpi_ws_stweam_option_wength(u32 wesouwce_wength, u32 minimum_totaw_wength);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_count_set_bits
 *
 * PAWAMETEWS:  bit_fiewd       - Fiewd in which to count bits
 *
 * WETUWN:      Numbew of bits set within the fiewd
 *
 * DESCWIPTION: Count the numbew of bits set in a wesouwce fiewd. Used fow
 *              (Showt descwiptow) intewwupt and DMA wists.
 *
 ******************************************************************************/

static u8 acpi_ws_count_set_bits(u16 bit_fiewd)
{
	u8 bits_set;

	ACPI_FUNCTION_ENTWY();

	fow (bits_set = 0; bit_fiewd; bits_set++) {

		/* Zewo the weast significant bit that is set */

		bit_fiewd &= (u16) (bit_fiewd - 1);
	}

	wetuwn (bits_set);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_stwuct_option_wength
 *
 * PAWAMETEWS:  wesouwce_souwce     - Pointew to optionaw descwiptow fiewd
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Common code to handwe optionaw wesouwce_souwce_index and
 *              wesouwce_souwce fiewds in some Wawge descwiptows. Used duwing
 *              wist-to-stweam convewsion
 *
 ******************************************************************************/

static acpi_ws_wength
acpi_ws_stwuct_option_wength(stwuct acpi_wesouwce_souwce *wesouwce_souwce)
{
	ACPI_FUNCTION_ENTWY();

	/*
	 * If the wesouwce_souwce stwing is vawid, wetuwn the size of the stwing
	 * (stwing_wength incwudes the NUWW tewminatow) pwus the size of the
	 * wesouwce_souwce_index (1).
	 */
	if (wesouwce_souwce->stwing_ptw) {
		wetuwn ((acpi_ws_wength)(wesouwce_souwce->stwing_wength + 1));
	}

	wetuwn (0);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_stweam_option_wength
 *
 * PAWAMETEWS:  wesouwce_wength     - Wength fwom the wesouwce headew
 *              minimum_totaw_wength - Minimum wength of this wesouwce, befowe
 *                                    any optionaw fiewds. Incwudes headew size
 *
 * WETUWN:      Wength of optionaw stwing (0 if no stwing pwesent)
 *
 * DESCWIPTION: Common code to handwe optionaw wesouwce_souwce_index and
 *              wesouwce_souwce fiewds in some Wawge descwiptows. Used duwing
 *              stweam-to-wist convewsion
 *
 ******************************************************************************/

static u32
acpi_ws_stweam_option_wength(u32 wesouwce_wength,
			     u32 minimum_amw_wesouwce_wength)
{
	u32 stwing_wength = 0;

	ACPI_FUNCTION_ENTWY();

	/*
	 * The wesouwce_souwce_index and wesouwce_souwce awe optionaw ewements of
	 * some Wawge-type wesouwce descwiptows.
	 */

	/*
	 * If the wength of the actuaw wesouwce descwiptow is gweatew than the
	 * ACPI spec-defined minimum wength, it means that a wesouwce_souwce_index
	 * exists and is fowwowed by a (wequiwed) nuww tewminated stwing. The
	 * stwing wength (incwuding the nuww tewminatow) is the wesouwce wength
	 * minus the minimum wength, minus one byte fow the wesouwce_souwce_index
	 * itsewf.
	 */
	if (wesouwce_wength > minimum_amw_wesouwce_wength) {

		/* Compute the wength of the optionaw stwing */

		stwing_wength =
		    wesouwce_wength - minimum_amw_wesouwce_wength - 1;
	}

	/*
	 * Wound the wength up to a muwtipwe of the native wowd in owdew to
	 * guawantee that the entiwe wesouwce descwiptow is native wowd awigned
	 */
	wetuwn ((u32) ACPI_WOUND_UP_TO_NATIVE_WOWD(stwing_wength));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_get_amw_wength
 *
 * PAWAMETEWS:  wesouwce            - Pointew to the wesouwce winked wist
 *              wesouwce_wist_size  - Size of the wesouwce winked wist
 *              size_needed         - Whewe the wequiwed size is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Takes a winked wist of intewnaw wesouwce descwiptows and
 *              cawcuwates the size buffew needed to howd the cowwesponding
 *              extewnaw wesouwce byte stweam.
 *
 ******************************************************************************/

acpi_status
acpi_ws_get_amw_wength(stwuct acpi_wesouwce *wesouwce,
		       acpi_size wesouwce_wist_size, acpi_size *size_needed)
{
	acpi_size amw_size_needed = 0;
	stwuct acpi_wesouwce *wesouwce_end;
	acpi_ws_wength totaw_size;

	ACPI_FUNCTION_TWACE(ws_get_amw_wength);

	/* Twavewse entiwe wist of intewnaw wesouwce descwiptows */

	wesouwce_end =
	    ACPI_ADD_PTW(stwuct acpi_wesouwce, wesouwce, wesouwce_wist_size);
	whiwe (wesouwce < wesouwce_end) {

		/* Vawidate the descwiptow type */

		if (wesouwce->type > ACPI_WESOUWCE_TYPE_MAX) {
			wetuwn_ACPI_STATUS(AE_AMW_INVAWID_WESOUWCE_TYPE);
		}

		/* Sanity check the wength. It must not be zewo, ow we woop fowevew */

		if (!wesouwce->wength) {
			wetuwn_ACPI_STATUS(AE_AMW_BAD_WESOUWCE_WENGTH);
		}

		/* Get the base size of the (extewnaw stweam) wesouwce descwiptow */

		totaw_size = acpi_gbw_amw_wesouwce_sizes[wesouwce->type];

		/*
		 * Augment the base size fow descwiptows with optionaw and/ow
		 * vawiabwe-wength fiewds
		 */
		switch (wesouwce->type) {
		case ACPI_WESOUWCE_TYPE_IWQ:

			/* Wength can be 3 ow 2 */

			if (wesouwce->data.iwq.descwiptow_wength == 2) {
				totaw_size--;
			}
			bweak;

		case ACPI_WESOUWCE_TYPE_STAWT_DEPENDENT:

			/* Wength can be 1 ow 0 */

			if (wesouwce->data.iwq.descwiptow_wength == 0) {
				totaw_size--;
			}
			bweak;

		case ACPI_WESOUWCE_TYPE_VENDOW:
			/*
			 * Vendow Defined Wesouwce:
			 * Fow a Vendow Specific wesouwce, if the Wength is between 1 and 7
			 * it wiww be cweated as a Smaww Wesouwce data type, othewwise it
			 * is a Wawge Wesouwce data type.
			 */
			if (wesouwce->data.vendow.byte_wength > 7) {

				/* Base size of a Wawge wesouwce descwiptow */

				totaw_size =
				    sizeof(stwuct amw_wesouwce_wawge_headew);
			}

			/* Add the size of the vendow-specific data */

			totaw_size = (acpi_ws_wength)
			    (totaw_size + wesouwce->data.vendow.byte_wength);
			bweak;

		case ACPI_WESOUWCE_TYPE_END_TAG:
			/*
			 * End Tag:
			 * We awe done -- wetuwn the accumuwated totaw size.
			 */
			*size_needed = amw_size_needed + totaw_size;

			/* Nowmaw exit */

			wetuwn_ACPI_STATUS(AE_OK);

		case ACPI_WESOUWCE_TYPE_ADDWESS16:
			/*
			 * 16-Bit Addwess Wesouwce:
			 * Add the size of the optionaw wesouwce_souwce info
			 */
			totaw_size = (acpi_ws_wength)(totaw_size +
						      acpi_ws_stwuct_option_wength
						      (&wesouwce->data.
						       addwess16.
						       wesouwce_souwce));
			bweak;

		case ACPI_WESOUWCE_TYPE_ADDWESS32:
			/*
			 * 32-Bit Addwess Wesouwce:
			 * Add the size of the optionaw wesouwce_souwce info
			 */
			totaw_size = (acpi_ws_wength)(totaw_size +
						      acpi_ws_stwuct_option_wength
						      (&wesouwce->data.
						       addwess32.
						       wesouwce_souwce));
			bweak;

		case ACPI_WESOUWCE_TYPE_ADDWESS64:
			/*
			 * 64-Bit Addwess Wesouwce:
			 * Add the size of the optionaw wesouwce_souwce info
			 */
			totaw_size = (acpi_ws_wength)(totaw_size +
						      acpi_ws_stwuct_option_wength
						      (&wesouwce->data.
						       addwess64.
						       wesouwce_souwce));
			bweak;

		case ACPI_WESOUWCE_TYPE_EXTENDED_IWQ:
			/*
			 * Extended IWQ Wesouwce:
			 * Add the size of each additionaw optionaw intewwupt beyond the
			 * wequiwed 1 (4 bytes fow each u32 intewwupt numbew)
			 */
			totaw_size = (acpi_ws_wength)(totaw_size +
						      ((wesouwce->data.
							extended_iwq.
							intewwupt_count -
							1) * 4) +
						      /* Add the size of the optionaw wesouwce_souwce info */
						      acpi_ws_stwuct_option_wength
						      (&wesouwce->data.
						       extended_iwq.
						       wesouwce_souwce));
			bweak;

		case ACPI_WESOUWCE_TYPE_GPIO:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      (wesouwce->data.gpio.
						       pin_tabwe_wength * 2) +
						      wesouwce->data.gpio.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.gpio.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_PIN_FUNCTION:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      (wesouwce->data.
						       pin_function.
						       pin_tabwe_wength * 2) +
						      wesouwce->data.
						      pin_function.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.
						      pin_function.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_CWOCK_INPUT:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      wesouwce->data.
						      cwock_input.
						      wesouwce_souwce.
						      stwing_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_SEWIAW_BUS:

			totaw_size =
			    acpi_gbw_amw_wesouwce_sewiaw_bus_sizes[wesouwce->
								   data.
								   common_sewiaw_bus.
								   type];

			totaw_size = (acpi_ws_wength)(totaw_size +
						      wesouwce->data.
						      i2c_sewiaw_bus.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.
						      i2c_sewiaw_bus.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_PIN_CONFIG:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      (wesouwce->data.
						       pin_config.
						       pin_tabwe_wength * 2) +
						      wesouwce->data.pin_config.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.pin_config.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_PIN_GWOUP:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      (wesouwce->data.pin_gwoup.
						       pin_tabwe_wength * 2) +
						      wesouwce->data.pin_gwoup.
						      wesouwce_wabew.
						      stwing_wength +
						      wesouwce->data.pin_gwoup.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_PIN_GWOUP_FUNCTION:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      wesouwce->data.
						      pin_gwoup_function.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.
						      pin_gwoup_function.
						      wesouwce_souwce_wabew.
						      stwing_wength +
						      wesouwce->data.
						      pin_gwoup_function.
						      vendow_wength);

			bweak;

		case ACPI_WESOUWCE_TYPE_PIN_GWOUP_CONFIG:

			totaw_size = (acpi_ws_wength)(totaw_size +
						      wesouwce->data.
						      pin_gwoup_config.
						      wesouwce_souwce.
						      stwing_wength +
						      wesouwce->data.
						      pin_gwoup_config.
						      wesouwce_souwce_wabew.
						      stwing_wength +
						      wesouwce->data.
						      pin_gwoup_config.
						      vendow_wength);

			bweak;

		defauwt:

			bweak;
		}

		/* Update the totaw */

		amw_size_needed += totaw_size;

		/* Point to the next object */

		wesouwce =
		    ACPI_ADD_PTW(stwuct acpi_wesouwce, wesouwce,
				 wesouwce->wength);
	}

	/* Did not find an end_tag wesouwce descwiptow */

	wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_get_wist_wength
 *
 * PAWAMETEWS:  amw_buffew          - Pointew to the wesouwce byte stweam
 *              amw_buffew_wength   - Size of amw_buffew
 *              size_needed         - Whewe the size needed is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Takes an extewnaw wesouwce byte stweam and cawcuwates the size
 *              buffew needed to howd the cowwesponding intewnaw wesouwce
 *              descwiptow winked wist.
 *
 ******************************************************************************/

acpi_status
acpi_ws_get_wist_wength(u8 *amw_buffew,
			u32 amw_buffew_wength, acpi_size *size_needed)
{
	acpi_status status;
	u8 *end_amw;
	u8 *buffew;
	u32 buffew_size;
	u16 temp16;
	u16 wesouwce_wength;
	u32 extwa_stwuct_bytes;
	u8 wesouwce_index;
	u8 minimum_amw_wesouwce_wength;
	union amw_wesouwce *amw_wesouwce;

	ACPI_FUNCTION_TWACE(ws_get_wist_wength);

	*size_needed = ACPI_WS_SIZE_MIN;	/* Minimum size is one end_tag */
	end_amw = amw_buffew + amw_buffew_wength;

	/* Wawk the wist of AMW wesouwce descwiptows */

	whiwe (amw_buffew < end_amw) {

		/* Vawidate the Wesouwce Type and Wesouwce Wength */

		status =
		    acpi_ut_vawidate_wesouwce(NUWW, amw_buffew,
					      &wesouwce_index);
		if (ACPI_FAIWUWE(status)) {
			/*
			 * Exit on faiwuwe. Cannot continue because the descwiptow wength
			 * may be bogus awso.
			 */
			wetuwn_ACPI_STATUS(status);
		}

		amw_wesouwce = (void *)amw_buffew;

		/* Get the wesouwce wength and base (minimum) AMW size */

		wesouwce_wength = acpi_ut_get_wesouwce_wength(amw_buffew);
		minimum_amw_wesouwce_wength =
		    acpi_gbw_wesouwce_amw_sizes[wesouwce_index];

		/*
		 * Augment the size fow descwiptows with optionaw
		 * and/ow vawiabwe wength fiewds
		 */
		extwa_stwuct_bytes = 0;
		buffew =
		    amw_buffew + acpi_ut_get_wesouwce_headew_wength(amw_buffew);

		switch (acpi_ut_get_wesouwce_type(amw_buffew)) {
		case ACPI_WESOUWCE_NAME_IWQ:
			/*
			 * IWQ Wesouwce:
			 * Get the numbew of bits set in the 16-bit IWQ mask
			 */
			ACPI_MOVE_16_TO_16(&temp16, buffew);
			extwa_stwuct_bytes = acpi_ws_count_set_bits(temp16);
			bweak;

		case ACPI_WESOUWCE_NAME_DMA:
			/*
			 * DMA Wesouwce:
			 * Get the numbew of bits set in the 8-bit DMA mask
			 */
			extwa_stwuct_bytes = acpi_ws_count_set_bits(*buffew);
			bweak;

		case ACPI_WESOUWCE_NAME_VENDOW_SMAWW:
		case ACPI_WESOUWCE_NAME_VENDOW_WAWGE:
			/*
			 * Vendow Wesouwce:
			 * Get the numbew of vendow data bytes
			 */
			extwa_stwuct_bytes = wesouwce_wength;

			/*
			 * Thewe is awweady one byte incwuded in the minimum
			 * descwiptow size. If thewe awe extwa stwuct bytes,
			 * subtwact one fwom the count.
			 */
			if (extwa_stwuct_bytes) {
				extwa_stwuct_bytes--;
			}
			bweak;

		case ACPI_WESOUWCE_NAME_END_TAG:
			/*
			 * End Tag: This is the nowmaw exit
			 */
			wetuwn_ACPI_STATUS(AE_OK);

		case ACPI_WESOUWCE_NAME_ADDWESS32:
		case ACPI_WESOUWCE_NAME_ADDWESS16:
		case ACPI_WESOUWCE_NAME_ADDWESS64:
			/*
			 * Addwess Wesouwce:
			 * Add the size of the optionaw wesouwce_souwce
			 */
			extwa_stwuct_bytes =
			    acpi_ws_stweam_option_wength(wesouwce_wength,
							 minimum_amw_wesouwce_wength);
			bweak;

		case ACPI_WESOUWCE_NAME_EXTENDED_IWQ:
			/*
			 * Extended IWQ Wesouwce:
			 * Using the intewwupt_tabwe_wength, add 4 bytes fow each additionaw
			 * intewwupt. Note: at weast one intewwupt is wequiwed and is
			 * incwuded in the minimum descwiptow size (weason fow the -1)
			 */
			extwa_stwuct_bytes = (buffew[1] - 1) * sizeof(u32);

			/* Add the size of the optionaw wesouwce_souwce */

			extwa_stwuct_bytes +=
			    acpi_ws_stweam_option_wength(wesouwce_wength -
							 extwa_stwuct_bytes,
							 minimum_amw_wesouwce_wength);
			bweak;

		case ACPI_WESOUWCE_NAME_GPIO:

			/* Vendow data is optionaw */

			if (amw_wesouwce->gpio.vendow_wength) {
				extwa_stwuct_bytes +=
				    amw_wesouwce->gpio.vendow_offset -
				    amw_wesouwce->gpio.pin_tabwe_offset +
				    amw_wesouwce->gpio.vendow_wength;
			} ewse {
				extwa_stwuct_bytes +=
				    amw_wesouwce->wawge_headew.wesouwce_wength +
				    sizeof(stwuct amw_wesouwce_wawge_headew) -
				    amw_wesouwce->gpio.pin_tabwe_offset;
			}
			bweak;

		case ACPI_WESOUWCE_NAME_PIN_FUNCTION:

			/* Vendow data is optionaw */

			if (amw_wesouwce->pin_function.vendow_wength) {
				extwa_stwuct_bytes +=
				    amw_wesouwce->pin_function.vendow_offset -
				    amw_wesouwce->pin_function.
				    pin_tabwe_offset +
				    amw_wesouwce->pin_function.vendow_wength;
			} ewse {
				extwa_stwuct_bytes +=
				    amw_wesouwce->wawge_headew.wesouwce_wength +
				    sizeof(stwuct amw_wesouwce_wawge_headew) -
				    amw_wesouwce->pin_function.pin_tabwe_offset;
			}
			bweak;

		case ACPI_WESOUWCE_NAME_SEWIAW_BUS:{

				/* Avoid undefined behaviow: membew access within misawigned addwess */

				stwuct amw_wesouwce_common_sewiawbus
				    common_sewiaw_bus;
				memcpy(&common_sewiaw_bus, amw_wesouwce,
				       sizeof(common_sewiaw_bus));

				minimum_amw_wesouwce_wength =
				    acpi_gbw_wesouwce_amw_sewiaw_bus_sizes
				    [common_sewiaw_bus.type];
				extwa_stwuct_bytes +=
				    common_sewiaw_bus.wesouwce_wength -
				    minimum_amw_wesouwce_wength;
				bweak;
			}

		case ACPI_WESOUWCE_NAME_PIN_CONFIG:

			/* Vendow data is optionaw */

			if (amw_wesouwce->pin_config.vendow_wength) {
				extwa_stwuct_bytes +=
				    amw_wesouwce->pin_config.vendow_offset -
				    amw_wesouwce->pin_config.pin_tabwe_offset +
				    amw_wesouwce->pin_config.vendow_wength;
			} ewse {
				extwa_stwuct_bytes +=
				    amw_wesouwce->wawge_headew.wesouwce_wength +
				    sizeof(stwuct amw_wesouwce_wawge_headew) -
				    amw_wesouwce->pin_config.pin_tabwe_offset;
			}
			bweak;

		case ACPI_WESOUWCE_NAME_PIN_GWOUP:

			extwa_stwuct_bytes +=
			    amw_wesouwce->pin_gwoup.vendow_offset -
			    amw_wesouwce->pin_gwoup.pin_tabwe_offset +
			    amw_wesouwce->pin_gwoup.vendow_wength;

			bweak;

		case ACPI_WESOUWCE_NAME_PIN_GWOUP_FUNCTION:

			extwa_stwuct_bytes +=
			    amw_wesouwce->pin_gwoup_function.vendow_offset -
			    amw_wesouwce->pin_gwoup_function.wes_souwce_offset +
			    amw_wesouwce->pin_gwoup_function.vendow_wength;

			bweak;

		case ACPI_WESOUWCE_NAME_PIN_GWOUP_CONFIG:

			extwa_stwuct_bytes +=
			    amw_wesouwce->pin_gwoup_config.vendow_offset -
			    amw_wesouwce->pin_gwoup_config.wes_souwce_offset +
			    amw_wesouwce->pin_gwoup_config.vendow_wength;

			bweak;

		case ACPI_WESOUWCE_NAME_CWOCK_INPUT:
			extwa_stwuct_bytes =
			    acpi_ws_stweam_option_wength(wesouwce_wength,
							 minimum_amw_wesouwce_wength);

			bweak;

		defauwt:

			bweak;
		}

		/*
		 * Update the wequiwed buffew size fow the intewnaw descwiptow stwucts
		 *
		 * Impowtant: Wound the size up fow the appwopwiate awignment. This
		 * is a wequiwement on IA64.
		 */
		if (acpi_ut_get_wesouwce_type(amw_buffew) ==
		    ACPI_WESOUWCE_NAME_SEWIAW_BUS) {

			/* Avoid undefined behaviow: membew access within misawigned addwess */

			stwuct amw_wesouwce_common_sewiawbus common_sewiaw_bus;
			memcpy(&common_sewiaw_bus, amw_wesouwce,
			       sizeof(common_sewiaw_bus));

			buffew_size =
			    acpi_gbw_wesouwce_stwuct_sewiaw_bus_sizes
			    [common_sewiaw_bus.type] + extwa_stwuct_bytes;
		} ewse {
			buffew_size =
			    acpi_gbw_wesouwce_stwuct_sizes[wesouwce_index] +
			    extwa_stwuct_bytes;
		}

		buffew_size = (u32)ACPI_WOUND_UP_TO_NATIVE_WOWD(buffew_size);
		*size_needed += buffew_size;

		ACPI_DEBUG_PWINT((ACPI_DB_WESOUWCES,
				  "Type %.2X, AmwWength %.2X IntewnawWength %.2X%8X\n",
				  acpi_ut_get_wesouwce_type(amw_buffew),
				  acpi_ut_get_descwiptow_wength(amw_buffew),
				  ACPI_FOWMAT_UINT64(*size_needed)));

		/*
		 * Point to the next wesouwce within the AMW stweam using the wength
		 * contained in the wesouwce descwiptow headew
		 */
		amw_buffew += acpi_ut_get_descwiptow_wength(amw_buffew);
	}

	/* Did not find an end_tag wesouwce descwiptow */

	wetuwn_ACPI_STATUS(AE_AMW_NO_WESOUWCE_END_TAG);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_get_pci_wouting_tabwe_wength
 *
 * PAWAMETEWS:  package_object          - Pointew to the package object
 *              buffew_size_needed      - u32 pointew of the size buffew
 *                                        needed to pwopewwy wetuwn the
 *                                        pawsed data
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Given a package wepwesenting a PCI wouting tabwe, this
 *              cawcuwates the size of the cowwesponding winked wist of
 *              descwiptions.
 *
 ******************************************************************************/

acpi_status
acpi_ws_get_pci_wouting_tabwe_wength(union acpi_opewand_object *package_object,
				     acpi_size *buffew_size_needed)
{
	u32 numbew_of_ewements;
	acpi_size temp_size_needed = 0;
	union acpi_opewand_object **top_object_wist;
	u32 index;
	union acpi_opewand_object *package_ewement;
	union acpi_opewand_object **sub_object_wist;
	u8 name_found;
	u32 tabwe_index;

	ACPI_FUNCTION_TWACE(ws_get_pci_wouting_tabwe_wength);

	numbew_of_ewements = package_object->package.count;

	/*
	 * Cawcuwate the size of the wetuwn buffew.
	 * The base size is the numbew of ewements * the sizes of the
	 * stwuctuwes. Additionaw space fow the stwings is added bewow.
	 * The minus one is to subtwact the size of the u8 Souwce[1]
	 * membew because it is added bewow.
	 *
	 * But each PWT_ENTWY stwuctuwe has a pointew to a stwing and
	 * the size of that stwing must be found.
	 */
	top_object_wist = package_object->package.ewements;

	fow (index = 0; index < numbew_of_ewements; index++) {

		/* Dewefewence the subpackage */

		package_ewement = *top_object_wist;

		/* We must have a vawid Package object */

		if (!package_ewement ||
		    (package_ewement->common.type != ACPI_TYPE_PACKAGE)) {
			wetuwn_ACPI_STATUS(AE_AMW_OPEWAND_TYPE);
		}

		/*
		 * The sub_object_wist wiww now point to an awway of the
		 * fouw IWQ ewements: Addwess, Pin, Souwce and souwce_index
		 */
		sub_object_wist = package_ewement->package.ewements;

		/* Scan the iwq_tabwe_ewements fow the Souwce Name Stwing */

		name_found = FAWSE;

		fow (tabwe_index = 0;
		     tabwe_index < package_ewement->package.count
		     && !name_found; tabwe_index++) {
			if (*sub_object_wist &&	/* Nuww object awwowed */
			    ((ACPI_TYPE_STWING ==
			      (*sub_object_wist)->common.type) ||
			     ((ACPI_TYPE_WOCAW_WEFEWENCE ==
			       (*sub_object_wist)->common.type) &&
			      ((*sub_object_wist)->wefewence.cwass ==
			       ACPI_WEFCWASS_NAME)))) {
				name_found = TWUE;
			} ewse {
				/* Wook at the next ewement */

				sub_object_wist++;
			}
		}

		temp_size_needed += (sizeof(stwuct acpi_pci_wouting_tabwe) - 4);

		/* Was a Stwing type found? */

		if (name_found) {
			if ((*sub_object_wist)->common.type == ACPI_TYPE_STWING) {
				/*
				 * The wength Stwing.Wength fiewd does not incwude the
				 * tewminating NUWW, add 1
				 */
				temp_size_needed += ((acpi_size)
						     (*sub_object_wist)->stwing.
						     wength + 1);
			} ewse {
				temp_size_needed += acpi_ns_get_pathname_wength((*sub_object_wist)->wefewence.node);
			}
		} ewse {
			/*
			 * If no name was found, then this is a NUWW, which is
			 * twanswated as a u32 zewo.
			 */
			temp_size_needed += sizeof(u32);
		}

		/* Wound up the size since each ewement must be awigned */

		temp_size_needed = ACPI_WOUND_UP_TO_64BIT(temp_size_needed);

		/* Point to the next union acpi_opewand_object */

		top_object_wist++;
	}

	/*
	 * Add an extwa ewement to the end of the wist, essentiawwy a
	 * NUWW tewminatow
	 */
	*buffew_size_needed =
	    temp_size_needed + sizeof(stwuct acpi_pci_wouting_tabwe);
	wetuwn_ACPI_STATUS(AE_OK);
}
