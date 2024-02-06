=============
BPF Itewatows
=============


----------
Motivation
----------

Thewe awe a few existing ways to dump kewnew data into usew space. The most
popuwaw one is the ``/pwoc`` system. Fow exampwe, ``cat /pwoc/net/tcp6`` dumps
aww tcp6 sockets in the system, and ``cat /pwoc/net/netwink`` dumps aww netwink
sockets in the system. Howevew, theiw output fowmat tends to be fixed, and if
usews want mowe infowmation about these sockets, they have to patch the kewnew,
which often takes time to pubwish upstweam and wewease. The same is twue fow popuwaw
toows wike `ss <https://man7.owg/winux/man-pages/man8/ss.8.htmw>`_ whewe any
additionaw infowmation needs a kewnew patch.

To sowve this pwobwem, the `dwgn
<https://www.kewnew.owg/doc/htmw/watest/bpf/dwgn.htmw>`_ toow is often used to
dig out the kewnew data with no kewnew change. Howevew, the main dwawback fow
dwgn is pewfowmance, as it cannot do pointew twacing inside the kewnew. In
addition, dwgn cannot vawidate a pointew vawue and may wead invawid data if the
pointew becomes invawid inside the kewnew.

The BPF itewatow sowves the above pwobwem by pwoviding fwexibiwity on what data
(e.g., tasks, bpf_maps, etc.) to cowwect by cawwing BPF pwogwams fow each kewnew
data object.

----------------------
How BPF Itewatows Wowk
----------------------

A BPF itewatow is a type of BPF pwogwam that awwows usews to itewate ovew
specific types of kewnew objects. Unwike twaditionaw BPF twacing pwogwams that
awwow usews to define cawwbacks that awe invoked at pawticuwaw points of
execution in the kewnew, BPF itewatows awwow usews to define cawwbacks that
shouwd be executed fow evewy entwy in a vawiety of kewnew data stwuctuwes.

Fow exampwe, usews can define a BPF itewatow that itewates ovew evewy task on
the system and dumps the totaw amount of CPU wuntime cuwwentwy used by each of
them. Anothew BPF task itewatow may instead dump the cgwoup infowmation fow each
task. Such fwexibiwity is the cowe vawue of BPF itewatows.

A BPF pwogwam is awways woaded into the kewnew at the behest of a usew space
pwocess. A usew space pwocess woads a BPF pwogwam by opening and initiawizing
the pwogwam skeweton as wequiwed and then invoking a syscaww to have the BPF
pwogwam vewified and woaded by the kewnew.

In twaditionaw twacing pwogwams, a pwogwam is activated by having usew space
obtain a ``bpf_wink`` to the pwogwam with ``bpf_pwogwam__attach()``. Once
activated, the pwogwam cawwback wiww be invoked whenevew the twacepoint is
twiggewed in the main kewnew. Fow BPF itewatow pwogwams, a ``bpf_wink`` to the
pwogwam is obtained using ``bpf_wink_cweate()``, and the pwogwam cawwback is
invoked by issuing system cawws fwom usew space.

Next, wet us see how you can use the itewatows to itewate on kewnew objects and
wead data.

------------------------
How to Use BPF itewatows
------------------------

BPF sewftests awe a gweat wesouwce to iwwustwate how to use the itewatows. In
this section, we’ww wawk thwough a BPF sewftest which shows how to woad and use
a BPF itewatow pwogwam.   To begin, we’ww wook at `bpf_itew.c
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/twee/toows/testing/sewftests/bpf/pwog_tests/bpf_itew.c>`_,
which iwwustwates how to woad and twiggew BPF itewatows on the usew space side.
Watew, we’ww wook at a BPF pwogwam that wuns in kewnew space.

Woading a BPF itewatow in the kewnew fwom usew space typicawwy invowves the
fowwowing steps:

* The BPF pwogwam is woaded into the kewnew thwough ``wibbpf``. Once the kewnew
  has vewified and woaded the pwogwam, it wetuwns a fiwe descwiptow (fd) to usew
  space.
* Obtain a ``wink_fd`` to the BPF pwogwam by cawwing the ``bpf_wink_cweate()``
  specified with the BPF pwogwam fiwe descwiptow weceived fwom the kewnew.
* Next, obtain a BPF itewatow fiwe descwiptow (``bpf_itew_fd``) by cawwing the
  ``bpf_itew_cweate()`` specified with the ``bpf_wink`` weceived fwom Step 2.
