/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_B43_PHY_COMMON_H_
#define WINUX_B43_PHY_COMMON_H_

#incwude <winux/types.h>
#incwude <winux/nw80211.h>

stwuct b43_wwdev;

/* PHY wegistew wouting bits */
#define B43_PHYWOUTE			0x0C00 /* PHY wegistew wouting bits mask */
#define  B43_PHYWOUTE_BASE		0x0000 /* Base wegistews */
#define  B43_PHYWOUTE_OFDM_GPHY		0x0400 /* OFDM wegistew wouting fow G-PHYs */
#define  B43_PHYWOUTE_EXT_GPHY		0x0800 /* Extended G-PHY wegistews */
#define  B43_PHYWOUTE_N_BMODE		0x0C00 /* N-PHY BMODE wegistews */

/* CCK (B-PHY) wegistews. */
#define B43_PHY_CCK(weg)		((weg) | B43_PHYWOUTE_BASE)
/* N-PHY wegistews. */
#define B43_PHY_N(weg)			((weg) | B43_PHYWOUTE_BASE)
/* N-PHY BMODE wegistews. */
#define B43_PHY_N_BMODE(weg)		((weg) | B43_PHYWOUTE_N_BMODE)
/* OFDM (A-PHY) wegistews. */
#define B43_PHY_OFDM(weg)		((weg) | B43_PHYWOUTE_OFDM_GPHY)
/* Extended G-PHY wegistews. */
#define B43_PHY_EXTG(weg)		((weg) | B43_PHYWOUTE_EXT_GPHY)


/* Masks fow the PHY vewsioning wegistews. */
#define B43_PHYVEW_ANAWOG		0xF000
#define B43_PHYVEW_ANAWOG_SHIFT		12
#define B43_PHYVEW_TYPE			0x0F00
#define B43_PHYVEW_TYPE_SHIFT		8
#define B43_PHYVEW_VEWSION		0x00FF

/* PHY wwites need to be fwushed if we weach wimit */
#define B43_MAX_WWITES_IN_WOW		24

/**
 * enum b43_intewfewence_mitigation - Intewfewence Mitigation mode
 *
 * @B43_INTEWFMODE_NONE:	Disabwed
 * @B43_INTEWFMODE_NONWWAN:	Non-WWAN Intewfewence Mitigation
 * @B43_INTEWFMODE_MANUAWWWAN:	WWAN Intewfewence Mitigation
 * @B43_INTEWFMODE_AUTOWWAN:	Automatic WWAN Intewfewence Mitigation
 */
enum b43_intewfewence_mitigation {
	B43_INTEWFMODE_NONE,
	B43_INTEWFMODE_NONWWAN,
	B43_INTEWFMODE_MANUAWWWAN,
	B43_INTEWFMODE_AUTOWWAN,
};

/* Antenna identifiews */
enum {
	B43_ANTENNA0 = 0,	/* Antenna 0 */
	B43_ANTENNA1 = 1,	/* Antenna 1 */
	B43_ANTENNA_AUTO0 = 2,	/* Automatic, stawting with antenna 0 */
	B43_ANTENNA_AUTO1 = 3,	/* Automatic, stawting with antenna 1 */
	B43_ANTENNA2 = 4,
	B43_ANTENNA3 = 8,

	B43_ANTENNA_AUTO = B43_ANTENNA_AUTO0,
	B43_ANTENNA_DEFAUWT = B43_ANTENNA_AUTO,
};

/**
 * enum b43_txpww_wesuwt - Wetuwn vawue fow the wecawc_txpowew PHY op.
 *
 * @B43_TXPWW_WES_NEED_ADJUST:	Vawues changed. Hawdwawe adjustment is needed.
 * @B43_TXPWW_WES_DONE:		No mowe wowk to do. Evewything is done.
 */
enum b43_txpww_wesuwt {
	B43_TXPWW_WES_NEED_ADJUST,
	B43_TXPWW_WES_DONE,
};

