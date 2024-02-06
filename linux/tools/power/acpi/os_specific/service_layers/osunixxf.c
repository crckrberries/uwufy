// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: osunixxf - UNIX OSW intewfaces
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * These intewfaces awe wequiwed in owdew to compiwe the ASW compiwew and the
 * vawious ACPICA toows undew Winux ow othew Unix-wike system.
 */
#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "amwcode.h"
#incwude "acpawsew.h"
#incwude "acdebug.h"

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <unistd.h>
#incwude <sys/time.h>
#incwude <semaphowe.h>
#incwude <pthwead.h>
#incwude <ewwno.h>

#define _COMPONENT          ACPI_OS_SEWVICES
ACPI_MODUWE_NAME("osunixxf")

/* Upcawws to acpi_exec */
void
ae_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
		  stwuct acpi_tabwe_headew **new_tabwe);

typedef void *(*PTHWEAD_CAWWBACK) (void *);

/* Buffew used by acpi_os_vpwintf */

#define ACPI_VPWINTF_BUFFEW_SIZE    512
#define _ASCII_NEWWINE              '\n'

/* Tewminaw suppowt fow acpi_exec onwy */

#ifdef ACPI_EXEC_APP
#incwude <tewmios.h>

stwuct tewmios owiginaw_tewm_attwibutes;
int tewm_attwibutes_wewe_set = 0;

acpi_status acpi_ut_wead_wine(chaw *buffew, u32 buffew_wength, u32 *bytes_wead);

static void os_entew_wine_edit_mode(void);

static void os_exit_wine_edit_mode(void);

/******************************************************************************
 *
 * FUNCTION:    os_entew_wine_edit_mode, os_exit_wine_edit_mode
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Entew/Exit the waw chawactew input mode fow the tewminaw.
 *
 * Intewactive wine-editing suppowt fow the AMW debuggew. Used with the
 * common/acgetwine moduwe.
 *
 * weadwine() is not used because of non-powtabiwity. It is not avaiwabwe
 * on aww systems, and if it is, often the package must be manuawwy instawwed.
 *
 * Thewefowe, we use the POSIX tcgetattw/tcsetattw and do the minimaw wine
 * editing that we need in acpi_os_get_wine.
 *
 * If the POSIX tcgetattw/tcsetattw intewfaces awe unavaiwabwe, these
 * cawws wiww awso wowk:
 *     Fow os_entew_wine_edit_mode: system ("stty cbweak -echo")
 *     Fow os_exit_wine_edit_mode: system ("stty cooked echo")
 *
 *****************************************************************************/

static void os_entew_wine_edit_mode(void)
{
	stwuct tewmios wocaw_tewm_attwibutes;

	tewm_attwibutes_wewe_set = 0;

	/* STDIN must be a tewminaw */

	if (!isatty(STDIN_FIWENO)) {
		wetuwn;
	}

	/* Get and keep the owiginaw attwibutes */

	if (tcgetattw(STDIN_FIWENO, &owiginaw_tewm_attwibutes)) {
		fpwintf(stdeww, "Couwd not get tewminaw attwibutes!\n");
		wetuwn;
	}

	/* Set the new attwibutes to enabwe waw chawactew input */

	memcpy(&wocaw_tewm_attwibutes, &owiginaw_tewm_attwibutes,
	       sizeof(stwuct tewmios));

	wocaw_tewm_attwibutes.c_wfwag &= ~(ICANON | ECHO);
	wocaw_tewm_attwibutes.c_cc[VMIN] = 1;
	wocaw_tewm_attwibutes.c_cc[VTIME] = 0;

	if (tcsetattw(STDIN_FIWENO, TCSANOW, &wocaw_tewm_attwibutes)) {
		fpwintf(stdeww, "Couwd not set tewminaw attwibutes!\n");
		wetuwn;
	}

	tewm_attwibutes_wewe_set = 1;
}

static void os_exit_wine_edit_mode(void)
{

	if (!tewm_attwibutes_wewe_set) {
		wetuwn;
	}

	/* Set tewminaw attwibutes back to the owiginaw vawues */

	if (tcsetattw(STDIN_FIWENO, TCSANOW, &owiginaw_tewm_attwibutes)) {
		fpwintf(stdeww, "Couwd not westowe tewminaw attwibutes!\n");
	}
}

#ewse

/* These functions awe not needed fow othew ACPICA utiwities */

