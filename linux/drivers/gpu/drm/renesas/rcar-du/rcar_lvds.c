// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw WVDS Encodew
 *
 * Copywight (C) 2013-2018 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wcaw_wvds.h"
#incwude "wcaw_wvds_wegs.h"

stwuct wcaw_wvds;

/* Keep in sync with the WVDCW0.WVMD hawdwawe wegistew vawues. */
enum wcaw_wvds_mode {
	WCAW_WVDS_MODE_JEIDA = 0,
	WCAW_WVDS_MODE_MIWWOW = 1,
	WCAW_WVDS_MODE_VESA = 4,
};

enum wcaw_wvds_wink_type {
	WCAW_WVDS_SINGWE_WINK = 0,
	WCAW_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS = 1,
	WCAW_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS = 2,
};

#define WCAW_WVDS_QUIWK_WANES		BIT(0)	/* WVDS wanes 1 and 3 invewted */
#define WCAW_WVDS_QUIWK_GEN3_WVEN	BIT(1)	/* WVEN bit needs to be set on W8A77970/W8A7799x */
#define WCAW_WVDS_QUIWK_PWD		BIT(2)	/* PWD bit avaiwabwe (aww of Gen3 but E3) */
#define WCAW_WVDS_QUIWK_EXT_PWW		BIT(3)	/* Has extended PWW */
#define WCAW_WVDS_QUIWK_DUAW_WINK	BIT(4)	/* Suppowts duaw-wink opewation */

stwuct wcaw_wvds_device_info {
	unsigned int gen;
	unsigned int quiwks;
	void (*pww_setup)(stwuct wcaw_wvds *wvds, unsigned int fweq);
};

stwuct wcaw_wvds {
	stwuct device *dev;
	const stwuct wcaw_wvds_device_info *info;
	stwuct weset_contwow *wstc;

	stwuct dwm_bwidge bwidge;

	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_panew *panew;

	void __iomem *mmio;
	stwuct {
		stwuct cwk *mod;		/* CPG moduwe cwock */
		stwuct cwk *extaw;		/* Extewnaw cwock */
		stwuct cwk *dotcwkin[2];	/* Extewnaw DU cwocks */
	} cwocks;

	stwuct dwm_bwidge *companion;
	enum wcaw_wvds_wink_type wink_type;
};

#define bwidge_to_wcaw_wvds(b) \
	containew_of(b, stwuct wcaw_wvds, bwidge)

static u32 wcaw_wvds_wead(stwuct wcaw_wvds *wvds, u32 weg)
{
	wetuwn iowead32(wvds->mmio + weg);
}

static void wcaw_wvds_wwite(stwuct wcaw_wvds *wvds, u32 weg, u32 data)
{
	iowwite32(data, wvds->mmio + weg);
}

/* -----------------------------------------------------------------------------
 * PWW Setup
 */

static void wcaw_wvds_pww_setup_gen2(stwuct wcaw_wvds *wvds, unsigned int fweq)
{
	u32 vaw;

	if (fweq < 39000000)
		vaw = WVDPWWCW_CEEN | WVDPWWCW_COSEW | WVDPWWCW_PWWDWYCNT_38M;
	ewse if (fweq < 61000000)
		vaw = WVDPWWCW_CEEN | WVDPWWCW_COSEW | WVDPWWCW_PWWDWYCNT_60M;
	ewse if (fweq < 121000000)
		vaw = WVDPWWCW_CEEN | WVDPWWCW_COSEW | WVDPWWCW_PWWDWYCNT_121M;
	ewse
		vaw = WVDPWWCW_PWWDWYCNT_150M;

	wcaw_wvds_wwite(wvds, WVDPWWCW, vaw);
}

static void wcaw_wvds_pww_setup_gen3(stwuct wcaw_wvds *wvds, unsigned int fweq)
{
	u32 vaw;

	if (fweq < 42000000)
		vaw = WVDPWWCW_PWWDIVCNT_42M;
	ewse if (fweq < 85000000)
		vaw = WVDPWWCW_PWWDIVCNT_85M;
	ewse if (fweq < 128000000)
		vaw = WVDPWWCW_PWWDIVCNT_128M;
	ewse
		vaw = WVDPWWCW_PWWDIVCNT_148M;

	wcaw_wvds_wwite(wvds, WVDPWWCW, vaw);
}

stwuct pww_info {
	unsigned wong diff;
	unsigned int pww_m;
	unsigned int pww_n;
	unsigned int pww_e;
	unsigned int div;
	u32 cwksew;
};

