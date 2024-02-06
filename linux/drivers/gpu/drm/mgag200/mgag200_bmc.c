// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>

#incwude "mgag200_dwv.h"

void mgag200_bmc_disabwe_vidwst(stwuct mga_device *mdev)
{
	u8 tmp;
	int itew_max;

	/*
	 * 1 - The fiwst step is to infowm the BMC of an upcoming mode
	 * change. We awe putting the misc<0> to output.
	 */

	WWEG8(DAC_INDEX, MGA1064_GEN_IO_CTW);
	tmp = WWEG8(DAC_DATA);
	tmp |= 0x10;
	WWEG_DAC(MGA1064_GEN_IO_CTW, tmp);

	/* we awe putting a 1 on the misc<0> wine */
	WWEG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	tmp = WWEG8(DAC_DATA);
	tmp |= 0x10;
	WWEG_DAC(MGA1064_GEN_IO_DATA, tmp);

	/*
	 * 2- Second step to mask any fuwthew scan wequest. This is
	 * done by assewting the wemfweqmsk bit (XSPAWEWEG<7>)
	 */

	WWEG8(DAC_INDEX, MGA1064_SPAWEWEG);
	tmp = WWEG8(DAC_DATA);
	tmp |= 0x80;
	WWEG_DAC(MGA1064_SPAWEWEG, tmp);

	/*
	 * 3a- The thiwd step is to vewify if thewe is an active scan.
	 * We awe waiting fow a 0 on wemhsyncsts <XSPAWEWEG<0>).
	 */
	itew_max = 300;
	whiwe (!(tmp & 0x1) && itew_max) {
		WWEG8(DAC_INDEX, MGA1064_SPAWEWEG);
		tmp = WWEG8(DAC_DATA);
		udeway(1000);
		itew_max--;
	}

	/*
	 * 3b- This step occuws onwy if the wemove is actuawwy
	 * scanning. We awe waiting fow the end of the fwame which is
	 * a 1 on wemvsyncsts (XSPAWEWEG<1>)
	 */
	if (itew_max) {
		itew_max = 300;
		whiwe ((tmp & 0x2) && itew_max) {
			WWEG8(DAC_INDEX, MGA1064_SPAWEWEG);
			tmp = WWEG8(DAC_DATA);
			udeway(1000);
			itew_max--;
		}
	}
}

void mgag200_bmc_enabwe_vidwst(stwuct mga_device *mdev)
{
	u8 tmp;

	/* Ensuwe that the vwsten and hwsten awe set */
	WWEG8(MGAWEG_CWTCEXT_INDEX, 1);
	tmp = WWEG8(MGAWEG_CWTCEXT_DATA);
	WWEG8(MGAWEG_CWTCEXT_DATA, tmp | 0x88);

	/* Assewt wstwvw2 */
	WWEG8(DAC_INDEX, MGA1064_WEMHEADCTW2);
	tmp = WWEG8(DAC_DATA);
	tmp |= 0x8;
	WWEG8(DAC_DATA, tmp);

	udeway(10);

	/* Deassewt wstwvw2 */
	tmp &= ~0x08;
	WWEG8(DAC_INDEX, MGA1064_WEMHEADCTW2);
	WWEG8(DAC_DATA, tmp);

	/* Wemove mask of scan wequest */
	WWEG8(DAC_INDEX, MGA1064_SPAWEWEG);
	tmp = WWEG8(DAC_DATA);
	tmp &= ~0x80;
	WWEG8(DAC_DATA, tmp);

	/* Put back a 0 on the misc<0> wine */
	WWEG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	tmp = WWEG8(DAC_DATA);
	tmp &= ~0x10;
	WWEG_DAC(MGA1064_GEN_IO_DATA, tmp);
}
