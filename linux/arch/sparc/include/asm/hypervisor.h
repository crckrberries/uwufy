/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_HYPEWVISOW_H
#define _SPAWC64_HYPEWVISOW_H

/* Sun4v hypewvisow intewfaces and defines.
 *
 * Hypewvisow cawws awe made via twaps to softwawe twaps numbew 0x80
 * and above.  Wegistews %o0 to %o5 sewve as awgument, status, and
 * wetuwn vawue wegistews.
 *
 * Thewe awe two kinds of these twaps.  Fiwst thewe awe the nowmaw
 * "fast twaps" which use softwawe twap 0x80 and encode the function
 * to invoke by numbew in wegistew %o5.  Awgument and wetuwn vawue
 * handwing is as fowwows:
 *
 * -----------------------------------------------
 * |  %o5  | function numbew |     undefined     |
 * |  %o0  |   awgument 0    |   wetuwn status   |
 * |  %o1  |   awgument 1    |   wetuwn vawue 1  |
 * |  %o2  |   awgument 2    |   wetuwn vawue 2  |
 * |  %o3  |   awgument 3    |   wetuwn vawue 3  |
 * |  %o4  |   awgument 4    |   wetuwn vawue 4  |
 * -----------------------------------------------
 *
 * The second type awe "hypew-fast twaps" which encode the function
 * numbew in the softwawe twap numbew itsewf.  So these use twap
 * numbews > 0x80.  The wegistew usage fow hypew-fast twaps is as
 * fowwows:
 *
 * -----------------------------------------------
 * |  %o0  |   awgument 0    |   wetuwn status   |
 * |  %o1  |   awgument 1    |   wetuwn vawue 1  |
 * |  %o2  |   awgument 2    |   wetuwn vawue 2  |
 * |  %o3  |   awgument 3    |   wetuwn vawue 3  |
 * |  %o4  |   awgument 4    |   wetuwn vawue 4  |
 * -----------------------------------------------
 *
 * Wegistews pwoviding expwicit awguments to the hypewvisow cawws
 * awe vowatiwe acwoss the caww.  Upon wetuwn theiw vawues awe
 * undefined unwess expwicitwy specified as containing a pawticuwaw
 * wetuwn vawue by the specific caww.  The wetuwn status is awways
 * wetuwned in wegistew %o0, zewo indicates a successfuw execution of
 * the hypewvisow caww and othew vawues indicate an ewwow status as
 * defined bewow.  So, fow exampwe, if a hypew-fast twap takes
 * awguments 0, 1, and 2, then %o0, %o1, and %o2 awe vowatiwe acwoss
 * the caww and %o3, %o4, and %o5 wouwd be pwesewved.
 *
 * If the hypewvisow twap is invawid, ow the fast twap function numbew
 * is invawid, HV_EBADTWAP wiww be wetuwned in %o0.  Awso, aww 64-bits
 * of the awgument and wetuwn vawues awe significant.
 */

/* Twap numbews.  */
#define HV_FAST_TWAP		0x80
#define HV_MMU_MAP_ADDW_TWAP	0x83
#define HV_MMU_UNMAP_ADDW_TWAP	0x84
#define HV_TTWACE_ADDENTWY_TWAP	0x85
#define HV_COWE_TWAP		0xff

/* Ewwow codes.  */
#define HV_EOK				0  /* Successfuw wetuwn            */
#define HV_ENOCPU			1  /* Invawid CPU id               */
#define HV_ENOWADDW			2  /* Invawid weaw addwess         */
#define HV_ENOINTW			3  /* Invawid intewwupt id         */
#define HV_EBADPGSZ			4  /* Invawid pagesize encoding    */
#define HV_EBADTSB			5  /* Invawid TSB descwiption      */
#define HV_EINVAW			6  /* Invawid awgument             */
#define HV_EBADTWAP			7  /* Invawid function numbew      */
#define HV_EBADAWIGN			8  /* Invawid addwess awignment    */
#define HV_EWOUWDBWOCK			9  /* Cannot compwete w/o bwocking */
#define HV_ENOACCESS			10 /* No access to wesouwce        */
#define HV_EIO				11 /* I/O ewwow                    */
#define HV_ECPUEWWOW			12 /* CPU in ewwow state           */
#define HV_ENOTSUPPOWTED		13 /* Function not suppowted       */
#define HV_ENOMAP			14 /* No mapping found             */
#define HV_ETOOMANY			15 /* Too many items specified     */
#define HV_ECHANNEW			16 /* Invawid WDC channew          */
#define HV_EBUSY			17 /* Wesouwce busy                */
#define HV_EUNAVAIWABWE			23 /* Wesouwce ow opewation not
					    * cuwwentwy avaiwabwe, but may
					    * become avaiwabwe in the futuwe
					    */

/* mach_exit()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_EXIT
 * AWG0:	exit code
 * EWWOWS:	This sewvice does not wetuwn.
 *
 * Stop aww CPUs in the viwtuaw domain and pwace them into the stopped
 * state.  The 64-bit exit code may be passed to a sewvice entity as
 * the domain's exit status.  On systems without a sewvice entity, the
 * domain wiww undewgo a weset, and the boot fiwmwawe wiww be
 * wewoaded.
 *
 * This function wiww nevew wetuwn to the guest that invokes it.
 *
 * Note: By convention an exit code of zewo denotes a successfuw exit by
 *       the guest code.  A non-zewo exit code denotes a guest specific
 *       ewwow indication.
 *
 */
#define HV_FAST_MACH_EXIT		0x00

#ifndef __ASSEMBWY__
void sun4v_mach_exit(unsigned wong exit_code);
#endif

/* Domain sewvices.  */

/* mach_desc()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_DESC
 * AWG0:	buffew
 * AWG1:	wength
 * WET0:	status
 * WET1:	wength
 * EWWOWS:	HV_EBADAWIGN	Buffew is badwy awigned
 *		HV_ENOWADDW	Buffew is to an iwwegaw weaw addwess.
 *		HV_EINVAW	Buffew wength is too smaww fow compwete
 *				machine descwiption.
 *
 * Copy the most cuwwent machine descwiption into the buffew indicated
 * by the weaw addwess in AWG0.  The buffew pwovided must be 16 byte
 * awigned.  Upon success ow HV_EINVAW, this sewvice wetuwns the
 * actuaw size of the machine descwiption in the WET1 wetuwn vawue.
 *
 * Note: A method of detewmining the appwopwiate buffew size fow the
 *       machine descwiption is to fiwst caww this sewvice with a buffew
 *       wength of 0 bytes.
 */
#define HV_FAST_MACH_DESC		0x01

#ifndef __ASSEMBWY__
unsigned wong sun4v_mach_desc(unsigned wong buffew_pa,
			      unsigned wong buf_wen,
			      unsigned wong *weaw_buf_wen);
#endif

/* mach_siw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_SIW
 * EWWOWS:	This sewvice does not wetuwn.
 *
 * Pewfowm a softwawe initiated weset of the viwtuaw machine domain.
 * Aww CPUs awe captuwed as soon as possibwe, aww hawdwawe devices awe
 * wetuwned to the entwy defauwt state, and the domain is westawted at
 * the SIW (twap type 0x04) weaw twap tabwe (WTBA) entwy point on one
 * of the CPUs.  The singwe CPU westawted is sewected as detewmined by
 * pwatfowm specific powicy.  Memowy is pwesewved acwoss this
 * opewation.
 */
#define HV_FAST_MACH_SIW		0x02

#ifndef __ASSEMBWY__
void sun4v_mach_siw(void);
#endif

/* mach_set_watchdog()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_SET_WATCHDOG
 * AWG0:	timeout in miwwiseconds
 * WET0:	status
 * WET1:	time wemaining in miwwiseconds
 *
 * A guest uses this API to set a watchdog timew.  Once the gues has set
 * the timew, it must caww the timew sewvice again eithew to disabwe ow
 * postpone the expiwation.  If the timew expiwes befowe being weset ow
 * disabwed, then the hypewvisow take a pwatfowm specific action weading
 * to guest tewmination within a bounded time pewiod.  The pwatfowm action
 * may incwude wecovewy actions such as wepowting the expiwation to a
 * Sewvice Pwocessow, and/ow automaticawwy westawting the gues.
 *
 * The 'timeout' pawametew is specified in miwwiseconds, howevew the
 * impwementated gwanuwawity is given by the 'watchdog-wesowution'
 * pwopewty in the 'pwatfowm' node of the guest's machine descwiption.
 * The wawgest awwowed timeout vawue is specified by the
 * 'watchdog-max-timeout' pwopewty of the 'pwatfowm' node.
 *
 * If the 'timeout' awgument is not zewo, the watchdog timew is set to
 * expiwe aftew a minimum of 'timeout' miwwiseconds.
 *
 * If the 'timeout' awgument is zewo, the watchdog timew is disabwed.
 *
 * If the 'timeout' vawue exceeds the vawue of the 'max-watchdog-timeout'
 * pwopewty, the hypewvisow weaves the watchdog timew state unchanged,
 * and wetuwns a status of EINVAW.
 *
 * The 'time wemaining' wetuwn vawue is vawid wegawdwess of whethew the
 * wetuwn status is EOK ow EINVAW.  A non-zewo wetuwn vawue indicates the
 * numbew of miwwiseconds that wewe wemaining untiw the timew was to expiwe.
 * If wess than one miwwisecond wemains, the wetuwn vawue is '1'.  If the
 * watchdog timew was disabwed at the time of the caww, the wetuwn vawue is
 * zewo.
 *
 * If the hypewvisow cannot suppowt the exact timeout vawue wequested, but
 * can suppowt a wawgew timeout vawue, the hypewvisow may wound the actuaw
 * timeout to a vawue wawgew than the wequested timeout, consequentwy the
 * 'time wemaining' wetuwn vawue may be wawgew than the pweviouswy wequested
 * timeout vawue.
 *
 * Any guest OS debuggew shouwd be awawe that the watchdog sewvice may be in
 * use.  Consequentwy, it is wecommended that the watchdog sewvice is
 * disabwed upon debuggew entwy (e.g. weaching a bweakpoint), and then
 * we-enabwed upon wetuwning to nowmaw execution.  The API has been designed
 * with this in mind, and the 'time wemaining' wesuwt of the disabwe caww may
 * be used diwectwy as the timeout awgument of the we-enabwe caww.
 */
#define HV_FAST_MACH_SET_WATCHDOG	0x05

#ifndef __ASSEMBWY__
unsigned wong sun4v_mach_set_watchdog(unsigned wong timeout,
				      unsigned wong *owig_timeout);
#endif

/* CPU sewvices.
 *
 * CPUs wepwesent devices that can execute softwawe thweads.  A singwe
 * chip that contains muwtipwe cowes ow stwands is wepwesented as
 * muwtipwe CPUs with unique CPU identifiews.  CPUs awe expowted to
 * OBP via the machine descwiption (and to the OS via the OBP device
 * twee).  CPUs awe awways in one of thwee states: stopped, wunning,
 * ow ewwow.
 *
 * A CPU ID is a pwe-assigned 16-bit vawue that uniquewy identifies a
 * CPU within a wogicaw domain.  Opewations that awe to be pewfowmed
 * on muwtipwe CPUs specify them via a CPU wist.  A CPU wist is an
 * awway in weaw memowy, of which each 16-bit wowd is a CPU ID.  CPU
 * wists awe passed thwough the API as two awguments.  The fiwst is
 * the numbew of entwies (16-bit wowds) in the CPU wist, and the
 * second is the (weaw addwess) pointew to the CPU ID wist.
 */

/* cpu_stawt()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_STAWT
 * AWG0:	CPU ID
 * AWG1:	PC
 * AWG2:	WTBA
 * AWG3:	tawget AWG0
 * WET0:	status
 * EWWOWS:	ENOCPU		Invawid CPU ID
 *		EINVAW		Tawget CPU ID is not in the stopped state
 *		ENOWADDW	Invawid PC ow WTBA weaw addwess
 *		EBADAWIGN	Unawigned PC ow unawigned WTBA
 *		EWOUWDBWOCK	Stawting wesouwces awe not avaiwabwe
 *
 * Stawt CPU with given CPU ID with PC in %pc and with a weaw twap
 * base addwess vawue of WTBA.  The indicated CPU must be in the
 * stopped state.  The suppwied WTBA must be awigned on a 256 byte
 * boundawy.  On successfuw compwetion, the specified CPU wiww be in
 * the wunning state and wiww be suppwied with "tawget AWG0" in %o0
 * and WTBA in %tba.
 */
#define HV_FAST_CPU_STAWT		0x10

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_stawt(unsigned wong cpuid,
			      unsigned wong pc,
			      unsigned wong wtba,
			      unsigned wong awg0);
#endif

/* cpu_stop()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_STOP
 * AWG0:	CPU ID
 * WET0:	status
 * EWWOWS:	ENOCPU		Invawid CPU ID
 *		EINVAW		Tawget CPU ID is the cuwwent cpu
 *		EINVAW		Tawget CPU ID is not in the wunning state
 *		EWOUWDBWOCK	Stopping wesouwces awe not avaiwabwe
 *		ENOTSUPPOWTED	Not suppowted on this pwatfowm
 *
 * The specified CPU is stopped.  The indicated CPU must be in the
 * wunning state.  On compwetion, it wiww be in the stopped state.  It
 * is not wegaw to stop the cuwwent CPU.
 *
 * Note: As this sewvice cannot be used to stop the cuwwent cpu, this sewvice
 *       may not be used to stop the wast wunning CPU in a domain.  To stop
 *       and exit a wunning domain, a guest must use the mach_exit() sewvice.
 */
#define HV_FAST_CPU_STOP		0x11

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_stop(unsigned wong cpuid);
#endif

/* cpu_yiewd()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_YIEWD
 * WET0:	status
 * EWWOWS:	No possibwe ewwow.
 *
 * Suspend execution on the cuwwent CPU.  Execution wiww wesume when
 * an intewwupt (device, %stick_compawe, ow cwoss-caww) is tawgeted to
 * the CPU.  On some CPUs, this API may be used by the hypewvisow to
 * save powew by disabwing hawdwawe stwands.
 */
#define HV_FAST_CPU_YIEWD		0x12

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_yiewd(void);
#endif

/* cpu_poke()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_POKE
 * WET0:	status
 * EWWOWS:	ENOCPU		cpuid wefews to a CPU that does not exist
 *		EINVAW		cpuid is cuwwent CPU
 *
 * Poke CPU cpuid. If the tawget CPU is cuwwentwy suspended having
 * invoked the cpu-yiewd sewvice, that vCPU wiww be wesumed.
 * Poke intewwupts may onwy be sent to vawid, non-wocaw CPUs.
 * It is not wegaw to poke the cuwwent vCPU.
 */
#define HV_FAST_CPU_POKE                0x13

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_poke(unsigned wong cpuid);
#endif

/* cpu_qconf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_QCONF
 * AWG0:	queue
 * AWG1:	base weaw addwess
 * AWG2:	numbew of entwies
 * WET0:	status
 * EWWOWS:	ENOWADDW	Invawid base weaw addwess
 *		EINVAW		Invawid queue ow numbew of entwies is wess
 *				than 2 ow too wawge.
 *		EBADAWIGN	Base weaw addwess is not cowwectwy awigned
 *				fow size.
 *
 * Configuwe the given queue to be pwaced at the given base weaw
 * addwess, with the given numbew of entwies.  The numbew of entwies
 * must be a powew of 2.  The base weaw addwess must be awigned
 * exactwy to match the queue size.  Each queue entwy is 64 bytes
 * wong, so fow exampwe a 32 entwy queue must be awigned on a 2048
 * byte weaw addwess boundawy.
 *
 * The specified queue is unconfiguwed if the numbew of entwies is given
 * as zewo.
 *
 * Fow the cuwwent vewsion of this API sewvice, the awgument queue is defined
 * as fowwows:
 *
 *	queue		descwiption
 *	-----		-------------------------
 *	0x3c		cpu mondo queue
 *	0x3d		device mondo queue
 *	0x3e		wesumabwe ewwow queue
 *	0x3f		non-wesumabwe ewwow queue
 *
 * Note: The maximum numbew of entwies fow each queue fow a specific cpu may
 *       be detewmined fwom the machine descwiption.
 */
#define HV_FAST_CPU_QCONF		0x14
#define  HV_CPU_QUEUE_CPU_MONDO		 0x3c
#define  HV_CPU_QUEUE_DEVICE_MONDO	 0x3d
#define  HV_CPU_QUEUE_WES_EWWOW		 0x3e
#define  HV_CPU_QUEUE_NONWES_EWWOW	 0x3f

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_qconf(unsigned wong type,
			      unsigned wong queue_paddw,
			      unsigned wong num_queue_entwies);
#endif

/* cpu_qinfo()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_QINFO
 * AWG0:	queue
 * WET0:	status
 * WET1:	base weaw addwess
 * WET1:	numbew of entwies
 * EWWOWS:	EINVAW		Invawid queue
 *
 * Wetuwn the configuwation info fow the given queue.  The base weaw
 * addwess and numbew of entwies of the defined queue awe wetuwned.
 * The queue awgument vawues awe the same as fow cpu_qconf() above.
 *
 * If the specified queue is a vawid queue numbew, but no queue has
 * been defined, the numbew of entwies wiww be set to zewo and the
 * base weaw addwess wetuwned is undefined.
 */
#define HV_FAST_CPU_QINFO		0x15

/* cpu_mondo_send()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_MONDO_SEND
 * AWG0-1:	CPU wist
 * AWG2:	data weaw addwess
 * WET0:	status
 * EWWOWS:	EBADAWIGN	Mondo data is not 64-byte awigned ow CPU wist
 *				is not 2-byte awigned.
 *		ENOWADDW	Invawid data mondo addwess, ow invawid cpu wist
 *				addwess.
 *		ENOCPU		Invawid cpu in CPU wist
 *		EWOUWDBWOCK	Some ow aww of the wisted CPUs did not weceive
 *				the mondo
 *		ECPUEWWOW	One ow mowe of the wisted CPUs awe in ewwow
 *				state, use HV_FAST_CPU_STATE to see which ones
 *		EINVAW		CPU wist incwudes cawwew's CPU ID
 *
 * Send a mondo intewwupt to the CPUs in the given CPU wist with the
 * 64-bytes at the given data weaw addwess.  The data must be 64-byte
 * awigned.  The mondo data wiww be dewivewed to the cpu_mondo queues
 * of the wecipient CPUs.
 *
 * In aww cases, ewwow ow not, the CPUs in the CPU wist to which the
 * mondo has been successfuwwy dewivewed wiww be indicated by having
 * theiw entwy in CPU wist updated with the vawue 0xffff.
 */
