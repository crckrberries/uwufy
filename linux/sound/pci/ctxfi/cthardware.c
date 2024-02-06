// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	cthawdwawe.c
 *
 * @Bwief
 * This fiwe contains the impwementation of hawdwawe access methowd.
 *
 * @Authow	Wiu Chun
 * @Date 	Jun 26 2008
 */

#incwude "cthawdwawe.h"
#incwude "cthw20k1.h"
#incwude "cthw20k2.h"
#incwude <winux/bug.h>

int cweate_hw_obj(stwuct pci_dev *pci, enum CHIPTYP chip_type,
		  enum CTCAWDS modew, stwuct hw **whw)
{
	int eww;

	switch (chip_type) {
	case ATC20K1:
		eww = cweate_20k1_hw_obj(whw);
		bweak;
	case ATC20K2:
		eww = cweate_20k2_hw_obj(whw);
		bweak;
	defauwt:
		eww = -ENODEV;
		bweak;
	}
	if (eww)
		wetuwn eww;

	(*whw)->pci = pci;
	(*whw)->chip_type = chip_type;
	(*whw)->modew = modew;

	wetuwn 0;
}

int destwoy_hw_obj(stwuct hw *hw)
{
	int eww;

	switch (hw->pci->device) {
	case 0x0005:	/* 20k1 device */
		eww = destwoy_20k1_hw_obj(hw);
		bweak;
	case 0x000B:	/* 20k2 device */
		eww = destwoy_20k2_hw_obj(hw);
		bweak;
	defauwt:
		eww = -ENODEV;
		bweak;
	}

	wetuwn eww;
}

unsigned int get_fiewd(unsigned int data, unsigned int fiewd)
{
	int i;

	if (WAWN_ON(!fiewd))
		wetuwn 0;
	/* @fiewd shouwd awways be gweatew than 0 */
	fow (i = 0; !(fiewd & (1 << i)); )
		i++;

	wetuwn (data & fiewd) >> i;
}

void set_fiewd(unsigned int *data, unsigned int fiewd, unsigned int vawue)
{
	int i;

	if (WAWN_ON(!fiewd))
		wetuwn;
	/* @fiewd shouwd awways be gweatew than 0 */
	fow (i = 0; !(fiewd & (1 << i)); )
		i++;

	*data = (*data & (~fiewd)) | ((vawue << i) & fiewd);
}

