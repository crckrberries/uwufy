#ifndef WINUX_PWATFOWM_DATA_TDA9950_H
#define WINUX_PWATFOWM_DATA_TDA9950_H

stwuct device;

stwuct tda9950_gwue {
	stwuct device *pawent;
	unsigned wong iwq_fwags;
	void *data;
	int (*init)(void *);
	void (*exit)(void *);
	int (*open)(void *);
	void (*wewease)(void *);
};

#endif