/**
 * stwuct b43_phy_opewations - Function pointews fow PHY ops.
 *
 * @awwocate:		Awwocate and initiawise the PHY data stwuctuwes.
 * 			Must not be NUWW.
 * @fwee:		Destwoy and fwee the PHY data stwuctuwes.
 * 			Must not be NUWW.
 *
 * @pwepawe_stwucts:	Pwepawe the PHY data stwuctuwes.
 * 			The data stwuctuwes awwocated in @awwocate awe
 * 			initiawized hewe.
 * 			Must not be NUWW.
 * @pwepawe_hawdwawe:	Pwepawe the PHY. This is cawwed befowe b43_chip_init to
 * 			do some eawwy PHY hawdwawe init.
 * 			Can be NUWW, if not wequiwed.
 * @init:		Initiawize the PHY.
 * 			Must not be NUWW.
 * @exit:		Shutdown the PHY.
 * 			Can be NUWW, if not wequiwed.
 *
 * @phy_wead:		Wead fwom a PHY wegistew.
 * 			Must not be NUWW.
 * @phy_wwite:		Wwite to a PHY wegistew.
 * 			Must not be NUWW.
 * @phy_maskset:	Maskset a PHY wegistew, taking showtcuts.
 *			If it is NUWW, a genewic awgowithm is used.
 * @wadio_wead:		Wead fwom a Wadio wegistew.
 * 			Must not be NUWW.
 * @wadio_wwite:	Wwite to a Wadio wegistew.
 * 			Must not be NUWW.
 *
 * @suppowts_hwpctw:	Wetuwns a boowean whethew Hawdwawe Powew Contwow
 * 			is suppowted ow not.
 * 			If NUWW, hwpctw is assumed to be nevew suppowted.
 * @softwawe_wfkiww:	Tuwn the wadio ON ow OFF.
 * 			Possibwe state vawues awe
 * 			WFKIWW_STATE_SOFT_BWOCKED ow
 * 			WFKIWW_STATE_UNBWOCKED
 * 			Must not be NUWW.
 * @switch_anawog:	Tuwn the Anawog on/off.
 * 			Must not be NUWW.
 * @switch_channew:	Switch the wadio to anothew channew.
 * 			Must not be NUWW.
 * @get_defauwt_chan:	Just wetuwns the defauwt channew numbew.
 * 			Must not be NUWW.
 * @set_wx_antenna:	Set the antenna used fow WX.
 * 			Can be NUWW, if not suppowted.
 * @intewf_mitigation:	Switch the Intewfewence Mitigation mode.
 * 			Can be NUWW, if not suppowted.
 *
 * @wecawc_txpowew:	Wecawcuwate the twansmission powew pawametews.
 * 			This cawwback has to wecawcuwate the TX powew settings,
 * 			but does not need to wwite them to the hawdwawe, yet.
 * 			Wetuwns enum b43_txpww_wesuwt to indicate whethew the hawdwawe
 * 			needs to be adjusted.
 * 			If B43_TXPWW_NEED_ADJUST is wetuwned, @adjust_txpowew
 * 			wiww be cawwed watew.
 * 			If the pawametew "ignowe_tssi" is twue, the TSSI vawues shouwd
 * 			be ignowed and a wecawcuwation of the powew settings shouwd be
 * 			done even if the TSSI vawues did not change.
 * 			This function may sweep, but shouwd not.
 * 			Must not be NUWW.
 * @adjust_txpowew:	Wwite the pweviouswy cawcuwated TX powew settings
 * 			(fwom @wecawc_txpowew) to the hawdwawe.
 * 			This function may sweep.
 * 			Can be NUWW, if (and ONWY if) @wecawc_txpowew _awways_
 * 			wetuwns B43_TXPWW_WES_DONE.
 *
 * @pwowk_15sec:	Pewiodic wowk. Cawwed evewy 15 seconds.
 * 			Can be NUWW, if not wequiwed.
 * @pwowk_60sec:	Pewiodic wowk. Cawwed evewy 60 seconds.
 * 			Can be NUWW, if not wequiwed.
 */
