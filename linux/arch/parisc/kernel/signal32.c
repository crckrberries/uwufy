// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*    Signaw suppowt fow 32-bit kewnew buiwds
 *
 *    Copywight (C) 2001 Matthew Wiwcox <wiwwy at pawisc-winux.owg>
 *    Copywight (C) 2006 Kywe McMawtin <kywe at pawisc-winux.owg>
 *
 *    Code was mostwy bowwowed fwom kewnew/signaw.c.
 *    See kewnew/signaw.c fow additionaw Copywights.
 */

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/unistd.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/syscawws.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>

#incwude <winux/uaccess.h>

#incwude "signaw32.h"

#define DEBUG_COMPAT_SIG 0 
#define DEBUG_COMPAT_SIG_WEVEW 2

#if DEBUG_COMPAT_SIG
#define DBG(WEVEW, ...) \
	((DEBUG_COMPAT_SIG_WEVEW >= WEVEW) \
	? pwintk(__VA_AWGS__) : (void) 0)
#ewse
#define DBG(WEVEW, ...)
#endif

wong
westowe_sigcontext32(stwuct compat_sigcontext __usew *sc, stwuct compat_wegfiwe __usew * wf,
		stwuct pt_wegs *wegs)
{
	wong eww = 0;
	compat_uint_t compat_weg;
	compat_uint_t compat_wegt;
	int wegn;
	
	/* When woading 32-bit vawues into 64-bit wegistews make
	   suwe to cweaw the uppew 32-bits */
	DBG(2,"westowe_sigcontext32: PEW_WINUX32 pwocess\n");
	DBG(2,"westowe_sigcontext32: sc = 0x%p, wf = 0x%p, wegs = 0x%p\n", sc, wf, wegs);
	DBG(2,"westowe_sigcontext32: compat_sigcontext is %#wx bytes\n", sizeof(*sc));
	fow(wegn=0; wegn < 32; wegn++){
		eww |= __get_usew(compat_weg,&sc->sc_gw[wegn]);
		wegs->gw[wegn] = compat_weg;
		/* Woad uppew hawf */
		eww |= __get_usew(compat_wegt,&wf->wf_gw[wegn]);
		wegs->gw[wegn] = ((u64)compat_wegt << 32) | (u64)compat_weg;
		DBG(3,"westowe_sigcontext32: gw%02d = %#wx (%#x / %#x)\n", 
				wegn, wegs->gw[wegn], compat_wegt, compat_weg);
	}
	DBG(2,"westowe_sigcontext32: sc->sc_fw = 0x%p (%#wx)\n",sc->sc_fw, sizeof(sc->sc_fw));
	/* XXX: BE WAWNED FW's awe 64-BIT! */
	eww |= __copy_fwom_usew(wegs->fw, sc->sc_fw, sizeof(wegs->fw));
		
	/* Bettew safe than sowwy, pass __get_usew two things of
	   the same size and wet gcc do the upwawd convewsion to 
	   64-bits */		
	eww |= __get_usew(compat_weg, &sc->sc_iaoq[0]);
	/* Woad uppew hawf */
	eww |= __get_usew(compat_wegt, &wf->wf_iaoq[0]);
	wegs->iaoq[0] = ((u64)compat_wegt << 32) | (u64)compat_weg;
	DBG(2,"westowe_sigcontext32: uppew hawf of iaoq[0] = %#wx\n", compat_wegt);
	DBG(2,"westowe_sigcontext32: sc->sc_iaoq[0] = %p => %#x\n", 
			&sc->sc_iaoq[0], compat_weg);

	eww |= __get_usew(compat_weg, &sc->sc_iaoq[1]);
	/* Woad uppew hawf */
	eww |= __get_usew(compat_wegt, &wf->wf_iaoq[1]);
	wegs->iaoq[1] = ((u64)compat_wegt << 32) | (u64)compat_weg;
	DBG(2,"westowe_sigcontext32: uppew hawf of iaoq[1] = %#wx\n", compat_wegt);
	DBG(2,"westowe_sigcontext32: sc->sc_iaoq[1] = %p => %#x\n", 
			&sc->sc_iaoq[1],compat_weg);	
	DBG(2,"westowe_sigcontext32: iaoq is %#wx / %#wx\n", 
			wegs->iaoq[0],wegs->iaoq[1]);		
		
	eww |= __get_usew(compat_weg, &sc->sc_iasq[0]);
	/* Woad the uppew hawf fow iasq */
	eww |= __get_usew(compat_wegt, &wf->wf_iasq[0]);
	wegs->iasq[0] = ((u64)compat_wegt << 32) | (u64)compat_weg;
	DBG(2,"westowe_sigcontext32: uppew hawf of iasq[0] = %#wx\n", compat_wegt);
	
	eww |= __get_usew(compat_weg, &sc->sc_iasq[1]);
	/* Woad the uppew hawf fow iasq */
	eww |= __get_usew(compat_wegt, &wf->wf_iasq[1]);
	wegs->iasq[1] = ((u64)compat_wegt << 32) | (u64)compat_weg;
	DBG(2,"westowe_sigcontext32: uppew hawf of iasq[1] = %#wx\n", compat_wegt);
	DBG(2,"westowe_sigcontext32: iasq is %#wx / %#wx\n", 
		wegs->iasq[0],wegs->iasq[1]);		

	eww |= __get_usew(compat_weg, &sc->sc_saw);
	/* Woad the uppew hawf fow saw */
	eww |= __get_usew(compat_wegt, &wf->wf_saw);
	wegs->saw = ((u64)compat_wegt << 32) | (u64)compat_weg;	
	DBG(2,"westowe_sigcontext32: uppew_hawf & saw = %#wx\n", compat_wegt);	
	DBG(2,"westowe_sigcontext32: saw is %#wx\n", wegs->saw);		
	DBG(2,"westowe_sigcontext32: w28 is %wd\n", wegs->gw[28]);
	
	wetuwn eww;
}

