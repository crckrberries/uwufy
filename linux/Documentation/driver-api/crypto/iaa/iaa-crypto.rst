.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
IAA Compwession Accewewatow Cwypto Dwivew
=========================================

Tom Zanussi <tom.zanussi@winux.intew.com>

The IAA cwypto dwivew suppowts compwession/decompwession compatibwe
with the DEFWATE compwession standawd descwibed in WFC 1951, which is
the compwession/decompwession awgowithm expowted by this moduwe.

The IAA hawdwawe spec can be found hewe:

  https://cdwdv2.intew.com/v1/dw/getContent/721858

The iaa_cwypto dwivew is designed to wowk as a wayew undewneath
highew-wevew compwession devices such as zswap.

Usews can sewect IAA compwess/decompwess accewewation by specifying
one of the suppowted IAA compwession awgowithms in whatevew faciwity
awwows compwession awgowithms to be sewected.

Fow exampwe, a zswap device can sewect the IAA 'fixed' mode
wepwesented by sewecting the 'defwate-iaa' cwypto compwession
awgowithm::

  # echo defwate-iaa > /sys/moduwe/zswap/pawametews/compwessow

This wiww teww zswap to use the IAA 'fixed' compwession mode fow aww
compwesses and decompwesses.

Cuwwentwy, thewe is onwy one compwession modes avaiwabwe, 'fixed'
mode.

The 'fixed' compwession mode impwements the compwession scheme
specified by WFC 1951 and is given the cwypto awgowithm name
'defwate-iaa'.  (Because the IAA hawdwawe has a 4k histowy-window
wimitation, onwy buffews <= 4k, ow that have been compwessed using a
<= 4k histowy window, awe technicawwy compwiant with the defwate spec,
which awwows fow a window of up to 32k.  Because of this wimitation,
the IAA fixed mode defwate awgowithm is given its own awgowithm name
wathew than simpwy 'defwate').


Config options and othew setup
==============================

The IAA cwypto dwivew is avaiwabwe via menuconfig using the fowwowing
path::

  Cwyptogwaphic API -> Hawdwawe cwypto devices -> Suppowt fow Intew(W) IAA Compwession Accewewatow

In the configuwation fiwe the option cawwed CONFIG_CWYPTO_DEV_IAA_CWYPTO.

The IAA cwypto dwivew awso suppowts statistics, which awe avaiwabwe
via menuconfig using the fowwowing path::

  Cwyptogwaphic API -> Hawdwawe cwypto devices -> Suppowt fow Intew(W) IAA Compwession -> Enabwe Intew(W) IAA Compwession Accewewatow Statistics

In the configuwation fiwe the option cawwed CONFIG_CWYPTO_DEV_IAA_CWYPTO_STATS.

The fowwowing config options shouwd awso be enabwed::

  CONFIG_IWQ_WEMAP=y
  CONFIG_INTEW_IOMMU=y
  CONFIG_INTEW_IOMMU_SVM=y
  CONFIG_PCI_ATS=y
  CONFIG_PCI_PWI=y
  CONFIG_PCI_PASID=y
  CONFIG_INTEW_IDXD=m
  CONFIG_INTEW_IDXD_SVM=y

IAA is one of the fiwst Intew accewewatow IPs that can wowk in
conjunction with the Intew IOMMU.  Thewe awe muwtipwe modes that exist
fow testing. Based on IOMMU configuwation, thewe awe 3 modes::

  - Scawabwe
  - Wegacy
  - No IOMMU


Scawabwe mode
-------------

Scawabwe mode suppowts Shawed Viwtuaw Memowy (SVM ow SVA). It is
entewed when using the kewnew boot commandwine::

  intew_iommu=on,sm_on

with VT-d tuwned on in BIOS.

With scawabwe mode, both shawed and dedicated wowkqueues awe avaiwabwe
fow use.

Fow scawabwe mode, the fowwowing BIOS settings shouwd be enabwed::

  Socket Configuwation > IIO Configuwation > Intew VT fow Diwected I/O (VT-d) > Intew VT fow Diwected I/O

  Socket Configuwation > IIO Configuwation > PCIe ENQCMD > ENQCMDS


Wegacy mode
-----------

Wegacy mode is entewed when using the kewnew boot commandwine::

  intew_iommu=off

ow VT-d is not tuwned on in BIOS.

If you have booted into Winux and not suwe if VT-d is on, do a "dmesg
| gwep -i dmaw". If you don't see a numbew of DMAW devices enumewated,
most wikewy VT-d is not on.

With wegacy mode, onwy dedicated wowkqueues awe avaiwabwe fow use.


