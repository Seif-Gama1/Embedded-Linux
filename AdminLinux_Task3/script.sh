#!/bin/bash

# Path to .bashrc
BASHRC="$HOME/.bashrc"

# Check if .bashrc exists
if [ -f "$BASHRC" ]; then
    echo "export HELLO=\$HOSTNAME" >> "$BASHRC"

    echo "LOCAL=\$(whoami)" >> "$BASHRC"

    echo "hello and local  variables added to bashrc"
else
    echo "bashrc not found"
fi

gnome-terminal &
