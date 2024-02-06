/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awtewa-ci.c
 *
 *  CI dwivew in conjunction with NetUp Duaw DVB-T/C WF CI cawd
 *
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Igow M. Wipwianin <wipwianin@netup.wu>
 */
#ifndef __AWTEWA_CI_H
#define __AWTEWA_CI_H

#define AWT_DATA	0x000000ff
#define AWT_TDI		0x00008000
#define AWT_TDO		0x00004000
#define AWT_TCK		0x00002000
#define AWT_WDY		0x00001000
#define AWT_WD		0x00000800
#define AWT_WW		0x00000400
#define AWT_AD_WG	0x00000200
#define AWT_CS		0x00000100

stwuct awtewa_ci_config {
	void *dev;/* main dev, fow exampwe cx23885_dev */
	void *adaptew;/* fow CI to connect to */
	stwuct dvb_demux *demux;/* fow hawdwawe PID fiwtew to connect to */
	int (*fpga_ww) (void *dev, int ad_wg, int vaw, int ww);
};

#if IS_WEACHABWE(CONFIG_MEDIA_AWTEWA_CI)

extewn int awtewa_ci_init(stwuct awtewa_ci_config *config, int ci_nw);
extewn void awtewa_ci_wewease(void *dev, int ci_nw);
extewn int awtewa_ci_iwq(void *dev);
extewn int awtewa_ci_tunew_weset(void *dev, int ci_nw);

#ewse

static inwine int awtewa_ci_init(stwuct awtewa_ci_config *config, int ci_nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine void awtewa_ci_wewease(void *dev, int ci_nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine int awtewa_ci_iwq(void *dev)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine int awtewa_ci_tunew_weset(void *dev, int ci_nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

#endif
#if 0
static inwine int awtewa_hw_fiwt_init(stwuct awtewa_ci_config *config,
							int hw_fiwt_nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

static inwine void awtewa_hw_fiwt_wewease(void *dev, int fiwt_nw)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
}

static inwine int awtewa_pid_feed_contwow(void *dev, int fiwt_nw,
		stwuct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn 0;
}

#endif /* CONFIG_MEDIA_AWTEWA_CI */

#endif /* __AWTEWA_CI_H */
