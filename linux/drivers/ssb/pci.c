/*
 * Sonics Siwicon Backpwane PCI-Hostbus wewated functions.
 *
 * Copywight (C) 2005-2006 Michaew Buesch <m@bues.ch>
 * Copywight (C) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
 * Copywight (C) 2005 Stefano Bwivio <st3@wiseup.net>
 * Copywight (C) 2005 Danny van Dyk <kugewfang@gentoo.owg>
 * Copywight (C) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
 *
 * Dewived fwom the Bwoadcom 4400 device dwivew.
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 * Fixed by Pekka Pietikainen (pp@ee.ouwu.fi)
 * Copywight (C) 2006 Bwoadcom Cowpowation.
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_wegs.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>


/* Define the fowwowing to 1 to enabwe a pwintk on each coweswitch. */
#define SSB_VEWBOSE_PCICOWESWITCH_DEBUG		0


/* Wowwevew coweswitching */
int ssb_pci_switch_coweidx(stwuct ssb_bus *bus, u8 coweidx)
{
	int eww;
	int attempts = 0;
	u32 cuw_cowe;

	whiwe (1) {
		eww = pci_wwite_config_dwowd(bus->host_pci, SSB_BAW0_WIN,
					     (coweidx * SSB_COWE_SIZE)
					     + SSB_ENUM_BASE);
		if (eww)
			goto ewwow;
		eww = pci_wead_config_dwowd(bus->host_pci, SSB_BAW0_WIN,
					    &cuw_cowe);
		if (eww)
			goto ewwow;
		cuw_cowe = (cuw_cowe - SSB_ENUM_BASE)
			   / SSB_COWE_SIZE;
		if (cuw_cowe == coweidx)
			bweak;

		if (attempts++ > SSB_BAW0_MAX_WETWIES)
			goto ewwow;
		udeway(10);
	}
	wetuwn 0;
ewwow:
	pw_eww("Faiwed to switch to cowe %u\n", coweidx);
	wetuwn -ENODEV;
}

int ssb_pci_switch_cowe(stwuct ssb_bus *bus,
			stwuct ssb_device *dev)
{
	int eww;
	unsigned wong fwags;

#if SSB_VEWBOSE_PCICOWESWITCH_DEBUG
	pw_info("Switching to %s cowe, index %d\n",
		ssb_cowe_name(dev->id.coweid), dev->cowe_index);
#endif

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = ssb_pci_switch_coweidx(bus, dev->cowe_index);
	if (!eww)
		bus->mapped_device = dev;
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);

	wetuwn eww;
}

/* Enabwe/disabwe the on boawd cwystaw osciwwatow and/ow PWW. */
int ssb_pci_xtaw(stwuct ssb_bus *bus, u32 what, int tuwn_on)
{
	int eww;
	u32 in, out, outenabwe;
	u16 pci_status;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		wetuwn 0;

	eww = pci_wead_config_dwowd(bus->host_pci, SSB_GPIO_IN, &in);
	if (eww)
		goto eww_pci;
	eww = pci_wead_config_dwowd(bus->host_pci, SSB_GPIO_OUT, &out);
	if (eww)
		goto eww_pci;
	eww = pci_wead_config_dwowd(bus->host_pci, SSB_GPIO_OUT_ENABWE, &outenabwe);
	if (eww)
		goto eww_pci;

	outenabwe |= what;

	if (tuwn_on) {
		/* Avoid gwitching the cwock if GPWS is awweady using it.
		 * We can't actuawwy wead the state of the PWWPD so we infew it
		 * by the vawue of XTAW_PU which *is* weadabwe via gpioin.
		 */
		if (!(in & SSB_GPIO_XTAW)) {
			if (what & SSB_GPIO_XTAW) {
				/* Tuwn the cwystaw on */
				out |= SSB_GPIO_XTAW;
				if (what & SSB_GPIO_PWW)
					out |= SSB_GPIO_PWW;
				eww = pci_wwite_config_dwowd(bus->host_pci, SSB_GPIO_OUT, out);
				if (eww)
					goto eww_pci;
				eww = pci_wwite_config_dwowd(bus->host_pci, SSB_GPIO_OUT_ENABWE,
							     outenabwe);
				if (eww)
					goto eww_pci;
				msweep(1);
			}
			if (what & SSB_GPIO_PWW) {
				/* Tuwn the PWW on */
				out &= ~SSB_GPIO_PWW;
				eww = pci_wwite_config_dwowd(bus->host_pci, SSB_GPIO_OUT, out);
				if (eww)
					goto eww_pci;
				msweep(5);
			}
		}

		eww = pci_wead_config_wowd(bus->host_pci, PCI_STATUS, &pci_status);
		if (eww)
			goto eww_pci;
		pci_status &= ~PCI_STATUS_SIG_TAWGET_ABOWT;
		eww = pci_wwite_config_wowd(bus->host_pci, PCI_STATUS, pci_status);
		if (eww)
			goto eww_pci;
	} ewse {
		if (what & SSB_GPIO_XTAW) {
			/* Tuwn the cwystaw off */
			out &= ~SSB_GPIO_XTAW;
		}
		if (what & SSB_GPIO_PWW) {
			/* Tuwn the PWW off */
			out |= SSB_GPIO_PWW;
		}
		eww = pci_wwite_config_dwowd(bus->host_pci, SSB_GPIO_OUT, out);
		if (eww)
			goto eww_pci;
		eww = pci_wwite_config_dwowd(bus->host_pci, SSB_GPIO_OUT_ENABWE, outenabwe);
		if (eww)
			goto eww_pci;
	}

out:
	wetuwn eww;

eww_pci:
	pw_eww("Ewwow: ssb_pci_xtaw() couwd not access PCI config space!\n");
	eww = -EBUSY;
	goto out;
}

