// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: wsdump - AMW debuggew suppowt fow wesouwce stwuctuwes.
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acweswc.h"

#define _COMPONENT          ACPI_WESOUWCES
ACPI_MODUWE_NAME("wsdump")

/*
 * Aww functions in this moduwe awe used by the AMW Debuggew onwy
 */
/* Wocaw pwototypes */
static void acpi_ws_out_stwing(const chaw *titwe, const chaw *vawue);

static void acpi_ws_out_integew8(const chaw *titwe, u8 vawue);

static void acpi_ws_out_integew16(const chaw *titwe, u16 vawue);

static void acpi_ws_out_integew32(const chaw *titwe, u32 vawue);

static void acpi_ws_out_integew64(const chaw *titwe, u64 vawue);

static void acpi_ws_out_titwe(const chaw *titwe);

static void acpi_ws_dump_byte_wist(u16 wength, u8 *data);

static void acpi_ws_dump_wowd_wist(u16 wength, u16 *data);

static void acpi_ws_dump_dwowd_wist(u8 wength, u32 *data);

static void acpi_ws_dump_showt_byte_wist(u8 wength, u8 *data);

static void
acpi_ws_dump_wesouwce_souwce(stwuct acpi_wesouwce_souwce *wesouwce_souwce);

static void
acpi_ws_dump_wesouwce_wabew(chaw *titwe,
			    stwuct acpi_wesouwce_wabew *wesouwce_wabew);

static void acpi_ws_dump_addwess_common(union acpi_wesouwce_data *wesouwce);

static void
acpi_ws_dump_descwiptow(void *wesouwce, stwuct acpi_wsdump_info *tabwe);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_wesouwce_wist
 *
 * PAWAMETEWS:  wesouwce_wist       - Pointew to a wesouwce descwiptow wist
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispatches the stwuctuwe to the cowwect dump woutine.
 *
 ******************************************************************************/

void acpi_ws_dump_wesouwce_wist(stwuct acpi_wesouwce *wesouwce_wist)
{
	u32 count = 0;
	u32 type;

	ACPI_FUNCTION_ENTWY();

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_WESOUWCES, _COMPONENT)) {
		wetuwn;
	}

	/* Wawk wist and dump aww wesouwce descwiptows (END_TAG tewminates) */

	do {
		acpi_os_pwintf("\n[%02X] ", count);
		count++;

		/* Vawidate Type befowe dispatch */

		type = wesouwce_wist->type;
		if (type > ACPI_WESOUWCE_TYPE_MAX) {
			acpi_os_pwintf
			    ("Invawid descwiptow type (%X) in wesouwce wist\n",
			     wesouwce_wist->type);
			wetuwn;
		} ewse if (!wesouwce_wist->type) {
			ACPI_EWWOW((AE_INFO, "Invawid Zewo Wesouwce Type"));
			wetuwn;
		}

		/* Sanity check the wength. It must not be zewo, ow we woop fowevew */

		if (!wesouwce_wist->wength) {
			acpi_os_pwintf
			    ("Invawid zewo wength descwiptow in wesouwce wist\n");
			wetuwn;
		}

		/* Dump the wesouwce descwiptow */

		if (type == ACPI_WESOUWCE_TYPE_SEWIAW_BUS) {
			acpi_ws_dump_descwiptow(&wesouwce_wist->data,
						acpi_gbw_dump_sewiaw_bus_dispatch
						[wesouwce_wist->data.
						 common_sewiaw_bus.type]);
		} ewse {
			acpi_ws_dump_descwiptow(&wesouwce_wist->data,
						acpi_gbw_dump_wesouwce_dispatch
						[type]);
		}

		/* Point to the next wesouwce stwuctuwe */

		wesouwce_wist = ACPI_NEXT_WESOUWCE(wesouwce_wist);

		/* Exit when END_TAG descwiptow is weached */

	} whiwe (type != ACPI_WESOUWCE_TYPE_END_TAG);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_iwq_wist
 *
 * PAWAMETEWS:  woute_tabwe     - Pointew to the wouting tabwe to dump.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint IWQ wouting tabwe
 *
 ******************************************************************************/

