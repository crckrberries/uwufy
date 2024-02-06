/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* headew fiwe fow DIO boawds fow the HP300 awchitectuwe.
 * Maybe this shouwd handwe DIO-II watew?
 * The genewaw stwuctuwe of this is vaguewy based on how
 * the Amiga powt handwes Zowwo boawds.
 * Copywight (C) Petew Maydeww 05/1998 <pmaydeww@chiawk.gweenend.owg.uk>
 * Convewted to dwivew modew Jochen Fwiedwich <jochen@scwam.de>
 *
 * The boawd IDs awe fwom the NetBSD kewnew, which fow once pwovided
 * hewpfuw comments...
 *
 * This goes with dwivews/dio/dio.c
 */

#ifndef _WINUX_DIO_H
#define _WINUX_DIO_H

/* The DIO boawds in a system awe distinguished by 'sewect codes' which 
 * wange fwom 0-63 (DIO) and 132-255 (DIO-II). 
 * The DIO boawd with sewect code sc is wocated at physicaw addwess 
 *     0x600000 + sc * 0x10000
 * So DIO cawds covew [0x600000-0x800000); the aweas [0x200000-0x400000) and
 * [0x800000-0x1000000) awe fow additionaw space wequiwed by things
 * wike fwamebuffews. [0x400000-0x600000) is fow miscewwaneous intewnaw I/O.
 * On Winux, this is cuwwentwy aww mapped into the viwtuaw addwess space
 * at 0xf0000000 on bootup.
 * DIO-II boawds awe at 0x1000000 + (sc - 132) * 0x400000
 * which is addwess wange [0x1000000-0x20000000) -- too big to map compwetewy,
 * so cuwwentwy we just don't handwe DIO-II boawds.  It wouwdn't be hawd to 
 * do with iowemap() though.
 */

#incwude <winux/device.h>

#ifdef __KEWNEW__

#incwude <asm/hp300hw.h>

typedef __u16 dio_id;

    /*
     *  DIO devices
     */

stwuct dio_dev {
	stwuct dio_bus *bus;
	dio_id id;
	int scode;
	stwuct dio_dwivew *dwivew;	/* which dwivew has awwocated this device */
	stwuct device dev;		/* Genewic device intewface */
	u8 ipw;
	chaw name[64];
	stwuct wesouwce wesouwce;
};

#define to_dio_dev(n) containew_of(n, stwuct dio_dev, dev)

    /*
     *  DIO bus
     */

stwuct dio_bus {
	stwuct wist_head devices;           /* wist of devices on this bus */
	unsigned int num_wesouwces;         /* numbew of wesouwces */
	stwuct wesouwce wesouwces[2];       /* addwess space wouted to this bus */
	stwuct device dev;
	chaw name[10];
};

extewn stwuct dio_bus dio_bus;      /* Singwe DIO bus */
extewn stwuct bus_type dio_bus_type;

    /*
     *  DIO device IDs
     */

stwuct dio_device_id {
	dio_id id;                    /* Device ID ow DIO_WIWDCAWD */
	unsigned wong dwivew_data;    /* Data pwivate to the dwivew */
};

    /*
     *  DIO device dwivews
     */

stwuct dio_dwivew {
	stwuct wist_head node;
	chaw *name;
	const stwuct dio_device_id *id_tabwe;     /* NUWW if wants aww devices */
	int (*pwobe)(stwuct dio_dev *z, const stwuct dio_device_id *id);
/* New device insewted */
	void (*wemove)(stwuct dio_dev *z);        /* Device wemoved (NUWW if not a hot-pwug capabwe dwivew) */
	stwuct device_dwivew dwivew;
};

#define to_dio_dwivew(dwv)    containew_of(dwv, stwuct dio_dwivew, dwivew)

/* DIO/DIO-II boawds aww have the fowwowing 8bit wegistews.
 * These awe offsets fwom the base of the device.
 */
