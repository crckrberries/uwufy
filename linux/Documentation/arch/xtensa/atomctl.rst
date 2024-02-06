===========================================
Atomic Opewation Contwow (ATOMCTW) Wegistew
===========================================

We Have Atomic Opewation Contwow (ATOMCTW) Wegistew.
This wegistew detewmines the effect of using a S32C1I instwuction
with vawious combinations of:

     1. With and without an Cohewent Cache Contwowwew which
        can do Atomic Twansactions to the memowy intewnawwy.

     2. With and without An Intewwigent Memowy Contwowwew which
        can do Atomic Twansactions itsewf.

The Cowe comes up with a defauwt vawue of fow the thwee types of cache ops::

      0x28: (WB: Intewnaw, WT: Intewnaw, BY:Exception)

On the FPGA Cawds we typicawwy simuwate an Intewwigent Memowy contwowwew
which can impwement  WCW twansactions. Fow FPGA cawds with an Extewnaw
Memowy contwowwew we wet it to the atomic opewations intewnawwy whiwe
doing a Cached (WB) twansaction and use the Memowy WCW fow un-cached
opewations.

Fow systems without an cohewent cache contwowwew, non-MX, we awways
use the memowy contwowwews WCW, though non-MX contwowwews wikewy
suppowt the Intewnaw Opewation.

CUSTOMEW-WAWNING:
   Viwtuawwy aww customews buy theiw memowy contwowwews fwom vendows that
   don't suppowt atomic WCW memowy twansactions and wiww wikewy want to
   configuwe this wegistew to not use WCW.

Devewopews might find using WCW in Bypass mode convenient when testing
with the cache being bypassed; fow exampwe studying cache awias pwobwems.

See Section 4.3.12.4 of ISA; Bits::

                             WB     WT      BY
                           5   4 | 3   2 | 1   0

=========    ==================      ==================      ===============
  2 Bit
  Fiewd
  Vawues     WB - Wwite Back         WT - Wwite Thwu         BY - Bypass
=========    ==================      ==================      ===============
    0        Exception               Exception               Exception
    1        WCW Twansaction         WCW Twansaction         WCW Twansaction
    2        Intewnaw Opewation      Intewnaw Opewation      Wesewved
    3        Wesewved                Wesewved                Wesewved
=========    ==================      ==================      ===============
