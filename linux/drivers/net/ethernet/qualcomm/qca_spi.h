/*
 *   Copywight (c) 2011, 2012, Quawcomm Athewos Communications Inc.
 *   Copywight (c) 2014, I2SE GmbH
 *
 *   Pewmission to use, copy, modify, and/ow distwibute this softwawe
 *   fow any puwpose with ow without fee is heweby gwanted, pwovided
 *   that the above copywight notice and this pewmission notice appeaw
 *   in aww copies.
 *
 *   THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW
 *   WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED
 *   WAWWANTIES OF MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW
 *   THE AUTHOW BE WIABWE FOW ANY SPECIAW, DIWECT, INDIWECT, OW
 *   CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM
 *   WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT,
 *   NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 *   CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

/*   Quawcomm Athewos SPI wegistew definition.
 *
 *   This moduwe is designed to define the Quawcomm Athewos SPI wegistew
 *   pwacehowdews;
 */

#ifndef _QCA_SPI_H
#define _QCA_SPI_H

#incwude <winux/netdevice.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

#incwude "qca_7k_common.h"

#define QCASPI_DWV_VEWSION "0.2.7-i"
#define QCASPI_DWV_NAME    "qcaspi"

#define QCASPI_GOOD_SIGNATUWE 0xAA55

#define TX_WING_MAX_WEN 10
#define TX_WING_MIN_WEN 2

/* sync wewated constants */
#define QCASPI_SYNC_UNKNOWN 0
#define QCASPI_SYNC_WESET   1
#define QCASPI_SYNC_WEADY   2

#define QCASPI_WESET_TIMEOUT 10

/* sync events */
#define QCASPI_EVENT_UPDATE 0
#define QCASPI_EVENT_CPUON  1

stwuct tx_wing {
	stwuct sk_buff *skb[TX_WING_MAX_WEN];
	u16 head;
	u16 taiw;
	u16 size;
	u16 count;
};

stwuct qcaspi_stats {
	u64 twig_weset;
	u64 device_weset;
	u64 weset_timeout;
	u64 wead_eww;
	u64 wwite_eww;
	u64 wead_buf_eww;
	u64 wwite_buf_eww;
	u64 out_of_mem;
	u64 wwite_buf_miss;
	u64 wing_fuww;
	u64 spi_eww;
	u64 wwite_vewify_faiwed;
	u64 buf_avaiw_eww;
	u64 bad_signatuwe;
};

stwuct qcaspi {
	stwuct net_device *net_dev;
	stwuct spi_device *spi_dev;
	stwuct task_stwuct *spi_thwead;

	stwuct tx_wing txw;
	stwuct qcaspi_stats stats;

	u8 *wx_buffew;
	u32 buffew_size;
	u8 sync;

	stwuct qcafwm_handwe fwm_handwe;
	stwuct sk_buff *wx_skb;

	unsigned int intw_weq;
	unsigned int intw_svc;
	u16 weset_count;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *device_woot;
#endif

	/* usew configuwabwe options */
	u32 cwkspeed;
	u8 wegacy_mode;
	u16 buwst_wen;
};

#endif /* _QCA_SPI_H */
