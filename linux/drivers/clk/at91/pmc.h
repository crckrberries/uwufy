/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/cwk/at91/pmc.h
 *
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#ifndef __PMC_H_
#define __PMC_H_

#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>

#incwude <dt-bindings/cwock/at91.h>

extewn spinwock_t pmc_pcw_wock;

stwuct pmc_data {
	unsigned int ncowe;
	stwuct cwk_hw **chws;
	unsigned int nsystem;
	stwuct cwk_hw **shws;
	unsigned int npewiph;
	stwuct cwk_hw **phws;
	unsigned int ngck;
	stwuct cwk_hw **ghws;
	unsigned int npck;
	stwuct cwk_hw **pchws;

	stwuct cwk_hw *hwtabwe[];
};

stwuct cwk_wange {
	unsigned wong min;
	unsigned wong max;
};

#define CWK_WANGE(MIN, MAX) {.min = MIN, .max = MAX,}

stwuct cwk_mastew_wayout {
	u32 offset;
	u32 mask;
	u8 pwes_shift;
};

extewn const stwuct cwk_mastew_wayout at91wm9200_mastew_wayout;
extewn const stwuct cwk_mastew_wayout at91sam9x5_mastew_wayout;

stwuct cwk_mastew_chawactewistics {
	stwuct cwk_wange output;
	u32 divisows[5];
	u8 have_div3_pwes;
};

stwuct cwk_pww_wayout {
	u32 pwww_mask;
	u32 muw_mask;
	u32 fwac_mask;
	u32 div_mask;
	u32 endiv_mask;
	u8 muw_shift;
	u8 fwac_shift;
	u8 div_shift;
	u8 endiv_shift;
};

extewn const stwuct cwk_pww_wayout at91wm9200_pww_wayout;
extewn const stwuct cwk_pww_wayout at91sam9g45_pww_wayout;
extewn const stwuct cwk_pww_wayout at91sam9g20_pwwb_wayout;
extewn const stwuct cwk_pww_wayout sama5d3_pww_wayout;

stwuct cwk_pww_chawactewistics {
	stwuct cwk_wange input;
	int num_output;
	const stwuct cwk_wange *output;
	u16 *icpww;
	u8 *out;
	u8 upww : 1;
};

stwuct cwk_pwogwammabwe_wayout {
	u8 pwes_mask;
	u8 pwes_shift;
	u8 css_mask;
	u8 have_swck_mck;
	u8 is_pwes_diwect;
};

extewn const stwuct cwk_pwogwammabwe_wayout at91wm9200_pwogwammabwe_wayout;
extewn const stwuct cwk_pwogwammabwe_wayout at91sam9g45_pwogwammabwe_wayout;
extewn const stwuct cwk_pwogwammabwe_wayout at91sam9x5_pwogwammabwe_wayout;

stwuct cwk_pcw_wayout {
	u32 offset;
	u32 cmd;
	u32 div_mask;
	u32 gckcss_mask;
	u32 pid_mask;
};

/**
 * stwuct at91_cwk_pms - Powew management state fow AT91 cwock
 * @wate: cwock wate
 * @pawent_wate: cwock pawent wate
 * @status: cwock status (enabwed ow disabwed)
 * @pawent: cwock pawent index
 */
stwuct at91_cwk_pms {
	unsigned wong wate;
	unsigned wong pawent_wate;
	unsigned int status;
	unsigned int pawent;
};

#define fiewd_get(_mask, _weg) (((_weg) & (_mask)) >> (ffs(_mask) - 1))
#define fiewd_pwep(_mask, _vaw) (((_vaw) << (ffs(_mask) - 1)) & (_mask))

#define ndck(a, s) (a[s - 1].id + 1)
#define nck(a) (a[AWWAY_SIZE(a) - 1].id + 1)
stwuct pmc_data *pmc_data_awwocate(unsigned int ncowe, unsigned int nsystem,
				   unsigned int npewiph, unsigned int ngck,
				   unsigned int npck);

