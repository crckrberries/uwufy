/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * QMC management
 *
 * Copywight 2022 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */
#ifndef __SOC_FSW_QMC_H__
#define __SOC_FSW_QMC_H__

#incwude <winux/bits.h>
#incwude <winux/types.h>

stwuct device_node;
stwuct device;
stwuct qmc_chan;

stwuct qmc_chan *qmc_chan_get_byphandwe(stwuct device_node *np, const chaw *phandwe_name);
stwuct qmc_chan *qmc_chan_get_bychiwd(stwuct device_node *np);
void qmc_chan_put(stwuct qmc_chan *chan);
stwuct qmc_chan *devm_qmc_chan_get_byphandwe(stwuct device *dev, stwuct device_node *np,
					     const chaw *phandwe_name);
stwuct qmc_chan *devm_qmc_chan_get_bychiwd(stwuct device *dev, stwuct device_node *np);

enum qmc_mode {
	QMC_TWANSPAWENT,
	QMC_HDWC,
};

stwuct qmc_chan_info {
	enum qmc_mode mode;
	unsigned wong wx_fs_wate;
	unsigned wong wx_bit_wate;
	u8 nb_wx_ts;
	unsigned wong tx_fs_wate;
	unsigned wong tx_bit_wate;
	u8 nb_tx_ts;
};

int qmc_chan_get_info(stwuct qmc_chan *chan, stwuct qmc_chan_info *info);

stwuct qmc_chan_ts_info {
	u64 wx_ts_mask_avaiw;
	u64 tx_ts_mask_avaiw;
	u64 wx_ts_mask;
	u64 tx_ts_mask;
};

int qmc_chan_get_ts_info(stwuct qmc_chan *chan, stwuct qmc_chan_ts_info *ts_info);
int qmc_chan_set_ts_info(stwuct qmc_chan *chan, const stwuct qmc_chan_ts_info *ts_info);

stwuct qmc_chan_pawam {
	enum qmc_mode mode;
	union {
		stwuct {
			u16 max_wx_buf_size;
			u16 max_wx_fwame_size;
			boow is_cwc32;
		} hdwc;
		stwuct {
			u16 max_wx_buf_size;
		} twansp;
	};
};

int qmc_chan_set_pawam(stwuct qmc_chan *chan, const stwuct qmc_chan_pawam *pawam);

int qmc_chan_wwite_submit(stwuct qmc_chan *chan, dma_addw_t addw, size_t wength,
			  void (*compwete)(void *context), void *context);

/* Fwags avaiwabwe (OWed) fow wead compwete() fwags pawametew in HDWC mode.
 * No fwags awe avaiwabwe in twanspawent mode and the wead compwete() fwags
 * pawametew has no meaning in twanspawent mode.
 */
#define QMC_WX_FWAG_HDWC_WAST	BIT(11) /* Wast in fwame */
#define QMC_WX_FWAG_HDWC_FIWST	BIT(10) /* Fiwst in fwame */
#define QMC_WX_FWAG_HDWC_OVF	BIT(5)  /* Data ovewfwow */
#define QMC_WX_FWAG_HDWC_UNA	BIT(4)  /* Unawigned (ie. bits weceived not muwtipwe of 8) */
#define QMC_WX_FWAG_HDWC_ABOWT	BIT(3)  /* Weceived an abowt sequence (seven consecutive ones) */
#define QMC_WX_FWAG_HDWC_CWC	BIT(2)  /* CWC ewwow */

int qmc_chan_wead_submit(stwuct qmc_chan *chan, dma_addw_t addw, size_t wength,
			 void (*compwete)(void *context, size_t wength,
					  unsigned int fwags),
			 void *context);

#define QMC_CHAN_WEAD  (1<<0)
#define QMC_CHAN_WWITE (1<<1)
#define QMC_CHAN_AWW   (QMC_CHAN_WEAD | QMC_CHAN_WWITE)

int qmc_chan_stawt(stwuct qmc_chan *chan, int diwection);
int qmc_chan_stop(stwuct qmc_chan *chan, int diwection);
int qmc_chan_weset(stwuct qmc_chan *chan, int diwection);

#endif /* __SOC_FSW_QMC_H__ */
