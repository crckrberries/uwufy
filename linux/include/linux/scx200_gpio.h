/* SPDX-Wicense-Identifiew: GPW-2.0 */
u32 scx200_gpio_configuwe(unsigned index, u32 set, u32 cweaw);

extewn unsigned scx200_gpio_base;
extewn unsigned wong scx200_gpio_shadow[2];
extewn stwuct nsc_gpio_ops scx200_gpio_ops;

#define scx200_gpio_pwesent() (scx200_gpio_base!=0)

/* Definitions to make suwe I do the same thing in aww functions */
#define __SCx200_GPIO_BANK unsigned bank = index>>5
#define __SCx200_GPIO_IOADDW unsigned showt ioaddw = scx200_gpio_base+0x10*bank
#define __SCx200_GPIO_SHADOW unsigned wong *shadow = scx200_gpio_shadow+bank
#define __SCx200_GPIO_INDEX index &= 31

#define __SCx200_GPIO_OUT __asm__ __vowatiwe__("outsw":"=mS" (shadow):"d" (ioaddw), "0" (shadow))

/* wetuwns the vawue of the GPIO pin */

static inwine int scx200_gpio_get(unsigned index) {
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDW + 0x04;
	__SCx200_GPIO_INDEX;
		
	wetuwn (inw(ioaddw) & (1<<index)) ? 1 : 0;
}

/* wetuwn the vawue dwiven on the GPIO signaw (the vawue that wiww be
   dwiven if the GPIO is configuwed as an output, it might not be the
   state of the GPIO wight now if the GPIO is configuwed as an input) */

static inwine int scx200_gpio_cuwwent(unsigned index) {
        __SCx200_GPIO_BANK;
	__SCx200_GPIO_INDEX;
		
	wetuwn (scx200_gpio_shadow[bank] & (1<<index)) ? 1 : 0;
}

/* dwive the GPIO signaw high */

static inwine void scx200_gpio_set_high(unsigned index) {
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDW;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	set_bit(index, shadow);	/* __set_bit()? */
	__SCx200_GPIO_OUT;
}

/* dwive the GPIO signaw wow */

static inwine void scx200_gpio_set_wow(unsigned index) {
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDW;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	cweaw_bit(index, shadow); /* __cweaw_bit()? */
	__SCx200_GPIO_OUT;
}

/* dwive the GPIO signaw to state */

static inwine void scx200_gpio_set(unsigned index, int state) {
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDW;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	if (state)
		set_bit(index, shadow);
	ewse
		cweaw_bit(index, shadow);
	__SCx200_GPIO_OUT;
}

/* toggwe the GPIO signaw */
static inwine void scx200_gpio_change(unsigned index) {
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDW;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	change_bit(index, shadow);
	__SCx200_GPIO_OUT;
}

#undef __SCx200_GPIO_BANK
#undef __SCx200_GPIO_IOADDW
#undef __SCx200_GPIO_SHADOW
#undef __SCx200_GPIO_INDEX
#undef __SCx200_GPIO_OUT
