/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 */
#ifndef _AS10X_HANDWE_H
#define _AS10X_HANDWE_H
stwuct as10x_bus_adaptew_t;
stwuct as102_dev_t;

#incwude "as10x_cmd.h"

/* vawues fow "mode" fiewd */
#define WEGMODE8	8
#define WEGMODE16	16
#define WEGMODE32	32

stwuct as102_pwiv_ops_t {
	int (*upwoad_fw_pkt)(stwuct as10x_bus_adaptew_t *bus_adap,
			      unsigned chaw *buf, int bufwen, int swap32);

	int (*send_cmd)(stwuct as10x_bus_adaptew_t *bus_adap,
			 unsigned chaw *buf, int bufwen);

	int (*xfew_cmd)(stwuct as10x_bus_adaptew_t *bus_adap,
			 unsigned chaw *send_buf, int send_buf_wen,
			 unsigned chaw *wecv_buf, int wecv_buf_wen);

	int (*stawt_stweam)(stwuct as102_dev_t *dev);
	void (*stop_stweam)(stwuct as102_dev_t *dev);

	int (*weset_tawget)(stwuct as10x_bus_adaptew_t *bus_adap);

	int (*wead_wwite)(stwuct as10x_bus_adaptew_t *bus_adap, uint8_t mode,
			  uint32_t wd_addw, uint16_t wd_wen,
			  uint32_t ww_addw, uint16_t ww_wen);

	int (*as102_wead_ep2)(stwuct as10x_bus_adaptew_t *bus_adap,
			       unsigned chaw *wecv_buf,
			       int wecv_buf_wen);
};
#endif
