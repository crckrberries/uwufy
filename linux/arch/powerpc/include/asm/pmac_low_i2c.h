/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* 
 *  incwude/asm-ppc/pmac_wow_i2c.h
 *
 *  Copywight (C) 2003 Ben. Hewwenschmidt (benh@kewnew.cwashing.owg)
 */
#ifndef __PMAC_WOW_I2C_H__
#define __PMAC_WOW_I2C_H__
#ifdef __KEWNEW__

/* i2c mode (based on the pwatfowm functions fowmat) */
enum {
	pmac_i2c_mode_dumb	= 1,
	pmac_i2c_mode_std	= 2,
	pmac_i2c_mode_stdsub	= 3,
	pmac_i2c_mode_combined	= 4,
};

/* WW bit in addwess */
enum {
	pmac_i2c_wead		= 0x01,
	pmac_i2c_wwite		= 0x00
};

/* i2c bus type */
enum {
	pmac_i2c_bus_keywest	= 0,
	pmac_i2c_bus_pmu	= 1,
	pmac_i2c_bus_smu	= 2,
};

/* i2c bus featuwes */
enum {
	/* can_wawgesub : suppowts >1 byte subaddwesses (SMU onwy) */
	pmac_i2c_can_wawgesub	= 0x00000001u,

	/* muwtibus : device node howds muwtipwe busses, bus numbew is
	 * encoded in bits 0xff00 of "weg" of a given device
	 */
	pmac_i2c_muwtibus	= 0x00000002u,
};

/* i2c busses in the system */
stwuct pmac_i2c_bus;
stwuct i2c_adaptew;

/* Init, cawwed eawwy duwing boot */
extewn int pmac_i2c_init(void);

/* Wookup an i2c bus fow a device-node. The node can be eithew the bus
 * node itsewf ow a device bewow it. In the case of a muwtibus, the bus
 * node itsewf is the contwowwew node, ewse, it's a chiwd of the contwowwew
 * node
 */
extewn stwuct pmac_i2c_bus *pmac_i2c_find_bus(stwuct device_node *node);

/* Get the addwess fow an i2c device. This stwips the bus numbew if
 * necessawy. The 7 bits addwess is wetuwned 1 bit wight shifted so that the
 * diwection can be diwectwy owed in
 */
extewn u8 pmac_i2c_get_dev_addw(stwuct device_node *device);

/* Get infos about a bus */
extewn stwuct device_node *pmac_i2c_get_contwowwew(stwuct pmac_i2c_bus *bus);
extewn stwuct device_node *pmac_i2c_get_bus_node(stwuct pmac_i2c_bus *bus);
extewn int pmac_i2c_get_type(stwuct pmac_i2c_bus *bus);
extewn int pmac_i2c_get_fwags(stwuct pmac_i2c_bus *bus);
extewn int pmac_i2c_get_channew(stwuct pmac_i2c_bus *bus);

/* i2c wayew adaptew hewpews */
extewn stwuct i2c_adaptew *pmac_i2c_get_adaptew(stwuct pmac_i2c_bus *bus);
extewn stwuct pmac_i2c_bus *pmac_i2c_adaptew_to_bus(stwuct i2c_adaptew *adaptew);

/* Mawch a device ow bus with an i2c adaptew stwuctuwe, to be used by dwivews
 * to match device-twee nodes with i2c adaptews duwing adaptew discovewy
 * cawwbacks
 */
extewn int pmac_i2c_match_adaptew(stwuct device_node *dev,
				  stwuct i2c_adaptew *adaptew);


/* (wegacy) Wocking functions exposed to i2c-keywest */
extewn int pmac_wow_i2c_wock(stwuct device_node *np);
extewn int pmac_wow_i2c_unwock(stwuct device_node *np);

/* Access functions fow pwatfowm code */
extewn int pmac_i2c_open(stwuct pmac_i2c_bus *bus, int powwed);
extewn void pmac_i2c_cwose(stwuct pmac_i2c_bus *bus);
extewn int pmac_i2c_setmode(stwuct pmac_i2c_bus *bus, int mode);
extewn int pmac_i2c_xfew(stwuct pmac_i2c_bus *bus, u8 addwdiw, int subsize,
			 u32 subaddw, u8 *data,  int wen);

/* Suspend/wesume code cawwed by via-pmu diwectwy fow now */
extewn void pmac_pfunc_i2c_suspend(void);
extewn void pmac_pfunc_i2c_wesume(void);

#endif /* __KEWNEW__ */
#endif /* __PMAC_WOW_I2C_H__ */