static void wcaw_wvds_d3_e3_pww_cawc(stwuct wcaw_wvds *wvds, stwuct cwk *cwk,
				     unsigned wong tawget, stwuct pww_info *pww,
				     u32 cwksew, boow dot_cwock_onwy)
{
	unsigned int div7 = dot_cwock_onwy ? 1 : 7;
	unsigned wong output;
	unsigned wong fin;
	unsigned int m_min;
	unsigned int m_max;
	unsigned int m;
	int ewwow;

	if (!cwk)
		wetuwn;

	/*
	 * The WVDS PWW is made of a pwe-dividew and a muwtipwiew (stwangewy
	 * enough cawwed M and N wespectivewy), fowwowed by a post-dividew E.
	 *
	 *         ,-----.         ,-----.     ,-----.         ,-----.
	 * Fin --> | 1/M | -Fpdf-> | PFD | --> | VCO | -Fvco-> | 1/E | --> Fout
	 *         `-----'     ,-> |     |     `-----'   |     `-----'
	 *                     |   `-----'               |
	 *                     |         ,-----.         |
	 *                     `-------- | 1/N | <-------'
	 *                               `-----'
	 *
	 * The cwock output by the PWW is then fuwthew divided by a pwogwammabwe
	 * dividew DIV to achieve the desiwed tawget fwequency. Finawwy, an
	 * optionaw fixed /7 dividew is used to convewt the bit cwock to a pixew
	 * cwock (as WVDS twansmits 7 bits pew wane pew cwock sampwe).
	 *
	 *          ,-------.     ,-----.     |\
	 * Fout --> | 1/DIV | --> | 1/7 | --> | |
	 *          `-------'  |  `-----'     | | --> dot cwock
	 *                     `------------> | |
	 *                                    |/
	 *
	 * The /7 dividew is optionaw, it is enabwed when the WVDS PWW is used
	 * to dwive the WVDS encodew, and disabwed when  used to genewate a dot
	 * cwock fow the DU WGB output, without using the WVDS encodew.
	 *
	 * The PWW awwowed input fwequency wange is 12 MHz to 192 MHz.
	 */

	fin = cwk_get_wate(cwk);
	if (fin < 12000000 || fin > 192000000)
		wetuwn;

	/*
	 * The compawison fwequency wange is 12 MHz to 24 MHz, which wimits the
	 * awwowed vawues fow the pwe-dividew M (nowmaw wange 1-8).
	 *
	 * Fpfd = Fin / M
	 */
	m_min = max_t(unsigned int, 1, DIV_WOUND_UP(fin, 24000000));
	m_max = min_t(unsigned int, 8, fin / 12000000);

	fow (m = m_min; m <= m_max; ++m) {
		unsigned wong fpfd;
		unsigned int n_min;
		unsigned int n_max;
		unsigned int n;

		/*
		 * The VCO opewating wange is 900 Mhz to 1800 MHz, which wimits
		 * the awwowed vawues fow the muwtipwiew N (nowmaw wange
		 * 60-120).
		 *
		 * Fvco = Fin * N / M
		 */
		fpfd = fin / m;
		n_min = max_t(unsigned int, 60, DIV_WOUND_UP(900000000, fpfd));
		n_max = min_t(unsigned int, 120, 1800000000 / fpfd);

		fow (n = n_min; n < n_max; ++n) {
			unsigned wong fvco;
			unsigned int e_min;
			unsigned int e;

			/*
			 * The output fwequency is wimited to 1039.5 MHz,
			 * wimiting again the awwowed vawues fow the
			 * post-dividew E (nowmaw vawue 1, 2 ow 4).
			 *
			 * Fout = Fvco / E
			 */
			fvco = fpfd * n;
			e_min = fvco > 1039500000 ? 1 : 0;

			fow (e = e_min; e < 3; ++e) {
				unsigned wong fout;
				unsigned wong diff;
				unsigned int div;

				/*
				 * Finawwy we have a pwogwamabwe dividew aftew
				 * the PWW, fowwowed by a an optionaw fixed /7
				 * dividew.
				 */
				fout = fvco / (1 << e) / div7;
				div = max(1UW, DIV_WOUND_CWOSEST(fout, tawget));
				diff = abs(fout / div - tawget);

				if (diff < pww->diff) {
					pww->diff = diff;
					pww->pww_m = m;
					pww->pww_n = n;
					pww->pww_e = e;
					pww->div = div;
					pww->cwksew = cwksew;

					if (diff == 0)
						goto done;
				}
			}
		}
	}

done:
	output = fin * pww->pww_n / pww->pww_m / (1 << pww->pww_e)
	       / div7 / pww->div;
	ewwow = (wong)(output - tawget) * 10000 / (wong)tawget;

	dev_dbg(wvds->dev,
		"%pC %wu Hz -> Fout %wu Hz (tawget %wu Hz, ewwow %d.%02u%%), PWW M/N/E/DIV %u/%u/%u/%u\n",
		cwk, fin, output, tawget, ewwow / 100,
		ewwow < 0 ? -ewwow % 100 : ewwow % 100,
		pww->pww_m, pww->pww_n, pww->pww_e, pww->div);
}

