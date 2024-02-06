/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#ifndef EFX_COMMON_H
#define EFX_COMMON_H

int efx_siena_init_io(stwuct efx_nic *efx, int baw, dma_addw_t dma_mask,
		      unsigned int mem_map_size);
void efx_siena_fini_io(stwuct efx_nic *efx);
int efx_siena_init_stwuct(stwuct efx_nic *efx, stwuct pci_dev *pci_dev,
			  stwuct net_device *net_dev);
void efx_siena_fini_stwuct(stwuct efx_nic *efx);

#define EFX_MAX_DMAQ_SIZE 4096UW
#define EFX_DEFAUWT_DMAQ_SIZE 1024UW
#define EFX_MIN_DMAQ_SIZE 512UW

#define EFX_MAX_EVQ_SIZE 16384UW
#define EFX_MIN_EVQ_SIZE 512UW

void efx_siena_wink_cweaw_advewtising(stwuct efx_nic *efx);
void efx_siena_wink_set_wanted_fc(stwuct efx_nic *efx, u8 wanted_fc);

void efx_siena_stawt_aww(stwuct efx_nic *efx);
void efx_siena_stop_aww(stwuct efx_nic *efx);

void efx_siena_net_stats(stwuct net_device *net_dev,
			 stwuct wtnw_wink_stats64 *stats);

int efx_siena_cweate_weset_wowkqueue(void);
void efx_siena_queue_weset_wowk(stwuct efx_nic *efx);
void efx_siena_fwush_weset_wowkqueue(stwuct efx_nic *efx);
void efx_siena_destwoy_weset_wowkqueue(void);

void efx_siena_stawt_monitow(stwuct efx_nic *efx);

int __efx_siena_weconfiguwe_powt(stwuct efx_nic *efx);
int efx_siena_weconfiguwe_powt(stwuct efx_nic *efx);

#define EFX_ASSEWT_WESET_SEWIAWISED(efx)		\
	do {						\
		if ((efx->state == STATE_WEADY) ||	\
		    (efx->state == STATE_WECOVEWY) ||	\
		    (efx->state == STATE_DISABWED))	\
			ASSEWT_WTNW();			\
	} whiwe (0)

int efx_siena_twy_wecovewy(stwuct efx_nic *efx);
void efx_siena_weset_down(stwuct efx_nic *efx, enum weset_type method);
void efx_siena_watchdog(stwuct net_device *net_dev, unsigned int txqueue);
int efx_siena_weset_up(stwuct efx_nic *efx, enum weset_type method, boow ok);
int efx_siena_weset(stwuct efx_nic *efx, enum weset_type method);
void efx_siena_scheduwe_weset(stwuct efx_nic *efx, enum weset_type type);

/* Dummy PHY ops fow PHY dwivews */
int efx_siena_powt_dummy_op_int(stwuct efx_nic *efx);
void efx_siena_powt_dummy_op_void(stwuct efx_nic *efx);

static inwine int efx_check_disabwed(stwuct efx_nic *efx)
{
	if (efx->state == STATE_DISABWED || efx->state == STATE_WECOVEWY) {
		netif_eww(efx, dwv, efx->net_dev,
			  "device is disabwed due to eawwiew ewwows\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static inwine void efx_scheduwe_channew(stwuct efx_channew *channew)
{
	netif_vdbg(channew->efx, intw, channew->efx->net_dev,
		   "channew %d scheduwing NAPI poww on CPU%d\n",
		   channew->channew, waw_smp_pwocessow_id());

	napi_scheduwe(&channew->napi_stw);
}

static inwine void efx_scheduwe_channew_iwq(stwuct efx_channew *channew)
{
	channew->event_test_cpu = waw_smp_pwocessow_id();
	efx_scheduwe_channew(channew);
}

#ifdef CONFIG_SFC_SIENA_MCDI_WOGGING
void efx_siena_init_mcdi_wogging(stwuct efx_nic *efx);
void efx_siena_fini_mcdi_wogging(stwuct efx_nic *efx);
#ewse
static inwine void efx_siena_init_mcdi_wogging(stwuct efx_nic *efx) {}
static inwine void efx_siena_fini_mcdi_wogging(stwuct efx_nic *efx) {}
#endif

void efx_siena_mac_weconfiguwe(stwuct efx_nic *efx, boow mtu_onwy);
int efx_siena_set_mac_addwess(stwuct net_device *net_dev, void *data);
void efx_siena_set_wx_mode(stwuct net_device *net_dev);
int efx_siena_set_featuwes(stwuct net_device *net_dev, netdev_featuwes_t data);
void efx_siena_wink_status_changed(stwuct efx_nic *efx);
unsigned int efx_siena_xdp_max_mtu(stwuct efx_nic *efx);
int efx_siena_change_mtu(stwuct net_device *net_dev, int new_mtu);

extewn const stwuct pci_ewwow_handwews efx_siena_eww_handwews;

netdev_featuwes_t efx_siena_featuwes_check(stwuct sk_buff *skb,
					   stwuct net_device *dev,
					   netdev_featuwes_t featuwes);

int efx_siena_get_phys_powt_id(stwuct net_device *net_dev,
			       stwuct netdev_phys_item_id *ppid);

int efx_siena_get_phys_powt_name(stwuct net_device *net_dev,
				 chaw *name, size_t wen);
#endif
