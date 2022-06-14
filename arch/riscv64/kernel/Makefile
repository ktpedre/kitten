extra-y		:= head.o head64.o bootstrap.o vmlwk.lds
EXTRA_FLAGS	:= -traditional -nostdlib -nodefaultlibs -ffreestanding

obj-y		:= setup.o \
               cpuinfo.o resource.o \
               entry.o show.o syscall.o cpu.o \
               interrupts.o \
               time.o sys_arch_prctl.o \
               task.o sched.o maccess.o tlbflush.o signal.o \
               traps.o ptrace.o \
               cpu_ops.o \
               reboot.o pda.o
# NMG Disabled for now (or maybe forever)
# memblock.o mpboot.o xcall.o acpi.o bitops.c entry-fpsimd.o irqchip.o smccc-call.o smp.o smp_spin_table.o psci.o topology.o
#obj-$(CONFIG_ARM64_ACPI_PARKING_PROTOCOL) += acpi_parking_protocol.o

obj-$(CONFIG_EFI)     += efi-header.o

# obj-y                 += pci/
# obj-y                 += timers/