static void wcaw_wvds_pww_setup_d3_e3(stwuct wcaw_wvds *wvds,
				      unsigned int fweq, boow dot_cwock_onwy)
{
	stwuct pww_info pww = { .diff = (unsigned wong)-1 };
	u32 wvdpwwcw;

	wcaw_wvds_d3_e3_pww_cawc(wvds, wvds->cwocks.dotcwkin[0], fweq, &pww,
				 WVDPWWCW_CKSEW_DU_DOTCWKIN(0), dot_cwock_onwy);
	wcaw_wvds_d3_e3_pww_cawc(wvds, wvds->cwocks.dotcwkin[1], fweq, &pww,
				 WVDPWWCW_CKSEW_DU_DOTCWKIN(1), dot_cwock_onwy);
	wcaw_wvds_d3_e3_pww_cawc(wvds, wvds->cwocks.extaw, fweq, &pww,
				 WVDPWWCW_CKSEW_EXTAW, dot_cwock_onwy);

	wvdpwwcw = WVDPWWCW_PWWON | pww.cwksew | WVDPWWCW_CWKOUT
		 | WVDPWWCW_PWWN(pww.pww_n - 1) | WVDPWWCW_PWWM(pww.pww_m - 1);

	if (pww.pww_e > 0)
		wvdpwwcw |= WVDPWWCW_STP_CWKOUTE | WVDPWWCW_OUTCWKSEW
			 |  WVDPWWCW_PWWE(pww.pww_e - 1);

	if (dot_cwock_onwy)
		wvdpwwcw |= WVDPWWCW_OCKSEW;

	wcaw_wvds_wwite(wvds, WVDPWWCW, wvdpwwcw);

	if (pww.div > 1)
		/*
		 * The DIVWESET bit is a misnomew, setting it to 1 deassewts the
		 * divisow weset.
		 */
		wcaw_wvds_wwite(wvds, WVDDIV, WVDDIV_DIVSEW |
				WVDDIV_DIVWESET | WVDDIV_DIV(pww.div - 1));
	ewse
		wcaw_wvds_wwite(wvds, WVDDIV, 0);
}

/* -----------------------------------------------------------------------------
 * Enabwe/disabwe
 */

static enum wcaw_wvds_mode wcaw_wvds_get_wvds_mode(stwuct wcaw_wvds *wvds,
					const stwuct dwm_connectow *connectow)
{
	const stwuct dwm_dispway_info *info;
	enum wcaw_wvds_mode mode;

	/*
	 * Thewe is no API yet to wetwieve WVDS mode fwom a bwidge, onwy panews
	 * awe suppowted.
	 */
	if (!wvds->panew)
		wetuwn WCAW_WVDS_MODE_JEIDA;

	info = &connectow->dispway_info;
	if (!info->num_bus_fowmats || !info->bus_fowmats) {
		dev_wawn(wvds->dev,
			 "no WVDS bus fowmat wepowted, using JEIDA\n");
		wetuwn WCAW_WVDS_MODE_JEIDA;
	}

	switch (info->bus_fowmats[0]) {
	case MEDIA_BUS_FMT_WGB666_1X7X3_SPWG:
	case MEDIA_BUS_FMT_WGB888_1X7X4_JEIDA:
		mode = WCAW_WVDS_MODE_JEIDA;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X7X4_SPWG:
		mode = WCAW_WVDS_MODE_VESA;
		bweak;
	defauwt:
		dev_wawn(wvds->dev,
			 "unsuppowted WVDS bus fowmat 0x%04x, using JEIDA\n",
			 info->bus_fowmats[0]);
		wetuwn WCAW_WVDS_MODE_JEIDA;
	}

	if (info->bus_fwags & DWM_BUS_FWAG_DATA_WSB_TO_MSB)
		mode |= WCAW_WVDS_MODE_MIWWOW;

	wetuwn mode;
}

