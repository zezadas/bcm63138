cmd_drivers/mtd/brcmnand/brcmnand_bbt.o := /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/usr/bin/arm-unknown-linux-uclibcgnueabi-gcc -Wp,-MD,drivers/mtd/brcmnand/.brcmnand_bbt.o.d  -nostdinc -isystem /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.6.2/include -I/home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/include/linux/kconfig.h -I/extern/broadcom-bsp-4.16L05/shared/opensource/include/bcm963xx -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-bcm963xx/include -Iarch/arm/plat-bcm63xx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=2048 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DARCADYAN -g -Werror -Wfatal-errors -I /include/asm-generic -I/home/users/popeye_shen/ac88u-gpl/bcm963xx/bcmdrivers/opensource/include/bcm963xx -I/home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/include/bcm963xx    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(brcmnand_bbt)"  -D"KBUILD_MODNAME=KBUILD_STR(brcmnand_bbt)" -c -o drivers/mtd/brcmnand/brcmnand_bbt.o drivers/mtd/brcmnand/brcmnand_bbt.c

source_drivers/mtd/brcmnand/brcmnand_bbt.o := drivers/mtd/brcmnand/brcmnand_bbt.c

deps_drivers/mtd/brcmnand/brcmnand_bbt.o := \
    $(wildcard include/config/bcm/kf/mtd/bcmnand.h) \
    $(wildcard include/config/mtd/brcmnand/version.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/3.h) \
    $(wildcard include/config/mtd/brcmnand/vers/1/0.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/bcm/kf/arm/bcm963xx.h) \
    $(wildcard include/config/bcm/zone/acp.h) \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/tracing.h) \
  include/linux/gfp.h \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/pm/sleep.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/have/memblock/node.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/preempt/rt/full.h) \
  include/linux/typecheck.h \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/rt/base.h) \
    $(wildcard include/config/bcm/kf/cpu/down/preempt/on.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/bcm/kf/unaligned/exception.h) \
    $(wildcard include/config/mips/bcm963xx.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/bcm/kf/bounce.h) \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/brcm/bounce.h) \
  include/linux/compiler-gcc4.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/posix_types.h \
  include/asm-generic/posix_types.h \
  include/linux/bitops.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/bitops.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/irqflags.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/hwcap.h \
    $(wildcard include/config/bcm/kf/android.h) \
    $(wildcard include/config/bcm/android.h) \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  arch/arm/include/generated/mach/barriers.h \
    $(wildcard include/config/bcm/b15/mega/barrier.h) \
    $(wildcard include/config/bcm/kf/arm/errata/798181.h) \
  include/linux/linkage.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/linkage.h \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/const.h \
  include/linux/kernel.h \
    $(wildcard include/config/bcm/kf/printk/int/enabled.h) \
    $(wildcard include/config/bcm/printk/int/enabled.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/sysinfo.h \
  /opt/toolchains/crosstools-arm-gcc-4.6-linux-3.4-uclibc-0.9.32-binutils-2.21-NPTL/usr/lib/gcc/arm-unknown-linux-uclibcgnueabi/4.6.2/include/stdarg.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/bcm/kf/extra/debug.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/div64.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/compiler.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  include/linux/spinlock_types_raw.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/spinlock_types_nort.h \
  include/linux/rwlock_types.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/spinlock.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/atomic.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/atomic-long.h \
  include/linux/wait.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/current.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/seqlock.h \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/string.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/glue.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/pgtable-2level-types.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
  arch/arm/include/generated/asm/sizes.h \
  include/asm-generic/sizes.h \
  arch/arm/include/generated/mach/memory.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  include/asm-generic/getorder.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/preempt/rt.h) \
    $(wildcard include/config/bcm/kf/rcu/constant/bug.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/bcm/kf/cpp/support.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bug.h \
  include/linux/completion.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/rcutree.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/smp.h \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/pfn.h \
  arch/arm/include/generated/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
  include/asm-generic/topology.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/slab_def.h \
  include/linux/kmalloc_sizes.h \
  include/linux/mtd/mtd.h \
  include/linux/uio.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/math64.h \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/linux/param.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/timex.h \
  arch/arm/include/generated/mach/timex.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/iommu/api.h) \
    $(wildcard include/config/arch/omap.h) \
  include/linux/pm_wakeup.h \
  include/mtd/mtd-abi.h \
  include/linux/mtd/nand.h \
    $(wildcard include/config/bcm/kf/nand.h) \
  include/linux/mtd/flashchip.h \
  include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/bcm/kf/schedaudit.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/wakeup/latency/hist.h) \
    $(wildcard include/config/missed/timer/offsets/hist.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/cfs/bandwidth.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/mm/owner.h) \
  include/linux/capability.h \
  include/linux/rbtree.h \
  include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  include/linux/auxvec.h \
  arch/arm/include/generated/asm/auxvec.h \
  include/asm-generic/auxvec.h \
  include/linux/prio_tree.h \
  include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/kmap_types.h \
    $(wildcard include/config/debug/highmem.h) \
  arch/arm/include/generated/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/sem.h \
  include/linux/ipc.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/ipcbuf.h \
  include/asm-generic/ipcbuf.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/sembuf.h \
  include/linux/signal.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/signal.h \
  include/asm-generic/signal-defs.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/sigcontext.h \
  arch/arm/include/generated/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/pid.h \
  include/linux/proportions.h \
  include/linux/percpu_counter.h \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/rculist.h \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/resource.h \
  arch/arm/include/generated/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  include/linux/timerqueue.h \
  include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  include/linux/latencytop.h \
  include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/sysctl.h \
  include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  include/linux/hardirq.h \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/hardirq.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/irq.h \
    $(wildcard include/config/sparse/irq.h) \
  arch/arm/include/generated/mach/irqs.h \
  include/linux/irq_cpustat.h \
  include/linux/aio.h \
  include/linux/aio_abi.h \
  include/linux/mtd/bbm.h \
  include/linux/mtd/nand_ecc.h \
  include/linux/delay.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/delay.h \
  include/linux/vmalloc.h \
  drivers/mtd/brcmnand/brcmnand_priv.h \
    $(wildcard include/config/mtd/brcmnand/use/isr.h) \
    $(wildcard include/config/mtd/brcmnand/edu.h) \
    $(wildcard include/config/mtd/brcmnand/isr/queue.h) \
    $(wildcard include/config/mtd/brcmnand/correctable/err/handling.h) \
    $(wildcard include/config/cs1.h) \
    $(wildcard include/config/cs2.h) \
    $(wildcard include/config/cs3.h) \
    $(wildcard include/config/arm.h) \
  include/linux/mtd/brcmnand.h \
    $(wildcard include/config/mtd/brcmnand/vers/0/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/0/1.h) \
    $(wildcard include/config/mtd/brcmnand/vers/2/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/2/1.h) \
    $(wildcard include/config/mtd/brcmnand/vers/2/2.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/1/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/1/1.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/2.h) \
    $(wildcard include/config/mtd/brcmnand/vers/3/4.h) \
    $(wildcard include/config/bcm7601.h) \
    $(wildcard include/config/bcm7400a0.h) \
    $(wildcard include/config/brcmnand/major/vers.h) \
    $(wildcard include/config/brcmnand/minor/vers.h) \
    $(wildcard include/config/mtd/brcmnand/vers/4/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/5/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/6/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/7/0.h) \
    $(wildcard include/config/mtd/brcmnand/vers/7/1.h) \
  include/linux/version.h \
  include/linux/mtd/bchp_nand_7x.h \
    $(wildcard include/config/ext.h) \
    $(wildcard include/config/ext/cs1.h) \
    $(wildcard include/config/ext/cs2.h) \
    $(wildcard include/config/mask.h) \
    $(wildcard include/config/shift.h) \
    $(wildcard include/config/block/size/mask.h) \
    $(wildcard include/config/block/size/shift.h) \
    $(wildcard include/config/block/size/bk/size/8192kb.h) \
    $(wildcard include/config/block/size/bk/size/4096kb.h) \
    $(wildcard include/config/block/size/bk/size/2048kb.h) \
    $(wildcard include/config/block/size/bk/size/1024kb.h) \
    $(wildcard include/config/block/size/bk/size/512kb.h) \
    $(wildcard include/config/block/size/bk/size/256kb.h) \
    $(wildcard include/config/block/size/bk/size/128kb.h) \
    $(wildcard include/config/block/size/bk/size/64kb.h) \
    $(wildcard include/config/block/size/bk/size/32kb.h) \
    $(wildcard include/config/block/size/bk/size/16kb.h) \
    $(wildcard include/config/block/size/bk/size/8kb.h) \
    $(wildcard include/config/page/size/mask.h) \
    $(wildcard include/config/page/size/shift.h) \
    $(wildcard include/config/page/size/pg/size/512.h) \
    $(wildcard include/config/page/size/pg/size/1kb.h) \
    $(wildcard include/config/page/size/pg/size/2kb.h) \
    $(wildcard include/config/page/size/pg/size/4kb.h) \
    $(wildcard include/config/page/size/pg/size/8kb.h) \
    $(wildcard include/config/page/size/pg/size/16kb.h) \
    $(wildcard include/config/lock.h) \
    $(wildcard include/config/config/lock/mask.h) \
    $(wildcard include/config/lock/mask.h) \
    $(wildcard include/config/config/lock/shift.h) \
    $(wildcard include/config/lock/shift.h) \
    $(wildcard include/config/device/size/mask.h) \
    $(wildcard include/config/device/size/shift.h) \
    $(wildcard include/config/device/size/dvc/size/4mb.h) \
    $(wildcard include/config/device/size/dvc/size/8mb.h) \
    $(wildcard include/config/device/size/dvc/size/16mb.h) \
    $(wildcard include/config/device/size/dvc/size/32mb.h) \
    $(wildcard include/config/device/size/dvc/size/64mb.h) \
    $(wildcard include/config/device/size/dvc/size/128mb.h) \
    $(wildcard include/config/device/size/dvc/size/256mb.h) \
    $(wildcard include/config/device/size/dvc/size/512mb.h) \
    $(wildcard include/config/device/size/dvc/size/1gb.h) \
    $(wildcard include/config/device/size/dvc/size/2gb.h) \
    $(wildcard include/config/device/size/dvc/size/4gb.h) \
    $(wildcard include/config/device/size/dvc/size/8gb.h) \
    $(wildcard include/config/device/size/dvc/size/16gb.h) \
    $(wildcard include/config/device/size/dvc/size/32gb.h) \
    $(wildcard include/config/device/size/dvc/size/64gb.h) \
    $(wildcard include/config/device/size/dvc/size/128gb.h) \
    $(wildcard include/config/device/width/mask.h) \
    $(wildcard include/config/device/width/shift.h) \
    $(wildcard include/config/device/width/dvc/width/8.h) \
    $(wildcard include/config/device/width/dvc/width/16.h) \
    $(wildcard include/config/reserved0/mask.h) \
    $(wildcard include/config/reserved0/shift.h) \
    $(wildcard include/config/reserved1/mask.h) \
    $(wildcard include/config/reserved1/shift.h) \
    $(wildcard include/config/ful/adr/bytes/mask.h) \
    $(wildcard include/config/ful/adr/bytes/shift.h) \
    $(wildcard include/config/reserved2/mask.h) \
    $(wildcard include/config/reserved2/shift.h) \
    $(wildcard include/config/col/adr/bytes/mask.h) \
    $(wildcard include/config/col/adr/bytes/shift.h) \
    $(wildcard include/config/reserved3/mask.h) \
    $(wildcard include/config/reserved3/shift.h) \
    $(wildcard include/config/blk/adr/bytes/mask.h) \
    $(wildcard include/config/blk/adr/bytes/shift.h) \
    $(wildcard include/config/reserved4/mask.h) \
    $(wildcard include/config/reserved4/shift.h) \
    $(wildcard include/config/cs1/ext.h) \
    $(wildcard include/config/cs1/block/size/mask.h) \
    $(wildcard include/config/cs1/block/size/shift.h) \
    $(wildcard include/config/cs1/block/size/bk/size/8192kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/4096kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/2048kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/1024kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/512kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/256kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/128kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/64kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/32kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/16kb.h) \
    $(wildcard include/config/cs1/block/size/bk/size/8kb.h) \
    $(wildcard include/config/cs1/page/size/mask.h) \
    $(wildcard include/config/cs1/page/size/shift.h) \
    $(wildcard include/config/cs1/page/size/pg/size/512.h) \
    $(wildcard include/config/cs1/page/size/pg/size/1kb.h) \
    $(wildcard include/config/cs1/page/size/pg/size/2kb.h) \
    $(wildcard include/config/cs1/page/size/pg/size/4kb.h) \
    $(wildcard include/config/cs1/page/size/pg/size/8kb.h) \
    $(wildcard include/config/cs1/page/size/pg/size/16kb.h) \
    $(wildcard include/config/cs1/config/lock/mask.h) \
    $(wildcard include/config/cs1/config/lock/shift.h) \
    $(wildcard include/config/cs1/device/size/mask.h) \
    $(wildcard include/config/cs1/device/size/shift.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/4mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/8mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/16mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/32mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/64mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/128mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/256mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/512mb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/1gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/2gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/4gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/8gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/16gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/32gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/64gb.h) \
    $(wildcard include/config/cs1/device/size/dvc/size/128gb.h) \
    $(wildcard include/config/cs1/device/width/mask.h) \
    $(wildcard include/config/cs1/device/width/shift.h) \
    $(wildcard include/config/cs1/device/width/dvc/width/8.h) \
    $(wildcard include/config/cs1/device/width/dvc/width/16.h) \
    $(wildcard include/config/cs1/reserved0/mask.h) \
    $(wildcard include/config/cs1/reserved0/shift.h) \
    $(wildcard include/config/cs1/reserved1/mask.h) \
    $(wildcard include/config/cs1/reserved1/shift.h) \
    $(wildcard include/config/cs1/ful/adr/bytes/mask.h) \
    $(wildcard include/config/cs1/ful/adr/bytes/shift.h) \
    $(wildcard include/config/cs1/reserved2/mask.h) \
    $(wildcard include/config/cs1/reserved2/shift.h) \
    $(wildcard include/config/cs1/col/adr/bytes/mask.h) \
    $(wildcard include/config/cs1/col/adr/bytes/shift.h) \
    $(wildcard include/config/cs1/reserved3/mask.h) \
    $(wildcard include/config/cs1/reserved3/shift.h) \
    $(wildcard include/config/cs1/blk/adr/bytes/mask.h) \
    $(wildcard include/config/cs1/blk/adr/bytes/shift.h) \
    $(wildcard include/config/cs1/reserved4/mask.h) \
    $(wildcard include/config/cs1/reserved4/shift.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/bcmdrivers/opensource/include/bcm963xx/bcm_map_part.h \
    $(wildcard include/config/bcm96318.h) \
    $(wildcard include/config/bcm963268.h) \
    $(wildcard include/config/bcm96328.h) \
    $(wildcard include/config/bcm96362.h) \
    $(wildcard include/config/bcm96838.h) \
    $(wildcard include/config/bcm963138.h) \
    $(wildcard include/config/bcm960333.h) \
    $(wildcard include/config/bcm963381.h) \
    $(wildcard include/config/bcm963148.h) \
    $(wildcard include/config/bcm96848.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/shared/opensource/include/bcm963xx/63138_map_part.h \
    $(wildcard include/config/2/bar1/size/mask.h) \
    $(wildcard include/config/2/bar1/disable.h) \
    $(wildcard include/config/lo/match/address/mask.h) \
    $(wildcard include/config/lo/size/256mb.h) \
    $(wildcard include/config/lo/size/max.h) \
    $(wildcard include/config/lo/match/addr/mask.h) \
    $(wildcard include/config/lo/enable/mask.h) \
    $(wildcard include/config/match/mask.h) \
    $(wildcard include/config/match/shift.h) \
    $(wildcard include/config/data/mask.h) \
    $(wildcard include/config/offset/mask.h) \
    $(wildcard include/config/access/en.h) \
    $(wildcard include/config/bcm/gmac.h) \
    $(wildcard include/config/5x3/crossbar/support.h) \
    $(wildcard include/config/4x2/crossbar/support.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/bcmdrivers/opensource/include/bcm963xx/bcmtypes.h \
  arch/arm/include/generated/mach/hardware.h \
    $(wildcard include/config/plat/bcm63xx/acp.h) \
  include/linux/mtd/mtd64.h \
  include/asm-generic/gcclib.h \
    $(wildcard include/config/cpu/little/endian.h) \
  include/asm-generic/longlong.h \
  include/linux/module.h \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  include/linux/stat.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/stat.h \
  include/linux/kmod.h \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/elf.h \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/user.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/tracepoint.h \
  include/linux/static_key.h \
  include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
    $(wildcard include/config/preempt/base.h) \
  include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/users/popeye_shen/ac88u-gpl/bcm963xx/kernel/linux-3.4rt/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \

drivers/mtd/brcmnand/brcmnand_bbt.o: $(deps_drivers/mtd/brcmnand/brcmnand_bbt.o)

$(deps_drivers/mtd/brcmnand/brcmnand_bbt.o):