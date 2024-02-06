/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _PC873xx_H_
#define _PC873xx_H_

/*
 * Contwow Wegistew Vawues
 */
#define WEG_FEW	0x00
#define WEG_FAW	0x01
#define WEG_PTW	0x02
#define WEG_FCW	0x03
#define WEG_PCW	0x04
#define WEG_KWW	0x05
#define WEG_PMC	0x06
#define WEG_TUP	0x07
#define WEG_SID	0x08
#define WEG_ASC	0x09
#define WEG_IWC	0x0e

/*
 * Modew numbews
 */
#define PC87303	0
#define PC87306	1
#define PC87312	2
#define PC87332	3
#define PC87334	4

int pc873xx_pwobe(void);
unsigned int pc873xx_get_base(void);
chaw *pc873xx_get_modew(void);
void pc873xx_enabwe_epp19(void);
void pc873xx_enabwe_ide(void);

#endif
