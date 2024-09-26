# Simple tag enumeration

Program that can parse a text file which contains XML-like tags,
in order to extract the tag types and the text elements they surround. More specifically,
given such a text file you must
- Identify each element tag
- Sount the number of occurrences of the tag and store the tag label
- Store the text enclosed by each tag type.


## To compile code use command:
```bash
make
```
## To Run code use command:
```bash
make run
```
## user will prompted to enter option `( r , p, d, l)` or `c` or `q`

`r`  must be entered with text file name like : r file.txt

`p`  is for printing to screen

`d` is for outputing to file called tag.txt on the same directory

`l` is for search, it must be entered with tag name like : l tagName

`c` for cleaning shell command screen

`q` is for quit program 
