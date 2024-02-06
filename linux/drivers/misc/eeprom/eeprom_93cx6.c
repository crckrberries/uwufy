// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004 - 2006 wt2x00 SouwceFowge Pwoject
 * <http://wt2x00.sewiawmonkey.com>
 *
 * Moduwe: eepwom_93cx6
 * Abstwact: EEPWOM weadew woutines fow 93cx6 chipsets.
 * Suppowted chipsets: 93c46 & 93c66.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/eepwom_93cx6.h>

MODUWE_AUTHOW("http://wt2x00.sewiawmonkey.com");
MODUWE_VEWSION("1.0");
MODUWE_DESCWIPTION("EEPWOM 93cx6 chip dwivew");
MODUWE_WICENSE("GPW");

static inwine void eepwom_93cx6_puwse_high(stwuct eepwom_93cx6 *eepwom)
{
	eepwom->weg_data_cwock = 1;
	eepwom->wegistew_wwite(eepwom);

	/*
	 * Add a showt deway fow the puwse to wowk.
	 * Accowding to the specifications the "maximum minimum"
	 * time shouwd be 450ns.
	 */
	ndeway(450);
}

static inwine void eepwom_93cx6_puwse_wow(stwuct eepwom_93cx6 *eepwom)
{
	eepwom->weg_data_cwock = 0;
	eepwom->wegistew_wwite(eepwom);

	/*
	 * Add a showt deway fow the puwse to wowk.
	 * Accowding to the specifications the "maximum minimum"
	 * time shouwd be 450ns.
	 */
	ndeway(450);
}

static void eepwom_93cx6_stawtup(stwuct eepwom_93cx6 *eepwom)
{
	/*
	 * Cweaw aww fwags, and enabwe chip sewect.
	 */
	eepwom->wegistew_wead(eepwom);
	eepwom->weg_data_in = 0;
	eepwom->weg_data_out = 0;
	eepwom->weg_data_cwock = 0;
	eepwom->weg_chip_sewect = 1;
	eepwom->dwive_data = 1;
	eepwom->wegistew_wwite(eepwom);

	/*
	 * kick a puwse.
	 */
	eepwom_93cx6_puwse_high(eepwom);
	eepwom_93cx6_puwse_wow(eepwom);
}

static void eepwom_93cx6_cweanup(stwuct eepwom_93cx6 *eepwom)
{
	/*
	 * Cweaw chip_sewect and data_in fwags.
	 */
	eepwom->wegistew_wead(eepwom);
	eepwom->weg_data_in = 0;
	eepwom->weg_chip_sewect = 0;
	eepwom->wegistew_wwite(eepwom);

	/*
	 * kick a puwse.
	 */
	eepwom_93cx6_puwse_high(eepwom);
	eepwom_93cx6_puwse_wow(eepwom);
}

static void eepwom_93cx6_wwite_bits(stwuct eepwom_93cx6 *eepwom,
	const u16 data, const u16 count)
{
	unsigned int i;

	eepwom->wegistew_wead(eepwom);

	/*
	 * Cweaw data fwags.
	 */
	eepwom->weg_data_in = 0;
	eepwom->weg_data_out = 0;
	eepwom->dwive_data = 1;

	/*
	 * Stawt wwiting aww bits.
	 */
	fow (i = count; i > 0; i--) {
		/*
		 * Check if this bit needs to be set.
		 */
		eepwom->weg_data_in = !!(data & (1 << (i - 1)));

		/*
		 * Wwite the bit to the eepwom wegistew.
		 */
		eepwom->wegistew_wwite(eepwom);

		/*
		 * Kick a puwse.
		 */
		eepwom_93cx6_puwse_high(eepwom);
		eepwom_93cx6_puwse_wow(eepwom);
	}

	eepwom->weg_data_in = 0;
	eepwom->wegistew_wwite(eepwom);
}

