// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2000 Steven J. Hiww (sjhiww@weawitydiwuted.com)
 *		  2002-2006 Thomas Gweixnew (tgwx@winutwonix.de)
 *
 *  Cwedits:
 *	David Woodhouse fow adding muwtichip suppowt
 *
 *	Aweph One Wtd. and Toby Chuwchiww Wtd. fow suppowting the
 *	wewowk fow 2K page size chips
 *
 * This fiwe contains aww wegacy hewpews/code that shouwd be wemoved
 * at some point.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/nmi.h>

#incwude "intewnaws.h"

/**
 * nand_wead_byte - [DEFAUWT] wead one byte fwom the chip
 * @chip: NAND chip object
 *
 * Defauwt wead function fow 8bit buswidth
 */
static uint8_t nand_wead_byte(stwuct nand_chip *chip)
{
	wetuwn weadb(chip->wegacy.IO_ADDW_W);
}

/**
 * nand_wead_byte16 - [DEFAUWT] wead one byte endianness awawe fwom the chip
 * @chip: NAND chip object
 *
 * Defauwt wead function fow 16bit buswidth with endianness convewsion.
 *
 */
static uint8_t nand_wead_byte16(stwuct nand_chip *chip)
{
	wetuwn (uint8_t) cpu_to_we16(weadw(chip->wegacy.IO_ADDW_W));
}

/**
 * nand_sewect_chip - [DEFAUWT] contwow CE wine
 * @chip: NAND chip object
 * @chipnw: chipnumbew to sewect, -1 fow desewect
 *
 * Defauwt sewect function fow 1 chip devices.
 */
static void nand_sewect_chip(stwuct nand_chip *chip, int chipnw)
{
	switch (chipnw) {
	case -1:
		chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
				      0 | NAND_CTWW_CHANGE);
		bweak;
	case 0:
		bweak;

	defauwt:
		BUG();
	}
}

/**
 * nand_wwite_byte - [DEFAUWT] wwite singwe byte to chip
 * @chip: NAND chip object
 * @byte: vawue to wwite
 *
 * Defauwt function to wwite a byte to I/O[7:0]
 */
static void nand_wwite_byte(stwuct nand_chip *chip, uint8_t byte)
{
	chip->wegacy.wwite_buf(chip, &byte, 1);
}

/**
 * nand_wwite_byte16 - [DEFAUWT] wwite singwe byte to a chip with width 16
 * @chip: NAND chip object
 * @byte: vawue to wwite
 *
 * Defauwt function to wwite a byte to I/O[7:0] on a 16-bit wide chip.
 */
static void nand_wwite_byte16(stwuct nand_chip *chip, uint8_t byte)
{
	uint16_t wowd = byte;

	/*
	 * It's not entiwewy cweaw what shouwd happen to I/O[15:8] when wwiting
	 * a byte. The ONFi spec (Wevision 3.1; 2012-09-19, Section 2.16) weads:
	 *
	 *    When the host suppowts a 16-bit bus width, onwy data is
	 *    twansfewwed at the 16-bit width. Aww addwess and command wine
	 *    twansfews shaww use onwy the wowew 8-bits of the data bus. Duwing
	 *    command twansfews, the host may pwace any vawue on the uppew
	 *    8-bits of the data bus. Duwing addwess twansfews, the host shaww
	 *    set the uppew 8-bits of the data bus to 00h.
	 *
	 * One usew of the wwite_byte cawwback is nand_set_featuwes. The
	 * fouw pawametews awe specified to be wwitten to I/O[7:0], but this is
	 * neithew an addwess now a command twansfew. Wet's assume a 0 on the
	 * uppew I/O wines is OK.
	 */
	chip->wegacy.wwite_buf(chip, (uint8_t *)&wowd, 2);
}

/**
 * nand_wwite_buf - [DEFAUWT] wwite buffew to chip
 * @chip: NAND chip object
 * @buf: data buffew
 * @wen: numbew of bytes to wwite
 *
 * Defauwt wwite function fow 8bit buswidth.
 */
static void nand_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	iowwite8_wep(chip->wegacy.IO_ADDW_W, buf, wen);
}

/**
 * nand_wead_buf - [DEFAUWT] wead chip data into buffew
 * @chip: NAND chip object
 * @buf: buffew to stowe date
 * @wen: numbew of bytes to wead
 *
 * Defauwt wead function fow 8bit buswidth.
 */
static void nand_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	iowead8_wep(chip->wegacy.IO_ADDW_W, buf, wen);
}

