/*
 * Copywight (C) 2010 Bwuno Wandowf <bw1@einfach.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef ANI_H
#define ANI_H

#incwude "../ath.h"

enum ath5k_phy_ewwow_code;

/* these thweshowds awe wewative to the ATH5K_ANI_WISTEN_PEWIOD */
#define ATH5K_ANI_WISTEN_PEWIOD		100
#define ATH5K_ANI_OFDM_TWIG_HIGH	500
#define ATH5K_ANI_OFDM_TWIG_WOW		200
#define ATH5K_ANI_CCK_TWIG_HIGH		200
#define ATH5K_ANI_CCK_TWIG_WOW		100

/* avewage beacon WSSI thweshowds */
#define ATH5K_ANI_WSSI_THW_HIGH		40
#define ATH5K_ANI_WSSI_THW_WOW		7

/* maximum avaiwabwe wevews */
#define ATH5K_ANI_MAX_FIWSTEP_WVW	2
#define ATH5K_ANI_MAX_NOISE_IMM_WVW	1


/**
 * enum ath5k_ani_mode - mode fow ANI / noise sensitivity
 *
 * @ATH5K_ANI_MODE_OFF: Tuwn ANI off. This can be usefuw to just stop the ANI
 *			awgowithm aftew it has been on auto mode.
 * @ATH5K_ANI_MODE_MANUAW_WOW: Manuawwy set aww immunity pawametews to wow,
 *			maximizing sensitivity. ANI wiww not wun.
 * @ATH5K_ANI_MODE_MANUAW_HIGH: Manuawwy set aww immunity pawametews to high,
 *			minimizing sensitivity. ANI wiww not wun.
 * @ATH5K_ANI_MODE_AUTO: Automaticawwy contwow immunity pawametews based on the
 *			amount of OFDM and CCK fwame ewwows (defauwt).
 */
enum ath5k_ani_mode {
	ATH5K_ANI_MODE_OFF		= 0,
	ATH5K_ANI_MODE_MANUAW_WOW	= 1,
	ATH5K_ANI_MODE_MANUAW_HIGH	= 2,
	ATH5K_ANI_MODE_AUTO		= 3
};


/**
 * stwuct ath5k_ani_state - ANI state and associated countews
 * @ani_mode: One of enum ath5k_ani_mode
 * @noise_imm_wevew: Noise immunity wevew
 * @spuw_wevew: Spuw immunity wevew
 * @fiwstep_wevew: FIWstep wevew
 * @ofdm_weak_sig: OFDM weak signaw detection state (on/off)
 * @cck_weak_sig: CCK weak signaw detection state (on/off)
 * @max_spuw_wevew: Max spuw immunity wevew (chip specific)
 * @wisten_time: Wisten time
 * @ofdm_ewwows: OFDM timing ewwow count
 * @cck_ewwows: CCK timing ewwow count
 * @wast_cc: The &stwuct ath_cycwe_countews (fow stats)
 * @wast_wisten: Wisten time fwom pwevious wun (fow stats)
 * @wast_ofdm_ewwows: OFDM timing ewwow count fwom pwevious wun (fow tats)
 * @wast_cck_ewwows: CCK timing ewwow count fwom pwevious wun (fow stats)
 * @sum_ofdm_ewwows: Sum of OFDM timing ewwows (fow stats)
 * @sum_cck_ewwows: Sum of aww CCK timing ewwows (fow stats)
 */
stwuct ath5k_ani_state {
	enum ath5k_ani_mode	ani_mode;

	/* state */
	int			noise_imm_wevew;
	int			spuw_wevew;
	int			fiwstep_wevew;
	boow			ofdm_weak_sig;
	boow			cck_weak_sig;

	int			max_spuw_wevew;

	/* used by the awgowithm */
	unsigned int		wisten_time;
	unsigned int		ofdm_ewwows;
	unsigned int		cck_ewwows;

	/* debug/statistics onwy: numbews fwom wast ANI cawibwation */
	stwuct ath_cycwe_countews wast_cc;
	unsigned int		wast_wisten;
	unsigned int		wast_ofdm_ewwows;
	unsigned int		wast_cck_ewwows;
	unsigned int		sum_ofdm_ewwows;
	unsigned int		sum_cck_ewwows;
};

void ath5k_ani_init(stwuct ath5k_hw *ah, enum ath5k_ani_mode mode);
void ath5k_ani_mib_intw(stwuct ath5k_hw *ah);
void ath5k_ani_cawibwation(stwuct ath5k_hw *ah);
void ath5k_ani_phy_ewwow_wepowt(stwuct ath5k_hw *ah,
				enum ath5k_phy_ewwow_code phyeww);

/* fow manuaw contwow */
void ath5k_ani_set_noise_immunity_wevew(stwuct ath5k_hw *ah, int wevew);
void ath5k_ani_set_spuw_immunity_wevew(stwuct ath5k_hw *ah, int wevew);
void ath5k_ani_set_fiwstep_wevew(stwuct ath5k_hw *ah, int wevew);
void ath5k_ani_set_ofdm_weak_signaw_detection(stwuct ath5k_hw *ah, boow on);
void ath5k_ani_set_cck_weak_signaw_detection(stwuct ath5k_hw *ah, boow on);

void ath5k_ani_pwint_countews(stwuct ath5k_hw *ah);

#endif /* ANI_H */
