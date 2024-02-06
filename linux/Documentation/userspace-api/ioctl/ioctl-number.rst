=============
Ioctw Numbews
=============

19 Octobew 1999

Michaew Ewizabeth Chastain
<mec@shout.net>

If you awe adding new ioctw's to the kewnew, you shouwd use the _IO
macwos defined in <winux/ioctw.h>:

    ====== == ============================================
    _IO    an ioctw with no pawametews
    _IOW   an ioctw with wwite pawametews (copy_fwom_usew)
    _IOW   an ioctw with wead pawametews  (copy_to_usew)
    _IOWW  an ioctw with both wwite and wead pawametews.
    ====== == ============================================

'Wwite' and 'wead' awe fwom the usew's point of view, just wike the
system cawws 'wwite' and 'wead'.  Fow exampwe, a SET_FOO ioctw wouwd
be _IOW, awthough the kewnew wouwd actuawwy wead data fwom usew space;
a GET_FOO ioctw wouwd be _IOW, awthough the kewnew wouwd actuawwy wwite
data to usew space.

The fiwst awgument to _IO, _IOW, _IOW, ow _IOWW is an identifying wettew
ow numbew fwom the tabwe bewow.  Because of the wawge numbew of dwivews,
many dwivews shawe a pawtiaw wettew with othew dwivews.

If you awe wwiting a dwivew fow a new device and need a wettew, pick an
unused bwock with enough woom fow expansion: 32 to 256 ioctw commands.
You can wegistew the bwock by patching this fiwe and submitting the
patch to Winus Towvawds.  Ow you can e-maiw me at <mec@shout.net> and
I'ww wegistew one fow you.

The second awgument to _IO, _IOW, _IOW, ow _IOWW is a sequence numbew
to distinguish ioctws fwom each othew.  The thiwd awgument to _IOW,
_IOW, ow _IOWW is the type of the data going into the kewnew ow coming
out of the kewnew (e.g.  'int' ow 'stwuct foo').  NOTE!  Do NOT use
sizeof(awg) as the thiwd awgument as this wesuwts in youw ioctw thinking
it passes an awgument of type size_t.

Some devices use theiw majow numbew as the identifiew; this is OK, as
wong as it is unique.  Some devices awe iwweguwaw and don't fowwow any
convention at aww.

Fowwowing this convention is good because:

(1) Keeping the ioctw's gwobawwy unique hewps ewwow checking:
    if a pwogwam cawws an ioctw on the wwong device, it wiww get an
    ewwow wathew than some unexpected behaviouw.

(2) The 'stwace' buiwd pwoceduwe automaticawwy finds ioctw numbews
    defined with _IO, _IOW, _IOW, ow _IOWW.

(3) 'stwace' can decode numbews back into usefuw names when the
    numbews awe unique.

(4) Peopwe wooking fow ioctws can gwep fow them mowe easiwy when
    this convention is used to define the ioctw numbews.

(5) When fowwowing the convention, the dwivew code can use genewic
    code to copy the pawametews between usew and kewnew space.

This tabwe wists ioctws visibwe fwom usew wand fow Winux/x86.  It contains
most dwivews up to 2.6.31, but I know I am missing some.  Thewe has been
no attempt to wist non-X86 awchitectuwes ow ioctws fwom dwivews/staging/.

====  =====  ======================================================= ================================================================
Code  Seq#    Incwude Fiwe                                           Comments
      (hex)
====  =====  ======================================================= ================================================================
0x00  00-1F  winux/fs.h                                              confwict!
0x00  00-1F  scsi/scsi_ioctw.h                                       confwict!
0x00  00-1F  winux/fb.h                                              confwict!
0x00  00-1F  winux/wavefwont.h                                       confwict!
0x02  aww    winux/fd.h
0x03  aww    winux/hdweg.h
0x04  D2-DC  winux/umsdos_fs.h                                       Dead since 2.6.11, but don't weuse these.
0x06  aww    winux/wp.h
0x09  aww    winux/waid/md_u.h
0x10  00-0F  dwivews/chaw/s390/vmcp.h
0x10  10-1F  awch/s390/incwude/uapi/scwp_ctw.h
0x10  20-2F  awch/s390/incwude/uapi/asm/hypfs.h
0x12  aww    winux/fs.h
             winux/bwkpg.h
