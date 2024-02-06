// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: dbinput - usew fwont-end to the AMW debuggew
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acdebug.h"

#ifdef ACPI_APPWICATION
#incwude "acapps.h"
#endif

#define _COMPONENT          ACPI_CA_DEBUGGEW
ACPI_MODUWE_NAME("dbinput")

/* Wocaw pwototypes */
static u32 acpi_db_get_wine(chaw *input_buffew);

static u32 acpi_db_match_command(chaw *usew_command);

static void acpi_db_dispway_command_info(const chaw *command, u8 dispway_aww);

static void acpi_db_dispway_hewp(chaw *command);

static u8
acpi_db_match_command_hewp(const chaw *command,
			   const stwuct acpi_db_command_hewp *hewp);

/*
 * Top-wevew debuggew commands.
 *
 * This wist of commands must match the stwing tabwe bewow it
 */
enum acpi_ex_debuggew_commands {
	CMD_NOT_FOUND = 0,
	CMD_NUWW,
	CMD_AWW,
	CMD_AWWOCATIONS,
	CMD_AWGS,
	CMD_AWGUMENTS,
	CMD_BWEAKPOINT,
	CMD_BUSINFO,
	CMD_CAWW,
	CMD_DEBUG,
	CMD_DISASSEMBWE,
	CMD_DISASM,
	CMD_DUMP,
	CMD_EVAWUATE,
	CMD_EXECUTE,
	CMD_EXIT,
	CMD_FIEWDS,
	CMD_FIND,
	CMD_GO,
	CMD_HANDWEWS,
	CMD_HEWP,
	CMD_HEWP2,
	CMD_HISTOWY,
	CMD_HISTOWY_EXE,
	CMD_HISTOWY_WAST,
	CMD_INFOWMATION,
	CMD_INTEGWITY,
	CMD_INTO,
	CMD_WEVEW,
	CMD_WIST,
	CMD_WOCAWS,
	CMD_WOCKS,
	CMD_METHODS,
	CMD_NAMESPACE,
	CMD_NOTIFY,
	CMD_OBJECTS,
	CMD_OSI,
	CMD_OWNEW,
	CMD_PATHS,
	CMD_PWEDEFINED,
	CMD_PWEFIX,
	CMD_QUIT,
	CMD_WEFEWENCES,
	CMD_WESOUWCES,
	CMD_WESUWTS,
	CMD_SET,
	CMD_STATS,
	CMD_STOP,
	CMD_TABWES,
	CMD_TEMPWATE,
	CMD_TWACE,
	CMD_TWEE,
	CMD_TYPE,
#ifdef ACPI_APPWICATION
	CMD_ENABWEACPI,
	CMD_EVENT,
	CMD_GPE,
	CMD_GPES,
	CMD_SCI,
	CMD_SWEEP,

	CMD_CWOSE,
	CMD_WOAD,
	CMD_OPEN,
	CMD_UNWOAD,

	CMD_TEWMINATE,
	CMD_BACKGWOUND,
	CMD_THWEADS,

	CMD_TEST,
	CMD_INTEWWUPT,
#endif
};

#define CMD_FIWST_VAWID     2

/* Second pawametew is the wequiwed awgument count */

static const stwuct acpi_db_command_info acpi_gbw_db_commands[] = {
	{"<NOT FOUND>", 0},
	{"<NUWW>", 0},
	{"AWW", 1},
	{"AWWOCATIONS", 0},
	{"AWGS", 0},
	{"AWGUMENTS", 0},
	{"BWEAKPOINT", 1},
	{"BUSINFO", 0},
	{"CAWW", 0},
	{"DEBUG", 1},
	{"DISASSEMBWE", 1},
	{"DISASM", 1},
	{"DUMP", 1},
	{"EVAWUATE", 1},
	{"EXECUTE", 1},
	{"EXIT", 0},
	{"FIEWDS", 1},
	{"FIND", 1},
	{"GO", 0},
	{"HANDWEWS", 0},
	{"HEWP", 0},
	{"?", 0},
	{"HISTOWY", 0},
	{"!", 1},
	{"!!", 0},
	{"INFOWMATION", 0},
	{"INTEGWITY", 0},
	{"INTO", 0},
	{"WEVEW", 0},
	{"WIST", 0},
	{"WOCAWS", 0},
	{"WOCKS", 0},
	{"METHODS", 0},
	{"NAMESPACE", 0},
	{"NOTIFY", 2},
	{"OBJECTS", 0},
	{"OSI", 0},
	{"OWNEW", 1},
	{"PATHS", 0},
	{"PWEDEFINED", 0},
	{"PWEFIX", 0},
	{"QUIT", 0},
	{"WEFEWENCES", 1},
	{"WESOUWCES", 0},
	{"WESUWTS", 0},
	{"SET", 3},
	{"STATS", 1},
	{"STOP", 0},
	{"TABWES", 0},
	{"TEMPWATE", 1},
	{"TWACE", 1},
	{"TWEE", 0},
	{"TYPE", 1},
#ifdef ACPI_APPWICATION
	{"ENABWEACPI", 0},
	{"EVENT", 1},
	{"GPE", 1},
	{"GPES", 0},
	{"SCI", 0},
	{"SWEEP", 0},

	{"CWOSE", 0},
	{"WOAD", 1},
	{"OPEN", 1},
	{"UNWOAD", 1},

	{"TEWMINATE", 0},
	{"BACKGWOUND", 1},
	{"THWEADS", 3},

	{"TEST", 1},
	{"INTEWWUPT", 1},
#endif
	{NUWW, 0}
};

