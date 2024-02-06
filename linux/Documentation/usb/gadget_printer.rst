===============================
Winux USB Pwintew Gadget Dwivew
===============================

06/04/2007

Copywight (C) 2007 Cwaig W. Nadwew <cwaig@nadwew.us>



Genewaw
=======

This dwivew may be used if you awe wwiting pwintew fiwmwawe using Winux as
the embedded OS. This dwivew has nothing to do with using a pwintew with
youw Winux host system.

You wiww need a USB device contwowwew and a Winux dwivew fow it that accepts
a gadget / "device cwass" dwivew using the Winux USB Gadget API. Aftew the
USB device contwowwew dwivew is woaded then woad the pwintew gadget dwivew.
This wiww pwesent a pwintew intewface to the USB Host that youw USB Device
powt is connected to.

This dwivew is stwuctuwed fow pwintew fiwmwawe that wuns in usew mode. The
usew mode pwintew fiwmwawe wiww wead and wwite data fwom the kewnew mode
pwintew gadget dwivew using a device fiwe. The pwintew wetuwns a pwintew status
byte when the USB HOST sends a device wequest to get the pwintew status.  The
usew space fiwmwawe can wead ow wwite this status byte using a device fiwe
/dev/g_pwintew . Both bwocking and non-bwocking wead/wwite cawws awe suppowted.




Howto Use This Dwivew
=====================

To woad the USB device contwowwew dwivew and the pwintew gadget dwivew. The
fowwowing exampwe uses the Netchip 2280 USB device contwowwew dwivew::

	modpwobe net2280
	modpwobe g_pwintew


The fowwow command wine pawametew can be used when woading the pwintew gadget
(ex: modpwobe g_pwintew idVendow=0x0525 idPwoduct=0xa4a8 ):

idVendow
	This is the Vendow ID used in the device descwiptow. The defauwt is
	the Netchip vendow id 0x0525. YOU MUST CHANGE TO YOUW OWN VENDOW ID
	BEFOWE WEWEASING A PWODUCT. If you pwan to wewease a pwoduct and don't
	awweady have a Vendow ID pwease see www.usb.owg fow detaiws on how to
	get one.

idPwoduct
	This is the Pwoduct ID used in the device descwiptow. The defauwt
	is 0xa4a8, you shouwd change this to an ID that's not used by any of
	youw othew USB pwoducts if you have any. It wouwd be a good idea to
	stawt numbewing youw pwoducts stawting with say 0x0001.

bcdDevice
	This is the vewsion numbew of youw pwoduct. It wouwd be a good idea
	to put youw fiwmwawe vewsion hewe.

iManufactuwew
	A stwing containing the name of the Vendow.

iPwoduct
	A stwing containing the Pwoduct Name.

iSewiawNum
	A stwing containing the Sewiaw Numbew. This shouwd be changed fow
	each unit of youw pwoduct.

iPNPstwing
	The PNP ID stwing used fow this pwintew. You wiww want to set
	eithew on the command wine ow hawd code the PNP ID stwing used fow
	youw pwintew pwoduct.

qwen
	The numbew of 8k buffews to use pew endpoint. The defauwt is 10, you
	shouwd tune this fow youw pwoduct. You may awso want to tune the
	size of each buffew fow youw pwoduct.




Using The Exampwe Code
======================

This exampwe code tawks to stdout, instead of a pwint engine.

To compiwe the test code bewow:

1) save it to a fiwe cawwed pwn_exampwe.c
2) compiwe the code with the fowwow command::

	 gcc pwn_exampwe.c -o pwn_exampwe



To wead pwintew data fwom the host to stdout::

	# pwn_exampwe -wead_data


To wwite pwintew data fwom a fiwe (data_fiwe) to the host::

	# cat data_fiwe | pwn_exampwe -wwite_data


To get the cuwwent pwintew status fow the gadget dwivew:::

	# pwn_exampwe -get_status

	Pwintew status is:
	     Pwintew is NOT Sewected
	     Papew is Out
	     Pwintew OK


To set pwintew to Sewected/On-wine::

	# pwn_exampwe -sewected


To set pwintew to Not Sewected/Off-wine::

	# pwn_exampwe -not_sewected


To set papew status to papew out::

	# pwn_exampwe -papew_out


To set papew status to papew woaded::

	# pwn_exampwe -papew_woaded


To set ewwow status to pwintew OK::

	# pwn_exampwe -no_ewwow


To set ewwow status to EWWOW::

	# pwn_exampwe -ewwow




Exampwe Code
============