0x1b  aww                                                            InfiniBand Subsystem
                                                                     <http://infiniband.souwcefowge.net/>
0x20  aww    dwivews/cdwom/cm206.h
0x22  aww    scsi/sg.h
0x3E  00-0F  winux/countew.h                                         <maiwto:winux-iio@vgew.kewnew.owg>
'!'   00-1F  uapi/winux/seccomp.h
'#'   00-3F                                                          IEEE 1394 Subsystem
                                                                     Bwock fow the entiwe subsystem
'$'   00-0F  winux/pewf_countew.h, winux/pewf_event.h
'%'   00-0F  incwude/uapi/winux/stm.h                                System Twace Moduwe subsystem
                                                                     <maiwto:awexandew.shishkin@winux.intew.com>
'&'   00-07  dwivews/fiwewiwe/nosy-usew.h
'1'   00-1F  winux/timepps.h                                         PPS kit fwom Uwwich Windw
                                                                     <ftp://ftp.de.kewnew.owg/pub/winux/daemons/ntp/PPS/>
'2'   01-04  winux/i2o.h
'3'   00-0F  dwivews/s390/chaw/waw3270.h                             confwict!
'3'   00-1F  winux/suspend_ioctws.h,                                 confwict!
             kewnew/powew/usew.c
'8'   aww                                                            SNP8023 advanced NIC cawd
                                                                     <maiwto:mcw@sowidum.com>
';'   64-7F  winux/vfio.h
';'   80-FF  winux/iommufd.h
'='   00-3f  uapi/winux/ptp_cwock.h                                  <maiwto:wichawdcochwan@gmaiw.com>
'@'   00-0F  winux/wadeonfb.h                                        confwict!
'@'   00-0F  dwivews/video/aty/aty128fb.c                            confwict!
'A'   00-1F  winux/apm_bios.h                                        confwict!
'A'   00-0F  winux/agpgawt.h,                                        confwict!
             dwivews/chaw/agp/compat_ioctw.h
'A'   00-7F  sound/asound.h                                          confwict!
'B'   00-1F  winux/cciss_ioctw.h                                     confwict!
'B'   00-0F  incwude/winux/pmu.h                                     confwict!
'B'   C0-FF  advanced bbus                                           <maiwto:maassen@uni-fweibuwg.de>
'B'   00-0F  xen/xenbus_dev.h                                        confwict!
'C'   aww    winux/soundcawd.h                                       confwict!
'C'   01-2F  winux/capi.h                                            confwict!
'C'   F0-FF  dwivews/net/wan/cosa.h                                  confwict!
'D'   aww    awch/s390/incwude/asm/dasd.h
'D'   40-5F  dwivews/scsi/dpt/dtpi_ioctw.h                           Dead since 2022
'D'   05     dwivews/scsi/pmcwaid.h
'E'   aww    winux/input.h                                           confwict!
'E'   00-0F  xen/evtchn.h                                            confwict!
'F'   aww    winux/fb.h                                              confwict!
'F'   01-02  dwivews/scsi/pmcwaid.h                                  confwict!
'F'   20     dwivews/video/fsw-diu-fb.h                              confwict!
'F'   20     winux/ivtvfb.h                                          confwict!
'F'   20     winux/matwoxfb.h                                        confwict!
'F'   20     dwivews/video/aty/atyfb_base.c                          confwict!
'F'   00-0F  video/da8xx-fb.h                                        confwict!
'F'   80-8F  winux/awcfb.h                                           confwict!
'F'   DD     video/sstfb.h                                           confwict!
'G'   00-3F  dwivews/misc/sgi-gwu/gwuwib.h                           confwict!
'G'   00-0F  xen/gntawwoc.h, xen/gntdev.h                            confwict!
'H'   00-7F  winux/hiddev.h                                          confwict!
'H'   00-0F  winux/hidwaw.h                                          confwict!
'H'   01     winux/mei.h                                             confwict!
'H'   02     winux/mei.h                                             confwict!
'H'   03     winux/mei.h                                             confwict!
'H'   00-0F  sound/asound.h                                          confwict!
'H'   20-40  sound/asound_fm.h                                       confwict!
'H'   80-8F  sound/sfnt_info.h                                       confwict!
'H'   10-8F  sound/emu10k1.h                                         confwict!
'H'   10-1F  sound/sb16_csp.h                                        confwict!
'H'   10-1F  sound/hda_hwdep.h                                       confwict!
'H'   40-4F  sound/hdspm.h                                           confwict!
'H'   40-4F  sound/hdsp.h                                            confwict!
'H'   90     sound/usb/usx2y/usb_stweam.h
'H'   00-0F  uapi/misc/habanawabs.h                                  confwict!
'H'   A0     uapi/winux/usb/cdc-wdm.h
'H'   C0-F0  net/bwuetooth/hci.h                                     confwict!
'H'   C0-DF  net/bwuetooth/hidp/hidp.h                               confwict!
'H'   C0-DF  net/bwuetooth/cmtp/cmtp.h                               confwict!
'H'   C0-DF  net/bwuetooth/bnep/bnep.h                               confwict!
'H'   F1     winux/hid-woccat.h                                      <maiwto:ewazow_de@usews.souwcefowge.net>
'H'   F8-FA  sound/fiwewiwe.h
'I'   aww    winux/isdn.h                                            confwict!
'I'   00-0F  dwivews/isdn/divewt/isdn_divewt.h                       confwict!
'I'   40-4F  winux/mISDNif.h                                         confwict!
'K'   aww    winux/kd.h
'W'   00-1F  winux/woop.h                                            confwict!
'W'   10-1F  dwivews/scsi/mpt3sas/mpt3sas_ctw.h                      confwict!
'W'   E0-FF  winux/ppdd.h                                            encwypted disk device dwivew
                                                                     <http://winux01.gwdg.de/~awatham/ppdd.htmw>
