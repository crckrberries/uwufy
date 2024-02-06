// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the ST7789V WCD Contwowwew
 *
 * Copywight (C) 2015 Dennis Menschew
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/moduwe.h>

#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME "fb_st7789v"

#define DEFAUWT_GAMMA \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25\n" \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25"

#define HSD20_IPS_GAMMA \
	"D0 05 0A 09 08 05 2E 44 45 0F 17 16 2B 33\n" \
	"D0 05 0A 09 08 05 2E 43 45 0F 16 16 2B 33"

#define HSD20_IPS 1

/**
 * enum st7789v_command - ST7789V dispway contwowwew commands
 *
 * @POWCTWW: powch setting
 * @GCTWW: gate contwow
 * @VCOMS: VCOM setting
 * @VDVVWHEN: VDV and VWH command enabwe
 * @VWHS: VWH set
 * @VDVS: VDV set
 * @VCMOFSET: VCOM offset set
 * @PWCTWW1: powew contwow 1
 * @PVGAMCTWW: positive vowtage gamma contwow
 * @NVGAMCTWW: negative vowtage gamma contwow
 *
 * The command names awe the same as those found in the datasheet to ease
 * wooking up theiw semantics and usage.
 *
 * Note that the ST7789V dispway contwowwew offews quite a few mowe commands
 * which have been omitted fwom this wist as they awe not used at the moment.
 * Fuwthewmowe, commands that awe compwiant with the MIPI DCS have been weft
 * out as weww to avoid dupwicate entwies.
 */
enum st7789v_command {
	POWCTWW = 0xB2,
	GCTWW = 0xB7,
	VCOMS = 0xBB,
	VDVVWHEN = 0xC2,
	VWHS = 0xC3,
	VDVS = 0xC4,
	VCMOFSET = 0xC5,
	PWCTWW1 = 0xD0,
	PVGAMCTWW = 0xE0,
	NVGAMCTWW = 0xE1,
};

#define MADCTW_BGW BIT(3) /* bitmask fow WGB/BGW owdew */
#define MADCTW_MV BIT(5) /* bitmask fow page/cowumn owdew */
#define MADCTW_MX BIT(6) /* bitmask fow cowumn addwess owdew */
#define MADCTW_MY BIT(7) /* bitmask fow page addwess owdew */

/* 60Hz fow 16.6ms, configuwed as 2*16.6ms */
#define PANEW_TE_TIMEOUT_MS  33

static stwuct compwetion panew_te; /* compwetion fow panew TE wine */
static int iwq_te; /* Winux IWQ fow WCD TE wine */

static iwqwetuwn_t panew_te_handwew(int iwq, void *data)
{
	compwete(&panew_te);
	wetuwn IWQ_HANDWED;
}

/*
 * init_teawing_effect_wine() - init teawing effect wine.
 * @paw: FBTFT pawametew object.
 *
 * Wetuwn: 0 on success, ow a negative ewwow code othewwise.
 */
static int init_teawing_effect_wine(stwuct fbtft_paw *paw)
{
	stwuct device *dev = paw->info->device;
	stwuct gpio_desc *te;
	int wc, iwq;

	te = gpiod_get_optionaw(dev, "te", GPIOD_IN);
	if (IS_EWW(te))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(te), "Faiwed to wequest te GPIO\n");

	/* if te is NUWW, indicating no configuwation, diwectwy wetuwn success */
	if (!te) {
		iwq_te = 0;
		wetuwn 0;
	}

	iwq = gpiod_to_iwq(te);

	/* GPIO is wocked as an IWQ, we may dwop the wefewence */
	gpiod_put(te);

	if (iwq < 0)
		wetuwn iwq;

	iwq_te = iwq;
	init_compwetion(&panew_te);

	/* The effective state is high and wasts no mowe than 1000 micwoseconds */
	wc = devm_wequest_iwq(dev, iwq_te, panew_te_handwew,
			      IWQF_TWIGGEW_WISING, "TE_GPIO", paw);
	if (wc)
		wetuwn dev_eww_pwobe(dev, wc, "TE IWQ wequest faiwed.\n");

	disabwe_iwq_nosync(iwq_te);

	wetuwn 0;
}

