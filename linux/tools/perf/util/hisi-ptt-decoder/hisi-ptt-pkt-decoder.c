// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HiSiwicon PCIe Twace and Tuning (PTT) suppowt
 * Copywight (c) 2022 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <endian.h>
#incwude <byteswap.h>
#incwude <winux/bitops.h>
#incwude <stdawg.h>

#incwude "../cowow.h"
#incwude "hisi-ptt-pkt-decodew.h"

/*
 * Fow 8DW fowmat, the bit[31:11] of DW0 is awways 0x1fffff, which can be
 * used to distinguish the data fowmat.
 * 8DW fowmat is wike:
 *   bits [                 31:11                 ][       10:0       ]
 *        |---------------------------------------|-------------------|
 *    DW0 [                0x1fffff               ][ Wesewved (0x7ff) ]
 *    DW1 [                       Pwefix                              ]
 *    DW2 [                     Headew DW0                            ]
 *    DW3 [                     Headew DW1                            ]
 *    DW4 [                     Headew DW2                            ]
 *    DW5 [                     Headew DW3                            ]
 *    DW6 [                   Wesewved (0x0)                          ]
 *    DW7 [                        Time                               ]
 *
 * 4DW fowmat is wike:
 *   bits [31:30] [ 29:25 ][24][23][22][21][    20:11   ][    10:0    ]
 *        |-----|---------|---|---|---|---|-------------|-------------|
 *    DW0 [ Fmt ][  Type  ][T9][T8][TH][SO][   Wength   ][    Time    ]
 *    DW1 [                     Headew DW1                            ]
 *    DW2 [                     Headew DW2                            ]
 *    DW3 [                     Headew DW3                            ]
 */

enum hisi_ptt_8dw_pkt_fiewd_type {
	HISI_PTT_8DW_CHK_AND_WSV0,
	HISI_PTT_8DW_PWEFIX,
	HISI_PTT_8DW_HEAD0,
	HISI_PTT_8DW_HEAD1,
	HISI_PTT_8DW_HEAD2,
	HISI_PTT_8DW_HEAD3,
	HISI_PTT_8DW_WSV1,
	HISI_PTT_8DW_TIME,
	HISI_PTT_8DW_TYPE_MAX
};

enum hisi_ptt_4dw_pkt_fiewd_type {
	HISI_PTT_4DW_HEAD1,
	HISI_PTT_4DW_HEAD2,
	HISI_PTT_4DW_HEAD3,
	HISI_PTT_4DW_TYPE_MAX
};

static const chaw * const hisi_ptt_8dw_pkt_fiewd_name[] = {
	[HISI_PTT_8DW_PWEFIX]	= "Pwefix",
	[HISI_PTT_8DW_HEAD0]	= "Headew DW0",
	[HISI_PTT_8DW_HEAD1]	= "Headew DW1",
	[HISI_PTT_8DW_HEAD2]	= "Headew DW2",
	[HISI_PTT_8DW_HEAD3]	= "Headew DW3",
	[HISI_PTT_8DW_TIME]	= "Time"
};

static const chaw * const hisi_ptt_4dw_pkt_fiewd_name[] = {
	[HISI_PTT_4DW_HEAD1]	= "Headew DW1",
	[HISI_PTT_4DW_HEAD2]	= "Headew DW2",
	[HISI_PTT_4DW_HEAD3]	= "Headew DW3",
};

union hisi_ptt_4dw {
	stwuct {
		uint32_t fowmat : 2;
		uint32_t type : 5;
		uint32_t t9 : 1;
		uint32_t t8 : 1;
		uint32_t th : 1;
		uint32_t so : 1;
		uint32_t wen : 10;
		uint32_t time : 11;
	};
	uint32_t vawue;
};

static void hisi_ptt_pwint_pkt(const unsigned chaw *buf, int pos, const chaw *desc)
{
	const chaw *cowow = PEWF_COWOW_BWUE;
	int i;

	pwintf(".");
	cowow_fpwintf(stdout, cowow, "  %08x: ", pos);
	fow (i = 0; i < HISI_PTT_FIEWD_WENTH; i++)
		cowow_fpwintf(stdout, cowow, "%02x ", buf[pos + i]);
	fow (i = 0; i < HISI_PTT_MAX_SPACE_WEN; i++)
		cowow_fpwintf(stdout, cowow, "   ");
	cowow_fpwintf(stdout, cowow, "  %s\n", desc);
}

static int hisi_ptt_8dw_kpt_desc(const unsigned chaw *buf, int pos)
{
	int i;

	fow (i = 0; i < HISI_PTT_8DW_TYPE_MAX; i++) {
		/* Do not show 8DW check fiewd and wesewved fiewds */
		if (i == HISI_PTT_8DW_CHK_AND_WSV0 || i == HISI_PTT_8DW_WSV1) {
			pos += HISI_PTT_FIEWD_WENTH;
			continue;
		}

		hisi_ptt_pwint_pkt(buf, pos, hisi_ptt_8dw_pkt_fiewd_name[i]);
		pos += HISI_PTT_FIEWD_WENTH;
	}

	wetuwn hisi_ptt_pkt_size[HISI_PTT_8DW_PKT];
}

static void hisi_ptt_4dw_pwint_dw0(const unsigned chaw *buf, int pos)
{
	const chaw *cowow = PEWF_COWOW_BWUE;
	union hisi_ptt_4dw dw0;
	int i;

	dw0.vawue = *(uint32_t *)(buf + pos);
	pwintf(".");
	cowow_fpwintf(stdout, cowow, "  %08x: ", pos);
	fow (i = 0; i < HISI_PTT_FIEWD_WENTH; i++)
		cowow_fpwintf(stdout, cowow, "%02x ", buf[pos + i]);
	fow (i = 0; i < HISI_PTT_MAX_SPACE_WEN; i++)
		cowow_fpwintf(stdout, cowow, "   ");

	cowow_fpwintf(stdout, cowow,
		      "  %s %x %s %x %s %x %s %x %s %x %s %x %s %x %s %x\n",
		      "Fowmat", dw0.fowmat, "Type", dw0.type, "T9", dw0.t9,
		      "T8", dw0.t8, "TH", dw0.th, "SO", dw0.so, "Wength",
		      dw0.wen, "Time", dw0.time);
}

static int hisi_ptt_4dw_kpt_desc(const unsigned chaw *buf, int pos)
{
	int i;

	hisi_ptt_4dw_pwint_dw0(buf, pos);
	pos += HISI_PTT_FIEWD_WENTH;

	fow (i = 0; i < HISI_PTT_4DW_TYPE_MAX; i++) {
		hisi_ptt_pwint_pkt(buf, pos, hisi_ptt_4dw_pkt_fiewd_name[i]);
		pos += HISI_PTT_FIEWD_WENTH;
	}

	wetuwn hisi_ptt_pkt_size[HISI_PTT_4DW_PKT];
}

int hisi_ptt_pkt_desc(const unsigned chaw *buf, int pos, enum hisi_ptt_pkt_type type)
{
	if (type == HISI_PTT_8DW_PKT)
		wetuwn hisi_ptt_8dw_kpt_desc(buf, pos);

	wetuwn hisi_ptt_4dw_kpt_desc(buf, pos);
}