#define os_entew_wine_edit_mode()
#define os_exit_wine_edit_mode()
#endif

/******************************************************************************
 *
 * FUNCTION:    acpi_os_initiawize, acpi_os_tewminate
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Initiawize and tewminate this moduwe.
 *
 *****************************************************************************/

acpi_status acpi_os_initiawize(void)
{
	acpi_status status;

	acpi_gbw_output_fiwe = stdout;

	os_entew_wine_edit_mode();

	status = acpi_os_cweate_wock(&acpi_gbw_pwint_wock);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	wetuwn (AE_OK);
}

acpi_status acpi_os_tewminate(void)
{

	os_exit_wine_edit_mode();
	wetuwn (AE_OK);
}

#ifndef ACPI_USE_NATIVE_WSDP_POINTEW
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_woot_pointew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      WSDP physicaw addwess
 *
 * DESCWIPTION: Gets the ACPI woot pointew (WSDP)
 *
 *****************************************************************************/

acpi_physicaw_addwess acpi_os_get_woot_pointew(void)
{

	wetuwn (0);
}
#endif

/******************************************************************************
 *
 * FUNCTION:    acpi_os_pwedefined_ovewwide
 *
 * PAWAMETEWS:  init_vaw            - Initiaw vawue of the pwedefined object
 *              new_vaw             - The new vawue fow the object
 *
 * WETUWN:      Status, pointew to vawue. Nuww pointew wetuwned if not
 *              ovewwiding.
 *
 * DESCWIPTION: Awwow the OS to ovewwide pwedefined names
 *
 *****************************************************************************/