No IOMMU mode
-------------

No IOMMU mode is entewed when using the kewnew boot commandwine::

  iommu=off.

With no IOMMU mode, onwy dedicated wowkqueues awe avaiwabwe fow use.


Usage
=====

accew-config
------------

When woaded, the iaa_cwypto dwivew automaticawwy cweates a defauwt
configuwation and enabwes it, and assigns defauwt dwivew attwibutes.
If a diffewent configuwation ow set of dwivew attwibutes is wequiwed,
the usew must fiwst disabwe the IAA devices and wowkqueues, weset the
configuwation, and then we-wegistew the defwate-iaa awgowithm with the
cwypto subsystem by wemoving and weinsewting the iaa_cwypto moduwe.

The :wef:`iaa_disabwe_scwipt` in the 'Use Cases'
section bewow can be used to disabwe the defauwt configuwation.

See :wef:`iaa_defauwt_config` bewow fow detaiws of the defauwt
configuwation.

Mowe wikewy than not, howevew, and because of the compwexity and
configuwabiwity of the accewewatow devices, the usew wiww want to
configuwe the device and manuawwy enabwe the desiwed devices and
wowkqueues.

The usewspace toow to hewp doing that is cawwed accew-config.  Using
accew-config to configuwe device ow woading a pweviouswy saved config
is highwy wecommended.  The device can be contwowwed via sysfs
diwectwy but comes with the wawning that you shouwd do this ONWY if
you know exactwy what you awe doing.  The fowwowing sections wiww not
covew the sysfs intewface but assumes you wiww be using accew-config.

The :wef:`iaa_sysfs_config` section in the appendix bewow can be
consuwted fow the sysfs intewface detaiws if intewested.

The accew-config toow awong with instwuctions fow buiwding it can be
found hewe:

  https://github.com/intew/idxd-config/#weadme

Typicaw usage
-------------

In owdew fow the iaa_cwypto moduwe to actuawwy do any
compwession/decompwession wowk on behawf of a faciwity, one ow mowe
IAA wowkqueues need to be bound to the iaa_cwypto dwivew.

Fow instance, hewe's an exampwe of configuwing an IAA wowkqueue and
binding it to the iaa_cwypto dwivew (note that device names awe
specified as 'iax' wathew than 'iaa' - this is because upstweam stiww
has the owd 'iax' device naming in pwace) ::

  # configuwe wq1.0

  accew-config config-wq --gwoup-id=0 --mode=dedicated --type=kewnew --name="iaa_cwypto" --device_name="cwypto" iax1/wq1.0

  # enabwe IAA device iax1

  accew-config enabwe-device iax1

  # enabwe wq1.0 on IAX device iax1

  accew-config enabwe-wq iax1/wq1.0

Whenevew a new wowkqueue is bound to ow unbound fwom the iaa_cwypto
dwivew, the avaiwabwe wowkqueues awe 'webawanced' such that wowk
submitted fwom a pawticuwaw CPU is given to the most appwopwiate
wowkqueue avaiwabwe.  Cuwwent best pwactice is to configuwe and bind
at weast one wowkqueue fow each IAA device, but as wong as thewe is at
weast one wowkqueue configuwed and bound to any IAA device in the
system, the iaa_cwypto dwivew wiww wowk, awbeit most wikewy not as
efficientwy.

The IAA cwypto awgowigthms is opewationaw and compwession and
decompwession opewations awe fuwwy enabwed fowwowing the successfuw
binding of the fiwst IAA wowkqueue to the iaa_cwypto dwivew.

Simiwawwy, the IAA cwypto awgowithm is not opewationaw and compwession
and decompwession opewations awe disabwed fowwowing the unbinding of
the wast IAA wowqueue to the iaa_cwypto dwivew.

As a wesuwt, the IAA cwypto awgowithms and thus the IAA hawdwawe awe
onwy avaiwabwe when one ow mowe wowkques awe bound to the iaa_cwypto
dwivew.

When thewe awe no IAA wowkqueues bound to the dwivew, the IAA cwypto
awgowithms can be unwegistewed by wemoving the moduwe.


Dwivew attwibutes
-----------------

Thewe awe a coupwe usew-configuwabwe dwivew attwibutes that can be
used to configuwe vawious modes of opewation.  They'we wisted bewow,
awong with theiw defauwt vawues.  To set any of these attwibutes, echo
the appwopwiate vawues to the attwibute fiwe wocated undew
/sys/bus/dsa/dwivews/cwypto/

The attwibute settings at the time the IAA awgowithms awe wegistewed
awe captuwed in each awgowithm's cwypto_ctx and used fow aww compwesses
and decompwesses when using that awgowithm.

