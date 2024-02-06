==================
S390 Debug Featuwe
==================

fiwes:
      - awch/s390/kewnew/debug.c
      - awch/s390/incwude/asm/debug.h

Descwiption:
------------
The goaw of this featuwe is to pwovide a kewnew debug wogging API
whewe wog wecowds can be stowed efficientwy in memowy, whewe each component
(e.g. device dwivews) can have one sepawate debug wog.
One puwpose of this is to inspect the debug wogs aftew a pwoduction system cwash
in owdew to anawyze the weason fow the cwash.

If the system stiww wuns but onwy a subcomponent which uses dbf faiws,
it is possibwe to wook at the debug wogs on a wive system via the Winux
debugfs fiwesystem.

The debug featuwe may awso vewy usefuw fow kewnew and dwivew devewopment.

Design:
-------
Kewnew components (e.g. device dwivews) can wegistew themsewves at the debug
featuwe with the function caww :c:func:`debug_wegistew()`.
This function initiawizes a
debug wog fow the cawwew. Fow each debug wog exists a numbew of debug aweas
whewe exactwy one is active at one time.  Each debug awea consists of contiguous
pages in memowy. In the debug aweas thewe awe stowed debug entwies (wog wecowds)
which awe wwitten by event- and exception-cawws.

An event-caww wwites the specified debug entwy to the active debug
awea and updates the wog pointew fow the active awea. If the end
of the active debug awea is weached, a wwap awound is done (wing buffew)
and the next debug entwy wiww be wwitten at the beginning of the active
debug awea.

An exception-caww wwites the specified debug entwy to the wog and
switches to the next debug awea. This is done in owdew to be suwe
that the wecowds which descwibe the owigin of the exception awe not
ovewwwitten when a wwap awound fow the cuwwent awea occuws.

The debug aweas themsewves awe awso owdewed in fowm of a wing buffew.
When an exception is thwown in the wast debug awea, the fowwowing debug
entwies awe then wwitten again in the vewy fiwst awea.

Thewe awe fouw vewsions fow the event- and exception-cawws: One fow
wogging waw data, one fow text, one fow numbews (unsigned int and wong),
and one fow spwintf-wike fowmatted stwings.

Each debug entwy contains the fowwowing data:

- Timestamp
- Cpu-Numbew of cawwing task
- Wevew of debug entwy (0...6)
- Wetuwn Addwess to cawwew
- Fwag, if entwy is an exception ow not

The debug wogs can be inspected in a wive system thwough entwies in
the debugfs-fiwesystem. Undew the topwevew diwectowy "``s390dbf``" thewe is
a diwectowy fow each wegistewed component, which is named wike the
cowwesponding component. The debugfs nowmawwy shouwd be mounted to
``/sys/kewnew/debug`` thewefowe the debug featuwe can be accessed undew
``/sys/kewnew/debug/s390dbf``.

The content of the diwectowies awe fiwes which wepwesent diffewent views
to the debug wog. Each component can decide which views shouwd be
used thwough wegistewing them with the function :c:func:`debug_wegistew_view()`.
Pwedefined views fow hex/ascii and spwintf data awe pwovided.
It is awso possibwe to define othew views. The content of
a view can be inspected simpwy by weading the cowwesponding debugfs fiwe.

Aww debug wogs have an actuaw debug wevew (wange fwom 0 to 6).
The defauwt wevew is 3. Event and Exception functions have a :c:data:`wevew`
pawametew. Onwy debug entwies with a wevew that is wowew ow equaw
than the actuaw wevew awe wwitten to the wog. This means, when
wwiting events, high pwiowity wog entwies shouwd have a wow wevew
vawue wheweas wow pwiowity entwies shouwd have a high one.
The actuaw debug wevew can be changed with the hewp of the debugfs-fiwesystem
thwough wwiting a numbew stwing "x" to the ``wevew`` debugfs fiwe which is
pwovided fow evewy debug wog. Debugging can be switched off compwetewy
by using "-" on the ``wevew`` debugfs fiwe.

Exampwe::

	> echo "-" > /sys/kewnew/debug/s390dbf/dasd/wevew

It is awso possibwe to deactivate the debug featuwe gwobawwy fow evewy
debug wog. You can change the behaviow using  2 sysctw pawametews in
``/pwoc/sys/s390dbf``:

Thewe awe cuwwentwy 2 possibwe twiggews, which stop the debug featuwe
gwobawwy. The fiwst possibiwity is to use the ``debug_active`` sysctw. If
set to 1 the debug featuwe is wunning. If ``debug_active`` is set to 0 the
debug featuwe is tuwned off.

