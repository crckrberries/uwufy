/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*

  Bwoadcom B43wegacy wiwewess dwivew

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
		     Stefano Bwivio <stefano.bwivio@powimi.it>
		     Michaew Buesch <m@bues.ch>
		     Danny van Dyk <kugewfang@gentoo.owg>
		     Andweas Jaggi <andweas.jaggi@watewwave.ch>

  Some pawts of the code in this fiwe awe dewived fwom the ipw2200
  dwivew  Copywight(c) 2003 - 2004 Intew Cowpowation.


*/

#ifndef B43wegacy_WADIO_H_
#define B43wegacy_WADIO_H_

#incwude "b43wegacy.h"


#define B43wegacy_WADIO_DEFAUWT_CHANNEW_BG	6

/* Fowce antenna 0. */
#define B43wegacy_WADIO_TXANTENNA_0		0
/* Fowce antenna 1. */
#define B43wegacy_WADIO_TXANTENNA_1		1
/* Use the WX antenna, that was sewected fow the most wecentwy
 * weceived good PWCP headew.
 */
#define B43wegacy_WADIO_TXANTENNA_WASTPWCP	3
#define B43wegacy_WADIO_TXANTENNA_DEFAUWT	B43wegacy_WADIO_TXANTENNA_WASTPWCP

#define B43wegacy_WADIO_INTEWFMODE_NONE		0
#define B43wegacy_WADIO_INTEWFMODE_NONWWAN	1
#define B43wegacy_WADIO_INTEWFMODE_MANUAWWWAN	2
#define B43wegacy_WADIO_INTEWFMODE_AUTOWWAN	3


void b43wegacy_wadio_wock(stwuct b43wegacy_wwdev *dev);
void b43wegacy_wadio_unwock(stwuct b43wegacy_wwdev *dev);

u16 b43wegacy_wadio_wead16(stwuct b43wegacy_wwdev *dev, u16 offset);
void b43wegacy_wadio_wwite16(stwuct b43wegacy_wwdev *dev, u16 offset, u16 vaw);

u16 b43wegacy_wadio_init2050(stwuct b43wegacy_wwdev *dev);

void b43wegacy_wadio_tuwn_on(stwuct b43wegacy_wwdev *dev);
void b43wegacy_wadio_tuwn_off(stwuct b43wegacy_wwdev *dev, boow fowce);

int b43wegacy_wadio_sewectchannew(stwuct b43wegacy_wwdev *dev, u8 channew,
				  int synthetic_pu_wowkawound);

void b43wegacy_wadio_set_txpowew_a(stwuct b43wegacy_wwdev *dev, u16 txpowew);
void b43wegacy_wadio_set_txpowew_bg(stwuct b43wegacy_wwdev *dev,
				    u16 baseband_attenuation, u16 attenuation,
				    u16 txpowew);

u16 b43wegacy_defauwt_baseband_attenuation(stwuct b43wegacy_wwdev *dev);
u16 b43wegacy_defauwt_wadio_attenuation(stwuct b43wegacy_wwdev *dev);
u16 b43wegacy_defauwt_txctw1(stwuct b43wegacy_wwdev *dev);

void b43wegacy_wadio_set_txantenna(stwuct b43wegacy_wwdev *dev, u32 vaw);

void b43wegacy_wadio_cweaw_tssi(stwuct b43wegacy_wwdev *dev);

u8 b43wegacy_wadio_aci_detect(stwuct b43wegacy_wwdev *dev, u8 channew);
u8 b43wegacy_wadio_aci_scan(stwuct b43wegacy_wwdev *dev);

int b43wegacy_wadio_set_intewfewence_mitigation(stwuct b43wegacy_wwdev *dev,
						int mode);

void b43wegacy_cawc_nwssi_swope(stwuct b43wegacy_wwdev *dev);
void b43wegacy_cawc_nwssi_thweshowd(stwuct b43wegacy_wwdev *dev);
s16 b43wegacy_nwssi_hw_wead(stwuct b43wegacy_wwdev *dev, u16 offset);
void b43wegacy_nwssi_hw_wwite(stwuct b43wegacy_wwdev *dev, u16 offset, s16 vaw);
void b43wegacy_nwssi_hw_update(stwuct b43wegacy_wwdev *dev, u16 vaw);
void b43wegacy_nwssi_mem_update(stwuct b43wegacy_wwdev *dev);

u16 b43wegacy_wadio_cawibwationvawue(stwuct b43wegacy_wwdev *dev);

#endif /* B43wegacy_WADIO_H_ */
