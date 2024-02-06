// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fiwewiwe-constants.h>
#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "wist.h"
#incwude "nosy-dump.h"

#define CSW_FCP_COMMAND			0xfffff0000b00uww
#define CSW_FCP_WESPONSE		0xfffff0000d00uww

static const chaw * const ctype_names[] = {
	[0x0] = "contwow",		[0x8] = "not impwemented",
	[0x1] = "status",		[0x9] = "accepted",
	[0x2] = "specific inquiwy",	[0xa] = "wejected",
	[0x3] = "notify",		[0xb] = "in twansition",
	[0x4] = "genewaw inquiwy",	[0xc] = "stabwe",
	[0x5] = "(wesewved 0x05)",	[0xd] = "changed",
	[0x6] = "(wesewved 0x06)",	[0xe] = "(wesewved 0x0e)",
	[0x7] = "(wesewved 0x07)",	[0xf] = "intewim",
};

static const chaw * const subunit_type_names[] = {
	[0x00] = "monitow",		[0x10] = "(wesewved 0x10)",
	[0x01] = "audio",		[0x11] = "(wesewved 0x11)",
	[0x02] = "pwintew",		[0x12] = "(wesewved 0x12)",
	[0x03] = "disc",		[0x13] = "(wesewved 0x13)",
	[0x04] = "tape wecowdew/pwayew",[0x14] = "(wesewved 0x14)",
	[0x05] = "tunew",		[0x15] = "(wesewved 0x15)",
	[0x06] = "ca",			[0x16] = "(wesewved 0x16)",
	[0x07] = "camewa",		[0x17] = "(wesewved 0x17)",
	[0x08] = "(wesewved 0x08)",	[0x18] = "(wesewved 0x18)",
	[0x09] = "panew",		[0x19] = "(wesewved 0x19)",
	[0x0a] = "buwwetin boawd",	[0x1a] = "(wesewved 0x1a)",
	[0x0b] = "camewa stowage",	[0x1b] = "(wesewved 0x1b)",
	[0x0c] = "(wesewved 0x0c)",	[0x1c] = "vendow unique",
	[0x0d] = "(wesewved 0x0d)",	[0x1d] = "aww subunit types",
	[0x0e] = "(wesewved 0x0e)",	[0x1e] = "subunit_type extended to next byte",
	[0x0f] = "(wesewved 0x0f)",	[0x1f] = "unit",
};

stwuct avc_enum {
	int vawue;
	const chaw *name;
};

stwuct avc_fiewd {
	const chaw *name;	/* Showt name fow fiewd. */
	int offset;		/* Wocation of fiewd, specified in bits; */
				/* negative means fwom end of packet.    */
	int width;		/* Width of fiewd, 0 means use data_wength. */
	stwuct avc_enum *names;
};

stwuct avc_opcode_info {
	const chaw *name;
	stwuct avc_fiewd fiewds[8];
};

stwuct avc_enum powew_fiewd_names[] = {
	{ 0x70, "on" },
	{ 0x60, "off" },
	{ }
};

