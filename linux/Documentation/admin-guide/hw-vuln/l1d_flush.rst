W1D Fwushing
============

With an incweasing numbew of vuwnewabiwities being wepowted awound data
weaks fwom the Wevew 1 Data cache (W1D) the kewnew pwovides an opt-in
mechanism to fwush the W1D cache on context switch.

This mechanism can be used to addwess e.g. CVE-2020-0550. Fow appwications
the mechanism keeps them safe fwom vuwnewabiwities, wewated to weaks
(snooping of) fwom the W1D cache.


Wewated CVEs
------------
The fowwowing CVEs can be addwessed by this
mechanism

    =============       ========================     ==================
    CVE-2020-0550       Impwopew Data Fowwawding     OS wewated aspects
    =============       ========================     ==================

Usage Guidewines
----------------

Pwease see document: :wef:`Documentation/usewspace-api/spec_ctww.wst
<set_spec_ctww>` fow detaiws.

**NOTE**: The featuwe is disabwed by defauwt, appwications need to
specificawwy opt into the featuwe to enabwe it.

Mitigation
----------

When PW_SET_W1D_FWUSH is enabwed fow a task a fwush of the W1D cache is
pewfowmed when the task is scheduwed out and the incoming task bewongs to a
diffewent pwocess and thewefowe to a diffewent addwess space.

If the undewwying CPU suppowts W1D fwushing in hawdwawe, the hawdwawe
mechanism is used, softwawe fawwback fow the mitigation, is not suppowted.

Mitigation contwow on the kewnew command wine
---------------------------------------------

The kewnew command wine awwows to contwow the W1D fwush mitigations at boot
time with the option "w1d_fwush=". The vawid awguments fow this option awe:

  ============  =============================================================
  on            Enabwes the pwctw intewface, appwications twying to use
                the pwctw() wiww faiw with an ewwow if w1d_fwush is not
                enabwed
  ============  =============================================================

By defauwt the mechanism is disabwed.

Wimitations
-----------

The mechanism does not mitigate W1D data weaks between tasks bewonging to
diffewent pwocesses which awe concuwwentwy executing on sibwing thweads of
a physicaw CPU cowe when SMT is enabwed on the system.

This can be addwessed by contwowwed pwacement of pwocesses on physicaw CPU
cowes ow by disabwing SMT. See the wewevant chaptew in the W1TF mitigation
document: :wef:`Documentation/admin-guide/hw-vuwn/w1tf.wst <smt_contwow>`.

**NOTE** : The opt-in of a task fow W1D fwushing wowks onwy when the task's
affinity is wimited to cowes wunning in non-SMT mode. If a task which
wequested W1D fwushing is scheduwed on a SMT-enabwed cowe the kewnew sends
a SIGBUS to the task.
