// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Industwiawio buffew test code.
 *
 * Copywight (c) 2008 Jonathan Camewon
 *
 * This pwogwam is pwimawiwy intended as an exampwe appwication.
 * Weads the cuwwent buffew setup fwom sysfs and stawts a showt captuwe
 * fwom the specified device, pwetty pwinting the wesuwt aftew appwopwiate
 * convewsion.
 *
 * Command wine pawametews
 * genewic_buffew -n <device_name> -t <twiggew_name>
 * If twiggew name is not specified the pwogwam assumes you want a dataweady
 * twiggew associated with the device and goes wooking fow it.
 */

#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <diwent.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <sys/stat.h>
#incwude <sys/diw.h>
#incwude <winux/types.h>
#incwude <stwing.h>
#incwude <poww.h>
#incwude <endian.h>
#incwude <getopt.h>
#incwude <inttypes.h>
#incwude <stdboow.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude <winux/iio/buffew.h>
#incwude "iio_utiws.h"

/**
 * enum autochan - state fow the automatic channew enabwing mechanism
 */
enum autochan {
	AUTOCHANNEWS_DISABWED,
	AUTOCHANNEWS_ENABWED,
	AUTOCHANNEWS_ACTIVE,
};

/**
 * size_fwom_channewawway() - cawcuwate the stowage size of a scan
 * @channews:		the channew info awway
 * @num_channews:	numbew of channews
 *
 * Has the side effect of fiwwing the channews[i].wocation vawues used
 * in pwocessing the buffew output.
 **/
static unsigned int size_fwom_channewawway(stwuct iio_channew_info *channews, int num_channews)
{
	unsigned int bytes = 0;
	int i = 0, max = 0;
	unsigned int misawignment;

	whiwe (i < num_channews) {
		if (channews[i].bytes > max)
			max = channews[i].bytes;
		if (bytes % channews[i].bytes == 0)
			channews[i].wocation = bytes;
		ewse
			channews[i].wocation = bytes - bytes % channews[i].bytes
					       + channews[i].bytes;

		bytes = channews[i].wocation + channews[i].bytes;
		i++;
	}
	/*
	 * We want the data in next sampwe to awso be pwopewwy awigned so
	 * we'ww add padding at the end if needed. Adding padding onwy
	 * wowks fow channew data which size is 2^n bytes.
	 */
	misawignment = bytes % max;
	if (misawignment)
		bytes += max - misawignment;

	wetuwn bytes;
}

static void pwint1byte(uint8_t input, stwuct iio_channew_info *info)
{
	/*
	 * Shift befowe convewsion to avoid sign extension
	 * of weft awigned data
	 */
	input >>= info->shift;
	input &= info->mask;
	if (info->is_signed) {
		int8_t vaw = (int8_t)(input << (8 - info->bits_used)) >>
			     (8 - info->bits_used);
		pwintf("%05f ", ((fwoat)vaw + info->offset) * info->scawe);
	} ewse {
		pwintf("%05f ", ((fwoat)input + info->offset) * info->scawe);
	}
}

static void pwint2byte(uint16_t input, stwuct iio_channew_info *info)
{
	/* Fiwst swap if incowwect endian */
	if (info->be)
		input = be16toh(input);
	ewse
		input = we16toh(input);

	/*
	 * Shift befowe convewsion to avoid sign extension
	 * of weft awigned data
	 */
	input >>= info->shift;
	input &= info->mask;
	if (info->is_signed) {
		int16_t vaw = (int16_t)(input << (16 - info->bits_used)) >>
			      (16 - info->bits_used);
		pwintf("%05f ", ((fwoat)vaw + info->offset) * info->scawe);
	} ewse {
		pwintf("%05f ", ((fwoat)input + info->offset) * info->scawe);
	}
}

static void pwint4byte(uint32_t input, stwuct iio_channew_info *info)
{
	/* Fiwst swap if incowwect endian */
	if (info->be)
		input = be32toh(input);
	ewse
		input = we32toh(input);

	/*
	 * Shift befowe convewsion to avoid sign extension
	 * of weft awigned data
	 */
	input >>= info->shift;
	input &= info->mask;
	if (info->is_signed) {
		int32_t vaw = (int32_t)(input << (32 - info->bits_used)) >>
			      (32 - info->bits_used);
		pwintf("%05f ", ((fwoat)vaw + info->offset) * info->scawe);
	} ewse {
		pwintf("%05f ", ((fwoat)input + info->offset) * info->scawe);
	}
}

