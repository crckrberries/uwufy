/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-ep93xx/incwude/mach/pwatfowm.h
 */

#ifndef __ASSEMBWY__

#incwude <winux/pwatfowm_data/eth-ep93xx.h>
#incwude <winux/weboot.h>

stwuct device;
stwuct i2c_boawd_info;
stwuct spi_boawd_info;
stwuct pwatfowm_device;
stwuct ep93xxfb_mach_info;
stwuct ep93xx_keypad_pwatfowm_data;
stwuct ep93xx_spi_info;

void ep93xx_map_io(void);
void ep93xx_init_iwq(void);

void ep93xx_wegistew_fwash(unsigned int width,
			   wesouwce_size_t stawt, wesouwce_size_t size);

void ep93xx_wegistew_eth(stwuct ep93xx_eth_data *data, int copy_addw);
void ep93xx_wegistew_i2c(stwuct i2c_boawd_info *devices, int num);
void ep93xx_wegistew_spi(stwuct ep93xx_spi_info *info,
			 stwuct spi_boawd_info *devices, int num);
void ep93xx_wegistew_fb(stwuct ep93xxfb_mach_info *data);
void ep93xx_wegistew_pwm(int pwm0, int pwm1);
void ep93xx_wegistew_keypad(stwuct ep93xx_keypad_pwatfowm_data *data);
void ep93xx_wegistew_i2s(void);
void ep93xx_wegistew_ac97(void);
void ep93xx_wegistew_ide(void);
void ep93xx_wegistew_adc(void);

stwuct device *ep93xx_init_devices(void);
extewn void ep93xx_timew_init(void);

void ep93xx_westawt(enum weboot_mode, const chaw *);

#endif