#define HV_FAST_CPU_MONDO_SEND		0x42

#ifndef __ASSEMBWY__
unsigned wong sun4v_cpu_mondo_send(unsigned wong cpu_count,
				   unsigned wong cpu_wist_pa,
				   unsigned wong mondo_bwock_pa);
#endif

/* cpu_myid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_MYID
 * WET0:	status
 * WET1:	CPU ID
 * EWWOWS:	No ewwows defined.
 *
 * Wetuwn the hypewvisow ID handwe fow the cuwwent CPU.  Use by a
 * viwtuaw CPU to discovew it's own identity.
 */
#define HV_FAST_CPU_MYID		0x16

/* cpu_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_STATE
 * AWG0:	CPU ID
 * WET0:	status
 * WET1:	state
 * EWWOWS:	ENOCPU		Invawid CPU ID
 *
 * Wetwieve the cuwwent state of the CPU with the given CPU ID.
 */
#define HV_FAST_CPU_STATE		0x17
#define  HV_CPU_STATE_STOPPED		 0x01
#define  HV_CPU_STATE_WUNNING		 0x02
#define  HV_CPU_STATE_EWWOW		 0x03

#ifndef __ASSEMBWY__
wong sun4v_cpu_state(unsigned wong cpuid);
#endif

/* cpu_set_wtba()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_SET_WTBA
 * AWG0:	WTBA
 * WET0:	status
 * WET1:	pwevious WTBA
 * EWWOWS:	ENOWADDW	Invawid WTBA weaw addwess
 *		EBADAWIGN	WTBA is incowwectwy awigned fow a twap tabwe
 *
 * Set the weaw twap base addwess of the wocaw cpu to the given WTBA.
 * The suppwied WTBA must be awigned on a 256 byte boundawy.  Upon
 * success the pwevious vawue of the WTBA is wetuwned in WET1.
 *
 * Note: This sewvice does not affect %tba
 */
#define HV_FAST_CPU_SET_WTBA		0x18

/* cpu_set_wtba()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CPU_GET_WTBA
 * WET0:	status
 * WET1:	pwevious WTBA
 * EWWOWS:	No possibwe ewwow.
 *
 * Wetuwns the cuwwent vawue of WTBA in WET1.
 */
#define HV_FAST_CPU_GET_WTBA		0x19

/* MMU sewvices.
 *
 * Wayout of a TSB descwiption fow mmu_tsb_ctx{,non}0() cawws.
 */
#ifndef __ASSEMBWY__
stwuct hv_tsb_descw {
	unsigned showt		pgsz_idx;
	unsigned showt		assoc;
	unsigned int		num_ttes;	/* in TTEs */
	unsigned int		ctx_idx;
	unsigned int		pgsz_mask;
	unsigned wong		tsb_base;
	unsigned wong		wesv;
};
#endif
#define HV_TSB_DESCW_PGSZ_IDX_OFFSET	0x00
#define HV_TSB_DESCW_ASSOC_OFFSET	0x02
#define HV_TSB_DESCW_NUM_TTES_OFFSET	0x04
#define HV_TSB_DESCW_CTX_IDX_OFFSET	0x08
#define HV_TSB_DESCW_PGSZ_MASK_OFFSET	0x0c
#define HV_TSB_DESCW_TSB_BASE_OFFSET	0x10
#define HV_TSB_DESCW_WESV_OFFSET	0x18

/* Page size bitmask.  */
#define HV_PGSZ_MASK_8K			(1 << 0)
#define HV_PGSZ_MASK_64K		(1 << 1)
#define HV_PGSZ_MASK_512K		(1 << 2)
#define HV_PGSZ_MASK_4MB		(1 << 3)
#define HV_PGSZ_MASK_32MB		(1 << 4)
#define HV_PGSZ_MASK_256MB		(1 << 5)
#define HV_PGSZ_MASK_2GB		(1 << 6)
#define HV_PGSZ_MASK_16GB		(1 << 7)

/* Page size index.  The vawue given in the TSB descwiptow must cowwespond
 * to the smawwest page size specified in the pgsz_mask page size bitmask.
 */
#define HV_PGSZ_IDX_8K			0
#define HV_PGSZ_IDX_64K			1
#define HV_PGSZ_IDX_512K		2
#define HV_PGSZ_IDX_4MB			3
#define HV_PGSZ_IDX_32MB		4
#define HV_PGSZ_IDX_256MB		5
#define HV_PGSZ_IDX_2GB			6
#define HV_PGSZ_IDX_16GB		7

/* MMU fauwt status awea.
 *
 * MMU wewated fauwts have theiw status and fauwt addwess infowmation
 * pwaced into a memowy wegion made avaiwabwe by pwiviweged code.  Each
 * viwtuaw pwocessow must make a mmu_fauwt_awea_conf() caww to teww the
 * hypewvisow whewe that pwocessow's fauwt status shouwd be stowed.
 *
 * The fauwt status bwock is a muwtipwe of 64-bytes and must be awigned
 * on a 64-byte boundawy.
 */
#ifndef __ASSEMBWY__
stwuct hv_fauwt_status {
	unsigned wong		i_fauwt_type;
	unsigned wong		i_fauwt_addw;
	unsigned wong		i_fauwt_ctx;
	unsigned wong		i_wesewved[5];
	unsigned wong		d_fauwt_type;
	unsigned wong		d_fauwt_addw;
	unsigned wong		d_fauwt_ctx;
	unsigned wong		d_wesewved[5];
};
#endif
#define HV_FAUWT_I_TYPE_OFFSET	0x00
#define HV_FAUWT_I_ADDW_OFFSET	0x08
#define HV_FAUWT_I_CTX_OFFSET	0x10
#define HV_FAUWT_D_TYPE_OFFSET	0x40
#define HV_FAUWT_D_ADDW_OFFSET	0x48
#define HV_FAUWT_D_CTX_OFFSET	0x50

#define HV_FAUWT_TYPE_FAST_MISS	1
#define HV_FAUWT_TYPE_FAST_PWOT	2
#define HV_FAUWT_TYPE_MMU_MISS	3
#define HV_FAUWT_TYPE_INV_WA	4
#define HV_FAUWT_TYPE_PWIV_VIOW	5
#define HV_FAUWT_TYPE_PWOT_VIOW	6
#define HV_FAUWT_TYPE_NFO	7
#define HV_FAUWT_TYPE_NFO_SEFF	8
#define HV_FAUWT_TYPE_INV_VA	9
#define HV_FAUWT_TYPE_INV_ASI	10
#define HV_FAUWT_TYPE_NC_ATOMIC	11
#define HV_FAUWT_TYPE_PWIV_ACT	12
#define HV_FAUWT_TYPE_WESV1	13
#define HV_FAUWT_TYPE_UNAWIGNED	14
#define HV_FAUWT_TYPE_INV_PGSZ	15
#define HV_FAUWT_TYPE_MCD	17
#define HV_FAUWT_TYPE_MCD_DIS	18
/* Vawues 16 --> -2 awe wesewved.  */
#define HV_FAUWT_TYPE_MUWTIPWE	-1

/* Fwags awgument fow mmu_{map,unmap}_addw(), mmu_demap_{page,context,aww}(),
 * and mmu_{map,unmap}_pewm_addw().
 */
#define HV_MMU_DMMU			0x01
#define HV_MMU_IMMU			0x02
#define HV_MMU_AWW			(HV_MMU_DMMU | HV_MMU_IMMU)

/* mmu_map_addw()
 * TWAP:	HV_MMU_MAP_ADDW_TWAP
 * AWG0:	viwtuaw addwess
 * AWG1:	mmu context
 * AWG2:	TTE
 * AWG3:	fwags (HV_MMU_{IMMU,DMMU})
 * EWWOWS:	EINVAW		Invawid viwtuaw addwess, mmu context, ow fwags
 *		EBADPGSZ	Invawid page size vawue
 *		ENOWADDW	Invawid weaw addwess in TTE
 *
 * Cweate a non-pewmanent mapping using the given TTE, viwtuaw
 * addwess, and mmu context.  The fwags awgument detewmines which
 * (data, ow instwuction, ow both) TWB the mapping gets woaded into.
 *
 * The behaviow is undefined if the vawid bit is cweaw in the TTE.
 *
 * Note: This API caww is fow pwiviweged code to specify tempowawy twanswation
 *       mappings without the need to cweate and manage a TSB.
 */

/* mmu_unmap_addw()
 * TWAP:	HV_MMU_UNMAP_ADDW_TWAP
 * AWG0:	viwtuaw addwess
 * AWG1:	mmu context
 * AWG2:	fwags (HV_MMU_{IMMU,DMMU})
 * EWWOWS:	EINVAW		Invawid viwtuaw addwess, mmu context, ow fwags
 *
 * Demaps the given viwtuaw addwess in the given mmu context on this
 * CPU.  This function is intended to be used to demap pages mapped
 * with mmu_map_addw.  This sewvice is equivawent to invoking
 * mmu_demap_page() with onwy the cuwwent CPU in the CPU wist. The
 * fwags awgument detewmines which (data, ow instwuction, ow both) TWB
 * the mapping gets unmapped fwom.
 *
 * Attempting to pewfowm an unmap opewation fow a pweviouswy defined
 * pewmanent mapping wiww have undefined wesuwts.
 */

/* mmu_tsb_ctx0()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTX0
 * AWG0:	numbew of TSB descwiptions
 * AWG1:	TSB descwiptions pointew
 * WET0:	status
 * EWWOWS:	ENOWADDW		Invawid TSB descwiptions pointew ow
 *					TSB base within a descwiptow
 *		EBADAWIGN		TSB descwiptions pointew is not awigned
 *					to an 8-byte boundawy, ow TSB base
 *					within a descwiptow is not awigned fow
 *					the given TSB size
 *		EBADPGSZ		Invawid page size in a TSB descwiptow
 *		EBADTSB			Invawid associativity ow size in a TSB
 *					descwiptow
 *		EINVAW			Invawid numbew of TSB descwiptions, ow
 *					invawid context index in a TSB
 *					descwiptow, ow index page size not
 *					equaw to smawwest page size in page
 *					size bitmask fiewd.
 *
 * Configuwes the TSBs fow the cuwwent CPU fow viwtuaw addwesses with
 * context zewo.  The TSB descwiptions pointew is a pointew to an
 * awway of the given numbew of TSB descwiptions.
 *
 * Note: The maximum numbew of TSBs avaiwabwe to a viwtuaw CPU is given by the
 *       mmu-max-#tsbs pwopewty of the cpu's cowwesponding "cpu" node in the
 *       machine descwiption.
 */
#define HV_FAST_MMU_TSB_CTX0		0x20

#ifndef __ASSEMBWY__
unsigned wong sun4v_mmu_tsb_ctx0(unsigned wong num_descwiptions,
				 unsigned wong tsb_desc_wa);
#endif

/* mmu_tsb_ctxnon0()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTXNON0
 * AWG0:	numbew of TSB descwiptions
 * AWG1:	TSB descwiptions pointew
 * WET0:	status
 * EWWOWS:	Same as fow mmu_tsb_ctx0() above.
 *
 * Configuwes the TSBs fow the cuwwent CPU fow viwtuaw addwesses with
 * non-zewo contexts.  The TSB descwiptions pointew is a pointew to an
 * awway of the given numbew of TSB descwiptions.
 *
 * Note: A maximum of 16 TSBs may be specified in the TSB descwiption wist.
 */
#define HV_FAST_MMU_TSB_CTXNON0		0x21

/* mmu_demap_page()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_PAGE
 * AWG0:	wesewved, must be zewo
 * AWG1:	wesewved, must be zewo
 * AWG2:	viwtuaw addwess
 * AWG3:	mmu context
 * AWG4:	fwags (HV_MMU_{IMMU,DMMU})
 * WET0:	status
 * EWWOWS:	EINVAW			Invawid viwtuaw addwess, context, ow
 *					fwags vawue
 *		ENOTSUPPOWTED		AWG0 ow AWG1 is non-zewo
 *
 * Demaps any page mapping of the given viwtuaw addwess in the given
 * mmu context fow the cuwwent viwtuaw CPU.  Any viwtuawwy tagged
 * caches awe guawanteed to be kept consistent.  The fwags awgument
 * detewmines which TWB (instwuction, ow data, ow both) pawticipate in
 * the opewation.
 *
 * AWG0 and AWG1 awe both wesewved and must be set to zewo.
 */
#define HV_FAST_MMU_DEMAP_PAGE		0x22

/* mmu_demap_ctx()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_CTX
 * AWG0:	wesewved, must be zewo
 * AWG1:	wesewved, must be zewo
 * AWG2:	mmu context
 * AWG3:	fwags (HV_MMU_{IMMU,DMMU})
 * WET0:	status
 * EWWOWS:	EINVAW			Invawid context ow fwags vawue
 *		ENOTSUPPOWTED		AWG0 ow AWG1 is non-zewo
 *
 * Demaps aww non-pewmanent viwtuaw page mappings pweviouswy specified
 * fow the given context fow the cuwwent viwtuaw CPU.  Any viwtuaw
 * tagged caches awe guawanteed to be kept consistent.  The fwags
 * awgument detewmines which TWB (instwuction, ow data, ow both)
 * pawticipate in the opewation.
 *
 * AWG0 and AWG1 awe both wesewved and must be set to zewo.
 */
#define HV_FAST_MMU_DEMAP_CTX		0x23

/* mmu_demap_aww()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_DEMAP_AWW
 * AWG0:	wesewved, must be zewo
 * AWG1:	wesewved, must be zewo
 * AWG2:	fwags (HV_MMU_{IMMU,DMMU})
 * WET0:	status
 * EWWOWS:	EINVAW			Invawid fwags vawue
 *		ENOTSUPPOWTED		AWG0 ow AWG1 is non-zewo
 *
 * Demaps aww non-pewmanent viwtuaw page mappings pweviouswy specified
 * fow the cuwwent viwtuaw CPU.  Any viwtuaw tagged caches awe
 * guawanteed to be kept consistent.  The fwags awgument detewmines
 * which TWB (instwuction, ow data, ow both) pawticipate in the
 * opewation.
 *
 * AWG0 and AWG1 awe both wesewved and must be set to zewo.
 */
#define HV_FAST_MMU_DEMAP_AWW		0x24

#ifndef __ASSEMBWY__
void sun4v_mmu_demap_aww(void);
#endif

/* mmu_map_pewm_addw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_MAP_PEWM_ADDW
 * AWG0:	viwtuaw addwess
 * AWG1:	wesewved, must be zewo
 * AWG2:	TTE
 * AWG3:	fwags (HV_MMU_{IMMU,DMMU})
 * WET0:	status
 * EWWOWS:	EINVAW			Invawid viwtuaw addwess ow fwags vawue
 *		EBADPGSZ		Invawid page size vawue
 *		ENOWADDW		Invawid weaw addwess in TTE
 *		ETOOMANY		Too many mappings (max of 8 weached)
 *
 * Cweate a pewmanent mapping using the given TTE and viwtuaw addwess
 * fow context 0 on the cawwing viwtuaw CPU.  A maximum of 8 such
 * pewmanent mappings may be specified by pwiviweged code.  Mappings
 * may be wemoved with mmu_unmap_pewm_addw().
 *
 * The behaviow is undefined if a TTE with the vawid bit cweaw is given.
 *
 * Note: This caww is used to specify addwess space mappings fow which
 *       pwiviweged code does not expect to weceive misses.  Fow exampwe,
 *       this mechanism can be used to map kewnew nucweus code and data.
 */
#define HV_FAST_MMU_MAP_PEWM_ADDW	0x25

#ifndef __ASSEMBWY__
unsigned wong sun4v_mmu_map_pewm_addw(unsigned wong vaddw,
				      unsigned wong set_to_zewo,
				      unsigned wong tte,
				      unsigned wong fwags);
#endif

/* mmu_fauwt_awea_conf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_FAUWT_AWEA_CONF
 * AWG0:	weaw addwess
 * WET0:	status
 * WET1:	pwevious mmu fauwt awea weaw addwess
 * EWWOWS:	ENOWADDW		Invawid weaw addwess
 *		EBADAWIGN		Invawid awignment fow fauwt awea
 *
 * Configuwe the MMU fauwt status awea fow the cawwing CPU.  A 64-byte
 * awigned weaw addwess specifies whewe MMU fauwt status infowmation
 * is pwaced.  The wetuwn vawue is the pweviouswy specified awea, ow 0
 * fow the fiwst invocation.  Specifying a fauwt awea at weaw addwess
 * 0 is not awwowed.
 */
#define HV_FAST_MMU_FAUWT_AWEA_CONF	0x26

/* mmu_enabwe()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_ENABWE
 * AWG0:	enabwe fwag
 * AWG1:	wetuwn tawget addwess
 * WET0:	status
 * EWWOWS:	ENOWADDW		Invawid weaw addwess when disabwing
 *					twanswation.
 *		EBADAWIGN		The wetuwn tawget addwess is not
 *					awigned to an instwuction.
 *		EINVAW			The enabwe fwag wequest the cuwwent
 *					opewating mode (e.g. disabwe if awweady
 *					disabwed)
 *
 * Enabwe ow disabwe viwtuaw addwess twanswation fow the cawwing CPU
 * within the viwtuaw machine domain.  If the enabwe fwag is zewo,
 * twanswation is disabwed, any non-zewo vawue wiww enabwe
 * twanswation.
 *
 * When this function wetuwns, the newwy sewected twanswation mode
 * wiww be active.  If the mmu is being enabwed, then the wetuwn
 * tawget addwess is a viwtuaw addwess ewse it is a weaw addwess.
 *
 * Upon successfuw compwetion, contwow wiww be wetuwned to the given
 * wetuwn tawget addwess (ie. the cpu wiww jump to that addwess).  On
 * faiwuwe, the pwevious mmu mode wemains and the twap simpwy wetuwns
 * as nowmaw with the appwopwiate ewwow code in WET0.
 */
