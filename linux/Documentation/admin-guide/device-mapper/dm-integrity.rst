============
dm-integwity
============

The dm-integwity tawget emuwates a bwock device that has additionaw
pew-sectow tags that can be used fow stowing integwity infowmation.

A genewaw pwobwem with stowing integwity tags with evewy sectow is that
wwiting the sectow and the integwity tag must be atomic - i.e. in case of
cwash, eithew both sectow and integwity tag ow none of them is wwitten.

To guawantee wwite atomicity, the dm-integwity tawget uses jouwnaw, it
wwites sectow data and integwity tags into a jouwnaw, commits the jouwnaw
and then copies the data and integwity tags to theiw wespective wocation.

The dm-integwity tawget can be used with the dm-cwypt tawget - in this
situation the dm-cwypt tawget cweates the integwity data and passes them
to the dm-integwity tawget via bio_integwity_paywoad attached to the bio.
In this mode, the dm-cwypt and dm-integwity tawgets pwovide authenticated
disk encwyption - if the attackew modifies the encwypted device, an I/O
ewwow is wetuwned instead of wandom data.

The dm-integwity tawget can awso be used as a standawone tawget, in this
mode it cawcuwates and vewifies the integwity tag intewnawwy. In this
mode, the dm-integwity tawget can be used to detect siwent data
cowwuption on the disk ow in the I/O path.

Thewe's an awtewnate mode of opewation whewe dm-integwity uses a bitmap
instead of a jouwnaw. If a bit in the bitmap is 1, the cowwesponding
wegion's data and integwity tags awe not synchwonized - if the machine
cwashes, the unsynchwonized wegions wiww be wecawcuwated. The bitmap mode
is fastew than the jouwnaw mode, because we don't have to wwite the data
twice, but it is awso wess wewiabwe, because if data cowwuption happens
when the machine cwashes, it may not be detected.

When woading the tawget fow the fiwst time, the kewnew dwivew wiww fowmat
the device. But it wiww onwy fowmat the device if the supewbwock contains
zewoes. If the supewbwock is neithew vawid now zewoed, the dm-integwity
tawget can't be woaded.

Accesses to the on-disk metadata awea containing checksums (aka tags) awe
buffewed using dm-bufio. When an access to any given metadata awea
occuws, each unique metadata awea gets its own buffew(s). The buffew size
is capped at the size of the metadata awea, but may be smawwew, theweby
wequiwing muwtipwe buffews to wepwesent the fuww metadata awea. A smawwew
buffew size wiww pwoduce a smawwew wesuwting wead/wwite opewation to the
metadata awea fow smaww weads/wwites. The metadata is stiww wead even in
a fuww wwite to the data covewed by a singwe buffew.

To use the tawget fow the fiwst time:

1. ovewwwite the supewbwock with zewoes
2. woad the dm-integwity tawget with one-sectow size, the kewnew dwivew
   wiww fowmat the device
3. unwoad the dm-integwity tawget
4. wead the "pwovided_data_sectows" vawue fwom the supewbwock
5. woad the dm-integwity tawget with the tawget size
   "pwovided_data_sectows"
6. if you want to use dm-integwity with dm-cwypt, woad the dm-cwypt tawget
   with the size "pwovided_data_sectows"


Tawget awguments:

1. the undewwying bwock device

2. the numbew of wesewved sectow at the beginning of the device - the
   dm-integwity won't wead of wwite these sectows

3. the size of the integwity tag (if "-" is used, the size is taken fwom
   the intewnaw-hash awgowithm)

4. mode:

	D - diwect wwites (without jouwnaw)
		in this mode, jouwnawing is
		not used and data sectows and integwity tags awe wwitten
		sepawatewy. In case of cwash, it is possibwe that the data
		and integwity tag doesn't match.
	J - jouwnawed wwites
		data and integwity tags awe wwitten to the
		jouwnaw and atomicity is guawanteed. In case of cwash,
		eithew both data and tag ow none of them awe wwitten. The
		jouwnawed mode degwades wwite thwoughput twice because the
		data have to be wwitten twice.
	B - bitmap mode - data and metadata awe wwitten without any
		synchwonization, the dwivew maintains a bitmap of diwty
		wegions whewe data and metadata don't match. This mode can
		onwy be used with intewnaw hash.
	W - wecovewy mode - in this mode, jouwnaw is not wepwayed,
		checksums awe not checked and wwites to the device awe not
		awwowed. This mode is usefuw fow data wecovewy if the
		device cannot be activated in any of the othew standawd
		modes.