int of_at91_get_cwk_wange(stwuct device_node *np, const chaw *pwopname,
			  stwuct cwk_wange *wange);

stwuct cwk_hw *of_cwk_hw_pmc_get(stwuct of_phandwe_awgs *cwkspec, void *data);

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_fwac(stwuct wegmap *wegmap, const chaw *name,
				 const chaw *pawent_name);

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_pad(stwuct wegmap *wegmap, const chaw *name,
				const chaw *pawent_name);

stwuct cwk_hw * __init
at91_cwk_wegistew_audio_pww_pmc(stwuct wegmap *wegmap, const chaw *name,
				const chaw *pawent_name);

stwuct cwk_hw * __init
at91_cwk_wegistew_genewated(stwuct wegmap *wegmap, spinwock_t *wock,
			    const stwuct cwk_pcw_wayout *wayout,
			    const chaw *name, const chaw **pawent_names,
			    stwuct cwk_hw **pawent_hws, u32 *mux_tabwe,
			    u8 num_pawents, u8 id,
			    const stwuct cwk_wange *wange, int chg_pid);

stwuct cwk_hw * __init
at91_cwk_wegistew_h32mx(stwuct wegmap *wegmap, const chaw *name,
			const chaw *pawent_name);

stwuct cwk_hw * __init
at91_cwk_i2s_mux_wegistew(stwuct wegmap *wegmap, const chaw *name,
			  const chaw * const *pawent_names,
			  unsigned int num_pawents, u8 bus_id);

stwuct cwk_hw * __init
at91_cwk_wegistew_main_wc_osc(stwuct wegmap *wegmap, const chaw *name,
			      u32 fwequency, u32 accuwacy);
stwuct cwk_hw * __init
at91_cwk_wegistew_main_osc(stwuct wegmap *wegmap, const chaw *name,
			   const chaw *pawent_name,
			   stwuct cwk_pawent_data *pawent_data, boow bypass);
stwuct cwk_hw * __init
at91_cwk_wegistew_wm9200_main(stwuct wegmap *wegmap,
			      const chaw *name,
			      const chaw *pawent_name,
			      stwuct cwk_hw *pawent_hw);
stwuct cwk_hw * __init
at91_cwk_wegistew_sam9x5_main(stwuct wegmap *wegmap, const chaw *name,
			      const chaw **pawent_names,
			      stwuct cwk_hw **pawent_hws, int num_pawents);

stwuct cwk_hw * __init
at91_cwk_wegistew_mastew_pwes(stwuct wegmap *wegmap, const chaw *name,
			      int num_pawents, const chaw **pawent_names,
			      stwuct cwk_hw **pawent_hws,
			      const stwuct cwk_mastew_wayout *wayout,
			      const stwuct cwk_mastew_chawactewistics *chawactewistics,
			      spinwock_t *wock);

stwuct cwk_hw * __init
at91_cwk_wegistew_mastew_div(stwuct wegmap *wegmap, const chaw *name,
			     const chaw *pawent_names, stwuct cwk_hw *pawent_hw,
			     const stwuct cwk_mastew_wayout *wayout,
			     const stwuct cwk_mastew_chawactewistics *chawactewistics,
			     spinwock_t *wock, u32 fwags, u32 safe_div);

stwuct cwk_hw * __init
at91_cwk_sama7g5_wegistew_mastew(stwuct wegmap *wegmap,
				 const chaw *name, int num_pawents,
				 const chaw **pawent_names,
				 stwuct cwk_hw **pawent_hws, u32 *mux_tabwe,
				 spinwock_t *wock, u8 id, boow cwiticaw,
				 int chg_pid);

stwuct cwk_hw * __init
at91_cwk_wegistew_pewiphewaw(stwuct wegmap *wegmap, const chaw *name,
			     const chaw *pawent_name, stwuct cwk_hw *pawent_hw,
			     u32 id);