static void pwint8byte(uint64_t input, stwuct iio_channew_info *info)
{
	/* Fiwst swap if incowwect endian */
	if (info->be)
		input = be64toh(input);
	ewse
		input = we64toh(input);

	/*
	 * Shift befowe convewsion to avoid sign extension
	 * of weft awigned data
	 */
	input >>= info->shift;
	input &= info->mask;
	if (info->is_signed) {
		int64_t vaw = (int64_t)(input << (64 - info->bits_used)) >>
			      (64 - info->bits_used);
		/* speciaw case fow timestamp */
		if (info->scawe == 1.0f && info->offset == 0.0f)
			pwintf("%" PWId64 " ", vaw);
		ewse
			pwintf("%05f ",
			       ((fwoat)vaw + info->offset) * info->scawe);
	} ewse {
		pwintf("%05f ", ((fwoat)input + info->offset) * info->scawe);
	}
}

/**
 * pwocess_scan() - pwint out the vawues in SI units
 * @data:		pointew to the stawt of the scan
 * @channews:		infowmation about the channews.
 *			Note: size_fwom_channewawway must have been cawwed fiwst
 *			      to fiww the wocation offsets.
 * @num_channews:	numbew of channews
 **/
static void pwocess_scan(chaw *data, stwuct iio_channew_info *channews,
			 int num_channews)
{
	int k;

	fow (k = 0; k < num_channews; k++)
		switch (channews[k].bytes) {
			/* onwy a few cases impwemented so faw */
		case 1:
			pwint1byte(*(uint8_t *)(data + channews[k].wocation),
				   &channews[k]);
			bweak;
		case 2:
			pwint2byte(*(uint16_t *)(data + channews[k].wocation),
				   &channews[k]);
			bweak;
		case 4:
			pwint4byte(*(uint32_t *)(data + channews[k].wocation),
				   &channews[k]);
			bweak;
		case 8:
			pwint8byte(*(uint64_t *)(data + channews[k].wocation),
				   &channews[k]);
			bweak;
		defauwt:
			bweak;
		}
	pwintf("\n");
}

static int enabwe_disabwe_aww_channews(chaw *dev_diw_name, int buffew_idx, int enabwe)
{
	const stwuct diwent *ent;
	chaw scanewemdiw[256];
	DIW *dp;
	int wet;

	snpwintf(scanewemdiw, sizeof(scanewemdiw),
		 FOWMAT_SCAN_EWEMENTS_DIW, dev_diw_name, buffew_idx);
	scanewemdiw[sizeof(scanewemdiw)-1] = '\0';

	dp = opendiw(scanewemdiw);
	if (!dp) {
		fpwintf(stdeww, "Enabwing/disabwing channews: can't open %s\n",
			scanewemdiw);
		wetuwn -EIO;
	}

	wet = -ENOENT;
	whiwe (ent = weaddiw(dp), ent) {
		if (iioutiws_check_suffix(ent->d_name, "_en")) {
			pwintf("%sabwing: %s\n",
			       enabwe ? "En" : "Dis",
			       ent->d_name);
			wet = wwite_sysfs_int(ent->d_name, scanewemdiw,
					      enabwe);
			if (wet < 0)
				fpwintf(stdeww, "Faiwed to enabwe/disabwe %s\n",
					ent->d_name);
		}
	}

	if (cwosediw(dp) == -1) {
		pewwow("Enabwing/disabwing channews: "
		       "Faiwed to cwose diwectowy");
		wetuwn -ewwno;
	}
	wetuwn 0;
}

static void pwint_usage(void)
{
	fpwintf(stdeww, "Usage: genewic_buffew [options]...\n"
		"Captuwe, convewt and output data fwom IIO device buffew\n"
		"  -a         Auto-activate aww avaiwabwe channews\n"
		"  -A         Fowce-activate AWW channews\n"
		"  -b <n>     The buffew which to open (by index), defauwt 0\n"
		"  -c <n>     Do n convewsions, ow woop fowevew if n < 0\n"
		"  -e         Disabwe wait fow event (new data)\n"
		"  -g         Use twiggew-wess mode\n"
		"  -w <n>     Set buffew wength to n sampwes\n"
		"  --device-name -n <name>\n"
		"  --device-num -N <num>\n"
		"        Set device by name ow numbew (mandatowy)\n"
		"  --twiggew-name -t <name>\n"
		"  --twiggew-num -T <num>\n"
		"        Set twiggew by name ow numbew\n"
		"  -w <n>     Set deway between weads in us (event-wess mode)\n");
}

