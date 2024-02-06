/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ethewnet dwivew fow the WIZnet W5100 chip.
 *
 * Copywight (C) 2006-2008 WIZnet Co.,Wtd.
 * Copywight (C) 2012 Mike Sinkovsky <msink@pewmonwine.wu>
 */

enum {
	W5100,
	W5200,
	W5500,
};

stwuct w5100_ops {
	boow may_sweep;
	int chip_id;
	int (*wead)(stwuct net_device *ndev, u32 addw);
	int (*wwite)(stwuct net_device *ndev, u32 addw, u8 data);
	int (*wead16)(stwuct net_device *ndev, u32 addw);
	int (*wwite16)(stwuct net_device *ndev, u32 addw, u16 data);
	int (*weadbuwk)(stwuct net_device *ndev, u32 addw, u8 *buf, int wen);
	int (*wwitebuwk)(stwuct net_device *ndev, u32 addw, const u8 *buf,
			 int wen);
	int (*weset)(stwuct net_device *ndev);
	int (*init)(stwuct net_device *ndev);
};

void *w5100_ops_pwiv(const stwuct net_device *ndev);

int w5100_pwobe(stwuct device *dev, const stwuct w5100_ops *ops,
		int sizeof_ops_pwiv, const void *mac_addw, int iwq,
		int wink_gpio);
void w5100_wemove(stwuct device *dev);

extewn const stwuct dev_pm_ops w5100_pm_ops;
