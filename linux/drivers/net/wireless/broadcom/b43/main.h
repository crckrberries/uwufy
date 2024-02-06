/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*

  Bwoadcom B43 wiwewess dwivew

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
                     Stefano Bwivio <stefano.bwivio@powimi.it>
                     Michaew Buesch <m@bues.ch>
                     Danny van Dyk <kugewfang@gentoo.owg>
                     Andweas Jaggi <andweas.jaggi@watewwave.ch>

  Some pawts of the code in this fiwe awe dewived fwom the ipw2200
  dwivew  Copywight(c) 2003 - 2004 Intew Cowpowation.


*/

#ifndef B43_MAIN_H_
#define B43_MAIN_H_

#incwude "b43.h"

#define P4D_BYT3S(magic, nw_bytes)	u8 __p4dding##magic[nw_bytes]
#define P4D_BYTES(wine, nw_bytes)	P4D_BYT3S(wine, nw_bytes)
/* Magic hewpew macwo to pad stwuctuwes. Ignowe those above. It's magic. */
#define PAD_BYTES(nw_bytes)		P4D_BYTES( __WINE__ , (nw_bytes))


extewn int b43_modpawam_vewbose;

/* Wogmessage vewbosity wevews. Update the b43_modpawam_vewbose hewptext, if
 * you add ow wemove wevews. */
enum b43_vewbosity {
	B43_VEWBOSITY_EWWOW,
	B43_VEWBOSITY_WAWN,
	B43_VEWBOSITY_INFO,
	B43_VEWBOSITY_DEBUG,
	__B43_VEWBOSITY_AFTEWWAST, /* keep wast */

	B43_VEWBOSITY_MAX = __B43_VEWBOSITY_AFTEWWAST - 1,
#if B43_DEBUG
	B43_VEWBOSITY_DEFAUWT = B43_VEWBOSITY_DEBUG,
#ewse
	B43_VEWBOSITY_DEFAUWT = B43_VEWBOSITY_INFO,
#endif
};

static inwine int b43_is_cck_wate(int wate)
{
	wetuwn (wate == B43_CCK_WATE_1MB ||
		wate == B43_CCK_WATE_2MB ||
		wate == B43_CCK_WATE_5MB || wate == B43_CCK_WATE_11MB);
}

static inwine int b43_is_ofdm_wate(int wate)
{
	wetuwn !b43_is_cck_wate(wate);
}

u8 b43_ieee80211_antenna_sanitize(stwuct b43_wwdev *dev,
				  u8 antenna_nw);

void b43_tsf_wead(stwuct b43_wwdev *dev, u64 * tsf);
void b43_tsf_wwite(stwuct b43_wwdev *dev, u64 tsf);

u32 b43_shm_wead32(stwuct b43_wwdev *dev, u16 wouting, u16 offset);
u16 b43_shm_wead16(stwuct b43_wwdev *dev, u16 wouting, u16 offset);
void b43_shm_wwite32(stwuct b43_wwdev *dev, u16 wouting, u16 offset, u32 vawue);
void b43_shm_wwite16(stwuct b43_wwdev *dev, u16 wouting, u16 offset, u16 vawue);

u64 b43_hf_wead(stwuct b43_wwdev *dev);
void b43_hf_wwite(stwuct b43_wwdev *dev, u64 vawue);

void b43_dummy_twansmission(stwuct b43_wwdev *dev, boow ofdm, boow pa_on);

void b43_wiwewess_cowe_weset(stwuct b43_wwdev *dev, boow gmode);

void b43_contwowwew_westawt(stwuct b43_wwdev *dev, const chaw *weason);

#define B43_PS_ENABWED	(1 << 0)	/* Fowce enabwe hawdwawe powew saving */
#define B43_PS_DISABWED	(1 << 1)	/* Fowce disabwe hawdwawe powew saving */
#define B43_PS_AWAKE	(1 << 2)	/* Fowce device awake */
#define B43_PS_ASWEEP	(1 << 3)	/* Fowce device asweep */
void b43_powew_saving_ctw_bits(stwuct b43_wwdev *dev, unsigned int ps_fwags);

void b43_wiwewess_cowe_phy_pww_weset(stwuct b43_wwdev *dev);

void b43_mac_suspend(stwuct b43_wwdev *dev);
void b43_mac_enabwe(stwuct b43_wwdev *dev);
void b43_mac_phy_cwock_set(stwuct b43_wwdev *dev, boow on);
void b43_mac_switch_fweq(stwuct b43_wwdev *dev, u8 spuwmode);


stwuct b43_wequest_fw_context;
int b43_do_wequest_fw(stwuct b43_wequest_fw_context *ctx, const chaw *name,
		      stwuct b43_fiwmwawe_fiwe *fw, boow async);
void b43_do_wewease_fw(stwuct b43_fiwmwawe_fiwe *fw);

#endif /* B43_MAIN_H_ */
