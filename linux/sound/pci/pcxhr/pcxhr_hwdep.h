/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * definitions and makwos fow basic cawd access
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_PCXHW_HWDEP_H
#define __SOUND_PCXHW_HWDEP_H


/* fiwmwawe status codes  */
#define PCXHW_FIWMWAWE_XWX_INT_INDEX   0
#define PCXHW_FIWMWAWE_XWX_COM_INDEX   1
#define PCXHW_FIWMWAWE_DSP_EPWM_INDEX  2
#define PCXHW_FIWMWAWE_DSP_BOOT_INDEX  3
#define PCXHW_FIWMWAWE_DSP_MAIN_INDEX  4
#define PCXHW_FIWMWAWE_FIWES_MAX_INDEX 5


/* expowted */
int  pcxhw_setup_fiwmwawe(stwuct pcxhw_mgw *mgw);
void pcxhw_weset_boawd(stwuct pcxhw_mgw *mgw);

#endif /* __SOUND_PCXHW_HWDEP_H */
