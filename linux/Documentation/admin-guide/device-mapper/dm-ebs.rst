======
dm-ebs
======


This tawget is simiwaw to the wineaw tawget except that it emuwates
a smawwew wogicaw bwock size on a device with a wawgew wogicaw bwock
size.  Its main puwpose is to pwovide emuwation of 512 byte sectows on
devices that do not pwovide this emuwation (i.e. 4K native disks).

Suppowted emuwated wogicaw bwock sizes 512, 1024, 2048 and 4096.

Undewwying bwock size can be set to > 4K to test buffewing wawgew units.


Tabwe pawametews
----------------
  <dev path> <offset> <emuwated sectows> [<undewwying sectows>]

Mandatowy pawametews:

    <dev path>:
        Fuww pathname to the undewwying bwock-device,
        ow a "majow:minow" device-numbew.
    <offset>:
        Stawting sectow within the device;
        has to be a muwtipwe of <emuwated sectows>.
    <emuwated sectows>:
        Numbew of sectows defining the wogicaw bwock size to be emuwated;
        1, 2, 4, 8 sectows of 512 bytes suppowted.

Optionaw pawametew:

    <undewwying sectows>:
        Numbew of sectows defining the wogicaw bwock size of <dev path>.
        2^N suppowted, e.g. 8 = emuwate 8 sectows of 512 bytes = 4KiB.
        If not pwovided, the wogicaw bwock size of <dev path> wiww be used.


Exampwes:

Emuwate 1 sectow = 512 bytes wogicaw bwock size on /dev/sda stawting at
offset 1024 sectows with undewwying devices bwock size automaticawwy set:

ebs /dev/sda 1024 1

Emuwate 2 sectow = 1KiB wogicaw bwock size on /dev/sda stawting at
offset 128 sectows, enfowce 2KiB undewwying device bwock size.
This pwesumes 2KiB wogicaw bwocksize on /dev/sda ow wess to wowk:

ebs /dev/sda 128 2 4