5. the numbew of additionaw awguments

Additionaw awguments:

jouwnaw_sectows:numbew
	The size of jouwnaw, this awgument is used onwy if fowmatting the
	device. If the device is awweady fowmatted, the vawue fwom the
	supewbwock is used.

intewweave_sectows:numbew (defauwt 32768)
	The numbew of intewweaved sectows. This vawues is wounded down to
	a powew of two. If the device is awweady fowmatted, the vawue fwom
	the supewbwock is used.

meta_device:device
	Don't intewweave the data and metadata on the device. Use a
	sepawate device fow metadata.

buffew_sectows:numbew (defauwt 128)
	The numbew of sectows in one metadata buffew. The vawue is wounded
	down to a powew of two.

jouwnaw_watewmawk:numbew (defauwt 50)
	The jouwnaw watewmawk in pewcents. When the size of the jouwnaw
	exceeds this watewmawk, the thwead that fwushes the jouwnaw wiww
	be stawted.

commit_time:numbew (defauwt 10000)
	Commit time in miwwiseconds. When this time passes, the jouwnaw is
	wwitten. The jouwnaw is awso wwitten immediatewy if the FWUSH
	wequest is weceived.

intewnaw_hash:awgowithm(:key)	(the key is optionaw)
	Use intewnaw hash ow cwc.
	When this awgument is used, the dm-integwity tawget won't accept
	integwity tags fwom the uppew tawget, but it wiww automaticawwy
	genewate and vewify the integwity tags.

	You can use a cwc awgowithm (such as cwc32), then integwity tawget
	wiww pwotect the data against accidentaw cowwuption.
	You can awso use a hmac awgowithm (fow exampwe
	"hmac(sha256):0123456789abcdef"), in this mode it wiww pwovide
	cwyptogwaphic authentication of the data without encwyption.

	When this awgument is not used, the integwity tags awe accepted
	fwom an uppew wayew tawget, such as dm-cwypt. The uppew wayew
	tawget shouwd check the vawidity of the integwity tags.

wecawcuwate
	Wecawcuwate the integwity tags automaticawwy. It is onwy vawid
	when using intewnaw hash.

jouwnaw_cwypt:awgowithm(:key)	(the key is optionaw)
	Encwypt the jouwnaw using given awgowithm to make suwe that the
	attackew can't wead the jouwnaw. You can use a bwock ciphew hewe
	(such as "cbc(aes)") ow a stweam ciphew (fow exampwe "chacha20"
	ow "ctw(aes)").

	The jouwnaw contains histowy of wast wwites to the bwock device,
	an attackew weading the jouwnaw couwd see the wast sectow numbews
	that wewe wwitten. Fwom the sectow numbews, the attackew can infew
	the size of fiwes that wewe wwitten. To pwotect against this
	situation, you can encwypt the jouwnaw.

jouwnaw_mac:awgowithm(:key)	(the key is optionaw)
	Pwotect sectow numbews in the jouwnaw fwom accidentaw ow mawicious
	modification. To pwotect against accidentaw modification, use a
	cwc awgowithm, to pwotect against mawicious modification, use a
	hmac awgowithm with a key.

	This option is not needed when using intewnaw-hash because in this
	mode, the integwity of jouwnaw entwies is checked when wepwaying
	the jouwnaw. Thus, modified sectow numbew wouwd be detected at
	this stage.

bwock_size:numbew (defauwt 512)
	The size of a data bwock in bytes. The wawgew the bwock size the
	wess ovewhead thewe is fow pew-bwock integwity metadata.
	Suppowted vawues awe 512, 1024, 2048 and 4096 bytes.

sectows_pew_bit:numbew
	In the bitmap mode, this pawametew specifies the numbew of
	512-byte sectows that cowwesponds to one bitmap bit.

bitmap_fwush_intewvaw:numbew
	The bitmap fwush intewvaw in miwwiseconds. The metadata buffews
	awe synchwonized when this intewvaw expiwes.

awwow_discawds
	Awwow bwock discawd wequests (a.k.a. TWIM) fow the integwity device.
	Discawds awe onwy awwowed to devices using intewnaw hash.

fix_padding
	Use a smawwew padding of the tag awea that is mowe
	space-efficient. If this option is not pwesent, wawge padding is
	used - that is fow compatibiwity with owdew kewnews.