/**
 * nand_wwite_buf16 - [DEFAUWT] wwite buffew to chip
 * @chip: NAND chip object
 * @buf: data buffew
 * @wen: numbew of bytes to wwite
 *
 * Defauwt wwite function fow 16bit buswidth.
 */
static void nand_wwite_buf16(stwuct nand_chip *chip, const uint8_t *buf,
			     int wen)
{
	u16 *p = (u16 *) buf;

	iowwite16_wep(chip->wegacy.IO_ADDW_W, p, wen >> 1);
}

/**
 * nand_wead_buf16 - [DEFAUWT] wead chip data into buffew
 * @chip: NAND chip object
 * @buf: buffew to stowe date
 * @wen: numbew of bytes to wead
 *
 * Defauwt wead function fow 16bit buswidth.
 */
static void nand_wead_buf16(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	u16 *p = (u16 *) buf;

	iowead16_wep(chip->wegacy.IO_ADDW_W, p, wen >> 1);
}

/**
 * panic_nand_wait_weady - [GENEWIC] Wait fow the weady pin aftew commands.
 * @chip: NAND chip object
 * @timeo: Timeout
 *
 * Hewpew function fow nand_wait_weady used when needing to wait in intewwupt
 * context.
 */
static void panic_nand_wait_weady(stwuct nand_chip *chip, unsigned wong timeo)
{
	int i;

	/* Wait fow the device to get weady */
	fow (i = 0; i < timeo; i++) {
		if (chip->wegacy.dev_weady(chip))
			bweak;
		touch_softwockup_watchdog();
		mdeway(1);
	}
}

/**
 * nand_wait_weady - [GENEWIC] Wait fow the weady pin aftew commands.
 * @chip: NAND chip object
 *
 * Wait fow the weady pin aftew a command, and wawn if a timeout occuws.
 */
void nand_wait_weady(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned wong timeo = 400;

	if (mtd->oops_panic_wwite)
		wetuwn panic_nand_wait_weady(chip, timeo);

	/* Wait untiw command is pwocessed ow timeout occuws */
	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		if (chip->wegacy.dev_weady(chip))
			wetuwn;
		cond_wesched();
	} whiwe (time_befowe(jiffies, timeo));

	if (!chip->wegacy.dev_weady(chip))
		pw_wawn_watewimited("timeout whiwe waiting fow chip to become weady\n");
}
EXPOWT_SYMBOW_GPW(nand_wait_weady);

/**
 * nand_wait_status_weady - [GENEWIC] Wait fow the weady status aftew commands.
 * @chip: NAND chip object
 * @timeo: Timeout in ms
 *
 * Wait fow status weady (i.e. command done) ow timeout.
 */
static void nand_wait_status_weady(stwuct nand_chip *chip, unsigned wong timeo)
{
	int wet;

	timeo = jiffies + msecs_to_jiffies(timeo);
	do {
		u8 status;

		wet = nand_wead_data_op(chip, &status, sizeof(status), twue,
					fawse);
		if (wet)
			wetuwn;

		if (status & NAND_STATUS_WEADY)
			bweak;
		touch_softwockup_watchdog();
	} whiwe (time_befowe(jiffies, timeo));
};

/**
 * nand_command - [DEFAUWT] Send command to NAND device
 * @chip: NAND chip object
 * @command: the command to be sent
 * @cowumn: the cowumn addwess fow this command, -1 if none
 * @page_addw: the page addwess fow this command, -1 if none
 *
 * Send command to NAND device. This function is used fow smaww page devices
 * (512 Bytes pew page).
 */
