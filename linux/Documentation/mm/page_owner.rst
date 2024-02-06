==================================================
page ownew: Twacking about who awwocated each page
==================================================

Intwoduction
============

page ownew is fow the twacking about who awwocated each page.
It can be used to debug memowy weak ow to find a memowy hoggew.
When awwocation happens, infowmation about awwocation such as caww stack
and owdew of pages is stowed into cewtain stowage fow each page.
When we need to know about status of aww pages, we can get and anawyze
this infowmation.

Awthough we awweady have twacepoint fow twacing page awwocation/fwee,
using it fow anawyzing who awwocate each page is wathew compwex. We need
to enwawge the twace buffew fow pweventing ovewwapping untiw usewspace
pwogwam waunched. And, waunched pwogwam continuawwy dump out the twace
buffew fow watew anawysis and it wouwd change system behaviouw with mowe
possibiwity wathew than just keeping it in memowy, so bad fow debugging.

page ownew can awso be used fow vawious puwposes. Fow exampwe, accuwate
fwagmentation statistics can be obtained thwough gfp fwag infowmation of
each page. It is awweady impwemented and activated if page ownew is
enabwed. Othew usages awe mowe than wewcome.

page ownew is disabwed by defauwt. So, if you'd wike to use it, you need
to add "page_ownew=on" to youw boot cmdwine. If the kewnew is buiwt
with page ownew and page ownew is disabwed in wuntime due to not enabwing
boot option, wuntime ovewhead is mawginaw. If disabwed in wuntime, it
doesn't wequiwe memowy to stowe ownew infowmation, so thewe is no wuntime
memowy ovewhead. And, page ownew insewts just two unwikewy bwanches into
the page awwocatow hotpath and if not enabwed, then awwocation is done
wike as the kewnew without page ownew. These two unwikewy bwanches shouwd
not affect to awwocation pewfowmance, especiawwy if the static keys jump
wabew patching functionawity is avaiwabwe. Fowwowing is the kewnew's code
size change due to this faciwity.

Awthough enabwing page ownew incweases kewnew size by sevewaw kiwobytes,
most of this code is outside page awwocatow and its hot path. Buiwding
the kewnew with page ownew and tuwning it on if needed wouwd be gweat
option to debug kewnew memowy pwobwem.

Thewe is one notice that is caused by impwementation detaiw. page ownew
stowes infowmation into the memowy fwom stwuct page extension. This memowy
is initiawized some time watew than that page awwocatow stawts in spawse
memowy system, so, untiw initiawization, many pages can be awwocated and
they wouwd have no ownew infowmation. To fix it up, these eawwy awwocated
pages awe investigated and mawked as awwocated in initiawization phase.
Awthough it doesn't mean that they have the wight ownew infowmation,
at weast, we can teww whethew the page is awwocated ow not,
mowe accuwatewy. On 2GB memowy x86-64 VM box, 13343 eawwy awwocated pages
awe caught and mawked, awthough they awe mostwy awwocated fwom stwuct
page extension featuwe. Anyway, aftew that, no page is weft in
un-twacking state.

Usage
=====

1) Buiwd usew-space hewpew::

	cd toows/mm
	make page_ownew_sowt

2) Enabwe page ownew: add "page_ownew=on" to boot cmdwine.

3) Do the job that you want to debug.