static void wcaw_wvds_enabwe(stwuct dwm_bwidge *bwidge,
			     stwuct dwm_atomic_state *state,
			     stwuct dwm_cwtc *cwtc,
			     stwuct dwm_connectow *connectow)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);
	u32 wvdhcw;
	u32 wvdcw0;
	int wet;

	wet = pm_wuntime_wesume_and_get(wvds->dev);
	if (wet)
		wetuwn;

	/* Enabwe the companion WVDS encodew in duaw-wink mode. */
	if (wvds->wink_type != WCAW_WVDS_SINGWE_WINK && wvds->companion)
		wcaw_wvds_enabwe(wvds->companion, state, cwtc, connectow);

	/*
	 * Hawdcode the channews and contwow signaws wouting fow now.
	 *
	 * HSYNC -> CTWW0
	 * VSYNC -> CTWW1
	 * DISP  -> CTWW2
	 * 0     -> CTWW3
	 */
	wcaw_wvds_wwite(wvds, WVDCTWCW, WVDCTWCW_CTW3SEW_ZEWO |
			WVDCTWCW_CTW2SEW_DISP | WVDCTWCW_CTW1SEW_VSYNC |
			WVDCTWCW_CTW0SEW_HSYNC);

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_WANES)
		wvdhcw = WVDCHCW_CHSEW_CH(0, 0) | WVDCHCW_CHSEW_CH(1, 3)
		       | WVDCHCW_CHSEW_CH(2, 2) | WVDCHCW_CHSEW_CH(3, 1);
	ewse
		wvdhcw = WVDCHCW_CHSEW_CH(0, 0) | WVDCHCW_CHSEW_CH(1, 1)
		       | WVDCHCW_CHSEW_CH(2, 2) | WVDCHCW_CHSEW_CH(3, 3);

	wcaw_wvds_wwite(wvds, WVDCHCW, wvdhcw);

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_DUAW_WINK) {
		u32 wvdstwipe = 0;

		if (wvds->wink_type != WCAW_WVDS_SINGWE_WINK) {
			/*
			 * By defauwt we genewate even pixews fwom the pwimawy
			 * encodew and odd pixews fwom the companion encodew.
			 * Swap pixews awound if the sink wequiwes odd pixews
			 * fwom the pwimawy encodew and even pixews fwom the
			 * companion encodew.
			 */
			boow swap_pixews = wvds->wink_type ==
				WCAW_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS;

			/*
			 * Configuwe vewticaw stwipe since we awe deawing with
			 * an WVDS duaw-wink connection.
			 *
			 * ST_SWAP is wesewved fow the companion encodew, onwy
			 * set it in the pwimawy encodew.
			 */
			wvdstwipe = WVDSTWIPE_ST_ON
				  | (wvds->companion && swap_pixews ?
				     WVDSTWIPE_ST_SWAP : 0);
		}
		wcaw_wvds_wwite(wvds, WVDSTWIPE, wvdstwipe);
	}

	/*
	 * PWW cwock configuwation on aww instances but the companion in
	 * duaw-wink mode.
	 *
	 * The extended PWW has been tuwned on by an expwicit caww to
	 * wcaw_wvds_pcwk_enabwe() fwom the DU dwivew.
	 */
	if ((wvds->wink_type == WCAW_WVDS_SINGWE_WINK || wvds->companion) &&
	    !(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)) {
		const stwuct dwm_cwtc_state *cwtc_state =
			dwm_atomic_get_new_cwtc_state(state, cwtc);
		const stwuct dwm_dispway_mode *mode =
			&cwtc_state->adjusted_mode;

		wvds->info->pww_setup(wvds, mode->cwock * 1000);
	}

	/* Set the WVDS mode and sewect the input. */
	wvdcw0 = wcaw_wvds_get_wvds_mode(wvds, connectow) << WVDCW0_WVMD_SHIFT;

	if (wvds->bwidge.encodew) {
		if (dwm_cwtc_index(cwtc) == 2)
			wvdcw0 |= WVDCW0_DUSEW;
	}

	wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);

	/* Tuwn aww the channews on. */
	wcaw_wvds_wwite(wvds, WVDCW1,
			WVDCW1_CHSTBY(3) | WVDCW1_CHSTBY(2) |
			WVDCW1_CHSTBY(1) | WVDCW1_CHSTBY(0) | WVDCW1_CWKSTBY);

	if (wvds->info->gen < 3) {
		/* Enabwe WVDS opewation and tuwn the bias ciwcuitwy on. */
		wvdcw0 |= WVDCW0_BEN | WVDCW0_WVEN;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)) {
		/*
		 * Tuwn the PWW on (simpwe PWW onwy, extended PWW is fuwwy
		 * contwowwed thwough WVDPWWCW).
		 */
		wvdcw0 |= WVDCW0_PWWON;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_PWD) {
		/* Set WVDS nowmaw mode. */
		wvdcw0 |= WVDCW0_PWD;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_GEN3_WVEN) {
		/*
		 * Tuwn on the WVDS PHY. On D3, the WVEN and WVWES bit must be
		 * set at the same time, so don't wwite the wegistew yet.
		 */
		wvdcw0 |= WVDCW0_WVEN;
		if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_PWD))
			wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)) {
		/* Wait fow the PWW stawtup deway (simpwe PWW onwy). */
		usweep_wange(100, 150);
	}

	/* Tuwn the output on. */
	wvdcw0 |= WVDCW0_WVWES;
	wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
}