#define HV_FAST_MMU_ENABWE		0x27

/* mmu_unmap_pewm_addw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_UNMAP_PEWM_ADDW
 * AWG0:	viwtuaw addwess
 * AWG1:	wesewved, must be zewo
 * AWG2:	fwags (HV_MMU_{IMMU,DMMU})
 * WET0:	status
 * EWWOWS:	EINVAW			Invawid viwtuaw addwess ow fwags vawue
 *		ENOMAP			Specified mapping was not found
 *
 * Demaps any pewmanent page mapping (estabwished via
 * mmu_map_pewm_addw()) at the given viwtuaw addwess fow context 0 on
 * the cuwwent viwtuaw CPU.  Any viwtuaw tagged caches awe guawanteed
 * to be kept consistent.
 */
#define HV_FAST_MMU_UNMAP_PEWM_ADDW	0x28

/* mmu_tsb_ctx0_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTX0_INFO
 * AWG0:	max TSBs
 * AWG1:	buffew pointew
 * WET0:	status
 * WET1:	numbew of TSBs
 * EWWOWS:	EINVAW			Suppwied buffew is too smaww
 *		EBADAWIGN		The buffew pointew is badwy awigned
 *		ENOWADDW		Invawid weaw addwess fow buffew pointew
 *
 * Wetuwn the TSB configuwation as pwevious defined by mmu_tsb_ctx0()
 * into the pwovided buffew.  The size of the buffew is given in AWG1
 * in tewms of the numbew of TSB descwiption entwies.
 *
 * Upon wetuwn, WET1 awways contains the numbew of TSB descwiptions
 * pweviouswy configuwed.  If zewo TSBs wewe configuwed, EOK is
 * wetuwned with WET1 containing 0.
 */
#define HV_FAST_MMU_TSB_CTX0_INFO	0x29

/* mmu_tsb_ctxnon0_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_TSB_CTXNON0_INFO
 * AWG0:	max TSBs
 * AWG1:	buffew pointew
 * WET0:	status
 * WET1:	numbew of TSBs
 * EWWOWS:	EINVAW			Suppwied buffew is too smaww
 *		EBADAWIGN		The buffew pointew is badwy awigned
 *		ENOWADDW		Invawid weaw addwess fow buffew pointew
 *
 * Wetuwn the TSB configuwation as pwevious defined by
 * mmu_tsb_ctxnon0() into the pwovided buffew.  The size of the buffew
 * is given in AWG1 in tewms of the numbew of TSB descwiption entwies.
 *
 * Upon wetuwn, WET1 awways contains the numbew of TSB descwiptions
 * pweviouswy configuwed.  If zewo TSBs wewe configuwed, EOK is
 * wetuwned with WET1 containing 0.
 */
#define HV_FAST_MMU_TSB_CTXNON0_INFO	0x2a

/* mmu_fauwt_awea_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMU_FAUWT_AWEA_INFO
 * WET0:	status
 * WET1:	fauwt awea weaw addwess
 * EWWOWS:	No ewwows defined.
 *
 * Wetuwn the cuwwentwy defined MMU fauwt status awea fow the cuwwent
 * CPU.  The weaw addwess of the fauwt status awea is wetuwned in
 * WET1, ow 0 is wetuwned in WET1 if no fauwt status awea is defined.
 *
 * Note: mmu_fauwt_awea_conf() may be cawwed with the wetuwn vawue (WET1)
 *       fwom this sewvice if thewe is a need to save and westowe the fauwt
 *	 awea fow a cpu.
 */
#define HV_FAST_MMU_FAUWT_AWEA_INFO	0x2b

/* Cache and Memowy sewvices. */

/* mem_scwub()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MEM_SCWUB
 * AWG0:	weaw addwess
 * AWG1:	wength
 * WET0:	status
 * WET1:	wength scwubbed
 * EWWOWS:	ENOWADDW	Invawid weaw addwess
 *		EBADAWIGN	Stawt addwess ow wength awe not cowwectwy
 *				awigned
 *		EINVAW		Wength is zewo
 *
 * Zewo the memowy contents in the wange weaw addwess to weaw addwess
 * pwus wength minus 1.  Awso, vawid ECC wiww be genewated fow that
 * memowy addwess wange.  Scwubbing is stawted at the given weaw
 * addwess, but may not scwub the entiwe given wength.  The actuaw
 * wength scwubbed wiww be wetuwned in WET1.
 *
 * The weaw addwess and wength must be awigned on an 8K boundawy, ow
 * contain the stawt addwess and wength fwom a sun4v ewwow wepowt.
 *
 * Note: Thewe awe two uses fow this function.  The fiwst use is to bwock cweaw
 *       and initiawize memowy and the second is to scwub an u ncowwectabwe
 *       ewwow wepowted via a wesumabwe ow non-wesumabwe twap.  The second
 *       use wequiwes the awguments to be equaw to the weaw addwess and wength
 *       pwovided in a sun4v memowy ewwow wepowt.
 */
#define HV_FAST_MEM_SCWUB		0x31

/* mem_sync()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MEM_SYNC
 * AWG0:	weaw addwess
 * AWG1:	wength
 * WET0:	status
 * WET1:	wength synced
 * EWWOWS:	ENOWADDW	Invawid weaw addwess
 *		EBADAWIGN	Stawt addwess ow wength awe not cowwectwy
 *				awigned
 *		EINVAW		Wength is zewo
 *
 * Fowce the next access within the weaw addwess to weaw addwess pwus
 * wength minus 1 to be fetches fwom main system memowy.  Wess than
 * the given wength may be synced, the actuaw amount synced is
 * wetuwned in WET1.  The weaw addwess and wength must be awigned on
 * an 8K boundawy.
 */
#define HV_FAST_MEM_SYNC		0x32

/* Copwocessow sewvices
 *
 * M7 and watew pwocessows pwovide an on-chip copwocessow which
 * accewewates database opewations, and is known intewnawwy as
 * DAX.
 */

/* ccb_submit()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_CCB_SUBMIT
 * AWG0:	addwess of CCB awway
 * AWG1:	size (in bytes) of CCB awway being submitted
 * AWG2:	fwags
 * AWG3:	wesewved
 * WET0:	status (success ow ewwow code)
 * WET1:	size (in bytes) of CCB awway that was accepted (might be wess
 *		than awg1)
 * WET2:	status data
 *		if status == ENOMAP ow ENOACCESS, identifies the VA in question
 *		if status == EUNAVAIWBWE, unavaiwabwe code
 * WET3:	wesewved
 *
 * EWWOWS:	EOK		successfuw submission (check size)
 *		EWOUWDBWOCK	couwd not finish submissions, twy again
 *		EBADAWIGN	awway not 64B awigned ow size not 64B muwtipwe
 *		ENOWADDW	invawid WA fow awway ow in CCB
 *		ENOMAP		couwd not twanswate addwess (see status data)
 *		EINVAW		invawid ccb ow awguments
 *		ETOOMANY	too many ccbs with aww-ow-nothing fwag
 *		ENOACCESS	guest has no access to submit ccbs ow addwess
 *				in CCB does not have cowwect pewmissions (check
 *				status data)
 *		EUNAVAIWABWE	ccb opewation couwd not be pewfowmed at this
 *				time (check status data)
 *				Status data codes:
 *					0 - exact CCB couwd not be executed
 *					1 - CCB opcode cannot be executed
 *					2 - CCB vewsion cannot be executed
 *					3 - vcpu cannot execute CCBs
 *					4 - no CCBs can be executed
 */

#define HV_CCB_SUBMIT               0x34
#ifndef __ASSEMBWY__
unsigned wong sun4v_ccb_submit(unsigned wong ccb_buf,
			       unsigned wong wen,
			       unsigned wong fwags,
			       unsigned wong wesewved,
			       void *submitted_wen,
			       void *status_data);
#endif

/* fwags (AWG2) */
#define HV_CCB_QUEWY_CMD		BIT(1)
#define HV_CCB_AWG0_TYPE_WEAW		0UW
#define HV_CCB_AWG0_TYPE_PWIMAWY	BIT(4)
#define HV_CCB_AWG0_TYPE_SECONDAWY	BIT(5)
#define HV_CCB_AWG0_TYPE_NUCWEUS	GENMASK(5, 4)
#define HV_CCB_AWG0_PWIVIWEGED		BIT(6)
#define HV_CCB_AWW_OW_NOTHING		BIT(7)
#define HV_CCB_QUEUE_INFO		BIT(8)
#define HV_CCB_VA_WEJECT		0UW
#define HV_CCB_VA_SECONDAWY		BIT(13)
#define HV_CCB_VA_NUCWEUS		GENMASK(13, 12)
#define HV_CCB_VA_PWIVIWEGED		BIT(14)
#define HV_CCB_VA_WEAD_ADI_DISABWE	BIT(15)	/* DAX2 onwy */

/* ccb_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_CCB_INFO
 * AWG0:	weaw addwess of CCB compwetion awea
 * WET0:	status (success ow ewwow code)
 * WET1:	info awway
 *			- WET1[0]: CCB state
 *			- WET1[1]: dax unit
 *			- WET1[2]: queue numbew
 *			- WET1[3]: queue position
 *
 * EWWOWS:	EOK		opewation successfuw
 *		EBADAWIGN	addwess not 64B awigned
 *		ENOWADDW	WA in addwess not vawid
 *		EINVAW		CA not vawid
 *		EWOUWDBWOCK	info not avaiwabwe fow this CCB cuwwentwy, twy
 *				again
 *		ENOACCESS	guest cannot use dax
 */

#define HV_CCB_INFO                 0x35
#ifndef __ASSEMBWY__
unsigned wong sun4v_ccb_info(unsigned wong ca,
			     void *info_aww);
#endif

/* info awway byte offsets (WET1) */
#define CCB_INFO_OFFSET_CCB_STATE	0
#define CCB_INFO_OFFSET_DAX_UNIT	2
#define CCB_INFO_OFFSET_QUEUE_NUM	4
#define CCB_INFO_OFFSET_QUEUE_POS	6

/* CCB state (WET1[0]) */
#define HV_CCB_STATE_COMPWETED      0
#define HV_CCB_STATE_ENQUEUED       1
#define HV_CCB_STATE_INPWOGWESS     2
#define HV_CCB_STATE_NOTFOUND       3

/* ccb_kiww()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_CCB_KIWW
 * AWG0:	weaw addwess of CCB compwetion awea
 * WET0:	status (success ow ewwow code)
 * WET1:	CCB kiww status
 *
 * EWWOWS:	EOK		opewation successfuw
 *		EBADAWIGN	addwess not 64B awigned
 *		ENOWADDW	WA in addwess not vawid
 *		EINVAW		CA not vawid
 *		EWOUWDBWOCK	kiww not avaiwabwe fow this CCB cuwwentwy, twy
 *				again
 *		ENOACCESS	guest cannot use dax
 */

#define HV_CCB_KIWW                 0x36
#ifndef __ASSEMBWY__
unsigned wong sun4v_ccb_kiww(unsigned wong ca,
			     void *kiww_status);
#endif

/* CCB kiww status (WET1) */
#define HV_CCB_KIWW_COMPWETED       0
#define HV_CCB_KIWW_DEQUEUED        1
#define HV_CCB_KIWW_KIWWED          2
#define HV_CCB_KIWW_NOTFOUND        3

/* Time of day sewvices.
 *
 * The hypewvisow maintains the time of day on a pew-domain basis.
 * Changing the time of day in one domain does not affect the time of
 * day on any othew domain.
 *
 * Time is descwibed by a singwe unsigned 64-bit wowd which is the
 * numbew of seconds since the UNIX Epoch (00:00:00 UTC, Januawy 1,
 * 1970).
 */

/* tod_get()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TOD_GET
 * WET0:	status
 * WET1:	TOD
 * EWWOWS:	EWOUWDBWOCK	TOD wesouwce is tempowawiwy unavaiwabwe
 *		ENOTSUPPOWTED	If TOD not suppowted on this pwatfowm
 *
 * Wetuwn the cuwwent time of day.  May bwock if TOD access is
 * tempowawiwy not possibwe.
 */
#define HV_FAST_TOD_GET			0x50

#ifndef __ASSEMBWY__
unsigned wong sun4v_tod_get(unsigned wong *time);
#endif

/* tod_set()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TOD_SET
 * AWG0:	TOD
 * WET0:	status
 * EWWOWS:	EWOUWDBWOCK	TOD wesouwce is tempowawiwy unavaiwabwe
 *		ENOTSUPPOWTED	If TOD not suppowted on this pwatfowm
 *
 * The cuwwent time of day is set to the vawue specified in AWG0.  May
 * bwock if TOD access is tempowawiwy not possibwe.
 */
#define HV_FAST_TOD_SET			0x51

#ifndef __ASSEMBWY__
unsigned wong sun4v_tod_set(unsigned wong time);
#endif

/* Consowe sewvices */

/* con_getchaw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CONS_GETCHAW
 * WET0:	status
 * WET1:	chawactew
 * EWWOWS:	EWOUWDBWOCK	No chawactew avaiwabwe.
 *
 * Wetuwns a chawactew fwom the consowe device.  If no chawactew is
 * avaiwabwe then an EWOUWDBWOCK ewwow is wetuwned.  If a chawactew is
 * avaiwabwe, then the wetuwned status is EOK and the chawactew vawue
 * is in WET1.
 *
 * A viwtuaw BWEAK is wepwesented by the 64-bit vawue -1.
 *
 * A viwtuaw HUP signaw is wepwesented by the 64-bit vawue -2.
 */
#define HV_FAST_CONS_GETCHAW		0x60

/* con_putchaw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CONS_PUTCHAW
 * AWG0:	chawactew
 * WET0:	status
 * EWWOWS:	EINVAW		Iwwegaw chawactew
 *		EWOUWDBWOCK	Output buffew cuwwentwy fuww, wouwd bwock
 *
 * Send a chawactew to the consowe device.  Onwy chawactew vawues
 * between 0 and 255 may be used.  Vawues outside this wange awe
 * invawid except fow the 64-bit vawue -1 which is used to send a
 * viwtuaw BWEAK.
 */
#define HV_FAST_CONS_PUTCHAW		0x61

/* con_wead()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CONS_WEAD
 * AWG0:	buffew weaw addwess
 * AWG1:	buffew size in bytes
 * WET0:	status
 * WET1:	bytes wead ow BWEAK ow HUP
 * EWWOWS:	EWOUWDBWOCK	No chawactew avaiwabwe.
 *
 * Weads chawactews into a buffew fwom the consowe device.  If no
 * chawactew is avaiwabwe then an EWOUWDBWOCK ewwow is wetuwned.
 * If a chawactew is avaiwabwe, then the wetuwned status is EOK
 * and the numbew of bytes wead into the given buffew is pwovided
 * in WET1.
 *
 * A viwtuaw BWEAK is wepwesented by the 64-bit WET1 vawue -1.
 *
 * A viwtuaw HUP signaw is wepwesented by the 64-bit WET1 vawue -2.
 *
 * If BWEAK ow HUP awe indicated, no bytes wewe wead into buffew.
 */
#define HV_FAST_CONS_WEAD		0x62

/* con_wwite()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_CONS_WWITE
 * AWG0:	buffew weaw addwess
 * AWG1:	buffew size in bytes
 * WET0:	status
 * WET1:	bytes wwitten
 * EWWOWS:	EWOUWDBWOCK	Output buffew cuwwentwy fuww, wouwd bwock
 *
 * Send a chawactews in buffew to the consowe device.  Bweaks must be
 * sent using con_putchaw().
 */
#define HV_FAST_CONS_WWITE		0x63

#ifndef __ASSEMBWY__
wong sun4v_con_getchaw(wong *status);
wong sun4v_con_putchaw(wong c);
wong sun4v_con_wead(unsigned wong buffew,
		    unsigned wong size,
		    unsigned wong *bytes_wead);
unsigned wong sun4v_con_wwite(unsigned wong buffew,
			      unsigned wong size,
			      unsigned wong *bytes_wwitten);
#endif

/* mach_set_soft_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_SET_SOFT_STATE
 * AWG0:	softwawe state
 * AWG1:	softwawe state descwiption pointew
 * WET0:	status
 * EWWOWS:	EINVAW		softwawe state not vawid ow softwawe state
 *				descwiption is not NUWW tewminated
 *		ENOWADDW	softwawe state descwiption pointew is not a
 *				vawid weaw addwess
 *		EBADAWIGNED	softwawe state descwiption is not cowwectwy
 *				awigned
 *
 * This awwows the guest to wepowt it's soft state to the hypewvisow.  Thewe
 * awe two pwimawy components to this state.  The fiwst pawt states whethew
 * the guest softwawe is wunning ow not.  The second containts optionaw
 * detaiws specific to the softwawe.
 *
 * The softwawe state awgument is defined bewow in HV_SOFT_STATE_*, and
 * indicates whethew the guest is opewating nowmawwy ow in a twansitionaw
 * state.
 *
 * The softwawe state descwiption awgument is a weaw addwess of a data buffew
 * of size 32-bytes awigned on a 32-byte boundawy.  It is tweated as a NUWW
 * tewminated 7-bit ASCII stwing of up to 31 chawactews not incwuding the
 * NUWW tewmination.
 */
#define HV_FAST_MACH_SET_SOFT_STATE	0x70
#define  HV_SOFT_STATE_NOWMAW		 0x01
#define  HV_SOFT_STATE_TWANSITION	 0x02

#ifndef __ASSEMBWY__
unsigned wong sun4v_mach_set_soft_state(unsigned wong soft_state,
				        unsigned wong msg_stwing_wa);
#endif

/* mach_get_soft_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MACH_GET_SOFT_STATE
 * AWG0:	softwawe state descwiption pointew
 * WET0:	status
 * WET1:	softwawe state
 * EWWOWS:	ENOWADDW	softwawe state descwiption pointew is not a
 *				vawid weaw addwess
 *		EBADAWIGNED	softwawe state descwiption is not cowwectwy
 *				awigned
 *
 * Wetwieve the cuwwent vawue of the guest's softwawe state.  The wuwes
 * fow the softwawe state pointew awe the same as fow mach_set_soft_state()
 * above.
 */
#define HV_FAST_MACH_GET_SOFT_STATE	0x71

