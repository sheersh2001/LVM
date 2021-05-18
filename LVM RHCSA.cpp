import os
import subprocess as sp
def createpartition():
    print("\nEnter the disk name: ",end="")
    diskname=input()
    os.system(f"fdisk /dev/{diskname}")
    os.system("udevadm settle")
    os.system("tput setaf 1")
    print("\nPartition created successfully")
    
def CPV() :
    print("\nEnter the name of the partition/hardisk: ", end="")
    partitionname=input()
    os.system("tput setaf 2")
    os.system(f"pvcreate /dev/{partitionname}")
    os.system("tput setaf 1")
    print("\nPhysical Volume created successfully")
    
def CVG() :
    print("\nEnter the name for the volume group to be created: ", end="")
    vgname=input()
    print("\nEnter the name of the 1st phyisical volume to be merged: ", end="")
    pvname1=input()
    print("\nEnter the name of the 2nd phyisical volume to be merged: ", end="")
    pvname2=input()
    os.system("tput setaf 2")
    os.system(f"vgcreate {vgname} /dev/{pvname1} /dev/{pvname2}")
    os.system("tput setaf 1")
    print("\nVolume Group created successfully")
    
def CLV() :
    print("\nEnter the name for the logical volume to be created: ", end="")
    lvname=input()
    print("\nEnter the name of the volume group(source): ", end="")
    vgname=input()
    print("\nEnter the size in GiB: ",end="")
    lsize=input()
    os.system("tput setaf 2")
    os.system(f"lvcreate --size {lsize}G --name {lvname} {vgname}") 
    os.system("tput setaf 7")
    print("\nLet's format the logical volume :-")
    os.system("tput setaf 2")
    os.system(f"mkfs.ext4 /dev/{vgname}/{lvname}")
    os.system("tput setaf 1")
    print("\nLogical Volume created successfully")
    os.system("tput setaf 6")
    print("\nNow let's Mount..")
    print("\nMount will be done temprarily after reboot it will again unmount..")
    os.system("tput setaf 10")
    print("\nLets create a folder for you.: ")
    os.system("tput setaf 7")
    print("\nEnter the path followed by name for the folder to be created(eg. /root/mylvmfold ,etc) : ",end="")
    foldpath=input()
    os.system(f"mkdir {foldpath}")
    os.system("tput setaf 1")
    print("\nFolder created successfully.")
    os.system("tput setaf 2")
    os.system(f"mount /dev/{vgname}/{lvname} {foldpath}")
            
                  
