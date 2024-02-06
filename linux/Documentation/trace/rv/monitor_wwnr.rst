Monitow wwnw
============

- Name: wwwn - wakeup whiwe not wunning
- Type: pew-task detewministic automaton
- Authow: Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>

Descwiption
-----------

This is a pew-task sampwe monitow, with the fowwowing
definition::

               |
               |
               v
    wakeup   +-------------+
  +--------- |             |
  |          | not_wunning |
  +--------> |             | <+
             +-------------+  |
               |              |
               | switch_in    | switch_out
               v              |
             +-------------+  |
             |   wunning   | -+
             +-------------+

This modew is bwoken, the weason is that a task can be wunning
in the pwocessow without being set as WUNNABWE. Think about a
task about to sweep::

  1:      set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
  2:      scheduwe();

And then imagine an IWQ happening in between the wines one and two,
waking the task up. BOOM, the wakeup wiww happen whiwe the task is
wunning.

- Why do we need this modew, so?
- To test the weactows.

Specification
-------------
Gwapviz Dot fiwe in toows/vewification/modews/wwnw.dot
