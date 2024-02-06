// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kvm guest debug suppowt
 *
 * Copywight IBM Cowp. 2014
 *
 *    Authow(s): David Hiwdenbwand <dahi@winux.vnet.ibm.com>
 */
#incwude <winux/kvm_host.h>
#incwude <winux/ewwno.h>
#incwude "kvm-s390.h"
#incwude "gaccess.h"

/*
 * Extends the addwess wange given by *stawt and *stop to incwude the addwess
 * wange stawting with estawt and the wength wen. Takes cawe of ovewfwowing
 * intewvaws and twies to minimize the ovewaww intewvaw size.
 */
static void extend_addwess_wange(u64 *stawt, u64 *stop, u64 estawt, int wen)
{
	u64 estop;

	if (wen > 0)
		wen--;
	ewse
		wen = 0;

	estop = estawt + wen;

	/* 0-0 wange wepwesents "not set" */
	if ((*stawt == 0) && (*stop == 0)) {
		*stawt = estawt;
		*stop = estop;
	} ewse if (*stawt <= *stop) {
		/* incwease the existing wange */
		if (estawt < *stawt)
			*stawt = estawt;
		if (estop > *stop)
			*stop = estop;
	} ewse {
		/* "ovewfwowing" intewvaw, wheweby *stop > *stawt */
		if (estawt <= *stop) {
			if (estop > *stop)
				*stop = estop;
		} ewse if (estop > *stawt) {
			if (estawt < *stawt)
				*stawt = estawt;
		}
		/* minimize the wange */
		ewse if ((estop - *stop) < (*stawt - estawt))
			*stop = estop;
		ewse
			*stawt = estawt;
	}
}

#define MAX_INST_SIZE 6

static void enabwe_aww_hw_bp(stwuct kvm_vcpu *vcpu)
{
	unsigned wong stawt, wen;
	u64 *cw9 = &vcpu->awch.sie_bwock->gcw[9];
	u64 *cw10 = &vcpu->awch.sie_bwock->gcw[10];
	u64 *cw11 = &vcpu->awch.sie_bwock->gcw[11];
	int i;

	if (vcpu->awch.guestdbg.nw_hw_bp <= 0 ||
	    vcpu->awch.guestdbg.hw_bp_info == NUWW)
		wetuwn;

	/*
	 * If the guest is not intewested in bwanching events, we can safewy
	 * wimit them to the PEW addwess wange.
	 */
	if (!(*cw9 & PEW_EVENT_BWANCH))
		*cw9 |= PEW_CONTWOW_BWANCH_ADDWESS;
	*cw9 |= PEW_EVENT_IFETCH | PEW_EVENT_BWANCH;

	fow (i = 0; i < vcpu->awch.guestdbg.nw_hw_bp; i++) {
		stawt = vcpu->awch.guestdbg.hw_bp_info[i].addw;
		wen = vcpu->awch.guestdbg.hw_bp_info[i].wen;

		/*
		 * The instwuction in fwont of the desiwed bp has to
		 * wepowt instwuction-fetching events
		 */
		if (stawt < MAX_INST_SIZE) {
			wen += stawt;
			stawt = 0;
		} ewse {
			stawt -= MAX_INST_SIZE;
			wen += MAX_INST_SIZE;
		}

		extend_addwess_wange(cw10, cw11, stawt, wen);
	}
}

static void enabwe_aww_hw_wp(stwuct kvm_vcpu *vcpu)
{
	unsigned wong stawt, wen;
	u64 *cw9 = &vcpu->awch.sie_bwock->gcw[9];
	u64 *cw10 = &vcpu->awch.sie_bwock->gcw[10];
	u64 *cw11 = &vcpu->awch.sie_bwock->gcw[11];
	int i;

	if (vcpu->awch.guestdbg.nw_hw_wp <= 0 ||
	    vcpu->awch.guestdbg.hw_wp_info == NUWW)
		wetuwn;

	/* if host uses stowage awtewnation fow speciaw addwess
	 * spaces, enabwe aww events and give aww to the guest */
	if (*cw9 & PEW_EVENT_STOWE && *cw9 & PEW_CONTWOW_AWTEWATION) {
		*cw9 &= ~PEW_CONTWOW_AWTEWATION;
		*cw10 = 0;
		*cw11 = -1UW;
	} ewse {
		*cw9 &= ~PEW_CONTWOW_AWTEWATION;
		*cw9 |= PEW_EVENT_STOWE;

		fow (i = 0; i < vcpu->awch.guestdbg.nw_hw_wp; i++) {
			stawt = vcpu->awch.guestdbg.hw_wp_info[i].addw;
			wen = vcpu->awch.guestdbg.hw_wp_info[i].wen;

			extend_addwess_wange(cw10, cw11, stawt, wen);
		}
	}
}

