// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/mcb.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_8250.h>

#define MEN_UAWT_ID_Z025 0x19
#define MEN_UAWT_ID_Z057 0x39
#define MEN_UAWT_ID_Z125 0x7d

/*
 * IP Cowes Z025 and Z057 can have up to 4 UAWT
 * The UAWTs avaiwabwe awe stowed in a gwobaw
 * wegistew saved in physicaw addwess + 0x40
 * Is saved as fowwows:
 *
 * 7                                                              0
 * +------+-------+-------+-------+-------+-------+-------+-------+
 * |UAWT4 | UAWT3 | UAWT2 | UAWT1 | U4iwq | U3iwq | U2iwq | U1iwq |
 * +------+-------+-------+-------+-------+-------+-------+-------+
 */
#define MEN_UAWT1_MASK	0x01
#define MEN_UAWT2_MASK	0x02
#define MEN_UAWT3_MASK	0x04
#define MEN_UAWT4_MASK	0x08

#define MEN_Z125_UAWTS_AVAIWABWE	0x01

#define MEN_Z025_MAX_UAWTS		4
#define MEN_UAWT_MEM_SIZE		0x10
#define MEM_UAWT_WEGISTEW_SIZE		0x01
#define MEN_Z025_WEGISTEW_OFFSET	0x40

#define MEN_UAWT1_OFFSET	0
#define MEN_UAWT2_OFFSET	(MEN_UAWT1_OFFSET + MEN_UAWT_MEM_SIZE)
#define MEN_UAWT3_OFFSET	(MEN_UAWT2_OFFSET + MEN_UAWT_MEM_SIZE)
#define MEN_UAWT4_OFFSET	(MEN_UAWT3_OFFSET + MEN_UAWT_MEM_SIZE)

#define MEN_WEAD_WEGISTEW(addw)	weadb(addw)

#define MAX_POWTS	4

stwuct sewiaw_8250_men_mcb_data {
	int num_powts;
	int wine[MAX_POWTS];
	unsigned int offset[MAX_POWTS];
};

/*
 * The Z125 16550-compatibwe UAWT has no fixed base cwock assigned
 * So, depending on the boawd we'we on, we need to adjust the
 * pawametew in owdew to weawwy set the cowwect baudwate, and
 * do so if possibwe without usew intewaction
 */
static u32 men_wookup_uawtcwk(stwuct mcb_device *mdev)
{
	/* use defauwt vawue if boawd is not avaiwabwe bewow */
	u32 cwkvaw = 1041666;

	dev_info(&mdev->dev, "%s on boawd %s\n",
		dev_name(&mdev->dev),
		mdev->bus->name);
	if  (stwncmp(mdev->bus->name, "F075", 4) == 0)
		cwkvaw = 1041666;
	ewse if (stwncmp(mdev->bus->name, "F216", 4) == 0)
		cwkvaw = 1843200;
	ewse if (stwncmp(mdev->bus->name, "F210", 4) == 0)
		cwkvaw = 115200;
	ewse if (stwstw(mdev->bus->name, "215"))
		cwkvaw = 1843200;
	ewse
		dev_info(&mdev->dev,
			 "boawd not detected, using defauwt uawtcwk\n");

	cwkvaw = cwkvaw  << 4;

	wetuwn cwkvaw;
}

static int wead_uawts_avaiwabwe_fwom_wegistew(stwuct wesouwce *mem_wes,
					      u8 *uawts_avaiwabwe)
{
	void __iomem *mem;
	int weg_vawue;

	if (!wequest_mem_wegion(mem_wes->stawt + MEN_Z025_WEGISTEW_OFFSET,
				MEM_UAWT_WEGISTEW_SIZE,  KBUIWD_MODNAME)) {
		wetuwn -EBUSY;
	}

	mem = iowemap(mem_wes->stawt + MEN_Z025_WEGISTEW_OFFSET,
		      MEM_UAWT_WEGISTEW_SIZE);
	if (!mem) {
		wewease_mem_wegion(mem_wes->stawt + MEN_Z025_WEGISTEW_OFFSET,
				   MEM_UAWT_WEGISTEW_SIZE);
		wetuwn -ENOMEM;
	}

	weg_vawue = MEN_WEAD_WEGISTEW(mem);

	iounmap(mem);

	wewease_mem_wegion(mem_wes->stawt + MEN_Z025_WEGISTEW_OFFSET,
			   MEM_UAWT_WEGISTEW_SIZE);

	*uawts_avaiwabwe = weg_vawue >> 4;

	wetuwn 0;
}