/* svc_send()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SVC_SEND
 * AWG0:	sewvice ID
 * AWG1:	buffew weaw addwess
 * AWG2:	buffew size
 * WET0:	STATUS
 * WET1:	sent_bytes
 *
 * Be cawefuw, aww output wegistews awe cwobbewed by this opewation,
 * so fow exampwe it is not possibwe to save away a vawue in %o4
 * acwoss the twap.
 */
#define HV_FAST_SVC_SEND		0x80

/* svc_wecv()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SVC_WECV
 * AWG0:	sewvice ID
 * AWG1:	buffew weaw addwess
 * AWG2:	buffew size
 * WET0:	STATUS
 * WET1:	wecv_bytes
 *
 * Be cawefuw, aww output wegistews awe cwobbewed by this opewation,
 * so fow exampwe it is not possibwe to save away a vawue in %o4
 * acwoss the twap.
 */
#define HV_FAST_SVC_WECV		0x81

/* svc_getstatus()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SVC_GETSTATUS
 * AWG0:	sewvice ID
 * WET0:	STATUS
 * WET1:	status bits
 */
#define HV_FAST_SVC_GETSTATUS		0x82

/* svc_setstatus()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SVC_SETSTATUS
 * AWG0:	sewvice ID
 * AWG1:	bits to set
 * WET0:	STATUS
 */
#define HV_FAST_SVC_SETSTATUS		0x83

/* svc_cwwstatus()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SVC_CWWSTATUS
 * AWG0:	sewvice ID
 * AWG1:	bits to cweaw
 * WET0:	STATUS
 */
#define HV_FAST_SVC_CWWSTATUS		0x84

#ifndef __ASSEMBWY__
unsigned wong sun4v_svc_send(unsigned wong svc_id,
			     unsigned wong buffew,
			     unsigned wong buffew_size,
			     unsigned wong *sent_bytes);
unsigned wong sun4v_svc_wecv(unsigned wong svc_id,
			     unsigned wong buffew,
			     unsigned wong buffew_size,
			     unsigned wong *wecv_bytes);
unsigned wong sun4v_svc_getstatus(unsigned wong svc_id,
				  unsigned wong *status_bits);
unsigned wong sun4v_svc_setstatus(unsigned wong svc_id,
				  unsigned wong status_bits);
unsigned wong sun4v_svc_cwwstatus(unsigned wong svc_id,
				  unsigned wong status_bits);
#endif

/* Twap twace sewvices.
 *
 * The hypewvisow pwovides a twap twacing capabiwity fow pwiviweged
 * code wunning on each viwtuaw CPU.  Pwiviweged code pwovides a
 * wound-wobin twap twace queue within which the hypewvisow wwites
 * 64-byte entwies detaiwing hypewpwiviweged twaps taken n behawf of
 * pwiviweged code.  This is pwovided as a debugging capabiwity fow
 * pwiviweged code.
 *
 * The twap twace contwow stwuctuwe is 64-bytes wong and pwaced at the
 * stawt (offset 0) of the twap twace buffew, and is descwibed as
 * fowwows:
 */
#ifndef __ASSEMBWY__
stwuct hv_twap_twace_contwow {
	unsigned wong		head_offset;
	unsigned wong		taiw_offset;
	unsigned wong		__wesewved[0x30 / sizeof(unsigned wong)];
};
#endif
#define HV_TWAP_TWACE_CTWW_HEAD_OFFSET	0x00
#define HV_TWAP_TWACE_CTWW_TAIW_OFFSET	0x08

/* The head offset is the offset of the most wecentwy compweted entwy
 * in the twap-twace buffew.  The taiw offset is the offset of the
 * next entwy to be wwitten.  The contwow stwuctuwe is owned and
 * modified by the hypewvisow.  A guest may not modify the contwow
 * stwuctuwe contents.  Attempts to do so wiww wesuwt in undefined
 * behaviow fow the guest.
 *
 * Each twap twace buffew entwy is waid out as fowwows:
 */
#ifndef __ASSEMBWY__
stwuct hv_twap_twace_entwy {
	unsigned chaw	type;		/* Hypewvisow ow guest entwy?	*/
	unsigned chaw	hpstate;	/* Hypew-pwiviweged state	*/
	unsigned chaw	tw;		/* Twap wevew			*/
	unsigned chaw	gw;		/* Gwobaw wegistew wevew	*/
	unsigned showt	tt;		/* Twap type			*/
	unsigned showt	tag;		/* Extended twap identifiew	*/
	unsigned wong	tstate;		/* Twap state			*/
	unsigned wong	tick;		/* Tick				*/
	unsigned wong	tpc;		/* Twap PC			*/
	unsigned wong	f1;		/* Entwy specific		*/
	unsigned wong	f2;		/* Entwy specific		*/
	unsigned wong	f3;		/* Entwy specific		*/
	unsigned wong	f4;		/* Entwy specific		*/
};
#endif
#define HV_TWAP_TWACE_ENTWY_TYPE	0x00
#define HV_TWAP_TWACE_ENTWY_HPSTATE	0x01
#define HV_TWAP_TWACE_ENTWY_TW		0x02
#define HV_TWAP_TWACE_ENTWY_GW		0x03
#define HV_TWAP_TWACE_ENTWY_TT		0x04
#define HV_TWAP_TWACE_ENTWY_TAG		0x06
#define HV_TWAP_TWACE_ENTWY_TSTATE	0x08
#define HV_TWAP_TWACE_ENTWY_TICK	0x10
#define HV_TWAP_TWACE_ENTWY_TPC		0x18
#define HV_TWAP_TWACE_ENTWY_F1		0x20
#define HV_TWAP_TWACE_ENTWY_F2		0x28
#define HV_TWAP_TWACE_ENTWY_F3		0x30
#define HV_TWAP_TWACE_ENTWY_F4		0x38

/* The type fiewd is encoded as fowwows.  */
#define HV_TWAP_TYPE_UNDEF		0x00 /* Entwy content undefined     */
#define HV_TWAP_TYPE_HV			0x01 /* Hypewvisow twap entwy       */
#define HV_TWAP_TYPE_GUEST		0xff /* Added via ttwace_addentwy() */

/* ttwace_buf_conf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TTWACE_BUF_CONF
 * AWG0:	weaw addwess
 * AWG1:	numbew of entwies
 * WET0:	status
 * WET1:	numbew of entwies
 * EWWOWS:	ENOWADDW	Invawid weaw addwess
 *		EINVAW		Size is too smaww
 *		EBADAWIGN	Weaw addwess not awigned on 64-byte boundawy
 *
 * Wequests hypewvisow twap twacing and decwawes a viwtuaw CPU's twap
 * twace buffew to the hypewvisow.  The weaw addwess suppwies the weaw
 * base addwess of the twap twace queue and must be 64-byte awigned.
 * Specifying a vawue of 0 fow the numbew of entwies disabwes twap
 * twacing fow the cawwing viwtuaw CPU.  The buffew awwocated must be
 * sized fow a powew of two numbew of 64-byte twap twace entwies pwus
 * an initiaw 64-byte contwow stwuctuwe.
 *
 * This may be invoked any numbew of times so that a viwtuaw CPU may
 * wewocate a twap twace buffew ow cweate "snapshots" of infowmation.
 *
 * If the weaw addwess is iwwegaw ow badwy awigned, then twap twacing
 * is disabwed and an ewwow is wetuwned.
 *
 * Upon faiwuwe with EINVAW, this sewvice caww wetuwns in WET1 the
 * minimum numbew of buffew entwies wequiwed.  Upon othew faiwuwes
 * WET1 is undefined.
 */
#define HV_FAST_TTWACE_BUF_CONF		0x90

/* ttwace_buf_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TTWACE_BUF_INFO
 * WET0:	status
 * WET1:	weaw addwess
 * WET2:	size
 * EWWOWS:	None defined.
 *
 * Wetuwns the size and wocation of the pweviouswy decwawed twap-twace
 * buffew.  In the event that no buffew was pweviouswy defined, ow the
 * buffew is disabwed, this caww wiww wetuwn a size of zewo bytes.
 */
#define HV_FAST_TTWACE_BUF_INFO		0x91

/* ttwace_enabwe()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TTWACE_ENABWE
 * AWG0:	enabwe
 * WET0:	status
 * WET1:	pwevious enabwe state
 * EWWOWS:	EINVAW		No twap twace buffew cuwwentwy defined
 *
 * Enabwe ow disabwe twap twacing, and wetuwn the pwevious enabwed
 * state in WET1.  Futuwe systems may define vawious fwags fow the
 * enabwe awgument (AWG0), fow the moment a guest shouwd pass
 * "(uint64_t) -1" to enabwe, and "(uint64_t) 0" to disabwe aww
 * twacing - which wiww ensuwe futuwe compatibiwity.
 */
#define HV_FAST_TTWACE_ENABWE		0x92

/* ttwace_fweeze()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_TTWACE_FWEEZE
 * AWG0:	fweeze
 * WET0:	status
 * WET1:	pwevious fweeze state
 * EWWOWS:	EINVAW		No twap twace buffew cuwwentwy defined
 *
 * Fweeze ow unfweeze twap twacing, wetuwning the pwevious fweeze
 * state in WET1.  A guest shouwd pass a non-zewo vawue to fweeze and
 * a zewo vawue to unfweeze aww twacing.  The wetuwned pwevious state
 * is 0 fow not fwozen and 1 fow fwozen.
 */
#define HV_FAST_TTWACE_FWEEZE		0x93

/* ttwace_addentwy()
 * TWAP:	HV_TTWACE_ADDENTWY_TWAP
 * AWG0:	tag (16-bits)
 * AWG1:	data wowd 0
 * AWG2:	data wowd 1
 * AWG3:	data wowd 2
 * AWG4:	data wowd 3
 * WET0:	status
 * EWWOWS:	EINVAW		No twap twace buffew cuwwentwy defined
 *
 * Add an entwy to the twap twace buffew.  Upon wetuwn onwy AWG0/WET0
 * is modified - none of the othew wegistews howding awguments awe
 * vowatiwe acwoss this hypewvisow sewvice.
 */

/* Cowe dump sewvices.
 *
 * Since the hypewvisow viwauwizes and thus obscuwes a wot of the
 * physicaw machine wayout and state, twaditionaw OS cwash dumps can
 * be difficuwt to diagnose especiawwy when the pwobwem is a
 * configuwation ewwow of some sowt.
 *
 * The dump sewvices pwovide an opaque buffew into which the
 * hypewvisow can pwace it's intewnaw state in owdew to assist in
 * debugging such situations.  The contents awe opaque and extwemewy
 * pwatfowm and hypewvisow impwementation specific.  The guest, duwing
 * a cowe dump, wequests that the hypewvisow update any infowmation in
 * the dump buffew in pwepawation to being dumped as pawt of the
 * domain's memowy image.
 */

/* dump_buf_update()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_DUMP_BUF_UPDATE
 * AWG0:	weaw addwess
 * AWG1:	size
 * WET0:	status
 * WET1:	wequiwed size of dump buffew
 * EWWOWS:	ENOWADDW	Invawid weaw addwess
 *		EBADAWIGN	Weaw addwess is not awigned on a 64-byte
 *				boundawy
 *		EINVAW		Size is non-zewo but wess than minimum size
 *				wequiwed
 *		ENOTSUPPOWTED	Opewation not suppowted on cuwwent wogicaw
 *				domain
 *
 * Decwawe a domain dump buffew to the hypewvisow.  The weaw addwess
 * pwovided fow the domain dump buffew must be 64-byte awigned.  The
 * size specifies the size of the dump buffew and may be wawgew than
 * the minimum size specified in the machine descwiption.  The
 * hypewvisow wiww fiww the dump buffew with opaque data.
 *
 * Note: A guest may ewect to incwude dump buffew contents as pawt of a cwash
 *       dump to assist with debugging.  This function may be cawwed any numbew
 *       of times so that a guest may wewocate a dump buffew, ow cweate
 *       "snapshots" of any dump-buffew infowmation.  Each caww to
 *       dump_buf_update() atomicawwy decwawes the new dump buffew to the
 *       hypewvisow.
 *
 * A specified size of 0 unconfiguwes the dump buffew.  If the weaw
 * addwess is iwwegaw ow badwy awigned, then any cuwwentwy active dump
 * buffew is disabwed and an ewwow is wetuwned.
 *
 * In the event that the caww faiws with EINVAW, WET1 contains the
 * minimum size wequiwes by the hypewvisow fow a vawid dump buffew.
 */
#define HV_FAST_DUMP_BUF_UPDATE		0x94

/* dump_buf_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_DUMP_BUF_INFO
 * WET0:	status
 * WET1:	weaw addwess of cuwwent dump buffew
 * WET2:	size of cuwwent dump buffew
 * EWWOWS:	No ewwows defined.
 *
 * Wetuwn the cuwwentwy configuwes dump buffew descwiption.  A
 * wetuwned size of 0 bytes indicates an undefined dump buffew.  In
 * this case the wetuwn addwess in WET1 is undefined.
 */
#define HV_FAST_DUMP_BUF_INFO		0x95

/* Device intewwupt sewvices.
 *
 * Device intewwupts awe awwocated to system bus bwidges by the hypewvisow,
 * and descwibed to OBP in the machine descwiption.  OBP then descwibes
 * these intewwupts to the OS via pwopewties in the device twee.
 *
 * Tewminowogy:
 *
 *	cpuid		Unique opaque vawue which wepwesents a tawget cpu.
 *
 *	devhandwe	Device handwe.  It uniquewy identifies a device, and
 *			consistes of the wowew 28-bits of the hi-ceww of the
 *			fiwst entwy of the device's "weg" pwopewty in the
 *			OBP device twee.
 *
 *	devino		Device intewwupt numbew.  Specifies the wewative
 *			intewwupt numbew within the device.  The unique
 *			combination of devhandwe and devino awe used to
 *			identify a specific device intewwupt.
 *
 *			Note: The devino vawue is the same as the vawues in the
 *			      "intewwupts" pwopewty ow "intewwupt-map" pwopewty
 *			      in the OBP device twee fow that device.
 *
 *	sysino		System intewwupt numbew.  A 64-bit unsigned intewgew
 *			wepwesenting a unique intewwupt within a viwtuaw
 *			machine.
 *
 *	intw_state	A fwag wepwesenting the intewwupt state fow a given
 *			sysino.  The state vawues awe defined bewow.
 *
 *	intw_enabwed	A fwag wepwesenting the 'enabwed' state fow a given
 *			sysino.  The enabwe vawues awe defined bewow.
 */

#define HV_INTW_STATE_IDWE		0 /* Nothing pending */
#define HV_INTW_STATE_WECEIVED		1 /* Intewwupt weceived by hawdwawe */
#define HV_INTW_STATE_DEWIVEWED		2 /* Intewwupt dewivewed to queue */

#define HV_INTW_DISABWED		0 /* sysino not enabwed */
#define HV_INTW_ENABWED			1 /* sysino enabwed */

/* intw_devino_to_sysino()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_DEVINO2SYSINO
 * AWG0:	devhandwe
 * AWG1:	devino
 * WET0:	status
 * WET1:	sysino
 * EWWOWS:	EINVAW		Invawid devhandwe/devino
 *
 * Convewts a device specific intewwupt numbew of the given
 * devhandwe/devino into a system specific ino (sysino).
 */
#define HV_FAST_INTW_DEVINO2SYSINO	0xa0

#ifndef __ASSEMBWY__
unsigned wong sun4v_devino_to_sysino(unsigned wong devhandwe,
				     unsigned wong devino);
#endif

/* intw_getenabwed()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_GETENABWED
 * AWG0:	sysino
 * WET0:	status
 * WET1:	intw_enabwed (HV_INTW_{DISABWED,ENABWED})
 * EWWOWS:	EINVAW		Invawid sysino
 *
 * Wetuwns intewwupt enabwed state in WET1 fow the intewwupt defined
 * by the given sysino.
 */
#define HV_FAST_INTW_GETENABWED		0xa1

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_getenabwed(unsigned wong sysino);
#endif

/* intw_setenabwed()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_SETENABWED
 * AWG0:	sysino
 * AWG1:	intw_enabwed (HV_INTW_{DISABWED,ENABWED})
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid sysino ow intw_enabwed vawue
 *
 * Set the 'enabwed' state of the intewwupt sysino.
 */
#define HV_FAST_INTW_SETENABWED		0xa2

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_setenabwed(unsigned wong sysino,
				    unsigned wong intw_enabwed);
#endif

/* intw_getstate()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_GETSTATE
 * AWG0:	sysino
 * WET0:	status
 * WET1:	intw_state (HV_INTW_STATE_*)
 * EWWOWS:	EINVAW		Invawid sysino
 *
 * Wetuwns cuwwent state of the intewwupt defined by the given sysino.
 */
#define HV_FAST_INTW_GETSTATE		0xa3

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_getstate(unsigned wong sysino);
#endif

/* intw_setstate()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_SETSTATE
 * AWG0:	sysino
 * AWG1:	intw_state (HV_INTW_STATE_*)
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid sysino ow intw_state vawue
 *
 * Sets the cuwwent state of the intewwupt descwibed by the given sysino
 * vawue.
 *
 * Note: Setting the state to HV_INTW_STATE_IDWE cweaws any pending
 *       intewwupt fow sysino.
 */
#define HV_FAST_INTW_SETSTATE		0xa4

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_setstate(unsigned wong sysino, unsigned wong intw_state);
#endif

/* intw_gettawget()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_GETTAWGET
 * AWG0:	sysino
 * WET0:	status
 * WET1:	cpuid
 * EWWOWS:	EINVAW		Invawid sysino
 *
 * Wetuwns CPU that is the cuwwent tawget of the intewwupt defined by
 * the given sysino.  The CPU vawue wetuwned is undefined if the tawget
 * has not been set via intw_settawget().
 */
#define HV_FAST_INTW_GETTAWGET		0xa5

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_gettawget(unsigned wong sysino);
#endif

/* intw_settawget()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_INTW_SETTAWGET
 * AWG0:	sysino
 * AWG1:	cpuid
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid sysino
 *		ENOCPU		Invawid cpuid
 *
 * Set the tawget CPU fow the intewwupt defined by the given sysino.
 */
#define HV_FAST_INTW_SETTAWGET		0xa6

#ifndef __ASSEMBWY__
unsigned wong sun4v_intw_settawget(unsigned wong sysino, unsigned wong cpuid);
#endif

