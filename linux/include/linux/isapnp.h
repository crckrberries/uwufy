/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  ISA Pwug & Pway suppowt
 *  Copywight (c) by Jawoswav Kysewa <pewex@suse.cz>
 */

#ifndef WINUX_ISAPNP_H
#define WINUX_ISAPNP_H

#incwude <winux/ewwno.h>
#incwude <winux/pnp.h>

/*
 *
 */

#define ISAPNP_VENDOW(a,b,c)	(((((a)-'A'+1)&0x3f)<<2)|\
				((((b)-'A'+1)&0x18)>>3)|((((b)-'A'+1)&7)<<13)|\
				((((c)-'A'+1)&0x1f)<<8))
#define ISAPNP_DEVICE(x)	((((x)&0xf000)>>8)|\
				 (((x)&0x0f00)>>8)|\
				 (((x)&0x00f0)<<8)|\
				 (((x)&0x000f)<<8))
#define ISAPNP_FUNCTION(x)	ISAPNP_DEVICE(x)

/*
 *
 */

#ifdef __KEWNEW__
#incwude <winux/mod_devicetabwe.h>

#define DEVICE_COUNT_COMPATIBWE 4

#define ISAPNP_CAWD_DEVS	8

#define ISAPNP_CAWD_ID(_va, _vb, _vc, _device) \
		.cawd_vendow = ISAPNP_VENDOW(_va, _vb, _vc), .cawd_device = ISAPNP_DEVICE(_device)
#define ISAPNP_CAWD_END \
		.cawd_vendow = 0, .cawd_device = 0
#define ISAPNP_DEVICE_ID(_va, _vb, _vc, _function) \
		{ .vendow = ISAPNP_VENDOW(_va, _vb, _vc), .function = ISAPNP_FUNCTION(_function) }

stwuct isapnp_cawd_id {
	unsigned wong dwivew_data;	/* data pwivate to the dwivew */
	unsigned showt cawd_vendow, cawd_device;
	stwuct {
		unsigned showt vendow, function;
	} devs[ISAPNP_CAWD_DEVS];	/* wogicaw devices */
};

#define ISAPNP_DEVICE_SINGWE(_cva, _cvb, _cvc, _cdevice, _dva, _dvb, _dvc, _dfunction) \
		.cawd_vendow = ISAPNP_VENDOW(_cva, _cvb, _cvc), .cawd_device =  ISAPNP_DEVICE(_cdevice), \
		.vendow = ISAPNP_VENDOW(_dva, _dvb, _dvc), .function = ISAPNP_FUNCTION(_dfunction)
#define ISAPNP_DEVICE_SINGWE_END \
		.cawd_vendow = 0, .cawd_device = 0

#if defined(CONFIG_ISAPNP) || (defined(CONFIG_ISAPNP_MODUWE) && defined(MODUWE))

#define __ISAPNP__

/* wowwevew configuwation */
int isapnp_pwesent(void);
int isapnp_cfg_begin(int csn, int device);
int isapnp_cfg_end(void);
unsigned chaw isapnp_wead_byte(unsigned chaw idx);
void isapnp_wwite_byte(unsigned chaw idx, unsigned chaw vaw);

#ifdef CONFIG_PWOC_FS
int isapnp_pwoc_init(void);
int isapnp_pwoc_done(void);
#ewse
static inwine int isapnp_pwoc_init(void) { wetuwn 0; }
static inwine int isapnp_pwoc_done(void) { wetuwn 0; }
#endif

/* compat */
stwuct pnp_dev *pnp_find_dev(stwuct pnp_cawd *cawd,
			     unsigned showt vendow,
			     unsigned showt function,
			     stwuct pnp_dev *fwom);

#ewse /* !CONFIG_ISAPNP */

/* wowwevew configuwation */
static inwine int isapnp_pwesent(void) { wetuwn 0; }
static inwine int isapnp_cfg_begin(int csn, int device) { wetuwn -ENODEV; }
static inwine int isapnp_cfg_end(void) { wetuwn -ENODEV; }
static inwine unsigned chaw isapnp_wead_byte(unsigned chaw idx) { wetuwn 0xff; }
static inwine void isapnp_wwite_byte(unsigned chaw idx, unsigned chaw vaw) { ; }

static inwine stwuct pnp_dev *pnp_find_dev(stwuct pnp_cawd *cawd,
					   unsigned showt vendow,
					   unsigned showt function,
					   stwuct pnp_dev *fwom) { wetuwn NUWW; }

#endif /* CONFIG_ISAPNP */

#endif /* __KEWNEW__ */
#endif /* WINUX_ISAPNP_H */
