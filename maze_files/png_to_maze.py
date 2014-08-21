#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 14 03:25:28 2014

@author: garrett
"""

import matplotlib.image as mpimg
import argparse
import numpy as np


##This snippet allows you to have the '\n' new lines in the program description below
class MyParser( argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write( 'error: {}\n'.format(message) )
        self.print_help()
        sys.exit(2)


def main():

	parser = argparse.ArgumentParser(description="Converts a .png into a maze file for input to pinn"
						"\nNote: the image should be made of 4 types pixels in RGB:"
						"\n(0,0,0) -> 0"
						"\n(x,0,0) -> 1 (where x is non-zero, for example, it could be 255)"
						"\n(0,x,0) -> 2"
						"\n(0,0,x) -> 3"
						"\n\nExample usage: ./png_to_maze -i ~/example_maze.png -o ./example_maze)")
	parser.add_argument('-i', '--input', type=str, required=True, help="input image filename")		
	parser.add_argument('-o', '--output', type=str, required=True, help="input image filename")
	args = parser.parse_args()	
	
	image_filename = args.input
	output_filename = args.output	
	
	img = mpimg.imread(image_filename)
	
	with open(output_filename, 'w') as file:
		for row in range(img.shape[0]):
			for col in range(img.shape[1]):
				current_pix = img[row][col][:]
				#if the pixel is RGB=(0,0,0), then set maze to be zero for this point
				if np.where(current_pix!=0)[0].size == 0:
					maze_value = 0
				else:
					#set maze value to be N if the N-th element of (R,G,B) is non-zero
					#example: (0,50,0) would mean maze_value = 2
					maze_value = np.where(current_pix!=0)[0][0] + 1
				file.write(str(maze_value) + ' ')
			file.write('\n')
	

if __name__ == '__main__':
	main()
