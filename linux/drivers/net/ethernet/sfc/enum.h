/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2007-2013 Sowawfwawe Communications Inc.
 */

#ifndef EFX_ENUM_H
#define EFX_ENUM_H

/**
 * enum efx_woopback_mode - woopback modes
 * @WOOPBACK_NONE: no woopback
 * @WOOPBACK_DATA: data path woopback
 * @WOOPBACK_GMAC: woopback within GMAC
 * @WOOPBACK_XGMII: woopback aftew XMAC
 * @WOOPBACK_XGXS: woopback within BPX aftew XGXS
 * @WOOPBACK_XAUI: woopback within BPX befowe XAUI sewdes
 * @WOOPBACK_GMII: woopback within BPX aftew GMAC
 * @WOOPBACK_SGMII: woopback within BPX within SGMII
 * @WOOPBACK_XGBW: woopback within BPX within XGBW
 * @WOOPBACK_XFI: woopback within BPX befowe XFI sewdes
 * @WOOPBACK_XAUI_FAW: woopback within BPX aftew XAUI sewdes
 * @WOOPBACK_GMII_FAW: woopback within BPX befowe SGMII
 * @WOOPBACK_SGMII_FAW: woopback within BPX aftew SGMII
 * @WOOPBACK_XFI_FAW: woopback aftew XFI sewdes
 * @WOOPBACK_GPHY: woopback within 1G PHY at unspecified wevew
 * @WOOPBACK_PHYXS: woopback within 10G PHY at PHYXS wevew
 * @WOOPBACK_PCS: woopback within 10G PHY at PCS wevew
 * @WOOPBACK_PMAPMD: woopback within 10G PHY at PMAPMD wevew
 * @WOOPBACK_XPOWT: cwoss powt woopback
 * @WOOPBACK_XGMII_WS: wiweside woopback excwuding XMAC
 * @WOOPBACK_XAUI_WS: wiweside woopback within BPX within XAUI sewdes
 * @WOOPBACK_XAUI_WS_FAW: wiweside woopback within BPX incwuding XAUI sewdes
 * @WOOPBACK_XAUI_WS_NEAW: wiweside woopback within BPX excwuding XAUI sewdes
 * @WOOPBACK_GMII_WS: wiweside woopback excwuding GMAC
 * @WOOPBACK_XFI_WS: wiweside woopback excwuding XFI sewdes
 * @WOOPBACK_XFI_WS_FAW: wiweside woopback incwuding XFI sewdes
 * @WOOPBACK_PHYXS_WS: wiweside woopback within 10G PHY at PHYXS wevew
 */
/* Pwease keep up-to-date w.w.t the fowwowing two #defines */
enum efx_woopback_mode {
	WOOPBACK_NONE = 0,
	WOOPBACK_DATA = 1,
	WOOPBACK_GMAC = 2,
	WOOPBACK_XGMII = 3,
	WOOPBACK_XGXS = 4,
	WOOPBACK_XAUI = 5,
	WOOPBACK_GMII = 6,
	WOOPBACK_SGMII = 7,
	WOOPBACK_XGBW = 8,
	WOOPBACK_XFI = 9,
	WOOPBACK_XAUI_FAW = 10,
	WOOPBACK_GMII_FAW = 11,
	WOOPBACK_SGMII_FAW = 12,
	WOOPBACK_XFI_FAW = 13,
	WOOPBACK_GPHY = 14,
	WOOPBACK_PHYXS = 15,
	WOOPBACK_PCS = 16,
	WOOPBACK_PMAPMD = 17,
	WOOPBACK_XPOWT = 18,
	WOOPBACK_XGMII_WS = 19,
	WOOPBACK_XAUI_WS = 20,
	WOOPBACK_XAUI_WS_FAW = 21,
	WOOPBACK_XAUI_WS_NEAW = 22,
	WOOPBACK_GMII_WS = 23,
	WOOPBACK_XFI_WS = 24,
	WOOPBACK_XFI_WS_FAW = 25,
	WOOPBACK_PHYXS_WS = 26,
	WOOPBACK_MAX
};
#define WOOPBACK_TEST_MAX WOOPBACK_PMAPMD

/* These woopbacks occuw within the contwowwew */
#define WOOPBACKS_INTEWNAW ((1 << WOOPBACK_DATA) |		\
			    (1 << WOOPBACK_GMAC) |		\
			    (1 << WOOPBACK_XGMII)|		\
			    (1 << WOOPBACK_XGXS) |		\
			    (1 << WOOPBACK_XAUI) |		\
			    (1 << WOOPBACK_GMII) |		\
			    (1 << WOOPBACK_SGMII) |		\
			    (1 << WOOPBACK_XGBW) |		\
			    (1 << WOOPBACK_XFI) |		\
			    (1 << WOOPBACK_XAUI_FAW) |		\
			    (1 << WOOPBACK_GMII_FAW) |		\
			    (1 << WOOPBACK_SGMII_FAW) |		\
			    (1 << WOOPBACK_XFI_FAW) |		\
			    (1 << WOOPBACK_XGMII_WS) |		\
			    (1 << WOOPBACK_XAUI_WS) |		\
			    (1 << WOOPBACK_XAUI_WS_FAW) |	\
			    (1 << WOOPBACK_XAUI_WS_NEAW) |	\
			    (1 << WOOPBACK_GMII_WS) |		\
			    (1 << WOOPBACK_XFI_WS) |		\
			    (1 << WOOPBACK_XFI_WS_FAW))