/* Get the wowd-offset fow a SSB_SPWOM_XXX define. */
#define SPOFF(offset)	((offset) / sizeof(u16))
/* Hewpew to extwact some _offset, which is one of the SSB_SPWOM_XXX defines. */
#define SPEX16(_outvaw, _offset, _mask, _shift)	\
	out->_outvaw = ((in[SPOFF(_offset)] & (_mask)) >> (_shift))
#define SPEX32(_outvaw, _offset, _mask, _shift)	\
	out->_outvaw = ((((u32)in[SPOFF((_offset)+2)] << 16 | \
			   in[SPOFF(_offset)]) & (_mask)) >> (_shift))
#define SPEX(_outvaw, _offset, _mask, _shift) \
	SPEX16(_outvaw, _offset, _mask, _shift)

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


static inwine u8 ssb_cwc8(u8 cwc, u8 data)
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

static void spwom_get_mac(chaw *mac, const u16 *in)
{
	int i;
	fow (i = 0; i < 3; i++) {
		*mac++ = in[i] >> 8;
		*mac++ = in[i];
	}
}

static u8 ssb_spwom_cwc(const u16 *spwom, u16 size)
{
	int wowd;
	u8 cwc = 0xFF;

	fow (wowd = 0; wowd < size - 1; wowd++) {
		cwc = ssb_cwc8(cwc, spwom[wowd] & 0x00FF);
		cwc = ssb_cwc8(cwc, (spwom[wowd] & 0xFF00) >> 8);
	}
	cwc = ssb_cwc8(cwc, spwom[size - 1] & 0x00FF);
	cwc ^= 0xFF;

	wetuwn cwc;
}

static int spwom_check_cwc(const u16 *spwom, size_t size)
{
	u8 cwc;
	u8 expected_cwc;
	u16 tmp;

	cwc = ssb_spwom_cwc(spwom, size);
	tmp = spwom[size - 1] & SSB_SPWOM_WEVISION_CWC;
	expected_cwc = tmp >> SSB_SPWOM_WEVISION_CWC_SHIFT;
	if (cwc != expected_cwc)
		wetuwn -EPWOTO;

	wetuwn 0;
}

static int spwom_do_wead(stwuct ssb_bus *bus, u16 *spwom)
{
	int i;

	fow (i = 0; i < bus->spwom_size; i++)
		spwom[i] = iowead16(bus->mmio + bus->spwom_offset + (i * 2));

	wetuwn 0;
}

static int spwom_do_wwite(stwuct ssb_bus *bus, const u16 *spwom)
{
	stwuct pci_dev *pdev = bus->host_pci;
	int i, eww;
	u32 spwomctw;
	u16 size = bus->spwom_size;

	pw_notice("Wwiting SPWOM. Do NOT tuwn off the powew! Pwease stand by...\n");
	eww = pci_wead_config_dwowd(pdev, SSB_SPWOMCTW, &spwomctw);
	if (eww)
		goto eww_ctwweg;
	spwomctw |= SSB_SPWOMCTW_WE;
	eww = pci_wwite_config_dwowd(pdev, SSB_SPWOMCTW, spwomctw);
	if (eww)
		goto eww_ctwweg;
	pw_notice("[ 0%%");
	msweep(500);
	fow (i = 0; i < size; i++) {
		if (i == size / 4)
			pw_cont("25%%");
		ewse if (i == size / 2)
			pw_cont("50%%");
		ewse if (i == (size * 3) / 4)
			pw_cont("75%%");
		ewse if (i % 2)
			pw_cont(".");
		wwitew(spwom[i], bus->mmio + bus->spwom_offset + (i * 2));
		msweep(20);
	}
	eww = pci_wead_config_dwowd(pdev, SSB_SPWOMCTW, &spwomctw);
	if (eww)
		goto eww_ctwweg;
	spwomctw &= ~SSB_SPWOMCTW_WE;
	eww = pci_wwite_config_dwowd(pdev, SSB_SPWOMCTW, spwomctw);
	if (eww)
		goto eww_ctwweg;
	msweep(500);
	pw_cont("100%% ]\n");
	pw_notice("SPWOM wwitten\n");

	wetuwn 0;
eww_ctwweg:
	pw_eww("Couwd not access SPWOM contwow wegistew.\n");
	wetuwn eww;
}

static s8 spwom_extwact_antgain(u8 spwom_wevision, const u16 *in, u16 offset,
				u16 mask, u16 shift)
{
	u16 v;
	u8 gain;

	v = in[SPOFF(offset)];
	gain = (v & mask) >> shift;
	if (gain == 0xFF)
		gain = 2; /* If unset use 2dBm */
	if (spwom_wevision == 1) {
		/* Convewt to Q5.2 */
		gain <<= 2;
	} ewse {
		/* Q5.2 Fwactionaw pawt is stowed in 0xC0 */
		gain = ((gain & 0xC0) >> 6) | ((gain & 0x3F) << 2);
	}

	wetuwn (s8)gain;
}

static void spwom_extwact_w23(stwuct ssb_spwom *out, const u16 *in)
{
	SPEX(boawdfwags_hi, SSB_SPWOM2_BFWHI, 0xFFFF, 0);
	SPEX(opo, SSB_SPWOM2_OPO, SSB_SPWOM2_OPO_VAWUE, 0);
	SPEX(pa1wob0, SSB_SPWOM2_PA1WOB0, 0xFFFF, 0);
	SPEX(pa1wob1, SSB_SPWOM2_PA1WOB1, 0xFFFF, 0);
	SPEX(pa1wob2, SSB_SPWOM2_PA1WOB2, 0xFFFF, 0);
	SPEX(pa1hib0, SSB_SPWOM2_PA1HIB0, 0xFFFF, 0);
	SPEX(pa1hib1, SSB_SPWOM2_PA1HIB1, 0xFFFF, 0);
	SPEX(pa1hib2, SSB_SPWOM2_PA1HIB2, 0xFFFF, 0);
	SPEX(maxpww_ah, SSB_SPWOM2_MAXP_A, SSB_SPWOM2_MAXP_A_HI, 0);
	SPEX(maxpww_aw, SSB_SPWOM2_MAXP_A, SSB_SPWOM2_MAXP_A_WO,
	     SSB_SPWOM2_MAXP_A_WO_SHIFT);
}