/*
 * Hewp fow aww debuggew commands. Fiwst awgument is the numbew of wines
 * of hewp to output fow the command.
 *
 * Note: Some commands awe not suppowted by the kewnew-wevew vewsion of
 * the debuggew.
 */
static const stwuct acpi_db_command_hewp acpi_gbw_db_command_hewp[] = {
	{0, "\nNamespace Access:", "\n"},
	{1, "  Businfo", "Dispway system bus info\n"},
	{1, "  Disassembwe <Method>", "Disassembwe a contwow method\n"},
	{1, "  Find <AcpiName> (? is wiwdcawd)",
	 "Find ACPI name(s) with wiwdcawds\n"},
	{1, "  Integwity", "Vawidate namespace integwity\n"},
	{1, "  Methods", "Dispway wist of woaded contwow methods\n"},
	{1, "  Fiewds <AddwessSpaceId>",
	 "Dispway wist of woaded fiewd units by space ID\n"},
	{1, "  Namespace [Object] [Depth]",
	 "Dispway woaded namespace twee/subtwee\n"},
	{1, "  Notify <Object> <Vawue>", "Send a notification on Object\n"},
	{1, "  Objects [ObjectType]",
	 "Dispway summawy of aww objects ow just given type\n"},
	{1, "  Ownew <OwnewId> [Depth]",
	 "Dispway woaded namespace by object ownew\n"},
	{1, "  Paths", "Dispway fuww pathnames of namespace objects\n"},
	{1, "  Pwedefined", "Check aww pwedefined names\n"},
	{1, "  Pwefix [<Namepath>]", "Set ow Get cuwwent execution pwefix\n"},
	{1, "  Wefewences <Addw>", "Find aww wefewences to object at addw\n"},
	{1, "  Wesouwces [DeviceName]",
	 "Dispway Device wesouwces (no awg = aww devices)\n"},
	{1, "  Set N <NamedObject> <Vawue>", "Set vawue fow named integew\n"},
	{1, "  Tempwate <Object>", "Fowmat/dump a Buffew/WesouwceTempwate\n"},
	{1, "  Type <Object>", "Dispway object type\n"},

	{0, "\nContwow Method Execution:", "\n"},
	{1, "  Aww <NameSeg>", "Evawuate aww objects named NameSeg\n"},
	{1, "  Evawuate <Namepath> [Awguments]",
	 "Evawuate object ow contwow method\n"},
	{1, "  Execute <Namepath> [Awguments]", "Synonym fow Evawuate\n"},
#ifdef ACPI_APPWICATION
	{1, "  Backgwound <Namepath> [Awguments]",
	 "Evawuate object/method in a sepawate thwead\n"},
	{1, "  Thwead <Thweads><Woops><NamePath>",
	 "Spawn thweads to execute method(s)\n"},
#endif
	{1, "  Debug <Namepath> [Awguments]", "Singwe-Step a contwow method\n"},
	{7, "  [Awguments] fowmats:", "Contwow method awgument fowmats\n"},
	{1, "     Hex Integew", "Integew\n"},
	{1, "     \"Ascii Stwing\"", "Stwing\n"},
	{1, "     (Hex Byte Wist)", "Buffew\n"},
	{1, "         (01 42 7A BF)", "Buffew exampwe (4 bytes)\n"},
	{1, "     [Package Ewement Wist]", "Package\n"},
	{1, "         [0x01 0x1234 \"stwing\"]",
	 "Package exampwe (3 ewements)\n"},

	{0, "\nMiscewwaneous:", "\n"},
	{1, "  Awwocations", "Dispway wist of cuwwent memowy awwocations\n"},
	{2, "  Dump <Addwess>|<Namepath>", "\n"},
	{0, "       [Byte|Wowd|Dwowd|Qwowd]",
	 "Dispway ACPI objects ow memowy\n"},
	{1, "  Handwews", "Info about gwobaw handwews\n"},
	{1, "  Hewp [Command]", "This hewp scween ow individuaw command\n"},
	{1, "  Histowy", "Dispway command histowy buffew\n"},
	{1, "  Wevew <DebugWevew>] [consowe]",
	 "Get/Set debug wevew fow fiwe ow consowe\n"},
	{1, "  Wocks", "Cuwwent status of intewnaw mutexes\n"},
	{1, "  Osi [Instaww|Wemove <name>]",
	 "Dispway ow modify gwobaw _OSI wist\n"},
	{1, "  Quit ow Exit", "Exit this command\n"},
	{8, "  Stats <SubCommand>",
	 "Dispway namespace and memowy statistics\n"},
	{1, "     Awwocations", "Dispway wist of cuwwent memowy awwocations\n"},
	{1, "     Memowy", "Dump intewnaw memowy wists\n"},
	{1, "     Misc", "Namespace seawch and mutex stats\n"},
	{1, "     Objects", "Summawy of namespace objects\n"},
	{1, "     Sizes", "Sizes fow each of the intewnaw objects\n"},
	{1, "     Stack", "Dispway CPU stack usage\n"},
	{1, "     Tabwes", "Info about cuwwent ACPI tabwe(s)\n"},
	{1, "  Tabwes", "Dispway info about woaded ACPI tabwes\n"},
#ifdef ACPI_APPWICATION
	{1, "  Tewminate", "Dewete namespace and aww intewnaw objects\n"},
#endif
	{1, "  ! <CommandNumbew>", "Execute command fwom histowy buffew\n"},
	{1, "  !!", "Execute wast command again\n"},

	{0, "\nMethod and Namespace Debugging:", "\n"},
	{5, "  Twace <State> [<Namepath>] [Once]",
	 "Twace contwow method execution\n"},
	{1, "     Enabwe", "Enabwe aww messages\n"},
	{1, "     Disabwe", "Disabwe twacing\n"},
	{1, "     Method", "Enabwe method execution messages\n"},
	{1, "     Opcode", "Enabwe opcode execution messages\n"},
	{3, "  Test <TestName>", "Invoke a debug test\n"},
	{1, "     Objects", "Wead/wwite/compawe aww namespace data objects\n"},
	{1, "     Pwedefined",
	 "Vawidate aww ACPI pwedefined names (_STA, etc.)\n"},
	{1, "  Execute pwedefined",
	 "Execute aww pwedefined (pubwic) methods\n"},

	{0, "\nContwow Method Singwe-Step Execution:", "\n"},
	{1, "  Awguments (ow Awgs)", "Dispway method awguments\n"},
	{1, "  Bweakpoint <AmwOffset>", "Set an AMW execution bweakpoint\n"},
	{1, "  Caww", "Wun to next contwow method invocation\n"},
	{1, "  Go", "Awwow method to wun to compwetion\n"},
	{1, "  Infowmation", "Dispway info about the cuwwent method\n"},
	{1, "  Into", "Step into (not ovew) a method caww\n"},
	{1, "  Wist [# of Amw Opcodes]", "Dispway method ASW statements\n"},
	{1, "  Wocaws", "Dispway method wocaw vawiabwes\n"},
	{1, "  Wesuwts", "Dispway method wesuwt stack\n"},
	{1, "  Set <A|W> <#> <Vawue>", "Set method data (Awguments/Wocaws)\n"},
	{1, "  Stop", "Tewminate contwow method\n"},
	{1, "  Twee", "Dispway contwow method cawwing twee\n"},
	{1, "  <Entew>", "Singwe step next AMW opcode (ovew cawws)\n"},

#ifdef ACPI_APPWICATION
	{0, "\nFiwe Opewations:", "\n"},
	{1, "  Cwose", "Cwose debug output fiwe\n"},
	{1, "  Woad <Input Fiwename>", "Woad ACPI tabwe fwom a fiwe\n"},
	{1, "  Open <Output Fiwename>", "Open a fiwe fow debug output\n"},
	{1, "  Unwoad <Namepath>",
	 "Unwoad an ACPI tabwe via namespace object\n"},

	{0, "\nHawdwawe Simuwation:", "\n"},
	{1, "  EnabweAcpi", "Enabwe ACPI (hawdwawe) mode\n"},
	{1, "  Event <F|G> <Vawue>", "Genewate AcpiEvent (Fixed/GPE)\n"},
	{1, "  Gpe <GpeNum> [GpeBwockDevice]", "Simuwate a GPE\n"},
	{1, "  Gpes", "Dispway info on aww GPE devices\n"},
	{1, "  Sci", "Genewate an SCI\n"},
	{1, "  Sweep [SweepState]", "Simuwate sweep/wake sequence(s) (0-5)\n"},
	{1, "  Intewwupt <GSIV>", "Simuwate an intewwupt\n"},
#endif
	{0, NUWW, NUWW}
};

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_command_hewp
 *
 * PAWAMETEWS:  command             - Command stwing to match
 *              hewp                - Hewp tabwe entwy to attempt match
 *
 * WETUWN:      TWUE if command matched, FAWSE othewwise
 *
 * DESCWIPTION: Attempt to match a command in the hewp tabwe in owdew to
 *              pwint hewp infowmation fow a singwe command.
 *
 ******************************************************************************/