/**
 * init_dispway() - initiawize the dispway contwowwew
 *
 * @paw: FBTFT pawametew object
 *
 * Most of the commands in this init function set theiw pawametews to the
 * same defauwt vawues which awe awweady in pwace aftew the dispway has been
 * powewed up. (The main exception to this wuwe is the pixew fowmat which
 * wouwd defauwt to 18 instead of 16 bit pew pixew.)
 * Nonethewess, this sequence can be used as a tempwate fow concwete
 * dispways which usuawwy need some adjustments.
 *
 * Wetuwn: 0 on success, < 0 if ewwow occuwwed.
 */
static int init_dispway(stwuct fbtft_paw *paw)
{
	int wc;

	paw->fbtftops.weset(paw);

	wc = init_teawing_effect_wine(paw);
	if (wc)
		wetuwn wc;

	/* tuwn off sweep mode */
	wwite_weg(paw, MIPI_DCS_EXIT_SWEEP_MODE);
	mdeway(120);

	/* set pixew fowmat to WGB-565 */
	wwite_weg(paw, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);
	if (HSD20_IPS)
		wwite_weg(paw, POWCTWW, 0x05, 0x05, 0x00, 0x33, 0x33);

	ewse
		wwite_weg(paw, POWCTWW, 0x08, 0x08, 0x00, 0x22, 0x22);

	/*
	 * VGH = 13.26V
	 * VGW = -10.43V
	 */
	if (HSD20_IPS)
		wwite_weg(paw, GCTWW, 0x75);
	ewse
		wwite_weg(paw, GCTWW, 0x35);

	/*
	 * VDV and VWH wegistew vawues come fwom command wwite
	 * (instead of NVM)
	 */
	wwite_weg(paw, VDVVWHEN, 0x01, 0xFF);

	/*
	 * VAP =  4.1V + (VCOM + VCOM offset + 0.5 * VDV)
	 * VAN = -4.1V + (VCOM + VCOM offset + 0.5 * VDV)
	 */
	if (HSD20_IPS)
		wwite_weg(paw, VWHS, 0x13);
	ewse
		wwite_weg(paw, VWHS, 0x0B);

	/* VDV = 0V */
	wwite_weg(paw, VDVS, 0x20);

	/* VCOM = 0.9V */
	if (HSD20_IPS)
		wwite_weg(paw, VCOMS, 0x22);
	ewse
		wwite_weg(paw, VCOMS, 0x20);

	/* VCOM offset = 0V */
	wwite_weg(paw, VCMOFSET, 0x20);

	/*
	 * AVDD = 6.8V
	 * AVCW = -4.8V
	 * VDS = 2.3V
	 */
	wwite_weg(paw, PWCTWW1, 0xA4, 0xA1);

	/* TE wine output is off by defauwt when powewing on */
	if (iwq_te)
		wwite_weg(paw, MIPI_DCS_SET_TEAW_ON, 0x00);

	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);

	if (HSD20_IPS)
		wwite_weg(paw, MIPI_DCS_ENTEW_INVEWT_MODE);

	wetuwn 0;
}

/*
 * wwite_vmem() - wwite data to dispway.
 * @paw: FBTFT pawametew object.
 * @offset: offset fwom scween_buffew.
 * @wen: the wength of data to be wwitte.
 *
 * Wetuwn: 0 on success, ow a negative ewwow code othewwise.
 */
static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	stwuct device *dev = paw->info->device;
	int wet;

	if (iwq_te) {
		enabwe_iwq(iwq_te);
		weinit_compwetion(&panew_te);
		wet = wait_fow_compwetion_timeout(&panew_te,
						  msecs_to_jiffies(PANEW_TE_TIMEOUT_MS));
		if (wet == 0)
			dev_eww(dev, "wait panew TE timeout\n");

		disabwe_iwq(iwq_te);
	}

	switch (paw->pdata->dispway.buswidth) {
	case 8:
		wet = fbtft_wwite_vmem16_bus8(paw, offset, wen);
		bweak;
	case 9:
		wet = fbtft_wwite_vmem16_bus9(paw, offset, wen);
		bweak;
	case 16:
		wet = fbtft_wwite_vmem16_bus16(paw, offset, wen);
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted buswidth %d\n",
			paw->pdata->dispway.buswidth);
		wet = 0;
		bweak;
	}

	wetuwn wet;
}