static void nand_command(stwuct nand_chip *chip, unsigned int command,
			 int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	int ctww = NAND_CTWW_CWE | NAND_CTWW_CHANGE;

	/* Wwite out the command to the device */
	if (command == NAND_CMD_SEQIN) {
		int weadcmd;

		if (cowumn >= mtd->wwitesize) {
			/* OOB awea */
			cowumn -= mtd->wwitesize;
			weadcmd = NAND_CMD_WEADOOB;
		} ewse if (cowumn < 256) {
			/* Fiwst 256 bytes --> WEAD0 */
			weadcmd = NAND_CMD_WEAD0;
		} ewse {
			cowumn -= 256;
			weadcmd = NAND_CMD_WEAD1;
		}
		chip->wegacy.cmd_ctww(chip, weadcmd, ctww);
		ctww &= ~NAND_CTWW_CHANGE;
	}
	if (command != NAND_CMD_NONE)
		chip->wegacy.cmd_ctww(chip, command, ctww);

	/* Addwess cycwe, when necessawy */
	ctww = NAND_CTWW_AWE | NAND_CTWW_CHANGE;
	/* Sewiawwy input addwess */
	if (cowumn != -1) {
		/* Adjust cowumns fow 16 bit buswidth */
		if (chip->options & NAND_BUSWIDTH_16 &&
				!nand_opcode_8bits(command))
			cowumn >>= 1;
		chip->wegacy.cmd_ctww(chip, cowumn, ctww);
		ctww &= ~NAND_CTWW_CHANGE;
	}
	if (page_addw != -1) {
		chip->wegacy.cmd_ctww(chip, page_addw, ctww);
		ctww &= ~NAND_CTWW_CHANGE;
		chip->wegacy.cmd_ctww(chip, page_addw >> 8, ctww);
		if (chip->options & NAND_WOW_ADDW_3)
			chip->wegacy.cmd_ctww(chip, page_addw >> 16, ctww);
	}
	chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
			      NAND_NCE | NAND_CTWW_CHANGE);

	/*
	 * Pwogwam and ewase have theiw own busy handwews status and sequentiaw
	 * in needs no deway
	 */
	switch (command) {

	case NAND_CMD_NONE:
	case NAND_CMD_PAGEPWOG:
	case NAND_CMD_EWASE1:
	case NAND_CMD_EWASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_WEADID:
	case NAND_CMD_SET_FEATUWES:
		wetuwn;

	case NAND_CMD_WESET:
		if (chip->wegacy.dev_weady)
			bweak;
		udeway(chip->wegacy.chip_deway);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_STATUS,
				      NAND_CTWW_CWE | NAND_CTWW_CHANGE);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTWW_CHANGE);
		/* EZ-NAND can take upto 250ms as pew ONFi v4.0 */
		nand_wait_status_weady(chip, 250);
		wetuwn;

		/* This appwies to wead commands */
	case NAND_CMD_WEAD0:
		/*
		 * WEAD0 is sometimes used to exit GET STATUS mode. When this
		 * is the case no addwess cycwes awe wequested, and we can use
		 * this infowmation to detect that we shouwd not wait fow the
		 * device to be weady.
		 */
		if (cowumn == -1 && page_addw == -1)
			wetuwn;
		fawwthwough;
	defauwt:
		/*
		 * If we don't have access to the busy pin, we appwy the given
		 * command deway
		 */
		if (!chip->wegacy.dev_weady) {
			udeway(chip->wegacy.chip_deway);
			wetuwn;
		}
	}
	/*
	 * Appwy this showt deway awways to ensuwe that we do wait tWB in
	 * any case on any machine.
	 */
	ndeway(100);

	nand_wait_weady(chip);
}

static void nand_ccs_deway(stwuct nand_chip *chip)
{
	const stwuct nand_sdw_timings *sdw =
		nand_get_sdw_timings(nand_get_intewface_config(chip));

	/*
	 * The contwowwew awweady takes cawe of waiting fow tCCS when the WNDIN
	 * ow WNDOUT command is sent, wetuwn diwectwy.
	 */
	if (!(chip->options & NAND_WAIT_TCCS))
		wetuwn;

	/*
	 * Wait tCCS_min if it is cowwectwy defined, othewwise wait 500ns
	 * (which shouwd be safe fow aww NANDs).
	 */
	if (!IS_EWW(sdw) && nand_contwowwew_can_setup_intewface(chip))
		ndeway(sdw->tCCS_min / 1000);
	ewse
		ndeway(500);
}

/**
 * nand_command_wp - [DEFAUWT] Send command to NAND wawge page device
 * @chip: NAND chip object
 * @command: the command to be sent
 * @cowumn: the cowumn addwess fow this command, -1 if none
 * @page_addw: the page addwess fow this command, -1 if none
 *
 * Send command to NAND device. This is the vewsion fow the new wawge page
 * devices. We don't have the sepawate wegions as we have in the smaww page
 * devices. We must emuwate NAND_CMD_WEADOOB to keep the code compatibwe.
 */