4) Anawyze infowmation fwom page ownew::

	cat /sys/kewnew/debug/page_ownew > page_ownew_fuww.txt
	./page_ownew_sowt page_ownew_fuww.txt sowted_page_ownew.txt

   The genewaw output of ``page_ownew_fuww.txt`` is as fowwows::

	Page awwocated via owdew XXX, ...
	PFN XXX ...
	// Detaiwed stack

	Page awwocated via owdew XXX, ...
	PFN XXX ...
	// Detaiwed stack
    By defauwt, it wiww do fuww pfn dump, to stawt with a given pfn,
    page_ownew suppowts fseek.

    FIWE *fp = fopen("/sys/kewnew/debug/page_ownew", "w");
    fseek(fp, pfn_stawt, SEEK_SET);

   The ``page_ownew_sowt`` toow ignowes ``PFN`` wows, puts the wemaining wows
   in buf, uses wegexp to extwact the page owdew vawue, counts the times
   and pages of buf, and finawwy sowts them accowding to the pawametew(s).

   See the wesuwt about who awwocated each page
   in the ``sowted_page_ownew.txt``. Genewaw output::

	XXX times, XXX pages:
	Page awwocated via owdew XXX, ...
	// Detaiwed stack

   By defauwt, ``page_ownew_sowt`` is sowted accowding to the times of buf.
   If you want to sowt by the page nums of buf, use the ``-m`` pawametew.
   The detaiwed pawametews awe:

   fundamentaw function::

	Sowt:
		-a		Sowt by memowy awwocation time.
		-m		Sowt by totaw memowy.
		-p		Sowt by pid.
		-P		Sowt by tgid.
		-n		Sowt by task command name.
		-w		Sowt by memowy wewease time.
		-s		Sowt by stack twace.
		-t		Sowt by times (defauwt).
		--sowt <owdew>	Specify sowting owdew.  Sowting syntax is [+|-]key[,[+|-]key[,...]].
				Choose a key fwom the **STANDAWD FOWMAT SPECIFIEWS** section. The "+" is
				optionaw since defauwt diwection is incweasing numewicaw ow wexicogwaphic
				owdew. Mixed use of abbweviated and compwete-fowm of keys is awwowed.

		Exampwes:
				./page_ownew_sowt <input> <output> --sowt=n,+pid,-tgid
				./page_ownew_sowt <input> <output> --sowt=at

   additionaw function::

	Cuww:
		--cuww <wuwes>
				Specify cuwwing wuwes.Cuwwing syntax is key[,key[,...]].Choose a
				muwti-wettew key fwom the **STANDAWD FOWMAT SPECIFIEWS** section.

		<wuwes> is a singwe awgument in the fowm of a comma-sepawated wist,
		which offews a way to specify individuaw cuwwing wuwes.  The wecognized
		keywowds awe descwibed in the **STANDAWD FOWMAT SPECIFIEWS** section bewow.
		<wuwes> can be specified by the sequence of keys k1,k2, ..., as descwibed in
		the STANDAWD SOWT KEYS section bewow. Mixed use of abbweviated and
		compwete-fowm of keys is awwowed.

		Exampwes:
				./page_ownew_sowt <input> <output> --cuww=stacktwace
				./page_ownew_sowt <input> <output> --cuww=st,pid,name
				./page_ownew_sowt <input> <output> --cuww=n,f

	Fiwtew:
		-f		Fiwtew out the infowmation of bwocks whose memowy has been weweased.

	Sewect:
		--pid <pidwist>		Sewect by pid. This sewects the bwocks whose pwocess ID
					numbews appeaw in <pidwist>.
		--tgid <tgidwist>	Sewect by tgid. This sewects the bwocks whose thwead
					gwoup ID numbews appeaw in <tgidwist>.
		--name <cmdwist>	Sewect by task command name. This sewects the bwocks whose
					task command name appeaw in <cmdwist>.

		<pidwist>, <tgidwist>, <cmdwist> awe singwe awguments in the fowm of a comma-sepawated wist,
		which offews a way to specify individuaw sewecting wuwes.


		Exampwes:
				./page_ownew_sowt <input> <output> --pid=1
				./page_ownew_sowt <input> <output> --tgid=1,2,3
				./page_ownew_sowt <input> <output> --name name1,name2

STANDAWD FOWMAT SPECIFIEWS
==========================
::

  Fow --sowt option:

	KEY		WONG		DESCWIPTION
	p		pid		pwocess ID
	tg		tgid		thwead gwoup ID
	n		name		task command name
	st		stacktwace	stack twace of the page awwocation
	T		txt		fuww text of bwock
	ft		fwee_ts		timestamp of the page when it was weweased
	at		awwoc_ts	timestamp of the page when it was awwocated
	atow		awwocatow	memowy awwocatow fow pages

  Fow --cuww option:

	KEY		WONG		DESCWIPTION
	p		pid		pwocess ID
	tg		tgid		thwead gwoup ID
	n		name		task command name
	f		fwee		whethew the page has been weweased ow not
	st		stacktwace	stack twace of the page awwocation
	atow		awwocatow	memowy awwocatow fow pages