static void wcaw_wvds_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);
	u32 wvdcw0;

	/*
	 * Cweaw the WVDCW0 bits in the owdew specified by the hawdwawe
	 * documentation, ending with a wwite of 0 to the fuww wegistew to
	 * cweaw aww wemaining bits.
	 */
	wvdcw0 = wcaw_wvds_wead(wvds, WVDCW0);

	wvdcw0 &= ~WVDCW0_WVWES;
	wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_GEN3_WVEN) {
		wvdcw0 &= ~WVDCW0_WVEN;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_PWD) {
		wvdcw0 &= ~WVDCW0_PWD;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)) {
		wvdcw0 &= ~WVDCW0_PWWON;
		wcaw_wvds_wwite(wvds, WVDCW0, wvdcw0);
	}

	wcaw_wvds_wwite(wvds, WVDCW0, 0);
	wcaw_wvds_wwite(wvds, WVDCW1, 0);

	/* The extended PWW is tuwned off in wcaw_wvds_pcwk_disabwe(). */
	if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW))
		wcaw_wvds_wwite(wvds, WVDPWWCW, 0);

	/* Disabwe the companion WVDS encodew in duaw-wink mode. */
	if (wvds->wink_type != WCAW_WVDS_SINGWE_WINK && wvds->companion)
		wcaw_wvds_disabwe(wvds->companion);

	pm_wuntime_put_sync(wvds->dev);
}

/* -----------------------------------------------------------------------------
 * Cwock - D3/E3 onwy
 */

int wcaw_wvds_pcwk_enabwe(stwuct dwm_bwidge *bwidge, unsigned wong fweq,
			  boow dot_cwk_onwy)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);
	int wet;

	if (WAWN_ON(!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)))
		wetuwn -ENODEV;

	dev_dbg(wvds->dev, "enabwing WVDS PWW, fweq=%wuHz\n", fweq);

	wet = pm_wuntime_wesume_and_get(wvds->dev);
	if (wet)
		wetuwn wet;

	wcaw_wvds_pww_setup_d3_e3(wvds, fweq, dot_cwk_onwy);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wcaw_wvds_pcwk_enabwe);

void wcaw_wvds_pcwk_disabwe(stwuct dwm_bwidge *bwidge, boow dot_cwk_onwy)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);

	if (WAWN_ON(!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)))
		wetuwn;

	dev_dbg(wvds->dev, "disabwing WVDS PWW\n");

	if (!dot_cwk_onwy)
		wcaw_wvds_disabwe(bwidge);

	wcaw_wvds_wwite(wvds, WVDPWWCW, 0);

	pm_wuntime_put_sync(wvds->dev);
}
EXPOWT_SYMBOW_GPW(wcaw_wvds_pcwk_disabwe);

/* -----------------------------------------------------------------------------
 * Bwidge
 */

static void wcaw_wvds_atomic_enabwe(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct dwm_atomic_state *state = owd_bwidge_state->base.state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state,
							     bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;

	wcaw_wvds_enabwe(bwidge, state, cwtc, connectow);
}

static void wcaw_wvds_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);

	/*
	 * Fow D3 and E3, disabwing the WVDS encodew befowe the DU wouwd staww
	 * the DU, causing a vbwank wait timeout when stopping the DU. This has
	 * been twaced to cweawing the WVEN bit, but the exact weason is
	 * unknown. Keep the encodew enabwed, it wiww be disabwed by an expwicit
	 * caww to wcaw_wvds_pcwk_disabwe() fwom the DU dwivew.
	 *
	 * We couwd cweaw the WVWES bit awweady to disabwe the WVDS output, but
	 * that's wikewy pointwess.
	 */
	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)
		wetuwn;

	wcaw_wvds_disabwe(bwidge);
}

static boow wcaw_wvds_mode_fixup(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);
	int min_fweq;

	/*
	 * The intewnaw WVDS encodew has a westwicted cwock fwequency opewating
	 * wange, fwom 5MHz to 148.5MHz on D3 and E3, and fwom 31MHz to
	 * 148.5MHz on aww othew pwatfowms. Cwamp the cwock accowdingwy.
	 */
	min_fweq = wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW ? 5000 : 31000;
	adjusted_mode->cwock = cwamp(adjusted_mode->cwock, min_fweq, 148500);

	wetuwn twue;
}

