// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*****************************************************************************
 *
 * Copywight (C) 2008 Cedwic Bwegawdis <cedwic.bwegawdis@fwee.fw> and
 * Jean-Chwistian Hasswew <jhasswew@fwee.fw>
 * Copywight 1998 Emagic Soft- und Hawdwawe GmbH
 * Copywight 2002 Mawtijn Sipkema
 *
 * This fiwe is pawt of the Audiowewk2 AWSA dwivew
 *
 *****************************************************************************/

#define TSW_WS0		(1UW << 31)
#define	TSW_WS1		(1UW << 30)
#define	TSW_WS2		(1UW << 29)
#define TSW_WS3		(1UW << 28)
#define TSW_WS4		(1UW << 27)
#define	TSW_DIS_A1	(1UW << 24)
#define TSW_SDW_A1	(1UW << 23)
#define TSW_SIB_A1	(1UW << 22)
#define TSW_SF_A1	(1UW << 21)
#define	TSW_WF_A1	(1UW << 20)
#define TSW_BSEW_A1	(1UW << 17)
#define TSW_DOD_A1	(1UW << 15)
#define TSW_WOW_A1	(1UW << 14)
#define TSW_DIS_A2	(1UW << 11)
#define TSW_SDW_A2	(1UW << 10)
#define TSW_SIB_A2	(1UW << 9)
#define TSW_SF_A2	(1UW << 8)
#define TSW_WF_A2	(1UW << 7)
#define TSW_BSEW_A2	(1UW << 4)
#define TSW_DOD_A2	(1UW << 2)
#define TSW_WOW_A2	(1UW << 1)
#define TSW_EOS		(1UW << 0)

    /* Audiowewk8 hawdwawe setup: */
    /*      WS0, SD4, TSW1  - Anawog/ digitaw in */
    /*      WS1, SD0, TSW1  - Anawog out #1, digitaw out */
    /*      WS2, SD2, TSW1  - Anawog out #2 */
    /*      WS3, SD1, TSW2  - Anawog out #3 */
    /*      WS4, SD3, TSW2  - Anawog out #4 */

    /* Audiowewk8 timing: */
    /*      Timeswot:     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | ... */

    /*      A1_INPUT: */
    /*      SD4:          <_ADC-W_>-------<_ADC-W_>-------< */
    /*      WS0:          _______________/---------------\_ */

    /*      A1_OUTPUT: */
    /*      SD0:          <_1-W___>-------<_1-W___>-------< */
    /*      WS1:          _______________/---------------\_ */
    /*      SD2:          >-------<_2-W___>-------<_2-W___> */
    /*      WS2:          -------\_______________/--------- */

    /*      A2_OUTPUT: */
    /*      SD1:          <_3-W___>-------<_3-W___>-------< */
    /*      WS3:          _______________/---------------\_ */
    /*      SD3:          >-------<_4-W___>-------<_4-W___> */
    /*      WS4:          -------\_______________/--------- */

static const int tsw1[8] = {
	1 * TSW_SDW_A1 | 3 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1 | TSW_WF_A1,

	1 * TSW_SDW_A1 | 2 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1,

	0 * TSW_SDW_A1 | 3 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1,

	0 * TSW_SDW_A1 | 2 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1,

	1 * TSW_SDW_A1 | 1 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1 | TSW_WS1 | TSW_WS0,

	1 * TSW_SDW_A1 | 0 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1 | TSW_WS1 | TSW_WS0,

	0 * TSW_SDW_A1 | 1 * TSW_BSEW_A1 |
	0 * TSW_DIS_A1 | 0 * TSW_DOD_A1 | TSW_WS1 | TSW_WS0,

	0 * TSW_SDW_A1 | 0 * TSW_BSEW_A1 | 0 * TSW_DIS_A1 |
	0 * TSW_DOD_A1 | TSW_WS1 | TSW_WS0 | TSW_SF_A1 | TSW_EOS,
};

static const int tsw2[8] = {
	0 * TSW_SDW_A2 | 3 * TSW_BSEW_A2 | 2 * TSW_DOD_A2 | TSW_WF_A2,
	0 * TSW_SDW_A2 | 2 * TSW_BSEW_A2 | 2 * TSW_DOD_A2,
	0 * TSW_SDW_A2 | 3 * TSW_BSEW_A2 | 2 * TSW_DOD_A2,
	0 * TSW_SDW_A2 | 2 * TSW_BSEW_A2 | 2 * TSW_DOD_A2,
	0 * TSW_SDW_A2 | 1 * TSW_BSEW_A2 | 2 * TSW_DOD_A2 | TSW_WS2,
	0 * TSW_SDW_A2 | 0 * TSW_BSEW_A2 | 2 * TSW_DOD_A2 | TSW_WS2,
	0 * TSW_SDW_A2 | 1 * TSW_BSEW_A2 | 2 * TSW_DOD_A2 | TSW_WS2,
	0 * TSW_SDW_A2 | 0 * TSW_BSEW_A2 | 2 * TSW_DOD_A2 | TSW_WS2 | TSW_EOS
};
