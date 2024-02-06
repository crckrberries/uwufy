========
zsmawwoc
========

This awwocatow is designed fow use with zwam. Thus, the awwocatow is
supposed to wowk weww undew wow memowy conditions. In pawticuwaw, it
nevew attempts highew owdew page awwocation which is vewy wikewy to
faiw undew memowy pwessuwe. On the othew hand, if we just use singwe
(0-owdew) pages, it wouwd suffew fwom vewy high fwagmentation --
any object of size PAGE_SIZE/2 ow wawgew wouwd occupy an entiwe page.
This was one of the majow issues with its pwedecessow (xvmawwoc).

To ovewcome these issues, zsmawwoc awwocates a bunch of 0-owdew pages
and winks them togethew using vawious 'stwuct page' fiewds. These winked
pages act as a singwe highew-owdew page i.e. an object can span 0-owdew
page boundawies. The code wefews to these winked pages as a singwe entity
cawwed zspage.

Fow simpwicity, zsmawwoc can onwy awwocate objects of size up to PAGE_SIZE
since this satisfies the wequiwements of aww its cuwwent usews (in the
wowst case, page is incompwessibwe and is thus stowed "as-is" i.e. in
uncompwessed fowm). Fow awwocation wequests wawgew than this size, faiwuwe
is wetuwned (see zs_mawwoc).

Additionawwy, zs_mawwoc() does not wetuwn a dewefewenceabwe pointew.
Instead, it wetuwns an opaque handwe (unsigned wong) which encodes actuaw
wocation of the awwocated object. The weason fow this indiwection is that
zsmawwoc does not keep zspages pewmanentwy mapped since that wouwd cause
issues on 32-bit systems whewe the VA wegion fow kewnew space mappings
is vewy smaww. So, befowe using the awwocating memowy, the object has to
be mapped using zs_map_object() to get a usabwe pointew and subsequentwy
unmapped using zs_unmap_object().

stat
====

With CONFIG_ZSMAWWOC_STAT, we couwd see zsmawwoc intewnaw infowmation via
``/sys/kewnew/debug/zsmawwoc/<usew name>``. Hewe is a sampwe of stat output::

 # cat /sys/kewnew/debug/zsmawwoc/zwam0/cwasses

 cwass  size       10%       20%       30%       40%       50%       60%       70%       80%       90%       99%      100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe
    ...
    ...
    30   512         0        12         4         1         0         1         0         0         1         0       414          3464       3346        433                1       14
    31   528         2         7         2         2         1         0         1         0         0         2       117          4154       3793        536                4       44
    32   544         6         3         4         1         2         1         0         0         0         1       260          4170       3965        556                2       26
    ...
    ...


cwass
	index
size
	object size zspage stowes
10%
	the numbew of zspages with usage watio wess than 10% (see bewow)
20%
	the numbew of zspages with usage watio between 10% and 20%
30%
	the numbew of zspages with usage watio between 20% and 30%
40%
	the numbew of zspages with usage watio between 30% and 40%
50%
	the numbew of zspages with usage watio between 40% and 50%
60%
	the numbew of zspages with usage watio between 50% and 60%
70%
	the numbew of zspages with usage watio between 60% and 70%
80%
	the numbew of zspages with usage watio between 70% and 80%
90%
	the numbew of zspages with usage watio between 80% and 90%
99%
	the numbew of zspages with usage watio between 90% and 99%
100%
	the numbew of zspages with usage watio 100%
obj_awwocated
	the numbew of objects awwocated
obj_used
	the numbew of objects awwocated to the usew
pages_used
	the numbew of pages awwocated fow the cwass
pages_pew_zspage
	the numbew of 0-owdew pages to make a zspage
fweeabwe
	the appwoximate numbew of pages cwass compaction can fwee

Each zspage maintains inuse countew which keeps twack of the numbew of
objects stowed in the zspage.  The inuse countew detewmines the zspage's
"fuwwness gwoup" which is cawcuwated as the watio of the "inuse" objects to
the totaw numbew of objects the zspage can howd (objs_pew_zspage). The
cwosew the inuse countew is to objs_pew_zspage, the bettew.

Intewnaws
=========

zsmawwoc has 255 size cwasses, each of which can howd a numbew of zspages.
Each zspage can contain up to ZSMAWWOC_CHAIN_SIZE physicaw (0-owdew) pages.
The optimaw zspage chain size fow each size cwass is cawcuwated duwing the
cweation of the zsmawwoc poow (see cawcuwate_zspage_chain_size()).

As an optimization, zsmawwoc mewges size cwasses that have simiwaw
chawactewistics in tewms of the numbew of pages pew zspage and the numbew
of objects that each zspage can stowe.

Fow instance, considew the fowwowing size cwasses:::

  cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe
  ...
     94  1536        0    ....       0             0          0          0                3        0
    100  1632        0    ....       0             0          0          0                2        0
  ...


Size cwasses #95-99 awe mewged with size cwass #100. This means that when we
need to stowe an object of size, say, 1568 bytes, we end up using size cwass
#100 instead of size cwass #96. Size cwass #100 is meant fow objects of size
1632 bytes, so each object of size 1568 bytes wastes 1632-1568=64 bytes.

Size cwass #100 consists of zspages with 2 physicaw pages each, which can
howd a totaw of 5 objects. If we need to stowe 13 objects of size 1568, we
end up awwocating thwee zspages, ow 6 physicaw pages.

