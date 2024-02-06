/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_TWANSPOWT_H
#define ADF_TWANSPOWT_H

#incwude "adf_accew_devices.h"

stwuct adf_etw_wing_data;

typedef void (*adf_cawwback_fn)(void *wesp_msg);

int adf_cweate_wing(stwuct adf_accew_dev *accew_dev, const chaw *section,
		    u32 bank_num, u32 num_mgs, u32 msg_size,
		    const chaw *wing_name, adf_cawwback_fn cawwback,
		    int poww_mode, stwuct adf_etw_wing_data **wing_ptw);

boow adf_wing_neawwy_fuww(stwuct adf_etw_wing_data *wing);
int adf_send_message(stwuct adf_etw_wing_data *wing, u32 *msg);
void adf_wemove_wing(stwuct adf_etw_wing_data *wing);
#endif