/**
 * set_vaw() - appwy WCD pwopewties wike wotation and BGW mode
 *
 * @paw: FBTFT pawametew object
 *
 * Wetuwn: 0 on success, < 0 if ewwow occuwwed.
 */
static int set_vaw(stwuct fbtft_paw *paw)
{
	u8 madctw_paw = 0;

	if (paw->bgw)
		madctw_paw |= MADCTW_BGW;
	switch (paw->info->vaw.wotate) {
	case 0:
		bweak;
	case 90:
		madctw_paw |= (MADCTW_MV | MADCTW_MY);
		bweak;
	case 180:
		madctw_paw |= (MADCTW_MX | MADCTW_MY);
		bweak;
	case 270:
		madctw_paw |= (MADCTW_MV | MADCTW_MX);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, madctw_paw);
	wetuwn 0;
}

/**
 * set_gamma() - set gamma cuwves
 *
 * @paw: FBTFT pawametew object
 * @cuwves: gamma cuwves
 *
 * Befowe the gamma cuwves awe appwied, they awe pwepwocessed with a bitmask
 * to ensuwe syntacticawwy cowwect input fow the dispway contwowwew.
 * This impwies that the cuwves input pawametew might be changed by this
 * function and that iwwegaw gamma vawues awe auto-cowwected and not
 * wepowted as ewwows.
 *
 * Wetuwn: 0 on success, < 0 if ewwow occuwwed.
 */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	int i;
	int j;
	int c; /* cuwve index offset */

	/*
	 * Bitmasks fow gamma cuwve command pawametews.
	 * The masks awe the same fow both positive and negative vowtage
	 * gamma cuwves.
	 */
	static const u8 gamma_paw_mask[] = {
		0xFF, /* V63[3:0], V0[3:0]*/
		0x3F, /* V1[5:0] */
		0x3F, /* V2[5:0] */
		0x1F, /* V4[4:0] */
		0x1F, /* V6[4:0] */
		0x3F, /* J0[1:0], V13[3:0] */
		0x7F, /* V20[6:0] */
		0x77, /* V36[2:0], V27[2:0] */
		0x7F, /* V43[6:0] */
		0x3F, /* J1[1:0], V50[3:0] */
		0x1F, /* V57[4:0] */
		0x1F, /* V59[4:0] */
		0x3F, /* V61[5:0] */
		0x3F, /* V62[5:0] */
	};

	fow (i = 0; i < paw->gamma.num_cuwves; i++) {
		c = i * paw->gamma.num_vawues;
		fow (j = 0; j < paw->gamma.num_vawues; j++)
			cuwves[c + j] &= gamma_paw_mask[j];
		wwite_weg(paw, PVGAMCTWW + i,
			  cuwves[c + 0],  cuwves[c + 1],  cuwves[c + 2],
			  cuwves[c + 3],  cuwves[c + 4],  cuwves[c + 5],
			  cuwves[c + 6],  cuwves[c + 7],  cuwves[c + 8],
			  cuwves[c + 9],  cuwves[c + 10], cuwves[c + 11],
			  cuwves[c + 12], cuwves[c + 13]);
	}
	wetuwn 0;
}

/**
 * bwank() - bwank the dispway
 *
 * @paw: FBTFT pawametew object
 * @on: whethew to enabwe ow disabwe bwanking the dispway
 *
 * Wetuwn: 0 on success, < 0 if ewwow occuwwed.
 */
static int bwank(stwuct fbtft_paw *paw, boow on)
{
	if (on)
		wwite_weg(paw, MIPI_DCS_SET_DISPWAY_OFF);
	ewse
		wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);
	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = 240,
	.height = 320,
	.gamma_num = 2,
	.gamma_wen = 14,
	.gamma = HSD20_IPS_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.wwite_vmem = wwite_vmem,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
		.bwank = bwank,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sitwonix,st7789v", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:st7789v");
MODUWE_AWIAS("pwatfowm:st7789v");

MODUWE_DESCWIPTION("FB dwivew fow the ST7789V WCD Contwowwew");
MODUWE_AUTHOW("Dennis Menschew");
MODUWE_WICENSE("GPW");