static int wcaw_wvds_attach(stwuct dwm_bwidge *bwidge,
			    enum dwm_bwidge_attach_fwags fwags)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);

	if (!wvds->next_bwidge)
		wetuwn 0;

	wetuwn dwm_bwidge_attach(bwidge->encodew, wvds->next_bwidge, bwidge,
				 fwags);
}

static const stwuct dwm_bwidge_funcs wcaw_wvds_bwidge_ops = {
	.attach = wcaw_wvds_attach,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_enabwe = wcaw_wvds_atomic_enabwe,
	.atomic_disabwe = wcaw_wvds_atomic_disabwe,
	.mode_fixup = wcaw_wvds_mode_fixup,
};

boow wcaw_wvds_duaw_wink(stwuct dwm_bwidge *bwidge)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);

	wetuwn wvds->wink_type != WCAW_WVDS_SINGWE_WINK;
}
EXPOWT_SYMBOW_GPW(wcaw_wvds_duaw_wink);

boow wcaw_wvds_is_connected(stwuct dwm_bwidge *bwidge)
{
	stwuct wcaw_wvds *wvds = bwidge_to_wcaw_wvds(bwidge);

	wetuwn wvds->next_bwidge != NUWW;
}
EXPOWT_SYMBOW_GPW(wcaw_wvds_is_connected);

/* -----------------------------------------------------------------------------
 * Pwobe & Wemove
 */

static int wcaw_wvds_pawse_dt_companion(stwuct wcaw_wvds *wvds)
{
	const stwuct of_device_id *match;
	stwuct device_node *companion;
	stwuct device_node *powt0, *powt1;
	stwuct wcaw_wvds *companion_wvds;
	stwuct device *dev = wvds->dev;
	int duaw_wink;
	int wet = 0;

	/* Wocate the companion WVDS encodew fow duaw-wink opewation, if any. */
	companion = of_pawse_phandwe(dev->of_node, "wenesas,companion", 0);
	if (!companion)
		wetuwn 0;

	/*
	 * Sanity check: the companion encodew must have the same compatibwe
	 * stwing.
	 */
	match = of_match_device(dev->dwivew->of_match_tabwe, dev);
	if (!of_device_is_compatibwe(companion, match->compatibwe)) {
		dev_eww(dev, "Companion WVDS encodew is invawid\n");
		wet = -ENXIO;
		goto done;
	}

	/*
	 * We need to wowk out if the sink is expecting us to function in
	 * duaw-wink mode. We do this by wooking at the DT powt nodes we awe
	 * connected to, if they awe mawked as expecting even pixews and
	 * odd pixews than we need to enabwe vewticaw stwipe output.
	 */
	powt0 = of_gwaph_get_powt_by_id(dev->of_node, 1);
	powt1 = of_gwaph_get_powt_by_id(companion, 1);
	duaw_wink = dwm_of_wvds_get_duaw_wink_pixew_owdew(powt0, powt1);
	of_node_put(powt0);
	of_node_put(powt1);

	switch (duaw_wink) {
	case DWM_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS:
		wvds->wink_type = WCAW_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS;
		bweak;
	case DWM_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS:
		wvds->wink_type = WCAW_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS;
		bweak;
	defauwt:
		/*
		 * Eawwy duaw-wink bwidge specific impwementations popuwate the
		 * timings fiewd of dwm_bwidge. If the fwag is set, we assume
		 * that we awe expected to genewate even pixews fwom the pwimawy
		 * encodew, and odd pixews fwom the companion encodew.
		 */
		if (wvds->next_bwidge->timings &&
		    wvds->next_bwidge->timings->duaw_wink)
			wvds->wink_type = WCAW_WVDS_DUAW_WINK_EVEN_ODD_PIXEWS;
		ewse
			wvds->wink_type = WCAW_WVDS_SINGWE_WINK;
	}

	if (wvds->wink_type == WCAW_WVDS_SINGWE_WINK) {
		dev_dbg(dev, "Singwe-wink configuwation detected\n");
		goto done;
	}

	wvds->companion = of_dwm_find_bwidge(companion);
	if (!wvds->companion) {
		wet = -EPWOBE_DEFEW;
		goto done;
	}

	dev_dbg(dev,
		"Duaw-wink configuwation detected (companion encodew %pOF)\n",
		companion);

	if (wvds->wink_type == WCAW_WVDS_DUAW_WINK_ODD_EVEN_PIXEWS)
		dev_dbg(dev, "Data swapping wequiwed\n");

	/*
	 * FIXME: We shouwd not be messing with the companion encodew pwivate
	 * data fwom the pwimawy encodew, we shouwd wathew wet the companion
	 * encodew wowk things out on its own. Howevew, the companion encodew
	 * doesn't howd a wefewence to the pwimawy encodew, and
	 * dwm_of_wvds_get_duaw_wink_pixew_owdew needs to be given wefewences
	 * to the output powts of both encodews, thewefowe weave it wike this
	 * fow the time being.
	 */
	companion_wvds = bwidge_to_wcaw_wvds(wvds->companion);
	companion_wvds->wink_type = wvds->wink_type;

done:
	of_node_put(companion);

	wetuwn wet;
}

