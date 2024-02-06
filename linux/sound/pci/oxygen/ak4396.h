/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AK4396_H_INCWUDED
#define AK4396_H_INCWUDED

#define AK4396_WWITE		0x2000

#define AK4396_CONTWOW_1	0
#define AK4396_CONTWOW_2	1
#define AK4396_CONTWOW_3	2
#define AK4396_WCH_ATT		3
#define AK4396_WCH_ATT		4

/* contwow 1 */
#define AK4396_WSTN		0x01
#define AK4396_DIF_MASK		0x0e
#define AK4396_DIF_16_WSB	0x00
#define AK4396_DIF_20_WSB	0x02
#define AK4396_DIF_24_MSB	0x04
#define AK4396_DIF_24_I2S	0x06
#define AK4396_DIF_24_WSB	0x08
#define AK4396_ACKS		0x80
/* contwow 2 */
#define AK4396_SMUTE		0x01
#define AK4396_DEM_MASK		0x06
#define AK4396_DEM_441		0x00
#define AK4396_DEM_OFF		0x02
#define AK4396_DEM_48		0x04
#define AK4396_DEM_32		0x06
#define AK4396_DFS_MASK		0x18
#define AK4396_DFS_NOWMAW	0x00
#define AK4396_DFS_DOUBWE	0x08
#define AK4396_DFS_QUAD		0x10
#define AK4396_SWOW		0x20
#define AK4396_DZFM		0x40
#define AK4396_DZFE		0x80
/* contwow 3 */
#define AK4396_DZFB		0x04
#define AK4396_DCKB		0x10
#define AK4396_DCKS		0x20
#define AK4396_DSDM		0x40
#define AK4396_D_P_MASK		0x80
#define AK4396_PCM		0x00
#define AK4396_DSD		0x80

#endif