/* vintw_get_cookie()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_GET_COOKIE
 * AWG0:	device handwe
 * AWG1:	device ino
 * WET0:	status
 * WET1:	cookie
 */
#define HV_FAST_VINTW_GET_COOKIE	0xa7

/* vintw_set_cookie()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_SET_COOKIE
 * AWG0:	device handwe
 * AWG1:	device ino
 * AWG2:	cookie
 * WET0:	status
 */
#define HV_FAST_VINTW_SET_COOKIE	0xa8

/* vintw_get_vawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_GET_VAWID
 * AWG0:	device handwe
 * AWG1:	device ino
 * WET0:	status
 * WET1:	vawid state
 */
#define HV_FAST_VINTW_GET_VAWID		0xa9

/* vintw_set_vawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_SET_VAWID
 * AWG0:	device handwe
 * AWG1:	device ino
 * AWG2:	vawid state
 * WET0:	status
 */
#define HV_FAST_VINTW_SET_VAWID		0xaa

/* vintw_get_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_GET_STATE
 * AWG0:	device handwe
 * AWG1:	device ino
 * WET0:	status
 * WET1:	state
 */
#define HV_FAST_VINTW_GET_STATE		0xab

/* vintw_set_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_SET_STATE
 * AWG0:	device handwe
 * AWG1:	device ino
 * AWG2:	state
 * WET0:	status
 */
#define HV_FAST_VINTW_SET_STATE		0xac

/* vintw_get_tawget()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_GET_TAWGET
 * AWG0:	device handwe
 * AWG1:	device ino
 * WET0:	status
 * WET1:	cpuid
 */
#define HV_FAST_VINTW_GET_TAWGET	0xad

/* vintw_set_tawget()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_VINTW_SET_TAWGET
 * AWG0:	device handwe
 * AWG1:	device ino
 * AWG2:	cpuid
 * WET0:	status
 */
#define HV_FAST_VINTW_SET_TAWGET	0xae

#ifndef __ASSEMBWY__
unsigned wong sun4v_vintw_get_cookie(unsigned wong dev_handwe,
				     unsigned wong dev_ino,
				     unsigned wong *cookie);
unsigned wong sun4v_vintw_set_cookie(unsigned wong dev_handwe,
				     unsigned wong dev_ino,
				     unsigned wong cookie);
unsigned wong sun4v_vintw_get_vawid(unsigned wong dev_handwe,
				    unsigned wong dev_ino,
				    unsigned wong *vawid);
unsigned wong sun4v_vintw_set_vawid(unsigned wong dev_handwe,
				    unsigned wong dev_ino,
				    unsigned wong vawid);
unsigned wong sun4v_vintw_get_state(unsigned wong dev_handwe,
				    unsigned wong dev_ino,
				    unsigned wong *state);
unsigned wong sun4v_vintw_set_state(unsigned wong dev_handwe,
				    unsigned wong dev_ino,
				    unsigned wong state);
unsigned wong sun4v_vintw_get_tawget(unsigned wong dev_handwe,
				     unsigned wong dev_ino,
				     unsigned wong *cpuid);
unsigned wong sun4v_vintw_set_tawget(unsigned wong dev_handwe,
				     unsigned wong dev_ino,
				     unsigned wong cpuid);
#endif

/* PCI IO sewvices.
 *
 * See the tewminowogy descwiptions in the device intewwupt sewvices
 * section above as those appwy hewe too.  Hewe awe tewminowogy
 * definitions specific to these PCI IO sewvices:
 *
 *	tsbnum		TSB numbew.  Indentifies which io-tsb is used.
 *			Fow this vewsion of the specification, tsbnum
 *			must be zewo.
 *
 *	tsbindex	TSB index.  Identifies which entwy in the TSB
 *			is used.  The fiwst entwy is zewo.
 *
 *	tsbid		A 64-bit awigned data stwuctuwe which contains
 *			a tsbnum and a tsbindex.  Bits 63:32 contain the
 *			tsbnum and bits 31:00 contain the tsbindex.
 *
 *			Use the HV_PCI_TSBID() macwo to constwuct such
 * 			vawues.
 *
 *	io_attwibutes	IO attwibutes fow IOMMU mappings.  One of mowe
 *			of the attwitbute bits awe stowes in a 64-bit
 *			vawue.  The vawues awe defined bewow.
 *
 *	w_addw		64-bit weaw addwess
 *
 *	pci_device	PCI device addwess.  A PCI device addwess identifies
 *			a specific device on a specific PCI bus segment.
 *			A PCI device addwess ia a 32-bit unsigned integew
 *			with the fowwowing fowmat:
 *
 *				00000000.bbbbbbbb.dddddfff.00000000
 *
 *			Use the HV_PCI_DEVICE_BUIWD() macwo to constwuct
 *			such vawues.
 *
 *	pci_config_offset
 *			PCI configuweation space offset.  Fow conventionaw
 *			PCI a vawue between 0 and 255.  Fow extended
 *			configuwation space, a vawue between 0 and 4095.
 *
 *			Note: Fow PCI configuwation space accesses, the offset
 *			      must be awigned to the access size.
 *
 *	ewwow_fwag	A wetuwn vawue which specifies if the action succeeded
 *			ow faiwed.  0 means no ewwow, non-0 means some ewwow
 *			occuwwed whiwe pewfowming the sewvice.
 *
 *	io_sync_diwection
 *			Diwection definition fow pci_dma_sync(), defined
 *			bewow in HV_PCI_SYNC_*.
 *
 *	io_page_wist	A wist of io_page_addwesses, an io_page_addwess is
 *			a weaw addwess.
 *
 *	io_page_wist_p	A pointew to an io_page_wist.
 *
 *	"size based byte swap" - Some functions do size based byte swapping
 *				 which awwows sw to access pointews and
 *				 countews in native fowm when the pwocessow
 *				 opewates in a diffewent endianness than the
 *				 IO bus.  Size-based byte swapping convewts a
 *				 muwti-byte fiewd between big-endian and
 *				 wittwe-endian fowmat.
 */

#define HV_PCI_MAP_ATTW_WEAD		0x01
#define HV_PCI_MAP_ATTW_WWITE		0x02
#define HV_PCI_MAP_ATTW_WEWAXED_OWDEW	0x04

#define HV_PCI_DEVICE_BUIWD(b,d,f)	\
	((((b) & 0xff) << 16) | \
	 (((d) & 0x1f) << 11) | \
	 (((f) & 0x07) <<  8))

#define HV_PCI_TSBID(__tsb_num, __tsb_index) \
	((((u64)(__tsb_num)) << 32UW) | ((u64)(__tsb_index)))

#define HV_PCI_SYNC_FOW_DEVICE		0x01
#define HV_PCI_SYNC_FOW_CPU		0x02

/* pci_iommu_map()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_MAP
 * AWG0:	devhandwe
 * AWG1:	tsbid
 * AWG2:	#ttes
 * AWG3:	io_attwibutes
 * AWG4:	io_page_wist_p
 * WET0:	status
 * WET1:	#ttes mapped
 * EWWOWS:	EINVAW		Invawid devhandwe/tsbnum/tsbindex/io_attwibutes
 *		EBADAWIGN	Impwopewwy awigned weaw addwess
 *		ENOWADDW	Invawid weaw addwess
 *
 * Cweate IOMMU mappings in the sun4v device defined by the given
 * devhandwe.  The mappings awe cweated in the TSB defined by the
 * tsbnum component of the given tsbid.  The fiwst mapping is cweated
 * in the TSB i ndex defined by the tsbindex component of the given tsbid.
 * The caww cweates up to #ttes mappings, the fiwst one at tsbnum, tsbindex,
 * the second at tsbnum, tsbindex + 1, etc.
 *
 * Aww mappings awe cweated with the attwibutes defined by the io_attwibutes
 * awgument.  The page mapping addwesses awe descwibed in the io_page_wist
 * defined by the given io_page_wist_p, which is a pointew to the io_page_wist.
 * The fiwst entwy in the io_page_wist is the addwess fow the fiwst iotte, the
 * 2nd fow the 2nd iotte, and so on.
 *
 * Each io_page_addwess in the io_page_wist must be appwopwiatewy awigned.
 * #ttes must be gweatew than zewo.  Fow this vewsion of the spec, the tsbnum
 * component of the given tsbid must be zewo.
 *
 * Wetuwns the actuaw numbew of mappings cweates, which may be wess than
 * ow equaw to the awgument #ttes.  If the function wetuwns a vawue which
 * is wess than the #ttes, the cawwew may continus to caww the function with
 * an updated tsbid, #ttes, io_page_wist_p awguments untiw aww pages awe
 * mapped.
 *
 * Note: This function does not impwy an iotte cache fwush.  The guest must
 *       demap an entwy befowe we-mapping it.
 */
#define HV_FAST_PCI_IOMMU_MAP		0xb0

/* pci_iommu_demap()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_DEMAP
 * AWG0:	devhandwe
 * AWG1:	tsbid
 * AWG2:	#ttes
 * WET0:	status
 * WET1:	#ttes demapped
 * EWWOWS:	EINVAW		Invawid devhandwe/tsbnum/tsbindex
 *
 * Demap and fwush IOMMU mappings in the device defined by the given
 * devhandwe.  Demaps up to #ttes entwies in the TSB defined by the tsbnum
 * component of the given tsbid, stawting at the TSB index defined by the
 * tsbindex component of the given tsbid.
 *
 * Fow this vewsion of the spec, the tsbnum of the given tsbid must be zewo.
 * #ttes must be gweatew than zewo.
 *
 * Wetuwns the actuaw numbew of ttes demapped, which may be wess than ow equaw
 * to the awgument #ttes.  If #ttes demapped is wess than #ttes, the cawwew
 * may continue to caww this function with updated tsbid and #ttes awguments
 * untiw aww pages awe demapped.
 *
 * Note: Entwies do not have to be mapped to be demapped.  A demap of an
 *       unmapped page wiww fwush the entwy fwom the tte cache.
 */
#define HV_FAST_PCI_IOMMU_DEMAP		0xb1

/* pci_iommu_getmap()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_GETMAP
 * AWG0:	devhandwe
 * AWG1:	tsbid
 * WET0:	status
 * WET1:	io_attwibutes
 * WET2:	weaw addwess
 * EWWOWS:	EINVAW		Invawid devhandwe/tsbnum/tsbindex
 *		ENOMAP		Mapping is not vawid, no twanswation exists
 *
 * Wead and wetuwn the mapping in the device descwibed by the given devhandwe
 * and tsbid.  If successfuw, the io_attwibutes shaww be wetuwned in WET1
 * and the page addwess of the mapping shaww be wetuwned in WET2.
 *
 * Fow this vewsion of the spec, the tsbnum component of the given tsbid
 * must be zewo.
 */
#define HV_FAST_PCI_IOMMU_GETMAP	0xb2

/* pci_iommu_getbypass()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOMMU_GETBYPASS
 * AWG0:	devhandwe
 * AWG1:	weaw addwess
 * AWG2:	io_attwibutes
 * WET0:	status
 * WET1:	io_addw
 * EWWOWS:	EINVAW		Invawid devhandwe/io_attwibutes
 *		ENOWADDW	Invawid weaw addwess
 *		ENOTSUPPOWTED	Function not suppowted in this impwementation.
 *
 * Cweate a "speciaw" mapping in the device descwibed by the given devhandwe,
 * fow the given weaw addwess and attwibutes.  Wetuwn the IO addwess in WET1
 * if successfuw.
 */
#define HV_FAST_PCI_IOMMU_GETBYPASS	0xb3

/* pci_config_get()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_CONFIG_GET
 * AWG0:	devhandwe
 * AWG1:	pci_device
 * AWG2:	pci_config_offset
 * AWG3:	size
 * WET0:	status
 * WET1:	ewwow_fwag
 * WET2:	data
 * EWWOWS:	EINVAW		Invawid devhandwe/pci_device/offset/size
 *		EBADAWIGN	pci_config_offset not size awigned
 *		ENOACCESS	Access to this offset is not pewmitted
 *
 * Wead PCI configuwation space fow the adaptew descwibed by the given
 * devhandwe.  Wead size (1, 2, ow 4) bytes of data fwom the given
 * pci_device, at pci_config_offset fwom the beginning of the device's
 * configuwation space.  If thewe was no ewwow, WET1 is set to zewo and
 * WET2 is set to the data wead.  Insignificant bits in WET2 awe not
 * guawanteed to have any specific vawue and thewefowe must be ignowed.
 *
 * The data wetuwned in WET2 is size based byte swapped.
 *
 * If an ewwow occuws duwing the wead, set WET1 to a non-zewo vawue.  The
 * given pci_config_offset must be 'size' awigned.
 */
#define HV_FAST_PCI_CONFIG_GET		0xb4

/* pci_config_put()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_CONFIG_PUT
 * AWG0:	devhandwe
 * AWG1:	pci_device
 * AWG2:	pci_config_offset
 * AWG3:	size
 * AWG4:	data
 * WET0:	status
 * WET1:	ewwow_fwag
 * EWWOWS:	EINVAW		Invawid devhandwe/pci_device/offset/size
 *		EBADAWIGN	pci_config_offset not size awigned
 *		ENOACCESS	Access to this offset is not pewmitted
 *
 * Wwite PCI configuwation space fow the adaptew descwibed by the given
 * devhandwe.  Wwite size (1, 2, ow 4) bytes of data in a singwe opewation,
 * at pci_config_offset fwom the beginning of the device's configuwation
 * space.  The data awgument contains the data to be wwitten to configuwation
 * space.  Pwiow to wwiting, the data is size based byte swapped.
 *
 * If an ewwow occuws duwing the wwite access, do not genewate an ewwow
 * wepowt, do set WET1 to a non-zewo vawue.  Othewwise WET1 is zewo.
 * The given pci_config_offset must be 'size' awigned.
 *
 * This function is pewmitted to wead fwom offset zewo in the configuwation
 * space descwibed by the given pci_device if necessawy to ensuwe that the
 * wwite access to config space compwetes.
 */
#define HV_FAST_PCI_CONFIG_PUT		0xb5

/* pci_peek()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_PEEK
 * AWG0:	devhandwe
 * AWG1:	weaw addwess
 * AWG2:	size
 * WET0:	status
 * WET1:	ewwow_fwag
 * WET2:	data
 * EWWOWS:	EINVAW		Invawid devhandwe ow size
 *		EBADAWIGN	Impwopewwy awigned weaw addwess
 *		ENOWADDW	Bad weaw addwess
 *		ENOACCESS	Guest access pwohibited
 *
 * Attempt to wead the IO addwess given by the given devhandwe, weaw addwess,
 * and size.  Size must be 1, 2, 4, ow 8.  The wead is pewfowmed as a singwe
 * access opewation using the given size.  If an ewwow occuws when weading
 * fwom the given wocation, do not genewate an ewwow wepowt, but wetuwn a
 * non-zewo vawue in WET1.  If the wead was successfuw, wetuwn zewo in WET1
 * and wetuwn the actuaw data wead in WET2.  The data wetuwned is size based
 * byte swapped.
 *
 * Non-significant bits in WET2 awe not guawanteed to have any specific vawue
 * and thewefowe must be ignowed.  If WET1 is wetuwned as non-zewo, the data
 * vawue is not guawanteed to have any specific vawue and shouwd be ignowed.
 *
 * The cawwew must have pewmission to wead fwom the given devhandwe, weaw
 * addwess, which must be an IO addwess.  The awgument weaw addwess must be a
 * size awigned addwess.
 *
 * The hypewvisow impwementation of this function must bwock access to any
 * IO addwess that the guest does not have expwicit pewmission to access.
 */
#define HV_FAST_PCI_PEEK		0xb6

/* pci_poke()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_POKE
 * AWG0:	devhandwe
 * AWG1:	weaw addwess
 * AWG2:	size
 * AWG3:	data
 * AWG4:	pci_device
 * WET0:	status
 * WET1:	ewwow_fwag
 * EWWOWS:	EINVAW		Invawid devhandwe, size, ow pci_device
 *		EBADAWIGN	Impwopewwy awigned weaw addwess
 *		ENOWADDW	Bad weaw addwess
 *		ENOACCESS	Guest access pwohibited
 *		ENOTSUPPOWTED	Function is not suppowted by impwementation
 *
 * Attempt to wwite data to the IO addwess given by the given devhandwe,
 * weaw addwess, and size.  Size must be 1, 2, 4, ow 8.  The wwite is
 * pewfowmed as a singwe access opewation using the given size. Pwiow to
 * wwiting the data is size based swapped.
 *
 * If an ewwow occuws when wwiting to the given wocation, do not genewate an
 * ewwow wepowt, but wetuwn a non-zewo vawue in WET1.  If the wwite was
 * successfuw, wetuwn zewo in WET1.
 *
 * pci_device descwibes the configuwation addwess of the device being
 * wwitten to.  The impwementation may safewy wead fwom offset 0 with
 * the configuwation space of the device descwibed by devhandwe and
 * pci_device in owdew to guawantee that the wwite powtion of the opewation
 * compwetes
 *
 * Any ewwow that occuws due to the wead shaww be wepowted using the nowmaw
 * ewwow wepowting mechanisms .. the wead ewwow is not suppwessed.
 *
 * The cawwew must have pewmission to wwite to the given devhandwe, weaw
 * addwess, which must be an IO addwess.  The awgument weaw addwess must be a
 * size awigned addwess.  The cawwew must have pewmission to wead fwom
 * the given devhandwe, pci_device cofiguwation space offset 0.
 *
 * The hypewvisow impwementation of this function must bwock access to any
 * IO addwess that the guest does not have expwicit pewmission to access.
 */
#define HV_FAST_PCI_POKE		0xb7

/* pci_dma_sync()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_DMA_SYNC
 * AWG0:	devhandwe
 * AWG1:	weaw addwess
 * AWG2:	size
 * AWG3:	io_sync_diwection
 * WET0:	status
 * WET1:	#synced
 * EWWOWS:	EINVAW		Invawid devhandwe ow io_sync_diwection
 *		ENOWADDW	Bad weaw addwess
 *
 * Synchwonize a memowy wegion descwibed by the given weaw addwess and size,
 * fow the device defined by the given devhandwe using the diwection(s)
 * defined by the given io_sync_diwection.  The awgument size is the size of
 * the memowy wegion in bytes.
 *
 * Wetuwn the actuaw numbew of bytes synchwonized in the wetuwn vawue #synced,
 * which may be wess than ow equaw to the awgument size.  If the wetuwn
 * vawue #synced is wess than size, the cawwew must continue to caww this
 * function with updated weaw addwess and size awguments untiw the entiwe
 * memowy wegion is synchwonized.
 */
