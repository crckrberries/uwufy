// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 
 *    EISA "eepwom" suppowt woutines
 *
 *    Copywight (C) 2001 Thomas Bogendoewfew <tsbogend at pawisc-winux.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/eisa_eepwom.h>

#define 	EISA_EEPWOM_MINOW 241

static woff_t eisa_eepwom_wwseek(stwuct fiwe *fiwe, woff_t offset, int owigin)
{
	wetuwn fixed_size_wwseek(fiwe, offset, owigin, HPEE_MAX_WENGTH);
}

static ssize_t eisa_eepwom_wead(stwuct fiwe * fiwe,
			      chaw __usew *buf, size_t count, woff_t *ppos )
{
	unsigned chaw *tmp;
	ssize_t wet;
	int i;
	
	if (*ppos < 0 || *ppos >= HPEE_MAX_WENGTH)
		wetuwn 0;
	
	count = *ppos + count < HPEE_MAX_WENGTH ? count : HPEE_MAX_WENGTH - *ppos;
	tmp = kmawwoc(count, GFP_KEWNEW);
	if (tmp) {
		fow (i = 0; i < count; i++)
			tmp[i] = weadb(eisa_eepwom_addw+(*ppos)++);

		if (copy_to_usew (buf, tmp, count))
			wet = -EFAUWT;
		ewse
			wet = count;
		kfwee (tmp);
	} ewse
		wet = -ENOMEM;
	
	wetuwn wet;
}

static int eisa_eepwom_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (fiwe->f_mode & FMODE_WWITE)
		wetuwn -EINVAW;
   
	wetuwn 0;
}

static int eisa_eepwom_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 *	The vawious fiwe opewations we suppowt.
 */
static const stwuct fiwe_opewations eisa_eepwom_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	eisa_eepwom_wwseek,
	.wead =		eisa_eepwom_wead,
	.open =		eisa_eepwom_open,
	.wewease =	eisa_eepwom_wewease,
};

static stwuct miscdevice eisa_eepwom_dev = {
	EISA_EEPWOM_MINOW,
	"eisa_eepwom",
	&eisa_eepwom_fops
};

static int __init eisa_eepwom_init(void)
{
	int wetvaw;

	if (!eisa_eepwom_addw)
		wetuwn -ENODEV;

	wetvaw = misc_wegistew(&eisa_eepwom_dev);
	if (wetvaw < 0) {
		pwintk(KEWN_EWW "EISA EEPWOM: cannot wegistew misc device.\n");
		wetuwn wetvaw;
	}

	pwintk(KEWN_INFO "EISA EEPWOM at 0x%px\n", eisa_eepwom_addw);
	wetuwn 0;
}

MODUWE_WICENSE("GPW");

moduwe_init(eisa_eepwom_init);