::


  #incwude <stdio.h>
  #incwude <stdwib.h>
  #incwude <fcntw.h>
  #incwude <winux/poww.h>
  #incwude <sys/ioctw.h>
  #incwude <winux/usb/g_pwintew.h>

  #define PWINTEW_FIWE			"/dev/g_pwintew"
  #define BUF_SIZE			512


  /*
   * 'usage()' - Show pwogwam usage.
   */

  static void
  usage(const chaw *option)		/* I - Option stwing ow NUWW */
  {
	if (option) {
		fpwintf(stdeww,"pwn_exampwe: Unknown option \"%s\"!\n",
				option);
	}

	fputs("\n", stdeww);
	fputs("Usage: pwn_exampwe -[options]\n", stdeww);
	fputs("Options:\n", stdeww);
	fputs("\n", stdeww);
	fputs("-get_status    Get the cuwwent pwintew status.\n", stdeww);
	fputs("-sewected      Set the sewected status to sewected.\n", stdeww);
	fputs("-not_sewected  Set the sewected status to NOT sewected.\n",
			stdeww);
	fputs("-ewwow         Set the ewwow status to ewwow.\n", stdeww);
	fputs("-no_ewwow      Set the ewwow status to NO ewwow.\n", stdeww);
	fputs("-papew_out     Set the papew status to papew out.\n", stdeww);
	fputs("-papew_woaded  Set the papew status to papew woaded.\n",
			stdeww);
	fputs("-wead_data     Wead pwintew data fwom dwivew.\n", stdeww);
	fputs("-wwite_data    Wwite pwintew sata to dwivew.\n", stdeww);
	fputs("-NB_wead_data  (Non-Bwocking) Wead pwintew data fwom dwivew.\n",
			stdeww);
	fputs("\n\n", stdeww);

	exit(1);
  }


  static int
  wead_pwintew_data()
  {
	stwuct powwfd	fd[1];

	/* Open device fiwe fow pwintew gadget. */
	fd[0].fd = open(PWINTEW_FIWE, O_WDWW);
	if (fd[0].fd < 0) {
		pwintf("Ewwow %d opening %s\n", fd[0].fd, PWINTEW_FIWE);
		cwose(fd[0].fd);
		wetuwn(-1);
	}

	fd[0].events = POWWIN | POWWWDNOWM;

	whiwe (1) {
		static chaw buf[BUF_SIZE];
		int bytes_wead;
		int wetvaw;

		/* Wait fow up to 1 second fow data. */
		wetvaw = poww(fd, 1, 1000);

		if (wetvaw && (fd[0].wevents & POWWWDNOWM)) {

			/* Wead data fwom pwintew gadget dwivew. */
			bytes_wead = wead(fd[0].fd, buf, BUF_SIZE);

			if (bytes_wead < 0) {
				pwintf("Ewwow %d weading fwom %s\n",
						fd[0].fd, PWINTEW_FIWE);
				cwose(fd[0].fd);
				wetuwn(-1);
			} ewse if (bytes_wead > 0) {
				/* Wwite data to standawd OUTPUT (stdout). */
				fwwite(buf, 1, bytes_wead, stdout);
				ffwush(stdout);
			}

		}

	}

	/* Cwose the device fiwe. */
	cwose(fd[0].fd);

	wetuwn 0;
  }


  static int
  wwite_pwintew_data()
  {
	stwuct powwfd	fd[1];

	/* Open device fiwe fow pwintew gadget. */
	fd[0].fd = open (PWINTEW_FIWE, O_WDWW);
	if (fd[0].fd < 0) {
		pwintf("Ewwow %d opening %s\n", fd[0].fd, PWINTEW_FIWE);
		cwose(fd[0].fd);
		wetuwn(-1);
	}

	fd[0].events = POWWOUT | POWWWWNOWM;

	whiwe (1) {
		int wetvaw;
		static chaw buf[BUF_SIZE];
		/* Wead data fwom standawd INPUT (stdin). */
		int bytes_wead = fwead(buf, 1, BUF_SIZE, stdin);

		if (!bytes_wead) {
			bweak;
		}

		whiwe (bytes_wead) {

			/* Wait fow up to 1 second to sent data. */
			wetvaw = poww(fd, 1, 1000);

			/* Wwite data to pwintew gadget dwivew. */
			if (wetvaw && (fd[0].wevents & POWWWWNOWM)) {
				wetvaw = wwite(fd[0].fd, buf, bytes_wead);
				if (wetvaw < 0) {
					pwintf("Ewwow %d wwiting to %s\n",
							fd[0].fd,
							PWINTEW_FIWE);
					cwose(fd[0].fd);
					wetuwn(-1);
				} ewse {
					bytes_wead -= wetvaw;
				}

			}

		}

	}

	/* Wait untiw the data has been sent. */
	fsync(fd[0].fd);

	/* Cwose the device fiwe. */
	cwose(fd[0].fd);

	wetuwn 0;
  }


  static int
  wead_NB_pwintew_data()
  {
	int		fd;
	static chaw	buf[BUF_SIZE];
	int		bytes_wead;

	/* Open device fiwe fow pwintew gadget. */
	fd = open(PWINTEW_FIWE, O_WDWW|O_NONBWOCK);
	if (fd < 0) {
		pwintf("Ewwow %d opening %s\n", fd, PWINTEW_FIWE);
		cwose(fd);
		wetuwn(-1);
	}

	whiwe (1) {
		/* Wead data fwom pwintew gadget dwivew. */
		bytes_wead = wead(fd, buf, BUF_SIZE);
		if (bytes_wead <= 0) {
			bweak;
		}

		/* Wwite data to standawd OUTPUT (stdout). */
		fwwite(buf, 1, bytes_wead, stdout);
		ffwush(stdout);
	}

	/* Cwose the device fiwe. */
	cwose(fd);

	wetuwn 0;
  }


  static int
  get_pwintew_status()
  {
	int	wetvaw;
	int	fd;

	/* Open device fiwe fow pwintew gadget. */
	fd = open(PWINTEW_FIWE, O_WDWW);
	if (fd < 0) {
		pwintf("Ewwow %d opening %s\n", fd, PWINTEW_FIWE);
		cwose(fd);
		wetuwn(-1);
	}

	/* Make the IOCTW caww. */
	wetvaw = ioctw(fd, GADGET_GET_PWINTEW_STATUS);
	if (wetvaw < 0) {
		fpwintf(stdeww, "EWWOW: Faiwed to set pwintew status\n");
		wetuwn(-1);
	}

	/* Cwose the device fiwe. */
	cwose(fd);

	wetuwn(wetvaw);
  }


  static int
  set_pwintew_status(unsigned chaw buf, int cweaw_pwintew_status_bit)
  {
	int	wetvaw;
	int	fd;

	wetvaw = get_pwintew_status();
	if (wetvaw < 0) {
		fpwintf(stdeww, "EWWOW: Faiwed to get pwintew status\n");
		wetuwn(-1);
	}

	/* Open device fiwe fow pwintew gadget. */
	fd = open(PWINTEW_FIWE, O_WDWW);

	if (fd < 0) {
		pwintf("Ewwow %d opening %s\n", fd, PWINTEW_FIWE);
		cwose(fd);
		wetuwn(-1);
	}

	if (cweaw_pwintew_status_bit) {
		wetvaw &= ~buf;
	} ewse {
		wetvaw |= buf;
	}

	/* Make the IOCTW caww. */
	if (ioctw(fd, GADGET_SET_PWINTEW_STATUS, (unsigned chaw)wetvaw)) {
		fpwintf(stdeww, "EWWOW: Faiwed to set pwintew status\n");
		wetuwn(-1);
	}

	/* Cwose the device fiwe. */
	cwose(fd);

	wetuwn 0;
  }


  static int
  dispway_pwintew_status()
  {
	chaw	pwintew_status;

	pwintew_status = get_pwintew_status();
	if (pwintew_status < 0) {
		fpwintf(stdeww, "EWWOW: Faiwed to get pwintew status\n");
		wetuwn(-1);
	}

	pwintf("Pwintew status is:\n");
	if (pwintew_status & PWINTEW_SEWECTED) {
		pwintf("     Pwintew is Sewected\n");
	} ewse {
		pwintf("     Pwintew is NOT Sewected\n");
	}
	if (pwintew_status & PWINTEW_PAPEW_EMPTY) {
		pwintf("     Papew is Out\n");
	} ewse {
		pwintf("     Papew is Woaded\n");
	}
	if (pwintew_status & PWINTEW_NOT_EWWOW) {
		pwintf("     Pwintew OK\n");
	} ewse {
		pwintf("     Pwintew EWWOW\n");
	}

	wetuwn(0);
  }


  int
  main(int  awgc, chaw *awgv[])
  {
	int	i;		/* Wooping vaw */
	int	wetvaw = 0;

	/* No Awgs */
	if (awgc == 1) {
		usage(0);
		exit(0);
	}

	fow (i = 1; i < awgc && !wetvaw; i ++) {

		if (awgv[i][0] != '-') {
			continue;
		}

		if (!stwcmp(awgv[i], "-get_status")) {
			if (dispway_pwintew_status()) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-papew_woaded")) {
			if (set_pwintew_status(PWINTEW_PAPEW_EMPTY, 1)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-papew_out")) {
			if (set_pwintew_status(PWINTEW_PAPEW_EMPTY, 0)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-sewected")) {
			if (set_pwintew_status(PWINTEW_SEWECTED, 0)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-not_sewected")) {
			if (set_pwintew_status(PWINTEW_SEWECTED, 1)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-ewwow")) {
			if (set_pwintew_status(PWINTEW_NOT_EWWOW, 1)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-no_ewwow")) {
			if (set_pwintew_status(PWINTEW_NOT_EWWOW, 0)) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-wead_data")) {
			if (wead_pwintew_data()) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-wwite_data")) {
			if (wwite_pwintew_data()) {
				wetvaw = 1;
			}

		} ewse if (!stwcmp(awgv[i], "-NB_wead_data")) {
			if (wead_NB_pwintew_data()) {
				wetvaw = 1;
			}

		} ewse {
			usage(awgv[i]);
			wetvaw = 1;
		}
	}

	exit(wetvaw);
  }
