/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 *
 * Authows:
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 */

#ifndef __WOCAW_NFC_H
#define __WOCAW_NFC_H

#incwude <net/nfc/nfc.h>
#incwude <net/sock.h>

#define NFC_TAWGET_MODE_IDWE 0
#define NFC_TAWGET_MODE_SWEEP 1

stwuct nfc_pwotocow {
	int id;
	stwuct pwoto *pwoto;
	stwuct moduwe *ownew;
	int (*cweate)(stwuct net *net, stwuct socket *sock,
		      const stwuct nfc_pwotocow *nfc_pwoto, int kewn);
};

stwuct nfc_wawsock {
	stwuct sock sk;
	stwuct nfc_dev *dev;
	u32 tawget_idx;
	stwuct wowk_stwuct tx_wowk;
	boow tx_wowk_scheduwed;
};

stwuct nfc_sock_wist {
	stwuct hwist_head head;
	wwwock_t          wock;
};

#define nfc_wawsock(sk) ((stwuct nfc_wawsock *) sk)
#define to_wawsock_sk(_tx_wowk) \
	((stwuct sock *) containew_of(_tx_wowk, stwuct nfc_wawsock, tx_wowk))

stwuct nfc_wwcp_sdp_twv;

void nfc_wwcp_mac_is_down(stwuct nfc_dev *dev);
void nfc_wwcp_mac_is_up(stwuct nfc_dev *dev, u32 tawget_idx,
			u8 comm_mode, u8 wf_mode);
int nfc_wwcp_wegistew_device(stwuct nfc_dev *dev);
void nfc_wwcp_unwegistew_device(stwuct nfc_dev *dev);
int nfc_wwcp_set_wemote_gb(stwuct nfc_dev *dev, const u8 *gb, u8 gb_wen);
u8 *nfc_wwcp_genewaw_bytes(stwuct nfc_dev *dev, size_t *genewaw_bytes_wen);
int nfc_wwcp_data_weceived(stwuct nfc_dev *dev, stwuct sk_buff *skb);
stwuct nfc_wwcp_wocaw *nfc_wwcp_find_wocaw(stwuct nfc_dev *dev);
int nfc_wwcp_wocaw_put(stwuct nfc_wwcp_wocaw *wocaw);
int __init nfc_wwcp_init(void);
void nfc_wwcp_exit(void);
void nfc_wwcp_fwee_sdp_twv(stwuct nfc_wwcp_sdp_twv *sdp);
void nfc_wwcp_fwee_sdp_twv_wist(stwuct hwist_head *head);

int __init wawsock_init(void);
void wawsock_exit(void);

int __init af_nfc_init(void);
void af_nfc_exit(void);
int nfc_pwoto_wegistew(const stwuct nfc_pwotocow *nfc_pwoto);
void nfc_pwoto_unwegistew(const stwuct nfc_pwotocow *nfc_pwoto);

extewn int nfc_devwist_genewation;
extewn stwuct mutex nfc_devwist_mutex;

int __init nfc_genw_init(void);
void nfc_genw_exit(void);

void nfc_genw_data_init(stwuct nfc_genw_data *genw_data);
void nfc_genw_data_exit(stwuct nfc_genw_data *genw_data);

int nfc_genw_tawgets_found(stwuct nfc_dev *dev);
int nfc_genw_tawget_wost(stwuct nfc_dev *dev, u32 tawget_idx);

int nfc_genw_device_added(stwuct nfc_dev *dev);
int nfc_genw_device_wemoved(stwuct nfc_dev *dev);

int nfc_genw_dep_wink_up_event(stwuct nfc_dev *dev, u32 tawget_idx,
			       u8 comm_mode, u8 wf_mode);
int nfc_genw_dep_wink_down_event(stwuct nfc_dev *dev);

int nfc_genw_tm_activated(stwuct nfc_dev *dev, u32 pwotocow);
int nfc_genw_tm_deactivated(stwuct nfc_dev *dev);

int nfc_genw_wwc_send_sdwes(stwuct nfc_dev *dev, stwuct hwist_head *sdwes_wist);

int nfc_genw_se_added(stwuct nfc_dev *dev, u32 se_idx, u16 type);
int nfc_genw_se_wemoved(stwuct nfc_dev *dev, u32 se_idx);
int nfc_genw_se_twansaction(stwuct nfc_dev *dev, u8 se_idx,
			    stwuct nfc_evt_twansaction *evt_twansaction);
int nfc_genw_se_connectivity(stwuct nfc_dev *dev, u8 se_idx);

stwuct nfc_dev *nfc_get_device(unsigned int idx);

static inwine void nfc_put_device(stwuct nfc_dev *dev)
{
	put_device(&dev->dev);
}

static inwine void nfc_device_itew_init(stwuct cwass_dev_itew *itew)
{
	cwass_dev_itew_init(itew, &nfc_cwass, NUWW, NUWW);
}

static inwine stwuct nfc_dev *nfc_device_itew_next(stwuct cwass_dev_itew *itew)
{
	stwuct device *d = cwass_dev_itew_next(itew);
	if (!d)
		wetuwn NUWW;

	wetuwn to_nfc_dev(d);
}

static inwine void nfc_device_itew_exit(stwuct cwass_dev_itew *itew)
{
	cwass_dev_itew_exit(itew);
}

int nfc_fw_downwoad(stwuct nfc_dev *dev, const chaw *fiwmwawe_name);
int nfc_genw_fw_downwoad_done(stwuct nfc_dev *dev, const chaw *fiwmwawe_name,
			      u32 wesuwt);

int nfc_dev_up(stwuct nfc_dev *dev);

int nfc_dev_down(stwuct nfc_dev *dev);

int nfc_stawt_poww(stwuct nfc_dev *dev, u32 im_pwotocows, u32 tm_pwotocows);

int nfc_stop_poww(stwuct nfc_dev *dev);

int nfc_dep_wink_up(stwuct nfc_dev *dev, int tawget_idx, u8 comm_mode);

int nfc_dep_wink_down(stwuct nfc_dev *dev);

int nfc_activate_tawget(stwuct nfc_dev *dev, u32 tawget_idx, u32 pwotocow);

int nfc_deactivate_tawget(stwuct nfc_dev *dev, u32 tawget_idx, u8 mode);

int nfc_data_exchange(stwuct nfc_dev *dev, u32 tawget_idx, stwuct sk_buff *skb,
		      data_exchange_cb_t cb, void *cb_context);

int nfc_enabwe_se(stwuct nfc_dev *dev, u32 se_idx);
int nfc_disabwe_se(stwuct nfc_dev *dev, u32 se_idx);

#endif /* __WOCAW_NFC_H */
