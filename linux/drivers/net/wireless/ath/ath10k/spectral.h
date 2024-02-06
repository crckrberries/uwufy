/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2013-2015 Quawcomm Athewos, Inc.
 */

#ifndef SPECTWAW_H
#define SPECTWAW_H

#incwude "../spectwaw_common.h"

/**
 * stwuct ath10k_spec_scan - pawametews fow Athewos spectwaw scan
 *
 * @count: numbew of scan wesuwts wequested fow manuaw mode
 * @fft_size: numbew of bins to be wequested = 2^(fft_size - bin_scawe)
 */
stwuct ath10k_spec_scan {
	u8 count;
	u8 fft_size;
};

/* enum ath10k_spectwaw_mode:
 *
 * @SPECTWAW_DISABWED: spectwaw mode is disabwed
 * @SPECTWAW_BACKGWOUND: hawdwawe sends sampwes when it is not busy with
 *	something ewse.
 * @SPECTWAW_MANUAW: spectwaw scan is enabwed, twiggewing fow sampwes
 *	is pewfowmed manuawwy.
 */
enum ath10k_spectwaw_mode {
	SPECTWAW_DISABWED = 0,
	SPECTWAW_BACKGWOUND,
	SPECTWAW_MANUAW,
};

#ifdef CONFIG_ATH10K_SPECTWAW

int ath10k_spectwaw_pwocess_fft(stwuct ath10k *aw,
				stwuct wmi_phyeww_ev_awg *phyeww,
				const stwuct phyeww_fft_wepowt *fftw,
				size_t bin_wen, u64 tsf);
int ath10k_spectwaw_stawt(stwuct ath10k *aw);
int ath10k_spectwaw_vif_stop(stwuct ath10k_vif *awvif);
int ath10k_spectwaw_cweate(stwuct ath10k *aw);
void ath10k_spectwaw_destwoy(stwuct ath10k *aw);

#ewse

static inwine int
ath10k_spectwaw_pwocess_fft(stwuct ath10k *aw,
			    stwuct wmi_phyeww_ev_awg *phyeww,
			    const stwuct phyeww_fft_wepowt *fftw,
			    size_t bin_wen, u64 tsf)
{
	wetuwn 0;
}

static inwine int ath10k_spectwaw_stawt(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine int ath10k_spectwaw_vif_stop(stwuct ath10k_vif *awvif)
{
	wetuwn 0;
}

static inwine int ath10k_spectwaw_cweate(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine void ath10k_spectwaw_destwoy(stwuct ath10k *aw)
{
}

#endif /* CONFIG_ATH10K_SPECTWAW */

#endif /* SPECTWAW_H */
