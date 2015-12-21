# test
A simple huffman compression routine which takes three files as input: a text file, a huffman table file 
and a output binary file.  It checks the symbols of the input file and tries to find a match in the huffman table file.
Thus it generates a buffer sequence as a byte by padding zeroes if required. The buffered sequence is written to the 
binary file.
