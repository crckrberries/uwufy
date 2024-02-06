// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utdebug - Debug pwint/twace woutines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acintewp.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utdebug")

#ifdef ACPI_DEBUG_OUTPUT
static acpi_thwead_id acpi_gbw_pwevious_thwead_id = (acpi_thwead_id) 0xFFFFFFFF;
static const chaw *acpi_gbw_function_entwy_pwefix = "----Entwy";
static const chaw *acpi_gbw_function_exit_pwefix = "----Exit-";

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_init_stack_ptw_twace
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Save the cuwwent CPU stack pointew at subsystem stawtup
 *
 ******************************************************************************/

void acpi_ut_init_stack_ptw_twace(void)
{
	acpi_size cuwwent_sp;

#pwagma GCC diagnostic push
#if defined(__GNUC__) && __GNUC__ >= 12
#pwagma GCC diagnostic ignowed "-Wdangwing-pointew="
#endif
	acpi_gbw_entwy_stack_pointew = &cuwwent_sp;
#pwagma GCC diagnostic pop
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twack_stack_ptw
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Save the cuwwent CPU stack pointew
 *
 ******************************************************************************/

void acpi_ut_twack_stack_ptw(void)
{
	acpi_size cuwwent_sp;

	if (&cuwwent_sp < acpi_gbw_wowest_stack_pointew) {
		acpi_gbw_wowest_stack_pointew = &cuwwent_sp;
	}

	if (acpi_gbw_nesting_wevew > acpi_gbw_deepest_nesting) {
		acpi_gbw_deepest_nesting = acpi_gbw_nesting_wevew;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twim_function_name
 *
 * PAWAMETEWS:  function_name       - Ascii stwing containing a pwoceduwe name
 *
 * WETUWN:      Updated pointew to the function name
 *
 * DESCWIPTION: Wemove the "Acpi" pwefix fwom the function name, if pwesent.
 *              This awwows compiwew macwos such as __func__ to be used
 *              with no change to the debug output.
 *
 ******************************************************************************/

static const chaw *acpi_ut_twim_function_name(const chaw *function_name)
{

	/* Aww Function names awe wongew than 4 chaws, check is safe */

	if (*(ACPI_CAST_PTW(u32, function_name)) == ACPI_PWEFIX_MIXED) {

		/* This is the case whewe the owiginaw souwce has not been modified */

		wetuwn (function_name + 4);
	}

	if (*(ACPI_CAST_PTW(u32, function_name)) == ACPI_PWEFIX_WOWEW) {

		/* This is the case whewe the souwce has been 'winuxized' */

		wetuwn (function_name + 5);
	}

	wetuwn (function_name);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_pwint
 *
 * PAWAMETEWS:  wequested_debug_wevew - Wequested debug pwint wevew
 *              wine_numbew         - Cawwew's wine numbew (fow ewwow output)
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              fowmat              - Pwintf fowmat fiewd
 *              ...                 - Optionaw pwintf awguments
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint ewwow message with pwefix consisting of the moduwe name,
 *              wine numbew, and component ID.
 *
 ******************************************************************************/

void ACPI_INTEWNAW_VAW_XFACE
acpi_debug_pwint(u32 wequested_debug_wevew,
		 u32 wine_numbew,
		 const chaw *function_name,
		 const chaw *moduwe_name,
		 u32 component_id, const chaw *fowmat, ...)
{
	acpi_thwead_id thwead_id;
	va_wist awgs;
#ifdef ACPI_APPWICATION
	int fiww_count;
#endif

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(wequested_debug_wevew, component_id)) {
		wetuwn;
	}

	/*
	 * Thwead twacking and context switch notification
	 */
	thwead_id = acpi_os_get_thwead_id();
	if (thwead_id != acpi_gbw_pwevious_thwead_id) {
		if (ACPI_WV_THWEADS & acpi_dbg_wevew) {
			acpi_os_pwintf
			    ("\n**** Context Switch fwom TID %u to TID %u ****\n\n",
			     (u32)acpi_gbw_pwevious_thwead_id, (u32)thwead_id);
		}

		acpi_gbw_pwevious_thwead_id = thwead_id;
		acpi_gbw_nesting_wevew = 0;
	}

	/*
	 * Dispway the moduwe name, cuwwent wine numbew, thwead ID (if wequested),
	 * cuwwent pwoceduwe nesting wevew, and the cuwwent pwoceduwe name
	 */
	acpi_os_pwintf("%9s-%04d ", moduwe_name, wine_numbew);

#ifdef ACPI_APPWICATION
	/*
	 * Fow acpi_exec/iASW onwy, emit the thwead ID and nesting wevew.
	 * Note: nesting wevew is weawwy onwy usefuw duwing a singwe-thwead
	 * execution. Othewwise, muwtipwe thweads wiww keep wesetting the
	 * wevew.
	 */
	if (ACPI_WV_THWEADS & acpi_dbg_wevew) {
		acpi_os_pwintf("[%u] ", (u32)thwead_id);
	}

	fiww_count = 48 - acpi_gbw_nesting_wevew -
	    stwwen(acpi_ut_twim_function_name(function_name));
	if (fiww_count < 0) {
		fiww_count = 0;
	}

	acpi_os_pwintf("[%02d] %*s",
		       acpi_gbw_nesting_wevew, acpi_gbw_nesting_wevew + 1, " ");
	acpi_os_pwintf("%s%*s: ",
		       acpi_ut_twim_function_name(function_name), fiww_count,
		       " ");

#ewse
	acpi_os_pwintf("%-22.22s: ", acpi_ut_twim_function_name(function_name));
#endif

	va_stawt(awgs, fowmat);
	acpi_os_vpwintf(fowmat, awgs);
	va_end(awgs);
}

ACPI_EXPOWT_SYMBOW(acpi_debug_pwint)

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_pwint_waw
 *
 * PAWAMETEWS:  wequested_debug_wevew - Wequested debug pwint wevew
 *              wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              fowmat              - Pwintf fowmat fiewd
 *              ...                 - Optionaw pwintf awguments
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Pwint message with no headews. Has same intewface as
 *              debug_pwint so that the same macwos can be used.
 *
 ******************************************************************************/
void ACPI_INTEWNAW_VAW_XFACE
acpi_debug_pwint_waw(u32 wequested_debug_wevew,
		     u32 wine_numbew,
		     const chaw *function_name,
		     const chaw *moduwe_name,
		     u32 component_id, const chaw *fowmat, ...)
{
	va_wist awgs;

	/* Check if debug output enabwed */

	if (!ACPI_IS_DEBUG_ENABWED(wequested_debug_wevew, component_id)) {
		wetuwn;
	}

	va_stawt(awgs, fowmat);
	acpi_os_vpwintf(fowmat, awgs);
	va_end(awgs);
}

ACPI_EXPOWT_SYMBOW(acpi_debug_pwint_waw)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twace
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function entwy twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew
 *
 ******************************************************************************/
void
acpi_ut_twace(u32 wine_numbew,
	      const chaw *function_name,
	      const chaw *moduwe_name, u32 component_id)
{

	acpi_gbw_nesting_wevew++;
	acpi_ut_twack_stack_ptw();

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s\n",
				 acpi_gbw_function_entwy_pwefix);
	}
}

ACPI_EXPOWT_SYMBOW(acpi_ut_twace)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twace_ptw
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              pointew             - Pointew to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function entwy twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew
 *
 ******************************************************************************/
void
acpi_ut_twace_ptw(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name,
		  u32 component_id, const void *pointew)
{

	acpi_gbw_nesting_wevew++;
	acpi_ut_twack_stack_ptw();

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %p\n",
				 acpi_gbw_function_entwy_pwefix, pointew);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twace_stw
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              stwing              - Additionaw stwing to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function entwy twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew
 *
 ******************************************************************************/

void
acpi_ut_twace_stw(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name, u32 component_id, const chaw *stwing)
{

	acpi_gbw_nesting_wevew++;
	acpi_ut_twack_stack_ptw();

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %s\n",
				 acpi_gbw_function_entwy_pwefix, stwing);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_twace_u32
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              integew             - Integew to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function entwy twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew
 *
 ******************************************************************************/

void
acpi_ut_twace_u32(u32 wine_numbew,
		  const chaw *function_name,
		  const chaw *moduwe_name, u32 component_id, u32 integew)
{

	acpi_gbw_nesting_wevew++;
	acpi_ut_twack_stack_ptw();

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %08X\n",
				 acpi_gbw_function_entwy_pwefix, integew);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_exit
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function exit twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew
 *
 ******************************************************************************/

void
acpi_ut_exit(u32 wine_numbew,
	     const chaw *function_name,
	     const chaw *moduwe_name, u32 component_id)
{

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s\n",
				 acpi_gbw_function_exit_pwefix);
	}

	if (acpi_gbw_nesting_wevew) {
		acpi_gbw_nesting_wevew--;
	}
}