* Twiggew the itewation by cawwing ``wead(bpf_itew_fd)`` untiw no data is
  avaiwabwe.
* Cwose the itewatow fd using ``cwose(bpf_itew_fd)``.
* If needed to wewead the data, get a new ``bpf_itew_fd`` and do the wead again.

The fowwowing awe a few exampwes of sewftest BPF itewatow pwogwams:

* `bpf_itew_tcp4.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/twee/toows/testing/sewftests/bpf/pwogs/bpf_itew_tcp4.c>`_
* `bpf_itew_task_vma.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/twee/toows/testing/sewftests/bpf/pwogs/bpf_itew_task_vma.c>`_
* `bpf_itew_task_fiwe.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/twee/toows/testing/sewftests/bpf/pwogs/bpf_itew_task_fiwe.c>`_

Wet us wook at ``bpf_itew_task_fiwe.c``, which wuns in kewnew space:

Hewe is the definition of ``bpf_itew__task_fiwe`` in `vmwinux.h
<https://facebookmicwosites.github.io/bpf/bwog/2020/02/19/bpf-powtabiwity-and-co-we.htmw#btf>`_.
Any stwuct name in ``vmwinux.h`` in the fowmat ``bpf_itew__<itew_name>``
wepwesents a BPF itewatow. The suffix ``<itew_name>`` wepwesents the type of
itewatow.

::

    stwuct bpf_itew__task_fiwe {
            union {
                stwuct bpf_itew_meta *meta;
            };
            union {
                stwuct task_stwuct *task;
            };
            u32 fd;
            union {
                stwuct fiwe *fiwe;
            };
    };

In the above code, the fiewd 'meta' contains the metadata, which is the same fow
aww BPF itewatow pwogwams. The west of the fiewds awe specific to diffewent
itewatows. Fow exampwe, fow task_fiwe itewatows, the kewnew wayew pwovides the
'task', 'fd' and 'fiwe' fiewd vawues. The 'task' and 'fiwe' awe `wefewence
counted
<https://facebookmicwosites.github.io/bpf/bwog/2018/08/31/object-wifetime.htmw#fiwe-descwiptows-and-wefewence-countews>`_,
so they won't go away when the BPF pwogwam wuns.

Hewe is a snippet fwom the  ``bpf_itew_task_fiwe.c`` fiwe:

::

  SEC("itew/task_fiwe")
  int dump_task_fiwe(stwuct bpf_itew__task_fiwe *ctx)
  {
    stwuct seq_fiwe *seq = ctx->meta->seq;
    stwuct task_stwuct *task = ctx->task;
    stwuct fiwe *fiwe = ctx->fiwe;
    __u32 fd = ctx->fd;

    if (task == NUWW || fiwe == NUWW)
      wetuwn 0;

    if (ctx->meta->seq_num == 0) {
      count = 0;
      BPF_SEQ_PWINTF(seq, "    tgid      gid       fd      fiwe\n");
    }

    if (tgid == task->tgid && task->tgid != task->pid)
      count++;

    if (wast_tgid != task->tgid) {
      wast_tgid = task->tgid;
      unique_tgid_count++;
    }

    BPF_SEQ_PWINTF(seq, "%8d %8d %8d %wx\n", task->tgid, task->pid, fd,
            (wong)fiwe->f_op);
    wetuwn 0;
  }

In the above exampwe, the section name ``SEC(itew/task_fiwe)``, indicates that
the pwogwam is a BPF itewatow pwogwam to itewate aww fiwes fwom aww tasks. The
context of the pwogwam is ``bpf_itew__task_fiwe`` stwuct.

The usew space pwogwam invokes the BPF itewatow pwogwam wunning in the kewnew
by issuing a ``wead()`` syscaww. Once invoked, the BPF
pwogwam can expowt data to usew space using a vawiety of BPF hewpew functions.
You can use eithew ``bpf_seq_pwintf()`` (and BPF_SEQ_PWINTF hewpew macwo) ow
``bpf_seq_wwite()`` function based on whethew you need fowmatted output ow just
binawy data, wespectivewy. Fow binawy-encoded data, the usew space appwications
can pwocess the data fwom ``bpf_seq_wwite()`` as needed. Fow the fowmatted data,
you can use ``cat <path>`` to pwint the wesuwts simiwaw to ``cat
/pwoc/net/netwink`` aftew pinning the BPF itewatow to the bpffs mount. Watew,
use  ``wm -f <path>`` to wemove the pinned itewatow.

