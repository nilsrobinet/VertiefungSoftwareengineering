#!/bin/bash

# TODO: add additional forwarding options

qemu-system-x86_64 -m 4G -smp 8 -enable-kvm\
                    -nic user,hostfwd=tcp::60022-:22,hostfwd=tcp::8090-:8090\
                    -display none\
                     build_server.qcow2&
VM_PID="$!"
alias stopvm="kill $VM_PID; unalias stopvm"
echo "PID of qemu $VM_PID"
echo "kill VM with stopvm"


