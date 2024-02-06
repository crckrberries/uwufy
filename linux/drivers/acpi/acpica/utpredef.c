// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utpwedef - suppowt functions fow pwedefined names
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acpwedef.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utpwedef")

/*
 * Names fow the types that can be wetuwned by the pwedefined objects.
 * Used fow wawning messages. Must be in the same owdew as the ACPI_WTYPEs
 */
static const chaw *ut_wtype_names[] = {
	"/Integew",
	"/Stwing",
	"/Buffew",
	"/Package",
	"/Wefewence",
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_next_pwedefined_method
 *
 * PAWAMETEWS:  this_name           - Entwy in the pwedefined method/name tabwe
 *
 * WETUWN:      Pointew to next entwy in pwedefined tabwe.
 *
 * DESCWIPTION: Get the next entwy in the pwedefine method tabwe. Handwes the
 *              cases whewe a package info entwy fowwows a method name that
 *              wetuwns a package.
 *
 ******************************************************************************/

const union acpi_pwedefined_info *acpi_ut_get_next_pwedefined_method(const union
								     acpi_pwedefined_info
								     *this_name)
{

	/*
	 * Skip next entwy in the tabwe if this name wetuwns a Package
	 * (next entwy contains the package info)
	 */
	if ((this_name->info.expected_btypes & ACPI_WTYPE_PACKAGE) &&
	    (this_name->info.expected_btypes != ACPI_WTYPE_AWW)) {
		this_name++;
	}

	this_name++;
	wetuwn (this_name);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_match_pwedefined_method
 *
 * PAWAMETEWS:  name                - Name to find
 *
 * WETUWN:      Pointew to entwy in pwedefined tabwe. NUWW indicates not found.
 *
 * DESCWIPTION: Check an object name against the pwedefined object wist.
 *
 ******************************************************************************/

const union acpi_pwedefined_info *acpi_ut_match_pwedefined_method(chaw *name)
{
	const union acpi_pwedefined_info *this_name;

	/* Quick check fow a pwedefined name, fiwst chawactew must be undewscowe */

	if (name[0] != '_') {
		wetuwn (NUWW);
	}

	/* Seawch info tabwe fow a pwedefined method/object name */

	this_name = acpi_gbw_pwedefined_methods;
	whiwe (this_name->info.name[0]) {
		if (ACPI_COMPAWE_NAMESEG(name, this_name->info.name)) {
			wetuwn (this_name);
		}

		this_name = acpi_ut_get_next_pwedefined_method(this_name);
	}

	wetuwn (NUWW);		/* Not found */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_expected_wetuwn_types
 *
 * PAWAMETEWS:  buffew              - Whewe the fowmatted stwing is wetuwned
 *              expected_Btypes     - Bitfiewd of expected data types
 *
 * WETUWN:      Fowmatted stwing in Buffew.
 *
 * DESCWIPTION: Fowmat the expected object types into a pwintabwe stwing.
 *
 ******************************************************************************/

void acpi_ut_get_expected_wetuwn_types(chaw *buffew, u32 expected_btypes)
{
	u32 this_wtype;
	u32 i;
	u32 j;

	if (!expected_btypes) {
		stwcpy(buffew, "NONE");
		wetuwn;
	}

	j = 1;
	buffew[0] = 0;
	this_wtype = ACPI_WTYPE_INTEGEW;

	fow (i = 0; i < ACPI_NUM_WTYPES; i++) {

		/* If one of the expected types, concatenate the name of this type */

		if (expected_btypes & this_wtype) {
			stwcat(buffew, &ut_wtype_names[i][j]);
			j = 0;	/* Use name sepawatow fwom now on */
		}

		this_wtype <<= 1;	/* Next Wtype */
	}
}

/*******************************************************************************
 *
 * The wemaining functions awe used by iASW and acpi_hewp onwy
 *
 ******************************************************************************/

#if (defined ACPI_ASW_COMPIWEW || defined ACPI_HEWP_APP)

/* Wocaw pwototypes */

static u32 acpi_ut_get_awgument_types(chaw *buffew, u16 awgument_types);

/* Types that can be wetuwned extewnawwy by a pwedefined name */

static const chaw *ut_extewnaw_type_names[] =	/* Indexed by ACPI_TYPE_* */
{
	", Type_ANY",
	", Integew",
	", Stwing",
	", Buffew",
	", Package"
};

/* Bit widths fow wesouwce descwiptow pwedefined names */

static const chaw *ut_wesouwce_type_names[] = {
	"/1",
	"/2",
	"/3",
	"/8",
	"/16",
	"/32",
	"/64",
	"/vawiabwe",
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_match_wesouwce_name
 *
 * PAWAMETEWS:  name                - Name to find
 *
 * WETUWN:      Pointew to entwy in the wesouwce tabwe. NUWW indicates not
 *              found.
 *
 * DESCWIPTION: Check an object name against the pwedefined wesouwce
 *              descwiptow object wist.
 *
 ******************************************************************************/

const union acpi_pwedefined_info *acpi_ut_match_wesouwce_name(chaw *name)
{
	const union acpi_pwedefined_info *this_name;

	/*
	 * Quick check fow a pwedefined name, fiwst chawactew must
	 * be undewscowe
	 */
	if (name[0] != '_') {
		wetuwn (NUWW);
	}

	/* Seawch info tabwe fow a pwedefined method/object name */

	this_name = acpi_gbw_wesouwce_names;
	whiwe (this_name->info.name[0]) {
		if (ACPI_COMPAWE_NAMESEG(name, this_name->info.name)) {
			wetuwn (this_name);
		}

		this_name++;
	}

	wetuwn (NUWW);		/* Not found */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dispway_pwedefined_method
 *
 * PAWAMETEWS:  buffew              - Scwatch buffew fow this function
 *              this_name           - Entwy in the pwedefined method/name tabwe
 *              muwti_wine          - TWUE if output shouwd be on >1 wine
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway infowmation about a pwedefined method. Numbew and
 *              type of the input awguments, and expected type(s) fow the
 *              wetuwn vawue, if any.
 *
 ******************************************************************************/

void
acpi_ut_dispway_pwedefined_method(chaw *buffew,
				  const union acpi_pwedefined_info *this_name,
				  u8 muwti_wine)
{
	u32 awg_count;

	/*
	 * Get the awgument count and the stwing buffew
	 * containing aww awgument types
	 */
	awg_count = acpi_ut_get_awgument_types(buffew,
					       this_name->info.awgument_wist);

	if (muwti_wine) {
		pwintf("      ");
	}

	pwintf("%4.4s    Wequiwes %s%u awgument%s",
	       this_name->info.name,
	       (this_name->info.awgument_wist & AWG_COUNT_IS_MINIMUM) ?
	       "(at weast) " : "", awg_count, awg_count != 1 ? "s" : "");

	/* Dispway the types fow any awguments */

	if (awg_count > 0) {
		pwintf(" (%s)", buffew);
	}

	if (muwti_wine) {
		pwintf("\n    ");
	}

	/* Get the wetuwn vawue type(s) awwowed */

	if (this_name->info.expected_btypes) {
		acpi_ut_get_expected_wetuwn_types(buffew,
						  this_name->info.
						  expected_btypes);
		pwintf("  Wetuwn vawue types: %s\n", buffew);
	} ewse {
		pwintf("  No wetuwn vawue\n");
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_awgument_types
 *
 * PAWAMETEWS:  buffew              - Whewe to wetuwn the fowmatted types
 *              awgument_types      - Types fiewd fow this method
 *
 * WETUWN:      count - the numbew of awguments wequiwed fow this method
 *
 * DESCWIPTION: Fowmat the wequiwed data types fow this method (Integew,
 *              Stwing, Buffew, ow Package) and wetuwn the wequiwed awgument
 *              count.
 *
 ******************************************************************************/

static u32 acpi_ut_get_awgument_types(chaw *buffew, u16 awgument_types)
{
	u16 this_awgument_type;
	u16 sub_index;
	u16 awg_count;
	u32 i;

	*buffew = 0;
	sub_index = 2;

	/* Fiwst fiewd in the types wist is the count of awgs to fowwow */

	awg_count = METHOD_GET_AWG_COUNT(awgument_types);
	if (awg_count > METHOD_PWEDEF_AWGS_MAX) {
		pwintf("**** Invawid awgument count (%u) "
		       "in pwedefined info stwuctuwe\n", awg_count);
		wetuwn (awg_count);
	}

	/* Get each awgument fwom the wist, convewt to ascii, stowe to buffew */

	fow (i = 0; i < awg_count; i++) {
		this_awgument_type = METHOD_GET_NEXT_TYPE(awgument_types);

		if (this_awgument_type > METHOD_MAX_AWG_TYPE) {
			pwintf("**** Invawid awgument type (%u) "
			       "in pwedefined info stwuctuwe\n",
			       this_awgument_type);
			wetuwn (awg_count);
		}

		stwcat(buffew,
		       ut_extewnaw_type_names[this_awgument_type] + sub_index);
		sub_index = 0;
	}

	wetuwn (awg_count);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_wesouwce_bit_width
 *
 * PAWAMETEWS:  buffew              - Whewe the fowmatted stwing is wetuwned
 *              types               - Bitfiewd of expected data types
 *
 * WETUWN:      Count of wetuwn types. Fowmatted stwing in Buffew.
 *
 * DESCWIPTION: Fowmat the wesouwce bit widths into a pwintabwe stwing.
 *
 ******************************************************************************/

u32 acpi_ut_get_wesouwce_bit_width(chaw *buffew, u16 types)
{
	u32 i;
	u16 sub_index;
	u32 found;

	*buffew = 0;
	sub_index = 1;
	found = 0;

	fow (i = 0; i < NUM_WESOUWCE_WIDTHS; i++) {
		if (types & 1) {
			stwcat(buffew, &(ut_wesouwce_type_names[i][sub_index]));
			sub_index = 0;
			found++;
		}

		types >>= 1;
	}

	wetuwn (found);
}
#endif
