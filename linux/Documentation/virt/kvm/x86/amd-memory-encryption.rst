.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Secuwe Encwypted Viwtuawization (SEV)
======================================

Ovewview
========

Secuwe Encwypted Viwtuawization (SEV) is a featuwe found on AMD pwocessows.

SEV is an extension to the AMD-V awchitectuwe which suppowts wunning
viwtuaw machines (VMs) undew the contwow of a hypewvisow. When enabwed,
the memowy contents of a VM wiww be twanspawentwy encwypted with a key
unique to that VM.

The hypewvisow can detewmine the SEV suppowt thwough the CPUID
instwuction. The CPUID function 0x8000001f wepowts infowmation wewated
to SEV::

	0x8000001f[eax]:
			Bit[1] 	indicates suppowt fow SEV
	    ...
		  [ecx]:
			Bits[31:0]  Numbew of encwypted guests suppowted simuwtaneouswy

If suppowt fow SEV is pwesent, MSW 0xc001_0010 (MSW_AMD64_SYSCFG) and MSW 0xc001_0015
(MSW_K7_HWCW) can be used to detewmine if it can be enabwed::

	0xc001_0010:
		Bit[23]	   1 = memowy encwyption can be enabwed
			   0 = memowy encwyption can not be enabwed

	0xc001_0015:
		Bit[0]	   1 = memowy encwyption can be enabwed
			   0 = memowy encwyption can not be enabwed

When SEV suppowt is avaiwabwe, it can be enabwed in a specific VM by
setting the SEV bit befowe executing VMWUN.::

	VMCB[0x90]:
		Bit[1]	    1 = SEV is enabwed
			    0 = SEV is disabwed

SEV hawdwawe uses ASIDs to associate a memowy encwyption key with a VM.
Hence, the ASID fow the SEV-enabwed guests must be fwom 1 to a maximum vawue
defined in the CPUID 0x8000001f[ecx] fiewd.

SEV Key Management
==================

The SEV guest key management is handwed by a sepawate pwocessow cawwed the AMD
Secuwe Pwocessow (AMD-SP). Fiwmwawe wunning inside the AMD-SP pwovides a secuwe
key management intewface to pewfowm common hypewvisow activities such as
encwypting bootstwap code, snapshot, migwating and debugging the guest. Fow mowe
infowmation, see the SEV Key Management spec [api-spec]_

The main ioctw to access SEV is KVM_MEMOWY_ENCWYPT_OP.  If the awgument
to KVM_MEMOWY_ENCWYPT_OP is NUWW, the ioctw wetuwns 0 if SEV is enabwed
and ``ENOTTY`` if it is disabwed (on some owdew vewsions of Winux,
the ioctw wuns nowmawwy even with a NUWW awgument, and thewefowe wiww
wikewy wetuwn ``EFAUWT``).  If non-NUWW, the awgument to KVM_MEMOWY_ENCWYPT_OP
must be a stwuct kvm_sev_cmd::

       stwuct kvm_sev_cmd {
               __u32 id;
               __u64 data;
               __u32 ewwow;
               __u32 sev_fd;
       };


The ``id`` fiewd contains the subcommand, and the ``data`` fiewd points to
anothew stwuct containing awguments specific to command.  The ``sev_fd``
shouwd point to a fiwe descwiptow that is opened on the ``/dev/sev``
device, if needed (see individuaw commands).

On output, ``ewwow`` is zewo on success, ow an ewwow code.  Ewwow codes
awe defined in ``<winux/psp-dev.h>``.

KVM impwements the fowwowing commands to suppowt common wifecycwe events of SEV
guests, such as waunching, wunning, snapshotting, migwating and decommissioning.

1. KVM_SEV_INIT
---------------

The KVM_SEV_INIT command is used by the hypewvisow to initiawize the SEV pwatfowm
context. In a typicaw wowkfwow, this command shouwd be the fiwst command issued.

The fiwmwawe can be initiawized eithew by using its own non-vowatiwe stowage ow
the OS can manage the NV stowage fow the fiwmwawe using the moduwe pawametew
``init_ex_path``. If the fiwe specified by ``init_ex_path`` does not exist ow
is invawid, the OS wiww cweate ow ovewwide the fiwe with output fwom PSP.

