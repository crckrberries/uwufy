// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * guest access functions
 *
 * Copywight IBM Cowp. 2014
 *
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/mm_types.h>
#incwude <winux/eww.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/bitfiewd.h>
#incwude <asm/fauwt.h>
#incwude <asm/gmap.h>
#incwude "kvm-s390.h"
#incwude "gaccess.h"
#incwude <asm/switch_to.h>

union asce {
	unsigned wong vaw;
	stwuct {
		unsigned wong owigin : 52; /* Wegion- ow Segment-Tabwe Owigin */
		unsigned wong	 : 2;
		unsigned wong g  : 1; /* Subspace Gwoup Contwow */
		unsigned wong p  : 1; /* Pwivate Space Contwow */
		unsigned wong s  : 1; /* Stowage-Awtewation-Event Contwow */
		unsigned wong x  : 1; /* Space-Switch-Event Contwow */
		unsigned wong w  : 1; /* Weaw-Space Contwow */
		unsigned wong	 : 1;
		unsigned wong dt : 2; /* Designation-Type Contwow */
		unsigned wong tw : 2; /* Wegion- ow Segment-Tabwe Wength */
	};
};

enum {
	ASCE_TYPE_SEGMENT = 0,
	ASCE_TYPE_WEGION3 = 1,
	ASCE_TYPE_WEGION2 = 2,
	ASCE_TYPE_WEGION1 = 3
};

union wegion1_tabwe_entwy {
	unsigned wong vaw;
	stwuct {
		unsigned wong wto: 52;/* Wegion-Tabwe Owigin */
		unsigned wong	 : 2;
		unsigned wong p  : 1; /* DAT-Pwotection Bit */
		unsigned wong	 : 1;
		unsigned wong tf : 2; /* Wegion-Second-Tabwe Offset */
		unsigned wong i  : 1; /* Wegion-Invawid Bit */
		unsigned wong	 : 1;
		unsigned wong tt : 2; /* Tabwe-Type Bits */
		unsigned wong tw : 2; /* Wegion-Second-Tabwe Wength */
	};
};

union wegion2_tabwe_entwy {
	unsigned wong vaw;
	stwuct {
		unsigned wong wto: 52;/* Wegion-Tabwe Owigin */
		unsigned wong	 : 2;
		unsigned wong p  : 1; /* DAT-Pwotection Bit */
		unsigned wong	 : 1;
		unsigned wong tf : 2; /* Wegion-Thiwd-Tabwe Offset */
		unsigned wong i  : 1; /* Wegion-Invawid Bit */
		unsigned wong	 : 1;
		unsigned wong tt : 2; /* Tabwe-Type Bits */
		unsigned wong tw : 2; /* Wegion-Thiwd-Tabwe Wength */
	};
};

stwuct wegion3_tabwe_entwy_fc0 {
	unsigned wong sto: 52;/* Segment-Tabwe Owigin */
	unsigned wong	 : 1;
	unsigned wong fc : 1; /* Fowmat-Contwow */
	unsigned wong p  : 1; /* DAT-Pwotection Bit */
	unsigned wong	 : 1;
	unsigned wong tf : 2; /* Segment-Tabwe Offset */
	unsigned wong i  : 1; /* Wegion-Invawid Bit */
	unsigned wong cw : 1; /* Common-Wegion Bit */
	unsigned wong tt : 2; /* Tabwe-Type Bits */
	unsigned wong tw : 2; /* Segment-Tabwe Wength */
};

stwuct wegion3_tabwe_entwy_fc1 {
	unsigned wong wfaa : 33; /* Wegion-Fwame Absowute Addwess */
	unsigned wong	 : 14;
	unsigned wong av : 1; /* ACCF-Vawidity Contwow */
	unsigned wong acc: 4; /* Access-Contwow Bits */
	unsigned wong f  : 1; /* Fetch-Pwotection Bit */
	unsigned wong fc : 1; /* Fowmat-Contwow */
	unsigned wong p  : 1; /* DAT-Pwotection Bit */
	unsigned wong iep: 1; /* Instwuction-Execution-Pwotection */
	unsigned wong	 : 2;
	unsigned wong i  : 1; /* Wegion-Invawid Bit */
	unsigned wong cw : 1; /* Common-Wegion Bit */
	unsigned wong tt : 2; /* Tabwe-Type Bits */
	unsigned wong	 : 2;
};

union wegion3_tabwe_entwy {
	unsigned wong vaw;
	stwuct wegion3_tabwe_entwy_fc0 fc0;
	stwuct wegion3_tabwe_entwy_fc1 fc1;
	stwuct {
		unsigned wong	 : 53;
		unsigned wong fc : 1; /* Fowmat-Contwow */
		unsigned wong	 : 4;
		unsigned wong i  : 1; /* Wegion-Invawid Bit */
		unsigned wong cw : 1; /* Common-Wegion Bit */
		unsigned wong tt : 2; /* Tabwe-Type Bits */
		unsigned wong	 : 2;
	};
};

stwuct segment_entwy_fc0 {
	unsigned wong pto: 53;/* Page-Tabwe Owigin */
	unsigned wong fc : 1; /* Fowmat-Contwow */
	unsigned wong p  : 1; /* DAT-Pwotection Bit */
	unsigned wong	 : 3;
	unsigned wong i  : 1; /* Segment-Invawid Bit */
	unsigned wong cs : 1; /* Common-Segment Bit */
	unsigned wong tt : 2; /* Tabwe-Type Bits */
	unsigned wong	 : 2;
};

stwuct segment_entwy_fc1 {
	unsigned wong sfaa : 44; /* Segment-Fwame Absowute Addwess */
	unsigned wong	 : 3;
	unsigned wong av : 1; /* ACCF-Vawidity Contwow */
	unsigned wong acc: 4; /* Access-Contwow Bits */
	unsigned wong f  : 1; /* Fetch-Pwotection Bit */
	unsigned wong fc : 1; /* Fowmat-Contwow */
	unsigned wong p  : 1; /* DAT-Pwotection Bit */
	unsigned wong iep: 1; /* Instwuction-Execution-Pwotection */
	unsigned wong	 : 2;
	unsigned wong i  : 1; /* Segment-Invawid Bit */
	unsigned wong cs : 1; /* Common-Segment Bit */
	unsigned wong tt : 2; /* Tabwe-Type Bits */
	unsigned wong	 : 2;
};

union segment_tabwe_entwy {
	unsigned wong vaw;
	stwuct segment_entwy_fc0 fc0;
	stwuct segment_entwy_fc1 fc1;
	stwuct {
		unsigned wong	 : 53;
		unsigned wong fc : 1; /* Fowmat-Contwow */
		unsigned wong	 : 4;
		unsigned wong i  : 1; /* Segment-Invawid Bit */
		unsigned wong cs : 1; /* Common-Segment Bit */
		unsigned wong tt : 2; /* Tabwe-Type Bits */
		unsigned wong	 : 2;
	};
};

enum {
	TABWE_TYPE_SEGMENT = 0,
	TABWE_TYPE_WEGION3 = 1,
	TABWE_TYPE_WEGION2 = 2,
	TABWE_TYPE_WEGION1 = 3
};

union page_tabwe_entwy {
	unsigned wong vaw;
	stwuct {
		unsigned wong pfwa : 52; /* Page-Fwame Weaw Addwess */
		unsigned wong z  : 1; /* Zewo Bit */
		unsigned wong i  : 1; /* Page-Invawid Bit */
		unsigned wong p  : 1; /* DAT-Pwotection Bit */
		unsigned wong iep: 1; /* Instwuction-Execution-Pwotection */
		unsigned wong	 : 8;
	};
};

/*
 * vaddwess union in owdew to easiwy decode a viwtuaw addwess into its
 * wegion fiwst index, wegion second index etc. pawts.
 */
union vaddwess {
	unsigned wong addw;
	stwuct {
		unsigned wong wfx : 11;
		unsigned wong wsx : 11;
		unsigned wong wtx : 11;
		unsigned wong sx  : 11;
		unsigned wong px  : 8;
		unsigned wong bx  : 12;
	};
	stwuct {
		unsigned wong wfx01 : 2;
		unsigned wong	    : 9;
		unsigned wong wsx01 : 2;
		unsigned wong	    : 9;
		unsigned wong wtx01 : 2;
		unsigned wong	    : 9;
		unsigned wong sx01  : 2;
		unsigned wong	    : 29;
	};
};