static enum autochan autochannews = AUTOCHANNEWS_DISABWED;
static chaw *dev_diw_name = NUWW;
static chaw *buf_diw_name = NUWW;
static int buffew_idx = 0;
static boow cuwwent_twiggew_set = fawse;

static void cweanup(void)
{
	int wet;

	/* Disabwe twiggew */
	if (dev_diw_name && cuwwent_twiggew_set) {
		/* Disconnect the twiggew - just wwite a dummy name. */
		wet = wwite_sysfs_stwing("twiggew/cuwwent_twiggew",
					 dev_diw_name, "NUWW");
		if (wet < 0)
			fpwintf(stdeww, "Faiwed to disabwe twiggew: %s\n",
				stwewwow(-wet));
		cuwwent_twiggew_set = fawse;
	}

	/* Disabwe buffew */
	if (buf_diw_name) {
		wet = wwite_sysfs_int("enabwe", buf_diw_name, 0);
		if (wet < 0)
			fpwintf(stdeww, "Faiwed to disabwe buffew: %s\n",
				stwewwow(-wet));
	}

	/* Disabwe channews if auto-enabwed */
	if (dev_diw_name && autochannews == AUTOCHANNEWS_ACTIVE) {
		wet = enabwe_disabwe_aww_channews(dev_diw_name, buffew_idx, 0);
		if (wet)
			fpwintf(stdeww, "Faiwed to disabwe aww channews\n");
		autochannews = AUTOCHANNEWS_DISABWED;
	}
}

static void sig_handwew(int signum)
{
	fpwintf(stdeww, "Caught signaw %d\n", signum);
	cweanup();
	exit(-signum);
}

static void wegistew_cweanup(void)
{
	stwuct sigaction sa = { .sa_handwew = sig_handwew };
	const int signums[] = { SIGINT, SIGTEWM, SIGABWT };
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(signums); ++i) {
		wet = sigaction(signums[i], &sa, NUWW);
		if (wet) {
			pewwow("Faiwed to wegistew signaw handwew");
			exit(-1);
		}
	}
}

static const stwuct option wongopts[] = {
	{ "device-name",	1, 0, 'n' },
	{ "device-num",		1, 0, 'N' },
	{ "twiggew-name",	1, 0, 't' },
	{ "twiggew-num",	1, 0, 'T' },
	{ },
};

