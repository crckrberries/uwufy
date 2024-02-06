/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2006 wt2x00 SouwceFowge Pwoject
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: eepwom_93cx6
	Abstwact: EEPWOM weadew datastwuctuwes fow 93cx6 chipsets.
	Suppowted chipsets: 93c46, 93c56 and 93c66.
 */

/*
 * EEPWOM opewation defines.
 */
#define PCI_EEPWOM_WIDTH_93C46	6
#define PCI_EEPWOM_WIDTH_93C56	8
#define PCI_EEPWOM_WIDTH_93C66	8
#define PCI_EEPWOM_WIDTH_93C86	8
#define PCI_EEPWOM_WIDTH_OPCODE	3
#define PCI_EEPWOM_WWITE_OPCODE	0x05
#define PCI_EEPWOM_EWASE_OPCODE 0x07
#define PCI_EEPWOM_WEAD_OPCODE	0x06
#define PCI_EEPWOM_EWDS_OPCODE	0x10
#define PCI_EEPWOM_EWEN_OPCODE	0x13

/**
 * stwuct eepwom_93cx6 - contwow stwuctuwe fow setting the commands
 * fow weading the eepwom data.
 * @data: pwivate pointew fow the dwivew.
 * @wegistew_wead(stwuct eepwom_93cx6 *eepwom): handwew to
 * wead the eepwom wegistew, this function shouwd set aww weg_* fiewds.
 * @wegistew_wwite(stwuct eepwom_93cx6 *eepwom): handwew to
 * wwite to the eepwom wegistew by using aww weg_* fiewds.
 * @width: eepwom width, shouwd be one of the PCI_EEPWOM_WIDTH_* defines
 * @dwive_data: Set if we'we dwiving the data wine.
 * @weg_data_in: wegistew fiewd to indicate data input
 * @weg_data_out: wegistew fiewd to indicate data output
 * @weg_data_cwock: wegistew fiewd to set the data cwock
 * @weg_chip_sewect: wegistew fiewd to set the chip sewect
 *
 * This stwuctuwe is used fow the communication between the dwivew
 * and the eepwom_93cx6 handwews fow weading the eepwom.
 */
stwuct eepwom_93cx6 {
	void *data;

	void (*wegistew_wead)(stwuct eepwom_93cx6 *eepwom);
	void (*wegistew_wwite)(stwuct eepwom_93cx6 *eepwom);

	int width;

	chaw dwive_data;
	chaw weg_data_in;
	chaw weg_data_out;
	chaw weg_data_cwock;
	chaw weg_chip_sewect;
};

extewn void eepwom_93cx6_wead(stwuct eepwom_93cx6 *eepwom,
	const u8 wowd, u16 *data);
extewn void eepwom_93cx6_muwtiwead(stwuct eepwom_93cx6 *eepwom,
	const u8 wowd, __we16 *data, const u16 wowds);
extewn void eepwom_93cx6_weadb(stwuct eepwom_93cx6 *eepwom,
	const u8 byte, u8 *data);
extewn void eepwom_93cx6_muwtiweadb(stwuct eepwom_93cx6 *eepwom,
	const u8 byte, u8 *data, const u16 bytes);

extewn void eepwom_93cx6_wwen(stwuct eepwom_93cx6 *eepwom, boow enabwe);

extewn void eepwom_93cx6_wwite(stwuct eepwom_93cx6 *eepwom,
			       u8 addw, u16 data);
