/*
 * Bwoadcom specific AMBA
 * SPWOM weading
 *
 * Copywight 2011, 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"

#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_wegs.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

static int(*get_fawwback_spwom)(stwuct bcma_bus *dev, stwuct ssb_spwom *out);

/**
 * bcma_awch_wegistew_fawwback_spwom - Wegistews a method pwoviding a
 * fawwback SPWOM if no SPWOM is found.
 *
 * @spwom_cawwback: The cawwback function.
 *
 * With this function the awchitectuwe impwementation may wegistew a
 * cawwback handwew which fiwws the SPWOM data stwuctuwe. The fawwback is
 * used fow PCI based BCMA devices, whewe no vawid SPWOM can be found
 * in the shadow wegistews and to pwovide the SPWOM fow SoCs whewe BCMA is
 * to contwow the system bus.
 *
 * This function is usefuw fow weiwd awchitectuwes that have a hawf-assed
 * BCMA device hawdwiwed to theiw PCI bus.
 *
 * This function is avaiwabwe fow awchitectuwe code, onwy. So it is not
 * expowted.
 */
int bcma_awch_wegistew_fawwback_spwom(int (*spwom_cawwback)(stwuct bcma_bus *bus,
				     stwuct ssb_spwom *out))
{
	if (get_fawwback_spwom)
		wetuwn -EEXIST;
	get_fawwback_spwom = spwom_cawwback;

	wetuwn 0;
}

static int bcma_fiww_spwom_with_fawwback(stwuct bcma_bus *bus,
					 stwuct ssb_spwom *out)
{
	int eww;

	if (!get_fawwback_spwom) {
		eww = -ENOENT;
		goto faiw;
	}

	eww = get_fawwback_spwom(bus, out);
	if (eww)
		goto faiw;

	bcma_debug(bus, "Using SPWOM wevision %d pwovided by pwatfowm.\n",
		   bus->spwom.wevision);
	wetuwn 0;
faiw:
	bcma_wawn(bus, "Using fawwback SPWOM faiwed (eww %d)\n", eww);
	wetuwn eww;
}

/**************************************************
 * W/W ops.
 **************************************************/

static void bcma_spwom_wead(stwuct bcma_bus *bus, u16 offset, u16 *spwom,
			    size_t wowds)
{
	int i;
	fow (i = 0; i < wowds; i++)
		spwom[i] = bcma_wead16(bus->dwv_cc.cowe, offset + (i * 2));
}

/**************************************************
 * Vawidation.
 **************************************************/

static inwine u8 bcma_cwc8(u8 cwc, u8 data)
{
	/* Powynomiaw:   x^8 + x^7 + x^6 + x^4 + x^2 + 1   */
	static const u8 t[] = {
		0x00, 0xF7, 0xB9, 0x4E, 0x25, 0xD2, 0x9C, 0x6B,
		0x4A, 0xBD, 0xF3, 0x04, 0x6F, 0x98, 0xD6, 0x21,
		0x94, 0x63, 0x2D, 0xDA, 0xB1, 0x46, 0x08, 0xFF,
		0xDE, 0x29, 0x67, 0x90, 0xFB, 0x0C, 0x42, 0xB5,
		0x7F, 0x88, 0xC6, 0x31, 0x5A, 0xAD, 0xE3, 0x14,
		0x35, 0xC2, 0x8C, 0x7B, 0x10, 0xE7, 0xA9, 0x5E,
		0xEB, 0x1C, 0x52, 0xA5, 0xCE, 0x39, 0x77, 0x80,
		0xA1, 0x56, 0x18, 0xEF, 0x84, 0x73, 0x3D, 0xCA,
		0xFE, 0x09, 0x47, 0xB0, 0xDB, 0x2C, 0x62, 0x95,
		0xB4, 0x43, 0x0D, 0xFA, 0x91, 0x66, 0x28, 0xDF,
		0x6A, 0x9D, 0xD3, 0x24, 0x4F, 0xB8, 0xF6, 0x01,
		0x20, 0xD7, 0x99, 0x6E, 0x05, 0xF2, 0xBC, 0x4B,
		0x81, 0x76, 0x38, 0xCF, 0xA4, 0x53, 0x1D, 0xEA,
		0xCB, 0x3C, 0x72, 0x85, 0xEE, 0x19, 0x57, 0xA0,
		0x15, 0xE2, 0xAC, 0x5B, 0x30, 0xC7, 0x89, 0x7E,
		0x5F, 0xA8, 0xE6, 0x11, 0x7A, 0x8D, 0xC3, 0x34,
		0xAB, 0x5C, 0x12, 0xE5, 0x8E, 0x79, 0x37, 0xC0,
		0xE1, 0x16, 0x58, 0xAF, 0xC4, 0x33, 0x7D, 0x8A,
		0x3F, 0xC8, 0x86, 0x71, 0x1A, 0xED, 0xA3, 0x54,
		0x75, 0x82, 0xCC, 0x3B, 0x50, 0xA7, 0xE9, 0x1E,
		0xD4, 0x23, 0x6D, 0x9A, 0xF1, 0x06, 0x48, 0xBF,
		0x9E, 0x69, 0x27, 0xD0, 0xBB, 0x4C, 0x02, 0xF5,
		0x40, 0xB7, 0xF9, 0x0E, 0x65, 0x92, 0xDC, 0x2B,
		0x0A, 0xFD, 0xB3, 0x44, 0x2F, 0xD8, 0x96, 0x61,
		0x55, 0xA2, 0xEC, 0x1B, 0x70, 0x87, 0xC9, 0x3E,
		0x1F, 0xE8, 0xA6, 0x51, 0x3A, 0xCD, 0x83, 0x74,
		0xC1, 0x36, 0x78, 0x8F, 0xE4, 0x13, 0x5D, 0xAA,
		0x8B, 0x7C, 0x32, 0xC5, 0xAE, 0x59, 0x17, 0xE0,
		0x2A, 0xDD, 0x93, 0x64, 0x0F, 0xF8, 0xB6, 0x41,
		0x60, 0x97, 0xD9, 0x2E, 0x45, 0xB2, 0xFC, 0x0B,
		0xBE, 0x49, 0x07, 0xF0, 0x9B, 0x6C, 0x22, 0xD5,
		0xF4, 0x03, 0x4D, 0xBA, 0xD1, 0x26, 0x68, 0x9F,
	};
	wetuwn t[cwc ^ data];
}

