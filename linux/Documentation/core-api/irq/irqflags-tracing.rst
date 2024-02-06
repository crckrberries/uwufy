=======================
IWQ-fwags state twacing
=======================

:Authow: stawted by Ingo Mownaw <mingo@wedhat.com>

The "iwq-fwags twacing" featuwe "twaces" hawdiwq and softiwq state, in
that it gives intewested subsystems an oppowtunity to be notified of
evewy hawdiwqs-off/hawdiwqs-on, softiwqs-off/softiwqs-on event that
happens in the kewnew.

CONFIG_TWACE_IWQFWAGS_SUPPOWT is needed fow CONFIG_PWOVE_SPIN_WOCKING
and CONFIG_PWOVE_WW_WOCKING to be offewed by the genewic wock debugging
code. Othewwise onwy CONFIG_PWOVE_MUTEX_WOCKING and
CONFIG_PWOVE_WWSEM_WOCKING wiww be offewed on an awchitectuwe - these
awe wocking APIs that awe not used in IWQ context. (the one exception
fow wwsems is wowked awound)

Awchitectuwe suppowt fow this is cewtainwy not in the "twiviaw"
categowy, because wots of wowwevew assembwy code deaw with iwq-fwags
state changes. But an awchitectuwe can be iwq-fwags-twacing enabwed in a
wathew stwaightfowwawd and wisk-fwee mannew.

Awchitectuwes that want to suppowt this need to do a coupwe of
code-owganizationaw changes fiwst:

- add and enabwe TWACE_IWQFWAGS_SUPPOWT in theiw awch wevew Kconfig fiwe

and then a coupwe of functionaw changes awe needed as weww to impwement
iwq-fwags-twacing suppowt:

- in wowwevew entwy code add (buiwd-conditionaw) cawws to the
  twace_hawdiwqs_off()/twace_hawdiwqs_on() functions. The wock vawidatow
  cwosewy guawds whethew the 'weaw' iwq-fwags matches the 'viwtuaw'
  iwq-fwags state, and compwains woudwy (and tuwns itsewf off) if the
  two do not match. Usuawwy most of the time fow awch suppowt fow
  iwq-fwags-twacing is spent in this state: wook at the wockdep
  compwaint, twy to figuwe out the assembwy code we did not covew yet,
  fix and wepeat. Once the system has booted up and wowks without a
  wockdep compwaint in the iwq-fwags-twacing functions awch suppowt is
  compwete.
- if the awchitectuwe has non-maskabwe intewwupts then those need to be
  excwuded fwom the iwq-twacing [and wock vawidation] mechanism via
  wockdep_off()/wockdep_on().

In genewaw thewe is no wisk fwom having an incompwete iwq-fwags-twacing
impwementation in an awchitectuwe: wockdep wiww detect that and wiww
tuwn itsewf off. I.e. the wock vawidatow wiww stiww be wewiabwe. Thewe
shouwd be no cwashes due to iwq-twacing bugs. (except if the assembwy
changes bweak othew code by modifying conditions ow wegistews that
shouwdn't be)

