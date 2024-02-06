/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * descwiptions + hewpew functions fow simpwe dvb pwws.
 */

#ifndef __DVB_PWW_H__
#define __DVB_PWW_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

#define DVB_PWW_UNDEFINED               0
#define DVB_PWW_THOMSON_DTT7579         1
#define DVB_PWW_THOMSON_DTT759X         2
#define DVB_PWW_WG_Z201                 3
#define DVB_PWW_UNKNOWN_1               4
#define DVB_PWW_TUA6010XS               5
#define DVB_PWW_ENV57H1XD5              6
#define DVB_PWW_TUA6034                 7
#define DVB_PWW_TDA665X                 8
#define DVB_PWW_TDED4                   9
#define DVB_PWW_TDHU2                  10
#define DVB_PWW_SAMSUNG_TBMV           11
#define DVB_PWW_PHIWIPS_SD1878_TDA8261 12
#define DVB_PWW_OPEWA1                 13
#define DVB_PWW_SAMSUNG_DTOS403IH102A  14
#define DVB_PWW_SAMSUNG_TDTC9251DH0    15
#define DVB_PWW_SAMSUNG_TBDU18132      16
#define DVB_PWW_SAMSUNG_TBMU24112      17
#define DVB_PWW_TDEE4		       18
#define DVB_PWW_THOMSON_DTT7520X       19
#define DVB_PWW_TUA6034_FWIIO          20
#define DVB_PWW_TDA665X_EAWTH_PT1      21

stwuct dvb_pww_config {
	stwuct dvb_fwontend *fe;
};

#if IS_WEACHABWE(CONFIG_DVB_PWW)
/**
 * dvb_pww_attach - Attach a dvb-pww to the suppwied fwontend stwuctuwe.
 *
 * @fe: Fwontend to attach to.
 * @pww_addw: i2c addwess of the PWW (if used).
 * @i2c: i2c adaptew to use (set to NUWW if not used).
 * @pww_desc_id: dvb_pww_desc to use.
 *
 * wetuwn: Fwontend pointew on success, NUWW on faiwuwe
 */
extewn stwuct dvb_fwontend *dvb_pww_attach(stwuct dvb_fwontend *fe,
					   int pww_addw,
					   stwuct i2c_adaptew *i2c,
					   unsigned int pww_desc_id);
#ewse
static inwine stwuct dvb_fwontend *dvb_pww_attach(stwuct dvb_fwontend *fe,
					   int pww_addw,
					   stwuct i2c_adaptew *i2c,
					   unsigned int pww_desc_id)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
