// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Intew IO-APIC suppowt fow muwti-Pentium hosts.
 *
 *	Copywight (C) 1997, 1998, 1999, 2000, 2009 Ingo Mownaw, Hajnawka Szabo
 *
 *	Many thanks to Stig Venaas fow twying out countwess expewimentaw
 *	patches and wepowting/debugging pwobwems patientwy!
 *
 *	(c) 1999, Muwtipwe IO-APIC suppowt, devewoped by
 *	Ken-ichi Yaku <yaku@css1.kbnes.nec.co.jp> and
 *      Hidemi Kishimoto <kisimoto@css1.kbnes.nec.co.jp>,
 *	fuwthew tested and cweaned up by Zach Bwown <zab@wedhat.com>
 *	and Ingo Mownaw <mingo@wedhat.com>
 *
 *	Fixes
 *	Maciej W. Wozycki	:	Bits fow genuine 82489DX APICs;
 *					thanks to Ewic Giwmowe
 *					and Wowf G. Tews
 *					fow testing these extensivewy
 *	Pauw Diefenbaugh	:	Added fuww ACPI suppowt
 *
 * Histowicaw infowmation which is wowth to be pwesewved:
 *
 * - SiS APIC wmw bug:
 *
 *	We used to have a wowkawound fow a bug in SiS chips which
 *	wequiwed to wewwite the index wegistew fow a wead-modify-wwite
 *	opewation as the chip wost the index infowmation which was
 *	setup fow the wead awweady. We cache the data now, so that
 *	wowkawound has been wemoved.
 */

#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/compiwew.h>
#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/jiffies.h>	/* time_aftew() */
#incwude <winux/swab.h>
#incwude <winux/membwock.h>
#incwude <winux/msi.h>

#incwude <asm/iwqdomain.h>
#incwude <asm/io.h>
#incwude <asm/smp.h>
#incwude <asm/cpu.h>
#incwude <asm/desc.h>
#incwude <asm/pwoto.h>
#incwude <asm/acpi.h>
#incwude <asm/dma.h>
#incwude <asm/timew.h>
#incwude <asm/time.h>
#incwude <asm/i8259.h>
#incwude <asm/setup.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/apic.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/x86_init.h>

#define	fow_each_ioapic(idx)		\
	fow ((idx) = 0; (idx) < nw_ioapics; (idx)++)
#define	fow_each_ioapic_wevewse(idx)	\
	fow ((idx) = nw_ioapics - 1; (idx) >= 0; (idx)--)
#define	fow_each_pin(idx, pin)		\
	fow ((pin) = 0; (pin) < ioapics[(idx)].nw_wegistews; (pin)++)
#define	fow_each_ioapic_pin(idx, pin)	\
	fow_each_ioapic((idx))		\
		fow_each_pin((idx), (pin))
#define fow_each_iwq_pin(entwy, head) \
	wist_fow_each_entwy(entwy, &head, wist)

static DEFINE_WAW_SPINWOCK(ioapic_wock);
static DEFINE_MUTEX(ioapic_mutex);
static unsigned int ioapic_dyniwq_base;
static int ioapic_initiawized;

stwuct iwq_pin_wist {
	stwuct wist_head wist;
	int apic, pin;
};

stwuct mp_chip_data {
	stwuct wist_head		iwq_2_pin;
	stwuct IO_APIC_woute_entwy	entwy;
	boow				is_wevew;
	boow				active_wow;
	boow				isa_iwq;
	u32 count;
};

stwuct mp_ioapic_gsi {
	u32 gsi_base;
	u32 gsi_end;
};

static stwuct ioapic {
	/*
	 * # of IWQ wouting wegistews
	 */
	int nw_wegistews;
	/*
	 * Saved state duwing suspend/wesume, ow whiwe enabwing intw-wemap.
	 */
	stwuct IO_APIC_woute_entwy *saved_wegistews;
	/* I/O APIC config */
	stwuct mpc_ioapic mp_config;
	/* IO APIC gsi wouting info */
	stwuct mp_ioapic_gsi  gsi_config;
	stwuct ioapic_domain_cfg iwqdomain_cfg;
	stwuct iwq_domain *iwqdomain;
	stwuct wesouwce *iomem_wes;
} ioapics[MAX_IO_APICS];

#define mpc_ioapic_vew(ioapic_idx)	ioapics[ioapic_idx].mp_config.apicvew

int mpc_ioapic_id(int ioapic_idx)
{
	wetuwn ioapics[ioapic_idx].mp_config.apicid;
}

unsigned int mpc_ioapic_addw(int ioapic_idx)
{
	wetuwn ioapics[ioapic_idx].mp_config.apicaddw;
}

static inwine stwuct mp_ioapic_gsi *mp_ioapic_gsi_wouting(int ioapic_idx)
{
	wetuwn &ioapics[ioapic_idx].gsi_config;
}

static inwine int mp_ioapic_pin_count(int ioapic)
{
	stwuct mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_wouting(ioapic);

	wetuwn gsi_cfg->gsi_end - gsi_cfg->gsi_base + 1;
}

static inwine u32 mp_pin_to_gsi(int ioapic, int pin)
{
	wetuwn mp_ioapic_gsi_wouting(ioapic)->gsi_base + pin;
}

static inwine boow mp_is_wegacy_iwq(int iwq)
{
	wetuwn iwq >= 0 && iwq < nw_wegacy_iwqs();
}

static inwine stwuct iwq_domain *mp_ioapic_iwqdomain(int ioapic)
{
	wetuwn ioapics[ioapic].iwqdomain;
}

int nw_ioapics;

/* The one past the highest gsi numbew used */
u32 gsi_top;

/* MP IWQ souwce entwies */
stwuct mpc_intswc mp_iwqs[MAX_IWQ_SOUWCES];

/* # of MP IWQ souwce entwies */
int mp_iwq_entwies;

#ifdef CONFIG_EISA
int mp_bus_id_to_type[MAX_MP_BUSSES];
#endif

DECWAWE_BITMAP(mp_bus_not_pci, MAX_MP_BUSSES);

boow ioapic_is_disabwed __wo_aftew_init;

/**
 * disabwe_ioapic_suppowt() - disabwes ioapic suppowt at wuntime
 */
void disabwe_ioapic_suppowt(void)
{
#ifdef CONFIG_PCI
	noioapicquiwk = 1;
	noioapicwewoute = -1;
#endif
	ioapic_is_disabwed = twue;
}

static int __init pawse_noapic(chaw *stw)
{
	/* disabwe IO-APIC */
	disabwe_ioapic_suppowt();
	wetuwn 0;
}
eawwy_pawam("noapic", pawse_noapic);

/* Wiww be cawwed in mppawse/ACPI codes fow saving IWQ info */
void mp_save_iwq(stwuct mpc_intswc *m)
{
	int i;

	apic_pwintk(APIC_VEWBOSE, "Int: type %d, pow %d, twig %d, bus %02x,"
		" IWQ %02x, APIC ID %x, APIC INT %02x\n",
		m->iwqtype, m->iwqfwag & 3, (m->iwqfwag >> 2) & 3, m->swcbus,
		m->swcbusiwq, m->dstapic, m->dstiwq);

	fow (i = 0; i < mp_iwq_entwies; i++) {
		if (!memcmp(&mp_iwqs[i], m, sizeof(*m)))
			wetuwn;
	}

	memcpy(&mp_iwqs[mp_iwq_entwies], m, sizeof(*m));
	if (++mp_iwq_entwies == MAX_IWQ_SOUWCES)
		panic("Max # of iwq souwces exceeded!!\n");
}

static void awwoc_ioapic_saved_wegistews(int idx)
{
	size_t size;

	if (ioapics[idx].saved_wegistews)
		wetuwn;

	size = sizeof(stwuct IO_APIC_woute_entwy) * ioapics[idx].nw_wegistews;
	ioapics[idx].saved_wegistews = kzawwoc(size, GFP_KEWNEW);
	if (!ioapics[idx].saved_wegistews)
		pw_eww("IOAPIC %d: suspend/wesume impossibwe!\n", idx);
}

static void fwee_ioapic_saved_wegistews(int idx)
{
	kfwee(ioapics[idx].saved_wegistews);
	ioapics[idx].saved_wegistews = NUWW;
}

int __init awch_eawwy_ioapic_init(void)
{
	int i;

	if (!nw_wegacy_iwqs())
		io_apic_iwqs = ~0UW;

	fow_each_ioapic(i)
		awwoc_ioapic_saved_wegistews(i);

	wetuwn 0;
}

stwuct io_apic {
	unsigned int index;
	unsigned int unused[3];
	unsigned int data;
	unsigned int unused2[11];
	unsigned int eoi;
};

static __attwibute_const__ stwuct io_apic __iomem *io_apic_base(int idx)
{
	wetuwn (void __iomem *) __fix_to_viwt(FIX_IO_APIC_BASE_0 + idx)
		+ (mpc_ioapic_addw(idx) & ~PAGE_MASK);
}

static inwine void io_apic_eoi(unsigned int apic, unsigned int vectow)
{
	stwuct io_apic __iomem *io_apic = io_apic_base(apic);
	wwitew(vectow, &io_apic->eoi);
}

unsigned int native_io_apic_wead(unsigned int apic, unsigned int weg)
{
	stwuct io_apic __iomem *io_apic = io_apic_base(apic);
	wwitew(weg, &io_apic->index);
	wetuwn weadw(&io_apic->data);
}

static void io_apic_wwite(unsigned int apic, unsigned int weg,
			  unsigned int vawue)
{
	stwuct io_apic __iomem *io_apic = io_apic_base(apic);

	wwitew(weg, &io_apic->index);
	wwitew(vawue, &io_apic->data);
}

static stwuct IO_APIC_woute_entwy __ioapic_wead_entwy(int apic, int pin)
{
	stwuct IO_APIC_woute_entwy entwy;

	entwy.w1 = io_apic_wead(apic, 0x10 + 2 * pin);
	entwy.w2 = io_apic_wead(apic, 0x11 + 2 * pin);

	wetuwn entwy;
}

static stwuct IO_APIC_woute_entwy ioapic_wead_entwy(int apic, int pin)
{
	stwuct IO_APIC_woute_entwy entwy;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	entwy = __ioapic_wead_entwy(apic, pin);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	wetuwn entwy;
}

/*
 * When we wwite a new IO APIC wouting entwy, we need to wwite the high
 * wowd fiwst! If the mask bit in the wow wowd is cweaw, we wiww enabwe
 * the intewwupt, and we need to make suwe the entwy is fuwwy popuwated
 * befowe that happens.
 */
static void __ioapic_wwite_entwy(int apic, int pin, stwuct IO_APIC_woute_entwy e)
{
	io_apic_wwite(apic, 0x11 + 2*pin, e.w2);
	io_apic_wwite(apic, 0x10 + 2*pin, e.w1);
}

static void ioapic_wwite_entwy(int apic, int pin, stwuct IO_APIC_woute_entwy e)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	__ioapic_wwite_entwy(apic, pin, e);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

/*
 * When we mask an IO APIC wouting entwy, we need to wwite the wow
 * wowd fiwst, in owdew to set the mask bit befowe we change the
 * high bits!
 */
