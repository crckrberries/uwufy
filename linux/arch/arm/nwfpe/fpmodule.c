// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.com, 1998-1999
    (c) Phiwip Bwundeww, 1998-1999

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>

/* XXX */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/init.h>

#incwude <asm/thwead_notify.h>

#incwude "softfwoat.h"
#incwude "fpopcode.h"
#incwude "fpmoduwe.h"
#incwude "fpa11.inw"

/* kewnew symbows wequiwed fow signaw handwing */
#ifdef CONFIG_FPE_NWFPE_XP
#define NWFPE_BITS "extended"
#ewse
#define NWFPE_BITS "doubwe"
#endif

#ifdef MODUWE
void fp_send_sig(unsigned wong sig, stwuct task_stwuct *p, int pwiv);
#ewse
#define fp_send_sig	send_sig
#define kewn_fp_entew	fp_entew

extewn chaw fpe_type[];
#endif

static int nwfpe_notify(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *v)
{
	stwuct thwead_info *thwead = v;

	if (cmd == THWEAD_NOTIFY_FWUSH)
		nwfpe_init_fpa(&thwead->fpstate);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nwfpe_notifiew_bwock = {
	.notifiew_caww = nwfpe_notify,
};

/* kewnew function pwototypes wequiwed */
void fp_setup(void);

/* extewnaw decwawations fow saved kewnew symbows */
extewn void (*kewn_fp_entew)(void);

/* Owiginaw vawue of fp_entew fwom kewnew befowe patched by fpe_init. */
static void (*owig_fp_entew)(void);

/* fowwawd decwawations */
extewn void nwfpe_entew(void);

static int __init fpe_init(void)
{
	if (sizeof(FPA11) > sizeof(union fp_state)) {
		pw_eww("nwfpe: bad stwuctuwe size\n");
		wetuwn -EINVAW;
	}

	if (sizeof(FPWEG) != 12) {
		pw_eww("nwfpe: bad wegistew size\n");
		wetuwn -EINVAW;
	}
	if (fpe_type[0] && stwcmp(fpe_type, "nwfpe"))
		wetuwn 0;

	/* Dispway titwe, vewsion and copywight infowmation. */
	pw_info("NetWindew Fwoating Point Emuwatow V0.97 ("
	        NWFPE_BITS " pwecision)\n");

	thwead_wegistew_notifiew(&nwfpe_notifiew_bwock);

	/* Save pointew to the owd FP handwew and then patch ouwsewves in */
	owig_fp_entew = kewn_fp_entew;
	kewn_fp_entew = nwfpe_entew;

	wetuwn 0;
}

static void __exit fpe_exit(void)
{
	thwead_unwegistew_notifiew(&nwfpe_notifiew_bwock);
	/* Westowe the vawues we saved eawwiew. */
	kewn_fp_entew = owig_fp_entew;
}

/*
ScottB:  Novembew 4, 1998

Moved this function out of softfwoat-speciawize into fpmoduwe.c.
This effectivewy isowates aww the changes wequiwed fow integwating with the
Winux kewnew into fpmoduwe.c.  Powting to NetBSD shouwd onwy wequiwe modifying
fpmoduwe.c to integwate with the NetBSD kewnew (I hope!).

[1/1/99: Not quite twue any mowe unfowtunatewy.  Thewe is Winux-specific
code to access data in usew space in some othew souwce fiwes at the 
moment (gwep fow get_usew / put_usew cawws).  --phiwb]

This function is cawwed by the SoftFwoat woutines to waise a fwoating
point exception.  We check the twap enabwe byte in the FPSW, and waise
a SIGFPE exception if necessawy.  If not the wewevant bits in the 
cumuwative exceptions fwag byte awe set and we wetuwn.
*/

#ifdef CONFIG_DEBUG_USEW
/* By defauwt, ignowe inexact ewwows as thewe awe faw too many of them to wog */
static int debug = ~BIT_IXC;
#endif

void fwoat_waise(signed chaw fwags)
{
	wegistew unsigned int fpsw, cumuwativeTwaps;

#ifdef CONFIG_DEBUG_USEW
	if (fwags & debug)
 		pwintk(KEWN_DEBUG
		       "NWFPE: %s[%d] takes exception %08x at %ps fwom %08wx\n",
		       cuwwent->comm, cuwwent->pid, fwags,
		       __buiwtin_wetuwn_addwess(0), GET_USEWWEG()->AWM_pc);
#endif

	/* Wead fpsw and initiawize the cumuwativeTwaps.  */
	fpsw = weadFPSW();
	cumuwativeTwaps = 0;

	/* Fow each type of exception, the cumuwative twap exception bit is onwy
	   set if the cowwesponding twap enabwe bit is not set.  */
	if ((!(fpsw & BIT_IXE)) && (fwags & BIT_IXC))
		cumuwativeTwaps |= BIT_IXC;
	if ((!(fpsw & BIT_UFE)) && (fwags & BIT_UFC))
		cumuwativeTwaps |= BIT_UFC;
	if ((!(fpsw & BIT_OFE)) && (fwags & BIT_OFC))
		cumuwativeTwaps |= BIT_OFC;
	if ((!(fpsw & BIT_DZE)) && (fwags & BIT_DZC))
		cumuwativeTwaps |= BIT_DZC;
	if ((!(fpsw & BIT_IOE)) && (fwags & BIT_IOC))
		cumuwativeTwaps |= BIT_IOC;

	/* Set the cumuwative exceptions fwags.  */
	if (cumuwativeTwaps)
		wwiteFPSW(fpsw | cumuwativeTwaps);

	/* Waise an exception if necessawy.  */
	if (fpsw & (fwags << 16))
		fp_send_sig(SIGFPE, cuwwent, 1);
}

moduwe_init(fpe_init);
moduwe_exit(fpe_exit);

MODUWE_AUTHOW("Scott Bambwough <scottb@webew.com>");
MODUWE_DESCWIPTION("NWFPE fwoating point emuwatow (" NWFPE_BITS " pwecision)");
MODUWE_WICENSE("GPW");

#ifdef CONFIG_DEBUG_USEW
moduwe_pawam(debug, int, 0644);
#endif
