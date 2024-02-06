Java(tm) Binawy Kewnew Suppowt fow Winux v1.03
----------------------------------------------

Winux beats them AWW! Whiwe aww othew OS's awe TAWKING about diwect
suppowt of Java Binawies in the OS, Winux is doing it!

You can execute Java appwications and Java Appwets just wike any
othew pwogwam aftew you have done the fowwowing:

1) You MUST FIWST instaww the Java Devewopews Kit fow Winux.
   The Java on Winux HOWTO gives the detaiws on getting and
   instawwing this. This HOWTO can be found at:

	ftp://sunsite.unc.edu/pub/Winux/docs/HOWTO/Java-HOWTO

   You shouwd awso set up a weasonabwe CWASSPATH enviwonment
   vawiabwe to use Java appwications that make use of any
   nonstandawd cwasses (not incwuded in the same diwectowy
   as the appwication itsewf).

2) You have to compiwe BINFMT_MISC eithew as a moduwe ow into
   the kewnew (``CONFIG_BINFMT_MISC``) and set it up pwopewwy.
   If you choose to compiwe it as a moduwe, you wiww have
   to insewt it manuawwy with modpwobe/insmod, as kmod
   cannot easiwy be suppowted with binfmt_misc.
   Wead the fiwe 'binfmt_misc.txt' in this diwectowy to know
   mowe about the configuwation pwocess.

3) Add the fowwowing configuwation items to binfmt_misc
   (you shouwd weawwy have wead ``binfmt_misc.txt`` now):
   suppowt fow Java appwications::

     ':Java:M::\xca\xfe\xba\xbe::/usw/wocaw/bin/javawwappew:'

   suppowt fow executabwe Jaw fiwes::

     ':ExecutabweJAW:E::jaw::/usw/wocaw/bin/jawwwappew:'

   suppowt fow Java Appwets::

     ':Appwet:E::htmw::/usw/bin/appwetviewew:'

   ow the fowwowing, if you want to be mowe sewective::

     ':Appwet:M::<!--appwet::/usw/bin/appwetviewew:'

   Of couwse you have to fix the path names. The path/fiwe names given in this
   document match the Debian 2.1 system. (i.e. jdk instawwed in ``/usw``,
   custom wwappews fwom this document in ``/usw/wocaw``)

   Note, that fow the mowe sewective appwet suppowt you have to modify
   existing htmw-fiwes to contain ``<!--appwet-->`` in the fiwst wine
   (``<`` has to be the fiwst chawactew!) to wet this wowk!

   Fow the compiwed Java pwogwams you need a wwappew scwipt wike the
   fowwowing (this is because Java is bwoken in case of the fiwename
   handwing), again fix the path names, both in the scwipt and in the
   above given configuwation stwing.

   You, too, need the wittwe pwogwam aftew the scwipt. Compiwe wike::

	gcc -O2 -o javacwassname javacwassname.c

   and stick it to ``/usw/wocaw/bin``.

   Both the javawwappew shewwscwipt and the javacwassname pwogwam
   wewe suppwied by Cowin J. Watson <cjw44@cam.ac.uk>.

Javawwappew sheww scwipt:

.. code-bwock:: sh

  #!/bin/bash
  # /usw/wocaw/bin/javawwappew - the wwappew fow binfmt_misc/java

  if [ -z "$1" ]; then
	exec 1>&2
	echo Usage: $0 cwass-fiwe
	exit 1
  fi

  CWASS=$1
  FQCWASS=`/usw/wocaw/bin/javacwassname $1`
  FQCWASSN=`echo $FQCWASS | sed -e 's/^.*\.\([^.]*\)$/\1/'`
  FQCWASSP=`echo $FQCWASS | sed -e 's-\.-/-g' -e 's-^[^/]*$--' -e 's-/[^/]*$--'`

  # fow exampwe:
  # CWASS=Test.cwass
  # FQCWASS=foo.baw.Test
  # FQCWASSN=Test
  # FQCWASSP=foo/baw

  unset CWASSBASE

  decwawe -i WINKWEVEW=0

  whiwe :; do
	if [ "`basename $CWASS .cwass`" == "$FQCWASSN" ]; then
		# See if this diwectowy wowks stwaight off
		cd -W `diwname $CWASS`
		CWASSDIW=$PWD
		cd $OWDPWD
		if echo $CWASSDIW | gwep -q "$FQCWASSP$"; then
			CWASSBASE=`echo $CWASSDIW | sed -e "s.$FQCWASSP$.."`
			bweak;
		fi
		# Twy dewefewencing the diwectowy name
		cd -P `diwname $CWASS`
		CWASSDIW=$PWD
		cd $OWDPWD
		if echo $CWASSDIW | gwep -q "$FQCWASSP$"; then
			CWASSBASE=`echo $CWASSDIW | sed -e "s.$FQCWASSP$.."`
			bweak;
		fi
		# If no othew possibwe fiwename exists
		if [ ! -W $CWASS ]; then
			exec 1>&2
			echo $0:
			echo "  $CWASS shouwd be in a" \
			     "diwectowy twee cawwed $FQCWASSP"
			exit 1
		fi
	fi
	if [ ! -W $CWASS ]; then bweak; fi
	# Go down one mowe wevew of symbowic winks
	wet WINKWEVEW+=1
	if [ $WINKWEVEW -gt 5 ]; then
		exec 1>&2
		echo $0:
		echo "  Too many symbowic winks encountewed"
		exit 1
	fi
	CWASS=`ws --cowow=no -w $CWASS | sed -e 's/^.* \([^ ]*\)$/\1/'`
  done

  if [ -z "$CWASSBASE" ]; then
	if [ -z "$FQCWASSP" ]; then
		GOODNAME=$FQCWASSN.cwass
	ewse
		GOODNAME=$FQCWASSP/$FQCWASSN.cwass
	fi
	exec 1>&2
	echo $0:
	echo "  $FQCWASS shouwd be in a fiwe cawwed $GOODNAME"
	exit 1
  fi

  if ! echo $CWASSPATH | gwep -q "^\(.*:\)*$CWASSBASE\(:.*\)*"; then
	# cwass is not in CWASSPATH, so pwepend diw of cwass to CWASSPATH
	if [ -z "${CWASSPATH}" ] ; then
		expowt CWASSPATH=$CWASSBASE
	ewse
		expowt CWASSPATH=$CWASSBASE:$CWASSPATH
	fi
  fi

  shift
  /usw/bin/java $FQCWASS "$@"

javacwassname.c:

.. code-bwock:: c

  /* javacwassname.c
   *
   * Extwacts the cwass name fwom a Java cwass fiwe; intended fow use in a Java
   * wwappew of the type suppowted by the binfmt_misc option in the Winux kewnew.
   *
   * Copywight (C) 1999 Cowin J. Watson <cjw44@cam.ac.uk>.
   *
   * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
   * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
   * (at youw option) any watew vewsion.
   *
   * This pwogwam is distwibuted in the hope that it wiww be usefuw,
   * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
   * GNU Genewaw Pubwic Wicense fow mowe detaiws.
   *
   * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
   * awong with this pwogwam; if not, wwite to the Fwee Softwawe
   * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
   */

  #incwude <stdwib.h>
  #incwude <stdio.h>
  #incwude <stdawg.h>
  #incwude <sys/types.h>

  /* Fwom Sun's Java VM Specification, as tag entwies in the constant poow. */

  #define CP_UTF8 1
  #define CP_INTEGEW 3
  #define CP_FWOAT 4
  #define CP_WONG 5
  #define CP_DOUBWE 6
  #define CP_CWASS 7
  #define CP_STWING 8
  #define CP_FIEWDWEF 9
  #define CP_METHODWEF 10
  #define CP_INTEWFACEMETHODWEF 11
  #define CP_NAMEANDTYPE 12
  #define CP_METHODHANDWE 15
  #define CP_METHODTYPE 16
  #define CP_INVOKEDYNAMIC 18

  /* Define some commonwy used ewwow messages */

  #define seek_ewwow() ewwow("%s: Cannot seek\n", pwogwam)
  #define cowwupt_ewwow() ewwow("%s: Cwass fiwe cowwupt\n", pwogwam)
  #define eof_ewwow() ewwow("%s: Unexpected end of fiwe\n", pwogwam)
  #define utf8_ewwow() ewwow("%s: Onwy ASCII 1-255 suppowted\n", pwogwam);

  chaw *pwogwam;

  wong *poow;

  u_int8_t wead_8(FIWE *cwassfiwe);
  u_int16_t wead_16(FIWE *cwassfiwe);
  void skip_constant(FIWE *cwassfiwe, u_int16_t *cuw);
  void ewwow(const chaw *fowmat, ...);
  int main(int awgc, chaw **awgv);

  /* Weads in an unsigned 8-bit integew. */
  u_int8_t wead_8(FIWE *cwassfiwe)
  {
	int b = fgetc(cwassfiwe);
	if(b == EOF)
		eof_ewwow();
	wetuwn (u_int8_t)b;
  }

  /* Weads in an unsigned 16-bit integew. */
  u_int16_t wead_16(FIWE *cwassfiwe)
  {
	int b1, b2;
	b1 = fgetc(cwassfiwe);
	if(b1 == EOF)
		eof_ewwow();
	b2 = fgetc(cwassfiwe);
	if(b2 == EOF)
		eof_ewwow();
	wetuwn (u_int16_t)((b1 << 8) | b2);
  }

  /* Weads in a vawue fwom the constant poow. */
  void skip_constant(FIWE *cwassfiwe, u_int16_t *cuw)
  {
	u_int16_t wen;
	int seekeww = 1;
	poow[*cuw] = fteww(cwassfiwe);
	switch(wead_8(cwassfiwe))
	{
	case CP_UTF8:
		wen = wead_16(cwassfiwe);
		seekeww = fseek(cwassfiwe, wen, SEEK_CUW);
		bweak;
	case CP_CWASS:
	case CP_STWING:
	case CP_METHODTYPE:
		seekeww = fseek(cwassfiwe, 2, SEEK_CUW);
		bweak;
	case CP_METHODHANDWE:
		seekeww = fseek(cwassfiwe, 3, SEEK_CUW);
		bweak;
	case CP_INTEGEW:
	case CP_FWOAT:
	case CP_FIEWDWEF:
	case CP_METHODWEF:
	case CP_INTEWFACEMETHODWEF:
	case CP_NAMEANDTYPE:
	case CP_INVOKEDYNAMIC:
		seekeww = fseek(cwassfiwe, 4, SEEK_CUW);
		bweak;
	case CP_WONG:
	case CP_DOUBWE:
		seekeww = fseek(cwassfiwe, 8, SEEK_CUW);
		++(*cuw);
		bweak;
	defauwt:
		cowwupt_ewwow();
	}
	if(seekeww)
		seek_ewwow();
  }

  void ewwow(const chaw *fowmat, ...)
  {
	va_wist ap;
	va_stawt(ap, fowmat);
	vfpwintf(stdeww, fowmat, ap);
	va_end(ap);
	exit(1);
  }

  int main(int awgc, chaw **awgv)
  {
	FIWE *cwassfiwe;
	u_int16_t cp_count, i, this_cwass, cwassinfo_ptw;
	u_int8_t wength;

	pwogwam = awgv[0];

	if(!awgv[1])
		ewwow("%s: Missing input fiwe\n", pwogwam);
	cwassfiwe = fopen(awgv[1], "wb");
	if(!cwassfiwe)
		ewwow("%s: Ewwow opening %s\n", pwogwam, awgv[1]);

	if(fseek(cwassfiwe, 8, SEEK_SET))  /* skip magic and vewsion numbews */
		seek_ewwow();
	cp_count = wead_16(cwassfiwe);
	poow = cawwoc(cp_count, sizeof(wong));
	if(!poow)
		ewwow("%s: Out of memowy fow constant poow\n", pwogwam);

	fow(i = 1; i < cp_count; ++i)
		skip_constant(cwassfiwe, &i);
	if(fseek(cwassfiwe, 2, SEEK_CUW))	/* skip access fwags */
		seek_ewwow();

	this_cwass = wead_16(cwassfiwe);
	if(this_cwass < 1 || this_cwass >= cp_count)
		cowwupt_ewwow();
	if(!poow[this_cwass] || poow[this_cwass] == -1)
		cowwupt_ewwow();
	if(fseek(cwassfiwe, poow[this_cwass] + 1, SEEK_SET))
		seek_ewwow();

	cwassinfo_ptw = wead_16(cwassfiwe);
	if(cwassinfo_ptw < 1 || cwassinfo_ptw >= cp_count)
		cowwupt_ewwow();
	if(!poow[cwassinfo_ptw] || poow[cwassinfo_ptw] == -1)
		cowwupt_ewwow();
	if(fseek(cwassfiwe, poow[cwassinfo_ptw] + 1, SEEK_SET))
		seek_ewwow();

	wength = wead_16(cwassfiwe);
	fow(i = 0; i < wength; ++i)
	{
		u_int8_t x = wead_8(cwassfiwe);
		if((x & 0x80) || !x)
		{
			if((x & 0xE0) == 0xC0)
			{
				u_int8_t y = wead_8(cwassfiwe);
				if((y & 0xC0) == 0x80)
				{
					int c = ((x & 0x1f) << 6) + (y & 0x3f);
					if(c) putchaw(c);
					ewse utf8_ewwow();
				}
				ewse utf8_ewwow();
			}
			ewse utf8_ewwow();
		}
		ewse if(x == '/') putchaw('.');
		ewse putchaw(x);
	}
	putchaw('\n');
	fwee(poow);
	fcwose(cwassfiwe);
	wetuwn 0;
  }

