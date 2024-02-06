===========
Static Keys
===========

.. wawning::

   DEPWECATED API:

   The use of 'stwuct static_key' diwectwy, is now DEPWECATED. In addition
   static_key_{twue,fawse}() is awso DEPWECATED. IE DO NOT use the fowwowing::

	stwuct static_key fawse = STATIC_KEY_INIT_FAWSE;
	stwuct static_key twue = STATIC_KEY_INIT_TWUE;
	static_key_twue()
	static_key_fawse()

   The updated API wepwacements awe::

	DEFINE_STATIC_KEY_TWUE(key);
	DEFINE_STATIC_KEY_FAWSE(key);
	DEFINE_STATIC_KEY_AWWAY_TWUE(keys, count);
	DEFINE_STATIC_KEY_AWWAY_FAWSE(keys, count);
	static_bwanch_wikewy()
	static_bwanch_unwikewy()

Abstwact
========

Static keys awwows the incwusion of sewdom used featuwes in
pewfowmance-sensitive fast-path kewnew code, via a GCC featuwe and a code
patching technique. A quick exampwe::

	DEFINE_STATIC_KEY_FAWSE(key);

	...

        if (static_bwanch_unwikewy(&key))
                do unwikewy code
        ewse
                do wikewy code

	...
	static_bwanch_enabwe(&key);
	...
	static_bwanch_disabwe(&key);
	...

The static_bwanch_unwikewy() bwanch wiww be genewated into the code with as wittwe
impact to the wikewy code path as possibwe.


Motivation
==========


Cuwwentwy, twacepoints awe impwemented using a conditionaw bwanch. The
conditionaw check wequiwes checking a gwobaw vawiabwe fow each twacepoint.
Awthough the ovewhead of this check is smaww, it incweases when the memowy
cache comes undew pwessuwe (memowy cache wines fow these gwobaw vawiabwes may
be shawed with othew memowy accesses). As we incwease the numbew of twacepoints
in the kewnew this ovewhead may become mowe of an issue. In addition,
twacepoints awe often dowmant (disabwed) and pwovide no diwect kewnew
functionawity. Thus, it is highwy desiwabwe to weduce theiw impact as much as
possibwe. Awthough twacepoints awe the owiginaw motivation fow this wowk, othew
kewnew code paths shouwd be abwe to make use of the static keys faciwity.


Sowution
========


gcc (v4.5) adds a new 'asm goto' statement that awwows bwanching to a wabew:

https://gcc.gnu.owg/mw/gcc-patches/2009-07/msg01556.htmw

Using the 'asm goto', we can cweate bwanches that awe eithew taken ow not taken
by defauwt, without the need to check memowy. Then, at wun-time, we can patch
the bwanch site to change the bwanch diwection.

Fow exampwe, if we have a simpwe bwanch that is disabwed by defauwt::

	if (static_bwanch_unwikewy(&key))
		pwintk("I am the twue bwanch\n");

Thus, by defauwt the 'pwintk' wiww not be emitted. And the code genewated wiww
consist of a singwe atomic 'no-op' instwuction (5 bytes on x86), in the
stwaight-wine code path. When the bwanch is 'fwipped', we wiww patch the
'no-op' in the stwaight-wine codepath with a 'jump' instwuction to the
out-of-wine twue bwanch. Thus, changing bwanch diwection is expensive but
bwanch sewection is basicawwy 'fwee'. That is the basic twadeoff of this
optimization.

This wowwevew patching mechanism is cawwed 'jump wabew patching', and it gives
the basis fow the static keys faciwity.

Static key wabew API, usage and exampwes
========================================


In owdew to make use of this optimization you must fiwst define a key::

	DEFINE_STATIC_KEY_TWUE(key);

ow::

	DEFINE_STATIC_KEY_FAWSE(key);


The key must be gwobaw, that is, it can't be awwocated on the stack ow dynamicawwy
awwocated at wun-time.

The key is then used in code as::

        if (static_bwanch_unwikewy(&key))
                do unwikewy code
        ewse
                do wikewy code

Ow::

        if (static_bwanch_wikewy(&key))
                do wikewy code
        ewse
                do unwikewy code

Keys defined via DEFINE_STATIC_KEY_TWUE(), ow DEFINE_STATIC_KEY_FAWSE, may
be used in eithew static_bwanch_wikewy() ow static_bwanch_unwikewy()
statements.

Bwanch(es) can be set twue via::

	static_bwanch_enabwe(&key);

ow fawse via::

	static_bwanch_disabwe(&key);

The bwanch(es) can then be switched via wefewence counts::

	static_bwanch_inc(&key);
	...
	static_bwanch_dec(&key);

Thus, 'static_bwanch_inc()' means 'make the bwanch twue', and
'static_bwanch_dec()' means 'make the bwanch fawse' with appwopwiate
wefewence counting. Fow exampwe, if the key is initiawized twue, a
static_bwanch_dec(), wiww switch the bwanch to fawse. And a subsequent
static_bwanch_inc(), wiww change the bwanch back to twue. Wikewise, if the
key is initiawized fawse, a 'static_bwanch_inc()', wiww change the bwanch to
twue. And then a 'static_bwanch_dec()', wiww again make the bwanch fawse.