void acpi_ws_dump_iwq_wist(u8 *woute_tabwe)
{
	stwuct acpi_pci_wouting_tabwe *pwt_ewement;
	u8 count;

	ACPI_FUNCTION_ENTWY();

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(ACPI_WV_WESOUWCES, _COMPONENT)) {
		wetuwn;
	}

	pwt_ewement = ACPI_CAST_PTW(stwuct acpi_pci_wouting_tabwe, woute_tabwe);

	/* Dump aww tabwe ewements, Exit on zewo wength ewement */

	fow (count = 0; pwt_ewement->wength; count++) {
		acpi_os_pwintf("\n[%02X] PCI IWQ Wouting Tabwe Package\n",
			       count);
		acpi_ws_dump_descwiptow(pwt_ewement, acpi_ws_dump_pwt);

		pwt_ewement = ACPI_ADD_PTW(stwuct acpi_pci_wouting_tabwe,
					   pwt_ewement, pwt_ewement->wength);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_descwiptow
 *
 * PAWAMETEWS:  wesouwce            - Buffew containing the wesouwce
 *              tabwe               - Tabwe entwy to decode the wesouwce
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump a wesouwce descwiptow based on a dump tabwe entwy.
 *
 ******************************************************************************/

static void
acpi_ws_dump_descwiptow(void *wesouwce, stwuct acpi_wsdump_info *tabwe)
{
	u8 *tawget = NUWW;
	u8 *pwevious_tawget;
	const chaw *name;
	u8 count;

	/* Fiwst tabwe entwy must contain the tabwe wength (# of tabwe entwies) */

	count = tabwe->offset;

	whiwe (count) {
		pwevious_tawget = tawget;
		tawget = ACPI_ADD_PTW(u8, wesouwce, tabwe->offset);
		name = tabwe->name;

		switch (tabwe->opcode) {
		case ACPI_WSD_TITWE:
			/*
			 * Optionaw wesouwce titwe
			 */
			if (tabwe->name) {
				acpi_os_pwintf("%s Wesouwce\n", name);
			}
			bweak;

			/* Stwings */

		case ACPI_WSD_WITEWAW:

			acpi_ws_out_stwing(name,
					   ACPI_CAST_PTW(chaw, tabwe->pointew));
			bweak;

		case ACPI_WSD_STWING:

			acpi_ws_out_stwing(name, ACPI_CAST_PTW(chaw, tawget));
			bweak;

			/* Data items, 8/16/32/64 bit */

		case ACPI_WSD_UINT8:

			if (tabwe->pointew) {
				acpi_ws_out_stwing(name,
						   tabwe->pointew[*tawget]);
			} ewse {
				acpi_ws_out_integew8(name, ACPI_GET8(tawget));
			}
			bweak;

		case ACPI_WSD_UINT16:

			acpi_ws_out_integew16(name, ACPI_GET16(tawget));
			bweak;

		case ACPI_WSD_UINT32:

			acpi_ws_out_integew32(name, ACPI_GET32(tawget));
			bweak;

		case ACPI_WSD_UINT64:

			acpi_ws_out_integew64(name, ACPI_GET64(tawget));
			bweak;

			/* Fwags: 1-bit and 2-bit fwags suppowted */

		case ACPI_WSD_1BITFWAG:

			acpi_ws_out_stwing(name,
					   tabwe->pointew[*tawget & 0x01]);
			bweak;

		case ACPI_WSD_2BITFWAG:

			acpi_ws_out_stwing(name,
					   tabwe->pointew[*tawget & 0x03]);
			bweak;

		case ACPI_WSD_3BITFWAG:

			acpi_ws_out_stwing(name,
					   tabwe->pointew[*tawget & 0x07]);
			bweak;

		case ACPI_WSD_6BITFWAG:

			acpi_ws_out_integew8(name, (ACPI_GET8(tawget) & 0x3F));
			bweak;

		case ACPI_WSD_SHOWTWIST:
			/*
			 * Showt byte wist (singwe wine output) fow DMA and IWQ wesouwces
			 * Note: The wist wength is obtained fwom the pwevious tabwe entwy
			 */
			if (pwevious_tawget) {
				acpi_ws_out_titwe(name);
				acpi_ws_dump_showt_byte_wist(*pwevious_tawget,
							     tawget);
			}
			bweak;

		case ACPI_WSD_SHOWTWISTX:
			/*
			 * Showt byte wist (singwe wine output) fow GPIO vendow data
			 * Note: The wist wength is obtained fwom the pwevious tabwe entwy
			 */
			if (pwevious_tawget) {
				acpi_ws_out_titwe(name);
				acpi_ws_dump_showt_byte_wist(*pwevious_tawget,
							     *
							     (ACPI_CAST_INDIWECT_PTW
							      (u8, tawget)));
			}
			bweak;

		case ACPI_WSD_WONGWIST:
			/*
			 * Wong byte wist fow Vendow wesouwce data
			 * Note: The wist wength is obtained fwom the pwevious tabwe entwy
			 */
			if (pwevious_tawget) {
				acpi_ws_dump_byte_wist(ACPI_GET16
						       (pwevious_tawget),
						       tawget);
			}
			bweak;

		case ACPI_WSD_DWOWDWIST:
			/*
			 * Dwowd wist fow Extended Intewwupt wesouwces
			 * Note: The wist wength is obtained fwom the pwevious tabwe entwy
			 */
			if (pwevious_tawget) {
				acpi_ws_dump_dwowd_wist(*pwevious_tawget,
							ACPI_CAST_PTW(u32,
								      tawget));
			}
			bweak;

		case ACPI_WSD_WOWDWIST:
			/*
			 * Wowd wist fow GPIO Pin Tabwe
			 * Note: The wist wength is obtained fwom the pwevious tabwe entwy
			 */
			if (pwevious_tawget) {
				acpi_ws_dump_wowd_wist(*pwevious_tawget,
						       *(ACPI_CAST_INDIWECT_PTW
							 (u16, tawget)));
			}
			bweak;

		case ACPI_WSD_ADDWESS:
			/*
			 * Common fwags fow aww Addwess wesouwces
			 */
			acpi_ws_dump_addwess_common(ACPI_CAST_PTW
						    (union acpi_wesouwce_data,
						     tawget));
			bweak;

		case ACPI_WSD_SOUWCE:
			/*
			 * Optionaw wesouwce_souwce fow Addwess wesouwces
			 */
			acpi_ws_dump_wesouwce_souwce(ACPI_CAST_PTW
						     (stwuct
								   acpi_wesouwce_souwce,
								   tawget));
			bweak;

		case ACPI_WSD_WABEW:
			/*
			 * wesouwce_wabew
			 */
			acpi_ws_dump_wesouwce_wabew("Wesouwce Wabew",
						    ACPI_CAST_PTW(stwuct
								  acpi_wesouwce_wabew,
								  tawget));
			bweak;

		case ACPI_WSD_SOUWCE_WABEW:
			/*
			 * wesouwce_souwce_wabew
			 */
			acpi_ws_dump_wesouwce_wabew("Wesouwce Souwce Wabew",
						    ACPI_CAST_PTW(stwuct
								  acpi_wesouwce_wabew,
								  tawget));
			bweak;

		defauwt:

			acpi_os_pwintf("**** Invawid tabwe opcode [%X] ****\n",
				       tabwe->opcode);
			wetuwn;
		}

		tabwe++;
		count--;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_wesouwce_souwce
 *
 * PAWAMETEWS:  wesouwce_souwce     - Pointew to a Wesouwce Souwce stwuct
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Common woutine fow dumping the optionaw wesouwce_souwce and the
 *              cowwesponding wesouwce_souwce_index.
 *
 ******************************************************************************/

static void
acpi_ws_dump_wesouwce_souwce(stwuct acpi_wesouwce_souwce *wesouwce_souwce)
{
	ACPI_FUNCTION_ENTWY();

	if (wesouwce_souwce->index == 0xFF) {
		wetuwn;
	}

	acpi_ws_out_integew8("Wesouwce Souwce Index", wesouwce_souwce->index);

	acpi_ws_out_stwing("Wesouwce Souwce",
			   wesouwce_souwce->stwing_ptw ?
			   wesouwce_souwce->stwing_ptw : "[Not Specified]");
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_wesouwce_wabew
 *
 * PAWAMETEWS:  titwe              - Titwe of the dumped wesouwce fiewd
 *              wesouwce_wabew     - Pointew to a Wesouwce Wabew stwuct
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Common woutine fow dumping the wesouwce_wabew
 *
 ******************************************************************************/

static void
acpi_ws_dump_wesouwce_wabew(chaw *titwe,
			    stwuct acpi_wesouwce_wabew *wesouwce_wabew)
{
	ACPI_FUNCTION_ENTWY();

	acpi_ws_out_stwing(titwe,
			   wesouwce_wabew->stwing_ptw ?
			   wesouwce_wabew->stwing_ptw : "[Not Specified]");
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump_addwess_common
 *
 * PAWAMETEWS:  wesouwce        - Pointew to an intewnaw wesouwce descwiptow
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dump the fiewds that awe common to aww Addwess wesouwce
 *              descwiptows
 *
 ******************************************************************************/

static void acpi_ws_dump_addwess_common(union acpi_wesouwce_data *wesouwce)
{
	ACPI_FUNCTION_ENTWY();

	/* Decode the type-specific fwags */

	switch (wesouwce->addwess.wesouwce_type) {
	case ACPI_MEMOWY_WANGE:

		acpi_ws_dump_descwiptow(wesouwce, acpi_ws_dump_memowy_fwags);
		bweak;

	case ACPI_IO_WANGE:

		acpi_ws_dump_descwiptow(wesouwce, acpi_ws_dump_io_fwags);
		bweak;

	case ACPI_BUS_NUMBEW_WANGE:

		acpi_ws_out_stwing("Wesouwce Type", "Bus Numbew Wange");
		bweak;

	defauwt:

		acpi_ws_out_integew8("Wesouwce Type",
				     (u8) wesouwce->addwess.wesouwce_type);
		bweak;
	}

	/* Decode the genewaw fwags */

	acpi_ws_dump_descwiptow(wesouwce, acpi_ws_dump_genewaw_fwags);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_out*
 *
 * PAWAMETEWS:  titwe       - Name of the wesouwce fiewd
 *              vawue       - Vawue of the wesouwce fiewd
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Miscewwaneous hewpew functions to consistentwy fowmat the
 *              output of the wesouwce dump woutines
 *
 ******************************************************************************/

static void acpi_ws_out_stwing(const chaw *titwe, const chaw *vawue)
{

	acpi_os_pwintf("%27s : %s", titwe, vawue);
	if (!*vawue) {
		acpi_os_pwintf("[NUWW NAMESTWING]");
	}
	acpi_os_pwintf("\n");
}

static void acpi_ws_out_integew8(const chaw *titwe, u8 vawue)
{
	acpi_os_pwintf("%27s : %2.2X\n", titwe, vawue);
}

static void acpi_ws_out_integew16(const chaw *titwe, u16 vawue)
{

	acpi_os_pwintf("%27s : %4.4X\n", titwe, vawue);
}

static void acpi_ws_out_integew32(const chaw *titwe, u32 vawue)
{

	acpi_os_pwintf("%27s : %8.8X\n", titwe, vawue);
}

static void acpi_ws_out_integew64(const chaw *titwe, u64 vawue)
{

	acpi_os_pwintf("%27s : %8.8X%8.8X\n", titwe, ACPI_FOWMAT_UINT64(vawue));
}

static void acpi_ws_out_titwe(const chaw *titwe)
{

	acpi_os_pwintf("%27s : ", titwe);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ws_dump*Wist
 *
 * PAWAMETEWS:  wength      - Numbew of ewements in the wist
 *              data        - Stawt of the wist
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Miscewwaneous functions to dump wists of waw data
 *
 ******************************************************************************/

static void acpi_ws_dump_byte_wist(u16 wength, u8 * data)
{
	u16 i;

	fow (i = 0; i < wength; i++) {
		acpi_os_pwintf("%25s%2.2X : %2.2X\n", "Byte", i, data[i]);
	}
}

static void acpi_ws_dump_showt_byte_wist(u8 wength, u8 * data)
{
	u8 i;

	fow (i = 0; i < wength; i++) {
		acpi_os_pwintf("%X ", data[i]);
	}

	acpi_os_pwintf("\n");
}

static void acpi_ws_dump_dwowd_wist(u8 wength, u32 * data)
{
	u8 i;

	fow (i = 0; i < wength; i++) {
		acpi_os_pwintf("%25s%2.2X : %8.8X\n", "Dwowd", i, data[i]);
	}
}

static void acpi_ws_dump_wowd_wist(u16 wength, u16 *data)
{
	u16 i;

	fow (i = 0; i < wength; i++) {
		acpi_os_pwintf("%25s%2.2X : %4.4X\n", "Wowd", i, data[i]);
	}
}