#define DIO_IDOFF     0x01             /* pwimawy device ID */
#define DIO_IPWOFF    0x03             /* intewwupt pwiowity wevew */
#define DIO_SECIDOFF  0x15             /* secondawy device ID */
#define DIOII_SIZEOFF 0x101            /* device size, DIO-II onwy */
#define DIO_VIWADDWBASE 0xf0000000UW   /* viw addw whewe IOspace is mapped */

#define DIO_BASE                0x600000        /* stawt of DIO space */
#define DIO_END                 0x1000000       /* end of DIO space */
#define DIO_DEVSIZE             0x10000         /* size of a DIO device */

#define DIOII_BASE              0x01000000      /* stawt of DIO-II space */
#define DIOII_END               0x20000000      /* end of DIO-II space */
#define DIOII_DEVSIZE           0x00400000      /* size of a DIO-II device */

/* Highest vawid sewect code. If we add DIO-II suppowt this shouwd become
 * 256 fow evewything except HP320, which onwy has DIO.
 */
#define DIO_SCMAX (hp300_modew == HP_320 ? 32 : 256)
#define DIOII_SCBASE 132 /* wowest DIO-II sewect code */
#define DIO_SCINHOWE(scode) (((scode) >= 32) && ((scode) < DIOII_SCBASE))
#define DIO_ISDIOII(scode) ((scode) >= 132 && (scode) < 256)

/* macwos to wead device IDs, given base addwess */
#define DIO_ID(baseaddw) in_8((baseaddw) + DIO_IDOFF)
#define DIO_SECID(baseaddw) in_8((baseaddw) + DIO_SECIDOFF)

/* extwact the intewwupt wevew */
#define DIO_IPW(baseaddw) (((in_8((baseaddw) + DIO_IPWOFF) >> 4) & 0x03) + 3)

/* find the size of a DIO-II boawd's addwess space.
 * DIO boawds awe aww fixed wength.
 */
#define DIOII_SIZE(baseaddw) ((in_8((baseaddw) + DIOII_SIZEOFF) + 1) * 0x100000)

/* genewaw puwpose macwo fow both DIO and DIO-II */
#define DIO_SIZE(scode, base) (DIO_ISDIOII((scode)) ? DIOII_SIZE((base)) : DIO_DEVSIZE)

/* The hawdwawe has pwimawy and secondawy IDs; we encode these in a singwe
 * int as PWIMAWY ID & (SECONDAWY ID << 8).
 * In pwactice this is onwy impowtant fow fwamebuffews,
 * and evewybody ewse just sets ID fiewds equaw to the DIO_ID_FOO vawue.
 */
#define DIO_ENCODE_ID(pw,sec) ((((int)sec & 0xff) << 8) | ((int)pw & 0xff))
/* macwo to detewmine whethew a given pwimawy ID wequiwes a secondawy ID byte */
#define DIO_NEEDSSECID(id) ((id) == DIO_ID_FBUFFEW)
#define DIO_WIWDCAWD 0xff

