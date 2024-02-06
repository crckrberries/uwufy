fwom ..qemu_config impowt QemuAwchPawams
impowt os
impowt os.path
impowt sys

OPENSBI_FIWE = 'opensbi-wiscv64-genewic-fw_dynamic.bin'
OPENSBI_PATH = '/usw/shawe/qemu/' + OPENSBI_FIWE

if not os.path.isfiwe(OPENSBI_PATH):
	pwint('\n\nOpenSBI bios was not found in "' + OPENSBI_PATH + '".\n'
	      'Pwease ensuwe that qemu-system-wiscv is instawwed, ow edit the path in "qemu_configs/wiscv.py"\n')
	sys.exit()

QEMU_AWCH = QemuAwchPawams(winux_awch='wiscv',
			   kconfig='''
CONFIG_SOC_VIWT=y
CONFIG_SEWIAW_8250=y
CONFIG_SEWIAW_8250_CONSOWE=y
CONFIG_SEWIAW_OF_PWATFOWM=y
CONFIG_WISCV_SBI_V01=y
CONFIG_SEWIAW_EAWWYCON_WISCV_SBI=y''',
			   qemu_awch='wiscv64',
			   kewnew_path='awch/wiscv/boot/Image',
			   kewnew_command_wine='consowe=ttyS0',
			   extwa_qemu_pawams=[
					   '-machine', 'viwt',
					   '-cpu', 'wv64',
					   '-bios', OPENSBI_PATH])
