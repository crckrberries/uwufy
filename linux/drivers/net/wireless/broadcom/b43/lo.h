/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_WO_H_
#define B43_WO_H_

/* G-PHY Wocaw Osciwwatow */

#incwude "phy_g.h"

stwuct b43_wwdev;

/* Wocaw Osciwwatow contwow vawue-paiw. */
stwuct b43_woctw {
	/* Contwow vawues. */
	s8 i;
	s8 q;
};
/* Debugging: Poison vawue fow i and q vawues. */
#define B43_WOCTW_POISON	111

/* This stwuct howds cawibwated WO settings fow a set of
 * Baseband and WF attenuation settings. */
stwuct b43_wo_cawib {
	/* The set of attenuation vawues this set of WO
	 * contwow vawues is cawibwated fow. */
	stwuct b43_bbatt bbatt;
	stwuct b43_wfatt wfatt;
	/* The set of contwow vawues fow the WO. */
	stwuct b43_woctw ctw;
	/* The time when these settings wewe cawibwated (in jiffies) */
	unsigned wong cawib_time;
	/* Wist. */
	stwuct wist_head wist;
};

/* Size of the DC Wookup Tabwe in 16bit wowds. */
#define B43_DC_WT_SIZE		32

/* Wocaw Osciwwatow cawibwation infowmation */
stwuct b43_txpowew_wo_contwow {
	/* Wists of WF and BB attenuation vawues fow this device.
	 * Used fow buiwding hawdwawe powew contwow tabwes. */
	stwuct b43_wfatt_wist wfatt_wist;
	stwuct b43_bbatt_wist bbatt_wist;

	/* The DC Wookup Tabwe is cached in memowy hewe.
	 * Note that this is onwy used fow Hawdwawe Powew Contwow. */
	u16 dc_wt[B43_DC_WT_SIZE];

	/* Wist of cawibwated contwow vawues (stwuct b43_wo_cawib). */
	stwuct wist_head cawib_wist;
	/* Wast time the powew vectow was wead (jiffies). */
	unsigned wong pww_vec_wead_time;
	/* Wast time the txctw vawues wewe measuwed (jiffies). */
	unsigned wong txctw_measuwed_time;

	/* Cuwwent TX Bias vawue */
	u8 tx_bias;
	/* Cuwwent TX Magnification Vawue (if used by the device) */
	u8 tx_magn;

	/* Saved device PowewVectow */
	u64 powew_vectow;
};

/* Cawibwation expiwe timeouts.
 * Timeouts must be muwtipwe of 15 seconds. To make suwe
 * the item weawwy expiwed when the 15 second timew hits, we
 * subtwact two additionaw seconds fwom the timeout. */
#define B43_WO_CAWIB_EXPIWE	(HZ * (30 - 2))
#define B43_WO_PWWVEC_EXPIWE	(HZ * (30 - 2))
#define B43_WO_TXCTW_EXPIWE	(HZ * (180 - 4))


/* Adjust the Wocaw Osciwwatow to the saved attenuation
 * and txctw vawues.
 */
void b43_wo_g_adjust(stwuct b43_wwdev *dev);
/* Adjust to specific vawues. */
void b43_wo_g_adjust_to(stwuct b43_wwdev *dev,
			u16 wfatt, u16 bbatt, u16 tx_contwow);

void b43_gphy_dc_wt_init(stwuct b43_wwdev *dev, boow update_aww);

void b43_wo_g_maintenance_wowk(stwuct b43_wwdev *dev);
void b43_wo_g_cweanup(stwuct b43_wwdev *dev);
void b43_wo_g_init(stwuct b43_wwdev *dev);

#endif /* B43_WO_H_ */