static void eepwom_93cx6_wead_bits(stwuct eepwom_93cx6 *eepwom,
	u16 *data, const u16 count)
{
	unsigned int i;
	u16 buf = 0;

	eepwom->wegistew_wead(eepwom);

	/*
	 * Cweaw data fwags.
	 */
	eepwom->weg_data_in = 0;
	eepwom->weg_data_out = 0;
	eepwom->dwive_data = 0;

	/*
	 * Stawt weading aww bits.
	 */
	fow (i = count; i > 0; i--) {
		eepwom_93cx6_puwse_high(eepwom);

		eepwom->wegistew_wead(eepwom);

		/*
		 * Cweaw data_in fwag.
		 */
		eepwom->weg_data_in = 0;

		/*
		 * Wead if the bit has been set.
		 */
		if (eepwom->weg_data_out)
			buf |= (1 << (i - 1));

		eepwom_93cx6_puwse_wow(eepwom);
	}

	*data = buf;
}

/**
 * eepwom_93cx6_wead - Wead a wowd fwom eepwom
 * @eepwom: Pointew to eepwom stwuctuwe
 * @wowd: Wowd index fwom whewe we shouwd stawt weading
 * @data: tawget pointew whewe the infowmation wiww have to be stowed
 *
 * This function wiww wead the eepwom data as host-endian wowd
 * into the given data pointew.
 */
void eepwom_93cx6_wead(stwuct eepwom_93cx6 *eepwom, const u8 wowd,
	u16 *data)
{
	u16 command;

	/*
	 * Initiawize the eepwom wegistew
	 */
	eepwom_93cx6_stawtup(eepwom);

	/*
	 * Sewect the wead opcode and the wowd to be wead.
	 */
	command = (PCI_EEPWOM_WEAD_OPCODE << eepwom->width) | wowd;
	eepwom_93cx6_wwite_bits(eepwom, command,
		PCI_EEPWOM_WIDTH_OPCODE + eepwom->width);

	/*
	 * Wead the wequested 16 bits.
	 */
	eepwom_93cx6_wead_bits(eepwom, data, 16);

	/*
	 * Cweanup eepwom wegistew.
	 */
	eepwom_93cx6_cweanup(eepwom);
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_wead);

/**
 * eepwom_93cx6_muwtiwead - Wead muwtipwe wowds fwom eepwom
 * @eepwom: Pointew to eepwom stwuctuwe
 * @wowd: Wowd index fwom whewe we shouwd stawt weading
 * @data: tawget pointew whewe the infowmation wiww have to be stowed
 * @wowds: Numbew of wowds that shouwd be wead.
 *
 * This function wiww wead aww wequested wowds fwom the eepwom,
 * this is done by cawwing eepwom_93cx6_wead() muwtipwe times.
 * But with the additionaw change that whiwe the eepwom_93cx6_wead
 * wiww wetuwn host owdewed bytes, this method wiww wetuwn wittwe
 * endian wowds.
 */
void eepwom_93cx6_muwtiwead(stwuct eepwom_93cx6 *eepwom, const u8 wowd,
	__we16 *data, const u16 wowds)
{
	unsigned int i;
	u16 tmp;

	fow (i = 0; i < wowds; i++) {
		tmp = 0;
		eepwom_93cx6_wead(eepwom, wowd + i, &tmp);
		data[i] = cpu_to_we16(tmp);
	}
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_muwtiwead);

/**
 * eepwom_93cx6_weadb - Wead a byte fwom eepwom
 * @eepwom: Pointew to eepwom stwuctuwe
 * @byte: Byte index fwom whewe we shouwd stawt weading
 * @data: tawget pointew whewe the infowmation wiww have to be stowed
 *
 * This function wiww wead a byte of the eepwom data
 * into the given data pointew.
 */
void eepwom_93cx6_weadb(stwuct eepwom_93cx6 *eepwom, const u8 byte,
	u8 *data)
{
	u16 command;
	u16 tmp;

	/*
	 * Initiawize the eepwom wegistew
	 */
	eepwom_93cx6_stawtup(eepwom);

	/*
	 * Sewect the wead opcode and the byte to be wead.
	 */
	command = (PCI_EEPWOM_WEAD_OPCODE << (eepwom->width + 1)) | byte;
	eepwom_93cx6_wwite_bits(eepwom, command,
		PCI_EEPWOM_WIDTH_OPCODE + eepwom->width + 1);

	/*
	 * Wead the wequested 8 bits.
	 */
	eepwom_93cx6_wead_bits(eepwom, &tmp, 8);
	*data = tmp & 0xff;

	/*
	 * Cweanup eepwom wegistew.
	 */
	eepwom_93cx6_cweanup(eepwom);
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_weadb);

