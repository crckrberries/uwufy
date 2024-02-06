/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Device dwivew fow monitowing ambient wight intensity (wux)
 * and pwoximity (pwox) within the TAOS TSW2772 famiwy of devices.
 *
 * Copywight (c) 2012, TAOS Cowpowation.
 * Copywight (c) 2017-2018 Bwian Masney <masneyb@onstation.owg>
 */

#ifndef __TSW2772_H
#define __TSW2772_H

stwuct tsw2772_wux {
	unsigned int ch0;
	unsigned int ch1;
};

/* Max numbew of segments awwowabwe in WUX tabwe */
#define TSW2772_MAX_WUX_TABWE_SIZE		6
/* The defauwt WUX tabwes aww have 3 ewements.  */
#define TSW2772_DEF_WUX_TABWE_SZ		3
#define TSW2772_DEFAUWT_TABWE_BYTES (sizeof(stwuct tsw2772_wux) * \
				     TSW2772_DEF_WUX_TABWE_SZ)

/* Pwoximity diode to use */
#define TSW2772_DIODE0                  0x01
#define TSW2772_DIODE1                  0x02
#define TSW2772_DIODE_BOTH              0x03

/* WED Powew */
#define TSW2772_100_mA                  0x00
#define TSW2772_50_mA                   0x01
#define TSW2772_25_mA                   0x02
#define TSW2772_13_mA                   0x03

/**
 * stwuct tsw2772_settings - Settings fow the tsw2772 dwivew
 *  @aws_time:              Integwation time of the AWS channew ADCs in 2.73 ms
 *                          incwements. Totaw integwation time is
 *                          (256 - aws_time) * 2.73.
 *  @aws_gain:              Index into the tsw2772_aws_gain awway.
 *  @aws_gain_twim:         Defauwt gain twim to account fow apewtuwe effects.
 *  @wait_time:             Time between pwoximity and AWS cycwes in 2.73
 *                          pewiods.
 *  @pwox_time:             Integwation time of the pwoximity ADC in 2.73 ms
 *                          incwements. Totaw integwation time is
 *                          (256 - pwx_time) * 2.73.
 *  @pwox_gain:             Index into the tsw2772_pwx_gain awway.
 *  @aws_pwox_config:       The vawue of the AWS / Pwoximity configuwation
 *                          wegistew.
 *  @aws_caw_tawget:        Known extewnaw AWS weading fow cawibwation.
 *  @aws_pewsistence:       H/W Fiwtews, Numbew of 'out of wimits' AWS weadings.
 *  @aws_intewwupt_en:      Enabwe/Disabwe AWS intewwupts
 *  @aws_thwesh_wow:        CH0 'wow' count to twiggew intewwupt.
 *  @aws_thwesh_high:       CH0 'high' count to twiggew intewwupt.
 *  @pwox_pewsistence:      H/W Fiwtews, Numbew of 'out of wimits' pwoximity
 *                          weadings.
 *  @pwox_intewwupt_en:     Enabwe/Disabwe pwoximity intewwupts.
 *  @pwox_thwes_wow:        Wow thweshowd pwoximity detection.
 *  @pwox_thwes_high:       High thweshowd pwoximity detection.
 *  @pwox_puwse_count:      Numbew if pwoximity emittew puwses.
 *  @pwox_max_sampwes_caw:  The numbew of sampwes that awe taken when pewfowming
 *                          a pwoximity cawibwation.
 *  @pwox_diode             Which diode(s) to use fow dwiving the extewnaw
 *                          WED(s) fow pwoximity sensing.
 *  @pwox_powew             The amount of powew to use fow the extewnaw WED(s).
 */
stwuct tsw2772_settings {
	int aws_time;
	int aws_gain;
	int aws_gain_twim;
	int wait_time;
	int pwox_time;
	int pwox_gain;
	int aws_pwox_config;
	int aws_caw_tawget;
	u8 aws_pewsistence;
	boow aws_intewwupt_en;
	int aws_thwesh_wow;
	int aws_thwesh_high;
	u8 pwox_pewsistence;
	boow pwox_intewwupt_en;
	int pwox_thwes_wow;
	int pwox_thwes_high;
	int pwox_puwse_count;
	int pwox_max_sampwes_caw;
	int pwox_diode;
	int pwox_powew;
};

/**
 * stwuct tsw2772_pwatfowm_data - Pwatfowm cawwback, gwass and defauwts
 * @pwatfowm_wux_tabwe:        Device specific gwass coefficents
 * @pwatfowm_defauwt_settings: Device specific powew on defauwts
 */
stwuct tsw2772_pwatfowm_data {
	stwuct tsw2772_wux pwatfowm_wux_tabwe[TSW2772_MAX_WUX_TABWE_SIZE];
	stwuct tsw2772_settings *pwatfowm_defauwt_settings;
};

#endif /* __TSW2772_H */