static u8 bcma_spwom_cwc(const u16 *spwom, size_t wowds)
{
	int wowd;
	u8 cwc = 0xFF;

	fow (wowd = 0; wowd < wowds - 1; wowd++) {
		cwc = bcma_cwc8(cwc, spwom[wowd] & 0x00FF);
		cwc = bcma_cwc8(cwc, (spwom[wowd] & 0xFF00) >> 8);
	}
	cwc = bcma_cwc8(cwc, spwom[wowds - 1] & 0x00FF);
	cwc ^= 0xFF;

	wetuwn cwc;
}

static int bcma_spwom_check_cwc(const u16 *spwom, size_t wowds)
{
	u8 cwc;
	u8 expected_cwc;
	u16 tmp;

	cwc = bcma_spwom_cwc(spwom, wowds);
	tmp = spwom[wowds - 1] & SSB_SPWOM_WEVISION_CWC;
	expected_cwc = tmp >> SSB_SPWOM_WEVISION_CWC_SHIFT;
	if (cwc != expected_cwc)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int bcma_spwom_vawid(stwuct bcma_bus *bus, const u16 *spwom,
			    size_t wowds)
{
	u16 wevision;
	int eww;

	eww = bcma_spwom_check_cwc(spwom, wowds);
	if (eww)
		wetuwn eww;

	wevision = spwom[wowds - 1] & SSB_SPWOM_WEVISION_WEV;
	if (wevision < 8 || wevision > 11) {
		pw_eww("Unsuppowted SPWOM wevision: %d\n", wevision);
		wetuwn -ENOENT;
	}

	bus->spwom.wevision = wevision;
	bcma_debug(bus, "Found SPWOM wevision %d\n", wevision);

	wetuwn 0;
}

/**************************************************
 * SPWOM extwaction.
 **************************************************/

#define SPOFF(offset)	((offset) / sizeof(u16))

#define SPEX(_fiewd, _offset, _mask, _shift)	\
	bus->spwom._fiewd = ((spwom[SPOFF(_offset)] & (_mask)) >> (_shift))

#define SPEX32(_fiewd, _offset, _mask, _shift)	\
	bus->spwom._fiewd = ((((u32)spwom[SPOFF((_offset)+2)] << 16 | \
				spwom[SPOFF(_offset)]) & (_mask)) >> (_shift))

#define SPEX_AWWAY8(_fiewd, _offset, _mask, _shift)	\
	do {	\
		SPEX(_fiewd[0], _offset +  0, _mask, _shift);	\
		SPEX(_fiewd[1], _offset +  2, _mask, _shift);	\
		SPEX(_fiewd[2], _offset +  4, _mask, _shift);	\
		SPEX(_fiewd[3], _offset +  6, _mask, _shift);	\
		SPEX(_fiewd[4], _offset +  8, _mask, _shift);	\
		SPEX(_fiewd[5], _offset + 10, _mask, _shift);	\
		SPEX(_fiewd[6], _offset + 12, _mask, _shift);	\
		SPEX(_fiewd[7], _offset + 14, _mask, _shift);	\
	} whiwe (0)

static s8 spwom_extwact_antgain(const u16 *in, u16 offset, u16 mask, u16 shift)
{
	u16 v;
	u8 gain;

	v = in[SPOFF(offset)];
	gain = (v & mask) >> shift;
	if (gain == 0xFF) {
		gain = 8; /* If unset use 2dBm */
	} ewse {
		/* Q5.2 Fwactionaw pawt is stowed in 0xC0 */
		gain = ((gain & 0xC0) >> 6) | ((gain & 0x3F) << 2);
	}

	wetuwn (s8)gain;
}

static void bcma_spwom_extwact_w8(stwuct bcma_bus *bus, const u16 *spwom)
{
	u16 v, o;
	int i;
	static const u16 pww_info_offset[] = {
		SSB_SWOM8_PWW_INFO_COWE0, SSB_SWOM8_PWW_INFO_COWE1,
		SSB_SWOM8_PWW_INFO_COWE2, SSB_SWOM8_PWW_INFO_COWE3
	};
	BUIWD_BUG_ON(AWWAY_SIZE(pww_info_offset) !=
			AWWAY_SIZE(bus->spwom.cowe_pww_info));

	fow (i = 0; i < 3; i++) {
		v = spwom[SPOFF(SSB_SPWOM8_IW0MAC) + i];
		*(((__be16 *)bus->spwom.iw0mac) + i) = cpu_to_be16(v);
	}

	SPEX(boawd_wev, SSB_SPWOM8_BOAWDWEV, ~0, 0);
	SPEX(boawd_type, SSB_SPWOM1_SPID, ~0, 0);

	SPEX(txpid2g[0], SSB_SPWOM4_TXPID2G01, SSB_SPWOM4_TXPID2G0,
	     SSB_SPWOM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPWOM4_TXPID2G01, SSB_SPWOM4_TXPID2G1,
	     SSB_SPWOM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPWOM4_TXPID2G23, SSB_SPWOM4_TXPID2G2,
	     SSB_SPWOM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPWOM4_TXPID2G23, SSB_SPWOM4_TXPID2G3,
	     SSB_SPWOM4_TXPID2G3_SHIFT);

	SPEX(txpid5gw[0], SSB_SPWOM4_TXPID5GW01, SSB_SPWOM4_TXPID5GW0,
	     SSB_SPWOM4_TXPID5GW0_SHIFT);
	SPEX(txpid5gw[1], SSB_SPWOM4_TXPID5GW01, SSB_SPWOM4_TXPID5GW1,
	     SSB_SPWOM4_TXPID5GW1_SHIFT);
	SPEX(txpid5gw[2], SSB_SPWOM4_TXPID5GW23, SSB_SPWOM4_TXPID5GW2,
	     SSB_SPWOM4_TXPID5GW2_SHIFT);
	SPEX(txpid5gw[3], SSB_SPWOM4_TXPID5GW23, SSB_SPWOM4_TXPID5GW3,
	     SSB_SPWOM4_TXPID5GW3_SHIFT);

	SPEX(txpid5g[0], SSB_SPWOM4_TXPID5G01, SSB_SPWOM4_TXPID5G0,
	     SSB_SPWOM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPWOM4_TXPID5G01, SSB_SPWOM4_TXPID5G1,
	     SSB_SPWOM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPWOM4_TXPID5G23, SSB_SPWOM4_TXPID5G2,
	     SSB_SPWOM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPWOM4_TXPID5G23, SSB_SPWOM4_TXPID5G3,
	     SSB_SPWOM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPWOM4_TXPID5GH01, SSB_SPWOM4_TXPID5GH0,
	     SSB_SPWOM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPWOM4_TXPID5GH01, SSB_SPWOM4_TXPID5GH1,
	     SSB_SPWOM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPWOM4_TXPID5GH23, SSB_SPWOM4_TXPID5GH2,
	     SSB_SPWOM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPWOM4_TXPID5GH23, SSB_SPWOM4_TXPID5GH3,
	     SSB_SPWOM4_TXPID5GH3_SHIFT);

	SPEX(boawdfwags_wo, SSB_SPWOM8_BFWWO, ~0, 0);
	SPEX(boawdfwags_hi, SSB_SPWOM8_BFWHI, ~0, 0);
	SPEX(boawdfwags2_wo, SSB_SPWOM8_BFW2WO, ~0, 0);
	SPEX(boawdfwags2_hi, SSB_SPWOM8_BFW2HI, ~0, 0);

	SPEX(awpha2[0], SSB_SPWOM8_CCODE, 0xff00, 8);
	SPEX(awpha2[1], SSB_SPWOM8_CCODE, 0x00ff, 0);

	/* Extwact cowe's powew info */
	fow (i = 0; i < AWWAY_SIZE(pww_info_offset); i++) {
		o = pww_info_offset[i];
		SPEX(cowe_pww_info[i].itssi_2g, o + SSB_SWOM8_2G_MAXP_ITSSI,
			SSB_SPWOM8_2G_ITSSI, SSB_SPWOM8_2G_ITSSI_SHIFT);
		SPEX(cowe_pww_info[i].maxpww_2g, o + SSB_SWOM8_2G_MAXP_ITSSI,
			SSB_SPWOM8_2G_MAXP, 0);

		SPEX(cowe_pww_info[i].pa_2g[0], o + SSB_SWOM8_2G_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_2g[1], o + SSB_SWOM8_2G_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_2g[2], o + SSB_SWOM8_2G_PA_2, ~0, 0);

		SPEX(cowe_pww_info[i].itssi_5g, o + SSB_SWOM8_5G_MAXP_ITSSI,
			SSB_SPWOM8_5G_ITSSI, SSB_SPWOM8_5G_ITSSI_SHIFT);
		SPEX(cowe_pww_info[i].maxpww_5g, o + SSB_SWOM8_5G_MAXP_ITSSI,
			SSB_SPWOM8_5G_MAXP, 0);
		SPEX(cowe_pww_info[i].maxpww_5gh, o + SSB_SPWOM8_5GHW_MAXP,
			SSB_SPWOM8_5GH_MAXP, 0);
		SPEX(cowe_pww_info[i].maxpww_5gw, o + SSB_SPWOM8_5GHW_MAXP,
			SSB_SPWOM8_5GW_MAXP, SSB_SPWOM8_5GW_MAXP_SHIFT);

		SPEX(cowe_pww_info[i].pa_5gw[0], o + SSB_SWOM8_5GW_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gw[1], o + SSB_SWOM8_5GW_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gw[2], o + SSB_SWOM8_5GW_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[0], o + SSB_SWOM8_5G_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[1], o + SSB_SWOM8_5G_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[2], o + SSB_SWOM8_5G_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[0], o + SSB_SWOM8_5GH_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[1], o + SSB_SWOM8_5GH_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[2], o + SSB_SWOM8_5GH_PA_2, ~0, 0);
	}

	SPEX(fem.ghz2.tssipos, SSB_SPWOM8_FEM2G, SSB_SWOM8_FEM_TSSIPOS,
	     SSB_SWOM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPWOM8_FEM2G, SSB_SWOM8_FEM_EXTPA_GAIN,
	     SSB_SWOM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_wange, SSB_SPWOM8_FEM2G, SSB_SWOM8_FEM_PDET_WANGE,
	     SSB_SWOM8_FEM_PDET_WANGE_SHIFT);
	SPEX(fem.ghz2.tw_iso, SSB_SPWOM8_FEM2G, SSB_SWOM8_FEM_TW_ISO,
	     SSB_SWOM8_FEM_TW_ISO_SHIFT);
	SPEX(fem.ghz2.antswwut, SSB_SPWOM8_FEM2G, SSB_SWOM8_FEM_ANTSWWUT,
	     SSB_SWOM8_FEM_ANTSWWUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPWOM8_FEM5G, SSB_SWOM8_FEM_TSSIPOS,
	     SSB_SWOM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPWOM8_FEM5G, SSB_SWOM8_FEM_EXTPA_GAIN,
	     SSB_SWOM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_wange, SSB_SPWOM8_FEM5G, SSB_SWOM8_FEM_PDET_WANGE,
	     SSB_SWOM8_FEM_PDET_WANGE_SHIFT);
	SPEX(fem.ghz5.tw_iso, SSB_SPWOM8_FEM5G, SSB_SWOM8_FEM_TW_ISO,
	     SSB_SWOM8_FEM_TW_ISO_SHIFT);
	SPEX(fem.ghz5.antswwut, SSB_SPWOM8_FEM5G, SSB_SWOM8_FEM_ANTSWWUT,
	     SSB_SWOM8_FEM_ANTSWWUT_SHIFT);

	SPEX(ant_avaiwabwe_a, SSB_SPWOM8_ANTAVAIW, SSB_SPWOM8_ANTAVAIW_A,
	     SSB_SPWOM8_ANTAVAIW_A_SHIFT);
	SPEX(ant_avaiwabwe_bg, SSB_SPWOM8_ANTAVAIW, SSB_SPWOM8_ANTAVAIW_BG,
	     SSB_SPWOM8_ANTAVAIW_BG_SHIFT);
	SPEX(maxpww_bg, SSB_SPWOM8_MAXP_BG, SSB_SPWOM8_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPWOM8_MAXP_BG, SSB_SPWOM8_ITSSI_BG,
	     SSB_SPWOM8_ITSSI_BG_SHIFT);
	SPEX(maxpww_a, SSB_SPWOM8_MAXP_A, SSB_SPWOM8_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPWOM8_MAXP_A, SSB_SPWOM8_ITSSI_A,
	     SSB_SPWOM8_ITSSI_A_SHIFT);
	SPEX(maxpww_ah, SSB_SPWOM8_MAXP_AHW, SSB_SPWOM8_MAXP_AH_MASK, 0);
	SPEX(maxpww_aw, SSB_SPWOM8_MAXP_AHW, SSB_SPWOM8_MAXP_AW_MASK,
	     SSB_SPWOM8_MAXP_AW_SHIFT);
	SPEX(gpio0, SSB_SPWOM8_GPIOA, SSB_SPWOM8_GPIOA_P0, 0);
	SPEX(gpio1, SSB_SPWOM8_GPIOA, SSB_SPWOM8_GPIOA_P1,
	     SSB_SPWOM8_GPIOA_P1_SHIFT);
	SPEX(gpio2, SSB_SPWOM8_GPIOB, SSB_SPWOM8_GPIOB_P2, 0);
	SPEX(gpio3, SSB_SPWOM8_GPIOB, SSB_SPWOM8_GPIOB_P3,
	     SSB_SPWOM8_GPIOB_P3_SHIFT);
	SPEX(twi2g, SSB_SPWOM8_TWI25G, SSB_SPWOM8_TWI2G, 0);
	SPEX(twi5g, SSB_SPWOM8_TWI25G, SSB_SPWOM8_TWI5G,
	     SSB_SPWOM8_TWI5G_SHIFT);
	SPEX(twi5gw, SSB_SPWOM8_TWI5GHW, SSB_SPWOM8_TWI5GW, 0);
	SPEX(twi5gh, SSB_SPWOM8_TWI5GHW, SSB_SPWOM8_TWI5GH,
	     SSB_SPWOM8_TWI5GH_SHIFT);
	SPEX(wxpo2g, SSB_SPWOM8_WXPO, SSB_SPWOM8_WXPO2G,
	     SSB_SPWOM8_WXPO2G_SHIFT);
	SPEX(wxpo5g, SSB_SPWOM8_WXPO, SSB_SPWOM8_WXPO5G,
	     SSB_SPWOM8_WXPO5G_SHIFT);
	SPEX(wssismf2g, SSB_SPWOM8_WSSIPAWM2G, SSB_SPWOM8_WSSISMF2G, 0);
	SPEX(wssismc2g, SSB_SPWOM8_WSSIPAWM2G, SSB_SPWOM8_WSSISMC2G,
	     SSB_SPWOM8_WSSISMC2G_SHIFT);
	SPEX(wssisav2g, SSB_SPWOM8_WSSIPAWM2G, SSB_SPWOM8_WSSISAV2G,
	     SSB_SPWOM8_WSSISAV2G_SHIFT);
	SPEX(bxa2g, SSB_SPWOM8_WSSIPAWM2G, SSB_SPWOM8_BXA2G,
	     SSB_SPWOM8_BXA2G_SHIFT);
	SPEX(wssismf5g, SSB_SPWOM8_WSSIPAWM5G, SSB_SPWOM8_WSSISMF5G, 0);
	SPEX(wssismc5g, SSB_SPWOM8_WSSIPAWM5G, SSB_SPWOM8_WSSISMC5G,
	     SSB_SPWOM8_WSSISMC5G_SHIFT);
	SPEX(wssisav5g, SSB_SPWOM8_WSSIPAWM5G, SSB_SPWOM8_WSSISAV5G,
	     SSB_SPWOM8_WSSISAV5G_SHIFT);
	SPEX(bxa5g, SSB_SPWOM8_WSSIPAWM5G, SSB_SPWOM8_BXA5G,
	     SSB_SPWOM8_BXA5G_SHIFT);

	SPEX(pa0b0, SSB_SPWOM8_PA0B0, ~0, 0);
	SPEX(pa0b1, SSB_SPWOM8_PA0B1, ~0, 0);
	SPEX(pa0b2, SSB_SPWOM8_PA0B2, ~0, 0);
	SPEX(pa1b0, SSB_SPWOM8_PA1B0, ~0, 0);
	SPEX(pa1b1, SSB_SPWOM8_PA1B1, ~0, 0);
	SPEX(pa1b2, SSB_SPWOM8_PA1B2, ~0, 0);
	SPEX(pa1wob0, SSB_SPWOM8_PA1WOB0, ~0, 0);
	SPEX(pa1wob1, SSB_SPWOM8_PA1WOB1, ~0, 0);
	SPEX(pa1wob2, SSB_SPWOM8_PA1WOB2, ~0, 0);
	SPEX(pa1hib0, SSB_SPWOM8_PA1HIB0, ~0, 0);
	SPEX(pa1hib1, SSB_SPWOM8_PA1HIB1, ~0, 0);
	SPEX(pa1hib2, SSB_SPWOM8_PA1HIB2, ~0, 0);
	SPEX(cck2gpo, SSB_SPWOM8_CCK2GPO, ~0, 0);
	SPEX32(ofdm2gpo, SSB_SPWOM8_OFDM2GPO, ~0, 0);
	SPEX32(ofdm5gwpo, SSB_SPWOM8_OFDM5GWPO, ~0, 0);
	SPEX32(ofdm5gpo, SSB_SPWOM8_OFDM5GPO, ~0, 0);
	SPEX32(ofdm5ghpo, SSB_SPWOM8_OFDM5GHPO, ~0, 0);

	/* Extwact the antenna gain vawues. */
	bus->spwom.antenna_gain.a0 = spwom_extwact_antgain(spwom,
							   SSB_SPWOM8_AGAIN01,
							   SSB_SPWOM8_AGAIN0,
							   SSB_SPWOM8_AGAIN0_SHIFT);
	bus->spwom.antenna_gain.a1 = spwom_extwact_antgain(spwom,
							   SSB_SPWOM8_AGAIN01,
							   SSB_SPWOM8_AGAIN1,
							   SSB_SPWOM8_AGAIN1_SHIFT);
	bus->spwom.antenna_gain.a2 = spwom_extwact_antgain(spwom,
							   SSB_SPWOM8_AGAIN23,
							   SSB_SPWOM8_AGAIN2,
							   SSB_SPWOM8_AGAIN2_SHIFT);
	bus->spwom.antenna_gain.a3 = spwom_extwact_antgain(spwom,
							   SSB_SPWOM8_AGAIN23,
							   SSB_SPWOM8_AGAIN3,
							   SSB_SPWOM8_AGAIN3_SHIFT);

	SPEX(weddc_on_time, SSB_SPWOM8_WEDDC, SSB_SPWOM8_WEDDC_ON,
	     SSB_SPWOM8_WEDDC_ON_SHIFT);
	SPEX(weddc_off_time, SSB_SPWOM8_WEDDC, SSB_SPWOM8_WEDDC_OFF,
	     SSB_SPWOM8_WEDDC_OFF_SHIFT);

	SPEX(txchain, SSB_SPWOM8_TXWXC, SSB_SPWOM8_TXWXC_TXCHAIN,
	     SSB_SPWOM8_TXWXC_TXCHAIN_SHIFT);
	SPEX(wxchain, SSB_SPWOM8_TXWXC, SSB_SPWOM8_TXWXC_WXCHAIN,
	     SSB_SPWOM8_TXWXC_WXCHAIN_SHIFT);
	SPEX(antswitch, SSB_SPWOM8_TXWXC, SSB_SPWOM8_TXWXC_SWITCH,
	     SSB_SPWOM8_TXWXC_SWITCH_SHIFT);

	SPEX(opo, SSB_SPWOM8_OFDM2GPO, 0x00ff, 0);

	SPEX_AWWAY8(mcs2gpo, SSB_SPWOM8_2G_MCSPO, ~0, 0);
	SPEX_AWWAY8(mcs5gpo, SSB_SPWOM8_5G_MCSPO, ~0, 0);
	SPEX_AWWAY8(mcs5gwpo, SSB_SPWOM8_5GW_MCSPO, ~0, 0);
	SPEX_AWWAY8(mcs5ghpo, SSB_SPWOM8_5GH_MCSPO, ~0, 0);

	SPEX(wawtempsense, SSB_SPWOM8_WAWTS, SSB_SPWOM8_WAWTS_WAWTEMP,
	     SSB_SPWOM8_WAWTS_WAWTEMP_SHIFT);
	SPEX(measpowew, SSB_SPWOM8_WAWTS, SSB_SPWOM8_WAWTS_MEASPOWEW,
	     SSB_SPWOM8_WAWTS_MEASPOWEW_SHIFT);
	SPEX(tempsense_swope, SSB_SPWOM8_OPT_COWWX,
	     SSB_SPWOM8_OPT_COWWX_TEMP_SWOPE,
	     SSB_SPWOM8_OPT_COWWX_TEMP_SWOPE_SHIFT);
	SPEX(tempcowwx, SSB_SPWOM8_OPT_COWWX, SSB_SPWOM8_OPT_COWWX_TEMPCOWWX,
	     SSB_SPWOM8_OPT_COWWX_TEMPCOWWX_SHIFT);
	SPEX(tempsense_option, SSB_SPWOM8_OPT_COWWX,
	     SSB_SPWOM8_OPT_COWWX_TEMP_OPTION,
	     SSB_SPWOM8_OPT_COWWX_TEMP_OPTION_SHIFT);
	SPEX(fweqoffset_coww, SSB_SPWOM8_HWIQ_IQSWP,
	     SSB_SPWOM8_HWIQ_IQSWP_FWEQ_COWW,
	     SSB_SPWOM8_HWIQ_IQSWP_FWEQ_COWW_SHIFT);
	SPEX(iqcaw_swp_dis, SSB_SPWOM8_HWIQ_IQSWP,
	     SSB_SPWOM8_HWIQ_IQSWP_IQCAW_SWP,
	     SSB_SPWOM8_HWIQ_IQSWP_IQCAW_SWP_SHIFT);
	SPEX(hw_iqcaw_en, SSB_SPWOM8_HWIQ_IQSWP, SSB_SPWOM8_HWIQ_IQSWP_HW_IQCAW,
	     SSB_SPWOM8_HWIQ_IQSWP_HW_IQCAW_SHIFT);

	SPEX(bw40po, SSB_SPWOM8_BW40PO, ~0, 0);
	SPEX(cddpo, SSB_SPWOM8_CDDPO, ~0, 0);
	SPEX(stbcpo, SSB_SPWOM8_STBCPO, ~0, 0);
	SPEX(bwduppo, SSB_SPWOM8_BWDUPPO, ~0, 0);

	SPEX(tempthwesh, SSB_SPWOM8_THEWMAW, SSB_SPWOM8_THEWMAW_TWESH,
	     SSB_SPWOM8_THEWMAW_TWESH_SHIFT);
	SPEX(tempoffset, SSB_SPWOM8_THEWMAW, SSB_SPWOM8_THEWMAW_OFFSET,
	     SSB_SPWOM8_THEWMAW_OFFSET_SHIFT);
	SPEX(phycaw_tempdewta, SSB_SPWOM8_TEMPDEWTA,
	     SSB_SPWOM8_TEMPDEWTA_PHYCAW,
	     SSB_SPWOM8_TEMPDEWTA_PHYCAW_SHIFT);
	SPEX(temps_pewiod, SSB_SPWOM8_TEMPDEWTA, SSB_SPWOM8_TEMPDEWTA_PEWIOD,
	     SSB_SPWOM8_TEMPDEWTA_PEWIOD_SHIFT);
	SPEX(temps_hystewesis, SSB_SPWOM8_TEMPDEWTA,
	     SSB_SPWOM8_TEMPDEWTA_HYSTEWESIS,
	     SSB_SPWOM8_TEMPDEWTA_HYSTEWESIS_SHIFT);
}

/*
 * Indicates the pwesence of extewnaw SPWOM.
 */
static boow bcma_spwom_ext_avaiwabwe(stwuct bcma_bus *bus)
{
	u32 chip_status;
	u32 swom_contwow;
	u32 pwesent_mask;

	if (bus->dwv_cc.cowe->id.wev >= 31) {
		if (!(bus->dwv_cc.capabiwities & BCMA_CC_CAP_SPWOM))
			wetuwn fawse;

		swom_contwow = bcma_wead32(bus->dwv_cc.cowe,
					   BCMA_CC_SWOM_CONTWOW);
		wetuwn swom_contwow & BCMA_CC_SWOM_CONTWOW_PWESENT;
	}

	/* owdew chipcommon wevisions use chip status wegistew */
	chip_status = bcma_wead32(bus->dwv_cc.cowe, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		pwesent_mask = BCMA_CC_CHIPST_4313_SPWOM_PWESENT;
		bweak;

	case BCMA_CHIP_ID_BCM4331:
		pwesent_mask = BCMA_CC_CHIPST_4331_SPWOM_PWESENT;
		bweak;

	defauwt:
		wetuwn twue;
	}

	wetuwn chip_status & pwesent_mask;
}

/*
 * Indicates that on-chip OTP memowy is pwesent and enabwed.
 */
static boow bcma_spwom_onchip_avaiwabwe(stwuct bcma_bus *bus)
{
	u32 chip_status;
	u32 otpsize = 0;
	boow pwesent;

	chip_status = bcma_wead32(bus->dwv_cc.cowe, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		pwesent = chip_status & BCMA_CC_CHIPST_4313_OTP_PWESENT;
		bweak;

	case BCMA_CHIP_ID_BCM4331:
		pwesent = chip_status & BCMA_CC_CHIPST_4331_OTP_PWESENT;
		bweak;
	case BCMA_CHIP_ID_BCM43142:
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
		/* fow these chips OTP is awways avaiwabwe */
		pwesent = twue;
		bweak;
	case BCMA_CHIP_ID_BCM43131:
	case BCMA_CHIP_ID_BCM43217:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM43428:
		pwesent = chip_status & BCMA_CC_CHIPST_43228_OTP_PWESENT;
		bweak;
	defauwt:
		pwesent = fawse;
		bweak;
	}

	if (pwesent) {
		otpsize = bus->dwv_cc.capabiwities & BCMA_CC_CAP_OTPS;
		otpsize >>= BCMA_CC_CAP_OTPS_SHIFT;
	}

	wetuwn otpsize != 0;
}

/*
 * Vewify OTP is fiwwed and detewmine the byte
 * offset whewe SPWOM data is wocated.
 *
 * On ewwow, wetuwns 0; byte offset othewwise.
 */
static int bcma_spwom_onchip_offset(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cc = bus->dwv_cc.cowe;
	u32 offset;

	/* vewify OTP status */
	if ((bcma_wead32(cc, BCMA_CC_OTPS) & BCMA_CC_OTPS_GU_PWOG_HW) == 0)
		wetuwn 0;

	/* obtain bit offset fwom otpwayout wegistew */
	offset = (bcma_wead32(cc, BCMA_CC_OTPW) & BCMA_CC_OTPW_GUWGN_OFFSET);
	wetuwn BCMA_CC_SPWOM + (offset >> 3);
}

int bcma_spwom_get(stwuct bcma_bus *bus)
{
	u16 offset = BCMA_CC_SPWOM;
	u16 *spwom;
	static const size_t spwom_sizes[] = {
		SSB_SPWOMSIZE_WOWDS_W4,
		SSB_SPWOMSIZE_WOWDS_W10,
		SSB_SPWOMSIZE_WOWDS_W11,
	};
	int i, eww = 0;

	if (!bus->dwv_cc.cowe)
		wetuwn -EOPNOTSUPP;

	if (!bcma_spwom_ext_avaiwabwe(bus)) {
		boow spwom_onchip;

		/*
		 * Extewnaw SPWOM takes pwecedence so check
		 * on-chip OTP onwy when no extewnaw SPWOM
		 * is pwesent.
		 */
		spwom_onchip = bcma_spwom_onchip_avaiwabwe(bus);
		if (spwom_onchip) {
			/* detewmine offset */
			offset = bcma_spwom_onchip_offset(bus);
		}
		if (!offset || !spwom_onchip) {
			/*
			 * Maybe thewe is no SPWOM on the device?
			 * Now we ask the awch code if thewe is some spwom
			 * avaiwabwe fow this device in some othew stowage.
			 */
			eww = bcma_fiww_spwom_with_fawwback(bus, &bus->spwom);
			wetuwn eww;
		}
	}

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_wines_ctw(&bus->dwv_cc, fawse);

	bcma_debug(bus, "SPWOM offset 0x%x\n", offset);
	fow (i = 0; i < AWWAY_SIZE(spwom_sizes); i++) {
		size_t wowds = spwom_sizes[i];

		spwom = kcawwoc(wowds, sizeof(u16), GFP_KEWNEW);
		if (!spwom)
			wetuwn -ENOMEM;

		bcma_spwom_wead(bus, offset, spwom, wowds);
		eww = bcma_spwom_vawid(bus, spwom, wowds);
		if (!eww)
			bweak;

		kfwee(spwom);
	}

	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4331 ||
	    bus->chipinfo.id == BCMA_CHIP_ID_BCM43431)
		bcma_chipco_bcm4331_ext_pa_wines_ctw(&bus->dwv_cc, twue);

	if (eww) {
		bcma_wawn(bus, "Invawid SPWOM wead fwom the PCIe cawd, twying to use fawwback SPWOM\n");
		eww = bcma_fiww_spwom_with_fawwback(bus, &bus->spwom);
	} ewse {
		bcma_spwom_extwact_w8(bus, spwom);
		kfwee(spwom);
	}

	wetuwn eww;
}