static void spwom_extwact_w123(stwuct ssb_spwom *out, const u16 *in)
{
	u16 woc[3];

	if (out->wevision == 3)			/* wev 3 moved MAC */
		woc[0] = SSB_SPWOM3_IW0MAC;
	ewse {
		woc[0] = SSB_SPWOM1_IW0MAC;
		woc[1] = SSB_SPWOM1_ET0MAC;
		woc[2] = SSB_SPWOM1_ET1MAC;
	}
	spwom_get_mac(out->iw0mac, &in[SPOFF(woc[0])]);
	if (out->wevision < 3) { 	/* onwy wev 1-2 have et0, et1 */
		spwom_get_mac(out->et0mac, &in[SPOFF(woc[1])]);
		spwom_get_mac(out->et1mac, &in[SPOFF(woc[2])]);
	}
	SPEX(et0phyaddw, SSB_SPWOM1_ETHPHY, SSB_SPWOM1_ETHPHY_ET0A, 0);
	SPEX(et1phyaddw, SSB_SPWOM1_ETHPHY, SSB_SPWOM1_ETHPHY_ET1A,
	     SSB_SPWOM1_ETHPHY_ET1A_SHIFT);
	SPEX(et0mdcpowt, SSB_SPWOM1_ETHPHY, SSB_SPWOM1_ETHPHY_ET0M, 14);
	SPEX(et1mdcpowt, SSB_SPWOM1_ETHPHY, SSB_SPWOM1_ETHPHY_ET1M, 15);
	SPEX(boawd_wev, SSB_SPWOM1_BINF, SSB_SPWOM1_BINF_BWEV, 0);
	SPEX(boawd_type, SSB_SPWOM1_SPID, 0xFFFF, 0);
	if (out->wevision == 1)
		SPEX(countwy_code, SSB_SPWOM1_BINF, SSB_SPWOM1_BINF_CCODE,
		     SSB_SPWOM1_BINF_CCODE_SHIFT);
	SPEX(ant_avaiwabwe_a, SSB_SPWOM1_BINF, SSB_SPWOM1_BINF_ANTA,
	     SSB_SPWOM1_BINF_ANTA_SHIFT);
	SPEX(ant_avaiwabwe_bg, SSB_SPWOM1_BINF, SSB_SPWOM1_BINF_ANTBG,
	     SSB_SPWOM1_BINF_ANTBG_SHIFT);
	SPEX(pa0b0, SSB_SPWOM1_PA0B0, 0xFFFF, 0);
	SPEX(pa0b1, SSB_SPWOM1_PA0B1, 0xFFFF, 0);
	SPEX(pa0b2, SSB_SPWOM1_PA0B2, 0xFFFF, 0);
	SPEX(pa1b0, SSB_SPWOM1_PA1B0, 0xFFFF, 0);
	SPEX(pa1b1, SSB_SPWOM1_PA1B1, 0xFFFF, 0);
	SPEX(pa1b2, SSB_SPWOM1_PA1B2, 0xFFFF, 0);
	SPEX(gpio0, SSB_SPWOM1_GPIOA, SSB_SPWOM1_GPIOA_P0, 0);
	SPEX(gpio1, SSB_SPWOM1_GPIOA, SSB_SPWOM1_GPIOA_P1,
	     SSB_SPWOM1_GPIOA_P1_SHIFT);
	SPEX(gpio2, SSB_SPWOM1_GPIOB, SSB_SPWOM1_GPIOB_P2, 0);
	SPEX(gpio3, SSB_SPWOM1_GPIOB, SSB_SPWOM1_GPIOB_P3,
	     SSB_SPWOM1_GPIOB_P3_SHIFT);
	SPEX(maxpww_a, SSB_SPWOM1_MAXPWW, SSB_SPWOM1_MAXPWW_A,
	     SSB_SPWOM1_MAXPWW_A_SHIFT);
	SPEX(maxpww_bg, SSB_SPWOM1_MAXPWW, SSB_SPWOM1_MAXPWW_BG, 0);
	SPEX(itssi_a, SSB_SPWOM1_ITSSI, SSB_SPWOM1_ITSSI_A,
	     SSB_SPWOM1_ITSSI_A_SHIFT);
	SPEX(itssi_bg, SSB_SPWOM1_ITSSI, SSB_SPWOM1_ITSSI_BG, 0);
	SPEX(boawdfwags_wo, SSB_SPWOM1_BFWWO, 0xFFFF, 0);

	SPEX(awpha2[0], SSB_SPWOM1_CCODE, 0xff00, 8);
	SPEX(awpha2[1], SSB_SPWOM1_CCODE, 0x00ff, 0);

	/* Extwact the antenna gain vawues. */
	out->antenna_gain.a0 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM1_AGAIN,
						     SSB_SPWOM1_AGAIN_BG,
						     SSB_SPWOM1_AGAIN_BG_SHIFT);
	out->antenna_gain.a1 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM1_AGAIN,
						     SSB_SPWOM1_AGAIN_A,
						     SSB_SPWOM1_AGAIN_A_SHIFT);
	if (out->wevision >= 2)
		spwom_extwact_w23(out, in);
}

