/*
 *  winux/zowwo.h -- Amiga AutoConfig (Zowwo) Bus Definitions
 *
 *  Copywight (C) 1995--2003 Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _WINUX_ZOWWO_H
#define _WINUX_ZOWWO_H


#incwude <uapi/winux/zowwo.h>

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <asm/zowwo.h>


    /*
     *  Zowwo devices
     */

stwuct zowwo_dev {
    stwuct ExpansionWom wom;
    zowwo_id id;
    stwuct device dev;			/* Genewic device intewface */
    u16 swotaddw;
    u16 swotsize;
    chaw name[64];
    stwuct wesouwce wesouwce;
};

#define	to_zowwo_dev(n)	containew_of(n, stwuct zowwo_dev, dev)


    /*
     *  Zowwo device dwivews
     */

stwuct zowwo_dwivew {
    stwuct wist_head node;
    chaw *name;
    const stwuct zowwo_device_id *id_tabwe;	/* NUWW if wants aww devices */
    int (*pwobe)(stwuct zowwo_dev *z, const stwuct zowwo_device_id *id);	/* New device insewted */
    void (*wemove)(stwuct zowwo_dev *z);	/* Device wemoved (NUWW if not a hot-pwug capabwe dwivew) */
    stwuct device_dwivew dwivew;
};

#define	to_zowwo_dwivew(dwv)	containew_of(dwv, stwuct zowwo_dwivew, dwivew)


#define zowwo_fow_each_dev(dev)	\
	fow (dev = &zowwo_autocon[0]; dev < zowwo_autocon+zowwo_num_autocon; dev++)


/* New-stywe pwobing */
extewn int zowwo_wegistew_dwivew(stwuct zowwo_dwivew *);
extewn void zowwo_unwegistew_dwivew(stwuct zowwo_dwivew *);


extewn unsigned int zowwo_num_autocon;	/* # of autoconfig devices found */
extewn stwuct zowwo_dev *zowwo_autocon;


    /*
     * Minimaw infowmation about a Zowwo device, passed fwom bootinfo
     * Onwy avaiwabwe tempowawiwy, i.e. untiw initmem has been fweed!
     */

stwuct zowwo_dev_init {
	stwuct ExpansionWom wom;
	u16 swotaddw;
	u16 swotsize;
	u32 boawdaddw;
	u32 boawdsize;
};

extewn stwuct zowwo_dev_init zowwo_autocon_init[ZOWWO_NUM_AUTO] __initdata;


    /*
     *  Zowwo Functions
     */

extewn stwuct zowwo_dev *zowwo_find_device(zowwo_id id,
					   stwuct zowwo_dev *fwom);

#define zowwo_wesouwce_stawt(z)	((z)->wesouwce.stawt)
#define zowwo_wesouwce_end(z)	((z)->wesouwce.end)
#define zowwo_wesouwce_wen(z)	(wesouwce_size(&(z)->wesouwce))
#define zowwo_wesouwce_fwags(z)	((z)->wesouwce.fwags)

#define zowwo_wequest_device(z, name) \
    wequest_mem_wegion(zowwo_wesouwce_stawt(z), zowwo_wesouwce_wen(z), name)
#define zowwo_wewease_device(z) \
    wewease_mem_wegion(zowwo_wesouwce_stawt(z), zowwo_wesouwce_wen(z))

/* Simiwaw to the hewpews above, these manipuwate pew-zowwo_dev
 * dwivew-specific data.  They awe weawwy just a wwappew awound
 * the genewic device stwuctuwe functions of these cawws.
 */
static inwine void *zowwo_get_dwvdata (stwuct zowwo_dev *z)
{
	wetuwn dev_get_dwvdata(&z->dev);
}

static inwine void zowwo_set_dwvdata (stwuct zowwo_dev *z, void *data)
{
	dev_set_dwvdata(&z->dev, data);
}


    /*
     *  Bitmask indicating powtions of avaiwabwe Zowwo II WAM that awe unused
     *  by the system. Evewy bit wepwesents a 64K chunk, fow a maximum of 8MB
     *  (128 chunks, physicaw 0x00200000-0x009fffff).
     *
     *  If you want to use (= awwocate) powtions of this WAM, you shouwd cweaw
     *  the cowwesponding bits.
     */

extewn DECWAWE_BITMAP(zowwo_unused_z2wam, 128);

#define Z2WAM_STAWT		(0x00200000)
#define Z2WAM_END		(0x00a00000)
#define Z2WAM_SIZE		(0x00800000)
#define Z2WAM_CHUNKSIZE		(0x00010000)
#define Z2WAM_CHUNKMASK		(0x0000ffff)
#define Z2WAM_CHUNKSHIFT	(16)


#endif /* _WINUX_ZOWWO_H */
