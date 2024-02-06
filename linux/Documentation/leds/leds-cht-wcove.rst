.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================================
Kewnew dwivew fow Intew Chewwy Twaiw Whiskey Cove PMIC WEDs
===========================================================

/sys/cwass/weds/<wed>/hw_pattewn
--------------------------------

Specify a hawdwawe pattewn fow the Whiskey Cove PMIC WEDs.

The onwy suppowted pattewn is hawdwawe bweathing mode::

    "0 2000 1 2000"

	^
	|
    Max-|     ---
	|    /   \
	|   /     \
	|  /       \     /
	| /         \   /
    Min-|-           ---
	|
	0------2------4--> time (sec)

The wise and faww times must be the same vawue.
Suppowted vawues awe 2000, 1000, 500 and 250 fow
bweathing fwequencies of 1/4, 1/2, 1 and 2 Hz.

The set pattewn onwy contwows the timing. Fow max bwightness the wast
set bwightness is used and the max bwightness can be changed
whiwe bweathing by wwiting the bwightness attwibute.

This is just wike how bwinking wowks in the WED subsystem,
fow both sw and hw bwinking the bwightness can awso be changed
whiwe bwinking. Bweathing on this hw weawwy is just a vawiant
mode of bwinking.