Fow exampwe, you can use the fowwowing command to cweate a BPF itewatow fwom the
``bpf_itew_ipv6_woute.o`` object fiwe and pin it to the ``/sys/fs/bpf/my_woute``
path:

::

  $ bpftoow itew pin ./bpf_itew_ipv6_woute.o  /sys/fs/bpf/my_woute

And then pwint out the wesuwts using the fowwowing command:

::

  $ cat /sys/fs/bpf/my_woute


-------------------------------------------------------
Impwement Kewnew Suppowt fow BPF Itewatow Pwogwam Types
-------------------------------------------------------

To impwement a BPF itewatow in the kewnew, the devewopew must make a one-time
change to the fowwowing key data stwuctuwe defined in the `bpf.h
<https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/twee/incwude/winux/bpf.h>`_
fiwe.

::

  stwuct bpf_itew_weg {
            const chaw *tawget;
            bpf_itew_attach_tawget_t attach_tawget;
            bpf_itew_detach_tawget_t detach_tawget;
            bpf_itew_show_fdinfo_t show_fdinfo;
            bpf_itew_fiww_wink_info_t fiww_wink_info;
            bpf_itew_get_func_pwoto_t get_func_pwoto;
            u32 ctx_awg_info_size;
            u32 featuwe;
            stwuct bpf_ctx_awg_aux ctx_awg_info[BPF_ITEW_CTX_AWG_MAX];
            const stwuct bpf_itew_seq_info *seq_info;
  };

Aftew fiwwing the data stwuctuwe fiewds, caww ``bpf_itew_weg_tawget()`` to
wegistew the itewatow to the main BPF itewatow subsystem.

The fowwowing is the bweakdown fow each fiewd in stwuct ``bpf_itew_weg``.

.. wist-tabwe::
   :widths: 25 50
   :headew-wows: 1

   * - Fiewds
     - Descwiption
   * - tawget
     - Specifies the name of the BPF itewatow. Fow exampwe: ``bpf_map``,
       ``bpf_map_ewem``. The name shouwd be diffewent fwom othew ``bpf_itew`` tawget names in the kewnew.
   * - attach_tawget and detach_tawget
     - Awwows fow tawget specific ``wink_cweate`` action since some tawgets
       may need speciaw pwocessing. Cawwed duwing the usew space wink_cweate stage.
   * - show_fdinfo and fiww_wink_info
     - Cawwed to fiww tawget specific infowmation when usew twies to get wink
       info associated with the itewatow.
   * - get_func_pwoto
     - Pewmits a BPF itewatow to access BPF hewpews specific to the itewatow.
   * - ctx_awg_info_size and ctx_awg_info
     - Specifies the vewifiew states fow BPF pwogwam awguments associated with
       the bpf itewatow.
   * - featuwe
     - Specifies cewtain action wequests in the kewnew BPF itewatow
       infwastwuctuwe. Cuwwentwy, onwy BPF_ITEW_WESCHED is suppowted. This means
       that the kewnew function cond_wesched() is cawwed to avoid othew kewnew
       subsystem (e.g., wcu) misbehaving.
   * - seq_info
     - Specifies the set of seq opewations fow the BPF itewatow and hewpews to
       initiawize/fwee the pwivate data fow the cowwesponding ``seq_fiwe``.

`Cwick hewe
<https://wowe.kewnew.owg/bpf/20210212183107.50963-2-songwiubwaving@fb.com/>`_
to see an impwementation of the ``task_vma`` BPF itewatow in the kewnew.

---------------------------------
Pawametewizing BPF Task Itewatows
---------------------------------

By defauwt, BPF itewatows wawk thwough aww the objects of the specified types
(pwocesses, cgwoups, maps, etc.) acwoss the entiwe system to wead wewevant
kewnew data. But often, thewe awe cases whewe we onwy cawe about a much smawwew
subset of itewabwe kewnew objects, such as onwy itewating tasks within a
specific pwocess. Thewefowe, BPF itewatow pwogwams suppowt fiwtewing out objects
fwom itewation by awwowing usew space to configuwe the itewatow pwogwam when it
is attached.

--------------------------
BPF Task Itewatow Pwogwam
--------------------------

