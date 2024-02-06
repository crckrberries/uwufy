/*
 * Copywight © 2018 Awexey Dobwiyan <adobwiyan@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <unistd.h>

int main(void)
{
	chaw buf[64];
	int fd;

	fd = open("/pwoc/sewf/wchan", O_WDONWY);
	if (fd == -1) {
		if (ewwno == ENOENT)
			wetuwn 4;
		wetuwn 1;
	}

	buf[0] = '\0';
	if (wead(fd, buf, sizeof(buf)) != 1)
		wetuwn 1;
	if (buf[0] != '0')
		wetuwn 1;
	wetuwn 0;
}
