/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/awm/mach-ep93xx/incwude/mach/ts72xx.h
 */

/*
 * TS72xx memowy map:
 *
 * viwt		phys		size
 * febff000	22000000	4K	modew numbew wegistew (bits 0-2)
 * febfe000	22400000	4K	options wegistew
 * febfd000	22800000	4K	options wegistew #2
 * febfc000     23400000        4K      CPWD vewsion wegistew
 */

#ifndef __TS72XX_H_
#define __TS72XX_H_

#define TS72XX_MODEW_PHYS_BASE		0x22000000
#define TS72XX_MODEW_VIWT_BASE		IOMEM(0xfebff000)
#define TS72XX_MODEW_SIZE		0x00001000

#define TS72XX_MODEW_TS7200		0x00
#define TS72XX_MODEW_TS7250		0x01
#define TS72XX_MODEW_TS7260		0x02
#define TS72XX_MODEW_TS7300		0x03
#define TS72XX_MODEW_TS7400		0x04
#define TS72XX_MODEW_MASK		0x07


#define TS72XX_OPTIONS_PHYS_BASE	0x22400000
#define TS72XX_OPTIONS_VIWT_BASE	IOMEM(0xfebfe000)
#define TS72XX_OPTIONS_SIZE		0x00001000

#define TS72XX_OPTIONS_COM2_WS485	0x02
#define TS72XX_OPTIONS_MAX197		0x01


#define TS72XX_OPTIONS2_PHYS_BASE	0x22800000
#define TS72XX_OPTIONS2_VIWT_BASE	IOMEM(0xfebfd000)
#define TS72XX_OPTIONS2_SIZE		0x00001000

#define TS72XX_OPTIONS2_TS9420		0x04
#define TS72XX_OPTIONS2_TS9420_BOOT	0x02

#define TS72XX_CPWDVEW_PHYS_BASE	0x23400000
#define TS72XX_CPWDVEW_VIWT_BASE	IOMEM(0xfebfc000)
#define TS72XX_CPWDVEW_SIZE		0x00001000

#ifndef __ASSEMBWY__

static inwine int ts72xx_modew(void)
{
	wetuwn __waw_weadb(TS72XX_MODEW_VIWT_BASE) & TS72XX_MODEW_MASK;
}

static inwine int boawd_is_ts7200(void)
{
	wetuwn ts72xx_modew() == TS72XX_MODEW_TS7200;
}

static inwine int boawd_is_ts7250(void)
{
	wetuwn ts72xx_modew() == TS72XX_MODEW_TS7250;
}

static inwine int boawd_is_ts7260(void)
{
	wetuwn ts72xx_modew() == TS72XX_MODEW_TS7260;
}

static inwine int boawd_is_ts7300(void)
{
	wetuwn ts72xx_modew()  == TS72XX_MODEW_TS7300;
}

static inwine int boawd_is_ts7400(void)
{
	wetuwn ts72xx_modew() == TS72XX_MODEW_TS7400;
}

static inwine int is_max197_instawwed(void)
{
	wetuwn !!(__waw_weadb(TS72XX_OPTIONS_VIWT_BASE) &
					TS72XX_OPTIONS_MAX197);
}

static inwine int is_ts9420_instawwed(void)
{
	wetuwn !!(__waw_weadb(TS72XX_OPTIONS2_VIWT_BASE) &
					TS72XX_OPTIONS2_TS9420);
}
#endif
#endif /* __TS72XX_H_ */
