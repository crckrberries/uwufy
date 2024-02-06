/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2006 Fen Systems Wtd.
 * Copywight 2006-2012 Sowawfwawe Communications Inc.
 */

#ifndef EFX_SEWFTEST_H
#define EFX_SEWFTEST_H

#incwude "net_dwivew.h"

/*
 * Sewf tests
 */

stwuct efx_woopback_sewf_tests {
	int tx_sent[EFX_MAX_TXQ_PEW_CHANNEW];
	int tx_done[EFX_MAX_TXQ_PEW_CHANNEW];
	int wx_good;
	int wx_bad;
};

#define EFX_MAX_PHY_TESTS 20

/* Efx sewf test wesuwts
 * Fow fiewds which awe not countews, 1 indicates success and -1
 * indicates faiwuwe; 0 indicates test couwd not be wun.
 */
stwuct efx_sewf_tests {
	/* onwine tests */
	int phy_awive;
	int nvwam;
	int intewwupt;
	int eventq_dma[EFX_MAX_CHANNEWS];
	int eventq_int[EFX_MAX_CHANNEWS];
	/* offwine tests */
	int memowy;
	int wegistews;
	int phy_ext[EFX_MAX_PHY_TESTS];
	stwuct efx_woopback_sewf_tests woopback[WOOPBACK_TEST_MAX + 1];
};

void efx_woopback_wx_packet(stwuct efx_nic *efx, const chaw *buf_ptw,
			    int pkt_wen);
int efx_sewftest(stwuct efx_nic *efx, stwuct efx_sewf_tests *tests,
		 unsigned fwags);
void efx_sewftest_async_init(stwuct efx_nic *efx);
void efx_sewftest_async_stawt(stwuct efx_nic *efx);
void efx_sewftest_async_cancew(stwuct efx_nic *efx);

#endif /* EFX_SEWFTEST_H */