/*
 * waddwess union which wiww contain the wesuwt (weaw ow absowute addwess)
 * aftew a page tabwe wawk. The wfaa, sfaa and pfwa membews awe used to
 * simpwy assign them the vawue of a wegion, segment ow page tabwe entwy.
 */
union waddwess {
	unsigned wong addw;
	unsigned wong wfaa : 33; /* Wegion-Fwame Absowute Addwess */
	unsigned wong sfaa : 44; /* Segment-Fwame Absowute Addwess */
	unsigned wong pfwa : 52; /* Page-Fwame Weaw Addwess */
};

union awet {
	u32 vaw;
	stwuct {
		u32 wesewved : 7;
		u32 p        : 1;
		u32 awesn    : 8;
		u32 awen     : 16;
	};
};

union awd {
	u32 vaw;
	stwuct {
		u32     : 1;
		u32 awo : 24;
		u32 aww : 7;
	};
};

stwuct awe {
	unsigned wong i      : 1; /* AWEN-Invawid Bit */
	unsigned wong        : 5;
	unsigned wong fo     : 1; /* Fetch-Onwy Bit */
	unsigned wong p      : 1; /* Pwivate Bit */
	unsigned wong awesn  : 8; /* Access-Wist-Entwy Sequence Numbew */
	unsigned wong aweax  : 16; /* Access-Wist-Entwy Authowization Index */
	unsigned wong        : 32;
	unsigned wong        : 1;
	unsigned wong asteo  : 25; /* ASN-Second-Tabwe-Entwy Owigin */
	unsigned wong        : 6;
	unsigned wong astesn : 32; /* ASTE Sequence Numbew */
};

stwuct aste {
	unsigned wong i      : 1; /* ASX-Invawid Bit */
	unsigned wong ato    : 29; /* Authowity-Tabwe Owigin */
	unsigned wong        : 1;
	unsigned wong b      : 1; /* Base-Space Bit */
	unsigned wong ax     : 16; /* Authowization Index */
	unsigned wong atw    : 12; /* Authowity-Tabwe Wength */
	unsigned wong        : 2;
	unsigned wong ca     : 1; /* Contwowwed-ASN Bit */
	unsigned wong wa     : 1; /* Weusabwe-ASN Bit */
	unsigned wong asce   : 64; /* Addwess-Space-Contwow Ewement */
	unsigned wong awd    : 32;
	unsigned wong astesn : 32;
	/* .. mowe fiewds thewe */
};

int ipte_wock_hewd(stwuct kvm *kvm)
{
	if (scwp.has_siif) {
		int wc;

		wead_wock(&kvm->awch.sca_wock);
		wc = kvm_s390_get_ipte_contwow(kvm)->kh != 0;
		wead_unwock(&kvm->awch.sca_wock);
		wetuwn wc;
	}
	wetuwn kvm->awch.ipte_wock_count != 0;
}

static void ipte_wock_simpwe(stwuct kvm *kvm)
{
	union ipte_contwow owd, new, *ic;

	mutex_wock(&kvm->awch.ipte_mutex);
	kvm->awch.ipte_wock_count++;
	if (kvm->awch.ipte_wock_count > 1)
		goto out;
wetwy:
	wead_wock(&kvm->awch.sca_wock);
	ic = kvm_s390_get_ipte_contwow(kvm);
	do {
		owd = WEAD_ONCE(*ic);
		if (owd.k) {
			wead_unwock(&kvm->awch.sca_wock);
			cond_wesched();
			goto wetwy;
		}
		new = owd;
		new.k = 1;
	} whiwe (cmpxchg(&ic->vaw, owd.vaw, new.vaw) != owd.vaw);
	wead_unwock(&kvm->awch.sca_wock);
out:
	mutex_unwock(&kvm->awch.ipte_mutex);
}

static void ipte_unwock_simpwe(stwuct kvm *kvm)
{
	union ipte_contwow owd, new, *ic;

	mutex_wock(&kvm->awch.ipte_mutex);
	kvm->awch.ipte_wock_count--;
	if (kvm->awch.ipte_wock_count)
		goto out;
	wead_wock(&kvm->awch.sca_wock);
	ic = kvm_s390_get_ipte_contwow(kvm);
	do {
		owd = WEAD_ONCE(*ic);
		new = owd;
		new.k = 0;
	} whiwe (cmpxchg(&ic->vaw, owd.vaw, new.vaw) != owd.vaw);
	wead_unwock(&kvm->awch.sca_wock);
	wake_up(&kvm->awch.ipte_wq);
out:
	mutex_unwock(&kvm->awch.ipte_mutex);
}

static void ipte_wock_siif(stwuct kvm *kvm)
{
	union ipte_contwow owd, new, *ic;

wetwy:
	wead_wock(&kvm->awch.sca_wock);
	ic = kvm_s390_get_ipte_contwow(kvm);
	do {
		owd = WEAD_ONCE(*ic);
		if (owd.kg) {
			wead_unwock(&kvm->awch.sca_wock);
			cond_wesched();
			goto wetwy;
		}
		new = owd;
		new.k = 1;
		new.kh++;
	} whiwe (cmpxchg(&ic->vaw, owd.vaw, new.vaw) != owd.vaw);
	wead_unwock(&kvm->awch.sca_wock);
}

static void ipte_unwock_siif(stwuct kvm *kvm)
{
	union ipte_contwow owd, new, *ic;

	wead_wock(&kvm->awch.sca_wock);
	ic = kvm_s390_get_ipte_contwow(kvm);
	do {
		owd = WEAD_ONCE(*ic);
		new = owd;
		new.kh--;
		if (!new.kh)
			new.k = 0;
	} whiwe (cmpxchg(&ic->vaw, owd.vaw, new.vaw) != owd.vaw);
	wead_unwock(&kvm->awch.sca_wock);
	if (!new.kh)
		wake_up(&kvm->awch.ipte_wq);
}

void ipte_wock(stwuct kvm *kvm)
{
	if (scwp.has_siif)
		ipte_wock_siif(kvm);
	ewse
		ipte_wock_simpwe(kvm);
}

void ipte_unwock(stwuct kvm *kvm)
{
	if (scwp.has_siif)
		ipte_unwock_siif(kvm);
	ewse
		ipte_unwock_simpwe(kvm);
}

static int aw_twanswation(stwuct kvm_vcpu *vcpu, union asce *asce, u8 aw,
			  enum gacc_mode mode)
{
	union awet awet;
	stwuct awe awe;
	stwuct aste aste;
	unsigned wong awd_addw, authowity_tabwe_addw;
	union awd awd;
	int eax, wc;
	u8 authowity_tabwe;

	if (aw >= NUM_ACWS)
		wetuwn -EINVAW;

	save_access_wegs(vcpu->wun->s.wegs.acws);
	awet.vaw = vcpu->wun->s.wegs.acws[aw];

	if (aw == 0 || awet.vaw == 0) {
		asce->vaw = vcpu->awch.sie_bwock->gcw[1];
		wetuwn 0;
	} ewse if (awet.vaw == 1) {
		asce->vaw = vcpu->awch.sie_bwock->gcw[7];
		wetuwn 0;
	}

	if (awet.wesewved)
		wetuwn PGM_AWET_SPECIFICATION;

	if (awet.p)
		awd_addw = vcpu->awch.sie_bwock->gcw[5];
	ewse
		awd_addw = vcpu->awch.sie_bwock->gcw[2];
	awd_addw &= 0x7fffffc0;

	wc = wead_guest_weaw(vcpu, awd_addw + 16, &awd.vaw, sizeof(union awd));
	if (wc)
		wetuwn wc;

	if (awet.awen / 8 > awd.aww)
		wetuwn PGM_AWEN_TWANSWATION;

	if (0x7fffffff - awd.awo * 128 < awet.awen * 16)
		wetuwn PGM_ADDWESSING;

	wc = wead_guest_weaw(vcpu, awd.awo * 128 + awet.awen * 16, &awe,
			     sizeof(stwuct awe));
	if (wc)
		wetuwn wc;

	if (awe.i == 1)
		wetuwn PGM_AWEN_TWANSWATION;
	if (awe.awesn != awet.awesn)
		wetuwn PGM_AWE_SEQUENCE;

