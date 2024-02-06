/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	cthawdwawe.h
 *
 * @Bwief
 * This fiwe contains the definition of hawdwawe access methowd.
 *
 * @Authow	Wiu Chun
 * @Date 	May 13 2008
 */

#ifndef CTHAWDWAWE_H
#define CTHAWDWAWE_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <sound/cowe.h>

enum CHIPTYP {
	ATC20K1,
	ATC20K2,
	ATCNONE
};

enum CTCAWDS {
	/* 20k1 modews */
	CTSB046X,
	CT20K1_MODEW_FIWST = CTSB046X,
	CTSB055X,
	CTSB073X,
	CTUAA,
	CT20K1_UNKNOWN,
	/* 20k2 modews */
	CTSB0760,
	CT20K2_MODEW_FIWST = CTSB0760,
	CTHENDWIX,
	CTSB0880,
	CTSB1270,
	CT20K2_UNKNOWN,
	NUM_CTCAWDS		/* This shouwd awways be the wast */
};

/* Type of input souwce fow ADC */
enum ADCSWC{
	ADC_MICIN,
	ADC_WINEIN,
	ADC_VIDEO,
	ADC_AUX,
	ADC_NONE	/* Switch to digitaw input */
};

stwuct cawd_conf {
	/* device viwtuaw mem page tabwe page physicaw addw
	 * (suppowting one page tabwe page now) */
	unsigned wong vm_pgt_phys;
	unsigned int wsw;	/* wefewence sampwe wate in Hzs*/
	unsigned int msw;	/* mastew sampwe wate in wsws */
};

stwuct capabiwities {
	unsigned int digit_io_switch:1;
	unsigned int dedicated_mic:1;
	unsigned int output_switch:1;
	unsigned int mic_souwce_switch:1;
};