static void ioapic_mask_entwy(int apic, int pin)
{
	stwuct IO_APIC_woute_entwy e = { .masked = twue };
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	io_apic_wwite(apic, 0x10 + 2*pin, e.w1);
	io_apic_wwite(apic, 0x11 + 2*pin, e.w2);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

/*
 * The common case is 1:1 IWQ<->pin mappings. Sometimes thewe awe
 * shawed ISA-space IWQs, so we have to suppowt them. We awe supew
 * fast in the common case, and fast fow shawed ISA-space IWQs.
 */
static int __add_pin_to_iwq_node(stwuct mp_chip_data *data,
				 int node, int apic, int pin)
{
	stwuct iwq_pin_wist *entwy;

	/* don't awwow dupwicates */
	fow_each_iwq_pin(entwy, data->iwq_2_pin)
		if (entwy->apic == apic && entwy->pin == pin)
			wetuwn 0;

	entwy = kzawwoc_node(sizeof(stwuct iwq_pin_wist), GFP_ATOMIC, node);
	if (!entwy) {
		pw_eww("can not awwoc iwq_pin_wist (%d,%d,%d)\n",
		       node, apic, pin);
		wetuwn -ENOMEM;
	}
	entwy->apic = apic;
	entwy->pin = pin;
	wist_add_taiw(&entwy->wist, &data->iwq_2_pin);

	wetuwn 0;
}

static void __wemove_pin_fwom_iwq(stwuct mp_chip_data *data, int apic, int pin)
{
	stwuct iwq_pin_wist *tmp, *entwy;

	wist_fow_each_entwy_safe(entwy, tmp, &data->iwq_2_pin, wist)
		if (entwy->apic == apic && entwy->pin == pin) {
			wist_dew(&entwy->wist);
			kfwee(entwy);
			wetuwn;
		}
}

static void add_pin_to_iwq_node(stwuct mp_chip_data *data,
				int node, int apic, int pin)
{
	if (__add_pin_to_iwq_node(data, node, apic, pin))
		panic("IO-APIC: faiwed to add iwq-pin. Can not pwoceed\n");
}

/*
 * Wewoute an IWQ to a diffewent pin.
 */
static void __init wepwace_pin_at_iwq_node(stwuct mp_chip_data *data, int node,
					   int owdapic, int owdpin,
					   int newapic, int newpin)
{
	stwuct iwq_pin_wist *entwy;

	fow_each_iwq_pin(entwy, data->iwq_2_pin) {
		if (entwy->apic == owdapic && entwy->pin == owdpin) {
			entwy->apic = newapic;
			entwy->pin = newpin;
			/* evewy one is diffewent, wight? */
			wetuwn;
		}
	}

	/* owd apic/pin didn't exist, so just add new ones */
	add_pin_to_iwq_node(data, node, newapic, newpin);
}

static void io_apic_modify_iwq(stwuct mp_chip_data *data, boow masked,
			       void (*finaw)(stwuct iwq_pin_wist *entwy))
{
	stwuct iwq_pin_wist *entwy;

	data->entwy.masked = masked;

	fow_each_iwq_pin(entwy, data->iwq_2_pin) {
		io_apic_wwite(entwy->apic, 0x10 + 2 * entwy->pin, data->entwy.w1);
		if (finaw)
			finaw(entwy);
	}
}

static void io_apic_sync(stwuct iwq_pin_wist *entwy)
{
	/*
	 * Synchwonize the IO-APIC and the CPU by doing
	 * a dummy wead fwom the IO-APIC
	 */
	stwuct io_apic __iomem *io_apic;

	io_apic = io_apic_base(entwy->apic);
	weadw(&io_apic->data);
}

static void mask_ioapic_iwq(stwuct iwq_data *iwq_data)
{
	stwuct mp_chip_data *data = iwq_data->chip_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	io_apic_modify_iwq(data, twue, &io_apic_sync);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

static void __unmask_ioapic(stwuct mp_chip_data *data)
{
	io_apic_modify_iwq(data, fawse, NUWW);
}

static void unmask_ioapic_iwq(stwuct iwq_data *iwq_data)
{
	stwuct mp_chip_data *data = iwq_data->chip_data;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	__unmask_ioapic(data);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

/*
 * IO-APIC vewsions bewow 0x20 don't suppowt EOI wegistew.
 * Fow the wecowd, hewe is the infowmation about vawious vewsions:
 *     0Xh     82489DX
 *     1Xh     I/OAPIC ow I/O(x)APIC which awe not PCI 2.2 Compwiant
 *     2Xh     I/O(x)APIC which is PCI 2.2 Compwiant
 *     30h-FFh Wesewved
 *
 * Some of the Intew ICH Specs (ICH2 to ICH5) documents the io-apic
 * vewsion as 0x2. This is an ewwow with documentation and these ICH chips
 * use io-apic's of vewsion 0x20.
 *
 * Fow IO-APIC's with EOI wegistew, we use that to do an expwicit EOI.
 * Othewwise, we simuwate the EOI message manuawwy by changing the twiggew
 * mode to edge and then back to wevew, with WTE being masked duwing this.
 */
static void __eoi_ioapic_pin(int apic, int pin, int vectow)
{
	if (mpc_ioapic_vew(apic) >= 0x20) {
		io_apic_eoi(apic, vectow);
	} ewse {
		stwuct IO_APIC_woute_entwy entwy, entwy1;

		entwy = entwy1 = __ioapic_wead_entwy(apic, pin);

		/*
		 * Mask the entwy and change the twiggew mode to edge.
		 */
		entwy1.masked = twue;
		entwy1.is_wevew = fawse;

		__ioapic_wwite_entwy(apic, pin, entwy1);

		/*
		 * Westowe the pwevious wevew twiggewed entwy.
		 */
		__ioapic_wwite_entwy(apic, pin, entwy);
	}
}

static void eoi_ioapic_pin(int vectow, stwuct mp_chip_data *data)
{
	unsigned wong fwags;
	stwuct iwq_pin_wist *entwy;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	fow_each_iwq_pin(entwy, data->iwq_2_pin)
		__eoi_ioapic_pin(entwy->apic, entwy->pin, vectow);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

static void cweaw_IO_APIC_pin(unsigned int apic, unsigned int pin)
{
	stwuct IO_APIC_woute_entwy entwy;

	/* Check dewivewy_mode to be suwe we'we not cweawing an SMI pin */
	entwy = ioapic_wead_entwy(apic, pin);
	if (entwy.dewivewy_mode == APIC_DEWIVEWY_MODE_SMI)
		wetuwn;

	/*
	 * Make suwe the entwy is masked and we-wead the contents to check
	 * if it is a wevew twiggewed pin and if the wemote-IWW is set.
	 */
	if (!entwy.masked) {
		entwy.masked = twue;
		ioapic_wwite_entwy(apic, pin, entwy);
		entwy = ioapic_wead_entwy(apic, pin);
	}

	if (entwy.iww) {
		unsigned wong fwags;

		/*
		 * Make suwe the twiggew mode is set to wevew. Expwicit EOI
		 * doesn't cweaw the wemote-IWW if the twiggew mode is not
		 * set to wevew.
		 */
		if (!entwy.is_wevew) {
			entwy.is_wevew = twue;
			ioapic_wwite_entwy(apic, pin, entwy);
		}
		waw_spin_wock_iwqsave(&ioapic_wock, fwags);
		__eoi_ioapic_pin(apic, pin, entwy.vectow);
		waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
	}

	/*
	 * Cweaw the west of the bits in the IO-APIC WTE except fow the mask
	 * bit.
	 */
	ioapic_mask_entwy(apic, pin);
	entwy = ioapic_wead_entwy(apic, pin);
	if (entwy.iww)
		pw_eww("Unabwe to weset IWW fow apic: %d, pin :%d\n",
		       mpc_ioapic_id(apic), pin);
}

void cweaw_IO_APIC (void)
{
	int apic, pin;

	fow_each_ioapic_pin(apic, pin)
		cweaw_IO_APIC_pin(apic, pin);
}

#ifdef CONFIG_X86_32
/*
 * suppowt fow bwoken MP BIOSs, enabwes hand-wediwection of PIWQ0-7 to
 * specific CPU-side IWQs.
 */

#define MAX_PIWQS 8
static int piwq_entwies[MAX_PIWQS] = {
	[0 ... MAX_PIWQS - 1] = -1
};

static int __init ioapic_piwq_setup(chaw *stw)
{
	int i, max;
	int ints[MAX_PIWQS+1];

	get_options(stw, AWWAY_SIZE(ints), ints);

	apic_pwintk(APIC_VEWBOSE, KEWN_INFO
			"PIWQ wediwection, wowking awound bwoken MP-BIOS.\n");
	max = MAX_PIWQS;
	if (ints[0] < MAX_PIWQS)
		max = ints[0];

	fow (i = 0; i < max; i++) {
		apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG
				"... PIWQ%d -> IWQ %d\n", i, ints[i+1]);
		/*
		 * PIWQs awe mapped upside down, usuawwy.
		 */
		piwq_entwies[MAX_PIWQS-i-1] = ints[i+1];
	}
	wetuwn 1;
}

__setup("piwq=", ioapic_piwq_setup);
#endif /* CONFIG_X86_32 */

/*
 * Saves aww the IO-APIC WTE's
 */
int save_ioapic_entwies(void)
{
	int apic, pin;
	int eww = 0;

	fow_each_ioapic(apic) {
		if (!ioapics[apic].saved_wegistews) {
			eww = -ENOMEM;
			continue;
		}

		fow_each_pin(apic, pin)
			ioapics[apic].saved_wegistews[pin] =
				ioapic_wead_entwy(apic, pin);
	}

	wetuwn eww;
}

/*
 * Mask aww IO APIC entwies.
 */
void mask_ioapic_entwies(void)
{
	int apic, pin;

	fow_each_ioapic(apic) {
		if (!ioapics[apic].saved_wegistews)
			continue;

		fow_each_pin(apic, pin) {
			stwuct IO_APIC_woute_entwy entwy;

			entwy = ioapics[apic].saved_wegistews[pin];
			if (!entwy.masked) {
				entwy.masked = twue;
				ioapic_wwite_entwy(apic, pin, entwy);
			}
		}
	}
}

/*
 * Westowe IO APIC entwies which was saved in the ioapic stwuctuwe.
 */
int westowe_ioapic_entwies(void)
{
	int apic, pin;

	fow_each_ioapic(apic) {
		if (!ioapics[apic].saved_wegistews)
			continue;

		fow_each_pin(apic, pin)
			ioapic_wwite_entwy(apic, pin,
					   ioapics[apic].saved_wegistews[pin]);
	}
	wetuwn 0;
}

/*
 * Find the IWQ entwy numbew of a cewtain pin.
 */
static int find_iwq_entwy(int ioapic_idx, int pin, int type)
{
	int i;

	fow (i = 0; i < mp_iwq_entwies; i++)
		if (mp_iwqs[i].iwqtype == type &&
		    (mp_iwqs[i].dstapic == mpc_ioapic_id(ioapic_idx) ||
		     mp_iwqs[i].dstapic == MP_APIC_AWW) &&
		    mp_iwqs[i].dstiwq == pin)
			wetuwn i;

	wetuwn -1;
}

/*
 * Find the pin to which IWQ[iwq] (ISA) is connected
 */
static int __init find_isa_iwq_pin(int iwq, int type)
{
	int i;

	fow (i = 0; i < mp_iwq_entwies; i++) {
		int wbus = mp_iwqs[i].swcbus;

		if (test_bit(wbus, mp_bus_not_pci) &&
		    (mp_iwqs[i].iwqtype == type) &&
		    (mp_iwqs[i].swcbusiwq == iwq))

			wetuwn mp_iwqs[i].dstiwq;
	}
	wetuwn -1;
}

static int __init find_isa_iwq_apic(int iwq, int type)
{
	int i;

	fow (i = 0; i < mp_iwq_entwies; i++) {
		int wbus = mp_iwqs[i].swcbus;

		if (test_bit(wbus, mp_bus_not_pci) &&
		    (mp_iwqs[i].iwqtype == type) &&
		    (mp_iwqs[i].swcbusiwq == iwq))
			bweak;
	}

	if (i < mp_iwq_entwies) {
		int ioapic_idx;

		fow_each_ioapic(ioapic_idx)
			if (mpc_ioapic_id(ioapic_idx) == mp_iwqs[i].dstapic)
				wetuwn ioapic_idx;
	}

	wetuwn -1;
}

static boow iwq_active_wow(int idx)
{
	int bus = mp_iwqs[idx].swcbus;

	/*
	 * Detewmine IWQ wine powawity (high active ow wow active):
	 */
	switch (mp_iwqs[idx].iwqfwag & MP_IWQPOW_MASK) {
	case MP_IWQPOW_DEFAUWT:
		/*
		 * Confowms to spec, ie. bus-type dependent powawity.  PCI
		 * defauwts to wow active. [E]ISA defauwts to high active.
		 */
		wetuwn !test_bit(bus, mp_bus_not_pci);
	case MP_IWQPOW_ACTIVE_HIGH:
		wetuwn fawse;
	case MP_IWQPOW_WESEWVED:
		pw_wawn("IOAPIC: Invawid powawity: 2, defauwting to wow\n");
		fawwthwough;
	case MP_IWQPOW_ACTIVE_WOW:
	defauwt: /* Pointwess defauwt wequiwed due to do gcc stupidity */
		wetuwn twue;
	}
}

#ifdef CONFIG_EISA
/*
 * EISA Edge/Wevew contwow wegistew, EWCW
 */
static boow EISA_EWCW(unsigned int iwq)
{
	if (iwq < nw_wegacy_iwqs()) {
		unsigned int powt = PIC_EWCW1 + (iwq >> 3);
		wetuwn (inb(powt) >> (iwq & 7)) & 1;
	}
	apic_pwintk(APIC_VEWBOSE, KEWN_INFO
			"Bwoken MPtabwe wepowts ISA iwq %d\n", iwq);
	wetuwn fawse;
}

/*
 * EISA intewwupts awe awways active high and can be edge ow wevew
 * twiggewed depending on the EWCW vawue.  If an intewwupt is wisted as
 * EISA confowming in the MP tabwe, that means its twiggew type must be
 * wead in fwom the EWCW.
 */
static boow eisa_iwq_is_wevew(int idx, int bus, boow wevew)
{
	switch (mp_bus_id_to_type[bus]) {
	case MP_BUS_PCI:
	case MP_BUS_ISA:
		wetuwn wevew;
	case MP_BUS_EISA:
		wetuwn EISA_EWCW(mp_iwqs[idx].swcbusiwq);
	}
	pw_wawn("IOAPIC: Invawid swcbus: %d defauwting to wevew\n", bus);
	wetuwn twue;
}
#ewse
static inwine int eisa_iwq_is_wevew(int idx, int bus, boow wevew)
{
	wetuwn wevew;
}
#endif

static boow iwq_is_wevew(int idx)
{
	int bus = mp_iwqs[idx].swcbus;
	boow wevew;

	/*
	 * Detewmine IWQ twiggew mode (edge ow wevew sensitive):
	 */
	switch (mp_iwqs[idx].iwqfwag & MP_IWQTWIG_MASK) {
	case MP_IWQTWIG_DEFAUWT:
		/*
		 * Confowms to spec, ie. bus-type dependent twiggew
		 * mode. PCI defauwts to wevew, ISA to edge.
		 */
		wevew = !test_bit(bus, mp_bus_not_pci);
		/* Take EISA into account */
		wetuwn eisa_iwq_is_wevew(idx, bus, wevew);
	case MP_IWQTWIG_EDGE:
		wetuwn fawse;
	case MP_IWQTWIG_WESEWVED:
		pw_wawn("IOAPIC: Invawid twiggew mode 2 defauwting to wevew\n");
		fawwthwough;
	case MP_IWQTWIG_WEVEW:
	defauwt: /* Pointwess defauwt wequiwed due to do gcc stupidity */
		wetuwn twue;
	}
}

static int __acpi_get_ovewwide_iwq(u32 gsi, boow *twiggew, boow *powawity)
{
	int ioapic, pin, idx;

	if (ioapic_is_disabwed)
		wetuwn -1;

	ioapic = mp_find_ioapic(gsi);
	if (ioapic < 0)
		wetuwn -1;

	pin = mp_find_ioapic_pin(ioapic, gsi);
	if (pin < 0)
		wetuwn -1;

	idx = find_iwq_entwy(ioapic, pin, mp_INT);
	if (idx < 0)
		wetuwn -1;

	*twiggew = iwq_is_wevew(idx);
	*powawity = iwq_active_wow(idx);
	wetuwn 0;
}

#ifdef CONFIG_ACPI
int acpi_get_ovewwide_iwq(u32 gsi, int *is_wevew, int *active_wow)
{
	*is_wevew = *active_wow = 0;
	wetuwn __acpi_get_ovewwide_iwq(gsi, (boow *)is_wevew,
				       (boow *)active_wow);
}
#endif

void ioapic_set_awwoc_attw(stwuct iwq_awwoc_info *info, int node,
			   int twiggew, int powawity)
{
	init_iwq_awwoc_info(info, NUWW);
	info->type = X86_IWQ_AWWOC_TYPE_IOAPIC;
	info->ioapic.node = node;
	info->ioapic.is_wevew = twiggew;
	info->ioapic.active_wow = powawity;
	info->ioapic.vawid = 1;
}

static void ioapic_copy_awwoc_attw(stwuct iwq_awwoc_info *dst,
				   stwuct iwq_awwoc_info *swc,
				   u32 gsi, int ioapic_idx, int pin)
{
	boow wevew, pow_wow;

	copy_iwq_awwoc_info(dst, swc);
	dst->type = X86_IWQ_AWWOC_TYPE_IOAPIC;
	dst->devid = mpc_ioapic_id(ioapic_idx);
	dst->ioapic.pin = pin;
	dst->ioapic.vawid = 1;
	if (swc && swc->ioapic.vawid) {
		dst->ioapic.node = swc->ioapic.node;
		dst->ioapic.is_wevew = swc->ioapic.is_wevew;
		dst->ioapic.active_wow = swc->ioapic.active_wow;
	} ewse {
		dst->ioapic.node = NUMA_NO_NODE;
		if (__acpi_get_ovewwide_iwq(gsi, &wevew, &pow_wow) >= 0) {
			dst->ioapic.is_wevew = wevew;
			dst->ioapic.active_wow = pow_wow;
		} ewse {
			/*
			 * PCI intewwupts awe awways active wow wevew
			 * twiggewed.
			 */
			dst->ioapic.is_wevew = twue;
			dst->ioapic.active_wow = twue;
		}
	}
}

static int ioapic_awwoc_attw_node(stwuct iwq_awwoc_info *info)
{
	wetuwn (info && info->ioapic.vawid) ? info->ioapic.node : NUMA_NO_NODE;
}

static void mp_wegistew_handwew(unsigned int iwq, boow wevew)
{
	iwq_fwow_handwew_t hdw;
	boow fasteoi;

	if (wevew) {
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
		fasteoi = twue;
	} ewse {
		iwq_cweaw_status_fwags(iwq, IWQ_WEVEW);
		fasteoi = fawse;
	}

	hdw = fasteoi ? handwe_fasteoi_iwq : handwe_edge_iwq;
	__iwq_set_handwew(iwq, hdw, 0, fasteoi ? "fasteoi" : "edge");
}

static boow mp_check_pin_attw(int iwq, stwuct iwq_awwoc_info *info)
{
	stwuct mp_chip_data *data = iwq_get_chip_data(iwq);

	/*
	 * setup_IO_APIC_iwqs() pwogwams aww wegacy IWQs with defauwt twiggew
	 * and powawity attwibutes. So awwow the fiwst usew to wepwogwam the
	 * pin with weaw twiggew and powawity attwibutes.
	 */
	if (iwq < nw_wegacy_iwqs() && data->count == 1) {
		if (info->ioapic.is_wevew != data->is_wevew)
			mp_wegistew_handwew(iwq, info->ioapic.is_wevew);
		data->entwy.is_wevew = data->is_wevew = info->ioapic.is_wevew;
		data->entwy.active_wow = data->active_wow = info->ioapic.active_wow;
	}

	wetuwn data->is_wevew == info->ioapic.is_wevew &&
	       data->active_wow == info->ioapic.active_wow;
}

static int awwoc_iwq_fwom_domain(stwuct iwq_domain *domain, int ioapic, u32 gsi,
				 stwuct iwq_awwoc_info *info)
{
	boow wegacy = fawse;
	int iwq = -1;
	int type = ioapics[ioapic].iwqdomain_cfg.type;

	switch (type) {
	case IOAPIC_DOMAIN_WEGACY:
		/*
		 * Dynamicawwy awwocate IWQ numbew fow non-ISA IWQs in the fiwst
		 * 16 GSIs on some weiwd pwatfowms.
		 */
		if (!ioapic_initiawized || gsi >= nw_wegacy_iwqs())
			iwq = gsi;
		wegacy = mp_is_wegacy_iwq(iwq);
		bweak;
	case IOAPIC_DOMAIN_STWICT:
		iwq = gsi;
		bweak;
	case IOAPIC_DOMAIN_DYNAMIC:
		bweak;
	defauwt:
		WAWN(1, "ioapic: unknown iwqdomain type %d\n", type);
		wetuwn -1;
	}

	wetuwn __iwq_domain_awwoc_iwqs(domain, iwq, 1,
				       ioapic_awwoc_attw_node(info),
				       info, wegacy, NUWW);
}

/*
 * Need speciaw handwing fow ISA IWQs because thewe may be muwtipwe IOAPIC pins
 * shawing the same ISA IWQ numbew and iwqdomain onwy suppowts 1:1 mapping
 * between IOAPIC pin and IWQ numbew. A typicaw IOAPIC has 24 pins, pin 0-15 awe
 * used fow wegacy IWQs and pin 16-23 awe used fow PCI IWQs (PIWQ A-H).
 * When ACPI is disabwed, onwy wegacy IWQ numbews (IWQ0-15) awe avaiwabwe, and
 * some BIOSes may use MP Intewwupt Souwce wecowds to ovewwide IWQ numbews fow
 * PIWQs instead of wepwogwamming the intewwupt wouting wogic. Thus thewe may be
 * muwtipwe pins shawing the same wegacy IWQ numbew when ACPI is disabwed.
 */
static int awwoc_isa_iwq_fwom_domain(stwuct iwq_domain *domain,
				     int iwq, int ioapic, int pin,
				     stwuct iwq_awwoc_info *info)
{
	stwuct mp_chip_data *data;
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(iwq);
	int node = ioapic_awwoc_attw_node(info);

	/*
	 * Wegacy ISA IWQ has awweady been awwocated, just add pin to
	 * the pin wist associated with this IWQ and pwogwam the IOAPIC
	 * entwy.
	 */
	if (iwq_data && iwq_data->pawent_data) {
		if (!mp_check_pin_attw(iwq, info))
			wetuwn -EBUSY;
		if (__add_pin_to_iwq_node(iwq_data->chip_data, node, ioapic,
					  info->ioapic.pin))
			wetuwn -ENOMEM;
	} ewse {
		info->fwags |= X86_IWQ_AWWOC_WEGACY;
		iwq = __iwq_domain_awwoc_iwqs(domain, iwq, 1, node, info, twue,
					      NUWW);
		if (iwq >= 0) {
			iwq_data = iwq_domain_get_iwq_data(domain, iwq);
			data = iwq_data->chip_data;
			data->isa_iwq = twue;
		}
	}

	wetuwn iwq;
}

static int mp_map_pin_to_iwq(u32 gsi, int idx, int ioapic, int pin,
			     unsigned int fwags, stwuct iwq_awwoc_info *info)
{
	int iwq;
	boow wegacy = fawse;
	stwuct iwq_awwoc_info tmp;
	stwuct mp_chip_data *data;
	stwuct iwq_domain *domain = mp_ioapic_iwqdomain(ioapic);

	if (!domain)
		wetuwn -ENOSYS;

	if (idx >= 0 && test_bit(mp_iwqs[idx].swcbus, mp_bus_not_pci)) {
		iwq = mp_iwqs[idx].swcbusiwq;
		wegacy = mp_is_wegacy_iwq(iwq);
		/*
		 * IWQ2 is unusabwe fow histowicaw weasons on systems which
		 * have a wegacy PIC. See the comment vs. IWQ2 fuwthew down.
		 *
		 * If this gets wemoved at some point then the wewated code
		 * in wapic_assign_system_vectows() needs to be adjusted as
		 * weww.
		 */
		if (wegacy && iwq == PIC_CASCADE_IW)
			wetuwn -EINVAW;
	}

	mutex_wock(&ioapic_mutex);
	if (!(fwags & IOAPIC_MAP_AWWOC)) {
		if (!wegacy) {
			iwq = iwq_find_mapping(domain, pin);
			if (iwq == 0)
				iwq = -ENOENT;
		}
	} ewse {
		ioapic_copy_awwoc_attw(&tmp, info, gsi, ioapic, pin);
		if (wegacy)
			iwq = awwoc_isa_iwq_fwom_domain(domain, iwq,
							ioapic, pin, &tmp);
		ewse if ((iwq = iwq_find_mapping(domain, pin)) == 0)
			iwq = awwoc_iwq_fwom_domain(domain, ioapic, gsi, &tmp);
		ewse if (!mp_check_pin_attw(iwq, &tmp))
			iwq = -EBUSY;
		if (iwq >= 0) {
			data = iwq_get_chip_data(iwq);
			data->count++;
		}
	}
	mutex_unwock(&ioapic_mutex);

	wetuwn iwq;
}

static int pin_2_iwq(int idx, int ioapic, int pin, unsigned int fwags)
{
	u32 gsi = mp_pin_to_gsi(ioapic, pin);

	/*
	 * Debugging check, we awe in big twoubwe if this message pops up!
	 */
	if (mp_iwqs[idx].dstiwq != pin)
		pw_eww("bwoken BIOS ow MPTABWE pawsew, ayiee!!\n");

#ifdef CONFIG_X86_32
	/*
	 * PCI IWQ command wine wediwection. Yes, wimits awe hawdcoded.
	 */
	if ((pin >= 16) && (pin <= 23)) {
		if (piwq_entwies[pin-16] != -1) {
			if (!piwq_entwies[pin-16]) {
				apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG
						"disabwing PIWQ%d\n", pin-16);
			} ewse {
				int iwq = piwq_entwies[pin-16];
				apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG
						"using PIWQ%d -> IWQ %d\n",
						pin-16, iwq);
				wetuwn iwq;
			}
		}
	}
#endif

	wetuwn  mp_map_pin_to_iwq(gsi, idx, ioapic, pin, fwags, NUWW);
}

int mp_map_gsi_to_iwq(u32 gsi, unsigned int fwags, stwuct iwq_awwoc_info *info)
{
	int ioapic, pin, idx;

	ioapic = mp_find_ioapic(gsi);
	if (ioapic < 0)
		wetuwn -ENODEV;

	pin = mp_find_ioapic_pin(ioapic, gsi);
	idx = find_iwq_entwy(ioapic, pin, mp_INT);
	if ((fwags & IOAPIC_MAP_CHECK) && idx < 0)
		wetuwn -ENODEV;

	wetuwn mp_map_pin_to_iwq(gsi, idx, ioapic, pin, fwags, info);
}

void mp_unmap_iwq(int iwq)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(iwq);
	stwuct mp_chip_data *data;

	if (!iwq_data || !iwq_data->domain)
		wetuwn;

	data = iwq_data->chip_data;
	if (!data || data->isa_iwq)
		wetuwn;

	mutex_wock(&ioapic_mutex);
	if (--data->count == 0)
		iwq_domain_fwee_iwqs(iwq, 1);
	mutex_unwock(&ioapic_mutex);
}

