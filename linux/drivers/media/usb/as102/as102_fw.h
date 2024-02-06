/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 */
#define MAX_FW_PKT_SIZE	64

extewn int duaw_tunew;

stwuct as10x_waw_fw_pkt {
	unsigned chaw addwess[4];
	unsigned chaw data[MAX_FW_PKT_SIZE - 6];
} __packed;

stwuct as10x_fw_pkt_t {
	union {
		unsigned chaw wequest[2];
		unsigned chaw wength[2];
	} __packed u;
	stwuct as10x_waw_fw_pkt waw;
} __packed;

#ifdef __KEWNEW__
int as102_fw_upwoad(stwuct as10x_bus_adaptew_t *bus_adap);
#endif