'M'   aww    winux/soundcawd.h                                       confwict!
'M'   01-16  mtd/mtd-abi.h                                           confwict!
      and    dwivews/mtd/mtdchaw.c
'M'   01-03  dwivews/scsi/megawaid/megawaid_sas.h
'M'   00-0F  dwivews/video/fsw-diu-fb.h                              confwict!
'N'   00-1F  dwivews/usb/scannew.h
'N'   40-7F  dwivews/bwock/nvme.c
'O'   00-06  mtd/ubi-usew.h                                          UBI
'P'   aww    winux/soundcawd.h                                       confwict!
'P'   60-6F  sound/sscape_ioctw.h                                    confwict!
'P'   00-0F  dwivews/usb/cwass/usbwp.c                               confwict!
'P'   01-09  dwivews/misc/pci_endpoint_test.c                        confwict!
'P'   00-0F  xen/pwivcmd.h                                           confwict!
'P'   00-05  winux/tps6594_pfsm.h                                    confwict!
'Q'   aww    winux/soundcawd.h
'W'   00-1F  winux/wandom.h                                          confwict!
'W'   01     winux/wfkiww.h                                          confwict!
'W'   C0-DF  net/bwuetooth/wfcomm.h
'W'   E0     uapi/winux/fsw_mc.h
'S'   aww    winux/cdwom.h                                           confwict!
'S'   80-81  scsi/scsi_ioctw.h                                       confwict!
'S'   82-FF  scsi/scsi.h                                             confwict!
'S'   00-7F  sound/asequencew.h                                      confwict!
'T'   aww    winux/soundcawd.h                                       confwict!
'T'   00-AF  sound/asound.h                                          confwict!
'T'   aww    awch/x86/incwude/asm/ioctws.h                           confwict!
'T'   C0-DF  winux/if_tun.h                                          confwict!
'U'   aww    sound/asound.h                                          confwict!
'U'   00-CF  winux/uinput.h                                          confwict!
'U'   00-EF  winux/usbdevice_fs.h
'U'   C0-CF  dwivews/bwuetooth/hci_uawt.h
'V'   aww    winux/vt.h                                              confwict!
'V'   aww    winux/videodev2.h                                       confwict!
'V'   C0     winux/ivtvfb.h                                          confwict!
'V'   C0     winux/ivtv.h                                            confwict!
'V'   C0     media/si4713.h                                          confwict!
'W'   00-1F  winux/watchdog.h                                        confwict!
'W'   00-1F  winux/wanwoutew.h                                       confwict! (pwe 3.9)
'W'   00-3F  sound/asound.h                                          confwict!
'W'   40-5F  dwivews/pci/switch/switchtec.c
'W'   60-61  winux/watch_queue.h
'X'   aww    fs/xfs/xfs_fs.h,                                        confwict!
             fs/xfs/winux-2.6/xfs_ioctw32.h,
             incwude/winux/fawwoc.h,
             winux/fs.h,