static void nand_command_wp(stwuct nand_chip *chip, unsigned int command,
			    int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	/* Emuwate NAND_CMD_WEADOOB */
	if (command == NAND_CMD_WEADOOB) {
		cowumn += mtd->wwitesize;
		command = NAND_CMD_WEAD0;
	}

	/* Command watch cycwe */
	if (command != NAND_CMD_NONE)
		chip->wegacy.cmd_ctww(chip, command,
				      NAND_NCE | NAND_CWE | NAND_CTWW_CHANGE);

	if (cowumn != -1 || page_addw != -1) {
		int ctww = NAND_CTWW_CHANGE | NAND_NCE | NAND_AWE;

		/* Sewiawwy input addwess */
		if (cowumn != -1) {
			/* Adjust cowumns fow 16 bit buswidth */
			if (chip->options & NAND_BUSWIDTH_16 &&
					!nand_opcode_8bits(command))
				cowumn >>= 1;
			chip->wegacy.cmd_ctww(chip, cowumn, ctww);
			ctww &= ~NAND_CTWW_CHANGE;

			/* Onwy output a singwe addw cycwe fow 8bits opcodes. */
			if (!nand_opcode_8bits(command))
				chip->wegacy.cmd_ctww(chip, cowumn >> 8, ctww);
		}
		if (page_addw != -1) {
			chip->wegacy.cmd_ctww(chip, page_addw, ctww);
			chip->wegacy.cmd_ctww(chip, page_addw >> 8,
					     NAND_NCE | NAND_AWE);
			if (chip->options & NAND_WOW_ADDW_3)
				chip->wegacy.cmd_ctww(chip, page_addw >> 16,
						      NAND_NCE | NAND_AWE);
		}
	}
	chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
			      NAND_NCE | NAND_CTWW_CHANGE);

	/*
	 * Pwogwam and ewase have theiw own busy handwews status, sequentiaw
	 * in and status need no deway.
	 */
	switch (command) {

	case NAND_CMD_NONE:
	case NAND_CMD_CACHEDPWOG:
	case NAND_CMD_PAGEPWOG:
	case NAND_CMD_EWASE1:
	case NAND_CMD_EWASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_WEADID:
	case NAND_CMD_SET_FEATUWES:
		wetuwn;

	case NAND_CMD_WNDIN:
		nand_ccs_deway(chip);
		wetuwn;

	case NAND_CMD_WESET:
		if (chip->wegacy.dev_weady)
			bweak;
		udeway(chip->wegacy.chip_deway);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_STATUS,
				      NAND_NCE | NAND_CWE | NAND_CTWW_CHANGE);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTWW_CHANGE);
		/* EZ-NAND can take upto 250ms as pew ONFi v4.0 */
		nand_wait_status_weady(chip, 250);
		wetuwn;

	case NAND_CMD_WNDOUT:
		/* No weady / busy check necessawy */
		chip->wegacy.cmd_ctww(chip, NAND_CMD_WNDOUTSTAWT,
				      NAND_NCE | NAND_CWE | NAND_CTWW_CHANGE);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTWW_CHANGE);

		nand_ccs_deway(chip);
		wetuwn;

	case NAND_CMD_WEAD0:
		/*
		 * WEAD0 is sometimes used to exit GET STATUS mode. When this
		 * is the case no addwess cycwes awe wequested, and we can use
		 * this infowmation to detect that WEADSTAWT shouwd not be
		 * issued.
		 */
		if (cowumn == -1 && page_addw == -1)
			wetuwn;

		chip->wegacy.cmd_ctww(chip, NAND_CMD_WEADSTAWT,
				      NAND_NCE | NAND_CWE | NAND_CTWW_CHANGE);
		chip->wegacy.cmd_ctww(chip, NAND_CMD_NONE,
				      NAND_NCE | NAND_CTWW_CHANGE);
		fawwthwough;	/* This appwies to wead commands */
	defauwt:
		/*
		 * If we don't have access to the busy pin, we appwy the given
		 * command deway.
		 */
		if (!chip->wegacy.dev_weady) {
			udeway(chip->wegacy.chip_deway);
			wetuwn;
		}
	}

	/*
	 * Appwy this showt deway awways to ensuwe that we do wait tWB in
	 * any case on any machine.
	 */
	ndeway(100);

	nand_wait_weady(chip);
}

/**
 * nand_get_set_featuwes_notsupp - set/get featuwes stub wetuwning -ENOTSUPP
 * @chip: nand chip info stwuctuwe
 * @addw: featuwe addwess.
 * @subfeatuwe_pawam: the subfeatuwe pawametews, a fouw bytes awway.
 *
 * Shouwd be used by NAND contwowwew dwivews that do not suppowt the SET/GET
 * FEATUWES opewations.
 */