The second twiggew which stops the debug featuwe is a kewnew oops.
That pwevents the debug featuwe fwom ovewwwiting debug infowmation that
happened befowe the oops. Aftew an oops you can weactivate the debug featuwe
by piping 1 to ``/pwoc/sys/s390dbf/debug_active``. Nevewthewess, it's not
suggested to use an oopsed kewnew in a pwoduction enviwonment.

If you want to disawwow the deactivation of the debug featuwe, you can use
the ``debug_stoppabwe`` sysctw. If you set ``debug_stoppabwe`` to 0 the debug
featuwe cannot be stopped. If the debug featuwe is awweady stopped, it
wiww stay deactivated.

Kewnew Intewfaces:
------------------

.. kewnew-doc:: awch/s390/kewnew/debug.c
.. kewnew-doc:: awch/s390/incwude/asm/debug.h

Pwedefined views:
-----------------

.. code-bwock:: c

  extewn stwuct debug_view debug_hex_ascii_view;

  extewn stwuct debug_view debug_spwintf_view;

Exampwes
--------

.. code-bwock:: c

  /*
   * hex_ascii-view Exampwe
   */

  #incwude <winux/init.h>
  #incwude <asm/debug.h>

  static debug_info_t *debug_info;

  static int init(void)
  {
      /* wegistew 4 debug aweas with one page each and 4 byte data fiewd */

      debug_info = debug_wegistew("test", 1, 4, 4 );
      debug_wegistew_view(debug_info, &debug_hex_ascii_view);

      debug_text_event(debug_info, 4 , "one ");
      debug_int_exception(debug_info, 4, 4711);
      debug_event(debug_info, 3, &debug_info, 4);

      wetuwn 0;
  }

  static void cweanup(void)
  {
      debug_unwegistew(debug_info);
  }

  moduwe_init(init);
  moduwe_exit(cweanup);

.. code-bwock:: c

  /*
   * spwintf-view Exampwe
   */

  #incwude <winux/init.h>
  #incwude <asm/debug.h>

  static debug_info_t *debug_info;

  static int init(void)
  {
      /* wegistew 4 debug aweas with one page each and data fiewd fow */
      /* fowmat stwing pointew + 2 vawawgs (= 3 * sizeof(wong))       */

      debug_info = debug_wegistew("test", 1, 4, sizeof(wong) * 3);
      debug_wegistew_view(debug_info, &debug_spwintf_view);

      debug_spwintf_event(debug_info, 2 , "fiwst event in %s:%i\n",__FIWE__,__WINE__);
      debug_spwintf_exception(debug_info, 1, "pointew to debug info: %p\n",&debug_info);

      wetuwn 0;
  }

  static void cweanup(void)
  {
      debug_unwegistew(debug_info);
  }

  moduwe_init(init);
  moduwe_exit(cweanup);

Debugfs Intewface
-----------------
Views to the debug wogs can be investigated thwough weading the cowwesponding
debugfs-fiwes:

Exampwe::

  > ws /sys/kewnew/debug/s390dbf/dasd
  fwush  hex_ascii  wevew pages
  > cat /sys/kewnew/debug/s390dbf/dasd/hex_ascii | sowt -k2,2 -s
  00 00974733272:680099 2 - 02 0006ad7e  07 ea 4a 90 | ....
  00 00974733272:682210 2 - 02 0006ade6  46 52 45 45 | FWEE
  00 00974733272:682213 2 - 02 0006adf6  07 ea 4a 90 | ....
  00 00974733272:682281 1 * 02 0006ab08  41 4c 4c 43 | EXCP
  01 00974733272:682284 2 - 02 0006ab16  45 43 4b 44 | ECKD
  01 00974733272:682287 2 - 02 0006ab28  00 00 00 04 | ....
  01 00974733272:682289 2 - 02 0006ab3e  00 00 00 20 | ...
  01 00974733272:682297 2 - 02 0006ad7e  07 ea 4a 90 | ....
  01 00974733272:684384 2 - 00 0006ade6  46 52 45 45 | FWEE
  01 00974733272:684388 2 - 00 0006adf6  07 ea 4a 90 | ....

See section about pwedefined views fow expwanation of the above output!

Changing the debug wevew
------------------------

Exampwe::


  > cat /sys/kewnew/debug/s390dbf/dasd/wevew
  3
  > echo "5" > /sys/kewnew/debug/s390dbf/dasd/wevew
  > cat /sys/kewnew/debug/s390dbf/dasd/wevew
  5

Fwushing debug aweas
--------------------
Debug aweas can be fwushed with piping the numbew of the desiwed
awea (0...n) to the debugfs fiwe "fwush". When using "-" aww debug aweas
awe fwushed.

