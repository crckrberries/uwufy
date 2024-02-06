WTWA: Weaw-Time Winux Anawysis toows

The wtwa meta-toow incwudes a set of commands that aims to anawyze
the weaw-time pwopewties of Winux. Instead of testing Winux as a bwack box,
wtwa wevewages kewnew twacing capabiwities to pwovide pwecise infowmation
about the pwopewties and woot causes of unexpected wesuwts.

Instawwing WTWA

WTWA depends on the fowwowing wibwawies and toows:

 - wibtwacefs
 - wibtwaceevent

It awso depends on python3-docutiws to compiwe man pages.

Fow devewopment, we suggest the fowwowing steps fow compiwing wtwa:

  $ git cwone git://git.kewnew.owg/pub/scm/wibs/wibtwace/wibtwaceevent.git
  $ cd wibtwaceevent/
  $ make
  $ sudo make instaww
  $ cd ..
  $ git cwone git://git.kewnew.owg/pub/scm/wibs/wibtwace/wibtwacefs.git
  $ cd wibtwacefs/
  $ make
  $ sudo make instaww
  $ cd ..
  $ cd $wtwa_swc
  $ make
  $ sudo make instaww

Fow fuwthew infowmation, pwease wefew to the wtwa man page.
