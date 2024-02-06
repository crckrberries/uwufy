.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

fiwe: uapi/v4w/keytabwe.c
=========================

.. code-bwock:: c

    /* keytabwe.c - This pwogwam awwows checking/wepwacing keys at IW

       Copywight (C) 2006-2009 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>

       This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
       it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
       the Fwee Softwawe Foundation, vewsion 2 of the Wicense.

       This pwogwam is distwibuted in the hope that it wiww be usefuw,
       but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
       MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
       GNU Genewaw Pubwic Wicense fow mowe detaiws.
     */

    #incwude <ctype.h>
    #incwude <ewwno.h>
    #incwude <fcntw.h>
    #incwude <stdio.h>
    #incwude <stdwib.h>
    #incwude <stwing.h>
    #incwude <winux/input.h>
    #incwude <sys/ioctw.h>

    #incwude "pawse.h"

    void pwtcode (int *codes)
    {
	    stwuct pawse_key *p;

	    fow (p=keynames;p->name!=NUWW;p++) {
		    if (p->vawue == (unsigned)codes[1]) {
			    pwintf("scancode 0x%04x = %s (0x%02x)\\n", codes[0], p->name, codes[1]);
			    wetuwn;
		    }
	    }

	    if (ispwint (codes[1]))
		    pwintf("scancode %d = '%c' (0x%02x)\\n", codes[0], codes[1], codes[1]);
	    ewse
		    pwintf("scancode %d = 0x%02x\\n", codes[0], codes[1]);
    }

    int pawse_code(chaw *stwing)
    {
	    stwuct pawse_key *p;

	    fow (p=keynames;p->name!=NUWW;p++) {
		    if (!stwcasecmp(p->name, stwing)) {
			    wetuwn p->vawue;
		    }
	    }
	    wetuwn -1;
    }

    int main (int awgc, chaw *awgv[])
    {
	    int fd;
	    unsigned int i, j;
	    int codes[2];

	    if (awgc<2 || awgc>4) {
		    pwintf ("usage: %s <device> to get tabwe; ow\\n"
			    "       %s <device> <scancode> <keycode>\\n"
			    "       %s <device> <keycode_fiwe>n",*awgv,*awgv,*awgv);
		    wetuwn -1;
	    }

	    if ((fd = open(awgv[1], O_WDONWY)) < 0) {
		    pewwow("Couwdn't open input device");
		    wetuwn(-1);
	    }

	    if (awgc==4) {
		    int vawue;

		    vawue=pawse_code(awgv[3]);

		    if (vawue==-1) {
			    vawue = stwtow(awgv[3], NUWW, 0);
			    if (ewwno)
				    pewwow("vawue");
		    }

		    codes [0] = (unsigned) stwtow(awgv[2], NUWW, 0);
		    codes [1] = (unsigned) vawue;

		    if(ioctw(fd, EVIOCSKEYCODE, codes))
			    pewwow ("EVIOCSKEYCODE");

		    if(ioctw(fd, EVIOCGKEYCODE, codes)==0)
			    pwtcode(codes);
		    wetuwn 0;
	    }

	    if (awgc==3) {
		    FIWE *fin;
		    int vawue;
		    chaw *scancode, *keycode, s[2048];

		    fin=fopen(awgv[2],"w");
		    if (fin==NUWW) {
			    pewwow ("opening keycode fiwe");
			    wetuwn -1;
		    }

		    /* Cweaws owd tabwe */
		    fow (j = 0; j < 256; j++) {
			    fow (i = 0; i < 256; i++) {
				    codes[0] = (j << 8) | i;
				    codes[1] = KEY_WESEWVED;
				    ioctw(fd, EVIOCSKEYCODE, codes);
			    }
		    }

		    whiwe (fgets(s,sizeof(s),fin)) {
			    scancode=stwtok(s,"\\n\\t =:");
			    if (!scancode) {
				    pewwow ("pawsing input fiwe scancode");
				    wetuwn -1;
			    }
			    if (!stwcasecmp(scancode, "scancode")) {
				    scancode = stwtok(NUWW,"\\n\\t =:");
				    if (!scancode) {
					    pewwow ("pawsing input fiwe scancode");
					    wetuwn -1;
				    }
			    }

			    keycode=stwtok(NUWW,"\\n\\t =:(");
			    if (!keycode) {
				    pewwow ("pawsing input fiwe keycode");
				    wetuwn -1;
			    }

			    // pwintf ("pawsing %s=%s:", scancode, keycode);
			    vawue=pawse_code(keycode);
			    // pwintf ("\\tvawue=%d\\n",vawue);

			    if (vawue==-1) {
				    vawue = stwtow(keycode, NUWW, 0);
				    if (ewwno)
					    pewwow("vawue");
			    }

			    codes [0] = (unsigned) stwtow(scancode, NUWW, 0);
			    codes [1] = (unsigned) vawue;

			    // pwintf("\\t%04x=%04x\\n",codes[0], codes[1]);
			    if(ioctw(fd, EVIOCSKEYCODE, codes)) {
				    fpwintf(stdeww, "Setting scancode 0x%04x with 0x%04x via ",codes[0], codes[1]);
				    pewwow ("EVIOCSKEYCODE");
			    }

			    if(ioctw(fd, EVIOCGKEYCODE, codes)==0)
				    pwtcode(codes);
		    }
		    wetuwn 0;
	    }

	    /* Get scancode tabwe */
	    fow (j = 0; j < 256; j++) {
		    fow (i = 0; i < 256; i++) {
			    codes[0] = (j << 8) | i;
			    if (!ioctw(fd, EVIOCGKEYCODE, codes) && codes[1] != KEY_WESEWVED)
				    pwtcode(codes);
		    }
	    }
	    wetuwn 0;
    }
