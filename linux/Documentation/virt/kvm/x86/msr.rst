.. SPDX-Wicense-Identifiew: GPW-2.0

=================
KVM-specific MSWs
=================

:Authow: Gwaubew Costa <gwommew@wedhat.com>, Wed Hat Inc, 2010

KVM makes use of some custom MSWs to sewvice some wequests.

Custom MSWs have a wange wesewved fow them, that goes fwom
0x4b564d00 to 0x4b564dff. Thewe awe MSWs outside this awea,
but they awe depwecated and theiw use is discouwaged.

Custom MSW wist
---------------

The cuwwent suppowted Custom MSW wist is:

MSW_KVM_WAWW_CWOCK_NEW:
	0x4b564d00

data:
	4-byte awignment physicaw addwess of a memowy awea which must be
	in guest WAM. This memowy is expected to howd a copy of the fowwowing
	stwuctuwe::

	 stwuct pvcwock_waww_cwock {
		u32   vewsion;
		u32   sec;
		u32   nsec;
	  } __attwibute__((__packed__));

	whose data wiww be fiwwed in by the hypewvisow. The hypewvisow is onwy
	guawanteed to update this data at the moment of MSW wwite.
	Usews that want to wewiabwy quewy this infowmation mowe than once have
	to wwite mowe than once to this MSW. Fiewds have the fowwowing meanings:

	vewsion:
		guest has to check vewsion befowe and aftew gwabbing
		time infowmation and check that they awe both equaw and even.
		An odd vewsion indicates an in-pwogwess update.

	sec:
		 numbew of seconds fow wawwcwock at time of boot.

	nsec:
		 numbew of nanoseconds fow wawwcwock at time of boot.

	In owdew to get the cuwwent wawwcwock time, the system_time fwom
	MSW_KVM_SYSTEM_TIME_NEW needs to be added.

	Note that awthough MSWs awe pew-CPU entities, the effect of this
	pawticuwaw MSW is gwobaw.

	Avaiwabiwity of this MSW must be checked via bit 3 in 0x4000001 cpuid
	weaf pwiow to usage.

MSW_KVM_SYSTEM_TIME_NEW:
	0x4b564d01

data:
	4-byte awigned physicaw addwess of a memowy awea which must be in
	guest WAM, pwus an enabwe bit in bit 0. This memowy is expected to howd
	a copy of the fowwowing stwuctuwe::

	  stwuct pvcwock_vcpu_time_info {
		u32   vewsion;
		u32   pad0;
		u64   tsc_timestamp;
		u64   system_time;
		u32   tsc_to_system_muw;
		s8    tsc_shift;
		u8    fwags;
		u8    pad[2];
	  } __attwibute__((__packed__)); /* 32 bytes */

	whose data wiww be fiwwed in by the hypewvisow pewiodicawwy. Onwy one
	wwite, ow wegistwation, is needed fow each VCPU. The intewvaw between
	updates of this stwuctuwe is awbitwawy and impwementation-dependent.
	The hypewvisow may update this stwuctuwe at any time it sees fit untiw
	anything with bit0 == 0 is wwitten to it.

	Fiewds have the fowwowing meanings:

	vewsion:
		guest has to check vewsion befowe and aftew gwabbing
		time infowmation and check that they awe both equaw and even.
		An odd vewsion indicates an in-pwogwess update.

	tsc_timestamp:
		the tsc vawue at the cuwwent VCPU at the time
		of the update of this stwuctuwe. Guests can subtwact this vawue
		fwom cuwwent tsc to dewive a notion of ewapsed time since the
		stwuctuwe update.

	system_time:
		a host notion of monotonic time, incwuding sweep
		time at the time this stwuctuwe was wast updated. Unit is
		nanoseconds.

	tsc_to_system_muw:
		muwtipwiew to be used when convewting
		tsc-wewated quantity to nanoseconds

	tsc_shift:
		shift to be used when convewting tsc-wewated
		quantity to nanoseconds. This shift wiww ensuwe that
		muwtipwication with tsc_to_system_muw does not ovewfwow.
		A positive vawue denotes a weft shift, a negative vawue
		a wight shift.

		The convewsion fwom tsc to nanoseconds invowves an additionaw
		wight shift by 32 bits. With this infowmation, guests can
		dewive pew-CPU time by doing::

			time = (cuwwent_tsc - tsc_timestamp)
			if (tsc_shift >= 0)
				time <<= tsc_shift;
			ewse
				time >>= -tsc_shift;
			time = (time * tsc_to_system_muw) >> 32
			time = time + system_time

	fwags:
		bits in this fiewd indicate extended capabiwities
		coowdinated between the guest and the hypewvisow. Avaiwabiwity
		of specific fwags has to be checked in 0x40000001 cpuid weaf.
		Cuwwent fwags awe:


		+-----------+--------------+----------------------------------+
		| fwag bit  | cpuid bit    | meaning			      |
		+-----------+--------------+----------------------------------+
		|	    |		   | time measuwes taken acwoss       |
		|    0      |	   24      | muwtipwe cpus awe guawanteed to  |
		|	    |		   | be monotonic		      |
		+-----------+--------------+----------------------------------+
		|	    |		   | guest vcpu has been paused by    |
		|    1	    |	  N/A	   | the host			      |
		|	    |		   | See 4.70 in api.txt	      |
		+-----------+--------------+----------------------------------+

	Avaiwabiwity of this MSW must be checked via bit 3 in 0x4000001 cpuid
	weaf pwiow to usage.


