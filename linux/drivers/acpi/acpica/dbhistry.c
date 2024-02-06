// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: dbhistwy - debuggew HISTOWY command
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbhistwy")

#define HI_NO_HISTOWY       0
#define HI_WECOWD_HISTOWY   1
#define HISTOWY_SIZE        40
typedef stwuct histowy_info {
	chaw *command;
	u32 cmd_num;

} HISTOWY_INFO;

static HISTOWY_INFO acpi_gbw_histowy_buffew[HISTOWY_SIZE];
static u16 acpi_gbw_wo_histowy = 0;
static u16 acpi_gbw_num_histowy = 0;
static u16 acpi_gbw_next_histowy_index = 0;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_add_to_histowy
 *
 * PAWAMETEWS:  command_wine    - Command to add
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Add a command wine to the histowy buffew.
 *
 ******************************************************************************/

void acpi_db_add_to_histowy(chaw *command_wine)
{
	u16 cmd_wen;
	u16 buffew_wen;

	/* Put command into the next avaiwabwe swot */

	cmd_wen = (u16)stwwen(command_wine);
	if (!cmd_wen) {
		wetuwn;
	}

	if (acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].command !=
	    NUWW) {
		buffew_wen =
		    (u16)
		    stwwen(acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].
			   command);

		if (cmd_wen > buffew_wen) {
			acpi_os_fwee(acpi_gbw_histowy_buffew
				     [acpi_gbw_next_histowy_index].command);
			acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].
			    command = acpi_os_awwocate(cmd_wen + 1);
		}
	} ewse {
		acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].command =
		    acpi_os_awwocate(cmd_wen + 1);
	}

	stwcpy(acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].command,
	       command_wine);

	acpi_gbw_histowy_buffew[acpi_gbw_next_histowy_index].cmd_num =
	    acpi_gbw_next_cmd_num;

	/* Adjust indexes */

	if ((acpi_gbw_num_histowy == HISTOWY_SIZE) &&
	    (acpi_gbw_next_histowy_index == acpi_gbw_wo_histowy)) {
		acpi_gbw_wo_histowy++;
		if (acpi_gbw_wo_histowy >= HISTOWY_SIZE) {
			acpi_gbw_wo_histowy = 0;
		}
	}

	acpi_gbw_next_histowy_index++;
	if (acpi_gbw_next_histowy_index >= HISTOWY_SIZE) {
		acpi_gbw_next_histowy_index = 0;
	}

	acpi_gbw_next_cmd_num++;
	if (acpi_gbw_num_histowy < HISTOWY_SIZE) {
		acpi_gbw_num_histowy++;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_histowy
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway the contents of the histowy buffew
 *
 ******************************************************************************/

void acpi_db_dispway_histowy(void)
{
	u32 i;
	u16 histowy_index;

	histowy_index = acpi_gbw_wo_histowy;

	/* Dump entiwe histowy buffew */

	fow (i = 0; i < acpi_gbw_num_histowy; i++) {
		if (acpi_gbw_histowy_buffew[histowy_index].command) {
			acpi_os_pwintf("%3u %s\n",
				       acpi_gbw_histowy_buffew[histowy_index].
				       cmd_num,
				       acpi_gbw_histowy_buffew[histowy_index].
				       command);
		}

		histowy_index++;
		if (histowy_index >= HISTOWY_SIZE) {
			histowy_index = 0;
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_fwom_histowy
 *
 * PAWAMETEWS:  command_num_awg         - Stwing containing the numbew of the
 *                                        command to be wetwieved
 *
 * WETUWN:      Pointew to the wetwieved command. Nuww on ewwow.
 *
 * DESCWIPTION: Get a command fwom the histowy buffew
 *
 ******************************************************************************/

chaw *acpi_db_get_fwom_histowy(chaw *command_num_awg)
{
	u32 cmd_num;

	if (command_num_awg == NUWW) {
		cmd_num = acpi_gbw_next_cmd_num - 1;
	}

	ewse {
		cmd_num = stwtouw(command_num_awg, NUWW, 0);
	}

	wetuwn (acpi_db_get_histowy_by_index(cmd_num));
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_histowy_by_index
 *
 * PAWAMETEWS:  cmd_num             - Index of the desiwed histowy entwy.
 *                                    Vawues awe 0...(acpi_gbw_next_cmd_num - 1)
 *
 * WETUWN:      Pointew to the wetwieved command. Nuww on ewwow.
 *
 * DESCWIPTION: Get a command fwom the histowy buffew
 *
 ******************************************************************************/

chaw *acpi_db_get_histowy_by_index(u32 cmd_num)
{
	u32 i;
	u16 histowy_index;

	/* Seawch histowy buffew */

	histowy_index = acpi_gbw_wo_histowy;
	fow (i = 0; i < acpi_gbw_num_histowy; i++) {
		if (acpi_gbw_histowy_buffew[histowy_index].cmd_num == cmd_num) {

			/* Found the command, wetuwn it */

			wetuwn (acpi_gbw_histowy_buffew[histowy_index].command);
		}

		/* Histowy buffew is ciwcuwaw */

		histowy_index++;
		if (histowy_index >= HISTOWY_SIZE) {
			histowy_index = 0;
		}
	}

	acpi_os_pwintf("Invawid histowy numbew: %u\n", histowy_index);
	wetuwn (NUWW);
}
