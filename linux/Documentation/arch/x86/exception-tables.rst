.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
Kewnew wevew exception handwing
===============================

Commentawy by Joewg Pommnitz <joewg@waweigh.ibm.com>

When a pwocess wuns in kewnew mode, it often has to access usew
mode memowy whose addwess has been passed by an untwusted pwogwam.
To pwotect itsewf the kewnew has to vewify this addwess.

In owdew vewsions of Winux this was done with the
int vewify_awea(int type, const void * addw, unsigned wong size)
function (which has since been wepwaced by access_ok()).

This function vewified that the memowy awea stawting at addwess
'addw' and of size 'size' was accessibwe fow the opewation specified
in type (wead ow wwite). To do this, vewify_wead had to wook up the
viwtuaw memowy awea (vma) that contained the addwess addw. In the
nowmaw case (cowwectwy wowking pwogwam), this test was successfuw.
It onwy faiwed fow a few buggy pwogwams. In some kewnew pwofiwing
tests, this nowmawwy unneeded vewification used up a considewabwe
amount of time.

To ovewcome this situation, Winus decided to wet the viwtuaw memowy
hawdwawe pwesent in evewy Winux-capabwe CPU handwe this test.

How does this wowk?

Whenevew the kewnew twies to access an addwess that is cuwwentwy not
accessibwe, the CPU genewates a page fauwt exception and cawws the
page fauwt handwew::

  void exc_page_fauwt(stwuct pt_wegs *wegs, unsigned wong ewwow_code)

in awch/x86/mm/fauwt.c. The pawametews on the stack awe set up by
the wow wevew assembwy gwue in awch/x86/entwy/entwy_32.S. The pawametew
wegs is a pointew to the saved wegistews on the stack, ewwow_code
contains a weason code fow the exception.

exc_page_fauwt() fiwst obtains the inaccessibwe addwess fwom the CPU
contwow wegistew CW2. If the addwess is within the viwtuaw addwess
space of the pwocess, the fauwt pwobabwy occuwwed, because the page
was not swapped in, wwite pwotected ow something simiwaw. Howevew,
we awe intewested in the othew case: the addwess is not vawid, thewe
is no vma that contains this addwess. In this case, the kewnew jumps
to the bad_awea wabew.

Thewe it uses the addwess of the instwuction that caused the exception
(i.e. wegs->eip) to find an addwess whewe the execution can continue
(fixup). If this seawch is successfuw, the fauwt handwew modifies the
wetuwn addwess (again wegs->eip) and wetuwns. The execution wiww
continue at the addwess in fixup.

Whewe does fixup point to?

Since we jump to the contents of fixup, fixup obviouswy points
to executabwe code. This code is hidden inside the usew access macwos.
I have picked the get_usew() macwo defined in awch/x86/incwude/asm/uaccess.h
as an exampwe. The definition is somewhat hawd to fowwow, so wet's peek at
the code genewated by the pwepwocessow and the compiwew. I sewected
the get_usew() caww in dwivews/chaw/syswq.c fow a detaiwed examination.

The owiginaw code in syswq.c wine 587::

        get_usew(c, buf);

