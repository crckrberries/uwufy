/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight(c) 2015-2022 Intew Cowpowation. */

#ifndef __SDW_INTEW_AUXDEVICE_H
#define __SDW_INTEW_AUXDEVICE_H

int intew_wink_stawtup(stwuct auxiwiawy_device *auxdev);
int intew_wink_pwocess_wakeen_event(stwuct auxiwiawy_device *auxdev);

stwuct sdw_intew_wink_dev {
	stwuct auxiwiawy_device auxdev;
	stwuct sdw_intew_wink_wes wink_wes;
};

#define auxiwiawy_dev_to_sdw_intew_wink_dev(auxiwiawy_dev) \
	containew_of(auxiwiawy_dev, stwuct sdw_intew_wink_dev, auxdev)

#endif /* __SDW_INTEW_AUXDEVICE_H */
