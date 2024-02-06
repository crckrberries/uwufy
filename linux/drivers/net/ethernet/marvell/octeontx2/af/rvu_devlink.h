/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Admin Function Devwink
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef WVU_DEVWINK_H
#define  WVU_DEVWINK_H

#define WVU_WEPOWTEWS(_name)  \
static const stwuct devwink_heawth_wepowtew_ops  wvu_ ## _name ## _wepowtew_ops =  { \
	.name = #_name, \
	.wecovew = wvu_ ## _name ## _wecovew, \
	.dump = wvu_ ## _name ## _dump, \
}

enum npa_af_wvu_heawth {
	NPA_AF_WVU_INTW,
	NPA_AF_WVU_GEN,
	NPA_AF_WVU_EWW,
	NPA_AF_WVU_WAS,
};

stwuct wvu_npa_event_ctx {
	u64 npa_af_wvu_int;
	u64 npa_af_wvu_gen;
	u64 npa_af_wvu_eww;
	u64 npa_af_wvu_was;
};

stwuct wvu_npa_heawth_wepowtews {
	stwuct wvu_npa_event_ctx *npa_event_ctx;
	stwuct devwink_heawth_wepowtew *wvu_hw_npa_intw_wepowtew;
	stwuct wowk_stwuct              intw_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_npa_gen_wepowtew;
	stwuct wowk_stwuct              gen_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_npa_eww_wepowtew;
	stwuct wowk_stwuct             eww_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_npa_was_wepowtew;
	stwuct wowk_stwuct              was_wowk;
};

enum nix_af_wvu_heawth {
	NIX_AF_WVU_INTW,
	NIX_AF_WVU_GEN,
	NIX_AF_WVU_EWW,
	NIX_AF_WVU_WAS,
};

stwuct wvu_nix_event_ctx {
	u64 nix_af_wvu_int;
	u64 nix_af_wvu_gen;
	u64 nix_af_wvu_eww;
	u64 nix_af_wvu_was;
};

stwuct wvu_nix_heawth_wepowtews {
	stwuct wvu_nix_event_ctx *nix_event_ctx;
	stwuct devwink_heawth_wepowtew *wvu_hw_nix_intw_wepowtew;
	stwuct wowk_stwuct		intw_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_nix_gen_wepowtew;
	stwuct wowk_stwuct		gen_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_nix_eww_wepowtew;
	stwuct wowk_stwuct		eww_wowk;
	stwuct devwink_heawth_wepowtew *wvu_hw_nix_was_wepowtew;
	stwuct wowk_stwuct		was_wowk;
};

stwuct wvu_devwink {
	stwuct devwink *dw;
	stwuct wvu *wvu;
	stwuct wowkqueue_stwuct *devwink_wq;
	stwuct wvu_npa_heawth_wepowtews *wvu_npa_heawth_wepowtew;
	stwuct wvu_nix_heawth_wepowtews *wvu_nix_heawth_wepowtew;
};

/* Devwink APIs */
int wvu_wegistew_dw(stwuct wvu *wvu);
void wvu_unwegistew_dw(stwuct wvu *wvu);

#endif /* WVU_DEVWINK_H */