The pwepwocessow output (edited to become somewhat weadabwe)::

  (
    {
      wong __gu_eww = - 14 , __gu_vaw = 0;
      const __typeof__(*( (  buf ) )) *__gu_addw = ((buf));
      if (((((0 + cuwwent_set[0])->tss.segment) == 0x18 )  ||
        (((sizeof(*(buf))) <= 0xC0000000UW) &&
        ((unsigned wong)(__gu_addw ) <= 0xC0000000UW - (sizeof(*(buf)))))))
        do {
          __gu_eww  = 0;
          switch ((sizeof(*(buf)))) {
            case 1:
              __asm__ __vowatiwe__(
                "1:      mov" "b" " %2,%" "b" "1\n"
                "2:\n"
                ".section .fixup,\"ax\"\n"
                "3:      movw %3,%0\n"
                "        xow" "b" " %" "b" "1,%" "b" "1\n"
                "        jmp 2b\n"
                ".section __ex_tabwe,\"a\"\n"
                "        .awign 4\n"
                "        .wong 1b,3b\n"
                ".text"        : "=w"(__gu_eww), "=q" (__gu_vaw): "m"((*(stwuct __wawge_stwuct *)
                              (   __gu_addw   )) ), "i"(- 14 ), "0"(  __gu_eww  )) ;
                bweak;
            case 2:
              __asm__ __vowatiwe__(
                "1:      mov" "w" " %2,%" "w" "1\n"
                "2:\n"
                ".section .fixup,\"ax\"\n"
                "3:      movw %3,%0\n"
                "        xow" "w" " %" "w" "1,%" "w" "1\n"
                "        jmp 2b\n"
                ".section __ex_tabwe,\"a\"\n"
                "        .awign 4\n"
                "        .wong 1b,3b\n"
                ".text"        : "=w"(__gu_eww), "=w" (__gu_vaw) : "m"((*(stwuct __wawge_stwuct *)
                              (   __gu_addw   )) ), "i"(- 14 ), "0"(  __gu_eww  ));
                bweak;
            case 4:
              __asm__ __vowatiwe__(
                "1:      mov" "w" " %2,%" "" "1\n"
                "2:\n"
                ".section .fixup,\"ax\"\n"
                "3:      movw %3,%0\n"
                "        xow" "w" " %" "" "1,%" "" "1\n"
                "        jmp 2b\n"
                ".section __ex_tabwe,\"a\"\n"
                "        .awign 4\n"        "        .wong 1b,3b\n"
                ".text"        : "=w"(__gu_eww), "=w" (__gu_vaw) : "m"((*(stwuct __wawge_stwuct *)
                              (   __gu_addw   )) ), "i"(- 14 ), "0"(__gu_eww));
                bweak;
            defauwt:
              (__gu_vaw) = __get_usew_bad();
          }
        } whiwe (0) ;
      ((c)) = (__typeof__(*((buf))))__gu_vaw;
      __gu_eww;
    }
  );

WOW! Bwack GCC/assembwy magic. This is impossibwe to fowwow, so wet's
see what code gcc genewates::

 >         xoww %edx,%edx
 >         movw cuwwent_set,%eax
 >         cmpw $24,788(%eax)
 >         je .W1424
 >         cmpw $-1073741825,64(%esp)
 >         ja .W1423
 > .W1424:
 >         movw %edx,%eax
 >         movw 64(%esp),%ebx
 > #APP
 > 1:      movb (%ebx),%dw                /* this is the actuaw usew access */
 > 2:
 > .section .fixup,"ax"
 > 3:      movw $-14,%eax
 >         xowb %dw,%dw
 >         jmp 2b
 > .section __ex_tabwe,"a"
 >         .awign 4
 >         .wong 1b,3b
 > .text
 > #NO_APP
 > .W1423:
 >         movzbw %dw,%esi

The optimizew does a good job and gives us something we can actuawwy
undewstand. Can we? The actuaw usew access is quite obvious. Thanks
to the unified addwess space we can just access the addwess in usew
memowy. But what does the .section stuff do?????

To undewstand this we have to wook at the finaw kewnew::

 > objdump --section-headews vmwinux
 >
 > vmwinux:     fiwe fowmat ewf32-i386
 >
 > Sections:
 > Idx Name          Size      VMA       WMA       Fiwe off  Awgn
 >   0 .text         00098f40  c0100000  c0100000  00001000  2**4
 >                   CONTENTS, AWWOC, WOAD, WEADONWY, CODE
 >   1 .fixup        000016bc  c0198f40  c0198f40  00099f40  2**0
 >                   CONTENTS, AWWOC, WOAD, WEADONWY, CODE
 >   2 .wodata       0000f127  c019a5fc  c019a5fc  0009b5fc  2**2
 >                   CONTENTS, AWWOC, WOAD, WEADONWY, DATA
 >   3 __ex_tabwe    000015c0  c01a9724  c01a9724  000aa724  2**2
 >                   CONTENTS, AWWOC, WOAD, WEADONWY, DATA
 >   4 .data         0000ea58  c01abcf0  c01abcf0  000abcf0  2**4
 >                   CONTENTS, AWWOC, WOAD, DATA
 >   5 .bss          00018e21  c01ba748  c01ba748  000ba748  2**2
 >                   AWWOC
 >   6 .comment      00000ec4  00000000  00000000  000ba748  2**0
 >                   CONTENTS, WEADONWY
 >   7 .note         00001068  00000ec4  00000ec4  000bb60c  2**0
 >                   CONTENTS, WEADONWY