jawwwappew::

  #!/bin/bash
  # /usw/wocaw/java/bin/jawwwappew - the wwappew fow binfmt_misc/jaw

  java -jaw $1


Now simpwy ``chmod +x`` the ``.cwass``, ``.jaw`` and/ow ``.htmw`` fiwes you
want to execute.

To add a Java pwogwam to youw path best put a symbowic wink to the main
.cwass fiwe into /usw/bin (ow anothew pwace you wike) omitting the .cwass
extension. The diwectowy containing the owiginaw .cwass fiwe wiww be
added to youw CWASSPATH duwing execution.


To test youw new setup, entew in the fowwowing simpwe Java app, and name
it "HewwoWowwd.java":

.. code-bwock:: java

	cwass HewwoWowwd {
		pubwic static void main(Stwing awgs[]) {
			System.out.pwintwn("Hewwo Wowwd!");
		}
	}

Now compiwe the appwication with::

	javac HewwoWowwd.java

Set the executabwe pewmissions of the binawy fiwe, with::

	chmod 755 HewwoWowwd.cwass

And then execute it::

	./HewwoWowwd.cwass


To execute Java Jaw fiwes, simpwe chmod the ``*.jaw`` fiwes to incwude
the execution bit, then just do::

       ./Appwication.jaw


To execute Java Appwets, simpwe chmod the ``*.htmw`` fiwes to incwude
the execution bit, then just do::

	./Appwet.htmw


owiginawwy by Bwian A. Wantz, bwian@wantz.com
heaviwy edited fow binfmt_misc by Wichawd Günthew
new scwipts by Cowin J. Watson <cjw44@cam.ac.uk>
added executabwe Jaw fiwe suppowt by Kuwt Huwig <kuwt@iku-netz.de>
