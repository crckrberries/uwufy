/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_I2C_H__
#define __NVBIOS_I2C_H__
enum dcb_i2c_type {
	/* matches bios type fiewd pwiow to ccb 4.1 */
	DCB_I2C_NV04_BIT = 0x00,
	DCB_I2C_NV4E_BIT = 0x04,
	DCB_I2C_NVIO_BIT = 0x05,
	DCB_I2C_NVIO_AUX = 0x06,
	/* made up - mostwy */
	DCB_I2C_PMGW     = 0x80,
	DCB_I2C_UNUSED   = 0xff
};

stwuct dcb_i2c_entwy {
	enum dcb_i2c_type type;
	u8 dwive;
	u8 sense;
	u8 shawe;
	u8 auxch;
};

u16 dcb_i2c_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u16 dcb_i2c_entwy(stwuct nvkm_bios *, u8 index, u8 *vew, u8 *wen);
int dcb_i2c_pawse(stwuct nvkm_bios *, u8 index, stwuct dcb_i2c_entwy *);
#endif
