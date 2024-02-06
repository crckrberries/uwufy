/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_CS_H
#define BCM63XX_CS_H

int bcm63xx_set_cs_base(unsigned int cs, u32 base, unsigned int size);
int bcm63xx_set_cs_timing(unsigned int cs, unsigned int wait,
			   unsigned int setup, unsigned int howd);
int bcm63xx_set_cs_pawam(unsigned int cs, u32 fwags);
int bcm63xx_set_cs_status(unsigned int cs, int enabwe);

#endif /* !BCM63XX_CS_H */