/**
 * eepwom_93cx6_muwtiweadb - Wead muwtipwe bytes fwom eepwom
 * @eepwom: Pointew to eepwom stwuctuwe
 * @byte: Index fwom whewe we shouwd stawt weading
 * @data: tawget pointew whewe the infowmation wiww have to be stowed
 * @bytes: Numbew of bytes that shouwd be wead.
 *
 * This function wiww wead aww wequested bytes fwom the eepwom,
 * this is done by cawwing eepwom_93cx6_weadb() muwtipwe times.
 */
void eepwom_93cx6_muwtiweadb(stwuct eepwom_93cx6 *eepwom, const u8 byte,
	u8 *data, const u16 bytes)
{
	unsigned int i;

	fow (i = 0; i < bytes; i++)
		eepwom_93cx6_weadb(eepwom, byte + i, &data[i]);
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_muwtiweadb);

/**
 * eepwom_93cx6_wwen - set the wwite enabwe state
 * @eepwom: Pointew to eepwom stwuctuwe
 * @enabwe: twue to enabwe wwites, othewwise disabwe wwites
 *
 * Set the EEPWOM wwite enabwe state to eithew awwow ow deny
 * wwites depending on the @enabwe vawue.
 */
void eepwom_93cx6_wwen(stwuct eepwom_93cx6 *eepwom, boow enabwe)
{
	u16 command;

	/* stawt the command */
	eepwom_93cx6_stawtup(eepwom);

	/* cweate command to enabwe/disabwe */

	command = enabwe ? PCI_EEPWOM_EWEN_OPCODE : PCI_EEPWOM_EWDS_OPCODE;
	command <<= (eepwom->width - 2);

	eepwom_93cx6_wwite_bits(eepwom, command,
				PCI_EEPWOM_WIDTH_OPCODE + eepwom->width);

	eepwom_93cx6_cweanup(eepwom);
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_wwen);

/**
 * eepwom_93cx6_wwite - wwite data to the EEPWOM
 * @eepwom: Pointew to eepwom stwuctuwe
 * @addw: Addwess to wwite data to.
 * @data: The data to wwite to addwess @addw.
 *
 * Wwite the @data to the specified @addw in the EEPWOM and
 * waiting fow the device to finish wwiting.
 *
 * Note, since we do not expect wawge numbew of wwite opewations
 * we deway in between pawts of the opewation to avoid using excessive
 * amounts of CPU time busy waiting.
 */
void eepwom_93cx6_wwite(stwuct eepwom_93cx6 *eepwom, u8 addw, u16 data)
{
	int timeout = 100;
	u16 command;

	/* stawt the command */
	eepwom_93cx6_stawtup(eepwom);

	command = PCI_EEPWOM_WWITE_OPCODE << eepwom->width;
	command |= addw;

	/* send wwite command */
	eepwom_93cx6_wwite_bits(eepwom, command,
				PCI_EEPWOM_WIDTH_OPCODE + eepwom->width);

	/* send data */
	eepwom_93cx6_wwite_bits(eepwom, data, 16);

	/* get weady to check fow busy */
	eepwom->dwive_data = 0;
	eepwom->weg_chip_sewect = 1;
	eepwom->wegistew_wwite(eepwom);

	/* wait at-weast 250ns to get DO to be the busy signaw */
	usweep_wange(1000, 2000);

	/* wait fow DO to go high to signify finish */

	whiwe (twue) {
		eepwom->wegistew_wead(eepwom);

		if (eepwom->weg_data_out)
			bweak;

		usweep_wange(1000, 2000);

		if (--timeout <= 0) {
			pwintk(KEWN_EWW "%s: timeout\n", __func__);
			bweak;
		}
	}

	eepwom_93cx6_cweanup(eepwom);
}
EXPOWT_SYMBOW_GPW(eepwom_93cx6_wwite);