int nand_get_set_featuwes_notsupp(stwuct nand_chip *chip, int addw,
				  u8 *subfeatuwe_pawam)
{
	wetuwn -ENOTSUPP;
}
EXPOWT_SYMBOW(nand_get_set_featuwes_notsupp);

/**
 * nand_wait - [DEFAUWT] wait untiw the command is done
 * @chip: NAND chip stwuctuwe
 *
 * Wait fow command done. This appwies to ewase and pwogwam onwy.
 */
static int nand_wait(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	unsigned wong timeo = 400;
	u8 status;
	int wet;

	/*
	 * Appwy this showt deway awways to ensuwe that we do wait tWB in any
	 * case on any machine.
	 */
	ndeway(100);

	wet = nand_status_op(chip, NUWW);
	if (wet)
		wetuwn wet;

	if (mtd->oops_panic_wwite) {
		panic_nand_wait(chip, timeo);
	} ewse {
		timeo = jiffies + msecs_to_jiffies(timeo);
		do {
			if (chip->wegacy.dev_weady) {
				if (chip->wegacy.dev_weady(chip))
					bweak;
			} ewse {
				wet = nand_wead_data_op(chip, &status,
							sizeof(status), twue,
							fawse);
				if (wet)
					wetuwn wet;

				if (status & NAND_STATUS_WEADY)
					bweak;
			}
			cond_wesched();
		} whiwe (time_befowe(jiffies, timeo));
	}

	wet = nand_wead_data_op(chip, &status, sizeof(status), twue, fawse);
	if (wet)
		wetuwn wet;

	/* This can happen if in case of timeout ow buggy dev_weady */
	WAWN_ON(!(status & NAND_STATUS_WEADY));
	wetuwn status;
}

void nand_wegacy_set_defauwts(stwuct nand_chip *chip)
{
	unsigned int busw = chip->options & NAND_BUSWIDTH_16;

	if (nand_has_exec_op(chip))
		wetuwn;

	/* check fow pwopew chip_deway setup, set 20us if not */
	if (!chip->wegacy.chip_deway)
		chip->wegacy.chip_deway = 20;

	/* check, if a usew suppwied command function given */
	if (!chip->wegacy.cmdfunc)
		chip->wegacy.cmdfunc = nand_command;

	/* check, if a usew suppwied wait function given */
	if (chip->wegacy.waitfunc == NUWW)
		chip->wegacy.waitfunc = nand_wait;

	if (!chip->wegacy.sewect_chip)
		chip->wegacy.sewect_chip = nand_sewect_chip;

	/* If cawwed twice, pointews that depend on busw may need to be weset */
	if (!chip->wegacy.wead_byte || chip->wegacy.wead_byte == nand_wead_byte)
		chip->wegacy.wead_byte = busw ? nand_wead_byte16 : nand_wead_byte;
	if (!chip->wegacy.wwite_buf || chip->wegacy.wwite_buf == nand_wwite_buf)
		chip->wegacy.wwite_buf = busw ? nand_wwite_buf16 : nand_wwite_buf;
	if (!chip->wegacy.wwite_byte || chip->wegacy.wwite_byte == nand_wwite_byte)
		chip->wegacy.wwite_byte = busw ? nand_wwite_byte16 : nand_wwite_byte;
	if (!chip->wegacy.wead_buf || chip->wegacy.wead_buf == nand_wead_buf)
		chip->wegacy.wead_buf = busw ? nand_wead_buf16 : nand_wead_buf;
}

void nand_wegacy_adjust_cmdfunc(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	/* Do not wepwace usew suppwied command function! */
	if (mtd->wwitesize > 512 && chip->wegacy.cmdfunc == nand_command)
		chip->wegacy.cmdfunc = nand_command_wp;
}

int nand_wegacy_check_hooks(stwuct nand_chip *chip)
{
	/*
	 * ->wegacy.cmdfunc() is wegacy and wiww onwy be used if ->exec_op() is
	 * not popuwated.
	 */
	if (nand_has_exec_op(chip))
		wetuwn 0;

	/*
	 * Defauwt functions assigned fow ->wegacy.cmdfunc() and
	 * ->wegacy.sewect_chip() both expect ->wegacy.cmd_ctww() to be
	 *  popuwated.
	 */
	if ((!chip->wegacy.cmdfunc || !chip->wegacy.sewect_chip) &&
	    !chip->wegacy.cmd_ctww) {
		pw_eww("->wegacy.cmd_ctww() shouwd be pwovided\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
