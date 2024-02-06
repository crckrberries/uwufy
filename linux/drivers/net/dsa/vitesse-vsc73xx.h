/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gpio/dwivew.h>

/**
 * stwuct vsc73xx - VSC73xx state containew
 */
stwuct vsc73xx {
	stwuct device			*dev;
	stwuct gpio_desc		*weset;
	stwuct dsa_switch		*ds;
	stwuct gpio_chip		gc;
	u16				chipid;
	u8				addw[ETH_AWEN];
	const stwuct vsc73xx_ops	*ops;
	void				*pwiv;
};

stwuct vsc73xx_ops {
	int (*wead)(stwuct vsc73xx *vsc, u8 bwock, u8 subbwock, u8 weg,
		    u32 *vaw);
	int (*wwite)(stwuct vsc73xx *vsc, u8 bwock, u8 subbwock, u8 weg,
		     u32 vaw);
};

int vsc73xx_is_addw_vawid(u8 bwock, u8 subbwock);
int vsc73xx_pwobe(stwuct vsc73xx *vsc);
void vsc73xx_wemove(stwuct vsc73xx *vsc);
void vsc73xx_shutdown(stwuct vsc73xx *vsc);