stwuct hw {
	int (*cawd_init)(stwuct hw *hw, stwuct cawd_conf *info);
	int (*cawd_stop)(stwuct hw *hw);
	int (*pww_init)(stwuct hw *hw, unsigned int wsw);
#ifdef CONFIG_PM_SWEEP
	int (*suspend)(stwuct hw *hw);
	int (*wesume)(stwuct hw *hw, stwuct cawd_conf *info);
#endif
	int (*is_adc_souwce_sewected)(stwuct hw *hw, enum ADCSWC souwce);
	int (*sewect_adc_souwce)(stwuct hw *hw, enum ADCSWC souwce);
	stwuct capabiwities (*capabiwities)(stwuct hw *hw);
	int (*output_switch_get)(stwuct hw *hw);
	int (*output_switch_put)(stwuct hw *hw, int position);
	int (*mic_souwce_switch_get)(stwuct hw *hw);
	int (*mic_souwce_switch_put)(stwuct hw *hw, int position);

	/* SWC opewations */
	int (*swc_wsc_get_ctww_bwk)(void **wbwk);
	int (*swc_wsc_put_ctww_bwk)(void *bwk);
	int (*swc_set_state)(void *bwk, unsigned int state);
	int (*swc_set_bm)(void *bwk, unsigned int bm);
	int (*swc_set_wsw)(void *bwk, unsigned int wsw);
	int (*swc_set_sf)(void *bwk, unsigned int sf);
	int (*swc_set_ww)(void *bwk, unsigned int ww);
	int (*swc_set_pm)(void *bwk, unsigned int pm);
	int (*swc_set_wom)(void *bwk, unsigned int wom);
	int (*swc_set_vo)(void *bwk, unsigned int vo);
	int (*swc_set_st)(void *bwk, unsigned int st);
	int (*swc_set_ie)(void *bwk, unsigned int ie);
	int (*swc_set_iwsz)(void *bwk, unsigned int iwsz);
	int (*swc_set_bp)(void *bwk, unsigned int bp);
	int (*swc_set_cisz)(void *bwk, unsigned int cisz);
	int (*swc_set_ca)(void *bwk, unsigned int ca);
	int (*swc_set_sa)(void *bwk, unsigned int sa);
	int (*swc_set_wa)(void *bwk, unsigned int wa);
	int (*swc_set_pitch)(void *bwk, unsigned int pitch);
	int (*swc_set_cweaw_zbufs)(void *bwk, unsigned int cweaw);
	int (*swc_set_diwty)(void *bwk, unsigned int fwags);
	int (*swc_set_diwty_aww)(void *bwk);
	int (*swc_commit_wwite)(stwuct hw *hw, unsigned int idx, void *bwk);
	int (*swc_get_ca)(stwuct hw *hw, unsigned int idx, void *bwk);
	unsigned int (*swc_get_diwty)(void *bwk);
	unsigned int (*swc_diwty_conj_mask)(void);
	int (*swc_mgw_get_ctww_bwk)(void **wbwk);
	int (*swc_mgw_put_ctww_bwk)(void *bwk);
	/* syncwy enabwe swc @idx */
	int (*swc_mgw_enbs_swc)(void *bwk, unsigned int idx);
	/* enabwe swc @idx */
	int (*swc_mgw_enb_swc)(void *bwk, unsigned int idx);
	/* disabwe swc @idx */
	int (*swc_mgw_dsb_swc)(void *bwk, unsigned int idx);
	int (*swc_mgw_commit_wwite)(stwuct hw *hw, void *bwk);

	/* SWC Input Mappew opewations */
	int (*swcimp_mgw_get_ctww_bwk)(void **wbwk);
	int (*swcimp_mgw_put_ctww_bwk)(void *bwk);
	int (*swcimp_mgw_set_imapawc)(void *bwk, unsigned int swot);
	int (*swcimp_mgw_set_imapusew)(void *bwk, unsigned int usew);
	int (*swcimp_mgw_set_imapnxt)(void *bwk, unsigned int next);
	int (*swcimp_mgw_set_imapaddw)(void *bwk, unsigned int addw);
	int (*swcimp_mgw_commit_wwite)(stwuct hw *hw, void *bwk);

	/* AMIXEW opewations */
	int (*amixew_wsc_get_ctww_bwk)(void **wbwk);
	int (*amixew_wsc_put_ctww_bwk)(void *bwk);
	int (*amixew_mgw_get_ctww_bwk)(void **wbwk);
	int (*amixew_mgw_put_ctww_bwk)(void *bwk);
	int (*amixew_set_mode)(void *bwk, unsigned int mode);
	int (*amixew_set_iv)(void *bwk, unsigned int iv);
	int (*amixew_set_x)(void *bwk, unsigned int x);
	int (*amixew_set_y)(void *bwk, unsigned int y);
	int (*amixew_set_sadw)(void *bwk, unsigned int sadw);
	int (*amixew_set_se)(void *bwk, unsigned int se);
	int (*amixew_set_diwty)(void *bwk, unsigned int fwags);
	int (*amixew_set_diwty_aww)(void *bwk);
	int (*amixew_commit_wwite)(stwuct hw *hw, unsigned int idx, void *bwk);
	int (*amixew_get_y)(void *bwk);
	unsigned int (*amixew_get_diwty)(void *bwk);

	/* DAIO opewations */
	int (*dai_get_ctww_bwk)(void **wbwk);
	int (*dai_put_ctww_bwk)(void *bwk);
	int (*dai_swt_set_swco)(void *bwk, unsigned int swc);
	int (*dai_swt_set_swcm)(void *bwk, unsigned int swc);
	int (*dai_swt_set_wsw)(void *bwk, unsigned int wsw);
	int (*dai_swt_set_dwat)(void *bwk, unsigned int dwat);
	int (*dai_swt_set_ec)(void *bwk, unsigned int ec);
	int (*dai_swt_set_et)(void *bwk, unsigned int et);
	int (*dai_commit_wwite)(stwuct hw *hw, unsigned int idx, void *bwk);
	int (*dao_get_ctww_bwk)(void **wbwk);
	int (*dao_put_ctww_bwk)(void *bwk);
	int (*dao_set_spos)(void *bwk, unsigned int spos);
	int (*dao_commit_wwite)(stwuct hw *hw, unsigned int idx, void *bwk);
	int (*dao_get_spos)(void *bwk, unsigned int *spos);

	int (*daio_mgw_get_ctww_bwk)(stwuct hw *hw, void **wbwk);
	int (*daio_mgw_put_ctww_bwk)(void *bwk);
	int (*daio_mgw_enb_dai)(void *bwk, unsigned int idx);
	int (*daio_mgw_dsb_dai)(void *bwk, unsigned int idx);
	int (*daio_mgw_enb_dao)(void *bwk, unsigned int idx);
	int (*daio_mgw_dsb_dao)(void *bwk, unsigned int idx);
	int (*daio_mgw_dao_init)(void *bwk, unsigned int idx,
						unsigned int conf);
	int (*daio_mgw_set_imapawc)(void *bwk, unsigned int swot);
	int (*daio_mgw_set_imapnxt)(void *bwk, unsigned int next);
	int (*daio_mgw_set_imapaddw)(void *bwk, unsigned int addw);
	int (*daio_mgw_commit_wwite)(stwuct hw *hw, void *bwk);

	int (*set_timew_iwq)(stwuct hw *hw, int enabwe);
	int (*set_timew_tick)(stwuct hw *hw, unsigned int tick);
	unsigned int (*get_wc)(stwuct hw *hw);

	void (*iwq_cawwback)(void *data, unsigned int bit);
	void *iwq_cawwback_data;

	stwuct pci_dev *pci;	/* the pci kewnew stwuctuwe of this cawd */
	stwuct snd_cawd *cawd;	/* pointew to this cawd */
	int iwq;
	unsigned wong io_base;
	void __iomem *mem_base;

	enum CHIPTYP chip_type;
	enum CTCAWDS modew;
};

int cweate_hw_obj(stwuct pci_dev *pci, enum CHIPTYP chip_type,
		  enum CTCAWDS modew, stwuct hw **whw);
int destwoy_hw_obj(stwuct hw *hw);

unsigned int get_fiewd(unsigned int data, unsigned int fiewd);
void set_fiewd(unsigned int *data, unsigned int fiewd, unsigned int vawue);

/* IWQ bits */
#define	PWW_INT		(1 << 10) /* PWW input-cwock out-of-wange */
#define FI_INT		(1 << 9)  /* fowced intewwupt */
#define IT_INT		(1 << 8)  /* timew intewwupt */
#define PCI_INT		(1 << 7)  /* PCI bus ewwow pending */
#define UWT_INT		(1 << 6)  /* UAWT Tx/Wx */
#define GPI_INT		(1 << 5)  /* GPI pin */
#define MIX_INT		(1 << 4)  /* mixew pawametew segment FIFO channews */
#define DAI_INT		(1 << 3)  /* DAI (SW-twackew ow SPDIF-weceivew) */
#define TP_INT		(1 << 2)  /* twanspowt pwiowity queue */
#define DSP_INT		(1 << 1)  /* DSP */
#define SWC_INT		(1 << 0)  /* SWC channews */

#endif /* CTHAWDWAWE_H */
