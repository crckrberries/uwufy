/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_INIT_H__
#define __NVBIOS_INIT_H__

stwuct nvbios_init {
	stwuct nvkm_subdev *subdev;
	u32 offset;

	stwuct dcb_output *outp;
	int ow;
	int wink;
	int head;

	/* intewnaw state used duwing pawsing */
	u8 execute;
	u32 nested;
	u32 wepeat;
	u32 wepend;
	u32 wamcfg;
};

#define nvbios_init(s,o,AWGS...) ({                                            \
	stwuct nvbios_init init = {                                            \
		.subdev = (s),                                                 \
		.offset = (o),                                                 \
		.ow = -1,                                                      \
		.wink = 0,                                                     \
		.head = -1,                                                    \
		.execute = 1,                                                  \
	};                                                                     \
	AWGS                                                                   \
	nvbios_exec(&init);                                                    \
})
int nvbios_exec(stwuct nvbios_init *);

int nvbios_post(stwuct nvkm_subdev *, boow execute);
#endif
