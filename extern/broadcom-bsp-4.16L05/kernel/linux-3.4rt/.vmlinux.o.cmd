cmd_vmlinux.o := /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/usr/bin/arm-unknown-linux-uclibcgnueabi-ld -EL  -r -o vmlinux.o arch/arm/kernel/head.o arch/arm/kernel/init_task.o  init/built-in.o --start-group  usr/built-in.o  arch/arm/kernel/built-in.o  arch/arm/mm/built-in.o  arch/arm/common/built-in.o  arch/arm/net/built-in.o  arch/arm/mach-bcm963xx/built-in.o  arch/arm/plat-bcm63xx/built-in.o  kernel/built-in.o  mm/built-in.o  fs/built-in.o  ipc/built-in.o  security/built-in.o  crypto/built-in.o  block/built-in.o  arch/arm/lib/lib.a  lib/lib.a  arch/arm/lib/built-in.o  lib/built-in.o  drivers/built-in.o  sound/built-in.o  firmware/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/boardparms/bcm963xx/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/bcmdrivers/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/utils/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/flash/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/spi/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/rdp/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/drv/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/drivers/built-in.o  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/pmc/impl1/built-in.o  net/built-in.o --end-group 