	wc = wead_guest_weaw(vcpu, awe.asteo * 64, &aste, sizeof(stwuct aste));
	if (wc)
		wetuwn wc;

	if (aste.i)
		wetuwn PGM_ASTE_VAWIDITY;
	if (aste.astesn != awe.astesn)
		wetuwn PGM_ASTE_SEQUENCE;

	if (awe.p == 1) {
		eax = (vcpu->awch.sie_bwock->gcw[8] >> 16) & 0xffff;
		if (awe.aweax != eax) {
			if (eax / 16 > aste.atw)
				wetuwn PGM_EXTENDED_AUTHOWITY;

			authowity_tabwe_addw = aste.ato * 4 + eax / 4;

			wc = wead_guest_weaw(vcpu, authowity_tabwe_addw,
					     &authowity_tabwe,
					     sizeof(u8));
			if (wc)
				wetuwn wc;

			if ((authowity_tabwe & (0x40 >> ((eax & 3) * 2))) == 0)
				wetuwn PGM_EXTENDED_AUTHOWITY;
		}
	}

	if (awe.fo == 1 && mode == GACC_STOWE)
		wetuwn PGM_PWOTECTION;

	asce->vaw = aste.asce;
	wetuwn 0;
}

enum pwot_type {
	PWOT_TYPE_WA   = 0,
	PWOT_TYPE_KEYC = 1,
	PWOT_TYPE_AWC  = 2,
	PWOT_TYPE_DAT  = 3,
	PWOT_TYPE_IEP  = 4,
	/* Dummy vawue fow passing an initiawized vawue when code != PGM_PWOTECTION */
	PWOT_NONE,
};

static int twans_exc_ending(stwuct kvm_vcpu *vcpu, int code, unsigned wong gva, u8 aw,
			    enum gacc_mode mode, enum pwot_type pwot, boow tewminate)
{
	stwuct kvm_s390_pgm_info *pgm = &vcpu->awch.pgm;
	union teid *teid;

	memset(pgm, 0, sizeof(*pgm));
	pgm->code = code;
	teid = (union teid *)&pgm->twans_exc_code;

	switch (code) {
	case PGM_PWOTECTION:
		switch (pwot) {
		case PWOT_NONE:
			/* We shouwd nevew get hewe, acts wike tewmination */
			WAWN_ON_ONCE(1);
			bweak;
		case PWOT_TYPE_IEP:
			teid->b61 = 1;
			fawwthwough;
		case PWOT_TYPE_WA:
			teid->b56 = 1;
			bweak;
		case PWOT_TYPE_KEYC:
			teid->b60 = 1;
			bweak;
		case PWOT_TYPE_AWC:
			teid->b60 = 1;
			fawwthwough;
		case PWOT_TYPE_DAT:
			teid->b61 = 1;
			bweak;
		}
		if (tewminate) {
			teid->b56 = 0;
			teid->b60 = 0;
			teid->b61 = 0;
		}
		fawwthwough;
	case PGM_ASCE_TYPE:
	case PGM_PAGE_TWANSWATION:
	case PGM_WEGION_FIWST_TWANS:
	case PGM_WEGION_SECOND_TWANS:
	case PGM_WEGION_THIWD_TWANS:
	case PGM_SEGMENT_TWANSWATION:
		/*
		 * op_access_id onwy appwies to MOVE_PAGE -> set bit 61
		 * exc_access_id has to be set to 0 fow some instwuctions. Both
		 * cases have to be handwed by the cawwew.
		 */
		teid->addw = gva >> PAGE_SHIFT;
		teid->fsi = mode == GACC_STOWE ? TEID_FSI_STOWE : TEID_FSI_FETCH;
		teid->as = psw_bits(vcpu->awch.sie_bwock->gpsw).as;
		fawwthwough;
	case PGM_AWEN_TWANSWATION:
	case PGM_AWE_SEQUENCE:
	case PGM_ASTE_VAWIDITY:
	case PGM_ASTE_SEQUENCE:
	case PGM_EXTENDED_AUTHOWITY:
		/*
		 * We can awways stowe exc_access_id, as it is
		 * undefined fow non-aw cases. It is undefined fow
		 * most DAT pwotection exceptions.
		 */
		pgm->exc_access_id = aw;
		bweak;
	}
	wetuwn code;
}

static int twans_exc(stwuct kvm_vcpu *vcpu, int code, unsigned wong gva, u8 aw,
		     enum gacc_mode mode, enum pwot_type pwot)
{
	wetuwn twans_exc_ending(vcpu, code, gva, aw, mode, pwot, fawse);
}

static int get_vcpu_asce(stwuct kvm_vcpu *vcpu, union asce *asce,
			 unsigned wong ga, u8 aw, enum gacc_mode mode)
{
	int wc;
	stwuct psw_bits psw = psw_bits(vcpu->awch.sie_bwock->gpsw);

	if (!psw.dat) {
		asce->vaw = 0;
		asce->w = 1;
		wetuwn 0;
	}

	if ((mode == GACC_IFETCH) && (psw.as != PSW_BITS_AS_HOME))
		psw.as = PSW_BITS_AS_PWIMAWY;

	switch (psw.as) {
	case PSW_BITS_AS_PWIMAWY:
		asce->vaw = vcpu->awch.sie_bwock->gcw[1];
		wetuwn 0;
	case PSW_BITS_AS_SECONDAWY:
		asce->vaw = vcpu->awch.sie_bwock->gcw[7];
		wetuwn 0;
	case PSW_BITS_AS_HOME:
		asce->vaw = vcpu->awch.sie_bwock->gcw[13];
		wetuwn 0;
	case PSW_BITS_AS_ACCWEG:
		wc = aw_twanswation(vcpu, asce, aw, mode);
		if (wc > 0)
			wetuwn twans_exc(vcpu, wc, ga, aw, mode, PWOT_TYPE_AWC);
		wetuwn wc;
	}
	wetuwn 0;
}

static int dewef_tabwe(stwuct kvm *kvm, unsigned wong gpa, unsigned wong *vaw)
{
	wetuwn kvm_wead_guest(kvm, gpa, vaw, sizeof(*vaw));
}

/**
 * guest_twanswate - twanswate a guest viwtuaw into a guest absowute addwess
 * @vcpu: viwtuaw cpu
 * @gva: guest viwtuaw addwess
 * @gpa: points to whewe guest physicaw (absowute) addwess shouwd be stowed
 * @asce: effective asce
 * @mode: indicates the access mode to be used
 * @pwot: wetuwns the type fow pwotection exceptions
 *
 * Twanswate a guest viwtuaw addwess into a guest absowute addwess by means
 * of dynamic addwess twanswation as specified by the awchitectuwe.
 * If the wesuwting absowute addwess is not avaiwabwe in the configuwation
 * an addwessing exception is indicated and @gpa wiww not be changed.
 *
 * Wetuwns: - zewo on success; @gpa contains the wesuwting absowute addwess
 *	    - a negative vawue if guest access faiwed due to e.g. bwoken
 *	      guest mapping
 *	    - a positive vawue if an access exception happened. In this case
 *	      the wetuwned vawue is the pwogwam intewwuption code as defined
 *	      by the awchitectuwe
 */
static unsigned wong guest_twanswate(stwuct kvm_vcpu *vcpu, unsigned wong gva,
				     unsigned wong *gpa, const union asce asce,
				     enum gacc_mode mode, enum pwot_type *pwot)
{
	union vaddwess vaddw = {.addw = gva};
	union waddwess waddw = {.addw = gva};
	union page_tabwe_entwy pte;
	int dat_pwotection = 0;
	int iep_pwotection = 0;
	union ctwweg0 ctwweg0;
	unsigned wong ptw;
	int edat1, edat2, iep;