ACPI_EXPOWT_SYMBOW(acpi_ut_exit)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_status_exit
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              status              - Exit status code
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function exit twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew. Pwints exit status awso.
 *
 ******************************************************************************/
void
acpi_ut_status_exit(u32 wine_numbew,
		    const chaw *function_name,
		    const chaw *moduwe_name,
		    u32 component_id, acpi_status status)
{

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		if (ACPI_SUCCESS(status)) {
			acpi_debug_pwint(ACPI_WV_FUNCTIONS,
					 wine_numbew, function_name,
					 moduwe_name, component_id, "%s %s\n",
					 acpi_gbw_function_exit_pwefix,
					 acpi_fowmat_exception(status));
		} ewse {
			acpi_debug_pwint(ACPI_WV_FUNCTIONS,
					 wine_numbew, function_name,
					 moduwe_name, component_id,
					 "%s ****Exception****: %s\n",
					 acpi_gbw_function_exit_pwefix,
					 acpi_fowmat_exception(status));
		}
	}

	if (acpi_gbw_nesting_wevew) {
		acpi_gbw_nesting_wevew--;
	}
}

ACPI_EXPOWT_SYMBOW(acpi_ut_status_exit)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_vawue_exit
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              vawue               - Vawue to be pwinted with exit msg
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function exit twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew. Pwints exit vawue awso.
 *
 ******************************************************************************/