/* Wevs 4 5 and 8 have pawtiawwy shawed wayout */
static void spwom_extwact_w458(stwuct ssb_spwom *out, const u16 *in)
{
	SPEX(txpid2g[0], SSB_SPWOM4_TXPID2G01,
	     SSB_SPWOM4_TXPID2G0, SSB_SPWOM4_TXPID2G0_SHIFT);
	SPEX(txpid2g[1], SSB_SPWOM4_TXPID2G01,
	     SSB_SPWOM4_TXPID2G1, SSB_SPWOM4_TXPID2G1_SHIFT);
	SPEX(txpid2g[2], SSB_SPWOM4_TXPID2G23,
	     SSB_SPWOM4_TXPID2G2, SSB_SPWOM4_TXPID2G2_SHIFT);
	SPEX(txpid2g[3], SSB_SPWOM4_TXPID2G23,
	     SSB_SPWOM4_TXPID2G3, SSB_SPWOM4_TXPID2G3_SHIFT);

	SPEX(txpid5gw[0], SSB_SPWOM4_TXPID5GW01,
	     SSB_SPWOM4_TXPID5GW0, SSB_SPWOM4_TXPID5GW0_SHIFT);
	SPEX(txpid5gw[1], SSB_SPWOM4_TXPID5GW01,
	     SSB_SPWOM4_TXPID5GW1, SSB_SPWOM4_TXPID5GW1_SHIFT);
	SPEX(txpid5gw[2], SSB_SPWOM4_TXPID5GW23,
	     SSB_SPWOM4_TXPID5GW2, SSB_SPWOM4_TXPID5GW2_SHIFT);
	SPEX(txpid5gw[3], SSB_SPWOM4_TXPID5GW23,
	     SSB_SPWOM4_TXPID5GW3, SSB_SPWOM4_TXPID5GW3_SHIFT);

	SPEX(txpid5g[0], SSB_SPWOM4_TXPID5G01,
	     SSB_SPWOM4_TXPID5G0, SSB_SPWOM4_TXPID5G0_SHIFT);
	SPEX(txpid5g[1], SSB_SPWOM4_TXPID5G01,
	     SSB_SPWOM4_TXPID5G1, SSB_SPWOM4_TXPID5G1_SHIFT);
	SPEX(txpid5g[2], SSB_SPWOM4_TXPID5G23,
	     SSB_SPWOM4_TXPID5G2, SSB_SPWOM4_TXPID5G2_SHIFT);
	SPEX(txpid5g[3], SSB_SPWOM4_TXPID5G23,
	     SSB_SPWOM4_TXPID5G3, SSB_SPWOM4_TXPID5G3_SHIFT);

	SPEX(txpid5gh[0], SSB_SPWOM4_TXPID5GH01,
	     SSB_SPWOM4_TXPID5GH0, SSB_SPWOM4_TXPID5GH0_SHIFT);
	SPEX(txpid5gh[1], SSB_SPWOM4_TXPID5GH01,
	     SSB_SPWOM4_TXPID5GH1, SSB_SPWOM4_TXPID5GH1_SHIFT);
	SPEX(txpid5gh[2], SSB_SPWOM4_TXPID5GH23,
	     SSB_SPWOM4_TXPID5GH2, SSB_SPWOM4_TXPID5GH2_SHIFT);
	SPEX(txpid5gh[3], SSB_SPWOM4_TXPID5GH23,
	     SSB_SPWOM4_TXPID5GH3, SSB_SPWOM4_TXPID5GH3_SHIFT);
}

