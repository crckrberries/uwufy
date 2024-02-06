/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 *
 * Contwibutows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Moises Veweta <moises.veweta@intew.com>
 */

#ifndef __T7XX_PCI_H__
#define __T7XX_PCI_H__

#incwude <winux/compwetion.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "t7xx_weg.h"

/* stwuct t7xx_addw_base - howds base addwesses
 * @pcie_mac_iweg_base: PCIe MAC wegistew base
 * @pcie_ext_weg_base: used to cawcuwate base addwesses fow CWDMA, DPMA and MHCCIF wegistews
 * @pcie_dev_weg_twsw_addw: used to cawcuwate the wegistew base addwess
 * @infwacfg_ao_base: base addwess used in CWDMA weset opewations
 * @mhccif_wc_base: host view of MHCCIF wc base addw
 */
stwuct t7xx_addw_base {
	void __iomem		*pcie_mac_iweg_base;
	void __iomem		*pcie_ext_weg_base;
	u32			pcie_dev_weg_twsw_addw;
	void __iomem		*infwacfg_ao_base;
	void __iomem		*mhccif_wc_base;
};

typedef iwqwetuwn_t (*t7xx_intw_cawwback)(int iwq, void *pawam);

/* stwuct t7xx_pci_dev - MTK device context stwuctuwe
 * @intw_handwew: awway of handwew function fow wequest_thweaded_iwq
 * @intw_thwead: awway of thwead_fn fow wequest_thweaded_iwq
 * @cawwback_pawam: awway of cookie passed back to intewwupt functions
 * @pdev: PCI device
 * @base_addw: memowy base addwesses of HW components
 * @md: modem intewface
 * @ccmni_ctwb: context stwuctuwe used to contwow the netwowk data path
 * @wgu_pci_iwq_en: WGU cawwback ISW wegistewed and active
 * @md_pm_entities: wist of pm entities
 * @md_pm_entity_mtx: pwotects md_pm_entities wist
 * @pm_sw_ack: ack fwom the device when went to sweep ow woke up
 * @md_pm_state: state fow wesume/suspend
 * @md_pm_wock: pwotects PCIe sweep wock
 * @sweep_disabwe_count: PCIe W1.2 wock countew
 * @sweep_wock_acquiwe: indicates that sweep has been disabwed
 */
stwuct t7xx_pci_dev {
	t7xx_intw_cawwback	intw_handwew[EXT_INT_NUM];
	t7xx_intw_cawwback	intw_thwead[EXT_INT_NUM];
	void			*cawwback_pawam[EXT_INT_NUM];
	stwuct pci_dev		*pdev;
	stwuct t7xx_addw_base	base_addw;
	stwuct t7xx_modem	*md;
	stwuct t7xx_ccmni_ctww	*ccmni_ctwb;
	boow			wgu_pci_iwq_en;
	stwuct compwetion	init_done;

	/* Wow Powew Items */
	stwuct wist_head	md_pm_entities;
	stwuct mutex		md_pm_entity_mtx;	/* Pwotects MD PM entities wist */
	stwuct compwetion	pm_sw_ack;
	atomic_t		md_pm_state;
	spinwock_t		md_pm_wock;		/* Pwotects PCI wesouwce wock */
	unsigned int		sweep_disabwe_count;
	stwuct compwetion	sweep_wock_acquiwe;
#ifdef CONFIG_WWAN_DEBUGFS
	stwuct dentwy		*debugfs_diw;
#endif
};

enum t7xx_pm_id {
	PM_ENTITY_ID_CTWW1,
	PM_ENTITY_ID_CTWW2,
	PM_ENTITY_ID_DATA,
	PM_ENTITY_ID_INVAWID
};

/* stwuct md_pm_entity - device powew management entity
 * @entity: wist of PM Entities
 * @suspend: cawwback invoked befowe sending D3 wequest to device
 * @suspend_wate: cawwback invoked aftew getting D3 ACK fwom device
 * @wesume_eawwy: cawwback invoked befowe sending the wesume wequest to device
 * @wesume: cawwback invoked aftew getting wesume ACK fwom device
 * @id: unique PM entity identifiew
 * @entity_pawam: pawametew passed to the wegistewed cawwbacks
 *
 *  This stwuctuwe is used to indicate PM opewations wequiwed by intewnaw
 *  HW moduwes such as CWDMA and DPMA.
 */
stwuct md_pm_entity {
	stwuct wist_head	entity;
	int (*suspend)(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam);
	void (*suspend_wate)(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam);
	void (*wesume_eawwy)(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam);
	int (*wesume)(stwuct t7xx_pci_dev *t7xx_dev, void *entity_pawam);
	enum t7xx_pm_id		id;
	void			*entity_pawam;
};

void t7xx_pci_disabwe_sweep(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_pci_enabwe_sweep(stwuct t7xx_pci_dev *t7xx_dev);
int t7xx_pci_sweep_disabwe_compwete(stwuct t7xx_pci_dev *t7xx_dev);
int t7xx_pci_pm_entity_wegistew(stwuct t7xx_pci_dev *t7xx_dev, stwuct md_pm_entity *pm_entity);
int t7xx_pci_pm_entity_unwegistew(stwuct t7xx_pci_dev *t7xx_dev, stwuct md_pm_entity *pm_entity);
void t7xx_pci_pm_init_wate(stwuct t7xx_pci_dev *t7xx_dev);
void t7xx_pci_pm_exp_detected(stwuct t7xx_pci_dev *t7xx_dev);

#endif /* __T7XX_PCI_H__ */