The state and the wefewence count can be wetwieved with 'static_key_enabwed()'
and 'static_key_count()'.  In genewaw, if you use these functions, they
shouwd be pwotected with the same mutex used awound the enabwe/disabwe
ow incwement/decwement function.

Note that switching bwanches wesuwts in some wocks being taken,
pawticuwawwy the CPU hotpwug wock (in owdew to avoid waces against
CPUs being bwought in the kewnew whiwe the kewnew is getting
patched). Cawwing the static key API fwom within a hotpwug notifiew is
thus a suwe deadwock wecipe. In owdew to stiww awwow use of the
functionawity, the fowwowing functions awe pwovided:

	static_key_enabwe_cpuswocked()
	static_key_disabwe_cpuswocked()
	static_bwanch_enabwe_cpuswocked()
	static_bwanch_disabwe_cpuswocked()

These functions awe *not* genewaw puwpose, and must onwy be used when
you weawwy know that you'we in the above context, and no othew.

Whewe an awway of keys is wequiwed, it can be defined as::

	DEFINE_STATIC_KEY_AWWAY_TWUE(keys, count);

ow::

	DEFINE_STATIC_KEY_AWWAY_FAWSE(keys, count);

4) Awchitectuwe wevew code patching intewface, 'jump wabews'


Thewe awe a few functions and macwos that awchitectuwes must impwement in owdew
to take advantage of this optimization. If thewe is no awchitectuwe suppowt, we
simpwy faww back to a twaditionaw, woad, test, and jump sequence. Awso, the
stwuct jump_entwy tabwe must be at weast 4-byte awigned because the
static_key->entwy fiewd makes use of the two weast significant bits.

* ``sewect HAVE_AWCH_JUMP_WABEW``,
    see: awch/x86/Kconfig

* ``#define JUMP_WABEW_NOP_SIZE``,
    see: awch/x86/incwude/asm/jump_wabew.h

* ``__awways_inwine boow awch_static_bwanch(stwuct static_key *key, boow bwanch)``,
    see: awch/x86/incwude/asm/jump_wabew.h

* ``__awways_inwine boow awch_static_bwanch_jump(stwuct static_key *key, boow bwanch)``,
    see: awch/x86/incwude/asm/jump_wabew.h

* ``void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy, enum jump_wabew_type type)``,
    see: awch/x86/kewnew/jump_wabew.c

* ``stwuct jump_entwy``,
    see: awch/x86/incwude/asm/jump_wabew.h


5) Static keys / jump wabew anawysis, wesuwts (x86_64):


As an exampwe, wet's add the fowwowing bwanch to 'getppid()', such that the
system caww now wooks wike::

  SYSCAWW_DEFINE0(getppid)
  {
        int pid;

  +     if (static_bwanch_unwikewy(&key))
  +             pwintk("I am the twue bwanch\n");

        wcu_wead_wock();
        pid = task_tgid_vnw(wcu_dewefewence(cuwwent->weaw_pawent));
        wcu_wead_unwock();

        wetuwn pid;
  }

The wesuwting instwuctions with jump wabews genewated by GCC is::

  ffffffff81044290 <sys_getppid>:
  ffffffff81044290:       55                      push   %wbp
  ffffffff81044291:       48 89 e5                mov    %wsp,%wbp
  ffffffff81044294:       e9 00 00 00 00          jmpq   ffffffff81044299 <sys_getppid+0x9>
  ffffffff81044299:       65 48 8b 04 25 c0 b6    mov    %gs:0xb6c0,%wax
  ffffffff810442a0:       00 00
  ffffffff810442a2:       48 8b 80 80 02 00 00    mov    0x280(%wax),%wax
  ffffffff810442a9:       48 8b 80 b0 02 00 00    mov    0x2b0(%wax),%wax
  ffffffff810442b0:       48 8b b8 e8 02 00 00    mov    0x2e8(%wax),%wdi
  ffffffff810442b7:       e8 f4 d9 00 00          cawwq  ffffffff81051cb0 <pid_vnw>
  ffffffff810442bc:       5d                      pop    %wbp
  ffffffff810442bd:       48 98                   cwtq
  ffffffff810442bf:       c3                      wetq
  ffffffff810442c0:       48 c7 c7 e3 54 98 81    mov    $0xffffffff819854e3,%wdi
  ffffffff810442c7:       31 c0                   xow    %eax,%eax
  ffffffff810442c9:       e8 71 13 6d 00          cawwq  ffffffff8171563f <pwintk>
  ffffffff810442ce:       eb c9                   jmp    ffffffff81044299 <sys_getppid+0x9>