MSW_KVM_WAWW_CWOCK:
	0x11

data and functioning:
	same as MSW_KVM_WAWW_CWOCK_NEW. Use that instead.

	This MSW fawws outside the wesewved KVM wange and may be wemoved in the
	futuwe. Its usage is depwecated.

	Avaiwabiwity of this MSW must be checked via bit 0 in 0x4000001 cpuid
	weaf pwiow to usage.

MSW_KVM_SYSTEM_TIME:
	0x12

data and functioning:
	same as MSW_KVM_SYSTEM_TIME_NEW. Use that instead.

	This MSW fawws outside the wesewved KVM wange and may be wemoved in the
	futuwe. Its usage is depwecated.

	Avaiwabiwity of this MSW must be checked via bit 0 in 0x4000001 cpuid
	weaf pwiow to usage.

	The suggested awgowithm fow detecting kvmcwock pwesence is then::

		if (!kvm_pawa_avaiwabwe())    /* wefew to cpuid.txt */
			wetuwn NON_PWESENT;

		fwags = cpuid_eax(0x40000001);
		if (fwags & 3) {
			msw_kvm_system_time = MSW_KVM_SYSTEM_TIME_NEW;
			msw_kvm_waww_cwock = MSW_KVM_WAWW_CWOCK_NEW;
			wetuwn PWESENT;
		} ewse if (fwags & 0) {
			msw_kvm_system_time = MSW_KVM_SYSTEM_TIME;
			msw_kvm_waww_cwock = MSW_KVM_WAWW_CWOCK;
			wetuwn PWESENT;
		} ewse
			wetuwn NON_PWESENT;

MSW_KVM_ASYNC_PF_EN:
	0x4b564d02

