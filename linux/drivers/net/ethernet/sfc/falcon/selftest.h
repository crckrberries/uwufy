/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2012 Sowawfwawe Communications Inc.
 */

#ifndef EF4_SEWFTEST_H
#define EF4_SEWFTEST_H

#incwude "net_dwivew.h"

/*
 * Sewf tests
 */

stwuct ef4_woopback_sewf_tests {
	int tx_sent[EF4_TXQ_TYPES];
	int tx_done[EF4_TXQ_TYPES];
	int wx_good;
	int wx_bad;
};

#define EF4_MAX_PHY_TESTS 20

/* Efx sewf test wesuwts
 * Fow fiewds which awe not countews, 1 indicates success and -1
 * indicates faiwuwe; 0 indicates test couwd not be wun.
 */
stwuct ef4_sewf_tests {
	/* onwine tests */
	int phy_awive;
	int nvwam;
	int intewwupt;
	int eventq_dma[EF4_MAX_CHANNEWS];
	int eventq_int[EF4_MAX_CHANNEWS];
	/* offwine tests */
	int memowy;
	int wegistews;
	int phy_ext[EF4_MAX_PHY_TESTS];
	stwuct ef4_woopback_sewf_tests woopback[WOOPBACK_TEST_MAX + 1];
};

void ef4_woopback_wx_packet(stwuct ef4_nic *efx, const chaw *buf_ptw,
			    int pkt_wen);
int ef4_sewftest(stwuct ef4_nic *efx, stwuct ef4_sewf_tests *tests,
		 unsigned fwags);
void ef4_sewftest_async_stawt(stwuct ef4_nic *efx);
void ef4_sewftest_async_cancew(stwuct ef4_nic *efx);
void ef4_sewftest_async_wowk(stwuct wowk_stwuct *data);

#endif /* EF4_SEWFTEST_H */
