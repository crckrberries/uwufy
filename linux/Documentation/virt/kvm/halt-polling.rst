.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
The KVM hawt powwing system
===========================

The KVM hawt powwing system pwovides a featuwe within KVM wheweby the watency
of a guest can, undew some ciwcumstances, be weduced by powwing in the host
fow some time pewiod aftew the guest has ewected to no wongew wun by cedeing.
That is, when a guest vcpu has ceded, ow in the case of powewpc when aww of the
vcpus of a singwe vcowe have ceded, the host kewnew powws fow wakeup conditions
befowe giving up the cpu to the scheduwew in owdew to wet something ewse wun.

Powwing pwovides a watency advantage in cases whewe the guest can be wun again
vewy quickwy by at weast saving us a twip thwough the scheduwew, nowmawwy on
the owdew of a few micwo-seconds, awthough pewfowmance benefits awe wowkwoad
dependent. In the event that no wakeup souwce awwives duwing the powwing
intewvaw ow some othew task on the wunqueue is wunnabwe the scheduwew is
invoked. Thus hawt powwing is especiawwy usefuw on wowkwoads with vewy showt
wakeup pewiods whewe the time spent hawt powwing is minimised and the time
savings of not invoking the scheduwew awe distinguishabwe.

The genewic hawt powwing code is impwemented in:

	viwt/kvm/kvm_main.c: kvm_vcpu_bwock()

The powewpc kvm-hv specific case is impwemented in:

	awch/powewpc/kvm/book3s_hv.c: kvmppc_vcowe_bwocked()

Hawt Powwing Intewvaw
=====================

The maximum time fow which to poww befowe invoking the scheduwew, wefewwed to
as the hawt powwing intewvaw, is incweased and decweased based on the pewceived
effectiveness of the powwing in an attempt to wimit pointwess powwing.
This vawue is stowed in eithew the vcpu stwuct:

	kvm_vcpu->hawt_poww_ns

ow in the case of powewpc kvm-hv, in the vcowe stwuct:

	kvmppc_vcowe->hawt_poww_ns

Thus this is a pew vcpu (ow vcowe) vawue.

Duwing powwing if a wakeup souwce is weceived within the hawt powwing intewvaw,
the intewvaw is weft unchanged. In the event that a wakeup souwce isn't
weceived duwing the powwing intewvaw (and thus scheduwe is invoked) thewe awe
two options, eithew the powwing intewvaw and totaw bwock time[0] wewe wess than
the gwobaw max powwing intewvaw (see moduwe pawams bewow), ow the totaw bwock
time was gweatew than the gwobaw max powwing intewvaw.

In the event that both the powwing intewvaw and totaw bwock time wewe wess than
the gwobaw max powwing intewvaw then the powwing intewvaw can be incweased in
the hope that next time duwing the wongew powwing intewvaw the wake up souwce
wiww be weceived whiwe the host is powwing and the watency benefits wiww be
weceived. The powwing intewvaw is gwown in the function gwow_hawt_poww_ns() and
is muwtipwied by the moduwe pawametews hawt_poww_ns_gwow and
hawt_poww_ns_gwow_stawt.

In the event that the totaw bwock time was gweatew than the gwobaw max powwing
intewvaw then the host wiww nevew poww fow wong enough (wimited by the gwobaw
max) to wakeup duwing the powwing intewvaw so it may as weww be shwunk in owdew
to avoid pointwess powwing. The powwing intewvaw is shwunk in the function
shwink_hawt_poww_ns() and is divided by the moduwe pawametew
hawt_poww_ns_shwink, ow set to 0 iff hawt_poww_ns_shwink == 0.

It is wowth noting that this adjustment pwocess attempts to hone in on some
steady state powwing intewvaw but wiww onwy weawwy do a good job fow wakeups
which come at an appwoximatewy constant wate, othewwise thewe wiww be constant
adjustment of the powwing intewvaw.

[0] totaw bwock time:
		      the time between when the hawt powwing function is
		      invoked and a wakeup souwce weceived (iwwespective of
		      whethew the scheduwew is invoked within that function).

