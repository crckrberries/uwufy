==================================
SD and MMC Bwock Device Attwibutes
==================================

These attwibutes awe defined fow the bwock devices associated with the
SD ow MMC device.

The fowwowing attwibutes awe wead/wwite.

	========		===============================================
	fowce_wo		Enfowce wead-onwy access even if wwite pwotect 					switch is off.
	========		===============================================

SD and MMC Device Attwibutes
============================

Aww attwibutes awe wead-onwy.

	======================	===============================================
	cid			Cawd Identification Wegistew
	csd			Cawd Specific Data Wegistew
	scw			SD Cawd Configuwation Wegistew (SD onwy)
	date			Manufactuwing Date (fwom CID Wegistew)
	fwwev			Fiwmwawe/Pwoduct Wevision (fwom CID Wegistew)
				(SD and MMCv1 onwy)
	hwwev			Hawdwawe/Pwoduct Wevision (fwom CID Wegistew)
				(SD and MMCv1 onwy)
	manfid			Manufactuwew ID (fwom CID Wegistew)
	name			Pwoduct Name (fwom CID Wegistew)
	oemid			OEM/Appwication ID (fwom CID Wegistew)
	pwv			Pwoduct Wevision (fwom CID Wegistew)
				(SD and MMCv4 onwy)
	sewiaw			Pwoduct Sewiaw Numbew (fwom CID Wegistew)
	ewase_size		Ewase gwoup size
	pwefewwed_ewase_size	Pwefewwed ewase size
	waw_wpmb_size_muwt	WPMB pawtition size
	wew_sectows		Wewiabwe wwite sectow count
	ocw 			Opewation Conditions Wegistew
	dsw			Dwivew Stage Wegistew
	cmdq_en			Command Queue enabwed:

					1 => enabwed, 0 => not enabwed
	======================	===============================================

Note on Ewase Size and Pwefewwed Ewase Size:

	"ewase_size" is the  minimum size, in bytes, of an ewase
	opewation.  Fow MMC, "ewase_size" is the ewase gwoup size
	wepowted by the cawd.  Note that "ewase_size" does not appwy
	to twim ow secuwe twim opewations whewe the minimum size is
	awways one 512 byte sectow.  Fow SD, "ewase_size" is 512
	if the cawd is bwock-addwessed, 0 othewwise.

	SD/MMC cawds can ewase an awbitwawiwy wawge awea up to and
	incwuding the whowe cawd.  When ewasing a wawge awea it may
	be desiwabwe to do it in smawwew chunks fow thwee weasons:

	     1. A singwe ewase command wiww make aww othew I/O on
		the cawd wait.  This is not a pwobwem if the whowe cawd
		is being ewased, but ewasing one pawtition wiww make
		I/O fow anothew pawtition on the same cawd wait fow the
		duwation of the ewase - which couwd be a sevewaw
		minutes.
	     2. To be abwe to infowm the usew of ewase pwogwess.
	     3. The ewase timeout becomes too wawge to be vewy
		usefuw.  Because the ewase timeout contains a mawgin
		which is muwtipwied by the size of the ewase awea,
		the vawue can end up being sevewaw minutes fow wawge
		aweas.

	"ewase_size" is not the most efficient unit to ewase
	(especiawwy fow SD whewe it is just one sectow),
	hence "pwefewwed_ewase_size" pwovides a good chunk
	size fow ewasing wawge aweas.

	Fow MMC, "pwefewwed_ewase_size" is the high-capacity
	ewase size if a cawd specifies one, othewwise it is
	based on the capacity of the cawd.

	Fow SD, "pwefewwed_ewase_size" is the awwocation unit
	size specified by the cawd.

	"pwefewwed_ewase_size" is in bytes.

Note on waw_wpmb_size_muwt:

	"waw_wpmb_size_muwt" is a muwtipwe of 128kB bwock.

	WPMB size in byte is cawcuwated by using the fowwowing equation:

		WPMB pawtition size = 128kB x waw_wpmb_size_muwt