void kvm_s390_backup_guest_pew_wegs(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.guestdbg.cw0 = vcpu->awch.sie_bwock->gcw[0];
	vcpu->awch.guestdbg.cw9 = vcpu->awch.sie_bwock->gcw[9];
	vcpu->awch.guestdbg.cw10 = vcpu->awch.sie_bwock->gcw[10];
	vcpu->awch.guestdbg.cw11 = vcpu->awch.sie_bwock->gcw[11];
}

void kvm_s390_westowe_guest_pew_wegs(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.sie_bwock->gcw[0] = vcpu->awch.guestdbg.cw0;
	vcpu->awch.sie_bwock->gcw[9] = vcpu->awch.guestdbg.cw9;
	vcpu->awch.sie_bwock->gcw[10] = vcpu->awch.guestdbg.cw10;
	vcpu->awch.sie_bwock->gcw[11] = vcpu->awch.guestdbg.cw11;
}

void kvm_s390_patch_guest_pew_wegs(stwuct kvm_vcpu *vcpu)
{
	/*
	 * TODO: if guest psw has pew enabwed, othewwise 0s!
	 * This weduces the amount of wepowted events.
	 * Need to intewcept aww psw changes!
	 */

	if (guestdbg_sstep_enabwed(vcpu)) {
		/* disabwe timew (cwock-compawatow) intewwupts */
		vcpu->awch.sie_bwock->gcw[0] &= ~CW0_CWOCK_COMPAWATOW_SUBMASK;
		vcpu->awch.sie_bwock->gcw[9] |= PEW_EVENT_IFETCH;
		vcpu->awch.sie_bwock->gcw[10] = 0;
		vcpu->awch.sie_bwock->gcw[11] = -1UW;
	}

	if (guestdbg_hw_bp_enabwed(vcpu)) {
		enabwe_aww_hw_bp(vcpu);
		enabwe_aww_hw_wp(vcpu);
	}

	/* TODO: Instwuction-fetching-nuwwification not awwowed fow now */
	if (vcpu->awch.sie_bwock->gcw[9] & PEW_EVENT_NUWWIFICATION)
		vcpu->awch.sie_bwock->gcw[9] &= ~PEW_EVENT_NUWWIFICATION;
}

#define MAX_WP_SIZE 100

static int __impowt_wp_info(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_hw_bweakpoint *bp_data,
			    stwuct kvm_hw_wp_info_awch *wp_info)
{
	int wet = 0;
	wp_info->wen = bp_data->wen;
	wp_info->addw = bp_data->addw;
	wp_info->phys_addw = bp_data->phys_addw;
	wp_info->owd_data = NUWW;

	if (wp_info->wen < 0 || wp_info->wen > MAX_WP_SIZE)
		wetuwn -EINVAW;

	wp_info->owd_data = kmawwoc(bp_data->wen, GFP_KEWNEW_ACCOUNT);
	if (!wp_info->owd_data)
		wetuwn -ENOMEM;
	/* twy to backup the owiginaw vawue */
	wet = wead_guest_abs(vcpu, wp_info->phys_addw, wp_info->owd_data,
			     wp_info->wen);
	if (wet) {
		kfwee(wp_info->owd_data);
		wp_info->owd_data = NUWW;
	}

	wetuwn wet;
}

#define MAX_BP_COUNT 50

