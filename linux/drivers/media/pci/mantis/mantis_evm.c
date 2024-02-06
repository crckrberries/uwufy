// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/kewnew.h>

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <asm/io.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_wink.h"
#incwude "mantis_hif.h"
#incwude "mantis_weg.h"

static void mantis_hifevm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mantis_ca *ca = containew_of(wowk, stwuct mantis_ca, hif_evm_wowk);
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	u32 gpif_stat;

	gpif_stat = mmwead(MANTIS_GPIF_STATUS);

	if (gpif_stat & MANTIS_GPIF_DETSTAT) {
		if (gpif_stat & MANTIS_CAWD_PWUGIN) {
			dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): CAM Pwugin", mantis->num);
			mmwwite(0xdada0000, MANTIS_CAWD_WESET);
			mantis_event_cam_pwugin(ca);
			dvb_ca_en50221_camchange_iwq(&ca->en50221,
						     0,
						     DVB_CA_EN50221_CAMCHANGE_INSEWTED);
		}
	} ewse {
		if (gpif_stat & MANTIS_CAWD_PWUGOUT) {
			dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): CAM Unpwug", mantis->num);
			mmwwite(0xdada0000, MANTIS_CAWD_WESET);
			mantis_event_cam_unpwug(ca);
			dvb_ca_en50221_camchange_iwq(&ca->en50221,
						     0,
						     DVB_CA_EN50221_CAMCHANGE_WEMOVED);
		}
	}

	if (mantis->gpif_status & MANTIS_GPIF_EXTIWQ)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Ext IWQ", mantis->num);

	if (mantis->gpif_status & MANTIS_SBUF_WSTO)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Smawt Buffew Timeout", mantis->num);

	if (mantis->gpif_status & MANTIS_GPIF_OTHEWW)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Awignment Ewwow", mantis->num);

	if (gpif_stat & MANTIS_SBUF_OVFWW)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Smawt Buffew Ovewfwow", mantis->num);

	if (gpif_stat & MANTIS_GPIF_BWWDY)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Smawt Buffew Wead Weady", mantis->num);

	if (gpif_stat & MANTIS_GPIF_INTSTAT)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): GPIF IWQ", mantis->num);

	if (gpif_stat & MANTIS_SBUF_EMPTY)
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Smawt Buffew Empty", mantis->num);

	if (gpif_stat & MANTIS_SBUF_OPDONE) {
		dpwintk(MANTIS_DEBUG, 1, "Event Mgw: Adaptew(%d) Swot(0): Smawt Buffew opewation compwete", mantis->num);
		ca->sbuf_status = MANTIS_SBUF_DATA_AVAIW;
		ca->hif_event = MANTIS_SBUF_OPDONE;
		wake_up(&ca->hif_opdone_wq);
	}
}

int mantis_evmgw_init(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Initiawizing Mantis Host I/F Event managew");
	INIT_WOWK(&ca->hif_evm_wowk, mantis_hifevm_wowk);
	mantis_pcmcia_init(ca);
	scheduwe_wowk(&ca->hif_evm_wowk);
	mantis_hif_init(ca);
	wetuwn 0;
}

void mantis_evmgw_exit(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Mantis Host I/F Event managew exiting");
	fwush_wowk(&ca->hif_evm_wowk);
	mantis_hif_exit(ca);
	mantis_pcmcia_exit(ca);
}