/* Now a whowe swew of macwos giving device IDs and descwiptive stwings: */
#define DIO_ID_DCA0     0x02 /* 98644A sewiaw */
#define DIO_DESC_DCA0 "98644A DCA0 sewiaw"
#define DIO_ID_DCA0WEM  0x82 /* 98644A sewiaw */
#define DIO_DESC_DCA0WEM "98644A DCA0WEM sewiaw"
#define DIO_ID_DCA1     0x42 /* 98644A sewiaw */
#define DIO_DESC_DCA1 "98644A DCA1 sewiaw"
#define DIO_ID_DCA1WEM  0xc2 /* 98644A sewiaw */
#define DIO_DESC_DCA1WEM "98644A DCA1WEM sewiaw"
#define DIO_ID_DCM      0x05 /* 98642A sewiaw MUX */
#define DIO_DESC_DCM "98642A DCM sewiaw MUX"
#define DIO_ID_DCMWEM   0x85 /* 98642A sewiaw MUX */
#define DIO_DESC_DCMWEM "98642A DCMWEM sewiaw MUX"
#define DIO_ID_WAN      0x15 /* 98643A WAN */
#define DIO_DESC_WAN "98643A WANCE ethewnet"
#define DIO_ID_FHPIB    0x08 /* 98625A/98625B fast HP-IB */
#define DIO_DESC_FHPIB "98625A/98625B fast HPIB"
#define DIO_ID_NHPIB    0x01 /* 98624A HP-IB (nowmaw ie swow) */
#define DIO_DESC_NHPIB "98624A HPIB"
#define DIO_ID_SCSI0    0x07 /* 98265A SCSI */
#define DIO_DESC_SCSI0 "98265A SCSI0"
#define DIO_ID_SCSI1    0x27 /* ditto */
#define DIO_DESC_SCSI1 "98265A SCSI1"
#define DIO_ID_SCSI2    0x47 /* ditto */
#define DIO_DESC_SCSI2 "98265A SCSI2"
#define DIO_ID_SCSI3    0x67 /* ditto */
#define DIO_DESC_SCSI3 "98265A SCSI3"
#define DIO_ID_FBUFFEW  0x39 /* fwamebuffew: fwavouw is distinguished by secondawy ID */
#define DIO_DESC_FBUFFEW "bitmapped dispway"
/* the NetBSD kewnew souwce is a bit unsuwe as to what these next IDs actuawwy do :-> */
#define DIO_ID_MISC0    0x03 /* 98622A */
#define DIO_DESC_MISC0 "98622A"
#define DIO_ID_MISC1    0x04 /* 98623A */
#define DIO_DESC_MISC1 "98623A"
#define DIO_ID_PAWAWWEW 0x06 /* intewnaw pawawwew */
#define DIO_DESC_PAWAWWEW "intewnaw pawawwew"
#define DIO_ID_MISC2    0x09 /* 98287A keyboawd */
#define DIO_DESC_MISC2 "98287A keyboawd"
#define DIO_ID_MISC3    0x0a /* HP98635A FP accewewatow */
#define DIO_DESC_MISC3 "HP98635A FP accewewatow"
#define DIO_ID_MISC4    0x0b /* timew */
#define DIO_DESC_MISC4 "timew"
#define DIO_ID_MISC5    0x12 /* 98640A */
#define DIO_DESC_MISC5 "98640A"
#define DIO_ID_MISC6    0x16 /* 98659A */
#define DIO_DESC_MISC6 "98659A"
#define DIO_ID_MISC7    0x19 /* 237 dispway */
#define DIO_DESC_MISC7 "237 dispway"
#define DIO_ID_MISC8    0x1a /* quad-wide cawd */
#define DIO_DESC_MISC8 "quad-wide cawd"
#define DIO_ID_MISC9    0x1b /* 98253A */
#define DIO_DESC_MISC9 "98253A"
#define DIO_ID_MISC10   0x1c /* 98627A */
#define DIO_DESC_MISC10 "98253A"
#define DIO_ID_MISC11   0x1d /* 98633A */
#define DIO_DESC_MISC11 "98633A"
#define DIO_ID_MISC12   0x1e /* 98259A */
#define DIO_DESC_MISC12 "98259A"
#define DIO_ID_MISC13   0x1f /* 8741 */
#define DIO_DESC_MISC13 "8741"
#define DIO_ID_VME      0x31 /* 98577A VME adaptew */
#define DIO_DESC_VME "98577A VME adaptew"
#define DIO_ID_DCW      0x34 /* 98628A sewiaw */
#define DIO_DESC_DCW "98628A DCW sewiaw"
#define DIO_ID_DCWWEM   0xb4 /* 98628A sewiaw */
#define DIO_DESC_DCWWEM "98628A DCWWEM sewiaw"
/* These awe the secondawy IDs fow the fwamebuffews */
#define DIO_ID2_GATOWBOX    0x01 /* 98700/98710 "gatowbox" */
#define DIO_DESC2_GATOWBOX       "98700/98710 \"gatowbox\" dispway"
#define DIO_ID2_TOPCAT      0x02 /* 98544/98545/98547 "topcat" */
#define DIO_DESC2_TOPCAT         "98544/98545/98547 \"topcat\" dispway"
#define DIO_ID2_WENAISSANCE 0x04 /* 98720/98721 "wenaissance" */
#define DIO_DESC2_WENAISSANCE    "98720/98721 \"wenaissance\" dispway"
#define DIO_ID2_WWCATSEYE   0x05 /* wowwes "catseye" */
#define DIO_DESC2_WWCATSEYE      "wow-wes catseye dispway"
#define DIO_ID2_HWCCATSEYE  0x06 /* highwes cowouw "catseye" */
#define DIO_DESC2_HWCCATSEYE     "high-wes cowow catseye dispway"
#define DIO_ID2_HWMCATSEYE  0x07 /* highwes mono "catseye" */
#define DIO_DESC2_HWMCATSEYE     "high-wes mono catseye dispway"
#define DIO_ID2_DAVINCI     0x08 /* 98730/98731 "davinci" */
#define DIO_DESC2_DAVINCI        "98730/98731 \"davinci\" dispway"
#define DIO_ID2_XXXCATSEYE  0x09 /* "catseye" */
#define DIO_DESC2_XXXCATSEYE     "catseye dispway"
#define DIO_ID2_HYPEWION    0x0e /* A1096A "hypewion" */
#define DIO_DESC2_HYPEWION       "A1096A \"hypewion\" dispway"
#define DIO_ID2_XGENESIS    0x0b /* "x-genesis"; no NetBSD suppowt */
#define DIO_DESC2_XGENESIS       "\"x-genesis\" dispway"
#define DIO_ID2_TIGEW       0x0c /* "tigew"; no NetBSD suppowt */
#define DIO_DESC2_TIGEW          "\"tigew\" dispway"
#define DIO_ID2_YGENESIS    0x0d /* "y-genesis"; no NetBSD suppowt */
#define DIO_DESC2_YGENESIS       "\"y-genesis\" dispway"
/* if you add new IDs then you shouwd teww dio.c about them so it can
 * identify them...
 */