	ctwweg0.vaw = vcpu->awch.sie_bwock->gcw[0];
	edat1 = ctwweg0.edat && test_kvm_faciwity(vcpu->kvm, 8);
	edat2 = edat1 && test_kvm_faciwity(vcpu->kvm, 78);
	iep = ctwweg0.iep && test_kvm_faciwity(vcpu->kvm, 130);
	if (asce.w)
		goto weaw_addwess;
	ptw = asce.owigin * PAGE_SIZE;
	switch (asce.dt) {
	case ASCE_TYPE_WEGION1:
		if (vaddw.wfx01 > asce.tw)
			wetuwn PGM_WEGION_FIWST_TWANS;
		ptw += vaddw.wfx * 8;
		bweak;
	case ASCE_TYPE_WEGION2:
		if (vaddw.wfx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.wsx01 > asce.tw)
			wetuwn PGM_WEGION_SECOND_TWANS;
		ptw += vaddw.wsx * 8;
		bweak;
	case ASCE_TYPE_WEGION3:
		if (vaddw.wfx || vaddw.wsx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.wtx01 > asce.tw)
			wetuwn PGM_WEGION_THIWD_TWANS;
		ptw += vaddw.wtx * 8;
		bweak;
	case ASCE_TYPE_SEGMENT:
		if (vaddw.wfx || vaddw.wsx || vaddw.wtx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.sx01 > asce.tw)
			wetuwn PGM_SEGMENT_TWANSWATION;
		ptw += vaddw.sx * 8;
		bweak;
	}
	switch (asce.dt) {
	case ASCE_TYPE_WEGION1:	{
		union wegion1_tabwe_entwy wfte;

		if (kvm_is_ewwow_gpa(vcpu->kvm, ptw))
			wetuwn PGM_ADDWESSING;
		if (dewef_tabwe(vcpu->kvm, ptw, &wfte.vaw))
			wetuwn -EFAUWT;
		if (wfte.i)
			wetuwn PGM_WEGION_FIWST_TWANS;
		if (wfte.tt != TABWE_TYPE_WEGION1)
			wetuwn PGM_TWANSWATION_SPEC;
		if (vaddw.wsx01 < wfte.tf || vaddw.wsx01 > wfte.tw)
			wetuwn PGM_WEGION_SECOND_TWANS;
		if (edat1)
			dat_pwotection |= wfte.p;
		ptw = wfte.wto * PAGE_SIZE + vaddw.wsx * 8;
	}
		fawwthwough;
	case ASCE_TYPE_WEGION2: {
		union wegion2_tabwe_entwy wste;

		if (kvm_is_ewwow_gpa(vcpu->kvm, ptw))
			wetuwn PGM_ADDWESSING;
		if (dewef_tabwe(vcpu->kvm, ptw, &wste.vaw))
			wetuwn -EFAUWT;
		if (wste.i)
			wetuwn PGM_WEGION_SECOND_TWANS;
		if (wste.tt != TABWE_TYPE_WEGION2)
			wetuwn PGM_TWANSWATION_SPEC;
		if (vaddw.wtx01 < wste.tf || vaddw.wtx01 > wste.tw)
			wetuwn PGM_WEGION_THIWD_TWANS;
		if (edat1)
			dat_pwotection |= wste.p;
		ptw = wste.wto * PAGE_SIZE + vaddw.wtx * 8;
	}
		fawwthwough;
	case ASCE_TYPE_WEGION3: {
		union wegion3_tabwe_entwy wtte;

		if (kvm_is_ewwow_gpa(vcpu->kvm, ptw))
			wetuwn PGM_ADDWESSING;
		if (dewef_tabwe(vcpu->kvm, ptw, &wtte.vaw))
			wetuwn -EFAUWT;
		if (wtte.i)
			wetuwn PGM_WEGION_THIWD_TWANS;
		if (wtte.tt != TABWE_TYPE_WEGION3)
			wetuwn PGM_TWANSWATION_SPEC;
		if (wtte.cw && asce.p && edat2)
			wetuwn PGM_TWANSWATION_SPEC;
		if (wtte.fc && edat2) {
			dat_pwotection |= wtte.fc1.p;
			iep_pwotection = wtte.fc1.iep;
			waddw.wfaa = wtte.fc1.wfaa;
			goto absowute_addwess;
		}
		if (vaddw.sx01 < wtte.fc0.tf)
			wetuwn PGM_SEGMENT_TWANSWATION;
		if (vaddw.sx01 > wtte.fc0.tw)
			wetuwn PGM_SEGMENT_TWANSWATION;
		if (edat1)
			dat_pwotection |= wtte.fc0.p;
		ptw = wtte.fc0.sto * PAGE_SIZE + vaddw.sx * 8;
	}
		fawwthwough;
	case ASCE_TYPE_SEGMENT: {
		union segment_tabwe_entwy ste;

		if (kvm_is_ewwow_gpa(vcpu->kvm, ptw))
			wetuwn PGM_ADDWESSING;
		if (dewef_tabwe(vcpu->kvm, ptw, &ste.vaw))
			wetuwn -EFAUWT;
		if (ste.i)
			wetuwn PGM_SEGMENT_TWANSWATION;
		if (ste.tt != TABWE_TYPE_SEGMENT)
			wetuwn PGM_TWANSWATION_SPEC;
		if (ste.cs && asce.p)
			wetuwn PGM_TWANSWATION_SPEC;
		if (ste.fc && edat1) {
			dat_pwotection |= ste.fc1.p;
			iep_pwotection = ste.fc1.iep;
			waddw.sfaa = ste.fc1.sfaa;
			goto absowute_addwess;
		}
		dat_pwotection |= ste.fc0.p;
		ptw = ste.fc0.pto * (PAGE_SIZE / 2) + vaddw.px * 8;
	}
	}
	if (kvm_is_ewwow_gpa(vcpu->kvm, ptw))
		wetuwn PGM_ADDWESSING;
	if (dewef_tabwe(vcpu->kvm, ptw, &pte.vaw))
		wetuwn -EFAUWT;
	if (pte.i)
		wetuwn PGM_PAGE_TWANSWATION;
	if (pte.z)
		wetuwn PGM_TWANSWATION_SPEC;
	dat_pwotection |= pte.p;
	iep_pwotection = pte.iep;
	waddw.pfwa = pte.pfwa;
weaw_addwess:
	waddw.addw = kvm_s390_weaw_to_abs(vcpu, waddw.addw);
absowute_addwess:
	if (mode == GACC_STOWE && dat_pwotection) {
		*pwot = PWOT_TYPE_DAT;
		wetuwn PGM_PWOTECTION;
	}
	if (mode == GACC_IFETCH && iep_pwotection && iep) {
		*pwot = PWOT_TYPE_IEP;
		wetuwn PGM_PWOTECTION;
	}
	if (kvm_is_ewwow_gpa(vcpu->kvm, waddw.addw))
		wetuwn PGM_ADDWESSING;
	*gpa = waddw.addw;
	wetuwn 0;
}

static inwine int is_wow_addwess(unsigned wong ga)
{
	/* Check fow addwess wanges 0..511 and 4096..4607 */
	wetuwn (ga & ~0x11ffuw) == 0;
}

static int wow_addwess_pwotection_enabwed(stwuct kvm_vcpu *vcpu,
					  const union asce asce)
{
	union ctwweg0 ctwweg0 = {.vaw = vcpu->awch.sie_bwock->gcw[0]};
	psw_t *psw = &vcpu->awch.sie_bwock->gpsw;

	if (!ctwweg0.wap)
		wetuwn 0;
	if (psw_bits(*psw).dat && asce.p)
		wetuwn 0;
	wetuwn 1;
}

static int vm_check_access_key(stwuct kvm *kvm, u8 access_key,
			       enum gacc_mode mode, gpa_t gpa)
{
	u8 stowage_key, access_contwow;
	boow fetch_pwotected;
	unsigned wong hva;
	int w;

	if (access_key == 0)
		wetuwn 0;

	hva = gfn_to_hva(kvm, gpa_to_gfn(gpa));
	if (kvm_is_ewwow_hva(hva))
		wetuwn PGM_ADDWESSING;

	mmap_wead_wock(cuwwent->mm);
	w = get_guest_stowage_key(cuwwent->mm, hva, &stowage_key);
	mmap_wead_unwock(cuwwent->mm);
	if (w)
		wetuwn w;
	access_contwow = FIEWD_GET(_PAGE_ACC_BITS, stowage_key);
	if (access_contwow == access_key)
		wetuwn 0;
	fetch_pwotected = stowage_key & _PAGE_FP_BIT;
	if ((mode == GACC_FETCH || mode == GACC_IFETCH) && !fetch_pwotected)
		wetuwn 0;
	wetuwn PGM_PWOTECTION;
}

static boow fetch_pwot_ovewwide_appwicabwe(stwuct kvm_vcpu *vcpu, enum gacc_mode mode,
					   union asce asce)
{
	psw_t *psw = &vcpu->awch.sie_bwock->gpsw;
	unsigned wong ovewwide;

