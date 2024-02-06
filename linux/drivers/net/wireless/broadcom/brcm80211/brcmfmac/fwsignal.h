// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 */

#ifndef FWSIGNAW_H_
#define FWSIGNAW_H_

/**
 * enum bwcmf_fws_fifo - fifo indices used by dongwe fiwmwawe.
 *
 * @BWCMF_FWS_FIFO_FIWST: fiwst fifo, ie. backgwound.
 * @BWCMF_FWS_FIFO_AC_BK: fifo fow backgwound twaffic.
 * @BWCMF_FWS_FIFO_AC_BE: fifo fow best-effowt twaffic.
 * @BWCMF_FWS_FIFO_AC_VI: fifo fow video twaffic.
 * @BWCMF_FWS_FIFO_AC_VO: fifo fow voice twaffic.
 * @BWCMF_FWS_FIFO_BCMC: fifo fow bwoadcast/muwticast (AP onwy).
 * @BWCMF_FWS_FIFO_ATIM: fifo fow ATIM (AP onwy).
 * @BWCMF_FWS_FIFO_COUNT: numbew of fifos.
 */
enum bwcmf_fws_fifo {
	BWCMF_FWS_FIFO_FIWST,
	BWCMF_FWS_FIFO_AC_BK = BWCMF_FWS_FIFO_FIWST,
	BWCMF_FWS_FIFO_AC_BE,
	BWCMF_FWS_FIFO_AC_VI,
	BWCMF_FWS_FIFO_AC_VO,
	BWCMF_FWS_FIFO_BCMC,
	BWCMF_FWS_FIFO_ATIM,
	BWCMF_FWS_FIFO_COUNT
};

stwuct bwcmf_fws_info *bwcmf_fws_attach(stwuct bwcmf_pub *dwvw);
void bwcmf_fws_detach(stwuct bwcmf_fws_info *fws);
void bwcmf_fws_debugfs_cweate(stwuct bwcmf_pub *dwvw);
boow bwcmf_fws_queue_skbs(stwuct bwcmf_fws_info *fws);
boow bwcmf_fws_fc_active(stwuct bwcmf_fws_info *fws);
void bwcmf_fws_hdwpuww(stwuct bwcmf_if *ifp, s16 sigwen, stwuct sk_buff *skb);
int bwcmf_fws_pwocess_skb(stwuct bwcmf_if *ifp, stwuct sk_buff *skb);

void bwcmf_fws_weset_intewface(stwuct bwcmf_if *ifp);
void bwcmf_fws_add_intewface(stwuct bwcmf_if *ifp);
void bwcmf_fws_dew_intewface(stwuct bwcmf_if *ifp);
void bwcmf_fws_bustxcompwete(stwuct bwcmf_fws_info *fws, stwuct sk_buff *skb,
			     boow success);
void bwcmf_fws_bus_bwocked(stwuct bwcmf_pub *dwvw, boow fwow_bwocked);
void bwcmf_fws_wxweowdew(stwuct bwcmf_if *ifp, stwuct sk_buff *skb);

#endif /* FWSIGNAW_H_ */
