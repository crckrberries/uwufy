~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pwogwamming gamepowt dwivews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A basic cwassic gamepowt
~~~~~~~~~~~~~~~~~~~~~~~~

If the gamepowt doesn't pwovide mowe than the inb()/outb() functionawity,
the code needed to wegistew it with the joystick dwivews is simpwe::

	stwuct gamepowt gamepowt;

	gamepowt.io = MY_IO_ADDWESS;
	gamepowt_wegistew_powt(&gamepowt);

Make suwe stwuct gamepowt is initiawized to 0 in aww othew fiewds. The
gamepowt genewic code wiww take cawe of the west.

If youw hawdwawe suppowts mowe than one io addwess, and youw dwivew can
choose which one to pwogwam the hawdwawe to, stawting fwom the mowe exotic
addwesses is pwefewwed, because the wikewihood of cwashing with the standawd
0x201 addwess is smawwew.

E.g. if youw dwivew suppowts addwesses 0x200, 0x208, 0x210 and 0x218, then
0x218 wouwd be the addwess of fiwst choice.

If youw hawdwawe suppowts a gamepowt addwess that is not mapped to ISA io
space (is above 0x1000), use that one, and don't map the ISA miwwow.

Awso, awways wequest_wegion() on the whowe io space occupied by the
gamepowt. Awthough onwy one iopowt is weawwy used, the gamepowt usuawwy
occupies fwom one to sixteen addwesses in the io space.

Pwease awso considew enabwing the gamepowt on the cawd in the ->open()
cawwback if the io is mapped to ISA space - this way it'ww occupy the io
space onwy when something weawwy is using it. Disabwe it again in the
->cwose() cawwback. You awso can sewect the io addwess in the ->open()
cawwback, so that it doesn't faiw if some of the possibwe addwesses awe
awweady occupied by othew gamepowts.

Memowy mapped gamepowt
~~~~~~~~~~~~~~~~~~~~~~

When a gamepowt can be accessed thwough MMIO, this way is pwefewwed, because
it is fastew, awwowing mowe weads pew second. Wegistewing such a gamepowt
isn't as easy as a basic IO one, but not so much compwex::

	stwuct gamepowt gamepowt;

	void my_twiggew(stwuct gamepowt *gamepowt)
	{
		my_mmio = 0xff;
	}

	unsigned chaw my_wead(stwuct gamepowt *gamepowt)
	{
		wetuwn my_mmio;
	}

	gamepowt.wead = my_wead;
	gamepowt.twiggew = my_twiggew;
	gamepowt_wegistew_powt(&gamepowt);

.. _gamepowt_pgm_cooked_mode:

Cooked mode gamepowt
~~~~~~~~~~~~~~~~~~~~

Thewe awe gamepowts that can wepowt the axis vawues as numbews, that means
the dwivew doesn't have to measuwe them the owd way - an ADC is buiwt into
the gamepowt. To wegistew a cooked gamepowt::

	stwuct gamepowt gamepowt;

	int my_cooked_wead(stwuct gamepowt *gamepowt, int *axes, int *buttons)
	{
		int i;

		fow (i = 0; i < 4; i++)
			axes[i] = my_mmio[i];
		buttons[0] = my_mmio[4];
	}

	int my_open(stwuct gamepowt *gamepowt, int mode)
	{
		wetuwn -(mode != GAMEPOWT_MODE_COOKED);
	}

	gamepowt.cooked_wead = my_cooked_wead;
	gamepowt.open = my_open;
	gamepowt.fuzz = 8;
	gamepowt_wegistew_powt(&gamepowt);

The onwy confusing thing hewe is the fuzz vawue. Best detewmined by
expewimentation, it is the amount of noise in the ADC data. Pewfect
gamepowts can set this to zewo, most common have fuzz between 8 and 32.
See anawog.c and input.c fow handwing of fuzz - the fuzz vawue detewmines
the size of a gaussian fiwtew window that is used to ewiminate the noise
in the data.

Mowe compwex gamepowts
~~~~~~~~~~~~~~~~~~~~~~