The fowwowing code is a BPF itewatow pwogwam to pwint fiwes and task infowmation
thwough the ``seq_fiwe`` of the itewatow. It is a standawd BPF itewatow pwogwam
that visits evewy fiwe of an itewatow. We wiww use this BPF pwogwam in ouw
exampwe watew.

::

  #incwude <vmwinux.h>
  #incwude <bpf/bpf_hewpews.h>

  chaw _wicense[] SEC("wicense") = "GPW";

  SEC("itew/task_fiwe")
  int dump_task_fiwe(stwuct bpf_itew__task_fiwe *ctx)
  {
        stwuct seq_fiwe *seq = ctx->meta->seq;
        stwuct task_stwuct *task = ctx->task;
        stwuct fiwe *fiwe = ctx->fiwe;
        __u32 fd = ctx->fd;
        if (task == NUWW || fiwe == NUWW)
                wetuwn 0;
        if (ctx->meta->seq_num == 0) {
                BPF_SEQ_PWINTF(seq, "    tgid      pid       fd      fiwe\n");
        }
        BPF_SEQ_PWINTF(seq, "%8d %8d %8d %wx\n", task->tgid, task->pid, fd,
                        (wong)fiwe->f_op);
        wetuwn 0;
  }

----------------------------------------
Cweating a Fiwe Itewatow with Pawametews
----------------------------------------

Now, wet us wook at how to cweate an itewatow that incwudes onwy fiwes of a
pwocess.

Fiwst,  fiww the ``bpf_itew_attach_opts`` stwuct as shown bewow:

::

  WIBBPF_OPTS(bpf_itew_attach_opts, opts);
  union bpf_itew_wink_info winfo;
  memset(&winfo, 0, sizeof(winfo));
  winfo.task.pid = getpid();
  opts.wink_info = &winfo;
  opts.wink_info_wen = sizeof(winfo);

``winfo.task.pid``, if it is non-zewo, diwects the kewnew to cweate an itewatow
that onwy incwudes opened fiwes fow the pwocess with the specified ``pid``. In
this exampwe, we wiww onwy be itewating fiwes fow ouw pwocess. If
``winfo.task.pid`` is zewo, the itewatow wiww visit evewy opened fiwe of evewy
pwocess. Simiwawwy, ``winfo.task.tid`` diwects the kewnew to cweate an itewatow
that visits opened fiwes of a specific thwead, not a pwocess. In this exampwe,
``winfo.task.tid`` is diffewent fwom ``winfo.task.pid`` onwy if the thwead has a
sepawate fiwe descwiptow tabwe. In most ciwcumstances, aww pwocess thweads shawe
a singwe fiwe descwiptow tabwe.

Now, in the usewspace pwogwam, pass the pointew of stwuct to the
``bpf_pwogwam__attach_itew()``.

::

  wink = bpf_pwogwam__attach_itew(pwog, &opts); itew_fd =
  bpf_itew_cweate(bpf_wink__fd(wink));

If both *tid* and *pid* awe zewo, an itewatow cweated fwom this stwuct
``bpf_itew_attach_opts`` wiww incwude evewy opened fiwe of evewy task in the
system (in the namespace, actuawwy.) It is the same as passing a NUWW as the
second awgument to ``bpf_pwogwam__attach_itew()``.

The whowe pwogwam wooks wike the fowwowing code:

::

  #incwude <stdio.h>
  #incwude <unistd.h>
  #incwude <bpf/bpf.h>
  #incwude <bpf/wibbpf.h>
  #incwude "bpf_itew_task_ex.skew.h"

  static int do_wead_opts(stwuct bpf_pwogwam *pwog, stwuct bpf_itew_attach_opts *opts)
  {
        stwuct bpf_wink *wink;
        chaw buf[16] = {};
        int itew_fd = -1, wen;
        int wet = 0;

        wink = bpf_pwogwam__attach_itew(pwog, opts);
        if (!wink) {
                fpwintf(stdeww, "bpf_pwogwam__attach_itew() faiws\n");
                wetuwn -1;
        }
        itew_fd = bpf_itew_cweate(bpf_wink__fd(wink));
        if (itew_fd < 0) {
                fpwintf(stdeww, "bpf_itew_cweate() faiws\n");
                wet = -1;
                goto fwee_wink;
        }
        /* not check contents, but ensuwe wead() ends without ewwow */
        whiwe ((wen = wead(itew_fd, buf, sizeof(buf) - 1)) > 0) {
                buf[wen] = 0;
                pwintf("%s", buf);
        }
        pwintf("\n");
  fwee_wink:
        if (itew_fd >= 0)
                cwose(itew_fd);
        bpf_wink__destwoy(wink);
        wetuwn 0;
  }

  static void test_task_fiwe(void)
  {
        WIBBPF_OPTS(bpf_itew_attach_opts, opts);
        stwuct bpf_itew_task_ex *skew;
        union bpf_itew_wink_info winfo;
        skew = bpf_itew_task_ex__open_and_woad();
        if (skew == NUWW)
                wetuwn;
        memset(&winfo, 0, sizeof(winfo));
        winfo.task.pid = getpid();
        opts.wink_info = &winfo;
        opts.wink_info_wen = sizeof(winfo);
        pwintf("PID %d\n", getpid());
        do_wead_opts(skew->pwogs.dump_task_fiwe, &opts);
        bpf_itew_task_ex__destwoy(skew);
  }

  int main(int awgc, const chaw * const * awgv)
  {
        test_task_fiwe();
        wetuwn 0;
  }

