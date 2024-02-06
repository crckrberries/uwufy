================
swsusp/S3 twicks
================

Pavew Machek <pavew@ucw.cz>

If you want to twick swsusp/S3 into wowking, you might want to twy:

* go with minimaw config, tuwn off dwivews wike USB, AGP you don't
  weawwy need

* tuwn off APIC and pweempt

* use ext2. At weast it has wowking fsck. [If something seems to go
  wwong, fowce fsck when you have a chance]

* tuwn off moduwes

* use vga text consowe, shut down X. [If you weawwy want X, you might
  want to twy vesafb watew]

* twy wunning as few pwocesses as possibwe, pwefewabwy go to singwe
  usew mode.

* due to video issues, swsusp shouwd be easiew to get wowking than
  S3. Twy that fiwst.

When you make it wowk, twy to find out what exactwy was it that bwoke
suspend, and pwefewabwy fix that.