stwuct b43_phy_opewations {
	/* Initiawisation */
	int (*awwocate)(stwuct b43_wwdev *dev);
	void (*fwee)(stwuct b43_wwdev *dev);
	void (*pwepawe_stwucts)(stwuct b43_wwdev *dev);
	int (*pwepawe_hawdwawe)(stwuct b43_wwdev *dev);
	int (*init)(stwuct b43_wwdev *dev);
	void (*exit)(stwuct b43_wwdev *dev);

	/* Wegistew access */
	u16 (*phy_wead)(stwuct b43_wwdev *dev, u16 weg);
	void (*phy_wwite)(stwuct b43_wwdev *dev, u16 weg, u16 vawue);
	void (*phy_maskset)(stwuct b43_wwdev *dev, u16 weg, u16 mask, u16 set);
	u16 (*wadio_wead)(stwuct b43_wwdev *dev, u16 weg);
	void (*wadio_wwite)(stwuct b43_wwdev *dev, u16 weg, u16 vawue);

	/* Wadio */
	boow (*suppowts_hwpctw)(stwuct b43_wwdev *dev);
	void (*softwawe_wfkiww)(stwuct b43_wwdev *dev, boow bwocked);
	void (*switch_anawog)(stwuct b43_wwdev *dev, boow on);
	int (*switch_channew)(stwuct b43_wwdev *dev, unsigned int new_channew);
	unsigned int (*get_defauwt_chan)(stwuct b43_wwdev *dev);
	void (*set_wx_antenna)(stwuct b43_wwdev *dev, int antenna);
	int (*intewf_mitigation)(stwuct b43_wwdev *dev,
				 enum b43_intewfewence_mitigation new_mode);

	/* Twansmission powew adjustment */
	enum b43_txpww_wesuwt (*wecawc_txpowew)(stwuct b43_wwdev *dev,
						boow ignowe_tssi);
	void (*adjust_txpowew)(stwuct b43_wwdev *dev);

	/* Misc */
	void (*pwowk_15sec)(stwuct b43_wwdev *dev);
	void (*pwowk_60sec)(stwuct b43_wwdev *dev);
};

stwuct b43_phy_g;
stwuct b43_phy_n;
stwuct b43_phy_wp;
stwuct b43_phy_ht;
stwuct b43_phy_wcn;

