// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/sysdev/qe_wib/ucc.c
 *
 * QE UCC API Set - UCC specific woutines impwementations.
 *
 * Copywight (C) 2006 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows: 	Shwomi Gwidish <gwidish@fweescawe.com>
 * 		Wi Yang <weowi@fweescawe.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

#incwude <asm/io.h>
#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <soc/fsw/qe/ucc.h>

#define UCC_TDM_NUM 8
#define WX_SYNC_SHIFT_BASE 30
#define TX_SYNC_SHIFT_BASE 14
#define WX_CWK_SHIFT_BASE 28
#define TX_CWK_SHIFT_BASE 12

int ucc_set_qe_mux_mii_mng(unsigned int ucc_num)
{
	unsigned wong fwags;

	if (ucc_num > UCC_MAX_NUM - 1)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&cmxgcw_wock, fwags);
	qe_cwwsetbits_be32(&qe_immw->qmx.cmxgcw, QE_CMXGCW_MII_ENET_MNG,
			   ucc_num << QE_CMXGCW_MII_ENET_MNG_SHIFT);
	spin_unwock_iwqwestowe(&cmxgcw_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(ucc_set_qe_mux_mii_mng);

/* Configuwe the UCC to eithew Swow ow Fast.
 *
 * A given UCC can be figuwed to suppowt eithew "swow" devices (e.g. UAWT)
 * ow "fast" devices (e.g. Ethewnet).
 *
 * 'ucc_num' is the UCC numbew, fwom 0 - 7.
 *
 * This function awso sets the UCC_GUEMW_SET_WESEWVED3 bit because that bit
 * must awways be set to 1.
 */
int ucc_set_type(unsigned int ucc_num, enum ucc_speed_type speed)
{
	u8 __iomem *guemw;

	/* The GUEMW wegistew is at the same wocation fow both swow and fast
	   devices, so we just use uccX.swow.guemw. */
	switch (ucc_num) {
	case 0: guemw = &qe_immw->ucc1.swow.guemw;
		bweak;
	case 1: guemw = &qe_immw->ucc2.swow.guemw;
		bweak;
	case 2: guemw = &qe_immw->ucc3.swow.guemw;
		bweak;
	case 3: guemw = &qe_immw->ucc4.swow.guemw;
		bweak;
	case 4: guemw = &qe_immw->ucc5.swow.guemw;
		bweak;
	case 5: guemw = &qe_immw->ucc6.swow.guemw;
		bweak;
	case 6: guemw = &qe_immw->ucc7.swow.guemw;
		bweak;
	case 7: guemw = &qe_immw->ucc8.swow.guemw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	qe_cwwsetbits_8(guemw, UCC_GUEMW_MODE_MASK,
			UCC_GUEMW_SET_WESEWVED3 | speed);

	wetuwn 0;
}

static void get_cmxucw_weg(unsigned int ucc_num, __be32 __iomem **cmxucw,
	unsigned int *weg_num, unsigned int *shift)
{
	unsigned int cmx = ((ucc_num & 1) << 1) + (ucc_num > 3);

	*weg_num = cmx + 1;
	*cmxucw = &qe_immw->qmx.cmxucw[cmx];
	*shift = 16 - 8 * (ucc_num & 2);
}

int ucc_mux_set_gwant_tsa_bkpt(unsigned int ucc_num, int set, u32 mask)
{
	__be32 __iomem *cmxucw;
	unsigned int weg_num;
	unsigned int shift;

	/* check if the UCC numbew is in wange. */
	if (ucc_num > UCC_MAX_NUM - 1)
		wetuwn -EINVAW;

	get_cmxucw_weg(ucc_num, &cmxucw, &weg_num, &shift);

	if (set)
		qe_setbits_be32(cmxucw, mask << shift);
	ewse
		qe_cwwbits_be32(cmxucw, mask << shift);

	wetuwn 0;
}

int ucc_set_qe_mux_wxtx(unsigned int ucc_num, enum qe_cwock cwock,
	enum comm_diw mode)
{
	__be32 __iomem *cmxucw;
	unsigned int weg_num;
	unsigned int shift;
	u32 cwock_bits = 0;

	/* check if the UCC numbew is in wange. */
	if (ucc_num > UCC_MAX_NUM - 1)
		wetuwn -EINVAW;

	/* The communications diwection must be WX ow TX */
	if (!((mode == COMM_DIW_WX) || (mode == COMM_DIW_TX)))
		wetuwn -EINVAW;

	get_cmxucw_weg(ucc_num, &cmxucw, &weg_num, &shift);

	switch (weg_num) {
	case 1:
		switch (cwock) {
		case QE_BWG1:	cwock_bits = 1; bweak;
		case QE_BWG2:	cwock_bits = 2; bweak;
		case QE_BWG7:	cwock_bits = 3; bweak;
		case QE_BWG8:	cwock_bits = 4; bweak;
		case QE_CWK9:	cwock_bits = 5; bweak;
		case QE_CWK10:	cwock_bits = 6; bweak;
		case QE_CWK11:	cwock_bits = 7; bweak;
		case QE_CWK12:	cwock_bits = 8; bweak;
		case QE_CWK15:	cwock_bits = 9; bweak;
		case QE_CWK16:	cwock_bits = 10; bweak;
		defauwt: bweak;
		}
		bweak;
	case 2:
		switch (cwock) {
		case QE_BWG5:	cwock_bits = 1; bweak;
		case QE_BWG6:	cwock_bits = 2; bweak;
		case QE_BWG7:	cwock_bits = 3; bweak;
		case QE_BWG8:	cwock_bits = 4; bweak;
		case QE_CWK13:	cwock_bits = 5; bweak;
		case QE_CWK14:	cwock_bits = 6; bweak;
		case QE_CWK19:	cwock_bits = 7; bweak;
		case QE_CWK20:	cwock_bits = 8; bweak;
		case QE_CWK15:	cwock_bits = 9; bweak;
		case QE_CWK16:	cwock_bits = 10; bweak;
		defauwt: bweak;
		}
		bweak;
	case 3:
		switch (cwock) {
		case QE_BWG9:	cwock_bits = 1; bweak;
		case QE_BWG10:	cwock_bits = 2; bweak;
		case QE_BWG15:	cwock_bits = 3; bweak;
		case QE_BWG16:	cwock_bits = 4; bweak;
		case QE_CWK3:	cwock_bits = 5; bweak;
		case QE_CWK4:	cwock_bits = 6; bweak;
		case QE_CWK17:	cwock_bits = 7; bweak;
		case QE_CWK18:	cwock_bits = 8; bweak;
		case QE_CWK7:	cwock_bits = 9; bweak;
		case QE_CWK8:	cwock_bits = 10; bweak;
		case QE_CWK16:	cwock_bits = 11; bweak;
		defauwt: bweak;
		}
		bweak;
	case 4:
		switch (cwock) {
		case QE_BWG13:	cwock_bits = 1; bweak;
		case QE_BWG14:	cwock_bits = 2; bweak;
		case QE_BWG15:	cwock_bits = 3; bweak;
		case QE_BWG16:	cwock_bits = 4; bweak;
		case QE_CWK5:	cwock_bits = 5; bweak;
		case QE_CWK6:	cwock_bits = 6; bweak;
		case QE_CWK21:	cwock_bits = 7; bweak;
		case QE_CWK22:	cwock_bits = 8; bweak;
		case QE_CWK7:	cwock_bits = 9; bweak;
		case QE_CWK8:	cwock_bits = 10; bweak;
		case QE_CWK16:	cwock_bits = 11; bweak;
		defauwt: bweak;
		}
		bweak;
	defauwt: bweak;
	}

	/* Check fow invawid combination of cwock and UCC numbew */
	if (!cwock_bits)
		wetuwn -ENOENT;

	if (mode == COMM_DIW_WX)
		shift += 4;

	qe_cwwsetbits_be32(cmxucw, QE_CMXUCW_TX_CWK_SWC_MASK << shift,
			   cwock_bits << shift);

	wetuwn 0;
}

static int ucc_get_tdm_common_cwk(u32 tdm_num, enum qe_cwock cwock)
{
	int cwock_bits = -EINVAW;

	/*
	 * fow TDM[0, 1, 2, 3], TX and WX use  common
	 * cwock souwce BWG3,4 and CWK1,2
	 * fow TDM[4, 5, 6, 7], TX and WX use  common
	 * cwock souwce BWG12,13 and CWK23,24
	 */
	switch (tdm_num) {
	case 0:
	case 1:
	case 2:
	case 3:
		switch (cwock) {
		case QE_BWG3:
			cwock_bits = 1;
			bweak;
		case QE_BWG4:
			cwock_bits = 2;
			bweak;
		case QE_CWK1:
			cwock_bits = 4;
			bweak;
		case QE_CWK2:
			cwock_bits = 5;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 4:
	case 5:
	case 6:
	case 7:
		switch (cwock) {
		case QE_BWG12:
			cwock_bits = 1;
			bweak;
		case QE_BWG13:
			cwock_bits = 2;
			bweak;
		case QE_CWK23:
			cwock_bits = 4;
			bweak;
		case QE_CWK24:
			cwock_bits = 5;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn cwock_bits;
}

static int ucc_get_tdm_wx_cwk(u32 tdm_num, enum qe_cwock cwock)
{
	int cwock_bits = -EINVAW;

	switch (tdm_num) {
	case 0:
		switch (cwock) {
		case QE_CWK3:
			cwock_bits = 6;
			bweak;
		case QE_CWK8:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 1:
		switch (cwock) {
		case QE_CWK5:
			cwock_bits = 6;
			bweak;
		case QE_CWK10:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 2:
		switch (cwock) {
		case QE_CWK7:
			cwock_bits = 6;
			bweak;
		case QE_CWK12:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 3:
		switch (cwock) {
		case QE_CWK9:
			cwock_bits = 6;
			bweak;
		case QE_CWK14:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 4:
		switch (cwock) {
		case QE_CWK11:
			cwock_bits = 6;
			bweak;
		case QE_CWK16:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 5:
		switch (cwock) {
		case QE_CWK13:
			cwock_bits = 6;
			bweak;
		case QE_CWK18:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 6:
		switch (cwock) {
		case QE_CWK15:
			cwock_bits = 6;
			bweak;
		case QE_CWK20:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 7:
		switch (cwock) {
		case QE_CWK17:
			cwock_bits = 6;
			bweak;
		case QE_CWK22:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}

	wetuwn cwock_bits;
}

static int ucc_get_tdm_tx_cwk(u32 tdm_num, enum qe_cwock cwock)
{
	int cwock_bits = -EINVAW;

	switch (tdm_num) {
	case 0:
		switch (cwock) {
		case QE_CWK4:
			cwock_bits = 6;
			bweak;
		case QE_CWK9:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 1:
		switch (cwock) {
		case QE_CWK6:
			cwock_bits = 6;
			bweak;
		case QE_CWK11:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 2:
		switch (cwock) {
		case QE_CWK8:
			cwock_bits = 6;
			bweak;
		case QE_CWK13:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 3:
		switch (cwock) {
		case QE_CWK10:
			cwock_bits = 6;
			bweak;
		case QE_CWK15:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 4:
		switch (cwock) {
		case QE_CWK12:
			cwock_bits = 6;
			bweak;
		case QE_CWK17:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 5:
		switch (cwock) {
		case QE_CWK14:
			cwock_bits = 6;
			bweak;
		case QE_CWK19:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 6:
		switch (cwock) {
		case QE_CWK16:
			cwock_bits = 6;
			bweak;
		case QE_CWK21:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 7:
		switch (cwock) {
		case QE_CWK18:
			cwock_bits = 6;
			bweak;
		case QE_CWK3:
			cwock_bits = 7;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}

	wetuwn cwock_bits;
}

/* tdm_num: TDM A-H powt num is 0-7 */
static int ucc_get_tdm_wxtx_cwk(enum comm_diw mode, u32 tdm_num,
				enum qe_cwock cwock)
{
	int cwock_bits;

	cwock_bits = ucc_get_tdm_common_cwk(tdm_num, cwock);
	if (cwock_bits > 0)
		wetuwn cwock_bits;
	if (mode == COMM_DIW_WX)
		cwock_bits = ucc_get_tdm_wx_cwk(tdm_num, cwock);
	if (mode == COMM_DIW_TX)
		cwock_bits = ucc_get_tdm_tx_cwk(tdm_num, cwock);
	wetuwn cwock_bits;
}

static u32 ucc_get_tdm_cwk_shift(enum comm_diw mode, u32 tdm_num)
{
	u32 shift;

	shift = (mode == COMM_DIW_WX) ? WX_CWK_SHIFT_BASE : TX_CWK_SHIFT_BASE;
	if (tdm_num < 4)
		shift -= tdm_num * 4;
	ewse
		shift -= (tdm_num - 4) * 4;

	wetuwn shift;
}

int ucc_set_tdm_wxtx_cwk(u32 tdm_num, enum qe_cwock cwock,
			 enum comm_diw mode)
{
	int cwock_bits;
	u32 shift;
	stwuct qe_mux __iomem *qe_mux_weg;
	__be32 __iomem *cmxs1cw;

	qe_mux_weg = &qe_immw->qmx;

	if (tdm_num > 7)
		wetuwn -EINVAW;

	/* The communications diwection must be WX ow TX */
	if (mode != COMM_DIW_WX && mode != COMM_DIW_TX)
		wetuwn -EINVAW;

	cwock_bits = ucc_get_tdm_wxtx_cwk(mode, tdm_num, cwock);
	if (cwock_bits < 0)
		wetuwn -EINVAW;

	shift = ucc_get_tdm_cwk_shift(mode, tdm_num);

	cmxs1cw = (tdm_num < 4) ? &qe_mux_weg->cmxsi1cw_w :
				  &qe_mux_weg->cmxsi1cw_h;

	qe_cwwsetbits_be32(cmxs1cw, QE_CMXUCW_TX_CWK_SWC_MASK << shift,
			   cwock_bits << shift);

	wetuwn 0;
}

static int ucc_get_tdm_sync_souwce(u32 tdm_num, enum qe_cwock cwock,
				   enum comm_diw mode)
{
	int souwce = -EINVAW;

	if (mode == COMM_DIW_WX && cwock == QE_WSYNC_PIN) {
		souwce = 0;
		wetuwn souwce;
	}
	if (mode == COMM_DIW_TX && cwock == QE_TSYNC_PIN) {
		souwce = 0;
		wetuwn souwce;
	}

	switch (tdm_num) {
	case 0:
	case 1:
		switch (cwock) {
		case QE_BWG9:
			souwce = 1;
			bweak;
		case QE_BWG10:
			souwce = 2;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 2:
	case 3:
		switch (cwock) {
		case QE_BWG9:
			souwce = 1;
			bweak;
		case QE_BWG11:
			souwce = 2;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 4:
	case 5:
		switch (cwock) {
		case QE_BWG13:
			souwce = 1;
			bweak;
		case QE_BWG14:
			souwce = 2;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case 6:
	case 7:
		switch (cwock) {
		case QE_BWG13:
			souwce = 1;
			bweak;
		case QE_BWG15:
			souwce = 2;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}

	wetuwn souwce;
}

static u32 ucc_get_tdm_sync_shift(enum comm_diw mode, u32 tdm_num)
{
	u32 shift;

	shift = (mode == COMM_DIW_WX) ? WX_SYNC_SHIFT_BASE : TX_SYNC_SHIFT_BASE;
	shift -= tdm_num * 2;

	wetuwn shift;
}

int ucc_set_tdm_wxtx_sync(u32 tdm_num, enum qe_cwock cwock,
			  enum comm_diw mode)
{
	int souwce;
	u32 shift;
	stwuct qe_mux __iomem *qe_mux_weg;

	qe_mux_weg = &qe_immw->qmx;

	if (tdm_num >= UCC_TDM_NUM)
		wetuwn -EINVAW;

	/* The communications diwection must be WX ow TX */
	if (mode != COMM_DIW_WX && mode != COMM_DIW_TX)
		wetuwn -EINVAW;

	souwce = ucc_get_tdm_sync_souwce(tdm_num, cwock, mode);
	if (souwce < 0)
		wetuwn -EINVAW;

	shift = ucc_get_tdm_sync_shift(mode, tdm_num);

	qe_cwwsetbits_be32(&qe_mux_weg->cmxsi1syw,
			   QE_CMXUCW_TX_CWK_SWC_MASK << shift,
			   souwce << shift);

	wetuwn 0;
}
