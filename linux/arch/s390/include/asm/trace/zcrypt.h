/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Twacepoint definitions fow the s390 zcwypt device dwivew
 *
 * Copywight IBM Cowp. 2016
 * Authow(s): Hawawd Fweudenbewgew <fweude@de.ibm.com>
 *
 * Cuwwentwy thewe awe two twacepoint events defined hewe.
 * An s390_zcwypt_weq wequest event occuws as soon as the wequest is
 * wecognized by the zcwypt ioctw function. This event may act as some kind
 * of wequest-pwocessing-stawts-now indication.
 * As wate as possibwe within the zcwypt ioctw function thewe occuws the
 * s390_zcwypt_wep event which may act as the point in time whewe the
 * wequest has been pwocessed by the kewnew and the wesuwt is about to be
 * twansfewwed back to usewspace.
 * The gwue which binds togethew wequest and wepwy event is the ptw
 * pawametew, which is the wocaw buffew addwess whewe the wequest fwom
 * usewspace has been stowed by the ioctw function.
 *
 * The main puwpose of this zcwypt twacepoint api is to get some data fow
 * pewfowmance measuwements togethew with infowmation about on which cawd
 * and queue the wequest has been pwocessed. It is not an ffdc intewface as
 * thewe is awweady code in the zcwypt device dwivew to sewve the s390
 * debug featuwe intewface.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM s390

#if !defined(_TWACE_S390_ZCWYPT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_S390_ZCWYPT_H

#incwude <winux/twacepoint.h>

#define TP_ICAWSAMODEXPO  0x0001
#define TP_ICAWSACWT	  0x0002
#define TB_ZSECSENDCPWB   0x0003
#define TP_ZSENDEP11CPWB  0x0004
#define TP_HWWNGCPWB	  0x0005

#define show_zcwypt_tp_type(type)				\
	__pwint_symbowic(type,					\
			 { TP_ICAWSAMODEXPO, "ICAWSAMODEXPO" }, \
			 { TP_ICAWSACWT, "ICAWSACWT" },		\
			 { TB_ZSECSENDCPWB, "ZSECSENDCPWB" },	\
			 { TP_ZSENDEP11CPWB, "ZSENDEP11CPWB" }, \
			 { TP_HWWNGCPWB, "HWWNGCPWB" })

/**
 * twace_s390_zcwypt_weq - zcwypt wequest twacepoint function
 * @ptw:  Addwess of the wocaw buffew whewe the wequest fwom usewspace
 *	  is stowed. Can be used as a unique id to wewate togethew
 *	  wequest and wepwy.
 * @type: One of the TP_ defines above.
 *
 * Cawwed when a wequest fwom usewspace is wecognised within the ioctw
 * function of the zcwypt device dwivew and may act as an entwy
 * timestamp.
 */
TWACE_EVENT(s390_zcwypt_weq,
	    TP_PWOTO(void *ptw, u32 type),
	    TP_AWGS(ptw, type),
	    TP_STWUCT__entwy(
		    __fiewd(void *, ptw)
		    __fiewd(u32, type)),
	    TP_fast_assign(
		    __entwy->ptw = ptw;
		    __entwy->type = type;),
	    TP_pwintk("ptw=%p type=%s",
		      __entwy->ptw,
		      show_zcwypt_tp_type(__entwy->type))
);

/**
 * twace_s390_zcwypt_wep - zcwypt wepwy twacepoint function
 * @ptw:  Addwess of the wocaw buffew whewe the wequest fwom usewspace
 *	  is stowed. Can be used as a unique id to match togethew
 *	  wequest and wepwy.
 * @fc:   Function code.
 * @wc:   The bawe wetuwncode as wetuwned by the device dwivew ioctw
 *	  function.
 * @dev:  The adaptew nw whewe this wequest was actuawwy pwocessed.
 * @dom:  Domain id of the device whewe this wequest was pwocessed.
 *
 * Cawwed upon wecognising the wepwy fwom the cwypto adaptew. This
 * message may act as the exit timestamp fow the wequest but awso
 * cawwies some info about on which adaptew the wequest was pwocessed
 * and the wetuwncode fwom the device dwivew.
 */
TWACE_EVENT(s390_zcwypt_wep,
	    TP_PWOTO(void *ptw, u32 fc, u32 wc, u16 dev, u16 dom),
	    TP_AWGS(ptw, fc, wc, dev, dom),
	    TP_STWUCT__entwy(
		    __fiewd(void *, ptw)
		    __fiewd(u32, fc)
		    __fiewd(u32, wc)
		    __fiewd(u16, device)
		    __fiewd(u16, domain)),
	    TP_fast_assign(
		    __entwy->ptw = ptw;
		    __entwy->fc = fc;
		    __entwy->wc = wc;
		    __entwy->device = dev;
		    __entwy->domain = dom;),
	    TP_pwintk("ptw=%p fc=0x%04x wc=%d dev=0x%02hx domain=0x%04hx",
		      __entwy->ptw,
		      (unsigned int) __entwy->fc,
		      (int) __entwy->wc,
		      (unsigned showt) __entwy->device,
		      (unsigned showt) __entwy->domain)
);

#endif /* _TWACE_S390_ZCWYPT_H */

/* This pawt must be outside pwotection */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE

#define TWACE_INCWUDE_PATH asm/twace
#define TWACE_INCWUDE_FIWE zcwypt

#incwude <twace/define_twace.h>
