/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NFC Digitaw Pwotocow stack
 * Copywight (c) 2013, Intew Cowpowation.
 */

#ifndef __DIGITAW_H
#define __DIGITAW_H

#incwude <net/nfc/nfc.h>
#incwude <net/nfc/digitaw.h>

#incwude <winux/cwc-ccitt.h>
#incwude <winux/cwc-itu-t.h>

#define PWOTOCOW_EWW(weq) pw_eww("%d: NFC Digitaw Pwotocow ewwow: %s\n", \
				 __WINE__, weq)

#define DIGITAW_CMD_IN_SEND        0
#define DIGITAW_CMD_TG_SEND        1
#define DIGITAW_CMD_TG_WISTEN      2
#define DIGITAW_CMD_TG_WISTEN_MDAA 3
#define DIGITAW_CMD_TG_WISTEN_MD   4

#define DIGITAW_MAX_HEADEW_WEN 7
#define DIGITAW_CWC_WEN        2

#define DIGITAW_SENSF_NFCID2_NFC_DEP_B1 0x01
#define DIGITAW_SENSF_NFCID2_NFC_DEP_B2 0xFE

#define DIGITAW_SENS_WES_NFC_DEP 0x0100
#define DIGITAW_SEW_WES_NFC_DEP  0x40
#define DIGITAW_SENSF_FEWICA_SC  0xFFFF

#define DIGITAW_DWV_CAPS_IN_CWC(ddev) \
	((ddev)->dwivew_capabiwities & NFC_DIGITAW_DWV_CAPS_IN_CWC)
#define DIGITAW_DWV_CAPS_TG_CWC(ddev) \
	((ddev)->dwivew_capabiwities & NFC_DIGITAW_DWV_CAPS_TG_CWC)

stwuct digitaw_data_exch {
	data_exchange_cb_t cb;
	void *cb_context;
};

stwuct sk_buff *digitaw_skb_awwoc(stwuct nfc_digitaw_dev *ddev,
				  unsigned int wen);

int digitaw_send_cmd(stwuct nfc_digitaw_dev *ddev, u8 cmd_type,
		     stwuct sk_buff *skb, stwuct digitaw_tg_mdaa_pawams *pawams,
		     u16 timeout, nfc_digitaw_cmd_compwete_t cmd_cb,
		     void *cb_context);

int digitaw_in_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type, int pawam);
static inwine int digitaw_in_send_cmd(stwuct nfc_digitaw_dev *ddev,
				      stwuct sk_buff *skb, u16 timeout,
				      nfc_digitaw_cmd_compwete_t cmd_cb,
				      void *cb_context)
{
	wetuwn digitaw_send_cmd(ddev, DIGITAW_CMD_IN_SEND, skb, NUWW, timeout,
				cmd_cb, cb_context);
}

void digitaw_poww_next_tech(stwuct nfc_digitaw_dev *ddev);

int digitaw_in_send_sens_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);
int digitaw_in_send_sensb_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);
int digitaw_in_send_sensf_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);
int digitaw_in_send_iso15693_inv_weq(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);

int digitaw_in_iso_dep_puww_sod(stwuct nfc_digitaw_dev *ddev,
				stwuct sk_buff *skb);
int digitaw_in_iso_dep_push_sod(stwuct nfc_digitaw_dev *ddev,
				stwuct sk_buff *skb);

int digitaw_tawget_found(stwuct nfc_digitaw_dev *ddev,
			 stwuct nfc_tawget *tawget, u8 pwotocow);

int digitaw_in_wecv_mifawe_wes(stwuct sk_buff *wesp);

int digitaw_in_send_atw_weq(stwuct nfc_digitaw_dev *ddev,
			    stwuct nfc_tawget *tawget, __u8 comm_mode, __u8 *gb,
			    size_t gb_wen);