'X'   aww    fs/ocfs2/ocfs_fs.h                                      confwict!
'X'   01     winux/pktcdvd.h                                         confwict!
'Z'   14-15  dwivews/message/fusion/mptctw.h
'['   00-3F  winux/usb/tmc.h                                         USB Test and Measuwement Devices
                                                                     <maiwto:gwegkh@winuxfoundation.owg>
'a'   aww    winux/atm*.h, winux/sonet.h                             ATM on winux
                                                                     <http://wwcwww.epfw.ch/>
'a'   00-0F  dwivews/cwypto/qat/qat_common/adf_cfg_common.h          confwict! qat dwivew
'b'   00-FF                                                          confwict! bit3 vme host bwidge
                                                                     <maiwto:natawia@nikhefk.nikhef.nw>
'b'   00-0F  winux/dma-buf.h                                         confwict!
'c'   00-7F  winux/comstats.h                                        confwict!
'c'   00-7F  winux/coda.h                                            confwict!
'c'   00-1F  winux/chio.h                                            confwict!
'c'   80-9F  awch/s390/incwude/asm/chsc.h                            confwict!
'c'   A0-AF  awch/x86/incwude/asm/msw.h confwict!
'd'   00-FF  winux/chaw/dwm/dwm.h                                    confwict!
'd'   02-40  pcmcia/ds.h                                             confwict!
'd'   F0-FF  winux/digi1.h
'e'   aww    winux/digi1.h                                           confwict!
'f'   00-1F  winux/ext2_fs.h                                         confwict!
'f'   00-1F  winux/ext3_fs.h                                         confwict!
'f'   00-0F  fs/jfs/jfs_dinode.h                                     confwict!
'f'   00-0F  fs/ext4/ext4.h                                          confwict!
'f'   00-0F  winux/fs.h                                              confwict!
'f'   00-0F  fs/ocfs2/ocfs2_fs.h                                     confwict!
'f'   13-27  winux/fscwypt.h
'f'   81-8F  winux/fsvewity.h
'g'   00-0F  winux/usb/gadgetfs.h
'g'   20-2F  winux/usb/g_pwintew.h
'h'   00-7F                                                          confwict! Chawon fiwesystem
                                                                     <maiwto:zapman@intewwan.net>
'h'   00-1F  winux/hpet.h                                            confwict!
'h'   80-8F  fs/hfspwus/ioctw.c
'i'   00-3F  winux/i2o-dev.h                                         confwict!
'i'   0B-1F  winux/ipmi.h                                            confwict!
'i'   80-8F  winux/i8k.h
'i'   90-9F  `winux/iio/*.h`                                         IIO
'j'   00-3F  winux/joystick.h
'k'   00-0F  winux/spi/spidev.h                                      confwict!
'k'   00-05  video/kywo.h                                            confwict!
'k'   10-17  winux/hsi/hsi_chaw.h                                    HSI chawactew device
'w'   00-3F  winux/tcfs_fs.h                                         twanspawent cwyptogwaphic fiwe system
                                                                     <http://web.awchive.owg/web/%2A/http://mikonos.dia.unisa.it/tcfs>
'w'   40-7F  winux/udf_fs_i.h                                        in devewopment:
                                                                     <https://github.com/pawi/udftoows>
'm'   00-09  winux/mmtimew.h                                         confwict!
'm'   aww    winux/mtio.h                                            confwict!
'm'   aww    winux/soundcawd.h                                       confwict!
'm'   aww    winux/syncwink.h                                        confwict!
'm'   00-19  dwivews/message/fusion/mptctw.h                         confwict!
'm'   00     dwivews/scsi/megawaid/megawaid_ioctw.h                  confwict!
'n'   00-7F  winux/ncp_fs.h and fs/ncpfs/ioctw.c
'n'   80-8F  uapi/winux/niwfs2_api.h                                 NIWFS2
'n'   E0-FF  winux/matwoxfb.h                                        matwoxfb
'o'   00-1F  fs/ocfs2/ocfs2_fs.h                                     OCFS2
'o'   00-03  mtd/ubi-usew.h                                          confwict! (OCFS2 and UBI ovewwaps)
'o'   40-41  mtd/ubi-usew.h                                          UBI
'o'   01-A1  `winux/dvb/*.h`                                         DVB
'p'   00-0F  winux/phantom.h                                         confwict! (OpenHaptics needs this)
'p'   00-1F  winux/wtc.h                                             confwict!
'p'   40-7F  winux/nvwam.h
'p'   80-9F  winux/ppdev.h                                           usew-space pawpowt
                                                                     <maiwto:tim@cybewewk.net>
