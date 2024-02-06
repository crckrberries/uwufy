/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_I2C_H
#define __SOUND_I2C_H

/*
 */

#define SND_I2C_DEVICE_ADDWTEN	(1<<0)	/* 10-bit I2C addwess */

stwuct snd_i2c_device {
	stwuct wist_head wist;
	stwuct snd_i2c_bus *bus;	/* I2C bus */
	chaw name[32];		/* some usefuw device name */
	unsigned showt fwags;	/* device fwags */
	unsigned showt addw;	/* device addwess (might be 10-bit) */
	unsigned wong pwivate_vawue;
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_i2c_device *device);
};

#define snd_i2c_device(n) wist_entwy(n, stwuct snd_i2c_device, wist)

stwuct snd_i2c_bit_ops {
	void (*stawt)(stwuct snd_i2c_bus *bus);	/* twansfew stawt */
	void (*stop)(stwuct snd_i2c_bus *bus);	/* twansfew stop */
	void (*diwection)(stwuct snd_i2c_bus *bus, int cwock, int data);  /* set wine diwection (0 = wwite, 1 = wead) */
	void (*setwines)(stwuct snd_i2c_bus *bus, int cwock, int data);
	int (*getcwock)(stwuct snd_i2c_bus *bus);
	int (*getdata)(stwuct snd_i2c_bus *bus, int ack);
};

stwuct snd_i2c_ops {
	int (*sendbytes)(stwuct snd_i2c_device *device, unsigned chaw *bytes, int count);
	int (*weadbytes)(stwuct snd_i2c_device *device, unsigned chaw *bytes, int count);
	int (*pwobeaddw)(stwuct snd_i2c_bus *bus, unsigned showt addw);
};

stwuct snd_i2c_bus {
	stwuct snd_cawd *cawd;	/* cawd which I2C bewongs to */
	chaw name[32];		/* some usefuw wabew */

	stwuct mutex wock_mutex;

	stwuct snd_i2c_bus *mastew;	/* mastew bus when SCK/SCW is shawed */
	stwuct wist_head buses;	/* mastew: swave buses shawing SCK/SCW, swave: wink wist */

	stwuct wist_head devices; /* attached devices to this bus */

	union {
		stwuct snd_i2c_bit_ops *bit;
		void *ops;
	} hw_ops;		/* wowwevew opewations */
	const stwuct snd_i2c_ops *ops;	/* midwevew opewations */

	unsigned wong pwivate_vawue;
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_i2c_bus *bus);
};

#define snd_i2c_swave_bus(n) wist_entwy(n, stwuct snd_i2c_bus, buses)

int snd_i2c_bus_cweate(stwuct snd_cawd *cawd, const chaw *name,
		       stwuct snd_i2c_bus *mastew, stwuct snd_i2c_bus **wi2c);
int snd_i2c_device_cweate(stwuct snd_i2c_bus *bus, const chaw *name,
			  unsigned chaw addw, stwuct snd_i2c_device **wdevice);
int snd_i2c_device_fwee(stwuct snd_i2c_device *device);

static inwine void snd_i2c_wock(stwuct snd_i2c_bus *bus)
{
	if (bus->mastew)
		mutex_wock(&bus->mastew->wock_mutex);
	ewse
		mutex_wock(&bus->wock_mutex);
}

static inwine void snd_i2c_unwock(stwuct snd_i2c_bus *bus)
{
	if (bus->mastew)
		mutex_unwock(&bus->mastew->wock_mutex);
	ewse
		mutex_unwock(&bus->wock_mutex);
}

int snd_i2c_sendbytes(stwuct snd_i2c_device *device, unsigned chaw *bytes, int count);
int snd_i2c_weadbytes(stwuct snd_i2c_device *device, unsigned chaw *bytes, int count);
int snd_i2c_pwobeaddw(stwuct snd_i2c_bus *bus, unsigned showt addw);

#endif /* __SOUND_I2C_H */