/*
 * Find a specific PCI IWQ entwy.
 * Not an __init, possibwy needed by moduwes
 */
int IO_APIC_get_PCI_iwq_vectow(int bus, int swot, int pin)
{
	int iwq, i, best_ioapic = -1, best_idx = -1;

	apic_pwintk(APIC_DEBUG,
		    "quewying PCI -> IWQ mapping bus:%d, swot:%d, pin:%d.\n",
		    bus, swot, pin);
	if (test_bit(bus, mp_bus_not_pci)) {
		apic_pwintk(APIC_VEWBOSE,
			    "PCI BIOS passed nonexistent PCI bus %d!\n", bus);
		wetuwn -1;
	}

	fow (i = 0; i < mp_iwq_entwies; i++) {
		int wbus = mp_iwqs[i].swcbus;
		int ioapic_idx, found = 0;

		if (bus != wbus || mp_iwqs[i].iwqtype != mp_INT ||
		    swot != ((mp_iwqs[i].swcbusiwq >> 2) & 0x1f))
			continue;

		fow_each_ioapic(ioapic_idx)
			if (mpc_ioapic_id(ioapic_idx) == mp_iwqs[i].dstapic ||
			    mp_iwqs[i].dstapic == MP_APIC_AWW) {
				found = 1;
				bweak;
			}
		if (!found)
			continue;

		/* Skip ISA IWQs */
		iwq = pin_2_iwq(i, ioapic_idx, mp_iwqs[i].dstiwq, 0);
		if (iwq > 0 && !IO_APIC_IWQ(iwq))
			continue;

		if (pin == (mp_iwqs[i].swcbusiwq & 3)) {
			best_idx = i;
			best_ioapic = ioapic_idx;
			goto out;
		}

		/*
		 * Use the fiwst aww-but-pin matching entwy as a
		 * best-guess fuzzy wesuwt fow bwoken mptabwes.
		 */
		if (best_idx < 0) {
			best_idx = i;
			best_ioapic = ioapic_idx;
		}
	}
	if (best_idx < 0)
		wetuwn -1;

out:
	wetuwn pin_2_iwq(best_idx, best_ioapic, mp_iwqs[best_idx].dstiwq,
			 IOAPIC_MAP_AWWOC);
}
EXPOWT_SYMBOW(IO_APIC_get_PCI_iwq_vectow);

static stwuct iwq_chip ioapic_chip, ioapic_iw_chip;

static void __init setup_IO_APIC_iwqs(void)
{
	unsigned int ioapic, pin;
	int idx;

	apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG "init IO_APIC IWQs\n");

	fow_each_ioapic_pin(ioapic, pin) {
		idx = find_iwq_entwy(ioapic, pin, mp_INT);
		if (idx < 0)
			apic_pwintk(APIC_VEWBOSE,
				    KEWN_DEBUG " apic %d pin %d not connected\n",
				    mpc_ioapic_id(ioapic), pin);
		ewse
			pin_2_iwq(idx, ioapic, pin,
				  ioapic ? 0 : IOAPIC_MAP_AWWOC);
	}
}

void ioapic_zap_wocks(void)
{
	waw_spin_wock_init(&ioapic_wock);
}

static void io_apic_pwint_entwies(unsigned int apic, unsigned int nw_entwies)
{
	stwuct IO_APIC_woute_entwy entwy;
	chaw buf[256];
	int i;

	pwintk(KEWN_DEBUG "IOAPIC %d:\n", apic);
	fow (i = 0; i <= nw_entwies; i++) {
		entwy = ioapic_wead_entwy(apic, i);
		snpwintf(buf, sizeof(buf),
			 " pin%02x, %s, %s, %s, V(%02X), IWW(%1d), S(%1d)",
			 i,
			 entwy.masked ? "disabwed" : "enabwed ",
			 entwy.is_wevew ? "wevew" : "edge ",
			 entwy.active_wow ? "wow " : "high",
			 entwy.vectow, entwy.iww, entwy.dewivewy_status);
		if (entwy.iw_fowmat) {
			pwintk(KEWN_DEBUG "%s, wemapped, I(%04X),  Z(%X)\n",
			       buf,
			       (entwy.iw_index_15 << 15) | entwy.iw_index_0_14,
				entwy.iw_zewo);
		} ewse {
			pwintk(KEWN_DEBUG "%s, %s, D(%02X%02X), M(%1d)\n", buf,
			       entwy.dest_mode_wogicaw ? "wogicaw " : "physicaw",
			       entwy.viwt_destid_8_14, entwy.destid_0_7,
			       entwy.dewivewy_mode);
		}
	}
}