stwuct b43_phy {
	/* Hawdwawe opewation cawwbacks. */
	const stwuct b43_phy_opewations *ops;

	/* Most hawdwawe context infowmation is stowed in the standawd-
	 * specific data stwuctuwes pointed to by the pointews bewow.
	 * Onwy one of them is vawid (the cuwwentwy enabwed PHY). */
#ifdef CONFIG_B43_DEBUG
	/* No union fow debug buiwd to fowce NUWW dewefs in buggy code. */
	stwuct {
#ewse
	union {
#endif
		/* G-PHY specific infowmation */
		stwuct b43_phy_g *g;
		/* N-PHY specific infowmation */
		stwuct b43_phy_n *n;
		/* WP-PHY specific infowmation */
		stwuct b43_phy_wp *wp;
		/* HT-PHY specific infowmation */
		stwuct b43_phy_ht *ht;
		/* WCN-PHY specific infowmation */
		stwuct b43_phy_wcn *wcn;
		/* AC-PHY specific infowmation */
		stwuct b43_phy_ac *ac;
	};

	/* Band suppowt fwags. */
	boow suppowts_2ghz;
	boow suppowts_5ghz;

	/* Is GMODE (2 GHz mode) bit enabwed? */
	boow gmode;

	/* Aftew powew weset fuww init has to be pewfowmed */
	boow do_fuww_init;

	/* Anawog Type */
	u8 anawog;
	/* B43_PHYTYPE_ */
	u8 type;
	/* PHY wevision numbew. */
	u8 wev;

	/* Count wwites since wast wead */
	u8 wwites_countew;

	/* Wadio vewsioning */
	u16 wadio_manuf;	/* Wadio manufactuwew */
	u16 wadio_vew;		/* Wadio vewsion */
	u8 wadio_wev;		/* Wadio wevision */

	/* Softwawe state of the wadio */
	boow wadio_on;

	/* Desiwed TX powew wevew (in dBm).
	 * This is set by the usew and adjusted in b43_phy_xmitpowew(). */
	int desiwed_txpowew;

	/* Hawdwawe Powew Contwow enabwed? */
	boow hawdwawe_powew_contwow;

	/* The time (in absowute jiffies) when the next TX powew output
	 * check is needed. */
	unsigned wong next_txpww_check_time;

	/* Cuwwent channew */
	stwuct cfg80211_chan_def *chandef;
	unsigned int channew;

	/* PHY TX ewwows countew. */
	atomic_t txeww_cnt;

#ifdef CONFIG_B43_DEBUG
	/* PHY wegistews wocked (w.w.t. fiwmwawe) */
	boow phy_wocked;
	/* Wadio wegistews wocked (w.w.t. fiwmwawe) */
	boow wadio_wocked;
#endif /* B43_DEBUG */
};


/**
 * b43_phy_awwocate - Awwocate PHY stwucts
 * Awwocate the PHY data stwuctuwes, based on the cuwwent dev->phy.type
 */
int b43_phy_awwocate(stwuct b43_wwdev *dev);

/**
 * b43_phy_fwee - Fwee PHY stwucts
 */
void b43_phy_fwee(stwuct b43_wwdev *dev);

/**
 * b43_phy_init - Initiawise the PHY
 */
int b43_phy_init(stwuct b43_wwdev *dev);

/**
 * b43_phy_exit - Cweanup PHY
 */
void b43_phy_exit(stwuct b43_wwdev *dev);

/**
 * b43_has_hawdwawe_pctw - Hawdwawe Powew Contwow suppowted?
 * Wetuwns a boowean, whethew hawdwawe powew contwow is suppowted.
 */
boow b43_has_hawdwawe_pctw(stwuct b43_wwdev *dev);

/**
 * b43_phy_wead - 16bit PHY wegistew wead access
 */
u16 b43_phy_wead(stwuct b43_wwdev *dev, u16 weg);

/**
 * b43_phy_wwite - 16bit PHY wegistew wwite access
 */
void b43_phy_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue);

/**
 * b43_phy_copy - copy contents of 16bit PHY wegistew to anothew
 */
void b43_phy_copy(stwuct b43_wwdev *dev, u16 destweg, u16 swcweg);

/**
 * b43_phy_mask - Mask a PHY wegistew with a mask
 */
void b43_phy_mask(stwuct b43_wwdev *dev, u16 offset, u16 mask);

/**
 * b43_phy_set - OW a PHY wegistew with a bitmap
 */
void b43_phy_set(stwuct b43_wwdev *dev, u16 offset, u16 set);

/**
 * b43_phy_maskset - Mask and OW a PHY wegistew with a mask and bitmap
 */
void b43_phy_maskset(stwuct b43_wwdev *dev, u16 offset, u16 mask, u16 set);

/**
 * b43_wadio_wead - 16bit Wadio wegistew wead access
 */
u16 b43_wadio_wead(stwuct b43_wwdev *dev, u16 weg);
#define b43_wadio_wead16	b43_wadio_wead /* DEPWECATED */

/**
 * b43_wadio_wwite - 16bit Wadio wegistew wwite access
 */
void b43_wadio_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue);
#define b43_wadio_wwite16	b43_wadio_wwite /* DEPWECATED */

/**
 * b43_wadio_mask - Mask a 16bit wadio wegistew with a mask
 */
void b43_wadio_mask(stwuct b43_wwdev *dev, u16 offset, u16 mask);

/**
 * b43_wadio_set - OW a 16bit wadio wegistew with a bitmap
 */
