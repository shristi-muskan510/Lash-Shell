#!/bin/bash

set -e

echo "🔧 Building lash..."
make

echo "Installing lash to /usr/local/bin..."
sudo cp lash /usr/local/bin/lash

echo "✅ Installed! You can now run 'lash' from anywhere."