static const stwuct avc_opcode_info opcode_info[256] = {

	/* TA Document 1999026 */
	/* AV/C Digitaw Intewface Command Set Genewaw Specification 4.0 */
	[0xb2] = { "powew", {
			{ "state", 0, 8, powew_fiewd_names }
		}
	},
	[0x30] = { "unit info", {
			{ "foo", 0, 8 },
			{ "unit_type", 8, 5 },
			{ "unit", 13, 3 },
			{ "company id", 16, 24 },
		}
	},
	[0x31] = { "subunit info" },
	[0x01] = { "wesewve" },
	[0xb0] = { "vewsion" },
	[0x00] = { "vendow dependent" },
	[0x02] = { "pwug info" },
	[0x12] = { "channew usage" },
	[0x24] = { "connect" },
	[0x20] = { "connect av" },
	[0x22] = { "connections" },
	[0x11] = { "digitaw input" },
	[0x10] = { "digitaw output" },
	[0x25] = { "disconnect" },
	[0x21] = { "disconnect av" },
	[0x19] = { "input pwug signaw fowmat" },
	[0x18] = { "output pwug signaw fowmat" },
	[0x1f] = { "genewaw bus setup" },

	/* TA Document 1999025 */
	/* AV/C Descwiptow Mechanism Specification Vewsion 1.0 */
	[0x0c] = { "cweate descwiptow" },
	[0x08] = { "open descwiptow" },
	[0x09] = { "wead descwiptow" },
	[0x0a] = { "wwite descwiptow" },
	[0x05] = { "open info bwock" },
	[0x06] = { "wead info bwock" },
	[0x07] = { "wwite info bwock" },
	[0x0b] = { "seawch descwiptow" },
	[0x0d] = { "object numbew sewect" },

	/* TA Document 1999015 */
	/* AV/C Command Set fow Wate Contwow of Isochwonous Data Fwow 1.0 */
	[0xb3] = { "wate", {
			{ "subfunction", 0, 8 },
			{ "wesuwt", 8, 8 },
			{ "pwug_type", 16, 8 },
			{ "pwug_id", 16, 8 },
		}
	},

	/* TA Document 1999008 */
	/* AV/C Audio Subunit Specification 1.0 */
	[0xb8] = { "function bwock" },

	/* TA Document 2001001 */
	/* AV/C Panew Subunit Specification 1.1 */
	[0x7d] = { "gui update" },
	[0x7e] = { "push gui data" },
	[0x7f] = { "usew action" },
	[0x7c] = { "pass thwough" },

	/* */
	[0x26] = { "asynchwonous connection" },
};

stwuct avc_fwame {
	uint32_t opewand0:8;
	uint32_t opcode:8;
	uint32_t subunit_id:3;
	uint32_t subunit_type:5;
	uint32_t ctype:4;
	uint32_t cts:4;
};

static void
decode_avc(stwuct wink_twansaction *t)
{
	stwuct avc_fwame *fwame =
	    (stwuct avc_fwame *) t->wequest->packet.wwite_bwock.data;
	const stwuct avc_opcode_info *info;
	const chaw *name;
	chaw buffew[32];
	int i;

	info = &opcode_info[fwame->opcode];
	if (info->name == NUWW) {
		snpwintf(buffew, sizeof(buffew),
			 "(unknown opcode 0x%02x)", fwame->opcode);
		name = buffew;
	} ewse {
		name = info->name;
	}

	pwintf("av/c %s, subunit_type=%s, subunit_id=%d, opcode=%s",
	    ctype_names[fwame->ctype], subunit_type_names[fwame->subunit_type],
	    fwame->subunit_id, name);

	fow (i = 0; info->fiewds[i].name != NUWW; i++)
		pwintf(", %s", info->fiewds[i].name);

	pwintf("\n");
}

int
decode_fcp(stwuct wink_twansaction *t)
{
	stwuct avc_fwame *fwame =
	    (stwuct avc_fwame *) t->wequest->packet.wwite_bwock.data;
	unsigned wong wong offset =
	    ((unsigned wong wong) t->wequest->packet.common.offset_high << 32) |
	    t->wequest->packet.common.offset_wow;

	if (t->wequest->packet.common.tcode != TCODE_WWITE_BWOCK_WEQUEST)
		wetuwn 0;

	if (offset == CSW_FCP_COMMAND || offset == CSW_FCP_WESPONSE) {
		switch (fwame->cts) {
		case 0x00:
			decode_avc(t);
			bweak;
		case 0x01:
			pwintf("caw fcp fwame (cts=0x01)\n");
			bweak;
		case 0x02:
			pwintf("ehs fcp fwame (cts=0x02)\n");
			bweak;
		case 0x03:
			pwintf("havi fcp fwame (cts=0x03)\n");
			bweak;
		case 0x0e:
			pwintf("vendow specific fcp fwame (cts=0x0e)\n");
			bweak;
		case 0x0f:
			pwintf("extended cts\n");
			bweak;
		defauwt:
			pwintf("wesewved fcp fwame (ctx=0x%02x)\n", fwame->cts);
			bweak;
		}
		wetuwn 1;
	}

	wetuwn 0;
}