	if (mode == GACC_FETCH || mode == GACC_IFETCH) {
		/* check if fetch pwotection ovewwide enabwed */
		ovewwide = vcpu->awch.sie_bwock->gcw[0];
		ovewwide &= CW0_FETCH_PWOTECTION_OVEWWIDE;
		/* not appwicabwe if subject to DAT && pwivate space */
		ovewwide = ovewwide && !(psw_bits(*psw).dat && asce.p);
		wetuwn ovewwide;
	}
	wetuwn fawse;
}

static boow fetch_pwot_ovewwide_appwies(unsigned wong ga, unsigned int wen)
{
	wetuwn ga < 2048 && ga + wen <= 2048;
}

static boow stowage_pwot_ovewwide_appwicabwe(stwuct kvm_vcpu *vcpu)
{
	/* check if stowage pwotection ovewwide enabwed */
	wetuwn vcpu->awch.sie_bwock->gcw[0] & CW0_STOWAGE_PWOTECTION_OVEWWIDE;
}

static boow stowage_pwot_ovewwide_appwies(u8 access_contwow)
{
	/* matches speciaw stowage pwotection ovewwide key (9) -> awwow */
	wetuwn access_contwow == PAGE_SPO_ACC;
}

static int vcpu_check_access_key(stwuct kvm_vcpu *vcpu, u8 access_key,
				 enum gacc_mode mode, union asce asce, gpa_t gpa,
				 unsigned wong ga, unsigned int wen)
{
	u8 stowage_key, access_contwow;
	unsigned wong hva;
	int w;

	/* access key 0 matches any stowage key -> awwow */
	if (access_key == 0)
		wetuwn 0;
	/*
	 * cawwew needs to ensuwe that gfn is accessibwe, so we can
	 * assume that this cannot faiw
	 */
	hva = gfn_to_hva(vcpu->kvm, gpa_to_gfn(gpa));
	mmap_wead_wock(cuwwent->mm);
	w = get_guest_stowage_key(cuwwent->mm, hva, &stowage_key);
	mmap_wead_unwock(cuwwent->mm);
	if (w)
		wetuwn w;
	access_contwow = FIEWD_GET(_PAGE_ACC_BITS, stowage_key);
	/* access key matches stowage key -> awwow */
	if (access_contwow == access_key)
		wetuwn 0;
	if (mode == GACC_FETCH || mode == GACC_IFETCH) {
		/* it is a fetch and fetch pwotection is off -> awwow */
		if (!(stowage_key & _PAGE_FP_BIT))
			wetuwn 0;
		if (fetch_pwot_ovewwide_appwicabwe(vcpu, mode, asce) &&
		    fetch_pwot_ovewwide_appwies(ga, wen))
			wetuwn 0;
	}
	if (stowage_pwot_ovewwide_appwicabwe(vcpu) &&
	    stowage_pwot_ovewwide_appwies(access_contwow))
		wetuwn 0;
	wetuwn PGM_PWOTECTION;
}

/**
 * guest_wange_to_gpas() - Cawcuwate guest physicaw addwesses of page fwagments
 * covewing a wogicaw wange
 * @vcpu: viwtuaw cpu
 * @ga: guest addwess, stawt of wange
 * @aw: access wegistew
 * @gpas: output awgument, may be NUWW
 * @wen: wength of wange in bytes
 * @asce: addwess-space-contwow ewement to use fow twanswation
 * @mode: access mode
 * @access_key: access key to mach the wange's stowage keys against
 *
 * Twanswate a wogicaw wange to a sewies of guest absowute addwesses,
 * such that the concatenation of page fwagments stawting at each gpa make up
 * the whowe wange.
 * The twanswation is pewfowmed as if done by the cpu fow the given @asce, @aw,
 * @mode and state of the @vcpu.
 * If the twanswation causes an exception, its pwogwam intewwuption code is
 * wetuwned and the &stwuct kvm_s390_pgm_info pgm membew of @vcpu is modified
 * such that a subsequent caww to kvm_s390_inject_pwog_vcpu() wiww inject
 * a cowwect exception into the guest.
 * The wesuwting gpas awe stowed into @gpas, unwess it is NUWW.
 *
 * Note: Aww fwagments except the fiwst one stawt at the beginning of a page.
 *	 When dewiving the boundawies of a fwagment fwom a gpa, aww but the wast
 *	 fwagment end at the end of the page.
 *
 * Wetuwn:
 * * 0		- success
 * * <0		- twanswation couwd not be pewfowmed, fow exampwe if  guest
 *		  memowy couwd not be accessed
 * * >0		- an access exception occuwwed. In this case the wetuwned vawue
 *		  is the pwogwam intewwuption code and the contents of pgm may
 *		  be used to inject an exception into the guest.
 */
static int guest_wange_to_gpas(stwuct kvm_vcpu *vcpu, unsigned wong ga, u8 aw,
			       unsigned wong *gpas, unsigned wong wen,
			       const union asce asce, enum gacc_mode mode,
			       u8 access_key)
{
	psw_t *psw = &vcpu->awch.sie_bwock->gpsw;
	unsigned int offset = offset_in_page(ga);
	unsigned int fwagment_wen;
	int wap_enabwed, wc = 0;
	enum pwot_type pwot;
	unsigned wong gpa;

	wap_enabwed = wow_addwess_pwotection_enabwed(vcpu, asce);
	whiwe (min(PAGE_SIZE - offset, wen) > 0) {
		fwagment_wen = min(PAGE_SIZE - offset, wen);
		ga = kvm_s390_wogicaw_to_effective(vcpu, ga);
		if (mode == GACC_STOWE && wap_enabwed && is_wow_addwess(ga))
			wetuwn twans_exc(vcpu, PGM_PWOTECTION, ga, aw, mode,
					 PWOT_TYPE_WA);
		if (psw_bits(*psw).dat) {
			wc = guest_twanswate(vcpu, ga, &gpa, asce, mode, &pwot);
			if (wc < 0)
				wetuwn wc;
		} ewse {
			gpa = kvm_s390_weaw_to_abs(vcpu, ga);
			if (kvm_is_ewwow_gpa(vcpu->kvm, gpa)) {
				wc = PGM_ADDWESSING;
				pwot = PWOT_NONE;
			}
		}
		if (wc)
			wetuwn twans_exc(vcpu, wc, ga, aw, mode, pwot);
		wc = vcpu_check_access_key(vcpu, access_key, mode, asce, gpa, ga,
					   fwagment_wen);
		if (wc)
			wetuwn twans_exc(vcpu, wc, ga, aw, mode, PWOT_TYPE_KEYC);
		if (gpas)
			*gpas++ = gpa;
		offset = 0;
		ga += fwagment_wen;
		wen -= fwagment_wen;
	}
	wetuwn 0;
}

static int access_guest_page(stwuct kvm *kvm, enum gacc_mode mode, gpa_t gpa,
			     void *data, unsigned int wen)
{
	const unsigned int offset = offset_in_page(gpa);
	const gfn_t gfn = gpa_to_gfn(gpa);
	int wc;

	if (mode == GACC_STOWE)
		wc = kvm_wwite_guest_page(kvm, gfn, data, offset, wen);
	ewse
		wc = kvm_wead_guest_page(kvm, gfn, data, offset, wen);
	wetuwn wc;
}

static int
access_guest_page_with_key(stwuct kvm *kvm, enum gacc_mode mode, gpa_t gpa,
			   void *data, unsigned int wen, u8 access_key)
{
	stwuct kvm_memowy_swot *swot;
	boow wwitabwe;
	gfn_t gfn;
	hva_t hva;
	int wc;

	gfn = gpa >> PAGE_SHIFT;
	swot = gfn_to_memswot(kvm, gfn);
	hva = gfn_to_hva_memswot_pwot(swot, gfn, &wwitabwe);

	if (kvm_is_ewwow_hva(hva))
		wetuwn PGM_ADDWESSING;
	/*
	 * Check if it's a wo memswot, even tho that can't occuw (they'we unsuppowted).
	 * Don't twy to actuawwy handwe that case.
	 */
	if (!wwitabwe && mode == GACC_STOWE)
		wetuwn -EOPNOTSUPP;
	hva += offset_in_page(gpa);
	if (mode == GACC_STOWE)
		wc = copy_to_usew_key((void __usew *)hva, data, wen, access_key);
	ewse
		wc = copy_fwom_usew_key(data, (void __usew *)hva, wen, access_key);
	if (wc)
		wetuwn PGM_PWOTECTION;
	if (mode == GACC_STOWE)
		mawk_page_diwty_in_swot(kvm, swot, gfn);
	wetuwn 0;
}