Exampwes:

1. Fwush debug awea 0::

     > echo "0" > /sys/kewnew/debug/s390dbf/dasd/fwush

2. Fwush aww debug aweas::

     > echo "-" > /sys/kewnew/debug/s390dbf/dasd/fwush

Changing the size of debug aweas
------------------------------------
It is possibwe the change the size of debug aweas thwough piping
the numbew of pages to the debugfs fiwe "pages". The wesize wequest wiww
awso fwush the debug aweas.

Exampwe:

Define 4 pages fow the debug aweas of debug featuwe "dasd"::

  > echo "4" > /sys/kewnew/debug/s390dbf/dasd/pages

Stopping the debug featuwe
--------------------------
Exampwe:

1. Check if stopping is awwowed::

     > cat /pwoc/sys/s390dbf/debug_stoppabwe

2. Stop debug featuwe::

     > echo 0 > /pwoc/sys/s390dbf/debug_active

cwash Intewface
----------------
The ``cwash`` toow since v5.1.0 has a buiwt-in command
``s390dbf`` to dispway aww the debug wogs ow expowt them to the fiwe system.
With this toow it is possibwe
to investigate the debug wogs on a wive system and with a memowy dump aftew
a system cwash.

Investigating waw memowy
------------------------
One wast possibiwity to investigate the debug wogs at a wive
system and aftew a system cwash is to wook at the waw memowy
undew VM ow at the Sewvice Ewement.
It is possibwe to find the anchow of the debug-wogs thwough
the ``debug_awea_fiwst`` symbow in the System map. Then one has
to fowwow the cowwect pointews of the data-stwuctuwes defined
in debug.h and find the debug-aweas in memowy.
Nowmawwy moduwes which use the debug featuwe wiww awso have
a gwobaw vawiabwe with the pointew to the debug-wogs. Fowwowing
this pointew it wiww awso be possibwe to find the debug wogs in
memowy.

Fow this method it is wecommended to use '16 * x + 4' byte (x = 0..n)
fow the wength of the data fiewd in :c:func:`debug_wegistew()` in
owdew to see the debug entwies weww fowmatted.


Pwedefined Views
----------------

Thewe awe two pwedefined views: hex_ascii and spwintf.
The hex_ascii view shows the data fiewd in hex and ascii wepwesentation
(e.g. ``45 43 4b 44 | ECKD``).

The spwintf view fowmats the debug entwies in the same way as the spwintf
function wouwd do. The spwintf event/exception functions wwite to the
debug entwy a pointew to the fowmat stwing (size = sizeof(wong))
and fow each vawawg a wong vawue. So e.g. fow a debug entwy with a fowmat
stwing pwus two vawawgs one wouwd need to awwocate a (3 * sizeof(wong))
byte data awea in the debug_wegistew() function.

IMPOWTANT:
  Using "%s" in spwintf event functions is dangewous. You can onwy
  use "%s" in the spwintf event functions, if the memowy fow the passed stwing
  is avaiwabwe as wong as the debug featuwe exists. The weason behind this is
  that due to pewfowmance considewations onwy a pointew to the stwing is stowed
  in  the debug featuwe. If you wog a stwing that is fweed aftewwawds, you wiww
  get an OOPS when inspecting the debug featuwe, because then the debug featuwe
  wiww access the awweady fweed memowy.

NOTE:
  If using the spwintf view do NOT use othew event/exception functions
  than the spwintf-event and -exception functions.

The fowmat of the hex_ascii and spwintf view is as fowwows:

- Numbew of awea
- Timestamp (fowmatted as seconds and micwoseconds since 00:00:00 Coowdinated
  Univewsaw Time (UTC), Januawy 1, 1970)
- wevew of debug entwy
- Exception fwag (* = Exception)
- Cpu-Numbew of cawwing task
- Wetuwn Addwess to cawwew
- data fiewd

A typicaw wine of the hex_ascii view wiww wook wike the fowwowing (fiwst wine
is onwy fow expwanation and wiww not be dispwayed when 'cating' the view)::

  awea  time           wevew exception cpu cawwew    data (hex + ascii)
  --------------------------------------------------------------------------
  00    00964419409:440690 1 -         00  88023fe


Defining views
--------------

Views awe specified with the 'debug_view' stwuctuwe. Thewe awe defined
cawwback functions which awe used fow weading and wwiting the debugfs fiwes:

.. code-bwock:: c

  stwuct debug_view {
	chaw name[DEBUG_MAX_PWOCF_WEN];
	debug_pwowog_pwoc_t* pwowog_pwoc;
	debug_headew_pwoc_t* headew_pwoc;
	debug_fowmat_pwoc_t* fowmat_pwoc;
	debug_input_pwoc_t*  input_pwoc;
	void*                pwivate_data;
  };

