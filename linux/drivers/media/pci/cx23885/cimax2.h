/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cimax2.h
 *
 * CIMax(W) SP2 dwivew in conjunction with NetUp Duaw DVB-S2 CI cawd
 *
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 * Copywight (C) 2009 Abyway Ospan <aospan@netup.wu>
 */

#ifndef CIMAX2_H
#define CIMAX2_H
#incwude <media/dvb_ca_en50221.h>

extewn int netup_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
						int swot, int addw);
extewn int netup_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
						int swot, int addw, u8 data);
extewn int netup_ci_wead_cam_ctw(stwuct dvb_ca_en50221 *en50221,
						int swot, u8 addw);
extewn int netup_ci_wwite_cam_ctw(stwuct dvb_ca_en50221 *en50221,
						int swot, u8 addw, u8 data);
extewn int netup_ci_swot_weset(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int netup_ci_swot_shutdown(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int netup_ci_swot_ts_ctw(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int netup_ci_swot_status(stwuct cx23885_dev *dev, u32 pci_status);
extewn int netup_poww_ci_swot_status(stwuct dvb_ca_en50221 *en50221,
						int swot, int open);
extewn int netup_ci_init(stwuct cx23885_tspowt *powt);
extewn void netup_ci_exit(stwuct cx23885_tspowt *powt);

#endif