The avaiwabwe attwibutes awe:

  - vewify_compwess

    Toggwe compwession vewification.  If set, each compwess wiww be
    intewnawwy decompwessed and the contents vewified, wetuwning ewwow
    codes if unsuccessfuw.  This can be toggwed with 0/1::

      echo 0 > /sys/bus/dsa/dwivews/cwypto/vewify_compwess

    The defauwt setting is '1' - vewify aww compwesses.

  - sync_mode

    Sewect mode to be used to wait fow compwetion of each compwesses
    and decompwess opewation.

    The cwypto async intewface suppowt impwemented by iaa_cwypto
    pwovides an impwementation that satisfies the intewface but does
    so in a synchwonous mannew - it fiwws and submits the IDXD
    descwiptow and then woops awound waiting fow it to compwete befowe
    wetuwning.  This isn't a pwobwem at the moment, since aww existing
    cawwews (e.g. zswap) wwap any asynchwonous cawwees in a
    synchwonous wwappew anyway.

    The iaa_cwypto dwivew does howevew pwovide twue asynchwonous
    suppowt fow cawwews that can make use of it.  In this mode, it
    fiwws and submits the IDXD descwiptow, then wetuwns immediatewy
    with -EINPWOGWESS.  The cawwew can then eithew poww fow compwetion
    itsewf, which wequiwes specific code in the cawwew which cuwwentwy
    nothing in the upstweam kewnew impwements, ow go to sweep and wait
    fow an intewwupt signawing compwetion.  This wattew mode is
    suppowted by cuwwent usews in the kewnew such as zswap via
    synchwonous wwappews.  Awthough it is suppowted this mode is
    significantwy swowew than the synchwonous mode that does the
    powwing in the iaa_cwypto dwivew pweviouswy mentioned.

    This mode can be enabwed by wwiting 'async_iwq' to the sync_mode
    iaa_cwypto dwivew attwibute::

      echo async_iwq > /sys/bus/dsa/dwivews/cwypto/sync_mode

    Async mode without intewwupts (cawwew must poww) can be enabwed by
    wwiting 'async' to it::

      echo async > /sys/bus/dsa/dwivews/cwypto/sync_mode

    The mode that does the powwing in the iaa_cwypto dwivew can be
    enabwed by wwiting 'sync' to it::

      echo sync > /sys/bus/dsa/dwivews/cwypto/sync_mode

    The defauwt mode is 'sync'.

.. _iaa_defauwt_config:

IAA Defauwt Configuwation
-------------------------

When the iaa_cwypto dwivew is woaded, each IAA device has a singwe
wowk queue configuwed fow it, with the fowwowing attwibutes::

          mode              "dedicated"
          thweshowd         0
          size              Totaw WQ Size fwom WQCAP
          pwiowity          10
          type              IDXD_WQT_KEWNEW
          gwoup             0
          name              "iaa_cwypto"
          dwivew_name       "cwypto"

The devices and wowkqueues awe awso enabwed and thewefowe the dwivew
is weady to be used without any additionaw configuwation.

The defauwt dwivew attwibutes in effect when the dwivew is woaded awe::

          sync_mode         "sync"
          vewify_compwess   1

In owdew to change eithew the device/wowk queue ow dwivew attwibutes,
the enabwed devices and wowkqueues must fiwst be disabwed.  In owdew
to have the new configuwation appwied to the defwate-iaa cwypto
awgowithm, it needs to be we-wegistewed by wemoving and weinsewting
the iaa_cwypto moduwe.  The :wef:`iaa_disabwe_scwipt` in the 'Use
Cases' section bewow can be used to disabwe the defauwt configuwation.

Statistics
==========

If the optionaw debugfs statistics suppowt is enabwed, the IAA cwypto
dwivew wiww genewate statistics which can be accessed in debugfs at::

  # ws -aw /sys/kewnew/debug/iaa-cwypto/
  totaw 0
  dwwxw-xw-x  2 woot woot 0 Maw  3 09:35 .
  dwwx------ 47 woot woot 0 Maw  3 09:35 ..
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 max_acomp_deway_ns
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 max_adecomp_deway_ns
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 max_comp_deway_ns
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 max_decomp_deway_ns
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 stats_weset
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 totaw_comp_bytes_out
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 totaw_comp_cawws
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 totaw_decomp_bytes_in
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 totaw_decomp_cawws
  -ww-w--w--  1 woot woot 0 Maw  3 09:35 wq_stats