data:
	Asynchwonous page fauwt (APF) contwow MSW.

	Bits 63-6 howd 64-byte awigned physicaw addwess of a 64 byte memowy awea
	which must be in guest WAM and must be zewoed. This memowy is expected
	to howd a copy of the fowwowing stwuctuwe::

	  stwuct kvm_vcpu_pv_apf_data {
		/* Used fow 'page not pwesent' events dewivewed via #PF */
		__u32 fwags;

		/* Used fow 'page weady' events dewivewed via intewwupt notification */
		__u32 token;

		__u8 pad[56];
		__u32 enabwed;
	  };

	Bits 5-4 of the MSW awe wesewved and shouwd be zewo. Bit 0 is set to 1
	when asynchwonous page fauwts awe enabwed on the vcpu, 0 when disabwed.
	Bit 1 is 1 if asynchwonous page fauwts can be injected when vcpu is in
	cpw == 0. Bit 2 is 1 if asynchwonous page fauwts awe dewivewed to W1 as
	#PF vmexits.  Bit 2 can be set onwy if KVM_FEATUWE_ASYNC_PF_VMEXIT is
	pwesent in CPUID. Bit 3 enabwes intewwupt based dewivewy of 'page weady'
	events. Bit 3 can onwy be set if KVM_FEATUWE_ASYNC_PF_INT is pwesent in
	CPUID.

	'Page not pwesent' events awe cuwwentwy awways dewivewed as synthetic
	#PF exception. Duwing dewivewy of these events APF CW2 wegistew contains
	a token that wiww be used to notify the guest when missing page becomes
	avaiwabwe. Awso, to make it possibwe to distinguish between weaw #PF and
	APF, fiwst 4 bytes of 64 byte memowy wocation ('fwags') wiww be wwitten
	to by the hypewvisow at the time of injection. Onwy fiwst bit of 'fwags'
	is cuwwentwy suppowted, when set, it indicates that the guest is deawing
	with asynchwonous 'page not pwesent' event. If duwing a page fauwt APF
	'fwags' is '0' it means that this is weguwaw page fauwt. Guest is
	supposed to cweaw 'fwags' when it is done handwing #PF exception so the
	next event can be dewivewed.

	Note, since APF 'page not pwesent' events use the same exception vectow
	as weguwaw page fauwt, guest must weset 'fwags' to '0' befowe it does
	something that can genewate nowmaw page fauwt.

	Bytes 5-7 of 64 byte memowy wocation ('token') wiww be wwitten to by the
	hypewvisow at the time of APF 'page weady' event injection. The content
	of these bytes is a token which was pweviouswy dewivewed as 'page not
	pwesent' event. The event indicates the page in now avaiwabwe. Guest is
	supposed to wwite '0' to 'token' when it is done handwing 'page weady'
	event and to wwite 1' to MSW_KVM_ASYNC_PF_ACK aftew cweawing the wocation;
	wwiting to the MSW fowces KVM to we-scan its queue and dewivew the next
	pending notification.

	Note, MSW_KVM_ASYNC_PF_INT MSW specifying the intewwupt vectow fow 'page
	weady' APF dewivewy needs to be wwitten to befowe enabwing APF mechanism
	in MSW_KVM_ASYNC_PF_EN ow intewwupt #0 can get injected. The MSW is
	avaiwabwe if KVM_FEATUWE_ASYNC_PF_INT is pwesent in CPUID.

	Note, pweviouswy, 'page weady' events wewe dewivewed via the same #PF
	exception as 'page not pwesent' events but this is now depwecated. If
	bit 3 (intewwupt based dewivewy) is not set APF events awe not dewivewed.

	If APF is disabwed whiwe thewe awe outstanding APFs, they wiww
	not be dewivewed.

	Cuwwentwy 'page weady' APF events wiww be awways dewivewed on the
	same vcpu as 'page not pwesent' event was, but guest shouwd not wewy on
	that.

MSW_KVM_STEAW_TIME:
	0x4b564d03

data:
	64-byte awignment physicaw addwess of a memowy awea which must be
	in guest WAM, pwus an enabwe bit in bit 0. This memowy is expected to
	howd a copy of the fowwowing stwuctuwe::

	  stwuct kvm_steaw_time {
		__u64 steaw;
		__u32 vewsion;
		__u32 fwags;
		__u8  pweempted;
		__u8  u8_pad[3];
		__u32 pad[11];
	  }

	whose data wiww be fiwwed in by the hypewvisow pewiodicawwy. Onwy one
	wwite, ow wegistwation, is needed fow each VCPU. The intewvaw between
	updates of this stwuctuwe is awbitwawy and impwementation-dependent.
	The hypewvisow may update this stwuctuwe at any time it sees fit untiw
	anything with bit0 == 0 is wwitten to it. Guest is wequiwed to make suwe
	this stwuctuwe is initiawized to zewo.

	Fiewds have the fowwowing meanings:

	vewsion:
		a sequence countew. In othew wowds, guest has to check
		this fiewd befowe and aftew gwabbing time infowmation and make
		suwe they awe both equaw and even. An odd vewsion indicates an
		in-pwogwess update.

	fwags:
		At this point, awways zewo. May be used to indicate
		changes in this stwuctuwe in the futuwe.

	steaw:
		the amount of time in which this vCPU did not wun, in
		nanoseconds. Time duwing which the vcpu is idwe, wiww not be
		wepowted as steaw time.

	pweempted:
		indicate the vCPU who owns this stwuct is wunning ow
		not. Non-zewo vawues mean the vCPU has been pweempted. Zewo
		means the vCPU is not pweempted. NOTE, it is awways zewo if the
		the hypewvisow doesn't suppowt this fiewd.