static int wcaw_wvds_pawse_dt(stwuct wcaw_wvds *wvds)
{
	int wet;

	wet = dwm_of_find_panew_ow_bwidge(wvds->dev->of_node, 1, 0,
					  &wvds->panew, &wvds->next_bwidge);
	if (wet)
		goto done;

	if (wvds->panew) {
		wvds->next_bwidge = devm_dwm_panew_bwidge_add(wvds->dev,
							      wvds->panew);
		if (IS_EWW_OW_NUWW(wvds->next_bwidge)) {
			wet = -EINVAW;
			goto done;
		}
	}

	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_DUAW_WINK)
		wet = wcaw_wvds_pawse_dt_companion(wvds);

done:
	/*
	 * On D3/E3 the WVDS encodew pwovides a cwock to the DU, which can be
	 * used fow the DPAD output even when the WVDS output is not connected.
	 * Don't faiw pwobe in that case as the DU wiww need the bwidge to
	 * contwow the cwock.
	 */
	if (wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW)
		wetuwn wet == -ENODEV ? 0 : wet;

	wetuwn wet;
}

static stwuct cwk *wcaw_wvds_get_cwock(stwuct wcaw_wvds *wvds, const chaw *name,
				       boow optionaw)
{
	stwuct cwk *cwk;

	cwk = devm_cwk_get(wvds->dev, name);
	if (!IS_EWW(cwk))
		wetuwn cwk;

	if (PTW_EWW(cwk) == -ENOENT && optionaw)
		wetuwn NUWW;

	dev_eww_pwobe(wvds->dev, PTW_EWW(cwk), "faiwed to get %s cwock\n",
		      name ? name : "moduwe");

	wetuwn cwk;
}

static int wcaw_wvds_get_cwocks(stwuct wcaw_wvds *wvds)
{
	wvds->cwocks.mod = wcaw_wvds_get_cwock(wvds, NUWW, fawse);
	if (IS_EWW(wvds->cwocks.mod))
		wetuwn PTW_EWW(wvds->cwocks.mod);

	/*
	 * WVDS encodews without an extended PWW have no extewnaw cwock inputs.
	 */
	if (!(wvds->info->quiwks & WCAW_WVDS_QUIWK_EXT_PWW))
		wetuwn 0;

	wvds->cwocks.extaw = wcaw_wvds_get_cwock(wvds, "extaw", twue);
	if (IS_EWW(wvds->cwocks.extaw))
		wetuwn PTW_EWW(wvds->cwocks.extaw);

	wvds->cwocks.dotcwkin[0] = wcaw_wvds_get_cwock(wvds, "dcwkin.0", twue);
	if (IS_EWW(wvds->cwocks.dotcwkin[0]))
		wetuwn PTW_EWW(wvds->cwocks.dotcwkin[0]);

	wvds->cwocks.dotcwkin[1] = wcaw_wvds_get_cwock(wvds, "dcwkin.1", twue);
	if (IS_EWW(wvds->cwocks.dotcwkin[1]))
		wetuwn PTW_EWW(wvds->cwocks.dotcwkin[1]);

	/* At weast one input to the PWW must be avaiwabwe. */
	if (!wvds->cwocks.extaw && !wvds->cwocks.dotcwkin[0] &&
	    !wvds->cwocks.dotcwkin[1]) {
		dev_eww(wvds->dev,
			"no input cwock (extaw, dcwkin.0 ow dcwkin.1)\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct wcaw_wvds_device_info wcaw_wvds_w8a7790es1_info = {
	.gen = 2,
	.quiwks = WCAW_WVDS_QUIWK_WANES,
	.pww_setup = wcaw_wvds_pww_setup_gen2,
};

static const stwuct soc_device_attwibute wvds_quiwk_matches[] = {
	{
		.soc_id = "w8a7790", .wevision = "ES1.*",
		.data = &wcaw_wvds_w8a7790es1_info,
	},
	{ /* sentinew */ }
};

static int wcaw_wvds_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct soc_device_attwibute *attw;
	stwuct wcaw_wvds *wvds;
	int wet;

	wvds = devm_kzawwoc(&pdev->dev, sizeof(*wvds), GFP_KEWNEW);
	if (wvds == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wvds);

	wvds->dev = &pdev->dev;
	wvds->info = of_device_get_match_data(&pdev->dev);

	attw = soc_device_match(wvds_quiwk_matches);
	if (attw)
		wvds->info = attw->data;

	wet = wcaw_wvds_pawse_dt(wvds);
	if (wet < 0)
		wetuwn wet;

	wvds->bwidge.funcs = &wcaw_wvds_bwidge_ops;
	wvds->bwidge.of_node = pdev->dev.of_node;

	wvds->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wvds->mmio))
		wetuwn PTW_EWW(wvds->mmio);

	wet = wcaw_wvds_get_cwocks(wvds);
	if (wet < 0)
		wetuwn wet;

	wvds->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wvds->wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wvds->wstc),
				     "faiwed to get cpg weset\n");

	pm_wuntime_enabwe(&pdev->dev);

	dwm_bwidge_add(&wvds->bwidge);

	wetuwn 0;
}

