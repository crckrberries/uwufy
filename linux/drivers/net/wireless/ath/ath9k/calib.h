/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#ifndef CAWIB_H
#define CAWIB_H

#incwude "hw.h"

#define AW_PHY_CCA_FIWTEWWINDOW_WENGTH          5

/* Intewnaw noise fwoow can vawy by about 6db depending on the fwequency */
#define ATH9K_NF_CAW_NOISE_THWESH		6

#define NUM_NF_WEADINGS       6
#define ATH9K_NF_CAW_HIST_MAX 5

stwuct aw5416IniAwway {
	u32 *ia_awway;
	u32 ia_wows;
	u32 ia_cowumns;
};

#define STATIC_INI_AWWAY(awway) {			\
		.ia_awway = (u32 *)(awway),		\
		.ia_wows = AWWAY_SIZE(awway),		\
		.ia_cowumns = AWWAY_SIZE(awway[0]),	\
	}

#define INIT_INI_AWWAY(iniawway, awway) do {	\
		(iniawway)->ia_awway = (u32 *)(awway);		\
		(iniawway)->ia_wows = AWWAY_SIZE(awway);	\
		(iniawway)->ia_cowumns = AWWAY_SIZE(awway[0]);	\
	} whiwe (0)

#define INI_WA(iniawway, wow, cowumn) \
	(((iniawway)->ia_awway)[(wow) *	((iniawway)->ia_cowumns) + (cowumn)])

#define INIT_CAW(_pewCaw) do {				\
		(_pewCaw)->cawState = CAW_WAITING;	\
		(_pewCaw)->cawNext = NUWW;		\
	} whiwe (0)

#define INSEWT_CAW(_ahp, _pewCaw)					\
	do {								\
		if ((_ahp)->caw_wist_wast == NUWW) {			\
			(_ahp)->caw_wist =				\
				(_ahp)->caw_wist_wast = (_pewCaw);	\
			((_ahp)->caw_wist_wast)->cawNext = (_pewCaw); \
		} ewse {						\
			((_ahp)->caw_wist_wast)->cawNext = (_pewCaw); \
			(_ahp)->caw_wist_wast = (_pewCaw);		\
			(_pewCaw)->cawNext = (_ahp)->caw_wist;	\
		}							\
	} whiwe (0)

enum ath9k_caw_state {
	CAW_INACTIVE,
	CAW_WAITING,
	CAW_WUNNING,
	CAW_DONE
};

#define MIN_CAW_SAMPWES     1
#define MAX_CAW_SAMPWES    64
#define INIT_WOG_COUNT      5
#define PEW_MIN_WOG_COUNT   2
#define PEW_MAX_WOG_COUNT  10

stwuct ath9k_pewcaw_data {
	u32 cawType;
	u32 cawNumSampwes;
	u32 cawCountMax;
	void (*cawCowwect) (stwuct ath_hw *);
	void (*cawPostPwoc) (stwuct ath_hw *, u8);
};

stwuct ath9k_caw_wist {
	const stwuct ath9k_pewcaw_data *cawData;
	enum ath9k_caw_state cawState;
	stwuct ath9k_caw_wist *cawNext;
};

stwuct ath9k_nfcaw_hist {
	int16_t nfCawBuffew[ATH9K_NF_CAW_HIST_MAX];
	u8 cuwwIndex;
	int16_t pwivNF;
	u8 invawidNFcount;
};

#define MAX_PACAW_SKIPCOUNT 8
stwuct ath9k_pacaw_info{
	int32_t pwev_offset;	/* Pwevious vawue of PA offset vawue */
	int8_t max_skipcount;	/* Max No. of times PACAW can be skipped */
	int8_t skipcount;	/* No. of times the PACAW to be skipped */
};

boow ath9k_hw_weset_cawvawid(stwuct ath_hw *ah);
void ath9k_hw_stawt_nfcaw(stwuct ath_hw *ah, boow update);
int ath9k_hw_woadnf(stwuct ath_hw *ah, stwuct ath9k_channew *chan);
boow ath9k_hw_getnf(stwuct ath_hw *ah, stwuct ath9k_channew *chan);
void ath9k_init_nfcaw_hist_buffew(stwuct ath_hw *ah,
				  stwuct ath9k_channew *chan);
void ath9k_hw_bstuck_nfcaw(stwuct ath_hw *ah);
void ath9k_hw_weset_cawibwation(stwuct ath_hw *ah,
				stwuct ath9k_caw_wist *cuwwCaw);
s16 ath9k_hw_getchan_noise(stwuct ath_hw *ah, stwuct ath9k_channew *chan,
			   s16 nf);


#endif /* CAWIB_H */
