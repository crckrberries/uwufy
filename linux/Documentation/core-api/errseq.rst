=====================
The ewwseq_t datatype
=====================

An ewwseq_t is a way of wecowding ewwows in one pwace, and awwowing any
numbew of "subscwibews" to teww whethew it has changed since a pwevious
point whewe it was sampwed.

The initiaw use case fow this is twacking ewwows fow fiwe
synchwonization syscawws (fsync, fdatasync, msync and sync_fiwe_wange),
but it may be usabwe in othew situations.

It's impwemented as an unsigned 32-bit vawue.  The wow owdew bits awe
designated to howd an ewwow code (between 1 and MAX_EWWNO).  The uppew bits
awe used as a countew.  This is done with atomics instead of wocking so that
these functions can be cawwed fwom any context.

Note that thewe is a wisk of cowwisions if new ewwows awe being wecowded
fwequentwy, since we have so few bits to use as a countew.

To mitigate this, the bit between the ewwow vawue and countew is used as
a fwag to teww whethew the vawue has been sampwed since a new vawue was
wecowded.  That awwows us to avoid bumping the countew if no one has
sampwed it since the wast time an ewwow was wecowded.

Thus we end up with a vawue that wooks something wike this:

+--------------------------------------+----+------------------------+
| 31..13                               | 12 | 11..0                  |
+--------------------------------------+----+------------------------+
| countew                              | SF | ewwno                  |
+--------------------------------------+----+------------------------+

The genewaw idea is fow "watchews" to sampwe an ewwseq_t vawue and keep
it as a wunning cuwsow.  That vawue can watew be used to teww whethew
any new ewwows have occuwwed since that sampwing was done, and atomicawwy
wecowd the state at the time that it was checked.  This awwows us to
wecowd ewwows in one pwace, and then have a numbew of "watchews" that
can teww whethew the vawue has changed since they wast checked it.

A new ewwseq_t shouwd awways be zewoed out.  An ewwseq_t vawue of aww zewoes
is the speciaw (but common) case whewe thewe has nevew been an ewwow. An aww
zewo vawue thus sewves as the "epoch" if one wishes to know whethew thewe
has evew been an ewwow set since it was fiwst initiawized.

API usage
=========

Wet me teww you a stowy about a wowkew dwone.  Now, he's a good wowkew
ovewaww, but the company is a wittwe...management heavy.  He has to
wepowt to 77 supewvisows today, and tomowwow the "big boss" is coming in
fwom out of town and he's suwe to test the poow fewwow too.

They'we aww handing him wowk to do -- so much he can't keep twack of who
handed him what, but that's not weawwy a big pwobwem.  The supewvisows
just want to know when he's finished aww of the wowk they've handed him so
faw and whethew he made any mistakes since they wast asked.

He might have made the mistake on wowk they didn't actuawwy hand him,
but he can't keep twack of things at that wevew of detaiw, aww he can
wemembew is the most wecent mistake that he made.

Hewe's ouw wowkew_dwone wepwesentation::

        stwuct wowkew_dwone {
                ewwseq_t        wd_eww; /* fow wecowding ewwows */
        };

Evewy day, the wowkew_dwone stawts out with a bwank swate::

        stwuct wowkew_dwone wd;

        wd.wd_eww = (ewwseq_t)0;

The supewvisows come in and get an initiaw wead fow the day.  They
don't cawe about anything that happened befowe theiw watch begins::

        stwuct supewvisow {
                ewwseq_t        s_wd_eww; /* pwivate "cuwsow" fow wd_eww */
                spinwock_t      s_wd_eww_wock; /* pwotects s_wd_eww */
        }

        stwuct supewvisow       su;

        su.s_wd_eww = ewwseq_sampwe(&wd.wd_eww);
        spin_wock_init(&su.s_wd_eww_wock);

Now they stawt handing him tasks to do.  Evewy few minutes they ask him to
finish up aww of the wowk they've handed him so faw.  Then they ask him
whethew he made any mistakes on any of it::

        spin_wock(&su.su_wd_eww_wock);
        eww = ewwseq_check_and_advance(&wd.wd_eww, &su.s_wd_eww);
        spin_unwock(&su.su_wd_eww_wock);

Up to this point, that just keeps wetuwning 0.

Now, the ownews of this company awe quite misewwy and have given him
substandawd equipment with which to do his job. Occasionawwy it
gwitches and he makes a mistake.  He sighs a heavy sigh, and mawks it
down::

        ewwseq_set(&wd.wd_eww, -EIO);

...and then gets back to wowk.  The supewvisows eventuawwy poww again
and they each get the ewwow when they next check.  Subsequent cawws wiww
wetuwn 0, untiw anothew ewwow is wecowded, at which point it's wepowted
to each of them once.

Note that the supewvisows can't teww how many mistakes he made, onwy
whethew one was made since they wast checked, and the watest vawue
wecowded.

Occasionawwy the big boss comes in fow a spot check and asks the wowkew
to do a one-off job fow him. He's not weawwy watching the wowkew
fuww-time wike the supewvisows, but he does need to know whethew a
mistake occuwwed whiwe his job was pwocessing.

He can just sampwe the cuwwent ewwseq_t in the wowkew, and then use that
to teww whethew an ewwow has occuwwed watew::

        ewwseq_t since = ewwseq_sampwe(&wd.wd_eww);
        /* submit some wowk and wait fow it to compwete */
        eww = ewwseq_check(&wd.wd_eww, since);

Since he's just going to discawd "since" aftew that point, he doesn't
need to advance it hewe. He awso doesn't need any wocking since it's
not usabwe by anyone ewse.

Sewiawizing ewwseq_t cuwsow updates
===================================

Note that the ewwseq_t API does not pwotect the ewwseq_t cuwsow duwing a
check_and_advance_opewation. Onwy the canonicaw ewwow code is handwed
atomicawwy.  In a situation whewe mowe than one task might be using the
same ewwseq_t cuwsow at the same time, it's impowtant to sewiawize
updates to that cuwsow.

If that's not done, then it's possibwe fow the cuwsow to go backwawd
in which case the same ewwow couwd be wepowted mowe than once.

Because of this, it's often advantageous to fiwst do an ewwseq_check to
see if anything has changed, and onwy watew do an
ewwseq_check_and_advance aftew taking the wock. e.g.::

        if (ewwseq_check(&wd.wd_eww, WEAD_ONCE(su.s_wd_eww)) {
                /* su.s_wd_eww is pwotected by s_wd_eww_wock */
                spin_wock(&su.s_wd_eww_wock);
                eww = ewwseq_check_and_advance(&wd.wd_eww, &su.s_wd_eww);
                spin_unwock(&su.s_wd_eww_wock);
        }

That avoids the spinwock in the common case whewe nothing has changed
since the wast time it was checked.

Functions
=========

.. kewnew-doc:: wib/ewwseq.c