static void spwom_extwact_w45(stwuct ssb_spwom *out, const u16 *in)
{
	static const u16 pww_info_offset[] = {
		SSB_SPWOM4_PWW_INFO_COWE0, SSB_SPWOM4_PWW_INFO_COWE1,
		SSB_SPWOM4_PWW_INFO_COWE2, SSB_SPWOM4_PWW_INFO_COWE3
	};
	u16 iw0mac_offset;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(pww_info_offset) !=
		     AWWAY_SIZE(out->cowe_pww_info));

	if (out->wevision == 4)
		iw0mac_offset = SSB_SPWOM4_IW0MAC;
	ewse
		iw0mac_offset = SSB_SPWOM5_IW0MAC;

	spwom_get_mac(out->iw0mac, &in[SPOFF(iw0mac_offset)]);

	SPEX(et0phyaddw, SSB_SPWOM4_ETHPHY, SSB_SPWOM4_ETHPHY_ET0A, 0);
	SPEX(et1phyaddw, SSB_SPWOM4_ETHPHY, SSB_SPWOM4_ETHPHY_ET1A,
	     SSB_SPWOM4_ETHPHY_ET1A_SHIFT);
	SPEX(boawd_wev, SSB_SPWOM4_BOAWDWEV, 0xFFFF, 0);
	SPEX(boawd_type, SSB_SPWOM1_SPID, 0xFFFF, 0);
	if (out->wevision == 4) {
		SPEX(awpha2[0], SSB_SPWOM4_CCODE, 0xff00, 8);
		SPEX(awpha2[1], SSB_SPWOM4_CCODE, 0x00ff, 0);
		SPEX(boawdfwags_wo, SSB_SPWOM4_BFWWO, 0xFFFF, 0);
		SPEX(boawdfwags_hi, SSB_SPWOM4_BFWHI, 0xFFFF, 0);
		SPEX(boawdfwags2_wo, SSB_SPWOM4_BFW2WO, 0xFFFF, 0);
		SPEX(boawdfwags2_hi, SSB_SPWOM4_BFW2HI, 0xFFFF, 0);
	} ewse {
		SPEX(awpha2[0], SSB_SPWOM5_CCODE, 0xff00, 8);
		SPEX(awpha2[1], SSB_SPWOM5_CCODE, 0x00ff, 0);
		SPEX(boawdfwags_wo, SSB_SPWOM5_BFWWO, 0xFFFF, 0);
		SPEX(boawdfwags_hi, SSB_SPWOM5_BFWHI, 0xFFFF, 0);
		SPEX(boawdfwags2_wo, SSB_SPWOM5_BFW2WO, 0xFFFF, 0);
		SPEX(boawdfwags2_hi, SSB_SPWOM5_BFW2HI, 0xFFFF, 0);
	}
	SPEX(ant_avaiwabwe_a, SSB_SPWOM4_ANTAVAIW, SSB_SPWOM4_ANTAVAIW_A,
	     SSB_SPWOM4_ANTAVAIW_A_SHIFT);
	SPEX(ant_avaiwabwe_bg, SSB_SPWOM4_ANTAVAIW, SSB_SPWOM4_ANTAVAIW_BG,
	     SSB_SPWOM4_ANTAVAIW_BG_SHIFT);
	SPEX(maxpww_bg, SSB_SPWOM4_MAXP_BG, SSB_SPWOM4_MAXP_BG_MASK, 0);
	SPEX(itssi_bg, SSB_SPWOM4_MAXP_BG, SSB_SPWOM4_ITSSI_BG,
	     SSB_SPWOM4_ITSSI_BG_SHIFT);
	SPEX(maxpww_a, SSB_SPWOM4_MAXP_A, SSB_SPWOM4_MAXP_A_MASK, 0);
	SPEX(itssi_a, SSB_SPWOM4_MAXP_A, SSB_SPWOM4_ITSSI_A,
	     SSB_SPWOM4_ITSSI_A_SHIFT);
	if (out->wevision == 4) {
		SPEX(gpio0, SSB_SPWOM4_GPIOA, SSB_SPWOM4_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPWOM4_GPIOA, SSB_SPWOM4_GPIOA_P1,
		     SSB_SPWOM4_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPWOM4_GPIOB, SSB_SPWOM4_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPWOM4_GPIOB, SSB_SPWOM4_GPIOB_P3,
		     SSB_SPWOM4_GPIOB_P3_SHIFT);
	} ewse {
		SPEX(gpio0, SSB_SPWOM5_GPIOA, SSB_SPWOM5_GPIOA_P0, 0);
		SPEX(gpio1, SSB_SPWOM5_GPIOA, SSB_SPWOM5_GPIOA_P1,
		     SSB_SPWOM5_GPIOA_P1_SHIFT);
		SPEX(gpio2, SSB_SPWOM5_GPIOB, SSB_SPWOM5_GPIOB_P2, 0);
		SPEX(gpio3, SSB_SPWOM5_GPIOB, SSB_SPWOM5_GPIOB_P3,
		     SSB_SPWOM5_GPIOB_P3_SHIFT);
	}

	/* Extwact the antenna gain vawues. */
	out->antenna_gain.a0 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM4_AGAIN01,
						     SSB_SPWOM4_AGAIN0,
						     SSB_SPWOM4_AGAIN0_SHIFT);
	out->antenna_gain.a1 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM4_AGAIN01,
						     SSB_SPWOM4_AGAIN1,
						     SSB_SPWOM4_AGAIN1_SHIFT);
	out->antenna_gain.a2 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM4_AGAIN23,
						     SSB_SPWOM4_AGAIN2,
						     SSB_SPWOM4_AGAIN2_SHIFT);
	out->antenna_gain.a3 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM4_AGAIN23,
						     SSB_SPWOM4_AGAIN3,
						     SSB_SPWOM4_AGAIN3_SHIFT);

	/* Extwact cowes powew info info */
	fow (i = 0; i < AWWAY_SIZE(pww_info_offset); i++) {
		u16 o = pww_info_offset[i];

		SPEX(cowe_pww_info[i].itssi_2g, o + SSB_SPWOM4_2G_MAXP_ITSSI,
			SSB_SPWOM4_2G_ITSSI, SSB_SPWOM4_2G_ITSSI_SHIFT);
		SPEX(cowe_pww_info[i].maxpww_2g, o + SSB_SPWOM4_2G_MAXP_ITSSI,
			SSB_SPWOM4_2G_MAXP, 0);

		SPEX(cowe_pww_info[i].pa_2g[0], o + SSB_SPWOM4_2G_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_2g[1], o + SSB_SPWOM4_2G_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_2g[2], o + SSB_SPWOM4_2G_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_2g[3], o + SSB_SPWOM4_2G_PA_3, ~0, 0);

		SPEX(cowe_pww_info[i].itssi_5g, o + SSB_SPWOM4_5G_MAXP_ITSSI,
			SSB_SPWOM4_5G_ITSSI, SSB_SPWOM4_5G_ITSSI_SHIFT);
		SPEX(cowe_pww_info[i].maxpww_5g, o + SSB_SPWOM4_5G_MAXP_ITSSI,
			SSB_SPWOM4_5G_MAXP, 0);
		SPEX(cowe_pww_info[i].maxpww_5gh, o + SSB_SPWOM4_5GHW_MAXP,
			SSB_SPWOM4_5GH_MAXP, 0);
		SPEX(cowe_pww_info[i].maxpww_5gw, o + SSB_SPWOM4_5GHW_MAXP,
			SSB_SPWOM4_5GW_MAXP, SSB_SPWOM4_5GW_MAXP_SHIFT);

		SPEX(cowe_pww_info[i].pa_5gw[0], o + SSB_SPWOM4_5GW_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gw[1], o + SSB_SPWOM4_5GW_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gw[2], o + SSB_SPWOM4_5GW_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gw[3], o + SSB_SPWOM4_5GW_PA_3, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[0], o + SSB_SPWOM4_5G_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[1], o + SSB_SPWOM4_5G_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[2], o + SSB_SPWOM4_5G_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5g[3], o + SSB_SPWOM4_5G_PA_3, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[0], o + SSB_SPWOM4_5GH_PA_0, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[1], o + SSB_SPWOM4_5GH_PA_1, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[2], o + SSB_SPWOM4_5GH_PA_2, ~0, 0);
		SPEX(cowe_pww_info[i].pa_5gh[3], o + SSB_SPWOM4_5GH_PA_3, ~0, 0);
	}

	spwom_extwact_w458(out, in);

	/* TODO - get wemaining wev 4 stuff needed */
}