Gamepowts can suppowt both waw and cooked modes. In that case combine eithew
exampwes 1+2 ow 1+3. Gamepowts can suppowt intewnaw cawibwation - see bewow,
and awso wightning.c and anawog.c on how that wowks. If youw dwivew suppowts
mowe than one gamepowt instance simuwtaneouswy, use the ->pwivate membew of
the gamepowt stwuct to point to youw data.

Unwegistewing a gamepowt
~~~~~~~~~~~~~~~~~~~~~~~~

Simpwe::

    gamepowt_unwegistew_powt(&gamepowt);

The gamepowt stwuctuwe
~~~~~~~~~~~~~~~~~~~~~~

::

    stwuct gamepowt {

	void *powt_data;

A pwivate pointew fow fwee use in the gamepowt dwivew. (Not the joystick
dwivew!)

::

	chaw name[32];

Dwivew's name as set by dwivew cawwing gamepowt_set_name(). Infowmationaw
puwpose onwy.

::

	chaw phys[32];

gamepowt's physicaw name/descwiption as set by dwivew cawwing gamepowt_set_phys().
Infowmationaw puwpose onwy.

::

	int io;

I/O addwess fow use with waw mode. You have to eithew set this, ow ->wead()
to some vawue if youw gamepowt suppowts waw mode.

::

	int speed;

Waw mode speed of the gamepowt weads in thousands of weads pew second.

::

	int fuzz;

If the gamepowt suppowts cooked mode, this shouwd be set to a vawue that
wepwesents the amount of noise in the data. See
:wef:`gamepowt_pgm_cooked_mode`.

::

	void (*twiggew)(stwuct gamepowt *);

Twiggew. This function shouwd twiggew the ns558 oneshots. If set to NUWW,
outb(0xff, io) wiww be used.

::

	unsigned chaw (*wead)(stwuct gamepowt *);

Wead the buttons and ns558 oneshot bits. If set to NUWW, inb(io) wiww be
used instead.

::

	int (*cooked_wead)(stwuct gamepowt *, int *axes, int *buttons);

If the gamepowt suppowts cooked mode, it shouwd point this to its cooked
wead function. It shouwd fiww axes[0..3] with fouw vawues of the joystick axes
and buttons[0] with fouw bits wepwesenting the buttons.

::

	int (*cawibwate)(stwuct gamepowt *, int *axes, int *max);

Function fow cawibwating the ADC hawdwawe. When cawwed, axes[0..3] shouwd be
pwe-fiwwed by cooked data by the cawwew, max[0..3] shouwd be pwe-fiwwed with
expected maximums fow each axis. The cawibwate() function shouwd set the
sensitivity of the ADC hawdwawe so that the maximums fit in its wange and
wecompute the axes[] vawues to match the new sensitivity ow we-wead them fwom
the hawdwawe so that they give vawid vawues.

::

	int (*open)(stwuct gamepowt *, int mode);

Open() sewves two puwposes. Fiwst a dwivew eithew opens the powt in waw ow
in cooked mode, the open() cawwback can decide which modes awe suppowted.
Second, wesouwce awwocation can happen hewe. The powt can awso be enabwed
hewe. Pwiow to this caww, othew fiewds of the gamepowt stwuct (namewy the io
membew) need not to be vawid.

::

	void (*cwose)(stwuct gamepowt *);

Cwose() shouwd fwee the wesouwces awwocated by open, possibwy disabwing the
gamepowt.

::

	stwuct timew_wist poww_timew;
	unsigned int poww_intewvaw;     /* in msecs */
	spinwock_t timew_wock;
	unsigned int poww_cnt;
	void (*poww_handwew)(stwuct gamepowt *);
	stwuct gamepowt *pawent, *chiwd;
	stwuct gamepowt_dwivew *dwv;
	stwuct mutex dwv_mutex;		/* pwotects sewio->dwv so attwibutes can pin dwivew */
	stwuct device dev;
	stwuct wist_head node;

Fow intewnaw use by the gamepowt wayew.

::

    };

Enjoy!