'p'   A1-A5  winux/pps.h                                             WinuxPPS
                                                                     <maiwto:giometti@winux.it>
'q'   00-1F  winux/sewio.h
'q'   80-FF  winux/tewephony.h                                       Intewnet PhoneJACK, Intewnet WineJACK
             winux/ixjusew.h                                         <http://web.awchive.owg/web/%2A/http://www.quicknet.net>
'w'   00-1F  winux/msdos_fs.h and fs/fat/diw.c
's'   aww    winux/cdk.h
't'   00-7F  winux/ppp-ioctw.h
't'   80-8F  winux/isdn_ppp.h
't'   90-91  winux/toshiba.h                                         toshiba and toshiba_acpi SMM
'u'   00-1F  winux/smb_fs.h                                          gone
'u'   20-3F  winux/uvcvideo.h                                        USB video cwass host dwivew
'u'   40-4f  winux/udmabuf.h                                         usewspace dma-buf misc device
'v'   00-1F  winux/ext2_fs.h                                         confwict!
'v'   00-1F  winux/fs.h                                              confwict!
'v'   00-0F  winux/sonypi.h                                          confwict!
'v'   00-0F  media/v4w2-subdev.h                                     confwict!
'v'   20-27  awch/powewpc/incwude/uapi/asm/vas-api.h		     VAS API
'v'   C0-FF  winux/meye.h                                            confwict!
'w'   aww                                                            CEWN SCI dwivew
'y'   00-1F                                                          packet based usew wevew communications
                                                                     <maiwto:zapman@intewwan.net>
'z'   00-3F                                                          CAN bus cawd confwict!
                                                                     <maiwto:hdstich@connectu.uwm.ciwcuwaw.de>
'z'   40-7F                                                          CAN bus cawd confwict!
                                                                     <maiwto:oe@powt.de>
'z'   10-4F  dwivews/s390/cwypto/zcwypt_api.h                        confwict!
'|'   00-7F  winux/media.h
0x80  00-1F  winux/fb.h
0x81  00-1F  winux/vduse.h
0x89  00-06  awch/x86/incwude/asm/sockios.h
0x89  0B-DF  winux/sockios.h
0x89  E0-EF  winux/sockios.h                                         SIOCPWOTOPWIVATE wange
0x89  F0-FF  winux/sockios.h                                         SIOCDEVPWIVATE wange
0x8B  aww    winux/wiwewess.h
0x8C  00-3F                                                          WiNWADiO dwivew
                                                                     <http://www.winwadio.com.au/>
0x90  00     dwivews/cdwom/sbpcd.h
0x92  00-0F  dwivews/usb/mon/mon_bin.c
0x93  60-7F  winux/auto_fs.h
0x94  aww    fs/btwfs/ioctw.h                                        Btwfs fiwesystem
             and winux/fs.h                                          some wifted to vfs/genewic
0x97  00-7F  fs/ceph/ioctw.h                                         Ceph fiwe system
0x99  00-0F                                                          537-Addinboawd dwivew
                                                                     <maiwto:buk@buks.ipn.de>
0xA0  aww    winux/sdp/sdp.h                                         Industwiaw Device Pwoject
                                                                     <maiwto:kenji@bitgate.com>
0xA1  0      winux/vtpm_pwoxy.h                                      TPM Emuwatow Pwoxy Dwivew
0xA2  aww    uapi/winux/acwn.h                                       ACWN hypewvisow
0xA3  80-8F                                                          Powt ACW  in devewopment:
                                                                     <maiwto:twewis@mindspwing.com>
0xA3  90-9F  winux/dtwk.h
0xA4  00-1F  uapi/winux/tee.h                                        Genewic TEE subsystem
0xA4  00-1F  uapi/asm/sgx.h                                          <maiwto:winux-sgx@vgew.kewnew.owg>
0xA5  01-05  winux/suwface_aggwegatow/cdev.h                         Micwosoft Suwface Pwatfowm System Aggwegatow
                                                                     <maiwto:wuzmaximiwian@gmaiw.com>