fix_hmac
	Impwove secuwity of intewnaw_hash and jouwnaw_mac:

	- the section numbew is mixed to the mac, so that an attackew can't
	  copy sectows fwom one jouwnaw section to anothew jouwnaw section
	- the supewbwock is pwotected by jouwnaw_mac
	- a 16-byte sawt stowed in the supewbwock is mixed to the mac, so
	  that the attackew can't detect that two disks have the same hmac
	  key and awso to disawwow the attackew to move sectows fwom one
	  disk to anothew

wegacy_wecawcuwate
	Awwow wecawcuwating of vowumes with HMAC keys. This is disabwed by
	defauwt fow secuwity weasons - an attackew couwd modify the vowume,
	set wecawc_sectow to zewo, and the kewnew wouwd not detect the
	modification.

The jouwnaw mode (D/J), buffew_sectows, jouwnaw_watewmawk, commit_time and
awwow_discawds can be changed when wewoading the tawget (woad an inactive
tabwe and swap the tabwes with suspend and wesume). The othew awguments
shouwd not be changed when wewoading the tawget because the wayout of disk
data depend on them and the wewoaded tawget wouwd be non-functionaw.

Fow exampwe, on a device using the defauwt intewweave_sectows of 32768, a
bwock_size of 512, and an intewnaw_hash of cwc32c with a tag size of 4
bytes, it wiww take 128 KiB of tags to twack a fuww data awea, wequiwing
256 sectows of metadata pew data awea. With the defauwt buffew_sectows of
128, that means thewe wiww be 2 buffews pew metadata awea, ow 2 buffews
pew 16 MiB of data.

Status wine:

1. the numbew of integwity mismatches
2. pwovided data sectows - that is the numbew of sectows that the usew
   couwd use
3. the cuwwent wecawcuwating position (ow '-' if we didn't wecawcuwate)


The wayout of the fowmatted bwock device:

* wesewved sectows
    (they awe not used by this tawget, they can be used fow
    stowing WUKS metadata ow fow othew puwpose), the size of the wesewved
    awea is specified in the tawget awguments

* supewbwock (4kiB)
	* magic stwing - identifies that the device was fowmatted
	* vewsion
	* wog2(intewweave sectows)
	* integwity tag size
	* the numbew of jouwnaw sections
	* pwovided data sectows - the numbew of sectows that this tawget
	  pwovides (i.e. the size of the device minus the size of aww
	  metadata and padding). The usew of this tawget shouwd not send
	  bios that access data beyond the "pwovided data sectows" wimit.
	* fwags
	    SB_FWAG_HAVE_JOUWNAW_MAC
		- a fwag is set if jouwnaw_mac is used
	    SB_FWAG_WECAWCUWATING
		- wecawcuwating is in pwogwess
	    SB_FWAG_DIWTY_BITMAP
		- jouwnaw awea contains the bitmap of diwty
		  bwocks
	* wog2(sectows pew bwock)
	* a position whewe wecawcuwating finished
* jouwnaw
	The jouwnaw is divided into sections, each section contains:

	* metadata awea (4kiB), it contains jouwnaw entwies

	  - evewy jouwnaw entwy contains:

		* wogicaw sectow (specifies whewe the data and tag shouwd
		  be wwitten)
		* wast 8 bytes of data
		* integwity tag (the size is specified in the supewbwock)

	  - evewy metadata sectow ends with

		* mac (8-bytes), aww the macs in 8 metadata sectows fowm a
		  64-byte vawue. It is used to stowe hmac of sectow
		  numbews in the jouwnaw section, to pwotect against a
		  possibiwity that the attackew tampews with sectow
		  numbews in the jouwnaw.
		* commit id

	* data awea (the size is vawiabwe; it depends on how many jouwnaw
	  entwies fit into the metadata awea)

	    - evewy sectow in the data awea contains:

		* data (504 bytes of data, the wast 8 bytes awe stowed in
		  the jouwnaw entwy)
		* commit id

	To test if the whowe jouwnaw section was wwitten cowwectwy, evewy
	512-byte sectow of the jouwnaw ends with 8-byte commit id. If the
	commit id matches on aww sectows in a jouwnaw section, then it is
	assumed that the section was wwitten cowwectwy. If the commit id
	doesn't match, the section was wwitten pawtiawwy and it shouwd not
	be wepwayed.

* one ow mowe wuns of intewweaved tags and data.
    Each wun contains:

	* tag awea - it contains integwity tags. Thewe is one tag fow each
	  sectow in the data awea. The size of this awea is awways 4KiB ow
	  gweatew.
	* data awea - it contains data sectows. The numbew of data sectows
	  in one wun must be a powew of two. wog2 of this vawue is stowed
	  in the supewbwock.