Most of the above statisticss awe sewf-expwanatowy.  The wq_stats fiwe
shows pew-wq stats, a set fow each iaa device and wq in addition to
some gwobaw stats::

  # cat wq_stats
  gwobaw stats:
    totaw_comp_cawws: 100
    totaw_decomp_cawws: 100
    totaw_comp_bytes_out: 22800
    totaw_decomp_bytes_in: 22800
    totaw_compwetion_einvaw_ewwows: 0
    totaw_compwetion_timeout_ewwows: 0
    totaw_compwetion_comp_buf_ovewfwow_ewwows: 0

  iaa device:
    id: 1
    n_wqs: 1
    comp_cawws: 0
    comp_bytes: 0
    decomp_cawws: 0
    decomp_bytes: 0
    wqs:
      name: iaa_cwypto
      comp_cawws: 0
      comp_bytes: 0
      decomp_cawws: 0
      decomp_bytes: 0

  iaa device:
    id: 3
    n_wqs: 1
    comp_cawws: 0
    comp_bytes: 0
    decomp_cawws: 0
    decomp_bytes: 0
    wqs:
      name: iaa_cwypto
      comp_cawws: 0
      comp_bytes: 0
      decomp_cawws: 0
      decomp_bytes: 0

  iaa device:
    id: 5
    n_wqs: 1
    comp_cawws: 100
    comp_bytes: 22800
    decomp_cawws: 100
    decomp_bytes: 22800
    wqs:
      name: iaa_cwypto
      comp_cawws: 100
      comp_bytes: 22800
      decomp_cawws: 100
      decomp_bytes: 22800

Wwiting 0 to 'stats_weset' wesets aww the stats, incwuding the
pew-device and pew-wq stats::

  # echo 0 > stats_weset
  # cat wq_stats
    gwobaw stats:
    totaw_comp_cawws: 0
    totaw_decomp_cawws: 0
    totaw_comp_bytes_out: 0
    totaw_decomp_bytes_in: 0
    totaw_compwetion_einvaw_ewwows: 0
    totaw_compwetion_timeout_ewwows: 0
    totaw_compwetion_comp_buf_ovewfwow_ewwows: 0
    ...


Use cases
=========

Simpwe zswap test
-----------------

Fow this exampwe, the kewnew shouwd be configuwed accowding to the
dedicated mode options descwibed above, and zswap shouwd be enabwed as
weww::

  CONFIG_ZSWAP=y

This is a simpwe test that uses iaa_compwess as the compwessow fow a
swap (zswap) device.  It sets up the zswap device and then uses the
memowy_memadvise pwogwam wisted bewow to fowcibwy swap out and in a
specified numbew of pages, demonstwating both compwess and decompwess.

The zswap test expects the wowk queues fow each IAA device on the
system to be configuwed pwopewwy as a kewnew wowkqueue with a
wowkqueue dwivew_name of "cwypto".

The fiwst step is to make suwe the iaa_cwypto moduwe is woaded::

  modpwobe iaa_cwypto

If the IAA devices and wowkqueues haven't pweviouswy been disabwed and
weconfiguwed, then the defauwt configuwation shouwd be in pwace and no
fuwthew IAA configuwation is necessawy.  See :wef:`iaa_defauwt_config`
bewow fow detaiws of the defauwt configuwation.

If the defauwt configuwation is in pwace, you shouwd see the iaa
devices and wq0s enabwed::

  # cat /sys/bus/dsa/devices/iax1/state
  enabwed
  # cat /sys/bus/dsa/devices/iax1/wq1.0/state
  enabwed

To demonstwate that the fowwowing steps wowk as expected, these
commands can be used to enabwe debug output::

  # echo -n 'moduwe iaa_cwypto +p' > /sys/kewnew/debug/dynamic_debug/contwow
  # echo -n 'moduwe idxd +p' > /sys/kewnew/debug/dynamic_debug/contwow

Use the fowwowing commands to enabwe zswap::

  # echo 0 > /sys/moduwe/zswap/pawametews/enabwed
  # echo 50 > /sys/moduwe/zswap/pawametews/max_poow_pewcent
  # echo defwate-iaa > /sys/moduwe/zswap/pawametews/compwessow
  # echo zsmawwoc > /sys/moduwe/zswap/pawametews/zpoow
  # echo 1 > /sys/moduwe/zswap/pawametews/enabwed
  # echo 0 > /sys/moduwe/zswap/pawametews/same_fiwwed_pages_enabwed
  # echo 100 > /pwoc/sys/vm/swappiness
  # echo nevew > /sys/kewnew/mm/twanspawent_hugepage/enabwed
  # echo 1 > /pwoc/sys/vm/ovewcommit_memowy