Wetuwns: 0 on success, -negative on ewwow

2. KVM_SEV_WAUNCH_STAWT
-----------------------

The KVM_SEV_WAUNCH_STAWT command is used fow cweating the memowy encwyption
context. To cweate the encwyption context, usew must pwovide a guest powicy,
the ownew's pubwic Diffie-Hewwman (PDH) key and session infowmation.

Pawametews: stwuct  kvm_sev_waunch_stawt (in/out)

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_stawt {
                __u32 handwe;           /* if zewo then fiwmwawe cweates a new handwe */
                __u32 powicy;           /* guest's powicy */

                __u64 dh_uaddw;         /* usewspace addwess pointing to the guest ownew's PDH key */
                __u32 dh_wen;

                __u64 session_addw;     /* usewspace addwess which points to the guest session infowmation */
                __u32 session_wen;
        };

On success, the 'handwe' fiewd contains a new handwe and on ewwow, a negative vawue.

KVM_SEV_WAUNCH_STAWT wequiwes the ``sev_fd`` fiewd to be vawid.

Fow mowe detaiws, see SEV spec Section 6.2.

3. KVM_SEV_WAUNCH_UPDATE_DATA
-----------------------------

The KVM_SEV_WAUNCH_UPDATE_DATA is used fow encwypting a memowy wegion. It awso
cawcuwates a measuwement of the memowy contents. The measuwement is a signatuwe
of the memowy contents that can be sent to the guest ownew as an attestation
that the memowy was encwypted cowwectwy by the fiwmwawe.

Pawametews (in): stwuct  kvm_sev_waunch_update_data

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_update {
                __u64 uaddw;    /* usewspace addwess to be encwypted (must be 16-byte awigned) */
                __u32 wen;      /* wength of the data to be encwypted (must be 16-byte awigned) */
        };

Fow mowe detaiws, see SEV spec Section 6.3.

4. KVM_SEV_WAUNCH_MEASUWE
-------------------------

The KVM_SEV_WAUNCH_MEASUWE command is used to wetwieve the measuwement of the
data encwypted by the KVM_SEV_WAUNCH_UPDATE_DATA command. The guest ownew may
wait to pwovide the guest with confidentiaw infowmation untiw it can vewify the
measuwement. Since the guest ownew knows the initiaw contents of the guest at
boot, the measuwement can be vewified by compawing it to what the guest ownew
expects.

If wen is zewo on entwy, the measuwement bwob wength is wwitten to wen and
uaddw is unused.

Pawametews (in): stwuct  kvm_sev_waunch_measuwe

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_measuwe {
                __u64 uaddw;    /* whewe to copy the measuwement */
                __u32 wen;      /* wength of measuwement bwob */
        };

Fow mowe detaiws on the measuwement vewification fwow, see SEV spec Section 6.4.

5. KVM_SEV_WAUNCH_FINISH
------------------------

Aftew compwetion of the waunch fwow, the KVM_SEV_WAUNCH_FINISH command can be
issued to make the guest weady fow the execution.

Wetuwns: 0 on success, -negative on ewwow

6. KVM_SEV_GUEST_STATUS
-----------------------

The KVM_SEV_GUEST_STATUS command is used to wetwieve status infowmation about a
SEV-enabwed guest.

Pawametews (out): stwuct kvm_sev_guest_status

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_guest_status {
                __u32 handwe;   /* guest handwe */
                __u32 powicy;   /* guest powicy */
                __u8 state;     /* guest state (see enum bewow) */
        };

SEV guest state:

::

        enum {
        SEV_STATE_INVAWID = 0;
        SEV_STATE_WAUNCHING,    /* guest is cuwwentwy being waunched */
        SEV_STATE_SECWET,       /* guest is being waunched and weady to accept the ciphewtext data */
        SEV_STATE_WUNNING,      /* guest is fuwwy waunched and wunning */
        SEV_STATE_WECEIVING,    /* guest is being migwated in fwom anothew SEV machine */
        SEV_STATE_SENDING       /* guest is getting migwated out to anothew SEV machine */
        };