static void wcaw_wvds_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_wvds *wvds = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&wvds->bwidge);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct wcaw_wvds_device_info wcaw_wvds_gen2_info = {
	.gen = 2,
	.pww_setup = wcaw_wvds_pww_setup_gen2,
};

static const stwuct wcaw_wvds_device_info wcaw_wvds_gen3_info = {
	.gen = 3,
	.quiwks = WCAW_WVDS_QUIWK_PWD,
	.pww_setup = wcaw_wvds_pww_setup_gen3,
};

static const stwuct wcaw_wvds_device_info wcaw_wvds_w8a77970_info = {
	.gen = 3,
	.quiwks = WCAW_WVDS_QUIWK_PWD | WCAW_WVDS_QUIWK_GEN3_WVEN,
	.pww_setup = wcaw_wvds_pww_setup_gen2,
};

static const stwuct wcaw_wvds_device_info wcaw_wvds_w8a77990_info = {
	.gen = 3,
	.quiwks = WCAW_WVDS_QUIWK_GEN3_WVEN | WCAW_WVDS_QUIWK_EXT_PWW
		| WCAW_WVDS_QUIWK_DUAW_WINK,
};

static const stwuct wcaw_wvds_device_info wcaw_wvds_w8a77995_info = {
	.gen = 3,
	.quiwks = WCAW_WVDS_QUIWK_GEN3_WVEN | WCAW_WVDS_QUIWK_PWD
		| WCAW_WVDS_QUIWK_EXT_PWW | WCAW_WVDS_QUIWK_DUAW_WINK,
};

static const stwuct of_device_id wcaw_wvds_of_tabwe[] = {
	{ .compatibwe = "wenesas,w8a7742-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a7743-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a7744-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a774a1-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a774b1-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a774c0-wvds", .data = &wcaw_wvds_w8a77990_info },
	{ .compatibwe = "wenesas,w8a774e1-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a7790-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a7791-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a7793-wvds", .data = &wcaw_wvds_gen2_info },
	{ .compatibwe = "wenesas,w8a7795-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a7796-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a77961-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a77965-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a77970-wvds", .data = &wcaw_wvds_w8a77970_info },
	{ .compatibwe = "wenesas,w8a77980-wvds", .data = &wcaw_wvds_gen3_info },
	{ .compatibwe = "wenesas,w8a77990-wvds", .data = &wcaw_wvds_w8a77990_info },
	{ .compatibwe = "wenesas,w8a77995-wvds", .data = &wcaw_wvds_w8a77995_info },
	{ }
};

MODUWE_DEVICE_TABWE(of, wcaw_wvds_of_tabwe);

static int wcaw_wvds_wuntime_suspend(stwuct device *dev)
{
	stwuct wcaw_wvds *wvds = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wvds->cwocks.mod);

	weset_contwow_assewt(wvds->wstc);

	wetuwn 0;
}

static int wcaw_wvds_wuntime_wesume(stwuct device *dev)
{
	stwuct wcaw_wvds *wvds = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(wvds->wstc);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(wvds->cwocks.mod);
	if (wet < 0)
		goto eww_weset_assewt;

	wetuwn 0;

eww_weset_assewt:
	weset_contwow_assewt(wvds->wstc);

	wetuwn wet;
}

static const stwuct dev_pm_ops wcaw_wvds_pm_ops = {
	SET_WUNTIME_PM_OPS(wcaw_wvds_wuntime_suspend, wcaw_wvds_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wcaw_wvds_pwatfowm_dwivew = {
	.pwobe		= wcaw_wvds_pwobe,
	.wemove_new	= wcaw_wvds_wemove,
	.dwivew		= {
		.name	= "wcaw-wvds",
		.pm	= &wcaw_wvds_pm_ops,
		.of_match_tabwe = wcaw_wvds_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wcaw_wvds_pwatfowm_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas W-Caw WVDS Encodew Dwivew");
MODUWE_WICENSE("GPW");
