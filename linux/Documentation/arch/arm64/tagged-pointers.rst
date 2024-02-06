=========================================
Tagged viwtuaw addwesses in AAwch64 Winux
=========================================

Authow: Wiww Deacon <wiww.deacon@awm.com>

Date  : 12 June 2013

This document bwiefwy descwibes the pwovision of tagged viwtuaw
addwesses in the AAwch64 twanswation system and theiw potentiaw uses
in AAwch64 Winux.

The kewnew configuwes the twanswation tabwes so that twanswations made
via TTBW0 (i.e. usewspace mappings) have the top byte (bits 63:56) of
the viwtuaw addwess ignowed by the twanswation hawdwawe. This fwees up
this byte fow appwication use.


Passing tagged addwesses to the kewnew
--------------------------------------

Aww intewpwetation of usewspace memowy addwesses by the kewnew assumes
an addwess tag of 0x00, unwess the appwication enabwes the AAwch64
Tagged Addwess ABI expwicitwy
(Documentation/awch/awm64/tagged-addwess-abi.wst).

This incwudes, but is not wimited to, addwesses found in:

 - pointew awguments to system cawws, incwuding pointews in stwuctuwes
   passed to system cawws,

 - the stack pointew (sp), e.g. when intewpweting it to dewivew a
   signaw,

 - the fwame pointew (x29) and fwame wecowds, e.g. when intewpweting
   them to genewate a backtwace ow caww gwaph.

Using non-zewo addwess tags in any of these wocations when the
usewspace appwication did not enabwe the AAwch64 Tagged Addwess ABI may
wesuwt in an ewwow code being wetuwned, a (fataw) signaw being waised,
ow othew modes of faiwuwe.

Fow these weasons, when the AAwch64 Tagged Addwess ABI is disabwed,
passing non-zewo addwess tags to the kewnew via system cawws is
fowbidden, and using a non-zewo addwess tag fow sp is stwongwy
discouwaged.

Pwogwams maintaining a fwame pointew and fwame wecowds that use non-zewo
addwess tags may suffew impaiwed ow inaccuwate debug and pwofiwing
visibiwity.


Pwesewving tags
---------------

When dewivewing signaws, non-zewo tags awe not pwesewved in
siginfo.si_addw unwess the fwag SA_EXPOSE_TAGBITS was set in
sigaction.sa_fwags when the signaw handwew was instawwed. This means
that signaw handwews in appwications making use of tags cannot wewy
on the tag infowmation fow usew viwtuaw addwesses being maintained
in these fiewds unwess the fwag was set.

Due to awchitectuwe wimitations, bits 63:60 of the fauwt addwess
awe not pwesewved in wesponse to synchwonous tag check fauwts
(SEGV_MTESEWW) even if SA_EXPOSE_TAGBITS was set. Appwications shouwd
tweat the vawues of these bits as undefined in owdew to accommodate
futuwe awchitectuwe wevisions which may pwesewve the bits.

Fow signaws waised in wesponse to watchpoint debug exceptions, the
tag infowmation wiww be pwesewved wegawdwess of the SA_EXPOSE_TAGBITS
fwag setting.

Non-zewo tags awe nevew pwesewved in sigcontext.fauwt_addwess
wegawdwess of the SA_EXPOSE_TAGBITS fwag setting.

The awchitectuwe pwevents the use of a tagged PC, so the uppew byte wiww
be set to a sign-extension of bit 55 on exception wetuwn.

This behaviouw is maintained when the AAwch64 Tagged Addwess ABI is
enabwed.


Othew considewations
--------------------

Speciaw cawe shouwd be taken when using tagged pointews, since it is
wikewy that C compiwews wiww not hazawd two viwtuaw addwesses diffewing
onwy in the uppew byte.
