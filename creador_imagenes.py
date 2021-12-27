#!/usr/bin/python3
# -*- coding: utf-8 -*-
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Polygon
from matplotlib.collections import PatchCollection
from matplotlib import collections  as mc
import numpy as np
import pylab
# import numpy as np
import argparse
import glob#, os
import sys

parser = argparse.ArgumentParser(description='Programa para graficar frames.')
parser.add_argument('-f','--pfile',help='Input data prefix file', required=True, action="store")

args =  parser.parse_args()
preName = args.pfile + '_'

fileFrames = []
# os.chdir('.')
for file in glob.glob(preName + '*.xy'):
    fileFrames.append(file)

fileFrames.sort()

contador=1

for f in fileFrames:
	fin = open(f,'r')
	data = fin.readlines()
	fin.close()

	fplot = f.split('.')[0]
	
	with open(f) as myfile:
		total_lines = sum(1 for line in myfile)
	
	ini = 0
	for linea in data:

		l = linea.split()
		#la variable ini le dice al programa si ya tuvo imagenes previas que cerrar
		
		ide=l[0].split()
		if ide[0]=="#":
			
			if ini != 0:
				
				cmap = plt.get_cmap('Set1')
				p = PatchCollection(patches, alpha=0.9)
				pylab.axes().set_aspect('equal')
				ax1 = pylab.gca()
				ax1.add_collection(p)
		
				pylab.xlim([1.5 * -(12.25/2), 1.5 * (12.25/2)])
				pylab.ylim([ - 1.5 * alturaSilo, 2.0 * alturaSilo])
				pylab.savefig(fout)
				pylab.cla()
				pylab.clf()
				pylab.close(fig)
				
			fig = pylab.figure(figsize=(10,10))
			fout = preName + '{:06d}.png'.format(ini)
			verts = []
			patches = []
			
			ini=ini+1
		elif l[0] == "caja":
			alturaSilo=float(l[2])
			verts.append([-(12.25/2), float(l[1])])
			verts.append([-(12.25/2), float(l[1])+alturaSilo+1])
			verts.append([(12.25/2), float(l[1])+alturaSilo+1])
			verts.append([(12.25/2), float(l[1])])
			patches.append(Polygon(verts, closed=True, facecolor=None))
			
		elif l[0] == "Ob":
			
			patches.append(Circle((float(l[2]),float(l[3])),float(l[4]), fill = True))
			
		else:

			patches.append(Circle((float(l[1]),float(l[2])), float(l[3]), fill=True))
		

		
		contador=contador+1
		
		if contador == total_lines-1:
			contador=0
			break

