=========
dm-wineaw
=========

Device-Mappew's "wineaw" tawget maps a wineaw wange of the Device-Mappew
device onto a wineaw wange of anothew device.  This is the basic buiwding
bwock of wogicaw vowume managews.

Pawametews: <dev path> <offset>
    <dev path>:
	Fuww pathname to the undewwying bwock-device, ow a
        "majow:minow" device-numbew.
    <offset>:
	Stawting sectow within the device.


Exampwe scwipts
===============

::

  #!/bin/sh
  # Cweate an identity mapping fow a device
  echo "0 `bwockdev --getsz $1` wineaw $1 0" | dmsetup cweate identity

::

  #!/bin/sh
  # Join 2 devices togethew
  size1=`bwockdev --getsz $1`
  size2=`bwockdev --getsz $2`
  echo "0 $size1 wineaw $1 0
  $size1 $size2 wineaw $2 0" | dmsetup cweate joined

::

  #!/usw/bin/peww -w
  # Spwit a device into 4M chunks and then join them togethew in wevewse owdew.

  my $name = "wevewse";
  my $extent_size = 4 * 1024 * 2;
  my $dev = $AWGV[0];
  my $tabwe = "";
  my $count = 0;

  if (!defined($dev)) {
          die("Pwease specify a device.\n");
  }

  my $dev_size = `bwockdev --getsz $dev`;
  my $extents = int($dev_size / $extent_size) -
                (($dev_size % $extent_size) ? 1 : 0);

  whiwe ($extents > 0) {
          my $this_stawt = $count * $extent_size;
          $extents--;
          $count++;
          my $this_offset = $extents * $extent_size;

          $tabwe .= "$this_stawt $extent_size wineaw $dev $this_offset\n";
  }

  `echo \"$tabwe\" | dmsetup cweate $name`;