os.system("tput setaf 7")
os.system("clear")
while 1:
    print('''
    1. List all the harddisk attached\n
    2. List all the block devices\n
    3. List all the mounted devices\n
    4. Create new volume\n
    5. Reduce logical  volume\n
    6. Extend logical  volume\n
    7. Display volume\n
    8. Remove volume\n
    9.. Exit\n
    ''')
    print("Enter your choice: ",end="")
    lvm=input()
    
    if lvm == "1" :
        os.system("tput setaf 2")
        os.system("fdisk -l")
    
    elif lvm == "2" :
        os.system("tput setaf 2")
        os.system("lsblk")
    
    elif lvm == "3" :
        os.system("tput setaf 2")
        os.system("df -hT")
                
    elif lvm == "4" :
        os.system("clear")
        os.system("tput setaf 7")
        while 1:
            print('''
        1. Create physical volume(PV)\n
        2. Create volume group(VG)\n
        3. Create logical volume(LG)\n
        4. Create new partition\n
        5. Go to previous menu\n
        6. Exit\n
            ''')
            print("Enter your choice : ",end="")
            lvc=input()
            if lvc == "1" :
                while 1:
                    print("\nPartition available.?(yes/no)" , end="")
                    pl=input()
                    if pl == "yes" :
                        CPV()
                        break
                    elif pl == "no" :
                        createpartition()
                        os.system("clear")
                        CPV()
                        break
                    os.system("tput setaf 7")
                    input("\nPress Enter to Continue :")
                    os.system("clear")
            elif lvc == "2" :
                CVG()
            elif lvc == "3" :
                CLV()
            elif lvc == "5" :
                break
            elif lvc == "4" :
                newpartition()
            elif lvc == "6" :
                os.system("tput setaf 7")
                exit()
            else :
                os.system("tput setaf 1")
                print("\nInvalid Choice")
            os.system("tput setaf 7")
            input("\nPress Enter to Continue :")
            os.system("clear")
                
    elif lvm == '5':
        print("\n")
        os.system("tput setaf 7")
        print("\t\t----------------------")
        print("\t\t!! Reduse partition !!")
        print("\t\t----------------------")
        os.system("tput setaf 2")
        print("\n")
        os.system("pvs")
        print("\n")
        lv_name = input("Enter the lv_name: " )
        print("\n")
        os.system("lvdisplay | grep {}".format(lv_name))
        print("\n")

        os.system("tput setaf 7")
        folder = input("Enter mount folder path followed by name (eg. /lvmfold1 ,etc)  ")
        pv_name = input("Enter already created PV name: ")
        size = input("Enter the size to reduce (GB) (eg. 5,10,etc): ")
        lv_path = input("Enter the LV Path: ")
        print("\n")
        os.system("umount {}".format(folder))
        os.system("e2fsck -f {}".format(pv_name))
        os.system("resize2fs {0} {1}G".format(lv_path,size))
        os.system("lvreduce --size -{0}G {1}".format(size,lv_path))
        os.system("mount {0} {1}".format(lv_path,folder))
                
    elif lvm == '6':
        print("\n")
        os.system("tput setaf 3")
        print("\t\t---------------")
        print("\t\t!! LV Extend !!")
        print("\t\t---------------")
        os.system("tput setaf 7")
        print("\n")
        lv_name = input("Enter the lv_name: " )
        print("\n")
        os.system("lvdisplay | grep {}".format(lv_name))
        print("\n")
        size = input("Enter the size: ")
        location = input("Enter the LV Path: ")
        os.system("lvextend --size +{0}GB {1}".format(size,location))
        os.system("resize2fs {}".format(location))
        print("\n")
        os.system("tput setaf 7")
        input("\nPress Enter to Continue :")
        os.system("clear")
                
    elif lvm == "7" :
        os.system("clear")
        os.system("tput setaf 7")
        while 1:
            print('''
        1. Display physical volume\n
        2. Display volume group\n
        3. Display logical volume\n
        4. Go to previous menu\n
        5. Exit\n
            ''')
            print("Enter your choice : ",end="")
            lvd=input()
            if lvd == "1" :
                print("Enter hardisk name: ",end="")
                pname=input()
                os.system("tput setaf 2")
                os.system(f"pvdisplay /dev/{pname}")
            elif lvd == "2" :
                print("Enter volume group name: ",end="")
                vname=input()
                os.system("tput setaf 2")
                os.system(f"vgdisplay {vname}")
            elif lvd == "3" :
                os.system("tput setaf 7")
                print("Enter volume group name: ",end="")
                vname=input()
                os.system("tput setaf 7")
                print("Enter logical Volume name: ",end="")
                lname=input()
                os.system("tput setaf 2")
                os.system(f"lvdisplay /dev/{vname}/{lname}")
            elif lvd == "4" :
                break
            elif lvd == "5" :
                os.system("tput setaf 7")
                exit()
            else :
                os.system("tput setaf 1")
                print("\nInvalid Choice")
            os.system("tput setaf 7")
            input("\nPress Enter to Continue :")
            os.system("clear")
                
    elif lvm == "8" :
        os.system("clear")
        os.system("tput setaf 7")
        while 1:
            print('''
        1. Remove physical volume\n
        2. Remove volume group\n
        3. Remove logical volume\n
        4. Go to previous menu\n
        5. Exit\n
            ''')
            print("Enter your choice : ",end="")
            lvr=input()
            if lvr == "1":
                name=input("Enter the name of Physical Volume:")
                os.system("tput setaf 2")
                os.system(f"pvremove /dev/{name}")
            elif lvr == "2":
                name=input("Enter the name of Volume Group:")
                os.system("tput setaf 2")
                os.system(f"vgremove {name} ")
                
            elif lvr == "3":
                name1=input("\nEnter the mount point(Path followed by name) : ")
                name=input("\nEnter the name of Logical Volume :")
                name2=input("\nEnter the Volume group name: ")
                os.system("tput setaf 2")
                os.system(f"umount {name1}")
                os.system(f"lvremove /dev/{name2}/{name}")
        
            elif lvr == "4" :
                break
            elif lvr == "5" :
                os.system("tput setaf 7")
                exit()
            else :
                os.system("tput setaf 1")
                print("\nInvalid Choice")
            os.system("tput setaf 7")
            input("\nPress Enter to Continue :")
            os.system("clear")
    elif lvm == "9" :
        os.system("tput setaf 7")
        exit()
    else:
        os.system("tput setaf 1")
    os.system("tput setaf 7")
    input("\nPress Enter to Continue :")
    os.system("clear")

