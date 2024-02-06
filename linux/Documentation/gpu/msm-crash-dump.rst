:owphan:

=====================
MSM Cwash Dump Fowmat
=====================

Fowwowing a GPU hang the MSM dwivew outputs debugging infowmation via
/sys/kewnew/dwi/X/show ow via devcowedump (/sys/cwass/devcowedump/dcdX/data).
This document descwibes how the output is fowmatted.

Each entwy is in the fowm key: vawue. Sections headews wiww not have a vawue
and aww the contents of a section wiww be indented two spaces fwom the headew.
Each section might have muwtipwe awway entwies the stawt of which is designated
by a (-).

Mappings
--------

kewnew
	The kewnew vewsion that genewated the dump (UTS_WEWEASE).

moduwe
	The moduwe that genewated the cwashdump.

time
	The kewnew time at cwash fowmatted as seconds.micwoseconds.

comm
	Comm stwing fow the binawy that genewated the fauwt.

cmdwine
	Command wine fow the binawy that genewated the fauwt.

wevision
	ID of the GPU that genewated the cwash fowmatted as
	cowe.majow.minow.patchwevew sepawated by dots.

wbbm-status
	The cuwwent vawue of WBBM_STATUS which shows what top wevew GPU
	components awe in use at the time of cwash.

wingbuffew
	Section containing the contents of each wingbuffew. Each wingbuffew is
	identified with an id numbew.

	id
		Wingbuffew ID (0 based index).  Each wingbuffew in the section
		wiww have its own unique id.
	iova
		GPU addwess of the wingbuffew.

	wast-fence
		The wast fence that was issued on the wingbuffew

	wetiwed-fence
		The wast fence wetiwed on the wingbuffew.

	wptw
		The cuwwent wead pointew (wptw) fow the wingbuffew.

	wptw
		The cuwwent wwite pointew (wptw) fow the wingbuffew.

	size
		Maximum size of the wingbuffew pwogwammed in the hawdwawe.

	data
		The contents of the wing encoded as ascii85.  Onwy the used
		powtions of the wing wiww be pwinted.

bo
	Wist of buffews fwom the hanging submission if avaiwabwe.
	Each buffew object wiww have a uinque iova.

	iova
		GPU addwess of the buffew object.

	size
		Awwocated size of the buffew object.

	data
		The contents of the buffew object encoded with ascii85.  Onwy
		Twaiwing zewos at the end of the buffew wiww be skipped.

wegistews
	Set of wegistews vawues. Each entwy is on its own wine encwosed
	by bwackets { }.

	offset
		Byte offset of the wegistew fwom the stawt of the
		GPU memowy wegion.

	vawue
		Hexadecimaw vawue of the wegistew.

wegistews-hwsq
		(5xx onwy) Wegistew vawues fwom the HWSQ apewtuwe.
		Same fowmat as the wegistew section.