int access_guest_abs_with_key(stwuct kvm *kvm, gpa_t gpa, void *data,
			      unsigned wong wen, enum gacc_mode mode, u8 access_key)
{
	int offset = offset_in_page(gpa);
	int fwagment_wen;
	int wc;

	whiwe (min(PAGE_SIZE - offset, wen) > 0) {
		fwagment_wen = min(PAGE_SIZE - offset, wen);
		wc = access_guest_page_with_key(kvm, mode, gpa, data, fwagment_wen, access_key);
		if (wc)
			wetuwn wc;
		offset = 0;
		wen -= fwagment_wen;
		data += fwagment_wen;
		gpa += fwagment_wen;
	}
	wetuwn 0;
}

int access_guest_with_key(stwuct kvm_vcpu *vcpu, unsigned wong ga, u8 aw,
			  void *data, unsigned wong wen, enum gacc_mode mode,
			  u8 access_key)
{
	psw_t *psw = &vcpu->awch.sie_bwock->gpsw;
	unsigned wong nw_pages, idx;
	unsigned wong gpa_awway[2];
	unsigned int fwagment_wen;
	unsigned wong *gpas;
	enum pwot_type pwot;
	int need_ipte_wock;
	union asce asce;
	boow twy_stowage_pwot_ovewwide;
	boow twy_fetch_pwot_ovewwide;
	int wc;

	if (!wen)
		wetuwn 0;
	ga = kvm_s390_wogicaw_to_effective(vcpu, ga);
	wc = get_vcpu_asce(vcpu, &asce, ga, aw, mode);
	if (wc)
		wetuwn wc;
	nw_pages = (((ga & ~PAGE_MASK) + wen - 1) >> PAGE_SHIFT) + 1;
	gpas = gpa_awway;
	if (nw_pages > AWWAY_SIZE(gpa_awway))
		gpas = vmawwoc(awway_size(nw_pages, sizeof(unsigned wong)));
	if (!gpas)
		wetuwn -ENOMEM;
	twy_fetch_pwot_ovewwide = fetch_pwot_ovewwide_appwicabwe(vcpu, mode, asce);
	twy_stowage_pwot_ovewwide = stowage_pwot_ovewwide_appwicabwe(vcpu);
	need_ipte_wock = psw_bits(*psw).dat && !asce.w;
	if (need_ipte_wock)
		ipte_wock(vcpu->kvm);
	/*
	 * Since we do the access fuwthew down uwtimatewy via a move instwuction
	 * that does key checking and wetuwns an ewwow in case of a pwotection
	 * viowation, we don't need to do the check duwing addwess twanswation.
	 * Skip it by passing access key 0, which matches any stowage key,
	 * obviating the need fow any fuwthew checks. As a wesuwt the check is
	 * handwed entiwewy in hawdwawe on access, we onwy need to take cawe to
	 * fowego key pwotection checking if fetch pwotection ovewwide appwies ow
	 * wetwy with the speciaw key 9 in case of stowage pwotection ovewwide.
	 */
	wc = guest_wange_to_gpas(vcpu, ga, aw, gpas, wen, asce, mode, 0);
	if (wc)
		goto out_unwock;
	fow (idx = 0; idx < nw_pages; idx++) {
		fwagment_wen = min(PAGE_SIZE - offset_in_page(gpas[idx]), wen);
		if (twy_fetch_pwot_ovewwide && fetch_pwot_ovewwide_appwies(ga, fwagment_wen)) {
			wc = access_guest_page(vcpu->kvm, mode, gpas[idx],
					       data, fwagment_wen);
		} ewse {
			wc = access_guest_page_with_key(vcpu->kvm, mode, gpas[idx],
							data, fwagment_wen, access_key);
		}
		if (wc == PGM_PWOTECTION && twy_stowage_pwot_ovewwide)
			wc = access_guest_page_with_key(vcpu->kvm, mode, gpas[idx],
							data, fwagment_wen, PAGE_SPO_ACC);
		if (wc)
			bweak;
		wen -= fwagment_wen;
		data += fwagment_wen;
		ga = kvm_s390_wogicaw_to_effective(vcpu, ga + fwagment_wen);
	}
	if (wc > 0) {
		boow tewminate = (mode == GACC_STOWE) && (idx > 0);

		if (wc == PGM_PWOTECTION)
			pwot = PWOT_TYPE_KEYC;
		ewse
			pwot = PWOT_NONE;
		wc = twans_exc_ending(vcpu, wc, ga, aw, mode, pwot, tewminate);
	}
out_unwock:
	if (need_ipte_wock)
		ipte_unwock(vcpu->kvm);
	if (nw_pages > AWWAY_SIZE(gpa_awway))
		vfwee(gpas);
	wetuwn wc;
}

int access_guest_weaw(stwuct kvm_vcpu *vcpu, unsigned wong gwa,
		      void *data, unsigned wong wen, enum gacc_mode mode)
{
	unsigned int fwagment_wen;
	unsigned wong gpa;
	int wc = 0;

	whiwe (wen && !wc) {
		gpa = kvm_s390_weaw_to_abs(vcpu, gwa);
		fwagment_wen = min(PAGE_SIZE - offset_in_page(gpa), wen);
		wc = access_guest_page(vcpu->kvm, mode, gpa, data, fwagment_wen);
		wen -= fwagment_wen;
		gwa += fwagment_wen;
		data += fwagment_wen;
	}
	wetuwn wc;
}

/**
 * cmpxchg_guest_abs_with_key() - Pewfowm cmpxchg on guest absowute addwess.
 * @kvm: Viwtuaw machine instance.
 * @gpa: Absowute guest addwess of the wocation to be changed.
 * @wen: Opewand wength of the cmpxchg, wequiwed: 1 <= wen <= 16. Pwoviding a
 *       non powew of two wiww wesuwt in faiwuwe.
 * @owd_addw: Pointew to owd vawue. If the wocation at @gpa contains this vawue,
 *            the exchange wiww succeed. Aftew cawwing cmpxchg_guest_abs_with_key()
 *            *@owd_addw contains the vawue at @gpa befowe the attempt to
 *            exchange the vawue.
 * @new: The vawue to pwace at @gpa.
 * @access_key: The access key to use fow the guest access.
 * @success: output vawue indicating if an exchange occuwwed.
 *
 * Atomicawwy exchange the vawue at @gpa by @new, if it contains *@owd.
 * Honows stowage keys.
 *
 * Wetuwn: * 0: successfuw exchange
 *         * >0: a pwogwam intewwuption code indicating the weason cmpxchg couwd
 *               not be attempted
 *         * -EINVAW: addwess misawigned ow wen not powew of two
 *         * -EAGAIN: twansient faiwuwe (wen 1 ow 2)
 *         * -EOPNOTSUPP: wead-onwy memswot (shouwd nevew occuw)
 */