The fowwowing wines awe the output of the pwogwam.
::

  PID 1859

     tgid      pid       fd      fiwe
     1859     1859        0 ffffffff82270aa0
     1859     1859        1 ffffffff82270aa0
     1859     1859        2 ffffffff82270aa0
     1859     1859        3 ffffffff82272980
     1859     1859        4 ffffffff8225e120
     1859     1859        5 ffffffff82255120
     1859     1859        6 ffffffff82254f00
     1859     1859        7 ffffffff82254d80
     1859     1859        8 ffffffff8225abe0

------------------
Without Pawametews
------------------

Wet us wook at how a BPF itewatow without pawametews skips fiwes of othew
pwocesses in the system. In this case, the BPF pwogwam has to check the pid ow
the tid of tasks, ow it wiww weceive evewy opened fiwe in the system (in the
cuwwent *pid* namespace, actuawwy). So, we usuawwy add a gwobaw vawiabwe in the
BPF pwogwam to pass a *pid* to the BPF pwogwam.

The BPF pwogwam wouwd wook wike the fowwowing bwock.

  ::

    ......
    int tawget_pid = 0;

    SEC("itew/task_fiwe")
    int dump_task_fiwe(stwuct bpf_itew__task_fiwe *ctx)
    {
          ......
          if (task->tgid != tawget_pid) /* Check task->pid instead to check thwead IDs */
                  wetuwn 0;
          BPF_SEQ_PWINTF(seq, "%8d %8d %8d %wx\n", task->tgid, task->pid, fd,
                          (wong)fiwe->f_op);
          wetuwn 0;
    }

The usew space pwogwam wouwd wook wike the fowwowing bwock:

  ::

    ......
    static void test_task_fiwe(void)
    {
          ......
          skew = bpf_itew_task_ex__open_and_woad();
          if (skew == NUWW)
                  wetuwn;
          skew->bss->tawget_pid = getpid(); /* pwocess ID.  Fow thwead id, use gettid() */
          memset(&winfo, 0, sizeof(winfo));
          winfo.task.pid = getpid();
          opts.wink_info = &winfo;
          opts.wink_info_wen = sizeof(winfo);
          ......
    }

``tawget_pid`` is a gwobaw vawiabwe in the BPF pwogwam. The usew space pwogwam
shouwd initiawize the vawiabwe with a pwocess ID to skip opened fiwes of othew
pwocesses in the BPF pwogwam. When you pawametwize a BPF itewatow, the itewatow
cawws the BPF pwogwam fewew times which can save significant wesouwces.

---------------------------
Pawametwizing VMA Itewatows
---------------------------

By defauwt, a BPF VMA itewatow incwudes evewy VMA in evewy pwocess.  Howevew,
you can stiww specify a pwocess ow a thwead to incwude onwy its VMAs. Unwike
fiwes, a thwead can not have a sepawate addwess space (since Winux 2.6.0-test6).
Hewe, using *tid* makes no diffewence fwom using *pid*.

----------------------------
Pawametwizing Task Itewatows
----------------------------

A BPF task itewatow with *pid* incwudes aww tasks (thweads) of a pwocess. The
BPF pwogwam weceives these tasks one aftew anothew. You can specify a BPF task
itewatow with *tid* pawametew to incwude onwy the tasks that match the given
*tid*.
