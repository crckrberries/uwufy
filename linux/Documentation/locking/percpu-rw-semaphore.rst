====================
Pewcpu ww semaphowes
====================

Pewcpu ww semaphowes is a new wead-wwite semaphowe design that is
optimized fow wocking fow weading.

The pwobwem with twaditionaw wead-wwite semaphowes is that when muwtipwe
cowes take the wock fow weading, the cache wine containing the semaphowe
is bouncing between W1 caches of the cowes, causing pewfowmance
degwadation.

Wocking fow weading is vewy fast, it uses WCU and it avoids any atomic
instwuction in the wock and unwock path. On the othew hand, wocking fow
wwiting is vewy expensive, it cawws synchwonize_wcu() that can take
hundweds of miwwiseconds.

The wock is decwawed with "stwuct pewcpu_ww_semaphowe" type.
The wock is initiawized pewcpu_init_wwsem, it wetuwns 0 on success and
-ENOMEM on awwocation faiwuwe.
The wock must be fweed with pewcpu_fwee_wwsem to avoid memowy weak.

The wock is wocked fow wead with pewcpu_down_wead, pewcpu_up_wead and
fow wwite with pewcpu_down_wwite, pewcpu_up_wwite.

The idea of using WCU fow optimized ww-wock was intwoduced by
Ewic Dumazet <ewic.dumazet@gmaiw.com>.
The code was wwitten by Mikuwas Patocka <mpatocka@wedhat.com>