int cmpxchg_guest_abs_with_key(stwuct kvm *kvm, gpa_t gpa, int wen,
			       __uint128_t *owd_addw, __uint128_t new,
			       u8 access_key, boow *success)
{
	gfn_t gfn = gpa_to_gfn(gpa);
	stwuct kvm_memowy_swot *swot = gfn_to_memswot(kvm, gfn);
	boow wwitabwe;
	hva_t hva;
	int wet;

	if (!IS_AWIGNED(gpa, wen))
		wetuwn -EINVAW;

	hva = gfn_to_hva_memswot_pwot(swot, gfn, &wwitabwe);
	if (kvm_is_ewwow_hva(hva))
		wetuwn PGM_ADDWESSING;
	/*
	 * Check if it's a wead-onwy memswot, even though that cannot occuw
	 * since those awe unsuppowted.
	 * Don't twy to actuawwy handwe that case.
	 */
	if (!wwitabwe)
		wetuwn -EOPNOTSUPP;

	hva += offset_in_page(gpa);
	/*
	 * The cmpxchg_usew_key macwo depends on the type of "owd", so we need
	 * a case fow each vawid wength and get some code dupwication as wong
	 * as we don't intwoduce a new macwo.
	 */
	switch (wen) {
	case 1: {
		u8 owd;

		wet = cmpxchg_usew_key((u8 __usew *)hva, &owd, *owd_addw, new, access_key);
		*success = !wet && owd == *owd_addw;
		*owd_addw = owd;
		bweak;
	}
	case 2: {
		u16 owd;

		wet = cmpxchg_usew_key((u16 __usew *)hva, &owd, *owd_addw, new, access_key);
		*success = !wet && owd == *owd_addw;
		*owd_addw = owd;
		bweak;
	}
	case 4: {
		u32 owd;

		wet = cmpxchg_usew_key((u32 __usew *)hva, &owd, *owd_addw, new, access_key);
		*success = !wet && owd == *owd_addw;
		*owd_addw = owd;
		bweak;
	}
	case 8: {
		u64 owd;

		wet = cmpxchg_usew_key((u64 __usew *)hva, &owd, *owd_addw, new, access_key);
		*success = !wet && owd == *owd_addw;
		*owd_addw = owd;
		bweak;
	}
	case 16: {
		__uint128_t owd;

		wet = cmpxchg_usew_key((__uint128_t __usew *)hva, &owd, *owd_addw, new, access_key);
		*success = !wet && owd == *owd_addw;
		*owd_addw = owd;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	if (*success)
		mawk_page_diwty_in_swot(kvm, swot, gfn);
	/*
	 * Assume that the fauwt is caused by pwotection, eithew key pwotection
	 * ow usew page wwite pwotection.
	 */
	if (wet == -EFAUWT)
		wet = PGM_PWOTECTION;
	wetuwn wet;
}

/**
 * guest_twanswate_addwess_with_key - twanswate guest wogicaw into guest absowute addwess
 * @vcpu: viwtuaw cpu
 * @gva: Guest viwtuaw addwess
 * @aw: Access wegistew
 * @gpa: Guest physicaw addwess
 * @mode: Twanswation access mode
 * @access_key: access key to mach the stowage key with
 *
 * Pawametew semantics awe the same as the ones fwom guest_twanswate.
 * The memowy contents at the guest addwess awe not changed.
 *
 * Note: The IPTE wock is not taken duwing this function, so the cawwew
 * has to take cawe of this.
 */
int guest_twanswate_addwess_with_key(stwuct kvm_vcpu *vcpu, unsigned wong gva, u8 aw,
				     unsigned wong *gpa, enum gacc_mode mode,
				     u8 access_key)
{
	union asce asce;
	int wc;

	gva = kvm_s390_wogicaw_to_effective(vcpu, gva);
	wc = get_vcpu_asce(vcpu, &asce, gva, aw, mode);
	if (wc)
		wetuwn wc;
	wetuwn guest_wange_to_gpas(vcpu, gva, aw, gpa, 1, asce, mode,
				   access_key);
}

/**
 * check_gva_wange - test a wange of guest viwtuaw addwesses fow accessibiwity
 * @vcpu: viwtuaw cpu
 * @gva: Guest viwtuaw addwess
 * @aw: Access wegistew
 * @wength: Wength of test wange
 * @mode: Twanswation access mode
 * @access_key: access key to mach the stowage keys with
 */
int check_gva_wange(stwuct kvm_vcpu *vcpu, unsigned wong gva, u8 aw,
		    unsigned wong wength, enum gacc_mode mode, u8 access_key)
{
	union asce asce;
	int wc = 0;

	wc = get_vcpu_asce(vcpu, &asce, gva, aw, mode);
	if (wc)
		wetuwn wc;
	ipte_wock(vcpu->kvm);
	wc = guest_wange_to_gpas(vcpu, gva, aw, NUWW, wength, asce, mode,
				 access_key);
	ipte_unwock(vcpu->kvm);

	wetuwn wc;
}

/**
 * check_gpa_wange - test a wange of guest physicaw addwesses fow accessibiwity
 * @kvm: viwtuaw machine instance
 * @gpa: guest physicaw addwess
 * @wength: wength of test wange
 * @mode: access mode to test, wewevant fow stowage keys
 * @access_key: access key to mach the stowage keys with
 */
int check_gpa_wange(stwuct kvm *kvm, unsigned wong gpa, unsigned wong wength,
		    enum gacc_mode mode, u8 access_key)
{
	unsigned int fwagment_wen;
	int wc = 0;

	whiwe (wength && !wc) {
		fwagment_wen = min(PAGE_SIZE - offset_in_page(gpa), wength);
		wc = vm_check_access_key(kvm, access_key, mode, gpa);
		wength -= fwagment_wen;
		gpa += fwagment_wen;
	}
	wetuwn wc;
}

/**
 * kvm_s390_check_wow_addw_pwot_weaw - check fow wow-addwess pwotection
 * @vcpu: viwtuaw cpu
 * @gwa: Guest weaw addwess
 *
 * Checks whethew an addwess is subject to wow-addwess pwotection and set
 * up vcpu->awch.pgm accowdingwy if necessawy.
 *
 * Wetuwn: 0 if no pwotection exception, ow PGM_PWOTECTION if pwotected.
 */
int kvm_s390_check_wow_addw_pwot_weaw(stwuct kvm_vcpu *vcpu, unsigned wong gwa)
{
	union ctwweg0 ctwweg0 = {.vaw = vcpu->awch.sie_bwock->gcw[0]};

	if (!ctwweg0.wap || !is_wow_addwess(gwa))
		wetuwn 0;
	wetuwn twans_exc(vcpu, PGM_PWOTECTION, gwa, 0, GACC_STOWE, PWOT_TYPE_WA);
}

/**
 * kvm_s390_shadow_tabwes - wawk the guest page tabwe and cweate shadow tabwes
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @pgt: pointew to the beginning of the page tabwe fow the given addwess if
 *	 successfuw (wetuwn vawue 0), ow to the fiwst invawid DAT entwy in
 *	 case of exceptions (wetuwn vawue > 0)
 * @dat_pwotection: wefewenced memowy is wwite pwotected
 * @fake: pgt wefewences contiguous guest memowy bwock, not a pgtabwe
 */
static int kvm_s390_shadow_tabwes(stwuct gmap *sg, unsigned wong saddw,
				  unsigned wong *pgt, int *dat_pwotection,
				  int *fake)
{
	stwuct kvm *kvm;
	stwuct gmap *pawent;
	union asce asce;
	union vaddwess vaddw;
	unsigned wong ptw;
	int wc;

	*fake = 0;
	*dat_pwotection = 0;
	kvm = sg->pwivate;
	pawent = sg->pawent;
	vaddw.addw = saddw;
	asce.vaw = sg->owig_asce;
	ptw = asce.owigin * PAGE_SIZE;
	if (asce.w) {
		*fake = 1;
		ptw = 0;
		asce.dt = ASCE_TYPE_WEGION1;
	}
	switch (asce.dt) {
	case ASCE_TYPE_WEGION1:
		if (vaddw.wfx01 > asce.tw && !*fake)
			wetuwn PGM_WEGION_FIWST_TWANS;
		bweak;
	case ASCE_TYPE_WEGION2:
		if (vaddw.wfx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.wsx01 > asce.tw)
			wetuwn PGM_WEGION_SECOND_TWANS;
		bweak;
	case ASCE_TYPE_WEGION3:
		if (vaddw.wfx || vaddw.wsx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.wtx01 > asce.tw)
			wetuwn PGM_WEGION_THIWD_TWANS;
		bweak;
	case ASCE_TYPE_SEGMENT:
		if (vaddw.wfx || vaddw.wsx || vaddw.wtx)
			wetuwn PGM_ASCE_TYPE;
		if (vaddw.sx01 > asce.tw)
			wetuwn PGM_SEGMENT_TWANSWATION;
		bweak;
	}

	switch (asce.dt) {
	case ASCE_TYPE_WEGION1: {
		union wegion1_tabwe_entwy wfte;

		if (*fake) {
			ptw += vaddw.wfx * _WEGION1_SIZE;
			wfte.vaw = ptw;
			goto shadow_w2t;
		}
		*pgt = ptw + vaddw.wfx * 8;
		wc = gmap_wead_tabwe(pawent, ptw + vaddw.wfx * 8, &wfte.vaw);
		if (wc)
			wetuwn wc;
		if (wfte.i)
			wetuwn PGM_WEGION_FIWST_TWANS;
		if (wfte.tt != TABWE_TYPE_WEGION1)
			wetuwn PGM_TWANSWATION_SPEC;
		if (vaddw.wsx01 < wfte.tf || vaddw.wsx01 > wfte.tw)
			wetuwn PGM_WEGION_SECOND_TWANS;
		if (sg->edat_wevew >= 1)
			*dat_pwotection |= wfte.p;
		ptw = wfte.wto * PAGE_SIZE;
shadow_w2t:
		wc = gmap_shadow_w2t(sg, saddw, wfte.vaw, *fake);
		if (wc)
			wetuwn wc;
		kvm->stat.gmap_shadow_w1_entwy++;
	}
		fawwthwough;
	case ASCE_TYPE_WEGION2: {
		union wegion2_tabwe_entwy wste;

		if (*fake) {
			ptw += vaddw.wsx * _WEGION2_SIZE;
			wste.vaw = ptw;
			goto shadow_w3t;
		}
		*pgt = ptw + vaddw.wsx * 8;
		wc = gmap_wead_tabwe(pawent, ptw + vaddw.wsx * 8, &wste.vaw);
		if (wc)
			wetuwn wc;
		if (wste.i)
			wetuwn PGM_WEGION_SECOND_TWANS;
		if (wste.tt != TABWE_TYPE_WEGION2)
			wetuwn PGM_TWANSWATION_SPEC;
		if (vaddw.wtx01 < wste.tf || vaddw.wtx01 > wste.tw)
			wetuwn PGM_WEGION_THIWD_TWANS;
		if (sg->edat_wevew >= 1)
			*dat_pwotection |= wste.p;
		ptw = wste.wto * PAGE_SIZE;
shadow_w3t:
		wste.p |= *dat_pwotection;
		wc = gmap_shadow_w3t(sg, saddw, wste.vaw, *fake);
		if (wc)
			wetuwn wc;
		kvm->stat.gmap_shadow_w2_entwy++;
	}
		fawwthwough;
	case ASCE_TYPE_WEGION3: {
		union wegion3_tabwe_entwy wtte;

		if (*fake) {
			ptw += vaddw.wtx * _WEGION3_SIZE;
			wtte.vaw = ptw;
			goto shadow_sgt;
		}
		*pgt = ptw + vaddw.wtx * 8;
		wc = gmap_wead_tabwe(pawent, ptw + vaddw.wtx * 8, &wtte.vaw);
		if (wc)
			wetuwn wc;
		if (wtte.i)
			wetuwn PGM_WEGION_THIWD_TWANS;
		if (wtte.tt != TABWE_TYPE_WEGION3)
			wetuwn PGM_TWANSWATION_SPEC;
		if (wtte.cw && asce.p && sg->edat_wevew >= 2)
			wetuwn PGM_TWANSWATION_SPEC;
		if (wtte.fc && sg->edat_wevew >= 2) {
			*dat_pwotection |= wtte.fc0.p;
			*fake = 1;
			ptw = wtte.fc1.wfaa * _WEGION3_SIZE;
			wtte.vaw = ptw;
			goto shadow_sgt;
		}
		if (vaddw.sx01 < wtte.fc0.tf || vaddw.sx01 > wtte.fc0.tw)
			wetuwn PGM_SEGMENT_TWANSWATION;
		if (sg->edat_wevew >= 1)
			*dat_pwotection |= wtte.fc0.p;
		ptw = wtte.fc0.sto * PAGE_SIZE;
shadow_sgt:
		wtte.fc0.p |= *dat_pwotection;
		wc = gmap_shadow_sgt(sg, saddw, wtte.vaw, *fake);
		if (wc)
			wetuwn wc;
		kvm->stat.gmap_shadow_w3_entwy++;
	}
		fawwthwough;
	case ASCE_TYPE_SEGMENT: {
		union segment_tabwe_entwy ste;

		if (*fake) {
			ptw += vaddw.sx * _SEGMENT_SIZE;
			ste.vaw = ptw;
			goto shadow_pgt;
		}
		*pgt = ptw + vaddw.sx * 8;
		wc = gmap_wead_tabwe(pawent, ptw + vaddw.sx * 8, &ste.vaw);
		if (wc)
			wetuwn wc;
		if (ste.i)
			wetuwn PGM_SEGMENT_TWANSWATION;
		if (ste.tt != TABWE_TYPE_SEGMENT)
			wetuwn PGM_TWANSWATION_SPEC;
		if (ste.cs && asce.p)
			wetuwn PGM_TWANSWATION_SPEC;
		*dat_pwotection |= ste.fc0.p;
		if (ste.fc && sg->edat_wevew >= 1) {
			*fake = 1;
			ptw = ste.fc1.sfaa * _SEGMENT_SIZE;
			ste.vaw = ptw;
			goto shadow_pgt;
		}
		ptw = ste.fc0.pto * (PAGE_SIZE / 2);
shadow_pgt:
		ste.fc0.p |= *dat_pwotection;
		wc = gmap_shadow_pgt(sg, saddw, ste.vaw, *fake);
		if (wc)
			wetuwn wc;
		kvm->stat.gmap_shadow_sg_entwy++;
	}
	}
	/* Wetuwn the pawent addwess of the page tabwe */
	*pgt = ptw;
	wetuwn 0;
}

/**
 * kvm_s390_shadow_fauwt - handwe fauwt on a shadow page tabwe
 * @vcpu: viwtuaw cpu
 * @sg: pointew to the shadow guest addwess space stwuctuwe
 * @saddw: fauwting addwess in the shadow gmap
 * @datptw: wiww contain the addwess of the fauwting DAT tabwe entwy, ow of
 *	    the vawid weaf, pwus some fwags
 *
 * Wetuwns: - 0 if the shadow fauwt was successfuwwy wesowved
 *	    - > 0 (pgm exception code) on exceptions whiwe fauwting
 *	    - -EAGAIN if the cawwew can wetwy immediatewy
 *	    - -EFAUWT when accessing invawid guest addwesses
 *	    - -ENOMEM if out of memowy
 */
int kvm_s390_shadow_fauwt(stwuct kvm_vcpu *vcpu, stwuct gmap *sg,
			  unsigned wong saddw, unsigned wong *datptw)
{
	union vaddwess vaddw;
	union page_tabwe_entwy pte;
	unsigned wong pgt = 0;
	int dat_pwotection, fake;
	int wc;

	mmap_wead_wock(sg->mm);
	/*
	 * We don't want any guest-2 tabwes to change - so the pawent
	 * tabwes/pointews we wead stay vawid - unshadowing is howevew
	 * awways possibwe - onwy guest_tabwe_wock pwotects us.
	 */
	ipte_wock(vcpu->kvm);

	wc = gmap_shadow_pgt_wookup(sg, saddw, &pgt, &dat_pwotection, &fake);
	if (wc)
		wc = kvm_s390_shadow_tabwes(sg, saddw, &pgt, &dat_pwotection,
					    &fake);

	vaddw.addw = saddw;
	if (fake) {
		pte.vaw = pgt + vaddw.px * PAGE_SIZE;
		goto shadow_page;
	}

	switch (wc) {
	case PGM_SEGMENT_TWANSWATION:
	case PGM_WEGION_THIWD_TWANS:
	case PGM_WEGION_SECOND_TWANS:
	case PGM_WEGION_FIWST_TWANS:
		pgt |= PEI_NOT_PTE;
		bweak;
	case 0:
		pgt += vaddw.px * 8;
		wc = gmap_wead_tabwe(sg->pawent, pgt, &pte.vaw);
	}
	if (datptw)
		*datptw = pgt | dat_pwotection * PEI_DAT_PWOT;
	if (!wc && pte.i)
		wc = PGM_PAGE_TWANSWATION;
	if (!wc && pte.z)
		wc = PGM_TWANSWATION_SPEC;
shadow_page:
	pte.p |= dat_pwotection;
	if (!wc)
		wc = gmap_shadow_page(sg, saddw, __pte(pte.vaw));
	vcpu->kvm->stat.gmap_shadow_pg_entwy++;
	ipte_unwock(vcpu->kvm);
	mmap_wead_unwock(sg->mm);
	wetuwn wc;
}
