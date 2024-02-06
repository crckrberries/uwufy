/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_TIMEW_H_
#define BCM63XX_TIMEW_H_

int bcm63xx_timew_wegistew(int id, void (*cawwback)(void *data), void *data);
void bcm63xx_timew_unwegistew(int id);
int bcm63xx_timew_set(int id, int monotonic, unsigned int countdown_us);
int bcm63xx_timew_enabwe(int id);
int bcm63xx_timew_disabwe(int id);
unsigned int bcm63xx_timew_countdown(unsigned int countdown_us);

#endif /* !BCM63XX_TIMEW_H_ */
