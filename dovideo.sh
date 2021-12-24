#!/bin/bash 
# dovideo.sh
# Script para concatenar imágenes secuenciales para armar una animación
# Manuel Carlevaro - 2021.07.26

if [ "$#" -ne 3 ]
then
    echo "Uso: "
    echo "  ./dovideo prefijo nombre_video frame_rate";
    echo "  "
    echo "      prefijo de archivos de imagen"
    echo "      nombre_video sin extensión (agrega .mp4)";
    echo "      frame_rate sugeridos: 20, 25, 30.";
    echo "  "
    echo "Ejemplo: "
    echo "  ./dovideo frm anim 25"
    echo "  "
    exit 1
fi

if ! [[ "$3" =~ ^[0-9]+$ ]]
then
    echo "El tercer argumento debe ser un entero." >&2;
    exit 1
fi

ffmpeg -i $1_%6d.png -c:v libx264 -r $3 -pix_fmt yuv420p $2.mp4
