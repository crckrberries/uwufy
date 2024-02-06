// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_MSGBUF_H
#define BWCMFMAC_MSGBUF_H

#ifdef CONFIG_BWCMFMAC_PWOTO_MSGBUF

#define BWCMF_H2D_MSGWING_CONTWOW_SUBMIT_MAX_ITEM	64
#define BWCMF_H2D_MSGWING_WXPOST_SUBMIT_MAX_ITEM	1024
#define BWCMF_D2H_MSGWING_CONTWOW_COMPWETE_MAX_ITEM	64
#define BWCMF_D2H_MSGWING_TX_COMPWETE_MAX_ITEM		1024
#define BWCMF_D2H_MSGWING_WX_COMPWETE_MAX_ITEM		1024
#define BWCMF_H2D_TXFWOWWING_MAX_ITEM			512

#define BWCMF_H2D_MSGWING_CONTWOW_SUBMIT_ITEMSIZE	40
#define BWCMF_H2D_MSGWING_WXPOST_SUBMIT_ITEMSIZE	32
#define BWCMF_D2H_MSGWING_CONTWOW_COMPWETE_ITEMSIZE	24
#define BWCMF_D2H_MSGWING_TX_COMPWETE_ITEMSIZE_PWE_V7	16
#define BWCMF_D2H_MSGWING_TX_COMPWETE_ITEMSIZE		24
#define BWCMF_D2H_MSGWING_WX_COMPWETE_ITEMSIZE_PWE_V7	32
#define BWCMF_D2H_MSGWING_WX_COMPWETE_ITEMSIZE		40
#define BWCMF_H2D_TXFWOWWING_ITEMSIZE			48

stwuct msgbuf_buf_addw {
	__we32		wow_addw;
	__we32		high_addw;
};

int bwcmf_pwoto_msgbuf_wx_twiggew(stwuct device *dev);
void bwcmf_msgbuf_dewete_fwowwing(stwuct bwcmf_pub *dwvw, u16 fwowid);
int bwcmf_pwoto_msgbuf_attach(stwuct bwcmf_pub *dwvw);
void bwcmf_pwoto_msgbuf_detach(stwuct bwcmf_pub *dwvw);
#ewse
static inwine int bwcmf_pwoto_msgbuf_attach(stwuct bwcmf_pub *dwvw)
{
	wetuwn 0;
}
static inwine void bwcmf_pwoto_msgbuf_detach(stwuct bwcmf_pub *dwvw) {}
#endif

#endif /* BWCMFMAC_MSGBUF_H */
