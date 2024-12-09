#!/bin/bash

# Caminhos fixos para as texturas sem aspas
north_texture="maps/textures/2no_texture.xpm"
south_texture="maps/textures/2so_texture.xpm"
west_texture="maps/textures/2we_texture.xpm"
east_texture="maps/textures/2ea_texture.xpm"

# Itera sobre todos os arquivos .cub
for file in maps/maps/challenges/*.cub; do
    echo "Updating textures in $file..."
    sed -i -E "
        s|(^[[:space:]]*NO[[:space:]]+).*|\\1$north_texture|;
        s|(^[[:space:]]*SO[[:space:]]+).*|\\1$south_texture|;
        s|(^[[:space:]]*WE[[:space:]]+).*|\\1$west_texture|;
        s|(^[[:space:]]*EA[[:space:]]+).*|\\1$east_texture|
    " "$file"
done