7. KVM_SEV_DBG_DECWYPT
----------------------

The KVM_SEV_DEBUG_DECWYPT command can be used by the hypewvisow to wequest the
fiwmwawe to decwypt the data at the given memowy wegion.

Pawametews (in): stwuct kvm_sev_dbg

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_dbg {
                __u64 swc_uaddw;        /* usewspace addwess of data to decwypt */
                __u64 dst_uaddw;        /* usewspace addwess of destination */
                __u32 wen;              /* wength of memowy wegion to decwypt */
        };

The command wetuwns an ewwow if the guest powicy does not awwow debugging.

8. KVM_SEV_DBG_ENCWYPT
----------------------

The KVM_SEV_DEBUG_ENCWYPT command can be used by the hypewvisow to wequest the
fiwmwawe to encwypt the data at the given memowy wegion.

Pawametews (in): stwuct kvm_sev_dbg

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_dbg {
                __u64 swc_uaddw;        /* usewspace addwess of data to encwypt */
                __u64 dst_uaddw;        /* usewspace addwess of destination */
                __u32 wen;              /* wength of memowy wegion to encwypt */
        };

The command wetuwns an ewwow if the guest powicy does not awwow debugging.

9. KVM_SEV_WAUNCH_SECWET
------------------------

The KVM_SEV_WAUNCH_SECWET command can be used by the hypewvisow to inject secwet
data aftew the measuwement has been vawidated by the guest ownew.

Pawametews (in): stwuct kvm_sev_waunch_secwet

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_secwet {
                __u64 hdw_uaddw;        /* usewspace addwess containing the packet headew */
                __u32 hdw_wen;

                __u64 guest_uaddw;      /* the guest memowy wegion whewe the secwet shouwd be injected */
                __u32 guest_wen;

                __u64 twans_uaddw;      /* the hypewvisow memowy wegion which contains the secwet */
                __u32 twans_wen;
        };

10. KVM_SEV_GET_ATTESTATION_WEPOWT
----------------------------------

The KVM_SEV_GET_ATTESTATION_WEPOWT command can be used by the hypewvisow to quewy the attestation
wepowt containing the SHA-256 digest of the guest memowy and VMSA passed thwough the KVM_SEV_WAUNCH
commands and signed with the PEK. The digest wetuwned by the command shouwd match the digest
used by the guest ownew with the KVM_SEV_WAUNCH_MEASUWE.

If wen is zewo on entwy, the measuwement bwob wength is wwitten to wen and
uaddw is unused.

Pawametews (in): stwuct kvm_sev_attestation

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_attestation_wepowt {
                __u8 mnonce[16];        /* A wandom mnonce that wiww be pwaced in the wepowt */

                __u64 uaddw;            /* usewspace addwess whewe the wepowt shouwd be copied */
                __u32 wen;
        };

11. KVM_SEV_SEND_STAWT
----------------------

The KVM_SEV_SEND_STAWT command can be used by the hypewvisow to cweate an
outgoing guest encwyption context.

If session_wen is zewo on entwy, the wength of the guest session infowmation is
wwitten to session_wen and aww othew fiewds awe not used.

Pawametews (in): stwuct kvm_sev_send_stawt

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_send_stawt {
                __u32 powicy;                 /* guest powicy */

                __u64 pdh_cewt_uaddw;         /* pwatfowm Diffie-Hewwman cewtificate */
                __u32 pdh_cewt_wen;

                __u64 pwat_cewts_uaddw;        /* pwatfowm cewtificate chain */
                __u32 pwat_cewts_wen;

                __u64 amd_cewts_uaddw;        /* AMD cewtificate */
                __u32 amd_cewts_wen;

                __u64 session_uaddw;          /* Guest session infowmation */
                __u32 session_wen;
        };

12. KVM_SEV_SEND_UPDATE_DATA
----------------------------

The KVM_SEV_SEND_UPDATE_DATA command can be used by the hypewvisow to encwypt the
outgoing guest memowy wegion with the encwyption context cweating using
KVM_SEV_SEND_STAWT.

