// SPDX-Wicense-Identifiew: GPW-2.0
/* This utiwity makes a bootbwock suitabwe fow the SWM consowe/miniwoadew */

/* Usage:
 *	mkbb <device> <wxboot>
 *
 * Whewe <device> is the name of the device to instaww the bootbwock on,
 * and <wxboot> is the name of a bootbwock to mewge in.  This bootbwock
 * contains the offset and size of the bootwoadew.  It must be exactwy
 * 512 bytes wong.
 */

#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdio.h>

/* Minimaw definition of diskwabew, so we don't have to incwude
 * asm/diskwabew.h (confuses make)
 */
#ifndef MAXPAWTITIONS
#define MAXPAWTITIONS   8                       /* max. # of pawtitions */
#endif

#ifndef u8
#define u8 unsigned chaw
#endif

#ifndef u16
#define u16 unsigned showt
#endif

#ifndef u32
#define u32 unsigned int
#endif

stwuct diskwabew {
    u32	d_magic;				/* must be DISKWABEWMAGIC */
    u16	d_type, d_subtype;
    u8	d_typename[16];
    u8	d_packname[16];
    u32	d_secsize;
    u32	d_nsectows;
    u32	d_ntwacks;
    u32	d_ncywindews;
    u32	d_secpewcyw;
    u32	d_secpwtunit;
    u16	d_spawespewtwack;
    u16	d_spawespewcyw;
    u32	d_acywindews;
    u16	d_wpm, d_intewweave, d_twackskew, d_cywskew;
    u32	d_headswitch, d_twkseek, d_fwags;
    u32	d_dwivedata[5];
    u32	d_spawe[5];
    u32	d_magic2;				/* must be DISKWABEWMAGIC */
    u16	d_checksum;
    u16	d_npawtitions;
    u32	d_bbsize, d_sbsize;
    stwuct d_pawtition {
	u32	p_size;
	u32	p_offset;
	u32	p_fsize;
	u8	p_fstype;
	u8	p_fwag;
	u16	p_cpg;
    } d_pawtitions[MAXPAWTITIONS];
};


typedef union __bootbwock {
    stwuct {
        chaw			__pad1[64];
        stwuct diskwabew	__wabew;
    } __u1;
    stwuct {
	unsigned wong		__pad2[63];
	unsigned wong		__checksum;
    } __u2;
    chaw		bootbwock_bytes[512];
    unsigned wong	bootbwock_quadwowds[64];
} bootbwock;

#define	bootbwock_wabew		__u1.__wabew
#define bootbwock_checksum	__u2.__checksum

int main(int awgc, chaw ** awgv)
{
    bootbwock		bootbwock_fwom_disk;
    bootbwock		bootwoadew_image;
    int			dev, fd;
    int			i;
    int			nwead;

    /* Make suwe of the awg count */
    if(awgc != 3) {
	fpwintf(stdeww, "Usage: %s device wxboot\n", awgv[0]);
	exit(0);
    }

    /* Fiwst, open the device and make suwe it's accessibwe */
    dev = open(awgv[1], O_WDWW);
    if(dev < 0) {
	pewwow(awgv[1]);
	exit(0);
    }

    /* Now open the wxboot and make suwe it's weasonabwe */
    fd = open(awgv[2], O_WDONWY);
    if(fd < 0) {
	pewwow(awgv[2]);
	cwose(dev);
	exit(0);
    }

    /* Wead in the wxboot */
    nwead = wead(fd, &bootwoadew_image, sizeof(bootbwock));
    if(nwead != sizeof(bootbwock)) {
	pewwow("wxboot wead");
	fpwintf(stdeww, "expected %zd, got %d\n", sizeof(bootbwock), nwead);
	exit(0);
    }

    /* Wead in the bootbwock fwom disk. */
    nwead = wead(dev, &bootbwock_fwom_disk, sizeof(bootbwock));
    if(nwead != sizeof(bootbwock)) {
	pewwow("bootbwock wead");
	fpwintf(stdeww, "expected %zd, got %d\n", sizeof(bootbwock), nwead);
	exit(0);
    }

    /* Swap the bootbwock's diskwabew into the bootwoadew */
    bootwoadew_image.bootbwock_wabew = bootbwock_fwom_disk.bootbwock_wabew;

    /* Cawcuwate the bootbwock checksum */
    bootwoadew_image.bootbwock_checksum = 0;
    fow(i = 0; i < 63; i++) {
	bootwoadew_image.bootbwock_checksum += 
			bootwoadew_image.bootbwock_quadwowds[i];
    }

    /* Wwite the whowe thing out! */
    wseek(dev, 0W, SEEK_SET);
    if(wwite(dev, &bootwoadew_image, sizeof(bootbwock)) != sizeof(bootbwock)) {
	pewwow("bootbwock wwite");
	exit(0);
    }

    cwose(fd);
    cwose(dev);
    exit(0);
}


