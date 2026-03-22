usb start

# We add console=tty1 first for the logo, and console=ttyS0 last so text stays on your PC
setenv bootargs "earlycon=bcm2835aux,0x3f215040 console=tty1 console=ttyS0,115200 8250.nr_uarts=1 ignore_loglevel keep_bootcon loglevel=8 root=/dev/sda2 rw rootwait rootdelay=2 init=init"

fatload usb 0:1 ${kernel_addr_r} Image
fatload usb 0:1 ${fdt_addr} bcm2837-rpi-3-b-plus.dtb

booti ${kernel_addr_r} - ${fdt_addr}


