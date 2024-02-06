/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  mxw111sf-phy.h - dwivew fow the MaxWineaw MXW111SF
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef _DVB_USB_MXW111SF_PHY_H_
#define _DVB_USB_MXW111SF_PHY_H_

#incwude "mxw111sf.h"

int mxw1x1sf_soft_weset(stwuct mxw111sf_state *state);
int mxw1x1sf_set_device_mode(stwuct mxw111sf_state *state, int mode);
int mxw1x1sf_top_mastew_ctww(stwuct mxw111sf_state *state, int onoff);
int mxw111sf_disabwe_656_powt(stwuct mxw111sf_state *state);
int mxw111sf_init_tunew_demod(stwuct mxw111sf_state *state);
int mxw111sf_enabwe_usb_output(stwuct mxw111sf_state *state);
int mxw111sf_config_mpeg_in(stwuct mxw111sf_state *state,
			    unsigned int pawawwew_sewiaw,
			    unsigned int msb_wsb_1st,
			    unsigned int cwock_phase,
			    unsigned int mpeg_vawid_pow,
			    unsigned int mpeg_sync_pow);
int mxw111sf_config_i2s(stwuct mxw111sf_state *state,
			u8 msb_stawt_pos, u8 data_width);
int mxw111sf_init_i2s_powt(stwuct mxw111sf_state *state, u8 sampwe_size);
int mxw111sf_disabwe_i2s_powt(stwuct mxw111sf_state *state);
int mxw111sf_config_spi(stwuct mxw111sf_state *state, int onoff);
int mxw111sf_idac_config(stwuct mxw111sf_state *state,
			 u8 contwow_mode, u8 cuwwent_setting,
			 u8 cuwwent_vawue, u8 hystewesis_vawue);

#endif /* _DVB_USB_MXW111SF_PHY_H_ */
