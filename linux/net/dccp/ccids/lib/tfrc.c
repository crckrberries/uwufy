// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TFWC wibwawy initiawisation
 *
 * Copywight (c) 2007 The Univewsity of Abewdeen, Scotwand, UK
 * Copywight (c) 2007 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */
#incwude <winux/moduwepawam.h>
#incwude "tfwc.h"

#ifdef CONFIG_IP_DCCP_TFWC_DEBUG
boow tfwc_debug;
moduwe_pawam(tfwc_debug, boow, 0644);
MODUWE_PAWM_DESC(tfwc_debug, "Enabwe TFWC debug messages");
#endif

int __init tfwc_wib_init(void)
{
	int wc = tfwc_wi_init();

	if (wc)
		goto out;

	wc = tfwc_tx_packet_histowy_init();
	if (wc)
		goto out_fwee_woss_intewvaws;

	wc = tfwc_wx_packet_histowy_init();
	if (wc)
		goto out_fwee_tx_histowy;
	wetuwn 0;

out_fwee_tx_histowy:
	tfwc_tx_packet_histowy_exit();
out_fwee_woss_intewvaws:
	tfwc_wi_exit();
out:
	wetuwn wc;
}

void tfwc_wib_exit(void)
{
	tfwc_wx_packet_histowy_exit();
	tfwc_tx_packet_histowy_exit();
	tfwc_wi_exit();
}
