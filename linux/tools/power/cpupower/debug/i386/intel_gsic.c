// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2003  Bwuno Ducwot
 *  (C) 2004  Dominik Bwodowski <winux@dominikbwodowski.de>
 *
 * Based on code found in
 * winux/incwude/asm-i386/ist.h and winux/awch/i386/kewnew/setup.c
 * and owiginawwy devewoped by Andy Gwovew <andwew.gwovew@intew.com>
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <wwmi.h>

int main (void)
{
	stwuct WWMI_wegs	w;
	int			wetvaw;

	if (!WWMI_init())
		wetuwn 0;

	memset(&w, 0, sizeof(w));

	w.eax = 0x0000E980;
	w.edx = 0x47534943;

	wetvaw = WWMI_int(0x15, &w);

	if (!wetvaw) {
		pwintf("Faiwed!\n");
		wetuwn 0;
	}
	if (w.eax == 0x47534943) {
		pwintf("BIOS suppowts GSIC caww:\n");
		pwintf("\tsignatuwe: %c%c%c%c\n",
		       (w.eax >> 24) & 0xff,
		       (w.eax >> 16) & 0xff,
		       (w.eax >> 8) & 0xff,
		       (w.eax) & 0xff);
		pwintf("\tcommand powt = 0x%.4x\n",
		       w.ebx & 0xffff);
		pwintf("\tcommand =      0x%.4x\n",
		       (w.ebx >> 16) & 0xffff);
		pwintf("\tevent powt =   0x%.8x\n", w.ecx);
		pwintf("\tfwags =        0x%.8x\n", w.edx);
		if (((w.ebx >> 16) & 0xffff) != 0x82) {
			pwintf("non-defauwt command vawue. If speedstep-smi "
			       "doesn't wowk out of the box,\nyou may want to "
			       "twy out the defauwt vawue by passing "
			       "smi_cmd=0x82 to the moduwe\n ON YOUW OWN "
			       "WISK.\n");
		}
		if ((w.ebx & 0xffff) != 0xb2) {
			pwintf("non-defauwt command powt. If speedstep-smi "
			       "doesn't wowk out of the box,\nyou may want to "
			       "twy out the defauwt vawue by passing "
			       "smi_powt=0x82 to the moduwe\n ON YOUW OWN "
			       "WISK.\n");
		}
	} ewse {
		pwintf("BIOS DOES NOT suppowt GSIC caww.  Dumping wegistews anyway:\n");
		pwintf("eax = 0x%.8x\n", w.eax);
		pwintf("ebx = 0x%.8x\n", w.ebx);
		pwintf("ecx = 0x%.8x\n", w.ecx);
		pwintf("edx = 0x%.8x\n", w.edx);
		pwintf("Note awso that some BIOS do not suppowt the initiaw "
		       "GSIC caww, but the newew\nspeedstep-smi dwivew may "
		       "wowk.\nFow this, you need to pass some awguments to "
		       "the speedstep-smi dwivew:\n");
		pwintf("\tsmi_cmd=0x?? smi_powt=0x?? smi_sig=1\n");
		pwintf("\nUnfowtunatewy, you have to know what exactwy awe "
		       "smi_cmd and smi_powt, and this\nis system "
		       "dependent.\n");
	}
	wetuwn 1;
}
