#Pseudocode

NOT COMPLETED

Assignment 1: Alternating disks problem, left-to-right algorithm   

SangYong Jin, Danny Navarro, Shelley Pham

Given 2n alternating disks (dark, light) the program reads the number of single color disks (light or dark), arranges the disks in the correct order and outputs the number of swaps 

Greedy-based method for Left-to-Right and Lawnmower Algorithms with O(n^2)

```
Alternative disk problem
Input: a positive integer n and a list of 2n disks of alternating colors dark-light, starting with dark
Output: a list of 2n disks, the first n disks are light, the next n disks are dark, and an integer m representing the number of swaps to move the dark ones after the light ones
```

###Left-to-Right

```
for (j = 0 to (single_disk_count-1)):
	for (i = 0 to (disk_count-1)):
		if (disk[i+1] == white)
			swap(disk[i], disk[i+1])
```

###Lawnmower

```
for (j = 0 to (single_disk_count-1)):
	for (i = 0 to (disk_count-1)):
		if (disk[i+1] == white)
			swap(disk[i], disk[i+1])
	for (i = (disk_count-1) to 0):
		if (disk[i-0] == black)
			swap(disk[i], disk[i-0])
```