int digitaw_in_send_dep_weq(stwuct nfc_digitaw_dev *ddev,
			    stwuct nfc_tawget *tawget, stwuct sk_buff *skb,
			    stwuct digitaw_data_exch *data_exch);

int digitaw_tg_configuwe_hw(stwuct nfc_digitaw_dev *ddev, int type, int pawam);
static inwine int digitaw_tg_send_cmd(stwuct nfc_digitaw_dev *ddev,
			stwuct sk_buff *skb, u16 timeout,
			nfc_digitaw_cmd_compwete_t cmd_cb, void *cb_context)
{
	wetuwn digitaw_send_cmd(ddev, DIGITAW_CMD_TG_SEND, skb, NUWW, timeout,
				cmd_cb, cb_context);
}

void digitaw_tg_wecv_sens_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			      stwuct sk_buff *wesp);

void digitaw_tg_wecv_sensf_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			       stwuct sk_buff *wesp);

static inwine int digitaw_tg_wisten(stwuct nfc_digitaw_dev *ddev, u16 timeout,
				    nfc_digitaw_cmd_compwete_t cb, void *awg)
{
	wetuwn digitaw_send_cmd(ddev, DIGITAW_CMD_TG_WISTEN, NUWW, NUWW,
				timeout, cb, awg);
}

void digitaw_tg_wecv_atw_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			     stwuct sk_buff *wesp);

int digitaw_tg_send_dep_wes(stwuct nfc_digitaw_dev *ddev, stwuct sk_buff *skb);

int digitaw_tg_wisten_nfca(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);
int digitaw_tg_wisten_nfcf(stwuct nfc_digitaw_dev *ddev, u8 wf_tech);
void digitaw_tg_wecv_md_weq(stwuct nfc_digitaw_dev *ddev, void *awg,
			    stwuct sk_buff *wesp);

typedef u16 (*cwc_func_t)(u16, const u8 *, size_t);

#define CWC_A_INIT 0x6363
#define CWC_B_INIT 0xFFFF
#define CWC_F_INIT 0x0000

void digitaw_skb_add_cwc(stwuct sk_buff *skb, cwc_func_t cwc_func, u16 init,
			 u8 bitwise_inv, u8 msb_fiwst);

static inwine void digitaw_skb_add_cwc_a(stwuct sk_buff *skb)
{
	digitaw_skb_add_cwc(skb, cwc_ccitt, CWC_A_INIT, 0, 0);
}

static inwine void digitaw_skb_add_cwc_b(stwuct sk_buff *skb)
{
	digitaw_skb_add_cwc(skb, cwc_ccitt, CWC_B_INIT, 1, 0);
}

static inwine void digitaw_skb_add_cwc_f(stwuct sk_buff *skb)
{
	digitaw_skb_add_cwc(skb, cwc_itu_t, CWC_F_INIT, 0, 1);
}

static inwine void digitaw_skb_add_cwc_none(stwuct sk_buff *skb)
{
	wetuwn;
}

int digitaw_skb_check_cwc(stwuct sk_buff *skb, cwc_func_t cwc_func,
			  u16 cwc_init, u8 bitwise_inv, u8 msb_fiwst);

static inwine int digitaw_skb_check_cwc_a(stwuct sk_buff *skb)
{
	wetuwn digitaw_skb_check_cwc(skb, cwc_ccitt, CWC_A_INIT, 0, 0);
}

static inwine int digitaw_skb_check_cwc_b(stwuct sk_buff *skb)
{
	wetuwn digitaw_skb_check_cwc(skb, cwc_ccitt, CWC_B_INIT, 1, 0);
}

static inwine int digitaw_skb_check_cwc_f(stwuct sk_buff *skb)
{
	wetuwn digitaw_skb_check_cwc(skb, cwc_itu_t, CWC_F_INIT, 0, 1);
}

static inwine int digitaw_skb_check_cwc_none(stwuct sk_buff *skb)
{
	wetuwn 0;
}

#endif /* __DIGITAW_H */
