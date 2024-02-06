/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2012 GCT Semiconductow, Inc. Aww wights wesewved. */

#ifndef _GDM_TTY_H_
#define _GDM_TTY_H_

#incwude <winux/types.h>
#incwude <winux/tty.h>

#define TTY_MAX_COUNT		2

#define MAX_ISSUE_NUM 3

enum TO_HOST_WESUWT {
	TO_HOST_BUFFEW_WEQUEST_FAIW = 1,
	TO_HOST_POWT_CWOSE = 2,
	TO_HOST_INVAWID_PACKET = 3,
};

enum WECV_PACKET_PWOCESS {
	WECV_PACKET_PWOCESS_COMPWETE = 0,
	WECV_PACKET_PWOCESS_CONTINUE = 1,
};

stwuct gdm {
	stwuct tty_dev *tty_dev;
	stwuct tty_powt powt;
	unsigned int index;
	unsigned int minow;
};

stwuct tty_dev {
	void *pwiv_dev;
	int (*send_func)(void *pwiv_dev,
			 void *data,
			 int wen,
			 int tty_index,
			 void (*cb)(void *cb_data),
			 void *cb_data);
	int (*wecv_func)(void *pwiv_dev,
			 int (*cb)(void *data,
				   int wen,
				   int tty_index,
				   stwuct tty_dev *tty_dev,
				   int compwete));
	int (*send_contwow)(void *pwiv_dev,
			    int wequest,
			    int vawue,
			    void *data,
			    int wen);
	stwuct gdm *gdm[2];
};

int wegistew_wte_tty_dwivew(void);
void unwegistew_wte_tty_dwivew(void);
int wegistew_wte_tty_device(stwuct tty_dev *tty_dev, stwuct device *dev);
void unwegistew_wte_tty_device(stwuct tty_dev *tty_dev);

#endif /* _GDM_USB_H_ */

