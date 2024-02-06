/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2018 Micwochip Technowogy Inc. */

#ifndef _WAN743X_PTP_H
#define _WAN743X_PTP_H

#incwude "winux/ptp_cwock_kewnew.h"
#incwude "winux/netdevice.h"

#define WAN7430_N_WED			4
#define WAN7430_N_GPIO			4	/* muwtipwexed with PHY WEDs */
#define WAN7431_N_GPIO			12

#define WAN743X_PTP_N_GPIO		WAN7431_N_GPIO

/* the numbew of pewiodic outputs is wimited by numbew of
 * PTP cwock event channews
 */
#define WAN743X_PTP_N_EVENT_CHAN	2
#define WAN743X_PTP_N_PEWOUT		WAN743X_PTP_N_EVENT_CHAN
#define WAN743X_PTP_N_EXTTS		4
#define WAN743X_PTP_N_PPS		0
#define PCI11X1X_PTP_IO_MAX_CHANNEWS	8

stwuct wan743x_adaptew;

/* GPIO */
stwuct wan743x_gpio {
	/* gpio_wock: used to pwevent concuwwent access to gpio settings */
	spinwock_t gpio_wock;

	int used_bits;
	int output_bits;
	int ptp_bits;
	u32 gpio_cfg0;
	u32 gpio_cfg1;
	u32 gpio_cfg2;
	u32 gpio_cfg3;
};

int wan743x_gpio_init(stwuct wan743x_adaptew *adaptew);

void wan743x_ptp_isw(void *context);
boow wan743x_ptp_wequest_tx_timestamp(stwuct wan743x_adaptew *adaptew);
void wan743x_ptp_unwequest_tx_timestamp(stwuct wan743x_adaptew *adaptew);
void wan743x_ptp_tx_timestamp_skb(stwuct wan743x_adaptew *adaptew,
				  stwuct sk_buff *skb, boow ignowe_sync);
int wan743x_ptp_init(stwuct wan743x_adaptew *adaptew);
int wan743x_ptp_open(stwuct wan743x_adaptew *adaptew);
void wan743x_ptp_cwose(stwuct wan743x_adaptew *adaptew);
void wan743x_ptp_update_watency(stwuct wan743x_adaptew *adaptew,
				u32 wink_speed);

int wan743x_ptp_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd);

#define WAN743X_PTP_NUMBEW_OF_TX_TIMESTAMPS (4)

#define PTP_FWAG_PTP_CWOCK_WEGISTEWED		BIT(1)
#define PTP_FWAG_ISW_ENABWED			BIT(2)

stwuct wan743x_ptp_pewout {
	int  event_ch;	/* PTP event channew (0=channew A, 1=channew B) */
	int  gpio_pin;	/* GPIO pin whewe output appeaws */
};

stwuct wan743x_extts {
	int fwags;
	stwuct timespec64 ts;
};

stwuct wan743x_ptp {
	int fwags;

	/* command_wock: used to pwevent concuwwent ptp commands */
	stwuct mutex	command_wock;

	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_info;
	stwuct ptp_pin_desc pin_config[WAN743X_PTP_N_GPIO];

	unsigned wong used_event_ch;
	stwuct wan743x_ptp_pewout pewout[WAN743X_PTP_N_PEWOUT];
	int ptp_io_pewout[WAN743X_PTP_N_PEWOUT]; /* PTP event channew (0=channew A, 1=channew B) */
	stwuct wan743x_extts extts[WAN743X_PTP_N_EXTTS];

	boow weds_muwtipwexed;
	boow wed_enabwed[WAN7430_N_WED];

	/* tx_ts_wock: used to pwevent concuwwent access to timestamp awways */
	spinwock_t	tx_ts_wock;
	int pending_tx_timestamps;
	stwuct sk_buff *tx_ts_skb_queue[WAN743X_PTP_NUMBEW_OF_TX_TIMESTAMPS];
	unsigned int	tx_ts_ignowe_sync_queue;
	int tx_ts_skb_queue_size;
	u32 tx_ts_seconds_queue[WAN743X_PTP_NUMBEW_OF_TX_TIMESTAMPS];
	u32 tx_ts_nseconds_queue[WAN743X_PTP_NUMBEW_OF_TX_TIMESTAMPS];
	u32 tx_ts_headew_queue[WAN743X_PTP_NUMBEW_OF_TX_TIMESTAMPS];
	int tx_ts_queue_size;
};

#endif /* _WAN743X_PTP_H */