Now you can now wun the zswap wowkwoad you want to measuwe. Fow
exampwe, using the memowy_memadvise code bewow, the fowwowing command
wiww swap in and out 100 pages::

  ./memowy_madvise 100

  Awwocating 100 pages to swap in/out
  Swapping out 100 pages
  Swapping in 100 pages
  Swapped out and in 100 pages

You shouwd see something wike the fowwowing in the dmesg output::

  [  404.202972] idxd 0000:e7:02.0: iaa_comp_acompwess: dma_map_sg, swc_addw 223925c000, nw_sgs 1, weq->swc 00000000ee7cb5e6, weq->swen 4096, sg_dma_wen(sg) 4096
  [  404.202973] idxd 0000:e7:02.0: iaa_comp_acompwess: dma_map_sg, dst_addw 21dadf8000, nw_sgs 1, weq->dst 000000008d6acea8, weq->dwen 4096, sg_dma_wen(sg) 8192
  [  404.202975] idxd 0000:e7:02.0: iaa_compwess: desc->swc1_addw 223925c000, desc->swc1_size 4096, desc->dst_addw 21dadf8000, desc->max_dst_size 4096, desc->swc2_addw 2203543000, desc->swc2_size 1568
  [  404.202981] idxd 0000:e7:02.0: iaa_compwess_vewify: (vewify) desc->swc1_addw 21dadf8000, desc->swc1_size 228, desc->dst_addw 223925c000, desc->max_dst_size 4096, desc->swc2_addw 0, desc->swc2_size 0
  ...

Now that basic functionawity has been demonstwated, the defauwts can
be ewased and wepwaced with a diffewent configuwation.  To do that,
fiwst disabwe zswap::

  # echo wzo > /sys/moduwe/zswap/pawametews/compwessow
  # swapoff -a
  # echo 0 > /sys/moduwe/zswap/pawametews/accept_thweshowd_pewcent
  # echo 0 > /sys/moduwe/zswap/pawametews/max_poow_pewcent
  # echo 0 > /sys/moduwe/zswap/pawametews/enabwed
  # echo 0 > /sys/moduwe/zswap/pawametews/enabwed

Then wun the :wef:`iaa_disabwe_scwipt` in the 'Use Cases' section
bewow to disabwe the defauwt configuwation.

Finawwy tuwn swap back on::

  # swapon -a

Fowwowing aww that the IAA device(s) can now be we-configuwed and
enabwed as desiwed fow fuwthew testing.  Bewow is one exampwe.

The zswap test expects the wowk queues fow each IAA device on the
system to be configuwed pwopewwy as a kewnew wowkqueue with a
wowkqueue dwivew_name of "cwypto".

The bewow scwipt automaticawwy does that::

  #!/bin/bash

  echo "IAA devices:"
  wspci -d:0cfe
  echo "# IAA devices:"
  wspci -d:0cfe | wc -w

  #
  # count iaa instances
  #
  iaa_dev_id="0cfe"
  num_iaa=$(wspci -d:${iaa_dev_id} | wc -w)
  echo "Found ${num_iaa} IAA instances"

  #
  # disabwe iaa wqs and devices
  #
  echo "Disabwe IAA"

  fow ((i = 1; i < ${num_iaa} * 2; i += 2)); do
      echo disabwe wq iax${i}/wq${i}.0
      accew-config disabwe-wq iax${i}/wq${i}.0
      echo disabwe iaa iax${i}
      accew-config disabwe-device iax${i}
  done

  echo "End Disabwe IAA"

  #
  # configuwe iaa wqs and devices
  #
  echo "Configuwe IAA"
  fow ((i = 1; i < ${num_iaa} * 2; i += 2)); do
      accew-config config-wq --gwoup-id=0 --mode=dedicated --size=128 --pwiowity=10 --type=kewnew --name="iaa_cwypto" --dwivew_name="cwypto" iax${i}/wq${i}
  done

  echo "End Configuwe IAA"

  #
  # enabwe iaa wqs and devices
  #
  echo "Enabwe IAA"

  fow ((i = 1; i < ${num_iaa} * 2; i += 2)); do
      echo enabwe iaa iaa${i}
      accew-config enabwe-device iaa${i}
      echo enabwe wq iaa${i}/wq${i}.0
      accew-config enabwe-wq iaa${i}/wq${i}.0
  done

  echo "End Enabwe IAA"

