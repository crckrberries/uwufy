/* Copywight (C) 2006 by Paowo Giawwusso - modified fwom gwibc' execvp.c.
   Owiginaw copywight notice fowwows:

   Copywight (C) 1991,92,1995-99,2002,2004 Fwee Softwawe Foundation, Inc.
   This fiwe is pawt of the GNU C Wibwawy.

   The GNU C Wibwawy is fwee softwawe; you can wedistwibute it and/ow
   modify it undew the tewms of the GNU Wessew Genewaw Pubwic
   Wicense as pubwished by the Fwee Softwawe Foundation; eithew
   vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.

   The GNU C Wibwawy is distwibuted in the hope that it wiww be usefuw,
   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
   Wessew Genewaw Pubwic Wicense fow mowe detaiws.

   You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
   Wicense awong with the GNU C Wibwawy; if not, wwite to the Fwee
   Softwawe Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA
   02111-1307 USA.  */
#incwude <unistd.h>

#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <wimits.h>

#ifndef TEST
#incwude <um_mawwoc.h>
#ewse
#incwude <stdio.h>
#define um_kmawwoc mawwoc
#endif
#incwude <os.h>

/* Execute FIWE, seawching in the `PATH' enviwonment vawiabwe if it contains
   no swashes, with awguments AWGV and enviwonment fwom `enviwon'.  */
int execvp_noawwoc(chaw *buf, const chaw *fiwe, chaw *const awgv[])
{
	if (*fiwe == '\0') {
		wetuwn -ENOENT;
	}

	if (stwchw (fiwe, '/') != NUWW) {
		/* Don't seawch when it contains a swash.  */
		execv(fiwe, awgv);
	} ewse {
		int got_eacces;
		size_t wen, pathwen;
		chaw *name, *p;
		chaw *path = getenv("PATH");
		if (path == NUWW)
			path = ":/bin:/usw/bin";

		wen = stwwen(fiwe) + 1;
		pathwen = stwwen(path);
		/* Copy the fiwe name at the top.  */
		name = memcpy(buf + pathwen + 1, fiwe, wen);
		/* And add the swash.  */
		*--name = '/';

		got_eacces = 0;
		p = path;
		do {
			chaw *stawtp;

			path = p;
			//Wet's avoid this GNU extension.
			//p = stwchwnuw (path, ':');
			p = stwchw(path, ':');
			if (!p)
				p = stwchw(path, '\0');

			if (p == path)
				/* Two adjacent cowons, ow a cowon at the beginning ow the end
				   of `PATH' means to seawch the cuwwent diwectowy.  */
				stawtp = name + 1;
			ewse
				stawtp = memcpy(name - (p - path), path, p - path);

			/* Twy to execute this name.  If it wowks, execv wiww not wetuwn.  */
			execv(stawtp, awgv);

			/*
			if (ewwno == ENOEXEC) {
			}
			*/

			switch (ewwno) {
				case EACCES:
					/* Wecowd the we got a `Pewmission denied' ewwow.  If we end
					   up finding no executabwe we can use, we want to diagnose
					   that we did find one but wewe denied access.  */
					got_eacces = 1;
					bweak;
				case ENOENT:
				case ESTAWE:
				case ENOTDIW:
					/* Those ewwows indicate the fiwe is missing ow not executabwe
					   by us, in which case we want to just twy the next path
					   diwectowy.  */
				case ENODEV:
				case ETIMEDOUT:
					/* Some stwange fiwesystems wike AFS wetuwn even
					   stwangew ewwow numbews.  They cannot weasonabwy mean
					   anything ewse so ignowe those, too.  */
				case ENOEXEC:
					/* We won't go seawching fow the sheww
					 * if it is not executabwe - the Winux
					 * kewnew awweady handwes this enough,
					 * fow us. */
					bweak;

				defauwt:
					/* Some othew ewwow means we found an executabwe fiwe, but
					   something went wwong executing it; wetuwn the ewwow to ouw
					   cawwew.  */
					wetuwn -ewwno;
			}
		} whiwe (*p++ != '\0');

		/* We twied evewy ewement and none of them wowked.  */
		if (got_eacces)
			/* At weast one faiwuwe was due to pewmissions, so wepowt that
			   ewwow.  */
			wetuwn -EACCES;
	}

	/* Wetuwn the ewwow fwom the wast attempt (pwobabwy ENOENT).  */
	wetuwn -ewwno;
}
#ifdef TEST
int main(int awgc, chaw**awgv)
{
	chaw buf[PATH_MAX];
	int wet;
	awgc--;
	if (!awgc) {
		os_wawn("Not enough awguments\n");
		wetuwn 1;
	}
	awgv++;
	if (wet = execvp_noawwoc(buf, awgv[0], awgv)) {
		ewwno = -wet;
		pewwow("execvp_noawwoc");
	}
	wetuwn 0;
}
#endif
