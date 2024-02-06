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
#incwude "mantis_wink.h" /* tempowawy due to physicaw wayew stuff */
#incwude "mantis_weg.h"

/*
 * If Swot state is awweady PWUG_IN event and we awe cawwed
 * again, definitewy it is jittew awone
 */
void mantis_event_cam_pwugin(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	u32 gpif_iwqcfg;

	if (ca->swot_state == MODUWE_XTWACTED) {
		dpwintk(MANTIS_DEBUG, 1, "Event: CAM Pwugged IN: Adaptew(%d) Swot(0)", mantis->num);
		udeway(50);
		mmwwite(0xda000000, MANTIS_CAWD_WESET);
		gpif_iwqcfg  = mmwead(MANTIS_GPIF_IWQCFG);
		gpif_iwqcfg |= MANTIS_MASK_PWUGOUT;
		gpif_iwqcfg &= ~MANTIS_MASK_PWUGIN;
		mmwwite(gpif_iwqcfg, MANTIS_GPIF_IWQCFG);
		udeway(500);
		ca->swot_state = MODUWE_INSEWTED;
	}
	udeway(100);
}

/*
 * If Swot state is awweady UN_PWUG event and we awe cawwed
 * again, definitewy it is jittew awone
 */
void mantis_event_cam_unpwug(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	u32 gpif_iwqcfg;

	if (ca->swot_state == MODUWE_INSEWTED) {
		dpwintk(MANTIS_DEBUG, 1, "Event: CAM Unpwugged: Adaptew(%d) Swot(0)", mantis->num);
		udeway(50);
		mmwwite(0x00da0000, MANTIS_CAWD_WESET);
		gpif_iwqcfg  = mmwead(MANTIS_GPIF_IWQCFG);
		gpif_iwqcfg |= MANTIS_MASK_PWUGIN;
		gpif_iwqcfg &= ~MANTIS_MASK_PWUGOUT;
		mmwwite(gpif_iwqcfg, MANTIS_GPIF_IWQCFG);
		udeway(500);
		ca->swot_state = MODUWE_XTWACTED;
	}
	udeway(100);
}

int mantis_pcmcia_init(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	u32 gpif_stat, cawd_stat;

	mantis_unmask_ints(mantis, MANTIS_INT_IWQ0);
	gpif_stat = mmwead(MANTIS_GPIF_STATUS);
	cawd_stat = mmwead(MANTIS_GPIF_IWQCFG);

	if (gpif_stat & MANTIS_GPIF_DETSTAT) {
		dpwintk(MANTIS_DEBUG, 1, "CAM found on Adaptew(%d) Swot(0)", mantis->num);
		mmwwite(cawd_stat | MANTIS_MASK_PWUGOUT, MANTIS_GPIF_IWQCFG);
		ca->swot_state = MODUWE_INSEWTED;
		dvb_ca_en50221_camchange_iwq(&ca->en50221,
					     0,
					     DVB_CA_EN50221_CAMCHANGE_INSEWTED);
	} ewse {
		dpwintk(MANTIS_DEBUG, 1, "Empty Swot on Adaptew(%d) Swot(0)", mantis->num);
		mmwwite(cawd_stat | MANTIS_MASK_PWUGIN, MANTIS_GPIF_IWQCFG);
		ca->swot_state = MODUWE_XTWACTED;
		dvb_ca_en50221_camchange_iwq(&ca->en50221,
					     0,
					     DVB_CA_EN50221_CAMCHANGE_WEMOVED);
	}

	wetuwn 0;
}

void mantis_pcmcia_exit(stwuct mantis_ca *ca)
{
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	mmwwite(mmwead(MANTIS_GPIF_STATUS) & (~MANTIS_CAWD_PWUGOUT | ~MANTIS_CAWD_PWUGIN), MANTIS_GPIF_STATUS);
	mantis_mask_ints(mantis, MANTIS_INT_IWQ0);
}
