#!/usr/bin/python -tt

import sys,os

#Should be changed to the name of the *.out file produced in /bin
ROBOT_NAME = 'Zaphod'
RRIO_IPADDRESS = '10.20.59.2'

#Global functions for the actions
def build():
    os.system('cd src && make && cd ..')

def clean():
    os.system('cd src && make clean && cd ..')

def deploy():
    command = 'cd bin && wput '+ ROBOT_NAME+'.out ftp://frc:frc@'+RRIO_IPADDRESS+'/ni-rt/system/FRC_UserProgram.out'
    os.system(command)

#Check that there is actually an action to perform
if len(sys.argv) == 1:
    print("Requires an argument")
    exit()

#Bulk of the program that checks for the actions it needs to do

if sys.argv[1] == 'build':
    build()

if sys.argv[1] == 'clean':
    clean()

if sys.argv[1] == 'buildclean':
    build()
    clean()

if sys.argv[1] == 'deploy':
    deploy()


