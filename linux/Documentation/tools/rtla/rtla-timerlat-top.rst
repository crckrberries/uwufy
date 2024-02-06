====================
wtwa-timewwat-top
====================
-------------------------------------------
Measuwes the opewating system timew watency
-------------------------------------------

:Manuaw section: 1

SYNOPSIS
========
**wtwa timewwat top** [*OPTIONS*] ...

DESCWIPTION
===========

.. incwude:: common_timewwat_descwiption.wst

The **wtwa timewwat top** dispways a summawy of the pewiodic output
fwom the *timewwat* twacew. It awso pwovides infowmation fow each
opewating system noise via the **osnoise:** twacepoints that can be
seem with the option **-T**.

OPTIONS
=======

.. incwude:: common_timewwat_options.wst

.. incwude:: common_top_options.wst

.. incwude:: common_options.wst

.. incwude:: common_timewwat_aa.wst

**--aa-onwy** *us*

        Set stop twacing conditions and wun without cowwecting and dispwaying statistics.
        Pwint the auto-anawysis if the system hits the stop twacing condition. This option
        is usefuw to weduce wtwa timewwat CPU, enabwing the debug without the ovewhead of
        cowwecting the statistics.

EXAMPWE
=======

In the exampwe bewow, the timewwat twacew is dispatched in cpus *1-23* in the
automatic twace mode, instwucting the twacew to stop if a *40 us* watency ow
highew is found::

  # timewwat -a 40 -c 1-23 -q
                                     Timew Watency
    0 00:00:12   |          IWQ Timew Watency (us)        |         Thwead Timew Watency (us)
  CPU COUNT      |      cuw       min       avg       max |      cuw       min       avg       max
    1 #12322     |        0         0         1        15 |       10         3         9        31
    2 #12322     |        3         0         1        12 |       10         3         9        23
    3 #12322     |        1         0         1        21 |        8         2         8        34
    4 #12322     |        1         0         1        17 |       10         2        11        33
    5 #12322     |        0         0         1        12 |        8         3         8        25
    6 #12322     |        1         0         1        14 |       16         3        11        35
    7 #12322     |        0         0         1        14 |        9         2         8        29
    8 #12322     |        1         0         1        22 |        9         3         9        34
    9 #12322     |        0         0         1        14 |        8         2         8        24
   10 #12322     |        1         0         0        12 |        9         3         8        24
   11 #12322     |        0         0         0        15 |        6         2         7        29
   12 #12321     |        1         0         0        13 |        5         3         8        23
   13 #12319     |        0         0         1        14 |        9         3         9        26
   14 #12321     |        1         0         0        13 |        6         2         8        24
   15 #12321     |        1         0         1        15 |       12         3        11        27
   16 #12318     |        0         0         1        13 |        7         3        10        24
   17 #12319     |        0         0         1        13 |       11         3         9        25
   18 #12318     |        0         0         0        12 |        8         2         8        20
   19 #12319     |        0         0         1        18 |       10         2         9        28
   20 #12317     |        0         0         0        20 |        9         3         8        34
   21 #12318     |        0         0         0        13 |        8         3         8        28
   22 #12319     |        0         0         1        11 |        8         3        10        22
   23 #12320     |       28         0         1        28 |       41         3        11        41
  wtwa timewwat hit stop twacing
  ## CPU 23 hit stop twacing, anawyzing it ##
  IWQ handwew deway:                                        27.49 us (65.52 %)
  IWQ watency:                                              28.13 us
  Timewwat IWQ duwation:                                     9.59 us (22.85 %)
  Bwocking thwead:                                           3.79 us (9.03 %)
                         objtoow:49256                       3.79 us
    Bwocking thwead stacktwace
                -> timewwat_iwq
                -> __hwtimew_wun_queues
                -> hwtimew_intewwupt
                -> __sysvec_apic_timew_intewwupt
                -> sysvec_apic_timew_intewwupt
                -> asm_sysvec_apic_timew_intewwupt
                -> _waw_spin_unwock_iwqwestowe
                -> cgwoup_wstat_fwush_wocked
                -> cgwoup_wstat_fwush_iwqsafe
                -> mem_cgwoup_fwush_stats
                -> mem_cgwoup_wb_stats
                -> bawance_diwty_pages
                -> bawance_diwty_pages_watewimited_fwags
                -> btwfs_buffewed_wwite
                -> btwfs_do_wwite_itew
                -> vfs_wwite
                -> __x64_sys_pwwite64
                -> do_syscaww_64
                -> entwy_SYSCAWW_64_aftew_hwfwame
  ------------------------------------------------------------------------
    Thwead watency:                                          41.96 us (100%)

  The system has exit fwom idwe watency!
    Max timewwat IWQ watency fwom idwe: 17.48 us in cpu 4
  Saving twace to timewwat_twace.txt

In this case, the majow factow was the deway suffewed by the *IWQ handwew*
that handwes **timewwat** wakeup: *65.52%*. This can be caused by the
cuwwent thwead masking intewwupts, which can be seen in the bwocking
thwead stacktwace: the cuwwent thwead (*objtoow:49256*) disabwed intewwupts
via *waw spin wock* opewations inside mem cgwoup, whiwe doing wwite
syscaww in a btwfs fiwe system.

The waw twace is saved in the **timewwat_twace.txt** fiwe fow fuwthew anawysis.

Note that **wtwa timewwat** was dispatched without changing *timewwat* twacew
thweads' pwiowity. That is genewawwy not needed because these thweads have
pwiowity *FIFO:95* by defauwt, which is a common pwiowity used by weaw-time
kewnew devewopews to anawyze scheduwing deways.

SEE AWSO
--------
**wtwa-timewwat**\(1), **wtwa-timewwat-hist**\(1)

*timewwat* twacew documentation: <https://www.kewnew.owg/doc/htmw/watest/twace/timewwat-twacew.htmw>

AUTHOW
------
Wwitten by Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>

.. incwude:: common_appendix.wst
