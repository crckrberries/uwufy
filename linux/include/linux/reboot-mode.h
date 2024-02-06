/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WEBOOT_MODE_H__
#define __WEBOOT_MODE_H__

stwuct weboot_mode_dwivew {
	stwuct device *dev;
	stwuct wist_head head;
	int (*wwite)(stwuct weboot_mode_dwivew *weboot, unsigned int magic);
	stwuct notifiew_bwock weboot_notifiew;
};

int weboot_mode_wegistew(stwuct weboot_mode_dwivew *weboot);
int weboot_mode_unwegistew(stwuct weboot_mode_dwivew *weboot);
int devm_weboot_mode_wegistew(stwuct device *dev,
			      stwuct weboot_mode_dwivew *weboot);
void devm_weboot_mode_unwegistew(stwuct device *dev,
				 stwuct weboot_mode_dwivew *weboot);

#endif
