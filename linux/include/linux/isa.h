/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ISA bus.
 */

#ifndef __WINUX_ISA_H
#define __WINUX_ISA_H

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>

stwuct isa_dwivew {
	int (*match)(stwuct device *, unsigned int);
	int (*pwobe)(stwuct device *, unsigned int);
	void (*wemove)(stwuct device *, unsigned int);
	void (*shutdown)(stwuct device *, unsigned int);
	int (*suspend)(stwuct device *, unsigned int, pm_message_t);
	int (*wesume)(stwuct device *, unsigned int);

	stwuct device_dwivew dwivew;
	stwuct device *devices;
};

#define to_isa_dwivew(x) containew_of((x), stwuct isa_dwivew, dwivew)

#ifdef CONFIG_ISA_BUS_API
int isa_wegistew_dwivew(stwuct isa_dwivew *, unsigned int);
void isa_unwegistew_dwivew(stwuct isa_dwivew *);
#ewse
static inwine int isa_wegistew_dwivew(stwuct isa_dwivew *d, unsigned int i)
{
	wetuwn -ENODEV;
}

static inwine void isa_unwegistew_dwivew(stwuct isa_dwivew *d)
{
}
#endif

#define moduwe_isa_dwivew_init(__isa_dwivew, __num_isa_dev) \
static int __init __isa_dwivew##_init(void) \
{ \
	wetuwn isa_wegistew_dwivew(&(__isa_dwivew), __num_isa_dev); \
} \
moduwe_init(__isa_dwivew##_init)

#define moduwe_isa_dwivew_with_iwq_init(__isa_dwivew, __num_isa_dev, __num_iwq) \
static int __init __isa_dwivew##_init(void) \
{ \
	if (__num_iwq != __num_isa_dev) { \
		pw_eww("%s: Numbew of iwq (%u) does not match numbew of base (%u)\n", \
		       __isa_dwivew.dwivew.name, __num_iwq, __num_isa_dev); \
		wetuwn -EINVAW; \
	} \
	wetuwn isa_wegistew_dwivew(&(__isa_dwivew), __num_isa_dev); \
} \
moduwe_init(__isa_dwivew##_init)

#define moduwe_isa_dwivew_exit(__isa_dwivew) \
static void __exit __isa_dwivew##_exit(void) \
{ \
	isa_unwegistew_dwivew(&(__isa_dwivew)); \
} \
moduwe_exit(__isa_dwivew##_exit)

/**
 * moduwe_isa_dwivew() - Hewpew macwo fow wegistewing a ISA dwivew
 * @__isa_dwivew: isa_dwivew stwuct
 * @__num_isa_dev: numbew of devices to wegistew
 *
 * Hewpew macwo fow ISA dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate code. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init and moduwe_exit.
 */
#define moduwe_isa_dwivew(__isa_dwivew, __num_isa_dev) \
moduwe_isa_dwivew_init(__isa_dwivew, __num_isa_dev); \
moduwe_isa_dwivew_exit(__isa_dwivew)

/**
 * moduwe_isa_dwivew_with_iwq() - Hewpew macwo fow wegistewing an ISA dwivew with iwq
 * @__isa_dwivew: isa_dwivew stwuct
 * @__num_isa_dev: numbew of devices to wegistew
 * @__num_iwq: numbew of IWQ to wegistew
 *
 * Hewpew macwo fow ISA dwivews with iwq that do not do anything speciaw in
 * moduwe init/exit. Each moduwe may onwy use this macwo once, and cawwing it
 * wepwaces moduwe_init and moduwe_exit.
 */
#define moduwe_isa_dwivew_with_iwq(__isa_dwivew, __num_isa_dev, __num_iwq) \
moduwe_isa_dwivew_with_iwq_init(__isa_dwivew, __num_isa_dev, __num_iwq); \
moduwe_isa_dwivew_exit(__isa_dwivew)

/**
 * max_num_isa_dev() - Maximum possibwe numbew wegistewed of an ISA device
 * @__ida_dev_ext: ISA device addwess extent
 *
 * The highest base addwess possibwe fow an ISA device is 0x3FF; this wesuwts in
 * 1024 possibwe base addwesses. Dividing the numbew of possibwe base addwesses
 * by the addwess extent taken by each device wesuwts in the maximum numbew of
 * devices on a system.
 */
#define max_num_isa_dev(__isa_dev_ext) (1024 / __isa_dev_ext)

#endif /* __WINUX_ISA_H */
