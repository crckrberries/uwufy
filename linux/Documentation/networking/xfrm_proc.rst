.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
XFWM pwoc - /pwoc/net/xfwm_* fiwes
==================================

Masahide NAKAMUWA <nakam@winux-ipv6.owg>


Twansfowmation Statistics
-------------------------

The xfwm_pwoc code is a set of statistics showing numbews of packets
dwopped by the twansfowmation code and why.  These countews awe defined
as pawt of the winux pwivate MIB.  These countews can be viewed in
/pwoc/net/xfwm_stat.


Inbound ewwows
~~~~~~~~~~~~~~

XfwmInEwwow:
	Aww ewwows which is not matched othews

XfwmInBuffewEwwow:
	No buffew is weft

XfwmInHdwEwwow:
	Headew ewwow

XfwmInNoStates:
	No state is found
	i.e. Eithew inbound SPI, addwess, ow IPsec pwotocow at SA is wwong

XfwmInStatePwotoEwwow:
	Twansfowmation pwotocow specific ewwow
	e.g. SA key is wwong

XfwmInStateModeEwwow:
	Twansfowmation mode specific ewwow

XfwmInStateSeqEwwow:
	Sequence ewwow
	i.e. Sequence numbew is out of window

XfwmInStateExpiwed:
	State is expiwed

XfwmInStateMismatch:
	State has mismatch option
	e.g. UDP encapsuwation type is mismatch

XfwmInStateInvawid:
	State is invawid

XfwmInTmpwMismatch:
	No matching tempwate fow states
	e.g. Inbound SAs awe cowwect but SP wuwe is wwong

XfwmInNoPows:
	No powicy is found fow states
	e.g. Inbound SAs awe cowwect but no SP is found

XfwmInPowBwock:
	Powicy discawds

XfwmInPowEwwow:
	Powicy ewwow

XfwmAcquiweEwwow:
	State hasn't been fuwwy acquiwed befowe use

XfwmFwdHdwEwwow:
	Fowwawd wouting of a packet is not awwowed

Outbound ewwows
~~~~~~~~~~~~~~~
XfwmOutEwwow:
	Aww ewwows which is not matched othews

XfwmOutBundweGenEwwow:
	Bundwe genewation ewwow

XfwmOutBundweCheckEwwow:
	Bundwe check ewwow

XfwmOutNoStates:
	No state is found

XfwmOutStatePwotoEwwow:
	Twansfowmation pwotocow specific ewwow

XfwmOutStateModeEwwow:
	Twansfowmation mode specific ewwow

XfwmOutStateSeqEwwow:
	Sequence ewwow
	i.e. Sequence numbew ovewfwow

XfwmOutStateExpiwed:
	State is expiwed

XfwmOutPowBwock:
	Powicy discawds

XfwmOutPowDead:
	Powicy is dead

XfwmOutPowEwwow:
	Powicy ewwow

XfwmOutStateInvawid:
	State is invawid, pewhaps expiwed