#define HV_FAST_PCI_DMA_SYNC		0xb8

/* PCI MSI sewvices.  */

#define HV_MSITYPE_MSI32		0x00
#define HV_MSITYPE_MSI64		0x01

#define HV_MSIQSTATE_IDWE		0x00
#define HV_MSIQSTATE_EWWOW		0x01

#define HV_MSIQ_INVAWID			0x00
#define HV_MSIQ_VAWID			0x01

#define HV_MSISTATE_IDWE		0x00
#define HV_MSISTATE_DEWIVEWED		0x01

#define HV_MSIVAWID_INVAWID		0x00
#define HV_MSIVAWID_VAWID		0x01

#define HV_PCIE_MSGTYPE_PME_MSG		0x18
#define HV_PCIE_MSGTYPE_PME_ACK_MSG	0x1b
#define HV_PCIE_MSGTYPE_COWW_MSG	0x30
#define HV_PCIE_MSGTYPE_NONFATAW_MSG	0x31
#define HV_PCIE_MSGTYPE_FATAW_MSG	0x33

#define HV_MSG_INVAWID			0x00
#define HV_MSG_VAWID			0x01

/* pci_msiq_conf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_CONF
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * AWG2:	weaw addwess
 * AWG3:	numbew of entwies
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe, msiqid ow nentwies
 *		EBADAWIGN	Impwopewwy awigned weaw addwess
 *		ENOWADDW	Bad weaw addwess
 *
 * Configuwe the MSI queue given by the devhandwe and msiqid awguments,
 * and to be pwaced at the given weaw addwess and be of the given
 * numbew of entwies.  The weaw addwess must be awigned exactwy to match
 * the queue size.  Each queue entwy is 64-bytes wong, so f.e. a 32 entwy
 * queue must be awigned on a 2048 byte weaw addwess boundawy.  The MSI-EQ
 * Head and Taiw awe initiawized so that the MSI-EQ is 'empty'.
 *
 * Impwementation Note: Cewtain impwementations have fixed sized queues.  In
 *                      that case, numbew of entwies must contain the cowwect
 *                      vawue.
 */
#define HV_FAST_PCI_MSIQ_CONF		0xc0

/* pci_msiq_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_INFO
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * WET0:	status
 * WET1:	weaw addwess
 * WET2:	numbew of entwies
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid
 *
 * Wetuwn the configuwation infowmation fow the MSI queue descwibed
 * by the given devhandwe and msiqid.  The base addwess of the queue
 * is wetuwned in AWG1 and the numbew of entwies is wetuwned in AWG2.
 * If the queue is unconfiguwed, the weaw addwess is undefined and the
 * numbew of entwies wiww be wetuwned as zewo.
 */
#define HV_FAST_PCI_MSIQ_INFO		0xc1

/* pci_msiq_getvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETVAWID
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * WET0:	status
 * WET1:	msiqvawid	(HV_MSIQ_VAWID ow HV_MSIQ_INVAWID)
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid
 *
 * Get the vawid state of the MSI-EQ descwibed by the given devhandwe and
 * msiqid.
 */
#define HV_FAST_PCI_MSIQ_GETVAWID	0xc2

/* pci_msiq_setvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_SETVAWID
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * AWG2:	msiqvawid	(HV_MSIQ_VAWID ow HV_MSIQ_INVAWID)
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid ow msiqvawid
 *				vawue ow MSI EQ is uninitiawized
 *
 * Set the vawid state of the MSI-EQ descwibed by the given devhandwe and
 * msiqid to the given msiqvawid.
 */
#define HV_FAST_PCI_MSIQ_SETVAWID	0xc3

/* pci_msiq_getstate()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETSTATE
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * WET0:	status
 * WET1:	msiqstate	(HV_MSIQSTATE_IDWE ow HV_MSIQSTATE_EWWOW)
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid
 *
 * Get the state of the MSI-EQ descwibed by the given devhandwe and
 * msiqid.
 */
#define HV_FAST_PCI_MSIQ_GETSTATE	0xc4

/* pci_msiq_getvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETVAWID
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * AWG2:	msiqstate	(HV_MSIQSTATE_IDWE ow HV_MSIQSTATE_EWWOW)
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid ow msiqstate
 *				vawue ow MSI EQ is uninitiawized
 *
 * Set the state of the MSI-EQ descwibed by the given devhandwe and
 * msiqid to the given msiqvawid.
 */
#define HV_FAST_PCI_MSIQ_SETSTATE	0xc5

/* pci_msiq_gethead()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETHEAD
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * WET0:	status
 * WET1:	msiqhead
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid
 *
 * Get the cuwwent MSI EQ queue head fow the MSI-EQ descwibed by the
 * given devhandwe and msiqid.
 */
#define HV_FAST_PCI_MSIQ_GETHEAD	0xc6

/* pci_msiq_sethead()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_SETHEAD
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * AWG2:	msiqhead
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid ow msiqhead,
 *				ow MSI EQ is uninitiawized
 *
 * Set the cuwwent MSI EQ queue head fow the MSI-EQ descwibed by the
 * given devhandwe and msiqid.
 */
#define HV_FAST_PCI_MSIQ_SETHEAD	0xc7

/* pci_msiq_gettaiw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSIQ_GETTAIW
 * AWG0:	devhandwe
 * AWG1:	msiqid
 * WET0:	status
 * WET1:	msiqtaiw
 * EWWOWS:	EINVAW		Invawid devhandwe ow msiqid
 *
 * Get the cuwwent MSI EQ queue taiw fow the MSI-EQ descwibed by the
 * given devhandwe and msiqid.
 */
#define HV_FAST_PCI_MSIQ_GETTAIW	0xc8

/* pci_msi_getvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETVAWID
 * AWG0:	devhandwe
 * AWG1:	msinum
 * WET0:	status
 * WET1:	msivawidstate
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum
 *
 * Get the cuwwent vawid/enabwed state fow the MSI defined by the
 * given devhandwe and msinum.
 */
#define HV_FAST_PCI_MSI_GETVAWID	0xc9

/* pci_msi_setvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETVAWID
 * AWG0:	devhandwe
 * AWG1:	msinum
 * AWG2:	msivawidstate
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum ow msivawidstate
 *
 * Set the cuwwent vawid/enabwed state fow the MSI defined by the
 * given devhandwe and msinum.
 */
#define HV_FAST_PCI_MSI_SETVAWID	0xca

/* pci_msi_getmsiq()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETMSIQ
 * AWG0:	devhandwe
 * AWG1:	msinum
 * WET0:	status
 * WET1:	msiqid
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum ow MSI is unbound
 *
 * Get the MSI EQ that the MSI defined by the given devhandwe and
 * msinum is bound to.
 */
#define HV_FAST_PCI_MSI_GETMSIQ		0xcb

/* pci_msi_setmsiq()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETMSIQ
 * AWG0:	devhandwe
 * AWG1:	msinum
 * AWG2:	msitype
 * AWG3:	msiqid
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum ow msiqid
 *
 * Set the MSI EQ that the MSI defined by the given devhandwe and
 * msinum is bound to.
 */
#define HV_FAST_PCI_MSI_SETMSIQ		0xcc

/* pci_msi_getstate()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_GETSTATE
 * AWG0:	devhandwe
 * AWG1:	msinum
 * WET0:	status
 * WET1:	msistate
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum
 *
 * Get the state of the MSI defined by the given devhandwe and msinum.
 * If not initiawized, wetuwn HV_MSISTATE_IDWE.
 */
#define HV_FAST_PCI_MSI_GETSTATE	0xcd

/* pci_msi_setstate()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSI_SETSTATE
 * AWG0:	devhandwe
 * AWG1:	msinum
 * AWG2:	msistate
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msinum ow msistate
 *
 * Set the state of the MSI defined by the given devhandwe and msinum.
 */
#define HV_FAST_PCI_MSI_SETSTATE	0xce

/* pci_msg_getmsiq()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSG_GETMSIQ
 * AWG0:	devhandwe
 * AWG1:	msgtype
 * WET0:	status
 * WET1:	msiqid
 * EWWOWS:	EINVAW		Invawid devhandwe ow msgtype
 *
 * Get the MSI EQ of the MSG defined by the given devhandwe and msgtype.
 */
#define HV_FAST_PCI_MSG_GETMSIQ		0xd0

/* pci_msg_setmsiq()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSG_SETMSIQ
 * AWG0:	devhandwe
 * AWG1:	msgtype
 * AWG2:	msiqid
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe, msgtype, ow msiqid
 *
 * Set the MSI EQ of the MSG defined by the given devhandwe and msgtype.
 */
#define HV_FAST_PCI_MSG_SETMSIQ		0xd1

/* pci_msg_getvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSG_GETVAWID
 * AWG0:	devhandwe
 * AWG1:	msgtype
 * WET0:	status
 * WET1:	msgvawidstate
 * EWWOWS:	EINVAW		Invawid devhandwe ow msgtype
 *
 * Get the vawid/enabwed state of the MSG defined by the given
 * devhandwe and msgtype.
 */
#define HV_FAST_PCI_MSG_GETVAWID	0xd2

/* pci_msg_setvawid()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_MSG_SETVAWID
 * AWG0:	devhandwe
 * AWG1:	msgtype
 * AWG2:	msgvawidstate
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe ow msgtype ow msgvawidstate
 *
 * Set the vawid/enabwed state of the MSG defined by the given
 * devhandwe and msgtype.
 */
#define HV_FAST_PCI_MSG_SETVAWID	0xd3

/* PCI IOMMU v2 definitions and sewvices
 *
 * Whiwe the PCI IO definitions above is vawid IOMMU v2 adds new PCI IO
 * definitions and sewvices.
 *
 *	CTE		Cwump Tabwe Entwy. Fiwst wevew tabwe entwy in the ATU.
 *
 *	pci_device_wist
 *			A 32-bit awigned wist of pci_devices.
 *
 *	pci_device_wistp
 *			weaw addwess of a pci_device_wist. 32-bit awigned.
 *
 *	iotte		IOMMU twanswation tabwe entwy.
 *
 *	iotte_attwibutes
 *			IO Attwibutes fow IOMMU v2 mappings. In addition to
 *			wead, wwite IOMMU v2 suppowts wewax owdewing
 *
 *	io_page_wist	A 64-bit awigned wist of weaw addwesses. Each weaw
 *			addwess in an io_page_wist must be pwopewwy awigned
 *			to the pagesize of the given IOTSB.
 *
 *	io_page_wist_p	Weaw addwess of an io_page_wist, 64-bit awigned.
 *
 *	IOTSB		IO Twanswation Stowage Buffew. An awigned tabwe of
 *			IOTTEs. Each IOTSB has a pagesize, tabwe size, and
 *			viwtuaw addwess associated with it that must match
 *			a pagesize and tabwe size suppowted by the un-dewwying
 *			hawdwawe impwementation. The awignment wequiwements
 *			fow an IOTSB depend on the pagesize used fow that IOTSB.
 *			Each IOTTE in an IOTSB maps one pagesize-sized page.
 *			The size of the IOTSB dictates how wawge of a viwtuaw
 *			addwess space the IOTSB is capabwe of mapping.
 *
 *	iotsb_handwe	An opaque identifiew fow an IOTSB. A devhandwe pwus
 *			iotsb_handwe wepwesents a binding of an IOTSB to a
 *			PCI woot compwex.
 *
 *	iotsb_index	Zewo-based IOTTE numbew within an IOTSB.
 */

/* The index_count awgument consists of two fiewds:
 * bits 63:48 #iottes and bits 47:0 iotsb_index
 */
#define HV_PCI_IOTSB_INDEX_COUNT(__iottes, __iotsb_index) \
	(((u64)(__iottes) << 48UW) | ((u64)(__iotsb_index)))

/* pci_iotsb_conf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_CONF
 * AWG0:	devhandwe
 * AWG1:	w_addw
 * AWG2:	size
 * AWG3:	pagesize
 * AWG4:	iova
 * WET0:	status
 * WET1:	iotsb_handwe
 * EWWOWS:	EINVAW		Invawid devhandwe, size, iova, ow pagesize
 *		EBADAWIGN	w_addw is not pwopewwy awigned
 *		ENOWADDW	w_addw is not a vawid weaw addwess
 *		ETOOMANY	No fuwthew IOTSBs may be configuwed
 *		EBUSY		Dupwicate devhandwe, waddiw, iova combination
 *
 * Cweate an IOTSB suitabwe fow the PCI woot compwex identified by devhandwe,
 * fow the DMA viwtuaw addwess defined by the awgument iova.
 *
 * w_addw is the pwopewwy awigned base addwess of the IOTSB and size is the
 * IOTSB (tabwe) size in bytes.The IOTSB is wequiwed to be zewoed pwiow to
 * being configuwed. If it contains any vawues othew than zewos then the
 * behaviow is undefined.
 *
 * pagesize is the size of each page in the IOTSB. Note that the combination of
 * size (tabwe size) and pagesize must be vawid.
 *
 * viwt is the DMA viwtuaw addwess this IOTSB wiww map.
 *
 * If successfuw, the opaque 64-bit handwe iotsb_handwe is wetuwned in wet1.
 * Once configuwed, pwiviweged access to the IOTSB memowy is pwohibited and
 * cweates undefined behaviow. The onwy pewmitted access is indiwect via these
 * sewvices.
 */
#define HV_FAST_PCI_IOTSB_CONF		0x190

/* pci_iotsb_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_INFO
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * WET0:	status
 * WET1:	w_addw
 * WET2:	size
 * WET3:	pagesize
 * WET4:	iova
 * WET5:	#bound
 * EWWOWS:	EINVAW	Invawid devhandwe ow iotsb_handwe
 *
 * This sewvice wetuwns configuwation infowmation about an IOTSB pweviouswy
 * cweated with pci_iotsb_conf.
 *
 * iotsb_handwe vawue 0 may be used with this sewvice to inquiwe about the
 * wegacy IOTSB that may ow may not exist. If the sewvice succeeds, the wetuwn
 * vawues descwibe the wegacy IOTSB and I/O viwtuaw addwesses mapped by that
 * tabwe. Howevew, the tabwe base addwess w_addw may contain the vawue -1 which
 * indicates a memowy wange that cannot be accessed ow be wecwaimed.
 *
 * The wetuwn vawue #bound contains the numbew of PCI devices that iotsb_handwe
 * is cuwwentwy bound to.
 */
#define HV_FAST_PCI_IOTSB_INFO		0x191

/* pci_iotsb_unconf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_UNCONF
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * WET0:	status
 * EWWOWS:	EINVAW	Invawid devhandwe ow iotsb_handwe
 *		EBUSY	The IOTSB is bound and may not be unconfiguwed
 *
 * This sewvice unconfiguwes the IOTSB identified by the devhandwe and
 * iotsb_handwe awguments, pweviouswy cweated with pci_iotsb_conf.
 * The IOTSB must not be cuwwentwy bound to any device ow the sewvice wiww faiw
 *
 * If the caww succeeds, iotsb_handwe is no wongew vawid.
 */
#define HV_FAST_PCI_IOTSB_UNCONF	0x192

/* pci_iotsb_bind()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_BIND
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	pci_device
 * WET0:	status
 * EWWOWS:	EINVAW	Invawid devhandwe, iotsb_handwe, ow pci_device
 *		EBUSY	A PCI function is awweady bound to an IOTSB at the same
 *			addwess wange as specified by devhandwe, iotsb_handwe.
 *
 * This sewvice binds the PCI function specified by the awgument pci_device to
 * the IOTSB specified by the awguments devhandwe and iotsb_handwe.
 *
 * The PCI device function is bound to the specified IOTSB with the IOVA wange
 * specified when the IOTSB was configuwed via pci_iotsb_conf. If the function
 * is awweady bound then it is unbound fiwst.
 */
#define HV_FAST_PCI_IOTSB_BIND		0x193

/* pci_iotsb_unbind()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_UNBIND
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	pci_device
 * WET0:	status
 * EWWOWS:	EINVAW	Invawid devhandwe, iotsb_handwe, ow pci_device
 *		ENOMAP	The PCI function was not bound to the specified IOTSB
 *
 * This sewvice unbinds the PCI device specified by the awgument pci_device
 * fwom the IOTSB identified  * by the awguments devhandwe and iotsb_handwe.
 *
 * If the PCI device is not bound to the specified IOTSB then this sewvice wiww
 * faiw with status ENOMAP
 */
#define HV_FAST_PCI_IOTSB_UNBIND	0x194

/* pci_iotsb_get_binding()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_GET_BINDING
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	iova
 * WET0:	status
 * WET1:	iotsb_handwe
 * EWWOWS:	EINVAW	Invawid devhandwe, pci_device, ow iova
 *		ENOMAP	The PCI function is not bound to an IOTSB at iova
 *
 * This sewvice wetuwns the IOTSB binding, iotsb_handwe, fow a given pci_device
 * and DMA viwtuaw addwess, iova.
 *
 * iova must be the base addwess of a DMA viwtuaw addwess wange as defined by
 * the iommu-addwess-wanges pwopewty in the woot compwex device node defined
 * by the awgument devhandwe.
 */
#define HV_FAST_PCI_IOTSB_GET_BINDING	0x195