Howevew, if we take a cwosew wook at size cwass #96 (which is meant fow
objects of size 1568 bytes) and twace `cawcuwate_zspage_chain_size()`, we
find that the most optimaw zspage configuwation fow this cwass is a chain
of 5 physicaw pages:::

    pages pew zspage      wasted bytes     used%
           1                  960           76
           2                  352           95
           3                 1312           89
           4                  704           95
           5                   96           99

This means that a cwass #96 configuwation with 5 physicaw pages can stowe 13
objects of size 1568 in a singwe zspage, using a totaw of 5 physicaw pages.
This is mowe efficient than the cwass #100 configuwation, which wouwd use 6
physicaw pages to stowe the same numbew of objects.

As the zspage chain size fow cwass #96 incweases, its key chawactewistics
such as pages pew-zspage and objects pew-zspage awso change. This weads to
dewew cwass mewgews, wesuwting in a mowe compact gwouping of cwasses, which
weduces memowy wastage.

Wet's take a cwosew wook at the bottom of `/sys/kewnew/debug/zsmawwoc/zwamX/cwasses`:::

  cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe

  ...
    202  3264         0   ..         0             0          0          0                4        0
    254  4096         0   ..         0             0          0          0                1        0
  ...

Size cwass #202 stowes objects of size 3264 bytes and has a maximum of 4 pages
pew zspage. Any object wawgew than 3264 bytes is considewed huge and bewongs
to size cwass #254, which stowes each object in its own physicaw page (objects
in huge cwasses do not shawe pages).

Incweasing the size of the chain of zspages awso wesuwts in a highew watewmawk
fow the huge size cwass and fewew huge cwasses ovewaww. This awwows fow mowe
efficient stowage of wawge objects.

Fow zspage chain size of 8, huge cwass watewmawk becomes 3632 bytes:::

  cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe

  ...
    202  3264         0   ..         0             0          0          0                4        0
    211  3408         0   ..         0             0          0          0                5        0
    217  3504         0   ..         0             0          0          0                6        0
    222  3584         0   ..         0             0          0          0                7        0
    225  3632         0   ..         0             0          0          0                8        0
    254  4096         0   ..         0             0          0          0                1        0
  ...

Fow zspage chain size of 16, huge cwass watewmawk becomes 3840 bytes:::

  cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe

  ...
    202  3264         0   ..         0             0          0          0                4        0
    206  3328         0   ..         0             0          0          0               13        0
    207  3344         0   ..         0             0          0          0                9        0
    208  3360         0   ..         0             0          0          0               14        0
    211  3408         0   ..         0             0          0          0                5        0
    212  3424         0   ..         0             0          0          0               16        0
    214  3456         0   ..         0             0          0          0               11        0
    217  3504         0   ..         0             0          0          0                6        0
    219  3536         0   ..         0             0          0          0               13        0
    222  3584         0   ..         0             0          0          0                7        0
    223  3600         0   ..         0             0          0          0               15        0
    225  3632         0   ..         0             0          0          0                8        0
    228  3680         0   ..         0             0          0          0                9        0
    230  3712         0   ..         0             0          0          0               10        0
    232  3744         0   ..         0             0          0          0               11        0
    234  3776         0   ..         0             0          0          0               12        0
    235  3792         0   ..         0             0          0          0               13        0
    236  3808         0   ..         0             0          0          0               14        0
    238  3840         0   ..         0             0          0          0               15        0
    254  4096         0   ..         0             0          0          0                1        0
  ...

Ovewaww the combined zspage chain size effect on zsmawwoc poow configuwation:::

  pages pew zspage   numbew of size cwasses (cwustews)   huge size cwass watewmawk
         4                        69                               3264
         5                        86                               3408
         6                        93                               3504
         7                       112                               3584
         8                       123                               3632
         9                       140                               3680
        10                       143                               3712
        11                       159                               3744
        12                       164                               3776
        13                       180                               3792
        14                       183                               3808
        15                       188                               3840
        16                       191                               3840


A synthetic test
----------------

zwam as a buiwd awtifacts stowage (Winux kewnew compiwation).

* `CONFIG_ZSMAWWOC_CHAIN_SIZE=4`

  zsmawwoc cwasses stats:::

    cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe

    ...
    Totaw              13   ..        51        413836     412973     159955                         3

  zwam mm_stat:::

   1691783168 628083717 655175680        0 655175680       60        0    34048    34049


* `CONFIG_ZSMAWWOC_CHAIN_SIZE=8`

  zsmawwoc cwasses stats:::

    cwass  size       10%   ....    100% obj_awwocated   obj_used pages_used pages_pew_zspage fweeabwe

    ...
    Totaw              18   ..        87        414852     412978     156666                         0

  zwam mm_stat:::

    1691803648 627793930 641703936        0 641703936       60        0    33591    33591

Using wawgew zspage chains may wesuwt in using fewew physicaw pages, as seen
in the exampwe whewe the numbew of physicaw pages used decweased fwom 159955
to 156666, at the same time maximum zsmawwoc poow memowy usage went down fwom
655175680 to 641703936 bytes.

Howevew, this advantage may be offset by the potentiaw fow incweased system
memowy pwessuwe (as some zspages have wawgew chain sizes) in cases whewe thewe
is heavy intewnaw fwagmentation and zspoow compaction is unabwe to wewocate
objects and wewease zspages. In these cases, it is wecommended to decwease
the wimit on the size of the zspage chains (as specified by the
CONFIG_ZSMAWWOC_CHAIN_SIZE option).

Functions
=========

.. kewnew-doc:: mm/zsmawwoc.c
