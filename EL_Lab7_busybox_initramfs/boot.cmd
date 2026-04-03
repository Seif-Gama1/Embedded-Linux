echo "--- Starting Seif Initramfs Boot ---"

setenv bootargs "earlycon=bcm2835aux,0x3f215040 console=tty1 console=ttyS0,115200 8250.nr_uarts=1 ignore_loglevel keep_bootcon loglevel=8 rdinit=/sbin/init"

usb start

# --- ATTEMPT 1: USB ---
echo ">>> Loading from USB..."
if fatload usb 0:1 ${kernel_addr_r} Image; then
    if fatload usb 0:1 ${fdt_addr_r} bcm2837-rpi-3-b-plus.dtb; then
        if fatload usb 0:1 ${ramdisk_addr_r} initramfs.uboot; then
            setenv ramdisk_size ${filesize}
            echo "[OK] USB Load Success. Booting..."
            booti ${kernel_addr_r} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r}
        else
            echo "!! initramfs.uboot not found on USB. Failing over to TFTP..."
        fi
    else
        echo "!! DTB not found on USB. Failing over to TFTP..."
    fi
else
    echo "!! Image not found on USB. Failing over to TFTP..."
fi

# --- ATTEMPT 2: TFTP ---
echo ">>> USB failed. Trying TFTP..."
setenv ipaddr 192.168.2.2
setenv serverip 192.168.2.1

if tftp ${kernel_addr_r} Image; then
    if tftp ${fdt_addr_r} bcm2837-rpi-3-b-plus.dtb; then
        if tftp ${ramdisk_addr_r} ramfs; then
            setenv ramdisk_size ${filesize}
            echo "[OK] TFTP Load Success. Booting..."
            booti ${kernel_addr_r} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r}
        else
            echo "!! Init ramFS not found on TFTP"
        fi
    else
        echo "!! DTB not found on TFTP"
    fi
else
    echo "!! Image not found on TFTP"
fi

echo "!! ERROR: All boot sources failed !!"
