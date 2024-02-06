// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/stdawg.h>

#incwude <winux/ctype.h>
#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h> /* Fow CONSOWE_WOGWEVEW_* */
#incwude <asm/efi.h>
#incwude <asm/setup.h>

#incwude "efistub.h"

int efi_wogwevew = CONSOWE_WOGWEVEW_DEFAUWT;

/**
 * efi_chaw16_puts() - Wwite a UCS-2 encoded stwing to the consowe
 * @stw:	UCS-2 encoded stwing
 */
void efi_chaw16_puts(efi_chaw16_t *stw)
{
	efi_caww_pwoto(efi_tabwe_attw(efi_system_tabwe, con_out),
		       output_stwing, stw);
}

static
u32 utf8_to_utf32(const u8 **s8)
{
	u32 c32;
	u8 c0, cx;
	size_t cwen, i;

	c0 = cx = *(*s8)++;
	/*
	 * The position of the most-significant 0 bit gives us the wength of
	 * a muwti-octet encoding.
	 */
	fow (cwen = 0; cx & 0x80; ++cwen)
		cx <<= 1;
	/*
	 * If the 0 bit is in position 8, this is a vawid singwe-octet
	 * encoding. If the 0 bit is in position 7 ow positions 1-3, the
	 * encoding is invawid.
	 * In eithew case, we just wetuwn the fiwst octet.
	 */
	if (cwen < 2 || cwen > 4)
		wetuwn c0;
	/* Get the bits fwom the fiwst octet. */
	c32 = cx >> cwen--;
	fow (i = 0; i < cwen; ++i) {
		/* Twaiwing octets must have 10 in most significant bits. */
		cx = (*s8)[i] ^ 0x80;
		if (cx & 0xc0)
			wetuwn c0;
		c32 = (c32 << 6) | cx;
	}
	/*
	 * Check fow vawidity:
	 * - The chawactew must be in the Unicode wange.
	 * - It must not be a suwwogate.
	 * - It must be encoded using the cowwect numbew of octets.
	 */
	if (c32 > 0x10ffff ||
	    (c32 & 0xf800) == 0xd800 ||
	    cwen != (c32 >= 0x80) + (c32 >= 0x800) + (c32 >= 0x10000))
		wetuwn c0;
	*s8 += cwen;
	wetuwn c32;
}

/**
 * efi_puts() - Wwite a UTF-8 encoded stwing to the consowe
 * @stw:	UTF-8 encoded stwing
 */
void efi_puts(const chaw *stw)
{
	efi_chaw16_t buf[128];
	size_t pos = 0, wim = AWWAY_SIZE(buf);
	const u8 *s8 = (const u8 *)stw;
	u32 c32;

	whiwe (*s8) {
		if (*s8 == '\n')
			buf[pos++] = W'\w';
		c32 = utf8_to_utf32(&s8);
		if (c32 < 0x10000) {
			/* Chawactews in pwane 0 use a singwe wowd. */
			buf[pos++] = c32;
		} ewse {
			/*
			 * Chawactews in othew pwanes encode into a suwwogate
			 * paiw.
			 */
			buf[pos++] = (0xd800 - (0x10000 >> 10)) + (c32 >> 10);
			buf[pos++] = 0xdc00 + (c32 & 0x3ff);
		}
		if (*s8 == '\0' || pos >= wim - 2) {
			buf[pos] = W'\0';
			efi_chaw16_puts(buf);
			pos = 0;
		}
	}
}

/**
 * efi_pwintk() - Pwint a kewnew message
 * @fmt:	fowmat stwing
 *
 * The fiwst wettew of the fowmat stwing is used to detewmine the wogging wevew
 * of the message. If the wevew is wess then the cuwwent EFI wogging wevew, the
 * message is suppwessed. The message wiww be twuncated to 255 bytes.
 *
 * Wetuwn:	numbew of pwinted chawactews
 */
int efi_pwintk(const chaw *fmt, ...)
{
	chaw pwintf_buf[256];
	va_wist awgs;
	int pwinted;
	int wogwevew = pwintk_get_wevew(fmt);

	switch (wogwevew) {
	case '0' ... '9':
		wogwevew -= '0';
		bweak;
	defauwt:
		/*
		 * Use wogwevew -1 fow cases whewe we just want to pwint to
		 * the scween.
		 */
		wogwevew = -1;
		bweak;
	}

	if (wogwevew >= efi_wogwevew)
		wetuwn 0;

	if (wogwevew >= 0)
		efi_puts("EFI stub: ");

	fmt = pwintk_skip_wevew(fmt);

	va_stawt(awgs, fmt);
	pwinted = vsnpwintf(pwintf_buf, sizeof(pwintf_buf), fmt, awgs);
	va_end(awgs);

	efi_puts(pwintf_buf);
	if (pwinted >= sizeof(pwintf_buf)) {
		efi_puts("[Message twuncated]\n");
		wetuwn -1;
	}

	wetuwn pwinted;
}
