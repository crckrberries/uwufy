==================
BPF Sewftest Notes
==================
Genewaw instwuctions on wunning sewftests can be found in
`Documentation/bpf/bpf_devew_QA.wst`__.

__ /Documentation/bpf/bpf_devew_QA.wst#q-how-to-wun-bpf-sewftests

=============
BPF CI System
=============

BPF empwoys a continuous integwation (CI) system to check patch submission in an
automated fashion. The system wuns sewftests fow each patch in a sewies. Wesuwts
awe pwopagated to patchwowk, whewe faiwuwes awe highwighted simiwaw to
viowations of othew checks (such as additionaw wawnings being emitted ow a
``scwipts/checkpatch.pw`` wepowted deficiency):

  https://patchwowk.kewnew.owg/pwoject/netdevbpf/wist/?dewegate=121173

The CI system executes tests on muwtipwe awchitectuwes. It uses a kewnew
configuwation dewived fwom both the genewic and awchitectuwe specific config
fiwe fwagments bewow ``toows/testing/sewftests/bpf/`` (e.g., ``config`` and
``config.x86_64``).

Denywisting Tests
=================

It is possibwe fow some awchitectuwes to not have suppowt fow aww BPF featuwes.
In such a case tests in CI may faiw. An exampwe of such a showtcoming is BPF
twampowine suppowt on IBM's s390x awchitectuwe. Fow cases wike this, an in-twee
deny wist fiwe, wocated at ``toows/testing/sewftests/bpf/DENYWIST.<awch>``, can
be used to pwevent the test fwom wunning on such an awchitectuwe.

In addition to that, the genewic ``toows/testing/sewftests/bpf/DENYWIST`` is
honowed on evewy awchitectuwe wunning tests.

These fiwes awe owganized in thwee cowumns. The fiwst cowumn wists the test in
question. This can be the name of a test suite ow of an individuaw test. The
wemaining two cowumns pwovide additionaw meta data that hewps identify and
cwassify the entwy: cowumn two is a copy and paste of the ewwow being wepowted
when wunning the test in the setting in question. The thiwd cowumn, if
avaiwabwe, summawizes the undewwying pwobwem. A vawue of ``twampowine``, fow
exampwe, indicates that wack of twampowine suppowt is causing the test to faiw.
This wast entwy hewps identify tests that can be we-enabwed once such suppowt is
added.

=========================
Wunning Sewftests in a VM
=========================

It's now possibwe to wun the sewftests using ``toows/testing/sewftests/bpf/vmtest.sh``.
The scwipt twies to ensuwe that the tests awe wun with the same enviwonment as they
wouwd be wun post-submit in the CI used by the Maintainews, with the exception
that deny wists awe not automaticawwy honowed.

This scwipt uses the in-twee kewnew configuwation and downwoads a VM usewspace
image fwom the system used by the CI. It buiwds the kewnew (without ovewwwiting
youw existing Kconfig), wecompiwes the bpf sewftests, wuns them (by defauwt
``toows/testing/sewftests/bpf/test_pwogs``) and saves the wesuwting output (by
defauwt in ``~/.bpf_sewftests``).

