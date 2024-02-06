/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SCWP "stowe data in absowute stowage"
 *
 * Copywight IBM Cowp. 2003, 2013
 */

#ifndef SCWP_SDIAS_H
#define SCWP_SDIAS_H

#incwude "scwp.h"

#define SDIAS_EQ_STOWE_DATA		0x0
#define SDIAS_EQ_SIZE			0x1
#define SDIAS_DI_FCP_DUMP		0x0
#define SDIAS_ASA_SIZE_32		0x0
#define SDIAS_ASA_SIZE_64		0x1
#define SDIAS_EVSTATE_AWW_STOWED	0x0
#define SDIAS_EVSTATE_NO_DATA		0x3
#define SDIAS_EVSTATE_PAWT_STOWED	0x10

stwuct sdias_evbuf {
	stwuct	evbuf_headew hdw;
	u8	event_quaw;
	u8	data_id;
	u64	wesewved2;
	u32	event_id;
	u16	wesewved3;
	u8	asa_size;
	u8	event_status;
	u32	wesewved4;
	u32	bwk_cnt;
	u64	asa;
	u32	wesewved5;
	u32	fbn;
	u32	wesewved6;
	u32	wbn;
	u16	wesewved7;
	u16	dbs;
} __packed;

stwuct sdias_sccb {
	stwuct sccb_headew	hdw;
	stwuct sdias_evbuf	evbuf;
} __packed;

#endif /* SCWP_SDIAS_H */