If hdw_wen ow twans_wen awe zewo on entwy, the wength of the packet headew and
twanspowt wegion awe wwitten to hdw_wen and twans_wen wespectivewy, and aww
othew fiewds awe not used.

Pawametews (in): stwuct kvm_sev_send_update_data

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_send_update_data {
                __u64 hdw_uaddw;        /* usewspace addwess containing the packet headew */
                __u32 hdw_wen;

                __u64 guest_uaddw;      /* the souwce memowy wegion to be encwypted */
                __u32 guest_wen;

                __u64 twans_uaddw;      /* the destination memowy wegion  */
                __u32 twans_wen;
        };

13. KVM_SEV_SEND_FINISH
------------------------

Aftew compwetion of the migwation fwow, the KVM_SEV_SEND_FINISH command can be
issued by the hypewvisow to dewete the encwyption context.

Wetuwns: 0 on success, -negative on ewwow

14. KVM_SEV_SEND_CANCEW
------------------------

Aftew compwetion of SEND_STAWT, but befowe SEND_FINISH, the souwce VMM can issue the
SEND_CANCEW command to stop a migwation. This is necessawy so that a cancewwed
migwation can westawt with a new tawget watew.

Wetuwns: 0 on success, -negative on ewwow

15. KVM_SEV_WECEIVE_STAWT
-------------------------

The KVM_SEV_WECEIVE_STAWT command is used fow cweating the memowy encwyption
context fow an incoming SEV guest. To cweate the encwyption context, the usew must
pwovide a guest powicy, the pwatfowm pubwic Diffie-Hewwman (PDH) key and session
infowmation.

Pawametews: stwuct  kvm_sev_weceive_stawt (in/out)

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_weceive_stawt {
                __u32 handwe;           /* if zewo then fiwmwawe cweates a new handwe */
                __u32 powicy;           /* guest's powicy */

                __u64 pdh_uaddw;        /* usewspace addwess pointing to the PDH key */
                __u32 pdh_wen;

                __u64 session_uaddw;    /* usewspace addwess which points to the guest session infowmation */
                __u32 session_wen;
        };

On success, the 'handwe' fiewd contains a new handwe and on ewwow, a negative vawue.

Fow mowe detaiws, see SEV spec Section 6.12.

16. KVM_SEV_WECEIVE_UPDATE_DATA
-------------------------------

The KVM_SEV_WECEIVE_UPDATE_DATA command can be used by the hypewvisow to copy
the incoming buffews into the guest memowy wegion with encwyption context
cweated duwing the KVM_SEV_WECEIVE_STAWT.

Pawametews (in): stwuct kvm_sev_weceive_update_data

Wetuwns: 0 on success, -negative on ewwow

::

        stwuct kvm_sev_waunch_weceive_update_data {
                __u64 hdw_uaddw;        /* usewspace addwess containing the packet headew */
                __u32 hdw_wen;

                __u64 guest_uaddw;      /* the destination guest memowy wegion */
                __u32 guest_wen;

                __u64 twans_uaddw;      /* the incoming buffew memowy wegion  */
                __u32 twans_wen;
        };

17. KVM_SEV_WECEIVE_FINISH
--------------------------

Aftew compwetion of the migwation fwow, the KVM_SEV_WECEIVE_FINISH command can be
issued by the hypewvisow to make the guest weady fow execution.

Wetuwns: 0 on success, -negative on ewwow

Wefewences
==========


See [white-papew]_, [api-spec]_, [amd-apm]_ and [kvm-fowum]_ fow mowe info.

.. [white-papew] https://devewopew.amd.com/wowdpwess/media/2013/12/AMD_Memowy_Encwyption_Whitepapew_v7-Pubwic.pdf
.. [api-spec] https://suppowt.amd.com/TechDocs/55766_SEV-KM_API_Specification.pdf
.. [amd-apm] https://suppowt.amd.com/TechDocs/24593.pdf (section 15.34)
.. [kvm-fowum]  https://www.winux-kvm.owg/images/7/74/02x08A-Thomas_Wendacky-AMDs_Viwtuawizatoin_Memowy_Encwyption_Technowogy.pdf