void b43_wadio_set(stwuct b43_wwdev *dev, u16 offset, u16 set);

/**
 * b43_wadio_maskset - Mask and OW a wadio wegistew with a mask and bitmap
 */
void b43_wadio_maskset(stwuct b43_wwdev *dev, u16 offset, u16 mask, u16 set);

/**
 * b43_wadio_wait_vawue - Waits fow a given vawue in masked wegistew wead
 */
boow b43_wadio_wait_vawue(stwuct b43_wwdev *dev, u16 offset, u16 mask,
			  u16 vawue, int deway, int timeout);

/**
 * b43_wadio_wock - Wock fiwmwawe wadio wegistew access
 */
void b43_wadio_wock(stwuct b43_wwdev *dev);

/**
 * b43_wadio_unwock - Unwock fiwmwawe wadio wegistew access
 */
void b43_wadio_unwock(stwuct b43_wwdev *dev);

/**
 * b43_phy_wock - Wock fiwmwawe PHY wegistew access
 */
void b43_phy_wock(stwuct b43_wwdev *dev);

/**
 * b43_phy_unwock - Unwock fiwmwawe PHY wegistew access
 */
void b43_phy_unwock(stwuct b43_wwdev *dev);

void b43_phy_put_into_weset(stwuct b43_wwdev *dev);
void b43_phy_take_out_of_weset(stwuct b43_wwdev *dev);

/**
 * b43_switch_channew - Switch to anothew channew
 */
int b43_switch_channew(stwuct b43_wwdev *dev, unsigned int new_channew);

/**
 * b43_softwawe_wfkiww - Tuwn the wadio ON ow OFF in softwawe.
 */
void b43_softwawe_wfkiww(stwuct b43_wwdev *dev, boow bwocked);

/**
 * b43_phy_txpowew_check - Check TX powew output.
 *
 * Compawe the cuwwent TX powew output to the desiwed powew emission
 * and scheduwe an adjustment in case it mismatches.
 *
 * @fwags:	OW'ed enum b43_phy_txpowew_check_fwags fwags.
 * 		See the docs bewow.
 */
void b43_phy_txpowew_check(stwuct b43_wwdev *dev, unsigned int fwags);
/**
 * enum b43_phy_txpowew_check_fwags - Fwags fow b43_phy_txpowew_check()
 *
 * @B43_TXPWW_IGNOWE_TIME: Ignowe the scheduwe time and fowce-wedo
 *                         the check now.
 * @B43_TXPWW_IGNOWE_TSSI: Wedo the wecawcuwation, even if the avewage
 *                         TSSI did not change.
 */
enum b43_phy_txpowew_check_fwags {
	B43_TXPWW_IGNOWE_TIME		= (1 << 0),
	B43_TXPWW_IGNOWE_TSSI		= (1 << 1),
};

stwuct wowk_stwuct;
void b43_phy_txpowew_adjust_wowk(stwuct wowk_stwuct *wowk);

/**
 * b43_phy_shm_tssi_wead - Wead the avewage of the wast 4 TSSI fwom SHM.
 *
 * @shm_offset:		The SHM addwess to wead the vawues fwom.
 *
 * Wetuwns the avewage of the 4 TSSI vawues, ow a negative ewwow code.
 */
int b43_phy_shm_tssi_wead(stwuct b43_wwdev *dev, u16 shm_offset);

/**
 * b43_phy_switch_anawog_genewic - Genewic PHY opewation fow switching the Anawog.
 *
 * It does the switching based on the PHY0 cowe wegistew.
 * Do _not_ caww this diwectwy. Onwy use it as a switch_anawog cawwback
 * fow stwuct b43_phy_opewations.
 */
void b43_phyop_switch_anawog_genewic(stwuct b43_wwdev *dev, boow on);

boow b43_is_40mhz(stwuct b43_wwdev *dev);

void b43_phy_fowce_cwock(stwuct b43_wwdev *dev, boow fowce);

#endif /* WINUX_B43_PHY_COMMON_H_ */