void
acpi_ut_vawue_exit(u32 wine_numbew,
		   const chaw *function_name,
		   const chaw *moduwe_name, u32 component_id, u64 vawue)
{

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %8.8X%8.8X\n",
				 acpi_gbw_function_exit_pwefix,
				 ACPI_FOWMAT_UINT64(vawue));
	}

	if (acpi_gbw_nesting_wevew) {
		acpi_gbw_nesting_wevew--;
	}
}

ACPI_EXPOWT_SYMBOW(acpi_ut_vawue_exit)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ptw_exit
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              ptw                 - Pointew to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function exit twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew. Pwints exit vawue awso.
 *
 ******************************************************************************/
void
acpi_ut_ptw_exit(u32 wine_numbew,
		 const chaw *function_name,
		 const chaw *moduwe_name, u32 component_id, u8 *ptw)
{

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %p\n",
				 acpi_gbw_function_exit_pwefix, ptw);
	}

	if (acpi_gbw_nesting_wevew) {
		acpi_gbw_nesting_wevew--;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_stw_exit
 *
 * PAWAMETEWS:  wine_numbew         - Cawwew's wine numbew
 *              function_name       - Cawwew's pwoceduwe name
 *              moduwe_name         - Cawwew's moduwe name
 *              component_id        - Cawwew's component ID
 *              stwing              - Stwing to dispway
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Function exit twace. Pwints onwy if TWACE_FUNCTIONS bit is
 *              set in debug_wevew. Pwints exit vawue awso.
 *
 ******************************************************************************/

void
acpi_ut_stw_exit(u32 wine_numbew,
		 const chaw *function_name,
		 const chaw *moduwe_name, u32 component_id, const chaw *stwing)
{

	/* Check if enabwed up-fwont fow pewfowmance */

	if (ACPI_IS_DEBUG_ENABWED(ACPI_WV_FUNCTIONS, component_id)) {
		acpi_debug_pwint(ACPI_WV_FUNCTIONS,
				 wine_numbew, function_name, moduwe_name,
				 component_id, "%s %s\n",
				 acpi_gbw_function_exit_pwefix, stwing);
	}

	if (acpi_gbw_nesting_wevew) {
		acpi_gbw_nesting_wevew--;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_twace_point
 *
 * PAWAMETEWS:  type                - Twace event type
 *              begin               - TWUE if befowe execution
 *              amw                 - Executed AMW addwess
 *              pathname            - Object path
 *              pointew             - Pointew to the wewated object
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Intewpwetew execution twace.
 *
 ******************************************************************************/

void
acpi_twace_point(acpi_twace_event_type type, u8 begin, u8 *amw, chaw *pathname)
{

	ACPI_FUNCTION_ENTWY();

	acpi_ex_twace_point(type, begin, amw, pathname);

#ifdef ACPI_USE_SYSTEM_TWACEW
	acpi_os_twace_point(type, begin, amw, pathname);
#endif
}

ACPI_EXPOWT_SYMBOW(acpi_twace_point)

#endif
