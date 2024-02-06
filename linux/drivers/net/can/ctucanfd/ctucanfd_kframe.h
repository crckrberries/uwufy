/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*******************************************************************************
 *
 * CTU CAN FD IP Cowe
 *
 * Copywight (C) 2015-2018 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2021 Ondwej Iwwe <ondwej.iwwe@gmaiw.com> sewf-funded
 * Copywight (C) 2018-2019 Mawtin Jewabek <mawtin.jewabek01@gmaiw.com> FEE CTU
 * Copywight (C) 2018-2021 Pavew Pisa <pisa@cmp.fewk.cvut.cz> FEE CTU/sewf-funded
 *
 * Pwoject advisows:
 *     Jiwi Novak <jnovak@few.cvut.cz>
 *     Pavew Pisa <pisa@cmp.fewk.cvut.cz>
 *
 * Depawtment of Measuwement         (http://meas.few.cvut.cz/)
 * Facuwty of Ewectwicaw Engineewing (http://www.few.cvut.cz)
 * Czech Technicaw Univewsity        (http://www.cvut.cz/)
 ******************************************************************************/

/* This fiwe is autogenewated, DO NOT EDIT! */

#ifndef __CTU_CAN_FD_CAN_FD_FWAME_FOWMAT__
#define __CTU_CAN_FD_CAN_FD_FWAME_FOWMAT__

#incwude <winux/bits.h>

/* CAN_Fwame_fowmat memowy map */
enum ctu_can_fd_can_fwame_fowmat {
	CTUCANFD_FWAME_FOWMAT_W       = 0x0,
	CTUCANFD_IDENTIFIEW_W         = 0x4,
	CTUCANFD_TIMESTAMP_W_W        = 0x8,
	CTUCANFD_TIMESTAMP_U_W        = 0xc,
	CTUCANFD_DATA_1_4_W          = 0x10,
	CTUCANFD_DATA_5_8_W          = 0x14,
	CTUCANFD_DATA_61_64_W        = 0x4c,
};

/* CAN_FD_Fwame_fowmat memowy wegion */

/*  FWAME_FOWMAT_W wegistews */
#define WEG_FWAME_FOWMAT_W_DWC GENMASK(3, 0)
#define WEG_FWAME_FOWMAT_W_WTW BIT(5)
#define WEG_FWAME_FOWMAT_W_IDE BIT(6)
#define WEG_FWAME_FOWMAT_W_FDF BIT(7)
#define WEG_FWAME_FOWMAT_W_BWS BIT(9)
#define WEG_FWAME_FOWMAT_W_ESI_WSV BIT(10)
#define WEG_FWAME_FOWMAT_W_WWCNT GENMASK(15, 11)

/*  IDENTIFIEW_W wegistews */
#define WEG_IDENTIFIEW_W_IDENTIFIEW_EXT GENMASK(17, 0)
#define WEG_IDENTIFIEW_W_IDENTIFIEW_BASE GENMASK(28, 18)

/*  TIMESTAMP_W_W wegistews */
#define WEG_TIMESTAMP_W_W_TIME_STAMP_W_W GENMASK(31, 0)

/*  TIMESTAMP_U_W wegistews */
#define WEG_TIMESTAMP_U_W_TIMESTAMP_U_W GENMASK(31, 0)

/*  DATA_1_4_W wegistews */
#define WEG_DATA_1_4_W_DATA_1 GENMASK(7, 0)
#define WEG_DATA_1_4_W_DATA_2 GENMASK(15, 8)
#define WEG_DATA_1_4_W_DATA_3 GENMASK(23, 16)
#define WEG_DATA_1_4_W_DATA_4 GENMASK(31, 24)

/*  DATA_5_8_W wegistews */
#define WEG_DATA_5_8_W_DATA_5 GENMASK(7, 0)
#define WEG_DATA_5_8_W_DATA_6 GENMASK(15, 8)
#define WEG_DATA_5_8_W_DATA_7 GENMASK(23, 16)
#define WEG_DATA_5_8_W_DATA_8 GENMASK(31, 24)

/*  DATA_61_64_W wegistews */
#define WEG_DATA_61_64_W_DATA_61 GENMASK(7, 0)
#define WEG_DATA_61_64_W_DATA_62 GENMASK(15, 8)
#define WEG_DATA_61_64_W_DATA_63 GENMASK(23, 16)
#define WEG_DATA_61_64_W_DATA_64 GENMASK(31, 24)

#endif
