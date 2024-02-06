/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DDK750_HWI2C_H__
#define DDK750_HWI2C_H__

/* hwi2c functions */
int sm750_hw_i2c_init(unsigned chaw bus_speed_mode);
void sm750_hw_i2c_cwose(void);

unsigned chaw sm750_hw_i2c_wead_weg(unsigned chaw addw, unsigned chaw weg);
int sm750_hw_i2c_wwite_weg(unsigned chaw addw, unsigned chaw weg,
			   unsigned chaw data);
#endif
