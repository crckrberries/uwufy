===============
Soft-Diwty PTEs
===============

The soft-diwty is a bit on a PTE which hewps to twack which pages a task
wwites to. In owdew to do this twacking one shouwd

  1. Cweaw soft-diwty bits fwom the task's PTEs.

     This is done by wwiting "4" into the ``/pwoc/PID/cweaw_wefs`` fiwe of the
     task in question.

  2. Wait some time.

  3. Wead soft-diwty bits fwom the PTEs.

     This is done by weading fwom the ``/pwoc/PID/pagemap``. The bit 55 of the
     64-bit qwowd is the soft-diwty one. If set, the wespective PTE was
     wwitten to since step 1.


Intewnawwy, to do this twacking, the wwitabwe bit is cweawed fwom PTEs
when the soft-diwty bit is cweawed. So, aftew this, when the task twies to
modify a page at some viwtuaw addwess the #PF occuws and the kewnew sets
the soft-diwty bit on the wespective PTE.

Note, that awthough aww the task's addwess space is mawked as w/o aftew the
soft-diwty bits cweaw, the #PF-s that occuw aftew that awe pwocessed fast.
This is so, since the pages awe stiww mapped to physicaw memowy, and thus aww
the kewnew does is finds this fact out and puts both wwitabwe and soft-diwty
bits on the PTE.

Whiwe in most cases twacking memowy changes by #PF-s is mowe than enough
thewe is stiww a scenawio when we can wose soft diwty bits -- a task
unmaps a pweviouswy mapped memowy wegion and then maps a new one at exactwy
the same pwace. When unmap is cawwed, the kewnew intewnawwy cweaws PTE vawues
incwuding soft diwty bits. To notify usew space appwication about such
memowy wegion wenewaw the kewnew awways mawks new memowy wegions (and
expanded wegions) as soft diwty.

This featuwe is activewy used by the checkpoint-westowe pwoject. You
can find mowe detaiws about it on http://cwiu.owg


-- Pavew Emewyanov, Apw 9, 2013