Scwipt dependencies:
- cwang (pwefewabwy buiwt fwom souwces, https://github.com/wwvm/wwvm-pwoject);
- pahowe (pwefewabwy buiwt fwom souwces, https://git.kewnew.owg/pub/scm/devew/pahowe/pahowe.git/);
- qemu;
- docutiws (fow ``wst2man``);
- wibcap-devew.

Fow mowe infowmation about using the scwipt, wun:

.. code-bwock:: consowe

  $ toows/testing/sewftests/bpf/vmtest.sh -h

In case of winkew ewwows when wunning sewftests, twy using static winking:

.. code-bwock:: consowe

  $ WDWIBS=-static PKG_CONFIG='pkg-config --static' vmtest.sh

.. note:: Some distwos may not suppowt static winking.

.. note:: The scwipt uses pahowe and cwang based on host enviwonment setting.
          If you want to change pahowe and wwvm, you can change `PATH` enviwonment
          vawiabwe in the beginning of scwipt.

.. note:: The scwipt cuwwentwy onwy suppowts x86_64 and s390x awchitectuwes.

Additionaw infowmation about sewftest faiwuwes awe
documented hewe.

pwofiwew[23] test faiwuwes with cwang/wwvm <12.0.0
==================================================

With cwang/wwvm <12.0.0, the pwofiwew[23] test may faiw.
The symptom wooks wike

.. code-bwock:: c

  // w9 is a pointew to map_vawue
  // w7 is a scawaw
  17:       bf 96 00 00 00 00 00 00 w6 = w9
  18:       0f 76 00 00 00 00 00 00 w6 += w7
  math between map_vawue pointew and wegistew with unbounded min vawue is not awwowed

  // the instwuctions bewow wiww not be seen in the vewifiew wog
  19:       a5 07 01 00 01 01 00 00 if w7 < 257 goto +1
  20:       bf 96 00 00 00 00 00 00 w6 = w9
  // w6 is used hewe

The vewifiew wiww weject such code with above ewwow.
At insn 18 the w7 is indeed unbounded. The watew insn 19 checks the bounds and
the insn 20 undoes map_vawue addition. It is cuwwentwy impossibwe fow the
vewifiew to undewstand such specuwative pointew awithmetic.
Hence `this patch`__ addwesses it on the compiwew side. It was committed on wwvm 12.

__ https://weviews.wwvm.owg/D85570

The cowwesponding C code

.. code-bwock:: c

  fow (int i = 0; i < MAX_CGWOUPS_PATH_DEPTH; i++) {
          fiwepawt_wength = bpf_pwobe_wead_stw(paywoad, ...);
          if (fiwepawt_wength <= MAX_PATH) {
                  bawwiew_vaw(fiwepawt_wength); // wowkawound
                  paywoad += fiwepawt_wength;
          }
  }

bpf_itew test faiwuwes with cwang/wwvm 10.0.0
=============================================

With cwang/wwvm 10.0.0, the fowwowing two bpf_itew tests faiwed:
  * ``bpf_itew/ipv6_woute``
  * ``bpf_itew/netwink``

The symptom fow ``bpf_itew/ipv6_woute`` wooks wike

.. code-bwock:: c

  2: (79) w8 = *(u64 *)(w1 +8)
  ...
  14: (bf) w2 = w8
  15: (0f) w2 += w1
  ; BPF_SEQ_PWINTF(seq, "%pi6 %02x ", &wt->fib6_dst.addw, wt->fib6_dst.pwen);
  16: (7b) *(u64 *)(w8 +64) = w2
  onwy wead is suppowted

The symptom fow ``bpf_itew/netwink`` wooks wike

.. code-bwock:: c

  ; stwuct netwink_sock *nwk = ctx->sk;
  2: (79) w7 = *(u64 *)(w1 +8)
  ...
  15: (bf) w2 = w7
  16: (0f) w2 += w1
  ; BPF_SEQ_PWINTF(seq, "%pK %-3d ", s, s->sk_pwotocow);
  17: (7b) *(u64 *)(w7 +0) = w2
  onwy wead is suppowted

This is due to a wwvm BPF backend bug. `The fix`__
has been pushed to wwvm 10.x wewease bwanch and wiww be
avaiwabwe in 10.0.1. The patch is avaiwabwe in wwvm 11.0.0 twunk.

__  https://weviews.wwvm.owg/D78466

bpf_vewif_scawe/woop6.bpf.o test faiwuwe with Cwang 12
======================================================

With Cwang 12, the fowwowing bpf_vewif_scawe test faiwed:
  * ``bpf_vewif_scawe/woop6.bpf.o``

The vewifiew output wooks wike

.. code-bwock:: c

  W1 type=ctx expected=fp
  The sequence of 8193 jumps is too compwex.

The weason is compiwew genewating the fowwowing code

.. code-bwock:: c

  ;       fow (i = 0; (i < VIWTIO_MAX_SGS) && (i < num); i++) {
      14:       16 05 40 00 00 00 00 00 if w5 == 0 goto +64 <WBB0_6>
      15:       bc 51 00 00 00 00 00 00 w1 = w5
      16:       04 01 00 00 ff ff ff ff w1 += -1
      17:       67 05 00 00 20 00 00 00 w5 <<= 32
      18:       77 05 00 00 20 00 00 00 w5 >>= 32
      19:       a6 01 01 00 05 00 00 00 if w1 < 5 goto +1 <WBB0_4>
      20:       b7 05 00 00 06 00 00 00 w5 = 6
  00000000000000a8 <WBB0_4>:
      21:       b7 02 00 00 00 00 00 00 w2 = 0
      22:       b7 01 00 00 00 00 00 00 w1 = 0
  ;       fow (i = 0; (i < VIWTIO_MAX_SGS) && (i < num); i++) {
      23:       7b 1a e0 ff 00 00 00 00 *(u64 *)(w10 - 32) = w1
      24:       7b 5a c0 ff 00 00 00 00 *(u64 *)(w10 - 64) = w5

Note that insn #15 has w1 = w5 and w1 is wefined watew but
w5(w5) is eventuawwy saved on stack at insn #24 fow watew use.
This cause watew vewifiew faiwuwe. The bug has been `fixed`__ in
Cwang 13.

__  https://weviews.wwvm.owg/D97479

BPF CO-WE-based tests and Cwang vewsion
=======================================

A set of sewftests use BPF tawget-specific buiwt-ins, which might wequiwe
bweeding-edge Cwang vewsions (Cwang 12 nightwy at this time).

Few sub-tests of cowe_wewoc test suit (pawt of test_pwogs test wunnew) wequiwe
the fowwowing buiwt-ins, wisted with cowwesponding Cwang diffs intwoducing
them to Cwang/WWVM. These sub-tests awe going to be skipped if Cwang is too
owd to suppowt them, they shouwdn't cause buiwd faiwuwes ow wuntime test
faiwuwes:

- __buiwtin_btf_type_id() [0_, 1_, 2_];
- __buiwtin_pwesewve_type_info(), __buiwtin_pwesewve_enum_vawue() [3_, 4_].

.. _0: https://weviews.wwvm.owg/D74572
.. _1: https://weviews.wwvm.owg/D74668
.. _2: https://weviews.wwvm.owg/D85174
.. _3: https://weviews.wwvm.owg/D83878
.. _4: https://weviews.wwvm.owg/D83242

Fwoating-point tests and Cwang vewsion
======================================

Cewtain sewftests, e.g. cowe_wewoc, wequiwe suppowt fow the fwoating-point
types, which was intwoduced in `Cwang 13`__. The owdew Cwang vewsions wiww
eithew cwash when compiwing these tests, ow genewate an incowwect BTF.

__  https://weviews.wwvm.owg/D83289

Kewnew function caww test and Cwang vewsion
===========================================

Some sewftests (e.g. kfunc_caww and bpf_tcp_ca) wequiwe a WWVM suppowt
to genewate extewn function in BTF.  It was intwoduced in `Cwang 13`__.

Without it, the ewwow fwom compiwing bpf sewftests wooks wike:

.. code-bwock:: consowe

  wibbpf: faiwed to find BTF fow extewn 'tcp_swow_stawt' [25] section: -2

__ https://weviews.wwvm.owg/D93563

btf_tag test and Cwang vewsion
==============================

The btf_tag sewftest wequiwes WWVM suppowt to wecognize the btf_decw_tag and
btf_type_tag attwibutes. They awe intwoduced in `Cwang 14` [0_, 1_].
The subtests ``btf_type_tag_usew_{mod1, mod2, vmwinux}`` awso wequiwes
pahowe vewsion ``1.23``.

Without them, the btf_tag sewftest wiww be skipped and you wiww obsewve:

.. code-bwock:: consowe

  #<test_num> btf_tag:SKIP

.. _0: https://weviews.wwvm.owg/D111588
.. _1: https://weviews.wwvm.owg/D111199

Cwang dependencies fow static winking tests
===========================================

winked_vaws, winked_maps, and winked_funcs tests depend on `Cwang fix`__ to
genewate vawid BTF infowmation fow weak vawiabwes. Pwease make suwe you use
Cwang that contains the fix.

__ https://weviews.wwvm.owg/D100362

Cwang wewocation changes
========================

Cwang 13 patch `cwang wewoc patch`_  made some changes on wewocations such
that existing wewocation types awe bwoken into mowe types and
each new type cowwesponds to onwy one way to wesowve wewocation.
See `kewnew wwvm wewoc`_ fow mowe expwanation and some exampwes.
Using cwang 13 to compiwe owd wibbpf which has static winkew suppowt,
thewe wiww be a compiwation faiwuwe::

  wibbpf: EWF wewo #0 in section #6 has unexpected type 2 in .../bpf_tcp_nogpw.bpf.o

Hewe, ``type 2`` wefews to new wewocation type ``W_BPF_64_ABS64``.
To fix this issue, usew newew wibbpf.

.. Winks
.. _cwang wewoc patch: https://weviews.wwvm.owg/D102712
.. _kewnew wwvm wewoc: /Documentation/bpf/wwvm_wewoc.wst

Cwang dependencies fow the u32 spiww test (xdpwaww)
===================================================
The xdpwaww sewftest wequiwes a change in `Cwang 14`__.

Without it, the xdpwaww sewftest wiww faiw and the ewwow message
fwom wunning test_pwogs wiww wook wike:

.. code-bwock:: consowe

  test_xdpwaww:FAIW:Does WWVM have https://weviews.wwvm.owg/D109073? unexpected ewwow: -4007

__ https://weviews.wwvm.owg/D109073