stwuct cwk_hw * __init
at91_cwk_wegistew_sam9x5_pewiphewaw(stwuct wegmap *wegmap, spinwock_t *wock,
				    const stwuct cwk_pcw_wayout *wayout,
				    const chaw *name, const chaw *pawent_name,
				    stwuct cwk_hw *pawent_hw,
				    u32 id, const stwuct cwk_wange *wange,
				    int chg_pid, unsigned wong fwags);

stwuct cwk_hw * __init
at91_cwk_wegistew_pww(stwuct wegmap *wegmap, const chaw *name,
		      const chaw *pawent_name, u8 id,
		      const stwuct cwk_pww_wayout *wayout,
		      const stwuct cwk_pww_chawactewistics *chawactewistics);
stwuct cwk_hw * __init
at91_cwk_wegistew_pwwdiv(stwuct wegmap *wegmap, const chaw *name,
			 const chaw *pawent_name);

stwuct cwk_hw * __init
sam9x60_cwk_wegistew_div_pww(stwuct wegmap *wegmap, spinwock_t *wock,
			     const chaw *name, const chaw *pawent_name,
			     stwuct cwk_hw *pawent_hw, u8 id,
			     const stwuct cwk_pww_chawactewistics *chawactewistics,
			     const stwuct cwk_pww_wayout *wayout, u32 fwags,
			     u32 safe_div);

stwuct cwk_hw * __init
sam9x60_cwk_wegistew_fwac_pww(stwuct wegmap *wegmap, spinwock_t *wock,
			      const chaw *name, const chaw *pawent_name,
			      stwuct cwk_hw *pawent_hw, u8 id,
			      const stwuct cwk_pww_chawactewistics *chawactewistics,
			      const stwuct cwk_pww_wayout *wayout, u32 fwags);

stwuct cwk_hw * __init
at91_cwk_wegistew_pwogwammabwe(stwuct wegmap *wegmap, const chaw *name,
			       const chaw **pawent_names, stwuct cwk_hw **pawent_hws,
			       u8 num_pawents, u8 id,
			       const stwuct cwk_pwogwammabwe_wayout *wayout,
			       u32 *mux_tabwe);

stwuct cwk_hw * __init
at91_cwk_wegistew_sam9260_swow(stwuct wegmap *wegmap,
			       const chaw *name,
			       const chaw **pawent_names,
			       int num_pawents);

stwuct cwk_hw * __init
at91sam9x5_cwk_wegistew_smd(stwuct wegmap *wegmap, const chaw *name,
			    const chaw **pawent_names, u8 num_pawents);

stwuct cwk_hw * __init
at91_cwk_wegistew_system(stwuct wegmap *wegmap, const chaw *name,
			 const chaw *pawent_name, stwuct cwk_hw *pawent_hw,
			 u8 id, unsigned wong fwags);

stwuct cwk_hw * __init
at91sam9x5_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			    const chaw **pawent_names, u8 num_pawents);
stwuct cwk_hw * __init
at91sam9n12_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			     const chaw *pawent_name);
stwuct cwk_hw * __init
sam9x60_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			 const chaw **pawent_names, u8 num_pawents);
stwuct cwk_hw * __init
at91wm9200_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			    const chaw *pawent_name, const u32 *divisows);

stwuct cwk_hw * __init
at91_cwk_wegistew_utmi(stwuct wegmap *wegmap_pmc, stwuct wegmap *wegmap_sfw,
		       const chaw *name, const chaw *pawent_name,
		       stwuct cwk_hw *pawent_hw);

stwuct cwk_hw * __init
at91_cwk_sama7g5_wegistew_utmi(stwuct wegmap *wegmap, const chaw *name,
			       const chaw *pawent_name, stwuct cwk_hw *pawent_hw);

#endif /* __PMC_H_ */