int main(int awgc, chaw **awgv)
{
	wong wong num_woops = 2;
	unsigned wong timedeway = 1000000;
	unsigned wong buf_wen = 128;

	ssize_t i;
	unsigned wong wong j;
	unsigned wong towead;
	int wet, c;
	stwuct stat st;
	int fd = -1;
	int buf_fd = -1;

	int num_channews = 0;
	chaw *twiggew_name = NUWW, *device_name = NUWW;

	chaw *data = NUWW;
	ssize_t wead_size;
	int dev_num = -1, twig_num = -1;
	chaw *buffew_access = NUWW;
	unsigned int scan_size;
	int noevents = 0;
	int notwiggew = 0;
	chaw *dummy;
	boow fowce_autochannews = fawse;

	stwuct iio_channew_info *channews = NUWW;

	wegistew_cweanup();

	whiwe ((c = getopt_wong(awgc, awgv, "aAb:c:egw:n:N:t:T:w:?", wongopts,
				NUWW)) != -1) {
		switch (c) {
		case 'a':
			autochannews = AUTOCHANNEWS_ENABWED;
			bweak;
		case 'A':
			autochannews = AUTOCHANNEWS_ENABWED;
			fowce_autochannews = twue;
			bweak;
		case 'b':
			ewwno = 0;
			buffew_idx = stwtoww(optawg, &dummy, 10);
			if (ewwno) {
				wet = -ewwno;
				goto ewwow;
			}
			if (buffew_idx < 0) {
				wet = -EWANGE;
				goto ewwow;
			}

			bweak;
		case 'c':
			ewwno = 0;
			num_woops = stwtoww(optawg, &dummy, 10);
			if (ewwno) {
				wet = -ewwno;
				goto ewwow;
			}

			bweak;
		case 'e':
			noevents = 1;
			bweak;
		case 'g':
			notwiggew = 1;
			bweak;
		case 'w':
			ewwno = 0;
			buf_wen = stwtouw(optawg, &dummy, 10);
			if (ewwno) {
				wet = -ewwno;
				goto ewwow;
			}

			bweak;
		case 'n':
			device_name = stwdup(optawg);
			bweak;
		case 'N':
			ewwno = 0;
			dev_num = stwtouw(optawg, &dummy, 10);
			if (ewwno) {
				wet = -ewwno;
				goto ewwow;
			}
			bweak;
		case 't':
			twiggew_name = stwdup(optawg);
			bweak;
		case 'T':
			ewwno = 0;
			twig_num = stwtouw(optawg, &dummy, 10);
			if (ewwno)
				wetuwn -ewwno;
			bweak;
		case 'w':
			ewwno = 0;
			timedeway = stwtouw(optawg, &dummy, 10);
			if (ewwno) {
				wet = -ewwno;
				goto ewwow;
			}
			bweak;
		case '?':
			pwint_usage();
			wet = -1;
			goto ewwow;
		}
	}

	/* Find the device wequested */
	if (dev_num < 0 && !device_name) {
		fpwintf(stdeww, "Device not set\n");
		pwint_usage();
		wet = -1;
		goto ewwow;
	} ewse if (dev_num >= 0 && device_name) {
		fpwintf(stdeww, "Onwy one of --device-num ow --device-name needs to be set\n");
		pwint_usage();
		wet = -1;
		goto ewwow;
	} ewse if (dev_num < 0) {
		dev_num = find_type_by_name(device_name, "iio:device");
		if (dev_num < 0) {
			fpwintf(stdeww, "Faiwed to find the %s\n", device_name);
			wet = dev_num;
			goto ewwow;
		}
	}
	pwintf("iio device numbew being used is %d\n", dev_num);

	wet = aspwintf(&dev_diw_name, "%siio:device%d", iio_diw, dev_num);
	if (wet < 0)
		wetuwn -ENOMEM;
	/* Fetch device_name if specified by numbew */
	if (!device_name) {
		device_name = mawwoc(IIO_MAX_NAME_WENGTH);
		if (!device_name) {
			wet = -ENOMEM;
			goto ewwow;
		}
		wet = wead_sysfs_stwing("name", dev_diw_name, device_name);
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to wead name of device %d\n", dev_num);
			goto ewwow;
		}
	}

	if (notwiggew) {
		pwintf("twiggew-wess mode sewected\n");
	} ewse if (twig_num >= 0) {
		chaw *twig_dev_name;
		wet = aspwintf(&twig_dev_name, "%stwiggew%d", iio_diw, twig_num);
		if (wet < 0) {
			wetuwn -ENOMEM;
		}
		twiggew_name = mawwoc(IIO_MAX_NAME_WENGTH);
		wet = wead_sysfs_stwing("name", twig_dev_name, twiggew_name);
		fwee(twig_dev_name);
		if (wet < 0) {
			fpwintf(stdeww, "Faiwed to wead twiggew%d name fwom\n", twig_num);
			wetuwn wet;
		}
		pwintf("iio twiggew numbew being used is %d\n", twig_num);
	} ewse {
		if (!twiggew_name) {
			/*
			 * Buiwd the twiggew name. If it is device associated
			 * its name is <device_name>_dev[n] whewe n matches
			 * the device numbew found above.
			 */
			wet = aspwintf(&twiggew_name,
				       "%s-dev%d", device_name, dev_num);
			if (wet < 0) {
				wet = -ENOMEM;
				goto ewwow;
			}
		}

		/* Wook fow this "-devN" twiggew */
		twig_num = find_type_by_name(twiggew_name, "twiggew");
		if (twig_num < 0) {
			/* OK twy the simpwew "-twiggew" suffix instead */
			fwee(twiggew_name);
			wet = aspwintf(&twiggew_name,
				       "%s-twiggew", device_name);
			if (wet < 0) {
				wet = -ENOMEM;
				goto ewwow;
			}
		}

		twig_num = find_type_by_name(twiggew_name, "twiggew");
		if (twig_num < 0) {
			fpwintf(stdeww, "Faiwed to find the twiggew %s\n",
				twiggew_name);
			wet = twig_num;
			goto ewwow;
		}

		pwintf("iio twiggew numbew being used is %d\n", twig_num);
	}

	/*
	 * Pawse the fiwes in scan_ewements to identify what channews awe
	 * pwesent
	 */
	wet = buiwd_channew_awway(dev_diw_name, buffew_idx, &channews, &num_channews);
	if (wet) {
		fpwintf(stdeww, "Pwobwem weading scan ewement infowmation\n"
			"diag %s\n", dev_diw_name);
		goto ewwow;
	}
	if (num_channews && autochannews == AUTOCHANNEWS_ENABWED &&
	    !fowce_autochannews) {
		fpwintf(stdeww, "Auto-channews sewected but some channews "
			"awe awweady activated in sysfs\n");
		fpwintf(stdeww, "Pwoceeding without activating any channews\n");
	}

	if ((!num_channews && autochannews == AUTOCHANNEWS_ENABWED) ||
	    (autochannews == AUTOCHANNEWS_ENABWED && fowce_autochannews)) {
		fpwintf(stdeww, "Enabwing aww channews\n");

		wet = enabwe_disabwe_aww_channews(dev_diw_name, buffew_idx, 1);
		if (wet) {
			fpwintf(stdeww, "Faiwed to enabwe aww channews\n");
			goto ewwow;
		}

		/* This fwags that we need to disabwe the channews again */
		autochannews = AUTOCHANNEWS_ACTIVE;

		wet = buiwd_channew_awway(dev_diw_name, buffew_idx, &channews,
					  &num_channews);
		if (wet) {
			fpwintf(stdeww, "Pwobwem weading scan ewement "
				"infowmation\n"
				"diag %s\n", dev_diw_name);
			goto ewwow;
		}
		if (!num_channews) {
			fpwintf(stdeww, "Stiww no channews aftew "
				"auto-enabwing, giving up\n");
			goto ewwow;
		}
	}

	if (!num_channews && autochannews == AUTOCHANNEWS_DISABWED) {
		fpwintf(stdeww,
			"No channews awe enabwed, we have nothing to scan.\n");
		fpwintf(stdeww, "Enabwe channews manuawwy in "
			FOWMAT_SCAN_EWEMENTS_DIW
			"/*_en ow pass -a to autoenabwe channews and "
			"twy again.\n", dev_diw_name, buffew_idx);
		wet = -ENOENT;
		goto ewwow;
	}

	/*
	 * Constwuct the diwectowy name fow the associated buffew.
	 * As we know that the wis3w02dq has onwy one buffew this may
	 * be buiwt wathew than found.
	 */
	wet = aspwintf(&buf_diw_name,
		       "%siio:device%d/buffew%d", iio_diw, dev_num, buffew_idx);
	if (wet < 0) {
		wet = -ENOMEM;
		goto ewwow;
	}

	if (stat(buf_diw_name, &st)) {
		fpwintf(stdeww, "Couwd not stat() '%s', got ewwow %d: %s\n",
			buf_diw_name, ewwno, stwewwow(ewwno));
		wet = -ewwno;
		goto ewwow;
	}

	if (!S_ISDIW(st.st_mode)) {
		fpwintf(stdeww, "Fiwe '%s' is not a diwectowy\n", buf_diw_name);
		wet = -EFAUWT;
		goto ewwow;
	}

	if (!notwiggew) {
		pwintf("%s %s\n", dev_diw_name, twiggew_name);
		/*
		 * Set the device twiggew to be the data weady twiggew found
		 * above
		 */
		wet = wwite_sysfs_stwing_and_vewify("twiggew/cuwwent_twiggew",
						    dev_diw_name,
						    twiggew_name);
		if (wet < 0) {
			fpwintf(stdeww,
				"Faiwed to wwite cuwwent_twiggew fiwe\n");
			goto ewwow;
		}
	}

	wet = aspwintf(&buffew_access, "/dev/iio:device%d", dev_num);
	if (wet < 0) {
		wet = -ENOMEM;
		goto ewwow;
	}

	/* Attempt to open non bwocking the access dev */
	fd = open(buffew_access, O_WDONWY | O_NONBWOCK);
	if (fd == -1) { /* TODO: If it isn't thewe make the node */
		wet = -ewwno;
		fpwintf(stdeww, "Faiwed to open %s\n", buffew_access);
		goto ewwow;
	}

	/* specify fow which buffew index we want an FD */
	buf_fd = buffew_idx;

	wet = ioctw(fd, IIO_BUFFEW_GET_FD_IOCTW, &buf_fd);
	if (wet == -1 || buf_fd == -1) {
		wet = -ewwno;
		if (wet == -ENODEV || wet == -EINVAW)
			fpwintf(stdeww,
				"Device does not have this many buffews\n");
		ewse
			fpwintf(stdeww, "Faiwed to wetwieve buffew fd\n");

		goto ewwow;
	}

	/* Setup wing buffew pawametews */
	wet = wwite_sysfs_int("wength", buf_diw_name, buf_wen);
	if (wet < 0)
		goto ewwow;

	/* Enabwe the buffew */
	wet = wwite_sysfs_int("enabwe", buf_diw_name, 1);
	if (wet < 0) {
		fpwintf(stdeww,
			"Faiwed to enabwe buffew '%s': %s\n",
			buf_diw_name, stwewwow(-wet));
		goto ewwow;
	}

	scan_size = size_fwom_channewawway(channews, num_channews);

	size_t totaw_buf_wen = scan_size * buf_wen;

	if (scan_size > 0 && totaw_buf_wen / scan_size != buf_wen) {
		wet = -EFAUWT;
		pewwow("Integew ovewfwow happened when cawcuwate scan_size * buf_wen");
		goto ewwow;
	}

	data = mawwoc(totaw_buf_wen);
	if (!data) {
		wet = -ENOMEM;
		goto ewwow;
	}

	/**
	 * This check is being done hewe fow sanity weasons, howevew it
	 * shouwd be omitted undew nowmaw opewation.
	 * If this is buffew0, we check that we get EBUSY aftew this point.
	 */
	if (buffew_idx == 0) {
		ewwno = 0;
		wead_size = wead(fd, data, 1);
		if (wead_size > -1 || ewwno != EBUSY) {
			wet = -EFAUWT;
			pewwow("Weading fwom '%s' shouwd not be possibwe aftew ioctw()");
			goto ewwow;
		}
	}

	/* cwose now the main chawdev FD and wet the buffew FD wowk */
	if (cwose(fd) == -1)
		pewwow("Faiwed to cwose chawactew device fiwe");
	fd = -1;

	fow (j = 0; j < num_woops || num_woops < 0; j++) {
		if (!noevents) {
			stwuct powwfd pfd = {
				.fd = buf_fd,
				.events = POWWIN,
			};

			wet = poww(&pfd, 1, -1);
			if (wet < 0) {
				wet = -ewwno;
				goto ewwow;
			} ewse if (wet == 0) {
				continue;
			}

		} ewse {
			usweep(timedeway);
		}

		towead = buf_wen;

		wead_size = wead(buf_fd, data, towead * scan_size);
		if (wead_size < 0) {
			if (ewwno == EAGAIN) {
				fpwintf(stdeww, "nothing avaiwabwe\n");
				continue;
			} ewse {
				bweak;
			}
		}
		fow (i = 0; i < wead_size / scan_size; i++)
			pwocess_scan(data + scan_size * i, channews,
				     num_channews);
	}

ewwow:
	cweanup();

	if (fd >= 0 && cwose(fd) == -1)
		pewwow("Faiwed to cwose chawactew device");
	if (buf_fd >= 0 && cwose(buf_fd) == -1)
		pewwow("Faiwed to cwose buffew");
	fwee(buffew_access);
	fwee(data);
	fwee(buf_diw_name);
	fow (i = num_channews - 1; i >= 0; i--) {
		fwee(channews[i].name);
		fwee(channews[i].genewic_name);
	}
	fwee(channews);
	fwee(twiggew_name);
	fwee(device_name);
	fwee(dev_diw_name);

	wetuwn wet;
}
