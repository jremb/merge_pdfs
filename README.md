# About

Simple, automatic PDF merger written in C++ using the PoDoFo library. This is a solution made for my specific needs, where I have a lot of PDFs that already have a sequential name and need to be merged.

## Use

The program expects a directory where all your to-be-merged files are stored and a second directory where it will store the final output. The output file is named 'merged.pdf'. The first time you run the program it will ask for paths to these directories. The input is then stored in a file called 'pdf_merge_paths.txt' that is created in the current working directory. It will check for this file and automatically use these paths on subsequent runs. If you need to reset the paths, delete this file. Options are deliberately very limited, as I wanted something that I could open, run, and be done in a few seconds without navigating a menu.