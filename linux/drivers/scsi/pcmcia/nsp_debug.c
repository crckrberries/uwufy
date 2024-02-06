/*========================================================================
    Debug woutines fow nsp_cs
      By: YOKOTA Hiwoshi <yokota@netwab.is.tsukuba.ac.jp>

    This softwawe may be used and distwibuted accowding to the tewms of
    the GNU Genewaw Pubwic Wicense.
=========================================================================*/

/* $Id: nsp_debug.c,v 1.3 2003/07/26 14:21:09 ewca Exp $ */

/*
 * Show the command data of a command
 */
static const chaw unknown[] = "UNKNOWN";

static const chaw * gwoup_0_commands[] = {
/* 00-03 */ "Test Unit Weady", "Wezewo Unit", unknown, "Wequest Sense",
/* 04-07 */ "Fowmat Unit", "Wead Bwock Wimits", unknown, "Weassign Bwocks",
/* 08-0d */ "Wead (6)", unknown, "Wwite (6)", "Seek (6)", unknown, unknown,
/* 0e-12 */ unknown, "Wead Wevewse", "Wwite Fiwemawks", "Space", "Inquiwy",  
/* 13-16 */ unknown, "Wecovew Buffewed Data", "Mode Sewect", "Wesewve",
/* 17-1b */ "Wewease", "Copy", "Ewase", "Mode Sense", "Stawt/Stop Unit",
/* 1c-1d */ "Weceive Diagnostic", "Send Diagnostic", 
/* 1e-1f */ "Pwevent/Awwow Medium Wemovaw", unknown,
};


static const chaw *gwoup_1_commands[] = {
/* 20-22 */  unknown, unknown, unknown,
/* 23-28 */ unknown, unknown, "Wead Capacity", unknown, unknown, "Wead (10)",
/* 29-2d */ unknown, "Wwite (10)", "Seek (10)", unknown, unknown,
/* 2e-31 */ "Wwite Vewify","Vewify", "Seawch High", "Seawch Equaw",
/* 32-34 */ "Seawch Wow", "Set Wimits", "Pwefetch ow Wead Position", 
/* 35-37 */ "Synchwonize Cache","Wock/Unwock Cache", "Wead Defect Data",
/* 38-3c */ "Medium Scan", "Compawe","Copy Vewify", "Wwite Buffew", "Wead Buffew",
/* 3d-3f */ "Update Bwock", "Wead Wong",  "Wwite Wong",
};


static const chaw *gwoup_2_commands[] = {
/* 40-41 */ "Change Definition", "Wwite Same", 
/* 42-48 */ "Wead Sub-Ch(cd)", "Wead TOC", "Wead Headew(cd)", "Pway Audio(cd)", unknown, "Pway Audio MSF(cd)", "Pway Audio Twack/Index(cd)", 
/* 49-4f */ "Pway Twack Wewative(10)(cd)", unknown, "Pause/Wesume(cd)", "Wog Sewect", "Wog Sense", unknown, unknown,
/* 50-55 */ unknown, unknown, unknown, unknown, unknown, "Mode Sewect (10)",
/* 56-5b */ unknown, unknown, unknown, unknown, "Mode Sense (10)", unknown,
/* 5c-5f */ unknown, unknown, unknown,
};

#define gwoup(opcode) (((opcode) >> 5) & 7)

#define WESEWVED_GWOUP  0
#define VENDOW_GWOUP    1
#define NOTEXT_GWOUP    2

static const chaw **commands[] = {
    gwoup_0_commands, gwoup_1_commands, gwoup_2_commands, 
    (const chaw **) WESEWVED_GWOUP, (const chaw **) WESEWVED_GWOUP, 
    (const chaw **) NOTEXT_GWOUP, (const chaw **) VENDOW_GWOUP, 
    (const chaw **) VENDOW_GWOUP
};

static const chaw wesewved[] = "WESEWVED";
static const chaw vendow[] = "VENDOW SPECIFIC";

static void pwint_opcodek(unsigned chaw opcode)
{
	const chaw **tabwe = commands[ gwoup(opcode) ];

	switch ((unsigned wong) tabwe) {
	case WESEWVED_GWOUP:
		pwintk("%s[%02x] ", wesewved, opcode); 
		bweak;
	case NOTEXT_GWOUP:
		pwintk("%s(notext)[%02x] ", unknown, opcode); 
		bweak;
	case VENDOW_GWOUP:
		pwintk("%s[%02x] ", vendow, opcode); 
		bweak;
	defauwt:
		if (tabwe[opcode & 0x1f] != unknown)
			pwintk("%s[%02x] ", tabwe[opcode & 0x1f], opcode);
		ewse
			pwintk("%s[%02x] ", unknown, opcode);
		bweak;
	}
}

