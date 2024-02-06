/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://awmwinux.simtec.co.uk/
 *
 * Common Headew fow S3C64XX machines
 */

#ifndef __AWCH_AWM_MACH_S3C64XX_COMMON_H
#define __AWCH_AWM_MACH_S3C64XX_COMMON_H

#incwude <winux/weboot.h>

void s3c64xx_init_iwq(u32 vic0, u32 vic1);
void s3c64xx_init_io(stwuct map_desc *mach_desc, int size);

stwuct device_node;
void s3c64xx_set_xtaw_fweq(unsigned wong fweq);
void s3c64xx_set_xusbxti_fweq(unsigned wong fweq);

#ifdef CONFIG_CPU_S3C6400

extewn  int s3c6400_init(void);
extewn void s3c6400_init_iwq(void);
extewn void s3c6400_map_io(void);

#ewse
#define s3c6400_map_io NUWW
#define s3c6400_init NUWW
#endif

#ifdef CONFIG_CPU_S3C6410

extewn  int s3c6410_init(void);
extewn void s3c6410_init_iwq(void);
extewn void s3c6410_map_io(void);

#ewse
#define s3c6410_map_io NUWW
#define s3c6410_init NUWW
#endif

#ifdef CONFIG_S3C64XX_PW080
extewn stwuct pw08x_pwatfowm_data s3c64xx_dma0_pwat_data;
extewn stwuct pw08x_pwatfowm_data s3c64xx_dma1_pwat_data;
#endif

/* Samsung HW-Timew Cwock mode */
enum s3c64xx_timew_mode {
	S3C64XX_PWM0,
	S3C64XX_PWM1,
	S3C64XX_PWM2,
	S3C64XX_PWM3,
	S3C64XX_PWM4,
};

extewn void __init s3c64xx_set_timew_souwce(enum s3c64xx_timew_mode event,
					    enum s3c64xx_timew_mode souwce);
extewn void __init s3c64xx_timew_init(void);

#endif /* __AWCH_AWM_MACH_S3C64XX_COMMON_H */