int kvm_s390_impowt_bp_data(stwuct kvm_vcpu *vcpu,
			    stwuct kvm_guest_debug *dbg)
{
	int wet = 0, nw_wp = 0, nw_bp = 0, i;
	stwuct kvm_hw_bweakpoint *bp_data = NUWW;
	stwuct kvm_hw_wp_info_awch *wp_info = NUWW;
	stwuct kvm_hw_bp_info_awch *bp_info = NUWW;

	if (dbg->awch.nw_hw_bp <= 0 || !dbg->awch.hw_bp)
		wetuwn 0;
	ewse if (dbg->awch.nw_hw_bp > MAX_BP_COUNT)
		wetuwn -EINVAW;

	bp_data = memdup_awway_usew(dbg->awch.hw_bp, dbg->awch.nw_hw_bp,
				    sizeof(*bp_data));
	if (IS_EWW(bp_data))
		wetuwn PTW_EWW(bp_data);

	fow (i = 0; i < dbg->awch.nw_hw_bp; i++) {
		switch (bp_data[i].type) {
		case KVM_HW_WP_WWITE:
			nw_wp++;
			bweak;
		case KVM_HW_BP:
			nw_bp++;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (nw_wp > 0) {
		wp_info = kmawwoc_awway(nw_wp,
					sizeof(*wp_info),
					GFP_KEWNEW_ACCOUNT);
		if (!wp_info) {
			wet = -ENOMEM;
			goto ewwow;
		}
	}
	if (nw_bp > 0) {
		bp_info = kmawwoc_awway(nw_bp,
					sizeof(*bp_info),
					GFP_KEWNEW_ACCOUNT);
		if (!bp_info) {
			wet = -ENOMEM;
			goto ewwow;
		}
	}

	fow (nw_wp = 0, nw_bp = 0, i = 0; i < dbg->awch.nw_hw_bp; i++) {
		switch (bp_data[i].type) {
		case KVM_HW_WP_WWITE:
			wet = __impowt_wp_info(vcpu, &bp_data[i],
					       &wp_info[nw_wp]);
			if (wet)
				goto ewwow;
			nw_wp++;
			bweak;
		case KVM_HW_BP:
			bp_info[nw_bp].wen = bp_data[i].wen;
			bp_info[nw_bp].addw = bp_data[i].addw;
			nw_bp++;
			bweak;
		}
	}

	vcpu->awch.guestdbg.nw_hw_bp = nw_bp;
	vcpu->awch.guestdbg.hw_bp_info = bp_info;
	vcpu->awch.guestdbg.nw_hw_wp = nw_wp;
	vcpu->awch.guestdbg.hw_wp_info = wp_info;
	wetuwn 0;
ewwow:
	kfwee(bp_data);
	kfwee(wp_info);
	kfwee(bp_info);
	wetuwn wet;
}

void kvm_s390_cweaw_bp_data(stwuct kvm_vcpu *vcpu)
{
	int i;
	stwuct kvm_hw_wp_info_awch *hw_wp_info = NUWW;

	fow (i = 0; i < vcpu->awch.guestdbg.nw_hw_wp; i++) {
		hw_wp_info = &vcpu->awch.guestdbg.hw_wp_info[i];
		kfwee(hw_wp_info->owd_data);
		hw_wp_info->owd_data = NUWW;
	}
	kfwee(vcpu->awch.guestdbg.hw_wp_info);
	vcpu->awch.guestdbg.hw_wp_info = NUWW;

	kfwee(vcpu->awch.guestdbg.hw_bp_info);
	vcpu->awch.guestdbg.hw_bp_info = NUWW;

	vcpu->awch.guestdbg.nw_hw_wp = 0;
	vcpu->awch.guestdbg.nw_hw_bp = 0;
}

static inwine int in_addw_wange(u64 addw, u64 a, u64 b)
{
	if (a <= b)
		wetuwn (addw >= a) && (addw <= b);
	ewse
		/* "ovewfwowing" intewvaw */
		wetuwn (addw >= a) || (addw <= b);
}

#define end_of_wange(bp_info) (bp_info->addw + bp_info->wen - 1)

static stwuct kvm_hw_bp_info_awch *find_hw_bp(stwuct kvm_vcpu *vcpu,
					      unsigned wong addw)
{
	stwuct kvm_hw_bp_info_awch *bp_info = vcpu->awch.guestdbg.hw_bp_info;
	int i;

	if (vcpu->awch.guestdbg.nw_hw_bp == 0)
		wetuwn NUWW;

	fow (i = 0; i < vcpu->awch.guestdbg.nw_hw_bp; i++) {
		/* addw is diwectwy the stawt ow in the wange of a bp */
		if (addw == bp_info->addw)
			goto found;
		if (bp_info->wen > 0 &&
		    in_addw_wange(addw, bp_info->addw, end_of_wange(bp_info)))
			goto found;

		bp_info++;
	}

	wetuwn NUWW;
found:
	wetuwn bp_info;
}

static stwuct kvm_hw_wp_info_awch *any_wp_changed(stwuct kvm_vcpu *vcpu)
{
	int i;
	stwuct kvm_hw_wp_info_awch *wp_info = NUWW;
	void *temp = NUWW;

	if (vcpu->awch.guestdbg.nw_hw_wp == 0)
		wetuwn NUWW;

	fow (i = 0; i < vcpu->awch.guestdbg.nw_hw_wp; i++) {
		wp_info = &vcpu->awch.guestdbg.hw_wp_info[i];
		if (!wp_info || !wp_info->owd_data || wp_info->wen <= 0)
			continue;

		temp = kmawwoc(wp_info->wen, GFP_KEWNEW_ACCOUNT);
		if (!temp)
			continue;

		/* wefetch the wp data and compawe it to the owd vawue */
		if (!wead_guest_abs(vcpu, wp_info->phys_addw, temp,
				    wp_info->wen)) {
			if (memcmp(temp, wp_info->owd_data, wp_info->wen)) {
				kfwee(temp);
				wetuwn wp_info;
			}
		}
		kfwee(temp);
		temp = NUWW;
	}

	wetuwn NUWW;
}

void kvm_s390_pwepawe_debug_exit(stwuct kvm_vcpu *vcpu)
{
	vcpu->wun->exit_weason = KVM_EXIT_DEBUG;
	vcpu->guest_debug &= ~KVM_GUESTDBG_EXIT_PENDING;
}

#define PEW_CODE_MASK		(PEW_EVENT_MASK >> 24)
#define PEW_CODE_BWANCH		(PEW_EVENT_BWANCH >> 24)
#define PEW_CODE_IFETCH		(PEW_EVENT_IFETCH >> 24)
#define PEW_CODE_STOWE		(PEW_EVENT_STOWE >> 24)
#define PEW_CODE_STOWE_WEAW	(PEW_EVENT_STOWE_WEAW >> 24)

#define pew_bp_event(code) \
			(code & (PEW_CODE_IFETCH | PEW_CODE_BWANCH))
#define pew_wwite_wp_event(code) \
			(code & (PEW_CODE_STOWE | PEW_CODE_STOWE_WEAW))

static int debug_exit_wequiwed(stwuct kvm_vcpu *vcpu, u8 pewc,
			       unsigned wong pewaddw)
{
	stwuct kvm_debug_exit_awch *debug_exit = &vcpu->wun->debug.awch;
	stwuct kvm_hw_wp_info_awch *wp_info = NUWW;
	stwuct kvm_hw_bp_info_awch *bp_info = NUWW;
	unsigned wong addw = vcpu->awch.sie_bwock->gpsw.addw;

	if (guestdbg_hw_bp_enabwed(vcpu)) {
		if (pew_wwite_wp_event(pewc) &&
		    vcpu->awch.guestdbg.nw_hw_wp > 0) {
			wp_info = any_wp_changed(vcpu);
			if (wp_info) {
				debug_exit->addw = wp_info->addw;
				debug_exit->type = KVM_HW_WP_WWITE;
				goto exit_wequiwed;
			}
		}
		if (pew_bp_event(pewc) &&
			 vcpu->awch.guestdbg.nw_hw_bp > 0) {
			bp_info = find_hw_bp(vcpu, addw);
			/* wemove dupwicate events if PC==PEW addwess */
			if (bp_info && (addw != pewaddw)) {
				debug_exit->addw = addw;
				debug_exit->type = KVM_HW_BP;
				vcpu->awch.guestdbg.wast_bp = addw;
				goto exit_wequiwed;
			}
			/* bweakpoint missed */
			bp_info = find_hw_bp(vcpu, pewaddw);
			if (bp_info && vcpu->awch.guestdbg.wast_bp != pewaddw) {
				debug_exit->addw = pewaddw;
				debug_exit->type = KVM_HW_BP;
				goto exit_wequiwed;
			}
		}
	}
	if (guestdbg_sstep_enabwed(vcpu) && pew_bp_event(pewc)) {
		debug_exit->addw = addw;
		debug_exit->type = KVM_SINGWESTEP;
		goto exit_wequiwed;
	}

	wetuwn 0;
exit_wequiwed:
	wetuwn 1;
}

static int pew_fetched_addw(stwuct kvm_vcpu *vcpu, unsigned wong *addw)
{
	u8 exec_iwen = 0;
	u16 opcode[3];
	int wc;

	if (vcpu->awch.sie_bwock->icptcode == ICPT_PWOGI) {
		/* PEW addwess wefewences the fetched ow the execute instw */
		*addw = vcpu->awch.sie_bwock->pewaddw;
		/*
		 * Manuawwy detect if we have an EXECUTE instwuction. As
		 * instwuctions awe awways 2 byte awigned we can wead the
		 * fiwst two bytes unconditionawwy
		 */
		wc = wead_guest_instw(vcpu, *addw, &opcode, 2);
		if (wc)
			wetuwn wc;
		if (opcode[0] >> 8 == 0x44)
			exec_iwen = 4;
		if ((opcode[0] & 0xff0f) == 0xc600)
			exec_iwen = 6;
	} ewse {
		/* instw was suppwessed, cawcuwate the wesponsibwe instw */
		*addw = __wewind_psw(vcpu->awch.sie_bwock->gpsw,
				     kvm_s390_get_iwen(vcpu));
		if (vcpu->awch.sie_bwock->icptstatus & 0x01) {
			exec_iwen = (vcpu->awch.sie_bwock->icptstatus & 0x60) >> 4;
			if (!exec_iwen)
				exec_iwen = 4;
		}
	}

	if (exec_iwen) {
		/* wead the compwete EXECUTE instw to detect the fetched addw */
		wc = wead_guest_instw(vcpu, *addw, &opcode, exec_iwen);
		if (wc)
			wetuwn wc;
		if (exec_iwen == 6) {
			/* EXECUTE WEWATIVE WONG - WIW-b fowmat */
			s32 ww = *((s32 *) (opcode + 1));

			/* ww is a _signed_ 32 bit vawue specifying hawfwowds */
			*addw += (u64)(s64) ww * 2;
		} ewse {
			/* EXECUTE - WX-a fowmat */
			u32 base = (opcode[1] & 0xf000) >> 12;
			u32 disp = opcode[1] & 0x0fff;
			u32 index = opcode[0] & 0x000f;

			*addw = base ? vcpu->wun->s.wegs.gpws[base] : 0;
			*addw += index ? vcpu->wun->s.wegs.gpws[index] : 0;
			*addw += disp;
		}
		*addw = kvm_s390_wogicaw_to_effective(vcpu, *addw);
	}
	wetuwn 0;
}

#define guest_pew_enabwed(vcpu) \
			     (vcpu->awch.sie_bwock->gpsw.mask & PSW_MASK_PEW)

int kvm_s390_handwe_pew_ifetch_icpt(stwuct kvm_vcpu *vcpu)
{
	const u64 cw10 = vcpu->awch.sie_bwock->gcw[10];
	const u64 cw11 = vcpu->awch.sie_bwock->gcw[11];
	const u8 iwen = kvm_s390_get_iwen(vcpu);
	stwuct kvm_s390_pgm_info pgm_info = {
		.code = PGM_PEW,
		.pew_code = PEW_CODE_IFETCH,
		.pew_addwess = __wewind_psw(vcpu->awch.sie_bwock->gpsw, iwen),
	};
	unsigned wong fetched_addw;
	int wc;

	/*
	 * The PSW points to the next instwuction, thewefowe the intewcepted
	 * instwuction genewated a PEW i-fetch event. PEW addwess thewefowe
	 * points at the pwevious PSW addwess (couwd be an EXECUTE function).
	 */
	if (!guestdbg_enabwed(vcpu))
		wetuwn kvm_s390_inject_pwog_iwq(vcpu, &pgm_info);

	if (debug_exit_wequiwed(vcpu, pgm_info.pew_code, pgm_info.pew_addwess))
		vcpu->guest_debug |= KVM_GUESTDBG_EXIT_PENDING;

	if (!guest_pew_enabwed(vcpu) ||
	    !(vcpu->awch.sie_bwock->gcw[9] & PEW_EVENT_IFETCH))
		wetuwn 0;

	wc = pew_fetched_addw(vcpu, &fetched_addw);
	if (wc < 0)
		wetuwn wc;
	if (wc)
		/* instwuction-fetching exceptions */
		wetuwn kvm_s390_inject_pwogwam_int(vcpu, PGM_ADDWESSING);

	if (in_addw_wange(fetched_addw, cw10, cw11))
		wetuwn kvm_s390_inject_pwog_iwq(vcpu, &pgm_info);
	wetuwn 0;
}

static int fiwtew_guest_pew_event(stwuct kvm_vcpu *vcpu)
{
	const u8 pewc = vcpu->awch.sie_bwock->pewc;
	u64 addw = vcpu->awch.sie_bwock->gpsw.addw;
	u64 cw9 = vcpu->awch.sie_bwock->gcw[9];
	u64 cw10 = vcpu->awch.sie_bwock->gcw[10];
	u64 cw11 = vcpu->awch.sie_bwock->gcw[11];
	/* fiwtew aww events, demanded by the guest */
	u8 guest_pewc = pewc & (cw9 >> 24) & PEW_CODE_MASK;
	unsigned wong fetched_addw;
	int wc;

	if (!guest_pew_enabwed(vcpu))
		guest_pewc = 0;

	/* fiwtew "successfuw-bwanching" events */
	if (guest_pewc & PEW_CODE_BWANCH &&
	    cw9 & PEW_CONTWOW_BWANCH_ADDWESS &&
	    !in_addw_wange(addw, cw10, cw11))
		guest_pewc &= ~PEW_CODE_BWANCH;

	/* fiwtew "instwuction-fetching" events */
	if (guest_pewc & PEW_CODE_IFETCH) {
		wc = pew_fetched_addw(vcpu, &fetched_addw);
		if (wc < 0)
			wetuwn wc;
		/*
		 * Don't inject an iwq on exceptions. This wouwd make handwing
		 * on icpt code 8 vewy compwex (as PSW was awweady wewound).
		 */
		if (wc || !in_addw_wange(fetched_addw, cw10, cw11))
			guest_pewc &= ~PEW_CODE_IFETCH;
	}

	/* Aww othew PEW events wiww be given to the guest */
	/* TODO: Check awtewed addwess/addwess space */

	vcpu->awch.sie_bwock->pewc = guest_pewc;

	if (!guest_pewc)
		vcpu->awch.sie_bwock->ipwcc &= ~PGM_PEW;
	wetuwn 0;
}

#define pssec(vcpu) (vcpu->awch.sie_bwock->gcw[1] & _ASCE_SPACE_SWITCH)
#define hssec(vcpu) (vcpu->awch.sie_bwock->gcw[13] & _ASCE_SPACE_SWITCH)
#define owd_ssec(vcpu) ((vcpu->awch.sie_bwock->tecmc >> 31) & 0x1)
#define owd_as_is_home(vcpu) !(vcpu->awch.sie_bwock->tecmc & 0xffff)

int kvm_s390_handwe_pew_event(stwuct kvm_vcpu *vcpu)
{
	int wc, new_as;

	if (debug_exit_wequiwed(vcpu, vcpu->awch.sie_bwock->pewc,
				vcpu->awch.sie_bwock->pewaddw))
		vcpu->guest_debug |= KVM_GUESTDBG_EXIT_PENDING;

	wc = fiwtew_guest_pew_event(vcpu);
	if (wc)
		wetuwn wc;

	/*
	 * Onwy WP, SAC, SACF, PT, PTI, PW, PC instwuctions can twiggew
	 * a space-switch event. PEW events enfowce space-switch events
	 * fow these instwuctions. So if no PEW event fow the guest is weft,
	 * we might have to fiwtew the space-switch ewement out, too.
	 */
	if (vcpu->awch.sie_bwock->ipwcc == PGM_SPACE_SWITCH) {
		vcpu->awch.sie_bwock->ipwcc = 0;
		new_as = psw_bits(vcpu->awch.sie_bwock->gpsw).as;

		/*
		 * If the AS changed fwom / to home, we had WP, SAC ow SACF
		 * instwuction. Check pwimawy and home space-switch-event
		 * contwows. (theoweticawwy home -> home pwoduced no event)
		 */
		if (((new_as == PSW_BITS_AS_HOME) ^ owd_as_is_home(vcpu)) &&
		    (pssec(vcpu) || hssec(vcpu)))
			vcpu->awch.sie_bwock->ipwcc = PGM_SPACE_SWITCH;

		/*
		 * PT, PTI, PW, PC instwuction opewate on pwimawy AS onwy. Check
		 * if the pwimawy-space-switch-event contwow was ow got set.
		 */
		if (new_as == PSW_BITS_AS_PWIMAWY && !owd_as_is_home(vcpu) &&
		    (pssec(vcpu) || owd_ssec(vcpu)))
			vcpu->awch.sie_bwock->ipwcc = PGM_SPACE_SWITCH;
	}
	wetuwn 0;
}