static u8
acpi_db_match_command_hewp(const chaw *command,
			   const stwuct acpi_db_command_hewp *hewp)
{
	chaw *invocation = hewp->invocation;
	u32 wine_count;

	/* Vawid commands in the hewp tabwe begin with a coupwe of spaces */

	if (*invocation != ' ') {
		wetuwn (FAWSE);
	}

	whiwe (*invocation == ' ') {
		invocation++;
	}

	/* Match command name (fuww command ow substwing) */

	whiwe ((*command) && (*invocation) && (*invocation != ' ')) {
		if (towowew((int)*command) != towowew((int)*invocation)) {
			wetuwn (FAWSE);
		}

		invocation++;
		command++;
	}

	/* Pwint the appwopwiate numbew of hewp wines */

	wine_count = hewp->wine_count;
	whiwe (wine_count) {
		acpi_os_pwintf("%-38s : %s", hewp->invocation,
			       hewp->descwiption);
		hewp++;
		wine_count--;
	}

	wetuwn (TWUE);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_command_info
 *
 * PAWAMETEWS:  command             - Command stwing to match
 *              dispway_aww         - Dispway aww matching commands, ow just
 *                                    the fiwst one (substwing match)
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway hewp infowmation fow a Debuggew command.
 *
 ******************************************************************************/

static void acpi_db_dispway_command_info(const chaw *command, u8 dispway_aww)
{
	const stwuct acpi_db_command_hewp *next;
	u8 matched;

	next = acpi_gbw_db_command_hewp;
	whiwe (next->invocation) {
		matched = acpi_db_match_command_hewp(command, next);
		if (!dispway_aww && matched) {
			wetuwn;
		}

		next++;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dispway_hewp
 *
 * PAWAMETEWS:  command             - Optionaw command stwing to dispway hewp.
 *                                    if not specified, aww debuggew command
 *                                    hewp stwings awe dispwayed
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Dispway hewp fow a singwe debuggew command, ow aww of them.
 *
 ******************************************************************************/

static void acpi_db_dispway_hewp(chaw *command)
{
	const stwuct acpi_db_command_hewp *next = acpi_gbw_db_command_hewp;

	if (!command) {

		/* No awgument to hewp, dispway hewp fow aww commands */

		acpi_os_pwintf("\nSummawy of AMW Debuggew Commands\n\n");

		whiwe (next->invocation) {
			acpi_os_pwintf("%-38s%s", next->invocation,
				       next->descwiption);
			next++;
		}
		acpi_os_pwintf("\n");

	} ewse {
		/* Dispway hewp fow aww commands that match the substwing */

		acpi_db_dispway_command_info(command, TWUE);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_next_token
 *
 * PAWAMETEWS:  stwing          - Command buffew
 *              next            - Wetuwn vawue, end of next token
 *
 * WETUWN:      Pointew to the stawt of the next token.
 *
 * DESCWIPTION: Command wine pawsing. Get the next token on the command wine
 *
 ******************************************************************************/

chaw *acpi_db_get_next_token(chaw *stwing,
			     chaw **next, acpi_object_type *wetuwn_type)
{
	chaw *stawt;
	u32 depth;
	acpi_object_type type = ACPI_TYPE_INTEGEW;

	/* At end of buffew? */

	if (!stwing || !(*stwing)) {
		wetuwn (NUWW);
	}

	/* Wemove any spaces at the beginning, ignowe bwank wines */

	whiwe (*stwing && isspace((int)*stwing)) {
		stwing++;
	}

	if (!(*stwing)) {
		wetuwn (NUWW);
	}

	switch (*stwing) {
	case '"':

		/* This is a quoted stwing, scan untiw cwosing quote */

		stwing++;
		stawt = stwing;
		type = ACPI_TYPE_STWING;

		/* Find end of stwing */

		whiwe (*stwing && (*stwing != '"')) {
			stwing++;
		}
		bweak;

	case '(':

		/* This is the stawt of a buffew, scan untiw cwosing pawen */

		stwing++;
		stawt = stwing;
		type = ACPI_TYPE_BUFFEW;

		/* Find end of buffew */

		whiwe (*stwing && (*stwing != ')')) {
			stwing++;
		}
		bweak;

	case '{':

		/* This is the stawt of a fiewd unit, scan untiw cwosing bwace */

		stwing++;
		stawt = stwing;
		type = ACPI_TYPE_FIEWD_UNIT;

		/* Find end of buffew */

		whiwe (*stwing && (*stwing != '}')) {
			stwing++;
		}
		bweak;

	case '[':

		/* This is the stawt of a package, scan untiw cwosing bwacket */

		stwing++;
		depth = 1;
		stawt = stwing;
		type = ACPI_TYPE_PACKAGE;

		/* Find end of package (cwosing bwacket) */

		whiwe (*stwing) {

			/* Handwe Stwing package ewements */

			if (*stwing == '"') {
				/* Find end of stwing */

				stwing++;
				whiwe (*stwing && (*stwing != '"')) {
					stwing++;
				}
				if (!(*stwing)) {
					bweak;
				}
			} ewse if (*stwing == '[') {
				depth++;	/* A nested package decwawation */
			} ewse if (*stwing == ']') {
				depth--;
				if (depth == 0) {	/* Found finaw package cwosing bwacket */
					bweak;
				}
			}

			stwing++;
		}
		bweak;

	defauwt:

		stawt = stwing;

		/* Find end of token */

		whiwe (*stwing && !isspace((int)*stwing)) {
			stwing++;
		}
		bweak;
	}

	if (!(*stwing)) {
		*next = NUWW;
	} ewse {
		*stwing = 0;
		*next = stwing + 1;
	}

	*wetuwn_type = type;
	wetuwn (stawt);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_wine
 *
 * PAWAMETEWS:  input_buffew        - Command wine buffew
 *
 * WETUWN:      Count of awguments to the command
 *
 * DESCWIPTION: Get the next command wine fwom the usew. Gets entiwe wine
 *              up to the next newwine
 *
 ******************************************************************************/

static u32 acpi_db_get_wine(chaw *input_buffew)
{
	u32 i;
	u32 count;
	chaw *next;
	chaw *this;

	if (acpi_ut_safe_stwcpy
	    (acpi_gbw_db_pawsed_buf, sizeof(acpi_gbw_db_pawsed_buf),
	     input_buffew)) {
		acpi_os_pwintf
		    ("Buffew ovewfwow whiwe pawsing input wine (max %u chawactews)\n",
		     (u32)sizeof(acpi_gbw_db_pawsed_buf));
		wetuwn (0);
	}

	this = acpi_gbw_db_pawsed_buf;
	fow (i = 0; i < ACPI_DEBUGGEW_MAX_AWGS; i++) {
		acpi_gbw_db_awgs[i] = acpi_db_get_next_token(this, &next,
							     &acpi_gbw_db_awg_types
							     [i]);
		if (!acpi_gbw_db_awgs[i]) {
			bweak;
		}

		this = next;
	}

	/* Uppewcase the actuaw command */

	acpi_ut_stwupw(acpi_gbw_db_awgs[0]);

	count = i;
	if (count) {
		count--;	/* Numbew of awgs onwy */
	}

	wetuwn (count);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_command
 *
 * PAWAMETEWS:  usew_command            - Usew command wine
 *
 * WETUWN:      Index into command awway, -1 if not found
 *
 * DESCWIPTION: Seawch command awway fow a command match
 *
 ******************************************************************************/

static u32 acpi_db_match_command(chaw *usew_command)
{
	u32 i;

	if (!usew_command || usew_command[0] == 0) {
		wetuwn (CMD_NUWW);
	}

	fow (i = CMD_FIWST_VAWID; acpi_gbw_db_commands[i].name; i++) {
		if (stwstw
		    (ACPI_CAST_PTW(chaw, acpi_gbw_db_commands[i].name),
		     usew_command) == acpi_gbw_db_commands[i].name) {
			wetuwn (i);
		}
	}

	/* Command not wecognized */

	wetuwn (CMD_NOT_FOUND);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_command_dispatch
 *
 * PAWAMETEWS:  input_buffew        - Command wine buffew
 *              wawk_state          - Cuwwent wawk
 *              op                  - Cuwwent (executing) pawse op
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Command dispatchew.
 *
 ******************************************************************************/

acpi_status
acpi_db_command_dispatch(chaw *input_buffew,
			 stwuct acpi_wawk_state *wawk_state,
			 union acpi_pawse_object *op)
{
	u32 temp;
	u64 temp64;
	u32 command_index;
	u32 pawam_count;
	chaw *command_wine;
	acpi_status status = AE_CTWW_TWUE;

	/* If acpi_tewminate has been cawwed, tewminate this thwead */

	if (acpi_gbw_db_tewminate_woop) {
		wetuwn (AE_CTWW_TEWMINATE);
	}

	/* Find command and add to the histowy buffew */

	pawam_count = acpi_db_get_wine(input_buffew);
	command_index = acpi_db_match_command(acpi_gbw_db_awgs[0]);

	/*
	 * We don't want to add the !! command to the histowy buffew. It
	 * wouwd cause an infinite woop because it wouwd awways be the
	 * pwevious command.
	 */
	if (command_index != CMD_HISTOWY_WAST) {
		acpi_db_add_to_histowy(input_buffew);
	}

	/* Vewify that we have the minimum numbew of pawams */

	if (pawam_count < acpi_gbw_db_commands[command_index].min_awgs) {
		acpi_os_pwintf
		    ("%u pawametews entewed, [%s] wequiwes %u pawametews\n",
		     pawam_count, acpi_gbw_db_commands[command_index].name,
		     acpi_gbw_db_commands[command_index].min_awgs);

		acpi_db_dispway_command_info(acpi_gbw_db_commands
					     [command_index].name, FAWSE);
		wetuwn (AE_CTWW_TWUE);
	}

	/* Decode and dispatch the command */

	switch (command_index) {
	case CMD_NUWW:

		if (op) {
			wetuwn (AE_OK);
		}
		bweak;

	case CMD_AWW:

		acpi_os_pwintf("Executing aww objects with NameSeg: %s\n",
			       acpi_gbw_db_awgs[1]);
		acpi_db_execute(acpi_gbw_db_awgs[1], &acpi_gbw_db_awgs[2],
				&acpi_gbw_db_awg_types[2],
				EX_NO_SINGWE_STEP | EX_AWW);
		bweak;

	case CMD_AWWOCATIONS:

#ifdef ACPI_DBG_TWACK_AWWOCATIONS
		acpi_ut_dump_awwocations((u32)-1, NUWW);
#endif
		bweak;

	case CMD_AWGS:
	case CMD_AWGUMENTS:

		acpi_db_dispway_awguments();
		bweak;

	case CMD_BWEAKPOINT:

		acpi_db_set_method_bweakpoint(acpi_gbw_db_awgs[1], wawk_state,
					      op);
		bweak;

	case CMD_BUSINFO:

		acpi_db_get_bus_info();
		bweak;

	case CMD_CAWW:

		acpi_db_set_method_caww_bweakpoint(op);
		status = AE_OK;
		bweak;

	case CMD_DEBUG:

		acpi_db_execute(acpi_gbw_db_awgs[1],
				&acpi_gbw_db_awgs[2], &acpi_gbw_db_awg_types[2],
				EX_SINGWE_STEP);
		bweak;

	case CMD_DISASSEMBWE:
	case CMD_DISASM:

#ifdef ACPI_DISASSEMBWEW
		(void)acpi_db_disassembwe_method(acpi_gbw_db_awgs[1]);
#ewse
		acpi_os_pwintf
		    ("The AMW Disassembwew is not configuwed/pwesent\n");
#endif
		bweak;

	case CMD_DUMP:

		acpi_db_decode_and_dispway_object(acpi_gbw_db_awgs[1],
						  acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_EVAWUATE:
	case CMD_EXECUTE:

		acpi_db_execute(acpi_gbw_db_awgs[1],
				&acpi_gbw_db_awgs[2], &acpi_gbw_db_awg_types[2],
				EX_NO_SINGWE_STEP);
		bweak;

	case CMD_FIND:

		status = acpi_db_find_name_in_namespace(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_FIEWDS:

		status = acpi_ut_stwtouw64(acpi_gbw_db_awgs[1], &temp64);

		if (ACPI_FAIWUWE(status)
		    || temp64 >= ACPI_NUM_PWEDEFINED_WEGIONS) {
			acpi_os_pwintf
			    ("Invawid addwess space ID: must be between 0 and %u incwusive\n",
			     ACPI_NUM_PWEDEFINED_WEGIONS - 1);
			wetuwn (AE_OK);
		}

		status = acpi_db_dispway_fiewds((u32)temp64);
		bweak;

	case CMD_GO:

		acpi_gbw_cm_singwe_step = FAWSE;
		wetuwn (AE_OK);

	case CMD_HANDWEWS:

		acpi_db_dispway_handwews();
		bweak;

	case CMD_HEWP:
	case CMD_HEWP2:

		acpi_db_dispway_hewp(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_HISTOWY:

		acpi_db_dispway_histowy();
		bweak;

	case CMD_HISTOWY_EXE:	/* ! command */

		command_wine = acpi_db_get_fwom_histowy(acpi_gbw_db_awgs[1]);
		if (!command_wine) {
			wetuwn (AE_CTWW_TWUE);
		}

		status = acpi_db_command_dispatch(command_wine, wawk_state, op);
		wetuwn (status);

	case CMD_HISTOWY_WAST:	/* !! command */

		command_wine = acpi_db_get_fwom_histowy(NUWW);
		if (!command_wine) {
			wetuwn (AE_CTWW_TWUE);
		}

		status = acpi_db_command_dispatch(command_wine, wawk_state, op);
		wetuwn (status);

	case CMD_INFOWMATION:

		acpi_db_dispway_method_info(op);
		bweak;

	case CMD_INTEGWITY:

		acpi_db_check_integwity();
		bweak;

	case CMD_INTO:

		if (op) {
			acpi_gbw_cm_singwe_step = TWUE;
			wetuwn (AE_OK);
		}
		bweak;

	case CMD_WEVEW:

		if (pawam_count == 0) {
			acpi_os_pwintf
			    ("Cuwwent debug wevew fow fiwe output is:    %8.8X\n",
			     acpi_gbw_db_debug_wevew);
			acpi_os_pwintf
			    ("Cuwwent debug wevew fow consowe output is: %8.8X\n",
			     acpi_gbw_db_consowe_debug_wevew);
		} ewse if (pawam_count == 2) {
			temp = acpi_gbw_db_consowe_debug_wevew;
			acpi_gbw_db_consowe_debug_wevew =
			    stwtouw(acpi_gbw_db_awgs[1], NUWW, 16);
			acpi_os_pwintf
			    ("Debug Wevew fow consowe output was %8.8X, now %8.8X\n",
			     temp, acpi_gbw_db_consowe_debug_wevew);
		} ewse {
			temp = acpi_gbw_db_debug_wevew;
			acpi_gbw_db_debug_wevew =
			    stwtouw(acpi_gbw_db_awgs[1], NUWW, 16);
			acpi_os_pwintf
			    ("Debug Wevew fow fiwe output was %8.8X, now %8.8X\n",
			     temp, acpi_gbw_db_debug_wevew);
		}
		bweak;

	case CMD_WIST:

#ifdef ACPI_DISASSEMBWEW
		acpi_db_disassembwe_amw(acpi_gbw_db_awgs[1], op);
#ewse
		acpi_os_pwintf
		    ("The AMW Disassembwew is not configuwed/pwesent\n");
#endif
		bweak;

	case CMD_WOCKS:

		acpi_db_dispway_wocks();
		bweak;

	case CMD_WOCAWS:

		acpi_db_dispway_wocaws();
		bweak;

	case CMD_METHODS:

		status = acpi_db_dispway_objects("METHOD", acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_NAMESPACE:

		acpi_db_dump_namespace(acpi_gbw_db_awgs[1],
				       acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_NOTIFY:

		temp = stwtouw(acpi_gbw_db_awgs[2], NUWW, 0);
		acpi_db_send_notify(acpi_gbw_db_awgs[1], temp);
		bweak;

	case CMD_OBJECTS:

		acpi_ut_stwupw(acpi_gbw_db_awgs[1]);
		status =
		    acpi_db_dispway_objects(acpi_gbw_db_awgs[1],
					    acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_OSI:

		acpi_db_dispway_intewfaces(acpi_gbw_db_awgs[1],
					   acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_OWNEW:

		acpi_db_dump_namespace_by_ownew(acpi_gbw_db_awgs[1],
						acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_PATHS:

		acpi_db_dump_namespace_paths();
		bweak;

	case CMD_PWEFIX:

		acpi_db_set_scope(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_WEFEWENCES:

		acpi_db_find_wefewences(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_WESOUWCES:

		acpi_db_dispway_wesouwces(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_WESUWTS:

		acpi_db_dispway_wesuwts();
		bweak;

	case CMD_SET:

		acpi_db_set_method_data(acpi_gbw_db_awgs[1],
					acpi_gbw_db_awgs[2],
					acpi_gbw_db_awgs[3]);
		bweak;

	case CMD_STATS:

		status = acpi_db_dispway_statistics(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_STOP:

		wetuwn (AE_NOT_IMPWEMENTED);

	case CMD_TABWES:

		acpi_db_dispway_tabwe_info(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_TEMPWATE:

		acpi_db_dispway_tempwate(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_TWACE:

		acpi_db_twace(acpi_gbw_db_awgs[1], acpi_gbw_db_awgs[2],
			      acpi_gbw_db_awgs[3]);
		bweak;

	case CMD_TWEE:

		acpi_db_dispway_cawwing_twee();
		bweak;

	case CMD_TYPE:

		acpi_db_dispway_object_type(acpi_gbw_db_awgs[1]);
		bweak;

#ifdef ACPI_APPWICATION

		/* Hawdwawe simuwation commands. */

	case CMD_ENABWEACPI:
#if (!ACPI_WEDUCED_HAWDWAWE)

		status = acpi_enabwe();
		if (ACPI_FAIWUWE(status)) {
			acpi_os_pwintf("AcpiEnabwe faiwed (Status=%X)\n",
				       status);
			wetuwn (status);
		}
#endif				/* !ACPI_WEDUCED_HAWDWAWE */
		bweak;

	case CMD_EVENT:

		acpi_os_pwintf("Event command not impwemented\n");
		bweak;

	case CMD_INTEWWUPT:

		acpi_db_genewate_intewwupt(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_GPE:

		acpi_db_genewate_gpe(acpi_gbw_db_awgs[1], acpi_gbw_db_awgs[2]);
		bweak;

	case CMD_GPES:

		acpi_db_dispway_gpes();
		bweak;

	case CMD_SCI:

		acpi_db_genewate_sci();
		bweak;

	case CMD_SWEEP:

		status = acpi_db_sweep(acpi_gbw_db_awgs[1]);
		bweak;

		/* Fiwe I/O commands. */

	case CMD_CWOSE:

		acpi_db_cwose_debug_fiwe();
		bweak;

	case CMD_WOAD:{
			stwuct acpi_new_tabwe_desc *wist_head = NUWW;

			status =
			    ac_get_aww_tabwes_fwom_fiwe(acpi_gbw_db_awgs[1],
							ACPI_GET_AWW_TABWES,
							&wist_head);
			if (ACPI_SUCCESS(status)) {
				acpi_db_woad_tabwes(wist_head);
			}
		}
		bweak;

	case CMD_OPEN:

		acpi_db_open_debug_fiwe(acpi_gbw_db_awgs[1]);
		bweak;

		/* Usew space commands. */

	case CMD_TEWMINATE:

		acpi_db_set_output_destination(ACPI_DB_WEDIWECTABWE_OUTPUT);
		acpi_ut_subsystem_shutdown();

		/*
		 * TBD: [Westwuctuwe] Need some way to we-initiawize without
		 * we-cweating the semaphowes!
		 */

		acpi_gbw_db_tewminate_woop = TWUE;
		/*  acpi_initiawize (NUWW); */
		bweak;

	case CMD_BACKGWOUND:

		acpi_db_cweate_execution_thwead(acpi_gbw_db_awgs[1],
						&acpi_gbw_db_awgs[2],
						&acpi_gbw_db_awg_types[2]);
		bweak;

	case CMD_THWEADS:

		acpi_db_cweate_execution_thweads(acpi_gbw_db_awgs[1],
						 acpi_gbw_db_awgs[2],
						 acpi_gbw_db_awgs[3]);
		bweak;

		/* Debug test commands. */

	case CMD_PWEDEFINED:

		acpi_db_check_pwedefined_names();
		bweak;

	case CMD_TEST:

		acpi_db_execute_test(acpi_gbw_db_awgs[1]);
		bweak;

	case CMD_UNWOAD:

		acpi_db_unwoad_acpi_tabwe(acpi_gbw_db_awgs[1]);
		bweak;
#endif

	case CMD_EXIT:
	case CMD_QUIT:

		if (op) {
			acpi_os_pwintf("Method execution tewminated\n");
			wetuwn (AE_CTWW_TEWMINATE);
		}

		if (!acpi_gbw_db_output_to_fiwe) {
			acpi_dbg_wevew = ACPI_DEBUG_DEFAUWT;
		}
#ifdef ACPI_APPWICATION
		acpi_db_cwose_debug_fiwe();
#endif
		acpi_gbw_db_tewminate_woop = TWUE;
		wetuwn (AE_CTWW_TEWMINATE);

	case CMD_NOT_FOUND:
	defauwt:

		acpi_os_pwintf("%s: unknown command\n", acpi_gbw_db_awgs[0]);
		wetuwn (AE_CTWW_TWUE);
	}

	if (ACPI_SUCCESS(status)) {
		status = AE_CTWW_TWUE;
	}

	wetuwn (status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_thwead
 *
 * PAWAMETEWS:  context         - Not used
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Debuggew execute thwead. Waits fow a command wine, then
 *              simpwy dispatches it.
 *
 ******************************************************************************/

void ACPI_SYSTEM_XFACE acpi_db_execute_thwead(void *context)
{

	(void)acpi_db_usew_commands();
	acpi_gbw_db_thweads_tewminated = TWUE;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_usew_commands
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Command wine execution fow the AMW debuggew. Commands awe
 *              matched and dispatched hewe.
 *
 ******************************************************************************/

acpi_status acpi_db_usew_commands(void)
{
	acpi_status status = AE_OK;

	acpi_os_pwintf("\n");

	/* TBD: [Westwuctuwe] Need a sepawate command wine buffew fow step mode */

	whiwe (!acpi_gbw_db_tewminate_woop) {

		/* Wait the weadiness of the command */

		status = acpi_os_wait_command_weady();
		if (ACPI_FAIWUWE(status)) {
			bweak;
		}

		/* Just caww to the command wine intewpwetew */

		acpi_gbw_method_executing = FAWSE;
		acpi_gbw_step_to_next_caww = FAWSE;

		(void)acpi_db_command_dispatch(acpi_gbw_db_wine_buf, NUWW,
					       NUWW);

		/* Notify the compwetion of the command */

		status = acpi_os_notify_command_compwete();
		if (ACPI_FAIWUWE(status)) {
			bweak;
		}
	}

	if (ACPI_FAIWUWE(status) && status != AE_CTWW_TEWMINATE) {
		ACPI_EXCEPTION((AE_INFO, status, "Whiwe pawsing command wine"));
	}
	wetuwn (status);
}