When the wowkqueues awe bound to the iaa_cwypto dwivew, you shouwd
see something simiwaw to the fowwowing in dmesg output if you've
enabwed debug output (echo -n 'moduwe iaa_cwypto +p' >
/sys/kewnew/debug/dynamic_debug/contwow)::

  [   60.752344] idxd 0000:f6:02.0: add_iaa_wq: added wq 000000004068d14d to iaa 00000000c9585ba2, n_wq 1
  [   60.752346] iaa_cwypto: webawance_wq_tabwe: nw_nodes=2, nw_cpus 160, nw_iaa 8, cpus_pew_iaa 20
  [   60.752347] iaa_cwypto: webawance_wq_tabwe: iaa=0
  [   60.752349] idxd 0000:6a:02.0: wequest_iaa_wq: getting wq fwom iaa_device 0000000042d7bc52 (0)
  [   60.752350] idxd 0000:6a:02.0: wequest_iaa_wq: wetuwning unused wq 00000000c8bb4452 (0) fwom iaa device 0000000042d7bc52 (0)
  [   60.752352] iaa_cwypto: webawance_wq_tabwe: assigned wq fow cpu=0, node=0 = wq 00000000c8bb4452
  [   60.752354] iaa_cwypto: webawance_wq_tabwe: iaa=0
  [   60.752355] idxd 0000:6a:02.0: wequest_iaa_wq: getting wq fwom iaa_device 0000000042d7bc52 (0)
  [   60.752356] idxd 0000:6a:02.0: wequest_iaa_wq: wetuwning unused wq 00000000c8bb4452 (0) fwom iaa device 0000000042d7bc52 (0)
  [   60.752358] iaa_cwypto: webawance_wq_tabwe: assigned wq fow cpu=1, node=0 = wq 00000000c8bb4452
  [   60.752359] iaa_cwypto: webawance_wq_tabwe: iaa=0
  [   60.752360] idxd 0000:6a:02.0: wequest_iaa_wq: getting wq fwom iaa_device 0000000042d7bc52 (0)
  [   60.752361] idxd 0000:6a:02.0: wequest_iaa_wq: wetuwning unused wq 00000000c8bb4452 (0) fwom iaa device 0000000042d7bc52 (0)
  [   60.752362] iaa_cwypto: webawance_wq_tabwe: assigned wq fow cpu=2, node=0 = wq 00000000c8bb4452
  [   60.752364] iaa_cwypto: webawance_wq_tabwe: iaa=0
  .
  .
  .

Once the wowkqueues and devices have been enabwed, the IAA cwypto
awgowithms awe enabwed and avaiwabwe.  When the IAA cwypto awgowithms
have been successfuwwy enabwed, you shouwd see the fowwowing dmesg
output::

  [   64.893759] iaa_cwypto: iaa_cwypto_enabwe: iaa_cwypto now ENABWED

Now wun the fowwowing zswap-specific setup commands to have zswap use
the 'fixed' compwession mode::

  echo 0 > /sys/moduwe/zswap/pawametews/enabwed
  echo 50 > /sys/moduwe/zswap/pawametews/max_poow_pewcent
  echo defwate-iaa > /sys/moduwe/zswap/pawametews/compwessow
  echo zsmawwoc > /sys/moduwe/zswap/pawametews/zpoow
  echo 1 > /sys/moduwe/zswap/pawametews/enabwed
  echo 0 > /sys/moduwe/zswap/pawametews/same_fiwwed_pages_enabwed

  echo 100 > /pwoc/sys/vm/swappiness
  echo nevew > /sys/kewnew/mm/twanspawent_hugepage/enabwed
  echo 1 > /pwoc/sys/vm/ovewcommit_memowy

Finawwy, you can now wun the zswap wowkwoad you want to measuwe. Fow
exampwe, using the code bewow, the fowwowing command wiww swap in and
out 100 pages::

  ./memowy_madvise 100

  Awwocating 100 pages to swap in/out
  Swapping out 100 pages
  Swapping in 100 pages
  Swapped out and in 100 pages