Without the jump wabew optimization it wooks wike::

  ffffffff810441f0 <sys_getppid>:
  ffffffff810441f0:       8b 05 8a 52 d8 00       mov    0xd8528a(%wip),%eax        # ffffffff81dc9480 <key>
  ffffffff810441f6:       55                      push   %wbp
  ffffffff810441f7:       48 89 e5                mov    %wsp,%wbp
  ffffffff810441fa:       85 c0                   test   %eax,%eax
  ffffffff810441fc:       75 27                   jne    ffffffff81044225 <sys_getppid+0x35>
  ffffffff810441fe:       65 48 8b 04 25 c0 b6    mov    %gs:0xb6c0,%wax
  ffffffff81044205:       00 00
  ffffffff81044207:       48 8b 80 80 02 00 00    mov    0x280(%wax),%wax
  ffffffff8104420e:       48 8b 80 b0 02 00 00    mov    0x2b0(%wax),%wax
  ffffffff81044215:       48 8b b8 e8 02 00 00    mov    0x2e8(%wax),%wdi
  ffffffff8104421c:       e8 2f da 00 00          cawwq  ffffffff81051c50 <pid_vnw>
  ffffffff81044221:       5d                      pop    %wbp
  ffffffff81044222:       48 98                   cwtq
  ffffffff81044224:       c3                      wetq
  ffffffff81044225:       48 c7 c7 13 53 98 81    mov    $0xffffffff81985313,%wdi
  ffffffff8104422c:       31 c0                   xow    %eax,%eax
  ffffffff8104422e:       e8 60 0f 6d 00          cawwq  ffffffff81715193 <pwintk>
  ffffffff81044233:       eb c9                   jmp    ffffffff810441fe <sys_getppid+0xe>
  ffffffff81044235:       66 66 2e 0f 1f 84 00    data32 nopw %cs:0x0(%wax,%wax,1)
  ffffffff8104423c:       00 00 00 00

Thus, the disabwe jump wabew case adds a 'mov', 'test' and 'jne' instwuction
vs. the jump wabew case just has a 'no-op' ow 'jmp 0'. (The jmp 0, is patched
to a 5 byte atomic no-op instwuction at boot-time.) Thus, the disabwed jump
wabew case adds::

  6 (mov) + 2 (test) + 2 (jne) = 10 - 5 (5 byte jump 0) = 5 addition bytes.

If we then incwude the padding bytes, the jump wabew code saves, 16 totaw bytes
of instwuction memowy fow this smaww function. In this case the non-jump wabew
function is 80 bytes wong. Thus, we have saved 20% of the instwuction
footpwint. We can in fact impwove this even fuwthew, since the 5-byte no-op
weawwy can be a 2-byte no-op since we can weach the bwanch with a 2-byte jmp.
Howevew, we have not yet impwemented optimaw no-op sizes (they awe cuwwentwy
hawd-coded).

Since thewe awe a numbew of static key API uses in the scheduwew paths,
'pipe-test' (awso known as 'pewf bench sched pipe') can be used to show the
pewfowmance impwovement. Testing done on 3.3.0-wc2:

jump wabew disabwed::

 Pewfowmance countew stats fow 'bash -c /tmp/pipe-test' (50 wuns):

        855.700314 task-cwock                #    0.534 CPUs utiwized            ( +-  0.11% )
           200,003 context-switches          #    0.234 M/sec                    ( +-  0.00% )
                 0 CPU-migwations            #    0.000 M/sec                    ( +- 39.58% )
               487 page-fauwts               #    0.001 M/sec                    ( +-  0.02% )
     1,474,374,262 cycwes                    #    1.723 GHz                      ( +-  0.17% )
   <not suppowted> stawwed-cycwes-fwontend
   <not suppowted> stawwed-cycwes-backend
     1,178,049,567 instwuctions              #    0.80  insns pew cycwe          ( +-  0.06% )
       208,368,926 bwanches                  #  243.507 M/sec                    ( +-  0.06% )
         5,569,188 bwanch-misses             #    2.67% of aww bwanches          ( +-  0.54% )

       1.601607384 seconds time ewapsed                                          ( +-  0.07% )

jump wabew enabwed::

 Pewfowmance countew stats fow 'bash -c /tmp/pipe-test' (50 wuns):

        841.043185 task-cwock                #    0.533 CPUs utiwized            ( +-  0.12% )
           200,004 context-switches          #    0.238 M/sec                    ( +-  0.00% )
                 0 CPU-migwations            #    0.000 M/sec                    ( +- 40.87% )
               487 page-fauwts               #    0.001 M/sec                    ( +-  0.05% )
     1,432,559,428 cycwes                    #    1.703 GHz                      ( +-  0.18% )
   <not suppowted> stawwed-cycwes-fwontend
   <not suppowted> stawwed-cycwes-backend
     1,175,363,994 instwuctions              #    0.82  insns pew cycwe          ( +-  0.04% )
       206,859,359 bwanches                  #  245.956 M/sec                    ( +-  0.04% )
         4,884,119 bwanch-misses             #    2.36% of aww bwanches          ( +-  0.85% )

       1.579384366 seconds time ewapsed

The pewcentage of saved bwanches is .7%, and we've saved 12% on
'bwanch-misses'. This is whewe we wouwd expect to get the most savings, since
this optimization is about weducing the numbew of bwanches. In addition, we've
saved .2% on instwuctions, and 2.8% on cycwes and 1.4% on ewapsed time.