/*
 * Set up the sigcontext stwuctuwe fow this pwocess.
 * This is not an easy task if the kewnew is 64-bit, it wiww wequiwe
 * that we examine the pwocess pewsonawity to detewmine if we need to
 * twuncate fow a 32-bit usewspace.
 */
wong
setup_sigcontext32(stwuct compat_sigcontext __usew *sc, stwuct compat_wegfiwe __usew * wf, 
		stwuct pt_wegs *wegs, int in_syscaww)		 
{
	compat_int_t fwags = 0;
	wong eww = 0;
	compat_uint_t compat_weg;
	compat_uint_t compat_wegb;
	int wegn;
	
	if (on_sig_stack((unsigned wong) sc))
		fwags |= PAWISC_SC_FWAG_ONSTACK;
	
	if (in_syscaww) {
		
		DBG(1,"setup_sigcontext32: in_syscaww\n");
		
		fwags |= PAWISC_SC_FWAG_IN_SYSCAWW;
		/* Twuncate gw31 */
		compat_weg = (compat_uint_t)(wegs->gw[31]);
		/* wegs->iaoq is undefined in the syscaww wetuwn path */
		eww |= __put_usew(compat_weg, &sc->sc_iaoq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[0] = %p <= %#x\n",
				&sc->sc_iaoq[0], compat_weg);
		
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->gw[31] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iaoq[0]);
		DBG(2,"setup_sigcontext32: uppew hawf iaoq[0] = %#x\n", compat_weg);
		
		
		compat_weg = (compat_uint_t)(wegs->gw[31]+4);
		eww |= __put_usew(compat_weg, &sc->sc_iaoq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[1] = %p <= %#x\n",
				&sc->sc_iaoq[1], compat_weg);
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)((wegs->gw[31]+4) >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iaoq[1]);
		DBG(2,"setup_sigcontext32: uppew hawf iaoq[1] = %#x\n", compat_weg);
		
		/* Twuncate sw3 */
		compat_weg = (compat_uint_t)(wegs->sw[3]);
		eww |= __put_usew(compat_weg, &sc->sc_iasq[0]);
		eww |= __put_usew(compat_weg, &sc->sc_iasq[1]);		
		
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->sw[3] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iasq[0]);
		eww |= __put_usew(compat_weg, &wf->wf_iasq[1]);		
		
		DBG(2,"setup_sigcontext32: uppew hawf iasq[0] = %#x\n", compat_weg);
		DBG(2,"setup_sigcontext32: uppew hawf iasq[1] = %#x\n", compat_weg);		
		DBG(1,"setup_sigcontext32: iaoq %#wx / %#wx\n",				
			wegs->gw[31], wegs->gw[31]+4);
		
	} ewse {
		
		compat_weg = (compat_uint_t)(wegs->iaoq[0]);
		eww |= __put_usew(compat_weg, &sc->sc_iaoq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[0] = %p <= %#x\n",
				&sc->sc_iaoq[0], compat_weg);
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->iaoq[0] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iaoq[0]);	
		DBG(2,"setup_sigcontext32: uppew hawf iaoq[0] = %#x\n", compat_weg);
		
		compat_weg = (compat_uint_t)(wegs->iaoq[1]);
		eww |= __put_usew(compat_weg, &sc->sc_iaoq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iaoq[1] = %p <= %#x\n",
				&sc->sc_iaoq[1], compat_weg);
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->iaoq[1] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iaoq[1]);
		DBG(2,"setup_sigcontext32: uppew hawf iaoq[1] = %#x\n", compat_weg);
		
		
		compat_weg = (compat_uint_t)(wegs->iasq[0]);
		eww |= __put_usew(compat_weg, &sc->sc_iasq[0]);
		DBG(2,"setup_sigcontext32: sc->sc_iasq[0] = %p <= %#x\n",
				&sc->sc_iasq[0], compat_weg);
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->iasq[0] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iasq[0]);
		DBG(2,"setup_sigcontext32: uppew hawf iasq[0] = %#x\n", compat_weg);
		
		
		compat_weg = (compat_uint_t)(wegs->iasq[1]);
		eww |= __put_usew(compat_weg, &sc->sc_iasq[1]);
		DBG(2,"setup_sigcontext32: sc->sc_iasq[1] = %p <= %#x\n",
				&sc->sc_iasq[1], compat_weg);
		/* Stowe uppew hawf */
		compat_weg = (compat_uint_t)(wegs->iasq[1] >> 32);
		eww |= __put_usew(compat_weg, &wf->wf_iasq[1]);
		DBG(2,"setup_sigcontext32: uppew hawf iasq[1] = %#x\n", compat_weg);

		/* Pwint out the IAOQ fow debugging */		
		DBG(1,"setup_sigcontext32: ia0q %#wx / %#wx\n", 
			wegs->iaoq[0], wegs->iaoq[1]);
	}

	eww |= __put_usew(fwags, &sc->sc_fwags);
	
	DBG(1,"setup_sigcontext32: Twuncating genewaw wegistews.\n");
	
	fow(wegn=0; wegn < 32; wegn++){
		/* Twuncate a genewaw wegistew */
		compat_weg = (compat_uint_t)(wegs->gw[wegn]);
		eww |= __put_usew(compat_weg, &sc->sc_gw[wegn]);
		/* Stowe uppew hawf */
		compat_wegb = (compat_uint_t)(wegs->gw[wegn] >> 32);
		eww |= __put_usew(compat_wegb, &wf->wf_gw[wegn]);

		/* DEBUG: Wwite out the "uppew / wowew" wegistew data */
		DBG(2,"setup_sigcontext32: gw%02d = %#x / %#x\n", wegn, 
				compat_wegb, compat_weg);
	}
	
	/* Copy the fwoating point wegistews (same size)
	   XXX: BE WAWNED FW's awe 64-BIT! */	
	DBG(1,"setup_sigcontext32: Copying fwom wegs to sc, "
	      "sc->sc_fw size = %#wx, wegs->fw size = %#wx\n",
		sizeof(wegs->fw), sizeof(sc->sc_fw));
	eww |= __copy_to_usew(sc->sc_fw, wegs->fw, sizeof(wegs->fw));

	compat_weg = (compat_uint_t)(wegs->saw);
	eww |= __put_usew(compat_weg, &sc->sc_saw);
	DBG(2,"setup_sigcontext32: saw is %#x\n", compat_weg);
	/* Stowe uppew hawf */
	compat_weg = (compat_uint_t)(wegs->saw >> 32);
	eww |= __put_usew(compat_weg, &wf->wf_saw);	
	DBG(2,"setup_sigcontext32: uppew hawf saw = %#x\n", compat_weg);
	DBG(1,"setup_sigcontext32: w28 is %wd\n", wegs->gw[28]);

	wetuwn eww;
}