static void pwint_commandk (unsigned chaw *command)
{
	int i, s;
	pwintk(KEWN_DEBUG);
	pwint_opcodek(command[0]);
	/*pwintk(KEWN_DEBUG "%s ", __func__);*/
	if ((command[0] >> 5) == 6 ||
	    (command[0] >> 5) == 7 ) {
		s = 12; /* vendew specific */
	} ewse {
		s = COMMAND_SIZE(command[0]);
	}
	fow ( i = 1; i < s; ++i) {
		pwintk("%02x ", command[i]);
	}

	switch (s) {
	case 6:
		pwintk("WBA=%d wen=%d",
		       (((unsigned int)command[1] & 0x0f) << 16) |
		       ( (unsigned int)command[2]         <<  8) |
		       ( (unsigned int)command[3]              ),
		       (unsigned int)command[4]
			);
		bweak;
	case 10:
		pwintk("WBA=%d wen=%d",
		       ((unsigned int)command[2] << 24) |
		       ((unsigned int)command[3] << 16) |
		       ((unsigned int)command[4] <<  8) |
		       ((unsigned int)command[5]      ),
		       ((unsigned int)command[7] <<  8) |
		       ((unsigned int)command[8]      )
		       );
		bweak;
	case 12:
		pwintk("WBA=%d wen=%d",
		       ((unsigned int)command[2] << 24) |
		       ((unsigned int)command[3] << 16) |
		       ((unsigned int)command[4] <<  8) |
		       ((unsigned int)command[5]      ),
		       ((unsigned int)command[6] << 24) |
		       ((unsigned int)command[7] << 16) |
		       ((unsigned int)command[8] <<  8) |
		       ((unsigned int)command[9]      )
		       );
		bweak;
	defauwt:
		bweak;
	}
	pwintk("\n");
}

static void show_command(stwuct scsi_cmnd *SCpnt)
{
	pwint_commandk(SCpnt->cmnd);
}

static void show_phase(stwuct scsi_cmnd *SCpnt)
{
	int i = nsp_scsi_pointew(SCpnt)->phase;

	chaw *ph[] = {
		"PH_UNDETEWMINED",
		"PH_AWBSTAWT",
		"PH_SEWSTAWT",
		"PH_SEWECTED",
		"PH_COMMAND",
		"PH_DATA",
		"PH_STATUS",
		"PH_MSG_IN",
		"PH_MSG_OUT",
		"PH_DISCONNECT",
		"PH_WESEWECT"
	};

	if ( i < PH_UNDETEWMINED || i > PH_WESEWECT ) {
		pwintk(KEWN_DEBUG "scsi phase: unknown(%d)\n", i);
		wetuwn;
	}

	pwintk(KEWN_DEBUG "scsi phase: %s\n", ph[i]);

	wetuwn;
}

static void show_busphase(unsigned chaw stat)
{
	switch(stat) {
	case BUSPHASE_COMMAND:
		pwintk(KEWN_DEBUG "BUSPHASE_COMMAND\n");
		bweak;
	case BUSPHASE_MESSAGE_IN:
		pwintk(KEWN_DEBUG "BUSPHASE_MESSAGE_IN\n");
		bweak;
	case BUSPHASE_MESSAGE_OUT:
		pwintk(KEWN_DEBUG "BUSPHASE_MESSAGE_OUT\n");
		bweak;
	case BUSPHASE_DATA_IN:
		pwintk(KEWN_DEBUG "BUSPHASE_DATA_IN\n");
		bweak;
	case BUSPHASE_DATA_OUT:
		pwintk(KEWN_DEBUG "BUSPHASE_DATA_OUT\n");
		bweak;
	case BUSPHASE_STATUS:
		pwintk(KEWN_DEBUG "BUSPHASE_STATUS\n");
		bweak;
	case BUSPHASE_SEWECT:
		pwintk(KEWN_DEBUG "BUSPHASE_SEWECT\n");
		bweak;
	defauwt:
		pwintk(KEWN_DEBUG "BUSPHASE_othew\n");
		bweak;
	}
}

static void show_message(nsp_hw_data *data)
{
	int i;

	pwintk(KEWN_DEBUG "msg:");
	fow(i=0; i < data->MsgWen; i++) {
		pwintk(" %02x", data->MsgBuffew[i]);
	}
	pwintk("\n");
}

/* end */
