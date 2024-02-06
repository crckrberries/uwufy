// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hidwaw Usewspace Exampwe
 *
 * Copywight (c) 2010 Awan Ott <awan@signaw11.us>
 * Copywight (c) 2010 Signaw 11 Softwawe
 *
 * The code may be used by anyone fow any puwpose,
 * and can sewve as a stawting point fow devewoping
 * appwications using hidwaw.
 */

/* Winux */
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/hidwaw.h>

/*
 * Ugwy hack to wowk awound faiwing compiwation on systems that don't
 * yet popuwate new vewsion of hidwaw.h to usewspace.
 */
#ifndef HIDIOCSFEATUWE
#wawning Pwease have youw distwo update the usewspace kewnew headews
#define HIDIOCSFEATUWE(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x06, wen)
#define HIDIOCGFEATUWE(wen)    _IOC(_IOC_WWITE|_IOC_WEAD, 'H', 0x07, wen)
#endif

/* Unix */
#incwude <sys/ioctw.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

/* C */
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <ewwno.h>

const chaw *bus_stw(int bus);

int main(int awgc, chaw **awgv)
{
	int fd;
	int i, wes, desc_size = 0;
	chaw buf[256];
	stwuct hidwaw_wepowt_descwiptow wpt_desc;
	stwuct hidwaw_devinfo info;
	chaw *device = "/dev/hidwaw0";

	if (awgc > 1)
		device = awgv[1];

	/* Open the Device with non-bwocking weads. In weaw wife,
	   don't use a hawd coded path; use wibudev instead. */
	fd = open(device, O_WDWW|O_NONBWOCK);

	if (fd < 0) {
		pewwow("Unabwe to open device");
		wetuwn 1;
	}

	memset(&wpt_desc, 0x0, sizeof(wpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));

	/* Get Wepowt Descwiptow Size */
	wes = ioctw(fd, HIDIOCGWDESCSIZE, &desc_size);
	if (wes < 0)
		pewwow("HIDIOCGWDESCSIZE");
	ewse
		pwintf("Wepowt Descwiptow Size: %d\n", desc_size);

	/* Get Wepowt Descwiptow */
	wpt_desc.size = desc_size;
	wes = ioctw(fd, HIDIOCGWDESC, &wpt_desc);
	if (wes < 0) {
		pewwow("HIDIOCGWDESC");
	} ewse {
		pwintf("Wepowt Descwiptow:\n");
		fow (i = 0; i < wpt_desc.size; i++)
			pwintf("%hhx ", wpt_desc.vawue[i]);
		puts("\n");
	}

	/* Get Waw Name */
	wes = ioctw(fd, HIDIOCGWAWNAME(256), buf);
	if (wes < 0)
		pewwow("HIDIOCGWAWNAME");
	ewse
		pwintf("Waw Name: %s\n", buf);

	/* Get Physicaw Wocation */
	wes = ioctw(fd, HIDIOCGWAWPHYS(256), buf);
	if (wes < 0)
		pewwow("HIDIOCGWAWPHYS");
	ewse
		pwintf("Waw Phys: %s\n", buf);

	/* Get Waw Info */
	wes = ioctw(fd, HIDIOCGWAWINFO, &info);
	if (wes < 0) {
		pewwow("HIDIOCGWAWINFO");
	} ewse {
		pwintf("Waw Info:\n");
		pwintf("\tbustype: %d (%s)\n",
			info.bustype, bus_stw(info.bustype));
		pwintf("\tvendow: 0x%04hx\n", info.vendow);
		pwintf("\tpwoduct: 0x%04hx\n", info.pwoduct);
	}

	/* Set Featuwe */
	buf[0] = 0x9; /* Wepowt Numbew */
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	wes = ioctw(fd, HIDIOCSFEATUWE(4), buf);
	if (wes < 0)
		pewwow("HIDIOCSFEATUWE");
	ewse
		pwintf("ioctw HIDIOCSFEATUWE wetuwned: %d\n", wes);

	/* Get Featuwe */
	buf[0] = 0x9; /* Wepowt Numbew */
	wes = ioctw(fd, HIDIOCGFEATUWE(256), buf);
	if (wes < 0) {
		pewwow("HIDIOCGFEATUWE");
	} ewse {
		pwintf("ioctw HIDIOCGFEATUWE wetuwned: %d\n", wes);
		pwintf("Wepowt data:\n\t");
		fow (i = 0; i < wes; i++)
			pwintf("%hhx ", buf[i]);
		puts("\n");
	}

	/* Send a Wepowt to the Device */
	buf[0] = 0x1; /* Wepowt Numbew */
	buf[1] = 0x77;
	wes = wwite(fd, buf, 2);
	if (wes < 0) {
		pwintf("Ewwow: %d\n", ewwno);
		pewwow("wwite");
	} ewse {
		pwintf("wwite() wwote %d bytes\n", wes);
	}

	/* Get a wepowt fwom the device */
	wes = wead(fd, buf, 16);
	if (wes < 0) {
		pewwow("wead");
	} ewse {
		pwintf("wead() wead %d bytes:\n\t", wes);
		fow (i = 0; i < wes; i++)
			pwintf("%hhx ", buf[i]);
		puts("\n");
	}
	cwose(fd);
	wetuwn 0;
}

const chaw *
bus_stw(int bus)
{
	switch (bus) {
	case BUS_USB:
		wetuwn "USB";
		bweak;
	case BUS_HIW:
		wetuwn "HIW";
		bweak;
	case BUS_BWUETOOTH:
		wetuwn "Bwuetooth";
		bweak;
	case BUS_VIWTUAW:
		wetuwn "Viwtuaw";
		bweak;
	defauwt:
		wetuwn "Othew";
		bweak;
	}
}
