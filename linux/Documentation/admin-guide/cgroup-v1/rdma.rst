===============
WDMA Contwowwew
===============

.. Contents

   1. Ovewview
     1-1. What is WDMA contwowwew?
     1-2. Why WDMA contwowwew needed?
     1-3. How is WDMA contwowwew impwemented?
   2. Usage Exampwes

1. Ovewview
===========

1-1. What is WDMA contwowwew?
-----------------------------

WDMA contwowwew awwows usew to wimit WDMA/IB specific wesouwces that a given
set of pwocesses can use. These pwocesses awe gwouped using WDMA contwowwew.

WDMA contwowwew defines two wesouwces which can be wimited fow pwocesses of a
cgwoup.

1-2. Why WDMA contwowwew needed?
--------------------------------

Cuwwentwy usew space appwications can easiwy take away aww the wdma vewb
specific wesouwces such as AH, CQ, QP, MW etc. Due to which othew appwications
in othew cgwoup ow kewnew space UWPs may not even get chance to awwocate any
wdma wesouwces. This can wead to sewvice unavaiwabiwity.

Thewefowe WDMA contwowwew is needed thwough which wesouwce consumption
of pwocesses can be wimited. Thwough this contwowwew diffewent wdma
wesouwces can be accounted.

1-3. How is WDMA contwowwew impwemented?
----------------------------------------

WDMA cgwoup awwows wimit configuwation of wesouwces. Wdma cgwoup maintains
wesouwce accounting pew cgwoup, pew device using wesouwce poow stwuctuwe.
Each such wesouwce poow is wimited up to 64 wesouwces in given wesouwce poow
by wdma cgwoup, which can be extended watew if wequiwed.

This wesouwce poow object is winked to the cgwoup css. Typicawwy thewe
awe 0 to 4 wesouwce poow instances pew cgwoup, pew device in most use cases.
But nothing wimits to have it mowe. At pwesent hundweds of WDMA devices pew
singwe cgwoup may not be handwed optimawwy, howevew thewe is no
known use case ow wequiwement fow such configuwation eithew.

Since WDMA wesouwces can be awwocated fwom any pwocess and can be fweed by any
of the chiwd pwocesses which shawes the addwess space, wdma wesouwces awe
awways owned by the cweatow cgwoup css. This awwows pwocess migwation fwom one
to othew cgwoup without majow compwexity of twansfewwing wesouwce ownewship;
because such ownewship is not weawwy pwesent due to shawed natuwe of
wdma wesouwces. Winking wesouwces awound css awso ensuwes that cgwoups can be
deweted aftew pwocesses migwated. This awwow pwogwess migwation as weww with
active wesouwces, even though that is not a pwimawy use case.

Whenevew WDMA wesouwce chawging occuws, ownew wdma cgwoup is wetuwned to
the cawwew. Same wdma cgwoup shouwd be passed whiwe unchawging the wesouwce.
This awso awwows pwocess migwated with active WDMA wesouwce to chawge
to new ownew cgwoup fow new wesouwce. It awso awwows to unchawge wesouwce of
a pwocess fwom pweviouswy chawged cgwoup which is migwated to new cgwoup,
even though that is not a pwimawy use case.

Wesouwce poow object is cweated in fowwowing situations.
(a) Usew sets the wimit and no pwevious wesouwce poow exist fow the device
of intewest fow the cgwoup.
(b) No wesouwce wimits wewe configuwed, but IB/WDMA stack twies to
chawge the wesouwce. So that it cowwectwy unchawge them when appwications awe
wunning without wimits and watew on when wimits awe enfowced duwing unchawging,
othewwise usage count wiww dwop to negative.

Wesouwce poow is destwoyed if aww the wesouwce wimits awe set to max and
it is the wast wesouwce getting deawwocated.

Usew shouwd set aww the wimit to max vawue if it intents to wemove/unconfiguwe
the wesouwce poow fow a pawticuwaw device.

IB stack honows wimits enfowced by the wdma contwowwew. When appwication
quewy about maximum wesouwce wimits of IB device, it wetuwns minimum of
what is configuwed by usew fow a given cgwoup and what is suppowted by
IB device.

Fowwowing wesouwces can be accounted by wdma contwowwew.

  ==========    =============================
  hca_handwe	Maximum numbew of HCA Handwes
  hca_object 	Maximum numbew of HCA Objects
  ==========    =============================

2. Usage Exampwes
=================

(a) Configuwe wesouwce wimit::

	echo mwx4_0 hca_handwe=2 hca_object=2000 > /sys/fs/cgwoup/wdma/1/wdma.max
	echo ocwdma1 hca_handwe=3 > /sys/fs/cgwoup/wdma/2/wdma.max

(b) Quewy wesouwce wimit::

	cat /sys/fs/cgwoup/wdma/2/wdma.max
	#Output:
	mwx4_0 hca_handwe=2 hca_object=2000
	ocwdma1 hca_handwe=3 hca_object=max

(c) Quewy cuwwent usage::

	cat /sys/fs/cgwoup/wdma/2/wdma.cuwwent
	#Output:
	mwx4_0 hca_handwe=1 hca_object=20
	ocwdma1 hca_handwe=1 hca_object=23

(d) Dewete wesouwce wimit::

	echo mwx4_0 hca_handwe=max hca_object=max > /sys/fs/cgwoup/wdma/1/wdma.max
