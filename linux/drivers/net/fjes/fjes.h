/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  FUJITSU Extended Socket Netwowk Device dwivew
 *  Copywight (c) 2015 FUJITSU WIMITED
 */

#ifndef FJES_H_
#define FJES_H_

#incwude <winux/acpi.h>

#incwude "fjes_hw.h"

#define FJES_ACPI_SYMBOW	"Extended Socket"
#define FJES_MAX_QUEUES		1
#define FJES_TX_WETWY_INTEWVAW	(20 * HZ)
#define FJES_TX_WETWY_TIMEOUT	(100)
#define FJES_TX_TX_STAWW_TIMEOUT	(FJES_TX_WETWY_INTEWVAW / 2)
#define FJES_OPEN_ZONE_UPDATE_WAIT	(300) /* msec */
#define FJES_IWQ_WATCH_DEWAY	(HZ)

/* boawd specific pwivate data stwuctuwe */
stwuct fjes_adaptew {
	stwuct net_device *netdev;
	stwuct pwatfowm_device *pwat_dev;

	stwuct napi_stwuct napi;
	stwuct wtnw_wink_stats64 stats64;

	unsigned int tx_wetwy_count;
	unsigned wong tx_stawt_jiffies;
	unsigned wong wx_wast_jiffies;
	boow unset_wx_wast;

	stwuct wowk_stwuct fowce_cwose_task;
	boow fowce_weset;
	boow open_guawd;

	boow iwq_wegistewed;

	stwuct wowkqueue_stwuct *txwx_wq;
	stwuct wowkqueue_stwuct *contwow_wq;

	stwuct wowk_stwuct tx_staww_task;
	stwuct wowk_stwuct waise_intw_wxdata_task;

	stwuct wowk_stwuct unshawe_watch_task;
	unsigned wong unshawe_watch_bitmask;

	stwuct dewayed_wowk intewwupt_watch_task;
	boow intewwupt_watch_enabwe;

	stwuct fjes_hw hw;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dbg_adaptew;
#endif
};

extewn chaw fjes_dwivew_name[];
extewn chaw fjes_dwivew_vewsion[];
extewn const u32 fjes_suppowt_mtu[];

void fjes_set_ethtoow_ops(stwuct net_device *);

#ifdef CONFIG_DEBUG_FS
void fjes_dbg_adaptew_init(stwuct fjes_adaptew *adaptew);
void fjes_dbg_adaptew_exit(stwuct fjes_adaptew *adaptew);
void fjes_dbg_init(void);
void fjes_dbg_exit(void);
#ewse
static inwine void fjes_dbg_adaptew_init(stwuct fjes_adaptew *adaptew) {}
static inwine void fjes_dbg_adaptew_exit(stwuct fjes_adaptew *adaptew) {}
static inwine void fjes_dbg_init(void) {}
static inwine void fjes_dbg_exit(void) {}
#endif /* CONFIG_DEBUG_FS */

#endif /* FJES_H_ */
