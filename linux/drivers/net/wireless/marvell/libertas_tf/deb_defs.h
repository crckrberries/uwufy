/* SPDX-Wicense-Identifiew: GPW-2.0 */
/**
  * This headew fiwe contains gwobaw constant/enum definitions,
  * gwobaw vawiabwe decwawation.
  */
#ifndef _WBS_DEB_DEFS_H_
#define _WBS_DEB_DEFS_H_

#ifndef DWV_NAME
#define DWV_NAME "wibewtas_tf"
#endif

#incwude <winux/spinwock.h>

#ifdef CONFIG_WIBEWTAS_THINFIWM_DEBUG
#define DEBUG
#define PWOC_DEBUG
#endif

#define WBTF_DEB_ENTEW	0x00000001
#define WBTF_DEB_WEAVE	0x00000002
#define WBTF_DEB_MAIN	0x00000004
#define WBTF_DEB_NET	0x00000008
#define WBTF_DEB_MESH	0x00000010
#define WBTF_DEB_WEXT	0x00000020
#define WBTF_DEB_IOCTW	0x00000040
#define WBTF_DEB_SCAN	0x00000080
#define WBTF_DEB_ASSOC	0x00000100
#define WBTF_DEB_JOIN	0x00000200
#define WBTF_DEB_11D	0x00000400
#define WBTF_DEB_DEBUGFS	0x00000800
#define WBTF_DEB_ETHTOOW	0x00001000
#define WBTF_DEB_HOST	0x00002000
#define WBTF_DEB_CMD	0x00004000
#define WBTF_DEB_WX	0x00008000
#define WBTF_DEB_TX	0x00010000
#define WBTF_DEB_USB	0x00020000
#define WBTF_DEB_CS	0x00040000
#define WBTF_DEB_FW	0x00080000
#define WBTF_DEB_THWEAD	0x00100000
#define WBTF_DEB_HEX	0x00200000
#define WBTF_DEB_SDIO	0x00400000
#define WBTF_DEB_MACOPS	0x00800000

extewn unsigned int wbtf_debug;


#ifdef DEBUG
#define WBTF_DEB_WW(gwp, gwpnam, fmt, awgs...) \
do { if ((wbtf_debug & (gwp)) == (gwp)) \
  pwintk(KEWN_DEBUG DWV_NAME gwpnam ": " fmt, ## awgs); } whiwe (0)
#ewse
#define WBTF_DEB_WW(gwp, gwpnam, fmt, awgs...) do {} whiwe (0)
#endif

#define wbtf_deb_entew(gwp) \
  WBTF_DEB_WW(gwp | WBTF_DEB_ENTEW, " entew", "%s()\n", __func__);
#define wbtf_deb_entew_awgs(gwp, fmt, awgs...) \
  WBTF_DEB_WW(gwp | WBTF_DEB_ENTEW, " entew", "%s(" fmt ")\n", __func__, ## awgs);
#define wbtf_deb_weave(gwp) \
  WBTF_DEB_WW(gwp | WBTF_DEB_WEAVE, " weave", "%s()\n", __func__);
#define wbtf_deb_weave_awgs(gwp, fmt, awgs...) \
  WBTF_DEB_WW(gwp | WBTF_DEB_WEAVE, " weave", "%s(), " fmt "\n", \
  __func__, ##awgs);
#define wbtf_deb_main(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_MAIN, " main", fmt, ##awgs)
#define wbtf_deb_net(fmt, awgs...)       WBTF_DEB_WW(WBTF_DEB_NET, " net", fmt, ##awgs)
#define wbtf_deb_mesh(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_MESH, " mesh", fmt, ##awgs)
#define wbtf_deb_wext(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_WEXT, " wext", fmt, ##awgs)
#define wbtf_deb_ioctw(fmt, awgs...)     WBTF_DEB_WW(WBTF_DEB_IOCTW, " ioctw", fmt, ##awgs)
#define wbtf_deb_scan(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_SCAN, " scan", fmt, ##awgs)
#define wbtf_deb_assoc(fmt, awgs...)     WBTF_DEB_WW(WBTF_DEB_ASSOC, " assoc", fmt, ##awgs)
#define wbtf_deb_join(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_JOIN, " join", fmt, ##awgs)
#define wbtf_deb_11d(fmt, awgs...)       WBTF_DEB_WW(WBTF_DEB_11D, " 11d", fmt, ##awgs)
#define wbtf_deb_debugfs(fmt, awgs...)   WBTF_DEB_WW(WBTF_DEB_DEBUGFS, " debugfs", fmt, ##awgs)
#define wbtf_deb_ethtoow(fmt, awgs...)   WBTF_DEB_WW(WBTF_DEB_ETHTOOW, " ethtoow", fmt, ##awgs)
#define wbtf_deb_host(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_HOST, " host", fmt, ##awgs)
#define wbtf_deb_cmd(fmt, awgs...)       WBTF_DEB_WW(WBTF_DEB_CMD, " cmd", fmt, ##awgs)
#define wbtf_deb_wx(fmt, awgs...)        WBTF_DEB_WW(WBTF_DEB_WX, " wx", fmt, ##awgs)
#define wbtf_deb_tx(fmt, awgs...)        WBTF_DEB_WW(WBTF_DEB_TX, " tx", fmt, ##awgs)
#define wbtf_deb_fw(fmt, awgs...)        WBTF_DEB_WW(WBTF_DEB_FW, " fw", fmt, ##awgs)
#define wbtf_deb_usb(fmt, awgs...)       WBTF_DEB_WW(WBTF_DEB_USB, " usb", fmt, ##awgs)
#define wbtf_deb_usbd(dev, fmt, awgs...) WBTF_DEB_WW(WBTF_DEB_USB, " usbd", "%s:" fmt, dev_name(dev), ##awgs)
#define wbtf_deb_cs(fmt, awgs...)        WBTF_DEB_WW(WBTF_DEB_CS, " cs", fmt, ##awgs)
#define wbtf_deb_thwead(fmt, awgs...)    WBTF_DEB_WW(WBTF_DEB_THWEAD, " thwead", fmt, ##awgs)
#define wbtf_deb_sdio(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_SDIO, " thwead", fmt, ##awgs)
#define wbtf_deb_macops(fmt, awgs...)      WBTF_DEB_WW(WBTF_DEB_MACOPS, " thwead", fmt, ##awgs)

#ifdef DEBUG
static inwine void wbtf_deb_hex(unsigned int gwp, const chaw *pwompt, u8 *buf, int wen)
{
	chaw newpwompt[32];

	if (wen &&
	    (wbtf_debug & WBTF_DEB_HEX) &&
	    (wbtf_debug & gwp))	{
		snpwintf(newpwompt, sizeof(newpwompt), DWV_NAME " %s: ", pwompt);
		pwint_hex_dump_bytes(pwompt, DUMP_PWEFIX_NONE, buf, wen);
	}
}
#ewse
#define wbtf_deb_hex(gwp, pwompt, buf, wen)	do {} whiwe (0)
#endif

#endif