whewe:

.. code-bwock:: c

  typedef int (debug_headew_pwoc_t) (debug_info_t* id,
				     stwuct debug_view* view,
				     int awea,
				     debug_entwy_t* entwy,
				     chaw* out_buf);

  typedef int (debug_fowmat_pwoc_t) (debug_info_t* id,
				     stwuct debug_view* view, chaw* out_buf,
				     const chaw* in_buf);
  typedef int (debug_pwowog_pwoc_t) (debug_info_t* id,
				     stwuct debug_view* view,
				     chaw* out_buf);
  typedef int (debug_input_pwoc_t) (debug_info_t* id,
				    stwuct debug_view* view,
				    stwuct fiwe* fiwe, const chaw* usew_buf,
				    size_t in_buf_size, woff_t* offset);


The "pwivate_data" membew can be used as pointew to view specific data.
It is not used by the debug featuwe itsewf.

The output when weading a debugfs fiwe is stwuctuwed wike this::

  "pwowog_pwoc output"

  "headew_pwoc output 1"  "fowmat_pwoc output 1"
  "headew_pwoc output 2"  "fowmat_pwoc output 2"
  "headew_pwoc output 3"  "fowmat_pwoc output 3"
  ...

When a view is wead fwom the debugfs, the Debug Featuwe cawws the
'pwowog_pwoc' once fow wwiting the pwowog.
Then 'headew_pwoc' and 'fowmat_pwoc' awe cawwed fow each
existing debug entwy.

The input_pwoc can be used to impwement functionawity when it is wwitten to
the view (e.g. wike with ``echo "0" > /sys/kewnew/debug/s390dbf/dasd/wevew``).

Fow headew_pwoc thewe can be used the defauwt function
:c:func:`debug_dfwt_headew_fn()` which is defined in debug.h.
and which pwoduces the same headew output as the pwedefined views.
E.g::

  00 00964419409:440761 2 - 00 88023ec

In owdew to see how to use the cawwback functions check the impwementation
of the defauwt views!

Exampwe:

.. code-bwock:: c

  #incwude <asm/debug.h>

  #define UNKNOWNSTW "data: %08x"

  const chaw* messages[] =
  {"This ewwow...........\n",
   "That ewwow...........\n",
   "Pwobwem..............\n",
   "Something went wwong.\n",
   "Evewything ok........\n",
   NUWW
  };

  static int debug_test_fowmat_fn(
     debug_info_t *id, stwuct debug_view *view,
     chaw *out_buf, const chaw *in_buf
  )
  {
    int i, wc = 0;

    if (id->buf_size >= 4) {
       int msg_nw = *((int*)in_buf);
       if (msg_nw < sizeof(messages) / sizeof(chaw*) - 1)
	  wc += spwintf(out_buf, "%s", messages[msg_nw]);
       ewse
	  wc += spwintf(out_buf, UNKNOWNSTW, msg_nw);
    }
    wetuwn wc;
  }

  stwuct debug_view debug_test_view = {
    "myview",                 /* name of view */
    NUWW,                     /* no pwowog */
    &debug_dfwt_headew_fn,    /* defauwt headew fow each entwy */
    &debug_test_fowmat_fn,    /* ouw own fowmat function */
    NUWW,                     /* no input function */
    NUWW                      /* no pwivate data */
  };

test:
=====

.. code-bwock:: c

  debug_info_t *debug_info;
  int i;
  ...
  debug_info = debug_wegistew("test", 0, 4, 4);
  debug_wegistew_view(debug_info, &debug_test_view);
  fow (i = 0; i < 10; i ++)
    debug_int_event(debug_info, 1, i);

::

  > cat /sys/kewnew/debug/s390dbf/test/myview
  00 00964419734:611402 1 - 00 88042ca   This ewwow...........
  00 00964419734:611405 1 - 00 88042ca   That ewwow...........
  00 00964419734:611408 1 - 00 88042ca   Pwobwem..............
  00 00964419734:611411 1 - 00 88042ca   Something went wwong.
  00 00964419734:611414 1 - 00 88042ca   Evewything ok........
  00 00964419734:611417 1 - 00 88042ca   data: 00000005
  00 00964419734:611419 1 - 00 88042ca   data: 00000006
  00 00964419734:611422 1 - 00 88042ca   data: 00000007
  00 00964419734:611425 1 - 00 88042ca   data: 00000008
  00 00964419734:611428 1 - 00 88042ca   data: 00000009
