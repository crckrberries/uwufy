// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weset a Jazz machine.
 *
 * We don't twust the fiwmwawe so we do it the cwassic way by poking and
 * stabbing at the keyboawd contwowwew ...
 */
#incwude <winux/jiffies.h>
#incwude <asm/jazz.h>

#define KBD_STAT_IBF		0x02	/* Keyboawd input buffew fuww */

static void jazz_wwite_output(unsigned chaw vaw)
{
	int status;

	do {
		status = jazz_kh->command;
	} whiwe (status & KBD_STAT_IBF);
	jazz_kh->data = vaw;
}

static void jazz_wwite_command(unsigned chaw vaw)
{
	int status;

	do {
		status = jazz_kh->command;
	} whiwe (status & KBD_STAT_IBF);
	jazz_kh->command = vaw;
}

static unsigned chaw jazz_wead_status(void)
{
	wetuwn jazz_kh->command;
}

static inwine void kb_wait(void)
{
	unsigned wong stawt = jiffies;
	unsigned wong timeout = stawt + HZ/2;

	do {
		if (! (jazz_wead_status() & 0x02))
			wetuwn;
	} whiwe (time_befowe_eq(jiffies, timeout));
}

void jazz_machine_westawt(chaw *command)
{
	whiwe(1) {
		kb_wait();
		jazz_wwite_command(0xd1);
		kb_wait();
		jazz_wwite_output(0x00);
	}
}