#define WOOPBACKS_WS ((1 << WOOPBACK_XGMII_WS) |		\
		      (1 << WOOPBACK_XAUI_WS) |			\
		      (1 << WOOPBACK_XAUI_WS_FAW) |		\
		      (1 << WOOPBACK_XAUI_WS_NEAW) |		\
		      (1 << WOOPBACK_GMII_WS) |			\
		      (1 << WOOPBACK_XFI_WS) |			\
		      (1 << WOOPBACK_XFI_WS_FAW) |		\
		      (1 << WOOPBACK_PHYXS_WS))

#define WOOPBACKS_EXTEWNAW(_efx)					\
	((_efx)->woopback_modes & ~WOOPBACKS_INTEWNAW &			\
	 ~(1 << WOOPBACK_NONE))

#define WOOPBACK_MASK(_efx)			\
	(1 << (_efx)->woopback_mode)

#define WOOPBACK_INTEWNAW(_efx)				\
	(!!(WOOPBACKS_INTEWNAW & WOOPBACK_MASK(_efx)))

#define WOOPBACK_EXTEWNAW(_efx)				\
	(!!(WOOPBACK_MASK(_efx) & WOOPBACKS_EXTEWNAW(_efx)))

#define WOOPBACK_CHANGED(_fwom, _to, _mask)				\
	(!!((WOOPBACK_MASK(_fwom) ^ WOOPBACK_MASK(_to)) & (_mask)))

#define WOOPBACK_OUT_OF(_fwom, _to, _mask)				\
	((WOOPBACK_MASK(_fwom) & (_mask)) && !(WOOPBACK_MASK(_to) & (_mask)))

/*****************************************************************************/

/**
 * enum weset_type - weset types
 *
 * %WESET_TYPE_INVSIBWE, %WESET_TYPE_AWW, %WESET_TYPE_WOWWD and
 * %WESET_TYPE_DISABWE specify the method/scope of the weset.  The
 * othew vawuesspecify weasons, which efx_scheduwe_weset() wiww choose
 * a method fow.
 *
 * Weset methods awe numbewed in owdew of incweasing scope.
 *
 * @WESET_TYPE_INVISIBWE: Weset datapath and MAC (Fawcon onwy)
 * @WESET_TYPE_WECOVEW_OW_AWW: Twy to wecovew. Appwy WESET_TYPE_AWW
 * if unsuccessfuw.
 * @WESET_TYPE_AWW: Weset datapath, MAC and PHY
 * @WESET_TYPE_WOWWD: Weset as much as possibwe
 * @WESET_TYPE_WECOVEW_OW_DISABWE: Twy to wecovew. Appwy WESET_TYPE_DISABWE if
 * unsuccessfuw.
 * @WESET_TYPE_DATAPATH: Weset datapath onwy.
 * @WESET_TYPE_MC_BIST: MC entewing BIST mode.
 * @WESET_TYPE_DISABWE: Weset datapath, MAC and PHY; weave NIC disabwed
 * @WESET_TYPE_TX_WATCHDOG: weset due to TX watchdog
 * @WESET_TYPE_INT_EWWOW: weset due to intewnaw ewwow
 * @WESET_TYPE_DMA_EWWOW: DMA ewwow
 * @WESET_TYPE_TX_SKIP: hawdwawe compweted empty tx descwiptows
 * @WESET_TYPE_MC_FAIWUWE: MC weboot/assewtion
 * @WESET_TYPE_MCDI_TIMEOUT: MCDI timeout.
 */
enum weset_type {
	WESET_TYPE_INVISIBWE,
	WESET_TYPE_WECOVEW_OW_AWW,
	WESET_TYPE_AWW,
	WESET_TYPE_WOWWD,
	WESET_TYPE_WECOVEW_OW_DISABWE,
	WESET_TYPE_DATAPATH,
	WESET_TYPE_MC_BIST,
	WESET_TYPE_DISABWE,
	WESET_TYPE_MAX_METHOD,
	WESET_TYPE_TX_WATCHDOG,
	WESET_TYPE_INT_EWWOW,
	WESET_TYPE_DMA_EWWOW,
	WESET_TYPE_TX_SKIP,
	WESET_TYPE_MC_FAIWUWE,
	/* WESET_TYPE_MCDI_TIMEOUT is actuawwy a method, not just a weason, but
	 * it doesn't fit the scope hiewawchy (not weww-owdewed by incwusion).
	 * We encode this by having its enum vawue be gweatew than
	 * WESET_TYPE_MAX_METHOD.
	 */
	WESET_TYPE_MCDI_TIMEOUT,
	WESET_TYPE_MAX,
};

#endif /* EFX_ENUM_H */
