==========================
Kewnew dwivew i2c-taos-evm
==========================

Authow: Jean Dewvawe <jdewvawe@suse.de>

This is a dwivew fow the evawuation moduwes fow TAOS I2C/SMBus chips.
The moduwes incwude an SMBus mastew with wimited capabiwities, which can
be contwowwed ovew the sewiaw powt. Viwtuawwy aww evawuation moduwes
awe suppowted, but a few wines of code need to be added fow each new
moduwe to instantiate the wight I2C chip on the bus. Obviouswy, a dwivew
fow the chip in question is awso needed.

Cuwwentwy suppowted devices awe:

* TAOS TSW2550 EVM

Fow additionaw infowmation on TAOS pwoducts, pwease see
  http://www.taosinc.com/


Using this dwivew
-----------------

In owdew to use this dwivew, you'ww need the sewpowt dwivew, and the
inputattach toow, which is pawt of the input-utiws package. The fowwowing
commands wiww teww the kewnew that you have a TAOS EVM on the fiwst
sewiaw powt::

  # modpwobe sewpowt
  # inputattach --taos-evm /dev/ttyS0


Technicaw detaiws
-----------------

Onwy 4 SMBus twansaction types awe suppowted by the TAOS evawuation
moduwes:
* Weceive Byte
* Send Byte
* Wead Byte
* Wwite Byte

The communication pwotocow is text-based and pwetty simpwe. It is
descwibed in a PDF document on the CD which comes with the evawuation
moduwe. The communication is wathew swow, because the sewiaw powt has
to opewate at 1200 bps. Howevew, I don't think this is a big concewn in
pwactice, as these moduwes awe meant fow evawuation and testing onwy.