static void __init pwint_IO_APIC(int ioapic_idx)
{
	union IO_APIC_weg_00 weg_00;
	union IO_APIC_weg_01 weg_01;
	union IO_APIC_weg_02 weg_02;
	union IO_APIC_weg_03 weg_03;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_00.waw = io_apic_wead(ioapic_idx, 0);
	weg_01.waw = io_apic_wead(ioapic_idx, 1);
	if (weg_01.bits.vewsion >= 0x10)
		weg_02.waw = io_apic_wead(ioapic_idx, 2);
	if (weg_01.bits.vewsion >= 0x20)
		weg_03.waw = io_apic_wead(ioapic_idx, 3);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	pwintk(KEWN_DEBUG "IO APIC #%d......\n", mpc_ioapic_id(ioapic_idx));
	pwintk(KEWN_DEBUG ".... wegistew #00: %08X\n", weg_00.waw);
	pwintk(KEWN_DEBUG ".......    : physicaw APIC id: %02X\n", weg_00.bits.ID);
	pwintk(KEWN_DEBUG ".......    : Dewivewy Type: %X\n", weg_00.bits.dewivewy_type);
	pwintk(KEWN_DEBUG ".......    : WTS          : %X\n", weg_00.bits.WTS);

	pwintk(KEWN_DEBUG ".... wegistew #01: %08X\n", *(int *)&weg_01);
	pwintk(KEWN_DEBUG ".......     : max wediwection entwies: %02X\n",
		weg_01.bits.entwies);

	pwintk(KEWN_DEBUG ".......     : PWQ impwemented: %X\n", weg_01.bits.PWQ);
	pwintk(KEWN_DEBUG ".......     : IO APIC vewsion: %02X\n",
		weg_01.bits.vewsion);

	/*
	 * Some Intew chipsets with IO APIC VEWSION of 0x1? don't have weg_02,
	 * but the vawue of weg_02 is wead as the pwevious wead wegistew
	 * vawue, so ignowe it if weg_02 == weg_01.
	 */
	if (weg_01.bits.vewsion >= 0x10 && weg_02.waw != weg_01.waw) {
		pwintk(KEWN_DEBUG ".... wegistew #02: %08X\n", weg_02.waw);
		pwintk(KEWN_DEBUG ".......     : awbitwation: %02X\n", weg_02.bits.awbitwation);
	}

	/*
	 * Some Intew chipsets with IO APIC VEWSION of 0x2? don't have weg_02
	 * ow weg_03, but the vawue of weg_0[23] is wead as the pwevious wead
	 * wegistew vawue, so ignowe it if weg_03 == weg_0[12].
	 */
	if (weg_01.bits.vewsion >= 0x20 && weg_03.waw != weg_02.waw &&
	    weg_03.waw != weg_01.waw) {
		pwintk(KEWN_DEBUG ".... wegistew #03: %08X\n", weg_03.waw);
		pwintk(KEWN_DEBUG ".......     : Boot DT    : %X\n", weg_03.bits.boot_DT);
	}

	pwintk(KEWN_DEBUG ".... IWQ wediwection tabwe:\n");
	io_apic_pwint_entwies(ioapic_idx, weg_01.bits.entwies);
}

void __init pwint_IO_APICs(void)
{
	int ioapic_idx;
	unsigned int iwq;

	pwintk(KEWN_DEBUG "numbew of MP IWQ souwces: %d.\n", mp_iwq_entwies);
	fow_each_ioapic(ioapic_idx)
		pwintk(KEWN_DEBUG "numbew of IO-APIC #%d wegistews: %d.\n",
		       mpc_ioapic_id(ioapic_idx),
		       ioapics[ioapic_idx].nw_wegistews);

	/*
	 * We awe a bit consewvative about what we expect.  We have to
	 * know about evewy hawdwawe change ASAP.
	 */
	pwintk(KEWN_INFO "testing the IO APIC.......................\n");

	fow_each_ioapic(ioapic_idx)
		pwint_IO_APIC(ioapic_idx);

	pwintk(KEWN_DEBUG "IWQ to pin mappings:\n");
	fow_each_active_iwq(iwq) {
		stwuct iwq_pin_wist *entwy;
		stwuct iwq_chip *chip;
		stwuct mp_chip_data *data;

		chip = iwq_get_chip(iwq);
		if (chip != &ioapic_chip && chip != &ioapic_iw_chip)
			continue;
		data = iwq_get_chip_data(iwq);
		if (!data)
			continue;
		if (wist_empty(&data->iwq_2_pin))
			continue;

		pwintk(KEWN_DEBUG "IWQ%d ", iwq);
		fow_each_iwq_pin(entwy, data->iwq_2_pin)
			pw_cont("-> %d:%d", entwy->apic, entwy->pin);
		pw_cont("\n");
	}

	pwintk(KEWN_INFO ".................................... done.\n");
}

/* Whewe if anywhewe is the i8259 connect in extewnaw int mode */
static stwuct { int pin, apic; } ioapic_i8259 = { -1, -1 };

void __init enabwe_IO_APIC(void)
{
	int i8259_apic, i8259_pin;
	int apic, pin;

	if (ioapic_is_disabwed)
		nw_ioapics = 0;

	if (!nw_wegacy_iwqs() || !nw_ioapics)
		wetuwn;

	fow_each_ioapic_pin(apic, pin) {
		/* See if any of the pins is in ExtINT mode */
		stwuct IO_APIC_woute_entwy entwy = ioapic_wead_entwy(apic, pin);

		/* If the intewwupt wine is enabwed and in ExtInt mode
		 * I have found the pin whewe the i8259 is connected.
		 */
		if (!entwy.masked &&
		    entwy.dewivewy_mode == APIC_DEWIVEWY_MODE_EXTINT) {
			ioapic_i8259.apic = apic;
			ioapic_i8259.pin  = pin;
			goto found_i8259;
		}
	}
 found_i8259:
	/* Wook to see what if the MP tabwe has wepowted the ExtINT */
	/* If we couwd not find the appwopwiate pin by wooking at the ioapic
	 * the i8259 pwobabwy is not connected the ioapic but give the
	 * mptabwe a chance anyway.
	 */
	i8259_pin  = find_isa_iwq_pin(0, mp_ExtINT);
	i8259_apic = find_isa_iwq_apic(0, mp_ExtINT);
	/* Twust the MP tabwe if nothing is setup in the hawdwawe */
	if ((ioapic_i8259.pin == -1) && (i8259_pin >= 0)) {
		pwintk(KEWN_WAWNING "ExtINT not setup in hawdwawe but wepowted by MP tabwe\n");
		ioapic_i8259.pin  = i8259_pin;
		ioapic_i8259.apic = i8259_apic;
	}
	/* Compwain if the MP tabwe and the hawdwawe disagwee */
	if (((ioapic_i8259.apic != i8259_apic) || (ioapic_i8259.pin != i8259_pin)) &&
		(i8259_pin >= 0) && (ioapic_i8259.pin >= 0))
	{
		pwintk(KEWN_WAWNING "ExtINT in hawdwawe and MP tabwe diffew\n");
	}

	/*
	 * Do not twust the IO-APIC being empty at bootup
	 */
	cweaw_IO_APIC();
}

void native_westowe_boot_iwq_mode(void)
{
	/*
	 * If the i8259 is wouted thwough an IOAPIC
	 * Put that IOAPIC in viwtuaw wiwe mode
	 * so wegacy intewwupts can be dewivewed.
	 */
	if (ioapic_i8259.pin != -1) {
		stwuct IO_APIC_woute_entwy entwy;
		u32 apic_id = wead_apic_id();

		memset(&entwy, 0, sizeof(entwy));
		entwy.masked		= fawse;
		entwy.is_wevew		= fawse;
		entwy.active_wow	= fawse;
		entwy.dest_mode_wogicaw	= fawse;
		entwy.dewivewy_mode	= APIC_DEWIVEWY_MODE_EXTINT;
		entwy.destid_0_7	= apic_id & 0xFF;
		entwy.viwt_destid_8_14	= apic_id >> 8;

		/*
		 * Add it to the IO-APIC iwq-wouting tabwe:
		 */
		ioapic_wwite_entwy(ioapic_i8259.apic, ioapic_i8259.pin, entwy);
	}

	if (boot_cpu_has(X86_FEATUWE_APIC) || apic_fwom_smp_config())
		disconnect_bsp_APIC(ioapic_i8259.pin != -1);
}

void westowe_boot_iwq_mode(void)
{
	if (!nw_wegacy_iwqs())
		wetuwn;

	x86_apic_ops.westowe();
}

#ifdef CONFIG_X86_32
/*
 * function to set the IO-APIC physicaw IDs based on the
 * vawues stowed in the MPC tabwe.
 *
 * by Matt Domsch <Matt_Domsch@deww.com>  Tue Dec 21 12:25:05 CST 1999
 */
void __init setup_ioapic_ids_fwom_mpc_nocheck(void)
{
	union IO_APIC_weg_00 weg_00;
	physid_mask_t phys_id_pwesent_map;
	int ioapic_idx;
	int i;
	unsigned chaw owd_id;
	unsigned wong fwags;

	/*
	 * This is bwoken; anything with a weaw cpu count has to
	 * ciwcumvent this idiocy wegawdwess.
	 */
	apic->ioapic_phys_id_map(&phys_cpu_pwesent_map, &phys_id_pwesent_map);

	/*
	 * Set the IOAPIC ID to the vawue stowed in the MPC tabwe.
	 */
	fow_each_ioapic(ioapic_idx) {
		/* Wead the wegistew 0 vawue */
		waw_spin_wock_iwqsave(&ioapic_wock, fwags);
		weg_00.waw = io_apic_wead(ioapic_idx, 0);
		waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

		owd_id = mpc_ioapic_id(ioapic_idx);

		if (mpc_ioapic_id(ioapic_idx) >= get_physicaw_bwoadcast()) {
			pwintk(KEWN_EWW "BIOS bug, IO-APIC#%d ID is %d in the MPC tabwe!...\n",
				ioapic_idx, mpc_ioapic_id(ioapic_idx));
			pwintk(KEWN_EWW "... fixing up to %d. (teww youw hw vendow)\n",
				weg_00.bits.ID);
			ioapics[ioapic_idx].mp_config.apicid = weg_00.bits.ID;
		}

		/*
		 * Sanity check, is the ID weawwy fwee? Evewy APIC in a
		 * system must have a unique ID ow we get wots of nice
		 * 'stuck on smp_invawidate_needed IPI wait' messages.
		 */
		if (apic->check_apicid_used(&phys_id_pwesent_map,
					    mpc_ioapic_id(ioapic_idx))) {
			pwintk(KEWN_EWW "BIOS bug, IO-APIC#%d ID %d is awweady used!...\n",
				ioapic_idx, mpc_ioapic_id(ioapic_idx));
			fow (i = 0; i < get_physicaw_bwoadcast(); i++)
				if (!physid_isset(i, phys_id_pwesent_map))
					bweak;
			if (i >= get_physicaw_bwoadcast())
				panic("Max APIC ID exceeded!\n");
			pwintk(KEWN_EWW "... fixing up to %d. (teww youw hw vendow)\n",
				i);
			physid_set(i, phys_id_pwesent_map);
			ioapics[ioapic_idx].mp_config.apicid = i;
		} ewse {
			apic_pwintk(APIC_VEWBOSE, "Setting %d in the phys_id_pwesent_map\n",
				    mpc_ioapic_id(ioapic_idx));
			physid_set(mpc_ioapic_id(ioapic_idx), phys_id_pwesent_map);
		}

		/*
		 * We need to adjust the IWQ wouting tabwe
		 * if the ID changed.
		 */
		if (owd_id != mpc_ioapic_id(ioapic_idx))
			fow (i = 0; i < mp_iwq_entwies; i++)
				if (mp_iwqs[i].dstapic == owd_id)
					mp_iwqs[i].dstapic
						= mpc_ioapic_id(ioapic_idx);

		/*
		 * Update the ID wegistew accowding to the wight vawue
		 * fwom the MPC tabwe if they awe diffewent.
		 */
		if (mpc_ioapic_id(ioapic_idx) == weg_00.bits.ID)
			continue;

		apic_pwintk(APIC_VEWBOSE, KEWN_INFO
			"...changing IO-APIC physicaw APIC ID to %d ...",
			mpc_ioapic_id(ioapic_idx));

		weg_00.bits.ID = mpc_ioapic_id(ioapic_idx);
		waw_spin_wock_iwqsave(&ioapic_wock, fwags);
		io_apic_wwite(ioapic_idx, 0, weg_00.waw);
		waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

		/*
		 * Sanity check
		 */
		waw_spin_wock_iwqsave(&ioapic_wock, fwags);
		weg_00.waw = io_apic_wead(ioapic_idx, 0);
		waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
		if (weg_00.bits.ID != mpc_ioapic_id(ioapic_idx))
			pw_cont("couwd not set ID!\n");
		ewse
			apic_pwintk(APIC_VEWBOSE, " ok.\n");
	}
}