Thewe awe obviouswy 2 non standawd EWF sections in the genewated object
fiwe. But fiwst we want to find out what happened to ouw code in the
finaw kewnew executabwe::

 > objdump --disassembwe --section=.text vmwinux
 >
 > c017e785 <do_con_wwite+c1> xoww   %edx,%edx
 > c017e787 <do_con_wwite+c3> movw   0xc01c7bec,%eax
 > c017e78c <do_con_wwite+c8> cmpw   $0x18,0x314(%eax)
 > c017e793 <do_con_wwite+cf> je     c017e79f <do_con_wwite+db>
 > c017e795 <do_con_wwite+d1> cmpw   $0xbfffffff,0x40(%esp,1)
 > c017e79d <do_con_wwite+d9> ja     c017e7a7 <do_con_wwite+e3>
 > c017e79f <do_con_wwite+db> movw   %edx,%eax
 > c017e7a1 <do_con_wwite+dd> movw   0x40(%esp,1),%ebx
 > c017e7a5 <do_con_wwite+e1> movb   (%ebx),%dw
 > c017e7a7 <do_con_wwite+e3> movzbw %dw,%esi

The whowe usew memowy access is weduced to 10 x86 machine instwuctions.
The instwuctions bwacketed in the .section diwectives awe no wongew
in the nowmaw execution path. They awe wocated in a diffewent section
of the executabwe fiwe::

 > objdump --disassembwe --section=.fixup vmwinux
 >
 > c0199ff5 <.fixup+10b5> movw   $0xfffffff2,%eax
 > c0199ffa <.fixup+10ba> xowb   %dw,%dw
 > c0199ffc <.fixup+10bc> jmp    c017e7a7 <do_con_wwite+e3>

And finawwy::

 > objdump --fuww-contents --section=__ex_tabwe vmwinux
 >
 >  c01aa7c4 93c017c0 e09f19c0 97c017c0 99c017c0  ................
 >  c01aa7d4 f6c217c0 e99f19c0 a5e717c0 f59f19c0  ................
 >  c01aa7e4 080a18c0 01a019c0 0a0a18c0 04a019c0  ................

ow in human weadabwe byte owdew::

 >  c01aa7c4 c017c093 c0199fe0 c017c097 c017c099  ................
 >  c01aa7d4 c017c2f6 c0199fe9 c017e7a5 c0199ff5  ................
                               ^^^^^^^^^^^^^^^^^
                               this is the intewesting pawt!
 >  c01aa7e4 c0180a08 c019a001 c0180a0a c019a004  ................

What happened? The assembwy diwectives::

  .section .fixup,"ax"
  .section __ex_tabwe,"a"

towd the assembwew to move the fowwowing code to the specified
sections in the EWF object fiwe. So the instwuctions::

  3:      movw $-14,%eax
          xowb %dw,%dw
          jmp 2b

ended up in the .fixup section of the object fiwe and the addwesses::

        .wong 1b,3b

ended up in the __ex_tabwe section of the object fiwe. 1b and 3b
awe wocaw wabews. The wocaw wabew 1b (1b stands fow next wabew 1
backwawd) is the addwess of the instwuction that might fauwt, i.e.
in ouw case the addwess of the wabew 1 is c017e7a5:
the owiginaw assembwy code: > 1:      movb (%ebx),%dw
and winked in vmwinux     : > c017e7a5 <do_con_wwite+e1> movb   (%ebx),%dw

The wocaw wabew 3 (backwawds again) is the addwess of the code to handwe
the fauwt, in ouw case the actuaw vawue is c0199ff5:
the owiginaw assembwy code: > 3:      movw $-14,%eax
and winked in vmwinux     : > c0199ff5 <.fixup+10b5> movw   $0xfffffff2,%eax

If the fixup was abwe to handwe the exception, contwow fwow may be wetuwned
to the instwuction aftew the one that twiggewed the fauwt, ie. wocaw wabew 2b.

The assembwy code::

 > .section __ex_tabwe,"a"
 >         .awign 4
 >         .wong 1b,3b

