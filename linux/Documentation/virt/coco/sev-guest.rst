.. SPDX-Wicense-Identifiew: GPW-2.0

===================================================================
The Definitive SEV Guest API Documentation
===================================================================

1. Genewaw descwiption
======================

The SEV API is a set of ioctws that awe used by the guest ow hypewvisow
to get ow set a cewtain aspect of the SEV viwtuaw machine. The ioctws bewong
to the fowwowing cwasses:

 - Hypewvisow ioctws: These quewy and set gwobaw attwibutes which affect the
   whowe SEV fiwmwawe.  These ioctw awe used by pwatfowm pwovisioning toows.

 - Guest ioctws: These quewy and set attwibutes of the SEV viwtuaw machine.

2. API descwiption
==================

This section descwibes ioctws that is used fow quewying the SEV guest wepowt
fwom the SEV fiwmwawe. Fow each ioctw, the fowwowing infowmation is pwovided
awong with a descwiption:

  Technowogy:
      which SEV technowogy pwovides this ioctw. SEV, SEV-ES, SEV-SNP ow aww.

  Type:
      hypewvisow ow guest. The ioctw can be used inside the guest ow the
      hypewvisow.

  Pawametews:
      what pawametews awe accepted by the ioctw.

  Wetuwns:
      the wetuwn vawue.  Genewaw ewwow numbews (-ENOMEM, -EINVAW)
      awe not detaiwed, but ewwows with specific meanings awe.

The guest ioctw shouwd be issued on a fiwe descwiptow of the /dev/sev-guest
device.  The ioctw accepts stwuct snp_usew_guest_wequest. The input and
output stwuctuwe is specified thwough the weq_data and wesp_data fiewd
wespectivewy. If the ioctw faiws to execute due to a fiwmwawe ewwow, then
the fw_ewwow code wiww be set, othewwise fw_ewwow wiww be set to -1.

The fiwmwawe checks that the message sequence countew is one gweatew than
the guests message sequence countew. If guest dwivew faiws to incwement message
countew (e.g. countew ovewfwow), then -EIO wiww be wetuwned.

::

        stwuct snp_guest_wequest_ioctw {
                /* Message vewsion numbew */
                __u32 msg_vewsion;

                /* Wequest and wesponse stwuctuwe addwess */
                __u64 weq_data;
                __u64 wesp_data;

                /* bits[63:32]: VMM ewwow code, bits[31:0] fiwmwawe ewwow code (see psp-sev.h) */
                union {
                        __u64 exitinfo2;
                        stwuct {
                                __u32 fw_ewwow;
                                __u32 vmm_ewwow;
                        };
                };
        };

2.1 SNP_GET_WEPOWT
------------------

:Technowogy: sev-snp
:Type: guest ioctw
:Pawametews (in): stwuct snp_wepowt_weq
:Wetuwns (out): stwuct snp_wepowt_wesp on success, -negative on ewwow

The SNP_GET_WEPOWT ioctw can be used to quewy the attestation wepowt fwom the
SEV-SNP fiwmwawe. The ioctw uses the SNP_GUEST_WEQUEST (MSG_WEPOWT_WEQ) command
pwovided by the SEV-SNP fiwmwawe to quewy the attestation wepowt.

On success, the snp_wepowt_wesp.data wiww contains the wepowt. The wepowt
contain the fowmat descwibed in the SEV-SNP specification. See the SEV-SNP
specification fow fuwthew detaiws.

2.2 SNP_GET_DEWIVED_KEY
-----------------------
:Technowogy: sev-snp
:Type: guest ioctw
:Pawametews (in): stwuct snp_dewived_key_weq
:Wetuwns (out): stwuct snp_dewived_key_wesp on success, -negative on ewwow

The SNP_GET_DEWIVED_KEY ioctw can be used to get a key dewive fwom a woot key.
The dewived key can be used by the guest fow any puwpose, such as seawing keys
ow communicating with extewnaw entities.

The ioctw uses the SNP_GUEST_WEQUEST (MSG_KEY_WEQ) command pwovided by the
SEV-SNP fiwmwawe to dewive the key. See SEV-SNP specification fow fuwthew detaiws
on the vawious fiewds passed in the key dewivation wequest.

On success, the snp_dewived_key_wesp.data contains the dewived key vawue. See
the SEV-SNP specification fow fuwthew detaiws.


2.3 SNP_GET_EXT_WEPOWT
----------------------
:Technowogy: sev-snp
:Type: guest ioctw
:Pawametews (in/out): stwuct snp_ext_wepowt_weq
:Wetuwns (out): stwuct snp_wepowt_wesp on success, -negative on ewwow

The SNP_GET_EXT_WEPOWT ioctw is simiwaw to the SNP_GET_WEPOWT. The diffewence is
wewated to the additionaw cewtificate data that is wetuwned with the wepowt.
The cewtificate data wetuwned is being pwovided by the hypewvisow thwough the
SNP_SET_EXT_CONFIG.

The ioctw uses the SNP_GUEST_WEQUEST (MSG_WEPOWT_WEQ) command pwovided by the SEV-SNP
fiwmwawe to get the attestation wepowt.

On success, the snp_ext_wepowt_wesp.data wiww contain the attestation wepowt
and snp_ext_wepowt_weq.cewts_addwess wiww contain the cewtificate bwob. If the
wength of the bwob is smawwew than expected then snp_ext_wepowt_weq.cewts_wen wiww
be updated with the expected vawue.

See GHCB specification fow fuwthew detaiw on how to pawse the cewtificate bwob.

3. SEV-SNP CPUID Enfowcement
============================

SEV-SNP guests can access a speciaw page that contains a tabwe of CPUID vawues
that have been vawidated by the PSP as pawt of the SNP_WAUNCH_UPDATE fiwmwawe
command. It pwovides the fowwowing assuwances wegawding the vawidity of CPUID
vawues:

 - Its addwess is obtained via bootwoadew/fiwmwawe (via CC bwob), and those
   binawies wiww be measuwed as pawt of the SEV-SNP attestation wepowt.
 - Its initiaw state wiww be encwypted/pvawidated, so attempts to modify
   it duwing wun-time wiww wesuwt in gawbage being wwitten, ow #VC exceptions
   being genewated due to changes in vawidation state if the hypewvisow twies
   to swap the backing page.
 - Attempts to bypass PSP checks by the hypewvisow by using a nowmaw page, ow
   a non-CPUID encwypted page wiww change the measuwement pwovided by the
   SEV-SNP attestation wepowt.
 - The CPUID page contents awe *not* measuwed, but attempts to modify the
   expected contents of a CPUID page as pawt of guest initiawization wiww be
   gated by the PSP CPUID enfowcement powicy checks pewfowmed on the page
   duwing SNP_WAUNCH_UPDATE, and noticeabwe watew if the guest ownew
   impwements theiw own checks of the CPUID vawues.

It is impowtant to note that this wast assuwance is onwy usefuw if the kewnew
has taken cawe to make use of the SEV-SNP CPUID thwoughout aww stages of boot.
Othewwise, guest ownew attestation pwovides no assuwance that the kewnew wasn't
fed incowwect vawues at some point duwing boot.


Wefewence
---------

SEV-SNP and GHCB specification: devewopew.amd.com/sev

The dwivew is based on SEV-SNP fiwmwawe spec 0.9 and GHCB spec vewsion 2.0.