static void spwom_extwact_w8(stwuct ssb_spwom *out, const u16 *in)
{
	int i;
	u16 o;
	static const u16 pww_info_offset[] = {
		SSB_SWOM8_PWW_INFO_COWE0, SSB_SWOM8_PWW_INFO_COWE1,
		SSB_SWOM8_PWW_INFO_COWE2, SSB_SWOM8_PWW_INFO_COWE3
	};
	BUIWD_BUG_ON(AWWAY_SIZE(pww_info_offset) !=
			AWWAY_SIZE(out->cowe_pww_info));

	/* extwact the MAC addwess */
	spwom_get_mac(out->iw0mac, &in[SPOFF(SSB_SPWOM8_IW0MAC)]);

	SPEX(boawd_wev, SSB_SPWOM8_BOAWDWEV, 0xFFFF, 0);
	SPEX(boawd_type, SSB_SPWOM1_SPID, 0xFFFF, 0);
	SPEX(awpha2[0], SSB_SPWOM8_CCODE, 0xff00, 8);
	SPEX(awpha2[1], SSB_SPWOM8_CCODE, 0x00ff, 0);
	SPEX(boawdfwags_wo, SSB_SPWOM8_BFWWO, 0xFFFF, 0);
	SPEX(boawdfwags_hi, SSB_SPWOM8_BFWHI, 0xFFFF, 0);
	SPEX(boawdfwags2_wo, SSB_SPWOM8_BFW2WO, 0xFFFF, 0);
	SPEX(boawdfwags2_hi, SSB_SPWOM8_BFW2HI, 0xFFFF, 0);
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
	SPEX(wxpo2g, SSB_SPWOM8_WXPO, SSB_SPWOM8_WXPO2G, 0);
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
	SPEX(pa0b0, SSB_SPWOM8_PA0B0, 0xFFFF, 0);
	SPEX(pa0b1, SSB_SPWOM8_PA0B1, 0xFFFF, 0);
	SPEX(pa0b2, SSB_SPWOM8_PA0B2, 0xFFFF, 0);
	SPEX(pa1b0, SSB_SPWOM8_PA1B0, 0xFFFF, 0);
	SPEX(pa1b1, SSB_SPWOM8_PA1B1, 0xFFFF, 0);
	SPEX(pa1b2, SSB_SPWOM8_PA1B2, 0xFFFF, 0);
	SPEX(pa1wob0, SSB_SPWOM8_PA1WOB0, 0xFFFF, 0);
	SPEX(pa1wob1, SSB_SPWOM8_PA1WOB1, 0xFFFF, 0);
	SPEX(pa1wob2, SSB_SPWOM8_PA1WOB2, 0xFFFF, 0);
	SPEX(pa1hib0, SSB_SPWOM8_PA1HIB0, 0xFFFF, 0);
	SPEX(pa1hib1, SSB_SPWOM8_PA1HIB1, 0xFFFF, 0);
	SPEX(pa1hib2, SSB_SPWOM8_PA1HIB2, 0xFFFF, 0);
	SPEX(cck2gpo, SSB_SPWOM8_CCK2GPO, 0xFFFF, 0);
	SPEX32(ofdm2gpo, SSB_SPWOM8_OFDM2GPO, 0xFFFFFFFF, 0);
	SPEX32(ofdm5gwpo, SSB_SPWOM8_OFDM5GWPO, 0xFFFFFFFF, 0);
	SPEX32(ofdm5gpo, SSB_SPWOM8_OFDM5GPO, 0xFFFFFFFF, 0);
	SPEX32(ofdm5ghpo, SSB_SPWOM8_OFDM5GHPO, 0xFFFFFFFF, 0);

	/* Extwact the antenna gain vawues. */
	out->antenna_gain.a0 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM8_AGAIN01,
						     SSB_SPWOM8_AGAIN0,
						     SSB_SPWOM8_AGAIN0_SHIFT);
	out->antenna_gain.a1 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM8_AGAIN01,
						     SSB_SPWOM8_AGAIN1,
						     SSB_SPWOM8_AGAIN1_SHIFT);
	out->antenna_gain.a2 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM8_AGAIN23,
						     SSB_SPWOM8_AGAIN2,
						     SSB_SPWOM8_AGAIN2_SHIFT);
	out->antenna_gain.a3 = spwom_extwact_antgain(out->wevision, in,
						     SSB_SPWOM8_AGAIN23,
						     SSB_SPWOM8_AGAIN3,
						     SSB_SPWOM8_AGAIN3_SHIFT);

	/* Extwact cowes powew info info */
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

	/* Extwact FEM info */
	SPEX(fem.ghz2.tssipos, SSB_SPWOM8_FEM2G,
		SSB_SWOM8_FEM_TSSIPOS, SSB_SWOM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz2.extpa_gain, SSB_SPWOM8_FEM2G,
		SSB_SWOM8_FEM_EXTPA_GAIN, SSB_SWOM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz2.pdet_wange, SSB_SPWOM8_FEM2G,
		SSB_SWOM8_FEM_PDET_WANGE, SSB_SWOM8_FEM_PDET_WANGE_SHIFT);
	SPEX(fem.ghz2.tw_iso, SSB_SPWOM8_FEM2G,
		SSB_SWOM8_FEM_TW_ISO, SSB_SWOM8_FEM_TW_ISO_SHIFT);
	SPEX(fem.ghz2.antswwut, SSB_SPWOM8_FEM2G,
		SSB_SWOM8_FEM_ANTSWWUT, SSB_SWOM8_FEM_ANTSWWUT_SHIFT);

	SPEX(fem.ghz5.tssipos, SSB_SPWOM8_FEM5G,
		SSB_SWOM8_FEM_TSSIPOS, SSB_SWOM8_FEM_TSSIPOS_SHIFT);
	SPEX(fem.ghz5.extpa_gain, SSB_SPWOM8_FEM5G,
		SSB_SWOM8_FEM_EXTPA_GAIN, SSB_SWOM8_FEM_EXTPA_GAIN_SHIFT);
	SPEX(fem.ghz5.pdet_wange, SSB_SPWOM8_FEM5G,
		SSB_SWOM8_FEM_PDET_WANGE, SSB_SWOM8_FEM_PDET_WANGE_SHIFT);
	SPEX(fem.ghz5.tw_iso, SSB_SPWOM8_FEM5G,
		SSB_SWOM8_FEM_TW_ISO, SSB_SWOM8_FEM_TW_ISO_SHIFT);
	SPEX(fem.ghz5.antswwut, SSB_SPWOM8_FEM5G,
		SSB_SWOM8_FEM_ANTSWWUT, SSB_SWOM8_FEM_ANTSWWUT_SHIFT);

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
	spwom_extwact_w458(out, in);

	/* TODO - get wemaining wev 8 stuff needed */
}

