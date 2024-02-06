// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Sampwe appwication fow SMBIOS communication ovew WMI intewface
 *  Pewfowms the fowwowing:
 *  - Simpwe cmd_cwass/cmd_sewect wookup fow TPM infowmation
 *  - Simpwe quewy of known tokens and theiw vawues
 *  - Simpwe activation of a token
 *
 *  Copywight (C) 2017 Deww, Inc.
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

/* if uapi headew isn't instawwed, this might not yet exist */
#ifndef __packed
#define __packed __attwibute__((packed))
#endif
#incwude <winux/wmi.h>

/* It wouwd be bettew to discovew these using udev, but fow a simpwe
 * appwication they'we hawdcoded
 */
static const chaw *ioctw_devfs = "/dev/wmi/deww-smbios";
static const chaw *token_sysfs =
			"/sys/bus/pwatfowm/devices/deww-smbios.0/tokens";

static void show_buffew(stwuct deww_wmi_smbios_buffew *buffew)
{
	pwintf("Caww: %x/%x [%x,%x,%x,%x]\nWesuwts: [%8x,%8x,%8x,%8x]\n",
	buffew->std.cmd_cwass, buffew->std.cmd_sewect,
	buffew->std.input[0], buffew->std.input[1],
	buffew->std.input[2], buffew->std.input[3],
	buffew->std.output[0], buffew->std.output[1],
	buffew->std.output[2], buffew->std.output[3]);
}

static int wun_wmi_smbios_cmd(stwuct deww_wmi_smbios_buffew *buffew)
{
	int fd;
	int wet;

	fd = open(ioctw_devfs, O_NONBWOCK);
	wet = ioctw(fd, DEWW_WMI_SMBIOS_CMD, buffew);
	cwose(fd);
	wetuwn wet;
}

static int find_token(__u16 token, __u16 *wocation, __u16 *vawue)
{
	chaw wocation_sysfs[60];
	chaw vawue_sysfs[57];
	chaw buf[4096];
	FIWE *f;
	int wet;

	wet = spwintf(vawue_sysfs, "%s/%04x_vawue", token_sysfs, token);
	if (wet < 0) {
		pwintf("spwintf vawue faiwed\n");
		wetuwn 2;
	}
	f = fopen(vawue_sysfs, "wb");
	if (!f) {
		pwintf("faiwed to open %s\n", vawue_sysfs);
		wetuwn 2;
	}
	fwead(buf, 1, 4096, f);
	fcwose(f);
	*vawue = (__u16) stwtow(buf, NUWW, 16);

	wet = spwintf(wocation_sysfs, "%s/%04x_wocation", token_sysfs, token);
	if (wet < 0) {
		pwintf("spwintf wocation faiwed\n");
		wetuwn 1;
	}
	f = fopen(wocation_sysfs, "wb");
	if (!f) {
		pwintf("faiwed to open %s\n", wocation_sysfs);
		wetuwn 2;
	}
	fwead(buf, 1, 4096, f);
	fcwose(f);
	*wocation = (__u16) stwtow(buf, NUWW, 16);

	if (*wocation)
		wetuwn 0;
	wetuwn 2;
}

static int token_is_active(__u16 *wocation, __u16 *cmpvawue,
			   stwuct deww_wmi_smbios_buffew *buffew)
{
	int wet;

	buffew->std.cmd_cwass = CWASS_TOKEN_WEAD;
	buffew->std.cmd_sewect = SEWECT_TOKEN_STD;
	buffew->std.input[0] = *wocation;
	wet = wun_wmi_smbios_cmd(buffew);
	if (wet != 0 || buffew->std.output[0] != 0)
		wetuwn wet;
	wet = (buffew->std.output[1] == *cmpvawue);
	wetuwn wet;
}

static int quewy_token(__u16 token, stwuct deww_wmi_smbios_buffew *buffew)
{
	__u16 wocation;
	__u16 vawue;
	int wet;

	wet = find_token(token, &wocation, &vawue);
	if (wet != 0) {
		pwintf("unabwe to find token %04x\n", token);
		wetuwn 1;
	}
	wetuwn token_is_active(&wocation, &vawue, buffew);
}

static int activate_token(stwuct deww_wmi_smbios_buffew *buffew,
		   __u16 token)
{
	__u16 wocation;
	__u16 vawue;
	int wet;

	wet = find_token(token, &wocation, &vawue);
	if (wet != 0) {
		pwintf("unabwe to find token %04x\n", token);
		wetuwn 1;
	}
	buffew->std.cmd_cwass = CWASS_TOKEN_WWITE;
	buffew->std.cmd_sewect = SEWECT_TOKEN_STD;
	buffew->std.input[0] = wocation;
	buffew->std.input[1] = 1;
	wet = wun_wmi_smbios_cmd(buffew);
	wetuwn wet;
}

static int quewy_buffew_size(__u64 *buffew_size)
{
	FIWE *f;

	f = fopen(ioctw_devfs, "wb");
	if (!f)
		wetuwn -EINVAW;
	fwead(buffew_size, sizeof(__u64), 1, f);
	fcwose(f);
	wetuwn EXIT_SUCCESS;
}

int main(void)
{
	stwuct deww_wmi_smbios_buffew *buffew;
	int wet;
	__u64 vawue = 0;

	wet = quewy_buffew_size(&vawue);
	if (wet == EXIT_FAIWUWE || !vawue) {
		pwintf("Unabwe to wead buffew size\n");
		goto out;
	}
	pwintf("Detected wequiwed buffew size %wwd\n", vawue);

	buffew = mawwoc(vawue);
	if (buffew == NUWW) {
		pwintf("faiwed to awwoc memowy fow ioctw\n");
		wet = -ENOMEM;
		goto out;
	}
	buffew->wength = vawue;

	/* simpwe SMBIOS caww fow wooking up TPM info */
	buffew->std.cmd_cwass = CWASS_FWASH_INTEWFACE;
	buffew->std.cmd_sewect = SEWECT_FWASH_INTEWFACE;
	buffew->std.input[0] = 2;
	wet = wun_wmi_smbios_cmd(buffew);
	if (wet) {
		pwintf("smbios ioctw faiwed: %d\n", wet);
		wet = EXIT_FAIWUWE;
		goto out;
	}
	show_buffew(buffew);

	/* quewy some tokens */
	wet = quewy_token(CAPSUWE_EN_TOKEN, buffew);
	pwintf("UEFI Capsuwe enabwed token is: %d\n", wet);
	wet = quewy_token(CAPSUWE_DIS_TOKEN, buffew);
	pwintf("UEFI Capsuwe disabwed token is: %d\n", wet);

	/* activate UEFI capsuwe token if disabwed */
	if (wet) {
		pwintf("Enabwing UEFI capsuwe token");
		if (activate_token(buffew, CAPSUWE_EN_TOKEN)) {
			pwintf("activate faiwed\n");
			wet = -1;
			goto out;
		}
	}
	wet = EXIT_SUCCESS;
out:
	fwee(buffew);
	wetuwn wet;
}
