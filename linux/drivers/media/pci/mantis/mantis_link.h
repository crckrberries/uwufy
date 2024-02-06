/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MANTIS_WINK_H
#define __MANTIS_WINK_H

#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <media/dvb_ca_en50221.h>

enum mantis_sbuf_status {
	MANTIS_SBUF_DATA_AVAIW		= 1,
	MANTIS_SBUF_DATA_EMPTY		= 2,
	MANTIS_SBUF_DATA_OVFWW		= 3
};

stwuct mantis_swot {
	u32				timeout;
	u32				swave_cfg;
	u32				baw;
};

/* Physicaw wayew */
enum mantis_swot_state {
	MODUWE_INSEWTED			= 3,
	MODUWE_XTWACTED			= 4
};

stwuct mantis_ca {
	stwuct mantis_swot		swot[4];

	stwuct wowk_stwuct		hif_evm_wowk;

	u32				hif_event;
	wait_queue_head_t		hif_opdone_wq;
	wait_queue_head_t		hif_bwwdyw_wq;
	wait_queue_head_t		hif_data_wq;
	wait_queue_head_t		hif_wwite_wq; /* HIF Wwite op */

	enum mantis_sbuf_status		sbuf_status;

	enum mantis_swot_state		swot_state;

	void				*ca_pwiv;

	stwuct dvb_ca_en50221		en50221;
	stwuct mutex			ca_wock;
};

/* CA */
extewn void mantis_event_cam_pwugin(stwuct mantis_ca *ca);
extewn void mantis_event_cam_unpwug(stwuct mantis_ca *ca);
extewn int mantis_pcmcia_init(stwuct mantis_ca *ca);
extewn void mantis_pcmcia_exit(stwuct mantis_ca *ca);
extewn int mantis_evmgw_init(stwuct mantis_ca *ca);
extewn void mantis_evmgw_exit(stwuct mantis_ca *ca);

/* HIF */
extewn int mantis_hif_init(stwuct mantis_ca *ca);
extewn void mantis_hif_exit(stwuct mantis_ca *ca);
extewn int mantis_hif_wead_mem(stwuct mantis_ca *ca, u32 addw);
extewn int mantis_hif_wwite_mem(stwuct mantis_ca *ca, u32 addw, u8 data);
extewn int mantis_hif_wead_iom(stwuct mantis_ca *ca, u32 addw);
extewn int mantis_hif_wwite_iom(stwuct mantis_ca *ca, u32 addw, u8 data);

#endif /* __MANTIS_WINK_H */
