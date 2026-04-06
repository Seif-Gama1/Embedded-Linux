TFTP:
 1972  sudo ip addr add 192.168.2.1/24 dev enp44s0 
 1973  sudo ip link set enp44s0 up
 1974  sudo apt install tftpd-hpa
 1975  sudo chmod 644 /srv/tftp/initramfs.uboot
 1976  sudo systemctl restart tftpd-hpa
 1977  sudo systemctl status tftpd-hpa


initramfs:
 2030  find . | cpio -H newc -o --owner root:root > ../initramfs.cpio
 2031  gzip ../initramfs.cpio 
 2032  ../u-boot/tools/mkimage -A arm  -olinux -T ramdisk -d ../initramfs.cpio.gz ../initramfs.uboot
 2033  sudo chmod 644 ../initramfs.uboot 
 2034  sudo cp ../initramfs.uboot /srv/tftp