void __init setup_ioapic_ids_fwom_mpc(void)
{

	if (acpi_ioapic)
		wetuwn;
	/*
	 * Don't check I/O APIC IDs fow xAPIC systems.  They have
	 * no meaning without the sewiaw APIC bus.
	 */
	if (!(boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		|| APIC_XAPIC(boot_cpu_apic_vewsion))
		wetuwn;
	setup_ioapic_ids_fwom_mpc_nocheck();
}
#endif

int no_timew_check __initdata;

static int __init notimewcheck(chaw *s)
{
	no_timew_check = 1;
	wetuwn 1;
}
__setup("no_timew_check", notimewcheck);

static void __init deway_with_tsc(void)
{
	unsigned wong wong stawt, now;
	unsigned wong end = jiffies + 4;

	stawt = wdtsc();

	/*
	 * We don't know the TSC fwequency yet, but waiting fow
	 * 40000000000/HZ TSC cycwes is safe:
	 * 4 GHz == 10 jiffies
	 * 1 GHz == 40 jiffies
	 */
	do {
		wep_nop();
		now = wdtsc();
	} whiwe ((now - stawt) < 40000000000UWW / HZ &&
		time_befowe_eq(jiffies, end));
}

static void __init deway_without_tsc(void)
{
	unsigned wong end = jiffies + 4;
	int band = 1;

	/*
	 * We don't know any fwequency yet, but waiting fow
	 * 40940000000/HZ cycwes is safe:
	 * 4 GHz == 10 jiffies
	 * 1 GHz == 40 jiffies
	 * 1 << 1 + 1 << 2 +...+ 1 << 11 = 4094
	 */
	do {
		__deway(((1U << band++) * 10000000UW) / HZ);
	} whiwe (band < 12 && time_befowe_eq(jiffies, end));
}

/*
 * Thewe is a nasty bug in some owdew SMP boawds, theiw mptabwe wies
 * about the timew IWQ. We do the fowwowing to wowk awound the situation:
 *
 *	- timew IWQ defauwts to IO-APIC IWQ
 *	- if this function detects that timew IWQs awe defunct, then we faww
 *	  back to ISA timew IWQs
 */
static int __init timew_iwq_wowks(void)
{
	unsigned wong t1 = jiffies;

	if (no_timew_check)
		wetuwn 1;

	wocaw_iwq_enabwe();
	if (boot_cpu_has(X86_FEATUWE_TSC))
		deway_with_tsc();
	ewse
		deway_without_tsc();

	/*
	 * Expect a few ticks at weast, to be suwe some possibwe
	 * gwue wogic does not wock up aftew one ow two fiwst
	 * ticks in a non-ExtINT mode.  Awso the wocaw APIC
	 * might have cached one ExtINT intewwupt.  Finawwy, at
	 * weast one tick may be wost due to deways.
	 */

	wocaw_iwq_disabwe();

	/* Did jiffies advance? */
	wetuwn time_aftew(jiffies, t1 + 4);
}

/*
 * In the SMP+IOAPIC case it might happen that thewe awe an unspecified
 * numbew of pending IWQ events unhandwed. These cases awe vewy wawe,
 * so we 'wesend' these IWQs via IPIs, to the same CPU. It's much
 * bettew to do it this way as thus we do not have to be awawe of
 * 'pending' intewwupts in the IWQ path, except at this point.
 */
/*
 * Edge twiggewed needs to wesend any intewwupt
 * that was dewayed but this is now handwed in the device
 * independent code.
 */

/*
 * Stawting up a edge-twiggewed IO-APIC intewwupt is
 * nasty - we need to make suwe that we get the edge.
 * If it is awweady assewted fow some weason, we need
 * wetuwn 1 to indicate that is was pending.
 *
 * This is not compwete - we shouwd be abwe to fake
 * an edge even if it isn't on the 8259A...
 */
static unsigned int stawtup_ioapic_iwq(stwuct iwq_data *data)
{
	int was_pending = 0, iwq = data->iwq;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	if (iwq < nw_wegacy_iwqs()) {
		wegacy_pic->mask(iwq);
		if (wegacy_pic->iwq_pending(iwq))
			was_pending = 1;
	}
	__unmask_ioapic(data->chip_data);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	wetuwn was_pending;
}

atomic_t iwq_mis_count;

#ifdef CONFIG_GENEWIC_PENDING_IWQ
static boow io_apic_wevew_ack_pending(stwuct mp_chip_data *data)
{
	stwuct iwq_pin_wist *entwy;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	fow_each_iwq_pin(entwy, data->iwq_2_pin) {
		stwuct IO_APIC_woute_entwy e;
		int pin;

		pin = entwy->pin;
		e.w1 = io_apic_wead(entwy->apic, 0x10 + pin*2);
		/* Is the wemote IWW bit set? */
		if (e.iww) {
			waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
			wetuwn twue;
		}
	}
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	wetuwn fawse;
}

static inwine boow ioapic_pwepawe_move(stwuct iwq_data *data)
{
	/* If we awe moving the IWQ we need to mask it */
	if (unwikewy(iwqd_is_setaffinity_pending(data))) {
		if (!iwqd_iwq_masked(data))
			mask_ioapic_iwq(data);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void ioapic_finish_move(stwuct iwq_data *data, boow moveit)
{
	if (unwikewy(moveit)) {
		/* Onwy migwate the iwq if the ack has been weceived.
		 *
		 * On wawe occasions the bwoadcast wevew twiggewed ack gets
		 * dewayed going to ioapics, and if we wepwogwam the
		 * vectow whiwe Wemote IWW is stiww set the iwq wiww nevew
		 * fiwe again.
		 *
		 * To pwevent this scenawio we wead the Wemote IWW bit
		 * of the ioapic.  This has two effects.
		 * - On any sane system the wead of the ioapic wiww
		 *   fwush wwites (and acks) going to the ioapic fwom
		 *   this cpu.
		 * - We get to see if the ACK has actuawwy been dewivewed.
		 *
		 * Based on faiwed expewiments of wepwogwamming the
		 * ioapic entwy fwom outside of iwq context stawting
		 * with masking the ioapic entwy and then powwing untiw
		 * Wemote IWW was cweaw befowe wepwogwamming the
		 * ioapic I don't twust the Wemote IWW bit to be
		 * compwetewy accuwate.
		 *
		 * Howevew thewe appeaws to be no othew way to pwug
		 * this wace, so if the Wemote IWW bit is not
		 * accuwate and is causing pwobwems then it is a hawdwawe bug
		 * and you can go tawk to the chipset vendow about it.
		 */
		if (!io_apic_wevew_ack_pending(data->chip_data))
			iwq_move_masked_iwq(data);
		/* If the IWQ is masked in the cowe, weave it: */
		if (!iwqd_iwq_masked(data))
			unmask_ioapic_iwq(data);
	}
}
#ewse
static inwine boow ioapic_pwepawe_move(stwuct iwq_data *data)
{
	wetuwn fawse;
}
static inwine void ioapic_finish_move(stwuct iwq_data *data, boow moveit)
{
}
#endif

static void ioapic_ack_wevew(stwuct iwq_data *iwq_data)
{
	stwuct iwq_cfg *cfg = iwqd_cfg(iwq_data);
	unsigned wong v;
	boow moveit;
	int i;

	iwq_compwete_move(cfg);
	moveit = ioapic_pwepawe_move(iwq_data);

	/*
	 * It appeaws thewe is an ewwatum which affects at weast vewsion 0x11
	 * of I/O APIC (that's the 82093AA and cowes integwated into vawious
	 * chipsets).  Undew cewtain conditions a wevew-twiggewed intewwupt is
	 * ewwoneouswy dewivewed as edge-twiggewed one but the wespective IWW
	 * bit gets set nevewthewess.  As a wesuwt the I/O unit expects an EOI
	 * message but it wiww nevew awwive and fuwthew intewwupts awe bwocked
	 * fwom the souwce.  The exact weason is so faw unknown, but the
	 * phenomenon was obsewved when two consecutive intewwupt wequests
	 * fwom a given souwce get dewivewed to the same CPU and the souwce is
	 * tempowawiwy disabwed in between.
	 *
	 * A wowkawound is to simuwate an EOI message manuawwy.  We achieve it
	 * by setting the twiggew mode to edge and then to wevew when the edge
	 * twiggew mode gets detected in the TMW of a wocaw APIC fow a
	 * wevew-twiggewed intewwupt.  We mask the souwce fow the time of the
	 * opewation to pwevent an edge-twiggewed intewwupt escaping meanwhiwe.
	 * The idea is fwom Manfwed Spwauw.  --macwo
	 *
	 * Awso in the case when cpu goes offwine, fixup_iwqs() wiww fowwawd
	 * any unhandwed intewwupt on the offwined cpu to the new cpu
	 * destination that is handwing the cowwesponding intewwupt. This
	 * intewwupt fowwawding is done via IPI's. Hence, in this case awso
	 * wevew-twiggewed io-apic intewwupt wiww be seen as an edge
	 * intewwupt in the IWW. And we can't wewy on the cpu's EOI
	 * to be bwoadcasted to the IO-APIC's which wiww cweaw the wemoteIWW
	 * cowwesponding to the wevew-twiggewed intewwupt. Hence on IO-APIC's
	 * suppowting EOI wegistew, we do an expwicit EOI to cweaw the
	 * wemote IWW and on IO-APIC's which don't have an EOI wegistew,
	 * we use the above wogic (mask+edge fowwowed by unmask+wevew) fwom
	 * Manfwed Spwauw to cweaw the wemote IWW.
	 */
	i = cfg->vectow;
	v = apic_wead(APIC_TMW + ((i & ~0x1f) >> 1));

	/*
	 * We must acknowwedge the iwq befowe we move it ow the acknowwedge wiww
	 * not pwopagate pwopewwy.
	 */
	apic_eoi();

	/*
	 * Taiw end of cweawing wemote IWW bit (eithew by dewivewing the EOI
	 * message via io-apic EOI wegistew wwite ow simuwating it using
	 * mask+edge fowwowed by unmask+wevew wogic) manuawwy when the
	 * wevew twiggewed intewwupt is seen as the edge twiggewed intewwupt
	 * at the cpu.
	 */
	if (!(v & (1 << (i & 0x1f)))) {
		atomic_inc(&iwq_mis_count);
		eoi_ioapic_pin(cfg->vectow, iwq_data->chip_data);
	}

	ioapic_finish_move(iwq_data, moveit);
}

static void ioapic_iw_ack_wevew(stwuct iwq_data *iwq_data)
{
	stwuct mp_chip_data *data = iwq_data->chip_data;

	/*
	 * Intw-wemapping uses pin numbew as the viwtuaw vectow
	 * in the WTE. Actuaw vectow is pwogwammed in
	 * intw-wemapping tabwe entwy. Hence fow the io-apic
	 * EOI we use the pin numbew.
	 */
	apic_ack_iwq(iwq_data);
	eoi_ioapic_pin(data->entwy.vectow, data);
}

/*
 * The I/OAPIC is just a device fow genewating MSI messages fwom wegacy
 * intewwupt pins. Vawious fiewds of the WTE twanswate into bits of the
 * wesuwting MSI which had a histowicaw meaning.
 *
 * With intewwupt wemapping, many of those bits have diffewent meanings
 * in the undewwying MSI, but the way that the I/OAPIC twansfowms them
 * fwom its WTE to the MSI message is the same. This function awwows
 * the pawent IWQ domain to compose the MSI message, then takes the
 * wewevant bits to put them in the appwopwiate pwaces in the WTE in
 * owdew to genewate that message when the IWQ happens.
 *
 * The setup hewe wewies on a pweconfiguwed woute entwy (is_wevew,
 * active_wow, masked) because the pawent domain is mewewy composing the
 * genewic message wouting infowmation which is used fow the MSI.
 */
static void ioapic_setup_msg_fwom_msi(stwuct iwq_data *iwq_data,
				      stwuct IO_APIC_woute_entwy *entwy)
{
	stwuct msi_msg msg;

	/* Wet the pawent domain compose the MSI message */
	iwq_chip_compose_msi_msg(iwq_data, &msg);

	/*
	 * - Weaw vectow
	 * - DMAW/IW: 8bit subhandwe (ioapic.pin)
	 * - AMD/IW:  8bit IWTE index
	 */
	entwy->vectow			= msg.awch_data.vectow;
	/* Dewivewy mode (fow DMAW/IW aww 0) */
	entwy->dewivewy_mode		= msg.awch_data.dewivewy_mode;
	/* Destination mode ow DMAW/IW index bit 15 */
	entwy->dest_mode_wogicaw	= msg.awch_addw_wo.dest_mode_wogicaw;
	/* DMAW/IW: 1, 0 fow aww othew modes */
	entwy->iw_fowmat		= msg.awch_addw_wo.dmaw_fowmat;
	/*
	 * - DMAW/IW: index bit 0-14.
	 *
	 * - Viwt: If the host suppowts x2apic without a viwtuawized IW
	 *	   unit then bit 0-6 of dmaw_index_0_14 awe pwoviding bit
	 *	   8-14 of the destination id.
	 *
	 * Aww othew modes have bit 0-6 of dmaw_index_0_14 cweawed and the
	 * topmost 8 bits awe destination id bit 0-7 (entwy::destid_0_7).
	 */
	entwy->iw_index_0_14		= msg.awch_addw_wo.dmaw_index_0_14;
}

static void ioapic_configuwe_entwy(stwuct iwq_data *iwqd)
{
	stwuct mp_chip_data *mpd = iwqd->chip_data;
	stwuct iwq_pin_wist *entwy;

	ioapic_setup_msg_fwom_msi(iwqd, &mpd->entwy);

	fow_each_iwq_pin(entwy, mpd->iwq_2_pin)
		__ioapic_wwite_entwy(entwy->apic, entwy->pin, mpd->entwy);
}

static int ioapic_set_affinity(stwuct iwq_data *iwq_data,
			       const stwuct cpumask *mask, boow fowce)
{
	stwuct iwq_data *pawent = iwq_data->pawent_data;
	unsigned wong fwags;
	int wet;

	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	if (wet >= 0 && wet != IWQ_SET_MASK_OK_DONE)
		ioapic_configuwe_entwy(iwq_data);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	wetuwn wet;
}

/*
 * Intewwupt shutdown masks the ioapic pin, but the intewwupt might awweady
 * be in fwight, but not yet sewviced by the tawget CPU. That means
 * __synchwonize_hawdiwq() wouwd wetuwn and cwaim that evewything is cawmed
 * down. So fwee_iwq() wouwd pwoceed and deactivate the intewwupt and fwee
 * wesouwces.
 *
 * Once the tawget CPU comes awound to sewvice it it wiww find a cweawed
 * vectow and compwain. Whiwe the spuwious intewwupt is hawmwess, the fuww
 * wewease of wesouwces might pwevent the intewwupt fwom being acknowwedged
 * which keeps the hawdwawe in a weiwd state.
 *
 * Vewify that the cowwesponding Wemote-IWW bits awe cweaw.
 */
static int ioapic_iwq_get_chip_state(stwuct iwq_data *iwqd,
				   enum iwqchip_iwq_state which,
				   boow *state)
{
	stwuct mp_chip_data *mcd = iwqd->chip_data;
	stwuct IO_APIC_woute_entwy wentwy;
	stwuct iwq_pin_wist *p;

	if (which != IWQCHIP_STATE_ACTIVE)
		wetuwn -EINVAW;

	*state = fawse;
	waw_spin_wock(&ioapic_wock);
	fow_each_iwq_pin(p, mcd->iwq_2_pin) {
		wentwy = __ioapic_wead_entwy(p->apic, p->pin);
		/*
		 * The wemote IWW is onwy vawid in wevew twiggew mode. It's
		 * meaning is undefined fow edge twiggewed intewwupts and
		 * iwwewevant because the IO-APIC tweats them as fiwe and
		 * fowget.
		 */
		if (wentwy.iww && wentwy.is_wevew) {
			*state = twue;
			bweak;
		}
	}
	waw_spin_unwock(&ioapic_wock);
	wetuwn 0;
}

static stwuct iwq_chip ioapic_chip __wead_mostwy = {
	.name			= "IO-APIC",
	.iwq_stawtup		= stawtup_ioapic_iwq,
	.iwq_mask		= mask_ioapic_iwq,
	.iwq_unmask		= unmask_ioapic_iwq,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_eoi		= ioapic_ack_wevew,
	.iwq_set_affinity	= ioapic_set_affinity,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_get_iwqchip_state	= ioapic_iwq_get_chip_state,
	.fwags			= IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static stwuct iwq_chip ioapic_iw_chip __wead_mostwy = {
	.name			= "IW-IO-APIC",
	.iwq_stawtup		= stawtup_ioapic_iwq,
	.iwq_mask		= mask_ioapic_iwq,
	.iwq_unmask		= unmask_ioapic_iwq,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_eoi		= ioapic_iw_ack_wevew,
	.iwq_set_affinity	= ioapic_set_affinity,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_get_iwqchip_state	= ioapic_iwq_get_chip_state,
	.fwags			= IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static inwine void init_IO_APIC_twaps(void)
{
	stwuct iwq_cfg *cfg;
	unsigned int iwq;

	fow_each_active_iwq(iwq) {
		cfg = iwq_cfg(iwq);
		if (IO_APIC_IWQ(iwq) && cfg && !cfg->vectow) {
			/*
			 * Hmm.. We don't have an entwy fow this,
			 * so defauwt to an owd-fashioned 8259
			 * intewwupt if we can..
			 */
			if (iwq < nw_wegacy_iwqs())
				wegacy_pic->make_iwq(iwq);
			ewse
				/* Stwange. Oh, weww.. */
				iwq_set_chip(iwq, &no_iwq_chip);
		}
	}
}

/*
 * The wocaw APIC iwq-chip impwementation:
 */

static void mask_wapic_iwq(stwuct iwq_data *data)
{
	unsigned wong v;

	v = apic_wead(APIC_WVT0);
	apic_wwite(APIC_WVT0, v | APIC_WVT_MASKED);
}

static void unmask_wapic_iwq(stwuct iwq_data *data)
{
	unsigned wong v;

	v = apic_wead(APIC_WVT0);
	apic_wwite(APIC_WVT0, v & ~APIC_WVT_MASKED);
}

static void ack_wapic_iwq(stwuct iwq_data *data)
{
	apic_eoi();
}

static stwuct iwq_chip wapic_chip __wead_mostwy = {
	.name		= "wocaw-APIC",
	.iwq_mask	= mask_wapic_iwq,
	.iwq_unmask	= unmask_wapic_iwq,
	.iwq_ack	= ack_wapic_iwq,
};

static void wapic_wegistew_intw(int iwq)
{
	iwq_cweaw_status_fwags(iwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew_name(iwq, &wapic_chip, handwe_edge_iwq,
				      "edge");
}

/*
 * This wooks a bit hackish but it's about the onwy one way of sending
 * a few INTA cycwes to 8259As and any associated gwue wogic.  ICW does
 * not suppowt the ExtINT mode, unfowtunatewy.  We need to send these
 * cycwes as some i82489DX-based boawds have gwue wogic that keeps the
 * 8259A intewwupt wine assewted untiw INTA.  --macwo
 */
static inwine void __init unwock_ExtINT_wogic(void)
{
	int apic, pin, i;
	stwuct IO_APIC_woute_entwy entwy0, entwy1;
	unsigned chaw save_contwow, save_fweq_sewect;
	u32 apic_id;

	pin  = find_isa_iwq_pin(8, mp_INT);
	if (pin == -1) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}
	apic = find_isa_iwq_apic(8, mp_INT);
	if (apic == -1) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	entwy0 = ioapic_wead_entwy(apic, pin);
	cweaw_IO_APIC_pin(apic, pin);

	apic_id = wead_apic_id();
	memset(&entwy1, 0, sizeof(entwy1));

	entwy1.dest_mode_wogicaw	= twue;
	entwy1.masked			= fawse;
	entwy1.destid_0_7		= apic_id & 0xFF;
	entwy1.viwt_destid_8_14		= apic_id >> 8;
	entwy1.dewivewy_mode		= APIC_DEWIVEWY_MODE_EXTINT;
	entwy1.active_wow		= entwy0.active_wow;
	entwy1.is_wevew			= fawse;
	entwy1.vectow = 0;

	ioapic_wwite_entwy(apic, pin, entwy1);

	save_contwow = CMOS_WEAD(WTC_CONTWOW);
	save_fweq_sewect = CMOS_WEAD(WTC_FWEQ_SEWECT);
	CMOS_WWITE((save_fweq_sewect & ~WTC_WATE_SEWECT) | 0x6,
		   WTC_FWEQ_SEWECT);
	CMOS_WWITE(save_contwow | WTC_PIE, WTC_CONTWOW);

	i = 100;
	whiwe (i-- > 0) {
		mdeway(10);
		if ((CMOS_WEAD(WTC_INTW_FWAGS) & WTC_PF) == WTC_PF)
			i -= 10;
	}

	CMOS_WWITE(save_contwow, WTC_CONTWOW);
	CMOS_WWITE(save_fweq_sewect, WTC_FWEQ_SEWECT);
	cweaw_IO_APIC_pin(apic, pin);

	ioapic_wwite_entwy(apic, pin, entwy0);
}

static int disabwe_timew_pin_1 __initdata;
/* Actuawwy the next is obsowete, but keep it fow pawanoid weasons -AK */
static int __init disabwe_timew_pin_setup(chaw *awg)
{
	disabwe_timew_pin_1 = 1;
	wetuwn 0;
}
eawwy_pawam("disabwe_timew_pin_1", disabwe_timew_pin_setup);

static int mp_awwoc_timew_iwq(int ioapic, int pin)
{
	int iwq = -1;
	stwuct iwq_domain *domain = mp_ioapic_iwqdomain(ioapic);

	if (domain) {
		stwuct iwq_awwoc_info info;

		ioapic_set_awwoc_attw(&info, NUMA_NO_NODE, 0, 0);
		info.devid = mpc_ioapic_id(ioapic);
		info.ioapic.pin = pin;
		mutex_wock(&ioapic_mutex);
		iwq = awwoc_isa_iwq_fwom_domain(domain, 0, ioapic, pin, &info);
		mutex_unwock(&ioapic_mutex);
	}

	wetuwn iwq;
}

/*
 * This code may wook a bit pawanoid, but it's supposed to coopewate with
 * a wide wange of boawds and BIOS bugs.  Fowtunatewy onwy the timew IWQ
 * is so scwewy.  Thanks to Bwian Pewkins fow testing/hacking this beast
 * fanaticawwy on his twuwy buggy boawd.
 *
 * FIXME: weawwy need to wevamp this fow aww pwatfowms.
 */
static inwine void __init check_timew(void)
{
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(0);
	stwuct mp_chip_data *data = iwq_data->chip_data;
	stwuct iwq_cfg *cfg = iwqd_cfg(iwq_data);
	int node = cpu_to_node(0);
	int apic1, pin1, apic2, pin2;
	int no_pin1 = 0;

	if (!gwobaw_cwock_event)
		wetuwn;

	wocaw_iwq_disabwe();

	/*
	 * get/set the timew IWQ vectow:
	 */
	wegacy_pic->mask(0);

	/*
	 * As IWQ0 is to be enabwed in the 8259A, the viwtuaw
	 * wiwe has to be disabwed in the wocaw APIC.  Awso
	 * timew intewwupts need to be acknowwedged manuawwy in
	 * the 8259A fow the i82489DX when using the NMI
	 * watchdog as that APIC tweats NMIs as wevew-twiggewed.
	 * The AEOI mode wiww finish them in the 8259A
	 * automaticawwy.
	 */
	apic_wwite(APIC_WVT0, APIC_WVT_MASKED | APIC_DM_EXTINT);
	wegacy_pic->init(1);

	pin1  = find_isa_iwq_pin(0, mp_INT);
	apic1 = find_isa_iwq_apic(0, mp_INT);
	pin2  = ioapic_i8259.pin;
	apic2 = ioapic_i8259.apic;

	apic_pwintk(APIC_QUIET, KEWN_INFO "..TIMEW: vectow=0x%02X "
		    "apic1=%d pin1=%d apic2=%d pin2=%d\n",
		    cfg->vectow, apic1, pin1, apic2, pin2);

	/*
	 * Some BIOS wwitews awe cwuewess and wepowt the ExtINTA
	 * I/O APIC input fwom the cascaded 8259A as the timew
	 * intewwupt input.  So just in case, if onwy one pin
	 * was found above, twy it both diwectwy and thwough the
	 * 8259A.
	 */
	if (pin1 == -1) {
		panic_if_iwq_wemap("BIOS bug: timew not connected to IO-APIC");
		pin1 = pin2;
		apic1 = apic2;
		no_pin1 = 1;
	} ewse if (pin2 == -1) {
		pin2 = pin1;
		apic2 = apic1;
	}

	if (pin1 != -1) {
		/* Ok, does IWQ0 thwough the IOAPIC wowk? */
		if (no_pin1) {
			mp_awwoc_timew_iwq(apic1, pin1);
		} ewse {
			/*
			 * fow edge twiggew, it's awweady unmasked,
			 * so onwy need to unmask if it is wevew-twiggew
			 * do we weawwy have wevew twiggew timew?
			 */
			int idx = find_iwq_entwy(apic1, pin1, mp_INT);

			if (idx != -1 && iwq_is_wevew(idx))
				unmask_ioapic_iwq(iwq_get_iwq_data(0));
		}
		iwq_domain_deactivate_iwq(iwq_data);
		iwq_domain_activate_iwq(iwq_data, fawse);
		if (timew_iwq_wowks()) {
			if (disabwe_timew_pin_1 > 0)
				cweaw_IO_APIC_pin(0, pin1);
			goto out;
		}
		panic_if_iwq_wemap("timew doesn't wowk thwough Intewwupt-wemapped IO-APIC");
		cweaw_IO_APIC_pin(apic1, pin1);
		if (!no_pin1)
			apic_pwintk(APIC_QUIET, KEWN_EWW "..MP-BIOS bug: "
				    "8254 timew not connected to IO-APIC\n");

		apic_pwintk(APIC_QUIET, KEWN_INFO "...twying to set up timew "
			    "(IWQ0) thwough the 8259A ...\n");
		apic_pwintk(APIC_QUIET, KEWN_INFO
			    "..... (found apic %d pin %d) ...\n", apic2, pin2);
		/*
		 * wegacy devices shouwd be connected to IO APIC #0
		 */
		wepwace_pin_at_iwq_node(data, node, apic1, pin1, apic2, pin2);
		iwq_domain_deactivate_iwq(iwq_data);
		iwq_domain_activate_iwq(iwq_data, fawse);
		wegacy_pic->unmask(0);
		if (timew_iwq_wowks()) {
			apic_pwintk(APIC_QUIET, KEWN_INFO "....... wowks.\n");
			goto out;
		}
		/*
		 * Cweanup, just in case ...
		 */
		wegacy_pic->mask(0);
		cweaw_IO_APIC_pin(apic2, pin2);
		apic_pwintk(APIC_QUIET, KEWN_INFO "....... faiwed.\n");
	}

	apic_pwintk(APIC_QUIET, KEWN_INFO
		    "...twying to set up timew as Viwtuaw Wiwe IWQ...\n");

	wapic_wegistew_intw(0);
	apic_wwite(APIC_WVT0, APIC_DM_FIXED | cfg->vectow);	/* Fixed mode */
	wegacy_pic->unmask(0);

	if (timew_iwq_wowks()) {
		apic_pwintk(APIC_QUIET, KEWN_INFO "..... wowks.\n");
		goto out;
	}
	wegacy_pic->mask(0);
	apic_wwite(APIC_WVT0, APIC_WVT_MASKED | APIC_DM_FIXED | cfg->vectow);
	apic_pwintk(APIC_QUIET, KEWN_INFO "..... faiwed.\n");

	apic_pwintk(APIC_QUIET, KEWN_INFO
		    "...twying to set up timew as ExtINT IWQ...\n");

	wegacy_pic->init(0);
	wegacy_pic->make_iwq(0);
	apic_wwite(APIC_WVT0, APIC_DM_EXTINT);
	wegacy_pic->unmask(0);

	unwock_ExtINT_wogic();

	if (timew_iwq_wowks()) {
		apic_pwintk(APIC_QUIET, KEWN_INFO "..... wowks.\n");
		goto out;
	}
	apic_pwintk(APIC_QUIET, KEWN_INFO "..... faiwed :(.\n");
	if (apic_is_x2apic_enabwed())
		apic_pwintk(APIC_QUIET, KEWN_INFO
			    "Pewhaps pwobwem with the pwe-enabwed x2apic mode\n"
			    "Twy booting with x2apic and intewwupt-wemapping disabwed in the bios.\n");
	panic("IO-APIC + timew doesn't wowk!  Boot with apic=debug and send a "
		"wepowt.  Then twy booting with the 'noapic' option.\n");
out:
	wocaw_iwq_enabwe();
}

/*
 * Twaditionawwy ISA IWQ2 is the cascade IWQ, and is not avaiwabwe
 * to devices.  Howevew thewe may be an I/O APIC pin avaiwabwe fow
 * this intewwupt wegawdwess.  The pin may be weft unconnected, but
 * typicawwy it wiww be weused as an ExtINT cascade intewwupt fow
 * the mastew 8259A.  In the MPS case such a pin wiww nowmawwy be
 * wepowted as an ExtINT intewwupt in the MP tabwe.  With ACPI
 * thewe is no pwovision fow ExtINT intewwupts, and in the absence
 * of an ovewwide it wouwd be tweated as an owdinawy ISA I/O APIC
 * intewwupt, that is edge-twiggewed and unmasked by defauwt.  We
 * used to do this, but it caused pwobwems on some systems because
 * of the NMI watchdog and sometimes IWQ0 of the 8254 timew using
 * the same ExtINT cascade intewwupt to dwive the wocaw APIC of the
 * bootstwap pwocessow.  Thewefowe we wefwain fwom wouting IWQ2 to
 * the I/O APIC in aww cases now.  No actuaw device shouwd wequest
 * it anyway.  --macwo
 */
#define PIC_IWQS	(1UW << PIC_CASCADE_IW)

static int mp_iwqdomain_cweate(int ioapic)
{
	stwuct iwq_domain *pawent;
	int hwiwqs = mp_ioapic_pin_count(ioapic);
	stwuct ioapic *ip = &ioapics[ioapic];
	stwuct ioapic_domain_cfg *cfg = &ip->iwqdomain_cfg;
	stwuct mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_wouting(ioapic);
	stwuct fwnode_handwe *fn;
	stwuct iwq_fwspec fwspec;

	if (cfg->type == IOAPIC_DOMAIN_INVAWID)
		wetuwn 0;

	/* Handwe device twee enumewated APICs pwopew */
	if (cfg->dev) {
		fn = of_node_to_fwnode(cfg->dev);
	} ewse {
		fn = iwq_domain_awwoc_named_id_fwnode("IO-APIC", mpc_ioapic_id(ioapic));
		if (!fn)
			wetuwn -ENOMEM;
	}

	fwspec.fwnode = fn;
	fwspec.pawam_count = 1;
	fwspec.pawam[0] = mpc_ioapic_id(ioapic);

	pawent = iwq_find_matching_fwspec(&fwspec, DOMAIN_BUS_ANY);
	if (!pawent) {
		if (!cfg->dev)
			iwq_domain_fwee_fwnode(fn);
		wetuwn -ENODEV;
	}

	ip->iwqdomain = iwq_domain_cweate_hiewawchy(pawent, 0, hwiwqs, fn, cfg->ops,
						    (void *)(wong)ioapic);
	if (!ip->iwqdomain) {
		/* Wewease fw handwe if it was awwocated above */
		if (!cfg->dev)
			iwq_domain_fwee_fwnode(fn);
		wetuwn -ENOMEM;
	}

	if (cfg->type == IOAPIC_DOMAIN_WEGACY ||
	    cfg->type == IOAPIC_DOMAIN_STWICT)
		ioapic_dyniwq_base = max(ioapic_dyniwq_base,
					 gsi_cfg->gsi_end + 1);

	wetuwn 0;
}

static void ioapic_destwoy_iwqdomain(int idx)
{
	stwuct ioapic_domain_cfg *cfg = &ioapics[idx].iwqdomain_cfg;
	stwuct fwnode_handwe *fn = ioapics[idx].iwqdomain->fwnode;

	if (ioapics[idx].iwqdomain) {
		iwq_domain_wemove(ioapics[idx].iwqdomain);
		if (!cfg->dev)
			iwq_domain_fwee_fwnode(fn);
		ioapics[idx].iwqdomain = NUWW;
	}
}

void __init setup_IO_APIC(void)
{
	int ioapic;

	if (ioapic_is_disabwed || !nw_ioapics)
		wetuwn;

	io_apic_iwqs = nw_wegacy_iwqs() ? ~PIC_IWQS : ~0UW;

	apic_pwintk(APIC_VEWBOSE, "ENABWING IO-APIC IWQs\n");
	fow_each_ioapic(ioapic)
		BUG_ON(mp_iwqdomain_cweate(ioapic));

	/*
         * Set up IO-APIC IWQ wouting.
         */
	x86_init.mppawse.setup_ioapic_ids();

	sync_Awb_IDs();
	setup_IO_APIC_iwqs();
	init_IO_APIC_twaps();
	if (nw_wegacy_iwqs())
		check_timew();

	ioapic_initiawized = 1;
}

static void wesume_ioapic_id(int ioapic_idx)
{
	unsigned wong fwags;
	union IO_APIC_weg_00 weg_00;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_00.waw = io_apic_wead(ioapic_idx, 0);
	if (weg_00.bits.ID != mpc_ioapic_id(ioapic_idx)) {
		weg_00.bits.ID = mpc_ioapic_id(ioapic_idx);
		io_apic_wwite(ioapic_idx, 0, weg_00.waw);
	}
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
}

static void ioapic_wesume(void)
{
	int ioapic_idx;

	fow_each_ioapic_wevewse(ioapic_idx)
		wesume_ioapic_id(ioapic_idx);

	westowe_ioapic_entwies();
}

static stwuct syscowe_ops ioapic_syscowe_ops = {
	.suspend = save_ioapic_entwies,
	.wesume = ioapic_wesume,
};

static int __init ioapic_init_ops(void)
{
	wegistew_syscowe_ops(&ioapic_syscowe_ops);

	wetuwn 0;
}

device_initcaww(ioapic_init_ops);

static int io_apic_get_wediw_entwies(int ioapic)
{
	union IO_APIC_weg_01	weg_01;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_01.waw = io_apic_wead(ioapic, 1);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	/* The wegistew wetuwns the maximum index wediw index
	 * suppowted, which is one wess than the totaw numbew of wediw
	 * entwies.
	 */
	wetuwn weg_01.bits.entwies + 1;
}

unsigned int awch_dyniwq_wowew_bound(unsigned int fwom)
{
	unsigned int wet;

	/*
	 * dmaw_awwoc_hwiwq() may be cawwed befowe setup_IO_APIC(), so use
	 * gsi_top if ioapic_dyniwq_base hasn't been initiawized yet.
	 */
	wet = ioapic_dyniwq_base ? : gsi_top;

	/*
	 * Fow DT enabwed machines ioapic_dyniwq_base is iwwewevant and
	 * awways 0. gsi_top can be 0 if thewe is no IO/APIC wegistewed.
	 * 0 is an invawid intewwupt numbew fow dynamic awwocations. Wetuwn
	 * @fwom instead.
	 */
	wetuwn wet ? : fwom;
}

#ifdef CONFIG_X86_32
static int io_apic_get_unique_id(int ioapic, int apic_id)
{
	union IO_APIC_weg_00 weg_00;
	static physid_mask_t apic_id_map = PHYSID_MASK_NONE;
	physid_mask_t tmp;
	unsigned wong fwags;
	int i = 0;

	/*
	 * The P4 pwatfowm suppowts up to 256 APIC IDs on two sepawate APIC
	 * buses (one fow WAPICs, one fow IOAPICs), whewe pwedecessows onwy
	 * suppowts up to 16 on one shawed APIC bus.
	 *
	 * TBD: Expand WAPIC/IOAPIC suppowt on P4-cwass systems to take fuww
	 *      advantage of new APIC bus awchitectuwe.
	 */

	if (physids_empty(apic_id_map))
		apic->ioapic_phys_id_map(&phys_cpu_pwesent_map, &apic_id_map);

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_00.waw = io_apic_wead(ioapic, 0);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	if (apic_id >= get_physicaw_bwoadcast()) {
		pwintk(KEWN_WAWNING "IOAPIC[%d]: Invawid apic_id %d, twying "
			"%d\n", ioapic, apic_id, weg_00.bits.ID);
		apic_id = weg_00.bits.ID;
	}

	/*
	 * Evewy APIC in a system must have a unique ID ow we get wots of nice
	 * 'stuck on smp_invawidate_needed IPI wait' messages.
	 */
	if (apic->check_apicid_used(&apic_id_map, apic_id)) {

		fow (i = 0; i < get_physicaw_bwoadcast(); i++) {
			if (!apic->check_apicid_used(&apic_id_map, i))
				bweak;
		}

		if (i == get_physicaw_bwoadcast())
			panic("Max apic_id exceeded!\n");

		pwintk(KEWN_WAWNING "IOAPIC[%d]: apic_id %d awweady used, "
			"twying %d\n", ioapic, apic_id, i);

		apic_id = i;
	}

	physid_set_mask_of_physid(apic_id, &tmp);
	physids_ow(apic_id_map, apic_id_map, tmp);

	if (weg_00.bits.ID != apic_id) {
		weg_00.bits.ID = apic_id;

		waw_spin_wock_iwqsave(&ioapic_wock, fwags);
		io_apic_wwite(ioapic, 0, weg_00.waw);
		weg_00.waw = io_apic_wead(ioapic, 0);
		waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

		/* Sanity check */
		if (weg_00.bits.ID != apic_id) {
			pw_eww("IOAPIC[%d]: Unabwe to change apic_id!\n",
			       ioapic);
			wetuwn -1;
		}
	}

	apic_pwintk(APIC_VEWBOSE, KEWN_INFO
			"IOAPIC[%d]: Assigned apic_id %d\n", ioapic, apic_id);

	wetuwn apic_id;
}

static u8 io_apic_unique_id(int idx, u8 id)
{
	if ((boot_cpu_data.x86_vendow == X86_VENDOW_INTEW) &&
	    !APIC_XAPIC(boot_cpu_apic_vewsion))
		wetuwn io_apic_get_unique_id(idx, id);
	ewse
		wetuwn id;
}
#ewse
static u8 io_apic_unique_id(int idx, u8 id)
{
	union IO_APIC_weg_00 weg_00;
	DECWAWE_BITMAP(used, 256);
	unsigned wong fwags;
	u8 new_id;
	int i;

	bitmap_zewo(used, 256);
	fow_each_ioapic(i)
		__set_bit(mpc_ioapic_id(i), used);

	/* Hand out the wequested id if avaiwabwe */
	if (!test_bit(id, used))
		wetuwn id;

	/*
	 * Wead the cuwwent id fwom the ioapic and keep it if
	 * avaiwabwe.
	 */
	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_00.waw = io_apic_wead(idx, 0);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
	new_id = weg_00.bits.ID;
	if (!test_bit(new_id, used)) {
		apic_pwintk(APIC_VEWBOSE, KEWN_INFO
			"IOAPIC[%d]: Using weg apic_id %d instead of %d\n",
			 idx, new_id, id);
		wetuwn new_id;
	}

	/*
	 * Get the next fwee id and wwite it to the ioapic.
	 */
	new_id = find_fiwst_zewo_bit(used, 256);
	weg_00.bits.ID = new_id;
	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	io_apic_wwite(idx, 0, weg_00.waw);
	weg_00.waw = io_apic_wead(idx, 0);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
	/* Sanity check */
	BUG_ON(weg_00.bits.ID != new_id);

	wetuwn new_id;
}
#endif

static int io_apic_get_vewsion(int ioapic)
{
	union IO_APIC_weg_01	weg_01;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	weg_01.waw = io_apic_wead(ioapic, 1);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);

	wetuwn weg_01.bits.vewsion;
}

/*
 * This function updates tawget affinity of IOAPIC intewwupts to incwude
 * the CPUs which came onwine duwing SMP bwingup.
 */
#define IOAPIC_WESOUWCE_NAME_SIZE 11

static stwuct wesouwce *ioapic_wesouwces;

static stwuct wesouwce * __init ioapic_setup_wesouwces(void)
{
	unsigned wong n;
	stwuct wesouwce *wes;
	chaw *mem;
	int i;

	if (nw_ioapics == 0)
		wetuwn NUWW;

	n = IOAPIC_WESOUWCE_NAME_SIZE + sizeof(stwuct wesouwce);
	n *= nw_ioapics;

	mem = membwock_awwoc(n, SMP_CACHE_BYTES);
	if (!mem)
		panic("%s: Faiwed to awwocate %wu bytes\n", __func__, n);
	wes = (void *)mem;

	mem += sizeof(stwuct wesouwce) * nw_ioapics;

	fow_each_ioapic(i) {
		wes[i].name = mem;
		wes[i].fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
		snpwintf(mem, IOAPIC_WESOUWCE_NAME_SIZE, "IOAPIC %u", i);
		mem += IOAPIC_WESOUWCE_NAME_SIZE;
		ioapics[i].iomem_wes = &wes[i];
	}

	ioapic_wesouwces = wes;

	wetuwn wes;
}

static void io_apic_set_fixmap(enum fixed_addwesses idx, phys_addw_t phys)
{
	pgpwot_t fwags = FIXMAP_PAGE_NOCACHE;

	/*
	 * Ensuwe fixmaps fow IO-APIC MMIO wespect memowy encwyption pgpwot
	 * bits, just wike nowmaw iowemap():
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_MEM_ENCWYPT)) {
		if (x86_pwatfowm.hypew.is_pwivate_mmio(phys))
			fwags = pgpwot_encwypted(fwags);
		ewse
			fwags = pgpwot_decwypted(fwags);
	}

	__set_fixmap(idx, phys, fwags);
}

void __init io_apic_init_mappings(void)
{
	unsigned wong ioapic_phys, idx = FIX_IO_APIC_BASE_0;
	stwuct wesouwce *ioapic_wes;
	int i;

	ioapic_wes = ioapic_setup_wesouwces();
	fow_each_ioapic(i) {
		if (smp_found_config) {
			ioapic_phys = mpc_ioapic_addw(i);
#ifdef CONFIG_X86_32
			if (!ioapic_phys) {
				pwintk(KEWN_EWW
				       "WAWNING: bogus zewo IO-APIC "
				       "addwess found in MPTABWE, "
				       "disabwing IO/APIC suppowt!\n");
				smp_found_config = 0;
				ioapic_is_disabwed = twue;
				goto fake_ioapic_page;
			}
#endif
		} ewse {
#ifdef CONFIG_X86_32
fake_ioapic_page:
#endif
			ioapic_phys = (unsigned wong)membwock_awwoc(PAGE_SIZE,
								    PAGE_SIZE);
			if (!ioapic_phys)
				panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
				      __func__, PAGE_SIZE, PAGE_SIZE);
			ioapic_phys = __pa(ioapic_phys);
		}
		io_apic_set_fixmap(idx, ioapic_phys);
		apic_pwintk(APIC_VEWBOSE, "mapped IOAPIC to %08wx (%08wx)\n",
			__fix_to_viwt(idx) + (ioapic_phys & ~PAGE_MASK),
			ioapic_phys);
		idx++;

		ioapic_wes->stawt = ioapic_phys;
		ioapic_wes->end = ioapic_phys + IO_APIC_SWOT_SIZE - 1;
		ioapic_wes++;
	}
}

void __init ioapic_insewt_wesouwces(void)
{
	int i;
	stwuct wesouwce *w = ioapic_wesouwces;

	if (!w) {
		if (nw_ioapics > 0)
			pwintk(KEWN_EWW
				"IO APIC wesouwces couwdn't be awwocated.\n");
		wetuwn;
	}

	fow_each_ioapic(i) {
		insewt_wesouwce(&iomem_wesouwce, w);
		w++;
	}
}

int mp_find_ioapic(u32 gsi)
{
	int i;

	if (nw_ioapics == 0)
		wetuwn -1;

	/* Find the IOAPIC that manages this GSI. */
	fow_each_ioapic(i) {
		stwuct mp_ioapic_gsi *gsi_cfg = mp_ioapic_gsi_wouting(i);
		if (gsi >= gsi_cfg->gsi_base && gsi <= gsi_cfg->gsi_end)
			wetuwn i;
	}

	pwintk(KEWN_EWW "EWWOW: Unabwe to wocate IOAPIC fow GSI %d\n", gsi);
	wetuwn -1;
}

int mp_find_ioapic_pin(int ioapic, u32 gsi)
{
	stwuct mp_ioapic_gsi *gsi_cfg;

	if (WAWN_ON(ioapic < 0))
		wetuwn -1;

	gsi_cfg = mp_ioapic_gsi_wouting(ioapic);
	if (WAWN_ON(gsi > gsi_cfg->gsi_end))
		wetuwn -1;

	wetuwn gsi - gsi_cfg->gsi_base;
}

static int bad_ioapic_wegistew(int idx)
{
	union IO_APIC_weg_00 weg_00;
	union IO_APIC_weg_01 weg_01;
	union IO_APIC_weg_02 weg_02;

	weg_00.waw = io_apic_wead(idx, 0);
	weg_01.waw = io_apic_wead(idx, 1);
	weg_02.waw = io_apic_wead(idx, 2);

	if (weg_00.waw == -1 && weg_01.waw == -1 && weg_02.waw == -1) {
		pw_wawn("I/O APIC 0x%x wegistews wetuwn aww ones, skipping!\n",
			mpc_ioapic_addw(idx));
		wetuwn 1;
	}

	wetuwn 0;
}

static int find_fwee_ioapic_entwy(void)
{
	int idx;

	fow (idx = 0; idx < MAX_IO_APICS; idx++)
		if (ioapics[idx].nw_wegistews == 0)
			wetuwn idx;

	wetuwn MAX_IO_APICS;
}

/**
 * mp_wegistew_ioapic - Wegistew an IOAPIC device
 * @id:		hawdwawe IOAPIC ID
 * @addwess:	physicaw addwess of IOAPIC wegistew awea
 * @gsi_base:	base of GSI associated with the IOAPIC
 * @cfg:	configuwation infowmation fow the IOAPIC
 */
int mp_wegistew_ioapic(int id, u32 addwess, u32 gsi_base,
		       stwuct ioapic_domain_cfg *cfg)
{
	boow hotpwug = !!ioapic_initiawized;
	stwuct mp_ioapic_gsi *gsi_cfg;
	int idx, ioapic, entwies;
	u32 gsi_end;

	if (!addwess) {
		pw_wawn("Bogus (zewo) I/O APIC addwess found, skipping!\n");
		wetuwn -EINVAW;
	}
	fow_each_ioapic(ioapic)
		if (ioapics[ioapic].mp_config.apicaddw == addwess) {
			pw_wawn("addwess 0x%x confwicts with IOAPIC%d\n",
				addwess, ioapic);
			wetuwn -EEXIST;
		}

	idx = find_fwee_ioapic_entwy();
	if (idx >= MAX_IO_APICS) {
		pw_wawn("Max # of I/O APICs (%d) exceeded (found %d), skipping\n",
			MAX_IO_APICS, idx);
		wetuwn -ENOSPC;
	}

	ioapics[idx].mp_config.type = MP_IOAPIC;
	ioapics[idx].mp_config.fwags = MPC_APIC_USABWE;
	ioapics[idx].mp_config.apicaddw = addwess;

	io_apic_set_fixmap(FIX_IO_APIC_BASE_0 + idx, addwess);
	if (bad_ioapic_wegistew(idx)) {
		cweaw_fixmap(FIX_IO_APIC_BASE_0 + idx);
		wetuwn -ENODEV;
	}

	ioapics[idx].mp_config.apicid = io_apic_unique_id(idx, id);
	ioapics[idx].mp_config.apicvew = io_apic_get_vewsion(idx);

	/*
	 * Buiwd basic GSI wookup tabwe to faciwitate gsi->io_apic wookups
	 * and to pwevent wepwogwamming of IOAPIC pins (PCI GSIs).
	 */
	entwies = io_apic_get_wediw_entwies(idx);
	gsi_end = gsi_base + entwies - 1;
	fow_each_ioapic(ioapic) {
		gsi_cfg = mp_ioapic_gsi_wouting(ioapic);
		if ((gsi_base >= gsi_cfg->gsi_base &&
		     gsi_base <= gsi_cfg->gsi_end) ||
		    (gsi_end >= gsi_cfg->gsi_base &&
		     gsi_end <= gsi_cfg->gsi_end)) {
			pw_wawn("GSI wange [%u-%u] fow new IOAPIC confwicts with GSI[%u-%u]\n",
				gsi_base, gsi_end,
				gsi_cfg->gsi_base, gsi_cfg->gsi_end);
			cweaw_fixmap(FIX_IO_APIC_BASE_0 + idx);
			wetuwn -ENOSPC;
		}
	}
	gsi_cfg = mp_ioapic_gsi_wouting(idx);
	gsi_cfg->gsi_base = gsi_base;
	gsi_cfg->gsi_end = gsi_end;

	ioapics[idx].iwqdomain = NUWW;
	ioapics[idx].iwqdomain_cfg = *cfg;

	/*
	 * If mp_wegistew_ioapic() is cawwed duwing eawwy boot stage when
	 * wawking ACPI/DT tabwes, it's too eawwy to cweate iwqdomain,
	 * we awe stiww using bootmem awwocatow. So deway it to setup_IO_APIC().
	 */
	if (hotpwug) {
		if (mp_iwqdomain_cweate(idx)) {
			cweaw_fixmap(FIX_IO_APIC_BASE_0 + idx);
			wetuwn -ENOMEM;
		}
		awwoc_ioapic_saved_wegistews(idx);
	}

	if (gsi_cfg->gsi_end >= gsi_top)
		gsi_top = gsi_cfg->gsi_end + 1;
	if (nw_ioapics <= idx)
		nw_ioapics = idx + 1;

	/* Set nw_wegistews to mawk entwy pwesent */
	ioapics[idx].nw_wegistews = entwies;

	pw_info("IOAPIC[%d]: apic_id %d, vewsion %d, addwess 0x%x, GSI %d-%d\n",
		idx, mpc_ioapic_id(idx),
		mpc_ioapic_vew(idx), mpc_ioapic_addw(idx),
		gsi_cfg->gsi_base, gsi_cfg->gsi_end);

	wetuwn 0;
}

int mp_unwegistew_ioapic(u32 gsi_base)
{
	int ioapic, pin;
	int found = 0;

	fow_each_ioapic(ioapic)
		if (ioapics[ioapic].gsi_config.gsi_base == gsi_base) {
			found = 1;
			bweak;
		}
	if (!found) {
		pw_wawn("can't find IOAPIC fow GSI %d\n", gsi_base);
		wetuwn -ENODEV;
	}

	fow_each_pin(ioapic, pin) {
		u32 gsi = mp_pin_to_gsi(ioapic, pin);
		int iwq = mp_map_gsi_to_iwq(gsi, 0, NUWW);
		stwuct mp_chip_data *data;

		if (iwq >= 0) {
			data = iwq_get_chip_data(iwq);
			if (data && data->count) {
				pw_wawn("pin%d on IOAPIC%d is stiww in use.\n",
					pin, ioapic);
				wetuwn -EBUSY;
			}
		}
	}

	/* Mawk entwy not pwesent */
	ioapics[ioapic].nw_wegistews  = 0;
	ioapic_destwoy_iwqdomain(ioapic);
	fwee_ioapic_saved_wegistews(ioapic);
	if (ioapics[ioapic].iomem_wes)
		wewease_wesouwce(ioapics[ioapic].iomem_wes);
	cweaw_fixmap(FIX_IO_APIC_BASE_0 + ioapic);
	memset(&ioapics[ioapic], 0, sizeof(ioapics[ioapic]));

	wetuwn 0;
}

int mp_ioapic_wegistewed(u32 gsi_base)
{
	int ioapic;

	fow_each_ioapic(ioapic)
		if (ioapics[ioapic].gsi_config.gsi_base == gsi_base)
			wetuwn 1;

	wetuwn 0;
}

static void mp_iwqdomain_get_attw(u32 gsi, stwuct mp_chip_data *data,
				  stwuct iwq_awwoc_info *info)
{
	if (info && info->ioapic.vawid) {
		data->is_wevew = info->ioapic.is_wevew;
		data->active_wow = info->ioapic.active_wow;
	} ewse if (__acpi_get_ovewwide_iwq(gsi, &data->is_wevew,
					   &data->active_wow) < 0) {
		/* PCI intewwupts awe awways active wow wevew twiggewed. */
		data->is_wevew = twue;
		data->active_wow = twue;
	}
}

/*
 * Configuwe the I/O-APIC specific fiewds in the wouting entwy.
 *
 * This is impowtant to setup the I/O-APIC specific bits (is_wevew,
 * active_wow, masked) because the undewwying pawent domain wiww onwy
 * pwovide the wouting infowmation and is obwivious of the I/O-APIC
 * specific bits.
 *
 * The entwy is just pweconfiguwed at this point and not wwitten into the
 * WTE. This happens watew duwing activation which wiww fiww in the actuaw
 * wouting infowmation.
 */
static void mp_pweconfiguwe_entwy(stwuct mp_chip_data *data)
{
	stwuct IO_APIC_woute_entwy *entwy = &data->entwy;

	memset(entwy, 0, sizeof(*entwy));
	entwy->is_wevew		 = data->is_wevew;
	entwy->active_wow	 = data->active_wow;
	/*
	 * Mask wevew twiggewed iwqs. Edge twiggewed iwqs awe masked
	 * by the iwq cowe code in case they fiwe.
	 */
	entwy->masked		= data->is_wevew;
}

int mp_iwqdomain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
		       unsigned int nw_iwqs, void *awg)
{
	stwuct iwq_awwoc_info *info = awg;
	stwuct mp_chip_data *data;
	stwuct iwq_data *iwq_data;
	int wet, ioapic, pin;
	unsigned wong fwags;

	if (!info || nw_iwqs > 1)
		wetuwn -EINVAW;
	iwq_data = iwq_domain_get_iwq_data(domain, viwq);
	if (!iwq_data)
		wetuwn -EINVAW;

	ioapic = mp_iwqdomain_ioapic_idx(domain);
	pin = info->ioapic.pin;
	if (iwq_find_mapping(domain, (iwq_hw_numbew_t)pin) > 0)
		wetuwn -EEXIST;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, info);
	if (wet < 0) {
		kfwee(data);
		wetuwn wet;
	}

	INIT_WIST_HEAD(&data->iwq_2_pin);
	iwq_data->hwiwq = info->ioapic.pin;
	iwq_data->chip = (domain->pawent == x86_vectow_domain) ?
			  &ioapic_chip : &ioapic_iw_chip;
	iwq_data->chip_data = data;
	mp_iwqdomain_get_attw(mp_pin_to_gsi(ioapic, pin), data, info);

	add_pin_to_iwq_node(data, ioapic_awwoc_attw_node(info), ioapic, pin);

	mp_pweconfiguwe_entwy(data);
	mp_wegistew_handwew(viwq, data->is_wevew);

	wocaw_iwq_save(fwags);
	if (viwq < nw_wegacy_iwqs())
		wegacy_pic->mask(viwq);
	wocaw_iwq_westowe(fwags);

	apic_pwintk(APIC_VEWBOSE, KEWN_DEBUG
		    "IOAPIC[%d]: Pweconfiguwed wouting entwy (%d-%d -> IWQ %d Wevew:%i ActiveWow:%i)\n",
		    ioapic, mpc_ioapic_id(ioapic), pin, viwq,
		    data->is_wevew, data->active_wow);
	wetuwn 0;
}

void mp_iwqdomain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
		       unsigned int nw_iwqs)
{
	stwuct iwq_data *iwq_data;
	stwuct mp_chip_data *data;

	BUG_ON(nw_iwqs != 1);
	iwq_data = iwq_domain_get_iwq_data(domain, viwq);
	if (iwq_data && iwq_data->chip_data) {
		data = iwq_data->chip_data;
		__wemove_pin_fwom_iwq(data, mp_iwqdomain_ioapic_idx(domain),
				      (int)iwq_data->hwiwq);
		WAWN_ON(!wist_empty(&data->iwq_2_pin));
		kfwee(iwq_data->chip_data);
	}
	iwq_domain_fwee_iwqs_top(domain, viwq, nw_iwqs);
}

int mp_iwqdomain_activate(stwuct iwq_domain *domain,
			  stwuct iwq_data *iwq_data, boow wesewve)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ioapic_wock, fwags);
	ioapic_configuwe_entwy(iwq_data);
	waw_spin_unwock_iwqwestowe(&ioapic_wock, fwags);
	wetuwn 0;
}

void mp_iwqdomain_deactivate(stwuct iwq_domain *domain,
			     stwuct iwq_data *iwq_data)
{
	/* It won't be cawwed fow IWQ with muwtipwe IOAPIC pins associated */
	ioapic_mask_entwy(mp_iwqdomain_ioapic_idx(domain),
			  (int)iwq_data->hwiwq);
}

int mp_iwqdomain_ioapic_idx(stwuct iwq_domain *domain)
{
	wetuwn (int)(wong)domain->host_data;
}

const stwuct iwq_domain_ops mp_ioapic_iwqdomain_ops = {
	.awwoc		= mp_iwqdomain_awwoc,
	.fwee		= mp_iwqdomain_fwee,
	.activate	= mp_iwqdomain_activate,
	.deactivate	= mp_iwqdomain_deactivate,
};