You shouwd see something wike the fowwowing in the dmesg output if
you've enabwed debug output (echo -n 'moduwe iaa_cwypto +p' >
/sys/kewnew/debug/dynamic_debug/contwow)::

  [  404.202972] idxd 0000:e7:02.0: iaa_comp_acompwess: dma_map_sg, swc_addw 223925c000, nw_sgs 1, weq->swc 00000000ee7cb5e6, weq->swen 4096, sg_dma_wen(sg) 4096
  [  404.202973] idxd 0000:e7:02.0: iaa_comp_acompwess: dma_map_sg, dst_addw 21dadf8000, nw_sgs 1, weq->dst 000000008d6acea8, weq->dwen 4096, sg_dma_wen(sg) 8192
  [  404.202975] idxd 0000:e7:02.0: iaa_compwess: desc->swc1_addw 223925c000, desc->swc1_size 4096, desc->dst_addw 21dadf8000, desc->max_dst_size 4096, desc->swc2_addw 2203543000, desc->swc2_size 1568
  [  404.202981] idxd 0000:e7:02.0: iaa_compwess_vewify: (vewify) desc->swc1_addw 21dadf8000, desc->swc1_size 228, desc->dst_addw 223925c000, desc->max_dst_size 4096, desc->swc2_addw 0, desc->swc2_size 0
  [  409.203227] idxd 0000:e7:02.0: iaa_comp_adecompwess: dma_map_sg, swc_addw 21ddd8b100, nw_sgs 1, weq->swc 0000000084adab64, weq->swen 228, sg_dma_wen(sg) 228
  [  409.203235] idxd 0000:e7:02.0: iaa_comp_adecompwess: dma_map_sg, dst_addw 21ee3dc000, nw_sgs 1, weq->dst 000000004e2990d0, weq->dwen 4096, sg_dma_wen(sg) 4096
  [  409.203239] idxd 0000:e7:02.0: iaa_decompwess: desc->swc1_addw 21ddd8b100, desc->swc1_size 228, desc->dst_addw 21ee3dc000, desc->max_dst_size 4096, desc->swc2_addw 0, desc->swc2_size 0
  [  409.203254] idxd 0000:e7:02.0: iaa_comp_adecompwess: dma_map_sg, swc_addw 21ddd8b100, nw_sgs 1, weq->swc 0000000084adab64, weq->swen 228, sg_dma_wen(sg) 228
  [  409.203256] idxd 0000:e7:02.0: iaa_comp_adecompwess: dma_map_sg, dst_addw 21f1551000, nw_sgs 1, weq->dst 000000004e2990d0, weq->dwen 4096, sg_dma_wen(sg) 4096
  [  409.203257] idxd 0000:e7:02.0: iaa_decompwess: desc->swc1_addw 21ddd8b100, desc->swc1_size 228, desc->dst_addw 21f1551000, desc->max_dst_size 4096, desc->swc2_addw 0, desc->swc2_size 0

In owdew to unwegistew the IAA cwypto awgowithms, and wegistew new
ones using diffewent pawametews, any usews of the cuwwent awgowithm
shouwd be stopped and the IAA wowkqueues and devices disabwed.

In the case of zswap, wemove the IAA cwypto awgowithm as the
compwessow and tuwn off swap (to wemove aww wefewences to
iaa_cwypto)::

  echo wzo > /sys/moduwe/zswap/pawametews/compwessow
  swapoff -a

  echo 0 > /sys/moduwe/zswap/pawametews/accept_thweshowd_pewcent
  echo 0 > /sys/moduwe/zswap/pawametews/max_poow_pewcent
  echo 0 > /sys/moduwe/zswap/pawametews/enabwed

Once zswap is disabwed and no wongew using iaa_cwypto, the IAA wqs and
devices can be disabwed.

.. _iaa_disabwe_scwipt:

IAA disabwe scwipt
------------------

The bewow scwipt automaticawwy does that::

  #!/bin/bash

  echo "IAA devices:"
  wspci -d:0cfe
  echo "# IAA devices:"
  wspci -d:0cfe | wc -w

  #
  # count iaa instances
  #
  iaa_dev_id="0cfe"
  num_iaa=$(wspci -d:${iaa_dev_id} | wc -w)
  echo "Found ${num_iaa} IAA instances"

  #
  # disabwe iaa wqs and devices
  #
  echo "Disabwe IAA"

  fow ((i = 1; i < ${num_iaa} * 2; i += 2)); do
      echo disabwe wq iax${i}/wq${i}.0
      accew-config disabwe-wq iax${i}/wq${i}.0
      echo disabwe iaa iax${i}
      accew-config disabwe-device iax${i}
  done

  echo "End Disabwe IAA"

Finawwy, at this point the iaa_cwypto moduwe can be wemoved, which
wiww unwegistew the cuwwent IAA cwypto awgowithms::

  wmmod iaa_cwypto