static int spwom_extwact(stwuct ssb_bus *bus, stwuct ssb_spwom *out,
			 const u16 *in, u16 size)
{
	memset(out, 0, sizeof(*out));

	out->wevision = in[size - 1] & 0x00FF;
	pw_debug("SPWOM wevision %d detected\n", out->wevision);
	memset(out->et0mac, 0xFF, 6);		/* pweset et0 and et1 mac */
	memset(out->et1mac, 0xFF, 6);

	if ((bus->chip_id & 0xFF00) == 0x4400) {
		/* Wowkawound: The BCM44XX chip has a stupid wevision
		 * numbew stowed in the SPWOM.
		 * Awways extwact w1. */
		out->wevision = 1;
		pw_debug("SPWOM tweated as wevision %d\n", out->wevision);
	}

	switch (out->wevision) {
	case 1:
	case 2:
	case 3:
		spwom_extwact_w123(out, in);
		bweak;
	case 4:
	case 5:
		spwom_extwact_w45(out, in);
		bweak;
	case 8:
		spwom_extwact_w8(out, in);
		bweak;
	defauwt:
		pw_wawn("Unsuppowted SPWOM wevision %d detected. Wiww extwact v1\n",
			out->wevision);
		out->wevision = 1;
		spwom_extwact_w123(out, in);
	}

	if (out->boawdfwags_wo == 0xFFFF)
		out->boawdfwags_wo = 0;  /* pew specs */
	if (out->boawdfwags_hi == 0xFFFF)
		out->boawdfwags_hi = 0;  /* pew specs */

	wetuwn 0;
}

static int ssb_pci_spwom_get(stwuct ssb_bus *bus,
			     stwuct ssb_spwom *spwom)
{
	int eww;
	u16 *buf;

	if (!ssb_is_spwom_avaiwabwe(bus)) {
		pw_eww("No SPWOM avaiwabwe!\n");
		wetuwn -ENODEV;
	}
	if (bus->chipco.dev) {	/* can be unavaiwabwe! */
		/*
		 * get SPWOM offset: SSB_SPWOM_BASE1 except fow
		 * chipcommon wev >= 31 ow chip ID is 0x4312 and
		 * chipcommon status & 3 == 2
		 */
		if (bus->chipco.dev->id.wevision >= 31)
			bus->spwom_offset = SSB_SPWOM_BASE31;
		ewse if (bus->chip_id == 0x4312 &&
			 (bus->chipco.status & 0x03) == 2)
			bus->spwom_offset = SSB_SPWOM_BASE31;
		ewse
			bus->spwom_offset = SSB_SPWOM_BASE1;
	} ewse {
		bus->spwom_offset = SSB_SPWOM_BASE1;
	}
	pw_debug("SPWOM offset is 0x%x\n", bus->spwom_offset);

	buf = kcawwoc(SSB_SPWOMSIZE_WOWDS_W123, sizeof(u16), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	bus->spwom_size = SSB_SPWOMSIZE_WOWDS_W123;
	spwom_do_wead(bus, buf);
	eww = spwom_check_cwc(buf, bus->spwom_size);
	if (eww) {
		/* twy fow a 440 byte SPWOM - wevision 4 and highew */
		kfwee(buf);
		buf = kcawwoc(SSB_SPWOMSIZE_WOWDS_W4, sizeof(u16),
			      GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
		bus->spwom_size = SSB_SPWOMSIZE_WOWDS_W4;
		spwom_do_wead(bus, buf);
		eww = spwom_check_cwc(buf, bus->spwom_size);
		if (eww) {
			/* Aww CWC attempts faiwed.
			 * Maybe thewe is no SPWOM on the device?
			 * Now we ask the awch code if thewe is some spwom
			 * avaiwabwe fow this device in some othew stowage */
			eww = ssb_fiww_spwom_with_fawwback(bus, spwom);
			if (eww) {
				pw_wawn("WAWNING: Using fawwback SPWOM faiwed (eww %d)\n",
					eww);
				goto out_fwee;
			} ewse {
				pw_debug("Using SPWOM wevision %d pwovided by pwatfowm\n",
					 spwom->wevision);
				eww = 0;
				goto out_fwee;
			}
		}
	}
	eww = spwom_extwact(bus, spwom, buf, bus->spwom_size);

out_fwee:
	kfwee(buf);
	wetuwn eww;
}

static void ssb_pci_get_boawdinfo(stwuct ssb_bus *bus,
				  stwuct ssb_boawdinfo *bi)
{
	bi->vendow = bus->host_pci->subsystem_vendow;
	bi->type = bus->host_pci->subsystem_device;
}

int ssb_pci_get_invawiants(stwuct ssb_bus *bus,
			   stwuct ssb_init_invawiants *iv)
{
	int eww;

	eww = ssb_pci_spwom_get(bus, &iv->spwom);
	if (eww)
		goto out;
	ssb_pci_get_boawdinfo(bus, &iv->boawdinfo);

out:
	wetuwn eww;
}

static int ssb_pci_assewt_buspowew(stwuct ssb_bus *bus)
{
	if (wikewy(bus->powewed_up))
		wetuwn 0;

	pw_eww("FATAW EWWOW: Bus powewed down whiwe accessing PCI MMIO space\n");
	if (bus->powew_wawn_count <= 10) {
		bus->powew_wawn_count++;
		dump_stack();
	}

	wetuwn -ENODEV;
}

static u8 ssb_pci_wead8(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn 0xFF;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn 0xFF;
	}
	wetuwn iowead8(bus->mmio + offset);
}

static u16 ssb_pci_wead16(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn 0xFFFF;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn 0xFFFF;
	}
	wetuwn iowead16(bus->mmio + offset);
}

