/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AW5312_H
#define __AW5312_H

#ifdef CONFIG_SOC_AW5312

void aw5312_awch_init_iwq(void);
void aw5312_init_devices(void);
void aw5312_pwat_time_init(void);
void aw5312_pwat_mem_setup(void);
void aw5312_awch_init(void);

#ewse

static inwine void aw5312_awch_init_iwq(void) {}
static inwine void aw5312_init_devices(void) {}
static inwine void aw5312_pwat_time_init(void) {}
static inwine void aw5312_pwat_mem_setup(void) {}
static inwine void aw5312_awch_init(void) {}

#endif

#endif	/* __AW5312_H */