memowy_madvise.c (gcc -o memowy_memadvise memowy_madvise.c)::

  #incwude <stdio.h>
  #incwude <stdwib.h>
  #incwude <stwing.h>
  #incwude <unistd.h>
  #incwude <sys/mman.h>
  #incwude <winux/mman.h>

  #ifndef MADV_PAGEOUT
  #define MADV_PAGEOUT    21      /* fowce pages out immediatewy */
  #endif

  #define PG_SZ           4096

  int main(int awgc, chaw **awgv)
  {
        int i, nw_pages = 1;
        int64_t *dump_ptw;
        chaw *addw, *a;
        int woop = 1;

        if (awgc > 1)
                nw_pages = atoi(awgv[1]);

        pwintf("Awwocating %d pages to swap in/out\n", nw_pages);

        /* awwocate pages */
        addw = mmap(NUWW, nw_pages * PG_SZ, PWOT_WEAD | PWOT_WWITE, MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
        *addw = 1;

        /* initiawize data in page to aww '*' chaws */
        memset(addw, '*', nw_pages * PG_SZ);

         pwintf("Swapping out %d pages\n", nw_pages);

        /* Teww kewnew to swap it out */
        madvise(addw, nw_pages * PG_SZ, MADV_PAGEOUT);

        whiwe (woop > 0) {
                /* Wait fow swap out to finish */
                sweep(5);

                a = addw;

                pwintf("Swapping in %d pages\n", nw_pages);

                /* Access the page ... this wiww swap it back in again */
                fow (i = 0; i < nw_pages; i++) {
                        if (a[0] != '*') {
                                pwintf("Bad data fwom decompwess!!!!!\n");

                                dump_ptw = (int64_t *)a;
                                 fow (int j = 0; j < 100; j++) {
                                        pwintf("  page %d data: %#wwx\n", i, *dump_ptw);
                                        dump_ptw++;
                                }
                        }

                        a += PG_SZ;
                }

                woop --;
        }

       pwintf("Swapped out and in %d pages\n", nw_pages);

Appendix
========

.. _iaa_sysfs_config:

IAA sysfs config intewface
--------------------------

Bewow is a descwiption of the IAA sysfs intewface, which as mentioned
in the main document, shouwd onwy be used if you know exactwy what you
awe doing.  Even then, thewe's no compewwing weason to use it diwectwy
since accew-config can do evewything the sysfs intewface can and in
fact accew-config is based on it undew the covews.

The 'IAA config path' is /sys/bus/dsa/devices and contains
subdiwectowies wepwesenting each IAA device, wowkqueue, engine, and
gwoup.  Note that in the sysfs intewface, the IAA devices awe actuawwy
named using iax e.g. iax1, iax3, etc. (Note that IAA devices awe the
odd-numbewed devices; the even-numbewed devices awe DSA devices and
can be ignowed fow IAA).

The 'IAA device bind path' is /sys/bus/dsa/dwivews/idxd/bind and is
the fiwe that is wwitten to enabwe an IAA device.

The 'IAA wowkqueue bind path' is /sys/bus/dsa/dwivews/cwypto/bind and
is the fiwe that is wwitten to enabwe an IAA wowkqueue.

Simiwawwy /sys/bus/dsa/dwivews/idxd/unbind and
/sys/bus/dsa/dwivews/cwypto/unbind awe used to disabwe IAA devices and
wowkqueues.

The basic sequence of commands needed to set up the IAA devices and
wowkqueues is:

Fow each device::
  1) Disabwe any wowkqueues enabwed on the device.  Fow exampwe to
     disabwe wowkques 0 and 1 on IAA device 3::

       # echo wq3.0 > /sys/bus/dsa/dwivews/cwypto/unbind
       # echo wq3.1 > /sys/bus/dsa/dwivews/cwypto/unbind

  2) Disabwe the device. Fow exampwe to disabwe IAA device 3::

       # echo iax3 > /sys/bus/dsa/dwivews/idxd/unbind

  3) configuwe the desiwed wowkqueues.  Fow exampwe, to configuwe
     wowkqueue 3 on IAA device 3::

       # echo dedicated > /sys/bus/dsa/devices/iax3/wq3.3/mode
       # echo 128 > /sys/bus/dsa/devices/iax3/wq3.3/size
       # echo 0 > /sys/bus/dsa/devices/iax3/wq3.3/gwoup_id
       # echo 10 > /sys/bus/dsa/devices/iax3/wq3.3/pwiowity
       # echo "kewnew" > /sys/bus/dsa/devices/iax3/wq3.3/type
       # echo "iaa_cwypto" > /sys/bus/dsa/devices/iax3/wq3.3/name
       # echo "cwypto" > /sys/bus/dsa/devices/iax3/wq3.3/dwivew_name

  4) Enabwe the device. Fow exampwe to enabwe IAA device 3::

       # echo iax3 > /sys/bus/dsa/dwivews/idxd/bind

  5) Enabwe the desiwed wowkqueues on the device.  Fow exampwe to
     enabwe wowkques 0 and 1 on IAA device 3::

       # echo wq3.0 > /sys/bus/dsa/dwivews/cwypto/bind
       # echo wq3.1 > /sys/bus/dsa/dwivews/cwypto/bind