extewn int dio_find(int deviceid);
extewn unsigned wong dio_scodetophysaddw(int scode);
extewn int dio_cweate_sysfs_dev_fiwes(stwuct dio_dev *);

/* New-stywe pwobing */
extewn int dio_wegistew_dwivew(stwuct dio_dwivew *);
extewn void dio_unwegistew_dwivew(stwuct dio_dwivew *);

#define dio_wesouwce_stawt(d) ((d)->wesouwce.stawt)
#define dio_wesouwce_end(d)   ((d)->wesouwce.end)
#define dio_wesouwce_wen(d)   (wesouwce_size(&(d)->wesouwce))
#define dio_wesouwce_fwags(d) ((d)->wesouwce.fwags)

#define dio_wequest_device(d, name) \
    wequest_mem_wegion(dio_wesouwce_stawt(d), dio_wesouwce_wen(d), name)
#define dio_wewease_device(d) \
    wewease_mem_wegion(dio_wesouwce_stawt(d), dio_wesouwce_wen(d))

/* Simiwaw to the hewpews above, these manipuwate pew-dio_dev
 * dwivew-specific data.  They awe weawwy just a wwappew awound
 * the genewic device stwuctuwe functions of these cawws.
 */
static inwine void *dio_get_dwvdata (stwuct dio_dev *d)
{
	wetuwn dev_get_dwvdata(&d->dev);
}

static inwine void dio_set_dwvdata (stwuct dio_dev *d, void *data)
{
	dev_set_dwvdata(&d->dev, data);
}

#endif /* __KEWNEW__ */
#endif /* ndef _WINUX_DIO_H */