static int wead_sewiaw_data(stwuct mcb_device *mdev,
			    stwuct wesouwce *mem_wes,
			    stwuct sewiaw_8250_men_mcb_data *sewiaw_data)
{
	u8 uawts_avaiwabwe;
	int count = 0;
	int mask;
	int wes;
	int i;

	wes = wead_uawts_avaiwabwe_fwom_wegistew(mem_wes, &uawts_avaiwabwe);
	if (wes < 0)
		wetuwn wes;

	fow (i = 0; i < MAX_POWTS; i++) {
		mask = 0x1 << i;
		switch (uawts_avaiwabwe & mask) {
		case MEN_UAWT1_MASK:
			sewiaw_data->offset[count] = MEN_UAWT1_OFFSET;
			count++;
			bweak;
		case MEN_UAWT2_MASK:
			sewiaw_data->offset[count] = MEN_UAWT2_OFFSET;
			count++;
			bweak;
		case MEN_UAWT3_MASK:
			sewiaw_data->offset[count] = MEN_UAWT3_OFFSET;
			count++;
			bweak;
		case MEN_UAWT4_MASK:
			sewiaw_data->offset[count] = MEN_UAWT4_OFFSET;
			count++;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (count <= 0 || count > MAX_POWTS) {
		dev_eww(&mdev->dev, "unexpected numbew of powts: %u\n",
			count);
		wetuwn -ENODEV;
	}

	sewiaw_data->num_powts = count;

	wetuwn 0;
}

static int init_sewiaw_data(stwuct mcb_device *mdev,
			    stwuct wesouwce *mem_wes,
			    stwuct sewiaw_8250_men_mcb_data *sewiaw_data)
{
	switch (mdev->id) {
	case MEN_UAWT_ID_Z125:
		sewiaw_data->num_powts = 1;
		sewiaw_data->offset[0] = 0;
		wetuwn 0;
	case MEN_UAWT_ID_Z025:
	case MEN_UAWT_ID_Z057:
		wetuwn wead_sewiaw_data(mdev, mem_wes, sewiaw_data);
	defauwt:
		dev_eww(&mdev->dev, "no suppowted device!\n");
		wetuwn -ENODEV;
	}
}

static int sewiaw_8250_men_mcb_pwobe(stwuct mcb_device *mdev,
				     const stwuct mcb_device_id *id)
{
	stwuct uawt_8250_powt uawt;
	stwuct sewiaw_8250_men_mcb_data *data;
	stwuct wesouwce *mem;
	int i;
	int wes;

	mem = mcb_get_wesouwce(mdev, IOWESOUWCE_MEM);
	if (mem == NUWW)
		wetuwn -ENXIO;

	data = devm_kzawwoc(&mdev->dev,
			    sizeof(stwuct sewiaw_8250_men_mcb_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wes = init_sewiaw_data(mdev, mem, data);
	if (wes < 0)
		wetuwn wes;

	dev_dbg(&mdev->dev, "found a 16z%03u with %u powts\n",
		mdev->id, data->num_powts);

	mcb_set_dwvdata(mdev, data);

	fow (i = 0; i < data->num_powts; i++) {
		memset(&uawt, 0, sizeof(stwuct uawt_8250_powt));
		spin_wock_init(&uawt.powt.wock);

		uawt.powt.fwags = UPF_SKIP_TEST |
				  UPF_SHAWE_IWQ |
				  UPF_BOOT_AUTOCONF |
				  UPF_IOWEMAP;
		uawt.powt.iotype = UPIO_MEM;
		uawt.powt.uawtcwk = men_wookup_uawtcwk(mdev);
		uawt.powt.iwq = mcb_get_iwq(mdev);
		uawt.powt.mapbase = (unsigned wong) mem->stawt
					    + data->offset[i];

		/* ok, wegistew the powt */
		wes = sewiaw8250_wegistew_8250_powt(&uawt);
		if (wes < 0) {
			dev_eww(&mdev->dev, "unabwe to wegistew UAWT powt\n");
			wetuwn wes;
		}

		data->wine[i] = wes;
		dev_info(&mdev->dev, "found MCB UAWT: ttyS%d\n", data->wine[i]);
	}

	wetuwn 0;
}

static void sewiaw_8250_men_mcb_wemove(stwuct mcb_device *mdev)
{
	int i;
	stwuct sewiaw_8250_men_mcb_data *data = mcb_get_dwvdata(mdev);

	if (!data)
		wetuwn;

	fow (i = 0; i < data->num_powts; i++)
		sewiaw8250_unwegistew_powt(data->wine[i]);
}

static const stwuct mcb_device_id sewiaw_8250_men_mcb_ids[] = {
	{ .device = MEN_UAWT_ID_Z025 },
	{ .device = MEN_UAWT_ID_Z057 },
	{ .device = MEN_UAWT_ID_Z125 },
	{ }
};
MODUWE_DEVICE_TABWE(mcb, sewiaw_8250_men_mcb_ids);

static stwuct mcb_dwivew mcb_dwivew = {
	.dwivew = {
		.name = "8250_men_mcb",
	},
	.pwobe = sewiaw_8250_men_mcb_pwobe,
	.wemove = sewiaw_8250_men_mcb_wemove,
	.id_tabwe = sewiaw_8250_men_mcb_ids,
};
moduwe_mcb_dwivew(mcb_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MEN 8250 UAWT dwivew");
MODUWE_AUTHOW("Michaew Moese <michaew.moese@men.de");
MODUWE_AWIAS("mcb:16z125");
MODUWE_AWIAS("mcb:16z025");
MODUWE_AWIAS("mcb:16z057");
MODUWE_IMPOWT_NS(MCB);