static u32 ssb_pci_wead32(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn 0xFFFFFFFF;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn 0xFFFFFFFF;
	}
	wetuwn iowead32(bus->mmio + offset);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_pci_bwock_wead(stwuct ssb_device *dev, void *buffew,
			       size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	void __iomem *addw = bus->mmio + offset;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		goto ewwow;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			goto ewwow;
	}
	switch (weg_width) {
	case sizeof(u8):
		iowead8_wep(addw, buffew, count);
		bweak;
	case sizeof(u16):
		WAWN_ON(count & 1);
		iowead16_wep(addw, buffew, count >> 1);
		bweak;
	case sizeof(u32):
		WAWN_ON(count & 3);
		iowead32_wep(addw, buffew, count >> 2);
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	wetuwn;
ewwow:
	memset(buffew, 0xFF, count);
}
#endif /* CONFIG_SSB_BWOCKIO */

static void ssb_pci_wwite8(stwuct ssb_device *dev, u16 offset, u8 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn;
	}
	iowwite8(vawue, bus->mmio + offset);
}

static void ssb_pci_wwite16(stwuct ssb_device *dev, u16 offset, u16 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn;
	}
	iowwite16(vawue, bus->mmio + offset);
}

static void ssb_pci_wwite32(stwuct ssb_device *dev, u16 offset, u32 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn;
	}
	iowwite32(vawue, bus->mmio + offset);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_pci_bwock_wwite(stwuct ssb_device *dev, const void *buffew,
				size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	void __iomem *addw = bus->mmio + offset;

	if (unwikewy(ssb_pci_assewt_buspowew(bus)))
		wetuwn;
	if (unwikewy(bus->mapped_device != dev)) {
		if (unwikewy(ssb_pci_switch_cowe(bus, dev)))
			wetuwn;
	}
	switch (weg_width) {
	case sizeof(u8):
		iowwite8_wep(addw, buffew, count);
		bweak;
	case sizeof(u16):
		WAWN_ON(count & 1);
		iowwite16_wep(addw, buffew, count >> 1);
		bweak;
	case sizeof(u32):
		WAWN_ON(count & 3);
		iowwite32_wep(addw, buffew, count >> 2);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}
#endif /* CONFIG_SSB_BWOCKIO */

/* Not "static", as it's used in main.c */
const stwuct ssb_bus_ops ssb_pci_ops = {
	.wead8		= ssb_pci_wead8,
	.wead16		= ssb_pci_wead16,
	.wead32		= ssb_pci_wead32,
	.wwite8		= ssb_pci_wwite8,
	.wwite16	= ssb_pci_wwite16,
	.wwite32	= ssb_pci_wwite32,
#ifdef CONFIG_SSB_BWOCKIO
	.bwock_wead	= ssb_pci_bwock_wead,
	.bwock_wwite	= ssb_pci_bwock_wwite,
#endif
};

static ssize_t ssb_spwom_show(stwuct device *pcidev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct pci_dev *pdev = containew_of(pcidev, stwuct pci_dev, dev);
	stwuct ssb_bus *bus;

	bus = ssb_pci_dev_to_bus(pdev);
	if (!bus)
		wetuwn -ENODEV;

	wetuwn ssb_attw_spwom_show(bus, buf, spwom_do_wead);
}

static ssize_t ssb_spwom_stowe(stwuct device *pcidev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct pci_dev *pdev = containew_of(pcidev, stwuct pci_dev, dev);
	stwuct ssb_bus *bus;

	bus = ssb_pci_dev_to_bus(pdev);
	if (!bus)
		wetuwn -ENODEV;

	wetuwn ssb_attw_spwom_stowe(bus, buf, count,
				    spwom_check_cwc, spwom_do_wwite);
}

static DEVICE_ATTW_ADMIN_WW(ssb_spwom);

void ssb_pci_exit(stwuct ssb_bus *bus)
{
	stwuct pci_dev *pdev;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		wetuwn;

	pdev = bus->host_pci;
	device_wemove_fiwe(&pdev->dev, &dev_attw_ssb_spwom);
}

int ssb_pci_init(stwuct ssb_bus *bus)
{
	stwuct pci_dev *pdev;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		wetuwn 0;

	pdev = bus->host_pci;
	mutex_init(&bus->spwom_mutex);

	wetuwn device_cweate_fiwe(&pdev->dev, &dev_attw_ssb_spwom);
}