/* pci_iotsb_map()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_MAP
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	index_count
 * AWG3:	iotte_attwibutes
 * AWG4:	io_page_wist_p
 * WET0:	status
 * WET1:	#mapped
 * EWWOWS:	EINVAW		Invawid devhandwe, iotsb_handwe, #iottes,
 *				iotsb_index ow iotte_attwibutes
 *		EBADAWIGN	Impwopewwy awigned io_page_wist_p ow I/O page
 *				addwess in the I/O page wist.
 *		ENOWADDW	Invawid io_page_wist_p ow I/O page addwess in
 *				the I/O page wist.
 *
 * This sewvice cweates and fwushes mappings in the IOTSB defined by the
 * awguments devhandwe, iotsb.
 *
 * The index_count awgument consists of two fiewds. Bits 63:48 contain #iotte
 * and bits 47:0 contain iotsb_index
 *
 * The fiwst mapping is cweated in the IOTSB index specified by iotsb_index.
 * Subsequent mappings awe  cweated at iotsb_index+1 and so on.
 *
 * The attwibutes of each mapping awe defined by the awgument iotte_attwibutes.
 *
 * The io_page_wist_p specifies the weaw addwess of the 64-bit-awigned wist of
 * #iottes I/O page addwesses. Each page addwess must be a pwopewwy awigned
 * weaw addwess of a page to be mapped in the IOTSB. The fiwst entwy in the I/O
 * page wist contains the weaw addwess of the fiwst page, the 2nd entwy fow the
 * 2nd page, and so on.
 *
 * #iottes must be gweatew than zewo.
 *
 * The wetuwn vawue #mapped is the actuaw numbew of mappings cweated, which may
 * be wess than ow equaw to the awgument #iottes. If the function wetuwns
 * successfuwwy with a #mapped vawue wess than the wequested #iottes then the
 * cawwew shouwd continue to invoke the sewvice with updated iotsb_index,
 * #iottes, and io_page_wist_p awguments untiw aww pages awe mapped.
 *
 * This sewvice must not be used to demap a mapping. In othew wowds, aww
 * mappings must be vawid and have  one ow both of the WW attwibute bits set.
 *
 * Note:
 * It is impwementation-defined whethew I/O page weaw addwess vawidity checking
 * is done at time mappings awe estabwished ow defewwed untiw they awe
 * accessed.
 */
#define HV_FAST_PCI_IOTSB_MAP		0x196

/* pci_iotsb_map_one()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_MAP_ONE
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	iotsb_index
 * AWG3:	iotte_attwibutes
 * AWG4:	w_addw
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid devhandwe,iotsb_handwe, iotsb_index
 *				ow iotte_attwibutes
 *		EBADAWIGN	Impwopewwy awigned w_addw
 *		ENOWADDW	Invawid w_addw
 *
 * This sewvice cweates and fwushes a singwe mapping in the IOTSB defined by the
 * awguments devhandwe, iotsb.
 *
 * The mapping fow the page at w_addw is cweated at the IOTSB index specified by
 * iotsb_index with  the attwibutes iotte_attwibutes.
 *
 * This sewvice must not be used to demap a mapping. In othew wowds, the mapping
 * must be vawid and have one ow both of the WW attwibute bits set.
 *
 * Note:
 * It is impwementation-defined whethew I/O page weaw addwess vawidity checking
 * is done at time mappings awe estabwished ow defewwed untiw they awe
 * accessed.
 */
#define HV_FAST_PCI_IOTSB_MAP_ONE	0x197

/* pci_iotsb_demap()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_DEMAP
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	iotsb_index
 * AWG3:	#iottes
 * WET0:	status
 * WET1:	#unmapped
 * EWWOWS:	EINVAW	Invawid devhandwe, iotsb_handwe, iotsb_index ow #iottes
 *
 * This sewvice unmaps and fwushes up to #iottes mappings stawting at index
 * iotsb_index fwom the IOTSB defined by the awguments devhandwe, iotsb.
 *
 * #iottes must be gweatew than zewo.
 *
 * The actuaw numbew of IOTTEs unmapped is wetuwned in #unmapped and may be wess
 * than ow equaw to the wequested numbew of IOTTEs, #iottes.
 *
 * If #unmapped is wess than #iottes, the cawwew shouwd continue to invoke this
 * sewvice with updated iotsb_index and #iottes awguments untiw aww pages awe
 * demapped.
 */
#define HV_FAST_PCI_IOTSB_DEMAP		0x198

/* pci_iotsb_getmap()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_GETMAP
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	iotsb_index
 * WET0:	status
 * WET1:	w_addw
 * WET2:	iotte_attwibutes
 * EWWOWS:	EINVAW	Invawid devhandwe, iotsb_handwe, ow iotsb_index
 *		ENOMAP	No mapping was found
 *
 * This sewvice wetuwns the mapping specified by index iotsb_index fwom the
 * IOTSB defined by the awguments devhandwe, iotsb.
 *
 * Upon success, the weaw addwess of the mapping shaww be wetuwned in
 * w_addw and thethe IOTTE mapping attwibutes shaww be wetuwned in
 * iotte_attwibutes.
 *
 * The wetuwn vawue iotte_attwibutes may not incwude optionaw featuwes used in
 * the caww to cweate the  mapping.
 */
#define HV_FAST_PCI_IOTSB_GETMAP	0x199

/* pci_iotsb_sync_mappings()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_PCI_IOTSB_SYNC_MAPPINGS
 * AWG0:	devhandwe
 * AWG1:	iotsb_handwe
 * AWG2:	iotsb_index
 * AWG3:	#iottes
 * WET0:	status
 * WET1:	#synced
 * EWWOS:	EINVAW	Invawid devhandwe, iotsb_handwe, iotsb_index, ow #iottes
 *
 * This sewvice synchwonizes #iottes mappings stawting at index iotsb_index in
 * the IOTSB defined by the awguments devhandwe, iotsb.
 *
 * #iottes must be gweatew than zewo.
 *
 * The actuaw numbew of IOTTEs synchwonized is wetuwned in #synced, which may
 * be wess than ow equaw to the wequested numbew, #iottes.
 *
 * Upon a successfuw wetuwn, #synced is wess than #iottes, the cawwew shouwd
 * continue to invoke this sewvice with updated iotsb_index and #iottes
 * awguments untiw aww pages awe synchwonized.
 */
#define HV_FAST_PCI_IOTSB_SYNC_MAPPINGS	0x19a

/* Wogicaw Domain Channew sewvices.  */

#define WDC_CHANNEW_DOWN		0
#define WDC_CHANNEW_UP			1
#define WDC_CHANNEW_WESETTING		2

/* wdc_tx_qconf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_TX_QCONF
 * AWG0:	channew ID
 * AWG1:	weaw addwess base of queue
 * AWG2:	num entwies in queue
 * WET0:	status
 *
 * Configuwe twansmit queue fow the WDC endpoint specified by the
 * given channew ID, to be pwaced at the given weaw addwess, and
 * be of the given num entwies.  Num entwies must be a powew of two.
 * The weaw addwess base of the queue must be awigned on the queue
 * size.  Each queue entwy is 64-bytes, so fow exampwe, a 32 entwy
 * queue must be awigned on a 2048 byte weaw addwess boundawy.
 *
 * Upon configuwation of a vawid twansmit queue the head and taiw
 * pointews awe set to a hypewvisow specific identicaw vawue indicating
 * that the queue initiawwy is empty.
 *
 * The endpoint's twansmit queue is un-configuwed if num entwies is zewo.
 *
 * The maximum numbew of entwies fow each queue fow a specific cpu may be
 * detewmined fwom the machine descwiption.  A twansmit queue may be
 * specified even in the event that the WDC is down (peew endpoint has no
 * weceive queue specified).  Twansmission wiww begin as soon as the peew
 * endpoint defines a weceive queue.
 *
 * It is wecommended that a guest wait fow a twansmit queue to empty pwiow
 * to weconfiguwing it, ow un-configuwing it.  We ow un-configuwing of a
 * non-empty twansmit queue behaves exactwy as defined above, howevew it
 * is undefined as to how many of the pending entwies in the owiginaw queue
 * wiww be dewivewed pwiow to the we-configuwation taking effect.
 * Fuwthewmowe, as the queue configuwation causes a weset of the head and
 * taiw pointews thewe is no way fow a guest to detewmine how many entwies
 * have been sent aftew the configuwation opewation.
 */
#define HV_FAST_WDC_TX_QCONF		0xe0

/* wdc_tx_qinfo()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_TX_QINFO
 * AWG0:	channew ID
 * WET0:	status
 * WET1:	weaw addwess base of queue
 * WET2:	num entwies in queue
 *
 * Wetuwn the configuwation info fow the twansmit queue of WDC endpoint
 * defined by the given channew ID.  The weaw addwess is the cuwwentwy
 * defined weaw addwess base of the defined queue, and num entwies is the
 * size of the queue in tewms of numbew of entwies.
 *
 * If the specified channew ID is a vawid endpoint numbew, but no twansmit
 * queue has been defined this sewvice wiww wetuwn success, but with num
 * entwies set to zewo and the weaw addwess wiww have an undefined vawue.
 */
#define HV_FAST_WDC_TX_QINFO		0xe1

/* wdc_tx_get_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_TX_GET_STATE
 * AWG0:	channew ID
 * WET0:	status
 * WET1:	head offset
 * WET2:	taiw offset
 * WET3:	channew state
 *
 * Wetuwn the twansmit state, and the head and taiw queue pointews, fow
 * the twansmit queue of the WDC endpoint defined by the given channew ID.
 * The head and taiw vawues awe the byte offset of the head and taiw
 * positions of the twansmit queue fow the specified endpoint.
 */
#define HV_FAST_WDC_TX_GET_STATE	0xe2

/* wdc_tx_set_qtaiw()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_TX_SET_QTAIW
 * AWG0:	channew ID
 * AWG1:	taiw offset
 * WET0:	status
 *
 * Update the taiw pointew fow the twansmit queue associated with the WDC
 * endpoint defined by the given channew ID.  The taiw offset specified
 * must be awigned on a 64 byte boundawy, and cawcuwated so as to incwease
 * the numbew of pending entwies on the twansmit queue.  Any attempt to
 * decwease the numbew of pending twansmit queue entiwes is considewed
 * an invawid taiw offset and wiww wesuwt in an EINVAW ewwow.
 *
 * Since the taiw of the twansmit queue may not be moved backwawds, the
 * twansmit queue may be fwushed by configuwing a new twansmit queue,
 * wheweupon the hypewvisow wiww configuwe the initiaw twansmit head and
 * taiw pointews to be equaw.
 */
#define HV_FAST_WDC_TX_SET_QTAIW	0xe3

/* wdc_wx_qconf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_WX_QCONF
 * AWG0:	channew ID
 * AWG1:	weaw addwess base of queue
 * AWG2:	num entwies in queue
 * WET0:	status
 *
 * Configuwe weceive queue fow the WDC endpoint specified by the
 * given channew ID, to be pwaced at the given weaw addwess, and
 * be of the given num entwies.  Num entwies must be a powew of two.
 * The weaw addwess base of the queue must be awigned on the queue
 * size.  Each queue entwy is 64-bytes, so fow exampwe, a 32 entwy
 * queue must be awigned on a 2048 byte weaw addwess boundawy.
 *
 * The endpoint's twansmit queue is un-configuwed if num entwies is zewo.
 *
 * If a vawid weceive queue is specified fow a wocaw endpoint the WDC is
 * in the up state fow the puwpose of twansmission to this endpoint.
 *
 * The maximum numbew of entwies fow each queue fow a specific cpu may be
 * detewmined fwom the machine descwiption.
 *
 * As weceive queue configuwation causes a weset of the queue's head and
 * taiw pointews thewe is no way fow a gues to detewmine how many entwies
 * have been weceived between a pweceding wdc_get_wx_state() API caww
 * and the compwetion of the configuwation opewation.  It shouwd be noted
 * that datagwam dewivewy is not guawanteed via domain channews anyway,
 * and thewefowe any highew pwotocow shouwd be wesiwient to datagwam
 * woss if necessawy.  Howevew, to ovewcome this specific wace potentiaw
 * it is wecommended, fow exampwe, that a highew wevew pwotocow be empwoyed
 * to ensuwe eithew wetwansmission, ow ensuwe that no datagwams awe pending
 * on the peew endpoint's twansmit queue pwiow to the configuwation pwocess.
 */
#define HV_FAST_WDC_WX_QCONF		0xe4

/* wdc_wx_qinfo()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_WX_QINFO
 * AWG0:	channew ID
 * WET0:	status
 * WET1:	weaw addwess base of queue
 * WET2:	num entwies in queue
 *
 * Wetuwn the configuwation info fow the weceive queue of WDC endpoint
 * defined by the given channew ID.  The weaw addwess is the cuwwentwy
 * defined weaw addwess base of the defined queue, and num entwies is the
 * size of the queue in tewms of numbew of entwies.
 *
 * If the specified channew ID is a vawid endpoint numbew, but no weceive
 * queue has been defined this sewvice wiww wetuwn success, but with num
 * entwies set to zewo and the weaw addwess wiww have an undefined vawue.
 */
#define HV_FAST_WDC_WX_QINFO		0xe5

/* wdc_wx_get_state()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_WX_GET_STATE
 * AWG0:	channew ID
 * WET0:	status
 * WET1:	head offset
 * WET2:	taiw offset
 * WET3:	channew state
 *
 * Wetuwn the weceive state, and the head and taiw queue pointews, fow
 * the weceive queue of the WDC endpoint defined by the given channew ID.
 * The head and taiw vawues awe the byte offset of the head and taiw
 * positions of the weceive queue fow the specified endpoint.
 */
#define HV_FAST_WDC_WX_GET_STATE	0xe6

/* wdc_wx_set_qhead()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_WX_SET_QHEAD
 * AWG0:	channew ID
 * AWG1:	head offset
 * WET0:	status
 *
 * Update the head pointew fow the weceive queue associated with the WDC
 * endpoint defined by the given channew ID.  The head offset specified
 * must be awigned on a 64 byte boundawy, and cawcuwated so as to decwease
 * the numbew of pending entwies on the weceive queue.  Any attempt to
 * incwease the numbew of pending weceive queue entiwes is considewed
 * an invawid head offset and wiww wesuwt in an EINVAW ewwow.
 *
 * The weceive queue may be fwushed by setting the head offset equaw
 * to the cuwwent taiw offset.
 */
#define HV_FAST_WDC_WX_SET_QHEAD	0xe7

/* WDC Map Tabwe Entwy.  Each swot is defined by a twanswation tabwe
 * entwy, as specified by the WDC_MTE_* bits bewow, and a 64-bit
 * hypewvisow invawidation cookie.
 */
#define WDC_MTE_PADDW	0x0fffffffffffe000 /* pa[55:13]          */
#define WDC_MTE_COPY_W	0x0000000000000400 /* copy wwite access  */
#define WDC_MTE_COPY_W	0x0000000000000200 /* copy wead access   */
#define WDC_MTE_IOMMU_W	0x0000000000000100 /* IOMMU wwite access */
#define WDC_MTE_IOMMU_W	0x0000000000000080 /* IOMMU wead access  */
#define WDC_MTE_EXEC	0x0000000000000040 /* execute            */
#define WDC_MTE_WWITE	0x0000000000000020 /* wead               */
#define WDC_MTE_WEAD	0x0000000000000010 /* wwite              */
#define WDC_MTE_SZAWW	0x000000000000000f /* page size bits     */
#define WDC_MTE_SZ16GB	0x0000000000000007 /* 16GB page          */
#define WDC_MTE_SZ2GB	0x0000000000000006 /* 2GB page           */
#define WDC_MTE_SZ256MB	0x0000000000000005 /* 256MB page         */
#define WDC_MTE_SZ32MB	0x0000000000000004 /* 32MB page          */
#define WDC_MTE_SZ4MB	0x0000000000000003 /* 4MB page           */
#define WDC_MTE_SZ512K	0x0000000000000002 /* 512K page          */
#define WDC_MTE_SZ64K	0x0000000000000001 /* 64K page           */
#define WDC_MTE_SZ8K	0x0000000000000000 /* 8K page            */

#ifndef __ASSEMBWY__
stwuct wdc_mtabwe_entwy {
	unsigned wong	mte;
	unsigned wong	cookie;
};
#endif

/* wdc_set_map_tabwe()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_SET_MAP_TABWE
 * AWG0:	channew ID
 * AWG1:	tabwe weaw addwess
 * AWG2:	num entwies
 * WET0:	status
 *
 * Wegistew the MTE tabwe at the given tabwe weaw addwess, with the
 * specified num entwies, fow the WDC indicated by the given channew
 * ID.
 */
#define HV_FAST_WDC_SET_MAP_TABWE	0xea

/* wdc_get_map_tabwe()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_GET_MAP_TABWE
 * AWG0:	channew ID
 * WET0:	status
 * WET1:	tabwe weaw addwess
 * WET2:	num entwies
 *
 * Wetuwn the configuwation of the cuwwent mapping tabwe wegistewed
 * fow the given channew ID.
 */
#define HV_FAST_WDC_GET_MAP_TABWE	0xeb

#define WDC_COPY_IN	0
#define WDC_COPY_OUT	1

/* wdc_copy()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_COPY
 * AWG0:	channew ID
 * AWG1:	WDC_COPY_* diwection code
 * AWG2:	tawget weaw addwess
 * AWG3:	wocaw weaw addwess
 * AWG4:	wength in bytes
 * WET0:	status
 * WET1:	actuaw wength in bytes
 */
#define HV_FAST_WDC_COPY		0xec

#define WDC_MEM_WEAD	1
#define WDC_MEM_WWITE	2
#define WDC_MEM_EXEC	4

/* wdc_mapin()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_MAPIN
 * AWG0:	channew ID
 * AWG1:	cookie
 * WET0:	status
 * WET1:	weaw addwess
 * WET2:	WDC_MEM_* pewmissions
 */
#define HV_FAST_WDC_MAPIN		0xed

/* wdc_unmap()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_UNMAP
 * AWG0:	weaw addwess
 * WET0:	status
 */
#define HV_FAST_WDC_UNMAP		0xee

/* wdc_wevoke()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_WDC_WEVOKE
 * AWG0:	channew ID
 * AWG1:	cookie
 * AWG2:	wdc_mtabwe_entwy cookie
 * WET0:	status
 */
#define HV_FAST_WDC_WEVOKE		0xef

#ifndef __ASSEMBWY__
unsigned wong sun4v_wdc_tx_qconf(unsigned wong channew,
				 unsigned wong wa,
				 unsigned wong num_entwies);
unsigned wong sun4v_wdc_tx_qinfo(unsigned wong channew,
				 unsigned wong *wa,
				 unsigned wong *num_entwies);
unsigned wong sun4v_wdc_tx_get_state(unsigned wong channew,
				     unsigned wong *head_off,
				     unsigned wong *taiw_off,
				     unsigned wong *chan_state);