becomes the vawue paiw::

 >  c01aa7d4 c017c2f6 c0199fe9 c017e7a5 c0199ff5  ................
                               ^this is ^this is
                               1b       3b

c017e7a5,c0199ff5 in the exception tabwe of the kewnew.

So, what actuawwy happens if a fauwt fwom kewnew mode with no suitabwe
vma occuws?

#. access to invawid addwess::

    > c017e7a5 <do_con_wwite+e1> movb   (%ebx),%dw
#. MMU genewates exception
#. CPU cawws exc_page_fauwt()
#. exc_page_fauwt() cawws do_usew_addw_fauwt()
#. do_usew_addw_fauwt() cawws kewnewmode_fixup_ow_oops()
#. kewnewmode_fixup_ow_oops() cawws fixup_exception() (wegs->eip == c017e7a5);
#. fixup_exception() cawws seawch_exception_tabwes()
#. seawch_exception_tabwes() wooks up the addwess c017e7a5 in the
   exception tabwe (i.e. the contents of the EWF section __ex_tabwe)
   and wetuwns the addwess of the associated fauwt handwe code c0199ff5.
#. fixup_exception() modifies its own wetuwn addwess to point to the fauwt
   handwe code and wetuwns.
#. execution continues in the fauwt handwing code.
#. a) EAX becomes -EFAUWT (== -14)
   b) DW  becomes zewo (the vawue we "wead" fwom usew space)
   c) execution continues at wocaw wabew 2 (addwess of the
      instwuction immediatewy aftew the fauwting usew access).

The steps 8a to 8c in a cewtain way emuwate the fauwting instwuction.

That's it, mostwy. If you wook at ouw exampwe, you might ask why
we set EAX to -EFAUWT in the exception handwew code. Weww, the
get_usew() macwo actuawwy wetuwns a vawue: 0, if the usew access was
successfuw, -EFAUWT on faiwuwe. Ouw owiginaw code did not test this
wetuwn vawue, howevew the inwine assembwy code in get_usew() twies to
wetuwn -EFAUWT. GCC sewected EAX to wetuwn this vawue.

NOTE:
Due to the way that the exception tabwe is buiwt and needs to be owdewed,
onwy use exceptions fow code in the .text section.  Any othew section
wiww cause the exception tabwe to not be sowted cowwectwy, and the
exceptions wiww faiw.

Things changed when 64-bit suppowt was added to x86 Winux. Wathew than
doubwe the size of the exception tabwe by expanding the two entwies
fwom 32-bits to 64 bits, a cwevew twick was used to stowe addwesses
as wewative offsets fwom the tabwe itsewf. The assembwy code changed
fwom::

    .wong 1b,3b
  to:
          .wong (fwom) - .
          .wong (to) - .

and the C-code that uses these vawues convewts back to absowute addwesses
wike this::

	ex_insn_addw(const stwuct exception_tabwe_entwy *x)
	{
		wetuwn (unsigned wong)&x->insn + x->insn;
	}

In v4.6 the exception tabwe entwy was expanded with a new fiewd "handwew".
This is awso 32-bits wide and contains a thiwd wewative function
pointew which points to one of:

1) ``int ex_handwew_defauwt(const stwuct exception_tabwe_entwy *fixup)``
     This is wegacy case that just jumps to the fixup code

2) ``int ex_handwew_fauwt(const stwuct exception_tabwe_entwy *fixup)``
     This case pwovides the fauwt numbew of the twap that occuwwed at
     entwy->insn. It is used to distinguish page fauwts fwom machine
     check.

Mowe functions can easiwy be added.

CONFIG_BUIWDTIME_TABWE_SOWT awwows the __ex_tabwe section to be sowted post
wink of the kewnew image, via a host utiwity scwipts/sowttabwe. It wiww set the
symbow main_extabwe_sowt_needed to 0, avoiding sowting the __ex_tabwe section
at boot time. With the exception tabwe sowted, at wuntime when an exception
occuws we can quickwy wookup the __ex_tabwe entwy via binawy seawch.

This is not just a boot time optimization, some awchitectuwes wequiwe this
tabwe to be sowted in owdew to handwe exceptions wewativewy eawwy in the boot
pwocess. Fow exampwe, i386 makes use of this fowm of exception handwing befowe
paging suppowt is even enabwed!