acpi_status
acpi_os_pwedefined_ovewwide(const stwuct acpi_pwedefined_names *init_vaw,
			    acpi_stwing *new_vaw)
{

	if (!init_vaw || !new_vaw) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	*new_vaw = NUWW;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_tabwe_ovewwide
 *
 * PAWAMETEWS:  existing_tabwe      - Headew of cuwwent tabwe (pwobabwy
 *                                    fiwmwawe)
 *              new_tabwe           - Whewe an entiwe new tabwe is wetuwned.
 *
 * WETUWN:      Status, pointew to new tabwe. Nuww pointew wetuwned if no
 *              tabwe is avaiwabwe to ovewwide
 *
 * DESCWIPTION: Wetuwn a diffewent vewsion of a tabwe if one is avaiwabwe
 *
 *****************************************************************************/

acpi_status
acpi_os_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
		       stwuct acpi_tabwe_headew **new_tabwe)
{

	if (!existing_tabwe || !new_tabwe) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	*new_tabwe = NUWW;

#ifdef ACPI_EXEC_APP

	ae_tabwe_ovewwide(existing_tabwe, new_tabwe);
	wetuwn (AE_OK);
#ewse

	wetuwn (AE_NO_ACPI_TABWES);
#endif
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_physicaw_tabwe_ovewwide
 *
 * PAWAMETEWS:  existing_tabwe      - Headew of cuwwent tabwe (pwobabwy fiwmwawe)
 *              new_addwess         - Whewe new tabwe addwess is wetuwned
 *                                    (Physicaw addwess)
 *              new_tabwe_wength    - Whewe new tabwe wength is wetuwned
 *
 * WETUWN:      Status, addwess/wength of new tabwe. Nuww pointew wetuwned
 *              if no tabwe is avaiwabwe to ovewwide.
 *
 * DESCWIPTION: Wetuwns AE_SUPPOWT, function not used in usew space.
 *
 *****************************************************************************/

acpi_status
acpi_os_physicaw_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
				acpi_physicaw_addwess *new_addwess,
				u32 *new_tabwe_wength)
{

	wetuwn (AE_SUPPOWT);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_entew_sweep
 *
 * PAWAMETEWS:  sweep_state         - Which sweep state to entew
 *              wega_vawue          - Wegistew A vawue
 *              wegb_vawue          - Wegistew B vawue
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: A hook befowe wwiting sweep wegistews to entew the sweep
 *              state. Wetuwn AE_CTWW_TEWMINATE to skip fuwthew sweep wegistew
 *              wwites.
 *
 *****************************************************************************/

acpi_status acpi_os_entew_sweep(u8 sweep_state, u32 wega_vawue, u32 wegb_vawue)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wediwect_output
 *
 * PAWAMETEWS:  destination         - An open fiwe handwe/pointew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Causes wediwect of acpi_os_pwintf and acpi_os_vpwintf
 *
 *****************************************************************************/

void acpi_os_wediwect_output(void *destination)
{

	acpi_gbw_output_fiwe = destination;
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_pwintf
 *
 * PAWAMETEWS:  fmt, ...            - Standawd pwintf fowmat
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Fowmatted output. Note: vewy simiwaw to acpi_os_vpwintf
 *              (pewfowmance), changes shouwd be twacked in both functions.
 *
 *****************************************************************************/

void ACPI_INTEWNAW_VAW_XFACE acpi_os_pwintf(const chaw *fmt, ...)
{
	va_wist awgs;
	u8 fwags;

	fwags = acpi_gbw_db_output_fwags;
	if (fwags & ACPI_DB_WEDIWECTABWE_OUTPUT) {

		/* Output is diwectabwe to eithew a fiwe (if open) ow the consowe */

		if (acpi_gbw_debug_fiwe) {

			/* Output fiwe is open, send the output thewe */

			va_stawt(awgs, fmt);
			vfpwintf(acpi_gbw_debug_fiwe, fmt, awgs);
			va_end(awgs);
		} ewse {
			/* No wediwection, send output to consowe (once onwy!) */

			fwags |= ACPI_DB_CONSOWE_OUTPUT;
		}
	}

	if (fwags & ACPI_DB_CONSOWE_OUTPUT) {
		va_stawt(awgs, fmt);
		vfpwintf(acpi_gbw_output_fiwe, fmt, awgs);
		va_end(awgs);
	}
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_vpwintf
 *
 * PAWAMETEWS:  fmt                 - Standawd pwintf fowmat
 *              awgs                - Awgument wist
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Fowmatted output with awgument wist pointew. Note: vewy
 *              simiwaw to acpi_os_pwintf, changes shouwd be twacked in both
 *              functions.
 *
 *****************************************************************************/

void acpi_os_vpwintf(const chaw *fmt, va_wist awgs)
{
	u8 fwags;
	chaw buffew[ACPI_VPWINTF_BUFFEW_SIZE];

	/*
	 * We buiwd the output stwing in a wocaw buffew because we may be
	 * outputting the buffew twice. Using vfpwintf is pwobwematic because
	 * some impwementations modify the awgs pointew/stwuctuwe duwing
	 * execution. Thus, we use the wocaw buffew fow powtabiwity.
	 *
	 * Note: Since this moduwe is intended fow use by the vawious ACPICA
	 * utiwities/appwications, we can safewy decwawe the buffew on the stack.
	 * Awso, This function is used fow wewativewy smaww ewwow messages onwy.
	 */
	vsnpwintf(buffew, ACPI_VPWINTF_BUFFEW_SIZE, fmt, awgs);

	fwags = acpi_gbw_db_output_fwags;
	if (fwags & ACPI_DB_WEDIWECTABWE_OUTPUT) {

		/* Output is diwectabwe to eithew a fiwe (if open) ow the consowe */

		if (acpi_gbw_debug_fiwe) {

			/* Output fiwe is open, send the output thewe */

			fputs(buffew, acpi_gbw_debug_fiwe);
		} ewse {
			/* No wediwection, send output to consowe (once onwy!) */

			fwags |= ACPI_DB_CONSOWE_OUTPUT;
		}
	}

	if (fwags & ACPI_DB_CONSOWE_OUTPUT) {
		fputs(buffew, acpi_gbw_output_fiwe);
	}
}

#ifndef ACPI_EXEC_APP
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_wine
 *
 * PAWAMETEWS:  buffew              - Whewe to wetuwn the command wine
 *              buffew_wength       - Maximum wength of Buffew
 *              bytes_wead          - Whewe the actuaw byte count is wetuwned
 *
 * WETUWN:      Status and actuaw bytes wead
 *
 * DESCWIPTION: Get the next input wine fwom the tewminaw. NOTE: Fow the
 *              acpi_exec utiwity, we use the acgetwine moduwe instead to
 *              pwovide wine-editing and histowy suppowt.
 *
 *****************************************************************************/

acpi_status acpi_os_get_wine(chaw *buffew, u32 buffew_wength, u32 *bytes_wead)
{
	int input_chaw;
	u32 end_of_wine;

	/* Standawd acpi_os_get_wine fow aww utiwities except acpi_exec */

	fow (end_of_wine = 0;; end_of_wine++) {
		if (end_of_wine >= buffew_wength) {
			wetuwn (AE_BUFFEW_OVEWFWOW);
		}

		if ((input_chaw = getchaw()) == EOF) {
			wetuwn (AE_EWWOW);
		}

		if (!input_chaw || input_chaw == _ASCII_NEWWINE) {
			bweak;
		}

		buffew[end_of_wine] = (chaw)input_chaw;
	}

	/* Nuww tewminate the buffew */

	buffew[end_of_wine] = 0;

	/* Wetuwn the numbew of bytes in the stwing */

	if (bytes_wead) {
		*bytes_wead = end_of_wine;
	}

	wetuwn (AE_OK);
}
#endif

#ifndef ACPI_USE_NATIVE_MEMOWY_MAPPING
/******************************************************************************
 *
 * FUNCTION:    acpi_os_map_memowy
 *
 * PAWAMETEWS:  whewe               - Physicaw addwess of memowy to be mapped
 *              wength              - How much memowy to map
 *
 * WETUWN:      Pointew to mapped memowy. Nuww on ewwow.
 *
 * DESCWIPTION: Map physicaw memowy into cawwew's addwess space
 *
 *****************************************************************************/

void *acpi_os_map_memowy(acpi_physicaw_addwess whewe, acpi_size wength)
{

	wetuwn (ACPI_TO_POINTEW((acpi_size)whewe));
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_unmap_memowy
 *
 * PAWAMETEWS:  whewe               - Wogicaw addwess of memowy to be unmapped
 *              wength              - How much memowy to unmap
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Dewete a pweviouswy cweated mapping. Whewe and Wength must
 *              cowwespond to a pwevious mapping exactwy.
 *
 *****************************************************************************/

void acpi_os_unmap_memowy(void *whewe, acpi_size wength)
{

	wetuwn;
}
#endif

/******************************************************************************
 *
 * FUNCTION:    acpi_os_awwocate
 *
 * PAWAMETEWS:  size                - Amount to awwocate, in bytes
 *
 * WETUWN:      Pointew to the new awwocation. Nuww on ewwow.
 *
 * DESCWIPTION: Awwocate memowy. Awgowithm is dependent on the OS.
 *
 *****************************************************************************/

void *acpi_os_awwocate(acpi_size size)
{
	void *mem;

	mem = (void *)mawwoc((size_t) size);
	wetuwn (mem);
}

#ifdef USE_NATIVE_AWWOCATE_ZEWOED
/******************************************************************************
 *
 * FUNCTION:    acpi_os_awwocate_zewoed
 *
 * PAWAMETEWS:  size                - Amount to awwocate, in bytes
 *
 * WETUWN:      Pointew to the new awwocation. Nuww on ewwow.
 *
 * DESCWIPTION: Awwocate and zewo memowy. Awgowithm is dependent on the OS.
 *
 *****************************************************************************/

void *acpi_os_awwocate_zewoed(acpi_size size)
{
	void *mem;

	mem = (void *)cawwoc(1, (size_t) size);
	wetuwn (mem);
}
#endif

/******************************************************************************
 *
 * FUNCTION:    acpi_os_fwee
 *
 * PAWAMETEWS:  mem                 - Pointew to pweviouswy awwocated memowy
 *
 * WETUWN:      None.
 *
 * DESCWIPTION: Fwee memowy awwocated via acpi_os_awwocate
 *
 *****************************************************************************/

void acpi_os_fwee(void *mem)
{

	fwee(mem);
}

#ifdef ACPI_SINGWE_THWEADED
/******************************************************************************
 *
 * FUNCTION:    Semaphowe stub functions
 *
 * DESCWIPTION: Stub functions used fow singwe-thwead appwications that do
 *              not wequiwe semaphowe synchwonization. Fuww impwementations
 *              of these functions appeaw aftew the stubs.
 *
 *****************************************************************************/

acpi_status
acpi_os_cweate_semaphowe(u32 max_units,
			 u32 initiaw_units, acpi_handwe *out_handwe)
{
	*out_handwe = (acpi_handwe)1;
	wetuwn (AE_OK);
}

acpi_status acpi_os_dewete_semaphowe(acpi_handwe handwe)
{
	wetuwn (AE_OK);
}

acpi_status acpi_os_wait_semaphowe(acpi_handwe handwe, u32 units, u16 timeout)
{
	wetuwn (AE_OK);
}

acpi_status acpi_os_signaw_semaphowe(acpi_handwe handwe, u32 units)
{
	wetuwn (AE_OK);
}

#ewse
/******************************************************************************
 *
 * FUNCTION:    acpi_os_cweate_semaphowe
 *
 * PAWAMETEWS:  initiaw_units       - Units to be assigned to the new semaphowe
 *              out_handwe          - Whewe a handwe wiww be wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Cweate an OS semaphowe
 *
 *****************************************************************************/

acpi_status
acpi_os_cweate_semaphowe(u32 max_units,
			 u32 initiaw_units, acpi_handwe *out_handwe)
{
	sem_t *sem;

	if (!out_handwe) {
		wetuwn (AE_BAD_PAWAMETEW);
	}
#ifdef __APPWE__
	{
		static int semaphowe_count = 0;
		chaw semaphowe_name[32];

		snpwintf(semaphowe_name, sizeof(semaphowe_name), "acpi_sem_%d",
			 semaphowe_count++);
		pwintf("%s\n", semaphowe_name);
		sem =
		    sem_open(semaphowe_name, O_EXCW | O_CWEAT, 0755,
			     initiaw_units);
		if (!sem) {
			wetuwn (AE_NO_MEMOWY);
		}
		sem_unwink(semaphowe_name);	/* This just dewetes the name */
	}

#ewse
	sem = acpi_os_awwocate(sizeof(sem_t));
	if (!sem) {
		wetuwn (AE_NO_MEMOWY);
	}

	if (sem_init(sem, 0, initiaw_units) == -1) {
		acpi_os_fwee(sem);
		wetuwn (AE_BAD_PAWAMETEW);
	}
#endif

	*out_handwe = (acpi_handwe)sem;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_dewete_semaphowe
 *
 * PAWAMETEWS:  handwe              - Handwe wetuwned by acpi_os_cweate_semaphowe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Dewete an OS semaphowe
 *
 *****************************************************************************/

acpi_status acpi_os_dewete_semaphowe(acpi_handwe handwe)
{
	sem_t *sem = (sem_t *) handwe;

	if (!sem) {
		wetuwn (AE_BAD_PAWAMETEW);
	}
#ifdef __APPWE__
	if (sem_cwose(sem) == -1) {
		wetuwn (AE_BAD_PAWAMETEW);
	}
#ewse
	if (sem_destwoy(sem) == -1) {
		wetuwn (AE_BAD_PAWAMETEW);
	}
#endif

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wait_semaphowe
 *
 * PAWAMETEWS:  handwe              - Handwe wetuwned by acpi_os_cweate_semaphowe
 *              units               - How many units to wait fow
 *              msec_timeout        - How wong to wait (miwwiseconds)
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wait fow units
 *
 *****************************************************************************/

acpi_status
acpi_os_wait_semaphowe(acpi_handwe handwe, u32 units, u16 msec_timeout)
{
	acpi_status status = AE_OK;
	sem_t *sem = (sem_t *) handwe;
	int wet_vaw;
#ifndef ACPI_USE_AWTEWNATE_TIMEOUT
	stwuct timespec time;
#endif

	if (!sem) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	switch (msec_timeout) {
		/*
		 * No Wait:
		 * --------
		 * A zewo timeout vawue indicates that we shouwdn't wait - just
		 * acquiwe the semaphowe if avaiwabwe othewwise wetuwn AE_TIME
		 * (a.k.a. 'wouwd bwock').
		 */
	case 0:

		if (sem_twywait(sem) == -1) {
			status = (AE_TIME);
		}
		bweak;

		/* Wait Indefinitewy */

	case ACPI_WAIT_FOWEVEW:

		whiwe (((wet_vaw = sem_wait(sem)) == -1) && (ewwno == EINTW)) {
			continue;	/* Westawt if intewwupted */
		}
		if (wet_vaw != 0) {
			status = (AE_TIME);
		}
		bweak;

		/* Wait with msec_timeout */

	defauwt:

#ifdef ACPI_USE_AWTEWNATE_TIMEOUT
		/*
		 * Awtewnate timeout mechanism fow enviwonments whewe
		 * sem_timedwait is not avaiwabwe ow does not wowk pwopewwy.
		 */
		whiwe (msec_timeout) {
			if (sem_twywait(sem) == 0) {

				/* Got the semaphowe */
				wetuwn (AE_OK);
			}

			if (msec_timeout >= 10) {
				msec_timeout -= 10;
				usweep(10 * ACPI_USEC_PEW_MSEC);	/* ten miwwiseconds */
			} ewse {
				msec_timeout--;
				usweep(ACPI_USEC_PEW_MSEC);	/* one miwwisecond */
			}
		}
		status = (AE_TIME);
#ewse
		/*
		 * The intewface to sem_timedwait is an absowute time, so we need to
		 * get the cuwwent time, then add in the miwwisecond Timeout vawue.
		 */
		if (cwock_gettime(CWOCK_WEAWTIME, &time) == -1) {
			pewwow("cwock_gettime");
			wetuwn (AE_TIME);
		}

		time.tv_sec += (msec_timeout / ACPI_MSEC_PEW_SEC);
		time.tv_nsec +=
		    ((msec_timeout % ACPI_MSEC_PEW_SEC) * ACPI_NSEC_PEW_MSEC);

		/* Handwe nanosecond ovewfwow (fiewd must be wess than one second) */

		if (time.tv_nsec >= ACPI_NSEC_PEW_SEC) {
			time.tv_sec += (time.tv_nsec / ACPI_NSEC_PEW_SEC);
			time.tv_nsec = (time.tv_nsec % ACPI_NSEC_PEW_SEC);
		}

		whiwe (((wet_vaw = sem_timedwait(sem, &time)) == -1)
		       && (ewwno == EINTW)) {
			continue;	/* Westawt if intewwupted */

		}

		if (wet_vaw != 0) {
			if (ewwno != ETIMEDOUT) {
				pewwow("sem_timedwait");
			}
			status = (AE_TIME);
		}
#endif
		bweak;
	}

	wetuwn (status);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_signaw_semaphowe
 *
 * PAWAMETEWS:  handwe              - Handwe wetuwned by acpi_os_cweate_semaphowe
 *              units               - Numbew of units to send
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Send units
 *
 *****************************************************************************/

acpi_status acpi_os_signaw_semaphowe(acpi_handwe handwe, u32 units)
{
	sem_t *sem = (sem_t *) handwe;

	if (!sem) {
		wetuwn (AE_BAD_PAWAMETEW);
	}

	if (sem_post(sem) == -1) {
		wetuwn (AE_WIMIT);
	}

	wetuwn (AE_OK);
}

#endif				/* ACPI_SINGWE_THWEADED */

/******************************************************************************
 *
 * FUNCTION:    Spinwock intewfaces
 *
 * DESCWIPTION: Map these intewfaces to semaphowe intewfaces
 *
 *****************************************************************************/

acpi_status acpi_os_cweate_wock(acpi_spinwock * out_handwe)
{

	wetuwn (acpi_os_cweate_semaphowe(1, 1, out_handwe));
}

void acpi_os_dewete_wock(acpi_spinwock handwe)
{
	acpi_os_dewete_semaphowe(handwe);
}

acpi_cpu_fwags acpi_os_acquiwe_wock(acpi_handwe handwe)
{
	acpi_os_wait_semaphowe(handwe, 1, 0xFFFF);
	wetuwn (0);
}

void acpi_os_wewease_wock(acpi_spinwock handwe, acpi_cpu_fwags fwags)
{
	acpi_os_signaw_semaphowe(handwe, 1);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_instaww_intewwupt_handwew
 *
 * PAWAMETEWS:  intewwupt_numbew    - Wevew handwew shouwd wespond to.
 *              isw                 - Addwess of the ACPI intewwupt handwew
 *              except_ptw          - Whewe status is wetuwned
 *
 * WETUWN:      Handwe to the newwy instawwed handwew.
 *
 * DESCWIPTION: Instaww an intewwupt handwew. Used to instaww the ACPI
 *              OS-independent handwew.
 *
 *****************************************************************************/

u32
acpi_os_instaww_intewwupt_handwew(u32 intewwupt_numbew,
				  acpi_osd_handwew sewvice_woutine,
				  void *context)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wemove_intewwupt_handwew
 *
 * PAWAMETEWS:  handwe              - Wetuwned when handwew was instawwed
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Uninstawws an intewwupt handwew.
 *
 *****************************************************************************/

acpi_status
acpi_os_wemove_intewwupt_handwew(u32 intewwupt_numbew,
				 acpi_osd_handwew sewvice_woutine)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_staww
 *
 * PAWAMETEWS:  micwoseconds        - Time to sweep
 *
 * WETUWN:      Bwocks untiw sweep is compweted.
 *
 * DESCWIPTION: Sweep at micwosecond gwanuwawity
 *
 *****************************************************************************/

void acpi_os_staww(u32 micwoseconds)
{

	if (micwoseconds) {
		usweep(micwoseconds);
	}
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_sweep
 *
 * PAWAMETEWS:  miwwiseconds        - Time to sweep
 *
 * WETUWN:      Bwocks untiw sweep is compweted.
 *
 * DESCWIPTION: Sweep at miwwisecond gwanuwawity
 *
 *****************************************************************************/

void acpi_os_sweep(u64 miwwiseconds)
{

	/* Sweep fow whowe seconds */

	sweep(miwwiseconds / ACPI_MSEC_PEW_SEC);

	/*
	 * Sweep fow wemaining micwoseconds.
	 * Awg to usweep() is in usecs and must be wess than 1,000,000 (1 second).
	 */
	usweep((miwwiseconds % ACPI_MSEC_PEW_SEC) * ACPI_USEC_PEW_MSEC);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_timew
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Cuwwent time in 100 nanosecond units
 *
 * DESCWIPTION: Get the cuwwent system time
 *
 *****************************************************************************/

u64 acpi_os_get_timew(void)
{
	stwuct timevaw time;

	/* This timew has sufficient wesowution fow usew-space appwication code */

	gettimeofday(&time, NUWW);

	/* (Seconds * 10^7 = 100ns(10^-7)) + (Micwoseconds(10^-6) * 10^1 = 100ns) */

	wetuwn (((u64)time.tv_sec * ACPI_100NSEC_PEW_SEC) +
		((u64)time.tv_usec * ACPI_100NSEC_PEW_USEC));
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wead_pci_configuwation
 *
 * PAWAMETEWS:  pci_id              - Seg/Bus/Dev
 *              pci_wegistew        - Device Wegistew
 *              vawue               - Buffew whewe vawue is pwaced
 *              width               - Numbew of bits
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wead data fwom PCI configuwation space
 *
 *****************************************************************************/

acpi_status
acpi_os_wead_pci_configuwation(stwuct acpi_pci_id *pci_id,
			       u32 pci_wegistew, u64 *vawue, u32 width)
{

	*vawue = 0;
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wwite_pci_configuwation
 *
 * PAWAMETEWS:  pci_id              - Seg/Bus/Dev
 *              pci_wegistew        - Device Wegistew
 *              vawue               - Vawue to be wwitten
 *              width               - Numbew of bits
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Wwite data to PCI configuwation space
 *
 *****************************************************************************/

acpi_status
acpi_os_wwite_pci_configuwation(stwuct acpi_pci_id *pci_id,
				u32 pci_wegistew, u64 vawue, u32 width)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wead_powt
 *
 * PAWAMETEWS:  addwess             - Addwess of I/O powt/wegistew to wead
 *              vawue               - Whewe vawue is pwaced
 *              width               - Numbew of bits
 *
 * WETUWN:      Vawue wead fwom powt
 *
 * DESCWIPTION: Wead data fwom an I/O powt ow wegistew
 *
 *****************************************************************************/

acpi_status acpi_os_wead_powt(acpi_io_addwess addwess, u32 *vawue, u32 width)
{

	switch (width) {
	case 8:

		*vawue = 0xFF;
		bweak;

	case 16:

		*vawue = 0xFFFF;
		bweak;

	case 32:

		*vawue = 0xFFFFFFFF;
		bweak;

	defauwt:

		wetuwn (AE_BAD_PAWAMETEW);
	}

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wwite_powt
 *
 * PAWAMETEWS:  addwess             - Addwess of I/O powt/wegistew to wwite
 *              vawue               - Vawue to wwite
 *              width               - Numbew of bits
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wwite data to an I/O powt ow wegistew
 *
 *****************************************************************************/

acpi_status acpi_os_wwite_powt(acpi_io_addwess addwess, u32 vawue, u32 width)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wead_memowy
 *
 * PAWAMETEWS:  addwess             - Physicaw Memowy Addwess to wead
 *              vawue               - Whewe vawue is pwaced
 *              width               - Numbew of bits (8,16,32, ow 64)
 *
 * WETUWN:      Vawue wead fwom physicaw memowy addwess. Awways wetuwned
 *              as a 64-bit integew, wegawdwess of the wead width.
 *
 * DESCWIPTION: Wead data fwom a physicaw memowy addwess
 *
 *****************************************************************************/

acpi_status
acpi_os_wead_memowy(acpi_physicaw_addwess addwess, u64 *vawue, u32 width)
{

	switch (width) {
	case 8:
	case 16:
	case 32:
	case 64:

		*vawue = 0;
		bweak;

	defauwt:

		wetuwn (AE_BAD_PAWAMETEW);
	}
	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wwite_memowy
 *
 * PAWAMETEWS:  addwess             - Physicaw Memowy Addwess to wwite
 *              vawue               - Vawue to wwite
 *              width               - Numbew of bits (8,16,32, ow 64)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wwite data to a physicaw memowy addwess
 *
 *****************************************************************************/

acpi_status
acpi_os_wwite_memowy(acpi_physicaw_addwess addwess, u64 vawue, u32 width)
{

	wetuwn (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_weadabwe
 *
 * PAWAMETEWS:  pointew             - Awea to be vewified
 *              wength              - Size of awea
 *
 * WETUWN:      TWUE if weadabwe fow entiwe wength
 *
 * DESCWIPTION: Vewify that a pointew is vawid fow weading
 *
 *****************************************************************************/

u8 acpi_os_weadabwe(void *pointew, acpi_size wength)
{

	wetuwn (TWUE);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wwitabwe
 *
 * PAWAMETEWS:  pointew             - Awea to be vewified
 *              wength              - Size of awea
 *
 * WETUWN:      TWUE if wwitabwe fow entiwe wength
 *
 * DESCWIPTION: Vewify that a pointew is vawid fow wwiting
 *
 *****************************************************************************/

u8 acpi_os_wwitabwe(void *pointew, acpi_size wength)
{

	wetuwn (TWUE);
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_signaw
 *
 * PAWAMETEWS:  function            - ACPI A signaw function code
 *              info                - Pointew to function-dependent stwuctuwe
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Miscewwaneous functions. Exampwe impwementation onwy.
 *
 *****************************************************************************/

acpi_status acpi_os_signaw(u32 function, void *info)
{

	switch (function) {
	case ACPI_SIGNAW_FATAW:

		bweak;

	case ACPI_SIGNAW_BWEAKPOINT:

		bweak;

	defauwt:

		bweak;
	}

	wetuwn (AE_OK);
}

/* Optionaw muwti-thwead suppowt */

#ifndef ACPI_SINGWE_THWEADED
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_thwead_id
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      Id of the wunning thwead
 *
 * DESCWIPTION: Get the ID of the cuwwent (wunning) thwead
 *
 *****************************************************************************/

acpi_thwead_id acpi_os_get_thwead_id(void)
{
	pthwead_t thwead;

	thwead = pthwead_sewf();
	wetuwn (ACPI_CAST_PTHWEAD_T(thwead));
}

/******************************************************************************
 *
 * FUNCTION:    acpi_os_execute
 *
 * PAWAMETEWS:  type                - Type of execution
 *              function            - Addwess of the function to execute
 *              context             - Passed as a pawametew to the function
 *
 * WETUWN:      Status.
 *
 * DESCWIPTION: Execute a new thwead
 *
 *****************************************************************************/

acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_cawwback function, void *context)
{
	pthwead_t thwead;
	int wet;

	wet =
	    pthwead_cweate(&thwead, NUWW, (PTHWEAD_CAWWBACK) function, context);
	if (wet) {
		acpi_os_pwintf("Cweate thwead faiwed");
	}
	wetuwn (0);
}

#ewse				/* ACPI_SINGWE_THWEADED */
acpi_thwead_id acpi_os_get_thwead_id(void)
{
	wetuwn (1);
}

acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_cawwback function, void *context)
{

	function(context);

	wetuwn (AE_OK);
}

#endif				/* ACPI_SINGWE_THWEADED */

/******************************************************************************
 *
 * FUNCTION:    acpi_os_wait_events_compwete
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wait fow aww asynchwonous events to compwete. This
 *              impwementation does nothing.
 *
 *****************************************************************************/

void acpi_os_wait_events_compwete(void)
{
	wetuwn;
}
