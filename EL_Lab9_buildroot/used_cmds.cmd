## 2. Configure buildroot for RPi3 64 board
cd buildroot
# to list the available boards
ls configs/
make raspberrypi3_64_defconfig
# Customize your image
make menuconfig


## buildroot config:
Target Packages > Graphics libraries and applications > Qt6
Target packages > Fonts, cursors, icons, sounds and themes > Dejavue


# check building my custom app
ls output/target/usr/bin/ | grep Calc
appTask02_Calculator    # that the app name (from CMakeList.txt)


4. Flash image on your Disk
# Unmount everything on the disk first
sudo umount /dev/sdb1 2>/dev/null
sudo umount /dev/sdb2 2>/dev/null
# Wipe the partition table and first sectors completely
sudo wipefs -a /dev/sdb
# Zero out the first 100MB to be sure
sudo dd if=/dev/zero of=/dev/sdb bs=1M count=100 conv=fsync
# Confirm disk is clean
sudo fdisk -l /dev/sdb
# Should show: no partition table
# Flash the new image
sudo dd if=output/images/sdcard.img of=/dev/sdb bs=16M conv=fsync status=progress
# Force kernel to re-read partition table
sudo partprobe /dev/sdb
# Verify partitions were created correctly
sudo fdisk -l /dev/sdb
# Eject and remove your SD Card/USB Disk
sudo eject /dev/sdX 

# 5. inside RPi
export LANG=C.UTF-8
export LC_ALL=C.UTF-8
export QT_QPA_PLATFORM=linuxfb
appTask02_Calculator