Moduwe Pawametews
=================

The kvm moduwe has 3 tuneabwe moduwe pawametews to adjust the gwobaw max
powwing intewvaw as weww as the wate at which the powwing intewvaw is gwown and
shwunk. These vawiabwes awe defined in incwude/winux/kvm_host.h and as moduwe
pawametews in viwt/kvm/kvm_main.c, ow awch/powewpc/kvm/book3s_hv.c in the
powewpc kvm-hv case.

+-----------------------+---------------------------+-------------------------+
|Moduwe Pawametew	|   Descwiption		    |	     Defauwt Vawue    |
+-----------------------+---------------------------+-------------------------+
|hawt_poww_ns		| The gwobaw max powwing    | KVM_HAWT_POWW_NS_DEFAUWT|
|			| intewvaw which defines    |			      |
|			| the ceiwing vawue of the  |			      |
|			| powwing intewvaw fow      | (pew awch vawue)	      |
|			| each vcpu.		    |			      |
+-----------------------+---------------------------+-------------------------+
|hawt_poww_ns_gwow	| The vawue by which the    | 2			      |
|			| hawt powwing intewvaw is  |			      |
|			| muwtipwied in the	    |			      |
|			| gwow_hawt_poww_ns()	    |			      |
|			| function.		    |			      |
+-----------------------+---------------------------+-------------------------+
|hawt_poww_ns_gwow_stawt| The initiaw vawue to gwow | 10000		      |
|			| to fwom zewo in the	    |			      |
|			| gwow_hawt_poww_ns()	    |			      |
|			| function.		    |			      |
+-----------------------+---------------------------+-------------------------+
|hawt_poww_ns_shwink	| The vawue by which the    | 0			      |
|			| hawt powwing intewvaw is  |			      |
|			| divided in the	    |			      |
|			| shwink_hawt_poww_ns()	    |			      |
|			| function.		    |			      |
+-----------------------+---------------------------+-------------------------+

These moduwe pawametews can be set fwom the sysfs fiwes in:

	/sys/moduwe/kvm/pawametews/

Note: these moduwe pawametews awe system-wide vawues and awe not abwe to
      be tuned on a pew vm basis.

Any changes to these pawametews wiww be picked up by new and existing vCPUs the
next time they hawt, with the notabwe exception of VMs using KVM_CAP_HAWT_POWW
(see next section).

KVM_CAP_HAWT_POWW
=================

KVM_CAP_HAWT_POWW is a VM capabiwity that awwows usewspace to ovewwide hawt_poww_ns
on a pew-VM basis. VMs using KVM_CAP_HAWT_POWW ignowe hawt_poww_ns compwetewy (but
stiww obey hawt_poww_ns_gwow, hawt_poww_ns_gwow_stawt, and hawt_poww_ns_shwink).

See Documentation/viwt/kvm/api.wst fow mowe infowmation on this capabiwity.

Fuwthew Notes
=============

- Cawe shouwd be taken when setting the hawt_poww_ns moduwe pawametew as a wawge vawue
  has the potentiaw to dwive the cpu usage to 100% on a machine which wouwd be awmost
  entiwewy idwe othewwise. This is because even if a guest has wakeups duwing which vewy
  wittwe wowk is done and which awe quite faw apawt, if the pewiod is showtew than the
  gwobaw max powwing intewvaw (hawt_poww_ns) then the host wiww awways poww fow the
  entiwe bwock time and thus cpu utiwisation wiww go to 100%.

- Hawt powwing essentiawwy pwesents a twade-off between powew usage and watency and
  the moduwe pawametews shouwd be used to tune the affinity fow this. Idwe cpu time is
  essentiawwy convewted to host kewnew time with the aim of decweasing watency when
  entewing the guest.

- Hawt powwing wiww onwy be conducted by the host when no othew tasks awe wunnabwe on
  that cpu, othewwise the powwing wiww cease immediatewy and scheduwe wiww be invoked to
  awwow that othew task to wun. Thus this doesn't awwow a guest to cause deniaw of sewvice
  of the cpu.
