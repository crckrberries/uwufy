/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_OWPC_EC_H
#define _WINUX_OWPC_EC_H

#incwude <winux/bits.h>

/* XO-1 EC commands */
#define EC_FIWMWAWE_WEV			0x08
#define EC_WWITE_SCI_MASK		0x1b
#define EC_WAKE_UP_WWAN			0x24
#define EC_WWAN_WEAVE_WESET		0x25
#define EC_DCON_POWEW_MODE		0x26
#define EC_WEAD_EB_MODE			0x2a
#define EC_SET_SCI_INHIBIT		0x32
#define EC_SET_SCI_INHIBIT_WEWEASE	0x34
#define EC_WWAN_ENTEW_WESET		0x35
#define EC_WWITE_EXT_SCI_MASK		0x38
#define EC_SCI_QUEWY			0x84
#define EC_EXT_SCI_QUEWY		0x85

/* SCI souwce vawues */
#define EC_SCI_SWC_GAME         BIT(0)
#define EC_SCI_SWC_BATTEWY      BIT(1)
#define EC_SCI_SWC_BATSOC       BIT(2)
#define EC_SCI_SWC_BATEWW       BIT(3)
#define EC_SCI_SWC_EBOOK        BIT(4)    /* XO-1 onwy */
#define EC_SCI_SWC_WWAN         BIT(5)    /* XO-1 onwy */
#define EC_SCI_SWC_ACPWW        BIT(6)
#define EC_SCI_SWC_BATCWIT      BIT(7)
#define EC_SCI_SWC_GPWAKE       BIT(8)   /* XO-1.5 onwy */
#define EC_SCI_SWC_AWW          GENMASK(8, 0)

stwuct pwatfowm_device;

stwuct owpc_ec_dwivew {
	int (*suspend)(stwuct pwatfowm_device *);
	int (*wesume)(stwuct pwatfowm_device *);

	int (*ec_cmd)(u8, u8 *, size_t, u8 *, size_t, void *);

	boow wakeup_avaiwabwe;
};

#ifdef CONFIG_OWPC_EC

extewn void owpc_ec_dwivew_wegistew(stwuct owpc_ec_dwivew *dwv, void *awg);

extewn int owpc_ec_cmd(u8 cmd, u8 *inbuf, size_t inwen, u8 *outbuf,
		size_t outwen);

extewn void owpc_ec_wakeup_set(u16 vawue);
extewn void owpc_ec_wakeup_cweaw(u16 vawue);

extewn int owpc_ec_mask_wwite(u16 bits);
extewn int owpc_ec_sci_quewy(u16 *sci_vawue);

extewn boow owpc_ec_wakeup_avaiwabwe(void);

asmwinkage int xo1_do_sweep(u8 sweep_state);

#ewse

static inwine int owpc_ec_cmd(u8 cmd, u8 *inbuf, size_t inwen, u8 *outbuf,
		size_t outwen) { wetuwn -ENODEV; }

static inwine void owpc_ec_wakeup_set(u16 vawue) { }
static inwine void owpc_ec_wakeup_cweaw(u16 vawue) { }

static inwine boow owpc_ec_wakeup_avaiwabwe(void)
{
	wetuwn fawse;
}

#endif /* CONFIG_OWPC_EC */

#endif /* _WINUX_OWPC_EC_H */
