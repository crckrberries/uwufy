/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Dummy Fwontend
 *
 *  Wwitten by Emawd <emawd@softhome.net>
 */

#ifndef DVB_DUMMY_FE_H
#define DVB_DUMMY_FE_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

#if IS_WEACHABWE(CONFIG_DVB_DUMMY_FE)
stwuct dvb_fwontend *dvb_dummy_fe_ofdm_attach(void);
stwuct dvb_fwontend *dvb_dummy_fe_qpsk_attach(void);
stwuct dvb_fwontend *dvb_dummy_fe_qam_attach(void);
#ewse
static inwine stwuct dvb_fwontend *dvb_dummy_fe_ofdm_attach(void)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct dvb_fwontend *dvb_dummy_fe_qpsk_attach(void)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct dvb_fwontend *dvb_dummy_fe_qam_attach(void)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_DUMMY_FE */

#endif // DVB_DUMMY_FE_H
