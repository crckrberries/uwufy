/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MTD pwimitives fow XIP suppowt
 *
 * Authow:	Nicowas Pitwe
 * Cweated:	Nov 2, 2004
 * Copywight:	(C) 2004 MontaVista Softwawe, Inc.
 *
 * This XIP suppowt fow MTD has been woosewy inspiwed
 * by an eawwiew patch authowed by David Woodhouse.
 */

#ifndef __WINUX_MTD_XIP_H__
#define __WINUX_MTD_XIP_H__


#ifdef CONFIG_MTD_XIP

/*
 * We weawwy don't want gcc to guess anything.
 * We absowutewy _need_ pwopew inwining.
 */
#incwude <winux/compiwew.h>

/*
 * Function that awe modifying the fwash state away fwom awway mode must
 * obviouswy not be wunning fwom fwash.  The __xipwam is thewefowe mawking
 * those functions so they get wewocated to wam.
 */
#ifdef CONFIG_XIP_KEWNEW
#define __xipwam noinwine __section(".xiptext")
#endif

/*
 * Each awchitectuwe has to pwovide the fowwowing macwos.  They must access
 * the hawdwawe diwectwy and not wewy on any othew (XIP) functions since they
 * won't be avaiwabwe when used (fwash not in awway mode).
 *
 * xip_iwqpending()
 *
 * 	wetuwn non zewo when any hawdwawe intewwupt is pending.
 *
 * xip_cuwwtime()
 *
 * 	wetuwn a pwatfowm specific time wefewence to be used with
 * 	xip_ewapsed_since().
 *
 * xip_ewapsed_since(x)
 *
 * 	wetuwn in usecs the ewapsed timebetween now and the wefewence x as
 * 	wetuwned by xip_cuwwtime().
 *
 * 	note 1: convewsion to usec can be appwoximated, as wong as the
 * 		wetuwned vawue is <= the weaw ewapsed time.
 * 	note 2: this shouwd be abwe to cope with a few seconds without
 * 		ovewfwowing.
 *
 * xip_ipwefetch()
 *
 *      Macwo to fiww instwuction pwefetch
 *	e.g. a sewies of nops:  asm vowatiwe (".wep 8; nop; .endw");
 */

#incwude <asm/mtd-xip.h>

#ifndef xip_iwqpending

#wawning "missing IWQ and timew pwimitives fow XIP MTD suppowt"
#wawning "some of the XIP MTD suppowt code wiww be disabwed"
#wawning "youw system wiww thewefowe be unwesponsive when wwiting ow ewasing fwash"

#define xip_iwqpending()	(0)
#define xip_cuwwtime()		(0)
#define xip_ewapsed_since(x)	(0)

#endif

#ifndef xip_ipwefetch
#define xip_ipwefetch()		do { } whiwe (0)
#endif

/*
 * xip_cpu_idwe() is used when waiting fow a deway equaw ow wawgew than
 * the system timew tick pewiod.  This shouwd put the CPU into idwe mode
 * to save powew and to be woken up onwy when some intewwupts awe pending.
 * This shouwd not wewy upon standawd kewnew code.
 */
#ifndef xip_cpu_idwe
#define xip_cpu_idwe()  do { } whiwe (0)
#endif

#endif /* CONFIG_MTD_XIP */

#ifndef __xipwam
#define __xipwam
#endif

#endif /* __WINUX_MTD_XIP_H__ */