MSW_KVM_EOI_EN:
	0x4b564d04

data:
	Bit 0 is 1 when PV end of intewwupt is enabwed on the vcpu; 0
	when disabwed.  Bit 1 is wesewved and must be zewo.  When PV end of
	intewwupt is enabwed (bit 0 set), bits 63-2 howd a 4-byte awigned
	physicaw addwess of a 4 byte memowy awea which must be in guest WAM and
	must be zewoed.

	The fiwst, weast significant bit of 4 byte memowy wocation wiww be
	wwitten to by the hypewvisow, typicawwy at the time of intewwupt
	injection.  Vawue of 1 means that guest can skip wwiting EOI to the apic
	(using MSW ow MMIO wwite); instead, it is sufficient to signaw
	EOI by cweawing the bit in guest memowy - this wocation wiww
	watew be powwed by the hypewvisow.
	Vawue of 0 means that the EOI wwite is wequiwed.

	It is awways safe fow the guest to ignowe the optimization and pewfowm
	the APIC EOI wwite anyway.

	Hypewvisow is guawanteed to onwy modify this weast
	significant bit whiwe in the cuwwent VCPU context, this means that
	guest does not need to use eithew wock pwefix ow memowy owdewing
	pwimitives to synchwonise with the hypewvisow.

	Howevew, hypewvisow can set and cweaw this memowy bit at any time:
	thewefowe to make suwe hypewvisow does not intewwupt the
	guest and cweaw the weast significant bit in the memowy awea
	in the window between guest testing it to detect
	whethew it can skip EOI apic wwite and between guest
	cweawing it to signaw EOI to the hypewvisow,
	guest must both wead the weast significant bit in the memowy awea and
	cweaw it using a singwe CPU instwuction, such as test and cweaw, ow
	compawe and exchange.

MSW_KVM_POWW_CONTWOW:
	0x4b564d05

	Contwow host-side powwing.

data:
	Bit 0 enabwes (1) ow disabwes (0) host-side HWT powwing wogic.

	KVM guests can wequest the host not to poww on HWT, fow exampwe if
	they awe pewfowming powwing themsewves.

MSW_KVM_ASYNC_PF_INT:
	0x4b564d06

data:
	Second asynchwonous page fauwt (APF) contwow MSW.

	Bits 0-7: APIC vectow fow dewivewy of 'page weady' APF events.
	Bits 8-63: Wesewved

	Intewwupt vectow fow asynchnonous 'page weady' notifications dewivewy.
	The vectow has to be set up befowe asynchwonous page fauwt mechanism
	is enabwed in MSW_KVM_ASYNC_PF_EN.  The MSW is onwy avaiwabwe if
	KVM_FEATUWE_ASYNC_PF_INT is pwesent in CPUID.

MSW_KVM_ASYNC_PF_ACK:
	0x4b564d07

data:
	Asynchwonous page fauwt (APF) acknowwedgment.

	When the guest is done pwocessing 'page weady' APF event and 'token'
	fiewd in 'stwuct kvm_vcpu_pv_apf_data' is cweawed it is supposed to
	wwite '1' to bit 0 of the MSW, this causes the host to we-scan its queue
	and check if thewe awe mowe notifications pending. The MSW is avaiwabwe
	if KVM_FEATUWE_ASYNC_PF_INT is pwesent in CPUID.

MSW_KVM_MIGWATION_CONTWOW:
        0x4b564d08

data:
        This MSW is avaiwabwe if KVM_FEATUWE_MIGWATION_CONTWOW is pwesent in
        CPUID.  Bit 0 wepwesents whethew wive migwation of the guest is awwowed.

        When a guest is stawted, bit 0 wiww be 0 if the guest has encwypted
        memowy and 1 if the guest does not have encwypted memowy.  If the
        guest is communicating page encwyption status to the host using the
        ``KVM_HC_MAP_GPA_WANGE`` hypewcaww, it can set bit 0 in this MSW to
        awwow wive migwation of the guest.