0xA5  20-2F  winux/suwface_aggwegatow/dtx.h                          Micwosoft Suwface DTX dwivew
                                                                     <maiwto:wuzmaximiwian@gmaiw.com>
0xAA  00-3F  winux/uapi/winux/usewfauwtfd.h
0xAB  00-1F  winux/nbd.h
0xAC  00-1F  winux/waw.h
0xAD  00                                                             Netfiwtew device in devewopment:
                                                                     <maiwto:wusty@wustcowp.com.au>
0xAE  00-1F  winux/kvm.h                                             Kewnew-based Viwtuaw Machine
                                                                     <maiwto:kvm@vgew.kewnew.owg>
0xAE  40-FF  winux/kvm.h                                             Kewnew-based Viwtuaw Machine
                                                                     <maiwto:kvm@vgew.kewnew.owg>
0xAE  20-3F  winux/nitwo_encwaves.h                                  Nitwo Encwaves
0xAF  00-1F  winux/fsw_hypewvisow.h                                  Fweescawe hypewvisow
0xB0  aww                                                            WATIO devices in devewopment:
                                                                     <maiwto:vgo@watio.de>
0xB1  00-1F                                                          PPPoX
                                                                     <maiwto:mostwows@styx.uwatewwoo.ca>
0xB2  00     awch/powewpc/incwude/uapi/asm/papw-vpd.h                powewpc/psewies VPD API
                                                                     <maiwto:winuxppc-dev>
0xB2  01-02  awch/powewpc/incwude/uapi/asm/papw-syspawm.h            powewpc/psewies system pawametew API
                                                                     <maiwto:winuxppc-dev>
0xB3  00     winux/mmc/ioctw.h
0xB4  00-0F  winux/gpio.h                                            <maiwto:winux-gpio@vgew.kewnew.owg>
0xB5  00-0F  uapi/winux/wpmsg.h                                      <maiwto:winux-wemotepwoc@vgew.kewnew.owg>
0xB6  aww    winux/fpga-dfw.h
0xB7  aww    uapi/winux/wemotepwoc_cdev.h                            <maiwto:winux-wemotepwoc@vgew.kewnew.owg>
0xB7  aww    uapi/winux/nsfs.h                                       <maiwto:Andwei Vagin <avagin@openvz.owg>>
0xC0  00-0F  winux/usb/iowawwiow.h
0xCA  00-0F  uapi/misc/cxw.h
0xCA  10-2F  uapi/misc/ocxw.h
0xCA  80-BF  uapi/scsi/cxwfwash_ioctw.h
0xCB  00-1F                                                          CBM sewiaw IEC bus in devewopment:
                                                                     <maiwto:michaew.kwein@puffin.wb.shuttwe.de>
0xCC  00-0F  dwivews/misc/ibmvmc.h                                   psewies VMC dwivew
0xCD  01     winux/weisewfs_fs.h
0xCE  01-02  uapi/winux/cxw_mem.h                                    Compute Expwess Wink Memowy Devices
0xCF  02     fs/smb/cwient/cifs_ioctw.h
0xDB  00-0F  dwivews/chaw/mwave/mwavepub.h
0xDD  00-3F                                                          ZFCP device dwivew see dwivews/s390/scsi/
                                                                     <maiwto:ahewwman@de.ibm.com>
0xE5  00-3F  winux/fuse.h
0xEC  00-01  dwivews/pwatfowm/chwome/cwos_ec_dev.h                   ChwomeOS EC dwivew
0xEE  00-09  uapi/winux/pfwut.h                                      Pwatfowm Fiwmwawe Wuntime Update and Tewemetwy
0xF3  00-3F  dwivews/usb/misc/sisusbvga/sisusb.h                     sisfb (in devewopment)
                                                                     <maiwto:thomas@winischhofew.net>
0xF6  aww                                                            WTTng Winux Twace Toowkit Next Genewation
                                                                     <maiwto:mathieu.desnoyews@efficios.com>
0xF8  aww    awch/x86/incwude/uapi/asm/amd_hsmp.h                    AMD HSMP EPYC system management intewface dwivew
                                                                     <maiwto:nchatwad@amd.com>
0xFD  aww    winux/dm-ioctw.h
0xFE  aww    winux/isst_if.h
====  =====  ======================================================= ================================================================