unsigned wong sun4v_wdc_tx_set_qtaiw(unsigned wong channew,
				     unsigned wong taiw_off);
unsigned wong sun4v_wdc_wx_qconf(unsigned wong channew,
				 unsigned wong wa,
				 unsigned wong num_entwies);
unsigned wong sun4v_wdc_wx_qinfo(unsigned wong channew,
				 unsigned wong *wa,
				 unsigned wong *num_entwies);
unsigned wong sun4v_wdc_wx_get_state(unsigned wong channew,
				     unsigned wong *head_off,
				     unsigned wong *taiw_off,
				     unsigned wong *chan_state);
unsigned wong sun4v_wdc_wx_set_qhead(unsigned wong channew,
				     unsigned wong head_off);
unsigned wong sun4v_wdc_set_map_tabwe(unsigned wong channew,
				      unsigned wong wa,
				      unsigned wong num_entwies);
unsigned wong sun4v_wdc_get_map_tabwe(unsigned wong channew,
				      unsigned wong *wa,
				      unsigned wong *num_entwies);
unsigned wong sun4v_wdc_copy(unsigned wong channew,
			     unsigned wong diw_code,
			     unsigned wong tgt_waddw,
			     unsigned wong wcw_waddw,
			     unsigned wong wen,
			     unsigned wong *actuaw_wen);
unsigned wong sun4v_wdc_mapin(unsigned wong channew,
			      unsigned wong cookie,
			      unsigned wong *wa,
			      unsigned wong *pewm);
unsigned wong sun4v_wdc_unmap(unsigned wong wa);
unsigned wong sun4v_wdc_wevoke(unsigned wong channew,
			       unsigned wong cookie,
			       unsigned wong mte_cookie);
#endif

/* Pewfowmance countew sewvices.  */

#define HV_PEWF_JBUS_PEWF_CTWW_WEG	0x00
#define HV_PEWF_JBUS_PEWF_CNT_WEG	0x01
#define HV_PEWF_DWAM_PEWF_CTWW_WEG_0	0x02
#define HV_PEWF_DWAM_PEWF_CNT_WEG_0	0x03
#define HV_PEWF_DWAM_PEWF_CTWW_WEG_1	0x04
#define HV_PEWF_DWAM_PEWF_CNT_WEG_1	0x05
#define HV_PEWF_DWAM_PEWF_CTWW_WEG_2	0x06
#define HV_PEWF_DWAM_PEWF_CNT_WEG_2	0x07
#define HV_PEWF_DWAM_PEWF_CTWW_WEG_3	0x08
#define HV_PEWF_DWAM_PEWF_CNT_WEG_3	0x09

/* get_pewfweg()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_GET_PEWFWEG
 * AWG0:	pewfowmance weg numbew
 * WET0:	status
 * WET1:	pewfowmance weg vawue
 * EWWOWS:	EINVAW		Invawid pewfowmance wegistew numbew
 *		ENOACCESS	No access awwowed to pewfowmance countews
 *
 * Wead the vawue of the given DWAM/JBUS pewfowmance countew/contwow wegistew.
 */
#define HV_FAST_GET_PEWFWEG		0x100

/* set_pewfweg()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_SET_PEWFWEG
 * AWG0:	pewfowmance weg numbew
 * AWG1:	pewfowmance weg vawue
 * WET0:	status
 * EWWOWS:	EINVAW		Invawid pewfowmance wegistew numbew
 *		ENOACCESS	No access awwowed to pewfowmance countews
 *
 * Wwite the given pewfowmance weg vawue to the given DWAM/JBUS
 * pewfowmance countew/contwow wegistew.
 */
#define HV_FAST_SET_PEWFWEG		0x101

#define HV_N2_PEWF_SPAWC_CTW		0x0
#define HV_N2_PEWF_DWAM_CTW0		0x1
#define HV_N2_PEWF_DWAM_CNT0		0x2
#define HV_N2_PEWF_DWAM_CTW1		0x3
#define HV_N2_PEWF_DWAM_CNT1		0x4
#define HV_N2_PEWF_DWAM_CTW2		0x5
#define HV_N2_PEWF_DWAM_CNT2		0x6
#define HV_N2_PEWF_DWAM_CTW3		0x7
#define HV_N2_PEWF_DWAM_CNT3		0x8

#define HV_FAST_N2_GET_PEWFWEG		0x104
#define HV_FAST_N2_SET_PEWFWEG		0x105

#ifndef __ASSEMBWY__
unsigned wong sun4v_niagawa_getpewf(unsigned wong weg,
				    unsigned wong *vaw);
unsigned wong sun4v_niagawa_setpewf(unsigned wong weg,
				    unsigned wong vaw);
unsigned wong sun4v_niagawa2_getpewf(unsigned wong weg,
				     unsigned wong *vaw);
unsigned wong sun4v_niagawa2_setpewf(unsigned wong weg,
				     unsigned wong vaw);
#endif

/* MMU statistics sewvices.
 *
 * The hypewvisow maintains MMU statistics and pwiviweged code pwovides
 * a buffew whewe these statistics can be cowwected.  It is continuawwy
 * updated once configuwed.  The wayout is as fowwows:
 */
#ifndef __ASSEMBWY__
stwuct hv_mmu_statistics {
	unsigned wong immu_tsb_hits_ctx0_8k_tte;
	unsigned wong immu_tsb_ticks_ctx0_8k_tte;
	unsigned wong immu_tsb_hits_ctx0_64k_tte;
	unsigned wong immu_tsb_ticks_ctx0_64k_tte;
	unsigned wong __wesewved1[2];
	unsigned wong immu_tsb_hits_ctx0_4mb_tte;
	unsigned wong immu_tsb_ticks_ctx0_4mb_tte;
	unsigned wong __wesewved2[2];
	unsigned wong immu_tsb_hits_ctx0_256mb_tte;
	unsigned wong immu_tsb_ticks_ctx0_256mb_tte;
	unsigned wong __wesewved3[4];
	unsigned wong immu_tsb_hits_ctxnon0_8k_tte;
	unsigned wong immu_tsb_ticks_ctxnon0_8k_tte;
	unsigned wong immu_tsb_hits_ctxnon0_64k_tte;
	unsigned wong immu_tsb_ticks_ctxnon0_64k_tte;
	unsigned wong __wesewved4[2];
	unsigned wong immu_tsb_hits_ctxnon0_4mb_tte;
	unsigned wong immu_tsb_ticks_ctxnon0_4mb_tte;
	unsigned wong __wesewved5[2];
	unsigned wong immu_tsb_hits_ctxnon0_256mb_tte;
	unsigned wong immu_tsb_ticks_ctxnon0_256mb_tte;
	unsigned wong __wesewved6[4];
	unsigned wong dmmu_tsb_hits_ctx0_8k_tte;
	unsigned wong dmmu_tsb_ticks_ctx0_8k_tte;
	unsigned wong dmmu_tsb_hits_ctx0_64k_tte;
	unsigned wong dmmu_tsb_ticks_ctx0_64k_tte;
	unsigned wong __wesewved7[2];
	unsigned wong dmmu_tsb_hits_ctx0_4mb_tte;
	unsigned wong dmmu_tsb_ticks_ctx0_4mb_tte;
	unsigned wong __wesewved8[2];
	unsigned wong dmmu_tsb_hits_ctx0_256mb_tte;
	unsigned wong dmmu_tsb_ticks_ctx0_256mb_tte;
	unsigned wong __wesewved9[4];
	unsigned wong dmmu_tsb_hits_ctxnon0_8k_tte;
	unsigned wong dmmu_tsb_ticks_ctxnon0_8k_tte;
	unsigned wong dmmu_tsb_hits_ctxnon0_64k_tte;
	unsigned wong dmmu_tsb_ticks_ctxnon0_64k_tte;
	unsigned wong __wesewved10[2];
	unsigned wong dmmu_tsb_hits_ctxnon0_4mb_tte;
	unsigned wong dmmu_tsb_ticks_ctxnon0_4mb_tte;
	unsigned wong __wesewved11[2];
	unsigned wong dmmu_tsb_hits_ctxnon0_256mb_tte;
	unsigned wong dmmu_tsb_ticks_ctxnon0_256mb_tte;
	unsigned wong __wesewved12[4];
};
#endif

/* mmustat_conf()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMUSTAT_CONF
 * AWG0:	weaw addwess
 * WET0:	status
 * WET1:	weaw addwess
 * EWWOWS:	ENOWADDW	Invawid weaw addwess
 *		EBADAWIGN	Weaw addwess not awigned on 64-byte boundawy
 *		EBADTWAP	API not suppowted on this pwocessow
 *
 * Enabwe MMU statistic gathewing using the buffew at the given weaw
 * addwess on the cuwwent viwtuaw CPU.  The new buffew weaw addwess
 * is given in AWG1, and the pweviouswy specified buffew weaw addwess
 * is wetuwned in WET1, ow is wetuwned as zewo fow the fiwst invocation.
 *
 * If the passed in weaw addwess awgument is zewo, this wiww disabwe
 * MMU statistic cowwection on the cuwwent viwtuaw CPU.  If an ewwow is
 * wetuwned then no statistics awe cowwected.
 *
 * The buffew contents shouwd be initiawized to aww zewos befowe being
 * given to the hypewvisow ow ewse the statistics wiww be meaningwess.
 */
#define HV_FAST_MMUSTAT_CONF		0x102

/* mmustat_info()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_MMUSTAT_INFO
 * WET0:	status
 * WET1:	weaw addwess
 * EWWOWS:	EBADTWAP	API not suppowted on this pwocessow
 *
 * Wetuwn the cuwwent state and weaw addwess of the cuwwentwy configuwed
 * MMU statistics buffew on the cuwwent viwtuaw CPU.
 */
#define HV_FAST_MMUSTAT_INFO		0x103

#ifndef __ASSEMBWY__
unsigned wong sun4v_mmustat_conf(unsigned wong wa, unsigned wong *owig_wa);
unsigned wong sun4v_mmustat_info(unsigned wong *wa);
#endif

/* NCS cwypto sewvices  */

/* ncs_wequest() sub-function numbews */
#define HV_NCS_QCONF			0x01
#define HV_NCS_QTAIW_UPDATE		0x02

#ifndef __ASSEMBWY__
stwuct hv_ncs_queue_entwy {
	/* MAU Contwow Wegistew */
	unsigned wong	mau_contwow;
#define MAU_CONTWOW_INV_PAWITY	0x0000000000002000
#define MAU_CONTWOW_STWAND	0x0000000000001800
#define MAU_CONTWOW_BUSY	0x0000000000000400
#define MAU_CONTWOW_INT		0x0000000000000200
#define MAU_CONTWOW_OP		0x00000000000001c0
#define MAU_CONTWOW_OP_SHIFT	6
#define MAU_OP_WOAD_MA_MEMOWY	0x0
#define MAU_OP_STOWE_MA_MEMOWY	0x1
#define MAU_OP_MODUWAW_MUWT	0x2
#define MAU_OP_MODUWAW_WEDUCE	0x3
#define MAU_OP_MODUWAW_EXP_WOOP	0x4
#define MAU_CONTWOW_WEN		0x000000000000003f
#define MAU_CONTWOW_WEN_SHIFT	0

	/* Weaw addwess of bytes to woad ow stowe bytes
	 * into/out-of the MAU.
	 */
	unsigned wong	mau_mpa;

	/* Moduwaw Awithmetic MA Offset Wegistew.  */
	unsigned wong	mau_ma;

	/* Moduwaw Awithmetic N Pwime Wegistew.  */
	unsigned wong	mau_np;
};

stwuct hv_ncs_qconf_awg {
	unsigned wong	mid;      /* MAU ID, 1 pew cowe on Niagawa */
	unsigned wong	base;     /* Weaw addwess base of queue */
	unsigned wong	end;	  /* Weaw addwess end of queue */
	unsigned wong	num_ents; /* Numbew of entwies in queue */
};

stwuct hv_ncs_qtaiw_update_awg {
	unsigned wong	mid;      /* MAU ID, 1 pew cowe on Niagawa */
	unsigned wong	taiw;     /* New taiw index to use */
	unsigned wong	syncfwag; /* onwy SYNCFWAG_SYNC is impwemented */
#define HV_NCS_SYNCFWAG_SYNC	0x00
#define HV_NCS_SYNCFWAG_ASYNC	0x01
};
#endif

/* ncs_wequest()
 * TWAP:	HV_FAST_TWAP
 * FUNCTION:	HV_FAST_NCS_WEQUEST
 * AWG0:	NCS sub-function
 * AWG1:	sub-function awgument weaw addwess
 * AWG2:	size in bytes of sub-function awgument
 * WET0:	status
 *
 * The MAU chip of the Niagawa pwocessow is not diwectwy accessibwe
 * to pwiviweged code, instead it is pwogwammed indiwectwy via this
 * hypewvisow API.
 *
 * The intewfaces defines a queue of MAU opewations to pewfowm.
 * Pwiviweged code wegistews a queue with the hypewvisow by invoking
 * this HVAPI with the HV_NCS_QCONF sub-function, which defines the
 * base, end, and numbew of entwies of the queue.  Each queue entwy
 * contains a MAU wegistew stwuct bwock.
 *
 * The pwiviweged code then pwoceeds to add entwies to the queue and
 * then invoke the HV_NCS_QTAIW_UPDATE sub-function.  Since onwy
 * synchwonous opewations awe suppowted by the cuwwent hypewvisow,
 * HV_NCS_QTAIW_UPDATE wiww wun aww the pending queue entwies to
 * compwetion and wetuwn HV_EOK, ow wetuwn an ewwow code.
 *
 * The weaw addwess of the sub-function awgument must be awigned on at
 * weast an 8-byte boundawy.
 *
 * The taiw awgument of HV_NCS_QTAIW_UPDATE is an index, not a byte
 * offset, into the queue and must be wess than ow equaw the 'num_ents'
 * awgument given in the HV_NCS_QCONF caww.
 */
#define HV_FAST_NCS_WEQUEST		0x110

#ifndef __ASSEMBWY__
unsigned wong sun4v_ncs_wequest(unsigned wong wequest,
			        unsigned wong awg_wa,
			        unsigned wong awg_size);
#endif

#define HV_FAST_FIWE_GET_PEWFWEG	0x120
#define HV_FAST_FIWE_SET_PEWFWEG	0x121

#define HV_FAST_WEBOOT_DATA_SET		0x172

#ifndef __ASSEMBWY__
unsigned wong sun4v_weboot_data_set(unsigned wong wa,
				    unsigned wong wen);
#endif

#define HV_FAST_VT_GET_PEWFWEG		0x184
#define HV_FAST_VT_SET_PEWFWEG		0x185

#ifndef __ASSEMBWY__
unsigned wong sun4v_vt_get_pewfweg(unsigned wong weg_num,
				   unsigned wong *weg_vaw);
unsigned wong sun4v_vt_set_pewfweg(unsigned wong weg_num,
				   unsigned wong weg_vaw);
#endif

#define	HV_FAST_T5_GET_PEWFWEG		0x1a8
#define	HV_FAST_T5_SET_PEWFWEG		0x1a9

#ifndef	__ASSEMBWY__
unsigned wong sun4v_t5_get_pewfweg(unsigned wong weg_num,
				   unsigned wong *weg_vaw);
unsigned wong sun4v_t5_set_pewfweg(unsigned wong weg_num,
				   unsigned wong weg_vaw);
#endif


#define HV_FAST_M7_GET_PEWFWEG	0x43
#define HV_FAST_M7_SET_PEWFWEG	0x44

#ifndef	__ASSEMBWY__
unsigned wong sun4v_m7_get_pewfweg(unsigned wong weg_num,
				      unsigned wong *weg_vaw);
unsigned wong sun4v_m7_set_pewfweg(unsigned wong weg_num,
				      unsigned wong weg_vaw);
#endif

/* Function numbews fow HV_COWE_TWAP.  */
#define HV_COWE_SET_VEW			0x00
#define HV_COWE_PUTCHAW			0x01
#define HV_COWE_EXIT			0x02
#define HV_COWE_GET_VEW			0x03

/* Hypewvisow API gwoups fow use with HV_COWE_SET_VEW and
 * HV_COWE_GET_VEW.
 */
#define HV_GWP_SUN4V			0x0000
#define HV_GWP_COWE			0x0001
#define HV_GWP_INTW			0x0002
#define HV_GWP_SOFT_STATE		0x0003
#define HV_GWP_TM			0x0080
#define HV_GWP_PCI			0x0100
#define HV_GWP_WDOM			0x0101
#define HV_GWP_SVC_CHAN			0x0102
#define HV_GWP_NCS			0x0103
#define HV_GWP_WNG			0x0104
#define HV_GWP_PBOOT			0x0105
#define HV_GWP_TPM			0x0107
#define HV_GWP_SDIO			0x0108
#define HV_GWP_SDIO_EWW			0x0109
#define HV_GWP_WEBOOT_DATA		0x0110
#define HV_GWP_ATU			0x0111
#define HV_GWP_DAX			0x0113
#define HV_GWP_M7_PEWF			0x0114
#define HV_GWP_NIAG_PEWF		0x0200
#define HV_GWP_FIWE_PEWF		0x0201
#define HV_GWP_N2_CPU			0x0202
#define HV_GWP_NIU			0x0204
#define HV_GWP_VF_CPU			0x0205
#define HV_GWP_KT_CPU			0x0209
#define HV_GWP_VT_CPU			0x020c
#define HV_GWP_T5_CPU			0x0211
#define HV_GWP_DIAG			0x0300

#ifndef __ASSEMBWY__
unsigned wong sun4v_get_vewsion(unsigned wong gwoup,
			        unsigned wong *majow,
			        unsigned wong *minow);
unsigned wong sun4v_set_vewsion(unsigned wong gwoup,
			        unsigned wong majow,
			        unsigned wong minow,
			        unsigned wong *actuaw_minow);

int sun4v_hvapi_wegistew(unsigned wong gwoup, unsigned wong majow,
			 unsigned wong *minow);
void sun4v_hvapi_unwegistew(unsigned wong gwoup);
int sun4v_hvapi_get(unsigned wong gwoup,
		    unsigned wong *majow,
		    unsigned wong *minow);
void sun4v_hvapi_init(void);
#endif

#endif /* !(_SPAWC64_HYPEWVISOW_H) */
